// Phase 5 pair tests for slice battle_camera, part 2 (game/src/battle/battle_camera_2.cpp): each camera work state
// against its recompiled body on random battle worlds (tests/game/battle_camera_harness.h; test_battle_camera.cpp
// documents what a pair compares).
#include "battle_camera_harness.h"

#include "p3fes/game/battle_camera_2.h"

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::bcam_test;

namespace p3fes::recomp_gen {
P3FES_BCAM_BODIES_2(P3FES_BCAM_DECL_PAIR)
}  // namespace p3fes::recomp_gen

namespace {

// A camera work record for the part-2 states: gen_cam_state's record and arguments, plus a valid subject chain (the
// btlAction at +224 a combatant most of the time, its unit with a sensible scale / height / radius / rotation), a field
// of view, a phase (+272) and a motion unit (+288) / motion (+292), the target fields (+256..+262), and the float
// arguments in camera ranges ($f12 an angle, $f13 a distance factor, $f14 a height factor, $f15 a minimum distance).
Inputs gen_cam2(Machine& m, const World& w, std::mt19937& rng) {
    Inputs in = gen_cam_state(m, w, rng);
    const u32 rec = static_cast<u32>(in.gpr[GPR_A0]);
    const u32 act = load32(m, rec + 224);
    if (act != 0) {
        if (chance(rng, 85)) store16(m, act + 26, static_cast<u16>(load16(m, act + 26) | 1u));
        const u32 unit = load32(m, act + 48);
        storef(m, unit + 44, chance(rng, 90) ? frand(rng, 0.5f, 2.0f) : frand(rng, -1.0f, 1.0f));
        storef(m, unit + 144, frand(rng, 10.0f, 200.0f));
        storef(m, unit + 140, frand(rng, 10.0f, 200.0f));
        for (u32 k = 0; k < 3; ++k) storef(m, unit + 28 + 4 * k, frand(rng, -3.2f, 3.2f));
        for (u32 k = 0; k < 4; ++k) storef(m, unit + 16 + 4 * k, frand(rng, -300.0f, 300.0f));
        store16(m, act + 110, static_cast<u16>(rng() % 1024));
        if (chance(rng, 50)) store32(m, rec + 256, load32(m, act + 56));
    }
    storef(m, rec + 184, chance(rng, 90) ? frand(rng, 20.0f, 80.0f) : frand(rng, -10.0f, 200.0f));
    store16(m, rec + 272, static_cast<u16>(chance(rng, 90) ? rng() % 7 : rng() % 16));
    store32(m, rec + 276, chance(rng, 50) ? 0u : 1u);
    store32(m, rec + 220, chance(rng, 50) ? 0u : 1u);
    const u32 mu = w.units[rng() % w.units.size()];
    store32(m, rec + 288, mu);
    // sub_2A3750's checks on the motion unit: +51 non-zero and +152 bit 1 (then the motion timing callees)
    if (chance(rng, 70)) m.at(mu + 51)[0] = static_cast<u8>(1 + rng() % 255);
    if (chance(rng, 70)) store32(m, mu + 152, load32(m, mu + 152) | 2u);
    if (act != 0 && chance(rng, 30)) store16(m, act + 106, 1);
    store16(m, rec + 292, static_cast<u16>(rng() % 64));
    in.fpr[12] = fbits(frand(rng, -3.2f, 3.2f));
    in.fpr[13] = fbits(frand(rng, 0.5f, 3.0f));
    in.fpr[14] = fbits(frand(rng, -1.0f, 2.0f));
    in.fpr[15] = fbits(frand(rng, 0.0f, 600.0f));
    return in;
}

const Spec kSpecs2[] = {
    {"sub_2AA2B0", PAIR(sub_2AA2B0, 002aa2b0), gen_cam2},
    {"sub_2AB330", PAIR(sub_2AB330, 002ab330), gen_cam2},
    {"sub_2AC6E0", PAIR(sub_2AC6E0, 002ac6e0), gen_cam2},
    {"sub_2AC920", PAIR(sub_2AC920, 002ac920), gen_cam2},
    {"sub_2ACF90", PAIR(sub_2ACF90, 002acf90), gen_cam2},
    {"sub_2AD880", PAIR(sub_2AD880, 002ad880), gen_cam2},
    {"sub_2ADD10", PAIR(sub_2ADD10, 002add10), gen_cam2},
    {"sub_2AE260", PAIR(sub_2AE260, 002ae260), gen_cam2},
    {"sub_2AE4D0", PAIR(sub_2AE4D0, 002ae4d0), gen_cam2},
    {"sub_2AE740", PAIR(sub_2AE740, 002ae740), gen_cam2},
    {"sub_2AF7F0", PAIR(sub_2AF7F0, 002af7f0), gen_cam2},
};

}  // namespace

TEST_CASE("game(battle_camera_2): every replaced camera state equals its recompiled body on random battle worlds") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
#ifdef NDEBUG
    constexpr int kWorlds = 300;
#else
    constexpr int kWorlds = 100;
#endif
    run_specs(m, std::vector<Spec>(std::begin(kSpecs2), std::end(kSpecs2)), kWorlds, 0xBCA2u, "battle_camera_2");
}

#else
TEST_CASE("game(battle_camera_2): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
