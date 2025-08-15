#include "InputSystem.h"

using namespace NNE::Systems;

void InputSystem::Update(float deltaTime)
{
    (void)deltaTime;
    InputManager::Update();
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

void InputSystem::RegisterComponent(NNE::Component::AComponent* component)
{
    if (auto* input = dynamic_cast<NNE::Component::Input::InputComponent*>(component))
    {
        _inputs.push_back(input);
    }
}

