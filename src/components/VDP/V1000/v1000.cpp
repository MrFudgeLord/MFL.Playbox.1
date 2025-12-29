#include "v1000.hpp"
#include "../../../scheduler/scheduler.hpp"
#include <cstddef>
#include <cstdlib>

V1000::V1000() {
    deviceID = scheduler::registerDevice(this);
    scheduler::registerDisplayProcessor(this);
    memset(&real, 0, sizeof(real));
    scheduler::scheduleEvent({TICKS_PER_SCANLINE - 1, deviceID, 0, 0x0000'0000});
    scheduler::scheduleEvent({SCANLINES_PER_FRAME * TICKS_PER_SCANLINE - 1, deviceID, 1, 0x0000'0000});
    scheduler::scheduleEvent({TICKS_PER_SCANLINE_HBLANK - 1, deviceID, 2, 0x0000'0000});
};

bool V1000::initialize(signaledDevice *sh, B2000 *d, B2100 *a, B2310 *crw, B2310 *cl, B2310 *cnmi, B2310 *cirq) {
    signalHandler = sh;
    dataBus       = d;
    addrBus       = a;
    rw            = crw;
    lock          = cl;
    nmi           = cnmi;
    irq           = cirq;
    return false;
}

uint64_t V1000::signal() {
    // Control register
    // Bottom 64 bytes of internal memory, frame palette
    // Top 256 bytes of memory, sprite table
    uint16_t maskedAddr = addrBus->val & 0x01ff;
    if(rw->val) {
        if(maskedAddr > 0xff) {
            temp.mem[ST_OFFSET + (uint8_t) maskedAddr] = dataBus->val;
        } else if(maskedAddr >= 0xa0 && maskedAddr <= 0xff) {
            temp.mem[maskedAddr - 0xa0] = dataBus->val;
        } else {
            switch(maskedAddr & 0x3) {
                case 0x0:
                    temp.ctrl = dataBus->val;
                    break;
                case 0x1:
                    if(xScrollWrite) {
                        temp.pixel.x = dataBus->val & 0x7;
                        xScrollWrite = false;
                    } else {
                        temp.tile.x  = dataBus->val & 0x3f;
                        xScrollWrite = true;
                    }
                    break;
                case 0x2:
                    if(yScrollWrite) {
                        temp.pixel.y = dataBus->val & 0x7;
                        yScrollWrite = false;
                    } else {
                        temp.tile.y  = dataBus->val & 0x1f;
                        yScrollWrite = true;
                    }
                    break;
                case 0x3:
                    xScrollWrite = false;
                    yScrollWrite = false;
                    break;
            }
        }
    } else {
        if(maskedAddr < 0xa0 && (maskedAddr & 0x3) == 0) {
            dataBus->val = lock->val;
        }
    }
    return 2 * 3 * 3 * 5; // 90
}

uint64_t V1000::dispatchEvent(uint8_t index, uint8_t data[4]) {
    static uint64_t (V1000::*eventHandlers[8])(uint8_t[4]) = {
        &V1000::renderScanline,
        &V1000::vBlank,
        &V1000::hBlank,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr};
    return (this->*eventHandlers[index])(data);
}

uint64_t V1000::renderScanline(uint8_t data[4]) {
    uint8_t scanline = data[0];
    uint8_t pixelRow = real.tile.y * 8 + real.pixel.y;
    scanlineBuffer   = (frameBuffer + 3 * scanline * REAL_PIXELS_PER_SCANLINE);
    uint16_t ttBase  = (real.ctrl & flags::bF) ? TT0_BASE : TT1_BASE;
    for(int i = 0; i < 16; i++) { // in this outer loop we fetch the palette bits for each pair of tiles
        // printf("i = %i\n", i);
        uint16_t palettePairAddr = VRAM_BASE + PT_OFFSET + real.tile.y * 16 + (real.tile.x / 4 / 2);
        addrBus->val             = palettePairAddr;
        signalHandler->signal();
        uint8_t palettePairBits   = dataBus->val;
        palettePairBits         >>= (2 * (real.tile.x % 4)); // shift the palette pair bits to bottom 2 bits
        palettePairBits          &= 0b11;                    // isolate bottom 2 bits
        palettePairBits         <<= 3;                       // shift it left 3 bits so we can OR it onto individual tile palette bits
        for(int j = 0; j < 2; j++) {                         // in this inner loop we handle each tile
            // printf("j = %i\n", j);
            uint16_t tileIndexAddress = VRAM_BASE + TM_OFFSET + real.tile.y * 64 + real.tile.x;
            addrBus->val              = tileIndexAddress;
            signalHandler->signal();
            uint8_t  tileIndex  = dataBus->val;
            uint32_t tilePixels = 0;
            uint16_t tileAddr   = ttBase + tileIndex * 24 + real.pixel.y * 3;
            // first byte
            addrBus->val = tileAddr;
            signalHandler->signal();
            ((uint8_t *) &tilePixels)[0]   = dataBus->val;
            tilePixels                   <<= 8;
            // second byte
            addrBus->val = tileAddr + 1;
            signalHandler->signal();
            ((uint8_t *) &tilePixels)[0]   = dataBus->val;
            tilePixels                   <<= 8;
            // third byte
            addrBus->val = tileAddr + 2;
            signalHandler->signal();
            ((uint8_t *) &tilePixels)[0] = dataBus->val;
            for(int k = 0; k < 8; k++) { // in this inner loop we handle each pixel of the row
                // printf("k = %i\n", k);
                uint8_t pixelBits  = tilePixels >> ((7 - k) * 3);
                pixelBits         &= 0b111;
                // printf("pixelBits = %02X\n", pixelBits);
                // printf("pixelBits | palettePairBits = %02X\n", pixelBits | palettePairBits);
                uint8_t pixelPaletteIndex                = pixelBits | palettePairBits;
                pixelPaletteIndexes[(i * 2 + j) * 8 + k] = pixelPaletteIndex;
            }
            real.tile.x++;
            real.tile.x &= 0x3f;
        }
    }
    // now we do the 33rd tile
    {
        uint16_t palettePairAddr = VRAM_BASE + PT_OFFSET + real.tile.y * 16 + (real.tile.x / 4 / 2);
        addrBus->val             = palettePairAddr;
        signalHandler->signal();
        uint8_t palettePairBits     = dataBus->val;
        palettePairBits           >>= (2 * (real.tile.x % 4)); // shift the palette pair bits to bottom 2 bits
        palettePairBits            &= 0b11;                    // isolate bottom 2 bits
        palettePairBits           <<= 3;                       // shift it left 3 bits so we can OR it onto individual tile palette bits
        uint16_t tileIndexAddress   = VRAM_BASE + TM_OFFSET + real.tile.y * 64 + real.tile.x;
        addrBus->val                = tileIndexAddress;
        signalHandler->signal();
        uint8_t  tileIndex  = dataBus->val;
        uint32_t tilePixels = 0;
        uint16_t tileAddr   = ttBase + tileIndex * 24 + real.pixel.y * 3;
        // first byte
        addrBus->val = tileAddr;
        signalHandler->signal();
        ((uint8_t *) &tilePixels)[0]   = dataBus->val;
        tilePixels                   <<= 8;
        // second byte
        addrBus->val = tileAddr + 1;
        signalHandler->signal();
        ((uint8_t *) &tilePixels)[0]   = dataBus->val;
        tilePixels                   <<= 8;
        // third byte
        addrBus->val = tileAddr + 2;
        signalHandler->signal();
        ((uint8_t *) &tilePixels)[0] = dataBus->val;
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
    ttBase = (real.ctrl & flags::sF) ? TT1_BASE : TT0_BASE;
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
        addrBus->val = tileAddr;
        signalHandler->signal();
        ((uint8_t *) &tilePixels)[0]   = dataBus->val;
        tilePixels                   <<= 8;
        // second byte
        addrBus->val = tileAddr + 1;
        signalHandler->signal();
        ((uint8_t *) &tilePixels)[0]   = dataBus->val;
        tilePixels                   <<= 8;
        // third byte
        addrBus->val = tileAddr + 2;
        signalHandler->signal();
        ((uint8_t *) &tilePixels)[0] = dataBus->val;
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
        uint8_t  paletteIndex = pixelPaletteIndexes[i + real.pixel.x];
        uint16_t paletteColor = (((uint16_t) real.ctrl & (flags::RF | flags::BF | flags::GF)) << 6) | real.mem[(paletteIndex & 0x03) ? paletteIndex : 0];
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
        scanlineBuffer[bufferIndex]      = (emuPixel.g >> 1) & 0xff00'7f00;
        scanlineBuffer[bufferIndex + 1]  = (emuPixel.b >> 1) & 0xff7f'0000;
        scanlineBuffer[bufferIndex + 2]  = (emuPixel.r >> 1) & 0xff00'007f;
    }
    if(real.pixel.y == 7) [[unlikely]] {
        real.pixel.y = 0;
        real.tile.y++;
        real.tile.y &= 0x1f;
    } else [[likely]] {
        real.pixel.y++;
    }
    if(real.tile.x < 33) {
        real.tile.x += 31;
    } else {
        real.tile.x -= 33;
    }
    // memcpy(&real, &temp, 5); // Copy the tile/pixel X and Y plus ctrl byte
    if(scanline < 239) {
        scheduler::event nextScanline {scheduler::mainClock + TICKS_PER_SCANLINE - 1, deviceID, 0};
        nextScanline.data[0] = scanline + 1;
        scheduler::scheduleEvent(nextScanline);
    }
    lock->val = false;
    return 0;
}

uint64_t V1000::vBlank(uint8_t data[4]) {
    memcpy(&real, &temp, 5);                                 // copy the registers
    memcpy(real.mem, temp.mem, 64);                          // Copy the first 64 (frame palette) bytes of internal memory
    memcpy(&real.mem[ST_OFFSET], &temp.mem[ST_OFFSET], 256); // Copy the sprite table
    if(real.ctrl & flags::iF) nmi->val = true;
    scheduler::scheduleEvent({scheduler::mainClock + scheduler::TICKS_PER_FRAME - 1,
                              deviceID,
                              1});
    scheduler::scheduleEvent({scheduler::mainClock + scheduler::TICKS_PER_FRAME + TICKS_PER_SCANLINE_HBLANK - 1,
                              deviceID,
                              2,
                              0x0000'0000});
    scheduler::scheduleEvent({scheduler::mainClock + scheduler::TICKS_PER_FRAME + TICKS_PER_SCANLINE - 1,
                              deviceID,
                              0,
                              0x0000'0000});
    return 0;
}

// Because the renderScanline event is scheduled for the end of the scanline, we schedule hBlank at the end of the hBlank portion of each scanline
// to lock VRAM for the time that would, at least in the CPU's view, be used by the VDP to render the scanline

uint64_t V1000::hBlank(uint8_t data[4]) {
    uint8_t scanline = data[0];
    lock->val        = true;
    if(scanline < 239) {
        scheduler::event nextHBlank {scheduler::mainClock + TICKS_PER_SCANLINE - 1, deviceID, 2};
        nextHBlank.data[0] = scanline + 1;
        scheduler::scheduleEvent(nextHBlank);
    }
    return 0;
}

// uint64_t V1000::renderPixel(uint8_t data[4]) {
//     uint8_t scanline = data[0];
//     uint8_t dot      = data[1];
//     // every even numbered tile, fetch the palette pair bits
//     if(real.tile.x % 2 == 0) {
//         fetchPalettePairBits();
//     }
//     // every time pixel.x is 0, fetch a new tile
//     if(real.pixel.x == 0) {
//         fetchTilePixelRow();
//     }
//     uint8_t pixelBits          = tilePixels >> ((7 - real.pixel.x) * 3);
//     pixelBits                 &= 0b111;
//     uint8_t pixelPaletteIndex  = pixelBits | palettePairBits;
//     // if(real.pixel.x == 0) {
//     //     for(int k = 0; k < 8; k++) { // in this inner loop we handle each pixel of the row
//     //         // printf("k = %i\n", k);
//     //         uint8_t pixelBits  = tilePixels >> ((7 - k) * 3);
//     //         pixelBits         &= 0b111;
//     //         // printf("pixelBits = %02X\n", pixelBits);
//     //         // printf("pixelBits | palettePairBits = %02X\n", pixelBits | palettePairBits);
//     //         uint8_t pixelPaletteIndex = pixelBits | palettePairBits;
//     //         pixelPaletteIndexes[k]    = pixelPaletteIndex;
//     //     }
//     // }

//     // turn RGB value of the palette color into 3 RGB subpixels in the framebuffer
//     renderToBuffer(scanline, dot, pixelPaletteIndex);
//     if(real.pixel.x == 7) {
//         real.pixel.x = 0;
//         real.tile.x++;
//         real.tile.x &= 0b00111111;
//     } else {
//         real.pixel.x++;
//     }
//     if(real.ctrl & flags::iF) irq->val = false;
//     // memcpy(&real, &temp, 5); // Copy the tile/pixel X and Y plus ctrl byte
//     scheduler::event nextPixel {scheduler::mainClock + TICKS_PER_PIXEL - 1, deviceID, 0};
//     if(dot != 255) {
//         nextPixel.data[0] = scanline;
//         nextPixel.data[1] = dot + 1;
//         scheduler::scheduleEvent(nextPixel);
//     } else {
//         if(real.pixel.y == 7) [[unlikely]] {
//             real.pixel.y = 0;
//             real.tile.y++;
//             real.tile.y &= 0x1f;
//         } else [[likely]] {
//             real.pixel.y++;
//         }
//         if(scanline < 239) {
//             nextPixel.data[0] = scanline + 1;
//             nextPixel.data[1] = 0;
//             scheduler::scheduleEvent(nextPixel);
//         }
//     }
//     return 0;
// }

// void V1000::fetchPalettePairBits() {
//     uint16_t palettePairAddr = VRAM_BASE + PT_OFFSET + real.tile.y * 16 + (real.tile.x / 4 / 2);
//     addrBus->val             = palettePairAddr;
//     signalHandler->signal();
//     palettePairBits   = dataBus->val;
//     palettePairBits >>= (2 * (real.tile.x % 4)); // shift the palette pair bits to bottom 2 bits
//     palettePairBits  &= 0b11;                    // isolate bottom 2 bits
//     palettePairBits <<= 3;                       // shift it left 3 bits so we can OR it onto individual tile palette bits
// }

// void V1000::fetchTilePixelRow() {
//     addrBus->val = VRAM_BASE + TM_OFFSET + real.tile.y * 64 + real.tile.x;
//     signalHandler->signal();
//     uint8_t  tileIndex = dataBus->val;
//     uint16_t rowAddr   = bgTTBase + tileIndex * 24 + real.pixel.y * 3;
//     // first byte
//     addrBus->val = rowAddr;
//     signalHandler->signal();
//     ((uint8_t *) &tilePixels)[0]   = dataBus->val;
//     tilePixels                   <<= 8;
//     // second byte
//     addrBus->val = rowAddr + 1;
//     signalHandler->signal();
//     ((uint8_t *) &tilePixels)[0]   = dataBus->val;
//     tilePixels                   <<= 8;
//     // third byte
//     addrBus->val = rowAddr + 2;
//     signalHandler->signal();
//     ((uint8_t *) &tilePixels)[0] = dataBus->val;
// }

// void V1000::renderToBuffer(uint8_t scanline, uint8_t dot, uint8_t pixelPaletteIndex) {
//     // frameBuffer is an RGBA8888[240][3][256][3] array
//     // RGBA8888 is 4 bytes, and we write all 3 subpixels per loop cycle, so we write 12 bytes in each row per cycle
//     uint16_t paletteColor = (((uint16_t) real.ctrl & (flags::RF | flags::BF | flags::GF)) << 6) | real.mem[(pixelPaletteIndex & 0x03) ? pixelPaletteIndex : 0];
//     // printf("Render pixel %i, with paletteColorIndex of %i\n", i, paletteColor);
//     uint32_t bufferIndex = (uint32_t) scanline * (3 * 256 * 3) + (uint32_t) dot * (3);
//     // printf("bufferIndex = %i * 3 * 256 * 3 + %i * 3 = %i\n", scanline, dot, bufferIndex);
//     struct {
//         int32_t r = 0, g = 0, b = 0;
//     } emuPixel;
//     emuPixel.r = 0xff00'0000 | (uint32_t) displayColors[paletteColor].r;
//     emuPixel.g = 0xff00'0000 | ((uint32_t) displayColors[paletteColor].g) << 8;
//     emuPixel.b = 0xff00'0000 | ((uint32_t) displayColors[paletteColor].b) << 16;
//     // first row
//     frameBuffer[bufferIndex]     = emuPixel.r;
//     frameBuffer[bufferIndex + 1] = emuPixel.g;
//     frameBuffer[bufferIndex + 2] = emuPixel.b;
//     // second row
//     bufferIndex                  += 256 * 3;
//     frameBuffer[bufferIndex]      = (emuPixel.g >> 1) & 0xff00'7f00;
//     frameBuffer[bufferIndex + 1]  = (emuPixel.b >> 1) & 0xff7f'0000;
//     frameBuffer[bufferIndex + 2]  = (emuPixel.r >> 1) & 0xff00'007f;
// }
