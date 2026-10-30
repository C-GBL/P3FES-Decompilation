// BF script VM (Atlus scrTraceCode.c) and BMD message helpers, hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/18_script_vm.md; names are the IDA names in symbols/p3fes.sym, promoted on the master
// 2026-10-20 from symbols/deltas/script_vm.sym).
//
// The script task record (`ScrTask`, 252 bytes, H_Malloc'd by scrStartScript 0x35B570) is addressed
// through the layout below; the opcode handlers of the 35-entry table at 0x69D3E0 take its guest
// address in $a0 and return 1 (continue), 2 (yield this frame) or 0 (script ended). The COMM-side
// accessors (scrGet*/scrSet*) work on g_scrCurrentTask 0x7CE5A8, which CodeFunc_Comm sets before it
// calls a command.
#pragma once

#include "p3fes/ee_context.h"

#include <cstddef>

namespace p3fes::game {

// The script task record (18_script_vm.md section 3). Offsets are the ones the generated bodies use.
struct ScrTask {  // 252 bytes
    char name[24];     // +0x00 start procedure name
    s32 pc;            // +0x18 index of the current instruction word
    s32 sp;            // +0x1C stack slot count; pushes assert sp < 27, pops sp > 0 (K_Assert is a no-op in retail)
    s8 tags[28];       // +0x20 slot tags (scr::Tag); tags[27] = tag of the COMM return register
    u32 values[28];    // +0x3C slot values; values[27] = the COMM return register
    u32 image;         // +0xAC BF header
    u32 sections;      // +0xB0 section descriptors (header + 0x20; 16 bytes each, count at +8)
    u32 proc_labels;   // +0xB4 section 0: { char name[24]; u32 insn; u32 }[]
    u32 jump_labels;   // +0xB8 section 1, same 32-byte records
    u32 insn;          // +0xBC section 2: { u16 opcode; s16 operand } words
    u32 message_data;  // +0xC0 section 3 or 0
    u32 strings;       // +0xC4 section 4
    s32 start_proc;    // +0xC8
    s32 message_id;    // +0xCC itfMesMng handle, -1 none
    s32 frames;        // +0xD0 yields so far
    s32 cmd_timer;     // +0xD4 frames spent in the current COMM
    u32 owned_image;   // +0xD8 H_Malloc copy of the BF or 0
    u32 local_ints;    // +0xDC s32[header +0x14]
    u32 local_floats;  // +0xE0 f32[header +0x16]
    u32 process;       // +0xE4 dds3 process handle
    u32 prev;          // +0xE8 running-script list
    u32 next;          // +0xEC
    u32 user_data;     // +0xF0 scrSetUserData / scrGetUserData
    u8 unused[8];      // +0xF4
};
static_assert(sizeof(ScrTask) == 252);
static_assert(offsetof(ScrTask, tags) == 0x20 && offsetof(ScrTask, values) == 0x3C && offsetof(ScrTask, image) == 0xAC &&
              offsetof(ScrTask, strings) == 0xC4 && offsetof(ScrTask, local_ints) == 0xDC && offsetof(ScrTask, user_data) == 0xF0);

namespace scr {
// ScrTask field offsets (kept for the first replacements and the tests).
inline constexpr u32 kPc = offsetof(ScrTask, pc);
inline constexpr u32 kSp = offsetof(ScrTask, sp);
inline constexpr u32 kTags = offsetof(ScrTask, tags);
inline constexpr u32 kValues = offsetof(ScrTask, values);
inline constexpr u32 kSections = offsetof(ScrTask, sections);
inline constexpr u32 kProcLabels = offsetof(ScrTask, proc_labels);
inline constexpr u32 kJumpLabels = offsetof(ScrTask, jump_labels);
inline constexpr u32 kInsn = offsetof(ScrTask, insn);
inline constexpr u32 kStrings = offsetof(ScrTask, strings);
inline constexpr u32 kMessageId = offsetof(ScrTask, message_id);
inline constexpr u32 kCmdTimer = offsetof(ScrTask, cmd_timer);
inline constexpr u32 kLocalInts = offsetof(ScrTask, local_ints);
inline constexpr u32 kLocalFloats = offsetof(ScrTask, local_floats);
inline constexpr u32 kUserData = offsetof(ScrTask, user_data);
inline constexpr u32 kLabelInsn = 0x18;  // offset of the instruction index inside a 32-byte label record
inline constexpr u32 kSectionCount = 8;  // offset of the element count inside a 16-byte section descriptor
inline constexpr u32 kReturnSlot = 27;   // slot 27: the COMM return register (tags[27] / values[27])
inline constexpr s32 kStackSlots = 27;   // a push asserts sp < 27

// Slot tags. PushIX/PushIF push the value with tag 0/1; tags 2 and 3 (an index into g_scrGlobals) are
// accepted by every pop and by scrOperation but pushed by nothing in this build.
enum Tag : s8 {
    kTagInt = 0,
    kTagFloat = 1,
    kTagGlobalInt = 2,
    kTagGlobalFloat = 3,
    kTagReturnAddress = 4,  // CALL pushes the pc; END pops it
    kTagString = 5,         // PUSHSTR: a pointer into section 4
};

// scrOperation's operations (the second argument of the 12 CodeFunc_Add..CodeFunc_LE wrappers).
enum Op : u32 {
    kOpAdd = 0,
    kOpSub = 1,
    kOpMul = 2,
    kOpDiv = 3,
    kOpOr = 4,
    kOpAnd = 5,
    kOpEq = 6,
    kOpNeq = 7,
    kOpLess = 8,          // S:  lhs <  rhs
    kOpGreater = 9,       // L:  lhs >  rhs
    kOpLessEqual = 10,    // SE: lhs <= rhs
    kOpGreaterEqual = 11  // LE: lhs >= rhs
};

// Globals (derived from $gp = 0x7D2CF0; 18_script_vm.md section 2.3).
inline constexpr u32 kGlobalsPtr = 0x7CCA5Cu;     // g_scrGlobals -> 0x957C00: s32[256] ints, then f32 floats at +1024
inline constexpr u32 kGlobalFloats = 1024;        // byte offset of the float half of the globals block
inline constexpr u32 kCurrentTask = 0x7CE5A8u;    // g_scrCurrentTask (set by CodeFunc_Comm)
inline constexpr u32 kOpLhsInt = 0x7CE588u;       // scrOperation scratch: popped left operand (int path)
inline constexpr u32 kOpRhsInt = 0x7CE58Cu;       //   right operand
inline constexpr u32 kOpResultInt = 0x7CE590u;    //   integer result (also the result of a float comparison)
inline constexpr u32 kOpLhsFloat = 0x7CE594u;     //   left operand (float path)
inline constexpr u32 kOpRhsFloat = 0x7CE598u;     //   right operand
inline constexpr u32 kOpResultFloat = 0x7CE59Cu;  //   float result
inline constexpr u32 kOpLhsTag = 0x7CE5A0u;       //   tag of the left operand (sign-extended)
inline constexpr u32 kOpRhsTag = 0x7CE5A4u;       //   tag of the right operand
inline constexpr u32 kSourceFile = 0x69D1E8u;     // "scrTraceCode.c", the K_Assert/K_Abort file argument

// The same layout as instruction immediates, for the register-view (p3fes_handgen) bodies of script_ops.cpp,
// script_vm.cpp and script_vm2.cpp: `lw(v0, task, ofs::pc)` is `lw $v0, 0x18(task)`. A slot address is
// task + i (tags) or task + 4 * i (values), so `lb(v1, slot, ofs::tags - 1)` reads tags[i - 1] (the top when
// i = sp). The gp_* entries are the $gp-relative globals above ($gp = 0x7D2CF0).
namespace ofs {
inline constexpr s32 pc = 0x18, sp = 0x1C, tags = 0x20, values = 0x3C;
inline constexpr s32 ret_tag = 0x20 + 27;        // tags[27]: the COMM return register's tag
inline constexpr s32 ret_value = 0x3C + 4 * 27;  // values[27]: the COMM return register
inline constexpr s32 image = 0xAC, sections = 0xB0, proc_labels = 0xB4, jump_labels = 0xB8, insn = 0xBC,
                     message_data = 0xC0, strings = 0xC4, start_proc = 0xC8, message_id = 0xCC, frames = 0xD0,
                     cmd_timer = 0xD4, owned_image = 0xD8, local_ints = 0xDC, local_floats = 0xE0, process = 0xE4,
                     prev = 0xE8, next = 0xEC, user_data = 0xF0;
inline constexpr s32 opcode = 0, operand = 2;  // an instruction word { u16 opcode; s16 operand }
inline constexpr s32 label_insn = 0x18;        // a 32-byte label record's instruction index
inline constexpr unsigned label_shift = 5;     // label records are 32 bytes
inline constexpr s32 section1_count = 0x10 + 8;  // sections[1].element_count (the jump-label count)
inline constexpr s32 global_floats = 1024;       // the float half of g_scrGlobals
inline constexpr s32 gp_globals = -25236;        // 0x7CCA5C g_scrGlobals (pointer)
inline constexpr s32 gp_trace_flag = -19176;     // 0x7CE208 g_scrTraceFlag
inline constexpr s32 gp_op_lhs_int = -18280, gp_op_rhs_int = -18276, gp_op_result_int = -18272;  // 0x7CE588..
inline constexpr s32 gp_op_lhs_float = -18268, gp_op_rhs_float = -18264, gp_op_result_float = -18260;
inline constexpr s32 gp_op_lhs_tag = -18256, gp_op_rhs_tag = -18252;  // 0x7CE5A0 / 0x7CE5A4
inline constexpr s32 gp_current_task = -18248;                        // 0x7CE5A8 g_scrCurrentTask
static_assert(ret_tag == static_cast<s32>(offsetof(ScrTask, tags) + 27) && insn == static_cast<s32>(kInsn) &&
              user_data == static_cast<s32>(kUserData) && cmd_timer == static_cast<s32>(kCmdTimer));
static_assert(0x7D2CF0 + gp_globals == static_cast<s32>(kGlobalsPtr) &&
              0x7D2CF0 + gp_current_task == static_cast<s32>(kCurrentTask) &&
              0x7D2CF0 + gp_op_lhs_int == static_cast<s32>(kOpLhsInt) &&
              0x7D2CF0 + gp_op_rhs_tag == static_cast<s32>(kOpRhsTag));
}  // namespace ofs
}  // namespace scr

// --- opcode handlers (sScrOpcodeTbl 0x69D3E0; each returns 1 = next instruction) -------------------
// Every handler reads the operand as the sign-extended s16 at insn[pc] + 2 and scales it as the
// recompiled body does (32-bit wrap-around). "ints[i]" / "floats[i]" are the halves of g_scrGlobals.

void CodeFunc_PushI(EEContext& ctx);  // [register ABI] 0x35C300 PUSHI:   push insn[pc + 1], tag 0; pc += 2
void CodeFunc_PushS(EEContext& ctx);  // [register ABI] 0x35C3B0 PUSHIS:  push the s16 operand, tag 0
void CodeFunc_PushF(EEContext& ctx);  // [register ABI] 0x35C450 PUSHF:   push insn[pc + 1], tag 1; pc += 2
void CodeFunc_PushIX(EEContext& ctx);  // [register ABI] 0x35C500 PUSHIX:  push ints[operand], tag 0
void CodeFunc_PushIF(EEContext& ctx);  // [register ABI] 0x35C5B0 PUSHIF:  push floats[operand], tag 1
void CodeFunc_PushLIX(EEContext& ctx);  // [register ABI] 0x35C660 PUSHLIX: push local_ints[operand], tag 0
void CodeFunc_PushLFX(EEContext& ctx);  // [register ABI] 0x35C710 PUSHLFX: push local_floats[operand], tag 1
void CodeFunc_PushSTR(EEContext& ctx);  // [register ABI] 0x35C7C0 PUSHSTR: push strings + operand, tag 5
void CodeFunc_PushREG(EEContext& ctx);  // [register ABI] 0x35C870 PUSHREG: push slot 27 (tag and value as they are)
void CodeFunc_PopIX(EEContext& ctx);  // [register ABI] 0x35C900 POPIX:   ints[operand] = pop as int
void CodeFunc_PopFX(EEContext& ctx);  // [register ABI] 0x35CA70 POPFX:   floats[operand] = pop as float
void CodeFunc_PopLIX(EEContext& ctx);  // [register ABI] 0x35CC00 POPLIX:  local_ints[operand] = pop as int
void CodeFunc_PopLFX(EEContext& ctx);  // [register ABI] 0x35CD70 POPLFX:  local_floats[operand] = pop as float
void CodeFunc_Proc(EEContext& ctx);  // [register ABI] 0x35CF00 PROC:    pc += 1
void CodeFunc_End(EEContext& ctx);  // [register ABI] 0x35D040 END:     empty stack -> 0; else pc = pop + 1
void CodeFunc_Jmp(EEContext& ctx);  // [register ABI] 0x35D1D0 JUMP:    pc = proc_labels[operand].insn
void CodeFunc_Call(EEContext& ctx);  // [register ABI] 0x35D210 CALL:    push pc, tag 4; pc = proc_labels[operand].insn
void CodeFunc_Goto(EEContext& ctx);  // [register ABI] 0x35D310 GOTO:    pc = jump_labels[operand].insn
void CodeFunc_Add(EEContext& ctx);  // [register ABI] 0x35DFE0 ADD .. 0x35E810 LE: scrOperation(task, op); pc += 1
void CodeFunc_Sub(EEContext& ctx);  // [register ABI] 0x35E020
void CodeFunc_Mul(EEContext& ctx);  // [register ABI] 0x35E060
void CodeFunc_Div(EEContext& ctx);  // [register ABI] 0x35E0A0
void CodeFunc_Minus(EEContext& ctx);  // [register ABI] 0x35E0E0 MINUS:   negate the top slot in place (by tag)
void CodeFunc_Not(EEContext& ctx);  // [register ABI] 0x35E250 NOT:     push (pop == 0), tag 0
void CodeFunc_Or(EEContext& ctx);  // [register ABI] 0x35E650
void CodeFunc_And(EEContext& ctx);  // [register ABI] 0x35E690
void CodeFunc_Eq(EEContext& ctx);  // [register ABI] 0x35E6D0
void CodeFunc_Neq(EEContext& ctx);  // [register ABI] 0x35E710
void CodeFunc_S(EEContext& ctx);  // [register ABI] 0x35E750
void CodeFunc_L(EEContext& ctx);  // [register ABI] 0x35E790
void CodeFunc_SE(EEContext& ctx);  // [register ABI] 0x35E7D0
void CodeFunc_LE(EEContext& ctx);  // [register ABI] 0x35E810
void CodeFunc_IF(EEContext& ctx);  // [register ABI] 0x35E850 IF:      pop; zero -> pc = jump_labels[operand].insn, else pc += 1

// 0x35D350 scrOperation: pops the right operand's tag from slot sp-2 and the left's from sp-1, works in
// integers when both tags are 0 or 2 and in floats otherwise (ints are converted with cvt.s.w; a
// return-address or string tag aborts the pop and yields 0.0), then pushes the result: tag 0 for the
// integer operations and for every comparison, tag 1 for a float ADD/SUB/MUL/DIV. The top of the
// stack is the LEFT operand. `op` >= 12 pushes the stale result word (nothing is computed). Operands
// and results pass through the scratch words scr::kOp* exactly as the original did. $v0 is untouched.
void scrOperation(EEContext& ctx, u32 task_va, u32 op);

// --- COMM-side accessors on g_scrCurrentTask ----------------------------------------------------------
void scrSetIntReturnVal(EEContext& ctx);  // [register ABI] 0x35F060 slot 27 := value, tag 0
void scrSetFloatReturnVal(EEContext& ctx);  // [register ABI] 0x35F080 slot 27 := value, tag 1 ($f12)
void scrSetPC(EEContext& ctx);  // [register ABI] 0x35F120
s32 scrGetCmdTimer(EEContext& ctx);                          // 0x35F130
s32 scrGetMessageID(EEContext& ctx);                         // 0x35F140
u32 scrGetCurrent(EEContext& ctx);                           // 0x35F150 the task address itself
u32 scrGetUserData(EEContext& ctx);                          // 0x35F160
// 0x35F0A0: jump_labels[index].insn, asserting 0 <= index < section 1's element count (both no-ops in retail).
void scrGetLabelAddr(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// COMM arguments: argument i is slot sp - 1 - i, converted by tag like a pop (the stack is not popped;
// CodeFunc_Comm drops the arguments afterwards). scrGetFloatPara returns the float's bits ($f0);
// scrGetStrPara requires tag 5 and returns 0 (after the no-op K_Abort) for any other tag.
void scrGetIntPara(EEContext& ctx);  // [register ABI] 0x35ED20
void scrGetFloatPara(EEContext& ctx);  // [register ABI] 0x35EE60
void scrGetStrPara(EEContext& ctx);  // [register ABI] 0x35EFA0

// 0x35AC90 ApplyRelocTable: applies a BMD relocation table in place. `words_va`
// points at the first relocatable word (BMD +0x20), `add` is the value added to every pointer (the
// BMD base + 0x20), `reloc_va`/`reloc_len` the table (BMD header +0x10/+0x14). Encoding, from the
// instructions: low bit 0 -> advance (byte >> 1) words; bits 1:0 == 01 -> advance (u16 >> 2) words
// (second byte is the high part); bits 2:0 == 011 -> advance (u24 >> 3) words; bits 2:0 == 111 ->
// fix the next (byte >> 3) + 2 consecutive words. Each advance is followed by one fix-up.
void ApplyRelocTable(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

}  // namespace p3fes::game
