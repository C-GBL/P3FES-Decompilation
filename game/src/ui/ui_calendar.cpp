// Calendar arithmetic of the date/time HUD (Atlus g_data.c / clnd*), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/20_menu_ui.md section 3). Phase 5: these replace the recompiled bodies listed in
// game/replaced.txt; tests/game/test_menu_ui.cpp runs each against its __recomp body.
//
// The game date is one s16, days since April 5 (0x83679C); the month/day are recomputed on every use by
// walking the 12-entry month-length table from April (index month-1, wrapping 12 -> 1). All arithmetic
// is 16-bit (the compiler re-truncates with dsll32/dsra32 after every step), which the hand versions
// mirror with sext16. The guest::enter/charge/backedge lines are the virtual-time model of the
// recompiled bodies (ADR-0013; block costs from recomp/generated, `ctx.cycles += N` per basic block).
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 8 of the 10 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: $v0 3, frame/spills 3, scratch GPRs 1, faults only
// 1); each keeps the notes of its earlier hand version above it. The others are the hand-written versions this header
// describes.
#include "p3fes/game/ui.h"

#include "p3fes/ee/hilo.h"
#include "p3fes/game/guest.h"
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn_datGetDaysSinceApr5_0016ef20(p3fes::EEContext&);  // 0x16EF20, replaced below; the shim is the call target
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

using namespace ui;

}  // namespace

// 0x16EF20 datGetDaysSinceApr5: the s16 game date.
s32 datGetDaysSinceApr5(EEContext& ctx) {
    guest::enter(ctx, 4);
    return guest::load<s16>(ctx, kDaysSinceApr5);
}

// 0x16EF30 datGetTime: the u8 day part.
u32 datGetTime(EEContext& ctx) {
    guest::enter(ctx, 4);
    return guest::load<u8>(ctx, kTimeOfDay);
}

// 0x0017D830 clndGetMonthFromDaysSinceApr5 -- 124 bytes; leaf frame (no stack)
// 0x17D830 clndGetMonthFromDaysSinceApr5.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void clndGetMonthFromDaysSinceApr5(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lh, hg::sll,
          hg::slt, hg::slti, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x0017d830
    enter(ctx, 7);  // entry check point + this block's cycles
    a3 = 4;
    v0 = addiu(a0, 4);
    t0 = dsll32(v0, 16);
    t0 = dsra32(t0, 16);
    v1 = 1;
    a2 = 0x5E0000;
    a2 = addiu(a2, 15200);  // &tbl_clndMonthLengths
    for (;;) {
        // 0x0017d84c
        charge(ctx, 10);
        v0 = dsll32(a3, 16);
        v0 = dsra32(v0, 16);
        a0 = sll(v0, 1);
        a0 = addu(a2, a0);
        lh(a1, a0, -2);
        a0 = dsll32(t0, 16);
        a0 = dsra32(a0, 16);
        a0 = slt(a0, a1);
        if (a0 != 0) {
            break;
        }
        // 0x0017d874
        charge(ctx, 9);
        v0 = subu(t0, a1);
        t0 = dsll32(v0, 16);
        t0 = dsra32(t0, 16);
        v0 = addiu(a3, 1);
        a3 = dsll32(v0, 16);
        a3 = dsra32(a3, 16);
        at = slti(a3, 13);
        if (at != 0) {
            backedge(ctx);
        } else {
            // 0x0017d898
            charge(ctx, 3);
            a3 = v1;
            backedge(ctx);
        }
    }
    // 0x0017d8a4
    charge(ctx, 2);
}

