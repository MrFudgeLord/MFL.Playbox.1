
#include "scheduler.hpp"
#include "..\scheduledDevice.hpp"

class dummy : public scheduledDevice {
public:
    dummy();
    void dispatchEvent(uint8_t index, uint8_t data[4]) override;
private:
    void frameEnd(uint8_t data[4]);
    void debugger(uint8_t data[4]);
};
