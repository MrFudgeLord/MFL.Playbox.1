#include "..\cpu.hpp"

void CPU::RET() {
    i.p = popWord();
}

void CPU::JMP_d() {
    i.p = fetchImmWord();
}

void CPU::JMP_id() {
    uint16_t addr = fetchImmWord();
    readMemoryWord(addr, i.p);
}

void CPU::JZ_iB() {
    uint8_t imm = fetchImmByte();
    if(addCyclePreemptable(), f & ZF) {
        i.p += (int16_t) imm;
        addCyclePreemptable();
    }
}

void CPU::JNZ_iB() {
    uint8_t imm = fetchImmByte();
    if(addCyclePreemptable(), !(f & ZF)) {
        i.p += (int16_t) imm;
        addCyclePreemptable();
    }
}

void CPU::JC_iB() {
    uint8_t imm = fetchImmByte();
    if(addCyclePreemptable(), f & CF) {
        i.p += (int16_t) imm;
        addCyclePreemptable();
    }
}

void CPU::JNC_iB() {
    uint8_t imm = fetchImmByte();
    if(addCyclePreemptable(), !(f & CF)) {
        i.p += (int16_t) imm;
        addCyclePreemptable();
    }
}

void CPU::JO_iB() {
    uint8_t imm = fetchImmByte();
    if(addCyclePreemptable(), f & OF) {
        i.p += (int16_t) imm;
        addCyclePreemptable();
    }
}

void CPU::JNO_iB() {
    uint8_t imm = fetchImmByte();
    if(addCyclePreemptable(), !(f & OF)) {
        i.p += (int16_t) imm;
        addCyclePreemptable();
    }
}

void CPU::JS_iB() {
    uint8_t imm = fetchImmByte();
    if(addCyclePreemptable(), f & SF) {
        i.p += (int16_t) imm;
        addCyclePreemptable();
    }
}

void CPU::JNS_iB() {
    uint8_t imm = fetchImmByte();
    if(addCyclePreemptable(), !(f & SF)) {
        i.p += (int16_t) imm;
        addCyclePreemptable();
    }
}

void CPU::CALL_d() {
    uint16_t addr = fetchImmWord();
    pushWord(i.p + 2);
    i.p = addr;
}
