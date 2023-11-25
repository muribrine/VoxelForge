#include "core.hpp"

void VoxelForge::run() {

    graphicalInterface.initWindow();
    graphicalInterface.initGraphicalAPI();

    mainLoop();

};


void VoxelForge::mainLoop() {

    while (!glfwWindowShouldClose(graphicalInterface.window)) {
        glfwPollEvents();
        graphicalInterface.drawFrame();
    }

    graphicalInterface.waitDeviceToFinish();

    shutdown();

};


void VoxelForge::shutdown() {

    graphicalInterface.shutdownGraphicalAPI();
    graphicalInterface.closeWindow();

};