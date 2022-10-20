#include "IApp.h"

void IApp::run()
{
    initWindow(m_Width, m_Height);
    initVulkan();
    mainLoop();
    cleanup();
}
void IApp::initWindow(uint32_t WIDTH, uint32_t HEIGHT)
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_Window = glfwCreateWindow(WIDTH, HEIGHT, appName, nullptr, nullptr);
}
void IApp::initVulkan()
{
    createInstance();
    Engine_VkDebugUtils::setupDebugMessenger(m_Instance, m_DebugMessenger); 
}
void IApp::mainLoop()
{
    while (!glfwWindowShouldClose(m_Window)) {
        glfwPollEvents();
    }
}
void IApp::cleanup()
{
    if (enableValidationLayers) {
        Engine_VkDebugUtils::DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);
    }

    vkDestroyInstance(m_Instance, nullptr);

    glfwDestroyWindow(m_Window);

    glfwTerminate();
}

void IApp::createInstance()
{
    if (enableValidationLayers && !Engine_VkDebugUtils::checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = appName;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = m_EngineName;
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = Engine_VkDebugUtils::getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        Engine_VkDebugUtils::populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else {
        createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

