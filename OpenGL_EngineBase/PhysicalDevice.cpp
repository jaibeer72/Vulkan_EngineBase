#include "PhysicalDevice.h"

PhysicalDevice::PhysicalDevice(VkInstance instance)
{
	vkEnumeratePhysicalDevices(instance, &m_DeviceCount, nullptr);
	if (m_DeviceCount == 0)
	{
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	EnumirateDeviceList(instance, m_DeviceCount, m_DeviceList); 
}

void PhysicalDevice::EnumirateDeviceList(VkInstance instance, uint32_t& deviceCount, std::vector<VkPhysicalDevice> &DeviceList)
{
	vkEnumeratePhysicalDevices(instance, &deviceCount, DeviceList.data()); 
}

void PhysicalDevice::FindAndSetSuitablePhysicalDevice(std::vector<VkPhysicalDevice> deviceList)
{
	for (const VkPhysicalDevice& device : deviceList)
	{
		if (IsDeviceSuitable(device))
		{
			m_PhysicalDevice = device; 
			break;
		}
	}

	if (m_PhysicalDevice == VK_NULL_HANDLE)
	{
		throw std::runtime_error("Failed to find a suitable GPU!!"); 
	}
}

bool PhysicalDevice::IsDeviceSuitable(VkPhysicalDevice device)
{
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	return deviceProperties.deviceType == 
		(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceFeatures.geometryShader);
}


