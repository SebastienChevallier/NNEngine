#pragma once
#include "AComponent.h"
#include "InputManager.h"
#include "MonoComponent.h"
#include "AEntity.h"
#include "TransformComponent.h"
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>

class FreeCameraController : public NNE::Component::MonoComponent {
private:
    float speed = 5.0f;
    float mouseSensitivity = 0.1f;
    glm::vec2 lastMousePos{0.0f};
    float yaw = 0.0f;
    float pitch = 0.0f;

public:
    FreeCameraController();
    ~FreeCameraController();
    void Awake() override;
    void Update(float dt) override;
};
