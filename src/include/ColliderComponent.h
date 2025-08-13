#pragma once
#include "AComponent.h"
#include "AEntity.h"
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>

namespace NNE::Component::Physics
{
    class ColliderComponent : public NNE::Component::AComponent
    {
    protected:
        JPH::ShapeRefC shape;

    public:
        JPH::BodyID bodyID;

        ColliderComponent() = default;
        virtual ~ColliderComponent() = default;

        virtual void CreateShape() = 0;

        JPH::ShapeRefC GetShape() const { return shape; }

        virtual void OnHit(ColliderComponent* other);

        virtual void OnTriggerHit(ColliderComponent* other);

        JPH::BodyID GetBodyID() const { return bodyID; }
    };
}
