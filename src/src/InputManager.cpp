#include "InputManager.h"

namespace NNE::Systems {

/**
 * <summary>
 * Initialise l'InputManager avec la fenêtre GLFW.
 * </summary>
 */
void InputManager::Init(GLFWwindow* win) {
    window = win;
}

/**
 * <summary>
 * Met à jour l'état des touches et de la souris.
 * </summary>
 */
void InputManager::Update() {
    previousKeys = currentKeys;
    for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
        currentKeys[key] = glfwGetKey(window, key) == GLFW_PRESS;
    }
}

/**
 * <summary>
 * Indique si la touche est actuellement maintenue.
 * </summary>
 */
bool InputManager::IsKeyPressed(int key) {
    return currentKeys[key];
}

/**
 * <summary>
 * Détecte si la touche vient d'être enfoncée cette frame.
 * </summary>
 */
bool InputManager::IsKeyJustPressed(int key) {
    return currentKeys[key] && !previousKeys[key];
}

/**
 * <summary>
 * Indique si la touche vient d'être relâchée.
 * </summary>
 */
bool InputManager::IsKeyJustReleased(int key) {
    return !currentKeys[key] && previousKeys[key];
}

/**
 * <summary>
 * Retourne la position actuelle du curseur de la souris.
 * </summary>
 */
glm::vec2 InputManager::GetMousePosition() {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return glm::vec2(x, y);
}

/**
 * <summary>
 * Vérifie si un bouton de la souris est pressé.
 * </summary>
 */
bool InputManager::IsMouseButtonPressed(int button) {
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

} // namespace NNE::Systems
