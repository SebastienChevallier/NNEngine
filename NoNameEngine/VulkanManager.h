#pragma once
#include <corecrt.h>
#include <iostream>
#include <vector>
#include <map>
#include <optional>
#include <cstdint>
#include <set>
#include <limits> // Necessary for std::numeric_limits
#include <algorithm> // Necessary for std::clamp
#include <cstddef>
#include <string>
#include <fstream>
#include <array>

#define NOMINMAX //Necessary for ::Max()


#define VK_USE_PLATFORM_WIN32_KHR
#define VK_KHR_surface
#define VK_KHR_win32_surface
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

namespace NNE {

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct Vertex {
		glm::vec2 pos;
		glm::vec3 color;

		static VkVertexInputBindingDescription getBindingDescription() {
			VkVertexInputBindingDescription bindingDescription{};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return bindingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
			std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, color);

			return attributeDescriptions;
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	struct UniformBufferObject {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};

	class VulkanManager
	{
	protected:
		const int MAX_FRAMES_IN_FLIGHT = 2;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		//VkDevice device = VK_NULL_HANDLE;
		VkQueue graphicsQueue = VK_NULL_HANDLE;
		VkSurfaceKHR surface = VK_NULL_HANDLE;
		VkQueue presentQueue = VK_NULL_HANDLE;

		VkSwapchainKHR swapChain;
		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;

		std::vector<VkImageView> swapChainImageViews;

		VkRenderPass renderPass;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;
		std::vector<VkFramebuffer> swapChainFramebuffers;
		VkCommandPool commandPool;
		std::vector<VkCommandBuffer> commandBuffers;
		std::vector < VkSemaphore> imageAvailableSemaphores;
		std::vector < VkSemaphore> renderFinishedSemaphores;
		std::vector < VkFence> inFlightFences;
		uint32_t currentFrame = 0;
		bool framebufferResized = false;

		const std::vector<Vertex> vertices = {
			{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
			{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
			{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
		};

		const std::vector<uint16_t> indices = {
			0, 1, 2, 2, 3, 0
		};

		
		VkBuffer indexBuffer;
		VkDeviceMemory indexBufferMemory;

		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;
		std::vector<void*> uniformBuffersMapped;

		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;

		VkDescriptorSetLayout descriptorSetLayout;
		VkPipelineLayout pipelineLayout;

	public :
		VkInstance instance = VK_NULL_HANDLE;
		GLFWwindow* window;
		VulkanManager();
		~VulkanManager();
		VkDevice device = VK_NULL_HANDLE;
		void initVulkan();

		void CreateVulkanInstance();
		bool checkValidationLayerSupport();
		void pickPhysicalDevice();
		void createLogicalDevice();
		GLFWwindow* CreateGLFWWindow(int width, int height);
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
		void createSurface();
		void createSwapChain();
		void createImageViews();
		void createRenderPass();
		void createGraphicsPipeline();
		void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
		void createIndexBuffer();
		void createVertexBuffer();
		void createFramebuffers();
		void createCommandPool();
		void createCommandBuffers();
		void createUniformBuffers();
		void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
		void updateUniformBuffer(uint32_t currentImage);
		void createDescriptorSetLayout();
		void drawFrame();
		void createSyncObjects();
		void recreateSwapChain();
		VkShaderModule createShaderModule(const std::vector<char>& code);

		static std::vector<char> readFile(const std::string& filename);

		void CleanUp();
		void cleanupSwapChain();

		bool isDeviceSuitable(VkPhysicalDevice device);
		int rateDeviceSuitability(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

		bool checkDeviceExtensionSupport(VkPhysicalDevice device);

		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	};
}








