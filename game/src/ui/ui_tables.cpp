// Table-driven UI leaves, hand-decompiled from SLUS_216.21 (docs/ANALYSIS/20_menu_ui.md sections 3.4,
// 4.4, 5.1): the global flag bit array read by the whole UI, the sprite-font file table of the camp
// fonts, and the social-stat level strings / thresholds of the status screen. Phase 5: these replace the
// recompiled bodies listed in game/replaced.txt; tests/game/test_menu_ui.cpp runs each against its
// __recomp body. Virtual time per ADR-0013 (block costs from recomp/generated).
//
// Faithfulness audit (2026-10-21, tools/ours/audit): all 8 functions here are now p3fes_handgen's register-faithful
// bodies (the hand versions differed from the original: scratch GPRs 5, $v0 3). Each keeps the notes of its earlier
// hand version above it; what this header says about how the bodies were written describes those earlier versions.
#include "p3fes/game/ui.h"

#include "p3fes/game/guest.h"
#include "p3fes/game/hg_cpu.h"

namespace p3fes::game {

namespace {

using namespace ui;

}  // namespace

// 0x0016F190 datGetFlag -- 88 bytes; leaf frame (no stack)
// 0x16F190 datGetFlag(id): bit (id % 32) of word (id / 32) of the 176-word flag array, with C's
// truncating division and remainder (the compiler's fix-ups for negative ids are kept; a negative
// remainder shifts by the same low five bits).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datGetFlag(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::i64, hg::lw, hg::sll, hg::sllv, hg::sltu, hg::sra;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016f190
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = sra(a0, 5);
    if (i64(a0) < 0) {
        // 0x0016f19c
        charge(ctx, 2);
        v0 = addiu(a0, 31);
        v0 = sra(v0, 5);
    }
    // 0x0016f1a4
    charge(ctx, 7);
    v1 = sll(v0, 2);
    v0 = 0x840000;
    v0 = addiu(v0, -24036);  // &g_datFlagWords
    a1 = addu(v0, v1);
    v1 = a0 & 0x1F;
    if (i64(a0) < 0) {
        // 0x0016f1c0
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x0016f1c8
            charge(ctx, 1);
            v1 = addiu(v1, -32);
        }
    }
    // 0x0016f1cc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 1;
    v1 = sllv(v0, v1);
    lw(v0, a1, 0);
    v0 = v0 & v1;
    v0 = sltu(0, v0);
}

// 0x001120A0 sprFontGetFile -- 28 bytes; leaf frame (no stack)
// 0x1120A0 sprFontGetFile(index): one of the three camp font sprite files registered by sprFontInit.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sprFontGetFile(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x001120a0
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = sll(a0, 2);
    v0 = 0x830000;
    v0 = addiu(v0, 14912);  // &sSprFontFiles
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
}

// 0x0011A810 H_Camp_GetAcademicLevelString -- 36 bytes; leaf frame (no stack)
// 0x11A810 / 0x11A840 / 0x11A870 H_Camp_Get{Academic,Charm,Courage}LevelString(level 1..6).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void H_Camp_GetAcademicLevelString(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::dsll32, hg::dsra32, hg::enter, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0011a810
    enter(ctx, 9);  // entry check point + this block's cycles
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v1 = sll(v0, 2);
    v0 = 0x5D0000;
    v0 = addiu(v0, 32436);  // "H~]"
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
}

// 0x0011A840 H_Camp_GetCharmLevelString -- 36 bytes; leaf frame (no stack)
// 0x11A810 / 0x11A840 / 0x11A870 H_Camp_Get{Academic,Charm,Courage}LevelString(level 1..6).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void H_Camp_GetCharmLevelString(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::dsll32, hg::dsra32, hg::enter, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0011a840
    enter(ctx, 9);  // entry check point + this block's cycles
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v1 = sll(v0, 2);
    v0 = 0x5D0000;
    v0 = addiu(v0, 32408);  // &tbl_H_Camp_CharmLevelStrings
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
}

// 0x0011A870 H_Camp_GetCourageLevelString -- 36 bytes; leaf frame (no stack)
// 0x11A810 / 0x11A840 / 0x11A870 H_Camp_Get{Academic,Charm,Courage}LevelString(level 1..6).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void H_Camp_GetCourageLevelString(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::dsll32, hg::dsra32, hg::enter, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0011a870
    enter(ctx, 9);  // entry check point + this block's cycles
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v1 = sll(v0, 2);
    v0 = 0x5D0000;
    v0 = addiu(v0, 32380);  // &0x5D7E7C
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
}

