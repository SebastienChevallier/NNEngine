#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/RegisterTypes.h>

namespace NNE {

    class PhysicsManager {
    private:
        JPH::PhysicsSystem physicsSystem;
        JPH::TempAllocatorImpl* tempAllocator;
        JPH::JobSystemThreadPool* jobSystem;

    public:
        PhysicsManager();
        ~PhysicsManager();

        void Initialize();
        void Update(float deltaTime);
        JPH::PhysicsSystem* GetPhysicsSystem();
    };

}