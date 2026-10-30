// BF script VM leaf handlers and the BMD relocator (game/include/p3fes/game/script_vm.h). Phase 5:
// these replace the recompiled bodies of the four functions listed in game/replaced.txt; the
// recompiled bodies stay in the program under the __recomp symbols and tests/game/test_script_vm.cpp
// proves both agree on randomised task records and relocation tables.
//
// All four bodies are p3fes_handgen's register-faithful ones (faithfulness audit 2026-10-21: the earlier hand
// versions differed in scratch GPRs 3, faults only 1), made readable on 2026-10-21 (slice read_script): ScrTask
// offsets by name (scr::ofs, script_vm.h), block roles, ApplyRelocTable's shared fix-up block as the loop's tail.
// Every guest statement, frame, link, cycle charge (ADR-0013: the recompiled body's `ctx.cycles += N` blocks) and
// check point is the generated body's, in its order.
#include "p3fes/game/script_vm.h"

#include "p3fes/game/guest.h"
#include "p3fes/game/hg_cpu.h"

namespace p3fes::game {

namespace {
namespace ofs = scr::ofs;
}  // namespace

// 0x0035CF00 CodeFunc_Proc -- 24 bytes; leaf frame (no stack)
// Opcode PROC (sScrOpcodeTbl 0x69D3E0): the procedure marker; steps over itself (pc += 1) and returns 1 (next
// instruction). One block of 6 (lw / addiu / sw / li / jr / nop).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_Proc(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::enter, hg::lw, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    Gpr& task = a0;  // $a0: the ScrTask
    // 0x0035cf00
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, task, ofs::pc);  // task->pc += 1
    v0 = addiu(v0, 1);
    sw(v0, task, ofs::pc);
    v0 = 1;  // continue with the next instruction
}

// 0x0035D1D0 CodeFunc_Jmp -- 52 bytes; leaf frame (no stack)
// Opcode JUMP: pc = proc_labels[operand].insn, a jump to the start of procedure `operand` (no return address is
// pushed; CALL is CodeFunc_Call). Returns 1. One block of 13.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_Jmp(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::enter, hg::lh, hg::lw, hg::sll, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    Gpr& task = a0;  // $a0: the ScrTask
    // 0x0035d1d0
    enter(ctx, 13);  // entry check point + this block's cycles
    lw(v1, task, ofs::insn);  // operand = insn[pc].operand (s16)
    lw(v0, task, ofs::pc);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lh(v0, v0, ofs::operand);
    v1 = sll(v0, ofs::label_shift);  // pc = proc_labels[operand].insn (32-byte label records)
    lw(v0, task, ofs::proc_labels);
    v0 = addu(v1, v0);
    lw(v0, v0, ofs::label_insn);
    sw(v0, task, ofs::pc);
    v0 = 1;
}

// 0x0035D310 CodeFunc_Goto -- 52 bytes; leaf frame (no stack)
// Opcode GOTO: pc = jump_labels[operand].insn (section 1, the labels inside procedures). Returns 1. One block of
// 13: CodeFunc_Jmp's body over the jump-label table.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void CodeFunc_Goto(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::enter, hg::lh, hg::lw, hg::sll, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    Gpr& task = a0;  // $a0: the ScrTask
    // 0x0035d310
    enter(ctx, 13);  // entry check point + this block's cycles
    lw(v1, task, ofs::insn);  // operand = insn[pc].operand (s16)
    lw(v0, task, ofs::pc);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lh(v0, v0, ofs::operand);
    v1 = sll(v0, ofs::label_shift);  // pc = jump_labels[operand].insn
    lw(v0, task, ofs::jump_labels);
    v0 = addu(v1, v0);
    lw(v0, v0, ofs::label_insn);
    sw(v0, task, ofs::pc);
    v0 = 1;
}

