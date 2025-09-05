#pragma once
#include "AComponent.h"
#include "InputManager.h"
#include "PhysicsSystem.h"
#include "MonoComponent.h"
#include "AEntity.h"
#include "TransformComponent.h"
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>

class PlayerController : public NNE::Component::MonoComponent
{
private:
        float speed = 10.0f;
        float gravity = -9.81f;
        glm::vec3 direction = glm::vec3(0.0f);

        float mouseSensitivity = 0.1f;
        glm::vec2 lastMousePos = glm::vec2(0.0f);
        float yaw = 0.0f;
        float pitch = 0.0f;
        NNE::Component::TransformComponent* cameraTransform = nullptr;

public:
	PlayerController();
	~PlayerController();
	void Awake() override;
	void Update(float deltaTime) override;

        void OnHit(NNE::Component::Physics::ColliderComponent* other) override;
};

