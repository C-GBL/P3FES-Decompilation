// Phase 5 slice facility2 (part 1 of 3): the fusion list helpers (0x3D3170 .. 0x3DCFB0) and the shop steps' callbacks
// (fclShop.c 0x3E0940 .. 0x3EFC20: the ARMSCOMBINE / TRADE / QUEST / QUESTCANCEL / BOOK / BOOKREGIST / TALK / MONEY /
// SUBTITLE / BG finis and draws, the sequence getters). p3fes_handgen bodies (game/include/p3fes/game/hg_cpu.h) made
// readable: role comments, block comments, the records of facility2.h as named offsets; every statement, charge and
// check point is the generator's (the slice's check script compares them).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/facility2.h"

namespace p3fes::recomp_gen {
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_nmCmdListCancelled_003c6c80(p3fes::EEContext&);
void fn_nmCmdListCloseNow_003c6f50(p3fes::EEContext&);
void fn_nmCmdListDestroy_003c5a20(p3fes::EEContext&);
void fn_nmCmdListDraw_003c6380(p3fes::EEContext&);
void fn_nmObjPayloadWord12_003c5460(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_175410_00175410(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_3C4DE0_003c4de0(p3fes::EEContext&);
void fn_sub_3C4E60_003c4e60(p3fes::EEContext&);
void fn_sub_3C5470_003c5470(p3fes::EEContext&);
void fn_sub_3D3170_003d3170(p3fes::EEContext&);
void fn_sub_3D3760_003d3760(p3fes::EEContext&);
void fn_sub_3D9820_003d9820(p3fes::EEContext&);
void fn_sub_3DCA10_003dca10(p3fes::EEContext&);
void fn_sub_3DCFB0_003dcfb0(p3fes::EEContext&);
void fn_sub_3DEF80_003def80(p3fes::EEContext&);
void fn_sub_3DF010_003df010(p3fes::EEContext&);
void fn_sub_3DF100_003df100(p3fes::EEContext&);
void fn_sub_3DFFC0_003dffc0(p3fes::EEContext&);
void fn_sub_3E0330_003e0330(p3fes::EEContext&);
void fn_sub_3E0940_003e0940(p3fes::EEContext&);
void fn_sub_3E6E20_003e6e20(p3fes::EEContext&);
void fn_sub_3EAEB0_003eaeb0(p3fes::EEContext&);
void fn_sub_3EAF30_003eaf30(p3fes::EEContext&);
void fn_sub_3EB940_003eb940(p3fes::EEContext&);
void fn_sub_3EBB90_003ebb90(p3fes::EEContext&);
void fn_sub_3EBC70_003ebc70(p3fes::EEContext&);
void fn_sub_3EBFE0_003ebfe0(p3fes::EEContext&);
void fn_sub_3EC280_003ec280(p3fes::EEContext&);
void fn_sub_3EC6A0_003ec6a0(p3fes::EEContext&);
void fn_sub_3EC8E0_003ec8e0(p3fes::EEContext&);
void fn_sub_3ECCE0_003ecce0(p3fes::EEContext&);
void fn_sub_3ECF80_003ecf80(p3fes::EEContext&);
void fn_sub_3ED310_003ed310(p3fes::EEContext&);
void fn_sub_3ED5A0_003ed5a0(p3fes::EEContext&);
void fn_sub_3EDD80_003edd80(p3fes::EEContext&);
void fn_sub_3EE4E0_003ee4e0(p3fes::EEContext&);
void fn_sub_3EE640_003ee640(p3fes::EEContext&);
void fn_sub_3EEE50_003eee50(p3fes::EEContext&);
void fn_sub_3EFC20_003efc20(p3fes::EEContext&);
void fn_sub_3FE3E0_003fe3e0(p3fes::EEContext&);
void fn_sub_3FEF30_003fef30(p3fes::EEContext&);
void fn_sub_400E30_00400e30(p3fes::EEContext&);
void fn_sub_405D60_00405d60(p3fes::EEContext&);
void fn_sub_40A200_0040a200(p3fes::EEContext&);
void fn_sub_40C150_0040c150(p3fes::EEContext&);
void fn_sub_40E3C0_0040e3c0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace fac2;  // the records of facility2.h

// 0x003D3170 sub_3D3170 -- 260 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCombineListCancel] The fusion list's cancel handler (called by the list step sub_3D2E00): a0 -> the list work
// (+0 the work: +8 the command list, +16 the element set). When the command list reports a cancel and the element set is
// idle (sub_3DF010), the elements are stopped and restarted from the cursor (sub_3C4E60 / sub_3DEF80 / sub_3C4DE0 keep the
// cursor row), the window's close animation starts (sub_3D3760(work, 0, 1)), the cancel sound plays (sound driver kind 2)
// and the list closes at once. Returns 1 when it closed, else 0.
void sub_3D3170(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d3170
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (a0 != 0) {
        // 0x003d318c
        charge(ctx, 3);
        lw(s0, a0, 0);
        if (s0 == 0) {
            goto L_003d3198;
        }
        // 0x003d31a4
        charge(ctx, 6);
        lw(s2, s0, 8);
        a0 = s2;
        jal(ctx, 0x3D31ACu, gen::fn_nmCmdListCancelled_003c6c80);
        if (v0 == 0) {
            // 0x003d3254: no cancel this frame
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x003d31bc
            charge(ctx, 5);
            lw(a0, s0, 16);
            jal(ctx, 0x3D31C0u, gen::fn_sub_3DF010_003df010);
            if (v0 != 0) {
                // 0x003d31dc: restart the elements from the cursor row, start the close animation, cancel sound, close now
                charge(ctx, 30);
                lw(s1, s2, lst::kCursor);
                a0 = s2;
                a1 = addiu(s2, 4);
                jal(ctx, 0x3D31E8u, gen::fn_sub_3C4E60_003c4e60);
                lw(a0, s0, 16);
                jal(ctx, 0x3D31F4u, gen::fn_sub_3DEF80_003def80);
                a0 = s2;
                a1 = addiu(s2, 4);
                a2 = s1;
                jal(ctx, 0x3D3208u, gen::fn_sub_3C4DE0_003c4de0);
                a0 = s0;
                a1 = 0;
                a2 = 1;
                jal(ctx, 0x3D321Cu, gen::fn_sub_3D3760_003d3760);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 2;
                jal(ctx, 0x3D3234u, gen::fn_sub_10A4E0_0010a4e0);
                a0 = s2;
                jal(ctx, 0x3D3240u, gen::fn_nmCmdListCloseNow_003c6f50);
                v0 = 1;
            } else {
                // 0x003d31d0: the elements are still moving
                charge(ctx, 3);
                v0 = 0;
            }
        }
        // 0x003d3258 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_003d3198:
    charge(ctx, 3);
    v0 = 0;
    // 0x003d3258 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003D3760 sub_3D3760 -- 332 bytes; frame 0xE0: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCombineListPanelAnim] Starts the fusion list panel's element animation: a0 -> the list work (+20 the element set),
// a1 = the part (only part 0 does anything), a2 = 0 the opening / 1 the closing animation. The two 28-byte templates of
// 0x6A4830 are copied to the stack, the chosen one's start / flag fields are cleared, and the element with the template's
// id (+4) is found (sub_3DFFC0) and started from it (sub_3DF100). Template layout: shops.h kElemTemplateSize.
void sub_3D3760(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d3760
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    if (a1 == 0) {
        // 0x003d377c
        charge(ctx, 2);
        if (a2 != 0) {
            // 0x003d380c
            charge(ctx, 3);
            v1 = 1;
            if (a2 == v1) {
                // 0x003d3818: phase 1: the closing template
                charge(ctx, 5);
                lw(s0, a0, 20);
                a2 = 0x6A0000;
                a2 = addiu(a2, 18480);  // &0x6A4830
                a1 = addiu(sp, 0x20);
                a0 = 7;
                for (;;) {
                    // 0x003d382c: copy the two templates of 0x6A4830 (7 x 8 bytes)
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
                // 0x003d3850
                charge(ctx, 18);
                sw(zero, sp, 0x20);
                sh(zero, sp, 0x38);
                sw(zero, sp, 0x3C);
                sh(zero, sp, 0x54);
                a0 = addiu(sp, 0xA0);
                a1 = addiu(sp, 0x3C);
                a2 = 28;
                jal(ctx, 0x3D386Cu, gen::fn_memcpy_00521250);
                lw(a2, sp, 0xA4);
                a0 = s0;
                a1 = 0;
                jal(ctx, 0x3D3880u, gen::fn_sub_3DFFC0_003dffc0);
                a0 = v0;
                a1 = addiu(sp, 0xA0);
                jal(ctx, 0x3D3890u, gen::fn_sub_3DF100_003df100);
            }
        } else {
            // 0x003d3784: phase 0: the opening template
            charge(ctx, 5);
            lw(s0, a0, 20);
            a2 = 0x6A0000;
            a2 = addiu(a2, 18480);  // &0x6A4830
            a1 = addiu(sp, 0x60);
            a0 = 7;
            for (;;) {
                // 0x003d3798: copy the two templates of 0x6A4830 (7 x 8 bytes)
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
            // 0x003d37bc
            charge(ctx, 20);
            sw(zero, sp, 0x60);
            sh(zero, sp, 0x78);
            sw(zero, sp, 0x7C);
            sh(zero, sp, 0x94);
            a0 = addiu(sp, 0xC0);
            a1 = addiu(sp, 0x60);
            a2 = 28;
            jal(ctx, 0x3D37D8u, gen::fn_memcpy_00521250);
            lw(a2, sp, 0xC4);
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x3D37ECu, gen::fn_sub_3DFFC0_003dffc0);
            a0 = v0;
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x3D37FCu, gen::fn_sub_3DF100_003df100);
        }
    } else {
        // 0x003d3774: part != 0: nothing
        charge(ctx, 2);
    }
    // 0x003d3898 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
}

// 0x003D9820 sub_3D9820 -- 1124 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclListPanelPartAnim] The list window part animator the fusion and shop list windows share (driven by sub_40C520 ..
// sub_40D330): a0 -> the panel work (panel::: +8 the window element set, +12 the command list), a1 = the part 0..7 (jump
// table 0x7BB820), a2 = the phase: 0 in, 1 out, 3 out with the cursor row highlighted.
//   part 0: every row's element (row user +8) through sub_3E0330(elems, 0, phase, delay) -- in: staggered by
//           i - i / 4 frames, the start y -i * spacing (+26); out (1 / 3): the end y -i * spacing (+30), with phase 3
//           the cursor row's end alpha 255 (+42);
//   part 1: in: every visible row's second element (from the first visible row); out: the cursor row's only;
//   parts 2..7: the window element set's part a1 in / out.
void sub_3D9820(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d9820
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0;
    lw(a3, a0, 12);
    lw(s2, a3, lst::kHead);
    at = sltiu(a1, 8);
    if (at != 0) {
        // 0x003d9850
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, -18400);  // &0x7BB820
        v1 = sll(a1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x3D986Cu:  // table[0]
            // 0x003d986c: part 0: the rows' elements
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x003d98d8
                charge(ctx, 3);
                v1 = 1;
                if (a2 != v1) {
                    // 0x003d9944
                    charge(ctx, 3);
                    v1 = 3;
                    if (a2 == v1) {
                        // 0x003d9950: part 0 out with the cursor row highlighted (end alpha 255)
                        charge(ctx, 4);
                        lw(v1, a3, lst::kState);
                        lw(s2, v1, 44);
                        for (;;) {
                            // 0x003d99b8
                            charge(ctx, 2);
                            if (s2 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x003d9960
                            charge(ctx, 18);
                            lw(v0, s2, 20);
                            lw(v0, v0, 28);
                            lw(a0, v0, 8);
                            a1 = 0;
                            a2 = 1;
                            a3 = 0;
                            jal(ctx, 0x3D9978u, gen::fn_sub_3E0330_003e0330);
                            lw(v1, s1, panel::kList);
                            lw(v1, v1, 36);
                            lw(v1, v1, 12);
                            v1 = subu(0, v1);
                            mult(v1, s0, v1);
                            sh(v1, v0, elem::kY1);
                            lw(v1, s1, panel::kList);
                            lw(v1, v1, 12);
                            if (s2 == v1) {
                                // 0x003d99a8
                                charge(ctx, 2);
                                v1 = 255;
                                sh(v1, v0, elem::kAlpha1);
                            }
                            // 0x003d99b0
                            charge(ctx, 2);
                            lw(s2, s2, 16);
                            s0 = addiu(s0, 1);
                        }
                        // 0x003d99c0
                        charge(ctx, 2);
                    }
                } else {
                    // 0x003d98e4: part 0 out: end y = -i * spacing
                    charge(ctx, 4);
                    lw(v1, a3, lst::kState);
                    lw(s2, v1, 44);
                    for (;;) {
                        // 0x003d9934
                        charge(ctx, 2);
                        if (s2 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x003d98f4
                        charge(ctx, 16);
                        lw(v0, s2, 20);
                        lw(v0, v0, 28);
                        lw(a0, v0, 8);
                        a1 = 0;
                        a2 = 1;
                        a3 = 0;
                        jal(ctx, 0x3D990Cu, gen::fn_sub_3E0330_003e0330);
                        lw(v1, s1, panel::kList);
                        lw(v1, v1, 36);
                        lw(v1, v1, 12);
                        v1 = subu(0, v1);
                        mult(v1, s0, v1);
                        sh(v1, v0, elem::kY1);
                        lw(s2, s2, 16);
                        s0 = addiu(s0, 1);
                    }
                    // 0x003d993c
                    charge(ctx, 2);
                }
            } else {
                // 0x003d9874: part 0 in: staggered, start y = -i * spacing
                charge(ctx, 4);
                lw(v1, a3, lst::kState);
                lw(s2, v1, 44);
                for (;;) {
                    // 0x003d98c8
                    charge(ctx, 2);
                    if (s2 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003d9884
                    charge(ctx, 17);
                    lw(v0, s2, 20);
                    lw(v1, v0, 28);
                    v0 = sra(s0, 2);
                    a3 = subu(s0, v0);
                    lw(a0, v1, 8);
                    a1 = 0;
                    a2 = 0;
                    jal(ctx, 0x3D98A0u, gen::fn_sub_3E0330_003e0330);
                    lw(v1, s1, panel::kList);
                    lw(v1, v1, 36);
                    lw(v1, v1, 12);
                    v1 = subu(0, v1);
                    mult(v1, s0, v1);
                    sh(v1, v0, elem::kY0);
                    lw(s2, s2, 16);
                    s0 = addiu(s0, 1);
                }
                // 0x003d98d0
                charge(ctx, 2);
            }
            break;
        case 0x3D99C8u:  // table[1]
            // 0x003d99c8: part 1: the rows' second elements
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x003d9a10
                charge(ctx, 3);
                a1 = 1;
                if (a2 != a1) {
                    // 0x003d9a44
                    charge(ctx, 3);
                    v1 = 3;
                    if (a2 == v1) {
                        // 0x003d9a50
                        charge(ctx, 10);
                        lw(v0, a3, lst::kCursor);
                        lw(v0, v0, 20);
                        lw(v0, v0, 28);
                        lw(a0, v0, 8);
                        a2 = a1;
                        a3 = 0;
                        jal(ctx, 0x3D9A68u, gen::fn_sub_3E0330_003e0330);
                    }
                } else {
                    // 0x003d9a1c
                    charge(ctx, 10);
                    lw(v0, a3, lst::kCursor);
                    lw(v0, v0, 20);
                    lw(v0, v0, 28);
                    lw(a0, v0, 8);
                    a2 = a1;
                    a3 = 0;
                    jal(ctx, 0x3D9A34u, gen::fn_sub_3E0330_003e0330);
                }
            } else {
                // 0x003d99d0
                charge(ctx, 2);
                for (;;) {
                    // 0x003d9a00
                    charge(ctx, 2);
                    if (s2 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003d99d8
                    charge(ctx, 10);
                    lw(v0, s2, 20);
                    lw(v0, v0, 28);
                    lw(a0, v0, 8);
                    a1 = 1;
                    a2 = 0;
                    a3 = 0;
                    jal(ctx, 0x3D99F0u, gen::fn_sub_3E0330_003e0330);
                    lw(s2, s2, 16);
                    s0 = addiu(s0, 1);
                }
                // 0x003d9a08
                charge(ctx, 2);
            }
            break;
        case 0x3D9A78u:  // table[2]
            // 0x003d9a78: part 2: the window's element set
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x003d9aa0
                charge(ctx, 3);
                v1 = 1;
                if (a2 == v1) {
                    // 0x003d9aac
                    charge(ctx, 8);
                    lw(a0, s1, panel::kElems);
                    a1 = 2;
                    a2 = v1;
                    a3 = 0;
                    jal(ctx, 0x3D9ABCu, gen::fn_sub_3E0330_003e0330);
                }
            } else {
                // 0x003d9a80
                charge(ctx, 8);
                lw(a0, s1, panel::kElems);
                a1 = 2;
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x3D9A90u, gen::fn_sub_3E0330_003e0330);
            }
            break;
        case 0x3D9ACCu:  // table[3]
            // 0x003d9acc: part 3
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x003d9af4
                charge(ctx, 3);
                v1 = 1;
                if (a2 == v1) {
                    // 0x003d9b00
                    charge(ctx, 8);
                    lw(a0, s1, panel::kElems);
                    a1 = 3;
                    a2 = v1;
                    a3 = 0;
                    jal(ctx, 0x3D9B10u, gen::fn_sub_3E0330_003e0330);
                }
            } else {
                // 0x003d9ad4
                charge(ctx, 8);
                lw(a0, s1, panel::kElems);
                a1 = 3;
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x3D9AE4u, gen::fn_sub_3E0330_003e0330);
            }
            break;
        case 0x3D9B20u:  // table[4]
            // 0x003d9b20: part 4
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x003d9b48
                charge(ctx, 3);
                v1 = 1;
                if (a2 == v1) {
                    // 0x003d9b54
                    charge(ctx, 8);
                    lw(a0, s1, panel::kElems);
                    a1 = 4;
                    a2 = v1;
                    a3 = 0;
                    jal(ctx, 0x3D9B64u, gen::fn_sub_3E0330_003e0330);
                }
            } else {
                // 0x003d9b28
                charge(ctx, 8);
                lw(a0, s1, panel::kElems);
                a1 = 4;
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x3D9B38u, gen::fn_sub_3E0330_003e0330);
            }
            break;
        case 0x3D9B74u:  // table[5]
            // 0x003d9b74: part 5
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x003d9b9c
                charge(ctx, 3);
                v1 = 1;
                if (a2 == v1) {
                    // 0x003d9ba8
                    charge(ctx, 8);
                    lw(a0, s1, panel::kElems);
                    a1 = 5;
                    a2 = v1;
                    a3 = 0;
                    jal(ctx, 0x3D9BB8u, gen::fn_sub_3E0330_003e0330);
                }
            } else {
                // 0x003d9b7c
                charge(ctx, 8);
                lw(a0, s1, panel::kElems);
                a1 = 5;
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x3D9B8Cu, gen::fn_sub_3E0330_003e0330);
            }
            break;
        case 0x3D9BC8u:  // table[6]
            // 0x003d9bc8: part 6
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x003d9bf0
                charge(ctx, 3);
                v1 = 1;
                if (a2 == v1) {
                    // 0x003d9bfc
                    charge(ctx, 8);
                    lw(a0, s1, panel::kElems);
                    a1 = 6;
                    a2 = v1;
                    a3 = 0;
                    jal(ctx, 0x3D9C0Cu, gen::fn_sub_3E0330_003e0330);
                }
            } else {
                // 0x003d9bd0
                charge(ctx, 8);
                lw(a0, s1, panel::kElems);
                a1 = 6;
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x3D9BE0u, gen::fn_sub_3E0330_003e0330);
            }
            break;
        case 0x3D9C1Cu:  // table[7]
            // 0x003d9c1c: part 7
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x003d9c44
                charge(ctx, 3);
                v1 = 1;
                if (a2 == v1) {
                    // 0x003d9c50
                    charge(ctx, 6);
                    lw(a0, s1, panel::kElems);
                    a1 = 7;
                    a2 = v1;
                    a3 = 0;
                    jal(ctx, 0x3D9C60u, gen::fn_sub_3E0330_003e0330);
                }
            } else {
                // 0x003d9c24
                charge(ctx, 8);
                lw(a0, s1, panel::kElems);
                a1 = 7;
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x3D9C34u, gen::fn_sub_3E0330_003e0330);
            }
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x003d9c68 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003DCA10 sub_3DCA10 -- 636 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCombineDrawStockSlots] Draws the twelve stock-slot markers of a fusion list row (called by the row drawer
// sub_3DD260): a0 = x of slot 0 (slots are 22 pixels apart), a1 = y, a2 = alpha, a3 -> the command list, t0 -> the row,
// t1 = the sprite argument. The slot count is the persona stock size (sub_175410); for each slot i < 12: beyond the
// stock -> sprite 45 (empty), else sprite 42 when the row's mask (row user +4) has bit i, else 43. The two loops (the
// window mode +12 == 3 or not) draw the same sprites.
void sub_3DCA10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003dca10
    enter(ctx, 27);  // entry check point + this block's cycles
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
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s7 = a3;
    s5 = t0;
    s0 = t1;
    jal(ctx, 0x3DCA50u, gen::fn_sub_175410_00175410);
    s4 = v0 & 0xFFFF;
    lw(v1, s5, node::kPayload);
    lw(s6, v1, 28);
    lw(v1, s7, lst::kState);
    lw(v1, v1, 68);
    lw(a0, v1, 12);
    v1 = 3;
    if (a0 != v1) {
        // 0x003dcb70: other modes (the same sprites)
        charge(ctx, 3);
        s5 = 0;
        for (;;) {
            // 0x003dcc50
            charge(ctx, 3);
            v1 = slti(s5, 12);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003dcb7c
            charge(ctx, 3);
            at = slt(s5, s4);
            if (at == 0) {
                // 0x003dcc18: beyond the stock: sprite 45
                charge(ctx, 13);
                v0 = sll(s5, 2);
                v0 = addu(v0, s5);
                v0 = sll(v0, 1);
                v0 = addu(v0, s5);
                v0 = sll(v0, 1);
                a0 = addu(s3, v0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a1 = s2;
                a3 = 45;
                t0 = 0;
                jal(ctx, 0x3DCC44u, gen::fn_sub_40E3C0_0040e3c0);
            } else {
                // 0x003dcb88
                charge(ctx, 6);
                v0 = 1;
                v1 = sllv(v0, s5);
                lw(v0, s6, 4);
                v0 = v0 & v1;
                if (v0 == 0) {
                    // 0x003dcbdc: free slot: sprite 43
                    charge(ctx, 15);
                    v0 = sll(s5, 2);
                    v0 = addu(v0, s5);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, s5);
                    v0 = sll(v0, 1);
                    a0 = addu(s3, v0);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a1 = s2;
                    a3 = 43;
                    t0 = s0;
                    jal(ctx, 0x3DCC08u, gen::fn_sub_40E3C0_0040e3c0);
                } else {
                    // 0x003dcba0: slot used by this row: sprite 42
                    charge(ctx, 15);
                    v0 = sll(s5, 2);
                    v0 = addu(v0, s5);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, s5);
                    v0 = sll(v0, 1);
                    a0 = addu(s3, v0);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a1 = s2;
                    a3 = 42;
                    t0 = s0;
                    jal(ctx, 0x3DCBCCu, gen::fn_sub_40E3C0_0040e3c0);
                }
            }
            // 0x003dcc4c
            charge(ctx, 1);
            s5 = addiu(s5, 1);
        }
    } else {
        // 0x003dca7c: window mode 3
        charge(ctx, 3);
        s5 = 0;
        for (;;) {
            // 0x003dcb5c
            charge(ctx, 3);
            v1 = slti(s5, 12);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003dca88
            charge(ctx, 3);
            at = slt(s5, s4);
            if (at == 0) {
                // 0x003dcb24: beyond the stock: sprite 45
                charge(ctx, 13);
                v0 = sll(s5, 2);
                v0 = addu(v0, s5);
                v0 = sll(v0, 1);
                v0 = addu(v0, s5);
                v0 = sll(v0, 1);
                a0 = addu(s3, v0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a1 = s2;
                a3 = 45;
                t0 = 0;
                jal(ctx, 0x3DCB50u, gen::fn_sub_40E3C0_0040e3c0);
            } else {
                // 0x003dca94
                charge(ctx, 6);
                v0 = 1;
                v1 = sllv(v0, s5);
                lw(v0, s6, 4);
                v0 = v0 & v1;
                if (v0 == 0) {
                    // 0x003dcae8: free slot: sprite 43
                    charge(ctx, 15);
                    v0 = sll(s5, 2);
                    v0 = addu(v0, s5);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, s5);
                    v0 = sll(v0, 1);
                    a0 = addu(s3, v0);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a1 = s2;
                    a3 = 43;
                    t0 = s0;
                    jal(ctx, 0x3DCB14u, gen::fn_sub_40E3C0_0040e3c0);
                } else {
                    // 0x003dcaac: slot used by this row: sprite 42
                    charge(ctx, 15);
                    v0 = sll(s5, 2);
                    v0 = addu(v0, s5);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, s5);
                    v0 = sll(v0, 1);
                    a0 = addu(s3, v0);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a1 = s2;
                    a3 = 42;
                    t0 = s0;
                    jal(ctx, 0x3DCAD8u, gen::fn_sub_40E3C0_0040e3c0);
                }
            }
            // 0x003dcb58
            charge(ctx, 1);
            s5 = addiu(s5, 1);
        }
        // 0x003dcb68
        charge(ctx, 2);
    }
    // 0x003dcc5c (the shared epilogue, written out on this path)
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

