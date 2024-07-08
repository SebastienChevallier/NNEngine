#pragma once

#include <iostream>
#include <vector>
#include <map>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

namespace NNE {
	class VulkanManager
	{

	private:
		

	public :
		VkInstance instance;

		void CreateVulkanInstance();
		bool checkValidationLayerSupport();
		void pickPhysicalDevice();
	};
}


