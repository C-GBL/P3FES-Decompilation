// Phase 5 slice libs5: CRI Sofdec SFD, the stream core's shared helpers: the handle's parameter table, the transfer
// slots and their method dispatch, the time base, the timer hooks, the condition table (0x599100-0x59C9F0).
// p3fes_handgen bodies (game/include/p3fes/game/hg_cpu.h); every statement, charge and check point is the
// generator's. Roles, proposed names and the record layouts: game/include/p3fes/game/libs5.h. Names are
// symbols/functions.json's (ADR-0009); roles are read from the instructions and the binary's own strings
// (no CRI material was opened). Pair tests: tests/game/test_libs5.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs5.h"

namespace p3fes::recomp_gen {
void fn_memset_00521408(p3fes::EEContext&);
void fn_sub_56F4B8_0056f4b8(p3fes::EEContext&);
void fn_sub_58BE40_0058be40(p3fes::EEContext&);
void fn_sub_58C060_0058c060(p3fes::EEContext&);
void fn_sub_58C100_0058c100(p3fes::EEContext&);
void fn_sub_58C118_0058c118(p3fes::EEContext&);
void fn_sub_599408_00599408(p3fes::EEContext&);
void fn_sub_5996B0_005996b0(p3fes::EEContext&);
void fn_sub_599730_00599730(p3fes::EEContext&);
void fn_sub_5997F8_005997f8(p3fes::EEContext&);
void fn_sub_599A30_00599a30(p3fes::EEContext&);
void fn_sub_599A78_00599a78(p3fes::EEContext&);
void fn_sub_599B80_00599b80(p3fes::EEContext&);
void fn_sub_599C08_00599c08(p3fes::EEContext&);
void fn_sub_599C58_00599c58(p3fes::EEContext&);
void fn_sub_599CC8_00599cc8(p3fes::EEContext&);
void fn_sub_599D00_00599d00(p3fes::EEContext&);
void fn_sub_599D28_00599d28(p3fes::EEContext&);
void fn_sub_599D70_00599d70(p3fes::EEContext&);
void fn_sub_599E08_00599e08(p3fes::EEContext&);
void fn_sub_599E48_00599e48(p3fes::EEContext&);
void fn_sub_59A150_0059a150(p3fes::EEContext&);
void fn_sub_59A168_0059a168(p3fes::EEContext&);
void fn_sub_59A200_0059a200(p3fes::EEContext&);
void fn_sub_59A458_0059a458(p3fes::EEContext&);
void fn_sub_59A560_0059a560(p3fes::EEContext&);
void fn_sub_59A7E0_0059a7e0(p3fes::EEContext&);
void fn_sub_59A860_0059a860(p3fes::EEContext&);
void fn_sub_59A870_0059a870(p3fes::EEContext&);
void fn_sub_59B490_0059b490(p3fes::EEContext&);
void fn_sub_59B4B0_0059b4b0(p3fes::EEContext&);
void fn_sub_59BB88_0059bb88(p3fes::EEContext&);
void fn_sub_59BC20_0059bc20(p3fes::EEContext&);
void fn_sub_59BC88_0059bc88(p3fes::EEContext&);
void fn_sub_59BCB8_0059bcb8(p3fes::EEContext&);
void fn_sub_59BDD0_0059bdd0(p3fes::EEContext&);
void fn_sub_59BE10_0059be10(p3fes::EEContext&);
void fn_sub_59BE18_0059be18(p3fes::EEContext&);
void fn_sub_59BE30_0059be30(p3fes::EEContext&);
void fn_sub_59BE48_0059be48(p3fes::EEContext&);
void fn_sub_59BE60_0059be60(p3fes::EEContext&);
void fn_sub_59BE78_0059be78(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace libs5;

// 0x00599408 sub_599408 -- 16 bytes; leaf frame (no stack)
// [sfdGetPara] SFD: parameter id of a handle (+2572 + 4 x id).
void sub_599408(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00599408
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = sll(a1, 2);
    a1 = addu(a1, a0);
    lw(v0, a1, 2572);
}

// 0x005996B0 sub_5996B0 -- 124 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [sfdGetTrnWork] SFD: a transfer slot's work head: handle check (0xFF000117 for a bad handle), else sub_599730.
void sub_5996B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005996b0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a1;
    jal(ctx, 0x5996CCu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = s0;
    a2 = s1;
    a1 = a1 | 0x117;
    if (v0 != 0) {
        // 0x005996e8
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        a0 = 0;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00599708
    charge(ctx, 9);
    a1 = s2;
    jal(ctx, 0x599708u, gen::fn_sub_599730_00599730);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00599730 sub_599730 -- 48 bytes; leaf frame (no stack)
// [sfdGetTrnWorkHead] SFD: slot id's work (+7992 + 68 x id) -- its first word -- to *a2 (0 without a work).
void sub_599730(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00599730
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = sll(a1, 4);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    lw(v0, v0, 7992);
    if (v0 == 0) {
        // 0x0059974c
        charge(ctx, 2);
        sw(zero, a2, 0);
        return;
    }
    lw(v0, v0, 0);
    // 0x00599758
    charge(ctx, 2);
    sw(v0, a2, 0);
}

// 0x005997F8 sub_5997F8 -- 16 bytes; leaf frame (no stack)
// [sfdInitRec3] SFD: clears a 12-byte record and sets its third word.
void sub_5997F8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5};
    // 0x005997f8
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(a1, a0, 8);
    sw(zero, a0, 4);
}

// 0x00599A30 sub_599A30 -- 68 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfdInitPicRec] SFD: initialises a 44-byte record: +0 = 0, +4..+35 cleared, +36 = a1, +40 = 1. Returns 1.
void sub_599A30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599a30
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    a0 = addiu(s0, 4);
    link(ctx, 0x599A4Cu);  // $ra first: the delay slot below depends on it
    sw(zero, s0, 0);
    call(ctx, gen::fn_sub_599A78_00599a78);
    sw(s1, s0, 36);
    v0 = 1;
    ld(ra, sp, 0x10);
    sw(v0, s0, 40);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00599A78 sub_599A78 -- 40 bytes; leaf frame (no stack)
// [sfdClearRec32] SFD: clears a 32-byte record (seven words and two halfwords).
void sub_599A78(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x00599a78
    enter(ctx, 10);  // entry check point + this block's cycles
    sh(zero, a0, 30);
    sw(zero, a0, 0);
    sw(zero, a0, 4);
    sw(zero, a0, 8);
    sw(zero, a0, 12);
    sw(zero, a0, 16);
    sw(zero, a0, 20);
    sw(zero, a0, 24);
    sh(zero, a0, 28);
}

// 0x00599B80 sub_599B80 -- 132 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// [sfdExecVsync] SFD: vsync for every handle: counts 0x7B4720; each of the 8 handle slots (0x7B4774) that passes the
// check gets sub_599C08.
void sub_599B80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599b80
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 0x7B0000;
    sd(s1, sp, 0x8);
    v1 = addiu(v1, 18208);  // &0x7B4720
    sd(s2, sp, 0x10);
    s2 = 7;
    sd(s3, sp, 0x18);
    s3 = si(-1);
    sd(s0, sp, 0x0);
    s1 = addiu(v1, 84);  // &0x7B4774
    sd(ra, sp, 0x20);
    lw(v0, v1, 0);  // 0x7B4720
    v0 = addiu(v0, 1);
    sw(v0, v1, 0);  // 0x7B4720
    lw(s0, s1, 0);  // 0x7B4774
    for (;;) {
        // 0x00599bc0
        charge(ctx, 5);
        s1 = addiu(s1, 4);
        a0 = s0;
        jal(ctx, 0x599BC4u, gen::fn_sub_58C060_0058c060);
        a0 = s0;
        if (v0 != s3) {
            // 0x00599bd4
            charge(ctx, 2);
            jal(ctx, 0x599BD4u, gen::fn_sub_599C08_00599c08);
        }
        // 0x00599bdc
        charge(ctx, 3);
        s2 = addiu(s2, -1);
        if (i64(s2) < 0) {
            break;
        }
        lw(s0, s1, 0);
        backedge(ctx);
    }
    // 0x00599be8
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00599C08 sub_599C08 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfdExecVsyncHn] SFD: one handle's vsync: the time advance, and with parameter 71 = 1 the time update.
void sub_599C08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599c08
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x599C14u, gen::fn_sub_599C58_00599c58);
    a0 = s0;
    a1 = 71;
    jal(ctx, 0x599C20u, gen::fn_sub_599408_00599408);
    v1 = 1;
    a0 = s0;
    if (v0 != v1) {
        // 0x00599c48
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00599c34
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59A7E0_0059a7e0(ctx);  // tail call
}

