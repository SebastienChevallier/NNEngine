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
                /**
                 * <summary>
                 * Crée un collider plan avec une normale et une distance.
                 * </summary>
                 */
                PlaneCollider(const glm::vec3& normal, float distance, bool isTrigger = false);
                /**
                 * <summary>
                 * Prépare le collider lors de son initialisation.
                 * </summary>
                 */
                void Awake() override;
                /**
                 * <summary>
                 * Génère la forme physique correspondant au plan.
                 * </summary>
                 */
                void CreateShape() override;
        };
}


