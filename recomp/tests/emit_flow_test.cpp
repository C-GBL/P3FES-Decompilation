// Emitter flow tests on synthetic word sequences (recomp/README.md "Tests" (b)).
//
// Each case assembles a few R5900 words by hand, runs the analyzer + generator over an
// in-memory function list, and checks the *structure* of the emitted C++: where the delay slot
// lands relative to the condition, that likely branches skip the slot, that jump tables become
// a switch with the lookup default, that mid-body jal targets produce the entry-dispatch form,
// that data words become rt::unreachable, that only statically reachable words are emitted, that
// jal/jalr write the link register before the slot, and that $zero writes are dropped.
// The structural cases run with the ADR-0013 additions off (legacy_options) so that they read
// like the emitted shape in recomp/README.md; the "cycles:" / "check_events:" cases at the end run
// with the defaults (both on) and pin the cycle counts and check-point placement.
#include "doctest.h"

#include "emit_analyze.h"
#include "emit_cgen.h"
#include "emit_program.h"

#include <algorithm>
#include <cstdint>
#include <set>
#include <string>
#include <vector>

using namespace p3fes::recomp;

namespace {

// Encoders for the handful of instructions the tests use.
constexpr std::uint32_t NOP = 0u;
constexpr std::uint32_t addiu(unsigned rt, unsigned rs, int imm) { return (9u << 26) | (rs << 21) | (rt << 16) | (static_cast<std::uint32_t>(imm) & 0xFFFFu); }
constexpr std::uint32_t addu(unsigned rd, unsigned rs, unsigned rt) { return (rs << 21) | (rt << 16) | (rd << 11) | 0x21u; }
constexpr std::uint32_t lw(unsigned rt, unsigned base, int imm) { return (0x23u << 26) | (base << 21) | (rt << 16) | (static_cast<std::uint32_t>(imm) & 0xFFFFu); }
constexpr std::uint32_t beq(unsigned rs, unsigned rt, int off) { return (4u << 26) | (rs << 21) | (rt << 16) | (static_cast<std::uint32_t>(off) & 0xFFFFu); }
constexpr std::uint32_t bnel(unsigned rs, unsigned rt, int off) { return (0x15u << 26) | (rs << 21) | (rt << 16) | (static_cast<std::uint32_t>(off) & 0xFFFFu); }
constexpr std::uint32_t bne(unsigned rs, unsigned rt, int off) { return (5u << 26) | (rs << 21) | (rt << 16) | (static_cast<std::uint32_t>(off) & 0xFFFFu); }
constexpr std::uint32_t jr(unsigned rs) { return (rs << 21) | 8u; }
constexpr std::uint32_t jalr(unsigned rs) { return (rs << 21) | (31u << 11) | 9u; }
constexpr std::uint32_t jal(std::uint32_t target) { return (3u << 26) | ((target >> 2) & 0x03FFFFFFu); }
constexpr std::uint32_t j(std::uint32_t target) { return (2u << 26) | ((target >> 2) & 0x03FFFFFFu); }
constexpr std::uint32_t JR_RA = jr(31);

// Emitter options without the ADR-0013 statements (cycle adds, check points).
GenOptions legacy_options() {
    GenOptions o;
    o.cycles = false;
    o.check_events = false;
    return o;
}

struct Fixture {
    FunctionList fl;
    SwitchTables sw;
    std::vector<std::uint32_t> words;
    std::uint32_t base;

    Fixture(std::uint32_t b, std::vector<std::uint32_t> w) : words(std::move(w)), base(b) {}

    Function& add(const char* name, std::uint32_t start, std::uint32_t end, std::vector<DataItem> data = {},
                  std::vector<Range> more_chunks = {}) {
        Function f;
        f.start = start;
        f.size = end - start;
        f.name = name;
        f.chunks.push_back({start, end});
        for (const Range& r : more_chunks) {
            f.chunks.push_back(r);
            f.size += r.end - r.start;
        }
        f.data = std::move(data);
        fl.functions.push_back(std::move(f));
        fl.has_chunks = true;
        std::sort(fl.functions.begin(), fl.functions.end(), [](const Function& x, const Function& y) { return x.start < y.start; });
        return *const_cast<Function*>(fl.find(start));
    }

    std::string generate(std::uint32_t start, FunctionAnalysis* out_a = nullptr, GenStats* out_st = nullptr,
                         const GenOptions& opt = legacy_options()) {
        VectorWordSource src(base, words);
        Program prog(fl, src, sw);
        std::vector<std::pair<std::uint32_t, std::uint32_t>> unowned;
        prog.compute_entries_and_returns(&unowned);
        const Function* f = fl.find(start);
        REQUIRE(f != nullptr);
        FunctionAnalysis a = analyze_function(prog, *f);
        std::string text;
        GenStats st;
        generate_function(text, prog, a, opt, st);
        if (out_a) *out_a = a;
        if (out_st) *out_st = st;
        return text;
    }
};

std::size_t count(const std::string& hay, const std::string& needle) {
    std::size_t n = 0;
    for (std::size_t p = hay.find(needle); p != std::string::npos; p = hay.find(needle, p + needle.size())) ++n;
    return n;
}

}  // namespace

