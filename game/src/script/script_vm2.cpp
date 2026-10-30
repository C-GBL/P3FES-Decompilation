// BF script VM, second wave (game/include/p3fes/game/script_vm2.h): the interpreter loop scrTraceCode,
// the dds3 task body, the FLW0 section resolver, the procedure lookup, the dds3 accessors and the
// generic COMM functions, hand-decompiled from SLUS_216.21 (scrScriptProcess.c, scrTraceCode.c,
// scrCommonCommand.c; docs/ANALYSIS/18_script_vm.md sections 2.1, 2.4, 3, 4).
// tests/game/test_script_vm2.cpp runs each against its __recomp body.
//
// Virtual time (ADR-0013): guest::enter / charge / backedge mirror the `ctx.cycles += N` blocks and the
// check points of the recompiled bodies (recomp/generated/fn_0029_0035ac90_00367d70.cpp); a block is
// charged at its start, before the callees it contains run, so their check points see the same clock.
// Every callee -- still recompiled or already replaced -- is entered through its generated symbol with
// the registers the original set (64-bit register copies stay 64-bit: `daddu $sN, $aN, $zero` keeps the
// whole register, so an argument the original forwarded from a saved copy is forwarded as read at
// entry), and each function that called out of a stack frame keeps that frame (guest::StackFrame) so
// the callees' frames land where they did. K_Assert sub_19D3F0 / K_Abort sub_19D400 are `jr $ra` in
// retail: a failed check goes on.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 25 of the 26 functions here are p3fes_handgen's register-faithful
// bodies (their hand versions differed from the original: frame/spills 25); sub_35B270 (COMM 22, `return 1`) is the
// hand-written version. Readability pass 2026-10-21 (slice read_script) over the 25: a role comment per function (the
// COMM functions with their index in sScrCommandTable 0x7B92B0 and their arguments), ScrTask offsets by name (scr::ofs),
// the BF header / descriptor layout (bf::), named registers (`Gpr &image = s5`), block roles, and the gotos turned into
// if / else and loop breaks -- the epilogue and scrStartScript2's bad-magic block are local lambdas called where the
// generated body jumped to them. Every guest statement, frame, spill, link, cycle charge and check point is the
// generated body's, in its order on every path.
#include "p3fes/game/script_vm2.h"

#include "p3fes/ee/core.h"
#include "p3fes/ee/fpu.h"
#include "p3fes/ee/hilo.h"
#include "p3fes/game/guest.h"
#include "p3fes/game/script_vm.h"

#include <initializer_list>
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line)
void fn_sub_19D400_0019d400(p3fes::EEContext&);  // K_Abort(message, file, line)
void fn_sub_1052B0_001052b0(p3fes::EEContext&);  // H_Dbprt formatter (the trace line)
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_scrStartScript_0035b570(p3fes::EEContext&);
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);
void fn_kwlnTaskGetTimer_00195520(p3fes::EEContext&);
void fn_kwlnTaskGetWorkData_00195540(p3fes::EEContext&);
void fn_kwlnTaskSetWorkData_00195530(p3fes::EEContext&);
void fn_MT_Misc_BitChk_003951d0(p3fes::EEContext&);
void fn_sub_395170_00395170(p3fes::EEContext&);  // MT_Misc_BitOn
void fn_sub_3951A0_003951a0(p3fes::EEContext&);  // MT_Misc_BitOff
void fn_sub_488F30_00488f30(p3fes::EEContext&);  // RpRandom
// already replaced (game/src/script/script_ops.cpp) or defined below
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_scrGetFloatPara_0035ee60(p3fes::EEContext&);
void fn_scrSetIntReturnVal_0035f060(p3fes::EEContext&);
void fn_scrSetFloatReturnVal_0035f080(p3fes::EEContext&);
void fn_scrGetLabelAddr_0035f0a0(p3fes::EEContext&);
void fn_scrSetPC_0035f120(p3fes::EEContext&);
void fn_scrGetCmdTimer_0035f130(p3fes::EEContext&);
void fn_scrTraceCode_0035ebf0(p3fes::EEContext&);
void fn_scrStartScript2_0035b930(p3fes::EEContext&);
void fn_sub_35ADD0_0035add0(p3fes::EEContext&);
void fn_sub_35ADF0_0035adf0(p3fes::EEContext&);
void fn_dds3GetProcessWorkData_0035ae10(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

using namespace scr;
using namespace scr2;
using guest::Fn;

// The BF header and its 16-byte section descriptors (scr2::kBf*, kSection*) as instruction immediates.
namespace bf {
constexpr s32 magic = 8, section_count = 0x10, sections = 0x20;  // 'FLW0' at +8; descriptors at +0x20
constexpr s32 type = 0, element_count = 8, offset = 12;          // inside a descriptor
constexpr unsigned descriptor_shift = 4;                         // descriptors are 16 bytes
static_assert(magic == static_cast<s32>(kBfMagic) && section_count == static_cast<s32>(kBfSectionCount) &&
              sections == static_cast<s32>(kBfSections) && element_count == static_cast<s32>(kSectionElementCount) &&
              offset == static_cast<s32>(kSectionOffset) && (1u << descriptor_shift) == kSectionSize);
}  // namespace bf

// $gp-relative / absolute words the COMM functions read.
constexpr s32 kPadWordALo = 2382;  // 0x7E094E = 0x7E0000 + 2382 (scr2::kPadWordA)
constexpr s32 kPadWordBLo = 2380;  // 0x7E094C (scr2::kPadWordB)
static_assert(0x7E0000u + kPadWordALo == kPadWordA && 0x7E0000u + kPadWordBLo == kPadWordB);

}  // namespace

