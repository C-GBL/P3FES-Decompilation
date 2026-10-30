// Pair tests for slice field3, part kosaka (game/src/field/field3_kosaka.cpp): the "battle kosaka" encounter task,
// the navigator's supporter proc and the virtual pad task. Every body against its recompiled body, compared by
// tests/game/handgen_pairs.h: the whole register file and cycle count at every check point and at the return / stop,
// all 32 MiB of RAM (the dead stack included), the scratchpad, the BIOS window and the bus log.
//   1. every function on random worlds (the p3fes_handgen skeleton);
//   2. the real world: the Tartarus snapshot climb_ref_17000 (two party members in the field, the pad task, the enemy
//      pop scheduler, the RW engine state), with kosaka works / encounter instances / pad inputs built on top, and the
//      callees this build does not emit served by test stand-ins (tests/game/stand_ins.h: the RW heap behind the
//      memory slots, recorders for the party panel, the EPL effects, the animation calls, the script-task creation);
//      both bodies of a pair meet identical stand-in worlds (their call logs are compared too). Runs that reach a callee
//      neither emitted nor stood in (the sound driver below sub_10A4E0, ...) stop there identically, and are counted;
//   3. documented-rule checks on the recompiled run's output (26_field.md 7.2 and the function comments): the slot
//      table 0x875A40, the turn period 120 / 22, the Reaper flag, the battler counts, the supporter's states and
//      stamps, the disjoint HP lists, the pad locks and idle counter, the creators' work fields.
// Skips cleanly without the ELF or the snapshot.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/field3_kosaka.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <map>
#include <vector>
#include <cstdlib>
#include <memory>
#include <random>
#include <string>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_datGetFlag_0016f190(EEContext&);  // the flag word reader (emitted)
void fn_K_FldCamera_UpdateBattleKosakaTask_001d7d40(EEContext&);  // generated body
void fn_K_FldCamera_UpdateBattleKosakaTask_001d7d40__recomp(EEContext&);  // recompiled
void fn_K_FldCamera_DestroyBattleKosakaTask_001d89b0(EEContext&);  // generated body
void fn_K_FldCamera_DestroyBattleKosakaTask_001d89b0__recomp(EEContext&);  // recompiled
void fn_K_Battle_CreateBattleTask_001d8b00(EEContext&);  // generated body
void fn_K_Battle_CreateBattleTask_001d8b00__recomp(EEContext&);  // recompiled
void fn_sub_1D8CB0_001d8cb0(EEContext&);  // generated body
void fn_sub_1D8CB0_001d8cb0__recomp(EEContext&);  // recompiled
void fn_sub_1D8CF0_001d8cf0(EEContext&);  // generated body
void fn_sub_1D8CF0_001d8cf0__recomp(EEContext&);  // recompiled
void fn_sub_1D8E60_001d8e60(EEContext&);  // generated body
void fn_sub_1D8E60_001d8e60__recomp(EEContext&);  // recompiled
void fn_sub_1D9310_001d9310(EEContext&);  // generated body
void fn_sub_1D9310_001d9310__recomp(EEContext&);  // recompiled
void fn_sub_1D94D0_001d94d0(EEContext&);  // generated body
void fn_sub_1D94D0_001d94d0__recomp(EEContext&);  // recompiled
void fn_sub_1D96A0_001d96a0(EEContext&);  // generated body
void fn_sub_1D96A0_001d96a0__recomp(EEContext&);  // recompiled
void fn_sub_1D9860_001d9860(EEContext&);  // generated body
void fn_sub_1D9860_001d9860__recomp(EEContext&);  // recompiled
void fn_sub_1D9EE0_001d9ee0(EEContext&);  // generated body
void fn_sub_1D9EE0_001d9ee0__recomp(EEContext&);  // recompiled
void fn_sub_1D9F10_001d9f10(EEContext&);  // generated body
void fn_sub_1D9F10_001d9f10__recomp(EEContext&);  // recompiled
void fn_sub_1E04E0_001e04e0(EEContext&);  // generated body
void fn_sub_1E04E0_001e04e0__recomp(EEContext&);  // recompiled
void fn_sub_1E0510_001e0510(EEContext&);  // generated body
void fn_sub_1E0510_001e0510__recomp(EEContext&);  // recompiled
void fn_sub_1E05B0_001e05b0(EEContext&);  // generated body
void fn_sub_1E05B0_001e05b0__recomp(EEContext&);  // recompiled
void fn_sub_1E1200_001e1200(EEContext&);  // generated body
void fn_sub_1E1200_001e1200__recomp(EEContext&);  // recompiled
void fn_sub_1E1230_001e1230(EEContext&);  // generated body
void fn_sub_1E1230_001e1230__recomp(EEContext&);  // recompiled
void fn_sub_1E1300_001e1300(EEContext&);  // generated body
void fn_sub_1E1300_001e1300__recomp(EEContext&);  // recompiled
void fn_sub_1E1360_001e1360(EEContext&);  // generated body
void fn_sub_1E1360_001e1360__recomp(EEContext&);  // recompiled
void fn_sub_1E14B0_001e14b0(EEContext&);  // generated body
void fn_sub_1E14B0_001e14b0__recomp(EEContext&);  // recompiled
void fn_sub_1E14E0_001e14e0(EEContext&);  // generated body
void fn_sub_1E14E0_001e14e0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"K_FldCamera_UpdateBattleKosakaTask", 0x1D7D40, &recomp_gen::fn_K_FldCamera_UpdateBattleKosakaTask_001d7d40, &recomp_gen::fn_K_FldCamera_UpdateBattleKosakaTask_001d7d40__recomp},
    {"K_FldCamera_DestroyBattleKosakaTask", 0x1D89B0, &recomp_gen::fn_K_FldCamera_DestroyBattleKosakaTask_001d89b0, &recomp_gen::fn_K_FldCamera_DestroyBattleKosakaTask_001d89b0__recomp},
    {"K_Battle_CreateBattleTask", 0x1D8B00, &recomp_gen::fn_K_Battle_CreateBattleTask_001d8b00, &recomp_gen::fn_K_Battle_CreateBattleTask_001d8b00__recomp},
    {"sub_1D8CB0", 0x1D8CB0, &recomp_gen::fn_sub_1D8CB0_001d8cb0, &recomp_gen::fn_sub_1D8CB0_001d8cb0__recomp},
    {"sub_1D8CF0", 0x1D8CF0, &recomp_gen::fn_sub_1D8CF0_001d8cf0, &recomp_gen::fn_sub_1D8CF0_001d8cf0__recomp},
    {"sub_1D8E60", 0x1D8E60, &recomp_gen::fn_sub_1D8E60_001d8e60, &recomp_gen::fn_sub_1D8E60_001d8e60__recomp},
    {"sub_1D9310", 0x1D9310, &recomp_gen::fn_sub_1D9310_001d9310, &recomp_gen::fn_sub_1D9310_001d9310__recomp},
    {"sub_1D94D0", 0x1D94D0, &recomp_gen::fn_sub_1D94D0_001d94d0, &recomp_gen::fn_sub_1D94D0_001d94d0__recomp},
    {"sub_1D96A0", 0x1D96A0, &recomp_gen::fn_sub_1D96A0_001d96a0, &recomp_gen::fn_sub_1D96A0_001d96a0__recomp},
    {"sub_1D9860", 0x1D9860, &recomp_gen::fn_sub_1D9860_001d9860, &recomp_gen::fn_sub_1D9860_001d9860__recomp},
    {"sub_1D9EE0", 0x1D9EE0, &recomp_gen::fn_sub_1D9EE0_001d9ee0, &recomp_gen::fn_sub_1D9EE0_001d9ee0__recomp},
    {"sub_1D9F10", 0x1D9F10, &recomp_gen::fn_sub_1D9F10_001d9f10, &recomp_gen::fn_sub_1D9F10_001d9f10__recomp},
    {"sub_1E04E0", 0x1E04E0, &recomp_gen::fn_sub_1E04E0_001e04e0, &recomp_gen::fn_sub_1E04E0_001e04e0__recomp},
    {"sub_1E0510", 0x1E0510, &recomp_gen::fn_sub_1E0510_001e0510, &recomp_gen::fn_sub_1E0510_001e0510__recomp},
    {"sub_1E05B0", 0x1E05B0, &recomp_gen::fn_sub_1E05B0_001e05b0, &recomp_gen::fn_sub_1E05B0_001e05b0__recomp},
    {"sub_1E1200", 0x1E1200, &recomp_gen::fn_sub_1E1200_001e1200, &recomp_gen::fn_sub_1E1200_001e1200__recomp},
    {"sub_1E1230", 0x1E1230, &recomp_gen::fn_sub_1E1230_001e1230, &recomp_gen::fn_sub_1E1230_001e1230__recomp},
    {"sub_1E1300", 0x1E1300, &recomp_gen::fn_sub_1E1300_001e1300, &recomp_gen::fn_sub_1E1300_001e1300__recomp},
    {"sub_1E1360", 0x1E1360, &recomp_gen::fn_sub_1E1360_001e1360, &recomp_gen::fn_sub_1E1360_001e1360__recomp},
    {"sub_1E14B0", 0x1E14B0, &recomp_gen::fn_sub_1E14B0_001e14b0, &recomp_gen::fn_sub_1E14B0_001e14b0__recomp},
    {"sub_1E14E0", 0x1E14E0, &recomp_gen::fn_sub_1E14E0_001e14e0, &recomp_gen::fn_sub_1E14E0_001e14e0__recomp},
};

