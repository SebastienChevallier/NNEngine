#include "CameraComponent.h"

NNE::Component::Render::CameraComponent::CameraComponent(float fov, float aspectRatio, float nearPlane, float farPlane) : fov(fov), aspectRatio(aspectRatio), nearPlane(nearPlane), farPlane(farPlane)
{
        SetPerspective(fov, aspectRatio, nearPlane, farPlane);
}

void NNE::Component::Render::CameraComponent::Update(float deltaTime)
{
    auto* cameraComp = _entity->GetComponent<NNE::Component::Render::CameraComponent>();
    auto* transform = _entity->GetComponent<NNE::Component::TransformComponent>();
    if (cameraComp && transform) {
        glm::vec3 pos = transform->GetWorldPosition();
        glm::vec3 target = pos + transform->GetForward();
        glm::vec3 up = transform->GetUp();
        cameraComp->UpdateViewMatrix(pos, target, up);
    }
}

void NNE::Component::Render::CameraComponent::SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane)
{
    this->fov = fov;
    this->aspectRatio = aspectRatio;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;

    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    projectionMatrix[1][1] *= -1;
}

void NNE::Component::Render::CameraComponent::UpdateViewMatrix(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up)
{
    viewMatrix = glm::lookAt(position, target, up);
}
