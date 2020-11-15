# STAR BATTLE COMMAND AND THE KOSMONAUT ENGINE
Star Battle Command is a soon to be space RTS and the kosmonaut engine,
is a self written 3D game, which consumes currently most of my coding time.

## How to build everything?
The kosmonaut engine currently depends on the network library NNG, OpenGL 4.5,
 SDL2 and CMake. If you are compiling for your own machine you can use the
following commands. If you want to cross compile from a Linux to Windows you need
to follow the next set of instructions.
  
`mkdir build`  
`cd build`  
`cmake ..`  
`make`  

### Crosscompiling from Linux to Windows
Sadly CMake isn't working for crosscompilation in this project so far. Therefore
we need to use plain old make and mingw32 in its 64bit version.

First you need to unzip that windows.zip in the main directory.
Afterwards everything gets compiled with  
`make windows`