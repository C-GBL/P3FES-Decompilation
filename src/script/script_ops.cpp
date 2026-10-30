// BF script VM: the operand-stack opcode handlers, scrOperation and the COMM-side accessors
// (game/include/p3fes/game/script_vm.h), hand-decompiled from SLUS_216.21 (scrTraceCode.c band,
// docs/ANALYSIS/18_script_vm.md). Phase 5: these replace the recompiled bodies listed in
// game/replaced.txt; tests/game/test_script_vm.cpp runs each against its __recomp body.
//
// Stack discipline (section 2.3 of the doc): `sp` counts the used slots; a push stores tag and value at
// slot sp and increments, a pop decrements and reads. The checks `sp < 27` (push) and `sp > 0` (pop)
// are K_Assert calls -- sub_19D3F0 -- and K_Abort on an unknown tag is sub_19D400; BOTH ARE `jr $ra`
// IN THE RETAIL BUILD, so a failed check continues with the same stores (a pop at sp == 0 reads slot
// -1 and leaves sp == -1; an unknown tag pops 0). The hand versions keep those calls through
// guest::call for their check point and two cycles, and do what the original did afterwards.
//
// The enter/charge lines are the virtual-time model of the recompiled bodies (ADR-0013; block costs from
// recomp/generated/fn_0029_0035ac90_00367d70.cpp, where `ctx.cycles += N` marks each basic block).
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 38 of the 42 functions here are p3fes_handgen's register-faithful
// bodies (their hand versions differed from the original: frame/spills 35, scratch GPRs 3); the four scrGet* leaves
// (cmd timer, message id, current task, user data) are the hand-written versions. Readability pass 2026-10-21 (slice
// read_script) over the 38: ScrTask offsets and $gp globals by name (scr::ofs, script_vm.h), the task register named
// (`Gpr& task = s0`), tag and opcode constants (scr::Tag, scr::Op), a role comment per function, block roles, and the
// gotos turned into if / else -- a block two paths share is written on both (each path runs exactly the generated
// statements), and in CodeFunc_IF / scrOperation the original's inlined PopInt / PopFloat bodies, the float push and
// the epilogue are local lambdas called where the generated body jumped to them. Every guest statement, frame, spill,
// link, cycle charge and check point is the generated body's, in its order on every path.
#include "p3fes/game/script_vm.h"

#include "p3fes/ee/fpu.h"
#include "p3fes/ee/hilo.h"
#include "p3fes/game/guest.h"
#include "p3fes/game/hg_cpu.h"

// Callees of the register-faithful bodies (p3fes_handgen), through their recomp_gen entry points.
namespace p3fes::recomp_gen {
void fn_scrOperation_0035d350(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line)
void fn_sub_19D400_0019d400(p3fes::EEContext&);  // K_Abort(message, file, line)
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

using namespace scr;

u32 current_task(const EEContext& ctx) { return guest::load<u32>(ctx, kCurrentTask); }

}  // namespace

// --- PUSH ---------------------------------------------------------------------------------------------

