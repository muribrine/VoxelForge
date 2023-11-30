#include "vulkanRequires.hpp"

#include "./physicalDevices/physicalDevices.hpp"
#include "./queues/queues.hpp"
#include "./swapChains/swapChains.hpp"
#include "./vkInstance/vkInstance.hpp"
#include "./graphicalPipeline/graphicalPipeline.hpp"
#include "./utils/readFile.hpp"

class VulkanInterface {

    public:

        struct Vertex {
            glm::vec2 pos;
            glm::vec3 color;

            static VkVertexInputBindingDescription getBindingDescription() {

                VkVertexInputBindingDescription bindingDescription{};
                bindingDescription.binding = 0;
                bindingDescription.stride = sizeof(Vertex);
                bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

                return bindingDescription;

            };

            static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {

                std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

                attributeDescriptions[0].binding = 0;
                attributeDescriptions[0].location = 0;
                attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
                attributeDescriptions[0].offset = offsetof(Vertex, pos);

                attributeDescriptions[1].binding = 0;
                attributeDescriptions[1].location = 1;
                attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
                attributeDescriptions[1].offset = offsetof(Vertex, color);

                return attributeDescriptions;
                
            };
        };

        const std::vector<Vertex> vertices = {
            {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
        };

        GLFWwindow* createWindow(const char* windowTitle, uint32_t windowWidth, uint32_t windowHeight);
        void createWindowSurface();

        void createInstance(const char* title);
        
        void pickPhysicalDevice();
        void createLogicalDevice();

        void createSwapChain();
        void cleanUpSwapChain();
        void recreateSwapChain();
        void createImageViews();

        void createRenderPass();
        void createGraphicsPipeline();
        void createFramebuffers();

        void createCommandPool();

        void createVertexBuffer();
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        void createCommandBuffers();
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        void createSyncObjects();

        void cleanUpVkResources();

        GLFWwindow* window;

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

        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;

        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;

        bool framebufferResized_FLAG = false;

        size_t maxConcurrentFrames;

};