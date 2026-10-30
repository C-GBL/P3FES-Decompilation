// Pair tests of slice field6, part result (game/src/battle/field6_result.cpp): br_root.c / br_data.c / bp_root.c /
// bcm_main.c, each body against its recompiled body (handgen_pairs.h / pair_harness.h / stand_ins.h: the whole register
// file and cycles at every check point, all RAM including the dead stack, the stand-ins' call logs incl. printf), on
//   * random worlds: the p3fes_handgen sweep;
//   * b_6150 (the battle replay's result screen: the "battle result" task 0x1024AF0 in state 7 with its four draw
//     children) -- the state-7 button rule, the draw, the destroy, the level-up pass and its page rule, the persona
//     shift / drop picks; a hand-built battle packet for the packet copy;
//   * b_5800 (the battle: the "battle panel" task and the command menu work alive) -- the menu set-up's printed command
//     states against the disable mask, its flag clears, the menu update, the field-skill / item filters on the party,
//     the panel destroy (gp slot cleared), the panel creation on the dorm snapshot.
// Callees this build does not emit are stood in by recorders (field4_util.h run_pair_si_absent).
#include "field6_util.h"

#include "p3fes/game/field6_result.h"

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::f6t;

namespace p3fes::recomp_gen {
void fn_brRoot_CreateBattleResultTasks_001ef500(EEContext&);  // generated body
void fn_brRoot_CreateBattleResultTasks_001ef500__recomp(EEContext&);  // recompiled
void fn_brRoot_UpdateBattleResultTask_001ef7f0(EEContext&);  // generated body
void fn_brRoot_UpdateBattleResultTask_001ef7f0__recomp(EEContext&);  // recompiled
void fn_sub_1F07A0_001f07a0(EEContext&);  // generated body
void fn_sub_1F07A0_001f07a0__recomp(EEContext&);  // recompiled
void fn_sub_1F0990_001f0990(EEContext&);  // generated body
void fn_sub_1F0990_001f0990__recomp(EEContext&);  // recompiled
void fn_sub_1F0AD0_001f0ad0(EEContext&);  // generated body
void fn_sub_1F0AD0_001f0ad0__recomp(EEContext&);  // recompiled
void fn_sub_1F13B0_001f13b0(EEContext&);  // generated body
void fn_sub_1F13B0_001f13b0__recomp(EEContext&);  // recompiled
void fn_sub_1FB560_001fb560(EEContext&);  // generated body
void fn_sub_1FB560_001fb560__recomp(EEContext&);  // recompiled
void fn_sub_1FBA70_001fba70(EEContext&);  // generated body
void fn_sub_1FBA70_001fba70__recomp(EEContext&);  // recompiled
void fn_sub_1FC980_001fc980(EEContext&);  // generated body
void fn_sub_1FC980_001fc980__recomp(EEContext&);  // recompiled
void fn_sub_1FCB30_001fcb30(EEContext&);  // generated body
void fn_sub_1FCB30_001fcb30__recomp(EEContext&);  // recompiled
void fn_bpRoot_CreateBattlePanelTasks_001fd630(EEContext&);  // generated body
void fn_bpRoot_CreateBattlePanelTasks_001fd630__recomp(EEContext&);  // recompiled
void fn_sub_1FDC00_001fdc00(EEContext&);  // generated body
void fn_sub_1FDC00_001fdc00__recomp(EEContext&);  // recompiled
void fn_sub_1FF890_001ff890(EEContext&);  // generated body
void fn_sub_1FF890_001ff890__recomp(EEContext&);  // recompiled
void fn_sub_1FFF40_001fff40(EEContext&);  // generated body
void fn_sub_1FFF40_001fff40__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"brRoot_CreateBattleResultTasks", 0x1EF500, &recomp_gen::fn_brRoot_CreateBattleResultTasks_001ef500, &recomp_gen::fn_brRoot_CreateBattleResultTasks_001ef500__recomp},
    {"brRoot_UpdateBattleResultTask", 0x1EF7F0, &recomp_gen::fn_brRoot_UpdateBattleResultTask_001ef7f0, &recomp_gen::fn_brRoot_UpdateBattleResultTask_001ef7f0__recomp},
    {"sub_1F07A0", 0x1F07A0, &recomp_gen::fn_sub_1F07A0_001f07a0, &recomp_gen::fn_sub_1F07A0_001f07a0__recomp},
    {"sub_1F0990", 0x1F0990, &recomp_gen::fn_sub_1F0990_001f0990, &recomp_gen::fn_sub_1F0990_001f0990__recomp},
    {"sub_1F0AD0", 0x1F0AD0, &recomp_gen::fn_sub_1F0AD0_001f0ad0, &recomp_gen::fn_sub_1F0AD0_001f0ad0__recomp},
    {"sub_1F13B0", 0x1F13B0, &recomp_gen::fn_sub_1F13B0_001f13b0, &recomp_gen::fn_sub_1F13B0_001f13b0__recomp},
    {"sub_1FB560", 0x1FB560, &recomp_gen::fn_sub_1FB560_001fb560, &recomp_gen::fn_sub_1FB560_001fb560__recomp},
    {"sub_1FBA70", 0x1FBA70, &recomp_gen::fn_sub_1FBA70_001fba70, &recomp_gen::fn_sub_1FBA70_001fba70__recomp},
    {"sub_1FC980", 0x1FC980, &recomp_gen::fn_sub_1FC980_001fc980, &recomp_gen::fn_sub_1FC980_001fc980__recomp},
    {"sub_1FCB30", 0x1FCB30, &recomp_gen::fn_sub_1FCB30_001fcb30, &recomp_gen::fn_sub_1FCB30_001fcb30__recomp},
    {"bpRoot_CreateBattlePanelTasks", 0x1FD630, &recomp_gen::fn_bpRoot_CreateBattlePanelTasks_001fd630, &recomp_gen::fn_bpRoot_CreateBattlePanelTasks_001fd630__recomp},
    {"sub_1FDC00", 0x1FDC00, &recomp_gen::fn_sub_1FDC00_001fdc00, &recomp_gen::fn_sub_1FDC00_001fdc00__recomp},
    {"sub_1FF890", 0x1FF890, &recomp_gen::fn_sub_1FF890_001ff890, &recomp_gen::fn_sub_1FF890_001ff890__recomp},
    {"sub_1FFF40", 0x1FFF40, &recomp_gen::fn_sub_1FFF40_001fff40, &recomp_gen::fn_sub_1FFF40_001fff40__recomp},
};

