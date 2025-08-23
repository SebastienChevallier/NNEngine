#include "UISystem.h"
#include "VulkanManager.h"
#include "PerformanceMetrics.h"
#include <imgui.h>

using namespace NNE::Systems;

UISystem::UISystem(VulkanManager* manager) : _vkManager(manager) {}

void UISystem::Start() {
    if (_vkManager) {
        _vkManager->initImGui();
    }
}

void UISystem::Update(float deltaTime) {
    (void)deltaTime;
    if (!_vkManager) return;

    _vkManager->beginImGuiFrame();

    static bool showPerf = true;
    if (showPerf) {
        ImGui::SetNextWindowSize(ImVec2(380, 220), ImGuiCond_FirstUseEver);
        ImGui::Begin("Performance", &showPerf);
        ImGui::Text("Frame time: %.2f ms  (%.1f FPS)", g_FrameTimeMs, g_FPS);
        static float history[120] = {};
        static int idx = 0;
        history[idx] = g_FrameTimeMs; idx = (idx + 1) % IM_ARRAYSIZE(history);
        ImGui::PlotLines("Frametime (ms)", history, IM_ARRAYSIZE(history), idx, nullptr, 0.0f, 50.0f, ImVec2(-1, 60));
        ImGui::End();
    }

    ImGui::Render();
}

void UISystem::LateUpdate(float deltaTime) {
    (void)deltaTime;
}

