#include "FreeCameraController.h"
#include <algorithm>
#include <glm/geometric.hpp>

FreeCameraController::FreeCameraController() {}
FreeCameraController::~FreeCameraController() {}

void FreeCameraController::Awake() {
    lastMousePos = NNE::Systems::InputManager::GetMousePosition();
    yaw = _entity->transform->rotation.y;
    pitch = _entity->transform->rotation.x;
}

void FreeCameraController::Update(float dt) {
    glm::vec2 mousePos = NNE::Systems::InputManager::GetMousePosition();
    glm::vec2 offset = mousePos - lastMousePos;
    lastMousePos = mousePos;

    yaw -= offset.x * mouseSensitivity;
    pitch -= offset.y * mouseSensitivity;
    pitch = std::clamp(pitch, -89.0f, 89.0f);

    _entity->transform->rotation.y = yaw;
    _entity->transform->rotation.x = pitch;

    glm::vec3 dir(0.0f);
    if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_W)) dir += _entity->transform->GetForward();
    if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_S)) dir -= _entity->transform->GetForward();
    if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_A)) dir -= _entity->transform->GetRight();
    if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_D)) dir += _entity->transform->GetRight();
    if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_SPACE)) dir += _entity->transform->GetUp();
    if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) dir -= _entity->transform->GetUp();

    if (glm::length(dir) > 0.0f) {
        dir = glm::normalize(dir);
        _entity->transform->position += dir * speed * dt;
    }
}