const Case& fc(const char* name) { return find_case(kCases, name); }
namespace gp6 = game::f6::gp6;
namespace br = game::f6::br;
constexpr u32 kPadFlags = 0x7E094Eu;  // gPadFlags (u16): the buttons pressed this frame

// `stood`: recorders from the first run on (callees a later slice replaced that a check still expects recorded).
SiPair run(Machine& m, const std::vector<u8>& base, const char* fn, Args args, u32 seed, const std::function<void(Machine&)>& extra = {},
           const std::vector<u32>& stood = {}) {
    std::vector<u32> absent = stood;
    return run_pair_si_absent(m, base, fc(fn).hand, fc(fn).recomp, args, seed, fn, whole_ram_check(),
                              [&](Machine& mm) {
                                  write_rw_slots(mm);
                                  if (extra) extra(mm);
                              },
                              absent);
}
std::vector<std::string> printed(const SiPair& sp) {
    std::vector<std::string> out;
    for (const StandInCall& c : sp.recomp->si.log)
        if (c.va == kPrintf) out.push_back(c.text);
    return out;
}

}  // namespace

TEST_CASE("game(field6 result): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 48);
}

// The result screen of the battle replay (b_6150).
TEST_CASE("game(field6 result): the battle result task on b_6150 (stand-ins)") {
    std::vector<u8> base;
    auto mp = real_machine("b_6150", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no b_6150 snapshot");
        return;
    }
    Machine& m = *mp;
    const u32 work = r32(m, gpv(gp6::kBrRoot));
    REQUIRE(work != 0u);
    u32 task = 0;
    for (u32 t = 0x1024000u; t < 0x1026000u && !task; t += 4)  // the task whose work is it and whose update is ours
        if (r32(m, t + 60) == work && r32(m, t + 52) == 0x1EF7F0u) task = t;
    REQUIRE(task != 0u);
    CHECK(r32(m, work + br::kState) == 7u);
    {  // state 7 without a button: stays
        SiPair sp = run(m, base, "brRoot_UpdateBattleResultTask", {task, 0, 0, 0}, 1, [](Machine& mm) {
            w16(mm, kPadFlags, 0);
            w16(mm, 0x7E094Cu, 0);
        });
        CHECK(v0_of(sp.hw) == 0);
        CHECK(r32(m, work + br::kState) == 7u);
        CHECK(r32(m, work + 40) == 0u);
    }
    {  // the confirm button with no page to show: the BGM fades, the latch +40 = 1, flag 0x200000 cleared
        SiPair sp = run(m, base, "brRoot_UpdateBattleResultTask", {task, 0, 0, 0}, 2, [work](Machine& mm) {
            w16(mm, kPadFlags, 0x40);
            w32(mm, work + br::kPage, 0);
        });
        CHECK(r32(m, work + 40) == 1u);
        CHECK((r32(m, work + br::kFlags) & 0x200000u) == 0u);
    }
    {  // flag 0x40: one frame skipped (the flag cleared, nothing else)
        SiPair sp = run(m, base, "brRoot_UpdateBattleResultTask", {task, 0, 0, 0}, 3, [work](Machine& mm) {
            w32(mm, work + br::kFlags, r32(mm, work + br::kFlags) | 0x40u);
        });
        CHECK((r32(m, work + br::kFlags) & 0x40u) == 0u);
        CHECK(r32(m, work + br::kState) == 7u);
    }
    for (u32 state : {0u, 1u, 3u, 4u, 5u, 6u, 8u, 9u, 12u}) {  // the other states on the same work (pairs)
        INFO("state " << state);
        run(m, base, "brRoot_UpdateBattleResultTask", {task, 0, 0, 0}, 10 + state, [work, state](Machine& mm) {
            w32(mm, work + br::kState, state);
        });
    }
    // the first draw child, with and without the level-up quad
    u32 draw = 0;
    for (u32 t = 0x1024000u; t < 0x1026000u && !draw; t += 4)
        if (r32(m, t + 60) == work && r32(m, t + 52) == 0x1F07A0u) draw = t;
    if (draw) {
        run(m, base, "sub_1F07A0", {draw, 0, 0, 0}, 30);
        run(m, base, "sub_1F07A0", {draw, 0, 0, 0}, 31, [work](Machine& mm) { w32(mm, work, r32(mm, work) | 0x10000u); });
    }
    {  // the destroy: the work is freed
        // sub_3C77A0 / sub_233E70 are hand-written since sweep5 and free their own blocks: recorded as before, so the
        // RwFree count below is the destroy's own (the panel resource release sub_21BB60, hand-written since finalB,
        // frees its six blocks: recorded as before too)
        SiPair sp = run(m, base, "sub_1F0990", {task, 0, 0, 0}, 32, {}, {0x3C77A0u, 0x233E70u, 0x21BB60u});
        CHECK(sp.recomp->si.calls_to(kRwSlotFns[1]) == 1);
    }
    {  // the level-up pass and its page rule: members -> 3, the hero's level -> 2, skills -> 1, else 0
        SiPair sp = run(m, base, "sub_1F13B0", {task, 0, 0, 0}, 33);
        const u32 flags = r32(m, work + br::kFlags);
        const u32 page = r32(m, work + br::kPage);
        const u32 expect = r32(m, work + 236) ? 3u : (flags & 8u) ? 2u : (flags & 4u) ? 1u : 0u;
        CHECK(page == expect);
        CHECK(((flags & 8u) != 0) == (r32(m, work + br::kLvBefore) != r32(m, work + br::kLvAfter)));
        bool lv_printed = false;
        for (const std::string& s : printed(sp)) lv_printed |= s.rfind("player lv ", 0) == 0;
        CHECK(lv_printed);
    }
    // the persona shift / drop picks for every persona of the stock (and a few others)
    for (s32 id : {1, 2, 9, 20, 40, 80, 120, 191}) {
        INFO("persona " << id);
        run(m, base, "sub_1FB560", {static_cast<u64>(id), 0, 0, 0}, 40 + static_cast<u32>(id));
        run(m, base, "sub_1FBA70", {static_cast<u64>(id), 0, 0, 0}, 300 + static_cast<u32>(id));
    }
}

