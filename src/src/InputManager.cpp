#include "InputManager.h"

namespace NNE {

    void InputManager::Init(GLFWwindow* win) {
        window = win;
    }

    void InputManager::Update() {
        // Copier l'état précédent des touches
        previousKeys = currentKeys;

        // Met à jour l'état actuel des touches
        for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
            currentKeys[key] = glfwGetKey(window, key) == GLFW_PRESS;
        }
    }

    bool InputManager::IsKeyPressed(int key) {
        return currentKeys[key];
    }

    bool InputManager::IsKeyJustPressed(int key) {
        return currentKeys[key] && !previousKeys[key];
    }

    bool InputManager::IsKeyJustReleased(int key) {
        return !currentKeys[key] && previousKeys[key];
    }

    glm::vec2 InputManager::GetMousePosition() {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return glm::vec2(x, y);
    }

    bool InputManager::IsMouseButtonPressed(int button) {
        return glfwGetMouseButton(window, button) == GLFW_PRESS;
    }

}