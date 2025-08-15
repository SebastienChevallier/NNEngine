#include "AEntity.h"
#include "Application.h"
#include "MonoComponent.h"


NNE::AEntity::AEntity()
{
        _ID = NNE::Systems::Application::GetInstance()->GenerateID();
        transform = this->AddComponent<NNE::Component::TransformComponent>();
}

NNE::AEntity::~AEntity()
{
        for (NNE::Component::AComponent* comp : NNE::AEntity::components) {
                delete comp;
        }
        components.clear();
}

int NNE::AEntity::GetID()
{
	
	return _ID;
}

void NNE::AEntity::Awake()
{
        if (!components.empty()) {
                for (NNE::Component::AComponent* component : components) {
                        component->Awake();
                }
        }
}

void NNE::AEntity::Start()
{
        if (!components.empty()) {
                for (NNE::Component::AComponent* component : components) {
                        component->Start();
                }
        }
}

void NNE::AEntity::Update(float delta)
{
        if (!components.empty()) {
                for (NNE::Component::AComponent* component : components) {
                        if (!dynamic_cast<NNE::Component::MonoComponent*>(component))
                                component->Update(delta);
                }
        }
}

void NNE::AEntity::LateUpdate(float delta)
{
        if (!components.empty()) {
                for (NNE::Component::AComponent* component : components) {
                        if (!dynamic_cast<NNE::Component::MonoComponent*>(component))
                                component->LateUpdate(delta);
                }
        }
}
