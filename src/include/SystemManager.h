#pragma once

#include <vector>

namespace NNE { namespace Component { class AComponent; } }

namespace NNE::Systems {
class ISystem;

class SystemManager {
private:
    std::vector<ISystem*> _systems;
    static SystemManager* Instance;

public:
    static SystemManager* GetInstance();

    void AddSystem(ISystem* system);
    std::vector<ISystem*>& GetSystems();

    void RegisterComponent(NNE::Component::AComponent* component);
};
}
