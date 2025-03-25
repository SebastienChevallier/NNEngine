#pragma once
#include <iostream>
#include "AComponent.h"
#include "Application.h"

namespace NNE {	
	class AComponent;	
	class AEntity
	{
	protected: 
		int _ID;
		std::string _Name;	

	public:
		AEntity();
		~AEntity();
		std::vector<AComponent*> components;

		int GetID();
		std::string GetName();

		void Awake();
		void Start();
		void Update(float delta);
		void LateUpdate(float delta);

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args);

		template<typename T>
		T* GetComponent();

		template<typename T>
		std::vector<T*> GetComponents();

	};

	template<typename T, typename... Args>
	T* NNE::AEntity::AddComponent(Args&&... args)
	{
		T* component = new T(std::forward<Args>(args)...);
		components.push_back(component);
		component->SetEntity(this);
		return component;
	}

	template<typename T>
	T* NNE::AEntity::GetComponent()
	{
		for (AComponent* component : components) {
			T* casted = dynamic_cast<T*>(component);
			if (casted) {
				return casted;
			}
		}
		return nullptr;
	}

	template<typename T>
	std::vector<T*> NNE::AEntity::GetComponents()
	{
		std::vector<T*> ref = new std::vector<T*>;
		for (AComponent* component : components) {
			T* casted = dynamic_cast<T*>(component);
			if (casted) {
				ref.push_back(component)
			}
		}
		return ref;
	}
}


