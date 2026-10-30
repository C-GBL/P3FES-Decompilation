// Pair tests of slice field4, the field event task (game/src/field/field4_event.cpp): every body against its recompiled
// body, on random worlds (the p3fes_handgen sweep) and one frame on the snapshots' live tasks (climb_ref_17000 exploring
// with four pad inputs, shop_ref_4100's door state, b_5800's battle state) on the stand-in world, the callees this
// build does not emit stood in by recorders; the documented next states are checked.
#include "handgen_pairs.h"
#include "field4_util.h"

#include "p3fes/game/field4.h"

#include <cstdio>
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
void fn_K_FldEvent_UpdateFldEventTask_001c8620(EEContext&);  // generated body
void fn_K_FldEvent_UpdateFldEventTask_001c8620__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"K_FldEvent_UpdateFldEventTask", 0x1C8620, &recomp_gen::fn_K_FldEvent_UpdateFldEventTask_001c8620, &recomp_gen::fn_K_FldEvent_UpdateFldEventTask_001c8620__recomp},
};

// The generic sweep: 64 KiB of free RAM above the harness's arena (the real structures: the snapshot cases below).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(field4 event): every body equals its recompiled body on random worlds") {
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

// --- field4 tests ---

namespace {
using namespace f4t;
namespace fld = game::f4::fld;
namespace evt = game::f4::evt;
namespace root = game::f4::root;
namespace exitrec = game::f4::exitrec;
constexpr u32 kPadFlags = 0x7E094Eu;  // gPadFlags (the pressed edges)
// One frame on the stand-ins (heap, printf, the file layer), every callee this build did not emit stood in by a
// recorder returning 0 (no interactable unit, no hit, ...); `prepare` re-applies the test's edits after each retry.
std::vector<u32> g_absent;
HwPair frame(Machine& m, const std::vector<u8>& base, u32 task, u32 seed, const std::function<void(Machine&)>& prepare) {
    const Case& c = kCases[0];
    SiPair sp = run_pair_si_absent(m, base, c.hand, c.recomp, {task, 0, 0, 0}, seed, c.name, whole_ram_check(), prepare, g_absent);
    return std::move(sp.hw);
}
}  // namespace

// The field event task on the snapshots' live tasks, one frame each: exploring in Tartarus (climb_ref_17000, state 1)
// with no button, confirm (0x40), the camp menu (0x10) and the header-script button (0x80) -- the documented next
// states of state 1 (26_field.md 5.1); the door state of shop_ref_4100 (state 3): the root takes the exit record's
// next field (state 17, +76 / +78 / +80 = exit +18 / +20 / +22) and the task waits in 32; the battle state of b_5800
// (state 15, the battle task alive): it keeps waiting. Hand-written and recompiled bodies compared over all RAM.
TEST_CASE("game(field4 event): one frame of the field event task on the replay snapshots") {
    int frames = 0;
    {
        std::vector<u8> base;
        auto mp = real_machine("climb_ref_17000", base);
        if (mp) {
            Machine& m = *mp;
            const u32 task = r32(m, kSField + fld::kEventTask);
            REQUIRE(task != 0);
            const u32 work = r32(m, task + game::f4::kTaskWork);
            CHECK(r32(m, work + evt::kState) == 1);
            for (u16 pad : {u16(0), u16(0x40), u16(0x10), u16(0x80)}) {
                HwPair r = frame(m, base, task, 1 + pad, [pad](Machine& mm) {
                    write_rw_slots(mm);
                    w16(mm, kPadFlags, pad);
                });
                ++frames;
                const u32 next = r32(m, work + evt::kState);
                CHECK(v0_of(r) == 0);
                if (pad == 0) CHECK((next == 1 || next == 4));          // exploring, or a shadow touched
                if (pad == 0x10) CHECK((next == 23 || next == 1 || next == 4));  // the camp menu unless flag 369
                if (pad == 0x40) CHECK((next == 1 || next == 2 || next == 3 || next == 4 || next == 8 || next == 21 || next == 22));
                MESSAGE("climb pad " << pad << ": state 1 -> " << next);
            }
        }
    }
    {
        std::vector<u8> base;
        auto mp = real_machine("shop_ref_4100", base);
        if (mp) {
            Machine& m = *mp;
            const u32 task = r32(m, kSField + fld::kEventTask);
            const u32 work = r32(m, task + game::f4::kTaskWork);
            if (r32(m, work + evt::kState) == 3) {
                const u32 rec = r32(m, kSField + fld::kExits) + exitrec::kSize * (r16(m, work + evt::kMode) & 0x3FF);
                const u16 major = r16(m, rec + exitrec::kNextMajor), minor = r16(m, rec + exitrec::kNextMinor);
                const u16 entry = r16(m, rec + exitrec::kNextEntry);
                frame(m, base, task, 7, [](Machine& mm) { write_rw_slots(mm); });
                ++frames;
                {
                    const u32 rw = r32(m, r32(m, kSField + fld::kRoot) + game::f4::kTaskWork);
                    CHECK(r32(m, work + evt::kState) == 32);
                    CHECK(r32(m, rw + root::kState) == 17);
                    CHECK(r16(m, rw + root::kNextMajor) == major);
                    CHECK(r16(m, rw + root::kNextMinor) == minor);
                    CHECK(r16(m, rw + root::kNextEntry) == entry);
                    MESSAGE("shop door: next field " << major << "/" << minor << " entry " << entry);
                }
            }
        }
    }
    {
        std::vector<u8> base;
        auto mp = real_machine("b_5800", base);
        if (mp) {
            Machine& m = *mp;
            const u32 task = r32(m, kSField + fld::kEventTask);
            const u32 work = r32(m, task + game::f4::kTaskWork);
            if (r32(m, work + evt::kState) == 15) {
                frame(m, base, task, 9, [](Machine& mm) { write_rw_slots(mm); });
                ++frames;
                CHECK(r32(m, work + evt::kState) == 15);  // the battle task is still alive
            }
        }
    }
    std::string absent;
    for (u32 va : g_absent) absent += " " + std::to_string(va);
    MESSAGE("callees stood in as absent (decimal):" << absent);
    if (frames == 0) MESSAGE("SKIP: no replay snapshot");
}
// --- end of the field4 tests ---

#else

TEST_CASE("game(field4 event): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
