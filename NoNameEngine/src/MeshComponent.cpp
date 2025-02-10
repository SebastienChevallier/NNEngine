#include "MeshComponent.h"

NNE::MeshComponent::MeshComponent()
{
}

void NNE::MeshComponent::SetModelPath(std::string path)
{
	modelPath = path;
}

void NNE::MeshComponent::SetTexturePath(std::string path)
{
	texturePath = path;
}

std::string NNE::MeshComponent::GetModelPath() const {
    return modelPath;
}

std::string NNE::MeshComponent::GetTexturePath() const {
    return texturePath;
}
