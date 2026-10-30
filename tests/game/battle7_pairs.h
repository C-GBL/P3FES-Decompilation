// The pair machinery of slice battle7's tests (test_battle7_ai.cpp, test_battle7_sound.cpp, test_battle7_misc.cpp):
// every body against its recompiled body (__recomp) on identical guest machines, compared by tests/game/handgen_pairs.h
// -- the whole register file and the cycle count at every check point and at the return / stop, all 32 MiB of RAM (the
// dead stack and every stray store), the scratchpad, the BIOS window and the bus log -- plus the stand-in call log (both
// bodies meet the same deterministic heap behind the RwMalloc / RwFree slots, sprintf, the H_Cdvd layer and the same
// recorders for the callees the test build does not emit).
//
//   * random worlds (the p3fes_handgen skeleton's);
//   * battle worlds: the replay snapshots b_5800 (the first battle in state ACTION: live gBtl, 4 btlActions, 7 btlUnits,
//     DatUnits, packets), battle_ref_6150 / b_6150 (the battle over), b_6300 / climb_ref_17000 (no battle: the null
//     paths). Each pair is perturbed the way the branches ask -- statuses, HP, unit ids (party members 1..10, enemy
//     ids with other affinities), the encounter, the actions' last command (+124 / +126), turns, one-more, candidate
//     lists, the DatUnit flags, the gBtl voice / camera / support words -- and restored afterwards (a long-lived
//     BaseRange); the arguments are of the kind each function takes (Case::kinds, below).
#pragma once

#include "handgen_pairs.h"
#include "stand_ins.h"
#include "write_tracker.h"

#include "p3fes/game/battle3.h"
#include "p3fes/game/battle4.h"
#include "p3fes/game/battle5.h"
#include "p3fes/game/battle7.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

namespace p3fes::game_test::b7t {

namespace b3 = p3fes::game::b3;
namespace b4 = p3fes::game::b4;
namespace b5 = p3fes::game::b5;
namespace b7 = p3fes::game::b7;

// --- the functions and the kinds of their arguments ($a0..$a3, then $t0..$t2) -------------------------------------------
// A btlAction   U btlUnit   E an enemy btlUnit   r an AI target record (btlAction +136)   R a command record (+56)
// p an AI parameter (a percentage, a unit id, an element, a status bit, a skill)   w an AI query word (kind bits)
// I a u16 item list   c a count 0..8   q 0..2   u a unit uid   n small 0..7   m 0..15   b 0 / 1   k a skill id
// x a help text id (message id or 0x1000 + item)   P a packet data block (64 small random bytes)   D a motion packet
// block {btlUnit, u16 x3}   S an AI script packet block {action, procedure, started, script}   V a voice bank packet
// block {request, started}   W a voice line packet block {action, u16 situation, args, started +20}   H a help packet
// block {unit, text, frames}   Q a camera shot   t a short text   o an out buffer   z zero
struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
    const char* kinds;
};

// --- guest memory helpers ---------------------------------------------------------------------------------------------
inline u8* ram(Machine& m, u32 va) { return m.at(std::min<u32>(va & 0x1FFFFFFu, 0x2000000u - 8)); }
inline void st8(Machine& m, u32 va, u8 v) { *ram(m, va) = v; }
inline void st16(Machine& m, u32 va, u16 v) { std::memcpy(ram(m, va), &v, 2); }
inline void st32(Machine& m, u32 va, u32 v) { std::memcpy(ram(m, va), &v, 4); }
inline void stf(Machine& m, u32 va, float v) { std::memcpy(ram(m, va), &v, 4); }
inline u8 ld8(Machine& m, u32 va) { return *ram(m, va); }
inline u16 ld16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, ram(m, va), 2);
    return v;
}
inline u32 ld32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, ram(m, va), 4);
    return v;
}
inline bool chance(std::mt19937& rng, u32 pct) { return rng() % 100 < pct; }
inline bool in_ram(u32 va) { return va >= 0x100000u && va < 0x2000000u; }

