#include "v1000.hpp"

V1000::V1000(signaledDevice &dc, B2000 &d, B2100 &a, B2310 &crw, B2310 &cnmi, B2310 &cirq, B2310 &crst)
    : decoder(dc), dataBus(d), addrBus(a), rw(crw), nmi(cnmi), irq(cirq), rst(crst) {};
