#include "PhysicsSystem.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"

#include "AEntity.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <Jolt/Physics/Collision/RayCast.h>
#include <Jolt/Physics/Collision/CastResult.h>
//#include <BroadPhaseLayer.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>
#include <Jolt/Physics/Body/BodyFilter.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Collision/NarrowPhaseQuery.h>
#include <algorithm>


namespace {

// Conversion directe des coordonnées de Jolt vers le moteur
inline glm::vec3 ToEnginePosition(const JPH::RVec3 &pos) {
  return {pos.GetX(), pos.GetY(), pos.GetZ()};
}

inline glm::vec3 ToEngineRotation(const JPH::Quat &rot) {
  glm::quat q(rot.GetW(), rot.GetX(), rot.GetY(), rot.GetZ());
  return glm::degrees(glm::eulerAngles(q));
}

} 

class SimpleBroadPhaseLayerInterface final
    : public JPH::BroadPhaseLayerInterface {
public:
  JPH::uint GetNumBroadPhaseLayers() const override { return 1; }
  JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer) const override {
    return JPH::BroadPhaseLayer(0);
  }
};

class SimpleObjectVsBroadPhaseLayerFilter final
    : public JPH::ObjectVsBroadPhaseLayerFilter {
public:
  bool ShouldCollide(JPH::ObjectLayer, JPH::BroadPhaseLayer) const override {
    return true;
  }
};

class SimpleObjectLayerPairFilter final : public JPH::ObjectLayerPairFilter {
public:
  bool ShouldCollide(JPH::ObjectLayer layer1, JPH::ObjectLayer layer2) const override {
    auto* phys = NNE::Systems::PhysicsSystem::GetInstance();
    return phys->LayersShouldCollide(layer1, layer2);
  }
};

