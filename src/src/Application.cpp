#include "Application.h"
#include "SystemManager.h"

std::clock_t lastFrameTime;
NNE::Systems::Application* NNE::Systems::Application::Instance = nullptr;
int NNE::Systems::Application::_genericID = 0;

NNE::Systems::Application::Application()
    : _systems(NNE::Systems::SystemManager::GetInstance()->GetSystems())
{
    Instance = this;
    VKManager = new VulkanManager();
    physicsSystem = new PhysicsSystem();
    renderSystem = new RenderSystem(VKManager);
    inputSystem = new InputSystem();
    scriptSystem = new ScriptSystem();
    NNE::Systems::SystemManager::GetInstance()->AddSystem(physicsSystem);
    NNE::Systems::SystemManager::GetInstance()->AddSystem(renderSystem);
    NNE::Systems::SystemManager::GetInstance()->AddSystem(inputSystem);
    NNE::Systems::SystemManager::GetInstance()->AddSystem(scriptSystem);
    delta = 0;
}

NNE::Systems::Application::~Application()
{
    if (VKManager) {
        VKManager->CleanUp();
        delete VKManager;
        VKManager = nullptr;
    }

    if (renderSystem)
    {
        delete renderSystem;
        renderSystem = nullptr;
    }

    if (inputSystem)
    {
        delete inputSystem;
        inputSystem = nullptr;
    }

    if (scriptSystem)
    {
        delete scriptSystem;
        scriptSystem = nullptr;
    }

    for (NNE::AEntity* entity : _entities) {
        delete entity;
    }
    _entities.clear();

    if (physicsSystem)
    {
        delete physicsSystem;
        physicsSystem = nullptr;
    }
}

void NNE::Systems::Application::Init()
{
    Open();
    VKManager->initVulkan();
    for (NNE::Systems::ISystem* system : _systems)
    {
        system->Awake();
        system->Start();
    }

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
        for (NNE::Systems::ISystem* system : _systems)
        {
            system->Update(delta);
        }

        for (NNE::AEntity* entity : _entities)
        {
            entity->Update(delta);
        }

        for (NNE::Systems::ISystem* system : _systems)
        {
            system->LateUpdate(delta);
        }

        for (NNE::AEntity* entity : _entities)
        {
            entity->LateUpdate(delta);
        }
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