inline constexpr u32 kGpVa = 0x7D2CF0u;
inline constexpr u32 kGBtlSlot = 0x7CE3ECu;
inline u32 gp(s32 off) { return kGpVa + static_cast<u32>(off); }
// Free guest memory for the blocks a test builds (zero in every replay snapshot; the stand-in heap allocates from
// kStandInHeap upwards and never gets this far in these pairs).
inline constexpr u32 kScratch = kStandInHeap + 0x2C0000u;

// The stand-ins: heap, printf, sprintf, H_Cdvd, and recorders for the callees the test build does not emit that the
// bodies reach (both bodies meet the same recorder; its log is compared).
inline const u32 kRecorded[] = {
    // the sound request layer below the bodies' sound calls and the sound driver entries
    0x10A0E0u, 0x10A100u, 0x10A240u, 0x10A720u, 0x51DF58u, 0x51E028u, 0x108F70u, 0x108FD0u, 0x109180u, 0x109F60u,
    0x1099D0u, 0x10A370u, 0x109AE0u, 0x109DF0u,
    // the navigator message stop, the cut-in / special effect players' task layer
    0x3C8FA0u, 0x3C8F70u, 0x3C77A0u, 0x3C7BC0u, 0x3C9850u, 0x3C9AB0u, 0x3C9D00u,
    // still-recompiled battle callees of the camera shots (sub_2E70B0 / sub_2E6A20, the boss target shots)
    0x2E70B0u, 0x2E6A20u,
    // other slices' stand-ins the bodies reach (recorders here never take them)
    0x324BD0u, 0x2E3AE0u, 0x2DCFB0u, 0x242600u, 0x2B94F0u, 0x316F70u, 0x4F7560u, 0x242720u, 0x25BE60u,
    // the light / camera / RW callees, the font / texture loaders, the message window and status tasks
    0x1A0700u, 0x1A07F0u, 0x1A4580u, 0x4C9D70u, 0x4DD2E0u, 0x20F9A0u, 0x21EC40u, 0x3A2D80u, 0x3B7090u, 0x3170C0u,
    0x31C820u, 0x1A08E0u, 0x20F570u, 0x21C9F0u, 0x21CC20u, 0x3C8230u, 0x491EA0u,
    0x245EA0u, 0x267120u, 0x274030u, 0x2813F0u, 0x282D40u, 0x288110u, 0x28DF00u, 0x2B6460u};
inline void b7_setup(StandInWorld& w) {
    install_standard(w);
    for (u32 va : kRecorded) w.si.install_recorder(va, "rec_" + hex64(va), 0, 4);
}

