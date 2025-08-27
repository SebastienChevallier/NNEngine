#include "PhysicsSystem.h"
#include "Application.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"

#include "AEntity.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

class SimpleBroadPhaseLayerInterface final : public JPH::BroadPhaseLayerInterface {
public:
    JPH::uint GetNumBroadPhaseLayers() const override { return 1; }
    JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer) const override { return JPH::BroadPhaseLayer(0); }
};

class SimpleObjectVsBroadPhaseLayerFilter final : public JPH::ObjectVsBroadPhaseLayerFilter {
public:
    bool ShouldCollide(JPH::ObjectLayer, JPH::BroadPhaseLayer) const override { return true; }
};

class SimpleObjectLayerPairFilter final : public JPH::ObjectLayerPairFilter {
public:
    bool ShouldCollide(JPH::ObjectLayer, JPH::ObjectLayer) const override { return true; }
};

namespace NNE::Systems {

/**
 * <summary>
 * Configure les allocations et enregistre les types Jolt.
 * </summary>
 */
PhysicsSystem::PhysicsSystem()
    : tempAllocator(nullptr), jobSystem(nullptr)
{
    JPH::RegisterDefaultAllocator();
    JPH::Factory::sInstance = new JPH::Factory();
    JPH::RegisterTypes();

    tempAllocator = new JPH::TempAllocatorImpl(10 * 1024 * 1024);
    jobSystem = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, std::thread::hardware_concurrency() - 1);
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

    physicsSystem.Init(
        1024, 0, 1024, 1024,
        broadPhaseLayerInterface,
        broadPhaseFilter,
        objectLayerFilter
    );

    physicsSystem.SetContactListener(&contactListener);
}

/**
 * <summary>
 * Nettoie les ressources allouées par Jolt.
 * </summary>
 */
PhysicsSystem::~PhysicsSystem() {
    delete JPH::Factory::sInstance;
    JPH::Factory::sInstance = nullptr;
}

/**
 * <summary>
 * Fournit un accès au système physique Jolt.
 * </summary>
 */
JPH::PhysicsSystem* PhysicsSystem::GetPhysicsSystem() {
    return &physicsSystem;
}

/**
 * <summary>
 * Prépare le système physique avant utilisation.
 * </summary>
 */
void PhysicsSystem::Awake()
{
    Initialize();
}

/**
 * <summary>
 * Démarre le système physique.
 * </summary>
 */
void PhysicsSystem::Start()
{
}

/**
 * <summary>
 * Avance la simulation physique et synchronise les entités.
 * </summary>
 */
void PhysicsSystem::Update(float deltaTime)
{
    physicsSystem.Update(deltaTime, 1, tempAllocator, jobSystem);

    JPH::BodyInterface& bodyInterface = physicsSystem.GetBodyInterface();
    for (auto* rb : rigidbodies)
    {
        if (!rb->GetBodyID().IsInvalid())
        {
            auto* transform = rb->GetEntity()->GetComponent<NNE::Component::TransformComponent>();
            JPH::RVec3 pos = bodyInterface.GetPosition(rb->GetBodyID());
            JPH::Quat rot = bodyInterface.GetRotation(rb->GetBodyID());
            transform->position = glm::vec3(pos.GetX(), pos.GetY(), pos.GetZ());
            glm::quat glmQuat(rot.GetW(), rot.GetX(), rot.GetY(), rot.GetZ());
            transform->rotation = glm::degrees(glm::eulerAngles(glmQuat));
        }
    }

    for (auto* collider : colliders)
    {
        if (collider->GetEntity()->GetComponent<NNE::Component::Physics::RigidbodyComponent>())
            continue;
        if (!collider->GetBodyID().IsInvalid())
        {
            auto* transform = collider->GetEntity()->GetComponent<NNE::Component::TransformComponent>();
            JPH::RVec3 pos = bodyInterface.GetPosition(collider->GetBodyID());
            JPH::Quat rot = bodyInterface.GetRotation(collider->GetBodyID());
            transform->position = glm::vec3(pos.GetX(), pos.GetY(), pos.GetZ());
            glm::quat glmQuat(rot.GetW(), rot.GetX(), rot.GetY(), rot.GetZ());
            transform->rotation = glm::degrees(glm::eulerAngles(glmQuat));
        }
    }
}

/**
 * <summary>
 * Termine les traitements physiques après l'Update principal.
 * </summary>
 */
void PhysicsSystem::LateUpdate(float deltaTime)
{
    (void)deltaTime;
}

/**
 * <summary>
 * Enregistre les composants physiques pour la simulation.
 * </summary>
 */
void PhysicsSystem::RegisterComponent(NNE::Component::AComponent* component)
{
    if (auto* collider = dynamic_cast<NNE::Component::Physics::ColliderComponent*>(component))
    {
        colliders.push_back(collider);
    }
    if (auto* rb = dynamic_cast<NNE::Component::Physics::RigidbodyComponent*>(component))
    {
        rigidbodies.push_back(rb);
    }
}

/**
 * <summary>
 * Gère la réaction lors de l'apparition d'un contact.
 * </summary>
 */
void PhysicsSystem::ContactListenerImpl::OnContactAdded(const JPH::Body& body1, const JPH::Body& body2, const JPH::ContactManifold& manifold, JPH::ContactSettings&)
{
    auto* colliderA = NNE::Systems::Application::GetInstance()->GetCollider(body1.GetID());
    auto* colliderB = NNE::Systems::Application::GetInstance()->GetCollider(body2.GetID());

    if (colliderA && colliderB)
    {
        colliderA->OnHit(colliderB);
        colliderB->OnHit(colliderA);
    }
}

} // namespace NNE::Systems
