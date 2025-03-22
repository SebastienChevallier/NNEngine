#pragma once

#include "AComponent.h"
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>

namespace NNE
{
	class AComponent;
	class ColliderComponent : public AComponent
	{
	protected:
		JPH::ShapeRefC shape;

	public:
		ColliderComponent() = default;
		virtual ~ColliderComponent() = default;

		virtual void CreateShape() = 0; // pure virtuelle

		JPH::ShapeRefC GetShape() const { return shape; }
	};
}