// --- the interpreter ----------------------------------------------------------------------------------

// 0x0035EBF0 scrTraceCode -- 296 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// scrTraceCode(ScrTask* task /*$a0*/): runs the task's instructions until a handler yields or the script ends.
// Per instruction: opcode = insn[pc].opcode (asserted 0 <= op < 35, lines 895 / 896; no-ops in retail, so a bad
// opcode is still dispatched), a trace line through H_Dbprt (sub_1052B0, ">>>SCRIPT TRACE <0x%X>") when
// g_scrTraceFlag == 1, then sScrOpcodeTbl[op](task). Handler result 0 = the script ended: cmd_timer = 0, returns 2;
// 2 = yield this frame: cmd_timer++ and frames++, returns 1; 1 = next instruction: cmd_timer = 0; anything else loops
// on without clearing it. The handlers get the whole $a0 the function was entered with (kept in $s1 by `daddu`).
// Blocks: entry 5; per instruction 7 (fetch), 5 + K_Assert, 3, 5 + K_Assert, 4 (trace flag), 9 + H_Dbprt, 10
// (dispatch); result 0: 4; else 3; result 2: 7; else 3 and, for 1, 3 more; then the back-edge check. Epilogue 6.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrTraceCode(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal, hg::jalr, hg::ld,
          hg::lh, hg::lq, hg::lw, hg::sd, hg::sll, hg::slti, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Gpr &task = s1, &opcode = s0;
    // 0x0035ebf0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    task = a0;
    for (;;) {
        // 0x0035ec04: opcode = insn[pc].opcode (s16)
        charge(ctx, 7);
        lw(v0, task, ofs::pc);
        v1 = sll(v0, 2);
        lw(v0, task, ofs::insn);
        v0 = addu(v0, v1);
        lh(opcode, v0, ofs::opcode);
        if (i64(opcode) < 0) {
            // 0x0035ec20
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -11800);  // "scrTraceCode.c"
            a1 = 895;
            jal(ctx, 0x35EC2Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
        }
        // 0x0035ec34
        charge(ctx, 3);
        v0 = slti(opcode, kOpcodeCount);
        if (v0 == 0) {
            // 0x0035ec40
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -11800);  // "scrTraceCode.c"
            a1 = 896;
            jal(ctx, 0x35EC4Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
        }
        // 0x0035ec54: g_scrTraceFlag == 1 -> H_Dbprt(">>>SCRIPT TRACE <0x%X>\n", insn[pc].operand)
        charge(ctx, 4);
        lw(v1, gp, ofs::gp_trace_flag);  // g_scrTraceFlag
        v0 = 1;
        if (v1 == v0) {
            // 0x0035ec64
            charge(ctx, 9);
            lw(v0, task, ofs::pc);
            v1 = sll(v0, 2);
            lw(v0, task, ofs::insn);
            v0 = addu(v0, v1);
            lh(a1, v0, ofs::operand);
            a0 = 0x6A0000;
            a0 = addiu(a0, -11152);  // ">>>SCRIPT TRACE <0x%X>\n"
            jal(ctx, 0x35EC80u, gen::fn_sub_1052B0_001052b0);
        }
        // 0x0035ec88: v0 = sScrOpcodeTbl[opcode](task)
        charge(ctx, 10);
        a0 = task;
        v1 = sll(opcode, 2);
        v0 = 0x6A0000;
        v0 = addiu(v0, -11296);  // &sScrOpcodeTbl
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        jalr(ctx, 0x35ECA0u, v0.u());
        if (v0 == 0) {
            // 0x0035ecb0: 0 = the script ended -- cmd_timer = 0, return 2
            charge(ctx, 4);
            sw(zero, task, ofs::cmd_timer);
            v0 = 2;
            // 0x0035ed00 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
        // 0x0035ecc0
        charge(ctx, 3);
        v1 = 2;
        if (v0 == v1) {
            break;  // 2 = yield this frame
        }
        // 0x0035eccc
        charge(ctx, 3);
        v1 = 1;
        if (v0 != v1) {
            backedge(ctx);
        } else {
            // 0x0035ecd8: 1 = next instruction -- cmd_timer = 0
            charge(ctx, 3);
            sw(zero, task, ofs::cmd_timer);
            backedge(ctx);
        }
    }
    // 0x0035ece4: a yield -- cmd_timer += 1, frames += 1; return 1
    charge(ctx, 7);
    lw(v0, task, ofs::cmd_timer);
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::cmd_timer);
    lw(v0, task, ofs::frames);
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::frames);
    v0 = 1;  // done
    // 0x0035ed00 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0035C270 scrScriptProcess -- 140 bytes; frame 0x10: ra sp+0x0
