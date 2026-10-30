// Slice battle_camera, part 4: the battle camera object: its key ring (four position + rotation keys), interpolation and field of view (0x2A0440-0x2A31B0);
// game/src/battle/battle_camera_4.cpp (game/include/p3fes/game/battle_camera.h describes the band; pair tests
// tests/game/test_battle_camera_4.cpp).
#pragma once

#include "p3fes/game/battle_camera.h"

namespace p3fes::game {

// The replaced functions of battle_camera_4.cpp: X(name, address as 8 hex digits).
#define P3FES_BCAM_BODIES_4(X) \
    X(sub_2A0440, 002a0440) \
    X(sub_2A1E00, 002a1e00) \
    X(sub_2A2050, 002a2050) \
    X(sub_2A2170, 002a2170) \
    X(sub_2A2290, 002a2290) \
    X(sub_2A2660, 002a2660) \
    X(sub_2A2A20, 002a2a20) \
    X(sub_2A2B50, 002a2b50) \
    X(sub_2A2C40, 002a2c40) \
    X(sub_2A2ED0, 002a2ed0) \
    X(sub_2A3010, 002a3010) \
    X(sub_2A3110, 002a3110) \
    X(sub_2A3160, 002a3160) \
    X(sub_2A31B0, 002a31b0)

#define P3FES_BCAM_API_4(name, addr) void name(EEContext& ctx);
P3FES_BCAM_BODIES_4(P3FES_BCAM_API_4)
#undef P3FES_BCAM_API_4

}  // namespace p3fes::game
