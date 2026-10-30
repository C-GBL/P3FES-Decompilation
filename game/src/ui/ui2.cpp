// Menu / UI layer, second wave (slice ui2), hand-decompiled from SLUS_216.21 (docs/ANALYSIS/20_menu_ui.md
// sections 2, 3, 3.4, 4.1, 5.1, 6). Phase 5: these replace the recompiled bodies listed in game/replaced.txt
// (section "ui2"); tests/game/test_ui2.cpp runs each against its __recomp body.
//
// Virtual time per ADR-0013: guest::enter / charge / backedge mirror the `ctx.cycles += N` blocks and the
// check points of the generated bodies. Calls into functions that are themselves replaced go through their
// generated entry points (the shims), with only the argument registers the original set changed: the rest
// of $a0..$a3 is left as the caller had it, exactly as the `jal` did. K_Assert (sub_19D3F0) is `jr $ra` in
// retail; its calls are kept (one check point, two cycles) and the bad-input path continues and stores.
// Globals addressed through $gp are absolute here ($gp = 0x7D2CF0).
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 45 of the 53 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: scratch GPRs 23, frame/spills 16, faults only 5,
// $v0 1); the others are the hand-written versions this header describes.
//
// Readability pass (read_text, 2026-10-21): the 45 generated bodies keep every statement, charge, check point and call
// of p3fes_handgen's output in the same order on every path; on top of it they name what they touch (ui2.h and
// text_view.h: `la(v0, ui2::kCounters)` for a lui/addiu pair, `hi()` / `lo()` / `gp_off()` / `gw_off()` for the
// addresses an instruction pair or a $gp / gGlobalWork offset forms, `k_assert(a0, a1, pc, kGDataFile, line)` for the
// four-statement K_Assert call, the social-stat, pad, weekday-flag and itemtbl constants), say what each block does,
// and replace the generator's gotos by if / else / break with a host bool where paths merge (none left). Each
// function's comment gives its role and, for a `sub_` name, a proposed name in brackets. datSetFlag is the lead's
// readable version and is unchanged.
#include "p3fes/game/ui2.h"

#include "p3fes/ee/core.h"
#include "p3fes/ee/fpu.h"
#include "p3fes/ee/hilo.h"
#include "p3fes/game/guest.h"
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/text_view.h"

namespace p3fes::recomp_gen {
// replaced elsewhere in game/ (called through their shims)
void fn_datGetDaysSinceApr5_0016ef20(p3fes::EEContext&);
void fn_clndGetMonthFromDaysSinceApr5_0017d830(p3fes::EEContext&);
void fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0(p3fes::EEContext&);
void fn_clndGetDaysSinceStartFromDate_0017d8b0(p3fes::EEContext&);
void fn_clndGetCurrentWeekDay_0017db00(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datGetCharmLevel_001772f0(p3fes::EEContext&);
void fn_datGetCourageLevel_00177360(p3fes::EEContext&);
// replaced in this file
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_clndIsHolidayOrSunday_0017dcf0(p3fes::EEContext&);
// still recompiled
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);   // K_Assert(file, line)
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sub_1052B0_001052b0(p3fes::EEContext&);   // the debug printer's log (vsprintf + on-screen list)
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);   // H_Snd_PlaySfx(0, 0, 0, 0): the cursor SFX
void fn_sub_172890_00172890(p3fes::EEContext&);   // day-change resets (flag 0x980 off, memset 0x836458, 56)
void fn_sub_172E10_00172e10(p3fes::EEContext&);   // day-change resets (memset 0x836498, 36)
void fn_sub_488F30_00488f30(p3fes::EEContext&);   // RpRandom
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace tview;  // text_view.h: la / k_assert / hi / lo / gp_off and the record offsets

namespace {

using namespace ui2;
namespace core = ee::core;

}  // namespace

// ===================================================================================== small accessors

// 0x00100570 H_Cursor_GetShouldDraw -- 16 bytes; leaf frame (no stack)
// H_Cursor_GetShouldDraw(task): the address of the cursor work record's should_draw word (work + 0x140; the work
// record is the task's +0x3C). One block of 4.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void H_Cursor_GetShouldDraw(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00100570
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, ui2::kTaskWorkData);  // the work record
    v0 = addiu(v0, 0x140);           // &work->should_draw
}

// 0x00111F30 sprFileIsReady -- 20 bytes; leaf frame (no stack)
// sprFileIsReady(file): the sprite file's s16 load state (+0) is 5 (loaded). One block of 5.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sprFileIsReady(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lh, hg::sltiu;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00111f30
    enter(ctx, 5);  // entry check point + this block's cycles
    lh(v0, a0, 0);
    v0 = v0 ^ 0x5;  // state == 5
    v0 = sltiu(v0, 1);
}

// 0x0011B9A0 H_Camp_GetRootSelection -- 16 bytes; leaf frame (no stack)
// H_Camp_GetRootSelection(task): the camp root list's selection (work +0xC: -2 closed, 0..6). One block of 4.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void H_Camp_GetRootSelection(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0011b9a0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, ui2::kTaskWorkData);  // the work record
    lw(v0, v0, 12);                  // its selection
}

// 0x00184D90 H_DayPartsDraw_IsIdle -- 24 bytes; leaf frame (no stack)
// H_DayPartsDraw_IsIdle(task): the day-parts HUD task's state word (work +0) is 2 (drawing, no animation
// running). One block of 6.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void H_DayPartsDraw_IsIdle(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sltiu;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00184d90
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, ui2::kTaskWorkData);  // the work record
    lw(v0, v0, 0);                   // its state
    v0 = v0 ^ 0x2;                   // state == 2
    v0 = sltiu(v0, 1);
}

// 0x195520 / 0x195530 / 0x195540 (the kwln task record fields) live in the task-system slice:
// game/src/kwln/task.cpp, declared in task.h.

// 0x17D800 [datGetScenarioMode]: 0 = The Journey, 1 = The Answer (set by the file-setup tasks).
u32 sub_17D800(EEContext& ctx) {
    guest::enter(ctx, 3);
    return guest::load<u32>(ctx, kScenarioMode);
}

// 0x17D810 / 0x17D820: one word of calendar state.
u32 sub_17D810(EEContext& ctx) {
    guest::enter(ctx, 4);
    return guest::load<u32>(ctx, kAigisCalendarState);
}

// 0x0017D820 sub_17D820 -- 16 bytes; leaf frame (no stack)
// sub_17D820 [datSetAigisCalendarState](value): stores the calendar state word that sub_17D810 reads. One block
// of 4.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_17D820(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x0017d820
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = hi(ui2::kAigisCalendarState);
    sw(a0, v1, lo(ui2::kAigisCalendarState));
}

// 0x191240 H_Memcard_ClearChkAreaSeq: the three words of the boot memory-card check sequence.
void H_Memcard_ClearChkAreaSeq(EEContext& ctx) {
    guest::enter(ctx, 5);
    for (u32 va : kMemcardChkAreaSeq) guest::store<u32>(ctx, va, 0);
}

// 0x0025A110 sub_25A110 -- 16 bytes; leaf frame (no stack)
// sub_25A110 [sflCursorSetWork](work): *work = 0 and the shuffle-time card cursor's work pointer = work
// (sub_25A120 clears it). One block of 4.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_25A110(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0025a110
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(a0, gp, gp_off(ui2::kSflCursorWork));
}
void sub_25A120(EEContext& ctx) {
    guest::enter(ctx, 3);
    guest::store<u32>(ctx, kSflCursorWork, 0);
}

// 0x001126B0 sprGetSpriteWidth -- 140 bytes; leaf frame (no stack)
// sprGetSpriteWidth(handle): the sprite's width as a float in $f0: the record's u1 - u0 (the sprite's 128-byte record
// in its file, from SprFile +0x184), or the s16 override at record +0x74 when it is non-zero, scaled by the
// handle's 4.12 scale (+0x28) when that is non-zero; converted as an unsigned word. The original's $v0 is
// left as it computes it.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sprGetSpriteWidth(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::charge, hg::cvt_s_w, hg::enter, hg::i64, hg::lh,
          hg::lhu, hg::lw, hg::mtc1, hg::mult, hg::sll, hg::srl, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0};
    // 0x001126b0
    enter(ctx, 13);  // entry check point + this block's cycles
    lw(v0, a0, 12);   // handle->sprite
    a2 = sll(v0, 7);  // * 128: the record's offset
    lw(v0, a0, 8);    // handle->file
    lw(a1, v0, kSprFileSprites);
    v0 = addu(a2, a1);
    lw(v1, v0, kSprRecordU1);
    lw(v0, v0, kSprRecordU0);
    a3 = subu(v1, v0);  // the size from the UVs
    v0 = addiu(a1, kSprRecordWidth);
    v0 = addu(v0, a2);
    lh(v0, v0, 0);
    if (v0 != 0) {
        // 0x001126e4: the override
        charge(ctx, 1);
        a3 = v0;
    }
    // 0x001126e8: the handle's scale (0 = 1.0)?
    charge(ctx, 3);
    lhu(v0, a0, 40);  // handle->scale_x
    if (v0 != 0) {
        // 0x001126f4: size = size * scale >> 12
        charge(ctx, 2);
        mult(v0, a3, v0);
        a3 = srl(v0, 12);
    }
    // 0x001126fc: to float: as an unsigned word
    charge(ctx, 2);
    if (i64(a3) < 0) {
        // 0x00112718: bit 31 set: halve (keeping the low bit), convert, double
        charge(ctx, 7);
        v1 = srl(a3, 1);
        v0 = a3 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00112704: convert
        charge(ctx, 5);
        mtc1(a3, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00112734: return
    charge(ctx, 2);
}

// 0x00112740 sprGetSpriteHeight -- 140 bytes; leaf frame (no stack)
// sprGetSpriteHeight(handle): the sprite's height as a float in $f0: the record's v1 - v0 (the sprite's 128-byte record
// in its file, from SprFile +0x184), or the s16 override at record +0x76 when it is non-zero, scaled by the
// handle's 4.12 scale (+0x2A) when that is non-zero; converted as an unsigned word. The original's $v0 is
// left as it computes it.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sprGetSpriteHeight(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::charge, hg::cvt_s_w, hg::enter, hg::i64, hg::lh,
          hg::lhu, hg::lw, hg::mtc1, hg::mult, hg::sll, hg::srl, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0};
    // 0x00112740
    enter(ctx, 13);  // entry check point + this block's cycles
    lw(v0, a0, 12);   // handle->sprite
    a2 = sll(v0, 7);  // * 128: the record's offset
    lw(v0, a0, 8);    // handle->file
    lw(a1, v0, kSprFileSprites);
    v0 = addu(a2, a1);
    lw(v1, v0, kSprRecordV1);
    lw(v0, v0, kSprRecordV0);
    a3 = subu(v1, v0);  // the size from the UVs
    v0 = addiu(a1, kSprRecordHeight);
    v0 = addu(v0, a2);
    lh(v0, v0, 0);
    if (v0 != 0) {
        // 0x00112774: the override
        charge(ctx, 1);
        a3 = v0;
    }
    // 0x00112778: the handle's scale (0 = 1.0)?
    charge(ctx, 3);
    lhu(v0, a0, 42);  // handle->scale_y
    if (v0 != 0) {
        // 0x00112784: size = size * scale >> 12
        charge(ctx, 2);
        mult(v0, a3, v0);
        a3 = srl(v0, 12);
    }
    // 0x0011278c: to float: as an unsigned word
    charge(ctx, 2);
    if (i64(a3) < 0) {
        // 0x001127a8: bit 31 set: halve (keeping the low bit), convert, double
        charge(ctx, 7);
        v1 = srl(a3, 1);
        v0 = a3 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00112794: convert
        charge(ctx, 5);
        mtc1(a3, f0);
        cvt_s_w(f0, f0);
    }
    // 0x001127c4: return
    charge(ctx, 2);
}

