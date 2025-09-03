#pragma once
#include "AComponent.h"
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>

namespace NNE::Component::Physics
{
    class ColliderComponent : public NNE::Component::AComponent
    {
    protected:
        JPH::ShapeRefC shape;
        bool isTrigger = false;

    public:
        JPH::BodyID bodyID;

        /**
         * <summary>
         * Constructeur du collider, permet de définir s'il est trigger.
         * </summary>
         */
        ColliderComponent(bool isTrigger = false) : isTrigger(isTrigger) {}
        /**
         * <summary>
         * Destructeur virtuel pour un nettoyage adéquat.
         * </summary>
         */
        virtual ~ColliderComponent() = default;

        /**
         * <summary>
         * Génère la forme physique utilisée par le collider.
         * </summary>
         */
        virtual void CreateShape() = 0;

        /**
         * <summary>
         * Retourne la forme associée au collider.
         * </summary>
         */
        JPH::ShapeRefC GetShape() const { return shape; }

        /**
         * <summary>
         * Indique si ce collider est un trigger (n'engendre pas de collision physique).
         * </summary>
         */
        bool IsTrigger() const { return isTrigger; }

        /**
         * <summary>
         * Définit ce collider comme trigger ou non.
         * </summary>
         */
        void SetTrigger(bool trigger) { isTrigger = trigger; }

        /**
         * <summary>
         * Réagit lorsqu'une collision est détectée.
         * </summary>
         */
        virtual void OnHit(ColliderComponent* other);

        /**
         * <summary>
         * Réagit lorsqu'une collision de type trigger survient.
         * </summary>
         */
        virtual void OnTriggerHit(ColliderComponent* other);

        /**
         * <summary>
         * Obtient l'identifiant physique du corps associé.
         * </summary>
         */
        JPH::BodyID GetBodyID() const { return bodyID; }
    };
}
