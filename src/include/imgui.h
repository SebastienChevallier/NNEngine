#pragma once
namespace ImGui {
inline void CreateContext() {}
inline void NewFrame() {}
inline void Render() {}
inline bool Begin(const char*, bool* = nullptr) { return true; }
inline void End() {}
inline void Text(const char*, ...) {}
}