// 0x00599C58 sub_599C58 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfdAdvanceVsyncTime] SFD: the vsync time advance: +4056 += the step +4060 while playing; +4092 += the step when
// its timer runs.
void sub_599C58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599c58
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = addiu(s0, 3376);
    jal(ctx, 0x599C6Cu, gen::fn_sub_599CC8_00599cc8);
    a0 = s0;
    a1 = s1;
    if (v0 != 0) {
        // 0x00599c80
        charge(ctx, 4);
        lw(v0, s1, 680);
        lw(v1, s1, 684);
        v0 = addu(v0, v1);
        sw(v0, s1, 680);
    }
    // 0x00599c90
    charge(ctx, 4);
    jal(ctx, 0x599C90u, gen::fn_sub_599D00_00599d00);
    ld(s0, sp, 0x0);
    if (v0 != 0) {
        // 0x00599ca0
        charge(ctx, 5);
        lw(v0, s1, 716);
        lw(v1, s1, 684);
        v0 = addu(v0, v1);
        sw(v0, s1, 716);
        ld(s0, sp, 0x0);
    }
    // 0x00599cb4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00599CC8 sub_599CC8 -- 52 bytes; leaf frame (no stack)
// [sfdIsTimeRunning] SFD: true when the handle plays (status +72 = 4), is not paused (+80) and +2416 is clear.
void sub_599CC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00599cc8
    enter(ctx, 6);  // entry check point + this block's cycles
    a1 = a0;
    a0 = 4;
    lw(v1, a1, 72);
    v0 = 0;
    a2 = addiu(a1, 2384);
    if (v1 == a0) {
        // 0x00599ce0
        charge(ctx, 3);
        lw(v1, a1, 80);
        if (v1 == 0) {
            // 0x00599cec
            charge(ctx, 2);
            lw(v0, a2, 32);
            v0 = sltiu(v0, 1);
        }
    }
    // 0x00599cf4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00599D00 sub_599D00 -- 36 bytes; leaf frame (no stack)
