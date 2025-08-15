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

    /**
     * <summary>
     * Ajoute un axe de contrôle basé sur deux touches.
     * </summary>
     */
    void AddAxis(const std::string &name, int positiveKey, int negativeKey) {
        axes[name] = {positiveKey, negativeKey, 0.0f};
    }

    /**
     * <summary>
     * Ajoute un bouton à surveiller.
     * </summary>
     */
    void AddButton(const std::string &name, int key) {
        buttons[name] = {key, false, false, false};
    }

    /**
     * <summary>
     * Retourne la valeur actuelle de l'axe demandé.
     * </summary>
     */
    float GetAxis(const std::string &name) const {
        auto it = axes.find(name);
        return it != axes.end() ? it->second.value : 0.0f;
    }

    /**
     * <summary>
     * Indique si le bouton est actuellement pressé.
     * </summary>
     */
    bool GetButton(const std::string &name) const {
        auto it = buttons.find(name);
        return it != buttons.end() ? it->second.pressed : false;
    }

    /**
     * <summary>
     * Indique si le bouton vient d'être pressé.
     * </summary>
     */
    bool GetButtonDown(const std::string &name) const {
        auto it = buttons.find(name);
        return it != buttons.end() ? it->second.justPressed : false;
    }

    /**
     * <summary>
     * Indique si le bouton vient d'être relâché.
     * </summary>
     */
    bool GetButtonUp(const std::string &name) const {
        auto it = buttons.find(name);
        return it != buttons.end() ? it->second.justReleased : false;
    }
};

}

