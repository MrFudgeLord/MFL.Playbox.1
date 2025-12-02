#include <cstdio>
#include <cstdint>

uint8_t lookupTable[256][3];

int main() {
    for(int i = 0; i < 256; i++) {
        uint8_t packed    = i;
        lookupTable[i][0] = packed;
    }
    for(int i = 0; i < 256; i++) {
        printf("{0x%02x, 0x%02x, 0x%02x}", lookupTable[i][0], lookupTable[i][1], lookupTable[i][2]);
        if(i < 255) printf(",");
        if((i + 1) % 8 == 0)
            printf("\n");
        else
            printf(" ");
    }
    return 0;
}
