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

        class ContactListenerImpl : public JPH::ContactListener
        {
        public:
            void OnContactAdded(const JPH::Body& body1, const JPH::Body& body2, const JPH::ContactManifold& manifold, JPH::ContactSettings&) override;
        };

        ContactListenerImpl contactListener;
    };

}