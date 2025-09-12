#include "CelestialBody.h"
#include "imgui.h"
#include <algorithm>
#include <glm/geometric.hpp>

std::vector<CelestialBody*> CelestialBody::bodies;

CelestialBody::CelestialBody() {}
CelestialBody::~CelestialBody() {}

void CelestialBody::Awake() {
    bodies.push_back(this);
}

void CelestialBody::OnDestroy() {
    bodies.erase(std::remove(bodies.begin(), bodies.end(), this), bodies.end());
}

void CelestialBody::Update(float dt) {
    const float G = 0.1f;
    glm::vec3 force(0.0f);
    for (auto* body : bodies) {
        if (body == this) continue;
        glm::vec3 dir = body->_entity->transform->position - _entity->transform->position;
        float distance = glm::length(dir);
        if (distance < 0.1f) continue;
        glm::vec3 norm = glm::normalize(dir);
        float f = G * mass * body->mass / (distance * distance);
        force += norm * f;
    }
    if (!isStatic) {
        glm::vec3 acceleration = force / mass;
        velocity += acceleration * dt;
        _entity->transform->position += velocity * dt;
    }

    ImGui::Begin(_entity->GetName().c_str());
    ImGui::InputFloat("Mass", &mass);
    ImGui::End();
}
