// Phase 5 pair tests for slice battle_camera, part 3 (game/src/battle/battle_camera_3.cpp): each camera work state
// against its recompiled body on random battle worlds (tests/game/battle_camera_harness.h; test_battle_camera.cpp
// documents what a pair compares). The worlds of gen_cam3: units with sensible positions / sizes / rotations, the
// camera work record's current key and field of view, and RW's engine table (the matrix routines sub_4C6C60 calls).
#include "battle_camera_harness.h"

#include "p3fes/game/battle_camera_3.h"

#include <cmath>

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::bcam_test;

namespace p3fes::recomp_gen {
P3FES_BCAM_BODIES_3(P3FES_BCAM_DECL_PAIR)
}  // namespace p3fes::recomp_gen

namespace {

// --- the camera work states' world ----------------------------------------------------------------------------------
// RW's engine table: sub_4C6C60 / sub_4C31B0 call the matrix routines through *(gp-17376) + 0x960070 (+8 .. +0x24);
// the battle snapshots' values (code addresses of the ELF and the engine's own globals).
void rw_engine_table(Machine& m) {
    store32(m, kGp - 17376u, 0x134u);
    const u32 tbl = 0x960070u + 0x134u;
    const u32 words[] = {0x4E3EC0u, 0x4E3F20u, 0x4E3FC0u, 0x4E4020u, 0x95FF50u, 0x20000u, 0x4E3E40u};
    for (u32 k = 0; k < std::size(words); ++k) store32(m, tbl + 8 + 4 * k, words[k]);
}
// A unit quaternion (x, y, z, w) at va: a turn about the up axis, sometimes a random one.
void quat(Machine& m, std::mt19937& rng, u32 va) {
    float q[4];
    if (chance(rng, 70)) {
        const float h = frand(rng, -3.1416f, 3.1416f) * 0.5f;
        q[0] = 0.0f;
        q[1] = std::sin(h);
        q[2] = 0.0f;
        q[3] = std::cos(h);
    } else {
        float n = 0.0f;
        for (float& c : q) {
            c = frand(rng, -1.0f, 1.0f);
            n += c * c;
        }
        n = std::sqrt(n > 1e-6f ? n : 1.0f);
        for (float& c : q) c /= n;
    }
    for (u32 k = 0; k < 4; ++k) storef(m, va + 4 * k, q[k]);
}
// Every unit: positions / sizes as floats over its first 0x200 bytes (the position at +4..+12 and +128..+136, the
// rotation +28, scale +44, sizes +132 / +140 / +144, the point +220..+232), the side byte +162 and flags +156 kept,
// the short offsets +148 / +150 small. The camera work record gBtl+32: the current key +156 (position, quaternion),
// the field of view +184 (degrees), +224 the subject; gBtl+328 the current action, +2980 the party count.
Inputs gen_cam3(Machine& m, const World& w, std::mt19937& rng) {
    rw_engine_table(m);
    for (u32 u : w.units) {
        const u8 side = m.at(u + 162)[0];
        const u32 flags = load32(m, u + 156);
        fill_floats(m, rng, u, 0x200, -300.0f, 300.0f);
        m.at(u + 162)[0] = side;
        store32(m, u + 156, flags);
        quat(m, rng, u + 28);
        storef(m, u + 44, chance(rng, 80) ? 1.0f : frand(rng, 0.5f, 2.0f));
        for (u32 off : {132u, 140u, 144u, 232u}) storef(m, u + off, chance(rng, 5) ? 0.0f : frand(rng, 20.0f, 250.0f));
        store16(m, u + 148, static_cast<u16>(rng() % 64));
        store16(m, u + 150, static_cast<u16>(rng() % 64));
        store16(m, u + 2546, static_cast<u16>(rng() % 4));
    }
    for (u32 a : w.actions) {  // the target cursor's candidates (+136, the current one at +194; sub_2C0880)
        for (u32 k = 0; k < 12; ++k) store32(m, a + 136 + 4 * k, w.actions[rng() % kNumActions]);
        store16(m, a + 194, static_cast<u16>(rng() % 12));
    }
    store32(m, kG + 328, w.actions[rng() % kNumActions]);
    m.at(kG + 2980)[0] = static_cast<u8>(chance(rng, 80) ? 1 + rng() % 3 : rng() % 6);
    store32(m, kG + 12, rng() & ~(chance(rng, 70) ? 0x200000u : 0u));
    const u32 rec = kCamWork;
    fill_floats(m, rng, rec, 0x100, -400.0f, 400.0f);
    fill_floats(m, rng, rec + 156, 12, -600.0f, 600.0f);
    quat(m, rng, rec + 168);
    storef(m, rec + 184, chance(rng, 90) ? frand(rng, 20.0f, 70.0f) : frand(rng, -10.0f, 179.0f));
    store32(m, rec + 224, chance(rng, 5) ? 0u : w.actions[rng() % kNumActions]);
    store32(m, rec + 260, rng() % 2);
    store32(m, rec + 264, rng() % 2);
    Inputs in;
    in.gpr[GPR_A0] = wide(rng, rec);
    in.gpr[GPR_A1] = wide(rng, chance(rng, 50) ? 0u : (chance(rng, 70) ? 1u : some_data(rng)));
    in.fpr[12] = fbits(chance(rng, 80) ? frand(rng, -90.0f, 90.0f) : frand(rng, -2.0f, 2.0f));
    in.fpr[13] = fbits(frand(rng, 0.2f, 8.0f));
    in.fpr[14] = fbits(frand(rng, -2.0f, 2.0f));
    in.fpr[15] = fbits(frand(rng, -2.0f, 2.0f));
    return in;
}
// sub_2B2EB0(record, key): the key in a data block
Inputs gen_cam3_key(Machine& m, const World& w, std::mt19937& rng) {
    Inputs in = gen_cam3(m, w, rng);
    const u32 key = some_data(rng);
    fill_floats(m, rng, key, 12, -600.0f, 600.0f);
    quat(m, rng, key + 12);
    in.gpr[GPR_A1] = wide(rng, key);
    return in;
}

const Spec kSpecs3[] = {
    {"sub_2AEF80", PAIR(sub_2AEF80, 002aef80), gen_cam3},
    {"sub_2AF960", PAIR(sub_2AF960, 002af960), gen_cam3},
    {"sub_2B0280", PAIR(sub_2B0280, 002b0280), gen_cam3},
    {"sub_2B1060", PAIR(sub_2B1060, 002b1060), gen_cam3},
    {"sub_2B17A0", PAIR(sub_2B17A0, 002b17a0), gen_cam3},
    {"sub_2B21F0", PAIR(sub_2B21F0, 002b21f0), gen_cam3},
    {"sub_2B2940", PAIR(sub_2B2940, 002b2940), gen_cam3},
    {"sub_2B2EB0", PAIR(sub_2B2EB0, 002b2eb0), gen_cam3_key},
    {"sub_2B3340", PAIR(sub_2B3340, 002b3340), gen_cam3},
    {"sub_2B3690", PAIR(sub_2B3690, 002b3690), gen_cam3},
    {"sub_2B3980", PAIR(sub_2B3980, 002b3980), gen_cam3},
    {"sub_2B3C60", PAIR(sub_2B3C60, 002b3c60), gen_cam3},
    {"sub_2B3F80", PAIR(sub_2B3F80, 002b3f80), gen_cam3},
    {"sub_2B41E0", PAIR(sub_2B41E0, 002b41e0), gen_cam3},
};

}  // namespace

TEST_CASE("game(battle_camera_3): every replaced camera state equals its recompiled body on random battle worlds") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
#ifdef NDEBUG
    constexpr int kWorlds = 300;
#else
    constexpr int kWorlds = 100;
#endif
    run_specs(m, std::vector<Spec>(std::begin(kSpecs3), std::end(kSpecs3)), kWorlds, 0xBCA3u, "battle_camera_3");
}

#else
TEST_CASE("game(battle_camera_3): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
