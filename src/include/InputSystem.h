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
    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override {}
    void RegisterComponent(NNE::Component::AComponent* component) override;
};

}

