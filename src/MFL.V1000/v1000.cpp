#include "v1000.hpp"
#include "..\scheduler\scheduler.hpp"
#include <cstddef>

V1000::V1000(signaledDevice &dc, B2000 &d, B2100 &a, B2310 &crw, B2310 &cnmi, B2310 &cirq)
    : decoder(dc), dataBus(d), addrBus(a), rw(crw), nmi(cnmi), irq(cirq) {
    deviceID = scheduler::registerDevice(this);
};

bool V1000::initialize() {
    x = 0;
    y = 0;
    a = VRAM_BASE + TM_OFFSET;
    return false;
}

void V1000::dispatchEvent(uint8_t index, uint8_t data[4]) {
    static void (V1000::*eventHandlers[8])() = {
        &V1000::renderScanline,
        &V1000::vBlank,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL};
    (this->*eventHandlers[index])();
}

void V1000::renderScanline() {
    int8_t   lastTileIndex = (a & 0x3f) + 32;
    uint8_t  paletteBits   = 0;
    uint16_t ttBase        = (ctrl & 0b00000010) ? TT0_BASE : TT1_BASE;
    if(lastTileIndex < 64) { // No wrapping
        for(int i = 0; i < 16; i++) {
            // get palette bits for the tile pair
            rw.val      = false;
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
                    pixelPaletteColors[i * 2 + j][k]   = paletteColor;
                    tilePixels                       >>= 3;
                }
                a++;
            }
        }
        // 33rd tile rendered, which is either offscreen or partially scrolled into
        {
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
                pixelPaletteColors[32][k]   = paletteColor;
                tilePixels                >>= 3;
            }
        }
    } else { // Wrapping at tile (lastTileIndex - 63)
        uint8_t wrapTileIndex = lastTileIndex - 63;
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
                    pixelPaletteColors[i * 2 + j][k]   = paletteColor;
                    tilePixels                       >>= 3;
                }
                if((a & 0x3f) == lastTileIndex) a -= 0x40;
                a++;
            }
        }
        // 33rd tile rendered, which is either offscreen or partially scrolled into
        {
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
                pixelPaletteColors[32][k]   = paletteColor;
                tilePixels                >>= 3;
            }
        }
    }
    for(int i = x; i < (256 + x); i++) {
        uint8_t  paletteColor                       = **(pixelPaletteColors + i);
        uint16_t bufferIndex                        = i * 4;
        *(uint32_t *) &scanlineBuffer[bufferIndex]  = *(uint32_t *) &displayColors[paletteColor];
        bufferIndex                                += 256;
        *(uint32_t *) &scanlineBuffer[bufferIndex]  = *(uint32_t *) &displayColors[paletteColor];
        bufferIndex                                += 256;
        scanlineBuffer[bufferIndex + 0]             = displayColors[paletteColor].r >> 2;
        scanlineBuffer[bufferIndex + 1]             = displayColors[paletteColor].g >> 2;
        scanlineBuffer[bufferIndex + 2]             = displayColors[paletteColor].b >> 2;
        scanlineBuffer[bufferIndex + 3]             = 0xff;
    }
    scheduler::scheduleEvent({deviceID, 0, scheduler::mainClock + 108});
}
