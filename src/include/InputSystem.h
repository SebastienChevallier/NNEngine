#pragma once

#include "ISystem.h"
#include "InputComponent.h"
#include "InputManager.h"
#include <vector>

namespace NNE::Systems {

class InputSystem : public ISystem {
private:
    std::vector<NNE::Component::Input::InputComponent*> _inputs;

public:
    void Awake() override {}
    void Start() override {}
    /**
     * <summary>
     * Met à jour l'état des composants d'entrée.
     * </summary>
     */
    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override {}
    /**
     * <summary>
     * Ajoute un composant d'entrée à la liste gérée.
     * </summary>
     */
    void RegisterComponent(NNE::Component::AComponent* component) override;
};

}

