// Phase 5 pair tests for slice battle_core2 (game/src/battle/battle_core2.cpp): every body against its recompiled body
// (__recomp) on identical guest machines, compared by tests/game/handgen_pairs.h -- the whole register file and the
// cycle count at every check point and at the return / stop, all 32 MiB of RAM (a PairRange: the dead stack and every
// stray store), the scratchpad, the BIOS window and the bus log -- plus the stand-in call log (both bodies meet the same
// deterministic stand-ins: the heap behind the RwMalloc / RwFree slots 0x960178 / 0x96017C, printf, the H_Cdvd file
// layer, and recorders for the callees the test build does not emit).
//
//   * random worlds (the p3fes_handgen skeleton's, with the stand-ins);
//   * battle worlds: a well-formed gBtl (game/include/p3fes/game/battle_core2.h) with btlUnits in the four side lists,
//     btlActions in the action list and the turn order, packets in the four queues with every condition kind, phase,
//     delay and callback (packet callbacks are this slice's own leaves or recorders), DatUnits, an admini task and
//     its work, the battle tables of the b_5800 snapshot (the table arena 0x875D00 and the section slots), every other
//     word random; arguments of the kind each function takes (a queued / fresh packet, a condition, a unit, an action,
//     a unit packet's data block, a table row, a queue, a side, an id valid for the unit's side);
//   * the replay snapshots b_5800 (mid-battle: 4 actions, 7 units, 15 packets), battle_ref_6150 (the battle over) and
//     dorm_replay_4900 (no battle): the real objects as arguments;
//   * documented-rule checks on the host: packet allocation and queueing, the uid counter's wrap, the 12 condition
//     kinds against a host model, the packet phase machine over frames, btlTableLoad on the real SKILL.TBL / UNIT.TBL
//     files (section placement in the arena against a host parse), btlUnitCreate / btlActionCreate linking and
//     defaults, the turn-order shuffle (a permutation with the player first), the turn start's return states.
#include "handgen_pairs.h"
#include "stand_ins.h"
#include "write_tracker.h"

#include "p3fes/game/battle_core2.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
namespace bc = p3fes::game::bcore;