// ===================================================================================== day skip, counters

// 0x16EF40 / 0x16EF50 / 0x16EF60 and 0x16F150 / 0x16F160 / 0x16F170 / 0x16F180: the time-skip targets of
// clndUpdateDrawTask and the day-part setter (the getter is datGetTime).
s32 sub_16EF40(EEContext& ctx) {
    guest::enter(ctx, 4);
    return guest::load<s16>(ctx, kDaysSkipTarget);
}
u32 sub_16EF50(EEContext& ctx) {
    guest::enter(ctx, 4);
    return guest::load<u8>(ctx, kTimeSkipTarget);
}
u32 sub_16EF60(EEContext& ctx) {
    guest::enter(ctx, 4);
    return guest::load<u32>(ctx, kSkipToTarget);
}

// 0x0016F150 sub_16F150 -- 16 bytes; leaf frame (no stack)
// sub_16F150 [datSetTime](time): the day part (u8 kTimeOfDay; the getter is datGetTime). One block of 4.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_16F150(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sb;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x0016f150
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = hi(ui2::kTimeOfDay);
    sb(a0, v1, lo(ui2::kTimeOfDay));
}

// 0x0016F160 sub_16F160 -- 16 bytes; leaf frame (no stack)
// sub_16F160 [datSetDaysSkipTarget](days): the day-skip target of clndUpdateDrawTask (s16). One block of 4.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_16F160(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sh;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x0016f160
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = hi(ui2::kDaysSkipTarget);
    sh(a0, v1, lo(ui2::kDaysSkipTarget));
}

// 0x0016F170 sub_16F170 -- 16 bytes; leaf frame (no stack)
// sub_16F170 [datSetTimeSkipTarget](time): the time-skip target (u8). One block of 4.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_16F170(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sb;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x0016f170
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = hi(ui2::kTimeSkipTarget);
    sb(a0, v1, lo(ui2::kTimeSkipTarget));
}

// 0x0016F180 sub_16F180 -- 16 bytes; leaf frame (no stack)
// sub_16F180 [datSetSkipToTarget](value): the skip-to-target word. One block of 4.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_16F180(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x0016f180
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = hi(ui2::kSkipToTarget);
    sw(a0, v1, lo(ui2::kSkipToTarget));
}

// 0x0016F380 sub_16F380 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_16F380 [datGetCounter](index): kCounters[index] (g_data.c), K_Assert(index < 128) at line 2001 (a negative
// index is not caught and reads below the array, as in the original).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_16F380(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sll,
          hg::slti, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016f380
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;  // index
    v0 = slti(s0, 128);
    if (v0 == 0) {
        // 0x0016f39c: K_Assert(index < 128)
        charge(ctx, 5);
        k_assert(a0, a1, 0x16F3A8u, kGDataFile, 2001);
    }
    // 0x0016f3b0: kCounters[index]; epilogue
    charge(ctx, 10);
    v1 = sll(s0, 2);
    la(v0, ui2::kCounters);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0016F3E0 sub_16F3E0 -- 100 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_16F3E0 [datSetCounter](index, value): kCounters[index] = value, K_Assert(index < 128) at line 2007 (a
// negative index is not caught, as in the original).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_16F3E0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sll, hg::slti,
          hg::sq, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016f3e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;  // index
    s0 = a1;  // value
    v1 = slti(s1, 128);
    if (v1 == 0) {
        // 0x0016f404: K_Assert(index < 128)
        charge(ctx, 5);
        k_assert(a0, a1, 0x16F410u, kGDataFile, 2007);
    }
    // 0x0016f418: kCounters[index] = value; epilogue
    charge(ctx, 11);
    a0 = sll(s1, 2);
    la(v1, ui2::kCounters);
    v1 = addu(v1, a0);
    sw(s0, v1, 0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0016F450 sub_16F450 -- 56 bytes; leaf frame (no stack)
// sub_16F450 [datClearCounters](): zeroes counters 0..126 (the loop stops one short of the 128 the accessors
// allow), indexing from gGlobalWork. Blocks: entry 5; test 3 (first); body 4; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_16F450(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::sll, hg::slti, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016f450
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 0;
    la(a0, kGlobalWork);
    for (;;) {
        // 0x0016f474: for (i = 0; i < 127; ++i)
        charge(ctx, 3);
        v1 = slti(a1, 127);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0016f464: kCounters[i] = 0
        charge(ctx, 4);
        v1 = sll(a1, 2);
        v1 = addu(a0, v1);
        sw(zero, v1, gw_off(ui2::kCounters));
        a1 = addiu(a1, 1);
    }
    // 0x0016f480: return
    charge(ctx, 2);
}

// ===================================================================================== flags

// 0x16F1F0 datSetFlag(id, on): asserts 0 <= id < 0x1600 (g_data.c line 1933), prints "hit \n" for flag
// 0x1376 (a debug trace left in retail; printf stays recompiled, its $v0 is what this void leaves), then
// sets (on != 0, the whole register) or clears bit id % 32 of word id / 32 with C's truncating division.
//
// Register for register, from p3fes_handgen (the full-climb replay route caught the earlier host-variable version:
// it never opened the 48-byte frame, so the 128-bit `sq` spills of $s0/$s1 and the $ra spill were missing from frames
// that stay live on a thread stack in the heap). Frame 0x30: $ra at +0x20, $s1 (the flag id) at +0x10, $s0 (on) at +0.
void datSetFlag(EEContext& ctx, s32 flag_id, u64 on) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    namespace gen = ::p3fes::recomp_gen;
    core::set_gpr64(ctx, GPR_A0, core::sext32(static_cast<u32>(flag_id)));
    core::set_gpr64(ctx, GPR_A1, on);
    enter(ctx, 8);
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;  // the flag id
    s0 = a1;  // on
    // the range check: 0 <= id < kFlagCount, else K_Assert (`jr $ra` in retail: the store below still happens)
    bool bad = true;
    if (i64(s1) >= 0) {
        charge(ctx, 3);
        v1 = slti(s1, kFlagCount);
        bad = (v1 == 0);
    }
    if (bad) {
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 1933;
        jal(ctx, 0x16F228u, gen::fn_sub_19D3F0_0019d3f0);
    }
    charge(ctx, 3);
    v1 = kHitFlag;
    if (s1 == v1) {
        charge(ctx, 3);
        a0 = addiu(gp, -27976);  // "hit \n" ($a1..$a3 as they are: the format has no conversions)
        jal(ctx, 0x16F240u, gen::fn_printf_005225a8);
    }
    // word = id / 32, bit = id % 32 (C's truncating division on a negative id)
    charge(ctx, 3);
    a1 = sra(s1, 5);
    if (i64(s1) < 0) {
        charge(ctx, 2);
        v1 = addiu(s1, 31);
        a1 = sra(v1, 5);
    }
    charge(ctx, 3);
    a0 = s1 & 0x1F;
    if (i64(s1) < 0) {
        charge(ctx, 2);
        if (a0 != 0) {
            charge(ctx, 1);
            a0 = addiu(a0, -32);
        }
    }
    charge(ctx, 4);
    v1 = 1;
    a2 = sllv(v1, a0);  // the bit mask
    if (s0 == 0) {
        // clear: words[word] &= ~mask
        charge(ctx, 8);
        a0 = sll(a1, 2);
        v1 = 0x840000;
        v1 = addiu(v1, -24036);  // &g_datFlagWords (kFlagWords)
        a1 = addu(v1, a0);
        a0 = nor(a2, 0);
        lw(v1, a1, 0);
        v1 = v1 & a0;
        sw(v1, a1, 0);
    } else {
        // set: words[word] |= mask
        charge(ctx, 9);
        a0 = sll(a1, 2);
        v1 = 0x840000;
        v1 = addiu(v1, -24036);  // &g_datFlagWords (kFlagWords)
        a0 = addu(v1, a0);
        lw(v1, a0, 0);
        v1 = v1 | a2;
        sw(v1, a0, 0);
    }
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0016F2E0 datClearFlagAll -- 56 bytes; leaf frame (no stack)
// datClearFlagAll(): zeroes the 176 flag words (all 5,632 flags), indexing from gGlobalWork. Blocks: entry 5;
// test 3 (first); body 4; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void datClearFlagAll(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::sll, hg::slti, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016f2e0
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 0;
    la(a0, kGlobalWork);
    for (;;) {
        // 0x0016f304: for (i = 0; i < 176; ++i)
        charge(ctx, 3);
        v1 = slti(a1, ui2::kFlagWordCount);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0016f2f4: kFlagWords[i] = 0
        charge(ctx, 4);
        v1 = sll(a1, 2);
        v1 = addu(a0, v1);
        sw(zero, v1, gw_off(ui2::kFlagWords));
        a1 = addiu(a1, 1);
    }
    // 0x0016f310: return
    charge(ctx, 2);
}