TEST_CASE("emit: conditional branch evaluates the condition before the slot and runs the slot once per path") {
    // 0x1000 beq a0, zero, +2 (-> 0x100c); 0x1004 addiu v0, zero, 1 (slot); 0x1008 addiu v0, zero, 2;
    // 0x100c jr ra; 0x1010 nop
    Fixture fx(0x1000, {beq(4, 0, 2), addiu(2, 0, 1), addiu(2, 0, 2), JR_RA, NOP});
    fx.add("A", 0x1000, 0x1014);
    FunctionAnalysis a;
    const std::string t = fx.generate(0x1000, &a);
    INFO(t);
    CHECK(t.find("void fn_A_00001000(p3fes::EEContext& ctx) {") != std::string::npos);
    const std::size_t cond = t.find("if (rt::cmp_eq(ctx, 4, 0)) {");
    const std::size_t slot1 = t.find("rt::addiu(ctx, 2, 0, 1);");
    const std::size_t go = t.find("goto L_0000100c;");
    const std::size_t slot2 = t.find("rt::addiu(ctx, 2, 0, 1);", slot1 + 1);
    const std::size_t next = t.find("rt::addiu(ctx, 2, 0, 2);");
    const std::size_t lab = t.find("L_0000100c:");
    const std::size_t ret = t.find("return;");
    REQUIRE(cond != std::string::npos);
    REQUIRE(slot1 != std::string::npos);
    REQUIRE(slot2 != std::string::npos);
    CHECK(cond < slot1);
    CHECK(slot1 < go);
    CHECK(go < slot2);
    CHECK(slot2 < next);
    CHECK(next < lab);
    CHECK(lab < ret);
    CHECK(count(t, "rt::addiu(ctx, 2, 0, 1);") == 2);  // taken path + fall-through path
    CHECK(a.labels == std::set<std::uint32_t>{0x100c});
    CHECK(a.stats.branches == 1);
    CHECK(a.stats.returns == 1);
}

TEST_CASE("emit: likely branch executes the slot only on the taken path") {
    Fixture fx(0x1000, {bnel(4, 0, 2), addiu(2, 0, 1), addiu(2, 0, 2), JR_RA, NOP});
    fx.add("A", 0x1000, 0x1014);
    FunctionAnalysis a;
    const std::string t = fx.generate(0x1000, &a);
    INFO(t);
    CHECK(count(t, "rt::addiu(ctx, 2, 0, 1);") == 1);
    const std::size_t cond = t.find("if (rt::cmp_ne(ctx, 4, 0)) {");
    const std::size_t slot = t.find("rt::addiu(ctx, 2, 0, 1);");
    const std::size_t go = t.find("goto L_0000100c;");
    const std::size_t close = t.find("}", go);
    REQUIRE(cond != std::string::npos);
    CHECK(cond < slot);
    CHECK(slot < go);
    CHECK(go < close);
    CHECK(close < t.find("rt::addiu(ctx, 2, 0, 2);"));
    CHECK(a.stats.likely_branches == 1);
}

TEST_CASE("emit: jr with an IDA switch table becomes a switch on the register value") {
    // 0x2000 lw v1, 0(v1); 0x2004 jr v1; 0x2008 nop; 0x200c addiu v0,zero,1; 0x2010 jr ra; 0x2014 nop;
    // 0x2018 addiu v0,zero,2; 0x201c jr ra; 0x2020 nop
    Fixture fx(0x2000, {lw(3, 3, 0), jr(3), NOP, addiu(2, 0, 1), JR_RA, NOP, addiu(2, 0, 2), JR_RA, NOP});
    fx.add("S", 0x2000, 0x2024);
    SwitchSite s;
    s.jr_ea = 0x2004;
    s.func_ea = 0x2000;
    s.reg = 3;
    s.targets = {0x200c, 0x2018};
    fx.sw.by_jr[0x2004] = s;
    FunctionAnalysis a;
    const std::string t = fx.generate(0x2000, &a);
    INFO(t);
    CHECK(t.find("const std::uint32_t t = rt::reg32(ctx, 3);") != std::string::npos);
    CHECK(t.find("switch (t) {") != std::string::npos);
    CHECK(t.find("case 0x200cu: goto L_0000200c;") != std::string::npos);
    CHECK(t.find("case 0x2018u: goto L_00002018;") != std::string::npos);
    CHECK(t.find("default: rt::lookup_func(t)(ctx); return;") != std::string::npos);
    CHECK(t.find("L_0000200c:") != std::string::npos);
    CHECK(t.find("L_00002018:") != std::string::npos);
    CHECK(a.stats.switches == 1);
    CHECK(a.stats.switch_targets == 2);
}

TEST_CASE("emit: jr $rN without a table is a tail call through lookup_func; jalr is an indirect call") {
    Fixture fx(0x5000, {lw(2, 4, 0), jr(2), NOP, jalr(2), NOP, JR_RA, NOP});
    fx.add("T", 0x5000, 0x500c);
    fx.add("U", 0x500c, 0x501c);
    FunctionAnalysis a;
    std::string t = fx.generate(0x5000, &a);
    INFO(t);
    CHECK(t.find("const std::uint32_t t = rt::reg32(ctx, 2);") != std::string::npos);
    CHECK(t.find("rt::lookup_func(t)(ctx);\n        return;") != std::string::npos);
    CHECK(a.stats.indirect_tails == 1);
    t = fx.generate(0x500c, &a);
    INFO(t);
    CHECK(t.find("rt::lookup_func(t)(ctx);\n    }") != std::string::npos);
    CHECK(a.stats.indirect_calls == 1);
    CHECK(a.stats.returns == 1);
}

