#pragma once

#include <cstdint>
#include <string>
#include <fstream>
#include <cstdio>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_video.h"

#include "scheduler/scheduler.hpp"
#include "scheduler/dummy.hpp"

#include "cartFuncs/cartFuncs.hpp"

#include "MFL.C1000/c1000.hpp"
#include "MFL.M1000/m1000.hpp"
#include "MFL.M1100/m1100.hpp"
#include "MFL.P1000/p1000.hpp"
#include "MFL.S1002/s1002.hpp"
#include "MFL.S1003/s1003.hpp"
#include "MFL.S1102/s1102.hpp"
#include "MFL.S1103/s1103.hpp"
#include "MFL.S2006/s2006.hpp"
#include "MFL.V1000/v1000.hpp"
