// The test build's forwarders and the pair runners (recomp/README.md "Forwarders", tests/game/stand_ins.h).
//
// In p3fes_game_tests every replaced function's entry point fn_<name>_<addr8> is a generated forwarder that asks the
// installed stand-ins first (game/forwarders.cmake), so a test can stand in a replaced callee. The function under test
// itself must still run for real when a pair calls it, even with a stand-in for its own address installed (a global
// set such as install_standard's FakeCd): the runners (pair_harness.h run / run_pair_hw, handgen_pairs.h run_one)
// open an EntryBypass for the function pointer they call. When that pointer is a forwarder, the first stand-in query
// of the run -- the forwarder's own, at its entry -- is answered "not stood in" (stand_ins.cpp, stand_in_hook); every
// later query, recursive calls of the same function included, is served as usual. The recompiled side
// (fn_X__recomp) is no forwarder, so its run is unaffected.
//
// Header-only: the forwarders register their table here at start-up; an executable without them (the handgen
// self-test, the audit) leaves the table empty and EntryBypass does nothing.
#pragma once

#include <cstddef>
#include <cstdint>
#include <unordered_map>

namespace p3fes {
struct EEContext;
}  // namespace p3fes

namespace p3fes::game_test {

using EntryFn = void (*)(::p3fes::EEContext&);

struct ForwarderRow {
    EntryFn fn;
    std::uint32_t va;
};

// fn -> address of every generated forwarder (empty unless the test build's forwarders are linked in).
inline std::unordered_map<EntryFn, std::uint32_t>& forwarder_table() {
    static std::unordered_map<EntryFn, std::uint32_t> table;
    return table;
}

// Called once by the generated forwarders_test.cpp (a static initialiser).
inline bool register_forwarders(const ForwarderRow* rows, std::size_t n) {
    auto& t = forwarder_table();
    t.reserve(t.size() + n);
    for (std::size_t i = 0; i < n; ++i) t.emplace(rows[i].fn, rows[i].va);
    return true;
}

// The address whose first stand-in query is skipped (0: none). Consumed by the first query of the run.
inline std::uint32_t g_entry_bypass_va = 0;

// Inside a runner, around the call of the function under test.
class EntryBypass {
public:
    explicit EntryBypass(EntryFn fn) {
        const auto& t = forwarder_table();
        const auto it = t.find(fn);
        g_entry_bypass_va = it == t.end() ? 0u : it->second;
    }
    ~EntryBypass() { g_entry_bypass_va = 0; }
    EntryBypass(const EntryBypass&) = delete;
    EntryBypass& operator=(const EntryBypass&) = delete;
};

// stand_in_hook's first step: true when this query is the bypassed entry (the token is consumed either way).
inline bool consume_entry_bypass(std::uint32_t va) {
    const std::uint32_t b = g_entry_bypass_va;
    if (b == 0) return false;
    g_entry_bypass_va = 0;
    return b == va;
}

}  // namespace p3fes::game_test