// The packet copy (sub_1F0AD0) on a hand-built packet: the outcome flags, the unit list, the counts, the drop ids
// that are not 1.
TEST_CASE("game(field6 result): the battle packet copy (stand-ins)") {
    std::vector<u8> base;
    auto mp = real_machine("b_6150", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no b_6150 snapshot");
        return;
    }
    Machine& m = *mp;
    const u32 task = kScratch, work = kScratch + 0x1000, pkt = kScratch + 0x100;
    SiPair sp = run(m, base, "sub_1F0AD0", {task, pkt, 0, 0}, 1, [=](Machine& mm) {
        std::memset(mm.at(kScratch), 0, 0x1000);
        std::memset(mm.at(work), 0, 0x4000);
        w32(mm, task + 60, work);
        w32(mm, pkt + 0, 3);    // flag 1 (Shuffle Time) and flag 2
        w32(mm, pkt + 28, 3);   // three unit entries {u16 id at +4, s32 at +8}
        for (u32 i = 0; i < 3; ++i) {
            w16(mm, pkt + 8 * i + 4, static_cast<u16>(10 + i));
            w32(mm, pkt + 8 * i + 8, 100 + i);
        }
        w32(mm, pkt + 32, 77);
        w32(mm, pkt + 44, 4);   // the drop count, ids at +36 (one of them 1: skipped)
        w16(mm, pkt + 36, 5);
        w16(mm, pkt + 38, 1);
        w16(mm, pkt + 40, 6);
        w16(mm, pkt + 42, 7);
        w32(mm, pkt + 48, 2);
        w32(mm, pkt + 52, 500);
        w32(mm, pkt + 56, 600);
        w32(mm, pkt + 60, 700);
        w32(mm, pkt + 64, 800);
    });
    CHECK((r32(m, work) & 2u) != 0u);
    CHECK(r32(m, work + 176) == 3u);
    CHECK(r32(m, work + 180) == 77u);
    for (u32 i = 0; i < 3; ++i) {
        CHECK(r16(m, work + 152 + 8 * i) == 10 + i);
        CHECK(r32(m, work + 156 + 8 * i) == 100 + i);
    }
    CHECK(r32(m, work + 280) == 4u);   // units (packet +44, the drop count's word)
    CHECK(r32(m, work + 284) == 2u);   // dead units (+48)
    CHECK(r32(m, work + 276) == 3u);   // the drop ids that are not 1
    CHECK(r16(m, work + 268) == 5);
    CHECK(r16(m, work + 270) == 6);
    CHECK(r16(m, work + 272) == 7);
    CHECK(r32(m, work + 288) == 1u);   // packet flag 2
    const std::vector<std::string> p = printed(sp);
    REQUIRE(p.size() == 2);
    CHECK(p[0] == "num_unit 4\n");
    CHECK(p[1] == "num_unit_dead 2\n");
}