namespace p3fes::recomp_gen {
#define P3FES_BC2_DECL(name, addr) \
    void fn_##name##_##addr(EEContext&); \
    void fn_##name##_##addr##__recomp(EEContext&);
#define P3FES_BC2_FUNCS(X)                                                                                              \
    X(sub_27C020, 0027c020) X(adminiChangeSeq, 0027c080) X(sub_27C220, 0027c220) X(sub_27C2B0, 0027c2b0)              \
    X(sub_27C330, 0027c330) X(adminiUpdateTask_Call, 0027c3b0) X(sub_27C5A0, 0027c5a0) X(sub_27C650, 0027c650)         \
    X(sub_27C840, 0027c840) X(sub_27C8F0, 0027c8f0) X(sub_27C9E0, 0027c9e0) X(sub_27CA10, 0027ca10)                   \
    X(sub_27CA40, 0027ca40) X(adminiSeqCallBtl, 0027ca70) X(adminiSeqExitBtl, 0027caa0) X(sub_27CAE0, 0027cae0)       \
    X(sub_27CB10, 0027cb10) X(sub_27CB40, 0027cb40) X(sub_27CB50, 0027cb50) X(sub_27CB80, 0027cb80)                   \
    X(sub_27CBD0, 0027cbd0) X(btlUpdateDraw3DFrontTask, 0027cd70) X(btlUpdateDraw2DTask, 0027cda0)                    \
    X(sub_27CE50, 0027ce50) X(btlCreate, 0027ced0) X(sub_27D020, 0027d020) X(btlScrCmd_CALL_BATTLE, 0027d5e0)         \
    X(sub_27D730, 0027d730) X(sub_27D810, 0027d810) X(sub_27D8D0, 0027d8d0) X(sub_27DC00, 0027dc00)                   \
    X(sub_27DC80, 0027dc80) X(btlTableLoad, 0027dcd0) X(btlTableLoadAll, 0027de40) X(btlTablePatchForAnswer, 0027df20) \
    X(btlTableInit, 0027e180) X(btlUpdateTableReloadTask, 0027e1d0) X(sub_27E270, 0027e270) X(sub_27E2C0, 0027e2c0)   \
    X(sub_27E530, 0027e530) X(sub_27EC10, 0027ec10) X(sub_27ED20, 0027ed20) X(nullsub_12, 0027edf0)                   \
    X(sub_27EE00, 0027ee00) X(sub_27F160, 0027f160) X(sub_27F1C0, 0027f1c0) X(sub_27F2E0, 0027f2e0)                   \
    X(sub_27F2F0, 0027f2f0) X(sub_27F3E0, 0027f3e0) X(sub_27F410, 0027f410) X(sub_27F530, 0027f530)                   \
    X(sub_27F650, 0027f650) X(sub_27F680, 0027f680) X(sub_27F6D0, 0027f6d0) X(sub_27F710, 0027f710)                   \
    X(sub_27F730, 0027f730) X(sub_27F770, 0027f770) X(sub_27F790, 0027f790) X(sub_27F7C0, 0027f7c0)                   \
    X(sub_27F930, 0027f930) X(sub_27FC80, 0027fc80) X(sub_27FCF0, 0027fcf0) X(sub_27FD70, 0027fd70)                   \
    X(sub_27FD90, 0027fd90) X(sub_27FE70, 0027fe70) X(sub_27FE90, 0027fe90) X(sub_27FFB0, 0027ffb0)                   \
    X(sub_281270, 00281270) X(sub_281290, 00281290) X(sub_2812B0, 002812b0) X(sub_2813D0, 002813d0)                   \
    X(sub_2819B0, 002819b0) X(sub_2819D0, 002819d0) X(sub_281AB0, 00281ab0) X(sub_281E60, 00281e60)                   \
    X(sub_281E80, 00281e80) X(sub_282130, 00282130) X(sub_282190, 00282190) X(sub_282290, 00282290)                   \
    X(sub_2822B0, 002822b0) X(sub_282380, 00282380) X(sub_282620, 00282620) X(sub_282650, 00282650)                   \
    X(sub_282C30, 00282c30) X(sub_282C60, 00282c60) X(sub_282CD0, 00282cd0) X(sub_283510, 00283510)                   \
    X(sub_283BA0, 00283ba0) X(sub_283C00, 00283c00) X(sub_283C50, 00283c50) X(sub_283FE0, 00283fe0)                   \
    X(sub_284170, 00284170) X(sub_284190, 00284190) X(sub_2841E0, 002841e0) X(sub_284200, 00284200)                   \
    X(sub_284330, 00284330) X(sub_284350, 00284350) X(sub_2843C0, 002843c0) X(sub_2843E0, 002843e0)                   \
    X(sub_284450, 00284450) X(sub_2845E0, 002845e0) X(sub_284600, 00284600) X(sub_284670, 00284670)                   \
    X(sub_2848E0, 002848e0) X(sub_284900, 00284900) X(sub_284980, 00284980) X(sub_284B50, 00284b50)                   \
    X(sub_284B70, 00284b70) X(sub_284BE0, 00284be0) X(sub_284C70, 00284c70) X(sub_284C90, 00284c90)                   \
    X(sub_284CF0, 00284cf0) X(sub_287400, 00287400) X(sub_287490, 00287490) X(sub_287510, 00287510)                   \
    X(sub_287580, 00287580) X(btlUnitCreate, 002875a0) X(sub_2889C0, 002889c0) X(sub_288F80, 00288f80)                \
    X(sub_289650, 00289650) X(btlActionCreate, 00299e90) X(btlActionUpdateAll, 00299fb0) X(sub_29A140, 0029a140)      \
    X(sub_29A750, 0029a750) X(sub_29ABE0, 0029abe0) X(sub_29AC70, 0029ac70) X(sub_29AE40, 0029ae40)                   \
    X(nullsub_13, 0029dfb0) X(sub_29E370, 0029e370) X(sub_29E390, 0029e390) X(sub_29E3C0, 0029e3c0)                   \
    X(sub_29E400, 0029e400) X(sub_29E420, 0029e420)
P3FES_BC2_FUNCS(P3FES_BC2_DECL)
#undef P3FES_BC2_DECL
void fn_kwlnTaskGetTaskByName_00195340(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

namespace rg = p3fes::recomp_gen;

// --- the functions and the kinds of their arguments ($a0..$a3) -------------------------------------------------------
// n small number   q queue 0..3     s side 0..3      P queued packet   F fresh packet    C packet condition
// U btlUnit        A btlAction      D unit-packet data (units at +0, +4, +12, +36)       X transform data
// M motion data    E call data      V vector or 0    v vector          T table row (index) K the admini task
// k packet kind    i an id valid for the unit in $a0's side               W DatUnit or 0    S setup block or 0
// Z size 0..64     m motion -6..30  x anything       w world pointer
struct Kinds {
    const char* name;
    const char* kinds;
};
const Kinds kKinds[] = {
    {"adminiChangeSeq", "nSZn"}, {"adminiUpdateTask_Call", "K"}, {"sub_27C5A0", "K"}, {"sub_27C650", "K"},
    {"sub_27C840", "K"}, {"adminiSeqCallBtl", "nS"}, {"sub_27CB10", "nS"}, {"sub_27DC00", "x"}, {"sub_27DC80", "x"},
    {"btlTableLoad", "Tn"}, {"btlTableLoadAll", "n"}, {"sub_27E270", "w"}, {"sub_27E2C0", "w"}, {"sub_27E530", "Cn"},
    {"sub_27EC10", "kZ"}, {"sub_27ED20", "Fq"}, {"sub_27EE00", "P"}, {"sub_27F160", "q"}, {"sub_27F3E0", "E"},
    {"sub_27F410", "xx"}, {"sub_27F530", "U"}, {"sub_27F650", "Uv"}, {"sub_27F680", "Uv"}, {"sub_27F6D0", "U"},
    {"sub_27F710", "U"}, {"sub_27F730", "Ux"}, {"sub_27F770", "Ux"}, {"sub_27F790", "Ux"}, {"sub_27F7C0", "UVVV"},
    {"sub_27F930", "U"}, {"sub_27FC80", "U"}, {"sub_27FCF0", "Uv"}, {"sub_27FD70", "D"}, {"sub_27FD90", "X"},
    {"sub_27FE70", "D"}, {"sub_27FE90", "UVVV"}, {"sub_27FFB0", "Uv"}, {"sub_281270", "U"}, {"sub_281290", "U"},
    {"sub_2812B0", "U"}, {"sub_2813D0", "D"}, {"sub_2819B0", "D"}, {"sub_2819D0", "UVn"}, {"sub_281AB0", "D"},
    {"sub_281E60", "D"}, {"sub_281E80", "UUn"}, {"sub_282130", "xn"}, {"sub_282190", "D"}, {"sub_282290", "D"},
    {"sub_2822B0", "UVn"}, {"sub_282380", "D"}, {"sub_282620", "D"}, {"sub_282650", "UUn"}, {"sub_282C30", "U"},
    {"sub_282C60", "U"}, {"sub_282CD0", "U"}, {"sub_283510", "Un"}, {"sub_283BA0", "U"}, {"sub_283C00", "U"},
    {"sub_283C50", "U"}, {"sub_283FE0", "Un"}, {"sub_284170", "D"}, {"sub_284190", "M"}, {"sub_2841E0", "D"},
    {"sub_284200", "Umnn"}, {"sub_284330", "D"}, {"sub_284350", "D"}, {"sub_2843C0", "D"}, {"sub_2843E0", "Un"},
    {"sub_284450", "D"}, {"sub_2845E0", "D"}, {"sub_284600", "U"}, {"sub_284670", "D"}, {"sub_2848E0", "D"},
    {"sub_284900", "Un"}, {"sub_284980", "D"}, {"sub_284B50", "D"}, {"sub_284B70", "U"}, {"sub_284BE0", "D"},
    {"sub_284C70", "D"}, {"sub_284C90", "U"}, {"sub_284CF0", "D"}, {"sub_287490", "U"}, {"sub_287510", "U"},
    {"sub_287580", "U"}, {"btlUnitCreate", "s"}, {"sub_2889C0", "Ui"}, {"sub_288F80", "Ui"}, {"sub_289650", "siW"},
    {"sub_29ABE0", "A"}, {"sub_29AC70", "A"},
};

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
    const char* kinds;
};
std::vector<Case> make_cases() {
    std::vector<Case> v;
#define P3FES_BC2_CASE(name, addr) \
    v.push_back({#name, 0x##addr##u, &rg::fn_##name##_##addr, &rg::fn_##name##_##addr##__recomp, ""});
    P3FES_BC2_FUNCS(P3FES_BC2_CASE)
#undef P3FES_BC2_CASE
    for (Case& c : v)
        for (const Kinds& k : kKinds)
            if (std::strcmp(c.name, k.name) == 0) c.kinds = k.kinds;
    return v;
}
const std::vector<Case>& cases() {
    static const std::vector<Case> v = make_cases();
    return v;
}

// --- guest memory helpers -------------------------------------------------------------------------------------------
// Host access to guest RAM: the address masked into the 32 MiB (a stray value read back from a run never faults the host).
u8* ram(Machine& m, u32 va) { return m.at(std::min<u32>(va & 0x1FFFFFFu, 0x2000000u - 8)); }
void st8(Machine& m, u32 va, u8 v) { *ram(m, va) = v; }
void st16(Machine& m, u32 va, u16 v) { std::memcpy(ram(m, va), &v, 2); }
void st32(Machine& m, u32 va, u32 v) { std::memcpy(ram(m, va), &v, 4); }
void st64(Machine& m, u32 va, u64 v) { std::memcpy(ram(m, va), &v, 8); }
void stf(Machine& m, u32 va, float v) { std::memcpy(ram(m, va), &v, 4); }
u8 ld8(Machine& m, u32 va) { return *ram(m, va); }
u16 ld16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, ram(m, va), 2);
    return v;
}
u32 ld32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, ram(m, va), 4);
    return v;
}
u64 ld64(Machine& m, u32 va) {
    u64 v;
    std::memcpy(&v, ram(m, va), 8);
    return v;
}
float ldf(Machine& m, u32 va) {
    float v;
    std::memcpy(&v, ram(m, va), 4);
    return v;
}
u32 gp_slot(s32 off) { return static_cast<u32>(static_cast<s32>(kGp) + off); }
bool chance(std::mt19937& rng, u32 pct) { return rng() % 100 < pct; }

constexpr u32 kGBtlSlot = 0x7CE3ECu;
constexpr u32 kAdminiName = 0x7CC500u;  // "admini"

// --- the stand-ins ----------------------------------------------------------------------------------------------------
// Callees the test build does not emit, served by recorders (both bodies meet the same one; its log is compared), and
// the packet callbacks the battle worlds use that are not emitted either (an update that never finishes, one that
// finishes, a query that answers 1).
constexpr u32 kUpdNever = 0x281F20u;  // recorder -> 0
constexpr u32 kUpdDone = 0x2813F0u;   // recorder -> 1
constexpr u32 kQueryYes = 0x2849A0u;  // recorder -> 1
const u32 kRecorded[] = {0x177270, 0x1A62C0, 0x282D40, 0x2879F0, 0x287EA0, 0x288110, 0x2891E0, 0x29E4B0, 0x2BC6D0,
                         0x2D3D70, 0x2DB8D0, 0x2DB980, 0x2DD9B0, 0x2E2F30, 0x2E2F80, 0x2F8790, 0x2FF340, 0x2FF3E0,
                         0x2FF760, 0x35BC00, 0x3A2D80, 0x3B5760, 0x3B5A10, 0x3B5AB0, 0x3E0780, 0x3E0920, 0x4C9D70, 0x1A4580,
                         0x2BC2F0};
void bc2_setup(StandInWorld& w) {
    install_standard(w);
    for (u32 va : kRecorded) w.si.install_recorder(va, "rec_" + hex64(va), va == 0x3B5A10u ? 1 : 0, 4);
    w.si.install_recorder(kUpdNever, "upd_never", 0, 3);
    w.si.install_recorder(kUpdDone, "upd_done", 1, 3);
    w.si.install_recorder(kQueryYes, "query_yes", 1, 3);
}

