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

La documentation est disponible ici : [Documentation](https://sebastienchevallier.github.io/NNEngine/)

## Architecture

Le moteur est basé sur un ECS avec les composants suivants :

### Classes principales

#### `NNE::Systems::Application`
Gère l'initialisation et la boucle principale du moteur.

- `void Init()` : Initialise Vulkan et les entités.
- `void Update()` : Met à jour toutes les entités.
- `void Quit()` : Nettoie et ferme le moteur.
- `AEntity* CreateEntity()` : Crée une nouvelle entité.
- `int GenerateID()` : Génère un identifiant unique.

#### `NNE::AEntity`
Représente une entité du jeu.

- `template<typename T> T* AddComponent()` : Ajoute un composant à l'entité.
- `template<typename T> T* GetComponent()` : Récupère un composant de l'entité.
- `void Update(float delta)` : Met à jour tous ses composants.

#### `NNE::AComponent`
Classe de base pour tous les composants.

- `virtual void Awake()`
- `virtual void Start()`
- `virtual void Update(float deltaTime)`
- `virtual void LateUpdate(float deltaTime)`

#### `NNE::Component::TransformComponent`
Gère la position, la rotation et l'échelle d'une entité.

- `glm::vec3 position` : Position dans l'espace.
- `glm::vec3 rotation` : Rotation en degrés.
- `glm::vec3 scale` : Échelle de l'entité.
- `glm::mat4 getModelMatrix()` : Retourne la matrice de transformation.

#### `NNE::Component::Render::CameraComponent`
Gère la caméra et sa projection.

- `void SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane)`
- `void UpdateViewMatrix(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up)`
- `glm::mat4 GetViewMatrix()`
- `glm::mat4 GetProjectionMatrix()`

#### `NNE::Component::Render::MeshComponent`
Gère le rendu des modèles 3D avec Vulkan.

- `void SetModelPath(std::string path)`
- `void SetTexturePath(std::string path)`
- `std::string GetModelPath()`
- `std::string GetTexturePath()`

#### `NNE::Systems::VulkanManager`
Gère l'initialisation et le rendu avec Vulkan.

- `void initVulkan()`
- `void drawFrame()`
- `void createGraphicsPipeline()`
- `void createCommandBuffers()`
- `void updateUniformBuffer(uint32_t currentImage)`
- `void CleanUp()`

#### `NNE::Systems::InputManager`
Gère les entrées clavier et souris.

- `static void Init(GLFWwindow* win)`
- `static void Update()`
- `static bool IsKeyPressed(int key)`
- `static bool IsKeyJustPressed(int key)`
- `static bool IsKeyJustReleased(int key)`
- `static glm::vec2 GetMousePosition()`
- `static bool IsMouseButtonPressed(int button)`

#### `NNE::Systems::PhysicsManager`
Interface avec Jolt Physics.

- `void Initialize()`
- `void Update(float deltaTime)`
- `JPH::PhysicsSystem* GetPhysicsSystem()`

#### `NNE::Component::Physics::ColliderComponent`
Classe mère pour les colliders.

- `virtual void CreateShape()`
- `virtual void OnHit(ColliderComponent* other)`
- `virtual void OnTriggerHit(ColliderComponent* other)`

#### `NNE::Component::Physics::BoxColliderComponent`
Collider en boîte.

- `void Awake()`
- `void CreateShape()`

#### `NNE::Component::Physics::PlaneCollider`
Collider plan.

- `void CreateShape()`

#### `NNE::Component::Physics::RigidbodyComponent`
Gère un corps physique dynamique.

- `void Awake()`
- `void Update(float deltaTime)`
- `void SetLinearVelocity(glm::vec3 velocity)`
- `glm::vec3 GetLinearVelocity()`

#### `NNE::Component::MonoComponent`
Composant scriptable générique.

- `void Awake()`
- `void Start()`
- `void Update(float deltaTime)`
- `void LateUpdate(float deltaTime)`
- `void OnHit(NNE::Component::Physics::ColliderComponent* other)`
- `void OnTriggerHit(NNE::Component::Physics::ColliderComponent* other)`

#### `Diagramme de classe`
![image](https://github.com/user-attachments/assets/39aa283d-5a06-489e-ba82-c189747c2691)



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
