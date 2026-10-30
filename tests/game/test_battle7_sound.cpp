// Phase 5 pair tests for slice battle7, sound (game/src/battle/battle7_voice/cutin.cpp): the party voice / navigator line pickers, the voice bank and line packets, the sound / motion / support packets, the support events, the analysed-enemy line, the cut-in / special effect packets, the boss hook. Every body
// against its recompiled body (__recomp) on random worlds and on the battle snapshots, perturbed (battle7_pairs.h: the
// whole register file and cycles at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad,
// the BIOS window, the bus log, the stand-in call log), plus documented-rule checks against host models (below).
#include "battle7_pairs.h"

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::b7t;

namespace p3fes::recomp_gen {
void fn_sub_2D86C0_002d86c0(EEContext&);
void fn_sub_2D86C0_002d86c0__recomp(EEContext&);
void fn_sub_2D8850_002d8850(EEContext&);
void fn_sub_2D8850_002d8850__recomp(EEContext&);
void fn_sub_2DB2A0_002db2a0(EEContext&);
void fn_sub_2DB2A0_002db2a0__recomp(EEContext&);
void fn_sub_2DB650_002db650(EEContext&);
void fn_sub_2DB650_002db650__recomp(EEContext&);
void fn_sub_2DB7D0_002db7d0(EEContext&);
void fn_sub_2DB7D0_002db7d0__recomp(EEContext&);
void fn_sub_2DB800_002db800(EEContext&);
void fn_sub_2DB800_002db800__recomp(EEContext&);
void fn_sub_2DBAC0_002dbac0(EEContext&);
void fn_sub_2DBAC0_002dbac0__recomp(EEContext&);
void fn_sub_2DBB00_002dbb00(EEContext&);
void fn_sub_2DBB00_002dbb00__recomp(EEContext&);
void fn_sub_2DD180_002dd180(EEContext&);
void fn_sub_2DD180_002dd180__recomp(EEContext&);
void fn_sub_2DD1B0_002dd1b0(EEContext&);
void fn_sub_2DD1B0_002dd1b0__recomp(EEContext&);
void fn_sub_2DD1F0_002dd1f0(EEContext&);
void fn_sub_2DD1F0_002dd1f0__recomp(EEContext&);
void fn_sub_2DD720_002dd720(EEContext&);
void fn_sub_2DD720_002dd720__recomp(EEContext&);
void fn_sub_2DD760_002dd760(EEContext&);
void fn_sub_2DD760_002dd760__recomp(EEContext&);
void fn_sub_2DD7D0_002dd7d0(EEContext&);
void fn_sub_2DD7D0_002dd7d0__recomp(EEContext&);
void fn_sub_2DD830_002dd830(EEContext&);
void fn_sub_2DD830_002dd830__recomp(EEContext&);
void fn_sub_2DDDC0_002dddc0(EEContext&);
void fn_sub_2DDDC0_002dddc0__recomp(EEContext&);
void fn_sub_2DDF10_002ddf10(EEContext&);
void fn_sub_2DDF10_002ddf10__recomp(EEContext&);
void fn_sub_2DE030_002de030(EEContext&);
void fn_sub_2DE030_002de030__recomp(EEContext&);
void fn_sub_2DEFE0_002defe0(EEContext&);
void fn_sub_2DEFE0_002defe0__recomp(EEContext&);
void fn_sub_2E0350_002e0350(EEContext&);
void fn_sub_2E0350_002e0350__recomp(EEContext&);
void fn_sub_2E0540_002e0540(EEContext&);
void fn_sub_2E0540_002e0540__recomp(EEContext&);
void fn_sub_2E1CD0_002e1cd0(EEContext&);
void fn_sub_2E1CD0_002e1cd0__recomp(EEContext&);
void fn_sub_2E1DF0_002e1df0(EEContext&);
void fn_sub_2E1DF0_002e1df0__recomp(EEContext&);
void fn_sub_2E1F10_002e1f10(EEContext&);
void fn_sub_2E1F10_002e1f10__recomp(EEContext&);
void fn_sub_2E2030_002e2030(EEContext&);
void fn_sub_2E2030_002e2030__recomp(EEContext&);
void fn_sub_2E2110_002e2110(EEContext&);
void fn_sub_2E2110_002e2110__recomp(EEContext&);
void fn_sub_2E22A0_002e22a0(EEContext&);
void fn_sub_2E22A0_002e22a0__recomp(EEContext&);
void fn_sub_2E2920_002e2920(EEContext&);
void fn_sub_2E2920_002e2920__recomp(EEContext&);
void fn_sub_2E2A60_002e2a60(EEContext&);
void fn_sub_2E2A60_002e2a60__recomp(EEContext&);
void fn_sub_2E2C70_002e2c70(EEContext&);
void fn_sub_2E2C70_002e2c70__recomp(EEContext&);
void fn_sub_2E2CB0_002e2cb0(EEContext&);
void fn_sub_2E2CB0_002e2cb0__recomp(EEContext&);
void fn_sub_2E2D00_002e2d00(EEContext&);
void fn_sub_2E2D00_002e2d00__recomp(EEContext&);
void fn_sub_2E2D40_002e2d40(EEContext&);
void fn_sub_2E2D40_002e2d40__recomp(EEContext&);
void fn_sub_2E3010_002e3010(EEContext&);
void fn_sub_2E3010_002e3010__recomp(EEContext&);
void fn_sub_2E30A0_002e30a0(EEContext&);
void fn_sub_2E30A0_002e30a0__recomp(EEContext&);
void fn_sub_2E3D50_002e3d50(EEContext&);
void fn_sub_2E3D50_002e3d50__recomp(EEContext&);
void fn_sub_2E3DB0_002e3db0(EEContext&);
void fn_sub_2E3DB0_002e3db0__recomp(EEContext&);
void fn_sub_2E3DE0_002e3de0(EEContext&);
void fn_sub_2E3DE0_002e3de0__recomp(EEContext&);
void fn_sub_2E3E60_002e3e60(EEContext&);
void fn_sub_2E3E60_002e3e60__recomp(EEContext&);
void fn_sub_2E3F20_002e3f20(EEContext&);
void fn_sub_2E3F20_002e3f20__recomp(EEContext&);
void fn_sub_2E3F70_002e3f70(EEContext&);
void fn_sub_2E3F70_002e3f70__recomp(EEContext&);
void fn_sub_2E3FB0_002e3fb0(EEContext&);
void fn_sub_2E3FB0_002e3fb0__recomp(EEContext&);
void fn_sub_2E3FE0_002e3fe0(EEContext&);
void fn_sub_2E3FE0_002e3fe0__recomp(EEContext&);
void fn_sub_2E4040_002e4040(EEContext&);
void fn_sub_2E4040_002e4040__recomp(EEContext&);
void fn_sub_2E40D0_002e40d0(EEContext&);
void fn_sub_2E40D0_002e40d0__recomp(EEContext&);
void fn_sub_2E4120_002e4120(EEContext&);
void fn_sub_2E4120_002e4120__recomp(EEContext&);
void fn_sub_2E41D0_002e41d0(EEContext&);
void fn_sub_2E41D0_002e41d0__recomp(EEContext&);
void fn_sub_2E4310_002e4310(EEContext&);
void fn_sub_2E4310_002e4310__recomp(EEContext&);
void fn_sub_2E43A0_002e43a0(EEContext&);
void fn_sub_2E43A0_002e43a0__recomp(EEContext&);
void fn_datGetFlag_0016f190(EEContext&);
void fn_sub_17D800_0017d800(EEContext&);
void fn_datCalcGetBadStatusNoDown_00300530(EEContext&);
void fn_sub_2DCA60_002dca60(EEContext&);
void fn_sub_2DC830_002dc830(EEContext&);
void fn_datSetFlag_0016f1f0(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

namespace rg = p3fes::recomp_gen;

const Case kCases[] = {
    {"sub_2D86C0", 0x2D86C0u, &rg::fn_sub_2D86C0_002d86c0, &rg::fn_sub_2D86C0_002d86c0__recomp, "A"},
    {"sub_2D8850", 0x2D8850u, &rg::fn_sub_2D8850_002d8850, &rg::fn_sub_2D8850_002d8850__recomp, "A"},
    {"sub_2DB2A0", 0x2DB2A0u, &rg::fn_sub_2DB2A0_002db2a0, &rg::fn_sub_2DB2A0_002db2a0__recomp, "n"},
    {"sub_2DB650", 0x2DB650u, &rg::fn_sub_2DB650_002db650, &rg::fn_sub_2DB650_002db650__recomp, "u"},
    {"sub_2DB7D0", 0x2DB7D0u, &rg::fn_sub_2DB7D0_002db7d0, &rg::fn_sub_2DB7D0_002db7d0__recomp, "P"},
    {"sub_2DB800", 0x2DB800u, &rg::fn_sub_2DB800_002db800, &rg::fn_sub_2DB800_002db800__recomp, "nn"},
    {"sub_2DBAC0", 0x2DBAC0u, &rg::fn_sub_2DBAC0_002dbac0, &rg::fn_sub_2DBAC0_002dbac0__recomp, ""},
    {"sub_2DBB00", 0x2DBB00u, &rg::fn_sub_2DBB00_002dbb00, &rg::fn_sub_2DBB00_002dbb00__recomp, "E"},
    {"sub_2DD180", 0x2DD180u, &rg::fn_sub_2DD180_002dd180, &rg::fn_sub_2DD180_002dd180__recomp, "P"},
    {"sub_2DD1B0", 0x2DD1B0u, &rg::fn_sub_2DD1B0_002dd1b0, &rg::fn_sub_2DD1B0_002dd1b0__recomp, "P"},
    {"sub_2DD1F0", 0x2DD1F0u, &rg::fn_sub_2DD1F0_002dd1f0, &rg::fn_sub_2DD1F0_002dd1f0__recomp, "nnn"},
    {"sub_2DD720", 0x2DD720u, &rg::fn_sub_2DD720_002dd720, &rg::fn_sub_2DD720_002dd720__recomp, "P"},
    {"sub_2DD760", 0x2DD760u, &rg::fn_sub_2DD760_002dd760, &rg::fn_sub_2DD760_002dd760__recomp, "nnn"},
    {"sub_2DD7D0", 0x2DD7D0u, &rg::fn_sub_2DD7D0_002dd7d0, &rg::fn_sub_2DD7D0_002dd7d0__recomp, "D"},
    {"sub_2DD830", 0x2DD830u, &rg::fn_sub_2DD830_002dd830, &rg::fn_sub_2DD830_002dd830__recomp, "Unnn"},
    {"sub_2DDDC0", 0x2DDDC0u, &rg::fn_sub_2DDDC0_002dddc0, &rg::fn_sub_2DDDC0_002dddc0__recomp, "A"},
    {"sub_2DDF10", 0x2DDF10u, &rg::fn_sub_2DDF10_002ddf10, &rg::fn_sub_2DDF10_002ddf10__recomp, "A"},
    {"sub_2DE030", 0x2DE030u, &rg::fn_sub_2DE030_002de030, &rg::fn_sub_2DE030_002de030__recomp, "A"},
    {"sub_2DEFE0", 0x2DEFE0u, &rg::fn_sub_2DEFE0_002defe0, &rg::fn_sub_2DEFE0_002defe0__recomp, "A"},
    {"sub_2E0350", 0x2E0350u, &rg::fn_sub_2E0350_002e0350, &rg::fn_sub_2E0350_002e0350__recomp, "A"},
    {"sub_2E0540", 0x2E0540u, &rg::fn_sub_2E0540_002e0540, &rg::fn_sub_2E0540_002e0540__recomp, "A"},
    {"sub_2E1CD0", 0x2E1CD0u, &rg::fn_sub_2E1CD0_002e1cd0, &rg::fn_sub_2E1CD0_002e1cd0__recomp, "A"},
    {"sub_2E1DF0", 0x2E1DF0u, &rg::fn_sub_2E1DF0_002e1df0, &rg::fn_sub_2E1DF0_002e1df0__recomp, "A"},
    {"sub_2E1F10", 0x2E1F10u, &rg::fn_sub_2E1F10_002e1f10, &rg::fn_sub_2E1F10_002e1f10__recomp, "A"},
    {"sub_2E2030", 0x2E2030u, &rg::fn_sub_2E2030_002e2030, &rg::fn_sub_2E2030_002e2030__recomp, "A"},
    {"sub_2E2110", 0x2E2110u, &rg::fn_sub_2E2110_002e2110, &rg::fn_sub_2E2110_002e2110__recomp, "A"},
    {"sub_2E22A0", 0x2E22A0u, &rg::fn_sub_2E22A0_002e22a0, &rg::fn_sub_2E22A0_002e22a0__recomp, "A"},
    {"sub_2E2920", 0x2E2920u, &rg::fn_sub_2E2920_002e2920, &rg::fn_sub_2E2920_002e2920__recomp, "V"},
    {"sub_2E2A60", 0x2E2A60u, &rg::fn_sub_2E2A60_002e2a60, &rg::fn_sub_2E2A60_002e2a60__recomp, "W"},
    {"sub_2E2C70", 0x2E2C70u, &rg::fn_sub_2E2C70_002e2c70, &rg::fn_sub_2E2C70_002e2c70__recomp, "P"},
    {"sub_2E2CB0", 0x2E2CB0u, &rg::fn_sub_2E2CB0_002e2cb0, &rg::fn_sub_2E2CB0_002e2cb0__recomp, "n"},
    {"sub_2E2D00", 0x2E2D00u, &rg::fn_sub_2E2D00_002e2d00, &rg::fn_sub_2E2D00_002e2d00__recomp, "n"},
    {"sub_2E2D40", 0x2E2D40u, &rg::fn_sub_2E2D40_002e2d40, &rg::fn_sub_2E2D40_002e2d40__recomp, ""},
    {"sub_2E3010", 0x2E3010u, &rg::fn_sub_2E3010_002e3010, &rg::fn_sub_2E3010_002e3010__recomp, "P"},
    {"sub_2E30A0", 0x2E30A0u, &rg::fn_sub_2E30A0_002e30a0, &rg::fn_sub_2E30A0_002e30a0__recomp, "nnnb"},
    {"sub_2E3D50", 0x2E3D50u, &rg::fn_sub_2E3D50_002e3d50, &rg::fn_sub_2E3D50_002e3d50__recomp, ""},
    {"sub_2E3DB0", 0x2E3DB0u, &rg::fn_sub_2E3DB0_002e3db0, &rg::fn_sub_2E3DB0_002e3db0__recomp, ""},
    {"sub_2E3DE0", 0x2E3DE0u, &rg::fn_sub_2E3DE0_002e3de0, &rg::fn_sub_2E3DE0_002e3de0__recomp, "nn"},
    {"sub_2E3E60", 0x2E3E60u, &rg::fn_sub_2E3E60_002e3e60, &rg::fn_sub_2E3E60_002e3e60__recomp, "P"},
    {"sub_2E3F20", 0x2E3F20u, &rg::fn_sub_2E3F20_002e3f20, &rg::fn_sub_2E3F20_002e3f20__recomp, ""},
    {"sub_2E3F70", 0x2E3F70u, &rg::fn_sub_2E3F70_002e3f70, &rg::fn_sub_2E3F70_002e3f70__recomp, "P"},
    {"sub_2E3FB0", 0x2E3FB0u, &rg::fn_sub_2E3FB0_002e3fb0, &rg::fn_sub_2E3FB0_002e3fb0__recomp, ""},
    {"sub_2E3FE0", 0x2E3FE0u, &rg::fn_sub_2E3FE0_002e3fe0, &rg::fn_sub_2E3FE0_002e3fe0__recomp, "n"},
    {"sub_2E4040", 0x2E4040u, &rg::fn_sub_2E4040_002e4040, &rg::fn_sub_2E4040_002e4040__recomp, "P"},
    {"sub_2E40D0", 0x2E40D0u, &rg::fn_sub_2E40D0_002e40d0, &rg::fn_sub_2E40D0_002e40d0__recomp, ""},
    {"sub_2E4120", 0x2E4120u, &rg::fn_sub_2E4120_002e4120, &rg::fn_sub_2E4120_002e4120__recomp, "P"},
    {"sub_2E41D0", 0x2E41D0u, &rg::fn_sub_2E41D0_002e41d0, &rg::fn_sub_2E41D0_002e41d0__recomp, ""},
    {"sub_2E4310", 0x2E4310u, &rg::fn_sub_2E4310_002e4310, &rg::fn_sub_2E4310_002e4310__recomp, ""},
    {"sub_2E43A0", 0x2E43A0u, &rg::fn_sub_2E43A0_002e43a0, &rg::fn_sub_2E43A0_002e43a0__recomp, ""},
};

const Snap kSnaps[] = {{"b_5800", 24}, {"battle_ref_6150", 2}, {"b_6150", 2}, {"b_6300", 1}, {"climb_ref_17000", 1}};

}  // namespace

TEST_CASE("game(battle7 sound): every body equals its recompiled body on random worlds") {
    run_random(kCases, std::size(kCases), 24, "battle7 sound");
}

TEST_CASE("game(battle7 sound): every body on the battle snapshots, perturbed") {
    run_snapshots(kCases, std::size(kCases), kSnaps, std::size(kSnaps), "battle7 sound");
}

TEST_CASE("game(battle7 sound): the voice, navigator, support and packet rules") {
    auto m = new_machine();
    if (!m) return;
    int checks = 0;
    auto v0 = [&](Fn f, u64 a0 = 0, u64 a1 = 0, u64 a2 = 0, u64 a3 = 0) { return v0_of(solo(*m, f, {a0, a1, a2, a3})); };
    // (1) the picker tables: the party voice pickers 0x697C10 by situation, the navigator pickers 0x6978F0
    {
        const std::pair<u32, u32> kVoice[] = {{1, 0x2DDDC0u}, {2, 0x2DDF10u}, {3, 0x2DE030u}, {9, 0x2DEFE0u}, {10, 0x2E0350u},
                                              {11, 0x2E0540u}, {17, 0x2E1CD0u}, {18, 0x2E1DF0u}, {19, 0x2E1F10u}, {20, 0x2E2030u},
                                              {21, 0x2E2110u}, {22, 0x2E22A0u}};
        for (const auto& [row, fn] : kVoice) {
            INFO("voice picker row " << row);
            CHECK(ld32(*m, b7::kVoicePickers + 4u * row) == fn);
            ++checks;
        }
        CHECK(ld32(*m, b7::kNaviPickers + 4u * 3) == 0x2D86C0u);
        CHECK(ld32(*m, b7::kNaviPickers + 4u * 6) == 0x2D8850u);
        checks += 2;
    }
    // (2) the fixed-line pickers: each party member (unit ids 2..5, 7..10) its own line, unit 3 by the flag *0x697BE4,
    //     unit 9 by sub_17D800; enemies, the hero (1), 6 and 11 none (-1). Picker 1 only with flag 388.
    {
        const u32 slot = ld32(*m, 0x697BE4u);
        const bool f3 = slot != 0xFFFFFFFFu && v0(&rg::fn_datGetFlag_0016f190, slot) != 0;
        const bool fes = v0(&rg::fn_sub_17D800_0017d800) != 0;
        struct Row {
            Fn fn;
            s32 l2, l3a, l3b, l4, l5, l7, l8, l9a, l9b, l10;  // l3a / l9a: the flag / sub_17D800 lines
            bool needs388;
        };
        const Row kRows[] = {
            {&rg::fn_sub_2DDDC0_002dddc0, 146, 220, 219, 328, 401, 474, 547, 1117, 620, 685, true},
            {&rg::fn_sub_2DDF10_002ddf10, 147, 222, 221, 329, 402, 475, 548, 1118, 621, 686, false},
            {&rg::fn_sub_2DE030_002de030, 148, 224, 223, 330, 403, 476, 549, 1119, 622, 687, false},
            {&rg::fn_sub_2E1CD0_002e1cd0, 155, 236, 235, 337, 410, 483, 556, 1126, 629, 694, false},
            {&rg::fn_sub_2E1DF0_002e1df0, 150, 227, 226, 332, 405, 478, 551, 1121, 624, 689, false},
            {&rg::fn_sub_2E1F10_002e1f10, 152, 231, 230, 334, 407, 480, 553, 1123, 626, 691, false},
            {&rg::fn_sub_2E2030_002e2030, 149, 225, 225, 331, 404, 477, 550, 1120, 623, 688, false},
            {&rg::fn_sub_2E0540_002e0540, 217, 326, 326, 399, 472, 545, 618, 1202, 683, -1, false},
        };
        for (const Row& r : kRows)
            for (u32 set388 = 0; set388 < 2; ++set388)
            for (u16 id = 0; id <= 11; ++id)
                for (u8 side : {u8{0}, u8{1}}) {
                    v0(&rg::fn_datSetFlag_0016f1f0, 388, set388);  // flag 388 off / on (picker 1 needs it)
                    const bool f388 = v0(&rg::fn_datGetFlag_0016f190, 388) != 0;
                    CHECK(f388 == (set388 != 0));
                    const Fake f = fake_battle(*m, 1, 1);
                    st8(*m, f.unit[0] + b3::unit::kSide, side);
                    st16(*m, f.unit[0] + b3::unit::kId, id);
                    s32 want = -1;
                    if (side == 0 && (!r.needs388 || f388)) switch (id) {
                        case 2: want = r.l2; break;
                        case 3: want = f3 ? r.l3a : r.l3b; break;
                        case 4: want = r.l4; break;
                        case 5: want = r.l5; break;
                        case 7: want = r.l7; break;
                        case 8: want = r.l8; break;
                        case 9: want = fes ? r.l9a : r.l9b; break;
                        case 10: want = r.l10; break;
                        default: break;
                        }
                    INFO("id " << id << " side " << int(side));
                    CHECK(static_cast<s32>(v0(r.fn, sx(f.act[0]))) == want);
                    ++checks;
                }
        // the navigator's member line (picker 3): 96..103 for the members 2..5, 7..10
        static const s32 kNavi[11] = {-1, -1, 96, 97, 98, 99, -1, 100, 101, 102, 103};
        for (u16 id = 0; id <= 10; ++id) {
            const Fake f = fake_battle(*m, 1, 1);
            st16(*m, f.unit[0] + b3::unit::kId, id);
            CHECK(static_cast<s32>(v0(&rg::fn_sub_2D86C0_002d86c0, sx(f.act[0]))) == kNavi[id]);
            st8(*m, f.unit[0] + b3::unit::kSide, 1);
            CHECK(static_cast<s32>(v0(&rg::fn_sub_2D86C0_002d86c0, sx(f.act[0]))) == -1);
            checks += 2;
        }
        // the two-line picker 10: one of the member's pair (50 % each); unit 9 with sub_17D800 always 1187
        static const s32 kPair[11] = {-1, -1, 215, 309, 397, 470, -1, 543, 616, 681, -1};
        for (int k = 0; k < 40; ++k)
            for (u16 id = 0; id <= 10; ++id) {
                const Fake f = fake_battle(*m, 1, 1);
                st16(*m, f.unit[0] + b3::unit::kId, id);
                const s32 got = static_cast<s32>(v0(&rg::fn_sub_2E0350_002e0350, sx(f.act[0])));
                INFO("id " << id);
                if (kPair[id] < 0) CHECK(got == -1);
                else if (id == 9 && fes) CHECK(got == 1187);
                else CHECK((got == kPair[id] || got == kPair[id] + 1));
                ++checks;
            }
        // pickers 21 / 22: a party unit's line from sub_357FD0 (311..319 / 320..324, or 1188..1195 / 1196..1200)
        for (int k = 0; k < 20; ++k) {
            const Fake f = fake_battle(*m, 1, 1);
            const s32 a = static_cast<s32>(v0(&rg::fn_sub_2E2110_002e2110, sx(f.act[0])));
            const s32 b = static_cast<s32>(v0(&rg::fn_sub_2E22A0_002e22a0, sx(f.act[0])));
            CHECK((fes ? (a >= 1188 && a <= 1195) : (a >= 311 && a <= 319)));
            CHECK((fes ? (b >= 1196 && b <= 1200) : (b >= 320 && b <= 324)));
            st8(*m, f.unit[0] + b3::unit::kSide, 1);
            CHECK(static_cast<s32>(v0(&rg::fn_sub_2E2110_002e2110, sx(f.act[0]))) == -1);
            checks += 3;
        }
    }
    // (3) the support events: arming sets the event bit, zeroes its counter and sets its limit within the documented
    //     ranges (event 0: 2..4 with the member word cleared, 1: 2..3, 2: 2..4 with flag 320, 3..5 with 321)
    {
        const bool f320 = v0(&rg::fn_datGetFlag_0016f190, 320) != 0, f321 = v0(&rg::fn_datGetFlag_0016f190, 321) != 0;
        for (int k = 0; k < 40; ++k)
            for (u16 ev = 0; ev < 3; ++ev) {
                const Fake f = fake_battle(*m, 1, 0);
                st16(*m, f.btl + b5::gbtl5::kSupportCount + 4u * ev, 7);
                st32(*m, f.btl + b5::gbtl5::kSupportMember, 0xDEADu);
                v0(&rg::fn_sub_2DB2A0_002db2a0, ev);
                INFO("event " << ev);
                CHECK((ld16(*m, f.btl + b5::gbtl5::kSupportEvents) & (1u << ev)) != 0);
                CHECK(ld16(*m, f.btl + b5::gbtl5::kSupportCount + 4u * ev) == 0);
                const u16 lim = ld16(*m, f.btl + b5::gbtl5::kSupportLimit + 4u * ev);
                if (ev == 0) {
                    CHECK((lim >= 2 && lim <= 4));
                    CHECK(ld32(*m, f.btl + b5::gbtl5::kSupportMember) == 0);
                } else if (ev == 1) {
                    CHECK((lim >= 2 && lim <= 3));
                } else if (f320) {
                    CHECK((lim >= 2 && lim <= 4));
                } else if (f321) {
                    CHECK((lim >= 3 && lim <= 5));
                }
                checks += 3;
            }
    }
    // (4) the ailment lines: one ailment (datCalcGetBadStatusNoDown's answer) -> 40, 42, .. 56 by its bit, +1 for an
    //     enemy; the turn-start lines by the ailment and the command kind; nothing for an inactive action
    {
        static const u32 kBits[] = {0x1u, 0x2u, 0x4u, 0x8u, 0x10u, 0x20u, 0x40u, 0x80u, 0x100u, 0x200u, 0u};
        for (u32 bit : kBits)
            for (u8 side : {u8{0}, u8{1}})
                for (u16 cmd : {u16{1}, u16{6}, u16{7}, u16{8}, u16{11}, u16{12}, u16{2}})
                    for (u8 sleep : {u8{0}, u8{1}}) {
                        const Fake f = fake_battle(*m, 1, 1);
                        st8(*m, f.unit[0] + b3::unit::kSide, side);
                        st32(*m, f.dat[0] + b3::dat::kStatus, bit);
                        st16(*m, f.act[0] + b3::act::kCmdKind, cmd);
                        st8(*m, f.act[0] + b3::act::kOneMore, sleep);
                        const u32 ail = static_cast<u32>(v0(&rg::fn_datCalcGetBadStatusNoDown_00300530, sx(f.dat[0])));
                        s32 base = -1;
                        switch (ail) {
                        case 1: base = 40; break;
                        case 2: base = 42; break;
                        case 4: base = 44; break;
                        case 8: base = 46; break;
                        case 16: base = 48; break;
                        case 32: base = 50; break;
                        case 64: base = 52; break;
                        case 256: base = 54; break;
                        case 512: base = 56; break;
                        default: break;
                        }
                        s32 turn = -1;
                        const bool c_special = cmd == 11 || cmd == 8 || cmd == 7;
                        switch (ail) {
                        case 512: turn = c_special ? 20 : -1; break;
                        case 64: turn = cmd == 11 ? 12 : -1; break;
                        case 32: turn = cmd == 11 ? 10 : -1; break;
                        case 16: turn = sleep == 0 ? 18 : -1; break;  // +40 / +41 both zero
                        case 8: turn = c_special ? 16 : (cmd == 12 || cmd == 6) ? 14 : -1; break;
                        case 1: turn = cmd == 1 ? 6 : 8; break;
                        default: break;
                        }
                        INFO("status " << hex64(bit) << " ailment " << ail << " side " << int(side) << " cmd " << cmd);
                        CHECK(static_cast<s32>(v0(&rg::fn_sub_2DCA60_002dca60, sx(f.act[0]))) == (base < 0 ? -1 : base + side));
                        CHECK(static_cast<s32>(v0(&rg::fn_sub_2DC830_002dc830, sx(f.act[0]))) == (turn < 0 ? -1 : turn + side));
                        st16(*m, f.act[0] + b3::act::kFlags2, 0);
                        CHECK(static_cast<s32>(v0(&rg::fn_sub_2DCA60_002dca60, sx(f.act[0]))) == -1);
                        CHECK(static_cast<s32>(v0(&rg::fn_sub_2DC830_002dc830, sx(f.act[0]))) == -1);
                        checks += 4;
                    }
    }
    // (5) the packet creators on the live battle (b_5800): the packet kind, the callbacks and the data layout
    const std::vector<u8> snap = read_snapshot("b_5800");
    if (!snap.empty()) {
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        write_rw_slots(*m);
        const Objects o = objects_of(*m);
        struct P {
            Fn fn;
            Args a;
            u32 kind, on_queue, update;
        };
        const u32 unit = o.units.empty() ? 0 : o.units[0];
        const P kP[] = {
            {&rg::fn_sub_2DB800_002db800, {5, 0x1234, 0, 0}, 2049, 0, 0x2DB7D0u},
            {&rg::fn_sub_2DD1F0_002dd1f0, {3, 4, 5, 0}, 2305, 0x2DD180u, 0x2DD1B0u},
            {&rg::fn_sub_2DD760_002dd760, {6, 0x77, 0x88, 0}, 2311, 0, 0x2DD720u},
            {&rg::fn_sub_2DD830_002dd830, {sx(unit), 1, 2, 3}, 2312, 0, 0x2DD7D0u},
            {&rg::fn_sub_2E2CB0_002e2cb0, {42, 0, 0, 0}, 2562, 0, 0x2E2C70u},
            {&rg::fn_sub_2E30A0_002e30a0, {1, 2, 3, 1}, 2564, 0, 0x2E3010u},
            {&rg::fn_sub_2E3DE0_002e3de0, {7, 8, 0, 0}, 3081, 0x2E3D50u, 0x2E3DB0u},
            {&rg::fn_sub_2E3F20_002e3f20, {0, 0, 0, 0}, 3082, 0, 0x2E3E60u},
            {&rg::fn_sub_2E3FE0_002e3fe0, {9, 0, 0, 0}, 3083, 0x2E3F70u, 0x2E3FB0u},
            {&rg::fn_sub_2E40D0_002e40d0, {0, 0, 0, 0}, 3084, 0, 0x2E4040u},
            {&rg::fn_sub_2E41D0_002e41d0, {0, 0, 0, 0}, 3085, 0, 0x2E4120u},
        };
        for (const P& p : kP) {
            const u32 pkt = static_cast<u32>(v0(p.fn, p.a[0], p.a[1], p.a[2], p.a[3]));
            INFO("packet kind " << p.kind);
            REQUIRE(in_ram(pkt));
            CHECK(ld32(*m, pkt + b3::pkt::kKind) == p.kind);
            if (p.on_queue) CHECK(ld32(*m, pkt + b3::pkt::kOnQueue) == p.on_queue);
            CHECK(ld32(*m, pkt + b3::pkt::kUpdate) == p.update);
            const u32 d = ld32(*m, pkt + b3::pkt::kData);
            switch (p.kind) {
            case 2049: CHECK(ld16(*m, d) == 5); CHECK(ld32(*m, d + 4) == 0x1234u); break;
            case 2305: CHECK(ld16(*m, d) == 3); CHECK(ld16(*m, d + 2) == 4); CHECK(ld16(*m, d + 4) == 5); break;
            case 2311: CHECK(ld16(*m, d) == 6); CHECK(ld32(*m, d + 4) == 0x77u); CHECK(ld32(*m, d + 8) == 0x88u); break;
            case 2312: CHECK(ld32(*m, d) == unit); CHECK(ld16(*m, d + 4) == 1); CHECK(ld16(*m, d + 6) == 2); CHECK(ld16(*m, d + 8) == 3); break;
            case 2562: CHECK(ld16(*m, d) == 42); break;
            case 2564: CHECK(ld16(*m, d + 4) == 3); CHECK(ld16(*m, d + 6) == 1); CHECK(ld32(*m, d + 8) == 0); break;
            case 3081: CHECK(ld32(*m, d) == 7); CHECK(ld32(*m, d + 4) == 8); CHECK((ld8(*m, pkt + b3::pkt::kFlags) & 0x11) == 0); break;
            case 3082: CHECK(ld16(*m, d) == 0); break;
            case 3083: CHECK(ld16(*m, d) == 9); break;
            default: CHECK(ld16(*m, d) == 0); CHECK(ld32(*m, d + 4) == 0); break;
            }
            ++checks;
        }
        // (6) the support watch: the uid and the id of the unit with that uid
        for (u32 u : o.units) {
            const u32 uid = ld32(*m, u + b3::unit::kUid);
            v0(&rg::fn_sub_2DB650_002db650, uid);
            CHECK(ld32(*m, o.btl + b7::gbtl7::kSupportUid) == uid);
            CHECK(ld16(*m, o.btl + b5::gbtl5::kSupportEnemy) == ld16(*m, u + b3::unit::kId));
            checks += 2;
        }
        // (7) the voice line packet is done at once without the voice bank (gBtl +2806 bit 0)
        st16(*m, o.btl + b7::gbtl7::kVoiceReady, 0);
        const u32 blk = kScratch + 0x30000u;
        std::memset(m->at(blk), 0, 32);
        st32(*m, blk, o.acts.empty() ? 0 : o.acts[0]);
        CHECK(v0(&rg::fn_sub_2E2A60_002e2a60, sx(blk)) == 1);
        CHECK(ld32(*m, blk + 20) == 0);
        checks += 2;
    }
    MESSAGE("battle7 sound rules: " << checks << " checks");
}

#else

TEST_CASE("game(battle7 sound): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
