// Phase 5 pair tests for slice battle8 (game/src/battle/battle8.cpp): the boss fights' camera shots, placements,
// opening shots, boss talks and event packets. Every body against its recompiled body (__recomp) on identical machines
// with battle7_pairs.h's machinery (the whole register file and cycles at every check point and at the return / stop,
// all 32 MiB of RAM, the scratchpad, the BIOS window, the bus log, the stand-in call log):
//   * random worlds (the p3fes_handgen skeleton's);
//   * the battle snapshots, perturbed by battle7_pairs.h's perturb() and by the boss branches these bodies take: enemy
//     ids 256..295 (the talk / placement / hook ids), party ids 1 / 2 / 5 / 7, the camera states the shots test, the
//     gBtl boss words (+2884 / +2888 units, +2896 / +2900 / +2902 / +2904 / +2912), action flags2 bits 0 / 3 / 4 and
//     unit flags 0x8 / 0x10;
//   * documented-rule checks against host models on a fake battle (below).
#include "battle7_pairs.h"

#include "p3fes/game/battle8.h"

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::b7t;

#define B8_FN(name, lo) \
    void fn_##name##_##lo(EEContext&); \
    void fn_##name##_##lo##__recomp(EEContext&);
namespace p3fes::recomp_gen {
B8_FN(sub_2E4A40, 002e4a40) B8_FN(sub_2E4F50, 002e4f50) B8_FN(sub_2E5060, 002e5060) B8_FN(sub_2E58A0, 002e58a0)
B8_FN(sub_2E6130, 002e6130) B8_FN(sub_2E7210, 002e7210) B8_FN(sub_2E7330, 002e7330) B8_FN(sub_2E7890, 002e7890)
B8_FN(sub_2E7DB0, 002e7db0) B8_FN(sub_2E82B0, 002e82b0) B8_FN(sub_2E8820, 002e8820) B8_FN(sub_2E8A40, 002e8a40)
B8_FN(sub_2E8E20, 002e8e20) B8_FN(sub_2E8F40, 002e8f40) B8_FN(sub_2E9170, 002e9170) B8_FN(sub_2E92C0, 002e92c0)
B8_FN(sub_2E9450, 002e9450) B8_FN(sub_2E95F0, 002e95f0) B8_FN(sub_2E9950, 002e9950) B8_FN(sub_2E9AC0, 002e9ac0)
B8_FN(sub_2E9C20, 002e9c20) B8_FN(sub_2E9F10, 002e9f10) B8_FN(sub_2EA060, 002ea060) B8_FN(sub_2EA210, 002ea210)
B8_FN(sub_2EA400, 002ea400) B8_FN(sub_2EA590, 002ea590) B8_FN(sub_2EA780, 002ea780) B8_FN(sub_2EA860, 002ea860)
B8_FN(sub_2EAB70, 002eab70) B8_FN(sub_2EABB0, 002eabb0) B8_FN(sub_2EABF0, 002eabf0) B8_FN(sub_2EB250, 002eb250)
B8_FN(sub_2EB2C0, 002eb2c0) B8_FN(sub_2EB9E0, 002eb9e0) B8_FN(sub_2EBA50, 002eba50) B8_FN(sub_2EBEC0, 002ebec0)
B8_FN(sub_2EC000, 002ec000) B8_FN(sub_2EC2C0, 002ec2c0) B8_FN(sub_2EC5C0, 002ec5c0) B8_FN(sub_2EC790, 002ec790)
B8_FN(sub_2EC990, 002ec990) B8_FN(sub_2ECB30, 002ecb30) B8_FN(sub_2ECBE0, 002ecbe0) B8_FN(sub_2ECC20, 002ecc20)
B8_FN(sub_2ECC60, 002ecc60) B8_FN(sub_2ECF80, 002ecf80) B8_FN(sub_2ED360, 002ed360) B8_FN(sub_2EE640, 002ee640)
B8_FN(sub_2EEA10, 002eea10) B8_FN(sub_2EEB70, 002eeb70) B8_FN(sub_2EEC60, 002eec60) B8_FN(sub_2EF000, 002ef000)
B8_FN(sub_2EF250, 002ef250) B8_FN(sub_2EF360, 002ef360) B8_FN(sub_2EF5A0, 002ef5a0) B8_FN(sub_2EF670, 002ef670)
B8_FN(sub_2EF7E0, 002ef7e0) B8_FN(sub_2EFC90, 002efc90) B8_FN(sub_2EFCD0, 002efcd0) B8_FN(sub_2EFD20, 002efd20)
B8_FN(sub_2EFDB0, 002efdb0) B8_FN(sub_2EFE50, 002efe50)
}  // namespace p3fes::recomp_gen
#undef B8_FN

