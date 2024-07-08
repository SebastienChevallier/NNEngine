#include <iostream>
#include "Application.h"

int main() {
    
    NNE::Application* app = new NNE::Application();

    app->Init();

    app->Update();
    app->Quit();

    

    return 0;
}