// 0x0035C300 CodeFunc_PushI -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Opcode PUSHI (sScrOpcodeTbl 0x69D3E0): pushes the 32-bit word that follows the instruction (insn[pc + 1])
// with tag 0 and steps over both words (pc += 2). Asserts sp < 27 (line 43; a no-op in retail). Returns 1.
// Blocks: entry 16 (pc += 1, the value word, the sp test), push 20.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_PushI(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sb, hg::sd,
          hg::sll, hg::slti, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s1;  // $s1: the ScrTask ($a0 at entry) for the whole body
    // 0x0035c300
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s1
    lw(v0, a0, ofs::pc);  // pc += 1: the value word follows the instruction
    v0 = addiu(v0, 1);
    sw(v0, a0, ofs::pc);
    v1 = sll(v0, 2);
    lw(v0, a0, ofs::insn);
    v0 = addu(v0, v1);
    lw(s0, v0, 0);  // value = insn[pc] (the whole word)
    lw(v0, a0, ofs::sp);
    v0 = slti(v0, kStackSlots);  // a push asserts sp < 27
    if (v0 == 0) {
        // 0x0035c340
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 43;
        jal(ctx, 0x35C34Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035c354 (the shared epilogue, written out on this path)
    charge(ctx, 20);
    // push: tags[sp] = tag, values[sp] = value, sp += 1
    lw(v0, task, ofs::sp);
    v0 = addu(v0, task);
    sb(zero, v0, ofs::tags);
    lw(v0, task, ofs::sp);
    v0 = sll(v0, 2);
    v0 = addu(v0, task);
    sw(s0, v0, ofs::values);
    lw(v0, task, ofs::sp);
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::sp);
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0035C3B0 CodeFunc_PushS -- 156 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Opcode PUSHIS: pushes the instruction's sign-extended s16 operand with tag 0; pc += 1. Returns 1.
// Blocks: entry 14, push 20.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_PushS(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lh, hg::lq, hg::lw, hg::sb,
          hg::sd, hg::sll, hg::slti, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s1;  // $s1: the ScrTask ($a0 at entry) for the whole body
    // 0x0035c3b0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s1
    lw(v1, a0, ofs::insn);
    lw(v0, a0, ofs::pc);  // operand = insn[pc].operand
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lh(s0, v0, ofs::operand);  // the s16 operand of insn[pc]
    lw(v0, a0, ofs::sp);
    v0 = slti(v0, kStackSlots);  // a push asserts sp < 27
    if (v0 == 0) {
        // 0x0035c3e8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 43;
        jal(ctx, 0x35C3F4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035c3fc (the shared epilogue, written out on this path)
    charge(ctx, 20);
    // push: tags[sp] = tag, values[sp] = value, sp += 1
    lw(v0, task, ofs::sp);
    v0 = addu(v0, task);
    sb(zero, v0, ofs::tags);
    lw(v0, task, ofs::sp);
    v0 = sll(v0, 2);
    v0 = addu(v0, task);
    sw(s0, v0, ofs::values);
    lw(v0, task, ofs::sp);
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::sp);
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0035C450 CodeFunc_PushF -- 164 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// Opcode PUSHF: pushes insn[pc + 1] as a float (tag 1; the word passes through $f20 unchanged); pc += 2.
// Asserts sp < 27 (line 55). Returns 1. Blocks: entry 16, push 20.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_PushF(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::lwc1,
          hg::sb, hg::sd, hg::sll, hg::slti, hg::sq, hg::sw, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f20{ctx, 20};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035c450
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    lw(v0, a0, ofs::pc);  // pc += 1: the value word follows the instruction
    v0 = addiu(v0, 1);
    sw(v0, a0, ofs::pc);
    v1 = sll(v0, 2);
    lw(v0, a0, ofs::insn);
    v0 = addu(v0, v1);
    lwc1(f20, v0, 0);  // value = insn[pc] (the whole word, as a float)
    lw(v0, a0, ofs::sp);
    v0 = slti(v0, kStackSlots);  // a push asserts sp < 27
    if (v0 == 0) {
        // 0x0035c490
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 55;
        jal(ctx, 0x35C49Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035c4a4 (the shared epilogue, written out on this path)
    charge(ctx, 20);
    v0 = 1;
    // push: tags[sp] = tag, values[sp] = value, sp += 1
    lw(v1, task, ofs::sp);
    v1 = addu(v1, task);
    sb(v0, v1, ofs::tags);
    lw(v1, task, ofs::sp);
    v1 = sll(v1, 2);
    v1 = addu(v1, task);
    swc1(f20, v1, ofs::values);
    lw(v1, task, ofs::sp);
    v1 = addiu(v1, 1);
    sw(v1, task, ofs::sp);
    lw(v1, task, ofs::pc);  // pc += 1
    v1 = addiu(v1, 1);
    sw(v1, task, ofs::pc);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0035C500 CodeFunc_PushIX -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Opcode PUSHIX: pushes the global int g_scrGlobals[operand] with tag 0; pc += 1. Returns 1.
// Blocks: entry 18, push 20.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_PushIX(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lh, hg::lq, hg::lw, hg::sb,
          hg::sd, hg::sll, hg::slti, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s1;  // $s1: the ScrTask ($a0 at entry) for the whole body
    // 0x0035c500
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s1
    lw(v1, a0, ofs::insn);
    lw(v0, a0, ofs::pc);  // operand = insn[pc].operand
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lh(v0, v0, ofs::operand);  // the s16 operand of insn[pc]
    v1 = sll(v0, 2);
    lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
    v0 = addu(v0, v1);
    lw(s0, v0, 0);  // value = insn[pc] (the whole word)
    lw(v0, a0, ofs::sp);
    v0 = slti(v0, kStackSlots);  // a push asserts sp < 27
    if (v0 == 0) {
        // 0x0035c548
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 43;
        jal(ctx, 0x35C554u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035c55c (the shared epilogue, written out on this path)
    charge(ctx, 20);
    // push: tags[sp] = tag, values[sp] = value, sp += 1
    lw(v0, task, ofs::sp);
    v0 = addu(v0, task);
    sb(zero, v0, ofs::tags);
    lw(v0, task, ofs::sp);
    v0 = sll(v0, 2);
    v0 = addu(v0, task);
    sw(s0, v0, ofs::values);
    lw(v0, task, ofs::sp);
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::sp);
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0035C5B0 CodeFunc_PushIF -- 172 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// Opcode PUSHIF: pushes the global float (g_scrGlobals + 1024)[operand] with tag 1; pc += 1. Returns 1.
// Blocks: entry 18, push 20.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_PushIF(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lh, hg::lq, hg::lw,
          hg::lwc1, hg::sb, hg::sd, hg::sll, hg::slti, hg::sq, hg::sw, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f20{ctx, 20};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035c5b0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    lw(v1, a0, ofs::insn);
    lw(v0, a0, ofs::pc);  // operand = insn[pc].operand
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lh(v0, v0, ofs::operand);  // the s16 operand of insn[pc]
    v1 = sll(v0, 2);
    lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
    v0 = addu(v0, v1);
    lwc1(f20, v0, ofs::global_floats);
    lw(v0, a0, ofs::sp);
    v0 = slti(v0, kStackSlots);  // a push asserts sp < 27
    if (v0 == 0) {
        // 0x0035c5f8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 55;
        jal(ctx, 0x35C604u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035c60c (the shared epilogue, written out on this path)
    charge(ctx, 20);
    v0 = 1;
    // push: tags[sp] = tag, values[sp] = value, sp += 1
    lw(v1, task, ofs::sp);
    v1 = addu(v1, task);
    sb(v0, v1, ofs::tags);
    lw(v1, task, ofs::sp);
    v1 = sll(v1, 2);
    v1 = addu(v1, task);
    swc1(f20, v1, ofs::values);
    lw(v1, task, ofs::sp);
    v1 = addiu(v1, 1);
    sw(v1, task, ofs::sp);
    lw(v1, task, ofs::pc);  // pc += 1
    v1 = addiu(v1, 1);
    sw(v1, task, ofs::pc);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0035C660 CodeFunc_PushLIX -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Opcode PUSHLIX: pushes the procedure-local int local_ints[operand] with tag 0; pc += 1. Returns 1.
// Blocks: entry 18, push 20.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_PushLIX(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lh, hg::lq, hg::lw, hg::sb,
          hg::sd, hg::sll, hg::slti, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s1;  // $s1: the ScrTask ($a0 at entry) for the whole body
    // 0x0035c660
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s1
    lw(v1, a0, ofs::insn);
    lw(v0, a0, ofs::pc);  // operand = insn[pc].operand
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lh(v0, v0, ofs::operand);  // the s16 operand of insn[pc]
    v1 = sll(v0, 2);
    lw(v0, a0, ofs::local_ints);
    v0 = addu(v0, v1);
    lw(s0, v0, 0);  // value = insn[pc] (the whole word)
    lw(v0, a0, ofs::sp);
    v0 = slti(v0, kStackSlots);  // a push asserts sp < 27
    if (v0 == 0) {
        // 0x0035c6a8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 43;
        jal(ctx, 0x35C6B4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035c6bc (the shared epilogue, written out on this path)
    charge(ctx, 20);
    // push: tags[sp] = tag, values[sp] = value, sp += 1
    lw(v0, task, ofs::sp);
    v0 = addu(v0, task);
    sb(zero, v0, ofs::tags);
    lw(v0, task, ofs::sp);
    v0 = sll(v0, 2);
    v0 = addu(v0, task);
    sw(s0, v0, ofs::values);
    lw(v0, task, ofs::sp);
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::sp);
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0035C710 CodeFunc_PushLFX -- 172 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// Opcode PUSHLFX: pushes the local float local_floats[operand] with tag 1; pc += 1. Returns 1.
// Blocks: entry 18, push 20.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_PushLFX(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lh, hg::lq, hg::lw,
          hg::lwc1, hg::sb, hg::sd, hg::sll, hg::slti, hg::sq, hg::sw, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f20{ctx, 20};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035c710
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    lw(v1, a0, ofs::insn);
    lw(v0, a0, ofs::pc);  // operand = insn[pc].operand
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lh(v0, v0, ofs::operand);  // the s16 operand of insn[pc]
    v1 = sll(v0, 2);
    lw(v0, a0, ofs::local_floats);
    v0 = addu(v0, v1);
    lwc1(f20, v0, 0);  // value = insn[pc] (the whole word, as a float)
    lw(v0, a0, ofs::sp);
    v0 = slti(v0, kStackSlots);  // a push asserts sp < 27
    if (v0 == 0) {
        // 0x0035c758
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 55;
        jal(ctx, 0x35C764u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035c76c (the shared epilogue, written out on this path)
    charge(ctx, 20);
    v0 = 1;
    // push: tags[sp] = tag, values[sp] = value, sp += 1
    lw(v1, task, ofs::sp);
    v1 = addu(v1, task);
    sb(v0, v1, ofs::tags);
    lw(v1, task, ofs::sp);
    v1 = sll(v1, 2);
    v1 = addu(v1, task);
    swc1(f20, v1, ofs::values);
    lw(v1, task, ofs::sp);
    v1 = addiu(v1, 1);
    sw(v1, task, ofs::sp);
    lw(v1, task, ofs::pc);  // pc += 1
    v1 = addiu(v1, 1);
    sw(v1, task, ofs::pc);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0035C7C0 CodeFunc_PushSTR -- 168 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Opcode PUSHSTR: pushes strings + operand (a pointer into section 4) with tag 5; pc += 1. Returns 1.
// Blocks: entry 16, push 21 (assertion line 69).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_PushSTR(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lh, hg::lq, hg::lw, hg::sb,
          hg::sd, hg::sll, hg::slti, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s1;  // $s1: the ScrTask ($a0 at entry) for the whole body
    // 0x0035c7c0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s1
    lw(a1, a0, ofs::strings);
    lw(v1, a0, ofs::insn);
    lw(v0, a0, ofs::pc);  // operand = insn[pc].operand
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lh(v0, v0, ofs::operand);  // the s16 operand of insn[pc]
    s0 = addu(a1, v0);
    lw(v0, a0, ofs::sp);
    v0 = slti(v0, kStackSlots);  // a push asserts sp < 27
    if (v0 == 0) {
        // 0x0035c800
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 69;
        jal(ctx, 0x35C80Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035c814 (the shared epilogue, written out on this path)
    charge(ctx, 21);
    v1 = 5;
    // push: tags[sp] = tag, values[sp] = value, sp += 1
    lw(v0, task, ofs::sp);
    v0 = addu(v0, task);
    sb(v1, v0, ofs::tags);
    lw(v0, task, ofs::sp);
    v0 = sll(v0, 2);
    v0 = addu(v0, task);
    sw(s0, v0, ofs::values);
    lw(v0, task, ofs::sp);
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::sp);
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0035C870 CodeFunc_PushREG -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode PUSHREG: pushes the COMM return register (slot 27, set by scrSet*ReturnVal) with its tag byte and value
// word as they are (a float return keeps tag 1, an unset register whatever it holds); pc += 1. Returns 1.
// Blocks: entry 8 (only the sp test), push 21 (assertion line 268).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_PushREG(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::lb, hg::ld, hg::lq, hg::lw,
          hg::lwc1, hg::sb, hg::sd, hg::sll, hg::slti, hg::sq, hg::sw, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035c870
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    lw(v0, a0, ofs::sp);
    v0 = slti(v0, kStackSlots);  // a push asserts sp < 27
    if (v0 == 0) {
        // 0x0035c890
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 268;
        jal(ctx, 0x35C89Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035c8a4 (the shared epilogue, written out on this path)
    charge(ctx, 21);
    lb(v1, task, ofs::ret_tag);
    // push: tags[sp] = tag, values[sp] = value, sp += 1
    lw(v0, task, ofs::sp);
    v0 = addu(v0, task);
    sb(v1, v0, ofs::tags);
    lw(v0, task, ofs::sp);
    v0 = sll(v0, 2);
    v0 = addu(v0, task);
    lwc1(f0, task, ofs::ret_value);
    swc1(f0, v0, ofs::values);
    lw(v0, task, ofs::sp);
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::sp);
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035D210 CodeFunc_Call -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Opcode CALL: pushes the current pc with tag 4 (a return address; END pops it and continues at + 1) and jumps to
// proc_labels[operand].insn. Asserts sp < 27 (line 111). Returns 1.
// Blocks: entry 10 (the pc is read before the push), push + jump 28.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_Call(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lh, hg::lq, hg::lw, hg::sb,
          hg::sd, hg::sll, hg::slti, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s1;  // $s1: the ScrTask ($a0 at entry) for the whole body
    // 0x0035d210
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s1
    lw(s0, a0, ofs::pc);
    lw(v0, a0, ofs::sp);
    v0 = slti(v0, kStackSlots);  // a push asserts sp < 27
    if (v0 == 0) {
        // 0x0035d238
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 111;
        jal(ctx, 0x35D244u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035d24c
    charge(ctx, 28);
    v1 = 4;
    // push: tags[sp] = tag, values[sp] = value, sp += 1
    lw(v0, task, ofs::sp);
    v0 = addu(v0, task);
    sb(v1, v0, ofs::tags);
    lw(v0, task, ofs::sp);
    v0 = sll(v0, 2);
    v0 = addu(v0, task);
    sw(s0, v0, ofs::values);
    lw(v0, task, ofs::sp);
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::sp);
    lw(v1, task, ofs::insn);
    lw(v0, task, ofs::pc);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lh(v0, v0, ofs::operand);  // the s16 operand of insn[pc]
    v1 = sll(v0, 5);
    lw(v0, task, ofs::proc_labels);
    v0 = addu(v1, v0);
    lw(v0, v0, ofs::label_insn);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// --- POP ----------------------------------------------------------------------------------------------
// 0x35C900 / 0x35CA70 / 0x35CC00 / 0x35CD70: entry 7 (the sp > 0 test), the pop, store + pc 18.

// 0x0035C900 CodeFunc_PopIX -- 364 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode POPIX: g_scrGlobals[operand] = pop as an int (the inlined PopInt(): tag 3 -> (s32) floats[value],
// 2 -> ints[value], 1 -> (s32) value, 0 and 4 -> the raw word, else K_Abort "PopInt(..) invalid stack type!!" (line
// 135; a no-op) and 0). Asserts sp > 0 (line 122). pc += 1; returns 1. Blocks: entry 7, the pop, store + pc 18.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_PopIX(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::cvt_w_s, hg::enter, hg::i64, hg::jal, hg::lb,
          hg::ld, hg::lh, hg::lq, hg::lw, hg::lwc1, hg::mfc1, hg::sd, hg::sll, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035c900
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    lw(v0, a0, ofs::sp);
    if (i64(v0) <= 0) {
        // 0x0035c91c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 122;
        jal(ctx, 0x35C928u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035c930
    charge(ctx, 8);
    // pop: sp -= 1, then the top slot by its tag
    lw(v0, task, ofs::sp);
    a0 = addiu(v0, -1);
    sw(a0, task, ofs::sp);
    v0 = addu(a0, task);
    lb(v1, v0, ofs::tags);
    v0 = kTagGlobalFloat;
    if (v1 == v0) {
        // 0x0035c9d8: kTagGlobalFloat
        charge(ctx, 11);
        v0 = sll(a0, 2);
        v0 = addu(v0, task);
        lw(v0, v0, ofs::values);
        v1 = sll(v0, 2);
        lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
        v0 = addu(v0, v1);
        lwc1(f0, v0, ofs::global_floats);
        cvt_w_s(f0, f0);
        mfc1(a0, f0);
    } else {
        // 0x0035c950
        charge(ctx, 3);
        v0 = kTagGlobalInt;
        if (v1 == v0) {
            // 0x0035c9b4: kTagGlobalInt
            charge(ctx, 9);
            v0 = sll(a0, 2);
            v0 = addu(v0, task);
            lw(v0, v0, ofs::values);
            v1 = sll(v0, 2);
            lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
        } else {
            // 0x0035c95c
            charge(ctx, 3);
            v0 = kTagFloat;
            if (v1 == v0) {
                // 0x0035c998: kTagFloat
                charge(ctx, 7);
                v0 = sll(a0, 2);
                v0 = addu(v0, task);
                lwc1(f0, v0, ofs::values);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
            } else {
                // 0x0035c968
                charge(ctx, 3);
                v0 = kTagReturnAddress;
                if (v1 != v0) {
                    // 0x0035c974: not kTagReturnAddress
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x0035c97c
                        charge(ctx, 2);
                        // 0x0035ca04
                        charge(ctx, 8);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -11776);  // "PopInt(..) invalid stack type!!\n"
                        a1 = 0x6A0000;
                        a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                        a2 = 135;
                        jal(ctx, 0x35CA18u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                        a0 = 0;
                        // 0x0035ca24 (the shared epilogue, written out on this path)
                        charge(ctx, 18);
                        lw(v1, task, ofs::insn);
                        lw(v0, task, ofs::pc);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, v1);
                        lh(v0, v0, ofs::operand);  // the s16 operand of insn[pc]
                        v1 = sll(v0, 2);
                        lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
                        v0 = addu(v0, v1);
                        sw(a0, v0, 0);
                        lw(v0, task, ofs::pc);  // pc += 1
                        v0 = addiu(v0, 1);
                        sw(v0, task, ofs::pc);
                        v0 = 1;
                        ld(ra, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x20);
                        return;
                    }
                }
                // 0x0035c984
                charge(ctx, 5);
                v0 = sll(a0, 2);
                v0 = addu(v0, task);
                lw(a0, v0, ofs::values);
            }
        }
    }
    // 0x0035ca24 (the shared epilogue, written out on this path)
    charge(ctx, 18);
    lw(v1, task, ofs::insn);
    lw(v0, task, ofs::pc);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lh(v0, v0, ofs::operand);  // the s16 operand of insn[pc]
    v1 = sll(v0, 2);
    lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
    v0 = addu(v0, v1);
    sw(a0, v0, 0);
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035CA70 CodeFunc_PopFX -- 396 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode POPFX: (g_scrGlobals + 1024)[operand] = pop as a float (the inlined PopFloat(): tag 3 -> floats[value],
// 2 -> (f32) ints[value], 1 -> value, 0 -> (f32) value, 4 -> K_Abort "PopFloat(..) invalid stack type(RET)!!" (152)
// and 0.0, else K_Abort "(?)" (161) and 0.0). Asserts sp > 0 (line 146). pc += 1; returns 1.
// Blocks: entry 7, the pop, store + pc 18.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_PopFX(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::cvt_s_w, hg::enter, hg::i64, hg::jal, hg::lb,
          hg::ld, hg::lh, hg::lq, hg::lw, hg::lwc1, hg::mtc1, hg::sd, hg::sll, hg::sq, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035ca70
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    lw(v0, a0, ofs::sp);
    if (i64(v0) <= 0) {
        // 0x0035ca8c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 146;
        jal(ctx, 0x35CA98u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035caa0
    charge(ctx, 8);
    // pop: sp -= 1, then the top slot by its tag
    lw(v0, task, ofs::sp);
    a0 = addiu(v0, -1);
    sw(a0, task, ofs::sp);
    v0 = addu(a0, task);
    lb(v1, v0, ofs::tags);
    v0 = kTagGlobalFloat;
    if (v1 == v0) {
        // 0x0035cb70: kTagGlobalFloat
        charge(ctx, 9);
        v0 = sll(a0, 2);
        v0 = addu(v0, task);
        lw(v0, v0, ofs::values);
        v1 = sll(v0, 2);
        lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
        v0 = addu(v0, v1);
        lwc1(f0, v0, ofs::global_floats);
    } else {
        // 0x0035cac0
        charge(ctx, 3);
        v0 = kTagGlobalInt;
        if (v1 == v0) {
            // 0x0035cb48: kTagGlobalInt
            charge(ctx, 10);
            v0 = sll(a0, 2);
            v0 = addu(v0, task);
            lw(v0, v0, ofs::values);
            v1 = sll(v0, 2);
            lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
            v0 = addu(v0, v1);
            lwc1(f0, v0, 0);
            cvt_s_w(f0, f0);
        } else {
            // 0x0035cacc
            charge(ctx, 3);
            v0 = kTagFloat;
            if (v1 == v0) {
                // 0x0035cb34: kTagFloat
                charge(ctx, 5);
                v0 = sll(a0, 2);
                v0 = addu(v0, task);
                lwc1(f0, v0, ofs::values);
            } else {
                // 0x0035cad8
                charge(ctx, 3);
                v0 = kTagReturnAddress;
                if (v1 == v0) {
                    // 0x0035cb0c: kTagReturnAddress
                    charge(ctx, 10);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -11728);  // "PopFloat(..) invalid stack type(RET)!!\n"
                    a1 = 0x6A0000;
                    a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                    a2 = 152;
                    jal(ctx, 0x35CB20u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                    mtc1(zero, f0);
                } else {
                    // 0x0035cae4
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x0035caf4
                        charge(ctx, 6);
                        v0 = sll(a0, 2);
                        v0 = addu(v0, task);
                        lwc1(f0, v0, ofs::values);
                        cvt_s_w(f0, f0);
                    } else {
                        // 0x0035caec
                        charge(ctx, 2);
                        // 0x0035cb94
                        charge(ctx, 8);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -11680);  // "PopFloat(..) invalid stack type(?)!!\n"
                        a1 = 0x6A0000;
                        a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                        a2 = 161;
                        jal(ctx, 0x35CBA8u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                        mtc1(zero, f0);
                    }
                }
            }
        }
    }
    // 0x0035cbb4 (the shared epilogue, written out on this path)
    charge(ctx, 18);
    lw(v1, task, ofs::insn);
    lw(v0, task, ofs::pc);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lh(v0, v0, ofs::operand);  // the s16 operand of insn[pc]
    v1 = sll(v0, 2);
    lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
    v0 = addu(v0, v1);
    swc1(f0, v0, ofs::global_floats);
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035CC00 CodeFunc_PopLIX -- 364 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode POPLIX: local_ints[operand] = pop as an int (PopInt, as CodeFunc_PopIX). pc += 1; returns 1.
// Blocks: entry 7, the pop, store + pc 18.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_PopLIX(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::cvt_w_s, hg::enter, hg::i64, hg::jal, hg::lb,
          hg::ld, hg::lh, hg::lq, hg::lw, hg::lwc1, hg::mfc1, hg::sd, hg::sll, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035cc00
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    lw(v0, a0, ofs::sp);
    if (i64(v0) <= 0) {
        // 0x0035cc1c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 122;
        jal(ctx, 0x35CC28u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035cc30
    charge(ctx, 8);
    // pop: sp -= 1, then the top slot by its tag
    lw(v0, task, ofs::sp);
    a0 = addiu(v0, -1);
    sw(a0, task, ofs::sp);
    v0 = addu(a0, task);
    lb(v1, v0, ofs::tags);
    v0 = kTagGlobalFloat;
    if (v1 == v0) {
        // 0x0035ccd8: kTagGlobalFloat
        charge(ctx, 11);
        v0 = sll(a0, 2);
        v0 = addu(v0, task);
        lw(v0, v0, ofs::values);
        v1 = sll(v0, 2);
        lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
        v0 = addu(v0, v1);
        lwc1(f0, v0, ofs::global_floats);
        cvt_w_s(f0, f0);
        mfc1(a0, f0);
    } else {
        // 0x0035cc50
        charge(ctx, 3);
        v0 = kTagGlobalInt;
        if (v1 == v0) {
            // 0x0035ccb4: kTagGlobalInt
            charge(ctx, 9);
            v0 = sll(a0, 2);
            v0 = addu(v0, task);
            lw(v0, v0, ofs::values);
            v1 = sll(v0, 2);
            lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
        } else {
            // 0x0035cc5c
            charge(ctx, 3);
            v0 = kTagFloat;
            if (v1 == v0) {
                // 0x0035cc98: kTagFloat
                charge(ctx, 7);
                v0 = sll(a0, 2);
                v0 = addu(v0, task);
                lwc1(f0, v0, ofs::values);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
            } else {
                // 0x0035cc68
                charge(ctx, 3);
                v0 = kTagReturnAddress;
                if (v1 != v0) {
                    // 0x0035cc74: not kTagReturnAddress
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x0035cc7c
                        charge(ctx, 2);
                        // 0x0035cd04
                        charge(ctx, 8);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -11776);  // "PopInt(..) invalid stack type!!\n"
                        a1 = 0x6A0000;
                        a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                        a2 = 135;
                        jal(ctx, 0x35CD18u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                        a0 = 0;
                        // 0x0035cd24 (the shared epilogue, written out on this path)
                        charge(ctx, 18);
                        lw(v1, task, ofs::insn);
                        lw(v0, task, ofs::pc);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, v1);
                        lh(v0, v0, ofs::operand);  // the s16 operand of insn[pc]
                        v1 = sll(v0, 2);
                        lw(v0, task, ofs::local_ints);
                        v0 = addu(v0, v1);
                        sw(a0, v0, 0);
                        lw(v0, task, ofs::pc);  // pc += 1
                        v0 = addiu(v0, 1);
                        sw(v0, task, ofs::pc);
                        v0 = 1;
                        ld(ra, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x20);
                        return;
                    }
                }
                // 0x0035cc84
                charge(ctx, 5);
                v0 = sll(a0, 2);
                v0 = addu(v0, task);
                lw(a0, v0, ofs::values);
            }
        }
    }
    // 0x0035cd24 (the shared epilogue, written out on this path)
    charge(ctx, 18);
    lw(v1, task, ofs::insn);
    lw(v0, task, ofs::pc);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lh(v0, v0, ofs::operand);  // the s16 operand of insn[pc]
    v1 = sll(v0, 2);
    lw(v0, task, ofs::local_ints);
    v0 = addu(v0, v1);
    sw(a0, v0, 0);
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035CD70 CodeFunc_PopLFX -- 396 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode POPLFX: local_floats[operand] = pop as a float (PopFloat, as CodeFunc_PopFX). pc += 1; returns 1.
// Blocks: entry 7, the pop, store + pc 18.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_PopLFX(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::cvt_s_w, hg::enter, hg::i64, hg::jal, hg::lb,
          hg::ld, hg::lh, hg::lq, hg::lw, hg::lwc1, hg::mtc1, hg::sd, hg::sll, hg::sq, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035cd70
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    lw(v0, a0, ofs::sp);
    if (i64(v0) <= 0) {
        // 0x0035cd8c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 146;
        jal(ctx, 0x35CD98u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035cda0
    charge(ctx, 8);
    // pop: sp -= 1, then the top slot by its tag
    lw(v0, task, ofs::sp);
    a0 = addiu(v0, -1);
    sw(a0, task, ofs::sp);
    v0 = addu(a0, task);
    lb(v1, v0, ofs::tags);
    v0 = kTagGlobalFloat;
    if (v1 == v0) {
        // 0x0035ce70: kTagGlobalFloat
        charge(ctx, 9);
        v0 = sll(a0, 2);
        v0 = addu(v0, task);
        lw(v0, v0, ofs::values);
        v1 = sll(v0, 2);
        lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
        v0 = addu(v0, v1);
        lwc1(f0, v0, ofs::global_floats);
    } else {
        // 0x0035cdc0
        charge(ctx, 3);
        v0 = kTagGlobalInt;
        if (v1 == v0) {
            // 0x0035ce48: kTagGlobalInt
            charge(ctx, 10);
            v0 = sll(a0, 2);
            v0 = addu(v0, task);
            lw(v0, v0, ofs::values);
            v1 = sll(v0, 2);
            lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
            v0 = addu(v0, v1);
            lwc1(f0, v0, 0);
            cvt_s_w(f0, f0);
        } else {
            // 0x0035cdcc
            charge(ctx, 3);
            v0 = kTagFloat;
            if (v1 == v0) {
                // 0x0035ce34: kTagFloat
                charge(ctx, 5);
                v0 = sll(a0, 2);
                v0 = addu(v0, task);
                lwc1(f0, v0, ofs::values);
            } else {
                // 0x0035cdd8
                charge(ctx, 3);
                v0 = kTagReturnAddress;
                if (v1 == v0) {
                    // 0x0035ce0c: kTagReturnAddress
                    charge(ctx, 10);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -11728);  // "PopFloat(..) invalid stack type(RET)!!\n"
                    a1 = 0x6A0000;
                    a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                    a2 = 152;
                    jal(ctx, 0x35CE20u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                    mtc1(zero, f0);
                } else {
                    // 0x0035cde4
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x0035cdf4
                        charge(ctx, 6);
                        v0 = sll(a0, 2);
                        v0 = addu(v0, task);
                        lwc1(f0, v0, ofs::values);
                        cvt_s_w(f0, f0);
                    } else {
                        // 0x0035cdec
                        charge(ctx, 2);
                        // 0x0035ce94
                        charge(ctx, 8);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -11680);  // "PopFloat(..) invalid stack type(?)!!\n"
                        a1 = 0x6A0000;
                        a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                        a2 = 161;
                        jal(ctx, 0x35CEA8u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                        mtc1(zero, f0);
                    }
                }
            }
        }
    }
    // 0x0035ceb4 (the shared epilogue, written out on this path)
    charge(ctx, 18);
    lw(v1, task, ofs::insn);
    lw(v0, task, ofs::pc);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lh(v0, v0, ofs::operand);  // the s16 operand of insn[pc]
    v1 = sll(v0, 2);
    lw(v0, task, ofs::local_floats);
    v0 = addu(v0, v1);
    swc1(f0, v0, 0);
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// --- END / CALL return ------------------------------------------------------------------------------------

// 0x0035D040 CodeFunc_End -- 392 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode END: the end of a procedure. An empty stack (sp == 0 exactly; a negative sp goes on) ends the script:
// returns 0. Otherwise the top slot should be a CALL's return address (assertion 383; a no-op): it is popped as an int
// (PopInt: any tag converts) and the pc becomes that value + 1; returns 1.
// Blocks: entry 7. sp == 0 -> 3 + 5. Otherwise 5, 3, the pop, 4, 5.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_End(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::cvt_w_s, hg::enter, hg::i64, hg::jal, hg::lb,
          hg::ld, hg::lq, hg::lw, hg::lwc1, hg::mfc1, hg::sd, hg::sll, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035d040
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    lw(v0, a0, ofs::sp);
    if (v0 != 0) {
        // 0x0035d068
        charge(ctx, 5);
        v0 = addu(v0, task);
        lb(v1, v0, ofs::tags - 1);
        v0 = kTagReturnAddress;
        if (v1 != v0) {
            // 0x0035d07c: not kTagReturnAddress
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -11800);  // "scrTraceCode.c"
            a1 = 383;
            jal(ctx, 0x35D088u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
        }
        // 0x0035d090
        charge(ctx, 3);
        lw(v0, task, ofs::sp);
        if (i64(v0) <= 0) {
            // 0x0035d09c
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -11800);  // "scrTraceCode.c"
            a1 = 122;
            jal(ctx, 0x35D0A8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
        }
        // 0x0035d0b0
        charge(ctx, 8);
        // pop: sp -= 1, then the top slot by its tag
        lw(v0, task, ofs::sp);
        a0 = addiu(v0, -1);
        sw(a0, task, ofs::sp);
        v0 = addu(a0, task);
        lb(v1, v0, ofs::tags);
        v0 = kTagGlobalFloat;
        if (v1 == v0) {
            // 0x0035d158: kTagGlobalFloat
            charge(ctx, 11);
            v0 = sll(a0, 2);
            v0 = addu(v0, task);
            lw(v0, v0, ofs::values);
            v1 = sll(v0, 2);
            lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
            v0 = addu(v0, v1);
            lwc1(f0, v0, ofs::global_floats);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
        } else {
            // 0x0035d0d0
            charge(ctx, 3);
            v0 = kTagGlobalInt;
            if (v1 == v0) {
                // 0x0035d134: kTagGlobalInt
                charge(ctx, 9);
                v0 = sll(a0, 2);
                v0 = addu(v0, task);
                lw(v0, v0, ofs::values);
                v1 = sll(v0, 2);
                lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
            } else {
                // 0x0035d0dc
                charge(ctx, 3);
                v0 = kTagFloat;
                if (v1 == v0) {
                    // 0x0035d118: kTagFloat
                    charge(ctx, 7);
                    v0 = sll(a0, 2);
                    v0 = addu(v0, task);
                    lwc1(f0, v0, ofs::values);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                } else {
                    // 0x0035d0e8
                    charge(ctx, 3);
                    v0 = kTagReturnAddress;
                    if (v1 != v0) {
                        // 0x0035d0f4: not kTagReturnAddress
                        charge(ctx, 2);
                        if (v1 != 0) {
                            // 0x0035d0fc: an invalid tag
                            charge(ctx, 2);
                            // 0x0035d184
                            charge(ctx, 8);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, -11776);  // "PopInt(..) invalid stack type!!\n"
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                            a2 = 135;
                            jal(ctx, 0x35D198u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                            v0 = 0;
                        } else {
                            // 0x0035d104: kTagInt -- the raw word
                            charge(ctx, 5);
                            v0 = sll(a0, 2);
                            v0 = addu(v0, task);
                            lw(v0, v0, ofs::values);
                        }
                    } else {
                        // 0x0035d104: kTagReturnAddress -- the raw word (the block the int tag shares)
                        charge(ctx, 5);
                        v0 = sll(a0, 2);
                        v0 = addu(v0, task);
                        lw(v0, v0, ofs::values);
                    }
                }
            }
        }
        // 0x0035d1a4: pc = popped value; pc += 1 (the instruction after the CALL)
        charge(ctx, 4);
        sw(v0, task, ofs::pc);
        v0 = addiu(v0, 1);
        sw(v0, task, ofs::pc);
        v0 = 1;
    } else {
        // 0x0035d05c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0035d1b4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// --- unary and binary operations ----------------------------------------------------------------------------

// 0x0035E0E0 CodeFunc_Minus -- 368 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode MINUS: negates the top slot in place, by its tag (floats by neg.s, ints as 0 - x; the global variants
// change the global itself); a return address (line 648) or an invalid tag (662) aborts and changes nothing. Asserts
// sp > 0 (line 642). pc += 1; returns 1.
// Blocks: entry 7, tag block 6, then by tag (3, 2, 1, 4, 0 order): global float 11, global int 11, float 7, return
// address 9 + K_Abort, int 7, unknown 7 + K_Abort; tail 9.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_Minus(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::i64, hg::jal, hg::lb, hg::ld, hg::lq,
          hg::lw, hg::lwc1, hg::neg_s, hg::sd, hg::sll, hg::sq, hg::subu, hg::sw, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035e0e0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    lw(v0, a0, ofs::sp);
    if (i64(v0) <= 0) {
        // 0x0035e0fc
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 642;
        jal(ctx, 0x35E108u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035e110
    charge(ctx, 6);
    lw(a0, task, ofs::sp);
    v0 = addu(a0, task);
    lb(v1, v0, ofs::tags - 1);
    v0 = kTagGlobalFloat;
    if (v1 == v0) {
        // 0x0035e1e4: kTagGlobalFloat
        charge(ctx, 11);
        v0 = sll(a0, 2);
        v0 = addu(v0, task);
        lw(v0, v0, ofs::values - 4);
        v1 = sll(v0, 2);
        lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
        v0 = addu(v0, v1);
        lwc1(f0, v0, ofs::global_floats);
        neg_s(f0, f0);
        swc1(f0, v0, ofs::global_floats);
    } else {
        // 0x0035e128
        charge(ctx, 3);
        v0 = kTagGlobalInt;
        if (v1 == v0) {
            // 0x0035e1b8: kTagGlobalInt
            charge(ctx, 11);
            v0 = sll(a0, 2);
            v0 = addu(v0, task);
            lw(v0, v0, ofs::values - 4);
            v1 = sll(v0, 2);
            lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
            v1 = addu(v0, v1);
            lw(v0, v1, 0);
            v0 = subu(0, v0);
            sw(v0, v1, 0);
        } else {
            // 0x0035e134
            charge(ctx, 3);
            v0 = kTagFloat;
            if (v1 == v0) {
                // 0x0035e19c: kTagFloat
                charge(ctx, 7);
                v0 = sll(a0, 2);
                v0 = addu(v0, task);
                lwc1(f0, v0, ofs::values - 4);
                neg_s(f0, f0);
                swc1(f0, v0, ofs::values - 4);
            } else {
                // 0x0035e140
                charge(ctx, 3);
                v0 = kTagReturnAddress;
                if (v1 == v0) {
                    // 0x0035e178: kTagReturnAddress
                    charge(ctx, 9);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -11584);  // "CodeFunc_Minus(..) invalid stack type(RET)!!\n"
                    a1 = 0x6A0000;
                    a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                    a2 = 648;
                    jal(ctx, 0x35E18Cu, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                } else {
                    // 0x0035e14c
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x0035e15c
                        charge(ctx, 7);
                        v0 = sll(a0, 2);
                        v1 = addu(v0, task);
                        lw(v0, v1, ofs::values - 4);
                        v0 = subu(0, v0);
                        sw(v0, v1, ofs::values - 4);
                    } else {
                        // 0x0035e154
                        charge(ctx, 2);
                        // 0x0035e210
                        charge(ctx, 7);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -11536);  // "CodeFunc_Minus(..) invalid stack type(?)!!\n"
                        a1 = 0x6A0000;
                        a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                        a2 = 662;
                        jal(ctx, 0x35E224u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                    }
                }
            }
        }
    }
    // 0x0035e22c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035E250 CodeFunc_Not -- 1012 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Opcode NOT: pops the top slot and pushes (value == 0) with tag 0 -- floats compared with 0.0 (PopFloat), the
// others as ints (PopInt). A return address (line 696) or an invalid tag (699) aborts and pushes nothing. Asserts
// sp > 0 (line 677). pc += 1; returns 1.
// Blocks: entry 8, tag block 6, chain order 4, 3, 1, 2, 0. A return address 9 + K_Abort; floats 2, pop, 6 [+1 when
// non-zero], 4, push 12; ints 2, pop, 6, push 12; an unknown tag 7 + K_Abort. Tail 10.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_Not(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::c_eq_s, hg::charge, hg::cond, hg::cvt_s_w, hg::cvt_w_s,
          hg::enter, hg::i64, hg::jal, hg::lb, hg::ld, hg::lq, hg::lw, hg::lwc1, hg::mfc1, hg::mtc1, hg::sb, hg::sd,
          hg::sll, hg::slti, hg::sltiu, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    Gpr& task = s1;  // $s1: the ScrTask ($a0 at entry) for the whole body
    // 0x0035e250
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s1
    lw(v0, a0, ofs::sp);
    if (i64(v0) <= 0) {
        // 0x0035e270
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 677;
        jal(ctx, 0x35E27Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035e284
    charge(ctx, 6);
    lw(a0, task, ofs::sp);
    v0 = addu(a0, task);
    lb(v1, v0, ofs::tags - 1);
    v0 = kTagReturnAddress;
    if (v1 == v0) {
        // 0x0035e5dc: kTagReturnAddress
        charge(ctx, 9);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11488);  // "CodeFunc_Not(..) invalid stack type(RET)!!\n"
        a1 = 0x6A0000;
        a1 = addiu(a1, -11800);  // "scrTraceCode.c"
        a2 = 696;
        jal(ctx, 0x35E5F0u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
    } else {
        // 0x0035e29c
        charge(ctx, 3);
        v0 = kTagGlobalFloat;
        if (v1 != v0) {
            // 0x0035e2a8: not kTagGlobalFloat
            charge(ctx, 3);
            v0 = kTagFloat;
            if (v1 != v0) {
                // 0x0035e2b4: not kTagFloat
                charge(ctx, 3);
                v0 = kTagGlobalInt;
                if (v1 != v0) {
                    // 0x0035e2c0: not kTagGlobalInt
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x0035e2c8
                        charge(ctx, 2);
                        // 0x0035e600
                        charge(ctx, 7);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -11440);  // "CodeFunc_Not(..) invalid stack type(?)!!\n"
                        a1 = 0x6A0000;
                        a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                        a2 = 699;
                        jal(ctx, 0x35E614u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                        // 0x0035e61c (the shared epilogue, written out on this path)
                        charge(ctx, 10);
                        lw(v0, task, ofs::pc);  // pc += 1
                        v0 = addiu(v0, 1);
                        sw(v0, task, ofs::pc);
                        v0 = 1;
                        ld(ra, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x30);
                        return;
                    }
                }
                // 0x0035e2d0
                charge(ctx, 2);
                if (i64(a0) <= 0) {
                    // 0x0035e2d8
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -11800);  // "scrTraceCode.c"
                    a1 = 122;
                    jal(ctx, 0x35E2E4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
                }
                // 0x0035e2ec
                charge(ctx, 8);
                // pop: sp -= 1, then the top slot by its tag
                lw(v0, task, ofs::sp);
                a0 = addiu(v0, -1);
                sw(a0, task, ofs::sp);
                v0 = addu(a0, task);
                lb(v1, v0, ofs::tags);
                v0 = kTagGlobalFloat;
                if (v1 == v0) {
                    // 0x0035e394: kTagGlobalFloat
                    charge(ctx, 11);
                    v0 = sll(a0, 2);
                    v0 = addu(v0, task);
                    lw(v0, v0, ofs::values);
                    v1 = sll(v0, 2);
                    lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
                    v0 = addu(v0, v1);
                    lwc1(f0, v0, ofs::global_floats);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                } else {
                    // 0x0035e30c
                    charge(ctx, 3);
                    v0 = kTagGlobalInt;
                    if (v1 == v0) {
                        // 0x0035e370: kTagGlobalInt
                        charge(ctx, 9);
                        v0 = sll(a0, 2);
                        v0 = addu(v0, task);
                        lw(v0, v0, ofs::values);
                        v1 = sll(v0, 2);
                        lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                    } else {
                        // 0x0035e318
                        charge(ctx, 3);
                        v0 = kTagFloat;
                        if (v1 == v0) {
                            // 0x0035e354: kTagFloat
                            charge(ctx, 7);
                            v0 = sll(a0, 2);
                            v0 = addu(v0, task);
                            lwc1(f0, v0, ofs::values);
                            cvt_w_s(f0, f0);
                            mfc1(v0, f0);
                        } else {
                            // 0x0035e324
                            charge(ctx, 3);
                            v0 = kTagReturnAddress;
                            if (v1 != v0) {
                                // 0x0035e330: not kTagReturnAddress
                                charge(ctx, 2);
                                if (v1 != 0) {
                                    // 0x0035e338: an invalid tag
                                    charge(ctx, 2);
                                    // 0x0035e3c0
                                    charge(ctx, 8);
                                    a0 = 0x6A0000;
                                    a0 = addiu(a0, -11776);  // "PopInt(..) invalid stack type!!\n"
                                    a1 = 0x6A0000;
                                    a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                                    a2 = 135;
                                    jal(ctx, 0x35E3D4u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                                    v0 = 0;
                                } else {
                                    // 0x0035e340: kTagInt -- the raw word
                                    charge(ctx, 5);
                                    v0 = sll(a0, 2);
                                    v0 = addu(v0, task);
                                    lw(v0, v0, ofs::values);
                                }
                            } else {
                                // 0x0035e340: kTagReturnAddress -- the raw word (the block the int tag shares)
                                charge(ctx, 5);
                                v0 = sll(a0, 2);
                                v0 = addu(v0, task);
                                lw(v0, v0, ofs::values);
                            }
                        }
                    }
                }
                // 0x0035e3e0: push (popped == 0) with tag 0
                charge(ctx, 6);
                s0 = v0;
                s0 = sltiu(s0, 1);
                lw(v0, task, ofs::sp);
                v0 = slti(v0, kStackSlots);  // a push asserts sp < 27
                if (v0 == 0) {
                    // 0x0035e3f8
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -11800);  // "scrTraceCode.c"
                    a1 = 43;
                    jal(ctx, 0x35E404u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
                }
                // 0x0035e40c
                charge(ctx, 12);
                // push: tags[sp] = tag, values[sp] = value, sp += 1
                lw(v0, task, ofs::sp);
                v0 = addu(v0, task);
                sb(zero, v0, ofs::tags);
                lw(v0, task, ofs::sp);
                v0 = sll(v0, 2);
                v0 = addu(v0, task);
                sw(s0, v0, ofs::values);
                lw(v0, task, ofs::sp);
                v0 = addiu(v0, 1);
                sw(v0, task, ofs::sp);
                // 0x0035e61c (the shared epilogue, written out on this path)
                charge(ctx, 10);
                lw(v0, task, ofs::pc);  // pc += 1
                v0 = addiu(v0, 1);
                sw(v0, task, ofs::pc);
                v0 = 1;
                ld(ra, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x30);
                return;
            }
        }
        // 0x0035e43c
        charge(ctx, 2);
        if (i64(a0) <= 0) {
            // 0x0035e444
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -11800);  // "scrTraceCode.c"
            a1 = 146;
            jal(ctx, 0x35E450u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
        }
        // 0x0035e458
        charge(ctx, 8);
        // pop: sp -= 1, then the top slot by its tag
        lw(v0, task, ofs::sp);
        a0 = addiu(v0, -1);
        sw(a0, task, ofs::sp);
        v0 = addu(a0, task);
        lb(v1, v0, ofs::tags);
        v0 = kTagGlobalFloat;
        if (v1 == v0) {
            // 0x0035e528: kTagGlobalFloat
            charge(ctx, 9);
            v0 = sll(a0, 2);
            v0 = addu(v0, task);
            lw(v0, v0, ofs::values);
            v1 = sll(v0, 2);
            lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
            v0 = addu(v0, v1);
            lwc1(f1, v0, ofs::global_floats);
        } else {
            // 0x0035e478
            charge(ctx, 3);
            v0 = kTagGlobalInt;
            if (v1 == v0) {
                // 0x0035e500: kTagGlobalInt
                charge(ctx, 10);
                v0 = sll(a0, 2);
                v0 = addu(v0, task);
                lw(v0, v0, ofs::values);
                v1 = sll(v0, 2);
                lw(v0, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
                v0 = addu(v0, v1);
                lwc1(f0, v0, 0);
                cvt_s_w(f1, f0);
            } else {
                // 0x0035e484
                charge(ctx, 3);
                v0 = kTagFloat;
                if (v1 == v0) {
                    // 0x0035e4ec: kTagFloat
                    charge(ctx, 5);
                    v0 = sll(a0, 2);
                    v0 = addu(v0, task);
                    lwc1(f1, v0, ofs::values);
                } else {
                    // 0x0035e490
                    charge(ctx, 3);
                    v0 = kTagReturnAddress;
                    if (v1 == v0) {
                        // 0x0035e4c4: kTagReturnAddress
                        charge(ctx, 10);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -11728);  // "PopFloat(..) invalid stack type(RET)!!\n"
                        a1 = 0x6A0000;
                        a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                        a2 = 152;
                        jal(ctx, 0x35E4D8u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                        mtc1(zero, f1);
                    } else {
                        // 0x0035e49c
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x0035e4ac
                            charge(ctx, 6);
                            v0 = sll(a0, 2);
                            v0 = addu(v0, task);
                            lwc1(f0, v0, ofs::values);
                            cvt_s_w(f1, f0);
                        } else {
                            // 0x0035e4a4
                            charge(ctx, 2);
                            // 0x0035e54c
                            charge(ctx, 8);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, -11680);  // "PopFloat(..) invalid stack type(?)!!\n"
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                            a2 = 161;
                            jal(ctx, 0x35E560u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                            mtc1(zero, f1);
                        }
                    }
                }
            }
        }
        // 0x0035e56c
        charge(ctx, 6);
        mtc1(zero, f0);
        c_eq_s(f0, f1);
        s0 = 1;
        if (!cond(ctx)) {
            // 0x0035e584
            charge(ctx, 1);
            s0 = 0;
        }
        // 0x0035e588
        charge(ctx, 4);
        lw(v0, task, ofs::sp);
        v0 = slti(v0, kStackSlots);  // a push asserts sp < 27
        if (v0 == 0) {
            // 0x0035e598
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -11800);  // "scrTraceCode.c"
            a1 = 43;
            jal(ctx, 0x35E5A4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
        }
        // 0x0035e5ac
        charge(ctx, 12);
        // push: tags[sp] = tag, values[sp] = value, sp += 1
        lw(v0, task, ofs::sp);
        v0 = addu(v0, task);
        sb(zero, v0, ofs::tags);
        lw(v0, task, ofs::sp);
        v0 = sll(v0, 2);
        v0 = addu(v0, task);
        sw(s0, v0, ofs::values);
        lw(v0, task, ofs::sp);
        v0 = addiu(v0, 1);
        sw(v0, task, ofs::sp);
    }
    // 0x0035e61c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0035E850 CodeFunc_IF -- 916 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode IF: pops the condition and branches when it is false: pc = jump_labels[operand].insn; true -> pc += 1.
// Floats are tested against 0.0 (PopFloat), the others as ints (PopInt); a return address (line 818) or an invalid tag
// (822) aborts, pops nothing and counts as false. Asserts sp > 0 (line 804). Returns 1.
// Blocks: entry 7, tag block 6, chain order 4, 3, 1, 2, 0: a return address 10 + K_Abort; floats 2, pop, 5, 3; ints
// 2, pop, 2; an unknown tag 8 + K_Abort. Then 2: true -> 5, false -> 10; tail 6.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_IF(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::c_eq_s, hg::charge, hg::cond, hg::cvt_s_w, hg::cvt_w_s,
          hg::enter, hg::i64, hg::jal, hg::lb, hg::ld, hg::lh, hg::lq, hg::lw, hg::lwc1, hg::mfc1, hg::mtc1, hg::sd,
          hg::sll, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body

    // The original's inlined PopInt(): pops the top slot ($a0 = sp on entry) and leaves the condition in $v0 as an
    // int (any tag converts; an invalid one aborts and gives 0). Reached for tags 2 and 0 (0x0035e8cc).
    auto pop_int = [&] {
        charge(ctx, 2);
        if (i64(a0) <= 0) {
            // 0x0035e8d4
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -11800);  // "scrTraceCode.c"
            a1 = 122;
            jal(ctx, 0x35E8E0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
        }
        // 0x0035e8e8
        charge(ctx, 8);
        // pop: sp -= 1, then the top slot by its tag
        lw(v0, task, ofs::sp);
        a0 = addiu(v0, -1);
        sw(a0, task, ofs::sp);
        v0 = addu(a0, task);
        lb(v1, v0, ofs::tags);
        v0 = kTagGlobalFloat;
        if (v1 == v0) {
            // 0x0035e990: kTagGlobalFloat -- (s32) floats[value]
            charge(ctx, 11);
            v0 = sll(a0, 2);
            v0 = addu(v0, task);
            lw(v0, v0, ofs::values);
            v1 = sll(v0, 2);
            lw(v0, gp, ofs::gp_globals);  // g_scrGlobals
            v0 = addu(v0, v1);
            lwc1(f0, v0, ofs::global_floats);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
        } else {
            // 0x0035e908
            charge(ctx, 3);
            v0 = kTagGlobalInt;
            if (v1 == v0) {
                // 0x0035e96c: kTagGlobalInt -- ints[value]
                charge(ctx, 9);
                v0 = sll(a0, 2);
                v0 = addu(v0, task);
                lw(v0, v0, ofs::values);
                v1 = sll(v0, 2);
                lw(v0, gp, ofs::gp_globals);  // g_scrGlobals
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
            } else {
                // 0x0035e914
                charge(ctx, 3);
                v0 = kTagFloat;
                if (v1 == v0) {
                    // 0x0035e950: kTagFloat -- (s32) value
                    charge(ctx, 7);
                    v0 = sll(a0, 2);
                    v0 = addu(v0, task);
                    lwc1(f0, v0, ofs::values);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                } else {
                    // 0x0035e920
                    charge(ctx, 3);
                    v0 = kTagReturnAddress;
                    if (v1 != v0) {
                        // 0x0035e92c: not kTagReturnAddress
                        charge(ctx, 2);
                        if (v1 != 0) {
                            // 0x0035e934: an invalid tag
                            charge(ctx, 2);
                            // 0x0035e9bc
                            charge(ctx, 8);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, -11776);  // "PopInt(..) invalid stack type!!\n"
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                            a2 = 135;
                            jal(ctx, 0x35E9D0u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                            v0 = 0;
                        } else {
                            // 0x0035e93c: kTagInt -- the raw word
                            charge(ctx, 5);
                            v0 = sll(a0, 2);
                            v0 = addu(v0, task);
                            lw(v0, v0, ofs::values);
                        }
                    } else {
                        // 0x0035e93c: kTagReturnAddress -- the raw word (the block the int tag shares)
                        charge(ctx, 5);
                        v0 = sll(a0, 2);
                        v0 = addu(v0, task);
                        lw(v0, v0, ofs::values);
                    }
                }
            }
        }
        // 0x0035e9dc
        charge(ctx, 2);
    };

    // The original's inlined PopFloat() and the test against 0.0: $v0 = (popped != 0.0). Reached for tags 3 and 1
    // (0x0035e9e4).
    auto pop_float = [&] {
        charge(ctx, 2);
        if (i64(a0) <= 0) {
            // 0x0035e9ec
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -11800);  // "scrTraceCode.c"
            a1 = 146;
            jal(ctx, 0x35E9F8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
        }
        // 0x0035ea00
        charge(ctx, 8);
        // pop: sp -= 1, then the top slot by its tag
        lw(v0, task, ofs::sp);
        a0 = addiu(v0, -1);
        sw(a0, task, ofs::sp);
        v0 = addu(a0, task);
        lb(v1, v0, ofs::tags);
        v0 = kTagGlobalFloat;
        if (v1 == v0) {
            // 0x0035ead0: kTagGlobalFloat -- floats[value]
            charge(ctx, 9);
            v0 = sll(a0, 2);
            v0 = addu(v0, task);
            lw(v0, v0, ofs::values);
            v1 = sll(v0, 2);
            lw(v0, gp, ofs::gp_globals);  // g_scrGlobals
            v0 = addu(v0, v1);
            lwc1(f1, v0, ofs::global_floats);
        } else {
            // 0x0035ea20
            charge(ctx, 3);
            v0 = kTagGlobalInt;
            if (v1 == v0) {
                // 0x0035eaa8: kTagGlobalInt -- (f32) ints[value]
                charge(ctx, 10);
                v0 = sll(a0, 2);
                v0 = addu(v0, task);
                lw(v0, v0, ofs::values);
                v1 = sll(v0, 2);
                lw(v0, gp, ofs::gp_globals);  // g_scrGlobals
                v0 = addu(v0, v1);
                lwc1(f0, v0, 0);
                cvt_s_w(f1, f0);
            } else {
                // 0x0035ea2c
                charge(ctx, 3);
                v0 = kTagFloat;
                if (v1 == v0) {
                    // 0x0035ea94: kTagFloat -- the value
                    charge(ctx, 5);
                    v0 = sll(a0, 2);
                    v0 = addu(v0, task);
                    lwc1(f1, v0, ofs::values);
                } else {
                    // 0x0035ea38
                    charge(ctx, 3);
                    v0 = kTagReturnAddress;
                    if (v1 == v0) {
                        // 0x0035ea6c: kTagReturnAddress -- an abort, 0.0
                        charge(ctx, 10);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -11728);  // "PopFloat(..) invalid stack type(RET)!!\n"
                        a1 = 0x6A0000;
                        a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                        a2 = 152;
                        jal(ctx, 0x35EA80u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                        mtc1(zero, f1);
                    } else {
                        // 0x0035ea44
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x0035ea54: kTagInt -- (f32) value
                            charge(ctx, 6);
                            v0 = sll(a0, 2);
                            v0 = addu(v0, task);
                            lwc1(f0, v0, ofs::values);
                            cvt_s_w(f1, f0);
                        } else {
                            // 0x0035ea4c: an invalid tag -- an abort, 0.0
                            charge(ctx, 2);
                            // 0x0035eaf4
                            charge(ctx, 8);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, -11680);  // "PopFloat(..) invalid stack type(?)!!\n"
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                            a2 = 161;
                            jal(ctx, 0x35EB08u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                            mtc1(zero, f1);
                        }
                    }
                }
            }
        }
        // 0x0035eb14: $v0 = (popped != 0.0)
        charge(ctx, 5);
        mtc1(zero, f0);
        c_eq_s(f0, f1);
        if (!cond(ctx)) {
            // 0x0035eb34
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x0035eb28
            charge(ctx, 3);
            v0 = 0;
        }
    };

    // 0x0035e850
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    lw(v0, a0, ofs::sp);
    if (i64(v0) <= 0) {
        // 0x0035e86c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 804;
        jal(ctx, 0x35E878u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035e880: the condition by the top slot's tag (tags[sp - 1])
    charge(ctx, 6);
    lw(a0, task, ofs::sp);
    v0 = addu(a0, task);
    lb(v1, v0, ofs::tags - 1);
    v0 = kTagReturnAddress;
    if (v1 == v0) {
        // 0x0035eb40: kTagReturnAddress -- an abort; false (nothing is popped)
        charge(ctx, 10);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11392);  // "CodeFunc_IF(..) invalid stack type(RET)!!\n"
        a1 = 0x6A0000;
        a1 = addiu(a1, -11800);  // "scrTraceCode.c"
        a2 = 818;
        jal(ctx, 0x35EB54u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
        v0 = 0;
    } else {
        // 0x0035e898
        charge(ctx, 3);
        v0 = kTagGlobalFloat;
        if (v1 == v0) {
            pop_float();  // 0x0035e9e4
        } else {
            // 0x0035e8a4
            charge(ctx, 3);
            v0 = kTagFloat;
            if (v1 == v0) {
                pop_float();  // 0x0035e9e4
            } else {
                // 0x0035e8b0
                charge(ctx, 3);
                v0 = kTagGlobalInt;
                if (v1 != v0) {
                    // 0x0035e8bc: not kTagGlobalInt
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x0035e8c4: an invalid tag -- an abort; false (nothing is popped)
                        charge(ctx, 2);
                        // 0x0035eb68
                        charge(ctx, 8);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -11344);  // "CodeFunc_IF(..) invalid stack type(?)!!\n"
                        a1 = 0x6A0000;
                        a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                        a2 = 822;
                        jal(ctx, 0x35EB7Cu, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                        v0 = 0;
                    } else {
                        pop_int();  // kTagInt: 0x0035e8cc
                    }
                } else {
                    pop_int();  // kTagGlobalInt: 0x0035e8cc
                }
            }
        }
    }
    // 0x0035eb88: false -> pc = jump_labels[operand].insn; true -> pc += 1
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x0035eba4
        charge(ctx, 10);
        lw(v1, task, ofs::insn);
        lw(v0, task, ofs::pc);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lh(v0, v0, ofs::operand);  // the s16 operand of insn[pc]
        v1 = sll(v0, ofs::label_shift);
        lw(v0, task, ofs::jump_labels);
        v0 = addu(v1, v0);
        lw(v0, v0, ofs::label_insn);
        sw(v0, task, ofs::pc);
    } else {
        // 0x0035eb90
        charge(ctx, 5);
        lw(v0, task, ofs::pc);  // pc += 1
        v0 = addiu(v0, 1);
        sw(v0, task, ofs::pc);
    }
    // 0x0035ebcc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035D350 scrOperation -- 3212 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// scrOperation(ScrTask* task /*$a0*/, u32 op /*$a1*/): the binary operators behind ADD .. LE (scr::Op). The top slot
// is the LEFT operand. When both operands are ints or global ints (tags 0 / 2) it pops them as ints, otherwise as
// floats; the operands and the result pass through the scratch words 0x7CE588.. (scr::kOp*), the tags through
// 0x7CE5A0 / 0x7CE5A4. Float ADD / SUB / MUL / DIV push a float (tag 1); every comparison and every int result is
// pushed as an int (tag 0). An op >= 12 computes nothing and pushes the stale result word. Asserts sp >= 2 (line
// 441), a float divisor != 0.0 (527) and an int divisor != 0 (460) -- no-ops in retail, so x / 0 divides. $v0 is
// left as the caller had it.
// Blocks: entry 11, tag block 8, 3 per non-zero tag test; each path: 3 (sp test) + pop + 4 (park) twice, 7 for the
// switch dispatch, the case block(s), the push (5 + check + 12 or 11), epilogue 7.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrOperation(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::c_eq_s, hg::c_le_s, hg::c_lt_s, hg::charge, hg::cond,
          hg::cvt_s_w, hg::cvt_w_s, hg::div, hg::div_s, hg::enter, hg::i64, hg::jal, hg::lb, hg::ld, hg::lq, hg::lw,
          hg::lwc1, hg::mfc1, hg::mflo, hg::mtc1, hg::mul_s, hg::mult, hg::sb, hg::sd, hg::sll, hg::slt, hg::slti,
          hg::sltiu, hg::sq, hg::sub_s, hg::subu, hg::sw, hg::swc1, hg::tail;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body

    // 0x0035dfc0: the epilogue every path that returns normally ends with (the generated body wrote it out on
    // each path).
    auto epilogue = [&] {
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x40);
    };

    // 0x0035df6c: the float path's push -- the float result word (0x7CE59C) with tag 1; reached by ADD / SUB / MUL /
    // DIV and by an op >= 12 (nothing computed: the stale word is pushed).
    auto push_float_result = [&] {
        charge(ctx, 5);
        lwc1(f20, gp, ofs::gp_op_result_float);  // 0x7CE59C
        lw(v1, task, ofs::sp);
        v1 = slti(v1, kStackSlots);  // a push asserts sp < 27
        if (v1 == 0) {
            // 0x0035df80
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -11800);  // "scrTraceCode.c"
            a1 = 55;
            jal(ctx, 0x35DF8Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
        }
        // 0x0035df94
        charge(ctx, 11);
        a0 = kTagFloat;
        // push: tags[sp] = tag, values[sp] = value, sp += 1
        lw(v1, task, ofs::sp);
        v1 = addu(v1, task);
        sb(a0, v1, ofs::tags);
        lw(v1, task, ofs::sp);
        v1 = sll(v1, 2);
        v1 = addu(v1, task);
        swc1(f20, v1, ofs::values);
        lw(v1, task, ofs::sp);
        v1 = addiu(v1, 1);
        sw(v1, task, ofs::sp);
    };

    // 0x0035d850: the float path (a tag other than 0 / 2 on either operand). Pops the LEFT operand (the top) into
    // 0x7CE594 and the right one into 0x7CE598 as floats (the original's inlined PopFloat(): ints converted with
    // cvt.s.w, a return address or an invalid tag aborts and gives 0.0), then the 12-way `jr` table 0x7BA270:
    // ADD / SUB / MUL / DIV push a float (tag 1), OR / AND / EQ / NEQ / S / L / SE / LE push an int (tag 0).
    auto float_path = [&] {
        charge(ctx, 3);
        lw(v1, task, ofs::sp);
        if (i64(v1) <= 0) {
            // 0x0035d85c
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -11800);  // "scrTraceCode.c"
            a1 = 146;
            jal(ctx, 0x35D868u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
        }
        // 0x0035d870: pop the LEFT operand (the top slot) as a float into $f0
        charge(ctx, 8);
        lw(v1, task, ofs::sp);
        a1 = addiu(v1, -1);
        sw(a1, task, ofs::sp);
        v1 = addu(a1, task);
        lb(a0, v1, ofs::tags);
        v1 = kTagGlobalFloat;
        if (a0 == v1) {
            // 0x0035d940: kTagGlobalFloat
            charge(ctx, 9);
            v1 = sll(a1, 2);
            v1 = addu(v1, task);
            lw(v1, v1, ofs::values);
            a0 = sll(v1, 2);
            lw(v1, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
            v1 = addu(v1, a0);
            lwc1(f0, v1, ofs::global_floats);
        } else {
            // 0x0035d890
            charge(ctx, 3);
            v1 = kTagGlobalInt;
            if (a0 == v1) {
                // 0x0035d918: kTagGlobalInt
                charge(ctx, 10);
                v1 = sll(a1, 2);
                v1 = addu(v1, task);
                lw(v1, v1, ofs::values);
                a0 = sll(v1, 2);
                lw(v1, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
                v1 = addu(v1, a0);
                lwc1(f0, v1, 0);
                cvt_s_w(f0, f0);
            } else {
                // 0x0035d89c
                charge(ctx, 3);
                v1 = kTagFloat;
                if (a0 == v1) {
                    // 0x0035d904: kTagFloat
                    charge(ctx, 5);
                    v1 = sll(a1, 2);
                    v1 = addu(v1, task);
                    lwc1(f0, v1, ofs::values);
                } else {
                    // 0x0035d8a8
                    charge(ctx, 3);
                    v1 = kTagReturnAddress;
                    if (a0 == v1) {
                        // 0x0035d8dc: kTagReturnAddress
                        charge(ctx, 10);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -11728);  // "PopFloat(..) invalid stack type(RET)!!\n"
                        a1 = 0x6A0000;
                        a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                        a2 = 152;
                        jal(ctx, 0x35D8F0u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                        mtc1(zero, f0);
                    } else {
                        // 0x0035d8b4
                        charge(ctx, 2);
                        if (a0 == 0) {
                            // 0x0035d8c4
                            charge(ctx, 6);
                            v1 = sll(a1, 2);
                            v1 = addu(v1, task);
                            lwc1(f0, v1, ofs::values);
                            cvt_s_w(f0, f0);
                        } else {
                            // 0x0035d8bc
                            charge(ctx, 2);
                            // 0x0035d964
                            charge(ctx, 8);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, -11680);  // "PopFloat(..) invalid stack type(?)!!\n"
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                            a2 = 161;
                            jal(ctx, 0x35D978u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                            mtc1(zero, f0);
                        }
                    }
                }
            }
        }
        // 0x0035d984: left -> 0x7CE594; pop the right operand as a float into $f2
        charge(ctx, 4);
        swc1(f0, gp, ofs::gp_op_lhs_float);  // 0x7CE594
        lw(v1, task, ofs::sp);
        if (i64(v1) <= 0) {
            // 0x0035d994
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -11800);  // "scrTraceCode.c"
            a1 = 146;
            jal(ctx, 0x35D9A0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
        }
        // 0x0035d9a8
        charge(ctx, 8);
        lw(v1, task, ofs::sp);
        a1 = addiu(v1, -1);
        sw(a1, task, ofs::sp);
        v1 = addu(a1, task);
        lb(a0, v1, ofs::tags);
        v1 = kTagGlobalFloat;
        if (a0 == v1) {
            // 0x0035da78: kTagGlobalFloat
            charge(ctx, 9);
            v1 = sll(a1, 2);
            v1 = addu(v1, task);
            lw(v1, v1, ofs::values);
            a0 = sll(v1, 2);
            lw(v1, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
            v1 = addu(v1, a0);
            lwc1(f2, v1, ofs::global_floats);
        } else {
            // 0x0035d9c8
            charge(ctx, 3);
            v1 = kTagGlobalInt;
            if (a0 == v1) {
                // 0x0035da50: kTagGlobalInt
                charge(ctx, 10);
                v1 = sll(a1, 2);
                v1 = addu(v1, task);
                lw(v1, v1, ofs::values);
                a0 = sll(v1, 2);
                lw(v1, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
                v1 = addu(v1, a0);
                lwc1(f0, v1, 0);
                cvt_s_w(f2, f0);
            } else {
                // 0x0035d9d4
                charge(ctx, 3);
                v1 = kTagFloat;
                if (a0 == v1) {
                    // 0x0035da3c: kTagFloat
                    charge(ctx, 5);
                    v1 = sll(a1, 2);
                    v1 = addu(v1, task);
                    lwc1(f2, v1, ofs::values);
                } else {
                    // 0x0035d9e0
                    charge(ctx, 3);
                    v1 = kTagReturnAddress;
                    if (a0 == v1) {
                        // 0x0035da14: kTagReturnAddress
                        charge(ctx, 10);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -11728);  // "PopFloat(..) invalid stack type(RET)!!\n"
                        a1 = 0x6A0000;
                        a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                        a2 = 152;
                        jal(ctx, 0x35DA28u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                        mtc1(zero, f2);
                    } else {
                        // 0x0035d9ec
                        charge(ctx, 2);
                        if (a0 == 0) {
                            // 0x0035d9fc
                            charge(ctx, 6);
                            v1 = sll(a1, 2);
                            v1 = addu(v1, task);
                            lwc1(f0, v1, ofs::values);
                            cvt_s_w(f2, f0);
                        } else {
                            // 0x0035d9f4
                            charge(ctx, 2);
                            // 0x0035da9c
                            charge(ctx, 8);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, -11680);  // "PopFloat(..) invalid stack type(?)!!\n"
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                            a2 = 161;
                            jal(ctx, 0x35DAB0u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                            mtc1(zero, f2);
                        }
                    }
                }
            }
        }
        // 0x0035dabc: right -> 0x7CE598; op < 12 -> the `jr` table 0x7BA270
        charge(ctx, 4);
        swc1(f2, gp, ofs::gp_op_rhs_float);  // 0x7CE598
        at = sltiu(s1, 12);
        if (at != 0) {
            // 0x0035dacc
            charge(ctx, 7);
            a0 = 0x7C0000;
            a0 = addiu(a0, -23952);  // &0x7BA270
            v1 = sll(s1, 2);
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
            switch (v1.u()) {
            case 0x35DAE8u:  // table[0]: ADD: lhs + rhs
                // 0x0035dae8
                charge(ctx, 5);
                lwc1(f0, gp, ofs::gp_op_lhs_float);  // 0x7CE594
                add_s(f0, f0, f2);
                swc1(f0, gp, ofs::gp_op_result_float);  // 0x7CE59C
                push_float_result();  // 0x0035df6c
                break;
            case 0x35DAFCu:  // table[1]: SUB: lhs - rhs
                // 0x0035dafc
                charge(ctx, 5);
                lwc1(f0, gp, ofs::gp_op_lhs_float);  // 0x7CE594
                sub_s(f0, f0, f2);
                swc1(f0, gp, ofs::gp_op_result_float);  // 0x7CE59C
                push_float_result();  // 0x0035df6c
                break;
            case 0x35DB10u:  // table[2]: MUL: lhs * rhs
                // 0x0035db10
                charge(ctx, 5);
                lwc1(f0, gp, ofs::gp_op_lhs_float);  // 0x7CE594
                mul_s(f0, f0, f2);
                swc1(f0, gp, ofs::gp_op_result_float);  // 0x7CE59C
                push_float_result();  // 0x0035df6c
                break;
            case 0x35DB24u:  // table[3]: DIV: lhs / rhs
                // 0x0035db24
                charge(ctx, 5);
                mtc1(zero, f0);
                c_eq_s(f0, f2);
                if (cond(ctx)) {
                    // 0x0035db38
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -11800);  // "scrTraceCode.c"
                    a1 = 527;
                    jal(ctx, 0x35DB44u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
                }
                // 0x0035db4c
                charge(ctx, 8);
                lwc1(f1, gp, ofs::gp_op_lhs_float);  // 0x7CE594
                lwc1(f0, gp, ofs::gp_op_rhs_float);  // 0x7CE598
                div_s(f0, f1, f0);
                swc1(f0, gp, ofs::gp_op_result_float);  // 0x7CE59C
                push_float_result();  // 0x0035df6c
                break;
            case 0x35DB6Cu:  // table[4]: OR -- result = (lhs != 0.0 || rhs != 0.0)
                // 0x0035db6c
                charge(ctx, 5);
                mtc1(zero, f1);
                lwc1(f0, gp, ofs::gp_op_lhs_float);  // 0x7CE594
                c_eq_s(f1, f0);
                if (cond(ctx)) {
                    // 0x0035db80: lhs == 0.0
                    charge(ctx, 3);
                    c_eq_s(f1, f2);
                    if (cond(ctx)) {
                        // 0x0035db9c: rhs == 0.0 too -- false
                        charge(ctx, 1);
                        sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                    } else {
                        // 0x0035db8c: true
                        charge(ctx, 4);
                        v1 = 1;
                        sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                    }
                } else {
                    // 0x0035db8c: true (the block the rhs test shares)
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                }
                // 0x0035dba0: push the int result
                charge(ctx, 5);
                lw(s1, gp, ofs::gp_op_result_int);  // 0x7CE590
                lw(v1, task, ofs::sp);
                v1 = slti(v1, kStackSlots);  // a push asserts sp < 27
                if (v1 == 0) {
                    // 0x0035dbb4
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -11800);  // "scrTraceCode.c"
                    a1 = 43;
                    jal(ctx, 0x35DBC0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
                }
                // 0x0035dbc8
                charge(ctx, 12);
                // push: tags[sp] = tag, values[sp] = value, sp += 1
                lw(v1, task, ofs::sp);
                v1 = addu(v1, task);
                sb(zero, v1, ofs::tags);
                lw(v1, task, ofs::sp);
                v1 = sll(v1, 2);
                v1 = addu(v1, task);
                sw(s1, v1, ofs::values);
                lw(v1, task, ofs::sp);
                v1 = addiu(v1, 1);
                sw(v1, task, ofs::sp);
                break;
            case 0x35DBF8u:  // table[5]: AND -- result = (lhs != 0.0 && rhs != 0.0)
                // 0x0035dbf8
                charge(ctx, 5);
                mtc1(zero, f1);
                lwc1(f0, gp, ofs::gp_op_lhs_float);  // 0x7CE594
                c_eq_s(f1, f0);
                if (!cond(ctx)) {
                    // 0x0035dc0c: lhs != 0.0
                    charge(ctx, 3);
                    c_eq_s(f1, f2);
                    if (!cond(ctx)) {
                        // 0x0035dc18: rhs != 0.0 too -- true
                        charge(ctx, 4);
                        v1 = 1;
                        sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                    } else {
                        // 0x0035dc28: false
                        charge(ctx, 1);
                        sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                    }
                } else {
                    // 0x0035dc28: false (the block the rhs test shares)
                    charge(ctx, 1);
                    sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                }
                // 0x0035dc2c: push the int result
                charge(ctx, 5);
                lw(s1, gp, ofs::gp_op_result_int);  // 0x7CE590
                lw(v1, task, ofs::sp);
                v1 = slti(v1, kStackSlots);  // a push asserts sp < 27
                if (v1 == 0) {
                    // 0x0035dc40
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -11800);  // "scrTraceCode.c"
                    a1 = 43;
                    jal(ctx, 0x35DC4Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
                }
                // 0x0035dc54
                charge(ctx, 12);
                // push: tags[sp] = tag, values[sp] = value, sp += 1
                lw(v1, task, ofs::sp);
                v1 = addu(v1, task);
                sb(zero, v1, ofs::tags);
                lw(v1, task, ofs::sp);
                v1 = sll(v1, 2);
                v1 = addu(v1, task);
                sw(s1, v1, ofs::values);
                lw(v1, task, ofs::sp);
                v1 = addiu(v1, 1);
                sw(v1, task, ofs::sp);
                break;
            case 0x35DC84u:  // table[6]: EQ: lhs == rhs
                // 0x0035dc84
                charge(ctx, 4);
                lwc1(f0, gp, ofs::gp_op_lhs_float);  // 0x7CE594
                c_eq_s(f0, f2);
                if (!cond(ctx)) {
                    // 0x0035dca4
                    charge(ctx, 1);
                    sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                } else {
                    // 0x0035dc94
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                }
                // 0x0035dca8
                charge(ctx, 5);
                lw(s1, gp, ofs::gp_op_result_int);  // 0x7CE590
                lw(v1, task, ofs::sp);
                v1 = slti(v1, kStackSlots);  // a push asserts sp < 27
                if (v1 == 0) {
                    // 0x0035dcbc
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -11800);  // "scrTraceCode.c"
                    a1 = 43;
                    jal(ctx, 0x35DCC8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
                }
                // 0x0035dcd0
                charge(ctx, 12);
                // push: tags[sp] = tag, values[sp] = value, sp += 1
                lw(v1, task, ofs::sp);
                v1 = addu(v1, task);
                sb(zero, v1, ofs::tags);
                lw(v1, task, ofs::sp);
                v1 = sll(v1, 2);
                v1 = addu(v1, task);
                sw(s1, v1, ofs::values);
                lw(v1, task, ofs::sp);
                v1 = addiu(v1, 1);
                sw(v1, task, ofs::sp);
                break;
            case 0x35DD00u:  // table[7]: NEQ: lhs != rhs
                // 0x0035dd00
                charge(ctx, 4);
                lwc1(f0, gp, ofs::gp_op_lhs_float);  // 0x7CE594
                c_eq_s(f0, f2);
                if (cond(ctx)) {
                    // 0x0035dd20
                    charge(ctx, 1);
                    sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                } else {
                    // 0x0035dd10
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                }
                // 0x0035dd24
                charge(ctx, 5);
                lw(s1, gp, ofs::gp_op_result_int);  // 0x7CE590
                lw(v1, task, ofs::sp);
                v1 = slti(v1, kStackSlots);  // a push asserts sp < 27
                if (v1 == 0) {
                    // 0x0035dd38
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -11800);  // "scrTraceCode.c"
                    a1 = 43;
                    jal(ctx, 0x35DD44u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
                }
                // 0x0035dd4c
                charge(ctx, 12);
                // push: tags[sp] = tag, values[sp] = value, sp += 1
                lw(v1, task, ofs::sp);
                v1 = addu(v1, task);
                sb(zero, v1, ofs::tags);
                lw(v1, task, ofs::sp);
                v1 = sll(v1, 2);
                v1 = addu(v1, task);
                sw(s1, v1, ofs::values);
                lw(v1, task, ofs::sp);
                v1 = addiu(v1, 1);
                sw(v1, task, ofs::sp);
                break;
            case 0x35DD7Cu:  // table[8]: S: lhs < rhs
                // 0x0035dd7c
                charge(ctx, 4);
                lwc1(f0, gp, ofs::gp_op_lhs_float);  // 0x7CE594
                c_lt_s(f0, f2);
                if (!cond(ctx)) {
                    // 0x0035dd9c
                    charge(ctx, 1);
                    sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                } else {
                    // 0x0035dd8c
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                }
                // 0x0035dda0
                charge(ctx, 5);
                lw(s1, gp, ofs::gp_op_result_int);  // 0x7CE590
                lw(v1, task, ofs::sp);
                v1 = slti(v1, kStackSlots);  // a push asserts sp < 27
                if (v1 == 0) {
                    // 0x0035ddb4
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -11800);  // "scrTraceCode.c"
                    a1 = 43;
                    jal(ctx, 0x35DDC0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
                }
                // 0x0035ddc8
                charge(ctx, 12);
                // push: tags[sp] = tag, values[sp] = value, sp += 1
                lw(v1, task, ofs::sp);
                v1 = addu(v1, task);
                sb(zero, v1, ofs::tags);
                lw(v1, task, ofs::sp);
                v1 = sll(v1, 2);
                v1 = addu(v1, task);
                sw(s1, v1, ofs::values);
                lw(v1, task, ofs::sp);
                v1 = addiu(v1, 1);
                sw(v1, task, ofs::sp);
                break;
            case 0x35DDF8u:  // table[9]: L: lhs > rhs
                // 0x0035ddf8
                charge(ctx, 4);
                lwc1(f0, gp, ofs::gp_op_lhs_float);  // 0x7CE594
                c_le_s(f0, f2);
                if (cond(ctx)) {
                    // 0x0035de18
                    charge(ctx, 1);
                    sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                } else {
                    // 0x0035de08
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                }
                // 0x0035de1c
                charge(ctx, 5);
                lw(s1, gp, ofs::gp_op_result_int);  // 0x7CE590
                lw(v1, task, ofs::sp);
                v1 = slti(v1, kStackSlots);  // a push asserts sp < 27
                if (v1 == 0) {
                    // 0x0035de30
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -11800);  // "scrTraceCode.c"
                    a1 = 43;
                    jal(ctx, 0x35DE3Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
                }
                // 0x0035de44
                charge(ctx, 12);
                // push: tags[sp] = tag, values[sp] = value, sp += 1
                lw(v1, task, ofs::sp);
                v1 = addu(v1, task);
                sb(zero, v1, ofs::tags);
                lw(v1, task, ofs::sp);
                v1 = sll(v1, 2);
                v1 = addu(v1, task);
                sw(s1, v1, ofs::values);
                lw(v1, task, ofs::sp);
                v1 = addiu(v1, 1);
                sw(v1, task, ofs::sp);
                break;
            case 0x35DE74u:  // table[10]: SE: lhs <= rhs
                // 0x0035de74
                charge(ctx, 4);
                lwc1(f0, gp, ofs::gp_op_lhs_float);  // 0x7CE594
                c_le_s(f0, f2);
                if (!cond(ctx)) {
                    // 0x0035de94
                    charge(ctx, 1);
                    sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                } else {
                    // 0x0035de84
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                }
                // 0x0035de98
                charge(ctx, 5);
                lw(s1, gp, ofs::gp_op_result_int);  // 0x7CE590
                lw(v1, task, ofs::sp);
                v1 = slti(v1, kStackSlots);  // a push asserts sp < 27
                if (v1 == 0) {
                    // 0x0035deac
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -11800);  // "scrTraceCode.c"
                    a1 = 43;
                    jal(ctx, 0x35DEB8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
                }
                // 0x0035dec0
                charge(ctx, 12);
                // push: tags[sp] = tag, values[sp] = value, sp += 1
                lw(v1, task, ofs::sp);
                v1 = addu(v1, task);
                sb(zero, v1, ofs::tags);
                lw(v1, task, ofs::sp);
                v1 = sll(v1, 2);
                v1 = addu(v1, task);
                sw(s1, v1, ofs::values);
                lw(v1, task, ofs::sp);
                v1 = addiu(v1, 1);
                sw(v1, task, ofs::sp);
                break;
            case 0x35DEF0u:  // table[11]: LE: lhs >= rhs
                // 0x0035def0
                charge(ctx, 4);
                lwc1(f0, gp, ofs::gp_op_lhs_float);  // 0x7CE594
                c_lt_s(f0, f2);
                if (cond(ctx)) {
                    // 0x0035df10
                    charge(ctx, 1);
                    sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                } else {
                    // 0x0035df00
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                }
                // 0x0035df14
                charge(ctx, 5);
                lw(s1, gp, ofs::gp_op_result_int);  // 0x7CE590
                lw(v1, task, ofs::sp);
                v1 = slti(v1, kStackSlots);  // a push asserts sp < 27
                if (v1 == 0) {
                    // 0x0035df28
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -11800);  // "scrTraceCode.c"
                    a1 = 43;
                    jal(ctx, 0x35DF34u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
                }
                // 0x0035df3c
                charge(ctx, 12);
                // push: tags[sp] = tag, values[sp] = value, sp += 1
                lw(v1, task, ofs::sp);
                v1 = addu(v1, task);
                sb(zero, v1, ofs::tags);
                lw(v1, task, ofs::sp);
                v1 = sll(v1, 2);
                v1 = addu(v1, task);
                sw(s1, v1, ofs::values);
                lw(v1, task, ofs::sp);
                v1 = addiu(v1, 1);
                sw(v1, task, ofs::sp);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
            epilogue();  // 0x0035dfc0
            return;
        }
        // op >= 12: no operation; the stale float result is pushed
        push_float_result();  // 0x0035df6c
        epilogue();  // 0x0035dfc0
    };

    // 0x0035d3d4: the int path (both tags 0 or 2). Pops the left operand into 0x7CE588 and the right one into
    // 0x7CE58C as ints (the inlined PopInt(): floats converted with cvt.w.s, tag 4 read raw, an invalid tag
    // aborts and gives 0), then the `jr` table 0x7BA2A0; every result is pushed as an int (tag 0). An op >= 12
    // pushes the stale int result word.
    auto int_path = [&] {
        charge(ctx, 3);
        lw(v1, task, ofs::sp);
        if (i64(v1) <= 0) {
            // 0x0035d3e0
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -11800);  // "scrTraceCode.c"
            a1 = 122;
            jal(ctx, 0x35D3ECu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
        }
        // 0x0035d3f4: pop the LEFT operand (the top slot) as an int into $v1
        charge(ctx, 8);
        lw(v1, task, ofs::sp);
        a1 = addiu(v1, -1);
        sw(a1, task, ofs::sp);
        v1 = addu(a1, task);
        lb(a0, v1, ofs::tags);
        v1 = kTagGlobalFloat;
        if (a0 == v1) {
            // 0x0035d49c: kTagGlobalFloat
            charge(ctx, 11);
            v1 = sll(a1, 2);
            v1 = addu(v1, task);
            lw(v1, v1, ofs::values);
            a0 = sll(v1, 2);
            lw(v1, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
            v1 = addu(v1, a0);
            lwc1(f0, v1, ofs::global_floats);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
        } else {
            // 0x0035d414
            charge(ctx, 3);
            v1 = kTagGlobalInt;
            if (a0 == v1) {
                // 0x0035d478: kTagGlobalInt
                charge(ctx, 9);
                v1 = sll(a1, 2);
                v1 = addu(v1, task);
                lw(v1, v1, ofs::values);
                a0 = sll(v1, 2);
                lw(v1, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
            } else {
                // 0x0035d420
                charge(ctx, 3);
                v1 = kTagFloat;
                if (a0 == v1) {
                    // 0x0035d45c: kTagFloat
                    charge(ctx, 7);
                    v1 = sll(a1, 2);
                    v1 = addu(v1, task);
                    lwc1(f0, v1, ofs::values);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                } else {
                    // 0x0035d42c
                    charge(ctx, 3);
                    v1 = kTagReturnAddress;
                    if (a0 != v1) {
                        // 0x0035d438: not kTagReturnAddress
                        charge(ctx, 2);
                        if (a0 != 0) {
                            // 0x0035d440: an invalid tag -- an abort, 0
                            charge(ctx, 2);
                            // 0x0035d4c8
                            charge(ctx, 8);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, -11776);  // "PopInt(..) invalid stack type!!\n"
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                            a2 = 135;
                            jal(ctx, 0x35D4DCu, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                            v1 = 0;
                        } else {
                            // 0x0035d448: kTagInt -- the raw word
                            charge(ctx, 5);
                            v1 = sll(a1, 2);
                            v1 = addu(v1, task);
                            lw(v1, v1, ofs::values);
                        }
                    } else {
                        // 0x0035d448: kTagReturnAddress -- the raw word (the block the int tag shares)
                        charge(ctx, 5);
                        v1 = sll(a1, 2);
                        v1 = addu(v1, task);
                        lw(v1, v1, ofs::values);
                    }
                }
            }
        }
        // 0x0035d4e8: the left operand -> 0x7CE588; pop the right operand
        charge(ctx, 4);
        sw(v1, gp, ofs::gp_op_lhs_int);  // 0x7CE588
        lw(v1, task, ofs::sp);
        if (i64(v1) <= 0) {
            // 0x0035d4f8
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -11800);  // "scrTraceCode.c"
            a1 = 122;
            jal(ctx, 0x35D504u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
        }
        // 0x0035d50c: pop the right operand as an int into $a1
        charge(ctx, 8);
        lw(v1, task, ofs::sp);
        a1 = addiu(v1, -1);
        sw(a1, task, ofs::sp);
        v1 = addu(a1, task);
        lb(a0, v1, ofs::tags);
        v1 = kTagGlobalFloat;
        if (a0 == v1) {
            // 0x0035d5b4: kTagGlobalFloat
            charge(ctx, 11);
            v1 = sll(a1, 2);
            v1 = addu(v1, task);
            lw(v1, v1, ofs::values);
            a0 = sll(v1, 2);
            lw(v1, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
            v1 = addu(v1, a0);
            lwc1(f0, v1, ofs::global_floats);
            cvt_w_s(f0, f0);
            mfc1(a1, f0);
        } else {
            // 0x0035d52c
            charge(ctx, 3);
            v1 = kTagGlobalInt;
            if (a0 == v1) {
                // 0x0035d590: kTagGlobalInt
                charge(ctx, 9);
                v1 = sll(a1, 2);
                v1 = addu(v1, task);
                lw(v1, v1, ofs::values);
                a0 = sll(v1, 2);
                lw(v1, gp, ofs::gp_globals);  // g_scrGlobals (ints; floats at + 1024)
                v1 = addu(v1, a0);
                lw(a1, v1, 0);
            } else {
                // 0x0035d538
                charge(ctx, 3);
                v1 = kTagFloat;
                if (a0 == v1) {
                    // 0x0035d574: kTagFloat
                    charge(ctx, 7);
                    v1 = sll(a1, 2);
                    v1 = addu(v1, task);
                    lwc1(f0, v1, ofs::values);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                } else {
                    // 0x0035d544
                    charge(ctx, 3);
                    v1 = kTagReturnAddress;
                    if (a0 != v1) {
                        // 0x0035d550: not kTagReturnAddress
                        charge(ctx, 2);
                        if (a0 != 0) {
                            // 0x0035d558: an invalid tag -- an abort, 0
                            charge(ctx, 2);
                            // 0x0035d5e0
                            charge(ctx, 8);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, -11776);  // "PopInt(..) invalid stack type!!\n"
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                            a2 = 135;
                            jal(ctx, 0x35D5F4u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                            a1 = 0;
                        } else {
                            // 0x0035d560: kTagInt -- the raw word
                            charge(ctx, 5);
                            v1 = sll(a1, 2);
                            v1 = addu(v1, task);
                            lw(a1, v1, ofs::values);
                        }
                    } else {
                        // 0x0035d560: kTagReturnAddress -- the raw word (the block the int tag shares)
                        charge(ctx, 5);
                        v1 = sll(a1, 2);
                        v1 = addu(v1, task);
                        lw(a1, v1, ofs::values);
                    }
                }
            }
        }
        // 0x0035d600: the right operand -> 0x7CE58C; dispatch on op through the `jr` table 0x7BA2A0
        charge(ctx, 4);
        sw(a1, gp, ofs::gp_op_rhs_int);  // 0x7CE58C
        at = sltiu(s1, 12);
        if (at != 0) {
            // 0x0035d610
            charge(ctx, 7);
            a0 = 0x7C0000;
            a0 = addiu(a0, -23904);  // &0x7BA2A0
            v1 = sll(s1, 2);
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
            switch (v1.u()) {
            case 0x35D62Cu:  // table[0]: ADD: lhs + rhs
                // 0x0035d62c
                charge(ctx, 5);
                lw(v1, gp, ofs::gp_op_lhs_int);  // 0x7CE588
                v1 = addu(v1, a1);
                sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                break;
            case 0x35D640u:  // table[1]: SUB: lhs - rhs
                // 0x0035d640
                charge(ctx, 5);
                lw(v1, gp, ofs::gp_op_lhs_int);  // 0x7CE588
                v1 = subu(v1, a1);
                sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                break;
            case 0x35D654u:  // table[2]: MUL: lhs * rhs
                // 0x0035d654
                charge(ctx, 5);
                lw(v1, gp, ofs::gp_op_lhs_int);  // 0x7CE588
                mult(v1, v1, a1);
                sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                break;
            case 0x35D668u:  // table[3]: DIV: lhs / rhs
                // 0x0035d668
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x0035d670
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -11800);  // "scrTraceCode.c"
                    a1 = 460;
                    jal(ctx, 0x35D67Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
                }
                // 0x0035d684
                charge(ctx, 7);
                lw(a0, gp, ofs::gp_op_lhs_int);  // 0x7CE588
                lw(v1, gp, ofs::gp_op_rhs_int);  // 0x7CE58C
                div(a0, v1);
                mflo(v1);
                sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                break;
            case 0x35D6A0u:  // table[4]: OR -- result = (lhs != 0 || rhs != 0)
                // 0x0035d6a0
                charge(ctx, 3);
                lw(v1, gp, ofs::gp_op_lhs_int);  // 0x7CE588
                if (v1 == 0) {
                    // 0x0035d6ac: lhs == 0
                    charge(ctx, 2);
                    if (a1 == 0) {
                        // 0x0035d6c4: rhs == 0 too -- false
                        charge(ctx, 3);
                        sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                        break;
                    }
                }
                // 0x0035d6b4: true
                charge(ctx, 4);
                v1 = 1;
                sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                break;
            case 0x35D6D0u:  // table[5]: AND -- result = (lhs != 0 && rhs != 0)
                // 0x0035d6d0
                charge(ctx, 3);
                lw(v1, gp, ofs::gp_op_lhs_int);  // 0x7CE588
                if (v1 != 0) {
                    // 0x0035d6dc: lhs != 0
                    charge(ctx, 2);
                    if (a1 != 0) {
                        // 0x0035d6e4: rhs != 0 too -- true
                        charge(ctx, 4);
                        v1 = 1;
                        sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                        break;
                    }
                }
                // 0x0035d6f4: false
                charge(ctx, 3);
                sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                break;
            case 0x35D700u:  // table[6]: EQ: lhs == rhs
                // 0x0035d700
                charge(ctx, 3);
                lw(v1, gp, ofs::gp_op_lhs_int);  // 0x7CE588
                if (v1 != a1) {
                    // 0x0035d71c
                    charge(ctx, 3);
                    sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                } else {
                    // 0x0035d70c
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                }
                break;
            case 0x35D728u:  // table[7]: NEQ: lhs != rhs
                // 0x0035d728
                charge(ctx, 3);
                lw(v1, gp, ofs::gp_op_lhs_int);  // 0x7CE588
                if (v1 == a1) {
                    // 0x0035d744
                    charge(ctx, 3);
                    sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                } else {
                    // 0x0035d734
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                }
                break;
            case 0x35D750u:  // table[8]: S: lhs < rhs
                // 0x0035d750
                charge(ctx, 4);
                lw(v1, gp, ofs::gp_op_lhs_int);  // 0x7CE588
                at = slt(v1, a1);
                if (at == 0) {
                    // 0x0035d770
                    charge(ctx, 3);
                    sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                } else {
                    // 0x0035d760
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                }
                break;
            case 0x35D77Cu:  // table[9]: L: lhs > rhs
                // 0x0035d77c
                charge(ctx, 4);
                lw(v1, gp, ofs::gp_op_lhs_int);  // 0x7CE588
                at = slt(a1, v1);
                if (at == 0) {
                    // 0x0035d79c
                    charge(ctx, 3);
                    sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                } else {
                    // 0x0035d78c
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                }
                break;
            case 0x35D7A8u:  // table[10]: SE: lhs <= rhs
                // 0x0035d7a8
                charge(ctx, 4);
                lw(v1, gp, ofs::gp_op_lhs_int);  // 0x7CE588
                at = slt(a1, v1);
                if (at != 0) {
                    // 0x0035d7c8
                    charge(ctx, 3);
                    sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                } else {
                    // 0x0035d7b8
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                }
                break;
            case 0x35D7D4u:  // table[11]: LE: lhs >= rhs
                // 0x0035d7d4
                charge(ctx, 4);
                lw(v1, gp, ofs::gp_op_lhs_int);  // 0x7CE588
                v1 = slt(v1, a1);
                if (v1 != 0) {
                    // 0x0035d7f4
                    charge(ctx, 1);
                    sw(zero, gp, ofs::gp_op_result_int);  // 0x7CE590
                } else {
                    // 0x0035d7e4
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, gp, ofs::gp_op_result_int);  // 0x7CE590
                }
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
        }
        // 0x0035d7f8: push the int result word (0x7CE590) with tag 0 (an op >= 12 pushes it stale)
        charge(ctx, 5);
        lw(s1, gp, ofs::gp_op_result_int);  // 0x7CE590
        lw(v1, task, ofs::sp);
        v1 = slti(v1, kStackSlots);  // a push asserts sp < 27
        if (v1 == 0) {
            // 0x0035d80c
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -11800);  // "scrTraceCode.c"
            a1 = 43;
            jal(ctx, 0x35D818u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
        }
        // 0x0035d820
        charge(ctx, 12);
        // push: tags[sp] = tag, values[sp] = value, sp += 1
        lw(v1, task, ofs::sp);
        v1 = addu(v1, task);
        sb(zero, v1, ofs::tags);
        lw(v1, task, ofs::sp);
        v1 = sll(v1, 2);
        v1 = addu(v1, task);
        sw(s1, v1, ofs::values);
        lw(v1, task, ofs::sp);
        v1 = addiu(v1, 1);
        sw(v1, task, ofs::sp);
        epilogue();  // 0x0035dfc0
    };

    // 0x0035d350
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    s1 = a1;  // $s1 = op (later reused for the int result)
    lw(v1, a0, ofs::sp);
    at = slti(v1, 2);
    if (at != 0) {
        // 0x0035d37c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 441;
        jal(ctx, 0x35D388u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035d390: the operand tags -- left = tags[sp - 1] -> 0x7CE5A0, right = tags[sp - 2] -> 0x7CE5A4
    charge(ctx, 8);
    lw(v1, task, ofs::sp);
    v1 = addu(v1, task);
    lb(a0, v1, ofs::tags - 1);
    sw(a0, gp, ofs::gp_op_lhs_tag);  // 0x7CE5A0
    lb(v1, v1, ofs::tags - 2);
    sw(v1, gp, ofs::gp_op_rhs_tag);  // 0x7CE5A4
    if (a0 != 0) {
        // 0x0035d3b0
        charge(ctx, 3);
        v1 = kTagGlobalInt;
        if (a0 != v1) {
            float_path();  // 0x0035d850: the left operand is neither an int nor a global int
            return;
        }
    }
    // 0x0035d3bc: the left operand is an int or a global int -- the right operand's tag decides
    charge(ctx, 3);
    lw(a0, gp, ofs::gp_op_rhs_tag);  // 0x7CE5A4
    if (a0 != 0) {
        // 0x0035d3c8
        charge(ctx, 3);
        v1 = kTagGlobalInt;
        if (a0 != v1) {
            float_path();  // 0x0035d850
            return;
        }
    }
    int_path();  // 0x0035d3d4: both operands are ints or global ints
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void scrOperation(EEContext& ctx, u32 task, u32 op) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(task)));
    ee::core::set_gpr64(ctx, GPR_A1, ee::core::sext32(static_cast<u32>(op)));
    scrOperation(ctx);
}

// 0x0035DFE0 CodeFunc_Add -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode ADD: scrOperation(task, kOpAdd); pc += 1. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_Add(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035dfe0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    a1 = kOpAdd;
    jal(ctx, 0x35DFF4u, gen::fn_scrOperation_0035d350);  // scrOperation(task, op)
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035E020 CodeFunc_Sub -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode SUB: scrOperation(task, kOpSub); pc += 1. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_Sub(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035e020
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    a1 = kOpSub;
    jal(ctx, 0x35E034u, gen::fn_scrOperation_0035d350);  // scrOperation(task, op)
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035E060 CodeFunc_Mul -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode MUL: scrOperation(task, kOpMul); pc += 1. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_Mul(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035e060
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    a1 = kOpMul;
    jal(ctx, 0x35E074u, gen::fn_scrOperation_0035d350);  // scrOperation(task, op)
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035E0A0 CodeFunc_Div -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode DIV: scrOperation(task, kOpDiv); pc += 1. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_Div(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035e0a0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    a1 = kOpDiv;
    jal(ctx, 0x35E0B4u, gen::fn_scrOperation_0035d350);  // scrOperation(task, op)
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035E650 CodeFunc_Or -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode OR: scrOperation(task, kOpOr); pc += 1. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_Or(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035e650
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    a1 = kOpOr;
    jal(ctx, 0x35E664u, gen::fn_scrOperation_0035d350);  // scrOperation(task, op)
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035E690 CodeFunc_And -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode AND: scrOperation(task, kOpAnd); pc += 1. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_And(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035e690
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    a1 = kOpAnd;
    jal(ctx, 0x35E6A4u, gen::fn_scrOperation_0035d350);  // scrOperation(task, op)
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035E6D0 CodeFunc_Eq -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode EQ: scrOperation(task, kOpEq); pc += 1. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_Eq(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035e6d0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    a1 = kOpEq;
    jal(ctx, 0x35E6E4u, gen::fn_scrOperation_0035d350);  // scrOperation(task, op)
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035E710 CodeFunc_Neq -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode NEQ: scrOperation(task, kOpNeq); pc += 1. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_Neq(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035e710
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    a1 = kOpNeq;
    jal(ctx, 0x35E724u, gen::fn_scrOperation_0035d350);  // scrOperation(task, op)
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035E750 CodeFunc_S -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode S: scrOperation(task, kOpLess), lhs < rhs; pc += 1. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_S(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035e750
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    a1 = kOpLess;
    jal(ctx, 0x35E764u, gen::fn_scrOperation_0035d350);  // scrOperation(task, op)
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035E790 CodeFunc_L -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode L: scrOperation(task, kOpGreater), lhs > rhs; pc += 1. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_L(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035e790
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    a1 = kOpGreater;
    jal(ctx, 0x35E7A4u, gen::fn_scrOperation_0035d350);  // scrOperation(task, op)
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035E7D0 CodeFunc_SE -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode SE: scrOperation(task, kOpLessEqual), lhs <= rhs; pc += 1. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_SE(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035e7d0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    a1 = kOpLessEqual;
    jal(ctx, 0x35E7E4u, gen::fn_scrOperation_0035d350);  // scrOperation(task, op)
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035E810 CodeFunc_LE -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opcode LE: scrOperation(task, kOpGreaterEqual), lhs >= rhs; pc += 1. Returns 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_LE(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // $s0: the ScrTask ($a0 at entry) for the whole body
    // 0x0035e810
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;  // the ScrTask stays in $s0
    a1 = kOpGreaterEqual;
    jal(ctx, 0x35E824u, gen::fn_scrOperation_0035d350);  // scrOperation(task, op)
    lw(v0, task, ofs::pc);  // pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// --- COMM-side accessors ---------------------------------------------------------------------------------
// A COMM handler (sScrCommandTable 0x7B92B0, called by CodeFunc_Comm 0x35CF20 with g_scrCurrentTask set) reads
// its arguments and writes its result through these; none takes the task as an argument.

// 0x0035F060 scrSetIntReturnVal -- 24 bytes; leaf frame (no stack)
// scrSetIntReturnVal(s32 value /*$a0*/): the COMM return register (slot 27) := value with tag 0 (int). One block
// of 6. PUSHREG (CodeFunc_PushREG) pushes it afterwards.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrSetIntReturnVal(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sb, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0035f060
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, gp, ofs::gp_current_task);  // g_scrCurrentTask->tags[27] = kTagInt
    sb(zero, v1, ofs::ret_tag);
    lw(v1, gp, ofs::gp_current_task);  // g_scrCurrentTask->values[27] = value
    sw(a0, v1, ofs::ret_value);
}

// 0x0035F080 scrSetFloatReturnVal -- 28 bytes; leaf frame (no stack)
// scrSetFloatReturnVal(f32 value /*$f12*/): slot 27 := value with tag 1 (float). One block of 7; $a0 is left 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrSetFloatReturnVal(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::enter, hg::lw, hg::sb, hg::swc1;
    Gpr v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    Fpr f12{ctx, 12};
    // 0x0035f080
    enter(ctx, 7);  // entry check point + this block's cycles
    a0 = kTagFloat;
    lw(v1, gp, ofs::gp_current_task);  // g_scrCurrentTask->tags[27] = kTagFloat
    sb(a0, v1, ofs::ret_tag);
    lw(v1, gp, ofs::gp_current_task);  // g_scrCurrentTask->values[27] = value (the float's bits)
    swc1(f12, v1, ofs::ret_value);
}

// 0x0035F120 scrSetPC -- 16 bytes; leaf frame (no stack)
// scrSetPC(s32 pc /*$a0*/): g_scrCurrentTask->pc = pc (a COMM that jumps; scrGetLabelAddr gives the target).
// One block of 4.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrSetPC(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0035f120
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, gp, ofs::gp_current_task);  // g_scrCurrentTask->pc = pc
    sw(a0, v1, ofs::pc);
}

s32 scrGetCmdTimer(EEContext& ctx) {
    guest::enter(ctx, 4);  // 0x35F130
    return guest::load<s32>(ctx, current_task(ctx) + kCmdTimer);
}

s32 scrGetMessageID(EEContext& ctx) {
    guest::enter(ctx, 4);  // 0x35F140
    return guest::load<s32>(ctx, current_task(ctx) + kMessageId);
}

u32 scrGetCurrent(EEContext& ctx) {
    guest::enter(ctx, 3);  // 0x35F150
    return current_task(ctx);
}

u32 scrGetUserData(EEContext& ctx) {
    guest::enter(ctx, 4);  // 0x35F160
    return guest::load<u32>(ctx, current_task(ctx) + kUserData);
}

// 0x0035F0A0 scrGetLabelAddr -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// scrGetLabelAddr(s32 index /*$a0*/) -> jump_labels[index].insn of g_scrCurrentTask: the instruction index of
// jump label `index` (a COMM's branch target, for scrSetPC). Asserts 0 <= index (line 1067) and index < section
// 1's element count (line 1068); both K_Assert calls are no-ops in retail, so a bad index still reads.
// Blocks: entry 6, 6 (the count test), 10.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrGetLabelAddr(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::slt, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& index = s0;  // $s0: the label index ($a0 at entry) for the whole body
    // 0x0035f0a0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    index = a0;
    if (i64(index) < 0) {
        // 0x0035f0b8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 1067;
        jal(ctx, 0x35F0C4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035f0cc: index < task->sections[1].element_count
    charge(ctx, 6);
    lw(v0, gp, ofs::gp_current_task);  // g_scrCurrentTask
    lw(v0, v0, ofs::sections);
    lw(v0, v0, ofs::section1_count);
    v0 = slt(index, v0);
    if (v0 == 0) {
        // 0x0035f0e4
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 1068;
        jal(ctx, 0x35F0F0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035f0f8: return task->jump_labels[index].insn
    charge(ctx, 10);
    lw(v0, gp, ofs::gp_current_task);  // g_scrCurrentTask
    lw(v1, v0, ofs::jump_labels);
    v0 = sll(index, ofs::label_shift);
    v0 = addu(v0, v1);
    lw(v0, v0, ofs::label_insn);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035ED20 scrGetIntPara -- 316 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// scrGetIntPara(s32 i /*$a0*/) -> COMM argument i of g_scrCurrentTask as an int: slot = sp - 1 - i (asserted
// >= 0, line 943; a no-op), read in place (the stack is not popped) and converted by its tag: 3 -> (s32)
// floats[value] (cvt.w.s), 2 -> ints[value], 1 -> (s32) value (cvt.w.s), 0 and 4 -> the raw word, anything else
// -> K_Abort "scrGetIntPara(..) invalid stack type!!" (line 956; a no-op) and 0.
// Blocks: entry 10, the slot block 6, the conversion by tag, tail 5.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrGetIntPara(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::cvt_w_s, hg::enter, hg::jal, hg::lb, hg::ld, hg::lq,
          hg::lw, hg::lwc1, hg::mfc1, hg::sd, hg::sll, hg::slt, hg::sq, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Gpr& slot = s0;  // $s0: the argument's slot index
    // 0x0035ed20
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, ofs::gp_current_task);  // slot = task->sp - (i + 1); assert task->sp >= i + 1
    lw(v1, v0, ofs::sp);
    v0 = addiu(a0, 1);
    slot = subu(v1, v0);
    at = slt(v1, v0);
    if (at != 0) {
        // 0x0035ed48
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 943;
        jal(ctx, 0x35ED54u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035ed5c: switch (task->tags[slot])
    charge(ctx, 6);
    lw(a0, gp, ofs::gp_current_task);  // $a0 = the task from here on
    v0 = addu(slot, a0);
    lb(v1, v0, ofs::tags);
    v0 = kTagGlobalFloat;
    if (v1 == v0) {
        // 0x0035edfc: (s32) floats[values[slot]]
        charge(ctx, 11);
        v0 = sll(slot, 2);
        v0 = addu(v0, a0);
        lw(v0, v0, ofs::values);
        v1 = sll(v0, 2);
        lw(v0, gp, ofs::gp_globals);  // g_scrGlobals
        v0 = addu(v0, v1);
        lwc1(f0, v0, ofs::global_floats);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
    } else {
        // 0x0035ed74
        charge(ctx, 3);
        v0 = kTagGlobalInt;
        if (v1 == v0) {
            // 0x0035edd8: ints[values[slot]]
            charge(ctx, 9);
            v0 = sll(slot, 2);
            v0 = addu(v0, a0);
            lw(v0, v0, ofs::values);
            v1 = sll(v0, 2);
            lw(v0, gp, ofs::gp_globals);  // g_scrGlobals
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
        } else {
            // 0x0035ed80
            charge(ctx, 3);
            v0 = kTagFloat;
            if (v1 == v0) {
                // 0x0035edbc: (s32) values[slot] as a float
                charge(ctx, 7);
                v0 = sll(slot, 2);
                v0 = addu(v0, a0);
                lwc1(f0, v0, ofs::values);
                cvt_w_s(f0, f0);
                mfc1(v0, f0);
            } else {
                // 0x0035ed8c
                charge(ctx, 3);
                v0 = kTagReturnAddress;
                if (v1 != v0) {
                    // 0x0035ed98: not kTagReturnAddress
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x0035eda0: an invalid tag
                        charge(ctx, 2);
                        // 0x0035ee28
                        charge(ctx, 8);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -11120);  // "scrGetIntPara(..) invalid stack type!!\n"
                        a1 = 0x6A0000;
                        a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                        a2 = 956;
                        jal(ctx, 0x35EE3Cu, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                        v0 = 0;
                        // 0x0035ee48 (the shared epilogue, written out on this path)
                        charge(ctx, 5);
                        ld(ra, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x20);
                        return;
                    }
                }
                // 0x0035eda8: tag 0 (int) or 4 (return address): the raw word values[slot]
                charge(ctx, 5);
                v0 = sll(slot, 2);
                v0 = addu(v0, a0);
                lw(v0, v0, ofs::values);
            }
        }
    }
    // 0x0035ee48 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035EE60 scrGetFloatPara -- 308 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// scrGetFloatPara(s32 i /*$a0*/) -> COMM argument i as a float in $f0: slot = sp - 1 - i (asserted, line 975),
// converted by tag: 3 -> floats[value], 2 -> (f32) ints[value] (cvt.s.w), 1 -> the value's bits, 0 and 4 ->
// (f32) value (a return-address tag is converted like an int here), anything else -> K_Abort "scrGetFloatPara(..)
// invalid stack type!!" (line 988; a no-op) and 0.0. Blocks: entry 10, slot block 6, the conversion, tail 5.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrGetFloatPara(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::cvt_s_w, hg::enter, hg::jal, hg::lb, hg::ld, hg::lq,
          hg::lw, hg::lwc1, hg::mtc1, hg::sd, hg::sll, hg::slt, hg::sq, hg::subu;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Gpr& slot = s0;  // $s0: the argument's slot index
    // 0x0035ee60
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, ofs::gp_current_task);  // slot = task->sp - (i + 1); assert task->sp >= i + 1
    lw(v1, v0, ofs::sp);
    v0 = addiu(a0, 1);
    slot = subu(v1, v0);
    at = slt(v1, v0);
    if (at != 0) {
        // 0x0035ee88
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 975;
        jal(ctx, 0x35EE94u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035ee9c: switch (task->tags[slot])
    charge(ctx, 6);
    lw(a0, gp, ofs::gp_current_task);  // $a0 = the task from here on
    v0 = addu(slot, a0);
    lb(v1, v0, ofs::tags);
    v0 = kTagGlobalFloat;
    if (v1 == v0) {
        // 0x0035ef3c: floats[values[slot]]
        charge(ctx, 9);
        v0 = sll(slot, 2);
        v0 = addu(v0, a0);
        lw(v0, v0, ofs::values);
        v1 = sll(v0, 2);
        lw(v0, gp, ofs::gp_globals);  // g_scrGlobals
        v0 = addu(v0, v1);
        lwc1(f0, v0, ofs::global_floats);
    } else {
        // 0x0035eeb4
        charge(ctx, 3);
        v0 = kTagGlobalInt;
        if (v1 == v0) {
            // 0x0035ef14: (f32) ints[values[slot]]
            charge(ctx, 10);
            v0 = sll(slot, 2);
            v0 = addu(v0, a0);
            lw(v0, v0, ofs::values);
            v1 = sll(v0, 2);
            lw(v0, gp, ofs::gp_globals);  // g_scrGlobals
            v0 = addu(v0, v1);
            lwc1(f0, v0, 0);
            cvt_s_w(f0, f0);
        } else {
            // 0x0035eec0
            charge(ctx, 3);
            v0 = kTagFloat;
            if (v1 == v0) {
                // 0x0035ef00: values[slot] as it is
                charge(ctx, 5);
                v0 = sll(slot, 2);
                v0 = addu(v0, a0);
                lwc1(f0, v0, ofs::values);
            } else {
                // 0x0035eecc
                charge(ctx, 3);
                v0 = kTagReturnAddress;
                if (v1 != v0) {
                    // 0x0035eed8: not kTagReturnAddress
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x0035eee0: an invalid tag
                        charge(ctx, 2);
                        // 0x0035ef60
                        charge(ctx, 8);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -11072);  // "scrGetFloatPara(..) invalid stack type!!\n"
                        a1 = 0x6A0000;
                        a1 = addiu(a1, -11800);  // "scrTraceCode.c"
                        a2 = 988;
                        jal(ctx, 0x35EF74u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                        mtc1(zero, f0);
                        // 0x0035ef80 (the shared epilogue, written out on this path)
                        charge(ctx, 5);
                        ld(ra, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x20);
                        return;
                    }
                }
                // 0x0035eee8: tag 0 (int) or 4 (return address): (f32) values[slot]
                charge(ctx, 6);
                v0 = sll(slot, 2);
                v0 = addu(v0, a0);
                lwc1(f0, v0, ofs::values);
                cvt_s_w(f0, f0);
            }
        }
    }
    // 0x0035ef80 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035EFA0 scrGetStrPara -- 184 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// scrGetStrPara(s32 i /*$a0*/) -> COMM argument i as a string pointer: slot = sp - 1 - i (asserted, line 1005);
// only tag 5 (PUSHSTR: a pointer into section 4) returns values[slot]; every other tag aborts ("scrGetStrPara(..)
// invalid stack type!!", line 1016; a no-op) and returns 0. Tags 0..5 go through the 6-entry `jr` table 0x7BA2D0 (7)
// of which only entry 5 reads the slot (5); entries 0..4 and tags >= 6 share the abort block (8 + K_Abort); tail 5.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrGetStrPara(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::lb, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::slt, hg::sltiu, hg::sq, hg::subu, hg::tail;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& slot = s0;  // $s0: the argument's slot index
    // 0x0035efa0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, ofs::gp_current_task);  // slot = task->sp - (i + 1); assert task->sp >= i + 1
    lw(v1, v0, ofs::sp);
    v0 = addiu(a0, 1);
    slot = subu(v1, v0);
    at = slt(v1, v0);
    if (at != 0) {
        // 0x0035efc8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -11800);  // "scrTraceCode.c"
        a1 = 1005;
        jal(ctx, 0x35EFD4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035efdc: switch (task->tags[slot]) through the table when the tag is 0..5
    charge(ctx, 6);
    lw(a0, gp, ofs::gp_current_task);  // $a0 = the task from here on
    v0 = addu(slot, a0);
    lb(v0, v0, ofs::tags);
    at = sltiu(v0, 6);
    if (at != 0) {
        // 0x0035eff4
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -23856);  // &0x7BA2D0, the jump table
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x35F010u:  // table[5]: kTagString -> values[slot]
            // 0x0035f010
            charge(ctx, 5);
            v0 = sll(slot, 2);
            v0 = addu(v0, a0);
            lw(v0, v0, ofs::values);
            break;
        case 0x35F024u:  // table[0, 1, 2, 3, 4]: not a string
        L_0035f024:  // also reached for tags outside 0..5 (below)
            charge(ctx, 8);
            a0 = 0x6A0000;
            a0 = addiu(a0, -11024);  // "scrGetStrPara(..) invalid stack type!!\n"
            a1 = 0x6A0000;
            a1 = addiu(a1, -11800);  // "scrTraceCode.c"
            a2 = 1016;
            jal(ctx, 0x35F038u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
            v0 = 0;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x0035f044 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
    goto L_0035f024;  // a tag >= 6 (unsigned): the abort block, shared with the table's entries 0..4
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (signatures from recomp/generated/functions.h) ---------
namespace p3fes::recomp_gen {

using namespace p3fes::game;

#define P3FES_SCR_HANDLER_SHIM(name, addr) \
    void fn_##name##_##addr(p3fes::EEContext& ctx) { guest::ret32(ctx, name(ctx, guest::arg32(ctx, 0))); }

#undef P3FES_SCR_HANDLER_SHIM

void fn_scrGetCmdTimer_0035f130(p3fes::EEContext& ctx) { guest::rets32(ctx, scrGetCmdTimer(ctx)); }
void fn_scrGetMessageID_0035f140(p3fes::EEContext& ctx) { guest::rets32(ctx, scrGetMessageID(ctx)); }
void fn_scrGetCurrent_0035f150(p3fes::EEContext& ctx) { guest::ret32(ctx, scrGetCurrent(ctx)); }
void fn_scrGetUserData_0035f160(p3fes::EEContext& ctx) { guest::ret32(ctx, scrGetUserData(ctx)); }

}  // namespace p3fes::recomp_gen
