// Shared helpers of the sweep2 pair tests (tests/game/test_sweep2_*.cpp): sweep1's runners (the random-world sweep, the
// stand-in pair by case name with every not-emitted callee recorded, the ELF-only machine), the snapshot machines of
// field4_util.h, and the guest structures the groups build (effect instances, battle unit lists, element sets).
#pragma once

#include "sweep1_util.h"

#include "p3fes/game/shops.h"
#include "p3fes/game/sweep2.h"

#include <cstring>
#include <vector>

namespace p3fes::game_test::s2t {

using namespace s1t;

// gBtl ($gp 0x7CE3EC) and its four unit lists (+336 + 8 * list, linked by unit +2612).
inline constexpr u32 kGBtlSlot = 0x7CE3ECu;

// A minimal battle record at `btl` with the units of `lists[i]` chained into list i; every unit is a 2,640-byte block
// cleared first (the fields the class-31 kinds read: +2508 flags, +2548 light block, +2604 status, +2612 next).
inline void make_unit_lists(Machine& m, u32 btl, const std::vector<std::vector<u32>>& lists) {
    std::memset(m.at(btl), 0, 0x200);
    w32(m, kGBtlSlot, btl);
    for (u32 i = 0; i < lists.size() && i < 4; ++i) {
        u32 prev = 0;
        for (u32 u : lists[i]) {
            std::memset(m.at(u), 0, 2640);
            if (prev == 0)
                w32(m, btl + 336 + 8 * i, u);
            else
                w32(m, prev + 2612, u);
            prev = u;
        }
    }
}

// One pair of the named case on the stand-in world (heap, printf / sprintf, the file layer), `world` adding the test's own
// stand-ins, every other callee this build does not emit recorded (v0 = `absent_v0`); `prepare` edits the machine after
// each reset. The recompiled run's memory is left in `m`.
template <std::size_t N>
SiPair run_case_w(Machine& m, const std::vector<u8>& base, const Case (&cases)[N], const char* fn, Args args, u32 seed,
                  const std::function<void(Machine&)>& prepare, const WorldSetup& world = {}, u64 absent_v0 = 0) {
    const Case& c = find_case(cases, fn);
    const HwCheck hw = whole_ram_check();
    std::vector<u32> absent;
    for (int tries = 0;; ++tries) {
        reset(m, base);
        write_rw_slots(m);
        if (prepare) prepare(m);
        try {
            const std::vector<u32> list = absent;
            return run_pair_si(m, c.hand, c.recomp, args, seed, fn, hw, [list, absent_v0, world](StandInWorld& w) {
                install_field_world(w);
                if (world) world(w);
                for (u32 va : list)
                    if (!w.si.has(va)) w.si.install_recorder(va, "absent", absent_v0);
            });
        } catch (const rt_test::FatalEvent& e) {
            const std::size_t k = e.what.find("function at 0x");
            if (k == std::string::npos || tries >= 24) throw;
            absent.push_back(static_cast<u32>(std::stoul(e.what.substr(k + 12, 10), nullptr, 16)));
        }
    }
}

// A snapshot as a machine (nullptr when the ELF or the snapshot is absent).
inline std::unique_ptr<Machine> snap_machine(const char* snapshot, std::vector<u8>& base) { return real_machine(snapshot, base); }

}  // namespace p3fes::game_test::s2t
