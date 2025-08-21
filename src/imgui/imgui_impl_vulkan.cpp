#include "imgui_impl_vulkan.h"

IMGUI_IMPL_API bool ImGui_ImplVulkan_Init(ImGui_ImplVulkan_InitInfo*, VkRenderPass) { return true; }
IMGUI_IMPL_API void ImGui_ImplVulkan_NewFrame() {}
IMGUI_IMPL_API void ImGui_ImplVulkan_RenderDrawData(ImDrawData*, VkCommandBuffer) {}
IMGUI_IMPL_API void ImGui_ImplVulkan_Shutdown() {}

