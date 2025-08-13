#pragma once
#include "AComponent.h"
#include "TransformComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "AEntity.h"

namespace NNE::Component::Render {
    class CameraComponent : public NNE::Component::AComponent {
    private:
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        float fov;
        float aspectRatio;
        float nearPlane;
        float farPlane;

    public:
        CameraComponent(float fov = 45.0f, float aspectRatio = 16.0f/9.0f, float nearPlane = 0.1f, float farPlane = 100.0f);
        virtual void Update(float deltaTime) override;
        void SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);
        void UpdateViewMatrix(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);

        glm::mat4 GetViewMatrix() const { return viewMatrix; }
        glm::mat4 GetProjectionMatrix() const { return projectionMatrix; }
        float GetFOV() { return fov; }
        float GetAspectRatio() { return aspectRatio; }
        float GetNearPlane() { return nearPlane; }
        float GetFarPlane() { return farPlane; }
    };
}
