#include "ScriptSystem.h"

using namespace NNE::Systems;

void ScriptSystem::Update(float deltaTime)
{
    for (auto* comp : _components)
    {
        comp->Update(deltaTime);
    }
}

void ScriptSystem::LateUpdate(float deltaTime)
{
    for (auto* comp : _components)
    {
        comp->LateUpdate(deltaTime);
    }
}

void ScriptSystem::RegisterComponent(NNE::Component::AComponent* component)
{
    if (auto* mono = dynamic_cast<NNE::Component::MonoComponent*>(component))
    {
        _components.push_back(mono);
    }
}
