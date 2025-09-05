#include "BoxColliderComponent.h"
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyInterface.h>

#include "PhysicsSystem.h"
#include "Application.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "AEntity.h"

/**
 * <summary>
 * Initialise un collider boîte avec la taille spécifiée.
 * </summary>
 */
NNE::Component::Physics::BoxColliderComponent::BoxColliderComponent(const glm::vec3& size, bool isTrigger)
    : ColliderComponent(isTrigger), size(size)
{}

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

        // Crée un corps statique uniquement si aucun rigidbody n'est associé à l'entité
        if (!_entity->GetComponent<NNE::Component::Physics::RigidbodyComponent>()) {
                auto* transform = _entity->GetComponent<NNE::Component::TransformComponent>();
                JPH::RVec3 position = JPH::RVec3::sZero();
                if (transform) {
                        position = JPH::RVec3(transform->position.x, transform->position.y, transform->position.z);
                }

                JPH::BodyCreationSettings bodySettings(shape, position, JPH::Quat::sIdentity(), JPH::EMotionType::Static, GetLayer());
                bodySettings.mIsSensor = IsTrigger();
                auto& bodyInterface = NNE::Systems::Application::GetInstance()->physicsSystem->GetPhysicsSystem()->GetBodyInterface();
                bodyID = bodyInterface.CreateAndAddBody(bodySettings, JPH::EActivation::Activate);

                NNE::Systems::Application::GetInstance()->RegisterCollider(bodyID, this);
        }
}
