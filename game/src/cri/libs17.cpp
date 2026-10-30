// Phase 5 slice libs17 (100 functions): CRI middleware leaves around Sofdec.
//   * the ADX-side meter table (16 x 48-byte records at 0x7833A8: open / close / take a record, the scan loop, getters);
//   * SFD handle setters and getters on the header object (+14000), the profile read-out, the frame-interval tracker,
//     the time sources (vsync, external callback, none), the drop-frame time codes, the pause hook and the end-time test;
//   * the SFX frame converter: the callback record, the plane walks, the composition / mode tables, the alpha copy,
//     the conversion work split, the Z object (SFXZ / ZMHDR / ZMVFRM tags), the Z ramp and Z tables, the z-clip;
//   * a few tails, empty functions and constant returns.
// Made by p3fes_handgen from SLUS_216.21 and symbols/: every body keeps the recompiled body's registers, frame, spills,
// $ra links, cycle charges and check points (game/include/p3fes/game/hg_cpu.h). The readability pass adds a role
// comment per function ([proposed name] where the binary's own error strings name it; symbols/deltas/libs17.sym) and
// libs17.h's record offsets; tests/game/test_libs17.cpp pairs every body with its recompiled body.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs17.h"

namespace p3fes::recomp_gen {
void fn_WTLS_get_table_2_0059fd60(p3fes::EEContext&);
void fn__ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_1_00535da0(p3fes::EEContext&);
void fn___divdi3_0052eeb0(p3fes::EEContext&);
void fn___errno_15_005a0bf0(p3fes::EEContext&);
void fn___muldi3_0052ea78(p3fes::EEContext&);
void fn_logl_9_0056def8(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_strtoul_00525e98(p3fes::EEContext&);
void fn_sub_5356B8_005356b8(p3fes::EEContext&);
void fn_sub_535708_00535708(p3fes::EEContext&);
void fn_sub_535758_00535758(p3fes::EEContext&);
void fn_sub_5358D8_005358d8(p3fes::EEContext&);
void fn_sub_535D18_00535d18(p3fes::EEContext&);
void fn_sub_535D40_00535d40(p3fes::EEContext&);
void fn_sub_535DB0_00535db0(p3fes::EEContext&);
void fn_sub_535DB8_00535db8(p3fes::EEContext&);
void fn_sub_539818_00539818(p3fes::EEContext&);
void fn_sub_539830_00539830(p3fes::EEContext&);
void fn_sub_563E68_00563e68(p3fes::EEContext&);
void fn_sub_56DE28_0056de28_at_0056de78(p3fes::EEContext&);
void fn_sub_56DED0_0056ded0(p3fes::EEContext&);
void fn_sub_56F4B8_0056f4b8(p3fes::EEContext&);
void fn_sub_57BAF0_0057baf0(p3fes::EEContext&);
void fn_sub_589FD0_00589fd0(p3fes::EEContext&);
void fn_sub_58BE40_0058be40(p3fes::EEContext&);
void fn_sub_58C060_0058c060(p3fes::EEContext&);
void fn_sub_58C100_0058c100(p3fes::EEContext&);
void fn_sub_58C118_0058c118(p3fes::EEContext&);
void fn_sub_596B68_00596b68(p3fes::EEContext&);
void fn_sub_597A18_00597a18(p3fes::EEContext&);
void fn_sub_598D90_00598d90(p3fes::EEContext&);
void fn_sub_598E18_00598e18(p3fes::EEContext&);
void fn_sub_598E88_00598e88(p3fes::EEContext&);
void fn_sub_598EE8_00598ee8(p3fes::EEContext&);
void fn_sub_598FD8_00598fd8(p3fes::EEContext&);
void fn_sub_599020_00599020(p3fes::EEContext&);
void fn_sub_5990A8_005990a8(p3fes::EEContext&);
void fn_sub_599240_00599240(p3fes::EEContext&);
void fn_sub_599408_00599408(p3fes::EEContext&);
void fn_sub_599590_00599590(p3fes::EEContext&);
void fn_sub_599808_00599808(p3fes::EEContext&);
void fn_sub_599AA0_00599aa0(p3fes::EEContext&);
void fn_sub_599B40_00599b40(p3fes::EEContext&);
void fn_sub_599CC8_00599cc8(p3fes::EEContext&);
void fn_sub_599EC8_00599ec8(p3fes::EEContext&);
void fn_sub_599F28_00599f28(p3fes::EEContext&);
void fn_sub_599FA0_00599fa0(p3fes::EEContext&);
void fn_sub_599FB0_00599fb0(p3fes::EEContext&);
void fn_sub_59A028_0059a028(p3fes::EEContext&);
void fn_sub_59A168_0059a168(p3fes::EEContext&);
void fn_sub_59A2E0_0059a2e0(p3fes::EEContext&);
void fn_sub_59A340_0059a340(p3fes::EEContext&);
void fn_sub_59A360_0059a360(p3fes::EEContext&);
void fn_sub_59A458_0059a458(p3fes::EEContext&);
void fn_sub_59A508_0059a508(p3fes::EEContext&);
void fn_sub_59A578_0059a578(p3fes::EEContext&);
void fn_sub_59A6F0_0059a6f0(p3fes::EEContext&);
void fn_sub_59A778_0059a778(p3fes::EEContext&);
void fn_sub_59A7E0_0059a7e0(p3fes::EEContext&);
void fn_sub_59A860_0059a860(p3fes::EEContext&);
void fn_sub_59A910_0059a910(p3fes::EEContext&);
void fn_sub_59AA10_0059aa10(p3fes::EEContext&);
void fn_sub_59AAE8_0059aae8(p3fes::EEContext&);
void fn_sub_59AB80_0059ab80(p3fes::EEContext&);
void fn_sub_59AC28_0059ac28(p3fes::EEContext&);
void fn_sub_59AC88_0059ac88(p3fes::EEContext&);
void fn_sub_59ACF0_0059acf0(p3fes::EEContext&);
void fn_sub_59AD40_0059ad40(p3fes::EEContext&);
void fn_sub_59B198_0059b198(p3fes::EEContext&);
void fn_sub_59B300_0059b300(p3fes::EEContext&);
void fn_sub_59B398_0059b398(p3fes::EEContext&);
void fn_sub_59B3A0_0059b3a0(p3fes::EEContext&);
void fn_sub_59B3A8_0059b3a8(p3fes::EEContext&);
void fn_sub_59B458_0059b458(p3fes::EEContext&);
void fn_sub_59BE98_0059be98(p3fes::EEContext&);
void fn_sub_59C3B8_0059c3b8(p3fes::EEContext&);
void fn_sub_59C418_0059c418(p3fes::EEContext&);
void fn_sub_59CC58_0059cc58(p3fes::EEContext&);
void fn_sub_59CC60_0059cc60(p3fes::EEContext&);
void fn_sub_59CC68_0059cc68(p3fes::EEContext&);
void fn_sub_59CC70_0059cc70(p3fes::EEContext&);
void fn_sub_59CC90_0059cc90(p3fes::EEContext&);
void fn_sub_59CCB0_0059ccb0(p3fes::EEContext&);
void fn_sub_59CCD0_0059ccd0(p3fes::EEContext&);
void fn_sub_59CCF0_0059ccf0(p3fes::EEContext&);
void fn_sub_59CF98_0059cf98(p3fes::EEContext&);
void fn_sub_59E918_0059e918(p3fes::EEContext&);
void fn_sub_59E960_0059e960(p3fes::EEContext&);
void fn_sub_59E998_0059e998(p3fes::EEContext&);
void fn_sub_59E9D0_0059e9d0(p3fes::EEContext&);
void fn_sub_59EA18_0059ea18(p3fes::EEContext&);
void fn_sub_59EA50_0059ea50(p3fes::EEContext&);
void fn_sub_59EA80_0059ea80(p3fes::EEContext&);
void fn_sub_59EAF8_0059eaf8(p3fes::EEContext&);
void fn_sub_59EBD0_0059ebd0(p3fes::EEContext&);
void fn_sub_59EC08_0059ec08(p3fes::EEContext&);
void fn_sub_59ED78_0059ed78(p3fes::EEContext&);
void fn_sub_59EE18_0059ee18(p3fes::EEContext&);
void fn_sub_59EE38_0059ee38(p3fes::EEContext&);
void fn_sub_59EF08_0059ef08(p3fes::EEContext&);
void fn_sub_59EF28_0059ef28(p3fes::EEContext&);
void fn_sub_59EF48_0059ef48(p3fes::EEContext&);
void fn_sub_59EF68_0059ef68(p3fes::EEContext&);
void fn_sub_59EF90_0059ef90(p3fes::EEContext&);
void fn_sub_59F008_0059f008(p3fes::EEContext&);
void fn_sub_59F080_0059f080(p3fes::EEContext&);
void fn_sub_59F0C8_0059f0c8(p3fes::EEContext&);
void fn_sub_59F320_0059f320(p3fes::EEContext&);
void fn_sub_59F3D8_0059f3d8(p3fes::EEContext&);
void fn_sub_59F518_0059f518(p3fes::EEContext&);
void fn_sub_59F6C8_0059f6c8(p3fes::EEContext&);
void fn_sub_59F740_0059f740(p3fes::EEContext&);
void fn_sub_59F7E8_0059f7e8(p3fes::EEContext&);
void fn_sub_59F8F8_0059f8f8(p3fes::EEContext&);
void fn_sub_59F968_0059f968(p3fes::EEContext&);
void fn_sub_59FD10_0059fd10(p3fes::EEContext&);
void fn_sub_59FDC0_0059fdc0(p3fes::EEContext&);
void fn_sub_59FDF0_0059fdf0(p3fes::EEContext&);
void fn_sub_59FE50_0059fe50(p3fes::EEContext&);
void fn_sub_59FE60_0059fe60(p3fes::EEContext&);
void fn_sub_59FF48_0059ff48(p3fes::EEContext&);
void fn_sub_59FF60_0059ff60(p3fes::EEContext&);
void fn_sub_59FF78_0059ff78(p3fes::EEContext&);
void fn_sub_59FF98_0059ff98(p3fes::EEContext&);
void fn_sub_59FFB0_0059ffb0(p3fes::EEContext&);
void fn_sub_59FFC8_0059ffc8(p3fes::EEContext&);
void fn_sub_5A0008_005a0008(p3fes::EEContext&);
void fn_sub_5A00B0_005a00b0(p3fes::EEContext&);
void fn_sub_5A0188_005a0188(p3fes::EEContext&);
void fn_sub_5A01B0_005a01b0(p3fes::EEContext&);
void fn_sub_5A0208_005a0208(p3fes::EEContext&);
void fn_sub_5A0220_005a0220(p3fes::EEContext&);
void fn_sub_5A0250_005a0250(p3fes::EEContext&);
void fn_sub_5A02C0_005a02c0(p3fes::EEContext&);
void fn_sub_5A03B0_005a03b0(p3fes::EEContext&);
void fn_sub_5A04F0_005a04f0(p3fes::EEContext&);
void fn_sub_5A0608_005a0608(p3fes::EEContext&);
void fn_sub_5A0688_005a0688(p3fes::EEContext&);
void fn_sub_5A07E0_005a07e0(p3fes::EEContext&);
void fn_sub_5A0830_005a0830(p3fes::EEContext&);
void fn_sub_5A0B00_005a0b00(p3fes::EEContext&);
void fn_sub_5A0B68_005a0b68(p3fes::EEContext&);
void fn_sub_5A0BB0_005a0bb0(p3fes::EEContext&);
void fn_sub_5A1088_005a1088(p3fes::EEContext&);
void fn_sub_5A10E8_005a10e8(p3fes::EEContext&);
void fn_sub_5A1778_005a1778(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace libs17;

// 0x005356B8 sub_5356B8 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Meter table: open a reference (0x7833A0); the first one clears the 16 x 48-byte records at 0x7833A8 (memset 768).
//   Returns the new count.
void sub_5356B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005356b8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x780000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 13216);  // &0x7833A0
    lw(v0, s0, 0);  // 0x7833A0
    sd(ra, sp, 0x8);
    if (v0 == 0) {
        // 0x005356d4
        charge(ctx, 6);
        a0 = 0x780000;
        a1 = 0;
        a0 = addiu(a0, 13224);  // &0x7833A8
        a2 = 768;
        jal(ctx, 0x5356E0u, gen::fn_memset_00521408);
        lw(v0, s0, 0);
    }
    // 0x005356ec (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = addiu(v0, 1);
    ld(ra, sp, 0x8);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00535708 sub_535708 -- 76 bytes; frame 0x10: ra sp+0x0
// Meter table: drop a reference (0x7833A0); the last one clears the 16 records (tail call to memset).
void sub_535708(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00535708
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x780000;
    sd(ra, sp, 0x0);
    v1 = addiu(v1, 13216);  // &0x7833A0
    lw(v0, v1, 0);  // 0x7833A0
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x7833A0
    if (v0 != 0) {
        // 0x00535748
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00535728
    charge(ctx, 7);
    a0 = 0x780000;
    ld(ra, sp, 0x0);
    a1 = 0;
    a0 = addiu(a0, 13224);  // &0x7833A8
    a2 = 768;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x00535758 sub_535758 -- 300 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// Meter table: take the first free record (state byte 0) of the 16 under the ADX lock (sub_539818 / sub_539830):
//   channel count $a0 (+2), per channel $a1[i] (+4 + 4i) and $a2[i] (+12 + 4i) and a zero peak (+20 + 4i); +28 = $a0,
//   rate 44100 (+32), two 0.1f decay values (+36, +40), +44 = 0, state 1 (+0), +1 = 0. Returns the record, 0 when all 16
//   are taken.
void sub_535758(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00535758
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = 0;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    s4 = 0x780000;
    sd(ra, sp, 0x28);
    v1 = addiu(s4, 13224);  // &0x7833A8
    lb(v0, v1, 0);  // 0x7833A8
    s3 = a1;
    if (v0 != 0) {
        // 0x00535794
        charge(ctx, 1);
        s0 = addiu(s0, 1);
        for (;;) {
            // 0x00535798
            charge(ctx, 3);
            v0 = slti(s0, 16);
            v1 = addiu(v1, 48);
            if (v0 != 0) {
                // 0x005357a4
                charge(ctx, 6);
                lb(v0, v1, 0);
                if (v0 != 0) {
                    s0 = addiu(s0, 1);
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x005357bc
    charge(ctx, 3);
    v1 = 16;
    v0 = 0;
    if (s0 != v1) {
        // 0x005357c8
        charge(ctx, 10);
        jal(ctx, 0x5357C8u, gen::fn_sub_539818_00539818);
        v0 = sll(s0, 1);
        v0 = addu(v0, s0);
        v1 = addiu(s4, 13224);
        v0 = sll(v0, 4);
        t0 = 0;
        s0 = addu(v0, v1);
        sb(s1, s0, 2);
        if (i64(s1) > 0) {
            // 0x005357f0
            charge(ctx, 2);
            t1 = addiu(s0, 12);
            a3 = addiu(s0, 4);
            for (;;) {
                // 0x005357f8
                charge(ctx, 13);
                v1 = sll(t0, 2);
                t0 = addiu(t0, 1);
                v0 = addu(v1, s3);
                a2 = addu(v1, s2);
                lw(a0, v0, 0);
                a1 = slt(t0, s1);
                v1 = addu(t1, v1);
                sw(zero, a3, 16);
                sw(a0, a3, 0);
                a3 = addiu(a3, 4);
                lw(v0, a2, 0);
                sw(v0, v1, 0);
                if (a1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0053582c
        charge(ctx, 14);
        at = 0x3DCC0000;
        at = at | 0xCCCC;
        mtc1(at, f0);
        v0 = 0xAC44;
        v1 = 1;
        sw(v0, s0, 32);
        sw(s1, s0, 28);
        swc1(f0, s0, 40);
        sb(v1, s0, 0);
        sb(zero, s0, 1);
        sw(zero, s0, 44);
        link(ctx, 0x535858u);  // $ra first: the delay slot below depends on it
        swc1(f0, s0, 36);
        call(ctx, gen::fn_sub_539830_00539830);
        v0 = s0;
    }
    // 0x00535864 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x005358D8 sub_5358D8 -- 8 bytes; leaf frame (no stack)
// Meter record: the signed state byte +1 (2 = running, see sub_535D18).
void sub_5358D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005358d8
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, meter::kRun);
}

// 0x00535D40 sub_535D40 -- 96 bytes; frame 0x20: ra sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// Meter table: runs sub_535D18 (the peak scan) on every record whose state byte is 1, all 16 records.
void sub_535D40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00535d40
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x780000;
    sd(ra, sp, 0x18);
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 13224);  // &0x7833A8
    sd(s1, sp, 0x8);
    s1 = 15;
    sd(s2, sp, 0x10);
    s2 = 1;
    for (;;) {
        // 0x00535d68
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x00535d74
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x535D74u, gen::fn_sub_535D18_00535d18);
            s1 = addiu(s1, -1);
        }
        // 0x00535d80
        charge(ctx, 2);
        s0 = addiu(s0, 48);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00535d88
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00535DA0 _ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_1 -- 8 bytes; leaf frame (no stack)
// A 32-bit getter: the word at +20 (FLIRT names it std::streambuf::eback).
void _ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_1(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00535da0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 20);
}

// 0x00535DB0 sub_535DB0 -- 8 bytes; leaf frame (no stack)
// Meter record: the word at +32 (the sample rate sub_535758 sets to 44100).
void sub_535DB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00535db0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, meter::kRate);
}

// 0x00535DB8 sub_535DB8 -- 8 bytes; leaf frame (no stack)
// Meter record: stores $f12 at +36 (the first decay value).
void sub_535DB8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    Fpr f12{ctx, 12};
    // 0x00535db8
    enter(ctx, 2);  // entry check point + this block's cycles
    swc1(f12, a0, meter::kDecay0);
}

// 0x00598D90 sub_598D90 -- 132 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// SFD handle setter: after the handle check (sub_58C060; error -16776870), the header object (+14000) gets +3528 = $a1
//   and +3532 = $a2, then sub_599020. No header object: returns 0, nothing stored.
void sub_598D90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598d90
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a1;
    jal(ctx, 0x598DACu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    a1 = a1 | 0x15A;
    if (v0 != 0) {
        // 0x00598dc4
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00598de0
    charge(ctx, 3);
    lw(v1, s0, 14000);
    a0 = s0;
    if (v1 != 0) {
        // 0x00598dec
        charge(ctx, 4);
        sw(s1, v1, 3532);
        link(ctx, 0x598DF0u);  // $ra first: the delay slot below depends on it
        sw(s2, v1, 3528);
        call(ctx, gen::fn_sub_599020_00599020);
        v0 = 0;
    }
    // 0x00598dfc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00598E18 sub_598E18 -- 112 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// SFD handle setter: handle check (error -16776869), header object (+14000) +3536 = $a1, then sub_599020.
void sub_598E18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598e18
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x598E2Cu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x00598e40
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x15B;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00598e58
    charge(ctx, 3);
    lw(v1, s0, 14000);
    if (v1 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00598e64
        charge(ctx, 5);
        sw(s1, v1, 3536);
        a0 = s0;
        jal(ctx, 0x598E68u, gen::fn_sub_599020_00599020);
        v0 = 0;
        ld(s0, sp, 0x0);
    }
    // 0x00598e78 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00598E88 sub_598E88 -- 96 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// SFD handle setter: handle check (error -16776868), header object (+14000) +3540 = $a1.
void sub_598E88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598e88
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x598E9Cu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x00598eb0
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x15C;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00598ec8
    charge(ctx, 3);
    lw(a0, s0, 14000);
    if (a0 != 0) {
        sw(s1, a0, 3540);
    }
    // 0x00598ed4
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00598EE8 sub_598EE8 -- 240 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s4 sp+0x20, s0 sp+0x0, s3 sp+0x18, ra sp+0x28
// SFD header refresh: unless parameter 49 is set (sub_589FD0): the header object's start frame +3500 (while <= 0) =
//   the transfer slot's frame count (sub_598FD8; -1 = none) plus +3540 (skipped when +3540 is negative; 0 when handle
//   +14008 is -3); its time +3504 / +3508 (while +3504 <= 0) = handle +3560 / +3564 when +3560 > 0; sub_599020 when
//   either changed.
void sub_598EE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00598ee8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s4, sp, 0x20);
    s4 = addiu(s2, 3524);
    sd(s0, sp, 0x0);
    s1 = addiu(s2, 14004);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x28);
    link(ctx, 0x598F10u);  // $ra first: the delay slot below depends on it
    lw(s0, s2, 14000);
    call(ctx, gen::fn_sub_589FD0_00589fd0);
    if (v0 != 0) {
        ld(s0, sp, 0x0);
        // 0x00598fbc (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x00598f20
    charge(ctx, 3);
    lw(v0, s0, 3500);
    s3 = 0;
    if (i64(v0) <= 0) {
        // 0x00598f2c
        charge(ctx, 4);
        lw(v1, s1, 4);
        v0 = si(-3);
        s1 = 0;
        if (v1 != v0) {
            // 0x00598f3c
            charge(ctx, 1);
            lw(s1, s0, 3540);
        }
        // 0x00598f40
        charge(ctx, 2);
        if (i64(s1) >= 0) {
            // 0x00598f48
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x598F48u, gen::fn_sub_598FD8_00598fd8);
            v1 = v0;
            v0 = si(-1);
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = addu(s1, v1);
            if (!cc) {
                // 0x00598f60
                charge(ctx, 2);
                s3 = 1;
                sw(v0, s0, 3500);
            }
            goto L_00598f68;
        }
        lw(v0, s0, 3504);
        goto L_00598f6c;
    }
L_00598f68:
    charge(ctx, 1);
    lw(v0, s0, 3504);
L_00598f6c:
    charge(ctx, 2);
    if (i64(v0) <= 0) {
        // 0x00598f74
        charge(ctx, 3);
        lw(v0, s4, 36);
        if (i64(v0) > 0) {
            // 0x00598f80
            charge(ctx, 4);
            sw(v0, s0, 3504);
            s3 = 1;
            lw(v0, s4, 40);
            sw(v0, s0, 3508);
        }
    }
    // 0x00598f90
    charge(ctx, 2);
    a0 = s2;
    if (s3 != 0) {
        // 0x00598f98
        charge(ctx, 8);
        ld(s2, sp, 0x10);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        gen::fn_sub_599020_00599020(ctx);  // tail call
        return;
    }
    // 0x00598fb8
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x00598fbc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00598FD8 sub_598FD8 -- 72 bytes; leaf frame (no stack)
// The frame count of the active stream's transfer slot: handle +8016 + 68 x (the stream record's word +80; record
//   +4880 + 116 x the stream index +8004); a negative count gives -1.
void sub_598FD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00598fd8
    enter(ctx, 18);  // entry check point + this block's cycles
    a1 = addiu(a0, 7984);
    a2 = si(-1);
    lw(v1, a1, 20);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    lw(v1, a0, 4960);
    v0 = sll(v1, 4);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    a1 = addu(a1, v0);
    lw(v0, a1, 32);
    v1 = slti(v0, 0);
    if (v1 != 0) v0 = a2;
}

// 0x005990A8 sub_5990A8 -- 20 bytes; frame 0x10: ra sp+0x0
// A tail call into sub_596B68.
void sub_5990A8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005990a8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_596B68_00596b68(ctx);  // tail call
}

// 0x00599590 sub_599590 -- 288 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// SFD profile read-out: handle check (error -16776934); copies the 224-byte profile (+14016, 7 x 32-byte records) to
//   $a1, then folds records 1..3 into record 0 (sums of the 64-bit word +0 and the word +24, minimum of +8, maximum of
//   +16); a handle in API mode 4 (+76) then runs sub_597A18.
void sub_599590(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599590
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x5995A4u, gen::fn_sub_58C060_0058c060);
    a0 = 0;
    if (v0 != 0) {
        // 0x005995b4
        charge(ctx, 7);
        a1 = lui(0xFF00);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        a1 = a1 | 0x11A;
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x005995d0
    charge(ctx, 3);
    v1 = s0;
    v0 = addiu(s1, 14016);
    a0 = addiu(s1, 14240);
    for (;;) {
        // 0x005995dc
        charge(ctx, 13);
        ld(a1, v0, 0);
        ld(a2, v0, 8);
        ld(a3, v0, 16);
        ld(t0, v0, 24);
        sd(a1, v1, 0);
        sd(a2, v1, 8);
        sd(a3, v1, 16);
        sd(t0, v1, 24);
        v0 = addiu(v0, 32);
        v1 = addiu(v1, 32);
        if (v0 == a0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00599610
    charge(ctx, 4);
    t4 = addiu(s0, 8);
    t2 = 1;
    t3 = t4;
    t1 = addiu(s0, 48);
    for (;;) {
        // 0x00599620
        charge(ctx, 24);
        ld(v1, t1, -16);
        a2 = sll(t2, 5);
        ld(v0, s0, 0);
        a2 = addu(t3, a2);
        lw(a3, t1, 8);
        t2 = addiu(t2, 1);
        v0 = v0 + v1;
        lw(a0, s0, 24);
        sd(v0, s0, 0);
        t0 = slti(t2, 4);
        a0 = addu(a0, a3);
        ld(a1, a2, 0);
        ld(v1, t3, 0);
        sw(a0, s0, 24);
        v0 = slt(a1, v1);
        if (v0 != 0) v1 = a1;
        sd(v1, t4, 0);
        ld(a0, t1, 0);
        t1 = addiu(t1, 32);
        ld(v0, s0, 16);
        v1 = slt(v0, a0);
        if (v1 != 0) v0 = a0;
        sd(v0, s0, 16);
        if (t0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00599680
    charge(ctx, 4);
    lw(v1, s1, 76);
    v0 = 4;
    if (v1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00599690
        charge(ctx, 3);
        a0 = s1;
        jal(ctx, 0x599690u, gen::fn_sub_597A18_00597a18);
        ld(s0, sp, 0x0);
    }
    // 0x0059969c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00599808 sub_599808 -- 8 bytes; leaf frame (no stack)
// An empty function (jr $ra).
void sub_599808(EEContext& ctx) {
    using namespace hg;
    // 0x00599808
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00599AA0 sub_599AA0 -- 156 bytes; leaf frame (no stack)
// Frame-interval tracker on the words +660..+672 of $a0, fed the time $a1: the first time (+660 = -5) is only stored;
//   then the interval since +660, its maximum (+668) and minimum (+672), and the smoothed interval +664 (0x7FFFFFFF =
//   unset: takes the interval; a larger interval at once; a smaller one moves it down by an eighth of the gap, or all
//   the way when that eighth is 0).
void sub_599AA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00599aa0
    enter(ctx, 5);  // entry check point + this block's cycles
    t0 = a0;
    v0 = si(-5);
    lw(a2, t0, 660);
    t2 = a1;
    if (a2 == v0) {
        // 0x00599ab4
        charge(ctx, 2);
        sw(t2, t0, 660);
        return;
    }
    // 0x00599ac0
    charge(ctx, 3);
    a3 = subu(t2, a2);
    a1 = 0x7FFF0000;
    if (a3 == 0) {
        // 0x00599b34 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x00599acc
    charge(ctx, 12);
    lw(v1, t0, 668);
    lw(v0, t0, 672);
    a1 = a1 | 0xFFFF;
    a2 = slt(a3, v1);
    lw(t1, t0, 664);
    a0 = slt(v0, a3);
    if (a2 == 0) v1 = a3;
    if (a0 == 0) v0 = a3;
    sw(t2, t0, 660);
    sw(v1, t0, 668);
    sw(v0, t0, 672);
    if (t1 != a1) {
        // 0x00599afc
        charge(ctx, 3);
        v0 = slt(a3, t1);
        if (v0 == 0) {
            sw(a3, t0, 664);
            // 0x00599b34 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        // 0x00599b08
        charge(ctx, 7);
        v0 = subu(t1, a3);
        a0 = addiu(v0, 7);
        v1 = slti(v0, 0);
        if (v1 != 0) v0 = a0;
        v0 = sra(v0, 3);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = subu(t1, v0);
        if (cc) {
            goto L_00599b30;
        }
        // 0x00599b24
        charge(ctx, 2);
        sw(v0, t0, 664);
        return;
    }
L_00599b30:
    charge(ctx, 1);
    sw(a3, t0, 664);
    // 0x00599b34 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00599B40 sub_599B40 -- 60 bytes; leaf frame (no stack)
// Frame-interval tracker: the next limit for the time $a1: base +660 + smoothed +664 while $a1 is before it; else base
//   + the maximum +668 while $a1 is before that; else 0x7FFFFFFF.
void sub_599B40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00599b40
    enter(ctx, 9);  // entry check point + this block's cycles
    a2 = a1;
    lw(a1, a0, 660);
    lw(v0, a0, 664);
    lw(v1, a0, 668);
    v0 = addu(a1, v0);
    a0 = slt(a2, v0);
    a1 = addu(a1, v1);
    v1 = v0;
    if (a0 == 0) {
        // 0x00599b64
        charge(ctx, 4);
        v1 = 0x7FFF0000;
        v0 = slt(a2, a1);
        v1 = v1 | 0xFFFF;
        if (v0 != 0) v1 = a1;
    }
    // 0x00599b74 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = v1;
}

// 0x00599EC8 sub_599EC8 -- 96 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The decode time in $a1's units: the 64-bit time +344 (negative: -1) x $a1 / 90,000 (the MPEG clock, __muldi3 /
//   __divdi3); stores the time at 0x7B47C0 and the result at 0x7B47C8.
void sub_599EC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599ec8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    v0 = si(-1);
    sd(ra, sp, 0x8);
    ld(s0, a0, 344);
    a0 = s0;
    if (i64(s0) >= 0) {
        // 0x00599ee4
        charge(ctx, 13);
        jal(ctx, 0x599EE4u, gen::fn___muldi3_0052ea78);
        a1 = 0x10000;
        a1 = a1 | 0x5F90;
        a0 = v0;
        jal(ctx, 0x599EF4u, gen::fn___divdi3_0052eeb0);
        v1 = 0x7B0000;
        a0 = dsll32(v0, 0);
        a0 = dsra32(a0, 0);
        a1 = 0x7B0000;
        sd(s0, v1, 18368);  // 0x7B47C0
        v0 = a0;
        sw(a0, a1, 18376);  // 0x7B47C8
    }
    // 0x00599f18 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00599F28 sub_599F28 -- 120 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The time in the unit $a1 (sub_57BAF0): the time record +316 / +320 when its flag +280 is set, else +272 / +276 (a
//   negative time: -1); the flag to *$a2; the time and result also go to 0x7B47CC / 0x7B47D0.
void sub_599F28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599f28
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = addiu(a0, 280);
    sd(s0, sp, 0x0);
    a0 = addiu(a0, 236);
    sd(ra, sp, 0x8);
    lw(v0, v1, 0);
    sw(v0, a2, 0);
    if (v0 != 0) {
        // 0x00599f48
        charge(ctx, 3);
        lw(a2, v1, 40);
        lw(s0, v1, 36);
        goto L_00599f78;
    }
    // 0x00599f58
    charge(ctx, 3);
    lw(v0, a0, 36);
    s0 = v0;
    if (i64(v0) < 0) {
        // 0x00599f70
        charge(ctx, 2);
        v0 = si(-1);
    } else {
        // 0x00599f64
        charge(ctx, 2);
        lw(a2, a0, 40);
    L_00599f78:
        charge(ctx, 6);
        a0 = s0;
        jal(ctx, 0x599F78u, gen::fn_sub_57BAF0_0057baf0);
        v1 = 0x7B0000;
        a0 = 0x7B0000;
        sw(s0, v1, 18380);  // 0x7B47CC
        sw(v0, a0, 18384);  // 0x7B47D0
    }
    // 0x00599f90 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00599FA0 sub_599FA0 -- 12 bytes; leaf frame (no stack)
// Stores $a1 at +324 and $a2 at +328.
void sub_599FA0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00599fa0
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a2, a0, 328);
    sw(a1, a0, 324);
}

// 0x00599FB0 sub_599FB0 -- 116 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Get-time entry: handle check (error -16776927), then sub_59A028.
void sub_599FB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599fb0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a1;
    jal(ctx, 0x599FCCu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = s0;
    a2 = s1;
    a1 = a1 | 0x121;
    if (v0 == 0) {
        // 0x0059a008
        charge(ctx, 7);
        a1 = s2;
        ld(s2, sp, 0x10);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_59A028_0059a028(ctx);  // tail call
        return;
    }
    // 0x00599fe8
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    a0 = 0;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0059A2E0 sub_59A2E0 -- 92 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Time source 'vsync': when the time is valid (sub_59A458), *$a1 = the time record's +680 and *$a2 = the rate at
//   0x7B4728; returns 0.
void sub_59A2E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a2e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x59A2FCu, gen::fn_sub_59A458_0059a458);
    s0 = addiu(s0, 3376);
    if (v0 != 0) {
        // 0x0059a30c
        charge(ctx, 6);
        lw(v1, s0, 680);
        a0 = 0x7B0000;
        v0 = 0;
        sw(v1, s1, 0);
        lw(v1, a0, 18216);  // 0x7B4728
        sw(v1, s2, 0);
    }
    // 0x0059a324 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059A340 sub_59A340 -- 32 bytes; frame 0x10: ra sp+0x0
// Time source 'none': the validity check (sub_59A458) only; returns 0.
void sub_59A340(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a340
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x59A348u, gen::fn_sub_59A458_0059a458);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x0059A360 sub_59A360 -- 248 bytes; frame 0x40: s1 sp+0x18, s3 sp+0x28, s4 sp+0x30, s0 sp+0x10, s2 sp+0x20, ra sp+0x38
// Time source 'external': when the time is valid and the callback +4100 is set, calls it (jalr; +4120, &time, &unit),
//   adds the time step to +4108 (wrapping by +4116 + 1 when the counter goes back) while the time runs (sub_599CC8) and
//   the last time +4104 is set (not -5), keeps the last time / unit (+4104 / +4112) and returns the callback's result;
//   *$a1 = +4108, *$a2 = the unit. No callback: *$a1 = -2, *$a2 = 1, 0.
void sub_59A360(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059a360
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s3, sp, 0x28);
    s3 = a1;
    sd(s4, sp, 0x30);
    sd(s0, sp, 0x10);
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x38);
    s4 = a2;
    jal(ctx, 0x59A384u, gen::fn_sub_59A458_0059a458);
    s0 = addiu(s1, 3376);
    if (v0 != 0) {
        // 0x0059a394
        charge(ctx, 3);
        lw(v0, s0, 724);
        if (v0 != 0) {
            lw(a0, s0, 744);
            // 0x0059a3b8
            charge(ctx, 8);
            a1 = sp;
            a2 = addiu(sp, 0x4);
            jalr(ctx, 0x59A3BCu, v0.u());
            a0 = s1;
            s2 = v0;
            jal(ctx, 0x59A3C8u, gen::fn_sub_599CC8_00599cc8);
            lw(a0, sp, 0x0);
            if (v0 == 0) {
                // 0x0059a418
                charge(ctx, 1);
                lw(v1, sp, 0x4);
            } else {
                // 0x0059a3d8
                charge(ctx, 4);
                lw(v1, s0, 728);
                v0 = si(-5);
                cc = v1 == v0;  // the condition, before the delay slot changes it
                lw(v1, sp, 0x4);
                if (!cc) {
                    // 0x0059a3e8
                    charge(ctx, 4);
                    lw(v0, s0, 728);
                    v1 = subu(a0, v0);
                    if (i64(v1) < 0) {
                        // 0x0059a3f8
                        charge(ctx, 3);
                        lw(v0, s0, 740);
                        v0 = addu(v1, v0);
                        v1 = addiu(v0, 1);
                    }
                    // 0x0059a404
                    charge(ctx, 5);
                    lw(v0, s0, 732);
                    v0 = addu(v0, v1);
                    sw(v0, s0, 732);
                    lw(v1, sp, 0x4);
                }
            }
            // 0x0059a41c
            charge(ctx, 6);
            v0 = s2;
            sw(a0, s0, 728);
            sw(v1, s0, 736);
            lw(a0, s0, 732);
            sw(a0, s3, 0);
            lw(v1, s0, 736);
        } else {
            // 0x0059a3a0
            charge(ctx, 5);
            v0 = si(-2);
            v1 = 1;
            sw(v0, s3, 0);
            v0 = 0;
        }
        // 0x0059a434
        charge(ctx, 1);
        sw(v1, s4, 0);
    }
    // 0x0059a438 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0059A508 sub_59A508 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// SFD handle setter: handle check (error -16776924), +3400 = $a1.
void sub_59A508(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a508
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x59A51Cu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 == 0) {
        // 0x0059a548
        charge(ctx, 6);
        sw(s1, s0, 3400);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059a530
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    a1 = a1 | 0x124;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0059A578 sub_59A578 -- 132 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Time-source selector: handle check (error -16776925), sub_59A860 ($a0, $a1, 4: the callback); a non-zero $a1 also
//   sets parameter 15 to 4 (sub_599240). Returns 0.
void sub_59A578(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a578
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x59A58Cu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    a2 = 4;
    a1 = a1 | 0x123;
    if (v0 != 0) {
        // 0x0059a5a8
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0059a5c0
    charge(ctx, 7);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x59A5C4u, gen::fn_sub_59A860_0059a860);
    a0 = s0;
    a1 = 15;
    a2 = 4;
    if (s1 != 0) {
        // 0x0059a5dc
        charge(ctx, 2);
        jal(ctx, 0x59A5DCu, gen::fn_sub_599240_00599240);
    }
    // 0x0059a5e4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    v0 = 0;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059A6F0 sub_59A6F0 -- 136 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Time update: one handle ($a0 != 0) through sub_59A778, or every open handle of the table 0x7B4774[8]; returns the
//   last non-zero result.
void sub_59A6F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a6f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    if (a0 != 0) {
        // 0x0059a760
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_59A778_0059a778(ctx);  // tail call
        return;
    }
    // 0x0059a708
    charge(ctx, 6);
    v0 = 0x7B0000;
    s2 = 0;
    s1 = addiu(v0, 18292);  // &0x7B4774
    s0 = 7;
    lw(v0, s1, 0);  // 0x7B4774
    for (;;) {
        // 0x0059a720
        charge(ctx, 3);
        s1 = addiu(s1, 4);
        a0 = v0;
        if (v0 != 0) {
            // 0x0059a72c
            charge(ctx, 3);
            jal(ctx, 0x59A72Cu, gen::fn_sub_59A778_0059a778);
            if (v0 != 0) s2 = v0;
        }
        // 0x0059a738
        charge(ctx, 3);
        s0 = addiu(s0, -1);
        if (i64(s0) < 0) {
            break;
        }
        lw(v0, s1, 0);
        backedge(ctx);
    }
    // 0x0059a744
    charge(ctx, 7);
    v0 = s2;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059A778 sub_59A778 -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Time update of one handle: handle check (error -16776918); unless parameter 71 is 1 (sub_599408), sub_59A7E0.
//   Returns 0.
void sub_59A778(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a778
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x59A784u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = s0;
    a1 = a1 | 0x12A;
    if (v0 != 0) {
        // 0x0059a79c
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        a0 = 0;
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0059a7b0
    charge(ctx, 5);
    a1 = 71;
    jal(ctx, 0x59A7B0u, gen::fn_sub_599408_00599408);
    v1 = 1;
    a0 = s0;
    if (v0 != v1) {
        // 0x0059a7c4
        charge(ctx, 2);
        jal(ctx, 0x59A7C4u, gen::fn_sub_59A7E0_0059a7e0);
    }
    // 0x0059a7cc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0059AA10 sub_59AA10 -- 56 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Time code to time at the 60,000 rate (sub_59A910); *$a3 = $a0 (the unit).
void sub_59AA10(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059aa10
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    a0 = 0xEA60;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a3;
    jal(ctx, 0x59AA28u, gen::fn_sub_59A910_0059a910);
    sw(s1, s0, 0);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
}

// 0x0059AAE8 sub_59AAE8 -- 152 bytes; leaf frame (no stack)
// Drop-frame time code ($a1) to time (29.97): frames = 107892 h (+8) + 1798 m (+12, mult1) + 2 (m / 10) + 30 s (+16) +
//   f (+20) + extra (+24), x 1,000, + 500 x the s16 field +30; *$a2 = the time, *$a3 = $a0 (the unit).
void sub_59AAE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14};
    // 0x0059aae8
    enter(ctx, 12);  // entry check point + this block's cycles
    lw(t1, a1, 12);
    t3 = 10;
    lw(t5, a1, 8);
    v0 = 0x10000;
    div(t1, t3);
    lw(t2, a1, 16);
    v0 = v0 | 0xA574;
    v1 = 1798;
    mult1(t1, t1, v1);
    t0 = sll(t2, 4);
    if (t3 == 0) {
        brk(ctx, 0x59AB14u, 0x7u);
    }
    // 0x0059ab18
    charge(ctx, 26);
    t0 = subu(t0, t2);
    lw(t4, a1, 20);
    lw(t2, a1, 24);
    t4 = addu(t4, t2);
    mflo(t6);
    mult(t5, t5, v0);
    lh(v0, a1, 30);
    t0 = addu(t0, t6);
    t0 = sll(t0, 1);
    v1 = sll(v0, 5);
    t5 = addu(t5, t1);
    v1 = subu(v1, v0);
    t0 = addu(t0, t5);
    v1 = sll(v1, 2);
    t0 = addu(t0, t4);
    v1 = addu(v1, v0);
    v0 = sll(t0, 5);
    v1 = sll(v1, 2);
    v0 = subu(v0, t0);
    v0 = sll(v0, 2);
    v0 = addu(v0, t0);
    v0 = sll(v0, 3);
    v0 = addu(v0, v1);
    sw(v0, a2, 0);
    sw(a0, a3, 0);
}

// 0x0059AB80 sub_59AB80 -- 168 bytes; leaf frame (no stack)
// Drop-frame time code ($a1) to time (the 59.94 table): frames = 215892 h + 3598 m + 2 (m / 10) + 60 s + f + extra, x
//   1,000, + 500 x field; *$a2 = the time, *$a3 = $a0.
void sub_59AB80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13};
    // 0x0059ab80
    enter(ctx, 19);  // entry check point + this block's cycles
    lw(t0, a1, 12);
    t4 = 10;
    lw(t3, a1, 16);
    t1 = 0x30000;
    div(t0, t4);
    lw(t2, a1, 8);
    t1 = t1 | 0x4B54;
    v0 = sll(t0, 3);
    v1 = sll(t3, 4);
    v0 = subu(v0, t0);
    v1 = subu(v1, t3);
    lw(t3, a1, 24);
    t0 = sll(v0, 8);
    v1 = sll(v1, 1);
    v0 = addu(v0, t0);
    lh(t0, a1, 30);
    v0 = sll(v0, 1);
    if (t4 == 0) {
        brk(ctx, 0x59ABC8u, 0x7u);
    }
    // 0x0059abcc
    charge(ctx, 23);
    mflo(t5);
    mult(t2, t2, t1);
    v1 = addu(v1, t5);
    lw(t1, a1, 20);
    v1 = sll(v1, 1);
    a1 = sll(t0, 5);
    t1 = addu(t1, t3);
    a1 = subu(a1, t0);
    t2 = addu(t2, v0);
    a1 = sll(a1, 2);
    v1 = addu(v1, t2);
    a1 = addu(a1, t0);
    v1 = addu(v1, t1);
    a1 = sll(a1, 2);
    v0 = sll(v1, 5);
    v0 = subu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 3);
    v0 = addu(v0, a1);
    sw(v0, a2, 0);
    sw(a0, a3, 0);
}

// 0x0059AC28 sub_59AC28 -- 96 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// Pause hook: only for $a1 == 2: reads the clock pair (sub_59AD40) and adds it to the vsync time (sub_59AC88) and the
//   external time (sub_59ACF0); $a1 < 2 returns 1, others 2.
void sub_59AC28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ac28
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = sltiu(a1, 2);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(ra, sp, 0x18);
    if (v0 == 0) {
        // 0x0059ac40
        charge(ctx, 3);
        v0 = 2;
        if (a1 == v0) {
            // 0x0059ac4c
            charge(ctx, 11);
            a1 = sp;
            a2 = addiu(sp, 0x4);
            jal(ctx, 0x59AC50u, gen::fn_sub_59AD40_0059ad40);
            a0 = s0;
            lw(a1, sp, 0x0);
            link(ctx, 0x59AC60u);  // $ra first: the delay slot below depends on it
            lw(a2, sp, 0x4);
            call(ctx, gen::fn_sub_59AC88_0059ac88);
            a0 = s0;
            lw(a1, sp, 0x0);
            link(ctx, 0x59AC70u);  // $ra first: the delay slot below depends on it
            lw(a2, sp, 0x4);
            call(ctx, gen::fn_sub_59ACF0_0059acf0);
            goto L_0059ac78;
        }
        ld(s0, sp, 0x10);
        // 0x0059ac7c (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0059ac78:
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    // 0x0059ac7c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059AC88 sub_59AC88 -- 100 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// Adds the clock converted to the vsync rate (sub_57BAF0, rate 0x7B4728) to the time record's +680 and +716, under the
//   SFD lock (sub_58C100 / sub_58C118).
void sub_59AC88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ac88
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x7B0000;
    sd(s0, sp, 0x10);
    s0 = addiu(a0, 3376);
    lw(a0, v0, 18216);  // 0x7B4728
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x20);
    jal(ctx, 0x59ACA4u, gen::fn_sub_57BAF0_0057baf0);
    a0 = sp;
    s1 = v0;
    jal(ctx, 0x59ACB0u, gen::fn_sub_58C100_0058c100);
    lw(v1, s0, 680);
    a0 = sp;
    v1 = addu(v1, s1);
    sw(v1, s0, 680);
    lw(v0, s0, 716);
    v0 = addu(v0, s1);
    link(ctx, 0x59ACD0u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 716);
    call(ctx, gen::fn_sub_58C118_0058c118);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0059ACF0 sub_59ACF0 -- 80 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// Adds the clock converted to the external unit (+4112, sub_57BAF0) to the time record's +732, under the SFD lock.
void sub_59ACF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059acf0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = addiu(a0, 3376);
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x20);
    link(ctx, 0x59AD04u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 736);
    call(ctx, gen::fn_sub_57BAF0_0057baf0);
    a0 = sp;
    s1 = v0;
    jal(ctx, 0x59AD10u, gen::fn_sub_58C100_0058c100);
    lw(v0, s0, 732);
    a0 = sp;
    v0 = addu(v0, s1);
    link(ctx, 0x59AD24u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 732);
    call(ctx, gen::fn_sub_58C118_0058c118);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0059B198 sub_59B198 -- 116 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Whether a time is reached: a negative +4092 is reset to 0 and gives 1; else the fraction compare (sub_56F4B8) of
//   ($a1, $a2) against (+4092, the rate 0x7B4728); *$a3 = the result. Returns 1.
void sub_59B198(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059b198
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = addiu(a0, 3376);
    sd(s0, sp, 0x0);
    s0 = a3;
    sd(ra, sp, 0x8);
    v0 = 0x7B0000;
    a0 = a1;
    a1 = a2;
    lw(v1, t0, 716);
    v0 = addiu(v0, 18208);  // &0x7B4720
    if (i64(v1) >= 0) {
        // 0x0059b1d8
        charge(ctx, 5);
        lw(a2, t0, 716);
        link(ctx, 0x59B1DCu);  // $ra first: the delay slot below depends on it
        lw(a3, v0, 8);
        call(ctx, gen::fn_sub_56F4B8_0056f4b8);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (cc) {
            // 0x0059b1f8
            charge(ctx, 1);
            sw(zero, s0, 0);
        } else {
            // 0x0059b1ec
            charge(ctx, 2);
            sw(v0, s0, 0);
        }
    } else {
        // 0x0059b1c4
        charge(ctx, 4);
        v0 = 1;
        sw(zero, t0, 716);
        sw(v0, s0, 0);
    }
    // 0x0059b1fc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0059B300 sub_59B300 -- 152 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// Whether the end time is reached: with counters (+2384) and an end time (+4012 != -5): end + 2000 x +4016 / 59940
//   against the current time (sub_59A168, sub_56F4B8); no counters: 1; no end time: 0.
void sub_59B300(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059b300
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = a0;
    sd(s0, sp, 0x10);
    v0 = 1;
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x20);
    lw(a1, v1, 2384);
    v1 = addiu(v1, 3376);
    lw(s0, v1, 640);
    lw(s1, v1, 636);
    if (a1 != 0) {
        // 0x0059b32c
        charge(ctx, 3);
        v1 = si(-5);
        v0 = 0;
        if (s1 != v1) {
            // 0x0059b338
            charge(ctx, 7);
            a1 = sp;
            a2 = addiu(sp, 0x4);
            jal(ctx, 0x59B33Cu, gen::fn_sub_59A168_0059a168);
            v1 = 0xEA24;
            a0 = sll(s0, 5);
            if (v1 == 0) {
                brk(ctx, 0x59B350u, 0x7u);
            }
            // 0x0059b354
            charge(ctx, 12);
            a0 = subu(a0, s0);
            lw(a2, sp, 0x0);
            a0 = sll(a0, 2);
            lw(a3, sp, 0x4);
            a0 = addu(a0, s0);
            a1 = s0;
            a0 = sll(a0, 4);
            div(a0, v1);
            mflo(a0);
            a0 = addu(s1, a0);
            jal(ctx, 0x59B378u, gen::fn_sub_56F4B8_0056f4b8);
            v0 = sltu(0, v0);
        }
    }
    // 0x0059b384 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0059B398 sub_59B398 -- 8 bytes; leaf frame (no stack)
// Stores $a1 at +4060.
void sub_59B398(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x0059b398
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, 4060);
}

// 0x0059B3A0 sub_59B3A0 -- 8 bytes; leaf frame (no stack)
// Reads +4060.
void sub_59B3A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0059b3a0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 4060);
}

// 0x0059B458 sub_59B458 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The cached clock 0x9ACBC8: computed by sub_59B3A8 when still zero.
void sub_59B458(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059b458
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x9B0000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, -13368);  // &0x9ACBC8
    ld(v0, s0, 0);  // 0x9ACBC8
    sd(ra, sp, 0x8);
    if (v0 == 0) {
        // 0x0059b474
        charge(ctx, 3);
        jal(ctx, 0x59B474u, gen::fn_sub_59B3A8_0059b3a8);
        ld(v0, s0, 0);
    }
    // 0x0059b480 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0059BE98 sub_59BE98 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// When +12 is clear, adds +304 x $a1[0] / $a1[1] (64-bit, __muldi3 / __divdi3) to the 64-bit +296.
void sub_59BE98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059be98
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    lw(v0, s0, 12);
    s1 = a1;
    if (v0 == 0) {
        // 0x0059beb8
        charge(ctx, 9);
        ld(a1, s1, 0);
        link(ctx, 0x59BEBCu);  // $ra first: the delay slot below depends on it
        ld(a0, s0, 304);
        call(ctx, gen::fn___muldi3_0052ea78);
        ld(a1, s1, 8);
        a0 = v0;
        jal(ctx, 0x59BEC8u, gen::fn___divdi3_0052eeb0);
        ld(v1, s0, 296);
        v1 = v1 + v0;
        sd(v1, s0, 296);
    }
    // 0x0059bedc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059C3B8 sub_59C3B8 -- 92 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Ring-average record: subtracts $a1 from each of the n samples (count +16, samples from +24), then stores the new
//   average (sub_59C418) at +424.
void sub_59C3B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059c3b8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, 16);
    a0 = 0;
    if (i64(v0) > 0) {
        // 0x0059c3d4
        charge(ctx, 1);
        v1 = addiu(s0, 24);
        for (;;) {
            // 0x0059c3d8
            charge(ctx, 8);
            lw(v0, v1, 0);
            a0 = addiu(a0, 1);
            v0 = subu(v0, a1);
            sw(v0, v1, 0);
            lw(v0, s0, 16);
            v0 = slt(a0, v0);
            v1 = addiu(v1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0059c3f8
    charge(ctx, 7);
    a0 = s0;
    jal(ctx, 0x59C3F8u, gen::fn_sub_59C418_0059c418);
    sw(v0, s0, 424);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0059CC58 sub_59CC58 -- 8 bytes; leaf frame (no stack)
// Returns 0.
void sub_59CC58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059cc58
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CC60 sub_59CC60 -- 8 bytes; leaf frame (no stack)
// Returns 0.
void sub_59CC60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059cc60
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CC68 sub_59CC68 -- 8 bytes; leaf frame (no stack)
// Returns 0.
void sub_59CC68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059cc68
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CC70 sub_59CC70 -- 28 bytes; frame 0x10: ra sp+0x0
// Unsupported entry: raises -16775679 on handle $a0 (sub_58BE40).
void sub_59CC70(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059cc70
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0x601;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0059CC90 sub_59CC90 -- 28 bytes; frame 0x10: ra sp+0x0
// Unsupported entry: raises -16775679 on handle $a0 (sub_58BE40).
void sub_59CC90(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059cc90
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0x601;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0059CCB0 sub_59CCB0 -- 28 bytes; frame 0x10: ra sp+0x0
// Unsupported entry: raises -16775679 on handle $a0 (sub_58BE40).
void sub_59CCB0(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ccb0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0x601;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0059CCD0 sub_59CCD0 -- 28 bytes; frame 0x10: ra sp+0x0
// Unsupported entry: raises -16775679 on handle $a0 (sub_58BE40).
void sub_59CCD0(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ccd0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0x601;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0059CCF0 sub_59CCF0 -- 8 bytes; leaf frame (no stack)
// Returns 0.
void sub_59CCF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059ccf0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CF98 sub_59CF98 -- 8 bytes; leaf frame (no stack)
// Returns 0.
void sub_59CF98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059cf98
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059E918 sub_59E918 -- 72 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// SFX callback record: calls the copy callback +24 when set (jalr; +8, +12, +16, $a2), then clears the busy word +4.
void sub_59E918(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059e918
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = a2;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    v0 = addiu(s0, 8);
    lw(v1, s0, cbrec::kCopyCb);
    lw(a2, v0, 8);
    lw(a0, v0, 0);
    lw(a1, v0, 4);
    if (v1 != 0) {
        // 0x0059e944
        charge(ctx, 2);
        jalr(ctx, 0x59E944u, v1.u());
    }
    // 0x0059e94c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sw(zero, s0, cbrec::kBusy);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0059E960 sub_59E960 -- 56 bytes; frame 0x10: ra sp+0x0
// SFX callback record: calls the callback +28 when set (jalr; $a2 and the bytes +20 / +21 / +22).
void sub_59E960(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059e960
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    a0 = a2;
    lw(v1, v0, cbrec::kCbA);
    lbu(a1, v0, 20);
    lbu(a2, v0, 21);
    lbu(a3, v0, 22);
    if (v1 != 0) {
        // 0x0059e984
        charge(ctx, 2);
        jalr(ctx, 0x59E984u, v1.u());
    }
    // 0x0059e98c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0059E998 sub_59E998 -- 56 bytes; frame 0x10: ra sp+0x0
// SFX callback record: calls the callback +32 when set (jalr; $a2 and the bytes +20 / +21 / +22).
void sub_59E998(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059e998
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    a0 = a2;
    lw(v1, v0, cbrec::kCbB);
    lbu(a1, v0, 20);
    lbu(a2, v0, 21);
    lbu(a3, v0, 22);
    if (v1 != 0) {
        // 0x0059e9bc
        charge(ctx, 2);
        jalr(ctx, 0x59E9BCu, v1.u());
    }
    // 0x0059e9c4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0059E9D0 sub_59E9D0 -- 8 bytes; leaf frame (no stack)
// SFX callback record: the busy word +4.
void sub_59E9D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0059e9d0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, cbrec::kBusy);
}

// 0x0059EA18 sub_59EA18 -- 20 bytes; leaf frame (no stack)
// SFX callback record: the bytes +20 / +21 / +22 = $a1, $a2, $a3.
void sub_59EA18(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0059ea18
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = addiu(a0, 20);
    sb(a3, a0, 2);
    sb(a1, a0, 0);
    sb(a2, a0, 1);
}

// 0x0059EA50 sub_59EA50 -- 176 bytes, 2 chunks; frame 0x10: ra sp+0x0
// SFX frame setup: $a1+68 = $t0 (width), $a1+72 = $t1 (height); steps the three planes $a1+4 / +20 / +36 (sub_5A0188)
//   down 2 ($a3 / 2) lines and right 2 ($a2 / 2) columns for Y, half of each for U and V. Two chunks.
void sub_59EA50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ea50
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    sd(ra, sp, 0x0);
    a0 = v0;
    a1 = a2;
    a2 = a3;
    ld(ra, sp, 0x0);
    sw(t0, v0, 68);
    sw(t1, v0, 72);
    sp = addiu(sp, 0x10);
    // 0x005a0100
    charge(ctx, 33);
    v0 = srl(a2, 31);
    v1 = srl(a1, 31);
    v0 = addu(v0, a2);
    v1 = addu(v1, a1);
    sp = addiu(sp, -0x20);
    v0 = sra(v0, 1);
    v1 = sra(v1, 1);
    v0 = sll(v0, 1);
    v1 = sll(v1, 1);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s2 = sra(v1, 1);
    s1 = sra(v0, 1);
    a1 = v0;
    a2 = v1;
    sd(ra, sp, 0x18);
    a0 = addiu(s0, 4);
    jal(ctx, 0x5A0148u, gen::fn_sub_5A0188_005a0188);
    a0 = addiu(s0, 20);
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x5A0158u, gen::fn_sub_5A0188_005a0188);
    a0 = addiu(s0, 36);
    a1 = s1;
    ld(s1, sp, 0x8);
    a2 = s2;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5A0188_005a0188(ctx);  // tail call
}

// 0x0059EA80 sub_59EA80 -- 40 bytes; leaf frame (no stack)
// Plane walk: flips the pitch +16 and moves the base +4 to the last line (+ pitch x (lines +12 - 1)).
void sub_59EA80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0059ea80
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(v1, a0, 12);
    lw(v0, a0, 16);
    v1 = addiu(v1, -1);
    lw(a1, a0, 4);
    mult(v1, v0, v1);
    v0 = subu(0, v0);
    sw(v0, a0, 16);
    a1 = addu(a1, v1);
    sw(a1, a0, 4);
}

// 0x0059EAF8 sub_59EAF8 -- 216 bytes; frame 0x10: ra sp+0x0
// [sfxcnv_IsCnvUpHalf] Whether the composition a0+4 converts the upper half: 1 for 33 and 257, 0 for 17, 49, 65, 81,
//   97, 113, 241, 273 and 4097; any other raises E201312 (sub_59FD10).
void sub_59EAF8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059eaf8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 97;
    sd(ra, sp, 0x0);
    lw(v1, a0, 4);
    cc = v1 == v0;  // the condition, before the delay slot changes it
    v0 = slti(v1, 98);
    if (!cc) {
        // 0x0059eb10
        charge(ctx, 2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 257;
        if (cc) {
            // 0x0059eb60
            charge(ctx, 2);
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (!cc) {
                // 0x0059eb68
                charge(ctx, 3);
                v0 = slti(v1, 258);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = 273;
                if (!cc) {
                    // 0x0059eb74
                    charge(ctx, 3);
                    v0 = 113;
                    cc = v1 == v0;  // the condition, before the delay slot changes it
                    v0 = 241;
                    if (!cc) {
                        // 0x0059eb80
                        charge(ctx, 2);
                        a2 = 0x7D0000;
                        if (v1 != v0) {
                            // 0x0059eb88
                            charge(ctx, 2);
                            a0 = 0;
                            goto L_0059ebb4;
                        }
                    }
                    goto L_0059ebc0;
                }
                // 0x0059eb90
                charge(ctx, 2);
                cc = v1 == v0;  // the condition, before the delay slot changes it
                v0 = 4097;
                if (cc) {
                    goto L_0059ebc0;
                }
                // 0x0059eb98
                charge(ctx, 2);
                a2 = 0x7D0000;
                if (v1 != v0) {
                    // 0x0059ebb0
                    charge(ctx, 1);
                    a0 = 0;
                L_0059ebb4:
                    charge(ctx, 3);
                    a2 = addiu(a2, -23024);
                    a1 = 0;
                    jal(ctx, 0x59EBB8u, gen::fn_sub_59FD10_0059fd10);
                    goto L_0059ebc0;
                }
                // 0x0059eba0
                charge(ctx, 2);
                v0 = 0;
            }
        } else {
            // 0x0059eb18
            charge(ctx, 3);
            v0 = 49;
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = slti(v1, 50);
            if (cc) {
                goto L_0059ebc0;
            }
            // 0x0059eb24
            charge(ctx, 2);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 65;
            if (cc) {
                // 0x0059eb48
                charge(ctx, 2);
                cc = v1 == v0;  // the condition, before the delay slot changes it
                v0 = 81;
                if (!cc) {
                    // 0x0059eb50
                    charge(ctx, 2);
                    a2 = 0x7D0000;
                    if (v1 != v0) {
                        // 0x0059eb58
                        charge(ctx, 2);
                        a0 = 0;
                        goto L_0059ebb4;
                    }
                }
                goto L_0059ebc0;
            }
            // 0x0059eb2c
            charge(ctx, 3);
            v0 = 17;
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = 33;
            if (cc) {
                goto L_0059ebc0;
            }
            // 0x0059eb38
            charge(ctx, 2);
            a2 = 0x7D0000;
            if (v1 != v0) {
                // 0x0059eb40
                charge(ctx, 2);
                a0 = 0;
                goto L_0059ebb4;
            }
            // 0x0059eba8
            charge(ctx, 2);
            v0 = 1;
        }
        // 0x0059ebc4 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_0059ebc0:
    charge(ctx, 1);
    v0 = 0;
    // 0x0059ebc4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0059EBD0 sub_59EBD0 -- 56 bytes; leaf frame (no stack)
// The conversion mode of a composition ($a0+4): 4 for 81, 5 for 97; otherwise 4 when $a1+148 is 81, else 5.
void sub_59EBD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0059ebd0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(a0, a0, 4);
    a2 = 81;
    v0 = 4;
    if (a0 != a2) {
        // 0x0059ebe0
        charge(ctx, 3);
        v1 = 97;
        v0 = 5;
        if (a0 != v1) {
            // 0x0059ebec
            charge(ctx, 5);
            lw(v1, a1, 148);
            a0 = 5;
            v0 = 4;
            v1 = v1 ^ a2;
            if (v1 != 0) v0 = a0;
        }
    }
    // 0x0059ec00 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0059ED78 sub_59ED78 -- 160 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Whether the conversion runs in mode $a1: 0 when +52 is 100; 1 when +52 differs from $a1; for an equal mode: 0 for 1,
//   4, 5 and 21, for 2 whether the record +48 is busy (sub_59E9D0 == 1), else 1.
void sub_59ED78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059ed78
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 100;
    sd(s0, sp, 0x0);
    s0 = 1;
    sd(ra, sp, 0x8);
    lw(a2, a0, 52);
    v0 = 0;
    if (a2 != v1) {
        // 0x0059ed98
        charge(ctx, 2);
        v0 = s0;
        if (a2 != a1) {
            goto L_0059ee08;
        }
        // 0x0059eda0
        charge(ctx, 3);
        v0 = sltiu(a1, 6);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 21;
        if (cc) {
            // 0x0059ede0
            charge(ctx, 2);
            cc = a1 == v0;  // the condition, before the delay slot changes it
            v0 = s0;
            if (cc) {
            L_0059ee00:
                charge(ctx, 1);
                s0 = 0;
            L_0059ee04:
                charge(ctx, 1);
                v0 = s0;
                goto L_0059ee08;
            }
            // 0x0059ede8
            charge(ctx, 2);
            ld(s0, sp, 0x0);
        } else {
            // 0x0059edac
            charge(ctx, 3);
            v0 = sltiu(a1, 4);
            if (v0 == 0) {
                s0 = 0;
                goto L_0059ee04;
            }
            // 0x0059edb8
            charge(ctx, 2);
            if (a1 == s0) {
                s0 = 0;
                goto L_0059ee04;
            }
            // 0x0059edc0
            charge(ctx, 2);
            v0 = s0;
            if (a1 == 0) {
                goto L_0059ee08;
            }
            // 0x0059edc8
            charge(ctx, 3);
            v0 = 2;
            cc = a1 == v0;  // the condition, before the delay slot changes it
            v0 = s0;
            if (cc) {
                // 0x0059edf0
                charge(ctx, 4);
                link(ctx, 0x59EDF0u);  // $ra first: the delay slot below depends on it
                lw(a0, a0, 48);
                call(ctx, gen::fn_sub_59E9D0_0059e9d0);
                cc = v0 == s0;  // the condition, before the delay slot changes it
                v0 = s0;
                if (!cc) {
                    goto L_0059ee00;
                }
                goto L_0059ee08;
            }
            // 0x0059edd4
            charge(ctx, 2);
            ld(s0, sp, 0x0);
        }
        // 0x0059ee0c (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_0059ee08:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0059ee0c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0059EE38 sub_59EE38 -- 204 bytes; frame 0x10: ra sp+0x0
// Fills the 256-byte luma-key table at +56: 0 for 0..15, (i - 16) x 0.582 for 16..235 (cvt.w.s with the 2^31
//   correction), 0x80 for 236..255.
void sub_59EE38(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0059ee38
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 56);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0059ee50
    charge(ctx, 2);
    a1 = 15;
    v0 = addiu(a0, 15);
    for (;;) {
        // 0x0059ee58
        charge(ctx, 7);
        a1 = addiu(a1, -1);
        sb(zero, v0, 0);
        v0 = addiu(v0, -1);
        if (i64(a1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0059ee74
    charge(ctx, 7);
    at = 0x3F140000;
    at = at | 0xFDF3;
    mtc1(at, f2);
    a1 = 16;
    at = 0x4F000000;
    mtc1(at, f1);
    a3 = lui(0x8000);
    for (;;) {
        // 0x0059ee90
        charge(ctx, 11);
        v0 = addiu(a1, -16);
        a2 = addu(a0, a1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        a1 = addiu(a1, 1);
        mul_s(f0, f0, f2);
        c_le_s(f1, f0);
        cvt_w_s(f3, f0);
        mfc1(v0, f3);
        v1 = slti(a1, 236);
        if (cond(ctx)) {
            // 0x0059eebc
            charge(ctx, 4);
            sub_s(f0, f0, f1);
            cvt_w_s(f3, f0);
            mfc1(v0, f3);
            v0 = v0 | a3;
        }
        // 0x0059eecc
        charge(ctx, 2);
        sb(v0, a2, 0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0059eed4
    charge(ctx, 3);
    a1 = 236;
    a2 = si(-128);
    for (;;) {
        // 0x0059eee0
        charge(ctx, 7);
        v1 = addu(a0, a1);
        a1 = addiu(a1, 1);
        v0 = slti(a1, 256);
        sb(a2, v1, 0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0059eefc
    charge(ctx, 2);
}

// 0x0059EF08 sub_59EF08 -- 32 bytes; frame 0x10: ra sp+0x0
// Runs the copy callback of the record $a0+48 (sub_59E918) with $a1+76 and $a0+56.
void sub_59EF08(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ef08
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a2, a0, sfx::kTable);
    lw(a1, a1, 76);
    lw(a0, a0, sfx::kCbRec);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59E918_0059e918(ctx);  // tail call
}

// 0x0059EF28 sub_59EF28 -- 32 bytes; frame 0x10: ra sp+0x0
// Runs the record $a0+48's callback +28 (sub_59E960) with $a1+76 and $a0+56.
void sub_59EF28(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ef28
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a2, a0, sfx::kTable);
    lw(a1, a1, 76);
    lw(a0, a0, sfx::kCbRec);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59E960_0059e960(ctx);  // tail call
}

// 0x0059EF48 sub_59EF48 -- 32 bytes; frame 0x10: ra sp+0x0
// Runs the record $a0+48's callback +32 (sub_59E998) with $a1+76 and $a0+56.
void sub_59EF48(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ef48
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a2, a0, sfx::kTable);
    lw(a1, a1, 76);
    lw(a0, a0, sfx::kCbRec);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59E998_0059e998(ctx);  // tail call
}

// 0x0059EF68 sub_59EF68 -- 40 bytes; frame 0x10: ra sp+0x0
// Calls the callback +112 (jalr) with +56 when set.
void sub_59EF68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ef68
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 112);
    lw(a0, a0, 56);
    if (v0 != 0) {
        // 0x0059ef7c
        charge(ctx, 2);
        jalr(ctx, 0x59EF7Cu, v0.u());
    }
    // 0x0059ef84 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0059EF90 sub_59EF90 -- 116 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [SFX_MakeTblZ16] When the Z object +36 answers 1 (sub_5A0BB0): sub_5A10E8 ($a0, 16, the E202282 message), then
//   sub_59EE18 ($a0, $a1) as a tail call; else sub_59FD10 ($a0, $a1, the E202282 message 'zclip is not set') as a tail
//   call.
void sub_59EF90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ef90
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    link(ctx, 0x59EFA8u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 36);
    call(ctx, gen::fn_sub_5A0BB0_005a0bb0);
    a2 = 0x7D0000;
    v1 = 1;
    a0 = s0;
    a1 = 16;
    a2 = addiu(a2, -22504);  // "E202282: SFX_MakeTblZ16 : zclip is not set."
    if (v0 != v1) {
        // 0x0059efc8
        charge(ctx, 6);
        a1 = s1;
        ld(s1, sp, 0x8);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_59FD10_0059fd10(ctx);  // tail call
        return;
    }
    // 0x0059efe0
    charge(ctx, 9);
    jal(ctx, 0x59EFE0u, gen::fn_sub_5A10E8_005a10e8);
    a0 = s0;
    a1 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_59EE18_0059ee18(ctx);  // tail call
}

// 0x0059F008 sub_59F008 -- 116 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [SFX_MakeTblZ32] sub_59EF90 for 32 bits (depth 32, message E202281).
void sub_59F008(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059f008
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    link(ctx, 0x59F020u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 36);
    call(ctx, gen::fn_sub_5A0BB0_005a0bb0);
    a2 = 0x7D0000;
    v1 = 1;
    a0 = s0;
    a1 = 32;
    a2 = addiu(a2, -22456);  // "E202281: SFX_MakeTblZ32 : zclip is not set."
    if (v0 != v1) {
        // 0x0059f040
        charge(ctx, 6);
        a1 = s1;
        ld(s1, sp, 0x8);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_59FD10_0059fd10(ctx);  // tail call
        return;
    }
    // 0x0059f058
    charge(ctx, 9);
    jal(ctx, 0x59F058u, gen::fn_sub_5A10E8_005a10e8);
    a0 = s0;
    a1 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_59EE18_0059ee18(ctx);  // tail call
}

// 0x0059F080 sub_59F080 -- 8 bytes; leaf frame (no stack)
// Stores $a1 at +104.
void sub_59F080(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x0059f080
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, 104);
}

// 0x0059F0C8 sub_59F0C8 -- 600 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// Conversion by callback: by the composition +4 (read from the header tag 'COMPO' by sub_59F968 when zero) sets the
//   mode (sub_59EC08: 2, 1, 21 or sub_59EBD0's) and runs the copy: sub_59F518 for 33, sub_59F320 for the rest; other
//   compositions raise E4111902 (sfxcnv_ChkCompoByCbFunc, sub_59FD10).
void sub_59F0C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059f0c8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    lw(s0, s1, 4);
    s3 = a2;
    if (s0 == 0) {
        // 0x0059f0f4
        charge(ctx, 5);
        a1 = 0x7D0000;
        a0 = s2;
        a1 = addiu(a1, -22408);  // "COMPO"
        jal(ctx, 0x59F0FCu, gen::fn_sub_59F968_0059f968);
        sw(v0, s1, 4);
    }
    // 0x0059f108
    charge(ctx, 3);
    v0 = 97;
    cc = s0 == v0;  // the condition, before the delay slot changes it
    v0 = slti(s0, 98);
    if (!cc) {
        // 0x0059f114
        charge(ctx, 2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 257;
        if (cc) {
            // 0x0059f168
            charge(ctx, 2);
            cc = s0 == v0;  // the condition, before the delay slot changes it
            v0 = slti(s0, 258);
            if (cc) {
                // 0x0059f2c8
                charge(ctx, 11);
                a0 = s1;
                ld(s1, sp, 0x8);
                a1 = s2;
                ld(s2, sp, 0x10);
                a2 = s3;
                ld(s3, sp, 0x18);
                ld(s0, sp, 0x0);
                a3 = 0;
                ld(ra, sp, 0x20);
                sp = addiu(sp, 0x30);
                gen::fn_sub_59F320_0059f320(ctx);  // tail call
                return;
            }
            // 0x0059f170
            charge(ctx, 2);
            a0 = s1;
            if (v0 == 0) {
                // 0x0059f178
                charge(ctx, 3);
                v0 = 273;
                cc = s0 == v0;  // the condition, before the delay slot changes it
                v0 = 4097;
                if (cc) {
                    goto L_0059f2f8;
                }
                // 0x0059f184
                charge(ctx, 2);
                a1 = s2;
                if (s0 != v0) {
                    // 0x0059f18c
                    charge(ctx, 2);
                    ld(s1, sp, 0x8);
                L_0059f300:
                    charge(ctx, 8);
                    ld(s2, sp, 0x10);
                    a2 = 0x7D0000;
                    ld(s0, sp, 0x0);
                    ld(s3, sp, 0x18);
                    a2 = addiu(a2, -22400);  // "E4111902: sfxcnv_ChkCompoByCbFunc : compo is not support."
                    ld(ra, sp, 0x20);
                    sp = addiu(sp, 0x30);
                    gen::fn_sub_59FD10_0059fd10(ctx);  // tail call
                    return;
                }
            L_0059f1d4:
                charge(ctx, 13);
                a2 = 21;
                jal(ctx, 0x59F1D4u, gen::fn_sub_59EC08_0059ec08);
                a0 = s1;
                a1 = s2;
                ld(s2, sp, 0x10);
                a2 = s3;
                ld(s3, sp, 0x18);
                ld(s0, sp, 0x0);
                a3 = 1;
                ld(s1, sp, 0x8);
                ld(ra, sp, 0x20);
                sp = addiu(sp, 0x30);
                gen::fn_sub_59F320_0059f320(ctx);  // tail call
                return;
            }
        L_0059f2f8:
            charge(ctx, 1);
            ld(s1, sp, 0x8);
        L_0059f2fc:
            charge(ctx, 1);
            a1 = s2;
            goto L_0059f300;
        }
        // 0x0059f11c
        charge(ctx, 3);
        v0 = 49;
        cc = s0 == v0;  // the condition, before the delay slot changes it
        v0 = slti(s0, 50);
        if (cc) {
            // 0x0059f240
            charge(ctx, 15);
            a0 = s1;
            a1 = s2;
            a2 = 2;
            jal(ctx, 0x59F248u, gen::fn_sub_59EC08_0059ec08);
            a0 = s1;
            a1 = s2;
            ld(s2, sp, 0x10);
            a2 = s3;
            ld(s3, sp, 0x18);
            ld(s0, sp, 0x0);
            a3 = 1;
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            gen::fn_sub_59F320_0059f320(ctx);  // tail call
            return;
        }
        // 0x0059f128
        charge(ctx, 2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 65;
        if (cc) {
            // 0x0059f150
            charge(ctx, 2);
            cc = s0 == v0;  // the condition, before the delay slot changes it
            v0 = 81;
            if (cc) {
                goto L_0059f280;
            }
            // 0x0059f158
            charge(ctx, 2);
            a0 = s1;
            if (s0 == v0) {
                goto L_0059f280;
            }
            // 0x0059f160
            charge(ctx, 2);
            ld(s1, sp, 0x8);
            goto L_0059f2fc;
        }
        // 0x0059f130
        charge(ctx, 3);
        v0 = 17;
        cc = s0 == v0;  // the condition, before the delay slot changes it
        v0 = 33;
        if (cc) {
            // 0x0059f198
            charge(ctx, 4);
            lw(v1, s2, 144);
            v0 = 1;
            a0 = s1;
            if (v1 == v0) {
                // 0x0059f1d0
                charge(ctx, 1);
                a1 = s2;
                goto L_0059f1d4;
            }
            // 0x0059f1a8
            charge(ctx, 10);
            ld(s1, sp, 0x8);
            a1 = s2;
            ld(s2, sp, 0x10);
            a2 = s3;
            ld(s3, sp, 0x18);
            ld(s0, sp, 0x0);
            a3 = 0;
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            gen::fn_sub_59F320_0059f320(ctx);  // tail call
            return;
        }
        // 0x0059f13c
        charge(ctx, 2);
        a0 = s1;
        if (s0 != v0) {
            // 0x0059f144
            charge(ctx, 2);
            ld(s1, sp, 0x8);
            goto L_0059f2fc;
        }
        // 0x0059f208
        charge(ctx, 13);
        a1 = s2;
        a2 = 1;
        jal(ctx, 0x59F20Cu, gen::fn_sub_59EC08_0059ec08);
        a0 = s1;
        a1 = s2;
        ld(s2, sp, 0x10);
        a2 = s3;
        ld(s3, sp, 0x18);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_59F518_0059f518(ctx);  // tail call
        return;
    }
L_0059f280:
    charge(ctx, 18);
    a0 = s1;
    a1 = s2;
    jal(ctx, 0x59F284u, gen::fn_sub_59EBD0_0059ebd0);
    a0 = s1;
    a1 = s2;
    a2 = v0;
    jal(ctx, 0x59F294u, gen::fn_sub_59EC08_0059ec08);
    a0 = s1;
    a1 = s2;
    ld(s2, sp, 0x10);
    a2 = s3;
    ld(s3, sp, 0x18);
    ld(s0, sp, 0x0);
    a3 = 1;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_59F320_0059f320(ctx);  // tail call
}

// 0x0059F518 sub_59F518 -- 432 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [sfxcnv_ExecCopyAlphaByCbFunc] The alpha copy: the plane records (sub_59F320, sub_59F3D8), the alpha plane by the
//   frame format *$a1 (1, 2: from the frame; 3: below the picture), the luma-key table +56 when the table mode
//   (WTLS_get_table_2) is 1, then the callback +108 (jalr) on the three records; format 0 or above 3 raises E4011801.
void sub_59F518(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059f518
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a3 = 0;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x59F538u, gen::fn_sub_59F320_0059f320);
    ld(ra, sp, 0x18);
    a0 = s0;
    a1 = s1;
    ld(s1, sp, 0x8);
    a2 = s2;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    // 0x0059f568
    charge(ctx, 16);
    sp = addiu(sp, -0xE0);
    sd(s0, sp, 0xC0);
    s0 = a2;
    sd(s1, sp, 0xC8);
    s1 = a1;
    a2 = sp;
    sd(s2, sp, 0xD0);
    sd(ra, sp, 0xD8);
    s2 = a0;
    jal(ctx, 0x59F588u, gen::fn_sub_59F3D8_0059f3d8);
    lw(v1, s1, 0);
    t1 = addiu(sp, 0x4);
    t2 = addiu(sp, 0x14);
    t3 = addiu(sp, 0x24);
    t4 = addiu(sp, 0x54);
    if (v1 == 0) {
        // 0x0059f668
        charge(ctx, 1);
        a2 = 0x7D0000;
    L_0059f66c:
        charge(ctx, 4);
        a1 = s1;
        a2 = addiu(a2, -22272);
        a0 = s2;
        jal(ctx, 0x59F674u, gen::fn_sub_59FD10_0059fd10);
    } else {
        // 0x0059f5a8
        charge(ctx, 3);
        v0 = sltiu(v1, 3);
        if (v0 != 0) {
            lw(v0, s0, 12);
            // 0x0059f630
            charge(ctx, 7);
            lw(a0, s0, 8);
            lw(a1, s2, 8);
            lw(v1, s0, 4);
            sw(a0, sp, 0x58);
            sw(v1, t4, 0);
            sw(v0, sp, 0x5C);
            if (a1 != 0) {
                // 0x0059f660
                charge(ctx, 2);
                sw(a1, sp, 0x60);
            } else {
            L_0059f64c:
                charge(ctx, 4);
                lw(v0, sp, 0x8);
                v0 = sll(v0, 2);
                sw(v0, sp, 0x60);
            }
        } else {
            // 0x0059f5b4
            charge(ctx, 3);
            v0 = 3;
            a2 = 0x7D0000;
            if (v1 != v0) {
                goto L_0059f66c;
            }
            // 0x0059f5c0
            charge(ctx, 26);
            lw(v1, sp, 0xC);
            lw(v0, sp, 0x10);
            lw(a0, s0, 8);
            mult(v0, v0, v1);
            lw(a1, t1, 0);
            lw(a2, s0, 12);
            lw(t0, s2, 8);
            sw(a0, sp, 0x58);
            v1 = srl(v0, 31);
            lw(a3, s0, 4);
            v0 = addu(v0, v1);
            sw(a2, sp, 0x5C);
            a0 = sra(v0, 1);
            v0 = srl(v0, 31);
            a1 = addu(a1, a0);
            a0 = addu(a0, v0);
            sw(a1, t1, 0);
            a0 = sra(a0, 1);
            lw(v0, t2, 0);
            v0 = addu(v0, a0);
            sw(v0, t2, 0);
            lw(v1, t3, 0);
            v1 = addu(v1, a0);
            sw(v1, t3, 0);
            sw(a3, t4, 0);
            if (t0 == 0) {
                goto L_0059f64c;
            }
            // 0x0059f628
            charge(ctx, 2);
            sw(t0, sp, 0x60);
        }
    }
    // 0x0059f67c
    charge(ctx, 5);
    jal(ctx, 0x59F67Cu, gen::fn_WTLS_get_table_2_0059fd60);
    v1 = 1;
    if (v0 != v1) {
        sw(zero, sp, 0xA0);
    } else {
        // 0x0059f690
        charge(ctx, 2);
        lw(v0, s2, 56);
        sw(v0, sp, 0xA0);
    }
    // 0x0059f698
    charge(ctx, 3);
    lw(v0, s2, 108);
    a0 = sp;
    if (v0 != 0) {
        // 0x0059f6a4
        charge(ctx, 3);
        a1 = addiu(sp, 0x50);
        a2 = addiu(sp, 0xA0);
        jalr(ctx, 0x59F6A8u, v0.u());
    }
    // 0x0059f6b0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0xC0);
    ld(s1, sp, 0xC8);
    ld(s2, sp, 0xD0);
    ld(ra, sp, 0xD8);
    sp = addiu(sp, 0xE0);
}

// 0x0059F6C8 sub_59F6C8 -- 120 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Conversion setup: sub_59EA50 on the frame, sub_59F740 for slot 0, *$a3 = 1; returns 1.
void sub_59F6C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059f6c8
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    a2 = t0;
    t0 = t2;
    a3 = t1;
    sd(ra, sp, 0x20);
    t1 = t3;
    jal(ctx, 0x59F6FCu, gen::fn_sub_59EA50_0059ea50);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    t0 = 0;
    jal(ctx, 0x59F714u, gen::fn_sub_59F740_0059f740);
    v0 = 1;
    sw(v0, s3, 0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0059F740 sub_59F740 -- 168 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Conversion slot $t0 of $a3 (16 bytes each): +4 = $a2, +8 = the width ($a1+68), +12 = the height ($a1+72, halved when
//   sub_59EAF8 says upper half), +16 = the pitch ($a0+8, or the width).
void sub_59F740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059f740
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = sll(t0, 4);
    sd(s1, sp, 0x8);
    s1 = a3;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = a0;
    sd(ra, sp, 0x20);
    v0 = addu(s1, s0);
    v1 = v0;
    sw(a2, v0, 4);
    lw(a1, s2, 68);
    link(ctx, 0x59F778u);  // $ra first: the delay slot below depends on it
    sw(a1, v1, 8);
    call(ctx, gen::fn_sub_59EAF8_0059eaf8);
    a1 = addu(s1, s0);
    a0 = a1;
    v1 = 1;
    s1 = a0;
    if (v0 != v1) {
        // 0x0059f7b0
        charge(ctx, 2);
        lw(v0, s2, 72);
        sw(v0, s1, 12);
    } else {
        // 0x0059f794
        charge(ctx, 6);
        lw(v0, s2, 72);
        v1 = srl(v0, 31);
        v0 = addu(v0, v1);
        v0 = sra(v0, 1);
        sw(v0, a0, 12);
    }
    // 0x0059f7b8
    charge(ctx, 3);
    lw(v0, s3, 8);
    v1 = v0;
    if (v0 == 0) {
        // 0x0059f7c4
        charge(ctx, 1);
        lw(v1, s2, 68);
    }
    // 0x0059f7c8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sw(v1, a1, 16);
    sp = addiu(sp, 0x30);
}

// 0x0059F7E8 sub_59F7E8 -- 272 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// Splits the conversion work ($t0, size $t1): the three sizes from sub_59F8F8 ($a1, $a2, $a3), each part 32-byte
//   aligned after the previous (+124 / +128, +132 / +136, +140 / +144; 0 / 0 for an empty part); +116 = $t0, +120 = $t1.
//   A work smaller than needed raises E5022301.
void sub_59F7E8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059f7e8
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = t0;
    sd(s2, sp, 0x20);
    s2 = t1;
    a0 = a1;
    a1 = a2;
    t1 = addiu(sp, 0x8);
    t0 = addiu(sp, 0x4);
    a2 = a3;
    sd(ra, sp, 0x28);
    a3 = sp;
    jal(ctx, 0x59F81Cu, gen::fn_sub_59F8F8_0059f8f8);
    v0 = slt(s2, v0);
    lw(a0, sp, 0x0);
    if (v0 == 0) {
        // 0x0059f850
        charge(ctx, 4);
        v1 = s1;
        sw(s2, s0, 120);
        sw(s1, s0, 116);
        if (a0 == 0) {
            // 0x0059f880
            charge(ctx, 2);
            sw(zero, s0, 124);
            sw(zero, s0, 128);
        } else {
            // 0x0059f860
            charge(ctx, 7);
            v0 = addiu(v1, 31);
            v1 = si(-32);
            v0 = v0 & v1;
            sw(a0, s0, 128);
            v1 = addu(v0, a0);
            sw(v0, s0, 124);
        }
        // 0x0059f888
        charge(ctx, 3);
        lw(a0, sp, 0x4);
        v0 = addiu(v1, 31);
        if (a0 == 0) {
            // 0x0059f8b0
            charge(ctx, 2);
            sw(zero, s0, 132);
            sw(zero, s0, 136);
        } else {
            // 0x0059f894
            charge(ctx, 6);
            v1 = si(-32);
            v0 = v0 & v1;
            sw(a0, s0, 136);
            v1 = addu(v0, a0);
            sw(v0, s0, 132);
        }
        // 0x0059f8b8
        charge(ctx, 3);
        lw(a0, sp, 0x8);
        v0 = addiu(v1, 31);
        if (a0 == 0) {
            // 0x0059f8d8
            charge(ctx, 2);
            sw(zero, s0, 144);
            sw(zero, s0, 140);
        } else {
            // 0x0059f8c4
            charge(ctx, 5);
            v1 = si(-32);
            v0 = v0 & v1;
            sw(a0, s0, 144);
            sw(v0, s0, 140);
        }
        // 0x0059f8e0
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    } else {
        // 0x0059f830
        charge(ctx, 7);
        a2 = 0x7D0000;
        a0 = 0;
        a2 = addiu(a2, -22200);  // "E5022301: cnvfrm work is short."
        a1 = 0;
        jal(ctx, 0x59F83Cu, gen::fn_sub_59FD10_0059fd10);
        ld(s0, sp, 0x10);
    }
    // 0x0059f8e4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0059FDC0 sub_59FDC0 -- 12 bytes; leaf frame (no stack)
// Stores $a1 at +8 and $a2 at +12.
void sub_59FDC0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0059fdc0
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a2, a0, 12);
    sw(a1, a0, 8);
}

// 0x0059FDF0 sub_59FDF0 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// sub_59FE50 ($a0, 100), then $a0+56 + 4 x $a1 = $a2.
void sub_59FDF0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059fdf0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    a1 = 100;
    s0 = sll(s0, 2);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x59FE14u, gen::fn_sub_59FE50_0059fe50);
    s0 = addu(s0, s1);
    ld(s1, sp, 0x8);
    sw(s2, s0, 56);
    ld(ra, sp, 0x18);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059FE60 sub_59FE60 -- 152 bytes; frame 0x40: s1 sp+0x28, s0 sp+0x20, ra sp+0x30
// SFX info: +24 = $a1, +28 = $a2 (the header buffer); looks up the 'SFXZ' tag in 'SFXINFE' (sub_563E68) and hands it,
//   or nothing, to the Z object +36 (sub_5A03B0); +20 = 1. Returns 1.
void sub_59FE60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059fe60
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    t0 = a0;
    sd(s1, sp, 0x28);
    s1 = addiu(t0, 20);
    sd(s0, sp, 0x20);
    v0 = a1;
    sd(ra, sp, 0x30);
    v1 = a2;
    sw(v0, s1, 4);
    a1 = 0x7D0000;
    sw(v1, s1, 8);
    a2 = 0x7D0000;
    a0 = sp;
    a1 = addiu(a1, -22000);  // "SFXZ"
    a2 = addiu(a2, -21992);  // "SFXINFE"
    lw(s0, t0, 36);
    a3 = addiu(sp, 0x10);
    sw(v0, sp, 0x0);
    link(ctx, 0x59FEA8u);  // $ra first: the delay slot below depends on it
    sw(v1, sp, 0x4);
    call(ctx, gen::fn_sub_563E68_00563e68);
    a1 = 0;
    a2 = 0;
    a0 = s0;
    if (v0 != 0) {
        // 0x0059fed0
        charge(ctx, 4);
        lw(a1, sp, 0x10);
        link(ctx, 0x59FED4u);  // $ra first: the delay slot below depends on it
        lw(a2, sp, 0x14);
        call(ctx, gen::fn_sub_5A03B0_005a03b0);
        v0 = 1;
    } else {
        // 0x0059fec0
        charge(ctx, 4);
        jal(ctx, 0x59FEC0u, gen::fn_sub_5A03B0_005a03b0);
        v0 = 1;
    }
    // 0x0059fee0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x20);
    sw(v0, s1, 0);
    ld(ra, sp, 0x30);
    ld(s1, sp, 0x28);
    sp = addiu(sp, 0x40);
}

// 0x0059FF48 sub_59FF48 -- 24 bytes; frame 0x10: ra sp+0x0
// Z-clip of the Z object +36 (sub_5A0B00, $f12 / $f13 passed on).
void sub_59FF48(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ff48
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, sfx::kZObj);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5A0B00_005a0b00(ctx);  // tail call
}

// 0x0059FF60 sub_59FF60 -- 44 bytes, 2 chunks; frame 0x10: ra sp+0x0
// The Z object +36's +60 / +64 to *$a1 / *$a2. Two chunks.
void sub_59FF60(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0059ff60
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, sfx::kZObj);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x005a0b98
    charge(ctx, 5);
    lwc1(f0, a0, zobj::kClipNear);
    swc1(f0, a1, 0);
    lwc1(f1, a0, zobj::kClipFar);
    swc1(f1, a2, 0);
}

// 0x0059FF78 sub_59FF78 -- 28 bytes; frame 0x10: ra sp+0x0
// The Z object +36's lookup (sub_5A04F0) with $a1+76.
void sub_59FF78(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ff78
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, sfx::kZObj);
    lw(a1, a1, 76);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5A04F0_005a04f0(ctx);  // tail call
}

// 0x0059FF98 sub_59FF98 -- 52 bytes, 2 chunks; frame 0x10: ra sp+0x0
// The callback record +48: +8 = $a3, +12 = $a1, +16 = $a2, busy +4 = 1. Two chunks.
void sub_59FF98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ff98
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, sfx::kCbRec);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x0059e9d8
    charge(ctx, 7);
    v0 = addiu(a0, 8);
    v1 = 1;
    sw(a2, v0, 8);
    sw(a3, v0, 0);
    sw(a1, v0, 4);
    sw(v1, a0, 4);
}

// 0x0059FFB0 sub_59FFB0 -- 56 bytes, 2 chunks; frame 0x10: ra sp+0x0
// The callback record +48: *$a3 = +8, *$a1 = +12, *$a2 = +16. Two chunks.
void sub_59FFB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ffb0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, sfx::kCbRec);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x0059e9f8
    charge(ctx, 8);
    a0 = addiu(a0, 8);
    lw(v0, a0, 0);
    sw(v0, a3, 0);
    lw(v1, a0, 4);
    sw(v1, a1, 0);
    lw(v0, a0, 8);
    sw(v0, a2, 0);
}

