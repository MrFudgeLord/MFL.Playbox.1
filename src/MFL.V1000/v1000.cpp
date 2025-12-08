#include "v1000.hpp"
#include "..\scheduler\scheduler.hpp"

V1000::V1000(signaledDevice &dc, B2000 &d, B2100 &a, B2310 &crw, B2310 &cnmi, B2310 &cirq, B2310 &crst)
    : decoder(dc), dataBus(d), addrBus(a), rw(crw), nmi(cnmi), irq(cirq), rst(crst) {
    scheduler::registerDevice(this);
};

bool V1000::initialize() {
    x = 0;
    y = 0;
    a = VRAM_BASE + TM_OFFSET;
    return false;
}

void V1000::dispatchEvent(uint8_t index, uint8_t data[4]) {
    renderScanline();
}

void V1000::renderScanline() {
    int8_t   indexDiff   = 32 - ((a & 0x3f) *);
    uint8_t  paletteBits = 0;
    uint16_t ttBase      = (ctrl & 0b00000010) ? TT0_BASE : TT1_BASE;
    if(indexDiff > 0) { // No wrapping
        for(int i = 0; i < 16; i++) {
            // get palette bits for the tile pair
            addrBus.val = VRAM_BASE + PT_OFFSET + i;
            decoder.signal();
            paletteBits   = dataBus.val;
            paletteBits >>= (2 * (i % 4));
            paletteBits  &= 0x03;
            paletteBits <<= 3;
            for(int j = 0; j < 2; j++) {
                uint8_t  tileIndex  = 0;
                uint32_t tilePixels = 0;
                // get tile index
                // we render
                addrBus.val = a;
                decoder.signal();
                tileIndex = dataBus.val;
                // get pixels for tile
                uint16_t tileAddress = ttBase + tileIndex * 24 + y * 3;
                addrBus.val          = tileAddress;
                decoder.signal();
                ((uint8_t *) &tilePixels)[3] = dataBus.val;
                addrBus.val                  = tileAddress + 1;
                decoder.signal();
                ((uint8_t *) &tilePixels)[2] = dataBus.val;
                addrBus.val                  = tileAddress + 2;
                decoder.signal();
                ((uint8_t *) &tilePixels)[1] = dataBus.val;
                for(int k = 0; k < 8; k++) {
                    uint8_t paletteColor = mem[BP_OFFSET];
                    uint8_t pixels       = tilePixels & 0x03;
                    if(pixels != 0) {
                        pixels       |= paletteBits;
                        paletteColor  = mem[BP_OFFSET + pixels];
                    }
                    // scanlineBuffer is treated as uint8_t[3][256][4] (3 lines of 256 pixels with 4 color values per pixel)
                    // Our index is scanlineBuffer[active line][active pixel][r/g/b/a]
                    //                                         [(i + j) * 8 + k] * 4
                    uint16_t bufferIndex              = ((i + j) * 8 + k) * 4;
                    scanlineBuffer[bufferIndex + 0]   = displayColors[paletteColor].r;
                    scanlineBuffer[bufferIndex + 1]   = displayColors[paletteColor].g;
                    scanlineBuffer[bufferIndex + 2]   = displayColors[paletteColor].b;
                    scanlineBuffer[bufferIndex + 3]   = 0xff;
                    bufferIndex                      += 256;
                    scanlineBuffer[bufferIndex + 0]   = displayColors[paletteColor].r;
                    scanlineBuffer[bufferIndex + 1]   = displayColors[paletteColor].g;
                    scanlineBuffer[bufferIndex + 2]   = displayColors[paletteColor].b;
                    scanlineBuffer[bufferIndex + 3]   = 0xff;
                    bufferIndex                      += 256;
                    scanlineBuffer[bufferIndex + 0]   = displayColors[paletteColor].r >> 2;
                    scanlineBuffer[bufferIndex + 1]   = displayColors[paletteColor].g >> 2;
                    scanlineBuffer[bufferIndex + 2]   = displayColors[paletteColor].b >> 2;
                    scanlineBuffer[bufferIndex + 3]   = 0xff;
                    tilePixels                      >>= 3;
                }
            }
        }
    } else { // Wrapping at tile (32 - indexDiff)
    }
}
