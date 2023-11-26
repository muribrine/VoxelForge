# VoxelForge

A 3d game engine / game framework written in C++ using the Vulkan API and OpenGL.

## Building and running

To just compile the game, run:

```console
chmod +x compileGame.sh
./compileGame.sh
```

To compile the shaders and the game, run:
```console
chmod +x ./shaders/compileShaders.sh
chmod +x compileAll.sh
./compileAll.sh
```

( Run "chmod" only on the first time. )

## Switching between Vulkan and OpenGL

Just use these define statements inside of "graphicalInterface.hpp", on the GraphicalMod folder. The compiler will take care of the rest.

```hpp
#define GRAPHICAL_API_IS_VULKAN 1
#define GRAPHICAL_API_iS_OPENGL 0
```

## Compiling Shaders ( Vulkan )

All shaders are found within the 'shaders' folder along with the compilation script.
First, install the Vulkan SDK ( may have to modify the script to fit your SDK version ).
After that, run:
```console
cd shaders
chmod +x compileShaders.sh
./compileShaders.sh
```