// [sfdIsSubTimeRunning] SFD: true when the time record's +716 is set (not -1) and +76 is 4.
void sub_599D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00599d00
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a1, 716);
    a2 = si(-1);
    v0 = 0;
    if (v1 != a2) {
        // 0x00599d10
        charge(ctx, 3);
        lw(v0, a0, 76);
        v0 = v0 ^ 0x4;
        v0 = sltiu(v0, 1);
    }
    // 0x00599d1c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00599D28 sub_599D28 -- 72 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfdSelectRefTime] SFD: the reference time: +680 with parameter 71 = 1, else +732; stored at +720.
void sub_599D28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599d28
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(ra, sp, 0x8);
    a1 = 71;
    jal(ctx, 0x599D38u, gen::fn_sub_599408_00599408);
    v1 = 1;
    if (v0 != v1) {
        // 0x00599d58
        charge(ctx, 2);
        lw(v0, s0, 732);
        sw(v0, s0, 720);
    } else {
        // 0x00599d4c
        charge(ctx, 3);
        lw(v0, s0, 680);
        sw(v0, s0, 720);
    }
    // 0x00599d60 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00599E08 sub_599E08 -- 60 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfdCheckLag] SFD: raises 0xFF000222 (sub_58BE40) and returns 1 when sub_599E48 reports a lag.
