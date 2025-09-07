#pragma once

#include <vector>
#include "ISystem.h"
#include "LightComponent.h"

namespace NNE::Systems {
class VulkanManager;

class LightSystem : public ISystem {
private:
    VulkanManager* _vkManager;
    std::vector<NNE::Component::Render::LightComponent*> _lights;
public:
    explicit LightSystem(VulkanManager* manager);
    void Awake() override {}
    void Start() override;
    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override {}
    void RegisterComponent(NNE::Component::AComponent* component) override;
};
}

