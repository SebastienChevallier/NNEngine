#include <iostream>
#include "Application.h"


int main() {
    
    try {
        NNE::Application* app = new NNE::Application();
        NNE::AEntity* entity = app->CreateEntity();
        NNE::TransformComponent* transform = entity->AddComponent<NNE::TransformComponent>();
        NNE::MeshComponent* mesh = entity->AddComponent<NNE::MeshComponent>();

        /*NNE::AEntity* entity1 = app->CreateEntity();
        NNE::MeshComponent* mesh1 = entity1->AddComponent<NNE::MeshComponent>();
        NNE::TransformComponent* transform1 = entity1->AddComponent<NNE::TransformComponent>()*/;

        mesh->SetModelPath("C:/Users/schev/Downloads/viking_room.obj");
        /*mesh1->SetModelPath("C:/Users/schev/Downloads/viking_room.obj");*/
        mesh->SetTexturePath("C:/Users/schev/Downloads/viking_room.png");
        //mesh1->SetTexturePath("");  // Utilisera la texture par défaut

        // Décalage pour éviter la superposition
        transform->scale = glm::vec3(1.0f, 1.0f, 1.0f);

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