namespace NNE::Systems {

PhysicsSystem* PhysicsSystem::instance = nullptr;

/**
 * <summary>
 * Configure les allocations et enregistre les types Jolt.
 * </summary>
 */
PhysicsSystem::PhysicsSystem() : tempAllocator(nullptr), jobSystem(nullptr), layerMasks(), initialized(false) {
  instance = this;
  JPH::RegisterDefaultAllocator();
  JPH::Factory::sInstance = new JPH::Factory();
  JPH::RegisterTypes();

  tempAllocator = new JPH::TempAllocatorImpl(10 * 1024 * 1024);
  jobSystem = new JPH::JobSystemThreadPool(
      JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers,
      std::thread::hardware_concurrency() - 1);
  layerMasks.fill(0xFFFFFFFF);
}

/**
 * <summary>
 * Initialise les structures internes de Jolt Physics.
 * </summary>
 */
void PhysicsSystem::Initialize() {
  static SimpleBroadPhaseLayerInterface broadPhaseLayerInterface;
  static SimpleObjectVsBroadPhaseLayerFilter broadPhaseFilter;
  static SimpleObjectLayerPairFilter objectLayerFilter;

  physicsSystem.Init(1024, 0, 1024, 1024, broadPhaseLayerInterface,
                     broadPhaseFilter, objectLayerFilter);

  physicsSystem.SetContactListener(&contactListener);
}

/**
 * <summary>
 * Nettoie les ressources allouées par Jolt.
 * </summary>
 */
PhysicsSystem::~PhysicsSystem() {
  delete tempAllocator;
  tempAllocator = nullptr;
  delete jobSystem;
  jobSystem = nullptr;
  JPH::UnregisterTypes();
  delete JPH::Factory::sInstance;
  JPH::Factory::sInstance = nullptr;
  if (instance == this)
    instance = nullptr;
}

/**
 * <summary>
 * Fournit un accès au système physique Jolt.
 * </summary>
 */
JPH::PhysicsSystem *PhysicsSystem::GetPhysicsSystem() { return &physicsSystem; }

PhysicsSystem* PhysicsSystem::GetInstance() { return instance; }

void PhysicsSystem::SetLayerCollision(JPH::ObjectLayer layer1, JPH::ObjectLayer layer2, bool shouldCollide) {
  if (shouldCollide) {
    layerMasks[layer1] |= (1u << layer2);
    layerMasks[layer2] |= (1u << layer1);
  } else {
    layerMasks[layer1] &= ~(1u << layer2);
    layerMasks[layer2] &= ~(1u << layer1);
  }
}

bool PhysicsSystem::LayersShouldCollide(JPH::ObjectLayer layer1, JPH::ObjectLayer layer2) const {
  return (layerMasks[layer1] & (1u << layer2)) != 0;
}

void PhysicsSystem::RegisterCollider(JPH::BodyID id, NNE::Component::Physics::ColliderComponent* collider) {
  colliderMap[id] = collider;
}

NNE::Component::Physics::ColliderComponent* PhysicsSystem::GetCollider(JPH::BodyID id) {
  auto it = colliderMap.find(id);
  return it != colliderMap.end() ? it->second : nullptr;
}

void PhysicsSystem::UnregisterCollider(JPH::BodyID id) {
  colliderMap.erase(id);
}

/**
 * <summary>
 * Prépare le système physique avant utilisation.
 * </summary>
 */
void PhysicsSystem::Awake() {
  if (!initialized) {
    Initialize();
    initialized = true;
  }
}

/**
 * <summary>
 * Démarre le système physique.
 * </summary>
 */
void PhysicsSystem::Start() {}

/**
 * <summary>
 * Avance la simulation physique et synchronise les entités.
 * </summary>
 */
void PhysicsSystem::Update(float deltaTime) {
  physicsSystem.Update(deltaTime, 1, tempAllocator, jobSystem);

  JPH::BodyInterface &bodyInterface = physicsSystem.GetBodyInterface();

  auto syncTransform = [&](const JPH::BodyID &id,
                           NNE::Component::TransformComponent *transform) {
    JPH::RVec3 pos = bodyInterface.GetPosition(id);
    JPH::Quat rot = bodyInterface.GetRotation(id);
    transform->position = ToEnginePosition(pos);
    transform->rotation = ToEngineRotation(rot);
  };

  for (auto *rb : rigidbodies) {
    if (!rb->GetBodyID().IsInvalid()) {
      auto *transform =
          rb->GetEntity()->GetComponent<NNE::Component::TransformComponent>();
      syncTransform(rb->GetBodyID(), transform);
    }
  }

  for (auto *collider : colliders) {
    if (collider->GetEntity()
            ->GetComponent<NNE::Component::Physics::RigidbodyComponent>())
      continue;
    if (!collider->GetBodyID().IsInvalid()) {
      auto *transform =
          collider->GetEntity()
              ->GetComponent<NNE::Component::TransformComponent>();
      syncTransform(collider->GetBodyID(), transform);
    }
  }
}

/**
 * <summary>
 * Termine les traitements physiques après l'Update principal.
 * </summary>
 */
void PhysicsSystem::LateUpdate(float deltaTime) { (void)deltaTime; }

/**
 * <summary>
 * Enregistre les composants physiques pour la simulation.
 * </summary>
 */
void PhysicsSystem::RegisterComponent(NNE::Component::AComponent *component) {
  if (auto *collider =
          dynamic_cast<NNE::Component::Physics::ColliderComponent *>(
              component)) {
    colliders.push_back(collider);
  }
  if (auto *rb = dynamic_cast<NNE::Component::Physics::RigidbodyComponent *>(
          component)) {
    rigidbodies.push_back(rb);
  }
}

void PhysicsSystem::UnregisterComponent(NNE::Component::AComponent *component) {
  if (auto *collider =
          dynamic_cast<NNE::Component::Physics::ColliderComponent *>(component)) {
    colliders.erase(
        std::remove(colliders.begin(), colliders.end(), collider),
        colliders.end());
  }
  if (auto *rb = dynamic_cast<NNE::Component::Physics::RigidbodyComponent *>(
          component)) {
    rigidbodies.erase(
        std::remove(rigidbodies.begin(), rigidbodies.end(), rb),
        rigidbodies.end());
  }
}

bool PhysicsSystem::Raycast(glm::vec3 origin, glm::vec3 direction, float distance,
                            RaycastHit &outHit, JPH::ObjectLayer rayLayer) {
    auto* system = NNE::Systems::PhysicsSystem::GetInstance();
    if (!system)
        return false;
    JPH::PhysicsSystem& phys = system->physicsSystem;

    class RaycastLayerFilter final : public JPH::ObjectLayerFilter {
    public:
        explicit RaycastLayerFilter(JPH::ObjectLayer layer) : mLayer(layer) {}
        bool ShouldCollide(JPH::ObjectLayer other) const override {
            auto* phys = NNE::Systems::PhysicsSystem::GetInstance();
            return phys->LayersShouldCollide(mLayer, other);
        }
    private:
        JPH::ObjectLayer mLayer;
    };

    JPH::RRayCast ray({ origin.x, origin.y, origin.z },
        JPH::Vec3(direction.x, direction.y, direction.z) * distance);
    JPH::RayCastResult result;
    JPH::BroadPhaseLayerFilter broadPhaseFilter;
    RaycastLayerFilter objectLayerFilter(rayLayer);
    JPH::BodyFilter bodyFilter;
    if (!phys.GetNarrowPhaseQuery().CastRay(
        ray, result, broadPhaseFilter, objectLayerFilter, bodyFilter))
        return false;

    outHit.bodyID = result.mBodyID;
    outHit.subShapeID = result.mSubShapeID2;
    outHit.fraction = result.mFraction;
    if (auto* col = system->GetCollider(result.mBodyID))
        outHit.entity = col->GetEntity();
    else
        outHit.entity = nullptr;

    JPH::RVec3 point = ray.GetPointOnRay(result.mFraction);
    outHit.position = glm::vec3(point.GetX(), point.GetY(), point.GetZ());

    JPH::BodyLockRead lock(phys.GetBodyLockInterface(), result.mBodyID);
    if (lock.Succeeded()) {
        const JPH::Body& body = lock.GetBody();
        JPH::Vec3 normal = body.GetWorldSpaceSurfaceNormal(result.mSubShapeID2, point);
        outHit.normal = glm::vec3(normal.GetX(), normal.GetY(), normal.GetZ());
    }
    return true;
}

/**
 * <summary>
 * Gère la réaction lors de l'apparition d'un contact.
 * </summary>
 */
void PhysicsSystem::ContactListenerImpl::OnContactAdded(
    const JPH::Body &body1, const JPH::Body &body2,
    const JPH::ContactManifold &manifold, JPH::ContactSettings &) {
  auto *colliderA =
      NNE::Systems::PhysicsSystem::GetInstance()->GetCollider(body1.GetID());
  auto *colliderB =
      NNE::Systems::PhysicsSystem::GetInstance()->GetCollider(body2.GetID());

  if (colliderA && colliderB) {
    if (colliderA->IsTrigger() || colliderB->IsTrigger()) {
      if (colliderA->IsTrigger())
        colliderA->OnTriggerHit(colliderB);
      else
        colliderA->OnHit(colliderB);
      if (colliderB->IsTrigger())
        colliderB->OnTriggerHit(colliderA);
      else
        colliderB->OnHit(colliderA);
    } else {
      colliderA->OnHit(colliderB);
      colliderB->OnHit(colliderA);
    }
  }
}

} 
