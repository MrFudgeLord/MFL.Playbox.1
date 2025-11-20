#include "..\cpu.hpp"

void CPU::LSL_a() {
    asm("shl             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10011110                            \n"
        "and             ah, 0b01100001                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(a), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void CPU::LSL_b() {
    asm("shl             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10011110                            \n"
        "and             ah, 0b01100001                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(b), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void CPU::ASR_a() {
    asm("sar             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10011110                            \n"
        "and             ah, 0b01100001                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(a), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void CPU::ASR_b() {
    asm("sar             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10011110                            \n"
        "and             ah, 0b01100001                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(b), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void CPU::ROL_a() {
    asm("rol             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10011110                            \n"
        "and             ah, 0b01100001                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(a), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void CPU::ROL_b() {
    asm("rol             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10011110                            \n"
        "and             ah, 0b01100001                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(b), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void CPU::ROR_a() {
    asm("ror             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10011110                            \n"
        "and             ah, 0b01100001                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(a), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void CPU::ROR_b() {
    asm("ror             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10011110                            \n"
        "and             ah, 0b01100001                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(b), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}
