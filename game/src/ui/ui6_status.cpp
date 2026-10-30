// The camp menu's screens, second pass (slice ui6; game/include/p3fes/game/ui6.h has the records, the role of
// every function and how the screens work): the main list's draws and the Status screen (its page, the persona page, the HP / SP / social-stat / persona
// tables, the persona cards of the facility screens, the persona screen's detail elements, the party-status persona page).
//
// The bodies are p3fes_handgen's (game/include/p3fes/game/hg_cpu.h): one statement per instruction on the guest
// registers, the original's frame, spills, $ra links, cycle charges and check points, so every register the original
// leaves at a check point, call or return is left the same way (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
// This readability pass gives each function its role, each jump-table case its state, names the record offsets,
// $gp words, pad words and sprite-file tables (ui6.h -- each constant equals the literal it replaces), gives the
// value of the float immediates and a note on the callees; it changes no statement. `// 0x00xxxxxx` lines name the
// original basic block a C++ block comes from; the remaining `goto`s jump to blocks the original shares.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/ui6.h"

namespace p3fes::recomp_gen {
void fn_clndGetCurrentDay_0017da40(p3fes::EEContext&);
void fn_clndGetCurrentMonth_0017d920(p3fes::EEContext&);
void fn_clndGetCurrentWeekDay_0017db00(p3fes::EEContext&);
void fn_clndIsHolidayOrSunday_0017dcf0(p3fes::EEContext&);
void fn_datGetAcademicLevel_00177280(p3fes::EEContext&);
void fn_datGetCharmLevel_001772f0(p3fes::EEContext&);
void fn_datGetCourageLevel_00177360(p3fes::EEContext&);
void fn_datGetTime_0016ef30(p3fes::EEContext&);
void fn_datPersonaGetByPcId_00174800(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_nullsub_3_0011bba0(p3fes::EEContext&);
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);
void fn_sprDrawSpriteBasic_001159f0(p3fes::EEContext&);
void fn_sprFontGetFile_001120a0(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_10C1A0_0010c1a0(p3fes::EEContext&);
void fn_sub_10C3A0_0010c3a0(p3fes::EEContext&);
void fn_sub_1127D0_001127d0(p3fes::EEContext&);
void fn_sub_113A30_00113a30(p3fes::EEContext&);
void fn_sub_114450_00114450(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_115AD0_00115ad0(p3fes::EEContext&);
void fn_sub_11BBB0_0011bbb0(p3fes::EEContext&);
void fn_sub_11C880_0011c880(p3fes::EEContext&);
void fn_sub_11CFB0_0011cfb0(p3fes::EEContext&);
void fn_sub_11D3A0_0011d3a0(p3fes::EEContext&);
void fn_sub_11D6D0_0011d6d0(p3fes::EEContext&);
void fn_sub_11DDB0_0011ddb0(p3fes::EEContext&);
void fn_sub_11DFE0_0011dfe0(p3fes::EEContext&);
void fn_sub_11E380_0011e380(p3fes::EEContext&);
void fn_sub_121DE0_00121de0(p3fes::EEContext&);
void fn_sub_122710_00122710(p3fes::EEContext&);
void fn_sub_1236A0_001236a0(p3fes::EEContext&);
void fn_sub_123B70_00123b70(p3fes::EEContext&);
void fn_sub_123F80_00123f80(p3fes::EEContext&);
void fn_sub_124090_00124090(p3fes::EEContext&);
void fn_sub_124370_00124370(p3fes::EEContext&);
void fn_sub_124B30_00124b30(p3fes::EEContext&);
void fn_sub_124E60_00124e60(p3fes::EEContext&);
void fn_sub_124FD0_00124fd0(p3fes::EEContext&);
void fn_sub_125B40_00125b40(p3fes::EEContext&);
void fn_sub_125D70_00125d70(p3fes::EEContext&);
void fn_sub_126710_00126710(p3fes::EEContext&);
void fn_sub_1269A0_001269a0(p3fes::EEContext&);
void fn_sub_1273B0_001273b0(p3fes::EEContext&);
void fn_sub_127C00_00127c00(p3fes::EEContext&);
void fn_sub_128140_00128140(p3fes::EEContext&);
void fn_sub_1281E0_001281e0(p3fes::EEContext&);
void fn_sub_128480_00128480(p3fes::EEContext&);
void fn_sub_128720_00128720(p3fes::EEContext&);
void fn_sub_128C40_00128c40(p3fes::EEContext&);
void fn_sub_129160_00129160(p3fes::EEContext&);
void fn_sub_1293B0_001293b0(p3fes::EEContext&);
void fn_sub_129B30_00129b30(p3fes::EEContext&);
void fn_sub_12A560_0012a560(p3fes::EEContext&);
void fn_sub_12AC60_0012ac60(p3fes::EEContext&);
void fn_sub_12B300_0012b300(p3fes::EEContext&);
void fn_sub_12B860_0012b860(p3fes::EEContext&);
void fn_sub_12BFB0_0012bfb0(p3fes::EEContext&);
void fn_sub_133180_00133180(p3fes::EEContext&);
void fn_sub_133460_00133460(p3fes::EEContext&);
void fn_sub_1339A0_001339a0(p3fes::EEContext&);
void fn_sub_133A80_00133a80(p3fes::EEContext&);
void fn_sub_1345B0_001345b0(p3fes::EEContext&);
void fn_sub_134900_00134900(p3fes::EEContext&);
void fn_sub_167930_00167930(p3fes::EEContext&);
void fn_sub_1685E0_001685e0(p3fes::EEContext&);
void fn_sub_16C470_0016c470(p3fes::EEContext&);
void fn_sub_16C4F0_0016c4f0(p3fes::EEContext&);
void fn_sub_16C570_0016c570(p3fes::EEContext&);
void fn_sub_16C5F0_0016c5f0(p3fes::EEContext&);
void fn_sub_16C670_0016c670(p3fes::EEContext&);
void fn_sub_16C6F0_0016c6f0(p3fes::EEContext&);
void fn_sub_16C740_0016c740(p3fes::EEContext&);
void fn_sub_16C790_0016c790(p3fes::EEContext&);
void fn_sub_16C860_0016c860(p3fes::EEContext&);
void fn_sub_16D2F0_0016d2f0(p3fes::EEContext&);
void fn_sub_16DD50_0016dd50(p3fes::EEContext&);
void fn_sub_173280_00173280(p3fes::EEContext&);
void fn_sub_173330_00173330(p3fes::EEContext&);
void fn_sub_173340_00173340(p3fes::EEContext&);
void fn_sub_173580_00173580(p3fes::EEContext&);
void fn_sub_173660_00173660(p3fes::EEContext&);
void fn_sub_174A90_00174a90(p3fes::EEContext&);
void fn_sub_177790_00177790(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_18B700_0018b700(p3fes::EEContext&);
void fn_sub_1FB1F0_001fb1f0(p3fes::EEContext&);
void fn_sub_1FC230_001fc230(p3fes::EEContext&);
void fn_sub_1FC3C0_001fc3c0(p3fes::EEContext&);
void fn_sub_3B32D0_003b32d0(p3fes::EEContext&);
void fn_sub_40EB50_0040eb50(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace ui6;  // the record offsets, $gp words, pad words and sprite tables of ui6.h

// 0x0011BBB0 sub_11BBB0 -- 2464 bytes; frame 0x170: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_RootDrawList] (root work): draws the camp main list from the tween records at gp-19876: rows 0..6 (sub_115AD0
// of camp sprite file 4, row 5 greyed in The Answer), the cursor bar (record 10), the selection caption (record 11,
// sprite 7 + cursor), the date panel (record 12: the time-of-day icon from datGetTime -- holiday / Sunday variants
// through clndIsHolidayOrSunday --, the month and day as digits of sprite font 1, the weekday), the side panels (record
// 13) and the money (record 14: datGetMoney through sprintf + sub_40EB50).
void sub_11BBB0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x0011bbb0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x170);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    mov_s(f21, f12);
    s2 = 0;
    for (;;) {
        // 0x0011bdb0
        charge(ctx, 3);
        v0 = slti(s2, 7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0011bbec
        charge(ctx, 9);
        v0 = sll(s2, 4);
        v0 = addu(v0, s2);
        v1 = sll(v0, 2);
        lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
        a0 = addu(v0, v1);
        jal(ctx, 0x11BC00u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
        if (v0 != 0) {
            // 0x0011bc10
            charge(ctx, 11);
            lw(v1, gp, g::kCampTweens);  // 0x7CDF4C
            v0 = sll(s2, 4);
            v0 = addu(v0, s2);
            v0 = sll(v0, 2);
            v0 = addu(v1, v0);
            lwc1(f22, v0, 56);
            lwc1(f20, v0, 60);
            lw(s0, v0, 64);
            v0 = 5;
            if (s2 != v0) {
                // 0x0011bd3c
                charge(ctx, 28);
                v0 = 0x41D80000;  // 27.0f
                mtc1(v0, f0);
                sub_s(f12, f22, f0);
                v0 = 0x40000000;  // 2.0f
                mtc1(v0, f0);
                add_s(f13, f0, f20);
                t0 = s0 & 0xFF;
                a0 = s3;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(4));  // 0x833B80: camp sprite file 4
                a2 = 16;
                a3 = 0;
                mov_s(f14, f21);
                jal(ctx, 0x11BD78u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                t0 = s0 & 0xFF;
                a0 = s3;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(4));  // 0x833B80: camp sprite file 4
                a2 = s2;
                mov_s(f12, f22);
                mov_s(f13, f20);
                a3 = 0;
                mov_s(f14, f21);
                jal(ctx, 0x11BDA4u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
            } else {
                // 0x0011bc3c
                charge(ctx, 4);
                jal(ctx, 0x11BC3Cu, gen::fn_sub_17D800_0017d800);  // 1 in The Answer
                if (v0 == 0) {
                    // 0x0011bcc4
                    charge(ctx, 30);
                    v0 = 0x41D80000;  // 27.0f
                    mtc1(v0, f0);
                    sub_s(f12, f22, f0);
                    v0 = 0x40000000;  // 2.0f
                    mtc1(v0, f0);
                    add_s(f13, f0, f20);
                    t0 = s0 & 0xFF;
                    a0 = s3;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(4));  // 0x833B80: camp sprite file 4
                    a2 = 16;
                    a3 = 0;
                    mov_s(f14, f21);
                    jal(ctx, 0x11BD00u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                    t0 = s0 & 0xFF;
                    a0 = s3;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(4));  // 0x833B80: camp sprite file 4
                    a2 = s2;
                    mov_s(f12, f22);
                    mov_s(f13, f20);
                    a3 = 0;
                    mov_s(f14, f21);
                    jal(ctx, 0x11BD2Cu, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                } else {
                    // 0x0011bc4c
                    charge(ctx, 30);
                    v0 = 0x41D80000;  // 27.0f
                    mtc1(v0, f0);
                    sub_s(f12, f22, f0);
                    v0 = 0x40000000;  // 2.0f
                    mtc1(v0, f0);
                    add_s(f13, f0, f20);
                    t0 = s0 & 0xFF;
                    a0 = s3;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(4));  // 0x833B80: camp sprite file 4
                    a2 = 16;
                    a3 = 128;
                    mov_s(f14, f21);
                    jal(ctx, 0x11BC88u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                    t0 = s0 & 0xFF;
                    a0 = s3;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(4));  // 0x833B80: camp sprite file 4
                    a2 = s2;
                    mov_s(f12, f22);
                    mov_s(f13, f20);
                    a3 = 128;
                    mov_s(f14, f21);
                    jal(ctx, 0x11BCB4u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                }
            }
        }
        // 0x0011bdac
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0011bdbc
    charge(ctx, 6);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 680);
    jal(ctx, 0x11BDC4u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
    if (v0 != 0) {
        // 0x0011bdd4
        charge(ctx, 12);
        lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
        lwc1(f12, v0, 736);
        lwc1(f13, v0, 740);
        lbu(t0, v0, 744);
        a0 = s3;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(4));  // 0x833B80: camp sprite file 4
        a2 = 14;
        a3 = 0;
        mov_s(f14, f21);
        jal(ctx, 0x11BDFCu, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
    }
    // 0x0011be04
    charge(ctx, 6);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 748);
    jal(ctx, 0x11BE0Cu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
    if (v0 != 0) {
        // 0x0011be1c
        charge(ctx, 30);
        lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
        lwc1(f22, v0, 804);
        lwc1(f20, v0, 808);
        lw(s0, v0, 812);
        v0 = 0x41D80000;  // 27.0f
        mtc1(v0, f0);
        sub_s(f12, f22, f0);
        t0 = s0 & 0xFF;
        a0 = s3;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(4));  // 0x833B80: camp sprite file 4
        a2 = 17;
        mov_s(f13, f20);
        a3 = 0;
        mov_s(f14, f21);
        jal(ctx, 0x11BE5Cu, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
        lw(v0, s4, root::kCursor);
        a2 = addiu(v0, 7);
        t0 = s0 & 0xFF;
        a0 = s3;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(4));  // 0x833B80: camp sprite file 4
        mov_s(f12, f22);
        mov_s(f13, f20);
        a3 = 0;
        mov_s(f14, f21);
        jal(ctx, 0x11BE8Cu, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
    }
    // 0x0011be94
    charge(ctx, 6);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 816);
    jal(ctx, 0x11BE9Cu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
    if (v0 != 0) {
        // 0x0011beac
        charge(ctx, 49);
        lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
        lwc1(f20, v0, 872);
        lwc1(f22, v0, 876);
        lw(s0, v0, 880);
        t0 = s0 & 0xFF;
        a0 = s3;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
        a2 = 0;
        mov_s(f12, f20);
        mov_s(f13, f22);
        a3 = 0;
        mov_s(f14, f21);
        jal(ctx, 0x11BEE0u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
        v0 = 0x42EA0000;  // 117.0f
        mtc1(v0, f0);
        add_s(f12, f0, f20);
        t0 = s0 & 0xFF;
        a0 = s3;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
        a2 = 1;
        mov_s(f13, f22);
        a3 = 0;
        mov_s(f14, f21);
        jal(ctx, 0x11BF18u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
        v0 = 0x431F0000;  // 159.0f
        mtc1(v0, f0);
        add_s(f12, f0, f20);
        t0 = s0 & 0xFF;
        a0 = s3;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
        a2 = 2;
        mov_s(f13, f22);
        a3 = 0;
        mov_s(f14, f21);
        jal(ctx, 0x11BF50u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
        jal(ctx, 0x11BF58u, gen::fn_datGetTime_0016ef30);
        v0 = v0 & 0xFF;
        at = sltiu(v0, 9);
        if (at != 0) {
            // 0x0011bf70
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 21712);  // &0x7B54D0
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x11BF8Cu:  // table[1]: morning: icon 28
                // 0x0011bf8c
                charge(ctx, 3);
                s1 = 28;
                break;
            case 0x11BF98u:  // table[2]: lunch: icon 29 (35 on a holiday / Sunday)
                // 0x0011bf98
                charge(ctx, 5);
                s1 = 29;
                jal(ctx, 0x11BF9Cu, gen::fn_clndIsHolidayOrSunday_0017dcf0);
                if (v0 != 0) {
                    // 0x0011bfac
                    charge(ctx, 3);
                    s1 = 35;
                }
                break;
            case 0x11BFB8u:  // table[3]: afternoon: icon 31 (35 on a holiday / Sunday)
                // 0x0011bfb8
                charge(ctx, 5);
                s1 = 31;
                jal(ctx, 0x11BFBCu, gen::fn_clndIsHolidayOrSunday_0017dcf0);
                if (v0 != 0) {
                    // 0x0011bfcc
                    charge(ctx, 3);
                    s1 = 35;
                }
                break;
            case 0x11BFD8u:  // table[4]: after school: icon 30 (35 ...)
                // 0x0011bfd8
                charge(ctx, 5);
                s1 = 30;
                jal(ctx, 0x11BFDCu, gen::fn_clndIsHolidayOrSunday_0017dcf0);
                if (v0 != 0) {
                    // 0x0011bfec
                    charge(ctx, 3);
                    s1 = 35;
                }
                break;
            case 0x11BFF8u:  // table[5]: evening: icon 32 (35 ...)
                // 0x0011bff8
                charge(ctx, 5);
                s1 = 32;
                jal(ctx, 0x11BFFCu, gen::fn_clndIsHolidayOrSunday_0017dcf0);
                if (v0 != 0) {
                    // 0x0011c00c
                    charge(ctx, 3);
                    s1 = 35;
                }
                break;
            case 0x11C018u:  // table[6]: dark hour: icon 33
                // 0x0011c018
                charge(ctx, 3);
                s1 = 33;
                break;
            case 0x11C024u:  // table[0, 7]: early morning: icon 34; icon 34
                // 0x0011c024
                charge(ctx, 3);
                s1 = 34;
                break;
            case 0x11C030u:  // table[8]: icon 36
                // 0x0011c030
                charge(ctx, 1);
                s1 = 36;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x0011c034
        charge(ctx, 43);
        v0 = 0x43A00000;  // 320.0f
        mtc1(v0, f0);
        add_s(f1, f20, f0);
        v0 = 0x42240000;  // 41.0f
        mtc1(v0, f0);
        sub_s(f20, f1, f0);
        v0 = 0x41880000;  // 17.0f
        mtc1(v0, f0);
        add_s(f1, f22, f0);
        v0 = 0x41300000;  // 11.0f
        mtc1(v0, f0);
        sub_s(f13, f1, f0);
        t0 = s0 & 0xFF;
        a0 = s3;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(5));  // 0x833B84: camp sprite file 5
        a2 = s1;
        mov_s(f12, f20);
        a3 = 100;
        mov_s(f14, f21);
        jal(ctx, 0x11C094u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
        v0 = 0x41F00000;  // 30.0f
        mtc1(v0, f0);
        add_s(f1, f22, f0);
        v0 = 0x41300000;  // 11.0f
        mtc1(v0, f0);
        sub_s(f1, f1, f0);
        v0 = 0x40000000;  // 2.0f
        mtc1(v0, f0);
        sub_s(f22, f1, f0);
        jal(ctx, 0x11C0CCu, gen::fn_clndGetCurrentMonth_0017d920);
        v0 = slti(v0, 10);
        if (v0 == 0) {
            // 0x0011c0e0
            charge(ctx, 23);
            a0 = 1;
            jal(ctx, 0x11C0E4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            s1 = v0;
            jal(ctx, 0x11C0F0u, gen::fn_clndGetCurrentMonth_0017d920);
            v1 = 10;
            div(v0, v1);
            mflo(v0);
            a2 = addiu(v0, 11);
            t0 = s0 & 0xFF;
            a0 = s3;
            a1 = s1;
            mov_s(f12, f20);
            mov_s(f13, f22);
            a3 = 120;
            mov_s(f14, f21);
            jal(ctx, 0x11C124u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
            v0 = 0x41800000;  // 16.0f
            mtc1(v0, f0);
            add_s(f20, f20, f0);
        }
        // 0x0011c13c
        charge(ctx, 43);
        a0 = 1;
        jal(ctx, 0x11C140u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
        s1 = v0;
        jal(ctx, 0x11C14Cu, gen::fn_clndGetCurrentMonth_0017d920);
        v1 = 10;
        div(v0, v1);
        mfhi(v0);
        a2 = addiu(v0, 11);
        t0 = s0 & 0xFF;
        a0 = s3;
        a1 = s1;
        mov_s(f12, f20);
        mov_s(f13, f22);
        a3 = 120;
        mov_s(f14, f21);
        jal(ctx, 0x11C180u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
        v0 = 0x41880000;  // 17.0f
        mtc1(v0, f0);
        add_s(f20, f20, f0);
        t0 = s0 & 0xFF;
        a0 = s3;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(5));  // 0x833B84: camp sprite file 5
        a2 = 45;
        mov_s(f12, f20);
        mov_s(f13, f22);
        a3 = 120;
        mov_s(f14, f21);
        jal(ctx, 0x11C1BCu, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
        v0 = 0x41200000;  // 10.0f
        mtc1(v0, f0);
        add_s(f20, f20, f0);
        jal(ctx, 0x11C1D4u, gen::fn_clndGetCurrentDay_0017da40);
        v0 = slti(v0, 10);
        if (v0 == 0) {
            // 0x0011c1e8
            charge(ctx, 23);
            a0 = 1;
            jal(ctx, 0x11C1ECu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            s1 = v0;
            jal(ctx, 0x11C1F8u, gen::fn_clndGetCurrentDay_0017da40);
            v1 = 10;
            div(v0, v1);
            mflo(v0);
            a2 = addiu(v0, 11);
            t0 = s0 & 0xFF;
            a0 = s3;
            a1 = s1;
            mov_s(f12, f20);
            mov_s(f13, f22);
            a3 = 120;
            mov_s(f14, f21);
            jal(ctx, 0x11C22Cu, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
            v0 = 0x41700000;  // 15.0f
            mtc1(v0, f0);
            add_s(f20, f20, f0);
        }
        // 0x0011c244
        charge(ctx, 28);
        a0 = 1;
        jal(ctx, 0x11C248u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
        s1 = v0;
        jal(ctx, 0x11C254u, gen::fn_clndGetCurrentDay_0017da40);
        v1 = 10;
        div(v0, v1);
        mfhi(v0);
        a2 = addiu(v0, 11);
        t0 = s0 & 0xFF;
        a0 = s3;
        a1 = s1;
        mov_s(f12, f20);
        mov_s(f13, f22);
        a3 = 120;
        mov_s(f14, f21);
        jal(ctx, 0x11C288u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
        v0 = 0x41A00000;  // 20.0f
        mtc1(v0, f0);
        add_s(f20, f20, f0);
        jal(ctx, 0x11C2A0u, gen::fn_clndGetCurrentWeekDay_0017db00);
        at = sltiu(v0, 7);
        if (at != 0) {
            // 0x0011c2b4
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 21680);  // &0x7B54B0
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x11C2D0u:  // table[0]: Sunday: sprite 27
                // 0x0011c2d0
                charge(ctx, 3);
                s2 = 27;
                break;
            case 0x11C2DCu:  // table[1]: Monday: 21
                // 0x0011c2dc
                charge(ctx, 3);
                s2 = 21;
                break;
            case 0x11C2E8u:  // table[2]: Tuesday: 22
                // 0x0011c2e8
                charge(ctx, 3);
                s2 = 22;
                break;
            case 0x11C2F4u:  // table[3]: Wednesday: 23
                // 0x0011c2f4
                charge(ctx, 3);
                s2 = 23;
                break;
            case 0x11C300u:  // table[4]: Thursday: 24
                // 0x0011c300
                charge(ctx, 3);
                s2 = 24;
                break;
            case 0x11C30Cu:  // table[5]: Friday: 25
                // 0x0011c30c
                charge(ctx, 3);
                s2 = 25;
                break;
            case 0x11C318u:  // table[6]: Saturday: 26
                // 0x0011c318
                charge(ctx, 1);
                s2 = 26;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x0011c31c
        charge(ctx, 11);
        t0 = s0 & 0xFF;
        a0 = s3;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(5));  // 0x833B84: camp sprite file 5
        a2 = s2;
        mov_s(f12, f20);
        mov_s(f13, f22);
        a3 = 120;
        mov_s(f14, f21);
        jal(ctx, 0x11C340u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
    }
    // 0x0011c348
    charge(ctx, 6);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 884);
    jal(ctx, 0x11C350u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
    if (v0 != 0) {
        // 0x0011c360
        charge(ctx, 59);
        lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
        lwc1(f22, v0, 940);
        lwc1(f20, v0, 944);
        lw(s0, v0, 948);
        a3 = s0 & 0xFF;
        a0 = s3;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
        a2 = 0;
        mov_s(f12, f22);
        mov_s(f13, f20);
        mov_s(f14, f21);
        jal(ctx, 0x11C390u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lw(v0, s4, root::kCursor);
        a2 = addiu(v0, 1);
        v0 = 0x41800000;  // 16.0f
        mtc1(v0, f0);
        add_s(f12, f0, f22);
        a3 = s0 & 0xFF;
        a0 = s3;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
        mov_s(f13, f20);
        mov_s(f14, f21);
        jal(ctx, 0x11C3C8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x43E10000;  // 450.0f
        mtc1(v0, f0);
        add_s(f12, f0, f22);
        a3 = s0 & 0xFF;
        a0 = s3;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
        a2 = 0;
        mov_s(f13, f20);
        mov_s(f14, f21);
        jal(ctx, 0x11C3FCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 561;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f0, f22);
        v0 = 0x42300000;  // 44.0f
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        a3 = s0 & 0xFF;
        a0 = s3;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
        a2 = 1;
        mov_s(f13, f20);
        mov_s(f14, f21);
        jal(ctx, 0x11C444u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x0011c44c
    charge(ctx, 6);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 952);
    jal(ctx, 0x11C454u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
    if (v0 != 0) {
        // 0x0011c464
        charge(ctx, 47);
        lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
        lwc1(f12, v0, 1008);
        lwc1(f13, v0, 1012);
        lw(s0, v0, 1016);
        a3 = s0 & 0xFF;
        a0 = s3;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
        a2 = 2;
        mov_s(f14, f21);
        jal(ctx, 0x11C48Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lw(v1, gp, g::kCampTweens);  // 0x7CDF4C
        lwc1(f1, v1, 1008);
        v0 = 0x43190000;  // 153.0f
        mtc1(v0, f0);
        add_s(f22, f0, f1);
        lwc1(f20, v1, 1012);
        jal(ctx, 0x11C4B0u, gen::fn_sub_16DD50_0016dd50);  // [datGetMoney]
        a0 = addiu(sp, 0x70);
        a1 = addiu(gp, -30344);  // "%d"
        a2 = v0;
        jal(ctx, 0x11C4C4u, gen::fn_sprintf_00523ac8);
        v0 = 0x40000000;  // 2.0f
        mtc1(v0, f0);
        sub_s(f0, f22, f0);
        cvt_w_s(f0, f0);
        mfc1(a0, f0);
        v0 = 0x40400000;  // 3.0f
        mtc1(v0, f0);
        add_s(f0, f0, f20);
        cvt_w_s(f0, f0);
        mfc1(a1, f0);
        v0 = 255;
        v0 = subu(v0, s0);
        a2 = v0 & 0xFF;
        mov_s(f12, f21);
        a3 = 4;
        t0 = addiu(sp, 0x70);
        t1 = 9;
        jal(ctx, 0x11C518u, gen::fn_sub_40EB50_0040eb50);  // text / number at (x, y)
    }
    // 0x0011c520 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x170);
}

// 0x0011C880 sub_11C880 -- 1024 bytes; frame 0x60: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [H_Camp_RootDrawOpen] (root work, z in $f12): the main list's open animation frame: frames 16..21 fade the persona
// background (sub_114450 on the CampPersonaTexControl texture, gp-19856) and the black curtain in, frames 12..21 slide
// the frame sprite (camp file 2) in; then the list (sub_11BBB0).
void sub_11C880(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20};
    // 0x0011c880
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a0;
    mov_s(f20, f12);
    lw(v1, a0, 4);
    v0 = slti(v1, 16);
    if (v0 == 0) {
        // 0x0011c8b4
        charge(ctx, 3);
        at = slti(v1, 22);
        if (at != 0) {
            // 0x0011c8c0
            charge(ctx, 4);
            s2 = addiu(v1, -16);
            at = slti(s2, 4);
            if (at == 0) {
                // 0x0011c8d0
                charge(ctx, 10);
                v0 = addiu(s2, -3);
                v0 = sll(v0, 7);
                a0 = 3;
                div(v0, a0);
                mflo(v1);
                v0 = 256;
                s1 = subu(v0, v1);
                lw(v0, gp, g::kPersonaTexTask);  // 0x7CDF60
                if (v0 != 0) {
                    // 0x0011c904
                    charge(ctx, 4);
                    lw(v1, v0, 60);
                    lw(v0, v1, 0);
                    if (v0 != a0) {
                        // 0x0011c920
                        charge(ctx, 1);
                        t0 = 0;
                    } else {
                        // 0x0011c914
                        charge(ctx, 3);
                        lw(t0, v1, 12);
                    }
                } else {
                    // 0x0011c8f8
                    charge(ctx, 3);
                    t0 = 0;
                }
                // 0x0011c924
                charge(ctx, 2);
                if (t0 != 0) {
                    // 0x0011c92c
                    charge(ctx, 8);
                    v1 = dsll32(s1, 16);
                    v1 = dsra32(v1, 16);
                    v0 = 255;
                    v1 = subu(v0, v1);
                    a1 = v1;
                    v0 = sltiu(v1, 25);
                    if (v0 == 0) {
                        // 0x0011c94c
                        charge(ctx, 1);
                        a1 = 25;
                    }
                    // 0x0011c950
                    charge(ctx, 16);
                    v0 = 0x40A00000;  // 5.0f
                    mtc1(v0, f0);
                    add_s(f12, f0, f20);
                    v0 = si(-256);
                    a0 = v1 | v0;
                    v0 = 0x4FA40000;
                    v0 = v0 | 0xFF00;
                    a1 = a1 | v0;
                    mtc1(zero, f13);
                    v0 = lui(0xC2AE);
                    mtc1(v0, f14);
                    a2 = 640;
                    a3 = a2;
                    jal(ctx, 0x11C988u, gen::fn_sub_114450_00114450);  // [nine-slice window] / the persona picture
                }
                // 0x0011c990
                charge(ctx, 11);
                mtc1(zero, f12);
                v0 = 0x40A00000;  // 5.0f
                mtc1(v0, f0);
                add_s(f14, f0, f20);
                a0 = dsll32(s1, 16);
                a0 = dsra32(a0, 16);
                mov_s(f13, f12);
                a1 = 4096;
                jal(ctx, 0x11C9B4u, gen::fn_nullsub_3_0011bba0);
            }
            // 0x0011c9bc
            charge(ctx, 13);
            v0 = sll(s2, 2);
            v1 = addu(v0, s2);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 1);
            v0 = 6;
            div(v1, v0);
            mflo(v1);
            v0 = 50;
            a1 = subu(v0, v1);
            lw(v0, gp, g::kPersonaTexTask);  // 0x7CDF60
            if (v0 != 0) {
                // 0x0011c9fc
                charge(ctx, 5);
                lw(a0, v0, 60);
                lw(v1, a0, 0);
                v0 = 3;
                if (v1 != v0) {
                    // 0x0011ca1c
                    charge(ctx, 1);
                    t0 = 0;
                } else {
                    // 0x0011ca10
                    charge(ctx, 3);
                    lw(t0, a0, 12);
                }
            } else {
                // 0x0011c9f0
                charge(ctx, 3);
                t0 = 0;
            }
            // 0x0011ca20
            charge(ctx, 2);
            if (t0 != 0) {
                // 0x0011ca28
                charge(ctx, 9);
                mtc1(a1, f0);
                cvt_s_w(f13, f0);
                v1 = subu(0, a1);
                v0 = sll(v1, 1);
                v1 = addu(v0, v1);
                v0 = sra(v1, 1);
                if (i64(v1) < 0) {
                    // 0x0011ca4c
                    charge(ctx, 2);
                    v0 = addiu(v1, 1);
                    v0 = sra(v0, 1);
                }
                // 0x0011ca54
                charge(ctx, 18);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = lui(0xC2AE);
                mtc1(v0, f0);
                add_s(f14, f0, f1);
                v0 = 0x40800000;  // 4.0f
                mtc1(v0, f0);
                add_s(f12, f0, f20);
                a0 = si(-129);
                v0 = 0x4FA40000;
                a1 = v0 | 0xFF19;
                a2 = 640;
                a3 = a2;
                jal(ctx, 0x11CA94u, gen::fn_sub_114450_00114450);  // [nine-slice window] / the persona picture
            }
        }
    }
    // 0x0011ca9c
    charge(ctx, 4);
    lw(v1, s0, root::kTimer);
    v0 = slti(v1, 12);
    if (v0 == 0) {
        // 0x0011caac
        charge(ctx, 3);
        at = slti(v1, 22);
        if (at != 0) {
            // 0x0011cab8
            charge(ctx, 4);
            s3 = addiu(v1, -12);
            at = slti(s3, 6);
            if (at == 0) {
                // 0x0011cac8
                charge(ctx, 36);
                v0 = addiu(s3, -5);
                v1 = sll(v0, 7);
                v0 = 5;
                div(v1, v0);
                mflo(v1);
                v0 = 256;
                s1 = subu(v0, v1);
                a0 = 0;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(2));  // 0x833B78: camp sprite file 2
                a2 = 0;
                jal(ctx, 0x11CAF4u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                s2 = v0;
                v1 = 0x40400000;  // 3.0f
                mtc1(v1, f0);
                add_s(f0, f0, f20);
                swc1(f0, v0, 44);
                v1 = 0x43D60000;  // 428.0f
                sw(v1, v0, 16);
                v1 = 0x41D80000;  // 27.0f
                sw(v1, v0, 20);
                v1 = dsll32(s1, 16);
                v1 = dsra32(v1, 16);
                sb(v1, v0, 24);
                v1 = 4096;
                sh(v1, v0, 40);
                sh(v1, v0, 42);
                a0 = s2;
                a1 = 1;
                jal(ctx, 0x11CB44u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                a0 = s2;
                jal(ctx, 0x11CB50u, gen::fn_sub_115980_00115980);  // draw and release the handle
            }
            // 0x0011cb58
            charge(ctx, 40);
            v0 = sll(s3, 2);
            v1 = addu(v0, s3);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v0 = sll(v0, 2);
            a0 = 10;
            div(v0, a0);
            mflo(v1);
            v0 = 100;
            s2 = subu(v0, v1);
            v0 = sll(s3, 11);
            div1(v0, a0);
            mflo1(v1);
            v0 = 6144;
            s1 = subu(v0, v1);
            a0 = 0;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(2));  // 0x833B78: camp sprite file 2
            a2 = 0;
            jal(ctx, 0x11CBA4u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
            s3 = v0;
            v1 = 0x40000000;  // 2.0f
            mtc1(v1, f0);
            add_s(f0, f0, f20);
            swc1(f0, v0, 44);
            v1 = 0x43D60000;  // 428.0f
            mtc1(v1, f1);
            mtc1(s2, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, v0, 16);
            v1 = subu(0, s2);
            v0 = sll(v1, 1);
            v1 = addu(v0, v1);
            v0 = sra(v1, 1);
            if (i64(v1) < 0) {
                // 0x0011cbf8
                charge(ctx, 2);
                v0 = addiu(v1, 1);
                v0 = sra(v0, 1);
            }
            // 0x0011cc00
            charge(ctx, 19);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41D80000;  // 27.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, s3, 20);
            v0 = 128;
            sb(v0, s3, 24);
            sh(s1, s3, 40);
            sh(s1, s3, 42);
            a0 = s3;
            a1 = 1;
            jal(ctx, 0x11CC38u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
            a0 = s3;
            jal(ctx, 0x11CC44u, gen::fn_sub_115980_00115980);  // draw and release the handle
        }
    }
    // 0x0011cc4c
    charge(ctx, 13);
    a0 = s0;
    mov_s(f12, f20);
    jal(ctx, 0x11CC54u, gen::fn_sub_11BBB0_0011bbb0);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0011CFB0 sub_11CFB0 -- 1004 bytes; frame 0x70: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_RootDrawConfirm] (root work, z in $f12): the 22-frame confirm flash after a selection (state 0xA): the
// background fading out over 10 frames, the frame sprite, the scrolling side strip (+32 moving by 1, wrapping at 767 by
// -448, file 7 sprites 3 / 4) and the list.
void sub_11CFB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x0011cfb0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s3 = a0;
    mov_s(f20, f12);
    lw(v1, a0, 4);
    v0 = slti(v1, 10);
    if (v0 != 0) {
        // 0x0011cff8
        charge(ctx, 5);
        v0 = sll(v1, 8);
        v1 = subu(v0, v1);
        v0 = 10;
        div(v1, v0);
        mflo(v1);
    } else {
        // 0x0011cfec
        charge(ctx, 3);
        v1 = 255;
    }
    // 0x0011d00c
    charge(ctx, 5);
    v0 = 255;
    s0 = subu(v0, v1);
    lw(v0, gp, g::kPersonaTexTask);  // 0x7CDF60
    if (v0 != 0) {
        // 0x0011d02c
        charge(ctx, 5);
        lw(a0, v0, 60);
        lw(v1, a0, 0);
        v0 = 3;
        if (v1 != v0) {
            // 0x0011d04c
            charge(ctx, 1);
            t0 = 0;
        } else {
            // 0x0011d040
            charge(ctx, 3);
            lw(t0, a0, 12);
        }
    } else {
        // 0x0011d020
        charge(ctx, 3);
        t0 = 0;
    }
    // 0x0011d050
    charge(ctx, 2);
    if (t0 != 0) {
        // 0x0011d058
        charge(ctx, 8);
        v1 = dsll32(s0, 16);
        v1 = dsra32(v1, 16);
        v0 = 255;
        v1 = subu(v0, v1);
        a1 = v1;
        v0 = sltiu(v1, 25);
        if (v0 == 0) {
            // 0x0011d078
            charge(ctx, 1);
            a1 = 25;
        }
        // 0x0011d07c
        charge(ctx, 16);
        v0 = 0x40800000;  // 4.0f
        mtc1(v0, f0);
        add_s(f12, f0, f20);
        v0 = si(-256);
        a0 = v1 | v0;
        v0 = 0x4FA40000;
        v0 = v0 | 0xFF00;
        a1 = a1 | v0;
        mtc1(zero, f13);
        v0 = lui(0xC2AE);
        mtc1(v0, f14);
        a2 = 640;
        a3 = a2;
        jal(ctx, 0x11D0B4u, gen::fn_sub_114450_00114450);  // [nine-slice window] / the persona picture
    }
    // 0x0011d0bc
    charge(ctx, 74);
    mtc1(zero, f12);
    v0 = 0x40800000;  // 4.0f
    mtc1(v0, f0);
    add_s(f14, f0, f20);
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    mov_s(f13, f12);
    a1 = 0;
    jal(ctx, 0x11D0E0u, gen::fn_nullsub_3_0011bba0);
    a0 = 0;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(2));  // 0x833B78: camp sprite file 2
    a2 = 0;
    jal(ctx, 0x11D0F8u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
    s2 = v0;
    v1 = 0x40000000;  // 2.0f
    mtc1(v1, f0);
    add_s(f0, f0, f20);
    swc1(f0, v0, 44);
    v1 = 0x43D60000;  // 428.0f
    sw(v1, v0, 16);
    v1 = 0x41D80000;  // 27.0f
    sw(v1, v0, 20);
    v1 = dsll32(s0, 16);
    v1 = dsra32(v1, 16);
    sb(v1, v0, 24);
    sh(zero, v0, 40);
    sh(zero, v0, 42);
    a0 = s2;
    a1 = 1;
    jal(ctx, 0x11D144u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
    a0 = s2;
    jal(ctx, 0x11D150u, gen::fn_sub_115980_00115980);  // draw and release the handle
    lw(v1, s3, root::kTimer);
    v0 = 22;
    v0 = subu(v0, v1);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x43480000;  // 200.0f
    mtc1(v0, f0);
    mul_s(f1, f0, f1);
    v0 = 0x41B00000;  // 22.0f
    mtc1(v0, f0);
    div_s(f0, f1, f0);
    swc1(f0, sp, 0x68);
    lwc1(f0, s3, root::kStrip);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x6C);
    v0 = 0x3F800000;  // 1.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sw(v0, s3, root::kStrip);
    lwc1(f0, s3, root::kStrip);
    cvt_s_w(f1, f0);
    v0 = 767;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    c_le_s(f1, f0);
    if (!cond(ctx)) {
        // 0x0011d1e4
        charge(ctx, 8);
        v0 = 0x43E00000;  // 448.0f
        mtc1(v0, f0);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        sw(v0, s3, root::kStrip);
    }
    // 0x0011d204
    charge(ctx, 47);
    ld(v0, sp, 0x68);
    sd(v0, sp, 0x60);
    lwc1(f22, sp, 0x64);
    v0 = 589;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x60);
    add_s(f21, f1, f0);
    v0 = 0x433E0000;  // 190.0f
    mtc1(v0, f0);
    sub_s(f13, f22, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
    a2 = 3;
    mov_s(f12, f21);
    jal(ctx, 0x11D258u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43010000;  // 129.0f
    mtc1(v0, f0);
    sub_s(f1, f22, f0);
    v0 = 0x433E0000;  // 190.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
    a2 = 4;
    mov_s(f12, f21);
    jal(ctx, 0x11D2A0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43E00000;  // 448.0f
    mtc1(v0, f1);
    c_le_s(f22, f1);
    if (!cond(ctx)) {
        // 0x0011d2c0
        charge(ctx, 40);
        mov_s(f0, f22);
        sub_s(f22, f0, f1);
        v0 = 589;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0x60);
        add_s(f21, f1, f0);
        v0 = 0x433E0000;  // 190.0f
        mtc1(v0, f0);
        sub_s(f13, f22, f0);
        a3 = s0 & 0xFF;
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s1;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
        a2 = 3;
        mov_s(f12, f21);
        jal(ctx, 0x11D310u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x43010000;  // 129.0f
        mtc1(v0, f0);
        sub_s(f1, f22, f0);
        v0 = 0x433E0000;  // 190.0f
        mtc1(v0, f0);
        sub_s(f13, f1, f0);
        a3 = s0 & 0xFF;
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s1;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
        a2 = 4;
        mov_s(f12, f21);
        jal(ctx, 0x11D358u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x0011d360
    charge(ctx, 15);
    a0 = s3;
    mov_s(f12, f20);
    jal(ctx, 0x11D368u, gen::fn_sub_11BBB0_0011bbb0);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0011D6D0 sub_11D6D0 -- 936 bytes; frame 0x70: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_RootDrawClose] (root work, z in $f12): the close animation (states 7 / 8): background alpha 255 - 255 * timer
// / 22, the frame sprite, the side strip and the list.
void sub_11D6D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x0011d6d0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s3 = a0;
    mov_s(f20, f12);
    lw(v1, a0, 4);
    v0 = sll(v1, 8);
    v1 = subu(v0, v1);
    v0 = 22;
    div(v1, v0);
    mflo(v1);
    v0 = 255;
    s0 = subu(v0, v1);
    lw(v0, gp, g::kPersonaTexTask);  // 0x7CDF60
    if (v0 != 0) {
        // 0x0011d734
        charge(ctx, 5);
        lw(a0, v0, 60);
        lw(v1, a0, 0);
        v0 = 3;
        if (v1 != v0) {
            // 0x0011d754
            charge(ctx, 1);
            t0 = 0;
        } else {
            // 0x0011d748
            charge(ctx, 3);
            lw(t0, a0, 12);
        }
    } else {
        // 0x0011d728
        charge(ctx, 3);
        t0 = 0;
    }
    // 0x0011d758
    charge(ctx, 2);
    if (t0 != 0) {
        // 0x0011d760
        charge(ctx, 8);
        v1 = dsll32(s0, 16);
        v1 = dsra32(v1, 16);
        v0 = 255;
        v1 = subu(v0, v1);
        a1 = v1;
        v0 = sltiu(v1, 25);
        if (v0 == 0) {
            // 0x0011d780
            charge(ctx, 1);
            a1 = 25;
        }
        // 0x0011d784
        charge(ctx, 16);
        v0 = 0x40000000;  // 2.0f
        mtc1(v0, f0);
        add_s(f12, f0, f20);
        v0 = si(-256);
        a0 = v1 | v0;
        v0 = 0x4FA40000;
        v0 = v0 | 0xFF00;
        a1 = a1 | v0;
        mtc1(zero, f13);
        v0 = lui(0xC2AE);
        mtc1(v0, f14);
        a2 = 640;
        a3 = a2;
        jal(ctx, 0x11D7BCu, gen::fn_sub_114450_00114450);  // [nine-slice window] / the persona picture
    }
    // 0x0011d7c4
    charge(ctx, 63);
    a0 = 0;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(2));  // 0x833B78: camp sprite file 2
    a2 = 0;
    jal(ctx, 0x11D7D4u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
    s2 = v0;
    v1 = 0x3F800000;  // 1.0f
    mtc1(v1, f0);
    add_s(f0, f0, f20);
    swc1(f0, v0, 44);
    v1 = 0x43D60000;  // 428.0f
    sw(v1, v0, 16);
    v1 = 0x41D80000;  // 27.0f
    sw(v1, v0, 20);
    v1 = dsll32(s0, 16);
    v1 = dsra32(v1, 16);
    sb(v1, v0, 24);
    sh(zero, v0, 40);
    sh(zero, v0, 42);
    a0 = s2;
    a1 = 1;
    jal(ctx, 0x11D820u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
    a0 = s2;
    jal(ctx, 0x11D82Cu, gen::fn_sub_115980_00115980);  // draw and release the handle
    lw(v1, s3, root::kTimer);
    v0 = 22;
    v0 = subu(v0, v1);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x43480000;  // 200.0f
    mtc1(v0, f0);
    mul_s(f1, f0, f1);
    v0 = 0x41B00000;  // 22.0f
    mtc1(v0, f0);
    div_s(f0, f1, f0);
    swc1(f0, sp, 0x68);
    lwc1(f0, s3, root::kStrip);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x6C);
    v0 = 0x3F800000;  // 1.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sw(v0, s3, root::kStrip);
    lwc1(f0, s3, root::kStrip);
    cvt_s_w(f1, f0);
    v0 = 767;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    c_le_s(f1, f0);
    if (!cond(ctx)) {
        // 0x0011d8c0
        charge(ctx, 8);
        v0 = 0x43E00000;  // 448.0f
        mtc1(v0, f0);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        sw(v0, s3, root::kStrip);
    }
    // 0x0011d8e0
    charge(ctx, 47);
    ld(v0, sp, 0x68);
    sd(v0, sp, 0x60);
    lwc1(f22, sp, 0x64);
    v0 = 589;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x60);
    add_s(f21, f1, f0);
    v0 = 0x433E0000;  // 190.0f
    mtc1(v0, f0);
    sub_s(f13, f22, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
    a2 = 3;
    mov_s(f12, f21);
    jal(ctx, 0x11D934u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43010000;  // 129.0f
    mtc1(v0, f0);
    sub_s(f1, f22, f0);
    v0 = 0x433E0000;  // 190.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
    a2 = 4;
    mov_s(f12, f21);
    jal(ctx, 0x11D97Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43E00000;  // 448.0f
    mtc1(v0, f1);
    c_le_s(f22, f1);
    if (!cond(ctx)) {
        // 0x0011d99c
        charge(ctx, 40);
        mov_s(f0, f22);
        sub_s(f22, f0, f1);
        v0 = 589;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0x60);
        add_s(f21, f1, f0);
        v0 = 0x433E0000;  // 190.0f
        mtc1(v0, f0);
        sub_s(f13, f22, f0);
        a3 = s0 & 0xFF;
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s1;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
        a2 = 3;
        mov_s(f12, f21);
        jal(ctx, 0x11D9ECu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x43010000;  // 129.0f
        mtc1(v0, f0);
        sub_s(f1, f22, f0);
        v0 = 0x433E0000;  // 190.0f
        mtc1(v0, f0);
        sub_s(f13, f1, f0);
        a3 = s0 & 0xFF;
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s1;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
        a2 = 4;
        mov_s(f12, f21);
        jal(ctx, 0x11DA34u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x0011da3c
    charge(ctx, 15);
    a0 = s3;
    mov_s(f12, f20);
    jal(ctx, 0x11DA44u, gen::fn_sub_11BBB0_0011bbb0);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0011DDB0 sub_11DDB0 -- 552 bytes; frame 0x50: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_RootDrawIdle] (root work): the side strip (+32 scrolling, file 7 sprites 3 / 4, drawn twice near the wrap)
// and the list -- the frame drawn when nothing animates.
void sub_11DDB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x0011ddb0
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    mov_s(f20, f12);
    sw(zero, sp, 0x48);
    lwc1(f0, a0, 32);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x4C);
    v0 = 0x3F800000;  // 1.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sw(v0, a0, 32);
    lwc1(f0, a0, 32);
    cvt_s_w(f1, f0);
    v0 = 767;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    c_le_s(f1, f0);
    if (!cond(ctx)) {
        // 0x0011de28
        charge(ctx, 8);
        v0 = 0x43E00000;  // 448.0f
        mtc1(v0, f0);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        sw(v0, s1, root::kStrip);
    }
    // 0x0011de48
    charge(ctx, 47);
    ld(v0, sp, 0x48);
    sd(v0, sp, 0x40);
    lwc1(f22, sp, 0x44);
    v0 = 589;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x40);
    add_s(f21, f1, f0);
    v0 = 0x433E0000;  // 190.0f
    mtc1(v0, f0);
    sub_s(f13, f22, f0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s0;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
    a2 = 3;
    mov_s(f12, f21);
    a3 = 0;
    jal(ctx, 0x11DE9Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43010000;  // 129.0f
    mtc1(v0, f0);
    sub_s(f1, f22, f0);
    v0 = 0x433E0000;  // 190.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s0;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
    a2 = 4;
    mov_s(f12, f21);
    a3 = 0;
    jal(ctx, 0x11DEE4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43E00000;  // 448.0f
    mtc1(v0, f1);
    c_le_s(f22, f1);
    if (!cond(ctx)) {
        // 0x0011df04
        charge(ctx, 40);
        mov_s(f0, f22);
        sub_s(f22, f0, f1);
        v0 = 589;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0x40);
        add_s(f21, f1, f0);
        v0 = 0x433E0000;  // 190.0f
        mtc1(v0, f0);
        sub_s(f13, f22, f0);
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
        a2 = 3;
        mov_s(f12, f21);
        a3 = 0;
        jal(ctx, 0x11DF54u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x43010000;  // 129.0f
        mtc1(v0, f0);
        sub_s(f1, f22, f0);
        v0 = 0x433E0000;  // 190.0f
        mtc1(v0, f0);
        sub_s(f13, f1, f0);
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
        a2 = 4;
        mov_s(f12, f21);
        a3 = 0;
        jal(ctx, 0x11DF9Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x0011dfa4
    charge(ctx, 13);
    a0 = s1;
    mov_s(f12, f20);
    jal(ctx, 0x11DFACu, gen::fn_sub_11BBB0_0011bbb0);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0011DFE0 sub_11DFE0 -- 912 bytes; frame 0x60: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_RootDrawInput] (root work, z in $f12): the input state's frame: the persona background, the frame sprite, the
// cursor bar easing to y 57 + 19 cursor (gp-19876 record 10 +60; +40 = 1 once it arrived), the side strip and the list.
void sub_11DFE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x0011dfe0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    mov_s(f20, f12);
    lw(v0, gp, g::kPersonaTexTask);  // 0x7CDF60
    if (v0 != 0) {
        // 0x0011e020
        charge(ctx, 5);
        lw(a0, v0, 60);
        lw(v1, a0, 0);
        v0 = 3;
        if (v1 != v0) {
            // 0x0011e040
            charge(ctx, 1);
            t0 = 0;
        } else {
            // 0x0011e034
            charge(ctx, 3);
            lw(t0, a0, 12);
        }
    } else {
        // 0x0011e014
        charge(ctx, 3);
        t0 = 0;
    }
    // 0x0011e044
    charge(ctx, 2);
    if (t0 != 0) {
        // 0x0011e04c
        charge(ctx, 14);
        v0 = 0x40000000;  // 2.0f
        mtc1(v0, f0);
        add_s(f12, f0, f20);
        mtc1(zero, f13);
        v0 = lui(0xC2AE);
        mtc1(v0, f14);
        a0 = si(-1);
        v0 = 0x4FA40000;
        a1 = v0 | 0xFF19;
        a2 = 640;
        a3 = a2;
        jal(ctx, 0x11E07Cu, gen::fn_sub_114450_00114450);  // [nine-slice window] / the persona picture
    }
    // 0x0011e084
    charge(ctx, 52);
    mtc1(zero, f12);
    v0 = 0x40000000;  // 2.0f
    mtc1(v0, f0);
    add_s(f14, f0, f20);
    mov_s(f13, f12);
    a0 = 0;
    a1 = 4096;
    jal(ctx, 0x11E0A4u, gen::fn_nullsub_3_0011bba0);
    a0 = 0;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(2));  // 0x833B78: camp sprite file 2
    a2 = 0;
    jal(ctx, 0x11E0BCu, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
    s1 = v0;
    v1 = 0x3F800000;  // 1.0f
    mtc1(v1, f0);
    add_s(f0, f0, f20);
    swc1(f0, v0, 44);
    v1 = 0x43D60000;  // 428.0f
    sw(v1, v0, 16);
    v1 = 0x41D80000;  // 27.0f
    sw(v1, v0, 20);
    sb(zero, v0, 24);
    v1 = 4096;
    sh(v1, v0, 40);
    sh(v1, v0, 42);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x11E104u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
    a0 = s1;
    jal(ctx, 0x11E110u, gen::fn_sub_115980_00115980);  // draw and release the handle
    lw(v1, s2, root::kCursor);
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    a0 = addiu(v0, 57);
    lw(v1, gp, g::kCampTweens);  // 0x7CDF4C
    v0 = addiu(v1, 732);
    lwc1(f1, v1, 732);
    mtc1(a0, f0);
    cvt_s_w(f0, f0);
    c_eq_s(f1, f0);
    if (cond(ctx)) {
        // 0x0011e160
        charge(ctx, 2);
        v0 = 1;
        sw(v0, s2, root::kArrived);
    } else {
        // 0x0011e154
        charge(ctx, 3);
        swc1(f0, v0, 0);
    }
    // 0x0011e168
    charge(ctx, 21);
    sw(zero, sp, 0x58);
    lwc1(f0, s2, root::kStrip);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x5C);
    v0 = 0x3F800000;  // 1.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sw(v0, s2, root::kStrip);
    lwc1(f0, s2, root::kStrip);
    cvt_s_w(f1, f0);
    v0 = 767;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    c_le_s(f1, f0);
    if (!cond(ctx)) {
        // 0x0011e1bc
        charge(ctx, 8);
        v0 = 0x43E00000;  // 448.0f
        mtc1(v0, f0);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        sw(v0, s2, root::kStrip);
    }
    // 0x0011e1dc
    charge(ctx, 47);
    ld(v0, sp, 0x58);
    sd(v0, sp, 0x50);
    lwc1(f22, sp, 0x54);
    v0 = 589;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x50);
    add_s(f21, f1, f0);
    v0 = 0x433E0000;  // 190.0f
    mtc1(v0, f0);
    sub_s(f13, f22, f0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s0;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
    a2 = 3;
    mov_s(f12, f21);
    a3 = 0;
    jal(ctx, 0x11E230u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43010000;  // 129.0f
    mtc1(v0, f0);
    sub_s(f1, f22, f0);
    v0 = 0x433E0000;  // 190.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s0;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
    a2 = 4;
    mov_s(f12, f21);
    a3 = 0;
    jal(ctx, 0x11E278u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43E00000;  // 448.0f
    mtc1(v0, f1);
    c_le_s(f22, f1);
    if (!cond(ctx)) {
        // 0x0011e298
        charge(ctx, 40);
        mov_s(f0, f22);
        sub_s(f22, f0, f1);
        v0 = 589;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0x50);
        add_s(f21, f1, f0);
        v0 = 0x433E0000;  // 190.0f
        mtc1(v0, f0);
        sub_s(f13, f22, f0);
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
        a2 = 3;
        mov_s(f12, f21);
        a3 = 0;
        jal(ctx, 0x11E2E8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x43010000;  // 129.0f
        mtc1(v0, f0);
        sub_s(f1, f22, f0);
        v0 = 0x433E0000;  // 190.0f
        mtc1(v0, f0);
        sub_s(f13, f1, f0);
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(7));  // 0x833B8C: camp sprite file 7
        a2 = 4;
        mov_s(f12, f21);
        a3 = 0;
        jal(ctx, 0x11E330u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x0011e338
    charge(ctx, 14);
    a0 = s2;
    mov_s(f12, f20);
    jal(ctx, 0x11E340u, gen::fn_sub_11BBB0_0011bbb0);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001236A0 sub_1236A0 -- 1232 bytes; frame 0x180: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [H_Camp_StatusDrawHp] (xy, pc, gauge, alpha): the HP block of a party member: the name (sub_177790 -> sprintf ->
// sub_3B32D0), the gauge (sub_113A30, `gauge` px), the frame (sprite 4 of camp file 8), the current HP (datGetPcHp) as
// up to three digits of sprite font 2 (sprite 11 + digit) and the maximum (datGetPcMaxHp) in colour 102.
void sub_1236A0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x001236a0
    enter(ctx, 63);  // entry check point + this block's cycles
    sp = addiu(sp, -0x180);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x78);
    mov_s(f21, f12);
    s1 = a1;
    s4 = a2;
    s0 = a3;
    lwc1(f20, sp, 0x7C);
    v0 = 255;
    s2 = subu(v0, s0);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x1236ECu, gen::fn_sub_177790_00177790);  // a member's name
    a0 = addiu(sp, 0x80);
    a1 = addiu(gp, -30340);  // "%s"
    a2 = v0;
    jal(ctx, 0x123700u, gen::fn_sprintf_00523ac8);
    v0 = 0x42FA0000;  // 125.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x78);
    add_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    v0 = 0x422C0000;  // 43.0f
    mtc1(v0, f0);
    add_s(f0, f0, f20);
    cvt_w_s(f0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x40A00000;  // 5.0f
    mtc1(v0, f0);
    add_s(f1, f0, f1);
    v0 = 0x41400000;  // 12.0f
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(a1, f0);
    v0 = 0x3F800000;  // 1.0f
    mtc1(v0, f0);
    sub_s(f12, f21, f0);
    v0 = si(-256);
    a2 = s2 | v0;
    a3 = 10;
    t0 = 1;
    t1 = addiu(sp, 0x80);
    t2 = 16;
    t3 = 120;
    jal(ctx, 0x12378Cu, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
    if (s4 != 0) {
        // 0x0012379c
        charge(ctx, 27);
        v0 = 0x43440000;  // 196.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x78);
        add_s(f1, f1, f0);
        v0 = 76;
        v0 = subu(v0, s4);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f13, f1, f0);
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f12, f21, f0);
        v0 = 0x428E0000;  // 71.0f
        mtc1(v0, f0);
        add_s(f1, f0, f20);
        v0 = 0x41400000;  // 12.0f
        mtc1(v0, f0);
        sub_s(f14, f1, f0);
        a0 = si(-256);
        a1 = s4;
        a2 = 10;
        jal(ctx, 0x123800u, gen::fn_sub_113A30_00113a30);  // [plain rectangle] (rgba, w, h)
    }
    // 0x00123808
    charge(ctx, 29);
    v0 = 0x43430000;  // 195.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x78);
    add_s(f12, f1, f0);
    v0 = 0x428E0000;  // 71.0f
    mtc1(v0, f0);
    add_s(f1, f0, f20);
    v0 = 0x41400000;  // 12.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 4;
    mov_s(f14, f21);
    jal(ctx, 0x123850u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x123860u, gen::fn_sub_16C4F0_0016c4f0);  // [datGetPcHp]
    s4 = v0 & 0xFFFF;
    s2 = 0;
    v0 = slti(s4, 100);
    if (v0 == 0) {
        // 0x0012387c
        charge(ctx, 29);
        s2 = 1;
        a0 = 2;
        jal(ctx, 0x123884u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
        v1 = 100;
        div(s4, v1);
        mflo(v1);
        a2 = addiu(v1, 11);
        v1 = 0x429E0000;  // 79.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        v1 = 0x428C0000;  // 70.0f
        mtc1(v1, f0);
        add_s(f1, f0, f20);
        v1 = 0x41400000;  // 12.0f
        mtc1(v1, f0);
        sub_s(f13, f1, f0);
        a3 = s0 & 0xFF;
        a0 = s3;
        a1 = v0;
        mov_s(f14, f21);
        jal(ctx, 0x1238DCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 100;
        div(s4, v0);
        mfhi(s4);
    }
    // 0x001238f0
    charge(ctx, 3);
    at = slti(s4, 10);
    if (at != 0) {
        // 0x001238fc
        charge(ctx, 2);
        if (s2 != 0) {
            goto L_00123904;
        }
        goto L_00123980;
    }
L_00123904:
    charge(ctx, 31);
    a0 = 2;
    jal(ctx, 0x123908u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
    v1 = 10;
    div(s4, v1);
    mflo(v1);
    a2 = addiu(v1, 11);
    v1 = 0x41700000;  // 15.0f
    mtc1(v1, f2);
    v1 = 0x429E0000;  // 79.0f
    mtc1(v1, f1);
    lwc1(f0, sp, 0x78);
    add_s(f0, f1, f0);
    add_s(f12, f2, f0);
    v1 = 0x428C0000;  // 70.0f
    mtc1(v1, f0);
    add_s(f1, f0, f20);
    v1 = 0x41400000;  // 12.0f
    mtc1(v1, f0);
    sub_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    a0 = s3;
    a1 = v0;
    mov_s(f14, f21);
    jal(ctx, 0x12396Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 10;
    div(s4, v0);
    mfhi(s4);
L_00123980:
    charge(ctx, 38);
    v0 = 0x428C0000;  // 70.0f
    mtc1(v0, f0);
    add_s(f1, f0, f20);
    v0 = 0x41400000;  // 12.0f
    mtc1(v0, f0);
    sub_s(f20, f1, f0);
    a0 = 2;
    jal(ctx, 0x1239A4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
    v1 = 10;
    div(s4, v1);
    mfhi(v1);
    a2 = addiu(v1, 11);
    v1 = 0x41F00000;  // 30.0f
    mtc1(v1, f2);
    v1 = 0x429E0000;  // 79.0f
    mtc1(v1, f1);
    lwc1(f0, sp, 0x78);
    add_s(f0, f1, f0);
    add_s(f12, f2, f0);
    a3 = s0 & 0xFF;
    a0 = s3;
    a1 = v0;
    mov_s(f13, f20);
    mov_s(f14, f21);
    jal(ctx, 0x1239ECu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x1239FCu, gen::fn_sub_16C5F0_0016c5f0);  // [datGetPcMaxHp]
    s2 = v0 & 0xFFFF;
    s1 = 0;
    v0 = slti(s2, 100);
    if (v0 == 0) {
        // 0x00123a18
        charge(ctx, 23);
        s1 = 1;
        a0 = 2;
        jal(ctx, 0x123A20u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
        v1 = 100;
        div(s2, v1);
        mflo(v1);
        a2 = addiu(v1, 11);
        v1 = 0x430A0000;  // 138.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        a3 = s0 & 0xFF;
        a0 = s3;
        a1 = v0;
        mov_s(f13, f20);
        t0 = 102;
        mov_s(f14, f21);
        jal(ctx, 0x123A60u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
        v0 = 100;
        div(s2, v0);
        mfhi(s2);
    }
    // 0x00123a74
    charge(ctx, 3);
    at = slti(s2, 10);
    if (at != 0) {
        // 0x00123a80
        charge(ctx, 2);
        if (s1 != 0) {
            goto L_00123a88;
        }
        goto L_00123aec;
    }
L_00123a88:
    charge(ctx, 25);
    a0 = 2;
    jal(ctx, 0x123A8Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
    v1 = 10;
    div(s2, v1);
    mflo(v1);
    a2 = addiu(v1, 11);
    v1 = 0x41700000;  // 15.0f
    mtc1(v1, f2);
    v1 = 0x430A0000;  // 138.0f
    mtc1(v1, f1);
    lwc1(f0, sp, 0x78);
    add_s(f0, f1, f0);
    add_s(f12, f2, f0);
    a3 = s0 & 0xFF;
    a0 = s3;
    a1 = v0;
    mov_s(f13, f20);
    t0 = 102;
    mov_s(f14, f21);
    jal(ctx, 0x123AD8u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
    v0 = 10;
    div(s2, v0);
    mfhi(s2);
L_00123aec:
    charge(ctx, 33);
    a0 = 2;
    jal(ctx, 0x123AF0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
    v1 = 10;
    div(s2, v1);
    mfhi(v1);
    a2 = addiu(v1, 11);
    v1 = 0x41F00000;  // 30.0f
    mtc1(v1, f2);
    v1 = 0x430A0000;  // 138.0f
    mtc1(v1, f1);
    lwc1(f0, sp, 0x78);
    add_s(f0, f1, f0);
    add_s(f12, f2, f0);
    a3 = s0 & 0xFF;
    a0 = s3;
    a1 = v0;
    mov_s(f13, f20);
    t0 = 102;
    mov_s(f14, f21);
    jal(ctx, 0x123B3Cu, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x180);
}

// 0x00124370 sub_124370 -- 1972 bytes; frame 0x90: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [H_Camp_StatusDrawPcPanelIn] (xy, pc, frame): a party member's status panel during its reveal: the frame sprite
// sliding in over 3 frames, then from frame 4 the level (datGetPcLevel, two digits of font 2), HP (sub_1236A0) and SP
// (sub_123B70) blocks with gauges 76 - 76 * cur / max, the condition icon (sub_123F80) and the sparkle ring
// (sub_124090), each with its own fade.
void sub_124370(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00124370
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x70);
    mov_s(f21, f12);
    s4 = a1;
    s3 = a2;
    at = slti(s3, 3);
    if (at == 0) {
        // 0x001243fc
        charge(ctx, 2);
        sw(zero, sp, 0x88);
        s1 = 0;
    } else {
        // 0x001243b0
        charge(ctx, 19);
        v0 = sll(s3, 8);
        v0 = subu(v0, s3);
        a1 = 3;
        div(v0, a1);
        mflo(v1);
        v0 = 255;
        s1 = subu(v0, v1);
        v1 = subu(a1, s3);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        div1(v0, a1);
        mflo1(v0);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x88);
    }
    // 0x00124404
    charge(ctx, 29);
    lwc1(f1, sp, 0x70);
    lwc1(f0, sp, 0x88);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x88);
    lwc1(f20, sp, 0x74);
    swc1(f20, sp, 0x8C);
    ld(v0, sp, 0x88);
    sd(v0, sp, 0x80);
    v0 = 0x41B00000;  // 22.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x80);
    add_s(f12, f1, f0);
    v0 = 0x421C0000;  // 39.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x84);
    add_s(f1, f1, f0);
    v0 = 0x41400000;  // 12.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s1 & 0xFF;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 0;
    mov_s(f14, f21);
    jal(ctx, 0x124468u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    if (s3 != 0) {
        // 0x00124478
        charge(ctx, 3);
        at = slti(s3, 4);
        if (at == 0) {
            // 0x001244d8
            charge(ctx, 2);
            s1 = 0;
            sw(zero, sp, 0x88);
        } else {
            // 0x00124484
            charge(ctx, 21);
            a0 = addiu(s3, -1);
            v1 = sll(a0, 8);
            v1 = subu(v1, a0);
            a1 = 3;
            div(v1, a1);
            mflo(a0);
            v1 = 255;
            s1 = subu(v1, a0);
            v1 = 4;
            a0 = subu(v1, s3);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            v1 = sll(v1, 3);
            div1(v1, a1);
            mflo1(v1);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x88);
        }
        // 0x001244e0
        charge(ctx, 5);
        lwc1(f1, sp, 0x70);
        lwc1(f0, sp, 0x88);
        sub_s(f0, f1, f0);
        swc1(f0, sp, 0x88);
        swc1(f20, sp, 0x8C);
    }
    // 0x001244f4
    charge(ctx, 3);
    v1 = slti(s3, 4);
    if (v1 == 0) {
        // 0x00124500
        charge(ctx, 3);
        at = slti(s3, 9);
        if (at == 0) {
            // 0x0012453c
            charge(ctx, 1);
            s1 = 0;
        } else {
            // 0x0012450c
            charge(ctx, 6);
            v1 = addiu(s3, -4);
            v0 = sll(v1, 8);
            v0 = subu(v0, v1);
            v1 = sra(v0, 2);
            if (i64(v0) < 0) {
                // 0x00124524
                charge(ctx, 2);
                v0 = addiu(v0, 3);
                v1 = sra(v0, 2);
            }
            // 0x0012452c
            charge(ctx, 4);
            v0 = 255;
            s1 = subu(v0, v1);
        }
        // 0x00124540
        charge(ctx, 9);
        ld(v0, sp, 0x70);
        sd(v0, sp, 0x78);
        a0 = s4;
        jal(ctx, 0x12454Cu, gen::fn_sub_16C470_0016c470);  // [datGetPcLevel]
        v0 = v0 & 0xFF;
        v0 = slti(v0, 10);
        if (v0 == 0) {
            // 0x00124564
            charge(ctx, 34);
            a0 = 2;
            jal(ctx, 0x124568u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            s0 = v0;
            a0 = s4;
            jal(ctx, 0x124578u, gen::fn_sub_16C470_0016c470);  // [datGetPcLevel]
            v1 = v0 & 0xFF;
            v0 = 10;
            div(v1, v0);
            mflo(v0);
            a2 = addiu(v0, 11);
            v0 = 0x42A20000;  // 81.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x78);
            add_s(f12, f1, f0);
            v0 = 0x42500000;  // 52.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x7C);
            add_s(f1, f1, f0);
            v0 = 0x3F800000;  // 1.0f
            mtc1(v0, f0);
            sub_s(f1, f1, f0);
            v0 = 0x41400000;  // 12.0f
            mtc1(v0, f0);
            sub_s(f13, f1, f0);
            a3 = s1 & 0xFF;
            a0 = s2;
            a1 = s0;
            mov_s(f14, f21);
            jal(ctx, 0x1245E4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        }
        // 0x001245ec
        charge(ctx, 34);
        a0 = 2;
        jal(ctx, 0x1245F0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
        s0 = v0;
        a0 = s4;
        jal(ctx, 0x124600u, gen::fn_sub_16C470_0016c470);  // [datGetPcLevel]
        v1 = v0 & 0xFF;
        v0 = 10;
        div(v1, v0);
        mfhi(v0);
        a2 = addiu(v0, 11);
        v0 = 0x42C00000;  // 96.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        v0 = 0x42500000;  // 52.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x7C);
        add_s(f1, f1, f0);
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f1, f1, f0);
        v0 = 0x41400000;  // 12.0f
        mtc1(v0, f0);
        sub_s(f13, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s2;
        a1 = s0;
        mov_s(f14, f21);
        jal(ctx, 0x12466Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x00124674
    charge(ctx, 3);
    v1 = slti(s3, 4);
    if (v1 == 0) {
        // 0x00124680
        charge(ctx, 3);
        at = slti(s3, 9);
        if (at == 0) {
            // 0x001246f4
            charge(ctx, 2);
            s1 = 0;
            sw(zero, sp, 0x88);
        } else {
            // 0x0012468c
            charge(ctx, 6);
            a0 = addiu(s1, -4);
            v1 = sll(a0, 8);
            v1 = subu(v1, a0);
            a0 = sra(v1, 2);
            if (i64(v1) < 0) {
                // 0x001246a4
                charge(ctx, 2);
                v1 = addiu(v1, 3);
                a0 = sra(v1, 2);
            }
            // 0x001246ac
            charge(ctx, 10);
            v1 = 255;
            s1 = subu(v1, a0);
            v1 = 9;
            a0 = subu(v1, s3);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 3);
            v1 = sra(a0, 2);
            if (i64(a0) < 0) {
                // 0x001246d4
                charge(ctx, 2);
                v1 = addiu(a0, 3);
                v1 = sra(v1, 2);
            }
            // 0x001246dc
            charge(ctx, 6);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x88);
        }
        // 0x001246fc
        charge(ctx, 5);
        lwc1(f1, sp, 0x70);
        lwc1(f0, sp, 0x88);
        sub_s(f0, f1, f0);
        swc1(f0, sp, 0x88);
        swc1(f20, sp, 0x8C);
    }
    // 0x00124710
    charge(ctx, 3);
    v1 = slti(s3, 6);
    if (v1 == 0) {
        // 0x0012471c
        charge(ctx, 3);
        at = slti(s3, 11);
        if (at == 0) {
            // 0x00124790
            charge(ctx, 2);
            s1 = 0;
            sw(zero, sp, 0x88);
        } else {
            // 0x00124728
            charge(ctx, 6);
            a0 = addiu(s3, -6);
            v1 = sll(a0, 8);
            v1 = subu(v1, a0);
            a0 = sra(v1, 2);
            if (i64(v1) < 0) {
                // 0x00124740
                charge(ctx, 2);
                v1 = addiu(v1, 3);
                a0 = sra(v1, 2);
            }
            // 0x00124748
            charge(ctx, 10);
            v1 = 255;
            s1 = subu(v1, a0);
            v1 = 11;
            a0 = subu(v1, s3);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 3);
            v1 = sra(a0, 2);
            if (i64(a0) < 0) {
                // 0x00124770
                charge(ctx, 2);
                v1 = addiu(a0, 3);
                v1 = sra(v1, 2);
            }
            // 0x00124778
            charge(ctx, 6);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x88);
        }
        // 0x00124798
        charge(ctx, 5);
        lwc1(f1, sp, 0x70);
        lwc1(f0, sp, 0x88);
        sub_s(f0, f1, f0);
        swc1(f0, sp, 0x88);
        swc1(f20, sp, 0x8C);
    }
    // 0x001247ac
    charge(ctx, 3);
    v1 = slti(s3, 11);
    if (v1 == 0) {
        // 0x001247b8
        charge(ctx, 3);
        at = slti(s3, 15);
        if (at == 0) {
            // 0x00124864
            charge(ctx, 18);
            s1 = 0;
            a0 = s4;
            jal(ctx, 0x12486Cu, gen::fn_sub_16C4F0_0016c4f0);  // [datGetPcHp]
            v1 = v0 & 0xFFFF;
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            s0 = sll(v0, 2);
            a0 = s4;
            jal(ctx, 0x124890u, gen::fn_sub_16C5F0_0016c5f0);  // [datGetPcMaxHp]
            v0 = v0 & 0xFFFF;
            div(s0, v0);
            mflo(v1);
            v0 = 76;
            a2 = subu(v0, v1);
        } else {
            // 0x001247c4
            charge(ctx, 6);
            v1 = addiu(s3, -11);
            v0 = sll(v1, 8);
            v0 = subu(v0, v1);
            v1 = sra(v0, 2);
            if (i64(v0) < 0) {
                // 0x001247dc
                charge(ctx, 2);
                v0 = addiu(v0, 3);
                v1 = sra(v0, 2);
            }
            // 0x001247e4
            charge(ctx, 22);
            v0 = 255;
            s1 = subu(v0, v1);
            a0 = s4;
            jal(ctx, 0x1247F0u, gen::fn_sub_16C4F0_0016c4f0);  // [datGetPcHp]
            v1 = v0 & 0xFFFF;
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            s0 = sll(v0, 2);
            a0 = s4;
            jal(ctx, 0x124814u, gen::fn_sub_16C5F0_0016c5f0);  // [datGetPcMaxHp]
            v0 = v0 & 0xFFFF;
            div(s0, v0);
            mflo(a0);
            v0 = addiu(s3, -11);
            mult(v0, a0, v0);
            v1 = sra(v0, 2);
            if (i64(v0) < 0) {
                // 0x0012483c
                charge(ctx, 2);
                v0 = addiu(v0, 3);
                v1 = sra(v0, 2);
            }
            // 0x00124844
            charge(ctx, 3);
            at = slt(a0, v1);
            if (at != 0) {
                // 0x00124850
                charge(ctx, 1);
                v1 = a0;
            }
            // 0x00124854
            charge(ctx, 4);
            v0 = 76;
            a2 = subu(v0, v1);
        }
        // 0x001248ac
        charge(ctx, 7);
        a1 = dsll32(s4, 16);
        a1 = dsra32(a1, 16);
        ld(a0, sp, 0x70);
        mov_s(f12, f21);
        a3 = s1;
        jal(ctx, 0x1248C0u, gen::fn_sub_1236A0_001236a0);
    }
    // 0x001248c8
    charge(ctx, 3);
    v1 = slti(s3, 15);
    if (v1 == 0) {
        // 0x001248d4
        charge(ctx, 3);
        at = slti(s3, 19);
        if (at == 0) {
            // 0x00124980
            charge(ctx, 18);
            s1 = 0;
            a0 = s4;
            jal(ctx, 0x124988u, gen::fn_sub_16C570_0016c570);  // [datGetPcSp]
            v1 = v0 & 0xFFFF;
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            s0 = sll(v0, 2);
            a0 = s4;
            jal(ctx, 0x1249ACu, gen::fn_sub_16C670_0016c670);  // [datGetPcMaxSp]
            v0 = v0 & 0xFFFF;
            div(s0, v0);
            mflo(v1);
            v0 = 76;
            a2 = subu(v0, v1);
        } else {
            // 0x001248e0
            charge(ctx, 6);
            v1 = addiu(s3, -15);
            v0 = sll(v1, 8);
            v0 = subu(v0, v1);
            v1 = sra(v0, 2);
            if (i64(v0) < 0) {
                // 0x001248f8
                charge(ctx, 2);
                v0 = addiu(v0, 3);
                v1 = sra(v0, 2);
            }
            // 0x00124900
            charge(ctx, 22);
            v0 = 255;
            s1 = subu(v0, v1);
            a0 = s4;
            jal(ctx, 0x12490Cu, gen::fn_sub_16C570_0016c570);  // [datGetPcSp]
            v1 = v0 & 0xFFFF;
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            s0 = sll(v0, 2);
            a0 = s4;
            jal(ctx, 0x124930u, gen::fn_sub_16C670_0016c670);  // [datGetPcMaxSp]
            v0 = v0 & 0xFFFF;
            div(s0, v0);
            mflo(v1);
            v0 = addiu(s3, -15);
            mult(v0, v1, v0);
            a0 = sra(v0, 2);
            if (i64(v0) < 0) {
                // 0x00124958
                charge(ctx, 2);
                v0 = addiu(v0, 3);
                a0 = sra(v0, 2);
            }
            // 0x00124960
            charge(ctx, 3);
            at = slt(v1, a0);
            if (at != 0) {
                // 0x0012496c
                charge(ctx, 1);
                a0 = v1;
            }
            // 0x00124970
            charge(ctx, 4);
            v0 = 76;
            a2 = subu(v0, a0);
        }
        // 0x001249c8
        charge(ctx, 7);
        a1 = dsll32(s4, 16);
        a1 = dsra32(a1, 16);
        ld(a0, sp, 0x70);
        mov_s(f12, f21);
        a3 = s1;
        jal(ctx, 0x1249DCu, gen::fn_sub_123B70_00123b70);  // the SP block
    }
    // 0x001249e4
    charge(ctx, 3);
    v1 = slti(s3, 15);
    if (v1 == 0) {
        // 0x001249f0
        charge(ctx, 3);
        at = slti(s3, 19);
        if (at == 0) {
            // 0x00124a64
            charge(ctx, 2);
            s1 = 0;
            sw(zero, sp, 0x88);
        } else {
            // 0x001249fc
            charge(ctx, 6);
            v1 = addiu(s3, -15);
            v0 = sll(v1, 8);
            v0 = subu(v0, v1);
            v1 = sra(v0, 2);
            if (i64(v0) < 0) {
                // 0x00124a14
                charge(ctx, 2);
                v0 = addiu(v0, 3);
                v1 = sra(v0, 2);
            }
            // 0x00124a1c
            charge(ctx, 10);
            v0 = 255;
            s1 = subu(v0, v1);
            v0 = 19;
            v1 = subu(v0, s3);
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v1 = sll(v0, 3);
            v0 = sra(v1, 2);
            if (i64(v1) < 0) {
                // 0x00124a44
                charge(ctx, 2);
                v0 = addiu(v1, 3);
                v0 = sra(v0, 2);
            }
            // 0x00124a4c
            charge(ctx, 6);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x88);
        }
        // 0x00124a6c
        charge(ctx, 11);
        lwc1(f1, sp, 0x70);
        lwc1(f0, sp, 0x88);
        sub_s(f0, f1, f0);
        swc1(f0, sp, 0x88);
        swc1(f20, sp, 0x8C);
        ld(a0, sp, 0x88);
        mov_s(f12, f21);
        a1 = s4;
        a2 = s1;
        jal(ctx, 0x124A90u, gen::fn_sub_123F80_00123f80);  // the condition icon
    }
    // 0x00124a98
    charge(ctx, 3);
    v1 = slti(s3, 16);
    if (v1 == 0) {
        // 0x00124aa4
        charge(ctx, 3);
        at = slti(s3, 20);
        if (at == 0) {
            // 0x00124ae0
            charge(ctx, 1);
            a2 = 0;
        } else {
            // 0x00124ab0
            charge(ctx, 6);
            v1 = addiu(s1, -16);
            v0 = sll(v1, 8);
            v0 = subu(v0, v1);
            v1 = sra(v0, 2);
            if (i64(v0) < 0) {
                // 0x00124ac8
                charge(ctx, 2);
                v0 = addiu(v0, 3);
                v1 = sra(v0, 2);
            }
            // 0x00124ad0
            charge(ctx, 4);
            v0 = 255;
            a2 = subu(v0, v1);
        }
        // 0x00124ae4
        charge(ctx, 5);
        ld(a0, sp, 0x70);
        mov_s(f12, f21);
        a1 = s4;
        jal(ctx, 0x124AF0u, gen::fn_sub_124090_00124090);  // the sparkle ring
    }
    // 0x00124af8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00124B30 sub_124B30 -- 708 bytes; frame 0x80: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [H_Camp_StatusDrawPcPanel] (xy, ?, pc, alpha): the same panel drawn at once: frame, level digits, HP / SP blocks with
// their gauges (76 - 76 * cur / max), condition icon, sparkle ring.
void sub_124B30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20};
    // 0x00124b30
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x60);
    mov_s(f20, f12);
    s3 = a2;
    s2 = a3;
    sd(a0, sp, 0x78);
    v0 = 0x41B00000;  // 22.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x78);
    add_s(f12, f1, f0);
    v0 = 0x421C0000;  // 39.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x7C);
    add_s(f1, f1, f0);
    v0 = 0x41400000;  // 12.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s2 & 0xFF;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 0;
    mov_s(f14, f20);
    jal(ctx, 0x124BA4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    ld(v0, sp, 0x60);
    sd(v0, sp, 0x70);
    a0 = s3;
    jal(ctx, 0x124BB8u, gen::fn_sub_16C470_0016c470);  // [datGetPcLevel]
    v0 = v0 & 0xFF;
    v0 = slti(v0, 10);
    if (v0 == 0) {
        // 0x00124bd0
        charge(ctx, 34);
        a0 = 2;
        jal(ctx, 0x124BD4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
        s0 = v0;
        a0 = s3;
        jal(ctx, 0x124BE4u, gen::fn_sub_16C470_0016c470);  // [datGetPcLevel]
        v1 = v0 & 0xFF;
        v0 = 10;
        div(v1, v0);
        mflo(v0);
        a2 = addiu(v0, 11);
        v0 = 0x42A20000;  // 81.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x70);
        add_s(f12, f1, f0);
        v0 = 0x42500000;  // 52.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x74);
        add_s(f1, f1, f0);
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f1, f1, f0);
        v0 = 0x41400000;  // 12.0f
        mtc1(v0, f0);
        sub_s(f13, f1, f0);
        a3 = s2 & 0xFF;
        a0 = s1;
        a1 = s0;
        mov_s(f14, f20);
        jal(ctx, 0x124C50u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x00124c58
    charge(ctx, 103);
    a0 = 2;
    jal(ctx, 0x124C5Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
    s0 = v0;
    a0 = s3;
    jal(ctx, 0x124C6Cu, gen::fn_sub_16C470_0016c470);  // [datGetPcLevel]
    v1 = v0 & 0xFF;
    v0 = 10;
    div(v1, v0);
    mfhi(v0);
    a2 = addiu(v0, 11);
    v0 = 0x42C00000;  // 96.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x70);
    add_s(f12, f1, f0);
    v0 = 0x42500000;  // 52.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x74);
    add_s(f1, f1, f0);
    v0 = 0x3F800000;  // 1.0f
    mtc1(v0, f0);
    sub_s(f1, f1, f0);
    v0 = 0x41400000;  // 12.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s2 & 0xFF;
    a0 = s1;
    a1 = s0;
    mov_s(f14, f20);
    jal(ctx, 0x124CD8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = s3;
    jal(ctx, 0x124CE4u, gen::fn_sub_16C4F0_0016c4f0);  // [datGetPcHp]
    v1 = v0 & 0xFFFF;
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    s0 = sll(v0, 2);
    a0 = s3;
    jal(ctx, 0x124D08u, gen::fn_sub_16C5F0_0016c5f0);  // [datGetPcMaxHp]
    v0 = v0 & 0xFFFF;
    div(s0, v0);
    mflo(v1);
    v0 = 76;
    a2 = subu(v0, v1);
    s0 = dsll32(s3, 16);
    s0 = dsra32(s0, 16);
    ld(a0, sp, 0x60);
    mov_s(f12, f20);
    a1 = s0;
    a3 = s2;
    jal(ctx, 0x124D3Cu, gen::fn_sub_1236A0_001236a0);
    a0 = s3;
    jal(ctx, 0x124D48u, gen::fn_sub_16C570_0016c570);  // [datGetPcSp]
    v1 = v0 & 0xFFFF;
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    s1 = sll(v0, 2);
    a0 = s3;
    jal(ctx, 0x124D6Cu, gen::fn_sub_16C670_0016c670);  // [datGetPcMaxSp]
    v0 = v0 & 0xFFFF;
    div(s1, v0);
    mflo(v1);
    v0 = 76;
    a2 = subu(v0, v1);
    ld(a0, sp, 0x60);
    mov_s(f12, f20);
    a1 = s0;
    a3 = s2;
    jal(ctx, 0x124D98u, gen::fn_sub_123B70_00123b70);  // the SP block
    ld(a0, sp, 0x60);
    mov_s(f12, f20);
    a1 = s3;
    a2 = s2;
    jal(ctx, 0x124DB0u, gen::fn_sub_123F80_00123f80);  // the condition icon
    ld(a0, sp, 0x60);
    mov_s(f12, f20);
    a1 = s3;
    a2 = s2;
    jal(ctx, 0x124DC8u, gen::fn_sub_124090_00124090);  // the sparkle ring
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00125D70 sub_125D70 -- 2412 bytes; frame 0x70: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [H_Camp_UpdateStatusPartsTask] Update of a status sub-task ("H_PcStatusParts00", created by sub_1269A0 state 3):
// state 0 -> 1; mode +4 = 0 waits, 1 fades the backdrop in over 8 frames (+6 counter), 2 fades it out; draws the
// persona background, the frame strip and the camp file 1 / 12 decorations.
void sub_125D70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00125d70
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s2, a0, 60);
    lw(v1, s2, 0);
    v0 = 1;
    if (v1 != v0) {
        // 0x00125da8
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00125db8
            charge(ctx, 2);
            sh(zero, s2, 6);
            sw(v0, s2, 0);
            goto L_00125dc0;
        }
        // 0x00125db0
        charge(ctx, 2);
        // 0x001266ac (the shared epilogue, written out on this path)
        charge(ctx, 12);
        v0 = 0;
        ld(ra, sp, 0x60);
        lq(s4, sp, 0x50);
        lq(s3, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        lwc1(f21, sp, 0x4);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x70);
        return;
    }
L_00125dc0:
    charge(ctx, 3);
    lh(v1, s2, 4);
    if (v1 != 0) {
        // 0x001262b8
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x001264c0
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x001264cc
                charge(ctx, 4);
                lh(v1, s2, 6);
                v0 = 8;
                if (v1 != v0) {
                    // 0x001264dc
                    charge(ctx, 5);
                    v0 = sll(v1, 8);
                    v1 = subu(v0, v1);
                    v0 = sra(v1, 3);
                    if (i64(v1) < 0) {
                        // 0x001264f0
                        charge(ctx, 2);
                        v0 = addiu(v1, 7);
                        v0 = sra(v0, 3);
                    }
                    // 0x001264f8
                    charge(ctx, 109);
                    s0 = dsll32(v0, 16);
                    s0 = dsra32(s0, 16);
                    lh(v0, s2, 6);
                    v0 = addiu(v0, 1);
                    sh(v0, s2, 6);
                    a0 = 0;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(2));  // 0x833B78: camp sprite file 2
                    a2 = 0;
                    jal(ctx, 0x12651Cu, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                    s2 = v0;
                    v1 = 0x42CA0000;  // 101.0f
                    sw(v1, v0, 44);
                    v1 = 449;
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    swc1(f0, v0, 16);
                    v1 = 0x41E80000;  // 29.0f
                    sw(v1, v0, 20);
                    sb(s0, v0, 24);
                    v1 = 3624;
                    sh(v1, v0, 40);
                    sh(v1, v0, 42);
                    a0 = s2;
                    a1 = 1;
                    jal(ctx, 0x126564u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                    a0 = s2;
                    jal(ctx, 0x126570u, gen::fn_sub_115980_00115980);  // draw and release the handle
                    v0 = 0x42080000;  // 34.0f
                    mtc1(v0, f12);
                    v0 = 415;
                    mtc1(v0, f0);
                    cvt_s_w(f13, f0);
                    a3 = s0 & 0xFF;
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f14);
                    a0 = s1;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
                    a2 = 0;
                    jal(ctx, 0x1265ACu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v0 = 0x42480000;  // 50.0f
                    mtc1(v0, f12);
                    v0 = 415;
                    mtc1(v0, f0);
                    cvt_s_w(f13, f0);
                    a3 = s0 & 0xFF;
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f14);
                    a0 = s1;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
                    a2 = 9;
                    jal(ctx, 0x1265E8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v0 = 0x43420000;  // 194.0f
                    mtc1(v0, f12);
                    v0 = 415;
                    mtc1(v0, f0);
                    cvt_s_w(f13, f0);
                    a3 = s0 & 0xFF;
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f14);
                    a0 = s1;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
                    a2 = 11;
                    jal(ctx, 0x126624u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v0 = 561;
                    mtc1(v0, f0);
                    cvt_s_w(f12, f0);
                    v0 = 415;
                    mtc1(v0, f0);
                    cvt_s_w(f13, f0);
                    a3 = s0 & 0xFF;
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f14);
                    a0 = s1;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
                    a2 = 1;
                    jal(ctx, 0x126668u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v0 = 0x43BF0000;  // 382.0f
                    mtc1(v0, f12);
                    v0 = 415;
                    mtc1(v0, f0);
                    cvt_s_w(f13, f0);
                    a3 = s0 & 0xFF;
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f14);
                    a0 = s1;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
                    a2 = 4;
                    jal(ctx, 0x1266A4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                }
            }
        } else {
            // 0x001262c4
            charge(ctx, 4);
            lh(v1, s2, 6);
            v0 = 8;
            if (v1 != v0) {
                // 0x001262e0
                charge(ctx, 5);
                v0 = sll(v1, 8);
                v0 = subu(v0, v1);
                v1 = sra(v0, 3);
                if (i64(v0) < 0) {
                    // 0x001262f4
                    charge(ctx, 2);
                    v0 = addiu(v0, 7);
                    v1 = sra(v0, 3);
                }
                // 0x001262fc
                charge(ctx, 7);
                v0 = 255;
                v0 = subu(v0, v1);
                s3 = dsll32(v0, 16);
                s3 = dsra32(s3, 16);
                lh(v0, s2, 6);
                v0 = addiu(v0, 1);
                sh(v0, s2, 6);
            } else {
                // 0x001262d4
                charge(ctx, 3);
                s3 = 0;
            }
            // 0x00126318
            charge(ctx, 106);
            a0 = 0;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(2));  // 0x833B78: camp sprite file 2
            a2 = 0;
            jal(ctx, 0x126328u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
            s0 = v0;
            v1 = 0x42CA0000;  // 101.0f
            sw(v1, v0, 44);
            v1 = 449;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            swc1(f0, v0, 16);
            v1 = 0x41E80000;  // 29.0f
            sw(v1, v0, 20);
            sb(s3, v0, 24);
            v1 = 3624;
            sh(v1, v0, 40);
            sh(v1, v0, 42);
            a0 = s0;
            a1 = 1;
            jal(ctx, 0x126370u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
            a0 = s0;
            jal(ctx, 0x12637Cu, gen::fn_sub_115980_00115980);  // draw and release the handle
            v0 = 0x42080000;  // 34.0f
            mtc1(v0, f12);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f13, f0);
            a3 = s3 & 0xFF;
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f14);
            a0 = s1;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
            a2 = 0;
            jal(ctx, 0x1263B8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f12);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f13, f0);
            a3 = s3 & 0xFF;
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f14);
            a0 = s1;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
            a2 = 9;
            jal(ctx, 0x1263F4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 0x43420000;  // 194.0f
            mtc1(v0, f12);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f13, f0);
            a3 = s3 & 0xFF;
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f14);
            a0 = s1;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
            a2 = 11;
            jal(ctx, 0x126430u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 561;
            mtc1(v0, f0);
            cvt_s_w(f12, f0);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f13, f0);
            a3 = s3 & 0xFF;
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f14);
            a0 = s1;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
            a2 = 1;
            jal(ctx, 0x126474u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 0x43BF0000;  // 382.0f
            mtc1(v0, f12);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f13, f0);
            a3 = s3 & 0xFF;
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f14);
            a0 = s1;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
            a2 = 4;
            jal(ctx, 0x1264B0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        }
    } else {
        // 0x00125dcc
        charge(ctx, 4);
        lh(v0, s2, 6);
        at = slti(v0, 5);
        if (at != 0) {
            // 0x00125ddc
            charge(ctx, 3);
            lw(v0, gp, g::kPersonaTexTask);  // 0x7CDF60
            if (v0 != 0) {
                // 0x00125df4
                charge(ctx, 5);
                lw(a0, v0, 60);
                lw(v1, a0, 0);
                v0 = 3;
                if (v1 != v0) {
                    // 0x00125e14
                    charge(ctx, 1);
                    t0 = 0;
                } else {
                    // 0x00125e08
                    charge(ctx, 3);
                    lw(t0, a0, 12);
                }
            } else {
                // 0x00125de8
                charge(ctx, 3);
                t0 = 0;
            }
            // 0x00125e18
            charge(ctx, 2);
            if (t0 != 0) {
                // 0x00125e20
                charge(ctx, 12);
                v0 = 0x42CC0000;  // 102.0f
                mtc1(v0, f12);
                mtc1(zero, f13);
                v0 = lui(0xC2AE);
                mtc1(v0, f14);
                a0 = si(-1);
                v0 = 0x4FA40000;
                a1 = v0 | 0xFF19;
                a2 = 640;
                a3 = a2;
                jal(ctx, 0x125E48u, gen::fn_sub_114450_00114450);  // [nine-slice window] / the persona picture
            }
            // 0x00125e50
            charge(ctx, 31);
            mtc1(zero, f12);
            v0 = 0x42CC0000;  // 102.0f
            mtc1(v0, f14);
            mov_s(f13, f12);
            a0 = 0;
            a1 = 0;
            jal(ctx, 0x125E68u, gen::fn_nullsub_3_0011bba0);
            a0 = 0;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(2));  // 0x833B78: camp sprite file 2
            a2 = 0;
            jal(ctx, 0x125E80u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
            s3 = v0;
            v1 = 0x42CA0000;  // 101.0f
            sw(v1, v0, 44);
            v1 = 0x43D60000;  // 428.0f
            sw(v1, v0, 16);
            v1 = 0x41D80000;  // 27.0f
            sw(v1, v0, 20);
            sb(zero, v0, 24);
            sh(zero, v0, 40);
            sh(zero, v0, 42);
            a0 = s3;
            a1 = 1;
            jal(ctx, 0x125EB8u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
            a0 = s3;
            jal(ctx, 0x125EC4u, gen::fn_sub_115980_00115980);  // draw and release the handle
        }
        // 0x00125ecc
        charge(ctx, 4);
        lh(v1, s2, 6);
        v0 = slti(v1, 5);
        if (v0 == 0) {
            // 0x00125edc
            charge(ctx, 3);
            at = slti(v1, 20);
            if (at != 0) {
                // 0x00125ee8
                charge(ctx, 21);
                v0 = addiu(v1, -5);
                s0 = dsll32(v0, 16);
                s0 = dsra32(s0, 16);
                v0 = sll(s0, 2);
                v1 = addu(v0, s0);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                v1 = sll(v0, 5);
                v0 = 15;
                div(v1, v0);
                mflo(v1);
                v0 = subu(0, v1);
                mtc1(v0, f0);
                cvt_s_w(f13, f0);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                lw(v0, gp, g::kPersonaTexTask);  // 0x7CDF60
                if (v0 != 0) {
                    // 0x00125f48
                    charge(ctx, 5);
                    lw(a0, v0, 60);
                    lw(v1, a0, 0);
                    v0 = 3;
                    if (v1 != v0) {
                        // 0x00125f68
                        charge(ctx, 1);
                        t0 = 0;
                    } else {
                        // 0x00125f5c
                        charge(ctx, 3);
                        lw(t0, a0, 12);
                    }
                } else {
                    // 0x00125f3c
                    charge(ctx, 3);
                    t0 = 0;
                }
                // 0x00125f6c
                charge(ctx, 2);
                if (t0 != 0) {
                    // 0x00125f74
                    charge(ctx, 13);
                    v0 = 0x42CC0000;  // 102.0f
                    mtc1(v0, f12);
                    v0 = lui(0xC2AE);
                    mtc1(v0, f0);
                    add_s(f14, f0, f1);
                    a0 = si(-1);
                    v0 = 0x4FA40000;
                    a1 = v0 | 0xFF19;
                    a2 = 640;
                    a3 = a2;
                    jal(ctx, 0x125FA0u, gen::fn_sub_114450_00114450);  // [nine-slice window] / the persona picture
                }
                // 0x00125fa8
                charge(ctx, 6);
                mtc1(zero, f13);
                v0 = 0x42CC0000;  // 102.0f
                mtc1(v0, f14);
                at = slti(s0, 11);
                if (at != 0) {
                    // 0x00125fcc
                    charge(ctx, 5);
                    v0 = sll(s0, 8);
                    v1 = subu(v0, s0);
                    v0 = 10;
                    div(v1, v0);
                    mflo(v0);
                } else {
                    // 0x00125fc0
                    charge(ctx, 3);
                    v0 = 255;
                }
                // 0x00125fe0
                charge(ctx, 6);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                mov_s(f12, f13);
                a1 = 0;
                jal(ctx, 0x125FF0u, gen::fn_nullsub_3_0011bba0);
            }
        }
        // 0x00125ff8
        charge(ctx, 4);
        lh(v1, s2, 6);
        v0 = slti(v1, 5);
        if (v0 == 0) {
            // 0x00126008
            charge(ctx, 3);
            at = slti(v1, 15);
            if (at == 0) {
                // 0x00126090
                charge(ctx, 5);
                v0 = 0x41A80000;  // 21.0f
                mtc1(v0, f21);
                v0 = 0x40000000;  // 2.0f
                mtc1(v0, f20);
                s4 = 3624;
            } else {
                // 0x00126014
                charge(ctx, 31);
                v0 = addiu(v1, -5);
                s0 = dsll32(v0, 16);
                s0 = dsra32(s0, 16);
                mtc1(s0, f0);
                cvt_s_w(f2, f0);
                v0 = 0x41A80000;  // 21.0f
                mtc1(v0, f0);
                mul_s(f0, f0, f2);
                v0 = 0x41200000;  // 10.0f
                mtc1(v0, f1);
                div_s(f21, f0, f1);
                v0 = 0x40000000;  // 2.0f
                mtc1(v0, f0);
                mul_s(f0, f0, f2);
                div_s(f20, f0, f1);
                v0 = sll(s0, 4);
                v0 = subu(v0, s0);
                v0 = sll(v0, 2);
                v0 = subu(v0, s0);
                v1 = sll(v0, 3);
                v0 = 10;
                div(v1, v0);
                mflo(v1);
                v0 = 4096;
                s4 = subu(v0, v1);
            }
            // 0x001260a4
            charge(ctx, 29);
            a0 = 0;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(2));  // 0x833B78: camp sprite file 2
            a2 = 0;
            jal(ctx, 0x1260B4u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
            s3 = v0;
            v1 = 0x42CA0000;  // 101.0f
            sw(v1, v0, 44);
            v1 = 0x43D60000;  // 428.0f
            mtc1(v1, f0);
            add_s(f0, f0, f21);
            swc1(f0, v0, 16);
            v1 = 0x41D80000;  // 27.0f
            mtc1(v1, f0);
            add_s(f0, f0, f20);
            swc1(f0, v0, 20);
            sb(zero, v0, 24);
            sh(s4, v0, 40);
            sh(s4, v0, 42);
            a0 = s3;
            a1 = 1;
            jal(ctx, 0x126104u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
            a0 = s3;
            jal(ctx, 0x126110u, gen::fn_sub_115980_00115980);  // draw and release the handle
        }
        // 0x00126118
        charge(ctx, 4);
        lh(v1, s2, 6);
        v0 = slti(v1, 15);
        if (v0 == 0) {
            // 0x00126128
            charge(ctx, 8);
            v0 = dsll32(s0, 16);
            v0 = dsra32(v0, 16);
            v0 = addiu(v0, -10);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            at = slti(v1, 20);
            if (at == 0) {
                // 0x00126160
                charge(ctx, 1);
                s0 = 0;
            } else {
                // 0x00126148
                charge(ctx, 6);
                v1 = 255;
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                s0 = subu(v1, v0);
            }
            // 0x00126164
            charge(ctx, 77);
            v0 = 0x42080000;  // 34.0f
            mtc1(v0, f12);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f13, f0);
            a3 = s0 & 0xFF;
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f14);
            a0 = s1;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
            a2 = 0;
            jal(ctx, 0x126198u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f12);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f13, f0);
            a3 = s0 & 0xFF;
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f14);
            a0 = s1;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
            a2 = 9;
            jal(ctx, 0x1261D4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 0x43420000;  // 194.0f
            mtc1(v0, f12);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f13, f0);
            a3 = s0 & 0xFF;
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f14);
            a0 = s1;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
            a2 = 11;
            jal(ctx, 0x126210u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 561;
            mtc1(v0, f0);
            cvt_s_w(f12, f0);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f13, f0);
            a3 = s0 & 0xFF;
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f14);
            a0 = s1;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
            a2 = 1;
            jal(ctx, 0x126254u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 0x43BF0000;  // 382.0f
            mtc1(v0, f12);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f13, f0);
            a3 = s0 & 0xFF;
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f14);
            a0 = s1;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
            a2 = 4;
            jal(ctx, 0x126290u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        }
        // 0x00126298
        charge(ctx, 4);
        lh(v0, s2, 6);
        at = slti(v0, 20);
        if (at != 0) {
            // 0x001262a8
            charge(ctx, 4);
            v0 = addiu(v0, 1);
            sh(v0, s2, 6);
        }
    }
    // 0x001266ac (the shared epilogue, written out on this path)
    charge(ctx, 12);
    v0 = 0;
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

// 0x001269A0 sub_1269A0 -- 2564 bytes; frame 0x80: ra sp+0x60, s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq)
// [H_Camp_UpdateStatusDrawTask] Update of "H_CampStatusDraw" (the Status page; jump table 0x7B5B10): state 0 starts the
// texture build of camp/status/i_camp_hum_blue.tmx (The Answer: AGS_i_camp_hum_blue_03.tmx) into +60; 1 polls it (+64
// the texture); 2 waits for the flash transition 2; 3 closes the main list (sub_11D3A0), creates "H_PcStatusParts00"
// and sets the side portraits to screen 2; 4 is the input state: cancel (0x20) closes, R1 / L1 (0x2000 / 0x8000) answer
// "switch page" to the root (+12); 5 / 6 and 7 / 8 the two exits (-1). Every state draws the page (sub_1273B0, the 512
// x 1024 strips sub_126710).
void sub_1269A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x001269a0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    s2 = a0;
    lw(s1, a0, 60);
    lw(v0, s1, sts::kState);
    at = sltiu(v0, 9);
    if (at != 0) {
        // 0x001269d0
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 23312);  // &0x7B5B10
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x1269ECu:  // table[0]: state 0: start the character picture build
            // 0x001269ec
            charge(ctx, 6);
            v0 = lui(0xC1A0);
            sw(v0, s1, sts::kSlide);
            jal(ctx, 0x1269F4u, gen::fn_sub_17D800_0017d800);  // 1 in The Answer
            if (v0 == 0) {
                // 0x00126a58
                charge(ctx, 19);
                sd(zero, sp, 0x0);
                sd(zero, sp, 0x8);
                v0 = 0x5E0000;
                v0 = addiu(v0, -20352);  // "_h_camp_status.c"
                sd(v0, sp, 0x10);
                v0 = 1777;
                sd(v0, sp, 0x18);
                a0 = 0;
                a1 = 0x5E0000;
                a1 = addiu(a1, -20320);  // "camp/status/i_camp_hum_blue.tmx"
                a2 = 0;
                a3 = 0;
                t0 = 0;
                t1 = 0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x126A98u, gen::fn_sub_10C1A0_0010c1a0);  // start a texture build
                sw(v0, s1, sts::kBuild);
            } else {
                // 0x00126a04
                charge(ctx, 21);
                sd(zero, sp, 0x0);
                sd(zero, sp, 0x8);
                v0 = 0x5E0000;
                v0 = addiu(v0, -20352);  // "_h_camp_status.c"
                sd(v0, sp, 0x10);
                v0 = 1775;
                sd(v0, sp, 0x18);
                a0 = 0;
                a1 = 0x5E0000;
                a1 = addiu(a1, -20400);  // "camp/status/AGS_i_camp_hum_blue_03.tmx"
                a2 = 0;
                a3 = 0;
                t0 = 0;
                t1 = 0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x126A44u, gen::fn_sub_10C1A0_0010c1a0);  // start a texture build
                sw(v0, s1, sts::kBuild);
            }
            // 0x00126aa4
            charge(ctx, 4);
            v0 = 1;
            sw(v0, s1, sts::kState);
        L_00127380:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x126AB4u:  // table[1]: state 1: poll the build
            // 0x00126ab4
            charge(ctx, 9);
            lw(a0, s1, sts::kBuild);
            a1 = addiu(sp, 0x7C);
            a2 = 0;
            jal(ctx, 0x126AC0u, gen::fn_sub_10C3A0_0010c3a0);  // poll the texture build
            sw(v0, s1, sts::kTexture);
            lw(v0, sp, 0x7C);
            if (v0 != 0) {
                // 0x00126ad8
                charge(ctx, 4);
                v0 = 2;
                sw(v0, s1, sts::kState);
            }
            goto L_00127380;
        case 0x126AE8u:  // table[2]: state 2: wait for flash 2
            // 0x00126ae8
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 2;
            jal(ctx, 0x126AF0u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x00126b00
                charge(ctx, 4);
                v0 = 3;
                sw(v0, s1, sts::kState);
            }
            goto L_00127380;
        case 0x126B10u:  // table[3]: state 3: close the main list, create the status parts, portraits to screen 2
            // 0x00126b10
            charge(ctx, 5);
            lw(v0, gp, g::kCampFlashTask);  // 0x7CDF50
            lw(v0, v0, 60);
            lw(v0, v0, 16);
            if (v0 != 0) {
                // 0x00126b24
                charge(ctx, 3);
                lh(v1, s1, 16);
                if (v1 != 0) {
                    // 0x00126b68
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x00126b74
                        charge(ctx, 1);
                        sh(zero, s1, 18);
                    }
                } else {
                    // 0x00126b30
                    charge(ctx, 14);
                    sh(zero, s1, 18);
                    lw(v0, gp, g::kCampRootTask);  // 0x7CDF5C
                    lw(s0, v0, 60);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a0 = s0;
                    jal(ctx, 0x126B48u, gen::fn_sub_11D3A0_0011d3a0);  // [H_Camp_RootFadeOut]
                    v0 = 8;
                    sw(v0, s0, 0);
                    v0 = 22;
                    sw(v0, s0, 4);
                }
                // 0x00126b78
                charge(ctx, 11);
                lh(s0, s1, 16);
                a0 = 1;
                a1 = 12;
                a2 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 388);  // 0x960184
                jalr(ctx, 0x126B90u, v0.u());
                s3 = v0;
                if (s3 != 0) {
                    // 0x00126bb0
                    charge(ctx, 13);
                    a0 = s2;
                    a1 = 0x5E0000;
                    a1 = addiu(a1, -20432);  // "H_PcStatusParts00"
                    a2 = 6334;
                    a3 = 0x120000;
                    a3 = addiu(a3, 23920);  // &sub_125D70
                    t0 = 0x120000;
                    t0 = addiu(t0, 26336);  // &sub_1266E0
                    t1 = s3;
                    jal(ctx, 0x126BD4u, gen::fn_kwlnTaskCreate_00194b20);  // (parent, name, priority, update, destroy, work)
                    if (v0 != 0) {
                        // 0x00126bf0
                        charge(ctx, 1);
                        sh(s0, s3, 4);
                    } else {
                        // 0x00126be4
                        charge(ctx, 3);
                        v0 = 0;
                    }
                } else {
                    // 0x00126ba4
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x00126bf4
                charge(ctx, 17);
                sw(v0, s1, sts::kParts);
                lw(a0, gp, g::kCampPcKani);  // 0x7CDF54
                a1 = 2;
                jal(ctx, 0x126C00u, gen::fn_sub_121DE0_00121de0);  // [H_Camp_PcKaniSetScreen]
                lw(a0, gp, g::kCampPersonaKani);  // 0x7CDF58
                a1 = 2;
                jal(ctx, 0x126C10u, gen::fn_sub_122710_00122710);  // [H_Camp_PersonaKaniSetScreen]
                lh(v1, s1, 12);
                lw(v0, s1, sts::kParts);
                lw(v0, v0, 60);
                sw(v1, v0, 8);
                v0 = 4;
                sw(v0, s1, sts::kState);
            }
            goto L_00127380;
        case 0x126C38u:  // table[4]: state 4: input (cancel closes, R1 / L1 switch page)
            // 0x00126c38
            charge(ctx, 4);
            lh(v0, s1, 12);
            v1 = 255;
            if (v0 != v1) {
                // 0x00126c48
                charge(ctx, 7);
                v0 = addiu(v0, 10);
                sh(v0, s1, 12);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                at = slti(v0, 256);
                if (at == 0) {
                    // 0x00126c64
                    charge(ctx, 1);
                    sh(v1, s1, 12);
                }
            }
            // 0x00126c68
            charge(ctx, 3);
            lh(v0, s1, 16);
            if (v0 != 0) {
                // 0x00126c74
                charge(ctx, 4);
                lh(v1, s1, 12);
                lw(v0, s1, sts::kParts);
                lw(v0, v0, 60);
                sw(v1, v0, 8);
            }
            // 0x00126c84
            charge(ctx, 4);
            lh(v1, s1, 16);
            v0 = 1;
            if (v1 != v0) {
                // 0x00126eec
                charge(ctx, 4);
                lh(v1, s1, 18);
                v0 = 8;
                if (v1 != v0) {
                    // 0x00126f64
                    charge(ctx, 2);
                    v0 = addiu(v1, 1);
                    sh(v0, s1, 18);
                } else {
                    // 0x00126efc
                    charge(ctx, 23);
                    v0 = 0x433C0000;  // 188.0f
                    sw(v0, sp, 0x70);
                    lwc1(f0, s1, sts::kSlide);
                    swc1(f0, sp, 0x74);
                    v0 = 0x42D20000;  // 105.0f
                    mtc1(v0, f12);
                    lw(a0, s1, sts::kTexture);
                    ld(a1, sp, 0x70);
                    a2 = 255;
                    jal(ctx, 0x126F20u, gen::fn_sub_126710_00126710);  // two 512 x 1024 strips
                    lwc1(f1, s1, sts::kSlide);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f0);
                    sub_s(f1, f1, f0);
                    swc1(f1, s1, sts::kSlide);
                    v0 = lui(0xC48A);
                    mtc1(v0, f0);
                    c_lt_s(f1, f0);
                    if (cond(ctx)) {
                        // 0x00126f58
                        charge(ctx, 3);
                        sw(zero, s1, sts::kSlide);
                    }
                }
                // 0x00126f6c
                charge(ctx, 16);
                sw(zero, sp, 0x70);
                sw(zero, sp, 0x74);
                lh(v1, s1, 12);
                v0 = 255;
                v0 = subu(v0, v1);
                a2 = dsll32(v0, 16);
                a2 = dsra32(a2, 16);
                a0 = 1;
                ld(a1, sp, 0x70);
                jal(ctx, 0x126F90u, gen::fn_sub_1273B0_001273b0);
                v0 = 0x7E0000;
                lhu(v1, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v0 = v1 & 0x20;  // cancel
                if (v0 == 0) {
                    // 0x00126fd4
                    charge(ctx, 4);
                    v0 = v1 & 0x2000;
                    v0 = sltu(0, v0);
                    if (v0 == 0) {
                        // 0x00126fe4
                        charge(ctx, 4);
                        v0 = 0x7E0000;
                        lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                        v0 = v0 & 0x2000;  // next page
                        v0 = sltu(0, v0);
                    }
                    // 0x00126ff4
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x00126ffc
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        jal(ctx, 0x12700Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = 1;
                        sw(v0, s1, sts::kAnswer);
                    }
                } else {
                    // 0x00126fac
                    charge(ctx, 10);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 2;
                    jal(ctx, 0x126FBCu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    v0 = si(-1);
                    sw(v0, s1, sts::kAnswer);
                }
            } else {
                // 0x00126c94
                charge(ctx, 4);
                lh(v1, s1, 18);
                v0 = 8;
                if (v1 != v0) {
                    // 0x00126d9c
                    charge(ctx, 10);
                    v1 = subu(v0, v1);
                    v0 = sll(v1, 2);
                    v1 = addu(v0, v1);
                    v0 = sll(v1, 2);
                    v0 = addu(v1, v0);
                    v1 = sll(v0, 3);
                    v0 = dsll32(v0, 3);
                    v0 = dsra32(v0, 3);
                    if (i64(v1) < 0) {
                        // 0x00126dc4
                        charge(ctx, 2);
                        v0 = addiu(v1, 7);
                        v0 = sra(v0, 3);
                    }
                    // 0x00126dcc
                    charge(ctx, 29);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x433C0000;  // 188.0f
                    mtc1(v0, f0);
                    sub_s(f0, f0, f1);
                    swc1(f0, sp, 0x70);
                    lwc1(f0, s1, sts::kSlide);
                    swc1(f0, sp, 0x74);
                    v0 = 0x42D20000;  // 105.0f
                    mtc1(v0, f12);
                    lw(a0, s1, sts::kTexture);
                    ld(a1, sp, 0x70);
                    a2 = 255;
                    jal(ctx, 0x126E08u, gen::fn_sub_126710_00126710);  // two 512 x 1024 strips
                    lwc1(f1, s1, sts::kSlide);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f0);
                    sub_s(f1, f1, f0);
                    swc1(f1, s1, sts::kSlide);
                    v0 = lui(0xC48A);
                    mtc1(v0, f0);
                    c_lt_s(f1, f0);
                    if (cond(ctx)) {
                        // 0x00126e40
                        charge(ctx, 1);
                        sw(zero, s1, sts::kSlide);
                    }
                    // 0x00126e44
                    charge(ctx, 11);
                    lh(a0, s1, 18);
                    v0 = 8;
                    v1 = subu(v0, a0);
                    v0 = sll(v1, 5);
                    v0 = subu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = sra(v1, 3);
                    if (i64(v1) < 0) {
                        // 0x00126e70
                        charge(ctx, 2);
                        v0 = addiu(v1, 7);
                        v0 = sra(v0, 3);
                    }
                    // 0x00126e78
                    charge(ctx, 11);
                    v0 = subu(0, v0);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0x70);
                    sw(zero, sp, 0x74);
                    v0 = sll(a0, 8);
                    v1 = subu(v0, a0);
                    v0 = sra(v1, 3);
                    if (i64(v1) < 0) {
                        // 0x00126ea4
                        charge(ctx, 2);
                        v0 = addiu(v1, 7);
                        v0 = sra(v0, 3);
                    }
                    // 0x00126eac
                    charge(ctx, 9);
                    v1 = dsll32(v0, 16);
                    v1 = dsra32(v1, 16);
                    v0 = 255;
                    v0 = subu(v0, v1);
                    s0 = dsll32(v0, 16);
                    s0 = dsra32(s0, 16);
                    lh(v0, s1, 18);
                    v0 = addiu(v0, 1);
                    sh(v0, s1, 18);
                } else {
                    // 0x00126ca4
                    charge(ctx, 23);
                    v0 = 0x433C0000;  // 188.0f
                    sw(v0, sp, 0x70);
                    lwc1(f0, s1, sts::kSlide);
                    swc1(f0, sp, 0x74);
                    v0 = 0x42D20000;  // 105.0f
                    mtc1(v0, f12);
                    lw(a0, s1, sts::kTexture);
                    ld(a1, sp, 0x70);
                    a2 = 255;
                    jal(ctx, 0x126CC8u, gen::fn_sub_126710_00126710);  // two 512 x 1024 strips
                    lwc1(f1, s1, sts::kSlide);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f0);
                    sub_s(f1, f1, f0);
                    swc1(f1, s1, sts::kSlide);
                    v0 = lui(0xC48A);
                    mtc1(v0, f0);
                    c_lt_s(f1, f0);
                    if (cond(ctx)) {
                        // 0x00126d00
                        charge(ctx, 1);
                        sw(zero, s1, sts::kSlide);
                    }
                    // 0x00126d04
                    charge(ctx, 8);
                    sw(zero, sp, 0x70);
                    sw(zero, sp, 0x74);
                    s0 = 0;
                    v0 = 0x7E0000;
                    lhu(v1, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                    v0 = v1 & 0x20;  // cancel
                    if (v0 == 0) {
                        // 0x00126d4c
                        charge(ctx, 4);
                        v0 = v1 & 0x2000;
                        v0 = sltu(0, v0);
                        if (v0 == 0) {
                            // 0x00126d5c
                            charge(ctx, 4);
                            v0 = 0x7E0000;
                            lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                            v0 = v0 & 0x2000;  // next page
                            v0 = sltu(0, v0);
                        }
                        // 0x00126d6c
                        charge(ctx, 2);
                        if (v0 != 0) {
                            // 0x00126d74
                            charge(ctx, 10);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x126D84u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                            v0 = 1;
                            sw(v0, s1, sts::kAnswer);
                        }
                    } else {
                        // 0x00126d24
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 2;
                        jal(ctx, 0x126D34u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = si(-1);
                        sw(v0, s1, sts::kAnswer);
                    }
                }
                // 0x00126ed0
                charge(ctx, 7);
                a0 = 1;
                ld(a1, sp, 0x70);
                a2 = s0;
                jal(ctx, 0x126EDCu, gen::fn_sub_1273B0_001273b0);
            }
            goto L_00127380;
        case 0x127024u:  // table[5]: state 5: wait for flash 1
            // 0x00127024
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 1;
            jal(ctx, 0x12702Cu, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0012703c
                charge(ctx, 2);
                v0 = 6;
                sw(v0, s1, sts::kState);
            }
            // 0x00127044
            charge(ctx, 23);
            v0 = 0x433C0000;  // 188.0f
            sw(v0, sp, 0x70);
            lwc1(f0, s1, sts::kSlide);
            swc1(f0, sp, 0x74);
            v0 = 0x42D20000;  // 105.0f
            mtc1(v0, f12);
            lw(a0, s1, sts::kTexture);
            ld(a1, sp, 0x70);
            a2 = 255;
            jal(ctx, 0x127068u, gen::fn_sub_126710_00126710);  // two 512 x 1024 strips
            lwc1(f1, s1, sts::kSlide);
            v0 = 0x3F800000;  // 1.0f
            mtc1(v0, f0);
            sub_s(f1, f1, f0);
            swc1(f1, s1, sts::kSlide);
            v0 = lui(0xC485);
            mtc1(v0, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x001270a0
                charge(ctx, 1);
                sw(zero, s1, sts::kSlide);
            }
            // 0x001270a4
            charge(ctx, 9);
            sw(zero, sp, 0x70);
            sw(zero, sp, 0x74);
            a0 = 1;
            ld(a1, sp, 0x70);
            a2 = 0;
            jal(ctx, 0x1270B8u, gen::fn_sub_1273B0_001273b0);
            goto L_00127380;
        case 0x1270C8u:  // table[6]: state 6: done (-1)
            // 0x001270c8
            charge(ctx, 7);
            lh(v0, s1, 12);
            v0 = addiu(v0, -25);
            sh(v0, s1, 12);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            if (i64(v0) >= 0) {
                // 0x001270f0
                charge(ctx, 23);
                v0 = 0x433C0000;  // 188.0f
                sw(v0, sp, 0x70);
                lwc1(f0, s1, sts::kSlide);
                swc1(f0, sp, 0x74);
                v0 = 0x42D20000;  // 105.0f
                mtc1(v0, f12);
                lw(a0, s1, sts::kTexture);
                ld(a1, sp, 0x70);
                a2 = 255;
                jal(ctx, 0x127114u, gen::fn_sub_126710_00126710);  // two 512 x 1024 strips
                lwc1(f1, s1, sts::kSlide);
                v0 = 0x3F800000;  // 1.0f
                mtc1(v0, f0);
                sub_s(f1, f1, f0);
                swc1(f1, s1, sts::kSlide);
                v0 = lui(0xC48A);
                mtc1(v0, f0);
                c_lt_s(f1, f0);
                if (cond(ctx)) {
                    // 0x0012714c
                    charge(ctx, 1);
                    sw(zero, s1, sts::kSlide);
                }
                // 0x00127150
                charge(ctx, 13);
                sw(zero, sp, 0x70);
                sw(zero, sp, 0x74);
                lh(v1, s1, 12);
                v0 = 255;
                v0 = subu(v0, v1);
                a2 = dsll32(v0, 16);
                a2 = dsra32(a2, 16);
                a0 = 1;
                ld(a1, sp, 0x70);
                jal(ctx, 0x127174u, gen::fn_sub_1273B0_001273b0);
                goto L_00127380;
            }
            // 0x001270e4
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x127184u:  // table[7]: state 7: page switch
            // 0x00127184
            charge(ctx, 23);
            v0 = 0x433C0000;  // 188.0f
            sw(v0, sp, 0x70);
            lwc1(f0, s1, sts::kSlide);
            swc1(f0, sp, 0x74);
            v0 = 0x42D20000;  // 105.0f
            mtc1(v0, f12);
            lw(a0, s1, sts::kTexture);
            ld(a1, sp, 0x70);
            a2 = 255;
            jal(ctx, 0x1271A8u, gen::fn_sub_126710_00126710);  // two 512 x 1024 strips
            lwc1(f1, s1, sts::kSlide);
            v0 = 0x3F800000;  // 1.0f
            mtc1(v0, f0);
            sub_s(f1, f1, f0);
            swc1(f1, s1, sts::kSlide);
            v0 = lui(0xC48A);
            mtc1(v0, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x001271e0
                charge(ctx, 1);
                sw(zero, s1, sts::kSlide);
            }
            // 0x001271e4
            charge(ctx, 12);
            sw(zero, sp, 0x70);
            sw(zero, sp, 0x74);
            a0 = 1;
            ld(a1, sp, 0x70);
            a2 = 0;
            jal(ctx, 0x1271F8u, gen::fn_sub_1273B0_001273b0);
            lw(v0, gp, g::kCampFlashTask);  // 0x7CDF50
            lw(v0, v0, 60);
            lw(v0, v0, 16);
            if (v0 != 0) {
                // 0x00127214
                charge(ctx, 10);
                sh(zero, s1, 18);
                lw(v0, s1, sts::kParts);
                lw(v1, v0, 60);
                v0 = 2;
                sh(v0, v1, 4);
                sh(zero, v1, 6);
                v0 = 8;
                sw(v0, s1, sts::kState);
            }
            goto L_00127380;
        case 0x12723Cu:  // table[8]: state 8: done (-1)
            // 0x0012723c
            charge(ctx, 8);
            lh(v0, s1, 18);
            v0 = addiu(v0, 1);
            sh(v0, s1, 18);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = 8;
            if (v1 != v0) {
                // 0x00127268
                charge(ctx, 8);
                v0 = sll(v1, 5);
                v0 = subu(v0, v1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                v0 = sra(v1, 3);
                if (i64(v1) < 0) {
                    // 0x00127288
                    charge(ctx, 2);
                    v0 = addiu(v1, 7);
                    v0 = sra(v0, 3);
                }
                // 0x00127290
                charge(ctx, 29);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x433C0000;  // 188.0f
                mtc1(v0, f0);
                sub_s(f0, f0, f1);
                swc1(f0, sp, 0x70);
                lwc1(f0, s1, sts::kSlide);
                swc1(f0, sp, 0x74);
                v0 = 0x42D20000;  // 105.0f
                mtc1(v0, f12);
                lw(a0, s1, sts::kTexture);
                ld(a1, sp, 0x70);
                a2 = 255;
                jal(ctx, 0x1272CCu, gen::fn_sub_126710_00126710);  // two 512 x 1024 strips
                lwc1(f1, s1, sts::kSlide);
                v0 = 0x3F800000;  // 1.0f
                mtc1(v0, f0);
                sub_s(f1, f1, f0);
                swc1(f1, s1, sts::kSlide);
                v0 = lui(0xC48A);
                mtc1(v0, f0);
                c_lt_s(f1, f0);
                if (cond(ctx)) {
                    // 0x00127304
                    charge(ctx, 1);
                    sw(zero, s1, sts::kSlide);
                }
                // 0x00127308
                charge(ctx, 9);
                lh(a0, s1, 18);
                v0 = sll(a0, 5);
                v0 = subu(v0, a0);
                v0 = sll(v0, 2);
                v0 = addu(v0, a0);
                v1 = sll(v0, 2);
                v0 = sra(v1, 3);
                if (i64(v1) < 0) {
                    // 0x0012732c
                    charge(ctx, 2);
                    v0 = addiu(v1, 7);
                    v0 = sra(v0, 3);
                }
                // 0x00127334
                charge(ctx, 11);
                v0 = subu(0, v0);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x70);
                sw(zero, sp, 0x74);
                v0 = sll(a0, 8);
                v1 = subu(v0, a0);
                v0 = sra(v1, 3);
                if (i64(v1) < 0) {
                    // 0x00127360
                    charge(ctx, 2);
                    v0 = addiu(v1, 7);
                    v0 = sra(v0, 3);
                }
                // 0x00127368
                charge(ctx, 6);
                a2 = dsll32(v0, 16);
                a2 = dsra32(a2, 16);
                a0 = 1;
                ld(a1, sp, 0x70);
                jal(ctx, 0x127378u, gen::fn_sub_1273B0_001273b0);
                goto L_00127380;
            }
            // 0x0012725c
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00127384 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x60);
        lq(s3, sp, 0x50);
        lq(s2, sp, 0x40);
        lq(s1, sp, 0x30);
        lq(s0, sp, 0x20);
        sp = addiu(sp, 0x80);
        return;
    }
    goto L_00127380;
}

// 0x001273B0 sub_1273B0 -- 1676 bytes; frame 0x190: ra sp+0x60, s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_StatusDrawSocial] (pc, xy, alpha): the protagonist's social stats: Academics / Charm / Courage rank sprites
// (datGetAcademicLevel / CharmLevel / CourageLevel of the points sub_16C6F0 / 16C740 / 16C790; camp file 9 sprites
// level - 1, + 6, + 13) with their frames, and the next-level exp (sub_16D2F0 through sprintf + sub_40EB50).
void sub_1273B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25};
    // 0x001273b0
    enter(ctx, 419);  // entry check point + this block's cycles
    sp = addiu(sp, -0x190);
    sd(ra, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    sd(a1, sp, 0x78);
    s0 = a2;
    lwc1(f24, sp, 0x7C);
    v0 = 0x42880000;  // 68.0f
    mtc1(v0, f0);
    add_s(f1, f0, f24);
    v0 = 0x41980000;  // 19.0f
    mtc1(v0, f0);
    sub_s(f20, f1, f0);
    v0 = 0x41A80000;  // 21.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x78);
    add_s(f23, f1, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    a2 = 22;
    mov_s(f12, f23);
    mov_s(f13, f20);
    jal(ctx, 0x127444u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x42FE0000;  // 127.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x78);
    add_s(f22, f1, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    a2 = 25;
    mov_s(f12, f22);
    mov_s(f13, f20);
    jal(ctx, 0x127480u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    a2 = 22;
    mov_s(f12, f23);
    mov_s(f13, f20);
    jal(ctx, 0x1274ACu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    a2 = 25;
    mov_s(f12, f22);
    mov_s(f13, f20);
    jal(ctx, 0x1274D8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = s1;
    jal(ctx, 0x1274E4u, gen::fn_sub_16C6F0_0016c6f0);  // [datGetAcademicPoint]
    a0 = v0;
    jal(ctx, 0x1274F0u, gen::fn_datGetAcademicLevel_00177280);
    s2 = dsll32(v0, 16);
    s2 = dsra32(s2, 16);
    v0 = 0x43010000;  // 129.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x78);
    add_s(f21, f1, f0);
    a2 = addiu(s2, -1);
    v0 = 0x42B60000;  // 91.0f
    mtc1(v0, f0);
    add_s(f1, f0, f24);
    v0 = 0x41980000;  // 19.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    mov_s(f12, f21);
    jal(ctx, 0x127550u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x42A40000;  // 82.0f
    mtc1(v0, f0);
    add_s(f1, f0, f24);
    v0 = 0x41980000;  // 19.0f
    mtc1(v0, f0);
    sub_s(f25, f1, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    a2 = 28;
    mov_s(f12, f22);
    mov_s(f13, f25);
    jal(ctx, 0x12759Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43000000;  // 128.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x78);
    add_s(f20, f1, f0);
    v1 = addiu(s2, -1);
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    add_s(f12, f20, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    a2 = 29;
    mov_s(f13, f25);
    jal(ctx, 0x1275F4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x42E80000;  // 116.0f
    mtc1(v0, f0);
    add_s(f1, f0, f24);
    v0 = 0x41980000;  // 19.0f
    mtc1(v0, f0);
    sub_s(f25, f1, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    a2 = 23;
    mov_s(f12, f23);
    mov_s(f13, f25);
    jal(ctx, 0x127640u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    a2 = 26;
    mov_s(f12, f22);
    mov_s(f13, f25);
    jal(ctx, 0x12766Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = s1;
    jal(ctx, 0x127678u, gen::fn_sub_16C740_0016c740);  // [datGetCharmPoint]
    a0 = v0;
    jal(ctx, 0x127684u, gen::fn_datGetCharmLevel_001772f0);
    s2 = dsll32(v0, 16);
    s2 = dsra32(s2, 16);
    a2 = addiu(s2, 6);
    v0 = 0x430B0000;  // 139.0f
    mtc1(v0, f0);
    add_s(f1, f0, f24);
    v0 = 0x41980000;  // 19.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    mov_s(f12, f21);
    jal(ctx, 0x1276D4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43020000;  // 130.0f
    mtc1(v0, f0);
    add_s(f1, f0, f24);
    v0 = 0x41980000;  // 19.0f
    mtc1(v0, f0);
    sub_s(f25, f1, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    a2 = 28;
    mov_s(f12, f22);
    mov_s(f13, f25);
    jal(ctx, 0x127720u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v1 = addiu(s2, -1);
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    add_s(f12, f20, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    a2 = 29;
    mov_s(f13, f25);
    jal(ctx, 0x127768u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43260000;  // 166.0f
    mtc1(v0, f0);
    add_s(f1, f0, f24);
    v0 = 0x41980000;  // 19.0f
    mtc1(v0, f0);
    sub_s(f25, f1, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    a2 = 24;
    mov_s(f12, f23);
    mov_s(f13, f25);
    jal(ctx, 0x1277B4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    a2 = 27;
    mov_s(f12, f22);
    mov_s(f13, f25);
    jal(ctx, 0x1277E0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = s1;
    jal(ctx, 0x1277ECu, gen::fn_sub_16C790_0016c790);  // [datGetCouragePoint]
    a0 = v0;
    jal(ctx, 0x1277F8u, gen::fn_datGetCourageLevel_00177360);
    s2 = dsll32(v0, 16);
    s2 = dsra32(s2, 16);
    a2 = addiu(s2, 13);
    v0 = 0x433D0000;  // 189.0f
    mtc1(v0, f0);
    add_s(f1, f0, f24);
    v0 = 0x41980000;  // 19.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    mov_s(f12, f21);
    jal(ctx, 0x127848u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43340000;  // 180.0f
    mtc1(v0, f0);
    add_s(f1, f0, f24);
    v0 = 0x41980000;  // 19.0f
    mtc1(v0, f0);
    sub_s(f21, f1, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    a2 = 28;
    mov_s(f12, f22);
    mov_s(f13, f21);
    jal(ctx, 0x127894u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v1 = addiu(s2, -1);
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    add_s(f12, f20, f0);
    a3 = s0 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
    a2 = 29;
    mov_s(f13, f21);
    jal(ctx, 0x1278DCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    ld(v0, sp, 0x78);
    sd(v0, sp, 0x188);
    s2 = dsll32(s0, 16);
    s2 = dsra32(s2, 16);
    v0 = 255;
    s0 = subu(v0, s2);
    lwc1(f1, sp, 0x18C);
    v0 = 339;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    add_s(f21, f0, f1);
    v0 = 0x424C0000;  // 51.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x188);
    add_s(f20, f1, f0);
    a3 = s2 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 17;
    mov_s(f12, f20);
    mov_s(f13, f21);
    jal(ctx, 0x127948u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x437E0000;  // 254.0f
    mtc1(v0, f0);
    add_s(f20, f0, f20);
    a3 = s2 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 34;
    mov_s(f12, f20);
    mov_s(f13, f21);
    jal(ctx, 0x127984u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = s1;
    jal(ctx, 0x127990u, gen::fn_sub_16D2F0_0016d2f0);
    a0 = addiu(sp, 0x80);
    a1 = addiu(gp, -30344);  // "%d"
    a2 = v0;
    jal(ctx, 0x1279A4u, gen::fn_sprintf_00523ac8);
    cvt_w_s(f0, f20);
    mfc1(a0, f0);
    v0 = 339;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x188);
    add_s(f1, f1, f0);
    v0 = 0x40000000;  // 2.0f
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(a1, f0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a2 = s0 & 0xFF;
    a3 = 4;
    t0 = addiu(sp, 0x80);
    t1 = 1;
    jal(ctx, 0x1279FCu, gen::fn_sub_40EB50_0040eb50);  // text / number at (x, y)
    ld(ra, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x190);
}

// 0x00127C00 sub_127C00 -- 956 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_UpdateStatusPersonaDrawTask] Update of "H_CampStatusPersonaDraw" (the Status screen's persona page; jump
// table 0x7B5B40): state 0 waits for flash 3 and creates the persona picture (sub_1339A0 of datGetPcPersonaId(1)); 1
// waits for the flash, sets the side portraits to screen 3; 2 fades the table in (+12 by 10 to 255) and is the input
// state (cancel / page switch answered in +20); 3..5 fade out and return -1. Draws the persona picture (sub_133A80) and
// the status table (sub_128140 kinds 0 / 1 / 2).
void sub_127C00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00127c00
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    mtc1(zero, f0);
    sw(zero, sp, 0x3C);
    sw(zero, sp, 0x38);
    lw(v0, s0, 0);
    at = sltiu(v0, 6);
    if (at != 0) {
        // 0x00127c34
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 23360);  // &0x7B5B40
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x127C50u:  // table[0]: state 0: wait for flash 3, create the persona picture
            // 0x00127c50
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 3;
            jal(ctx, 0x127C58u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x00127c68
                charge(ctx, 16);
                a0 = 1;
                jal(ctx, 0x127C6Cu, gen::fn_sub_16C860_0016c860);  // [datGetPcPersonaId]
                v1 = 0x42C80000;  // 100.0f
                mtc1(v1, f12);
                a0 = s1;
                a1 = 6335;
                a2 = v0;
                a3 = si(-1);
                jal(ctx, 0x127C8Cu, gen::fn_sub_1339A0_001339a0);  // [H_Camp_CreatePersonaDispCtlDrawTask]
                sw(v0, s0, 28);
                v0 = 1;
                sw(v0, s0, 0);
            }
        L_00127fa0:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x127CA8u:  // table[1]: state 1: wait for the flash, portraits to screen 3
            // 0x00127ca8
            charge(ctx, 5);
            lw(v0, gp, g::kCampFlashTask);  // 0x7CDF50
            lw(v0, v0, 60);
            lw(v0, v0, 16);
            if (v0 != 0) {
                // 0x00127cbc
                charge(ctx, 13);
                sh(zero, s0, 16);
                lw(a0, gp, g::kCampPcKani);  // 0x7CDF54
                a1 = 3;
                jal(ctx, 0x127CC8u, gen::fn_sub_121DE0_00121de0);  // [H_Camp_PcKaniSetScreen]
                lw(a0, gp, g::kCampPersonaKani);  // 0x7CDF58
                a1 = 3;
                jal(ctx, 0x127CD8u, gen::fn_sub_122710_00122710);  // [H_Camp_PersonaKaniSetScreen]
                v0 = 2;
                sw(v0, s0, 0);
            }
            goto L_00127fa0;
        case 0x127CF0u:  // table[2]: state 2: fade the table in; input
            // 0x00127cf0
            charge(ctx, 7);
            s1 = 0;
            lw(a0, s0, 28);
            jal(ctx, 0x127CF8u, gen::fn_sub_133A80_00133a80);  // draw the persona picture
            lh(v0, s0, 18);
            if (v0 != 0) {
                // 0x00127d70
                charge(ctx, 4);
                lh(v0, s0, 12);
                v1 = 255;
                if (v0 == v1) {
                    // 0x00127da8
                    charge(ctx, 1);
                    s1 = 1;
                } else {
                    // 0x00127d80
                    charge(ctx, 7);
                    v0 = addiu(v0, 10);
                    sh(v0, s0, 12);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    at = slti(v0, 256);
                    if (at == 0) {
                        // 0x00127d9c
                        charge(ctx, 3);
                        sh(v1, s0, 12);
                    }
                }
                // 0x00127dac
                charge(ctx, 16);
                sw(zero, sp, 0x3C);
                sw(zero, sp, 0x38);
                a0 = 1;
                jal(ctx, 0x127DB8u, gen::fn_datPersonaGetByPcId_00174800);
                v1 = 0x42C80000;  // 100.0f
                mtc1(v1, f12);
                lh(a0, s0, 12);
                v1 = 255;
                t0 = subu(v1, a0);
                ld(a0, sp, 0x38);
                a1 = v0;
                a2 = 2;
                a3 = 0;
                jal(ctx, 0x127DE4u, gen::fn_sub_128140_00128140);  // [H_Camp_StatusDrawPanel]
            } else {
                // 0x00127d0c
                charge(ctx, 4);
                lh(v1, s0, 16);
                v0 = 20;
                if (v1 == v0) {
                    // 0x00127d2c
                    charge(ctx, 1);
                    s1 = 1;
                } else {
                    // 0x00127d1c
                    charge(ctx, 4);
                    v0 = addiu(v1, 1);
                    sh(v0, s0, 16);
                }
                // 0x00127d30
                charge(ctx, 16);
                sw(zero, sp, 0x3C);
                sw(zero, sp, 0x38);
                a0 = 1;
                jal(ctx, 0x127D3Cu, gen::fn_datPersonaGetByPcId_00174800);
                v1 = 0x42C80000;  // 100.0f
                mtc1(v1, f12);
                lh(a3, s0, 16);
                ld(a0, sp, 0x38);
                a1 = v0;
                a2 = 0;
                t0 = 0;
                jal(ctx, 0x127D60u, gen::fn_sub_128140_00128140);  // [H_Camp_StatusDrawPanel]
            }
            // 0x00127dec
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x00127df4
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v1, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v0 = v1 & 0x20;  // cancel
                if (v0 == 0) {
                    // 0x00127e30
                    charge(ctx, 4);
                    v0 = v1 & 0x8000;
                    v0 = sltu(0, v0);
                    if (v0 == 0) {
                        // 0x00127e40
                        charge(ctx, 4);
                        v0 = 0x7E0000;
                        lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                        v0 = v0 & 0x8000;  // previous page
                        v0 = sltu(0, v0);
                    }
                    // 0x00127e50
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x00127e58
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        jal(ctx, 0x127E68u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = 1;
                        sw(v0, s0, 20);
                    }
                } else {
                    // 0x00127e08
                    charge(ctx, 10);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 2;
                    jal(ctx, 0x127E18u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    v0 = si(-1);
                    sw(v0, s0, 20);
                }
            }
            goto L_00127fa0;
        case 0x127E80u:  // table[3]: state 3: fade out (close)
            // 0x00127e80
            charge(ctx, 7);
            lh(v0, s0, 12);
            v0 = addiu(v0, -25);
            sh(v0, s0, 12);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
            if (i64(s0) >= 0) {
                // 0x00127ea8
                charge(ctx, 17);
                swc1(f0, sp, 0x3C);
                swc1(f0, sp, 0x38);
                a0 = 1;
                jal(ctx, 0x127EB4u, gen::fn_datPersonaGetByPcId_00174800);
                v1 = 0x42C80000;  // 100.0f
                mtc1(v1, f12);
                v1 = 255;
                t0 = subu(v1, s0);
                ld(a0, sp, 0x38);
                a1 = v0;
                a2 = 2;
                a3 = 0;
                jal(ctx, 0x127EDCu, gen::fn_sub_128140_00128140);  // [H_Camp_StatusDrawPanel]
                goto L_00127fa0;
            }
            // 0x00127e9c
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x127EECu:  // table[4]: state 4: page switch
            // 0x00127eec
            charge(ctx, 19);
            swc1(f0, sp, 0x3C);
            swc1(f0, sp, 0x38);
            a0 = 1;
            jal(ctx, 0x127EF8u, gen::fn_datPersonaGetByPcId_00174800);
            v1 = 0x42C80000;  // 100.0f
            mtc1(v1, f12);
            ld(a0, sp, 0x38);
            a1 = v0;
            a2 = 2;
            a3 = 0;
            t0 = 0;
            jal(ctx, 0x127F1Cu, gen::fn_sub_128140_00128140);  // [H_Camp_StatusDrawPanel]
            lw(v0, gp, g::kCampFlashTask);  // 0x7CDF50
            lw(v0, v0, 60);
            lw(v0, v0, 16);
            if (v0 != 0) {
                // 0x00127f38
                charge(ctx, 5);
                sh(zero, s0, 16);
                v0 = 5;
                sw(v0, s0, 0);
            }
            goto L_00127fa0;
        case 0x127F4Cu:  // table[5]: state 5: fade out (switch)
            // 0x00127f4c
            charge(ctx, 4);
            lh(v1, s0, 16);
            v0 = 10;
            if (v1 != v0) {
                // 0x00127f68
                charge(ctx, 14);
                v0 = addiu(v1, 1);
                sh(v0, s0, 16);
                a0 = 1;
                jal(ctx, 0x127F74u, gen::fn_datPersonaGetByPcId_00174800);
                v1 = 0x42C80000;  // 100.0f
                mtc1(v1, f12);
                lh(a3, s0, 16);
                ld(a0, sp, 0x38);
                a1 = v0;
                a2 = 1;
                t0 = 0;
                jal(ctx, 0x127F98u, gen::fn_sub_128140_00128140);  // [H_Camp_StatusDrawPanel]
                goto L_00127fa0;
            }
            // 0x00127f5c
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00127fa4 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
    goto L_00127fa0;
}

// 0x00128720 sub_128720 -- 1308 bytes; frame 0x80: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_StatusDrawPersonaStats] (xy, bonus, persona, alpha): the five persona stats (St Ma En Ag Lu:
// datPersonaGetTotalStat(persona, i)) as two digits of sprite font 2, plus the bonus bytes +56..+60 of `bonus` when
// given.
void sub_128720(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00128720
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x78);
    mov_s(f22, f12);
    s3 = a1;
    s2 = a2;
    s1 = a3;
    a0 = s2;
    a1 = 0;
    jal(ctx, 0x128764u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
    s4 = v0 & 0xFF;
    if (s3 != 0) {
        // 0x00128778
        charge(ctx, 2);
        lbu(v0, s3, 56);
        s4 = addu(s4, v0);
    }
    // 0x00128780
    charge(ctx, 3);
    v0 = sltiu(s4, 10);
    if (v0 == 0) {
        // 0x0012878c
        charge(ctx, 25);
        a0 = 2;
        jal(ctx, 0x128790u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
        v1 = 10;
        divu(s4, v1);
        mflo(v1);
        a2 = addiu(v1, 11);
        v1 = 0x428A0000;  // 69.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        v1 = 0x43030000;  // 131.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0x7C);
        add_s(f1, f1, f0);
        v1 = 0x41C80000;  // 25.0f
        mtc1(v1, f0);
        sub_s(f13, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s0;
        a1 = v0;
        mov_s(f14, f22);
        jal(ctx, 0x1287E8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x001287f0
    charge(ctx, 34);
    lwc1(f1, sp, 0x7C);
    v0 = 0x43030000;  // 131.0f
    mtc1(v0, f0);
    add_s(f21, f0, f1);
    v0 = 0x42AA0000;  // 85.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x78);
    add_s(f20, f1, f0);
    a0 = 2;
    jal(ctx, 0x128818u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
    v1 = 10;
    divu(s4, v1);
    mfhi(v1);
    a2 = addiu(v1, 11);
    v1 = 0x41C80000;  // 25.0f
    mtc1(v1, f0);
    sub_s(f13, f21, f0);
    a3 = s1 & 0xFF;
    a0 = s0;
    a1 = v0;
    mov_s(f12, f20);
    mov_s(f14, f22);
    jal(ctx, 0x128854u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = s2;
    a1 = 1;
    jal(ctx, 0x128864u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
    s4 = v0 & 0xFF;
    if (s3 != 0) {
        // 0x00128878
        charge(ctx, 2);
        lbu(v0, s3, 57);
        s4 = addu(s4, v0);
    }
    // 0x00128880
    charge(ctx, 3);
    v0 = sltiu(s4, 10);
    if (v0 == 0) {
        // 0x0012888c
        charge(ctx, 25);
        a0 = 2;
        jal(ctx, 0x128890u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
        v1 = 10;
        divu(s4, v1);
        mflo(v1);
        a2 = addiu(v1, 11);
        v1 = 0x428A0000;  // 69.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        v1 = 0x41980000;  // 19.0f
        mtc1(v1, f0);
        add_s(f1, f0, f21);
        v1 = 0x41C80000;  // 25.0f
        mtc1(v1, f0);
        sub_s(f13, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s0;
        a1 = v0;
        mov_s(f14, f22);
        jal(ctx, 0x1288E8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x001288f0
    charge(ctx, 29);
    a0 = 2;
    jal(ctx, 0x1288F4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
    v1 = 10;
    divu(s4, v1);
    mfhi(v1);
    a2 = addiu(v1, 11);
    v1 = 0x41980000;  // 19.0f
    mtc1(v1, f0);
    add_s(f1, f0, f21);
    v1 = 0x41C80000;  // 25.0f
    mtc1(v1, f0);
    sub_s(f13, f1, f0);
    a3 = s1 & 0xFF;
    a0 = s0;
    a1 = v0;
    mov_s(f12, f20);
    mov_s(f14, f22);
    jal(ctx, 0x128940u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = s2;
    a1 = 2;
    jal(ctx, 0x128950u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
    s4 = v0 & 0xFF;
    if (s3 != 0) {
        // 0x00128964
        charge(ctx, 2);
        lbu(v0, s3, 58);
        s4 = addu(s4, v0);
    }
    // 0x0012896c
    charge(ctx, 3);
    v0 = sltiu(s4, 10);
    if (v0 == 0) {
        // 0x00128978
        charge(ctx, 25);
        a0 = 2;
        jal(ctx, 0x12897Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
        v1 = 10;
        divu(s4, v1);
        mflo(v1);
        a2 = addiu(v1, 11);
        v1 = 0x428A0000;  // 69.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        v1 = 0x42180000;  // 38.0f
        mtc1(v1, f0);
        add_s(f1, f0, f21);
        v1 = 0x41C80000;  // 25.0f
        mtc1(v1, f0);
        sub_s(f13, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s0;
        a1 = v0;
        mov_s(f14, f22);
        jal(ctx, 0x1289D4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x001289dc
    charge(ctx, 29);
    a0 = 2;
    jal(ctx, 0x1289E0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
    v1 = 10;
    divu(s4, v1);
    mfhi(v1);
    a2 = addiu(v1, 11);
    v1 = 0x42180000;  // 38.0f
    mtc1(v1, f0);
    add_s(f1, f0, f21);
    v1 = 0x41C80000;  // 25.0f
    mtc1(v1, f0);
    sub_s(f13, f1, f0);
    a3 = s1 & 0xFF;
    a0 = s0;
    a1 = v0;
    mov_s(f12, f20);
    mov_s(f14, f22);
    jal(ctx, 0x128A2Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = s2;
    a1 = 3;
    jal(ctx, 0x128A3Cu, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
    s4 = v0 & 0xFF;
    if (s3 != 0) {
        // 0x00128a50
        charge(ctx, 2);
        lbu(v0, s3, 59);
        s4 = addu(s4, v0);
    }
    // 0x00128a58
    charge(ctx, 3);
    v0 = sltiu(s4, 10);
    if (v0 == 0) {
        // 0x00128a64
        charge(ctx, 25);
        a0 = 2;
        jal(ctx, 0x128A68u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
        v1 = 10;
        divu(s4, v1);
        mflo(v1);
        a2 = addiu(v1, 11);
        v1 = 0x428A0000;  // 69.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        v1 = 0x42640000;  // 57.0f
        mtc1(v1, f0);
        add_s(f1, f0, f21);
        v1 = 0x41C80000;  // 25.0f
        mtc1(v1, f0);
        sub_s(f13, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s0;
        a1 = v0;
        mov_s(f14, f22);
        jal(ctx, 0x128AC0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x00128ac8
    charge(ctx, 29);
    a0 = 2;
    jal(ctx, 0x128ACCu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
    v1 = 10;
    divu(s4, v1);
    mfhi(v1);
    a2 = addiu(v1, 11);
    v1 = 0x42640000;  // 57.0f
    mtc1(v1, f0);
    add_s(f1, f0, f21);
    v1 = 0x41C80000;  // 25.0f
    mtc1(v1, f0);
    sub_s(f13, f1, f0);
    a3 = s1 & 0xFF;
    a0 = s0;
    a1 = v0;
    mov_s(f12, f20);
    mov_s(f14, f22);
    jal(ctx, 0x128B18u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = s2;
    a1 = 4;
    jal(ctx, 0x128B28u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
    s2 = v0 & 0xFF;
    if (s3 != 0) {
        // 0x00128b3c
        charge(ctx, 2);
        lbu(v0, s3, 60);
        s2 = addu(s2, v0);
    }
    // 0x00128b44
    charge(ctx, 3);
    v0 = sltiu(s2, 10);
    if (v0 == 0) {
        // 0x00128b50
        charge(ctx, 25);
        a0 = 2;
        jal(ctx, 0x128B54u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
        v1 = 10;
        divu(s2, v1);
        mflo(v1);
        a2 = addiu(v1, 11);
        v1 = 0x428A0000;  // 69.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        v1 = 0x42980000;  // 76.0f
        mtc1(v1, f0);
        add_s(f1, f0, f21);
        v1 = 0x41C80000;  // 25.0f
        mtc1(v1, f0);
        sub_s(f13, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s0;
        a1 = v0;
        mov_s(f14, f22);
        jal(ctx, 0x128BACu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x00128bb4
    charge(ctx, 34);
    a0 = 2;
    jal(ctx, 0x128BB8u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
    v1 = 10;
    divu(s2, v1);
    mfhi(v1);
    a2 = addiu(v1, 11);
    v1 = 0x42980000;  // 76.0f
    mtc1(v1, f0);
    add_s(f1, f0, f21);
    v1 = 0x41C80000;  // 25.0f
    mtc1(v1, f0);
    sub_s(f13, f1, f0);
    a3 = s1 & 0xFF;
    a0 = s0;
    a1 = v0;
    mov_s(f12, f20);
    mov_s(f14, f22);
    jal(ctx, 0x128C04u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00128C40 sub_128C40 -- 1308 bytes; frame 0x80: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_StatusDrawPersonaBaseStats] (xy, bonus, persona, alpha): as sub_128720 with sub_173580 (the stat without
// equipment bonus) -- the facility screens' variant.
void sub_128C40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00128c40
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x78);
    mov_s(f22, f12);
    s3 = a1;
    s2 = a2;
    s1 = a3;
    a0 = s2;
    a1 = 0;
    jal(ctx, 0x128C84u, gen::fn_sub_173580_00173580);  // (persona, stat): the stat without the bonus
    s4 = v0 & 0xFF;
    if (s3 != 0) {
        // 0x00128c98
        charge(ctx, 2);
        lbu(v0, s3, 56);
        s4 = addu(s4, v0);
    }
    // 0x00128ca0
    charge(ctx, 3);
    v0 = sltiu(s4, 10);
    if (v0 == 0) {
        // 0x00128cac
        charge(ctx, 25);
        a0 = 2;
        jal(ctx, 0x128CB0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
        v1 = 10;
        divu(s4, v1);
        mflo(v1);
        a2 = addiu(v1, 11);
        v1 = 0x428A0000;  // 69.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        v1 = 0x43030000;  // 131.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0x7C);
        add_s(f1, f1, f0);
        v1 = 0x41C80000;  // 25.0f
        mtc1(v1, f0);
        sub_s(f13, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s0;
        a1 = v0;
        mov_s(f14, f22);
        jal(ctx, 0x128D08u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x00128d10
    charge(ctx, 34);
    lwc1(f1, sp, 0x7C);
    v0 = 0x43030000;  // 131.0f
    mtc1(v0, f0);
    add_s(f21, f0, f1);
    v0 = 0x42AA0000;  // 85.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x78);
    add_s(f20, f1, f0);
    a0 = 2;
    jal(ctx, 0x128D38u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
    v1 = 10;
    divu(s4, v1);
    mfhi(v1);
    a2 = addiu(v1, 11);
    v1 = 0x41C80000;  // 25.0f
    mtc1(v1, f0);
    sub_s(f13, f21, f0);
    a3 = s1 & 0xFF;
    a0 = s0;
    a1 = v0;
    mov_s(f12, f20);
    mov_s(f14, f22);
    jal(ctx, 0x128D74u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = s2;
    a1 = 1;
    jal(ctx, 0x128D84u, gen::fn_sub_173580_00173580);  // (persona, stat): the stat without the bonus
    s4 = v0 & 0xFF;
    if (s3 != 0) {
        // 0x00128d98
        charge(ctx, 2);
        lbu(v0, s3, 57);
        s4 = addu(s4, v0);
    }
    // 0x00128da0
    charge(ctx, 3);
    v0 = sltiu(s4, 10);
    if (v0 == 0) {
        // 0x00128dac
        charge(ctx, 25);
        a0 = 2;
        jal(ctx, 0x128DB0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
        v1 = 10;
        divu(s4, v1);
        mflo(v1);
        a2 = addiu(v1, 11);
        v1 = 0x428A0000;  // 69.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        v1 = 0x41980000;  // 19.0f
        mtc1(v1, f0);
        add_s(f1, f0, f21);
        v1 = 0x41C80000;  // 25.0f
        mtc1(v1, f0);
        sub_s(f13, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s0;
        a1 = v0;
        mov_s(f14, f22);
        jal(ctx, 0x128E08u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x00128e10
    charge(ctx, 29);
    a0 = 2;
    jal(ctx, 0x128E14u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
    v1 = 10;
    divu(s4, v1);
    mfhi(v1);
    a2 = addiu(v1, 11);
    v1 = 0x41980000;  // 19.0f
    mtc1(v1, f0);
    add_s(f1, f0, f21);
    v1 = 0x41C80000;  // 25.0f
    mtc1(v1, f0);
    sub_s(f13, f1, f0);
    a3 = s1 & 0xFF;
    a0 = s0;
    a1 = v0;
    mov_s(f12, f20);
    mov_s(f14, f22);
    jal(ctx, 0x128E60u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = s2;
    a1 = 2;
    jal(ctx, 0x128E70u, gen::fn_sub_173580_00173580);  // (persona, stat): the stat without the bonus
    s4 = v0 & 0xFF;
    if (s3 != 0) {
        // 0x00128e84
        charge(ctx, 2);
        lbu(v0, s3, 58);
        s4 = addu(s4, v0);
    }
    // 0x00128e8c
    charge(ctx, 3);
    v0 = sltiu(s4, 10);
    if (v0 == 0) {
        // 0x00128e98
        charge(ctx, 25);
        a0 = 2;
        jal(ctx, 0x128E9Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
        v1 = 10;
        divu(s4, v1);
        mflo(v1);
        a2 = addiu(v1, 11);
        v1 = 0x428A0000;  // 69.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        v1 = 0x42180000;  // 38.0f
        mtc1(v1, f0);
        add_s(f1, f0, f21);
        v1 = 0x41C80000;  // 25.0f
        mtc1(v1, f0);
        sub_s(f13, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s0;
        a1 = v0;
        mov_s(f14, f22);
        jal(ctx, 0x128EF4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x00128efc
    charge(ctx, 29);
    a0 = 2;
    jal(ctx, 0x128F00u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
    v1 = 10;
    divu(s4, v1);
    mfhi(v1);
    a2 = addiu(v1, 11);
    v1 = 0x42180000;  // 38.0f
    mtc1(v1, f0);
    add_s(f1, f0, f21);
    v1 = 0x41C80000;  // 25.0f
    mtc1(v1, f0);
    sub_s(f13, f1, f0);
    a3 = s1 & 0xFF;
    a0 = s0;
    a1 = v0;
    mov_s(f12, f20);
    mov_s(f14, f22);
    jal(ctx, 0x128F4Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = s2;
    a1 = 3;
    jal(ctx, 0x128F5Cu, gen::fn_sub_173580_00173580);  // (persona, stat): the stat without the bonus
    s4 = v0 & 0xFF;
    if (s3 != 0) {
        // 0x00128f70
        charge(ctx, 2);
        lbu(v0, s3, 59);
        s4 = addu(s4, v0);
    }
    // 0x00128f78
    charge(ctx, 3);
    v0 = sltiu(s4, 10);
    if (v0 == 0) {
        // 0x00128f84
        charge(ctx, 25);
        a0 = 2;
        jal(ctx, 0x128F88u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
        v1 = 10;
        divu(s4, v1);
        mflo(v1);
        a2 = addiu(v1, 11);
        v1 = 0x428A0000;  // 69.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        v1 = 0x42640000;  // 57.0f
        mtc1(v1, f0);
        add_s(f1, f0, f21);
        v1 = 0x41C80000;  // 25.0f
        mtc1(v1, f0);
        sub_s(f13, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s0;
        a1 = v0;
        mov_s(f14, f22);
        jal(ctx, 0x128FE0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x00128fe8
    charge(ctx, 29);
    a0 = 2;
    jal(ctx, 0x128FECu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
    v1 = 10;
    divu(s4, v1);
    mfhi(v1);
    a2 = addiu(v1, 11);
    v1 = 0x42640000;  // 57.0f
    mtc1(v1, f0);
    add_s(f1, f0, f21);
    v1 = 0x41C80000;  // 25.0f
    mtc1(v1, f0);
    sub_s(f13, f1, f0);
    a3 = s1 & 0xFF;
    a0 = s0;
    a1 = v0;
    mov_s(f12, f20);
    mov_s(f14, f22);
    jal(ctx, 0x129038u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = s2;
    a1 = 4;
    jal(ctx, 0x129048u, gen::fn_sub_173580_00173580);  // (persona, stat): the stat without the bonus
    s2 = v0 & 0xFF;
    if (s3 != 0) {
        // 0x0012905c
        charge(ctx, 2);
        lbu(v0, s3, 60);
        s2 = addu(s2, v0);
    }
    // 0x00129064
    charge(ctx, 3);
    v0 = sltiu(s2, 10);
    if (v0 == 0) {
        // 0x00129070
        charge(ctx, 25);
        a0 = 2;
        jal(ctx, 0x129074u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
        v1 = 10;
        divu(s2, v1);
        mflo(v1);
        a2 = addiu(v1, 11);
        v1 = 0x428A0000;  // 69.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        v1 = 0x42980000;  // 76.0f
        mtc1(v1, f0);
        add_s(f1, f0, f21);
        v1 = 0x41C80000;  // 25.0f
        mtc1(v1, f0);
        sub_s(f13, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s0;
        a1 = v0;
        mov_s(f14, f22);
        jal(ctx, 0x1290CCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x001290d4
    charge(ctx, 34);
    a0 = 2;
    jal(ctx, 0x1290D8u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
    v1 = 10;
    divu(s2, v1);
    mfhi(v1);
    a2 = addiu(v1, 11);
    v1 = 0x42980000;  // 76.0f
    mtc1(v1, f0);
    add_s(f1, f0, f21);
    v1 = 0x41C80000;  // 25.0f
    mtc1(v1, f0);
    sub_s(f13, f1, f0);
    a3 = s1 & 0xFF;
    a0 = s0;
    a1 = v0;
    mov_s(f12, f20);
    mov_s(f14, f22);
    jal(ctx, 0x129124u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x001293B0 sub_1293B0 -- 1912 bytes; frame 0x160: ra sp+0xC0, fp sp+0xB0 (sq), s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_StatusDrawSkills] (xy, next, persona, alpha): the persona's eight skill slots in 2 x 4 cells (sprite 18 of
// camp file 8, the skill name through sprintf + sub_3B32D0, the element icon), the new skills of `next` (+62) marked;
// then the next-skill line (sub_1FC230 / sub_1FC3C0 / sub_1FB1F0).
void sub_1293B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29};
    // 0x001293b0
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x160);
    sd(ra, sp, 0xC0);
    sq(fp, sp, 0xB0);
    sq(s7, sp, 0xA0);
    sq(s6, sp, 0x90);
    sq(s5, sp, 0x80);
    sq(s4, sp, 0x70);
    sq(s3, sp, 0x60);
    sq(s2, sp, 0x50);
    sq(s1, sp, 0x40);
    sq(s0, sp, 0x30);
    swc1(f29, sp, 0x24);
    swc1(f28, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x118);
    mov_s(f29, f12);
    s4 = a2;
    s3 = a3;
    sw(zero, sp, 0x15C);
    s0 = 0;
    v0 = 255;
    v1 = subu(v0, s3);
    v0 = addiu(s4, 12);
    sq(v0, sp, 0xF0);
    if (a1 != 0) {
        // 0x00129434
        charge(ctx, 1);
        s0 = addiu(a1, 62);
    }
    // 0x00129438
    charge(ctx, 36);
    s2 = 0;
    lwc1(f20, sp, 0x11C);
    v0 = 0x439E0000;  // 316.0f
    mtc1(v0, f0);
    add_s(f28, f0, f20);
    v0 = 0x42080000;  // 34.0f
    mtc1(v0, f0);
    lwc1(f1, sp, 0x118);
    add_s(f27, f0, f1);
    v0 = lui(0x95B9);
    v0 = v0 | 0xFF00;
    s7 = v1 | v0;
    v0 = 319;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    add_s(f26, f0, f20);
    v0 = 0x42300000;  // 44.0f
    mtc1(v0, f0);
    add_s(f25, f0, f1);
    v0 = 0x43A60000;  // 332.0f
    mtc1(v0, f0);
    add_s(f24, f0, f20);
    v0 = 0x421C0000;  // 39.0f
    mtc1(v0, f0);
    add_s(f23, f0, f1);
    v0 = 0x77FF0000;
    v0 = v0 | 0xCF00;
    v0 = v1 | v0;
    sw(v0, sp, 0x100);
    for (;;) {
        // 0x001296e4
        charge(ctx, 3);
        v0 = slti(s2, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001294c8
        charge(ctx, 18);
        s1 = 0;
        v0 = sll(s2, 1);
        v0 = addu(v0, s2);
        v0 = sll(v0, 5);
        v0 = subu(v0, s2);
        v0 = sll(v0, 1);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        add_s(f22, f27, f1);
        v0 = sll(s2, 2);
        sq(v0, sp, 0xE0);
        add_s(f0, f25, f1);
        cvt_w_s(f0, f0);
        mfc1(fp, f0);
        add_s(f21, f23, f1);
        for (;;) {
            // 0x001296d4
            charge(ctx, 3);
            v0 = slti(s1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00129510
            charge(ctx, 25);
            v0 = sll(s1, 1);
            v0 = addu(v0, s1);
            s5 = sll(v0, 3);
            mtc1(s5, f0);
            cvt_s_w(f0, f0);
            add_s(f13, f28, f0);
            a3 = s3 & 0xFF;
            a0 = s6;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
            a2 = 18;
            mov_s(f12, f22);
            mov_s(f14, f29);
            jal(ctx, 0x129548u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lq(v0, sp, 0xE0);
            v0 = addu(s1, v0);
            a0 = sll(v0, 1);
            lq(v0, sp, 0xF0);
            v0 = addu(v0, a0);
            sq(v0, sp, 0xD0);
            lhu(v1, v0, 0);
            if (v1 != 0) {
                // 0x00129574
                charge(ctx, 2);
                if (s0 != 0) {
                    // 0x0012957c
                    charge(ctx, 4);
                    v0 = addu(s0, a0);
                    lhu(v0, v0, 0);
                    if (v0 == 0) {
                        goto L_0012958c;
                    }
                    // 0x00129610
                    charge(ctx, 48);
                    v0 = sll(s1, 1);
                    v0 = addu(v0, s1);
                    s5 = sll(v0, 3);
                    mtc1(s5, f0);
                    cvt_s_w(f0, f0);
                    add_s(f13, f24, f0);
                    a3 = s3 & 0xFF;
                    a0 = s6;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
                    a2 = 25;
                    mov_s(f12, f21);
                    mov_s(f14, f29);
                    jal(ctx, 0x129648u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    lq(v0, sp, 0xD0);
                    lhu(v1, v0, 0);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 1);
                    v1 = addu(v0, v1);
                    lw(v0, gp, g::kSkillTable);  // 0x7CE4EC
                    a2 = addu(v0, v1);
                    a0 = addiu(sp, 0x130);
                    a1 = addiu(gp, -30340);  // "%s"
                    jal(ctx, 0x129678u, gen::fn_sprintf_00523ac8);
                    mtc1(s5, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f26, f0);
                    v0 = 0x40800000;  // 4.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    a0 = fp;
                    mov_s(f12, f29);
                    lw(a2, sp, 0x100);
                    a3 = 6;
                    t0 = 1;
                    t1 = addiu(sp, 0x130);
                    t2 = 16;
                    t3 = 120;
                    jal(ctx, 0x1296C8u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                    goto L_001296d0;
                }
            L_0012958c:
                charge(ctx, 33);
                v1 = v1 & 0xFFFF;
                v0 = sll(v1, 3);
                v0 = addu(v0, v1);
                v0 = sll(v0, 1);
                v1 = addu(v0, v1);
                lw(v0, gp, g::kSkillTable);  // 0x7CE4EC
                a2 = addu(v0, v1);
                a0 = addiu(sp, 0x130);
                a1 = addiu(gp, -30340);  // "%s"
                jal(ctx, 0x1295B0u, gen::fn_sprintf_00523ac8);
                mtc1(s5, f0);
                cvt_s_w(f0, f0);
                add_s(f1, f26, f0);
                v0 = 0x40800000;  // 4.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                a0 = fp;
                mov_s(f12, f29);
                a2 = s7;
                a3 = 6;
                t0 = 1;
                t1 = addiu(sp, 0x130);
                t2 = 16;
                t3 = 120;
                jal(ctx, 0x129600u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
            }
        L_001296d0:
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
        // 0x001296e0
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x001296f0
    charge(ctx, 5);
    a0 = s4;
    jal(ctx, 0x1296F4u, gen::fn_sub_1FC230_001fc230);
    if (v0 != 0) {
        // 0x00129704
        charge(ctx, 42);
        lwc1(f1, sp, 0x11C);
        v0 = 0x43A30000;  // 326.0f
        mtc1(v0, f0);
        add_s(f21, f0, f1);
        v0 = 411;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0x118);
        add_s(f12, f1, f0);
        a3 = s3 & 0xFF;
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
        a2 = 21;
        mov_s(f13, f21);
        mov_s(f14, f29);
        jal(ctx, 0x12974Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 557;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0x118);
        add_s(f12, f1, f0);
        a3 = s3 & 0xFF;
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
        a2 = 23;
        mov_s(f13, f21);
        mov_s(f14, f29);
        jal(ctx, 0x129788u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        a0 = s4;
        jal(ctx, 0x129794u, gen::fn_sub_1FC3C0_001fc3c0);
        s0 = v0;
        v0 = slti(s0, 10);
        if (v0 != 0) {
            // 0x00129868
            charge(ctx, 23);
            a0 = 2;
            jal(ctx, 0x12986Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            v1 = 10;
            div(s0, v1);
            mfhi(v1);
            a2 = addiu(v1, 11);
            v1 = 534;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, sp, 0x118);
            add_s(f12, f1, f0);
            v1 = 0x43A40000;  // 328.0f
            mtc1(v1, f0);
            add_s(f13, f0, f20);
            a3 = s3 & 0xFF;
            a0 = s6;
            a1 = v0;
            mov_s(f14, f29);
            jal(ctx, 0x1298BCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        } else {
            // 0x001297ac
            charge(ctx, 47);
            lwc1(f1, sp, 0x11C);
            v0 = 0x43A40000;  // 328.0f
            mtc1(v0, f0);
            add_s(f21, f0, f1);
            a0 = 2;
            jal(ctx, 0x1297C4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            v1 = 10;
            div(s0, v1);
            mflo(v1);
            a2 = addiu(v1, 11);
            v1 = 526;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, sp, 0x118);
            add_s(f12, f1, f0);
            a3 = s3 & 0xFF;
            a0 = s6;
            a1 = v0;
            mov_s(f13, f21);
            mov_s(f14, f29);
            jal(ctx, 0x129808u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            a0 = 2;
            jal(ctx, 0x129814u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            v1 = 10;
            div(s0, v1);
            mfhi(v1);
            a2 = addiu(v1, 11);
            v1 = 541;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, sp, 0x118);
            add_s(f12, f1, f0);
            a3 = s3 & 0xFF;
            a0 = s6;
            a1 = v0;
            mov_s(f13, f21);
            mov_s(f14, f29);
            jal(ctx, 0x129858u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        }
    }
    // 0x001298c4
    charge(ctx, 34);
    a0 = s4;
    a1 = addiu(sp, 0x120);
    a2 = addiu(sp, 0x15C);
    jal(ctx, 0x1298D0u, gen::fn_sub_1FB1F0_001fb1f0);
    s1 = 0;
    lwc1(f1, sp, 0x11C);
    v1 = 0x43AA0000;  // 340.0f
    mtc1(v1, f0);
    add_s(f21, f0, f1);
    v1 = 0x43CF0000;  // 414.0f
    mtc1(v1, f0);
    lwc1(f2, sp, 0x118);
    add_s(f22, f0, f2);
    v1 = 343;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    add_s(f1, f0, f1);
    v1 = 0x40800000;  // 4.0f
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(s2, f0);
    v1 = 0x43D40000;  // 424.0f
    mtc1(v1, f0);
    add_s(f0, f0, f2);
    cvt_w_s(f0, f0);
    mfc1(s4, f0);
    for (;;) {
        // 0x001299f0
        charge(ctx, 4);
        lw(a0, sp, 0x15C);
        v1 = slt(s1, a0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0012994c
        charge(ctx, 6);
        v1 = sll(s1, 1);
        v1 = addu(v1, sp);
        s0 = addiu(v1, 288);
        lhu(v1, s0, 0);
        if (v1 != 0) {
            // 0x00129964
            charge(ctx, 2);
            if (s1 == 0) {
                // 0x0012996c
                charge(ctx, 32);
                a3 = s3 & 0xFF;
                a0 = s6;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
                a2 = 19;
                mov_s(f12, f22);
                mov_s(f13, f21);
                mov_s(f14, f29);
                jal(ctx, 0x12998Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lhu(v1, s0, 0);
                v0 = sll(v1, 3);
                v0 = addu(v0, v1);
                v0 = sll(v0, 1);
                v1 = addu(v0, v1);
                lw(v0, gp, g::kSkillTable);  // 0x7CE4EC
                a2 = addu(v0, v1);
                a0 = addiu(sp, 0x130);
                a1 = addiu(gp, -30340);  // "%s"
                jal(ctx, 0x1299B8u, gen::fn_sprintf_00523ac8);
                a0 = s4;
                a1 = s2;
                mov_s(f12, f29);
                a2 = s7;
                a3 = 6;
                t0 = 1;
                t1 = addiu(sp, 0x130);
                t2 = 16;
                t3 = 120;
                jal(ctx, 0x1299E4u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
            }
        }
        // 0x001299ec
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00129a00
    charge(ctx, 3);
    v1 = slti(a0, 7);
    if (v1 == 0) {
        // 0x00129a0c
        charge(ctx, 2);
        v1 = 7;
        sw(v1, sp, 0x15C);
    }
    // 0x00129a14
    charge(ctx, 7);
    s0 = 0;
    v1 = 0x43B70000;  // 366.0f
    mtc1(v1, f0);
    add_s(f20, f0, f20);
    for (;;) {
        // 0x00129ab8
        charge(ctx, 5);
        lw(v1, sp, 0x15C);
        v1 = addiu(v1, -1);
        v1 = slt(s0, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00129a30
        charge(ctx, 3);
        v1 = sra(s0, 1);
        if (i64(s0) < 0) {
            // 0x00129a3c
            charge(ctx, 2);
            v0 = addiu(s0, 1);
            v1 = sra(v0, 1);
        }
        // 0x00129a44
        charge(ctx, 10);
        v0 = sll(v1, 5);
        v0 = subu(v0, v1);
        v0 = sll(v0, 1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f12, f22, f0);
        v1 = s0 & 0x1;
        if (i64(s0) < 0) {
            // 0x00129a6c
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x00129a74
                charge(ctx, 1);
                v1 = addiu(v1, -2);
            }
        }
        // 0x00129a78
        charge(ctx, 16);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f13, f20, f0);
        a3 = s3 & 0xFF;
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
        a2 = 20;
        mov_s(f14, f29);
        jal(ctx, 0x129AACu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        s0 = addiu(s0, 1);
    }
    // 0x00129acc
    charge(ctx, 23);
    ld(ra, sp, 0xC0);
    lq(fp, sp, 0xB0);
    lq(s7, sp, 0xA0);
    lq(s6, sp, 0x90);
    lq(s5, sp, 0x80);
    lq(s4, sp, 0x70);
    lq(s3, sp, 0x60);
    lq(s2, sp, 0x50);
    lq(s1, sp, 0x40);
    lq(s0, sp, 0x30);
    lwc1(f29, sp, 0x24);
    lwc1(f28, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x160);
}

// 0x00129B30 sub_129B30 -- 2600 bytes; frame 0x1E0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_StatusDrawPersonaPanelIn] (xy, persona, frame): the persona status panel's 20-frame reveal: the frame sliding
// in from +300 over 5 frames, the nine stat labels (sub_1281E0) appearing one per frame, resistances (sub_128480),
// stats (sub_128720), the five bars (handles of sprite 24 of camp file 10, scaled by the stat), the skills (sub_1293B0)
// and the next-exp text (sprintf of sub_173340 - sub_173330 through sub_40EB50), each faded by its frame.
void sub_129B30(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x00129b30
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1E0);
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
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0xB8);
    mov_s(f22, f12);
    s4 = a1;
    s3 = a2;
    if (i64(s3) >= 0) {
        // 0x00129b84
        charge(ctx, 3);
        at = slti(s3, 5);
        if (at == 0) {
            // 0x00129bec
            charge(ctx, 3);
            lwc1(f0, sp, 0xB8);
            swc1(f0, sp, 0x1D8);
            s1 = 0;
        } else {
            // 0x00129b90
            charge(ctx, 23);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f2);
            mtc1(s3, f0);
            cvt_s_w(f0, f0);
            mul_s(f1, f2, f0);
            v0 = 0x40A00000;  // 5.0f
            mtc1(v0, f0);
            div_s(f0, f1, f0);
            sub_s(f1, f2, f0);
            lwc1(f0, sp, 0xB8);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x1D8);
            v0 = sll(s3, 8);
            v1 = subu(v0, s3);
            v0 = 5;
            div(v1, v0);
            mflo(v1);
            v0 = 255;
            s1 = subu(v0, v1);
        }
        // 0x00129bf8
        charge(ctx, 2);
        lwc1(f0, sp, 0xBC);
        swc1(f0, sp, 0x1DC);
    }
    // 0x00129c00
    charge(ctx, 3);
    v0 = slti(s3, 15);
    if (v0 == 0) {
        // 0x00129c0c
        charge(ctx, 4);
        v1 = addiu(s3, -15);
        at = slti(v1, 5);
        if (at == 0) {
            // 0x00129c40
            charge(ctx, 1);
            s1 = 0;
        } else {
            // 0x00129c1c
            charge(ctx, 9);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 5;
            div(v1, v0);
            mflo(v1);
            v0 = 255;
            s1 = subu(v0, v1);
        }
    }
    // 0x00129c44
    charge(ctx, 4);
    s0 = 0;
    lwc1(f21, sp, 0xBC);
    for (;;) {
        // 0x00129cfc
        charge(ctx, 3);
        v0 = sltiu(s0, 9);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00129c54
        charge(ctx, 3);
        v0 = sltu(s3, s0);
        if (v0 == 0) {
            // 0x00129c60
            charge(ctx, 4);
            a0 = subu(s3, s0);
            at = slti(a0, 10);
            if (at == 0) {
                // 0x00129cd8
                charge(ctx, 1);
                s1 = 0;
            } else {
                // 0x00129c70
                charge(ctx, 26);
                v0 = sll(a0, 5);
                v0 = subu(v0, a0);
                v0 = sll(v0, 2);
                v0 = addu(v0, a0);
                v0 = sll(v0, 2);
                v1 = 10;
                div(v0, v1);
                mflo(v0);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x43FA0000;  // 500.0f
                mtc1(v0, f0);
                sub_s(f1, f0, f1);
                lwc1(f0, sp, 0xB8);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x1D8);
                v0 = sll(a0, 8);
                v0 = subu(v0, a0);
                div1(v0, v1);
                mflo1(v1);
                v0 = 255;
                s1 = subu(v0, v1);
            }
            // 0x00129cdc
            charge(ctx, 7);
            swc1(f21, sp, 0x1DC);
            ld(a0, sp, 0x1D8);
            mov_s(f12, f22);
            a1 = s0;
            a2 = s1;
            jal(ctx, 0x129CF0u, gen::fn_sub_1281E0_001281e0);  // a stat label
        }
        // 0x00129cf8
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00129d08
    charge(ctx, 3);
    v0 = slti(s3, 3);
    if (v0 == 0) {
        // 0x00129d14
        charge(ctx, 4);
        a1 = addiu(s3, -3);
        at = slti(a1, 5);
        if (at == 0) {
            // 0x00129d8c
            charge(ctx, 3);
            s1 = 0;
            lwc1(f0, sp, 0xB8);
            swc1(f0, sp, 0x1D8);
        } else {
            // 0x00129d24
            charge(ctx, 26);
            v0 = sll(a1, 8);
            v0 = subu(v0, a1);
            a0 = 5;
            div(v0, a0);
            mflo(v1);
            v0 = 255;
            s1 = subu(v0, v1);
            v0 = sll(a1, 2);
            v1 = addu(v0, a1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v0 = sll(v0, 2);
            div1(v0, a0);
            mflo1(v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f0);
            sub_s(f1, f0, f1);
            lwc1(f0, sp, 0xB8);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x1D8);
        }
        // 0x00129d98
        charge(ctx, 80);
        swc1(f21, sp, 0x1DC);
        v0 = 0x42080000;  // 34.0f
        mtc1(v0, f12);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f13, f0);
        a3 = s1 & 0xFF;
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s2;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
        a2 = 0;
        jal(ctx, 0x129DD0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x42480000;  // 50.0f
        mtc1(v0, f12);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f13, f0);
        a3 = s1 & 0xFF;
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s2;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
        a2 = 10;
        jal(ctx, 0x129E0Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x43540000;  // 212.0f
        mtc1(v0, f12);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f13, f0);
        a3 = s1 & 0xFF;
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s2;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
        a2 = 11;
        jal(ctx, 0x129E48u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 561;
        mtc1(v0, f0);
        cvt_s_w(f12, f0);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f13, f0);
        a3 = s1 & 0xFF;
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s2;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
        a2 = 1;
        jal(ctx, 0x129E8Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 361;
        mtc1(v0, f0);
        cvt_s_w(f12, f0);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f13, f0);
        a3 = s1 & 0xFF;
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s2;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
        a2 = 5;
        jal(ctx, 0x129ED0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x00129ed8
    charge(ctx, 3);
    v0 = slti(s3, 3);
    if (v0 == 0) {
        // 0x00129ee4
        charge(ctx, 4);
        v1 = addiu(s3, -3);
        at = slti(v1, 5);
        if (at == 0) {
            // 0x00129f18
            charge(ctx, 1);
            s1 = 0;
        } else {
            // 0x00129ef4
            charge(ctx, 9);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 5;
            div(v1, v0);
            mflo(v1);
            v0 = 255;
            s1 = subu(v0, v1);
        }
        // 0x00129f1c
        charge(ctx, 6);
        ld(a0, sp, 0xB8);
        mov_s(f12, f22);
        a1 = s4;
        a2 = s1;
        jal(ctx, 0x129F2Cu, gen::fn_sub_128480_00128480);  // the resistances
    }
    // 0x00129f34
    charge(ctx, 3);
    v0 = slti(s3, 3);
    if (v0 == 0) {
        // 0x00129f40
        charge(ctx, 4);
        a1 = addiu(s3, -3);
        at = slti(a1, 5);
        if (at == 0) {
            // 0x00129fb0
            charge(ctx, 3);
            s1 = 0;
            lwc1(f0, sp, 0xB8);
            swc1(f0, sp, 0x1D8);
        } else {
            // 0x00129f50
            charge(ctx, 24);
            v0 = sll(a1, 8);
            v0 = subu(v0, a1);
            a0 = 5;
            div(v0, a0);
            mflo(v1);
            v0 = 255;
            s1 = subu(v0, v1);
            v0 = sll(a1, 4);
            v1 = subu(v0, a1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v0 = sll(v0, 2);
            div1(v0, a0);
            mflo1(v1);
            v0 = 300;
            v0 = subu(v0, v1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, sp, 0xB8);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x1D8);
        }
        // 0x00129fbc
        charge(ctx, 42);
        swc1(f21, sp, 0x1DC);
        ld(v0, sp, 0x1D8);
        sd(v0, sp, 0x1D0);
        lwc1(f23, sp, 0x1D4);
        v0 = 0x41F00000;  // 30.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x1D0);
        add_s(f20, f1, f0);
        v0 = 0x42FA0000;  // 125.0f
        mtc1(v0, f0);
        add_s(f1, f0, f23);
        v0 = 0x41C80000;  // 25.0f
        mtc1(v0, f0);
        sub_s(f13, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s2;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
        a2 = 18;
        mov_s(f12, f20);
        mov_s(f14, f22);
        jal(ctx, 0x12A018u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x43380000;  // 184.0f
        mtc1(v0, f0);
        add_s(f1, f0, f23);
        v0 = 0x41C80000;  // 25.0f
        mtc1(v0, f0);
        sub_s(f13, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s2;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
        a2 = 19;
        mov_s(f12, f20);
        mov_s(f14, f22);
        jal(ctx, 0x12A05Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x0012a064
    charge(ctx, 3);
    v0 = slti(s3, 5);
    if (v0 == 0) {
        // 0x0012a070
        charge(ctx, 4);
        v1 = addiu(s3, -5);
        at = slti(v1, 3);
        if (at == 0) {
            // 0x0012a0a4
            charge(ctx, 1);
            s1 = 0;
        } else {
            // 0x0012a080
            charge(ctx, 9);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 3;
            div(v1, v0);
            mflo(v1);
            v0 = 255;
            s1 = subu(v0, v1);
        }
        // 0x0012a0a8
        charge(ctx, 7);
        ld(a0, sp, 0xB8);
        mov_s(f12, f22);
        a1 = 0;
        a2 = s4;
        a3 = s1;
        jal(ctx, 0x12A0BCu, gen::fn_sub_128720_00128720);
    }
    // 0x0012a0c4
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x0012a384
        charge(ctx, 3);
        v0 = sltiu(s0, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0012a0d0
        charge(ctx, 3);
        v0 = slti(s3, 3);
        if (v0 == 0) {
            // 0x0012a0dc
            charge(ctx, 4);
            s5 = addiu(s3, -3);
            a1 = 4;
            if (s0 == a1) {
                // 0x0012a184
                charge(ctx, 4);
                a0 = s4;
                jal(ctx, 0x12A188u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                s2 = v0 & 0xFF;
            } else {
                // 0x0012a0ec
                charge(ctx, 3);
                a1 = 3;
                if (s0 == a1) {
                    // 0x0012a16c
                    charge(ctx, 6);
                    a0 = s4;
                    jal(ctx, 0x12A170u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                    s2 = v0 & 0xFF;
                } else {
                    // 0x0012a0f8
                    charge(ctx, 3);
                    a1 = 2;
                    if (s0 == a1) {
                        // 0x0012a154
                        charge(ctx, 6);
                        a0 = s4;
                        jal(ctx, 0x12A158u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                        s2 = v0 & 0xFF;
                    } else {
                        // 0x0012a104
                        charge(ctx, 3);
                        a1 = 1;
                        if (s0 == a1) {
                            // 0x0012a13c
                            charge(ctx, 6);
                            a0 = s4;
                            jal(ctx, 0x12A140u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                            s2 = v0 & 0xFF;
                        } else {
                            // 0x0012a110
                            charge(ctx, 2);
                            if (s0 == 0) {
                                // 0x0012a120
                                charge(ctx, 7);
                                a0 = s4;
                                a1 = 0;
                                jal(ctx, 0x12A128u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                                s2 = v0 & 0xFF;
                            } else {
                                // 0x0012a118
                                charge(ctx, 2);
                            }
                        }
                    }
                }
            }
            // 0x0012a194
            charge(ctx, 3);
            at = slti(s5, 5);
            if (at == 0) {
                // 0x0012a214
                charge(ctx, 3);
                s1 = 0;
                lwc1(f0, sp, 0xB8);
                swc1(f0, sp, 0x1D8);
            } else {
                // 0x0012a1a0
                charge(ctx, 29);
                v0 = sll(s5, 8);
                v0 = subu(v0, s5);
                a0 = 5;
                div(v0, a0);
                mflo(v1);
                v0 = 255;
                s1 = subu(v0, v1);
                v0 = sll(s5, 4);
                v1 = subu(v0, s5);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 2);
                div1(v0, a0);
                mflo1(v1);
                v0 = 300;
                v0 = subu(v0, v1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, sp, 0xB8);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x1D8);
                mult(v0, s2, s5);
                divu(v0, a0);
                mflo(s2);
            }
            // 0x0012a220
            charge(ctx, 88);
            swc1(f21, sp, 0x1DC);
            ld(v0, sp, 0x1D8);
            sd(v0, sp, 0x1C8);
            v0 = sll(s0, 3);
            v0 = addu(v0, s0);
            v0 = sll(v0, 1);
            s5 = addu(v0, s0);
            lwc1(f20, sp, 0x1CC);
            v0 = 0x43010000;  // 129.0f
            mtc1(v0, f0);
            add_s(f1, f0, f20);
            mtc1(s5, f0);
            cvt_s_w(f0, f0);
            add_s(f1, f1, f0);
            v0 = 0x41C80000;  // 25.0f
            mtc1(v0, f0);
            sub_s(f23, f1, f0);
            v0 = 0x42D00000;  // 104.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x1C8);
            add_s(f12, f1, f0);
            a3 = s1 & 0xFF;
            a0 = s6;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
            a2 = 20;
            mov_s(f13, f23);
            mov_s(f14, f22);
            jal(ctx, 0x12A29Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 333;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, sp, 0x1C8);
            add_s(f12, f1, f0);
            a3 = s1 & 0xFF;
            a0 = s6;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
            a2 = 21;
            mov_s(f13, f23);
            mov_s(f14, f22);
            jal(ctx, 0x12A2D8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 227;
            mult(v1, s2, v0);
            v0 = 99;
            div(v1, v0);
            mflo(fp);
            a0 = 0;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
            a2 = 24;
            jal(ctx, 0x12A304u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
            s6 = v0;
            swc1(f22, v0, 44);
            v1 = 0x42D80000;  // 108.0f
            mtc1(v1, f1);
            lwc1(f0, sp, 0x1C8);
            add_s(f0, f1, f0);
            swc1(f0, v0, 16);
            v1 = 0x43020000;  // 130.0f
            mtc1(v1, f0);
            add_s(f1, f0, f20);
            mtc1(s5, f0);
            cvt_s_w(f0, f0);
            add_s(f1, f1, f0);
            v1 = 0x41C80000;  // 25.0f
            mtc1(v1, f0);
            sub_s(f0, f1, f0);
            swc1(f0, v0, 20);
            sb(s1, v0, 24);
            sh(fp, v0, 28);
            a0 = s6;
            a1 = 1;
            jal(ctx, 0x12A36Cu, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
            a0 = s6;
            jal(ctx, 0x12A378u, gen::fn_sub_115980_00115980);  // draw and release the handle
        }
        // 0x0012a380
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0012a390
    charge(ctx, 68);
    ld(a0, sp, 0xB8);
    mov_s(f12, f22);
    a1 = 0;
    a2 = s4;
    a3 = s1;
    jal(ctx, 0x12A3A4u, gen::fn_sub_1293B0_001293b0);
    ld(v0, sp, 0xB8);
    sd(v0, sp, 0x1C0);
    v0 = 255;
    s0 = subu(v0, s1);
    lwc1(f1, sp, 0x1C0);
    v0 = 0x41400000;  // 12.0f
    mtc1(v0, f0);
    add_s(f2, f1, f0);
    swc1(f2, sp, 0x1C0);
    lwc1(f1, sp, 0x1C4);
    v0 = 0x42C00000;  // 96.0f
    mtc1(v0, f0);
    add_s(f1, f1, f0);
    swc1(f1, sp, 0x1C4);
    v0 = 0x43360000;  // 182.0f
    mtc1(v0, f0);
    add_s(f21, f0, f1);
    v0 = 0x41A80000;  // 21.0f
    mtc1(v0, f0);
    add_s(f20, f0, f2);
    a3 = s1 & 0xFF;
    a0 = s7;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 17;
    mov_s(f12, f20);
    mov_s(f13, f21);
    mov_s(f14, f22);
    jal(ctx, 0x12A42Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 275;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x1C0);
    add_s(f12, f1, f0);
    a3 = s1 & 0xFF;
    a0 = s7;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 34;
    mov_s(f13, f21);
    mov_s(f14, f22);
    jal(ctx, 0x12A468u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x437E0000;  // 254.0f
    mtc1(v0, f0);
    add_s(f23, f0, f20);
    v0 = 0x40000000;  // 2.0f
    mtc1(v0, f0);
    add_s(f20, f0, f21);
    lbu(v1, s4, 4);
    v0 = 99;
    if (v1 != v0) {
        // 0x0012a4b8
        charge(ctx, 12);
        a0 = s4;
        jal(ctx, 0x12A4BCu, gen::fn_sub_173340_00173340);  // (persona, level): the exp of that level
        s1 = v0;
        a0 = s4;
        jal(ctx, 0x12A4CCu, gen::fn_sub_173330_00173330);  // [datPersonaGetExp]
        a2 = subu(s1, v0);
        a0 = addiu(sp, 0xC0);
        a1 = addiu(gp, -30344);  // "%d"
        jal(ctx, 0x12A4E0u, gen::fn_sprintf_00523ac8);
    } else {
        // 0x0012a4a0
        charge(ctx, 6);
        a0 = addiu(sp, 0xC0);
        a1 = addiu(gp, -30336);  // &0x7CB670
        jal(ctx, 0x12A4A8u, gen::fn_sprintf_00523ac8);
    }
    // 0x0012a4e8
    charge(ctx, 28);
    cvt_w_s(f0, f23);
    mfc1(a0, f0);
    cvt_w_s(f0, f20);
    mfc1(a1, f0);
    a2 = s0 & 0xFF;
    mov_s(f12, f22);
    a3 = 4;
    t0 = addiu(sp, 0xC0);
    t1 = 1;
    jal(ctx, 0x12A50Cu, gen::fn_sub_40EB50_0040eb50);  // text / number at (x, y)
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
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1E0);
}

// 0x0012A560 sub_12A560 -- 1788 bytes; frame 0x1E0: ra sp+0xA0, s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_StatusDrawPersonaPanelOut] (xy, persona, frame): the same panel sliding out (+300 * frame / 5) and fading
// over 5 frames.
void sub_12A560(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26};
    // 0x0012a560
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1E0);
    sd(ra, sp, 0xA0);
    sq(s7, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0xB8);
    mov_s(f25, f12);
    s4 = a1;
    at = slti(a2, 5);
    if (at == 0) {
        // 0x0012a60c
        charge(ctx, 2);
    } else {
        // 0x0012a5bc
        charge(ctx, 20);
        v0 = sll(a2, 4);
        v1 = subu(v0, a2);
        v0 = sll(v1, 2);
        v0 = addu(v1, v0);
        v0 = sll(v0, 2);
        v1 = 5;
        div(v0, v1);
        mflo(v0);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0xB8);
        add_s(f0, f0, f1);
        swc1(f0, sp, 0xB8);
        v0 = sll(a2, 8);
        v0 = subu(v0, a2);
        div1(v0, v1);
        mflo1(s2);
        // 0x0012a614
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x0012a63c
            charge(ctx, 3);
            v0 = sltiu(s0, 9);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0012a620
            charge(ctx, 7);
            ld(a0, sp, 0xB8);
            mov_s(f12, f25);
            a1 = s0;
            a2 = s2;
            jal(ctx, 0x12A630u, gen::fn_sub_1281E0_001281e0);  // a stat label
            s0 = addiu(s0, 1);
        }
        // 0x0012a648
        charge(ctx, 160);
        v0 = 0x42080000;  // 34.0f
        mtc1(v0, f12);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f13, f0);
        a3 = s2 & 0xFF;
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s1;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
        a2 = 0;
        jal(ctx, 0x12A67Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x42480000;  // 50.0f
        mtc1(v0, f12);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f13, f0);
        a3 = s2 & 0xFF;
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s1;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
        a2 = 10;
        jal(ctx, 0x12A6B8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x43540000;  // 212.0f
        mtc1(v0, f12);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f13, f0);
        a3 = s2 & 0xFF;
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s1;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
        a2 = 11;
        jal(ctx, 0x12A6F4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 561;
        mtc1(v0, f0);
        cvt_s_w(f12, f0);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f13, f0);
        a3 = s2 & 0xFF;
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s1;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
        a2 = 1;
        jal(ctx, 0x12A738u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 361;
        mtc1(v0, f0);
        cvt_s_w(f12, f0);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f13, f0);
        a3 = s2 & 0xFF;
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f14);
        a0 = s1;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
        a2 = 5;
        jal(ctx, 0x12A77Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        ld(a0, sp, 0xB8);
        mov_s(f12, f25);
        a1 = s4;
        a2 = s2;
        jal(ctx, 0x12A794u, gen::fn_sub_128480_00128480);  // the resistances
        ld(v0, sp, 0xB8);
        sd(v0, sp, 0x1D8);
        lwc1(f21, sp, 0x1DC);
        v0 = 0x41F00000;  // 30.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x1D8);
        add_s(f20, f1, f0);
        v0 = 0x42FA0000;  // 125.0f
        mtc1(v0, f0);
        add_s(f1, f0, f21);
        v0 = 0x41C80000;  // 25.0f
        mtc1(v0, f0);
        sub_s(f13, f1, f0);
        a3 = s2 & 0xFF;
        a0 = s1;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
        a2 = 18;
        mov_s(f12, f20);
        mov_s(f14, f25);
        jal(ctx, 0x12A7F4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x43380000;  // 184.0f
        mtc1(v0, f0);
        add_s(f1, f0, f21);
        v0 = 0x41C80000;  // 25.0f
        mtc1(v0, f0);
        sub_s(f13, f1, f0);
        a3 = s2 & 0xFF;
        a0 = s1;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
        a2 = 19;
        mov_s(f12, f20);
        mov_s(f14, f25);
        jal(ctx, 0x12A838u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        ld(a0, sp, 0xB8);
        mov_s(f12, f25);
        a1 = 0;
        a2 = s4;
        a3 = s2;
        jal(ctx, 0x12A854u, gen::fn_sub_128720_00128720);
        s0 = 0;
        ld(v0, sp, 0xB8);
        sd(v0, sp, 0x1D0);
        lwc1(f2, sp, 0x1D4);
        v0 = 0x43010000;  // 129.0f
        mtc1(v0, f0);
        add_s(f24, f0, f2);
        v0 = 0x42D00000;  // 104.0f
        mtc1(v0, f0);
        lwc1(f1, sp, 0x1D0);
        add_s(f23, f0, f1);
        v0 = 333;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f22, f0, f1);
        v0 = 0x42D80000;  // 108.0f
        mtc1(v0, f0);
        add_s(f21, f0, f1);
        v0 = 0x43020000;  // 130.0f
        mtc1(v0, f0);
        add_s(f20, f0, f2);
        for (;;) {
            // 0x0012aa80
            charge(ctx, 3);
            v0 = sltiu(s0, 5);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0012a8c8
            charge(ctx, 3);
            a1 = 4;
            if (s0 == a1) {
                // 0x0012a96c
                charge(ctx, 4);
                a0 = s4;
                jal(ctx, 0x12A970u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                s3 = v0 & 0xFF;
            } else {
                // 0x0012a8d4
                charge(ctx, 3);
                a1 = 3;
                if (s0 == a1) {
                    // 0x0012a954
                    charge(ctx, 6);
                    a0 = s4;
                    jal(ctx, 0x12A958u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                    s3 = v0 & 0xFF;
                } else {
                    // 0x0012a8e0
                    charge(ctx, 3);
                    a1 = 2;
                    if (s0 == a1) {
                        // 0x0012a93c
                        charge(ctx, 6);
                        a0 = s4;
                        jal(ctx, 0x12A940u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                        s3 = v0 & 0xFF;
                    } else {
                        // 0x0012a8ec
                        charge(ctx, 3);
                        a1 = 1;
                        if (s0 == a1) {
                            // 0x0012a924
                            charge(ctx, 6);
                            a0 = s4;
                            jal(ctx, 0x12A928u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                            s3 = v0 & 0xFF;
                        } else {
                            // 0x0012a8f8
                            charge(ctx, 2);
                            if (s0 == 0) {
                                // 0x0012a908
                                charge(ctx, 7);
                                a0 = s4;
                                a1 = 0;
                                jal(ctx, 0x12A910u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                                s3 = v0 & 0xFF;
                            } else {
                                // 0x0012a900
                                charge(ctx, 2);
                            }
                        }
                    }
                }
            }
            // 0x0012a97c
            charge(ctx, 65);
            v0 = sll(s0, 3);
            v0 = addu(v0, s0);
            v0 = sll(v0, 1);
            s5 = addu(v0, s0);
            mtc1(s5, f0);
            cvt_s_w(f0, f0);
            add_s(f1, f24, f0);
            v0 = 0x41C80000;  // 25.0f
            mtc1(v0, f0);
            sub_s(f26, f1, f0);
            a3 = s2 & 0xFF;
            a0 = s1;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
            a2 = 20;
            mov_s(f12, f23);
            mov_s(f13, f26);
            mov_s(f14, f25);
            jal(ctx, 0x12A9CCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            a3 = s2 & 0xFF;
            a0 = s1;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
            a2 = 21;
            mov_s(f12, f22);
            mov_s(f13, f26);
            mov_s(f14, f25);
            jal(ctx, 0x12A9F4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 227;
            mult(v1, s3, v0);
            v0 = 99;
            div(v1, v0);
            mflo(s7);
            a0 = 0;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
            a2 = 24;
            jal(ctx, 0x12AA20u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
            s1 = v0;
            swc1(f25, v0, 44);
            swc1(f21, v0, 16);
            mtc1(s5, f0);
            cvt_s_w(f0, f0);
            add_s(f1, f20, f0);
            v1 = 0x41C80000;  // 25.0f
            mtc1(v1, f0);
            sub_s(f0, f1, f0);
            swc1(f0, v0, 20);
            sb(s2, v0, 24);
            sh(s7, v0, 28);
            a0 = s1;
            a1 = 1;
            jal(ctx, 0x12AA68u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
            a0 = s1;
            jal(ctx, 0x12AA74u, gen::fn_sub_115980_00115980);  // draw and release the handle
            s0 = addiu(s0, 1);
        }
        // 0x0012aa8c
        charge(ctx, 68);
        ld(a0, sp, 0xB8);
        mov_s(f12, f25);
        a1 = 0;
        a2 = s4;
        a3 = s2;
        jal(ctx, 0x12AAA0u, gen::fn_sub_1293B0_001293b0);
        ld(v0, sp, 0xB8);
        sd(v0, sp, 0x1C8);
        v0 = 255;
        s0 = subu(v0, s2);
        lwc1(f1, sp, 0x1C8);
        v0 = 0x41400000;  // 12.0f
        mtc1(v0, f0);
        add_s(f2, f1, f0);
        swc1(f2, sp, 0x1C8);
        lwc1(f1, sp, 0x1CC);
        v0 = 0x42C00000;  // 96.0f
        mtc1(v0, f0);
        add_s(f1, f1, f0);
        swc1(f1, sp, 0x1CC);
        v0 = 0x43360000;  // 182.0f
        mtc1(v0, f0);
        add_s(f21, f0, f1);
        v0 = 0x41A80000;  // 21.0f
        mtc1(v0, f0);
        add_s(f20, f0, f2);
        a3 = s2 & 0xFF;
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
        a2 = 17;
        mov_s(f12, f20);
        mov_s(f13, f21);
        mov_s(f14, f25);
        jal(ctx, 0x12AB28u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 275;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0x1C8);
        add_s(f12, f1, f0);
        a3 = s2 & 0xFF;
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
        a2 = 34;
        mov_s(f13, f21);
        mov_s(f14, f25);
        jal(ctx, 0x12AB64u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x437E0000;  // 254.0f
        mtc1(v0, f0);
        add_s(f22, f0, f20);
        v0 = 0x40000000;  // 2.0f
        mtc1(v0, f0);
        add_s(f20, f0, f21);
        lbu(v1, s4, 4);
        v0 = 99;
        if (v1 != v0) {
            // 0x0012abb4
            charge(ctx, 12);
            a0 = s4;
            jal(ctx, 0x12ABB8u, gen::fn_sub_173340_00173340);  // (persona, level): the exp of that level
            s1 = v0;
            a0 = s4;
            jal(ctx, 0x12ABC8u, gen::fn_sub_173330_00173330);  // [datPersonaGetExp]
            a2 = subu(s1, v0);
            a0 = addiu(sp, 0xC0);
            a1 = addiu(gp, -30344);  // "%d"
            jal(ctx, 0x12ABDCu, gen::fn_sprintf_00523ac8);
        } else {
            // 0x0012ab9c
            charge(ctx, 6);
            a0 = addiu(sp, 0xC0);
            a1 = addiu(gp, -30336);  // &0x7CB670
            jal(ctx, 0x12ABA4u, gen::fn_sprintf_00523ac8);
        }
        // 0x0012abe4
        charge(ctx, 11);
        cvt_w_s(f0, f22);
        mfc1(a0, f0);
        cvt_w_s(f0, f20);
        mfc1(a1, f0);
        a2 = s0 & 0xFF;
        mov_s(f12, f25);
        a3 = 4;
        t0 = addiu(sp, 0xC0);
        t1 = 1;
        jal(ctx, 0x12AC08u, gen::fn_sub_40EB50_0040eb50);  // text / number at (x, y)
    }
    // 0x0012ac10 (the shared epilogue, written out on this path)
    charge(ctx, 19);
    ld(ra, sp, 0xA0);
    lq(s7, sp, 0x90);
    lq(s6, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1E0);
}

// 0x0012AC60 sub_12AC60 -- 1692 bytes; frame 0x1E0: ra sp+0xA0, s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_StatusDrawPersonaPanel] (xy, persona, alpha): the persona status panel drawn at once: labels, frames,
// resistances, stats, the five stat bars, skills and next exp.
void sub_12AC60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26};
    // 0x0012ac60
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1E0);
    sd(ra, sp, 0xA0);
    sq(s7, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0xB8);
    mov_s(f25, f12);
    s4 = a1;
    s3 = a2;
    s0 = 0;
    for (;;) {
        // 0x0012acdc
        charge(ctx, 3);
        v0 = sltiu(s0, 9);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0012acc0
        charge(ctx, 7);
        ld(a0, sp, 0xB8);
        mov_s(f12, f25);
        a1 = s0;
        a2 = s3;
        jal(ctx, 0x12ACD0u, gen::fn_sub_1281E0_001281e0);  // a stat label
        s0 = addiu(s0, 1);
    }
    // 0x0012ace8
    charge(ctx, 160);
    v0 = 0x42080000;  // 34.0f
    mtc1(v0, f12);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f13, f0);
    a3 = s3 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
    a2 = 0;
    jal(ctx, 0x12AD1Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f12);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f13, f0);
    a3 = s3 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
    a2 = 10;
    jal(ctx, 0x12AD58u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43540000;  // 212.0f
    mtc1(v0, f12);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f13, f0);
    a3 = s3 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(1));  // 0x833B74: camp sprite file 1
    a2 = 11;
    jal(ctx, 0x12AD94u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 561;
    mtc1(v0, f0);
    cvt_s_w(f12, f0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f13, f0);
    a3 = s3 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
    a2 = 1;
    jal(ctx, 0x12ADD8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 361;
    mtc1(v0, f0);
    cvt_s_w(f12, f0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f13, f0);
    a3 = s3 & 0xFF;
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f14);
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
    a2 = 5;
    jal(ctx, 0x12AE1Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    ld(a0, sp, 0xB8);
    mov_s(f12, f25);
    a1 = s4;
    a2 = s3;
    jal(ctx, 0x12AE34u, gen::fn_sub_128480_00128480);  // the resistances
    ld(v0, sp, 0xB8);
    sd(v0, sp, 0x1D8);
    lwc1(f21, sp, 0x1DC);
    v0 = 0x41F00000;  // 30.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x1D8);
    add_s(f20, f1, f0);
    v0 = 0x42FA0000;  // 125.0f
    mtc1(v0, f0);
    add_s(f1, f0, f21);
    v0 = 0x41C80000;  // 25.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s3 & 0xFF;
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
    a2 = 18;
    mov_s(f12, f20);
    mov_s(f14, f25);
    jal(ctx, 0x12AE94u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43380000;  // 184.0f
    mtc1(v0, f0);
    add_s(f1, f0, f21);
    v0 = 0x41C80000;  // 25.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s3 & 0xFF;
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
    a2 = 19;
    mov_s(f12, f20);
    mov_s(f14, f25);
    jal(ctx, 0x12AED8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    ld(a0, sp, 0xB8);
    mov_s(f12, f25);
    a1 = 0;
    a2 = s4;
    a3 = s3;
    jal(ctx, 0x12AEF4u, gen::fn_sub_128720_00128720);
    s0 = 0;
    ld(v0, sp, 0xB8);
    sd(v0, sp, 0x1D0);
    lwc1(f2, sp, 0x1D4);
    v0 = 0x43010000;  // 129.0f
    mtc1(v0, f0);
    add_s(f24, f0, f2);
    v0 = 0x42D00000;  // 104.0f
    mtc1(v0, f0);
    lwc1(f1, sp, 0x1D0);
    add_s(f23, f0, f1);
    v0 = 333;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    add_s(f22, f0, f1);
    v0 = 0x42D80000;  // 108.0f
    mtc1(v0, f0);
    add_s(f21, f0, f1);
    v0 = 0x43020000;  // 130.0f
    mtc1(v0, f0);
    add_s(f20, f0, f2);
    for (;;) {
        // 0x0012b120
        charge(ctx, 3);
        v0 = sltiu(s0, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0012af68
        charge(ctx, 3);
        a1 = 4;
        if (s0 == a1) {
            // 0x0012b00c
            charge(ctx, 4);
            a0 = s4;
            jal(ctx, 0x12B010u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
            s2 = v0 & 0xFF;
        } else {
            // 0x0012af74
            charge(ctx, 3);
            a1 = 3;
            if (s0 == a1) {
                // 0x0012aff4
                charge(ctx, 6);
                a0 = s4;
                jal(ctx, 0x12AFF8u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                s2 = v0 & 0xFF;
            } else {
                // 0x0012af80
                charge(ctx, 3);
                a1 = 2;
                if (s0 == a1) {
                    // 0x0012afdc
                    charge(ctx, 6);
                    a0 = s4;
                    jal(ctx, 0x12AFE0u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                    s2 = v0 & 0xFF;
                } else {
                    // 0x0012af8c
                    charge(ctx, 3);
                    a1 = 1;
                    if (s0 == a1) {
                        // 0x0012afc4
                        charge(ctx, 6);
                        a0 = s4;
                        jal(ctx, 0x12AFC8u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                        s2 = v0 & 0xFF;
                    } else {
                        // 0x0012af98
                        charge(ctx, 2);
                        if (s0 == 0) {
                            // 0x0012afa8
                            charge(ctx, 7);
                            a0 = s4;
                            a1 = 0;
                            jal(ctx, 0x12AFB0u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                            s2 = v0 & 0xFF;
                        } else {
                            // 0x0012afa0
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
        // 0x0012b01c
        charge(ctx, 65);
        v0 = sll(s0, 3);
        v0 = addu(v0, s0);
        v0 = sll(v0, 1);
        s5 = addu(v0, s0);
        mtc1(s5, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f24, f0);
        v0 = 0x41C80000;  // 25.0f
        mtc1(v0, f0);
        sub_s(f26, f1, f0);
        a3 = s3 & 0xFF;
        a0 = s1;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
        a2 = 20;
        mov_s(f12, f23);
        mov_s(f13, f26);
        mov_s(f14, f25);
        jal(ctx, 0x12B06Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        a3 = s3 & 0xFF;
        a0 = s1;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
        a2 = 21;
        mov_s(f12, f22);
        mov_s(f13, f26);
        mov_s(f14, f25);
        jal(ctx, 0x12B094u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 227;
        mult(v1, s2, v0);
        v0 = 99;
        div(v1, v0);
        mflo(s7);
        a0 = 0;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
        a2 = 24;
        jal(ctx, 0x12B0C0u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
        s1 = v0;
        swc1(f25, v0, 44);
        swc1(f21, v0, 16);
        mtc1(s5, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f20, f0);
        v1 = 0x41C80000;  // 25.0f
        mtc1(v1, f0);
        sub_s(f0, f1, f0);
        swc1(f0, v0, 20);
        sb(s3, v0, 24);
        sh(s7, v0, 28);
        a0 = s1;
        a1 = 1;
        jal(ctx, 0x12B108u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
        a0 = s1;
        jal(ctx, 0x12B114u, gen::fn_sub_115980_00115980);  // draw and release the handle
        s0 = addiu(s0, 1);
    }
    // 0x0012b12c
    charge(ctx, 68);
    ld(a0, sp, 0xB8);
    mov_s(f12, f25);
    a1 = 0;
    a2 = s4;
    a3 = s3;
    jal(ctx, 0x12B140u, gen::fn_sub_1293B0_001293b0);
    ld(v0, sp, 0xB8);
    sd(v0, sp, 0x1C8);
    v0 = 255;
    s0 = subu(v0, s3);
    lwc1(f1, sp, 0x1C8);
    v0 = 0x41400000;  // 12.0f
    mtc1(v0, f0);
    add_s(f2, f1, f0);
    swc1(f2, sp, 0x1C8);
    lwc1(f1, sp, 0x1CC);
    v0 = 0x42C00000;  // 96.0f
    mtc1(v0, f0);
    add_s(f1, f1, f0);
    swc1(f1, sp, 0x1CC);
    v0 = 0x43360000;  // 182.0f
    mtc1(v0, f0);
    add_s(f21, f0, f1);
    v0 = 0x41A80000;  // 21.0f
    mtc1(v0, f0);
    add_s(f20, f0, f2);
    a3 = s3 & 0xFF;
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 17;
    mov_s(f12, f20);
    mov_s(f13, f21);
    mov_s(f14, f25);
    jal(ctx, 0x12B1C8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 275;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x1C8);
    add_s(f12, f1, f0);
    a3 = s3 & 0xFF;
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 34;
    mov_s(f13, f21);
    mov_s(f14, f25);
    jal(ctx, 0x12B204u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x437E0000;  // 254.0f
    mtc1(v0, f0);
    add_s(f22, f0, f20);
    v0 = 0x40000000;  // 2.0f
    mtc1(v0, f0);
    add_s(f20, f0, f21);
    lbu(v1, s4, 4);
    v0 = 99;
    if (v1 != v0) {
        // 0x0012b254
        charge(ctx, 12);
        a0 = s4;
        jal(ctx, 0x12B258u, gen::fn_sub_173340_00173340);  // (persona, level): the exp of that level
        s1 = v0;
        a0 = s4;
        jal(ctx, 0x12B268u, gen::fn_sub_173330_00173330);  // [datPersonaGetExp]
        a2 = subu(s1, v0);
        a0 = addiu(sp, 0xC0);
        a1 = addiu(gp, -30344);  // "%d"
        jal(ctx, 0x12B27Cu, gen::fn_sprintf_00523ac8);
    } else {
        // 0x0012b23c
        charge(ctx, 6);
        a0 = addiu(sp, 0xC0);
        a1 = addiu(gp, -30336);  // &0x7CB670
        jal(ctx, 0x12B244u, gen::fn_sprintf_00523ac8);
    }
    // 0x0012b284
    charge(ctx, 30);
    cvt_w_s(f0, f22);
    mfc1(a0, f0);
    cvt_w_s(f0, f20);
    mfc1(a1, f0);
    a2 = s0 & 0xFF;
    mov_s(f12, f25);
    a3 = 4;
    t0 = addiu(sp, 0xC0);
    t1 = 1;
    jal(ctx, 0x12B2A8u, gen::fn_sub_40EB50_0040eb50);  // text / number at (x, y)
    ld(ra, sp, 0xA0);
    lq(s7, sp, 0x90);
    lq(s6, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1E0);
}

// 0x0012B300 sub_12B300 -- 1376 bytes; frame 0x1E0: ra sp+0xA0, s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_StatusDrawPersonaPanelPlain] (xy, persona, alpha): sub_12AC60 without the camp file 1 / 12 frame sprites (the
// variant drawn over another backdrop).
void sub_12B300(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26};
    // 0x0012b300
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1E0);
    sd(ra, sp, 0xA0);
    sq(s7, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0xB8);
    mov_s(f25, f12);
    s4 = a1;
    s3 = a2;
    s0 = 0;
    for (;;) {
        // 0x0012b37c
        charge(ctx, 3);
        v0 = sltiu(s0, 9);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0012b360
        charge(ctx, 7);
        ld(a0, sp, 0xB8);
        mov_s(f12, f25);
        a1 = s0;
        a2 = s3;
        jal(ctx, 0x12B370u, gen::fn_sub_1281E0_001281e0);  // a stat label
        s0 = addiu(s0, 1);
    }
    // 0x0012b388
    charge(ctx, 81);
    ld(a0, sp, 0xB8);
    mov_s(f12, f25);
    a1 = s4;
    a2 = s3;
    jal(ctx, 0x12B398u, gen::fn_sub_128480_00128480);  // the resistances
    ld(v0, sp, 0xB8);
    sd(v0, sp, 0x1D8);
    lwc1(f21, sp, 0x1DC);
    v0 = 0x41F00000;  // 30.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x1D8);
    add_s(f20, f1, f0);
    v0 = 0x42FA0000;  // 125.0f
    mtc1(v0, f0);
    add_s(f1, f0, f21);
    v0 = 0x41C80000;  // 25.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s3 & 0xFF;
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
    a2 = 18;
    mov_s(f12, f20);
    mov_s(f14, f25);
    jal(ctx, 0x12B3F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43380000;  // 184.0f
    mtc1(v0, f0);
    add_s(f1, f0, f21);
    v0 = 0x41C80000;  // 25.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s3 & 0xFF;
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
    a2 = 19;
    mov_s(f12, f20);
    mov_s(f14, f25);
    jal(ctx, 0x12B43Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    ld(a0, sp, 0xB8);
    mov_s(f12, f25);
    a1 = 0;
    a2 = s4;
    a3 = s3;
    jal(ctx, 0x12B458u, gen::fn_sub_128720_00128720);
    s0 = 0;
    ld(v0, sp, 0xB8);
    sd(v0, sp, 0x1D0);
    lwc1(f2, sp, 0x1D4);
    v0 = 0x43010000;  // 129.0f
    mtc1(v0, f0);
    add_s(f24, f0, f2);
    v0 = 0x42D00000;  // 104.0f
    mtc1(v0, f0);
    lwc1(f1, sp, 0x1D0);
    add_s(f23, f0, f1);
    v0 = 333;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    add_s(f22, f0, f1);
    v0 = 0x42D80000;  // 108.0f
    mtc1(v0, f0);
    add_s(f21, f0, f1);
    v0 = 0x43020000;  // 130.0f
    mtc1(v0, f0);
    add_s(f20, f0, f2);
    for (;;) {
        // 0x0012b684
        charge(ctx, 3);
        v0 = sltiu(s0, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0012b4cc
        charge(ctx, 3);
        a1 = 4;
        if (s0 == a1) {
            // 0x0012b570
            charge(ctx, 4);
            a0 = s4;
            jal(ctx, 0x12B574u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
            s2 = v0 & 0xFF;
        } else {
            // 0x0012b4d8
            charge(ctx, 3);
            a1 = 3;
            if (s0 == a1) {
                // 0x0012b558
                charge(ctx, 6);
                a0 = s4;
                jal(ctx, 0x12B55Cu, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                s2 = v0 & 0xFF;
            } else {
                // 0x0012b4e4
                charge(ctx, 3);
                a1 = 2;
                if (s0 == a1) {
                    // 0x0012b540
                    charge(ctx, 6);
                    a0 = s4;
                    jal(ctx, 0x12B544u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                    s2 = v0 & 0xFF;
                } else {
                    // 0x0012b4f0
                    charge(ctx, 3);
                    a1 = 1;
                    if (s0 == a1) {
                        // 0x0012b528
                        charge(ctx, 6);
                        a0 = s4;
                        jal(ctx, 0x12B52Cu, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                        s2 = v0 & 0xFF;
                    } else {
                        // 0x0012b4fc
                        charge(ctx, 2);
                        if (s0 == 0) {
                            // 0x0012b50c
                            charge(ctx, 7);
                            a0 = s4;
                            a1 = 0;
                            jal(ctx, 0x12B514u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                            s2 = v0 & 0xFF;
                        } else {
                            // 0x0012b504
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
        // 0x0012b580
        charge(ctx, 65);
        v0 = sll(s0, 3);
        v0 = addu(v0, s0);
        v0 = sll(v0, 1);
        s5 = addu(v0, s0);
        mtc1(s5, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f24, f0);
        v0 = 0x41C80000;  // 25.0f
        mtc1(v0, f0);
        sub_s(f26, f1, f0);
        a3 = s3 & 0xFF;
        a0 = s1;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
        a2 = 20;
        mov_s(f12, f23);
        mov_s(f13, f26);
        mov_s(f14, f25);
        jal(ctx, 0x12B5D0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        a3 = s3 & 0xFF;
        a0 = s1;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
        a2 = 21;
        mov_s(f12, f22);
        mov_s(f13, f26);
        mov_s(f14, f25);
        jal(ctx, 0x12B5F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 227;
        mult(v1, s2, v0);
        v0 = 99;
        div(v1, v0);
        mflo(s7);
        a0 = 0;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
        a2 = 24;
        jal(ctx, 0x12B624u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
        s1 = v0;
        swc1(f25, v0, 44);
        swc1(f21, v0, 16);
        mtc1(s5, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f20, f0);
        v1 = 0x41C80000;  // 25.0f
        mtc1(v1, f0);
        sub_s(f0, f1, f0);
        swc1(f0, v0, 20);
        sb(s3, v0, 24);
        sh(s7, v0, 28);
        a0 = s1;
        a1 = 1;
        jal(ctx, 0x12B66Cu, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
        a0 = s1;
        jal(ctx, 0x12B678u, gen::fn_sub_115980_00115980);  // draw and release the handle
        s0 = addiu(s0, 1);
    }
    // 0x0012b690
    charge(ctx, 68);
    ld(a0, sp, 0xB8);
    mov_s(f12, f25);
    a1 = 0;
    a2 = s4;
    a3 = s3;
    jal(ctx, 0x12B6A4u, gen::fn_sub_1293B0_001293b0);
    ld(v0, sp, 0xB8);
    sd(v0, sp, 0x1C8);
    v0 = 255;
    s0 = subu(v0, s3);
    lwc1(f1, sp, 0x1C8);
    v0 = 0x41400000;  // 12.0f
    mtc1(v0, f0);
    add_s(f2, f1, f0);
    swc1(f2, sp, 0x1C8);
    lwc1(f1, sp, 0x1CC);
    v0 = 0x42C00000;  // 96.0f
    mtc1(v0, f0);
    add_s(f1, f1, f0);
    swc1(f1, sp, 0x1CC);
    v0 = 0x43360000;  // 182.0f
    mtc1(v0, f0);
    add_s(f21, f0, f1);
    v0 = 0x41A80000;  // 21.0f
    mtc1(v0, f0);
    add_s(f20, f0, f2);
    a3 = s3 & 0xFF;
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 17;
    mov_s(f12, f20);
    mov_s(f13, f21);
    mov_s(f14, f25);
    jal(ctx, 0x12B72Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 275;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x1C8);
    add_s(f12, f1, f0);
    a3 = s3 & 0xFF;
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 34;
    mov_s(f13, f21);
    mov_s(f14, f25);
    jal(ctx, 0x12B768u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x437E0000;  // 254.0f
    mtc1(v0, f0);
    add_s(f22, f0, f20);
    v0 = 0x40000000;  // 2.0f
    mtc1(v0, f0);
    add_s(f20, f0, f21);
    lbu(v1, s4, 4);
    v0 = 99;
    if (v1 != v0) {
        // 0x0012b7b8
        charge(ctx, 12);
        a0 = s4;
        jal(ctx, 0x12B7BCu, gen::fn_sub_173340_00173340);  // (persona, level): the exp of that level
        s1 = v0;
        a0 = s4;
        jal(ctx, 0x12B7CCu, gen::fn_sub_173330_00173330);  // [datPersonaGetExp]
        a2 = subu(s1, v0);
        a0 = addiu(sp, 0xC0);
        a1 = addiu(gp, -30344);  // "%d"
        jal(ctx, 0x12B7E0u, gen::fn_sprintf_00523ac8);
    } else {
        // 0x0012b7a0
        charge(ctx, 6);
        a0 = addiu(sp, 0xC0);
        a1 = addiu(gp, -30336);  // &0x7CB670
        jal(ctx, 0x12B7A8u, gen::fn_sprintf_00523ac8);
    }
    // 0x0012b7e8
    charge(ctx, 30);
    cvt_w_s(f0, f22);
    mfc1(a0, f0);
    cvt_w_s(f0, f20);
    mfc1(a1, f0);
    a2 = s0 & 0xFF;
    mov_s(f12, f25);
    a3 = 4;
    t0 = addiu(sp, 0xC0);
    t1 = 1;
    jal(ctx, 0x12B80Cu, gen::fn_sub_40EB50_0040eb50);  // text / number at (x, y)
    ld(ra, sp, 0xA0);
    lq(s7, sp, 0x90);
    lq(s6, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1E0);
}

// 0x0012B860 sub_12B860 -- 1144 bytes; frame 0x1A0: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_StatusDrawPersonaTable] (xy, bonus, persona, alpha): the persona table used by the persona screen and the
// facilities: labels, resistances, stats with the bonus bytes (sub_128720), the five bars with the gain bars
// (sub_129160 per stat), skills, next exp.
void sub_12B860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x0012b860
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1A0);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x88);
    mov_s(f20, f12);
    s4 = a1;
    s3 = a2;
    s2 = a3;
    s1 = 0;
    for (;;) {
        // 0x0012b8cc
        charge(ctx, 3);
        v0 = sltiu(s1, 9);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0012b8b0
        charge(ctx, 7);
        ld(a0, sp, 0x88);
        mov_s(f12, f20);
        a1 = s1;
        a2 = s2;
        jal(ctx, 0x12B8C0u, gen::fn_sub_1281E0_001281e0);  // a stat label
        s1 = addiu(s1, 1);
    }
    // 0x0012b8d8
    charge(ctx, 57);
    ld(a0, sp, 0x88);
    mov_s(f12, f20);
    a1 = s3;
    a2 = s2;
    jal(ctx, 0x12B8E8u, gen::fn_sub_128480_00128480);  // the resistances
    ld(v0, sp, 0x88);
    sd(v0, sp, 0x198);
    lwc1(f22, sp, 0x19C);
    v0 = 0x41F00000;  // 30.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x198);
    add_s(f21, f1, f0);
    v0 = 0x42FA0000;  // 125.0f
    mtc1(v0, f0);
    add_s(f1, f0, f22);
    v0 = 0x41C80000;  // 25.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s2 & 0xFF;
    a0 = s0;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
    a2 = 18;
    mov_s(f12, f21);
    mov_s(f14, f20);
    jal(ctx, 0x12B948u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43380000;  // 184.0f
    mtc1(v0, f0);
    add_s(f1, f0, f22);
    v0 = 0x41C80000;  // 25.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s2 & 0xFF;
    a0 = s0;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
    a2 = 19;
    mov_s(f12, f21);
    mov_s(f14, f20);
    jal(ctx, 0x12B98Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    ld(a0, sp, 0x88);
    mov_s(f12, f20);
    a1 = s4;
    a2 = s3;
    a3 = s2;
    jal(ctx, 0x12B9A8u, gen::fn_sub_128720_00128720);
    s1 = 0;
    for (;;) {
        // 0x0012bb10
        charge(ctx, 3);
        v0 = sltiu(s1, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0012b9bc
        charge(ctx, 3);
        a1 = 4;
        if (s1 == a1) {
            // 0x0012ba60
            charge(ctx, 4);
            a0 = s3;
            jal(ctx, 0x12BA64u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
            s0 = v0 & 0xFF;
        } else {
            // 0x0012b9c8
            charge(ctx, 3);
            a1 = 3;
            if (s1 == a1) {
                // 0x0012ba48
                charge(ctx, 6);
                a0 = s3;
                jal(ctx, 0x12BA4Cu, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                s0 = v0 & 0xFF;
            } else {
                // 0x0012b9d4
                charge(ctx, 3);
                a1 = 2;
                if (s1 == a1) {
                    // 0x0012ba30
                    charge(ctx, 6);
                    a0 = s3;
                    jal(ctx, 0x12BA34u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                    s0 = v0 & 0xFF;
                } else {
                    // 0x0012b9e0
                    charge(ctx, 3);
                    a1 = 1;
                    if (s1 == a1) {
                        // 0x0012ba18
                        charge(ctx, 6);
                        a0 = s3;
                        jal(ctx, 0x12BA1Cu, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                        s0 = v0 & 0xFF;
                    } else {
                        // 0x0012b9ec
                        charge(ctx, 2);
                        if (s1 == 0) {
                            // 0x0012b9fc
                            charge(ctx, 7);
                            a0 = s3;
                            a1 = 0;
                            jal(ctx, 0x12BA04u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
                            s0 = v0 & 0xFF;
                        } else {
                            // 0x0012b9f4
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
        // 0x0012ba70
        charge(ctx, 3);
        a3 = 0;
        if (s4 != 0) {
            // 0x0012ba7c
            charge(ctx, 3);
            v0 = 4;
            if (s1 == v0) {
                // 0x0012baec
                charge(ctx, 1);
                lbu(a3, s4, 60);
            } else {
                // 0x0012ba88
                charge(ctx, 3);
                v0 = 3;
                if (s1 == v0) {
                    // 0x0012bae0
                    charge(ctx, 3);
                    lbu(a3, s4, 59);
                } else {
                    // 0x0012ba94
                    charge(ctx, 3);
                    v0 = 2;
                    if (s1 == v0) {
                        // 0x0012bad4
                        charge(ctx, 3);
                        lbu(a3, s4, 58);
                    } else {
                        // 0x0012baa0
                        charge(ctx, 3);
                        v0 = 1;
                        if (s1 == v0) {
                            // 0x0012bac8
                            charge(ctx, 3);
                            lbu(a3, s4, 57);
                        } else {
                            // 0x0012baac
                            charge(ctx, 2);
                            if (s1 == 0) {
                                // 0x0012babc
                                charge(ctx, 3);
                                lbu(a3, s4, 56);
                            } else {
                                // 0x0012bab4
                                charge(ctx, 2);
                            }
                        }
                    }
                }
            }
        }
        // 0x0012baf0
        charge(ctx, 8);
        ld(a0, sp, 0x88);
        mov_s(f12, f20);
        a1 = s1;
        a2 = s0;
        t0 = s2;
        jal(ctx, 0x12BB04u, gen::fn_sub_129160_00129160);  // a stat bar
        s1 = addiu(s1, 1);
    }
    // 0x0012bb1c
    charge(ctx, 68);
    ld(a0, sp, 0x88);
    mov_s(f12, f20);
    a1 = s4;
    a2 = s3;
    a3 = s2;
    jal(ctx, 0x12BB30u, gen::fn_sub_1293B0_001293b0);
    ld(v0, sp, 0x88);
    sd(v0, sp, 0x190);
    v0 = 255;
    s0 = subu(v0, s2);
    lwc1(f1, sp, 0x190);
    v0 = 0x41400000;  // 12.0f
    mtc1(v0, f0);
    add_s(f2, f1, f0);
    swc1(f2, sp, 0x190);
    lwc1(f1, sp, 0x194);
    v0 = 0x42C00000;  // 96.0f
    mtc1(v0, f0);
    add_s(f1, f1, f0);
    swc1(f1, sp, 0x194);
    v0 = 0x43360000;  // 182.0f
    mtc1(v0, f0);
    add_s(f22, f0, f1);
    v0 = 0x41A80000;  // 21.0f
    mtc1(v0, f0);
    add_s(f21, f0, f2);
    a3 = s2 & 0xFF;
    a0 = s5;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 17;
    mov_s(f12, f21);
    mov_s(f13, f22);
    mov_s(f14, f20);
    jal(ctx, 0x12BBB8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 275;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x190);
    add_s(f12, f1, f0);
    a3 = s2 & 0xFF;
    a0 = s5;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 34;
    mov_s(f13, f22);
    mov_s(f14, f20);
    jal(ctx, 0x12BBF4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x437E0000;  // 254.0f
    mtc1(v0, f0);
    add_s(f23, f0, f21);
    v0 = 0x40000000;  // 2.0f
    mtc1(v0, f0);
    add_s(f21, f0, f22);
    lbu(v1, s3, 4);
    v0 = 99;
    if (v1 != v0) {
        // 0x0012bc44
        charge(ctx, 12);
        a0 = s3;
        jal(ctx, 0x12BC48u, gen::fn_sub_173340_00173340);  // (persona, level): the exp of that level
        s1 = v0;
        a0 = s3;
        jal(ctx, 0x12BC58u, gen::fn_sub_173330_00173330);  // [datPersonaGetExp]
        a2 = subu(s1, v0);
        a0 = addiu(sp, 0x90);
        a1 = addiu(gp, -30344);  // "%d"
        jal(ctx, 0x12BC6Cu, gen::fn_sprintf_00523ac8);
    } else {
        // 0x0012bc2c
        charge(ctx, 6);
        a0 = addiu(sp, 0x90);
        a1 = addiu(gp, -30336);  // &0x7CB670
        jal(ctx, 0x12BC34u, gen::fn_sprintf_00523ac8);
    }
    // 0x0012bc74
    charge(ctx, 25);
    cvt_w_s(f0, f23);
    mfc1(a0, f0);
    cvt_w_s(f0, f21);
    mfc1(a1, f0);
    a2 = s0 & 0xFF;
    mov_s(f12, f20);
    a3 = 4;
    t0 = addiu(sp, 0x90);
    t1 = 1;
    jal(ctx, 0x12BC98u, gen::fn_sub_40EB50_0040eb50);  // text / number at (x, y)
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1A0);
}

// 0x0012BFB0 sub_12BFB0 -- 1144 bytes; frame 0x1A0: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_StatusDrawPersonaBaseTable] (xy, bonus, persona, alpha): sub_12B860 on the base stats (sub_128C40 /
// sub_173580).
void sub_12BFB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x0012bfb0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1A0);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x88);
    mov_s(f20, f12);
    s4 = a1;
    s3 = a2;
    s2 = a3;
    s1 = 0;
    for (;;) {
        // 0x0012c01c
        charge(ctx, 3);
        v0 = sltiu(s1, 9);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0012c000
        charge(ctx, 7);
        ld(a0, sp, 0x88);
        mov_s(f12, f20);
        a1 = s1;
        a2 = s2;
        jal(ctx, 0x12C010u, gen::fn_sub_1281E0_001281e0);  // a stat label
        s1 = addiu(s1, 1);
    }
    // 0x0012c028
    charge(ctx, 57);
    ld(a0, sp, 0x88);
    mov_s(f12, f20);
    a1 = s3;
    a2 = s2;
    jal(ctx, 0x12C038u, gen::fn_sub_128480_00128480);  // the resistances
    ld(v0, sp, 0x88);
    sd(v0, sp, 0x198);
    lwc1(f22, sp, 0x19C);
    v0 = 0x41F00000;  // 30.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x198);
    add_s(f21, f1, f0);
    v0 = 0x42FA0000;  // 125.0f
    mtc1(v0, f0);
    add_s(f1, f0, f22);
    v0 = 0x41C80000;  // 25.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s2 & 0xFF;
    a0 = s0;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
    a2 = 18;
    mov_s(f12, f21);
    mov_s(f14, f20);
    jal(ctx, 0x12C098u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43380000;  // 184.0f
    mtc1(v0, f0);
    add_s(f1, f0, f22);
    v0 = 0x41C80000;  // 25.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s2 & 0xFF;
    a0 = s0;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(10));  // 0x833B98: camp sprite file 10
    a2 = 19;
    mov_s(f12, f21);
    mov_s(f14, f20);
    jal(ctx, 0x12C0DCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    ld(a0, sp, 0x88);
    mov_s(f12, f20);
    a1 = s4;
    a2 = s3;
    a3 = s2;
    jal(ctx, 0x12C0F8u, gen::fn_sub_128C40_00128c40);
    s1 = 0;
    for (;;) {
        // 0x0012c260
        charge(ctx, 3);
        v0 = sltiu(s1, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0012c10c
        charge(ctx, 3);
        a1 = 4;
        if (s1 == a1) {
            // 0x0012c1b0
            charge(ctx, 4);
            a0 = s3;
            jal(ctx, 0x12C1B4u, gen::fn_sub_173580_00173580);  // (persona, stat): the stat without the bonus
            s0 = v0 & 0xFF;
        } else {
            // 0x0012c118
            charge(ctx, 3);
            a1 = 3;
            if (s1 == a1) {
                // 0x0012c198
                charge(ctx, 6);
                a0 = s3;
                jal(ctx, 0x12C19Cu, gen::fn_sub_173580_00173580);  // (persona, stat): the stat without the bonus
                s0 = v0 & 0xFF;
            } else {
                // 0x0012c124
                charge(ctx, 3);
                a1 = 2;
                if (s1 == a1) {
                    // 0x0012c180
                    charge(ctx, 6);
                    a0 = s3;
                    jal(ctx, 0x12C184u, gen::fn_sub_173580_00173580);  // (persona, stat): the stat without the bonus
                    s0 = v0 & 0xFF;
                } else {
                    // 0x0012c130
                    charge(ctx, 3);
                    a1 = 1;
                    if (s1 == a1) {
                        // 0x0012c168
                        charge(ctx, 6);
                        a0 = s3;
                        jal(ctx, 0x12C16Cu, gen::fn_sub_173580_00173580);  // (persona, stat): the stat without the bonus
                        s0 = v0 & 0xFF;
                    } else {
                        // 0x0012c13c
                        charge(ctx, 2);
                        if (s1 == 0) {
                            // 0x0012c14c
                            charge(ctx, 7);
                            a0 = s3;
                            a1 = 0;
                            jal(ctx, 0x12C154u, gen::fn_sub_173580_00173580);  // (persona, stat): the stat without the bonus
                            s0 = v0 & 0xFF;
                        } else {
                            // 0x0012c144
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
        // 0x0012c1c0
        charge(ctx, 3);
        a3 = 0;
        if (s4 != 0) {
            // 0x0012c1cc
            charge(ctx, 3);
            v0 = 4;
            if (s1 == v0) {
                // 0x0012c23c
                charge(ctx, 1);
                lbu(a3, s4, 60);
            } else {
                // 0x0012c1d8
                charge(ctx, 3);
                v0 = 3;
                if (s1 == v0) {
                    // 0x0012c230
                    charge(ctx, 3);
                    lbu(a3, s4, 59);
                } else {
                    // 0x0012c1e4
                    charge(ctx, 3);
                    v0 = 2;
                    if (s1 == v0) {
                        // 0x0012c224
                        charge(ctx, 3);
                        lbu(a3, s4, 58);
                    } else {
                        // 0x0012c1f0
                        charge(ctx, 3);
                        v0 = 1;
                        if (s1 == v0) {
                            // 0x0012c218
                            charge(ctx, 3);
                            lbu(a3, s4, 57);
                        } else {
                            // 0x0012c1fc
                            charge(ctx, 2);
                            if (s1 == 0) {
                                // 0x0012c20c
                                charge(ctx, 3);
                                lbu(a3, s4, 56);
                            } else {
                                // 0x0012c204
                                charge(ctx, 2);
                            }
                        }
                    }
                }
            }
        }
        // 0x0012c240
        charge(ctx, 8);
        ld(a0, sp, 0x88);
        mov_s(f12, f20);
        a1 = s1;
        a2 = s0;
        t0 = s2;
        jal(ctx, 0x12C254u, gen::fn_sub_129160_00129160);  // a stat bar
        s1 = addiu(s1, 1);
    }
    // 0x0012c26c
    charge(ctx, 68);
    ld(a0, sp, 0x88);
    mov_s(f12, f20);
    a1 = s4;
    a2 = s3;
    a3 = s2;
    jal(ctx, 0x12C280u, gen::fn_sub_1293B0_001293b0);
    ld(v0, sp, 0x88);
    sd(v0, sp, 0x190);
    v0 = 255;
    s0 = subu(v0, s2);
    lwc1(f1, sp, 0x190);
    v0 = 0x41400000;  // 12.0f
    mtc1(v0, f0);
    add_s(f2, f1, f0);
    swc1(f2, sp, 0x190);
    lwc1(f1, sp, 0x194);
    v0 = 0x42C00000;  // 96.0f
    mtc1(v0, f0);
    add_s(f1, f1, f0);
    swc1(f1, sp, 0x194);
    v0 = 0x43360000;  // 182.0f
    mtc1(v0, f0);
    add_s(f22, f0, f1);
    v0 = 0x41A80000;  // 21.0f
    mtc1(v0, f0);
    add_s(f21, f0, f2);
    a3 = s2 & 0xFF;
    a0 = s5;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 17;
    mov_s(f12, f21);
    mov_s(f13, f22);
    mov_s(f14, f20);
    jal(ctx, 0x12C308u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 275;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x190);
    add_s(f12, f1, f0);
    a3 = s2 & 0xFF;
    a0 = s5;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 34;
    mov_s(f13, f22);
    mov_s(f14, f20);
    jal(ctx, 0x12C344u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x437E0000;  // 254.0f
    mtc1(v0, f0);
    add_s(f23, f0, f21);
    v0 = 0x40000000;  // 2.0f
    mtc1(v0, f0);
    add_s(f21, f0, f22);
    lbu(v1, s3, 4);
    v0 = 99;
    if (v1 != v0) {
        // 0x0012c394
        charge(ctx, 12);
        a0 = s3;
        jal(ctx, 0x12C398u, gen::fn_sub_173340_00173340);  // (persona, level): the exp of that level
        s1 = v0;
        a0 = s3;
        jal(ctx, 0x12C3A8u, gen::fn_sub_173330_00173330);  // [datPersonaGetExp]
        a2 = subu(s1, v0);
        a0 = addiu(sp, 0x90);
        a1 = addiu(gp, -30344);  // "%d"
        jal(ctx, 0x12C3BCu, gen::fn_sprintf_00523ac8);
    } else {
        // 0x0012c37c
        charge(ctx, 6);
        a0 = addiu(sp, 0x90);
        a1 = addiu(gp, -30336);  // &0x7CB670
        jal(ctx, 0x12C384u, gen::fn_sprintf_00523ac8);
    }
    // 0x0012c3c4
    charge(ctx, 25);
    cvt_w_s(f0, f23);
    mfc1(a0, f0);
    cvt_w_s(f0, f21);
    mfc1(a1, f0);
    a2 = s0 & 0xFF;
    mov_s(f12, f20);
    a3 = 4;
    t0 = addiu(sp, 0x90);
    t1 = 1;
    jal(ctx, 0x12C3E8u, gen::fn_sub_40EB50_0040eb50);  // text / number at (x, y)
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1A0);
}

// 0x00133180 sub_133180 -- 356 bytes; frame 0x80: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [H_Camp_DrawPersonaCard] (xy, bonus, persona, fade): the facility screens' persona card: the table (sub_12B860) at
// alpha 255 - fade, the frame (sprite 1 of camp file 8) and the arcana card (camp file 6, datPersonaGetArcana - 1) at
// +12 / +96, the level (sub_124E60) and the name (sub_124FD0).
void sub_133180(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20};
    // 0x00133180
    enter(ctx, 89);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x68);
    mov_s(f20, f12);
    s2 = a2;
    v0 = 255;
    s0 = subu(v0, a3);
    a3 = s0;
    jal(ctx, 0x1331B4u, gen::fn_sub_12B860_0012b860);
    lwc1(f1, sp, 0x68);
    v0 = 0x41400000;  // 12.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x68);
    lwc1(f1, sp, 0x6C);
    v0 = 0x42C00000;  // 96.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x6C);
    ld(v0, sp, 0x68);
    sd(v0, sp, 0x78);
    v0 = 0x41B00000;  // 22.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x78);
    add_s(f12, f1, f0);
    v0 = 0x42EA0000;  // 117.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x7C);
    add_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 1;
    mov_s(f14, f20);
    jal(ctx, 0x13322Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    ld(v0, sp, 0x68);
    sd(v0, sp, 0x70);
    v0 = 0x830000;
    lw(s3, v0, spr::camp(6));  // 0x833B88: camp sprite file 6
    lhu(a0, s2, 2);
    jal(ctx, 0x133248u, gen::fn_sub_173280_00173280);  // [datPersonaGetArcana]
    v0 = v0 & 0xFF;
    a2 = addiu(v0, -1);
    v0 = 0x42D20000;  // 105.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x70);
    add_s(f12, f1, f0);
    v0 = 0x430E0000;  // 142.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x74);
    add_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    a0 = s1;
    a1 = s3;
    mov_s(f14, f20);
    jal(ctx, 0x133288u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    ld(a0, sp, 0x68);
    mov_s(f12, f20);
    a1 = s2;
    a2 = s0;
    jal(ctx, 0x1332A0u, gen::fn_sub_124E60_00124e60);  // the persona level
    ld(a0, sp, 0x68);
    mov_s(f12, f20);
    a1 = s2;
    a2 = s0;
    jal(ctx, 0x1332B8u, gen::fn_sub_124FD0_00124fd0);  // [numbered label] the persona name
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00133460 sub_133460 -- 356 bytes; frame 0x80: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [H_Camp_DrawPersonaBaseCard] (xy, bonus, persona, fade): sub_133180 on the base-stat table (sub_12BFB0).
void sub_133460(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20};
    // 0x00133460
    enter(ctx, 89);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x68);
    mov_s(f20, f12);
    s2 = a2;
    v0 = 255;
    s0 = subu(v0, a3);
    a3 = s0;
    jal(ctx, 0x133494u, gen::fn_sub_12BFB0_0012bfb0);
    lwc1(f1, sp, 0x68);
    v0 = 0x41400000;  // 12.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x68);
    lwc1(f1, sp, 0x6C);
    v0 = 0x42C00000;  // 96.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x6C);
    ld(v0, sp, 0x68);
    sd(v0, sp, 0x78);
    v0 = 0x41B00000;  // 22.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x78);
    add_s(f12, f1, f0);
    v0 = 0x42EA0000;  // 117.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x7C);
    add_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(8));  // 0x833B90: camp sprite file 8
    a2 = 1;
    mov_s(f14, f20);
    jal(ctx, 0x13350Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    ld(v0, sp, 0x68);
    sd(v0, sp, 0x70);
    v0 = 0x830000;
    lw(s3, v0, spr::camp(6));  // 0x833B88: camp sprite file 6
    lhu(a0, s2, 2);
    jal(ctx, 0x133528u, gen::fn_sub_173280_00173280);  // [datPersonaGetArcana]
    v0 = v0 & 0xFF;
    a2 = addiu(v0, -1);
    v0 = 0x42D20000;  // 105.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x70);
    add_s(f12, f1, f0);
    v0 = 0x430E0000;  // 142.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x74);
    add_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    a0 = s1;
    a1 = s3;
    mov_s(f14, f20);
    jal(ctx, 0x133568u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    ld(a0, sp, 0x68);
    mov_s(f12, f20);
    a1 = s2;
    a2 = s0;
    jal(ctx, 0x133580u, gen::fn_sub_124E60_00124e60);  // the persona level
    ld(a0, sp, 0x68);
    mov_s(f12, f20);
    a1 = s2;
    a2 = s0;
    jal(ctx, 0x133598u, gen::fn_sub_124FD0_00124fd0);  // [numbered label] the persona name
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x001345B0 sub_1345B0 -- 836 bytes; frame 0x60: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [H_Camp_PersonaDrawElement] (tween, ?, element, ids, cursor, previous): one tween element of the persona screen's
// detail (jump table 0x7B5C80): 0 / 1 the persona table and panel of the selected (+cursor) or previous stock slot, the
// rest its frame sprites of camp file 13.
void sub_1345B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20};
    // 0x001345b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s2 = a0;
    s1 = a1;
    at = sltiu(a2, 6);
    if (at != 0) {
        // 0x001345dc
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 23680);  // &0x7B5C80
        v1 = sll(a2, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x1345F8u:  // table[0]: element 0: the selected persona's table and panel
            // 0x001345f8
            charge(ctx, 45);
            v0 = dsll32(t0, 16);
            v0 = dsra32(v0, 16);
            v0 = sll(v0, 1);
            v0 = addu(a3, v0);
            lh(a0, v0, 0);
            jal(ctx, 0x13460Cu, gen::fn_sub_174A90_00174a90);  // [datPersonaGetHeroPersona] (slot)
            s0 = v0;
            lw(v0, s2, tw::kAlpha);
            v1 = 255;
            v0 = subu(v1, v0);
            lwc1(f20, s2, tw::kZ);
            lwc1(f1, s2, tw::kX);
            lwc1(f0, s2, tw::kY);
            swc1(f1, sp, 0x58);
            swc1(f0, sp, 0x5C);
            s1 = subu(v1, v0);
            ld(a0, sp, 0x58);
            mov_s(f12, f20);
            a1 = 0;
            a2 = s0;
            a3 = s1;
            jal(ctx, 0x134650u, gen::fn_sub_12B860_0012b860);
            lwc1(f1, sp, 0x58);
            v0 = 0x41400000;  // 12.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x58);
            lwc1(f1, sp, 0x5C);
            v0 = 0x42C00000;  // 96.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x5C);
            ld(a0, sp, 0x58);
            a1 = a0;
            mov_s(f12, f20);
            a2 = s0;
            a3 = s1;
            jal(ctx, 0x13469Cu, gen::fn_sub_125B40_00125b40);  // the persona panel
            break;
        case 0x1346ACu:  // table[1]: element 1: the previous persona's table and panel
            // 0x001346ac
            charge(ctx, 45);
            v0 = dsll32(t1, 16);
            v0 = dsra32(v0, 16);
            v0 = sll(v0, 1);
            v0 = addu(a3, v0);
            lh(a0, v0, 0);
            jal(ctx, 0x1346C0u, gen::fn_sub_174A90_00174a90);  // [datPersonaGetHeroPersona] (slot)
            s0 = v0;
            lw(v0, s2, tw::kAlpha);
            v1 = 255;
            v0 = subu(v1, v0);
            lwc1(f20, s2, tw::kZ);
            lwc1(f1, s2, tw::kX);
            lwc1(f0, s2, tw::kY);
            swc1(f1, sp, 0x50);
            swc1(f0, sp, 0x54);
            s1 = subu(v1, v0);
            ld(a0, sp, 0x50);
            mov_s(f12, f20);
            a1 = 0;
            a2 = s0;
            a3 = s1;
            jal(ctx, 0x134704u, gen::fn_sub_12B860_0012b860);
            lwc1(f1, sp, 0x50);
            v0 = 0x41400000;  // 12.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x50);
            lwc1(f1, sp, 0x54);
            v0 = 0x42C00000;  // 96.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x54);
            ld(a0, sp, 0x50);
            a1 = a0;
            mov_s(f12, f20);
            a2 = s0;
            a3 = s1;
            jal(ctx, 0x134750u, gen::fn_sub_125B40_00125b40);  // the persona panel
            break;
        case 0x134760u:  // table[2]
            // 0x00134760
            charge(ctx, 11);
            lbu(a3, s2, tw::kAlpha);
            a0 = s0;
            lw(a1, s1, 0);
            a2 = 2;
            lwc1(f12, s2, tw::kX);
            lwc1(f13, s2, tw::kY);
            lwc1(f14, s2, tw::kZ);
            jal(ctx, 0x13477Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x13478Cu:  // table[3]
            // 0x0013478c
            charge(ctx, 11);
            lbu(a3, s2, tw::kAlpha);
            a0 = s0;
            lw(a1, s1, 0);
            a2 = 3;
            lwc1(f12, s2, tw::kX);
            lwc1(f13, s2, tw::kY);
            lwc1(f14, s2, tw::kZ);
            jal(ctx, 0x1347A8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x1347B8u:  // table[4]
            // 0x001347b8
            charge(ctx, 11);
            lbu(a3, s2, tw::kAlpha);
            a0 = s0;
            lw(a1, s1, 0);
            a2 = 1;
            lwc1(f12, s2, tw::kX);
            lwc1(f13, s2, tw::kY);
            lwc1(f14, s2, tw::kZ);
            jal(ctx, 0x1347D4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x1347E4u:  // table[5]
            // 0x001347e4
            charge(ctx, 60);
            lbu(a3, s2, tw::kAlpha);
            a0 = s0;
            lw(a1, s1, 8);
            a2 = 0;
            lwc1(f12, s2, tw::kX);
            lwc1(f13, s2, tw::kY);
            lwc1(f14, s2, tw::kZ);
            jal(ctx, 0x134800u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s2, tw::kX);
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            v0 = 0x42080000;  // 34.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            lbu(a3, s2, tw::kAlpha);
            a0 = s0;
            lw(a1, s1, 8);
            a2 = 2;
            lwc1(f13, s2, tw::kY);
            lwc1(f14, s2, tw::kZ);
            jal(ctx, 0x134844u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 433;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s2, tw::kX);
            add_s(f12, f1, f0);
            lbu(a3, s2, tw::kAlpha);
            a0 = s0;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
            a2 = 2;
            lwc1(f13, s2, tw::kY);
            lwc1(f14, s2, tw::kZ);
            jal(ctx, 0x134880u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 561;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s2, tw::kX);
            add_s(f1, f1, f0);
            v0 = 0x42080000;  // 34.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            lbu(a3, s2, tw::kAlpha);
            a0 = s0;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
            a2 = 3;
            lwc1(f13, s2, tw::kY);
            lwc1(f14, s2, tw::kZ);
            jal(ctx, 0x1348CCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x001348d4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00134900 sub_134900 -- 260 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_PersonaRunDetailTweens] (tweens, ...): steps the 10 detail tween records (sub_18B700), draws each active one
// (sub_1345B0) and returns 1 when all reached their last frame.
void sub_134900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00134900
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    s3 = a2;
    s6 = a3;
    s7 = t0;
    s1 = 1;
    s2 = 0;
    for (;;) {
        // 0x001349c4
        charge(ctx, 3);
        v0 = slti(s2, 10);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0013494c
        charge(ctx, 7);
        v0 = sll(s2, 4);
        v0 = addu(v0, s2);
        v0 = sll(v0, 2);
        s0 = addu(s5, v0);
        lw(v0, s0, 4);
        if (v0 != 0) {
            // 0x00134968
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x13496Cu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
            if (v0 != 0) {
                // 0x0013497c
                charge(ctx, 8);
                a0 = s0;
                a1 = s4;
                a2 = s2;
                a3 = s3;
                t0 = s6;
                t1 = s7;
                jal(ctx, 0x134994u, gen::fn_sub_1345B0_001345b0);
            }
            // 0x0013499c
            charge(ctx, 8);
            v0 = sll(s2, 4);
            v0 = addu(v0, s2);
            v0 = sll(v0, 2);
            v0 = addu(s5, v0);
            lw(v1, v0, 24);
            lw(v0, v0, 32);
            if (v1 != v0) {
                // 0x001349bc
                charge(ctx, 1);
                s1 = 0;
            }
        }
        // 0x001349c0
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x001349d0
    charge(ctx, 13);
    v0 = s1;
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00167930 sub_167930 -- 1412 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_UpdateFrStatusPersonaDrawTask] Update of "H_CampFrStatusPersonaDraw" (the party-status screen's persona page;
// jump table 0x7B62C0): state 0 requests flash 2 (sub_1685E0) and creates a "CampPersonaDispCtlDraw" picture of the
// member's persona (+14); 1 sets the side portraits to screen 3; 2 draws the picture background and fades the persona
// panel in (sub_129B30 / sub_12AC60) -- cancel / page switch answered; 3..5 fade out (sub_12A560) and return -1.
void sub_167930(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00167930
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    mtc1(zero, f0);
    sw(zero, sp, 0x5C);
    sw(zero, sp, 0x58);
    lw(v0, s0, frp::kState);
    at = sltiu(v0, 6);
    if (at != 0) {
        // 0x0016796c
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 25280);  // &0x7B62C0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x167988u:  // table[0]: state 0: flash 2, create the persona picture
            // 0x00167988
            charge(ctx, 18);
            lw(a0, gp, g::kFrStatusFlashTask);  // 0x7CDF88
            a1 = 2;
            jal(ctx, 0x167990u, gen::fn_sub_1685E0_001685e0);  // [H_Camp_FrStatusFlashRequest]
            lh(a0, s0, frp::kPc);
            jal(ctx, 0x16799Cu, gen::fn_sub_16C860_0016c860);  // [datGetPcPersonaId]
            s2 = v0;
            a0 = 1;
            a1 = 300;
            a2 = 0x40000;
            v0 = 0x960000;
            lw(v0, v0, 388);  // 0x960184
            jalr(ctx, 0x1679BCu, v0.u());
            s3 = v0;
            if (s3 != 0) {
                // 0x001679dc
                charge(ctx, 13);
                a0 = s1;
                a1 = 0x5E0000;
                a1 = addiu(a1, -20080);  // "CampPersonaDispCtlDraw"
                a2 = 6335;
                a3 = 0x130000;
                a3 = addiu(a3, 14208);  // &sub_133780
                t0 = 0x130000;
                t0 = addiu(t0, 14592);  // &sub_133900
                t1 = s3;
                jal(ctx, 0x167A00u, gen::fn_kwlnTaskCreate_00194b20);  // (parent, name, priority, update, destroy, work)
                if (v0 != 0) {
                    // 0x00167a1c
                    charge(ctx, 5);
                    sw(s2, s3, 4);
                    v1 = si(-1);
                    sw(v1, s3, 12);
                    v1 = 0x42C80000;  // 100.0f
                    sw(v1, s3, 16);
                } else {
                    // 0x00167a10
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x001679d0
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x00167a30
            charge(ctx, 5);
            sw(v0, s0, 40);
            v0 = 1;
            sw(v0, s0, frp::kState);
        L_00167e90:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x167A44u:  // table[1]: state 1: portraits to screen 3
            // 0x00167a44
            charge(ctx, 13);
            sh(zero, s0, 16);
            lw(a0, gp, g::kCampPcKani);  // 0x7CDF54
            a1 = 3;
            jal(ctx, 0x167A50u, gen::fn_sub_121DE0_00121de0);  // [H_Camp_PcKaniSetScreen]
            lw(a0, gp, g::kCampPersonaKani);  // 0x7CDF58
            a1 = 3;
            jal(ctx, 0x167A60u, gen::fn_sub_122710_00122710);  // [H_Camp_PersonaKaniSetScreen]
            v0 = 2;
            sw(v0, s0, frp::kState);
            goto L_00167e90;
        case 0x167A78u:  // table[2]: state 2: the panel reveal; input
            // 0x00167a78
            charge(ctx, 7);
            s1 = 0;
            lw(v0, s0, 40);
            lw(t0, v0, 60);
            lw(v1, t0, 0);
            v0 = 3;
            if (v1 == v0) {
                // 0x00167a94
                charge(ctx, 3);
                lw(v0, t0, 4);
                if (v0 != 0) {
                    // 0x00167aa0
                    charge(ctx, 7);
                    lwc1(f1, t0, 24);
                    v0 = 0x42700000;  // 60.0f
                    mtc1(v0, f2);
                    c_eq_s(f2, f1);
                    if (!cond(ctx)) {
                        // 0x00167abc
                        charge(ctx, 13);
                        lwc1(f0, t0, 20);
                        sub_s(f0, f1, f0);
                        swc1(f0, t0, 24);
                        lwc1(f1, t0, 20);
                        v0 = 0x40A00000;  // 5.0f
                        mtc1(v0, f0);
                        add_s(f0, f1, f0);
                        swc1(f0, t0, 20);
                        lwc1(f0, t0, 24);
                        c_lt_s(f0, f2);
                        if (cond(ctx)) {
                            // 0x00167af0
                            charge(ctx, 1);
                            swc1(f2, t0, 24);
                        }
                    }
                    // 0x00167af4
                    charge(ctx, 11);
                    lwc1(f12, t0, 16);
                    lw(a0, t0, 12);
                    v0 = 0x4FA40000;
                    a1 = v0 | 0xFF19;
                    lwc1(f13, t0, 24);
                    lwc1(f14, t0, 28);
                    a2 = 640;
                    a3 = a2;
                    lw(t0, t0, 40);
                    jal(ctx, 0x167B18u, gen::fn_sub_114450_00114450);  // [nine-slice window] / the persona picture
                }
            }
            // 0x00167b20
            charge(ctx, 3);
            lh(v0, s0, 18);
            if (v0 != 0) {
                // 0x00167b8c
                charge(ctx, 4);
                lh(v0, s0, 12);
                v1 = 255;
                if (v0 == v1) {
                    // 0x00167bc4
                    charge(ctx, 1);
                    s1 = 1;
                } else {
                    // 0x00167b9c
                    charge(ctx, 7);
                    v0 = addiu(v0, 10);
                    sh(v0, s0, 12);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    at = slti(v0, 256);
                    if (at == 0) {
                        // 0x00167bb8
                        charge(ctx, 3);
                        sh(v1, s0, 12);
                    }
                }
                // 0x00167bc8
                charge(ctx, 15);
                sw(zero, sp, 0x5C);
                sw(zero, sp, 0x58);
                lh(v1, s0, 12);
                v0 = 255;
                s2 = subu(v0, v1);
                lhu(a0, s0, frp::kPc);
                jal(ctx, 0x167BE0u, gen::fn_datPersonaGetByPcId_00174800);
                v1 = 0x42C80000;  // 100.0f
                mtc1(v1, f12);
                ld(a0, sp, 0x58);
                a1 = v0;
                a2 = s2;
                jal(ctx, 0x167BFCu, gen::fn_sub_12AC60_0012ac60);
            } else {
                // 0x00167b2c
                charge(ctx, 4);
                lh(v1, s0, 16);
                v0 = 20;
                if (v1 == v0) {
                    // 0x00167b4c
                    charge(ctx, 1);
                    s1 = 1;
                } else {
                    // 0x00167b3c
                    charge(ctx, 4);
                    v0 = addiu(v1, 1);
                    sh(v0, s0, 16);
                }
                // 0x00167b50
                charge(ctx, 15);
                sw(zero, sp, 0x5C);
                sw(zero, sp, 0x58);
                lh(s2, s0, 16);
                lhu(a0, s0, frp::kPc);
                jal(ctx, 0x167B60u, gen::fn_datPersonaGetByPcId_00174800);
                v1 = 0x42C80000;  // 100.0f
                mtc1(v1, f12);
                ld(a0, sp, 0x58);
                a1 = v0;
                a2 = s2;
                jal(ctx, 0x167B7Cu, gen::fn_sub_129B30_00129b30);
            }
            // 0x00167c04
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x00167c0c
                charge(ctx, 3);
                lh(v0, s0, 28);
                if (v0 != 0) {
                    // 0x00167ca4
                    charge(ctx, 5);
                    v0 = 0x7E0000;
                    lhu(v1, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                    v0 = v1 & 0x20;  // cancel
                    if (v0 == 0) {
                        // 0x00167ce0
                        charge(ctx, 4);
                        v0 = v1 & 0x8000;
                        v0 = sltu(0, v0);
                        if (v0 == 0) {
                            // 0x00167cf0
                            charge(ctx, 4);
                            v0 = 0x7E0000;
                            lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                            v0 = v0 & 0x8000;  // previous page
                            v0 = sltu(0, v0);
                        }
                        // 0x00167d00
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x00167d30
                            charge(ctx, 3);
                            v0 = v1 & 0x8;
                            if (v0 == 0) {
                                // 0x00167d64
                                charge(ctx, 3);
                                v0 = v1 & 0x4;
                                if (v0 != 0) {
                                    // 0x00167d70
                                    charge(ctx, 10);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x167D80u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    v0 = 3;
                                    sw(v0, s0, 20);
                                }
                            } else {
                                // 0x00167d3c
                                charge(ctx, 10);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x167D4Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                v0 = 2;
                                sw(v0, s0, 20);
                            }
                        } else {
                            // 0x00167d08
                            charge(ctx, 10);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x167D18u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                            v0 = 1;
                            sw(v0, s0, 20);
                        }
                    } else {
                        // 0x00167cb8
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 2;
                        jal(ctx, 0x167CC8u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = si(-1);
                        sw(v0, s0, 20);
                    }
                } else {
                    // 0x00167c18
                    charge(ctx, 5);
                    v0 = 0x7E0000;
                    lhu(v1, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                    v0 = v1 & 0x20;  // cancel
                    if (v0 == 0) {
                        // 0x00167c54
                        charge(ctx, 4);
                        v0 = v1 & 0x8000;
                        v0 = sltu(0, v0);
                        if (v0 == 0) {
                            // 0x00167c64
                            charge(ctx, 4);
                            v0 = 0x7E0000;
                            lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                            v0 = v0 & 0x8000;  // previous page
                            v0 = sltu(0, v0);
                        }
                        // 0x00167c74
                        charge(ctx, 2);
                        if (v0 != 0) {
                            // 0x00167c7c
                            charge(ctx, 10);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x167C8Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                            v0 = 1;
                            sw(v0, s0, 20);
                        }
                    } else {
                        // 0x00167c2c
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 2;
                        jal(ctx, 0x167C3Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = si(-1);
                        sw(v0, s0, 20);
                    }
                }
            }
            goto L_00167e90;
        case 0x167D98u:  // table[3]: state 3: fade out (close)
            // 0x00167d98
            charge(ctx, 7);
            lh(v0, s0, 12);
            v0 = addiu(v0, -25);
            sh(v0, s0, 12);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            if (i64(v1) >= 0) {
                // 0x00167dc0
                charge(ctx, 14);
                swc1(f0, sp, 0x5C);
                swc1(f0, sp, 0x58);
                v0 = 255;
                s1 = subu(v0, v1);
                lhu(a0, s0, frp::kPc);
                jal(ctx, 0x167DD4u, gen::fn_datPersonaGetByPcId_00174800);
                v1 = 0x42C80000;  // 100.0f
                mtc1(v1, f12);
                ld(a0, sp, 0x58);
                a1 = v0;
                a2 = s1;
                jal(ctx, 0x167DF0u, gen::fn_sub_12AC60_0012ac60);
            L_00167df8:
                charge(ctx, 17);
                sw(zero, sp, 0x5C);
                sw(zero, sp, 0x58);
                lhu(a0, s0, frp::kPc);
                jal(ctx, 0x167E04u, gen::fn_datPersonaGetByPcId_00174800);
                v1 = 0x42C80000;  // 100.0f
                mtc1(v1, f12);
                ld(a0, sp, 0x58);
                a1 = v0;
                a2 = 0;
                jal(ctx, 0x167E20u, gen::fn_sub_12AC60_0012ac60);
                sh(zero, s0, 16);
                v0 = 5;
                sw(v0, s0, frp::kState);
                goto L_00167e90;
            }
            // 0x00167db4
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x167DF8u:  // table[4]: state 4: page switch
            goto L_00167df8;
        case 0x167E3Cu:  // table[5]: state 5: slide out
            // 0x00167e3c
            charge(ctx, 4);
            lh(v1, s0, 16);
            v0 = 10;
            if (v1 != v0) {
                // 0x00167e58
                charge(ctx, 14);
                v0 = addiu(v1, 1);
                sh(v0, s0, 16);
                s1 = dsll32(v0, 16);
                s1 = dsra32(s1, 16);
                lhu(a0, s0, frp::kPc);
                jal(ctx, 0x167E6Cu, gen::fn_datPersonaGetByPcId_00174800);
                v1 = 0x42C80000;  // 100.0f
                mtc1(v1, f12);
                ld(a0, sp, 0x58);
                a1 = v0;
                a2 = s1;
                jal(ctx, 0x167E88u, gen::fn_sub_12A560_0012a560);
                goto L_00167e90;
            }
            // 0x00167e4c
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00167e94 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x60);
        return;
    }
    goto L_00167e90;
}

}  // namespace p3fes::game
