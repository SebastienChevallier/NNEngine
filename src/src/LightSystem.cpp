#include "LightSystem.h"
#include "VulkanManager.h"
#include "AComponent.h"

namespace NNE::Systems {

LightSystem::LightSystem(VulkanManager* manager) : _vkManager(manager) {}

void LightSystem::Start() {
    if (_vkManager && !_lights.empty()) {
        _vkManager->activeLight = _lights[0];
    }
}

void LightSystem::Update(float deltaTime) {
    (void)deltaTime;
}

void LightSystem::RegisterComponent(NNE::Component::AComponent* component) {
    if (auto* light = dynamic_cast<NNE::Component::Render::LightComponent*>(component)) {
        _lights.push_back(light);
        if (_vkManager && !_vkManager->activeLight) {
            _vkManager->activeLight = light;
        }
    }
}

} // namespace NNE::Systems