// 0x0017D9C0 clndGetDayOfMonthFromDaysSinceApr5 -- 128 bytes; leaf frame (no stack)
// 0x17D9C0 clndGetDayOfMonthFromDaysSinceApr5.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void clndGetDayOfMonthFromDaysSinceApr5(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lh, hg::sll,
          hg::slt, hg::slti, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x0017d9c0
    enter(ctx, 7);  // entry check point + this block's cycles
    a3 = 4;
    v0 = addiu(a0, 4);
    t0 = dsll32(v0, 16);
    t0 = dsra32(t0, 16);
    v0 = 1;
    a2 = 0x5E0000;
    a2 = addiu(a2, 15200);  // &tbl_clndMonthLengths
    for (;;) {
        // 0x0017d9dc
        charge(ctx, 10);
        v1 = dsll32(a3, 16);
        v1 = dsra32(v1, 16);
        v1 = sll(v1, 1);
        v1 = addu(a2, v1);
        lh(a1, v1, -2);
        a0 = dsll32(t0, 16);
        a0 = dsra32(a0, 16);
        v1 = slt(a0, a1);
        if (v1 != 0) {
            break;
        }
        // 0x0017da04
        charge(ctx, 9);
        v1 = subu(t0, a1);
        t0 = dsll32(v1, 16);
        t0 = dsra32(t0, 16);
        v1 = addiu(a3, 1);
        a3 = dsll32(v1, 16);
        a3 = dsra32(a3, 16);
        at = slti(a3, 13);
        if (at != 0) {
            backedge(ctx);
        } else {
            // 0x0017da28
            charge(ctx, 3);
            a3 = v0;
            backedge(ctx);
        }
    }
    // 0x0017da34
    charge(ctx, 3);
    v0 = addiu(a0, 1);
}

// 0x0017D8B0 clndGetDaysSinceStartFromDate -- 112 bytes; leaf frame (no stack)
// 0x17D8B0 clndGetDaysSinceStartFromDate(month, day): the month lengths from April up to `month`, plus
// day - 5. The loop counts `month` down to 4 (wrapping 0 -> 12) while the table index runs 4..12, 1..;
// a month of 0 or below never reaches 4 within 2^32 steps, exactly as the original.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void clndGetDaysSinceStartFromDate(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lh, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x0017d8b0
    enter(ctx, 8);  // entry check point + this block's cycles
    t3 = 0;
    t2 = 4;
    a2 = 12;
    t0 = 0x5E0000;
    t0 = addiu(t0, 15200);  // &tbl_clndMonthLengths
    v1 = 13;
    v0 = 1;
    t1 = t2;
    for (;;) {
        // 0x0017d8d0
        charge(ctx, 2);
        if (a0 == t1) {
            break;
        }
        // 0x0017d8d8
        charge(ctx, 8);
        a3 = sll(t2, 1);
        a3 = addu(t0, a3);
        lh(a3, a3, -2);
        t3 = addu(t3, a3);
        t2 = addiu(t2, 1);
        a0 = addiu(a0, -1);
        if (a0 == 0) {
            // 0x0017d8f8
            charge(ctx, 1);
            a0 = a2;
        }
        // 0x0017d8fc
        charge(ctx, 2);
        if (t2 != v1) {
            backedge(ctx);
        } else {
            // 0x0017d904
            charge(ctx, 3);
            t2 = v0;
            backedge(ctx);
        }
    }
    // 0x0017d910
    charge(ctx, 4);
    v0 = addiu(a1, -5);
    v0 = addu(t3, v0);
}

// 0x0017DAE0 clndGetWeekDay -- 24 bytes; leaf frame (no stack)
// 0x17DAE0 clndGetWeekDay(days).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void clndGetWeekDay(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::div, hg::enter, hg::mfhi;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0017dae0
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = addiu(a0, 7);
    v0 = 7;
    div(v1, v0);
    mfhi(v0);
}

