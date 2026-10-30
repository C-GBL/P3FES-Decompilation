// Pair tests of slice field6, part shuffle (game/src/battle/field6_shuffle.cpp): Shuffle Time's root and result, each
// body against its recompiled body (handgen_pairs.h / pair_harness.h / stand_ins.h: the whole register file and cycles
// at every check point, all RAM including the dead stack, the stand-ins' call logs incl. printf), on
//   * random worlds: the p3fes_handgen sweep;
//   * a Shuffle Time world made by the game's own code: no replay route reaches Shuffle Time, so the test starts one
//     on b_6150 (the battle replay's result screen) -- brRoot_CreateBattleResultTasks with the packet's Shuffle Time
//     flag creates the "shuffle root" task, its work (gp 0x7CE2DC), the result work (gp 0x7CE2E0) and the modules
//     (paired itself) -- and every later pair starts from that machine (the stand-in heap's blocks kept live): the
//     root's update in each of its states, the draws, the deal and command builders, the state moves of the small
//     steps (documented), the result's start / update / pages / lists / reward roll on two hand-placed entries (one
//     persona, one arcana card), the 13 card conditions (0 / 1), the two destroys (gp slots cleared).
// Callees this build does not emit are stood in by recorders.
#include "field6_util.h"

#include "p3fes/game/field6_shuffle.h"

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::f6t;

