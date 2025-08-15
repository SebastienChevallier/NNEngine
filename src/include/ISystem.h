#pragma once

namespace NNE { namespace Component { class AComponent; } }

namespace NNE::Systems {
class ISystem {
public:
    virtual ~ISystem() = default;
    virtual void Awake() = 0;
    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void LateUpdate(float deltaTime) = 0;
    virtual void RegisterComponent(NNE::Component::AComponent* component) {}
};
}
