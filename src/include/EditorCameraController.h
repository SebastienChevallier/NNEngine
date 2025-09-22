#pragma once

#include "MonoComponent.h"
#include <glm/vec2.hpp>

namespace NNE {
class AEntity;
}

namespace NNE::Component {

class TransformComponent;

namespace Render {
class CameraComponent;
}

class EditorCameraController : public MonoComponent {
    Render::CameraComponent* _camera = nullptr;
    TransformComponent* _transform = nullptr;
    glm::vec2 _lastMousePos{0.0f, 0.0f};
    float _yaw = 0.0f;
    float _pitch = 0.0f;
    bool _capturing = false;
    float _moveSpeed = 5.0f;
    float _fastMoveSpeed = 12.0f;
    float _mouseSensitivity = 0.1f;

public:
    void Awake() override;
    void Update(float deltaTime) override;
};

} // namespace NNE::Component

