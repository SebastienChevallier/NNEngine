#include "ColliderComponent.h"


void NNE::ColliderComponent::OnHit(ColliderComponent* other)
{
	std::vector<MonoComponent*> list = _entity->GetComponents<MonoComponent>();

	if (!list.empty()) {
		for each (MonoComponent * comp in list)
		{
			comp->OnHit(other);
		}
	}
	
}

void NNE::ColliderComponent::OnTriggerHit(ColliderComponent* other)
{
	std::vector<MonoComponent*> list = _entity->GetComponents<MonoComponent>();

	if (!list.empty()) {
		for each (MonoComponent * comp in list)
		{
			comp->OnTriggerHit(other);
		}
	}
}
