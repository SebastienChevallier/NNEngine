#include "RigidbodyComponent.h"
#include "Application.h"
#include "TransformComponent.h"
#include <Jolt/Physics/Body/BodyCreationSettings.h>

namespace NNE::Component::Physics {

RigidbodyComponent::RigidbodyComponent(float mass, bool kinematic)
    : bodyID(), mass(mass), isKinematic(kinematic) {
}

RigidbodyComponent::~RigidbodyComponent() {
    auto physicsSystem = NNE::Systems::Application::GetInstance()->physicsSystem->GetPhysicsSystem();
    if (!bodyID.IsInvalid()) {
        physicsSystem->GetBodyInterface().RemoveBody(bodyID);
    }
}

void RigidbodyComponent::Awake() {
    auto physicsSystem = NNE::Systems::Application::GetInstance()->physicsSystem->GetPhysicsSystem();
    auto* transform = GetEntity()->GetComponent<NNE::Component::TransformComponent>();
    auto* collider = GetEntity()->GetComponent<NNE::Component::Physics::ColliderComponent>();

    if (!collider || !collider->GetShape()) {
        return;
    }

    JPH::BodyCreationSettings bodySettings(
        collider->GetShape(),
        JPH::RVec3(transform->position.x, transform->position.y, transform->position.z),
        JPH::Quat::sIdentity(),
        (mass > 0.0f) ? JPH::EMotionType::Dynamic : (isKinematic ? JPH::EMotionType::Kinematic : JPH::EMotionType::Dynamic),
        0);

    if (mass > 0.0f) {
        bodySettings.mMassPropertiesOverride.mMass = mass;
    }

    JPH::BodyInterface& bodyInterface = physicsSystem->GetBodyInterface();
    bodyID = bodyInterface.CreateAndAddBody(bodySettings, JPH::EActivation::Activate);
}

void RigidbodyComponent::Update(float deltaTime) {
    (void)deltaTime;
}

JPH::BodyID RigidbodyComponent::GetBodyID() const {
    return bodyID;
}

void RigidbodyComponent::SetLinearVelocity(glm::vec3 velocity) {
    auto physicsSystem = NNE::Systems::Application::GetInstance()->physicsSystem->GetPhysicsSystem();
    auto& bodyInterface = physicsSystem->GetBodyInterface();
    if (!bodyID.IsInvalid()) {
        bodyInterface.SetLinearVelocity(bodyID, JPH::RVec3(velocity.x, velocity.y, velocity.z));
    }
}

glm::vec3 RigidbodyComponent::GetLinearVelocity() const {
    auto physicsSystem = NNE::Systems::Application::GetInstance()->physicsSystem->GetPhysicsSystem();
    auto& bodyInterface = physicsSystem->GetBodyInterface();
    if (!bodyID.IsInvalid()) {
        JPH::RVec3 velocity = bodyInterface.GetLinearVelocity(bodyID);
        return glm::vec3(velocity.GetX(), velocity.GetY(), velocity.GetZ());
    }
    return glm::vec3();
}

} // namespace NNE::Component::Physics