void sub_599E08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599e08
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x599E14u, gen::fn_sub_599E48_00599e48);
    a1 = lui(0xFF00);
    a0 = s0;
    if (v0 != 0) {
        // 0x00599e28
        charge(ctx, 3);
        a1 = a1 | 0x222;
        jal(ctx, 0x599E28u, gen::fn_sub_58BE40_0058be40);
        v0 = 1;
    }
    // 0x00599e34 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00599E48 sub_599E48 -- 128 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// [sfdIsLagging] SFD: with parameters 6 and 51 set, true when parameter 51 < the quotient of sub_599D70's two figures
// (divides; the original traps on a zero divisor).
void sub_599E48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599e48
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a1 = 6;
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x20);
    s0 = a0;
    jal(ctx, 0x599E5Cu, gen::fn_sub_599408_00599408);
    a0 = s0;
    a1 = 51;
    if (v0 != 0) {
        // 0x00599e70
        charge(ctx, 8);
        jal(ctx, 0x599E70u, gen::fn_sub_599408_00599408);
        a0 = s0;
        s1 = v0;
        a1 = addiu(a0, 3376);
        a2 = sp;
        a3 = addiu(sp, 0x4);
        if (s1 != 0) {
            // 0x00599e90
            charge(ctx, 6);
            jal(ctx, 0x599E90u, gen::fn_sub_599D70_00599d70);
            lw(v1, sp, 0x4);
            lw(v0, sp, 0x0);
            if (v1 == 0) {
                brk(ctx, 0x599EA4u, 0x7u);
            }
            // 0x00599ea8
            charge(ctx, 3);
            div(v0, v1);
            mflo(v0);
            v0 = slt(s1, v0);
        }
    }
    // 0x00599eb4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0059A150 sub_59A150 -- 20 bytes; frame 0x10: ra sp+0x0
// [sfdGetTimeThunk] SFD: thunk to sub_59A168.
void sub_59A150(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a150
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59A168_0059a168(ctx);  // tail call
}

// 0x0059A168 sub_59A168 -- 28 bytes; leaf frame (no stack)
// [sfdGetTime] SFD: the current time and unit (time record +652 / +656) to *a1 / *a2; returns 0.
void sub_59A168(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0059a168
    enter(ctx, 7);  // entry check point + this block's cycles
    a0 = addiu(a0, 3376);
    v0 = 0;
    lw(v1, a0, 652);
    sw(v1, a1, 0);
    lw(a1, a0, 656);
    sw(a1, a2, 0);
}

// 0x0059A200 sub_59A200 -- 148 bytes; frame 0x40: s1 sp+0x18, s0 sp+0x10, s2 sp+0x20, s3 sp+0x28, ra sp+0x30
// [sfdReadTime] SFD: reads the time through the time source selected by parameter 15 (callback table +3376; default
// sub_59A298) under the SVM lock.
void sub_59A200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a200
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x18);
    s1 = a0;
    a0 = sp;
    sd(s0, sp, 0x10);
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(s3, sp, 0x28);
    sd(ra, sp, 0x30);
    s3 = a2;
    jal(ctx, 0x59A224u, gen::fn_sub_58C100_0058c100);
    a0 = s1;
    a1 = 15;
    jal(ctx, 0x59A230u, gen::fn_sub_599408_00599408);
    a0 = s1;
    v0 = sll(v0, 2);
    s0 = addiu(s1, 3376);
    s0 = addu(s0, v0);
    a1 = s2;
    lw(v0, s0, 0);
    a2 = s3;
    if (v0 == 0) {
        // 0x0059a258
        charge(ctx, 2);
        v0 = 0x5A0000;
        v0 = addiu(v0, -23912);  // &sub_59A298
    }
    // 0x0059a260
    charge(ctx, 13);
    jalr(ctx, 0x59A260u, v0.u());
    a0 = sp;
    s0 = v0;
    jal(ctx, 0x59A26Cu, gen::fn_sub_58C118_0058c118);
    v0 = s0;
    ld(s1, sp, 0x18);
    ld(s0, sp, 0x10);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0059A458 sub_59A458 -- 80 bytes; leaf frame (no stack)
