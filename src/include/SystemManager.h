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

    /**
     * <summary>
     * Réveille tous les systèmes enregistrés.
     * </summary>
     */
    void AwakeAll();
    /**
     * <summary>
     * Démarre tous les systèmes enregistrés.
     * </summary>
     */
    void StartAll();
    /**
     * <summary>
     * Met à jour tous les systèmes enregistrés.
     * </summary>
     */
    void UpdateAll(float deltaTime);
    /**
     * <summary>
     * Applique les mises à jour tardives de tous les systèmes.
     * </summary>
     */
    void LateUpdateAll(float deltaTime);
    /**
     * <summary>
     * Supprime et nettoie tous les systèmes.
     * </summary>
     */
    void Clear();

    ~SystemManager();

    template <typename T>
    T* GetSystem()
    {
        for (ISystem* system : _systems)
        {
            if (auto casted = dynamic_cast<T*>(system))
                return casted;
        }
        return nullptr;
    }
};
}
