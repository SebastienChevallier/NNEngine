#include <iostream>
#include "Application.h"

int main() {
    
    NNE::Application* app = new NNE::Application();

    //NNE::AEntity* entity = app->CreateEntity();
    NNE::AEntity* entity1 = app->CreateEntity();
    //NNE::MeshComponent* mesh = entity->AddComponent<NNE::MeshComponent>();
    NNE::MeshComponent* mesh1 = entity1->AddComponent<NNE::MeshComponent>();
    //mesh->SetModelPath("C:/Users/schev/Downloads/viking_room.obj");
    mesh1->SetModelPath("C:/Users/schev/Downloads/viking_room.obj");
   //mesh->SetTexturePath("C:/Users/schev/source/repos/Git-NNE/NoNameEngine/textures/viking_room.png");
    mesh1->SetTexturePath("");

    app->Init();

    app->Update();
    app->Quit();

    

    return 0;
}