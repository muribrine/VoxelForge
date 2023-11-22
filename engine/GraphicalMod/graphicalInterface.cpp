#include "graphicalInterface.hpp"

#if GRAPHICAL_API_IS_VULKAN

    void GraphicalInterface::initWindow() {

        window = vulkanInterface.createWindow(windowTitle, windowWidth, windowHeight);

    };

    void GraphicalInterface::initGraphicalAPI() {

        vulkanInterface.createInstance(windowTitle);
        vulkanInterface.createWindowSurface(window);
        vulkanInterface.pickPhysicalDevice();
        vulkanInterface.createLogicalDevice();
        vulkanInterface.createSwapChain(window);

    };

    void GraphicalInterface::closeWindow() {

        glfwDestroyWindow(window);
        glfwTerminate();

    };

    void GraphicalInterface::shutdownGraphicalAPI() {

        vulkanInterface.DestroySwapChain();
        vulkanInterface.DestroyLogicalDevice();
        vulkanInterface.DestroySurface();
        vulkanInterface.DestroyInstance();

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