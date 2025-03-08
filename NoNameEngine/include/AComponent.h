#pragma once

namespace NNE {
	class AComponent
	{
	protected:
		int _id;

	public:
		AComponent();
		~AComponent() = default;
		
		virtual void Awake();
		virtual void Start();
		virtual void Update(float deltaTime);
		virtual void LateUpdate(float deltaTime);

		int GetID();
	};
}


