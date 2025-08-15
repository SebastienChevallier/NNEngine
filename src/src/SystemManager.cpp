#include "SystemManager.h"
#include "ISystem.h"
#include "AComponent.h"

namespace NNE::Systems {

SystemManager* SystemManager::Instance = nullptr;

SystemManager* SystemManager::GetInstance()
{
    if (!Instance)
        Instance = new SystemManager();
    return Instance;
}

void SystemManager::AddSystem(ISystem* system)
{
    _systems.push_back(system);
}

std::vector<ISystem*>& SystemManager::GetSystems()
{
    return _systems;
}

void SystemManager::RegisterComponent(NNE::Component::AComponent* component)
{
    for (ISystem* system : _systems)
    {
        system->RegisterComponent(component);
    }
}

} // namespace NNE::Systems
