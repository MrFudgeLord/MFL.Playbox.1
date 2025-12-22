#include "c1000.hpp"
#include <iostream>
#include <thread>
#include "..\scheduler\scheduler.hpp"

C1000::C1000() {
    scheduler::registerProcessor(this);
}

bool C1000::initialize(signaledDevice *sh, B2000 *d, B2100 *a, B2310 *crw, B2310 *cnmi, B2310 *cirq, B2310 *crst) {
    signalHandler = sh;
    dataBus       = d;
    addrBus       = a;
    rw            = crw;
    nmi           = cnmi;
    irq           = cirq;
    rst           = crst;
    return true;
}

void C1000::run() {
    while(true) {
        FDE();
    }
}

void C1000::addCyclePreemptable() {
    eventClock++;
    longClock++;
    if(eventClock == scheduler::nextEventClock) {
        scheduler::mainClock = eventClock;
        scheduler::handleNextEvent();
        eventClock = scheduler::mainClock;
        // std::cin.get();
    }
    if(false && longClock == scheduler::CLOCKS_PER_FRAME * 60) {
        std::cin.get();
        exit(0);
    }
    // printState();
}

void C1000::printState() {
    printf("cy: %lli | ip: 0x%04X | sp: 0x%04x | a: 0x%02X, b: 0x%02X, x: 0x%02X, y: 0x%02X, z: 0x%02X | data bus: %02X | addr bus: %04X\n", longClock, i.p, s.p, a, b, x, y, z, dataBus->val, addrBus->val);
    printf("ec: %i | lc: %lli | mc: %i | nec: %i\n", eventClock, longClock, scheduler::mainClock, scheduler::nextEventClock);
}

void C1000::readMemoryByte(uint16_t addr, uint8_t &dest) {
    rw->val      = false;
    addrBus->val = addr;
    signalHandler->signal();
    dest = dataBus->val;
    addCyclePreemptable();
}

void C1000::readMemoryWord(uint16_t addr, uint16_t &dest) {
    rw->val      = false;
    addrBus->val = addr + 1;
    signalHandler->signal();
    dest   = dataBus->val;
    dest <<= 8;
    addCyclePreemptable();
    rw->val      = false;
    addrBus->val = addr;
    signalHandler->signal();
    dest |= dataBus->val;
}

void C1000::writeMemoryByte(uint16_t addr, uint8_t &src) {
    rw->val      = true;
    addrBus->val = addr;
    dataBus->val = src;
    signalHandler->signal();
    addCyclePreemptable();
}

void C1000::writeMemoryWord(uint16_t addr, uint16_t &src) {
    rw->val      = true;
    addrBus->val = addr;
    dataBus->val = (uint8_t) src;
    signalHandler->signal();
    addCyclePreemptable();
    rw->val      = true;
    addrBus->val = addr + 1;
    dataBus->val = src >> 8;
    signalHandler->signal();
    addCyclePreemptable();
}

uint8_t C1000::fetchImmByte() {
    uint8_t val;
    readMemoryByte(i.p, val);
    i.p += 1;
    return val;
}

uint16_t C1000::fetchImmWord() {
    uint16_t val;
    readMemoryWord(i.p, val);
    i.p += 2;
    return val;
}

void C1000::pushByte(uint8_t val) {
    writeMemoryByte(s.p, val);
    s.l -= 1;
    addCyclePreemptable();
}

void C1000::pushWord(uint16_t val) {
    writeMemoryWord(s.p, val);
    s.l -= 2;
    addCyclePreemptable();
}

uint8_t C1000::popByte() {
    s.l += 1;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(s.p, val);
    return val;
}

uint16_t C1000::popWord() {
    s.l += 2;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(s.p, val);
    return val;
}

void C1000::FDE() {
    if(!rst->val) {
        reset();
    }
    if(!nmi->val) {
        nmiInterrupt();
    }
    if(f & IF) {
        if(!irq->val) irqInterrupt();
    }
    uint8_t opcode = fetchImmByte();
    (this->*opTable[opcode])();
}

void C1000::reset() {
    readMemoryWord(0xFFFE, i.p);
    s.h = 0x01;
    addCyclePreemptable();
    s.l = 0xff;
    addCyclePreemptable();
    a = 0;
    addCyclePreemptable();
    b = 0;
    addCyclePreemptable();
    x = 0;
    addCyclePreemptable();
    y = 0;
    addCyclePreemptable();
    z = 0;
    addCyclePreemptable();
    f = 0;
    addCyclePreemptable();
    rw->val  = false;
    nmi->val = true;
    irq->val = true;
    rst->val = true;
}

void C1000::nmiInterrupt() {
    pushWord(i.p);
    pushByte(f);
    readMemoryWord(0xFFFC, i.p);
    nmi->val = false;
}

void C1000::irqInterrupt() {
    pushWord(i.p);
    pushByte(f);
    readMemoryWord(0xFFFA, i.p);
    irq->val = false;
}

void C1000::FAULT_ILLEGAL() {
    return;
}
