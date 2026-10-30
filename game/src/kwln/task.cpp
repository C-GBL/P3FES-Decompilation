// kwlnTask.c, the task kernel (game/include/p3fes/game/task.h), hand-decompiled from SLUS_216.21: list
// insertion and removal, the per-frame walk (kwlnTaskMain -> kwlnTaskUpdateAll -> kwlnTaskUpdate), task
// creation, destruction (single, sibling chain, with hierarchy, by name), the tree links, the flag helpers,
// the lookups and accessors. Phase 5: these replace the recompiled bodies listed in game/replaced.txt;
// tests/game/test_kwln_task.cpp runs each against its __recomp body.
//
// Virtual time per ADR-0013: the block costs are those of recomp/generated/fn_0005_001885f0_00199140.cpp
// (`ctx.cycles += N` lines), charged at the start of each block, before any call inside it, so that every
// callee reaches its check point at the same virtual time; `guest::backedge` stands where the recompiled
// loop checks.
//
// Register discipline (task.h): the original prologue spills, the s-registers and $ra are reproduced at every
// call, because the callbacks' frames and these frames are live on the stack; and every caller-saved register
// the original writes ($at, $v0/$v1, $a0..$a3, $t0..$t6) holds the original's value at every call and at the
// return, because game code reads some of them: a kwlnTaskExists caller in the boot path reads one of the
// list-walk temporaries it leaves behind (with only $v0 reproduced, M1 differs by two bytes of the sound
// command block 0x782B98), kwlnTaskDetachAllChildren starts from the $a1 its caller leaves, and an update
// callback that does not write $v0 returns the -1 the kernel loaded. The `lwr` helper is "lw into register".
//
// K_Assert and K_Abort (sub_19D3F0 / sub_19D400) are `jr $ra` in retail: an invalid state continues as the
// original did; printf (only on those paths), memset, memcpy, H_Malloc and H_Free stay recompiled and are
// called exactly where the original called them.
//
// Not replaced: kwlnTaskPrintRecursive 0x194750 / kwlnTaskPrintTrees 0x1948B0 (printf-only debug dumps).
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 21 of the 34 functions here are p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: faults only 15, callee frames 5, the hand version
// terminated the host on a random world 1); the others are the hand-written versions this header describes. The 21
// were made readable on 2026-10-22 (slice read_misc): KwlnTask fields by name (tk::, asserted against task.h's
// kOff*), the list variables as $gp offsets (kGp*), la / k_assert (misc_view.h) for the address pairs and K_Assert
// calls, named registers, block roles, and no goto left (state switches with a host `valid` flag, insertion and
// unlink blocks inside their search loops). Every guest statement, frame, link, cycle charge and check point is the
// generated body's, in its order on every path.
#include "p3fes/game/task.h"
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/misc_view.h"

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line)
void fn_sub_19D400_0019d400(p3fes::EEContext&);  // K_Abort(msg, file, line)
void fn_printf_005225a8(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_sub_191AF0_00191af0(p3fes::EEContext&);  // H_Malloc(size)
void fn_sub_191A10_00191a10(p3fes::EEContext&);  // H_Free(ptr)
// This file's own entry points, called the way the original called them (jal).
void fn_kwlnTaskRemoveFromList_001939d0(p3fes::EEContext&);
void fn_kwlnTaskAddToList_00193ba0(p3fes::EEContext&);
void fn_kwlnTaskUpdate_00193ec0(p3fes::EEContext&);
void fn_kwlnTaskUpdateAll_00194100(p3fes::EEContext&);
void fn_kwlnTaskDestroyHierarchy_001941f0(p3fes::EEContext&);
void fn_kwlnTaskDestroy_00194280(p3fes::EEContext&);
void fn_kwlnTaskSetFlagsRecursive_001943b0(p3fes::EEContext&);
void fn_kwlnTaskSetFlagsByMode_001944c0(p3fes::EEContext&);
void fn_kwlnTaskInit_00194c50(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskGetTaskByName_00195340(p3fes::EEContext&);
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);
void fn_kwlnTaskAddChild_00195550(p3fes::EEContext&);
void fn_kwlnTaskDetachParent_001955f0(p3fes::EEContext&);
void fn_kwlnTaskDetachAllChildren_00195690(p3fes::EEContext&);
void fn_kwlnGetFlags_00198600(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

using namespace kwln;
using guest::backedge;
using guest::charge;
namespace gen = recomp_gen;
using mview::k_assert;
using mview::la;

// --- named immediates of the register-level (p3fes_handgen) bodies --------------------------------------------
// KwlnTask field offsets as the load / store immediates (task.h KwlnTask, kOff*).
namespace tk {
inline constexpr s32 kNameLast = 0x17;  // u8: name[23], forced to 0
inline constexpr s32 kNameSum = 0x18;   // s32: the signed byte sum of the name
inline constexpr s32 kState = 0x1C;     // u32: the state nibble and the flags
inline constexpr s32 kPriority = 0x20;  // u32: list order (unsigned)
inline constexpr s32 k24 = 0x24;        // u32: cleared on start
inline constexpr s32 kTimer = 0x28;     // u32: frames run
inline constexpr s32 kStartWait = 0x2C; // s32: frames in the starting list
inline constexpr s32 kEndWait = 0x30;   // s32: frames in the ending list
inline constexpr s32 kUpdate = 0x34;    // the update callback
inline constexpr s32 kDestroy = 0x38;   // the destroy callback
inline constexpr s32 kWork = 0x3C;      // the work area
inline constexpr s32 kNext = 0x40;      // state list
inline constexpr s32 kPrev = 0x44;      // state list
inline constexpr s32 kPrev2 = 0x48;     // the prev written on insertion
inline constexpr s32 kParent = 0x4C;    // tree
inline constexpr s32 kChild = 0x50;     // tree: first child
inline constexpr s32 kSibling = 0x54;   // tree: next sibling
inline constexpr s32 kUnk58 = 0x58;     // u32[4], zeroed
static_assert(kNameSum == kOffNameSum && kState == kOffState && kPriority == kOffPriority && k24 == kOff24);
static_assert(kTimer == kOffTimer && kStartWait == kOffStartWait && kEndWait == kOffEndWait && kUpdate == kOffUpdate);
static_assert(kDestroy == kOffDestroy && kWork == kOffWork && kNext == kOffNext && kPrev == kOffPrev);
static_assert(kPrev2 == kOffPrev2 && kParent == kOffParent && kChild == kOffChild && kSibling == kOffSibling);
static_assert(kNameLast == 23 && kUnk58 + 16 == static_cast<s32>(kTaskSize));
}  // namespace tk
// The $gp-relative kernel variables (task.h ListVars) as the load / store immediates.
inline constexpr s32 kGpStartingHead = -0x4C8C, kGpStartingTail = -0x4C88, kGpStartingCount = -0x4C84;  // 0x7CE064
inline constexpr s32 kGpEndingHead = -0x4C80, kGpEndingTail = -0x4C7C, kGpEndingCount = -0x4C78;        // 0x7CE070
inline constexpr s32 kGpRunningHead = -0x4C74, kGpRunningTail = -0x4C70, kGpRunningCount = -0x4C6C;     // 0x7CE07C
static_assert(kGpStartingHead == kStartingList.head && kGpStartingTail == kStartingList.tail &&
              kGpStartingCount == kStartingList.count);
static_assert(kGpEndingHead == kEndingList.head && kGpEndingTail == kEndingList.tail &&
              kGpEndingCount == kEndingList.count);
static_assert(kGpRunningHead == kRunningList.head && kGpRunningTail == kRunningList.tail &&
              kGpRunningCount == kRunningList.count);
inline constexpr s32 kCountBound = 10001;  // AddToList: `slti at, count, 10001` before its K_Assert
static_assert(kCountBound == static_cast<s32>(kListCountLimit) + 1);

// `lw reg, va` into a register; returns the 32-bit value.
u32 lwr(EEContext& ctx, unsigned r, u32 va) {
    const u32 v = lw(ctx, va);
    setreg(ctx, r, v);
    return v;
}

// `jal K_Assert(kwlnTask.c, line)` / `jal K_Abort(msg, kwlnTask.c, line)` / `jal printf(str)` at `pc`.
void k_assert(EEContext& ctx, u32 pc, u32 line) {
    setreg(ctx, GPR_A0, kStrSourceFile);
    setreg(ctx, GPR_A1, line);
    jal(ctx, pc, &gen::fn_sub_19D3F0_0019d3f0);
}
void print(EEContext& ctx, u32 pc, u32 str) {
    setreg(ctx, GPR_A0, str);
    jal(ctx, pc, &gen::fn_printf_005225a8);
}
// `move a0, sN; jal fn` (the task pointers live in s-registers around every call).
void call_with_s(EEContext& ctx, unsigned s, u32 pc, rt::Fn fn) {
    setreg64(ctx, GPR_A0, reg64(ctx, s));
    jal(ctx, pc, fn);
}

// The compiler's state switch `li r,3; beq; li r,2; beq; li r,1; beq [; b default]`: one 3-cycle block per
// test, 2 more for the trailing branch to the default when there is one. `r` keeps the last constant tested.
// Returns 3, 2, 1 or 0.
u32 cascade(EEContext& ctx, u32 s, bool trailing_branch, unsigned r = GPR_V1) {
    for (u32 v = 3; v >= 1; --v) {
        charge(ctx, 3);
        setreg(ctx, r, v);
        if (s == v) return v;
    }
    if (trailing_branch) charge(ctx, 2);
    return 0;
}

// `lw v1, state; li v0, -16; and v0, v1, v0 [; ori v0, v0, s]; sw v0, state`: the state nibble rewritten.
void set_state_nibble(EEContext& ctx, u32 task, u32 s) {
    const u32 w = lwr(ctx, GPR_V1, task + kOffState);
    const u32 st = (w & ~kStateMask) | s;
    setreg(ctx, GPR_V0, st);
    sw(ctx, task + kOffState, st);
}

}  // namespace

// 0x001939D0 kwlnTaskRemoveFromList -- 464 bytes; frame 0x10: ra sp+0x0
// ------------------------------------------------------------------------------------------------------------
// 0x1939D0 kwlnTaskRemoveFromList(task): unlink from the list of its state (head/tail fixed up), clear its
// links and decrement the list's count. An invalid state K_Aborts (line 70) and returns.
// Leaves $v1 = the new count, $a0 = $a2 = the state nibble, $a1 = prev (when there was a next) or the nibble.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskRemoveFromList(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001939d0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, tk::kState);  // $a0: the task (from 0x193b20 on, its state nibble)
    a2 = v1 & kStateMask;
    // the state switch: 3 / 2 / 1 are lists, 0 and anything above 3 K_Abort
    bool valid = false;
    if (a2 != 0) {
        // 0x001939e8
        charge(ctx, 3);
        v1 = 3;
        valid = a2 == v1;
        if (!valid) {
            // 0x001939f4
            charge(ctx, 3);
            v1 = 2;
            valid = a2 == v1;
            if (!valid) {
                // 0x00193a00
                charge(ctx, 3);
                v1 = 1;
                valid = a2 == v1;
            }
        }
    }
    if (valid) {
        // 0x00193a30: prev->next = task->next, or the list head when it was first
        charge(ctx, 3);
        lw(a1, a0, tk::kPrev);
        if (a1 == 0) {
            // 0x00193a4c
            charge(ctx, 3);
            v1 = 3;
            if (a2 == v1) {
                // 0x00193a98
                charge(ctx, 2);
                lw(v1, a0, tk::kNext);
                sw(v1, gp, kGpEndingHead);
            } else {
                // 0x00193a58
                charge(ctx, 3);
                v1 = 2;
                if (a2 == v1) {
                    // 0x00193a88
                    charge(ctx, 4);
                    lw(v1, a0, tk::kNext);
                    sw(v1, gp, kGpRunningHead);
                } else {
                    // 0x00193a64
                    charge(ctx, 3);
                    v1 = 1;
                    if (a2 == v1) {
                        // 0x00193a78
                        charge(ctx, 4);
                        lw(v1, a0, tk::kNext);
                        sw(v1, gp, kGpStartingHead);
                    } else {
                        // 0x00193a70
                        charge(ctx, 2);
                    }
                }
            }
        } else {
            // 0x00193a3c
            charge(ctx, 4);
            lw(v1, a0, tk::kNext);
            sw(v1, a1, tk::kNext);
        }
        // 0x00193aa0: next->prev = task->prev (and next->prev2), or the list tail when it was last
        charge(ctx, 3);
        lw(v1, a0, tk::kNext);
        if (v1 == 0) {
            // 0x00193ac4
            charge(ctx, 5);
            lw(v1, a0, tk::kState);
            a1 = v1 & kStateMask;
            v1 = 3;
            if (a1 == v1) {
                // 0x00193b18
                charge(ctx, 2);
                lw(v1, a0, tk::kPrev);
                sw(v1, gp, kGpEndingTail);
            } else {
                // 0x00193ad8
                charge(ctx, 3);
                v1 = 2;
                if (a1 == v1) {
                    // 0x00193b08
                    charge(ctx, 4);
                    lw(v1, a0, tk::kPrev);
                    sw(v1, gp, kGpRunningTail);
                } else {
                    // 0x00193ae4
                    charge(ctx, 3);
                    v1 = 1;
                    if (a1 == v1) {
                        // 0x00193af8
                        charge(ctx, 4);
                        lw(v1, a0, tk::kPrev);
                        sw(v1, gp, kGpStartingTail);
                    } else {
                        // 0x00193af0
                        charge(ctx, 2);
                    }
                }
            }
        } else {
            // 0x00193aac
            charge(ctx, 6);
            lw(a1, a0, tk::kPrev);
            sw(a1, v1, tk::kPrev2);
            lw(v1, a0, tk::kNext);
            sw(a1, v1, tk::kPrev);
        }
        // 0x00193b20: clear the links, count-- of the list
        charge(ctx, 7);
        sw(zero, a0, tk::kNext);
        sw(zero, a0, tk::kPrev);
        lw(v1, a0, tk::kState);
        a0 = v1 & kStateMask;
        v1 = 3;
        if (a0 == v1) {
            // 0x00193b84
            charge(ctx, 3);
            lw(v1, gp, kGpEndingCount);
            v1 = addiu(v1, -1);
            sw(v1, gp, kGpEndingCount);
        } else {
            // 0x00193b3c
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                // 0x00193b70
                charge(ctx, 5);
                lw(v1, gp, kGpRunningCount);
                v1 = addiu(v1, -1);
                sw(v1, gp, kGpRunningCount);
            } else {
                // 0x00193b48
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    // 0x00193b5c
                    charge(ctx, 5);
                    lw(v1, gp, kGpStartingCount);
                    v1 = addiu(v1, -1);
                    sw(v1, gp, kGpStartingCount);
                } else {
                    // 0x00193b54
                    charge(ctx, 2);
                }
            }
        }
        // 0x00193b90 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00193a0c: K_Abort("Process stat Invalid!!", "kwlnTask.c", 70) -- `jr $ra` in retail
    charge(ctx, 9);
    la(a0, kStrStatInvalid);  // "Process stat Invalid!!"
    la(a1, kStrSourceFile);  // "kwlnTask.c"
    a2 = 70;
    jal(ctx, 0x193A20u, gen::fn_sub_19D400_0019d400);
    // 0x00193b90 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00193BA0 kwlnTaskAddToList -- 796 bytes; frame 0x10: ra sp+0x0
