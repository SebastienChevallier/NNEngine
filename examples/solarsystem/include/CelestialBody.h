#pragma once
#include "MonoComponent.h"
#include "TransformComponent.h"
#include <vector>
#include <glm/ext/vector_float3.hpp>

class CelestialBody : public NNE::Component::MonoComponent {
public:
    float mass = 1.0f;
    glm::vec3 velocity{0.0f};
    bool isStatic = false;

    CelestialBody();
    ~CelestialBody();

    void Awake() override;
    void Update(float dt) override;
    void OnDestroy() override;

    static std::vector<CelestialBody*> bodies;
};
