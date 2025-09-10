#pragma once

namespace NNE { class AEntity; }

namespace NNE::Component {
        class AComponent
        {
        protected:
                int _id;
                NNE::AEntity* _entity;

        public:
                /**
                 * <summary>
                 * Constructeur de base du composant.
                 * </summary>
                 */
                AComponent();
                ~AComponent() = default;

                /**
                 * <summary>
                 * Appelé lorsque le composant est initialisé.
                 * </summary>
                 */
                virtual void Awake();
                /**
                 * <summary>
                 * Appelé au démarrage du composant.
                 * </summary>
                 */
                virtual void Start();
                /**
                 * <summary>
                 * Met à jour le composant chaque frame.
                 * </summary>
                 */
                virtual void Update(float deltaTime);
                /**
                 * <summary>
                 * Effectue les mises à jour après l'Update principal.
                 * </summary>
                 */
                virtual void LateUpdate(float deltaTime);

                /**
                 * <summary>
                 * Retourne l'identifiant du composant.
                 * </summary>
                 */
                int GetID() const;
                /**
                 * <summary>
                 * Obtient l'entité propriétaire.
                 * </summary>
                 */
                NNE::AEntity* GetEntity();
                /**
                 * <summary>
                 * Associe le composant à une entité.
                 * </summary>
                 */
                void SetEntity(NNE::AEntity* entity);
        };
}


