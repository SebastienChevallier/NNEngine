#pragma once
#include "ColliderComponent.h"
#include <glm/glm.hpp>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>

namespace NNE::Component::Physics
{
    class BoxColliderComponent : public ColliderComponent
    {
    private:
        glm::vec3 size;

    public:
        /**
         * <summary>
         * Crée un collider de type boîte avec une taille donnée.
         * </summary>
         */
        BoxColliderComponent(const glm::vec3& size, bool isTrigger = false);

        /**
         * <summary>
         * Prépare le collider lors de l'initialisation.
         * </summary>
         */
        void Awake() override;
        /**
         * <summary>
         * Construit la forme physique correspondant à la boîte.
         * </summary>
         */
        void CreateShape() override;
    };
}
