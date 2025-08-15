#pragma once

#include <vector>
#include <utility>
#include "ISystem.h"
#include "MeshComponent.h"
#include "TransformComponent.h"

namespace NNE::Systems {
class VulkanManager;

class RenderSystem : public ISystem {
private:
    VulkanManager* _vkManager;
    std::vector<std::pair<NNE::Component::Render::MeshComponent*, NNE::Component::TransformComponent*>> _renderObjects;

public:
    explicit RenderSystem(VulkanManager* manager);
    ~RenderSystem() = default;

    void Awake() override {}
    void Start() override;
    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override {}
    void RegisterComponent(NNE::Component::AComponent* component) override;

    const std::vector<std::pair<NNE::Component::Render::MeshComponent*, NNE::Component::TransformComponent*>>& GetRenderObjects() const;
};
}

