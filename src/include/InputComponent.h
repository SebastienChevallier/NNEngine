#pragma once

#include "AComponent.h"
#include <string>
#include <unordered_map>

namespace NNE::Component::Input {

struct AxisAction {
    int positiveKey;
    int negativeKey;
    float value{0.0f};
};

struct ButtonAction {
    int key;
    bool pressed{false};
    bool justPressed{false};
    bool justReleased{false};
};

class InputComponent : public NNE::Component::AComponent {
public:
    std::unordered_map<std::string, AxisAction> axes;
    std::unordered_map<std::string, ButtonAction> buttons;

    void AddAxis(const std::string &name, int positiveKey, int negativeKey) {
        axes[name] = {positiveKey, negativeKey, 0.0f};
    }

    void AddButton(const std::string &name, int key) {
        buttons[name] = {key, false, false, false};
    }

    float GetAxis(const std::string &name) const {
        auto it = axes.find(name);
        return it != axes.end() ? it->second.value : 0.0f;
    }

    bool GetButton(const std::string &name) const {
        auto it = buttons.find(name);
        return it != buttons.end() ? it->second.pressed : false;
    }

    bool GetButtonDown(const std::string &name) const {
        auto it = buttons.find(name);
        return it != buttons.end() ? it->second.justPressed : false;
    }

    bool GetButtonUp(const std::string &name) const {
        auto it = buttons.find(name);
        return it != buttons.end() ? it->second.justReleased : false;
    }
};

}

