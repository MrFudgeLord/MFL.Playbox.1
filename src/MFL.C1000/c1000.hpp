#pragma once

#include <cstdint>

#include "..\processor.hpp"
#include "..\signaledDevice.hpp"
#include "..\MFL.B2000\b2000.hpp"
#include "..\MFL.B2100\b2100.hpp"
#include "..\MFL.B2310\b2310.hpp"
#include "..\MFL.B3000\b3000.hpp"

class alignas(64) C1000 : public B3000, public processor {
public:
    void addCyclePreemptable() override;
    void run() override;
public:
    uint8_t a, b, x, y, z, f;
    union {
        uint16_t p;
        struct {
            uint8_t l;
            uint8_t h;
        };
    } s, i;
    enum flags {
        CF = 0x01,
        IF = 0b00010000,
        OF = 0b00100000,
        ZF = 0x40,
        SF = 0b10000000
    };
    bool initialize(signaledDevice *sh, B2000 *d, B2100 *a, B2310 *crw, B2310 *cnmi, B2310 *cirq, B2310 *crst) override;
public:
    void     readMemoryByte(uint16_t addr, uint8_t &dest);
    void     readMemoryWord(uint16_t addr, uint16_t &dest);
    void     writeMemoryByte(uint16_t addr, uint8_t &src);
    void     writeMemoryWord(uint16_t addr, uint16_t &src);
    uint8_t  fetchImmByte();
    uint16_t fetchImmWord();
    void     pushByte(uint8_t val);
    void     pushWord(uint16_t val);
    uint8_t  popByte();
    uint16_t popWord();
    void     FDE();
    void     reset();
    void     nmiInterrupt();
    void     irqInterrupt();
private:
    void FAULT_ILLEGAL();
    void FAULT_BUS();
private:
    void MOV_a_b();
    void MOV_a_iB();
    void MOV_a_dB();
    void MOV_a_zpdB();
    void MOV_a_zpxB();
    void MOV_a_zpyB();
    void MOV_a_zpzB();
    void MOV_a_izpxB();
    void MOV_a_izpyB();
    void MOV_a_izpzB();
    void MOV_a_dxB();
    void MOV_a_dyB();
    void MOV_a_dzB();
    void MOV_a_x();
    void MOV_a_y();
    void MOV_a_z();
    void MOV_b_a();
    void MOV_b_iB();
    void MOV_b_dB();
    void MOV_b_zpdB();
    void MOV_b_zpxB();
    void MOV_b_zpyB();
    void MOV_b_zpzB();
    void MOV_b_izpxB();
    void MOV_b_izpyB();
    void MOV_b_izpzB();
    void MOV_b_dxB();
    void MOV_b_dyB();
    void MOV_b_dzB();
    void MOV_b_x();
    void MOV_b_y();
    void MOV_b_z();
    void PUSH_a();
    void PUSH_b();
    void POP_a();
    void POP_b();
    void PUSHF();
    void POPF();
    void SETI();
    void CLRI();
    void SETC();
    void CLRC();
    void NOT_a();
    void NOT_b();
    void SSPH_iB();
    void NOP();
    void INT();
    void IRET();
    void RET();
    void JMP_d();
    void JMP_id();
    void JZ_iB();
    void JNZ_iB();
    void JC_iB();
    void JNC_iB();
    void JO_iB();
    void JNO_iB();
    void JS_iB();
    void JNS_iB();
    void SLX();
    void XSL();
    void TEST_a_b();
    void TEST_b_a();
    void TEST_a_iB();
    void TEST_b_iB();
    void CALL_d();
    void LSL_a();
    void LSL_b();
    void ASR_a();
    void ASR_b();
    void ROL_a();
    void ROL_b();
    void ROR_a();
    void ROR_b();
    void CMP_a_b();
    void CMP_a_iB();
    void CMP_a_zpxB();
    void CMP_a_zpyB();
    void CMP_a_zpzB();
    void CMP_b_a();
    void CMP_b_iB();
    void CMP_b_dxB();
    void CMP_b_dyB();
    void CMP_b_dzB();
    void HALT();
    void AND_a_b();
    void AND_a_iB();
    void AND_a_dB();
    void AND_a_zpdB();
    void AND_a_zpxB();
    void AND_a_zpyB();
    void AND_a_zpzB();
    void AND_a_izpxB();
    void AND_a_izpyB();
    void AND_a_izpzB();
    void AND_a_dxB();
    void AND_a_dyB();
    void AND_a_dzB();
    void PUSH_x();
    void PUSH_y();
    void PUSH_z();
    void AND_b_a();
    void AND_b_iB();
    void AND_b_dB();
    void AND_b_zpdB();
    void AND_b_zpxB();
    void AND_b_zpyB();
    void AND_b_zpzB();
    void AND_b_izpxB();
    void AND_b_izpyB();
    void AND_b_izpzB();
    void AND_b_dxB();
    void AND_b_dyB();
    void AND_b_dzB();
    void POP_x();
    void POP_y();
    void POP_z();
    void OR_a_b();
    void OR_a_iB();
    void OR_a_dB();
    void OR_a_zpdB();
    void OR_a_zpxB();
    void OR_a_zpyB();
    void OR_a_zpzB();
    void OR_a_izpxB();
    void OR_a_izpyB();
    void OR_a_izpzB();
    void OR_a_dxB();
    void OR_a_dyB();
    void OR_a_dzB();
    void MOV_x_a();
    void MOV_y_a();
    void MOV_z_a();
    void OR_b_a();
    void OR_b_iB();
    void OR_b_dB();
    void OR_b_zpdB();
    void OR_b_zpxB();
    void OR_b_zpyB();
    void OR_b_zpzB();
    void OR_b_izpxB();
    void OR_b_izpyB();
    void OR_b_izpzB();
    void OR_b_dxB();
    void OR_b_dyB();
    void OR_b_dzB();
    void MOV_x_b();
    void MOV_y_b();
    void MOV_z_b();
    void XOR_a_b();
    void XOR_a_iB();
    void XOR_a_dB();
    void XOR_a_zpdB();
    void XOR_a_zpxB();
    void XOR_a_zpyB();
    void XOR_a_zpzB();
    void XOR_a_izpxB();
    void XOR_a_izpyB();
    void XOR_a_izpzB();
    void XOR_a_dxB();
    void XOR_a_dyB();
    void XOR_a_dzB();
    void INC_x();
    void INC_y();
    void INC_z();
    void XOR_b_a();
    void XOR_b_iB();
    void XOR_b_dB();
    void XOR_b_zpdB();
    void XOR_b_zpxB();
    void XOR_b_zpyB();
    void XOR_b_zpzB();
    void XOR_b_izpxB();
    void XOR_b_izpyB();
    void XOR_b_izpzB();
    void XOR_b_dxB();
    void XOR_b_dyB();
    void XOR_b_dzB();
    void DEC_x();
    void DEC_y();
    void DEC_z();
    void ADC_a_b();
    void ADC_a_iB();
    void ADC_a_dB();
    void ADC_a_zpdB();
    void ADC_a_zpxB();
    void ADC_a_zpyB();
    void ADC_a_zpzB();
    void ADC_a_izpxB();
    void ADC_a_izpyB();
    void ADC_a_izpzB();
    void ADC_a_dxB();
    void ADC_a_dyB();
    void ADC_a_dzB();
    void CMP_x_a();
    void CMP_y_a();
    void CMP_z_a();
    void ADC_b_a();
    void ADC_b_iB();
    void ADC_b_dB();
    void ADC_b_zpdB();
    void ADC_b_zpxB();
    void ADC_b_zpyB();
    void ADC_b_zpzB();
    void ADC_b_izpxB();
    void ADC_b_izpyB();
    void ADC_b_izpzB();
    void ADC_b_dxB();
    void ADC_b_dyB();
    void ADC_b_dzB();
    void CMP_x_b();
    void CMP_y_b();
    void CMP_z_b();
    void SBB_a_b();
    void SBB_a_iB();
    void SBB_a_dB();
    void SBB_a_zpdB();
    void SBB_a_zpxB();
    void SBB_a_zpyB();
    void SBB_a_zpzB();
    void SBB_a_izpxB();
    void SBB_a_izpyB();
    void SBB_a_izpzB();
    void SBB_a_dxB();
    void SBB_a_dyB();
    void SBB_a_dzB();
    void CMP_x_dB();
    void CMP_y_dB();
    void CMP_z_dB();
    void SBB_b_a();
    void SBB_b_iB();
    void SBB_b_dB();
    void SBB_b_zpdB();
    void SBB_b_zpxB();
    void SBB_b_zpyB();
    void SBB_b_zpzB();
    void SBB_b_izpxB();
    void SBB_b_izpyB();
    void SBB_b_izpzB();
    void SBB_b_dxB();
    void SBB_b_dyB();
    void SBB_b_dzB();
    void CMP_x_iB();
    void CMP_y_iB();
    void CMP_z_iB();
private:
    static inline void (C1000 ::*opTable[256])() = {
        &C1000::MOV_a_b,
        &C1000::MOV_a_iB,
        &C1000::MOV_a_dB,
        &C1000::MOV_a_zpdB,
        &C1000::MOV_a_zpxB,
        &C1000::MOV_a_zpyB,
        &C1000::MOV_a_zpzB,
        &C1000::MOV_a_izpxB,
        &C1000::MOV_a_izpyB,
        &C1000::MOV_a_izpzB,
        &C1000::MOV_a_dxB,
        &C1000::MOV_a_dyB,
        &C1000::MOV_a_dzB,
        &C1000::MOV_a_x,
        &C1000::MOV_a_y,
        &C1000::MOV_a_z,
        &C1000::MOV_b_a,
        &C1000::MOV_b_iB,
        &C1000::MOV_b_dB,
        &C1000::MOV_b_zpdB,
        &C1000::MOV_b_zpxB,
        &C1000::MOV_b_zpyB,
        &C1000::MOV_b_zpzB,
        &C1000::MOV_b_izpxB,
        &C1000::MOV_b_izpyB,
        &C1000::MOV_b_izpzB,
        &C1000::MOV_b_dxB,
        &C1000::MOV_b_dyB,
        &C1000::MOV_b_dzB,
        &C1000::MOV_b_x,
        &C1000::MOV_b_y,
        &C1000::MOV_b_z,
        &C1000::PUSH_a,
        &C1000::PUSH_b,
        &C1000::POP_a,
        &C1000::POP_b,
        &C1000::PUSHF,
        &C1000::POPF,
        &C1000::SETI,
        &C1000::CLRI,
        &C1000::SETC,
        &C1000::CLRC,
        &C1000::NOT_a,
        &C1000::NOT_b,
        &C1000::SSPH_iB,
        &C1000::NOP,
        &C1000::INT,
        &C1000::IRET,
        &C1000::RET,
        &C1000::JMP_d,
        &C1000::JMP_id,
        &C1000::JZ_iB,
        &C1000::JNZ_iB,
        &C1000::JC_iB,
        &C1000::JNC_iB,
        &C1000::JO_iB,
        &C1000::JNO_iB,
        &C1000::JS_iB,
        &C1000::JNS_iB,
        &C1000::SLX,
        &C1000::XSL,
        &C1000::TEST_a_b,
        &C1000::TEST_b_a,
        &C1000::TEST_a_iB,
        &C1000::TEST_b_iB,
        &C1000::CALL_d,
        &C1000::LSL_a,
        &C1000::LSL_b,
        &C1000::ASR_a,
        &C1000::ASR_b,
        &C1000::ROL_a,
        &C1000::ROL_b,
        &C1000::ROR_a,
        &C1000::ROR_b,
        &C1000::CMP_a_b,
        &C1000::CMP_a_iB,
        &C1000::CMP_a_zpxB,
        &C1000::CMP_a_zpyB,
        &C1000::CMP_a_zpzB,
        &C1000::CMP_b_a,
        &C1000::CMP_b_iB,
        &C1000::CMP_b_dxB,
        &C1000::CMP_b_dyB,
        &C1000::CMP_b_dzB,
        &C1000::HALT,
        &C1000::AND_a_b,
        &C1000::AND_a_iB,
        &C1000::AND_a_dB,
        &C1000::AND_a_zpdB,
        &C1000::AND_a_zpxB,
        &C1000::AND_a_zpyB,
        &C1000::AND_a_zpzB,
        &C1000::AND_a_izpxB,
        &C1000::AND_a_izpyB,
        &C1000::AND_a_izpzB,
        &C1000::AND_a_dxB,
        &C1000::AND_a_dyB,
        &C1000::AND_a_dzB,
        &C1000::PUSH_x,
        &C1000::PUSH_y,
        &C1000::PUSH_z,
        &C1000::AND_b_a,
        &C1000::AND_b_iB,
        &C1000::AND_b_dB,
        &C1000::AND_b_zpdB,
        &C1000::AND_b_zpxB,
        &C1000::AND_b_zpyB,
        &C1000::AND_b_zpzB,
        &C1000::AND_b_izpxB,
        &C1000::AND_b_izpyB,
        &C1000::AND_b_izpzB,
        &C1000::AND_b_dxB,
        &C1000::AND_b_dyB,
        &C1000::AND_b_dzB,
        &C1000::POP_x,
        &C1000::POP_y,
        &C1000::POP_z,
        &C1000::OR_a_b,
        &C1000::OR_a_iB,
        &C1000::OR_a_dB,
        &C1000::OR_a_zpdB,
        &C1000::OR_a_zpxB,
        &C1000::OR_a_zpyB,
        &C1000::OR_a_zpzB,
        &C1000::OR_a_izpxB,
        &C1000::OR_a_izpyB,
        &C1000::OR_a_izpzB,
        &C1000::OR_a_dxB,
        &C1000::OR_a_dyB,
        &C1000::OR_a_dzB,
        &C1000::MOV_x_a,
        &C1000::MOV_y_a,
        &C1000::MOV_z_a,
        &C1000::OR_b_a,
        &C1000::OR_b_iB,
        &C1000::OR_b_dB,
        &C1000::OR_b_zpdB,
        &C1000::OR_b_zpxB,
        &C1000::OR_b_zpyB,
        &C1000::OR_b_zpzB,
        &C1000::OR_b_izpxB,
        &C1000::OR_b_izpyB,
        &C1000::OR_b_izpzB,
        &C1000::OR_b_dxB,
        &C1000::OR_b_dyB,
        &C1000::OR_b_dzB,
        &C1000::MOV_x_b,
        &C1000::MOV_y_b,
        &C1000::MOV_z_b,
        &C1000::XOR_a_b,
        &C1000::XOR_a_iB,
        &C1000::XOR_a_dB,
        &C1000::XOR_a_zpdB,
        &C1000::XOR_a_zpxB,
        &C1000::XOR_a_zpyB,
        &C1000::XOR_a_zpzB,
        &C1000::XOR_a_izpxB,
        &C1000::XOR_a_izpyB,
        &C1000::XOR_a_izpzB,
        &C1000::XOR_a_dxB,
        &C1000::XOR_a_dyB,
        &C1000::XOR_a_dzB,
        &C1000::INC_x,
        &C1000::INC_y,
        &C1000::INC_z,
        &C1000::XOR_b_a,
        &C1000::XOR_b_iB,
        &C1000::XOR_b_dB,
        &C1000::XOR_b_zpdB,
        &C1000::XOR_b_zpxB,
        &C1000::XOR_b_zpyB,
        &C1000::XOR_b_zpzB,
        &C1000::XOR_b_izpxB,
        &C1000::XOR_b_izpyB,
        &C1000::XOR_b_izpzB,
        &C1000::XOR_b_dxB,
        &C1000::XOR_b_dyB,
        &C1000::XOR_b_dzB,
        &C1000::DEC_x,
        &C1000::DEC_y,
        &C1000::DEC_z,
        &C1000::ADC_a_b,
        &C1000::ADC_a_iB,
        &C1000::ADC_a_dB,
        &C1000::ADC_a_zpdB,
        &C1000::ADC_a_zpxB,
        &C1000::ADC_a_zpyB,
        &C1000::ADC_a_zpzB,
        &C1000::ADC_a_izpxB,
        &C1000::ADC_a_izpyB,
        &C1000::ADC_a_izpzB,
        &C1000::ADC_a_dxB,
        &C1000::ADC_a_dyB,
        &C1000::ADC_a_dzB,
        &C1000::CMP_x_a,
        &C1000::CMP_y_a,
        &C1000::CMP_z_a,
        &C1000::ADC_b_a,
        &C1000::ADC_b_iB,
        &C1000::ADC_b_dB,
        &C1000::ADC_b_zpdB,
        &C1000::ADC_b_zpxB,
        &C1000::ADC_b_zpyB,
        &C1000::ADC_b_zpzB,
        &C1000::ADC_b_izpxB,
        &C1000::ADC_b_izpyB,
        &C1000::ADC_b_izpzB,
        &C1000::ADC_b_dxB,
        &C1000::ADC_b_dyB,
        &C1000::ADC_b_dzB,
        &C1000::CMP_x_b,
        &C1000::CMP_y_b,
        &C1000::CMP_z_b,
        &C1000::SBB_a_b,
        &C1000::SBB_a_iB,
        &C1000::SBB_a_dB,
        &C1000::SBB_a_zpdB,
        &C1000::SBB_a_zpxB,
        &C1000::SBB_a_zpyB,
        &C1000::SBB_a_zpzB,
        &C1000::SBB_a_izpxB,
        &C1000::SBB_a_izpyB,
        &C1000::SBB_a_izpzB,
        &C1000::SBB_a_dxB,
        &C1000::SBB_a_dyB,
        &C1000::SBB_a_dzB,
        &C1000::CMP_x_dB,
        &C1000::CMP_x_dB,
        &C1000::CMP_y_dB,
        &C1000::CMP_z_dB,
        &C1000::SBB_b_a,
        &C1000::SBB_b_iB,
        &C1000::SBB_b_dB,
        &C1000::SBB_b_zpdB,
        &C1000::SBB_b_zpxB,
        &C1000::SBB_b_zpyB,
        &C1000::SBB_b_zpzB,
        &C1000::SBB_b_izpxB,
        &C1000::SBB_b_izpyB,
        &C1000::SBB_b_izpzB,
        &C1000::SBB_b_dxB,
        &C1000::SBB_b_dyB,
        &C1000::SBB_b_dzB,
        &C1000::CMP_x_iB,
        &C1000::CMP_y_iB,
        &C1000::CMP_z_iB,
    };
};
