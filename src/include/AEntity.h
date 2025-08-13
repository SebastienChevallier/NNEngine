#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "AComponent.h"
#include "TransformComponent.h"

namespace NNE {
        class AEntity
        {
        protected:
                int _ID;
                std::string _Name;

        public:
                AEntity();
                ~AEntity();
                NNE::Component::TransformComponent* transform;
                std::vector<NNE::Component::AComponent*> components;

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
                for (NNE::Component::AComponent* component : components) {
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
                std::vector<T*> ref;
                for (NNE::Component::AComponent* component : components) {
                        T* casted = dynamic_cast<T*>(component);
                        if (casted) {
                                ref.push_back(casted);
                        }
                }
                return ref;
        }
}


