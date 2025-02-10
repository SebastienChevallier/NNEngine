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
