#include "PlayerController.h"
#include <RigidbodyComponent.h>
#include <algorithm>
#include <Application.h>
#include <UISystem.h>

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
	if (NNE::Systems::Application::GetInstance()->uiSystem->showPerf) return;

    direction = glm::vec3(0.0f);

    glm::vec2 mousePos = NNE::Systems::InputManager::GetMousePosition();
    glm::vec2 offset = mousePos - lastMousePos;
    lastMousePos = mousePos;

    yaw -= offset.x * mouseSensitivity;
    pitch -= offset.y * mouseSensitivity;
    pitch = std::clamp(pitch, -89.0f, 89.0f);

    _entity->transform->rotation.y = yaw;
    if (cameraTransform) {
            cameraTransform->rotation.x = -pitch;
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
		if (!isGrounded) return;
        _entity->GetComponent<NNE::Component::Physics::RigidbodyComponent>()->ApplyImpulse(_entity->transform->GetUp() * jumpHeight);
        //_entity->GetComponent<NNE::Component::Physics::RigidbodyComponent>()->ApplyForce(_entity->transform->GetUp() * jumpHeight, deltaTime);
    }

    if(NNE::Systems::InputManager::IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
        speed = 10.0f;
    } else {
        speed = 5.0f;
	}
    if(NNE::Systems::InputManager::IsMouseButtonPressed(0)) {
		NNE::Systems::PhysicsSystem::RaycastHit hitInfo;
        if(NNE::Systems::PhysicsSystem::Raycast(_entity->transform->position + (_entity->transform->GetForward() * 1.5f), _entity->transform->GetForward(), 1.0f, hitInfo)) {
            std::cout << "Hit : " << hitInfo.entity->GetName() << std::endl;
            if(hitInfo.entity->GetComponent<NNE::Component::Physics::RigidbodyComponent>()) {
                hitInfo.entity->GetComponent<NNE::Component::Physics::RigidbodyComponent>()->ApplyForce(_entity->transform->GetForward() * 50.0f, deltaTime);
			}
		}
	}

    if (glm::length(direction) > 0.0f) {
            direction = glm::normalize(direction);
            glm::vec3 forward = _entity->transform->GetForward();
            glm::vec3 right = _entity->transform->GetRight();
            direction = (forward * direction.z + right * direction.x) * speed;
	}

	direction.y += (_entity->GetComponent<NNE::Component::Physics::RigidbodyComponent>()->GetLinearVelocity().y);
	

	_entity->GetComponent<NNE::Component::Physics::RigidbodyComponent>()->SetLinearVelocity(direction);

	//Check if the player is grounded
    
    
    NNE::Systems::PhysicsSystem::RaycastHit hitInfo;
    isGrounded = NNE::Systems::PhysicsSystem::Raycast(_entity->transform->position, -_entity->transform->GetUp(), 1.5f, hitInfo, NNE::Systems::Layers::RAYCAST);
    //std::cout << isGrounded << std::endl;
	

	//std::cout << "X : " << direction.x << "|Y : " << direction.y << "|Z : " << direction.z << std::endl;
}

void PlayerController::OnHit(NNE::Component::Physics::ColliderComponent* other)
{
	std::cout << "OnHit" << std::endl;
}
