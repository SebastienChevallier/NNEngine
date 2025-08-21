#include "DebugOverlay.h"


namespace NNE::Debug {

void DebugOverlay::Init() {
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
}

void DebugOverlay::Render() {
    ImGui::Render();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
}

void DebugOverlay::Shutdown() {
    ImGui::DestroyPlatformWindows();
    ImGui::DestroyContext();
}

} // namespace NNE::Debug


