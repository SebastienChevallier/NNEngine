#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "AComponent.h"
#include <iostream>

namespace NNE {
	class alignas(16) TransformComponent : public AComponent
	{
	public:
		alignas(16) glm::vec3 position;
		alignas(16) glm::vec3 rotation; // en degrés ou radians selon votre convention
		alignas(16) glm::vec3 scale;

		TransformComponent();

		virtual void Update(float deltaTime);

        glm::mat4 getModelMatrix() const {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, position);
			
			model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
			model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(rotation.x - 90), glm::vec3(1, 0, 0));
			
			model = glm::scale(model, scale); // Échelle fixe (pas d'écrasement)
			//std::cout << "scale : " << scale.x << " " << scale.y << " " << scale.z << std::endl;
			return model;
        }
	};
}


