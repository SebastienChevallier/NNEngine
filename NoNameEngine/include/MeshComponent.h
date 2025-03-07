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
        uint32_t indexOffset = 0;
        uint32_t indexCount = 0;

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

        void setIndexOffset(uint32_t offset) { indexOffset = offset; }
        void setIndexCount(uint32_t count) { indexCount = count; }
        uint32_t getIndexOffset() const { return indexOffset; }
        uint32_t getIndexCount() const { return indexCount; }
	};
}
	

