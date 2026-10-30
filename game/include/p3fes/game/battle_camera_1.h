// Battle camera work states (slice battle_camera, part 1): the rows of the camera table 0x6939F0 that
// game/src/battle/battle_camera_1.cpp hand-decompiles (game/include/p3fes/game/battle_camera.h describes the band;
// pair tests tests/game/test_battle_camera_1.cpp).
#pragma once

#include "p3fes/game/battle_camera.h"

namespace p3fes::game {

// The replaced functions of battle_camera_1.cpp: X(name, address as 8 hex digits).
#define P3FES_BCAM_BODIES_1(X) \
    X(sub_2A54F0, 002a54f0) \
    X(sub_2A5FD0, 002a5fd0) \
    X(sub_2A65F0, 002a65f0) \
    X(sub_2A7390, 002a7390) \
    X(sub_2A79F0, 002a79f0) \
    X(sub_2A8150, 002a8150) \
    X(sub_2A8D20, 002a8d20) \
    X(sub_2A95D0, 002a95d0)

#define P3FES_BCAM_API_1(name, addr) void name(EEContext& ctx);
P3FES_BCAM_BODIES_1(P3FES_BCAM_API_1)
#undef P3FES_BCAM_API_1

}  // namespace p3fes::game