// scrScriptProcess(process /*$a0*/): the dds3 per-frame body of a script task: runs
// scrTraceCode(dds3GetProcessWorkData(process)) and maps its result for the process manager: 2 (ended) -> -1 (the
// process is done), 1 (yield) -> 0, 0 -> K_Abort "scrScriptProcess(..) error script!" (line 1120; a no-op) and -1,
// anything else 0. Blocks: 10 (both calls), 3 per compare against 2 and 1, 2 against 0, the K_Abort block 10, 3 / 1
// for the results, epilogue 4.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrScriptProcess(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::sd, hg::si;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035c270
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x35C278u, gen::fn_dds3GetProcessWorkData_0035ae10);  // the ScrTask
    a0 = v0;
    jal(ctx, 0x35C284u, gen::fn_scrTraceCode_0035ebf0);
    v1 = 2;
    if (v0 == v1) {
        // 0x0035c2dc: ended -- the process is done
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x0035c298
        charge(ctx, 3);
        v1 = 1;
        if (v0 != v1) {
            // 0x0035c2a4
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x0035c2b4: 0 cannot come back from scrTraceCode
                charge(ctx, 10);
                a0 = 0x6A0000;
                a0 = addiu(a0, -11840);  // "scrScriptProcess(..) error script!\n"
                a1 = 0x6A0000;
                a1 = addiu(a1, -12368);  // "scrScriptProcess.c"
                a2 = 1120;
                jal(ctx, 0x35C2C8u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                v0 = si(-1);
                // 0x0035c2ec (the shared epilogue, written out on this path)
                charge(ctx, 4);
                ld(ra, sp, 0x0);
                sp = addiu(sp, 0x10);
                return;
            }
            // 0x0035c2ac
            charge(ctx, 2);
        }
        // 0x0035c2e8: yield (or another value) -- keep running
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0035c2ec (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0035C250 scrForceTraceCode -- 32 bytes; frame 0x10: ra sp+0x0
// scrForceTraceCode(ScrTask* task): one synchronous scrTraceCode(task) outside the process manager; $a0 passes
// through and the result is scrTraceCode's. One block of 8.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrForceTraceCode(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0035c250
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x35C258u, gen::fn_scrTraceCode_0035ebf0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// --- loading ------------------------------------------------------------------------------------------

// 0x0035B930 scrStartScript2 -- 520 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// scrStartScript2(BfHeader* image /*$a0*/, s32 start_proc /*$a1*/) -> ScrTask*: checks the 'FLW0' magic at +8
// (K_Assert for a null image, line 271; a mismatch -> K_Abort "invalid script data!!" (280) and 0), resolves the
// section descriptors (+0x20, 16 bytes each, count at +0x10) by type to absolute pointers -- 0 procedure labels,
// 1 jump labels, 2 instructions, 3 messages (only when its element count is non-zero), 4 strings; a later
// descriptor of the same type wins; an unknown type -> K_Abort "scrStartScript2(..) Invalid type!!" (306) and 0 --
// and returns scrStartScript(image, image + 0x20, procs, jumps, insns, messages, strings, start_proc). The image and
// the start procedure go on as the whole registers they arrived in ($s5 / $s6 copies).
// Blocks: entry 18, 5 + K_Assert, 5 (first magic byte), 4 per further byte, 10 + K_Abort on a mismatch; 8, then the
// section loop (test 3, checked as a back-edge before every descriptor including the first; 5, 2 per failed type
// compare in the order 4, 3, 2, 1, 0; 4 to take a section (3 + 4 for type 3, 3 alone when it is empty); 2 + 10 +
// K_Abort after the fifth failed compare; 1 to advance); 9 + scrStartScript; epilogue 11.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrStartScript2(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lb, hg::ld, hg::lq, hg::lw,
          hg::sd, hg::sll, hg::slt, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Gpr &image = s5, &start_proc = s6;                                                 // the arguments
    Gpr &procs = s4, &jumps = s3, &insns = s2, &messages = s1, &strings = s0;          // the sections found
    Gpr &descs = a1, &index = v1, &count = v0, &desc = t2;                             // the descriptor loop

    // 0x0035bb0c: the epilogue (the generated body wrote it out on each path).
    auto epilogue = [&] {
        charge(ctx, 11);
        ld(ra, sp, 0x70);
        lq(s6, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x80);
    };
    // 0x0035b9d0: not 'FLW0' -- K_Abort (a no-op) and return 0.
    auto bad_magic = [&] {
        charge(ctx, 10);
        a0 = 0x6A0000;
        a0 = addiu(a0, -12192);  // "invalid script data!!\n"
        a1 = 0x6A0000;
        a1 = addiu(a1, -12368);  // "scrScriptProcess.c"
        a2 = 280;
        jal(ctx, 0x35B9E4u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
        v0 = 0;
        epilogue();  // 0x0035bb0c
    };

    // 0x0035b930
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    image = a0;
    start_proc = a1;
    procs = 0;
    jumps = 0;
    insns = 0;
    messages = 0;
    strings = 0;
    if (image == 0) {
        // 0x0035b978
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -12368);  // "scrScriptProcess.c"
        a1 = 271;
        jal(ctx, 0x35B984u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035b98c: the magic 'F' 'L' 'W' '0' at image + 8
    charge(ctx, 5);
    descs = addiu(image, bf::sections);
    lb(v1, image, bf::magic);
    v0 = 'F';
    if (v1 != v0) {
        bad_magic();
        return;
    }
    // 0x0035b9a0
    charge(ctx, 4);
    lb(v1, image, bf::magic + 1);
    v0 = 'L';
    if (v1 != v0) {
        bad_magic();
        return;
    }
    // 0x0035b9b0
    charge(ctx, 4);
    lb(v1, image, bf::magic + 2);
    v0 = 'W';
    if (v1 != v0) {
        bad_magic();
        return;
    }
    // 0x0035b9c0
    charge(ctx, 4);
    lb(v1, image, bf::magic + 3);
    v0 = '0';
    if (v1 != v0) {
        bad_magic();
        return;
    }
    // 0x0035b9f8: for (index = 0; index < image->section_count; index++) take descriptor `index` by its type
    charge(ctx, 8);
    index = 0;
    lw(count, image, bf::section_count);
    a2 = kSectionJumpLabels;
    a3 = kSectionInsns;
    t0 = kSectionMessages;
    t1 = kSectionStrings;
    for (;;) {
        // 0x0035badc
        charge(ctx, 3);
        a0 = slt(index, count);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0035ba18: desc = descs + 16 * index; switch (desc->type)
        charge(ctx, 5);
        a0 = sll(index, bf::descriptor_shift);
        desc = addu(descs, a0);
        lw(a0, desc, bf::type);
        if (a0 == t1) {
            // 0x0035baa0: type 4 -- strings = image + desc->offset
            charge(ctx, 4);
            lw(a0, desc, bf::offset);
            strings = addu(image, a0);
        } else {
            // 0x0035ba2c
            charge(ctx, 2);
            if (a0 == t0) {
                // 0x0035ba84: type 3 -- messages = image + desc->offset, only when desc->element_count != 0
                charge(ctx, 3);
                lw(a0, desc, bf::element_count);
                if (a0 != 0) {
                    // 0x0035ba90
                    charge(ctx, 4);
                    lw(a0, desc, bf::offset);
                    messages = addu(image, a0);
                }
            } else {
                // 0x0035ba34
                charge(ctx, 2);
                if (a0 == a3) {
                    // 0x0035ba74: type 2 -- insns = image + desc->offset
                    charge(ctx, 4);
                    lw(a0, desc, bf::offset);
                    insns = addu(image, a0);
                } else {
                    // 0x0035ba3c
                    charge(ctx, 2);
                    if (a0 == a2) {
                        // 0x0035ba64: type 1 -- jumps = image + desc->offset
                        charge(ctx, 4);
                        lw(a0, desc, bf::offset);
                        jumps = addu(image, a0);
                    } else {
                        // 0x0035ba44
                        charge(ctx, 2);
                        if (a0 != 0) {
                            // 0x0035ba4c: an unknown type -- K_Abort (a no-op) and return 0
                            charge(ctx, 2);
                            // 0x0035bab0
                            charge(ctx, 10);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, -12160);  // "scrStartScript2(..) Invalid type!!\n"
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -12368);  // "scrScriptProcess.c"
                            a2 = 306;
                            jal(ctx, 0x35BAC4u, gen::fn_sub_19D400_0019d400);  // K_Abort(message, file, line): a no-op in retail
                            v0 = 0;
                            epilogue();  // 0x0035bb0c
                            return;
                        }
                        // 0x0035ba54: type 0 -- procs = image + desc->offset
                        charge(ctx, 4);
                        lw(a0, desc, bf::offset);
                        procs = addu(image, a0);
                    }
                }
            }
        }
        // 0x0035bad8: the next descriptor
        charge(ctx, 1);
        index = addiu(index, 1);
    }
    // 0x0035bae8: return scrStartScript(image, descs, procs, jumps, insns, messages, strings, start_proc)
    charge(ctx, 9);
    a0 = image;
    a2 = procs;
    a3 = jumps;
    t0 = insns;
    t1 = messages;
    t2 = strings;
    t3 = start_proc;
    jal(ctx, 0x35BB04u, gen::fn_scrStartScript_0035b570);
    epilogue();  // 0x0035bb0c
}

// 0x0035BD20 sub_35BD20 -- 36 bytes; frame 0x10: ra sp+0x0
// sub_35BD20(BfHeader* image) [scrStartScriptFirstPrcd] -> scrStartScript2(image, 0): starts a script at its first
// procedure; $a0 passes through. One block of 9.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_35BD20(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035bd20
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 0;  // start_proc
    jal(ctx, 0x35BD2Cu, gen::fn_scrStartScript2_0035b930);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0035C090 scrFindPrcdIdxByName -- 260 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// scrFindPrcdIdxByName(BfHeader* image /*$a0*/, const char* name /*$a1*/) -> the index of the procedure called
// `name` (strcmp against the 32-byte labels of the first type-0 section), -1 for a null image, no procedure section
// or no match. Blocks: entry 10; 3 for a null image; 5, then the descriptor loop up to the first type-0 descriptor
// (test 3 checked before each; 5, 4 on type 0, 1 to advance); 2, 3 when there is no procedure section; 5, the label
// loop (test 4 checked before each; 7 + strcmp, 3 on a match, 1 to advance; 1 after the last); epilogue 8.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrFindPrcdIdxByName(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::si, hg::sll, hg::slt, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Gpr &image = a0, &name = s3, &labels = s2, &index = s1, &section = s0;
    Gpr &descs = a2, &d = a3, &count = a1, &desc = v1;

    // 0x0035c174: the epilogue (the generated body wrote it out on each path).
    auto epilogue = [&] {
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
    };

    // 0x0035c090
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    name = a1;
    labels = 0;
    if (image != 0) {
        // 0x0035c0c4: find the first descriptor of type 0 (procedure labels)
        charge(ctx, 5);
        descs = addiu(image, bf::sections);
        d = 0;
        lw(count, image, bf::section_count);
        for (;;) {
            // 0x0035c100
            charge(ctx, 3);
            v0 = slt(d, count);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0035c0d8
            charge(ctx, 5);
            v0 = sll(d, bf::descriptor_shift);
            desc = addu(descs, v0);
            lw(v0, desc, bf::type);
            if (v0 == 0) {
                // 0x0035c0ec: labels = image + desc->offset
                charge(ctx, 4);
                lw(v0, desc, bf::offset);
                labels = addu(image, v0);
                break;
            }
            // 0x0035c0fc
            charge(ctx, 1);
            d = addiu(d, 1);
        }
        // 0x0035c10c
        charge(ctx, 2);
        if (labels != 0) {
            // 0x0035c120: for (index = 0; index < descs[d].element_count; index++) strcmp(labels[index].name, name)
            charge(ctx, 5);
            index = 0;
            v0 = sll(d, bf::descriptor_shift);
            section = addu(descs, v0);
            for (;;) {
                // 0x0035c160
                charge(ctx, 4);
                lw(v0, section, bf::element_count);
                v0 = slt(index, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0035c134
                charge(ctx, 7);
                v0 = sll(index, ofs::label_shift);
                a0 = addu(labels, v0);
                a1 = name;
                jal(ctx, 0x35C140u, gen::fn_strcmp_00524128);
                if (v0 == 0) {
                    // 0x0035c150: found -- return index
                    charge(ctx, 3);
                    v0 = index;
                    epilogue();  // 0x0035c174
                    return;
                }
                // 0x0035c15c
                charge(ctx, 1);
                index = addiu(index, 1);
            }
            // 0x0035c170: no match
            charge(ctx, 1);
            v0 = si(-1);
        } else {
            // 0x0035c114: no procedure section
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x0035c0b8: a null image
        charge(ctx, 3);
        v0 = si(-1);
    }
    epilogue();  // 0x0035c174
}

// 0x0035C1A0 scrSetUserData -- 88 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// scrSetUserData(process /*$a0*/, u32 data /*$a1*/): the script task of `process` (dds3GetProcessWorkData; asserted
// non-null, line 1052 -- a no-op, so a null task is stored through too) gets user_data = data (scrGetUserData reads
// it back). $v0 stays the task pointer. Blocks: 10 + dds3GetProcessWorkData, 5 + K_Assert, 7 (the store).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrSetUserData(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Gpr &task = s0, &data = s1;
    // 0x0035c1a0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    data = a1;
    jal(ctx, 0x35C1B4u, gen::fn_dds3GetProcessWorkData_0035ae10);
    task = v0;
    if (task == 0) {
        // 0x0035c1c8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -12368);  // "scrScriptProcess.c"
        a1 = 1052;
        jal(ctx, 0x35C1D4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035c1dc: task->user_data = data
    charge(ctx, 7);
    sw(data, task, ofs::user_data);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// --- COMM functions -----------------------------------------------------------------------------------

// 0x0035AEB0 scrCommand_BIT_CHK -- 64 bytes; frame 0x10: ra sp+0x0
// COMM 7 BIT_CHK (1 argument; sScrCommandTable 0x7B92B0): returns MT_Misc_BitChk(arg0), the event flag arg0.
// Returns 1 (done). One block of 16.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrCommand_BIT_CHK_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035aeb0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x35AEBCu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    a0 = v0;
    jal(ctx, 0x35AEC8u, gen::fn_MT_Misc_BitChk_003951d0);
    a0 = v0;
    jal(ctx, 0x35AED4u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0035AEF0 scrCommand_BIT_ON -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 8 BIT_ON (1 argument): sets event flag arg0 (sub_395170 [MT_Misc_BitOn]); asserts arg0 < 0x1600 unsigned
// (line 117; a no-op in retail). Returns 1. Blocks: 10, 5 + K_Assert, 9.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrCommand_BIT_ON_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sltiu, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035aef0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x35AF00u, gen::fn_scrGetIntPara_0035ed20);  // the flag
    s0 = v0;
    v0 = sltiu(s0, 0x1600);  // arg0 < kFlagCount (unsigned)
    if (v0 == 0) {
        // 0x0035af18
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -12576);  // "scrCommonCommand.c"
        a1 = 117;
        jal(ctx, 0x35AF24u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035af2c
    charge(ctx, 9);
    a0 = s0;
    jal(ctx, 0x35AF30u, gen::fn_sub_395170_00395170);  // [MT_Misc_BitOn](flag)
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035AF50 scrCommand_BIT_OFF -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 9 BIT_OFF (1 argument): clears event flag arg0 (sub_3951A0 [MT_Misc_BitOff]); asserts arg0 < 0x1600
// (line 132). Returns 1. Blocks: 10, 5 + K_Assert, 9.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrCommand_BIT_OFF_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sltiu, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035af50
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x35AF60u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s0 = v0;
    v0 = sltiu(s0, 0x1600);  // arg0 < kFlagCount (unsigned)
    if (v0 == 0) {
        // 0x0035af78
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -12576);  // "scrCommonCommand.c"
        a1 = 132;
        jal(ctx, 0x35AF84u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x0035af8c
    charge(ctx, 9);
    a0 = s0;
    jal(ctx, 0x35AF90u, gen::fn_sub_3951A0_003951a0);  // [MT_Misc_BitOff](flag)
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035AFB0 scrCommand_RAND -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 10 RAND (1 argument): returns RpRandom() % (arg0 + 1) (sub_488F30; divu leaves the remainder in HI -- a
// zero divisor, arg0 == -1, follows the EE rule of ee::divu, as the recompiled divu does). Returns 1. One block of 19.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrCommand_RAND_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::divu, hg::enter, hg::jal, hg::ld, hg::lq, hg::mfhi, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035afb0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x35AFC0u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s0 = addiu(v0, 1);
    jal(ctx, 0x35AFCCu, gen::fn_sub_488F30_00488f30);
    divu(v0, s0);
    mfhi(a0);
    jal(ctx, 0x35AFDCu, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035B000 scrCommand_SYNC -- 36 bytes; frame 0x10: ra sp+0x0
// COMM 11 SYNC (no arguments): returns (scrGetCmdTimer() != 0) to the dispatcher -- 0 on the first frame (re-run
// next frame), 1 from the second (sltu $v0, $zero, $v0 on the whole register). One block of 9.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrCommand_SYNC_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd, hg::sltu;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035b000
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x35B008u, gen::fn_scrGetCmdTimer_0035f130);
    v0 = sltu(0, v0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0035B030 scrCommand_WAIT -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 12 WAIT (1 argument: frames): done (1) at once when arg0 <= 0, else once cmd_timer >= arg0 (0 = wait one
// more frame; 64-bit signed compares). Blocks: 8; arg0 <= 0 -> 3; else 8 (cmd timer, arg0 again); epilogue 5.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrCommand_WAIT_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld, hg::lq, hg::sd, hg::slt, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035b030
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x35B040u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    if (i64(v0) > 0) {
        // 0x0035b05c
        charge(ctx, 8);
        jal(ctx, 0x35B05Cu, gen::fn_scrGetCmdTimer_0035f130);
        s0 = v0;
        a0 = 0;
        jal(ctx, 0x35B06Cu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
        v0 = slt(s0, v0);
        v0 = v0 ^ 0x1;
    } else {
        // 0x0035b050
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0035b07c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035B110 scrCommand_SWITCH -- 160 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 15 SWITCH (8 arguments: sel, label0..label6): when sel >= 0 (asserted < 7, line 342) and label_sel =
// argument sel + 1 is >= 0, jumps there (scrSetPC(scrGetLabelAddr(label_sel))). Always done (1).
// Blocks: 9; sel < 0 -> 3; else 3, 5 + K_Assert, 5; a negative label -> 3; else 7; epilogue 5. ($at keeps `sel < 7`.)
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrCommand_SWITCH_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld, hg::lq, hg::sd, hg::slti, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035b110
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x35B120u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s0 = v0;
    if (i64(s0) >= 0) {
        // 0x0035b140
        charge(ctx, 3);
        at = slti(s0, kSwitchLabels);  // sel < 7
        if (at == 0) {
            // 0x0035b14c
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -12576);  // "scrCommonCommand.c"
            a1 = 342;
            jal(ctx, 0x35B158u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
        }
        // 0x0035b160
        charge(ctx, 5);
        a0 = addiu(s0, 1);  // label = argument sel + 1
        jal(ctx, 0x35B164u, gen::fn_scrGetIntPara_0035ed20);
        if (i64(v0) >= 0) {
            // 0x0035b180
            charge(ctx, 7);
            a0 = v0;
            jal(ctx, 0x35B184u, gen::fn_scrGetLabelAddr_0035f0a0);
            a0 = v0;
            jal(ctx, 0x35B190u, gen::fn_scrSetPC_0035f120);
            v0 = 1;
        } else {
            // 0x0035b174
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x0035b134
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0035b19c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035B1B0 sub_35B1B0 -- 60 bytes; frame 0x10: ra sp+0x0
// COMM 19 (1 argument: a button mask): returns gPadFlags (u16 0x7E094E) & arg0 [a pad-button test]. Returns 1.
// One block of 15.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_35B1B0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lhu, hg::sd;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035b1b0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x35B1BCu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    v1 = 0x7E0000;
    lhu(v1, v1, kPadWordALo);  // gPadFlags (u16 0x7E094E)
    a0 = v1 & v0;
    jal(ctx, 0x35B1D0u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0035B1F0 sub_35B1F0 -- 60 bytes; frame 0x10: ra sp+0x0
// COMM 20 (1 argument: a button mask): returns (u16 0x7E094C) & arg0, the other pad word. Returns 1. One block of
// 15.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_35B1F0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lhu, hg::sd;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035b1f0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x35B1FCu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    v1 = 0x7E0000;
    lhu(v1, v1, kPadWordBLo);  // u16 0x7E094C
    a0 = v1 & v0;
    jal(ctx, 0x35B210u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0035B230 sub_35B230 -- 64 bytes; frame 0x10: ra sp+0x0
// COMM 21 (3 arguments): reads the three arguments and drops them (a command stubbed out in this build).
// Returns 1. One block of 16.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_35B230_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035b230
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x35B23Cu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    a0 = 1;
    jal(ctx, 0x35B248u, gen::fn_scrGetIntPara_0035ed20);  // arg 1 (int)
    a0 = 2;
    jal(ctx, 0x35B254u, gen::fn_scrGetIntPara_0035ed20);  // arg 2 (int)
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

u32 sub_35B270(EEContext& ctx) {
    guest::enter(ctx, 3);  // 0x35B270: leaf, return 1
    return 1;
}

// 0x0035B400 sub_35B400 -- 56 bytes; frame 0x10: ra sp+0x0
// COMM 25 (1 argument: a process): done (1) once process arg0 no longer exists (sub_35ADD0 [dds3ProcessExists]
// == 0; sltiu of the whole $v0), else 0 (wait) [scrCommand_SCR_KILL_SYNC]. One block of 14.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_35B400_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd, hg::sltiu;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035b400
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x35B40Cu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    a0 = v0;
    jal(ctx, 0x35B418u, gen::fn_sub_35ADD0_0035add0);
    // xor v0: a 64-bit move to itself (no effect)
    v0 = sltiu(v0, 1);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0035B440 scrCommand_SCR_EXISTS -- 92 bytes; frame 0x10: ra sp+0x0
// COMM 26 SCR_EXISTS (1 argument: a process): returns 1 when process arg0 exists (sub_35ADD0), else 0. Returns
// 1. Blocks: 10; exists -> 5; else 3; epilogue 5.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrCommand_SCR_EXISTS_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035b440
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x35B44Cu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    a0 = v0;
    jal(ctx, 0x35B458u, gen::fn_sub_35ADD0_0035add0);
    if (v0 == 0) {
        // 0x0035b47c
        charge(ctx, 3);
        a0 = 0;
        jal(ctx, 0x35B480u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    } else {
        // 0x0035b468
        charge(ctx, 5);
        a0 = 1;
        jal(ctx, 0x35B46Cu, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    }
    // 0x0035b488 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0035B4A0 scrCommand_SCR_GET_TIMER -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 27 SCR_GET_TIMER (1 argument: a process): returns the process's timer (sub_35ADF0
// [dds3GetProcessTimer]), 0 when it does not exist. Returns 1. Blocks: 12; missing -> 5; else 6; epilogue 6.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void scrCommand_SCR_GET_TIMER_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035b4a0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x35B4B0u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x35B4C0u, gen::fn_sub_35ADD0_0035add0);
    if (v0 != 0) {
        // 0x0035b4e4
        charge(ctx, 6);
        a0 = s0;
        jal(ctx, 0x35B4E8u, gen::fn_sub_35ADF0_0035adf0);
        a0 = v0;
        jal(ctx, 0x35B4F4u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    } else {
        // 0x0035b4d0
        charge(ctx, 5);
        a0 = 0;
        jal(ctx, 0x35B4D4u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    }
    // 0x0035b4fc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0035B520 sub_35B520 -- 68 bytes; frame 0x10: ra sp+0x0
// COMM 46 (1 argument) [scrCommand_SQRT]: returns sqrt(arg0) as a float: scrSetFloatReturnVal(sqrt.s(
// scrGetFloatPara(0))). The body sets no $v0: the COMM dispatcher sees what the two callees left there. One block of
// 17.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_35B520(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd, hg::sqrt_s;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x0035b520
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x35B52Cu, gen::fn_scrGetFloatPara_0035ee60);  // arg 0 (float)
    sqrt_s(f12, f0);
    jal(ctx, 0x35B54Cu, gen::fn_scrSetFloatReturnVal_0035f080);  // the COMM result (float)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0035ADD0 sub_35ADD0 -- 32 bytes; frame 0x10: ra sp+0x0
// sub_35ADD0(process) [dds3ProcessExists] = kwlnTaskExists(process): the dds3 layer over the kwln task kernel.
// One block of 8.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_35ADD0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0035add0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x35ADD8u, gen::fn_kwlnTaskExists_00195460);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0035ADF0 sub_35ADF0 -- 32 bytes; frame 0x10: ra sp+0x0
// sub_35ADF0(process) [dds3GetProcessTimer] = kwlnTaskGetTimer(process). One block of 8.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_35ADF0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0035adf0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x35ADF8u, gen::fn_kwlnTaskGetTimer_00195520);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0035AE10 dds3GetProcessWorkData -- 32 bytes; frame 0x10: ra sp+0x0
// dds3GetProcessWorkData(process) = kwlnTaskGetWorkData(process): for a script process, its ScrTask. One block
// of 8.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void dds3GetProcessWorkData(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0035ae10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x35AE18u, gen::fn_kwlnTaskGetWorkData_00195540);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0035AE30 sub_35AE30 -- 32 bytes; frame 0x10: ra sp+0x0
// sub_35AE30(process, work) [dds3SetProcessWorkData] = kwlnTaskSetWorkData(process, work). One block of 8.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_35AE30(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0035ae30
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x35AE38u, gen::fn_kwlnTaskSetWorkData_00195530);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (signatures from recomp/generated/functions.h) ---------
namespace p3fes::recomp_gen {

using namespace p3fes::game;

#define P3FES_SCR_COMMAND_SHIM(name, addr) \
    void fn_##name##_##addr(p3fes::EEContext& ctx) { guest::ret32(ctx, name(ctx)); }
P3FES_SCR_COMMAND_SHIM(sub_35B270, 0035b270)
#undef P3FES_SCR_COMMAND_SHIM

}  // namespace p3fes::recomp_gen
