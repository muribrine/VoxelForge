#include "vulkanInterface.hpp"

GLFWwindow* VulkanInterface::createWindow(const char* windowTitle, uint32_t windowWidth, uint32_t windowHeight) {

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    return glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);

};


void VulkanInterface::createInstance(const char* title) {

    VkApplicationInfo appInfo = makeInstanceAppInfo(title);
    VkInstanceCreateInfo createInfo = makeInstanceCreateInfo(appInfo);

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create instance!");
    };

};


void VulkanInterface::createWindowSurface(GLFWwindow* window) {

    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create window surface!");
    }
    
}


void VulkanInterface::pickPhysicalDevice() {

    physicalDevice = VK_NULL_HANDLE;
    std::vector<VkPhysicalDevice> devices = getPhysicalDevices(instance);
    std::vector<VkPhysicalDevice> candidates;

    for (const auto& device : devices) {

        if (deviceIsSuitable(device, surface)) { candidates.push_back(device); }

    }

    physicalDevice = selectBestPhysicalDevice(candidates);

    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
    std::cout << "Selected PhysicalDevice: " << deviceProperties.deviceName << "\n";

};


void VulkanInterface::createLogicalDevice() {

    QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;

    for (uint32_t queueFamily : uniqueQueueFamilies) {

        VkDeviceQueueCreateInfo queueCreateInfo{};

        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        queueCreateInfos.push_back(queueCreateInfo);

    };

    VkPhysicalDeviceFeatures deviceFeatures{};
    VkDeviceCreateInfo createInfo{};

    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();
    createInfo.enabledLayerCount = 0;

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {

        throw std::runtime_error("Failed to create logical device!");

    };

    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
    vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);

};


void VulkanInterface::createSwapChain(GLFWwindow* window) {

    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice, surface);

    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    swapChainExtent = chooseSwapExtent(swapChainSupport.capabilities, window);

    uint32_t imageCount = selectImageCount(swapChainSupport);


    VkSwapchainCreateInfoKHR createInfo = makeSwapChainCreateInfo(
        surface,
        imageCount,
        swapChainExtent,
        surfaceFormat,
        physicalDevice,
        swapChainSupport,
        presentMode
    );


    if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {

        throw std::runtime_error("Failed to create swap chain!");

    };

    vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

    swapChainImageFormat = surfaceFormat.format;

};


void VulkanInterface::createImageViews() {

    swapChainImageViews.resize(swapChainImages.size());

    for (size_t i = 0; i < swapChainImages.size(); i++) {

        VkImageViewCreateInfo createInfo = makeImageViewCreateInfo(i, swapChainImageFormat, swapChainImages);

        if (vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {

            throw std::runtime_error("Failed to create image view!");
            
        };

    };

};


void VulkanInterface::createGraphicsPipeline() {

    auto vertShaderCode = readFile("./shaders/vert.spv");
    auto fragShaderCode = readFile("./shaders/frag.spv");


    VkShaderModule vertShaderModule = createShaderModule(vertShaderCode, device);
    VkShaderModule fragShaderModule = createShaderModule(fragShaderCode, device);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo = createShaderStageCreateInfo(vertShaderModule, std::string("vert"));
    VkPipelineShaderStageCreateInfo fragShaderStageInfo = createShaderStageCreateInfo(fragShaderModule, std::string("frag"));


    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};


    vkDestroyShaderModule(device, fragShaderModule, nullptr);
    vkDestroyShaderModule(device, vertShaderModule, nullptr);

};


void VulkanInterface::cleanUpVkResources() {

    for (auto imageView : swapChainImageViews) {
        vkDestroyImageView(device, imageView, nullptr);
    };

    vkDestroySwapchainKHR(device, swapChain, nullptr);
    vkDestroyDevice(device, nullptr);
    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);

};