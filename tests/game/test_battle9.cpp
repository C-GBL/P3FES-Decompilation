// Phase 5 pair tests for slice battle9 (game/src/battle/battle9.cpp): the boss-encounter scripts -- the encounter
// dispatch hooks, the formations, the unit inits, the scenes and their done callbacks, the camera shots. Every body
// against its recompiled body (__recomp) on identical machines (battle7_pairs.h: the whole register file and cycles at
// every check point and at the return / stop, all 32 MiB of RAM with the dead stack, the scratchpad, the BIOS window,
// the bus log and the stand-in call log):
//   * random worlds (the p3fes_handgen skeleton's);
//   * the replay snapshots (b_5800: a live battle; climb_ref_17000 / dorm_replay_4900: no battle, the null paths),
//     perturbed by battle7's rules plus the boss ones below -- the encounter (416..436, 456 and plain ones), the boss
//     enemy ids, the boss work words (gBtl +2884 .. +2912: listed actions, the phase counter, the copy counts, the fade
//     timers), the actions' skill (343), target lists and summon ids;
//   * documented-rule checks against host models (the boss-unit and turn queries, a formation, the copy pick of
//     encounter 432, its unit init, the packet-owner query of the done callbacks).
#include "battle7_pairs.h"

#include "p3fes/game/battle9.h"

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::b7t;

namespace b9 = p3fes::game::b9;
namespace bcore = p3fes::game::bcore;

namespace p3fes::recomp_gen {
#define P3FES_B9_PAIR(fn) void fn(EEContext&); void fn##__recomp(EEContext&);
P3FES_B9_PAIR(fn_sub_2F0580_002f0580)
P3FES_B9_PAIR(fn_sub_2F05F0_002f05f0)
P3FES_B9_PAIR(fn_sub_2F0E30_002f0e30)
P3FES_B9_PAIR(fn_sub_2F0EA0_002f0ea0)
P3FES_B9_PAIR(fn_sub_2F14A0_002f14a0)
P3FES_B9_PAIR(fn_sub_2F1680_002f1680)
P3FES_B9_PAIR(fn_sub_2F1810_002f1810)
P3FES_B9_PAIR(fn_sub_2F19D0_002f19d0)
P3FES_B9_PAIR(fn_sub_2F1D40_002f1d40)
P3FES_B9_PAIR(fn_sub_2F1F00_002f1f00)
P3FES_B9_PAIR(fn_sub_2F2090_002f2090)
P3FES_B9_PAIR(fn_sub_2F2250_002f2250)
P3FES_B9_PAIR(fn_sub_2F2450_002f2450)
P3FES_B9_PAIR(fn_sub_2F2490_002f2490)
P3FES_B9_PAIR(fn_sub_2F2550_002f2550)
P3FES_B9_PAIR(fn_sub_2F2840_002f2840)
P3FES_B9_PAIR(fn_sub_2F2890_002f2890)
P3FES_B9_PAIR(fn_sub_2F2B40_002f2b40)
P3FES_B9_PAIR(fn_sub_2F2B90_002f2b90)
P3FES_B9_PAIR(fn_sub_2F3190_002f3190)
P3FES_B9_PAIR(fn_sub_2F3320_002f3320)
P3FES_B9_PAIR(fn_sub_2F3520_002f3520)
P3FES_B9_PAIR(fn_sub_2F3670_002f3670)
P3FES_B9_PAIR(fn_sub_2F3760_002f3760)
P3FES_B9_PAIR(fn_sub_2F3840_002f3840)
P3FES_B9_PAIR(fn_sub_2F39B0_002f39b0)
P3FES_B9_PAIR(fn_sub_2F3A80_002f3a80)
P3FES_B9_PAIR(fn_sub_2F43A0_002f43a0)
P3FES_B9_PAIR(fn_sub_2F4410_002f4410)
P3FES_B9_PAIR(fn_sub_2F4490_002f4490)
P3FES_B9_PAIR(fn_sub_2F4540_002f4540)
P3FES_B9_PAIR(fn_sub_2F46D0_002f46d0)
P3FES_B9_PAIR(fn_sub_2F4890_002f4890)
P3FES_B9_PAIR(fn_sub_2F4950_002f4950)
P3FES_B9_PAIR(fn_sub_2F4A40_002f4a40)
P3FES_B9_PAIR(fn_sub_2F4C00_002f4c00)
P3FES_B9_PAIR(fn_sub_2F4CE0_002f4ce0)
P3FES_B9_PAIR(fn_sub_2F4E70_002f4e70)
P3FES_B9_PAIR(fn_sub_2F5030_002f5030)
P3FES_B9_PAIR(fn_sub_2F5330_002f5330)
P3FES_B9_PAIR(fn_sub_2F5490_002f5490)
P3FES_B9_PAIR(fn_sub_2F5660_002f5660)
P3FES_B9_PAIR(fn_sub_2F5870_002f5870)
P3FES_B9_PAIR(fn_sub_2F5980_002f5980)
P3FES_B9_PAIR(fn_sub_2F5A70_002f5a70)
P3FES_B9_PAIR(fn_sub_2F5D80_002f5d80)
P3FES_B9_PAIR(fn_sub_2F6120_002f6120)
P3FES_B9_PAIR(fn_sub_2F6330_002f6330)
P3FES_B9_PAIR(fn_sub_2F6510_002f6510)
P3FES_B9_PAIR(fn_sub_2F6840_002f6840)
P3FES_B9_PAIR(fn_sub_2F6AB0_002f6ab0)
P3FES_B9_PAIR(fn_sub_2F7DC0_002f7dc0)
P3FES_B9_PAIR(fn_sub_2F8460_002f8460)
P3FES_B9_PAIR(fn_sub_2F88C0_002f88c0)
P3FES_B9_PAIR(fn_sub_2F8A40_002f8a40)
P3FES_B9_PAIR(fn_sub_2FAC80_002fac80)
P3FES_B9_PAIR(fn_sub_2FACC0_002facc0)
P3FES_B9_PAIR(fn_sub_2FB690_002fb690)
#undef P3FES_B9_PAIR
}  // namespace p3fes::recomp_gen

