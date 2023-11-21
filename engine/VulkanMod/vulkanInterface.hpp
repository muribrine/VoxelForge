#include "vulkanRequires.hpp"

#include "./logicalDevices/logicalDevices.hpp"
#include "./physicalDevices/physicalDevices.hpp"
#include "./queues/queues.hpp"
#include "./swapChains/swapChains.hpp"
#include "./vkInstance/vkInstance.hpp"
#include "./windowing/windowing.hpp"

class VulkanInterface {

    public:

        void createInstance(const char* title);
        void pickPhysicalDevice();
        void createLogicalDevice();

        void closeInstance();
        void closeLogicalDevice();

    private:

        VkInstance instance;
        VkPhysicalDevice physicalDevice;
        VkDevice device;

};