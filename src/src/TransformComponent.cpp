#include "TransformComponent.h"
#include <imgui.h>

/**
 * <summary>
 * Initialise les valeurs par défaut de position, rotation et échelle.
 * </summary>
 */
NNE::Component::TransformComponent::TransformComponent()
{
        position = glm::vec3(0.0f);
        rotation = glm::vec3(0.0f);
        scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

/**
 * <summary>
 * Met à jour les données de transformation.
 * </summary>
 */
void NNE::Component::TransformComponent::Update(float deltaTime)
{
        //rotation.y += 20.0f * deltaTime;
}

void NNE::Component::TransformComponent::DrawImGui()
{
        ImGui::DragFloat3("Position", &position[0], 0.1f);
        ImGui::DragFloat3("Rotation", &rotation[0], 0.1f);
        ImGui::DragFloat3("Scale", &scale[0], 0.1f);
}
