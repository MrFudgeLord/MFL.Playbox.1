#include "../c1000.hpp"

void C1000::LSL_a() {
    asm("shl             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::LSL_b() {
    asm("shl             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::ASR_a() {
    asm("sar             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::ASR_b() {
    asm("sar             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::ROL_a() {
    asm("rol             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::ROL_b() {
    asm("rol             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::ROR_a() {
    asm("ror             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::ROR_b() {
    asm("ror             %[dest], 1                                      \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}
