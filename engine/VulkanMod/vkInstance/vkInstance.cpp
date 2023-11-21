#include "vkInstance.hpp"

VkApplicationInfo makeInstanceAppInfo(const char* title) {

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = title;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    return appInfo;

};

VkInstanceCreateInfo makeInstanceCreateInfo(VkApplicationInfo &appInfo) {

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    checkGLFWExtensionsAvailability(glfwExtensions, glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    return createInfo;

};

void checkGLFWExtensionsAvailability(const char** glfwExtensions, uint32_t glfwExtensionCount) {

    uint32_t vkExtensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, nullptr);

    std::vector<VkExtensionProperties> extensions(vkExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, extensions.data());

    std::cout << "Required GLFW extensions: \n";
    for (uint32_t i = 0; i < glfwExtensionCount; i++) {
        const char* GLFWExtension = glfwExtensions[i];
        std::cout << '\t' << GLFWExtension << '\n';
    };

    std::cout << "Available extensions ( Vulkan ): \n";
    for (const auto& extension : extensions) {
        std::cout << '\t' << extension.extensionName << '\n';
    };

};