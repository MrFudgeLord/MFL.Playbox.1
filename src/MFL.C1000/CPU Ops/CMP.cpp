#include "..\c1000.hpp"

void C1000::CMP_a_b() {
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(a), [src] "+r"(b), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_a_iB() {
    uint8_t imm = fetchImmByte();
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(a), [src] "+r"(imm), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_a_zpxB() {
    uint16_t addr = x;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(a), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_a_zpyB() {
    uint16_t addr = y;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(a), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_a_zpzB() {
    uint16_t addr = z;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(a), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_b_a() {
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(b), [src] "+r"(a), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_b_iB() {
    uint8_t imm = fetchImmByte();
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(b), [src] "+r"(imm), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_b_dxB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + x;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(b), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_b_dyB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + y;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(b), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_b_dzB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + z;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(b), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_x_a() {
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(x), [src] "+r"(a), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_y_a() {
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(y), [src] "+r"(a), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_z_a() {
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(z), [src] "+r"(a), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_x_b() {
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(x), [src] "+r"(b), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_y_b() {
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(y), [src] "+r"(b), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_z_b() {
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(z), [src] "+r"(b), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_x_dB() {
    uint16_t addr = fetchImmWord();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(x), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_y_dB() {
    uint16_t addr = fetchImmWord();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(y), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_z_dB() {
    uint16_t addr = fetchImmWord();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(z), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_x_iB() {
    uint8_t imm = fetchImmByte();
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(x), [src] "+r"(imm), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_y_iB() {
    uint8_t imm = fetchImmByte();
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(y), [src] "+r"(imm), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}

void C1000::CMP_z_iB() {
    uint8_t imm = fetchImmByte();
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x1e                         \n"
        "and             ah, 0xc1                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+r"(z), [src] "+r"(imm), [flags] "+m"(f)
        :
        : "ah", "bl", "cc", "al");
    addCyclePreemptable();
}
