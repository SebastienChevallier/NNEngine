#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>
#include <Jolt/Physics/Body/BodyID.h>
#include <Jolt/RegisterTypes.h>
#include "ISystem.h"
#include <vector>
#include <array>
#include <unordered_map>
#include <glm/glm.hpp>
#include "AEntity.h"

namespace NNE { namespace Component { class AComponent; } }
namespace NNE { namespace Component { namespace Physics { class RigidbodyComponent; class ColliderComponent; } } }

namespace NNE::Systems {

    namespace Layers {
        constexpr JPH::ObjectLayer DEFAULT = 0;
        constexpr JPH::ObjectLayer PLAYER = 1;
        constexpr JPH::ObjectLayer RAYCAST = 2;
    }

    class PhysicsSystem : public ISystem {
    private:
        static PhysicsSystem* instance;
        JPH::PhysicsSystem physicsSystem;
        JPH::TempAllocatorImpl* tempAllocator;
        JPH::JobSystemThreadPool* jobSystem;
        std::vector<NNE::Component::Physics::RigidbodyComponent*> rigidbodies;
        std::vector<NNE::Component::Physics::ColliderComponent*> colliders;
        std::unordered_map<JPH::BodyID, NNE::Component::Physics::ColliderComponent*> colliderMap;
        std::array<uint32_t, 32> layerMasks;
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
        void UnregisterComponent(NNE::Component::AComponent* component);
        /**
         * <summary>
         * Accède à l'objet PhysicsSystem de Jolt.
         * </summary>
         */
        JPH::PhysicsSystem* GetPhysicsSystem();
        /**
         * <summary>
         * Retourne l'instance unique du système physique.
         * </summary>
         */
        static PhysicsSystem* GetInstance();

        /**
         * <summary>
         * Définit si deux couches doivent entrer en collision.
         * </summary>
         */
        void SetLayerCollision(JPH::ObjectLayer layer1, JPH::ObjectLayer layer2, bool shouldCollide);

        /**
         * <summary>
         * Vérifie si deux couches peuvent entrer en collision.
         * </summary>
         */
        bool LayersShouldCollide(JPH::ObjectLayer layer1, JPH::ObjectLayer layer2) const;

        /**
         * <summary>
         * Associe un collider à son identifiant physique.
         * </summary>
         */
        void RegisterCollider(JPH::BodyID id, NNE::Component::Physics::ColliderComponent* collider);

        /**
         * <summary>
         * Récupère le collider lié à un identifiant physique.
         * </summary>
         */
        NNE::Component::Physics::ColliderComponent* GetCollider(JPH::BodyID id);

        /**
         * <summary>
         * Retire un collider du suivi par identifiant.
         * </summary>
         */
        void UnregisterCollider(JPH::BodyID id);

        struct RaycastHit {
            JPH::BodyID bodyID;
            JPH::SubShapeID subShapeID;
            float fraction;
            glm::vec3 position;
            glm::vec3 normal;
			NNE::AEntity* entity;
        };

        static bool Raycast(glm::vec3 origin, glm::vec3 direction, float distance,
                            RaycastHit& outHit,
                            JPH::ObjectLayer rayLayer = Layers::RAYCAST);

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
