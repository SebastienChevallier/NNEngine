#pragma once
#include "AComponent.h"
#include <glm/glm.hpp>
#include "IDebugUI.h"

namespace NNE::Component::Render {
    class LightComponent : public NNE::Component::AComponent, public NNE::IDebugUI {
    private:
        glm::vec3 direction;
        glm::vec3 color;
        float intensity;
        float ambient;

    public:
        /**
         * <summary>
         * Crée un composant de lumière directionnelle.
         * </summary>
         */
        LightComponent(const glm::vec3& dir = glm::vec3(-0.2f, -1.f, -0.3f),
                       const glm::vec3& color = glm::vec3(1.f),
                       float intensity = 1.f,
                       float ambient = 0.25f);
        /**
         * <summary>
         * Met à jour la direction selon la transformation de l'entité.
         * </summary>
         */
        void Update(float deltaTime) override;

        /**
         * <summary>
         * Définit la direction de la lumière.
         * </summary>
         */
        void SetDirection(const glm::vec3& dir);
        /**
         * <summary>
         * Retourne la direction actuelle de la lumière.
         * </summary>
         */
        glm::vec3 GetDirection() const;
        /**
         * <summary>
         * Modifie la couleur de la lumière.
         * </summary>
         */
        void SetColor(const glm::vec3& col);
        /**
         * <summary>
         * Retourne la couleur de la lumière.
         * </summary>
         */
        glm::vec3 GetColor() const;
        /**
         * <summary>
         * Définit l'intensité de la lumière.
         * </summary>
         */
        void SetIntensity(float i);
        /**
         * <summary>
         * Retourne l'intensité de la lumière.
         * </summary>
         */
        float GetIntensity() const;
        /**
         * <summary>
         * Définit la composante ambiante.
         * </summary>
         */
        void SetAmbient(float a);
        /**
         * <summary>
         * Retourne la composante ambiante.
         * </summary>
         */
        float GetAmbient() const;

        // Hérité via IDebugUI
        void DrawImGui() override;
    };
}
