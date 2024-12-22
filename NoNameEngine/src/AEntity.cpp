#include "AEntity.h"
#include "Application.h"

NNE::AEntity::AEntity()
{
	_ID = NNE::Application::GetInstance()->GenerateID();
}

NNE::AEntity::~AEntity()
{
}

int NNE::AEntity::GetID()
{
	
	return _ID;
}

void NNE::AEntity::Awake()
{
}

void NNE::AEntity::Start()
{
}

void NNE::AEntity::Update(float delta)
{
}

void NNE::AEntity::LateUpdate(float delta)
{
}
