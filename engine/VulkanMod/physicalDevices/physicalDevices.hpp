#include "../vulkanRequires.hpp"

const std::vector<const char*> deviceExtensions = {

    VK_KHR_SWAPCHAIN_EXTENSION_NAME

};

std::vector<VkPhysicalDevice> getPhysicalDevices(VkInstance instance);
bool deviceIsSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
int scoreDevice(VkPhysicalDevice device);
VkPhysicalDevice selectBestPhysicalDevice(std::vector<VkPhysicalDevice> candidates);
bool checkDeviceExtensionSupport(VkPhysicalDevice device);