#include "SphereCollider.h"
//#include "ColliderComponent.h"
//#include <Jolt/Physics/Collision/Shape/SphereShape.h>

NNE::Component::Physics::SphereCollider::SphereCollider(float radius, bool isTrigger) : ColliderComponent(isTrigger), _radius(radius)
{
}

void NNE::Component::Physics::SphereCollider::Awake()
{
    CreateShape();
}

/**
 * <summary>
 * Construit et enregistre la forme physique de la boîte.
 * </summary>
 */
void NNE::Component::Physics::SphereCollider::CreateShape()
{
    shape = new JPH::SphereShape(_radius);

    
}