namespace {

namespace rg = p3fes::recomp_gen;
namespace b8 = p3fes::game::b8;

#define B8_CASE(name, lo, kinds) {#name, 0x##lo##u, &rg::fn_##name##_##lo, &rg::fn_##name##_##lo##__recomp, kinds}
// Argument kinds (battle7_pairs.h): Q a camera shot, A a btlAction, U a btlUnit, o an out block, m 0..15, "" none.
const Case kCases[] = {
    B8_CASE(sub_2E4A40, 002e4a40, "Q"), B8_CASE(sub_2E4F50, 002e4f50, "Q"), B8_CASE(sub_2E5060, 002e5060, "Q"),
    B8_CASE(sub_2E58A0, 002e58a0, "Q"), B8_CASE(sub_2E6130, 002e6130, "UUoo"), B8_CASE(sub_2E7210, 002e7210, "Q"),
    B8_CASE(sub_2E7330, 002e7330, "Q"), B8_CASE(sub_2E7890, 002e7890, "Q"), B8_CASE(sub_2E7DB0, 002e7db0, "Q"),
    B8_CASE(sub_2E82B0, 002e82b0, "Q"), B8_CASE(sub_2E8820, 002e8820, "Q"), B8_CASE(sub_2E8A40, 002e8a40, "Q"),
    B8_CASE(sub_2E8E20, 002e8e20, ""), B8_CASE(sub_2E8F40, 002e8f40, ""), B8_CASE(sub_2E9170, 002e9170, ""),
    B8_CASE(sub_2E92C0, 002e92c0, ""), B8_CASE(sub_2E9450, 002e9450, ""), B8_CASE(sub_2E95F0, 002e95f0, ""),
    B8_CASE(sub_2E9950, 002e9950, ""), B8_CASE(sub_2E9AC0, 002e9ac0, ""), B8_CASE(sub_2E9C20, 002e9c20, "A"),
    B8_CASE(sub_2E9F10, 002e9f10, "A"), B8_CASE(sub_2EA060, 002ea060, ""), B8_CASE(sub_2EA210, 002ea210, ""),
    B8_CASE(sub_2EA400, 002ea400, ""), B8_CASE(sub_2EA590, 002ea590, ""), B8_CASE(sub_2EA780, 002ea780, "A"),
    B8_CASE(sub_2EA860, 002ea860, ""), B8_CASE(sub_2EAB70, 002eab70, ""), B8_CASE(sub_2EABB0, 002eabb0, ""),
    B8_CASE(sub_2EABF0, 002eabf0, ""), B8_CASE(sub_2EB250, 002eb250, "A"), B8_CASE(sub_2EB2C0, 002eb2c0, ""),
    B8_CASE(sub_2EB9E0, 002eb9e0, "A"), B8_CASE(sub_2EBA50, 002eba50, "A"), B8_CASE(sub_2EBEC0, 002ebec0, "A"),
    B8_CASE(sub_2EC000, 002ec000, ""), B8_CASE(sub_2EC2C0, 002ec2c0, ""), B8_CASE(sub_2EC5C0, 002ec5c0, ""),
    B8_CASE(sub_2EC790, 002ec790, ""), B8_CASE(sub_2EC990, 002ec990, "U"), B8_CASE(sub_2ECB30, 002ecb30, "Am"),
    B8_CASE(sub_2ECBE0, 002ecbe0, "U"), B8_CASE(sub_2ECC20, 002ecc20, "U"), B8_CASE(sub_2ECC60, 002ecc60, "oo"),
    B8_CASE(sub_2ECF80, 002ecf80, "A"), B8_CASE(sub_2ED360, 002ed360, "A"), B8_CASE(sub_2EE640, 002ee640, "A"),
    B8_CASE(sub_2EEA10, 002eea10, "A"), B8_CASE(sub_2EEB70, 002eeb70, "A"), B8_CASE(sub_2EEC60, 002eec60, ""),
    B8_CASE(sub_2EF000, 002ef000, "A"), B8_CASE(sub_2EF250, 002ef250, "A"), B8_CASE(sub_2EF360, 002ef360, ""),
    B8_CASE(sub_2EF5A0, 002ef5a0, ""), B8_CASE(sub_2EF670, 002ef670, ""), B8_CASE(sub_2EF7E0, 002ef7e0, ""),
    B8_CASE(sub_2EFC90, 002efc90, "A"), B8_CASE(sub_2EFCD0, 002efcd0, "A"), B8_CASE(sub_2EFD20, 002efd20, "U"),
    B8_CASE(sub_2EFDB0, 002efdb0, "U"), B8_CASE(sub_2EFE50, 002efe50, "A"),
};
#undef B8_CASE

const Snap kSnaps[] = {{"b_5800", 12}, {"battle_ref_6150", 2}, {"b_6300", 1}, {"climb_ref_17000", 1}};

// The boss ids the bodies branch on (talks, placements, hooks, the event tables 226..230, the child motions 0xE9..).
const u16 kBossIds[] = {256, 257, 258, 259, 260, 261, 262, 263, 265, 266, 267, 268, 269, 276, 277, 281, 295,
                        226, 227, 228, 229, 230, 0xE9, 0xF0, 272};
const u16 kPartyIds[] = {1, 2, 5, 7, 3};
const u16 kCamStates[] = {0, 2, 9, 18, 28, 29, 31, 34};

void perturb_boss(Machine& m, const Objects& o, std::mt19937& rng) {
    if (!o.btl) return;
    for (u32 u : o.units) {
        if (!chance(rng, 50)) continue;
        const bool enemy = ld8(m, u + b3::unit::kSide) != 0;
        const u16 id = enemy ? kBossIds[rng() % std::size(kBossIds)] : kPartyIds[rng() % std::size(kPartyIds)];
        st16(m, u + b3::unit::kId, id);
        if (chance(rng, 20)) st32(m, u + b3::unit::kFlags, ld32(m, u + b3::unit::kFlags) ^ (chance(rng, 50) ? 0x10u : 0x8u));
    }
    if (chance(rng, 50)) st16(m, o.btl + b3::gbtl::kCameraState, kCamStates[rng() % std::size(kCamStates)]);
    if (chance(rng, 40)) st32(m, o.btl + b3::gbtl::kBossWork0, pick(o.units, rng, 0u));
    if (chance(rng, 40)) st32(m, o.btl + b3::gbtl::kBossWork1, pick(o.units, rng, 0u));
    if (chance(rng, 30)) st32(m, o.btl + b3::gbtl::kBossWork3, rng() % 2);
    if (chance(rng, 30)) st16(m, o.btl + b3::gbtl::kBossWork4, static_cast<u16>(rng() % 2));
    if (chance(rng, 40)) st16(m, o.btl + b8::gbtl8::kEvState, static_cast<u16>(rng() % 5));
    if (chance(rng, 40)) st16(m, o.btl + b8::gbtl8::kEvState2, static_cast<u16>(rng() % 5));
    if (chance(rng, 30)) st16(m, o.btl + b8::gbtl8::kEvPick, static_cast<u16>(chance(rng, 50) ? 0xFFFFu : rng() % 0x1D0));
    if (chance(rng, 30)) stf(m, o.btl + b8::gbtl8::kEvTimer, static_cast<float>(rng() % 4));
    for (u32 a : o.acts)
        if (chance(rng, 30)) {
            static const u16 kBits[] = {0x1u, 0x8u, 0x10u};
            st16(m, a + b3::act::kFlags2, static_cast<u16>(ld16(m, a + b3::act::kFlags2) ^ kBits[rng() % 3]));
        }
}

// battle7_pairs.h's stand-ins plus recorders for the two not-emitted callees the boss shots meet first (both bodies
// meet the same recorder; its log is compared): sub_2F8A40 (sub_2E7330's gate, 1 = take the shot) and sub_2F88C0
// (sub_2E8820 / sub_2E8A40's boss-row index, 0).
void b8_setup(StandInWorld& w) {
    b7_setup(w);
    w.si.install_recorder(0x2F8A40u, "rec_2f8a40", 1, 4);
    w.si.install_recorder(0x2F88C0u, "rec_2f88c0", 0, 4);
}

// pair_base (battle7_pairs.h) on b8_setup's stand-in worlds: the same checks.
hgp::Run pair_b8(Machine& m, BaseRange& ram, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const HwCheck& hw) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    b8_setup(*wh);
    b8_setup(*wr);
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    ram.begin();
    hgp::Run h = hgp::run_one(m, &thunk0, args, seed, hw);
    std::vector<u8> bios_h;
    if (!hgp::bios_clean(m)) {
        bios_h.assign(m.mem.bios(), m.mem.bios() + EEMemory::kBiosSize);
        std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    }
    ram.between();
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    hgp::Run r = hgp::run_one(m, &thunk1, args, seed, hw);
    const bool bios_r = !hgp::bios_clean(m);
    INFO(std::string(what) << " a0=" << hex64(args[0]) << " a1=" << hex64(args[1]) << " seed=" << seed
                           << (r.stopped ? " (recomp stopped: " + r.what + " at " + hex64(r.stop_pc) + ")" : std::string())
                           << (h.stopped ? " (hand stopped: " + h.what + " at " + hex64(h.stop_pc) + ")" : std::string()));
    CHECK(bios_r == !bios_h.empty());
    if (bios_r) std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    CHECK(h.stopped == r.stopped);
    CHECK(h.stop_pc == r.stop_pc);
    CHECK(h.what == r.what);
    CHECK(h.syscalls == r.syscalls);
    CHECK(h.snaps.size() == r.snaps.size());
    const std::size_t n = std::min(h.snaps.size(), r.snaps.size());
    for (std::size_t i = 0; i < n; ++i) {
        const std::string d = hgp::diff(h.snaps[i], r.snaps[i]);
        if (!d.empty()) {
            INFO("check point " << i << " of " << n << ": " << d);
            CHECK(false);
            break;
        }
    }
    {
        const std::string d = hgp::diff(h.end, r.end);
        INFO((r.stopped ? "at the stop: " : "at the return: ") << d);
        CHECK(d.empty());
    }
    if (const std::size_t first = ram.first_difference(); first != ram.size()) {
        INFO("main RAM: first differing byte at " << hex64(first) << " hand " << unsigned(ram.first_body_byte(first)) << " recomp "
                                                  << unsigned(m.mem.main_ram()[first]));
        CHECK(false);
    }
    CHECK(h.spr == r.spr);
    CHECK(h.bus.size() == r.bus.size());
    for (std::size_t i = 0; i < std::min(h.bus.size(), r.bus.size()); ++i) {
        const auto &x = h.bus[i], &y = r.bus[i];
        if (x.write != y.write || x.bits != y.bits || x.pa != y.pa || x.lo != y.lo || x.hi != y.hi) {
            INFO("bus access " << i << " differs");
            CHECK(false);
            break;
        }
    }
    CHECK(h.vu_control == r.vu_control);
    expect_same_log(wh->si, wr->si, what);
    return r;
}