namespace {

namespace rg = p3fes::recomp_gen;

#define P3FES_B9_CASE(name, va, fn, kinds) {name, va, &rg::fn, &rg::fn##__recomp, kinds}
// Argument kinds (battle7_pairs.h): A a btlAction, U / E a (enemy) btlUnit, P a data block (the event records), Q a
// camera shot, "" none.
const Case kCases[] = {
    P3FES_B9_CASE("sub_2F0580", 0x2F0580u, fn_sub_2F0580_002f0580, "A"),
    P3FES_B9_CASE("sub_2F05F0", 0x2F05F0u, fn_sub_2F05F0_002f05f0, "A"),
    P3FES_B9_CASE("sub_2F0E30", 0x2F0E30u, fn_sub_2F0E30_002f0e30, "A"),
    P3FES_B9_CASE("sub_2F0EA0", 0x2F0EA0u, fn_sub_2F0EA0_002f0ea0, "A"),
    P3FES_B9_CASE("sub_2F14A0", 0x2F14A0u, fn_sub_2F14A0_002f14a0, "A"),
    P3FES_B9_CASE("sub_2F1680", 0x2F1680u, fn_sub_2F1680_002f1680, ""),
    P3FES_B9_CASE("sub_2F1810", 0x2F1810u, fn_sub_2F1810_002f1810, ""),
    P3FES_B9_CASE("sub_2F19D0", 0x2F19D0u, fn_sub_2F19D0_002f19d0, ""),
    P3FES_B9_CASE("sub_2F1D40", 0x2F1D40u, fn_sub_2F1D40_002f1d40, ""),
    P3FES_B9_CASE("sub_2F1F00", 0x2F1F00u, fn_sub_2F1F00_002f1f00, ""),
    P3FES_B9_CASE("sub_2F2090", 0x2F2090u, fn_sub_2F2090_002f2090, ""),
    P3FES_B9_CASE("sub_2F2250", 0x2F2250u, fn_sub_2F2250_002f2250, ""),
    P3FES_B9_CASE("sub_2F2450", 0x2F2450u, fn_sub_2F2450_002f2450, "P"),
    P3FES_B9_CASE("sub_2F2490", 0x2F2490u, fn_sub_2F2490_002f2490, "P"),
    P3FES_B9_CASE("sub_2F2550", 0x2F2550u, fn_sub_2F2550_002f2550, "A"),
    P3FES_B9_CASE("sub_2F2840", 0x2F2840u, fn_sub_2F2840_002f2840, "A"),
    P3FES_B9_CASE("sub_2F2890", 0x2F2890u, fn_sub_2F2890_002f2890, "A"),
    P3FES_B9_CASE("sub_2F2B40", 0x2F2B40u, fn_sub_2F2B40_002f2b40, "A"),
    P3FES_B9_CASE("sub_2F2B90", 0x2F2B90u, fn_sub_2F2B90_002f2b90, "A"),
    P3FES_B9_CASE("sub_2F3190", 0x2F3190u, fn_sub_2F3190_002f3190, "A"),
    P3FES_B9_CASE("sub_2F3320", 0x2F3320u, fn_sub_2F3320_002f3320, "A"),
    P3FES_B9_CASE("sub_2F3520", 0x2F3520u, fn_sub_2F3520_002f3520, "A"),
    P3FES_B9_CASE("sub_2F3670", 0x2F3670u, fn_sub_2F3670_002f3670, "A"),
    P3FES_B9_CASE("sub_2F3760", 0x2F3760u, fn_sub_2F3760_002f3760, ""),
    P3FES_B9_CASE("sub_2F3840", 0x2F3840u, fn_sub_2F3840_002f3840, ""),
    P3FES_B9_CASE("sub_2F39B0", 0x2F39B0u, fn_sub_2F39B0_002f39b0, "P"),
    P3FES_B9_CASE("sub_2F3A80", 0x2F3A80u, fn_sub_2F3A80_002f3a80, "A"),
    P3FES_B9_CASE("sub_2F43A0", 0x2F43A0u, fn_sub_2F43A0_002f43a0, "A"),
    P3FES_B9_CASE("sub_2F4410", 0x2F4410u, fn_sub_2F4410_002f4410, ""),
    P3FES_B9_CASE("sub_2F4490", 0x2F4490u, fn_sub_2F4490_002f4490, "A"),
    P3FES_B9_CASE("sub_2F4540", 0x2F4540u, fn_sub_2F4540_002f4540, ""),
    P3FES_B9_CASE("sub_2F46D0", 0x2F46D0u, fn_sub_2F46D0_002f46d0, ""),
    P3FES_B9_CASE("sub_2F4890", 0x2F4890u, fn_sub_2F4890_002f4890, "A"),
    P3FES_B9_CASE("sub_2F4950", 0x2F4950u, fn_sub_2F4950_002f4950, ""),
    P3FES_B9_CASE("sub_2F4A40", 0x2F4A40u, fn_sub_2F4A40_002f4a40, ""),
    P3FES_B9_CASE("sub_2F4C00", 0x2F4C00u, fn_sub_2F4C00_002f4c00, "A"),
    P3FES_B9_CASE("sub_2F4CE0", 0x2F4CE0u, fn_sub_2F4CE0_002f4ce0, ""),
    P3FES_B9_CASE("sub_2F4E70", 0x2F4E70u, fn_sub_2F4E70_002f4e70, ""),
    P3FES_B9_CASE("sub_2F5030", 0x2F5030u, fn_sub_2F5030_002f5030, "A"),
    P3FES_B9_CASE("sub_2F5330", 0x2F5330u, fn_sub_2F5330_002f5330, "A"),
    P3FES_B9_CASE("sub_2F5490", 0x2F5490u, fn_sub_2F5490_002f5490, ""),
    P3FES_B9_CASE("sub_2F5660", 0x2F5660u, fn_sub_2F5660_002f5660, "A"),
    P3FES_B9_CASE("sub_2F5870", 0x2F5870u, fn_sub_2F5870_002f5870, "A"),
    P3FES_B9_CASE("sub_2F5980", 0x2F5980u, fn_sub_2F5980_002f5980, "A"),
    P3FES_B9_CASE("sub_2F5A70", 0x2F5A70u, fn_sub_2F5A70_002f5a70, ""),
    P3FES_B9_CASE("sub_2F5D80", 0x2F5D80u, fn_sub_2F5D80_002f5d80, "E"),
    P3FES_B9_CASE("sub_2F6120", 0x2F6120u, fn_sub_2F6120_002f6120, ""),
    P3FES_B9_CASE("sub_2F6330", 0x2F6330u, fn_sub_2F6330_002f6330, "Q"),
    P3FES_B9_CASE("sub_2F6510", 0x2F6510u, fn_sub_2F6510_002f6510, "Q"),
    P3FES_B9_CASE("sub_2F6840", 0x2F6840u, fn_sub_2F6840_002f6840, "A"),
    P3FES_B9_CASE("sub_2F6AB0", 0x2F6AB0u, fn_sub_2F6AB0_002f6ab0, "A"),
    P3FES_B9_CASE("sub_2F7DC0", 0x2F7DC0u, fn_sub_2F7DC0_002f7dc0, ""),
    P3FES_B9_CASE("sub_2F8460", 0x2F8460u, fn_sub_2F8460_002f8460, ""),
    P3FES_B9_CASE("sub_2F88C0", 0x2F88C0u, fn_sub_2F88C0_002f88c0, ""),
    P3FES_B9_CASE("sub_2F8A40", 0x2F8A40u, fn_sub_2F8A40_002f8a40, "U"),
    P3FES_B9_CASE("sub_2FAC80", 0x2FAC80u, fn_sub_2FAC80_002fac80, ""),
    P3FES_B9_CASE("sub_2FACC0", 0x2FACC0u, fn_sub_2FACC0_002facc0, ""),
    P3FES_B9_CASE("sub_2FB690", 0x2FB690u, fn_sub_2FB690_002fb690, ""),
};
#undef P3FES_B9_CASE

const Snap kSnaps[] = {{"b_5800", 16}, {"climb_ref_17000", 2}, {"dorm_replay_4900", 1}};

// The boss encounters (and plain ones) and the enemy ids their hooks look for.
const u16 kBossEncounters[] = {416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431,
                               432, 433, 434, 435, 436, 456, 1, 300};
const u16 kBossIds[] = {233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 256, 257, 258, 259, 260, 261, 262,
                        263, 264, 266, 269, 271, 272, 274, 275, 276, 277, 278, 279, 280, 294, 1, 9, 100};

inline u64 ld64(Machine& m, u32 va) {
    u64 v;
    std::memcpy(&v, ram(m, va), 8);
    return v;
}
inline void st64(Machine& m, u32 va, u64 v) { std::memcpy(ram(m, va), &v, 8); }

// The enemy (side 1) or party (side 0) list as the bodies walk it: from the tail, by +2612.
std::vector<u32> side_list(Machine& m, u32 btl, u32 side) {
    std::vector<u32> v;
    for (u32 u = ld32(m, btl + bcore::kBtlUnitTail + 8 * side), n = 0; in_ram(u) && n < 16; u = ld32(m, u + bcore::kUnPrev), ++n)
        v.push_back(u);
    return v;
}

// The boss perturbations of one battle-world pair (after battle7's).
void perturb9(Machine& m, const Objects& o, std::mt19937& rng) {
    if (!o.btl) return;
    if (chance(rng, 70))
        if (const u32 g = ld32(m, o.btl + bcore::kBtlSetupEnemies); in_ram(g)) {
            const u16 enc = kBossEncounters[rng() % std::size(kBossEncounters)];
            st16(m, g + b9::kEncId, enc);
        }
    for (u32 u : o.units)
        if (chance(rng, 40)) {
            const u16 id = kBossIds[rng() % std::size(kBossIds)];
            st16(m, u + bcore::kUnId, id);
        }
    // the boss work: listed actions (live ones), the phase, the copy counts, the fade timers, the once flags
    if (chance(rng, 50) && !o.acts.empty()) {
        const u16 n = static_cast<u16>(rng() % 4);
        for (u16 i = 0; i < n; ++i) st32(m, o.btl + b9::kBoss2884 + 4u * i, o.acts[rng() % o.acts.size()]);
        st16(m, o.btl + b9::kBoss2896, n);
    }
    if (chance(rng, 60)) {
        const u32 stage = rng() % 3;
        st32(m, o.btl + b9::kBoss2888, stage);
    }
    if (chance(rng, 40)) {
        const u32 arg = rng() % 3;
        st32(m, o.btl + b9::kBoss2892, arg);
    }
    if (chance(rng, 50)) {
        const u32 pick = rng() % 11;
        st32(m, o.btl + b9::kBoss2900, pick);
        const u16 len = static_cast<u16>(1 + rng() % 8);
        st16(m, o.btl + b9::kBoss2902, len);
        const u32 frame = rng() % 10;
        st32(m, o.btl + b9::kBoss2904, frame);
    }
    if (chance(rng, 40)) {
        for (u32 i = 0; i < 11; ++i) {
            const u16 c = static_cast<u16>(rng() % 3);
            st16(m, o.btl + b9::kBoss2908 + 2 * i, c);
        }
        if (chance(rng, 50)) {
            const u32 skill = 293 + rng() % 5;
            st32(m, o.btl + b9::kBoss2908, skill);
        }
    }
    if (chance(rng, 30)) {
        const u32 once = rng() % 2;
        st32(m, o.btl + b9::kBoss2912, once);
    }
    for (u32 a : o.acts) {
        if (chance(rng, 20)) st16(m, a + b9::kActSkill, 343);
        if (chance(rng, 25)) {  // a target list of live actions
            const u16 n = static_cast<u16>(rng() % (o.acts.size() + 1));
            for (u16 i = 0; i < n; ++i) st32(m, a + b9::kActTargets + 4u * i, o.acts[rng() % o.acts.size()]);
            st16(m, a + b9::kActTargetCount, n);
        }
        if (chance(rng, 20) && !o.enemies.empty())  // the summon's enemy ids: the snapshot's own enemy genus
            for (u32 i = 0; i < 3; ++i) {
                const u32 e = o.enemies[rng() % o.enemies.size()];
                const u16 id = ld16(m, ld32(m, e + bcore::kUnDat) + bcore::kDatId);
                st16(m, a + 118 + 2 * i, id);
            }
    }
}

// battle7's stand-ins plus a recorder for sub_2DCE90, the not-emitted first call of sub_2F3840 (429's death scene):
// without it that body's pairs stop at its entry.
void b9_setup(StandInWorld& w) {
    b7_setup(w);
    w.si.install_recorder(0x2DCE90u, "rec_sub_2DCE90", 0, 4);
}

// battle7_pairs.h's pair_base with b9_setup's stand-ins (the same checks).
hgp::Run pair_base9(Machine& m, BaseRange& ram, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what,
                    const HwCheck& hw) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    b9_setup(*wh);
    b9_setup(*wr);
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
                           << (r.stopped ? " (recomp stopped: " + r.what + " at " + hex64(r.stop_pc) + ")" : std::string()));
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

