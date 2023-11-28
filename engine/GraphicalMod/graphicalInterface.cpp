#include "graphicalInterface.hpp"

#if GRAPHICAL_API_IS_VULKAN

    void GraphicalInterface::initWindow() {

        window = vulkanInterface.createWindow(windowTitle, windowWidth, windowHeight);

    };

    void GraphicalInterface::initGraphicalAPI() {

        vulkanInterface.maxConcurrentFrames = maxConcurrentFrames;

        vulkanInterface.createInstance(windowTitle);

        vulkanInterface.createWindowSurface();

        vulkanInterface.pickPhysicalDevice();
        vulkanInterface.createLogicalDevice();

        vulkanInterface.createSwapChain();
        vulkanInterface.createImageViews();

        vulkanInterface.createRenderPass();
        vulkanInterface.createGraphicsPipeline();
        vulkanInterface.createFramebuffers();

        vulkanInterface.createCommandPool();
        vulkanInterface.createCommandBuffers();

        vulkanInterface.createSyncObjects();

    };

    void GraphicalInterface::drawFrame() {
        
        vkWaitForFences(vulkanInterface.device, 1, &vulkanInterface.inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(
            vulkanInterface.device,
            vulkanInterface.swapChain,
            UINT64_MAX,
            vulkanInterface.imageAvailableSemaphores[currentFrame],
            VK_NULL_HANDLE,
            &imageIndex
        );

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            vulkanInterface.recreateSwapChain();
            return;
        } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("Failed to acquire swap chain image!");
        };

        vkResetFences(vulkanInterface.device, 1, &vulkanInterface.inFlightFences[currentFrame]);

        vkResetCommandBuffer(vulkanInterface.commandBuffers[currentFrame], 0);
        vulkanInterface.recordCommandBuffer(vulkanInterface.commandBuffers[currentFrame], imageIndex);


        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = {vulkanInterface.imageAvailableSemaphores[currentFrame]};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &vulkanInterface.commandBuffers[currentFrame];

        VkSemaphore signalSemaphores[] = {vulkanInterface.renderFinishedSemaphores[currentFrame]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        if (vkQueueSubmit(vulkanInterface.graphicsQueue, 1, &submitInfo, vulkanInterface.inFlightFences[currentFrame]) != VK_SUCCESS) {

            throw std::runtime_error("Failed to submit draw command buffer!");

        }


        VkPresentInfoKHR presentInfo{};

        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {vulkanInterface.swapChain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(vulkanInterface.presentQueue, &presentInfo);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
            vulkanInterface.framebufferResized_FLAG = false;
            vulkanInterface.recreateSwapChain();
        } else if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to present swap chain image!");
        };

        currentFrame = (currentFrame + 1) % maxConcurrentFrames;

    };

    void GraphicalInterface::waitDeviceToFinish() {

        vkDeviceWaitIdle(vulkanInterface.device);

    };

    void GraphicalInterface::closeWindow() {

        glfwDestroyWindow(window);
        glfwTerminate();

    };

    void GraphicalInterface::shutdownGraphicalAPI() {

        vulkanInterface.cleanUpVkResources();

    };

#endif


#if GRAPHICAL_API_IS_OPENGL

    void GraphicalInterface::initWindow() {



    };

    void GraphicalInterface::initGraphicalAPI() {



    };

    void GraphicalInterface::closeWindow() {



    };

    void GraphicalInterface::shutdownGraphicalAPI() {



    };

#endif