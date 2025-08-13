#include "PhysicsManager.h"
#include "Application.h"
#include "ColliderComponent.h"

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

PhysicsManager::PhysicsManager()
    : tempAllocator(nullptr), jobSystem(nullptr)
{
    JPH::RegisterDefaultAllocator();
    JPH::Factory::sInstance = new JPH::Factory();
    JPH::RegisterTypes();

    tempAllocator = new JPH::TempAllocatorImpl(10 * 1024 * 1024);
    jobSystem = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, std::thread::hardware_concurrency() - 1);
}

void PhysicsManager::Initialize() {
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

void PhysicsManager::Update(float deltaTime) {
    physicsSystem.Update(deltaTime, 1, tempAllocator, jobSystem);
}

PhysicsManager::~PhysicsManager() {
    delete JPH::Factory::sInstance;
    JPH::Factory::sInstance = nullptr;
}

JPH::PhysicsSystem* PhysicsManager::GetPhysicsSystem() {
    return &physicsSystem;
}

void PhysicsManager::ContactListenerImpl::OnContactAdded(const JPH::Body& body1, const JPH::Body& body2, const JPH::ContactManifold& manifold, JPH::ContactSettings&)
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