StandInWorld* g_si[2];
Fn g_fn[2];
void thunk0(EEContext& ctx) {
    StandInsScope s(g_si[0]->si);
    g_fn[0](ctx);
}
void thunk1(EEContext& ctx) {
    StandInsScope s(g_si[1]->si);
    g_fn[1](ctx);
}

// hgp::pair (everything at every check point, the end / stop, all RAM, scratchpad, BIOS, bus) with a fresh stand-in
// world around each body, and the two call logs compared. Returns the recompiled run.
hgp::Run pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    bc2_setup(*wh);
    bc2_setup(*wr);
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what);
    expect_same_log(wh->si, wr->si, what);
    return r;
}

// One body alone (the rule checks), with its own stand-in world; returns the run and keeps the world for inspection.
struct Solo {
    hgp::Run run;
    std::unique_ptr<StandInWorld> world;
};
Solo solo(Machine& m, Fn fn, const Args& args, u32 seed = 1) {
    Solo s;
    s.world = std::make_unique<StandInWorld>();
    bc2_setup(*s.world);
    g_si[0] = s.world.get();
    g_fn[0] = fn;
    s.run = hgp::run_one(m, &thunk0, args, seed, {});
    return s;
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

// The same without hgp's check-point cap (20,000: a table file's memcpy takes more): pair_harness.h's run().
struct SoloU {
    Outcome out;
    std::unique_ptr<StandInWorld> world;
    std::string fault;  // empty = returned
};
SoloU solo_uncapped(Machine& m, Fn fn, const Args& args) {
    SoloU s;
    s.world = std::make_unique<StandInWorld>();
    bc2_setup(*s.world);
    g_si[0] = s.world.get();
    g_fn[0] = fn;
    s.fault = fault_of([&] { s.out = run(m, &thunk0, args, 1); });
    return s;
}

// --- the battle world -------------------------------------------------------------------------------------------------
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x20000u;
constexpr u32 kBtl = kWorld;                // gBtl (3,440 bytes)
constexpr u32 kUnits = kWorld + 0x1000u;    // 8 btlUnits
constexpr u32 kUnitStride = 0xA40u;
constexpr u32 kActs = kWorld + 0x6400u;     // 8 btlActions
constexpr u32 kActStride = 0x4C0u;
constexpr u32 kPkts = kWorld + 0x8C00u;     // 24 packets (144 + 112 data bytes)
constexpr u32 kPktStride = 0x100u;
constexpr u32 kDats = kWorld + 0xA400u;     // 8 DatUnits (60 bytes)
constexpr u32 kTask = kWorld + 0xA800u;     // a kwln task record (+60 = the admini work)
constexpr u32 kAdm = kWorld + 0xA900u;      // the admini work (36 bytes)
constexpr u32 kVecs = kWorld + 0xAA00u;     // 16 vectors
constexpr u32 kCallData = kWorld + 0xAB00u; // sub_27F3E0's data blocks
constexpr u32 kBlob = kWorld + 0xB000u;     // random words: models and other pointers
constexpr u32 kSetup = kWorld + 0x10000u;   // a 52-byte setup block

struct World {
    std::vector<u32> units, acts, queued, fresh, conds, data;
    u32 task = 0;
};

const std::vector<u8>& b5800() {
    static const std::vector<u8> s = read_snapshot("b_5800");
    return s;
}

// The battle tables (the arena and the section slots) of the b_5800 snapshot: real records for the unit id setters
// and the table readers.
void copy_tables(Machine& m) {
    const std::vector<u8>& s = b5800();
    if (s.empty()) return;
    copy_from_snapshot(m, s, bc::kTableArena, 0xDDB00u);
    copy_from_snapshot(m, s, 0x7CE3F0u, 0x110u);
}

float small_f(std::mt19937& rng) { return static_cast<float>(static_cast<int>(rng() % 2001) - 1000) / 8.0f; }

World battle_world(Machine& m, std::mt19937& rng) {
    World w;
    hgp::random_world(m, kWorld, kWorldSize, rng);
    copy_tables(m);
    // --- gBtl ---
    std::memset(m.at(kBtl), 0, bc::kBtlSize);
    for (u32 i = 0; i < bc::kBtlSize; i += 4)
        if (chance(rng, 20)) st32(m, kBtl + i, hgp::world_word(rng, kWorld, kWorldSize));
    u32 flags = 0;
    for (u32 bit : {0x2u, 0x8u, 0x2000u, 0x8000u, 0x80000u, 0x80u, 0x1u})
        if (chance(rng, 40)) flags |= bit;
    st32(m, kBtl + bc::kBtlFlags, flags);
    // --- units: well-formed side lists ---
    const u32 nu = 3 + rng() % 6;
    std::vector<u32> side_of(nu);
    // at most four party members (the player and the three the order lottery weighs, {40, 35, 25} at gp-26344) and
    // five enemies, as in the game
    u32 count[3] = {};
    for (u32 k = 0; k < nu; ++k) {
        u32 s = k == 0 ? 0 : k == 1 ? 1 : rng() % 3;
        if (s == 0 && count[0] == 4) s = 1;
        if (s == 1 && count[1] == 5) s = 2;
        side_of[k] = s;
        ++count[s];
    }
    for (u32 s = 0; s < 4; ++s) {
        st32(m, kBtl + bc::kBtlUnitHead + 8 * s, 0);
        st32(m, kBtl + bc::kBtlUnitTail + 8 * s, 0);
    }
    for (u32 k = 0; k < nu; ++k) {
        const u32 u = kUnits + kUnitStride * k;
        w.units.push_back(u);
        const u32 side = side_of[k];
        st8(m, u + bc::kUnSide, static_cast<u8>(side));
        const u16 id = side == 0 ? static_cast<u16>(1 + rng() % 10) : side == 1 ? static_cast<u16>(rng() % 336)
                                                                                : static_cast<u16>(rng() % 256);
        st16(m, u + bc::kUnId, chance(rng, 5) ? u16{207} : id);
        st32(m, u + bc::kUnDirty, (rng() % 4) * 2);
        u32 uf = 0;
        for (u32 bit : {0x1u, 0x2u, 0x8u, 0x20u, 0x1000u, 0x2000u})
            if (chance(rng, 30)) uf |= bit;
        st32(m, u + bc::kUnFlags, uf);
        st16(m, u + bc::kUnBusy, static_cast<u16>(rng() % 4));
        st16(m, u + bc::kUnShowFlags, static_cast<u16>(rng()));
        for (u32 i = 0; i < 3; ++i) stf(m, u + bc::kUnPos + 4 * i, small_f(rng));
        for (u32 i = 0; i < 4; ++i) stf(m, u + bc::kUnRot + 4 * i, small_f(rng) / 128.0f);
        stf(m, u + bc::kUnScale, 0.5f + static_cast<float>(rng() % 4) * 0.25f);
        for (u32 i = 0; i < 3; ++i) stf(m, u + bc::kUnCentre + 4 * i, small_f(rng));
        stf(m, u + bc::kUnHeight, 150.0f);
        stf(m, u + bc::kUnSize, 50.0f);
        st16(m, u + bc::kUnGridX, static_cast<u16>(rng() % 141));
        st16(m, u + bc::kUnGridZ, static_cast<u16>(rng() % 141));
        st16(m, u + bc::kUnMoveFlags, static_cast<u16>(rng() % 4));
        st16(m, u + bc::kUnMotion, static_cast<u16>(rng() % 4));
        st16(m, u + bc::kUnIdleMotion, static_cast<u16>(rng() % 4));
        st16(m, u + bc::kUnModelId, chance(rng, 50) ? static_cast<u16>(1 + rng() % 300) : 0);
        st32(m, u + bc::kUnModel, kBlob + 0x200 * k);
        st32(m, u + bc::kUnDat, chance(rng, 85) ? kDats + 0x40 * k : 0);
        st16(m, kDats + 0x40 * k + 8, static_cast<u16>(rng() % 3));  // hp (0 = dead now and then)
        st32(m, kDats + 0x40 * k + 12, chance(rng, 20) ? 0x80000u : 0u);  // status (bit 19: dead)
        st32(m, u + bc::kUnPersona, 0);
        // append to the side list (the btlUnitCreate rule)
        const u32 tail = ld32(m, kBtl + bc::kBtlUnitTail + 8 * side);
        st32(m, u + bc::kUnNext, 0);
        if (tail) {
            st32(m, tail + bc::kUnNext, u);
            st32(m, u + bc::kUnPrev, tail);
        } else {
            st32(m, kBtl + bc::kBtlUnitHead + 8 * side, u);
            st32(m, u + bc::kUnPrev, 0);
        }
        st32(m, kBtl + bc::kBtlUnitTail + 8 * side, u);
    }
    for (u32 k = 0; k < nu; ++k)  // party units: a persona sub-unit now and then
        if (side_of[k] == 0)
            for (u32 j = 0; j < nu; ++j)
                if (side_of[j] == 2 && chance(rng, 60)) st32(m, w.units[k] + bc::kUnPersona, w.units[j]);
    // --- actions: the combatants, pushed at the head of gBtl+332 ---
    st32(m, kBtl + bc::kBtlActionList, 0);
    u32 player = 0;
    for (u32 k = 0; k < nu && w.acts.size() < 8; ++k) {
        if (side_of[k] == 2) continue;
        const u32 a = kActs + kActStride * static_cast<u32>(w.acts.size());
        w.acts.push_back(a);
        st32(m, a + bc::kActUnit, w.units[k]);
        st16(m, a + bc::kActState, static_cast<u16>(chance(rng, 50) ? 1u : rng() % 36));
        const bool pend = chance(rng, 30);
        st16(m, a + bc::kActNextState, static_cast<u16>(pend ? rng() % 36 : 0u));
        st16(m, a + bc::kActDelay, static_cast<u16>(rng() % 3));
        st16(m, a + bc::kActReturn, static_cast<u16>(rng() % 10));
        st16(m, a + bc::kActResume, static_cast<u16>(rng() % 36));
        u32 f1 = chance(rng, 70) ? 1u : 0u, f2 = 0;
        if (chance(rng, 25)) f1 |= 4u;
        for (u32 bit : {1u, 2u, 4u, 8u, 0x10u})
            if (chance(rng, 25)) f2 |= bit;
        st16(m, a + bc::kActFlags, static_cast<u16>(f1));
        st16(m, a + bc::kActFlags2, static_cast<u16>(f2));
        const u32 head = ld32(m, kBtl + bc::kBtlActionList);
        st32(m, a + bc::kActLinkPrev, 0);
        st32(m, a + bc::kActLinkNext, head);
        if (head) st32(m, head + bc::kActLinkPrev, a);
        st32(m, kBtl + bc::kBtlActionList, a);
        if (side_of[k] == 0 && player == 0 && chance(rng, 80)) player = a;
    }
    st32(m, kBtl + bc::kBtlPlayerAction, player);
    {  // the turn order: the actions shuffled (the player first, usually), then zeros; the next-round list
        std::vector<u32> order = w.acts;
        std::shuffle(order.begin(), order.end(), rng);
        if (player && chance(rng, 80)) {
            order.erase(std::find(order.begin(), order.end(), player));
            order.insert(order.begin(), player);
        }
        if (chance(rng, 10)) order.clear();
        for (u32 i = 0; i < 12; ++i) st32(m, kBtl + bc::kBtlOrderList + 4 * i, i < order.size() ? order[i] : 0);
        for (u32 i = 0; i < 12; ++i) st32(m, kBtl + bc::kBtlOrderNext + 4 * i, 0);
        if (!w.acts.empty() && chance(rng, 30)) st32(m, kBtl + bc::kBtlOrderNext, w.acts[rng() % w.acts.size()]);
        st16(m, kBtl + bc::kBtlOrderFlags, static_cast<u16>(rng() % 16));
        st32(m, kBtl + bc::kBtlOrderTurns, rng() % 3);
    }
    // --- packets: queued ones in the four queues, fresh ones outside ---
    const u32 np = 6 + rng() % 18, nq = np - 1 - rng() % 3;
    std::vector<u64> ids;
    std::vector<u32> kinds;
    for (u32 q = 0; q < 4; ++q) {
        st32(m, kBtl + bc::kBtlPktHead + 8 * q, 0);
        st32(m, kBtl + bc::kBtlPktTail + 8 * q, 0);
    }
    const u32 kKindPool[] = {256, 260, 266, 283, 0xFF00, 0xFF01, 1538, 274};
    for (u32 k = 0; k < np; ++k) {
        ids.push_back(1 + rng() % 40 + (chance(rng, 10) ? (u64{rng() % 4} << 62) : 0));
        kinds.push_back(chance(rng, 80) ? kKindPool[rng() % 8] : rng() % 1024);
    }
    for (u32 k = 0; k < np; ++k) {
        const u32 p = kPkts + kPktStride * k;
        const bool queued = k < nq;
        for (u32 c = 0; c < 4; ++c) {
            const u32 cond = p + 16 * c;
            w.conds.push_back(cond);
            const u32 r = rng() % 100;
            const u8 kind = r < 45 ? 1 : static_cast<u8>(r % 14);
            st8(m, cond + bc::kCondKind, kind);
            u64 arg = rng() % 8;
            if (kind >= 3 && kind <= 8) arg = chance(rng, 70) ? (ids[rng() % np] & 0x3FFFFFFFFFFFFFFFull) : rng() % 64;
            if (kind == 9 || kind == 10) arg = chance(rng, 70) ? kinds[rng() % np] : rng() % 1024;
            if (kind == 11 || kind == 12) arg = ids[rng() % np] & 0x3FFFFFFFFFFFFFFFull;
            st64(m, cond + bc::kCondArg, arg);
        }
        st32(m, p + bc::kPktKind, kinds[k]);
        st8(m, p + bc::kPktPhase, queued ? static_cast<u8>(rng() % 5) : 0);
        st8(m, p + bc::kPktPaused, static_cast<u8>(chance(rng, 8) ? 1 : 0));
        u32 pf = bc::kPktLive;
        if (queued) pf |= bc::kPktQueued;
        if (chance(rng, 10)) pf |= bc::kPktKill;
        if (chance(rng, 10)) pf &= ~0x20u;
        st8(m, p + bc::kPktFlags, static_cast<u8>(pf));
        st16(m, p + bc::kPktStartDelay, static_cast<u16>(rng() % 3));
        st16(m, p + bc::kPktEndDelay, static_cast<u16>(rng() % 3));
        st32(m, p + bc::kPktAge, rng() % 10);
        st32(m, p + bc::kPktRunFrames, rng() % 4);
        st64(m, p + bc::kPktId, ids[k]);
        st64(m, p + bc::kPktOwner, ids[rng() % np] & 0x3FFFFFFFFFFFFFFFull);
        st32(m, p + bc::kPktOnQueue, chance(rng, 50) ? 0x27FD70u : 0u);
        const u32 upd[] = {0x27F2E0u, kUpdNever, kUpdDone, 0x27FD90u};
        st32(m, p + bc::kPktUpdate, upd[rng() % 4]);
        st32(m, p + bc::kPktOnEnd, chance(rng, 50) ? 0x27FE70u : 0u);
        st32(m, p + bc::kPktQuery, chance(rng, 50) ? kQueryYes : 0u);
        const u32 data = p + bc::kPktHeader;
        st32(m, p + bc::kPktData, data);
        w.data.push_back(data);
        for (u32 off : {0u, 4u, 12u, 36u}) st32(m, data + off, w.units[rng() % nu]);
        st16(m, data + bc::kXfMask, static_cast<u16>(rng() % 8));  // (the transform update's mask)
        if (queued) {
            const u32 q = rng() % 4;
            st8(m, p + bc::kPktQueue, static_cast<u8>(q));
            const u32 tail = ld32(m, kBtl + bc::kBtlPktTail + 8 * q);
            st32(m, p + bc::kPktNext, 0);
            if (tail) {
                st32(m, tail + bc::kPktNext, p);
                st32(m, p + bc::kPktPrev, tail);
            } else {
                st32(m, kBtl + bc::kBtlPktHead + 8 * q, p);
                st32(m, p + bc::kPktPrev, 0);
            }
            st32(m, kBtl + bc::kBtlPktTail + 8 * q, p);
            w.queued.push_back(p);
        } else {
            w.fresh.push_back(p);
        }
    }
    // --- sub_27F3E0's data blocks: fn = a finishing update or a recorder ---
    for (u32 i = 0; i < 4; ++i) {
        st32(m, kCallData + 8 * i, i % 2 ? 0x27F2E0u : kUpdNever);
        st32(m, kCallData + 8 * i + 4, rng() % 64);
    }
    // --- vectors ---
    for (u32 i = 0; i < 64; ++i) stf(m, kVecs + 4 * i, small_f(rng));
    // --- the admini task and its work ---
    st32(m, kTask + 60, kAdm);
    u32 af = 0;
    for (u32 bit : {0x1u, 0x2u, 0x4u, 0x8u, 0x10000u})
        if (chance(rng, 35)) af |= bit;
    st32(m, kAdm + bc::kAdmFlags, af);
    st32(m, kAdm + bc::kAdmFrames, rng() % 100);
    st8(m, kAdm + bc::kAdmSeq, static_cast<u8>(static_cast<s32>(rng() % 9) - 1));
    st8(m, kAdm + bc::kAdmNextSeq, static_cast<u8>(static_cast<s32>(rng() % 9) - 1));
    st8(m, kAdm + bc::kAdmRing, static_cast<u8>(rng() % 8));
    for (u32 i = 0; i < 8; ++i) {
        st8(m, kAdm + bc::kAdmRingSeq + i, static_cast<u8>(static_cast<s32>(rng() % 9) - 1));
        st8(m, kAdm + bc::kAdmRingFlags + i, static_cast<u8>(rng() % 2));
    }
    st32(m, kAdm + bc::kAdmParam, chance(rng, 50) ? 0u : kSetup);
    st8(m, kAdm + bc::kAdmParamSize, 52);
    st8(m, kAdm + bc::kAdmDelay, static_cast<u8>(rng() % 3));
    w.task = kTask;
    // --- the setup block ---
    std::memset(m.at(kSetup), 0, 52);
    st16(m, kSetup + 24, static_cast<u16>(rng() % 300));
    st16(m, kSetup + 26, static_cast<u16>(rng() % 4));
    // --- the $gp slots ---
    st32(m, kGBtlSlot, chance(rng, 5) ? 0u : kBtl);
    st64(m, gp_slot(bc::kGpUidCounter), chance(rng, 10) ? 0x3FFFFFFFFFFFFFFDull + rng() % 3 : 40 + rng() % 1000);
    st16(m, gp_slot(bc::kGpModelIdCounter), static_cast<u16>(250 + rng() % 270));
    st32(m, gp_slot(bc::kGpUnitSerial), chance(rng, 10) ? 0xFFFFFFEu + rng() % 3 : rng() % 1000);
    st32(m, gp_slot(bc::kGpActionSerial), chance(rng, 10) ? 0xFFFFFFEu + rng() % 3 : rng() % 1000);
    st32(m, gp_slot(bc::kGpGameOverLatch), rng() % 2);
    st32(m, gp_slot(bc::kGpTblArenaOff), chance(rng, 50) ? 0u : (rng() % 64) * 16);
    st32(m, gp_slot(bc::kGpTblRequest), 0);
    st32(m, gp_slot(bc::kGpTblReloadIdx), rng() % 8);
    return w;
}

template <class T>
T pick(const std::vector<T>& v, std::mt19937& rng, T fallback) {
    return v.empty() ? fallback : v[rng() % v.size()];
}

u64 arg_of(Machine& m, char kind, const World& w, std::mt19937& rng, const Args& prev) {
    if (rng() % 100 < 4) return hgp::random_arg(rng, kWorld, kWorldSize);  // anything, now and then
    switch (kind) {
    case 'n': return rng() % 8;
    case 'q': return rng() % 4;
    case 's': return rng() % (chance(rng, 90) ? 3 : 4);
    case 'P': return sx(pick(w.queued, rng, kPkts));
    case 'F': return sx(pick(w.fresh, rng, kPkts));
    case 'C': return sx(pick(w.conds, rng, kPkts));
    case 'U': return sx(pick(w.units, rng, kUnits));
    case 'A': return sx(pick(w.acts, rng, kActs));
    case 'D':
    case 'X':
    case 'M': {
        const u32 d = pick(w.data, rng, kPkts + bc::kPktHeader);
        if (kind == 'M') {  // the motion packet's data
            st16(m, d + bc::kMoMotion, static_cast<u16>(static_cast<s32>(rng() % 37) - 6));
            st16(m, d + bc::kMoMode, static_cast<u16>(rng() % 4));
            stf(m, d + bc::kMoSpeed, 1.0f);
            st16(m, d + bc::kMoFlags, static_cast<u16>(rng() % 4));
        }
        return sx(d);
    }
    case 'E': return sx(kCallData + 8 * (rng() % 4));
    case 'V': return chance(rng, 25) ? 0 : sx(kVecs + 16 * (rng() % 15));
    case 'v': return sx(kVecs + 16 * (rng() % 15));
    case 'T': return sx(bc::kTableFiles + bc::kTableFileRow * (rng() % 8));
    case 'K': return sx(w.task);
    case 'k': return rng() % 0x10000;
    case 'i': {  // an id valid for the side of the unit in $a0
        const u32 u = static_cast<u32>(prev[0]);
        const u8 side = (u >= kWorld && u < kWorld + kWorldSize) ? ld8(m, u + bc::kUnSide) : 0;
        if (side == 0) return 1 + rng() % 10;
        if (side == 1) return rng() % 336;
        return rng() % 256;
    }
    case 'W': return chance(rng, 30) ? 0 : sx(kDats + 0x40 * (rng() % 8));
    case 'S': return chance(rng, 20) ? 0 : sx(kSetup);
    case 'Z': return rng() % 65;
    case 'm': return sx(static_cast<u32>(static_cast<s32>(rng() % 37) - 6));
    case 'w': return sx(kWorld + 0x10 * (rng() % 0x100));
    default: return hgp::random_arg(rng, kWorld, kWorldSize);
    }
}

Args args_for(Machine& m, const Case& c, const World& w, std::mt19937& rng) {
    Args a{};
    const std::size_t n = std::strlen(c.kinds);
    for (unsigned i = 0; i < 4; ++i) a[i] = i < n ? arg_of(m, c.kinds[i], w, rng, a) : hgp::random_arg(rng, kWorld, kWorldSize);
    // btlTableLoad: synchronous most of the time (the async path polls H_Cdvd_IsFileLoaded)
    if (std::strcmp(c.name, "btlTableLoad") == 0) a[1] = chance(rng, 75) ? 1 : 0;
    return a;
}

std::unique_ptr<Machine> new_machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    write_rw_slots(*m);
    return m;
}

}  // namespace

