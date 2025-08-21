#pragma once
#include "imgui.h"
#include <GLFW/glfw3.h>

#ifndef IMGUI_IMPL_API
#define IMGUI_IMPL_API
#endif

IMGUI_IMPL_API bool ImGui_ImplGlfw_InitForVulkan(GLFWwindow* window, bool install_callbacks);
IMGUI_IMPL_API void ImGui_ImplGlfw_NewFrame();
IMGUI_IMPL_API void ImGui_ImplGlfw_Shutdown();

