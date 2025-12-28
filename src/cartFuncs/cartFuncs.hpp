#pragma once

#include <fstream>

#include "../MFL.B3900/b3900.hpp"

B3900 *cartM1100(std::fstream &cartFileStream);
bool   cleanupM1100(std::fstream &cartFileStream, B3900 *cartMB);
