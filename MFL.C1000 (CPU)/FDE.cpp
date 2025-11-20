#include "cpu.hpp"

void CPU::FDE(){
    readMemoryByte(ip + insSize, instruction.opcode);
    insSize++;
    (this->*opTable[instruction.opcode])();
    insSize = 0;
}