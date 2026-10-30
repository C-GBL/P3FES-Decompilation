// Pair tests of slice field8, group field (game/src/sweep/field8_field.cpp): every body against its recompiled body
//   * on random worlds (the p3fes_handgen sweep, each random draw its own statement);
//   * on built and real worlds with the documented rules: a debug list box built with field7's creators (the value
//     column's formats, the update's states, the window's open / close, the destroys freeing their blocks, the colour
//     box), the EPL delay queue's update, MT_Scene's flag setters / light set-ups / free index on the dorm snapshot, the
//     model-load wait task and the circle draw, the RpUserData searches and material walkers on the snapshots' clumps.
#include "field8_util.h"

#include "p3fes/game/field7_epl.h"
#include "p3fes/game/field7_lbox.h"
#include "p3fes/game/models.h"
#include "p3fes/game/task.h"

#include <algorithm>
#include <cstring>
#include <map>
#include <memory>
#include <string>
#include <vector>
#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_sub_1A0590_001a0590(EEContext&);  // generated body
void fn_sub_1A0590_001a0590__recomp(EEContext&);  // recompiled
void fn_sub_1A0A90_001a0a90(EEContext&);  // generated body
void fn_sub_1A0A90_001a0a90__recomp(EEContext&);  // recompiled
void fn_sub_1A0E50_001a0e50(EEContext&);  // generated body
void fn_sub_1A0E50_001a0e50__recomp(EEContext&);  // recompiled
void fn_sub_1A0EE0_001a0ee0(EEContext&);  // generated body
void fn_sub_1A0EE0_001a0ee0__recomp(EEContext&);  // recompiled
void fn_sub_1A1550_001a1550(EEContext&);  // generated body
void fn_sub_1A1550_001a1550__recomp(EEContext&);  // recompiled
void fn_sub_1A2170_001a2170(EEContext&);  // generated body
void fn_sub_1A2170_001a2170__recomp(EEContext&);  // recompiled
void fn_sub_1A2720_001a2720(EEContext&);  // generated body
void fn_sub_1A2720_001a2720__recomp(EEContext&);  // recompiled
void fn_sub_1A2A80_001a2a80(EEContext&);  // generated body
void fn_sub_1A2A80_001a2a80__recomp(EEContext&);  // recompiled
void fn_sub_1A3A60_001a3a60(EEContext&);  // generated body
void fn_sub_1A3A60_001a3a60__recomp(EEContext&);  // recompiled
void fn_sub_1A4940_001a4940(EEContext&);  // generated body
void fn_sub_1A4940_001a4940__recomp(EEContext&);  // recompiled
void fn_sub_1A5280_001a5280(EEContext&);  // generated body
void fn_sub_1A5280_001a5280__recomp(EEContext&);  // recompiled
void fn_sub_1A5320_001a5320(EEContext&);  // generated body
void fn_sub_1A5320_001a5320__recomp(EEContext&);  // recompiled
void fn_sub_1A5C50_001a5c50(EEContext&);  // generated body
void fn_sub_1A5C50_001a5c50__recomp(EEContext&);  // recompiled
void fn_sub_1A5DE0_001a5de0(EEContext&);  // generated body
void fn_sub_1A5DE0_001a5de0__recomp(EEContext&);  // recompiled
void fn_sub_1A6350_001a6350(EEContext&);  // generated body
void fn_sub_1A6350_001a6350__recomp(EEContext&);  // recompiled
void fn_sub_1A64F0_001a64f0(EEContext&);  // generated body
void fn_sub_1A64F0_001a64f0__recomp(EEContext&);  // recompiled
void fn_sub_1A65C0_001a65c0(EEContext&);  // generated body
void fn_sub_1A65C0_001a65c0__recomp(EEContext&);  // recompiled
void fn_sub_1A66F0_001a66f0(EEContext&);  // generated body
void fn_sub_1A66F0_001a66f0__recomp(EEContext&);  // recompiled
void fn_sub_1A6740_001a6740(EEContext&);  // generated body
void fn_sub_1A6740_001a6740__recomp(EEContext&);  // recompiled
void fn_sub_1A7370_001a7370(EEContext&);  // generated body
void fn_sub_1A7370_001a7370__recomp(EEContext&);  // recompiled
void fn_sub_1A74E0_001a74e0(EEContext&);  // generated body
void fn_sub_1A74E0_001a74e0__recomp(EEContext&);  // recompiled
void fn_sub_1A7910_001a7910(EEContext&);  // generated body
void fn_sub_1A7910_001a7910__recomp(EEContext&);  // recompiled
void fn_sub_1A88E0_001a88e0(EEContext&);  // generated body
void fn_sub_1A88E0_001a88e0__recomp(EEContext&);  // recompiled
void fn_sub_1A9500_001a9500(EEContext&);  // generated body
void fn_sub_1A9500_001a9500__recomp(EEContext&);  // recompiled
void fn_sub_1AE580_001ae580(EEContext&);  // generated body
void fn_sub_1AE580_001ae580__recomp(EEContext&);  // recompiled
void fn_sub_1A3B10_001a3b10(EEContext&);
void fn_sub_1A3B10_001a3b10__recomp(EEContext&);
void fn_sub_1A3F20_001a3f20(EEContext&);
void fn_sub_1A3F20_001a3f20__recomp(EEContext&);
void fn_sub_1A4090_001a4090(EEContext&);
void fn_sub_1A4090_001a4090__recomp(EEContext&);
void fn_sub_1A4110_001a4110(EEContext&);
void fn_sub_1A4110_001a4110__recomp(EEContext&);
void fn_sub_1A41F0_001a41f0(EEContext&);
void fn_sub_1A41F0_001a41f0__recomp(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game_test::f8t;

const Case kCases[] = {
    {"sub_1A0590", 0x1A0590, &recomp_gen::fn_sub_1A0590_001a0590, &recomp_gen::fn_sub_1A0590_001a0590__recomp},
    {"sub_1A0A90", 0x1A0A90, &recomp_gen::fn_sub_1A0A90_001a0a90, &recomp_gen::fn_sub_1A0A90_001a0a90__recomp},
    {"sub_1A0E50", 0x1A0E50, &recomp_gen::fn_sub_1A0E50_001a0e50, &recomp_gen::fn_sub_1A0E50_001a0e50__recomp},
    {"sub_1A0EE0", 0x1A0EE0, &recomp_gen::fn_sub_1A0EE0_001a0ee0, &recomp_gen::fn_sub_1A0EE0_001a0ee0__recomp},
    {"sub_1A1550", 0x1A1550, &recomp_gen::fn_sub_1A1550_001a1550, &recomp_gen::fn_sub_1A1550_001a1550__recomp},
    {"sub_1A2170", 0x1A2170, &recomp_gen::fn_sub_1A2170_001a2170, &recomp_gen::fn_sub_1A2170_001a2170__recomp},
    {"sub_1A2720", 0x1A2720, &recomp_gen::fn_sub_1A2720_001a2720, &recomp_gen::fn_sub_1A2720_001a2720__recomp},
    {"sub_1A2A80", 0x1A2A80, &recomp_gen::fn_sub_1A2A80_001a2a80, &recomp_gen::fn_sub_1A2A80_001a2a80__recomp},
    {"sub_1A3A60", 0x1A3A60, &recomp_gen::fn_sub_1A3A60_001a3a60, &recomp_gen::fn_sub_1A3A60_001a3a60__recomp},
    {"sub_1A4940", 0x1A4940, &recomp_gen::fn_sub_1A4940_001a4940, &recomp_gen::fn_sub_1A4940_001a4940__recomp},
    {"sub_1A5280", 0x1A5280, &recomp_gen::fn_sub_1A5280_001a5280, &recomp_gen::fn_sub_1A5280_001a5280__recomp},
    {"sub_1A5320", 0x1A5320, &recomp_gen::fn_sub_1A5320_001a5320, &recomp_gen::fn_sub_1A5320_001a5320__recomp},
    {"sub_1A5C50", 0x1A5C50, &recomp_gen::fn_sub_1A5C50_001a5c50, &recomp_gen::fn_sub_1A5C50_001a5c50__recomp},
    {"sub_1A5DE0", 0x1A5DE0, &recomp_gen::fn_sub_1A5DE0_001a5de0, &recomp_gen::fn_sub_1A5DE0_001a5de0__recomp},
    {"sub_1A6350", 0x1A6350, &recomp_gen::fn_sub_1A6350_001a6350, &recomp_gen::fn_sub_1A6350_001a6350__recomp},
    {"sub_1A64F0", 0x1A64F0, &recomp_gen::fn_sub_1A64F0_001a64f0, &recomp_gen::fn_sub_1A64F0_001a64f0__recomp},
    {"sub_1A65C0", 0x1A65C0, &recomp_gen::fn_sub_1A65C0_001a65c0, &recomp_gen::fn_sub_1A65C0_001a65c0__recomp},
    {"sub_1A66F0", 0x1A66F0, &recomp_gen::fn_sub_1A66F0_001a66f0, &recomp_gen::fn_sub_1A66F0_001a66f0__recomp},
    {"sub_1A6740", 0x1A6740, &recomp_gen::fn_sub_1A6740_001a6740, &recomp_gen::fn_sub_1A6740_001a6740__recomp},
    {"sub_1A7370", 0x1A7370, &recomp_gen::fn_sub_1A7370_001a7370, &recomp_gen::fn_sub_1A7370_001a7370__recomp},
    {"sub_1A74E0", 0x1A74E0, &recomp_gen::fn_sub_1A74E0_001a74e0, &recomp_gen::fn_sub_1A74E0_001a74e0__recomp},
    {"sub_1A7910", 0x1A7910, &recomp_gen::fn_sub_1A7910_001a7910, &recomp_gen::fn_sub_1A7910_001a7910__recomp},
    {"sub_1A88E0", 0x1A88E0, &recomp_gen::fn_sub_1A88E0_001a88e0, &recomp_gen::fn_sub_1A88E0_001a88e0__recomp},
    {"sub_1A9500", 0x1A9500, &recomp_gen::fn_sub_1A9500_001a9500, &recomp_gen::fn_sub_1A9500_001a9500__recomp},
    {"sub_1AE580", 0x1AE580, &recomp_gen::fn_sub_1AE580_001ae580, &recomp_gen::fn_sub_1AE580_001ae580__recomp},
};

namespace rg = p3fes::recomp_gen;
namespace lbox = p3fes::game::f7::lbox;
namespace epl = p3fes::game::f7::epl;

constexpr u32 kParent = 0x01B80000u;   // a parent task for the creators (field7_lbox's world)
constexpr u32 kStrings = 0x01B84000u;  // guest strings, 256 bytes each

void clean_world(Machine& m) {
    std::memset(m.at(0x7CE064u), 0, 0x7CE088u - 0x7CE064u);  // the kwln starting / ending / running lists
    std::memset(m.at(kParent), 0, 0x8000);
    w32(m, kParent + game::kwln::kOffWork, kParent + 0x100u);
    w32(m, kParent + game::kwln::kOffState, 2);
}
u32 put_string(Machine& m, u32 slot, const std::string& s) {
    const u32 va = kStrings + 256u * slot;
    std::memset(m.at(va), 0, 256);
    std::memcpy(m.at(va), s.data(), s.size());
    return va;
}

// A sequence of pairs on one machine that carries the stand-in heap's live blocks from pair to pair (the creators'
// RwMalloc blocks stay live for the later calls), with every callee this build does not emit stood in by a recorder:
// a missing-function stop restores the RAM from before the call, adds the recorder and runs the pair again.
struct Seq {
    explicit Seq(Machine& mm) : m(mm) {}
    Machine& m;
    std::map<u32, u32> live;
    std::vector<u32> absent;
    u32 seed = 1;
    int pairs = 0;
    std::vector<StandInCall> last_log;
    u64 call(Fn hand, Fn recomp, const Args& args, const char* what, u64 t0 = 0, u64 t1 = 0,
             const std::function<void(StandInWorld&)>& extra = {}) {
        const std::vector<u8> before(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        HwCheck hw = whole_ram_check();
        hw.gpr_in[GPR_T0] = t0;
        hw.gpr_in[GPR_T1] = t1;
        for (int tries = 0;; ++tries) {
            try {
                const std::map<u32, u32> carried = live;
                const std::vector<u32> list = absent;
                SiPair p = run_pair_si(m, hand, recomp, args, seed++, what, hw, [&, carried, list](StandInWorld& w) {
                    install_field_world(w);
                    for (const auto& [b, n] : carried) w.heap.reserve(b, n);
                    for (u32 va : list) w.si.install_recorder(va, "absent", 0);
                    if (extra) extra(w);
                });
                ++pairs;
                live = p.recomp->heap.live();
                last_log = p.recomp->si.log;
                return p.hw.recomp.base.v0;
            } catch (const rt_test::FatalEvent& e) {
                const std::size_t k = e.what.find("function at 0x");
                if (k == std::string::npos || tries >= 32) throw;
                absent.push_back(static_cast<u32>(std::stoul(e.what.substr(k + 12, 10), nullptr, 16)));
                std::memcpy(m.mem.main_ram(), before.data(), before.size());
            }
        }
    }
    std::vector<std::string> texts() const {
        std::vector<std::string> out;
        for (const StandInCall& c : last_log)
            if (c.va == kVsprintf || c.va == kSprintf) out.push_back(c.text);
        return out;
    }
};
template <std::size_t N>
Fn hand_of(const Case (&cases)[N], const char* n) { return find_case(cases, n).hand; }
template <std::size_t N>
Fn recomp_of(const Case (&cases)[N], const char* n) { return find_case(cases, n).recomp; }

}  // namespace

TEST_CASE("game(field8 field): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 48);
}

// --- the debug widgets -------------------------------------------------------------------------------------------
// A list box built with field7's creators (labels, string / flag / int / hex values), then: the value column draws
// each visible row's value with its kind's format (" %s" right-aligned, "  TRUE" / " FALSE", " %8d", " 0x%08X"),
// the update runs its states (0 waits for the box to be shown, 1 makes the window, 2 waits for it, 3 the open frames,
// 5 ends with -1), the destroy frees the items and the work. The window update steps from 0 to open and from the fade-out
// to done (-1); its destroy frees the buffer and the work. The colour box copies the four list-box values into its target
// and ends on the pad's 0x20 bit.
TEST_CASE("game(field8 field): the ksk window, list box and colour box updates and destroys") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);  // RenderWare is up for the 2-D objects
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    write_rw_slots(m);
    clean_world(m);
    Seq s{m};
    const u32 task = static_cast<u32>(s.call(&rg::fn_sub_1A3B10_001a3b10, &rg::fn_sub_1A3B10_001a3b10__recomp,
                                             {sx(kParent), 40, 60, 2}, "sub_1A3B10 create"));
    REQUIRE(task != 0u);
    const u32 work = r32(m, task + lbox::kTaskWork);
    struct Row {
        std::string label;
        u32 kind;
        u32 value;
        u32 hex;
        std::string text;
    };
    const Row rows[] = {{"NAME", 1, 0, 0, "kosaka"}, {"ON", 2, 1, 0, ""}, {"OFF", 2, 0, 0, ""}, {"COUNT", 3, 42, 0, ""},
                        {"MASK", 3, 0xBEEF, 1, ""},  {"NEG", 3, static_cast<u32>(-7), 0, ""}, {"PLAIN", 0, 0, 0, ""}};
    u32 slot = 0;
    for (const Row& r : rows) {
        const u32 label = put_string(m, slot++, r.label);
        const u32 id = static_cast<u32>(s.call(&rg::fn_sub_1A3F20_001a3f20, &rg::fn_sub_1A3F20_001a3f20__recomp,
                                               {sx(task), sx(label), 0, 0}, "sub_1A3F20 add"));
        if (r.kind == 1) {
            const u32 text = put_string(m, slot++, r.text);
            s.call(&rg::fn_sub_1A4090_001a4090, &rg::fn_sub_1A4090_001a4090__recomp, {sx(task), sx(id), sx(text), 0}, "set string");
        } else if (r.kind == 2) {
            s.call(&rg::fn_sub_1A41F0_001a41f0, &rg::fn_sub_1A41F0_001a41f0__recomp, {sx(task), sx(id), r.value, 0}, "set flag");
        } else if (r.kind == 3) {
            s.call(&rg::fn_sub_1A4110_001a4110, &rg::fn_sub_1A4110_001a4110__recomp, {sx(task), sx(id), sx(r.value), static_cast<u64>(s64{-100})},
                   "set int", 0x10000, r.hex);
        }
    }
    CHECK(r32(m, work + lbox::kBoxCount) == 7u);
    // the value column: one formatted value per visible row with a value, in its kind's format
    s.call(hand_of(kCases, "sub_1A2720"), recomp_of(kCases, "sub_1A2720"), {sx(task), 0, 0, 0}, "sub_1A2720 values");
    const std::vector<std::string> t = s.texts();
    const auto has = [&](const std::string& x) { return std::find(t.begin(), t.end(), x) != t.end(); };
    CHECK(has(" kosaka"));
    CHECK(has("  TRUE"));
    CHECK(has(" FALSE"));
    CHECK(has("       42"));
    CHECK(has(" 0x0000BEEF"));
    CHECK(has("       -7"));
    for (const Row& r : rows) CHECK(has(r.label));
    // the update's states
    const u32 state_va = work + 0;
    for (u32 st : {0u, 1u, 2u, 3u, 3u, 4u, 5u}) {
        w32(m, state_va, st);
        w32(m, work + 12, 1);  // shown
        const s64 v0 = static_cast<s32>(static_cast<u32>(
            s.call(hand_of(kCases, "sub_1A2A80"), recomp_of(kCases, "sub_1A2A80"), {sx(task), 0, 0, 0}, "sub_1A2A80 update")));
        CHECK(v0 == (st == 5 ? -1 : 0));
        if (st == 0) CHECK(r32(m, state_va) == 1u);
        if (st == 1) {
            CHECK(r32(m, state_va) == 2u);
            CHECK(r32(m, work + lbox::kBoxWindow) != 0u);
        }
    }
    // the window the box made: its own update from the build to open, then fading out to done
    const u32 win = r32(m, work + lbox::kBoxWindow);
    REQUIRE(win != 0u);
    const u32 wwork = r32(m, win + lbox::kTaskWork);
    int frames = 0;
    w32(m, wwork + lbox::kWinState, 0);
    for (; frames < 120 && r32(m, wwork + lbox::kWinState) != 6u; ++frames)
        CHECK(s.call(hand_of(kCases, "sub_1A1550"), recomp_of(kCases, "sub_1A1550"), {sx(win), 0, 0, 0}, "sub_1A1550 open") == 0u);
    CHECK(r32(m, wwork + lbox::kWinState) == 6u);
    // the fade-out: the fill alpha (+35) and the frame alpha (+31) drop by one a frame; at fill 0 the state moves to
    // done, which answers -1
    w32(m, wwork + lbox::kWinState, 7);
    w8(m, wwork + 35, 3);
    w8(m, wwork + 31, 1);
    for (u32 k = 0; k < 3; ++k) {
        CHECK(s.call(hand_of(kCases, "sub_1A1550"), recomp_of(kCases, "sub_1A1550"), {sx(win), 0, 0, 0}, "sub_1A1550 close") == 0u);
        CHECK(r8(m, wwork + 35) == 2u - k);
        CHECK(r8(m, wwork + 31) == 0u);
        CHECK(r32(m, wwork + lbox::kWinState) == (k == 2 ? 8u : 7u));
    }
    const s64 last = static_cast<s32>(static_cast<u32>(
        s.call(hand_of(kCases, "sub_1A1550"), recomp_of(kCases, "sub_1A1550"), {sx(win), 0, 0, 0}, "sub_1A1550 done")));
    CHECK(last == -1);
    // the destroys free their blocks
    const std::size_t live_before = s.live.size();
    s.call(hand_of(kCases, "sub_1A2170"), recomp_of(kCases, "sub_1A2170"), {sx(win), 0, 0, 0}, "sub_1A2170 destroy");
    CHECK(s.live.size() < live_before);
    CHECK(s.live.count(wwork) == 0u);
    s.call(hand_of(kCases, "sub_1A3A60"), recomp_of(kCases, "sub_1A3A60"), {sx(task), 0, 0, 0}, "sub_1A3A60 destroy");
    CHECK(s.live.count(work) == 0u);
    CHECK(r32(m, work + lbox::kBoxCount) == 0u);
    // the colour box: the list box's four values (a stand-in getter answering one cell) into the target; the end bit
    constexpr u32 cbox = kScratch, target = kScratch + 0x40, cell = kScratch + 0x80;
    for (const u16 pad : {u16{0}, u16{0x20}}) {
        std::memset(m.at(cbox), 0, 12);
        w32(m, cbox + 0, 1);
        w32(m, cbox + 8, target);
        w32(m, target, 0);
        w32(m, cell, 0x5A);
        w32(m, kScratch + 0xC0, cbox);  // a task whose work is the box
        w32(m, kScratch + 0xC0 + lbox::kTaskWork, cbox);
        w16(m, 0x7E094Eu, pad);
        s.call(hand_of(kCases, "sub_1A4940"), recomp_of(kCases, "sub_1A4940"), {sx(kScratch + 0xC0), 0, 0, 0}, "sub_1A4940",
               0, 0, [](StandInWorld& w) { w.si.install_recorder(0x1A41B0u, "sub_1A41B0 (box int)", cell); });
        CHECK(r32(m, target) == 0x5A5A5A5Au);
        CHECK(r32(m, cbox) == (pad ? 2u : 1u));
    }
    MESSAGE("debug widgets: " << s.pairs << " pairs, absent callees " << s.absent.size());
}

