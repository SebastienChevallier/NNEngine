#include "Application.h"

int main() {
    NNE::Application app;

	NNE::AEntity* floor = app.CreateEntity();
	//NNE::PlaneCollider* PC = floor->AddComponent<NNE::PlaneCollider>(glm::vec3(0, 1, 0), 10.0f);
	NNE::TransformComponent* TCfloor = floor->GetComponent<NNE::TransformComponent>();
	NNE::BoxColliderComponent* BCFloor = floor->AddComponent<NNE::BoxColliderComponent>(glm::vec3(100.0f, 0.50f, 100.0f));
	NNE::RigidbodyComponent* RBCFloor = floor->AddComponent<NNE::RigidbodyComponent>(0.0f, false);
	TCfloor->position = glm::vec3(0.0f, -1.0f, 0.0f);

	NNE::AEntity* entity = app.CreateEntity();
	NNE::MeshComponent* MC = entity->AddComponent<NNE::MeshComponent>();
	NNE::TransformComponent* TC = entity->GetComponent<NNE::TransformComponent>();
	TC->position = glm::vec3(0.0f, 5.0f, 0.0f);
	NNE::BoxColliderComponent* BCC = entity->AddComponent<NNE::BoxColliderComponent>(glm::vec3(1.0f, 1.0f, 1.0f));
	NNE::RigidbodyComponent* RBC = entity->AddComponent<NNE::RigidbodyComponent>( 1.0f, false);
	MC->SetModelPath("C:/Users/schev/Downloads/viking_room.obj");
	MC->SetTexturePath("C:/Users/schev/Downloads/viking_room.PNG");
	

	NNE::AEntity* camera = app.CreateEntity();
	NNE::CameraComponent* CC = camera->AddComponent<NNE::CameraComponent>();
	NNE::TransformComponent* TC2 = camera->GetComponent<NNE::TransformComponent>();

	CC->SetPerspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);	
	TC2->position = glm::vec3(0.0f, 0.0f, 5.0f);
	app.VKManager->activeCamera = CC;

    app.Init();
    app.Update();
    app.Quit();
    return 0;
}