// The random world: 64 KiB of free RAM above the harness's arena (the real structures: the snapshot tests below).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(field3_kosaka): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

// =====================================================================================================================
// The real world: the Tartarus snapshot, with stand-ins for the callees this build does not emit
// =====================================================================================================================
namespace {

namespace rg = p3fes::recomp_gen;
using namespace p3fes::game::f3ks;

constexpr const char* kSnap = "climb_ref_17000";
constexpr u32 kSField = 0x869F60u;
constexpr u32 kFake = 0x01EF0000u;          // test structures: the top of the stand-in heap arena (zero in the snapshot)
constexpr u32 kFakeTask = kFake;            // a KwlnTask whose +60 is kFakeWork
constexpr u32 kFakeWork = kFake + 0x100;    // a work block (<= 336 bytes)
constexpr u32 kFakeInst = kFake + 0x400;    // synthetic encounter instances, 0x100 apart
constexpr u32 kFakeMtx = kFake + 0x800;     // the matrix sub_318B70's stand-in returns
constexpr u32 kFakeScript = kFake + 0x900;  // the "task" scrCreateTaskFromHeader's stand-in returns
constexpr u32 kEffectIndex = 5;             // sub_1A91B0's stand-in result
constexpr u32 kRwFree = 0x104280u;          // what the RW free slot 0x96017C holds (served by GuestHeap)
constexpr u32 kGpAddr(s32 off) { return kGp + static_cast<u32>(off); }
// What sub_434F70 [Y_Npc_ResetGlobals] (called once by sub_1D8CB0) writes: eight bytes cleared (gp-17972, -17968,
// -17964, -17960, the three bytes at gp-17928, gp-17920), the halfword gp-17916 set to -1, the byte gp-20960 set to 1,
// eight words 16 bytes apart at 0x86BE00 cleared, and the 256-byte table 0x95C110 cleared unless flag 5140 is set.
constexpr u32 kNpcResetBytes[] = {0x7CE6BCu, 0x7CE6C0u, 0x7CE6C4u, 0x7CE6C8u, 0x7CE6E8u, 0x7CE6E9u, 0x7CE6EAu, 0x7CE6F0u};
constexpr u32 kNpcResetHalf = 0x7CE6F4u, kNpcResetOne = 0x7CDB10u, kNpcResetWords = 0x86BE00u, kNpcResetTable = 0x95C110u;

u32 get32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void put32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void put16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
u16 get16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.at(va), 2);
    return v;
}
constexpr u32 pc_unit(u32 i) { return kPcUnits + kUnitSize * i; }
constexpr u32 ec_unit(u32 i) { return kEcUnits + kUnitSize * i; }
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

const std::vector<u8>& snapshot() {
    static const std::vector<u8> s = read_snapshot(kSnap);
    return s;
}