// --- the EPL delay queue -----------------------------------------------------------------------------------------
// sub_1A9500 on the dorm snapshot's field (K_Field_Get's EPL table): 0 -> 1; idle with requests: the oldest starts
// (sub_1A91B0 with the request's position), the queue moves down one entry, the counter restarts, counting (2);
// counting: +1 per frame up to the delay, then idle (1); 3 answers -1.
TEST_CASE("game(field8 field): the epl delay queue's update (dorm snapshot)") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    constexpr u32 kTask = kScratch, kWork = kScratch + 0x100;
    u32 seed = 1;
    int n = 0;
    for (u32 state = 0; state < 4; ++state) {
        for (const u32 count : {0u, 1u, 5u}) {
            for (const u32 counter : {0u, 19u, 20u}) {
                SiPair sp = run_f8(m, base, kCases, "sub_1A9500", {kTask, 0, 0, 0}, seed++, [&](Machine& mm) {
                    std::memset(mm.at(kTask), 0, 0x100 + epl::kDelayWorkSize);
                    w32(mm, kTask + epl::kTaskWork, kWork);
                    w32(mm, kWork + 0, state);
                    w32(mm, kWork + epl::kDelayWait, 20);
                    w32(mm, kWork + 8, counter);
                    w32(mm, kWork + epl::kDelayCount, count);
                    for (u32 i = 0; i < 8; ++i) {
                        w32(mm, kWork + epl::kDelayId + 4 * i, i & 1);
                        wf32(mm, kWork + epl::kDelayPos + 12 * i, 100.0f + static_cast<float>(i));
                        w32(mm, kWork + epl::kDelayArg3 + 4 * i, static_cast<u32>(-1));
                        w32(mm, kWork + epl::kDelayArg4 + 4 * i, i);
                    }
                }, [](StandInWorld& w) {  // sub_1A91B0: hand-written since sweep5a, recorded as when it was absent
                    w.si.install_recorder(0x1A91B0u, "absent", 0);
                });
                ++n;
                const s64 v0 = v0_of(sp.hw);
                CHECK(v0 == (state == 3 ? -1 : 0));
                const bool start = (state == 0 || state == 1) && count > 0;
                if (start) {
                    REQUIRE(count_of(sp, 0x1A91B0u) == 1u);
                    CHECK(static_cast<u32>(log_of(sp, 0x1A91B0u)[0].args[1]) == kWork + epl::kDelayPos);
                    CHECK(r32(m, kWork + epl::kDelayCount) == count - 1);
                    CHECK(r32(m, kWork + 0) == 2u);
                    CHECK(r32(m, kWork + 8) == 0u);
                    for (u32 i = 1; i < 8; ++i) {
                        CHECK(r32(m, kWork + epl::kDelayId + 4 * (i - 1)) == (i & 1));
                        CHECK(rf32(m, kWork + epl::kDelayPos + 12 * (i - 1)) == 100.0f + static_cast<float>(i));
                        CHECK(r32(m, kWork + epl::kDelayArg4 + 4 * (i - 1)) == i);
                    }
                } else {
                    CHECK(count_of(sp, 0x1A91B0u) == 0u);
                    if (state == 0) CHECK(r32(m, kWork + 0) == 1u);
                    if (state == 2) {
                        CHECK(r32(m, kWork + 0) == (counter >= 20 ? 1u : 2u));
                        CHECK(r32(m, kWork + 8) == (counter >= 20 ? counter : counter + 1));
                    }
                }
            }
        }
    }
    MESSAGE("epl delay: " << n << " pairs");
}

