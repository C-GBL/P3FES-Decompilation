// Phase 5 pair tests for slice battle_camera, part 1 (game/src/battle/battle_camera_1.cpp): each camera work state
// against its recompiled body on random battle worlds (tests/game/battle_camera_harness.h; test_battle_camera.cpp
// documents what a pair compares).
#include "battle_camera_harness.h"

#include "p3fes/game/battle_camera_1.h"

#include <cmath>

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::bcam_test;

namespace p3fes::recomp_gen {
P3FES_BCAM_BODIES_1(P3FES_BCAM_DECL_PAIR)
}  // namespace p3fes::recomp_gen

namespace {

// A unit rotation: a random unit quaternion at va (x, y, z, w).
void unit_quat(Machine& m, std::mt19937& rng, u32 va) {
    float q[4];
    float n = 0.0f;
    for (float& x : q) {
        x = frand(rng, -1.0f, 1.0f);
        n += x * x;
    }
    n = n > 1e-6f ? 1.0f / std::sqrt(n) : 1.0f;
    for (int k = 0; k < 4; ++k) storef(m, va + 4 * k, q[k] * n);
}

// The camera work states of part 1 read the work record gBtl+32 (the key +156: position, rotation; the field of view
// +184; the subject btlAction +224, its unit +48 and first target +56 -> +48) and the units' placement floats (+4..+12
// position, +28 rotation, +44 scale, +128..+148 offsets and sizes, +220..+232 an anchor). The world gets sensible values
// there (sometimes left random); $a1 / $a2 / $a3 the reset flag and the two angle limits of sub_2A54F0.
Inputs gen_cam1(Machine& m, const World& w, std::mt19937& rng) {
    Inputs in = gen_cam_state(m, w, rng);
    const u32 rec = static_cast<u32>(in.gpr[GPR_A0]);
    if (chance(rng, 90)) {
        fill_floats(m, rng, rec + 156, 12, -300.0f, 300.0f);
        unit_quat(m, rng, rec + 168);
        storef(m, rec + 184, frand(rng, 0.3f, 1.6f));
    }
    if (chance(rng, 97)) store32(m, rec + 224, w.actions[rng() % kNumActions]);
    for (u32 u : w.units) {
        if (chance(rng, 10)) continue;
        fill_floats(m, rng, u + 4, 12, -300.0f, 300.0f);
        unit_quat(m, rng, u + 28);
        storef(m, u + 44, frand(rng, 0.5f, 2.0f));
        fill_floats(m, rng, u + 128, 24, chance(rng, 80) ? 0.0f : -50.0f, 120.0f);
        fill_floats(m, rng, u + 220, 16, -300.0f, 300.0f);
    }
    for (u32 u : w.units) store32(m, u + 2560, chance(rng, 85) ? 0u : w.units[rng() % kNumUnits]);  // the sub-object
    // The RW vector functions the matrix helpers (sub_4C6C60 ...) call through the engine's table, as the battle
    // snapshots hold them: *(gp-17376) = 0x134, 0x960070 + 0x134 + 8.. = the plugin's functions.
    store32(m, kGp - 17376u, 0x134u);
    store32(m, 0x9601ACu, 0x4E3EC0u);
    store32(m, 0x9601B0u, 0x4E3F20u);
    store32(m, 0x9601B4u, 0x4E3FC0u);
    store32(m, 0x9601B8u, 0x4E4020u);
    store32(m, 0x9601C4u, 0x4E3E40u);
    // the game's random state (sub_357FD0's 16 bytes at 0x957BF0; all zero in the ELF, which makes every datCalcRand 0)
    for (u32 k = 0; k < 4; ++k) store32(m, 0x957BF0u + 4 * k, rng() | 1u);
    in.gpr[GPR_A1] = wide(rng, chance(rng, 70) ? 0u : chance(rng, 80) ? 1u : rng());
    const u32 lim = 1 + rng() % 40;
    in.gpr[GPR_A2] = wide(rng, lim);
    in.gpr[GPR_A3] = wide(rng, lim + rng() % 90);
    return in;
}

const Spec kSpecs1[] = {
    {"sub_2A54F0", PAIR(sub_2A54F0, 002a54f0), gen_cam1},
    {"sub_2A5FD0", PAIR(sub_2A5FD0, 002a5fd0), gen_cam1},
    {"sub_2A65F0", PAIR(sub_2A65F0, 002a65f0), gen_cam1},
    {"sub_2A7390", PAIR(sub_2A7390, 002a7390), gen_cam1},
    {"sub_2A79F0", PAIR(sub_2A79F0, 002a79f0), gen_cam1},
    {"sub_2A8150", PAIR(sub_2A8150, 002a8150), gen_cam1},
    {"sub_2A8D20", PAIR(sub_2A8D20, 002a8d20), gen_cam1},
    {"sub_2A95D0", PAIR(sub_2A95D0, 002a95d0), gen_cam1},
};

}  // namespace

TEST_CASE("game(battle_camera_1): every replaced camera state equals its recompiled body on random battle worlds") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
#ifdef NDEBUG
    constexpr int kWorlds = 300;
#else
    constexpr int kWorlds = 100;
#endif
    run_specs(m, std::vector<Spec>(std::begin(kSpecs1), std::end(kSpecs1)), kWorlds, 0xBCA1u, "battle_camera_1");
}

#else
TEST_CASE("game(battle_camera_1): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
