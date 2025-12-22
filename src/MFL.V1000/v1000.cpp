#include "v1000.hpp"
#include "..\scheduler\scheduler.hpp"
#include <cstddef>
#include <cstdlib>

V1000::V1000() {
    deviceID = scheduler::registerDevice(this);
    scheduler::registerDisplayProcessor(this);
    scheduler::event firstScanline {deviceID, 0, CYCLES_PER_SCANLINE - 1};
    firstScanline.data[0] = 0;
    memset(&real, 0, sizeof(real));
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
    uint16_t maskedAddr = addrBus->val & 0x00ff;
    if(maskedAddr < 0x60) {
        if(!rw->val) {
            temp.mem[maskedAddr] = dataBus->val;
        }
    }
    switch(maskedAddr) {
        case 0x0:
            break;
        case 0x1:
            break;
    }
    return 1;
}

uint32_t V1000::dispatchEvent(uint8_t index, uint8_t data[4]) {
    static uint32_t (V1000::*eventHandlers[8])(uint8_t[4]) = {
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

// uint32_t V1000::renderScanline(uint8_t data[4]) {
//     uint32_t eventTime        = 0;
//     uint8_t  scanline         = data[0];
//     uint8_t  scrolledScanline = scanline + real.tile.y * 8 + real.pixel.y;
//     real.tile.y               = 0;
//     scanlineBuffer            = (frameBuffer + 3 * scrolledScanline * REAL_PIXELS_PER_SCANLINE);
//     uint8_t  lastTileIndex    = 0 * (real.tile.x) + 32;
//     uint8_t  paletteBits      = 0;
//     uint16_t ttBase           = (real.ctrl & 0b00000010) ? TT0_BASE : TT1_BASE;
//     if(lastTileIndex < 64) { // No wrapping
//         for(int i = 0; i < 16; i++) {
//             // get palette bits for the tile pair
//             rw->val        = false;
//             addrBus->val   = VRAM_BASE + PT_OFFSET + (real.tile.y * 16) + (real.tile.x / 4 / 2);
//             eventTime     += signalHandler->signal();
//             paletteBits    = dataBus->val;
//             paletteBits  >>= (2 * (i % 4));
//             paletteBits   &= 0x03;
//             paletteBits  <<= 3;
//             for(int j = 0; j < 2; j++) {
//                 uint8_t  tileIndex  = 0;
//                 uint32_t tilePixels = 0;
//                 // get tile index
//                 addrBus->val  = VRAM_BASE + TM_OFFSET + (real.tile.y * 64) + real.tile.x;
//                 eventTime    += signalHandler->signal();
//                 tileIndex     = dataBus->val;
//                 // get pixels for tile
//                 uint16_t tileAddress   = ttBase + (tileIndex * 24) + (real.pixel.y * 3);
//                 rw->val                = false;
//                 addrBus->val           = tileAddress;
//                 eventTime             += signalHandler->signal();
//                 tilePixels             = dataBus->val;
//                 tilePixels           <<= 8;
//                 rw->val                = false;
//                 addrBus->val           = tileAddress + 1;
//                 eventTime             += signalHandler->signal();
//                 tilePixels             = dataBus->val;
//                 tilePixels           <<= 8;
//                 rw->val                = false;
//                 addrBus->val           = tileAddress + 2;
//                 eventTime             += signalHandler->signal();
//                 tilePixels             = dataBus->val;
//                 tilePixels           <<= 8;
//                 for(int k = 0; k < 8; k++) {
//                     // uint8_t paletteColor = real.mem[BP_OFFSET]; // we set it to the transparent color
//                     // uint8_t pixels       = tilePixels & 0x07;
//                     // if(pixels != 0) { // if not transparent, we set it to the full palette color; if it is, we leave it that way
//                     //     pixels       |= paletteBits;
//                     //     paletteColor  = real.mem[BP_OFFSET + pixels];
//                     // }
//                     // pixelPaletteColors[(i * 2 + j) * 8 + k]   = paletteColor;
//                     // tilePixels                              >>= 3;
//                     // pixelPaletteColors[(i * 2 + j) * 8 + k]   = rand() % 64;

//                     uint8_t pixelBits                        = tilePixels >> ((7 - k) * 3);
//                     pixelBits                               &= 0b111;
//                     uint8_t pixelPaletteIndex                = real.mem[BP_OFFSET + (pixelBits ? (tilePixels | paletteBits) : 0)];
//                     pixelPaletteColors[(i * 2 + j) * 8 + k]  = pixelPaletteIndex;
//                 }
//                 real.tile.x++;
//             }
//         }
//         // 33rd tile rendered, which is either offscreen or partially scrolled into
//         {
//             // get palette group bits
//             rw->val        = false;
//             addrBus->val   = VRAM_BASE + PT_OFFSET + (real.tile.y * 16) + (real.tile.x / 4 / 2);
//             eventTime     += signalHandler->signal();
//             paletteBits    = dataBus->val;
//             paletteBits  >>= (2 * (3 % 4)); // REPLACE THE 3 WITH ACTUAL LOGIC
//             paletteBits   &= 0x03;
//             paletteBits  <<= 3;
//             // get tile index
//             uint8_t  tileIndex   = 0;
//             uint32_t tilePixels  = 0;
//             addrBus->val         = VRAM_BASE + TM_OFFSET + (real.tile.y * 64) + real.tile.x;
//             eventTime           += signalHandler->signal();
//             tileIndex            = dataBus->val;
//             // get pixels for tile
//             uint16_t tileAddress           = ttBase + (tileIndex * 24) + (real.pixel.y * 3);
//             rw->val                        = false;
//             addrBus->val                   = tileAddress;
//             eventTime                     += signalHandler->signal();
//             ((uint8_t *) &tilePixels)[0]   = dataBus->val;
//             tilePixels                   <<= 8;
//             rw->val                        = false;
//             addrBus->val                   = tileAddress + 1;
//             eventTime                     += signalHandler->signal();
//             ((uint8_t *) &tilePixels)[0]   = dataBus->val;
//             tilePixels                   <<= 8;
//             rw->val                        = false;
//             addrBus->val                   = tileAddress + 2;
//             eventTime                     += signalHandler->signal();
//             ((uint8_t *) &tilePixels)[0]   = dataBus->val;
//             tilePixels                   <<= 8;
//             for(int k = 0; k < 8; k++) {
//                 // uint8_t paletteColor = real.mem[BP_OFFSET]; // we set it to the transparent color
//                 // uint8_t pixels       = tilePixels & 0x07;
//                 // if(pixels != 0) { // if not transparent, we set it to the full palette color; if it is, we leave it that way
//                 //     pixels       |= paletteBits;
//                 //     paletteColor  = real.mem[BP_OFFSET + pixels];
//                 // }
//                 // pixelPaletteColors[32 * 8 + k]   = paletteColor;
//                 // tilePixels                     >>= 3;

//                 uint8_t pixelBits               = tilePixels >> ((7 - k) * 3);
//                 pixelBits                      &= 0b111;
//                 uint8_t pixelPaletteIndex       = real.mem[BP_OFFSET + (pixelBits ? (tilePixels | paletteBits) : 0)];
//                 pixelPaletteColors[32 * 8 + k]  = pixelPaletteIndex;
//             }
//         }
//         real.tile.x -= 33;
//     } else { // Wrapping at tile (lastTileIndex - 63)
//         // uint8_t wrapTileIndex = lastTileIndex - 63;
//         // for(int i = 0; i < 16; i++) {
//         //     // get palette bits for the tile pair
//         //     addrBus->val   = VRAM_BASE + PT_OFFSET + i;
//         //     eventTime     += signalHandler->signal();
//         //     paletteBits    = dataBus->val;
//         //     paletteBits  >>= (2 * (i % 4));
//         //     paletteBits   &= 0x03;
//         //     paletteBits  <<= 3;
//         //     for(int j = 0; j < 2; j++) {
//         //         uint8_t  tileIndex  = 0;
//         //         uint32_t tilePixels = 0;
//         //         // get tile index
//         //         addrBus->val  = a;
//         //         eventTime    += signalHandler->signal();
//         //         tileIndex     = dataBus->val;
//         //         // get pixels for tile
//         //         uint16_t tileAddress          = ttBase + tileIndex * 24 + real.y * 3;
//         //         addrBus->val                  = tileAddress;
//         //         eventTime                    += signalHandler->signal();
//         //         ((uint8_t *) &tilePixels)[3]  = dataBus->val;
//         //         addrBus->val                  = tileAddress + 1;
//         //         eventTime                    += signalHandler->signal();
//         //         ((uint8_t *) &tilePixels)[2]  = dataBus->val;
//         //         addrBus->val                  = tileAddress + 2;
//         //         eventTime                    += signalHandler->signal();
//         //         ((uint8_t *) &tilePixels)[1]  = dataBus->val;
//         //         for(int k = 0; k < 8; k++) {
//         //             uint8_t paletteColor = mem[BP_OFFSET];
//         //             uint8_t pixels       = tilePixels & 0x03;
//         //             if(pixels != 0) {
//         //                 pixels       |= paletteBits;
//         //                 paletteColor  = mem[BP_OFFSET + pixels];
//         //             }
//         //             pixelPaletteColors[i * 2 + j][k]   = paletteColor;
//         //             tilePixels                       >>= 3;
//         //         }
//         //         if((a & 0x3f) == lastTileIndex) a -= 0x40;
//         //         a++;
//         //     }
//         // }
//         // // 33rd tile rendered, which is either offscreen or partially scrolled into
//         // {
//         //     uint8_t  tileIndex  = 0;
//         //     uint32_t tilePixels = 0;
//         //     // get tile index
//         //     addrBus->val  = a;
//         //     eventTime    += signalHandler->signal();
//         //     tileIndex     = dataBus->val;
//         //     // get pixels for tile
//         //     uint16_t tileAddress          = ttBase + tileIndex * 24 + real.y * 3;
//         //     addrBus->val                  = tileAddress;
//         //     eventTime                    += signalHandler->signal();
//         //     ((uint8_t *) &tilePixels)[3]  = dataBus->val;
//         //     addrBus->val                  = tileAddress + 1;
//         //     eventTime                    += signalHandler->signal();
//         //     ((uint8_t *) &tilePixels)[2]  = dataBus->val;
//         //     addrBus->val                  = tileAddress + 2;
//         //     eventTime                    += signalHandler->signal();
//         //     ((uint8_t *) &tilePixels)[1]  = dataBus->val;
//         //     for(int k = 0; k < 8; k++) {
//         //         uint8_t paletteColor = mem[BP_OFFSET];
//         //         uint8_t pixels       = tilePixels & 0x03;
//         //         if(pixels != 0) {
//         //             pixels       |= paletteBits;
//         //             paletteColor  = mem[BP_OFFSET + pixels];
//         //         }
//         //         pixelPaletteColors[32][k]   = paletteColor;
//         //         tilePixels                >>= 3;
//         //     }
//         // }
//     }
//     printf("frameBuffer is %p, scanlineBuffer is %p\n", frameBuffer, scanlineBuffer);
//     for(int i = 0; i < 256; i++) {
//         // scanlineBuffer is treated as an array of RGBA8888[3][256][3]; it represents 3 rows of 256 emuPixels, each of which has 3 subPixels, each of which is an RGBA8888
//         // i represents the current pixel of the scanline we are rendering, which may not start at pixel 0 of tile 0
//         // RGBA8888 is 4 bytes, and we write all 3 subpixels per loop cycle, so we write 12 bytes in each row per cycle
//         uint8_t paletteColor = pixelPaletteColors[i + real.pixel.x];
//         printf("Fetched paletteColor\n");
//         uint16_t bufferIndex = i * 3;
//         struct {
//             uint32_t r = 0, g = 0, b = 0;
//         } emuPixel;
//         emuPixel.r = 0xff00'0000 | (uint32_t) displayColors[paletteColor].r;
//         emuPixel.g = 0xff00'0000 | ((uint32_t) displayColors[paletteColor].g << 8);
//         emuPixel.b = 0xff00'0000 | ((uint32_t) displayColors[paletteColor].b << 16);
//         printf("Pixel %d: paletteColor %i\n", i, paletteColor);
//         printf("Pixel %d: Color %02x %02x %02x\n", i, displayColors[paletteColor].r, displayColors[paletteColor].g, displayColors[paletteColor].b);
//         // first row
//         scanlineBuffer[bufferIndex]     = 0xff00'0000 | emuPixel.r;
//         scanlineBuffer[bufferIndex + 1] = 0xff00'0000 | emuPixel.g;
//         scanlineBuffer[bufferIndex + 2] = 0xff00'0000 | emuPixel.b;
//         // second row
//         bufferIndex                     += 256 * 3;
//         scanlineBuffer[bufferIndex]      = 0xff00'0000 | emuPixel.r;
//         scanlineBuffer[bufferIndex + 1]  = 0xff00'0000 | emuPixel.g;
//         scanlineBuffer[bufferIndex + 2]  = 0xff00'0000 | emuPixel.b;
//         // dimmed third row
//         bufferIndex                     += 256 * 3;
//         scanlineBuffer[bufferIndex]      = 0xff00'0000 | (emuPixel.r >> 2);
//         scanlineBuffer[bufferIndex + 1]  = 0xff00'0000 | ((emuPixel.g >> 2) & 0x0000'ff00);
//         scanlineBuffer[bufferIndex + 2]  = 0xff00'0000 | ((emuPixel.b >> 2) & 0x00ff'0000);
//     }
//     // irq->val = false;
//     if(scanline < 239) {
//         scheduler::event nextScanline {deviceID, 0, (scanline + 2) * CYCLES_PER_SCANLINE - 1};
//         nextScanline.data[0] = scanline + 1;
//         scheduler::scheduleEvent(nextScanline);
//     }
//     return eventTime;
// }

uint32_t V1000::renderScanline(uint8_t data[4]) {
    uint32_t eventTime = 0;
    uint8_t  scanline  = data[0];
    uint8_t  pixelRow  = real.tile.y * 8 + real.pixel.y;
    scanlineBuffer     = (frameBuffer + 3 * pixelRow * REAL_PIXELS_PER_SCANLINE);
    uint16_t ttBase    = (real.ctrl & 0b00000010) ? TT0_BASE : TT1_BASE;
    for(int i = 0; i < 16; i++) { // in this outer loop we fetch the palette bits for each pair of tiles
        // printf("i = %i\n", i);
        uint16_t palettePairAddr   = VRAM_BASE + PT_OFFSET + real.tile.y * 16 + (real.tile.x / 4 / 2);
        addrBus->val               = palettePairAddr;
        eventTime                 += signalHandler->signal();
        uint8_t palettePairBits    = dataBus->val;
        palettePairBits          >>= (2 * (real.tile.x % 4)); // shift the palette pair bits to bottom 2 bits
        palettePairBits           &= 0b11;                    // isolate bottom 2 bits
        palettePairBits          <<= 3;                       // shift it left 3 bits so we can OR it onto individual tile palette bits
        for(int j = 0; j < 2; j++) {                          // in this inner loop we handle each tile
            // printf("j = %i\n", j);
            uint16_t tileIndexAddress  = VRAM_BASE + TM_OFFSET + real.tile.y * 64 + real.tile.x;
            addrBus->val               = tileIndexAddress;
            eventTime                 += signalHandler->signal();
            uint8_t  tileIndex         = dataBus->val;
            uint32_t tilePixels        = 0;
            uint16_t tileAddr          = ttBase + tileIndex * 24 + real.pixel.y * 3;
            // first byte
            addrBus->val                   = tileAddr;
            eventTime                     += signalHandler->signal();
            ((uint8_t *) &tilePixels)[0]   = dataBus->val;
            tilePixels                   <<= 8;
            // second byte
            addrBus->val                   = tileAddr + 1;
            eventTime                     += signalHandler->signal();
            ((uint8_t *) &tilePixels)[0]   = dataBus->val;
            tilePixels                   <<= 8;
            // third byte
            addrBus->val                  = tileAddr + 2;
            eventTime                    += signalHandler->signal();
            ((uint8_t *) &tilePixels)[0]  = dataBus->val;
            for(int k = 0; k < 8; k++) { // in this inner loop we handle each pixel of the row
                // printf("k = %i\n", k);
                uint8_t pixelBits  = tilePixels >> ((7 - k) * 3);
                pixelBits         &= 0b111;
                // printf("pixelBits = %02X\n", pixelBits);
                // printf("pixelBits | palettePairBits = %02X\n", pixelBits | palettePairBits);
                uint8_t pixelPaletteIndex                = pixelBits | palettePairBits;
                pixelPaletteIndexes[(i * 2 + j) * 8 + k] = pixelPaletteIndex;
            }
            if(real.tile.x == 63) {
                real.tile.x = 0;
            } else {
                real.tile.x++;
            }
        }
    }
    // now we do the 33rd tile
    {
        uint16_t palettePairAddr    = VRAM_BASE + PT_OFFSET + real.tile.y * 16 + (real.tile.x / 4 / 2);
        addrBus->val                = palettePairAddr;
        eventTime                  += signalHandler->signal();
        uint8_t palettePairBits     = dataBus->val;
        palettePairBits           >>= (2 * (real.tile.x % 4)); // shift the palette pair bits to bottom 2 bits
        palettePairBits            &= 0b11;                    // isolate bottom 2 bits
        palettePairBits           <<= 3;                       // shift it left 3 bits so we can OR it onto individual tile palette bits
        uint16_t tileIndexAddress   = VRAM_BASE + TM_OFFSET + real.tile.y * 64 + real.tile.x;
        addrBus->val                = tileIndexAddress;
        eventTime                  += signalHandler->signal();
        uint8_t  tileIndex          = dataBus->val;
        uint32_t tilePixels         = 0;
        uint16_t tileAddr           = ttBase + tileIndex * 24 + real.pixel.y * 3;
        // first byte
        addrBus->val                   = tileAddr;
        eventTime                     += signalHandler->signal();
        ((uint8_t *) &tilePixels)[0]   = dataBus->val;
        tilePixels                   <<= 8;
        // second byte
        addrBus->val                   = tileAddr + 1;
        eventTime                     += signalHandler->signal();
        ((uint8_t *) &tilePixels)[0]   = dataBus->val;
        tilePixels                   <<= 8;
        // third byte
        addrBus->val                  = tileAddr + 2;
        eventTime                    += signalHandler->signal();
        ((uint8_t *) &tilePixels)[0]  = dataBus->val;
        for(int k = 0; k < 8; k++) { // in this inner loop we handle each pixel of the row
            uint8_t pixelBits  = tilePixels >> ((7 - k) * 3);
            pixelBits         &= 0b111;
            // printf("pixelBits = %02X\n", pixelBits);
            // printf("pixelBits | palettePairBits = %02X\n", pixelBits | palettePairBits);
            uint8_t pixelPaletteIndex       = pixelBits | palettePairBits;
            pixelPaletteIndexes[32 * 8 + k] = pixelPaletteIndex;
        }
    }
    // find our active sprites
    uint8_t activeSpriteCount = 0;
    for(int i = 0; i < 64; i++) {
        uint8_t spriteY = real.mem[ST_OFFSET + i * 4];
        if(pixelRow >= spriteY && pixelRow < spriteY + 7) {
            real.mem[AS_OFFSET + activeSpriteCount * 4]     = real.mem[ST_OFFSET + i * 4];
            real.mem[AS_OFFSET + activeSpriteCount * 4 + 1] = real.mem[ST_OFFSET + i * 4 + 1];
            real.mem[AS_OFFSET + activeSpriteCount * 4 + 2] = real.mem[ST_OFFSET + i * 4 + 2];
            real.mem[AS_OFFSET + activeSpriteCount * 4 + 3] = real.mem[ST_OFFSET + i * 4 + 3];
            activeSpriteCount++;
        }
        if(activeSpriteCount == 8) break;
    }
    for(int i = 0; i < activeSpriteCount; i++) {
        uint8_t spriteY     = real.mem[AS_OFFSET + i * 4];
        uint8_t spriteX     = real.mem[AS_OFFSET + i * 4 + 1];
        uint8_t spriteTile  = real.mem[AS_OFFSET + i * 4 + 2];
        uint8_t spriteAttr  = real.mem[AS_OFFSET + i * 4 + 3];
        uint8_t paletteBits = (spriteAttr & 0b000011) << 3;
        bool    bgPriority  = spriteAttr & 0b00100000;
        bool    flipH       = spriteAttr & 0b10000000;
        bool    flipV       = spriteAttr & 0b01000000;
        uint8_t yInSprite   = pixelRow - spriteY;
        if(flipV) {
            yInSprite = 7 - yInSprite;
        }
        uint16_t tileAddr   = ttBase + spriteTile * 24 + yInSprite * 3;
        uint32_t tilePixels = 0;
        // first byte
        addrBus->val                   = tileAddr;
        eventTime                     += signalHandler->signal();
        ((uint8_t *) &tilePixels)[0]   = dataBus->val;
        tilePixels                   <<= 8;
        // second byte
        addrBus->val                   = tileAddr + 1;
        eventTime                     += signalHandler->signal();
        ((uint8_t *) &tilePixels)[0]   = dataBus->val;
        tilePixels                   <<= 8;
        // third byte
        addrBus->val                  = tileAddr + 2;
        eventTime                    += signalHandler->signal();
        ((uint8_t *) &tilePixels)[0]  = dataBus->val;
        if(bgPriority) {
            if(flipH) {
                for(int k = 0; k < 8; k++) {
                    uint8_t pixelBits  = tilePixels >> (k * 3);
                    pixelBits         &= 0b111;
                    if(pixelBits != 0) {
                        uint8_t pixelPaletteIndex          = SP_OFFSET + (pixelBits | paletteBits);
                        pixelPaletteIndexes[(spriteX + k)] = pixelPaletteIndex;
                    }
                }
            } else {
                for(int k = 0; k < 8; k++) {
                    uint8_t pixelBits  = tilePixels >> ((7 - k) * 3);
                    pixelBits         &= 0b111;
                    if(pixelBits != 0) {
                        uint8_t pixelPaletteIndex          = SP_OFFSET + (pixelBits | paletteBits);
                        pixelPaletteIndexes[(spriteX + k)] = pixelPaletteIndex;
                    }
                }
            }
        } else {
            if(flipH) {
                for(int k = 0; k < 8; k++) {
                    if((pixelPaletteIndexes[(spriteX + k)] & 0b111) != 0) continue;
                    uint8_t pixelBits  = tilePixels >> (k * 3);
                    pixelBits         &= 0b111;
                    if(pixelBits != 0) {
                        uint8_t pixelPaletteIndex          = SP_OFFSET + (pixelBits | paletteBits);
                        pixelPaletteIndexes[(spriteX + k)] = pixelPaletteIndex;
                    }
                }
            } else {
                for(int k = 0; k < 8; k++) {
                    if((pixelPaletteIndexes[(spriteX + k)] & 0b111) != 0) continue;
                    uint8_t pixelBits  = tilePixels >> ((7 - k) * 3);
                    pixelBits         &= 0b111;
                    if(pixelBits != 0) {
                        uint8_t pixelPaletteIndex          = SP_OFFSET + (pixelBits | paletteBits);
                        pixelPaletteIndexes[(spriteX + k)] = pixelPaletteIndex;
                    }
                }
            }
        }
    }
    for(int i = 0; i < 256; i++) {
        // scanlineBuffer is treated as an array of RGBA8888[3][256][3]; it represents 3 rows of 256 emuPixels, each of which has 3 subPixels, each of which is an RGBA8888
        // i represents the current pixel of the scanline we are rendering, which may not start at pixel 0 of tile 0
        // RGBA8888 is 4 bytes, and we write all 3 subpixels per loop cycle, so we write 12 bytes in each row per cycle
        uint8_t paletteIndex = pixelPaletteIndexes[i + real.pixel.x];
        uint8_t paletteColor = real.mem[(paletteIndex & 0x03) ? paletteIndex : 0];
        // printf("Render pixel %i, with paletteColorIndex of %i\n", i, paletteColor);
        uint16_t bufferIndex = i * 3;
        struct {
            int32_t r = 0, g = 0, b = 0;
        } emuPixel;
        emuPixel.r = 0xff00'0000 | (uint32_t) displayColors[paletteColor].r;
        emuPixel.g = 0xff00'0000 | ((uint32_t) displayColors[paletteColor].g) << 8;
        emuPixel.b = 0xff00'0000 | ((uint32_t) displayColors[paletteColor].b) << 16;
        // first row
        scanlineBuffer[bufferIndex]     = emuPixel.r;
        scanlineBuffer[bufferIndex + 1] = emuPixel.g;
        scanlineBuffer[bufferIndex + 2] = emuPixel.b;
        // second row
        bufferIndex                     += 256 * 3;
        scanlineBuffer[bufferIndex]      = emuPixel.b;
        scanlineBuffer[bufferIndex + 1]  = emuPixel.r;
        scanlineBuffer[bufferIndex + 2]  = emuPixel.g;
        // third row
        // bufferIndex += 256 * 3;
        // scanlineBuffer[bufferIndex]     = (emuPixel.g >> 1) & 0xff00'7f00;
        // scanlineBuffer[bufferIndex + 1] = (emuPixel.b >> 1) & 0xff7f'0000;
        // scanlineBuffer[bufferIndex + 2] = (emuPixel.r >> 1) & 0xff00'007f;
    }
    if(real.pixel.y == 7) [[unlikely]] {
        real.pixel.y = 0;
        if(real.tile.y == 31) [[unlikely]] {
            real.tile.y = 0;
        } else [[likely]] {
            real.tile.y++;
        }
    } else [[likely]] {
        real.pixel.y++;
    }
    if(real.tile.x < 33) {
        real.tile.x += 31;
    } else {
        real.tile.x -= 33;
    }
    irq->val = false;
    if(scanline < 239) {
        scheduler::event nextScanline {deviceID, 0, (scanline + 2) * CYCLES_PER_SCANLINE - 1};
        nextScanline.data[0] = scanline + 1;
        scheduler::scheduleEvent(nextScanline);
    }
    return 0;
}

uint32_t V1000::vBlank(uint8_t data[4]) {
    nmi->val = false;
    memcpy(&real, &temp, sizeof(real));
    scheduler::scheduleEvent({deviceID,
                              1,
                              (SCANLINES_PER_FRAME * CYCLES_PER_SCANLINE) - 1});
    scheduler::scheduleEvent({deviceID,
                              0,
                              CYCLES_PER_SCANLINE - 1});
    return 0;
}
