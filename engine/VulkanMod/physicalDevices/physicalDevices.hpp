#include "../vulkanRequires.hpp"

std::vector<VkPhysicalDevice> getPhysicalDevices(VkInstance instance);
bool deviceIsSuitable(VkPhysicalDevice device);
int scoreDevice(VkPhysicalDevice device);
VkPhysicalDevice selectBestPhysicalDevice(std::vector<VkPhysicalDevice> candidates);

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);