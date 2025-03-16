#include "Application.h"

int main() {
    NNE::Application app;

	NNE::AEntity* entity = app.CreateEntity();
	NNE::MeshComponent* MC = entity->AddComponent<NNE::MeshComponent>();
	NNE::TransformComponent* TC = entity->GetComponent<NNE::TransformComponent>();
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