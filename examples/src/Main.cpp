#include "Application.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "SphereCollider.h"
#include "RigidbodyComponent.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "PhysicsSystem.h"

#include "VulkanManager.h"

#include "../include/PlayerController.h"
#include <PlaneCollider.h>

int main() {
    NNE::Systems::Application app;
    app.physicsSystem->SetLayerCollision(NNE::Systems::Layers::RAYCAST, NNE::Systems::Layers::PLAYER, false);
    
    app.physicsSystem->SetLayerCollision(NNE::Systems::Layers::RAYCAST, NNE::Systems::Layers::DEFAULT, true);


	NNE::AEntity* Skybox = app.CreateEntity();
	Skybox->SetName("Skybox");
	NNE::Component::Render::MeshComponent* SBC = Skybox->AddComponent<NNE::Component::Render::MeshComponent>();
	SBC->SetPrimitive(NNE::Component::Render::PrimitiveType::SPHERE);
	SBC->SetSkybox(true);
	SBC->SetTexturePath("../assets/textures/skybox.hdr");
	Skybox->GetComponent<NNE::Component::TransformComponent>()->scale = glm::vec3(500.0f, 500.0f, 500.0f);

    NNE::AEntity* floor = app.CreateEntity();
	floor->SetName("Floor");
    NNE::Component::Physics::BoxColliderComponent const* PC = floor->AddComponent<NNE::Component::Physics::BoxColliderComponent>(glm::vec3(100.0f, 0.5f, 100.0f));
    //NNE::Component::Physics::PlaneCollider const* PC = floor->AddComponent<NNE::Component::Physics::PlaneCollider>(glm::vec3(1.0f, 1.0f, 1.0f));
    NNE::Component::TransformComponent* TCfloor = floor->GetComponent<NNE::Component::TransformComponent>();    
    NNE::Component::Physics::RigidbodyComponent const* RBCFloor = floor->AddComponent<NNE::Component::Physics::RigidbodyComponent>(1.0f, true);
    NNE::Component::Render::MeshComponent* MFC = floor->AddComponent<NNE::Component::Render::MeshComponent>();
	MFC->SetPrimitive(NNE::Component::Render::PrimitiveType::CUBE);
	MFC->SetTexturePath("../assets/textures/checker.png");
	MFC->GetMaterial().tiling = glm::vec2(0.1f, 0.1f);
    TCfloor->position = glm::vec3(0.0f, 0.0f, 0.0f);
    TCfloor->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	TCfloor->scale = glm::vec3(100.0f, 0.5f, 100.0f);

    NNE::AEntity* entity = app.CreateEntity();
    NNE::Component::Render::MeshComponent* MC = entity->AddComponent<NNE::Component::Render::MeshComponent>();
    NNE::Component::TransformComponent* TC = entity->GetComponent<NNE::Component::TransformComponent>();
    TC->position = glm::vec3(0.0f, 0.0f, 5.0f);
    NNE::Component::Physics::BoxColliderComponent const* BCC = entity->AddComponent<NNE::Component::Physics::BoxColliderComponent>(glm::vec3(1.0f, 1.0f, 1.0f));
    NNE::Component::Physics::RigidbodyComponent const* RBC = entity->AddComponent<NNE::Component::Physics::RigidbodyComponent>( 0.1f, false);
	
    //MC->SetModelPath("../assets/models/viking_room.obj");
	MC->SetPrimitive(NNE::Component::Render::PrimitiveType::CUBE);
    MC->SetTexturePath("../assets/textures/viking_room.png");

    NNE::AEntity* Sphere = app.CreateEntity();
    NNE::Component::Render::MeshComponent* MCs = Sphere->AddComponent<NNE::Component::Render::MeshComponent>();
    NNE::Component::TransformComponent* TCs = Sphere->GetComponent<NNE::Component::TransformComponent>();
    TCs->position = glm::vec3(0.0f, 2.0f, 0.0f);
    NNE::Component::Physics::SphereCollider const* SCC = Sphere->AddComponent<NNE::Component::Physics::SphereCollider>(1.0f);
    NNE::Component::Physics::RigidbodyComponent const* RBS = Sphere->AddComponent<NNE::Component::Physics::RigidbodyComponent>(0.1f, false);

    
    MCs->SetPrimitive(NNE::Component::Render::PrimitiveType::SPHERE);
    MCs->SetTexturePath("../assets/textures/checker.png");

    NNE::AEntity* player = app.CreateEntity();
	player->SetName("Player");
    NNE::Component::TransformComponent* TCplayer = player->GetComponent<NNE::Component::TransformComponent>();
    auto* BCCplayer = player->AddComponent<NNE::Component::Physics::BoxColliderComponent>(glm::vec3(1.0f, 1.0f, 1.0f));
    BCCplayer->SetLayer(NNE::Systems::Layers::PLAYER);
    NNE::Component::Physics::RigidbodyComponent const* RBCplayer = player->AddComponent<NNE::Component::Physics::RigidbodyComponent>(10.0f, false, glm::bvec3(0, 0, 0), glm::bvec3(1, 1, 1));
    PlayerController const* PlayerC = player->AddComponent<PlayerController>();


    TCplayer->position = glm::vec3(0.0f, 5.0f, 0.0f);

    NNE::AEntity* camera = app.CreateEntity();
    NNE::Component::Render::CameraComponent* CC = camera->AddComponent<NNE::Component::Render::CameraComponent>();
    NNE::Component::TransformComponent* TC2 = camera->GetComponent<NNE::Component::TransformComponent>();

	TC2->SetParent(TCplayer);
	Skybox->GetComponent<NNE::Component::TransformComponent>()->SetParent(TCplayer);

	CC->SetPerspective(55.0f, 16.0f / 9.0f, 0.1f, 500.0f);	
    TC2->position = glm::vec3(0.0f, 1.0f, 0.0f);
    TC2->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    app.VKManager->activeCamera = CC;

    NNE::AEntity* light = app.CreateEntity();
    auto* LC = light->AddComponent<NNE::Component::Render::LightComponent>();
    app.VKManager->activeLight = LC;

    app.Init();
    app.Update();
    app.Quit();
    return 0;
}
