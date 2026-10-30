// The big draw bodies (game/include/p3fes/game/big_draws.h), hand-decompiled from SLUS_216.21: the title screen's
// per-frame draws of op_title.c / op_menu.c / op_wait.c (docs/ANALYSIS/27_unmapped_bands.md section 4; the title slice
// has the rest of those files) and the date / time HUD's three helpers (docs/ANALYSIS/20_menu_ui.md; the ui3 slice
// has the HUD task). Phase 5 slice `big_draws`: these replace the recompiled bodies listed in game/replaced.txt;
// tests/game/test_big_draws.cpp runs each against its __recomp body.
//
// How. The bodies were transliterated from the recompiled blocks by a scratch converter (`rt::` call -> Cpu statement,
// `ctx.cycles += N` -> charge, the back-edge `check_events` -> backedge, `rt::jal` + call -> jal), structured
// automatically where the shapes are plain (if-skips, if / else diamonds, else-chains to a common join, test-first and
// test-last loops), then the verbatim repeats were folded into the Cpu helpers of big_draws.h (f2u8, white_alpha,
// quad_pass, rotate_quad, scale_quad_about_centre, kassert) and the sections documented by hand. The HUD helpers were
// rewritten by hand around their jump tables.
//
// What the title draws do. None of them draws anything itself: each updates sprite strips in its module's work (the
// 4-vertex records of the 2D sprite helpers, battle_panel.h: positions at +0 / +4 per 64-byte vertex, colour floats at
// +32..+44) through sub_21CCA0 (an entry of the title image: its size at +12 / +16), sub_21D8E0 (a rectangle
// {x, y, w, h}), sub_21D890 (four free corners), sub_21EAE0 (a source rectangle) and sub_21D950 (one RGBA for all four
// vertices); the "op draw" task renders the strips later. Every animation is a function of the module's frame counters:
// a piecewise-linear ramp of a timer (alpha 0 -> 1 over a window, an offset moving in), a sine of a wrapping counter
// (2 pi * counter / period), or a rotation / zoom of a full-screen quad about the screen centre (320, 224). Fades are
// expressed as an alpha byte (u8)(255 * a) (f2u8: the compiled float -> unsigned conversion).
//
// Virtual time (ADR-0013): every enter / charge is one `ctx.cycles += N` block of the recompiled body on the executed
// path, charged where the block starts (before its calls); backedge() sits where the recompiled loop checks before
// jumping back (all the loops here test first: the check comes after a true test, before the body). A block that ends
// in a `jal` is charged in full before the call.
//
// Registers: register-faithful (big_draws.h). Each body keeps the original's register allocation; a scratch register
// holds the original's value at every call, check point and return; the FPU steps run through the runtime's EE
// semantics in the compiled order. The sprite calls of the HUD helpers pass on the caller's list register unset, as
// the original does.
#include "p3fes/game/big_draws.h"

#include "p3fes_recomp_rt.h"

