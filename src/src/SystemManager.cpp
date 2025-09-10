#include "SystemManager.h"
#include "ISystem.h"
#include "AComponent.h"

namespace NNE::Systems {

SystemManager* SystemManager::Instance = nullptr;

/**
 * <summary>
 * Retourne l'unique instance du gestionnaire de systèmes.
 * </summary>
 */
SystemManager* SystemManager::GetInstance()
{
    if (!Instance)
        Instance = new SystemManager();
    return Instance;
}

/**
 * <summary>
 * Ajoute un système à la collection gérée.
 * </summary>
 */
void SystemManager::AddSystem(ISystem* system)
{
    _systems.push_back(system);
}

/**
 * <summary>
 * Obtient la liste des systèmes enregistrés.
 * </summary>
 */
std::vector<ISystem*>& SystemManager::GetSystems()
{
    return _systems;
}

/**
 * <summary>
 * Inscrit un composant auprès de chaque système.
 * </summary>
 */
void SystemManager::RegisterComponent(NNE::Component::AComponent* component)
{
    for (ISystem* system : _systems)
    {
        system->RegisterComponent(component);
    }
}

void SystemManager::AwakeAll()
{
    for (ISystem* system : _systems)
    {
        system->Awake();
    }
}

void SystemManager::StartAll()
{
    for (ISystem* system : _systems)
    {
        system->Start();
    }
}

void SystemManager::UpdateAll(float deltaTime)
{
    for (ISystem* system : _systems)
    {
        system->Update(deltaTime);
    }
}

void SystemManager::LateUpdateAll(float deltaTime)
{
    for (ISystem* system : _systems)
    {
        system->LateUpdate(deltaTime);
    }
}

void SystemManager::Clear()
{
    for (ISystem* system : _systems)
    {
        delete system;
    }
    _systems.clear();
}

SystemManager::~SystemManager()
{
    Clear();
}

} // namespace NNE::Systems
