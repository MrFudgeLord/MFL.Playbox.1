#include "v1000.hpp"
#include "..\scheduler\scheduler.hpp"
#include <cstddef>

V1000::V1000() {
    deviceID = scheduler::registerDevice(this);
    scheduler::registerDisplayProcessor(this);
    real.x  = 0;
    real.y  = 0;
    a       = VRAM_BASE + TM_OFFSET;
    a      |= real.tileX;
    a      |= (real.tileY << 6);
    scheduler::event firstScanline {deviceID, 0, CYCLES_PER_SCANLINE - 1};
    firstScanline.data[0] = 0;
    scheduler::scheduleEvent(firstScanline);
};

bool V1000::initialize(signaledDevice *sh, B2000 *d, B2100 *a, B2310 *crw, B2310 *cnmi, B2310 *cirq) {
    signalHandler = sh;
    dataBus       = d;
    addrBus       = a;
    rw            = crw;
    nmi           = cnmi;
    irq           = cirq;
    return false;
}

uint32_t V1000::signal() {
    uint16_t maskedAddr = addrBus->val & 0x000f;
    switch(maskedAddr) {
        case 0x0:
            break;
        case 0x1:
            break;
    }
    return 1;
}

bool V1000::dispatchEvent(uint8_t index, uint8_t data[4]) {
    static bool (V1000::*eventHandlers[8])(uint8_t[4]) = {
        &V1000::renderScanline,
        &V1000::vBlank,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL};
    return (this->*eventHandlers[index])(data);
}

bool V1000::renderScanline(uint8_t data[4]) {
    uint8_t scanline         = data[0];
    uint8_t scrolledScanline = scanline + real.y;
    scanlineBuffer           = (frameBuffer + scrolledScanline * BYTES_PER_SCANLINE);
    int8_t   lastTileIndex   = (a & 0x3f) + 32;
    uint8_t  paletteBits     = 0;
    uint16_t ttBase          = (real.ctrl & 0b00000010) ? TT0_BASE : TT1_BASE;
    if(data[0] < 240) {
        if(lastTileIndex < 64) { // No wrapping
            for(int i = 0; i < 16; i++) {
                // get palette bits for the tile pair
                rw->val      = false;
                addrBus->val = VRAM_BASE + PT_OFFSET + real.y * 8 + i;
                signalHandler->signal();
                paletteBits   = dataBus->val;
                paletteBits >>= (2 * (i % 4));
                paletteBits  &= 0x03;
                paletteBits <<= 3;
                printf("\nFetch palette bits\n");
                for(int j = 0; j < 2; j++) {
                    printf("Render tile %i, a = 0x%X\n", i * 2 + j, a);
                    uint8_t  tileIndex  = 0;
                    uint32_t tilePixels = 0;
                    // get tile index
                    // we render
                    addrBus->val = a;
                    signalHandler->signal();
                    tileIndex = dataBus->val;
                    // get pixels for tile
                    uint16_t tileAddress = ttBase + tileIndex * 24 + real.y * 3;
                    addrBus->val         = tileAddress;
                    signalHandler->signal();
                    ((uint8_t *) &tilePixels)[3] = dataBus->val;
                    addrBus->val                 = tileAddress + 1;
                    signalHandler->signal();
                    ((uint8_t *) &tilePixels)[2] = dataBus->val;
                    addrBus->val                 = tileAddress + 2;
                    signalHandler->signal();
                    ((uint8_t *) &tilePixels)[1] = dataBus->val;
                    for(int k = 0; k < 8; k++) {
                        printf("Fetch pixel %i\n", k);
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
                printf("Render 33rd tile\n");
                uint8_t  tileIndex  = 0;
                uint32_t tilePixels = 0;
                // get tile index
                addrBus->val = a;
                signalHandler->signal();
                tileIndex = dataBus->val;
                // get pixels for tile
                uint16_t tileAddress = ttBase + tileIndex * 24 + real.y * 3;
                addrBus->val         = tileAddress;
                signalHandler->signal();
                ((uint8_t *) &tilePixels)[3] = dataBus->val;
                addrBus->val                 = tileAddress + 1;
                signalHandler->signal();
                ((uint8_t *) &tilePixels)[2] = dataBus->val;
                addrBus->val                 = tileAddress + 2;
                signalHandler->signal();
                ((uint8_t *) &tilePixels)[1] = dataBus->val;
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
                addrBus->val = VRAM_BASE + PT_OFFSET + i;
                signalHandler->signal();
                paletteBits   = dataBus->val;
                paletteBits >>= (2 * (i % 4));
                paletteBits  &= 0x03;
                paletteBits <<= 3;
                for(int j = 0; j < 2; j++) {
                    uint8_t  tileIndex  = 0;
                    uint32_t tilePixels = 0;
                    // get tile index
                    addrBus->val = a;
                    signalHandler->signal();
                    tileIndex = dataBus->val;
                    // get pixels for tile
                    uint16_t tileAddress = ttBase + tileIndex * 24 + real.y * 3;
                    addrBus->val         = tileAddress;
                    signalHandler->signal();
                    ((uint8_t *) &tilePixels)[3] = dataBus->val;
                    addrBus->val                 = tileAddress + 1;
                    signalHandler->signal();
                    ((uint8_t *) &tilePixels)[2] = dataBus->val;
                    addrBus->val                 = tileAddress + 2;
                    signalHandler->signal();
                    ((uint8_t *) &tilePixels)[1] = dataBus->val;
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
                addrBus->val = a;
                signalHandler->signal();
                tileIndex = dataBus->val;
                // get pixels for tile
                uint16_t tileAddress = ttBase + tileIndex * 24 + real.y * 3;
                addrBus->val         = tileAddress;
                signalHandler->signal();
                ((uint8_t *) &tilePixels)[3] = dataBus->val;
                addrBus->val                 = tileAddress + 1;
                signalHandler->signal();
                ((uint8_t *) &tilePixels)[2] = dataBus->val;
                addrBus->val                 = tileAddress + 2;
                signalHandler->signal();
                ((uint8_t *) &tilePixels)[1] = dataBus->val;
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
        for(int i = real.x; i < (256 + real.x); i++) {
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
    }
    // irq->val = false;
    if(scanline < 239) {
        scheduler::event nextScanline {deviceID, 0, (scanline + 2) * CYCLES_PER_SCANLINE - 1};
        nextScanline.data[0] = scanline + 1;
        scheduler::scheduleEvent(nextScanline);
    }
    return false;
}

bool V1000::vBlank(uint8_t data[4]) {
    nmi->val  = false;
    a         = VRAM_BASE + TM_OFFSET;
    a        |= real.tileX;
    a        |= (real.tileY << 6);
    scheduler::scheduleEvent({deviceID,
                              1,
                              (SCANLINES_PER_FRAME * CYCLES_PER_SCANLINE) - 1});
    scheduler::scheduleEvent({deviceID,
                              0,
                              CYCLES_PER_SCANLINE - 1});
    return true;
}
