#include "Application.h"

std::clock_t lastFrameTime;
NNE::Application* NNE::Application::Instance = nullptr;
int NNE::Application::_genericID = 0;



NNE::Application::Application()
{
    Instance = this;
    VKManager = new VulkanManager();
    delta = 0;
}

NNE::Application::~Application()
{
    for (AEntity* entity : _entities) {
        delete entity;
    }   
    _entities.clear();

    if (VKManager) {
        VKManager->CleanUp();
        delete VKManager;
        VKManager = nullptr;
    }
}


void NNE::Application::Init()
{    
    Open();    
    VKManager->initVulkan();

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
        VKManager->drawFrame();
        

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
    }   
    vkDeviceWaitIdle(VKManager->device);
}

void NNE::Application::Open()
{
    VKManager->CreateGLFWWindow(WIDTH, HEIGHT);
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
    std::clock_t currentFrameTime = std::clock();
    float deltaTime = float(currentFrameTime - lastFrameTime) / CLOCKS_PER_SEC;
    lastFrameTime = currentFrameTime;
    return deltaTime;
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