namespace p3fes::recomp_gen {
void fn_clndGetDaysSinceStartFromDate_0017d8b0(p3fes::EEContext&);
void fn_clndGetWeekDay_0017dae0(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sprDrawSpriteBasic_001159f0(p3fes::EEContext&);
void fn_sub_115AD0_00115ad0(p3fes::EEContext&);
void fn_sub_115BC0_00115bc0(p3fes::EEContext&);
void fn_sub_17DB40_0017db40(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_21CCA0_0021cca0(p3fes::EEContext&);
void fn_sub_21D890_0021d890(p3fes::EEContext&);
void fn_sub_21D8E0_0021d8e0(p3fes::EEContext&);
void fn_sub_21D950_0021d950(p3fes::EEContext&);
void fn_sub_21EAE0_0021eae0(p3fes::EEContext&);
void fn_sub_266C50_00266c50(p3fes::EEContext&);
void fn_sub_269A10_00269a10(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {
namespace big_draws::detail {
namespace gen = ::p3fes::recomp_gen;

// =====================================================================================================================
// The date / time HUD's helpers. H_DayPartsDraw_DrawHud (ui3.cpp) calls them with $a0 = the HUD sprite file (task work
// +408), $f12 = the slide offset x (gp-19704), $f13 = 0, $a1 = 0 or the day-part name's alpha, $a2 / $a3 = month / day.
// Each draws through sprDrawSpriteBasic (0x1159F0; $a0 = the sprite list, $a1 = the file, $a2 = the sprite, $a3 = the
// alpha byte, $f12 / $f13 = x / y, $f14 = z 50.0) or its tinted / faded forms sub_115BC0 ($t0..$t2 = r, g, b) and
// sub_115AD0 ($t0 = alpha). The list argument is never set by these helpers: they pass on the caller's $s1 / $s6 / $s0
// (H_DayPartsDraw_DrawHud's $s5 path does not reach them; sprDrawSpriteBasic ignores it), as the original does.
// =====================================================================================================================

// 0x183840 [H_DayPartsDraw_DrawMoon](file, alpha, month, day): the moon of the date. days = clndGetDaysSinceStartFromDate
// (month, day), phase = tbl_clndMoonPhase[days] (0x5E38D0, 0..29). Unless phase 29: the disc (sprite 46 at 584, 57).
// The phase icon at (595, 67): sprite 18 for phase 29, else 3..17 by the jump table 0x7B6630 (phases 0-1 -> 3, 2-3 -> 4,
// 4-5 -> 5, 6 -> 6, 7-8 -> 7, 9-11 -> 8, 12-13 -> 9, 14 -> 10, 15-16 -> 11, 17-19 -> 12, 20-21 -> 13, 22 -> 14,
// 23-24 -> 15, 25-26 -> 16, 27-28 -> 17); a phase >= 30 leaves days itself as the sprite (as compiled). Phases 0..14
// (up to the full moon, 14): the glow, sprite icon + 57 at (584, 57) through sub_115AD0 with alpha
// tri * 255 / 20, tri the triangle 0..20..0 of the counter gp-19708 (0..40, one step per call). Then the phase's label
// at (540, ..): phase 29 sprite 2 (y 80), phases 6 / 22 sprite 0 (y 80), phase 14 sprite 1 (y 67).
void Cpu::sub_183840() {
    enter(26);
    sp = addiu(sp, -112);
    sd(ra, sp, 96);
    sq(s4, sp, 80);
    sq(s3, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s4 = a0;  // the file
    mov_s(F21, F12);  // x offset
    mov_s(F20, F13);  // y offset
    s3 = a1;  // alpha
    a0 = a2;
    a1 = a3;
    jal(0x183880u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
    s2 = v0;  // days
    v0 = lui(0x5E);
    v0 = addiu(v0, 14544);  // tbl_clndMoonPhase
    v0 = addu(v0, s2);
    lbu(s0, v0, 0);  // phase
    v0 = 29;
    if (s0 != v0) {  // the disc
        charge(16);
        v0 = lui(0x4412);  // 584.0
        mtc1(v0, F0);
        add_s(F12, F0, F21);
        v0 = lui(0x4264);  // 57.0
        mtc1(v0, F0);
        add_s(F13, F0, F20);
        a3 = s3 & 0xFF;
        v0 = lui(0x4248);  // 50.0
        mtc1(v0, F14);
        a0 = s1;
        a1 = s4;
        a2 = 46;
        jal(0x1838E0u, gen::fn_sprDrawSpriteBasic_001159f0);
    }
    // The phase icon: `sltiu at, phase, 30; beqz at; ...; jr` through 0x7B6630 (the target stays in $v0).
    charge(3);
    at = sltiu(s0, 30);
    if (at != 0) {
        charge(7);
        v1 = lui(0x7B);
        v1 = addiu(v1, 26160);
        v0 = sll(s0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x183910u: charge(3); s2 = 18; break;  // phase 29
        case 0x18391Cu: charge(3); s2 = 3; break;
        case 0x183928u: charge(3); s2 = 4; break;
        case 0x183934u: charge(3); s2 = 5; break;
        case 0x183940u: charge(3); s2 = 6; break;
        case 0x18394Cu: charge(3); s2 = 7; break;
        case 0x183958u: charge(3); s2 = 8; break;
        case 0x183964u: charge(3); s2 = 9; break;
        case 0x183970u: charge(3); s2 = 10; break;
        case 0x18397Cu: charge(3); s2 = 11; break;
        case 0x183988u: charge(3); s2 = 12; break;
        case 0x183994u: charge(3); s2 = 13; break;
        case 0x1839A0u: charge(3); s2 = 14; break;
        case 0x1839ACu: charge(3); s2 = 15; break;
        case 0x1839B8u: charge(3); s2 = 16; break;
        case 0x1839C4u: charge(1); s2 = 17; break;  // falls into the draw (no `b`)
        default: tail(v0.u()); return;
        }
    }
    charge(20);
    v0 = lui(0x4286);  // 67.0
    mtc1(v0, F0);
    add_s(F22, F0, F20);  // y 67 (kept for the full-moon label)
    v0 = 595;
    mtc1(v0, F0);
    cvt_s_w(F0, F0);
    add_s(F12, F0, F21);
    a3 = s3 & 0xFF;
    v0 = lui(0x4248);  // 50.0
    mtc1(v0, F14);
    a0 = s1;
    a1 = s4;
    a2 = s2;
    mov_s(F13, F22);
    jal(0x183A08u, gen::fn_sprDrawSpriteBasic_001159f0);
    // The glow of phases 0..14.
    if (gez(s0)) {
        charge(3);
        at = slti(s0, 15);
        if (at != 0) {
            charge(6);
            lw(v0, gp, kGpHudBlink);
            v0 = addiu(v0, 1);
            sw(v0, gp, kGpHudBlink);
            at = slti(v0, 41);
            if (at == 0) {
                charge(1);
                sw(zero, gp, kGpHudBlink);
            }
            charge(4);
            lw(v1, gp, kGpHudBlink);
            at = slti(v1, 21);
            if (at == 0) {  // the way down: 40 - n
                charge(2);
                v0 = 40;
                v1 = subu(v0, v1);
            }
            charge(22);
            a2 = addiu(s2, 57);
            v0 = lui(0x4412);  // 584.0
            mtc1(v0, F0);
            add_s(F12, F0, F21);
            v0 = lui(0x4264);  // 57.0
            mtc1(v0, F0);
            add_s(F13, F0, F20);
            a3 = s3 & 0xFF;
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);  // tri * 255
            v0 = 20;
            div(v1, v0);
            mflo(v0);
            t0 = v0 & 0xFF;
            v0 = lui(0x4248);  // 50.0
            mtc1(v0, F14);
            a0 = s1;
            a1 = s4;
            jal(0x183AA8u, gen::fn_sub_115AD0_00115ad0);
        }
    }
    // The phase label: 29 -> sprite 2, 6 / 22 -> sprite 0, 14 -> sprite 1.
    charge(3);
    v1 = 29;
    if (s0 == v1) {
        charge(18);
        v0 = lui(0x4407);  // 540.0
        mtc1(v0, F0);
        add_s(F12, F0, F21);
        v0 = lui(0x42A0);  // 80.0
        mtc1(v0, F0);
        add_s(F13, F0, F20);
        a3 = s3 & 0xFF;
        v0 = lui(0x4248);  // 50.0
        mtc1(v0, F14);
        a0 = s1;
        a1 = s4;
        a2 = 2;
        jal(0x183AF4u, gen::fn_sprDrawSpriteBasic_001159f0);
    } else {
        charge(3);
        v1 = 6;
        bool half = s0 == v1;
        if (!half) {
            charge(3);
            v1 = 22;
            half = s0 == v1;
        }
        if (half) {
            charge(18);
            v0 = lui(0x4407);  // 540.0
            mtc1(v0, F0);
            add_s(F12, F0, F21);
            v0 = lui(0x42A0);  // 80.0
            mtc1(v0, F0);
            add_s(F13, F0, F20);
            a3 = s3 & 0xFF;
            v0 = lui(0x4248);  // 50.0
            mtc1(v0, F14);
            a0 = s1;
            a1 = s4;
            a2 = 0;
            jal(0x183B54u, gen::fn_sprDrawSpriteBasic_001159f0);
        } else {
            charge(3);
            v1 = 14;
            if (s0 == v1) {
                charge(13);
                v0 = lui(0x4407);  // 540.0
                mtc1(v0, F0);
                add_s(F12, F0, F21);
                a3 = s3 & 0xFF;
                v0 = lui(0x4248);  // 50.0
                mtc1(v0, F14);
                a0 = s1;
                a1 = s4;
                a2 = 1;
                mov_s(F13, F22);
                jal(0x183B9Cu, gen::fn_sprDrawSpriteBasic_001159f0);
            }
        }
    }
    charge(12);
    ld(ra, sp, 96);
    lq(s4, sp, 80);
    lq(s3, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 112);
}

// 0x183BE0 [H_DayPartsDraw_DrawDate](file, alpha, month, day): month / day as digit sprites 35 + d through sub_115BC0
// with the tint (0, 14, 2), alpha max(alpha, 40) (`slti at, a1, 40` replaces smaller values): the month's tens '1' at
// x 515 (y 15, only month >= 10), its units at 532, the '/' (sprite 45) at 548, the day's tens at 557 (day >= 10), its
// units at 574 (all y 15). Then the weekday glyph at (592, 13): clndGetWeekDay(days) 0..6 -> sprite 34, 28..33 (jump
// table 0x7B66B0; a weekday >= 7 leaves $v0 = the weekday as the sprite), tinted (95, 42, 80) on a holiday or Sunday
// (sub_17DB40(days) == 1), (6, 78, 126) on Saturday (weekday 6), else (50, 60, 66). The sprite list argument is the
// caller's $s6.
void Cpu::sub_183BE0() {
    enter(21);
    sp = addiu(sp, -144);
    sd(ra, sp, 128);
    sq(s6, sp, 112);
    sq(s5, sp, 96);
    sq(s4, sp, 80);
    sq(s3, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s4 = a0;  // the file
    mov_s(F21, F12);
    mov_s(F20, F13);
    s3 = a1;  // alpha
    s1 = a2;  // month
    s0 = a3;  // day
    at = slti(s3, 40);
    if (at != 0) {
        charge(1);
        s3 = 40;
    }
    // `digit(sprite, x)`: the common arguments of the five digit calls (the caller's block charges them).
    const auto digit = [this](u32 link) {
        a3 = s3 & 0xFF;
        v0 = lui(0x4248);  // 50.0
        mtc1(v0, F14);
        a0 = s6;
        a1 = s4;
        mov_s(F13, F22);
        t0 = 0;
        t1 = 14;
        t2 = 2;
        jal(link, gen::fn_sub_115BC0_00115bc0);
    };
    charge(3);
    v0 = slti(s1, 10);
    if (v0 == 0) {  // the month's tens: always '1'
        charge(20);
        v0 = 515;
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        add_s(F12, F0, F21);
        v0 = lui(0x4170);  // 15.0
        mtc1(v0, F0);
        add_s(F13, F0, F20);
        a3 = s3 & 0xFF;
        v0 = lui(0x4248);  // 50.0
        mtc1(v0, F14);
        a0 = s6;
        a1 = s4;
        a2 = 36;
        t0 = 0;
        t1 = 14;
        t2 = 2;
        jal(0x183C8Cu, gen::fn_sub_115BC0_00115bc0);
    }
    charge(42);
    v0 = lui(0x4170);  // 15.0
    mtc1(v0, F0);
    add_s(F22, F0, F20);  // y 15
    v0 = 10;
    div(s1, v0);
    mfhi(v0);
    a2 = addiu(v0, 35);  // month % 10
    v0 = lui(0x4405);  // 532.0
    mtc1(v0, F0);
    add_s(F12, F0, F21);
    digit(0x183CE8u);
    v0 = lui(0x4409);  // 548.0
    mtc1(v0, F0);
    add_s(F12, F0, F21);
    a3 = s3 & 0xFF;
    v0 = lui(0x4248);  // 50.0
    mtc1(v0, F14);
    a0 = s6;
    a1 = s4;
    a2 = 45;  // '/'
    mov_s(F13, F22);
    t0 = 0;
    t1 = 14;
    t2 = 2;
    jal(0x183D28u, gen::fn_sub_115BC0_00115bc0);
    v0 = slti(s0, 10);
    if (v0 == 0) {  // the day's tens
        charge(20);
        v0 = 10;
        div(s0, v0);
        mflo(v0);
        a2 = addiu(v0, 35);
        v0 = 557;
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        add_s(F12, F0, F21);
        digit(0x183D84u);
    }
    charge(32);
    v0 = 10;
    div(s0, v0);
    mfhi(v0);
    a2 = addiu(v0, 35);  // day % 10
    v0 = 574;
    mtc1(v0, F0);
    cvt_s_w(F0, F0);
    add_s(F12, F0, F21);
    digit(0x183DD4u);
    // The weekday's tint.
    a0 = s1;
    a1 = s0;
    jal(0x183DE4u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
    s2 = v0;  // days
    a0 = dsll32(s2, 16);
    a0 = dsra32(a0, 16);  // (s16)days
    jal(0x183DF8u, gen::fn_sub_17DB40_0017db40);
    v1 = 1;
    if (v0 == v1) {  // holiday or Sunday
        charge(5);
        s1 = 95;
        s0 = 42;
        s5 = 80;
    } else {
        charge(6);
        a0 = s2;
        jal(0x183E24u, gen::fn_clndGetWeekDay_0017dae0);
        s1 = 6;
        if (v0 == s1) {  // Saturday
            charge(4);
            s0 = 78;
            s5 = 126;
        } else {
            charge(3);
            s1 = 50;
            s0 = 60;
            s5 = 66;
        }
    }
    // The weekday glyph: `sltiu at, v0, 7; beqz at; ...; jr` through 0x7B66B0 (the target stays in $v1).
    charge(6);
    a0 = s2;
    jal(0x183E58u, gen::fn_clndGetWeekDay_0017dae0);
    at = sltiu(v0, 7);
    if (at != 0) {
        charge(7);
        a0 = lui(0x7B);
        a0 = addiu(a0, 26288);
        v1 = sll(v0, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x183E88u: charge(3); v0 = 34; break;  // Sunday
        case 0x183E94u: charge(3); v0 = 28; break;
        case 0x183EA0u: charge(3); v0 = 29; break;
        case 0x183EACu: charge(3); v0 = 30; break;
        case 0x183EB8u: charge(3); v0 = 31; break;
        case 0x183EC4u: charge(3); v0 = 32; break;
        case 0x183ED0u: charge(1); v0 = 33; break;  // Saturday (falls into the draw)
        default: tail(v1.u()); return;
        }
    }
    charge(33);
    v1 = lui(0x4414);  // 592.0
    mtc1(v1, F0);
    add_s(F12, F0, F21);
    v1 = lui(0x4150);  // 13.0
    mtc1(v1, F0);
    add_s(F13, F0, F20);
    a3 = s3 & 0xFF;
    t0 = s1 & 0xFF;
    t1 = s0 & 0xFF;
    t2 = s5 & 0xFF;
    v1 = lui(0x4248);  // 50.0
    mtc1(v1, F14);
    a0 = s6;
    a1 = s4;
    a2 = v0;
    jal(0x183F18u, gen::fn_sub_115BC0_00115bc0);
    ld(ra, sp, 128);
    lq(s6, sp, 112);
    lq(s5, sp, 96);
    lq(s4, sp, 80);
    lq(s3, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 144);
}

// 0x183F60 [H_DayPartsDraw_DrawDayPart](file, alpha, month, day; $t0 = the day part): the day part's name at y 29. On a
// holiday or Sunday (sub_17DB40(days) == 1) parts 2..5 show the holiday name (sprite 54 at x 525) instead. Otherwise the
// jump table 0x7B66D0 (parts 0..8): 0 and 7 sprite 53 at 491, 1 47 at 452, 2 48 at 524, 3 49 at 495, 4 50 at 499,
// 5 51 at 467, 6 52 at 528, 8 (the Dark Hour) 55 at (500, 26); a part >= 9 draws nothing. The alpha byte is $a1 & 0xFF
// (the caller's fade), the sprite list argument the caller's $s0.
void Cpu::sub_183F60() {
    enter(24);
    sp = addiu(sp, -96);
    sd(ra, sp, 80);
    sq(s3, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s3 = a0;  // the file
    mov_s(F21, F12);
    mov_s(F20, F13);
    s2 = a1;  // alpha
    s1 = t0;  // the day part
    a0 = a2;
    a1 = a3;
    jal(0x183F9Cu, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    jal(0x183FACu, gen::fn_sub_17DB40_0017db40);
    // The name sprite at (x, y): `x` as an integer (`li; mtc1; cvt.s.w`, 19 cycles) or a float (`lui; mtc1`, 18).
    const auto name = [this](bool int_x, u32 x, u32 y_hi, u32 sprite, u32 link) {
        if (int_x) {
            v0 = x;
            mtc1(v0, F0);
            cvt_s_w(F0, F0);
        } else {
            v0 = lui(x);
            mtc1(v0, F0);
        }
        add_s(F12, F0, F21);
        v0 = lui(y_hi);
        mtc1(v0, F0);
        add_s(F13, F0, F20);
        a3 = s2 & 0xFF;
        v0 = lui(0x4248);  // 50.0
        mtc1(v0, F14);
        a0 = s0;
        a1 = s3;
        a2 = sprite;
        jal(link, gen::fn_sprDrawSpriteBasic_001159f0);
    };
    v1 = 1;
    bool drawn = false;
    if (v0 == v1) {  // holiday or Sunday: parts 2..5 -> the holiday name
        charge(4);
        v1 = addiu(s1, -2);
        at = sltiu(v1, 4);
        if (at != 0) {
            charge(19);
            name(true, 525, 0x41E8, 54, 0x18400Cu);  // 525, 29.0
            drawn = true;
        }
    }
    if (!drawn) {
        charge(3);
        at = sltiu(s1, 9);
        if (at != 0) {
            charge(7);
            a0 = lui(0x7B);
            a0 = addiu(a0, 26320);
            v1 = sll(s1, 2);
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
            switch (v1.u()) {
            case 0x184044u: charge(18); name(false, 0x43E2, 0x41E8, 47, 0x18407Cu); break;  // part 1: 452, 29
            case 0x18408Cu: charge(18); name(false, 0x4403, 0x41E8, 48, 0x1840C4u); break;  // part 2: 524
            case 0x1840D4u: charge(19); name(true, 495, 0x41E8, 49, 0x184110u); break;      // part 3
            case 0x184120u: charge(19); name(true, 499, 0x41E8, 50, 0x18415Cu); break;      // part 4
            case 0x18416Cu: charge(19); name(true, 467, 0x41E8, 51, 0x1841A8u); break;      // part 5
            case 0x1841B8u: charge(18); name(false, 0x4404, 0x41E8, 52, 0x1841F0u); break;  // part 6: 528
            case 0x184200u: charge(19); name(true, 491, 0x41E8, 53, 0x18423Cu); break;      // parts 0 and 7
            case 0x18424Cu: charge(16); name(false, 0x43FA, 0x41D0, 55, 0x184284u); break;  // part 8: 500, 26
            default: tail(v1.u()); return;
            }
        }
    }
    charge(10);
    ld(ra, sp, 80);
    lq(s3, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 96);
}

// =====================================================================================================================
// op_title.c (work gp-18756: +0 flags (bit 0 alive, bit 2 showing), +4 the fade timer, +8 the page (0 the logo
// appearing, 1 the logo moving aside for the menu), +16 / +272 / +528 / +784 / +1040 / +1296 the sprites, +1552 9
// streaks of 288 bytes (+0 flags bit 0 alive, +16 the strip, +272 the age, +276 the lane), +4148 3 emitters of 8 bytes
// (+0 the period, +4 the timer)).
// =====================================================================================================================
//
// 0x267430 [opTitle_Draw]: one frame of the title logo. Asserts the work (line 142); s1 = the work, s4 = the title
// image (opRes_GetTitleImage(0)), $f20 = the logo scale s = 1.0. Nothing more while flags bit 0 is clear. While showing
// (bit 2) the fade timer +4 counts up to 200 (page 0) / 512 (page 1), then bit 2 is cleared. Then six sprites, each from
// the page and the new timer t: an alpha $f23 (white, (u8)(255 * alpha)) and an offset ($f25, $f24); ramp(t, a, n) is
// 0 before a, (t - a) / n, then 1:
//   +16   entry 14 at (188, 144) + offset, its size times s. Page 0: alpha ramp(t, 70, 30). Page 1: alpha 1 - t / 10 for
//         t < 10 (1 for t < 0), 0 at 10..11, ramp(t, 12, 20) after, and from t = 10 on s = 0.787 (the .sdata literal at
//         0x7CB164, the logo's size beside the menu); the offset (108.5, -60.5) * t / 10, 0 at 10..11, the same times
//         (t - 12) / 20, and (217, -121) from 32 (the logo's move to the upper right).
//   +272  entry 13 at (188 - 8 s, 144 + 84 s) + offset: the same alpha; on page 1 the offset is half the corner move of
//         this part ((405 + 182 s) - (188 + 182 s), (23 - 6 s) - (144 - 6 s)) on the same schedule.
//   +1040 entry 36 at (188 + 182 s, 144 - 6 s) + offset: page 0 alpha ramp(t, 120, 45); page 1 as +272.
//   +784  entry 37 at (368, 137) + offset: page 0 alpha ramp(t, 95, 35), held to 160, 1 - (t - 160) / 20 to 180, then 0;
//         page 1 alpha 0 and the offset (98.5, -62.5) on the same schedule, (197, -125) from 32.
//   +1296 entry 37 again: page 0 a flash, 0 up to t = 144, then 1 - (t - 145) / 35 down to 0 at 180, times 0.4 (the
//         .sdata literal at 0x7CAD78); page 1 as +784.
//   +528  entry 17, the backdrop: page 0 the full screen {0, 0, 640, 448} with alpha ramp(t, 120, 100); page 1 alpha
//         1 - k with k = ramp(t, 0, 25), the full-screen quad zoomed about the centre by (1 + 1.5 k, 1 - 0.8 k) (0.8:
//         the .sdata literal at 0x7CB08C).
// Then the streaks: each emitter i counts its timer to its period; at the period it restarts with a new period
// 4 + (RpRandom() & 3) and lights the first free streak (bit 0 clear; K_Assert line 879 when all 9 run) with age 0
// and lane i. Every alive streak ages by one frame up to 12 (then it dies); lane 0 / 1 / 2 is the y 127 / 187 / 236,
// lane 1 runs right to left (x = 640 - 1840 age / 12), lanes 0 and 2 left to right (x = 1840 age / 12 - 1200); the
// strip is {x, y, 1000, 40} on page 0 and that quad zoomed like the backdrop on page 1, white with alpha 20.
void Cpu::sub_267430() {
    enter(16);
    sp = addiu(sp, -176);
    sd(ra, sp, 112);
    sq(s4, sp, 96);
    sq(s3, sp, 80);
    sq(s2, sp, 64);
    sq(s1, sp, 48);
    sq(s0, sp, 32);
    swc1(F25, sp, 20);
    swc1(F24, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    lw(v0, gp, kGpOpTitle);
    if (v0 == 0) {
        charge(5);
        kassert(0x26747Cu, kFileOpTitle, 142);
    }
    charge(12);
    lw(s1, gp, kGpOpTitle);
    a0 = 0;
    jal(0x26748Cu, gen::fn_sub_266C50_00266c50);
    s4 = v0;  // the title image
    v1 = lui(0x3F80);  // 1.0
    mtc1(v1, F20);  // the logo scale
    lw(a0, s1, 0);
    v1 = nor(a0, zero);
    v1 = v1 & 0x1;
    if (v1 == 0) {  // alive
        // The fade timer: up to 200 (page 0) / 512 (page 1) while showing, then showing ends.
        charge(3);
        v0 = a0 & 0x4;
        if (v0 != 0) {
            charge(4);
            lw(v1, s1, 8);
            v0 = 1;
            if (v1 != v0) {
                charge(2);
                if (v1 != 0) {
                    charge(2);
                } else {
                    charge(4);
                    lw(v0, s1, 4);
                    at = slti(v0, 200);
                    if (at != 0) {
                        charge(4);
                        v0 = addiu(v0, 1);
                        sw(v0, s1, 4);
                    } else {
                        charge(5);
                        v0 = si(-5);
                        v0 = a0 & v0;
                        sw(v0, s1, 0);
                    }
                }
            } else {
                charge(4);
                lw(v0, s1, 4);
                at = slti(v0, 512);
                if (at != 0) {
                    charge(4);
                    v0 = addiu(v0, 1);
                    sw(v0, s1, 4);
                } else {
                    charge(3);
                    v0 = si(-5);
                    v0 = a0 & v0;
                    sw(v0, s1, 0);
                }
            }
        }
        // Sprite +16 (image entry 14): the logo. Every sprite's block starts the same way: page 1, page 0, or any other
        // page (which keeps the previous sprite's alpha / offset registers).
        charge(4);
        lw(v1, s1, 8);
        v0 = 1;
        if (v1 != v0) {
            charge(2);
            if (v1 != 0) {
                charge(2);
            } else {
                charge(4);
                lw(v0, s1, 4);
                at = slti(v0, 70);
                if (at != 0) {
                    charge(3);
                    mtc1(zero, F23);
                } else {
                    charge(3);
                    at = slti(v0, 100);
                    if (at != 0) {
                        charge(13);
                        v0 = addiu(v0, -70);
                        mtc1(v0, F0);
                        cvt_s_w(F1, F0);
                        v0 = lui(0x41F0);  // 30.0
                        mtc1(v0, F0);
                        div_s(F23, F1, F0);
                    } else {
                        charge(2);
                        v0 = lui(0x3F80);  // 1.0
                        mtc1(v0, F23);
                    }
                }
                charge(5);
                mtc1(zero, F25);
                mov_s(F24, F25);
            }
        } else {
            charge(3);
            lw(v1, s1, 4);
            if (ltz(v1)) {
                charge(4);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F23);
            } else {
                charge(3);
                at = slti(v1, 10);
                if (at != 0) {
                    charge(13);
                    mtc1(v1, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x4120);  // 10.0
                    mtc1(v0, F0);
                    div_s(F1, F1, F0);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F0);
                    sub_s(F23, F0, F1);
                } else {
                    charge(3);
                    at = slti(v1, 12);
                    if (at != 0) {
                        charge(4);
                        lwc1(F20, gp, -31628);  // 0.787 (the .sdata literal at 0x7CB164)
                        mtc1(zero, F23);
                    } else {
                        charge(3);
                        at = slti(v1, 32);
                        if (at != 0) {
                            charge(14);
                            lwc1(F20, gp, -31628);  // 0.787 (the .sdata literal at 0x7CB164)
                            v0 = addiu(v1, -12);
                            mtc1(v0, F0);
                            cvt_s_w(F1, F0);
                            v0 = lui(0x41A0);  // 20.0
                            mtc1(v0, F0);
                            div_s(F23, F1, F0);
                        } else {
                            charge(3);
                            lwc1(F20, gp, -31628);  // 0.787 (the .sdata literal at 0x7CB164)
                            v0 = lui(0x3F80);  // 1.0
                            mtc1(v0, F23);
                        }
                    }
                }
            }
            charge(2);
            if (ltz(v1)) {
                charge(5);
                mtc1(zero, F25);
                mov_s(F24, F25);
            } else {
                charge(3);
                at = slti(v1, 10);
                if (at != 0) {
                    charge(17);
                    mtc1(v1, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x4120);  // 10.0
                    mtc1(v0, F0);
                    div_s(F1, F1, F0);
                    v0 = lui(0x42D9);  // 108.5
                    mtc1(v0, F0);
                    mul_s(F25, F0, F1);
                    v0 = lui(0xC272);  // -60.5
                    mtc1(v0, F0);
                    mul_s(F24, F0, F1);
                } else {
                    charge(3);
                    at = slti(v1, 12);
                    if (at != 0) {
                        charge(5);
                        mtc1(zero, F25);
                        mov_s(F24, F25);
                    } else {
                        charge(3);
                        at = slti(v1, 32);
                        if (at != 0) {
                            charge(21);
                            v0 = addiu(v1, -12);
                            mtc1(v0, F0);
                            cvt_s_w(F1, F0);
                            v0 = lui(0x41A0);  // 20.0
                            mtc1(v0, F0);
                            div_s(F2, F1, F0);
                            v0 = lui(0x42D9);  // 108.5
                            mtc1(v0, F0);
                            mtc1(zero, F1);
                            adda_s(F1, F0);
                            madd_s(F25, F0, F2);
                            v0 = lui(0xC272);  // -60.5
                            mtc1(v0, F0);
                            adda_s(F1, F0);
                            madd_s(F24, F0, F2);
                        } else {
                            charge(4);
                            v0 = lui(0x4359);  // 217.0
                            mtc1(v0, F25);
                            v0 = lui(0xC2F2);  // -121.0
                            mtc1(v0, F24);
                        }
                    }
                }
            }
        }
        charge(40);
        a0 = s4;
        a1 = 14;
        jal(0x2677A4u, gen::fn_sub_21CCA0_0021cca0);
        v1 = lui(0x433C);  // 188.0
        mtc1(v1, F0);
        add_s(F0, F0, F25);
        swc1(F0, sp, 128);
        v1 = lui(0x4310);  // 144.0
        mtc1(v1, F0);
        add_s(F0, F0, F24);
        swc1(F0, sp, 132);
        lwc1(F0, v0, 12);
        cvt_s_w(F0, F0);
        mul_s(F0, F0, F20);
        swc1(F0, sp, 136);
        lwc1(F0, v0, 16);
        cvt_s_w(F0, F0);
        mul_s(F0, F0, F20);
        swc1(F0, sp, 140);
        a0 = addiu(s1, 16);
        a1 = addiu(sp, 128);
        jal(0x2677FCu, gen::fn_sub_21D8E0_0021d8e0);
        white_alpha(172, F23);
        charge(9);
        sb(v1, sp, 175);
        a0 = addiu(s1, 16);
        a1 = addiu(sp, 172);
        jal(0x267878u, gen::fn_sub_21D950_0021d950);
        // Sprite +272 (image entry 13).
        lw(v1, s1, 8);
        v0 = 1;
        if (v1 != v0) {
            charge(2);
            if (v1 != 0) {
                charge(2);
            } else {
                charge(4);
                lw(v0, s1, 4);
                at = slti(v0, 70);
                if (at != 0) {
                    charge(3);
                    mtc1(zero, F23);
                } else {
                    charge(3);
                    at = slti(v0, 100);
                    if (at != 0) {
                        charge(13);
                        v0 = addiu(v0, -70);
                        mtc1(v0, F0);
                        cvt_s_w(F1, F0);
                        v0 = lui(0x41F0);  // 30.0
                        mtc1(v0, F0);
                        div_s(F23, F1, F0);
                    } else {
                        charge(2);
                        v0 = lui(0x3F80);  // 1.0
                        mtc1(v0, F23);
                    }
                }
                charge(2);
            }
        } else {
            charge(3);
            lw(v1, s1, 4);
            if (ltz(v1)) {
                charge(4);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F23);
            } else {
                charge(3);
                at = slti(v1, 10);
                if (at != 0) {
                    charge(13);
                    mtc1(v1, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x4120);  // 10.0
                    mtc1(v0, F0);
                    div_s(F1, F1, F0);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F0);
                    sub_s(F23, F0, F1);
                } else {
                    charge(3);
                    at = slti(v1, 12);
                    if (at != 0) {
                        charge(4);
                        mtc1(zero, F23);
                        lwc1(F20, gp, -31628);  // 0.787 (the .sdata literal at 0x7CB164)
                    } else {
                        charge(3);
                        at = slti(v1, 32);
                        if (at != 0) {
                            charge(14);
                            lwc1(F20, gp, -31628);  // 0.787 (the .sdata literal at 0x7CB164)
                            v0 = addiu(v1, -12);
                            mtc1(v0, F0);
                            cvt_s_w(F1, F0);
                            v0 = lui(0x41A0);  // 20.0
                            mtc1(v0, F0);
                            div_s(F23, F1, F0);
                        } else {
                            charge(3);
                            lwc1(F20, gp, -31628);  // 0.787 (the .sdata literal at 0x7CB164)
                            v0 = lui(0x3F80);  // 1.0
                            mtc1(v0, F23);
                        }
                    }
                }
            }
            charge(33);
            v0 = lui(0x4100);  // 8.0
            mtc1(v0, F1);
            v0 = 405;
            mtc1(v0, F0);
            cvt_s_w(F0, F0);
            mtc1(zero, F24);
            adda_s(F24, F0);
            msub_s(F2, F1, F20);
            v0 = lui(0xC100);  // -8.0
            mtc1(v0, F1);
            v0 = lui(0x433C);  // 188.0
            mtc1(v0, F0);
            adda_s(F24, F0);
            madd_s(F0, F1, F20);
            sub_s(F25, F2, F0);
            v0 = lui(0x42A8);  // 84.0
            mtc1(v0, F0);
            mul_s(F2, F0, F20);
            v0 = lui(0x41B8);  // 23.0
            mtc1(v0, F0);
            add_s(F1, F0, F2);
            v0 = lui(0x4310);  // 144.0
            mtc1(v0, F0);
            add_s(F0, F0, F2);
            sub_s(F3, F1, F0);
            if (ltz(v1)) {
                charge(3);
                mov_s(F25, F24);
            } else {
                charge(3);
                at = slti(v1, 10);
                if (at != 0) {
                    charge(18);
                    mtc1(v1, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x4120);  // 10.0
                    mtc1(v0, F0);
                    div_s(F2, F1, F0);
                    v0 = lui(0x4000);  // 2.0
                    mtc1(v0, F1);
                    div_s(F0, F25, F1);
                    mul_s(F25, F0, F2);
                    div_s(F0, F3, F1);
                    mul_s(F24, F0, F2);
                } else {
                    charge(3);
                    at = slti(v1, 12);
                    if (at != 0) {
                        charge(3);
                        mov_s(F25, F24);
                    } else {
                        charge(3);
                        at = slti(v1, 32);
                        if (at != 0) {
                            charge(20);
                            v0 = addiu(v1, -12);
                            mtc1(v0, F0);
                            cvt_s_w(F1, F0);
                            v0 = lui(0x41A0);  // 20.0
                            mtc1(v0, F0);
                            div_s(F2, F1, F0);
                            v0 = lui(0x4000);  // 2.0
                            mtc1(v0, F1);
                            div_s(F0, F25, F1);
                            adda_s(F24, F0);
                            madd_s(F25, F0, F2);
                            div_s(F0, F3, F1);
                            adda_s(F24, F0);
                            madd_s(F24, F0, F2);
                        } else {
                            charge(1);
                            mov_s(F24, F3);
                        }
                    }
                }
            }
        }
        charge(49);
        a0 = s4;
        a1 = 13;
        jal(0x267B38u, gen::fn_sub_21CCA0_0021cca0);
        v1 = lui(0xC100);  // -8.0
        mtc1(v1, F1);
        v1 = lui(0x433C);  // 188.0
        mtc1(v1, F0);
        mtc1(zero, F2);
        adda_s(F2, F0);
        madd_s(F0, F1, F20);
        add_s(F0, F0, F25);
        swc1(F0, sp, 128);
        v1 = lui(0x42A8);  // 84.0
        mtc1(v1, F1);
        v1 = lui(0x4310);  // 144.0
        mtc1(v1, F0);
        adda_s(F2, F0);
        madd_s(F0, F1, F20);
        add_s(F0, F0, F24);
        swc1(F0, sp, 132);
        lwc1(F0, v0, 12);
        cvt_s_w(F0, F0);
        mul_s(F0, F0, F20);
        swc1(F0, sp, 136);
        lwc1(F0, v0, 16);
        cvt_s_w(F0, F0);
        mul_s(F0, F0, F20);
        swc1(F0, sp, 140);
        a0 = addiu(s1, 272);
        a1 = addiu(sp, 128);
        jal(0x267BB4u, gen::fn_sub_21D8E0_0021d8e0);
        white_alpha(172, F23);
        charge(9);
        sb(v1, sp, 175);
        a0 = addiu(s1, 272);
        a1 = addiu(sp, 172);
        jal(0x267C30u, gen::fn_sub_21D950_0021d950);
        // Sprite +1040 (image entry 36).
        lw(v1, s1, 8);
        v0 = 1;
        if (v1 != v0) {
            charge(2);
            if (v1 != 0) {
                charge(2);
            } else {
                charge(4);
                lw(v0, s1, 4);
                at = slti(v0, 120);
                if (at != 0) {
                    charge(3);
                    mtc1(zero, F23);
                } else {
                    charge(3);
                    at = slti(v0, 165);
                    if (at != 0) {
                        charge(13);
                        v0 = addiu(v0, -120);
                        mtc1(v0, F0);
                        cvt_s_w(F1, F0);
                        v0 = lui(0x4234);  // 45.0
                        mtc1(v0, F0);
                        div_s(F23, F1, F0);
                    } else {
                        charge(2);
                        v0 = lui(0x3F80);  // 1.0
                        mtc1(v0, F23);
                    }
                }
                charge(2);
            }
        } else {
            charge(3);
            lw(v1, s1, 4);
            if (ltz(v1)) {
                charge(4);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F23);
            } else {
                charge(3);
                at = slti(v1, 10);
                if (at != 0) {
                    charge(13);
                    mtc1(v1, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x4120);  // 10.0
                    mtc1(v0, F0);
                    div_s(F1, F1, F0);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F0);
                    sub_s(F23, F0, F1);
                } else {
                    charge(3);
                    at = slti(v1, 12);
                    if (at != 0) {
                        charge(4);
                        mtc1(zero, F23);
                        lwc1(F20, gp, -31628);  // 0.787 (the .sdata literal at 0x7CB164)
                    } else {
                        charge(3);
                        at = slti(v1, 32);
                        if (at != 0) {
                            charge(13);
                            v0 = addiu(v1, -12);
                            mtc1(v0, F0);
                            cvt_s_w(F1, F0);
                            v0 = lui(0x41A0);  // 20.0
                            mtc1(v0, F0);
                            div_s(F23, F1, F0);
                            lwc1(F20, gp, -31628);  // 0.787 (the .sdata literal at 0x7CB164)
                        } else {
                            charge(3);
                            lwc1(F20, gp, -31628);  // 0.787 (the .sdata literal at 0x7CB164)
                            v0 = lui(0x3F80);  // 1.0
                            mtc1(v0, F23);
                        }
                    }
                }
            }
            charge(32);
            v0 = lui(0x4336);  // 182.0
            mtc1(v0, F0);
            mul_s(F2, F0, F20);
            v0 = 405;
            mtc1(v0, F0);
            cvt_s_w(F0, F0);
            add_s(F1, F0, F2);
            v0 = lui(0x433C);  // 188.0
            mtc1(v0, F0);
            add_s(F0, F0, F2);
            sub_s(F25, F1, F0);
            v0 = lui(0x40C0);  // 6.0
            mtc1(v0, F1);
            v0 = lui(0x41B8);  // 23.0
            mtc1(v0, F0);
            mtc1(zero, F24);
            adda_s(F24, F0);
            msub_s(F2, F1, F20);
            v0 = lui(0xC0C0);  // -6.0
            mtc1(v0, F1);
            v0 = lui(0x4310);  // 144.0
            mtc1(v0, F0);
            adda_s(F24, F0);
            madd_s(F0, F1, F20);
            sub_s(F3, F2, F0);
            if (ltz(v1)) {
                charge(3);
                mov_s(F25, F24);
            } else {
                charge(3);
                at = slti(v1, 10);
                if (at != 0) {
                    charge(18);
                    mtc1(v1, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x4120);  // 10.0
                    mtc1(v0, F0);
                    div_s(F2, F1, F0);
                    v0 = lui(0x4000);  // 2.0
                    mtc1(v0, F1);
                    div_s(F0, F25, F1);
                    mul_s(F25, F0, F2);
                    div_s(F0, F3, F1);
                    mul_s(F24, F0, F2);
                } else {
                    charge(3);
                    at = slti(v1, 12);
                    if (at != 0) {
                        charge(3);
                        mov_s(F25, F24);
                    } else {
                        charge(3);
                        at = slti(v1, 32);
                        if (at != 0) {
                            charge(20);
                            v0 = addiu(v1, -12);
                            mtc1(v0, F0);
                            cvt_s_w(F1, F0);
                            v0 = lui(0x41A0);  // 20.0
                            mtc1(v0, F0);
                            div_s(F2, F1, F0);
                            v0 = lui(0x4000);  // 2.0
                            mtc1(v0, F1);
                            div_s(F0, F25, F1);
                            adda_s(F24, F0);
                            madd_s(F25, F0, F2);
                            div_s(F0, F3, F1);
                            adda_s(F24, F0);
                            madd_s(F24, F0, F2);
                        } else {
                            charge(1);
                            mov_s(F24, F3);
                        }
                    }
                }
            }
        }
        charge(49);
        a0 = s4;
        a1 = 36;
        jal(0x267EE8u, gen::fn_sub_21CCA0_0021cca0);
        v1 = lui(0x4336);  // 182.0
        mtc1(v1, F1);
        v1 = lui(0x433C);  // 188.0
        mtc1(v1, F0);
        mtc1(zero, F2);
        adda_s(F2, F0);
        madd_s(F0, F1, F20);
        add_s(F0, F0, F25);
        swc1(F0, sp, 128);
        v1 = lui(0xC0C0);  // -6.0
        mtc1(v1, F1);
        v1 = lui(0x4310);  // 144.0
        mtc1(v1, F0);
        adda_s(F2, F0);
        madd_s(F0, F1, F20);
        add_s(F0, F0, F24);
        swc1(F0, sp, 132);
        lwc1(F0, v0, 12);
        cvt_s_w(F0, F0);
        mul_s(F0, F0, F20);
        swc1(F0, sp, 136);
        lwc1(F0, v0, 16);
        cvt_s_w(F0, F0);
        mul_s(F0, F0, F20);
        swc1(F0, sp, 140);
        a0 = addiu(s1, 1040);
        a1 = addiu(sp, 128);
        jal(0x267F64u, gen::fn_sub_21D8E0_0021d8e0);
        white_alpha(172, F23);
        charge(9);
        sb(v1, sp, 175);
        a0 = addiu(s1, 1040);
        a1 = addiu(sp, 172);
        jal(0x267FE0u, gen::fn_sub_21D950_0021d950);
        // Sprite +784 (image entry 37).
        lw(v1, s1, 8);
        v0 = 1;
        if (v1 != v0) {
            charge(2);
            if (v1 != 0) {
                charge(2);
            } else {
                charge(4);
                lw(v0, s1, 4);
                at = slti(v0, 95);
                if (at != 0) {
                    charge(3);
                    mtc1(zero, F23);
                } else {
                    charge(3);
                    at = slti(v0, 130);
                    if (at != 0) {
                        charge(13);
                        v0 = addiu(v0, -95);
                        mtc1(v0, F0);
                        cvt_s_w(F1, F0);
                        v0 = lui(0x420C);  // 35.0
                        mtc1(v0, F0);
                        div_s(F23, F1, F0);
                    } else {
                        charge(3);
                        at = slti(v0, 160);
                        if (at != 0) {
                            charge(4);
                            v0 = lui(0x3F80);  // 1.0
                            mtc1(v0, F23);
                        } else {
                            charge(3);
                            at = slti(v0, 180);
                            if (at != 0) {
                                charge(14);
                                v0 = addiu(v0, -160);
                                mtc1(v0, F0);
                                cvt_s_w(F1, F0);
                                v0 = lui(0x41A0);  // 20.0
                                mtc1(v0, F0);
                                div_s(F1, F1, F0);
                                v0 = lui(0x3F80);  // 1.0
                                mtc1(v0, F0);
                                sub_s(F23, F0, F1);
                            } else {
                                charge(1);
                                mtc1(zero, F23);
                            }
                        }
                    }
                }
                charge(2);
            }
        } else {
            charge(3);
            lw(v0, s1, 4);
            if (ltz(v0)) {
                charge(3);
                mtc1(zero, F23);
            } else {
                charge(3);
                at = slti(v0, 10);
                if (at != 0) {
                    charge(3);
                    mtc1(zero, F23);
                } else {
                    charge(3);
                    at = slti(v0, 12);
                    if (at != 0) {
                        charge(3);
                        mtc1(zero, F23);
                    } else {
                        charge(3);
                        at = slti(v0, 32);
                        if (at != 0) {
                            charge(3);
                            mtc1(zero, F23);
                        } else {
                            charge(1);
                            mtc1(zero, F23);
                        }
                    }
                }
            }
            charge(2);
            if (ltz(v0)) {
                charge(5);
                mtc1(zero, F25);
                mov_s(F24, F25);
            } else {
                charge(3);
                at = slti(v0, 10);
                if (at != 0) {
                    charge(17);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x4120);  // 10.0
                    mtc1(v0, F0);
                    div_s(F1, F1, F0);
                    v0 = lui(0x42C5);  // 98.5
                    mtc1(v0, F0);
                    mul_s(F25, F0, F1);
                    v0 = lui(0xC27A);  // -62.5
                    mtc1(v0, F0);
                    mul_s(F24, F0, F1);
                } else {
                    charge(3);
                    at = slti(v0, 12);
                    if (at != 0) {
                        charge(5);
                        mtc1(zero, F25);
                        mov_s(F24, F25);
                    } else {
                        charge(3);
                        at = slti(v0, 32);
                        if (at != 0) {
                            charge(21);
                            v0 = addiu(v0, -12);
                            mtc1(v0, F0);
                            cvt_s_w(F1, F0);
                            v0 = lui(0x41A0);  // 20.0
                            mtc1(v0, F0);
                            div_s(F2, F1, F0);
                            v0 = lui(0x42C5);  // 98.5
                            mtc1(v0, F0);
                            mtc1(zero, F1);
                            adda_s(F1, F0);
                            madd_s(F25, F0, F2);
                            v0 = lui(0xC27A);  // -62.5
                            mtc1(v0, F0);
                            adda_s(F1, F0);
                            madd_s(F24, F0, F2);
                        } else {
                            charge(4);
                            v0 = lui(0x4345);  // 197.0
                            mtc1(v0, F25);
                            v0 = lui(0xC2FA);  // -125.0
                            mtc1(v0, F24);
                        }
                    }
                }
            }
        }
        charge(38);
        a0 = s4;
        a1 = 37;
        jal(0x268238u, gen::fn_sub_21CCA0_0021cca0);
        v1 = lui(0x43B8);  // 368.0
        mtc1(v1, F0);
        add_s(F0, F0, F25);
        swc1(F0, sp, 128);
        v1 = lui(0x4309);  // 137.0
        mtc1(v1, F0);
        add_s(F0, F0, F24);
        swc1(F0, sp, 132);
        lwc1(F0, v0, 12);
        cvt_s_w(F0, F0);
        swc1(F0, sp, 136);
        lwc1(F0, v0, 16);
        cvt_s_w(F0, F0);
        swc1(F0, sp, 140);
        a0 = addiu(s1, 784);
        a1 = addiu(sp, 128);
        jal(0x268288u, gen::fn_sub_21D8E0_0021d8e0);
        white_alpha(172, F23);
        charge(9);
        sb(v1, sp, 175);
        a0 = addiu(s1, 784);
        a1 = addiu(sp, 172);
        jal(0x268304u, gen::fn_sub_21D950_0021d950);
        // Sprite +1296 (image entry 37): the flash.
        lw(v1, s1, 8);
        v0 = 1;
        if (v1 != v0) {
            charge(2);
            if (v1 != 0) {
                charge(2);
            } else {
                charge(4);
                lw(v0, s1, 4);
                at = slti(v0, 144);
                if (at != 0) {
                    charge(3);
                    mtc1(zero, F1);
                } else {
                    charge(3);
                    at = slti(v0, 145);
                    if (at != 0) {
                        charge(6);
                        v0 = addiu(v0, -144);
                        mtc1(v0, F0);
                        cvt_s_w(F1, F0);
                    } else {
                        charge(3);
                        at = slti(v0, 180);
                        if (at != 0) {
                            charge(14);
                            v0 = addiu(v0, -145);
                            mtc1(v0, F0);
                            cvt_s_w(F1, F0);
                            v0 = lui(0x420C);  // 35.0
                            mtc1(v0, F0);
                            div_s(F1, F1, F0);
                            v0 = lui(0x3F80);  // 1.0
                            mtc1(v0, F0);
                            sub_s(F1, F0, F1);
                        } else {
                            charge(1);
                            mtc1(zero, F1);
                        }
                    }
                }
                charge(4);
                lwc1(F0, gp, -32632);  // 0.4 (the .sdata literal at 0x7CAD78)
                mul_s(F23, F1, F0);
            }
        } else {
            charge(3);
            lw(v0, s1, 4);
            if (ltz(v0)) {
                charge(3);
                mtc1(zero, F23);
            } else {
                charge(3);
                at = slti(v0, 10);
                if (at != 0) {
                    charge(3);
                    mtc1(zero, F23);
                } else {
                    charge(3);
                    at = slti(v0, 12);
                    if (at != 0) {
                        charge(3);
                        mtc1(zero, F23);
                    } else {
                        charge(3);
                        at = slti(v0, 32);
                        if (at != 0) {
                            charge(3);
                            mtc1(zero, F23);
                        } else {
                            charge(1);
                            mtc1(zero, F23);
                        }
                    }
                }
            }
            charge(2);
            if (ltz(v0)) {
                charge(5);
                mtc1(zero, F25);
                mov_s(F24, F25);
            } else {
                charge(3);
                at = slti(v0, 10);
                if (at != 0) {
                    charge(17);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x4120);  // 10.0
                    mtc1(v0, F0);
                    div_s(F1, F1, F0);
                    v0 = lui(0x42C5);  // 98.5
                    mtc1(v0, F0);
                    mul_s(F25, F0, F1);
                    v0 = lui(0xC27A);  // -62.5
                    mtc1(v0, F0);
                    mul_s(F24, F0, F1);
                } else {
                    charge(3);
                    at = slti(v0, 12);
                    if (at != 0) {
                        charge(5);
                        mtc1(zero, F25);
                        mov_s(F24, F25);
                    } else {
                        charge(3);
                        at = slti(v0, 32);
                        if (at != 0) {
                            charge(21);
                            v0 = addiu(v0, -12);
                            mtc1(v0, F0);
                            cvt_s_w(F1, F0);
                            v0 = lui(0x41A0);  // 20.0
                            mtc1(v0, F0);
                            div_s(F2, F1, F0);
                            v0 = lui(0x42C5);  // 98.5
                            mtc1(v0, F0);
                            mtc1(zero, F1);
                            adda_s(F1, F0);
                            madd_s(F25, F0, F2);
                            v0 = lui(0xC27A);  // -62.5
                            mtc1(v0, F0);
                            adda_s(F1, F0);
                            madd_s(F24, F0, F2);
                        } else {
                            charge(4);
                            v0 = lui(0x4345);  // 197.0
                            mtc1(v0, F25);
                            v0 = lui(0xC2FA);  // -125.0
                            mtc1(v0, F24);
                        }
                    }
                }
            }
        }
        charge(38);
        a0 = s4;
        a1 = 37;
        jal(0x26852Cu, gen::fn_sub_21CCA0_0021cca0);
        v1 = lui(0x43B8);  // 368.0
        mtc1(v1, F0);
        add_s(F0, F0, F25);
        swc1(F0, sp, 128);
        v1 = lui(0x4309);  // 137.0
        mtc1(v1, F0);
        add_s(F0, F0, F24);
        swc1(F0, sp, 132);
        lwc1(F0, v0, 12);
        cvt_s_w(F0, F0);
        swc1(F0, sp, 136);
        lwc1(F0, v0, 16);
        cvt_s_w(F0, F0);
        swc1(F0, sp, 140);
        a0 = addiu(s1, 1296);
        a1 = addiu(sp, 128);
        jal(0x26857Cu, gen::fn_sub_21D8E0_0021d8e0);
        white_alpha(172, F23);
        charge(9);
        sb(v1, sp, 175);
        a0 = addiu(s1, 1296);
        a1 = addiu(sp, 172);
        jal(0x2685F8u, gen::fn_sub_21D950_0021d950);
        // Sprite +528 (image entry 17): the backdrop.
        lw(v1, s1, 8);
        v0 = 1;
        if (v1 != v0) {
            charge(2);
            if (v1 != 0) {
                charge(2);
            } else {
                charge(4);
                lw(v0, s1, 4);
                at = slti(v0, 120);
                if (at != 0) {
                    charge(3);
                    mtc1(zero, F23);
                } else {
                    charge(3);
                    at = slti(v0, 220);
                    if (at != 0) {
                        charge(13);
                        v0 = addiu(v0, -120);
                        mtc1(v0, F0);
                        cvt_s_w(F1, F0);
                        v0 = lui(0x42C8);  // 100.0
                        mtc1(v0, F0);
                        div_s(F23, F1, F0);
                    } else {
                        charge(2);
                        v0 = lui(0x3F80);  // 1.0
                        mtc1(v0, F23);
                    }
                }
                charge(16);
                a0 = s4;
                a1 = 17;
                jal(0x26868Cu, gen::fn_sub_21CCA0_0021cca0);
                sw(zero, sp, 128);
                sw(zero, sp, 132);
                v0 = lui(0x4420);
                sw(v0, sp, 136);
                v0 = lui(0x43E0);
                sw(v0, sp, 140);
                a0 = addiu(s1, 528);
                a1 = addiu(sp, 128);
                jal(0x2686B4u, gen::fn_sub_21D8E0_0021d8e0);
            }
        } else {
            charge(3);
            lw(v1, s1, 4);
            if (ltz(v1)) {
                charge(3);
                mtc1(zero, F0);
            } else {
                charge(3);
                at = slti(v1, 25);
                if (at != 0) {
                    charge(12);
                    mtc1(v1, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x41C8);  // 25.0
                    mtc1(v0, F0);
                    div_s(F0, F1, F0);
                } else {
                    charge(2);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F0);
                }
            }
            charge(6);
            v0 = lui(0x3F80);  // 1.0
            mtc1(v0, F3);
            sub_s(F23, F3, F0);
            if (ltz(v1)) {
                charge(3);
                mtc1(zero, F3);
            } else {
                charge(3);
                at = slti(v1, 25);
                if (at != 0) {
                    charge(10);
                    mtc1(v1, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x41C8);  // 25.0
                    mtc1(v0, F0);
                    div_s(F3, F1, F0);
                }
            }
            charge(28);
            v0 = lui(0x3FC0);  // 1.5
            mtc1(v0, F0);
            v0 = lui(0x3F80);  // 1.0
            mtc1(v0, F2);
            mtc1(zero, F1);
            adda_s(F1, F2);
            madd_s(F22, F0, F3);
            lwc1(F0, gp, -31844);  // 0.8 (the .sdata literal at 0x7CB08C)
            adda_s(F1, F2);
            msub_s(F21, F0, F3);
            sw(zero, sp, 128);
            sw(zero, sp, 132);
            v0 = lui(0x4420);
            sw(v0, sp, 136);
            sw(zero, sp, 140);
            sw(v0, sp, 144);
            v0 = lui(0x43E0);
            sw(v0, sp, 148);
            sw(zero, sp, 152);
            sw(v0, sp, 156);
            scale_quad_about_centre();
            charge(4);
            a0 = addiu(s1, 528);
            a1 = addiu(sp, 128);
            jal(0x2688B4u, gen::fn_sub_21D890_0021d890);
        }
        charge(18);
        a0 = s4;
        a1 = 17;
        jal(0x2688C4u, gen::fn_sub_21CCA0_0021cca0);
        white_alpha(172, F23);
        charge(8);
        sb(v1, sp, 175);
        a0 = addiu(s1, 528);
        a1 = addiu(sp, 172);
        jal(0x268940u, gen::fn_sub_21D950_0021d950);
        // The three streak emitters (+4148 + 8 i: the period, +4152 + 8 i: the timer).
        s2 = 0;
        for (;;) {
            charge(3);
            v0 = slti(s2, 3);
            if (v0 == 0) break;
            backedge();
            charge(8);
            v0 = sll(s2, 3);
            v0 = addu(s1, v0);
            s0 = addiu(v0, 4148);
            lw(v1, v0, 4152);
            lw(v0, v0, 4148);
            at = slt(v1, v0);
            if (at != 0) {
                charge(4);
                v0 = addiu(v1, 1);
                sw(v0, s0, 4);
            } else {
                charge(9);
                sw(zero, s0, 4);
                jal(0x268988u, gen::fn_sub_488F30_00488f30);
                v0 = v0 & 0x3;
                v0 = addiu(v0, 4);
                sw(v0, s0, 0);
                v1 = 0;
                for (;;) {
                    charge(3);
                    v0 = slti(v1, 9);
                    if (v0 == 0) break;
                    backedge();
                    charge(10);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 5);
                    v0 = addu(s1, v0);
                    s3 = addiu(v0, 1552);
                    lw(v0, v0, 1552);
                    v0 = nor(v0, zero);
                    v0 = v0 & 0x1;
                    if (v0 != 0) break;
                    charge(1);
                    v1 = addiu(v1, 1);
                }
                charge(3);
                v0 = slti(v1, 9);
                if (v0 == 0) {
                    charge(5);
                    kassert(0x2689F8u, kFileOpTitle, 879);
                }
                charge(5);
                lw(v0, s3, 0);
                v0 = v0 | 0x1;
                sw(v0, s3, 0);
                sw(zero, s3, 272);
                sw(s2, s3, 276);
            }
            charge(1);
            s2 = addiu(s2, 1);
        }
        charge(4);
        lw(v1, s1, 8);
        v0 = 1;
        if (v1 != v0) {
            charge(2);
        } else {
            charge(3);
            lw(v0, s1, 4);
            if (ltz(v0)) {
                charge(3);
                mtc1(zero, F3);
            } else {
                charge(3);
                at = slti(v0, 25);
                if (at != 0) {
                    charge(12);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x41C8);  // 25.0
                    mtc1(v0, F0);
                    div_s(F3, F1, F0);
                } else {
                    charge(2);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F3);
                }
            }
            charge(11);
            v0 = lui(0x3FC0);  // 1.5
            mtc1(v0, F0);
            v0 = lui(0x3F80);  // 1.0
            mtc1(v0, F2);
            mtc1(zero, F1);
            adda_s(F1, F2);
            madd_s(F22, F0, F3);
            lwc1(F0, gp, -31844);  // 0.8 (the .sdata literal at 0x7CB08C)
            adda_s(F1, F2);
            msub_s(F21, F0, F3);
        }
        charge(7);
        // The streaks (image entry 15 is looked up and not used).
        a0 = s4;
        a1 = 15;
        jal(0x268ACCu, gen::fn_sub_21CCA0_0021cca0);
        s2 = 0;
        for (;;) {
            charge(3);
            v1 = slti(s2, 9);
            if (v1 == 0) break;
            backedge();
            charge(10);
            v1 = sll(s2, 3);
            v1 = addu(v1, s2);
            v1 = sll(v1, 5);
            v1 = addu(s1, v1);
            s0 = addiu(v1, 1552);
            lw(a0, v1, 1552);
            v1 = nor(a0, zero);
            v1 = v1 & 0x1;
            if (v1 == 0) {
                charge(4);
                lw(v1, s0, 272);
                at = slti(v1, 12);
                if (at == 0) {  // 12 frames old: it dies
                    charge(5);
                    v1 = si(-2);
                    v1 = a0 & v1;
                    sw(v1, s0, 0);
                } else {
                    charge(4);
                    v0 = addiu(v1, 1);
                    sw(v0, s0, 272);
                    // The lane: its y, and x by the age (lane 1 right to left, lanes 0 / 2 left to right).
                    charge(4);
                    lw(v1, s0, 276);
                    v0 = 2;
                    if (v1 != v0) {
                        charge(3);
                        v0 = 1;
                        if (v1 != v0) {
                            charge(2);
                            if (v1 != 0) {
                                charge(2);
                            } else {
                                charge(4);
                                v0 = lui(0x42FE);  // 127.0
                                mtc1(v0, F24);
                            }
                        } else {
                            charge(4);
                            v0 = lui(0x433B);  // 187.0
                            mtc1(v0, F24);
                        }
                    } else {
                        charge(2);
                        v0 = lui(0x436C);  // 236.0
                        mtc1(v0, F24);
                    }
                    charge(11);
                    lwc1(F0, s0, 272);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x4140);  // 12.0
                    mtc1(v0, F0);
                    div_s(F3, F1, F0);
                    v0 = 1;
                    if (v1 == v0) {  // lane 1
                        charge(8);
                        v0 = lui(0xC4E6);  // -1840.0
                        mtc1(v0, F2);
                        v0 = lui(0x4420);  // 640.0
                        mtc1(v0, F1);
                        mtc1(zero, F0);
                        adda_s(F0, F1);
                        madd_s(F25, F2, F3);
                    } else {
                        charge(3);
                        v0 = 2;
                        bool right = v1 == v0;
                        if (!right) {
                            charge(2);
                            right = v1 == 0;
                            if (!right) charge(2);  // another lane: x keeps $f25
                        }
                        if (right) {  // lanes 0 / 2
                            charge(10);
                            v0 = lui(0x44E6);  // 1840.0
                            mtc1(v0, F0);
                            mul_s(F1, F0, F3);
                            v0 = lui(0x4496);  // 1200.0
                            mtc1(v0, F0);
                            sub_s(F25, F1, F0);
                        }
                    }
                    charge(4);
                    lw(v1, s1, 8);
                    v0 = 1;
                    if (v1 != v0) {
                        charge(2);
                        if (v1 != 0) {
                            charge(2);
                        } else {
                            charge(12);
                            swc1(F25, sp, 128);
                            swc1(F24, sp, 132);
                            v0 = lui(0x447A);
                            sw(v0, sp, 136);
                            v0 = lui(0x4220);
                            sw(v0, sp, 140);
                            a0 = addiu(s0, 16);
                            a1 = addiu(sp, 128);
                            jal(0x268C60u, gen::fn_sub_21D8E0_0021d8e0);
                        }
                    } else {
                        charge(23);
                        swc1(F25, sp, 128);
                        swc1(F24, sp, 132);
                        v0 = lui(0x447A);  // 1000.0
                        mtc1(v0, F0);
                        add_s(F0, F25, F0);
                        swc1(F0, sp, 136);
                        swc1(F24, sp, 140);
                        swc1(F0, sp, 144);
                        v0 = lui(0x4220);  // 40.0
                        mtc1(v0, F0);
                        add_s(F0, F24, F0);
                        swc1(F0, sp, 148);
                        swc1(F25, sp, 152);
                        swc1(F0, sp, 156);
                        scale_quad_about_centre();
                        charge(4);
                        a0 = addiu(s0, 16);
                        a1 = addiu(sp, 128);
                        jal(0x268D98u, gen::fn_sub_21D890_0021d890);
                    }
                    charge(10);
                    v0 = 255;
                    sb(v0, sp, 172);
                    sb(v0, sp, 173);
                    sb(v0, sp, 174);
                    v0 = 20;
                    sb(v0, sp, 175);
                    a0 = addiu(s0, 16);
                    a1 = addiu(sp, 172);
                    jal(0x268DC0u, gen::fn_sub_21D950_0021d950);
                }
            }
            charge(1);
            s2 = addiu(s2, 1);
        }
    }
    charge(15);
    ld(ra, sp, 112);
    lq(s4, sp, 96);
    lq(s3, sp, 80);
    lq(s2, sp, 64);
    lq(s1, sp, 48);
    lq(s0, sp, 32);
    lwc1(F25, sp, 20);
    lwc1(F24, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 176);
    return;
}

