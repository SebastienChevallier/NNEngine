#include "BoxColliderComponent.h"
#include <Jolt/Physics/Collision/Shape/BoxShape.h>

NNE::BoxColliderComponent::BoxColliderComponent(const glm::vec3& size) : size(size)
{
	CreateShape();
}

void NNE::BoxColliderComponent::CreateShape()
{
	shape = new JPH::BoxShape(JPH::Vec3(size.x, size.y, size.z));
}
