// The battle code, sixth pass (slice battle6; docs/ANALYSIS/21_battle.md, game/include/p3fes/game/battle6.h for the
// layouts): the staff roll -- its script and scroll (ed_scroll.c), resources (ed_res.c) and task (ed_sr.c). The
// bodies are p3fes_handgen's (frame, spills, $ra links, every register, cycle charges, check points); this file names
// their offsets (battle3.h's b3::, battle4.h's b4::, battle5.h's b5:: records reused, this slice's in b6::) and gives
// each function its role -- proposed names in brackets (ADR-0009), symbols in code are functions.json's.
// Still-recompiled callees are reached through their gen:: entry points (the relaxed callee rule).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/battle6.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_ArchiveGetFile_00102100(p3fes::EEContext&);
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_frFontBuildGlyphList_003b0970(p3fes::EEContext&);
void fn_frFontClearDefaultGlyphFlags_003b0e90(p3fes::EEContext&);
void fn_frFontDraw_003b1360(p3fes::EEContext&);
void fn_frFontLineGetWidth_003b19d0(p3fes::EEContext&);
void fn_frFontLineSetPos_003b0d70(p3fes::EEContext&);
void fn_frFontLineSetRgba_003b0e20(p3fes::EEContext&);
void fn_frFontSetDefaultGlyphFlags_003b0e70(p3fes::EEContext&);
void fn_frLoadFontData_Ptr_003af770(p3fes::EEContext&);
void fn_kwlnTaskAddChild_00195550(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);
void fn_kwlnTaskInitEx_00194e10(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncpy_00524828(p3fes::EEContext&);
void fn_sub_108570_00108570(p3fes::EEContext&);
void fn_sub_1085C0_001085c0(p3fes::EEContext&);
void fn_sub_108710_00108710(p3fes::EEContext&);
void fn_sub_10BCE0_0010bce0(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_1985B0_001985b0(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_279940_00279940(p3fes::EEContext&);
void fn_sub_279AC0_00279ac0(p3fes::EEContext&);
void fn_sub_279AF0_00279af0(p3fes::EEContext&);
void fn_sub_279B10_00279b10(p3fes::EEContext&);
void fn_sub_279B20_00279b20(p3fes::EEContext&);
void fn_sub_279B30_00279b30(p3fes::EEContext&);
void fn_sub_279BF0_00279bf0(p3fes::EEContext&);
void fn_sub_279C90_00279c90(p3fes::EEContext&);
void fn_sub_279D10_00279d10(p3fes::EEContext&);
void fn_sub_279D60_00279d60(p3fes::EEContext&);
void fn_sub_27A3B0_0027a3b0(p3fes::EEContext&);
void fn_sub_27A4A0_0027a4a0(p3fes::EEContext&);
void fn_sub_27A560_0027a560(p3fes::EEContext&);
void fn_sub_27A5D0_0027a5d0(p3fes::EEContext&);
void fn_sub_27A6A0_0027a6a0(p3fes::EEContext&);
void fn_sub_27A930_0027a930(p3fes::EEContext&);
void fn_sub_27AA00_0027aa00(p3fes::EEContext&);
void fn_sub_27AAA0_0027aaa0(p3fes::EEContext&);
void fn_sub_27AB10_0027ab10(p3fes::EEContext&);
void fn_sub_27AB80_0027ab80(p3fes::EEContext&);
void fn_sub_27AC60_0027ac60(p3fes::EEContext&);
void fn_sub_27AC80_0027ac80(p3fes::EEContext&);
void fn_sub_27ACE0_0027ace0(p3fes::EEContext&);
void fn_sub_27AE90_0027ae90(p3fes::EEContext&);
void fn_sub_27AF80_0027af80(p3fes::EEContext&);
void fn_sub_27AFD0_0027afd0(p3fes::EEContext&);
void fn_sub_27B070_0027b070(p3fes::EEContext&);
void fn_sub_27B0B0_0027b0b0(p3fes::EEContext&);
void fn_sub_27B200_0027b200(p3fes::EEContext&);
void fn_sub_27B2B0_0027b2b0(p3fes::EEContext&);
void fn_sub_27B3F0_0027b3f0(p3fes::EEContext&);
void fn_sub_27B460_0027b460(p3fes::EEContext&);
void fn_sub_3AFC30_003afc30(p3fes::EEContext&);
void fn_sub_3B0170_003b0170(p3fes::EEContext&);
void fn_sub_3B2C60_003b2c60(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b3;  // the record offsets and $gp slots of battle3.h
using namespace b4;  // battle4.h's additions
using namespace b5;  // battle5.h's additions
using namespace b6;  // this slice's additions (battle6.h)

// 0x00279940 sub_279940 -- 372 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [edScriptBuild] Builds the staff roll script object from the loaded ed_sr.bin file 0 (a0 = the file): allocates
// (RwMalloc slot, hint 0x40000) a 20-byte head + the string table (4 bytes per string, +12 of them) + the string data
// (file +20 / +24: offset / size) + the command stream (file +4 / +8), each part 4-byte aligned; head +0 the file's
// word 0, +4 the string count, +8 the table, +12 the strings, +16 the commands; then the table: each string's start,
// the strings' lengths being the bytes at file +16. Returns the object.
// Arguments: a0 the file image.
void sub_279940(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00279940
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    v1 = 20;
    lw(v0, a0, edfile::kStringCount);
    v0 = sll(v0, 2);
    a0 = addu(v1, v0);
    v1 = a0 & 0x3;
    if (v1 != 0) {
        // 0x00279970
        charge(ctx, 3);
        v0 = 4;
        v0 = subu(v0, v1);
        a0 = addu(a0, v0);
    }
    // 0x0027997c
    charge(ctx, 5);
    lw(v0, s1, edfile::kStringSize);
    a0 = addu(a0, v0);
    v1 = a0 & 0x3;
    if (v1 != 0) {
        // 0x00279990
        charge(ctx, 3);
        v0 = 4;
        v0 = subu(v0, v1);
        a0 = addu(a0, v0);
    }
    // 0x0027999c
    charge(ctx, 16);
    lw(v0, s1, edfile::kCmdSize);
    a0 = addu(a0, v0);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x2799B0u, v0.u());
    s0 = v0;
    v1 = addiu(v0, 20);
    sw(v1, v0, 8);
    lw(v0, s1, edfile::kStringCount);
    v0 = sll(v0, 2);
    v0 = addu(v1, v0);
    a0 = v0 & 0x3;
    if (a0 != 0) {
        // 0x002799dc
        charge(ctx, 3);
        v1 = 4;
        v1 = subu(v1, a0);
        v0 = addu(v0, v1);
    }
    // 0x002799e8
    charge(ctx, 6);
    sw(v0, s0, 12);
    lw(v1, s1, edfile::kStringSize);
    v0 = addu(v0, v1);
    a0 = v0 & 0x3;
    if (a0 != 0) {
        // 0x00279a00
        charge(ctx, 3);
        v1 = 4;
        v1 = subu(v1, a0);
        v0 = addu(v0, v1);
    }
    // 0x00279a0c
    charge(ctx, 23);
    sw(v0, s0, 16);
    lw(v0, s1, edfile::kStringCount);
    sw(v0, s0, 4);
    lw(v0, s1, edfile::kWord0);
    sw(v0, s0, 0);
    lw(v0, s1, edfile::kStringOffset);
    a1 = addu(s1, v0);
    lw(a0, s0, 12);
    lw(a2, s1, edfile::kStringSize);
    jal(ctx, 0x279A30u, gen::fn_memcpy_00521250);
    lw(v0, s1, edfile::kCmdOffset);
    a1 = addu(s1, v0);
    lw(a0, s0, 16);
    lw(a2, s1, edfile::kCmdSize);
    jal(ctx, 0x279A48u, gen::fn_memcpy_00521250);
    lw(v0, s1, edfile::kLengthOffset);
    a0 = addu(s1, v0);
    lw(a2, s0, 12);
    a1 = 0;
    for (;;) {
        // 0x00279a88
        charge(ctx, 4);
        lw(v0, s1, edfile::kStringCount);
        v0 = sltu(a1, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00279a68
        charge(ctx, 8);
        v1 = sll(a1, 2);
        lw(v0, s0, 8);
        v0 = addu(v0, v1);
        sw(a2, v0, 0);
        lbu(v0, a0, 0);
        a2 = addu(a2, v0);
        a1 = addiu(a1, 1);
        a0 = addiu(a0, 1);
    }
    // 0x00279a98
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00279AC0 sub_279AC0 -- 40 bytes; frame 0x10: ra sp+0x0
// [edScriptFree] Frees the staff roll script object (a0) through the RwFree slot 0x96017C.
// Arguments: a0 the object.
void sub_279AC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00279ac0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x279AD0u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00279AF0 sub_279AF0 -- 24 bytes; leaf frame (no stack)
// [edScriptGetString] The staff roll script's string a1 (head +8 table[a1]).
// Arguments: a0 the object, a1 index.
void sub_279AF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00279af0
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = sll(a1, 2);
    lw(v0, a0, edscript::kStrings);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
}

// 0x00279B10 sub_279B10 -- 12 bytes; leaf frame (no stack)
// [edScriptGetCommands] The staff roll script's command stream (head +16).
// Arguments: a0 the object.
void sub_279B10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00279b10
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, edscript::kCommands);
}

// 0x00279B20 sub_279B20 -- 12 bytes; leaf frame (no stack)
// [edScriptGetStringCount] The staff roll script's string count (head +4).
// Arguments: a0 the object.
void sub_279B20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00279b20
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, edscript::kStringCount);
}

