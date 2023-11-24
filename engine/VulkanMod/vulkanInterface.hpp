#include "vulkanRequires.hpp"

#include "./physicalDevices/physicalDevices.hpp"
#include "./queues/queues.hpp"
#include "./swapChains/swapChains.hpp"
#include "./vkInstance/vkInstance.hpp"
#include "./graphicalPipeline/graphicalPipeline.hpp"
#include "./utils/readFile.hpp"

class VulkanInterface {

    public:

        GLFWwindow* createWindow(const char* windowTitle, uint32_t windowWidth, uint32_t windowHeight);
        void createInstance(const char* title);
        void createWindowSurface(GLFWwindow* window);
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createSwapChain(GLFWwindow* window);
        void createImageViews();
        void createRenderPass();
        void createGraphicsPipeline();

        void cleanUpVkResources();

    private:

        VkInstance instance;

        VkPhysicalDevice physicalDevice;
        VkDevice device;

        VkQueue graphicsQueue;
        VkQueue presentQueue;
        
        VkSurfaceKHR surface;

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;

        std::vector<VkImageView> swapChainImageViews;

        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        VkRenderPass renderPass;

};