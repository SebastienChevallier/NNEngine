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

		template<typename T>
		T* AddComponent();

		template<typename T>
		T* GetComponent();

	};

	template<typename T>
	T* NNE::AEntity::AddComponent()
	{
		T* component = new T();
		components.push_back(component);		
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
}


