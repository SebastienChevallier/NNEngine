#pragma once
#include "ColliderComponent.h"
#include <glm/glm.hpp>
#include <Jolt/Physics/Collision/Shape/PlaneShape.h>

namespace NNE::Component::Physics
{
        class PlaneCollider : public ColliderComponent
        {
        private:
                glm::vec3 normal;
                float distance;
                JPH::Plane plane;

        public:
                PlaneCollider(const glm::vec3& normal, float distance);
                void CreateShape() override;
        };
}


