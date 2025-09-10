#pragma once
#include <iostream>
#include <vector>

#include <Jolt/Jolt.h>

namespace NNE { class AEntity; }

namespace NNE::Systems {
class VulkanManager;

class Application
{
        protected:

                static Application* Instance;
                /*GLFWwindow* window;*/
                float delta;

		

	private:
		/*VkInstance instance;*/


	public:
		int WIDTH = 960;
        int HEIGHT = 540;
                /**
                 * <summary>
                 * Retourne l'instance unique de l'application.
                 * </summary>
                 */
                static Application* GetInstance();

                /**
                 * <summary>
                 * Calcule le temps écoulé entre deux frames.
                 * </summary>
                 */
                float GetDeltaTime();

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
                std::vector<NNE::AEntity*> _entities;

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
                 * Crée une nouvelle entité gérée par l'application.
                 * </summary>
                 */
                NNE::AEntity* CreateEntity();

};
}


