#include "Application.h"
#include "SystemManager.h"
#include "PerformanceMetrics.h"
#include <algorithm>
#include <chrono>
#include "VulkanManager.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"
#include "UISystem.h"
#include "InputSystem.h"
#include "ScriptSystem.h"
#include "LightSystem.h"
#include "InputManager.h"

std::clock_t lastFrameTime;
NNE::Systems::Application* NNE::Systems::Application::Instance = nullptr;
int NNE::Systems::Application::_genericID = 0;

/**
 * <summary>
 * Construit l'application et crée les systèmes principaux.
 * </summary>
 */
NNE::Systems::Application::Application()
    : _systems(NNE::Systems::SystemManager::GetInstance()->GetSystems())
{
    Instance = this;
    VKManager = new VulkanManager();
    physicsSystem = new PhysicsSystem();
    physicsSystem->Awake();
    uiSystem = new UISystem(VKManager);
    renderSystem = new RenderSystem(VKManager);
    lightSystem = new LightSystem(VKManager);
    inputSystem = new InputSystem();
    scriptSystem = new ScriptSystem();
    NNE::Systems::SystemManager::GetInstance()->AddSystem(physicsSystem);
    NNE::Systems::SystemManager::GetInstance()->AddSystem(uiSystem);
    NNE::Systems::SystemManager::GetInstance()->AddSystem(renderSystem);
    NNE::Systems::SystemManager::GetInstance()->AddSystem(lightSystem);
    NNE::Systems::SystemManager::GetInstance()->AddSystem(inputSystem);
    NNE::Systems::SystemManager::GetInstance()->AddSystem(scriptSystem);
    delta = 0;
}

/**
 * <summary>
 * Libère toutes les ressources allouées par l'application.
 * </summary>
 */
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

    if (uiSystem)
    {
        delete uiSystem;
        uiSystem = nullptr;
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

    if (lightSystem)
    {
        delete lightSystem;
        lightSystem = nullptr;
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

/**
 * <summary>
 * Initialise l'application et démarre les systèmes et entités.
 * </summary>
 */
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

/**
 * <summary>
 * Fait tourner la boucle principale de l'application.
 * </summary>
 */
void NNE::Systems::Application::Update()
{
    while (!glfwWindowShouldClose(VKManager->window)) {
        delta = GetDeltaTime();
        float dtMs = delta * 1000.0f;
        static float smooth = dtMs;
        smooth = 0.9f * smooth + 0.1f * dtMs;
        g_FrameTimeMs = smooth;
        g_FPS = 1000.0f / std::max(0.001f, g_FrameTimeMs);
        glfwPollEvents();

		glfwGetWindowSize(VKManager->window, &WIDTH,&HEIGHT);
		

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

/**
 * <summary>
 * Ouvre la fenêtre principale et prépare les entrées.
 * </summary>
 */
void NNE::Systems::Application::Open()
{
    VKManager->CreateGLFWWindow(WIDTH, HEIGHT);
    NNE::Systems::InputManager::Init(VKManager->window);
}

/**
 * <summary>
 * Termine l'application en fermant les bibliothèques utilisées.
 * </summary>
 */
void NNE::Systems::Application::Quit()
{
    glfwTerminate();
}

/**
 * <summary>
 * Fournit un nouvel identifiant unique.
 * </summary>
 */
int NNE::Systems::Application::GenerateID()
{
    _genericID++;
    return _genericID;
}

/**
 * <summary>
 * Crée et enregistre une entité dans l'application.
 * </summary>
 */
NNE::AEntity* NNE::Systems::Application::CreateEntity()
{
    NNE::AEntity* entity = new NNE::AEntity();
    _entities.push_back(entity);
    return entity;
}

/**
 * <summary>
 * Calcule le temps écoulé depuis la dernière frame.
 * </summary>
 */
float NNE::Systems::Application::GetDeltaTime()
{
    static auto lastFrame = std::chrono::high_resolution_clock::now();
    auto currentFrame = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float>(currentFrame - lastFrame).count();
    lastFrame = currentFrame;
    return dt;
}

/**
 * <summary>
 * Accède à l'instance unique de l'application.
 * </summary>
 */
NNE::Systems::Application* NNE::Systems::Application::GetInstance()
{
    return Instance;
}
