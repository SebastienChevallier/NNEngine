#pragma once
#include <iostream>
#include <vector>
#include <map>

#include "AEntity.h"
#include "AComponent.h"
#include "VulkanManager.h"



namespace NNE {
	class Application
	{
	protected:
		std::vector<AEntity*> _entities;
		std::vector<AComponent*> _components;
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

		void Init();		
		void Update();
		void Open();
		void Quit();

		int GenerateID();

		AEntity* CreateEntity();

		template<typename T>
		T* CreateSpecificEntity();

		template<typename T>
		T* AddComponent(AEntity* entity);
		
		/*GLFWwindow* CreateGLFWWindow(int width, int height);*/
		
	};

	template<typename T>
	T* NNE::Application::CreateSpecificEntity()
	{
		T* entity = new T();
		_entities.push_back(entity);
		return entity;
	}

	template<typename T>
	T* NNE::Application::AddComponent(NNE::AEntity* entity)
	{
		T* component = new T();
		_components.push_back(component);
		_link[component->GetID()] = entity->GetID();
		return component;
	}
}


