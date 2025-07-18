#pragma once
#include "AComponent.h"
#include "InputManager.h"
#include "MonoComponent.h"
#include "AEntity.h"
#include <glm/ext/vector_float3.hpp>

class PlayerController : public NNE::MonoComponent
{
private:
	float speed = 10.0f;
	float gravity = -9.81f;
	glm::vec3 direction = glm::vec3(0.0f);

public:
	PlayerController();
	~PlayerController();
	void Awake() override;
	void Update(float deltaTime) override;

	void OnHit(NNE::ColliderComponent* other) override;
};

