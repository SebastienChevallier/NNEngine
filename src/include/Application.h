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
#include "PhysicsManager.h"
#include "PlaneCollider.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "InputManager.h"

namespace NNE::Systems {
        class Application
        {
        protected:

                std::map<int, int> _link;
                static Application* Instance;
                /*GLFWwindow* window;*/
                float delta;
                float GetDeltaTime();

                static int _genericID;

		

	private:
		/*VkInstance instance;*/


	public:
		const uint32_t WIDTH = 960;
                const uint32_t HEIGHT = 540;
                static Application* GetInstance();
                Application();
                ~Application();
                NNE::Systems::VulkanManager* VKManager;
                NNE::Systems::PhysicsManager* physicsManager;
                std::vector<NNE::AEntity*> _entities;

		void Init();
		void Update();
		void Open();
		void Quit();

		int GenerateID();

                NNE::AEntity* CreateEntity();

                std::unordered_map<JPH::BodyID, NNE::Component::Physics::ColliderComponent*> colliderMap;

                void RegisterCollider(JPH::BodyID id, NNE::Component::Physics::ColliderComponent* collider) {
                        colliderMap[id] = collider;
                }

                NNE::Component::Physics::ColliderComponent* GetCollider(JPH::BodyID id) {
                        auto it = colliderMap.find(id);
                        return it != colliderMap.end() ? it->second : nullptr;
                }

                void UnregisterCollider(JPH::BodyID id) {
                        colliderMap.erase(id);
                }
        };
}


