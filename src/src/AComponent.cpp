#include "AComponent.h"
#include "Application.h"

NNE::Component::AComponent::AComponent()
{
        _id = NNE::Systems::Application::GetInstance()->GenerateID();
}

void NNE::Component::AComponent::Awake()
{
}

void NNE::Component::AComponent::Start()
{
}

void NNE::Component::AComponent::Update(float deltaTime)
{
}

void NNE::Component::AComponent::LateUpdate(float deltaTime)
{
}

int NNE::Component::AComponent::GetID()
{
        return _id;
}

NNE::AEntity* NNE::Component::AComponent::GetEntity()
{
        return _entity;
}

void NNE::Component::AComponent::SetEntity(NNE::AEntity* entity)
{
        _entity = entity;
}