// The callees this build does not emit, served by recorders (log the call, return v0).
struct Rec {
    u32 va;
    const char* name;
    u64 v0;
};
const Rec kRecorders[] = {
    {0x18BEE0u, "sub_18BEE0 (party panel)", 0},       {0x1A91B0u, "sub_1A91B0 (EPL start)", kEffectIndex},
    {0x1A9400u, "sub_1A9400 (EPL stop)", 0},          {0x1B00C0u, "sub_1B00C0", 0},
    {0x1B02C0u, "sub_1B02C0", 0},                     {0x1DDE00u, "sub_1DDE00 (stand animation)", 3},
    {0x1DE630u, "sub_1DE630 (walk animation)", 4},    {0x1DED40u, "sub_1DED40 (run animation)", 5},
    {0x1DF450u, "sub_1DF450 (tired animation)", 6},   {0x3182D0u, "sub_3182D0 (start animation)", 0},
    {0x318540u, "sub_318540 (current animation)", 0}, {0x318B70u, "sub_318B70 (model matrix)", kFakeMtx},
    {0x35BB40u, "scrCreateTaskFromHeader", kFakeScript}, {0x35BC00u, "scrCreateTaskFromScriptMemory", kFakeScript},
    {0x4C2CC0u, "sub_4C2CC0", 0},
    {0x4C2D20u, "sub_4C2D20", 0},                     {0x4C2F10u, "sub_4C2F10", 0},
    {0x3B7090u, "sub_3B7090", 0},                     {0x1A5EA0u, "sub_1A5EA0", 0},
    {0x2FF760u, "datUnitDestroyGenus", 0},
    // below the emitted callees: the SE sequencer's status (the sound path of sub_10A4E0), an RW frame helper of the
    // free camera (sub_1D5E30: its matrix), fabs (the camera rotation tasks)
    {0x51E028u, "sceSkSsSESQ_Status", 0},             {0x4CB890u, "sub_4CB890", kFakeMtx},
    {0x52E118u, "fabs", 0},                           {0x51DF58u, "sceSkSsSESQ_Control", 0},
    {0x1A1210u, "sub_1A1210 (camera aim)", 0},        {0x45EC00u, "sub_45EC00", 0},
    {0x1F9E90u, "sub_1F9E90 (in the follow-up damage)", 0},
};
void field_world(StandInWorld& w) {
    install_standard(w);
    for (const Rec& r : kRecorders) w.si.install_recorder(r.va, r.name, r.v0);
}

// hgp::pair (stops compared, not fatal) with a fresh stand-in world around each body: the thunks install the world's
// set for the run, so both bodies meet identical stand-ins.
StandInWorld* g_w[2];
Fn g_f[2];
void thunk_hand(EEContext& c) {
    StandInsScope s(g_w[0]->si);
    g_f[0](c);
}
void thunk_recomp(EEContext& c) {
    StandInsScope s(g_w[1]->si);
    g_f[1](c);
}

struct SnapPair {
    hgp::Run run;
    std::unique_ptr<StandInWorld> hand, recomp;
    bool stopped() const { return run.stopped; }
    u64 v0() const { return v0_of(run); }
};

// The snapshot's RAM, then `build` on top, then the pair; afterwards the recompiled run's memory is in place.
SnapPair snap_pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what,
                   const std::function<void(Machine&)>& build, const WorldSetup& setup = field_world) {
    const std::vector<u8>& s = snapshot();
    std::memcpy(m.mem.main_ram(), s.data(), std::min<std::size_t>(s.size(), EEMemory::kMainRamSize));
    build(m);
    SnapPair p;
    p.hand = std::make_unique<StandInWorld>();
    p.recomp = std::make_unique<StandInWorld>();
    setup(*p.hand);
    setup(*p.recomp);
    g_w[0] = p.hand.get();
    g_w[1] = p.recomp.get();
    g_f[0] = hand;
    g_f[1] = recomp;
    p.run = hgp::pair(m, &thunk_hand, &thunk_recomp, args, seed, what);
    expect_same_log(p.hand->si, p.recomp->si, what);
    CHECK(p.hand->heap.live() == p.recomp->heap.live());
    CHECK(p.hand->heap.bad_frees == p.recomp->heap.bad_frees);
    return p;
}

std::unique_ptr<Machine> snapshot_machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    if (snapshot().size() < EEMemory::kMainRamSize) {
        MESSAGE("SKIP: no snapshot extracted/_ours/" << kSnap);
        return nullptr;
    }
    return m;
}

// An enemy field unit (gFldUnitsEc[i]) on a synthetic encounter instance {u16 1, u16 DatUnits, DatUnit* +4,
// u32 encounter +8, 6 x 60-byte DatUnits}; it borrows party unit 1's model and the hero's resource (controller).
void make_enemy(Machine& m, std::mt19937& rng, u32 i, u32 encounter, u32 dat_units) {
    const u32 u = ec_unit(i), inst = kFakeInst + 0x200u * i, dats = inst + 0x20u;
    std::memset(m.at(inst), 0, 0x200);
    put16(m, inst, 1);
    put16(m, inst + kInstEnemyCount, static_cast<u16>(dat_units));
    put32(m, inst + 4, dats);
    put32(m, inst + kInstEncounter, encounter);
    for (u32 k = 0; k < dat_units; ++k) {
        const u32 d = dats + 60u * k;
        put16(m, d, static_cast<u16>(rng() & 0xFF));
        put16(m, d + 2, static_cast<u16>(225 + k));
        put16(m, d + kDatUnitHp, static_cast<u16>(rng() % 3 ? 1 + rng() % 60 : 0));
    }
    put32(m, u + kUnitInstance, inst);
    put32(m, u + kUnitModel, get32(m, pc_unit(1) + kUnitModel));
    put32(m, u + kUnitResource, get32(m, pc_unit(0) + kUnitResource));
    put32(m, u + kUnitTask368, 0);
}

// A kosaka work at kFakeWork (task kFakeTask): party units, enemies, the battler counts as the set-up leaves them.
struct Ks {
    u32 party[2];
    u32 nparty;
    u32 nenemy;
    u32 enemy_dats;
};
Ks make_kosaka(Machine& m, std::mt19937& rng, bool reaper) {
    Ks k{};
    k.nparty = 1 + rng() % 2;
    k.party[0] = pc_unit(1);
    k.party[1] = pc_unit(0);
    k.nenemy = 1 + rng() % 2;
    std::memset(m.at(kFakeWork), 0, kKsWorkSize);
    put32(m, kFakeTask + kTaskWork, kFakeWork);
    for (u32 i = 0; i < k.nparty; ++i) put32(m, kFakeWork + kKsParty + 4 * i, k.party[i]);
    for (u32 i = 0; i < k.nenemy; ++i) {
        const u32 dats = 1 + rng() % 2;
        make_enemy(m, rng, i, reaper ? kEncReaper : 466 + rng() % 4, dats);
        put32(m, kFakeWork + kKsEnemies + 4 * i, ec_unit(i));
        k.enemy_dats += dats;
    }
    put32(m, kFakeWork + kKsPartyCount, k.nparty);
    put32(m, kFakeWork + kKsEnemyCount, k.nenemy);
    put32(m, kFakeWork + kKsPartyBattlers, k.nparty);
    put32(m, kFakeWork + kKsEnemyBattlers, k.enemy_dats);
    put32(m, kFakeWork + kKsBattlerCount, k.nparty + k.enemy_dats);
    put32(m, kFakeWork + kKsReaper, reaper ? 1u : 0u);
    put32(m, kFakeWork + kKsEffect, kEffectIndex);
    put32(m, kFakeWork + kKsSlot, rng() % kKsTaskCount);
    return k;
}

