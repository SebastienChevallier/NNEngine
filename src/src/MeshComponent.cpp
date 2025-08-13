#include "MeshComponent.h"
#include <iostream>

NNE::Component::Render::MeshComponent::MeshComponent()
{
    textureImage = VK_NULL_HANDLE;
    textureImageMemory = VK_NULL_HANDLE;
    textureImageView = VK_NULL_HANDLE;
    textureSampler = VK_NULL_HANDLE;
}

void NNE::Component::Render::MeshComponent::SetModelPath(std::string path)
{
        modelPath = std::move(path);
}

void NNE::Component::Render::MeshComponent::SetTexturePath(std::string path)
{
        texturePath = std::move(path);
}

std::string NNE::Component::Render::MeshComponent::GetModelPath() const {
    return modelPath;
}

std::string NNE::Component::Render::MeshComponent::GetTexturePath() const {
    return texturePath;
}
