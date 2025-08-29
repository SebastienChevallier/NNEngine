#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <unordered_map>

namespace NNE::Systems {

    class InputManager {
    public:
        /**
         * <summary>
         * Initialise la gestion des entrées avec la fenêtre donnée.
         * </summary>
         */
        static void Init(GLFWwindow* win);
        /**
         * <summary>
         * Met à jour l'état des entrées chaque frame.
         * </summary>
         */
        static void Update();
        /**
         * <summary>
         * Vérifie si une touche est maintenue enfoncée.
         * </summary>
         */
        static bool IsKeyPressed(int key);
        /**
         * <summary>
         * Vérifie si une touche vient d'être pressée.
         * </summary>
         */
        static bool IsKeyJustPressed(int key);
        /**
         * <summary>
         * Vérifie si une touche vient d'être relâchée.
         * </summary>
         */
        static bool IsKeyJustReleased(int key);
        /**
         * <summary>
         * Retourne la position actuelle de la souris.
         * </summary>
         */
        static glm::vec2 GetMousePosition();
        /**
         * <summary>
         * Indique si un bouton de souris est pressé.
         * </summary>
         */
        static bool IsMouseButtonPressed(int button);
        static inline bool ShowMouseCursor;

    private:
        static inline GLFWwindow* window = nullptr;
        static inline std::unordered_map<int, bool> currentKeys;
        static inline std::unordered_map<int, bool> previousKeys;
    };
}
#endif
