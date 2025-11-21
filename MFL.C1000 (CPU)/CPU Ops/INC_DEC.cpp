#include "..\cpu.hpp"

void CPU::INC_x() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001111                            \n"
        "and             ah, 0b01110000                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(x), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::INC_y() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001111                            \n"
        "and             ah, 0b01110000                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(y), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::INC_z() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001111                            \n"
        "and             ah, 0b01110000                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(z), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::DEC_x() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001111                            \n"
        "and             ah, 0b01110000                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(x), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::DEC_y() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001111                            \n"
        "and             ah, 0b01110000                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(y), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::DEC_z() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001111                            \n"
        "and             ah, 0b01110000                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(z), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}
