#pragma once

// Minimal ImGui stub for compilation in NNEngine tests.
// Provides enough interface used by DebugOverlay and VulkanManager.

struct ImGuiIO {
    int ConfigFlags = 0;
};

// Config flag for enabling viewports
constexpr int ImGuiConfigFlags_ViewportsEnable = 1 << 10;

namespace ImGui {
inline void CreateContext() {}
inline void DestroyContext() {}
inline void NewFrame() {}
inline void Render() {}
inline void UpdatePlatformWindows() {}
inline void RenderPlatformWindowsDefault() {}
inline void DestroyPlatformWindows() {}

inline ImGuiIO& GetIO() {
    static ImGuiIO io{};
    return io;
}
} // namespace ImGui

