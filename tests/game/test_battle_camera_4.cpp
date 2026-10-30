// Phase 5 pair tests for slice battle_camera, part 4 (game/src/battle/battle_camera_4.cpp): the camera object's key ring
// and interpolation and the scene colour fade, each against its recompiled body on random battle worlds
// (tests/game/battle_camera_harness.h; test_battle_camera.cpp documents what a pair compares).
#include "battle_camera_harness.h"

#include "p3fes/game/battle_camera_4.h"

#include <cmath>

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::bcam_test;

namespace p3fes::recomp_gen {
P3FES_BCAM_BODIES_4(P3FES_BCAM_DECL_PAIR)
}  // namespace p3fes::recomp_gen

namespace {

// A unit quaternion (x, y, z, w) at va, sometimes left random.
void quat(Machine& m, std::mt19937& rng, u32 va) {
    if (chance(rng, 5)) return;
    float q[4];
    float n = 0.0f;
    for (float& x : q) {
        x = frand(rng, -1.0f, 1.0f);
        n += x * x;
    }
    n = n > 1e-6f ? 1.0f / std::sqrt(n) : 1.0f;
    for (int k = 0; k < 4; ++k) storef(m, va + 4 * k, q[k] * n);
}
// A camera key at va: position (x, y, z) at +0, rotation at +12.
u32 key_at(Machine& m, std::mt19937& rng, u32 va) {
    fill_floats(m, rng, va, 12, -300.0f, 300.0f);
    quat(m, rng, va + 12);
    return va;
}
u32 some_key(Machine& m, std::mt19937& rng) { return chance(rng, 8) ? 0u : key_at(m, rng, some_data(rng)); }

// A camera object at `cam`: flags (bit 0 no RwFrame keys, bits 1 / 2 the curves), four keys (+4 position, +16
// rotation, 28 apart), head / count / write (+116 / +118 / +120, mostly in range), the path parameter +124, progress
// +128, duration +132, eased parameter +148 and the RwFrame +152 (a block of floats).
void camera_object(Machine& m, std::mt19937& rng, u32 cam) {
    store16(m, cam + 0, static_cast<u16>(chance(rng, 90) ? rng() % 8 : rng()));
    for (u32 k = 0; k < 4; ++k) key_at(m, rng, cam + 4 + 28 * k);
    store16(m, cam + 116, static_cast<u16>(chance(rng, 90) ? rng() % 4 : rng() % 8));
    store16(m, cam + 118, static_cast<u16>(chance(rng, 90) ? rng() % 5 : rng() % 8));
    store16(m, cam + 120, static_cast<u16>(chance(rng, 90) ? rng() % 4 : rng() % 8));
    storef(m, cam + 124, frand(rng, 0.0f, chance(rng, 80) ? 1.0f : 1.6f));
    storef(m, cam + 128, frand(rng, 0.0f, 1.0f));
    storef(m, cam + 132, chance(rng, 5) ? 0.0f : frand(rng, 1.0f, 120.0f));
    storef(m, cam + 148, frand(rng, 0.4f, 1.1f));
    const u32 frame = some_data(rng);
    fill_floats(m, rng, frame, 0x80, -2.0f, 2.0f);
    for (u32 off = 0; off < 16; off += 4) store32(m, frame + off, 0);  // a frame without parent / objects
    store32(m, cam + 152, chance(rng, 90) ? frame : 0u);
}
u32 some_camera(Machine& m, std::mt19937& rng) {
    const u32 cam = chance(rng, 30) ? kG + 32 : some_data(rng);
    camera_object(m, rng, cam);
    return cam;
}

Inputs gen_interp(Machine& m, const World&, std::mt19937& rng) {  // sub_2A1E00(out, a, b; $f12)
    Inputs in;
    in.gpr[GPR_A0] = wide(rng, some_data(rng));
    in.gpr[GPR_A1] = wide(rng, key_at(m, rng, some_data(rng)));
    in.gpr[GPR_A2] = wide(rng, chance(rng, 10) ? static_cast<u32>(in.gpr[GPR_A1]) : key_at(m, rng, some_data(rng)));
    in.fpr[12] = fbits(chance(rng, 15) ? (chance(rng, 50) ? 0.0f : 1.0f) : frand(rng, -0.3f, 1.3f));
    return in;
}
Inputs gen_push(Machine& m, const World&, std::mt19937& rng) {  // sub_2A2050(cam, pos, rot)
    Inputs in;
    in.gpr[GPR_A0] = wide(rng, some_camera(m, rng));
    in.gpr[GPR_A1] = wide(rng, chance(rng, 10) ? 0u : key_at(m, rng, some_data(rng)));
    in.gpr[GPR_A2] = wide(rng, chance(rng, 10) ? 0u : key_at(m, rng, some_data(rng)) + 12);
    return in;
}
// sub_2A2170 / 2290 (cam, keys..., a3 = flags) and sub_2A2660 (cam, four keys a1..a3 / t0, t1 = flags)
Inputs gen_keys(Machine& m, std::mt19937& rng, bool four) {
    Inputs in;
    in.gpr[GPR_A0] = wide(rng, some_camera(m, rng));
    in.gpr[GPR_A1] = wide(rng, some_key(m, rng));
    in.gpr[GPR_A2] = wide(rng, some_key(m, rng));
    in.gpr[GPR_A3] = wide(rng, four ? some_key(m, rng) : rng() % 8);
    in.gpr[GPR_T0] = wide(rng, some_key(m, rng));
    in.gpr[GPR_T1] = wide(rng, rng() % 8);
    return in;
}
Inputs gen_keys2(Machine& m, const World&, std::mt19937& rng) { return gen_keys(m, rng, false); }
Inputs gen_keys4(Machine& m, const World&, std::mt19937& rng) { return gen_keys(m, rng, true); }
Inputs gen_path(Machine& m, const World&, std::mt19937& rng) {  // sub_2A2A20 / 2B50 / 2C40 / 2ED0 / 3010 / 3110 / 3160
    Inputs in;
    in.gpr[GPR_A0] = wide(rng, some_camera(m, rng));
    in.gpr[GPR_A1] = wide(rng, some_data(rng));
    in.gpr[GPR_A2] = wide(rng, some_data(rng));
    in.fpr[12] = fbits(chance(rng, 10) ? 0.0f : frand(rng, 0.0f, chance(rng, 70) ? 1.0f : 2.0f));
    return in;
}
Inputs gen_step(Machine& m, const World&, std::mt19937& rng) {  // sub_2A31B0(cam): the game camera gBtl+32
    Inputs in;
    const u32 cam = chance(rng, 85) ? kG + 32 : some_data(rng);
    camera_object(m, rng, cam);
    if (cam != kG + 32) camera_object(m, rng, kG + 32);
    in.gpr[GPR_A0] = wide(rng, cam);
    return in;
}
// The scene packet's data block: the frames +80, the frame counter +84 (0 = the first frame, sometimes past the end),
// flags +88; gBtl+12 bits 1 and 25 mostly set; the four unit lists gBtl+336.. (lists 2 / 3 mostly empty) with models.
Inputs gen_scene(Machine& m, const World& w, std::mt19937& rng) {
    Inputs in;
    u32 f = load32(m, kG + 12);
    f = chance(rng, 90) ? (f | 0x2000002u) : f;
    store32(m, kG + 12, f);
    for (u32 k = 2; k < 4; ++k) store32(m, kG + 336 + 8 * k, chance(rng, 70) ? 0u : w.units[rng() % kNumUnits]);
    for (u32 u : w.units) {
        const u32 model = some_data(rng);
        store32(m, u + 2548, model);
        fill_floats(m, rng, model + 924, 24, 0.0f, 2.0f);
        store32(m, u + 152, chance(rng, 60) ? (rng() | 2u) : rng());
        fill_floats(m, rng, u + 96, 32, 0.0f, 1.0f);
    }
    for (u32 k = 0; k < 6; ++k) fill_floats(m, rng, kG + 404 + 16 * k, 16, 0.0f, 1.0f);
    fill_floats(m, rng, kG + 500, 32, 0.0f, 1.0f);
    fill_floats(m, rng, kG + 548, 16, 0.0f, 1.0f);
    const u32 d = some_data(rng);
    fill_floats(m, rng, d, 80, 0.0f, 1.0f);
    const u32 frames = chance(rng, 10) ? 0u : rng() % 60;
    store32(m, d + 80, frames);
    store32(m, d + 84, chance(rng, 30) ? 0u : rng() % (frames + 3));
    store16(m, d + 88, static_cast<u16>(chance(rng, 50) ? rng() % 8 : rng()));
    in.gpr[GPR_A0] = wide(rng, d);
    return in;
}

const Spec kSpecs4[] = {
    {"sub_2A0440", PAIR(sub_2A0440, 002a0440), gen_scene},
    {"sub_2A1E00", PAIR(sub_2A1E00, 002a1e00), gen_interp},
    {"sub_2A2050", PAIR(sub_2A2050, 002a2050), gen_push},
    {"sub_2A2170", PAIR(sub_2A2170, 002a2170), gen_keys2},
    {"sub_2A2290", PAIR(sub_2A2290, 002a2290), gen_keys2},
    {"sub_2A2660", PAIR(sub_2A2660, 002a2660), gen_keys4},
    {"sub_2A2A20", PAIR(sub_2A2A20, 002a2a20), gen_path},
    {"sub_2A2B50", PAIR(sub_2A2B50, 002a2b50), gen_path},
    {"sub_2A2C40", PAIR(sub_2A2C40, 002a2c40), gen_path},
    {"sub_2A2ED0", PAIR(sub_2A2ED0, 002a2ed0), gen_path},
    {"sub_2A3010", PAIR(sub_2A3010, 002a3010), gen_path},
    {"sub_2A3110", PAIR(sub_2A3110, 002a3110), gen_path},
    {"sub_2A3160", PAIR(sub_2A3160, 002a3160), gen_path},
    {"sub_2A31B0", PAIR(sub_2A31B0, 002a31b0), gen_step},
};

}  // namespace

TEST_CASE("game(battle_camera_4): every replaced body equals its recompiled body on random battle worlds") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
#ifdef NDEBUG
    constexpr int kWorlds = 300;
#else
    constexpr int kWorlds = 100;
#endif
    run_specs(m, std::vector<Spec>(std::begin(kSpecs4), std::end(kSpecs4)), kWorlds, 0xBCA4u, "battle_camera_4");
}

#else
TEST_CASE("game(battle_camera_4): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
