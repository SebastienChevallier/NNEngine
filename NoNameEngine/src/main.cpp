#include <iostream>
#include "Application.h"


int main() {
    
    NNE::Application* app = new NNE::Application();

<<<<<<< Updated upstream
=======
    NNE::AEntity* entity = app->CreateEntity();
    NNE::TransformComponent* transform = entity->AddComponent<NNE::TransformComponent>();
    NNE::MeshComponent* mesh = entity->AddComponent<NNE::MeshComponent>();

    NNE::AEntity* entity1 = app->CreateEntity();    
    NNE::MeshComponent* mesh1 = entity1->AddComponent<NNE::MeshComponent>();
    NNE::TransformComponent* transform1 = entity1->AddComponent<NNE::TransformComponent>();    

    mesh->SetModelPath("C:/Users/schev/Downloads/viking_room.obj");
    mesh1->SetModelPath("C:/Users/schev/Downloads/viking_room.obj");
    mesh->SetTexturePath("C:/Users/schev/source/repos/Git-NNE/NoNameEngine/textures/viking_room.png");
    mesh1->SetTexturePath("");

>>>>>>> Stashed changes
    app->Init();

    app->Update();
    app->Quit();

    

    return 0;
}