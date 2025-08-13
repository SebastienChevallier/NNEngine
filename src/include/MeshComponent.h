#pragma once
#include "AComponent.h"
#include <string>
#include <vulkan/vulkan.h>

namespace NNE::Component::Render {
        class MeshComponent : public NNE::Component::AComponent
        {
    private:
        std::string modelPath;
        std::string texturePath;
        uint32_t indexOffset = 0;
        uint32_t indexCount = 0;

    public:
        MeshComponent();

        VkImage textureImage = VK_NULL_HANDLE;
        VkDeviceMemory textureImageMemory = VK_NULL_HANDLE;
        VkImageView textureImageView = VK_NULL_HANDLE;
        VkSampler textureSampler = VK_NULL_HANDLE;

        std::string GetModelPath() const;
        std::string GetTexturePath() const;
        void SetModelPath(std::string path);
        void SetTexturePath(std::string path);

        void setIndexOffset(uint32_t offset) { indexOffset = offset; }
        void setIndexCount(uint32_t count) { indexCount = count; }
        uint32_t getIndexOffset() const { return indexOffset; }
        uint32_t getIndexCount() const { return indexCount; }
        };
}
