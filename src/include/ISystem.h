#pragma once

namespace NNE { namespace Component { class AComponent; } }

namespace NNE::Systems {
class ISystem {
public:
    virtual ~ISystem() = default;
    /**
     * <summary>
     * Prépare le système avant son utilisation.
     * </summary>
     */
    virtual void Awake() = 0;
    /**
     * <summary>
     * Démarre le système.
     * </summary>
     */
    virtual void Start() = 0;
    /**
     * <summary>
     * Met à jour le système chaque frame.
     * </summary>
     */
    virtual void Update(float deltaTime) = 0;
    /**
     * <summary>
     * Applique les mises à jour tardives du système.
     * </summary>
     */
    virtual void LateUpdate(float deltaTime) = 0;
    /**
     * <summary>
     * Enregistre un composant auprès du système.
     * </summary>
     */
    virtual void RegisterComponent(NNE::Component::AComponent* component) {}
};
}
