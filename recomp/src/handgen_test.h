// p3fes_handgen's pair-test skeleton (tests/game/test_<slice>.cpp on tests/game/handgen_pairs.h).
#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace p3fes::recomp {

struct TestEntry {
    std::uint32_t start = 0;
    std::string name;    // the game:: body's name
    std::string hand;    // recomp_gen symbol of the generated body's shim (fn_<name>_<addr8>[shim suffix])
    std::string recomp;  // recomp_gen symbol of the recompiled body: fn_<name>_<addr8>__recomp once the function is in
                         // game/replaced.txt (the replacement flow), the plain fn_<name>_<addr8> next to a shim suffix
                         // for a function the build does not replace (the self-tests)
};

std::string pair_test_skeleton(const std::string& slice, const std::vector<TestEntry>& entries, const std::string& header_include);

}  // namespace p3fes::recomp
