// p3fes_types: whole-program struct-layout recovery (docs/ANALYSIS/28_types.md).
//
// Phase 1 (types_analyze.cpp) runs a light forward dataflow over every function the emitter can analyse
// (emit_analyze's chunks, delay slots and reachability): each GPR holds an abstract value -- a pointer into a
// "type variable" plus a constant offset (optionally indexed with a stride), a constant (global addresses, gp
// relative slots), a stack address, or an unknown integer that may be scaled -- and every load/store through a
// pointer is recorded as an access (offset, width, kind, load/store). Values loaded from a pointer field become a
// new type variable "the pointee of that field" (a deref constraint); calls record which values reach $a0..$t3,
// returns which value leaves in $v0, stores which pointer lands in which field.
//
// Phase 2 (types_solve.cpp) unifies type variables with a union-find (field-sensitive Steensgaard: unifying two
// classes unifies the pointees of their common fields) in order of confidence -- joins inside a function, field
// derefs, pointer stores, call arguments, returns, then calls through function-pointer fields whose stored callbacks
// are known -- with a veto: classes whose field layouts conflict (same offset, different width or float vs int), or
// that carry two different seed anchors (header-known structs), stay apart. Parameters that carry no field evidence
// (memcpy, printf, free...) never link their callers.
//
// Output: one JSON document (types.raw.json) the Python side (tools/ours/types/) turns into types.json, the proposed
// headers and the validation report.
#pragma once

#include "emit_program.h"

#include <cstdint>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace p3fes::recomp::types {

enum class TvKind : std::uint8_t {
    Param,   // a = function start, b = argument index 0..7 ($a0..$a3, $t0..$t3)
    Ret,     // a = function start: the value it returns in $v0
    CallRes, // a = call-site pc, b = callee start (or 0)
    Deref,   // a = base tv, b = offset (as u32): the pointee of a pointer field
    GSlot,   // a = absolute address: the pointee of the pointer stored at that global
    GObj,    // a = absolute address: the object at that address
    Stack,   // a = function start, b = entry-$sp offset: a stack object whose address escapes
    Code,    // a = function start: the code object (a callback value)
};

struct Tv {
    TvKind kind;
    std::uint32_t a = 0;
    std::uint32_t b = 0;
    std::uint32_t fn = 0;  // function whose analysis created it (Deref, CallRes, Stack)
};

// Access kinds (bit mask).
enum : std::uint8_t {
    kKSigned = 1,     // lb / lh / lw (sign-extending integer)
    kKUnsigned = 2,   // lbu / lhu / lwu
    kKFloat = 4,      // lwc1 / swc1
    kKVector = 8,     // lqc2 / sqc2 (VU0 vector)
    kKInt128 = 16,    // lq / sq
    kKInt64 = 32,     // ld / sd
    kKStore = 64,     // a store (sb / sh / sw / sd / sq / swc1 / sqc2); loads have it clear
};

struct Access {
    std::uint32_t tv;
    std::int32_t off;
    std::int32_t stride;  // 0: fixed offset; > 0: indexed (element stride), 1 = unknown stride
    std::uint32_t pc;
    std::uint32_t fn;
    std::uint8_t width;
    std::uint8_t kind;
};

struct GAccess {  // through an absolute address (lui/addiu, gp-relative)
    std::uint32_t addr;
    std::int32_t stride;
    std::uint32_t pc;
    std::uint32_t fn;
    std::uint8_t width;
    std::uint8_t kind;
};

enum class CKind : std::uint8_t {
    Join,     // a, b: the same register at a merge point
    Deref,    // a = deref tv (its Tv says base/offset)
    Store,    // a = stored tv, b = deref-like slot tv (a Deref created for the store)
    Arg,      // a = value tv, b = callee param tv; pc = call site
    Result,   // a = call-result tv, b = callee Ret tv
    Return,   // a = returned tv, b = Ret tv of this function
    ICall,    // a = called tv (the loaded function pointer), args in icall_args[c]; pc
    Embed,    // a = pointer tv (+ offset c) passed where b (callee param) is expected: a sub-object
};

