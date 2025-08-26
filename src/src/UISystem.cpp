#include "UISystem.h"
#include "VulkanManager.h"
#include "PerformanceMetrics.h"
#include <imgui.h>
#include "Application.h"

namespace NNE::Systems {

UISystem::UISystem(VulkanManager* manager) : _vkManager(manager) {}

void UISystem::Start() {
    if (_vkManager) {
        _vkManager->initImGui();
    }
    _app = Application::GetInstance();
}

void UISystem::Update(float deltaTime) {
    (void)deltaTime;
    if (!_vkManager) return;

    _vkManager->beginImGuiFrame();

    static bool showPerf = true;
    static bool perfMax = false;
    //if (ImGui::IsKeyPressed(ImGuiKey_F11)) perfMax = !perfMax;

    if (showPerf) {
        ImGuiIO& io = ImGui::GetIO();

        ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_Appearing);
        ImGui::Begin("Performance", &showPerf);

        io.FontGlobalScale = 1.3f;

        ImGui::Text("Frame time: %.2f ms  (%.1f FPS)", g_FrameTimeMs, g_FPS);

        static float history[120] = {};
        static int idx = 0;
        history[idx] = g_FrameTimeMs;
        idx = (idx + 1) % IM_ARRAYSIZE(history);
        ImGui::PlotLines("Frametime (ms)", history, IM_ARRAYSIZE(history), idx, nullptr, 0.0f, 50.0f, ImVec2(-1, 80));

        ImGui::End();
        ImGui::Begin("Entities", &showPerf);

        for (NNE::AEntity* entity : _app->_entities) {
            ImGui::Text("Entity : %d", entity->GetName());
        }

        ImGui::End();
    }

    ImGui::Render();
}

void UISystem::LateUpdate(float deltaTime) {
    (void)deltaTime;
}

} // namespace NNE::Systems