// --- MT_Scene's helpers on the dorm snapshot --------------------------------------------------------------------
// The flag setters change one word of one scene object: the flags word, by exactly the bit (0x40000000 for kinds
// 1..3, 0x10000 for sub_1A0E50), set for on == 1 and cleared otherwise. The light set-ups leave the two light frames
// orthonormal (turned, never scaled). The free-index search answers an index below 1024.
TEST_CASE("game(field8 field): the scene object flags, the light set-ups and the free object index (dorm snapshot)") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    u32 seed = 1;
    int changed = 0, pairs = 0;
    for (const char* fn : {"sub_1A0590", "sub_1A0E50"}) {
        const u32 bit = std::string(fn) == "sub_1A0590" ? 0x40000000u : 0x10000u;
        for (u32 kind = 0; kind < 5; ++kind) {
            for (u32 index = 0; index < 24; ++index) {
                for (const u32 on : {1u, 0u}) {
                    const u32 id = (kind << 10) | index;
                    run_f8(m, base, kCases, fn, {id, on, 0, 0}, seed++, {});
                    ++pairs;
                    std::vector<u32> diffs;
                    for (u32 va = 0; va < EEMemory::kMainRamSize && diffs.size() < 3; va += 4)
                        if (std::memcmp(m.at(va), base.data() + va, 4) != 0) diffs.push_back(va);
                    // the stack page of the harness is the only other memory a run writes
                    std::erase_if(diffs, [](u32 va) { return va >= 0x01F00000u; });
                    if (diffs.empty()) continue;
                    ++changed;
                    REQUIRE(diffs.size() == 1u);
                    u32 before;
                    std::memcpy(&before, base.data() + diffs[0], 4);
                    const u32 after = r32(m, diffs[0]);
                    CHECK((before ^ after) == bit);
                    CHECK(((after & bit) != 0) == (on == 1));
                }
            }
        }
    }
    MESSAGE("scene flags: " << pairs << " pairs, " << changed << " changed one object's flags");
    // the light set-ups on the snapshot's scene records (pairs: the RwMatrixRotate they call is hand-written and runs)
    for (const char* fn : {"sub_1A0A90", "sub_1A0EE0"}) {
        run_f8(m, base, kCases, fn, {0, 0, 0, 0}, seed++, {});
        ++pairs;
    }
    for (u32 kind = 0; kind < 13; ++kind) {
        SiPair sp = run_f8(m, base, kCases, "sub_1A5C50", {kind, 0, 0, 0}, seed++, {});
        CHECK(static_cast<u64>(v0_of(sp.hw)) < 1024u);
    }
}

