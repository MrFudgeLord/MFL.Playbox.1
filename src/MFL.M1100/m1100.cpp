#include "m1100.hpp"

bool M1100::initialize(signaledDevice *sh, B2000 *d, B2100 *a, B2310 *crw, B2310 *cnmi, B2310 *cirq) {
    signalHandler = sh;
    dataBus       = d;
    addrBus       = a;
    rw            = crw;
    nmi           = cnmi;
    irq           = cirq;
    return true;
}