// 0x003951D0 MT_Misc_BitChk -- 36 bytes; frame 0x10: ra sp+0x0
// MT_Misc_BitChk(id): datGetFlag(id) != 0; $a0 is passed on as it came. One block of 9 around the call.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void MT_Misc_BitChk_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd, hg::sltu;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003951d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3951D8u, gen::fn_datGetFlag_0016f190);
    v0 = sltu(0, v0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00395170 sub_395170 -- 36 bytes; frame 0x10: ra sp+0x0
// sub_395170 [MT_Misc_BitOn](id): datSetFlag(id, 1). One block of 9 around the call.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_395170(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00395170
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 1;
    jal(ctx, 0x39517Cu, gen::fn_datSetFlag_0016f1f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003951A0 sub_3951A0 -- 36 bytes; frame 0x10: ra sp+0x0
// sub_3951A0 [MT_Misc_BitOff](id): datSetFlag(id, 0). One block of 9 around the call.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_3951A0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003951a0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 0;
    jal(ctx, 0x3951ACu, gen::fn_datSetFlag_0016f1f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// ===================================================================================== social stats

// 0x0016C6F0 sub_16C6F0 -- 80 bytes; leaf frame (no stack)
// sub_16C6F0 [datGetAcademicPoint](character): the academic points (s16) of a character: the protagonist's (character 1) at
// kProtagonistStats, the others' at kCharacterStats + 868 * character. Blocks: entry 5; other 9 / protagonist
// 4; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_16C6F0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lh, hg::sll, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0016c6f0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);  // (s16)character
    v1 = dsra32(v1, 16);
    v0 = 1;
    if (v1 != v0) {
        // 0x0016c714: another character: kCharacterStats + 868 * character (((c * 31) * 7) * 4)
        charge(ctx, 9);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        la(v0, ui2::kCharacterStats + social::kAcademic);
        v0 = addu(v0, v1);
        lh(v0, v0, 0);
    } else {
        // 0x0016c704: the protagonist
        charge(ctx, 4);
        v0 = hi(ui2::kProtagonistStats + social::kAcademic);
        lh(v0, v0, lo(ui2::kProtagonistStats + social::kAcademic));
    }
    // 0x0016c738: return
    charge(ctx, 2);
}

// 0x0016C740 sub_16C740 -- 80 bytes; leaf frame (no stack)
// sub_16C740 [datGetCharmPoint](character): the charm points (s16) of a character: the protagonist's (character 1) at
// kProtagonistStats, the others' at kCharacterStats + 868 * character. Blocks: entry 5; other 9 / protagonist
// 4; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_16C740(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lh, hg::sll, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0016c740
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);  // (s16)character
    v1 = dsra32(v1, 16);
    v0 = 1;
    if (v1 != v0) {
        // 0x0016c764: another character: kCharacterStats + 868 * character (((c * 31) * 7) * 4)
        charge(ctx, 9);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        la(v0, ui2::kCharacterStats + social::kCharm);
        v0 = addu(v0, v1);
        lh(v0, v0, 0);
    } else {
        // 0x0016c754: the protagonist
        charge(ctx, 4);
        v0 = hi(ui2::kProtagonistStats + social::kCharm);
        lh(v0, v0, lo(ui2::kProtagonistStats + social::kCharm));
    }
    // 0x0016c788: return
    charge(ctx, 2);
}

// 0x0016C790 sub_16C790 -- 80 bytes; leaf frame (no stack)
// sub_16C790 [datGetCouragePoint](character): the courage points (s16) of a character: the protagonist's (character 1) at
// kProtagonistStats, the others' at kCharacterStats + 868 * character. Blocks: entry 5; other 9 / protagonist
// 4; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_16C790(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lh, hg::sll, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0016c790
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);  // (s16)character
    v1 = dsra32(v1, 16);
    v0 = 1;
    if (v1 != v0) {
        // 0x0016c7b4: another character: kCharacterStats + 868 * character (((c * 31) * 7) * 4)
        charge(ctx, 9);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        la(v0, ui2::kCharacterStats + social::kCourage);
        v0 = addu(v0, v1);
        lh(v0, v0, 0);
    } else {
        // 0x0016c7a4: the protagonist
        charge(ctx, 4);
        v0 = hi(ui2::kProtagonistStats + social::kCourage);
        lh(v0, v0, lo(ui2::kProtagonistStats + social::kCourage));
    }
    // 0x0016c7d8: return
    charge(ctx, 2);
}

// 0x0016CFE0 sub_16CFE0 -- 168 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_16CFE0 [datSetAcademicPoint](character, points): stores the academic points (s16) of a character (the protagonist's at
// kProtagonistStats, the others' at kCharacterStats + 868 * character). K_Assert(0 <= points < 1000) at line
// 797 (`jr $ra` in retail: the store happens anyway).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_16CFE0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::jal, hg::ld,
          hg::lq, hg::sd, hg::sh, hg::sll, hg::slti, hg::sq, hg::subu;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016cfe0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;  // character
    s0 = a1;  // points
    v1 = dsll32(s0, 16);
    v1 = dsra32(v1, 16);
    bool in_range = false;  // 0 <= (s16)points < 1000
    if (i64(v1) >= 0) {
        // 0x0016d008: points < 1000
        charge(ctx, 3);
        at = slti(v1, social::kPointLimit);
        in_range = at != 0;
    }
    if (!in_range) {
        // 0x0016d014: K_Assert(0 <= points < 1000)
        charge(ctx, 5);
        k_assert(a0, a1, 0x16D020u, kGDataFile, 797);
    }
    // 0x0016d028: the protagonist (character 1)?
    charge(ctx, 5);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    v1 = 1;
    if (a0 != v1) {
        // 0x0016d04c: another character: kCharacterStats + 868 * character
        charge(ctx, 9);
        v1 = sll(a0, 5);
        a0 = subu(v1, a0);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 2);
        la(v1, ui2::kCharacterStats + social::kAcademic);
        v1 = addu(v1, a0);
        sh(s0, v1, 0);
    } else {
        // 0x0016d03c: the protagonist
        charge(ctx, 4);
        v1 = hi(ui2::kProtagonistStats + social::kAcademic);
        sh(s0, v1, lo(ui2::kProtagonistStats + social::kAcademic));
    }
    // 0x0016d070: epilogue
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0016D090 sub_16D090 -- 200 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_16D090 [datSetCharmPoint](character, points): stores the charm points (s16) of a character (the protagonist's at
// kProtagonistStats, the others' at kCharacterStats + 868 * character). K_Assert(0 <= points < 1000) at line
// 808 (`jr $ra` in retail: the store happens anyway). For the protagonist the level function is called on the old and the new points, the
// results dropped.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_16D090(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::jal, hg::ld,
          hg::lh, hg::lq, hg::sd, hg::sh, hg::sll, hg::slti, hg::sq, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016d090
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;  // character
    s0 = a1;  // points
    v1 = dsll32(s0, 16);
    v1 = dsra32(v1, 16);
    bool in_range = false;  // 0 <= (s16)points < 1000
    if (i64(v1) >= 0) {
        // 0x0016d0b8: points < 1000
        charge(ctx, 3);
        at = slti(v1, social::kPointLimit);
        in_range = at != 0;
    }
    if (!in_range) {
        // 0x0016d0c4: K_Assert(0 <= points < 1000)
        charge(ctx, 5);
        k_assert(a0, a1, 0x16D0D0u, kGDataFile, 808);
    }
    // 0x0016d0d8: the protagonist (character 1)?
    charge(ctx, 5);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    v1 = 1;
    if (a0 != v1) {
        // 0x0016d11c: another character: kCharacterStats + 868 * character
        charge(ctx, 9);
        v1 = sll(a0, 5);
        a0 = subu(v1, a0);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 2);
        la(v1, ui2::kCharacterStats + social::kCharm);
        v1 = addu(v1, a0);
        sh(s0, v1, 0);
    } else {
        // 0x0016d0ec: the protagonist: datGetCharmLevel(old points), store, datGetCharmLevel(new points) (results unused)
        charge(ctx, 12);
        v0 = hi(ui2::kProtagonistStats + social::kCharm);
        lh(a0, v0, lo(ui2::kProtagonistStats + social::kCharm));
        jal(ctx, 0x16D0F4u, gen::fn_datGetCharmLevel_001772f0);
        v0 = hi(ui2::kProtagonistStats + social::kCharm);
        sh(s0, v0, lo(ui2::kProtagonistStats + social::kCharm));
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x16D10Cu, gen::fn_datGetCharmLevel_001772f0);
    }
    // 0x0016d140: epilogue
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0016D160 sub_16D160 -- 200 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_16D160 [datSetCouragePoint](character, points): stores the courage points (s16) of a character (the protagonist's at
// kProtagonistStats, the others' at kCharacterStats + 868 * character). K_Assert(0 <= points < 1000) at line
// 828 (`jr $ra` in retail: the store happens anyway). For the protagonist the level function is called on the old and the new points, the
// results dropped.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_16D160(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::jal, hg::ld,
          hg::lh, hg::lq, hg::sd, hg::sh, hg::sll, hg::slti, hg::sq, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016d160
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;  // character
    s0 = a1;  // points
    v1 = dsll32(s0, 16);
    v1 = dsra32(v1, 16);
    bool in_range = false;  // 0 <= (s16)points < 1000
    if (i64(v1) >= 0) {
        // 0x0016d188: points < 1000
        charge(ctx, 3);
        at = slti(v1, social::kPointLimit);
        in_range = at != 0;
    }
    if (!in_range) {
        // 0x0016d194: K_Assert(0 <= points < 1000)
        charge(ctx, 5);
        k_assert(a0, a1, 0x16D1A0u, kGDataFile, 828);
    }
    // 0x0016d1a8: the protagonist (character 1)?
    charge(ctx, 5);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    v1 = 1;
    if (a0 != v1) {
        // 0x0016d1ec: another character: kCharacterStats + 868 * character
        charge(ctx, 9);
        v1 = sll(a0, 5);
        a0 = subu(v1, a0);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 2);
        la(v1, ui2::kCharacterStats + social::kCourage);
        v1 = addu(v1, a0);
        sh(s0, v1, 0);
    } else {
        // 0x0016d1bc: the protagonist: datGetCourageLevel(old points), store, datGetCourageLevel(new points) (results unused)
        charge(ctx, 12);
        v0 = hi(ui2::kProtagonistStats + social::kCourage);
        lh(a0, v0, lo(ui2::kProtagonistStats + social::kCourage));
        jal(ctx, 0x16D1C4u, gen::fn_datGetCourageLevel_00177360);
        v0 = hi(ui2::kProtagonistStats + social::kCourage);
        sh(s0, v0, lo(ui2::kProtagonistStats + social::kCourage));
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x16D1DCu, gen::fn_datGetCourageLevel_00177360);
    }
    // 0x0016d210: epilogue
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// ===================================================================================== calendar

