#pragma once

#include "AComponent.h"
#include "ColliderComponent.h"
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/Body.h>
#include <Jolt/Physics/Body/BodyID.h>
#include <glm/glm.hpp>

namespace NNE::Component::Physics {

    class RigidbodyComponent : public NNE::Component::AComponent {
    private:
        JPH::BodyID bodyID;
        float mass;
        bool isKinematic;

    public:
        /**
         * <summary>
         * Initialise un rigidbody avec masse et type souhaités.
         * </summary>
         */
        RigidbodyComponent(float mass = 1.0f, bool kinematic = false);
        /**
         * <summary>
         * Libère les ressources du rigidbody.
         * </summary>
         */
        ~RigidbodyComponent();

        /**
         * <summary>
         * Crée le corps physique au démarrage.
         * </summary>
         */
        void Awake() override;
        /**
         * <summary>
         * Synchronise la physique à chaque frame.
         * </summary>
         */
        void Update(float deltaTime) override;
        /**
         * <summary>
         * Renvoie l'identifiant du corps physique.
         * </summary>
         */
        JPH::BodyID GetBodyID() const;

        /**
         * <summary>
         * Définit la vitesse linéaire du corps.
         * </summary>
         */
        void SetLinearVelocity(glm::vec3 velocity);
        /**
         * <summary>
         * Obtient la vitesse linéaire actuelle.
         * </summary>
         */
        glm::vec3 GetLinearVelocity() const;
    };

}
