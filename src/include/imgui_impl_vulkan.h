#pragma once
#include "imgui.h"
#include <vulkan/vulkan.h>

#ifndef IMGUI_IMPL_API
#define IMGUI_IMPL_API
#endif

struct ImGui_ImplVulkan_InitInfo {
    VkInstance Instance;
    VkPhysicalDevice PhysicalDevice;
    VkDevice Device;
    uint32_t QueueFamily;
    VkQueue Queue;
    VkDescriptorPool DescriptorPool;
    uint32_t MinImageCount;
    uint32_t ImageCount;
};

IMGUI_IMPL_API bool ImGui_ImplVulkan_Init(ImGui_ImplVulkan_InitInfo* info, VkRenderPass render_pass);
IMGUI_IMPL_API void ImGui_ImplVulkan_NewFrame();
IMGUI_IMPL_API void ImGui_ImplVulkan_RenderDrawData(ImDrawData* draw_data, VkCommandBuffer command_buffer);
IMGUI_IMPL_API void ImGui_ImplVulkan_Shutdown();

