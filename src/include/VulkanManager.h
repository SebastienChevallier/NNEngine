#pragma once
#include <corecrt.h>
#include <iostream>
#include <vector>
#include <map>
#include <optional>
#include <cstdint>
#include <stdexcept>
#include <set>
#include <limits> // Necessary for std::numeric_limits
#include <algorithm> // Necessary for std::clamp
#include <cstddef>
#include <string>
#include <fstream>
#include <array>
#include <unordered_map>
#include "CameraComponent.h"

#define NOMINMAX //Necessary for ::Max()
#define VK_USE_PLATFORM_WIN32_KHR
#define VK_KHR_surface
#define VK_KHR_win32_surface
#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define STB_IMAGE_IMPLEMENTATION

//#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <chrono>



namespace NNE {
	class AEntity;	

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct Vertex {
		glm::vec3 pos;
		glm::vec3 color;
		glm::vec2 texCoord;

		static VkVertexInputBindingDescription getBindingDescription() {
			VkVertexInputBindingDescription bindingDescription{};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return bindingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
			std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, color);

			attributeDescriptions[2].binding = 0;
			attributeDescriptions[2].location = 2;
			attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

			return attributeDescriptions;
		}

		bool operator==(const Vertex& other) const {
			return pos == other.pos && color == other.color && texCoord == other.texCoord;
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	struct UniformBufferObject {		
		alignas(16) glm::mat4 model;		
	};	

	struct GlobalUniformBufferObject {
		alignas(16)glm::mat4 view;
		alignas(16)glm::mat4 proj;
	};

	class VulkanManager
	{
	protected:
		size_t dynamicAlignment;
		const size_t MAX_OBJECTS = 100;
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

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		
		VkBuffer indexBuffer;
		VkDeviceMemory indexBufferMemory;

		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;
		std::vector<void*> uniformBuffersMapped;

		std::vector<VkBuffer> objectUniformBuffers;
		std::vector<VkDeviceMemory> objectUniformBuffersMemory;
		std::vector<void*> objectUniformBuffersMapped;

		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		uint32_t mipLevels;
		VkImage textureImage;
		VkDeviceMemory textureImageMemory;
		VkImageView textureImageView;
		VkDescriptorSetLayout descriptorSetLayout;		
		VkSampler textureSampler;

		VkImage colorImage;
		VkDeviceMemory colorImageMemory;
		VkImageView colorImageView;

		VkDescriptorPool descriptorPool;
		std::vector<VkDescriptorSet> descriptorSets;

		VkImage depthImage;
		VkDeviceMemory depthImageMemory;
		VkImageView depthImageView;
		VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

	public :
		CameraComponent* activeCamera = nullptr;
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
		VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
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
		void createDescriptorPool();
		void createDescriptorSets();
		void drawFrame();
		void createSyncObjects();
		void recreateSwapChain();
		void updateCameraAspectRatio();
		
		void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		void createTextureImageView(VkImage textureImage, VkImageView& textureImageView);
		void createTextureSampler(VkSampler& textureSampler);
		void createDepthResources();
		void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
		
		void createColorResources();

		void loadModel(const std::string& modelPath);
		void createTextureImage(const std::string& texturePath, VkImage& textureImage, VkDeviceMemory& textureImageMemory);
		void LoadEntitiesModels(const std::vector<AEntity*>& entities);

		void UpdateObjectUniformBuffer(uint32_t currentImage, const std::vector<AEntity*>& entities);

		VkSampleCountFlagBits getMaxUsableSampleCount();

		VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		VkFormat findDepthFormat();
		bool hasStencilComponent(VkFormat format);
		VkCommandBuffer beginSingleTimeCommands();
		void endSingleTimeCommands(VkCommandBuffer commandBuffer);
		void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
		void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
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

namespace std {
	template<> struct hash<NNE::Vertex> {
		size_t operator()(NNE::Vertex const& vertex) const {
			return ((hash<glm::vec3>()(vertex.pos) ^
				(hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
				(hash<glm::vec2>()(vertex.texCoord) << 1);
		}
	};
}








