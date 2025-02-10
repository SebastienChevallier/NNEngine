#pragma once
#include <VulkanManager.h>

namespace NNE {
	class TransformComponent : public AComponent
	{
	public:
		glm::vec3 position;
		glm::vec3 rotation; // en degrés ou radians selon votre convention
		glm::vec3 scale;

        TransformComponent() : position(0.0f), rotation(0.0f), scale(1.0f) {}

        glm::mat4 getModelMatrix() const {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, position);
            // Appliquer la rotation autour des axes X, Y et Z
            model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
            model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
            model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
            model = glm::scale(model, scale);
            return model;
        }
	};
}


