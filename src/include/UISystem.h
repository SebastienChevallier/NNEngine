#pragma once

#include "ISystem.h"

namespace NNE { class AEntity; }
namespace NNE { namespace Component { class AComponent; class TransformComponent; } }

namespace NNE::Systems {
class VulkanManager;
class Application;

class UISystem : public ISystem {
    VulkanManager* _vkManager;
    Application* _app;
    NNE::AEntity* _selectedEntity = nullptr;
    bool _sceneTabActive = true;

    void DrawHierarchyWindow(ImGuiID dockId);
    void DrawHierarchyNode(NNE::Component::TransformComponent* transform);
    void DrawInspectorWindow(ImGuiID dockId);
    void DrawViewportWindow(ImGuiID dockId);
    void DrawToolbarWindow(ImGuiID dockId);
    void DrawDebugWindow(ImGuiID dockId);

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

