#include "DebugOverlay.h"
#include "Application.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"

namespace NNE::Debug {

void DebugOverlay::Init() {
    ImGui::CreateContext();

    // Initialize platform/renderer backends
    ImGui_ImplGlfw_InitForVulkan(nullptr, true);
    ImGui_ImplVulkan_InitInfo initInfo{};
    ImGui_ImplVulkan_Init(&initInfo, VK_NULL_HANDLE);

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void DebugOverlay::Render() {
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplVulkan_NewFrame();
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
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), VK_NULL_HANDLE);
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
}

void DebugOverlay::Shutdown() {
    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyPlatformWindows();
    ImGui::DestroyContext();
}

} // namespace NNE::Debug


