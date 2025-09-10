#include "PlaneCollider.h"
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/PlaneShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Body/MassProperties.h>

#include "PhysicsSystem.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "AEntity.h"

/**
 * <summary>
 * Initialise un plan collision avec une normale et une distance.
 * </summary>
 */
NNE::Component::Physics::PlaneCollider::PlaneCollider(const glm::vec3& normal, float distance, bool isTrigger)
    : ColliderComponent(isTrigger)
{
        plane = JPH::Plane(JPH::Vec3(normal.x, normal.y, normal.z), distance);
}

/**
 * <summary>
 * Prépare le collider lors de l'initialisation du composant.
 * </summary>
 */
void NNE::Component::Physics::PlaneCollider::Awake()
{
        if (!shape)
                CreateShape();
}

/**
 * <summary>
 * Crée l'objet shape représentant le plan.
 * </summary>
 */
void NNE::Component::Physics::PlaneCollider::CreateShape()
{
        shape = new JPH::PlaneShape(plane);

        if (!_entity->GetComponent<NNE::Component::Physics::RigidbodyComponent>()) {
                auto* transform = _entity->GetComponent<NNE::Component::TransformComponent>();
                JPH::RVec3 position = JPH::RVec3::sZero();
                if (transform) {
                        position = JPH::RVec3(transform->position.x, transform->position.y, transform->position.z);
                }

                JPH::BodyCreationSettings bodySettings(shape, position, JPH::Quat::sIdentity(), JPH::EMotionType::Static, GetLayer());
                bodySettings.mIsSensor = IsTrigger();

                bodySettings.mOverrideMassProperties =
                    JPH::EOverrideMassProperties::MassAndInertiaProvided;
                
                bodySettings.mMassPropertiesOverride.mMass = 1.0f;
                bodySettings.mMassPropertiesOverride.mInertia =
                    JPH::Mat44::sIdentity();

                auto& bodyInterface = NNE::Systems::PhysicsSystem::GetInstance()->GetPhysicsSystem()->GetBodyInterface();
                bodyID = bodyInterface.CreateAndAddBody(bodySettings, JPH::EActivation::Activate);

                NNE::Systems::PhysicsSystem::GetInstance()->RegisterCollider(bodyID, this);
        }
}