// 0x00181B10 clndGetCurrentMoonPhase -- 56 bytes; frame 0x10: ra sp+0x0
// clndGetCurrentMoonPhase(): the moon phase of the current day, kMoonPhaseTable[(s16)datGetDaysSinceApr5()]. One
// block of 14 around the call.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void clndGetCurrentMoonPhase_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::lbu, hg::ld, hg::sd;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00181b10
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x181B18u, gen::fn_datGetDaysSinceApr5_0016ef20);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    la(v0, ui2::kMoonPhaseTable);
    v0 = addu(v0, v1);
    lbu(v0, v0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0017DCF0 clndIsHolidayOrSunday -- 252 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// clndIsHolidayOrSunday(): 1 when the current day is a Sunday ((days + 7) % 7 == 0: April 5 was a Sunday) or a
// kHolidays date ({s16 month, s16 day} entries, month -1 ends the table, at most 356 scanned), else 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void clndIsHolidayOrSunday_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::div, hg::dsll32, hg::dsra32, hg::enter,
          hg::jal, hg::ld, hg::lh, hg::lq, hg::mfhi, hg::sd, hg::si, hg::sll, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017dcf0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x17DD00u, gen::fn_datGetDaysSinceApr5_0016ef20);
    s1 = dsll32(v0, 16);  // days (s16)
    s1 = dsra32(s1, 16);
    v1 = addiu(s1, 7);
    v0 = 7;
    div(v1, v0);
    mfhi(v0);
    if (v0 != 0) {
        // 0x0017dd34: not a Sunday: s0 = the month, a3 = the day of the month; walk the holidays
        charge(ctx, 18);
        a0 = s1;
        jal(ctx, 0x17DD38u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
        s0 = dsll32(v0, 16);
        s0 = dsra32(s0, 16);
        a0 = s1;
        jal(ctx, 0x17DD4Cu, gen::fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0);
        a3 = dsll32(v0, 16);
        a3 = dsra32(a3, 16);
        t0 = 0;
        a2 = dsll32(s0, 16);
        a2 = dsra32(a2, 16);
        la(a1, ui2::kHolidays);
        a0 = si(-1);  // the table's end marker
        bool holiday = false;
        for (;;) {
            // 0x0017ddbc: for (i = 0; i < 356; ++i) (i as s16)
            charge(ctx, 5);
            v1 = dsll32(t0, 16);
            v1 = dsra32(v1, 16);
            v0 = slti(v1, ui2::kHolidayScanLimit);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0017dd7c: the entry {month, day}; month -1 ends the table
            charge(ctx, 5);
            v0 = sll(v1, 2);
            v1 = addu(a1, v0);
            lh(v0, v1, 0);
            if (v0 == a0) {
                break;
            }
            // 0x0017dd90: the month matches?
            charge(ctx, 2);
            if (a2 == v0) {
                // 0x0017dd98: the day matches -> a holiday
                charge(ctx, 3);
                lh(v0, v1, 2);
                if (a3 == v0) {
                    holiday = true;
                    break;
                }
            }
            // 0x0017ddb0: ++i
            charge(ctx, 3);
            v0 = addiu(t0, 1);
            t0 = dsll32(v0, 16);
            t0 = dsra32(t0, 16);
        }
        if (!holiday) {
            // 0x0017ddd0: not in the table: 0
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0017dda4: a holiday: 1
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x0017dd28: a Sunday: 1
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0017ddd4: epilogue
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0017DB40 sub_17DB40 -- 420 bytes; leaf frame (no stack)
// sub_17DB40 [clndIsHolidayOrSundayFromDays](days): clndIsHolidayOrSunday for a given day, with the month and
// day-of-month walks of the calendar inlined (both walk kMonthLengths from April, wrapping after month 12; the
// second one recomputes the remainder), then the same holiday-table walk.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_17DB40(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::div, hg::dsll32, hg::dsra32, hg::enter, hg::lh,
          hg::mfhi, hg::si, hg::sll, hg::slt, hg::slti, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x0017db40
    enter(ctx, 8);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);  // days (s16)
    a0 = dsra32(a0, 16);
    v1 = addiu(a0, 7);
    v0 = 7;
    div(v1, v0);
    mfhi(v0);
    if (v0 != 0) {
        // 0x0017db6c: not a Sunday: the month walk: t0 = month (from 4), t1 = the days left (days + 4)
        charge(ctx, 7);
        t0 = 4;
        a3 = addiu(a0, 4);
        t1 = dsll32(a3, 16);
        t1 = dsra32(t1, 16);
        v0 = 1;
        la(a1, ui2::kMonthLengths);
        for (;;) {
            // 0x0017db88: the days left < this month's length -> the month is found
            charge(ctx, 10);
            a2 = dsll32(t0, 16);
            a2 = dsra32(a2, 16);
            v1 = sll(a2, 1);
            v1 = addu(a1, v1);
            lh(a0, v1, -2);
            v1 = dsll32(t1, 16);
            v1 = dsra32(v1, 16);
            v1 = slt(v1, a0);
            if (v1 != 0) {
                break;
            }
            // 0x0017dbb0: the next month (12 wraps to 1)
            charge(ctx, 9);
            v1 = subu(t1, a0);
            t1 = dsll32(v1, 16);
            t1 = dsra32(t1, 16);
            v1 = addiu(t0, 1);
            t0 = dsll32(v1, 16);
            t0 = dsra32(t0, 16);
            at = slti(t0, 13);
            if (at != 0) {
                backedge(ctx);
            } else {
                // 0x0017dbd4: month 13 -> 1
                charge(ctx, 3);
                t0 = v0;
                backedge(ctx);
            }
        }
        // 0x0017dbe0: the day walk: t0 = the month found; t1 = month from 4, a3 = the days left again
        charge(ctx, 8);
        t0 = dsll32(a2, 16);
        t0 = dsra32(t0, 16);
        t1 = 4;
        a3 = dsll32(a3, 16);
        a3 = dsra32(a3, 16);
        v0 = 1;
        la(a2, ui2::kMonthLengths);
        for (;;) {
            // 0x0017dc00: the days left < this month's length -> a0 = the day of the month - 1
            charge(ctx, 10);
            v1 = dsll32(t1, 16);
            v1 = dsra32(v1, 16);
            v1 = sll(v1, 1);
            v1 = addu(a2, v1);
            lh(a1, v1, -2);
            a0 = dsll32(a3, 16);
            a0 = dsra32(a0, 16);
            v1 = slt(a0, a1);
            if (v1 != 0) {
                break;
            }
            // 0x0017dc28: the next month (12 wraps to 1)
            charge(ctx, 9);
            v1 = subu(a3, a1);
            a3 = dsll32(v1, 16);
            a3 = dsra32(a3, 16);
            v1 = addiu(t1, 1);
            t1 = dsll32(v1, 16);
            t1 = dsra32(t1, 16);
            at = slti(t1, 13);
            if (at != 0) {
                backedge(ctx);
            } else {
                // 0x0017dc4c: month 13 -> 1
                charge(ctx, 3);
                t1 = v0;
                backedge(ctx);
            }
        }
        // 0x0017dc58: a3 = the day of the month, a2 = the month; walk the holidays
        charge(ctx, 11);
        v0 = addiu(a0, 1);
        a3 = dsll32(v0, 16);
        a3 = dsra32(a3, 16);
        t1 = 0;
        a2 = dsll32(t0, 16);
        a2 = dsra32(a2, 16);
        la(a1, ui2::kHolidays);
        a0 = si(-1);  // the table's end marker
        bool holiday = false;
        for (;;) {
            // 0x0017dcc4: for (i = 0; i < 356; ++i) (i as s16)
            charge(ctx, 5);
            v1 = dsll32(t1, 16);
            v1 = dsra32(v1, 16);
            v0 = slti(v1, ui2::kHolidayScanLimit);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0017dc84: the entry {month, day}; month -1 ends the table
            charge(ctx, 5);
            v0 = sll(v1, 2);
            v1 = addu(a1, v0);
            lh(v0, v1, 0);
            if (v0 == a0) {
                break;
            }
            // 0x0017dc98: the month matches?
            charge(ctx, 2);
            if (a2 == v0) {
                // 0x0017dca0: the day matches -> a holiday
                charge(ctx, 3);
                lh(v0, v1, 2);
                if (a3 == v0) {
                    holiday = true;
                    break;
                }
            }
            // 0x0017dcb8: ++i
            charge(ctx, 3);
            v0 = addiu(t1, 1);
            t1 = dsll32(v0, 16);
            t1 = dsra32(t1, 16);
        }
        if (!holiday) {
            // 0x0017dcd8: not in the table: 0
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0017dcac: a holiday: 1
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x0017db60: a Sunday: 1
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0017dcdc: return
    charge(ctx, 2);
}

// 0x0017E480 clndIsDateInRange -- 160 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// clndIsDateInRange(m0, d0, m1, d1): 1 when start <= today <= end, comparing days since April 5
// (clndGetDaysSinceStartFromDate of both ends, datGetDaysSinceApr5 read twice), else 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void clndIsDateInRange_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd,
          hg::slt, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017e480: s1 = start, s0 = end (days since April 5); today >= start?
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a2;
    s0 = a3;
    jal(ctx, 0x17E49Cu, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
    s1 = v0;
    a0 = s2;
    a1 = s0;
    jal(ctx, 0x17E4B0u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
    s0 = v0;
    jal(ctx, 0x17E4BCu, gen::fn_datGetDaysSinceApr5_0016ef20);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    v0 = slt(v0, s1);
    bool inside = false;
    if (v0 == 0) {
        // 0x0017e4d8: today <= end?
        charge(ctx, 7);
        jal(ctx, 0x17E4D8u, gen::fn_datGetDaysSinceApr5_0016ef20);
        v0 = dsll32(v0, 16);
        v0 = dsra32(v0, 16);
        at = slt(s0, v0);
        inside = at == 0;
    }
    if (inside) {
        // 0x0017e4f4: 1
        charge(ctx, 3);
        v0 = 1;
    } else {
        // 0x0017e500: 0
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0017e504: epilogue
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0017E520 sub_17E520 -- 176 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_17E520 [clndIsDateInRangeFromDate](m, d, m0, d0, m1 in $t0, d1 in $t1): 1 when start <= (m, d) <= end in
// days since April 5 (clndGetDaysSinceStartFromDate of all three), else 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_17E520_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::slt, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017e520: s1 = start, s0 = end, v0 = the date (days since April 5); date >= start?
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;  // m
    s3 = a1;  // d
    s2 = t0;  // m1
    s0 = t1;  // d1
    a0 = a2;
    a1 = a3;
    jal(ctx, 0x17E554u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
    s1 = v0;
    a0 = s2;
    a1 = s0;
    jal(ctx, 0x17E568u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
    s0 = v0;
    a0 = s4;
    a1 = s3;
    jal(ctx, 0x17E57Cu, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
    v1 = slt(v0, s1);
    bool inside = false;
    if (v1 == 0) {
        // 0x0017e590: date <= end?
        charge(ctx, 3);
        at = slt(s0, v0);
        inside = at == 0;
    }
    if (inside) {
        // 0x0017e59c: 1
        charge(ctx, 3);
        v0 = 1;
    } else {
        // 0x0017e5a8: 0
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0017e5ac: epilogue
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0017E5D0 clndIsDateInRangeFromStart -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// clndIsDateInRangeFromStart(m, d, n): 1 when today lies within the n days starting at (m, d), else 0; n == 0
// logs "Calender chk range is 0 " through the (still recompiled) debug printer sub_1052B0 and returns 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void clndIsDateInRangeFromStart_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq,
          hg::sd, hg::slt, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017e5d0: s0 = n
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a2;
    if (s0 != 0) {
        // 0x0017e608: s1 = start, s0 = start + n - 1; today >= start?
        charge(ctx, 12);
        jal(ctx, 0x17E608u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
        s1 = v0;
        v0 = addiu(s0, -1);
        s0 = addu(s1, v0);
        jal(ctx, 0x17E61Cu, gen::fn_datGetDaysSinceApr5_0016ef20);
        v0 = dsll32(v0, 16);
        v0 = dsra32(v0, 16);
        v0 = slt(v0, s1);
        bool inside = false;
        if (v0 == 0) {
            // 0x0017e638: today <= the last day?
            charge(ctx, 7);
            jal(ctx, 0x17E638u, gen::fn_datGetDaysSinceApr5_0016ef20);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            at = slt(s0, v0);
            inside = at == 0;
        }
        if (inside) {
            // 0x0017e654: 1
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x0017e660: 0
            charge(ctx, 1);
            v0 = 0;
        }
    } else {
        // 0x0017e5ec: n == 0: the debug message, 0
        charge(ctx, 7);
        la(a0, ui2::kRangeZeroString);  // "Calender chk range is 0 "
        jal(ctx, 0x17E5F4u, gen::fn_sub_1052B0_001052b0);
        v0 = 0;
    }
    // 0x0017e664: epilogue
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0016EF70 datSetDaysSinceApr5 -- 468 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// datSetDaysSinceApr5(days): clears the weekday flags 0xA08..0xA0E and the holiday flag 0xA0F; when the date
// changes runs the two day-change resets (sub_172890, sub_172E10) and clears flag 0x98C; stores the date; sets
// the new weekday's flag (the jump table 0x7B6460, weekday 0 = Sunday -> 0xA0E) and 0xA0F on a holiday or
// Sunday. A weekday >= 7 skips the flag.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datSetDaysSinceApr5(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lh,
          hg::lq, hg::lw, hg::sd, hg::sh, hg::sll, hg::sltiu, hg::sq, hg::tail;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016ef70
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;  // days
    // clear the weekday flags 0xA08..0xA0E and the holiday flag 0xA0F
    a0 = ui2::kWeekdayFlagFirst + 0;  // Monday
    a1 = 0;
    jal(ctx, 0x16EF88u, gen::fn_datSetFlag_0016f1f0);
    a0 = ui2::kWeekdayFlagFirst + 1;  // Tuesday
    a1 = 0;
    jal(ctx, 0x16EF98u, gen::fn_datSetFlag_0016f1f0);
    a0 = ui2::kWeekdayFlagFirst + 2;  // Wednesday
    a1 = 0;
    jal(ctx, 0x16EFA8u, gen::fn_datSetFlag_0016f1f0);
    a0 = ui2::kWeekdayFlagFirst + 3;  // Thursday
    a1 = 0;
    jal(ctx, 0x16EFB8u, gen::fn_datSetFlag_0016f1f0);
    a0 = ui2::kWeekdayFlagFirst + 4;  // Friday
    a1 = 0;
    jal(ctx, 0x16EFC8u, gen::fn_datSetFlag_0016f1f0);
    a0 = ui2::kWeekdayFlagFirst + 5;  // Saturday
    a1 = 0;
    jal(ctx, 0x16EFD8u, gen::fn_datSetFlag_0016f1f0);
    a0 = ui2::kWeekdayFlagFirst + 6;  // Sunday
    a1 = 0;
    jal(ctx, 0x16EFE8u, gen::fn_datSetFlag_0016f1f0);
    a0 = ui2::kHolidayFlag;
    a1 = 0;
    jal(ctx, 0x16EFF8u, gen::fn_datSetFlag_0016f1f0);
    v1 = dsll32(s0, 16);
    v1 = dsra32(v1, 16);
    v0 = hi(ui2::kDaysSinceApr5);
    lh(v0, v0, lo(ui2::kDaysSinceApr5));
    if (v1 != v0) {
        // 0x0016f018: the date changes: the two day-change resets, clear flag 0x98C
        charge(ctx, 8);
        jal(ctx, 0x16F018u, gen::fn_sub_172890_00172890);
        jal(ctx, 0x16F020u, gen::fn_sub_172E10_00172e10);
        a0 = ui2::kDayChangedFlag;
        a1 = 0;
        jal(ctx, 0x16F030u, gen::fn_datSetFlag_0016f1f0);
    }
    // 0x0016f038: store the date; v0 = the weekday (0 Sunday .. 6)
    charge(ctx, 7);
    v0 = hi(ui2::kDaysSinceApr5);
    sh(s0, v0, lo(ui2::kDaysSinceApr5));
    jal(ctx, 0x16F040u, gen::fn_clndGetCurrentWeekDay_0017db00);
    at = sltiu(v0, 7);
    if (at != 0) {
        // 0x0016f054: set the weekday's flag through the jump table
        charge(ctx, 7);
        la(v1, kWeekdayJumpTable);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x16F070u:  // table[0]
            // 0x0016f070: Sunday
            charge(ctx, 6);
            a0 = ui2::kWeekdayFlagFirst + 6;
            a1 = 1;
            jal(ctx, 0x16F078u, gen::fn_datSetFlag_0016f1f0);
            break;
        case 0x16F088u:  // table[1]
            // 0x0016f088: Monday
            charge(ctx, 6);
            a0 = ui2::kWeekdayFlagFirst + 0;
            a1 = 1;
            jal(ctx, 0x16F090u, gen::fn_datSetFlag_0016f1f0);
            break;
        case 0x16F0A0u:  // table[2]
            // 0x0016f0a0: Tuesday
            charge(ctx, 6);
            a0 = ui2::kWeekdayFlagFirst + 1;
            a1 = 1;
            jal(ctx, 0x16F0A8u, gen::fn_datSetFlag_0016f1f0);
            break;
        case 0x16F0B8u:  // table[3]
            // 0x0016f0b8: Wednesday
            charge(ctx, 6);
            a0 = ui2::kWeekdayFlagFirst + 2;
            a1 = 1;
            jal(ctx, 0x16F0C0u, gen::fn_datSetFlag_0016f1f0);
            break;
        case 0x16F0D0u:  // table[4]
            // 0x0016f0d0: Thursday
            charge(ctx, 6);
            a0 = ui2::kWeekdayFlagFirst + 3;
            a1 = 1;
            jal(ctx, 0x16F0D8u, gen::fn_datSetFlag_0016f1f0);
            break;
        case 0x16F0E8u:  // table[5]
            // 0x0016f0e8: Friday
            charge(ctx, 6);
            a0 = ui2::kWeekdayFlagFirst + 4;
            a1 = 1;
            jal(ctx, 0x16F0F0u, gen::fn_datSetFlag_0016f1f0);
            break;
        case 0x16F100u:  // table[6]
            // 0x0016f100: Saturday
            charge(ctx, 4);
            a0 = ui2::kWeekdayFlagFirst + 5;
            a1 = 1;
            jal(ctx, 0x16F108u, gen::fn_datSetFlag_0016f1f0);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    // 0x0016f110: a holiday or a Sunday?
    charge(ctx, 4);
    jal(ctx, 0x16F110u, gen::fn_clndIsHolidayOrSunday_0017dcf0);
    if (v0 != 0) {
        // 0x0016f120: set the holiday flag
        charge(ctx, 4);
        a0 = ui2::kHolidayFlag;
        a1 = 1;
        jal(ctx, 0x16F128u, gen::fn_datSetFlag_0016f1f0);
    }
    // 0x0016f130: epilogue
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// ===================================================================================== camp

// 0x0011ABD0 H_Camp_MoveListCursor -- 1240 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// H_Camp_MoveListCursor(count, page, &scroll, &cursor): the list navigation of the camp sub-screens. `page` rows
// are visible from `scroll`; `cursor` is the row within the page. Up (0x1000, pressed or repeat) moves toward
// the top, scrolling while the cursor is on row 1 and wrapping from the top to the last page on a fresh press;
// down (0x4000) is the mirror image, keeping the cursor on row page - 2 while it can scroll and wrapping from the
// last entry to the top; page keys 0x1 / 0x2 move by a page. Each move plays H_Snd_PlaySfx(0, 0, 0, 0) and the
// two out-parameters are written only when something moved (the return value, 0 / 1). Lists of 0 or 1 entries
// do not move.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void H_Camp_MoveListCursor(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::slt, hg::sltu, hg::sq, hg::subu, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0011abd0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;  // count
    s4 = a1;  // page (rows visible)
    s3 = a2;  // &scroll
    s2 = a3;  // &cursor
    lw(s0, a2, 0);  // s0 = scroll
    lw(s1, a3, 0);  // s1 = cursor (the row within the page)
    v0 = 0;         // moved
    a1 = 1;         // up: pressed, or the repeat edge
    v1 = hi(ui2::kPadPressed);
    lhu(a0, v1, lo(ui2::kPadPressed));
    v1 = a0 & ui2::kPadUp;
    if (v1 == 0) {
        // 0x0011ac24: up not pressed: the repeat edge?
        charge(ctx, 5);
        v1 = hi(ui2::kPadRepeat);
        lhu(v1, v1, lo(ui2::kPadRepeat));
        v1 = v1 & ui2::kPadUp;
        if (v1 == 0) {
            // 0x0011ac38: not up
            charge(ctx, 1);
            a1 = 0;
        }
    }
    // 0x0011ac3c: up?
    charge(ctx, 2);
    if (a1 == 0) {
        // 0x0011ad74: down: pressed or the repeat edge
        charge(ctx, 4);
        v1 = a0 & ui2::kPadDown;
        v1 = sltu(0, v1);
        if (v1 == 0) {
            // 0x0011ad84: the repeat edge
            charge(ctx, 4);
            v1 = hi(ui2::kPadRepeat);
            lhu(v1, v1, lo(ui2::kPadRepeat));
            v1 = v1 & ui2::kPadDown;
            v1 = sltu(0, v1);
        }
        // 0x0011ad94: down?
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0011af58: neither: page up?
            charge(ctx, 3);
            v1 = a0 & ui2::kPadPagePrev;
            if (v1 == 0) {
                // 0x0011afe4: page down?
                charge(ctx, 3);
                v1 = a0 & ui2::kPadPageNext;
                if (v1 != 0) {
                    // 0x0011aff0: only when the list is longer than a page
                    charge(ctx, 3);
                    at = slt(s4, s5);
                    if (at != 0) {
                        // 0x0011affc: a whole page more below?
                        charge(ctx, 5);
                        v1 = sll(s4, 1);
                        v1 = addu(v1, s0);
                        at = slt(v1, s5);
                        if (at == 0) {
                            // 0x0011b038: no: to the last page (scroll = count - page) unless already there
                            charge(ctx, 3);
                            s4 = subu(s5, s4);
                            if (s0 != s4) {
                                // 0x0011b044: move
                                charge(ctx, 8);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x11B054u, gen::fn_sub_10A4E0_0010a4e0);  // H_Snd_PlaySfx(0, 0, 0, 0): the cursor sound
                                v0 = 1;
                                s0 = s4;
                            }
                        } else {
                            // 0x0011b010: scroll += page
                            charge(ctx, 10);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x11B020u, gen::fn_sub_10A4E0_0010a4e0);  // H_Snd_PlaySfx(0, 0, 0, 0): the cursor sound
                            v0 = 1;
                            s0 = addu(s0, s4);
                        }
                        // 0x0011b064: cursor on row 0 -> row 1
                        charge(ctx, 2);
                        if (s1 == 0) {
                            // 0x0011b06c: ++cursor
                            charge(ctx, 1);
                            s1 = addiu(s1, 1);
                        }
                    }
                }
            } else {
                // 0x0011af64: page up: only when the list is longer than a page
                charge(ctx, 3);
                at = slt(s4, s5);
                if (at != 0) {
                    // 0x0011af70: less than a page above?
                    charge(ctx, 3);
                    v1 = slt(s0, s4);
                    if (v1 != 0) {
                        // 0x0011afa4: to the top unless already there
                        charge(ctx, 2);
                        if (s0 != 0) {
                            // 0x0011afac: scroll = 0
                            charge(ctx, 8);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x11AFBCu, gen::fn_sub_10A4E0_0010a4e0);  // H_Snd_PlaySfx(0, 0, 0, 0): the cursor sound
                            v0 = 1;
                            s0 = 0;
                        }
                    } else {
                        // 0x0011af7c: scroll -= page
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        jal(ctx, 0x11AF8Cu, gen::fn_sub_10A4E0_0010a4e0);  // H_Snd_PlaySfx(0, 0, 0, 0): the cursor sound
                        v0 = 1;
                        s0 = subu(s0, s4);
                    }
                    // 0x0011afcc: cursor on the last row -> one up
                    charge(ctx, 3);
                    v1 = addiu(s4, -1);
                    if (s1 == v1) {
                        // 0x0011afd8: --cursor
                        charge(ctx, 3);
                        s1 = addiu(s1, -1);
                    }
                }
            }
        } else {
            // 0x0011ad9c: down: the cursor on row page - 2 (where it scrolls)?
            charge(ctx, 3);
            v1 = addiu(s4, -2);
            if (s1 != v1) {
                // 0x0011ae9c: no: the cursor on the last entry?
                charge(ctx, 4);
                a0 = addiu(s5, -1);
                v1 = addu(s0, s1);
                if (a0 != v1) {
                    // 0x0011af1c: no: lists of 0 or 1 entries do not move
                    charge(ctx, 2);
                    if (s5 != 0) {
                        // 0x0011af24
                        charge(ctx, 3);
                        v1 = 1;
                        if (s5 != v1) {
                            // 0x0011af30: ++cursor
                            charge(ctx, 10);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x11AF40u, gen::fn_sub_10A4E0_0010a4e0);  // H_Snd_PlaySfx(0, 0, 0, 0): the cursor sound
                            v0 = 1;
                            s1 = addiu(s1, 1);
                        }
                    }
                } else {
                    // 0x0011aeac: the last entry: wrap to the top on a fresh press (held word or its repeat)
                    charge(ctx, 6);
                    v1 = hi(ui2::kPadHeld);
                    lhu(v1, v1, lo(ui2::kPadHeld));
                    v1 = v1 & ui2::kPadDown;
                    v1 = sltu(0, v1);
                    if (v1 == 0) {
                        // 0x0011aec4
                        charge(ctx, 4);
                        v1 = hi(ui2::kPadRepeatHeld);
                        lhu(v1, v1, lo(ui2::kPadRepeatHeld));
                        v1 = v1 & ui2::kPadDown;
                        v1 = sltu(0, v1);
                    }
                    // 0x0011aed4
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x0011aedc: lists of 0 or 1 entries do not move
                        charge(ctx, 2);
                        if (s5 != 0) {
                            // 0x0011aee4
                            charge(ctx, 3);
                            v1 = 1;
                            if (s5 != v1) {
                                // 0x0011aef0: scroll = cursor = 0
                                charge(ctx, 11);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x11AF00u, gen::fn_sub_10A4E0_0010a4e0);  // H_Snd_PlaySfx(0, 0, 0, 0): the cursor sound
                                v0 = 1;
                                s0 = 0;
                                s1 = 0;
                            }
                        }
                    }
                }
            } else {
                // 0x0011ada8: row page - 2: can the list scroll?
                charge(ctx, 4);
                v1 = addu(s0, s4);
                at = slt(v1, s5);
                if (at == 0) {
                    // 0x0011ade0: no: is there a row below the cursor?
                    charge(ctx, 5);
                    v1 = addiu(s4, -1);
                    v1 = addu(s0, v1);
                    at = slt(v1, s5);
                    if (at == 0) {
                        // 0x0011ae1c: no: the cursor on the last entry?
                        charge(ctx, 4);
                        a0 = addiu(s5, -1);
                        v1 = addu(s0, s1);
                        if (a0 == v1) {
                            // 0x0011ae2c: wrap to the top on a fresh press
                            charge(ctx, 6);
                            v1 = hi(ui2::kPadHeld);
                            lhu(v1, v1, lo(ui2::kPadHeld));
                            v1 = v1 & ui2::kPadDown;
                            v1 = sltu(0, v1);
                            if (v1 == 0) {
                                // 0x0011ae44
                                charge(ctx, 4);
                                v1 = hi(ui2::kPadRepeatHeld);
                                lhu(v1, v1, lo(ui2::kPadRepeatHeld));
                                v1 = v1 & ui2::kPadDown;
                                v1 = sltu(0, v1);
                            }
                            // 0x0011ae54
                            charge(ctx, 2);
                            if (v1 != 0) {
                                // 0x0011ae5c: lists of 0 or 1 entries do not move
                                charge(ctx, 2);
                                if (s5 != 0) {
                                    // 0x0011ae64
                                    charge(ctx, 3);
                                    v1 = 1;
                                    if (s5 != v1) {
                                        // 0x0011ae70: scroll = cursor = 0
                                        charge(ctx, 11);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x11AE80u, gen::fn_sub_10A4E0_0010a4e0);  // H_Snd_PlaySfx(0, 0, 0, 0): the cursor sound
                                        v0 = 1;
                                        s0 = 0;
                                        s1 = 0;
                                    }
                                }
                            }
                        }
                    } else {
                        // 0x0011adf4: ++cursor
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        jal(ctx, 0x11AE04u, gen::fn_sub_10A4E0_0010a4e0);  // H_Snd_PlaySfx(0, 0, 0, 0): the cursor sound
                        v0 = 1;
                        s1 = addiu(s1, 1);
                    }
                } else {
                    // 0x0011adb8: ++scroll
                    charge(ctx, 10);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 0;
                    jal(ctx, 0x11ADC8u, gen::fn_sub_10A4E0_0010a4e0);  // H_Snd_PlaySfx(0, 0, 0, 0): the cursor sound
                    v0 = 1;
                    s0 = addiu(s0, 1);
                }
            }
        }
    } else {
        // 0x0011ac44: up: the cursor on row 1 (where it scrolls)?
        charge(ctx, 3);
        v1 = 1;
        if (s1 != v1) {
            // 0x0011ac8c: no: on row 0?
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x0011ad3c: no: lists of 0 or 1 entries do not move
                charge(ctx, 2);
                if (s5 != 0) {
                    // 0x0011ad44
                    charge(ctx, 2);
                    if (s5 != v1) {
                        // 0x0011ad4c: --cursor
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        jal(ctx, 0x11AD5Cu, gen::fn_sub_10A4E0_0010a4e0);  // H_Snd_PlaySfx(0, 0, 0, 0): the cursor sound
                        v0 = 1;
                        s1 = addiu(s1, -1);
                    }
                }
            } else {
                // 0x0011ac94: row 0: wrap to the bottom on a fresh press (held word or its repeat)
                charge(ctx, 6);
                v1 = hi(ui2::kPadHeld);
                lhu(v1, v1, lo(ui2::kPadHeld));
                v1 = v1 & ui2::kPadUp;
                v1 = sltu(0, v1);
                if (v1 == 0) {
                    // 0x0011acac
                    charge(ctx, 4);
                    v1 = hi(ui2::kPadRepeatHeld);
                    lhu(v1, v1, lo(ui2::kPadRepeatHeld));
                    v1 = v1 & ui2::kPadUp;
                    v1 = sltu(0, v1);
                }
                // 0x0011acbc
                charge(ctx, 2);
                if (v1 != 0) {
                    // 0x0011acc4: a list longer than a page?
                    charge(ctx, 3);
                    at = slt(s4, s5);
                    if (at == 0) {
                        // 0x0011acfc: no: lists of 0 or 1 entries do not move
                        charge(ctx, 2);
                        if (s5 != 0) {
                            // 0x0011ad04
                            charge(ctx, 3);
                            v1 = 1;
                            if (s5 != v1) {
                                // 0x0011ad10: cursor = count - 1, scroll = 0
                                charge(ctx, 11);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x11AD20u, gen::fn_sub_10A4E0_0010a4e0);  // H_Snd_PlaySfx(0, 0, 0, 0): the cursor sound
                                v0 = 1;
                                s1 = addiu(s5, -1);
                                s0 = 0;
                            }
                        }
                    } else {
                        // 0x0011acd0: yes: cursor = page - 1, scroll = count - page
                        charge(ctx, 11);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        jal(ctx, 0x11ACE0u, gen::fn_sub_10A4E0_0010a4e0);  // H_Snd_PlaySfx(0, 0, 0, 0): the cursor sound
                        v0 = 1;
                        s1 = addiu(s4, -1);
                        s0 = subu(s5, s4);
                    }
                }
            }
        } else {
            // 0x0011ac50: row 1: scroll up, or move the cursor to row 0 at the top
            charge(ctx, 9);
            a0 = 0;
            a1 = 0;
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x11AC60u, gen::fn_sub_10A4E0_0010a4e0);  // H_Snd_PlaySfx(0, 0, 0, 0): the cursor sound
            v0 = 1;
            if (s0 == 0) {
                // 0x0011ac80: --cursor
                charge(ctx, 3);
                s1 = addiu(s1, -1);
            } else {
                // 0x0011ac74: --scroll
                charge(ctx, 3);
                s0 = addiu(s0, -1);
            }
        }
    }
    // 0x0011b070: moved: write the scroll and cursor back
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x0011b078
        charge(ctx, 2);
        sw(s0, s3, 0);
        sw(s1, s2, 0);
    }
    // 0x0011b080: epilogue
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// ===================================================================================== event/itemtbl.bin

