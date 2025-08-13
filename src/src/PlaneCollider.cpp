#include "PlaneCollider.h"
#include <Jolt/Physics/Collision/Shape/PlaneShape.h>

NNE::Component::Physics::PlaneCollider::PlaneCollider(const glm::vec3& normal, float distance)
{
        plane = JPH::Plane(JPH::Vec3(normal.x, normal.y, normal.z), distance);
}

void NNE::Component::Physics::PlaneCollider::CreateShape()
{
        shape = new JPH::PlaneShape(plane);
}
