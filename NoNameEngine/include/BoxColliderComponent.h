#pragma once
#include "ColliderComponent.h"
#include "Application.h"
#include <glm/glm.hpp>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>

namespace NNE
{
	//class ColliderComponent;
	class BoxColliderComponent : public ColliderComponent
	{
	private:
		glm::vec3 size;

	public:
		BoxColliderComponent(const glm::vec3& size);

		void Awake() override;
		void CreateShape() override;	

		/*void OnHit(ColliderComponent* other) override;
		void OnTriggerHit(ColliderComponent* other) override;*/
		
	};
}


