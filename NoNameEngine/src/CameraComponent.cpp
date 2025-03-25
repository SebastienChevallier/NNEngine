#include "CameraComponent.h"

NNE::CameraComponent::CameraComponent(float fov, float aspectRatio, float nearPlane, float farPlane) : fov(fov), aspectRatio(aspectRatio), nearPlane(nearPlane), farPlane(farPlane)
{
	SetPerspective(fov, aspectRatio, nearPlane, farPlane);
}

void NNE::CameraComponent::Update(float deltaTime)
{
    CameraComponent* cameraComp = _entity->GetComponent<CameraComponent>();
    TransformComponent* transform = _entity->GetComponent<TransformComponent>();
    // S’il s’agit d’une entité “caméra”
    if (cameraComp && transform) {
        glm::vec3 pos = transform->GetWorldPosition();
        glm::vec3 target = pos + transform->GetForward();
        glm::vec3 up = transform->GetUp();
        cameraComp->UpdateViewMatrix(pos, target, up);
    }
}

void NNE::CameraComponent::SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane)
{
    this->fov = fov;
    this->aspectRatio = aspectRatio;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;

    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    projectionMatrix[1][1] *= -1; // Correction pour Vulkan
}

void NNE::CameraComponent::UpdateViewMatrix(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up)
{
    viewMatrix = glm::lookAt(position, target, up);
}
