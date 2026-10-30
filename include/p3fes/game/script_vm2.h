// BF script VM, second wave (slice script_vm2): the interpreter loop, the per-frame task body, the BF
// section resolver, the procedure lookup, the dds3 process accessors the VM uses and the generic COMM
// functions of scrCommonCommand.c that neither allocate nor print, hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/18_script_vm.md sections 2.1, 2.4, 3, 4).
//
// Names are the IDA names of symbols/functions.json; the ones still sub_* carry, in brackets, the
// community hint name (symbols/hints, tge-pr4 / snaku) whose behaviour the body confirms, or our own
// proposal. The ScrTask layout and the scr:: constants come from script_vm.h (first wave).
//
// Every function keeps the recompiled body's contract: still-recompiled callees (and the already
// replaced ones) are reached through their generated entry points with the argument registers the
// original set (64-bit register copies stay 64-bit), so register pass-through ($v0 of a void function)
// is what the recompiled body produced.
//
// Not replaced (PHASE5_AGENT_BRIEF step 7: they reach the MW heap -- H_Malloc sub_191AF0 / H_Free
// sub_191A10, which run DIntr/EIntr syscalls -- or printf on their main path): scrCreateTaskFromHeader
// 0x35BB40, scrCreateTask 0x35BD50, dds3InitProcess sub_35AD80, dds3KillProcess sub_35ADB0,
// scrDestroyTask 0x35C200, scrCommand_SCR_KILL 0x35B390.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace scr2 {
// Atlus source-file strings (.rodata), the K_Assert/K_Abort file arguments.
inline constexpr u32 kFileScriptProcess = 0x69CFB0u;  // "scrScriptProcess.c"
inline constexpr u32 kFileCommonCommand = 0x69CEE0u;  // "scrCommonCommand.c"
inline constexpr u32 kFileTraceCode = 0x69D1E8u;      // "scrTraceCode.c"
// K_Abort messages and the trace format.
inline constexpr u32 kMsgInvalidScriptData = 0x69D060u;  // "invalid script data!!\n"
inline constexpr u32 kMsgInvalidType = 0x69D080u;        // "scrStartScript2(..) Invalid type!!\n"
inline constexpr u32 kMsgErrorScript = 0x69D1C0u;        // "scrScriptProcess(..) error script!\n"
inline constexpr u32 kMsgTrace = 0x69D470u;              // ">>>SCRIPT TRACE <0x%X>\n" (H_Dbprt format)

inline constexpr u32 kOpcodeTable = 0x69D3E0u;  // sScrOpcodeTbl: 35 x u32 handler addresses
inline constexpr s32 kOpcodeCount = 35;
inline constexpr u32 kTraceFlag = 0x7CE208u;  // g_scrTraceFlag ($gp - 0x4AE8): == 1 logs every instruction

// The BF header (FORMATS.md section 2): +8 'FLW0', +0x10 section count, +0x20 the 16-byte descriptors
// { u32 type, u32 element_size, u32 element_count, u32 offset }.
inline constexpr u32 kBfMagic = 8;
inline constexpr u32 kBfSectionCount = 0x10;
inline constexpr u32 kBfSections = 0x20;
inline constexpr u32 kSectionType = 0, kSectionElementCount = 8, kSectionOffset = 12, kSectionSize = 16;
enum SectionType : u32 {
    kSectionProcLabels = 0,
    kSectionJumpLabels = 1,
    kSectionInsns = 2,
    kSectionMessages = 3,  // taken only when element_count != 0
    kSectionStrings = 4,
};

// Pad words read by the COMM functions 19/20 (sub_35B1B0 / sub_35B1F0): u16 at 0x7E094E / 0x7E094C.
inline constexpr u32 kPadWordA = 0x7E094Eu;
inline constexpr u32 kPadWordB = 0x7E094Cu;
inline constexpr u32 kFlagCount = 0x1600u;  // BIT_ON / BIT_OFF assert arg0 < 0x1600 (unsigned)
inline constexpr s32 kSwitchLabels = 7;     // SWITCH(sel, l0..l6) asserts sel < 7
}  // namespace scr2