// 0x005A0008 sub_5A0008 -- 56 bytes, 2 chunks; frame 0x10: ra sp+0x0
// The callback record +48: the bytes +20 / +21 / +22 to *$a1 / *$a2 / *$a3. Two chunks.
void sub_5A0008(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a0008
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, sfx::kCbRec);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x0059ea30
    charge(ctx, 8);
    a0 = addiu(a0, 20);
    lbu(v0, a0, 0);
    sb(v0, a1, 0);
    lbu(v1, a0, 1);
    sb(v1, a2, 0);
    lbu(v0, a0, 2);
    sb(v0, a3, 0);
}

// 0x005A00B0 sub_5A00B0 -- 36 bytes; leaf frame (no stack)
// Plane step: base +0 += $a1 x pitch +4, lines +8 -= $a1.
void sub_5A00B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x005a00b0
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(v1, a0, plane::kPitch);
    lw(a2, a0, plane::kBase);
    mult(v1, a1, v1);
    lw(v0, a0, plane::kLines);
    v0 = subu(v0, a1);
    sw(v0, a0, plane::kLines);
    a2 = addu(a2, v1);
    sw(a2, a0, plane::kBase);
}

// 0x005A0188 sub_5A0188 -- 40 bytes; leaf frame (no stack)
// Plane step with columns: base +0 += $a1 x pitch +4 + $a2, lines +8 -= $a1.
void sub_5A0188(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x005a0188
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(a3, a0, plane::kPitch);
    lw(v1, a0, plane::kBase);
    mult(a3, a1, a3);
    lw(v0, a0, plane::kLines);
    v0 = subu(v0, a1);
    sw(v0, a0, plane::kLines);
    v1 = addu(v1, a3);
    v1 = addu(v1, a2);
    sw(v1, a0, plane::kBase);
}

