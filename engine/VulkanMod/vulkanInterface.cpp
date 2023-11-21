#include "vulkanInterface.hpp"

void VulkanInterface::createInstance(const char* title) {

    VkApplicationInfo appInfo = makeInstanceAppInfo(title);
    VkInstanceCreateInfo createInfo = makeInstanceCreateInfo(appInfo);

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create instance!");
    };

};

void VulkanInterface::pickPhysicalDevice() {

    physicalDevice = VK_NULL_HANDLE;
    std::vector<VkPhysicalDevice> devices = getPhysicalDevices(instance);
    std::vector<VkPhysicalDevice> candidates;

    for (const auto& device : devices) {

        if (deviceIsSuitable(device)) { candidates.push_back(device); }
    }

    physicalDevice = selectBestPhysicalDevice(candidates);

    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
    std::cout << "Selected PhysicalDevice: " << deviceProperties.deviceName << "\n";

};

void VulkanInterface::createLogicalDevice() {

    VkDeviceQueueCreateInfo queueCreateInfo = makeLogicalDeviceQueueCreateInfo(physicalDevice);
    VkDeviceCreateInfo createInfo = makeLogicalDeviceCreateInfo(queueCreateInfo);

    std::cout << "creating device... \n";

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

}

void VulkanInterface::closeInstance() {

    vkDestroyInstance(instance, nullptr);
    

};

void VulkanInterface::closeLogicalDevice() {

    vkDestroyDevice(device, nullptr);

}