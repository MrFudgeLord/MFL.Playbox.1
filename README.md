# Playbox.1

The Playbox.1 is a fantasy console, with the following specs:

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

You can simply run the executable by providing it a path to a cartridge file as the only argument, or, additionally, a path to an NVRAM file (you can have multiple states for each cartridge). There isn't yet a tool to create cartridge files, but they're pretty simple: a byte for the version of the file, a byte defining the type of board, several bytes defining the components on that board, and the ROM contents. NVRAM files are literally just the contents of NVRAM for that cartridge.

# How it works

The emulator consists of a scheduler, a `dummy` device which mediates the host and guest, and of course, a bunch of emulated components.

The emulator runs on a sort of tick clock, with about 1 billion ticks in each second. The scheduler consists of a priority queue of events which have to occur at a specific time, such as rendering a scanline or a timer interrupt.

The emulated components are based in the motherboard, which contains a set of **busses**, **address-to-signal decoders**, and **sockets**. Sockets represent generalized classes of components based on their bus interface. For example, the S1003/4 RAM chips use the same B3100 socket, an interface of a 16-bit address bus, 8-bit data bus, and a 1-bit read/write line. Cartridge boards add yet another level of abstraction: they are, in and of themselves, a socket, so the main motherboard can connect to any number of different cartridge boards, and it just needs to provide an address bus, data bus, interrupt lines, etc. The cartridge boards also contain sockets, so they can contain different ROM/RAM/NVRAM chips and coprocessors. When a component needs to use the bus to communicate to another specific device based on address (ex. CPU or VDP fetching from memory, but not, for example, the VDP firing an interrupt or locking VRAM), it writes the values to the bus and then signals an address-to-signal decoder. The decoder determines the appropriate device to signal based on the attached address bus (which could be another signal decoder; see the chaining of the memMapDecoder to the hwRegDecoder of the M1000), and the signaled device acts on that. The signaled device returns a number of ticks which *essentially* represent the number of nanoseconds it took to complete the operation, in emulated time, and this is specifically used by the CPU to determine how many cycles it needs to wait for.

The CPU is a special component, in that it gets to freely run as the main loop, and yields to the scheduler when an event needs to be handled. The VDP (video display processor) renders scanline-by-scanline, but this is integrated into the architecture by having VRAM be locked during rendering.