TEST_CASE("emit: jal to a function start is a direct call; jal into a body uses the entry-dispatch form") {
    // A @ 0x3000: jal B; nop; jal B+8; nop; jr ra; nop
    // B @ 0x3100: addiu v0,zero,1; nop; (0x3108) addiu v0,zero,2; jr ra; nop
    std::vector<std::uint32_t> w(0x200 / 4, NOP);
    w[0] = jal(0x3100); w[2] = jal(0x3108); w[4] = JR_RA;
    w[0x100 / 4] = addiu(2, 0, 1); w[0x108 / 4] = addiu(2, 0, 2); w[0x10c / 4] = JR_RA;
    Fixture fx(0x3000, w);
    fx.add("A", 0x3000, 0x3018);
    fx.add("B", 0x3100, 0x3114);
    FunctionAnalysis a;
    const std::string ta = fx.generate(0x3000, &a);
    INFO(ta);
    CHECK(ta.find("fn_B_00003100(ctx);") != std::string::npos);
    CHECK(ta.find("fn_B_00003100_at_00003108(ctx);") != std::string::npos);  // the entry's wrapper, never fn_B_entry
    CHECK(a.stats.calls == 1);
    CHECK(a.stats.mid_body_calls == 1);

    FunctionAnalysis b;
    const std::string tb = fx.generate(0x3100, &b);
    INFO(tb);
    CHECK(b.entry_form);
    CHECK(b.entries == std::set<std::uint32_t>{0x3108});
    CHECK(tb.find("void fn_B_00003100_entry(p3fes::EEContext& ctx, std::uint32_t entry_pc) {") != std::string::npos);
    CHECK(tb.find("switch (entry_pc) {") != std::string::npos);
    CHECK(tb.find("case 0x3100u: goto L_00003100;") != std::string::npos);
    CHECK(tb.find("case 0x3108u: goto L_00003108;") != std::string::npos);
    CHECK(tb.find("default: rt::bad_entry(0x3100u, entry_pc);") != std::string::npos);
    CHECK(tb.find("void fn_B_00003100(p3fes::EEContext& ctx) { fn_B_00003100_entry(ctx, 0x3100u); }") != std::string::npos);
    CHECK(tb.find("void fn_B_00003100_at_00003108(p3fes::EEContext& ctx) { fn_B_00003100_entry(ctx, 0x3108u); }") != std::string::npos);
    const std::size_t l1 = tb.find("L_00003100:");
    const std::size_t l2 = tb.find("L_00003108:");
    REQUIRE(l1 != std::string::npos);
    REQUIRE(l2 != std::string::npos);
    CHECK(l1 < tb.find("rt::addiu(ctx, 2, 0, 1);"));
    CHECK(tb.find("rt::addiu(ctx, 2, 0, 1);") < l2);
    CHECK(l2 < tb.find("rt::addiu(ctx, 2, 0, 2);"));

    // Declarations carry all three forms.
    VectorWordSource src(fx.base, fx.words);
    Program prog(fx.fl, src, fx.sw);
    prog.compute_entries_and_returns(nullptr);
    std::string decl;
    generate_declaration(decl, prog, *fx.fl.find(0x3100));
    CHECK(decl == "void fn_B_00003100(p3fes::EEContext&);\n"
                  "void fn_B_00003100_entry(p3fes::EEContext&, std::uint32_t);\n"
                  "void fn_B_00003100_at_00003108(p3fes::EEContext&);\n");
}

TEST_CASE("emit: a replaced function with a mid-body entry keeps its entry form under __recomp; callers use the _at_ selector") {
    // The same A / B as above, with B replaced (Phase 5 --replace): A's call to B's start goes through fn_B__sel, its
    // call into B's body through fn_B_at_<pc8>__sel (game/ defines the plain fn_B and fn_B_at_<pc8>); B's recompiled
    // body keeps the entry-dispatch form with __recomp on the _entry body and on every wrapper. A j into the entry
    // (C) is the same selector with a return.
    std::vector<std::uint32_t> w(0x200 / 4, NOP);
    w[0] = jal(0x3100); w[2] = jal(0x3108); w[4] = JR_RA;
    w[0x100 / 4] = addiu(2, 0, 1); w[0x108 / 4] = addiu(2, 0, 2); w[0x10c / 4] = JR_RA;
    w[0x120 / 4] = j(0x3108);
    Fixture fx(0x3000, w);
    fx.add("A", 0x3000, 0x3018);
    fx.add("B", 0x3100, 0x3114);
    fx.add("C", 0x3120, 0x3128);
    const std::set<std::uint32_t> replaced{0x3100};
    GenOptions sel = legacy_options();
    sel.replaced = &replaced;
    FunctionAnalysis a;
    const std::string ta = fx.generate(0x3000, &a, nullptr, sel);
    INFO(ta);
    CHECK(ta.find("fn_B_00003100__sel(ctx);") != std::string::npos);
    CHECK(ta.find("fn_B_00003100_at_00003108__sel(ctx);") != std::string::npos);
    CHECK(ta.find("_entry(") == std::string::npos);
    const std::string tc = fx.generate(0x3120, nullptr, nullptr, sel);
    INFO(tc);
    CHECK(tc.find("fn_B_00003100_at_00003108__sel(ctx); return;") != std::string::npos);

    GenOptions rec = legacy_options();
    rec.symbol_suffix = "__recomp";
    FunctionAnalysis b;
    const std::string tb = fx.generate(0x3100, &b, nullptr, rec);
    INFO(tb);
    CHECK(b.entry_form);
    CHECK(tb.find("void fn_B_00003100_entry__recomp(p3fes::EEContext& ctx, std::uint32_t entry_pc) {") != std::string::npos);
    CHECK(tb.find("void fn_B_00003100__recomp(p3fes::EEContext& ctx) { fn_B_00003100_entry__recomp(ctx, 0x3100u); }") != std::string::npos);
    CHECK(tb.find("void fn_B_00003100_at_00003108__recomp(p3fes::EEContext& ctx) { fn_B_00003100_entry__recomp(ctx, 0x3108u); }") !=
          std::string::npos);
    CHECK(tb.find("void fn_B_00003100(") == std::string::npos);  // the plain symbols are game/'s
    CHECK(tb.find("void fn_B_00003100_at_00003108(") == std::string::npos);
}

