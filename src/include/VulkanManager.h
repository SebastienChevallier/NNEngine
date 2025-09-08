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
#include <utility>
#include "CameraComponent.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "LightComponent.h"

#define NOMINMAX //Necessary for ::Max()
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define STB_IMAGE_IMPLEMENTATION
#define GLM_FORCE_CXX17

//#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>




namespace NNE::Systems {
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
		glm::vec3 normal;

		static VkVertexInputBindingDescription getBindingDescription() {
			VkVertexInputBindingDescription bindingDescription{};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return bindingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 4> getAttributeDescriptions() {
			std::array<VkVertexInputAttributeDescription, 4> attributeDescriptions{};

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

			attributeDescriptions[3].binding = 0;
			attributeDescriptions[3].location = 3;
			attributeDescriptions[3].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[3].offset = offsetof(Vertex, normal);

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
            alignas(16)glm::mat4 lightSpace;
    };

    struct alignas(16) LightUBO {
        glm::vec3 dir;      float intensity; // 16B
        glm::vec3 color;    float ambient;   // 16B
	};

    class VulkanManager
	{
	protected:
                size_t dynamicAlignment;
                const size_t MAX_OBJECTS = 100;
                static constexpr int MAX_FRAMES_IN_FLIGHT = 2;
                const uint32_t SHADOW_MAP_DIM = 2048;
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

		
		
		VkBuffer indexBuffer;
		VkDeviceMemory indexBufferMemory;

		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;
		std::vector<void*> uniformBuffersMapped;

        std::vector<VkBuffer> objectUniformBuffers;
        std::vector<VkDeviceMemory> objectUniformBuffersMemory;
        std::vector<void*> objectUniformBuffersMapped;

        std::vector<VkBuffer> lightBuffers;
        std::vector<VkDeviceMemory> lightBuffersMemory;
        std::vector<void*> lightBuffersMapped;

        std::vector<NNE::Component::Render::MeshComponent*> loadedMeshes;

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
                VkDescriptorPool imguiPool;

                VkImage depthImage;
                VkDeviceMemory depthImageMemory;
                VkImageView depthImageView;
                VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_8_BIT;
                bool supportsRenderToSingleSampled = false;

                // Shadow mapping resources
                VkRenderPass shadowRenderPass;
                VkFramebuffer shadowFramebuffer;
                VkImage shadowImage;
                VkDeviceMemory shadowImageMemory;
                VkImageView shadowImageView;
                VkSampler shadowSampler;
                VkPipeline shadowPipeline;

                VkPipelineLayout shadowPipelineLayout;
                VkDescriptorSetLayout shadowDescriptorSetLayout;
                std::array<VkDescriptorSet, MAX_FRAMES_IN_FLIGHT> shadowDescriptorSets;

        private:
                bool shadowDebugRequested;

        public :
            NNE::Component::Render::CameraComponent* activeCamera = nullptr;
            NNE::Component::Render::LightComponent* activeLight = nullptr;
                VkInstance instance = VK_NULL_HANDLE;
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
		GLFWwindow* window;
            /**
                * <summary>
                * Initialise le gestionnaire Vulkan.
                * </summary>
                */
            VulkanManager();
            /**
                * <summary>
                * Libère toutes les ressources Vulkan.
                * </summary>
                */
            ~VulkanManager();
            VkDevice device = VK_NULL_HANDLE;
            /**
                * <summary>
                * Configure et lance l'initialisation Vulkan.
                * </summary>
                */
            void initVulkan();

            /**
                * <summary>
                * Crée l'instance Vulkan principale.
                * </summary>
                */
            void CreateVulkanInstance();
            /**
                * <summary>
                * Vérifie la disponibilité des couches de validation.
                * </summary>
                */
            bool checkValidationLayerSupport();
            /**
                * <summary>
                * Sélectionne le périphérique physique approprié.
                * </summary>
                */
            void pickPhysicalDevice();
            /**
                * <summary>
                * Crée le périphérique logique Vulkan.
                * </summary>
                */
            void createLogicalDevice();
            /**
                * <summary>
                * Crée une fenêtre GLFW pour le rendu.
                * </summary>
                */
            GLFWwindow* CreateGLFWWindow(int width, int height);
            /**
                * <summary>
                * Callback lors du redimensionnement de la fenêtre.
                * </summary>
                */
            static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
            /**
                * <summary>
                * Crée la surface de rendu Vulkan.
                * </summary>
                */
            void createSurface();
            /**
                * <summary>
                * Met en place la swap chain.
                * </summary>
                */
            void createSwapChain();
            /**
                * <summary>
                * Crée les vues d'images de la swap chain.
                * </summary>
                */
            void createImageViews();
            /**
                * <summary>
                * Crée une vue sur une image Vulkan.
                * </summary>
                */
            VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
            /**
                * <summary>
                * Établit le render pass.
                * </summary>
                */
            void createRenderPass();
            void createShadowRenderPass();
            /**
                * <summary>
                * Génère le pipeline graphique.
                * </summary>
                */
            void createGraphicsPipeline();
            void createShadowPipeline();
            /**
                * <summary>
                * Crée un buffer Vulkan générique.
                * </summary>
                */
            void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
            /**
                * <summary>
                * Copie les données d'un buffer à un autre.
                * </summary>
                */
            void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
            /**
                * <summary>
                * Crée le buffer d'indices.
                * </summary>
                */
            void createIndexBuffer();
            /**
                * <summary>
                * Crée le buffer de sommets.
                * </summary>
                */
            void createVertexBuffer();
            /**
                * <summary>
                * Crée les framebuffers de rendu.
                * </summary>
                */
            void createFramebuffers();
            /**
                * <summary>
                * Crée le pool de commandes.
                * </summary>
                */
            void createCommandPool();
            /**
                * <summary>
                * Alloue les buffers de commandes.
                * </summary>
                */
            void createCommandBuffers();
            /**
                * <summary>
                * Crée les buffers uniformes.
                * </summary>
                */
            void createUniformBuffers();
            /**
                * <summary>
                * Enregistre les commandes de dessin.
                * </summary>
                */
            void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, const std::vector<std::pair<NNE::Component::Render::MeshComponent*, NNE::Component::TransformComponent*>>& objects);
            /**
                * <summary>
                * Met à jour le buffer uniforme pour une image.
                * </summary>
                */
            void updateUniformBuffer(uint32_t currentImage);
            /**
                * <summary>
                * Crée le layout des descripteurs.
                * </summary>
                */
            void createDescriptorSetLayout();
            void createShadowDescriptorSetLayout();
            /**
                * <summary>
                * Crée le pool de descripteurs.
                * </summary>
                */
            void createDescriptorPool();
            /**
                * <summary>
                * Alloue et écrit les descripteurs.
                * </summary>
                */
            void createDescriptorSets();
            void createShadowDescriptorSets();
            /**
                * <summary>
                * Dessine une frame complète.
                * </summary>
                */
            void drawFrame(const std::vector<std::pair<NNE::Component::Render::MeshComponent*, NNE::Component::TransformComponent*>>& objects);
            /**
                * <summary>
                * Crée les objets de synchronisation.
                * </summary>
                */
            void createSyncObjects();
            /**
                * <summary>
                * Reconstruit la swap chain après redimensionnement.
                * </summary>
                */
            void recreateSwapChain();
            /**
                * <summary>
                * Met à jour le ratio d'aspect de la caméra active.
                * </summary>
                */
            void updateCameraAspectRatio();
		
            /**
                * <summary>
                * Crée une image Vulkan avec les paramètres souhaités.
                * </summary>
                */
            void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
            /**
                * <summary>
                * Crée une vue pour une image de texture.
                * </summary>
                */
            void createTextureImageView(VkImage textureImage, VkImageView& textureImageView, VkFormat format);
            /**
                * <summary>
                * Crée un sampler pour les textures.
                * </summary>
                */
            void createTextureSampler(VkSampler& textureSampler);
            /**
                * <summary>
                * Prépare les ressources de profondeur.
                * </summary>
                */
            void createDepthResources();
            void createShadowResources();
            /**
                * <summary>
                * Génère les mipmaps d'une image.
                * </summary>
                */
            void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

            /**
                * <summary>
                * Crée les ressources de couleur nécessaires au MSAA.
                * </summary>
                */
            void createColorResources();

            /**
                * <summary>
                * Charge un modèle 3D depuis le disque.
                * </summary>
                */
            void loadModel(const std::string& modelPath);
            void generateCube(std::vector<Vertex>& vertexData, std::vector<uint32_t>& indexData);
            void generateSphere(std::vector<Vertex>& vertexData, std::vector<uint32_t>& indexData);
            /**
                * <summary>
                * Charge une texture depuis le disque.
                * </summary>
                */
            void createTextureImage(const std::string& texturePath, VkImage& textureImage, VkDeviceMemory& textureImageMemory, VkFormat& imageFormat);
            /**
                * <summary>
                * Charge les meshes des objets fournis.
                * </summary>
                */
            void LoadMeshes(const std::vector<std::pair<NNE::Component::Render::MeshComponent*, NNE::Component::TransformComponent*>>& objects);

            /**
                * <summary>
                * Retourne le niveau d'échantillonnage maximal supporté.
                * </summary>
                */
            VkSampleCountFlagBits getMaxUsableSampleCount();

            /**
                * <summary>
                * Trouve un format supporté répondant aux critères.
                * </summary>
                */
            VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
            /**
                * <summary>
                * Récupère le format utilisé pour la profondeur.
                * </summary>
                */
            VkFormat findDepthFormat();
            /**
                * <summary>
                * Vérifie si le format possède un composant profondeur.
                * </summary>
                */
            bool hasDepthComponent(VkFormat format);
            /**
                * <summary>
                * Vérifie si le format possède un composant stencil.
                * </summary>
                */
            bool hasStencilComponent(VkFormat format);
            /**
                * <summary>
                * Commence une commande à usage unique.
                * </summary>
                */
            VkCommandBuffer beginSingleTimeCommands();
            /**
                * <summary>
                * Termine l'exécution d'une commande à usage unique.
                * </summary>
                */
            void endSingleTimeCommands(VkCommandBuffer commandBuffer);
            void initImGui();
            void cleanupImGui();
            void beginImGuiFrame();
            void renderImGui(VkCommandBuffer commandBuffer);
            /**
                * <summary>
                * Change l'agencement d'une image.
                * </summary>
                */
            void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
            /**
                * <summary>
                * Copie les données d'un buffer vers une image.
                * </summary>
                */
            void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
            /**
                * <summary>
                * Copie les données d'une image vers un buffer.
                * </summary>
                */
            void copyImageToBuffer(VkImage image, VkBuffer buffer, uint32_t width, uint32_t height);
            /**
                * <summary>
                * Affiche des statistiques sur la shadow map pour vérifier son contenu.
                * </summary>
                */
            void debugShadowMap();
            void requestShadowDebug();
            /**
                * <summary>
                * Crée un module de shader à partir de code binaire.
                * </summary>
                */
            VkShaderModule createShaderModule(const std::vector<char>& code);

            /**
                * <summary>
                * Lit un fichier binaire depuis le disque.
                * </summary>
                */
            static std::vector<char> readFile(const std::string& filename);

            /**
                * <summary>
                * Nettoie toutes les ressources Vulkan.
                * </summary>
                */
            void CleanUp();
            /**
                * <summary>
                * Détruit les ressources de la swap chain.
                * </summary>
                */
            void cleanupSwapChain();

            /**
                * <summary>
                * Vérifie si un périphérique physique convient.
                * </summary>
                */
            bool isDeviceSuitable(VkPhysicalDevice device);
            /**
                * <summary>
                * Évalue la pertinence d'un périphérique.
                * </summary>
                */
            int rateDeviceSuitability(VkPhysicalDevice device);
            /**
                * <summary>
                * Trouve les familles de files nécessaires.
                * </summary>
                */
            QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

            /**
                * <summary>
                * Vérifie le support des extensions requises.
                * </summary>
                */
            bool checkDeviceExtensionSupport(VkPhysicalDevice device);
            bool hasExtension(VkPhysicalDevice device, const char* extensionName);

            /**
                * <summary>
                * Interroge les capacités de la swap chain du périphérique.
                * </summary>
                */
            SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
            /**
                * <summary>
                * Choisit le format de surface approprié.
                * </summary>
                */
            VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
            /**
                * <summary>
                * Choisit le mode de présentation de la swap chain.
                * </summary>
                */
            VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
            /**
                * <summary>
                * Détermine les dimensions de la swap chain.
                * </summary>
                */
            VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
            /**
                * <summary>
                * Trouve un type de mémoire répondant aux propriétés requises.
                * </summary>
                */
            uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	};
}

namespace std {
        template<> struct hash<glm::vec2> {
                size_t operator()(glm::vec2 const& v) const noexcept {
                        return hash<float>()(v.x) ^ (hash<float>()(v.y) << 1);
                }
        };
        template<> struct hash<glm::vec3> {
                size_t operator()(glm::vec3 const& v) const noexcept {
                        size_t h1 = hash<float>()(v.x);
                        size_t h2 = hash<float>()(v.y);
                        size_t h3 = hash<float>()(v.z);
                        return ((h1 ^ (h2 << 1)) >> 1) ^ (h3 << 1);
                }
        };
        template<> struct hash<NNE::Systems::Vertex> {
                size_t operator()(NNE::Systems::Vertex const& vertex) const {
                        return ((hash<glm::vec3>()(vertex.pos) ^
                                (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
                                (hash<glm::vec2>()(vertex.texCoord) << 1);
                }
        };
}