// --- stand-ins and the pair -----------------------------------------------------------------------------------------
inline StandInWorld* g_si[2];
inline Fn g_fn[2];
inline void thunk0(EEContext& ctx) {
    StandInsScope s(g_si[0]->si);
    g_fn[0](ctx);
}
inline void thunk1(EEContext& ctx) {
    StandInsScope s(g_si[1]->si);
    g_fn[1](ctx);
}
// hgp::pair (everything at every check point, the end / stop, all RAM, scratchpad, BIOS, bus) with a fresh stand-in
// world around each body and the two call logs compared. Returns the recompiled run.
inline hgp::Run pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const HwCheck& hw) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    b7_setup(*wh);
    b7_setup(*wr);
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what, hw);
    expect_same_log(wh->si, wr->si, what);
    return r;
}
// hgp::pair's comparison on a long-lived BaseRange (write_tracker.h) instead of a PairRange per pair: the snapshot
// world's 32 MiB stay the base and restore() copies back only the pages a pair wrote. Same checks as hgp::pair.
inline hgp::Run pair_base(Machine& m, BaseRange& ram, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what,
                          const HwCheck& hw) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    b7_setup(*wh);
    b7_setup(*wr);
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
    INFO(std::string(what) << " a0=" << hex64(args[0]) << " a1=" << hex64(args[1]) << " a2=" << hex64(args[2]) << " a3=" << hex64(args[3])
              << " seed=" << seed << (r.stopped ? " (recomp stopped: " + r.what + " at " + hex64(r.stop_pc) + ")" : std::string())
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
// One body alone (the rule checks) with its own stand-in world (kept in g_solo for its call log).
inline std::unique_ptr<StandInWorld> g_solo;
inline hgp::Run solo(Machine& m, Fn fn, const Args& args, const HwCheck& hw = {}) {
    g_solo = std::make_unique<StandInWorld>();
    b7_setup(*g_solo);
    g_si[0] = g_solo.get();
    g_fn[0] = fn;
    return hgp::run_one(m, &thunk0, args, 1, hw);
}
// The solo run's last call of the stood-in `va` (nullptr when none).
inline const StandInCall* solo_call(u32 va) {
    for (auto it = g_solo->si.log.rbegin(); it != g_solo->si.log.rend(); ++it)
        if (it->va == va) return &*it;
    return nullptr;
}
inline u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

inline std::unique_ptr<Machine> new_machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    write_rw_slots(*m);
    return m;
}

// --- the battle objects of a snapshot -------------------------------------------------------------------------------
struct Objects {
    u32 btl = 0;
    std::vector<u32> acts, units, enemies, dats, data;  // data: the packets' data blocks
    std::vector<u32> uids;
};
inline Objects objects_of(Machine& m) {
    Objects o;
    o.btl = ld32(m, kGBtlSlot);
    if (!in_ram(o.btl)) {
        o.btl = 0;
        return o;
    }
    for (u32 a = ld32(m, o.btl + b3::gbtl::kActionList), n = 0; in_ram(a) && n < 32; a = ld32(m, a + b3::act::kNext), ++n)
        o.acts.push_back(a);
    for (u32 s = 0; s < 4; ++s)
        for (u32 u = ld32(m, o.btl + b3::gbtl::kUnitHead0 + 8 * s), n = 0; in_ram(u) && n < 32; u = ld32(m, u + b3::unit::kNext), ++n) {
            o.units.push_back(u);
            if (s == 1) o.enemies.push_back(u);
            o.uids.push_back(ld32(m, u + b3::unit::kUid));
            if (const u32 d = ld32(m, u + b3::unit::kDat); in_ram(d)) o.dats.push_back(d);
        }
    for (u32 q = 0; q < 4; ++q)
        for (u32 p = ld32(m, o.btl + b3::gbtl::kPktHead0 + 8 * q), n = 0; in_ram(p) && n < 64; p = ld32(m, p + b3::pkt::kNext), ++n)
            if (const u32 d = ld32(m, p + b3::pkt::kData); in_ram(d)) o.data.push_back(d);
    return o;
}
template <class T>
T pick(const std::vector<T>& v, std::mt19937& rng, T fallback) {
    return v.empty() ? fallback : v[rng() % v.size()];
}

// The encounters the bodies branch on (the FES boss fights 433..435, 417, 428, 429, the boss rules) and plain ones.
inline const u16 kEncounters[] = {417, 428, 429, 433, 434, 435, 436, 1, 25, 120, 300};
// Party member ids 1..10 and enemy ids (other affinities, silent / analysed ones).
inline const u16 kUnitIds[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 30, 61, 100, 149, 152, 200, 241, 300};