// [sfdIsTimeValid] SFD: true when the status is 4, -4, 6 or -6; else time -1 / unit 1 and 0.
void sub_59A458(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059a458
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 72);
    v0 = 4;
    if (v1 == v0) {
        // 0x0059a4a0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 1;
        return;
    }
    // 0x0059a468
    charge(ctx, 3);
    v0 = si(-4);
    if (v1 == v0) {
        // 0x0059a4a0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 1;
        return;
    }
    // 0x0059a474
    charge(ctx, 3);
    v0 = 6;
    if (v1 == v0) {
        // 0x0059a4a0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 1;
        return;
    }
    // 0x0059a480
    charge(ctx, 3);
    v0 = si(-6);
    cc = v1 == v0;  // the condition, before the delay slot changes it
    v1 = si(-1);
    if (cc) {
        // 0x0059a4a0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 1;
        return;
    }
    // 0x0059a48c
    charge(ctx, 5);
    a0 = 1;
    sw(v1, a1, 0);
    v0 = 0;
    sw(a0, a2, 0);
}

// 0x0059A560 sub_59A560 -- 20 bytes; frame 0x10: ra sp+0x0
// [sfdThunk56F4B8] SFD: thunk to sub_56F4B8.
void sub_59A560(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a560
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_56F4B8_0056f4b8(ctx);  // tail call
}

// 0x0059A7E0 sub_59A7E0 -- 124 bytes; frame 0x30: s1 sp+0x18, s0 sp+0x10, ra sp+0x20
// [sfdUpdateTime] SFD: the time update: reads the time; when it changed, re-selects the reference and stores the new
// pair; sets +68. Returns 1.
void sub_59A7E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059a7e0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x18);
    s1 = a0;
    a1 = sp;
    a2 = addiu(sp, 0x4);
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x20);
    s0 = addiu(s1, 3376);
    jal(ctx, 0x59A7FCu, gen::fn_sub_59A200_0059a200);
    lw(v0, sp, 0x0);
    a0 = s1;
    lw(v1, s0, 652);
    a1 = s0;
    if (v1 == v0) {
        // 0x0059a818
        charge(ctx, 4);
        lw(v1, s0, 656);
        lw(v0, sp, 0x4);
        cc = v1 == v0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (!cc) {
            goto L_0059a828;
        }
        // 0x0059a844 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x10);
        sw(v0, s1, sfdh::kTimeUpd);
        ld(ra, sp, 0x20);
        ld(s1, sp, 0x18);
        sp = addiu(sp, 0x30);
        return;
    }
L_0059a828:
    charge(ctx, 7);
    jal(ctx, 0x59A828u, gen::fn_sub_599D28_00599d28);
    lw(v0, sp, 0x0);
    lw(v1, sp, 0x4);
    sw(v0, s0, 652);
    sw(v1, s0, 656);
    v0 = 1;
    // 0x0059a844 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x10);
    sw(v0, s1, sfdh::kTimeUpd);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x18);
    sp = addiu(sp, 0x30);
}

// 0x0059A860 sub_59A860 -- 16 bytes; leaf frame (no stack)
// [sfdSetTimeSrc] SFD: installs a time-source callback: +3376 [index] = callback.
void sub_59A860(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0059a860
    enter(ctx, 4);  // entry check point + this block's cycles
    a2 = sll(a2, 2);
    a0 = addu(a0, a2);
    sw(a1, a0, 3376);
}

