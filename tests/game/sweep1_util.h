// Shared helpers of the sweep1 pair tests (tests/game/test_sweep1_*.cpp): the random-world sweep and the stand-in pair
// runners of field6_util.h / field4_util.h (each random draw its own statement), the snapshot / ELF-only machines, a
// pair runner by case name, and the guest-string helpers the groups share.
#pragma once

#include "field6_util.h"

#include "p3fes/game/sweep1.h"

#include <cstring>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace p3fes::game_test::s1t {

using namespace f6t;

// A machine with the ELF loaded and nothing else (nullptr without the ELF); `base` keeps its RAM for resets.
inline std::unique_ptr<Machine> elf_machine(std::vector<u8>& base) {
    auto m = std::make_unique<Machine>();
    if (m->load_elf(elf_path()) != nullptr) return nullptr;
    base.assign(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
    return m;
}

// One pair of the named case on the stand-in world (heap, printf / sprintf, the file layer, FileExists), every callee
// this build does not emit stood in by a recorder returning `absent_v0`; `extra` edits the world after each reset and
// `regs` sets $t0..$t3 (arguments 5..8). `stood`: recorders (returning `absent_v0`) from the first run on, for callees
// a later slice replaced that a test's checks still expect recorded as they were while absent. The recompiled run's
// memory is left in `m`.
template <std::size_t N>
SiPair run_case(Machine& m, const std::vector<u8>& base, const Case (&cases)[N], const char* fn, Args args, u32 seed,
                const std::function<void(Machine&)>& extra = {}, u64 absent_v0 = 0,
                const std::map<unsigned, u64>& regs = {}, const std::vector<u32>& stood = {}) {
    std::vector<u32> absent = stood;
    const Case& c = find_case(cases, fn);
    HwCheck hw = whole_ram_check();
    hw.gpr_in = regs;
    return run_pair_si_absent(m, base, c.hand, c.recomp, args, seed, fn, hw,
                              [&](Machine& mm) {
                                  write_rw_slots(mm);
                                  if (extra) extra(mm);
                              },
                              absent, absent_v0);
}

// A guest C string (at most `max` bytes).
inline std::string gstr(Machine& m, u32 va, u32 max = 256) {
    std::string s;
    for (u32 i = 0; i < max; ++i) {
        const char ch = static_cast<char>(r8(m, va + i));
        if (ch == 0) break;
        s.push_back(ch);
    }
    return s;
}
inline void wstr(Machine& m, u32 va, const std::string& s) {
    std::memcpy(m.at(va), s.c_str(), s.size() + 1);
}

// The stand-in call log of the recompiled run, filtered by callee.
inline std::vector<StandInCall> calls(const SiPair& sp, u32 va) {
    std::vector<StandInCall> out;
    for (const StandInCall& c : sp.recomp->si.log)
        if (c.va == va) out.push_back(c);
    return out;
}

}  // namespace p3fes::game_test::s1t
