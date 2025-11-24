#include "..\c1000.hpp"

void C1000::LSL_a() {
    asm("shl             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00111110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(a), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void C1000::LSL_b() {
    asm("shl             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00111110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(b), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void C1000::ASR_a() {
    asm("sar             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00111110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(a), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void C1000::ASR_b() {
    asm("sar             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00111110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(b), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void C1000::ROL_a() {
    asm("rol             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00111110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(a), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void C1000::ROL_b() {
    asm("rol             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00111110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(b), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void C1000::ROR_a() {
    asm("ror             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00111110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(a), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void C1000::ROR_b() {
    asm("ror             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00111110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(b), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}
