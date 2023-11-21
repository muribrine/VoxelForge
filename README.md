# VoxelForge

A 3d game engine / game framework written in C++ using the Vulkan API and OpenGL.

## Building and running

```console
make all
./bin/game
```

## Switching between Vulkan and OpenGL

Just use these define statements inside of "graphicalInterface.hpp", on the GraphicalMod folder. The compiler will take care of the rest.

```hpp
#define GRAPHICAL_API_IS_VULKAN 1
#define GRAPHICAL_API_iS_OPENGL 0
```