// 0x0016C2F0 datItemTblSetSections -- 380 bytes; leaf frame (no stack)
// datItemTblSetSections(): walks the 13 counted sections of event/itemtbl.bin at kItemTbl (each a 16-byte header
// whose first word is the record count, then the records: 40, 16, 32, 32, 36, 28, 28, 16, 32, 20, 32, 8, 12
// bytes) storing each first record's address in its $gp slot (ui2::kItemTblSectionSlot), then fills
// kItemTblTail with the 35 records of 32 bytes after the 14th header. The counts are trusted. The multiplies
// by the record sizes are the compiler's shift / add forms. Blocks: entry 85; test 3 (first); body 5; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void datItemTblSetSections(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sll, hg::sltiu, hg::subu,
          hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x0016c2f0
    enter(ctx, 85);  // entry check point + this block's cycles
    la(v1, ui2::kItemTbl);
    lw(a1, v1, itemtbl::kCount);         // section 0's record count
    a0 = addiu(v1, itemtbl::kHeaderSize);  // its first record
    sw(a0, gp, gp_off(ui2::kItemTblSectionSlot[0]));
    v1 = sll(a1, 2);
    v1 = addu(v1, a1);
    v1 = sll(v1, 3);
    a0 = addu(a0, v1);
    lw(v1, a0, itemtbl::kCount);  // the next section's count
    a0 = addiu(a0, itemtbl::kHeaderSize);
    sw(a0, gp, gp_off(ui2::kItemTblSectionSlot[1]));
    v1 = sll(v1, 4);
    a0 = addu(a0, v1);
    lw(v1, a0, itemtbl::kCount);  // the next section's count
    a0 = addiu(a0, itemtbl::kHeaderSize);
    sw(a0, gp, gp_off(ui2::kItemTblSectionSlot[2]));
    v1 = sll(v1, 5);
    a0 = addu(a0, v1);
    lw(v1, a0, itemtbl::kCount);  // the next section's count
    a0 = addiu(a0, itemtbl::kHeaderSize);
    sw(a0, gp, gp_off(ui2::kItemTblSectionSlot[3]));
    v1 = sll(v1, 5);
    v1 = addu(a0, v1);
    lw(a1, v1, itemtbl::kCount);  // the next section's count
    a0 = addiu(v1, itemtbl::kHeaderSize);
    sw(a0, gp, gp_off(ui2::kItemTblSectionSlot[4]));
    v1 = sll(a1, 3);
    v1 = addu(v1, a1);
    v1 = sll(v1, 2);
    v1 = addu(a0, v1);
    lw(a1, v1, itemtbl::kCount);  // the next section's count
    a0 = addiu(v1, itemtbl::kHeaderSize);
    sw(a0, gp, gp_off(ui2::kItemTblSectionSlot[5]));
    v1 = sll(a1, 3);
    v1 = subu(v1, a1);
    v1 = sll(v1, 2);
    v1 = addu(a0, v1);
    lw(a1, v1, itemtbl::kCount);  // the next section's count
    a0 = addiu(v1, itemtbl::kHeaderSize);
    sw(a0, gp, gp_off(ui2::kItemTblSectionSlot[6]));
    v1 = sll(a1, 3);
    v1 = subu(v1, a1);
    v1 = sll(v1, 2);
    a0 = addu(a0, v1);
    lw(v1, a0, itemtbl::kCount);  // the next section's count
    a0 = addiu(a0, itemtbl::kHeaderSize);
    sw(a0, gp, gp_off(ui2::kItemTblSectionSlot[7]));
    v1 = sll(v1, 4);
    a0 = addu(a0, v1);
    lw(v1, a0, itemtbl::kCount);  // the next section's count
    a0 = addiu(a0, itemtbl::kHeaderSize);
    sw(a0, gp, gp_off(ui2::kItemTblSectionSlot[8]));
    v1 = sll(v1, 5);
    v1 = addu(a0, v1);
    lw(a1, v1, itemtbl::kCount);  // the next section's count
    a0 = addiu(v1, itemtbl::kHeaderSize);
    sw(a0, gp, gp_off(ui2::kItemTblSectionSlot[9]));
    v1 = sll(a1, 2);
    v1 = addu(v1, a1);
    v1 = sll(v1, 2);
    a0 = addu(a0, v1);
    lw(v1, a0, itemtbl::kCount);  // the next section's count
    a0 = addiu(a0, itemtbl::kHeaderSize);
    sw(a0, gp, gp_off(ui2::kItemTblSectionSlot[10]));
    v1 = sll(v1, 5);
    a0 = addu(a0, v1);
    lw(v1, a0, itemtbl::kCount);  // the next section's count
    a0 = addiu(a0, itemtbl::kHeaderSize);
    sw(a0, gp, gp_off(ui2::kItemTblSectionSlot[11]));
    v1 = sll(v1, 3);
    v1 = addu(a0, v1);
    lw(a1, v1, itemtbl::kCount);  // the next section's count
    a0 = addiu(v1, itemtbl::kHeaderSize);
    sw(a0, gp, gp_off(ui2::kItemTblSectionSlot[12]));
    v1 = sll(a1, 1);
    v1 = addu(v1, a1);
    v1 = sll(v1, 2);
    v1 = addu(a0, v1);
    a2 = addiu(v1, itemtbl::kHeaderSize);  // the 35 records after the 14th header
    a1 = 0;
    la(a0, ui2::kItemTblTail);
    for (;;) {
        // 0x0016c458: for (i = 0; i < 35; ++i)
        charge(ctx, 3);
        v1 = sltiu(a1, ui2::kItemTblTailCount);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0016c444: kItemTblTail[i] = record; record += 32
        charge(ctx, 5);
        v1 = sll(a1, 2);
        v1 = addu(a0, v1);
        sw(a2, v1, 0);
        a2 = addiu(a2, itemtbl::kTailRecordSize);
        a1 = addiu(a1, 1);
    }
    // 0x0016c464: return
    charge(ctx, 2);
}

