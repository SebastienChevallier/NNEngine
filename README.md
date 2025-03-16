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

### Compilation

```sh
mkdir build
cd build
cmake ..
make
```

## Architecture

Le moteur est basé sur un ECS avec les composants suivants :

### Classes principales

#### `NNE::Application`
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

#### `NNE::TransformComponent`
Gère la position, la rotation et l'échelle d'une entité.

- `glm::vec3 position` : Position dans l'espace.
- `glm::vec3 rotation` : Rotation en degrés.
- `glm::vec3 scale` : Échelle de l'entité.
- `glm::mat4 getModelMatrix()` : Retourne la matrice de transformation.

#### `NNE::CameraComponent`
Gère la caméra et sa projection.

- `void SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane)`
- `void UpdateViewMatrix(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up)`
- `glm::mat4 GetViewMatrix()`
- `glm::mat4 GetProjectionMatrix()`

#### `NNE::MeshComponent`
Gère le rendu des modèles 3D avec Vulkan.

- `void SetModelPath(std::string path)`
- `void SetTexturePath(std::string path)`
- `std::string GetModelPath()`
- `std::string GetTexturePath()`

#### `NNE::VulkanManager`
Gère l'initialisation et le rendu avec Vulkan.

- `void initVulkan()`
- `void drawFrame()`
- `void createGraphicsPipeline()`
- `void createCommandBuffers()`
- `void updateUniformBuffer(uint32_t currentImage)`
- `void CleanUp()`

#### `Diagramme de classe`
![image](https://github.com/user-attachments/assets/f7313fe1-f969-477c-8f9f-a3bef365b3a8)


## Exécution

Un exemple minimal d'utilisation du moteur :

```cpp
int main() {
    NNE::Application app;
    
    NNE::AEntity* entity = app.CreateEntity();
    NNE::MeshComponent* MC = entity->AddComponent<NNE::MeshComponent>();
    NNE::TransformComponent* TC = entity->AddComponent<NNE::TransformComponent>();
    MC->SetModelPath("viking_room.obj");
    MC->SetTexturePath("viking_room.png");
    
    NNE::AEntity* camera = app.CreateEntity();
    NNE::CameraComponent* CC = camera->AddComponent<NNE::CameraComponent>();
    NNE::TransformComponent* TC2 = camera->AddComponent<NNE::TransformComponent>();
    TC2->position = glm::vec3(0.0f, 0.0f, 30.0f);
    app.VKManager->activeCamera = CC;
    
    app.Init();
    app.Update();
    app.Quit();
    return 0;
}
```


 