TEST_CASE("game(battle_core2): every body equals its recompiled body on random worlds") {
    auto m = new_machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 24;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int pairs = 0, stops = 0;
    for (const Case& c : cases()) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("random worlds: " << pairs << " pairs over " << cases().size() << " functions, " << stops << " ended at a compared stop");
}

TEST_CASE("game(battle_core2): every body equals its recompiled body on battle worlds") {
    auto m = new_machine();
    if (!m) return;
    if (b5800().empty()) MESSAGE("note: extracted/_ours/b_5800 absent -- the battle tables stay zero");
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 40;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int pairs = 0, stops = 0;
    std::string always;
    for (const Case& c : cases()) {
        if (only && std::string(only) != c.name) continue;
        int st = 0;
        std::string why;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 104729u + c.addr};
            const World w = battle_world(*m, rng);
            const Args a = args_for(*m, c, w, rng);
            const hgp::Run r = pair(*m, c.hand, c.recomp, a, seed, c.name);
            if (r.stopped) {
                ++st;
                if (why.empty()) why = r.what + " at " + hex64(r.stop_pc);
            }
        }
        pairs += static_cast<int>(seeds);
        stops += st;
        if (st == static_cast<int>(seeds)) always += std::string(" ") + c.name + " (" + why + ")";
    }
    MESSAGE("battle worlds: " << pairs << " pairs, " << stops << " ended at a compared stop; always stopped:"
                              << (always.empty() ? " none" : always));
}