// run_snapshots with the boss perturbation and b8_setup's recorders (same counts and messages).
void run_boss_snapshots(const char* label) {
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int pairs = 0, stops = 0, used = 0;
    std::map<u32, std::string> missing;
    for (const Snap& sn : kSnaps) {
        const u32 reps = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : sn.reps;
        const std::vector<u8> snap = read_snapshot(sn.dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << std::string(sn.dir) << "/eeMemory.bin not found");
            continue;
        }
        auto m = new_machine();
        if (!m) return;
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        write_rw_slots(*m);
        const Objects o = objects_of(*m);
        ++used;
        BaseRange base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            for (u32 rep = 0; rep < reps; ++rep) {
                if (trace) std::fprintf(stderr, "%s %s rep %u\n", sn.dir, c.name, rep);
                std::mt19937 rng{rep * 104729u + c.addr + static_cast<u32>(used) * 7u + 0xB8u};
                perturb(*m, o, rng);
                perturb_boss(*m, o, rng);
                Args a{};
                HwCheck hw;
                args_for(*m, c, o, rng, a, hw);
                const u32 seed = rng();
                const hgp::Run r = pair_b8(*m, base, c.hand, c.recomp, a, seed, c.name, hw);
                ++pairs;
                if (r.stopped) {
                    ++stops;
                    if (r.what.rfind("missing_function", 0) == 0 && missing[r.stop_pc].find(c.name) == std::string::npos)
                        missing[r.stop_pc] += std::string(" ") + c.name;
                }
                base.restore();
            }
        }
    }
    for (const auto& [pc, who] : missing) MESSAGE("stopped at the not-emitted " << hex64(pc) << ":" << who.substr(0, 200));
    MESSAGE(std::string(label) << " boss snapshots: " << pairs << " pairs on " << used << " snapshot(s), " << stops
                               << " ended at a compared stop");
}

