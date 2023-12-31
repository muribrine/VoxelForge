#include "physicalDevices.hpp"
#include "../queues/queues.hpp"
#include "../swapChains/swapChains.hpp"

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

bool deviceIsSuitable(VkPhysicalDevice device, VkSurfaceKHR surface) {

    /*
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
    */

    bool extensionsSupported = checkDeviceExtensionSupport(device);
    bool swapChainAdequate = false;

    QueueFamilyIndices indices = findQueueFamilies(device, surface);
    if (extensionsSupported) {
        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device, surface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    };

    return indices.isComplete() && extensionsSupported && swapChainAdequate;

};

bool checkDeviceExtensionSupport(VkPhysicalDevice device) {

    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();

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