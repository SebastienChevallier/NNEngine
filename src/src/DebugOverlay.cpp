#include "DebugOverlay.h"
#include "Application.h"

namespace NNE::Debug {

void DebugOverlay::Init() {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void DebugOverlay::Render() {
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    if (ImGui::Begin("Profiler")) {
        auto* app = NNE::Systems::Application::GetInstance();
        float dt = app ? app->GetDelta() : 0.0f;
        float fps = dt > 0.0f ? 1.0f / dt : 0.0f;
        ImGui::Text("Frame time: %.3f ms (%.1f FPS)", dt * 1000.0f, fps);
    }
    ImGui::End();

    ImGui::Render();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
}

void DebugOverlay::Shutdown() {
    ImGui::DestroyPlatformWindows();
    ImGui::DestroyContext();
}

} // namespace NNE::Debug