// 0x005A01B0 sub_5A01B0 -- 84 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Sets the CFT word to $a1 (sub_56DED0), the mode 0 (sub_59FE50) and the record bytes (0, ($a1 & 0xFF) >> 1, $a1 &
//   0xFF) through sub_59FFC8.
void sub_5A01B0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a01b0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    a0 = s0;
    sd(ra, sp, 0x10);
    s0 = s0 & 0xFF;
    jal(ctx, 0x5A01CCu, gen::fn_sub_56DED0_0056ded0);
    a0 = s1;
    a1 = 0;
    jal(ctx, 0x5A01D8u, gen::fn_sub_59FE50_0059fe50);
    a0 = s1;
    a3 = s0;
    a2 = srl(s0, 1);
    ld(s1, sp, 0x8);
    a1 = 0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_59FFC8_0059ffc8(ctx);  // tail call
}

// 0x005A0208 sub_5A0208 -- 20 bytes; frame 0x10: ra sp+0x0
// A tail call into logl_9 (CFT's global word).
void sub_5A0208(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005a0208
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_logl_9_0056def8(ctx);  // tail call
}

// 0x005A0220 sub_5A0220 -- 20 bytes; frame 0x10: ra sp+0x0
// A tail call into sub_56DE28 at its mid entry 0x56DE78.
void sub_5A0220(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005a0220
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_56DE28_0056de28_at_0056de78(ctx);  // tail call
}

