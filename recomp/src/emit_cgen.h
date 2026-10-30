// C++ generator: turns a FunctionAnalysis into the text of one recompiled function
// (recomp/README.md "Emitted code shape"). Every state-changing instruction becomes one call into
// p3fes::rt (recomp/include/p3fes_recomp_rt.h); control flow becomes labels, gotos, host calls and
// returns. Only items the analysis marked reachable are emitted.
#pragma once

#include "emit_analyze.h"

#include <cstddef>
#include <cstdint>
#include <set>
#include <string>

namespace p3fes::recomp {

struct GenOptions {
    bool annotate = false;      // trailing "// <pc> <mnemonic>" comments on every statement
    // ADR-0013 check points and virtual time (recomp/README.md "Cycle accounting and check points").
    bool cycles = true;         // `ctx.cycles += N;` at the start of every basic block
    bool check_events = true;   // rt::check_events(ctx) once per invocation and before every back-edge
    // Appended to the function's symbol in its definition (Phase 5 replacement: "__recomp"); for the entry form
    // to the _entry body and every wrapper. Declarations are unaffected (emit_driver adds the second ones).
    std::string symbol_suffix;
    // Phase 5 replacements (the --replace starts): calls to them go through fn_<name>_<addr8>__sel, which runs
    // the __recomp body when the runtime's reference mode is on and the hand-written one otherwise
    // (runtime/STATE.md "Reference mode"). nullptr / empty: plain calls.
    const std::set<std::uint32_t>* replaced = nullptr;
};

struct GenStats {
    std::size_t statements = 0;
    std::size_t nops_dropped = 0;         // word 0
    std::size_t zero_writes_dropped = 0;  // pure ALU ops with destination $zero
    std::size_t dangling_labels = 0;      // label targets with no item at that address (trap emitted)
    std::size_t invalid_words = 0;        // Op::Invalid emitted as rt::trap(Unsupported)
    std::size_t cycle_adds = 0;           // `ctx.cycles += N;` statements
    std::size_t cycle_words = 0;          // sum of N over those statements (static, not per path)
    std::size_t entry_checks = 0;         // rt::check_events at function entry (one per function body)
    std::size_t backedge_checks = 0;      // rt::check_events before a backward local edge (sites)
};

// fn_<sanitised IDA name>_<addr8>; the entry-dispatch form appends _entry; per-entry wrappers
// append _at_<pc8>.
std::string function_symbol(const Function& f);
std::string entry_symbol(const Function& f);
std::string at_symbol(const Function& f, std::uint32_t pc);

// Append the C++ definition(s) of one function to `out`.
void generate_function(std::string& out, const Program& prog, const FunctionAnalysis& a, const GenOptions& opt, GenStats& st);

// Append the declaration(s) of one function (as functions.h carries them).
void generate_declaration(std::string& out, const Program& prog, const Function& f);

// Append a statement for one non-control-flow instruction (exposed for tests). Returns false
// when nothing was emitted (nop / $zero write).
bool generate_insn(std::string& out, const Insn& insn, const GenOptions& opt, GenStats& st);

// p3fes::rt name of an Op ("addu", "and_", "add_s", "vadd_bc" for broadcast forms).
std::string rt_name(const Insn& insn);

}  // namespace p3fes::recomp
