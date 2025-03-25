#include "Application.h"


std::clock_t lastFrameTime;
NNE::Application* NNE::Application::Instance = nullptr;
int NNE::Application::_genericID = 0;



NNE::Application::Application()
{
    Instance = this;
    VKManager = new VulkanManager();
	physicsManager = new PhysicsManager();
    delta = 0;
}

NNE::Application::~Application()
{
    if (VKManager) {
        VKManager->CleanUp();
        delete VKManager;
        VKManager = nullptr;
    }


    for (AEntity* entity : _entities) {
        delete entity;
    }   
    _entities.clear();
}


void NNE::Application::Init()
{    
    Open();    
    VKManager->initVulkan();
    physicsManager->Initialize();
    //VKManager->LoadEntitiesModels(_entities);

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    for (AEntity* entity : _entities)
    {
        entity->Awake();
        entity->Start();
    }
}

void NNE::Application::Update()
{
    
    while (!glfwWindowShouldClose(VKManager->window)) {
        delta = GetDeltaTime();
        glfwPollEvents();        
        InputManager::Update();
        physicsManager->Update(delta);
        
        for (AEntity* entity : _entities) {
            // Récupérer le CameraComponent et le TransformComponent
            CameraComponent* cameraComp = entity->GetComponent<CameraComponent>();
            TransformComponent* transform = entity->GetComponent<TransformComponent>();
            // S’il s’agit d’une entité “caméra”
            if (cameraComp && transform) {
                // Exemple : On regarde vers l’axe -Z depuis la position
                glm::vec3 pos = transform->position;
                glm::vec3 target = pos + glm::vec3(0, 0, -1);
                glm::vec3 up = glm::vec3(0, 1, 0);
                cameraComp->UpdateViewMatrix(pos, target, up);
            }
        }

        //Update
        for(AEntity* entity : _entities)
        {
            entity->Update(delta);
        }

        //LateUpdate
        for (AEntity* entity : _entities)
        {
            entity->LateUpdate(delta);
        }

        VKManager->drawFrame();
    }   
    vkDeviceWaitIdle(VKManager->device);
}

void NNE::Application::Open()
{
    VKManager->CreateGLFWWindow(WIDTH, HEIGHT);
    InputManager::Init(VKManager->window);
}

void NNE::Application::Quit()
{    
    glfwTerminate();
}

int NNE::Application::GenerateID()
{
    _genericID++;
    return _genericID;
}

NNE::AEntity* NNE::Application::CreateEntity()
{
    AEntity* entity = new AEntity();
    _entities.push_back(entity);
    return entity;
}

float NNE::Application::GetDeltaTime()
{
    static auto lastFrame = std::chrono::high_resolution_clock::now();
    auto currentFrame = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float>(currentFrame - lastFrame).count();
    lastFrame = currentFrame;
    return dt;
}

//GLFWwindow* NNE::Application::CreateGLFWWindow(int width, int height)
//{
//    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
//    window = glfwCreateWindow(width, height, "Vulkan window", nullptr, nullptr);
//    return window;
//}

NNE::Application* NNE::Application::GetInstance()
{
    return Instance;
}
