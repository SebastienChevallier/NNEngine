#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include <Jolt/Jolt.h>
#include "PhysicsSystem.h"
#include "Application.h"
#include "AEntity.h"
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyInterface.h>

namespace NNE::Component::Physics {

/**
 * <summary>
 * Instancie un corps rigide avec masse et type kinematic.
 * </summary>
 */
RigidbodyComponent::RigidbodyComponent(float mass, bool kinematic)
    : bodyID(), mass(mass), isKinematic(kinematic) {
}

/**
 * <summary>
 * Supprime le corps physique lors de la destruction.
 * </summary>
 */
RigidbodyComponent::~RigidbodyComponent() {
    auto physicsSystem = NNE::Systems::Application::GetInstance()->physicsSystem->GetPhysicsSystem();
    if (!bodyID.IsInvalid()) {
        physicsSystem->GetBodyInterface().RemoveBody(bodyID);
    }
}

/**
 * <summary>
 * Crée le corps physique et l'ajoute au monde.
 * </summary>
 */
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

/**
 * <summary>
 * Met à jour l'état physique si nécessaire.
 * </summary>
 */
void RigidbodyComponent::Update(float deltaTime) {
    (void)deltaTime;
}

/**
 * <summary>
 * Obtient l'identifiant du corps rigide.
 * </summary>
 */
JPH::BodyID RigidbodyComponent::GetBodyID() const {
    return bodyID;
}

/**
 * <summary>
 * Applique une vitesse linéaire au corps.
 * </summary>
 */
void RigidbodyComponent::SetLinearVelocity(glm::vec3 velocity) {
    auto physicsSystem = NNE::Systems::Application::GetInstance()->physicsSystem->GetPhysicsSystem();
    auto& bodyInterface = physicsSystem->GetBodyInterface();
    if (!bodyID.IsInvalid()) {
        bodyInterface.SetLinearVelocity(bodyID, JPH::RVec3(velocity.x, velocity.y, velocity.z));
    }
}

/**
 * <summary>
 * Retourne la vitesse linéaire actuelle du corps.
 * </summary>
 */
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