// 0x00170D60 sub_170D60 -- 60 bytes; leaf frame (no stack)
// sub_170D60 [datItemTblGetRecord0](id): the record of an item id < 1000 in section 0 (40 bytes), 0 otherwise
// (ids are s16; a negative id is not caught). Blocks: entry 5; out of range 1 / record 7; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_170D60(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lw, hg::sll, hg::slti;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00170d60
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);  // (s16)id
    v1 = dsra32(v1, 16);
    at = slti(v1, 1000);
    if (at == 0) {
        // 0x00170d90: out of range: 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00170d74: section 0 + 40 * id
        charge(ctx, 7);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 3);
        lw(v0, gp, gp_off(ui2::kItemTblSectionSlot[0]));
        v0 = addu(v0, v1);
    }
    // 0x00170d94: return
    charge(ctx, 2);
}

// 0x00170DA0 sub_170DA0 -- 68 bytes; leaf frame (no stack)
// sub_170DA0 [datItemTblGetRecord2](id): the record of an item id in 1000..1999 in section 2 (32 bytes), 0 otherwise
// (ids are s16). Blocks: entry 5; range test 3; record 6 / out of range 1; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_170DA0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lw, hg::sll, hg::slti;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00170da0: id (s16) >= 1000?
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = slti(v1, 1000);
    bool in_range = false;
    if (v0 == 0) {
        // 0x00170db4: id < 2000?
        charge(ctx, 3);
        at = slti(v1, 2000);
        in_range = at != 0;
    }
    if (in_range) {
        // 0x00170dc0: section 2 + 32 * (id - 1000)
        charge(ctx, 6);
        v0 = addiu(v1, -1000);
        v1 = sll(v0, 5);
        lw(v0, gp, gp_off(ui2::kItemTblSectionSlot[2]));
        v0 = addu(v0, v1);
    } else {
        // 0x00170dd8: out of range: 0
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x00170ddc: return
    charge(ctx, 2);
}

