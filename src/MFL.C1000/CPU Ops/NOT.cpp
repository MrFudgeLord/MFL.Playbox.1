#include "..\c1000.hpp"

void C1000::NOT_a() {
    asm("not             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10111111                            \n"
        "and             ah, 0b01000000                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(a), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void C1000::NOT_b() {
    asm("not             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10111111                            \n"
        "and             ah, 0b01000000                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(b), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}