// 0x00279B30 sub_279B30 -- 188 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [edScrollInit] Initialises the staff roll scroll work (a0, 4,656 bytes inside the ed_sr work) and registers it at
// $gp 0x7CE3D4: flags 0, the line colour 0xFFFFFFFF, the 32 line slots free; the clear colour white (sub_1985B0 255,
// 255, 255, 255) with flag 2958 set, else dark blue (15, 31, 40, 255).
// Arguments: a0 the work.
void sub_279B30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00279b30
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    sw(zero, a0, edscroll::kFlags);
    v0 = 255;
    sb(v0, a0, edscroll::kRgba);
    sb(v0, a0, edscroll::kRgba + 1);
    sb(v0, a0, edscroll::kRgba + 2);
    sb(v0, a0, edscroll::kRgba + 3);
    a0 = 2958;
    jal(ctx, 0x279B5Cu, gen::fn_datGetFlag_0016f190);
    if (v0 == 0) {
        // 0x00279b8c
        charge(ctx, 6);
        a0 = 15;
        a1 = 31;
        a2 = 40;
        a3 = 255;
        jal(ctx, 0x279B9Cu, gen::fn_sub_1985B0_001985b0);
    } else {
        // 0x00279b6c
        charge(ctx, 8);
        a0 = 255;
        a1 = a0;
        a2 = a0;
        a3 = a0;
        jal(ctx, 0x279B7Cu, gen::fn_sub_1985B0_001985b0);
    }
    // 0x00279ba4
    charge(ctx, 3);
    a0 = 0;
    for (;;) {
        // 0x00279bc8
        charge(ctx, 3);
        v1 = slti(a0, 32);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00279bb0
        charge(ctx, 6);
        v1 = sll(a0, 3);
        v1 = addu(v1, a0);
        v1 = sll(v1, 4);
        v1 = addu(s0, v1);
        sw(zero, v1, 4);
        a0 = addiu(a0, 1);
    }
    // 0x00279bd4
    charge(ctx, 6);
    sw(s0, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00279BF0 sub_279BF0 -- 156 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [edScrollTerm] Closes the staff roll scroll work (K_Assert line 88 when none): frees every used line slot's glyph
// lists (sub_27A560) and clears the $gp slot.
void sub_279BF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00279bf0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    if (v1 == 0) {
        // 0x00279c0c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4288);  // "ed_scroll.c"
        a1 = 88;
        jal(ctx, 0x279C18u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00279c20
    charge(ctx, 4);
    lw(s0, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    s1 = 0;
    for (;;) {
        // 0x00279c64
        charge(ctx, 3);
        v1 = slti(s1, 32);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00279c30
        charge(ctx, 10);
        v1 = sll(s1, 3);
        v1 = addu(v1, s1);
        v1 = sll(v1, 4);
        v1 = addu(s0, v1);
        a0 = addiu(v1, 4);
        lw(v1, v1, 4);
        v1 = nor(v1, 0);
        v1 = v1 & 0x1;
        if (v1 == 0) {
            // 0x00279c58
            charge(ctx, 2);
            jal(ctx, 0x279C58u, gen::fn_sub_27A560_0027a560);
        }
        // 0x00279c60
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00279c70
    charge(ctx, 7);
    sw(zero, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00279C90 sub_279C90 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [edScrollStart] Starts the staff roll scroll: the frame counter, string index and command cursor to 0, the start y
// (+4632) and the next line's y (+4636) to 448.0 (the screen bottom), places the lines (sub_27A5D0), sets flag 1
// (running) and the end phase 0.
void sub_279C90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00279c90
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    if (v0 == 0) {
        // 0x00279ca8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4288);  // "ed_scroll.c"
        a1 = 88;
        jal(ctx, 0x279CB4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00279cbc
    charge(ctx, 20);
    lw(s0, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    sw(zero, s0, edscroll::kWord4624);
    sw(zero, s0, edscroll::kWord4628);
    v0 = 0x43E00000;
    sw(v0, s0, edscroll::kStartY);
    sw(v0, s0, edscroll::kNextY);
    sw(zero, s0, edscroll::kEndFrame);
    sw(zero, s0, edscroll::kStringIndex);
    sw(zero, s0, edscroll::kCursor);
    jal(ctx, 0x279CE0u, gen::fn_sub_27A5D0_0027a5d0);
    lw(v1, s0, edscroll::kFlags);
    v1 = v1 | 0x1;
    sw(v1, s0, edscroll::kFlags);
    sw(zero, s0, edscroll::kEndPhase);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00279D10 sub_279D10 -- 68 bytes; frame 0x10: ra sp+0x0
// [edScrollIsRunning] Nonzero while the staff roll scroll runs (flag 1).
void sub_279D10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00279d10
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    if (v0 == 0) {
        // 0x00279d24
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4288);  // "ed_scroll.c"
        a1 = 88;
        jal(ctx, 0x279D30u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00279d38 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    lw(v0, v0, edscroll::kFlags);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00279D60 sub_279D60 -- 1608 bytes; frame 0x70: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [edScrollUpdate] Per-frame update of the staff roll scroll (K_Assert line 88). While running: when the last line
// was placed (flag 4) it notes that line's y (+4648), clears the frame counter, enters end phase 1 and sets the clear
// colour black. The scroll speed is the constant 0x7CAFAC (0x7CAFB4-based for the alternate episode, sub_17D800); the
// hold time at the end 60 frames (alternate) or 30 (*0x7CC4E0). End phase 1: the last line eases to y = 208 over n =
// speed / (k / (2 * (y0 - 208))) frames (a decelerating step each frame), holds for the hold time, then fades the
// line colour's alpha (+4655) from 255 to 0 over 45 frames and stops (flag 1 cleared). Phase 0 scrolls by the speed.
// Then, until the script ended (flag 2), reads commands while the next line's y minus the step is above 448: 4 a half
// line (+12 px), 3 n blank lines (+24 * n px), 2 the next line is a caption, 1 a line: a free slot (sub_27A4A0) gets
// the next string's glyph lists (sub_27A6A0), the last string marks the slot as the last line (+4640, flag 4), y
// advances 24 px; 0 the script ends; each command printf's its kind ('regist string', 'caption', 'empty line', 'line
// 0') and steps the cursor (sub_27AB80). Finally every used slot moves up by the step (freed once 24 px above the
// top) and the lines are placed again.
void sub_279D60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00279d60
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v1, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    if (v1 == 0) {
        // 0x00279d90
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4288);  // "ed_scroll.c"
        a1 = 88;
        jal(ctx, 0x279D9Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00279da4
    charge(ctx, 6);
    lw(s1, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    lw(a0, s1, edscroll::kFlags);
    v1 = nor(a0, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x00279dbc
        charge(ctx, 3);
        v0 = a0 & 0x4;
        if (v0 != 0) {
            // 0x00279dc8
            charge(ctx, 16);
            lw(v0, s1, edscroll::kLastLine);
            lwc1(f0, v0, edline::kY);
            swc1(f0, s1, edscroll::kEndY0);
            sw(zero, s1, edscroll::kEndFrame);
            v0 = 1;
            sw(v0, s1, edscroll::kEndPhase);
            lw(v1, s1, edscroll::kFlags);
            v0 = si(-5);
            v0 = v1 & v0;
            sw(v0, s1, edscroll::kFlags);
            a0 = 0;
            a1 = 0;
            a2 = 0;
            a3 = 255;
            jal(ctx, 0x279E00u, gen::fn_sub_1985B0_001985b0);
        }
        // 0x00279e08
        charge(ctx, 4);
        jal(ctx, 0x279E08u, gen::fn_sub_17D800_0017d800);
        if (v0 != 0) {
            // 0x00279e28
            charge(ctx, 2);
            v0 = 60;
            sw(v0, gp, kGpEdHoldFrames);  // the hold of the staff roll at the end: 60 frames (alternate episode) or 30 (0x7CC4E0) 0x7CC4E0
        } else {
            // 0x00279e18
            charge(ctx, 4);
            v0 = 30;
            sw(v0, gp, kGpEdHoldFrames);  // the hold of the staff roll at the end: 60 frames (alternate episode) or 30 (0x7CC4E0) 0x7CC4E0
        }
        // 0x00279e30
        charge(ctx, 4);
        lw(v1, s1, edscroll::kEndPhase);
        v0 = 1;
        if (v1 == v0) {
            // 0x00279e78
            charge(ctx, 4);
            jal(ctx, 0x279E78u, gen::fn_sub_17D800_0017d800);
            if (v0 != 0) {
                // 0x00279ecc
                charge(ctx, 14);
                v0 = 0x43500000;
                mtc1(v0, f2);
                lwc1(f0, s1, edscroll::kEndY0);
                sub_s(f1, f0, f2);
                v0 = 0x40000000;
                mtc1(v0, f0);
                mul_s(f1, f0, f1);
                lwc1(f0, gp, -32060);  // 0x7CAFB4
                div_s(f21, f0, f1);
                lwc1(f0, gp, -32068);  // 0x7CAFAC
                div_s(f0, f0, f21);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
            } else {
                // 0x00279e88
                charge(ctx, 17);
                v0 = 0x43500000;
                mtc1(v0, f2);
                lwc1(f0, s1, edscroll::kEndY0);
                sub_s(f1, f0, f2);
                v0 = 0x40000000;
                mtc1(v0, f0);
                mul_s(f1, f0, f1);
                lwc1(f0, gp, -32064);  // 0x7CAFB0
                div_s(f21, f0, f1);
                lwc1(f0, gp, -32552);  // 0x7CADC8
                div_s(f0, f0, f21);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
            }
            // 0x00279f04
            charge(ctx, 4);
            lw(v1, s1, edscroll::kEndFrame);
            at = slt(v1, a0);
            if (at == 0) {
                // 0x00279fcc
                charge(ctx, 5);
                lw(v0, gp, kGpEdHoldFrames);  // the hold of the staff roll at the end: 60 frames (alternate episode) or 30 (0x7CC4E0) 0x7CC4E0
                v0 = addu(a0, v0);
                at = slt(v1, v0);
                if (at == 0) {
                    // 0x00279ffc
                    charge(ctx, 4);
                    v0 = addiu(v0, 45);
                    at = slt(v1, v0);
                    if (at == 0) {
                        // 0x0027a0b0
                        charge(ctx, 7);
                        mtc1(zero, f20);
                        lw(v0, s1, edscroll::kLastLine);
                        swc1(f2, v0, edline::kY);
                        lw(v1, s1, edscroll::kFlags);
                        v0 = si(-2);
                        v0 = v1 & v0;
                        sw(v0, s1, edscroll::kFlags);
                    } else {
                        // 0x0027a00c
                        charge(ctx, 23);
                        v1 = addiu(v1, 1);
                        sw(v1, s1, edscroll::kEndFrame);
                        lw(v0, gp, kGpEdHoldFrames);  // the hold of the staff roll at the end: 60 frames (alternate episode) or 30 (0x7CC4E0) 0x7CC4E0
                        v0 = addu(a0, v0);
                        v0 = addiu(v0, 45);
                        v0 = subu(v0, v1);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x437F0000;
                        mtc1(v0, f0);
                        mul_s(f1, f0, f1);
                        v0 = 0x42340000;
                        mtc1(v0, f0);
                        div_s(f1, f1, f0);
                        v0 = 0x4F000000;
                        mtc1(v0, f0);
                        c_le_s(f0, f1);
                        if (cond(ctx)) {
                            // 0x0027a080
                            charge(ctx, 6);
                            sub_s(f0, f1, f0);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            v0 = lui(0x8000);
                            v1 = v1 | v0;
                            v1 = v1 & 0xFF;
                        } else {
                            // 0x0027a068
                            charge(ctx, 6);
                            cvt_w_s(f0, f1);
                            mfc1(v1, f0);
                            v1 = v1 & 0xFF;
                        }
                        // 0x0027a098
                        charge(ctx, 6);
                        sb(v1, s1, edscroll::kRgba + 3);
                        mtc1(zero, f20);
                        lw(v0, s1, edscroll::kLastLine);
                        swc1(f2, v0, edline::kY);
                    }
                } else {
                    // 0x00279fe0
                    charge(ctx, 7);
                    v0 = addiu(v1, 1);
                    sw(v0, s1, edscroll::kEndFrame);
                    mtc1(zero, f20);
                    lw(v0, s1, edscroll::kLastLine);
                    swc1(f2, v0, edline::kY);
                }
            } else {
                // 0x00279f14
                charge(ctx, 6);
                v0 = addiu(v1, 1);
                sw(v0, s1, edscroll::kEndFrame);
                jal(ctx, 0x279F1Cu, gen::fn_sub_17D800_0017d800);
                if (v0 != 0) {
                    // 0x00279f7c
                    charge(ctx, 20);
                    lwc1(f0, s1, edscroll::kEndFrame);
                    cvt_s_w(f2, f0);
                    lwc1(f1, gp, -32068);  // 0x7CAFAC
                    mtc1(zero, f0);
                    adda_s(f0, f1);
                    msub_s(f20, f21, f2);
                    v0 = 0x3F000000;
                    mtc1(v0, f0);
                    mul_s(f0, f0, f21);
                    mul_s(f0, f0, f2);
                    mula_s(f1, f2);
                    msub_s(f1, f2, f0);
                    lwc1(f0, s1, edscroll::kEndY0);
                    sub_s(f0, f0, f1);
                    lw(v0, s1, edscroll::kLastLine);
                    swc1(f0, v0, edline::kY);
                } else {
                    // 0x00279f2c
                    charge(ctx, 20);
                    lwc1(f0, s1, edscroll::kEndFrame);
                    cvt_s_w(f2, f0);
                    lwc1(f1, gp, -32552);  // 0x7CADC8
                    mtc1(zero, f0);
                    adda_s(f0, f1);
                    msub_s(f20, f21, f2);
                    v0 = 0x3F000000;
                    mtc1(v0, f0);
                    mul_s(f0, f0, f21);
                    mul_s(f0, f0, f2);
                    mula_s(f1, f2);
                    msub_s(f1, f2, f0);
                    lwc1(f0, s1, edscroll::kEndY0);
                    sub_s(f0, f0, f1);
                    lw(v0, s1, edscroll::kLastLine);
                    swc1(f0, v0, edline::kY);
                }
            }
        } else {
            // 0x00279e40
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00279e50
                charge(ctx, 4);
                jal(ctx, 0x279E50u, gen::fn_sub_17D800_0017d800);
                if (v0 != 0) {
                    // 0x00279e6c
                    charge(ctx, 3);
                    lwc1(f20, gp, -32068);  // 0x7CAFAC
                } else {
                    // 0x00279e60
                    charge(ctx, 3);
                    lwc1(f20, gp, -32552);  // 0x7CADC8
                }
            } else {
                // 0x00279e48
                charge(ctx, 2);
            }
        }
        // 0x0027a0cc
        charge(ctx, 8);
        jal(ctx, 0x27A0CCu, gen::fn_sub_27B070_0027b070);
        s3 = v0;
        lw(v0, s1, edscroll::kFlags);
        v0 = nor(v0, 0);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x0027a0ec
            charge(ctx, 6);
            lwc1(f0, s1, edscroll::kNextY);
            sub_s(f1, f0, f20);
            s2 = 1;
            s0 = 0;
            for (;;) {
                // 0x0027a2ac
                charge(ctx, 7);
                v0 = 0x43E00000;
                mtc1(v0, f0);
                c_lt_s(f1, f0);
                v0 = 1;
                if (!cond(ctx)) {
                    // 0x0027a2c8
                    charge(ctx, 1);
                    v0 = 0;
                }
                // 0x0027a2cc
                charge(ctx, 3);
                v0 = v0 ^ 0x1;
                if (v0 == 0) {
                    // 0x0027a2d8
                    charge(ctx, 2);
                    if (s2 != 0) {
                        backedge(ctx);
                        // 0x0027a104
                        charge(ctx, 5);
                        jal(ctx, 0x27A104u, gen::fn_sub_27AAA0_0027aaa0);
                        v1 = 4;
                        if (v0 == v1) {
                            // 0x0027a278
                            charge(ctx, 9);
                            lwc1(f1, s1, edscroll::kNextY);
                            v0 = 0x41400000;
                            mtc1(v0, f0);
                            add_s(f0, f1, f0);
                            swc1(f0, s1, edscroll::kNextY);
                            a0 = addiu(gp, -26632);  // "line 0\n"
                            jal(ctx, 0x27A294u, gen::fn_printf_005225a8);
                        } else {
                            // 0x0027a118
                            charge(ctx, 3);
                            v1 = 3;
                            if (v0 == v1) {
                                // 0x0027a22c
                                charge(ctx, 19);
                                jal(ctx, 0x27A22Cu, gen::fn_sub_27AB10_0027ab10);
                                mtc1(v0, f0);
                                cvt_s_w(f3, f0);
                                v0 = 0x41C00000;
                                mtc1(v0, f2);
                                lwc1(f1, s1, edscroll::kNextY);
                                mtc1(zero, f0);
                                adda_s(f0, f1);
                                madd_s(f0, f2, f3);
                                swc1(f0, s1, edscroll::kNextY);
                                a0 = 0x690000;
                                a0 = addiu(a0, -4240);  // "empty line\n"
                                jal(ctx, 0x27A268u, gen::fn_printf_005225a8);
                            } else {
                                // 0x0027a124
                                charge(ctx, 3);
                                v1 = 2;
                                if (v0 == v1) {
                                    // 0x0027a210
                                    charge(ctx, 7);
                                    s0 = 1;
                                    a0 = 0x690000;
                                    a0 = addiu(a0, -4256);  // "caption\n"
                                    jal(ctx, 0x27A21Cu, gen::fn_printf_005225a8);
                                } else {
                                    // 0x0027a130
                                    charge(ctx, 3);
                                    v1 = 1;
                                    if (v0 == v1) {
                                        // 0x0027a170
                                        charge(ctx, 21);
                                        jal(ctx, 0x27A170u, gen::fn_sub_27A4A0_0027a4a0);
                                        s4 = v0;
                                        s0 = sltu(0, s0);
                                        a0 = s3;
                                        lw(a1, s1, edscroll::kStringIndex);
                                        jal(ctx, 0x27A188u, gen::fn_sub_279AF0_00279af0);
                                        a0 = s4;
                                        a1 = v0;
                                        a2 = s0;
                                        jal(ctx, 0x27A19Cu, gen::fn_sub_27A6A0_0027a6a0);
                                        lw(v0, s1, edscroll::kStringIndex);
                                        s0 = addiu(v0, 1);
                                        sw(s0, s1, edscroll::kStringIndex);
                                        a0 = s3;
                                        jal(ctx, 0x27A1B4u, gen::fn_sub_279B20_00279b20);
                                        if (s0 == v0) {
                                            // 0x0027a1c4
                                            charge(ctx, 4);
                                            sw(s4, s1, edscroll::kLastLine);
                                            lw(v0, s1, edscroll::kFlags);
                                            v0 = v0 | 0x4;
                                            sw(v0, s1, edscroll::kFlags);
                                        }
                                        // 0x0027a1d4
                                        charge(ctx, 15);
                                        lwc1(f0, s1, edscroll::kNextY);
                                        swc1(f0, s4, edline::kY);
                                        lwc1(f1, s1, edscroll::kNextY);
                                        v0 = 0x41C00000;
                                        mtc1(v0, f0);
                                        add_s(f0, f1, f0);
                                        swc1(f0, s1, edscroll::kNextY);
                                        s0 = 0;
                                        a0 = 0x690000;
                                        a0 = addiu(a0, -4272);  // "regist string\n"
                                        jal(ctx, 0x27A200u, gen::fn_printf_005225a8);
                                    } else {
                                        // 0x0027a13c
                                        charge(ctx, 2);
                                        if (v0 == 0) {
                                            // 0x0027a14c
                                            charge(ctx, 9);
                                            lw(v0, s1, edscroll::kFlags);
                                            v0 = v0 | 0x2;
                                            sw(v0, s1, edscroll::kFlags);
                                            s2 = 0;
                                            lwc1(f0, s1, edscroll::kNextY);
                                            add_s(f0, f0, f20);
                                            swc1(f0, s1, edscroll::kNextY);
                                        } else {
                                            // 0x0027a144
                                            charge(ctx, 2);
                                        }
                                    }
                                }
                            }
                        }
                        // 0x0027a29c
                        charge(ctx, 4);
                        jal(ctx, 0x27A29Cu, gen::fn_sub_27AB80_0027ab80);
                        lwc1(f0, s1, edscroll::kNextY);
                        sub_s(f1, f0, f20);
                        continue;
                    }
                }
                break;
            }
        }
        // 0x0027a2e0
        charge(ctx, 3);
        s2 = 0;
        for (;;) {
            // 0x0027a35c
            charge(ctx, 3);
            v0 = slti(s2, 32);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0027a2ec
            charge(ctx, 10);
            v0 = sll(s2, 3);
            v0 = addu(v0, s2);
            v0 = sll(v0, 4);
            v0 = addu(s1, v0);
            s0 = addiu(v0, 4);
            lw(v0, v0, 4);
            v0 = nor(v0, 0);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x0027a314
                charge(ctx, 11);
                lwc1(f0, s0, 140);
                sub_s(f1, f0, f20);
                v0 = 0x41C00000;
                mtc1(v0, f0);
                add_s(f1, f0, f1);
                mtc1(zero, f0);
                c_lt_s(f1, f0);
                if (cond(ctx)) {
                    // 0x0027a340
                    charge(ctx, 3);
                    a0 = s0;
                    jal(ctx, 0x27A344u, gen::fn_sub_27A560_0027a560);
                }
                // 0x0027a34c
                charge(ctx, 3);
                lwc1(f0, s0, 140);
                sub_s(f0, f0, f20);
                swc1(f0, s0, 140);
            }
            // 0x0027a358
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
        // 0x0027a368
        charge(ctx, 5);
        lwc1(f0, s1, edscroll::kNextY);
        sub_s(f0, f0, f20);
        swc1(f0, s1, edscroll::kNextY);
        jal(ctx, 0x27A374u, gen::fn_sub_27A5D0_0027a5d0);
    }
    // 0x0027a37c (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0027A3B0 sub_27A3B0 -- 240 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [edScrollDraw] Draws the staff roll (the 'edsr draw' task's pass; K_Assert line 88): every glyph list of every used
// line slot through frFontDraw (a0 list, 1, 0) while the scroll runs. (Its caller, functions.json's
// btlDrawMessagePass, is the staff roll's draw callback.)
void sub_27A3B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027a3b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    if (v1 == 0) {
        // 0x0027a3d4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4288);  // "ed_scroll.c"
        a1 = 88;
        jal(ctx, 0x27A3E0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027a3e8
    charge(ctx, 6);
    lw(s1, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    lw(v1, s1, edscroll::kFlags);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x0027a400
        charge(ctx, 3);
        s3 = 0;
        for (;;) {
            // 0x0027a474
            charge(ctx, 3);
            v1 = slti(s3, 32);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0027a40c
            charge(ctx, 10);
            v1 = sll(s3, 3);
            v1 = addu(v1, s3);
            v1 = sll(v1, 4);
            v1 = addu(s1, v1);
            s0 = addiu(v1, 4);
            lw(v1, v1, 4);
            v1 = nor(v1, 0);
            v1 = v1 & 0x1;
            if (v1 == 0) {
                // 0x0027a434
                charge(ctx, 3);
                s2 = 0;
                for (;;) {
                    // 0x0027a460
                    charge(ctx, 4);
                    lw(v1, s0, 132);
                    v1 = slt(s2, v1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0027a440
                    charge(ctx, 8);
                    v0 = sll(s2, 3);
                    v0 = addu(s0, v0);
                    lw(a0, v0, 8);
                    a1 = 1;
                    a2 = 0;
                    jal(ctx, 0x27A454u, gen::fn_frFontDraw_003b1360);
                    s2 = addiu(s2, 1);
                }
            }
            // 0x0027a470
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
    }
    // 0x0027a480 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0027A4A0 sub_27A4A0 -- 180 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [edScrollAllocLine] Takes the first free staff roll line slot (of 32, 144 bytes from +4), marks it used and returns
// it (K_Assert line 407 when all are used).
void sub_27A4A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027a4a0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    if (v0 == 0) {
        // 0x0027a4b8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4288);  // "ed_scroll.c"
        a1 = 88;
        jal(ctx, 0x27A4C4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027a4cc
    charge(ctx, 4);
    lw(v1, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    a0 = 0;
    for (;;) {
        // 0x0027a504
        charge(ctx, 3);
        v0 = slti(a0, 32);
        if (v0 != 0) {
            backedge(ctx);
            // 0x0027a4dc
            charge(ctx, 9);
            v0 = sll(a0, 3);
            v0 = addu(v0, a0);
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            s0 = addiu(v0, 4);
            lw(v0, v0, 4);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x0027a500
                charge(ctx, 1);
                a0 = addiu(a0, 1);
                continue;
            }
        }
        break;
    }
    // 0x0027a510
    charge(ctx, 3);
    v0 = slti(a0, 32);
    if (v0 == 0) {
        // 0x0027a51c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4288);  // "ed_scroll.c"
        a1 = 407;
        jal(ctx, 0x27A528u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027a530 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(v0, s0, 0);
    v0 = v0 | 0x1;
    sw(v0, s0, 0);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027A560 sub_27A560 -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [edScrollFreeLine] Frees a staff roll line slot (a0): each of its +132 glyph lists through sub_3B0170, then clears
// the used flag.
// Arguments: a0 the line slot.
void sub_27A560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027a560
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = 0;
    for (;;) {
        // 0x0027a598
        charge(ctx, 4);
        lw(v1, s0, edline::kWordCount);
        v1 = slt(s1, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027a580
        charge(ctx, 6);
        v0 = sll(s1, 3);
        v0 = addu(s0, v0);
        lw(a0, v0, 8);
        jal(ctx, 0x27A58Cu, gen::fn_sub_3B0170_003b0170);
        s1 = addiu(s1, 1);
    }
    // 0x0027a5a8
    charge(ctx, 10);
    lw(a0, s0, edline::kFlags);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, s0, edline::kFlags);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0027A5D0 sub_27A5D0 -- 200 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [edScrollPlaceLines] Places every used staff roll line: position (x 57.0, the slot's y +140) through sub_27A930 and
// the work's line colour (+4652) through sub_27AA00.
void sub_27A5D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0027a5d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    if (v1 == 0) {
        // 0x0027a5f0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4288);  // "ed_scroll.c"
        a1 = 88;
        jal(ctx, 0x27A5FCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027a604
    charge(ctx, 4);
    lw(s0, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    s1 = 0;
    for (;;) {
        // 0x0027a670
        charge(ctx, 3);
        v1 = slti(s1, 32);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027a614
        charge(ctx, 10);
        v1 = sll(s1, 3);
        v1 = addu(v1, s1);
        v1 = sll(v1, 4);
        v1 = addu(s0, v1);
        s2 = addiu(v1, 4);
        lw(v1, v1, 4);
        v1 = nor(v1, 0);
        v1 = v1 & 0x1;
        if (v1 == 0) {
            // 0x0027a63c
            charge(ctx, 12);
            v0 = 0x42640000;
            sw(v0, sp, 0x48);
            lwc1(f0, s2, 140);
            swc1(f0, sp, 0x4C);
            a0 = s2;
            a1 = addiu(sp, 0x48);
            jal(ctx, 0x27A654u, gen::fn_sub_27A930_0027a930);
            a0 = s2;
            a1 = addiu(s0, 4652);
            jal(ctx, 0x27A664u, gen::fn_sub_27AA00_0027aa00);
        }
        // 0x0027a66c
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0027a67c
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0027A6A0 sub_27A6A0 -- 656 bytes; frame 0x1D0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [edScrollBuildLine] Breaks a staff roll string (a1) into words for a line slot (a0): walks the string to its NUL;
// each word (ended by a tab, space or the NUL) becomes a glyph list (frFontBuildGlyphList of the strncpy'd word, font
// 6 for a name or font 7 for a caption by a2) stored with its x offset at slot +4 / +8 + 8 * n; the offset advances
// by the word's width, 40 px per tab and 10 px per space; slot +132 the word count; the default glyph flags 1 / 2 are
// set / cleared around it.
// Arguments: a0 the line slot, a1 the string, a2 1 a caption.
void sub_27A6A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0027a6a0
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1D0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s6 = a0;
    s7 = a2;
    s5 = a1;
    s4 = a1;
    a0 = a1;
    jal(ctx, 0x27A6E4u, gen::fn_strlen_00524388);
    sq(v0, sp, 0xB0);
    s3 = 0;
    a0 = 1;
    jal(ctx, 0x27A6F8u, gen::fn_frFontSetDefaultGlyphFlags_003b0e70);
    a0 = 2;
    jal(ctx, 0x27A704u, gen::fn_frFontClearDefaultGlyphFlags_003b0e90);
    a0 = 0;
    mtc1(zero, f20);
    s2 = 0;
    for (;;) {
        // 0x0027a8c8
        charge(ctx, 5);
        lq(v0, sp, 0xB0);
        v0 = addiu(v0, 1);
        v0 = slt(s2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027a720
        charge(ctx, 4);
        lb(v1, s5, 0);  // the character
        v0 = 9;
        bool separator = true;  // a tab, the NUL or a space ends a word
        if (v1 != v0) {
            // 0x0027a730
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x0027a738
                charge(ctx, 3);
                v0 = 32;
                if (v1 != v0) {
                    // 0x0027a744: inside a word
                    charge(ctx, 2);
                    // 0x0027a830
                    charge(ctx, 1);
                    a0 = 1;  // a word is open
                    separator = false;
                }
            }
        }
        if (separator) {
            // 0x0027a74c: a separator: an open word (a0) becomes a glyph list
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x0027a754: the word copied to the stack (strncpy + NUL)
                charge(ctx, 11);
                s0 = subu(s5, s4);
                a0 = addiu(sp, 0xD0);
                a1 = s4;
                a2 = s0;
                jal(ctx, 0x27A764u, gen::fn_strncpy_00524828);
                v0 = addu(s0, sp);
                sb(zero, v0, 208);
                v0 = 1;
                if (s7 == v0) {
                    // 0x0027a7a0: a caption: font 7, flag 1
                    charge(ctx, 2);
                    fp = 0x7;
                    sw(v0, sp, 0xCC);
                } else {
                    // 0x0027a780
                    charge(ctx, 2);
                    if (s7 == 0) {
                        // 0x0027a790: a name: font 6, flag 0
                        charge(ctx, 4);
                        fp = 0x6;
                        sw(zero, sp, 0xCC);
                    } else {
                        // 0x0027a788
                        charge(ctx, 2);
                    }
                }
                // 0x0027a7a8: the glyph list, white, stored with its x offset; x advances by its width
                charge(ctx, 34);
                a1 = dsll32(fp, 24);
                a1 = dsra32(a1, 24);
                lb(v0, sp, 0xCC);
                a2 = v0;
                a0 = addiu(sp, 0xD0);
                a3 = 0;
                t0 = 0;
                jal(ctx, 0x27A7C4u, gen::fn_frFontBuildGlyphList_003b0970);
                s1 = v0;
                mtc1(zero, f12);
                a0 = s1;
                jal(ctx, 0x27A7D8u, gen::fn_sub_3B2C60_003b2c60);
                a0 = s1;
                a1 = si(-1);
                jal(ctx, 0x27A7E8u, gen::fn_frFontLineSetRgba_003b0e20);
                v0 = sll(s3, 3);
                v0 = addu(s6, v0);
                sw(s1, v0, edline::kWords + 4);
                swc1(f20, v0, edline::kWords);
                s3 = addiu(s3, 1);
                s4 = addu(s4, s0);
                a0 = s1;
                jal(ctx, 0x27A80Cu, gen::fn_frFontLineGetWidth_003b19d0);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f20, f20, f0);
                a0 = 0;
            }
        }
        // 0x0027a834: a tab adds 40 px, a space 10, and both start the next word after them
        charge(ctx, 4);
        lb(v1, s5, 0);
        v0 = 9;
        if (v1 == v0) {
            // 0x0027a878
            charge(ctx, 4);
            v0 = 0x42200000;
            mtc1(v0, f0);
            add_s(f20, f20, f0);
        } else {
            // 0x0027a844
            charge(ctx, 3);
            v0 = 32;
            if (v1 == v0) {
                // 0x0027a860
                charge(ctx, 6);
                v0 = 0x41200000;
                mtc1(v0, f0);
                add_s(f20, f20, f0);
            } else {
                // 0x0027a850
                charge(ctx, 2);
                if (v1 != 0) {
                    // 0x0027a858
                    charge(ctx, 2);
                }
            }
        }
        // 0x0027a888
        charge(ctx, 3);
        v0 = 9;
        if (v1 == v0) {
            // 0x0027a8bc
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        } else {
            // 0x0027a894
            charge(ctx, 3);
            v0 = 32;
            if (v1 == v0) {
                // 0x0027a8b0
                charge(ctx, 3);
                s4 = addiu(s4, 1);
            } else {
                // 0x0027a8a0
                charge(ctx, 2);
                if (v1 != 0) {
                    // 0x0027a8a8
                    charge(ctx, 2);
                }
            }
        }
        // 0x0027a8c0
        charge(ctx, 2);
        s2 = addiu(s2, 1);
        s5 = addiu(s5, 1);
    }
    // 0x0027a8dc
    charge(ctx, 21);
    a0 = 1;
    jal(ctx, 0x27A8E0u, gen::fn_frFontClearDefaultGlyphFlags_003b0e90);
    a0 = 2;
    jal(ctx, 0x27A8ECu, gen::fn_frFontSetDefaultGlyphFlags_003b0e70);
    sw(s3, s6, edline::kWordCount);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1D0);
}

// 0x0027A930 sub_27A930 -- 196 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [edScrollPlaceLine] Positions a staff roll line slot's glyph lists (a0) at the point a1 {f32 x, y}: each list at
// (16 * (x + its offset), 8 * y) in the font's fixed-point units, then sub_3B2C60.
// Arguments: a0 the line slot, a1 f32[2].
void sub_27A930(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x0027a930
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = 0;
    for (;;) {
        // 0x0027a9c4
        charge(ctx, 4);
        lw(v1, s2, edline::kWordCount);
        v1 = slt(s0, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027a95c
        charge(ctx, 26);
        v0 = sll(s0, 3);
        v1 = addu(s2, v0);
        s3 = addiu(v1, 4);
        lwc1(f1, s1, 0);
        lwc1(f0, v1, 4);
        add_s(f1, f1, f0);
        v0 = 0x41800000;
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(a1, f0);
        v0 = 0x41000000;
        mtc1(v0, f1);
        lwc1(f0, s1, 4);
        mul_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        lw(a0, v1, 8);
        jal(ctx, 0x27A9A8u, gen::fn_frFontLineSetPos_003b0d70);
        mtc1(zero, f12);
        lw(a0, s3, 4);
        jal(ctx, 0x27A9B8u, gen::fn_sub_3B2C60_003b2c60);
        s0 = addiu(s0, 1);
    }
    // 0x0027a9d4
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0027AA00 sub_27AA00 -- 148 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [edScrollSetLineRgba] Sets the colour of a staff roll line slot's glyph lists (a0) from the bytes a1[0..3] (packed
// r << 24 | g << 16 | b << 8 | a) through frFontLineSetRgba.
// Arguments: a0 the line slot, a1 u8[4] rgba.
void sub_27AA00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027aa00
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lbu(v1, a1, 0);
    a0 = sll(v1, 24);
    lbu(v1, a1, 1);
    v1 = sll(v1, 16);
    a0 = a0 | v1;
    lbu(v1, a1, 2);
    v1 = sll(v1, 8);
    a0 = v1 | a0;
    lbu(v1, a1, 3);
    s1 = v1 | a0;
    s2 = 0;
    for (;;) {
        // 0x0027aa68
        charge(ctx, 4);
        lw(v1, s0, edline::kWordCount);
        v1 = slt(s2, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027aa4c
        charge(ctx, 7);
        v0 = sll(s2, 3);
        v0 = addu(s0, v0);
        lw(a0, v0, 8);
        a1 = s1;
        jal(ctx, 0x27AA5Cu, gen::fn_frFontLineSetRgba_003b0e20);
        s2 = addiu(s2, 1);
    }
    // 0x0027aa78
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0027AAA0 sub_27AAA0 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [edScrollPeekCommand] The staff roll command at the script cursor (the command stream's byte at +4620).
void sub_27AAA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027aaa0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    if (v0 == 0) {
        // 0x0027aab8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4288);  // "ed_scroll.c"
        a1 = 88;
        jal(ctx, 0x27AAC4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027aacc
    charge(ctx, 14);
    lw(s0, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    jal(ctx, 0x27AAD0u, gen::fn_sub_27B070_0027b070);
    a0 = v0;
    jal(ctx, 0x27AADCu, gen::fn_sub_279B10_00279b10);
    lw(v1, s0, edscroll::kCursor);
    v0 = addu(v0, v1);
    lbu(v0, v0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027AB10 sub_27AB10 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [edScrollPeekOperand] The staff roll command's operand (the byte after the cursor: the blank line count of command
// 3).
void sub_27AB10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027ab10
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    if (v0 == 0) {
        // 0x0027ab28
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4288);  // "ed_scroll.c"
        a1 = 88;
        jal(ctx, 0x27AB34u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027ab3c
    charge(ctx, 14);
    lw(s0, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    jal(ctx, 0x27AB40u, gen::fn_sub_27B070_0027b070);
    a0 = v0;
    jal(ctx, 0x27AB4Cu, gen::fn_sub_279B10_00279b10);
    lw(v1, s0, edscroll::kCursor);
    v0 = addu(v1, v0);
    lbu(v0, v0, 1);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027AB80 sub_27AB80 -- 220 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [edScrollStepCommand] Steps the staff roll command cursor past the current command: 1 / 2 / 4 one byte, 3 two bytes
// (its operand), 0 stays (the end).
void sub_27AB80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027ab80
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    if (v0 == 0) {
        // 0x0027ab98
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4288);  // "ed_scroll.c"
        a1 = 88;
        jal(ctx, 0x27ABA4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027abac
    charge(ctx, 12);
    lw(s0, gp, kGpEdScroll);  // the staff roll scroll (ed_scroll.c) 0x7CE3D4
    jal(ctx, 0x27ABB0u, gen::fn_sub_27B070_0027b070);
    a0 = v0;
    jal(ctx, 0x27ABBCu, gen::fn_sub_279B10_00279b10);
    lw(a1, s0, edscroll::kCursor);
    v1 = addu(v0, a1);
    lbu(a0, v1, 0);
    v1 = 4;
    if (a0 == v1) {
        // 0x0027ac40
        charge(ctx, 2);
        v1 = addiu(a1, 1);
        sw(v1, s0, edscroll::kCursor);
    } else {
        // 0x0027abdc
        charge(ctx, 3);
        v1 = 3;
        if (a0 == v1) {
            // 0x0027ac30
            charge(ctx, 4);
            v1 = addiu(a1, 2);
            sw(v1, s0, edscroll::kCursor);
        } else {
            // 0x0027abe8
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                // 0x0027ac20
                charge(ctx, 4);
                v1 = addiu(a1, 1);
                sw(v1, s0, edscroll::kCursor);
            } else {
                // 0x0027abf4
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    // 0x0027ac10
                    charge(ctx, 4);
                    v1 = addiu(a1, 1);
                    sw(v1, s0, edscroll::kCursor);
                } else {
                    // 0x0027ac00
                    charge(ctx, 2);
                    if (a0 != 0) {
                        // 0x0027ac08
                        charge(ctx, 2);
                    }
                }
            }
        }
    }
    // 0x0027ac48 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027AC60 sub_27AC60 -- 20 bytes; leaf frame (no stack)
// [edResInit] Initialises the staff roll resource work (a0, 16 bytes) and registers it at $gp 0x7CE3D8: both flag
// words 0.
// Arguments: a0 the work.
void sub_27AC60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0027ac60
    enter(ctx, 5);  // entry check point + this block's cycles
    sw(zero, a0, edres::kLoading);
    sw(zero, a0, edres::kLoaded);
    sw(a0, gp, kGpEdRes);  // the staff roll resources (ed_res.c) 0x7CE3D8
}

// 0x0027AC80 sub_27AC80 -- 88 bytes; frame 0x10: ra sp+0x0
// [edResTerm] Closes the staff roll resource work (K_Assert line 49): releases the loaded resources (sub_27AFD0) and
// clears the $gp slot.
void sub_27AC80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027ac80
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpEdRes);  // the staff roll resources (ed_res.c) 0x7CE3D8
    if (v1 == 0) {
        // 0x0027ac94
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4224);  // "ed_res.c"
        a1 = 49;
        jal(ctx, 0x27ACA0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027aca8
    charge(ctx, 5);
    lw(v1, gp, kGpEdRes);  // the staff roll resources (ed_res.c) 0x7CE3D8
    lw(v1, v1, edres::kLoaded);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x0027acbc
        charge(ctx, 2);
        jal(ctx, 0x27ACBCu, gen::fn_sub_27AFD0_0027afd0);
    }
    // 0x0027acc4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sw(zero, gp, kGpEdRes);  // the staff roll resources (ed_res.c) 0x7CE3D8
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027ACE0 sub_27ACE0 -- 420 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [edResUpdate] Per-frame step of the staff roll resource work (K_Assert line 49): once the requested archive is
// loaded (flag 1, H_Cdvd_IsFileLoaded) it takes its three files -- 0 the script (edScriptBuild), 1 / 2 the fonts 6 /
// 7 copied into RwMalloc blocks and installed with frLoadFontData_Ptr --, sets loaded (+4 flag 1), destroys the
// request and clears flag 1.
void sub_27ACE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027ace0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpEdRes);  // the staff roll resources (ed_res.c) 0x7CE3D8
    if (v1 == 0) {
        // 0x0027ad04
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4224);  // "ed_res.c"
        a1 = 49;
        jal(ctx, 0x27AD10u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027ad18
    charge(ctx, 5);
    lw(s0, gp, kGpEdRes);  // the staff roll resources (ed_res.c) 0x7CE3D8
    lw(v1, s0, edres::kLoading);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x0027ad2c
        charge(ctx, 5);
        lw(a0, s0, edres::kRequest);
        jal(ctx, 0x27AD30u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
        if (v0 != 0) {
            // 0x0027ad40
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x0027ae30
                charge(ctx, 3);
                v0 = slti(s2, 3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0027ad4c
                charge(ctx, 9);
                lw(a0, s0, edres::kRequest);
                a1 = s2;
                a2 = addiu(sp, 0x5C);
                jal(ctx, 0x27AD58u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                s1 = v0;
                v0 = 2;
                if (s2 == v0) {
                    // 0x0027adec
                    charge(ctx, 16);
                    lw(a0, sp, 0x5C);
                    a1 = 0x40000;
                    v0 = 0x960000;
                    lw(v0, v0, 376);  // 0x960178
                    jalr(ctx, 0x27ADFCu, v0.u());
                    s3 = v0;
                    lw(a2, sp, 0x5C);
                    a0 = s3;
                    a1 = s1;
                    jal(ctx, 0x27AE14u, gen::fn_memcpy_00521250);
                    a0 = 7;
                    a1 = s3;
                    jal(ctx, 0x27AE24u, gen::fn_frLoadFontData_Ptr_003af770);
                } else {
                    // 0x0027ad70
                    charge(ctx, 3);
                    v0 = 1;
                    if (s2 == v0) {
                        // 0x0027ada4
                        charge(ctx, 18);
                        lw(a0, sp, 0x5C);
                        a1 = 0x40000;
                        v0 = 0x960000;
                        lw(v0, v0, 376);  // 0x960178
                        jalr(ctx, 0x27ADB4u, v0.u());
                        s3 = v0;
                        lw(a2, sp, 0x5C);
                        a0 = s3;
                        a1 = s1;
                        jal(ctx, 0x27ADCCu, gen::fn_memcpy_00521250);
                        a0 = 6;
                        a1 = s3;
                        jal(ctx, 0x27ADDCu, gen::fn_frLoadFontData_Ptr_003af770);
                    } else {
                        // 0x0027ad7c
                        charge(ctx, 2);
                        if (s2 == 0) {
                            // 0x0027ad8c
                            charge(ctx, 6);
                            a0 = s1;
                            jal(ctx, 0x27AD90u, gen::fn_sub_279940_00279940);
                            sw(v0, s0, edres::kScript);
                        } else {
                            // 0x0027ad84
                            charge(ctx, 2);
                        }
                    }
                }
                // 0x0027ae2c
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x0027ae3c
            charge(ctx, 10);
            lw(v0, s0, edres::kLoaded);
            v0 = v0 | 0x1;
            sw(v0, s0, edres::kLoaded);
            lw(a0, s0, edres::kRequest);
            jal(ctx, 0x27AE4Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
            lw(a0, s0, edres::kLoading);
            v1 = si(-2);
            v1 = a0 & v1;
            sw(v1, s0, edres::kLoading);
        }
    }
    // 0x0027ae64 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0027AE90 sub_27AE90 -- 232 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [edResRequest] Requests the staff roll archive (K_Assert lines 118 / 119: not loading, not loaded):
// oped/ed_sr_f.bin for the alternate episode (sub_17D800), else oped/ed_sr.bin, through H_Cdvd_Request (kind 1); sets
// flag 1.
void sub_27AE90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027ae90
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpEdRes);  // the staff roll resources (ed_res.c) 0x7CE3D8
    if (v0 == 0) {
        // 0x0027aea8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4224);  // "ed_res.c"
        a1 = 49;
        jal(ctx, 0x27AEB4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027aebc
    charge(ctx, 6);
    lw(s0, gp, kGpEdRes);  // the staff roll resources (ed_res.c) 0x7CE3D8
    lw(v0, s0, edres::kLoading);
    v0 = nor(v0, 0);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0027aed4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4224);  // "ed_res.c"
        a1 = 118;
        jal(ctx, 0x27AEE0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027aee8
    charge(ctx, 5);
    lw(v0, s0, edres::kLoaded);
    v0 = nor(v0, 0);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0027aefc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4224);  // "ed_res.c"
        a1 = 119;
        jal(ctx, 0x27AF08u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027af10
    charge(ctx, 4);
    jal(ctx, 0x27AF10u, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x0027af40
        charge(ctx, 6);
        a0 = 0x690000;
        a0 = addiu(a0, -4192);  // "oped/ed_sr_f.bin"
        a1 = 1;
        jal(ctx, 0x27AF4Cu, gen::fn_H_Cdvd_Request_00100d80);
        sw(v0, s0, edres::kRequest);
    } else {
        // 0x0027af20
        charge(ctx, 8);
        a0 = 0x690000;
        a0 = addiu(a0, -4208);  // "oped/ed_sr.bin"
        a1 = 1;
        jal(ctx, 0x27AF2Cu, gen::fn_H_Cdvd_Request_00100d80);
        sw(v0, s0, edres::kRequest);
    }
    // 0x0027af58 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v1, s0, edres::kLoading);
    v1 = v1 | 0x1;
    sw(v1, s0, edres::kLoading);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027AF80 sub_27AF80 -- 68 bytes; frame 0x10: ra sp+0x0
// [edResIsLoading] Nonzero while the staff roll archive loads (flag 1).
void sub_27AF80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027af80
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpEdRes);  // the staff roll resources (ed_res.c) 0x7CE3D8
    if (v0 == 0) {
        // 0x0027af94
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4224);  // "ed_res.c"
        a1 = 49;
        jal(ctx, 0x27AFA0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027afa8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpEdRes);  // the staff roll resources (ed_res.c) 0x7CE3D8
    lw(v0, v0, edres::kLoading);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027AFD0 sub_27AFD0 -- 156 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [edResRelease] Releases the staff roll resources (K_Assert line 142 when not loaded): the script object, the fonts
// 6 and 7 (sub_3AFC30), clears the loaded flag.
void sub_27AFD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027afd0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpEdRes);  // the staff roll resources (ed_res.c) 0x7CE3D8
    if (v0 == 0) {
        // 0x0027afe8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4224);  // "ed_res.c"
        a1 = 49;
        jal(ctx, 0x27AFF4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027affc
    charge(ctx, 5);
    lw(s0, gp, kGpEdRes);  // the staff roll resources (ed_res.c) 0x7CE3D8
    lw(v0, s0, edres::kLoaded);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0027b010
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4224);  // "ed_res.c"
        a1 = 142;
        jal(ctx, 0x27B01Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027b024
    charge(ctx, 18);
    lw(a0, s0, edres::kScript);
    jal(ctx, 0x27B028u, gen::fn_sub_279AC0_00279ac0);
    a0 = 6;
    jal(ctx, 0x27B034u, gen::fn_sub_3AFC30_003afc30);
    a0 = 7;
    jal(ctx, 0x27B040u, gen::fn_sub_3AFC30_003afc30);
    lw(a0, s0, edres::kLoaded);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, s0, edres::kLoaded);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027B070 sub_27B070 -- 64 bytes; frame 0x10: ra sp+0x0
// [edResGetScript] The staff roll script object (resource work +12; K_Assert line 49).
void sub_27B070(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027b070
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpEdRes);  // the staff roll resources (ed_res.c) 0x7CE3D8
    if (v0 == 0) {
        // 0x0027b084
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4224);  // "ed_res.c"
        a1 = 49;
        jal(ctx, 0x27B090u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027b098 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lw(v0, gp, kGpEdRes);  // the staff roll resources (ed_res.c) 0x7CE3D8
    lw(v0, v0, edres::kScript);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027B0B0 sub_27B0B0 -- 332 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [edSrUpdate] Per-frame update of the staff roll ('edsr' task, ed_sr.c; K_Assert line 61), while running: step 0
// waits for the archive, starts the fade-in (sub_1085C0) -> 1; step 1 once the fade is idle (sub_108710) starts the
// movie and the scroll (sub_27B200) -> 2; step 2 counts frames and, once the scroll stopped and the movie task is
// gone (kwlnTaskExists), starts the fade-out (sub_108570) -> 3; step 3 clears the running flag once the fade is idle.
// Every frame the resource step and the scroll update run.
void sub_27B0B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027b0b0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpEdSr);  // the staff roll (ed_sr.c) 0x7CE3DC
    if (v1 == 0) {
        // 0x0027b0c8
        charge(ctx, 4);
        a0 = addiu(gp, -26624);  // "ed_sr.c"
        a1 = 61;
        jal(ctx, 0x27B0D0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027b0d8
    charge(ctx, 6);
    lw(s0, gp, kGpEdSr);  // the staff roll (ed_sr.c) 0x7CE3DC
    lw(v1, s0, edsr::kFlags);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x0027b0f0
        charge(ctx, 4);
        lw(v1, s0, edsr::kStep);
        v0 = 3;
        if (v1 == v0) {
            // 0x0027b1b8
            charge(ctx, 4);
            jal(ctx, 0x27B1B8u, gen::fn_sub_108710_00108710);
            if (v0 != 0) {
                // 0x0027b1c8
                charge(ctx, 4);
                lw(v1, s0, edsr::kFlags);
                v0 = si(-2);
                v0 = v1 & v0;
                sw(v0, s0, edsr::kFlags);
            }
        } else {
            // 0x0027b100
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x0027b170
                charge(ctx, 7);
                lw(v0, s0, edsr::kFrame);
                v0 = addiu(v0, 1);
                sw(v0, s0, edsr::kFrame);
                jal(ctx, 0x27B17Cu, gen::fn_sub_279D10_00279d10);
                if (v0 == 0) {
                    // 0x0027b18c
                    charge(ctx, 5);
                    lw(a0, s0, edsr::kMovieTask);
                    jal(ctx, 0x27B190u, gen::fn_kwlnTaskExists_00195460);
                    if (v0 == 0) {
                        // 0x0027b1a0
                        charge(ctx, 6);
                        jal(ctx, 0x27B1A0u, gen::fn_sub_108570_00108570);
                        v0 = 3;
                        sw(v0, s0, edsr::kStep);
                    }
                }
            } else {
                // 0x0027b10c
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x0027b150
                    charge(ctx, 4);
                    jal(ctx, 0x27B150u, gen::fn_sub_108710_00108710);
                    if (v0 != 0) {
                        // 0x0027b160
                        charge(ctx, 4);
                        jal(ctx, 0x27B160u, gen::fn_sub_27B200_0027b200);
                    }
                } else {
                    // 0x0027b118
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x0027b128
                        charge(ctx, 4);
                        jal(ctx, 0x27B128u, gen::fn_sub_27AF80_0027af80);
                        if (v0 == 0) {
                            // 0x0027b138
                            charge(ctx, 6);
                            jal(ctx, 0x27B138u, gen::fn_sub_1085C0_001085c0);
                            v0 = 1;
                            sw(v0, s0, edsr::kStep);
                        }
                    } else {
                        // 0x0027b120
                        charge(ctx, 2);
                    }
                }
            }
        }
        // 0x0027b1d8
        charge(ctx, 4);
        jal(ctx, 0x27B1D8u, gen::fn_sub_27ACE0_0027ace0);
        jal(ctx, 0x27B1E0u, gen::fn_sub_279D60_00279d60);
    }
    // 0x0027b1e8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027B200 sub_27B200 -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [edSrStartMovie] Starts the staff roll's movie and scroll: movie 42 for the alternate episode (sub_17D800), else 32
// with flag 2958 set or 33; starts the scroll (edScrollStart), creates the 'H_SfdPlay' movie task under the edsr task
// (sub_10BCE0) into +4688, clears the frame counter +4692, step 2.
void sub_27B200(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027b200
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpEdSr);  // the staff roll (ed_sr.c) 0x7CE3DC
    if (v0 == 0) {
        // 0x0027b21c
        charge(ctx, 4);
        a0 = addiu(gp, -26624);  // "ed_sr.c"
        a1 = 61;
        jal(ctx, 0x27B224u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027b22c
    charge(ctx, 5);
    lw(s0, gp, kGpEdSr);  // the staff roll (ed_sr.c) 0x7CE3DC
    jal(ctx, 0x27B230u, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x0027b26c
        charge(ctx, 1);
        s1 = 42;
    } else {
        // 0x0027b240
        charge(ctx, 5);
        a0 = 2958;
        jal(ctx, 0x27B244u, gen::fn_datGetFlag_0016f190);
        if (v0 == 0) {
            // 0x0027b260
            charge(ctx, 3);
            s1 = 33;
        } else {
            // 0x0027b254
            charge(ctx, 3);
            s1 = 32;
        }
    }
    // 0x0027b270
    charge(ctx, 16);
    jal(ctx, 0x27B270u, gen::fn_sub_279C90_00279c90);
    lw(a0, s0, edsr::kTask);
    a1 = s1;
    jal(ctx, 0x27B280u, gen::fn_sub_10BCE0_0010bce0);
    sw(v0, s0, edsr::kMovieTask);
    sw(zero, s0, edsr::kFrame);
    v1 = 2;
    sw(v1, s0, edsr::kStep);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0027B2B0 sub_27B2B0 -- 96 bytes; frame 0x10: ra sp+0x0
// [edSrTaskUpdate] The 'edsr' task's update callback: runs edSrUpdate and returns 0 while the staff roll runs, -1
// (the task ends) once it stopped.
void sub_27B2B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027b2b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x27B2B8u, gen::fn_sub_27B0B0_0027b0b0);
    lw(v0, gp, kGpEdSr);  // the staff roll (ed_sr.c) 0x7CE3DC
    if (v0 == 0) {
        // 0x0027b2cc
        charge(ctx, 4);
        a0 = addiu(gp, -26624);  // "ed_sr.c"
        a1 = 61;
        jal(ctx, 0x27B2D4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027b2dc
    charge(ctx, 5);
    lw(v0, gp, kGpEdSr);  // the staff roll (ed_sr.c) 0x7CE3DC
    lw(v0, v0, edsr::kFlags);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0027b2fc
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x0027b2f0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0027b300 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027B3F0 sub_27B3F0 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [edSrTaskDestroy] The 'edsr' task's destroy callback: closes the scroll and resource works and frees the task's
// work (a0 +60) through the RwFree slot.
// Arguments: a0 the task.
void sub_27B3F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027b3f0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpEdSr);  // the staff roll (ed_sr.c) 0x7CE3DC
    if (v0 == 0) {
        // 0x0027b40c
        charge(ctx, 4);
        a0 = addiu(gp, -26624);  // "ed_sr.c"
        a1 = 61;
        jal(ctx, 0x27B414u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027b41c
    charge(ctx, 14);
    jal(ctx, 0x27B41Cu, gen::fn_sub_279BF0_00279bf0);
    jal(ctx, 0x27B424u, gen::fn_sub_27AC80_0027ac80);
    lw(a0, s0, ktask::kWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x27B438u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027B460 sub_27B460 -- 328 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [edSrStart] Starts or polls the staff roll (a script command's handler): with no staff roll task (*$gp 0x7CE3E0) it
// allocates the 4,696-byte work, creates the 'edsr' task (edSrTaskUpdate / edSrTaskDestroy) and its 'edsr draw' child
// (btlDrawMessagePass), initialises the resource and scroll works inside, requests the archive and sets running;
// returns 0. Later calls return 0 while the task exists, then clear the slot and return 1.
void sub_27B460(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027b460
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, kGpEdSrTask);  // the staff roll's 'edsr' task 0x7CE3E0
    if (a0 != 0) {
        // 0x0027b56c
        charge(ctx, 4);
        jal(ctx, 0x27B56Cu, gen::fn_kwlnTaskExists_00195460);
        if (v0 != 0) {
            // 0x0027b58c
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0027b57c
            charge(ctx, 4);
            sw(zero, gp, kGpEdSrTask);  // the staff roll's 'edsr' task 0x7CE3E0
            v0 = 1;
        }
    } else {
        // 0x0027b47c
        charge(ctx, 45);
        a0 = 4696;
        a1 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178
        jalr(ctx, 0x27B48Cu, v0.u());
        s0 = v0;
        a0 = 0;
        a1 = 10;
        a2 = addiu(gp, -26616);  // "edsr"
        a3 = 0x280000;
        a3 = addiu(a3, -19792);  // &sub_27B2B0
        t0 = 0x280000;
        t0 = addiu(t0, -19472);  // &sub_27B3F0
        t1 = s0;
        jal(ctx, 0x27B4B8u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s1 = v0;
        a0 = 0x690000;
        a0 = addiu(a0, -4168);  // "edsr draw"
        a1 = 7384;
        a2 = 1;
        a3 = 2;
        t0 = 0x280000;
        t0 = addiu(t0, -19696);  // &btlDrawMessagePass
        t1 = 0;
        t2 = 0;
        jal(ctx, 0x27B4E8u, gen::fn_kwlnTaskInitEx_00194e10);
        sw(v0, s0, 8);
        a0 = s1;
        a1 = v0;
        jal(ctx, 0x27B4FCu, gen::fn_kwlnTaskAddChild_00195550);
        sw(zero, s0, 0);
        a0 = addiu(s0, 12);
        jal(ctx, 0x27B50Cu, gen::fn_sub_27AC60_0027ac60);
        a0 = addiu(s0, 28);
        jal(ctx, 0x27B518u, gen::fn_sub_279B30_00279b30);
        sw(s1, s0, 4);
        sw(s0, gp, kGpEdSr);  // the staff roll (ed_sr.c) 0x7CE3DC
        if (s0 == 0) {
            // 0x0027b530
            charge(ctx, 4);
            a0 = addiu(gp, -26624);  // "ed_sr.c"
            a1 = 61;
            jal(ctx, 0x27B538u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x0027b540
        charge(ctx, 11);
        lw(s0, gp, kGpEdSr);  // the staff roll (ed_sr.c) 0x7CE3DC
        jal(ctx, 0x27B544u, gen::fn_sub_27AE90_0027ae90);
        sw(zero, s0, edsr::kStep);
        lw(v0, s0, edsr::kFlags);
        v0 = v0 | 0x1;
        sw(v0, s0, edsr::kFlags);
        sw(s1, gp, kGpEdSrTask);  // the staff roll's 'edsr' task 0x7CE3E0
        v0 = 0;
    }
    // 0x0027b590 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

}  // namespace p3fes::game
