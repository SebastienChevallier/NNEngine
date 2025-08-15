#pragma once
#include "AComponent.h"
#include "TransformComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "AEntity.h"

namespace NNE::Component::Render {
    class CameraComponent : public NNE::Component::AComponent {
    private:
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        float fov;
        float aspectRatio;
        float nearPlane;
        float farPlane;

    public:
        /**
         * <summary>
         * Initialise la caméra avec ses paramètres de projection.
         * </summary>
         */
        CameraComponent(float fov = 45.0f, float aspectRatio = 16.0f/9.0f, float nearPlane = 0.1f, float farPlane = 100.0f);
        /**
         * <summary>
         * Met à jour la caméra chaque frame.
         * </summary>
         */
        virtual void Update(float deltaTime) override;
        /**
         * <summary>
         * Définit les paramètres de projection de la caméra.
         * </summary>
         */
        void SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);
        /**
         * <summary>
         * Met à jour la matrice de vue selon la position et la cible.
         * </summary>
         */
        void UpdateViewMatrix(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);

        /**
         * <summary>
         * Retourne la matrice de vue actuelle.
         * </summary>
         */
        glm::mat4 GetViewMatrix() const { return viewMatrix; }
        /**
         * <summary>
         * Retourne la matrice de projection actuelle.
         * </summary>
         */
        glm::mat4 GetProjectionMatrix() const { return projectionMatrix; }
        /**
         * <summary>
         * Récupère le champ de vision de la caméra.
         * </summary>
         */
        float GetFOV() { return fov; }
        /**
         * <summary>
         * Renvoie le ratio d'aspect de la caméra.
         * </summary>
         */
        float GetAspectRatio() { return aspectRatio; }
        /**
         * <summary>
         * Donne la distance du plan proche.
         * </summary>
         */
        float GetNearPlane() { return nearPlane; }
        /**
         * <summary>
         * Donne la distance du plan éloigné.
         * </summary>
         */
        float GetFarPlane() { return farPlane; }
    };
}
