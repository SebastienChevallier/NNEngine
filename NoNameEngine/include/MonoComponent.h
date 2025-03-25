#pragma once
#include "AComponent.h"
//#include "ColliderComponent.h"

namespace NNE {
	class ColliderComponent;
	class MonoComponent : public AComponent
	{
	public:
		virtual void Awake() override;
		virtual void Start() override;
		virtual void Update(float deltaTime) override;
		virtual void LateUpdate(float deltaTime) override;

		virtual void OnHit(NNE::ColliderComponent* other);
		virtual void OnTriggerHit(NNE::ColliderComponent* other);
	};
}


