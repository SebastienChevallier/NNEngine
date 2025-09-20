#include "MeshComponent.h"
#include <iostream>
#include <imgui.h>
#include <array>
#include <cstring>

/**
 * <summary>
 * Initialise les ressources du composant mesh.
 * </summary>
 */
NNE::Component::Render::MeshComponent::MeshComponent()
{
    
}

NNE::Component::Render::MeshComponent::~MeshComponent()
{

}

/**
 * <summary>
 * Définit le chemin vers le modèle à charger.
 * </summary>
 */
void NNE::Component::Render::MeshComponent::SetModelPath(std::string path)
{
        modelPath = std::move(path);
}

/**
 * <summary>
 * Définit le chemin vers la texture associée.
 * </summary>
 */
void NNE::Component::Render::MeshComponent::SetTexturePath(std::string path)
{
    material.texturePath = std::move(path);
}

void NNE::Component::Render::MeshComponent::DrawImGui()
{
    ImGui::TextUnformatted("Mesh");
    ImGui::Separator();

    std::array<char, 256> modelBuffer{};
    std::strncpy(modelBuffer.data(), modelPath.c_str(), modelBuffer.size() - 1);
    if (ImGui::InputText("Model Path", modelBuffer.data(), modelBuffer.size())) {
        SetModelPath(modelBuffer.data());
    }

    std::array<char, 256> textureBuffer{};
    std::strncpy(textureBuffer.data(), material.texturePath.c_str(), textureBuffer.size() - 1);
    if (ImGui::InputText("Texture Path", textureBuffer.data(), textureBuffer.size())) {
        SetTexturePath(textureBuffer.data());
    }

    const char* primitiveLabels[] = { "None", "Cube", "Sphere" };
    int primitiveIndex = static_cast<int>(primitive);
    if (ImGui::Combo("Primitive", &primitiveIndex, primitiveLabels, IM_ARRAYSIZE(primitiveLabels))) {
        primitive = static_cast<PrimitiveType>(primitiveIndex);
    }

    bool isSkybox = skybox;
    if (ImGui::Checkbox("Skybox", &isSkybox)) {
        skybox = isSkybox;
    }

    ImGui::DragFloat2("Tiling", &material.tiling[0], 0.01f);
    ImGui::DragFloat2("Offset", &material.offset[0], 0.01f);
}

/**
 * <summary>
 * Renvoie le chemin du modèle utilisé.
 * </summary>
 */
std::string NNE::Component::Render::MeshComponent::GetModelPath() const {
    return modelPath;
}

/**
 * <summary>
 * Renvoie le chemin de la texture utilisée.
 * </summary>
 */
std::string NNE::Component::Render::MeshComponent::GetTexturePath() const {
    return material.texturePath;
}
