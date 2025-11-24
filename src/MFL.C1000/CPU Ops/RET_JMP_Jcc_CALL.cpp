#include "..\c1000.hpp"

void C1000::RET() {
    i.p = popWord();
}

void C1000::JMP_d() {
    i.p = fetchImmWord();
}

void C1000::JMP_id() {
    uint16_t addr = fetchImmWord();
    readMemoryWord(addr, i.p);
}

void C1000::JZ_iB() {
    uint8_t imm = fetchImmByte();
    if(addCyclePreemptable(), f & ZF) {
        i.p += (int16_t) imm;
        addCyclePreemptable();
    }
}

void C1000::JNZ_iB() {
    uint8_t imm = fetchImmByte();
    if(addCyclePreemptable(), !(f & ZF)) {
        i.p += (int16_t) imm;
        addCyclePreemptable();
    }
}

void C1000::JC_iB() {
    uint8_t imm = fetchImmByte();
    if(addCyclePreemptable(), f & CF) {
        i.p += (int16_t) imm;
        addCyclePreemptable();
    }
}

void C1000::JNC_iB() {
    uint8_t imm = fetchImmByte();
    if(addCyclePreemptable(), !(f & CF)) {
        i.p += (int16_t) imm;
        addCyclePreemptable();
    }
}

void C1000::JO_iB() {
    uint8_t imm = fetchImmByte();
    if(addCyclePreemptable(), f & OF) {
        i.p += (int16_t) imm;
        addCyclePreemptable();
    }
}

void C1000::JNO_iB() {
    uint8_t imm = fetchImmByte();
    if(addCyclePreemptable(), !(f & OF)) {
        i.p += (int16_t) imm;
        addCyclePreemptable();
    }
}

void C1000::JS_iB() {
    uint8_t imm = fetchImmByte();
    if(addCyclePreemptable(), f & SF) {
        i.p += (int16_t) imm;
        addCyclePreemptable();
    }
}

void C1000::JNS_iB() {
    uint8_t imm = fetchImmByte();
    if(addCyclePreemptable(), !(f & SF)) {
        i.p += (int16_t) imm;
        addCyclePreemptable();
    }
}

void C1000::CALL_d() {
    uint16_t addr = fetchImmWord();
    pushWord(i.p + 2);
    i.p = addr;
}
