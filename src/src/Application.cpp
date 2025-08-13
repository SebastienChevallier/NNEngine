#include "Application.h"

std::clock_t lastFrameTime;
NNE::Systems::Application* NNE::Systems::Application::Instance = nullptr;
int NNE::Systems::Application::_genericID = 0;

NNE::Systems::Application::Application()
{
    Instance = this;
    VKManager = new VulkanManager();
    physicsManager = new PhysicsManager();
    delta = 0;
}

NNE::Systems::Application::~Application()
{
    if (VKManager) {
        VKManager->CleanUp();
        delete VKManager;
        VKManager = nullptr;
    }

    for (NNE::AEntity* entity : _entities) {
        delete entity;
    }
    _entities.clear();
}

void NNE::Systems::Application::Init()
{
    Open();
    VKManager->initVulkan();
    physicsManager->Initialize();

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    for (NNE::AEntity* entity : _entities)
    {
        entity->Awake();
        entity->Start();
    }
}

void NNE::Systems::Application::Update()
{
    while (!glfwWindowShouldClose(VKManager->window)) {
        delta = GetDeltaTime();
        glfwPollEvents();
        NNE::Systems::InputManager::Update();
        physicsManager->Update(delta);

        for (NNE::AEntity* entity : _entities)
        {
            entity->Update(delta);
        }

        for (NNE::AEntity* entity : _entities)
        {
            entity->LateUpdate(delta);
        }

        VKManager->drawFrame();
    }
    vkDeviceWaitIdle(VKManager->device);
}

void NNE::Systems::Application::Open()
{
    VKManager->CreateGLFWWindow(WIDTH, HEIGHT);
    NNE::Systems::InputManager::Init(VKManager->window);
}

void NNE::Systems::Application::Quit()
{
    glfwTerminate();
}

int NNE::Systems::Application::GenerateID()
{
    _genericID++;
    return _genericID;
}

NNE::AEntity* NNE::Systems::Application::CreateEntity()
{
    NNE::AEntity* entity = new NNE::AEntity();
    _entities.push_back(entity);
    return entity;
}

float NNE::Systems::Application::GetDeltaTime()
{
    static auto lastFrame = std::chrono::high_resolution_clock::now();
    auto currentFrame = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float>(currentFrame - lastFrame).count();
    lastFrame = currentFrame;
    return dt;
}

NNE::Systems::Application* NNE::Systems::Application::GetInstance()
{
    return Instance;
}
