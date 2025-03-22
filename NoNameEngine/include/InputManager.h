#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <unordered_map>

namespace NNE {

    class InputManager {
    public:
        static void Init(GLFWwindow* win);
        static void Update();  // Met à jour les états des touches
        static bool IsKeyPressed(int key);
        static bool IsKeyJustPressed(int key);
        static bool IsKeyJustReleased(int key);
        static glm::vec2 GetMousePosition();
        static bool IsMouseButtonPressed(int button);

    private:
        static inline GLFWwindow* window = nullptr;
        static inline std::unordered_map<int, bool> currentKeys;
        static inline std::unordered_map<int, bool> previousKeys;
    };
}
#endif