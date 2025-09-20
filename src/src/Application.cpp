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

/**
 * <summary>
 * Construit l'application et crée les systèmes principaux.
 * </summary>
 */
NNE::Systems::Application::Application()
{
    Instance = this;
    VKManager = new VulkanManager();
    auto* manager = NNE::Systems::SystemManager::GetInstance();
    manager->AddSystem(new PhysicsSystem());
    manager->AddSystem(new UISystem(VKManager));
    manager->AddSystem(new RenderSystem(VKManager));
    manager->AddSystem(new LightSystem(VKManager));
    manager->AddSystem(new InputSystem());
    manager->AddSystem(new ScriptSystem());
    delta = 0;
    _playMode = false;
    _sceneViewActive = true;
    _deltaTime = 0.0f;
    _gameDeltaTime = 0.0f;
    _lastFrameTime = std::chrono::high_resolution_clock::now();
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

    for (NNE::AEntity* entity : _entities) {
        delete entity;
    }
    _entities.clear();

    NNE::Systems::SystemManager::GetInstance()->Clear();
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
    auto* manager = NNE::Systems::SystemManager::GetInstance();
    manager->AwakeAll();
    manager->StartAll();

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
    auto* manager = NNE::Systems::SystemManager::GetInstance();
    while (!glfwWindowShouldClose(VKManager->window)) {
        auto currentFrame = std::chrono::high_resolution_clock::now();
        float realDelta = std::chrono::duration<float>(currentFrame - _lastFrameTime).count();
        _lastFrameTime = currentFrame;

        _deltaTime = realDelta;
        _gameDeltaTime = _playMode ? realDelta : 0.0f;
        delta = _gameDeltaTime;

        float dtMs = realDelta * 1000.0f;
        static float smooth = dtMs;
        smooth = 0.9f * smooth + 0.1f * dtMs;
        g_FrameTimeMs = smooth;
        g_FPS = 1000.0f / std::max(0.001f, g_FrameTimeMs);
        glfwPollEvents();

        glfwGetWindowSize(VKManager->window, &WIDTH,&HEIGHT);

        manager->UpdateAll(_gameDeltaTime);

        for (NNE::AEntity* entity : _entities)
        {
            entity->Update(_gameDeltaTime);
        }

        manager->LateUpdateAll(_gameDeltaTime);

        for (NNE::AEntity* entity : _entities)
        {
            entity->LateUpdate(_gameDeltaTime);
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
float NNE::Systems::Application::GetDeltaTime() const
{
    return _deltaTime;
}

float NNE::Systems::Application::GetGameDeltaTime() const
{
    return _gameDeltaTime;
}

bool NNE::Systems::Application::IsPlayMode() const
{
    return _playMode;
}

void NNE::Systems::Application::SetPlayMode(bool playing)
{
    if (_playMode == playing)
        return;

    _playMode = playing;
    _lastFrameTime = std::chrono::high_resolution_clock::now();
    _gameDeltaTime = 0.0f;
    delta = 0.0f;
}

bool NNE::Systems::Application::IsSceneViewActive() const
{
    return _sceneViewActive;
}

void NNE::Systems::Application::SetSceneViewActive(bool active)
{
    if (_sceneViewActive == active)
        return;

    _sceneViewActive = active;
    if (_sceneViewActive)
    {
        SetPlayMode(false);
    }
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
