#include "../c1000.hpp"

void C1000::INC_x() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(x), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::INC_y() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(y), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::INC_z() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(z), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::DEC_x() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(x), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::DEC_y() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(y), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::DEC_z() {
    asm("inc             %[dest]                                         \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(z), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}
