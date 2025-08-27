#include "BoxColliderComponent.h"
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyInterface.h>

#include "PhysicsSystem.h"
#include "Application.h"

/**
 * <summary>
 * Initialise un collider boîte avec la taille spécifiée.
 * </summary>
 */
NNE::Component::Physics::BoxColliderComponent::BoxColliderComponent(const glm::vec3& size) : size(size)
{
}

/**
 * <summary>
 * Crée la forme lors de l'activation du composant.
 * </summary>
 */
void NNE::Component::Physics::BoxColliderComponent::Awake()
{
        CreateShape();
}

/**
 * <summary>
 * Construit et enregistre la forme physique de la boîte.
 * </summary>
 */
void NNE::Component::Physics::BoxColliderComponent::CreateShape()
{
        shape = new JPH::BoxShape(JPH::Vec3(size.x, size.y, size.z));

        JPH::BodyCreationSettings bodySettings(shape, JPH::RVec3::sZero(), JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic, 0);
        auto& bodyInterface = NNE::Systems::Application::GetInstance()->physicsSystem->GetPhysicsSystem()->GetBodyInterface();
        bodyID = bodyInterface.CreateAndAddBody(bodySettings, JPH::EActivation::Activate);

        NNE::Systems::Application::GetInstance()->RegisterCollider(bodyID, this);
}