// battle7_pairs.h's run_snapshots with perturb9 after perturb and b9_setup's stand-ins.
void run_snapshots9() {
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
        MESSAGE("battle9 " << std::string(sn.dir) << ": gBtl " << hex64(o.btl) << ", " << o.acts.size() << " actions, "
                           << o.units.size() << " units");
        BaseRange base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            for (u32 rep = 0; rep < reps; ++rep) {
                if (trace) std::fprintf(stderr, "%s %s rep %u\n", sn.dir, c.name, rep);
                std::mt19937 rng{rep * 104729u + c.addr + static_cast<u32>(used) * 7u};
                perturb(*m, o, rng);
                perturb9(*m, o, rng);
                Args a{};
                HwCheck hw;
                args_for(*m, c, o, rng, a, hw);
                const u32 seed = rng();
                const hgp::Run r = pair_base9(*m, base, c.hand, c.recomp, a, seed, c.name, hw);
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
    MESSAGE("battle9 battle snapshots: " << pairs << " pairs on " << used << " snapshot(s), " << stops << " ended at a compared stop");
}

// sub_2F8A40's table (its jump table read from the instructions): is the unit the encounter's boss.
bool is_boss_model(u16 enc, u8 side, u16 id) {
    if (side != 1) return false;
    switch (enc) {
    case 436: case 428: return true;
    case 429: return id == 274;
    case 424: return id == 269;
    case 422: return id == 266;
    case 421: return id == 263;
    case 420: return id == 261 || id == 262 || id == 277;
    case 419: return id == 260;
    case 418: return id == 259;
    case 417: return id == 257 || id == 258;
    case 416: return id == 256;
    default: return false;
    }
}

}  // namespace

