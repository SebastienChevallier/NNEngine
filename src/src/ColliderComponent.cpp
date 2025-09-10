#include "ColliderComponent.h"
#include "MonoComponent.h"
#include "AEntity.h"
#include "PhysicsSystem.h"
#include "RigidbodyComponent.h"
#include <vector>
#include <Jolt/Physics/Body/BodyInterface.h>

NNE::Component::Physics::ColliderComponent::~ColliderComponent() {
    if (auto* system = NNE::Systems::PhysicsSystem::GetInstance()) {
        // If a rigidbody owns this collider's body, let it handle teardown to
        // avoid removing the same body twice.
        bool hasRigidbody = _entity &&
            _entity->GetComponent<NNE::Component::Physics::RigidbodyComponent>();
        if (!hasRigidbody && !bodyID.IsInvalid()) {
            system->GetPhysicsSystem()->GetBodyInterface().RemoveBody(bodyID);
            system->UnregisterCollider(bodyID);
            bodyID = JPH::BodyID();
        }
        system->UnregisterComponent(this);
    }
}


/**
 * <summary>
 * Notifie les composants mono lors d'une collision physique.
 * </summary>
 */
void NNE::Component::Physics::ColliderComponent::OnHit(ColliderComponent* other)
{
        std::vector<NNE::Component::MonoComponent*> list = _entity->GetComponents<NNE::Component::MonoComponent>();

        if (!list.empty()) {
                for (NNE::Component::MonoComponent* comp : list) {
                        comp->OnHit(other);
                }
        }
	
}

/**
 * <summary>
 * Notifie les composants mono lors d'une collision trigger.
 * </summary>
 */
void NNE::Component::Physics::ColliderComponent::OnTriggerHit(ColliderComponent* other)
{
        std::vector<NNE::Component::MonoComponent*> list = _entity->GetComponents<NNE::Component::MonoComponent>();

        if (!list.empty()) {
                for (NNE::Component::MonoComponent* comp : list) {
                        comp->OnTriggerHit(other);
                }
        }
}
