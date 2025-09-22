#include "RigidbodyComponent.h"
#include "TransformComponent.h"

#include <Jolt/Jolt.h>

#include "PhysicsSystem.h"
#include "AEntity.h"
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Body/MassProperties.h>
#include <Jolt/Physics/Body/MotionProperties.h>
#include <glm/gtc/quaternion.hpp>
#include <imgui.h>
#include <algorithm>
#include <limits>
#include <cmath>
#include <iostream>


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
      lockRotation(lockRotation),
      lastPosition(0.0f),
      lastRotation(0.0f) {
}

/**
 * <summary>
 * Supprime le corps physique lors de la destruction.
 * </summary>
 */
RigidbodyComponent::~RigidbodyComponent() {
    if (auto* system = NNE::Systems::PhysicsSystem::GetInstance()) {
        if (!bodyID.IsInvalid()) {
            auto* physicsSystem = system->GetPhysicsSystem();
            physicsSystem->GetBodyInterface().RemoveBody(bodyID);
            system->UnregisterCollider(bodyID);
            bodyID = JPH::BodyID();
        }
        system->UnregisterComponent(this);
    }
}

/**
 * <summary>
 * Crée le corps physique et l'ajoute au monde.
 * </summary>
 */
void RigidbodyComponent::Awake() {
    auto physicsSystem = NNE::Systems::PhysicsSystem::GetInstance()->GetPhysicsSystem();
    auto const* transform = GetEntity()->GetComponent<NNE::Component::TransformComponent>();
    if (transform) {
        lastPosition = transform->position;
        lastRotation = transform->rotation;
    }
    auto* collider = GetEntity()->GetComponent<NNE::Component::Physics::ColliderComponent>();

    if (!collider)
        return;

    if (!collider->GetShape()) {
        collider->Awake();
        if (!collider->GetShape())
            return;
    }

    if (collider->IsTrigger()) {
        std::cerr << "Collider on entity '" << GetEntity()->GetName()

                  << "' is marked as trigger; forcing IsTrigger to false for physical collisions." << std::endl;
        collider->SetTrigger(false);

    }

    JPH::EMotionType motionType = isKinematic ? JPH::EMotionType::Kinematic
        : JPH::EMotionType::Dynamic;

    //JPH::EMotionType motionType = JPH::EMotionType::Dynamic;


    JPH::BodyCreationSettings bodySettings(
        collider->GetShape(),
        JPH::RVec3(transform->position.x, transform->position.y, transform->position.z),
        JPH::Quat::sIdentity(),
        motionType,
        collider->GetLayer());
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
        JPH::MassProperties mp = collider->GetShape()->GetMassProperties();
        mp.ScaleToMass(mass);
        bodySettings.mMassPropertiesOverride = mp;
        bodySettings.mOverrideMassProperties = JPH::EOverrideMassProperties::MassAndInertiaProvided;
        bodySettings.mMotionQuality = JPH::EMotionQuality::LinearCast;
    }

    if (isKinematic) {
        bodySettings.mOverrideMassProperties = JPH::EOverrideMassProperties::MassAndInertiaProvided;
        bodySettings.mMassPropertiesOverride.mMass = 1.0f;
        bodySettings.mMassPropertiesOverride.mInertia = JPH::Mat44::sIdentity();
        bodySettings.mGravityFactor = 0.0f;
        bodySettings.mUseManifoldReduction = false; // Important pour les kinematic
        bodySettings.mMotionQuality = JPH::EMotionQuality::LinearCast;
    }

    JPH::BodyInterface& bodyInterface = physicsSystem->GetBodyInterface();
    bodyID = bodyInterface.CreateAndAddBody(bodySettings, JPH::EActivation::Activate);
    collider->bodyID = bodyID;
    NNE::Systems::PhysicsSystem::GetInstance()->RegisterCollider(bodyID, collider);
}

/**
 * <summary>
 * Met à jour l'état physique si nécessaire.
 * </summary>
 */
void RigidbodyComponent::Update(float deltaTime) {
    if (!isKinematic)
        return;

    auto* transform = GetEntity()->GetComponent<NNE::Component::TransformComponent>();
    if (transform && (transform->position != lastPosition || transform->rotation != lastRotation)) {
        MoveKinematic(transform->position, transform->rotation, deltaTime);
        lastPosition = transform->position;
        lastRotation = transform->rotation;
    }
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

    auto physicsSystem = NNE::Systems::PhysicsSystem::GetInstance()->GetPhysicsSystem();
    auto& bodyInterface = physicsSystem->GetBodyInterface();
    if (!bodyID.IsInvalid()) {
        bodyInterface.SetLinearVelocity(bodyID, JPH::RVec3(velocity.x, velocity.y, velocity.z));
    }
}

void RigidbodyComponent::ApplyForce(glm::vec3 force, float deltaTime) {
    auto physicsSystem = NNE::Systems::PhysicsSystem::GetInstance()->GetPhysicsSystem();
    auto& bodyInterface = physicsSystem->GetBodyInterface();
    if (!bodyID.IsInvalid()) {
        // Jolt expects a force vector; scale by the duration to apply the impulse
        JPH::Vec3 joltForce(force.x, force.y, force.z);
        bodyInterface.AddForce(bodyID, joltForce);
    }
}

