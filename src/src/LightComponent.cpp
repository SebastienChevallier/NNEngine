#include "LightComponent.h"
#include "TransformComponent.h"
#include "AEntity.h"
#include <imgui_widgets.cpp>


/**
 * <summary>
 * Initialise une lumière directionnelle.
 * </summary>
 */
NNE::Component::Render::LightComponent::LightComponent(const glm::vec3& dir, const glm::vec3& color, float intensity, float ambient)
    : direction(glm::normalize(dir)), color(color), intensity(intensity), ambient(ambient) {}

/**
 * <summary>
 * Met à jour la direction de la lumière selon la transformation de l'entité.
 * </summary>
 */
void NNE::Component::Render::LightComponent::Update(float deltaTime)
{
    (void)deltaTime;
    if (NNE::Component::TransformComponent* transform = _entity->GetComponent<NNE::Component::TransformComponent>()) {
        direction = -transform->GetForward();
    }
}

void NNE::Component::Render::LightComponent::SetDirection(const glm::vec3& dir)
{
    direction = glm::normalize(dir);
}

glm::vec3 NNE::Component::Render::LightComponent::GetDirection() const
{
    return direction;
}

void NNE::Component::Render::LightComponent::SetColor(const glm::vec3& col)
{
    color = col;
}

glm::vec3 NNE::Component::Render::LightComponent::GetColor() const
{
    return color;
}

void NNE::Component::Render::LightComponent::SetIntensity(float i)
{
    intensity = i;
}

float NNE::Component::Render::LightComponent::GetIntensity() const
{
    return intensity;
}

void NNE::Component::Render::LightComponent::SetAmbient(float a)
{
    ambient = a;
}

float NNE::Component::Render::LightComponent::GetAmbient() const
{
    return ambient;
}

void NNE::Component::Render::LightComponent::DrawImGui()
{
    /*ImGui::Text("Light Component");
    ImGui::Separator();
    ImGui::ColorEdit3("Color", &color[0]);
    ImGui::SliderFloat("Intensity", &intensity, 0.0f, 10.0f);
    ImGui::SliderFloat("Ambient", &ambient, 0.0f, 1.0f);
	ImGui::DragFloat3("Direction", &direction[0], 0.1f, -1.0f, 1.0f);*/
}