TEST_CASE("emit: j / fall-through to another function are tail calls; into nowhere is rt::unreachable") {
    // A @ 0x6000: beq zero,zero,+1 (-> 0x6008) ; nop ; (0x6008) j C ; nop        (chunk end 0x6010)
    // B @ 0x6010: addiu v0,zero,1 ; addiu v0,zero,2                               (falls into C at 0x6018)
    // C @ 0x6018: addiu v0,zero,3                                                 (falls into nothing at 0x601c)
    // D @ 0x6020: j E ; nop        E @ 0x6028: jr ra ; nop
    Fixture fx(0x6000, {beq(0, 0, 1), NOP, j(0x6018), NOP, addiu(2, 0, 1), addiu(2, 0, 2), addiu(2, 0, 3), NOP,
                        j(0x6028), NOP, JR_RA, NOP});
    fx.add("A", 0x6000, 0x6010);
    fx.add("B", 0x6010, 0x6018);
    fx.add("C", 0x6018, 0x601c);
    fx.add("D", 0x6020, 0x6028);
    fx.add("E", 0x6028, 0x6030);
    FunctionAnalysis a;
    std::string t = fx.generate(0x6000, &a);
    INFO(t);
    CHECK(t.find("goto L_00006008;") != std::string::npos);
    // C cannot return (it ends in rt::unreachable), so the tail call carries no `return;`.
    CHECK(t.find("fn_C_00006018(ctx);\n") != std::string::npos);
    CHECK(t.find("return;") == std::string::npos);
    CHECK_FALSE(a.returns);
    CHECK_FALSE(t.find("if (") != std::string::npos);  // beq zero,zero is unconditional
    CHECK(a.stats.tail_calls == 1);
    CHECK(a.stats.noreturn_tail_calls == 1);
    t = fx.generate(0x6010, &a);
    INFO(t);
    CHECK(t.find("rt::addiu(ctx, 2, 0, 2);\n    fn_C_00006018(ctx);\n}") != std::string::npos);
    t = fx.generate(0x6018, &a);
    INFO(t);
    CHECK(t.find("rt::unreachable(0x601cu);") != std::string::npos);
    CHECK(a.stats.unreachable_ends == 1);
    t = fx.generate(0x6020, &a);
    INFO(t);
    CHECK(t.find("fn_E_00006028(ctx); return;") != std::string::npos);  // E returns
    CHECK(a.returns);
}

TEST_CASE("emit: nothing is emitted after a call that cannot return; the property propagates through callers") {
    // L @ 0x7000 (endless loop): addiu v0,v0,1 ; beq zero,zero,-2 (-> 0x7000) ; nop
    // M @ 0x7100: jal L ; nop ; addiu v0,zero,9 ; jr ra ; nop      (the code after the jal is dead)
    // N @ 0x7200: jal M ; nop ; jr ra ; nop                         (M cannot return either)
    // P @ 0x7300: beq a0,zero,+3 (-> 0x7310) ; nop ; jal L ; nop ; jr ra ; nop  (one path returns)
    std::vector<std::uint32_t> w(0x400 / 4, NOP);
    w[0] = addiu(2, 2, 1); w[1] = beq(0, 0, -2);
    w[0x100 / 4] = jal(0x7000); w[0x108 / 4] = addiu(2, 0, 9); w[0x10c / 4] = JR_RA;
    w[0x200 / 4] = jal(0x7100); w[0x208 / 4] = JR_RA;
    w[0x300 / 4] = beq(4, 0, 3); w[0x308 / 4] = jal(0x7000); w[0x310 / 4] = JR_RA;
    Fixture fx(0x7000, w);
    fx.add("L", 0x7000, 0x700c);
    fx.add("M", 0x7100, 0x7114);
    fx.add("N", 0x7200, 0x7210);
    fx.add("P", 0x7300, 0x7318);
    FunctionAnalysis a;
    std::string t = fx.generate(0x7100, &a);
    INFO(t);
    CHECK(t.find("fn_L_00007000(ctx);\n") != std::string::npos);
    CHECK(t.find("rt::addiu") == std::string::npos);
    CHECK(t.find("return;") == std::string::npos);
    CHECK_FALSE(a.returns);
    CHECK(a.stats.noreturn_calls == 1);
    t = fx.generate(0x7200, &a);
    INFO(t);
    CHECK(t.find("fn_M_00007100(ctx);\n") != std::string::npos);
    CHECK(t.find("return;") == std::string::npos);
    CHECK_FALSE(a.returns);
    t = fx.generate(0x7300, &a);
    INFO(t);
    CHECK(a.returns);
    CHECK(count(t, "return;") == 1);
    CHECK(t.find("fn_L_00007000(ctx);\nL_00007310:") != std::string::npos);
}

TEST_CASE("emit: data words inside a chunk are never decoded; reachable ones trap, dead ones are skipped") {
    {
        // addiu ; <data> ; jr ra ; nop  -- the data word is in the fall-through path.
        Fixture fx(0x4000, {addiu(2, 0, 7), 0xDEADBEEFu, JR_RA, NOP});
        fx.add("D", 0x4000, 0x4010, {{0x4004, 4}});
        FunctionAnalysis a;
        const std::string t = fx.generate(0x4000, &a);
        INFO(t);
        CHECK(t.find("rt::addiu(ctx, 2, 0, 7);\n    rt::unreachable(0x4004u);  // IDA data word reached by fall-through\n") !=
              std::string::npos);
        CHECK(a.problems.empty());
        CHECK(a.stats.data_words == 1);
        CHECK(a.stats.reached_data_words == 1);
        CHECK(a.stats.words == 3);
        CHECK(a.stats.dead_data_words == 0);
        // Nothing after the data word is reachable: the jr ra is not emitted either.
        CHECK(t.find("return;") == std::string::npos);
        CHECK(a.stats.dead_words == 2);
    }
    {
        // jr ra ; nop ; <data> ; addiu  -- both words follow a terminator with no label: not emitted.
        Fixture fx(0x4000, {JR_RA, NOP, 0xDEADBEEFu, addiu(2, 0, 7)});
        fx.add("D", 0x4000, 0x4010, {{0x4008, 4}});
        FunctionAnalysis a;
        const std::string t = fx.generate(0x4000, &a);
        INFO(t);
        CHECK(t.find("rt::unreachable") == std::string::npos);
        CHECK(t.find("rt::addiu") == std::string::npos);
        CHECK(t.find("// 0x00004008..0x00004010: not reached by any static path, not emitted (2 words, 1 IDA data)") !=
              std::string::npos);
        CHECK(a.stats.dead_data_words == 1);
        CHECK(a.stats.dead_words == 1);
    }
}

