#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "AEntity.h"
#include "AComponent.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "VulkanManager.h"



namespace NNE {
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
		const uint32_t WIDTH = 800;
		const uint32_t HEIGHT = 600;
		static Application* GetInstance();
		Application();
		~Application();
		NNE::VulkanManager* VKManager;
		std::vector<AEntity*> _entities;

		void Init();
		void Update();
		void Open();
		void Quit();

		int GenerateID();

		AEntity* CreateEntity();
	};
}


