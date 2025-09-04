#pragma once
#include "ColliderComponent.h"
#include <Jolt/Physics/Collision/Shape/SphereShape.h>

namespace NNE::Component::Physics 
{
	class SphereCollider :
		public ColliderComponent
	{
	private:
		float _radius;
	public: 
		SphereCollider(float radius, bool isTrigger = false);

		void Awake() override;		
		void CreateShape() override;
	};
}