// --- the model-load wait task and the circle draw -------------------------------------------------------------
// sub_1A5DE0: state 0 moves on only when the model is ready (sub_316F70 stood in), state 1 destroys it and ends.
// The circle draw: the task "circle draw" (update 0x1A50F0, destroy 0x1A5280), radius 400; its destroy frees every
// block its create made.
TEST_CASE("game(field8 field): the model-load wait task and the circle draw task (dorm snapshot)") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    constexpr u32 kTask = kScratch, kWork = kScratch + 0x100;
    u32 seed = 1;
    for (u32 state = 0; state < 3; ++state) {
        for (const u64 ready : {0ull, 1ull}) {
            SiPair sp = run_f8(m, base, kCases, "sub_1A5DE0", {kTask, 0, 0, 0}, seed++, [&](Machine& mm) {
                w32(mm, kTask + 60, kWork);
                w32(mm, kWork, state);
                w32(mm, kWork + 4, 0x1234);
            }, [ready](StandInWorld& w) { w.si.install_recorder(0x316F70u, "sub_316F70 (model ready)", ready); });
            CHECK(v0_of(sp.hw) == (state == 1 ? -1 : 0));
            if (state == 0) CHECK(r32(m, kWork) == (ready ? 1u : 0u));
            if (state == 0) CHECK((log_of(sp, 0x316F70u).at(0).args[0] & 0xFFFFFFFFu) == 0x1234u);
        }
    }
    write_rw_slots(m);
    clean_world(m);
    Seq s{m};
    const u32 task = static_cast<u32>(s.call(hand_of(kCases, "sub_1A5320"), recomp_of(kCases, "sub_1A5320"), {sx(kParent), 0, 0, 0},
                                             "sub_1A5320 create"));
    if (task != 0u) {
        CHECK(m.str(task + game::kwln::kOffName, 24) == "circle draw");
        CHECK(r32(m, task + game::kwln::kOffUpdate) == 0x1A50F0u);
        CHECK(r32(m, task + game::kwln::kOffDestroy) == 0x1A5280u);
        const u32 work = r32(m, task + 60);
        const u32 rec = r32(m, work + 8);
        CHECK(rf32(m, rec + 4) == 400.0f);
        const std::size_t made = s.live.size();
        CHECK(made >= 2u);
        s.call(hand_of(kCases, "sub_1A5280"), recomp_of(kCases, "sub_1A5280"), {sx(task), 0, 0, 0}, "sub_1A5280 destroy");
        CHECK(s.live.count(work) == 0u);
        CHECK(s.live.count(rec) == 0u);
    }
    MESSAGE("circle draw: " << s.pairs << " pairs, task " << task);
}