namespace p3fes::recomp_gen {
void fn_sflRoot_CreateShuffleRootTasks_001f2080(EEContext&);  // generated body
void fn_sflRoot_CreateShuffleRootTasks_001f2080__recomp(EEContext&);  // recompiled
void fn_sflRoot_UpdateShuffleRootTask_001f2300(EEContext&);  // generated body
void fn_sflRoot_UpdateShuffleRootTask_001f2300__recomp(EEContext&);  // recompiled
void fn_sflRoot_UpdateShuffleRootDraw0Task_001f2f50(EEContext&);  // generated body
void fn_sflRoot_UpdateShuffleRootDraw0Task_001f2f50__recomp(EEContext&);  // recompiled
void fn_sflRoot_UpdateShuffleRootDraw1Task_001f2f80(EEContext&);  // generated body
void fn_sflRoot_UpdateShuffleRootDraw1Task_001f2f80__recomp(EEContext&);  // recompiled
void fn_sub_1F2FD0_001f2fd0(EEContext&);  // generated body
void fn_sub_1F2FD0_001f2fd0__recomp(EEContext&);  // recompiled
void fn_sub_1F2FF0_001f2ff0(EEContext&);  // generated body
void fn_sub_1F2FF0_001f2ff0__recomp(EEContext&);  // recompiled
void fn_sub_1F30F0_001f30f0(EEContext&);  // generated body
void fn_sub_1F30F0_001f30f0__recomp(EEContext&);  // recompiled
void fn_sub_1F3270_001f3270(EEContext&);  // generated body
void fn_sub_1F3270_001f3270__recomp(EEContext&);  // recompiled
void fn_sub_1F4750_001f4750(EEContext&);  // generated body
void fn_sub_1F4750_001f4750__recomp(EEContext&);  // recompiled
void fn_sub_1F4A00_001f4a00(EEContext&);  // generated body
void fn_sub_1F4A00_001f4a00__recomp(EEContext&);  // recompiled
void fn_sub_1F53A0_001f53a0(EEContext&);  // generated body
void fn_sub_1F53A0_001f53a0__recomp(EEContext&);  // recompiled
void fn_sub_1F54A0_001f54a0(EEContext&);  // generated body
void fn_sub_1F54A0_001f54a0__recomp(EEContext&);  // recompiled
void fn_sub_1F55E0_001f55e0(EEContext&);  // generated body
void fn_sub_1F55E0_001f55e0__recomp(EEContext&);  // recompiled
void fn_sub_1F5950_001f5950(EEContext&);  // generated body
void fn_sub_1F5950_001f5950__recomp(EEContext&);  // recompiled
void fn_sub_1F59B0_001f59b0(EEContext&);  // generated body
void fn_sub_1F59B0_001f59b0__recomp(EEContext&);  // recompiled
void fn_sub_1F5B20_001f5b20(EEContext&);  // generated body
void fn_sub_1F5B20_001f5b20__recomp(EEContext&);  // recompiled
void fn_sub_1F64C0_001f64c0(EEContext&);  // generated body
void fn_sub_1F64C0_001f64c0__recomp(EEContext&);  // recompiled
void fn_sub_1F6630_001f6630(EEContext&);  // generated body
void fn_sub_1F6630_001f6630__recomp(EEContext&);  // recompiled
void fn_sub_1F6A60_001f6a60(EEContext&);  // generated body
void fn_sub_1F6A60_001f6a60__recomp(EEContext&);  // recompiled
void fn_sub_1F6E80_001f6e80(EEContext&);  // generated body
void fn_sub_1F6E80_001f6e80__recomp(EEContext&);  // recompiled
void fn_sub_1F7030_001f7030(EEContext&);  // generated body
void fn_sub_1F7030_001f7030__recomp(EEContext&);  // recompiled
void fn_sub_1F70D0_001f70d0(EEContext&);  // generated body
void fn_sub_1F70D0_001f70d0__recomp(EEContext&);  // recompiled
void fn_sub_1F7170_001f7170(EEContext&);  // generated body
void fn_sub_1F7170_001f7170__recomp(EEContext&);  // recompiled
void fn_sub_1F7210_001f7210(EEContext&);  // generated body
void fn_sub_1F7210_001f7210__recomp(EEContext&);  // recompiled
void fn_sub_1F9100_001f9100(EEContext&);  // generated body
void fn_sub_1F9100_001f9100__recomp(EEContext&);  // recompiled
void fn_sub_1F9170_001f9170(EEContext&);  // generated body
void fn_sub_1F9170_001f9170__recomp(EEContext&);  // recompiled
void fn_sub_1F98D0_001f98d0(EEContext&);  // generated body
void fn_sub_1F98D0_001f98d0__recomp(EEContext&);  // recompiled
void fn_sub_1F99F0_001f99f0(EEContext&);  // generated body
void fn_sub_1F99F0_001f99f0__recomp(EEContext&);  // recompiled
void fn_sub_1F9A80_001f9a80(EEContext&);  // generated body
void fn_sub_1F9A80_001f9a80__recomp(EEContext&);  // recompiled
void fn_sub_1F9C60_001f9c60(EEContext&);  // generated body
void fn_sub_1F9C60_001f9c60__recomp(EEContext&);  // recompiled
void fn_brRoot_CreateBattleResultTasks_001ef500(EEContext&);
void fn_brRoot_CreateBattleResultTasks_001ef500__recomp(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sflRoot_CreateShuffleRootTasks", 0x1F2080, &recomp_gen::fn_sflRoot_CreateShuffleRootTasks_001f2080, &recomp_gen::fn_sflRoot_CreateShuffleRootTasks_001f2080__recomp},
    {"sflRoot_UpdateShuffleRootTask", 0x1F2300, &recomp_gen::fn_sflRoot_UpdateShuffleRootTask_001f2300, &recomp_gen::fn_sflRoot_UpdateShuffleRootTask_001f2300__recomp},
    {"sflRoot_UpdateShuffleRootDraw0Task", 0x1F2F50, &recomp_gen::fn_sflRoot_UpdateShuffleRootDraw0Task_001f2f50, &recomp_gen::fn_sflRoot_UpdateShuffleRootDraw0Task_001f2f50__recomp},
    {"sflRoot_UpdateShuffleRootDraw1Task", 0x1F2F80, &recomp_gen::fn_sflRoot_UpdateShuffleRootDraw1Task_001f2f80, &recomp_gen::fn_sflRoot_UpdateShuffleRootDraw1Task_001f2f80__recomp},
    {"sub_1F2FD0", 0x1F2FD0, &recomp_gen::fn_sub_1F2FD0_001f2fd0, &recomp_gen::fn_sub_1F2FD0_001f2fd0__recomp},
    {"sub_1F2FF0", 0x1F2FF0, &recomp_gen::fn_sub_1F2FF0_001f2ff0, &recomp_gen::fn_sub_1F2FF0_001f2ff0__recomp},
    {"sub_1F30F0", 0x1F30F0, &recomp_gen::fn_sub_1F30F0_001f30f0, &recomp_gen::fn_sub_1F30F0_001f30f0__recomp},
    {"sub_1F3270", 0x1F3270, &recomp_gen::fn_sub_1F3270_001f3270, &recomp_gen::fn_sub_1F3270_001f3270__recomp},
    {"sub_1F4750", 0x1F4750, &recomp_gen::fn_sub_1F4750_001f4750, &recomp_gen::fn_sub_1F4750_001f4750__recomp},
    {"sub_1F4A00", 0x1F4A00, &recomp_gen::fn_sub_1F4A00_001f4a00, &recomp_gen::fn_sub_1F4A00_001f4a00__recomp},
    {"sub_1F53A0", 0x1F53A0, &recomp_gen::fn_sub_1F53A0_001f53a0, &recomp_gen::fn_sub_1F53A0_001f53a0__recomp},
    {"sub_1F54A0", 0x1F54A0, &recomp_gen::fn_sub_1F54A0_001f54a0, &recomp_gen::fn_sub_1F54A0_001f54a0__recomp},
    {"sub_1F55E0", 0x1F55E0, &recomp_gen::fn_sub_1F55E0_001f55e0, &recomp_gen::fn_sub_1F55E0_001f55e0__recomp},
    {"sub_1F5950", 0x1F5950, &recomp_gen::fn_sub_1F5950_001f5950, &recomp_gen::fn_sub_1F5950_001f5950__recomp},
    {"sub_1F59B0", 0x1F59B0, &recomp_gen::fn_sub_1F59B0_001f59b0, &recomp_gen::fn_sub_1F59B0_001f59b0__recomp},
    {"sub_1F5B20", 0x1F5B20, &recomp_gen::fn_sub_1F5B20_001f5b20, &recomp_gen::fn_sub_1F5B20_001f5b20__recomp},
    {"sub_1F64C0", 0x1F64C0, &recomp_gen::fn_sub_1F64C0_001f64c0, &recomp_gen::fn_sub_1F64C0_001f64c0__recomp},
    {"sub_1F6630", 0x1F6630, &recomp_gen::fn_sub_1F6630_001f6630, &recomp_gen::fn_sub_1F6630_001f6630__recomp},
    {"sub_1F6A60", 0x1F6A60, &recomp_gen::fn_sub_1F6A60_001f6a60, &recomp_gen::fn_sub_1F6A60_001f6a60__recomp},
    {"sub_1F6E80", 0x1F6E80, &recomp_gen::fn_sub_1F6E80_001f6e80, &recomp_gen::fn_sub_1F6E80_001f6e80__recomp},
    {"sub_1F7030", 0x1F7030, &recomp_gen::fn_sub_1F7030_001f7030, &recomp_gen::fn_sub_1F7030_001f7030__recomp},
    {"sub_1F70D0", 0x1F70D0, &recomp_gen::fn_sub_1F70D0_001f70d0, &recomp_gen::fn_sub_1F70D0_001f70d0__recomp},
    {"sub_1F7170", 0x1F7170, &recomp_gen::fn_sub_1F7170_001f7170, &recomp_gen::fn_sub_1F7170_001f7170__recomp},
    {"sub_1F7210", 0x1F7210, &recomp_gen::fn_sub_1F7210_001f7210, &recomp_gen::fn_sub_1F7210_001f7210__recomp},
    {"sub_1F9100", 0x1F9100, &recomp_gen::fn_sub_1F9100_001f9100, &recomp_gen::fn_sub_1F9100_001f9100__recomp},
    {"sub_1F9170", 0x1F9170, &recomp_gen::fn_sub_1F9170_001f9170, &recomp_gen::fn_sub_1F9170_001f9170__recomp},
    {"sub_1F98D0", 0x1F98D0, &recomp_gen::fn_sub_1F98D0_001f98d0, &recomp_gen::fn_sub_1F98D0_001f98d0__recomp},
    {"sub_1F99F0", 0x1F99F0, &recomp_gen::fn_sub_1F99F0_001f99f0, &recomp_gen::fn_sub_1F99F0_001f99f0__recomp},
    {"sub_1F9A80", 0x1F9A80, &recomp_gen::fn_sub_1F9A80_001f9a80, &recomp_gen::fn_sub_1F9A80_001f9a80__recomp},
    {"sub_1F9C60", 0x1F9C60, &recomp_gen::fn_sub_1F9C60_001f9c60, &recomp_gen::fn_sub_1F9C60_001f9c60__recomp},
};

const Case& fc(const char* name) { return find_case(kCases, name); }
namespace gp6 = game::f6::gp6;
constexpr u32 kSflState = 8, kSflFlags = 4;
constexpr u32 kResFlags = 0, kResStep = 4, kResMode = 8, kResEntries = 92, kEntrySize = 1648;
constexpr u32 kResCount = 13276, kKind0List = 28, kKind0Count = 13336, kKind1List = 60, kKind1Count = 13340;

// The Shuffle Time world: b_6150 after brRoot_CreateBattleResultTasks(packet with flag 1).
struct World {
    std::unique_ptr<Machine> m;
    std::vector<u8> base;
    u32 reserved = 0;
    u32 root_task = 0;
    bool ok = false;
};
World& world() {
    static World w;
    static bool made = false;
    if (made) return w;
    made = true;
    std::vector<u8> b;
    w.m = real_machine("b_6150", b);
    if (!w.m) return w;
    Machine& m = *w.m;
    constexpr u32 pkt = kScratch;
    std::vector<u32> absent;
    SiPair sp = run_absent_reserved(m, b, &recomp_gen::fn_brRoot_CreateBattleResultTasks_001ef500,
                                    &recomp_gen::fn_brRoot_CreateBattleResultTasks_001ef500__recomp, {pkt, 0, 0, 0}, 1,
                                    "brRoot_CreateBattleResultTasks (Shuffle Time)",
                                    [](Machine& mm) {
                                        write_rw_slots(mm);
                                        w32(mm, gpv(gp6::kBrRoot), 0);
                                        w32(mm, gpv(gp6::kSflRoot), 0);
                                        w32(mm, gpv(gp6::kSflResult), 0);
                                        std::memset(mm.at(pkt), 0, 0x100);
                                        w32(mm, pkt, 1);  // Shuffle Time follows
                                    },
                                    absent, 0);
    w.reserved = heap_used(*sp.recomp);
    w.base.assign(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    const u32 brw = r32(m, gpv(gp6::kBrRoot));
    w.root_task = brw ? r32(m, brw + 148) : 0;
    w.ok = w.root_task != 0 && r32(m, gpv(gp6::kSflRoot)) != 0 && r32(m, gpv(gp6::kSflResult)) != 0;
    return w;
}
SiPair run(const char* fn, Args args, u32 seed, const std::function<void(Machine&)>& extra = {}) {
    World& w = world();
    std::vector<u32> absent;
    return run_absent_reserved(*w.m, w.base, fc(fn).hand, fc(fn).recomp, args, seed, fn,
                               [&](Machine& mm) {
                                   write_rw_slots(mm);
                                   if (extra) extra(mm);
                               },
                               absent, w.reserved);
}
// A pair that may reach a part of the world this test does not build (a function pointer of a card or pose record the
// hand-placed entries leave empty): such a stop ends the pair as a skipped run (counted), any other result is checked.
s64 g_last_v0 = 0;
bool try_run(const char* fn, Args args, u32 seed, const std::function<void(Machine&)>& extra, int& skipped) {
    try {
        SiPair sp = run(fn, args, seed, extra);
        g_last_v0 = v0_of(sp.hw);
        return true;
    } catch (const rt_test::FatalEvent& e) {
        if (e.what.find("lookup_miss") == std::string::npos && e.what.find("budget") == std::string::npos) throw;
        ++skipped;
        return false;
    }
}
u32 sfl_root(Machine& m) { return r32(m, gpv(gp6::kSflRoot)); }
u32 sfl_res(Machine& m) { return r32(m, gpv(gp6::kSflResult)); }
// Two result entries: a persona card (kind 1, persona 9) and an arcana card (kind 0, arcana 3 / number 2).
void two_entries(Machine& m) {
    const u32 r = sfl_res(m);
    w32(m, r + kResCount, 2);
    w32(m, r + kResEntries + 0, 1);
    w32(m, r + kResEntries + 4, 9);
    w32(m, r + kResEntries + kEntrySize + 0, 0);
    w32(m, r + kResEntries + kEntrySize + 4, 3);
    w32(m, r + kResEntries + kEntrySize + 8, 2);
    w32(m, r + kKind1Count, 1);
    w32(m, r + kKind1List, 0);
    w32(m, r + kKind0Count, 1);
    w32(m, r + kKind0List, 1);
}

}  // namespace

TEST_CASE("game(field6 shuffle): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 32);
}

TEST_CASE("game(field6 shuffle): the root task on a Shuffle Time world built by the game's code (stand-ins)") {
    World& w = world();
    if (!w.ok) {
        MESSAGE("SKIP: no ELF / b_6150, or the Shuffle Time world could not be built");
        return;
    }
    Machine& m = *w.m;
    for (u32 state = 0; state <= 24; ++state) {
        INFO("root state " << state);
        run("sflRoot_UpdateShuffleRootTask", {w.root_task, 0, 0, 0}, 1 + state, [state](Machine& mm) { w32(mm, sfl_root(mm) + kSflState, state); });
    }
    run("sflRoot_UpdateShuffleRootDraw0Task", {w.root_task, 0, 0, 0}, 40);
    run("sflRoot_UpdateShuffleRootDraw1Task", {w.root_task, 0, 0, 0}, 41);
    {
        SiPair sp = run("sub_1F30F0", {w.root_task, 0, 0, 0}, 42);
        CHECK(r32(m, sfl_root(m) + 172560) == 1u);
        CHECK(r32(m, sfl_root(m) + 228) == 0u);
    }
    run("sub_1F3270", {w.root_task, 0, 0, 0}, 43);
    {
        SiPair sp = run("sub_1F4A00", {0, 0, 0, 0}, 44);
        CHECK((r32(m, sfl_root(m) + kSflFlags) & 0x20u) != 0u);
        bool started = false;
        for (const StandInCall& c : sp.recomp->si.log) started |= c.text == "sfl_root: start create shuffle command\n";
        CHECK(started);
    }
    {  // the pick's message: state 17, flag 0x40
        SiPair sp = run("sub_1F4750", {w.root_task, 0, 0, 0}, 45);
        CHECK(r32(m, sfl_root(m) + kSflState) == 17u);
        CHECK((r32(m, sfl_root(m) + kSflFlags) & 0x40u) != 0u);
    }
    {  // after the pick: a blank card (0x1000) -> its message, state 24; else the result, state 22
        run("sub_1F53A0", {0, 0, 0, 0}, 46, [](Machine& mm) {
            w32(mm, sfl_root(mm) + kSflState, 17);
            w32(mm, sfl_root(mm) + kSflFlags, r32(mm, sfl_root(mm) + kSflFlags) | 0x1000u);
        });
        CHECK(r32(m, sfl_root(m) + kSflState) == 24u);
        run("sub_1F53A0", {0, 0, 0, 0}, 47, [](Machine& mm) {
            w32(mm, sfl_root(mm) + kSflState, 21);
            w32(mm, sfl_root(mm) + kSflFlags, r32(mm, sfl_root(mm) + kSflFlags) & ~0x1000u);
        });
        CHECK(r32(m, sfl_root(m) + kSflState) == 22u);
        CHECK((r32(m, sfl_res(m) + kResFlags) & 2u) != 0u);   // the result started (sub_1F59B0; with no entries its pages
                                                               // end it at once, clearing flag 1 again)
        CHECK(r32(m, sfl_res(m) + 24) == 100u);
    }
    run("sub_1F54A0", {0, 0, 0, 0}, 48);
    CHECK(r32(m, sfl_root(m) + kSflState) == 24u);
    run("sub_1F55E0", {0, 0, 0, 0}, 49);
    CHECK(r32(m, sfl_root(m) + kSflState) == 11u);
    {  // the destroy clears the root's gp slot
        run("sub_1F2FD0", {w.root_task, 0, 0, 0}, 50);
        CHECK(sfl_root(m) == 0u);
        run("sub_1F2FF0", {w.root_task, 0, 0, 0}, 51);
        CHECK(sfl_root(m) == 0u);
    }
}

TEST_CASE("game(field6 shuffle): the result on two hand-placed cards (stand-ins)") {
    World& w = world();
    if (!w.ok) {
        MESSAGE("SKIP: no ELF / b_6150, or the Shuffle Time world could not be built");
        return;
    }
    Machine& m = *w.m;
    int skipped = 0, runs = 0;
    // Each pair below may stop at a record the two hand-placed entries leave empty (try_run); its checks run only when
    // the pair ran to the end.
    auto pr = [&](const char* fn, Args a, u32 seed, const std::function<void(Machine&)>& x) {
        ++runs;
        return try_run(fn, a, seed, x, skipped);
    };
    if (pr("sub_1F59B0", {0, 0, 0, 0}, 1, two_entries)) {  // start: two entries -> mode 1, flag 0x80
        CHECK(r32(m, sfl_res(m) + kResMode) == 1u);
        CHECK((r32(m, sfl_res(m) + kResFlags) & 0x83u) == 0x83u);
    }
    for (u32 step = 0; step <= 8; ++step) {
        INFO("result step " << step);
        pr("sub_1F5B20", {0, 0, 0, 0}, 10 + step, [step](Machine& mm) {
            two_entries(mm);
            w32(mm, sfl_res(mm) + kResFlags, 1u);
            w32(mm, sfl_res(mm) + kResMode, 1u);
            w32(mm, sfl_res(mm) + kResStep, step);
        });
        if (step == 0 || step == 3) continue;  // sub_1F6A60's steps 0 / 3 re-dispatch the same step forever (never entered)
        pr("sub_1F6A60", {0, 0, 0, 0}, 30 + step, [step](Machine& mm) {
            two_entries(mm);
            w32(mm, sfl_res(mm) + kResFlags, 0x19u);
            w32(mm, sfl_res(mm) + kResStep, step);
            w32(mm, sfl_res(mm) + 13312, 1u);
            w32(mm, sfl_res(mm) + 13316, 1u);
        });
    }
    pr("sub_1F64C0", {0, 0, 0, 0}, 50, [](Machine& mm) {
        two_entries(mm);
        w32(mm, sfl_res(mm) + kResFlags, 0x401u);
        w32(mm, sfl_res(mm) + kResMode, 1u);
    });
    pr("sub_1F6630", {0, 0, 0, 0}, 51, two_entries);
    pr("sub_1F6E80", {0, 0, 0, 0}, 52, two_entries);
    if (pr("sub_1F7030", {0, 0, 0, 0}, 53, two_entries)) CHECK(r32(m, sfl_res(m) + kResStep) == 5u);
    if (pr("sub_1F70D0", {0, 0, 0, 0}, 54, two_entries)) CHECK(r32(m, sfl_res(m) + kResStep) == 6u);
    if (pr("sub_1F7170", {0, 0, 0, 0}, 55, two_entries)) CHECK(r32(m, sfl_res(m) + kResStep) == 4u);
    if (pr("sub_1F99F0", {0, 0, 0, 0}, 56, two_entries)) CHECK(r32(m, sfl_res(m) + kResStep) == 2u);
    if (pr("sub_1F9A80", {0, 0, 0, 0}, 57, two_entries)) CHECK(r32(m, sfl_res(m) + kResStep) == 7u);
    for (u32 seed = 60; seed < 68; ++seed) pr("sub_1F7210", {0, 0, 0, 0}, seed, two_entries);
    pr("sub_1F9100", {0, 0, 0, 0}, 70, two_entries);
    pr("sub_1F9C60", {0, 0, 0, 0}, 71, two_entries);
    if (pr("sub_1F98D0", {0, 0, 0, 0}, 72, [](Machine& mm) {
            two_entries(mm);
            w32(mm, sfl_res(mm) + kResFlags, 0x80u);
            w32(mm, sfl_res(mm) + kResMode, 1u);
        }))
        CHECK((r32(m, sfl_res(m) + kResFlags) & 0x80u) == 0u);
    for (u32 row = 0; row < 24; ++row) {  // the card conditions: 0 or 1
        if (pr("sub_1F9170", {row, 0, 0, 0}, 80 + row, {})) {
            const s64 v = g_last_v0;
            CHECK((v == 0 || v == 1));
        }
    }
    if (pr("sub_1F5950", {0, 0, 0, 0}, 110, {})) CHECK(sfl_res(m) == 0u);
    MESSAGE("result pairs: " << runs << ", stopped at a record this world leaves empty: " << skipped);
    CHECK(skipped * 4 <= runs);
}

#else

TEST_CASE("game(field6 shuffle): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