// 0x005A0250 sub_5A0250 -- 52 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Decrements the count 0x7B5058 while positive. Two chunks.
void sub_5A0250(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a0250
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x005a1168
    charge(ctx, 5);
    v0 = 0x7B0000;
    v0 = addiu(v0, 20568);  // &0x7B5058
    lw(v1, v0, 0);  // 0x7B5058
    a0 = addiu(v1, -1);
    if (i64(v1) > 0) {
        // 0x005a117c
        charge(ctx, 1);
        sw(a0, v0, 0);
    }
    // 0x005a1180 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005A02C0 sub_5A02C0 -- 8 bytes; leaf frame (no stack)
// An empty function (jr $ra).
void sub_5A02C0(EEContext& ctx) {
    using namespace hg;
    // 0x005a02c0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x005A03B0 sub_5A03B0 -- 272 bytes; frame 0x10: ra sp+0x0
// Z object init: +8 = 1, +12 = $a1, +16 = $a2 (the SFXZ data); with data, the 'ZMHDR' and 'ZMVFRM' tags of 'SFXINFE'
//   (sub_563E68) go to +24 / +28 / +32 and +40 / +44 / +48 (flag, pointer, size); without, both are flagged empty.
void sub_5A03B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a03b0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = addiu(a0, 8);
    sd(ra, sp, 0x0);
    v1 = 1;
    sw(a2, v0, 8);
    ld(ra, sp, 0x0);
    sw(v1, v0, 0);
    sw(a1, v0, 4);
    sp = addiu(sp, 0x10);
    // 0x005a03d8
    charge(ctx, 14);
    sp = addiu(sp, -0x50);
    v0 = a0;
    sd(s3, sp, 0x38);
    s3 = addiu(v0, 24);
    sd(s4, sp, 0x40);
    s4 = addiu(v0, 40);
    sd(s0, sp, 0x20);
    v1 = addiu(v0, 8);
    sd(s1, sp, 0x28);
    sd(s2, sp, 0x30);
    sd(ra, sp, 0x48);
    lw(t0, v1, 4);
    a0 = sp;
    if (t0 != 0) {
        // 0x005a0430
        charge(ctx, 28);
        s0 = 0x7D0000;
        s2 = addiu(sp, 0x10);
        lw(v0, v1, 8);
        s0 = addiu(s0, -21976);  // "SFXINFE"
        a1 = 0x7D0000;
        a2 = s0;
        a1 = addiu(a1, -21984);  // "ZMHDR"
        a3 = s2;
        sw(t0, sp, 0x0);
        s1 = 1;
        link(ctx, 0x5A0458u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x4);
        call(ctx, gen::fn_sub_563E68_00563e68);
        lw(v1, sp, 0x10);
        a1 = 0x7D0000;
        lw(v0, sp, 0x14);
        a1 = addiu(a1, -21968);  // "ZMVFRM"
        sw(v1, s3, 4);
        a2 = s0;
        sw(v0, s3, 8);
        a3 = s2;
        sw(s1, s3, 0);
        a0 = sp;
        jal(ctx, 0x5A0484u, gen::fn_sub_563E68_00563e68);
        sw(s1, s4, 0);
        lw(v0, sp, 0x10);
        lw(v1, sp, 0x14);
        sw(v0, s4, 4);
        sw(v1, s4, 8);
    } else {
        // 0x005a0410
        charge(ctx, 8);
        v0 = 1;
        sw(zero, s3, 8);
        sw(v0, s3, 0);
        sw(zero, s3, 4);
        sw(v0, s4, 0);
        sw(zero, s4, 8);
        sw(zero, s4, 4);
    }
    // 0x005a04a0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x005A0608 sub_5A0608 -- 128 bytes; frame 0x40: s0 sp+0x20, s1 sp+0x28, ra sp+0x30
// Z object lookup: when +40 is 1 and its data +44 is set, the tag ($a1, $a2) in it (sub_563E68) to *$a3 / *$t0; else
//   zeros.
void sub_5A0608(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a0608
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a0 = addiu(a0, 40);
    sd(s0, sp, 0x20);
    s0 = a3;
    sd(s1, sp, 0x28);
    s1 = t0;
    sd(ra, sp, 0x30);
    v1 = 1;
    lw(v0, a0, 0);
    if (v0 != v1) {
        sw(zero, s0, 0);
    } else {
        // 0x005a0634
        charge(ctx, 3);
        lw(v1, a0, 4);
        if (v1 == 0) {
            // 0x005a0640
            charge(ctx, 1);
            sw(zero, s0, 0);
            goto L_005a0644;
        }
        lw(v0, a0, 8);
        // 0x005a0650
        charge(ctx, 9);
        a0 = sp;
        a3 = addiu(sp, 0x10);
        sw(v1, sp, 0x0);
        link(ctx, 0x5A065Cu);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x4);
        call(ctx, gen::fn_sub_563E68_00563e68);
        lw(v1, sp, 0x10);
        lw(v0, sp, 0x14);
        sw(v1, s0, 0);
        sw(v0, s1, 0);
        // 0x005a0674 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x20);
        ld(s1, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        return;
    }
L_005a0644:
    charge(ctx, 2);
    sw(zero, s1, 0);
    // 0x005a0674 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x005A0688 sub_5A0688 -- 340 bytes; frame 0x10: ra sp+0x0
// Builds the 256-word Z ramp at $a3: 0 for 0..8, near $a1 for 9..16, near + (far - near) / 207 x (i - 17) for 17..223
//   (divu), far $a2 for 224..239, 0x7FFFFFFF for 240..255 (an INT_MIN near / far counts as 0x7FFFFFFF).
void sub_5A0688(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a0688
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x005a06a0
    charge(ctx, 10);
    v0 = lui(0x8000);
    v1 = 0x7FFF0000;
    a0 = a1 ^ v0;
    v0 = a2 ^ v0;
    v1 = v1 | 0xFFFF;
    t0 = 8;
    if (v0 == 0) a2 = v1;
    v0 = addiu(a3, 32);
    if (a0 == 0) a1 = v1;
    for (;;) {
        // 0x005a06c8
        charge(ctx, 7);
        t0 = addiu(t0, -1);
        sw(zero, v0, 0);
        v0 = addiu(v0, -4);
        if (i64(t0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005a06e4
    charge(ctx, 3);
    v0 = addiu(a3, 36);
    t0 = 7;
    for (;;) {
        // 0x005a06f0
        charge(ctx, 7);
        t0 = addiu(t0, -1);
        sw(a1, v0, 0);
        v0 = addiu(v0, 4);
        if (i64(t0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005a070c
    charge(ctx, 2);
    t0 = 17;
    if (a1 != a2) {
        // 0x005a0740
        charge(ctx, 4);
        t2 = subu(a2, a1);
        t3 = 207;
        t1 = addiu(a3, 68);
        for (;;) {
            // 0x005a0750
            charge(ctx, 5);
            divu(t2, t3);
            v1 = addiu(t0, -17);
            t0 = addiu(t0, 1);
            if (t3 == 0) {
                brk(ctx, 0x5A0760u, 0x7u);
            }
            // 0x005a0764
            charge(ctx, 7);
            a0 = slti(t0, 224);
            mflo(v0);
            mult(t4, v0, v1);
            v0 = addu(t4, a1);
            sw(v0, t1, 0);
            t1 = addiu(t1, 4);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005a0780
        charge(ctx, 1);
        v0 = addiu(a3, 896);
    } else {
        // 0x005a0714
        charge(ctx, 1);
        v1 = addiu(a3, 68);
        for (;;) {
            // 0x005a0718
            charge(ctx, 7);
            t0 = addiu(t0, 1);
            sw(a1, v1, 0);
            v0 = slti(t0, 224);
            v1 = addiu(v1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005a0734
        charge(ctx, 2);
        v0 = addiu(a3, 896);
    }
    // 0x005a0784
    charge(ctx, 1);
    t0 = 15;
    for (;;) {
        // 0x005a0788
        charge(ctx, 7);
        t0 = addiu(t0, -1);
        sw(a2, v0, 0);
        v0 = addiu(v0, 4);
        if (i64(t0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005a07a4
    charge(ctx, 5);
    v0 = 0x7FFF0000;
    a3 = addiu(a3, 960);
    v0 = v0 | 0xFFFF;
    t0 = 15;
    for (;;) {
        // 0x005a07b8
        charge(ctx, 7);
        t0 = addiu(t0, -1);
        sw(v0, a3, 0);
        a3 = addiu(a3, 4);
        if (i64(t0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005a07d4
    charge(ctx, 2);
}

// 0x005A07E0 sub_5A07E0 -- 76 bytes; frame 0x30: s1 sp+0x18, s0 sp+0x10, ra sp+0x20
// Makes a Z table: the clip pair from sub_5A04F0, then sub_5A0830.
void sub_5A07E0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a07e0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x18);
    s1 = a2;
    a3 = addiu(sp, 0x4);
    a2 = sp;
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x20);
    s0 = a0;
    jal(ctx, 0x5A07FCu, gen::fn_sub_5A04F0_005a04f0);
    lw(a1, sp, 0x0);
    a0 = s0;
    lw(a2, sp, 0x4);
    a3 = s1;
    jal(ctx, 0x5A0810u, gen::fn_sub_5A0830_005a0830);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005A0830 sub_5A0830 -- 716 bytes; frame 0x30: s4 sp+0x20, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x28
// Z table: clears 1 KiB at $a3, builds the ramp at $a3 + 1024 (sub_5A0688); a callback +68 takes over (jalr); 16-bit Z
//   (+4 == 16): halfwords ramp >> 15 when the Z mode (0x7B4DEC) is 1, else E405241; 32-bit: 2 x (ramp & 0x7FFFFF80) in
//   mode 1, else 16777215 / (+64 x ramp / 2147483500.0) per word (a zero ramp entry becomes 1).
void sub_5A0830(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005a0830
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s4, sp, 0x20);
    s4 = a3;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s3, sp, 0x18);
    s3 = addiu(s4, 1024);
    a1 = 0;
    a2 = 1024;
    sd(ra, sp, 0x28);
    a0 = s4;
    jal(ctx, 0x5A0868u, gen::fn_memset_00521408);
    a0 = s2;
    a1 = s1;
    a2 = s0;
    a3 = s3;
    jal(ctx, 0x5A087Cu, gen::fn_sub_5A0688_005a0688);
    a0 = s3;
    lw(v0, s2, 68);
    a1 = s4;
    v1 = 16;
    if (v0 != 0) {
        // 0x005a08f8
        charge(ctx, 11);
        lwc1(f13, s2, 64);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x5A08FCu);  // $ra = the return address
        lwc1(f12, s2, 60);
        call_ptr(ctx, jt);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x005a0898
    charge(ctx, 3);
    lw(v0, s2, 4);
    a0 = s2;
    if (v0 == v1) {
        // 0x005a08a4
        charge(ctx, 10);
        ld(s2, sp, 0x10);
        a1 = s3;
        ld(s3, sp, 0x18);
        a2 = s4;
        ld(s4, sp, 0x20);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        // 0x005a0928
        charge(ctx, 10);
        sp = addiu(sp, -0x20);
        sd(s0, sp, 0x0);
        s0 = a2;
        sd(s1, sp, 0x8);
        sd(ra, sp, 0x10);
        s1 = a1;
        jal(ctx, 0x5A093Cu, gen::fn___errno_15_005a0bf0);
        v1 = 1;
        if (v0 != v1) {
            a2 = 0x7D0000;
            // 0x005a0998
            charge(ctx, 8);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            a0 = 0;
            ld(ra, sp, 0x10);
            a2 = addiu(a2, -21920);
            a1 = 0;
            sp = addiu(sp, 0x20);
            gen::fn_sub_59FD10_0059fd10(ctx);  // tail call
            return;
        }
        // 0x005a0950
        charge(ctx, 4);
        a2 = s0;
        a1 = s1;
        a0 = 0;
        for (;;) {
            // 0x005a0960
            charge(ctx, 8);
            lw(v0, a1, 0);
            a1 = addiu(a1, 4);
            a0 = addiu(a0, 1);
            v0 = srl(v0, 15);
            v1 = slti(a0, 256);
            sh(v0, a2, 0);
            a2 = addiu(a2, 2);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005a0980
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x005a08d0
    charge(ctx, 10);
    ld(s2, sp, 0x10);
    a1 = s3;
    ld(s3, sp, 0x18);
    a2 = s4;
    ld(s4, sp, 0x20);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    // 0x005a09b8
    charge(ctx, 12);
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x18);
    link(ctx, 0x5A09D4u);  // $ra first: the delay slot below depends on it
    lwc1(f20, a0, 64);
    call(ctx, gen::fn___errno_15_005a0bf0);
    v1 = 1;
    a2 = 0;
    if (v0 != v1) {
        // 0x005a0a20
        charge(ctx, 8);
        at = 0x4EFF0000;
        at = at | 0xFFFF;
        mtc1(at, f3);
        at = 0x4B7F0000;
        at = at | 0xFFFF;
        mtc1(at, f2);
        t0 = 1;
        t1 = lui(0x8000);
        for (;;) {
            // 0x005a0a40
            charge(ctx, 7);
            v0 = sll(a2, 2);
            a2 = addiu(a2, 1);
            v1 = addu(v0, s1);
            a3 = slti(a2, 256);
            lw(a0, v1, 0);
            a1 = addu(v0, s0);
            if (a0 == 0) {
                // 0x005a0a5c
                charge(ctx, 2);
                sw(t0, v1, 0);
                a0 = t0;
            }
            // 0x005a0a64
            charge(ctx, 2);
            v1 = srl(a0, 1);
            if (i64(a0) < 0) {
                // 0x005a0a80
                charge(ctx, 6);
                v0 = a0 & 0x1;
                v0 = v0 | v1;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
                mul_s(f0, f20, f0);
            } else {
                // 0x005a0a6c
                charge(ctx, 4);
                mtc1(a0, f0);
                cvt_s_w(f0, f0);
                mul_s(f0, f20, f0);
            }
            // 0x005a0a98
            charge(ctx, 13);
            at = 0x4F000000;
            mtc1(at, f1);
            div_s(f0, f0, f3);
            div_s(f0, f2, f0);
            c_le_s(f1, f0);
            cvt_w_s(f4, f0);
            mfc1(v0, f4);
            if (cond(ctx)) {
                // 0x005a0acc
                charge(ctx, 4);
                sub_s(f0, f0, f1);
                cvt_w_s(f1, f0);
                mfc1(v0, f1);
                v0 = v0 | t1;
            }
            // 0x005a0adc
            charge(ctx, 2);
            sw(v0, a1, 0);
            if (a3 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005a0ae4
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    } else {
        // 0x005a09e8
        charge(ctx, 2);
        a3 = 0x7FFF0000;
        a3 = a3 | 0xFF80;
        for (;;) {
            // 0x005a09f0
            charge(ctx, 10);
            a0 = sll(a2, 2);
            a2 = addiu(a2, 1);
            v1 = addu(a0, s1);
            a0 = addu(a0, s0);
            lw(v0, v1, 0);
            a1 = slti(a2, 256);
            v0 = v0 & a3;
            v0 = sll(v0, 1);
            sw(v0, a0, 0);
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005a0a18
        charge(ctx, 2);
        ld(s0, sp, 0x0);
    }
    // 0x005a0ae8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005A0B00 sub_5A0B00 -- 100 bytes; frame 0x20: s0 sp+0x0, f21 sp+0x18, f20 sp+0x10, ra sp+0x8
// [SFXZ_SetZclip] Stores the z-clip pair ($f12 -> +60, $f13 -> +64) after the range check (sub_5A0B68); an invalid
//   pair raises E201314 first.
void sub_5A0B00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21};
    // 0x005a0b00
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    swc1(f21, sp, 0x18);
    mov_s(f21, f12);
    swc1(f20, sp, 0x10);
    sd(ra, sp, 0x8);
    mov_s(f20, f13);
    jal(ctx, 0x5A0B1Cu, gen::fn_sub_5A0B68_005a0b68);
    a2 = 0x7D0000;
    v1 = 1;
    a0 = 0;
    a2 = addiu(a2, -21856);  // "E201314: SFXZ_SetZclip : zclip is invalid."
    a1 = 0;
    if (v0 != v1) {
        // 0x005a0b3c
        charge(ctx, 2);
        jal(ctx, 0x5A0B3Cu, gen::fn_sub_59FD10_0059fd10);
    }
    // 0x005a0b44 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    swc1(f20, s0, zobj::kClipFar);
    swc1(f21, s0, zobj::kClipNear);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    lwc1(f21, sp, 0x18);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005A0B68 sub_5A0B68 -- 48 bytes; leaf frame (no stack)
// Z-clip range check: 1 unless far ($f13) <= near ($f12) or far - near < -14.0.
void sub_5A0B68(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13};
    // 0x005a0b68
    enter(ctx, 4);  // entry check point + this block's cycles
    c_le_s(f13, f12);
    v0 = 1;
    sub_s(f1, f13, f12);
    if (cond(ctx)) {
        // 0x005a0b78
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x005a0b7c
    charge(ctx, 5);
    at = lui(0xC160);
    mtc1(at, f0);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        v0 = 0;
    }
    // 0x005a0b90
    charge(ctx, 2);
}

// 0x005A0BF0 __errno_15 -- 12 bytes; leaf frame (no stack)
// The Z mode word 0x7B4DEC (FLIRT names it __errno).
void __errno_15(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x005a0bf0
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    lw(v0, v1, 19948);  // 0x7B4DEC
}

// 0x005A1088 sub_5A1088 -- 96 bytes; frame 0x10: ra sp+0x0
// [sfxcnv_CnvZbitToCft] Z bits to the CFT depth code: 16 -> 1, 24 -> 2, 32 -> 3; others raise E201313 and give 0.
void sub_5A1088(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a1088
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 16;
    sd(ra, sp, 0x0);
    a1 = sltiu(a0, 17);
    v1 = 1;
    if (a0 != v0) {
        // 0x005a10a0
        charge(ctx, 2);
        a2 = 0x7D0000;
        if (a1 == 0) {
            // 0x005a10a8
            charge(ctx, 3);
            v0 = 24;
            v1 = 2;
            if (a0 != v0) {
                // 0x005a10b4
                charge(ctx, 3);
                v0 = 32;
                v1 = 3;
                if (a0 != v0) {
                    // 0x005a10c0
                    charge(ctx, 1);
                    a2 = 0x7D0000;
                    goto L_005a10c4;
                }
            }
            // 0x005a10d8 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x0);
            v0 = v1;
            sp = addiu(sp, 0x10);
            return;
        }
    L_005a10c4:
        charge(ctx, 5);
        a0 = 0;
        a2 = addiu(a2, -21696);
        a1 = 0;
        jal(ctx, 0x5A10CCu, gen::fn_sub_59FD10_0059fd10);
        v1 = 0;
    }
    // 0x005a10d8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    v0 = v1;
    sp = addiu(sp, 0x10);
}

// 0x005A1778 sub_5A1778 -- 20 bytes; frame 0x10: ra sp+0x0
// A tail call into strtoul.
void sub_5A1778(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005a1778
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_strtoul_00525e98(ctx);  // tail call
}

}  // namespace p3fes::game