TEST_CASE("emit: $zero ALU writes and nops are dropped, loads to $zero are kept") {
    Fixture fx(0x7000, {addu(0, 4, 5), lw(0, 4, 0), addiu(0, 0, 5), NOP, JR_RA, NOP});
    fx.add("Z", 0x7000, 0x7018);
    GenStats st;
    const std::string t = fx.generate(0x7000, nullptr, &st);
    INFO(t);
    CHECK(t.find("rt::addu") == std::string::npos);
    CHECK(t.find("rt::addiu") == std::string::npos);
    CHECK(t.find("rt::lw(ctx, 0, 4, 0);") != std::string::npos);
    CHECK(st.zero_writes_dropped == 2);
    CHECK(st.nops_dropped == 2);
}

TEST_CASE("emit: a branch that targets a delay slot re-emits the slot under its label") {
    // 0x8000 beq a0, zero, +3 -> 0x8010 ; 0x8004 addiu v0,zero,9 (slot, and the target of the branch below)
    // 0x8008 beq a1, zero, -2 -> 0x8004 ; 0x800c addiu v0,zero,1 (slot of 0x8008)
    // 0x8010 jr ra ; 0x8014 nop
    Fixture fx(0x8000, {beq(4, 0, 3), addiu(2, 0, 9), beq(5, 0, -2), addiu(2, 0, 1), JR_RA, NOP});
    fx.add("L", 0x8000, 0x8018);
    FunctionAnalysis a;
    const std::string t = fx.generate(0x8000, &a);
    INFO(t);
    CHECK(a.stats.slot_labels == 1);
    CHECK(count(t, "L_00008004:") == 1);
    // Taken path of the first branch runs the slot inside the if; the fall-through copy carries the label.
    CHECK(t.find("L_00008004:\n    rt::addiu(ctx, 2, 0, 9);") != std::string::npos);
    CHECK(count(t, "rt::addiu(ctx, 2, 0, 9);") == 2);
}

TEST_CASE("emit: problems are reported, not silently emitted") {
    // A branch in a delay slot and a jump into no function.
    Fixture fx(0x9000, {beq(4, 0, 2), beq(5, 0, 1), NOP, j(0x9f000), NOP, JR_RA, NOP});
    fx.add("P", 0x9000, 0x901c);
    FunctionAnalysis a;
    fx.generate(0x9000, &a);
    REQUIRE(a.problems.size() == 2);
    CHECK(a.problems[0].kind == ProblemKind::BranchInSlot);
    CHECK(a.problems[0].pc == 0x9000);
    CHECK(a.problems[1].kind == ProblemKind::UnownedTarget);
    CHECK(a.problems[1].target == 0x9f000);
}

TEST_CASE("emit: rt names follow the mnemonic mechanically") {
    CHECK(rt_name(decode(0x00851024, 0)) == "and_");       // and v0,a0,a1
    CHECK(rt_name(decode(0x46020000, 0)) == "add_s");      // add.s
    CHECK(rt_name(decode(0x4be25ad8, 0)) == "vmul_bc");    // vmulx.xyzw (broadcast)
    CHECK(rt_name(decode(0x70000c28, 0)) == "padduw");
    std::string s;
    GenStats st;
    CHECK(generate_insn(s, decode(0x0000000d, 0x1234), GenOptions{}, st));
    CHECK(s == "    rt::trap(ctx, 0x1234u, rt::Trap::Break, 0x0u);\n");  // break: no op of its own
    s.clear();
    CHECK(generate_insn(s, decode(0x4be25ad8, 0x285a9c), GenOptions{}, st));
    CHECK(s == "    rt::vmul_bc(ctx, 15, 11, 11, 2, 0);\n");  // vmulx.xyzw vf11, vf11, vf2x: dest, fd, fs, ft, bc
    s.clear();
    CHECK(generate_insn(s, decode(0x3c031234, 0), GenOptions{}, st));
    CHECK(s == "    rt::lui(ctx, 3, 0x1234u);\n");
    s.clear();
    CHECK(generate_insn(s, decode(lw(2, 29, -16), 0), GenOptions{}, st));
    CHECK(s == "    rt::lw(ctx, 2, 29, -16);\n");
}

TEST_CASE("emit: operand fields that differ from the generic MIPS layout") {
    std::string s;
    GenStats st;
    // qmfc2 $v0, $vf1 / qmtc2 $a0, $vf3: the vf register is the fs field (bits 15..11).
    CHECK(generate_insn(s, decode(0x48220800u, 0), GenOptions{}, st));
    CHECK(s == "    rt::qmfc2(ctx, 2, 1, false);\n");
    s.clear();
    CHECK(generate_insn(s, decode(0x48a41801u, 0), GenOptions{}, st));
    CHECK(s == "    rt::qmtc2(ctx, 4, 3, true);\n");
    s.clear();
    // cfc2 $v0, $vi22 (Q)
    CHECK(generate_insn(s, decode(0x4842b000u, 0), GenOptions{}, st));
    CHECK(s == "    rt::cfc2(ctx, 2, 22, false);\n");
    s.clear();
    // sqrt.s $f0, $f1: the EE reads the ft field.
    CHECK(generate_insn(s, decode(0x46010004u, 0), GenOptions{}, st));
    CHECK(s == "    rt::sqrt_s(ctx, 0, 1);\n");
    s.clear();
    // phmadh $zero, $a0, $a1 still writes HI/LO: kept.
    CHECK(generate_insn(s, decode((0x1Cu << 26) | (4u << 21) | (5u << 16) | (0u << 11) | (0x11u << 6) | 9u, 0), GenOptions{}, st));
    CHECK(s == "    rt::phmadh(ctx, 0, 4, 5);\n");
}

