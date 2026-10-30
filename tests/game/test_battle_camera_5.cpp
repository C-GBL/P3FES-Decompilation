// Phase 5 pair tests for slice battle_camera, part 5 (game/src/battle/battle_camera_5.cpp): each body against its
// recompiled body on random battle worlds (tests/game/battle_camera_harness.h; test_battle_camera.cpp documents
// what a pair compares). The generators below give the small camera states a camera work record whose subject chain
// (record +224 -> btlAction -> btlUnit -> DatUnit) is valid most of the time, the fields each state reads (phase,
// targets, motion unit, gBtl's repeat counter / scripted-battle word), and the leaf helpers their own records: a camera
// sequence record over a small sequence table, census counts, an enemy list. A documented-rule case checks the
// sequence step and census rules on the host.
#include "battle_camera_harness.h"

#include "p3fes/game/battle_camera_5.h"

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::bcam_test;

namespace p3fes::recomp_gen {
P3FES_BCAM_BODIES_5(P3FES_BCAM_DECL_PAIR)
}  // namespace p3fes::recomp_gen

namespace {

// The subject chain and the units: combatant flag, unit sizes / side / class / DatUnit, first targets.
void subject_world(Machine& m, const World& w, std::mt19937& rng) {
    for (u32 i = 0; i < kNumActions; ++i) {
        const u32 a = w.actions[i];
        store16(m, a + 26, static_cast<u16>(chance(rng, 75) ? (rng() | 1u) : (rng() & ~1u)));
        store16(m, a + 106, static_cast<u16>(chance(rng, 60) ? 1u : rng() % 4));
        store16(m, a + 110, static_cast<u16>(chance(rng, 85) ? rng() % 400 : rng()));
        if (chance(rng, 10)) store32(m, a + 56, a);  // targets itself
    }
    for (u32 i = 0; i < kNumUnits; ++i) {
        const u32 u = w.units[i];
        storef(m, u + 44, frand(rng, 0.5f, 2.0f));
        storef(m, u + 140, frand(rng, 20.0f, 250.0f));
        storef(m, u + 144, frand(rng, 20.0f, 200.0f));
        store16(m, u + 164, static_cast<u16>(chance(rng, 90) ? rng() % 11 : rng()));
        store32(m, u + 2604, some_data(rng));
        store32(m, u + 2560, chance(rng, 50) ? 0u : some_data(rng));
    }
}

// The camera states: the record of gen_cam_state plus the fields the states compare.
Inputs gen_cam5(Machine& m, const World& w, std::mt19937& rng) {
    subject_world(m, w, rng);
    Inputs in = gen_cam_state(m, w, rng);
    const u32 rec = static_cast<u32>(in.gpr[GPR_A0]);
    const u32 subj = load32(m, rec + 224);
    const u32 tgt = subj ? load32(m, subj + 56) : 0u;
    store32(m, rec + 220, chance(rng, 50) ? 0u : 1u);
    store32(m, rec + 272, chance(rng, 90) ? rng() % 8 : rng());
    store32(m, rec + 280, chance(rng, 70) ? tgt : w.actions[rng() % kNumActions]);
    store32(m, rec + 284, chance(rng, 70) ? tgt : w.actions[rng() % kNumActions]);
    store32(m, rec + 288, w.units[rng() % kNumUnits]);
    store16(m, rec + 292, static_cast<u16>(rng() % 64));
    storef(m, rec + 268, frand(rng, 50.0f, 400.0f));
    store16(m, kG + 266, static_cast<u16>(rng() % 3));
    store32(m, kG + 12, chance(rng, 30) ? (load32(m, kG + 12) | 0x200000u) : (load32(m, kG + 12) & ~0x200000u));
    const u32 grp = some_data(rng);
    store16(m, grp + 8, static_cast<u16>(chance(rng, 50) ? 436u : rng() % 500));
    store32(m, kG + 3004, grp);
    return in;
}

// A sequence table at `tbl`: u16 count, 60-byte steps from +4 (step +0 s16 frames, +24 u16 the camera kind).
void seq_table(Machine& m, std::mt19937& rng, u32 tbl) {
    store16(m, tbl, static_cast<u16>(chance(rng, 90) ? rng() % 6 : rng()));
    for (u32 k = 0; k < 5; ++k) {
        store16(m, tbl + 4 + 60 * k, static_cast<u16>(chance(rng, 80) ? rng() % 30 : rng()));
        store16(m, tbl + 4 + 60 * k + 28, static_cast<u16>(rng() % 3));
    }
}

// A camera sequence record (sub_2B6BD0 / sub_2B6CD0).
Inputs gen_seq(Machine& m, const World&, std::mt19937& rng) {
    Inputs in;
    const u32 rec = some_data(rng);
    const u32 tbl = some_data(rng);
    seq_table(m, rng, tbl);
    store16(m, rec + 10, static_cast<u16>(chance(rng, 80) ? static_cast<u32>(static_cast<s32>(rng() % 6) - 1) : rng()));
    store16(m, rec + 12, static_cast<u16>(rng() % 40));
    store16(m, rec + 14, static_cast<u16>(chance(rng, 80) ? (rng() | 1u) : (rng() & ~1u)));
    store32(m, rec + 16, chance(rng, 10) ? 0u : tbl);
    in.gpr[GPR_A0] = wide(rng, rec);
    return in;
}

// sub_2B6BF0(seq, a1, a2, table, flags).
Inputs gen_seq_start(Machine& m, const World& w, std::mt19937& rng) {
    Inputs in;
    in.gpr[GPR_A0] = wide(rng, some_data(rng));
    in.gpr[GPR_A1] = wide(rng, w.actions[rng() % kNumActions]);
    in.gpr[GPR_A2] = wide(rng, w.actions[rng() % kNumActions]);
    const u32 tbl = some_data(rng);
    seq_table(m, rng, tbl);
    in.gpr[GPR_A3] = wide(rng, tbl);
    in.gpr[GPR_T0] = chance(rng, 80) ? rng() % 16 : (static_cast<u64>(rng()) << 32) | rng();
    return in;
}

// A data block in $a0 (sub_2B6DB0's record, sub_2B6DE0's counts) with an enemy list for the census.
Inputs gen_block(Machine& m, const World& w, std::mt19937& rng) {
    subject_world(m, w, rng);
    Inputs in;
    in.gpr[GPR_A0] = wide(rng, some_data(rng));
    // the enemies' list A (gBtl+348 along +2608): a random subset of the units
    std::vector<u32> u(w.units.begin(), w.units.end());
    std::shuffle(u.begin(), u.end(), rng);
    const u32 n = chance(rng, 10) ? 0u : 1 + rng() % kNumUnits;
    store32(m, kG + 348, n ? u[0] : 0u);
    for (u32 i = 0; i < n; ++i) store32(m, u[i] + 2608, i + 1 < n ? u[i + 1] : 0u);
    return in;
}

// sub_2B6F70(counts): three u16 counts.
Inputs gen_counts(Machine& m, const World&, std::mt19937& rng) {
    Inputs in;
    const u32 c = some_data(rng);
    for (u32 k = 0; k < 3; ++k) store16(m, c + 2 * k, static_cast<u16>(chance(rng, 85) ? rng() % 3 : rng()));
    in.gpr[GPR_A0] = wide(rng, c);
    return in;
}

// sub_2B7000(unit, slot, value).
Inputs gen_slot(Machine& m, const World& w, std::mt19937& rng) {
    Inputs in;
    const u32 u = w.units[rng() % kNumUnits];
    m.at(u + 162)[0] = static_cast<u8>(chance(rng, 90) ? rng() % 2 : rng());
    in.gpr[GPR_A0] = wide(rng, u);
    in.gpr[GPR_A1] = chance(rng, 80) ? rng() % 4 : (static_cast<u64>(rng()) << 32) | rng();
    in.gpr[GPR_A2] = (static_cast<u64>(rng()) << 32) | rng();
    return in;
}

Inputs gen_none(Machine&, const World&, std::mt19937&) { return Inputs{}; }

const Spec kSpecs5[] = {
    {"sub_2A5460", PAIR(sub_2A5460, 002a5460), gen_cam5},
    {"sub_2A5F40", PAIR(sub_2A5F40, 002a5f40), gen_cam5},
    {"sub_2A6560", PAIR(sub_2A6560, 002a6560), gen_cam5},
    {"nullsub_87", PAIR(nullsub_87, 002a6ed0), gen_cam_state},
    {"nullsub_88", PAIR(nullsub_88, 002a7380), gen_cam_state},
    {"nullsub_89", PAIR(nullsub_89, 002a7820), gen_cam_state},
    {"sub_2A7830", PAIR(sub_2A7830, 002a7830), gen_cam5},
    {"sub_2AB2A0", PAIR(sub_2AB2A0, 002ab2a0), gen_cam5},
    {"sub_2AD770", PAIR(sub_2AD770, 002ad770), gen_cam5},
    {"nullsub_90", PAIR(nullsub_90, 002adc70), gen_cam_state},
    {"nullsub_91", PAIR(nullsub_91, 002adcc0), gen_cam_state},
    {"nullsub_92", PAIR(nullsub_92, 002add00), gen_cam_state},
    {"nullsub_93", PAIR(nullsub_93, 002ae250), gen_cam_state},
    {"nullsub_94", PAIR(nullsub_94, 002ae4c0), gen_cam_state},
    {"nullsub_95", PAIR(nullsub_95, 002ae730), gen_cam_state},
    {"sub_2B0210", PAIR(sub_2B0210, 002b0210), gen_cam5},
    {"nullsub_96", PAIR(nullsub_96, 002b1050), gen_cam_state},
    {"sub_2B1CF0", PAIR(sub_2B1CF0, 002b1cf0), gen_cam5},
    {"sub_2B1E00", PAIR(sub_2B1E00, 002b1e00), gen_cam5},
    {"sub_2B2800", PAIR(sub_2B2800, 002b2800), gen_cam5},
    {"nullsub_97", PAIR(nullsub_97, 002b2ea0), gen_cam_state},
    {"nullsub_98", PAIR(nullsub_98, 002b3330), gen_cam_state},
    {"nullsub_99", PAIR(nullsub_99, 002b3680), gen_cam_state},
    {"sub_2B4720", PAIR(sub_2B4720, 002b4720), gen_cam5},
    {"sub_2B4BC0", PAIR(sub_2B4BC0, 002b4bc0), gen_cam5},
    {"sub_2B4F40", PAIR(sub_2B4F40, 002b4f40), gen_cam5},
    {"sub_2B55D0", PAIR(sub_2B55D0, 002b55d0), gen_cam5},
    {"sub_2B5650", PAIR(sub_2B5650, 002b5650), gen_cam5},
    {"sub_2B6490", PAIR(sub_2B6490, 002b6490), gen_none},
    {"sub_2B6BD0", PAIR(sub_2B6BD0, 002b6bd0), gen_seq},
    {"sub_2B6BF0", PAIR(sub_2B6BF0, 002b6bf0), gen_seq_start},
    {"sub_2B6CD0", PAIR(sub_2B6CD0, 002b6cd0), gen_seq},
    {"sub_2B6DB0", PAIR(sub_2B6DB0, 002b6db0), gen_block},
    {"sub_2B6DE0", PAIR(sub_2B6DE0, 002b6de0), gen_block},
    {"sub_2B6F70", PAIR(sub_2B6F70, 002b6f70), gen_counts},
    {"sub_2B7000", PAIR(sub_2B7000, 002b7000), gen_slot},
};

}  // namespace

