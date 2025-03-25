#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "AComponent.h"
#include <iostream>
#include <vector>

namespace NNE {
	class alignas(16) TransformComponent : public AComponent
	{
	public:
		alignas(16) glm::vec3 position;
		alignas(16) glm::vec3 rotation; // en degrés ou radians selon votre convention
		alignas(16) glm::vec3 scale;

		TransformComponent* parent = nullptr;
		std::vector<TransformComponent*> children;

		TransformComponent();

		virtual void Update(float deltaTime);

        glm::mat4 getModelMatrix() const {
			return getWorldMatrix();
        }		

		glm::mat4 getWorldMatrix() const {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, position);

			model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
			model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(rotation.x - 90), glm::vec3(1, 0, 0));

			model = glm::scale(model, scale); // Échelle fixe (pas d'écrasement)
			//std::cout << "scale : " << scale.x << " " << scale.y << " " << scale.z << std::endl;
			//return model;

			if (parent) return parent->getWorldMatrix() * model;
			return model;
		}

		void SetParent(TransformComponent* newParent) {
			if (parent) {
				auto& siblings = parent->children;
				siblings.erase(std::remove(siblings.begin(), siblings.end(), this), siblings.end());
			}
			parent = newParent;
			if (parent) parent->children.push_back(this);
		}

		glm::vec3 GetWorldPosition() const {
			glm::mat4 world = getWorldMatrix();
			return glm::vec3(world[3]); // translation de la matrice
		}

		// Retourne la direction "avant" dans l'espace monde (utile pour caméras, IA, etc.)
		glm::vec3 GetForward() const {
			glm::mat4 world = getWorldMatrix();
			return glm::normalize(glm::vec3(world * glm::vec4(0, 0, -1, 0)));
		}

		// Retourne le vecteur "haut" monde
		glm::vec3 GetUp() const {
			glm::mat4 world = getWorldMatrix();
			return glm::normalize(glm::vec3(world * glm::vec4(0, 1, 0, 0)));
		}
	};
}


