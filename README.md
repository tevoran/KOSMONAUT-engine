# KOSMONAUT ENGINE
The KOSMONAUT-ENGINE is a game engine written in C with OpenGL, which I originally
to use for a game but engine is apparently more fun. If you want to use the engine
you can do it, even if it is not production ready but it has some important features.
OBJ models can be used, BMP textures are working, rotation without gimbal lock,
different primitives, skyboxes, network support via NNG and input via SDL2.

## How to build everything?
The kosmonaut engine currently depends on the network library NNG, OpenGL 4.5,
SDL2 and CMake. All of these have to be installed on your computer for a successful
compilation. If you are compiling for your own machine you can use the
following commands. If you want to cross compile from a Linux to Windows you need
to follow the next set of instructions.
  
`mkdir build`  
`cd build`  
`cmake ..`  
`make`  
`cp SBC ../`

If you need only the engine library then use instead of `make`  
`make KOSMONAUT`

### Crosscompiling from Linux to Windows
Sadly CMake isn't working for crosscompilation in this project so far. Therefore
we need to use plain old make and mingw32 in its 64bit version.

First you need to unzip that windows.zip in the main directory.
Afterwards everything gets compiled with  
`make windows`
