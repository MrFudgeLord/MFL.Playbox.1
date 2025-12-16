#include "..\c1000.hpp"

void C1000::ADC_a_b() {
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_a_iB() {
    uint8_t imm = fetchImmByte();
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_a_dB() {
    uint16_t addr = fetchImmWord();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_a_zpdB() {
    uint16_t addr = fetchImmByte();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_a_zpxB() {
    uint16_t addr = x;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_a_zpyB() {
    uint16_t addr = y;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_a_zpzB() {
    uint16_t addr = z;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_a_izpxB() {
    uint16_t addr = x;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_a_izpyB() {
    uint16_t addr = y;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_a_izpzB() {
    uint16_t addr = z;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_a_dxB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) x;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_a_dyB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) y;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             byte ptr  %[flags], 0x1e                        \n"
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

void C1000::ADC_a_dzB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) z;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_b_a() {
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_b_iB() {
    uint8_t imm = fetchImmByte();
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_b_dB() {
    uint16_t addr = fetchImmWord();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_b_zpdB() {
    uint16_t addr = fetchImmByte();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_b_zpxB() {
    uint16_t addr = x;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_b_zpyB() {
    uint16_t addr = y;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_b_zpzB() {
    uint16_t addr = z;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_b_izpxB() {
    uint16_t addr = x;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_b_izpyB() {
    uint16_t addr = y;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_b_izpzB() {
    uint16_t addr = z;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_b_dxB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) x;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_b_dyB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) y;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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

void C1000::ADC_b_dzB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) z;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0x01                                        \n"
        "add             al, 0xff                                        \n"
        "adc             %[dest], %[src]                                 \n"
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
