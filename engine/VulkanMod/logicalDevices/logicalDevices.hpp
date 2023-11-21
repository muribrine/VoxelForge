#include "../vulkanRequires.hpp"

VkDeviceQueueCreateInfo makeLogicalDeviceQueueCreateInfo(VkPhysicalDevice physicalDevice);
VkDeviceCreateInfo makeLogicalDeviceCreateInfo(VkDeviceQueueCreateInfo &queueCreateInfo);