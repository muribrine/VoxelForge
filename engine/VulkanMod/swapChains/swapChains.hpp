#include "../vulkanRequires.hpp"

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);
VkImageViewCreateInfo makeImageViewCreateInfo(size_t i, VkFormat swapChainImageFormat, std::vector<VkImage> swapChainImages);
uint32_t selectImageCount(SwapChainSupportDetails swapChainSupport);
VkSwapchainCreateInfoKHR makeSwapChainCreateInfo(VkSurfaceKHR surface, uint32_t imageCount, VkExtent2D extent, VkSurfaceFormatKHR surfaceFormat, VkPhysicalDevice physicalDevice, SwapChainSupportDetails swapChainSupport, VkPresentModeKHR presentMode);
void cleanUpSwapChain(VkDevice device, std::vector<VkFramebuffer> swapChainFramebuffers, std::vector<VkImageView> swapChainImageViews, VkSwapchainKHR swapChain);