TEST_CASE("game(battle_camera_5): every replaced body equals its recompiled body on random battle worlds") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
#ifdef NDEBUG
    constexpr int kWorlds = 300;
#else
    constexpr int kWorlds = 100;
#endif
    run_specs(m, std::vector<Spec>(std::begin(kSpecs5), std::end(kSpecs5)), kWorlds, 0xBCA5u, "battle_camera_5");
}

TEST_CASE("game(battle_camera_5): the documented rules (sequence step, census row, side slots)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5EC5u};
    g_stats.clear();
    int steps = 0, rows = 0, slots = 0;
    for (int it = 0; it < 300; ++it) {
        const World w = random_world(m, rng);
        // sub_2B6CD0: a running record over a table of n steps at index i (frame f): the step i, or i + 1 once f
        // reaches step i's frames (or i == -1), when that index is below n and below 4; else 0.
        {
            Inputs in = gen_seq(m, w, rng);
            const u32 rec = static_cast<u32>(in.gpr[GPR_A0]);
            const u16 flags = load16(m, rec + 14);
            const u32 tbl = load32(m, rec + 16);
            const s32 i = static_cast<s16>(load16(m, rec + 10));
            const u16 f = load16(m, rec + 12);
            s32 k = i;
            if (tbl && (flags & 1)) {
                if (i == -1 || f >= static_cast<s16>(load16(m, tbl + 60 * static_cast<u32>(i) + 4))) k = static_cast<s16>(i + 1);
            }
            const u32 expect = (flags & 1) && tbl && k < static_cast<s32>(load16(m, tbl)) && k < 4 ? tbl + 4 + 60 * static_cast<u32>(k) : 0u;
            const Run r = pair(m, PAIR(sub_2B6CD0, 002b6cd0), in, rng(), "sequence rule");
            if (!r.stopped) {
                CHECK(static_cast<u32>(r.end.gpr[GPR_V0].u64[0]) == expect);
                ++steps;
            }
        }
        // sub_2B6F70: the first row of 0x694F10 whose limits hold the counts, else 23.
        {
            Inputs in = gen_counts(m, w, rng);
            const u32 c = static_cast<u32>(in.gpr[GPR_A0]);
            u32 expect = 23;
            for (u32 row = 0; row < 24; ++row) {
                const u32 base = 0x694F10u + 224 * row;
                if (load16(m, c) <= load16(m, base + 216) && load16(m, c + 2) <= load16(m, base + 218) &&
                    load16(m, c + 4) <= load16(m, base + 220)) {
                    expect = row;
                    break;
                }
            }
            const Run r = pair(m, PAIR(sub_2B6F70, 002b6f70), in, rng(), "census row rule");
            CHECK(r.end.gpr[GPR_V0].u64[0] == expect);
            ++rows;
        }
        // sub_2B7000: side 0 -> gBtl+2620 + 4 * slot, side 1 -> +2636 + 4 * slot.
        {
            Inputs in = gen_slot(m, w, rng);
            in.gpr[GPR_A1] = rng() % 4;
            const u32 u = static_cast<u32>(in.gpr[GPR_A0]);
            const u8 side = m.at(u + 162)[0];
            pair(m, PAIR(sub_2B7000, 002b7000), in, rng(), "side slot rule");
            if (side < 2) {
                CHECK(load32(m, kG + (side ? 2636u : 2620u) + 4 * static_cast<u32>(in.gpr[GPR_A1])) ==
                      static_cast<u32>(in.gpr[GPR_A2]));
                ++slots;
            }
        }
    }
    MESSAGE("rules: " << steps << " sequence steps, " << rows << " census rows, " << slots << " side slots");
    CHECK(steps > 100);
    CHECK(rows == 300);
    CHECK(slots > 100);
}

#else
TEST_CASE("game(battle_camera_5): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
