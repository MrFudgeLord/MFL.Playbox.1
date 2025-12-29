# MFL.Playbox.1

The MFL.Playbox.1 is a fantasy console, with the following specs:

* C1000 central processing unit @ 1.7 MHz
* V1000 video display processor
* 4 KB work RAM
* 3 KB video RAM
* A single controller

## Controls

The controller is practically just an NES controller. The keys are mapped as follows:

DPad: WASD
A: J
B: L
Start: [ (left bracket)
Select ] (right bracket)

Support for key remapping will probably be added soon.

# Building and running

This project includes a CMakeLists.txt file, so you can build it with CMake. This program requires the SDL3 DLL/shared library.

You can simply run the executable by providing it a path to a cartridge file as the only argument, or, additionally, a path to an NVRAM file (you can have multiple states for each cartridge). There isn't yet a tool to create cartridge files, but they're pretty simple: a byte defining the type of board, several bytes defining the components on that board, and the ROM contents. NVRAM files are literally just the contents of NVRAM for that cartridge.