#include "AEntity.h"
#include <Application.h>


NNE::AEntity::AEntity()
{
	_ID = NNE::Application::GetInstance()->GenerateID();
	this->AddComponent<TransformComponent>();
}

NNE::AEntity::~AEntity()
{
	for (AComponent* comp : NNE::AEntity::components) {
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
		for (AComponent* component : components) {
			component->Awake();
		}
	}
}

void NNE::AEntity::Start()
{
	if (!components.empty()) {
		for (AComponent* component : components) {
			component->Start();
		}
	}
}

void NNE::AEntity::Update(float delta)
{
	if (!components.empty()) {
		for (AComponent* component : components) {
			component->Update(delta);
		}
	}
}

void NNE::AEntity::LateUpdate(float delta)
{
	if (!components.empty()) {
		for (AComponent* component : components) {
			component->LateUpdate(delta);
		}
	}
}
