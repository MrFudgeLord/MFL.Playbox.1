#include "../c1000.hpp"

void C1000::NOT_a() {
    asm("not             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0xbf                         \n"
        "and             ah, 0x40                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::NOT_b() {
    asm("not             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0xbf                         \n"
        "and             ah, 0x40                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}
