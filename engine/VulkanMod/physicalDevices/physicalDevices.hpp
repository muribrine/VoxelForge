#include "../vulkanRequires.hpp"

std::vector<VkPhysicalDevice> getPhysicalDevices(VkInstance instance);
bool deviceIsSuitable(VkPhysicalDevice device);
int scoreDevice(VkPhysicalDevice device);
VkPhysicalDevice selectBestPhysicalDevice(std::vector<VkPhysicalDevice> candidates);