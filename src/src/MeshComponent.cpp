#include "MeshComponent.h"
#include <iostream>
#include <imgui_widgets.cpp>

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
    ImGui::Text("Model Path: %s", modelPath.c_str());
	ImGui::Text("Texture Path: %s", material.texturePath.c_str());

    //Modify Material Offset and tilling
	ImGui::DragFloat2("Offset", &material.offset.x, 0.01f);
	ImGui::DragFloat2("Tiling", &material.tiling.x, 0.01f, 0.01f, 10.0f);
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
