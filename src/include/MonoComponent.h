#pragma once
#include "AComponent.h"

namespace NNE::Component::Physics { class ColliderComponent; }

namespace NNE::Component {
        class MonoComponent : public AComponent
        {
        public:
                /**
                 * <summary>
                 * Prépare le composant mono lors de l'initialisation.
                 * </summary>
                 */
                virtual void Awake() override;
                /**
                 * <summary>
                 * Lance le composant mono au démarrage.
                 * </summary>
                 */
                virtual void Start() override;
                /**
                 * <summary>
                 * Met à jour le script mono chaque frame.
                 * </summary>
                 */
                virtual void Update(float deltaTime) override;
                /**
                 * <summary>
                 * Applique les mises à jour tardives du script.
                 * </summary>
                 */
                virtual void LateUpdate(float deltaTime) override;

                /**
                 * <summary>
                 * Réagit à une collision physique.
                 * </summary>
                 */
                virtual void OnHit(NNE::Component::Physics::ColliderComponent* other);
                /**
                 * <summary>
                 * Réagit à une collision de type trigger.
                 * </summary>
                 */
                virtual void OnTriggerHit(NNE::Component::Physics::ColliderComponent* other);
        };
}


