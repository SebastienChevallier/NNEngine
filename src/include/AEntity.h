#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "AComponent.h"
#include "TransformComponent.h"
#include "SystemManager.h"

namespace NNE {
        class AEntity
        {
        protected:
                int _ID;
                std::string _Name;

        public:
                /**
                 * <summary>
                 * Construit une entité vide.
                 * </summary>
                 */
                AEntity();
                /**
                 * <summary>
                 * Détruit l'entité et ses composants.
                 * </summary>
                 */
                ~AEntity();
                NNE::Component::TransformComponent* transform;
                std::vector<NNE::Component::AComponent*> components;

                /**
                 * <summary>
                 * Retourne l'identifiant unique de l'entité.
                 * </summary>
                 */
                int GetID();
                /**
                 * <summary>
                 * Renvoie le nom de l'entité.
                 * </summary>
                 */
                std::string GetName();

				void SetName(const std::string& name);

                /**
                 * <summary>
                 * Appelée lors de l'initialisation de l'entité.
                 * </summary>
                 */
                void Awake();
                /**
                 * <summary>
                 * Appelée au démarrage de l'entité.
                 * </summary>
                 */
                void Start();
                /**
                 * <summary>
                 * Met à jour l'entité à chaque frame.
                 * </summary>
                 */
                void Update(float delta);
                /**
                 * <summary>
                 * Effectue les mises à jour tardives de l'entité.
                 * </summary>
                 */
                void LateUpdate(float delta);

                /**
                 * <summary>
                 * Ajoute un composant de type T à l'entité.
                 * </summary>
                 */
                template<typename T, typename... Args>
                T* AddComponent(Args&&... args);

                /**
                 * <summary>
                 * Récupère le premier composant du type demandé.
                 * </summary>
                 */
                template<typename T>
                T* GetComponent();

                /**
                 * <summary>
                 * Renvoie tous les composants du type demandé.
                 * </summary>
                 */
                template<typename T>
                std::vector<T*> GetComponents();

	};

/**
 * <summary>
 * Instancie et attache un composant à l'entité.
 * </summary>
 */
template<typename T, typename... Args>
T* NNE::AEntity::AddComponent(Args&&... args)
        {
                T* component = new T(std::forward<Args>(args)...);
                components.push_back(component);
                component->SetEntity(this);
                NNE::Systems::SystemManager::GetInstance()->RegisterComponent(component);
                return component;
        }

/**
 * <summary>
 * Recherche un composant du type donné.
 * </summary>
 */
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

/**
 * <summary>
 * Collecte tous les composants correspondant au type donné.
 * </summary>
 */
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


