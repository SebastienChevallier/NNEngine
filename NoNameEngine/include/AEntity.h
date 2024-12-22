#pragma once
#include <iostream>


namespace NNE {
	class AEntity
	{
	protected: 
		int _ID;
		std::string _Name;

	public:
		AEntity();
		~AEntity();

		int GetID();
		std::string GetName();

		void Awake();
		void Start();
		void Update(float delta);
		void LateUpdate(float delta);

	};
}