// The real objects of a snapshot: the lists of gBtl, the admini task.
struct SnapObjects {
    std::vector<u32> units, acts, queued, conds, data;
    u32 task = 0;
};
SnapObjects snap_objects(Machine& m) {
    SnapObjects o;
    const u32 g = ld32(m, kGBtlSlot);
    if (g) {
        for (u32 a = ld32(m, g + bc::kBtlActionList), n = 0; a && n < 32; a = ld32(m, a + bc::kActLinkNext), ++n) o.acts.push_back(a);
        for (u32 s = 0; s < 4; ++s)
            for (u32 u = ld32(m, g + bc::kBtlUnitHead + 8 * s), n = 0; u && n < 32; u = ld32(m, u + bc::kUnNext), ++n) o.units.push_back(u);
        for (u32 q = 0; q < 4; ++q)
            for (u32 p = ld32(m, g + bc::kBtlPktHead + 8 * q), n = 0; p && n < 64; p = ld32(m, p + bc::kPktNext), ++n) {
                o.queued.push_back(p);
                for (u32 c = 0; c < 4; ++c) o.conds.push_back(p + 16 * c);
                if (const u32 d = ld32(m, p + bc::kPktData)) o.data.push_back(d);
            }
    }
    // the admini task, through the hand-written kwln lookup
    o.task = static_cast<u32>(v0_of(solo(m, &rg::fn_kwlnTaskGetTaskByName_00195340, {sx(kAdminiName), 0, 0, 0}).run));
    return o;
}

