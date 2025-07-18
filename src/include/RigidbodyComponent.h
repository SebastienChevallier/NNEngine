#pragma once

#include "AComponent.h"
#include "ColliderComponent.h"
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/Body.h>
#include <Jolt/Physics/Body/BodyID.h>
#include <glm/glm.hpp>

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

        void SetLinearVelocity(glm::vec3 velocity);
		glm::vec3 GetLinearVelocity() const;
    };

}