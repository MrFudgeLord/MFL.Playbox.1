#include "..\cpu.hpp"

void CPU::SBB_a_b() {
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(a), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_a_iB() {
    uint8_t imm = fetchImmByte();
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(imm), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_a_dB() {
    uint16_t addr = fetchImmWord();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_a_zpdB() {
    uint16_t addr = fetchImmByte();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_a_zpxB() {
    uint16_t addr = x;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_a_zpyB() {
    uint16_t addr = y;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_a_zpzB() {
    uint16_t addr = z;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_a_izpxB() {
    uint16_t addr = x;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_a_izpyB() {
    uint16_t addr = y;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_a_izpzB() {
    uint16_t addr = z;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_a_dxB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) x;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_a_dyB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) y;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_a_dzB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) z;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_b_a() {
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(a), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_b_iB() {
    uint8_t imm = fetchImmByte();
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(imm), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_b_dB() {
    uint16_t addr = fetchImmWord();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_b_zpdB() {
    uint16_t addr = fetchImmByte();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_b_zpxB() {
    uint16_t addr = x;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_b_zpyB() {
    uint16_t addr = y;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_b_zpzB() {
    uint16_t addr = z;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_b_izpxB() {
    uint16_t addr = x;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_b_izpyB() {
    uint16_t addr = y;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_b_izpzB() {
    uint16_t addr = z;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_b_dxB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) x;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_b_dyB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) y;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void CPU::SBB_b_dzB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + (int16_t) z;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(effAddr, val);
    asm("mov             al, %[flags]                                    \n"
        "and             al, 0b00000001                                  \n"
        "add             al, 0xff                                        \n"
        "sbb             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b10001110                            \n"
        "and             ah, 0b01110001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}