// 0x00170DF0 sub_170DF0 -- 68 bytes; leaf frame (no stack)
// sub_170DF0 [datItemTblGetRecord3](id): the record of an item id in 2000..2999 in section 3 (32 bytes), 0 otherwise
// (ids are s16). Blocks: entry 5; range test 3; record 6 / out of range 1; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_170DF0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lw, hg::sll, hg::slti;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00170df0: id (s16) >= 2000?
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = slti(v1, 2000);
    bool in_range = false;
    if (v0 == 0) {
        // 0x00170e04: id < 3000?
        charge(ctx, 3);
        at = slti(v1, 3000);
        in_range = at != 0;
    }
    if (in_range) {
        // 0x00170e10: section 3 + 32 * (id - 2000)
        charge(ctx, 6);
        v0 = addiu(v1, -2000);
        v1 = sll(v0, 5);
        lw(v0, gp, gp_off(ui2::kItemTblSectionSlot[3]));
        v0 = addu(v0, v1);
    } else {
        // 0x00170e28: out of range: 0
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x00170e2c: return
    charge(ctx, 2);
}

// 0x00170E40 sub_170E40 -- 76 bytes; leaf frame (no stack)
// sub_170E40 [datItemTblGetRecord4](id): the record of an item id in 3000..3999 in section 4 (36 bytes), 0 otherwise
// (ids are s16). Blocks: entry 5; range test 3; record 8 / out of range 1; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_170E40(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lw, hg::sll, hg::slti;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00170e40: id (s16) >= 3000?
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = slti(v1, 3000);
    bool in_range = false;
    if (v0 == 0) {
        // 0x00170e54: id < 4000?
        charge(ctx, 3);
        at = slti(v1, 4000);
        in_range = at != 0;
    }
    if (in_range) {
        // 0x00170e60: section 4 + 36 * (id - 3000)
        charge(ctx, 8);
        v1 = addiu(v1, -3000);
        v0 = sll(v1, 3);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        lw(v0, gp, gp_off(ui2::kItemTblSectionSlot[4]));
        v0 = addu(v0, v1);
    } else {
        // 0x00170e80: out of range: 0
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x00170e84: return
    charge(ctx, 2);
}

// 0x00170E90 sub_170E90 -- 64 bytes; leaf frame (no stack)
// sub_170E90 [datItemTblGetRecord6](id): section 6 (28 bytes) at id - 4000; the guard is id >= 3000, so ids
// 3000..3999 index before the section (as in the original). Blocks: entry 5; out of range 1 / record 8;
// return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_170E90(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lw, hg::sll, hg::slti,
          hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00170e90
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);  // (s16)id
    v1 = dsra32(v1, 16);
    v0 = slti(v1, 3000);
    if (v0 != 0) {
        // 0x00170ec4: id < 3000: 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00170ea4: section 6 + 28 * (id - 4000)
        charge(ctx, 8);
        v1 = addiu(v1, -4000);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        lw(v0, gp, gp_off(ui2::kItemTblSectionSlot[6]));
        v0 = addu(v0, v1);
    }
    // 0x00170ec8: return
    charge(ctx, 2);
}

