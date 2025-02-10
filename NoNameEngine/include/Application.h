#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "AEntity.h"
#include "AComponent.h"
#include "MeshComponent.h"
#include "VulkanManager.h"

namespace NNE {
	class AEntity;  // Déclaration avancée
	class VulkanManager;  // Déclaration avancée
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
		/*void CreateVulkanInstance();
		bool checkValidationLayerSupport();
		void pickPhysicalDevice();*/
		std::vector<AEntity*> _entities;

		void Init();		
		void Update();
		void Open();
		void Quit();

		int GenerateID();
		AEntity* CreateEntity();

		template<typename T>
		T* CreateSpecificEntity();
	};

	template<typename T>
	T* NNE::Application::CreateSpecificEntity()
	{
		T* entity = new T();
		_entities.push_back(entity);
		return entity;
	}

	
}


