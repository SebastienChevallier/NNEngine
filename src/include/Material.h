#pragma once
#include <string>
#include <vulkan/vulkan.h>
#include <glm/vec2.hpp>

namespace NNE::Component::Render {
    class Material {
    public:
        Material();
        ~Material();

        std::string texturePath;
        glm::vec2 tiling;
        glm::vec2 offset;
        std::string vertexShaderPath;
        std::string fragmentShaderPath;

        VkImage textureImage;
        VkDeviceMemory textureImageMemory;
        VkImageView textureImageView;
        VkSampler textureSampler;
    };
}
