#pragma once

#include "AComponent.h"
#include "ColliderComponent.h"
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/Body.h>
#include <Jolt/Physics/Body/BodyID.h>

namespace NNE {

    class RigidbodyComponent : public AComponent {
    private:
        JPH::BodyID bodyID;
        float mass;
        bool isKinematic;

    public:
        RigidbodyComponent(float mass = 1.0f, bool kinematic = false);
        ~RigidbodyComponent();

        void Awake() override;
        void Update(float deltaTime) override;
        JPH::BodyID GetBodyID() const;
    };

}