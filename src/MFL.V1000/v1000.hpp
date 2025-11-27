#include <cstdint>

#include "..\scheduledDevice.hpp"
#include "..\signaledDevice.hpp"
#include "..\MFL.B2000\b2000.hpp"
#include "..\MFL.B2100\b2100.hpp"
#include "..\MFL.B2310\b2310.hpp"

class alignas(64) C1000 : public scheduledDevice, public signaledDevice {
    signaledDevice &decoder;
    B2000          &dataBus;
    B2100          &addrBus;
    B2310          &rw;
    B2310          &nmi;
    B2310          &irq;
    B2310          &rst;
public:
    uint8_t a, b, x, y, z, f;
    union {
        uint16_t p;
        struct {
            uint8_t h;
            uint8_t l;
        };
    } s, i;
    enum flags {
        CF = 0b00000001,
        IF = 0b00010000,
        OF = 0b00100000,
        ZF = 0b01000000,
        SF = 0b10000000
    };
    C1000(signaledDevice &dc, B2000 &d, B2100 &a, B2310 &crw, B2310 &cnmi, B2310 &cirq, B2310 &crst)
        : decoder(dc), dataBus(d), addrBus(a), rw(crw), nmi(cnmi), irq(cirq), rst(crst) {};
    uint32_t cycleCount = 0;
    uint8_t  addCyclePreemptable();
private:
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
    void     loop();
    void     FDE();
    void     reset();
    void     nmiInterrupt();
    void     irqInterrupt();
};