// 0x193BA0 kwlnTaskAddToList(task): insert into the list of its state before the first task of a strictly
// greater (unsigned) priority, so equal priorities run in creation order; count++ with an assertion at
// 10,001 (lines 226/230/234). Note that +0x48 receives the new prev only on insertion.
// Leaves $at = (count < 10001), $v1 = the new count, $a0 = the nibble, $a2 = the entry nibble, $a3 = the
// list cursor (0 when appended), $a1 = the cursor's priority / the nibble / untouched (empty list).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskAddToList(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd, hg::slti,
          hg::sltu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00193ba0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, tk::kState);  // $a0: the task (from 0x193de4 on, its state nibble)
    a2 = v1 & kStateMask;
    // the state switch: the head of list 3 / 2 / 1 into $a3 (the cursor); 0 and anything above 3 K_Abort
    bool valid = false;
    if (a2 != 0) {
        // 0x00193bb8
        charge(ctx, 3);
        v1 = 3;
        if (a2 != v1) {
            // 0x00193bc4
            charge(ctx, 3);
            v1 = 2;
            if (a2 == v1) {
                // 0x00193bf0
                charge(ctx, 3);
                lw(a3, gp, kGpRunningHead);
                valid = true;
            } else {
                // 0x00193bd0
                charge(ctx, 3);
                v1 = 1;
                if (a2 != v1) {
                    // 0x00193bdc
                    charge(ctx, 2);
                } else {
                    // 0x00193be4
                    charge(ctx, 3);
                    lw(a3, gp, kGpStartingHead);
                    valid = true;
                }
            }
        } else {
            // 0x00193bfc
            charge(ctx, 3);
            lw(a3, gp, kGpEndingHead);
            valid = true;
        }
    }
    if (valid) {
        // 0x00193c2c
        charge(ctx, 2);
        if (a3 != 0) {
            // walk to the first task of a strictly greater (unsigned) priority
            for (;;) {
                // 0x00193d44
                charge(ctx, 2);
                if (a3 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00193c9c
                charge(ctx, 5);
                lw(a1, a3, tk::kPriority);
                lw(v1, a0, tk::kPriority);
                at = sltu(v1, a1);
                if (at != 0) {
                    // 0x00193cb0: insert the task before the cursor (or as the new head)
                    charge(ctx, 3);
                    lw(v1, a3, tk::kPrev);
                    if (v1 == 0) {
                        // 0x00193ce0
                        charge(ctx, 3);
                        v1 = 3;
                        if (a2 == v1) {
                            // 0x00193d24
                            charge(ctx, 1);
                            sw(a0, gp, kGpEndingHead);
                        } else {
                            // 0x00193cec
                            charge(ctx, 3);
                            v1 = 2;
                            if (a2 == v1) {
                                // 0x00193d18
                                charge(ctx, 3);
                                sw(a0, gp, kGpRunningHead);
                            } else {
                                // 0x00193cf8
                                charge(ctx, 3);
                                v1 = 1;
                                if (a2 == v1) {
                                    // 0x00193d0c
                                    charge(ctx, 3);
                                    sw(a0, gp, kGpStartingHead);
                                } else {
                                    // 0x00193d04
                                    charge(ctx, 2);
                                }
                            }
                        }
                        // 0x00193d28
                        charge(ctx, 6);
                        sw(zero, a0, tk::kPrev);
                        sw(a3, a0, tk::kNext);
                        sw(a0, a3, tk::kPrev2);
                        sw(a0, a3, tk::kPrev);
                    } else {
                        // 0x00193cbc
                        charge(ctx, 9);
                        sw(a0, v1, tk::kNext);
                        lw(v1, a3, tk::kPrev);
                        sw(v1, a0, tk::kPrev2);
                        sw(v1, a0, tk::kPrev);
                        sw(a3, a0, tk::kNext);
                        sw(a0, a3, tk::kPrev2);
                        sw(a0, a3, tk::kPrev);
                    }
                    break;
                }
                // 0x00193d40
                charge(ctx, 1);
                lw(a3, a3, tk::kNext);
            }
            // 0x00193d4c: none greater: append at the tail
            charge(ctx, 2);
            if (a3 == 0) {
                // 0x00193d54
                charge(ctx, 5);
                lw(v1, a0, tk::kState);
                a1 = v1 & kStateMask;
                v1 = 3;
                if (a1 == v1) {
                    // 0x00193dc8
                    charge(ctx, 6);
                    lw(v1, gp, kGpEndingTail);
                    sw(a0, v1, tk::kNext);
                    lw(v1, gp, kGpEndingTail);
                    sw(v1, a0, tk::kPrev2);
                    sw(v1, a0, tk::kPrev);
                    sw(a0, gp, kGpEndingTail);
                } else {
                    // 0x00193d68
                    charge(ctx, 3);
                    v1 = 2;
                    if (a1 == v1) {
                        // 0x00193da8
                        charge(ctx, 8);
                        lw(v1, gp, kGpRunningTail);
                        sw(a0, v1, tk::kNext);
                        lw(v1, gp, kGpRunningTail);
                        sw(v1, a0, tk::kPrev2);
                        sw(v1, a0, tk::kPrev);
                        sw(a0, gp, kGpRunningTail);
                    } else {
                        // 0x00193d74
                        charge(ctx, 3);
                        v1 = 1;
                        if (a1 == v1) {
                            // 0x00193d88
                            charge(ctx, 8);
                            lw(v1, gp, kGpStartingTail);
                            sw(a0, v1, tk::kNext);
                            lw(v1, gp, kGpStartingTail);
                            sw(v1, a0, tk::kPrev2);
                            sw(v1, a0, tk::kPrev);
                            sw(a0, gp, kGpStartingTail);
                        } else {
                            // 0x00193d80
                            charge(ctx, 2);
                        }
                    }
                }
                // 0x00193de0
                charge(ctx, 1);
                sw(zero, a0, tk::kNext);
            }
        } else {
            // 0x00193c34
            charge(ctx, 3);
            v1 = 3;
            if (a2 == v1) {
                // 0x00193c80
                charge(ctx, 2);
                sw(a0, gp, kGpEndingHead);
                sw(a0, gp, kGpEndingTail);
            } else {
                // 0x00193c40
                charge(ctx, 3);
                v1 = 2;
                if (a2 == v1) {
                    // 0x00193c70
                    charge(ctx, 4);
                    sw(a0, gp, kGpRunningHead);
                    sw(a0, gp, kGpRunningTail);
                } else {
                    // 0x00193c4c
                    charge(ctx, 3);
                    v1 = 1;
                    if (a2 == v1) {
                        // 0x00193c60
                        charge(ctx, 4);
                        sw(a0, gp, kGpStartingHead);
                        sw(a0, gp, kGpStartingTail);
                    } else {
                        // 0x00193c58
                        charge(ctx, 2);
                    }
                }
            }
            // 0x00193c88
            charge(ctx, 5);
            sw(zero, a0, tk::kPrev2);
            sw(zero, a0, tk::kPrev);
            sw(zero, a0, tk::kNext);
        }
        // 0x00193de4
        charge(ctx, 5);
        lw(v1, a0, tk::kState);
        a0 = v1 & kStateMask;
        v1 = 3;
        if (a0 == v1) {
            // 0x00193e80
            charge(ctx, 6);
            lw(v1, gp, kGpEndingCount);
            v1 = addiu(v1, 1);
            sw(v1, gp, kGpEndingCount);
            at = slti(v1, kCountBound);  // asserted: count <= 10000
            if (at == 0) {
                // 0x00193e98
                charge(ctx, 5);
                k_assert(a0, a1, 0x193EA4u, kStrSourceFile, 234);  // K_Assert(file, line): a no-op in retail
            }
        } else {
            // 0x00193df8
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                // 0x00193e4c
                charge(ctx, 6);
                lw(v1, gp, kGpRunningCount);
                v1 = addiu(v1, 1);
                sw(v1, gp, kGpRunningCount);
                at = slti(v1, kCountBound);  // asserted: count <= 10000
                if (at == 0) {
                    // 0x00193e64
                    charge(ctx, 7);
                    k_assert(a0, a1, 0x193E70u, kStrSourceFile, 230);  // K_Assert(file, line): a no-op in retail
                }
            } else {
                // 0x00193e04
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    // 0x00193e18
                    charge(ctx, 6);
                    lw(v1, gp, kGpStartingCount);
                    v1 = addiu(v1, 1);
                    sw(v1, gp, kGpStartingCount);
                    at = slti(v1, kCountBound);  // asserted: count <= 10000
                    if (at == 0) {
                        // 0x00193e30
                        charge(ctx, 7);
                        k_assert(a0, a1, 0x193E3Cu, kStrSourceFile, 226);  // K_Assert(file, line): a no-op in retail
                    }
                } else {
                    // 0x00193e10
                    charge(ctx, 2);
                }
            }
        }
        // 0x00193eac (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00193c08: K_Abort("Process stat Invalid!!", "kwlnTask.c", 143) -- `jr $ra` in retail
    charge(ctx, 9);
    la(a0, kStrStatInvalid);  // "Process stat Invalid!!"
    la(a1, kStrSourceFile);  // "kwlnTask.c"
    a2 = 143;
    jal(ctx, 0x193C1Cu, gen::fn_sub_19D400_0019d400);
    // 0x00193eac (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00193EC0 kwlnTaskUpdate -- 576 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x193EC0 kwlnTaskUpdate(task): 1 = keep it in the walk, 0 = it ended. Skipped (1) when kwlnGetFlags has
