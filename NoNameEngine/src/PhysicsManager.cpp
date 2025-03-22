#include "PhysicsManager.h"


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

NNE::PhysicsManager::PhysicsManager()
    : tempAllocator(nullptr), jobSystem(nullptr) // Initialisation temporaire et neutre
{
    // Initialisation indispensable AVANT toute utilisation des objets internes Jolt :
    JPH::RegisterDefaultAllocator();
    JPH::Factory::sInstance = new JPH::Factory();
    JPH::RegisterTypes();

    // Initialisation correcte APRÈS :
    tempAllocator = new JPH::TempAllocatorImpl(10 * 1024 * 1024);
    jobSystem = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, std::thread::hardware_concurrency() - 1);
}

void NNE::PhysicsManager::Initialize() {
    static SimpleBroadPhaseLayerInterface broadPhaseLayerInterface;
    static SimpleObjectVsBroadPhaseLayerFilter broadPhaseFilter;
    static SimpleObjectLayerPairFilter objectLayerFilter;

    physicsSystem.Init(
        1024, 0, 1024, 1024,
        broadPhaseLayerInterface,
        broadPhaseFilter,
        objectLayerFilter
    );
}

void NNE::PhysicsManager::Update(float deltaTime) {
    physicsSystem.Update(deltaTime, 1, tempAllocator, jobSystem);
}

NNE::PhysicsManager::~PhysicsManager() {
    delete JPH::Factory::sInstance;
    JPH::Factory::sInstance = nullptr;
}

JPH::PhysicsSystem* NNE::PhysicsManager::GetPhysicsSystem() {
    return &physicsSystem;
}