TEST_CASE("emit: jal and jalr write the link register before the delay slot") {
    // 0x3000 jal B ; 0x3004 addiu a0,zero,1 ; 0x3008 jalr v0 ; 0x300c addiu a0,zero,2 ; 0x3010 jr ra ; nop
    std::vector<std::uint32_t> w(0x200 / 4, NOP);
    w[0] = jal(0x3100); w[1] = addiu(4, 0, 1); w[2] = jalr(2); w[3] = addiu(4, 0, 2); w[4] = JR_RA;
    w[0x100 / 4] = JR_RA;
    Fixture fx(0x3000, w);
    fx.add("A", 0x3000, 0x3018);
    fx.add("B", 0x3100, 0x3108);
    const std::string t = fx.generate(0x3000);
    INFO(t);
    const std::size_t l1 = t.find("rt::jal(ctx, 0x3000u);");
    const std::size_t s1 = t.find("rt::addiu(ctx, 4, 0, 1);");
    const std::size_t c1 = t.find("fn_B_00003100(ctx);");
    const std::size_t r2 = t.find("const std::uint32_t t = rt::reg32(ctx, 2);");
    const std::size_t l2 = t.find("rt::jalr(ctx, 31, 0x3008u);");
    const std::size_t s2 = t.find("rt::addiu(ctx, 4, 0, 2);");
    const std::size_t c2 = t.find("rt::lookup_func(t)(ctx);");
    REQUIRE(l1 != std::string::npos);
    REQUIRE(l2 != std::string::npos);
    CHECK(l1 < s1);
    CHECK(s1 < c1);
    CHECK(c1 < r2);
    CHECK(r2 < l2);
    CHECK(l2 < s2);
    CHECK(s2 < c2);
}

TEST_CASE("emit: code reached only from unreachable code is not emitted and creates no labels or entries") {
    // A @ 0x1000: jr ra ; nop ; (dead) 0x1008 beq a0,zero -> 0x101c ; nop ; (dead) 0x1010 jal B+8 ; nop
    //             0x1018 addiu v0,zero,5 ; 0x101c jr ra ; nop   (only the dead beq targets 0x101c)
    // B @ 0x1100: addiu v0,zero,1 ; nop ; addiu v0,zero,2 ; jr ra ; nop
    std::vector<std::uint32_t> w(0x200 / 4, NOP);
    w[0] = JR_RA; w[2] = beq(4, 0, 4); w[4] = jal(0x1108); w[6] = addiu(2, 0, 5); w[7] = JR_RA;
    w[0x100 / 4] = addiu(2, 0, 1); w[0x108 / 4] = addiu(2, 0, 2); w[0x10c / 4] = JR_RA;
    Fixture fx(0x1000, w);
    fx.add("A", 0x1000, 0x1024);
    fx.add("B", 0x1100, 0x1114);
    FunctionAnalysis a;
    const std::string t = fx.generate(0x1000, &a);
    INFO(t);
    CHECK(a.labels.empty());
    CHECK(t.find("goto") == std::string::npos);
    CHECK(t.find("rt::addiu") == std::string::npos);
    CHECK(t.find("fn_B") == std::string::npos);
    CHECK(count(t, "return;") == 1);
    CHECK(a.stats.dead_words == 7);
    FunctionAnalysis b;
    fx.generate(0x1100, &b);
    CHECK_FALSE(b.entry_form);  // the jal into B's body is dead: no entry
}

TEST_CASE("emit: a multi-chunk function jumps between its chunks; a slot past the chunk end resumes after it") {
    // F: chunk 0x2000..0x2010, chunk 0x2100..0x2108.
    //   0x2000 addiu v0,zero,1 ; 0x2004 bne a0,zero,+? -> 0x2100 ; 0x2008 nop ; 0x200c addiu v0,zero,2  (falls to 0x2010)
    //   0x2010 is not F's: it belongs to G, so the fall-through is a tail call.
    //   0x2100 addiu v0,zero,3 ; 0x2104 j 0x2000 ; (slot 0x2108 lies outside the chunk, in no function)
    std::vector<std::uint32_t> w(0x200 / 4, NOP);
    w[0] = addiu(2, 0, 1);
    w[1] = (5u << 26) | (4u << 21) | ((0x2100u - 0x2008u) / 4u);  // bne a0, zero, 0x2100
    w[3] = addiu(2, 0, 2);
    w[4] = JR_RA;
    w[0x100 / 4] = addiu(2, 0, 3); w[0x104 / 4] = j(0x2000); w[0x108 / 4] = addiu(3, 0, 9);
    Fixture fx(0x2000, w);
    fx.add("F", 0x2000, 0x2010, {}, {{0x2100, 0x2108}});
    fx.add("G", 0x2010, 0x2018);
    FunctionAnalysis a;
    const std::string t = fx.generate(0x2000, &a);
    INFO(t);
    CHECK(a.chunks.size() == 2);
    CHECK(t.find("if (rt::cmp_ne(ctx, 4, 0)) {\n        goto L_00002100;") != std::string::npos);
    CHECK(t.find("rt::addiu(ctx, 2, 0, 2);\n    fn_G_00002010(ctx); return;") != std::string::npos);
    CHECK(t.find("L_00002100:\n    rt::addiu(ctx, 2, 0, 3);\n    rt::addiu(ctx, 3, 0, 9);\n    goto L_00002000;") != std::string::npos);
    CHECK(a.stats.slots_outside_chunk == 1);
    CHECK(a.stats.tail_calls == 1);
    CHECK(a.chunks[1].end_pc == 0x210c);
    CHECK_FALSE(a.chunks[1].end_reachable);
}

// ---------------------------------------------------------------------------------------------
// ADR-0013: cycle accounting and check points (defaults: both on).

TEST_CASE("cycles: a straight-line function is one block; nops and the delay slot count") {
    // addiu ; nop ; addiu ; jr ra ; nop  -> 5 words, one add, one entry check, no back-edge.
    Fixture fx(0x1000, {addiu(2, 0, 1), NOP, addiu(3, 0, 2), JR_RA, NOP});
    fx.add("A", 0x1000, 0x1014);
    GenStats st;
    const std::string t = fx.generate(0x1000, nullptr, &st, GenOptions{});
    INFO(t);
    CHECK(t.find("void fn_A_00001000(p3fes::EEContext& ctx) {\n    rt::check_events(ctx);\n    ctx.cycles += 5;\n"
                 "    rt::addiu(ctx, 2, 0, 1);\n") != std::string::npos);
    CHECK(count(t, "ctx.cycles +=") == 1);
    CHECK(count(t, "rt::check_events(ctx);") == 1);
    CHECK(st.cycle_adds == 1);
    CHECK(st.cycle_words == 5);
    CHECK(st.entry_checks == 1);
    CHECK(st.backedge_checks == 0);
}

