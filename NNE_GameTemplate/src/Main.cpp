#include <iostream>
#include "Application.h"

int main() {
    NNE::Application app;

    app.Init();
    app.Update();
    app.Quit();
    return 0;
}