struct Tally {
    std::string name;
    int pairs = 0, stops = 0;
    std::map<std::string, int> why;  // the stops: where and what
    void add(const SnapPair& p) {
        ++pairs;
        if (!p.stopped()) return;
        ++stops;
        ++why[p.run.what + " at " + hex64(p.run.stop_pc)];
    }
    ~Tally() {
        std::string s;
        for (const auto& [w, n] : why) s += "; " + std::to_string(n) + " x " + w;
        MESSAGE(name << ": " << pairs << " snapshot pairs, " << stops << " stopped early (identically)" << s);
    }
};

}  // namespace

namespace {
// A word of the snapshot (the arguments are chosen before the pair loads it).
u32 snap32(u32 va) {
    u32 v = 0;
    std::memcpy(&v, snapshot().data() + va, 4);
    return v;
}
bool logged(const StandIns& si, u32 va, u64 a0) {
    for (const StandInCall& c : si.log)
        if (c.va == va && static_cast<u32>(c.args[0]) == static_cast<u32>(a0)) return true;
    return false;
}
}  // namespace

TEST_CASE("game(field3_kosaka): the battle kosaka task on the Tartarus snapshot") {
    auto mp = snapshot_machine();
    if (!mp) return;
    Machine& m = *mp;
    std::mt19937 rng{0xF3C0510u};
    const u32 root = snap32(kSField);  // the field root task: a real kwln task to create children under

    // K_Battle_CreateBattleTask(field root, party unit 1, an enemy): the first free slot of 0x875A40 gets the task,
    // the turn period starts at 120, +64 marks the Reaper (encounter 506), one unit on each side.
    {
        Tally t{"K_Battle_CreateBattleTask"};
        for (int i = 0; i < 48; ++i) {
            const bool reaper = (i % 3) == 0;
            u32 slots[3];
            for (u32& s : slots) s = ((i % 8) == 7 || rng() % 3 == 0) ? kFakeTask + 0x40u : 0u;
            const u32 enc = reaper ? kEncReaper : 466u + rng() % 4;
            const u32 seed = rng();
            const SnapPair p = snap_pair(m, rg::fn_K_Battle_CreateBattleTask_001d8b00, rg::fn_K_Battle_CreateBattleTask_001d8b00__recomp,
                                         {root, pc_unit(1), ec_unit(0), 0}, seed, "K_Battle_CreateBattleTask", [&](Machine& mm) {
                                             for (u32 k = 0; k < 3; ++k) put32(mm, kKsTasks + 4 * k, slots[k]);
                                             std::mt19937 r2{seed};
                                             make_enemy(mm, r2, 0, enc, 1);
                                         });
            t.add(p);
            if (p.stopped()) continue;
            const u32 task = static_cast<u32>(p.v0());
            REQUIRE(task != 0);
            const u32 work = get32(m, task + kTaskWork);
            CHECK(get32(m, work + kKsState) == 0);
            CHECK(get32(m, work + kKsPartyCount) == 1);
            CHECK(get32(m, work + kKsEnemyCount) == 1);
            CHECK(get32(m, work + kKsParty) == pc_unit(1));
            CHECK(get32(m, work + kKsEnemies) == ec_unit(0));
            CHECK(get32(m, work + kKsTurnPeriod) == kKsFirstTurnDelay);
            CHECK(get32(m, work + kKsReaper) == (reaper ? 1u : 0u));
            int free_slot = -1;
            for (int k = 2; k >= 0; --k)
                if (slots[k] == 0) free_slot = k;
            CHECK(static_cast<s32>(get32(m, work + kKsSlot)) == free_slot);
            if (free_slot >= 0) CHECK(get32(m, kKsTasks + 4u * static_cast<u32>(free_slot)) == task);
        }
    }

    // K_FldCamera_UpdateBattleKosakaTask: paused, over, the set-up, waiting for the turn, a turn (party or enemy).
    {
        Tally t{"K_FldCamera_UpdateBattleKosakaTask"};
        int setups = 0, turns = 0;
        for (int i = 0; i < 120; ++i) {
            const int kind = i % 6;  // 0 paused, 1 over, 2 set-up, 3 waiting, 4 a turn, 5 an unknown state
            const bool reaper = rng() % 4 == 0;
            const u32 seed = rng();
            Ks ks{};
            u32 timer = 0, period = 0, actor = 0;
            const SnapPair p = snap_pair(m, rg::fn_K_FldCamera_UpdateBattleKosakaTask_001d7d40,
                                         rg::fn_K_FldCamera_UpdateBattleKosakaTask_001d7d40__recomp, {kFakeTask, 0, 0, 0}, seed,
                                         "K_FldCamera_UpdateBattleKosakaTask", [&](Machine& mm) {
                                             std::mt19937 r2{seed};
                                             ks = make_kosaka(mm, r2, reaper);
                                             const u32 state = kind == 1 ? 2u : kind == 2 ? 0u : kind == 5 ? 3u + r2() % 5 : 1u;
                                             put32(mm, kFakeWork + kKsState, state);
                                             put32(mm, kFakeWork + kKsPause, kind == 0 ? 1u : (r2() % 4 == 0 ? 2u : 0u));
                                             period = kind == 3 ? 22u + r2() % 100 : r2() % 2 ? 120u : 22u;
                                             timer = kind == 3 ? r2() % (period + 1) : period + 1;
                                             actor = r2() % (ks.nparty + ks.enemy_dats);
                                             put32(mm, kFakeWork + kKsTurnTimer, timer);
                                             put32(mm, kFakeWork + kKsTurnPeriod, period);
                                             put32(mm, kFakeWork + kKsActor, actor);
                                         });
            t.add(p);
            if (p.stopped()) continue;
            const u32 state = get32(m, kFakeWork + kKsState);
            switch (kind) {
            case 0:  // paused: nothing happens
                CHECK(p.v0() == 0);
                CHECK(p.recomp->si.log.empty());
                break;
            case 1:
                CHECK(static_cast<s64>(p.v0()) == -1);
                break;
            case 2:  // the set-up: the dome, the counts, a first actor, state 1
                ++setups;
                CHECK(p.v0() == 0);
                CHECK(state == 1);
                CHECK(get32(m, kFakeWork + kKsEffect) == kEffectIndex);
                CHECK(get32(m, kFakeWork + kKsPartyBattlers) == ks.nparty);
                CHECK(get32(m, kFakeWork + kKsEnemyBattlers) == ks.enemy_dats);
                CHECK(get32(m, kFakeWork + kKsBattlerCount) == ks.nparty + ks.enemy_dats);
                CHECK(get32(m, kFakeWork + kKsActor) < ks.nparty + ks.enemy_dats);
                break;
            case 3:  // not yet: the timer counts
                CHECK(p.v0() == 0);
                CHECK(state == 1);
                CHECK(get32(m, kFakeWork + kKsTurnTimer) == timer + 1);
                CHECK(p.recomp->si.log.empty());
                break;
            case 4:  // a turn: either the fight goes on (timer 0, period <= 22) or it is over (state 2)
                ++turns;
                CHECK(p.v0() == 0);
                CHECK((state == 1 || state == 2));
                if (state == 1) {
                    CHECK(get32(m, kFakeWork + kKsTurnTimer) == 0);
                    CHECK(get32(m, kFakeWork + kKsTurnPeriod) == std::min(period, 22u));
                    CHECK(get32(m, kFakeWork + kKsActor) < get32(m, kFakeWork + kKsBattlerCount));
                }
                break;
            default:  // states 3.. do nothing
                CHECK(p.v0() == 0);
                break;
            }
        }
        MESSAGE("kosaka update: " << setups << " set-ups and " << turns << " turns ran to the end");
    }

    // sub_1D8E60 [K_Battle_JoinUnits]: a party unit and / or an enemy join an existing skirmish.
    {
        Tally t{"sub_1D8E60"};
        for (int i = 0; i < 40; ++i) {
            const u32 seed = rng();
            const bool add_party = rng() % 3 != 0, add_enemy = rng() % 3 != 0;
            Ks ks{};
            const SnapPair p = snap_pair(m, rg::fn_sub_1D8E60_001d8e60, rg::fn_sub_1D8E60_001d8e60__recomp,
                                         {kFakeTask, add_party ? pc_unit(0) : 0u, add_enemy ? ec_unit(2) : 0u, 0}, seed, "sub_1D8E60",
                                         [&](Machine& mm) {
                                             std::mt19937 r2{seed};
                                             ks = make_kosaka(mm, r2, false);
                                             make_enemy(mm, r2, 2, 467, 2);
                                         });
            t.add(p);
            if (p.stopped()) continue;
            CHECK(p.v0() == ((add_party || add_enemy) ? 1u : 0u));
            const u32 np = get32(m, kFakeWork + kKsPartyCount), ne = get32(m, kFakeWork + kKsEnemyCount);
            CHECK(np == ks.nparty + (add_party ? 1u : 0u));
            CHECK(ne == ks.nenemy + (add_enemy ? 1u : 0u));
            if (add_party) CHECK(get32(m, kFakeWork + kKsParty + 4 * ks.nparty) == pc_unit(0));
            if (add_enemy) CHECK(get32(m, kFakeWork + kKsEnemies + 4 * ks.nenemy) == ec_unit(2));
            if (add_party || add_enemy) {
                CHECK(get32(m, kFakeWork + kKsPartyBattlers) == np);
                CHECK(get32(m, kFakeWork + kKsEnemyBattlers) == ks.enemy_dats + (add_enemy ? 2u : 0u));
                CHECK(get32(m, kFakeWork + kKsBattlerCount) == np + ks.enemy_dats + (add_enemy ? 2u : 0u));
            }
        }
    }

    // K_FldCamera_DestroyBattleKosakaTask: the slot freed, the work RwFree'd (a heap block of the stand-in world).
    {
        Tally t{"K_FldCamera_DestroyBattleKosakaTask"};
        const WorldSetup with_work = [](StandInWorld& w) {
            field_world(w);
            w.heap.alloc(kKsWorkSize);  // == kStandInHeap: the work
        };
        for (int i = 0; i < 40; ++i) {
            const u32 seed = rng();
            u32 slot = 0;
            const SnapPair p = snap_pair(m, rg::fn_K_FldCamera_DestroyBattleKosakaTask_001d89b0,
                                         rg::fn_K_FldCamera_DestroyBattleKosakaTask_001d89b0__recomp, {kFakeTask, 0, 0, 0}, seed,
                                         "K_FldCamera_DestroyBattleKosakaTask",
                                         [&](Machine& mm) {
                                             std::mt19937 r2{seed};
                                             make_kosaka(mm, r2, false);
                                             std::memcpy(mm.at(kStandInHeap), mm.at(kFakeWork), kKsWorkSize);
                                             put32(mm, kFakeTask + kTaskWork, kStandInHeap);
                                             slot = r2() % kKsTaskCount;
                                             put32(mm, kStandInHeap + kKsSlot, slot);
                                             for (u32 k = 0; k < 3; ++k) put32(mm, kKsTasks + 4 * k, kFakeTask);
                                             if (r2() % 2) put32(mm, kGpAddr(-19788), 1);  // The Answer: no item drop
                                         },
                                         with_work);
            t.add(p);
            if (p.stopped()) continue;
            CHECK(get32(m, kKsTasks + 4 * slot) == 0);
            for (u32 k = 0; k < 3; ++k)
                if (k != slot) CHECK(get32(m, kKsTasks + 4 * k) == kFakeTask);
            CHECK(logged(p.recomp->si, kRwFree, kStandInHeap));
            CHECK(p.recomp->heap.live().empty());
        }
    }

    // sub_1D8CB0 [K_Battle_InitTasks] / sub_1D8CF0 [K_Battle_DestroyAllTasks] (the real pad task as a live entry).
    {
        Tally t{"sub_1D8CB0 / sub_1D8CF0"};
        for (int i = 0; i < 8; ++i) {
            const u32 seed = rng();
            const SnapPair p = snap_pair(m, rg::fn_sub_1D8CB0_001d8cb0, rg::fn_sub_1D8CB0_001d8cb0__recomp, {0, 0, 0, 0}, seed,
                                         "sub_1D8CB0", [&](Machine& mm) {
                                             for (u32 k = 0; k < 3; ++k) put32(mm, kKsTasks + 4 * k, seed * (k + 1));
                                             // what sub_434F70 [Y_Npc_ResetGlobals] resets, set to values it must clear
                                             for (const u32 b : kNpcResetBytes) mm.at(b)[0] = 0x5A;
                                             put16(mm, kNpcResetHalf, 0x1234);
                                             mm.at(kNpcResetOne)[0] = 0;
                                             for (u32 k = 0; k < 8; ++k) put32(mm, kNpcResetWords + 16 * k, 0xA5A5A5A5u);
                                             std::memset(mm.at(kNpcResetTable), 0x5A, 256);
                                         });
            t.add(p);
            if (p.stopped()) continue;
            for (u32 k = 0; k < 3; ++k) CHECK(get32(m, kKsTasks + 4 * k) == 0);
            // sub_434F70 ran once (hand-written since slice unblock, so checked by its effect in guest memory, not by a
            // recorder's call count): the NPC globals reset, the 256-byte table cleared unless flag 5140 is set
            for (const u32 b : kNpcResetBytes) CHECK(m.at(b)[0] == 0);
            CHECK(get16(m, kNpcResetHalf) == 0xFFFFu);
            CHECK(m.at(kNpcResetOne)[0] == 1);
            for (u32 k = 0; k < 8; ++k) CHECK(get32(m, kNpcResetWords + 16 * k) == 0u);
            const bool keep_table = (hgp::run_one(m, &rg::fn_datGetFlag_0016f190, {5140, 0, 0, 0}, 1, HwCheck{}).end.gpr[GPR_V0].u64[0] & 0xFFFFFFFFu) != 0;
            u32 table_bytes = 0;
            for (u32 k = 0; k < 256; ++k) table_bytes += m.at(kNpcResetTable + k)[0] == (keep_table ? 0x5A : 0) ? 1u : 0u;
            CHECK(table_bytes == 256u);
        }
        const u32 pad = snap32(kSField + kFieldPadTask);
        for (int i = 0; i < 6; ++i) {
            const u32 seed = rng();
            const u32 live = i % 3;  // 0: none, 1: the pad task in slot 1, 2: in slot 2
            const SnapPair p = snap_pair(m, rg::fn_sub_1D8CF0_001d8cf0, rg::fn_sub_1D8CF0_001d8cf0__recomp, {0, 0, 0, 0}, seed,
                                         "sub_1D8CF0", [&](Machine& mm) {
                                             for (u32 k = 0; k < 3; ++k) put32(mm, kKsTasks + 4 * k, live == k && k ? pad : 0u);
                                         });
            t.add(p);
            if (p.stopped()) continue;
            if (live == 0) CHECK(p.recomp->si.log.empty());
        }
    }
}

