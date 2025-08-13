#pragma once

namespace NNE { class AEntity; }

namespace NNE::Component {
        class AComponent
        {
        protected:
                int _id;
                NNE::AEntity* _entity;

        public:
                AComponent();
                ~AComponent() = default;

                virtual void Awake();
                virtual void Start();
                virtual void Update(float deltaTime);
                virtual void LateUpdate(float deltaTime);

                int GetID();
                NNE::AEntity* GetEntity();
                void SetEntity(NNE::AEntity* entity);
        };
}


