#pragma once
#include <cstdint>

// Simplified ImGui header providing minimal declarations used by NNEngine.
// This is not a full implementation of Dear ImGui.

struct ImDrawData {};

struct ImGuiIO {
    int ConfigFlags = 0;
};

struct ImGuiViewport {};

constexpr int ImGuiConfigFlags_ViewportsEnable = 1 << 10;
constexpr int ImGuiConfigFlags_DockingEnable   = 1 << 7;

namespace ImGui {
inline void CreateContext() {}
inline void DestroyContext() {}
inline void NewFrame() {}
inline void Render() {}
inline void UpdatePlatformWindows() {}
inline void RenderPlatformWindowsDefault() {}
inline void DestroyPlatformWindows() {}

inline ImGuiIO& GetIO() { static ImGuiIO io{}; return io; }
inline ImGuiViewport* GetMainViewport() { static ImGuiViewport viewport; return &viewport; }
inline ImDrawData* GetDrawData() { static ImDrawData drawData; return &drawData; }

inline void DockSpaceOverViewport(ImGuiViewport*, int = 0) {}

inline bool Begin(const char*, bool* = nullptr, int = 0) { return true; }
inline void End() {}
inline void Text(const char*, ...) {}
} // namespace ImGui

