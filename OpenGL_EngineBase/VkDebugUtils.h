#pragma once
#include"IApp.h"

const std::vector<const char*> validationLayers = {
"VK_LAYER_KHRONOS_validation"
};


static class Engine_VkDebugUtils
{
public:
	static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT m_DebugMessenger, const VkAllocationCallbacks* pAllocator);
	static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	static void setupDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger);
	static std::vector<const char*> getRequiredExtensions();
	static bool checkValidationLayerSupport();
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
};