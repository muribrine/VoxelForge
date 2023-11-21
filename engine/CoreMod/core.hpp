#include "../GraphicalMod/graphicalInterface.hpp"

class VoxelForge {

    public:

        void run();
        void mainLoop();
        void shutdown();

    private:

        GraphicalInterface graphicalInterface;

};