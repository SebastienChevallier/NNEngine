#pragma once
#include <iostream>
#include <vector>
#include <chrono>

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
                bool _playMode = false;
                bool _sceneViewActive = true;
                NNE::AEntity* _editorCameraEntity = nullptr;
                float _deltaTime = 0.0f;
                float _gameDeltaTime = 0.0f;
                std::chrono::high_resolution_clock::time_point _lastFrameTime;


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
                float GetDeltaTime() const;
                float GetGameDeltaTime() const;
                bool IsPlayMode() const;
                void SetPlayMode(bool playing);
                bool IsSceneViewActive() const;
                void SetSceneViewActive(bool active);
                NNE::AEntity* GetEditorCameraEntity() const { return _editorCameraEntity; }

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


