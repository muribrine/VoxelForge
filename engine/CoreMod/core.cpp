#include "core.hpp"

void VoxelForge::run() {

    graphicalInterface.initWindow();
    graphicalInterface.initGraphicalAPI();

    mainLoop();

};


void VoxelForge::mainLoop() {

    while (!glfwWindowShouldClose(graphicalInterface.window)) {
        glfwPollEvents();
    }

    shutdown();

};


void VoxelForge::shutdown() {

    graphicalInterface.shutdownGraphicalAPI();
    graphicalInterface.closeWindow();

};