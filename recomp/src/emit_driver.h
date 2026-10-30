// Emission driver: selects functions, groups them into translation units, and writes the
// output directory (recomp/generated/, gitignored):
//   gen_prelude.h      includes p3fes_recomp_rt.h + functions.h, silences the unused-label warning
//   functions.h        declarations of every function in the program (plus entry forms); independent of the
//                      selection and of --replace, so changing game/replaced.txt recompiles only the units
//                      that hold a function whose replacement status changed
//   replaced.h         the __recomp declarations of the --replace set (included by no generated unit)
//   fn_NNNN_<lo>_<hi>.cpp   ~group_size functions each, ascending by address
//   dispatch.cpp       sorted {va, fn} table over every function start and mid-body entry of the
//                      program (independent of the selection) and p3fes::rt::lookup_func
//   missing_stubs.cpp  definitions for declared-but-not-emitted functions (empty in a full run)
//   manifest.json      selection, counts, mid-body entries, every IDA data word (reached or not),
//                      unsupported words, problems
#pragma once

#include "emit_analyze.h"
#include "emit_cgen.h"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace p3fes::recomp {

struct EmitOptions {
    std::string out_dir;
    std::vector<std::uint32_t> only;   // function starts to emit; empty = all (subject to band)
    bool has_band = false;
    std::uint32_t band_lo = 0, band_hi = 0;  // [lo, hi) on function start
    std::size_t group_size = 200;
    // --stable-units: unit k holds the selected functions among the program's functions [k*group_size,
    // (k+1)*group_size) (by position in functions.json, not in the selection) and is named after that band
    // (fn_<k>_<band lo>_<band hi>.cpp), so a subset's units keep their names and text when the selection grows
    // or shrinks elsewhere (tests/rt/emit_units.cmake). A full run writes the same units either way.
    bool stable_units = false;
    bool annotate = false;
    bool keep_going = false;           // write output even when problems were found
    bool cycles = true;                // ADR-0013: `ctx.cycles += N;` per basic block (--no-cycles)
    bool check_events = true;          // ADR-0013: rt::check_events at entries / back-edges (--no-check-events)
    // Reference mode (runtime/STATE.md): calls / dispatch rows of replaced functions through the __sel selectors.
    // --no-selectors: plain calls (the hand-written bodies only; --reference-mode then changes nothing) -- the
    // baseline for measuring the selectors' cost.
    bool selectors = true;
    std::string elf_sha256;            // provenance for the manifest
    // Phase 5 (GOAL.md): functions whose definition comes from game/ (hand-decompiled). The emitter
    // still analyses and emits each one, but under the symbol fn_<name>_<addr>__recomp, keeps the
    // declaration and the dispatch row on the plain symbol (which game/ defines), and refuses a
    // function whose IDA name differs from the listed one (a stale list). A function with mid-body
    // entries lists them on its row (`@0x<pc>` per entry, exactly the program's set, else the run
    // stops): game/ then defines fn_<name>_<addr>_at_<pc8> for each one as well (game/forwarders.cmake
    // reads the same tokens), and the __recomp emission keeps its entry form and wrappers.
    struct Replace { std::uint32_t start; std::string name; std::vector<std::uint32_t> entries; };
    std::vector<Replace> replace;
};

struct FunctionProblem {
    const Function* fn;
    Problem problem;
};

struct EmitReport {
    std::size_t functions_total = 0;
    std::size_t functions_selected = 0;
    std::size_t functions_emitted = 0;
    std::size_t functions_with_entries = 0;  // among all functions in the program
    std::size_t entry_points = 0;            // mid-body entries over the whole program
    std::size_t returning_roots = 0;         // starts + entries proven to return (whole program)
    std::size_t noreturn_functions = 0;      // emitted functions with no path to a return
    std::size_t files = 0;
    FunctionStats stats;                     // summed over emitted functions
    GenStats gen;
    std::vector<FunctionProblem> problems;   // over selected functions
    std::vector<std::pair<std::uint32_t, std::uint32_t>> unowned;  // (from pc, target) from the entry pre-pass
    std::size_t problem_functions = 0;
    std::size_t replaced = 0;                // functions emitted under the __recomp symbol (opt.replace)
};

// Runs the entry pre-pass on `prog`, analyses and generates the selected functions, writes the
// output directory. Returns false with `error` on I/O failure, or when problems were found and
// !keep_going (nothing is written in that case). The report is filled either way.
bool emit_program(Program& prog, const EmitOptions& opt, EmitReport& report, std::string& error);

}  // namespace p3fes::recomp