// 0x0059A870 sub_59A870 -- 160 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfdDispatchCond] SFD: the condition dispatch: the table 0x7CA2E8 [2 x kind + sub-kind] with 0x7CA2C0 [kind]; an
// empty entry raises 0xFF000221 and gives 0 / 1.
void sub_59A870(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a870
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = a0;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    a1 = lui(0xFF00);
    a0 = 0;
    a1 = a1 | 0x221;
    lw(v0, t0, 0);
    a2 = s1;
    lw(a3, t0, 4);
    v1 = sll(v0, 1);
    v0 = sll(v0, 2);
    v1 = addu(v1, a3);
    v1 = sll(v1, 2);
    at = 0x7D0000;
    at = addu(at, v0);
    lw(v0, at, -23872);
    at = 0x7D0000;
    at = addu(at, v1);
    lw(v1, at, -23832);
    a3 = s0;
    if (v1 != 0) {
        // 0x0059a8f0
        charge(ctx, 3);
        a0 = v0;
        a1 = t0;
        jalr(ctx, 0x59A8F4u, v1.u());
    } else {
        // 0x0059a8d4
        charge(ctx, 6);
        jal(ctx, 0x59A8D4u, gen::fn_sub_58BE40_0058be40);
        v1 = 1;
        sw(zero, s1, 0);
        sw(v1, s0, 0);
    }
    // 0x0059a8fc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059B490 sub_59B490 -- 28 bytes; leaf frame (no stack)
// [sfdInitStat] SFD: initialises a statistics record: count 0, minimum INT64_MAX, sum and maximum 0.
void sub_59B490(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4};
    // 0x0059b490
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = si(-1);
    v0 = dsrl(v0, 1);
    sw(zero, a0, 24);
    sd(v0, a0, 8);
    sd(zero, a0, 0);
    sd(zero, a0, 16);
}

// 0x0059B4B0 sub_59B4B0 -- 60 bytes; leaf frame (no stack)
// [sfdAddStat] SFD: adds a 64-bit sample to a statistics record (sum, minimum, maximum, count).
void sub_59B4B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x0059b4b0
    enter(ctx, 15);  // entry check point + this block's cycles
    ld(a3, a0, 8);
    ld(t0, a0, 16);
    ld(a2, a0, 0);
    t1 = slt(a1, a3);
    lw(v1, a0, 24);
    v0 = slt(t0, a1);
    if (v0 != 0) t0 = a1;
    a2 = a2 + a1;
    if (t1 != 0) a3 = a1;
    v1 = addiu(v1, 1);
    sw(v1, a0, 24);
    sd(a2, a0, 0);
    sd(a3, a0, 8);
    sd(t0, a0, 16);
}

// 0x0059BB88 sub_59BB88 -- 152 bytes; frame 0x30: s2 sp+0x10, ra sp+0x20, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18
// [sfdCallAllTrn] SFD: calls method index of every transfer slot (9 x 68 bytes from +7984) that has a method table,
// until one returns non-zero.
void sub_59BB88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059bb88
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(ra, sp, 0x20);
    a0 = 0;
    sd(s0, sp, 0x0);
    s0 = addiu(s2, 7984);
    sd(s1, sp, 0x8);
    s1 = 0;
    sd(s3, sp, 0x18);
    s3 = sll(a1, 2);
    for (;;) {
    L_0059bbb8:
        charge(ctx, 1);
        v0 = slti(s1, 9);
        for (;;) {
            // 0x0059bbbc
            charge(ctx, 2);
            s1 = addiu(s1, 1);
            if (v0 != 0) {
                // 0x0059bbc4
                charge(ctx, 6);
                lw(v0, s0, 12);
                s0 = addiu(s0, 68);
                v1 = addu(s3, v0);
                if (v0 == 0) {
                    backedge(ctx);
                    goto L_0059bbb8;
                }
                // 0x0059bbdc
                charge(ctx, 9);
                lw(v0, v1, 0);
                a0 = s2;
                a1 = 0;
                a2 = 0;
                a3 = 0;
                jalr(ctx, 0x59BBECu, v0.u());
                a0 = v0;
                v0 = slti(s1, 9);
                if (a0 == 0) {
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
        break;
    }
    // 0x0059bc00 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    v0 = a0;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0059BC20 sub_59BC20 -- 80 bytes; frame 0x10: ra sp+0x0
// [sfdCallTrn] SFD: calls method index of transfer slot id (table +7996 + 68 x id) with the caller's arguments; 0
// without a table.
void sub_59BC20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059bc20
    enter(ctx, 14);  // entry check point + this block's cycles
    v0 = sll(a1, 4);
    sp = addiu(sp, -0x10);
    v0 = addu(v0, a1);
    a1 = a3;
    v0 = sll(v0, 2);
    sd(ra, sp, 0x0);
    v1 = addu(a0, v0);
    v0 = 0;
    lw(t1, v1, 7996);
    a2 = sll(a2, 2);
    a3 = 0;
    v1 = addu(a2, t1);
    a2 = t0;
    if (t1 != 0) {
        // 0x0059bc58
        charge(ctx, 3);
        lw(v0, v1, 0);
        jalr(ctx, 0x59BC5Cu, v0.u());
    }
    // 0x0059bc64 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0059BC88 sub_59BC88 -- 24 bytes; leaf frame (no stack)
// [sfdIsTrnInputEnd] SFD: transfer slot id's input-ended flag (+7984 + 68 x id).
void sub_59BC88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0059bc88
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = sll(a1, 4);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    lw(v0, a0, 7984);
}

// 0x0059BCB8 sub_59BCB8 -- 24 bytes; leaf frame (no stack)
// [sfdIsTrnOutputEnd] SFD: transfer slot id's output-ended flag (+7988 + 68 x id).
void sub_59BCB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0059bcb8
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = sll(a1, 4);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    lw(v0, a0, 7988);
}

// 0x0059BDD0 sub_59BDD0 -- 64 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfdTbReset] SFD: the time base's reset: clears its 240-byte history (+24) and +20, counts resets (+412).
void sub_59BDD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059bdd0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(s0, sp, 0x0);
    s0 = a0;
    a0 = addiu(s0, 24);
    sd(ra, sp, 0x8);
    a2 = 240;
    jal(ctx, 0x59BDE8u, gen::fn_memset_00521408);
    lw(v0, s0, 412);
    sw(zero, s0, 20);
    v0 = addiu(v0, 1);
    ld(ra, sp, 0x8);
    sw(v0, s0, 412);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0059BE10 sub_59BE10 -- 8 bytes; leaf frame (no stack)
// [sfdTbSetMode] SFD: sets the time base's mode (+0).
void sub_59BE10(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x0059be10
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, 0);
}

