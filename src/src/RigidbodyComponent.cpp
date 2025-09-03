#include "RigidbodyComponent.h"
#include "TransformComponent.h"

#include <Jolt/Jolt.h>

#include "PhysicsSystem.h"
#include "Application.h"
#include "AEntity.h"
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Body/MassProperties.h>


namespace NNE::Component::Physics {

/**
 * <summary>
 * Instancie un corps rigide avec masse et type kinematic.
 * </summary>
 */
RigidbodyComponent::RigidbodyComponent(float mass,
                                       bool kinematic,
                                       glm::bvec3 lockPosition,
                                       glm::bvec3 lockRotation)
    : bodyID(),
      mass(mass),
      isKinematic(kinematic),
      lockPosition(lockPosition),
      lockRotation(lockRotation) {
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
    auto const* transform = GetEntity()->GetComponent<NNE::Component::TransformComponent>();
    auto* collider = GetEntity()->GetComponent<NNE::Component::Physics::ColliderComponent>();

    if (!collider)
        return;

    if (!collider->GetShape()) {
        collider->CreateShape();
        if (!collider->GetShape())
            return;
    }

    JPH::EMotionType motionType = isKinematic ? JPH::EMotionType::Kinematic
        : JPH::EMotionType::Dynamic;


    JPH::BodyCreationSettings bodySettings(
        collider->GetShape(),
        JPH::RVec3(transform->position.x, transform->position.y, transform->position.z),
        JPH::Quat::sIdentity(),
        motionType,
        0);
    bodySettings.mIsSensor = collider->IsTrigger();

    JPH::EAllowedDOFs allowed = JPH::EAllowedDOFs::All;
    if (lockPosition.x) allowed = allowed & ~JPH::EAllowedDOFs::TranslationX;
    if (lockPosition.y) allowed = allowed & ~JPH::EAllowedDOFs::TranslationY;
    if (lockPosition.z) allowed = allowed & ~JPH::EAllowedDOFs::TranslationZ;
    if (lockRotation.x) allowed = allowed & ~JPH::EAllowedDOFs::RotationX;
    if (lockRotation.y) allowed = allowed & ~JPH::EAllowedDOFs::RotationY;
    if (lockRotation.z) allowed = allowed & ~JPH::EAllowedDOFs::RotationZ;
    bodySettings.mAllowedDOFs = allowed;

    if (!isKinematic && mass > 0.0f) {
        bodySettings.mOverrideMassProperties = JPH::EOverrideMassProperties::MassAndInertiaProvided;
        bodySettings.mMassPropertiesOverride.mMass = mass;
        bodySettings.mMassPropertiesOverride.mInertia = JPH::Mat44::sIdentity();
    }

    if (isKinematic) {
        bodySettings.mOverrideMassProperties = JPH::EOverrideMassProperties::MassAndInertiaProvided;
        bodySettings.mMassPropertiesOverride.mMass = 1.0f;
        bodySettings.mMassPropertiesOverride.mInertia = JPH::Mat44::sIdentity();
        bodySettings.mGravityFactor = 0.0f;
    }

    JPH::BodyInterface& bodyInterface = physicsSystem->GetBodyInterface();
    bodyID = bodyInterface.CreateAndAddBody(bodySettings, JPH::EActivation::Activate);
    collider->bodyID = bodyID;
    NNE::Systems::Application::GetInstance()->RegisterCollider(bodyID, collider);
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