// 0x00170ED0 sub_170ED0 -- 388 bytes; leaf frame (no stack)
// sub_170ED0 [datItemTblGetRecord](id, &kind): the record of any item id, choosing by its range (< 1000, < 2000,
// < 3000, < 4000, else) the inlined lookups of sections 0, 2, 3, 4 and 6 and storing the range (0..4) in *kind;
// each inlined lookup keeps its own range checks and its own return block.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_170ED0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lw, hg::sll, hg::slti,
          hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x00170ed0: v1 = (s16)id; < 1000?
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    at = slti(v1, 1000);
    if (at == 0) {
        // 0x00170f1c: < 2000?
        charge(ctx, 3);
        at = slti(v1, 2000);
        if (at == 0) {
            // 0x00170f6c: < 3000?
            charge(ctx, 3);
            at = slti(v1, 3000);
            if (at == 0) {
                // 0x00170fbc: < 4000?
                charge(ctx, 3);
                at = slti(v1, 4000);
                if (at == 0) {
                    // 0x00171014: kind 4: section 6 (the inlined sub_170E90)
                    charge(ctx, 5);
                    v0 = 4;
                    sw(v0, a1, 0);
                    v0 = slti(v1, 3000);
                    if (v0 != 0) {
                        // 0x00171048
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x00171028: section 6 + 28 * (id - 4000)
                        charge(ctx, 8);
                        v1 = addiu(v1, -4000);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 2);
                        lw(v0, gp, gp_off(ui2::kItemTblSectionSlot[6]));
                        v0 = addu(v0, v1);
                    }
                } else {
                    // 0x00170fc8: kind 3: section 4 (the inlined sub_170E40)
                    charge(ctx, 5);
                    v0 = 3;
                    sw(v0, a1, 0);
                    v0 = slti(v1, 3000);
                    bool in_range = false;
                    if (v0 == 0) {
                        // 0x00170fdc
                        charge(ctx, 3);
                        at = slti(v1, 4000);
                        in_range = at != 0;
                    }
                    if (in_range) {
                        // 0x00170fe8: section 4 + 36 * (id - 3000)
                        charge(ctx, 8);
                        v1 = addiu(v1, -3000);
                        v0 = sll(v1, 3);
                        v0 = addu(v0, v1);
                        v1 = sll(v0, 2);
                        lw(v0, gp, gp_off(ui2::kItemTblSectionSlot[4]));
                        v0 = addu(v0, v1);
                    } else {
                        // 0x00171008
                        charge(ctx, 1);
                        v0 = 0;
                    }
                    // 0x0017100c
                    charge(ctx, 2);
                }
            } else {
                // 0x00170f78: kind 2: section 3 (the inlined sub_170DF0)
                charge(ctx, 5);
                v0 = 2;
                sw(v0, a1, 0);
                v0 = slti(v1, 2000);
                bool in_range = false;
                if (v0 == 0) {
                    // 0x00170f8c
                    charge(ctx, 3);
                    at = slti(v1, 3000);
                    in_range = at != 0;
                }
                if (in_range) {
                    // 0x00170f98: section 3 + 32 * (id - 2000)
                    charge(ctx, 6);
                    v0 = addiu(v1, -2000);
                    v1 = sll(v0, 5);
                    lw(v0, gp, gp_off(ui2::kItemTblSectionSlot[3]));
                    v0 = addu(v0, v1);
                } else {
                    // 0x00170fb0
                    charge(ctx, 1);
                    v0 = 0;
                }
                // 0x00170fb4
                charge(ctx, 2);
            }
        } else {
            // 0x00170f28: kind 1: section 2 (the inlined sub_170DA0)
            charge(ctx, 5);
            v0 = 1;
            sw(v0, a1, 0);
            v0 = slti(v1, 1000);
            bool in_range = false;
            if (v0 == 0) {
                // 0x00170f3c
                charge(ctx, 3);
                at = slti(v1, 2000);
                in_range = at != 0;
            }
            if (in_range) {
                // 0x00170f48: section 2 + 32 * (id - 1000)
                charge(ctx, 6);
                v0 = addiu(v1, -1000);
                v1 = sll(v0, 5);
                lw(v0, gp, gp_off(ui2::kItemTblSectionSlot[2]));
                v0 = addu(v0, v1);
            } else {
                // 0x00170f60
                charge(ctx, 1);
                v0 = 0;
            }
            // 0x00170f64
            charge(ctx, 2);
        }
    } else {
        // 0x00170ee4: kind 0: section 0 (the inlined sub_170D60)
        charge(ctx, 4);
        sw(zero, a1, 0);
        at = slti(v1, 1000);
        if (at == 0) {
            // 0x00170f10
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x00170ef4: section 0 + 40 * id
            charge(ctx, 7);
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v1 = sll(v0, 3);
            lw(v0, gp, gp_off(ui2::kItemTblSectionSlot[0]));
            v0 = addu(v0, v1);
        }
        // 0x00170f14
        charge(ctx, 2);
    }
    // 0x0017104c: return
    charge(ctx, 2);
}

// 0x001714B0 sub_1714B0 -- 20 bytes; leaf frame (no stack)
// sub_1714B0 [datItemTblGetSection7Record](i): section 7's record i (16 bytes), unchecked. One block of 5.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_1714B0(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::enter, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x001714b0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = sll(a0, 4);
    lw(v0, gp, gp_off(ui2::kItemTblSectionSlot[7]));
    v0 = addu(v0, v1);
}

// 0x001714D0 sub_1714D0 -- 20 bytes; leaf frame (no stack)
// sub_1714D0 [datItemTblGetSection8Record](i): section 8's record i (32 bytes), unchecked. One block of 5.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_1714D0(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::enter, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x001714d0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = sll(a0, 5);
    lw(v0, gp, gp_off(ui2::kItemTblSectionSlot[8]));
    v0 = addu(v0, v1);
}

// 0x001714F0 sub_1714F0 -- 20 bytes; leaf frame (no stack)
// sub_1714F0 [datItemTblGetSection11Record](i): section 11's record i (8 bytes), unchecked. One block of 5.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_1714F0(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::enter, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x001714f0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = sll(a0, 3);
    lw(v0, gp, gp_off(ui2::kItemTblSectionSlot[11]));
    v0 = addu(v0, v1);
}

// 0x00171510 sub_171510 -- 56 bytes; leaf frame (no stack)
// sub_171510 [datItemTblGetSection9Float](row, column): float `column` of section 9's 20-byte row `row` (both
// s16), returned in $f0; the address stays in $v0 (the original's scratch). One block of 14.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_171510(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addu, hg::dsll32, hg::dsra32, hg::enter, hg::lw, hg::lwc1, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    Fpr f0{ctx, 0};
    // 0x00171510
    enter(ctx, 14);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);  // row (s16): 20 * row = (row * 5) * 4
    v1 = dsra32(v1, 16);
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    lw(v0, gp, gp_off(ui2::kItemTblSectionSlot[9]));
    v1 = addu(v0, v1);
    v0 = dsll32(a1, 16);  // column (s16)
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 2);
    v0 = addu(v1, v0);
    lwc1(f0, v0, 0);
}

// 0x00171550 sub_171550 -- 160 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_171550 [datItemTblPickWeighted](-, -, table): a weighted pick from section 10's 32-byte record `table`
// (u16): 16 {weight, value} byte pairs; r = RpRandom() % 100 (unsigned), the first pair whose running weight sum
// reaches past r gives its value, else the last pair's value. RpRandom is called with the argument registers as
// they came.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_171550(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::divu, hg::enter, hg::jal, hg::lbu, hg::ld,
          hg::lq, hg::lw, hg::mfhi, hg::sd, hg::sll, hg::slti, hg::sltu, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00171550: a3 = r = RpRandom() % 100; t0 = the weight sum, t1 = the pair; a0 = the record
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a2;  // table
    jal(ctx, 0x171560u, gen::fn_sub_488F30_00488f30);
    v1 = 100;
    divu(v0, v1);
    mfhi(a3);
    t0 = 0;
    t1 = 0;
    lw(a2, gp, gp_off(ui2::kItemTblSectionSlot[10]));
    v0 = s0 & 0xFFFF;
    a1 = sll(v0, 5);
    a0 = addu(a2, a1);
    bool picked = false;
    for (;;) {
        // 0x001715c8: for (i = 0; i < 16; ++i)
        charge(ctx, 3);
        v0 = slti(t1, 16);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00171594: sum += pair[i].weight; sum > r -> picked
        charge(ctx, 7);
        v1 = sll(t1, 1);
        v0 = addu(a0, v1);
        lbu(v0, v0, 0);
        t0 = addu(t0, v0);
        at = sltu(t0, a3);
        if (at == 0) {
            picked = true;
            break;
        }
        // 0x001715c4
        charge(ctx, 1);
        t1 = addiu(t1, 1);
    }
    if (!picked) {
        // 0x001715d4: none: the last pair's value (record + 31)
        charge(ctx, 2);
        v0 = addu(a1, a2);
        lbu(v0, v0, 31);
    } else {
        // 0x001715b0: pair[i].value
        charge(ctx, 5);
        v0 = addu(a1, a2);
        v0 = addu(v1, v0);
        lbu(v0, v0, 1);
    }
    // 0x001715dc: epilogue
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------
// Void functions leave $v0 as their last callee (or the caller) had it.
namespace p3fes::recomp_gen {
using namespace p3fes::game;
using p3fes::game::guest::arg32;
using p3fes::game::guest::args32;
using p3fes::game::guest::ret32;
using p3fes::game::guest::rets32;
void fn_sub_17D800_0017d800(p3fes::EEContext& ctx) { ret32(ctx, sub_17D800(ctx)); }
void fn_sub_17D810_0017d810(p3fes::EEContext& ctx) { ret32(ctx, sub_17D810(ctx)); }
void fn_H_Memcard_ClearChkAreaSeq_00191240(p3fes::EEContext& ctx) { H_Memcard_ClearChkAreaSeq(ctx); }
void fn_sub_25A120_0025a120(p3fes::EEContext& ctx) { sub_25A120(ctx); }
void fn_sub_16EF40_0016ef40(p3fes::EEContext& ctx) { rets32(ctx, sub_16EF40(ctx)); }
void fn_sub_16EF50_0016ef50(p3fes::EEContext& ctx) { ret32(ctx, sub_16EF50(ctx)); }
void fn_sub_16EF60_0016ef60(p3fes::EEContext& ctx) { ret32(ctx, sub_16EF60(ctx)); }
void fn_datSetFlag_0016f1f0(p3fes::EEContext& ctx) { datSetFlag(ctx, args32(ctx, 0), ee::core::gpr64(ctx, GPR_A1)); }
}  // namespace p3fes::recomp_gen