// The perturbations of one battle-world pair.
inline void perturb(Machine& m, const Objects& o, std::mt19937& rng) {
    static const u32 kStatus[] = {0x100000u, 0x80000u, 0x1u, 0x2u, 0x4u, 0x8u, 0x10u, 0x20u, 0x40u, 0x80u, 0x100u, 0x200u};
    for (u32 d : o.dats) {
        if (chance(rng, 35)) {
            const bool clear = chance(rng, 50);
            const u32 a = kStatus[rng() % std::size(kStatus)];
            st32(m, d + b3::dat::kStatus, clear ? 0 : a);
        }
        if (chance(rng, 25)) {
            const bool zero = chance(rng, 20);
            const u32 hp = 1 + rng() % 400;
            st16(m, d + b3::dat::kHp, static_cast<u16>(zero ? 0 : hp));
        }
        if (chance(rng, 15)) {
            const u16 fl = static_cast<u16>(rng() & 0x34u);
            st16(m, d + b3::dat::kFlags, static_cast<u16>((ld16(m, d + b3::dat::kFlags) & ~0x30u) | fl));
        }
    }
    if (!o.btl) return;
    if (chance(rng, 40))
        if (const u32 g = ld32(m, o.btl + b3::gbtl::kSetupEnemies); in_ram(g)) {
            const u16 enc = kEncounters[rng() % std::size(kEncounters)];
            st16(m, g + 8, enc);
        }
    for (u32 u : o.units)
        if (chance(rng, 25)) {
            const u16 id = kUnitIds[rng() % std::size(kUnitIds)];
            st16(m, u + b3::unit::kId, id);
        }
    static const u32 kFlagBits[] = {0x40u, 0x80u, 0x2000u, 0x4000u, 0x200000u};
    for (int k = 0; k < 2; ++k)
        if (chance(rng, 30)) {
            const u32 bit = kFlagBits[rng() % std::size(kFlagBits)];
            st32(m, o.btl + b3::gbtl::kFlags, ld32(m, o.btl + b3::gbtl::kFlags) ^ bit);
        }
    if (chance(rng, 50)) {
        const u16 ready = static_cast<u16>(rng() & 1u);
        st16(m, o.btl + b7::gbtl7::kVoiceReady, ready);
    }
    if (chance(rng, 25)) {
        const u16 side = static_cast<u16>(rng() & 1u);
        st16(m, o.btl + b7::gbtl7::kCamSideShot, side);
    }
    if (chance(rng, 25)) {
        const u16 mode = static_cast<u16>(rng() % 3);
        st16(m, o.btl + b7::gbtl7::kCamMode, mode);
    }
    if (chance(rng, 20)) {
        const u32 bits = rng() & 0x2000000u;
        st32(m, o.btl + b4::gbtl4::kTestFlags, bits);
    }
    for (u32 a : o.acts) {
        if (chance(rng, 30)) {
            const u16 kind = static_cast<u16>(rng() % 4);
            st16(m, a + b4::act4::kLastCmdKind, kind);
            const u16 id = static_cast<u16>(rng() % 0x1D0);
            st16(m, a + b4::act4::kLastCmdId, id);
        }
        if (chance(rng, 20)) {
            const u32 turns = rng() % 6;
            st32(m, a + b3::act::kTurnsTaken, turns);
        }
        if (chance(rng, 15)) {
            const u8 more = static_cast<u8>(rng() % 2);
            st8(m, a + b3::act::kOneMore, more);
        }
        if (chance(rng, 25)) {
            const u16 skill = static_cast<u16>(rng() % 0x1D0);
            st16(m, a + b3::act::kCmdSkill, skill);
        }
        if (chance(rng, 25)) {  // a candidate list of live actions
            const u16 n = static_cast<u16>(rng() % (o.acts.size() + 1));
            for (u16 i = 0; i < n; ++i) st32(m, a + b3::act::kTargetRec + 4u * i, o.acts[rng() % o.acts.size()]);
            st16(m, a + b3::act::kTargetRecCount, n);
        }
        if (chance(rng, 15)) {
            const u16 kind = static_cast<u16>(rng() % 13);
            st16(m, a + b3::act::kCmdKind, kind);
        }
    }
}

