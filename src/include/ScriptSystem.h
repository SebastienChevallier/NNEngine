#pragma once

#include "ISystem.h"
#include "MonoComponent.h"
#include <vector>

namespace NNE::Systems {

class ScriptSystem : public ISystem {
private:
    std::vector<NNE::Component::MonoComponent*> _components;

public:
    void Awake() override {}
    void Start() override {}
    /**
     * <summary>
     * Met à jour tous les scripts à chaque frame.
     * </summary>
     */
    void Update(float deltaTime) override;
    /**
     * <summary>
     * Exécute les mises à jour tardives des scripts.
     * </summary>
     */
    void LateUpdate(float deltaTime) override;
    /**
     * <summary>
     * Ajoute un composant script à la gestion.
     * </summary>
     */
    void RegisterComponent(NNE::Component::AComponent* component) override;
};

}
