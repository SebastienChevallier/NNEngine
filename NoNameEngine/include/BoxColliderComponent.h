#pragma once
#include "ColliderComponent.h"
#include <glm/glm.hpp>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>

namespace NNE
{
	class BoxColliderComponent : public ColliderComponent
	{
	private:
		glm::vec3 size;

	public:
		BoxColliderComponent(const glm::vec3& size);
		void CreateShape() override;		
		
	};
}


