// Slice battle_camera, part 5: the small camera work states of the table 0x6939F0, the empty update rows and the leaf helpers at the band's end (0x2B6490-0x2B7000);
// game/src/battle/battle_camera_5.cpp (game/include/p3fes/game/battle_camera.h describes the band; pair tests
// tests/game/test_battle_camera_5.cpp).
#pragma once

#include "p3fes/game/battle_camera.h"

namespace p3fes::game {

// The replaced functions of battle_camera_5.cpp: X(name, address as 8 hex digits).
#define P3FES_BCAM_BODIES_5(X) \
    X(sub_2A5460, 002a5460) \
    X(sub_2A5F40, 002a5f40) \
    X(sub_2A6560, 002a6560) \
    X(nullsub_87, 002a6ed0) \
    X(nullsub_88, 002a7380) \
    X(nullsub_89, 002a7820) \
    X(sub_2A7830, 002a7830) \
    X(sub_2AB2A0, 002ab2a0) \
    X(sub_2AD770, 002ad770) \
    X(nullsub_90, 002adc70) \
    X(nullsub_91, 002adcc0) \
    X(nullsub_92, 002add00) \
    X(nullsub_93, 002ae250) \
    X(nullsub_94, 002ae4c0) \
    X(nullsub_95, 002ae730) \
    X(sub_2B0210, 002b0210) \
    X(nullsub_96, 002b1050) \
    X(sub_2B1CF0, 002b1cf0) \
    X(sub_2B1E00, 002b1e00) \
    X(sub_2B2800, 002b2800) \
    X(nullsub_97, 002b2ea0) \
    X(nullsub_98, 002b3330) \
    X(nullsub_99, 002b3680) \
    X(sub_2B4720, 002b4720) \
    X(sub_2B4BC0, 002b4bc0) \
    X(sub_2B4F40, 002b4f40) \
    X(sub_2B55D0, 002b55d0) \
    X(sub_2B5650, 002b5650) \
    X(sub_2B6490, 002b6490) \
    X(sub_2B6BD0, 002b6bd0) \
    X(sub_2B6BF0, 002b6bf0) \
    X(sub_2B6CD0, 002b6cd0) \
    X(sub_2B6DB0, 002b6db0) \
    X(sub_2B6DE0, 002b6de0) \
    X(sub_2B6F70, 002b6f70) \
    X(sub_2B7000, 002b7000)

#define P3FES_BCAM_API_5(name, addr) void name(EEContext& ctx);
P3FES_BCAM_BODIES_5(P3FES_BCAM_API_5)
#undef P3FES_BCAM_API_5

}  // namespace p3fes::game
