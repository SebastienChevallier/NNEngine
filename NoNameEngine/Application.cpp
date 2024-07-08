#include "Application.h"

std::clock_t lastFrameTime;
NNE::Application* NNE::Application::Instance = nullptr;
int NNE::Application::_genericID = 0;

//const std::vector<const char*> validationLayers = {
//    "VK_LAYER_KHRONOS_validation"
//};
//
//#ifdef NDEBUG
//const bool enableValidationLayers = false;
//#else
//const bool enableValidationLayers = true;
//#endif


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
    for (AComponent* comp : _components) {
        delete comp;
    }
}


void NNE::Application::Init()
{
    glfwInit();
    VKManager->CreateVulkanInstance();
    VKManager->pickPhysicalDevice();
    Open();

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
    
    while (!glfwWindowShouldClose(window)) {
        delta = GetDeltaTime();
        glfwPollEvents();

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
}

void NNE::Application::Open()
{
    CreateWindow(800, 600);
}

void NNE::Application::Quit()
{
    vkDestroyInstance(VKManager->instance, nullptr);

    glfwDestroyWindow(window);

    glfwTerminate();
}

int NNE::Application::GenerateID()
{
    _genericID++;
    return _genericID;
}

float NNE::Application::GetDeltaTime()
{
    std::clock_t currentFrameTime = std::clock();
    float deltaTime = float(currentFrameTime - lastFrameTime) / CLOCKS_PER_SEC;
    lastFrameTime = currentFrameTime;
    return deltaTime;
}

GLFWwindow* NNE::Application::CreateWindow(int width, int height)
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, "Vulkan window", nullptr, nullptr);
    return window;
}

NNE::Application* NNE::Application::GetInstance()
{
    return Instance;
}
