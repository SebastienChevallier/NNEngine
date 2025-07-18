#include "AComponent.h"
#include <Application.h>

NNE::AComponent::AComponent()
{
	_id = NNE::Application::GetInstance()->GenerateID();
}

void NNE::AComponent::Awake()
{
}

void NNE::AComponent::Start()
{
}

void NNE::AComponent::Update(float deltaTime)
{
}

void NNE::AComponent::LateUpdate(float deltaTime)
{
}

int NNE::AComponent::GetID()
{
	return _id;
}

NNE::AEntity* NNE::AComponent::GetEntity()
{
	return _entity;
}

void NNE::AComponent::SetEntity(AEntity* entity)
{
	_entity = entity;
}
