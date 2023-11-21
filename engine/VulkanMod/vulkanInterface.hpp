#include "vulkanRequires.hpp"

#include "./physicalDevices/physicalDevices.hpp"
#include "./queues/queues.hpp"
#include "./swapChains/swapChains.hpp"
#include "./vkInstance/vkInstance.hpp"
#include "./windowing/windowing.hpp"

class VulkanInterface {

    public:

        GLFWwindow* createWindow(const char* windowTitle, uint32_t windowWidth, uint32_t windowHeight);
        void createInstance(const char* title);
        void createWindowSurface(GLFWwindow* window);
        void pickPhysicalDevice();
        void createLogicalDevice();

        void vkDestroySurface();
        void closeInstance();
        void closeLogicalDevice();

    private:

        VkInstance instance;
        VkPhysicalDevice physicalDevice;
        VkDevice device;
        VkQueue graphicsQueue;
        VkQueue presentQueue;
        VkSurfaceKHR surface;

};