// --- the RpUserData searches and the material walkers on the snapshots' model clumps ---------------------------
// For each live model clump: its atomics (the clump's atomic list, each atomic's +60 the clump), their geometries'
// materials (+32 list, +36 count). Rules: sub_1A66F0(clump, name) is 1 exactly when sub_1A64F0(material, name) is 1 for
// a material of one of its atomics; when sub_1A64F0 finds a name, sub_1A6350 answers an entry (non-zero); the alpha-mode
// collector sets the fog / wall words of its record for "per3FogDisable" / "per3TrnsWall" materials; the matte tint with
// a zero scale leaves every material colour of the atomic black.
TEST_CASE("game(field8 field): the user-data searches and material walkers on model clumps") {
    auto mp = std::make_unique<Machine>();
    if (mp->load_elf(elf_path()) != nullptr) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    constexpr u32 kMdlLists = 0x9571F0u;  // gMdlLists[12] (test_models.cpp)
    constexpr u32 kName = kScratch, kRec = kScratch + 0x100, kScale = kScratch + 0x200;
    const char* names[] = {"per3MatAlpha", "per3TrnsWall", "per3FogDisable", "per3modelMatColor"};
    int snaps = 0, clumps = 0, mats = 0, found = 0, pairs = 0;
    u32 seed = 1;
    for (const char* snap : {"dorm_replay_4900", "climb_ref_17000", "b_5800"}) {
        std::vector<u8> base = read_snapshot(snap);
        if (base.size() != EEMemory::kMainRamSize) continue;
        ++snaps;
        std::memcpy(m.mem.main_ram(), base.data(), base.size());
        INFO(snap);
        std::vector<u32> clump_list;
        for (u32 k = 0; k < static_cast<u32>(game::mdl::kMdlListCount); ++k)
            for (u32 md = r32(m, kMdlLists + 4u * k); md != 0 && clump_list.size() < 4; md = r32(m, md + game::mdl::kMdlNext)) {
                const u32 clump = r32(m, md + game::mdl::kMdlClump);
                if (clump != 0) clump_list.push_back(clump);
            }
        for (const u32 clump : clump_list) {
            // the clump's atomics: the link list at +8, each link at atomic + 64 (the atomic's +60 is its clump)
            std::vector<u32> atomics;
            for (u32 link = r32(m, clump + 8); link != clump + 8 && link != 0 && atomics.size() < 64; link = r32(m, link)) {
                const u32 atomic = link - 64;
                if (r32(m, atomic + 60) != clump) break;
                atomics.push_back(atomic);
            }
            if (atomics.empty()) continue;
            ++clumps;
            for (const char* name : names) {
                std::memset(m.at(kName), 0, 64);
                std::memcpy(m.at(kName), name, std::strlen(name));
                bool any = false;
                for (const u32 atomic : atomics) {
                    const u32 geo = r32(m, atomic + 24);
                    if (geo == 0) continue;
                    const u32 list = r32(m, geo + 32), n = std::min<u32>(r32(m, geo + 36), 64u);
                    for (u32 i = 0; i < n; ++i) {
                        const u32 mat = r32(m, list + 4 * i);
                        ++mats;
                        const s64 has = v0_of(run_f8(m, base, kCases, "sub_1A64F0", {mat, kName, 0, 0}, seed++,
                                                     [name](Machine& mm) {
                                                         std::memset(mm.at(kName), 0, 64);
                                                         std::memcpy(mm.at(kName), name, std::strlen(name));
                                                     }).hw);
                        ++pairs;
                        CHECK((has == 0 || has == 1));
                        if (has == 1) {
                            any = true;
                            ++found;
                            const u64 entry = run_f8(m, base, kCases, "sub_1A6350", {mat, kName, 0, 0}, seed++, [&](Machine& mm) {
                                std::memset(mm.at(kName), 0, 64);
                                std::memcpy(mm.at(kName), name, std::strlen(name));
                            }).hw.recomp.base.v0;
                            ++pairs;
                            CHECK(entry != 0u);
                        }
                    }
                }
                const s64 clump_has = v0_of(run_f8(m, base, kCases, "sub_1A66F0", {clump, kName, 0, 0}, seed++, [&](Machine& mm) {
                    std::memset(mm.at(kName), 0, 64);
                    std::memcpy(mm.at(kName), name, std::strlen(name));
                }).hw);
                ++pairs;
                CHECK(clump_has == (any ? 1 : 0));
            }
            // the alpha-mode collector and the zero tint on the first atomic's materials
            const u32 atomic = atomics[0];
            const u32 geo = r32(m, atomic + 24);
            if (geo == 0) continue;
            const u32 list = r32(m, geo + 32), n = std::min<u32>(r32(m, geo + 36), 8u);
            for (u32 i = 0; i < n; ++i) {
                const u32 mat = r32(m, list + 4 * i);
                run_f8(m, base, kCases, "sub_1A7370", {mat, kRec, 0, 0}, seed++, [](Machine& mm) { std::memset(mm.at(kRec), 0, 12); });
                ++pairs;
                const u32 fog = r32(m, kRec + 4), wall = r32(m, kRec + 8);
                const auto has_name = [&](const char* nm) {
                    return v0_of(run_f8(m, base, kCases, "sub_1A64F0", {mat, kName, 0, 0}, seed++, [nm](Machine& mm) {
                        std::memset(mm.at(kName), 0, 64);
                        std::memcpy(mm.at(kName), nm, std::strlen(nm));
                    }).hw) == 1;
                };
                CHECK((fog == 1) == has_name("per3FogDisable"));
                CHECK((wall == 1) == has_name("per3TrnsWall"));
                pairs += 2;
            }
            run_f8(m, base, kCases, "sub_1A7910", {atomic, kScale, 0, 0}, seed++, [](Machine& mm) { std::memset(mm.at(kScale), 0, 16); });
            ++pairs;
            for (u32 i = 0; i < n; ++i) CHECK(r32(m, r32(m, list + 4 * i) + 4) == 0u);
        }
    }
    if (snaps == 0) MESSAGE("SKIP: no replay snapshot under extracted/_ours");
    MESSAGE("user data: " << snaps << " snapshots, " << clumps << " clumps, " << mats << " material searches, " << found
                          << " found, " << pairs << " pairs");
}

#else

TEST_CASE("game(field8 field): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
