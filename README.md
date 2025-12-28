# MFL.Playbox.1

The MFL.Playbox.1 is a fantasy console, with the following specs:

* C1000 central processing unit @ 1.7 MHz
* V1000 video display processor
* 4 KB work RAM
* 3 KB video RAM

# Building and running

This project includes a CMakeLists.txt file, so you can build it with CMake. This program requires the SDL3 DLL/shared library.

You can simply run the executable by providing it a path to a cartridge file as the only argument. There isn't yet a tool to create cartridge files, but they're pretty simple: a byte defining the type of board, several bytes defining the components on that board, and the ROM/NVRAM contents.