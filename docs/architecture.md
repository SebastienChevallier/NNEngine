# Architecture du moteur

Ce document présente un aperçu simplifié de l'architecture de **NoNameEngine** et liste quelques bonnes pratiques pour limiter son impact environnemental.

## Schéma global

```mermaid
classDiagram
    class Application {
        +Init()
        +Update()
        +Quit()
    }
    class VulkanManager {
        +initVulkan()
        +drawFrame()
    }
    class AEntity {
        +AddComponent()
        +Update()
    }
    class AComponent {
        +Awake()
        +Update()
    }
    Application o-- "1..*" AEntity : gère
    AEntity o-- "0..*" AComponent : possède
    Application o-- VulkanManager : utilise
```

**Légende**

- `Application` orchestre la création des entités et la boucle de rendu.
- `AEntity` regroupe des `AComponent` décrivant les comportements.
- `VulkanManager` s'occupe des appels graphiques bas niveau.
- Les flèches indiquent les dépendances principales entre les éléments.

## Impact environnemental

L'utilisation de Vulkan permet de limiter les surcoûts de calcul en accédant directement au GPU. Afin de réduire l'empreinte carbone lors de l'exécution du moteur :

- Limiter le nombre de draw calls et activer le frustum culling.
- Adapter la fréquence d'affichage en fonction des besoins du jeu.
- Nettoyer les entités et composants inutilisés pour éviter une consommation mémoire et CPU superflue.


## Diagramme de classes complet

```mermaid
classDiagram
    class Application
    class VulkanManager
    class PhysicsManager
    class InputManager
    class AScene
    class AEntity
    class AComponent
    class TransformComponent
    class CameraComponent
    class MeshComponent
    class MonoComponent
    class RigidbodyComponent
    class ColliderComponent
    class BoxColliderComponent
    class PlaneCollider

    Application o-- "1..*" AEntity
    Application o-- VulkanManager
    Application o-- PhysicsManager
    Application o-- InputManager
    Application o-- AScene
    AEntity o-- "0..*" AComponent
    AComponent <|-- TransformComponent
    AComponent <|-- CameraComponent
    AComponent <|-- MeshComponent
    AComponent <|-- MonoComponent
    AComponent <|-- RigidbodyComponent
    AComponent <|-- ColliderComponent
    ColliderComponent <|-- BoxColliderComponent
    ColliderComponent <|-- PlaneCollider
```

### Liste des classes

- `Application` : point d'entrée du moteur et gestionnaire général.
- `VulkanManager` : gestion des ressources graphiques.
- `PhysicsManager` : encapsule le moteur physique Jolt.
- `InputManager` : gestion des entrées clavier/souris.
- `AScene` : base décrivant un niveau.
- `AEntity` : conteneur d'ensembles de composants.
- `AComponent` : classe mère de tous les composants.
- `TransformComponent` : position et orientation d'une entité.
- `CameraComponent` : paramètres de caméra.
- `MeshComponent` : rendu des modèles 3D.
- `MonoComponent` : logique de jeu personnalisable.
- `RigidbodyComponent` : corps physique dynamique.
- `ColliderComponent` : base des composants de collision.
- `BoxColliderComponent` : collider en forme de boîte.
- `PlaneCollider` : collider plan infini.