// bit 30/31 and the priority is in 0x816..0x1CE5, when pause word A is set and it is in 0x833..0x103D,
// when pause word B is set and it is in 0x1064..0x1CD9, or when the task has the paused flag. Otherwise
// it becomes the updating task, gets gPads (neutral sticks when flag 0x10, else a copy of gWorkPads), and
// its update callback runs: a non-zero result replaces the callback, -1 on a running task destroys it and
// its children (0), a task whose whole state word is then 3 returns 0, anything else counts a frame (+0x28).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskUpdate(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::jalr, hg::ld, hg::lq,
          hg::lui, hg::lw, hg::sb, hg::sd, hg::sh, hg::si, hg::sll, hg::slti, hg::sltiu, hg::sq, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // the task (from $a0)
    // 0x00193ec0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(task, sp, 0x0);
    task = a0;
    jal(ctx, 0x193ED0u, gen::fn_kwlnGetFlags_00198600);
    v1 = lui(0xC000);
    v0 = v0 & v1;
    if (v0 != 0) {
        // 0x00193ee8: kwlnGetFlags bit 30/31: skip priorities 0x816..0x1CE5
        charge(ctx, 4);
        lw(v1, task, tk::kPriority);
        v0 = sltiu(v1, 2070);
        if (v0 == 0) {
            // 0x00193ef8
            charge(ctx, 3);
            at = sltiu(v1, 7398);
            if (at != 0) {
                // 0x00193f04: skipped, keep it in the walk (1)
                charge(ctx, 3);
                v0 = 1;
                // 0x001940ec (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(task, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
        }
    }
    // 0x00193f10: pause word A: skip priorities 0x833..0x103D
    charge(ctx, 3);
    lw(v0, gp, kGpPauseBandA);
    if (v0 != 0) {
        // 0x00193f1c
        charge(ctx, 4);
        lw(v1, task, tk::kPriority);
        v0 = sltiu(v1, 2099);
        if (v0 == 0) {
            // 0x00193f2c
            charge(ctx, 3);
            at = sltiu(v1, 4158);
            if (at != 0) {
                // 0x00193f38: skipped (1)
                charge(ctx, 3);
                v0 = 1;
                // 0x001940ec (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(task, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
        }
    }
    // 0x00193f44: pause word B: skip priorities 0x1064..0x1CD9
    charge(ctx, 3);
    lw(v0, gp, kGpPauseBandB);
    if (v0 != 0) {
        // 0x00193f50
        charge(ctx, 4);
        lw(v1, task, tk::kPriority);
        v0 = sltiu(v1, 4196);
        if (v0 == 0) {
            // 0x00193f60
            charge(ctx, 3);
            at = sltiu(v1, 7386);
            if (at != 0) {
                // 0x00193f6c: skipped (1)
                charge(ctx, 3);
                v0 = 1;
                // 0x001940ec (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(task, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
        }
    }
    // 0x00193f78: the paused flag skips the task
    charge(ctx, 4);
    lw(v0, task, tk::kState);
    v0 = v0 & kFlagPaused;
    if (v0 == 0) {
        // 0x00193f94: it becomes the updating task; gPads = neutral pads or a copy of gWorkPads
        charge(ctx, 5);
        sw(task, gp, kGpUpdatingTask);
        lw(v0, task, tk::kState);
        v0 = v0 & kFlagNeutralPads;
        if (v0 == 0) {
            // 0x00194024: memcpy(gPads, gWorkPads, 108)
            charge(ctx, 7);
            la(a0, kPads);
            la(a1, kWorkPads);
            a2 = kPadsSize;
            jal(ctx, 0x194038u, gen::fn_memcpy_00521250);
        } else {
            // 0x00193fa8: memset(gPads, 0, 108), then the analog fields of both 54-byte records = 0x80 (centred)
            charge(ctx, 12);
            la(a0, kPads);
            a1 = 0;
            a2 = kPadsSize;
            jal(ctx, 0x193FB8u, gen::fn_memset_00521408);
            a2 = 0;  // the pad index
            la(a0, kPads);
            v1 = 128;
            for (;;) {
                // 0x00194010: while (pad < 2)
                charge(ctx, 3);
                v0 = slti(a2, 2);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00193fd8: v0 = &gPads[pad] (pad * 54, as ((pad * 9) * 4 - pad * 9) * 2)
                charge(ctx, 14);
                v0 = sll(a2, 3);
                a1 = addu(v0, a2);
                v0 = sll(a1, 2);
                v0 = subu(v0, a1);
                v0 = sll(v0, 1);
                v0 = addu(a0, v0);
                sh(v1, v0, 22);
                sh(v1, v0, 24);
                sh(v1, v0, 28);
                sb(v1, v0, 30);
                sb(v1, v0, 31);
                sb(v1, v0, 32);
                sb(v1, v0, 33);
                a2 = addiu(a2, 1);
            }
            // 0x0019401c
            charge(ctx, 2);
        }
        // 0x00194040: the update callback (none, or -1: just count the frame)
        charge(ctx, 3);
        lw(v1, task, tk::kUpdate);
        if (v1 != 0) {
            // 0x0019404c
            charge(ctx, 3);
            v0 = si(-1);
            if (v1 != v0) {
                // 0x00194058: v0 = update(task); a non-zero result becomes the next update callback
                charge(ctx, 5);
                a0 = task;
                jalr(ctx, 0x19405Cu, v1.u());
                if (v0 != 0) {
                    // 0x0019406c
                    charge(ctx, 1);
                    sw(v0, task, tk::kUpdate);
                }
                // 0x00194070
                charge(ctx, 3);
                v1 = si(-1);
                if (v0 == v1) {
                    // 0x0019407c: -1 finishes a running task: destroy it and its children, 0
                    charge(ctx, 5);
                    lw(v0, task, tk::kState);
                    v1 = v0 & kStateMask;
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x00194090
                        charge(ctx, 10);
                        a0 = task;
                        jal(ctx, 0x194094u, gen::fn_kwlnTaskDestroy_00194280);
                        lw(a0, task, tk::kChild);
                        jal(ctx, 0x1940A0u, gen::fn_kwlnTaskDestroyHierarchy_001941f0);
                        sw(zero, gp, kGpUpdatingTask);
                        v0 = 0;
                        // 0x001940ec (the shared epilogue, written out on this path)
                        charge(ctx, 5);
                        ld(ra, sp, 0x10);
                        lq(task, sp, 0x0);
                        sp = addiu(sp, 0x20);
                        return;
                    }
                }
                // 0x001940b8: a task whose whole state word is 3 (ending, no flags) has ended: 0
                charge(ctx, 4);
                lw(v1, task, tk::kState);
                v0 = 3;
                if (v1 == v0) {
                    // 0x001940c8
                    charge(ctx, 4);
                    sw(zero, gp, kGpUpdatingTask);
                    v0 = 0;
                    // 0x001940ec (the shared epilogue, written out on this path)
                    charge(ctx, 5);
                    ld(ra, sp, 0x10);
                    lq(task, sp, 0x0);
                    sp = addiu(sp, 0x20);
                    return;
                }
            }
        }
        // 0x001940d8: timer++, no updating task, keep it in the walk (1)
        charge(ctx, 5);
        lw(v0, task, tk::kTimer);
        v0 = addiu(v0, 1);
        sw(v0, task, tk::kTimer);
        sw(zero, gp, kGpUpdatingTask);
        v0 = 1;
    } else {
        // 0x00193f88: paused (1)
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001940ec (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(task, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00194100 kwlnTaskUpdateAll -- 228 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x194100 kwlnTaskUpdateAll(): the per-frame walk of the running list in priority order. The successor is
// read after the update, so a task may create or move others. When a task ends (Update 0) the walk resumes
// after its predecessor -- read before the update -- skipping predecessors that are themselves ending
// (state 3) back to the first live one; a chain of ending tasks up to the head leaves the last one's +0x48,
// and no predecessor at all restarts from the head.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskUpdateAll(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sltu,
          hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s1;  // the walk cursor
    Gpr& prev = s0;  // its predecessor, read before the update
    // 0x00194100
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(task, sp, 0x10);
    sq(prev, sp, 0x0);
    lw(task, gp, kGpRunningHead);
    if (task != 0) {
        // 0x0019411c
        charge(ctx, 2);
        for (;;) {
            // 0x001941c4
            charge(ctx, 2);
            if (task == 0) {
                break;
            }
            backedge(ctx);
            // 0x00194124: prev = task->prev; kwlnTaskUpdate(task)
            charge(ctx, 6);
            lw(prev, task, tk::kPrev);
            a0 = task;
            jal(ctx, 0x19412Cu, gen::fn_kwlnTaskUpdate_00193ec0);
            if (v0 == 0) {
                // 0x00194148: it ended
                charge(ctx, 2);
                if (prev == 0) {
                    // 0x001941c0
                    charge(ctx, 1);
                    lw(task, gp, kGpRunningHead);
                } else {
                    // 0x00194150: step back over predecessors that are themselves ending (state 3)
                    charge(ctx, 3);
                    v1 = 3;
                    for (;;) {
                        // 0x00194180: while (prev != 0 && (prev->state & 0xF) == 3)
                        charge(ctx, 4);
                        a0 = sltu(0, prev);
                        a0 = a0 ^ 0x1;
                        if (a0 == 0) {
                            // 0x00194190
                            charge(ctx, 4);
                            lw(a0, prev, tk::kState);
                            a0 = a0 & kStateMask;
                            if (a0 == v1) {
                                backedge(ctx);
                                // 0x0019415c
                                charge(ctx, 3);
                                lw(a0, prev, tk::kPrev);
                                if (a0 == 0) {
                                    // 0x00194174: an ending chain up to the head: its +0x48 (prev2)
                                    charge(ctx, 3);
                                    lw(prev, prev, tk::kPrev2);
                                    break;
                                }
                                // 0x00194168
                                charge(ctx, 3);
                                prev = a0;
                                continue;
                            }
                        }
                        break;
                    }
                    // 0x001941a0: resume after prev, or from the head when there is none
                    charge(ctx, 2);
                    if (prev == 0) {
                        // 0x001941b4
                        charge(ctx, 3);
                        lw(task, gp, kGpRunningHead);
                    } else {
                        // 0x001941a8
                        charge(ctx, 3);
                        lw(task, prev, tk::kNext);
                    }
                }
            } else {
                // 0x0019413c
                charge(ctx, 3);
                lw(task, task, tk::kNext);
            }
        }
    }
    // 0x001941cc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(task, sp, 0x10);
    lq(prev, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001941F0 kwlnTaskDestroyHierarchy -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x1941F0 kwlnTaskDestroyHierarchy(first): for `first` and each of its next siblings, destroy the
// children's subtrees and the children (kwlnTaskDestroy each), then the task itself.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskDestroyHierarchy(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s1;  // the sibling chain from $a0
    Gpr& child = s0;  // the task's children
    // 0x001941f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(task, sp, 0x10);
    sq(child, sp, 0x0);
    if (a0 != 0) {
        // 0x00194208: the sibling chain from $a0
        charge(ctx, 3);
        task = a0;
        for (;;) {
            // 0x0019425c: while (task)
            charge(ctx, 2);
            if (task == 0) {
                break;
            }
            backedge(ctx);
            // 0x00194214: its children
            charge(ctx, 3);
            lw(child, task, tk::kChild);
            if (child != 0) {
                // 0x00194220
                charge(ctx, 2);
                for (;;) {
                    // 0x00194244: while (child)
                    charge(ctx, 2);
                    if (child == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00194228: kwlnTaskDestroyHierarchy(child->child); kwlnTaskDestroy(child); child = child->sibling
                    charge(ctx, 7);
                    lw(a0, child, tk::kChild);
                    jal(ctx, 0x19422Cu, gen::fn_kwlnTaskDestroyHierarchy_001941f0);
                    a0 = child;
                    jal(ctx, 0x194238u, gen::fn_kwlnTaskDestroy_00194280);
                    lw(child, child, tk::kSibling);
                }
            }
            // 0x0019424c: kwlnTaskDestroy(task); task = task->sibling
            charge(ctx, 4);
            a0 = task;
            jal(ctx, 0x194250u, gen::fn_kwlnTaskDestroy_00194280);
            lw(task, task, tk::kSibling);
        }
    }
    // 0x00194264 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(task, sp, 0x10);
    lq(child, sp, 0x0);
    sp = addiu(sp, 0x30);
}

namespace {
// The retirement common to kwlnTaskDestroy (end_wait 0), its copy in kwlnTaskDestroyWithHierarchy and
// kwlnTaskMain's ending walk, after the cost of its first block is charged: unlink, the destroy callback
// ($v0 = the callback across the jalr), state nibble 0, out of the tree, H_Free. `pcs` are the five jal/jalr
// sites in order (Remove, the callback, DetachParent, DetachAllChildren, H_Free).
void retire(EEContext& ctx, u32 task, const u32 (&pcs)[5]) {
    call_with_s(ctx, GPR_S0, pcs[0], &gen::fn_kwlnTaskRemoveFromList_001939d0);
    const u32 cb = lwr(ctx, GPR_V0, task + kOffDestroy);
    if (cb != 0) {
        charge(ctx, 3);
        setreg64(ctx, GPR_A0, reg64(ctx, GPR_S0));
        jalr(ctx, pcs[1], cb);
    }
    charge(ctx, 13);
    set_state_nibble(ctx, task, 0);
    call_with_s(ctx, GPR_S0, pcs[2], &gen::fn_kwlnTaskDetachParent_001955f0);
    call_with_s(ctx, GPR_S0, pcs[3], &gen::fn_kwlnTaskDetachAllChildren_00195690);
    call_with_s(ctx, GPR_S0, pcs[4], &gen::fn_sub_191A10_00191a10);
}
}  // namespace

// 0x00194280 kwlnTaskDestroy -- 292 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x194280 kwlnTaskDestroy(task): a starting or running task moves to the ending list (state 3); with
// end_wait 0 it is retired at once: unlinked, destroy callback, state 0, detached from the tree, H_Free.
// An ending task is left alone; state 0 or > 3 prints "Process stat Invalid!!" and K_Asserts (line 574).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskDestroy(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::jalr, hg::ld, hg::lq, hg::lw, hg::sd, hg::si,
          hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // the task (from $a0)
    // 0x00194280
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(task, sp, 0x0);
    task = a0;
    lw(v1, a0, tk::kState);
    a0 = v1 & kStateMask;
    // the state switch: 3 is left alone, 2 / 1 move to the ending list, 0 and anything above 3 are invalid
    bool valid = false;
    if (a0 != 0) {
        // 0x001942a0
        charge(ctx, 3);
        v1 = 3;
        if (a0 == v1) {
            // 0x001942cc: already ending
            charge(ctx, 2);
            valid = true;
        } else {
            // 0x001942ac
            charge(ctx, 3);
            v0 = 2;
            valid = a0 == v0;
            if (!valid) {
                // 0x001942b8
                charge(ctx, 3);
                v0 = 1;
                valid = a0 == v0;
                if (!valid) {
                    // 0x001942c4
                    charge(ctx, 2);
                }
            }
            if (valid) {
                // 0x00194300: unlink, state = 3 (ending), relink into the ending list
                charge(ctx, 14);
                a0 = task;
                jal(ctx, 0x194304u, gen::fn_kwlnTaskRemoveFromList_001939d0);
                lw(v1, task, tk::kState);
                v0 = si(-16);  // ~kStateMask
                v0 = v1 & v0;
                v0 = v0 | kStateEnding;
                sw(v0, task, tk::kState);
                a0 = task;
                jal(ctx, 0x194324u, gen::fn_kwlnTaskAddToList_00193ba0);
                lw(v1, task, tk::kEndWait);
                if (v1 == 0) {
                    // 0x00194338: end_wait 0: retire at once -- unlink, the destroy callback, state 0, out of the
                    // tree, H_Free
                    charge(ctx, 6);
                    a0 = task;
                    jal(ctx, 0x19433Cu, gen::fn_kwlnTaskRemoveFromList_001939d0);
                    lw(v0, task, tk::kDestroy);
                    if (v0 != 0) {
                        // 0x00194350: destroy(task)
                        charge(ctx, 3);
                        a0 = task;
                        jalr(ctx, 0x194354u, v0.u());
                    }
                    // 0x0019435c
                    charge(ctx, 13);
                    lw(v1, task, tk::kState);
                    v0 = si(-16);  // ~kStateMask
                    v0 = v1 & v0;
                    sw(v0, task, tk::kState);
                    a0 = task;
                    jal(ctx, 0x194370u, gen::fn_kwlnTaskDetachParent_001955f0);
                    a0 = task;
                    jal(ctx, 0x19437Cu, gen::fn_kwlnTaskDetachAllChildren_00195690);
                    a0 = task;
                    jal(ctx, 0x194388u, gen::fn_sub_191A10_00191a10);  // H_Free(task)
                }
            }
        }
    }
    if (valid) {
        // 0x00194390 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(task, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x001942d4: printf("Process stat Invalid!!\n"); K_Assert("kwlnTask.c", 574)
    charge(ctx, 11);
    la(a0, kStrStatInvalidNl);  // "Process stat Invalid!!\n"
    jal(ctx, 0x1942DCu, gen::fn_printf_005225a8);
    k_assert(a0, a1, 0x1942F0u, kStrSourceFile, 574);  // K_Assert(file, line): a no-op in retail
    // 0x00194390 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(task, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001943B0 kwlnTaskSetFlagsRecursive -- 272 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x1943B0 kwlnTaskSetFlagsRecursive(set, task, mask): set (set != 0) or clear the flag bits
// mask & 0x0FFFFFF0 on `task` and every descendant (the children here, deeper levels by recursion).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskSetFlagsRecursive(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::nor, hg::sd,
          hg::sq, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& set = s4;  // $a0: set (!= 0) or clear
    Gpr& mask = s3;  // $a2: the flag bits (& kFlagBits)
    Gpr& child = s2;  // the task's children
    Gpr& grandchild = s5;  // each child's children (recursion)
    Gpr& bits = s1;  // mask & kFlagBits
    Gpr& keep = s0;  // ~bits
    // 0x001943b0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(grandchild, sp, 0x50);
    sq(set, sp, 0x40);
    sq(mask, sp, 0x30);
    sq(child, sp, 0x20);
    sq(bits, sp, 0x10);
    sq(keep, sp, 0x0);
    set = a0;
    mask = a2;
    if (set == 0) {
        // 0x00194400: clear: task->state &= ~(mask & kFlagBits)
        charge(ctx, 7);
        v1 = 0xFFF0000;  // v1 = kFlagBits (0x0FFFFFF0)
        v1 = v1 | 0xFFF0;
        v1 = mask & v1;
        a0 = nor(v1, 0);
        lw(v1, a1, tk::kState);
        v1 = v1 & a0;
        sw(v1, a1, tk::kState);
    } else {
        // 0x001943e0: set: task->state |= mask & kFlagBits
        charge(ctx, 8);
        v1 = 0xFFF0000;  // v1 = kFlagBits (0x0FFFFFF0)
        v1 = v1 | 0xFFF0;
        a0 = mask & v1;
        lw(v1, a1, tk::kState);
        v1 = v1 | a0;
        sw(v1, a1, tk::kState);
    }
    // 0x0019441c: the children (bits / keep computed once)
    charge(ctx, 7);
    lw(child, a1, tk::kChild);
    v1 = 0xFFF0000;  // v1 = kFlagBits (0x0FFFFFF0)
    v1 = v1 | 0xFFF0;
    bits = mask & v1;
    keep = nor(bits, 0);
    for (;;) {
        // 0x00194490: while (child)
        charge(ctx, 2);
        if (child == 0) {
            break;
        }
        backedge(ctx);
        // 0x00194438
        charge(ctx, 2);
        if (set == 0) {
            // 0x00194454: clear
            charge(ctx, 3);
            lw(v1, child, tk::kState);
            v1 = v1 & keep;
            sw(v1, child, tk::kState);
        } else {
            // 0x00194440: set
            charge(ctx, 5);
            lw(v1, child, tk::kState);
            v1 = v1 | bits;
            sw(v1, child, tk::kState);
        }
        // 0x00194460: each grandchild by recursion
        charge(ctx, 3);
        lw(grandchild, child, tk::kChild);
        for (;;) {
            // 0x00194484: while (grandchild)
            charge(ctx, 2);
            if (grandchild == 0) {
                break;
            }
            backedge(ctx);
            // 0x0019446c: kwlnTaskSetFlagsRecursive(set, grandchild, mask); grandchild = grandchild->sibling
            charge(ctx, 6);
            a0 = set;
            a1 = grandchild;
            a2 = mask;
            jal(ctx, 0x194478u, gen::fn_kwlnTaskSetFlagsRecursive_001943b0);
            lw(grandchild, grandchild, tk::kSibling);
        }
        // 0x0019448c: child = child->sibling
        charge(ctx, 1);
        lw(child, child, tk::kSibling);
    }
    // 0x00194498
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(grandchild, sp, 0x50);
    lq(set, sp, 0x40);
    lq(mask, sp, 0x30);
    lq(child, sp, 0x20);
    lq(bits, sp, 0x10);
    lq(keep, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x001944C0 kwlnTaskSetFlagsByMode -- 644 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x1944C0 kwlnTaskSetFlagsByMode(set, task, mask, mode): mode 0 = `task` only, 1 = every task in the three
// lists except `task`, 2 = `task` and its descendants, 3 = every task in the three lists (starting, running,
// ending order). A null task K_Asserts (669/677/703) and is still written; another mode asserts (708).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskSetFlagsByMode(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::nor, hg::sd,
          hg::slti, hg::sq, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& set = s4;  // $a0: set (!= 0) or clear
    Gpr& task = s3;  // $a1
    Gpr& mask = s2;  // $a2
    Gpr& mode = s1;  // $a3: 0..3
    Gpr& cursor = s0;  // the child / list cursor
    Gpr& list = t1;  // the list index 0..2
    Gpr& bits = t0;  // mask & kFlagBits
    // 0x001944c0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(set, sp, 0x40);
    sq(task, sp, 0x30);
    sq(mask, sp, 0x20);
    sq(mode, sp, 0x10);
    sq(cursor, sp, 0x0);
    set = a0;
    task = a1;
    mask = a2;
    mode = a3;
    cursor = 0;
    v1 = 2;
    if (mode == v1) {
        // 0x00194678: mode 2: `task` and its descendants (a null task asserts, line 703)
        charge(ctx, 2);
        if (task == 0) {
            // 0x00194680
            charge(ctx, 5);
            k_assert(a0, a1, 0x19468Cu, kStrSourceFile, 703);  // K_Assert(file, line): a no-op in retail
        }
        // 0x00194694
        charge(ctx, 2);
        if (set == 0) {
            // 0x001946bc: clear
            charge(ctx, 7);
            v1 = 0xFFF0000;  // v1 = kFlagBits (0x0FFFFFF0)
            v1 = v1 | 0xFFF0;
            v1 = mask & v1;
            a0 = nor(v1, 0);
            lw(v1, task, tk::kState);
            v1 = v1 & a0;
            sw(v1, task, tk::kState);
        } else {
            // 0x0019469c: set
            charge(ctx, 8);
            v1 = 0xFFF0000;  // v1 = kFlagBits (0x0FFFFFF0)
            v1 = v1 | 0xFFF0;
            a0 = mask & v1;
            lw(v1, task, tk::kState);
            v1 = v1 | a0;
            sw(v1, task, tk::kState);
        }
        // 0x001946d8: each child: kwlnTaskSetFlagsRecursive(set, child, mask)
        charge(ctx, 3);
        lw(cursor, task, tk::kChild);
        for (;;) {
            // 0x001946fc: while (child)
            charge(ctx, 2);
            if (cursor == 0) {
                break;
            }
            backedge(ctx);
            // 0x001946e4
            charge(ctx, 6);
            a0 = set;
            a1 = cursor;
            a2 = mask;
            jal(ctx, 0x1946F0u, gen::fn_kwlnTaskSetFlagsRecursive_001943b0);
            lw(cursor, cursor, tk::kSibling);
        }
        // 0x00194704
        charge(ctx, 2);
    } else {
        // 0x001944fc: modes 3 and 1 walk the three lists; mode 0 is `task` alone; any other mode asserts
        charge(ctx, 3);
        v1 = 3;
        bool walk = mode == v1;
        if (!walk) {
            // 0x00194508
            charge(ctx, 3);
            v1 = 1;
            walk = mode == v1;
            if (walk) {
                // 0x0019458c
                charge(ctx, 2);
                if (task == 0) {
                    // 0x00194594
                    charge(ctx, 5);
                    k_assert(a0, a1, 0x1945A0u, kStrSourceFile, 677);  // K_Assert(file, line): a no-op in retail
                }
            } else {
                // 0x00194514
                charge(ctx, 2);
                if (mode == 0) {
                    // 0x00194524: mode 0, `task` only
                    charge(ctx, 2);
                    if (task == 0) {
                        // 0x0019452c
                        charge(ctx, 5);
                        k_assert(a0, a1, 0x194538u, kStrSourceFile, 669);  // K_Assert(file, line): a no-op in retail
                    }
                    // 0x00194540
                    charge(ctx, 2);
                    if (set == 0) {
                        // 0x00194568: state &= ~(mask & kFlagBits)
                        charge(ctx, 9);
                        v1 = 0xFFF0000;  // v1 = kFlagBits (0x0FFFFFF0)
                        v1 = v1 | 0xFFF0;
                        v1 = mask & v1;
                        a0 = nor(v1, 0);
                        lw(v1, task, tk::kState);
                        v1 = v1 & a0;
                        sw(v1, task, tk::kState);
                    } else {
                        // 0x00194548: state |= mask & kFlagBits
                        charge(ctx, 8);
                        v1 = 0xFFF0000;  // v1 = kFlagBits (0x0FFFFFF0)
                        v1 = v1 | 0xFFF0;
                        a0 = mask & v1;
                        lw(v1, task, tk::kState);
                        v1 = v1 | a0;
                        sw(v1, task, tk::kState);
                    }
                } else {
                    // 0x0019451c
                    charge(ctx, 2);
                    // 0x0019470c: an unknown mode
                    charge(ctx, 5);
                    k_assert(a0, a1, 0x194718u, kStrSourceFile, 708);  // K_Assert(file, line): a no-op in retail
                }
                // 0x00194720 (the shared epilogue, written out on this path)
                charge(ctx, 9);
                ld(ra, sp, 0x50);
                lq(set, sp, 0x40);
                lq(task, sp, 0x30);
                lq(mask, sp, 0x20);
                lq(mode, sp, 0x10);
                lq(cursor, sp, 0x0);
                sp = addiu(sp, 0x60);
                return;
            }
        }
        // 0x001945a8: modes 3 / 1: the starting, running and ending lists in turn
        charge(ctx, 10);
        list = 0;
        v1 = 0xFFF0000;  // v1 = kFlagBits (0x0FFFFFF0)
        v1 = v1 | 0xFFF0;
        bits = mask & v1;
        a3 = nor(bits, 0);
        a1 = 1;
        a2 = 2;
        a0 = 3;
        for (;;) {
            // 0x00194664: while (list < 3)
            charge(ctx, 3);
            v1 = slti(list, 3);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001945d0: the head of list 0 / 1 / 2 (starting, running, ending)
            charge(ctx, 2);
            if (list == a2) {
                // 0x00194608
                charge(ctx, 3);
                lw(cursor, gp, kGpEndingHead);
            } else {
                // 0x001945d8
                charge(ctx, 2);
                if (list == a1) {
                    // 0x001945fc
                    charge(ctx, 3);
                    lw(cursor, gp, kGpRunningHead);
                } else {
                    // 0x001945e0
                    charge(ctx, 2);
                    if (list == 0) {
                        // 0x001945f0
                        charge(ctx, 3);
                        lw(cursor, gp, kGpStartingHead);
                    } else {
                        // 0x001945e8
                        charge(ctx, 2);
                    }
                }
            }
            for (;;) {
                // 0x00194658: walk the list
                charge(ctx, 2);
                if (cursor == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00194614: mode 1 takes every task but `task`, mode 3 every task
                charge(ctx, 2);
                bool apply = false;
                if (cursor != task) {
                    // 0x0019461c
                    charge(ctx, 2);
                    apply = mode == a1;
                }
                if (!apply) {
                    // 0x00194624
                    charge(ctx, 2);
                    apply = mode == a0;
                }
                if (apply) {
                    // 0x0019462c
                    charge(ctx, 2);
                    if (set == 0) {
                        // 0x00194648: state &= ~bits
                        charge(ctx, 3);
                        lw(v1, cursor, tk::kState);
                        v1 = v1 & a3;
                        sw(v1, cursor, tk::kState);
                    } else {
                        // 0x00194634: state |= bits
                        charge(ctx, 5);
                        lw(v1, cursor, tk::kState);
                        v1 = v1 | bits;
                        sw(v1, cursor, tk::kState);
                    }
                }
                // 0x00194654
                charge(ctx, 1);
                lw(cursor, cursor, tk::kNext);
            }
            // 0x00194660
            charge(ctx, 1);
            list = addiu(list, 1);
        }
        // 0x00194670
        charge(ctx, 2);
    }
    // 0x00194720 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(set, sp, 0x40);
    lq(task, sp, 0x30);
    lq(mask, sp, 0x20);
    lq(mode, sp, 0x10);
    lq(cursor, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x1949E0 kwlnTaskMain(): one frame of the kernel (kwlnUpdate calls it). 1) Each starting task's
// start_wait counts down; at 0 it moves to the running list with +0x24/+0x28 cleared. 2) kwlnTaskUpdateAll.
// 3) Each ending task's end_wait counts down; at 0 it is unlinked, its destroy callback runs, its state
// becomes 0, it leaves the tree and is H_Free'd. Both walks read the successor before touching a task.
u32 kwlnTaskMain(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 48);
    f.sd(GPR_RA, 32);
    f.sq(GPR_S1, 16);
    f.sq(GPR_S0, 0);
    const auto count_down = [&](u32 t, u32 off) {
        charge(ctx, 3);
        const s32 w = static_cast<s32>(lwr(ctx, GPR_V0, t + off));
        if (w > 0) {
            charge(ctx, 2);
            setreg(ctx, GPR_V0, static_cast<u32>(w - 1));
            sw(ctx, t + off, static_cast<u32>(w - 1));
        }
        charge(ctx, 5);
        setreg64(ctx, GPR_S0, reg64(ctx, GPR_S1));
        setreg(ctx, GPR_S1, lw(ctx, t + kOffNext));
        return lwr(ctx, GPR_V0, t + off) == 0;
    };
    setreg(ctx, GPR_S1, lw(ctx, gpvar(ctx, kStartingList.head)));
    for (;;) {
        charge(ctx, 2);
        if (reg64(ctx, GPR_S1) == 0) break;
        backedge(ctx);
        const u32 t = reg(ctx, GPR_S1);
        if (!count_down(t, kOffStartWait)) continue;
        charge(ctx, 13);
        call_with_s(ctx, GPR_S0, 0x194A28, &gen::fn_kwlnTaskRemoveFromList_001939d0);
        set_state_nibble(ctx, t, kStateRunning);
        call_with_s(ctx, GPR_S0, 0x194A48, &gen::fn_kwlnTaskAddToList_00193ba0);
        sw(ctx, t + kOff24, 0);
        sw(ctx, t + kOffTimer, 0);
    }
    charge(ctx, 5);
    jal(ctx, 0x194A60, &gen::fn_kwlnTaskUpdateAll_00194100);
    setreg(ctx, GPR_S1, lw(ctx, gpvar(ctx, kEndingList.head)));
    for (;;) {
        charge(ctx, 2);
        if (reg64(ctx, GPR_S1) == 0) break;
        backedge(ctx);
        const u32 t = reg(ctx, GPR_S1);
        if (!count_down(t, kOffEndWait)) continue;
        charge(ctx, 6);
        static constexpr u32 kPcs[5] = {0x194AA0, 0x194AB8, 0x194AD4, 0x194AE0, 0x194AEC};
        retire(ctx, t, kPcs);
    }
    charge(ctx, 7);
    setreg(ctx, GPR_V0, 1);
    return 1;
}

// 0x194B20 kwlnTaskCreate(parent, name, priority, update, destroy, work) = kwlnTaskInit(name, ...) +
// kwlnTaskAddChild(parent, task); returns the task. A register shuffle in the original, kept as one
// (the six arguments are $a0..$a3, $t0, $t1).
void kwlnTaskCreate(EEContext& ctx) {
    guest::enter(ctx, 24);
    Frame f(ctx, 48);
    f.sd(GPR_RA, 32);
    f.sq(GPR_S1, 16);
    f.sq(GPR_S0, 0);
    setreg64(ctx, GPR_S1, reg64(ctx, GPR_A0));
    setreg64(ctx, GPR_A0, reg64(ctx, GPR_A1));
    setreg64(ctx, GPR_A1, reg64(ctx, GPR_A2));
    setreg64(ctx, GPR_A2, reg64(ctx, GPR_A3));
    setreg64(ctx, GPR_A3, reg64(ctx, GPR_T0));
    setreg64(ctx, GPR_T0, reg64(ctx, GPR_T1));
    jal(ctx, 0x194B48, &gen::fn_kwlnTaskInit_00194c50);
    setreg64(ctx, GPR_S0, reg64(ctx, GPR_V0));
    setreg64(ctx, GPR_A0, reg64(ctx, GPR_S1));
    setreg64(ctx, GPR_A1, reg64(ctx, GPR_S0));
    jal(ctx, 0x194B5C, &gen::fn_kwlnTaskAddChild_00195550);
    setreg64(ctx, GPR_V0, reg64(ctx, GPR_S0));
}

// 0x00194B80 kwlnTaskCreateWithAutoPriority -- 204 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x194B80 kwlnTaskCreateWithAutoPriority(parent, priority, name, update, destroy, work): like
// kwlnTaskCreate, but when an ancestor (the parent chain, parent included) has a priority p in
// [priority, priority + 1024), the task gets (largest such p) + 1. The walk lives in $t2 (ancestor),
// $t3 (best), $v0 (priority + 1024), $a0 (p), $v1 / $at (the compares).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskCreateWithAutoPriority(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sltu,
          hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& parent = s0;  // $a0
    Gpr& ancestor = t2;  // the parent chain
    Gpr& best = t3;  // the largest ancestor priority in range
    // 0x00194b80
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(parent, sp, 0x0);
    parent = a0;
    ancestor = parent;
    if (parent != 0) {
        // 0x00194ba8: the largest ancestor priority p in [priority, priority + 1024)
        charge(ctx, 4);
        best = 0;
        v0 = addiu(a1, 1024);
        for (;;) {
            // 0x00194be8: while (ancestor)
            charge(ctx, 2);
            if (ancestor == 0) {
                break;
            }
            backedge(ctx);
            // 0x00194bb8: p = ancestor->priority; p >= priority?
            charge(ctx, 4);
            lw(a0, ancestor, tk::kPriority);
            v1 = sltu(a0, a1);
            if (v1 == 0) {
                // 0x00194bc8: p < priority + 1024?
                charge(ctx, 3);
                at = sltu(a0, v0);
                if (at != 0) {
                    // 0x00194bd4: p > best?
                    charge(ctx, 3);
                    at = sltu(best, a0);
                    if (at != 0) {
                        // 0x00194be0
                        charge(ctx, 1);
                        best = a0;
                    }
                }
            }
            // 0x00194be4: ancestor = ancestor->parent
            charge(ctx, 1);
            lw(ancestor, ancestor, tk::kParent);
        }
        // 0x00194bf0
        charge(ctx, 2);
        if (best != 0) {
            // 0x00194c00: priority = best + 1
            charge(ctx, 1);
            a1 = addiu(best, 1);
        } else {
            // 0x00194bf8
            charge(ctx, 2);
        }
    } else {
        // 0x00194ba0
        charge(ctx, 2);
    }
    // 0x00194c04: task = kwlnTaskInit(name, priority, update, destroy, work); kwlnTaskAddChild(parent, task); return task
    charge(ctx, 18);
    a0 = a2;
    a2 = a3;
    a3 = t0;
    t0 = t1;
    jal(ctx, 0x194C14u, gen::fn_kwlnTaskInit_00194c50);
    s1 = v0;
    a0 = parent;
    a1 = s1;
    jal(ctx, 0x194C28u, gen::fn_kwlnTaskAddChild_00195550);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(parent, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00194C50 kwlnTaskInit -- 436 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x194C50 kwlnTaskInit(name, priority, update, destroy, work): a new running task (start_wait 0,
// end_wait 2), not linked into the tree; 0 when H_Malloc fails. An empty name asserts (line 1022).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskInit(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lb, hg::ld, hg::lq, hg::lw,
          hg::sb, hg::sd, hg::si, hg::slti, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // the new record
    Gpr& name = s5;  // $a0
    Gpr& priority = s4;  // $a1
    Gpr& update = s3;  // $a2
    Gpr& destroy = s2;  // $a3
    Gpr& work = s1;  // $t0
    // 0x00194c50
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(name, sp, 0x50);
    sq(priority, sp, 0x40);
    sq(update, sp, 0x30);
    sq(destroy, sp, 0x20);
    sq(work, sp, 0x10);
    sq(task, sp, 0x0);
    name = a0;
    priority = a1;
    update = a2;
    destroy = a3;
    work = t0;
    lb(v0, a0, 0);
    if (v0 == 0) {
        // 0x00194c90: an empty name asserts (line 1022)
        charge(ctx, 5);
        k_assert(a0, a1, 0x194C9Cu, kStrSourceFile, 1022);  // K_Assert(file, line): a no-op in retail
    }
    // 0x00194ca4: task = H_Malloc(0x68)
    charge(ctx, 6);
    a0 = kTaskSize;  // H_Malloc(sizeof(KwlnTask))
    jal(ctx, 0x194CA8u, gen::fn_sub_191AF0_00191af0);
    task = v0;
    if (task == 0) {
        // 0x00194cbc: out of memory asserts (line 1032)
        charge(ctx, 5);
        k_assert(a0, a1, 0x194CC8u, kStrSourceFile, 1032);  // K_Assert(file, line): a no-op in retail
    }
    // 0x00194cd0
    charge(ctx, 2);
    if (task != 0) {
        // 0x00194ce4: copy the name (at most 24 bytes) and sum its signed bytes
        charge(ctx, 4);
        sw(zero, task, tk::kNameSum);
        a1 = 0;
        for (;;) {
            // 0x00194d08
            charge(ctx, 6);
            a0 = addu(name, a1);
            lb(v1, a0, 0);
            v0 = addu(task, a1);
            sb(v1, v0, 0);
            if (v1 != 0) {
                // 0x00194d20
                charge(ctx, 3);
                v0 = slti(a1, 24);
                if (v0 != 0) {
                    backedge(ctx);
                    // 0x00194cf4: name_sum += name[i]; i++
                    charge(ctx, 5);
                    lb(v1, a0, 0);
                    lw(v0, task, tk::kNameSum);
                    v0 = addu(v0, v1);
                    sw(v0, task, tk::kNameSum);
                    a1 = addiu(a1, 1);
                    continue;
                }
            }
            break;
        }
        // 0x00194d2c: the fields: state 1 (starting), start_wait 0, end_wait 2, no links; kwlnTaskAddToList
        charge(ctx, 30);
        sb(zero, task, tk::kNameLast);
        sw(zero, task, tk::kState);
        v0 = 0;
        v0 = v0 | kStateStarting;
        sw(v0, task, tk::kState);
        sw(priority, task, tk::kPriority);
        sw(zero, task, tk::k24);
        sw(zero, task, tk::kTimer);
        sw(zero, task, tk::kStartWait);
        v0 = 2;
        sw(v0, task, tk::kEndWait);
        sw(update, task, tk::kUpdate);
        sw(destroy, task, tk::kDestroy);
        sw(work, task, tk::kWork);
        sw(zero, task, tk::kNext);
        sw(zero, task, tk::kPrev);
        sw(zero, task, tk::kPrev2);
        sw(zero, task, tk::kParent);
        sw(zero, task, tk::kChild);
        sw(zero, task, tk::kSibling);
        sw(zero, task, tk::kUnk58);
        sw(zero, task, tk::kUnk58 + 4);
        sw(zero, task, tk::kUnk58 + 8);
        sw(zero, task, tk::kUnk58 + 12);
        a0 = task;
        jal(ctx, 0x194D90u, gen::fn_kwlnTaskAddToList_00193ba0);
        lw(v0, task, tk::kStartWait);
        if (v0 == 0) {
            // 0x00194da4: start_wait 0: straight on to the running list
            charge(ctx, 13);
            a0 = task;
            jal(ctx, 0x194DA8u, gen::fn_kwlnTaskRemoveFromList_001939d0);
            lw(v1, task, tk::kState);
            v0 = si(-16);  // ~kStateMask
            v0 = v1 & v0;
            v0 = v0 | kStateRunning;
            sw(v0, task, tk::kState);
            a0 = task;
            jal(ctx, 0x194DC8u, gen::fn_kwlnTaskAddToList_00193ba0);
            sw(zero, task, tk::k24);
            sw(zero, task, tk::kTimer);
        }
        // 0x00194dd8: return the task
        charge(ctx, 1);
        v0 = task;
    } else {
        // 0x00194cd8: H_Malloc failed: 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00194ddc (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(name, sp, 0x50);
    lq(priority, sp, 0x40);
    lq(update, sp, 0x30);
    lq(destroy, sp, 0x20);
    lq(work, sp, 0x10);
    lq(task, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00194E10 kwlnTaskInitEx -- 456 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x194E10 kwlnTaskInitEx(name, priority, start_wait, end_wait, update, destroy, work): the same with the
// two delays given (a task with start_wait > 0 stays in the starting list). Asserts at lines 1101/1109.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskInitEx(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lb, hg::ld, hg::lq, hg::lw,
          hg::sb, hg::sd, hg::si, hg::slti, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // the new record
    Gpr& name = s5;  // $a0
    Gpr& priority = s4;  // $a1
    Gpr& start_wait = s3;  // $a2
    Gpr& end_wait = s2;  // $a3
    Gpr& update = s1;  // $t0
    Gpr& destroy = s6;  // $t1
    Gpr& work = s7;  // $t2
    // 0x00194e10
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(work, sp, 0x70);
    sq(destroy, sp, 0x60);
    sq(name, sp, 0x50);
    sq(priority, sp, 0x40);
    sq(start_wait, sp, 0x30);
    sq(end_wait, sp, 0x20);
    sq(update, sp, 0x10);
    sq(task, sp, 0x0);
    name = a0;
    priority = a1;
    start_wait = a2;
    end_wait = a3;
    update = t0;
    destroy = t1;
    work = t2;
    lb(v0, a0, 0);
    if (v0 == 0) {
        // 0x00194e60: an empty name asserts (line 1101)
        charge(ctx, 5);
        k_assert(a0, a1, 0x194E6Cu, kStrSourceFile, 1101);  // K_Assert(file, line): a no-op in retail
    }
    // 0x00194e74: task = H_Malloc(0x68)
    charge(ctx, 6);
    a0 = kTaskSize;  // H_Malloc(sizeof(KwlnTask))
    jal(ctx, 0x194E78u, gen::fn_sub_191AF0_00191af0);
    task = v0;
    if (task == 0) {
        // 0x00194e8c: out of memory asserts (line 1109)
        charge(ctx, 5);
        k_assert(a0, a1, 0x194E98u, kStrSourceFile, 1109);  // K_Assert(file, line): a no-op in retail
    }
    // 0x00194ea0
    charge(ctx, 2);
    if (task != 0) {
        // 0x00194eb4: copy the name (at most 24 bytes) and sum its signed bytes
        charge(ctx, 4);
        sw(zero, task, tk::kNameSum);
        a1 = 0;
        for (;;) {
            // 0x00194ed8
            charge(ctx, 6);
            a0 = addu(name, a1);
            lb(v1, a0, 0);
            v0 = addu(task, a1);
            sb(v1, v0, 0);
            if (v1 != 0) {
                // 0x00194ef0
                charge(ctx, 3);
                v0 = slti(a1, 24);
                if (v0 != 0) {
                    backedge(ctx);
                    // 0x00194ec4: name_sum += name[i]; i++
                    charge(ctx, 5);
                    lb(v1, a0, 0);
                    lw(v0, task, tk::kNameSum);
                    v0 = addu(v0, v1);
                    sw(v0, task, tk::kNameSum);
                    a1 = addiu(a1, 1);
                    continue;
                }
            }
            break;
        }
        // 0x00194efc: the fields: state 1 (starting), the given waits and callbacks, no links; kwlnTaskAddToList
        charge(ctx, 29);
        sb(zero, task, tk::kNameLast);
        sw(zero, task, tk::kState);
        v0 = 0;
        v0 = v0 | kStateStarting;
        sw(v0, task, tk::kState);
        sw(priority, task, tk::kPriority);
        sw(zero, task, tk::k24);
        sw(zero, task, tk::kTimer);
        sw(start_wait, task, tk::kStartWait);
        sw(end_wait, task, tk::kEndWait);
        sw(update, task, tk::kUpdate);
        sw(destroy, task, tk::kDestroy);
        sw(work, task, tk::kWork);
        sw(zero, task, tk::kNext);
        sw(zero, task, tk::kPrev);
        sw(zero, task, tk::kPrev2);
        sw(zero, task, tk::kParent);
        sw(zero, task, tk::kChild);
        sw(zero, task, tk::kSibling);
        sw(zero, task, tk::kUnk58);
        sw(zero, task, tk::kUnk58 + 4);
        sw(zero, task, tk::kUnk58 + 8);
        sw(zero, task, tk::kUnk58 + 12);
        a0 = task;
        jal(ctx, 0x194F5Cu, gen::fn_kwlnTaskAddToList_00193ba0);
        lw(v0, task, tk::kStartWait);
        if (v0 == 0) {
            // 0x00194f70: start_wait 0: straight on to the running list
            charge(ctx, 13);
            a0 = task;
            jal(ctx, 0x194F74u, gen::fn_kwlnTaskRemoveFromList_001939d0);
            lw(v1, task, tk::kState);
            v0 = si(-16);  // ~kStateMask
            v0 = v1 & v0;
            v0 = v0 | kStateRunning;
            sw(v0, task, tk::kState);
            a0 = task;
            jal(ctx, 0x194F94u, gen::fn_kwlnTaskAddToList_00193ba0);
            sw(zero, task, tk::k24);
            sw(zero, task, tk::kTimer);
        }
        // 0x00194fa4: return the task
        charge(ctx, 1);
        v0 = task;
    } else {
        // 0x00194ea8: H_Malloc failed: 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00194fa8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x80);
    lq(work, sp, 0x70);
    lq(destroy, sp, 0x60);
    lq(name, sp, 0x50);
    lq(priority, sp, 0x40);
    lq(start_wait, sp, 0x30);
    lq(end_wait, sp, 0x20);
    lq(update, sp, 0x10);
    lq(task, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 kwlnTaskInitEx(EEContext& ctx, u64 name, u64 prio, u64 start_wait, u64 end_wait, u64 update, u64 destroy,
               u64 work) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(name));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(prio));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(start_wait));
    ee::core::set_gpr64(ctx, GPR_A3, static_cast<u64>(end_wait));
    ee::core::set_gpr64(ctx, GPR_T0, static_cast<u64>(update));
    ee::core::set_gpr64(ctx, GPR_T1, static_cast<u64>(destroy));
    ee::core::set_gpr64(ctx, GPR_T2, static_cast<u64>(work));
    kwlnTaskInitEx(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x194FE0 kwlnTaskDestroyWithHierarchyByName(name): kwlnTaskGetTaskByName + kwlnTaskDestroyWithHierarchy;
// 0 when no task has that name. The name stays in $a0 for the lookup.
u64 kwlnTaskDestroyWithHierarchyByName(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 16);
    f.sd(GPR_RA, 0);
    jal(ctx, 0x194FE8, &gen::fn_kwlnTaskGetTaskByName_00195340);
    charge(ctx, 3);
    if (reg64(ctx, GPR_V0) != 0) {
        setreg64(ctx, GPR_A0, reg64(ctx, GPR_V0));
        jal(ctx, 0x195008, &gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    } else {
        setreg64(ctx, GPR_V0, 0);
    }
    charge(ctx, 4);
    return reg64(ctx, GPR_V0);
}

// 0x00195020 kwlnTaskDestroyWithHierarchy -- 616 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x195020 kwlnTaskDestroyWithHierarchy(task): 0 (K_Abort "ProcessID invalid!!", lines 1181/1204) for a
// null or -1 id or a dead/invalid state; else 1. A starting or running task gets end_wait 2 and is destroyed
// (kwlnTaskDestroy inlined; end_wait 2 means it always waits), then its children's subtrees and children
// are; an ending task only gets end_wait 2 again and keeps its children.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskDestroyWithHierarchy(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::jalr, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::si, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& task = s0;  // the task (from $a0), later its children
    // 0x00195020
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(task, sp, 0x0);
    task = a0;
    if (task != 0) {
        // 0x00195038: -1 is not a task either
        charge(ctx, 3);
        v0 = si(-1);
        if (task != v0) {
            // 0x0019506c: the state switch: 2 / 1 are destroyed with their children, 3 only gets end_wait 2 again,
            // 0 and anything above 3 K_Abort (line 1204)
            charge(ctx, 4);
            lw(v0, task, tk::kState);
            v1 = v0 & kStateMask;
            bool live = false;    // starting or running
            bool ending = false;  // already ending
            if (v1 != 0) {
                // 0x0019507c
                charge(ctx, 3);
                v0 = 3;
                if (v1 != v0) {
                    // 0x00195088
                    charge(ctx, 3);
                    v0 = 2;
                    live = v1 == v0;
                    if (!live) {
                        // 0x00195094
                        charge(ctx, 3);
                        v0 = 1;
                        live = v1 == v0;
                        if (!live) {
                            // 0x001950a0
                            charge(ctx, 2);
                        }
                    }
                    if (live) {
                        // 0x001950a8: end_wait = 2, then kwlnTaskDestroy inlined (its state switch again)
                        charge(ctx, 6);
                        a0 = 2;
                        sw(a0, task, tk::kEndWait);
                        lw(v0, task, tk::kState);
                        v1 = v0 & kStateMask;
                        bool invalid = true;
                        if (v1 != 0) {
                            // 0x001950c0
                            charge(ctx, 3);
                            v0 = 3;
                            invalid = false;
                            if (v1 != v0) {
                                // 0x001950cc
                                charge(ctx, 2);
                                bool move = v1 == a0;
                                if (!move) {
                                    // 0x001950d4
                                    charge(ctx, 3);
                                    v0 = 1;
                                    move = v1 == v0;
                                }
                                if (move) {
                                    // 0x0019510c: unlink, state = 3 (ending), relink into the ending list
                                    charge(ctx, 14);
                                    a0 = task;
                                    jal(ctx, 0x195110u, gen::fn_kwlnTaskRemoveFromList_001939d0);
                                    lw(v1, task, tk::kState);
                                    v0 = si(-16);  // ~kStateMask
                                    v0 = v1 & v0;
                                    v0 = v0 | kStateEnding;
                                    sw(v0, task, tk::kState);
                                    a0 = task;
                                    jal(ctx, 0x195130u, gen::fn_kwlnTaskAddToList_00193ba0);
                                    lw(v0, task, tk::kEndWait);
                                    if (v0 == 0) {
                                        // 0x00195144: end_wait 0 (never: it is 2 here): retire at once
                                        charge(ctx, 6);
                                        a0 = task;
                                        jal(ctx, 0x195148u, gen::fn_kwlnTaskRemoveFromList_001939d0);
                                        lw(v0, task, tk::kDestroy);
                                        if (v0 != 0) {
                                            // 0x0019515c: destroy(task)
                                            charge(ctx, 3);
                                            a0 = task;
                                            jalr(ctx, 0x195160u, v0.u());
                                        }
                                        // 0x00195168
                                        charge(ctx, 13);
                                        lw(v1, task, tk::kState);
                                        v0 = si(-16);  // ~kStateMask
                                        v0 = v1 & v0;
                                        sw(v0, task, tk::kState);
                                        a0 = task;
                                        jal(ctx, 0x19517Cu, gen::fn_kwlnTaskDetachParent_001955f0);
                                        a0 = task;
                                        jal(ctx, 0x195188u, gen::fn_kwlnTaskDetachAllChildren_00195690);
                                        a0 = task;
                                        jal(ctx, 0x195194u, gen::fn_sub_191A10_00191a10);  // H_Free(task)
                                    }
                                } else {
                                    invalid = true;
                                }
                            }
                        }
                        if (invalid) {
                            // 0x001950e0: printf("Process stat Invalid!!\n"); K_Assert("kwlnTask.c", 574)
                            charge(ctx, 11);
                            la(a0, kStrStatInvalidNl);  // "Process stat Invalid!!\n"
                            jal(ctx, 0x1950E8u, gen::fn_printf_005225a8);
                            k_assert(a0, a1, 0x1950FCu, kStrSourceFile, 574);  // K_Assert(file, line): a no-op in retail
                        }
                        // 0x0019519c: each child: kwlnTaskDestroyHierarchy(child->child), kwlnTaskDestroy(child)
                        charge(ctx, 3);
                        lw(task, task, tk::kChild);
                        if (task != 0) {
                            // 0x001951a8
                            charge(ctx, 2);
                            for (;;) {
                                // 0x001951cc
                                charge(ctx, 2);
                                if (task == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x001951b0
                                charge(ctx, 7);
                                lw(a0, task, tk::kChild);
                                jal(ctx, 0x1951B4u, gen::fn_kwlnTaskDestroyHierarchy_001941f0);
                                a0 = task;
                                jal(ctx, 0x1951C0u, gen::fn_kwlnTaskDestroy_00194280);
                                lw(task, task, tk::kSibling);
                            }
                            // 0x001951d4
                            charge(ctx, 2);
                        }
                    }
                } else {
                    // 0x001951dc: ending: end_wait = 2 (the retire test on the constant is dead)
                    ending = true;
                    charge(ctx, 4);
                    v0 = 2;
                    sw(v0, task, tk::kEndWait);
                    if (v0 == 0) {
                        // 0x001951ec
                        charge(ctx, 5);
                        jal(ctx, 0x1951ECu, gen::fn_kwlnTaskRemoveFromList_001939d0);
                        lw(v0, task, tk::kDestroy);
                        if (v0 != 0) {
                            // 0x00195200
                            charge(ctx, 3);
                            a0 = task;
                            jalr(ctx, 0x195204u, v0.u());
                        }
                        // 0x0019520c
                        charge(ctx, 15);
                        lw(v1, task, tk::kState);
                        v0 = si(-16);  // ~kStateMask
                        v0 = v1 & v0;
                        sw(v0, task, tk::kState);
                        a0 = task;
                        jal(ctx, 0x195220u, gen::fn_kwlnTaskDetachParent_001955f0);
                        a0 = task;
                        jal(ctx, 0x19522Cu, gen::fn_kwlnTaskDetachAllChildren_00195690);
                        a0 = task;
                        jal(ctx, 0x195238u, gen::fn_sub_191A10_00191a10);
                    }
                }
            }
            if (live || ending) {
                // 0x00195270: 1
                charge(ctx, 1);
                v0 = 1;
                // 0x00195274 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(task, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
            // 0x00195248: K_Abort("ProcessID invalid!!\n", "kwlnTask.c", 1204), 0
            charge(ctx, 10);
            la(a0, kStrIdInvalid);  // "ProcessID invalid!!\n"
            la(a1, kStrSourceFile);  // "kwlnTask.c"
            a2 = 1204;
            jal(ctx, 0x19525Cu, gen::fn_sub_19D400_0019d400);
            v0 = 0;
            // 0x00195274 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(task, sp, 0x0);
            sp = addiu(sp, 0x20);
            return;
        }
    }
    // 0x00195044: a null or -1 task: K_Abort("ProcessID invalid!!\n", "kwlnTask.c", 1181), 0
    charge(ctx, 10);
    la(a0, kStrIdInvalid);  // "ProcessID invalid!!\n"
    la(a1, kStrSourceFile);  // "kwlnTask.c"
    a2 = 1181;
    jal(ctx, 0x195058u, gen::fn_sub_19D400_0019d400);
    v0 = 0;
    // 0x00195274 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(task, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x195290 kwlnTaskGetState(task): the state nibble of a task that is in one of the lists, else 0; a
// listed task with state 0 is fine, > 3 prints and asserts (line 1286) and gives 0.
u32 kwlnTaskGetState(EEContext& ctx, u64 task64) {
    guest::enter(ctx, 8);
    Frame f(ctx, 32);
    f.sd(GPR_RA, 16);
    f.sq(GPR_S0, 0);
    setreg64(ctx, GPR_S0, task64);
    setreg64(ctx, GPR_A0, task64);
    jal(ctx, 0x1952A0, &gen::fn_kwlnTaskExists_00195460);
    u32 ret = 0;
    if (reg64(ctx, GPR_V0) == 0) {
        charge(ctx, 3);
    } else {
        charge(ctx, 4);
        const u32 s = lw(ctx, static_cast<u32>(task64) + kOffState) & kStateMask;
        setreg(ctx, GPR_V0, s);
        if (s == 0 || cascade(ctx, s, true) != 0) {
            charge(ctx, 2);
            ret = s;
        } else {
            charge(ctx, 10);
            print(ctx, 0x195308, kStrStatInvalidNl);
            k_assert(ctx, 0x19531C, 1286);
        }
    }
    charge(ctx, 5);
    return ret;
}

// 0x00195340 kwlnTaskGetTaskByName -- 260 bytes; leaf frame (no stack)
// 0x195340 kwlnTaskGetTaskByName(name): the first task, in the starting, running then ending list, whose
// name sum and bytes (compared from the terminator down) match; 0 if none. The heads are read once.
// Registers as the original: $t3 sum, $t4 length, $t2/$t1/$t0 the heads, $t6 the list index, $t5 the byte
// index, $a2 = 1, $a3 = 2, $a1 / $v1 the compared bytes, $v0 the cursor.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskGetTaskByName(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lb, hg::lw,
          hg::slti;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, gp{ctx, 28};
    Gpr& name = a0;
    Gpr& sum = t3;  // the signed byte sum of the name
    Gpr& len = t4;  // its length
    Gpr& list = t6;  // the list index 0..2
    Gpr& pos = t5;  // the byte compared
    Gpr& task = v0;  // the cursor (the result)
    // 0x00195340
    enter(ctx, 5);  // entry check point + this block's cycles
    task = 0;
    sum = 0;
    len = 0;
    for (;;) {
        // 0x00195364
        charge(ctx, 4);
        v1 = addu(name, len);
        lb(v1, v1, 0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00195354
        charge(ctx, 4);
        v1 = dsll32(v1, 24);
        v1 = dsra32(v1, 24);
        sum = addu(sum, v1);
        len = addiu(len, 1);
    }
    // 0x00195374: the three heads are read once; list 0 starting, 1 running, 2 ending
    charge(ctx, 8);
    list = 0;
    lw(t2, gp, kGpStartingHead);
    lw(t1, gp, kGpRunningHead);
    lw(t0, gp, kGpEndingHead);
    a2 = 1;
    a3 = 2;
    bool found = false;
    for (;;) {
        // 0x0019542c: while (list < 3)
        charge(ctx, 3);
        v1 = slti(list, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00195394
        charge(ctx, 2);
        if (list == a3) {
            // 0x001953cc
            charge(ctx, 3);
            task = t0;
        } else {
            // 0x0019539c
            charge(ctx, 2);
            if (list == a2) {
                // 0x001953c0
                charge(ctx, 3);
                task = t1;
            } else {
                // 0x001953a4
                charge(ctx, 2);
                if (list == 0) {
                    // 0x001953b4
                    charge(ctx, 3);
                    task = t2;
                } else {
                    // 0x001953ac
                    charge(ctx, 2);
                }
            }
        }
        for (;;) {
            // 0x00195420: walk the list
            charge(ctx, 2);
            if (task == 0) {
                break;
            }
            backedge(ctx);
            // 0x001953d8: the sums first
            charge(ctx, 3);
            lw(v1, task, tk::kNameSum);
            if (v1 == sum) {
                // 0x001953e4: then the bytes, from the terminator down to byte 0
                charge(ctx, 3);
                pos = len;
                for (;;) {
                    // 0x00195404
                    charge(ctx, 6);
                    v1 = addu(name, pos);
                    lb(a1, v1, 0);
                    v1 = addu(task, pos);
                    lb(v1, v1, 0);
                    if (a1 != v1) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001953f0
                    charge(ctx, 2);
                    if (pos == 0) {
                        found = true;
                        break;
                    }
                    // 0x00195400
                    charge(ctx, 1);
                    pos = addiu(pos, -1);
                }
                if (found) {
                    break;
                }
            }
            // 0x0019541c
            charge(ctx, 1);
            lw(task, task, tk::kNext);
        }
        if (found) {
            break;
        }
        // 0x00195428
        charge(ctx, 1);
        list = addiu(list, 1);
    }
    if (found) {
        // 0x001953f8: the cursor is the result
        charge(ctx, 2);
    } else {
        // 0x00195438: none
        charge(ctx, 1);
        task = 0;
    }
    // 0x0019543c
    charge(ctx, 2);
}

// 0x195450 kwlnTaskGetUpdating(): the task whose update callback is running (0 outside kwlnTaskUpdate).
u32 kwlnTaskGetUpdating(EEContext& ctx) {
    guest::enter(ctx, 3);
    return lw(ctx, gpvar(ctx, kGpUpdatingTask));
}

// 0x195460 kwlnTaskExists(task): 1 when the pointer is in the starting, running or ending list.
// Registers as the original: $t1 the cursor, $t2 the list index, $t0/$a3/$a2 the heads, $v1 = 1, $a1 = 2.
u32 kwlnTaskExists(EEContext& ctx, u64 task) {
    guest::enter(ctx, 3);
    setreg(ctx, GPR_T1, 0);
    if (task == 0) {
        charge(ctx, 3);
        setreg(ctx, GPR_V0, 0);
        charge(ctx, 2);
        return 0;
    }
    charge(ctx, 8);
    setreg(ctx, GPR_T2, 0);
    const u32 heads[3] = {lwr(ctx, GPR_T0, gpvar(ctx, kStartingList.head)), lwr(ctx, GPR_A3, gpvar(ctx, kRunningList.head)),
                          lwr(ctx, GPR_A2, gpvar(ctx, kEndingList.head))};
    setreg(ctx, GPR_V1, 1);
    setreg(ctx, GPR_A1, 2);
    for (u32 i = 0;; ++i) {
        charge(ctx, 3);
        setreg(ctx, GPR_V0, i < 3 ? 1u : 0u);
        if (!(i < 3)) break;
        backedge(ctx);
        charge(ctx, 2);
        if (i != 2) {
            charge(ctx, 2);
            if (i != 1) charge(ctx, 2);
        }
        charge(ctx, 3);
        u64 t = ee::core::sext32(heads[i]);
        setreg64(ctx, GPR_T1, t);
        for (;;) {
            charge(ctx, 2);
            if (t == 0) break;
            backedge(ctx);
            charge(ctx, 2);
            if (t == task) {
                charge(ctx, 3);
                setreg(ctx, GPR_V0, 1);
                charge(ctx, 2);
                return 1;
            }
            charge(ctx, 1);
            t = ee::core::sext32(lw(ctx, static_cast<u32>(t) + kOffNext));
            setreg64(ctx, GPR_T1, t);
        }
        charge(ctx, 1);
        setreg(ctx, GPR_T2, i + 1);
    }
    charge(ctx, 1);
    setreg(ctx, GPR_V0, 0);
    charge(ctx, 2);
    return 0;
}

// 0x00195520 kwlnTaskGetTimer -- 12 bytes; leaf frame (no stack)
// 0x195520 / 0x195530 / 0x195540: the frame timer and the work-area pointer.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskGetTimer(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00195520
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, tk::kTimer);
}

// 0x00195530 kwlnTaskSetWorkData -- 12 bytes; leaf frame (no stack)
// 0x195520 / 0x195530 / 0x195540: the frame timer and the work-area pointer.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskSetWorkData(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00195530
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a1, a0, tk::kWork);
}

// 0x00195540 kwlnTaskGetWorkData -- 12 bytes; leaf frame (no stack)
// 0x195520 / 0x195530 / 0x195540: the frame timer and the work-area pointer.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskGetWorkData(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00195540
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, tk::kWork);
}

// 0x00195550 kwlnTaskAddChild -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x195550 kwlnTaskAddChild(parent, child): no-op for a null parent; else the child leaves its old parent
// and becomes the parent's last child.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskAddChild(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq,
          hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& parent = s1;  // $a0
    Gpr& child = s0;  // $a1
    // 0x00195550
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(parent, sp, 0x10);
    sq(child, sp, 0x0);
    parent = a0;
    child = a1;
    if (parent != 0) {
        // 0x00195570: a child with a parent leaves it first
        charge(ctx, 3);
        lw(v1, child, tk::kParent);
        if (v1 != 0) {
            // 0x0019557c: kwlnTaskDetachParent(child)
            charge(ctx, 3);
            a0 = child;
            jal(ctx, 0x195580u, gen::fn_kwlnTaskDetachParent_001955f0);
        }
        // 0x00195588: append as the last child
        charge(ctx, 3);
        lw(a0, parent, tk::kChild);
        if (a0 == 0) {
            // 0x001955c4: the first child
            charge(ctx, 1);
            sw(child, parent, tk::kChild);
        } else {
            // 0x00195594: walk to the last sibling
            charge(ctx, 2);
            for (;;) {
                // 0x001955a0
                charge(ctx, 6);
                lw(v1, a0, tk::kSibling);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0019559c
                charge(ctx, 1);
                a0 = v1;
            }
            // 0x001955b8: last->sibling = child
            charge(ctx, 3);
            sw(child, a0, tk::kSibling);
        }
        // 0x001955c8: child->parent = parent
        charge(ctx, 1);
        sw(parent, child, tk::kParent);
    }
    // 0x001955cc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(parent, sp, 0x10);
    lq(child, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001955F0 kwlnTaskDetachParent -- 160 bytes; frame 0x10: ra sp+0x0
// 0x1955F0 kwlnTaskDetachParent(task): unlink from the parent's child chain and clear parent/sibling. A
// parentless task with a sibling asserts (line 1519).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskDetachParent(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001955f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, tk::kParent);
    if (v1 != 0) {
        // 0x0019562c: a1 = &parent->child: find the link that points at the task
        charge(ctx, 4);
        a1 = addiu(v1, tk::kChild);  // &parent->child
        lw(a2, v1, tk::kChild);
        if (a2 != a0) {
            // 0x0019564c: walk the siblings
            charge(ctx, 2);
            for (;;) {
                // 0x00195658
                charge(ctx, 6);
                lw(v1, a2, tk::kSibling);
                if (v1 == a0) {
                    break;
                }
                backedge(ctx);
                // 0x00195654
                charge(ctx, 1);
                a2 = v1;
            }
            // 0x00195670: prev->sibling = task->sibling
            charge(ctx, 2);
            lw(v1, a0, tk::kSibling);
            sw(v1, a2, tk::kSibling);
        } else {
            // 0x0019563c: it is the first child: parent->child = task->sibling
            charge(ctx, 4);
            lw(v1, a0, tk::kSibling);
            sw(v1, a1, 0);
        }
        // 0x00195678: task->parent = task->sibling = 0
        charge(ctx, 2);
        sw(zero, a0, tk::kParent);
        sw(zero, a0, tk::kSibling);
    } else {
        // 0x00195604: no parent: a sibling asserts (line 1519)
        charge(ctx, 3);
        lw(v1, a0, tk::kSibling);
        if (v1 != 0) {
            // 0x00195610
            charge(ctx, 5);
            k_assert(a0, a1, 0x19561Cu, kStrSourceFile, 1519);  // K_Assert(file, line): a no-op in retail
        }
        // 0x00195624
        charge(ctx, 2);
    }
    // 0x00195680 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00195690 kwlnTaskDetachAllChildren -- 56 bytes; leaf frame (no stack)
// 0x195690 kwlnTaskDetachAllChildren(task): clear parent/sibling of every child. A child whose parent
// field is not `task` clears the previous matching child again -- $a1 on entry if none yet (kept: the
// destroy paths leave kwlnTaskDetachParent's or kwlnTaskRemoveFromList's $a1 there).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskDetachAllChildren(EEContext& ctx) {
    using hg::Gpr, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00195690
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a2, a0, tk::kChild);
    for (;;) {
        // 0x001956b8: while (child)
        charge(ctx, 2);
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0019569c: a child of this task becomes the one cleared
        charge(ctx, 3);
        lw(v1, a2, tk::kParent);
        if (v1 == a0) {
            // 0x001956a8
            charge(ctx, 1);
            a1 = a2;
        }
        // 0x001956ac: child = child->sibling; clear parent / sibling of the last matching child ($a1)
        charge(ctx, 3);
        lw(a2, a2, tk::kSibling);
        sw(zero, a1, tk::kParent);
        sw(zero, a1, tk::kSibling);
    }
    // 0x001956c0
    charge(ctx, 2);
}

// 0x1956D0 / 0x195710 kwlnTaskSetFlags / kwlnTaskClearFlags(task, mask, mode) = kwlnTaskSetFlagsByMode(1 / 0,
// task, mask, mode). Register shuffles; $v0 is left holding the mask, as in the original.
namespace {
void flags_by_mode(EEContext& ctx, u32 set, u32 pc) {
    guest::enter(ctx, 14);
    Frame f(ctx, 16);
    f.sd(GPR_RA, 0);
    setreg64(ctx, GPR_V1, reg64(ctx, GPR_A0));
    setreg64(ctx, GPR_V0, reg64(ctx, GPR_A1));
    setreg64(ctx, GPR_A3, reg64(ctx, GPR_A2));
    setreg(ctx, GPR_A0, set);
    setreg64(ctx, GPR_A1, reg64(ctx, GPR_V1));
    setreg64(ctx, GPR_A2, reg64(ctx, GPR_V0));
    jal(ctx, pc, &gen::fn_kwlnTaskSetFlagsByMode_001944c0);
}
}  // namespace
void kwlnTaskSetFlags(EEContext& ctx) { flags_by_mode(ctx, 1, 0x1956F0); }
void kwlnTaskClearFlags(EEContext& ctx) { flags_by_mode(ctx, 0, 0x195730); }

// 0x195750 / 0x195770 / 0x195790: the two pause words of kwlnTaskUpdate, as "enabled" = word != 1.
u32 kwlnTaskIsBandAEnabled(EEContext& ctx) {
    guest::enter(ctx, 5);
    return lw(ctx, gpvar(ctx, kGpPauseBandA)) != 1 ? 1u : 0u;
}
void kwlnTaskSetBandBEnabled(EEContext& ctx, u64 enable) {
    guest::enter(ctx, 5);
    const u32 v = enable != 1 ? 1u : 0u;
    setreg(ctx, GPR_V1, v);
    sw(ctx, gpvar(ctx, kGpPauseBandB), v);
}
u32 kwlnTaskIsBandBEnabled(EEContext& ctx) {
    guest::enter(ctx, 5);
    return lw(ctx, gpvar(ctx, kGpPauseBandB)) != 1 ? 1u : 0u;
}

// 0x001957B0 kwlnTaskMoveAfter -- 228 bytes; leaf frame (no stack)
// 0x1957B0 kwlnTaskMoveAfter(ref, task): task takes ref's priority and is relinked right after ref in the
// running list (nothing when ref is not found there). The second walk's cursor is $a2.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskMoveAfter(EEContext& ctx) {
    using hg::Gpr, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    Gpr &ref = a0, &task = a1;
    // 0x001957b0: task->priority = ref->priority
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, ref, tk::kPriority);
    sw(v1, task, tk::kPriority);
    lw(a3, gp, kGpRunningHead);
    for (;;) {
        // 0x00195824: find `task` in the running list
        charge(ctx, 2);
        if (a3 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001957c4
        charge(ctx, 2);
        if (a3 == task) {
            // 0x001957cc: unlink it (its own links stay)
            charge(ctx, 3);
            lw(a2, a3, tk::kPrev);
            if (a2 == 0) {
                // 0x00195808: it was the head: next->prev = 0
                charge(ctx, 3);
                lw(v1, a3, tk::kNext);
                if (v1 != 0) {
                    // 0x00195814
                    charge(ctx, 3);
                    sw(zero, v1, tk::kPrev);
                }
            } else {
                // 0x001957d8: prev->next = next, next->prev = prev
                charge(ctx, 3);
                lw(v1, a3, tk::kNext);
                if (v1 == 0) {
                    // 0x001957fc
                    charge(ctx, 3);
                    sw(zero, a2, tk::kNext);
                } else {
                    // 0x001957e4
                    charge(ctx, 6);
                    sw(v1, a2, tk::kNext);
                    lw(a2, a3, tk::kPrev);
                    lw(v1, a3, tk::kNext);
                    sw(a2, v1, tk::kPrev);
                }
            }
            break;
        }
        // 0x00195820
        charge(ctx, 1);
        lw(a3, a3, tk::kNext);
    }
    // 0x0019582c: find `ref`
    charge(ctx, 3);
    lw(a2, gp, kGpRunningHead);
    for (;;) {
        // 0x00195884
        charge(ctx, 2);
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00195838
        charge(ctx, 2);
        if (a2 == ref) {
            // 0x00195840: link `task` right after it
            charge(ctx, 3);
            lw(v1, a2, tk::kNext);
            if (v1 == 0) {
                // 0x0019586c: ref was the last
                charge(ctx, 5);
                sw(a2, task, tk::kPrev);
                sw(zero, task, tk::kNext);
                sw(task, a2, tk::kNext);
            } else {
                // 0x0019584c
                charge(ctx, 8);
                sw(a2, task, tk::kPrev);
                lw(v1, a2, tk::kNext);
                sw(v1, task, tk::kNext);
                lw(v1, a2, tk::kNext);
                sw(task, v1, tk::kPrev);
                sw(task, a2, tk::kNext);
            }
            break;
        }
        // 0x00195880
        charge(ctx, 1);
        lw(a2, a2, tk::kNext);
    }
    // 0x0019588c
    charge(ctx, 2);
}

// 0x001958A0 kwlnTaskMoveBefore -- 224 bytes; leaf frame (no stack)
// 0x1958A0 kwlnTaskMoveBefore(ref, task): the same, right before ref.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void kwlnTaskMoveBefore(EEContext& ctx) {
    using hg::Gpr, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    Gpr &ref = a0, &task = a1;
    // 0x001958a0: task->priority = ref->priority
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, ref, tk::kPriority);
    sw(v1, task, tk::kPriority);
    lw(a3, gp, kGpRunningHead);
    for (;;) {
        // 0x00195914: find `task` in the running list
        charge(ctx, 2);
        if (a3 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001958b4
        charge(ctx, 2);
        if (a3 == task) {
            // 0x001958bc: unlink it (its own links stay)
            charge(ctx, 3);
            lw(a2, a3, tk::kPrev);
            if (a2 == 0) {
                // 0x001958f8: it was the head: next->prev = 0
                charge(ctx, 3);
                lw(v1, a3, tk::kNext);
                if (v1 != 0) {
                    // 0x00195904
                    charge(ctx, 3);
                    sw(zero, v1, tk::kPrev);
                }
            } else {
                // 0x001958c8: prev->next = next, next->prev = prev
                charge(ctx, 3);
                lw(v1, a3, tk::kNext);
                if (v1 == 0) {
                    // 0x001958ec
                    charge(ctx, 3);
                    sw(zero, a2, tk::kNext);
                } else {
                    // 0x001958d4
                    charge(ctx, 6);
                    sw(v1, a2, tk::kNext);
                    lw(a2, a3, tk::kPrev);
                    lw(v1, a3, tk::kNext);
                    sw(a2, v1, tk::kPrev);
                }
            }
            break;
        }
        // 0x00195910
        charge(ctx, 1);
        lw(a3, a3, tk::kNext);
    }
    // 0x0019591c: find `ref`
    charge(ctx, 3);
    lw(a2, gp, kGpRunningHead);
    for (;;) {
        // 0x00195970
        charge(ctx, 2);
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00195928
        charge(ctx, 2);
        if (a2 == ref) {
            // 0x00195930: link `task` right before it
            charge(ctx, 3);
            lw(v1, a2, tk::kPrev);
            if (v1 == 0) {
                // 0x00195958: ref was the first (the list head is not updated)
                charge(ctx, 5);
                sw(zero, task, tk::kPrev);
                sw(a2, task, tk::kNext);
                sw(task, a2, tk::kPrev);
            } else {
                // 0x0019593c
                charge(ctx, 7);
                sw(v1, task, tk::kPrev);
                sw(a2, task, tk::kNext);
                lw(v1, a2, tk::kPrev);
                sw(task, v1, tk::kNext);
                sw(task, a2, tk::kPrev);
            }
            break;
        }
        // 0x0019596c
        charge(ctx, 1);
        lw(a2, a2, tk::kNext);
    }
    // 0x00195978
    charge(ctx, 2);
}

// 0x198600 kwlnGetFlags() / 0x198610 kwlnSetFlags(mask, on): the kwlnRoot flag word (bits 30/31 make
// kwlnTaskUpdate skip the 0x816..0x1CE5 band); on == 1 sets the mask bits, anything else clears them. The
// whole 64-bit mask takes part ($v1 = the new word as a 64-bit register, $a0 = ~mask when clearing).
u32 kwlnGetFlags(EEContext& ctx) {
    guest::enter(ctx, 3);
    return lw(ctx, gpvar(ctx, kGpKwlnFlags));
}
void kwlnSetFlags(EEContext& ctx, u64 mask, u64 on) {
    guest::enter(ctx, 3);
    setreg(ctx, GPR_V1, 1);
    const u32 flags = gpvar(ctx, kGpKwlnFlags);
    u64 v;
    if (on != 1) {
        charge(ctx, 4);
        setreg64(ctx, GPR_A0, ~mask);
        v = ee::core::sext32(lw(ctx, flags)) & ~mask;
    } else {
        charge(ctx, 5);
        v = ee::core::sext32(lw(ctx, flags)) | mask;
    }
    setreg64(ctx, GPR_V1, v);
    sw(ctx, flags, static_cast<u32>(v));
    charge(ctx, 2);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------
namespace p3fes::recomp_gen {
using namespace p3fes::game;
using guest::arg32;
namespace {
u64 a64(const EEContext& ctx, unsigned i) { return ee::core::gpr64(ctx, GPR_A0 + i); }
void ret64(EEContext& ctx, u64 v) { ee::core::set_gpr64(ctx, GPR_V0, v); }
}  // namespace
void fn_kwlnTaskMain_001949e0(EEContext& ctx) { guest::ret32(ctx, kwlnTaskMain(ctx)); }
void fn_kwlnTaskCreate_00194b20(EEContext& ctx) { kwlnTaskCreate(ctx); }
void fn_kwlnTaskDestroyWithHierarchyByName_00194fe0(EEContext& ctx) { ret64(ctx, kwlnTaskDestroyWithHierarchyByName(ctx)); }
void fn_kwlnTaskGetState_00195290(EEContext& ctx) { guest::ret32(ctx, kwlnTaskGetState(ctx, a64(ctx, 0))); }
void fn_kwlnTaskGetUpdating_00195450(EEContext& ctx) { guest::ret32(ctx, kwlnTaskGetUpdating(ctx)); }
void fn_kwlnTaskExists_00195460(EEContext& ctx) { guest::ret32(ctx, kwlnTaskExists(ctx, a64(ctx, 0))); }
void fn_kwlnTaskSetFlags_001956d0(EEContext& ctx) { kwlnTaskSetFlags(ctx); }
void fn_kwlnTaskClearFlags_00195710(EEContext& ctx) { kwlnTaskClearFlags(ctx); }
void fn_kwlnTaskIsBandAEnabled_00195750(EEContext& ctx) { guest::ret32(ctx, kwlnTaskIsBandAEnabled(ctx)); }
void fn_kwlnTaskSetBandBEnabled_00195770(EEContext& ctx) { kwlnTaskSetBandBEnabled(ctx, a64(ctx, 0)); }
void fn_kwlnTaskIsBandBEnabled_00195790(EEContext& ctx) { guest::ret32(ctx, kwlnTaskIsBandBEnabled(ctx)); }
void fn_kwlnGetFlags_00198600(EEContext& ctx) { guest::ret32(ctx, kwlnGetFlags(ctx)); }
void fn_kwlnSetFlags_00198610(EEContext& ctx) { kwlnSetFlags(ctx, a64(ctx, 0), a64(ctx, 1)); }
}  // namespace p3fes::recomp_gen
