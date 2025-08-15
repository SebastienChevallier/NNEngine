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

} // namespace NNE::Systems
