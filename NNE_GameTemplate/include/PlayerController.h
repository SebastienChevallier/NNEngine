#pragma once
#include "AComponent.h"
#include "InputManager.h"
#include "AEntity.h"
#include "../../../../../vcpkg/installed/x64-windows/include/glm/ext/vector_float3.hpp"

class PlayerController : public NNE::AComponent
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


};