TEST_CASE("cycles: a conditional branch ends its block; the fall-through and the target start new ones") {
    // 0x1000 beq a0,zero -> 0x100c ; 0x1004 slot ; 0x1008 addiu ; 0x100c jr ra ; 0x1010 nop
    // Blocks: [beq, slot] = 2, fall-through [addiu] = 1 (stops at the label), [jr, nop] = 2.
    Fixture fx(0x1000, {beq(4, 0, 2), addiu(2, 0, 1), addiu(2, 0, 2), JR_RA, NOP});
    fx.add("A", 0x1000, 0x1014);
    GenStats st;
    const std::string t = fx.generate(0x1000, nullptr, &st, GenOptions{});
    INFO(t);
    CHECK(t.find("    rt::check_events(ctx);\n    ctx.cycles += 2;\n    if (rt::cmp_eq(ctx, 4, 0)) {\n"
                 "        rt::addiu(ctx, 2, 0, 1);\n        goto L_0000100c;\n    }\n"
                 "    rt::addiu(ctx, 2, 0, 1);\n    ctx.cycles += 1;\n    rt::addiu(ctx, 2, 0, 2);\n"
                 "L_0000100c:\n    ctx.cycles += 2;\n    return;\n") != std::string::npos);
    CHECK(st.cycle_adds == 3);
    CHECK(st.cycle_words == 5);       // every word charged exactly once
    CHECK(st.backedge_checks == 0);   // forward branch: no check point
    CHECK(count(t, "rt::check_events(ctx);") == 1);
}

TEST_CASE("cycles: a likely branch charges its slot once, also on the not-taken path that skips it") {
    Fixture fx(0x1000, {bnel(4, 0, 2), addiu(2, 0, 1), addiu(2, 0, 2), JR_RA, NOP});
    fx.add("A", 0x1000, 0x1014);
    GenStats st;
    const std::string t = fx.generate(0x1000, nullptr, &st, GenOptions{});
    INFO(t);
    CHECK(t.find("    ctx.cycles += 2;\n    if (rt::cmp_ne(ctx, 4, 0)) {\n        rt::addiu(ctx, 2, 0, 1);\n"
                 "        goto L_0000100c;\n    }\n    ctx.cycles += 1;\n    rt::addiu(ctx, 2, 0, 2);\n") != std::string::npos);
    CHECK(count(t, "rt::addiu(ctx, 2, 0, 1);") == 1);
    CHECK(st.cycle_words == 5);
}

TEST_CASE("check_events: a backward branch gets a check point, a forward one does not") {
    // 0x1000 addiu v0,v0,1           <- loop head = function start
    // 0x1004 bne a0,zero -> 0x1000   (backward)   0x1008 addiu a0,a0,-1 (slot)
    // 0x100c beq a1,zero -> 0x1018   (forward)    0x1010 nop (slot)
    // 0x1014 nop ; 0x1018 jr ra ; 0x101c nop
    Fixture fx(0x1000, {addiu(2, 2, 1), bne(4, 0, -2), addiu(4, 4, -1), beq(5, 0, 2), NOP, NOP, JR_RA, NOP});
    fx.add("L", 0x1000, 0x1020);
    GenStats st;
    const std::string t = fx.generate(0x1000, nullptr, &st, GenOptions{});
    INFO(t);
    // The entry check sits before the loop label, so the loop does not check twice per iteration.
    CHECK(t.find("{\n    rt::check_events(ctx);\nL_00001000:\n    ctx.cycles += 3;\n    rt::addiu(ctx, 2, 2, 1);\n"
                 "    if (rt::cmp_ne(ctx, 4, 0)) {\n        rt::addiu(ctx, 4, 4, -1);\n"
                 "        rt::check_events(ctx); goto L_00001000;\n    }\n") != std::string::npos);
    CHECK(t.find("goto L_00001018;") != std::string::npos);
    CHECK(t.find("rt::check_events(ctx); goto L_00001018;") == std::string::npos);
    CHECK(st.entry_checks == 1);
    CHECK(st.backedge_checks == 1);
    CHECK(count(t, "rt::check_events(ctx);") == 2);
    // [addiu, bne, slot] 3, [beq, slot] 2, [nop] 1, [jr, nop] 2: all 8 words once.
    CHECK(st.cycle_adds == 4);
    CHECK(st.cycle_words == 8);
}

TEST_CASE("check_events: a backward j gets a check point") {
    // 0x2000 addiu ; 0x2004 beq a0,zero -> 0x2014 (forward exit) ; 0x2008 nop ; 0x200c j 0x2000 ; 0x2010 nop
    // 0x2014 jr ra ; 0x2018 nop
    Fixture fx(0x2000, {addiu(2, 2, 1), beq(4, 0, 3), NOP, j(0x2000), NOP, JR_RA, NOP});
    fx.add("J", 0x2000, 0x201c);
    GenStats st;
    const std::string t = fx.generate(0x2000, nullptr, &st, GenOptions{});
    INFO(t);
    CHECK(t.find("    ctx.cycles += 2;\n    rt::check_events(ctx); goto L_00002000;\n") != std::string::npos);
    CHECK(t.find("rt::check_events(ctx); goto L_00002014;") == std::string::npos);
    CHECK(st.backedge_checks == 1);
    CHECK(st.cycle_words == 7);
}

