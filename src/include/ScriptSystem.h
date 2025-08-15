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
    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override;
    void RegisterComponent(NNE::Component::AComponent* component) override;
};

}
