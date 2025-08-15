#include "TransformComponent.h"

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
