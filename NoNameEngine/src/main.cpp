#include <iostream>
#include "Application.h"


int main() {
    
    try {

        NNE::Application* app = new NNE::Application();

        NNE::AEntity* entity1 = app->CreateEntity();
        NNE::MeshComponent* mesh1 = entity1->AddComponent<NNE::MeshComponent>();
        NNE::TransformComponent* transform1 = entity1->AddComponent<NNE::TransformComponent>();
        mesh1->SetModelPath("C:/Users/schev/Downloads/viking_room.obj");
        mesh1->SetTexturePath("");  // Utilisera la texture par défaut  

        NNE::AEntity* entity = app->CreateEntity();
        NNE::TransformComponent* transform = entity->AddComponent<NNE::TransformComponent>();
        NNE::MeshComponent* mesh = entity->AddComponent<NNE::MeshComponent>();
        mesh->SetModelPath("C:/Users/schev/Downloads/viking_room.obj");
        mesh->SetTexturePath("C:/Users/schev/Downloads/viking_room.png");
		transform->position = glm::vec3(10.0f, 0.0f, 0.0f);

        

        NNE::AEntity* cameraEntity = app->CreateEntity();
        NNE::CameraComponent* camera = cameraEntity->AddComponent<NNE::CameraComponent>();
        camera->UpdateViewMatrix(glm::vec3(0.0f, 2.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        app->VKManager->activeCamera = camera;

        app->Init();
        app->Update();
        app->Quit();
        delete app;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}