TEST_CASE("game(battle_core2): every body on the replay snapshots' real state") {
    int ran = 0, used = 0, stops = 0;
    for (const char* dir : {"b_5800", "battle_ref_6150", "dorm_replay_4900"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << "/eeMemory.bin not found");
            continue;
        }
        ++used;
        auto m = new_machine();
        if (!m) return;
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        write_rw_slots(*m);
        const SnapObjects o = snap_objects(*m);
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        write_rw_slots(*m);
        MESSAGE(std::string(dir) << ": " << o.acts.size() << " actions, " << o.units.size() << " units, " << o.queued.size()
                    << " packets, admini task " << hex64(o.task));
        std::mt19937 rng{0xB7C2u};
        World w;  // the snapshot's objects in the world's shape (arguments only)
        w.units = o.units;
        w.acts = o.acts;
        w.queued = o.queued;
        w.fresh = {};
        w.conds = o.conds;
        w.data = o.data;
        w.task = o.task;
        for (const Case& c : cases()) {
            const int reps = std::strlen(c.kinds) ? 4 : 1;
            for (int rep = 0; rep < reps; ++rep) {
                Args a{};
                const std::size_t n = std::strlen(c.kinds);
                for (unsigned i = 0; i < 4; ++i) {
                    const char k = i < n ? c.kinds[i] : 'n';
                    // world-only kinds become small values or stand-in heap pointers (zero in every snapshot)
                    const bool world_only = k == 'F' || k == 'E' || k == 'V' || k == 'v' || k == 'S' || k == 'W' || k == 'w';
                    a[i] = world_only ? sx(kStandInHeap + 0x200000u + 0x100u * (rng() % 64)) : arg_of(*m, k, w, rng, a);
                    if ((k == 'P' && o.queued.empty()) || (k == 'U' && o.units.empty()) || (k == 'A' && o.acts.empty()) ||
                        (k == 'C' && o.conds.empty()) || ((k == 'D' || k == 'X' || k == 'M') && o.data.empty()))
                        a[i] = sx(kStandInHeap + 0x200000u + 0x100u * (rng() % 64));
                }
                if (std::strcmp(c.name, "btlTableLoad") == 0) a[1] = 1;
                stops += pair(*m, c.hand, c.recomp, a, rng(), c.name).stopped ? 1 : 0;
                ++ran;
                std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
                write_rw_slots(*m);
            }
        }
    }
    MESSAGE("snapshots: " << ran << " pairs on " << used << " snapshot(s), " << stops << " ended at a compared stop");
}

// --- documented rules ----------------------------------------------------------------------------------------------

// The host model of a packet condition (sub_27E530).
bool host_cond(Machine& m, u32 cond, u32 age) {
    const u8 kind = ld8(m, cond);
    const u64 arg = ld64(m, cond + 8);
    const u32 g = ld32(m, kGBtlSlot);
    auto find = [&](u32 off, bool by_kind) -> u32 {
        for (u32 q = 0; q < 4; ++q)
            for (u32 p = ld32(m, g + bc::kBtlPktHead + 8 * q); p; p = ld32(m, p + bc::kPktNext)) {
                const bool match = by_kind ? ld16(m, p + bc::kPktKind) == static_cast<u16>(arg)
                                           : (ld64(m, p + off) & 0x3FFFFFFFFFFFFFFFull) == arg;
                if (match && (ld8(m, p + bc::kPktFlags) & 0x20)) return p;
            }
        return 0;
    };
    switch (kind) {
    case 1: return true;
    case 2: return static_cast<s32>(age) >= static_cast<s32>(static_cast<u32>(arg));
    case 3: return find(bc::kPktId, false) != 0;
    case 4: return find(bc::kPktId, false) == 0;
    case 5: {
        const u32 p = find(bc::kPktId, false);
        return p == 0 || ld8(m, p + bc::kPktPhase) == 2;
    }
    case 6: return find(bc::kPktOwner, false) != 0;
    case 7: return find(bc::kPktOwner, false) == 0;
    case 8: {
        const u32 p = find(bc::kPktOwner, false);
        return p == 0 || ld8(m, p + bc::kPktPhase) == 2;
    }
    case 9: return find(0, true) != 0;
    case 10: return find(0, true) == 0;
    case 11:
    case 12: {
        const u32 p = find(kind == 11 ? bc::kPktId : bc::kPktOwner, false);
        if (!p) return true;
        const u32 q = ld32(m, p + bc::kPktQuery);
        return q == kQueryYes;  // the world's only query answers 1
    }
    default: return false;
    }
}

