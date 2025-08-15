#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/RegisterTypes.h>
#include "ISystem.h"

namespace NNE::Systems {

    class PhysicsManager : public ISystem {
    private:
        JPH::PhysicsSystem physicsSystem;
        JPH::TempAllocatorImpl* tempAllocator;
        JPH::JobSystemThreadPool* jobSystem;

    public:
        PhysicsManager();
        ~PhysicsManager();

        void Initialize();
        void Update(float deltaTime) override;
        void LateUpdate(float deltaTime) override;
        void Awake() override;
        void Start() override;
        void RegisterComponent(NNE::Component::AComponent* component) override;
        JPH::PhysicsSystem* GetPhysicsSystem();

        class ContactListenerImpl : public JPH::ContactListener
        {
        public:
            void OnContactAdded(const JPH::Body& body1, const JPH::Body& body2, const JPH::ContactManifold& manifold, JPH::ContactSettings&) override;
        };

        ContactListenerImpl contactListener;
    };

}