// 0x00177280 datGetAcademicLevel -- 100 bytes; leaf frame (no stack)
// 0x177280 / 0x1772F0 / 0x177360 datGet{Academic,Charm,Courage}Level(points) -> 1..6.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datGetAcademicLevel(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lh, hg::sll,
          hg::slt;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00177280
    enter(ctx, 5);  // entry check point + this block's cycles
    a2 = 5;
    a1 = dsll32(a0, 16);
    a1 = dsra32(a1, 16);
    v1 = 0x5E0000;
    v1 = addiu(v1, 12392);  // &academicLevelThreshold
    for (;;) {
        // 0x00177294
        charge(ctx, 8);
        a0 = dsll32(a2, 16);
        a0 = dsra32(a0, 16);
        v0 = sll(a0, 1);
        v0 = addu(v1, v0);
        lh(v0, v0, 0);
        at = slt(a1, v0);
        if (at == 0) {
            break;
        }
        // 0x001772c8
        charge(ctx, 5);
        v0 = addiu(a2, -1);
        a2 = dsll32(v0, 16);
        a2 = dsra32(a2, 16);
        backedge(ctx);
    }
    // 0x001772b4
    charge(ctx, 5);
    v0 = addiu(a0, 1);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    // 0x001772dc
    charge(ctx, 2);
}

// 0x001772F0 datGetCharmLevel -- 100 bytes; leaf frame (no stack)
// 0x177280 / 0x1772F0 / 0x177360 datGet{Academic,Charm,Courage}Level(points) -> 1..6.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datGetCharmLevel(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lh, hg::sll,
          hg::slt;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x001772f0
    enter(ctx, 5);  // entry check point + this block's cycles
    a2 = 5;
    a1 = dsll32(a0, 16);
    a1 = dsra32(a1, 16);
    v1 = 0x5E0000;
    v1 = addiu(v1, 12408);  // &charmLevelThreshold
    for (;;) {
        // 0x00177304
        charge(ctx, 8);
        a0 = dsll32(a2, 16);
        a0 = dsra32(a0, 16);
        v0 = sll(a0, 1);
        v0 = addu(v1, v0);
        lh(v0, v0, 0);
        at = slt(a1, v0);
        if (at == 0) {
            break;
        }
        // 0x00177338
        charge(ctx, 5);
        v0 = addiu(a2, -1);
        a2 = dsll32(v0, 16);
        a2 = dsra32(a2, 16);
        backedge(ctx);
    }
    // 0x00177324
    charge(ctx, 5);
    v0 = addiu(a0, 1);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    // 0x0017734c
    charge(ctx, 2);
}

// 0x00177360 datGetCourageLevel -- 100 bytes; leaf frame (no stack)
// 0x177280 / 0x1772F0 / 0x177360 datGet{Academic,Charm,Courage}Level(points) -> 1..6.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datGetCourageLevel(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lh, hg::sll,
          hg::slt;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00177360
    enter(ctx, 5);  // entry check point + this block's cycles
    a2 = 5;
    a1 = dsll32(a0, 16);
    a1 = dsra32(a1, 16);
    v1 = 0x5E0000;
    v1 = addiu(v1, 12424);  // &courageLevelThreshold
    for (;;) {
        // 0x00177374
        charge(ctx, 8);
        a0 = dsll32(a2, 16);
        a0 = dsra32(a0, 16);
        v0 = sll(a0, 1);
        v0 = addu(v1, v0);
        lh(v0, v0, 0);
        at = slt(a1, v0);
        if (at == 0) {
            break;
        }
        // 0x001773a8
        charge(ctx, 5);
        v0 = addiu(a2, -1);
        a2 = dsll32(v0, 16);
        a2 = dsra32(a2, 16);
        backedge(ctx);
    }
    // 0x00177394
    charge(ctx, 5);
    v0 = addiu(a0, 1);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    // 0x001773bc
    charge(ctx, 2);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points -------------------------------------------------------------
namespace p3fes::recomp_gen {
using namespace p3fes::game;
}  // namespace p3fes::recomp_gen
