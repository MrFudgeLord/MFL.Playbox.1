#include "..\c1000.hpp"

void C1000::CMP_a_b() {
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(b), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_a_iB() {
    uint8_t imm = fetchImmByte();
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(imm), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_a_zpxB() {
    uint16_t addr = x;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_a_zpyB() {
    uint16_t addr = y;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_a_zpzB() {
    uint16_t addr = z;
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(a), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_b_a() {
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(a), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_b_iB() {
    uint8_t imm = fetchImmByte();
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(imm), [flags] "+rm"(f)
        :
        : "ah", "al");
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
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
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
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
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
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(b), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_x_a() {
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(x), [src] "+rm"(a), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_y_a() {
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(y), [src] "+rm"(a), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_z_a() {
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(z), [src] "+rm"(a), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_x_b() {
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(x), [src] "+rm"(b), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_y_b() {
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(y), [src] "+rm"(b), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_z_b() {
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(z), [src] "+rm"(b), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_x_dB() {
    uint16_t addr = fetchImmWord();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(x), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_y_dB() {
    uint16_t addr = fetchImmWord();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(y), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_z_dB() {
    uint16_t addr = fetchImmWord();
    uint8_t  val;
    readMemoryByte(addr, val);
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(z), [src] "+rm"(val), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_x_iB() {
    uint8_t imm = fetchImmByte();
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(x), [src] "+rm"(imm), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_y_iB() {
    uint8_t imm = fetchImmByte();
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(y), [src] "+rm"(imm), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}

void C1000::CMP_z_iB() {
    uint8_t imm = fetchImmByte();
    asm("cmp             %[dest], %[src]                                 \n"
        "lahf                                                            \n"
        "and             %[flags], 0b00011110                            \n"
        "and             ah, 0b11000001                                  \n"
        "or              %[flags], ah                                    \n"
        "seto            al                                              \n"
        "shl             al, 4                                           \n"
        "or              %[flags], al                                    \n"
        : [dest] "+rm"(z), [src] "+rm"(imm), [flags] "+rm"(f)
        :
        : "ah", "al");
    addCyclePreemptable();
}
