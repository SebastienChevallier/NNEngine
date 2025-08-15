#include "PlaneCollider.h"
#include <Jolt/Physics/Collision/Shape/PlaneShape.h>

/**
 * <summary>
 * Initialise un plan collision avec une normale et une distance.
 * </summary>
 */
NNE::Component::Physics::PlaneCollider::PlaneCollider(const glm::vec3& normal, float distance)
{
        plane = JPH::Plane(JPH::Vec3(normal.x, normal.y, normal.z), distance);
}

/**
 * <summary>
 * Crée l'objet shape représentant le plan.
 * </summary>
 */
void NNE::Component::Physics::PlaneCollider::CreateShape()
{
        shape = new JPH::PlaneShape(plane);
}
