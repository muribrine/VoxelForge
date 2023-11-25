#define GRAPHICAL_API_IS_VULKAN 1
#define GRAPHICAL_API_iS_OPENGL 0

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#if GRAPHICAL_API_IS_VULKAN

    #include "../VulkanMod/vulkanInterface.hpp"

    class GraphicalInterface {

        public:

            const uint32_t windowWidth = 800;
            const uint32_t windowHeight = 600;
            const char* windowTitle = "VoxelForge";

            GLFWwindow* window;

            void initWindow();
            void initGraphicalAPI();

            void drawFrame();
            void waitDeviceToFinish();

            void closeWindow();
            void shutdownGraphicalAPI();

        private:

            VulkanInterface vulkanInterface;

};

#endif


#if GRAPHICAL_API_iS_OPENGL

    #include <GLFW/glfw3.h>

    #include "../OpenGLMod/openGLInterface.hpp"

    class GraphicalInterface {

        public:

            GLFWwindow* window;

            void initWindow();
            void initGraphicalAPI();

            void closeWindow();
            void shutdownGraphicalAPI();

        private:

            OpenGLInterface openGLInterface;
    
    }

#endif

