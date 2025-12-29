#include "../c1000.hpp"

void C1000::TEST_a_b() {
    asm("test            %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [src] "+r"(b), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::TEST_b_a() {
    asm("test            %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [src] "+r"(b), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::TEST_a_iB() {
    uint8_t imm = fetchImmByte();
    asm("test            %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [src] "+r"(imm), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::TEST_b_iB() {
    uint8_t imm = fetchImmByte();
    asm("test            %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [src] "+r"(imm), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}
