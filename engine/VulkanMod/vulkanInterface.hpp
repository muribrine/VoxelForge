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
        void createFramebuffers();
        void createCommandPool();
        void createCommandBuffers();
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        void createSyncObjects();

        void cleanUpVkResources();

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
        std::vector<VkFramebuffer> swapChainFramebuffers;

        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        VkRenderPass renderPass;

        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;

        size_t maxConcurrentFrames;

};