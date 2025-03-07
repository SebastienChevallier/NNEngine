#include "TransformComponent.h"

NNE::TransformComponent::TransformComponent()
{
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);

	std::cout << "📢 Constructeur TransformComponent appelé. Scale : "
		<< scale.x << " " << scale.y << " " << scale.z << std::endl;
}
