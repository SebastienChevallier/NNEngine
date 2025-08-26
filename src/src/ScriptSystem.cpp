#include "ScriptSystem.h"

namespace NNE::Systems {

/**
 * <summary>
 * Met à jour tous les composants script.
 * </summary>
 */
void ScriptSystem::Update(float deltaTime)
{
    for (auto* comp : _components)
    {
        comp->Update(deltaTime);
    }
}

/**
 * <summary>
 * Applique les mises à jour tardives aux scripts.
 * </summary>
 */
void ScriptSystem::LateUpdate(float deltaTime)
{
    for (auto* comp : _components)
    {
        comp->LateUpdate(deltaTime);
    }
}

/**
 * <summary>
 * Enregistre un composant script s'il est valide.
 * </summary>
 */
void ScriptSystem::RegisterComponent(NNE::Component::AComponent* component)
{
    if (auto* mono = dynamic_cast<NNE::Component::MonoComponent*>(component))
    {
        _components.push_back(mono);
    }
}

} // namespace NNE::Systems
