#include "PlayerController.h"
#include <RigidbodyComponent.h>

PlayerController::PlayerController()
{

}

PlayerController::~PlayerController()
{
}

void PlayerController::Awake()
{
	
}

void PlayerController::Update(float deltaTime)
{
	direction = glm::vec3(0.0f);	

	if (NNE::InputManager::IsKeyPressed(GLFW_KEY_W)) {
		direction.z = 1;				
	}

	if (NNE::InputManager::IsKeyPressed(GLFW_KEY_S)) {
		direction.z = -1;
	}	

	if (NNE::InputManager::IsKeyPressed(GLFW_KEY_A)) {
		direction.x = 1;
	}
	

	if (NNE::InputManager::IsKeyPressed(GLFW_KEY_D)) {
		direction.x = -1;
	}
	

	if (NNE::InputManager::IsKeyPressed(GLFW_KEY_SPACE)) {
		direction.y = 1;
	}

	direction.y += (gravity / speed);
	
	_entity->GetComponent<NNE::RigidbodyComponent>()->SetLinearVelocity(direction * speed);	
	std::cout << _entity->transform->position.x << std::endl;
}

void PlayerController::OnHit(NNE::ColliderComponent* other)
{
	std::cout << "OnHit" << std::endl;
}
