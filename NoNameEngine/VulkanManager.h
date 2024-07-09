#pragma once
#include <corecrt.h>
#include <iostream>
#include <vector>
#include <map>
#include <optional>
#include <cstdint>
#include <set>


#define VK_USE_PLATFORM_WIN32_KHR
#define VK_KHR_surface
#define VK_KHR_win32_surface
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace NNE {

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	class VulkanManager
	{
	protected:
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device = VK_NULL_HANDLE;
		VkQueue graphicsQueue = VK_NULL_HANDLE;
		VkSurfaceKHR surface = VK_NULL_HANDLE;
		VkQueue presentQueue = VK_NULL_HANDLE;

	public :
		VkInstance instance = VK_NULL_HANDLE;

		VulkanManager();
		~VulkanManager();

		void CreateVulkanInstance();
		bool checkValidationLayerSupport();
		void pickPhysicalDevice();
		void createLogicalDevice();
		void createSurface(GLFWwindow* window);

		void CleanUp();

		bool isDeviceSuitable(VkPhysicalDevice device);
		int rateDeviceSuitability(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	};
}








