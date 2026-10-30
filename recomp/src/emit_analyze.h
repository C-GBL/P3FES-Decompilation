// Per-function analysis for the emitter: walk IDA's chunks word by word (skipping data items by
// address), pair every branch/jump with its delay slot, classify where each edge goes, and
// collect the label set. The generator (emit_cgen) consumes the result without re-deciding
// anything.
//
// Edge model (recomp/README.md "Control flow"):
//   Local         target inside this function (any of its chunks)      -> goto L_<target>
//   CallFunc      jal to a function start                               -> fn(ctx);
//   CallEntry     jal to a mid-body address of a function               -> fn_entry(ctx, pc);
//   TailFunc      j / branch / fall-through to a function start        -> fn(ctx); return;
//   TailEntry     j / branch / fall-through into a function body       -> fn_entry(ctx, pc); return;
//   Return        jr $ra                                                -> return;
//   Switch        jr with an IDA switch table                           -> switch (reg) { ... }
//   IndirectCall  jalr                                                  -> lookup_func(reg)(ctx);
//   IndirectTail  jr $rN without a table                                -> lookup_func(reg)(ctx); return;
//   Unreachable   chunk end falls through into no function             -> rt::unreachable(pc);
//   Unowned       a static target that lies in no function (fatal unless --keep-going)
//
// Reachability: items are emitted only when a static path reaches them from the function start or
// one of its mid-body entries (fall-through, local branch/jump/switch edges, a branch into a delay
// slot). A call to a root that cannot return (Program::returns_from, an interprocedural fixpoint)
// ends the path. Unreached words (alignment padding after a return, IDA data words after a
// terminator, code after a call that never returns) produce no C++ at all, which is what keeps
// MSVC's C4702 (unreachable code) quiet without any suppression, also under /O2 inlining: every
// emitted statement is reachable in the C++ control flow as well.
#pragma once

#include "emit_program.h"

#include <cstddef>
#include <cstdint>
#include <map>
#include <set>
#include <vector>

namespace p3fes::recomp {

enum class EdgeKind : std::uint8_t {
    Local, CallFunc, CallEntry, TailFunc, TailEntry, Return, Switch, IndirectCall, IndirectTail,
    Unreachable, Unowned
};

struct Edge {
    EdgeKind kind = EdgeKind::Unowned;
    std::uint32_t target = 0;        // static target / fall-through address (0 for register edges)
    const Function* fn = nullptr;    // callee / owner for CallFunc, CallEntry, TailFunc, TailEntry
    bool returns = true;             // Call* / Tail*: the callee root can return (Program::returns_from)
};

enum class ProblemKind : std::uint8_t {
    InvalidWord,        // decodes to Op::Invalid
    UnbackedWord,       // no file bytes at this address
    BranchInSlot,       // a branch/jump sits in another's delay slot
    SlotIsData,         // the delay slot is an IDA data item
    SlotUnbacked,       // the delay slot has no file bytes
    UnownedTarget,      // branch/jump/call target lies in no function
    UnownedSwitchTarget // jump-table target lies in no function
};

struct Problem {
    ProblemKind kind;
    std::uint32_t pc;
    std::uint32_t target;
};

struct Item {
    enum class Kind : std::uint8_t { Code, Data };
    Kind kind = Kind::Code;
    std::uint32_t pc = 0;
    Insn insn;                       // Code only
    bool reachable = false;          // reached from the start / an entry by the static walk; unreachable items are not emitted

    // Control flow (Code with insn.has_delay_slot, or Eret).
    bool is_cf = false;
    bool has_slot = false;           // false for eret
    Insn slot;                       // the delay-slot instruction (fetched by address, even past the chunk end)
    bool slot_outside_chunk = false; // the slot word lies beyond this chunk's end
    bool slot_is_label = false;      // a reached branch targets the slot word itself (the slot is then also
                                     // emitted under its own label, followed by the item at pc + 8)
    bool unconditional = false;      // j, jr, jal, jalr, eret, beq/beql with rs == rt
    bool terminates = false;         // no fall-through after the slot (j, jr, eret, unconditional branch,
                                     // or a jal to a root that cannot return)
    Edge edge;                       // the taken edge (Local/Tail*/Call*/Return/Switch/Indirect*)
    const SwitchSite* sw = nullptr;  // Switch only
    std::vector<Edge> sw_edges;      // Switch only: one per distinct table target (sorted by target)
};

struct ChunkAnalysis {
    Range range;
    std::vector<Item> items;
    std::uint32_t end_pc = 0;        // address execution reaches after the last item: range.end, or
                                     // last.pc + 8 when the last delay slot lies beyond range.end
    Edge end_edge;                   // classification of end_pc (Local / Tail* / Unreachable)
    bool end_reachable = false;      // a reached path falls off the chunk's end (edge is emitted)
};

struct FunctionStats {
    std::size_t words = 0;             // instruction words decoded (slots included)
    std::size_t data_words = 0;
    std::size_t dead_words = 0;        // code words no static path reaches (not emitted)
    std::size_t dead_data_words = 0;   // data words no static path reaches (comment only)
    std::size_t reached_data_words = 0;// data words a static path falls into (rt::unreachable)
    std::size_t branches = 0;
    std::size_t likely_branches = 0;
    std::size_t calls = 0;             // jal to a function start
    std::size_t mid_body_calls = 0;    // jal into a body (CallEntry)
    std::size_t tail_calls = 0;        // static TailFunc/TailEntry (j, branch, fall-through)
    std::size_t indirect_calls = 0;    // jalr
    std::size_t indirect_tails = 0;    // jr $rN without a table
    std::size_t returns = 0;           // jr $ra
    std::size_t switches = 0;
    std::size_t switch_targets = 0;
    std::size_t syscalls = 0;
    std::size_t breaks = 0;
    std::size_t erets = 0;
    std::size_t slots_outside_chunk = 0;
    std::size_t slot_labels = 0;       // delay slots that are branch targets
    std::size_t unreachable_ends = 0;  // chunk ends falling into no function
    std::size_t noreturn_calls = 0;    // jal to a root that cannot return (path ends after the call)
    std::size_t noreturn_tail_calls = 0; // tail calls to such a root (emitted without `return;`)
};

struct FunctionAnalysis {
    const Function* fn = nullptr;
    bool entry_form = false;           // emitted as fn_entry(ctx, entry_pc) + wrappers
    std::vector<ChunkAnalysis> chunks;
    std::set<std::uint32_t> labels;    // every address that gets an L_ label
    std::set<std::uint32_t> entries;   // mid-body entry points (subset of labels)
    bool returns = false;              // some reached path leaves the function
    std::map<std::uint32_t, bool> root_returns;  // per root (start, each entry): a path from it returns
    std::vector<Problem> problems;
    FunctionStats stats;
};

// Classify a static target seen from `self`. `is_call` selects jal semantics (function starts
// first) over jump semantics (local labels first).
Edge classify_static_target(const Program& prog, const Function& self, std::uint32_t target, bool is_call) noexcept;

// Analyse one function with the entries currently known to `prog`. Never fails; problems are
// reported in the result (every word is checked, reached or not: fail closed).
FunctionAnalysis analyze_function(const Program& prog, const Function& fn);

const char* problem_name(ProblemKind k) noexcept;

}  // namespace p3fes::recomp
