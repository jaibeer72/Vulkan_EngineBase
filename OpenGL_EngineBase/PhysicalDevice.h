#pragma once
#include <vulkan/vulkan_core.h>
#include <stdexcept>
#include <vector>

class PhysicalDevice
{
public:
	VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
	uint32_t m_DeviceCount = 0; 
	std::vector<VkPhysicalDevice> m_DeviceList; 
	PhysicalDevice(VkInstance instance);

private:
	void EnumirateDeviceList(VkInstance instance, uint32_t& deviceCount, std::vector<VkPhysicalDevice>& DeviceList);
	bool IsDeviceSuitable(VkPhysicalDevice device);
	void FindAndSetSuitablePhysicalDevice(std::vector<VkPhysicalDevice> deviceList);
};
