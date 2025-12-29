#pragma once

#include <fstream>
#include "../MFL.B3900/b3900.hpp"

namespace cartV0 {

struct nvram {
    uint8_t *memory;
    uint32_t size;
};

extern uint8_t nvramCount;
extern nvram   nvramComponents[256];
bool           storeNVRAM(std::fstream &NVRAMFileStream);

B3900 *cartM1100(std::fstream &ROMFileStream, std::fstream &NVRAMFileStream);

} // namespace cartV0
