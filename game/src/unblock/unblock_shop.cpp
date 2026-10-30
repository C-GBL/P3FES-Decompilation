// Phase 5 slice unblock, part shop (game/include/p3fes/game/unblock.h):
// the facility band 0x3E0000-0x420000 -- sequence-step hold bits, the money panel, the subtitle state, the stock
// rules of fclShopMisc.c, the SELL list builder, list groups and row enables, the sign flags, the request (Elizabeth)
// table accessors and state counters.
// These functions were kept recompiled only because other slices' pair tests stood them in with recorders; slice
// unblock rewrote those checks as guest-memory checks (docs/INTEGRATION_LOG.md, "unblock"). Started from p3fes_handgen's
// bodies (register for register, block for block as the recompiled ones; game/include/p3fes/game/hg_cpu.h): every path
// keeps the original's statements, cycle charges and check points in order; the role comments name what each does.
// Pair tests: tests/game/test_unblock.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/unblock.h"

namespace p3fes::recomp_gen {
void fn_clndGetCurrentWeekDay_0017db00(p3fes::EEContext&);
void fn_clndIsDateInRangeFromStart_0017e5d0(p3fes::EEContext&);
void fn_clndIsDateInRange_0017e480(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_nmCmdListAddRow_003c5a40(p3fes::EEContext&);
void fn_nmCmdListCancelled_003c6c80(p3fes::EEContext&);
void fn_nmCmdListClose_003c6f10(p3fes::EEContext&);
void fn_nmCmdListDecidedRow_003c6c50(p3fes::EEContext&);
void fn_nmCmdListDraw_003c6380(p3fes::EEContext&);
void fn_nmCmdListHold_003c6ea0(p3fes::EEContext&);
void fn_nmCmdListMovedDownRow_003c6ce0(p3fes::EEContext&);
void fn_nmCmdListScrolledRow_003c6d10(p3fes::EEContext&);
void fn_nmCmdListSetDrawFunc_003c5e20(p3fes::EEContext&);
void fn_nmCmdListSetPosition_003c6d40(p3fes::EEContext&);
void fn_nmCmdListSetRowDrawFunc_003c5ee0(p3fes::EEContext&);
void fn_nmCmdListSetUpdateFunc_003c5e80(p3fes::EEContext&);
void fn_nmCmdListSort_003c7000(p3fes::EEContext&);
void fn_nmCmdListUpdate_003c6270(p3fes::EEContext&);
void fn_nmListAppendNew_003c4910(p3fes::EEContext&);
void fn_nmListFindByKey_003c4b50(p3fes::EEContext&);
void fn_nmObjPayloadWord12_003c5460(p3fes::EEContext&);
void fn_nmSequenceAddStep_003c5240(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_16DBA0_0016dba0(p3fes::EEContext&);
void fn_sub_16DD50_0016dd50(p3fes::EEContext&);
void fn_sub_16DFB0_0016dfb0(p3fes::EEContext&);
void fn_sub_16E100_0016e100(p3fes::EEContext&);
void fn_sub_16F630_0016f630(p3fes::EEContext&);
void fn_sub_16F720_0016f720(p3fes::EEContext&);
void fn_sub_170760_00170760(p3fes::EEContext&);
void fn_sub_170ED0_00170ed0(p3fes::EEContext&);
void fn_sub_171110_00171110(p3fes::EEContext&);
void fn_sub_1725A0_001725a0(p3fes::EEContext&);
void fn_sub_174A90_00174a90(p3fes::EEContext&);
void fn_sub_175410_00175410(p3fes::EEContext&);
void fn_sub_17C220_0017c220(p3fes::EEContext&);
void fn_sub_17C590_0017c590(p3fes::EEContext&);
void fn_sub_17C610_0017c610(p3fes::EEContext&);
void fn_sub_17C670_0017c670(p3fes::EEContext&);
void fn_sub_17C700_0017c700(p3fes::EEContext&);
void fn_sub_17CA10_0017ca10(p3fes::EEContext&);
void fn_sub_17D030_0017d030(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_1831E0_001831e0(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_3B32D0_003b32d0(p3fes::EEContext&);
void fn_sub_3C45F0_003c45f0(p3fes::EEContext&);
void fn_sub_3C5470_003c5470(p3fes::EEContext&);
void fn_sub_3C58F0_003c58f0(p3fes::EEContext&);
void fn_sub_3C6EE0_003c6ee0(p3fes::EEContext&);
void fn_sub_3D9820_003d9820(p3fes::EEContext&);
void fn_sub_3DFF00_003dff00(p3fes::EEContext&);
void fn_sub_3E0680_003e0680(p3fes::EEContext&);
void fn_sub_3E6E20_003e6e20(p3fes::EEContext&);
void fn_sub_3EB9B0_003eb9b0(p3fes::EEContext&);
void fn_sub_3EC030_003ec030(p3fes::EEContext&);
void fn_sub_3ED380_003ed380(p3fes::EEContext&);
void fn_sub_3EE670_003ee670(p3fes::EEContext&);
void fn_sub_3EED50_003eed50(p3fes::EEContext&);
void fn_sub_3EF970_003ef970(p3fes::EEContext&);
void fn_sub_3F00B0_003f00b0(p3fes::EEContext&);
void fn_sub_3F04F0_003f04f0(p3fes::EEContext&);
void fn_sub_3F06E0_003f06e0(p3fes::EEContext&);
void fn_sub_3F0AC0_003f0ac0(p3fes::EEContext&);
void fn_sub_3F0EC0_003f0ec0(p3fes::EEContext&);
void fn_sub_3F12A0_003f12a0(p3fes::EEContext&);
void fn_sub_3F1520_003f1520(p3fes::EEContext&);
void fn_sub_3F1690_003f1690(p3fes::EEContext&);
void fn_sub_3F2240_003f2240(p3fes::EEContext&);
void fn_sub_3F5830_003f5830(p3fes::EEContext&);
void fn_sub_3F98F0_003f98f0(p3fes::EEContext&);
void fn_sub_3F99D0_003f99d0(p3fes::EEContext&);
void fn_sub_3F9E30_003f9e30(p3fes::EEContext&);
void fn_sub_3FD8A0_003fd8a0(p3fes::EEContext&);
void fn_sub_3FDF80_003fdf80(p3fes::EEContext&);
void fn_sub_3FE2B0_003fe2b0(p3fes::EEContext&);
void fn_sub_4003F0_004003f0(p3fes::EEContext&);
void fn_sub_400E90_00400e90(p3fes::EEContext&);
void fn_sub_401890_00401890(p3fes::EEContext&);
void fn_sub_401950_00401950(p3fes::EEContext&);
void fn_sub_402480_00402480(p3fes::EEContext&);
void fn_sub_403380_00403380(p3fes::EEContext&);
void fn_sub_403520_00403520(p3fes::EEContext&);
void fn_sub_403610_00403610(p3fes::EEContext&);
void fn_sub_403740_00403740(p3fes::EEContext&);
void fn_sub_4037E0_004037e0(p3fes::EEContext&);
void fn_sub_403800_00403800(p3fes::EEContext&);
void fn_sub_403830_00403830(p3fes::EEContext&);
void fn_sub_403880_00403880(p3fes::EEContext&);
void fn_sub_4038A0_004038a0(p3fes::EEContext&);
void fn_sub_403900_00403900(p3fes::EEContext&);
void fn_sub_403920_00403920(p3fes::EEContext&);
void fn_sub_404470_00404470(p3fes::EEContext&);
void fn_sub_40C170_0040c170(p3fes::EEContext&);
void fn_sub_40C310_0040c310(p3fes::EEContext&);
void fn_sub_40C490_0040c490(p3fes::EEContext&);
void fn_sub_40E3C0_0040e3c0(p3fes::EEContext&);
void fn_sub_40EB50_0040eb50(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x003EB9B0 sub_3EB9B0 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShop] Clears the "hold" bit (2) of step 7 when $a0 is 0.
void sub_3EB9B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003eb9b0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, gp, -18024);  // 0x7CE688
    jal(ctx, 0x3EB9C4u, gen::fn_nmObjPayloadWord12_003c5460);
    lw(a0, v0, 40);
    jal(ctx, 0x3EB9D0u, gen::fn_sub_3C5470_003c5470);
    if (s0 == 0) {
        // 0x003eb9e0
        charge(ctx, 4);
        lw(a0, v0, 4);
        v1 = si(-3);
        v1 = a0 & v1;
        sw(v1, v0, 4);
    }
    // 0x003eb9f0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003EC030 sub_3EC030 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShop] Clears the hold bit of step 6 when $a0 is 0.
void sub_3EC030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ec030
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, gp, -18024);  // 0x7CE688
    jal(ctx, 0x3EC044u, gen::fn_nmObjPayloadWord12_003c5460);
    lw(a0, v0, 36);
    jal(ctx, 0x3EC050u, gen::fn_sub_3C5470_003c5470);
    if (s0 == 0) {
        // 0x003ec060
        charge(ctx, 4);
        lw(a0, v0, 4);
        v1 = si(-3);
        v1 = a0 & v1;
        sw(v1, v0, 4);
    }
    // 0x003ec070 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003ED380 sub_3ED380 -- 156 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShop] Adds sequence step 11 (table 0x6A71D0) into $a0 +56.
void sub_3ED380(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003ed380
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 29136);  // &0x6A71D0
    a0 = addiu(sp, 0x30);
    v1 = 2;
    for (;;) {
        // 0x003ed3a4
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003ed3c0
    charge(ctx, 12);
    lwc1(f0, a1, 0);
    swc1(f0, a0, 0);
    lw(a0, gp, -18024);  // 0x7CE688
    a1 = 11;
    a2 = addiu(sp, 0x30);
    a3 = 0;
    t0 = 2;
    jal(ctx, 0x3ED3DCu, gen::fn_nmSequenceAddStep_003c5240);
    s1 = v0;
    if (s0 != 0) {
        // 0x003ed3f0
        charge(ctx, 1);
        sw(s1, s0, 56);
    }
    // 0x003ed3f4
    charge(ctx, 10);
    a0 = s1;
    jal(ctx, 0x3ED3F8u, gen::fn_sub_3C5470_003c5470);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003EE670 sub_3EE670 -- 680 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShop] The MONEY panel's update: the shown yen count runs towards the real one (sub_16DD50) over 5 frames with a
// sound at the start, and the panel's flags drive its slide.
void sub_3EE670(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x003ee670
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3EE684u, gen::fn_sub_16DD50_0016dd50);
    s1 = v0;
    a0 = s0;
    jal(ctx, 0x3EE694u, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    lw(v0, v0, 12);
    if (s1 == v0) {
        // 0x003ee748
        charge(ctx, 1);
        sw(s1, s0, 8);
    } else {
        // 0x003ee6ac
        charge(ctx, 3);
        lw(v0, s0, 16);
        if (v0 == 0) {
            // 0x003ee6b8
            charge(ctx, 8);
            a0 = 0;
            a1 = 0;
            a2 = 0;
            a3 = 6;
            jal(ctx, 0x3EE6C8u, gen::fn_sub_10A4E0_0010a4e0);
            v0 = 5;
            sw(v0, s0, 16);
        }
        // 0x003ee6d8
        charge(ctx, 24);
        lw(v0, s0, 16);
        v1 = addiu(v0, -1);
        sw(v1, s0, 16);
        lw(v0, s0, 12);
        v0 = subu(v0, s1);
        mult(v0, v1, v0);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x40A00000;
        mtc1(v0, f0);
        div_s(f1, f1, f0);
        mtc1(s1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        sw(v0, s0, 8);
        lw(v0, s0, 16);
        if (v0 == 0) {
            // 0x003ee738
            charge(ctx, 4);
            sw(s1, s0, 8);
            sw(s1, s0, 12);
        }
    }
    // 0x003ee74c
    charge(ctx, 4);
    lw(v1, s0, 4);
    v0 = v1 & 0x1;
    if (v0 == 0) {
        // 0x003ee7bc
        charge(ctx, 3);
        v0 = v1 & 0x2;
        if (v0 != 0) {
            // 0x003ee7c8
            charge(ctx, 17);
            lh(v0, s0, 28);
            v0 = addiu(v0, 1);
            sh(v0, s0, 28);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 10;
            div(v1, v0);
            mflo(v1);
            v0 = 255;
            v0 = subu(v0, v1);
            sh(v0, s0, 24);
            lh(v0, s0, 28);
            v0 = slti(v0, 10);
            if (v0 == 0) {
                // 0x003ee80c
                charge(ctx, 6);
                lw(v1, s0, 4);
                v0 = si(-3);
                v0 = v1 & v0;
                sw(v0, s0, 4);
                sh(zero, s0, 24);
                sh(zero, s0, 28);
            }
        }
    } else {
        // 0x003ee75c
        charge(ctx, 15);
        lh(v0, s0, 28);
        v0 = addiu(v0, 1);
        sh(v0, s0, 28);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
        v0 = sll(v1, 8);
        v1 = subu(v0, v1);
        v0 = 10;
        div(v1, v0);
        mflo(v0);
        sh(v0, s0, 24);
        lh(v0, s0, 28);
        v0 = slti(v0, 10);
        if (v0 == 0) {
            // 0x003ee798
            charge(ctx, 9);
            lw(v1, s0, 4);
            v0 = si(-2);
            v0 = v1 & v0;
            sw(v0, s0, 4);
            v0 = 255;
            sh(v0, s0, 24);
            sh(zero, s0, 28);
        }
    }
    // 0x003ee824
    charge(ctx, 4);
    lw(v1, s0, 4);
    v0 = v1 & 0x4;
    if (v0 == 0) {
        // 0x003ee894
        charge(ctx, 3);
        v0 = v1 & 0x8;
        if (v0 != 0) {
            // 0x003ee8a0
            charge(ctx, 17);
            lh(v0, s0, 30);
            v0 = addiu(v0, 1);
            sh(v0, s0, 30);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 10;
            div(v1, v0);
            mflo(v1);
            v0 = 255;
            v0 = subu(v0, v1);
            sh(v0, s0, 26);
            lh(v0, s0, 30);
            v0 = slti(v0, 10);
            if (v0 == 0) {
                // 0x003ee8e4
                charge(ctx, 6);
                lw(v1, s0, 4);
                v0 = si(-9);
                v0 = v1 & v0;
                sw(v0, s0, 4);
                sh(zero, s0, 26);
                sh(zero, s0, 30);
            }
        }
    } else {
        // 0x003ee834
        charge(ctx, 15);
        lh(v0, s0, 30);
        v0 = addiu(v0, 1);
        sh(v0, s0, 30);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
        v0 = sll(v1, 8);
        v1 = subu(v0, v1);
        v0 = 10;
        div(v1, v0);
        mflo(v0);
        sh(v0, s0, 26);
        lh(v0, s0, 30);
        v0 = slti(v0, 10);
        if (v0 == 0) {
            // 0x003ee870
            charge(ctx, 9);
            lw(v1, s0, 4);
            v0 = si(-5);
            v0 = v1 & v0;
            sw(v0, s0, 4);
            v0 = 255;
            sh(v0, s0, 26);
            sh(zero, s0, 30);
        }
    }
    // 0x003ee8fc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003EED50 sub_3EED50 -- 52 bytes; frame 0x10: ra sp+0x0
// [fclShop] The MONEY panel's shown value (step +68's +8).
void sub_3EED50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003eed50
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, -18024);  // 0x7CE688
    jal(ctx, 0x3EED5Cu, gen::fn_nmObjPayloadWord12_003c5460);
    lw(a0, v0, 68);
    jal(ctx, 0x3EED68u, gen::fn_sub_3C5470_003c5470);
    lw(v0, v0, 8);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003EF970 sub_3EF970 -- 464 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShop] Sets the shop's subtitle state by kind $a0 (flags of step +72) through a jump table.
void sub_3EF970(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ef970
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, gp, -18024);  // 0x7CE688
    jal(ctx, 0x3EF984u, gen::fn_nmObjPayloadWord12_003c5460);
    lw(a0, v0, 72);
    jal(ctx, 0x3EF990u, gen::fn_sub_3C5470_003c5470);
    at = sltiu(s0, 18);
    if (at != 0) {
        // 0x003ef9a4
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, -17104);  // &0x7BBD30
        v1 = sll(s0, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x3EF9C0u:  // table[0]
            // 0x003ef9c0
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x1;
            sw(v1, v0, 4);
            break;
        case 0x3EF9D4u:  // table[1]
            // 0x003ef9d4
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x2;
            sw(v1, v0, 4);
            break;
        case 0x3EF9E8u:  // table[2]
            // 0x003ef9e8
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x4;
            sw(v1, v0, 4);
            break;
        case 0x3EF9FCu:  // table[3]
            // 0x003ef9fc
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x8;
            sw(v1, v0, 4);
            break;
        case 0x3EFA10u:  // table[4]
            // 0x003efa10
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x10;
            sw(v1, v0, 4);
            break;
        case 0x3EFA24u:  // table[5]
            // 0x003efa24
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x20;
            sw(v1, v0, 4);
            break;
        case 0x3EFA38u:  // table[6]
            // 0x003efa38
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x40;
            sw(v1, v0, 4);
            break;
        case 0x3EFA4Cu:  // table[7]
            // 0x003efa4c
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x80;
            sw(v1, v0, 4);
            break;
        case 0x3EFA60u:  // table[8]
            // 0x003efa60
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x100;
            sw(v1, v0, 4);
            break;
        case 0x3EFA74u:  // table[9]
            // 0x003efa74
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x200;
            sw(v1, v0, 4);
            break;
        case 0x3EFA88u:  // table[10]
            // 0x003efa88
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x400;
            sw(v1, v0, 4);
            break;
        case 0x3EFA9Cu:  // table[11]
            // 0x003efa9c
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x800;
            sw(v1, v0, 4);
            break;
        case 0x3EFAB0u:  // table[12]
            // 0x003efab0
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x1000;
            sw(v1, v0, 4);
            break;
        case 0x3EFAC4u:  // table[13]
            // 0x003efac4
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x2000;
            sw(v1, v0, 4);
            break;
        case 0x3EFAD8u:  // table[14]
            // 0x003efad8
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x4000;
            sw(v1, v0, 4);
            break;
        case 0x3EFAECu:  // table[15]
            // 0x003efaec
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x8000;
            sw(v1, v0, 4);
            break;
        case 0x3EFB00u:  // table[16]
            // 0x003efb00
            charge(ctx, 6);
            lw(a0, v0, 4);
            v1 = 0x10000;
            v1 = a0 | v1;
            sw(v1, v0, 4);
            break;
        case 0x3EFB18u:  // table[17]
            // 0x003efb18
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 0x20000;
            v1 = a0 | v1;
            sw(v1, v0, 4);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x003efb28 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003F00B0 sub_3F00B0 -- 28 bytes; leaf frame (no stack)
// [fclShop] The halfword of shop $a0 in the table 0x6ACC70 (the second of each pair).
void sub_3F00B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003f00b0
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = sll(a0, 2);
    v0 = 0x6B0000;
    v0 = addiu(v0, -13198);  // &0x6ACC72
    v0 = addu(v0, v1);
    lh(v0, v0, 0);
}

// 0x003F04F0 sub_3F04F0 -- 496 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopMisc.c] [proposed: fclShopItemIsAvailable] Is a shop line available today: its weekday mask against
// clndGetCurrentWeekDay, its flag (datGetFlag), its date range (clndIsDateInRange / FromStart) by kind $a1.
void sub_3F04F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f04f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    if (s1 == 0) {
        // 0x003f0514
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 364;
        jal(ctx, 0x3F0520u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003f0528
    charge(ctx, 8);
    jal(ctx, 0x3F0528u, gen::fn_clndGetCurrentWeekDay_0017db00);
    lh(v1, s1, 0);
    s2 = 1;
    v0 = sllv(s2, v0);
    v0 = v1 & v0;
    if (v0 != 0) {
        // 0x003f0554
        charge(ctx, 3);
        lh(a0, s1, 2);
        if (a0 != 0) {
            // 0x003f0560
            charge(ctx, 4);
            jal(ctx, 0x3F0560u, gen::fn_datGetFlag_0016f190);
            if (v0 == 0) {
                // 0x003f0570
                charge(ctx, 1);
                s2 = 0;
            }
        }
        // 0x003f0574
        charge(ctx, 2);
        if (s2 != 0) {
            // 0x003f0588
            charge(ctx, 3);
            lh(v1, s1, 4);
            if (v1 != 0) {
                // 0x003f05a4
                charge(ctx, 3);
                v0 = 2;
                if (s0 != v0) {
                    // 0x003f05d8
                    charge(ctx, 6);
                    lb(v0, s1, 5);
                    v0 = dsll32(v0, 24);
                    v1 = dsra32(v0, 28);
                    v0 = 1;
                    if (v1 != v0) {
                        // 0x003f05f0
                        charge(ctx, 5);
                        a0 = 0x6B0000;
                        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                        a1 = 383;
                        jal(ctx, 0x3F05FCu, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x003f0604
                    charge(ctx, 5);
                    lb(v0, s1, 7);
                    v0 = dsll32(v0, 24);
                    v1 = dsra32(v0, 28);
                    if (v1 == 0) {
                        // 0x003f06b4
                        charge(ctx, 3);
                        v0 = 1;
                    } else {
                        // 0x003f0618
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x003f067c
                            charge(ctx, 14);
                            lh(v0, s1, 4);
                            v0 = dsll32(v0, 20);
                            a0 = dsra32(v0, 26);
                            lb(v0, s1, 4);
                            a1 = dsll32(v0, 26);
                            a1 = dsra32(a1, 26);
                            lh(v0, s1, 6);
                            a2 = dsll32(v0, 20);
                            a2 = dsra32(a2, 20);
                            jal(ctx, 0x3F06A0u, gen::fn_clndIsDateInRangeFromStart_0017e5d0);
                            v0 = sltu(0, v0);
                        } else {
                            // 0x003f0624
                            charge(ctx, 3);
                            v0 = 1;
                            if (v1 == v0) {
                                // 0x003f0638
                                charge(ctx, 17);
                                lh(v0, s1, 4);
                                v0 = dsll32(v0, 20);
                                a0 = dsra32(v0, 26);
                                lb(v0, s1, 4);
                                a1 = dsll32(v0, 26);
                                a1 = dsra32(a1, 26);
                                lh(v0, s1, 6);
                                v0 = dsll32(v0, 20);
                                a2 = dsra32(v0, 26);
                                lb(v0, s1, 6);
                                a3 = dsll32(v0, 26);
                                a3 = dsra32(a3, 26);
                                jal(ctx, 0x3F0668u, gen::fn_clndIsDateInRange_0017e480);
                                v0 = sltu(0, v0);
                            } else {
                                // 0x003f0630
                                charge(ctx, 2);
                                // 0x003f06c0
                                charge(ctx, 1);
                                v0 = 0;
                            }
                        }
                    }
                } else {
                    // 0x003f05b0
                    charge(ctx, 10);
                    v0 = dsll32(v1, 20);
                    a0 = dsra32(v0, 26);
                    lb(v0, s1, 4);
                    a1 = dsll32(v0, 26);
                    a1 = dsra32(a1, 26);
                    a2 = 365;
                    jal(ctx, 0x3F05C8u, gen::fn_clndIsDateInRangeFromStart_0017e5d0);
                }
            } else {
                // 0x003f0594
                charge(ctx, 4);
                v0 = s0 ^ 0x1;
                v0 = sltu(0, v0);
            }
        } else {
            // 0x003f057c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003f0548
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003f06c4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003F0AC0 sub_3F0AC0 -- 668 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopMisc.c] Builds the stock of shop kind $a0 (4: 3 lines, 0: 15, else 255): the available lines of the table
// 0x6AC9D0, random picks through RpRandom where the table says so.
void sub_3F0AC0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f0ac0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = 4;
    if (s0 == v0) {
        // 0x003f0b00
        charge(ctx, 3);
        s2 = 3;
    } else {
        // 0x003f0ae4
        charge(ctx, 2);
        if (s0 == 0) {
            // 0x003f0af4
            charge(ctx, 3);
            s2 = 15;
        } else {
            // 0x003f0aec
            charge(ctx, 2);
            // 0x003f0b0c
            charge(ctx, 1);
            s2 = 255;
        }
    }
    // 0x003f0b10
    charge(ctx, 2);
    if (i64(s0) >= 0) {
        // 0x003f0b18
        charge(ctx, 3);
        v0 = slti(s0, 9);
        if (v0 == 0) {
            goto L_003f0b24;
        }
        goto L_003f0b38;
    }
L_003f0b24:
    charge(ctx, 5);
    a0 = 0x6B0000;
    a0 = addiu(a0, -4632);  // "fclShopMisc.c"
    a1 = 185;
    jal(ctx, 0x3F0B30u, gen::fn_sub_19D3F0_0019d3f0);
L_003f0b38:
    charge(ctx, 4);
    jal(ctx, 0x3F0B38u, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x003f0b68
        charge(ctx, 7);
        v1 = addiu(s0, 9);
        v0 = sll(v1, 3);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13872);  // &0x6AC9D0
        v0 = addu(v0, v1);
    } else {
        // 0x003f0b48
        charge(ctx, 8);
        v0 = sll(s0, 3);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13872);  // &0x6AC9D0
        v0 = addu(v0, v1);
    }
    // 0x003f0b84
    charge(ctx, 8);
    lw(s1, v0, 32);
    a0 = addiu(s1, 12);
    a1 = 1;
    jal(ctx, 0x3F0B90u, gen::fn_sub_3F06E0_003f06e0);
    s0 = v0;
    if (s0 == 0) {
        // 0x003f0bfc
        charge(ctx, 3);
        v0 = 255;
        if (s2 != v0) {
            // 0x003f0c08
            charge(ctx, 3);
            lw(v0, s1, 8);
            if (v0 == 0) {
                // 0x003f0c14
                charge(ctx, 5);
                a0 = 0x6B0000;
                a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                a1 = 412;
                jal(ctx, 0x3F0C20u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x003f0c28
            charge(ctx, 3);
            v0 = 255;
            if (s2 != v0) {
                // 0x003f0c40
                charge(ctx, 6);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x3F0C48u, gen::fn_sub_16E100_0016e100);
                if (v0 != 0) {
                    // 0x003f0c64
                    charge(ctx, 8);
                    a0 = dsll32(s2, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x3F0C6Cu, gen::fn_sub_16DBA0_0016dba0);
                    s0 = dsll32(v0, 24);
                    s0 = dsra32(s0, 24);
                    if (s0 != 0) {
                        // 0x003f0c90
                        charge(ctx, 2);
                        if (i64(s0) > 0) {
                            // 0x003f0c98
                            charge(ctx, 3);
                            at = slti(s0, 11);
                            if (at == 0) {
                                goto L_003f0ca4;
                            }
                            goto L_003f0cb8;
                        }
                    L_003f0ca4:
                        charge(ctx, 5);
                        a0 = 0x6B0000;
                        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                        a1 = 418;
                        jal(ctx, 0x3F0CB0u, gen::fn_sub_19D3F0_0019d3f0);
                    L_003f0cb8:
                        charge(ctx, 3);
                        v1 = sll(s0, 5);
                        lw(v0, s1, 8);
                        v0 = addu(v0, v1);
                    } else {
                        // 0x003f0c84
                        charge(ctx, 3);
                        lw(v0, s1, 8);
                    }
                } else {
                    // 0x003f0c58
                    charge(ctx, 3);
                    lw(v0, s1, 8);
                }
            } else {
                // 0x003f0c34
                charge(ctx, 3);
                lw(v0, s1, 8);
            }
            // 0x003f0cc4
            charge(ctx, 2);
            if (v0 == 0) {
                goto L_003f0ce4;
            }
            // 0x003f0ccc
            charge(ctx, 4);
            lh(v0, v0, 14);
            v1 = si(-1);
            if (v0 == v1) {
                goto L_003f0ce4;
            }
            // 0x003f0cdc
            charge(ctx, 2);
            // 0x003f0d40 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_003f0ce4:
        charge(ctx, 7);
        a0 = addiu(s1, 12);
        a1 = 0;
        jal(ctx, 0x3F0CECu, gen::fn_sub_3F06E0_003f06e0);
        s0 = v0;
        if (s0 == 0) {
        L_003f0d3c:
            charge(ctx, 1);
            v0 = si(-1);
        } else {
            // 0x003f0d00
            charge(ctx, 13);
            jal(ctx, 0x3F0D00u, gen::fn_sub_488F30_00488f30);
            v1 = 0xFFFF;
            divu(v0, v1);
            mfhi(v0);
            divu(v0, v1);
            mflo(v0);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            lh(v0, v0, 8);
            v1 = si(-1);
            if (v0 == v1) {
                goto L_003f0d3c;
            }
            // 0x003f0d34
            charge(ctx, 2);
        }
    } else {
        // 0x003f0ba4
        charge(ctx, 4);
        lw(v0, s0, 0);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x003f0bb4
            charge(ctx, 3);
            a0 = 1;
            jal(ctx, 0x3F0BB8u, gen::fn_sub_3E6E20_003e6e20);
        }
        // 0x003f0bc0
        charge(ctx, 13);
        jal(ctx, 0x3F0BC0u, gen::fn_sub_488F30_00488f30);
        v1 = 0xFFFF;
        divu(v0, v1);
        mfhi(v0);
        divu(v0, v1);
        mflo(v0);
        v0 = sll(v0, 1);
        v0 = addu(v0, s0);
        lh(v0, v0, 8);
        v1 = si(-1);
        if (v0 == v1) {
            goto L_003f0d3c;
        }
        // 0x003f0bf4
        charge(ctx, 2);
    }
    // 0x003f0d40 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003F0EC0 sub_3F0EC0 -- 492 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopMisc.c] The sell / equip category of an item (sub_170ED0): by the item's kind and its flag bits.
void sub_3F0EC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f0ec0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    a1 = addiu(sp, 0x2C);
    jal(ctx, 0x3F0ED4u, gen::fn_sub_170ED0_00170ed0);
    lw(a3, sp, 0x2C);
    v1 = 4;
    if (a3 == v1) {
        // 0x003f1050
        charge(ctx, 4);
        lhu(v1, v0, 16);
        v0 = v1 & 0x10;
        if (v0 == 0) {
            // 0x003f106c
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                // 0x003f1084
                charge(ctx, 3);
                v0 = v1 & 0x4;
                if (v0 != 0) {
                    // 0x003f1090
                    charge(ctx, 1);
                    s0 = 1;
                }
            } else {
                // 0x003f1078
                charge(ctx, 3);
                s0 = 2;
            }
        } else {
            // 0x003f1060
            charge(ctx, 3);
            s0 = 3;
        }
    } else {
        // 0x003f0eec
        charge(ctx, 3);
        a2 = 3;
        if (a3 == a2) {
            // 0x003f1004
            charge(ctx, 4);
            lhu(v1, v0, 22);
            v0 = v1 & 0x10;
            if (v0 == 0) {
                // 0x003f1020
                charge(ctx, 3);
                v0 = v1 & 0x8;
                if (v0 == 0) {
                    // 0x003f1038
                    charge(ctx, 3);
                    v0 = v1 & 0x4;
                    if (v0 != 0) {
                        // 0x003f1044
                        charge(ctx, 3);
                        s0 = 1;
                    }
                } else {
                    // 0x003f102c
                    charge(ctx, 3);
                    s0 = 2;
                }
            } else {
                // 0x003f1014
                charge(ctx, 3);
                s0 = a2;
            }
        } else {
            // 0x003f0ef8
            charge(ctx, 3);
            a1 = 2;
            if (a3 == a1) {
                // 0x003f0fb8
                charge(ctx, 4);
                lhu(v1, v0, 24);
                v0 = v1 & 0x10;
                if (v0 == 0) {
                    // 0x003f0fd4
                    charge(ctx, 3);
                    v0 = v1 & 0x8;
                    if (v0 == 0) {
                        // 0x003f0fec
                        charge(ctx, 3);
                        v0 = v1 & 0x4;
                        if (v0 != 0) {
                            // 0x003f0ff8
                            charge(ctx, 3);
                            s0 = 1;
                        }
                    } else {
                        // 0x003f0fe0
                        charge(ctx, 3);
                        s0 = a1;
                    }
                } else {
                    // 0x003f0fc8
                    charge(ctx, 3);
                    s0 = a2;
                }
            } else {
                // 0x003f0f04
                charge(ctx, 3);
                a0 = 1;
                if (a3 == a0) {
                    // 0x003f0f6c
                    charge(ctx, 4);
                    lhu(v1, v0, 24);
                    v0 = v1 & 0x10;
                    if (v0 == 0) {
                        // 0x003f0f88
                        charge(ctx, 3);
                        v0 = v1 & 0x8;
                        if (v0 == 0) {
                            // 0x003f0fa0
                            charge(ctx, 3);
                            v0 = v1 & 0x4;
                            if (v0 != 0) {
                                // 0x003f0fac
                                charge(ctx, 3);
                                s0 = a0;
                            }
                        } else {
                            // 0x003f0f94
                            charge(ctx, 3);
                            s0 = a1;
                        }
                    } else {
                        // 0x003f0f7c
                        charge(ctx, 3);
                        s0 = a2;
                    }
                } else {
                    // 0x003f0f10
                    charge(ctx, 2);
                    if (a3 == 0) {
                        // 0x003f0f20
                        charge(ctx, 4);
                        lhu(v1, v0, 34);
                        v0 = v1 & 0x10;
                        if (v0 == 0) {
                            // 0x003f0f3c
                            charge(ctx, 3);
                            v0 = v1 & 0x8;
                            if (v0 == 0) {
                                // 0x003f0f54
                                charge(ctx, 3);
                                v0 = v1 & 0x4;
                                if (v0 != 0) {
                                    // 0x003f0f60
                                    charge(ctx, 3);
                                    s0 = a0;
                                }
                            } else {
                                // 0x003f0f48
                                charge(ctx, 3);
                                s0 = a1;
                            }
                        } else {
                            // 0x003f0f30
                            charge(ctx, 3);
                            s0 = a2;
                        }
                    } else {
                        // 0x003f0f18
                        charge(ctx, 2);
                    }
                }
            }
        }
    }
    // 0x003f1094 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003F12A0 sub_3F12A0 -- 460 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopMisc.c] The stock line $a1 of shop kind $a0 (4 or 0), or -1.
void sub_3F12A0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f12a0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s2 = a1;
    v0 = 4;
    if (s0 == v0) {
        // 0x003f12e4
        charge(ctx, 3);
        s1 = 3;
    L_003f12fc:
        charge(ctx, 2);
        if (i64(s0) >= 0) {
            // 0x003f1304
            charge(ctx, 3);
            v0 = slti(s0, 9);
            if (v0 == 0) {
                goto L_003f1310;
            }
            goto L_003f1324;
        }
    L_003f1310:
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 185;
        jal(ctx, 0x3F131Cu, gen::fn_sub_19D3F0_0019d3f0);
    L_003f1324:
        charge(ctx, 4);
        jal(ctx, 0x3F1324u, gen::fn_sub_17D800_0017d800);
        if (v0 != 0) {
            // 0x003f1354
            charge(ctx, 7);
            v1 = addiu(s0, 9);
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            v0 = 0x6B0000;
            v0 = addiu(v0, -13872);  // &0x6AC9D0
            v0 = addu(v0, v1);
        } else {
            // 0x003f1334
            charge(ctx, 8);
            v0 = sll(s0, 3);
            v0 = addu(v0, s0);
            v1 = sll(v0, 2);
            v0 = 0x6B0000;
            v0 = addiu(v0, -13872);  // &0x6AC9D0
            v0 = addu(v0, v1);
        }
        // 0x003f1370
        charge(ctx, 4);
        lw(s0, v0, 32);
        lw(v0, s0, 8);
        if (v0 == 0) {
            // 0x003f1380
            charge(ctx, 5);
            a0 = 0x6B0000;
            a0 = addiu(a0, -4632);  // "fclShopMisc.c"
            a1 = 412;
            jal(ctx, 0x3F138Cu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x003f1394
        charge(ctx, 3);
        v0 = 255;
        if (s1 != v0) {
            // 0x003f13ac
            charge(ctx, 6);
            a0 = dsll32(s1, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x3F13B4u, gen::fn_sub_16E100_0016e100);
            if (v0 != 0) {
                // 0x003f13d0
                charge(ctx, 8);
                a0 = dsll32(s1, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x3F13D8u, gen::fn_sub_16DBA0_0016dba0);
                s1 = dsll32(v0, 24);
                s1 = dsra32(s1, 24);
                if (s1 != 0) {
                    // 0x003f13fc
                    charge(ctx, 2);
                    if (i64(s1) > 0) {
                        // 0x003f1404
                        charge(ctx, 3);
                        at = slti(s1, 11);
                        if (at == 0) {
                            goto L_003f1410;
                        }
                        goto L_003f1424;
                    }
                L_003f1410:
                    charge(ctx, 5);
                    a0 = 0x6B0000;
                    a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                    a1 = 418;
                    jal(ctx, 0x3F141Cu, gen::fn_sub_19D3F0_0019d3f0);
                L_003f1424:
                    charge(ctx, 3);
                    v1 = sll(s1, 5);
                    lw(v0, s0, 8);
                    v1 = addu(v0, v1);
                } else {
                    // 0x003f13f0
                    charge(ctx, 3);
                    lw(v1, s0, 8);
                }
            } else {
                // 0x003f13c4
                charge(ctx, 3);
                lw(v1, s0, 8);
            }
        } else {
            // 0x003f13a0
            charge(ctx, 3);
            lw(v1, s0, 8);
        }
        // 0x003f1430
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x003f144c
            charge(ctx, 1);
            v0 = si(-1);
        } else {
            // 0x003f1438
            charge(ctx, 5);
            v0 = sll(s2, 1);
            v0 = addu(v0, v1);
            lh(v0, v0, 24);
        }
    } else {
        // 0x003f12c8
        charge(ctx, 2);
        if (s0 == 0) {
            // 0x003f12d8
            charge(ctx, 3);
            s1 = 15;
            goto L_003f12fc;
        }
        // 0x003f12d0
        charge(ctx, 2);
        // 0x003f12f0
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x003f1450 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003F1520 sub_3F1520 -- 172 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopMisc.c] Refreshes the counts of shop kind $a0 (8, 4, 0) through sub_1725A0 / sub_16DFB0.
void sub_3F1520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f1520
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v1 = 8;
    if (a0 == v1) {
        // 0x003f156c
        charge(ctx, 3);
        s0 = 2;
    L_003f1580:
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x3F1584u, gen::fn_sub_16E100_0016e100);
        if (v0 == 0) {
            // 0x003f15ac
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x3F15B0u, gen::fn_sub_16DFB0_0016dfb0);
        } else {
            // 0x003f1594
            charge(ctx, 6);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x3F159Cu, gen::fn_sub_1725A0_001725a0);
        }
    } else {
        // 0x003f1538
        charge(ctx, 3);
        v1 = 4;
        if (a0 == v1) {
            // 0x003f1560
            charge(ctx, 3);
            s0 = 3;
            goto L_003f1580;
        }
        // 0x003f1544
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x003f1554
            charge(ctx, 3);
            s0 = 15;
            goto L_003f1580;
        }
        // 0x003f154c
        charge(ctx, 2);
        // 0x003f1578
        charge(ctx, 2);
    }
    // 0x003f15b8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003F1690 sub_3F1690 -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopMisc.c] Finds the first free slot of list 1 (of 300; sub_16F630 == 0) and stores $a0 there (sub_1831E0).
// Returns the slot, or -1.
void sub_3F1690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f1690
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0;
    for (;;) {
        // 0x003f16f4
        charge(ctx, 3);
        v0 = slti(s0, 300);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f16b0
        charge(ctx, 7);
        a0 = 1;
        a1 = s0;
        jal(ctx, 0x3F16B8u, gen::fn_sub_16F630_0016f630);
        v0 = v0 & 0xFFFF;
        if (v0 == 0) {
            goto L_003f16cc_2;
        }
        // 0x003f16f0
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x003f1700
    charge(ctx, 1);
    v0 = si(-1);
    // 0x003f1704 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_003f16cc_2:
    charge(ctx, 9);
    a1 = dsll32(s0, 16);
    a1 = dsra32(a1, 16);
    a0 = 1;
    a2 = s1;
    jal(ctx, 0x3F16DCu, gen::fn_sub_1831E0_001831e0);
    v0 = s0;
    // 0x003f1704 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003F5830 sub_3F5830 -- 628 bytes; frame 0xA0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [facility] Draws a request / list row with its name (sub_3B32D0) and number.
void sub_3F5830(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x003f5830
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s5 = 5;
    lwc1(f1, gp, -21480);  // 0x7CD908
    lwc1(f0, gp, -21476);  // 0x7CD90C
    swc1(f1, sp, 0x98);
    swc1(f0, sp, 0x9C);
    s1 = 0;
    lw(v0, t0, 20);
    lw(s0, v0, 28);
    v0 = t1 & 0x1;
    if (v0 != 0) {
        // 0x003f588c
        charge(ctx, 2);
        s5 = 6;
        s1 = 1;
    }
    // 0x003f5894
    charge(ctx, 4);
    lw(v0, s0, 0);
    v0 = v0 & 0x10;
    if (v0 != 0) {
        // 0x003f58a4
        charge(ctx, 7);
        mtc1(s2, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, gp, -32624);  // 0x7CAD80
        mul_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(s2, f0);
    }
    // 0x003f58c0
    charge(ctx, 74);
    s6 = sll(s1, 1);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 133;
    t0 = s6;
    jal(ctx, 0x3F58DCu, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 134;
    t0 = s6;
    jal(ctx, 0x3F58FCu, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s4, 14);
    a1 = addiu(s3, 3);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    lw(v0, s0, 20);
    lhu(v1, v0, 2);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 1);
    lw(v0, gp, -18640);  // 0x7CE420
    v0 = addu(v1, v0);
    lbu(v0, v0, 2);
    v0 = addiu(v0, -1);
    v0 = sll(v0, 1);
    t0 = addu(s1, v0);
    a3 = 3;
    jal(ctx, 0x3F5944u, gen::fn_sub_40E3C0_0040e3c0);
    v0 = si(-256);
    s6 = s2 | v0;
    a0 = addiu(s4, 117);
    a1 = addiu(s3, 2);
    mtc1(zero, f12);
    a3 = dsll32(s5, 24);
    a3 = dsra32(a3, 24);
    lw(v0, s0, 20);
    lhu(v1, v0, 2);
    v0 = sll(v1, 4);
    v1 = addu(v0, v1);
    lw(v0, gp, -18444);  // 0x7CE4E4
    t1 = addu(v0, v1);
    a2 = s6;
    t0 = 1;
    t2 = 0;
    t3 = 120;
    jal(ctx, 0x3F5990u, gen::fn_sub_3B32D0_003b32d0);
    lw(v0, s0, 20);
    lbu(a2, v0, 4);
    a0 = addiu(sp, 0x80);
    a1 = addiu(gp, -21488);  // "%d"
    jal(ctx, 0x3F59A8u, gen::fn_sprintf_00523ac8);
    a0 = addiu(s4, 334);
    a1 = addiu(s3, 10);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    v0 = sll(s1, 2);
    v0 = addu(v0, sp);
    lw(a3, v0, 152);
    t0 = addiu(sp, 0x80);
    t1 = 1;
    jal(ctx, 0x3F59D4u, gen::fn_sub_40EB50_0040eb50);
    lh(v1, s0, 28);
    if (v1 != 0) {
        // 0x003f59e8
        charge(ctx, 26);
        a0 = addiu(s4, 350);
        a1 = addiu(s3, -1);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        lbu(v0, s0, 24);
        v0 = sll(v0, 1);
        t0 = addu(v0, s1);
        a3 = 4;
        jal(ctx, 0x3F5A08u, gen::fn_sub_40E3C0_0040e3c0);
        lh(a0, s0, 28);
        a1 = 2;
        jal(ctx, 0x3F5A18u, gen::fn_sub_171110_00171110);
        a0 = addiu(s4, 388);
        a1 = addiu(s3, 1);
        mtc1(zero, f12);
        a3 = dsll32(s5, 24);
        a3 = dsra32(a3, 24);
        a2 = s6;
        t0 = 1;
        t1 = v0;
        t2 = 0;
        t3 = 115;
        jal(ctx, 0x3F5A48u, gen::fn_sub_3B32D0_003b32d0);
    }
    // 0x003f5a50
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x003f5a58
        charge(ctx, 8);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s4;
        a1 = s3;
        a3 = 137;
        t0 = 0;
        jal(ctx, 0x3F5A70u, gen::fn_sub_40E3C0_0040e3c0);
    }
    // 0x003f5a78 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x003F9E30 sub_3F9E30 -- 664 bytes; frame 0x110: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShop] Builds the SELL list: the rows from the stock (nmCmdListAddRow), sorted, the update / draw / row-draw callbacks
// and the position set.
void sub_3F9E30(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f9e30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    a2 = 0x6B0000;
    a2 = addiu(a2, -4080);  // &0x6AF010
    a1 = addiu(sp, 0xD0);
    a0 = 8;
    for (;;) {
        // 0x003f9e5c
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f9e80
    charge(ctx, 20);
    a0 = 0;
    a1 = 88;
    a2 = 5;
    a3 = 26;
    jal(ctx, 0x3F9E90u, gen::fn_sub_3C58F0_003c58f0);
    s2 = v0;
    lw(v0, v0, 36);
    lw(v1, v0, 68);
    sh(s3, v1, 4);
    v0 = si(-1);
    sh(v0, v1, 6);
    a0 = s2;
    v0 = 0x70000;
    a1 = v0 | 0xFFFF;
    jal(ctx, 0x3F9EBCu, gen::fn_sub_3F99D0_003f99d0);
    s1 = 4000;
    for (;;) {
        // 0x003f9f64
        charge(ctx, 3);
        v0 = slti(s1, 4224);
        if (v0 != 0) {
            backedge(ctx);
            // 0x003f9ed0
            charge(ctx, 4);
            v0 = addiu(s1, -4000);
            at = slti(v0, 300);
            if (at != 0) {
                // 0x003f9ee0
                charge(ctx, 6);
                a0 = addiu(sp, 0x50);
                a1 = s1;
                jal(ctx, 0x3F9EE8u, gen::fn_sub_3F2240_003f2240);
                if (v0 != 0) {
                    // 0x003f9ef8
                    charge(ctx, 5);
                    a0 = s1 & 0xFFFF;
                    jal(ctx, 0x3F9EFCu, gen::fn_sub_3F98F0_003f98f0);
                    if (v0 != 0) {
                        // 0x003f9f0c
                        charge(ctx, 19);
                        lhu(v0, s2, 16);
                        a1 = addiu(v0, 1);
                        a0 = s2;
                        a2 = 32;
                        a3 = 0;
                        jal(ctx, 0x3F9F20u, gen::fn_nmCmdListAddRow_003c5a40);
                        lw(v0, v0, 20);
                        lw(s0, v0, 28);
                        a0 = addiu(s0, 4);
                        a1 = addiu(sp, 0x50);
                        a2 = 28;
                        jal(ctx, 0x3F9F3Cu, gen::fn_memcpy_00521250);
                        lw(v0, s0, 16);
                        v0 = sra(v0, 2);
                        sw(v0, s0, 16);
                        if (i64(v0) <= 0) {
                            // 0x003f9f58
                            charge(ctx, 2);
                            v0 = 1;
                            sw(v0, s0, 16);
                        }
                    }
                }
                // 0x003f9f60
                charge(ctx, 1);
                s1 = addiu(s1, 1);
                continue;
            }
        }
        break;
    }
    // 0x003f9f70
    charge(ctx, 13);
    a0 = s2;
    a1 = 0x400000;
    a1 = addiu(a1, -25424);  // &sub_3F9CB0
    a2 = 0;
    jal(ctx, 0x3F9F80u, gen::fn_nmCmdListSort_003c7000);
    a0 = s2;
    jal(ctx, 0x3F9F8Cu, gen::fn_sub_3C6EE0_003c6ee0);
    a2 = 0x6B0000;
    a2 = addiu(a2, -4016);  // &0x6AF050
    a1 = addiu(sp, 0xB0);
    a0 = 4;
    for (;;) {
        // 0x003f9fa4
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f9fc8
    charge(ctx, 4);
    a2 = 0x6B0000;
    a2 = addiu(a2, -3984);  // &0x6AF070
    a1 = addiu(sp, 0x90);
    a0 = 4;
    for (;;) {
        // 0x003f9fd8
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f9ffc
    charge(ctx, 4);
    a2 = 0x6B0000;
    a2 = addiu(a2, -3952);  // &0x6AF090
    a1 = addiu(sp, 0x70);
    a0 = 4;
    for (;;) {
        // 0x003fa00c
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003fa030
    charge(ctx, 38);
    s0 = sll(s3, 2);
    v0 = addu(s0, sp);
    a0 = s2;
    lw(a1, v0, 176);
    jal(ctx, 0x3FA040u, gen::fn_nmCmdListSetUpdateFunc_003c5e80);
    v0 = addu(s0, sp);
    a0 = s2;
    lw(a1, v0, 144);
    jal(ctx, 0x3FA054u, gen::fn_nmCmdListSetDrawFunc_003c5e20);
    v0 = addu(s0, sp);
    a0 = s2;
    lw(a1, v0, 112);
    jal(ctx, 0x3FA068u, gen::fn_nmCmdListSetRowDrawFunc_003c5ee0);
    v0 = sll(s3, 3);
    v0 = addu(v0, sp);
    a0 = s2;
    lw(a1, v0, 208);
    lw(a2, v0, 212);
    jal(ctx, 0x3FA084u, gen::fn_nmCmdListSetPosition_003c6d40);
    v1 = 20;
    lw(v0, s2, 36);
    sh(v1, v0, 6);
    v1 = 10;
    lw(v0, s2, 36);
    sh(v1, v0, 8);
    v0 = s2;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x110);
}

// 0x003FD8A0 sub_3FD8A0 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShop] Releases that object: its BG node, then the list object.
void sub_3FD8A0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fd8a0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 8);
    jal(ctx, 0x3FD8B4u, gen::fn_sub_3DFF00_003dff00);
    lw(a0, s0, 0);
    jal(ctx, 0x3FD8C0u, gen::fn_sub_3C45F0_003c45f0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003FDF80 sub_3FDF80 -- 148 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShop] Draws the list group: the BG of the object, then every child's BG and command list.
void sub_3FDF80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fdf80
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(a0, a0, 8);
    a1 = 0x400000;
    a1 = addiu(a1, -9024);  // &sub_3FDCC0
    a2 = s2;
    jal(ctx, 0x3FDFA8u, gen::fn_sub_3E0680_003e0680);
    lw(v0, s2, 0);
    lw(s1, v0, 4);
    for (;;) {
        // 0x003fdfec
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003fdfc0
        charge(ctx, 11);
        lw(s0, s1, 20);
        lw(a0, s0, 8);
        a1 = 0x400000;
        a1 = addiu(a1, -9024);  // &sub_3FDCC0
        a2 = s2;
        jal(ctx, 0x3FDFD4u, gen::fn_sub_3E0680_003e0680);
        lw(a0, s0, 4);
        jal(ctx, 0x3FDFE0u, gen::fn_nmCmdListDraw_003c6380);
        lw(s1, s1, 16);
    }
    // 0x003fdff4
    charge(ctx, 8);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003FE2B0 sub_3FE2B0 -- 296 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShop] Counts the item groups of the table 0x6AF180 held (sub_170760) / flagged (sub_16F720).
void sub_3FE2B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fe2b0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    for (;;) {
        // 0x003fe2f4
        charge(ctx, 4);
        a2 = 0x6B0000;
        a2 = addiu(a2, -3712);  // &0x6AF180
        a1 = addiu(sp, 0x20);
        a0 = 4;
        for (;;) {
            // 0x003fe304
            charge(ctx, 9);
            lh(v1, a2, 0);
            lh(v0, a2, 2);
            a2 = addiu(a2, 4);
            a0 = addiu(a0, -1);
            sh(v1, a1, 0);
            sh(v0, a1, 2);
            a1 = addiu(a1, 4);
            if (i64(a0) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x003fe328
        charge(ctx, 3);
        v0 = sltiu(s0, 8);
        if (v0 != 0) {
            // 0x003fe340
            charge(ctx, 3);
            v0 = sll(s0, 1);
            v0 = addu(v0, sp);
            lhu(v0, v0, 32);
        } else {
            // 0x003fe334
            charge(ctx, 3);
            v0 = 0;
        }
        // 0x003fe34c
        charge(ctx, 3);
        v0 = v0 & 0xFFFF;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003fe2c8
        charge(ctx, 7);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = 1;
        jal(ctx, 0x3FE2D4u, gen::fn_sub_170760_00170760);
        if (v0 != 0) {
            goto L_003fe2e4_2;
        }
        // 0x003fe2f0
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x003fe358
    charge(ctx, 1);
    v0 = 0;
L_003fe35c:
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x003fe370
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x003fe3ac
            charge(ctx, 5);
            a1 = dsll32(s0, 16);
            a1 = dsra32(a1, 16);
            v0 = slti(a1, 300);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003fe37c
            charge(ctx, 6);
            a0 = 1;
            jal(ctx, 0x3FE380u, gen::fn_sub_16F720_0016f720);
            v0 = v0 & 0xFF00;
            if (v0 != 0) {
                goto L_003fe394_15;
            }
            // 0x003fe3a0
            charge(ctx, 3);
            v0 = addiu(s0, 1);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
        }
        // 0x003fe3c0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003fe364
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x003fe3c4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_003fe2e4_2:
    charge(ctx, 3);
    v0 = 1;
    goto L_003fe35c;
L_003fe394_15:
    charge(ctx, 3);
    v0 = 1;
    // 0x003fe3c4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004003F0 sub_4003F0 -- 660 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShop] A shop list step: update, decided row (sound, hold), cancel, scroll and move-down handling; -1 when the list
// closed.
void sub_4003F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004003f0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(s4, a0, 0);
    a0 = s4;
    jal(ctx, 0x40041Cu, gen::fn_nmCmdListUpdate_003c6270);
    v1 = 2;
    if (v0 != v1) {
        // 0x0040043c
        charge(ctx, 7);
        lw(s1, s4, 12);
        a0 = s4;
        jal(ctx, 0x400444u, gen::fn_nmCmdListDecidedRow_003c6c50);
        s0 = v0;
        if (s0 == 0) {
            // 0x00400524
            charge(ctx, 5);
            a0 = s4;
            jal(ctx, 0x400528u, gen::fn_nmCmdListCancelled_003c6c80);
            if (v0 == 0) {
                // 0x004005c4
                charge(ctx, 5);
                a0 = s4;
                jal(ctx, 0x4005C8u, gen::fn_nmCmdListMovedDownRow_003c6ce0);
                if (v0 == 0) {
                    // 0x004005d8
                    charge(ctx, 5);
                    a0 = s4;
                    jal(ctx, 0x4005DCu, gen::fn_nmCmdListScrolledRow_003c6d10);
                    if (v0 != 0) {
                        goto L_004005ec;
                    }
                    goto L_00400658;
                }
            L_004005ec:
                charge(ctx, 27);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x4005FCu, gen::fn_sub_10A4E0_0010a4e0);
                lw(s4, s1, 0);
                lw(v0, s1, 20);
                lw(s2, v0, 4);
                lw(s1, v0, 0);
                lw(a0, s3, 4);
                lw(s0, a0, 36);
                lhu(v0, a0, 16);
                a1 = addiu(v0, 1);
                a2 = 20;
                jal(ctx, 0x400628u, gen::fn_nmListAppendNew_003c4910);
                lw(v1, v0, 20);
                sh(s1, v1, 4);
                sh(s2, v1, 6);
                sh(s4, v1, 8);
                v0 = 1;
                sh(v0, v1, 14);
                lw(v0, s0, 0);
                sw(v0, v1, 16);
                v0 = 7;
                sh(v0, v1, 12);
            L_00400658:
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x00400538
                charge(ctx, 35);
                a0 = s4;
                jal(ctx, 0x40053Cu, gen::fn_nmCmdListHold_003c6ea0);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 2;
                jal(ctx, 0x400554u, gen::fn_sub_10A4E0_0010a4e0);
                a0 = s4;
                jal(ctx, 0x400560u, gen::fn_nmCmdListClose_003c6f10);
                lw(s2, s1, 0);
                lw(v0, s1, 20);
                lw(s1, v0, 4);
                lw(s0, v0, 0);
                lw(a0, s3, 4);
                lw(s3, a0, 36);
                lhu(v0, a0, 16);
                a1 = addiu(v0, 1);
                a2 = 20;
                jal(ctx, 0x40058Cu, gen::fn_nmListAppendNew_003c4910);
                lw(v1, v0, 20);
                sh(s0, v1, 4);
                sh(s1, v1, 6);
                sh(s2, v1, 8);
                sh(zero, v1, 14);
                lw(v0, s3, 0);
                sw(v0, v1, 16);
                v0 = 5;
                sh(v0, v1, 12);
                v0 = 4;
            }
        } else {
            // 0x00400458
            charge(ctx, 6);
            lw(v0, s0, 20);
            lw(v0, v0, 28);
            lw(v0, v0, 0);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x00400494
                charge(ctx, 36);
                a0 = s4;
                jal(ctx, 0x400498u, gen::fn_nmCmdListHold_003c6ea0);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 1;
                jal(ctx, 0x4004B0u, gen::fn_sub_10A4E0_0010a4e0);
                lw(s2, s0, 0);
                a0 = s4;
                jal(ctx, 0x4004C0u, gen::fn_nmCmdListClose_003c6f10);
                lw(s0, s1, 0);
                lw(v0, s1, 20);
                lw(s5, v0, 4);
                lw(s4, v0, 0);
                lw(a0, s3, 4);
                lw(s1, a0, 36);
                lhu(v0, a0, 16);
                a1 = addiu(v0, 1);
                a2 = 20;
                jal(ctx, 0x4004ECu, gen::fn_nmListAppendNew_003c4910);
                lw(v1, v0, 20);
                sh(s4, v1, 4);
                sh(s5, v1, 6);
                sh(s0, v1, 8);
                sh(zero, v1, 14);
                lw(v0, s1, 0);
                sw(v0, v1, 16);
                v0 = 5;
                sh(v0, v1, 12);
                v0 = s2;
            } else {
                // 0x00400470
                charge(ctx, 9);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 8;
                jal(ctx, 0x400480u, gen::fn_sub_10A4E0_0010a4e0);
                v0 = 0;
            }
        }
    } else {
        // 0x00400430
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x0040065c (the shared epilogue, written out on this path)
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

// 0x00400E90 sub_400E90 -- 732 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopMisc.c] Fills a shop list from its key table through nmListFindByKey (callbacks through function pointers).
void sub_400E90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00400e90
    enter(ctx, 16);  // entry check point + this block's cycles
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
    lw(s4, a0, 8);
    lw(a0, a0, 0);
    v1 = a0 & 0x1;
    if (v1 != 0) {
        // 0x00400ed0
        charge(ctx, 3);
        v1 = a0 & 0x2;
        if (v1 != 0) {
            // 0x00400edc
            charge(ctx, 10);
            lw(a1, s5, 16);
            lw(v1, s5, 20);
            a0 = sll(v1, 3);
            lw(v1, a1, 0);
            s6 = addu(v1, a0);
            lw(s7, s6, 0);
            s1 = 0;
            s2 = 0;
            for (;;) {
                // 0x00400fec
                charge(ctx, 4);
                lw(a0, s6, 4);
                v1 = slt(s2, a0);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00400f04
                charge(ctx, 6);
                v1 = sll(s2, 3);
                s0 = addu(s7, v1);
                lw(a0, s5, 4);
                lw(v1, s0, 0);
                if (a0 == v1) {
                    // 0x00400f1c
                    charge(ctx, 11);
                    lh(v0, s0, 4);
                    a2 = addiu(v0, 1);
                    a0 = s4;
                    a1 = addiu(s4, 4);
                    jal(ctx, 0x400F2Cu, gen::fn_nmListFindByKey_003c4b50);
                    lw(s3, v0, 20);
                    lw(a0, s3, 0);
                    v0 = a0 & 0x1;
                    if (v0 != 0) {
                        // 0x00400f60
                        charge(ctx, 4);
                        lh(v1, s0, 6);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x00400f78
                            charge(ctx, 6);
                            v0 = si(-2);
                            v1 = a0 & v0;
                            sw(v1, s3, 0);
                            v0 = si(-3);
                            v0 = v1 & v0;
                            sw(v0, s3, 0);
                        } else {
                            // 0x00400f70
                            charge(ctx, 2);
                        }
                    } else {
                        // 0x00400f48
                        charge(ctx, 6);
                        v0 = a0 | 0x1;
                        sw(v0, s3, 0);
                        v0 = v0 | 0x2;
                        sw(v0, s3, 0);
                    }
                    // 0x00400f90
                    charge(ctx, 4);
                    lw(v0, s3, 8);
                    lw(v0, v0, 0);
                    if (v0 == 0) {
                        // 0x00400fa0
                        charge(ctx, 5);
                        a0 = 0x6B0000;
                        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                        a1 = 6442;
                        jal(ctx, 0x400FACu, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x00400fb4
                    charge(ctx, 7);
                    a0 = s5;
                    a1 = s3;
                    a2 = s0;
                    lw(v0, s3, 8);
                    lw(v0, v0, 0);
                    jalr(ctx, 0x400FC8u, v0.u());
                }
                // 0x00400fd0
                charge(ctx, 5);
                lw(a0, s0, 0);
                lw(v1, s5, 4);
                at = slt(v1, a0);
                if (at == 0) {
                    // 0x00400fe4
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                }
                // 0x00400fe8
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00400ffc
            charge(ctx, 2);
            if (s1 == a0) {
                // 0x00401004
                charge(ctx, 4);
                lw(a0, s5, 0);
                v1 = si(-3);
                v1 = a0 & v1;
                sw(v1, s5, 0);
            }
        }
        // 0x00401014
        charge(ctx, 4);
        s1 = 0;
        lw(s2, s4, 4);
        for (;;) {
            // 0x004010d8
            charge(ctx, 2);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00401024
            charge(ctx, 5);
            lw(s0, s2, 20);
            lw(v1, s0, 0);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x00401038
                charge(ctx, 10);
                a0 = s5;
                a1 = s0;
                a2 = 0;
                lw(v0, s0, 8);
                lw(v0, v0, 0);
                jalr(ctx, 0x40104Cu, v0.u());
                v1 = 2;
                if (v0 == v1) {
                    // 0x004010a0
                    charge(ctx, 4);
                    lw(a0, s0, 0);
                    v1 = si(-2);
                    v1 = a0 & v1;
                    sw(v1, s0, 0);
                } else {
                    // 0x00401060
                    charge(ctx, 3);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x00401088
                        charge(ctx, 6);
                        lw(a0, s0, 0);
                        v1 = si(-3);
                        v1 = a0 & v1;
                        sw(v1, s0, 0);
                    } else {
                        // 0x0040106c
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x0040107c
                            charge(ctx, 3);
                            s1 = v1;
                        } else {
                            // 0x00401074
                            charge(ctx, 2);
                        }
                    }
                }
            }
            // 0x004010b0
            charge(ctx, 8);
            lw(v1, s0, 4);
            a1 = addiu(v1, 1);
            sw(a1, s0, 4);
            v1 = 0xFFF0000;
            a0 = v1 | 0xFFFF;
            v1 = slt(a1, a0);
            if (v1 == 0) {
                // 0x004010d0
                charge(ctx, 1);
                sw(a0, s0, 4);
            }
            // 0x004010d4
            charge(ctx, 1);
            lw(s2, s2, 16);
        }
        // 0x004010e0
        charge(ctx, 8);
        lw(v1, s5, 4);
        a1 = addiu(v1, 1);
        sw(a1, s5, 4);
        v1 = 0xFFF0000;
        a0 = v1 | 0xFFFF;
        v1 = slt(a1, a0);
        if (v1 == 0) {
            // 0x00401100
            charge(ctx, 1);
            sw(a0, s5, 4);
        }
        // 0x00401104
        charge(ctx, 4);
        lw(a0, s5, 0);
        v1 = a0 & 0x4;
        if (v1 != 0) {
            // 0x00401114
            charge(ctx, 2);
            if (s1 == 0) {
                // 0x0040111c
                charge(ctx, 8);
                v1 = si(-5);
                v1 = a0 & v1;
                sw(v1, s5, 0);
                v1 = v1 | 0x2;
                sw(v1, s5, 0);
                lw(v1, s5, 24);
                sw(v1, s5, 20);
                sw(zero, s5, 4);
            }
        }
    }
    // 0x0040113c (the shared epilogue, written out on this path)
    charge(ctx, 12);
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

// 0x00401890 sub_401890 -- 184 bytes; frame 0x40: ra sp+0x0
// [fclShop] Is shop sign $a0 lit: the flag of its entry in the 12-pair table 0x6AF3A0.
void sub_401890(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00401890
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x0);
    a3 = 0x6B0000;
    a3 = addiu(a3, -3168);  // &0x6AF3A0
    a2 = addiu(sp, 0x10);
    a1 = 12;
    for (;;) {
        // 0x004018a8
        charge(ctx, 9);
        lh(v1, a3, 0);
        lh(v0, a3, 2);
        a3 = addiu(a3, 4);
        a1 = addiu(a1, -1);
        sh(v1, a2, 0);
        sh(v0, a2, 2);
        a2 = addiu(a2, 4);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004018cc
    charge(ctx, 4);
    a1 = 0;
    v1 = a0 & 0xFFFF;
    for (;;) {
        // 0x00401900
        charge(ctx, 3);
        v0 = sltiu(a1, 24);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x004018dc
        charge(ctx, 5);
        v0 = sll(a1, 1);
        v0 = addu(v0, sp);
        lhu(v0, v0, 16);
        if (v1 == v0) {
            goto L_004018f0_4;
        }
        // 0x004018fc
        charge(ctx, 1);
        a1 = addiu(a1, 1);
    }
    // 0x0040190c
    charge(ctx, 1);
    a0 = 0;
L_00401910:
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x00401918
        charge(ctx, 4);
        jal(ctx, 0x401918u, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            goto L_00401934;
        }
        // 0x00401928
        charge(ctx, 3);
        v0 = 1;
        // 0x00401938 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_00401934:
    charge(ctx, 1);
    v0 = 0;
    // 0x00401938 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_004018f0_4:
    charge(ctx, 3);
    a0 = addiu(a1, 4736);
    goto L_00401910;
}

// 0x00401950 sub_401950 -- 168 bytes; frame 0x40: ra sp+0x0
// [fclShop] Sets the flag of shop sign $a0 from the table 0x6AF3A0.
void sub_401950(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00401950
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x0);
    a3 = 0x6B0000;
    a3 = addiu(a3, -3168);  // &0x6AF3A0
    a2 = addiu(sp, 0x10);
    a1 = 12;
    for (;;) {
        // 0x00401968
        charge(ctx, 9);
        lh(v1, a3, 0);
        lh(v0, a3, 2);
        a3 = addiu(a3, 4);
        a1 = addiu(a1, -1);
        sh(v1, a2, 0);
        sh(v0, a2, 2);
        a2 = addiu(a2, 4);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0040198c
    charge(ctx, 4);
    a1 = 0;
    v1 = a0 & 0xFFFF;
    for (;;) {
        // 0x004019c0
        charge(ctx, 3);
        v0 = sltiu(a1, 24);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0040199c
        charge(ctx, 5);
        v0 = sll(a1, 1);
        v0 = addu(v0, sp);
        lhu(v0, v0, 16);
        if (v1 == v0) {
            goto L_004019b0_4;
        }
        // 0x004019bc
        charge(ctx, 1);
        a1 = addiu(a1, 1);
    }
    // 0x004019cc
    charge(ctx, 1);
    a0 = 0;
L_004019d0:
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x004019d8
        charge(ctx, 3);
        a1 = 1;
        jal(ctx, 0x4019DCu, gen::fn_datSetFlag_0016f1f0);
    }
    // 0x004019e4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_004019b0_4:
    charge(ctx, 3);
    a0 = addiu(a1, 4736);
    goto L_004019d0;
}

// 0x00402480 sub_402480 -- 132 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShop] Is the request record ($a0, or a stack copy from sub_17C220) dated within a year (clndIsDateInRangeFromStart):
// 1 / -1, 0 when unused.
void sub_402480(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00402480
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 == 0) {
        // 0x00402498
        charge(ctx, 1);
        s0 = addiu(sp, 0x20);
    }
    // 0x0040249c
    charge(ctx, 7);
    a0 = s0;
    jal(ctx, 0x4024A0u, gen::fn_sub_17C220_0017c220);
    lh(v0, s0, 0);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x004024c4
        charge(ctx, 7);
        lb(a0, s0, 2);
        lb(a1, s0, 3);
        a2 = 365;
        jal(ctx, 0x4024D0u, gen::fn_clndIsDateInRangeFromStart_0017e5d0);
        if (v0 == 0) {
            // 0x004024ec
            charge(ctx, 1);
            v0 = si(-1);
        } else {
            // 0x004024e0
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x004024b8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x004024f0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00403380 sub_403380 -- 140 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclRequest] [proposed: fclRequestGetState] A request's state: 3 done (flag 4464 + id), 2 not available
// (sub_3F04F0), else 1 / 0 by sub_17C610.
void sub_403380(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00403380
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = dsll32(s0, 16);
    v0 = dsra32(v0, 16);
    a0 = addiu(v0, 4464);
    jal(ctx, 0x40339Cu, gen::fn_datGetFlag_0016f190);
    if (v0 == 0) {
        // 0x004033b8
        charge(ctx, 9);
        a0 = s0;
        jal(ctx, 0x4033BCu, gen::fn_sub_4037E0_004037e0);
        a0 = v0;
        a1 = 0;
        jal(ctx, 0x4033CCu, gen::fn_sub_3F04F0_003f04f0);
        if (v0 == 0) {
            // 0x004033f4
            charge(ctx, 1);
            v0 = 2;
        } else {
            // 0x004033dc
            charge(ctx, 6);
            a0 = s0;
            jal(ctx, 0x4033E0u, gen::fn_sub_17C610_0017c610);
            v0 = sltu(0, v0);
        }
    } else {
        // 0x004033ac
        charge(ctx, 3);
        v0 = 3;
    }
    // 0x004033f8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00403520 sub_403520 -- 236 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclRequest] Counts the three active requests by state.
void sub_403520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00403520
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    for (;;) {
        // 0x004035e4
        charge(ctx, 3);
        v0 = slti(s1, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0040353c
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x403540u, gen::fn_sub_17C670_0017c670);
        if (v0 != 0) {
            // 0x00403550
            charge(ctx, 6);
            lh(s0, v0, 0);
            a0 = addiu(s0, 4464);
            jal(ctx, 0x403558u, gen::fn_datGetFlag_0016f190);
            if (v0 == 0) {
                // 0x00403574
                charge(ctx, 9);
                a0 = s0;
                jal(ctx, 0x403578u, gen::fn_sub_4037E0_004037e0);
                a0 = v0;
                a1 = 0;
                jal(ctx, 0x403588u, gen::fn_sub_3F04F0_003f04f0);
                if (v0 == 0) {
                    // 0x004035b8
                    charge(ctx, 3);
                    v1 = 2;
                } else {
                    // 0x00403598
                    charge(ctx, 5);
                    a0 = s0;
                    jal(ctx, 0x40359Cu, gen::fn_sub_17C610_0017c610);
                    if (v0 == 0) {
                        // 0x004035c4
                        charge(ctx, 1);
                        v1 = 0;
                    } else {
                        // 0x004035ac
                        charge(ctx, 3);
                        v1 = 1;
                    }
                }
            } else {
                // 0x00403568
                charge(ctx, 3);
                v1 = 3;
            }
            // 0x004035c8
            charge(ctx, 3);
            v0 = 2;
            if (v1 != v0) {
                goto L_004035e0;
            }
            goto L_004035d4_10;
        }
    L_004035e0:
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x004035f0
    charge(ctx, 1);
    v0 = 0;
    // 0x004035f4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_004035d4_10:
    charge(ctx, 3);
    v0 = 1;
    // 0x004035f4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00403610 sub_403610 -- 300 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclRequest] Retires active requests that are no longer available (state 2) through sub_17C590 / sub_404470.
void sub_403610(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00403610
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    s0 = 0;
    for (;;) {
        // 0x0040370c
        charge(ctx, 3);
        v0 = slti(s1, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00403638
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x40363Cu, gen::fn_sub_17C670_0017c670);
        s2 = v0;
        if (s2 != 0) {
            // 0x00403650
            charge(ctx, 6);
            lh(s3, s2, 0);
            a0 = addiu(s3, 4464);
            jal(ctx, 0x403658u, gen::fn_datGetFlag_0016f190);
            if (v0 == 0) {
                // 0x00403674
                charge(ctx, 9);
                a0 = s3;
                jal(ctx, 0x403678u, gen::fn_sub_4037E0_004037e0);
                a0 = v0;
                a1 = 0;
                jal(ctx, 0x403688u, gen::fn_sub_3F04F0_003f04f0);
                if (v0 == 0) {
                    // 0x004036b8
                    charge(ctx, 3);
                    v1 = 2;
                } else {
                    // 0x00403698
                    charge(ctx, 5);
                    a0 = s3;
                    jal(ctx, 0x40369Cu, gen::fn_sub_17C610_0017c610);
                    if (v0 == 0) {
                        // 0x004036c4
                        charge(ctx, 1);
                        v1 = 0;
                    } else {
                        // 0x004036ac
                        charge(ctx, 3);
                        v1 = 1;
                    }
                }
            } else {
                // 0x00403668
                charge(ctx, 3);
                v1 = 3;
            }
            // 0x004036c8
            charge(ctx, 3);
            v0 = 2;
            if (v1 != v0) {
                goto L_00403708;
            }
            // 0x004036d4
            charge(ctx, 13);
            lh(s1, s2, 0);
            a0 = s1;
            jal(ctx, 0x4036DCu, gen::fn_sub_17C590_0017c590);
            a0 = dsll32(s1, 16);
            a0 = dsra32(a0, 16);
            a1 = 0;
            jal(ctx, 0x4036F0u, gen::fn_sub_404470_00404470);
            s0 = addiu(s0, 1);
            s1 = 0;
            continue;
        }
    L_00403708:
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00403718
    charge(ctx, 9);
    v0 = s0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00403740 sub_403740 -- 32 bytes; leaf frame (no stack)
// [fclRequest] The request table 0x7CD8F0 (64-byte records): halfword +58 of request $a0.
void sub_403740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00403740
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v1, gp, -21504);  // 0x7CD8F0
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 6);
    v0 = addu(v0, v1);
    lh(v0, v0, 58);
}

// 0x00403800 sub_403800 -- 40 bytes; leaf frame (no stack)
// [fclRequest] Bits 6..11 of the halfword +14 of request $a0, signed.
void sub_403800(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00403800
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v1 = sll(v0, 6);
    lw(v0, gp, -21504);  // 0x7CD8F0
    v0 = addu(v0, v1);
    lh(v0, v0, 14);
    v0 = dsll32(v0, 20);
    v0 = dsra32(v0, 26);
}

// 0x00403830 sub_403830 -- 40 bytes; leaf frame (no stack)
// [fclRequest] Bits 0..5 of the byte +14 of request $a0, signed.
void sub_403830(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00403830
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v1 = sll(v0, 6);
    lw(v0, gp, -21504);  // 0x7CD8F0
    v0 = addu(v0, v1);
    lb(v0, v0, 14);
    v0 = dsll32(v0, 26);
    v0 = dsra32(v0, 26);
}

// 0x00403880 sub_403880 -- 32 bytes; leaf frame (no stack)
// [fclRequest] The address of request $a0's reward block (+32).
void sub_403880(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00403880
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v1 = sll(v0, 6);
    lw(v0, gp, -21504);  // 0x7CD8F0
    v0 = addu(v0, v1);
    v0 = addiu(v0, 32);
}

// 0x004038A0 sub_4038A0 -- 64 bytes; leaf frame (no stack)
// [fclRequest] The reward item of request $a0 when its reward kind (+38) is 3, else 0.
void sub_4038A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004038a0
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v1 = sll(v0, 6);
    lw(v0, gp, -21504);  // 0x7CD8F0
    v0 = addu(v0, v1);
    a0 = addiu(v0, 32);
    lbu(v1, v0, 38);
    v0 = 3;
    if (v1 != v0) {
        // 0x004038d4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004038c8
        charge(ctx, 3);
        lw(v0, a0, 8);
    }
    // 0x004038d8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00403900 sub_403900 -- 32 bytes; leaf frame (no stack)
// [fclRequest] Halfword +60 of request $a0.
void sub_403900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00403900
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v1, gp, -21504);  // 0x7CD8F0
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 6);
    v0 = addu(v0, v1);
    lh(v0, v0, 60);
}

// 0x00403920 sub_403920 -- 80 bytes; leaf frame (no stack)
// [fclRequest] Does request $a0 ask for item $a1: kind byte +26 == 1 and halfword +28 == $a1.
void sub_403920(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x00403920
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v1 = sll(v0, 6);
    lw(v0, gp, -21504);  // 0x7CD8F0
    v0 = addu(v0, v1);
    a0 = addiu(v0, 16);
    lbu(v1, v0, 26);
    v0 = 1;
    if (v1 == v0) {
        // 0x00403948
        charge(ctx, 5);
        lh(a0, a0, 12);
        v1 = dsll32(a1, 16);
        v1 = dsra32(v1, 16);
        if (a0 != v1) {
            goto L_00403964;
        }
        // 0x0040395c
        charge(ctx, 2);
        // 0x00403968 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00403964:
    charge(ctx, 1);
    v0 = 0;
    // 0x00403968 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0040C170 sub_40C170 -- 100 bytes; frame 0x10: ra sp+0x0
// [facility] Maps the current value of sub_17D030 to an entry of the run-length table 0x6AEDC0.
void sub_40C170(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040c170
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x40C178u, gen::fn_sub_17D030_0017d030);
    a2 = 0;
    a1 = 0x6B0000;
    a1 = addiu(a1, -4672);  // &0x6AEDC0
    for (;;) {
        // 0x0040c18c
        charge(ctx, 6);
        v1 = sll(a2, 3);
        a0 = addu(a1, v1);
        lw(v1, a0, 4);
        at = sltu(v1, v0);
        if (at == 0) {
            goto L_0040c1a4_2;
        }
        // 0x0040c1b0
        charge(ctx, 4);
        v0 = subu(v0, v1);
        a2 = addiu(a2, 1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0040c1c0
    charge(ctx, 1);
    v0 = 0;
    // 0x0040c1c4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    return;
L_0040c1a4_2:
    charge(ctx, 3);
    lw(v0, a0, 0);
    // 0x0040c1c4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0040C310 sub_40C310 -- 332 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [facility] Updates the enabled bit of every row of a command list (kinds 11, 13 ...).
void sub_40C310(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040c310
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 12);
    lw(s1, v1, 4);
    for (;;) {
        // 0x0040c438
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0040c334
        charge(ctx, 4);
        lw(a0, s1, 0);
        v1 = 11;
        if (a0 == v1) {
            // 0x0040c3f8
            charge(ctx, 6);
            lw(v0, s1, 20);
            lw(s0, v0, 28);
            jal(ctx, 0x40C400u, gen::fn_sub_17C700_0017c700);
            if (v0 != 0) {
                // 0x0040c424
                charge(ctx, 4);
                lw(a0, s0, 0);
                v1 = si(-2);
                v1 = a0 & v1;
                sw(v1, s0, 0);
            } else {
                // 0x0040c410
                charge(ctx, 5);
                lw(v1, s0, 0);
                v1 = v1 | 0x1;
                sw(v1, s0, 0);
            }
        } else {
            // 0x0040c344
            charge(ctx, 3);
            v1 = 13;
            if (a0 == v1) {
                // 0x0040c358
                charge(ctx, 5);
                lw(v0, s1, 20);
                lw(s0, v0, 28);
                s2 = 0;
                for (;;) {
                    // 0x0040c3a8
                    charge(ctx, 6);
                    jal(ctx, 0x40C3A8u, gen::fn_sub_175410_00175410);
                    v1 = v0 & 0xFFFF;
                    v1 = slt(s2, v1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0040c36c
                    charge(ctx, 6);
                    a0 = dsll32(s2, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x40C374u, gen::fn_sub_174A90_00174a90);
                    if (v0 != 0) {
                        // 0x0040c384
                        charge(ctx, 6);
                        a0 = v0;
                        jal(ctx, 0x40C388u, gen::fn_sub_17CA10_0017ca10);
                        v1 = 1;
                        if (v0 != v1) {
                            goto L_0040c3a4;
                        }
                        goto L_0040c39c_7;
                    }
                L_0040c3a4:
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0040c3c0
                charge(ctx, 1);
                v1 = 0;
            L_0040c3c4:
                charge(ctx, 2);
                if (v1 != 0) {
                    // 0x0040c3e0
                    charge(ctx, 6);
                    lw(a0, s0, 0);
                    v1 = si(-2);
                    v1 = a0 & v1;
                    sw(v1, s0, 0);
                } else {
                    // 0x0040c3cc
                    charge(ctx, 5);
                    lw(v1, s0, 0);
                    v1 = v1 | 0x1;
                    sw(v1, s0, 0);
                }
            } else {
                // 0x0040c350
                charge(ctx, 2);
            }
        }
        // 0x0040c434
        charge(ctx, 1);
        lw(s1, s1, 16);
    }
    // 0x0040c440
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_0040c39c_7:
    charge(ctx, 2);
    goto L_0040c3c4;
}

// 0x0040C490 sub_40C490 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [facility] Resets the five list window parts 4, 0, 1, 5, 6 (sub_3D9820).
void sub_40C490(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040c490
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 4;
    a2 = 0;
    jal(ctx, 0x40C4A8u, gen::fn_sub_3D9820_003d9820);
    a0 = s0;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x40C4BCu, gen::fn_sub_3D9820_003d9820);
    a0 = s0;
    a1 = 1;
    a2 = 0;
    jal(ctx, 0x40C4D0u, gen::fn_sub_3D9820_003d9820);
    a0 = s0;
    a1 = 5;
    a2 = 0;
    jal(ctx, 0x40C4E4u, gen::fn_sub_3D9820_003d9820);
    a0 = s0;
    a1 = 6;
    a2 = 0;
    jal(ctx, 0x40C4F8u, gen::fn_sub_3D9820_003d9820);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
