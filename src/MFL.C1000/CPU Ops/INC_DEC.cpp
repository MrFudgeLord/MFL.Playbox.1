#include "..\c1000.hpp"

void C1000::INC_x() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011111                            \n"
        "and             ah, 0b11000000                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(x), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::INC_y() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011111                            \n"
        "and             ah, 0b11000000                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(y), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::INC_z() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011111                            \n"
        "and             ah, 0b11000000                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(z), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::DEC_x() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011111                            \n"
        "and             ah, 0b11000000                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(x), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::DEC_y() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011111                            \n"
        "and             ah, 0b11000000                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(y), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::DEC_z() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011111                            \n"
        "and             ah, 0b11000000                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(z), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}