TEST_CASE("game(field3_kosaka): the supporter proc on the Tartarus snapshot") {
    auto mp = snapshot_machine();
    if (!mp) return;
    Machine& m = *mp;
    std::mt19937 rng{0xF3C5099u};

    // The three party filters on the same party (members 2 / 3 made live with other ids): low HP (< 0.3) and the
    // other two (>= 0.3) never list the same member; every list holds live members' ids.
    {
        Tally t{"sub_1D9310 / sub_1D94D0 / sub_1D96A0"};
        const Fn hands[3] = {rg::fn_sub_1D9310_001d9310, rg::fn_sub_1D94D0_001d94d0, rg::fn_sub_1D96A0_001d96a0};
        const Fn recomps[3] = {rg::fn_sub_1D9310_001d9310__recomp, rg::fn_sub_1D94D0_001d94d0__recomp, rg::fn_sub_1D96A0_001d96a0__recomp};
        const char* names[3] = {"sub_1D9310", "sub_1D94D0", "sub_1D96A0"};
        const u16 ids[] = {2, 3, 4, 5, 6, 7, 8, 9};
        for (int i = 0; i < 24; ++i) {
            const u32 seed = rng();
            std::vector<u32> lists[3];
            std::vector<u32> live_ids;
            for (int f = 0; f < 3; ++f) {
                const SnapPair p = snap_pair(m, hands[f], recomps[f], {kFakeWork, 0, 0, 0}, seed, names[f], [&](Machine& mm) {
                    std::mt19937 r2{seed};
                    live_ids.clear();
                    for (u32 k = 1; k < 4; ++k) {
                        const u32 u = pc_unit(k);
                        if (k > 1 && r2() % 2) {
                            put32(mm, u + kUnitInstance, get32(mm, pc_unit(1) + kUnitInstance));
                            put32(mm, u + kUnitResource, get32(mm, pc_unit(1) + kUnitResource));
                            put16(mm, u + kUnitId, ids[r2() % 8]);
                        }
                        if (get32(mm, u + kUnitInstance) && get32(mm, u + kUnitResource)) live_ids.push_back(get16(mm, u + kUnitId));
                    }
                    std::memset(mm.at(kFakeWork), 0xA5, 16);
                });
                t.add(p);
                if (p.stopped()) continue;
                const u32 n = get32(m, kFakeWork);
                CHECK(n <= 3);
                CHECK(p.v0() == (n != 0 ? 1u : 0u));
                for (u32 k = 0; k < n && k < 3; ++k) {
                    const u32 id = get32(m, kFakeWork + 4 + 4 * k);
                    lists[f].push_back(id);
                    CHECK(std::find(live_ids.begin(), live_ids.end(), id) != live_ids.end());
                }
            }
            for (u32 id : lists[0]) {
                CHECK(std::find(lists[1].begin(), lists[1].end(), id) == lists[1].end());
                CHECK(std::find(lists[2].begin(), lists[2].end(), id) == lists[2].end());
            }
        }
    }

    // sub_1D9860 [K_Support_UpdateTask]: paused, over, the start, waiting for scripts, the 901-frame rounds.
    {
        Tally t{"sub_1D9860"};
        const u32 frame = snap32(kGpAddr(kGpFrameCounterB));
        for (int i = 0; i < 72; ++i) {
            const int kind = i % 6;  // 0 paused, 1 over, 2 start, 3 waiting for scripts, 4 a quiet frame, 5 a round
            const u32 seed = rng();
            u32 stamp = 0, said = 0;
            const SnapPair p = snap_pair(m, rg::fn_sub_1D9860_001d9860, rg::fn_sub_1D9860_001d9860__recomp, {kFakeTask, 0, 0, 0}, seed,
                                         "sub_1D9860", [&](Machine& mm) {
                                             std::mt19937 r2{seed};
                                             std::memset(mm.at(kFakeWork), 0, kSupWorkSize);
                                             put32(mm, kFakeTask + kTaskWork, kFakeWork);
                                             const u32 state = kind == 1 ? 4u : kind == 2 ? 0u : kind == 3 ? 3u : kind == 0 ? r2() % 4 : 1u;
                                             put32(mm, kFakeWork + kSupState, state);
                                             put32(mm, kFakeWork + kSupPause, kind == 0 ? 1u : 0u);
                                             said = kind == 4 ? 1u : r2() % 2;
                                             put32(mm, kFakeWork + kSupReaperSaid, said);
                                             stamp = kind == 4 ? frame - r2() % kSupPeriod : kind == 5 ? frame - kSupPeriod - r2() % 300 : frame - r2() % 2000;
                                             put32(mm, kFakeWork + kSupStamp, stamp);
                                             if (kind == 3)
                                                 for (u32 k = 0; k < kSupSlots; ++k)
                                                     put32(mm, kFakeWork + kSupTasks + 4 * k, r2() % 3 ? 0u : kFakeScript);
                                         });
            t.add(p);
            if (p.stopped()) continue;
            const u32 state = get32(m, kFakeWork + kSupState);
            switch (kind) {
            case 0:
                CHECK(p.v0() == 0);
                CHECK(get32(m, kFakeWork + kSupStamp) == stamp);
                break;
            case 1:
                CHECK(static_cast<s64>(p.v0()) == -1);
                break;
            case 2:  // stamped, then running (or already waiting for a comment it started)
                CHECK(p.v0() == 0);
                CHECK((state == 1 || state == 3));
                break;
            case 3:  // the fake script task is no kwln task: every slot cleared, back to running, stamped
                CHECK(p.v0() == 0);
                CHECK(state == 1);
                CHECK(get32(m, kFakeWork + kSupStamp) == frame);
                for (u32 k = 0; k < kSupSlots; ++k) CHECK(get32(m, kFakeWork + kSupTasks + 4 * k) == 0);
                break;
            case 4:  // less than 901 frames and the Reaper comment given: nothing
                CHECK(p.v0() == 0);
                CHECK(get32(m, kFakeWork + kSupStamp) == stamp);
                CHECK(p.recomp->si.calls_to(0x35BB40u) == 0);
                break;
            default:  // a round: stamped again; every comment started went into a slot and set state 3
                CHECK(p.v0() == 0);
                CHECK(get32(m, kFakeWork + kSupStamp) == frame);
                CHECK((p.recomp->si.calls_to(0x35BB40u) == 0) == (state == 1));
                break;
            }
        }
    }

    // sub_1D9F10 [K_Support_CreateTask]: only in a Tartarus scene other than major 33; sub_1D9EE0 frees the work.
    {
        Tally t{"sub_1D9F10 / sub_1D9EE0"};
        const u32 root = snap32(kSField);
        const u32 scene = snap32(kGpAddr(-22448));
        const u32 majors[] = {51, 33, 7, 21, 35};
        for (int i = 0; i < 10; ++i) {
            const u32 major = majors[i % 5];
            const SnapPair p = snap_pair(m, rg::fn_sub_1D9F10_001d9f10, rg::fn_sub_1D9F10_001d9f10__recomp, {root, 0, 0, 0}, rng(),
                                         "sub_1D9F10", [&](Machine& mm) {
                                             put32(mm, scene, major);
                                             if (major == 21) put32(mm, scene + 4, 0);
                                         });
            t.add(p);
            if (p.stopped()) continue;
            const bool expect = major == 51 || major == 21 || major == 35;
            CHECK((p.v0() != 0) == expect);
            if (p.v0()) {
                const u32 work = get32(m, static_cast<u32>(p.v0()) + kTaskWork);
                CHECK(p.recomp->heap.size_of(work) >= kSupWorkSize);
            }
        }
        const WorldSetup with_block = [](StandInWorld& w) {
            field_world(w);
            w.heap.alloc(kSupWorkSize);
        };
        for (int i = 0; i < 4; ++i) {
            const SnapPair p = snap_pair(m, rg::fn_sub_1D9EE0_001d9ee0, rg::fn_sub_1D9EE0_001d9ee0__recomp, {kFakeTask, 0, 0, 0}, rng(),
                                         "sub_1D9EE0", [&](Machine& mm) { put32(mm, kFakeTask + kTaskWork, kStandInHeap); }, with_block);
            t.add(p);
            if (p.stopped()) continue;
            CHECK(logged(p.recomp->si, kRwFree, kStandInHeap));
            CHECK(p.recomp->heap.live().empty());
        }
    }
}

