// The emitter's view of the whole program: instruction words, IDA's function scope, the jump
// tables, and the two derived facts the per-function generator cannot compute alone:
// which function owns an arbitrary address (chunk ownership) and which addresses inside a
// function are entered from outside (mid-body entry points; recomp/README.md).
//
// Nothing here reads IDA mnemonics or item sizes (ADR-0011 section 2): words come from a
// WordSource (the verified ELF, or an in-memory vector in tests), scope from FunctionList.
#pragma once

#include "function_list.h"
#include "r5900_decode.h"

#include <cstdint>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace p3fes::recomp {

class ElfImage;

// Where instruction words come from.
struct WordSource {
    virtual ~WordSource() = default;
    virtual std::optional<std::uint32_t> word_at(std::uint32_t va) const noexcept = 0;
};

struct ElfWordSource final : WordSource {
    explicit ElfWordSource(const ElfImage& e) noexcept : elf(e) {}
    std::optional<std::uint32_t> word_at(std::uint32_t va) const noexcept override;
    const ElfImage& elf;
};

// Contiguous words starting at `base` (tests, synthetic sequences).
struct VectorWordSource final : WordSource {
    VectorWordSource(std::uint32_t b, std::vector<std::uint32_t> w) : base(b), words(std::move(w)) {}
    std::optional<std::uint32_t> word_at(std::uint32_t va) const noexcept override;
    std::uint32_t base;
    std::vector<std::uint32_t> words;
};

// One IDA switch (symbols/jumptables.json "resolved[]"): a `jr` whose register holds a target
// read from a 32-bit absolute table. The generated code switches on the register value.
struct SwitchSite {
    std::uint32_t jr_ea = 0;
    std::uint32_t func_ea = 0;
    std::uint32_t table_ea = 0;
    std::uint32_t default_ea = 0;
    std::uint8_t reg = 0;                  // GPR index the jr reads
    std::vector<std::uint32_t> targets;    // distinct, sorted
};

struct SwitchTables {
    std::unordered_map<std::uint32_t, SwitchSite> by_jr;   // resolved[] keyed by jr_ea
    std::unordered_set<std::uint32_t> unresolved_jr;      // unresolved[] jr_ea (tail calls through lookup)
    std::size_t total_cases = 0;

    // Parse symbols/jumptables.json. Returns nullptr or a static error message.
    const char* load_json(const std::string& text);
};

// GPR numbers for register names in the exporter ("$v0" -> 2 ...); 0xFF if unknown.
std::uint8_t gpr_index_from_name(const std::string& name) noexcept;

class Program {
public:
    Program(const FunctionList& fl, const WordSource& words, const SwitchTables& switches);

    const FunctionList& functions() const noexcept { return fl_; }
    const WordSource& words() const noexcept { return words_; }
    const SwitchTables& switches() const noexcept { return switches_; }

    // The function starting exactly at `va`, or nullptr.
    const Function* function_at(std::uint32_t va) const noexcept { return fl_.find(va); }

    // The function whose chunk contains `va` (lowest start wins when chunks are shared), or nullptr.
    const Function* owner_of(std::uint32_t va) const noexcept;

    // Does `va` lie inside one of `f`'s chunks?
    static bool contains(const Function& f, std::uint32_t va) noexcept;

    // Can a call that enters at `root` (a function start or a mid-body entry) return to its
    // caller? False until the fixpoint proves a path to a `return;`: the least fixpoint, so
    // endless loops and calls chains that end in one are noreturn.
    bool returns_from(std::uint32_t root) const noexcept { return returns_.count(root) != 0; }
    std::size_t returning_roots() const noexcept { return returns_.size(); }

    // Mid-body entry points: addresses inside `f` (other than its start) that live code calls,
    // jumps to or falls through into from outside the local control flow (another function, or
    // a jal into `f`'s own body). Filled by compute_entries_and_returns().
    const std::set<std::uint32_t>& entries_of(const Function& f) const noexcept;
    bool has_entries(const Function& f) const noexcept { return !entries_of(f).empty(); }

    // Solve entries and returns together: a fixpoint over live code. A function is re-analysed
    // when it gains an entry (more of its body becomes reachable) or when a callee root is proven
    // to return (the code after that call becomes reachable). Both sets only grow. `unowned`
    // receives (source pc, target) pairs of live edges whose target lies in no function at all.
    void compute_entries_and_returns(std::vector<std::pair<std::uint32_t, std::uint32_t>>* unowned);
    std::size_t entry_count() const noexcept;

private:
    struct OwnedRange {
        std::uint32_t start, end;
        std::uint32_t fn_index;
        std::uint32_t max_end_so_far;  // over ranges[0..i], for the backwards walk
    };
    const FunctionList& fl_;
    const WordSource& words_;
    const SwitchTables& switches_;
    std::vector<OwnedRange> ranges_;
    std::map<std::uint32_t, std::set<std::uint32_t>> entries_;  // by function start
    std::unordered_set<std::uint32_t> returns_;                  // roots proven to return
};

}  // namespace p3fes::recomp