TEST_CASE("game(battle9): every body equals its recompiled body on random worlds") {
    run_random(kCases, std::size(kCases), 48, "battle9");
}

TEST_CASE("game(battle9): every body on the battle snapshots, perturbed") { run_snapshots9(); }

TEST_CASE("game(battle9): the boss rules") {
    auto m = new_machine();
    if (!m) return;
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
    auto v0 = [&](Fn f, u64 a0 = 0) { return v0_of(solo(*m, f, {a0, 0, 0, 0})); };
    auto set_encounter = [&](const Objects& o, u16 enc) { st16(*m, ld32(*m, o.btl + bcore::kBtlSetupEnemies) + b9::kEncId, enc); };
    std::mt19937 rng{0xB9u};
    int checks = 0;
    // (1) the boss-unit query: the encounter's table of enemy ids (436 / 428: any enemy), never a party unit
    for (int k = 0; k < 96; ++k) {
        const Objects o = load();
        if (o.units.empty()) break;
        const u32 u = o.units[rng() % o.units.size()];
        const u16 enc = kBossEncounters[rng() % std::size(kBossEncounters)];
        const u8 side = static_cast<u8>(rng() % 3);
        const u16 id = kBossIds[rng() % std::size(kBossIds)];
        set_encounter(o, enc);
        st8(*m, u + bcore::kUnSide, side);
        st16(*m, u + bcore::kUnId, id);
        INFO("encounter " << enc << " side " << unsigned(side) << " id " << id);
        CHECK(v0(&rg::fn_sub_2F8A40_002f8a40, sx(u)) == (is_boss_model(enc, side, id) ? 1u : 0u));
        ++checks;
    }
    // (2) the turn query: 424 asks gBtl +2900 == 1; 416 whether an enemy 275 / 276 is present; a plain encounter 0
    for (int k = 0; k < 48; ++k) {
        const Objects o = load();
        if (!o.btl) break;
        const u32 kind = rng() % 3;
        const u16 enc = kind == 0 ? 424 : kind == 1 ? 416 : 300;
        set_encounter(o, enc);
        const u32 w = rng() % 3;
        st32(*m, o.btl + b9::kBoss2900, w);
        bool present = false;
        for (u32 e : side_list(*m, o.btl, 1)) {
            static const u16 kIds[] = {275, 276, 100, 233};
            const u16 id = kIds[rng() % std::size(kIds)];
            st16(*m, e + bcore::kUnId, id);
            present |= id == 275 || id == 276;
        }
        const u64 want = enc == 424 ? (w == 1 ? 1 : 0) : enc == 416 ? (present ? 1 : 0) : 0;
        INFO("encounter " << enc << " +2900 " << w);
        CHECK(v0(&rg::fn_sub_2F88C0_002f88c0) == want);
        ++checks;
    }
    // (3) a formation (sub_2F3760): the hero at (0, 500) with slot 0, the other party units at (0, 0), every enemy at
    //     (0, -500)
    {
        const Objects o = load();
        if (o.btl) {
            const std::vector<u32> party = side_list(*m, o.btl, 0), enemies = side_list(*m, o.btl, 1);
            if (!party.empty()) st16(*m, party[0] + bcore::kUnId, 1);
            v0(&rg::fn_sub_2F3760_002f3760);
            auto xz = [&](u32 u) {
                float x, z;
                std::memcpy(&x, m->at(u + bcore::kUnPos), 4);
                std::memcpy(&z, m->at(u + bcore::kUnPos + 8), 4);
                return std::pair<float, float>(x, z);
            };
            for (u32 u : party) {
                const bool hero = ld16(*m, u + bcore::kUnId) == 1;
                INFO("party unit " << hex64(u) << (hero ? " (hero)" : ""));
                CHECK(xz(u).first == 0.0f);
                CHECK(xz(u).second == (hero ? 500.0f : 0.0f));
                if (hero) CHECK(ld8(*m, u + bcore::kUnFormSlot) == 0);
                checks += 2;
            }
            for (u32 u : enemies) {
                INFO("enemy unit " << hex64(u));
                CHECK(xz(u).first == 0.0f);
                CHECK(xz(u).second == -500.0f);
                checks += 2;
            }
        }
    }
    // (4) encounter 432's copy pick: among the party ids other than the last copy and 9, one with the fewest copies;
    //     its count + 1, the copy's skill (+2904) and the boss DatUnit's +4 by the member
    for (int k = 0; k < 64; ++k) {
        const Objects o = load();
        if (o.acts.empty()) break;
        const std::vector<u32> party = side_list(*m, o.btl, 0);
        static const u16 kParty[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::vector<u16> ids;
        for (u32 u : party) {
            const u16 id = kParty[rng() % std::size(kParty)];
            st16(*m, u + bcore::kUnId, id);
            ids.push_back(id);
        }
        for (u32 i = 0; i < 11; ++i) {
            const u16 c = static_cast<u16>(1 + rng() % 3);
            st16(*m, o.btl + b9::kBoss2908 + 2 * i, c);
        }
        const u32 last = rng() % 11;
        st32(*m, o.btl + b9::kBoss2900, last);
        st32(*m, o.btl + b9::kBoss2904, 0xFFu);
        const u32 a = o.acts[rng() % o.acts.size()];
        const u32 dat = ld32(*m, ld32(*m, a + bcore::kActUnit) + bcore::kUnDat);
        st16(*m, dat + 4, 0x7777u);
        u32 fewest = 0xFFFF;
        std::vector<u16> cand;
        for (u16 id : ids)
            if (id != last && id != 9) {
                cand.push_back(id);
                fewest = std::min<u32>(fewest, ld16(*m, o.btl + b9::kBoss2908 + 2 * id));
            }
        std::vector<u16> before(11);
        for (u32 i = 0; i < 11; ++i) before[i] = ld16(*m, o.btl + b9::kBoss2908 + 2 * i);
        v0(&rg::fn_sub_2F5030_002f5030, sx(a));
        const u32 got = ld32(*m, o.btl + b9::kBoss2900);
        INFO("party " << ids.size() << " last " << last << " picked " << got);
        if (cand.empty()) {
            CHECK(got == last);
            ++checks;
            continue;
        }
        CHECK(std::find(cand.begin(), cand.end(), static_cast<u16>(got)) != cand.end());
        CHECK(before[got] == fewest);
        CHECK(ld16(*m, o.btl + b9::kBoss2908 + 2 * got) == before[got] + 1);
        static const u32 kSkill[11] = {0xFF, 225, 224, 0xFF, 226, 227, 0xFF, 228, 229, 231, 230};
        static const u16 kDat4[11] = {0x7777, 297, 298, 0x7777, 299, 300, 0x7777, 301, 302, 0, 303};
        if (got < 11 && got != 9) {
            CHECK(ld32(*m, o.btl + b9::kBoss2904) == kSkill[got]);
            CHECK(ld16(*m, dat + 4) == kDat4[got]);
        }
        checks += 5;
    }
    // (5) encounter 432's unit init (enemy 234): the boss work starts at member 1, skill 225, the copy counts cleared
    //     but the hero's (1); the action gets +26 bit 0x10, the unit flags 0x1C0
    for (int k = 0; k < 8; ++k) {
        const Objects o = load();
        if (o.acts.empty()) break;
        const u32 a = o.acts[rng() % o.acts.size()];
        const u32 u = ld32(*m, a + bcore::kActUnit);
        st16(*m, a + bcore::kActFlags2, static_cast<u16>(ld16(*m, a + bcore::kActFlags2) | 1));
        st8(*m, u + bcore::kUnSide, 1);
        st16(*m, u + bcore::kUnId, 234);
        for (u32 i = 0; i < 11; ++i) st16(*m, o.btl + b9::kBoss2908 + 2 * i, 0x5555u);
        const u32 fl = ld32(*m, u + bcore::kUnFlags);
        v0(&rg::fn_sub_2F4C00_002f4c00, sx(a));
        CHECK(ld32(*m, o.btl + b9::kBoss2900) == 1);
        CHECK(ld32(*m, o.btl + b9::kBoss2904) == 225);
        bool cleared = true;
        for (u32 i = 0; i < 11; ++i)
            if (i != 1) cleared &= ld16(*m, o.btl + b9::kBoss2908 + 2 * i) == 0;
        CHECK(cleared);
        CHECK(ld16(*m, o.btl + b9::kBoss2910) == 1);
        CHECK((ld16(*m, a + bcore::kActFlags2) & 0x10) != 0);
        CHECK(ld32(*m, u + bcore::kUnFlags) == (fl | 0x1C0u));
        checks += 6;
    }
    // (6) the done callbacks' query: 1 while a queued packet is owned by the action's uid, 0 for an uid no packet has
    {
        const Objects o = load();
        std::vector<u64> owners;
        for (u32 q = 0; q < 4 && o.btl; ++q)
            for (u32 p = ld32(*m, o.btl + bcore::kBtlPktHead + 8 * q), n = 0; in_ram(p) && n < 64; p = ld32(*m, p + bcore::kPktNext), ++n)
                owners.push_back(ld64(*m, p + bcore::kPktOwner));
        const u32 act = kScratch + 0x20000u;
        std::memset(m->at(act), 0, 64);
        for (u64 uid : owners) {
            st64(*m, act, uid);
            CHECK(v0(&rg::fn_sub_2F2840_002f2840, sx(act)) == 1u);
            ++checks;
        }
        st64(*m, act, 0x1234567890ABCDEull);
        CHECK(v0(&rg::fn_sub_2F2840_002f2840, sx(act)) == 0u);
        CHECK(v0(&rg::fn_sub_2F2B40_002f2b40, sx(act)) == 0u);
        checks += 2;
        MESSAGE("battle9 packet owners in b_5800: " << owners.size());
    }
    MESSAGE("battle9 boss rules: " << checks << " checks");
}

#else

TEST_CASE("game(battle9): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