struct Constraint {
    CKind kind;
    std::uint32_t a = 0;
    std::uint32_t b = 0;
    std::int32_t c = 0;
    std::uint32_t pc = 0;
    std::uint32_t fn = 0;
};

struct Anchor {  // a header-known struct pinned on a type variable (seed)
    std::string name;
    std::string how;  // "param", "ret", "gslot", "gobj"
    std::uint32_t addr = 0;
    std::uint32_t index = 0;
};

struct Facts {
    std::vector<Tv> tvs;
    std::vector<Access> accesses;
    std::vector<GAccess> gaccesses;
    std::vector<Constraint> cons;
    std::vector<std::vector<std::uint32_t>> icall_args;  // per ICall: arg tvs (0 = none) for $a0..$t3

    // memo
    std::unordered_map<std::uint64_t, std::uint32_t> param, ret, gslot, gobj, code, stack;

    std::uint32_t new_tv(TvKind k, std::uint32_t a, std::uint32_t b, std::uint32_t fn) {
        tvs.push_back({k, a, b, fn});
        return static_cast<std::uint32_t>(tvs.size() - 1);
    }
    std::uint32_t memo(std::unordered_map<std::uint64_t, std::uint32_t>& m, TvKind k, std::uint32_t a, std::uint32_t b,
                       std::uint32_t fn) {
        const std::uint64_t key = (static_cast<std::uint64_t>(a) << 32) | b;
        auto it = m.find(key);
        if (it != m.end()) return it->second;
        const std::uint32_t t = new_tv(k, a, b, fn);
        m.emplace(key, t);
        return t;
    }
    std::uint32_t param_tv(std::uint32_t f, std::uint32_t i) { return memo(param, TvKind::Param, f, i, f); }
    std::uint32_t ret_tv(std::uint32_t f) { return memo(ret, TvKind::Ret, f, 0, f); }
    std::uint32_t gslot_tv(std::uint32_t a) { return memo(gslot, TvKind::GSlot, a, 0, 0); }
    std::uint32_t gobj_tv(std::uint32_t a) { return memo(gobj, TvKind::GObj, a, 0, 0); }
    std::uint32_t code_tv(std::uint32_t f) { return memo(code, TvKind::Code, f, 0, f); }
    std::uint32_t stack_tv(std::uint32_t f, std::int32_t off) {
        return memo(stack, TvKind::Stack, f, static_cast<std::uint32_t>(off), f);
    }
};

struct AnalyzeStats {
    std::size_t functions = 0;
    std::size_t analysed = 0;
    std::size_t skipped = 0;      // problems in the emitter's analysis (invalid words...)
    std::size_t instructions = 0;
    std::size_t iterations = 0;   // dataflow node visits
};

// Phase 1 over every function of the program (the program's entries/returns must be computed).
void analyze_program(const Program& prog, Facts& facts, AnalyzeStats& st);

struct SolveOptions {
    std::vector<Anchor> anchors;
    std::map<std::string, std::uint32_t> sizes;  // documented record sizes: no merge adds an access at or past it
    int max_conflicts = 4;  // veto above this many conflicting offsets, or above one per ten agreeing offsets
};

struct SolveStats {
    std::size_t unions = 0;
    std::size_t vetoes = 0;
    std::size_t vetoes_anchor = 0;
    std::size_t args_no_evidence = 0;
    std::size_t icall_resolved = 0;
    std::size_t anchors_applied = 0;
};

// Phase 2 + JSON output (types.raw.json). Returns false if the file cannot be written.
bool solve_and_write(const Program& prog, Facts& facts, const SolveOptions& opt, SolveStats& st,
                     const std::string& out_path, const AnalyzeStats& ast, double phase1_seconds);

}  // namespace p3fes::recomp::types
