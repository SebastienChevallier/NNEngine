#pragma once

#include <vector>
#include <utility>
#include "ISystem.h"
#include "MeshComponent.h"
#include "TransformComponent.h"

namespace NNE::Systems {
class VulkanManager;

class RenderSystem : public ISystem {
private:
    VulkanManager* _renderer;
    std::vector<std::pair<NNE::Component::Render::MeshComponent*, NNE::Component::TransformComponent*>> _renderObjects;

public:
    /**
     * <summary>
     * Crée le système de rendu avec son gestionnaire Vulkan.
     * </summary>
     */
    explicit RenderSystem(VulkanManager* manager);
    ~RenderSystem() = default;

    void Awake() override {}
    /**
     * <summary>
     * Prépare les ressources de rendu.
     * </summary>
     */
    void Start() override;
    /**
     * <summary>
     * Dessine les objets chaque frame.
     * </summary>
     */
    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override {}
    /**
     * <summary>
     * Enregistre un composant pour le rendu.
     * </summary>
     */
    void RegisterComponent(NNE::Component::AComponent* component) override;

    /**
     * <summary>
     * Récupère la liste des objets à rendre.
     * </summary>
     */
    const std::vector<std::pair<NNE::Component::Render::MeshComponent*, NNE::Component::TransformComponent*>>& GetRenderObjects() const;
};
}

