#include "../engine/CoreMod/core.hpp"

int main() {

    VoxelForge engine;

    try {

        engine.run();
        
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
    
    
};