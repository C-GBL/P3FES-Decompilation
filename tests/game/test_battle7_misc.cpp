// Phase 5 pair tests for slice battle7, misc (game/src/battle/battle7_action/camera.cpp): ROUNDUP (the all-out attack), the help window and command panel helpers, the camera script commands, kill / revive, the poison damage and ailment lines, the boss archive files, the cell position, the camera shots. Every body
// against its recompiled body (__recomp) on random worlds and on the battle snapshots, perturbed (battle7_pairs.h: the
// whole register file and cycles at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad,
// the BIOS window, the bus log, the stand-in call log), plus documented-rule checks against host models (below).
#include "battle7_pairs.h"

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::b7t;

namespace p3fes::recomp_gen {
void fn_sub_298610_00298610(EEContext&);
void fn_sub_298610_00298610__recomp(EEContext&);
void fn_sub_2BCCD0_002bccd0(EEContext&);
void fn_sub_2BCCD0_002bccd0__recomp(EEContext&);
void fn_sub_2BD7E0_002bd7e0(EEContext&);
void fn_sub_2BD7E0_002bd7e0__recomp(EEContext&);
void fn_sub_2BEDD0_002bedd0(EEContext&);
void fn_sub_2BEDD0_002bedd0__recomp(EEContext&);
void fn_sub_2BF690_002bf690(EEContext&);
void fn_sub_2BF690_002bf690__recomp(EEContext&);
void fn_sub_2BF850_002bf850(EEContext&);
void fn_sub_2BF850_002bf850__recomp(EEContext&);
void fn_sub_2BF880_002bf880(EEContext&);
void fn_sub_2BF880_002bf880__recomp(EEContext&);
void fn_sub_2BF8B0_002bf8b0(EEContext&);
void fn_sub_2BF8B0_002bf8b0__recomp(EEContext&);
void fn_sub_2BF8E0_002bf8e0(EEContext&);
void fn_sub_2BF8E0_002bf8e0__recomp(EEContext&);
void fn_sub_2BF910_002bf910(EEContext&);
void fn_sub_2BF910_002bf910__recomp(EEContext&);
void fn_sub_2BF940_002bf940(EEContext&);
void fn_sub_2BF940_002bf940__recomp(EEContext&);
void fn_sub_2D0D70_002d0d70(EEContext&);
void fn_sub_2D0D70_002d0d70__recomp(EEContext&);
void fn_sub_2D0DE0_002d0de0(EEContext&);
void fn_sub_2D0DE0_002d0de0__recomp(EEContext&);
void fn_sub_2D1030_002d1030(EEContext&);
void fn_sub_2D1030_002d1030__recomp(EEContext&);
void fn_sub_2D10F0_002d10f0(EEContext&);
void fn_sub_2D10F0_002d10f0__recomp(EEContext&);
void fn_sub_2D1180_002d1180(EEContext&);
void fn_sub_2D1180_002d1180__recomp(EEContext&);
void fn_sub_2D19B0_002d19b0(EEContext&);
void fn_sub_2D19B0_002d19b0__recomp(EEContext&);
void fn_sub_2D21E0_002d21e0(EEContext&);
void fn_sub_2D21E0_002d21e0__recomp(EEContext&);
void fn_sub_2D5CF0_002d5cf0(EEContext&);
void fn_sub_2D5CF0_002d5cf0__recomp(EEContext&);
void fn_sub_2D7890_002d7890(EEContext&);
void fn_sub_2D7890_002d7890__recomp(EEContext&);
void fn_sub_2DC670_002dc670(EEContext&);
void fn_sub_2DC670_002dc670__recomp(EEContext&);
void fn_sub_2DC830_002dc830(EEContext&);
void fn_sub_2DC830_002dc830__recomp(EEContext&);
void fn_sub_2DCA60_002dca60(EEContext&);
void fn_sub_2DCA60_002dca60__recomp(EEContext&);
void fn_sub_2F87E0_002f87e0(EEContext&);
void fn_sub_2F87E0_002f87e0__recomp(EEContext&);
void fn_sub_2F8810_002f8810(EEContext&);
void fn_sub_2F8810_002f8810__recomp(EEContext&);
void fn_sub_2FD160_002fd160(EEContext&);
void fn_sub_2FD160_002fd160__recomp(EEContext&);
void fn_sub_2FDDB0_002fddb0(EEContext&);
void fn_sub_2FDDB0_002fddb0__recomp(EEContext&);
void fn_sub_2ADC30_002adc30(EEContext&);
void fn_sub_2ADC30_002adc30__recomp(EEContext&);
void fn_sub_2ADC80_002adc80(EEContext&);
void fn_sub_2ADC80_002adc80__recomp(EEContext&);
void fn_sub_2ADCD0_002adcd0(EEContext&);
void fn_sub_2ADCD0_002adcd0__recomp(EEContext&);
void fn_sub_2B2880_002b2880(EEContext&);
void fn_sub_2B2880_002b2880__recomp(EEContext&);
void fn_sub_2B32C0_002b32c0(EEContext&);
void fn_sub_2B32C0_002b32c0__recomp(EEContext&);
void fn_sub_2E4A30_002e4a30(EEContext&);
void fn_sub_2E4A30_002e4a30__recomp(EEContext&);
void fn_sub_2E5040_002e5040(EEContext&);
void fn_sub_2E5040_002e5040__recomp(EEContext&);
void fn_sub_2E71C0_002e71c0(EEContext&);
void fn_sub_2E71C0_002e71c0__recomp(EEContext&);
void fn_sub_2E7320_002e7320(EEContext&);
void fn_sub_2E7320_002e7320__recomp(EEContext&);
void fn_sub_2E7680_002e7680(EEContext&);
void fn_sub_2E7680_002e7680__recomp(EEContext&);
void fn_sub_2E76A0_002e76a0(EEContext&);
void fn_sub_2E76A0_002e76a0__recomp(EEContext&);
void fn_sub_2E7710_002e7710(EEContext&);
void fn_sub_2E7710_002e7710__recomp(EEContext&);
void fn_sub_2E77C0_002e77c0(EEContext&);
void fn_sub_2E77C0_002e77c0__recomp(EEContext&);
void fn_sub_2E7810_002e7810(EEContext&);
void fn_sub_2E7810_002e7810__recomp(EEContext&);
void fn_sub_2E7880_002e7880(EEContext&);
void fn_sub_2E7880_002e7880__recomp(EEContext&);
void fn_sub_2E87B0_002e87b0(EEContext&);
void fn_sub_2E87B0_002e87b0__recomp(EEContext&);
void fn_sub_2E8C80_002e8c80(EEContext&);
void fn_sub_2E8C80_002e8c80__recomp(EEContext&);
void fn_sub_2E8C90_002e8c90(EEContext&);
void fn_sub_2E8C90_002e8c90__recomp(EEContext&);
void fn_sub_2E8D20_002e8d20(EEContext&);
void fn_sub_2E8D20_002e8d20__recomp(EEContext&);
void fn_sub_2E8D40_002e8d40(EEContext&);
void fn_sub_2E8D40_002e8d40__recomp(EEContext&);
void fn_sub_2E8D70_002e8d70(EEContext&);
void fn_sub_2E8D70_002e8d70__recomp(EEContext&);
void fn_sub_2E9060_002e9060(EEContext&);
void fn_sub_2E9060_002e9060__recomp(EEContext&);
void fn_datCalcGetMaxHp_002ffdf0(EEContext&);
void fn_datCalcGetHp_002ffd70(EEContext&);
void fn_datCalcIsDead_0030b5a0(EEContext&);
void fn_datCalcGetBadStatusNoDown_00300530(EEContext&);
void fn_datCalcGetEffectState_00301750(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

namespace rg = p3fes::recomp_gen;

const Case kCases[] = {
    {"sub_298610", 0x298610u, &rg::fn_sub_298610_00298610, &rg::fn_sub_298610_00298610__recomp, "A"},
    {"sub_2BCCD0", 0x2BCCD0u, &rg::fn_sub_2BCCD0_002bccd0, &rg::fn_sub_2BCCD0_002bccd0__recomp, "Ux"},
    {"sub_2BD7E0", 0x2BD7E0u, &rg::fn_sub_2BD7E0_002bd7e0, &rg::fn_sub_2BD7E0_002bd7e0__recomp, "H"},
    {"sub_2BEDD0", 0x2BEDD0u, &rg::fn_sub_2BEDD0_002bedd0, &rg::fn_sub_2BEDD0_002bedd0__recomp, "A"},
    {"sub_2BF690", 0x2BF690u, &rg::fn_sub_2BF690_002bf690, &rg::fn_sub_2BF690_002bf690__recomp, "m"},
    {"sub_2BF850", 0x2BF850u, &rg::fn_sub_2BF850_002bf850, &rg::fn_sub_2BF850_002bf850__recomp, ""},
    {"sub_2BF880", 0x2BF880u, &rg::fn_sub_2BF880_002bf880, &rg::fn_sub_2BF880_002bf880__recomp, ""},
    {"sub_2BF8B0", 0x2BF8B0u, &rg::fn_sub_2BF8B0_002bf8b0, &rg::fn_sub_2BF8B0_002bf8b0__recomp, ""},
    {"sub_2BF8E0", 0x2BF8E0u, &rg::fn_sub_2BF8E0_002bf8e0, &rg::fn_sub_2BF8E0_002bf8e0__recomp, ""},
    {"sub_2BF910", 0x2BF910u, &rg::fn_sub_2BF910_002bf910, &rg::fn_sub_2BF910_002bf910__recomp, ""},
    {"sub_2BF940", 0x2BF940u, &rg::fn_sub_2BF940_002bf940, &rg::fn_sub_2BF940_002bf940__recomp, ""},
    {"sub_2D0D70", 0x2D0D70u, &rg::fn_sub_2D0D70_002d0d70, &rg::fn_sub_2D0D70_002d0d70__recomp, ""},
    {"sub_2D0DE0", 0x2D0DE0u, &rg::fn_sub_2D0DE0_002d0de0, &rg::fn_sub_2D0DE0_002d0de0__recomp, ""},
    {"sub_2D1030", 0x2D1030u, &rg::fn_sub_2D1030_002d1030, &rg::fn_sub_2D1030_002d1030__recomp, ""},
    {"sub_2D10F0", 0x2D10F0u, &rg::fn_sub_2D10F0_002d10f0, &rg::fn_sub_2D10F0_002d10f0__recomp, ""},
    {"sub_2D1180", 0x2D1180u, &rg::fn_sub_2D1180_002d1180, &rg::fn_sub_2D1180_002d1180__recomp, ""},
    {"sub_2D19B0", 0x2D19B0u, &rg::fn_sub_2D19B0_002d19b0, &rg::fn_sub_2D19B0_002d19b0__recomp, ""},
    {"sub_2D21E0", 0x2D21E0u, &rg::fn_sub_2D21E0_002d21e0, &rg::fn_sub_2D21E0_002d21e0__recomp, "o"},
    {"sub_2D5CF0", 0x2D5CF0u, &rg::fn_sub_2D5CF0_002d5cf0, &rg::fn_sub_2D5CF0_002d5cf0__recomp, "U"},
    {"sub_2D7890", 0x2D7890u, &rg::fn_sub_2D7890_002d7890, &rg::fn_sub_2D7890_002d7890__recomp, "Ab"},
    {"sub_2DC670", 0x2DC670u, &rg::fn_sub_2DC670_002dc670, &rg::fn_sub_2DC670_002dc670__recomp, "A"},
    {"sub_2DC830", 0x2DC830u, &rg::fn_sub_2DC830_002dc830, &rg::fn_sub_2DC830_002dc830__recomp, "A"},
    {"sub_2DCA60", 0x2DCA60u, &rg::fn_sub_2DCA60_002dca60, &rg::fn_sub_2DCA60_002dca60__recomp, "A"},
    {"sub_2F87E0", 0x2F87E0u, &rg::fn_sub_2F87E0_002f87e0, &rg::fn_sub_2F87E0_002f87e0__recomp, "m"},
    {"sub_2F8810", 0x2F8810u, &rg::fn_sub_2F8810_002f8810, &rg::fn_sub_2F8810_002f8810__recomp, ""},
    {"sub_2FD160", 0x2FD160u, &rg::fn_sub_2FD160_002fd160, &rg::fn_sub_2FD160_002fd160__recomp, "A"},
    {"sub_2FDDB0", 0x2FDDB0u, &rg::fn_sub_2FDDB0_002fddb0, &rg::fn_sub_2FDDB0_002fddb0__recomp, "Uo"},
    {"sub_2ADC30", 0x2ADC30u, &rg::fn_sub_2ADC30_002adc30, &rg::fn_sub_2ADC30_002adc30__recomp, "Q"},
    {"sub_2ADC80", 0x2ADC80u, &rg::fn_sub_2ADC80_002adc80, &rg::fn_sub_2ADC80_002adc80__recomp, "Q"},
    {"sub_2ADCD0", 0x2ADCD0u, &rg::fn_sub_2ADCD0_002adcd0, &rg::fn_sub_2ADCD0_002adcd0__recomp, "Q"},
    {"sub_2B2880", 0x2B2880u, &rg::fn_sub_2B2880_002b2880, &rg::fn_sub_2B2880_002b2880__recomp, "Q"},
    {"sub_2B32C0", 0x2B32C0u, &rg::fn_sub_2B32C0_002b32c0, &rg::fn_sub_2B32C0_002b32c0__recomp, "Q"},
    {"sub_2E4A30", 0x2E4A30u, &rg::fn_sub_2E4A30_002e4a30, &rg::fn_sub_2E4A30_002e4a30__recomp, "Q"},
    {"sub_2E5040", 0x2E5040u, &rg::fn_sub_2E5040_002e5040, &rg::fn_sub_2E5040_002e5040__recomp, "Q"},
    {"sub_2E71C0", 0x2E71C0u, &rg::fn_sub_2E71C0_002e71c0, &rg::fn_sub_2E71C0_002e71c0__recomp, "Q"},
    {"sub_2E7320", 0x2E7320u, &rg::fn_sub_2E7320_002e7320, &rg::fn_sub_2E7320_002e7320__recomp, "Q"},
    {"sub_2E7680", 0x2E7680u, &rg::fn_sub_2E7680_002e7680, &rg::fn_sub_2E7680_002e7680__recomp, "Q"},
    {"sub_2E76A0", 0x2E76A0u, &rg::fn_sub_2E76A0_002e76a0, &rg::fn_sub_2E76A0_002e76a0__recomp, "Q"},
    {"sub_2E7710", 0x2E7710u, &rg::fn_sub_2E7710_002e7710, &rg::fn_sub_2E7710_002e7710__recomp, "Q"},
    {"sub_2E77C0", 0x2E77C0u, &rg::fn_sub_2E77C0_002e77c0, &rg::fn_sub_2E77C0_002e77c0__recomp, "Q"},
    {"sub_2E7810", 0x2E7810u, &rg::fn_sub_2E7810_002e7810, &rg::fn_sub_2E7810_002e7810__recomp, "Q"},
    {"sub_2E7880", 0x2E7880u, &rg::fn_sub_2E7880_002e7880, &rg::fn_sub_2E7880_002e7880__recomp, "Q"},
    {"sub_2E87B0", 0x2E87B0u, &rg::fn_sub_2E87B0_002e87b0, &rg::fn_sub_2E87B0_002e87b0__recomp, "Q"},
    {"sub_2E8C80", 0x2E8C80u, &rg::fn_sub_2E8C80_002e8c80, &rg::fn_sub_2E8C80_002e8c80__recomp, "Q"},
    {"sub_2E8C90", 0x2E8C90u, &rg::fn_sub_2E8C90_002e8c90, &rg::fn_sub_2E8C90_002e8c90__recomp, "Q"},
    {"sub_2E8D20", 0x2E8D20u, &rg::fn_sub_2E8D20_002e8d20, &rg::fn_sub_2E8D20_002e8d20__recomp, "Q"},
    {"sub_2E8D40", 0x2E8D40u, &rg::fn_sub_2E8D40_002e8d40, &rg::fn_sub_2E8D40_002e8d40__recomp, "Q"},
    {"sub_2E8D70", 0x2E8D70u, &rg::fn_sub_2E8D70_002e8d70, &rg::fn_sub_2E8D70_002e8d70__recomp, "Q"},
    {"sub_2E9060", 0x2E9060u, &rg::fn_sub_2E9060_002e9060, &rg::fn_sub_2E9060_002e9060__recomp, "Q"},
};

const Snap kSnaps[] = {{"b_5800", 16}, {"battle_ref_6150", 2}, {"b_6150", 2}, {"b_6300", 1}, {"climb_ref_17000", 1}};

}  // namespace

TEST_CASE("game(battle7 misc): every body equals its recompiled body on random worlds") {
    run_random(kCases, std::size(kCases), 24, "battle7 misc");
}

TEST_CASE("game(battle7 misc): every body on the battle snapshots, perturbed") {
    run_snapshots(kCases, std::size(kCases), kSnaps, std::size(kSnaps), "battle7 misc");
}

TEST_CASE("game(battle7 misc): the action, damage and camera rules") {
    auto m = new_machine();
    if (!m) return;
    int checks = 0;
    auto v0 = [&](Fn f, u64 a0 = 0, u64 a1 = 0, u64 a2 = 0, u64 a3 = 0) { return v0_of(solo(*m, f, {a0, a1, a2, a3})); };
    const std::vector<u8> snap = read_snapshot("b_5800");
    if (snap.empty()) {
        MESSAGE("SKIP: extracted/_ours/b_5800/eeMemory.bin not found");
        return;
    }
    auto load = [&]() {
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        write_rw_slots(*m);
        return objects_of(*m);
    };
    std::mt19937 rng{0xB7C3u};
    // (1) a unit's cell position: x = 25 * cell x - 1750, y = the unit's y, z = 25 * cell z - 1750 + 200 + radius *
    //     scale (the R5900 FPU rounds toward zero: z within a relative 1e-6)
    {
        const Objects o = load();
        const u32 out = kScratch + 0x30000u;
        for (u32 u : o.units)
            for (int k = 0; k < 12; ++k) {
                const s16 cx = static_cast<s16>(static_cast<int>(rng() % 141) - 70);
                const s16 cz = static_cast<s16>(static_cast<int>(rng() % 141) - 70);
                st16(*m, u + b4::unit4::kCellX, static_cast<u16>(cx));
                st16(*m, u + b4::unit4::kCellZ, static_cast<u16>(cz));
                v0(&rg::fn_sub_2FDDB0_002fddb0, sx(u), sx(out));
                float x, y, z, r, s, uy;
                std::memcpy(&x, m->at(out), 4);
                std::memcpy(&y, m->at(out + 4), 4);
                std::memcpy(&z, m->at(out + 8), 4);
                std::memcpy(&r, m->at(u + b3::unit::kRadius), 4);
                std::memcpy(&s, m->at(u + b3::unit::kScale), 4);
                std::memcpy(&uy, m->at(u + b4::unit4::kPos + 4), 4);
                const double want_z = 25.0 * cz - 1750.0 + 200.0 + double(r) * double(s);
                INFO("unit " << hex64(u) << " cell " << cx << "," << cz);
                CHECK(x == static_cast<float>(25 * cx - 1750));
                CHECK(std::memcmp(&y, &uy, 4) == 0);
                CHECK(std::fabs(double(z) - want_z) <= 1e-6 * std::max(1.0, std::fabs(want_z)));
                checks += 3;
            }
    }
    // (2) kill / revive: a kill leaves HP 0, the dead status alone and the unit's died bit (0x1) without the revived
    //     bit (0x10); a revive sets HP 1 (not after skill 438 at +1120), clears the dead status and sets the revived bit
    for (int k = 0; k < 24; ++k) {
        const Objects o = load();
        if (o.acts.empty()) break;
        const u32 a = o.acts[rng() % o.acts.size()];
        const u32 u = ld32(*m, a + b3::act::kUnit), d = ld32(*m, u + b3::unit::kDat);
        const bool revive = rng() % 2 != 0;
        const bool s438 = rng() % 3 == 0;
        st16(*m, a + b5::act5::kReviveSkill, static_cast<u16>(s438 ? 438 : 1));
        const u16 hp0 = ld16(*m, d + b3::dat::kHp);
        v0(&rg::fn_sub_2D7890_002d7890, sx(a), revive ? 1 : 0);
        const u32 st = ld32(*m, d + b3::dat::kStatus), fl = ld32(*m, u + b3::unit::kFlags);
        INFO("action " << hex64(a) << (revive ? " revive" : " kill") << " skill438 " << s438);
        if (revive) {
            CHECK(ld16(*m, d + b3::dat::kHp) == (s438 ? hp0 : 1));
            CHECK((st & 0x80000u) == 0);
            CHECK((fl & 0x10u) != 0);
        } else {
            CHECK(ld16(*m, d + b3::dat::kHp) == 0);
            CHECK((st & 0xFFFFFFu) == 0x80000u);
            CHECK((fl & 0x1u) != 0);
            CHECK((fl & 0x10u) == 0);
        }
        checks += 3;
    }
    // (3) the poison damage of a turn (the ailment 128): a party unit loses max HP / 500 (in hundredths: -100 * max /
    //     500), an enemy by its enemy-table flags (0x400 / 0x800 / 0x1000 / 0x2000: 50 / 100 / 150 / 200) or -100 * max
    //     / 333; never more than leaves 1 HP (datCalcIsDead with the delta -> 1 - HP); no ailment, no damage
    for (int k = 0; k < 48; ++k) {
        const Objects o = load();
        if (o.acts.empty()) break;
        const u32 a = o.acts[rng() % o.acts.size()];
        const u32 u = ld32(*m, a + b3::act::kUnit), d = ld32(*m, u + b3::unit::kDat);
        static const u32 kSt[] = {0x80u, 0x80u, 0x80u, 0x1u, 0x0u};
        st32(*m, d + b3::dat::kStatus, kSt[rng() % std::size(kSt)]);
        const bool low = rng() % 4 == 0;
        const u16 hp = static_cast<u16>(low ? 1 + rng() % 3 : 50 + rng() % 300);
        st16(*m, d + b3::dat::kHp, hp);
        const u32 ail = static_cast<u32>(v0(&rg::fn_datCalcGetBadStatusNoDown_00300530, sx(d)));
        s32 want = 0;
        if (ail == 128) {
            const s32 maxhp = static_cast<u16>(v0(&rg::fn_datCalcGetMaxHp_002ffdf0, sx(d)));
            if (ld16(*m, d + b3::dat::kFlags) & 4) {
                const u16 f = ld16(*m, ld32(*m, 0x7CE410u) + 62u * ld16(*m, d + b3::dat::kId));
                want = (f & 0x400) ? -50 : (f & 0x800) ? -100 : (f & 0x1000) ? -150 : (f & 0x2000) ? -200
                                                                                 : static_cast<s16>(-100 * maxhp / 333);
            } else {
                want = static_cast<s16>(-100 * maxhp / 500);
            }
        }
        if (v0(&rg::fn_datCalcIsDead_0030b5a0, sx(d), sx(static_cast<u32>(want))) != 0)
            want = static_cast<s16>(1 - static_cast<s32>(static_cast<u16>(v0(&rg::fn_datCalcGetHp_002ffd70, sx(d)))));
        INFO("action " << hex64(a) << " ailment " << ail << " hp " << hp);
        CHECK(static_cast<s32>(static_cast<s16>(v0(&rg::fn_sub_2DC670_002dc670, sx(a)))) == want);
        ++checks;
    }
    // (4) encounter 428's hook: an active enemy action with the effect state 11 returns the boss work word (+2884)
    for (int k = 0; k < 48; ++k) {
        const Objects o = load();
        if (o.acts.empty()) break;
        perturb(*m, o, rng);
        const u32 a = o.acts[rng() % o.acts.size()];
        const bool is428 = rng() % 2 != 0;
        st16(*m, ld32(*m, o.btl + b3::gbtl::kSetupEnemies) + 8, static_cast<u16>(is428 ? 428 : 427));
        st32(*m, o.btl + b3::gbtl::kBossWork0, 0x5A5Au);
        const u32 u = ld32(*m, a + b3::act::kUnit);
        const bool ok = is428 && (ld16(*m, a + b3::act::kFlags2) & 1) && ld8(*m, u + b3::unit::kSide) == 1 &&
                        static_cast<s8>(v0(&rg::fn_datCalcGetEffectState_00301750, sx(ld32(*m, u + b3::unit::kDat)), 11)) > 0;
        CHECK(v0(&rg::fn_sub_2FD160_002fd160, sx(a)) == (ok ? 0x5A5Au : 0u));
        ++checks;
    }
    // (5) the boss camera start: remembers the action's first target (gBtl +2932)
    for (int k = 0; k < 16; ++k) {
        const Objects o = load();
        if (o.acts.empty()) break;
        const u32 a = o.acts[rng() % o.acts.size()];
        const u32 shot = kScratch + 0x31000u;
        std::memset(m->at(shot), 0, 320);
        st32(*m, shot + b7::shot::kAction, a);
        v0(&rg::fn_sub_2E76A0_002e76a0, sx(shot));
        CHECK(ld32(*m, o.btl + b7::gbtl7::kCamLastTarget) == ld32(*m, a + b3::act::kTargets));
        ++checks;
    }
    MESSAGE("battle7 misc rules: " << checks << " checks");
}

#else

TEST_CASE("game(battle7 misc): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
