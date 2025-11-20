#include "..\cpu.hpp"

void CPU::TEST_a_b() {
    asm("test            %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             [flags], 0b10011111                             \n"
        "and             ah, 0b01100000                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(b), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void CPU::TEST_b_a() {
    asm("test            %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             [flags], 0b10011111                             \n"
        "and             ah, 0b01100000                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(b), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void CPU::TEST_a_iB() {
    uint8_t imm = fetchImmByte();
    asm("test            %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             [flags], 0b10011111                             \n"
        "and             ah, 0b01100000                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(imm), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}

void CPU::TEST_b_iB() {
    uint8_t imm = fetchImmByte();
    asm("test            %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             [flags], 0b10011111                             \n"
        "and             ah, 0b01100000                                  \n"
        "or              %[flags], ah                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(imm), [flags] "+rm"(f)
        :
        : "ah");
    addCyclePreemptable();
}
