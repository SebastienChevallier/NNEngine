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
        /**
         * <summary>
         * Initialise un composant mesh sans données.
         * </summary>
         */
        MeshComponent();

        VkImage textureImage = VK_NULL_HANDLE;
        VkDeviceMemory textureImageMemory = VK_NULL_HANDLE;
        VkImageView textureImageView = VK_NULL_HANDLE;
        VkSampler textureSampler = VK_NULL_HANDLE;

        /**
         * <summary>
         * Retourne le chemin du modèle associé.
         * </summary>
         */
        std::string GetModelPath() const;
        /**
         * <summary>
         * Retourne le chemin de la texture associée.
         * </summary>
         */
        std::string GetTexturePath() const;
        /**
         * <summary>
         * Définit le chemin du modèle.
         * </summary>
         */
        void SetModelPath(std::string path);
        /**
         * <summary>
         * Définit le chemin de la texture.
         * </summary>
         */
        void SetTexturePath(std::string path);

        /**
         * <summary>
         * Spécifie le décalage d'indices dans le buffer.
         * </summary>
         */
        void setIndexOffset(uint32_t offset) { indexOffset = offset; }
        /**
         * <summary>
         * Spécifie le nombre d'indices du mesh.
         * </summary>
         */
        void setIndexCount(uint32_t count) { indexCount = count; }
        /**
         * <summary>
         * Récupère le décalage d'indices.
         * </summary>
         */
        uint32_t getIndexOffset() const { return indexOffset; }
        /**
         * <summary>
         * Récupère le nombre d'indices.
         * </summary>
         */
        uint32_t getIndexCount() const { return indexCount; }
        };
}
