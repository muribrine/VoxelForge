#include "graphicalInterface.hpp"

#if GRAPHICAL_API_IS_VULKAN

    void GraphicalInterface::initWindow() {

        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);

    };

    void GraphicalInterface::initGraphicalAPI() {

        vulkanInterface.createInstance(windowTitle);
        vulkanInterface.pickPhysicalDevice();
        vulkanInterface.createLogicalDevice();

    };

    void GraphicalInterface::closeWindow() {

        glfwDestroyWindow(window);
        glfwTerminate();

    };

    void GraphicalInterface::shutdownGraphicalAPI() {

        vulkanInterface.closeLogicalDevice();
        vulkanInterface.closeInstance();

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