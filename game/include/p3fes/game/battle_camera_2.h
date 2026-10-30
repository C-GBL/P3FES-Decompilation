// Battle camera work states (slice battle_camera, part 2): the rows of the camera table 0x6939F0 that
// game/src/battle/battle_camera_2.cpp hand-decompiles (game/include/p3fes/game/battle_camera.h describes the band;
// pair tests tests/game/test_battle_camera_2.cpp).
#pragma once

#include "p3fes/game/battle_camera.h"

namespace p3fes::game {

// The replaced functions of battle_camera_2.cpp: X(name, address as 8 hex digits).
#define P3FES_BCAM_BODIES_2(X) \
    X(sub_2AA2B0, 002aa2b0) \
    X(sub_2AB330, 002ab330) \
    X(sub_2AC6E0, 002ac6e0) \
    X(sub_2AC920, 002ac920) \
    X(sub_2ACF90, 002acf90) \
    X(sub_2AD880, 002ad880) \
    X(sub_2ADD10, 002add10) \
    X(sub_2AE260, 002ae260) \
    X(sub_2AE4D0, 002ae4d0) \
    X(sub_2AE740, 002ae740) \
    X(sub_2AF7F0, 002af7f0)

#define P3FES_BCAM_API_2(name, addr) void name(EEContext& ctx);
P3FES_BCAM_BODIES_2(P3FES_BCAM_API_2)
#undef P3FES_BCAM_API_2

}  // namespace p3fes::game
