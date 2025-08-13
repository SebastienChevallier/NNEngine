#pragma once
#include "AComponent.h"

namespace NNE::Component::Physics { class ColliderComponent; }

namespace NNE::Component {
        class MonoComponent : public AComponent
        {
        public:
                virtual void Awake() override;
                virtual void Start() override;
                virtual void Update(float deltaTime) override;
                virtual void LateUpdate(float deltaTime) override;

                virtual void OnHit(NNE::Component::Physics::ColliderComponent* other);
                virtual void OnTriggerHit(NNE::Component::Physics::ColliderComponent* other);
        };
}