// 0x003DCFB0 sub_3DCFB0 -- 688 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCombineDrawRowIcons] Draws a fusion list row's icon strip (called by sub_3DD260): a1 -> the row's element (its x /
// y / alpha), a2 -> the draw context {+0 x, +4 y, +8 s16 alpha, +10 s16 flags, +12 -> the row flags, +20 -> the list},
// a3 = 0 dims the alpha by 0.8 (0x7CAD74). alpha = context alpha * element alpha / 255. With the list's mode (user +4)
// >= 2: sprites 83 / 81 / 82; else a row flagged 1 shows 49 / 61 / 62 (context flag 2) or 49 / 60 / 47 / 59, an
// unflagged row 49 / 47 / 48.
void sub_3DCFB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x003dcfb0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lh(v1, a1, elem::kX);
    lw(v0, a2, 0);
    s1 = addu(v0, v1);
    lh(v1, a1, elem::kY);
    lw(v0, a2, 4);
    s0 = addu(v0, v1);
    lh(v1, a2, 8);
    lh(v0, a1, elem::kAlpha);
    mult(v1, v1, v0);
    v0 = 255;
    div(v1, v0);
    mflo(v0);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    if (a3 == 0) {
        // 0x003dd004: a3 == 0: alpha x 0.8
        charge(ctx, 10);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, gp, -32636);  // 0x7CAD74
        mul_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
    }
    // 0x003dd02c
    charge(ctx, 7);
    lw(v0, a2, 20);
    lw(v0, v0, 36);
    lw(v0, v0, 68);
    lw(v0, v0, 4);
    v0 = slti(v0, 2);
    if (v0 != 0) {
        // 0x003dd0b8
        charge(ctx, 5);
        lw(v0, a2, 12);
        lw(v0, v0, 0);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x003dd1dc: unflagged row: 49 / 47 / 48
            charge(ctx, 26);
            s2 = dsll32(v1, 16);
            s2 = dsra32(s2, 16);
            mtc1(zero, f12);
            a2 = s2 & 0xFF;
            a0 = s1;
            a1 = s0;
            a3 = 49;
            t0 = 0;
            jal(ctx, 0x3DD1FCu, gen::fn_sub_40E3C0_0040e3c0);
            mtc1(zero, f12);
            a2 = s2 & 0xFF;
            a0 = s1;
            a1 = s0;
            a3 = 47;
            t0 = 0;
            jal(ctx, 0x3DD21Cu, gen::fn_sub_40E3C0_0040e3c0);
            mtc1(zero, f12);
            a2 = s2 & 0xFF;
            a0 = s1;
            a1 = s0;
            a3 = 48;
            t0 = 0;
            jal(ctx, 0x3DD23Cu, gen::fn_sub_40E3C0_0040e3c0);
        } else {
            // 0x003dd0cc
            charge(ctx, 4);
            lh(v0, a2, 10);
            v0 = v0 & 0x2;
            if (v0 == 0) {
                // 0x003dd14c: flagged row: 49 / 60 / 47 / 59
                charge(ctx, 36);
                s2 = dsll32(v1, 16);
                s2 = dsra32(s2, 16);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                a0 = s1;
                a1 = s0;
                a3 = 49;
                t0 = 0;
                jal(ctx, 0x3DD16Cu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                a0 = s1;
                a1 = s0;
                a3 = 60;
                t0 = 0;
                jal(ctx, 0x3DD18Cu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                a0 = s1;
                a1 = s0;
                a3 = 47;
                t0 = 0;
                jal(ctx, 0x3DD1ACu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                a0 = s1;
                a1 = s0;
                a3 = 59;
                t0 = 0;
                jal(ctx, 0x3DD1CCu, gen::fn_sub_40E3C0_0040e3c0);
            } else {
                // 0x003dd0dc: flagged row, context flag 2: 49 / 61 / 62
                charge(ctx, 28);
                s2 = dsll32(v1, 16);
                s2 = dsra32(s2, 16);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                a0 = s1;
                a1 = s0;
                a3 = 49;
                t0 = 0;
                jal(ctx, 0x3DD0FCu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                a0 = s1;
                a1 = s0;
                a3 = 61;
                t0 = 0;
                jal(ctx, 0x3DD11Cu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                a0 = s1;
                a1 = s0;
                a3 = 62;
                t0 = 0;
                jal(ctx, 0x3DD13Cu, gen::fn_sub_40E3C0_0040e3c0);
            }
        }
    } else {
        // 0x003dd048: list mode >= 2: sprites 83 / 81 / 82
        charge(ctx, 28);
        s2 = dsll32(v1, 16);
        s2 = dsra32(s2, 16);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s1;
        a1 = s0;
        a3 = 83;
        t0 = 0;
        jal(ctx, 0x3DD068u, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s1;
        a1 = s0;
        a3 = 81;
        t0 = 0;
        jal(ctx, 0x3DD088u, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s1;
        a1 = s0;
        a3 = 82;
        t0 = 0;
        jal(ctx, 0x3DD0A8u, gen::fn_sub_40E3C0_0040e3c0);
    }
    // 0x003dd244 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003E0940 sub_3E0940 -- 12 bytes; leaf frame (no stack)
// [fclShopGetSequence] Returns the shop's nm sequence (gp - 18024 = 0x7CE688, shops.h kShopSeqGlobal; 0 when no shop is
// open).
void sub_3E0940(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x003e0940
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, gp, -18024);  // 0x7CE688
}

// 0x003E6E20 sub_3E6E20 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopTestFlags] Returns 1 when a shop is open and its work record's flags (+8, shops.h kShopFlags) share a bit with
// a0, else 0.
void sub_3E6E20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e6e20
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, gp, -18024);  // 0x7CE688
    if (a0 != 0) {
        // 0x003e6e3c
        charge(ctx, 6);
        jal(ctx, 0x3E6E3Cu, gen::fn_nmObjPayloadWord12_003c5460);
        lw(v0, v0, 8);
        v0 = v0 & s0;
        if (v0 == 0) {
            goto L_003e6e60;
        }
        // 0x003e6e54: a common bit: 1
        charge(ctx, 3);
        v0 = 1;
        // 0x003e6e64 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_003e6e60:
    charge(ctx, 1);
    v0 = 0;
    // 0x003e6e64 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003EAEB0 sub_3EAEB0 -- 116 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopArmsCombineInit] ARMSCOMBINE's init (step descriptor 0x6A70E0): builds the weapon-fusion base-item list for the
// shop type (sub_3FE3E0(work +0)) into the payload's +12, clears +16 (the persona list, built later), phase 1, flag 2
// (hidden until shown). Returns 0.
void sub_3EAEB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003eaeb0
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3EAEC4u, gen::fn_nmObjPayloadWord12_003c5460);
    lw(s1, v0, 0);
    a0 = s0;
    jal(ctx, 0x3EAED4u, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    a0 = s1;
    jal(ctx, 0x3EAEE4u, gen::fn_sub_3FE3E0_003fe3e0);
    sw(v0, s0, step::kList);
    sw(zero, s0, step::kList2);
    v0 = 1;
    sw(v0, s0, step::kPhase);
    lw(v0, s0, step::kFlags);
    v0 = v0 | 0x2;
    sw(v0, s0, step::kFlags);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003EAF30 sub_3EAF30 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopArmsCombineFini] ARMSCOMBINE's fini: destroys the base-item list (+12) and, when built, the persona list (+16).
// Returns 0.
void sub_3EAF30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003eaf30
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EAF40u, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    lw(a0, v0, step::kList);
    jal(ctx, 0x3EAF50u, gen::fn_nmCmdListDestroy_003c5a20);
    lw(a0, s0, step::kList2);
    if (a0 != 0) {
        // 0x003eaf64
        charge(ctx, 2);
        jal(ctx, 0x3EAF64u, gen::fn_nmCmdListDestroy_003c5a20);
    }
    // 0x003eaf6c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003EB940 sub_3EB940 -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopArmsCombineDraw] ARMSCOMBINE's draw: unless hidden (flag 2), draws the base-item list and the persona list when
// there is one. Returns 0.
void sub_3EB940(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003eb940
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EB950u, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    lw(v0, v0, step::kFlags);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x003eb978: shown: draw both lists
        charge(ctx, 6);
        lw(a0, s0, step::kList);
        jal(ctx, 0x3EB97Cu, gen::fn_nmCmdListDraw_003c6380);
        lw(a0, s0, step::kList2);
        if (a0 != 0) {
            // 0x003eb990
            charge(ctx, 2);
            jal(ctx, 0x3EB990u, gen::fn_nmCmdListDraw_003c6380);
        }
        // 0x003eb998
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003eb96c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003eb99c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003EBB90 sub_3EBB90 -- 212 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopTradeInit] TRADE's init (0x6A7110): builds the trade list for the shop type -- the root state (shops.h
// kShopState) 69 lists the trades (sub_3FEF30(type, 0)), 71 the trade-ins (sub_3FEF30(type, 1)); any other state is
// K_Assert("fclShop.c", 3783) (it continues and the list stays unset). Phase 1, flag 2. Returns 0.
void sub_3EBB90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ebb90
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3EBBA8u, gen::fn_nmObjPayloadWord12_003c5460);
    s1 = v0;
    lw(s2, v0, 0);
    a0 = s0;
    jal(ctx, 0x3EBBBCu, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    lw(v1, s1, shopw::kState);
    v0 = 69;
    if (v1 != v0) {
        // 0x003ebbf4
        charge(ctx, 3);
        v0 = 71;
        if (v1 != v0) {
            // 0x003ebc1c
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 27384);  // "fclShop.c"
            a1 = 3783;
            jal(ctx, 0x3EBC28u, gen::fn_sub_19D3F0_0019d3f0);
        } else {
            // 0x003ebc00: state 71: the trade-ins
            charge(ctx, 7);
            a0 = s2;
            a1 = 1;
            jal(ctx, 0x3EBC08u, gen::fn_sub_3FEF30_003fef30);
            sw(v0, s0, step::kList);
        }
    } else {
        // 0x003ebbd8: state 69: the trades
        charge(ctx, 7);
        a0 = s2;
        a1 = 0;
        jal(ctx, 0x3EBBE0u, gen::fn_sub_3FEF30_003fef30);
        sw(v0, s0, step::kList);
    }
    // 0x003ebc30 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    v0 = 1;
    sw(v0, s0, step::kPhase);
    lw(v0, s0, step::kFlags);
    v0 = v0 | 0x2;
    sw(v0, s0, step::kFlags);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003EBC70 sub_3EBC70 -- 52 bytes; frame 0x10: ra sp+0x0
// [fclShopTradeFini] TRADE's fini: destroys the trade list (+12). Returns 0.
void sub_3EBC70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ebc70
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EBC7Cu, gen::fn_sub_3C5470_003c5470);
    lw(a0, v0, step::kList);
    jal(ctx, 0x3EBC88u, gen::fn_nmCmdListDestroy_003c5a20);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003EBFE0 sub_3EBFE0 -- 80 bytes; frame 0x10: ra sp+0x0
// [fclShopTradeDraw] TRADE's draw: the trade list unless hidden (flag 2). Returns 0.
void sub_3EBFE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ebfe0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EBFECu, gen::fn_sub_3C5470_003c5470);
    lw(v1, v0, step::kFlags);
    v1 = v1 & 0x2;
    if (v1 == 0) {
        // 0x003ec010
        charge(ctx, 4);
        lw(a0, v0, step::kList);
        jal(ctx, 0x3EC014u, gen::fn_nmCmdListDraw_003c6380);
        v0 = 0;
    } else {
        // 0x003ec004
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ec020 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003EC280 sub_3EC280 -- 52 bytes; frame 0x10: ra sp+0x0
// [fclShopQuestFini] QUEST's fini (0x6A7140): destroys the request list and its element set (sub_405D60). Returns 0.
void sub_3EC280(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ec280
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EC28Cu, gen::fn_sub_3C5470_003c5470);
    lw(a0, v0, step::kList);
    jal(ctx, 0x3EC298u, gen::fn_sub_405D60_00405d60);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003EC6A0 sub_3EC6A0 -- 80 bytes; frame 0x10: ra sp+0x0
// [fclShopQuestDraw] QUEST's draw: the request list unless hidden. Returns 0.
void sub_3EC6A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ec6a0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EC6ACu, gen::fn_sub_3C5470_003c5470);
    lw(v1, v0, step::kFlags);
    v1 = v1 & 0x2;
    if (v1 == 0) {
        // 0x003ec6d0
        charge(ctx, 4);
        lw(a0, v0, step::kList);
        jal(ctx, 0x3EC6D4u, gen::fn_nmCmdListDraw_003c6380);
        v0 = 0;
    } else {
        // 0x003ec6c4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ec6e0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003EC8E0 sub_3EC8E0 -- 52 bytes; frame 0x10: ra sp+0x0
// [fclShopQuestCancelFini] QUESTCANCEL's fini (0x6A7170): destroys the accepted-request list and its element set
// (sub_405D60). Returns 0.
void sub_3EC8E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ec8e0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EC8ECu, gen::fn_sub_3C5470_003c5470);
    lw(a0, v0, step::kList);
    jal(ctx, 0x3EC8F8u, gen::fn_sub_405D60_00405d60);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003ECCE0 sub_3ECCE0 -- 80 bytes; frame 0x10: ra sp+0x0
// [fclShopQuestCancelDraw] QUESTCANCEL's draw: the list unless hidden. Returns 0.
void sub_3ECCE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ecce0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3ECCECu, gen::fn_sub_3C5470_003c5470);
    lw(v1, v0, step::kFlags);
    v1 = v1 & 0x2;
    if (v1 == 0) {
        // 0x003ecd10
        charge(ctx, 4);
        lw(a0, v0, step::kList);
        jal(ctx, 0x3ECD14u, gen::fn_nmCmdListDraw_003c6380);
        v0 = 0;
    } else {
        // 0x003ecd04
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ecd20 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003ECF80 sub_3ECF80 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopBookFini] BOOK's fini (0x6A71A0, the compendium): destroys the task the compendium list owns (its user area
// +12) with its children, then the list and its two element sets (sub_40A200). Returns 0.
void sub_3ECF80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ecf80
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3ECF90u, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    lw(v0, v0, step::kList2);
    lw(v0, v0, 36);
    lw(v0, v0, 68);
    lw(a0, v0, step::kList);
    jal(ctx, 0x3ECFACu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    lw(a0, s0, step::kList2);
    jal(ctx, 0x3ECFB8u, gen::fn_sub_40A200_0040a200);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003ED310 sub_3ED310 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopBookDraw] BOOK's draw: unless hidden, the compendium list (+16) and sub_40C150 on it. Returns 0.
