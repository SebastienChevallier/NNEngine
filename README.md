# NoNameEngine
![Build Status](https://github.com/SebastienChevallier/NNEngine/actions/workflows/c-cpp.yml/badge.svg)

# NoNameEngine

NoNameEngine est un moteur de jeu basé sur un système Entity Component System (ECS) utilisant Vulkan pour le rendu.

## Installation

### Prérequis
- CMake 3.15+
- Vulkan SDK
- GLFW
- GLM
- tinyobjloader

### Installer les dépendances
Ce projet utilise [vcpkg](https://github.com/microsoft/vcpkg) pour gérer les bibliothèques tierces.
Des scripts sont fournis pour installer automatiquement `vcpkg` ainsi que les packages requis.

```sh
# Linux/macOS
./scripts/install_dependencies.sh

# Windows
scripts\install_dependencies.bat
```

Une fois les dépendances en place, vous pouvez générer la solution comme décrit ci-dessous.

### Compilation

```sh
# On Linux/macOS
./scripts/build.sh

# On Windows
scripts\build.bat
```

## Documentation

La documentation est disponible ici : [Documentation](https://sebastienchevallier.github.io/NNEngine/html/index.html)

## Exécution

Un exemple minimal d'utilisation du moteur :

```cpp
int main() {
    NNE::Systems::Application app;
    
    NNE::AEntity* entity = app.CreateEntity();
    NNE::Component::Render::MeshComponent* MC = entity->AddComponent<NNE::Component::Render::MeshComponent>();
    NNE::Component::TransformComponent* TC = entity->AddComponent<NNE::Component::TransformComponent>();
    // The engine expects the assets folder to be copied next to the executable
    // when building. Relative paths can then be used during runtime.
    MC->SetModelPath("../assets/viking_room.obj");
    MC->SetTexturePath("../assets/textures/viking_room.png");
    
    NNE::AEntity* camera = app.CreateEntity();
    NNE::Component::Render::CameraComponent* CC = camera->AddComponent<NNE::Component::Render::CameraComponent>();
    NNE::Component::TransformComponent* TC2 = camera->AddComponent<NNE::Component::TransformComponent>();
    TC2->position = glm::vec3(0.0f, 0.0f, 30.0f);
    app.VKManager->activeCamera = CC;
    
    app.Init();
    app.Update();
    app.Quit();
    return 0;
}
```
> Les fichiers `viking_room.obj` et `viking_room.png` ne sont pas fournis. Placez le modèle dans `assets/` et la texture dans `src/textures/` avant de compiler.