// 0x0017DB00 clndGetCurrentWeekDay -- 56 bytes; frame 0x10: ra sp+0x0
// 0x17DB00 clndGetCurrentWeekDay: one block around the datGetDaysSinceApr5 call.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void clndGetCurrentWeekDay_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::div, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::mfhi, hg::sd;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017db00
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x17DB08u, gen::fn_datGetDaysSinceApr5_0016ef20);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    v1 = addiu(v0, 7);
    v0 = 7;
    div(v1, v0);
    mfhi(v0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0017D920 clndGetCurrentMonth -- 156 bytes; frame 0x10: ra sp+0x0
// 0x17D920 clndGetCurrentMonth.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void clndGetCurrentMonth_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld,
          hg::lh, hg::sd, hg::sll, hg::slt, hg::slti, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017d920
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x17D928u, gen::fn_datGetDaysSinceApr5_0016ef20);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    a3 = 4;
    v0 = addiu(v0, 4);
    t0 = dsll32(v0, 16);
    t0 = dsra32(t0, 16);
    v1 = 1;
    a2 = 0x5E0000;
    a2 = addiu(a2, 15200);  // &tbl_clndMonthLengths
    for (;;) {
        // 0x0017d954
        charge(ctx, 10);
        v0 = dsll32(a3, 16);
        v0 = dsra32(v0, 16);
        a0 = sll(v0, 1);
        a0 = addu(a2, a0);
        lh(a1, a0, -2);
        a0 = dsll32(t0, 16);
        a0 = dsra32(a0, 16);
        a0 = slt(a0, a1);
        if (a0 != 0) {
            break;
        }
        // 0x0017d97c
        charge(ctx, 9);
        v0 = subu(t0, a1);
        t0 = dsll32(v0, 16);
        t0 = dsra32(t0, 16);
        v0 = addiu(a3, 1);
        a3 = dsll32(v0, 16);
        a3 = dsra32(a3, 16);
        at = slti(a3, 13);
        if (at != 0) {
            backedge(ctx);
        } else {
            // 0x0017d9a0
            charge(ctx, 3);
            a3 = v1;
            backedge(ctx);
        }
    }
    // 0x0017d9ac
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0017DA40 clndGetCurrentDay -- 160 bytes; frame 0x10: ra sp+0x0
// 0x17DA40 clndGetCurrentDay.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void clndGetCurrentDay_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld,
          hg::lh, hg::sd, hg::sll, hg::slt, hg::slti, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017da40
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x17DA48u, gen::fn_datGetDaysSinceApr5_0016ef20);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    a3 = 4;
    v0 = addiu(v0, 4);
    t0 = dsll32(v0, 16);
    t0 = dsra32(t0, 16);
    v0 = 1;
    a2 = 0x5E0000;
    a2 = addiu(a2, 15200);  // &tbl_clndMonthLengths
    for (;;) {
        // 0x0017da74
        charge(ctx, 10);
        v1 = dsll32(a3, 16);
        v1 = dsra32(v1, 16);
        v1 = sll(v1, 1);
        v1 = addu(a2, v1);
        lh(a1, v1, -2);
        a0 = dsll32(t0, 16);
        a0 = dsra32(a0, 16);
        v1 = slt(a0, a1);
        if (v1 != 0) {
            break;
        }
        // 0x0017da9c
        charge(ctx, 9);
        v1 = subu(t0, a1);
        t0 = dsll32(v1, 16);
        t0 = dsra32(t0, 16);
        v1 = addiu(a3, 1);
        a3 = dsll32(v1, 16);
        a3 = dsra32(a3, 16);
        at = slti(a3, 13);
        if (at != 0) {
            backedge(ctx);
        } else {
            // 0x0017dac0
            charge(ctx, 3);
            a3 = v0;
            backedge(ctx);
        }
    }
    // 0x0017dacc
    charge(ctx, 5);
    v0 = addiu(a0, 1);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00181B50 clndGetMoonPhase -- 24 bytes; leaf frame (no stack)
// 0x181B50 clndGetMoonPhase(days since April 5): the phase byte, 0x0E = full moon.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void clndGetMoonPhase(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::lbu;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00181b50
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x5E0000;
    v0 = addiu(v0, 14544);  // &tbl_clndMoonPhase
    v0 = addu(v0, a0);
    lbu(v0, v0, 0);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points -------------------------------------------------------------
namespace p3fes::recomp_gen {
using namespace p3fes::game;
void fn_datGetDaysSinceApr5_0016ef20(p3fes::EEContext& ctx) { guest::rets32(ctx, datGetDaysSinceApr5(ctx)); }
void fn_datGetTime_0016ef30(p3fes::EEContext& ctx) { guest::ret32(ctx, datGetTime(ctx)); }
}  // namespace p3fes::recomp_gen
