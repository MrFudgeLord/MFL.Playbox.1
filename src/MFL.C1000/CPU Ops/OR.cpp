#include "../c1000.hpp"

void C1000::OR_a_b() {
    asm("or              %[dest], %[src]                                 \n"
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

void C1000::OR_a_iB() {
    uint8_t imm = fetchImmByte();
    asm("or              %[dest], %[src]                                 \n"
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

void C1000::OR_a_dB() {
    uint16_t addr = fetchImmWord();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_a_zpdB() {
    uint16_t addr = fetchImmByte();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_a_zpxB() {
    uint16_t addr = x;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_a_zpyB() {
    uint16_t addr = y;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_a_zpzB() {
    uint16_t addr = z;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_a_izpxB() {
    uint16_t addr = x;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_a_izpyB() {
    uint16_t addr = y;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_a_izpzB() {
    uint16_t addr = z;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_a_dxB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) x;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_a_dyB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) y;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_a_dzB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) z;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(a), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_b_a() {
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [src] "+r"(b), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_b_iB() {
    uint8_t imm = fetchImmByte();
    asm("or              %[dest], %[src]                                 \n"
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

void C1000::OR_b_dB() {
    uint16_t addr = fetchImmWord();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_b_zpdB() {
    uint16_t addr = fetchImmByte();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_b_zpxB() {
    uint16_t addr = x;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_b_zpyB() {
    uint16_t addr = y;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_b_zpzB() {
    uint16_t addr = z;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_b_izpxB() {
    uint16_t addr = x;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_b_izpyB() {
    uint16_t addr = y;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_b_izpzB() {
    uint16_t addr = z;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_b_dxB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) x;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_b_dyB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) y;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}

void C1000::OR_b_dzB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) z;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("or              %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr %[flags], 0x3f                         \n"
        "and             ah, 0xc0                                        \n"
        "mov             bl, ah                                          \n"
        "or              %[flags], bl                                    \n"
        : [dest] "+r"(b), [src] "+r"(val), [flags] "+m"(f)
        :
        : "ah", "bl", "cc");
    addCyclePreemptable();
}
