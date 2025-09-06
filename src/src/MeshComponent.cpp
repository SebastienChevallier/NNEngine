#include "MeshComponent.h"
#include <iostream>

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
