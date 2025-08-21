#include "DebugOverlay.h"


namespace NNE::Debug {

void  DebugOverlay::Init() {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	
}

void  DebugOverlay::Render() {
    ImGui::Render();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
}

void  DebugOverlay::Shutdown() {
    ImGui::DestroyPlatformWindows();
    ImGui::DestroyContext();
}

} // namespace NNE::Debug


