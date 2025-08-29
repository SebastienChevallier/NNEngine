#include "PlayerController.h"
#include <RigidbodyComponent.h>
#include <algorithm>

PlayerController::PlayerController()
{

}

PlayerController::~PlayerController()
{
}

void PlayerController::Awake()
{
        lastMousePos = NNE::Systems::InputManager::GetMousePosition();
        if (_entity->transform && !_entity->transform->children.empty()) {
                cameraTransform = _entity->transform->children[0];
                pitch = cameraTransform->rotation.x;
        }
        yaw = _entity->transform->rotation.y;
}

void PlayerController::Update(float deltaTime)
{
    direction = glm::vec3(0.0f);

    glm::vec2 mousePos = NNE::Systems::InputManager::GetMousePosition();
    glm::vec2 offset = mousePos - lastMousePos;
    lastMousePos = mousePos;

    yaw += offset.x * mouseSensitivity;
    pitch -= offset.y * mouseSensitivity;
    pitch = std::clamp(pitch, -89.0f, 89.0f);

    _entity->transform->rotation.y = yaw;
    if (cameraTransform) {
            cameraTransform->rotation.x = pitch;
    }

    if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_W)) {
            direction.z = 1;
    }

    if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_S)) {
            direction.z = -1;
    }

    if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_A)) {
            direction.x = 1;
    }


    if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_D)) {
            direction.x = -1;
    }
	

    if (NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_SPACE)) {
            direction.y = 1;
    }

	direction.y += (gravity / speed);
	
    _entity->GetComponent<NNE::Component::Physics::RigidbodyComponent>()->SetLinearVelocity(direction * speed);
	std::cout << _entity->transform->position.y << std::endl;
}

void PlayerController::OnHit(NNE::Component::Physics::ColliderComponent* other)
{
	std::cout << "OnHit" << std::endl;
}