// The command menu and the panel on b_5800 (a battle in progress).
TEST_CASE("game(field6 result): the command menu and the battle panel on b_5800 (stand-ins)") {
    std::vector<u8> base;
    auto mp = real_machine("b_5800", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no b_5800 snapshot");
        return;
    }
    Machine& m = *mp;
    const u32 bcm = r32(m, gpv(gp6::kBcm));
    REQUIRE(bcm != 0u);
    for (u32 mask : {0u, 0x7Fu, 0x15u}) {  // the seven commands' printed states follow the disable mask
        INFO("mask " << mask);
        SiPair sp = run(m, base, "sub_1FF890", {0, 0, 0, 0}, 1 + mask, [bcm, mask](Machine& mm) { w32(mm, bcm + 30624, mask); });
        static const char* const kNames[7] = {"ATTACK", "SKILL", "ITEM", "PERSONA", "ESCAPE", "WAIT", "OPERATION"};
        const std::vector<std::string> p = printed(sp);
        REQUIRE(p.size() >= 7);
        for (u32 i = 0; i < 7; ++i) CHECK(p[i] == std::string(kNames[i]) + ((mask >> i) & 1u ? " : OFF\n" : " : ON\n"));
        CHECK(r32(m, bcm + 4) == 0u);
        CHECK(r32(m, bcm + 30628) == 0u);
        CHECK((r32(m, bcm + 8) & ~7u) == 0u);  // the start mode: bits 1 / 2 / 4 only
    }
    for (u32 seed = 20; seed < 26; ++seed) run(m, base, "sub_1FFF40", {0, 0, 0, 0}, seed, [seed](Machine& mm) { w16(mm, kPadFlags, static_cast<u16>(1u << (seed - 20))); });
    // the field-skill / item filters for the party's characters: only skills 192..194 / items 4001 / 4002 qualify
    for (u16 pc = 1; pc <= 7; ++pc) {
        const u32 unit = kScratch, out = kScratch + 0x100, cnt = kScratch + 0x200;
        SiPair sp = run(m, base, "sub_1FC980", {unit, out, cnt, 0}, 40 + pc, [=](Machine& mm) {
            std::memset(mm.at(kScratch), 0, 0x300);
            w16(mm, unit + 2, pc);
        });
        const u32 n = r32(m, cnt);
        CHECK(n <= 3u);
        for (u32 i = 0; i < n; ++i) {
            const u16 skill = r16(m, out + 2 * i);
            CHECK((skill >= 192 && skill <= 194));
        }
        sp = run(m, base, "sub_1FCB30", {unit, out, cnt, 0}, 60 + pc, [=](Machine& mm) {
            std::memset(mm.at(kScratch), 0, 0x300);
            w16(mm, unit + 2, pc);
        });
        const u32 k = r32(m, cnt);
        CHECK(k <= 12u);
        for (u32 i = 0; i < k; ++i) {
            const u32 item = r32(m, out + 4 * i);
            CHECK((item == 4001u || item == 4002u));
        }
    }
    {  // the panel destroy clears gp 0x7CE2E4 and frees the work
        const u32 task = r32(m, gpv(gp6::kBpRoot));
        REQUIRE(task != 0u);
        // (the resource release sub_21BB60, hand-written since finalB, is recorded: the count below is the work's free)
        SiPair sp = run(m, base, "sub_1FDC00", {task, 0, 0, 0}, 80, {}, {0x21BB60u});
        CHECK(r32(m, gpv(gp6::kBpRoot)) == 0u);
        CHECK(sp.recomp->si.calls_to(kRwSlotFns[1]) == 1);
    }
    {  // a new panel (the creation on the dorm snapshot: no battle running)
        std::vector<u8> dbase;
        auto dp = real_machine("dorm_replay_4900", dbase);
        if (!dp) return;
        SiPair sp = run(*dp, dbase, "bpRoot_CreateBattlePanelTasks", {0, 0, 0, 0}, 81);
        const u32 task = static_cast<u32>(v0_of(sp.hw));
        CHECK(task != 0u);
        CHECK(r32(*dp, gpv(gp6::kBpRoot)) == task);
    }
    {  // a new result screen on the dorm snapshot from a hand-built packet without Shuffle Time
        std::vector<u8> dbase;
        auto dp = real_machine("dorm_replay_4900", dbase);
        if (!dp) return;
        constexpr u32 pkt = kScratch;
        SiPair sp = run(*dp, dbase, "brRoot_CreateBattleResultTasks", {pkt, 0, 0, 0}, 82, [](Machine& mm) { std::memset(mm.at(pkt), 0, 0x100); });
        const u32 work = r32(*dp, gpv(gp6::kBrRoot));
        CHECK(work != 0u);
        if (work) {
            CHECK(r32(*dp, work + br::kState) == 0u);
            CHECK(r32(*dp, work + 10844) == 100u);
            CHECK((r32(*dp, work + br::kLoading) & 2u) != 0u);  // the result resources requested
        }
    }
}

#else

TEST_CASE("game(field6 result): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
