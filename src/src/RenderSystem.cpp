#include "RenderSystem.h"
#include "VulkanManager.h"
#include "AComponent.h"

namespace NNE::Systems {

/**
 * <summary>
 * Initialise le système de rendu avec un gestionnaire Vulkan.
 * </summary>
 */
RenderSystem::RenderSystem(VulkanManager* manager) : _vkManager(manager) {}

/**
 * <summary>
 * Charge les ressources graphiques nécessaires.
 * </summary>
 */
void RenderSystem::Start()
{
    if (_vkManager)
    {
        _vkManager->LoadMeshes(_renderObjects);

        if (!_vkManager->vertices.empty() && !_vkManager->indices.empty())
        {
            _vkManager->createVertexBuffer();
            _vkManager->createIndexBuffer();
        }
        _vkManager->createUniformBuffers();
        _vkManager->createDescriptorPool();
        _vkManager->createDescriptorSets();
        _vkManager->createShadowDescriptorSets();
        _vkManager->createCommandBuffers();
        _vkManager->createSyncObjects();
    }
}

/**
 * <summary>
 * Dessine la scène à chaque frame.
 * </summary>
 */
void RenderSystem::Update(float deltaTime)
{
    (void)deltaTime;
    if (_vkManager)
    {
        _vkManager->drawFrame(_renderObjects);
    }
}

/**
 * <summary>
 * Ajoute un mesh et son transform à la liste de rendu.
 * </summary>
 */
void RenderSystem::RegisterComponent(NNE::Component::AComponent* component)
{
    if (auto* mesh = dynamic_cast<NNE::Component::Render::MeshComponent*>(component))
    {
        NNE::Component::TransformComponent* transform = mesh->GetEntity()->GetComponent<NNE::Component::TransformComponent>();
        if (transform)
        {
            _renderObjects.emplace_back(mesh, transform);
        }
    }
}

/**
 * <summary>
 * Fournit la liste des objets actuellement rendus.
 * </summary>
 */
const std::vector<std::pair<NNE::Component::Render::MeshComponent*, NNE::Component::TransformComponent*>>& RenderSystem::GetRenderObjects() const
{
    return _renderObjects;
}

} // namespace NNE::Systems