// Builds the argument blocks in the scratch area and returns the value for one kind.
inline u64 arg_of(Machine& m, char kind, const Objects& o, std::mt19937& rng, u32& blk) {
    auto block = [&](u32 size) {
        const u32 b = kScratch + blk;
        blk += (size + 15) & ~15u;
        for (u32 i = 0; i < size; i += 4) {
            const bool zero = chance(rng, 60);
            const u32 v = rng() % 64;
            st32(m, b + i, zero ? 0 : v);
        }
        return b;
    };
    auto rnd_f = [&](int lo, int hi) {
        const int v = lo + static_cast<int>(rng() % static_cast<u32>(hi - lo + 1));
        return static_cast<float>(v);
    };
    const u32 act = pick(o.acts, rng, 0u);
    const u32 unit = pick(o.units, rng, 0u);
    switch (kind) {
    case 'A': return sx(act);
    case 'U': return sx(unit);
    case 'E': return sx(pick(o.enemies, rng, unit));
    case 'r': return sx(act ? act + b3::act::kTargetRec : 0);
    case 'R': return sx(act ? act + b3::act::kTargets : 0);
    case 'p': {  // an AI parameter
        static const u32 kStatusBits[] = {0x1u, 0x2u, 0x4u, 0x8u, 0x10u, 0x20u, 0x40u, 0x80u, 0x200u, 0x80000u, 0x100000u};
        const u32 k = rng() % 5;
        if (k == 0) return rng() % 101;                    // a percentage
        if (k == 1) return rng() % 12;                     // a unit id / an element / a level
        if (k == 2) return kStatusBits[rng() % std::size(kStatusBits)];
        if (k == 3) return rng() % 0x1D0;                  // a skill
        return rng() % 100;
    }
    case 'w': {
        static const u32 kWords[] = {0x200u, 64u, 32u, 16u, 8u, 1u, 0x100001u, 0x2000008u};
        return kWords[rng() % std::size(kWords)];
    }
    case 'I': {  // u16 item ids: the heal items and random ones
        const u32 b = block(32);
        for (u32 i = 0; i < 8; ++i) {
            const bool any = chance(rng, 50);
            const u16 id = static_cast<u16>(any ? rng() % 0x300 : 0x100 + rng() % 0x40);
            st16(m, b + 2 * i, id);
        }
        return sx(b);
    }
    case 'c': return rng() % 9;
    case 'q': return rng() % 3;
    case 'u': {
        const bool live = chance(rng, 80);
        const u32 any = rng() % 0x400;
        return live ? pick(o.uids, rng, 0u) : any;
    }
    case 'n': return rng() % 8;
    case 'm': return rng() % 16;
    case 'b': return rng() % 2;
    case 'k': return rng() % 0x1D0;
    case 'x': {
        const bool item = chance(rng, 40);
        const u32 msg = rng() % 300;
        const u32 it = 0x1000u + rng() % 0x100;
        return item ? it : msg;
    }
    case 'P': return sx(block(64));
    case 'D': {
        const u32 b = block(16);
        st32(m, b, unit);
        return sx(b);
    }
    case 'S': {
        const u32 b = block(16);
        st32(m, b, act);
        const u32 started = rng() % 2;
        st32(m, b + 8, started);
        return sx(b);
    }
    case 'V': {
        const u32 b = block(16);
        const u32 started = rng() % 2;
        st32(m, b + 4, started);
        const u32 req = rng() % 2;
        st32(m, b, req);
        return sx(b);
    }
    case 'W': {
        const u32 b = block(32);
        const bool none = chance(rng, 15);
        st32(m, b, none ? 0 : act);
        const u16 sit = static_cast<u16>(rng() % 27);
        st16(m, b + 4, sit);
        const u32 started = chance(rng, 30) ? 1u : 0u;
        st32(m, b + 20, started);
        return sx(b);
    }
    case 'H': {
        const u32 b = block(16);
        const bool nounit = chance(rng, 20);
        st32(m, b, nounit ? 0 : unit);
        const bool item = chance(rng, 30);
        const u32 msg = rng() % 300;
        st32(m, b + 4, item ? 0x1000u + rng() % 0x80 : msg);
        const u32 fr = chance(rng, 50) ? 0u : rng() % 50;
        st32(m, b + 8, fr);
        return sx(b);
    }
    case 'Q': {  // a camera shot: the action +224, the point +156, the target +256, the motion unit +288 / +292
        const u32 b = block(320);
        const bool noact = chance(rng, 10);
        st32(m, b + b7::shot::kAction, noact ? 0 : act);
        for (u32 i = 0; i < 3; ++i) stf(m, b + b7::shot::kPoint + 4 * i, rnd_f(-500, 500));
        const u32 tgt = act ? ld32(m, act + b3::act::kTargets) : 0;
        const bool same = chance(rng, 70);
        st32(m, b + b7::shot::kTarget, same ? tgt : pick(o.acts, rng, 0u));
        const u16 calls = static_cast<u16>(rng() % 3);
        st16(m, b + b7::shot::kCalls, calls);
        const bool mu = chance(rng, 60);
        st32(m, b + b7::shot::kMotionUnit, mu ? unit : 0);
        const u16 mo = static_cast<u16>(rng() % 26);
        st16(m, b + b7::shot::kMotion, mo);
        return sx(b);
    }
    case 't': {
        static const char* kTexts[] = {"AI_EVENT_000_BTLSTART", "", "AI_PC_001_002", "NOPROC"};
        const u32 b = block(32);
        const char* t = kTexts[rng() % std::size(kTexts)];
        std::memcpy(m.at(b), t, std::strlen(t) + 1);
        return sx(b);
    }
    case 'o': return sx(block(64));
    case 'z': return 0;
    default: return rng() % 8;
    }
}