TEST_CASE("game(field3_kosaka): the virtual pad on the Tartarus snapshot") {
    auto mp = snapshot_machine();
    if (!mp) return;
    Machine& m = *mp;
    std::mt19937 rng{0xF3C1E05u};
    const u32 pad = snap32(kSField + kFieldPadTask);
    const u32 root = snap32(kSField);
    if (pad == 0) {
        MESSAGE("SKIP: no pad task in the snapshot");
        return;
    }
    const u32 work = snap32(pad + kTaskWork);
    const u32 model = snap32(work + kPadModel), ctl = snap32(work + kPadController);

    // sub_1E05B0 [K_VPad_UpdateTask]: the real pad task with random sticks / buttons, locks and states.
    {
        Tally t{"sub_1E05B0"};
        const u16 bits[] = {0x1000, 0x2000, 0x4000, 0x8000, 0x0002, 0x0008, 0x0001, 0x0004, 0x0020, 0x0040};
        int still_checked = 0;
        for (int i = 0; i < 96; ++i) {
            const int kind = i % 8;  // 0 state 0, 1 state 5, 2 locked, 3 still, 4.. random input
            const u32 seed = rng();
            u32 still = 0, speed = 0;
            const SnapPair p = snap_pair(m, rg::fn_sub_1E05B0_001e05b0, rg::fn_sub_1E05B0_001e05b0__recomp, {pad, 0, 0, 0}, seed,
                                         "sub_1E05B0", [&](Machine& mm) {
                                             std::mt19937 r2{seed};
                                             put32(mm, work + kPadState, kind == 0 ? 0u : kind == 1 ? 5u : (i % 16 == 15) ? 2u : 1u);
                                             put32(mm, work + kPadLockEvent, kind == 2 && r2() % 2 ? 1u : 0u);
                                             put32(mm, work + kPadLockNpc, kind == 2 && get32(mm, work + kPadLockEvent) == 0 ? 1u : 0u);
                                             still = r2() % 6;
                                             put32(mm, work + kPadStill, still);
                                             put32(mm, work + kPadIdle, r2() % 3 ? r2() % 400 : 59);
                                             put32(mm, work + kPadAnimDebounce, r2() % 3);
                                             put32(mm, work + kPadAnim, 4 + r2() % 2);
                                             speed = get32(mm, kGpAddr(kGpPadSpeed));
                                             u16 held = 0, pressed = 0;
                                             u8 sticks[4] = {128, 128, 128, 128};
                                             if (kind >= 4) {
                                                 for (u8& s : sticks) s = r2() % 3 ? static_cast<u8>(r2()) : 128;
                                                 for (u16 b : bits)
                                                     if (r2() % 6 == 0) held |= b;
                                                 if (r2() % 5 == 0) pressed |= 0x20;
                                             }
                                             put16(mm, kPadHeld, held);
                                             put16(mm, kPadPressed, pressed);
                                             std::memcpy(mm.at(kPadStickLX), sticks, 4);
                                             // the model matrix sub_318B70's stand-in hands back: identity, at the origin
                                             std::memset(mm.at(kFakeMtx), 0, 80);
                                             for (u32 k = 0; k < 3; ++k) put32(mm, kFakeMtx + 16 + 20 * k, 0x3F800000u);
                                         });
            t.add(p);
            if (p.stopped()) continue;
            const u32 state = get32(m, work + kPadState);
            if (kind == 1) CHECK(static_cast<s64>(p.v0()) == -1);
            if (kind != 1) CHECK(p.v0() == 0);
            if (kind == 0) CHECK(state == 1);
            if (kind == 2 && state == 1) {  // locked: no move, no animation request
                CHECK(get32(m, kGpAddr(kGpPadSpeed)) == speed);
                CHECK(get32(m, work + kPadStill) == still);
            }
            if (kind == 3 && state == 1 && still < 4) {  // inside the dead zone: the still counter runs
                ++still_checked;
                CHECK(get32(m, work + kPadStill) == still + 1);
            }
        }
        MESSAGE("pad: " << still_checked << " still-counter checks");
    }

    // sub_1E1300 / sub_1E1360: the two input locks (a null task is ignored).
    {
        Tally t{"sub_1E1300 / sub_1E1360"};
        for (int i = 0; i < 24; ++i) {
            const bool npc = i % 2, null_task = i % 6 == 5;
            const u32 on = rng() % 2;
            const SnapPair p = snap_pair(m, npc ? rg::fn_sub_1E1360_001e1360 : rg::fn_sub_1E1300_001e1300,
                                         npc ? rg::fn_sub_1E1360_001e1360__recomp : rg::fn_sub_1E1300_001e1300__recomp,
                                         {null_task ? 0u : pad, on, 0, 0}, rng(), npc ? "sub_1E1360" : "sub_1E1300",
                                         [&](Machine& mm) { put32(mm, work + kPadAnimSet, 1); });
            t.add(p);
            if (p.stopped()) continue;
            if (null_task) {
                CHECK(p.recomp->si.log.empty());
                continue;
            }
            CHECK(get32(m, work + (npc ? kPadLockNpc : kPadLockEvent)) == on);
            CHECK(get32(m, work + kPadAnimSet) == 0);
            CHECK(logged(p.recomp->si, 0x3182D0u, model));
        }
    }

    // The creators under the field root, and the three free callbacks.
    {
        Tally t{"sub_1E1230 / sub_1E14E0 / sub_1E0510 / frees"};
        for (int i = 0; i < 6; ++i) {
            const SnapPair p = snap_pair(m, rg::fn_sub_1E1230_001e1230, rg::fn_sub_1E1230_001e1230__recomp, {root, ctl, model, 0}, rng(),
                                         "sub_1E1230", [](Machine&) {});
            t.add(p);
            if (p.stopped() || p.v0() == 0) continue;
            const u32 w = get32(m, static_cast<u32>(p.v0()) + kTaskWork);
            CHECK(get32(m, w + kPadController) == ctl);
            CHECK(get32(m, w + kPadModel) == model);
            const u32 rot = get32(m, w + kPadRotateTask);
            REQUIRE(rot != 0);
            const u32 rw = get32(m, rot + kTaskWork);
            CHECK(get32(m, rw + 68) == ctl);
            CHECK(get32(m, rw + 72) == model);
        }
        for (int i = 0; i < 4; ++i) {
            const u32 arg = rng();
            const SnapPair p = snap_pair(m, rg::fn_sub_1E0510_001e0510, rg::fn_sub_1E0510_001e0510__recomp, {root, arg, 0, 0}, rng(),
                                         "sub_1E0510", [](Machine&) {});
            t.add(p);
            if (p.stopped() || p.v0() == 0) continue;
            CHECK(get32(m, get32(m, static_cast<u32>(p.v0()) + kTaskWork) + 80) == arg);
        }
        for (int i = 0; i < 4; ++i) {
            const SnapPair p = snap_pair(m, rg::fn_sub_1E14E0_001e14e0, rg::fn_sub_1E14E0_001e14e0__recomp, {root, ctl, model, 0}, rng(),
                                         "sub_1E14E0", [](Machine&) {});
            t.add(p);
            if (p.stopped() || p.v0() == 0) continue;
            const u32 rw = get32(m, static_cast<u32>(p.v0()) + kTaskWork);
            CHECK(get32(m, rw + 68) == ctl);
            CHECK(get32(m, rw + 72) == model);
        }
        const Fn hands[3] = {rg::fn_sub_1E04E0_001e04e0, rg::fn_sub_1E1200_001e1200, rg::fn_sub_1E14B0_001e14b0};
        const Fn recomps[3] = {rg::fn_sub_1E04E0_001e04e0__recomp, rg::fn_sub_1E1200_001e1200__recomp, rg::fn_sub_1E14B0_001e14b0__recomp};
        const WorldSetup with_block = [](StandInWorld& w) {
            field_world(w);
            w.heap.alloc(kPadWorkSize);
        };
        for (int f = 0; f < 3; ++f) {
            const SnapPair p = snap_pair(m, hands[f], recomps[f], {kFakeTask, 0, 0, 0}, rng(), "free callback",
                                         [](Machine& mm) { put32(mm, kFakeTask + kTaskWork, kStandInHeap); }, with_block);
            t.add(p);
            if (p.stopped()) continue;
            CHECK(logged(p.recomp->si, kRwFree, kStandInHeap));
            CHECK(p.recomp->heap.live().empty());
        }
    }
}

#else

TEST_CASE("game(field3_kosaka): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
