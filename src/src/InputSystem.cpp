#include "InputSystem.h"
#include "Application.h"
#include "VulkanManager.h"

namespace NNE::Systems {

/**
 * <summary>
 * Met à jour les valeurs des axes et boutons pour chaque composant d'entrée.
 * </summary>
 */
void InputSystem::Update(float deltaTime)
{
    (void)deltaTime;
    InputManager::Update();
    if (InputManager::IsKeyJustPressed(GLFW_KEY_F3))
    {
        Application::GetInstance()->VKManager->requestShadowDebug();
    }
    for (auto* input : _inputs)
    {
        for (auto& pair : input->buttons)
        {
            auto& btn = pair.second;
            bool pressed = InputManager::IsKeyPressed(btn.key);
            btn.justPressed = pressed && !btn.pressed;
            btn.justReleased = !pressed && btn.pressed;
            btn.pressed = pressed;
        }
        for (auto& pair : input->axes)
        {
            auto& axis = pair.second;
            float value = 0.0f;
            if (InputManager::IsKeyPressed(axis.positiveKey))
                value += 1.0f;
            if (InputManager::IsKeyPressed(axis.negativeKey))
                value -= 1.0f;
            axis.value = value;
        }
    }
}

/**
 * <summary>
 * Ajoute un composant d'entrée s'il correspond au type attendu.
 * </summary>
 */
void InputSystem::RegisterComponent(NNE::Component::AComponent* component)
{
    if (auto* input = dynamic_cast<NNE::Component::Input::InputComponent*>(component))
    {
        _inputs.push_back(input);
    }
}

} // namespace NNE::Systems