// a0..a3 in Args; $t0..$t2 through HwCheck::gpr_in.
inline void args_for(Machine& m, const Case& c, const Objects& o, std::mt19937& rng, Args& a, HwCheck& hw) {
    u32 blk = 0;
    const std::size_t n = std::strlen(c.kinds);
    for (unsigned i = 0; i < 7; ++i) {
        const u64 v = i < n ? arg_of(m, c.kinds[i], o, rng, blk) : rng() % 8;
        if (i < 4) a[i] = v;
        else hw.gpr_in[GPR_T0 + (i - 4)] = v;
    }
}

struct Snap {
    const char* dir;
    u32 reps;
};

// Every case on random worlds (P3FES_HG_SEEDS pairs each, default `seeds`).
inline void run_random(const Case* cases, std::size_t count, u32 default_seeds, const char* label) {
    auto m = new_machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : default_seeds;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    constexpr u32 kWorld = 0x01810000u, kWorldSize = 0x10000u;
    int pairs = 0, stops = 0;
    for (std::size_t ci = 0; ci < count; ++ci) {
        const Case& c = cases[ci];
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const u64 a0 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a1 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a2 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a3 = hgp::random_arg(rng, kWorld, kWorldSize);
            stops += pair(*m, c.hand, c.recomp, Args{a0, a1, a2, a3}, seed, c.name, {}).stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE(std::string(label) << " random worlds: " << pairs << " pairs, " << stops << " ended at a compared stop");
}

// Every case on the battle snapshots, perturbed; reports the not-emitted callees the pairs stopped at.
inline void run_snapshots(const Case* cases, std::size_t count, const Snap* snaps, std::size_t nsnaps, const char* label) {
    const char* env = std::getenv("P3FES_HG_SEEDS");
    int pairs = 0, stops = 0, used = 0;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    std::string always;
    std::vector<int> stopped_of(count, 0), ran_of(count, 0);
    std::vector<std::string> why_of(count);
    std::map<u32, std::string> missing;
    for (std::size_t si = 0; si < nsnaps; ++si) {
        const Snap& sn = snaps[si];
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
        MESSAGE(std::string(label) << " " << std::string(sn.dir) << ": gBtl " << hex64(o.btl) << ", " << o.acts.size() << " actions, "
                      << o.units.size() << " units, " << o.data.size() << " packet data blocks");
        BaseRange base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
        for (std::size_t ci = 0; ci < count; ++ci) {
            const Case& c = cases[ci];
            if (only && std::string(only) != c.name) continue;
            for (u32 rep = 0; rep < reps; ++rep) {
                if (trace) std::fprintf(stderr, "%s %s rep %u\n", sn.dir, c.name, rep);
                std::mt19937 rng{rep * 104729u + c.addr + static_cast<u32>(used) * 7u};
                perturb(*m, o, rng);
                Args a{};
                HwCheck hw;
                args_for(*m, c, o, rng, a, hw);
                const u32 seed = rng();
                const hgp::Run r = pair_base(*m, base, c.hand, c.recomp, a, seed, c.name, hw);
                ++pairs;
                ++ran_of[ci];
                if (r.stopped) {
                    ++stops;
                    if (stopped_of[ci]++ == 0) why_of[ci] = r.what + " at " + hex64(r.stop_pc);
                    if (r.what.rfind("missing_function", 0) == 0 && missing[r.stop_pc].find(c.name) == std::string::npos)
                        missing[r.stop_pc] += std::string(" ") + c.name;
                }
                base.restore();
            }
        }
    }
    for (std::size_t ci = 0; ci < count; ++ci)
        if (ran_of[ci] && stopped_of[ci] == ran_of[ci]) always += std::string(" ") + cases[ci].name + " (" + why_of[ci] + ")";
    for (const auto& [pc, who] : missing) MESSAGE("stopped at the not-emitted " << hex64(pc) << ":" << who.substr(0, 200));
    MESSAGE(std::string(label) << " battle snapshots: " << pairs << " pairs on " << used << " snapshot(s), " << stops
                  << " ended at a compared stop; always stopped:" << (always.empty() ? " none" : always.substr(0, 1500)));
}

// A small fake battle on the scratch area for the rule checks: a zeroed gBtl (3,440 bytes) behind $gp - 18692, its
// setup genus (+3004, the encounter id at +8), up to four action / unit / DatUnit triples in gBtl's action list and the
// side lists.
struct Fake {
    u32 btl = kScratch + 0x10000u, genus = kScratch + 0x10E00u;
    u32 act[4], unit[4], dat[4];
};
inline Fake fake_battle(Machine& m, u16 encounter, u32 n_actions) {
    Fake f;
    std::memset(m.at(kScratch + 0x10000u), 0, 0x8000);
    st32(m, kGBtlSlot, f.btl);
    st32(m, f.btl + b3::gbtl::kSetupEnemies, f.genus);
    st16(m, f.genus + 8, encounter);
    for (u32 i = 0; i < 4; ++i) {
        f.act[i] = kScratch + 0x11000u + 0x500u * i;
        f.unit[i] = kScratch + 0x12400u + 0xA80u * i;
        f.dat[i] = kScratch + 0x15000u + 0x100u * i;
    }
    u32 prev = 0;
    for (u32 i = 0; i < n_actions; ++i) {
        st32(m, f.act[i] + b3::act::kUnit, f.unit[i]);
        st32(m, f.unit[i] + b3::unit::kDat, f.dat[i]);
        st16(m, f.act[i] + b3::act::kFlags2, 0x9);  // a combatant, placed
        st16(m, f.act[i] + b3::act::kFlags, 0x1);   // active
        if (prev) st32(m, prev + b3::act::kNext, f.act[i]);
        else st32(m, f.btl + b3::gbtl::kActionList, f.act[i]);
        prev = f.act[i];
    }
    return f;
}

}  // namespace p3fes::game_test::b7t

#endif
