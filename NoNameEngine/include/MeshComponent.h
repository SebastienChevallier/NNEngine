#pragma once
#include "AComponent.h" 
#include <string>

namespace NNE {
    class AComponent;
	class MeshComponent : public AComponent
	{
    private:
        std::string modelPath;
        std::string texturePath;

    public:
        MeshComponent();   

        /*virtual void Awake() override;
        virtual void Start() override;
        virtual void Update(float deltaTime) override;
        virtual void LateUpdate(float deltaTime) override;*/

        std::string GetModelPath() const;
        std::string GetTexturePath() const;
        void SetModelPath(std::string path);
        void SetTexturePath(std::string path);
	};
}
	