// Links units into gBtl's side-1 tail list (+344, walked through +2612 prev) of a fake battle.
void link_enemies(Machine& m, const Fake& f, std::initializer_list<u32> units) {
    u32 prev = 0;
    for (u32 u : units) {
        st8(m, u + b3::unit::kSide, 1);
        st32(m, u + b3::unit::kPrev, prev);
        prev = u;
    }
    st32(m, f.btl + b8::gbtl8::kUnitTail1, prev);
}

}  // namespace

TEST_CASE("game(battle8): every body equals its recompiled body on random worlds") {
    run_random(kCases, std::size(kCases), 24, "battle8");
}

TEST_CASE("game(battle8): every body on the battle snapshots, perturbed") {
    run_snapshots(kCases, std::size(kCases), kSnaps, std::size(kSnaps), "battle8");
}

TEST_CASE("game(battle8): every body on the battle snapshots with the boss ids and words") {
    run_boss_snapshots("battle8");
}

TEST_CASE("game(battle8): the call packets, the end checks, the fade and the cleanup rules") {
    auto m = new_machine();
    if (!m) return;
    int checks = 0;
    std::mt19937 rng{0xB8C3u};
    // (1) the call packets sub_2ECBE0 / sub_2ECC20 set / clear gBtl +2896, clear / set flags2 bit 3 of the unit's action
    //     (the first of gBtl's list with that unit) and return 1
    for (int k = 0; k < 8; ++k) {
        const Fake f = fake_battle(*m, 1, 3);
        const bool set = k % 2 == 0;
        const u32 i = static_cast<u32>(k / 2) % 3;
        st32(*m, f.btl + b3::gbtl::kBossWork3, set ? 0u : 1u);
        const hgp::Run r = solo(*m, set ? &rg::fn_sub_2ECBE0_002ecbe0 : &rg::fn_sub_2ECC20_002ecc20, {sx(f.unit[i]), 0, 0, 0});
        if (r.stopped) continue;
        CHECK(v0_of(r) == 1);
        CHECK(ld32(*m, f.btl + b3::gbtl::kBossWork3) == (set ? 1u : 0u));
        for (u32 j = 0; j < 3; ++j) CHECK(ld16(*m, f.act[j] + b3::act::kFlags2) == ((j == i && set) ? 0x1u : 0x9u));
        checks += 5;
    }
    // (2) the end checks sub_2EB250 / sub_2EB9E0: with no packet queued for the owner they clear gBtl flag 0x80000
    //     (and nothing else) and return 0
    for (int k = 0; k < 8; ++k) {
        const Fake f = fake_battle(*m, 1, 1);
        const u32 flags = (rng() & 0x7FFFFFFFu) | 0x80000u;
        st32(*m, f.btl + b3::gbtl::kFlags, flags);
        const u32 data = kScratch + 0x20000u;
        st32(*m, data, rng());
        st32(*m, data + 4, 0);
        const hgp::Run r = solo(*m, k % 2 ? &rg::fn_sub_2EB9E0_002eb9e0 : &rg::fn_sub_2EB250_002eb250, {sx(data), 0, 0, 0});
        if (r.stopped) continue;
        CHECK(v0_of(r) == 0);
        CHECK(ld32(*m, f.btl + b3::gbtl::kFlags) == (flags & ~0x80000u));
        checks += 2;
    }
    // (3) sub_2EC990 on enemy 265 with a model and gBtl +2896 clear: the model's +216 bit 0x80 is cleared and the
    //     alpha (+67) rises by 8, saturating at 255 (from 0xF7 up); 255 stays without the colour-changed flag
    for (int k = 0; k < 24; ++k) {
        const Fake f = fake_battle(*m, 1, 1);
        const u32 u = f.unit[0], model = kScratch + 0x18000u;
        std::memset(m->at(model), 0, 0x800);
        st16(*m, model + 216, 0x80u | 0x3u);
        st8(*m, u + b3::unit::kSide, 1);
        st16(*m, u + b3::unit::kId, 265);
        st32(*m, u + b3::unit::kModelFlags, 0x2u);
        st32(*m, u + b3::unit::kModel, model);
        const u8 alpha = k == 0 ? 255 : k == 1 ? 0xF7 : static_cast<u8>(rng() % 256);
        st8(*m, u + 67, alpha);
        const hgp::Run r = solo(*m, &rg::fn_sub_2EC990_002ec990, {sx(u), 0, 0, 0});
        if (r.stopped) continue;
        const u8 want = alpha == 255 ? 255 : alpha >= 0xF7 ? 255 : static_cast<u8>(alpha + 8);
        INFO("alpha " << unsigned(alpha));
        CHECK(ld16(*m, model + 216) == 0x3u);
        CHECK(ld8(*m, u + 67) == want);
        CHECK(((ld32(*m, u + b3::unit::kModelFlags) & 0x4u) != 0) == (alpha != 255));
        checks += 3;
    }
    // (4) the cleanup sub_2EF5A0: enemy 295 clears gBtl +2908, 281 clears +2904; both zero their model's +1053
    {
        const Fake f = fake_battle(*m, 1, 2);
        const u32 m0 = kScratch + 0x18000u, m1 = kScratch + 0x18800u;
        std::memset(m->at(m0), 0x5A, 0x800);
        std::memset(m->at(m1), 0x5A, 0x800);
        st16(*m, f.unit[0] + b3::unit::kId, 295);
        st16(*m, f.unit[1] + b3::unit::kId, 281);
        st32(*m, f.unit[0] + b3::unit::kModel, m0);
        st32(*m, f.unit[1] + b3::unit::kModel, m1);
        link_enemies(*m, f, {f.unit[0], f.unit[1]});
        st32(*m, f.btl + b8::gbtl8::kEvTimer, 0x3F800000u);
        st16(*m, f.btl + b8::gbtl8::kEvState2, 3);
        const hgp::Run r = solo(*m, &rg::fn_sub_2EF5A0_002ef5a0, {0, 0, 0, 0});
        if (!r.stopped) {
            CHECK(ld32(*m, f.btl + b8::gbtl8::kEvTimer) == 0);
            CHECK(ld32(*m, f.btl + b8::gbtl8::kEvState2) == 0);
            CHECK(ld8(*m, m0 + 1053) == 0);
            CHECK(ld8(*m, m1 + 1053) == 0);
            CHECK(ld8(*m, m0 + 1052) == 0x5A);
            checks += 5;
        }
    }
    MESSAGE("battle8 rule checks: " << checks);
    CHECK(checks > 0);
}

#else

TEST_CASE("game(battle8): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
