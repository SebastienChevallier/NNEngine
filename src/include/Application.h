#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "AEntity.h"
#include "AComponent.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "VulkanManager.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"
#include "UISystem.h"
#include "InputSystem.h"
#include "ScriptSystem.h"
#include "PlaneCollider.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "InputManager.h"
#include "ISystem.h"
#include "SystemManager.h"

namespace NNE { class AEntity; }
namespace JPH { class BodyID; }

namespace NNE::Component::Physics { class ColliderComponent; }

namespace NNE::Systems {
    class VulkanManager;
    class PhysicsSystem;
    class RenderSystem;
    class UISystem;
    class InputSystem;
    class ScriptSystem;
    class ISystem;
        class Application
        {
        protected:

                std::map<int, int> _link;
                static Application* Instance;
                /*GLFWwindow* window;*/
                float delta;
                /**
                 * <summary>
                 * Calcule le temps écoulé entre deux frames.
                 * </summary>
                 */
                float GetDeltaTime();

                static int _genericID;

		

	private:
		/*VkInstance instance;*/


	public:
		const uint32_t WIDTH = 960;
                const uint32_t HEIGHT = 540;
                /**
                 * <summary>
                 * Retourne l'instance unique de l'application.
                 * </summary>
                 */
                static Application* GetInstance();
                /**
                 * <summary>
                 * Construit l'application et initialise les systèmes principaux.
                 * </summary>
                 */
                Application();
                /**
                 * <summary>
                 * Nettoie les ressources utilisées par l'application.
                 * </summary>
                 */
                ~Application();
                NNE::Systems::VulkanManager* VKManager;
                NNE::Systems::PhysicsSystem* physicsSystem;
                NNE::Systems::UISystem* uiSystem;
                NNE::Systems::RenderSystem* renderSystem;
                NNE::Systems::InputSystem* inputSystem;
                NNE::Systems::ScriptSystem* scriptSystem;
                std::vector<NNE::AEntity*> _entities;
                std::vector<NNE::Systems::ISystem*>& _systems;

                /**
                 * <summary>
                 * Prépare l'application et démarre les différents systèmes.
                 * </summary>
                 */
                void Init();
                /**
                 * <summary>
                 * Exécute la boucle principale de mise à jour.
                 * </summary>
                 */
                void Update();
                /**
                 * <summary>
                 * Crée la fenêtre et initialise les entrées.
                 * </summary>
                 */
                void Open();
                /**
                 * <summary>
                 * Ferme proprement l'application.
                 * </summary>
                 */
                void Quit();

                /**
                 * <summary>
                 * Génère un identifiant unique pour les entités.
                 * </summary>
                 */
                int GenerateID();

                /**
                 * <summary>
                 * Crée une nouvelle entité gérée par l'application.
                 * </summary>
                 */
                NNE::AEntity* CreateEntity();

                std::unordered_map<JPH::BodyID, NNE::Component::Physics::ColliderComponent*> colliderMap;

                /**
                 * <summary>
                 * Associe un collider à son identifiant physique.
                 * </summary>
                 */
                void RegisterCollider(JPH::BodyID id, NNE::Component::Physics::ColliderComponent* collider) {
                        colliderMap[id] = collider;
                }

                /**
                 * <summary>
                 * Récupère le collider lié à un identifiant physique.
                 * </summary>
                 */
                NNE::Component::Physics::ColliderComponent* GetCollider(JPH::BodyID id) {
                        auto it = colliderMap.find(id);
                        return it != colliderMap.end() ? it->second : nullptr;
                }

                /**
                 * <summary>
                 * Retire un collider du suivi par identifiant.
                 * </summary>
                 */
                void UnregisterCollider(JPH::BodyID id) {
                        colliderMap.erase(id);
                }
        };
}


