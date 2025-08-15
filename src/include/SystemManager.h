#pragma once

#include <vector>

namespace NNE { namespace Component { class AComponent; } }

namespace NNE::Systems {
class ISystem;

class SystemManager {
private:
    std::vector<ISystem*> _systems;
    static SystemManager* Instance;

public:
    /**
     * <summary>
     * Accède à l'instance unique du gestionnaire de systèmes.
     * </summary>
     */
    static SystemManager* GetInstance();

    /**
     * <summary>
     * Ajoute un système à la liste gérée.
     * </summary>
     */
    void AddSystem(ISystem* system);
    /**
     * <summary>
     * Fournit la liste des systèmes enregistrés.
     * </summary>
     */
    std::vector<ISystem*>& GetSystems();

    /**
     * <summary>
     * Enregistre un composant auprès des systèmes concernés.
     * </summary>
     */
    void RegisterComponent(NNE::Component::AComponent* component);
};
}
