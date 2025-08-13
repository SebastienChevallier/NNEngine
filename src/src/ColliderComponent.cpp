#include "ColliderComponent.h"
#include "MonoComponent.h"


void NNE::Component::Physics::ColliderComponent::OnHit(ColliderComponent* other)
{
        std::vector<NNE::Component::MonoComponent*> list = _entity->GetComponents<NNE::Component::MonoComponent>();

	if (!list.empty()) {
                for each (NNE::Component::MonoComponent * comp in list)
                {
                        comp->OnHit(other);
                }
	}
	
}

void NNE::Component::Physics::ColliderComponent::OnTriggerHit(ColliderComponent* other)
{
        std::vector<NNE::Component::MonoComponent*> list = _entity->GetComponents<NNE::Component::MonoComponent>();

	if (!list.empty()) {
                for each (NNE::Component::MonoComponent * comp in list)
                {
                        comp->OnTriggerHit(other);
                }
	}
}
