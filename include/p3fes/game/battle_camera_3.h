// Battle camera work states (slice battle_camera, part 3): the rows of the camera table 0x6939F0 that
// game/src/battle/battle_camera_3.cpp hand-decompiles (game/include/p3fes/game/battle_camera.h describes the band;
// pair tests tests/game/test_battle_camera_3.cpp).
#pragma once

#include "p3fes/game/battle_camera.h"

namespace p3fes::game {

// The replaced functions of battle_camera_3.cpp: X(name, address as 8 hex digits). All take the camera work record
// gBtl+32 in $a0 (the table rows' init functions: 2 sub_2B3690, 5 sub_2B41E0, 10 sub_2AF960, 14 sub_2B2940, 31
// sub_2B3340, 32 sub_2B3980, 33 sub_2B3C60, 34 sub_2B3F80) or are helpers of such rows with more arguments:
//   sub_2AEF80(record, set at once)          the camera between the subject and its target's side (row 29's update)
//   sub_2B0280(record, target, keep; $f12)   a unit acting on its first target (row 11's init, boss sub_2E7210)
//   sub_2B1060(record; $f12 turn, $f13 lens) a turned two-shot of the subject and its target (row 15's init)
//   sub_2B17A0(record; $f12 sweep, $f13 lens) a four-key sweep around subject and target (row 15's init)
//   sub_2B21F0(record, choose; $f12 lens)    a two-shot over a shoulder (row 13's update)
//   sub_2B2EB0(record, key)                  a key over the enemy side, turned at most 45 degrees (row 30's init)
// Each body's comment in the .cpp gives the geometry.
#define P3FES_BCAM_BODIES_3(X) \
    X(sub_2AEF80, 002aef80) \
    X(sub_2AF960, 002af960) \
    X(sub_2B0280, 002b0280) \
    X(sub_2B1060, 002b1060) \
    X(sub_2B17A0, 002b17a0) \
    X(sub_2B21F0, 002b21f0) \
    X(sub_2B2940, 002b2940) \
    X(sub_2B2EB0, 002b2eb0) \
    X(sub_2B3340, 002b3340) \
    X(sub_2B3690, 002b3690) \
    X(sub_2B3980, 002b3980) \
    X(sub_2B3C60, 002b3c60) \
    X(sub_2B3F80, 002b3f80) \
    X(sub_2B41E0, 002b41e0)

#define P3FES_BCAM_API_3(name, addr) void name(EEContext& ctx);
P3FES_BCAM_BODIES_3(P3FES_BCAM_API_3)
#undef P3FES_BCAM_API_3

}  // namespace p3fes::game