// =====================================================================================================================
// op_menu.c (work gp-18748: +0 flags (bit 0 alive, bit 2 showing, bit 3 the opening counter runs, bit 5 the title list,
// else the continue list), +16 .. +2336 the background sprites, +2320 / +2324 / +2328 / +2784 / +2788 / +2792 / +2796 /
// +2800 the background counters, +2804 the opening counter, +2332 the menu timer, +2808 the title list's cursor, +2816
// 4 title items of 784 bytes (+0 the state, +4 the highlight timer, +16 / +272 / +528 three sprites), +5952 the
// continue panel, +6736 the continue list's cursor, +6752 2 continue items).
// =====================================================================================================================
//
// 0x26A2C0 opMenuUpdate: one frame of the title menu. Asserts the work (line 135); s1 = the work, s4 = the title image.
// Nothing more while flags bit 0 is clear. Otherwise:
//   * the counters step: +2320 mod 1300, +2324 mod 500, +2328 / +2788 / +2792 / +2800 / +2796 mod 150, +2784 mod 80
//     (each `(c + 1) % n` through the integer divide); +2804 counts to 40, then flags bit 3 is cleared; while showing
//     (bit 2) the menu timer +2332 counts to 80, then bit 2 is cleared;
//   * the list's items (bit 5: the 4 title items and the continue panel, else the 2 continue items): each item's state
//     +0 counts up to 8; every item but the cursor's counts its highlight timer +4 up to 16;
//   * the background, a = ramp(timer, 0, 70) (0 for a negative timer): +16 the full screen with alpha a; +272 / +528 a
//     1280-wide band scrolling right by +2320 (x = -320 - 1100 (1 - c / 1300), the second copy 1100 to its right) with
//     alpha 255 (0.45 + 0.25 sin(2 pi c2324 / 500)) (0.45: the .sdata literal at 0x7CAD54); +784 / +1040 full-screen
//     quads swaying about the centre (rotated by 2 pi * 1.5 sin(2 pi c / 150) / 360 of +2792, and of +2800 + 0.2 period,
//     zoomed 1.1, and 1.1 growing to 1.3 while +2796 runs 65..95); +1296 / +1552 one more (25 degrees of sway on
//     +2788 + 0.2, zoomed 1.7 + 0.25 sin(2 pi c2784 / 80)) with alpha 255 / 153 times the fade (+1552 blinking with
//     +2796); +1808 / +2064 the full screen fading in over
//     the timer (alpha 204 ramp(timer, 20, 30) / 255 ramp(timer, 10, 70)), +2336 (image entry 21) sliding in from
//     x = 750 (750 (1 - (2k - k^2)), k = ramp(timer, 20, 20)) at y 95, 313.9 x 403.125 (.sdata literals 0x7CB168 /
//     0x7CB16C);
//   * the list: item i's three sprites (title entries {0, 2, 4, 25}[i] / {1, 3, 5, 26}[i] / {6, 7, 8, 27}[i]; y 298, 323,
//     346, 371) slide in from x = 20 - 50 (1 - (2k - k^2)) with k = ramp(timer, 20 + 5 i, 10), alpha k times
//     255 (1 - highlight / 16) (the plate), 127.5 (1 - state / 8) (the flash), 255 highlight / 16 (the lit plate); the
//     continue panel (+5952, entries 34 / 35 at (323, 115)) and the continue items (entries {28, 30} / {29, 31}) the
//     same way;
//   * the bottom glow: a triangle {0, -88} / {1086, 448} / {0, 448} zoomed about (0, 448) by 1.35 + 0.35 sin(2 pi
//     c2328 / 150) (.sdata literals 0x7CB094 / 0x7CAD8C), written straight into the strip at +2576 (corners +2592..,
//     colours: the inlined byte -> float conversion of the RGBA (10, 17, 48, alpha), alpha 178.5 (0x7CB170) times a
//     ramp of the timer).
void Cpu::sub_26A2C0() {
    enter(16);
    sp = addiu(sp, -192);
    sd(ra, sp, 128);
    sq(s5, sp, 112);
    sq(s4, sp, 96);
    sq(s3, sp, 80);
    sq(s2, sp, 64);
    sq(s1, sp, 48);
    sq(s0, sp, 32);
    swc1(F24, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    lw(v0, gp, kGpOpMenu);
    if (v0 == 0) {
        charge(5);
        kassert(0x26A30Cu, kFileOpMenu, 135);
    }
    charge(10);
    lw(s1, gp, kGpOpMenu);
    a0 = 0;
    jal(0x26A31Cu, gen::fn_sub_266C50_00266c50);
    s4 = v0;
    lw(v1, s1, 0);
    v1 = nor(v1, zero);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        charge(56);
        lw(v0, s1, 2320);
        v1 = addiu(v0, 1);
        sw(v1, s1, 2320);
        v0 = 1300;
        div(v1, v0);
        mfhi(v0);
        sw(v0, s1, 2320);
        lw(v0, s1, 2324);
        v1 = addiu(v0, 1);
        sw(v1, s1, 2324);
        v0 = 500;
        div(v1, v0);
        mfhi(v0);
        sw(v0, s1, 2324);
        lw(v0, s1, 2328);
        v0 = addiu(v0, 1);
        sw(v0, s1, 2328);
        a0 = 150;
        div(v0, a0);
        mfhi(v0);
        sw(v0, s1, 2328);
        lw(v0, s1, 2788);
        v0 = addiu(v0, 1);
        sw(v0, s1, 2788);
        div(v0, a0);
        mfhi(v0);
        sw(v0, s1, 2788);
        lw(v0, s1, 2784);
        v1 = addiu(v0, 1);
        sw(v1, s1, 2784);
        v0 = 80;
        div(v1, v0);
        mfhi(v0);
        sw(v0, s1, 2784);
        lw(v0, s1, 2792);
        v0 = addiu(v0, 1);
        sw(v0, s1, 2792);
        div(v0, a0);
        mfhi(v0);
        sw(v0, s1, 2792);
        lw(v0, s1, 2800);
        v0 = addiu(v0, 1);
        sw(v0, s1, 2800);
        div(v0, a0);
        mfhi(v0);
        sw(v0, s1, 2800);
        lw(v0, s1, 2796);
        v0 = addiu(v0, 1);
        sw(v0, s1, 2796);
        div(v0, a0);
        mfhi(v0);
        sw(v0, s1, 2796);
        lw(v0, s1, 2804);
        at = slti(v0, 40);
        if (at != 0) {
            charge(4);
            v0 = addiu(v0, 1);
            sw(v0, s1, 2804);
        } else {
            charge(4);
            lw(v1, s1, 0);
            v0 = si(-9);
            v0 = v1 & v0;
            sw(v0, s1, 0);
        }
        charge(4);
        lw(v1, s1, 0);
        v0 = v1 & 0x4;
        if (v0 != 0) {
            charge(4);
            lw(v0, s1, 2332);
            at = slti(v0, 80);
            if (at != 0) {
                charge(4);
                v0 = addiu(v0, 1);
                sw(v0, s1, 2332);
            } else {
                charge(3);
                v0 = si(-5);
                v0 = v1 & v0;
                sw(v0, s1, 0);
            }
        }
        charge(4);
        lw(v0, s1, 0);
        v0 = v0 & 0x20;
        if (v0 != 0) {
            charge(3);
            a0 = 0;
            for (;;) {
                charge(3);
                v0 = slti(a0, 4);
                if (v0 == 0) break;
                backedge();
                charge(11);
                v0 = sll(a0, 3);
                v1 = subu(v0, a0);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v0 = sll(v0, 4);
                v0 = addu(s1, v0);
                v1 = addiu(v0, 2816);
                lw(v0, v0, 2816);
                at = slti(v0, 8);
                if (at != 0) {
                    charge(2);
                    v0 = addiu(v0, 1);
                    sw(v0, v1, 0);
                }
                charge(3);
                lw(v0, s1, 2808);
                if (a0 != v0) {
                    charge(4);
                    lw(v0, v1, 4);
                    at = slti(v0, 16);
                    if (at != 0) {
                        charge(2);
                        v0 = addiu(v0, 1);
                        sw(v0, v1, 4);
                    }
                }
                charge(1);
                a0 = addiu(a0, 1);
            }
            charge(5);
            v1 = addiu(s1, 5952);
            lw(v0, s1, 5952);
            at = slti(v0, 8);
            if (at != 0) {
                charge(4);
                v0 = addiu(v0, 1);
                sw(v0, v1, 0);
            }
        } else {
            charge(3);
            a0 = 0;
            for (;;) {
                charge(3);
                v0 = slti(a0, 2);
                if (v0 == 0) break;
                backedge();
                charge(11);
                v0 = sll(a0, 3);
                v1 = subu(v0, a0);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v0 = sll(v0, 4);
                v0 = addu(s1, v0);
                v1 = addiu(v0, 6752);
                lw(v0, v0, 6752);
                at = slti(v0, 8);
                if (at != 0) {
                    charge(2);
                    v0 = addiu(v0, 1);
                    sw(v0, v1, 0);
                }
                charge(3);
                lw(v0, s1, 6736);
                if (a0 != v0) {
                    charge(4);
                    lw(v0, v1, 4);
                    at = slti(v0, 16);
                    if (at != 0) {
                        charge(2);
                        v0 = addiu(v0, 1);
                        sw(v0, v1, 4);
                    }
                }
                charge(1);
                a0 = addiu(a0, 1);
            }
        }
        charge(3);
        lw(v0, s1, 2332);
        if (ltz(v0)) {
            charge(3);
            mtc1(zero, F20);
        } else {
            charge(3);
            at = slti(v0, 70);
            if (at != 0) {
                charge(12);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x428C);  // 70.0
                mtc1(v0, F0);
                div_s(F20, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F20);
            }
        }
        charge(24);
        sw(zero, sp, 144);
        sw(zero, sp, 148);
        v0 = lui(0x4420);
        sw(v0, sp, 152);
        v0 = lui(0x43E0);
        sw(v0, sp, 156);
        // The background: +16, the full screen.
        a0 = addiu(s1, 16);
        a1 = addiu(sp, 144);
        jal(0x26A610u, gen::fn_sub_21D8E0_0021d8e0);
        white_alpha(188, F20);
        charge(8);
        sb(v1, sp, 191);
        a0 = addiu(s1, 16);
        a1 = addiu(sp, 188);
        jal(0x26A68Cu, gen::fn_sub_21D950_0021d950);
        lw(v0, s1, 2332);
        if (ltz(v0)) {
            charge(3);
            mtc1(zero, F22);
        } else {
            charge(2);
            if (ltz(v0)) {
                charge(11);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                mtc1(zero, F0);
                div_s(F22, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F22);
            }
        }
        charge(99);
        lwc1(F0, s1, 2320);
        cvt_s_w(F1, F0);
        v0 = 1300;
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        div_s(F1, F1, F0);
        v0 = 1100;
        mtc1(v0, F0);
        cvt_s_w(F3, F0);
        v0 = lui(0x3F80);  // 1.0
        mtc1(v0, F0);
        sub_s(F2, F0, F1);
        v0 = lui(0xC3A0);  // -320.0
        mtc1(v0, F1);
        mtc1(zero, F0);
        adda_s(F0, F1);
        msub_s(F21, F3, F2);
        lwc1(F0, s1, 2324);
        cvt_s_w(F1, F0);
        v0 = lui(0x43FA);  // 500.0
        mtc1(v0, F0);
        div_s(F1, F1, F0);
        v0 = lui(0x4000);  // 2.0
        mtc1(v0, F0);
        mul_s(F1, F0, F1);
        lwc1(F0, gp, -32184);  // pi (the .sdata literal at 0x7CAF38)
        mul_s(F12, F0, F1);
        jal(0x26A76Cu, gen::fn_sinf_0052e878);
        v0 = lui(0x3E80);  // 0.25
        mtc1(v0, F3);
        lwc1(F2, gp, -32668);  // 0.45 (the .sdata literal at 0x7CAD54)
        mtc1(zero, F1);
        adda_s(F1, F2);
        madd_s(F20, F3, F0);
        swc1(F21, sp, 144);
        sw(zero, sp, 148);
        v0 = lui(0x44A0);
        sw(v0, sp, 152);
        v0 = lui(0x43E0);
        sw(v0, sp, 156);
        // +272 / +528: the scrolling band (two copies 1100 apart).
        a0 = addiu(s1, 272);
        a1 = addiu(sp, 144);
        jal(0x26A7B0u, gen::fn_sub_21D8E0_0021d8e0);
        lwc1(F0, s1, 2320);
        cvt_s_w(F1, F0);
        v0 = 1300;
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        div_s(F1, F1, F0);
        v0 = 1100;
        mtc1(v0, F0);
        cvt_s_w(F3, F0);
        v0 = lui(0x3F80);  // 1.0
        mtc1(v0, F0);
        sub_s(F2, F0, F1);
        v0 = lui(0xC3A0);  // -320.0
        mtc1(v0, F1);
        mtc1(zero, F0);
        adda_s(F0, F1);
        msub_s(F0, F3, F2);
        add_s(F0, F3, F0);
        swc1(F0, sp, 144);
        sw(zero, sp, 148);
        v0 = lui(0x44A0);
        sw(v0, sp, 152);
        v0 = lui(0x43E0);
        sw(v0, sp, 156);
        a0 = addiu(s1, 528);
        a1 = addiu(sp, 144);
        jal(0x26A830u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 188);
        sb(v0, sp, 189);
        sb(v0, sp, 190);
        v0 = lui(0x437F);  // 255.0
        mtc1(v0, F0);
        mul_s(F0, F0, F22);
        mul_s(F1, F0, F20);
        f2u8(v1, F1);
        charge(54);
        sb(v1, sp, 191);
        a0 = addiu(s1, 272);
        a1 = addiu(sp, 188);
        jal(0x26A8B0u, gen::fn_sub_21D950_0021d950);
        a0 = addiu(s1, 528);
        a1 = addiu(sp, 188);
        jal(0x26A8C0u, gen::fn_sub_21D950_0021d950);
        lwc1(F0, s1, 2792);
        cvt_s_w(F1, F0);
        v0 = lui(0x4316);  // 150.0
        mtc1(v0, F0);
        div_s(F1, F1, F0);
        v0 = lui(0x4000);  // 2.0
        mtc1(v0, F0);
        mul_s(F1, F0, F1);
        lwc1(F0, gp, -32184);  // pi (the .sdata literal at 0x7CAF38)
        mul_s(F12, F0, F1);
        jal(0x26A8F8u, gen::fn_sinf_0052e878);
        v0 = lui(0x3FC0);  // 1.5
        mtc1(v0, F1);
        mul_s(F1, F1, F0);
        v0 = lui(0x43B4);  // 360.0
        mtc1(v0, F0);
        div_s(F1, F1, F0);
        v0 = lui(0x4000);  // 2.0
        mtc1(v0, F0);
        mul_s(F1, F0, F1);
        lwc1(F0, gp, -32184);  // pi (the .sdata literal at 0x7CAF38)
        mul_s(F20, F0, F1);
        sw(zero, sp, 144);
        sw(zero, sp, 148);
        v0 = lui(0x4420);
        sw(v0, sp, 152);
        sw(zero, sp, 156);
        sw(v0, sp, 160);
        v0 = lui(0x43E0);
        sw(v0, sp, 164);
        sw(zero, sp, 168);
        sw(v0, sp, 172);
        v1 = 0;
        v0 = lui(0x43A0);  // 320.0
        mtc1(v0, F2);
        v0 = lui(0x4360);  // 224.0
        mtc1(v0, F1);
        quad_pass(144, QuadOp::Sub, F2, F1);
        charge(4);
        v1 = 0;
        lwc1(F1, gp, -32576);  // 1.1 (the .sdata literal at 0x7CADB0)
        quad_pass(144, QuadOp::Mul, F1, F1);
        charge(3);
        s2 = 0;
        rotate_quad(144, 0x26AA14u, F20, F22, F21, F23);
        charge(7);
        v1 = 0;
        v0 = lui(0x43A0);  // 320.0
        mtc1(v0, F2);
        v0 = lui(0x4360);  // 224.0
        mtc1(v0, F1);
        quad_pass(144, QuadOp::Add, F2, F1);
        charge(38);
        // +784: the swaying quad of counter +2792 (scale 1.1).
        a0 = addiu(s1, 784);
        a1 = addiu(sp, 144);
        jal(0x26AAD8u, gen::fn_sub_21D890_0021d890);
        lwc1(F0, s1, 2800);
        cvt_s_w(F1, F0);
        v0 = lui(0x4316);  // 150.0
        mtc1(v0, F0);
        div_s(F1, F1, F0);
        lwc1(F0, gp, -32004);  // 0.2 (the .sdata literal at 0x7CAFEC)
        add_s(F1, F0, F1);
        v0 = lui(0x4000);  // 2.0
        mtc1(v0, F0);
        mul_s(F1, F0, F1);
        lwc1(F0, gp, -32184);  // pi (the .sdata literal at 0x7CAF38)
        mul_s(F12, F0, F1);
        jal(0x26AB18u, gen::fn_sinf_0052e878);
        v0 = lui(0x3FC0);  // 1.5
        mtc1(v0, F1);
        mul_s(F1, F1, F0);
        v0 = lui(0x43B4);  // 360.0
        mtc1(v0, F0);
        div_s(F1, F1, F0);
        v0 = lui(0x4000);  // 2.0
        mtc1(v0, F0);
        mul_s(F1, F0, F1);
        lwc1(F0, gp, -32184);  // pi (the .sdata literal at 0x7CAF38)
        mul_s(F20, F0, F1);
        lw(v0, s1, 2796);
        at = slti(v0, 65);
        if (at != 0) {
            charge(3);
            lwc1(F3, gp, -32576);  // 1.1 (the .sdata literal at 0x7CADB0)
        } else {
            charge(3);
            at = slti(v0, 95);
            if (at != 0) {
                charge(14);
                v0 = addiu(v0, -65);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x41F0);  // 30.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
                lwc1(F0, gp, -32004);  // 0.2 (the .sdata literal at 0x7CAFEC)
                mul_s(F1, F0, F1);
                lwc1(F0, gp, -32576);  // 1.1 (the .sdata literal at 0x7CADB0)
                add_s(F3, F0, F1);
            } else {
                charge(3);
                at = slti(v0, 115);
                if (at != 0) {
                    charge(3);
                    lwc1(F3, gp, -32576);  // 1.1 (the .sdata literal at 0x7CADB0)
                } else {
                    charge(1);
                    lwc1(F3, gp, -32576);  // 1.1 (the .sdata literal at 0x7CADB0)
                }
            }
        }
        charge(17);
        sw(zero, sp, 144);
        sw(zero, sp, 148);
        v0 = lui(0x4420);
        sw(v0, sp, 152);
        sw(zero, sp, 156);
        sw(v0, sp, 160);
        v0 = lui(0x43E0);
        sw(v0, sp, 164);
        sw(zero, sp, 168);
        sw(v0, sp, 172);
        v1 = 0;
        v0 = lui(0x43A0);  // 320.0
        mtc1(v0, F2);
        v0 = lui(0x4360);  // 224.0
        mtc1(v0, F1);
        quad_pass(144, QuadOp::Sub, F2, F1);
        charge(3);
        v1 = 0;
        quad_pass(144, QuadOp::Mul, F3, F3);
        charge(3);
        s2 = 0;
        rotate_quad(144, 0x26ACACu, F20, F22, F21, F23);
        charge(7);
        v1 = 0;
        v0 = lui(0x43A0);  // 320.0
        mtc1(v0, F2);
        v0 = lui(0x4360);  // 224.0
        mtc1(v0, F1);
        quad_pass(144, QuadOp::Add, F2, F1);
        charge(25);
        // +1040: the swaying quad of counter +2800 (scale by +2796).
        a0 = addiu(s1, 1040);
        a1 = addiu(sp, 144);
        jal(0x26AD70u, gen::fn_sub_21D890_0021d890);
        v0 = 255;
        sb(v0, sp, 188);
        sb(v0, sp, 189);
        sb(v0, sp, 190);
        sb(v0, sp, 191);
        a0 = addiu(s1, 784);
        a1 = addiu(sp, 188);
        jal(0x26AD94u, gen::fn_sub_21D950_0021d950);
        v0 = 255;
        sb(v0, sp, 188);
        sb(v0, sp, 189);
        sb(v0, sp, 190);
        sb(v0, sp, 191);
        a0 = addiu(s1, 1040);
        a1 = addiu(sp, 188);
        jal(0x26ADB8u, gen::fn_sub_21D950_0021d950);
        lw(v0, s1, 2332);
        if (ltz(v0)) {
            charge(3);
            mtc1(zero, F22);
        } else {
            charge(2);
            if (ltz(v0)) {
                charge(11);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                mtc1(zero, F0);
                div_s(F22, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F22);
            }
        }
        charge(75);
        lwc1(F0, s1, 2788);
        cvt_s_w(F1, F0);
        v0 = lui(0x4316);  // 150.0
        mtc1(v0, F0);
        div_s(F1, F1, F0);
        lwc1(F0, gp, -32004);  // 0.2 (the .sdata literal at 0x7CAFEC)
        add_s(F1, F0, F1);
        v0 = lui(0x4000);  // 2.0
        mtc1(v0, F0);
        mul_s(F1, F0, F1);
        lwc1(F0, gp, -32184);  // pi (the .sdata literal at 0x7CAF38)
        mul_s(F12, F0, F1);
        jal(0x26AE4Cu, gen::fn_sinf_0052e878);
        v0 = lui(0x41C8);  // 25.0
        mtc1(v0, F1);
        mul_s(F1, F1, F0);
        v0 = lui(0x43B4);  // 360.0
        mtc1(v0, F0);
        div_s(F0, F1, F0);
        v0 = lui(0x4000);  // 2.0
        mtc1(v0, F3);
        mul_s(F0, F3, F0);
        lwc1(F2, gp, -32184);  // pi (the .sdata literal at 0x7CAF38)
        mul_s(F21, F2, F0);
        lwc1(F0, s1, 2784);
        cvt_s_w(F1, F0);
        v0 = lui(0x42A0);  // 80.0
        mtc1(v0, F0);
        div_s(F0, F1, F0);
        mul_s(F0, F3, F0);
        mul_s(F23, F2, F0);
        mov_s(F12, F23);
        jal(0x26AEB0u, gen::fn_sinf_0052e878);
        v0 = lui(0x3E80);  // 0.25
        mtc1(v0, F3);
        lwc1(F2, gp, -32356);  // 1.7 (the .sdata literal at 0x7CAE8C)
        mtc1(zero, F1);
        adda_s(F1, F2);
        madd_s(F20, F3, F0);
        mov_s(F12, F23);
        jal(0x26AED8u, gen::fn_sinf_0052e878);
        v0 = lui(0x3E80);  // 0.25
        mtc1(v0, F3);
        lwc1(F2, gp, -32356);  // 1.7 (the .sdata literal at 0x7CAE8C)
        mtc1(zero, F1);
        adda_s(F1, F2);
        madd_s(F3, F3, F0);
        sw(zero, sp, 144);
        sw(zero, sp, 148);
        v0 = lui(0x4420);
        sw(v0, sp, 152);
        sw(zero, sp, 156);
        sw(v0, sp, 160);
        v0 = lui(0x43E0);
        sw(v0, sp, 164);
        sw(zero, sp, 168);
        sw(v0, sp, 172);
        v1 = 0;
        v0 = lui(0x43A0);  // 320.0
        mtc1(v0, F2);
        v0 = lui(0x4360);  // 224.0
        mtc1(v0, F1);
        quad_pass(144, QuadOp::Sub, F2, F1);
        charge(3);
        v1 = 0;
        quad_pass(144, QuadOp::Mul, F20, F3);
        charge(3);
        s2 = 0;
        rotate_quad(144, 0x26AFD4u, F21, F23, F20, F24);
        charge(7);
        v1 = 0;
        v0 = lui(0x43A0);  // 320.0
        mtc1(v0, F2);
        v0 = lui(0x4360);  // 224.0
        mtc1(v0, F1);
        quad_pass(144, QuadOp::Add, F2, F1);
        charge(22);
        // +1296 / +1552: the swaying quads of counter +2328 (scale 1.7 + 0.25 sin).
        a0 = addiu(s1, 1296);
        a1 = addiu(sp, 144);
        jal(0x26B098u, gen::fn_sub_21D890_0021d890);
        a0 = addiu(s1, 1552);
        a1 = addiu(sp, 144);
        jal(0x26B0A8u, gen::fn_sub_21D890_0021d890);
        white_alpha(188, F22);
        charge(9);
        sb(v1, sp, 191);
        a0 = addiu(s1, 1296);
        a1 = addiu(sp, 188);
        jal(0x26B124u, gen::fn_sub_21D950_0021d950);
        lw(v0, s1, 2796);
        at = slti(v0, 65);
        if (at != 0) {
            charge(4);
            v0 = lui(0x3F80);  // 1.0
            mtc1(v0, F1);
        } else {
            charge(3);
            at = slti(v0, 95);
            if (at != 0) {
                charge(14);
                v0 = addiu(v0, -65);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x41F0);  // 30.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F0);
                sub_s(F1, F0, F1);
            } else {
                charge(3);
                at = slti(v0, 115);
                if (at != 0) {
                    charge(3);
                    mtc1(zero, F1);
                } else {
                    charge(3);
                    at = slti(v0, 145);
                    if (at != 0) {
                        charge(13);
                        v0 = addiu(v0, -115);
                        mtc1(v0, F0);
                        cvt_s_w(F1, F0);
                        v0 = lui(0x41F0);  // 30.0
                        mtc1(v0, F0);
                        div_s(F1, F1, F0);
                    } else {
                        charge(2);
                        v0 = lui(0x3F80);  // 1.0
                        mtc1(v0, F1);
                    }
                }
            }
        }
        charge(15);
        v0 = 255;
        sb(v0, sp, 188);
        sb(v0, sp, 189);
        sb(v0, sp, 190);
        v0 = lui(0x4319);  // 153.0
        mtc1(v0, F0);
        mul_s(F0, F0, F22);
        mul_s(F1, F0, F1);
        f2u8(v1, F1);
        charge(9);
        sb(v1, sp, 191);
        a0 = addiu(s1, 1552);
        a1 = addiu(sp, 188);
        jal(0x26B268u, gen::fn_sub_21D950_0021d950);
        lw(v0, s1, 2332);
        at = slti(v0, 20);
        if (at != 0) {
            charge(3);
            mtc1(zero, F20);
        } else {
            charge(3);
            at = slti(v0, 50);
            if (at != 0) {
                charge(13);
                v0 = addiu(v0, -20);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x41F0);  // 30.0
                mtc1(v0, F0);
                div_s(F20, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F20);
            }
        }
        charge(24);
        sw(zero, sp, 144);
        sw(zero, sp, 148);
        v0 = lui(0x4420);
        sw(v0, sp, 152);
        v0 = lui(0x43E0);
        sw(v0, sp, 156);
        // +1808: the full screen, alpha 204 ramp(timer, 20, 30).
        a0 = addiu(s1, 1808);
        a1 = addiu(sp, 144);
        jal(0x26B2F4u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 188);
        sb(v0, sp, 189);
        sb(v0, sp, 190);
        v0 = lui(0x434C);  // 204.0
        mtc1(v0, F0);
        mul_s(F1, F0, F20);
        f2u8(v1, F1);
        charge(9);
        sb(v1, sp, 191);
        a0 = addiu(s1, 1808);
        a1 = addiu(sp, 188);
        jal(0x26B370u, gen::fn_sub_21D950_0021d950);
        lw(v0, s1, 2332);
        at = slti(v0, 10);
        if (at != 0) {
            charge(3);
            mtc1(zero, F20);
        } else {
            charge(3);
            at = slti(v0, 80);
            if (at != 0) {
                charge(13);
                v0 = addiu(v0, -10);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x428C);  // 70.0
                mtc1(v0, F0);
                div_s(F20, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F20);
            }
        }
        charge(24);
        sw(zero, sp, 144);
        sw(zero, sp, 148);
        v0 = lui(0x4420);
        sw(v0, sp, 152);
        v0 = lui(0x43E0);
        sw(v0, sp, 156);
        // +2064: the full screen, alpha 255 ramp(timer, 10, 70).
        a0 = addiu(s1, 2064);
        a1 = addiu(sp, 144);
        jal(0x26B3FCu, gen::fn_sub_21D8E0_0021d8e0);
        white_alpha(188, F20);
        charge(9);
        sb(v1, sp, 191);
        a0 = addiu(s1, 2064);
        a1 = addiu(sp, 188);
        jal(0x26B478u, gen::fn_sub_21D950_0021d950);
        lw(v0, s1, 2332);
        at = slti(v0, 20);
        if (at != 0) {
            charge(6);
            v0 = 750;
            mtc1(v0, F0);
            cvt_s_w(F20, F0);
        } else {
            charge(3);
            at = slti(v0, 40);
            if (at != 0) {
                charge(24);
                v0 = addiu(v0, -20);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x41A0);  // 20.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
                v0 = lui(0x4000);  // 2.0
                mtc1(v0, F0);
                mula_s(F0, F1);
                msub_s(F2, F1, F1);
                v0 = 750;
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F0);
                sub_s(F0, F0, F2);
                mul_s(F20, F1, F0);
            } else {
                charge(1);
                mtc1(zero, F20);
            }
        }
        charge(28);
        a0 = s4;
        a1 = 21;
        jal(0x26B520u, gen::fn_sub_21CCA0_0021cca0);
        swc1(F20, sp, 144);
        v0 = lui(0x42BE);
        sw(v0, sp, 148);
        lwc1(F0, gp, -31624);  // 313.9 (the .sdata literal at 0x7CB168)
        swc1(F0, sp, 152);
        lwc1(F0, gp, -31620);  // 403.125 (the .sdata literal at 0x7CB16C)
        swc1(F0, sp, 156);
        // +2336 (image entry 21): sliding in from x 750.
        a0 = addiu(s1, 2336);
        a1 = addiu(sp, 144);
        jal(0x26B54Cu, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 188);
        sb(v0, sp, 189);
        sb(v0, sp, 190);
        sb(v0, sp, 191);
        a0 = addiu(s1, 2336);
        a1 = addiu(sp, 188);
        jal(0x26B570u, gen::fn_sub_21D950_0021d950);
        lw(v0, s1, 0);
        v0 = v0 & 0x20;
        if (v0 != 0) {
            charge(3);
            s2 = 0;
            for (;;) {
                charge(3);
                v0 = slti(s2, 4);
                if (v0 == 0) break;
                backedge();
                charge(14);
                v0 = sll(s2, 3);
                v1 = subu(v0, s2);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v0 = sll(v0, 4);
                v0 = addu(s1, v0);
                s0 = addiu(v0, 2816);
                v0 = sll(s2, 2);
                a1 = addu(v0, s2);
                a0 = addiu(a1, 20);
                lw(v1, s1, 2332);
                at = slt(v1, a0);
                if (at != 0) {
                    charge(4);
                    v0 = lui(0xC248);  // -50.0
                    mtc1(v0, F20);
                } else {
                    charge(4);
                    v0 = addiu(a1, 30);
                    at = slt(v1, v0);
                    if (at != 0) {
                        charge(22);
                        v0 = subu(v1, a0);
                        mtc1(v0, F0);
                        cvt_s_w(F1, F0);
                        v0 = lui(0x4120);  // 10.0
                        mtc1(v0, F0);
                        div_s(F1, F1, F0);
                        v0 = lui(0x4000);  // 2.0
                        mtc1(v0, F0);
                        mula_s(F0, F1);
                        msub_s(F2, F1, F1);
                        v0 = lui(0xC248);  // -50.0
                        mtc1(v0, F1);
                        v0 = lui(0x3F80);  // 1.0
                        mtc1(v0, F0);
                        sub_s(F0, F0, F2);
                        mul_s(F20, F1, F0);
                    } else {
                        charge(1);
                        mtc1(zero, F20);
                    }
                }
                charge(3);
                at = slt(v1, a0);
                if (at != 0) {
                    charge(3);
                    mtc1(zero, F21);
                } else {
                    charge(4);
                    v0 = addiu(a1, 30);
                    at = slt(v1, v0);
                    if (at != 0) {
                        charge(13);
                        v0 = subu(v1, a0);
                        mtc1(v0, F0);
                        cvt_s_w(F1, F0);
                        v0 = lui(0x4120);  // 10.0
                        mtc1(v0, F0);
                        div_s(F21, F1, F0);
                    } else {
                        charge(2);
                        v0 = lui(0x3F80);  // 1.0
                        mtc1(v0, F21);
                    }
                }
                charge(3);
                v0 = 3;
                if (s2 != v0) {
                    charge(3);
                    v1 = 2;
                    if (s2 != v1) {
                        charge(3);
                        v0 = 1;
                        if (s2 != v0) {
                            charge(2);
                            if (s2 != 0) {
                                charge(2);
                            } else {
                                charge(3);
                                s3 = 0;
                            }
                        } else {
                            charge(3);
                            s3 = v1;
                        }
                    } else {
                        charge(3);
                        s3 = 4;
                    }
                } else {
                    charge(1);
                    s3 = 25;
                }
                charge(12);
                // Title item i: the plate (entries {0, 2, 4, 25}), at x 20 + the slide.
                a0 = s4;
                a1 = s3;
                jal(0x26B710u, gen::fn_sub_21CCA0_0021cca0);
                v1 = lui(0x41A0);  // 20.0
                mtc1(v1, F0);
                add_s(F20, F0, F20);
                swc1(F20, sp, 144);
                v1 = 3;
                if (s2 != v1) {
                    charge(3);
                    v1 = 2;
                    if (s2 != v1) {
                        charge(3);
                        v1 = 1;
                        if (s2 != v1) {
                            charge(2);
                            if (s2 != 0) {
                                charge(2);
                            } else {
                                charge(4);
                                v1 = lui(0x4395);
                                sw(v1, sp, 148);
                            }
                        } else {
                            charge(7);
                            v1 = 323;
                            mtc1(v1, F0);
                            cvt_s_w(F0, F0);
                            swc1(F0, sp, 148);
                        }
                    } else {
                        charge(4);
                        v1 = lui(0x43AD);
                        sw(v1, sp, 148);
                    }
                } else {
                    charge(5);
                    v1 = 371;
                    mtc1(v1, F0);
                    cvt_s_w(F0, F0);
                    swc1(F0, sp, 148);
                }
                charge(35);
                lwc1(F0, v0, 12);
                cvt_s_w(F0, F0);
                swc1(F0, sp, 152);
                lwc1(F0, v0, 16);
                cvt_s_w(F0, F0);
                swc1(F0, sp, 156);
                a0 = addiu(s0, 16);
                a1 = addiu(sp, 144);
                jal(0x26B7D0u, gen::fn_sub_21D8E0_0021d8e0);
                lwc1(F0, s0, 4);
                cvt_s_w(F1, F0);
                v0 = lui(0x4180);  // 16.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F0);
                sub_s(F1, F0, F1);
                v0 = 255;
                sb(v0, sp, 188);
                sb(v0, sp, 189);
                sb(v0, sp, 190);
                v0 = lui(0x437F);  // 255.0
                mtc1(v0, F0);
                mul_s(F0, F0, F1);
                mul_s(F1, F0, F21);
                f2u8(v1, F1);
                charge(8);
                sb(v1, sp, 191);
                a0 = addiu(s0, 16);
                a1 = addiu(sp, 188);
                jal(0x26B878u, gen::fn_sub_21D950_0021d950);
                v1 = 3;
                if (s2 != v1) {
                    charge(3);
                    v0 = 2;
                    if (s2 != v0) {
                        charge(3);
                        v0 = 1;
                        if (s2 != v0) {
                            charge(2);
                            if (s2 != 0) {
                                charge(2);
                            } else {
                                charge(3);
                                s3 = v0;
                            }
                        } else {
                            charge(3);
                            s3 = v1;
                        }
                    } else {
                        charge(3);
                        s3 = 5;
                    }
                } else {
                    charge(1);
                    s3 = 26;
                }
                charge(8);
                // The flash (entries {1, 3, 5, 26}), alpha 127.5 (1 - state / 8).
                a0 = s4;
                a1 = s3;
                jal(0x26B8E4u, gen::fn_sub_21CCA0_0021cca0);
                swc1(F20, sp, 144);
                v1 = 3;
                if (s2 != v1) {
                    charge(3);
                    v1 = 2;
                    if (s2 != v1) {
                        charge(3);
                        v1 = 1;
                        if (s2 != v1) {
                            charge(2);
                            if (s2 != 0) {
                                charge(2);
                            } else {
                                charge(4);
                                v1 = lui(0x4395);
                                sw(v1, sp, 148);
                            }
                        } else {
                            charge(7);
                            v1 = 323;
                            mtc1(v1, F0);
                            cvt_s_w(F0, F0);
                            swc1(F0, sp, 148);
                        }
                    } else {
                        charge(4);
                        v1 = lui(0x43AD);
                        sw(v1, sp, 148);
                    }
                } else {
                    charge(5);
                    v1 = 371;
                    mtc1(v1, F0);
                    cvt_s_w(F0, F0);
                    swc1(F0, sp, 148);
                }
                charge(35);
                lwc1(F0, v0, 12);
                cvt_s_w(F0, F0);
                swc1(F0, sp, 152);
                lwc1(F0, v0, 16);
                cvt_s_w(F0, F0);
                swc1(F0, sp, 156);
                a0 = addiu(s0, 272);
                a1 = addiu(sp, 144);
                jal(0x26B994u, gen::fn_sub_21D8E0_0021d8e0);
                lwc1(F0, s0, 0);
                cvt_s_w(F1, F0);
                v0 = lui(0x4100);  // 8.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F0);
                sub_s(F1, F0, F1);
                v0 = 255;
                sb(v0, sp, 188);
                sb(v0, sp, 189);
                sb(v0, sp, 190);
                v0 = lui(0x42FF);  // 127.5
                mtc1(v0, F0);
                mul_s(F0, F0, F1);
                mul_s(F1, F0, F21);
                f2u8(v1, F1);
                charge(8);
                sb(v1, sp, 191);
                a0 = addiu(s0, 272);
                a1 = addiu(sp, 188);
                jal(0x26BA3Cu, gen::fn_sub_21D950_0021d950);
                v0 = 3;
                if (s2 != v0) {
                    charge(3);
                    v0 = 2;
                    if (s2 != v0) {
                        charge(3);
                        v0 = 1;
                        if (s2 != v0) {
                            charge(2);
                            if (s2 != 0) {
                                charge(2);
                            } else {
                                charge(3);
                                s3 = 6;
                            }
                        } else {
                            charge(3);
                            s3 = 7;
                        }
                    } else {
                        charge(3);
                        s3 = 8;
                    }
                } else {
                    charge(1);
                    s3 = 27;
                }
                charge(8);
                // The lit plate (entries {6, 7, 8, 27}), alpha 255 highlight / 16.
                a0 = s4;
                a1 = s3;
                jal(0x26BAA8u, gen::fn_sub_21CCA0_0021cca0);
                swc1(F20, sp, 144);
                v1 = 3;
                if (s2 != v1) {
                    charge(3);
                    v1 = 2;
                    if (s2 != v1) {
                        charge(3);
                        v1 = 1;
                        if (s2 != v1) {
                            charge(2);
                            if (s2 != 0) {
                                charge(2);
                            } else {
                                charge(4);
                                v1 = lui(0x4395);
                                sw(v1, sp, 148);
                            }
                        } else {
                            charge(7);
                            v1 = 323;
                            mtc1(v1, F0);
                            cvt_s_w(F0, F0);
                            swc1(F0, sp, 148);
                        }
                    } else {
                        charge(4);
                        v1 = lui(0x43AD);
                        sw(v1, sp, 148);
                    }
                } else {
                    charge(5);
                    v1 = 371;
                    mtc1(v1, F0);
                    cvt_s_w(F0, F0);
                    swc1(F0, sp, 148);
                }
                charge(31);
                lwc1(F0, v0, 12);
                cvt_s_w(F0, F0);
                swc1(F0, sp, 152);
                lwc1(F0, v0, 16);
                cvt_s_w(F0, F0);
                swc1(F0, sp, 156);
                a0 = addiu(s0, 528);
                a1 = addiu(sp, 144);
                jal(0x26BB58u, gen::fn_sub_21D8E0_0021d8e0);
                lwc1(F0, s0, 4);
                cvt_s_w(F1, F0);
                v0 = lui(0x4180);  // 16.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
                v0 = 255;
                sb(v0, sp, 188);
                sb(v0, sp, 189);
                sb(v0, sp, 190);
                v0 = lui(0x437F);  // 255.0
                mtc1(v0, F0);
                mul_s(F0, F0, F1);
                mul_s(F1, F0, F21);
                f2u8(v1, F1);
                charge(6);
                sb(v1, sp, 191);
                a0 = addiu(s0, 528);
                a1 = addiu(sp, 188);
                jal(0x26BBF0u, gen::fn_sub_21D950_0021d950);
                s2 = addiu(s2, 1);
            }
            charge(63);
            s0 = addiu(s1, 5952);
            // The continue panel (+5952: entries 34 / 35 at x 323).
            a0 = s4;
            a1 = 34;
            jal(0x26BC14u, gen::fn_sub_21CCA0_0021cca0);
            v1 = 323;
            mtc1(v1, F0);
            cvt_s_w(F0, F0);
            swc1(F0, sp, 144);
            v1 = lui(0x42E6);
            sw(v1, sp, 148);
            lwc1(F0, v0, 12);
            cvt_s_w(F0, F0);
            swc1(F0, sp, 152);
            lwc1(F0, v0, 16);
            cvt_s_w(F0, F0);
            swc1(F0, sp, 156);
            a0 = addiu(s0, 16);
            a1 = addiu(sp, 144);
            jal(0x26BC58u, gen::fn_sub_21D8E0_0021d8e0);
            a0 = s4;
            a1 = 35;
            jal(0x26BC68u, gen::fn_sub_21CCA0_0021cca0);
            v1 = 323;
            mtc1(v1, F0);
            cvt_s_w(F0, F0);
            swc1(F0, sp, 144);
            v1 = lui(0x42E6);
            sw(v1, sp, 148);
            lwc1(F0, v0, 12);
            cvt_s_w(F0, F0);
            swc1(F0, sp, 152);
            lwc1(F0, v0, 16);
            cvt_s_w(F0, F0);
            swc1(F0, sp, 156);
            a0 = addiu(s0, 272);
            a1 = addiu(sp, 144);
            jal(0x26BCACu, gen::fn_sub_21D8E0_0021d8e0);
            lwc1(F0, s0, 0);
            cvt_s_w(F1, F0);
            v0 = lui(0x4100);  // 8.0
            mtc1(v0, F0);
            div_s(F1, F1, F0);
            white_alpha(188, F1);
            charge(11);
            sb(v1, sp, 191);
            a0 = addiu(s0, 16);
            a1 = addiu(sp, 188);
            jal(0x26BD40u, gen::fn_sub_21D950_0021d950);
            a0 = addiu(s0, 272);
            a1 = addiu(sp, 188);
            jal(0x26BD50u, gen::fn_sub_21D950_0021d950);
        } else {
            charge(3);
            s2 = 0;
            for (;;) {
                charge(3);
                v0 = slti(s2, 2);
                if (v0 == 0) break;
                backedge();
                charge(14);
                v0 = sll(s2, 3);
                v1 = subu(v0, s2);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v0 = sll(v0, 4);
                v0 = addu(s1, v0);
                s0 = addiu(v0, 6752);
                v0 = sll(s2, 2);
                a1 = addu(v0, s2);
                a0 = addiu(a1, 20);
                lw(v1, s1, 2332);
                at = slt(v1, a0);
                if (at != 0) {
                    charge(4);
                    v0 = lui(0xC248);  // -50.0
                    mtc1(v0, F21);
                } else {
                    charge(4);
                    v0 = addiu(a1, 30);
                    at = slt(v1, v0);
                    if (at != 0) {
                        charge(22);
                        v0 = subu(v1, a0);
                        mtc1(v0, F0);
                        cvt_s_w(F1, F0);
                        v0 = lui(0x4120);  // 10.0
                        mtc1(v0, F0);
                        div_s(F1, F1, F0);
                        v0 = lui(0x4000);  // 2.0
                        mtc1(v0, F0);
                        mula_s(F0, F1);
                        msub_s(F2, F1, F1);
                        v0 = lui(0xC248);  // -50.0
                        mtc1(v0, F1);
                        v0 = lui(0x3F80);  // 1.0
                        mtc1(v0, F0);
                        sub_s(F0, F0, F2);
                        mul_s(F21, F1, F0);
                    } else {
                        charge(1);
                        mtc1(zero, F21);
                    }
                }
                charge(3);
                at = slt(v1, a0);
                if (at != 0) {
                    charge(3);
                    mtc1(zero, F20);
                } else {
                    charge(4);
                    v0 = addiu(a1, 30);
                    at = slt(v1, v0);
                    if (at != 0) {
                        charge(13);
                        v0 = subu(v1, a0);
                        mtc1(v0, F0);
                        cvt_s_w(F1, F0);
                        v0 = lui(0x4120);  // 10.0
                        mtc1(v0, F0);
                        div_s(F20, F1, F0);
                    } else {
                        charge(2);
                        v0 = lui(0x3F80);  // 1.0
                        mtc1(v0, F20);
                    }
                }
                charge(3);
                v0 = 1;
                if (s2 != v0) {
                    charge(2);
                    if (s2 != 0) {
                        charge(2);
                    } else {
                        charge(3);
                        s3 = 28;
                    }
                } else {
                    charge(1);
                    s3 = 30;
                }
                charge(12);
                a0 = s4;
                a1 = s3;
                jal(0x26BEB8u, gen::fn_sub_21CCA0_0021cca0);
                v1 = lui(0x41D0);  // 26.0
                mtc1(v1, F0);
                add_s(F21, F0, F21);
                swc1(F21, sp, 144);
                v1 = 1;
                if (s2 != v1) {
                    charge(2);
                    if (s2 != 0) {
                        charge(2);
                    } else {
                        charge(7);
                        v1 = 345;
                        mtc1(v1, F0);
                        cvt_s_w(F0, F0);
                        swc1(F0, sp, 148);
                    }
                } else {
                    charge(2);
                    v1 = lui(0x43BF);
                    sw(v1, sp, 148);
                }
                charge(35);
                lwc1(F0, v0, 12);
                cvt_s_w(F0, F0);
                swc1(F0, sp, 152);
                lwc1(F0, v0, 16);
                cvt_s_w(F0, F0);
                swc1(F0, sp, 156);
                a0 = addiu(s0, 16);
                a1 = addiu(sp, 144);
                jal(0x26BF34u, gen::fn_sub_21D8E0_0021d8e0);
                lwc1(F0, s0, 4);
                cvt_s_w(F1, F0);
                v0 = lui(0x4180);  // 16.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F0);
                sub_s(F1, F0, F1);
                v0 = 255;
                sb(v0, sp, 188);
                sb(v0, sp, 189);
                sb(v0, sp, 190);
                v0 = lui(0x437F);  // 255.0
                mtc1(v0, F0);
                mul_s(F0, F0, F1);
                mul_s(F1, F0, F20);
                f2u8(v1, F1);
                charge(8);
                sb(v1, sp, 191);
                a0 = addiu(s0, 16);
                a1 = addiu(sp, 188);
                jal(0x26BFDCu, gen::fn_sub_21D950_0021d950);
                v0 = 1;
                if (s2 != v0) {
                    charge(2);
                    if (s2 != 0) {
                        charge(2);
                    } else {
                        charge(3);
                        s3 = 29;
                    }
                } else {
                    charge(1);
                    s3 = 31;
                }
                charge(8);
                a0 = s4;
                a1 = s3;
                jal(0x26C018u, gen::fn_sub_21CCA0_0021cca0);
                swc1(F21, sp, 144);
                v1 = 1;
                if (s2 != v1) {
                    charge(2);
                    if (s2 != 0) {
                        charge(2);
                    } else {
                        charge(7);
                        v1 = 345;
                        mtc1(v1, F0);
                        cvt_s_w(F0, F0);
                        swc1(F0, sp, 148);
                    }
                } else {
                    charge(2);
                    v1 = lui(0x43BF);
                    sw(v1, sp, 148);
                }
                charge(31);
                lwc1(F0, v0, 12);
                cvt_s_w(F0, F0);
                swc1(F0, sp, 152);
                lwc1(F0, v0, 16);
                cvt_s_w(F0, F0);
                swc1(F0, sp, 156);
                a0 = addiu(s0, 272);
                a1 = addiu(sp, 144);
                jal(0x26C084u, gen::fn_sub_21D8E0_0021d8e0);
                lwc1(F0, s0, 4);
                cvt_s_w(F1, F0);
                v0 = lui(0x4180);  // 16.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
                v0 = 255;
                sb(v0, sp, 188);
                sb(v0, sp, 189);
                sb(v0, sp, 190);
                v0 = lui(0x437F);  // 255.0
                mtc1(v0, F0);
                mul_s(F0, F0, F1);
                mul_s(F1, F0, F20);
                f2u8(v1, F1);
                charge(6);
                sb(v1, sp, 191);
                a0 = addiu(s0, 272);
                a1 = addiu(sp, 188);
                jal(0x26C11Cu, gen::fn_sub_21D950_0021d950);
                s2 = addiu(s2, 1);
            }
        }
        charge(3);
        lw(v0, s1, 2332);
        if (ltz(v0)) {
            charge(3);
            mtc1(zero, F21);
        } else {
            charge(2);
            if (ltz(v0)) {
                charge(11);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                mtc1(zero, F0);
                div_s(F21, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F21);
            }
        }
        charge(47);
        sw(zero, sp, 144);
        v0 = lui(0xC2B0);
        sw(v0, sp, 148);
        v0 = 1086;
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        swc1(F0, sp, 152);
        v0 = lui(0x43E0);
        sw(v0, sp, 156);
        sw(zero, sp, 160);
        sw(v0, sp, 164);
        lwc1(F0, s1, 2328);
        cvt_s_w(F1, F0);
        v0 = lui(0x4316);  // 150.0
        mtc1(v0, F0);
        div_s(F1, F1, F0);
        v0 = lui(0x4000);  // 2.0
        mtc1(v0, F0);
        mul_s(F1, F0, F1);
        lwc1(F0, gp, -32184);  // pi (the .sdata literal at 0x7CAF38)
        mul_s(F22, F0, F1);
        mov_s(F12, F22);
        jal(0x26C1ECu, gen::fn_sinf_0052e878);
        lwc1(F3, gp, -31836);  // 0.35 (the .sdata literal at 0x7CB094)
        lwc1(F2, gp, -32612);  // 1.35 (the .sdata literal at 0x7CAD8C)
        mtc1(zero, F1);
        adda_s(F1, F2);
        madd_s(F20, F3, F0);
        mov_s(F12, F22);
        jal(0x26C210u, gen::fn_sinf_0052e878);
        lwc1(F3, gp, -31836);  // 0.35 (the .sdata literal at 0x7CB094)
        lwc1(F1, gp, -32612);  // 1.35 (the .sdata literal at 0x7CAD8C)
        mtc1(zero, F2);
        adda_s(F2, F1);
        madd_s(F3, F3, F0);
        a0 = 0;
        v1 = lui(0x43E0);  // 448.0
        mtc1(v1, F1);
        for (;;) {
            charge(3);
            v1 = slti(a0, 3);
            if (v1 == 0) break;
            backedge();
            charge(10);
            v1 = sll(a0, 3);
            v1 = addu(v1, sp);
            v1 = addiu(v1, 144);
            lwc1(F0, v1, 0);
            sub_s(F0, F0, F2);
            swc1(F0, v1, 0);
            lwc1(F0, v1, 4);
            sub_s(F0, F0, F1);
            swc1(F0, v1, 4);
            a0 = addiu(a0, 1);
        }
        charge(3);
        a0 = 0;
        for (;;) {
            charge(3);
            v1 = slti(a0, 3);
            if (v1 == 0) break;
            backedge();
            charge(10);
            v1 = sll(a0, 3);
            v1 = addu(v1, sp);
            v1 = addiu(v1, 144);
            lwc1(F0, v1, 0);
            mul_s(F0, F0, F20);
            swc1(F0, v1, 0);
            lwc1(F0, v1, 4);
            mul_s(F0, F0, F3);
            swc1(F0, v1, 4);
            a0 = addiu(a0, 1);
        }
        charge(6);
        a0 = 0;
        mtc1(zero, F2);
        v1 = lui(0x43E0);  // 448.0
        mtc1(v1, F1);
        for (;;) {
            charge(3);
            v1 = slti(a0, 3);
            if (v1 == 0) break;
            backedge();
            charge(10);
            v1 = sll(a0, 3);
            v1 = addu(v1, sp);
            v1 = addiu(v1, 144);
            lwc1(F0, v1, 0);
            add_s(F0, F0, F2);
            swc1(F0, v1, 0);
            lwc1(F0, v1, 4);
            add_s(F0, F0, F1);
            swc1(F0, v1, 4);
            a0 = addiu(a0, 1);
        }
        charge(23);
        v1 = addiu(s1, 2592);
        lwc1(F0, sp, 144);
        swc1(F0, s1, 2592);
        lwc1(F0, sp, 148);
        swc1(F0, s1, 2596);
        lwc1(F0, sp, 152);
        swc1(F0, s1, 2656);
        lwc1(F0, sp, 156);
        swc1(F0, s1, 2660);
        lwc1(F0, sp, 160);
        swc1(F0, s1, 2720);
        lwc1(F0, sp, 164);
        swc1(F0, s1, 2724);
        a0 = 10;
        sb(a0, sp, 188);
        a0 = 17;
        sb(a0, sp, 189);
        a0 = 48;
        sb(a0, sp, 190);
        sb(zero, sp, 191);
        lbu(a0, sp, 188);
        if (gez(a0)) {
            charge(5);
            mtc1(a0, F0);
            cvt_s_w(F0, F0);
        } else {
            charge(7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, F0);
            cvt_s_w(F0, F0);
            add_s(F0, F0, F0);
        }
        charge(4);
        swc1(F0, v1, 32);
        lbu(a0, sp, 189);
        if (gez(a0)) {
            charge(5);
            mtc1(a0, F0);
            cvt_s_w(F0, F0);
        } else {
            charge(7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, F0);
            cvt_s_w(F0, F0);
            add_s(F0, F0, F0);
        }
        charge(4);
        swc1(F0, v1, 36);
        lbu(a0, sp, 190);
        if (gez(a0)) {
            charge(5);
            mtc1(a0, F0);
            cvt_s_w(F0, F0);
        } else {
            charge(7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, F0);
            cvt_s_w(F0, F0);
            add_s(F0, F0, F0);
        }
        charge(4);
        swc1(F0, v1, 40);
        lbu(a0, sp, 191);
        if (gez(a0)) {
            charge(5);
            mtc1(a0, F0);
            cvt_s_w(F0, F0);
        } else {
            charge(7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, F0);
            cvt_s_w(F0, F0);
            add_s(F0, F0, F0);
        }
        charge(10);
        swc1(F0, v1, 44);
        sb(zero, sp, 188);
        a0 = 7;
        sb(a0, sp, 189);
        a0 = 38;
        sb(a0, sp, 190);
        sb(zero, sp, 191);
        lbu(a0, sp, 188);
        if (gez(a0)) {
            charge(5);
            mtc1(a0, F0);
            cvt_s_w(F0, F0);
        } else {
            charge(7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, F0);
            cvt_s_w(F0, F0);
            add_s(F0, F0, F0);
        }
        charge(4);
        swc1(F0, v1, 96);
        lbu(a0, sp, 189);
        if (gez(a0)) {
            charge(5);
            mtc1(a0, F0);
            cvt_s_w(F0, F0);
        } else {
            charge(7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, F0);
            cvt_s_w(F0, F0);
            add_s(F0, F0, F0);
        }
        charge(4);
        swc1(F0, v1, 100);
        lbu(a0, sp, 190);
        if (gez(a0)) {
            charge(5);
            mtc1(a0, F0);
            cvt_s_w(F0, F0);
        } else {
            charge(7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, F0);
            cvt_s_w(F0, F0);
            add_s(F0, F0, F0);
        }
        charge(4);
        swc1(F0, v1, 104);
        lbu(a0, sp, 191);
        if (gez(a0)) {
            charge(5);
            mtc1(a0, F0);
            cvt_s_w(F0, F0);
        } else {
            charge(7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, F0);
            cvt_s_w(F0, F0);
            add_s(F0, F0, F0);
        }
        charge(14);
        swc1(F0, v1, 108);
        sb(zero, sp, 188);
        a0 = 7;
        sb(a0, sp, 189);
        a0 = 38;
        sb(a0, sp, 190);
        lwc1(F0, gp, -31616);  // 178.5 (the .sdata literal at 0x7CB170)
        mul_s(F1, F0, F21);
        f2u8(a1, F1, a0);
        charge(4);
        sb(a1, sp, 191);
        lbu(a0, sp, 188);
        if (gez(a0)) {
            charge(5);
            mtc1(a0, F0);
            cvt_s_w(F0, F0);
        } else {
            charge(7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, F0);
            cvt_s_w(F0, F0);
            add_s(F0, F0, F0);
        }
        charge(4);
        swc1(F0, v1, 160);
        lbu(a0, sp, 189);
        if (gez(a0)) {
            charge(5);
            mtc1(a0, F0);
            cvt_s_w(F0, F0);
        } else {
            charge(7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, F0);
            cvt_s_w(F0, F0);
            add_s(F0, F0, F0);
        }
        charge(4);
        swc1(F0, v1, 164);
        lbu(a0, sp, 190);
        if (gez(a0)) {
            charge(5);
            mtc1(a0, F0);
            cvt_s_w(F0, F0);
        } else {
            charge(7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, F0);
            cvt_s_w(F0, F0);
            add_s(F0, F0, F0);
        }
        charge(4);
        swc1(F0, v1, 168);
        lbu(a0, sp, 191);
        if (gez(a0)) {
            charge(5);
            mtc1(a0, F0);
            cvt_s_w(F0, F0);
        } else {
            charge(7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, F0);
            cvt_s_w(F0, F0);
            add_s(F0, F0, F0);
        }
        charge(1);
        swc1(F0, v1, 172);
    }
    charge(15);
    ld(ra, sp, 128);
    lq(s5, sp, 112);
    lq(s4, sp, 96);
    lq(s3, sp, 80);
    lq(s2, sp, 64);
    lq(s1, sp, 48);
    lq(s0, sp, 32);
    lwc1(F24, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 192);
    return;
}

