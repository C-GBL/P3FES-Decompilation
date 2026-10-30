// Slice scene (game/include/p3fes/game/scene.h has the formats and the records): three leftovers of 0x3C0000: the nmlist node allocator, a facility panel slide animation, the fclBank panel states.
// p3fes_handgen bodies (register for register, block for block as the recompiled ones) with a role comment per
// function and named offsets / globals (each constant equals the literal it replaces; tools check it).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/scene.h"

namespace p3fes::recomp_gen {
void fn_memset_00521408(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sub_106E90_00106e90(p3fes::EEContext&);
void fn_sub_106F60_00106f60(p3fes::EEContext&);
void fn_sub_106FB0_00106fb0(p3fes::EEContext&);
void fn_sub_133180_00133180(p3fes::EEContext&);
void fn_sub_1332F0_001332f0(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_3C4650_003c4650(p3fes::EEContext&);
void fn_sub_3CA960_003ca960(p3fes::EEContext&);
void fn_sub_3CFB50_003cfb50(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace scn;

// 0x003C4650 sub_3C4650 -- 192 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [nmListAllocNode] (?, owner, size) A list node of size + 24 bytes (RwMalloc, asserts nmlist.c 96), zeroed: +0 the
// owner (or itself), +8 the size, +20 -> the payload at +24 when size != 0.
void sub_3C4650(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c4650
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    s3 = a2;
    s2 = addiu(s3, 24);
    a0 = s2;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, g::kLoRwMalloc);  // 0x960178 the RwMalloc slot
    jalr(ctx, 0x3C4684u, v0.u());
    s1 = v0;
    if (s1 == 0) {
        // 0x003c4698
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15848);  // "nmlist.c"
        a1 = 96;
        jal(ctx, 0x3C46A4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003c46ac
    charge(ctx, 7);
    a0 = s1;
    a1 = 0;
    a2 = s2;
    jal(ctx, 0x3C46B8u, gen::fn_memset_00521408);
    if (s3 != 0) {
        // 0x003c46c8
        charge(ctx, 2);
        v0 = addiu(s1, 24);
        sw(v0, s1, 20);
    }
    // 0x003c46d0
    charge(ctx, 3);
    sw(s2, s1, 8);
    if (s0 != 0) {
        // 0x003c46e8
        charge(ctx, 1);
        sw(s0, s1, 0);
    } else {
        // 0x003c46dc
        charge(ctx, 3);
        sw(s1, s1, 0);
    }
    // 0x003c46ec (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s1;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003CA960 sub_3CA960 -- 856 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (sprite) The slide animation of a facility panel sprite: with flag 0x40, the in and out halves of the frame counter
// (+22 of +20, the fractions 0x7CAD7C / 0x7CADD0) move it by 80 * (sin(...) + 1) and scale its alpha (+18); flag 2
// picks the draw sub_1332F0, else sub_133180; the position is +28 or +112 by the side byte +232.
void sub_3CA960(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x003ca960
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = addiu(sp, 0x68);
    v1 = 8;
    if (a0 != 0) {
        for (;;) {
            // 0x003ca990
            charge(ctx, 7);
            sb(zero, a0, 0);
            a0 = addiu(a0, 1);
            v1 = addiu(v1, -1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x003ca9ac
    charge(ctx, 3);
    lb(a2, s1, 232);
    if (a2 != 0) {
        // 0x003ca9c4
        charge(ctx, 1);
        a1 = addiu(s1, 112);
    } else {
        // 0x003ca9b8
        charge(ctx, 3);
        a1 = addiu(s1, 28);
    }
    // 0x003ca9c8
    charge(ctx, 4);
    lw(a0, s1, 8);
    v1 = a0 & 0x40;
    if (v1 == 0) {
        // 0x003cac50
        charge(ctx, 3);
        v0 = a0 & 0x2;
        if (v0 == 0) {
            // 0x003cac7c
            charge(ctx, 6);
            mtc1(zero, f12);
            lh(a3, s1, 18);
            ld(a0, sp, 0x68);
            a2 = addiu(a1, 4);
            jal(ctx, 0x3CAC8Cu, gen::fn_sub_133180_00133180);
        } else {
            // 0x003cac5c
            charge(ctx, 8);
            mtc1(zero, f12);
            lh(a3, s1, 18);
            ld(a0, sp, 0x68);
            a2 = addiu(a1, 4);
            jal(ctx, 0x3CAC6Cu, gen::fn_sub_1332F0_001332f0);
        }
    } else {
        // 0x003ca9d8
        charge(ctx, 15);
        lh(s0, s1, 22);
        lh(v1, s1, 20);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, gp, -32628);  // 0x7CAD7C
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(s3, f0);
        lwc1(f0, gp, -32544);  // 0x7CADD0
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(s2, f0);
        if (a2 == 0) {
            // 0x003caa14
            charge(ctx, 3);
            v1 = dsll32(v1, 16);
            v1 = dsra32(v1, 16);
            s0 = subu(v1, s0);
        }
        // 0x003caa20
        charge(ctx, 2);
        if (a2 != 0) {
            // 0x003caa34
            charge(ctx, 1);
            s4 = addiu(s1, 28);
        } else {
            // 0x003caa28
            charge(ctx, 3);
            s4 = addiu(s1, 112);
        }
        // 0x003caa38
        charge(ctx, 3);
        at = slt(s2, s0);
        if (at == 0) {
            // 0x003caa44
            charge(ctx, 27);
            mtc1(s0, f0);
            cvt_s_w(f1, f0);
            mtc1(s2, f0);
            cvt_s_w(f0, f0);
            div_s(f3, f1, f0);
            lwc1(f2, gp, -32496);  // 0x7CAE00
            lwc1(f1, gp, -32272);  // 0x7CAEE0
            mtc1(zero, f0);
            adda_s(f0, f1);
            msub_s(f12, f2, f3);
            jal(ctx, 0x3CAA78u, gen::fn_sinf_0052e878);
            v0 = 0x3F800000;
            mtc1(v0, f1);
            add_s(f2, f1, f0);
            v0 = 0x42A00000;
            mtc1(v0, f0);
            mul_s(f1, f0, f2);
            swc1(f1, sp, 0x68);
            lb(v0, s1, 232);
            if (v0 == 0) {
                // 0x003caab0
                charge(ctx, 5);
                v0 = lui(0xBF80);
                mtc1(v0, f0);
                mul_s(f0, f1, f0);
                swc1(f0, sp, 0x68);
            }
            // 0x003caac4
            charge(ctx, 15);
            lh(v0, s1, 18);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f0, f0, f2);
            mul_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(a3, f0);
            lw(v0, s1, 8);
            v0 = v0 & 0x2;
            if (v0 == 0) {
                // 0x003cab20
                charge(ctx, 6);
                mtc1(zero, f12);
                ld(a0, sp, 0x68);
                a1 = s4;
                a2 = addiu(s4, 4);
                jal(ctx, 0x3CAB30u, gen::fn_sub_133180_00133180);
            } else {
                // 0x003cab00
                charge(ctx, 8);
                mtc1(zero, f12);
                ld(a0, sp, 0x68);
                a1 = s4;
                a2 = addiu(s4, 4);
                jal(ctx, 0x3CAB10u, gen::fn_sub_1332F0_001332f0);
            }
        }
        // 0x003cab38
        charge(ctx, 3);
        lb(v1, s1, 232);
        if (v1 != 0) {
            // 0x003cab50
            charge(ctx, 1);
            s4 = addiu(s1, 112);
        } else {
            // 0x003cab44
            charge(ctx, 3);
            s4 = addiu(s1, 28);
        }
        // 0x003cab54
        charge(ctx, 3);
        v1 = slt(s0, s3);
        if (v1 == 0) {
            // 0x003cab60
            charge(ctx, 28);
            v0 = subu(s0, s3);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            mtc1(s2, f0);
            cvt_s_w(f0, f0);
            div_s(f3, f1, f0);
            lwc1(f2, gp, -32496);  // 0x7CAE00
            lwc1(f1, gp, -32272);  // 0x7CAEE0
            mtc1(zero, f0);
            adda_s(f0, f1);
            msub_s(f12, f2, f3);
            jal(ctx, 0x3CAB98u, gen::fn_sinf_0052e878);
            v0 = 0x3F800000;
            mtc1(v0, f2);
            add_s(f3, f2, f0);
            v0 = lui(0xC2A0);
            mtc1(v0, f1);
            sub_s(f0, f2, f3);
            mul_s(f1, f1, f0);
            swc1(f1, sp, 0x68);
            lb(v0, s1, 232);
            if (v0 == 0) {
                // 0x003cabd0
                charge(ctx, 5);
                v0 = lui(0xBF80);
                mtc1(v0, f0);
                mul_s(f0, f1, f0);
                swc1(f0, sp, 0x68);
            }
            // 0x003cabe4
            charge(ctx, 11);
            lh(v0, s1, 18);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            mul_s(f0, f0, f3);
            cvt_w_s(f0, f0);
            mfc1(a3, f0);
            lw(v0, s1, 8);
            v0 = v0 & 0x2;
            if (v0 == 0) {
                // 0x003cac30
                charge(ctx, 8);
                mtc1(zero, f12);
                ld(a0, sp, 0x68);
                a1 = s4;
                a2 = addiu(s4, 4);
                jal(ctx, 0x3CAC40u, gen::fn_sub_133180_00133180);
            } else {
                // 0x003cac10
                charge(ctx, 8);
                mtc1(zero, f12);
                ld(a0, sp, 0x68);
                a1 = s4;
                a2 = addiu(s4, 4);
                jal(ctx, 0x3CAC20u, gen::fn_sub_1332F0_001332f0);
            }
        }
    }
    // 0x003cac94 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003CFB50 sub_3CFB50 -- 764 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// The fclBank panels (three 20-byte records at the bank task's work +36 + 4): state 1/2 slide in over 5 frames (x
// from 256 / -126, alpha 255 * t / 5), 3 holds, 4/5 fade out over 5 frames; through the sprite setters sub_106FB0 /
// sub_106E90 / sub_106F60.
void sub_3CFB50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003cfb50
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, g::kGpBankTask);  // 0x7CE680 the fclBank task
    lw(v1, v1, 36);
    s1 = addiu(v1, 4);
    s0 = 0;
    for (;;) {
        // 0x003cfe28
        charge(ctx, 3);
        v1 = slti(s0, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003cfb78
        charge(ctx, 4);
        lh(v1, s1, 0);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            // 0x003cfb88
            charge(ctx, 4);
            lhu(v1, s1, 2);
            at = sltiu(v1, 6);
            if (at != 0) {
                // 0x003cfb98
                charge(ctx, 7);
                a0 = 0x7C0000;
                a0 = addiu(a0, -19216);  // &0x7BB4F0
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x3CFBB4u:  // table[1]
                    // 0x003cfbb4
                    charge(ctx, 15);
                    v0 = 2;
                    sh(v0, s1, 2);
                    lh(v0, s1, 0);
                    v0 = v0 | 0x8;
                    sh(v0, s1, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    v0 = v0 | 0x10;
                    sh(v0, s1, 0);
                    v1 = dsll32(v0, 16);
                    v1 = dsra32(v1, 16);
                    v0 = si(-5);
                    v0 = v1 & v0;
                    sh(v0, s1, 0);
                    sh(zero, s1, 16);
                L_003cfbf0:
                    charge(ctx, 7);
                    lh(v0, s1, 16);
                    v0 = addiu(v0, 1);
                    sh(v0, s1, 16);
                    lh(v1, s1, 0);
                    v0 = v1 & 0x20;
                    if (v0 == 0) {
                        // 0x003cfc30
                        charge(ctx, 3);
                        v0 = v1 & 0x100;
                        if (v0 == 0) {
                            // 0x003cfc5c
                            charge(ctx, 7);
                            lh(v0, s1, 16);
                            v1 = sll(v0, 5);
                            v0 = 5;
                            div(v1, v0);
                            mflo(v1);
                            v0 = 288;
                            a0 = subu(v0, v1);
                        } else {
                            // 0x003cfc3c
                            charge(ctx, 8);
                            lh(v0, s1, 16);
                            v1 = sll(v0, 5);
                            v0 = 5;
                            div(v1, v0);
                            mflo(v0);
                            a0 = addiu(v0, -158);
                        }
                    } else {
                        // 0x003cfc0c
                        charge(ctx, 3);
                        v0 = v1 & 0x100;
                        if (v0 == 0) {
                            // 0x003cfc24
                            charge(ctx, 3);
                            a0 = 256;
                        } else {
                            // 0x003cfc18
                            charge(ctx, 3);
                            a0 = si(-126);
                        }
                    }
                    // 0x003cfc78
                    charge(ctx, 4);
                    v1 = addiu(sp, 0x38);
                    v0 = 8;
                    if (v1 != 0) {
                        for (;;) {
                            // 0x003cfc88
                            charge(ctx, 7);
                            sb(zero, v1, 0);
                            v1 = addiu(v1, 1);
                            v0 = addiu(v0, -1);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                    // 0x003cfca4
                    charge(ctx, 26);
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0x38);
                    lh(a0, s1, 8);
                    ld(a1, sp, 0x38);
                    jal(ctx, 0x3CFCBCu, gen::fn_sub_106FB0_00106fb0);
                    lh(v1, s1, 16);
                    v0 = sll(v1, 8);
                    v1 = subu(v0, v1);
                    v0 = 5;
                    div(v1, v0);
                    mflo(v0);
                    a1 = v0 & 0xFF;
                    lh(a0, s1, 8);
                    jal(ctx, 0x3CFCE4u, gen::fn_sub_106E90_00106e90);
                    lh(a0, s1, 8);
                    a1 = 0;
                    jal(ctx, 0x3CFCF4u, gen::fn_sub_106F60_00106f60);
                    lh(v1, s1, 16);
                    v1 = slti(v1, 5);
                    if (v1 == 0) {
                        // 0x003cfd0c
                        charge(ctx, 13);
                        sh(zero, s1, 16);
                        lh(v1, s1, 0);
                        v1 = v1 | 0x4;
                        sh(v1, s1, 0);
                        a0 = dsll32(v1, 16);
                        a0 = dsra32(a0, 16);
                        v1 = si(-17);
                        v1 = a0 & v1;
                        sh(v1, s1, 0);
                        v1 = 3;
                        sh(v1, s1, 2);
                    }
                    break;
                case 0x3CFBF0u:  // table[2]
                    goto L_003cfbf0;
                case 0x3CFD40u:  // table[3]
                    // 0x003cfd40
                    charge(ctx, 6);
                    lh(a0, s1, 8);
                    a1 = 0;
                    jal(ctx, 0x3CFD48u, gen::fn_sub_106F60_00106f60);
                    break;
                case 0x3CFD58u:  // table[4]
                    // 0x003cfd58
                    charge(ctx, 11);
                    v0 = 5;
                    sh(v0, s1, 2);
                    lh(v0, s1, 0);
                    v0 = v0 | 0x10;
                    sh(v0, s1, 0);
                    v1 = dsll32(v0, 16);
                    v1 = dsra32(v1, 16);
                    v0 = si(-5);
                    v0 = v1 & v0;
                    sh(v0, s1, 0);
                    sh(zero, s1, 16);
                L_003cfd84:
                    charge(ctx, 24);
                    lh(v0, s1, 16);
                    v0 = addiu(v0, 1);
                    sh(v0, s1, 16);
                    v1 = dsll32(v0, 16);
                    v1 = dsra32(v1, 16);
                    v0 = sll(v1, 8);
                    v1 = subu(v0, v1);
                    v0 = 5;
                    div(v1, v0);
                    mflo(v1);
                    v0 = 255;
                    v0 = subu(v0, v1);
                    a1 = v0 & 0xFF;
                    lh(a0, s1, 8);
                    jal(ctx, 0x3CFDBCu, gen::fn_sub_106E90_00106e90);
                    lh(a0, s1, 8);
                    a1 = 0;
                    jal(ctx, 0x3CFDCCu, gen::fn_sub_106F60_00106f60);
                    lh(v1, s1, 16);
                    v1 = slti(v1, 5);
                    if (v1 == 0) {
                        // 0x003cfde4
                        charge(ctx, 15);
                        sh(zero, s1, 16);
                        lh(a0, s1, 0);
                        v1 = si(-9);
                        v1 = a0 & v1;
                        sh(v1, s1, 0);
                        v1 = dsll32(v1, 16);
                        v1 = dsra32(v1, 16);
                        v1 = v1 | 0x4;
                        sh(v1, s1, 0);
                        a0 = dsll32(v1, 16);
                        a0 = dsra32(a0, 16);
                        v1 = si(-17);
                        v1 = a0 & v1;
                        sh(v1, s1, 0);
                        sh(zero, s1, 2);
                    }
                    break;
                case 0x3CFD84u:  // table[5]
                    goto L_003cfd84;
                case 0x3CFE20u:  // table[0]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
        }
        // 0x003cfe20
        charge(ctx, 2);
        s1 = addiu(s1, 20);
        s0 = addiu(s0, 1);
    }
    // 0x003cfe34
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

}  // namespace p3fes::game
