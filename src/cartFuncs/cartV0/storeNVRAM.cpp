#include "../cartFuncs.hpp"

namespace cartV0 {

uint8_t nvramCount = 0;
nvram   nvramComponents[256];

bool storeNVRAM(std::fstream &NVRAMFileStream) {
    NVRAMFileStream.seekp(0);
    for(int i = 0; i < nvramCount; i++) {
        NVRAMFileStream.write((const char *) nvramComponents[i].memory, nvramComponents[i].size);
    }
    return true;
}

} // namespace cartV0
