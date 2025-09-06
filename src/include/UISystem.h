#pragma once

#include "ISystem.h"

namespace NNE { namespace Component { class AComponent; } }

namespace NNE::Systems {
class VulkanManager;
class Application;

class UISystem : public ISystem {
    VulkanManager* _vkManager;
	Application* _app;
public:
    explicit UISystem(VulkanManager* manager);
    void Awake() override {}
    void Start() override;
    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override;
    void RegisterComponent(NNE::Component::AComponent* component) override {}
    bool showPerf = 0;
};
}