void RigidbodyComponent::ApplyImpulse(glm::vec3 impulse) {
    auto physicsSystem = NNE::Systems::PhysicsSystem::GetInstance()->GetPhysicsSystem();
    auto& bodyInterface = physicsSystem->GetBodyInterface();
    if (!bodyID.IsInvalid()) {
        JPH::Vec3 joltImpulse(impulse.x, impulse.y, impulse.z);
        bodyInterface.AddImpulse(bodyID, joltImpulse);
    }
}

/**
 * <summary>
 * Déplace un corps cinématique vers une nouvelle position.
 * </summary>
 */

void RigidbodyComponent::MoveKinematic(glm::vec3 position, glm::vec3 rotation, float deltaTime) {

    if (!isKinematic)
        return;

    auto physicsSystem = NNE::Systems::PhysicsSystem::GetInstance()->GetPhysicsSystem();
    auto& bodyInterface = physicsSystem->GetBodyInterface();
    if (!bodyID.IsInvalid()) {
        glm::vec3 radians = glm::radians(rotation);
        glm::quat q = glm::quat(radians);
        JPH::Quat orient(q.x, q.y, q.z, q.w);
        bodyInterface.MoveKinematic(bodyID,
                                    JPH::RVec3(position.x, position.y, position.z),
                                    orient,
                                    deltaTime);
    }
}

/**
 * <summary>
 * Retourne la vitesse linéaire actuelle du corps.
 * </summary>
 */
glm::vec3 RigidbodyComponent::GetLinearVelocity() const {
    auto physicsSystem = NNE::Systems::PhysicsSystem::GetInstance()->GetPhysicsSystem();
    auto& bodyInterface = physicsSystem->GetBodyInterface();
    if (!bodyID.IsInvalid()) {
        JPH::RVec3 velocity = bodyInterface.GetLinearVelocity(bodyID);
        return glm::vec3(velocity.GetX(), velocity.GetY(), velocity.GetZ());
    }
    return glm::vec3();
}

void RigidbodyComponent::DrawImGui() {
    ImGui::TextUnformatted("Rigidbody");
    ImGui::Separator();

    bool changed = false;

    float newMass = mass;
    if (ImGui::DragFloat("Mass", &newMass, 0.1f, 0.0f, 1000.0f)) {
        newMass = std::max(newMass, 0.0f);
        if (std::fabs(newMass - mass) > std::numeric_limits<float>::epsilon()) {
            mass = newMass;
            changed = true;
        }
    }

    bool kinematic = isKinematic;
    if (ImGui::Checkbox("Kinematic", &kinematic)) {
        isKinematic = kinematic;
        changed = true;
    }

    bool lockPosX = lockPosition.x;
    bool lockPosY = lockPosition.y;
    bool lockPosZ = lockPosition.z;
    if (ImGui::Checkbox("Lock Pos X", &lockPosX)) { lockPosition.x = lockPosX; changed = true; }
    ImGui::SameLine();
    if (ImGui::Checkbox("Lock Pos Y", &lockPosY)) { lockPosition.y = lockPosY; changed = true; }
    ImGui::SameLine();
    if (ImGui::Checkbox("Lock Pos Z", &lockPosZ)) { lockPosition.z = lockPosZ; changed = true; }

    bool lockRotX = lockRotation.x;
    bool lockRotY = lockRotation.y;
    bool lockRotZ = lockRotation.z;
    if (ImGui::Checkbox("Lock Rot X", &lockRotX)) { lockRotation.x = lockRotX; changed = true; }
    ImGui::SameLine();
    if (ImGui::Checkbox("Lock Rot Y", &lockRotY)) { lockRotation.y = lockRotY; changed = true; }
    ImGui::SameLine();
    if (ImGui::Checkbox("Lock Rot Z", &lockRotZ)) { lockRotation.z = lockRotZ; changed = true; }

    glm::vec3 velocity = GetLinearVelocity();
    ImGui::Text("Velocity: %.2f %.2f %.2f", velocity.x, velocity.y, velocity.z);
    if (ImGui::Button("Reset Velocity")) {
        SetLinearVelocity(glm::vec3(0.0f));
    }

    if (changed) {
        RecreateBody();
    }
}

void RigidbodyComponent::RecreateBody() {
    auto* system = NNE::Systems::PhysicsSystem::GetInstance();
    if (!system)
        return;

    auto* physicsSystem = system->GetPhysicsSystem();
    if (!physicsSystem)
        return;

    auto& bodyInterface = physicsSystem->GetBodyInterface();
    if (!bodyID.IsInvalid()) {
        bodyInterface.RemoveBody(bodyID);
        bodyInterface.DestroyBody(bodyID);
        system->UnregisterCollider(bodyID);
        bodyID = JPH::BodyID();
    }

    Awake();
}

} // namespace NNE::Component::Physics
