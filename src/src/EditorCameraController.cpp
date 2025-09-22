#include "EditorCameraController.h"
#include "Application.h"
#include "CameraComponent.h"
#include "InputManager.h"
#include "TransformComponent.h"
#include "VulkanManager.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <glm/glm.hpp>

using namespace NNE::Component;

void EditorCameraController::Awake()
{
    _transform = _entity ? _entity->transform : nullptr;
    if (_transform)
    {
        _yaw = _transform->rotation.y;
        _pitch = _transform->rotation.x;
    }

    _camera = _entity ? _entity->GetComponent<NNE::Component::Render::CameraComponent>() : nullptr;
    _lastMousePos = NNE::Systems::InputManager::GetMousePosition();

    if (auto* app = NNE::Systems::Application::GetInstance())
    {
        if (auto* vk = app->VKManager)
        {
            vk->SetSceneCamera(_camera);
            vk->UseSceneView(app->IsSceneViewActive());
        }
    }
}

void EditorCameraController::Update(float deltaTime)
{
    (void)deltaTime;
    auto* app = NNE::Systems::Application::GetInstance();
    GLFWwindow* window = (app && app->VKManager) ? app->VKManager->window : nullptr;

    if (!_transform || !_camera)
    {
        if (_capturing && window)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        _capturing = false;
        return;
    }

    if (!app || !app->IsSceneViewActive())
    {
        if (_capturing && window)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        _capturing = false;
        _lastMousePos = NNE::Systems::InputManager::GetMousePosition();
        return;
    }

    bool rightMouseDown = NNE::Systems::InputManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT);

    if (rightMouseDown && !_capturing)
    {
        _capturing = true;
        if (window)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        _lastMousePos = NNE::Systems::InputManager::GetMousePosition();
    }
    else if (!rightMouseDown && _capturing)
    {
        _capturing = false;
        if (window)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    glm::vec2 currentMouse = NNE::Systems::InputManager::GetMousePosition();
    if (_capturing)
    {
        glm::vec2 delta = currentMouse - _lastMousePos;
        _lastMousePos = currentMouse;
        _yaw -= delta.x * _mouseSensitivity;
        _pitch -= delta.y * _mouseSensitivity;
        _pitch = std::clamp(_pitch, -89.0f, 89.0f);
    }
    else
    {
        _lastMousePos = currentMouse;
    }

    _transform->rotation.x = _pitch;
    _transform->rotation.y = _yaw;

    float dt = app->GetDeltaTime();
    float speed = NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_LEFT_SHIFT) ? _fastMoveSpeed : _moveSpeed;
    glm::vec3 move{0.0f};

    if (rightMouseDown)
    {
        if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_W))
            move += _transform->GetForward();
        if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_S))
            move -= _transform->GetForward();
        if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_A))
            move -= _transform->GetRight();
        if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_D))
            move += _transform->GetRight();
        if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_E))
            move += _transform->GetUp();
        if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_Q))
            move -= _transform->GetUp();
    }

    if (glm::length(move) > 0.0f)
    {
        move = glm::normalize(move);
    }

    _transform->position += move * speed * dt;

    glm::vec3 position = _transform->GetWorldPosition();
    glm::vec3 forward = _transform->GetForward();
    glm::vec3 up = _transform->GetUp();
    _camera->UpdateViewMatrix(position, position + forward, up);
}

