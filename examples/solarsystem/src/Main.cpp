#include "Application.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "VulkanManager.h"

#include "CelestialBody.h"
#include "FreeCameraController.h"

int main() {
    NNE::Systems::Application app;

    // Skybox (optional)
    NNE::AEntity* skybox = app.CreateEntity();
    skybox->SetName("Skybox");
    auto* skyMesh = skybox->AddComponent<NNE::Component::Render::MeshComponent>();
    skyMesh->SetPrimitive(NNE::Component::Render::PrimitiveType::SPHERE);
    skyMesh->SetSkybox(true);
    skyMesh->SetTexturePath("../assets/textures/skybox.hdr");
    skybox->GetComponent<NNE::Component::TransformComponent>()->scale = glm::vec3(500.0f);

    // Sun
    NNE::AEntity* sun = app.CreateEntity();
    sun->SetName("Sun");
    auto* sunMesh = sun->AddComponent<NNE::Component::Render::MeshComponent>();
    sunMesh->SetPrimitive(NNE::Component::Render::PrimitiveType::SPHERE);
    sunMesh->SetTexturePath("../assets/textures/texture.png");
    sun->GetComponent<NNE::Component::TransformComponent>()->scale = glm::vec3(2.0f);
    auto* sunBody = sun->AddComponent<CelestialBody>();
    sunBody->mass = 1000.0f;
    sunBody->isStatic = true;
    auto* sunLight = sun->AddComponent<NNE::Component::Render::LightComponent>();
    app.VKManager->activeLight = sunLight;

    // Planet 1
    NNE::AEntity* planet1 = app.CreateEntity();
    planet1->SetName("Planet1");
    auto* p1Mesh = planet1->AddComponent<NNE::Component::Render::MeshComponent>();
    p1Mesh->SetPrimitive(NNE::Component::Render::PrimitiveType::SPHERE);
    p1Mesh->SetTexturePath("../assets/textures/texture.png");
    planet1->GetComponent<NNE::Component::TransformComponent>()->position = glm::vec3(10.0f, 0.0f, 0.0f);
    auto* p1Body = planet1->AddComponent<CelestialBody>();
    p1Body->mass = 10.0f;
    p1Body->velocity = glm::vec3(0.0f, 0.0f, 15.0f);

    // Planet 2
    NNE::AEntity* planet2 = app.CreateEntity();
    planet2->SetName("Planet2");
    auto* p2Mesh = planet2->AddComponent<NNE::Component::Render::MeshComponent>();
    p2Mesh->SetPrimitive(NNE::Component::Render::PrimitiveType::SPHERE);
    p2Mesh->SetTexturePath("../assets/textures/texture.png");
    planet2->GetComponent<NNE::Component::TransformComponent>()->position = glm::vec3(15.0f, 0.0f, 0.0f);
    auto* p2Body = planet2->AddComponent<CelestialBody>();
    p2Body->mass = 5.0f;
    p2Body->velocity = glm::vec3(0.0f, 0.0f, 12.0f);

    // Camera
    NNE::AEntity* camera = app.CreateEntity();
    auto* camComp = camera->AddComponent<NNE::Component::Render::CameraComponent>();
    camera->AddComponent<FreeCameraController>();
    camera->GetComponent<NNE::Component::TransformComponent>()->position = glm::vec3(0.0f, 5.0f, 25.0f);
    app.VKManager->activeCamera = camComp;

    app.Init();
    app.Update();
    app.Quit();
    return 0;
}