std::vector<u8> read_file(const std::string& path) {
    std::ifstream f(path, std::ios::binary);
    return std::vector<u8>((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

TEST_CASE("game(battle_core2): the battle core follows the documented rules") {
    auto m = new_machine();
    if (!m) return;
    std::mt19937 rng{0xC0DEu};
    int checks = 0;

    // 1. btlGetUID (sub_27CB80): ++counter, 1 after 0x3FFFFFFFFFFFFFFE.
    for (u64 start : {u64{5}, u64{0x3FFFFFFFFFFFFFFDull}, u64{0x3FFFFFFFFFFFFFFEull}}) {
        st64(*m, gp_slot(bc::kGpUidCounter), start);
        const Solo s = solo(*m, &rg::fn_sub_27CB80_0027cb80, {0, 0, 0, 0});
        const u64 want = start + 1 >= 0x3FFFFFFFFFFFFFFFull ? 1 : start + 1;
        CHECK(v0_of(s.run) == want);
        CHECK(ld64(*m, gp_slot(bc::kGpUidCounter)) == want);
        checks += 2;
    }

    // 2. btlPacketAlloc (sub_27EC10) and btlPacketQueue (sub_27ED20).
    for (int rep = 0; rep < 20; ++rep) {
        const World w = battle_world(*m, rng);
        st32(*m, kGBtlSlot, kBtl);
        const u32 kind = rng() % 0x10000, size = rng() % 65;
        Solo s = solo(*m, &rg::fn_sub_27EC10_0027ec10, {kind, size, 0, 0});
        const u32 p = static_cast<u32>(v0_of(s.run));
        REQUIRE(p >= kStandInHeap);
        CHECK(s.world->heap.size_of(p) >= ((144 + size + 15) & ~15u));
        CHECK(ld32(*m, p + bc::kPktKind) == kind);
        CHECK(ld8(*m, p + 0) == 1);
        CHECK(ld8(*m, p + 16) == 1);
        CHECK(ld8(*m, p + 32) == 1);
        CHECK(ld8(*m, p + 48) == 1);
        CHECK(ld32(*m, p + bc::kPktData) == (size > 0 ? p + 144 : 0u));
        CHECK(ld8(*m, p + bc::kPktFlags) == 0x31);
        checks += 8;
        // queue a fresh world packet with an on-queue callback that holds its unit
        const u32 f = w.fresh.empty() ? w.queued.back() : w.fresh.front();
        if (!w.fresh.empty()) {
            const u32 q = rng() % 4;
            st32(*m, f + bc::kPktOnQueue, 0x27FD70u);
            const u32 unit = ld32(*m, ld32(*m, f + bc::kPktData));
            const u16 busy = ld16(*m, unit + bc::kUnBusy);
            const u32 tail = ld32(*m, kBtl + bc::kBtlPktTail + 8 * q);
            const u64 ctr = ld64(*m, gp_slot(bc::kGpUidCounter));
            const Solo sq = solo(*m, &rg::fn_sub_27ED20_0027ed20, {sx(f), q, 0, 0});
            const u64 id = ctr + 1 >= 0x3FFFFFFFFFFFFFFFull ? 1 : ctr + 1;
            CHECK(v0_of(sq.run) == id);
            CHECK(ld64(*m, f + bc::kPktId) == id);
            CHECK(ld32(*m, kBtl + bc::kBtlPktTail + 8 * q) == f);
            CHECK(ld32(*m, f + bc::kPktPrev) == tail);
            CHECK(ld32(*m, f + bc::kPktNext) == 0);
            if (tail) {
                CHECK(ld32(*m, tail + bc::kPktNext) == f);
            } else {
                CHECK(ld32(*m, kBtl + bc::kBtlPktHead + 8 * q) == f);
            }
            CHECK(static_cast<u32>(ld8(*m, f + bc::kPktQueue)) == q);
            CHECK(ld8(*m, f + bc::kPktPhase) == 0);
            CHECK((ld8(*m, f + bc::kPktFlags) & bc::kPktQueued) != 0);
            CHECK(ld16(*m, unit + bc::kUnBusy) == static_cast<u16>(busy + 1));
            checks += 10;
        }
    }

    // 3. The 12 condition kinds (sub_27E530) against the host model.
    {
        int n = 0;
        for (int rep = 0; rep < 60; ++rep) {
            const World w = battle_world(*m, rng);
            st32(*m, kGBtlSlot, kBtl);
            for (u32 cond : w.conds) {
                if (chance(rng, 70)) continue;
                const u32 age = rng() % 10;
                const bool want = host_cond(*m, cond, age);
                const Solo s = solo(*m, &rg::fn_sub_27E530_0027e530, {sx(cond), age, 0, 0});
                REQUIRE(!s.run.stopped);
                INFO("kind " << unsigned(ld8(*m, cond)) << " arg " << hex64(ld64(*m, cond + 8)) << " age " << age);
                CHECK((v0_of(s.run) != 0) == want);
                ++n;
            }
        }
        checks += n;
        MESSAGE("conditions checked: " << n);
    }

    // 4. The packet phase machine (sub_27EE00): a packet with both start conditions "always", start delay d0, an update
    //    that finishes at once, end conditions "always", end delay d1: phase 0 -> 1 -> 2 -> 3 -> 4 in the first frame
    //    as far as the delays allow, then the delays count down one per frame, then it is unlinked and freed.
    for (int rep = 0; rep < 12; ++rep) {
        const World w = battle_world(*m, rng);
        st32(*m, kGBtlSlot, kBtl);
        const u32 q = rng() % 4;
        // a packet of our own, allocated and queued by the bodies themselves
        const u32 d0 = rng() % 3, d1 = rng() % 3;
        Solo s = solo(*m, &rg::fn_sub_27F2F0_0027f2f0, {0, 0, 0, 0});  // kind 0xFF00, update = done at once
        const u32 p = static_cast<u32>(v0_of(s.run));
        REQUIRE(p >= kStandInHeap);
        st16(*m, p + bc::kPktStartDelay, static_cast<u16>(d0));
        st16(*m, p + bc::kPktEndDelay, static_cast<u16>(d1));
        auto world = std::move(s.world);  // keep the heap: the packet lives in it
        g_si[0] = world.get();
        g_fn[0] = &rg::fn_sub_27ED20_0027ed20;
        hgp::run_one(*m, &thunk0, {sx(p), q, 0, 0}, 1, {});
        // frame 1: phase 0 -> 1 (conditions hold), the start delay d0 -> d0 - 1 or on to running
        int frames = 0;
        bool freed = false;
        for (; frames < 10 && !freed; ++frames) {
            g_fn[0] = &rg::fn_sub_27EE00_0027ee00;
            hgp::run_one(*m, &thunk0, {sx(p), 0, 0, 0}, 1, {});
            freed = world->heap.size_of(p) == 0;
        }
        // frames: d0 frames of start delay + the frame that runs the update and reaches the end delay + d1 frames
        CHECK(freed);
        CHECK(frames == static_cast<int>(d0 + d1 + 1));
        bool in_queue = false;
        for (u32 x = ld32(*m, kBtl + bc::kBtlPktHead + 8 * q); x; x = ld32(*m, x + bc::kPktNext)) in_queue |= x == p;
        CHECK(!in_queue);
        checks += 3;
    }

    // 5. btlTableLoad on the real files: each section of the file lands 16-aligned in the arena, in order.
    {
        const std::string root = extracted_root();
        int files = 0;
        for (u32 row = 0; row < 8; ++row) {
            const u32 r = bc::kTableFiles + bc::kTableFileRow * row;
            const std::string name = m->str(ld32(*m, r + bc::kTblName));
            // the main game's file (The Answer's _F files are taken when sub_17D800() says so: not in this world)
            auto wcd = std::make_unique<StandInWorld>();
            bc2_setup(*wcd);
            const std::string host = wcd->cd.host_path(name);
            const std::vector<u8> file = host.empty() ? std::vector<u8>{} : read_file(host);
            if (file.empty()) {
                MESSAGE("SKIP: " << name << " not found under " << root);
                continue;
            }
            st32(*m, gp_slot(bc::kGpTblArenaOff), 0);
            st32(*m, gp_slot(bc::kGpTblRequest), 0);
            const SoloU s = solo_uncapped(*m, &rg::fn_btlTableLoad_0027dcd0, {sx(r), 1, 0, 0});
            INFO(name << ": " << s.fault << " (missing: "
                      << (s.world->cd.missing.empty() ? std::string("-") : s.world->cd.missing.front()) << ")");
            REQUIRE(s.fault.empty());
            CHECK(s.out.v0 == 1);
            CHECK(ld32(*m, gp_slot(bc::kGpTblRequest)) == 0);
            u32 off = 0, sec = 0;
            for (u32 k = 0; k < 20; ++k) {
                const u32 dst = ld32(*m, r + bc::kTblDst + 8 * k);
                if (dst == 0) break;
                REQUIRE(sec + 4 <= file.size());
                u32 size;
                std::memcpy(&size, file.data() + sec, 4);
                CHECK(ld32(*m, dst) == bc::kTableArena + off);
                CHECK(std::memcmp(m->at(bc::kTableArena + off), file.data() + sec + 4, std::min<std::size_t>(size, file.size() - sec - 4)) == 0);
                off += (size + 15) & ~15u;
                sec += (size + 4 + 15) & ~15u;
                checks += 2;
            }
            CHECK(ld32(*m, gp_slot(bc::kGpTblArenaOff)) == off);
            checks += 3;
            ++files;
        }
        MESSAGE("table files checked: " << files);
    }

    // 6. btlUnitCreate: the defaults and the tail of the side's list; btlActionCreate: the head of the action list.
    for (int rep = 0; rep < 10; ++rep) {
        const World w = battle_world(*m, rng);
        st32(*m, kGBtlSlot, kBtl);
        const u32 side = rng() % 4;
        for (u32 off = 392; off < 412; off += 4) st32(*m, kBtl + off, 0);  // the BED pool lists sub_2BBC00 / sub_2BB7D0 append to
        const u32 tail = ld32(*m, kBtl + bc::kBtlUnitTail + 8 * side);
        const u32 serial = ld32(*m, gp_slot(bc::kGpUnitSerial));
        Solo s = solo(*m, &rg::fn_btlUnitCreate_002875a0, {side, 0, 0, 0});
        const u32 u = static_cast<u32>(v0_of(s.run));
        INFO("btlUnitCreate: " << s.run.what << " at " << hex64(s.run.stop_pc));
        REQUIRE(!s.run.stopped);
        REQUIRE(u >= kStandInHeap);
        REQUIRE(u < kStandInHeap + kStandInHeapSize);
        CHECK(static_cast<u32>(ld8(*m, u + bc::kUnSide)) == side);
        CHECK(ld32(*m, u + bc::kUnSerial) == (serial >= 0xFFFFFFFu ? 1u : serial));
        CHECK(ldf(*m, u + bc::kUnHeight) == 150.0f);
        CHECK(ldf(*m, u + bc::kUnSize) == 50.0f);
        CHECK(ldf(*m, u + bc::kUnCentre + 4) == 75.0f);
        CHECK(ldf(*m, u + bc::kUnScale) == 1.0f);
        CHECK(ldf(*m, u + bc::kUnRot + 12) == 1.0f);
        CHECK(ldf(*m, u + bc::kUnHalfWidth) == (side == 0 ? 4.0f : 7.0f));
        CHECK(static_cast<s8>(ld8(*m, u + bc::kUnFormSlot)) == -1);
        CHECK(ld32(*m, u + bc::kUnColour) == 0xFFFFFFFFu);
        CHECK(ld32(*m, kBtl + bc::kBtlUnitTail + 8 * side) == u);
        CHECK(ld32(*m, u + bc::kUnPrev) == tail);
        CHECK(ld32(*m, u + bc::kUnNext) == 0);
        if (tail) {
            CHECK(ld32(*m, tail + bc::kUnNext) == u);
        } else {
            CHECK(ld32(*m, kBtl + bc::kBtlUnitHead + 8 * side) == u);
        }
        checks += 14;
        const u32 head = ld32(*m, kBtl + bc::kBtlActionList);
        Solo sa = solo(*m, &rg::fn_btlActionCreate_00299e90, {0, 0, 0, 0});
        if (sa.run.stopped) continue;  // sBtlActionTbl[0].init through a random world
        const u32 a = static_cast<u32>(v0_of(sa.run));
        REQUIRE(a >= kStandInHeap);
        REQUIRE(a < kStandInHeap + kStandInHeapSize);
        CHECK(ld32(*m, kBtl + bc::kBtlActionList) == a);
        CHECK(ld32(*m, a + bc::kActLinkNext) == head);
        CHECK(ld32(*m, a + bc::kActLinkPrev) == 0);
        if (head) {
            CHECK(ld32(*m, head + bc::kActLinkPrev) == a);
        }
        CHECK(ld16(*m, a + bc::kActReturn) == 8);
        CHECK(ld16(*m, a + bc::kActState) == 0);
        CHECK(ld16(*m, a + bc::kActRand) < 60);
        CHECK(static_cast<s32>(ld32(*m, a + bc::kAct36)) == -1);
        checks += 8;
    }

    // 7. The turn-order shuffle (sub_29A750): the player action first, every other action exactly once, zeros after.
    {
        int n = 0;
        for (int rep = 0; rep < 40; ++rep) {
            const World w = battle_world(*m, rng);
            st32(*m, kGBtlSlot, kBtl);
            std::multiset<u32> before;
            const u32 player = ld32(*m, kBtl + bc::kBtlPlayerAction);
            for (u32 i = 0; i < 12; ++i) {
                const u32 a = ld32(*m, kBtl + bc::kBtlOrderList + 4 * i);
                if (!a) break;
                const u8 side = ld8(*m, ld32(*m, a + bc::kActUnit) + bc::kUnSide);
                if (a != player && side <= 1) before.insert(a);
            }
            const Solo s = solo(*m, &rg::fn_sub_29A750_0029a750, {0, 0, 0, 0});
            if (s.run.stopped) continue;
            CHECK(ld32(*m, kBtl + bc::kBtlOrderList) == player);
            std::multiset<u32> after;
            u32 i = 1;
            for (; i < 12; ++i) {
                const u32 a = ld32(*m, kBtl + bc::kBtlOrderList + 4 * i);
                if (!a) break;
                after.insert(a);
            }
            for (; i < 12; ++i) CHECK(ld32(*m, kBtl + bc::kBtlOrderList + 4 * i) == 0);
            CHECK(after == before);
            checks += 2;
            ++n;
        }
        MESSAGE("order shuffles checked: " << n);
    }

    // 8. The turn start (sub_29AE40): the head of the order in StandBy gets its return state and enters Start (2).
    {
        int n = 0;
        for (int rep = 0; rep < 60; ++rep) {
            const World w = battle_world(*m, rng);
            st32(*m, kGBtlSlot, kBtl);
            for (u32 i = 0; i < 12; ++i) st32(*m, kBtl + bc::kBtlOrderNext + 4 * i, 0);
            st16(*m, kBtl + bc::kBtlOrderFlags, 1 | 8);  // active, a turn may start, no reshuffle
            const u32 head = ld32(*m, kBtl + bc::kBtlOrderList);
            if (!head) continue;
            st16(*m, head + bc::kActState, 1);
            st16(*m, head + bc::kActNextState, 0);
            const u32 flags = ld32(*m, kBtl + bc::kBtlFlags);
            const u32 turns = ld32(*m, kBtl + bc::kBtlOrderTurns);
            const u8 side = ld8(*m, ld32(*m, head + bc::kActUnit) + bc::kUnSide);
            const Solo s = solo(*m, &rg::fn_sub_29AE40_0029ae40, {0, 0, 0, 0});
            if (s.run.stopped) continue;  // the Start state's init through a random world
            if (flags & 0x80000u) {
                CHECK(ld32(*m, kBtl + bc::kBtlOrderTurns) == turns);
                ++n;
                continue;
            }
            const u32 want = side != 0 ? 8u : (flags & 0x2000u) ? 9u : (ld32(*m, kBtl + bc::kBtlPlayerAction) == head) ? 5u : 8u;
            CHECK(static_cast<u32>(ld16(*m, head + bc::kActReturn)) == want);
            CHECK(ld32(*m, kBtl + bc::kBtlOrderTurns) == turns + 1);
            CHECK((ld16(*m, kBtl + bc::kBtlOrderFlags) & 8) == 0);
            checks += 3;
            ++n;
        }
        MESSAGE("turn starts checked: " << n);
    }

    // 9. The unit accessors: the grid position (sub_27F7C0), the transform setters' dirty bit.
    for (int rep = 0; rep < 20; ++rep) {
        const World w = battle_world(*m, rng);
        st32(*m, kGBtlSlot, kBtl);
        const u32 u = w.units[rng() % w.units.size()];
        const Solo s = solo(*m, &rg::fn_sub_27F7C0_0027f7c0, {sx(u), sx(kVecs), 0, 0});
        REQUIRE(!s.run.stopped);
        CHECK(ldf(*m, kVecs) == static_cast<float>(25 * static_cast<s16>(ld16(*m, u + bc::kUnGridX)) - 1750));
        CHECK(ldf(*m, kVecs + 4) == ldf(*m, u + bc::kUnPos + 4));
        CHECK(ldf(*m, kVecs + 8) == static_cast<float>(25 * static_cast<s16>(ld16(*m, u + bc::kUnGridZ)) - 1750));
        st32(*m, u + bc::kUnDirty, 0);
        const bool locked = (ld32(*m, u + bc::kUnFlags) & 0x2000u) != 0;
        const float before = ldf(*m, u + bc::kUnRot);
        stf(*m, kVecs + 16, 0.25f);
        solo(*m, &rg::fn_sub_27F680_0027f680, {sx(u), sx(kVecs + 16), 0, 0});
        CHECK(ldf(*m, u + bc::kUnRot) == (locked ? before : 0.25f));
        CHECK((ld32(*m, u + bc::kUnDirty) & 4) == (locked ? 0u : 4u));
        checks += 5;
    }
    MESSAGE("documented-rule checks: " << checks);
}

#else

TEST_CASE("game(battle_core2): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
