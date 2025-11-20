#include "..\cpu.hpp"

void CPU::NOT_a() {
    asm("not             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             [flags], 0b11011111                             \n"
        "and             0b00100000, ah                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(a), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void CPU::NOT_b() {
    asm("not             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             [flags], 0b11011111                             \n"
        "and             0b00100000, ah                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(b), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}