TEST_CASE("check_events: switch cases that go backwards get a check point, forward cases do not") {
    // 0x2000 addiu v0,zero,1 (backward case target = function start) ; 0x2004 lw v1,0(v1) ; 0x2008 jr v1
    // 0x200c nop ; 0x2010 addiu v0,zero,2 (forward case) ; 0x2014 jr ra ; 0x2018 nop
    Fixture fx(0x2000, {addiu(2, 0, 1), lw(3, 3, 0), jr(3), NOP, addiu(2, 0, 2), JR_RA, NOP});
    fx.add("S", 0x2000, 0x201c);
    SwitchSite s;
    s.jr_ea = 0x2008;
    s.func_ea = 0x2000;
    s.reg = 3;
    s.targets = {0x2000, 0x2010};
    fx.sw.by_jr[0x2008] = s;
    GenStats st;
    const std::string t = fx.generate(0x2000, nullptr, &st, GenOptions{});
    INFO(t);
    CHECK(t.find("case 0x2000u: rt::check_events(ctx); goto L_00002000;") != std::string::npos);
    CHECK(t.find("case 0x2010u: goto L_00002010;") != std::string::npos);
    CHECK(t.find("    rt::check_events(ctx);\nL_00002000:\n    ctx.cycles += 4;\n") != std::string::npos);
    CHECK(t.find("L_00002010:\n    ctx.cycles += 3;\n") != std::string::npos);
    CHECK(st.backedge_checks == 1);
    CHECK(st.cycle_words == 7);
}

TEST_CASE("check_events: an entry-form function checks once per invocation, before the entry dispatch") {
    // A @ 0x3000: jal B ; nop ; jal B+8 ; nop ; jr ra ; nop        (calls do not end a block: 6 words)
    // B @ 0x3100: addiu ; nop ; (0x3108, entry) addiu ; jr ra ; nop
    std::vector<std::uint32_t> w(0x200 / 4, NOP);
    w[0] = jal(0x3100); w[2] = jal(0x3108); w[4] = JR_RA;
    w[0x100 / 4] = addiu(2, 0, 1); w[0x108 / 4] = addiu(2, 0, 2); w[0x10c / 4] = JR_RA;
    Fixture fx(0x3000, w);
    fx.add("A", 0x3000, 0x3018);
    fx.add("B", 0x3100, 0x3114);
    GenStats sa;
    const std::string ta = fx.generate(0x3000, nullptr, &sa, GenOptions{});
    INFO(ta);
    CHECK(ta.find("    rt::check_events(ctx);\n    ctx.cycles += 6;\n    rt::jal(ctx, 0x3000u);\n") != std::string::npos);
    CHECK(sa.cycle_adds == 1);
    GenStats sb;
    const std::string tb = fx.generate(0x3100, nullptr, &sb, GenOptions{});
    INFO(tb);
    CHECK(tb.find("std::uint32_t entry_pc) {\n    rt::check_events(ctx);\n    switch (entry_pc) {\n") != std::string::npos);
    CHECK(tb.find("L_00003100:\n    ctx.cycles += 2;\n") != std::string::npos);
    CHECK(tb.find("L_00003108:\n    ctx.cycles += 3;\n") != std::string::npos);
    CHECK(tb.find("void fn_B_00003100(p3fes::EEContext& ctx) { fn_B_00003100_entry(ctx, 0x3100u); }") != std::string::npos);
    CHECK(count(tb, "rt::check_events(ctx);") == 1);
    CHECK(sb.entry_checks == 1);
    CHECK(sb.backedge_checks == 0);
}

TEST_CASE("cycles: a delay slot that is a branch target keeps every path exact") {
    // 0x8000 beq a0,zero -> 0x8010 ; 0x8004 addiu v0,zero,9 (slot; also the target of 0x8008)
    // 0x8008 beq a1,zero -> 0x8004 (backward) ; 0x800c addiu v0,zero,1 (slot) ; 0x8010 jr ra ; 0x8014 nop
    // Path sums: taken at 0x8000: 1 + 1 + 2 = 4 (beq, slot, jr, nop); not taken then not taken:
    // 1 + 1 + 2 + 2 = 6; each loop back to the slot label: 1 + 2 = 3 (slot, beq, slot).
    Fixture fx(0x8000, {beq(4, 0, 3), addiu(2, 0, 9), beq(5, 0, -2), addiu(2, 0, 1), JR_RA, NOP});
    fx.add("L", 0x8000, 0x8018);
    GenStats st;
    const std::string t = fx.generate(0x8000, nullptr, &st, GenOptions{});
    INFO(t);
    CHECK(t.find("    rt::check_events(ctx);\n    ctx.cycles += 1;\n    if (rt::cmp_eq(ctx, 4, 0)) {\n"
                 "        ctx.cycles += 1;\n        rt::addiu(ctx, 2, 0, 9);\n        goto L_00008010;\n    }\n"
                 "L_00008004:\n    ctx.cycles += 1;\n    rt::addiu(ctx, 2, 0, 9);\n    ctx.cycles += 2;\n"
                 "    if (rt::cmp_eq(ctx, 5, 0)) {\n        rt::addiu(ctx, 2, 0, 1);\n"
                 "        rt::check_events(ctx); goto L_00008004;\n    }\n    rt::addiu(ctx, 2, 0, 1);\n"
                 "L_00008010:\n    ctx.cycles += 2;\n    return;\n") != std::string::npos);
    CHECK(st.backedge_checks == 1);
}

TEST_CASE("cycles / check_events: each can be switched off on its own") {
    Fixture fx(0x1000, {addiu(2, 2, 1), bne(4, 0, -2), addiu(4, 4, -1), JR_RA, NOP});
    fx.add("L", 0x1000, 0x1014);
    GenOptions no_cycles;
    no_cycles.cycles = false;
    GenStats s1;
    std::string t = fx.generate(0x1000, nullptr, &s1, no_cycles);
    INFO(t);
    CHECK(t.find("ctx.cycles") == std::string::npos);
    CHECK(count(t, "rt::check_events(ctx);") == 2);
    CHECK(s1.cycle_adds == 0);
    GenOptions no_checks;
    no_checks.check_events = false;
    GenStats s2;
    t = fx.generate(0x1000, nullptr, &s2, no_checks);
    INFO(t);
    CHECK(t.find("check_events") == std::string::npos);
    CHECK(count(t, "ctx.cycles +=") == 2);
    CHECK(s2.entry_checks == 0);
    CHECK(s2.backedge_checks == 0);
    t = fx.generate(0x1000);  // legacy_options(): neither
    CHECK(t.find("ctx.cycles") == std::string::npos);
    CHECK(t.find("check_events") == std::string::npos);
}