void sub_3ED310(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ed310
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3ED320u, gen::fn_sub_3C5470_003c5470);
    lw(v1, v0, step::kFlags);
    v1 = v1 & 0x2;
    if (v1 == 0) {
        // 0x003ed344: shown: draw the compendium list
        charge(ctx, 8);
        lw(s0, v0, step::kList2);
        a0 = s0;
        jal(ctx, 0x3ED34Cu, gen::fn_nmCmdListDraw_003c6380);
        a0 = s0;
        jal(ctx, 0x3ED358u, gen::fn_sub_40C150_0040c150);
        v0 = 0;
    } else {
        // 0x003ed338
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ed364 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003ED5A0 sub_3ED5A0 -- 52 bytes; frame 0x10: ra sp+0x0
// [fclShopBookRegistFini] BOOKREGIST's fini (0x6A71D0): destroys the register list and its element sets (sub_40A200).
// Returns 0.
void sub_3ED5A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ed5a0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3ED5ACu, gen::fn_sub_3C5470_003c5470);
    lw(a0, v0, step::kList);
    jal(ctx, 0x3ED5B8u, gen::fn_sub_40A200_0040a200);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003EDD80 sub_3EDD80 -- 80 bytes; frame 0x10: ra sp+0x0
// [fclShopBookRegistDraw] BOOKREGIST's draw: the register list unless hidden. Returns 0.
void sub_3EDD80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003edd80
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EDD8Cu, gen::fn_sub_3C5470_003c5470);
    lw(v1, v0, step::kFlags);
    v1 = v1 & 0x2;
    if (v1 == 0) {
        // 0x003eddb0
        charge(ctx, 4);
        lw(a0, v0, step::kList);
        jal(ctx, 0x3EDDB4u, gen::fn_nmCmdListDraw_003c6380);
        v0 = 0;
    } else {
        // 0x003edda4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003eddc0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003EE4E0 sub_3EE4E0 -- 40 bytes; frame 0x10: ra sp+0x0
// [fclShopTalkFini] TALK's fini (0x6A7230): fetches the payload and does nothing with it. Returns 0.
void sub_3EE4E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ee4e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EE4ECu, gen::fn_sub_3C5470_003c5470);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003EE640 sub_3EE640 -- 40 bytes; frame 0x10: ra sp+0x0
// [fclShopMoneyFini] MONEY's fini (0x6A7260): fetches the payload and does nothing with it. Returns 0.
void sub_3EE640(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ee640
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EE64Cu, gen::fn_sub_3C5470_003c5470);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003EEE50 sub_3EEE50 -- 40 bytes; frame 0x10: ra sp+0x0
// [fclShopSubtitleFini] SUBTITLE's fini: fetches the payload and does nothing with it. Returns 0.
void sub_3EEE50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003eee50
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EEE5Cu, gen::fn_sub_3C5470_003c5470);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003EFC20 sub_3EFC20 -- 52 bytes; frame 0x10: ra sp+0x0
// [fclShopBgFini] BG's fini (0x6A75CC): destroys the background manager (payload +8, sub_400E30). Returns 0.
void sub_3EFC20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003efc20
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EFC2Cu, gen::fn_sub_3C5470_003c5470);
    lw(a0, v0, 8);
    jal(ctx, 0x3EFC38u, gen::fn_sub_400E30_00400e30);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