// 0x0035AC90 ApplyRelocTable -- 240 bytes; leaf frame (no stack)
// ApplyRelocTable(u32* words /*$a0*/, u32 add /*$a1*/, const u8* table /*$a2*/, s32 len /*$a3*/): the BMD
// relocator (caller itfMesMngRelocateBmdOnce 0x3A5030). Walks the table bytes; each code moves the word cursor
// and fixes the word it lands on (+= add):
//   code & 1 == 0  -> advance code >> 1 words                                  (form 1, one byte)
//   code & 3 == 1  -> advance (code | next << 8) >> 2 words                    (form 2, two bytes)
//   code & 7 == 3  -> advance (code | next << 8 | next2 << 16) >> 3 words      (form 3, three bytes)
//   code & 7 == 7  -> fix the next (code >> 3) + 2 consecutive words           (a run; no separate fix-up)
// Blocks (recomp/generated): entry 3; loop test 0x35AD68 4 (+2 on exit); byte fetch 0x35AC9C 5; the three advance
// forms 3 / 3+7 / 3+3+10, each followed by the fix-up block 0x35AD54 5; the run form 3+3+5, then the inner test
// 0x35AD40 3 per evaluation (+2 on exit) and the inner body 0x35AD2C 5 per word. Back-edge check points sit on
// both loops, as in the generated code (each loop's test block comes first: the check precedes every iteration).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void ApplyRelocTable(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lbu, hg::lw, hg::sll, hg::slt,
          hg::sra, hg::subu, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    Gpr &word = a0, &add = a1, &table = a2, &len = a3;  // the arguments
    Gpr &cursor = v1, &code = t2;                       // the table cursor and the current code byte
    // 0x0035ac90
    enter(ctx, 3);  // entry check point + this block's cycles
    cursor = table;
    for (;;) {
        // 0x0035ad68: while (cursor - table < len)
        charge(ctx, 4);
        t0 = subu(cursor, table);
        t0 = slt(t0, len);
        if (t0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0035ac9c: code = *cursor++
        charge(ctx, 5);
        lbu(code, cursor, 0);
        cursor = addiu(cursor, 1);
        t0 = code & 0x1;
        if (t0 == 0) {
            // 0x0035acb0: form 1 -- advance code >> 1 words
            charge(ctx, 3);
            t0 = sra(code, 1);
        } else {
            // 0x0035acbc
            charge(ctx, 3);
            t0 = code & 0x2;
            if (t0 == 0) {
                // 0x0035acc8: form 2 -- advance (code | *cursor++ << 8) >> 2 words
                charge(ctx, 7);
                lbu(t0, cursor, 0);
                t0 = sll(t0, 8);
                t0 = code | t0;
                t0 = sra(t0, 2);
                cursor = addiu(cursor, 1);
            } else {
                // 0x0035ace4
                charge(ctx, 3);
                t0 = code & 0x4;
                if (t0 != 0) {
                    // 0x0035ad18: a run -- for (i = 0; i < (code >> 3) + 2; i++) *++word += add
                    charge(ctx, 5);
                    t0 = sra(code, 3);
                    t1 = addiu(t0, 2);
                    t2 = 0;  // the run counter (the code register is reused)
                    for (;;) {
                        // 0x0035ad40
                        charge(ctx, 3);
                        t0 = slt(t2, t1);
                        if (t0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0035ad2c
                        charge(ctx, 5);
                        word = addiu(word, 4);
                        lw(t0, word, 0);
                        t0 = addu(t0, add);
                        sw(t0, word, 0);
                        t2 = addiu(t2, 1);
                    }
                    // 0x0035ad4c: back to the loop test (a run has no fix-up)
                    charge(ctx, 2);
                    continue;
                }
                // 0x0035acf0: form 3 -- advance (code | cursor[0] << 8 | cursor[1] << 16) >> 3 words; cursor += 2
                charge(ctx, 10);
                lbu(t0, cursor, 1);
                t1 = sll(t0, 16);
                lbu(t0, cursor, 0);
                t0 = sll(t0, 8);
                t0 = code | t0;
                t0 = t1 | t0;
                t0 = sra(t0, 3);
                cursor = addiu(cursor, 2);
            }
        }
        // 0x0035ad54: the fix-up after an advance -- word += t0 words; *word += add
        charge(ctx, 5);
        t0 = sll(t0, 2);
        word = addu(word, t0);
        lw(t0, word, 0);
        t0 = addu(t0, add);
        sw(t0, word, 0);
    }
    // 0x0035ad78
    charge(ctx, 2);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (signatures from recomp/generated/functions.h) ---------
