#include "handgen_test.h"

#include <cstdio>

namespace p3fes::recomp {

std::string pair_test_skeleton(const std::string& slice, const std::vector<TestEntry>& entries, const std::string& header_include) {
    std::string o;
    o += "// Pair tests for slice " + slice + " (skeleton written by p3fes_handgen; docs/PHASE5_AGENT_BRIEF.md \"Using p3fes_handgen\").\n"
         "// Every body against its recompiled body on random worlds, compared by tests/game/handgen_pairs.h: the whole register\n"
         "// file and cycle count at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS\n"
         "// window and the bus log.\n"
         "// TODO(" + slice + "): give each function meaningful inputs -- its real structures (world layouts, real game data from\n"
         "// the extracted tree, snapshots), the edge cases its branches test, the callees it needs emitted (the _callees list\n"
         "// of tests/game/CMakeLists.txt; without them the runs stop, identically, at the first call) -- and a few documented-rule\n"
         "// checks on the host.\n";
    o += "#include \"handgen_pairs.h\"\n";
    if (!header_include.empty()) o += "\n#include \"" + header_include + "\"\n";
    o += "\n#include <cstdio>\n#include <cstdlib>\n#include <memory>\n#include <random>\n#include <string>\n\n"
         "#ifndef P3FES_GAME_HAVE_GENERATED\n#define P3FES_GAME_HAVE_GENERATED 0\n#endif\n\n"
         "#if P3FES_GAME_HAVE_GENERATED\n\n"
         "using namespace p3fes;\nusing namespace p3fes::game_test;\n\n"
         "namespace p3fes::recomp_gen {\n";
    for (const TestEntry& e : entries) {
        o += "void " + e.hand + "(EEContext&);  // generated body\n";
        o += "void " + e.recomp + "(EEContext&);  // recompiled\n";
    }
    o += "}  // namespace p3fes::recomp_gen\n\nnamespace {\n\n"
         "struct Case {\n    const char* name;\n    u32 addr;\n    Fn hand;\n    Fn recomp;\n};\n\n"
         "const Case kCases[] = {\n";
    for (const TestEntry& e : entries) {
        char addr[16];
        std::snprintf(addr, sizeof addr, "0x%X", e.start);
        const std::string hand = "&recomp_gen::" + e.hand;
        const std::string rec = "&recomp_gen::" + e.recomp;
        o += "    {\"" + e.name + "\", " + addr + ", " + hand + ", " + rec + "},\n";
    }
    o += "};\n\n"
         "// The world: 64 KiB of free RAM above the harness's arena (TODO: the function's real structures).\n"
         "constexpr u32 kWorld = 0x01810000u;\nconstexpr u32 kWorldSize = 0x10000u;\nconstexpr u32 kSeeds = 64;\n\n"
         "}  // namespace\n\n";
    o += "TEST_CASE(\"game(" + slice + "): every body equals its recompiled body on random worlds\") {\n"
         "    auto m = std::make_unique<Machine>();\n"
         "    if (const char* err = m->load_elf(elf_path())) {\n"
         "        MESSAGE(\"SKIP: \" << err);\n"
         "        return;\n"
         "    }\n"
         "    const char* env = std::getenv(\"P3FES_HG_SEEDS\");  // more (or fewer) pairs per function\n"
         "    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;\n"
         "    const char* only = std::getenv(\"P3FES_HG_ONLY\");     // one function by name (debugging)\n"
         "    const bool trace = std::getenv(\"P3FES_HG_TRACE\") != nullptr;  // name and seed of every pair on stderr\n"
         "    for (const Case& c : kCases) {\n"
         "        if (only && std::string(only) != c.name) continue;\n"
         "        int stops = 0;\n"
         "        for (u32 seed = 1; seed <= seeds; ++seed) {\n"
         "            if (trace) std::fprintf(stderr, \"%s seed %u\\n\", c.name, seed);\n"
         "            std::mt19937 rng{seed * 7919u + c.addr};\n"
         "            hgp::random_world(*m, kWorld, kWorldSize, rng);\n"
         "            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),\n"
         "                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};\n"
         "            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;\n"
         "        }\n"
         "        const std::string summary = std::string(c.name) + \": \" + std::to_string(seeds) + \" pairs, \" + std::to_string(stops) + \" stopped early\";\n"
         "        MESSAGE(summary);\n"
         "    }\n"
         "}\n\n"
         "#else\n\n"
         "TEST_CASE(\"game(" + slice + "): no recompiled code in this build\") { MESSAGE(\"SKIP: built without P3FES_RT_EXEC_ELF\"); }\n\n"
         "#endif\n";
    return o;
}

}  // namespace p3fes::recomp
