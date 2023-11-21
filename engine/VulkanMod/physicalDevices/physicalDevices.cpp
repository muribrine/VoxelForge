#include "physicalDevices.hpp"

std::vector<VkPhysicalDevice> getPhysicalDevices(VkInstance instance) {

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("Failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    return devices;

};

bool deviceIsSuitable(VkPhysicalDevice device) {

    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    QueueFamilyIndices indices = findQueueFamilies(device);
    return indices.isComplete();

};

int scoreDevice(VkPhysicalDevice device) {

    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);


    int score = 0;

    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        score += 1000;
    }
    score += deviceProperties.limits.maxImageDimension2D;
    if (!deviceFeatures.geometryShader) {
        score = 0;
    }
    
    return score;

}

VkPhysicalDevice selectBestPhysicalDevice(std::vector<VkPhysicalDevice> candidates) {

    std::multimap<int, VkPhysicalDevice> candidateMap;
    VkPhysicalDevice selectedDevice = VK_NULL_HANDLE;

    for (const auto& candidate : candidates) {

        int score = scoreDevice(candidate);
        candidateMap.insert(std::make_pair(score, candidate));

    }

    if (candidateMap.rbegin()->first > 0) {
        selectedDevice = candidateMap.rbegin()->second;
    } else {
        throw std::runtime_error("Failed to find a suitable GPU!");
    }

    return selectedDevice;
    
};



QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {

    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        if (indices.isComplete()) {
            break;
        }

        i++;
    };

    return indices;

};