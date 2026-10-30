// p3fes_handgen: the register-faithful converter (recomp/README.md "p3fes_handgen", docs/PHASE5_AGENT_BRIEF.md
// "Using p3fes_handgen").
//
// For one function it writes the C++ body a Phase 5 slice starts from: the same instructions, frame, spills, $ra
// links, cycle charges and check points as the recompiled body (emit_cgen), on the register view of
// game/include/p3fes/game/hg_cpu.h, with the control flow recovered into if / else, loops, switches, early returns and
// break / continue (a labelled goto named after the original block address only where the structure is irreducible
// or a block is shared). The CFG is built from the same FunctionAnalysis the emitter uses and mirrors
// generate_function's block and charge decisions item for item, so the body is faithful by construction; the pair
// tests (tests/game/handgen_pairs.h) are the proof.
#pragma once

#include "emit_analyze.h"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace p3fes::recomp {

class ElfImage;

// symbols/p3fes.sym (functions, named data, named labels) for the readability comments.
struct SymbolTable {
    struct Sym {
        std::uint32_t addr = 0;
        std::uint32_t size = 0;
        char kind = 'D';  // F, D, L
        std::string name;
    };
    std::vector<Sym> syms;  // sorted by address

    // Parse p3fes.sym text. Returns nullptr or a static error message.
    const char* load_sym(const std::string& text);
    // The function starting exactly at `va`, else the data item containing it (or starting at it), else nullptr.
    const Sym* describe(std::uint32_t va) const noexcept;
};

struct HandgenOptions {
    std::string body_suffix;   // appended to the game:: body's name (a scratch substitution next to a typed version)
    std::string shim_suffix;   // appended to the recomp_gen shim's symbol (self-tests pair fn_X__hg with fn_X)
    bool shim = true;          // define the recomp_gen shim
    std::uint32_t gp = 0x007D2CF0u;  // crt0's $gp, for naming gp-relative globals
};

struct HandgenStats {
    std::size_t blocks = 0;
    std::size_t statements = 0;
    std::size_t charges = 0;          // charge / enter statements (one per block that has words)
    std::size_t backedges = 0;        // backedge(ctx) sites
    std::size_t loops = 0;            // for (;;) constructs
    std::size_t ifs = 0;
    std::size_t switches = 0;
    std::size_t gotos = 0;            // goto statements left in the body
    std::size_t labels = 0;           // labels printed (goto targets)
    std::size_t calls = 0;            // jal / jalr sites
    std::size_t hoisted_slots = 0;    // delay slots written before their call / branch (independent of it)
    std::size_t ordered_slots = 0;    // delay slots kept after the link / condition (they depend on it)
};

struct HandgenFunction {
    std::uint32_t start = 0;
    std::string name;          // functions.json name (sanitised: the game:: body's name before body_suffix)
    std::string symbol;        // recomp_gen::fn_<name>_<addr8>
    std::string body;          // the game:: definition(s) (no namespace braces)
    std::string shim;          // the recomp_gen shim definition (no namespace braces); empty without opt.shim
    std::string decl;          // header declaration line(s)
    std::string replaced_row;  // "0x<start> <name>" (+ " @0x<pc>" per mid-body entry)
    // A function with mid-body entries (the recompiled entry form) gets one more game:: function per entry,
    // <name>_at_<pc8>[body_suffix], behind recomp_gen::fn_<name>_<addr8>_at_<pc8>; the regions the entry points
    // share are static bodies in `body`. Each entry is its own pair (skeleton) and its own forwarder.
    struct Entry {
        std::uint32_t pc = 0;
        std::string name;    // <name>_at_<pc8> (the case name); the game:: function is name + body_suffix
        std::string symbol;  // recomp_gen symbol (without the shim suffix)
        std::string shim;    // its shim definition; empty without opt.shim
    };
    std::vector<Entry> entries;
    std::vector<std::string> callees;  // recomp_gen symbols the body calls (declarations the file needs)
    HandgenStats stats;
    std::string error;         // non-empty: not generated (reason)
};

// Generate one function. `elf` and `syms` may be null (no string / symbol comments). The analysis must come from the
// same Program after compute_entries_and_returns (emit_program does it; p3fes_handgen's main too).
HandgenFunction handgen_function(const Program& prog, const FunctionAnalysis& a, const ElfImage* elf,
                                 const SymbolTable* syms, const HandgenOptions& opt);

}  // namespace p3fes::recomp
