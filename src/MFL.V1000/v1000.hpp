#include <cstdint>

#include "..\processor.hpp"
#include "..\scheduledDevice.hpp"
#include "..\signaledDevice.hpp"
#include "..\MFL.B2000\b2000.hpp"
#include "..\MFL.B2100\b2100.hpp"
#include "..\MFL.B2310\b2310.hpp"

class alignas(64) V1000 : public processor, public scheduledDevice, public signaledDevice {
    signaledDevice &decoder;
    B2000          &dataBus;
    B2100          &addrBus;
    B2310          &rw;
    B2310          &nmi;
    B2310          &irq;
    B2310          &rst;
private:
    // VRAM memory map
    const static uint16_t VRAM_BASE = 0x1000;
    const static uint16_t TM_OFFSET = 0x0000;
    const static uint16_t PT_OFFSET = 0x0800;
    const static uint16_t ST_OFFSET = 0x0A00;
    // Cartridge memory map
    const static uint16_t TT0_BASE = 0x4000;
    const static uint16_t TT1_BASE = 0x5000;
    // Internal memory map
    const static uint8_t BP_OFFSET = 0x00;
    const static uint8_t SP_OFFSET = 0x10;
    const static uint8_t AS_OFFSET = 0x60;
private:
    struct {
        uint8_t r, g, b;
    } displayColors[64];
    uint8_t *scanlineBuffer; // uint8_t[768][4]
public:
    uint8_t  x, y, ctrl;
    uint16_t a;
    uint8_t  mem[128];
    V1000(signaledDevice &dc, B2000 &d, B2100 &a, B2310 &crw, B2310 &cnmi, B2310 &cirq, B2310 &crst);
    bool initialize() override;
    void dispatchEvent(uint8_t index, uint8_t data[4]) override;
private:
    void renderScanline();
};
