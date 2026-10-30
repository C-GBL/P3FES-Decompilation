// Shared helpers of the field8 pair tests (tests/game/test_field8_sys.cpp, test_field8_field.cpp): a stand-in pair on
// the field world (heap, printf / sprintf, the file layer, FileExists) with the test's own stand-ins on top and every
// other callee this build does not emit stood in by a recorder (run_pair_si_absent's retry), plus a "stop" stand-in
// for bodies that never return (the worker thread): it ends the run by throwing F8Stop, which the wrapped body catches,
// so both bodies of a pair end at the same call with everything up to it compared.
#pragma once

#include "sweep1_util.h"

#include "p3fes/game/field8.h"

#include <functional>
#include <map>
#include <string>
#include <vector>

namespace p3fes::game_test::f8t {

using namespace s1t;

// Thrown by a stand-in to end a run at that call (see the file comment).
struct F8Stop {};

// One pair of `hand` / `recomp` from `base` (reset, then `prepare`), the field world plus `extra`; a missing callee is
// stood in by a recorder returning `absent_v0` and the pair re-run (at most 32 times). `regs`: $t0.. arguments.
inline SiPair run_f8(Machine& m, const std::vector<u8>& base, Fn hand, Fn recomp, const Args& args, u32 seed,
                     const char* what, const std::function<void(Machine&)>& prepare,
                     const std::function<void(StandInWorld&)>& extra = {}, u64 absent_v0 = 0,
                     const std::map<unsigned, u64>& regs = {}) {
    std::vector<u32> absent;
    HwCheck hw = whole_ram_check();
    hw.gpr_in = regs;
    for (int tries = 0;; ++tries) {
        reset(m, base);
        write_rw_slots(m);
        if (prepare) prepare(m);
        try {
            const std::vector<u32> list = absent;
            return run_pair_si(m, hand, recomp, args, seed, what, hw, [&, list](StandInWorld& w) {
                install_field_world(w);
                for (u32 va : list) w.si.install_recorder(va, "absent", absent_v0);
                if (extra) extra(w);
            });
        } catch (const rt_test::FatalEvent& e) {
            const std::size_t k = e.what.find("function at 0x");
            if (k == std::string::npos || tries >= 32) throw;
            absent.push_back(static_cast<u32>(std::stoul(e.what.substr(k + 12, 10), nullptr, 16)));
        }
    }
}
template <std::size_t N>
SiPair run_f8(Machine& m, const std::vector<u8>& base, const Case (&cases)[N], const char* fn, const Args& args, u32 seed,
              const std::function<void(Machine&)>& prepare, const std::function<void(StandInWorld&)>& extra = {},
              u64 absent_v0 = 0, const std::map<unsigned, u64>& regs = {}) {
    const Case& c = find_case(cases, fn);
    return run_f8(m, base, c.hand, c.recomp, args, seed, fn, prepare, extra, absent_v0, regs);
}

// The recompiled run's calls of `va` (the hand run's are equal: run_pair_si compares the two logs).
inline std::vector<StandInCall> log_of(const SiPair& sp, u32 va) { return calls(sp, va); }
inline std::size_t count_of(const SiPair& sp, u32 va) { return sp.recomp->si.calls_to(va); }

inline s64 s64_at(Machine& m, u32 va) {
    s64 v;
    std::memcpy(&v, m.at(va), 8);
    return v;
}
inline void w64(Machine& m, u32 va, s64 v) { std::memcpy(m.at(va), &v, 8); }
inline std::string guest_str(EEContext& ctx, u64 va) {
    std::string s;
    for (u32 i = 0; i < 512; ++i) {
        const char ch = static_cast<char>(ctx.memory->read<u8>(static_cast<u32>(va) + i));
        if (ch == 0) break;
        s.push_back(ch);
    }
    return s;
}

}  // namespace p3fes::game_test::f8t