// =====================================================================================================================
// op_wait.c (work gp-18744: +0 flags, +4 the page (0 the screen appearing, 1 leaving), +8 the page timer, +12 .. +48
// the animation counters opWait_Update steps (+12 % 90, +16 % 50, +20 % 30, +24 % 690, +28 % 70, +32 % 690, +36 % 1024,
// +44 % 360, +48 % 1024; +40 the fade-in timer), +64 .. +3392 the sprites, +3648 3 symbols, +4464 / +4468 the two fade
// grids, +4472 a float the draw leaves for the grid visitors).
// =====================================================================================================================
//
// 0x26EED0 [opWait_Draw]: one frame of the "press start" screen (opWait_Update's last step, also opWait_Init's first
// draw). Asserts the work (line 219); s0 = the work, s1 = the title image. Every sprite's alpha follows the page: on
// page 0 a ramp of the page timer t over the sprite's window, on page 1 1 - a short ramp from t = 0 (the leave), any
// other page keeps the previous value; the counters drive the motion:
//   +64   the backdrop, the full screen: page 0 ramp(t, 0, 100), page 1 1 - ramp(t, 0, 40);
//   +320  a band {-1, 29} .. {642, 448} (its y pass in a 3-stage loop over the corners as compiled), alpha the fade
//         (page 0 ramp(t, 110, 90)) times 0.75 + 0.15 sin(2 pi c28 / 70) (0.15: the .sdata literal at 0x7CAD84);
//   +576  a 256 x 256 square drifting from (210, 69) by -(188, 93) c32 / 690, page 0 ramp(t, 0, 200);
//   +832  / +1088 the two text strips (title texture 12's size, see opWait_Init): page 0 a rectangle fading in over
//         t 0 .. 60 / 55 .. 100, page 1 a quad built from the leave ramp (the constants 140 / 150 / 4.5 / 6.75 for
//         +832, 500 / 400 / 232 / 416 / 116 / 208 for +1088);
//   +1600 alpha by a sine of c16 (period 50) on page 0's window 100 .. 180;
//   +1856 its source rectangle (sub_21EAE0) scrolling with c12 (period 90), page 0 window 40 .. 150;
//   +2112 a quad waving with two sines of c20 (period 30);
//   +2624 / +2368 / +2880 / +3392 the image entries of opWait_Init (38, 19, 10, 16) at their places, page 0
//         windows 200 .. 220, 170 .. 210, 210 .. 220, 70 .. 150 (page 1 out over 10 / 30 frames);
//   +3648 the 3 symbols (+0 their phase 100 perm + 60): each a quad rotated about its centre (sinf / cosf of its
//         angle), page 1 out over 20 frames;
// then +4472 = the last fade ($f29), and the two fade grids: sub_269A10(+4464, {sub_271230, work}) and
// sub_269A10(+4468, {sub_2716D0, work}) (the visitor record on the frame at sp + 288: the function, the work), which
// write the grids' vertices from the counters +44 / +48.
void Cpu::sub_26EED0() {
    enter(26);
    sp = addiu(sp, -304);
    sd(ra, sp, 192);
    sq(fp, sp, 176);
    sq(s7, sp, 160);
    sq(s6, sp, 144);
    sq(s5, sp, 128);
    sq(s4, sp, 112);
    sq(s3, sp, 96);
    sq(s2, sp, 80);
    sq(s1, sp, 64);
    sq(s0, sp, 48);
    swc1(F31, sp, 44);
    swc1(F30, sp, 40);
    swc1(F29, sp, 36);
    swc1(F28, sp, 32);
    swc1(F27, sp, 28);
    swc1(F26, sp, 24);
    swc1(F25, sp, 20);
    swc1(F24, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    lw(v0, gp, kGpOpWait);
    if (v0 == 0) {
        charge(5);
        kassert(0x26EF44u, kFileOpWait, 219);
    }
    charge(9);
    lw(s0, gp, kGpOpWait);
    a0 = 0;
    jal(0x26EF54u, gen::fn_sub_266C50_00266c50);
    s1 = v0;
    lw(v1, s0, 4);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
        } else {
            charge(3);
            lw(v0, s0, 8);
            if (ltz(v0)) {
                charge(3);
                mtc1(zero, F29);
            } else {
                charge(3);
                at = slti(v0, 100);
                if (at != 0) {
                    charge(12);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x42C8);  // 100.0
                    mtc1(v0, F0);
                    div_s(F29, F1, F0);
                } else {
                    charge(2);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F29);
                }
            }
            charge(2);
        }
    } else {
        charge(3);
        lw(v0, s0, 8);
        if (ltz(v0)) {
            charge(3);
            mtc1(zero, F1);
        } else {
            charge(3);
            at = slti(v0, 40);
            if (at != 0) {
                charge(12);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x4220);  // 40.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F1);
            }
        }
        charge(4);
        v0 = lui(0x3F80);  // 1.0
        mtc1(v0, F0);
        sub_s(F29, F0, F1);
    }
    charge(24);
    sw(zero, sp, 256);
    sw(zero, sp, 260);
    v0 = lui(0x4420);
    sw(v0, sp, 264);
    v0 = lui(0x43E0);
    sw(v0, sp, 268);
    // +64: the backdrop.
    a0 = addiu(s0, 64);
    a1 = addiu(sp, 256);
    jal(0x26F070u, gen::fn_sub_21D8E0_0021d8e0);
    white_alpha(300, F29);
    charge(9);
    sb(v1, sp, 303);
    a0 = addiu(s0, 64);
    a1 = addiu(sp, 300);
    jal(0x26F0ECu, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, 4);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
        } else {
            charge(4);
            lw(v0, s0, 8);
            at = slti(v0, 110);
            if (at != 0) {
                charge(3);
                mtc1(zero, F29);
            } else {
                charge(3);
                at = slti(v0, 200);
                if (at != 0) {
                    charge(13);
                    v0 = addiu(v0, -110);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x42B4);  // 90.0
                    mtc1(v0, F0);
                    div_s(F29, F1, F0);
                } else {
                    charge(2);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F29);
                }
            }
            charge(2);
        }
    } else {
        charge(3);
        lw(v0, s0, 8);
        if (ltz(v0)) {
            charge(3);
            mtc1(zero, F1);
        } else {
            charge(3);
            at = slti(v0, 40);
            if (at != 0) {
                charge(12);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x4220);  // 40.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F1);
            }
        }
        charge(4);
        v0 = lui(0x3F80);  // 1.0
        mtc1(v0, F0);
        sub_s(F29, F0, F1);
    }
    charge(48);
    lwc1(F0, s0, 28);
    cvt_s_w(F1, F0);
    v0 = lui(0x428C);  // 70.0
    mtc1(v0, F0);
    div_s(F1, F1, F0);
    v0 = lui(0x4000);  // 2.0
    mtc1(v0, F0);
    mul_s(F1, F0, F1);
    lwc1(F0, gp, -32184);  // pi (the .sdata literal at 0x7CAF38)
    mul_s(F12, F0, F1);
    jal(0x26F21Cu, gen::fn_sinf_0052e878);
    lwc1(F3, gp, -32620);  // 0.15 (the .sdata literal at 0x7CAD84)
    v0 = lui(0x3F40);  // 0.75
    mtc1(v0, F2);
    mtc1(zero, F1);
    adda_s(F1, F2);
    madd_s(F24, F3, F0);
    v0 = 643;
    mtc1(v0, F0);
    cvt_s_w(F23, F0);
    v0 = 419;
    mtc1(v0, F0);
    cvt_s_w(F22, F0);
    a0 = lui(0xBF80);
    sw(a0, sp, 256);
    v1 = lui(0x41E8);
    sw(v1, sp, 260);
    v0 = 642;
    mtc1(v0, F0);
    cvt_s_w(F0, F0);
    swc1(F0, sp, 264);
    sw(v1, sp, 268);
    swc1(F0, sp, 272);
    v0 = lui(0x43E0);
    sw(v0, sp, 276);
    sw(a0, sp, 280);
    sw(v0, sp, 284);
    v1 = 0;
    mtc1(v0, F1);
    for (;;) {
        charge(3);
        v0 = slti(v1, 4);
        if (v0 == 0) break;
        backedge();
        charge(6);
        v0 = sll(v1, 3);
        v0 = addu(v0, sp);
        lwc1(F0, v0, 260);
        sub_s(F0, F0, F1);
        swc1(F0, v0, 260);
        v1 = addiu(v1, 1);
    }
    charge(5);
    v1 = 0;
    v0 = lui(0x3F80);  // 1.0
    mtc1(v0, F1);
    for (;;) {
        charge(3);
        v0 = slti(v1, 4);
        if (v0 == 0) break;
        backedge();
        charge(6);
        v0 = sll(v1, 3);
        v0 = addu(v0, sp);
        lwc1(F0, v0, 260);
        mul_s(F0, F0, F1);
        swc1(F0, v0, 260);
        v1 = addiu(v1, 1);
    }
    charge(5);
    v1 = 0;
    v0 = lui(0x43E0);  // 448.0
    mtc1(v0, F1);
    for (;;) {
        charge(3);
        v0 = slti(v1, 4);
        if (v0 == 0) break;
        backedge();
        charge(6);
        v0 = sll(v1, 3);
        v0 = addu(v0, sp);
        lwc1(F0, v0, 260);
        add_s(F0, F0, F1);
        swc1(F0, v0, 260);
        v1 = addiu(v1, 1);
    }
    charge(19);
    // +320: the band, alpha times 0.75 + 0.15 sin(2 pi c28 / 70).
    a0 = addiu(s0, 320);
    a1 = addiu(sp, 256);
    jal(0x26F348u, gen::fn_sub_21D890_0021d890);
    v0 = 255;
    sb(v0, sp, 300);
    sb(v0, sp, 301);
    sb(v0, sp, 302);
    v0 = lui(0x437F);  // 255.0
    mtc1(v0, F0);
    mul_s(F0, F0, F29);
    mul_s(F1, F0, F24);
    f2u8(v1, F1);
    charge(9);
    sb(v1, sp, 303);
    a0 = addiu(s0, 320);
    a1 = addiu(sp, 300);
    jal(0x26F3C8u, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, 4);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
        } else {
            charge(3);
            lw(v0, s0, 8);
            if (ltz(v0)) {
                charge(3);
                mtc1(zero, F29);
            } else {
                charge(3);
                at = slti(v0, 200);
                if (at != 0) {
                    charge(12);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x4348);  // 200.0
                    mtc1(v0, F0);
                    div_s(F29, F1, F0);
                } else {
                    charge(2);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F29);
                }
            }
            charge(2);
        }
    } else {
        charge(3);
        lw(v0, s0, 8);
        if (ltz(v0)) {
            charge(3);
            mtc1(zero, F1);
        } else {
            charge(3);
            at = slti(v0, 20);
            if (at != 0) {
                charge(12);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x41A0);  // 20.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F1);
            }
        }
        charge(4);
        v0 = lui(0x3F80);  // 1.0
        mtc1(v0, F0);
        sub_s(F29, F0, F1);
    }
    charge(47);
    lwc1(F0, s0, 32);
    cvt_s_w(F1, F0);
    v0 = 690;
    mtc1(v0, F0);
    cvt_s_w(F0, F0);
    div_s(F2, F1, F0);
    v0 = lui(0x4352);  // 210.0
    mtc1(v0, F26);
    v0 = lui(0x428A);  // 69.0
    mtc1(v0, F25);
    v0 = lui(0xC1C0);  // -24.0
    mtc1(v0, F24);
    v0 = lui(0xC33C);  // -188.0
    mtc1(v0, F0);
    mtc1(zero, F1);
    adda_s(F1, F26);
    madd_s(F28, F2, F0);
    v0 = lui(0xC2BA);  // -93.0
    mtc1(v0, F0);
    adda_s(F1, F25);
    madd_s(F27, F2, F0);
    swc1(F28, sp, 256);
    swc1(F27, sp, 260);
    v0 = lui(0x4380);
    sw(v0, sp, 264);
    sw(v0, sp, 268);
    // +576: the drifting square (c32 / 690).
    a0 = addiu(s0, 576);
    a1 = addiu(sp, 256);
    jal(0x26F53Cu, gen::fn_sub_21D8E0_0021d8e0);
    white_alpha(300, F29);
    charge(9);
    sb(v1, sp, 303);
    a0 = addiu(s0, 576);
    a1 = addiu(sp, 300);
    jal(0x26F5B8u, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, 4);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
        } else {
            charge(3);
            lw(v0, s0, 8);
            if (ltz(v0)) {
                charge(3);
                mtc1(zero, F29);
            } else {
                charge(3);
                at = slti(v0, 60);
                if (at != 0) {
                    charge(12);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x4270);  // 60.0
                    mtc1(v0, F0);
                    div_s(F29, F1, F0);
                } else {
                    charge(2);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F29);
                }
            }
            charge(12);
            sw(zero, sp, 256);
            sw(zero, sp, 260);
            v0 = lui(0x4420);
            sw(v0, sp, 264);
            v0 = lui(0x43E0);
            sw(v0, sp, 268);
            // +832: the first text strip (page 0: a rectangle).
            a0 = addiu(s0, 832);
            a1 = addiu(sp, 256);
            jal(0x26F65Cu, gen::fn_sub_21D8E0_0021d8e0);
        }
    } else {
        charge(3);
        lw(v1, s0, 8);
        if (ltz(v1)) {
            charge(3);
            mtc1(zero, F0);
        } else {
            charge(3);
            at = slti(v1, 30);
            if (at != 0) {
                charge(12);
                mtc1(v1, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x41F0);  // 30.0
                mtc1(v0, F0);
                div_s(F0, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F0);
            }
        }
        charge(6);
        v0 = lui(0x3F80);  // 1.0
        mtc1(v0, F3);
        sub_s(F29, F3, F0);
        if (ltz(v1)) {
            charge(3);
            mtc1(zero, F3);
        } else {
            charge(3);
            at = slti(v1, 40);
            if (at != 0) {
                charge(10);
                mtc1(v1, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x4220);  // 40.0
                mtc1(v0, F0);
                div_s(F3, F1, F0);
            }
        }
        charge(17);
        sw(zero, sp, 256);
        sw(zero, sp, 260);
        v0 = lui(0x4420);
        sw(v0, sp, 264);
        sw(zero, sp, 268);
        sw(v0, sp, 272);
        v0 = lui(0x43E0);
        sw(v0, sp, 276);
        sw(zero, sp, 280);
        sw(v0, sp, 284);
        v1 = 0;
        v0 = lui(0x430C);  // 140.0
        mtc1(v0, F2);
        v0 = lui(0x4316);  // 150.0
        mtc1(v0, F1);
        quad_pass(256, QuadOp::Sub, F2, F1);
        charge(16);
        v1 = 0;
        v0 = lui(0x4090);  // 4.5
        mtc1(v0, F0);
        v0 = lui(0x3F80);  // 1.0
        mtc1(v0, F2);
        mtc1(zero, F1);
        adda_s(F1, F2);
        madd_s(F4, F0, F3);
        v0 = lui(0x40D8);  // 6.75
        mtc1(v0, F0);
        adda_s(F1, F2);
        madd_s(F1, F0, F3);
        quad_pass(256, QuadOp::Mul, F4, F1);
        charge(7);
        v1 = 0;
        v0 = lui(0x430C);  // 140.0
        mtc1(v0, F2);
        v0 = lui(0x4316);  // 150.0
        mtc1(v0, F1);
        quad_pass(256, QuadOp::Add, F2, F1);
        charge(4);
        // (page 1: the squeezed quad)
        a0 = addiu(s0, 832);
        a1 = addiu(sp, 256);
        jal(0x26F864u, gen::fn_sub_21D890_0021d890);
    }
    charge(14);
    white_alpha(300, F29);
    charge(9);
    sb(v1, sp, 303);
    a0 = addiu(s0, 832);
    a1 = addiu(sp, 300);
    jal(0x26F8E0u, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, 4);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
        } else {
            charge(4);
            lw(v1, s0, 8);
            at = slti(v1, 55);
            if (at != 0) {
                charge(3);
                mtc1(zero, F29);
            } else {
                charge(3);
                at = slti(v1, 60);
                if (at != 0) {
                    charge(13);
                    v0 = addiu(v1, -55);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x40A0);  // 5.0
                    mtc1(v0, F0);
                    div_s(F29, F1, F0);
                } else {
                    charge(2);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F29);
                }
            }
            charge(3);
            at = slti(v1, 55);
            if (at != 0) {
                charge(3);
                mtc1(zero, F2);
            } else {
                charge(3);
                at = slti(v1, 100);
                if (at != 0) {
                    charge(13);
                    v0 = addiu(v1, -55);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x4234);  // 45.0
                    mtc1(v0, F0);
                    div_s(F2, F1, F0);
                } else {
                    charge(2);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F2);
                }
            }
            charge(38);
            mul_s(F1, F2, F2);
            v0 = lui(0x4000);  // 2.0
            mtc1(v0, F0);
            mul_s(F0, F0, F2);
            sub_s(F26, F0, F1);
            v0 = lui(0xC3B9);  // -370.0
            mtc1(v0, F2);
            v0 = lui(0x3F80);  // 1.0
            mtc1(v0, F0);
            sub_s(F1, F0, F26);
            mul_s(F28, F2, F1);
            v0 = lui(0x42C8);  // 100.0
            mtc1(v0, F0);
            mul_s(F27, F0, F1);
            v0 = 335;
            mtc1(v0, F0);
            cvt_s_w(F0, F0);
            add_s(F0, F0, F28);
            swc1(F0, sp, 256);
            v0 = lui(0x4200);  // 32.0
            mtc1(v0, F0);
            add_s(F0, F0, F27);
            swc1(F0, sp, 260);
            v0 = lui(0x4368);
            sw(v0, sp, 264);
            v0 = lui(0x43D0);
            sw(v0, sp, 268);
            // +1088: the second text strip (page 0: a rectangle).
            a0 = addiu(s0, 1088);
            a1 = addiu(sp, 256);
            jal(0x26FA54u, gen::fn_sub_21D8E0_0021d8e0);
        }
    } else {
        charge(4);
        lw(v1, s0, 8);
        at = slti(v1, 10);
        if (at != 0) {
            charge(3);
            mtc1(zero, F0);
        } else {
            charge(3);
            at = slti(v1, 10);
            if (at != 0) {
                charge(12);
                v0 = addiu(v1, -10);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                mtc1(zero, F0);
                div_s(F0, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F0);
            }
        }
        charge(6);
        v0 = lui(0x3F80);  // 1.0
        mtc1(v0, F1);
        sub_s(F29, F1, F0);
        if (ltz(v1)) {
            charge(3);
            mtc1(zero, F1);
        } else {
            charge(3);
            at = slti(v1, 10);
            if (at != 0) {
                charge(10);
                mtc1(v1, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x4120);  // 10.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
            }
        }
        charge(10);
        v0 = lui(0x43FA);  // 500.0
        mtc1(v0, F0);
        mul_s(F26, F0, F1);
        v0 = lui(0x43C8);  // 400.0
        mtc1(v0, F0);
        mul_s(F25, F0, F1);
        if (ltz(v1)) {
            charge(3);
            mtc1(zero, F1);
        } else {
            charge(3);
            at = slti(v1, 10);
            if (at != 0) {
                charge(12);
                mtc1(v1, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x4120);  // 10.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F1);
            }
        }
        charge(46);
        v0 = lui(0x4000);  // 2.0
        mtc1(v0, F0);
        mul_s(F1, F0, F1);
        v0 = lui(0x3F80);  // 1.0
        mtc1(v0, F0);
        add_s(F2, F0, F1);
        v0 = 335;
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        add_s(F1, F0, F26);
        v0 = lui(0x41F0);  // 30.0
        mtc1(v0, F0);
        sub_s(F28, F1, F0);
        v0 = lui(0x4200);  // 32.0
        mtc1(v0, F0);
        add_s(F27, F0, F25);
        v0 = lui(0x4368);  // 232.0
        mtc1(v0, F23);
        v0 = lui(0x43D0);  // 416.0
        mtc1(v0, F22);
        v0 = lui(0x42E8);  // 116.0
        mtc1(v0, F0);
        add_s(F3, F28, F0);
        v0 = lui(0x4350);  // 208.0
        mtc1(v0, F0);
        add_s(F1, F27, F0);
        swc1(F28, sp, 256);
        swc1(F27, sp, 260);
        add_s(F0, F28, F23);
        swc1(F0, sp, 264);
        swc1(F27, sp, 268);
        swc1(F0, sp, 272);
        add_s(F0, F27, F22);
        swc1(F0, sp, 276);
        swc1(F28, sp, 280);
        swc1(F0, sp, 284);
        v1 = 0;
        quad_pass(256, QuadOp::Sub, F3, F1);
        charge(3);
        v1 = 0;
        quad_pass(256, QuadOp::Mul, F2, F2);
        charge(3);
        v1 = 0;
        quad_pass(256, QuadOp::Add, F3, F1);
        charge(4);
        // (page 1: the squeezed quad)
        a0 = addiu(s0, 1088);
        a1 = addiu(sp, 256);
        jal(0x26FD08u, gen::fn_sub_21D890_0021d890);
    }
    charge(14);
    white_alpha(300, F29);
    charge(9);
    sb(v1, sp, 303);
    a0 = addiu(s0, 1088);
    a1 = addiu(sp, 300);
    jal(0x26FD84u, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, 4);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
        } else {
            charge(4);
            lw(v0, s0, 8);
            at = slti(v0, 100);
            if (at != 0) {
                charge(3);
                mtc1(zero, F29);
            } else {
                charge(3);
                at = slti(v0, 180);
                if (at != 0) {
                    charge(13);
                    v0 = addiu(v0, -100);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x42A0);  // 80.0
                    mtc1(v0, F0);
                    div_s(F29, F1, F0);
                } else {
                    charge(2);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F29);
                }
            }
            charge(2);
        }
    } else {
        charge(3);
        lw(v0, s0, 8);
        if (ltz(v0)) {
            charge(3);
            mtc1(zero, F1);
        } else {
            charge(3);
            at = slti(v0, 20);
            if (at != 0) {
                charge(12);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x41A0);  // 20.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F1);
            }
        }
        charge(4);
        v0 = lui(0x3F80);  // 1.0
        mtc1(v0, F0);
        sub_s(F29, F0, F1);
    }
    charge(35);
    lwc1(F0, s0, 16);
    cvt_s_w(F1, F0);
    v0 = lui(0x4248);  // 50.0
    mtc1(v0, F0);
    div_s(F1, F1, F0);
    v0 = lui(0x4000);  // 2.0
    mtc1(v0, F0);
    mul_s(F1, F0, F1);
    lwc1(F0, gp, -32184);  // pi (the .sdata literal at 0x7CAF38)
    mul_s(F12, F0, F1);
    jal(0x26FEB4u, gen::fn_sinf_0052e878);
    lwc1(F3, gp, -32620);  // 0.15 (the .sdata literal at 0x7CAD84)
    lwc1(F2, gp, -32604);  // 0.85 (the .sdata literal at 0x7CAD94)
    mtc1(zero, F1);
    adda_s(F1, F2);
    madd_s(F1, F3, F0);
    v0 = 255;
    sb(v0, sp, 300);
    sb(v0, sp, 301);
    sb(v0, sp, 302);
    v0 = lui(0x437F);  // 255.0
    mtc1(v0, F0);
    mul_s(F0, F0, F29);
    mul_s(F1, F0, F1);
    f2u8(v1, F1);
    charge(9);
    sb(v1, sp, 303);
    // +1600: alpha by the sine of c16.
    a0 = addiu(s0, 1600);
    a1 = addiu(sp, 300);
    jal(0x26FF4Cu, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, 4);
    v0 = 1;
    if (v1 != v0) {
    }
    charge(45);
    lwc1(F0, s0, 12);
    cvt_s_w(F1, F0);
    v0 = lui(0x42B4);  // 90.0
    mtc1(v0, F0);
    div_s(F2, F1, F0);
    v0 = lui(0x4080);  // 4.0
    mtc1(v0, F0);
    mul_s(F1, F0, F2);
    mtc1(zero, F0);
    adda_s(F0, F1);
    msub_s(F1, F1, F2);
    lwc1(F0, gp, -32004);  // 0.2 (the .sdata literal at 0x7CAFEC)
    mul_s(F3, F0, F1);
    v0 = lui(0x3F00);  // 0.5
    mtc1(v0, F2);
    sub_s(F0, F2, F3);
    lwc1(F1, gp, -31856);  // 0.3 (the .sdata literal at 0x7CB080)
    sub_s(F0, F0, F1);
    swc1(F0, sp, 256);
    swc1(F0, sp, 260);
    add_s(F0, F2, F3);
    add_s(F0, F1, F0);
    swc1(F0, sp, 264);
    swc1(F0, sp, 268);
    // +1856: the source rectangle scrolled by c12.
    a0 = addiu(s0, 1856);
    a1 = addiu(sp, 256);
    jal(0x26FFDCu, gen::fn_sub_21EAE0_0021eae0);
    v0 = 255;
    sb(v0, sp, 300);
    sb(v0, sp, 301);
    sb(v0, sp, 302);
    sb(v0, sp, 303);
    a0 = addiu(s0, 1856);
    a1 = addiu(sp, 300);
    jal(0x270000u, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, 4);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
        } else {
            charge(4);
            lw(v0, s0, 8);
            at = slti(v0, 40);
            if (at != 0) {
                charge(3);
                mtc1(zero, F29);
            } else {
                charge(3);
                at = slti(v0, 150);
                if (at != 0) {
                    charge(13);
                    v0 = addiu(v0, -40);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x42DC);  // 110.0
                    mtc1(v0, F0);
                    div_s(F29, F1, F0);
                } else {
                    charge(2);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F29);
                }
            }
            charge(2);
        }
    } else {
        charge(3);
        lw(v0, s0, 8);
        if (ltz(v0)) {
            charge(3);
            mtc1(zero, F1);
        } else {
            charge(3);
            at = slti(v0, 40);
            if (at != 0) {
                charge(12);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x4220);  // 40.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F1);
            }
        }
        charge(4);
        v0 = lui(0x3F80);  // 1.0
        mtc1(v0, F0);
        sub_s(F29, F0, F1);
    }
    charge(48);
    swc1(F29, s0, 4472);
    lwc1(F0, s0, 20);
    cvt_s_w(F1, F0);
    v0 = lui(0x41F0);  // 30.0
    mtc1(v0, F0);
    div_s(F1, F1, F0);
    v0 = lui(0x4000);  // 2.0
    mtc1(v0, F0);
    mul_s(F1, F0, F1);
    lwc1(F0, gp, -32184);  // pi (the .sdata literal at 0x7CAF38)
    mul_s(F31, F0, F1);
    mov_s(F12, F31);
    jal(0x270138u, gen::fn_sinf_0052e878);
    lwc1(F3, gp, -31636);  // 0.05 (the .sdata literal at 0x7CB15C)
    lwc1(F2, gp, -32576);  // 1.1 (the .sdata literal at 0x7CADB0)
    mtc1(zero, F1);
    adda_s(F1, F2);
    madd_s(F30, F3, F0);
    mov_s(F12, F31);
    jal(0x27015Cu, gen::fn_sinf_0052e878);
    lwc1(F3, gp, -31636);  // 0.05 (the .sdata literal at 0x7CB15C)
    lwc1(F2, gp, -32576);  // 1.1 (the .sdata literal at 0x7CADB0)
    mtc1(zero, F1);
    adda_s(F1, F2);
    madd_s(F3, F3, F0);
    sw(zero, sp, 256);
    sw(zero, sp, 260);
    v0 = lui(0x4420);
    sw(v0, sp, 264);
    sw(zero, sp, 268);
    sw(v0, sp, 272);
    v0 = lui(0x43E0);
    sw(v0, sp, 276);
    sw(zero, sp, 280);
    sw(v0, sp, 284);
    v1 = 0;
    v0 = lui(0x43A0);  // 320.0
    mtc1(v0, F2);
    v0 = lui(0x4360);  // 224.0
    mtc1(v0, F1);
    quad_pass(256, QuadOp::Sub, F2, F1);
    charge(3);
    v1 = 0;
    quad_pass(256, QuadOp::Mul, F30, F3);
    charge(7);
    v1 = 0;
    v0 = lui(0x43A0);  // 320.0
    mtc1(v0, F2);
    v0 = lui(0x4360);  // 224.0
    mtc1(v0, F1);
    quad_pass(256, QuadOp::Add, F2, F1);
    charge(18);
    // +2112: the quad waving with c20.
    a0 = addiu(s0, 2112);
    a1 = addiu(sp, 256);
    jal(0x27028Cu, gen::fn_sub_21D890_0021d890);
    white_alpha(300, F29);
    charge(9);
    sb(v1, sp, 303);
    a0 = addiu(s0, 2112);
    a1 = addiu(sp, 300);
    jal(0x270308u, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, 4);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
        } else {
            charge(4);
            lw(v0, s0, 8);
            at = slti(v0, 200);
            if (at != 0) {
                charge(3);
                mtc1(zero, F29);
            } else {
                charge(3);
                at = slti(v0, 220);
                if (at != 0) {
                    charge(13);
                    v0 = addiu(v0, -200);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x41A0);  // 20.0
                    mtc1(v0, F0);
                    div_s(F29, F1, F0);
                } else {
                    charge(2);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F29);
                }
            }
            charge(5);
            mtc1(zero, F28);
            mov_s(F27, F28);
        }
    } else {
        charge(3);
        lw(v0, s0, 8);
        if (ltz(v0)) {
            charge(3);
            mtc1(zero, F1);
        } else {
            charge(3);
            at = slti(v0, 10);
            if (at != 0) {
                charge(12);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x4120);  // 10.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F1);
            }
        }
        charge(12);
        v0 = lui(0x3F80);  // 1.0
        mtc1(v0, F0);
        sub_s(F29, F0, F1);
        v0 = lui(0x42C8);  // 100.0
        mtc1(v0, F0);
        mul_s(F28, F0, F1);
        v0 = lui(0x4248);  // 50.0
        mtc1(v0, F0);
        mul_s(F27, F0, F1);
    }
    charge(39);
    // +2624 and +2368: two image entries.
    a0 = s1;
    a1 = 38;
    jal(0x27043Cu, gen::fn_sub_21CCA0_0021cca0);
    v1 = lui(0x43AF);  // 350.0
    mtc1(v1, F0);
    add_s(F0, F0, F28);
    swc1(F0, sp, 256);
    v1 = 401;
    mtc1(v1, F0);
    cvt_s_w(F0, F0);
    add_s(F31, F0, F27);
    swc1(F31, sp, 260);
    lwc1(F0, v0, 12);
    cvt_s_w(F0, F0);
    swc1(F0, sp, 264);
    lwc1(F0, v0, 16);
    cvt_s_w(F0, F0);
    swc1(F0, sp, 268);
    a0 = addiu(s0, 2624);
    a1 = addiu(sp, 256);
    jal(0x270490u, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 300);
    sb(v0, sp, 301);
    sb(v0, sp, 302);
    v0 = lui(0x437F);  // 255.0
    mtc1(v0, F0);
    mul_s(F30, F0, F29);
    f2u8(v1, F30);
    charge(35);
    sb(v1, sp, 303);
    a0 = addiu(s0, 2624);
    a1 = addiu(sp, 300);
    jal(0x27050Cu, gen::fn_sub_21D950_0021d950);
    a0 = s1;
    a1 = 19;
    jal(0x27051Cu, gen::fn_sub_21CCA0_0021cca0);
    v1 = lui(0x43D0);  // 416.0
    mtc1(v1, F0);
    add_s(F0, F0, F28);
    swc1(F0, sp, 256);
    swc1(F31, sp, 260);
    lwc1(F0, v0, 12);
    cvt_s_w(F0, F0);
    swc1(F0, sp, 264);
    lwc1(F0, v0, 16);
    cvt_s_w(F0, F0);
    swc1(F0, sp, 268);
    a0 = addiu(s0, 2368);
    a1 = addiu(sp, 256);
    jal(0x27055Cu, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 300);
    sb(v0, sp, 301);
    sb(v0, sp, 302);
    f2u8(v1, F30);
    charge(9);
    sb(v1, sp, 303);
    a0 = addiu(s0, 2368);
    a1 = addiu(sp, 300);
    jal(0x2705C8u, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, 4);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
        } else {
            charge(4);
            lw(v0, s0, 8);
            at = slti(v0, 170);
            if (at != 0) {
                charge(3);
                mtc1(zero, F29);
            } else {
                charge(3);
                at = slti(v0, 210);
                if (at != 0) {
                    charge(13);
                    v0 = addiu(v0, -170);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x4220);  // 40.0
                    mtc1(v0, F0);
                    div_s(F29, F1, F0);
                } else {
                    charge(2);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F29);
                }
            }
            charge(5);
            mtc1(zero, F28);
            mov_s(F27, F28);
        }
    } else {
        charge(3);
        lw(v0, s0, 8);
        if (ltz(v0)) {
            charge(3);
            mtc1(zero, F1);
        } else {
            charge(3);
            at = slti(v0, 10);
            if (at != 0) {
                charge(12);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x4120);  // 10.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F1);
            }
        }
        charge(12);
        v0 = lui(0x3F80);  // 1.0
        mtc1(v0, F0);
        sub_s(F29, F0, F1);
        v0 = lui(0xC2C8);  // -100.0
        mtc1(v0, F0);
        mul_s(F28, F0, F1);
        v0 = lui(0xC248);  // -50.0
        mtc1(v0, F0);
        mul_s(F27, F0, F1);
    }
    charge(38);
    // +2880.
    a0 = s1;
    a1 = 10;
    jal(0x2706FCu, gen::fn_sub_21CCA0_0021cca0);
    v1 = lui(0x4140);  // 12.0
    mtc1(v1, F0);
    add_s(F0, F0, F28);
    swc1(F0, sp, 256);
    v1 = lui(0x4170);  // 15.0
    mtc1(v1, F0);
    add_s(F0, F0, F27);
    swc1(F0, sp, 260);
    lwc1(F0, v0, 12);
    cvt_s_w(F0, F0);
    swc1(F0, sp, 264);
    lwc1(F0, v0, 16);
    cvt_s_w(F0, F0);
    swc1(F0, sp, 268);
    a0 = addiu(s0, 2880);
    a1 = addiu(sp, 256);
    jal(0x27074Cu, gen::fn_sub_21D8E0_0021d8e0);
    white_alpha(300, F29);
    charge(9);
    sb(v1, sp, 303);
    a0 = addiu(s0, 2880);
    a1 = addiu(sp, 300);
    jal(0x2707C8u, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, 4);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
        } else {
            charge(4);
            lw(v0, s0, 8);
            at = slti(v0, 210);
            if (at != 0) {
                charge(3);
                mtc1(zero, F29);
            } else {
                charge(3);
                at = slti(v0, 220);
                if (at != 0) {
                    charge(13);
                    v0 = addiu(v0, -210);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x4120);  // 10.0
                    mtc1(v0, F0);
                    div_s(F29, F1, F0);
                } else {
                    charge(2);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F29);
                }
            }
            charge(2);
        }
    } else {
        charge(3);
        lw(v0, s0, 8);
        if (ltz(v0)) {
            charge(3);
            mtc1(zero, F1);
        } else {
            charge(3);
            at = slti(v0, 10);
            if (at != 0) {
                charge(12);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x4120);  // 10.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F1);
            }
        }
        charge(4);
        v0 = lui(0x3F80);  // 1.0
        mtc1(v0, F0);
        sub_s(F29, F0, F1);
    }
    charge(3);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
        } else {
            charge(4);
            lw(v0, s0, 8);
            at = slti(v0, 70);
            if (at != 0) {
                charge(3);
                mtc1(zero, F29);
            } else {
                charge(3);
                at = slti(v0, 150);
                if (at != 0) {
                    charge(13);
                    v0 = addiu(v0, -70);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x42A0);  // 80.0
                    mtc1(v0, F0);
                    div_s(F29, F1, F0);
                } else {
                    charge(2);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F29);
                }
            }
            charge(3);
            mtc1(zero, F26);
        }
    } else {
        charge(3);
        lw(v0, s0, 8);
        if (ltz(v0)) {
            charge(3);
            mtc1(zero, F1);
        } else {
            charge(3);
            at = slti(v0, 30);
            if (at != 0) {
                charge(12);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                v0 = lui(0x41F0);  // 30.0
                mtc1(v0, F0);
                div_s(F1, F1, F0);
            } else {
                charge(2);
                v0 = lui(0x3F80);  // 1.0
                mtc1(v0, F1);
            }
        }
        charge(5);
        v0 = lui(0x3F80);  // 1.0
        mtc1(v0, F0);
        sub_s(F29, F0, F1);
        mtc1(zero, F26);
    }
    charge(46);
    lwc1(F0, s0, 24);
    cvt_s_w(F1, F0);
    v0 = 690;
    mtc1(v0, F0);
    cvt_s_w(F0, F0);
    div_s(F1, F1, F0);
    v0 = lui(0xC396);  // -300.0
    mtc1(v0, F0);
    mul_s(F31, F0, F1);
    add_s(F27, F26, F31);
    // +3392.
    a0 = s1;
    a1 = 16;
    jal(0x2709FCu, gen::fn_sub_21CCA0_0021cca0);
    v0 = 341;
    mtc1(v0, F0);
    cvt_s_w(F0, F0);
    add_s(F0, F0, F27);
    swc1(F0, sp, 256);
    v0 = lui(0x4380);
    sw(v0, sp, 260);
    v0 = lui(0x43BB);
    sw(v0, sp, 264);
    v0 = lui(0x434A);
    sw(v0, sp, 268);
    a0 = addiu(s0, 3392);
    a1 = addiu(sp, 256);
    jal(0x270A3Cu, gen::fn_sub_21D8E0_0021d8e0);
    white_alpha(300, F29);
    charge(8);
    sb(v1, sp, 303);
    a0 = addiu(s0, 3392);
    a1 = addiu(sp, 300);
    jal(0x270AB8u, gen::fn_sub_21D950_0021d950);
    s1 = 0;
    for (;;) {
        charge(3);
        v0 = slti(s1, 3);
        if (v0 == 0) break;
        backedge();
        charge(11);
        v0 = sll(s1, 4);
        v0 = addu(v0, s1);
        v0 = sll(v0, 4);
        v1 = addu(s0, v0);
        v0 = addiu(v1, 3648);
        sq(v0, sp, 240);
        lw(v1, v1, 3648);
        lw(v0, s0, 36);
        at = slt(v0, v1);
        if (at != 0) {
            charge(3);
            mtc1(zero, F29);
        } else {
            charge(4);
            s4 = subu(v0, v1);
            v0 = 2;
            if (s1 != v0) {
                charge(3);
                v0 = 1;
                if (s1 != v0) {
                    charge(2);
                    if (s1 != 0) {
                        charge(2);
                    } else {
                        charge(3);
                        s7 = 100;
                    }
                } else {
                    charge(3);
                    s7 = 100;
                }
            } else {
                charge(1);
                s7 = 100;
            }
            charge(3);
            v0 = 2;
            if (s1 != v0) {
                charge(3);
                v0 = 1;
                if (s1 != v0) {
                    charge(2);
                    if (s1 != 0) {
                        charge(2);
                    } else {
                        charge(3);
                        s3 = 160;
                    }
                } else {
                    charge(3);
                    s3 = 160;
                }
            } else {
                charge(1);
                s3 = 160;
            }
            charge(3);
            v0 = 2;
            if (s1 != v0) {
                charge(3);
                v0 = 1;
                if (s1 != v0) {
                    charge(2);
                    if (s1 != 0) {
                        charge(2);
                    } else {
                        charge(3);
                        s2 = 200;
                    }
                } else {
                    charge(3);
                    s2 = 100;
                }
            } else {
                charge(1);
                s2 = 200;
            }
            charge(3);
            at = slt(s4, s7);
            if (at != 0) {
                charge(12);
                mtc1(s4, F0);
                cvt_s_w(F1, F0);
                mtc1(s7, F0);
                cvt_s_w(F0, F0);
                div_s(F29, F1, F0);
            } else {
                charge(3);
                at = slt(s4, s3);
                if (at != 0) {
                    charge(4);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F29);
                } else {
                    charge(3);
                    at = slt(s4, s2);
                    if (at != 0) {
                        charge(15);
                        v0 = subu(s4, s3);
                        mtc1(v0, F0);
                        cvt_s_w(F1, F0);
                        v0 = subu(s2, s3);
                        mtc1(v0, F0);
                        cvt_s_w(F0, F0);
                        div_s(F1, F1, F0);
                        v0 = lui(0x3F80);  // 1.0
                        mtc1(v0, F0);
                        sub_s(F29, F0, F1);
                    } else {
                        charge(1);
                        mtc1(zero, F29);
                    }
                }
            }
        }
        charge(4);
        lw(v1, s0, 4);
        v0 = 1;
        if (v1 != v0) {  // not page 1: 1.0 (the compare block, then the load block)
            charge(2);
            charge(2);
            v0 = lui(0x3F80);  // 1.0
            mtc1(v0, F27);
        } else {  // page 1: 1 - ramp(timer, 0, 20)
            charge(3);
            lw(v0, s0, 8);
            if (ltz(v0)) {
                charge(3);
                mtc1(zero, F1);
            } else {
                charge(3);
                at = slti(v0, 20);
                if (at != 0) {
                    charge(12);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x41A0);  // 20.0
                    mtc1(v0, F0);
                    div_s(F1, F1, F0);
                } else {
                    charge(2);
                    v0 = lui(0x3F80);  // 1.0
                    mtc1(v0, F1);
                }
            }
            charge(6);
            v0 = lui(0x3F80);  // 1.0
            mtc1(v0, F0);
            sub_s(F27, F0, F1);
        }
        charge(3);
        v0 = 2;
        if (s1 != v0) {
            charge(3);
            v0 = 1;
            if (s1 != v0) {
                charge(2);
                if (s1 != 0) {
                    charge(2);
                } else {
                    charge(10);
                    v0 = lui(0x4344);  // 196.0
                    mtc1(v0, F26);
                    v0 = lui(0x42A8);  // 84.0
                    mtc1(v0, F25);
                    v0 = lui(0xC2E6);  // -115.0
                    mtc1(v0, F31);
                    v0 = lui(0x4369);  // 233.0
                    mtc1(v0, F24);
                }
            } else {
                charge(10);
                v0 = lui(0x42F6);  // 123.0
                mtc1(v0, F26);
                v0 = lui(0x436D);  // 237.0
                mtc1(v0, F25);
                v0 = lui(0xC2F6);  // -123.0
                mtc1(v0, F31);
                v0 = lui(0x41A8);  // 21.0
                mtc1(v0, F24);
            }
        } else {
            charge(10);
            v0 = lui(0xC29A);  // -77.0
            mtc1(v0, F26);
            v0 = lui(0x432D);  // 173.0
            mtc1(v0, F25);
            v0 = 271;
            mtc1(v0, F0);
            cvt_s_w(F31, F0);
            v0 = lui(0x423C);  // 47.0
            mtc1(v0, F24);
        }
        charge(3);
        v0 = 2;
        if (s1 != v0) {
            charge(3);
            v0 = 1;
            if (s1 != v0) {
                charge(2);
                if (s1 != 0) {
                    charge(2);
                } else {
                    charge(3);
                    s2 = 200;
                }
            } else {
                charge(3);
                s2 = 100;
            }
        } else {
            charge(1);
            s2 = 200;
        }
        charge(3);
        v0 = 2;
        if (s1 != v0) {
            charge(3);
            v0 = 1;
            if (s1 != v0) {
                charge(2);
                if (s1 != 0) {
                    charge(2);
                } else {
                    charge(6);
                    v0 = lui(0x4380);  // 256.0
                    mtc1(v0, F23);
                    v0 = lui(0x4300);  // 128.0
                    mtc1(v0, F22);
                }
            } else {
                charge(6);
                v0 = lui(0x4380);  // 256.0
                mtc1(v0, F23);
                v0 = lui(0x4300);  // 128.0
                mtc1(v0, F22);
            }
        } else {
            charge(4);
            v0 = lui(0x4380);  // 256.0
            mtc1(v0, F23);
            mov_s(F22, F23);
        }
        charge(22);
        mtc1(zero, F1);
        sw(zero, sp, 256);
        sw(zero, sp, 260);
        add_s(F0, F1, F23);
        swc1(F0, sp, 264);
        sw(zero, sp, 268);
        swc1(F0, sp, 272);
        add_s(F0, F1, F22);
        swc1(F0, sp, 276);
        sw(zero, sp, 280);
        swc1(F0, sp, 284);
        v0 = lui(0x4000);  // 2.0
        mtc1(v0, F1);
        div_s(F0, F23, F1);
        swc1(F0, sp, 232);
        div_s(F0, F22, F1);
        swc1(F0, sp, 236);
        v0 = 2;
        if (s1 != v0) {
            charge(3);
            v0 = 1;
            if (s1 != v0) {
                charge(2);
                if (s1 != 0) {
                    charge(2);
                } else {
                    charge(4);
                    lwc1(F21, gp, -31632);  // -pi / 6 (the .sdata literal at 0x7CB160)
                    lwc1(F20, gp, -31716);  // pi / 6 (the .sdata literal at 0x7CB10C)
                }
            } else {
                charge(4);
                lwc1(F21, gp, -31632);  // -pi / 6 (the .sdata literal at 0x7CB160)
                lwc1(F20, gp, -31716);  // pi / 6 (the .sdata literal at 0x7CB10C)
            }
        } else {
            charge(2);
            lwc1(F21, gp, -31632);  // -pi / 6 (the .sdata literal at 0x7CB160)
            lwc1(F20, gp, -31716);  // pi / 6 (the .sdata literal at 0x7CB10C)
        }
        charge(25);
        mtc1(s4, F0);
        cvt_s_w(F1, F0);
        mtc1(s2, F0);
        cvt_s_w(F0, F0);
        div_s(F28, F1, F0);
        sub_s(F0, F20, F21);
        mtc1(zero, F1);
        adda_s(F1, F21);
        madd_s(F30, F28, F0);
        sw(zero, sp, 256);
        sw(zero, sp, 260);
        add_s(F0, F1, F23);
        swc1(F0, sp, 264);
        sw(zero, sp, 268);
        swc1(F0, sp, 272);
        add_s(F0, F1, F22);
        swc1(F0, sp, 276);
        sw(zero, sp, 280);
        swc1(F0, sp, 284);
        v1 = 0;
        for (;;) {
            charge(3);
            v0 = slti(v1, 4);
            if (v0 == 0) break;
            backedge();
            charge(12);
            v0 = sll(v1, 3);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 256);
            lwc1(F1, v0, 0);
            lwc1(F0, sp, 232);
            sub_s(F0, F1, F0);
            swc1(F0, v0, 0);
            lwc1(F1, v0, 4);
            lwc1(F0, sp, 236);
            sub_s(F0, F1, F0);
            swc1(F0, v0, 4);
            v1 = addiu(v1, 1);
        }
        charge(3);
        s5 = 0;
        for (;;) {
            charge(3);
            v0 = slti(s5, 4);
            if (v0 == 0) break;
            backedge();
            charge(37);
            v0 = sll(s5, 3);
            v0 = addu(v0, sp);
            s6 = addiu(v0, 256);
            fp = addiu(s6, 4);
            mov_s(F12, F30);
            jal(0x270FB4u, gen::fn_sinf_0052e878);
            swc1(F0, sp, 228);
            lwc1(F0, fp, 0);
            swc1(F0, sp, 224);
            mov_s(F12, F30);
            jal(0x270FCCu, gen::fn_cosf_0052e6d8);
            lwc1(F1, s6, 0);
            mula_s(F1, F0);
            lwc1(F1, sp, 224);
            lwc1(F0, sp, 228);
            msub_s(F0, F1, F0);
            swc1(F0, sp, 220);
            mov_s(F12, F30);
            jal(0x270FF0u, gen::fn_sinf_0052e878);
            swc1(F0, sp, 216);
            lwc1(F0, s6, 0);
            swc1(F0, sp, 212);
            mov_s(F12, F30);
            jal(0x271008u, gen::fn_cosf_0052e6d8);
            lwc1(F1, fp, 0);
            mula_s(F1, F0);
            lwc1(F1, sp, 212);
            lwc1(F0, sp, 216);
            madd_s(F1, F1, F0);
            lwc1(F0, sp, 220);
            swc1(F0, s6, 0);
            swc1(F1, fp, 0);
            s5 = addiu(s5, 1);
        }
        charge(3);
        v1 = 0;
        for (;;) {
            charge(3);
            v0 = slti(v1, 4);
            if (v0 == 0) break;
            backedge();
            charge(12);
            v0 = sll(v1, 3);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 256);
            lwc1(F1, v0, 0);
            lwc1(F0, sp, 232);
            add_s(F0, F1, F0);
            swc1(F0, v0, 0);
            lwc1(F1, v0, 4);
            lwc1(F0, sp, 236);
            add_s(F0, F1, F0);
            swc1(F0, v0, 4);
            v1 = addiu(v1, 1);
        }
        charge(11);
        sub_s(F0, F31, F26);
        mtc1(zero, F1);
        adda_s(F1, F26);
        madd_s(F2, F28, F0);
        sub_s(F0, F24, F25);
        adda_s(F1, F25);
        madd_s(F1, F28, F0);
        v1 = 0;
        quad_pass(256, QuadOp::Add, F2, F1);
        charge(20);
        lq(v0, sp, 240);
        a0 = addiu(v0, 16);
        a1 = addiu(sp, 256);
        jal(0x2710F4u, gen::fn_sub_21D890_0021d890);
        v0 = 255;
        sb(v0, sp, 300);
        sb(v0, sp, 301);
        sb(v0, sp, 302);
        v0 = lui(0x437F);  // 255.0
        mtc1(v0, F0);
        mul_s(F0, F0, F29);
        mul_s(F1, F0, F27);
        f2u8(v1, F1);
        charge(7);
        sb(v1, sp, 303);
        lq(v0, sp, 240);
        a0 = addiu(v0, 16);
        a1 = addiu(sp, 300);
        jal(0x271178u, gen::fn_sub_21D950_0021d950);
        s1 = addiu(s1, 1);
    }
    charge(40);
    sw(s0, sp, 292);
    v0 = lui(0x27);
    v0 = addiu(v0, 4656);
    sw(v0, sp, 288);
    lw(a0, s0, 4464);
    a1 = addiu(sp, 288);
    // The two fade grids: sub_269A10(grid, {visitor, work}) with the visitors sub_271230 (0x271230) and sub_2716D0
    // (0x2716D0).
    jal(0x2711A8u, gen::fn_sub_269A10_00269a10);
    v0 = lui(0x27);
    v0 = addiu(v0, 5840);
    sw(v0, sp, 288);
    lw(a0, s0, 4468);
    a1 = addiu(sp, 288);
    jal(0x2711C4u, gen::fn_sub_269A10_00269a10);
    ld(ra, sp, 192);
    lq(fp, sp, 176);
    lq(s7, sp, 160);
    lq(s6, sp, 144);
    lq(s5, sp, 128);
    lq(s4, sp, 112);
    lq(s3, sp, 96);
    lq(s2, sp, 80);
    lq(s1, sp, 64);
    lq(s0, sp, 48);
    lwc1(F31, sp, 44);
    lwc1(F30, sp, 40);
    lwc1(F29, sp, 36);
    lwc1(F28, sp, 32);
    lwc1(F27, sp, 28);
    lwc1(F26, sp, 24);
    lwc1(F25, sp, 20);
    lwc1(F24, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 304);
    return;
}

}  // namespace big_draws::detail

void sub_183840(EEContext& ctx) { big_draws::detail::Cpu(ctx).sub_183840(); }
void sub_183BE0(EEContext& ctx) { big_draws::detail::Cpu(ctx).sub_183BE0(); }
void sub_183F60(EEContext& ctx) { big_draws::detail::Cpu(ctx).sub_183F60(); }
void sub_267430(EEContext& ctx) { big_draws::detail::Cpu(ctx).sub_267430(); }
void sub_26A2C0(EEContext& ctx) { big_draws::detail::Cpu(ctx).sub_26A2C0(); }
void sub_26EED0(EEContext& ctx) { big_draws::detail::Cpu(ctx).sub_26EED0(); }
}  // namespace p3fes::game