// 0x0059BE18 sub_59BE18 -- 20 bytes; leaf frame (no stack)
// [sfdTbSetRatio1] SFD: sets the time base's first ratio pair (+312 / +320).
void sub_59BE18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0059be18
    enter(ctx, 5);  // entry check point + this block's cycles
    ld(v0, a1, 0);
    sd(v0, a0, 312);
    ld(v1, a1, 8);
    sd(v1, a0, 320);
}

// 0x0059BE30 sub_59BE30 -- 20 bytes; leaf frame (no stack)
// [sfdTbSetRatio2] SFD: sets the second ratio pair (+328 / +336).
void sub_59BE30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0059be30
    enter(ctx, 5);  // entry check point + this block's cycles
    ld(v0, a1, 0);
    sd(v0, a0, 328);
    ld(v1, a1, 8);
    sd(v1, a0, 336);
}

// 0x0059BE48 sub_59BE48 -- 20 bytes; leaf frame (no stack)
// [sfdTbSetRatio3] SFD: sets the third ratio pair (+344 / +352).
void sub_59BE48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0059be48
    enter(ctx, 5);  // entry check point + this block's cycles
    ld(v0, a1, 0);
    sd(v0, a0, 344);
    ld(v1, a1, 8);
    sd(v1, a0, 352);
}

// 0x0059BE60 sub_59BE60 -- 20 bytes; leaf frame (no stack)
// [sfdTbSetRatio4] SFD: sets the fourth ratio pair (+360 / +368).
void sub_59BE60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0059be60
    enter(ctx, 5);  // entry check point + this block's cycles
    ld(v0, a1, 0);
    sd(v0, a0, 360);
    ld(v1, a1, 8);
    sd(v1, a0, 368);
}

// 0x0059BE78 sub_59BE78 -- 16 bytes; leaf frame (no stack)
// [sfdTbSetLimit] SFD: sets the time base's limit (+16) when positive.
void sub_59BE78(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x0059be78
    enter(ctx, 2);  // entry check point + this block's cycles
    if (i64(a1) > 0) {
        sw(a1, a0, 16);
    }
    // 0x0059be80
    charge(ctx, 2);
}

}  // namespace p3fes::game
