#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/RegisterTypes.h>
#include "ISystem.h"
#include <vector>

namespace NNE { namespace Component { class AComponent; } }
namespace NNE { namespace Component { namespace Physics { class RigidbodyComponent; class ColliderComponent; } } }

namespace NNE::Systems {

    class PhysicsSystem : public ISystem {
    private:
        JPH::PhysicsSystem physicsSystem;
        JPH::TempAllocatorImpl* tempAllocator;
        JPH::JobSystemThreadPool* jobSystem;
        std::vector<NNE::Component::Physics::RigidbodyComponent*> rigidbodies;
        std::vector<NNE::Component::Physics::ColliderComponent*> colliders;
        bool initialized;

    public:
        /**
         * <summary>
         * Construit le système physique et ses dépendances.
         * </summary>
         */
        PhysicsSystem();
        /**
         * <summary>
         * Détruit le système physique et libère les ressources.
         * </summary>
         */
        ~PhysicsSystem();

        /**
         * <summary>
         * Initialise les structures de la bibliothèque Jolt.
         * </summary>
         */
        void Initialize();
        /**
         * <summary>
         * Met à jour la simulation physique.
         * </summary>
         */
        void Update(float deltaTime) override;
        /**
         * <summary>
         * Applique les mises à jour tardives de la physique.
         * </summary>
         */
        void LateUpdate(float deltaTime) override;
        /**
         * <summary>
         * Prépare le système avant le démarrage.
         * </summary>
         */
        void Awake() override;
        /**
         * <summary>
         * Démarre le système physique.
         * </summary>
         */
        void Start() override;
        /**
         * <summary>
         * Enregistre un composant physique.
         * </summary>
         */
        void RegisterComponent(NNE::Component::AComponent* component) override;
        /**
         * <summary>
         * Accède à l'objet PhysicsSystem de Jolt.
         * </summary>
         */
        JPH::PhysicsSystem* GetPhysicsSystem();

        class ContactListenerImpl : public JPH::ContactListener
        {
        public:
            /**
             * <summary>
             * Réagit lorsqu'un contact physique est ajouté.
             * </summary>
             */
            void OnContactAdded(const JPH::Body& body1, const JPH::Body& body2, const JPH::ContactManifold& manifold, JPH::ContactSettings&) override;
        };

        ContactListenerImpl contactListener;
    };

}
