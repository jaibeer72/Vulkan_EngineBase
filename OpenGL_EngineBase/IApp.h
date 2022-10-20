#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#include "VkDebugUtils.h"

#pragma region Macros

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

#pragma endregion


class IApp
{
public:
    const char* appName = "Application Name";
    void run();
private:
    // Private variables 
    GLFWwindow* m_Window;
    VkInstance m_Instance;
    uint32_t m_Width = 800, m_Height = 600; 
    const char* m_EngineName = "BaseEngine"; 
    VkDebugUtilsMessengerEXT m_DebugMessenger;

    void initWindow(uint32_t WIDTH, uint32_t HEIGHT);
    void initVulkan();
    void mainLoop();
    void cleanup();
    void createInstance();
 /*   VkResult vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkInstance* instance); */
};