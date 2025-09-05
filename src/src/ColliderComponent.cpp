#include "ColliderComponent.h"
#include "MonoComponent.h"
#include "AEntity.h"
#include "PhysicsSystem.h"
#include "Application.h"
#include <vector>
#include <Jolt/Physics/Body/BodyInterface.h>

NNE::Component::Physics::ColliderComponent::~ColliderComponent() {
        auto app = NNE::Systems::Application::GetInstance();
        if (!bodyID.IsInvalid()) {
                app->physicsSystem->GetPhysicsSystem()->GetBodyInterface().RemoveBody(bodyID);
                app->UnregisterCollider(bodyID);
                bodyID = JPH::BodyID();
        }
        app->physicsSystem->UnregisterComponent(this);
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
