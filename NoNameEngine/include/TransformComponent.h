﻿#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "AComponent.h"
#include <iostream>

namespace NNE {
	class TransformComponent : public AComponent
	{
	public:
		glm::vec3 position;
		glm::vec3 rotation; // en degrés ou radians selon votre convention
		glm::vec3 scale;

		TransformComponent();

		glm::mat4 getModelMatrix() const {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, position);

			model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
			model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
			std::cout << "Rotation : " << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;

			std::cout << "scaleBefore : " << scale.x << " " << scale.y << " " << scale.z << std::endl;
			model = glm::scale(model, scale); // Échelle fixe (pas d'écrasement)
			std::cout << "scaleAfter : " << scale.x << " " << scale.y << " " << scale.z << std::endl;
			return model;
		}
	};
}