// --- the interpreter ----------------------------------------------------------------------------------
// 0x35EBF0: runs instructions of `task` until a handler yields (2: cmd_timer++ and frames++, returns 1)
// or the script ends (0: cmd_timer = 0, returns 2); a handler result of 1 clears cmd_timer, any other
// result loops on without clearing it. Opcodes outside 0..34 are asserted (no-op) and still dispatched.
// With g_scrTraceFlag == 1 every instruction is logged through H_Dbprt (sub_1052B0) first.
void scrTraceCode(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x35C270: the dds3 per-frame body: 2 (ended) -> -1 (process done), 1 -> 0, 0 -> K_Abort (no-op) and
// -1, anything else 0.
void scrScriptProcess(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void scrForceTraceCode(EEContext& ctx);  // [register ABI] 0x35C250: one synchronous scrTraceCode

// --- loading ------------------------------------------------------------------------------------------
// 0x35B930: checks 'FLW0' (K_Abort and 0 otherwise), resolves the section descriptors by type to
// absolute pointers (an unknown type aborts and returns 0; a later descriptor of the same type wins) and
// returns scrStartScript(image, image + 0x20, proc, jump, insn, messages, strings, start_proc).
void scrStartScript2(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void sub_35BD20(EEContext& ctx);  // [register ABI] 0x35BD20 scrStartScript2(image, 0) [scrStartScriptFirstPrcd]
// 0x35C090: index of the procedure named `name` in section 0 of `image` (strcmp), -1 when absent or
// when none of the +0x10 descriptors has type 0 (the first type-0 descriptor is taken).
void scrFindPrcdIdxByName(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void scrSetUserData(EEContext& ctx);  // 0x35C1A0: dds3GetProcessWorkData(a0)->user_data = a1

// --- dds3 process accessors (forward their argument registers unchanged to the kwln task system) ------
void sub_35ADD0(EEContext& ctx);              // [dds3ProcessExists]  kwlnTaskExists(a0)
void sub_35ADF0(EEContext& ctx);              // [dds3GetProcessTimer] kwlnTaskGetTimer(a0)
void dds3GetProcessWorkData(EEContext& ctx);  // 0x35AE10 kwlnTaskGetWorkData(a0)
void sub_35AE30(EEContext& ctx);              // [dds3SetProcessWorkData] kwlnTaskSetWorkData(a0, a1)

// --- COMM functions (sScrCommandTable ids in brackets; return 1 = done, 0 = run again next frame) -----
void scrCommand_BIT_CHK_regs(EEContext& ctx);  // [register ABI] [7]  return MT_Misc_BitChk(arg0)
void scrCommand_BIT_ON_regs(EEContext& ctx);  // [register ABI] [8]  assert arg0 < 0x1600; MT_Misc_BitOn(arg0)
void scrCommand_BIT_OFF_regs(EEContext& ctx);  // [register ABI] [9]  the same with MT_Misc_BitOff
void scrCommand_RAND_regs(EEContext& ctx);  // [register ABI] [10] return RpRandom() % (arg0 + 1) (divu)
void scrCommand_SYNC_regs(EEContext& ctx);  // [register ABI] [11] done once cmd_timer != 0
void scrCommand_WAIT_regs(EEContext& ctx);  // [register ABI] [12] done when arg0 <= 0 or cmd_timer >= arg0
void scrCommand_SWITCH_regs(EEContext& ctx);  // [register ABI] [15] pc = jump_labels[arg(sel + 1)] for sel >= 0, label >= 0
void sub_35B1B0_regs(EEContext& ctx);  // [register ABI] [19] return pad word 0x7E094E & arg0
void sub_35B1F0_regs(EEContext& ctx);  // [register ABI] [20] return pad word 0x7E094C & arg0
void sub_35B230_regs(EEContext& ctx);  // [register ABI] [21] reads three arguments, does nothing
u32 sub_35B270(EEContext& ctx);                // [22] returns 1
void sub_35B400_regs(EEContext& ctx);  // [register ABI] [25] done when process arg0 no longer exists [scrCommand_SCR_KILL_SYNC]
void scrCommand_SCR_EXISTS_regs(EEContext& ctx);  // [register ABI] [26] return dds3ProcessExists(arg0) != 0
void scrCommand_SCR_GET_TIMER_regs(EEContext& ctx);  // [register ABI] [27] return the process timer, 0 when it does not exist
void sub_35B520(EEContext& ctx);  // [46] return sqrt(float arg0) [scrCommand_SQRT]; $v0 is left by the callees

}  // namespace p3fes::game
