#include "../vulkanRequires.hpp"

VkApplicationInfo makeInstanceAppInfo(const char* title);
VkInstanceCreateInfo makeInstanceCreateInfo(VkApplicationInfo &appInfo);
void checkGLFWExtensionsAvailability(const char** glfwExtensions, uint32_t glfwExtensionCount);