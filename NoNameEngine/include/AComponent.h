#pragma once

namespace NNE {
	class AEntity;
	class AComponent
	{
	protected:
		int _id;
		AEntity* _entity;

	public:
		AComponent();
		~AComponent() = default;
		
		virtual void Awake();
		virtual void Start();
		virtual void Update(float deltaTime);
		virtual void LateUpdate(float deltaTime);

		int GetID();
		AEntity* GetEntity();
		void SetEntity(AEntity* entity);
	};
}


