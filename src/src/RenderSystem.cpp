#include "RenderSystem.h"
#include "VulkanManager.h"
#include "AComponent.h"

using namespace NNE::Systems;

RenderSystem::RenderSystem(VulkanManager* manager) : _vkManager(manager) {}

void RenderSystem::Start()
{
    if (_vkManager)
    {
        _vkManager->LoadMeshes(_renderObjects);
        _vkManager->createVertexBuffer();
        _vkManager->createIndexBuffer();
        _vkManager->createUniformBuffers();
        _vkManager->createDescriptorPool();
        _vkManager->createDescriptorSets();
        _vkManager->createCommandBuffers();
        _vkManager->createSyncObjects();
    }
}

void RenderSystem::Update(float deltaTime)
{
    (void)deltaTime;
    if (_vkManager)
    {
        _vkManager->drawFrame(_renderObjects);
    }
}

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

const std::vector<std::pair<NNE::Component::Render::MeshComponent*, NNE::Component::TransformComponent*>>& RenderSystem::GetRenderObjects() const
{
    return _renderObjects;
}

