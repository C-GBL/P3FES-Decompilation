// Phase 5 slice cri2: libmpeg's pure parts (0x4FB168-0x501408) -- the motion-compensation set-up and the 16
// interpolation kernels, the residual add, the sequence buffer layout, the GOP / picture header parsers and the
// extension walker, the picture loop and the reference rotation. Written from the binary and the public MPEG-2
// video syntax (ISO/IEC 13818-2) only. Everything that touches the IPU (the bit reader _sceMpegNextBit /
// _sceMpegPeepBit / _sceMpegFlushBuf, flushByteBoundary, the waits, the DMA) stays recompiled; these bodies call it.
// p3fes_handgen bodies with a role comment per function and the decoder state's fields named (cri2::mpeg).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/cri2.h"

namespace p3fes::recomp_gen {
void fn___muldi3_0052ea78(p3fes::EEContext&);
void fn__copyAddRefImage_004fd968(p3fes::EEContext&);
void fn__cpr8_00501178(p3fes::EEContext&);
void fn__decPicture_00500f98(p3fes::EEContext&);
void fn__decodeOrSkipField_00500858(p3fes::EEContext&);
void fn__decodeOrSkipFrame_005006e8(p3fes::EEContext&);
void fn__decodeOrSkip_00500e00(p3fes::EEContext&);
void fn__dispRefImage_00501408(p3fes::EEContext&);
void fn__dualPrimeVector_004fafe0(p3fes::EEContext&);
void fn__extensionAndUserData_004ff7c8(p3fes::EEContext&);
void fn__getAllRefs_004fb168(p3fes::EEContext&);
void fn__getRef0_004fbac0(p3fes::EEContext&);
void fn__getpic_00500278(p3fes::EEContext&);
void fn__groupOfPicturesHeader_004ff190(p3fes::EEContext&);
void fn__initSeq_004febc8(p3fes::EEContext&);
void fn__pictureHeader_004ff230(p3fes::EEContext&);
void fn__ri0_000_004fdd10(p3fes::EEContext&);
void fn__ri0_001_004fde60(p3fes::EEContext&);
void fn__ri0_010_004fdfe0(p3fes::EEContext&);
void fn__ri0_011_004fe190(p3fes::EEContext&);
void fn__ri0_100_004fe330(p3fes::EEContext&);
void fn__ri0_101_004fe4c0(p3fes::EEContext&);
void fn__ri0_110_004fe680(p3fes::EEContext&);
void fn__ri0_111_004fe870(p3fes::EEContext&);
void fn__rix_000_004fdc98(p3fes::EEContext&);
void fn__rix_001_004fdda8(p3fes::EEContext&);
void fn__rix_010_004fdf30(p3fes::EEContext&);
void fn__rix_011_004fe098(p3fes::EEContext&);
void fn__rix_100_004fe290(p3fes::EEContext&);
void fn__rix_101_004fe3e0(p3fes::EEContext&);
void fn__rix_110_004fe5a8(p3fes::EEContext&);
void fn__rix_111_004fe750(p3fes::EEContext&);
void fn__sceMpegAlalcAlloc_005010a0(p3fes::EEContext&);
void fn__sceMpegAlalcFree_00501090(p3fes::EEContext&);
void fn__sceMpegCscStoreRefImage_00501df8(p3fes::EEContext&);
void fn__sceMpegError1_005026c0(p3fes::EEContext&);
void fn__sceMpegError_00502668(p3fes::EEContext&);
void fn__sceMpegFlush_00501ae8(p3fes::EEContext&);
void fn__sceMpegNextBit_004fd658(p3fes::EEContext&);
void fn__sceMpegNextHeader_004ff9d8(p3fes::EEContext&);
void fn__sceMpegOutputFrame_00501ba8(p3fes::EEContext&);
void fn__sceMpegPeepBit_004fd740(p3fes::EEContext&);
void fn__sceMpegPictureData0_004fc168(p3fes::EEContext&);
void fn__skipMB0_004fd8a8(p3fes::EEContext&);
void fn__updateRefImage_00500430(p3fes::EEContext&);
void fn_flushBuf32_004ffb30(p3fes::EEContext&);
void fn_flushByteBoundary_004ffb38(p3fes::EEContext&);
void fn_j__sceMpegFlushBuf_0_004ff9d0(p3fes::EEContext&);
void fn_scePrintf_00505e48(p3fes::EEContext&);
void fn_sceSnprintf_00505d90(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace cri2;

// 0x004FB168 _getAllRefs -- 1796 bytes; frame 0xF0: fp sp+0xD0, s6 sp+0xB0, s5 sp+0xA0, s4 sp+0x90, s3 sp+0x80, s2 sp+0x70, s1 sp+0x60, s0 sp+0x50, ra sp+0xE0, s7 sp+0xC0
// set up every reference fetch of a macroblock: frame / field / dual-prime prediction, forward and backward
//   (motion_type per picture structure). [_getAllRefs]
void _getAllRefs(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fb168
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    v1 = 320;
    sd(fp, sp, 0xD0);
    sd(s6, sp, 0xB0);
    fp = t2;
    sd(s5, sp, 0xA0);
    s6 = a2;
    sd(s4, sp, 0x90);
    s5 = a1;
    sd(s3, sp, 0x80);
    s4 = t0;
    sd(s2, sp, 0x70);
    s3 = 1;
    sd(s1, sp, 0x60);
    s2 = t1;
    sd(s0, sp, 0x50);
    s1 = a0;
    sd(ra, sp, 0xE0);
    s0 = 0;
    sd(s7, sp, 0xC0);
    lw(v0, s1, 2080);
    sw(a3, sp, 0x40);
    mult(a0, v0, v1);
    t4 = a3 & 0x8;
    v0 = addu(a0, s1);
    sw(zero, v0, 1740);
    if (t4 == 0) {
        // 0x004fb1d4
        charge(ctx, 4);
        lw(v1, s1, mpeg::kPicType);
        v0 = 2;
        lw(a0, sp, 0x40);
        if (v1 == v0) {
            goto L_004fb1e4;
        }
        goto L_004fb650;
    }
L_004fb1e4:
    charge(ctx, 4);
    lw(v1, s1, mpeg::kPicStruct);
    v0 = 3;
    cc = v1 != v0;  // the condition, before the delay slot changes it
    v0 = v1 ^ 0x2;
    if (!cc) {
        // 0x004fb1f4
        charge(ctx, 3);
        v0 = 2;
        if (s4 == v0) {
            lw(v0, s2, 0);
        } else {
            // 0x004fb200
            charge(ctx, 2);
            if (t4 == 0) {
                // 0x004fb208
                charge(ctx, 1);
                lw(v0, s2, 0);
                goto L_004fb20c;
            }
            // 0x004fb240
            charge(ctx, 2);
            a0 = s1;
            if (s4 != s3) {
                // 0x004fb2cc
                charge(ctx, 2);
                a1 = 0x7C0000;
                if (s4 == v1) {
                    // 0x004fb2d4
                    charge(ctx, 68);
                    lw(t0, s2, 4);
                    a2 = t3;
                    lw(a3, s2, 0);
                    a0 = s1;
                    t0 = sra(t0, 1);
                    a1 = addiu(sp, 0x20);
                    jal(ctx, 0x4FB2E8u, gen::fn__dualPrimeVector_004fafe0);
                    lw(v0, s2, 4);
                    a0 = s1;
                    lw(v1, s2, 0);
                    a2 = 0;
                    lw(a1, s1, mpeg::kRefFwd);
                    v0 = sra(v0, 1);
                    sw(v1, sp, 0x0);
                    a3 = 0;
                    sw(v0, sp, 0x8);
                    t0 = 0;
                    sw(s3, sp, 0x10);
                    t1 = 8;
                    sw(zero, sp, 0x18);
                    t2 = s5;
                    t3 = s6;
                    jal(ctx, 0x4FB328u, gen::fn__getRef0_004fbac0);
                    lw(v0, sp, 0x20);
                    a0 = s1;
                    lw(v1, sp, 0x24);
                    a2 = 1;
                    lw(a1, s1, mpeg::kRefFwd);
                    a3 = 0;
                    sw(v0, sp, 0x0);
                    t0 = 0;
                    sw(v1, sp, 0x8);
                    t1 = 8;
                    sw(s3, sp, 0x10);
                    t2 = s5;
                    sw(s3, sp, 0x18);
                    t3 = s6;
                    jal(ctx, 0x4FB364u, gen::fn__getRef0_004fbac0);
                    lw(v0, s2, 4);
                    a0 = s1;
                    lw(v1, s2, 0);
                    a2 = 1;
                    lw(a1, s1, mpeg::kRefFwd);
                    v0 = sra(v0, 1);
                    sw(v1, sp, 0x0);
                    a3 = 1;
                    sw(v0, sp, 0x8);
                    t0 = 0;
                    sw(s3, sp, 0x10);
                    t1 = 8;
                    sw(zero, sp, 0x18);
                    t2 = s5;
                    t3 = s6;
                    jal(ctx, 0x4FB3A4u, gen::fn__getRef0_004fbac0);
                    lw(v0, sp, 0x28);
                    a0 = s1;
                    lw(v1, sp, 0x2C);
                    a2 = 0;
                    lw(a1, s1, mpeg::kRefFwd);
                    a3 = 1;
                    sw(v0, sp, 0x0);
                    t0 = 0;
                    sw(v1, sp, 0x8);
                    t1 = 8;
                    sw(s3, sp, 0x18);
                    t2 = s5;
                    sw(s3, sp, 0x10);
                    goto L_004fb628;
                }
                // 0x004fb3e4
                charge(ctx, 6);
                a0 = s1;
                a1 = addiu(a1, -11072);
                a2 = s4;
                jal(ctx, 0x4FB3ECu, gen::fn__sceMpegError1_005026c0);
                s0 = 1;
            } else {
                // 0x004fb248
                charge(ctx, 33);
                lw(v0, s2, 4);
                lw(v1, s2, 0);
                a3 = 0;
                lw(a1, s1, mpeg::kRefFwd);
                v0 = sra(v0, 1);
                lw(a2, fp, 0x0);
                t0 = 0;
                sw(v1, sp, 0x0);
                t1 = 8;
                sw(v0, sp, 0x8);
                t2 = s5;
                sw(s4, sp, 0x10);
                t3 = s6;
                link(ctx, 0x4FB27Cu);  // $ra first: the delay slot below depends on it
                sw(zero, sp, 0x18);
                call(ctx, gen::fn__getRef0_004fbac0);
                lw(v0, s2, 20);
                a0 = s1;
                lw(v1, s2, 16);
                a3 = 1;
                lw(a1, s1, mpeg::kRefFwd);
                v0 = sra(v0, 1);
                lw(a2, fp, 0x8);
                t0 = 0;
                sw(v1, sp, 0x0);
                t1 = 8;
                sw(v0, sp, 0x8);
                t2 = s5;
                sw(s4, sp, 0x10);
                t3 = s6;
                link(ctx, 0x4FB2BCu);  // $ra first: the delay slot below depends on it
                sw(zero, sp, 0x18);
                call(ctx, gen::fn__getRef0_004fbac0);
                s0 = 1;
            }
            goto L_004fb64c;
        }
    L_004fb20c:
        charge(ctx, 13);
        a0 = s1;
        lw(v1, s2, 4);
        a2 = 0;
        lw(a1, s1, mpeg::kRefFwd);
        a3 = 0;
        sw(v0, sp, 0x0);
        t0 = 0;
        sw(v1, sp, 0x8);
        t1 = 16;
        sw(zero, sp, 0x10);
        t2 = s5;
        sw(zero, sp, 0x18);
        goto L_004fb628;
    }
    // 0x004fb3fc
    charge(ctx, 13);
    lw(a3, s1, 472);
    lw(a1, s1, 488);
    s7 = sltiu(v0, 1);
    lw(a0, s1, 476);
    a2 = 2;
    lw(v1, s1, 492);
    s3 = 0;
    lw(v0, s1, mpeg::kPicType);
    sw(a3, sp, 0x30);
    sw(a1, sp, 0x34);
    sw(a0, sp, 0x38);
    sw(v1, sp, 0x3C);
    if (v0 == a2) {
        // 0x004fb430
        charge(ctx, 3);
        lw(v0, s1, mpeg::kFieldParity);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (!cc) {
            // 0x004fb43c
            charge(ctx, 3);
            lw(v0, fp, 0x0);
            v0 = s7 ^ v0;
            s3 = sltu(0, v0);
            goto L_004fb448;
        }
        goto L_004fb44c;
    }
L_004fb448:
    charge(ctx, 1);
    v0 = 1;
L_004fb44c:
    charge(ctx, 2);
    if (s4 == v0) {
        lw(v0, fp, 0x0);
    } else {
        // 0x004fb454
        charge(ctx, 2);
        v0 = 2;
        if (t4 == 0) {
            // 0x004fb45c
            charge(ctx, 1);
            lw(v0, fp, 0x0);
            goto L_004fb460;
        }
        // 0x004fb49c
        charge(ctx, 2);
        cc = s4 != v0;  // the condition, before the delay slot changes it
        v0 = 3;
        if (!cc) {
            // 0x004fb4a4
            charge(ctx, 24);
            lw(v0, fp, 0x0);
            a1 = sll(s3, 3);
            lw(a0, s2, 4);
            s0 = addiu(sp, 0x30);
            lw(v1, s2, 0);
            v0 = sll(v0, 2);
            v0 = addu(v0, a1);
            sw(a0, sp, 0x8);
            sw(v1, sp, 0x0);
            v0 = addu(s0, v0);
            a0 = s1;
            a2 = 0;
            lw(a1, v0, 0);
            a3 = 0;
            sw(zero, sp, 0x10);
            t0 = 0;
            sw(zero, sp, 0x18);
            t1 = 8;
            t2 = s5;
            t3 = s6;
            jal(ctx, 0x4FB4F0u, gen::fn__getRef0_004fbac0);
            lw(v0, s1, mpeg::kPicType);
            s3 = 0;
            if (v0 != s4) {
                // 0x004fb520
                charge(ctx, 1);
                lw(v1, fp, 0x8);
            } else {
                // 0x004fb504
                charge(ctx, 3);
                lw(v0, s1, mpeg::kFieldParity);
                lw(v1, fp, 0x8);
                if (v0 != 0) {
                    // 0x004fb510
                    charge(ctx, 4);
                    s3 = 1;
                    v0 = s7 ^ v1;
                    if (v0 == 0) s3 = 0;
                }
            }
            // 0x004fb524
            charge(ctx, 18);
            v0 = sll(v1, 2);
            lw(a2, s2, 16);
            v1 = sll(s3, 3);
            a0 = s1;
            v0 = addu(v0, v1);
            a3 = 0;
            v0 = addu(s0, v0);
            lw(v1, s2, 20);
            lw(a1, v0, 0);
            t0 = 8;
            sw(a2, sp, 0x0);
            t1 = 8;
            a2 = 0;
            sw(v1, sp, 0x8);
            sw(zero, sp, 0x10);
            t2 = s5;
            sw(zero, sp, 0x18);
            goto L_004fb628;
        }
        // 0x004fb56c
        charge(ctx, 2);
        a1 = 0x7C0000;
        if (s4 != v0) {
            // 0x004fb638
            charge(ctx, 5);
            a0 = s1;
            a1 = addiu(a1, -11040);
            a2 = s4;
            jal(ctx, 0x4FB640u, gen::fn__sceMpegError1_005026c0);
            s0 = 1;
        } else {
            // 0x004fb574
            charge(ctx, 42);
            lw(v0, s1, mpeg::kFieldParity);
            s3 = 1;
            lw(a3, s2, 0);
            a2 = t3;
            lw(t0, s2, 4);
            if (v0 == 0) s3 = 0;
            a0 = s1;
            a1 = addiu(sp, 0x20);
            jal(ctx, 0x4FB590u, gen::fn__dualPrimeVector_004fafe0);
            s0 = addiu(sp, 0x30);
            v0 = sll(s7, 2);
            lw(t0, s2, 4);
            v0 = addu(s0, v0);
            lw(v1, s2, 0);
            a0 = s1;
            lw(a1, v0, 0);
            a2 = 0;
            sw(t0, sp, 0x8);
            a3 = 0;
            sw(v1, sp, 0x0);
            t0 = 0;
            sw(zero, sp, 0x10);
            t1 = 16;
            sw(zero, sp, 0x18);
            t2 = s5;
            t3 = s6;
            jal(ctx, 0x4FB5D8u, gen::fn__getRef0_004fbac0);
            v1 = sll(s3, 3);
            lw(a0, sp, 0x20);
            v0 = addiu(v1, 4);
            lw(a1, sp, 0x24);
            if (s7 != 0) v0 = v1;
            sw(a0, sp, 0x0);
            s0 = addu(s0, v0);
            sw(a1, sp, 0x8);
            lw(a1, s0, 0);
            v1 = 1;
            a0 = s1;
            sw(v1, sp, 0x18);
            a2 = 0;
            sw(zero, sp, 0x10);
            a3 = 0;
        L_004fb61c:
            charge(ctx, 3);
            t0 = 0;
            t1 = 16;
            t2 = s5;
        L_004fb628:
            charge(ctx, 4);
            t3 = s6;
            jal(ctx, 0x4FB628u, gen::fn__getRef0_004fbac0);
            s0 = 1;
        }
        goto L_004fb64c;
    }
L_004fb460:
    charge(ctx, 15);
    v1 = sll(s3, 3);
    lw(a2, s2, 0);
    a0 = s1;
    lw(a1, s2, 4);
    v0 = sll(v0, 2);
    sw(a2, sp, 0x0);
    v0 = addu(v0, v1);
    v1 = addu(sp, v0);
    sw(a1, sp, 0x8);
    lw(a1, v1, 48);
    a2 = 0;
    sw(zero, sp, 0x10);
    a3 = 0;
    sw(zero, sp, 0x18);
    goto L_004fb61c;
L_004fb64c:
    charge(ctx, 1);
    lw(a0, sp, 0x40);
L_004fb650:
    charge(ctx, 3);
    v0 = a0 & 0x4;
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 3;
    if (!cc) {
        // 0x004fb65c
        charge(ctx, 3);
        lw(v1, s1, mpeg::kPicStruct);
        cc = v1 != v0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (cc) {
            // 0x004fb734
            charge(ctx, 2);
            cc = s4 != v0;  // the condition, before the delay slot changes it
            v0 = 2;
            if (cc) {
                // 0x004fb78c
                charge(ctx, 2);
                a1 = 0x7C0000;
                if (s4 != v0) {
                    // 0x004fb82c
                    charge(ctx, 4);
                    a0 = s1;
                    a1 = addiu(a1, -11008);
                    a2 = s4;
                    jal(ctx, 0x4FB834u, gen::fn__sceMpegError1_005026c0);
                    goto L_004fb83c;
                }
                // 0x004fb794
                charge(ctx, 3);
                lw(v0, fp, 0x4);
                if (v0 == 0) {
                    lw(a1, s1, 476);
                } else {
                    // 0x004fb7a0
                    charge(ctx, 1);
                    lw(a1, s1, 492);
                }
                // 0x004fb7a4
                charge(ctx, 17);
                lw(v0, s2, 8);
                a0 = s1;
                lw(v1, s2, 12);
                a2 = 0;
                sw(v0, sp, 0x0);
                a3 = 0;
                sw(v1, sp, 0x8);
                t0 = 0;
                sw(zero, sp, 0x10);
                t1 = 8;
                sw(s0, sp, 0x18);
                t2 = s5;
                t3 = s6;
                jal(ctx, 0x4FB7D4u, gen::fn__getRef0_004fbac0);
                lw(v0, fp, 0xC);
                if (v0 == 0) {
                    lw(a1, s1, 476);
                } else {
                    // 0x004fb7e8
                    charge(ctx, 1);
                    lw(a1, s1, 492);
                }
                // 0x004fb7ec
                charge(ctx, 16);
                lw(v0, s2, 28);
                a0 = s1;
                lw(v1, s2, 24);
                t2 = s5;
                sw(v0, sp, 0x8);
                t3 = s6;
                sw(v1, sp, 0x0);
                a2 = 0;
                sw(s0, sp, 0x18);
                a3 = 0;
                sw(zero, sp, 0x10);
                t0 = 8;
                t1 = 8;
                jal(ctx, 0x4FB81Cu, gen::fn__getRef0_004fbac0);
                ld(ra, sp, 0xE0);
            } else {
                // 0x004fb73c
                charge(ctx, 3);
                lw(v0, fp, 0x4);
                if (v0 == 0) {
                    lw(a1, s1, 476);
                } else {
                    // 0x004fb748
                    charge(ctx, 1);
                    lw(a1, s1, 492);
                }
                // 0x004fb74c
                charge(ctx, 16);
                lw(v0, s2, 12);
                a0 = s1;
                lw(v1, s2, 8);
                t2 = s5;
                sw(v0, sp, 0x8);
                t3 = s6;
                sw(v1, sp, 0x0);
                a2 = 0;
                sw(s0, sp, 0x18);
                a3 = 0;
                sw(zero, sp, 0x10);
                t0 = 0;
                t1 = 16;
                jal(ctx, 0x4FB77Cu, gen::fn__getRef0_004fbac0);
                ld(ra, sp, 0xE0);
            }
        } else {
            // 0x004fb668
            charge(ctx, 3);
            v0 = 2;
            s3 = 1;
            if (s4 != v0) {
                // 0x004fb6ac
                charge(ctx, 30);
                lw(v0, s2, 12);
                a0 = s1;
                lw(v1, s2, 8);
                a3 = 0;
                lw(a1, s1, mpeg::kRefBwd);
                v0 = sra(v0, 1);
                lw(a2, fp, 0x4);
                t0 = 0;
                sw(v1, sp, 0x0);
                t1 = 8;
                sw(v0, sp, 0x8);
                t2 = s5;
                sw(s3, sp, 0x10);
                t3 = s6;
                link(ctx, 0x4FB6E4u);  // $ra first: the delay slot below depends on it
                sw(s0, sp, 0x18);
                call(ctx, gen::fn__getRef0_004fbac0);
                lw(v0, s2, 28);
                a0 = s1;
                lw(v1, s2, 24);
                t2 = s5;
                v0 = sra(v0, 1);
                sw(s3, sp, 0x10);
                sw(v1, sp, 0x0);
                t3 = s6;
                sw(v0, sp, 0x8);
                a3 = 1;
                sw(s0, sp, 0x18);
                t0 = 0;
                t1 = 8;
                lw(a2, fp, 0xC);
            } else {
                // 0x004fb674
                charge(ctx, 14);
                lw(v0, s2, 12);
                a0 = s1;
                lw(v1, s2, 8);
                t2 = s5;
                sw(v0, sp, 0x8);
                t3 = s6;
                sw(v1, sp, 0x0);
                a2 = 0;
                sw(s0, sp, 0x18);
                a3 = 0;
                sw(zero, sp, 0x10);
                t0 = 0;
                t1 = 16;
            }
            // 0x004fb724
            charge(ctx, 4);
            link(ctx, 0x4FB724u);  // $ra first: the delay slot below depends on it
            lw(a1, a0, 460);
            call(ctx, gen::fn__getRef0_004fbac0);
            ld(ra, sp, 0xE0);
        }
        // 0x004fb840 (the shared epilogue, written out on this path)
        charge(ctx, 11);
        ld(fp, sp, 0xD0);
        ld(s7, sp, 0xC0);
        ld(s6, sp, 0xB0);
        ld(s5, sp, 0xA0);
        ld(s4, sp, 0x90);
        ld(s3, sp, 0x80);
        ld(s2, sp, 0x70);
        ld(s1, sp, 0x60);
        ld(s0, sp, 0x50);
        sp = addiu(sp, 0xF0);
        return;
    }
L_004fb83c:
    charge(ctx, 1);
    ld(ra, sp, 0xE0);
    // 0x004fb840 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(fp, sp, 0xD0);
    ld(s7, sp, 0xC0);
    ld(s6, sp, 0xB0);
    ld(s5, sp, 0xA0);
    ld(s4, sp, 0x90);
    ld(s3, sp, 0x80);
    ld(s2, sp, 0x70);
    ld(s1, sp, 0x60);
    ld(s0, sp, 0x50);
    sp = addiu(sp, 0xF0);
}

// 0x004FBAC0 _getRef0 -- 1160 bytes; frame 0xB0: fp sp+0xA0, s5 sp+0x70, s2 sp+0x40, s1 sp+0x30, s0 sp+0x20, s7 sp+0x90, s6 sp+0x80, s4 sp+0x60, s3 sp+0x50
// set up one reference fetch: the source macroblock addresses for a vector, the rows before / after the macroblock
//   boundary, the luma and chroma kernels by half-pel bits and averaging. [_getRef0]
void _getRef0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fbac0
    enter(ctx, 41);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    t7 = a0;
    sd(fp, sp, 0xA0);
    v1 = addiu(t7, 1740);
    sd(s5, sp, 0x70);
    v0 = 320;
    sd(s2, sp, 0x40);
    t6 = t1;
    sd(s1, sp, 0x30);
    s2 = a2;
    sd(s0, sp, 0x20);
    s1 = t3;
    sd(s7, sp, 0x90);
    s0 = t0;
    sd(s6, sp, 0x80);
    sd(s4, sp, 0x60);
    sd(s3, sp, 0x50);
    lw(s3, t7, 2080);
    sw(v1, sp, 0xC);
    mult(v0, s3, v0);
    lw(fp, sp, 0xB0);
    lw(a0, t7, 2096);
    sw(t2, sp, 0x4);
    sw(a0, sp, 0x8);
    t2 = sra(fp, 1);
    sw(a3, sp, 0x0);
    v1 = addu(v1, v0);
    a0 = 28;
    v0 = addiu(v0, 1440);
    lw(t9, v1, 0);
    v0 = addu(t7, v0);
    lw(a2, sp, 0x4);
    mult(a0, t9, a0);
    lw(t8, sp, 0xC0);
    t2 = addu(t2, a2);
    lw(s5, sp, 0xB8);
    v1 = addiu(a0, 184);
    a0 = addiu(a0, 72);
    t5 = addu(v0, v1);
    t4 = addu(v0, a0);
    if (t8 == 0) {
        // 0x004fbb74
        charge(ctx, 2);
        v0 = sra(s5, 1);
        v1 = addu(s0, s2);
    } else {
        // 0x004fbb64
        charge(ctx, 4);
        v0 = sra(s5, 1);
        v1 = addu(s0, s2);
        v0 = sll(v0, 1);
    }
    // 0x004fbb7c
    charge(ctx, 37);
    v0 = addu(v0, s1);
    t3 = addu(v0, v1);
    lw(a3, a1, 16);
    s6 = sra(t2, 4);
    v0 = 320;
    lw(t1, a1, 0);
    mult(v1, s6, a3);
    mult1(v0, s3, v0);
    s7 = sra(t3, 4);
    t0 = sll(t9, 2);
    sw(t0, sp, 0x10);
    a2 = 384;
    lw(a1, sp, 0x0);
    v0 = addu(t0, v0);
    v1 = addu(v1, s7);
    mult(t0, v1, a2);
    a0 = addu(a1, s0);
    v1 = addu(v1, a3);
    a0 = sll(a0, 5);
    mult(a3, v1, a2);
    a1 = sll(s6, 4);
    lw(v1, sp, 0x8);
    a1 = subu(t2, a1);
    s3 = addu(t1, t0);
    t2 = s5 & 0x1;
    a0 = addu(v1, a0);
    sw(a1, t4, 4);
    s4 = addu(a3, t1);
    v1 = sll(s7, 4);
    a3 = addu(t7, v0);
    t3 = subu(t3, v1);
    v0 = a3;
    sw(s3, a3, 1448);
    a3 = fp & 0x1;
    sw(s4, v0, 1464);
    sw(a0, t4, 0);
    if (t2 == 0) {
        // 0x004fbc48
        charge(ctx, 5);
        v0 = sllv(t6, t8);
        v0 = addu(t3, v0);
        v0 = slti(v0, 17);
        if (v0 != 0) {
            sw(t6, t4, 8);
        L_004fbc7c:
            charge(ctx, 1);
            sw(zero, t4, 12);
        } else {
            // 0x004fbc5c
            charge(ctx, 8);
            v0 = 16;
            v1 = srav(t3, t8);
            v0 = srav(v0, t8);
            v0 = subu(v0, v1);
            a0 = subu(t6, v0);
            sw(v0, t4, 8);
            sw(a0, t4, 12);
        }
    } else {
        // 0x004fbc10
        charge(ctx, 5);
        v0 = sllv(t6, t8);
        v0 = addu(t3, v0);
        v0 = slti(v0, 16);
        if (v0 != 0) {
            sw(t6, t4, 8);
            goto L_004fbc7c;
        }
        // 0x004fbc24
        charge(ctx, 9);
        v0 = 16;
        v1 = srav(t3, t8);
        v0 = srav(v0, t8);
        v0 = subu(v0, v1);
        v0 = addiu(v0, -1);
        v1 = subu(t6, v0);
        sw(v0, t4, 8);
        sw(v1, t4, 12);
    }
    // 0x004fbc80
    charge(ctx, 3);
    lw(v0, t7, 2172);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = sll(t3, 4);
    if (cc) {
        // 0x004fbcc8
        charge(ctx, 5);
        t0 = s3;
        v1 = addu(s4, v0);
        v0 = addu(s3, v0);
        sw(v1, t4, 24);
        sw(v0, t4, 20);
    } else {
        // 0x004fbc8c
        charge(ctx, 15);
        lw(a2, t7, 2080);
        v0 = 320;
        v1 = 1536;
        a1 = sll(t3, 4);
        mult(a0, a2, v0);
        mult(v1, t9, v1);
        a2 = addu(a0, t7);
        lw(v0, a2, 1440);
        a0 = addiu(a1, 768);
        t0 = addu(v0, v1);
        a0 = addu(t0, a0);
        a1 = addu(t0, a1);
        sw(a1, t4, 20);
        sw(a0, t4, 24);
    }
    // 0x004fbcdc
    charge(ctx, 23);
    lw(v0, sp, 0xC8);
    v1 = sll(a3, 1);
    a0 = srl(fp, 31);
    a1 = 16;
    v0 = sll(v0, 2);
    a0 = addu(fp, a0);
    sw(v0, sp, 0x14);
    t9 = sra(a0, 1);
    v0 = srl(s5, 31);
    a1 = sllv(a1, t8);
    lw(a3, sp, 0x14);
    a2 = addu(s5, v0);
    a0 = sra(a0, 2);
    s5 = sra(a2, 1);
    v1 = a3 | v1;
    t1 = sra(t6, 1);
    fp = v1 | t2;
    a3 = sra(s0, 1);
    lw(v1, sp, 0x4);
    sw(a1, t4, 16);
    v0 = sra(v1, 1);
    t2 = addu(a0, v0);
    if (t8 == 0) {
        // 0x004fbd54
        charge(ctx, 5);
        v0 = sra(a2, 2);
        v1 = sra(s1, 1);
        v0 = addu(v0, v1);
        a0 = addu(a3, s2);
        t3 = addu(v0, a0);
    } else {
        // 0x004fbd38
        charge(ctx, 7);
        v0 = sra(a2, 2);
        a0 = sra(s1, 1);
        v0 = sll(v0, 1);
        v1 = addu(a3, s2);
        v0 = addu(v0, a0);
        t3 = addu(v0, v1);
    }
    // 0x004fbd68
    charge(ctx, 17);
    lw(a0, sp, 0x0);
    a2 = sra(t2, 3);
    a1 = sra(t3, 3);
    v1 = sll(a2, 3);
    v0 = addu(a0, a3);
    v1 = subu(t2, v1);
    lw(a3, sp, 0x8);
    v0 = sll(v0, 4);
    v0 = addiu(v0, 512);
    a0 = sll(a1, 3);
    v0 = addu(a3, v0);
    t3 = subu(t3, a0);
    a3 = t9 & 0x1;
    t2 = s5 & 0x1;
    sw(v1, t5, 4);
    sw(v0, t5, 0);
    if (t2 == 0) {
        // 0x004fbde4
        charge(ctx, 5);
        v0 = sllv(t1, t8);
        v0 = addu(t3, v0);
        v0 = slti(v0, 9);
        if (v0 != 0) {
            sw(t1, t5, 8);
        L_004fbe18:
            charge(ctx, 1);
            sw(zero, t5, 12);
        } else {
            // 0x004fbdf8
            charge(ctx, 8);
            v0 = 8;
            v1 = srav(t3, t8);
            v0 = srav(v0, t8);
            v0 = subu(v0, v1);
            a0 = subu(t1, v0);
            sw(v0, t5, 8);
            sw(a0, t5, 12);
        }
    } else {
        // 0x004fbdac
        charge(ctx, 5);
        v0 = sllv(t1, t8);
        v0 = addu(t3, v0);
        v0 = slti(v0, 8);
        if (v0 != 0) {
            sw(t1, t5, 8);
            goto L_004fbe18;
        }
        // 0x004fbdc0
        charge(ctx, 9);
        v0 = 8;
        v1 = srav(t3, t8);
        v0 = srav(v0, t8);
        v0 = subu(v0, v1);
        v0 = addiu(v0, -1);
        v1 = subu(t1, v0);
        sw(v0, t5, 8);
        sw(v1, t5, 12);
    }
    // 0x004fbe1c
    charge(ctx, 9);
    v0 = subu(a2, s6);
    v1 = subu(a1, s7);
    v0 = sll(v0, 1);
    a0 = 384;
    v0 = addu(v0, v1);
    lw(a1, t7, 2172);
    mult(v1, v0, a0);
    a0 = addu(t0, v1);
    if (a1 != 0) {
        // 0x004fbe60
        charge(ctx, 6);
        a0 = sll(t3, 3);
        a1 = addiu(a0, 256);
        v0 = addu(v1, a1);
        v0 = sltiu(v0, 769);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = addu(s3, v1);
        if (cc) {
            // 0x004fbe84
            charge(ctx, 3);
            v1 = addu(s4, v1);
            v0 = addu(v1, a1);
            v0 = addiu(v0, -768);
        } else {
            // 0x004fbe78
            charge(ctx, 3);
            v0 = addu(v0, a1);
            v1 = addu(s4, v1);
        }
        // 0x004fbe90
        charge(ctx, 4);
        sw(v0, t5, 20);
        v0 = addiu(a0, 256);
        v0 = addu(v1, v0);
        sw(v0, t5, 24);
    } else {
        // 0x004fbe40
        charge(ctx, 8);
        v0 = sll(t3, 3);
        v1 = addiu(v0, 1024);
        v0 = addiu(v0, 256);
        v1 = addu(a0, v1);
        v0 = addu(a0, v0);
        sw(v1, t5, 24);
        sw(v0, t5, 20);
    }
    // 0x004fbea0
    charge(ctx, 42);
    v0 = 8;
    a0 = 0x780000;
    v0 = sllv(v0, t8);
    a0 = addiu(a0, -3336);  // &0x77F2F8
    sw(v0, t5, 16);
    v1 = sll(a3, 1);
    v0 = sll(fp, 2);
    a2 = 320;
    lw(t0, sp, 0x14);
    v0 = addu(v0, a0);
    lw(a3, v0, 0);
    lw(a1, t7, 2080);
    v1 = t0 | v1;
    v1 = v1 | t2;
    v0 = 0x780000;
    mult(a1, a1, a2);
    v0 = addiu(v0, -3304);  // &0x77F318
    v1 = sll(v1, 2);
    lw(a2, sp, 0xC);
    v1 = addu(v1, v0);
    ld(fp, sp, 0xA0);
    lw(v0, sp, 0x10);
    ld(s7, sp, 0x90);
    a0 = addu(v0, a1);
    ld(s6, sp, 0x80);
    a1 = addu(a2, a1);
    ld(s5, sp, 0x70);
    a2 = addu(t7, a0);
    lw(v0, a1, 0);
    sw(a3, a2, 1480);
    a0 = a2;
    v0 = addiu(v0, 1);
    ld(s4, sp, 0x60);
    lw(a2, v1, 0);
    ld(s3, sp, 0x50);
    ld(s2, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sw(v0, a1, 0);
    sw(a2, a0, 1496);
    sp = addiu(sp, 0xB0);
}

// 0x004FD8A8 _skipMB0 -- 188 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// a skipped macroblock: reset vectors in P pictures, keep the motion type; not allowed in I pictures. [_skipMB0]
void _skipMB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fd8a8
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 320;
    sd(s0, sp, 0x0);
    t1 = 1;
    sd(ra, sp, 0x10);
    s0 = t0;
    t0 = 2;
    lw(v0, a0, 2080);
    mult(t2, v0, v1);
    v0 = addu(t2, a0);
    sw(t1, v0, 1756);
    sw(t1, a0, 448);
    lw(v0, a0, 352);
    if (v0 != t0) {
        lw(v1, a0, 388);
    } else {
        // 0x004fd8e4
        charge(ctx, 5);
        sw(zero, a1, 0);
        sw(zero, a1, 20);
        sw(zero, a1, 16);
        sw(zero, a1, 4);
        lw(v1, a0, 388);
    }
    // 0x004fd8f8
    charge(ctx, 3);
    v0 = 3;
    if (v1 != v0) {
        sw(t1, a2, 0);
        // 0x004fd90c
        charge(ctx, 5);
        lw(v0, a0, 388);
        v0 = v0 ^ 0x2;
        v0 = sltiu(v0, 1);
        sw(v0, a3, 0);
        sw(v0, a3, 4);
    } else {
        // 0x004fd904
        charge(ctx, 2);
        sw(t0, a2, 0);
    }
    // 0x004fd920
    charge(ctx, 4);
    lw(v1, a0, 352);
    v0 = 1;
    if (v1 != v0) {
        lw(v1, s0, 0);
    } else {
        // 0x004fd930
        charge(ctx, 5);
        a1 = 0x7C0000;
        a1 = addiu(a1, -10848);  // "skiped macroblock in I picure is not allowed"
        jal(ctx, 0x4FD934u, gen::fn__sceMpegError_00502668);
        t1 = 0;
        lw(v1, s0, 0);
    }
    // 0x004fd944 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    a0 = si(-2);
    ld(ra, sp, 0x10);
    v0 = t1;
    v1 = v1 & a0;
    sw(v1, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004FD968 _copyAddRefImage -- 236 bytes; leaf frame (no stack)
// add a 16-bit residual to the 8-bit prediction, clamp 0..255, pack (MMI). [_copyAddRefImage]
void _copyAddRefImage(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t9{ctx, 25};
    // 0x004fd968
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 24;
    t2 = 0x500000;
    t2 = addiu(t2, -9472);  // &0x4FDB00
    lq(v1, t2, 0);  // 0x4FDB00
    for (;;) {
        // 0x004fd978
        charge(ctx, 53);
        lq(t0, a2, 0);
        v0 = addiu(v0, -4);
        lq(t1, a2, 16);
        lq(t2, a2, 32);
        lq(t3, a2, 48);
        lq(t4, a2, 64);
        lq(t5, a2, 80);
        lq(t6, a2, 96);
        lq(t7, a2, 112);
        lq(t9, a1, 0);
        paddh(t0, t0, t9);
        lq(t9, a1, 16);
        pminh(t0, t0, v1);
        pmaxh(t0, t0, zero);
        paddh(t1, t1, t9);
        lq(t9, a1, 32);
        pminh(t1, t1, v1);
        pmaxh(t1, t1, zero);
        ppacb(t1, t1, t0);
        paddh(t2, t2, t9);
        pminh(t2, t2, v1);
        lq(t9, a1, 48);
        pmaxh(t2, t2, zero);
        paddh(t3, t3, t9);
        lq(t9, a1, 64);
        pminh(t3, t3, v1);
        pmaxh(t3, t3, zero);
        ppacb(t3, t3, t2);
        paddh(t4, t4, t9);
        lq(t9, a1, 80);
        pminh(t4, t4, v1);
        pmaxh(t4, t4, zero);
        paddh(t5, t5, t9);
        lq(t9, a1, 96);
        pminh(t5, t5, v1);
        pmaxh(t5, t5, zero);
        ppacb(t5, t5, t4);
        paddh(t6, t6, t9);
        lq(t9, a1, 112);
        pminh(t6, t6, v1);
        pmaxh(t6, t6, zero);
        sq(t1, a0, 0);
        paddh(t7, t7, t9);
        pminh(t7, t7, v1);
        pmaxh(t7, t7, zero);
        ppacb(t7, t7, t6);
        sq(t3, a0, 16);
        sq(t5, a0, 32);
        sq(t7, a0, 48);
        a1 = addiu(a1, 128);
        a0 = addiu(a0, 64);
        a2 = addiu(a2, 128);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fda4c
    charge(ctx, 2);
}

// 0x004FDC98 _rix_000 -- 116 bytes; leaf frame (no stack)
// luma fetch, full-pel, no averaging (16-bit out, MMI). [_rix_000]
void _rix_000(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t6{ctx, 14}, t7{ctx, 15};
    // 0x004fdc98
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(t6, a0, 0);
    lw(a1, a0, 20);
    lw(a2, a0, 24);
    lw(t4, a0, 16);
    lw(t0, a0, 4);
    lw(a3, a0, 8);
    mtsab(t0, 0);
    t3 = sll(t4, 1);
    t7 = si(-1);
    for (;;) {
        // 0x004fdcbc
        charge(ctx, 12);
        lq(t0, a1, 0);
        lq(t1, a2, 0);
        a3 = addiu(a3, -1);
        a1 = addu(a1, t4);
        a2 = addu(a2, t4);
        qfsrv(t2, t1, t0);
        pextlb(t0, zero, t2);
        pextub(t1, zero, t2);
        sq(t0, t6, 0);
        sq(t1, t6, 16);
        t6 = addu(t6, t3);
        if (i64(a3) > 0) {
            backedge(ctx);
            continue;
        }
        // 0x004fdcec
        charge(ctx, 6);
        a1 = addiu(a1, 128);
        a2 = addiu(a2, 128);
        lw(a3, a0, 12);
        t2 = t7 & a3;
        t7 = 0;
        if (t2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fdd04
    charge(ctx, 2);
}

// 0x004FDD10 _ri0_000 -- 148 bytes; leaf frame (no stack)
// chroma fetch, full-pel, no averaging. [_ri0_000]
void _ri0_000(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t7{ctx, 15}, t8{ctx, 24}, t9{ctx, 25};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fdd10
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(a1, a0, 0);
    lw(a2, a0, 20);
    lw(a3, a0, 24);
    lw(t5, a0, 16);
    lw(t4, a0, 4);
    t3 = sll(t5, 1);
    mtsab(t4, 0);
    t8 = si(-1);
    for (;;) {
        // 0x004fdd30
        charge(ctx, 2);
        lw(t7, a0, 8);
        t9 = si(-1);
        for (;;) {
            // 0x004fdd38
            charge(ctx, 11);
            ld(t0, a2, 0);
            ld(t1, a3, 0);
            pcpyld(t0, t1, t0);
            qfsrv(t1, t0, t0);
            pextlb(t0, zero, t1);
            sq(t0, a1, 0);
            t7 = addiu(t7, -1);
            a2 = addu(a2, t5);
            a1 = addu(a1, t3);
            a3 = addu(a3, t5);
            if (i64(t7) > 0) {
                backedge(ctx);
                continue;
            }
            // 0x004fdd64
            charge(ctx, 6);
            a2 = addiu(a2, 320);
            a3 = addiu(a3, 320);
            lw(t7, a0, 12);
            t2 = t9 & t7;
            t9 = 0;
            if (t2 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004fdd7c
        charge(ctx, 8);
        lw(a1, a0, 0);
        lw(a2, a0, 20);
        lw(a3, a0, 24);
        a1 = addiu(a1, 128);
        a2 = addiu(a2, 64);
        a3 = addiu(a3, 64);
        cc = t8 != 0;  // the condition, before the delay slot changes it
        t8 = 0;
        if (!cc) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fdd9c
    charge(ctx, 2);
}

// 0x004FDDA8 _rix_001 -- 180 bytes; leaf frame (no stack)
// luma fetch, vertical half-pel. [_rix_001]
void _rix_001(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, t9{ctx, 25};
    // 0x004fdda8
    enter(ctx, 17);  // entry check point + this block's cycles
    lw(t6, a0, 0);
    lw(a1, a0, 20);
    lw(a2, a0, 24);
    lw(t8, a0, 16);
    lw(t5, a0, 4);
    lw(a3, a0, 8);
    pnor(t9, zero, zero);
    psrlh(t9, t9, 15);
    lq(t0, a1, 0);
    t4 = sll(t8, 1);
    lq(t1, a2, 0);
    mtsab(t5, 0);
    qfsrv(t2, t1, t0);
    pextlb(t0, zero, t2);
    t3 = si(-1);
    pextub(t1, zero, t2);
    if (a3 != 0) {
        for (;;) {
        L_004fddec:
            charge(ctx, 20);
            a1 = addu(a1, t8);
            a2 = addu(a2, t8);
            lq(t2, a1, 0);
            lq(t7, a2, 0);
            qfsrv(v0, t7, t2);
            pextlb(t2, zero, v0);
            a3 = addiu(a3, -1);
            pextub(t7, zero, v0);
            paddh(v0, t0, t2);
            paddh(v1, t1, t7);
            por(t0, t2, zero);
            por(t1, t7, zero);
            paddh(v0, v0, t9);
            paddh(v1, v1, t9);
            psrlh(v0, v0, 1);
            psrlh(v1, v1, 1);
            sq(v0, t6, 0);
            sq(v1, t6, 16);
            t6 = addu(t6, t4);
            if (i64(a3) <= 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004fde3c
    charge(ctx, 6);
    a1 = addiu(a1, 128);
    a2 = addiu(a2, 128);
    lw(a3, a0, 12);
    t2 = t3 & a3;
    t3 = 0;
    if (t2 != 0) {
        backedge(ctx);
        goto L_004fddec;
    }
    // 0x004fde54
    charge(ctx, 2);
}

// 0x004FDE60 _ri0_001 -- 204 bytes; leaf frame (no stack)
// chroma fetch, vertical half-pel. [_ri0_001]
void _ri0_001(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, t9{ctx, 25};
    // 0x004fde60
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(t6, a0, 0);
    lw(a1, a0, 20);
    lw(a2, a0, 24);
    lw(t4, a0, 16);
    lw(t5, a0, 4);
    pnor(t9, zero, zero);
    psrlh(t9, t9, 15);
    t3 = 1;
    t8 = sll(t4, 1);
    mtsab(t5, 0);
    for (;;) {
        // 0x004fde88
        charge(ctx, 8);
        lw(a3, a0, 8);
        ld(t0, a1, 0);
        ld(t1, a2, 0);
        pcpyld(t0, t1, t0);
        qfsrv(t0, t0, t0);
        t3 = t3 | 0x8000;
        pextlb(t7, zero, t0);
        if (a3 != 0) {
            for (;;) {
            L_004fdea8:
                charge(ctx, 15);
                a1 = addu(a1, t4);
                a2 = addu(a2, t4);
                ld(t0, a1, 0);
                ld(t1, a2, 0);
                pcpyld(t0, t1, t0);
                qfsrv(t0, t0, t0);
                pextlb(t2, zero, t0);
                a3 = addiu(a3, -1);
                paddh(t1, t2, t7);
                por(t7, t2, zero);
                paddh(t2, t1, t9);
                psrlh(t2, t2, 1);
                sq(t2, t6, 0);
                t6 = addu(t6, t8);
                if (i64(a3) <= 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004fdee4
        charge(ctx, 7);
        psrah(t2, t3, 15);
        a1 = addiu(a1, 320);
        lw(a3, a0, 12);
        a2 = addiu(a2, 320);
        t2 = t2 & a3;
        t3 = t3 & 0x7FFF;
        if (t2 != 0) {
            backedge(ctx);
            goto L_004fdea8;
        }
        // 0x004fdf00
        charge(ctx, 9);
        lw(t6, a0, 0);
        lw(a1, a0, 20);
        lw(a2, a0, 24);
        t6 = addiu(t6, 128);
        a1 = addiu(a1, 64);
        a2 = addiu(a2, 64);
        t2 = t3 & 0x1;
        t3 = t3 & 0xFFFE;
        if (t2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fdf24
    charge(ctx, 2);
}

// 0x004FDF30 _rix_010 -- 172 bytes; leaf frame (no stack)
// luma fetch, horizontal half-pel. [_rix_010]
void _rix_010(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, t9{ctx, 25};
    // 0x004fdf30
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(t6, a0, 0);
    lw(a1, a0, 20);
    lw(a2, a0, 24);
    lw(t1, a0, 16);
    lw(t5, a0, 4);
    lw(a3, a0, 8);
    pnor(t9, zero, zero);
    psrlh(t9, t9, 15);
    t8 = 1;
    t0 = sll(t1, 1);
    t3 = si(-1);
    for (;;) {
        // 0x004fdf5c
        charge(ctx, 24);
        lq(t2, a1, 0);
        lq(t7, a2, 0);
        mtsab(t5, 0);
        qfsrv(v0, t7, t2);
        qfsrv(v1, t2, t7);
        pextlb(t2, zero, v0);
        a3 = addiu(a3, -1);
        pextub(t7, zero, v0);
        mtsab(t8, 0);
        qfsrv(v1, v1, v0);
        pextlb(v0, zero, v1);
        pextub(v1, zero, v1);
        paddh(t2, t2, v0);
        paddh(t7, t7, v1);
        paddh(v0, t2, t9);
        paddh(v1, t7, t9);
        psrlh(v0, v0, 1);
        psrlh(v1, v1, 1);
        sq(v0, t6, 0);
        sq(v1, t6, 16);
        a1 = addu(a1, t1);
        a2 = addu(a2, t1);
        t6 = addu(t6, t0);
        if (i64(a3) > 0) {
            backedge(ctx);
            continue;
        }
        // 0x004fdfbc
        charge(ctx, 6);
        a1 = addiu(a1, 128);
        a2 = addiu(a2, 128);
        lw(a3, a0, 12);
        t4 = t3 & a3;
        t3 = 0;
        if (t4 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fdfd4
    charge(ctx, 2);
}

// 0x004FDFE0 _ri0_010 -- 184 bytes; leaf frame (no stack)
// chroma fetch, horizontal half-pel. [_ri0_010]
void _ri0_010(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t8{ctx, 24}, t9{ctx, 25};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fdfe0
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(t6, a0, 0);
    lw(a1, a0, 20);
    lw(a2, a0, 24);
    lw(v1, a0, 16);
    lw(t5, a0, 4);
    pnor(t9, zero, zero);
    psrlh(t9, t9, 15);
    t8 = 1;
    t4 = si(-1);
    v0 = sll(v1, 1);
    for (;;) {
        // 0x004fe008
        charge(ctx, 2);
        lw(a3, a0, 8);
        t3 = si(-1);
        for (;;) {
            // 0x004fe010
            charge(ctx, 18);
            ld(t0, a1, 0);
            ld(t1, a2, 0);
            pcpyld(t0, t1, t0);
            mtsab(t5, 0);
            qfsrv(t0, t0, t0);
            pextlb(t1, zero, t0);
            a3 = addiu(a3, -1);
            a1 = addu(a1, v1);
            a2 = addu(a2, v1);
            mtsab(t8, 0);
            qfsrv(t2, zero, t0);
            pextlb(t0, zero, t2);
            paddh(t2, t1, t0);
            paddh(t2, t2, t9);
            psrlh(t2, t2, 1);
            sq(t2, t6, 0);
            t6 = addu(t6, v0);
            if (i64(a3) > 0) {
                backedge(ctx);
                continue;
            }
            // 0x004fe058
            charge(ctx, 6);
            a1 = addiu(a1, 320);
            a2 = addiu(a2, 320);
            lw(a3, a0, 12);
            t2 = t3 & a3;
            t3 = 0;
            if (t2 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004fe070
        charge(ctx, 8);
        lw(t6, a0, 0);
        lw(a1, a0, 20);
        lw(a2, a0, 24);
        t6 = addiu(t6, 128);
        a1 = addiu(a1, 64);
        a2 = addiu(a2, 64);
        cc = t4 != 0;  // the condition, before the delay slot changes it
        t4 = 0;
        if (!cc) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fe090
    charge(ctx, 2);
}

// 0x004FE098 _rix_011 -- 248 bytes; leaf frame (no stack)
// luma fetch, both half-pel. [_rix_011]
void _rix_011(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, t9{ctx, 25};
    // 0x004fe098
    enter(ctx, 25);  // entry check point + this block's cycles
    lw(t6, a0, 0);
    lw(a1, a0, 20);
    lw(a2, a0, 24);
    lw(t4, a0, 16);
    lw(t5, a0, 4);
    lw(a3, a0, 8);
    pnor(t9, zero, zero);
    psrlh(t9, t9, 15);
    psllh(t9, t9, 1);
    t8 = 1;
    lq(t0, a1, 0);
    lq(t1, a2, 0);
    mtsab(t5, 0);
    qfsrv(t2, t1, t0);
    qfsrv(t7, t0, t1);
    pextlb(t0, zero, t2);
    pextub(t1, zero, t2);
    t3 = si(-1);
    mtsab(t8, 0);
    qfsrv(t7, t7, t2);
    pextlb(t2, zero, t7);
    pextub(t7, zero, t7);
    paddh(t0, t0, t2);
    paddh(t1, t1, t7);
    if (a3 != 0) {
        for (;;) {
        L_004fe0fc:
            charge(ctx, 29);
            a1 = addu(a1, t4);
            a2 = addu(a2, t4);
            lq(t2, a1, 0);
            lq(t7, a2, 0);
            mtsab(t5, 0);
            qfsrv(v0, t7, t2);
            qfsrv(v1, t2, t7);
            pextlb(t2, zero, v0);
            a3 = addiu(a3, -1);
            pextub(t7, zero, v0);
            mtsab(t8, 0);
            qfsrv(v1, v1, v0);
            pextlb(v0, zero, v1);
            pextub(v1, zero, v1);
            paddh(t2, t2, v0);
            paddh(t7, t7, v1);
            paddh(v0, t0, t2);
            paddh(v1, t1, t7);
            por(t0, t2, zero);
            por(t1, t7, zero);
            paddh(v0, v0, t9);
            paddh(v1, v1, t9);
            psrlh(v0, v0, 2);
            psrlh(v1, v1, 2);
            sq(v0, t6, 0);
            t2 = sll(t4, 1);
            sq(v1, t6, 16);
            t6 = addu(t6, t2);
            if (i64(a3) <= 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004fe170
    charge(ctx, 6);
    a1 = addiu(a1, 128);
    a2 = addiu(a2, 128);
    lw(a3, a0, 12);
    t2 = t3 & a3;
    t3 = 0;
    if (t2 != 0) {
        backedge(ctx);
        goto L_004fe0fc;
    }
    // 0x004fe188
    charge(ctx, 2);
}

// 0x004FE190 _ri0_011 -- 252 bytes; leaf frame (no stack)
// chroma fetch, both half-pel. [_ri0_011]
void _ri0_011(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, t9{ctx, 25};
    // 0x004fe190
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(t6, a0, 0);
    lw(a1, a0, 20);
    lw(a2, a0, 24);
    lw(t4, a0, 16);
    lw(t5, a0, 4);
    pnor(t9, zero, zero);
    psrlh(t9, t9, 15);
    psllh(t9, t9, 1);
    t8 = 1;
    t3 = 1;
    for (;;) {
        // 0x004fe1b8
        charge(ctx, 14);
        lw(a3, a0, 8);
        ld(t0, a1, 0);
        ld(t1, a2, 0);
        pcpyld(t0, t1, t0);
        mtsab(t5, 0);
        qfsrv(t0, t0, t0);
        pextlb(t1, zero, t0);
        a1 = addu(a1, t4);
        t3 = t3 | 0x8000;
        mtsab(t8, 0);
        qfsrv(t2, zero, t0);
        pextlb(t0, zero, t2);
        paddh(t7, t1, t0);
        if (a3 != 0) {
            for (;;) {
            L_004fe1f0:
                charge(ctx, 21);
                a2 = addu(a2, t4);
                ld(t0, a1, 0);
                ld(t1, a2, 0);
                pcpyld(t0, t1, t0);
                mtsab(t5, 0);
                qfsrv(t0, t0, t0);
                pextlb(t1, zero, t0);
                a3 = addiu(a3, -1);
                a1 = addu(a1, t4);
                mtsab(t8, 0);
                qfsrv(t2, zero, t0);
                pextlb(t0, zero, t2);
                paddh(t2, t1, t0);
                paddh(t1, t2, t7);
                por(t7, t2, zero);
                paddh(t2, t1, t9);
                t0 = sll(t4, 1);
                psrlh(t2, t2, 2);
                sq(t2, t6, 0);
                t6 = addu(t6, t0);
                if (i64(a3) <= 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004fe244
        charge(ctx, 7);
        psrah(t2, t3, 15);
        a1 = addiu(a1, 320);
        lw(a3, a0, 12);
        a2 = addiu(a2, 320);
        t2 = t2 & a3;
        t3 = t3 & 0x7FFF;
        if (t2 != 0) {
            backedge(ctx);
            goto L_004fe1f0;
        }
        // 0x004fe260
        charge(ctx, 9);
        lw(t6, a0, 0);
        lw(a1, a0, 20);
        lw(a2, a0, 24);
        t6 = addiu(t6, 128);
        a1 = addiu(a1, 64);
        a2 = addiu(a2, 64);
        t2 = t3 & 0x1;
        t3 = t3 & 0xFFFE;
        if (t2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fe284
    charge(ctx, 2);
}

// 0x004FE290 _rix_100 -- 156 bytes; leaf frame (no stack)
// luma fetch averaged with the prediction already there (bidirectional), full-pel. [_rix_100]
void _rix_100(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t9{ctx, 25};
    // 0x004fe290
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(t6, a0, 0);
    lw(a1, a0, 20);
    lw(a2, a0, 24);
    lw(t1, a0, 16);
    lw(t5, a0, 4);
    lw(a3, a0, 8);
    t0 = sll(t1, 1);
    t3 = si(-1);
    mtsab(t5, 0);
    for (;;) {
        // 0x004fe2b4
        charge(ctx, 22);
        lq(t2, a1, 0);
        lq(t7, a2, 0);
        qfsrv(v0, t7, t2);
        pextlb(t2, zero, v0);
        pextub(t7, zero, v0);
        lq(v0, t6, 0);
        lq(v1, t6, 16);
        paddh(v0, v0, t2);
        paddh(v1, v1, t7);
        pnor(t9, zero, zero);
        psrlh(t9, t9, 15);
        paddh(t2, v0, t9);
        psrlh(v0, t2, 1);
        paddh(t2, v1, t9);
        psrlh(v1, t2, 1);
        sq(v0, t6, 0);
        sq(v1, t6, 16);
        a3 = addiu(a3, -1);
        a1 = addu(a1, t1);
        t6 = addu(t6, t0);
        a2 = addu(a2, t1);
        if (i64(a3) > 0) {
            backedge(ctx);
            continue;
        }
        // 0x004fe30c
        charge(ctx, 6);
        a1 = addiu(a1, 128);
        a2 = addiu(a2, 128);
        lw(a3, a0, 12);
        t4 = t3 & a3;
        t3 = 0;
        if (t4 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fe324
    charge(ctx, 2);
}

// 0x004FE330 _ri0_100 -- 172 bytes; leaf frame (no stack)
// chroma, averaged, full-pel. [_ri0_100]
void _ri0_100(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fe330
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(t6, a0, 0);
    lw(a1, a0, 20);
    lw(a2, a0, 24);
    lw(v1, a0, 16);
    lw(t5, a0, 4);
    t4 = si(-1);
    v0 = sll(v1, 1);
    mtsab(t5, 0);
    for (;;) {
        // 0x004fe350
        charge(ctx, 2);
        lw(a3, a0, 8);
        t3 = si(-1);
        for (;;) {
            // 0x004fe358
            charge(ctx, 17);
            ld(t0, a1, 0);
            ld(t1, a2, 0);
            pcpyld(t0, t1, t0);
            qfsrv(t0, t0, t0);
            pextlb(t1, zero, t0);
            a3 = addiu(a3, -1);
            a1 = addu(a1, v1);
            a2 = addu(a2, v1);
            lq(t0, t6, 0);
            paddh(t2, t1, t0);
            pcgth(t1, t2, zero);
            psrlh(t1, t1, 15);
            paddh(t2, t2, t1);
            psrlh(t2, t2, 1);
            sq(t2, t6, 0);
            t6 = addu(t6, v0);
            if (i64(a3) > 0) {
                backedge(ctx);
                continue;
            }
            // 0x004fe39c
            charge(ctx, 6);
            a1 = addiu(a1, 320);
            a2 = addiu(a2, 320);
            lw(a3, a0, 12);
            t2 = t3 & a3;
            t3 = 0;
            if (t2 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004fe3b4
        charge(ctx, 8);
        lw(t6, a0, 0);
        lw(a1, a0, 20);
        lw(a2, a0, 24);
        t6 = addiu(t6, 128);
        a1 = addiu(a1, 64);
        a2 = addiu(a2, 64);
        cc = t4 != 0;  // the condition, before the delay slot changes it
        t4 = 0;
        if (!cc) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fe3d4
    charge(ctx, 2);
}

// 0x004FE3E0 _rix_101 -- 220 bytes; leaf frame (no stack)
// luma, averaged, vertical half-pel. [_rix_101]
void _rix_101(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, t9{ctx, 25};
    // 0x004fe3e0
    enter(ctx, 17);  // entry check point + this block's cycles
    lw(t6, a0, 0);
    lw(a1, a0, 20);
    lw(a2, a0, 24);
    lw(t4, a0, 16);
    lw(t5, a0, 4);
    lw(a3, a0, 8);
    pnor(t9, zero, zero);
    psrlh(t9, t9, 15);
    lq(t0, a1, 0);
    lq(t1, a2, 0);
    mtsab(t5, 0);
    qfsrv(t2, t1, t0);
    t8 = sll(t4, 1);
    pextlb(t0, zero, t2);
    t3 = si(-1);
    pextub(t1, zero, t2);
    if (a3 != 0) {
        for (;;) {
        L_004fe424:
            charge(ctx, 30);
            a1 = addu(a1, t4);
            a2 = addu(a2, t4);
            lq(t2, a1, 0);
            lq(t7, a2, 0);
            qfsrv(v0, t7, t2);
            pextlb(t2, zero, v0);
            a3 = addiu(a3, -1);
            pextub(t7, zero, v0);
            paddh(v0, t0, t2);
            paddh(v1, t1, t7);
            por(t0, t2, zero);
            por(t1, t7, zero);
            paddh(v0, v0, t9);
            paddh(v1, v1, t9);
            psrlh(v0, v0, 1);
            psrlh(v1, v1, 1);
            lq(t2, t6, 0);
            lq(t7, t6, 16);
            paddh(v0, v0, t2);
            paddh(v1, v1, t7);
            paddh(t2, v0, t9);
            psrlh(v0, t2, 1);
            pcgth(t2, v1, zero);
            psrlh(t2, t2, 15);
            paddh(t2, v1, t2);
            psrlh(v1, t2, 1);
            sq(v0, t6, 0);
            sq(v1, t6, 16);
            t6 = addu(t6, t8);
            if (i64(a3) <= 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004fe49c
    charge(ctx, 6);
    a1 = addiu(a1, 128);
    a2 = addiu(a2, 128);
    lw(a3, a0, 12);
    t2 = t3 & a3;
    t3 = 0;
    if (t2 != 0) {
        backedge(ctx);
        goto L_004fe424;
    }
    // 0x004fe4b4
    charge(ctx, 2);
}

// 0x004FE4C0 _ri0_101 -- 228 bytes; leaf frame (no stack)
// chroma, averaged, vertical half-pel. [_ri0_101]
void _ri0_101(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, t9{ctx, 25};
    // 0x004fe4c0
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(t6, a0, 0);
    lw(a1, a0, 20);
    lw(a2, a0, 24);
    lw(t4, a0, 16);
    lw(t5, a0, 4);
    pnor(t9, zero, zero);
    psrlh(t9, t9, 15);
    t3 = 1;
    t8 = sll(t4, 1);
    mtsab(t5, 0);
    for (;;) {
        // 0x004fe4e8
        charge(ctx, 8);
        lw(a3, a0, 8);
        ld(t0, a1, 0);
        ld(t1, a2, 0);
        pcpyld(t0, t1, t0);
        qfsrv(t0, t0, t0);
        t3 = t3 | 0x8000;
        pextlb(t7, zero, t0);
        if (a3 != 0) {
            for (;;) {
            L_004fe508:
                charge(ctx, 21);
                a1 = addu(a1, t4);
                a2 = addu(a2, t4);
                ld(t0, a1, 0);
                ld(t1, a2, 0);
                pcpyld(t0, t1, t0);
                qfsrv(t0, t0, t0);
                pextlb(t2, zero, t0);
                a3 = addiu(a3, -1);
                paddh(t1, t2, t7);
                por(t7, t2, zero);
                paddh(t2, t1, t9);
                psrlh(t2, t2, 1);
                lq(t0, t6, 0);
                paddh(t2, t2, t0);
                pcgth(t1, t2, zero);
                psrlh(t1, t1, 15);
                paddh(t2, t2, t1);
                psrlh(t2, t2, 1);
                sq(t2, t6, 0);
                t6 = addu(t6, t8);
                if (i64(a3) <= 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004fe55c
        charge(ctx, 7);
        psrah(t2, t3, 15);
        a1 = addiu(a1, 320);
        lw(a3, a0, 12);
        a2 = addiu(a2, 320);
        t2 = t2 & a3;
        t3 = t3 & 0x7FFF;
        if (t2 != 0) {
            backedge(ctx);
            goto L_004fe508;
        }
        // 0x004fe578
        charge(ctx, 9);
        lw(t6, a0, 0);
        lw(a1, a0, 20);
        lw(a2, a0, 24);
        t6 = addiu(t6, 128);
        a1 = addiu(a1, 64);
        a2 = addiu(a2, 64);
        t2 = t3 & 0x1;
        t3 = t3 & 0xFFFE;
        if (t2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fe59c
    charge(ctx, 2);
}

// 0x004FE5A8 _rix_110 -- 212 bytes; leaf frame (no stack)
// luma, averaged, horizontal half-pel. [_rix_110]
void _rix_110(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, t9{ctx, 25};
    // 0x004fe5a8
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(t6, a0, 0);
    lw(a1, a0, 20);
    lw(a2, a0, 24);
    lw(t1, a0, 16);
    lw(t5, a0, 4);
    lw(a3, a0, 8);
    pnor(t9, zero, zero);
    psrlh(t9, t9, 15);
    t8 = 1;
    t0 = sll(t1, 1);
    t3 = si(-1);
    for (;;) {
        // 0x004fe5d4
        charge(ctx, 34);
        lq(t2, a1, 0);
        lq(t7, a2, 0);
        mtsab(t5, 0);
        qfsrv(v0, t7, t2);
        qfsrv(v1, t2, t7);
        pextlb(t2, zero, v0);
        a3 = addiu(a3, -1);
        pextub(t7, zero, v0);
        mtsab(t8, 0);
        qfsrv(v1, v1, v0);
        pextlb(v0, zero, v1);
        pextub(v1, zero, v1);
        paddh(t2, t2, v0);
        paddh(t7, t7, v1);
        paddh(v0, t2, t9);
        paddh(v1, t7, t9);
        psrlh(v0, v0, 1);
        psrlh(v1, v1, 1);
        lq(t2, t6, 0);
        lq(t7, t6, 16);
        paddh(v0, v0, t2);
        paddh(v1, v1, t7);
        paddh(t2, v0, t9);
        psrlh(v0, t2, 1);
        pcgth(t2, v1, zero);
        psrlh(t2, t2, 15);
        paddh(t2, v1, t2);
        psrlh(v1, t2, 1);
        sq(v0, t6, 0);
        sq(v1, t6, 16);
        a1 = addu(a1, t1);
        a2 = addu(a2, t1);
        t6 = addu(t6, t0);
        if (i64(a3) > 0) {
            backedge(ctx);
            continue;
        }
        // 0x004fe65c
        charge(ctx, 6);
        a1 = addiu(a1, 128);
        a2 = addiu(a2, 128);
        lw(a3, a0, 12);
        t4 = t3 & a3;
        t3 = 0;
        if (t4 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fe674
    charge(ctx, 2);
}

// 0x004FE680 _ri0_110 -- 208 bytes; leaf frame (no stack)
// chroma, averaged, horizontal half-pel. [_ri0_110]
void _ri0_110(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t8{ctx, 24}, t9{ctx, 25};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fe680
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(t6, a0, 0);
    lw(a1, a0, 20);
    lw(a2, a0, 24);
    lw(v1, a0, 16);
    lw(t5, a0, 4);
    pnor(t9, zero, zero);
    psrlh(t9, t9, 15);
    t8 = 1;
    t4 = si(-1);
    v0 = sll(v1, 1);
    for (;;) {
        // 0x004fe6a8
        charge(ctx, 2);
        lw(a3, a0, 8);
        t3 = si(-1);
        for (;;) {
            // 0x004fe6b0
            charge(ctx, 24);
            ld(t0, a1, 0);
            ld(t1, a2, 0);
            pcpyld(t0, t1, t0);
            mtsab(t5, 0);
            qfsrv(t0, t0, t0);
            pextlb(t1, zero, t0);
            a3 = addiu(a3, -1);
            a1 = addu(a1, v1);
            a2 = addu(a2, v1);
            mtsab(t8, 0);
            qfsrv(t2, zero, t0);
            pextlb(t0, zero, t2);
            paddh(t2, t1, t0);
            paddh(t2, t2, t9);
            psrlh(t2, t2, 1);
            lq(t0, t6, 0);
            paddh(t2, t2, t0);
            pcgth(t1, t2, zero);
            psrlh(t1, t1, 15);
            paddh(t2, t2, t1);
            psrlh(t2, t2, 1);
            sq(t2, t6, 0);
            t6 = addu(t6, v0);
            if (i64(a3) > 0) {
                backedge(ctx);
                continue;
            }
            // 0x004fe710
            charge(ctx, 6);
            a1 = addiu(a1, 320);
            a2 = addiu(a2, 320);
            lw(a3, a0, 12);
            t2 = t3 & a3;
            t3 = 0;
            if (t2 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004fe728
        charge(ctx, 8);
        lw(t6, a0, 0);
        lw(a1, a0, 20);
        lw(a2, a0, 24);
        t6 = addiu(t6, 128);
        a1 = addiu(a1, 64);
        a2 = addiu(a2, 64);
        cc = t4 != 0;  // the condition, before the delay slot changes it
        t4 = 0;
        if (!cc) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fe748
    charge(ctx, 2);
}

// 0x004FE750 _rix_111 -- 288 bytes; leaf frame (no stack)
// luma, averaged, both half-pel. [_rix_111]
void _rix_111(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, t9{ctx, 25};
    // 0x004fe750
    enter(ctx, 25);  // entry check point + this block's cycles
    lw(t6, a0, 0);
    lw(a1, a0, 20);
    lw(a2, a0, 24);
    lw(t8, a0, 16);
    lw(t5, a0, 4);
    lw(a3, a0, 8);
    pnor(t9, zero, zero);
    psrlh(t9, t9, 15);
    psllh(t9, t9, 1);
    t4 = 1;
    lq(t0, a1, 0);
    lq(t1, a2, 0);
    mtsab(t5, 0);
    qfsrv(t2, t1, t0);
    qfsrv(t7, t0, t1);
    pextlb(t0, zero, t2);
    pextub(t1, zero, t2);
    t3 = si(-1);
    mtsab(t4, 0);
    qfsrv(t7, t7, t2);
    pextlb(t2, zero, t7);
    pextub(t7, zero, t7);
    paddh(t0, t0, t2);
    paddh(t1, t1, t7);
    if (a3 != 0) {
        for (;;) {
        L_004fe7b4:
            charge(ctx, 39);
            a1 = addu(a1, t8);
            a2 = addu(a2, t8);
            lq(t2, a1, 0);
            lq(t7, a2, 0);
            mtsab(t5, 0);
            qfsrv(v0, t7, t2);
            qfsrv(v1, t2, t7);
            pextlb(t2, zero, v0);
            a3 = addiu(a3, -1);
            pextub(t7, zero, v0);
            mtsab(t4, 0);
            qfsrv(v1, v1, v0);
            pextlb(v0, zero, v1);
            pextub(v1, zero, v1);
            paddh(t2, t2, v0);
            paddh(t7, t7, v1);
            paddh(v0, t0, t2);
            paddh(v1, t1, t7);
            por(t0, t2, zero);
            por(t1, t7, zero);
            paddh(v0, v0, t9);
            paddh(v1, v1, t9);
            psrlh(v0, v0, 2);
            psrlh(v1, v1, 2);
            lq(t2, t6, 0);
            lq(t7, t6, 16);
            paddh(v0, v0, t2);
            paddh(v1, v1, t7);
            pnor(t9, zero, zero);
            psrlh(t9, t9, 15);
            paddh(t2, v0, t9);
            psrlh(v0, t2, 1);
            paddh(t2, v1, t9);
            psrlh(v1, t2, 1);
            sq(v0, t6, 0);
            t2 = sll(t8, 1);
            sq(v1, t6, 16);
            t6 = addu(t6, t2);
            if (i64(a3) <= 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004fe850
    charge(ctx, 6);
    a1 = addiu(a1, 128);
    a2 = addiu(a2, 128);
    lw(a3, a0, 12);
    t2 = t3 & a3;
    t3 = 0;
    if (t2 != 0) {
        backedge(ctx);
        goto L_004fe7b4;
    }
    // 0x004fe868
    charge(ctx, 2);
}

// 0x004FE870 _ri0_111 -- 276 bytes; leaf frame (no stack)
// chroma, averaged, both half-pel. [_ri0_111]
void _ri0_111(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, t9{ctx, 25};
    // 0x004fe870
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(t6, a0, 0);
    lw(a1, a0, 20);
    lw(a2, a0, 24);
    lw(t4, a0, 16);
    lw(t5, a0, 4);
    pnor(t9, zero, zero);
    psrlh(t9, t9, 15);
    psllh(t9, t9, 1);
    t8 = 1;
    t3 = 1;
    for (;;) {
        // 0x004fe898
        charge(ctx, 14);
        lw(a3, a0, 8);
        ld(t0, a1, 0);
        ld(t1, a2, 0);
        pcpyld(t0, t1, t0);
        mtsab(t5, 0);
        qfsrv(t0, t0, t0);
        pextlb(t1, zero, t0);
        a1 = addu(a1, t4);
        t3 = t3 | 0x8000;
        mtsab(t8, 0);
        qfsrv(t2, zero, t0);
        pextlb(t0, zero, t2);
        paddh(t7, t1, t0);
        if (a3 != 0) {
            for (;;) {
            L_004fe8d0:
                charge(ctx, 27);
                a2 = addu(a2, t4);
                ld(t0, a1, 0);
                ld(t1, a2, 0);
                pcpyld(t0, t1, t0);
                mtsab(t5, 0);
                qfsrv(t0, t0, t0);
                pextlb(t1, zero, t0);
                a3 = addiu(a3, -1);
                a1 = addu(a1, t4);
                mtsab(t8, 0);
                qfsrv(t2, zero, t0);
                pextlb(t0, zero, t2);
                paddh(t2, t1, t0);
                paddh(t1, t2, t7);
                por(t7, t2, zero);
                paddh(t2, t1, t9);
                psrlh(t2, t2, 2);
                lq(t0, t6, 0);
                paddh(t2, t2, t0);
                pcgth(t1, t2, zero);
                psrlh(t1, t1, 15);
                paddh(t2, t2, t1);
                t0 = sll(t4, 1);
                psrlh(t2, t2, 1);
                sq(t2, t6, 0);
                t6 = addu(t6, t0);
                if (i64(a3) <= 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004fe93c
        charge(ctx, 7);
        psrah(t2, t3, 15);
        a1 = addiu(a1, 320);
        lw(a3, a0, 12);
        a2 = addiu(a2, 320);
        t2 = t2 & a3;
        t3 = t3 & 0x7FFF;
        if (t2 != 0) {
            backedge(ctx);
            goto L_004fe8d0;
        }
        // 0x004fe958
        charge(ctx, 9);
        lw(t6, a0, 0);
        lw(a1, a0, 20);
        lw(a2, a0, 24);
        t6 = addiu(t6, 128);
        a1 = addiu(a1, 64);
        a2 = addiu(a2, 64);
        t2 = t3 & 0x1;
        t3 = t3 & 0xFFFE;
        if (t2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fe97c
    charge(ctx, 2);
}

// 0x004FEBC8 _initSeq -- 788 bytes; frame 0x80: s3 sp+0x30, ra sp+0x70, s6 sp+0x60, s5 sp+0x50, s4 sp+0x40, s1 sp+0x10, s0 sp+0x0, s2 sp+0x20
// a new sequence: MPEG-1 defaults, macroblock counts, (re)allocate the three reference frames on a size change, the 12
//   reference descriptors. [_initSeq]
void _initSeq(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004febc8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s3, sp, 0x30);
    sd(ra, sp, 0x70);
    s3 = a0;
    sd(s6, sp, 0x60);
    sd(s5, sp, 0x50);
    sd(s4, sp, 0x40);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x20);
    lw(s2, s3, 64);
    lw(a1, s2, 2136);
    if (a1 != 0) {
        lw(v0, s2, 308);
    } else {
        // 0x004fec00
        charge(ctx, 10);
        v0 = 1;
        v1 = 3;
        a0 = 5;
        sw(v1, s2, 388);
        sw(v0, s2, 396);
        sw(a0, s2, 340);
        sw(v0, s2, 332);
        sw(v0, s2, 336);
        sw(v0, s2, 408);
        lw(v0, s2, 308);
    }
    // 0x004fec28
    charge(ctx, 4);
    v0 = addiu(v0, 15);
    v0 = sra(v0, 4);
    sw(v0, s2, 316);
    if (a1 == 0) {
        // 0x004fec54
        charge(ctx, 1);
        lw(v0, s2, 312);
    L_004fec58:
        charge(ctx, 2);
        v0 = addiu(v0, 15);
        v0 = sra(v0, 4);
    } else {
        // 0x004fec38
        charge(ctx, 3);
        lw(v0, s2, 332);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        lw(v0, s2, 312);
        if (cc) {
            goto L_004fec58;
        }
        // 0x004fec44
        charge(ctx, 4);
        v0 = addiu(v0, 31);
        v0 = sra(v0, 5);
        v0 = sll(v0, 1);
    }
    // 0x004fec60
    charge(ctx, 7);
    sw(v0, s2, 320);
    s5 = sll(v0, 4);
    lw(v0, s2, 316);
    lw(v1, s3, 0);
    s4 = sll(v0, 4);
    s6 = 384;
    if (s4 == v1) {
        // 0x004fec7c
        charge(ctx, 3);
        lw(v0, s3, 4);
        ld(ra, sp, 0x70);
        if (s5 != v0) {
            goto L_004fec88;
        }
        // 0x004feeb8 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(s6, sp, 0x60);
        ld(s5, sp, 0x50);
        ld(s4, sp, 0x40);
        ld(s3, sp, 0x30);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x80);
        return;
    }
L_004fec88:
    charge(ctx, 29);
    s1 = addiu(s2, 280);
    mult(s0, s5, s6);
    sw(s4, s3, 0);
    sw(s5, s3, 4);
    a0 = s1;
    mult(s0, s4, s0);
    s0 = srl(s0, 8);
    jal(ctx, 0x4FECA0u, gen::fn__sceMpegAlalcFree_00501090);
    a0 = s2;
    a1 = s1;
    a2 = s0;
    a3 = 64;
    jal(ctx, 0x4FECB4u, gen::fn__sceMpegAlalcAlloc_005010a0);
    sw(v0, s2, 268);
    a0 = s2;
    a1 = s1;
    a2 = s0;
    a3 = 64;
    jal(ctx, 0x4FECCCu, gen::fn__sceMpegAlalcAlloc_005010a0);
    sw(v0, s2, 272);
    a1 = s1;
    a2 = s0;
    a0 = s2;
    a3 = 64;
    jal(ctx, 0x4FECE4u, gen::fn__sceMpegAlalcAlloc_005010a0);
    t0 = v0;
    lw(v1, s2, 2172);
    sw(t0, s2, 276);
    if (v1 == 0) {
        // 0x004fecfc
        charge(ctx, 33);
        lw(a0, s3, 4);
        v0 = 0xFFF0000;
        lw(a2, s3, 0);
        v0 = v0 | 0xFFFF;
        lw(a1, s2, 268);
        t0 = t0 & v0;
        mult(a2, a2, a0);
        lw(v1, s2, 272);
        a1 = a1 & v0;
        a3 = si(-1);
        v1 = v1 & v0;
        a0 = 0x20000000;
        a1 = a1 | a0;
        v1 = v1 | a0;
        a3 = slt(a3, a2);
        v0 = addiu(a2, 511);
        if (a3 != 0) v0 = a2;
        t0 = t0 | a0;
        v0 = sra(v0, 9);
        sw(a1, s2, 504);
        mult(v0, v0, s6);
        sw(v1, s2, 608);
        sw(a1, s2, 816);
        sw(v1, s2, 920);
        sw(t0, s2, 712);
        a0 = addu(t0, v0);
        a1 = addu(a1, v0);
        v1 = addu(v1, v0);
        sw(a1, s2, 1128);
        sw(v1, s2, 1232);
        sw(a0, s2, 1336);
        sw(t0, s2, 1024);
        goto L_004fede8;
    }
    // 0x004fed80
    charge(ctx, 3);
    v0 = 1;
    a2 = sra(s4, 4);
    if (v1 == v0) {
        // 0x004fed8c
        charge(ctx, 23);
        lw(v0, s3, 4);
        a0 = si(-1);
        lw(v1, s3, 0);
        lw(a2, s2, 268);
        mult(v1, v1, v0);
        lw(a1, s2, 272);
        sw(a2, s2, 504);
        sw(a1, s2, 608);
        sw(a2, s2, 816);
        a0 = slt(a0, v1);
        v0 = addiu(v1, 511);
        if (a0 != 0) v0 = v1;
        sw(a1, s2, 920);
        v0 = sra(v0, 9);
        sw(t0, s2, 712);
        mult(v0, v0, s6);
        sw(t0, s2, 1024);
        v1 = addu(t0, v0);
        a2 = addu(a2, v0);
        a1 = addu(a1, v0);
        sw(a2, s2, 1128);
        sw(a1, s2, 1232);
        sw(v1, s2, 1336);
    L_004fede8:
        charge(ctx, 1);
        a2 = sra(s4, 4);
    }
    // 0x004fedec
    charge(ctx, 51);
    v0 = addiu(s2, 504);
    a3 = sra(s5, 4);
    a0 = srl(s5, 31);
    sw(a3, v0, 16);
    v1 = addiu(s2, 608);
    sw(s4, v0, 4);
    a0 = addu(s5, a0);
    sw(s5, v0, 8);
    t2 = sra(a0, 5);
    sw(a2, v0, 12);
    a0 = sra(a0, 1);
    sw(a3, v1, 16);
    v0 = addiu(s2, 712);
    sw(s4, v1, 4);
    a1 = addiu(s2, 816);
    sw(s5, v1, 8);
    t0 = addiu(s2, 1128);
    sw(a2, v1, 12);
    t1 = addiu(s2, 1232);
    sw(a3, v0, 16);
    v1 = addiu(s2, 920);
    sw(s4, v0, 4);
    a3 = addiu(s2, 1024);
    sw(s5, v0, 8);
    sw(a2, v0, 12);
    sw(t2, a1, 16);
    v0 = addiu(s2, 1336);
    sw(s4, a1, 4);
    sw(a0, a1, 8);
    sw(a2, a1, 12);
    sw(t2, v1, 16);
    sw(s4, v1, 4);
    sw(a0, v1, 8);
    sw(a2, v1, 12);
    sw(t2, a3, 16);
    sw(s4, a3, 4);
    sw(a0, a3, 8);
    sw(a2, a3, 12);
    sw(t2, t0, 16);
    sw(s4, t0, 4);
    sw(a0, t0, 8);
    sw(a2, t0, 12);
    sw(t2, t1, 16);
    sw(s4, t1, 4);
    sw(a0, t1, 8);
    sw(a2, t1, 12);
    sw(s4, v0, 4);
    sw(a0, v0, 8);
    sw(t2, v0, 16);
    sw(a2, v0, 12);
    ld(ra, sp, 0x70);
    // 0x004feeb8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x004FF190 _groupOfPicturesHeader -- 160 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// parse a GOP header (time code, closed_gop, broken_link); new temporal-reference base. [_groupOfPicturesHeader]
void _groupOfPicturesHeader(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ff190
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 1;
    sd(s0, sp, 0x0);
    a1 = 1;
    sd(ra, sp, 0x10);
    s0 = a0;
    sw(zero, s0, mpeg::kBrokenLinkPend);
    lw(v0, s0, mpeg::kGopMax);
    sw(v1, s0, mpeg::kGopFirst);
    v0 = addiu(v0, 1);
    link(ctx, 0x4FF1B8u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, mpeg::kGopBase);
    call(ctx, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 5;
    jal(ctx, 0x4FF1C4u, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 6;
    jal(ctx, 0x4FF1D0u, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FF1DCu, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 6;
    jal(ctx, 0x4FF1E8u, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 6;
    jal(ctx, 0x4FF1F4u, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FF200u, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s0, mpeg::kClosedGop);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FF210u, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s0, mpeg::kBrokenLink);
    a0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    gen::fn__extensionAndUserData_004ff7c8(ctx);  // tail call
}

// 0x004FF230 _pictureHeader -- 324 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x10, ra sp+0x20
// parse a picture header (temporal_reference, picture_coding_type, vbv_delay, the f-codes, extra info) and make the
//   temporal reference absolute. [_pictureHeader]
void _pictureHeader(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ff230
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a1 = 10;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x20);
    s0 = a0;
    jal(ctx, 0x4FF244u, gen::fn__sceMpegNextBit_004fd658);
    s1 = v0;
    a0 = s0;
    a1 = 3;
    jal(ctx, 0x4FF254u, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s0, mpeg::kPicType);
    a0 = s0;
    a1 = 16;
    jal(ctx, 0x4FF264u, gen::fn__sceMpegNextBit_004fd658);
    lw(v1, s0, mpeg::kPicType);
    v0 = addiu(v1, -2);
    v0 = sltiu(v0, 2);
    a0 = s0;
    if (v0 != 0) {
        // 0x004ff280
        charge(ctx, 8);
        a1 = 1;
        jal(ctx, 0x4FF280u, gen::fn__sceMpegNextBit_004fd658);
        sw(v0, s0, mpeg::kFullPelFwd);
        a0 = s0;
        a1 = 3;
        jal(ctx, 0x4FF290u, gen::fn__sceMpegNextBit_004fd658);
        sw(v0, s0, mpeg::kFwdFcode);
        lw(v1, s0, mpeg::kPicType);
    }
    // 0x004ff2a0
    charge(ctx, 3);
    v0 = 3;
    a0 = s0;
    if (v1 == v0) {
        // 0x004ff2ac
        charge(ctx, 8);
        a1 = 1;
        jal(ctx, 0x4FF2ACu, gen::fn__sceMpegNextBit_004fd658);
        sw(v0, s0, mpeg::kFullPelBwd);
        a0 = s0;
        a1 = 3;
        jal(ctx, 0x4FF2BCu, gen::fn__sceMpegNextBit_004fd658);
        sw(v0, s0, mpeg::kBwdFcode);
    L_004ff2d8:
        charge(ctx, 1);
        a0 = s0;
    }
    // 0x004ff2dc
    charge(ctx, 4);
    a1 = 1;
    jal(ctx, 0x4FF2DCu, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    if (v0 != 0) {
        backedge(ctx);
        // 0x004ff2d0
        charge(ctx, 2);
        a1 = 8;
        jal(ctx, 0x4FF2D0u, gen::fn_j__sceMpegFlushBuf_0_004ff9d0);
        goto L_004ff2d8;
    }
    // 0x004ff2ec
    charge(ctx, 7);
    a0 = s0;
    jal(ctx, 0x4FF2ECu, gen::fn__extensionAndUserData_004ff7c8);
    lw(v1, s0, mpeg::kPicType);
    a1 = 0;
    v0 = 3;
    a0 = 0;
    if (v1 != v0) {
        // 0x004ff308
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x004ff310
            charge(ctx, 2);
            if (i64(s1) >= 0) {
                sw(zero, s0, mpeg::kGopFirst);
            } else {
                // 0x004ff318
                charge(ctx, 3);
                lw(v0, s0, mpeg::kGopFirst);
                a1 = sltiu(v0, 1);
                sw(zero, s0, mpeg::kGopFirst);
            }
            // 0x004ff324
            charge(ctx, 1);
            a0 = s1;
            goto L_004ff328;
        }
        lw(v0, s0, mpeg::kGopBase);
        goto L_004ff32c;
    }
L_004ff328:
    charge(ctx, 1);
    lw(v0, s0, mpeg::kGopBase);
L_004ff32c:
    charge(ctx, 3);
    v1 = addu(v0, s1);
    sw(v1, s0, mpeg::kTempRef);
    if (a1 != 0) {
        // 0x004ff338
        charge(ctx, 3);
        v0 = slt(a0, s1);
        if (v0 == 0) {
            // 0x004ff344
            charge(ctx, 2);
            v0 = addiu(v1, 1024);
            sw(v0, s0, mpeg::kTempRef);
            goto L_004ff34c;
        }
        lw(v0, s0, mpeg::kGopMax);
        // 0x004ff350 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        lw(a0, s0, mpeg::kTempRef);
        ld(ra, sp, 0x20);
        v1 = slt(v0, a0);
        ld(s1, sp, 0x10);
        if (v1 != 0) v0 = a0;
        sw(v0, s0, mpeg::kGopMax);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_004ff34c:
    charge(ctx, 1);
    lw(v0, s0, mpeg::kGopMax);
    // 0x004ff350 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a0, s0, mpeg::kTempRef);
    ld(ra, sp, 0x20);
    v1 = slt(v0, a0);
    ld(s1, sp, 0x10);
    if (v1 != 0) v0 = a0;
    sw(v0, s0, mpeg::kGopMax);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004FF7C8 _extensionAndUserData -- 460 bytes; frame 0x90: s0 sp+0x30, s1 sp+0x40, ra sp+0x80, s4 sp+0x70, s3 sp+0x60, s2 sp+0x50
// walk the extensions (to the 11 handlers of 0x7BD7E8 by extension id) and user data up to the next start code.
//   [_extensionAndUserData]
void _extensionAndUserData(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ff7c8
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    v0 = 0x7C0000;
    sd(s0, sp, 0x30);
    sd(s1, sp, 0x40);
    s0 = a0;
    sd(ra, sp, 0x80);
    sd(s4, sp, 0x70);
    sd(s3, sp, 0x60);
    sd(s2, sp, 0x50);
    a3 = addiu(v0, -10264);  // &0x7BD7E8
    ldl(v1, a3, 7);  // 0x7BD7EF
    ldr(v1, a3, 0);  // 0x7BD7E8
    ldl(a1, a3, 15);  // 0x7BD7F7
    ldr(a1, a3, 8);  // 0x7BD7F0
    ldl(a2, a3, 23);  // 0x7BD7FF
    ldr(a2, a3, 16);  // 0x7BD7F8
    sdl(v1, sp, 0x7);
    sdr(v1, sp, 0x0);
    sdl(a1, sp, 0xF);
    sdr(a1, sp, 0x8);
    sdl(a2, sp, 0x17);
    sdr(a2, sp, 0x10);
    ldl(v1, a3, 31);  // 0x7BD807
    ldr(v1, a3, 24);  // 0x7BD800
    ldl(a1, a3, 39);  // 0x7BD80F
    ldr(a1, a3, 32);  // 0x7BD808
    lw(a2, a3, 40);  // 0x7BD810
    sdl(v1, sp, 0x1F);
    sdr(v1, sp, 0x18);
    sdl(a1, sp, 0x27);
    sdr(a1, sp, 0x20);
    sw(a2, sp, 0x28);
    s1 = 1;
    jal(ctx, 0x4FF848u, gen::fn_flushByteBoundary_004ffb38);
    a0 = s0;
    for (;;) {
        // 0x004ff864
        charge(ctx, 5);
        a1 = 24;
        jal(ctx, 0x4FF864u, gen::fn__sceMpegPeepBit_004fd740);
        a0 = s0;
        a1 = 8;
        if (v0 != s1) {
            // 0x004ff878
            charge(ctx, 3);
            lw(v0, s0, mpeg::kAbort);
            if (v0 == 0) {
                backedge(ctx);
                // 0x004ff858
                charge(ctx, 3);
                jal(ctx, 0x4FF858u, gen::fn_j__sceMpegFlushBuf_0_004ff9d0);
                a0 = s0;
                continue;
            }
        }
        break;
    }
    // 0x004ff884
    charge(ctx, 4);
    s2 = 437;
    s4 = 434;
    s3 = 10;
    for (;;) {
    L_004ff95c:
        charge(ctx, 1);
        a0 = s0;
        for (;;) {
        L_004ff960:
            charge(ctx, 4);
            a1 = 32;
            jal(ctx, 0x4FF960u, gen::fn__sceMpegPeepBit_004fd740);
            a0 = s0;
            if (v0 == s2) {
                backedge(ctx);
            } else {
                goto L_004ff970_17;
            }
        L_004ff8a0:
            charge(ctx, 16);
            s1 = 1;
            jal(ctx, 0x4FF8A0u, gen::fn_flushBuf32_004ffb30);
            a0 = s0;
            a1 = 4;
            jal(ctx, 0x4FF8ACu, gen::fn__sceMpegNextBit_004fd658);
            v1 = sltu(s3, v0);
            if (v1 != 0) v0 = 0;
            v0 = sll(v0, 2);
            v1 = addu(sp, v0);
            lw(v0, v1, 0);
            a0 = s0;
            jalr(ctx, 0x4FF8C8u, v0.u());
            a0 = s0;
            jal(ctx, 0x4FF8D0u, gen::fn_flushByteBoundary_004ffb38);
            a0 = s0;
            for (;;) {
                // 0x004ff8ec
                charge(ctx, 5);
                a1 = 24;
                jal(ctx, 0x4FF8ECu, gen::fn__sceMpegPeepBit_004fd740);
                a0 = s0;
                a1 = 8;
                if (v0 == s1) {
                    break;
                }
                // 0x004ff900
                charge(ctx, 3);
                lw(v0, s0, mpeg::kAbort);
                if (v0 != 0) {
                    goto L_004ff90c_10;
                }
                backedge(ctx);
                // 0x004ff8e0
                charge(ctx, 3);
                jal(ctx, 0x4FF8E0u, gen::fn_j__sceMpegFlushBuf_0_004ff9d0);
                a0 = s0;
            }
        }
        break;
    }
L_004ff978_18:
    charge(ctx, 7);
    ld(s4, sp, 0x70);
    ld(s3, sp, 0x60);
    ld(s2, sp, 0x50);
    ld(s1, sp, 0x40);
    ld(s0, sp, 0x30);
    sp = addiu(sp, 0x90);
    return;
L_004ff898:
    charge(ctx, 2);
    a0 = s0;
    if (v0 == s2) {
        goto L_004ff8a0;
    }
    // 0x004ff914
    charge(ctx, 6);
    s1 = 1;
    jal(ctx, 0x4FF914u, gen::fn_flushBuf32_004ffb30);
    a0 = s0;
    jal(ctx, 0x4FF91Cu, gen::fn_flushByteBoundary_004ffb38);
    a0 = s0;
    for (;;) {
        // 0x004ff93c
        charge(ctx, 5);
        a1 = 24;
        jal(ctx, 0x4FF93Cu, gen::fn__sceMpegPeepBit_004fd740);
        a0 = s0;
        a1 = 8;
        if (v0 == s1) {
            break;
        }
        // 0x004ff950
        charge(ctx, 3);
        lw(v0, s0, mpeg::kAbort);
        if (v0 != 0) {
            goto L_004ff95c;
        }
        backedge(ctx);
        // 0x004ff930
        charge(ctx, 3);
        jal(ctx, 0x4FF930u, gen::fn_j__sceMpegFlushBuf_0_004ff9d0);
        a0 = s0;
    }
    goto L_004ff960;
L_004ff90c_10:
    charge(ctx, 2);
    goto L_004ff95c;
L_004ff970_17:
    charge(ctx, 2);
    ld(ra, sp, 0x80);
    if (v0 != s4) {
        goto L_004ff978_18;
    }
    backedge(ctx);
    goto L_004ff898;
}

// 0x004FFB30 flushBuf32 -- 8 bytes; leaf frame (no stack)
// drop 32 bits (a start code). [flushBuf32]
void flushBuf32(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5};
    // 0x004ffb30
    enter(ctx, 2);  // entry check point + this block's cycles
    a1 = 32;
    gen::fn_j__sceMpegFlushBuf_0_004ff9d0(ctx);  // tail call
}

// 0x00500278 _getpic -- 436 bytes; frame 0x50: s3 sp+0x30, s2 sp+0x20, s1 sp+0x10, ra sp+0x40, s0 sp+0x0
// the picture loop of sceMpegGetPicture: next header, decode or skip by picture type, until a picture is shown or the
//   stream ends. [_getpic]
void _getpic(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00500278
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    s3 = 0;
    sd(s1, sp, 0x10);
    s2 = 1;
    sd(ra, sp, 0x40);
    s1 = a0;
    sd(s0, sp, 0x0);
    lw(s0, s1, 64);
    lw(a2, s0, 236);
    v0 = a2 & 0x3F;
    sw(zero, s0, 0);
    if (v0 == 0) {
        // 0x005002c8
        charge(ctx, 3);
        lw(v0, s0, 2168);
        a0 = 0x7C0000;
        if (v0 == 0) {
            // 0x005002f4
            charge(ctx, 3);
            sw(zero, s0, 2100);
            v0 = si(-1);
            for (;;) {
                // 0x00500300
                charge(ctx, 2);
                cc = s3 == v0;  // the condition, before the delay slot changes it
                v0 = sltiu(s2, 5);
                if (!cc) {
                    for (;;) {
                        // 0x00500308
                        charge(ctx, 5);
                        a0 = s0;
                        jal(ctx, 0x500308u, gen::fn__sceMpegNextHeader_004ff9d8);
                        s2 = v0;
                        v0 = si(-1);
                        if (i64(s2) < 0) {
                            break;
                        }
                        // 0x0050031c
                        charge(ctx, 2);
                        v0 = sltiu(s2, 5);
                        if (s2 == 0) {
                            goto L_00500340;
                        }
                        // 0x00500324
                        charge(ctx, 4);
                        lw(v1, s0, 388);
                        lw(v0, s0, 232);
                        cc = v1 == v0;  // the condition, before the delay slot changes it
                        v0 = sltiu(s2, 5);
                        if (cc) {
                            goto L_00500340;
                        }
                        // 0x00500334
                        charge(ctx, 3);
                        lw(v0, s0, 2136);
                        cc = v0 != 0;  // the condition, before the delay slot changes it
                        v0 = sltiu(s2, 5);
                        if (!cc) {
                            goto L_00500340;
                        }
                        backedge(ctx);
                    }
                    break;
                }
            L_00500340:
                charge(ctx, 2);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = 0x7C0000;
                if (!cc) {
                    // 0x00500348
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v0 = addiu(v0, -9904);
                    v1 = addu(v1, v0);
                    lw(a0, v1, 0);
                    switch (a0.u()) {
                    case 0x500360u:  // table[0]
                        // 0x00500360
                        charge(ctx, 5);
                        a0 = s1;
                        jal(ctx, 0x500360u, gen::fn__sceMpegFlush_00501ae8);
                        v1 = 1;
                        sw(v1, s0, 0);
                        break;
                    case 0x500374u:  // table[1]
                        // 0x00500374
                        charge(ctx, 12);
                        sw(zero, s0, 188);
                        a0 = s1;
                        sw(zero, s0, 184);
                        a1 = 0;
                        sw(zero, s0, 180);
                        link(ctx, 0x500388u);  // $ra first: the delay slot below depends on it
                        lw(a2, s0, 168);
                        call(ctx, gen::fn__decodeOrSkip_00500e00);
                        lw(v1, s0, 180);
                        s3 = v0;
                        v1 = addiu(v1, 1);
                        sw(v1, s0, 180);
                        break;
                    case 0x5003A4u:  // table[2]
                        // 0x005003a4
                        charge(ctx, 9);
                        lw(a1, s0, 184);
                        a0 = s1;
                        link(ctx, 0x5003ACu);  // $ra first: the delay slot below depends on it
                        lw(a2, s0, 172);
                        call(ctx, gen::fn__decodeOrSkip_00500e00);
                        lw(v1, s0, 184);
                        s3 = v0;
                        v1 = addiu(v1, 1);
                        sw(v1, s0, 184);
                        break;
                    case 0x5003C8u:  // table[3, 4]
                        // 0x005003c8
                        charge(ctx, 8);
                        lw(a1, s0, 188);
                        a0 = s1;
                        link(ctx, 0x5003D0u);  // $ra first: the delay slot below depends on it
                        lw(a2, s0, 176);
                        call(ctx, gen::fn__decodeOrSkip_00500e00);
                        lw(v1, s0, 188);
                        s3 = v0;
                        v1 = addiu(v1, 1);
                        sw(v1, s0, 188);
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, a0.u());
                        return;
                    }
                }
                // 0x005003e8
                charge(ctx, 3);
                lw(v0, s0, 2168);
                a0 = 0x7C0000;
                if (v0 != 0) {
                    backedge(ctx);
                    goto L_005002e4;
                }
                // 0x005003f4
                charge(ctx, 3);
                lw(v0, s0, 2100);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = 1;
                if (!cc) {
                    // 0x00500400
                    charge(ctx, 3);
                    lw(v0, s0, 0);
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = si(-1);
                    if (!cc) {
                        goto L_0050040c_20;
                    }
                    backedge(ctx);
                    continue;
                }
                break;
            }
        } else {
            // 0x005002d4
            charge(ctx, 4);
            a0 = addiu(a0, -10000);
            jal(ctx, 0x5002D4u, gen::fn_scePrintf_00505e48);
            v0 = si(-1);
        }
    } else {
        // 0x005002b0
        charge(ctx, 6);
        a1 = 0x7C0000;
        a0 = s0;
        a1 = addiu(a1, -10064);  // "image buffer needs to be aligned to 64byte boundary(0x%08x)"
        jal(ctx, 0x5002B8u, gen::fn__sceMpegError1_005026c0);
        v0 = si(-1);
    }
    // 0x00500410 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_005002e4:
    charge(ctx, 4);
    a0 = addiu(a0, -9936);
    jal(ctx, 0x5002E4u, gen::fn_scePrintf_00505e48);
    v0 = si(-1);
    // 0x00500410 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_0050040c_20:
    charge(ctx, 1);
    v0 = 1;
    // 0x00500410 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00500430 _updateRefImage -- 692 bytes; leaf frame (no stack)
// rotate the reference frames for the next picture and decide whether it can be decoded (its references complete); copy
//   the picture's parameters into the current descriptor. [_updateRefImage]
void _updateRefImage(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00500430
    enter(ctx, 11);  // entry check point + this block's cycles
    a3 = a0;
    t3 = 4;
    lw(t1, a3, 388);
    t4 = 2;
    lw(t2, a3, 352);
    t0 = 0;
    v0 = t1 ^ 0x3;
    t5 = 0;
    t6 = 3;
    if (v0 == 0) t3 = t4;
    if (t2 != t6) {
        // 0x00500568
        charge(ctx, 2);
        if (a1 != 0) {
            lw(v0, a3, 460);
        } else {
            // 0x00500570
            charge(ctx, 13);
            lw(a2, a3, 456);
            lw(a0, a3, 460);
            sw(a2, a3, 460);
            lw(a2, a3, 472);
            lw(v1, a3, 476);
            sw(a2, a3, 476);
            lw(a2, a3, 488);
            lw(v0, a3, 492);
            sw(a0, a3, 456);
            sw(v1, a3, 472);
            sw(v0, a3, 488);
            sw(a2, a3, 492);
            lw(v0, a3, 460);
        }
        // 0x005005a4
        charge(ctx, 6);
        lw(a0, a3, 476);
        lw(v1, a3, 492);
        sw(v0, a3, 464);
        sw(a0, a3, 480);
        sw(v1, a3, 496);
        if (t1 == t6) {
            // 0x005005bc
            charge(ctx, 2);
            if (t2 != t4) {
                t5 = 1;
                goto L_0050061c;
            }
            // 0x005005c4
            charge(ctx, 3);
            lw(v0, a3, 456);
            a0 = 1;
            goto L_0050060c;
        }
        // 0x005005d0
        charge(ctx, 5);
        v0 = t1 ^ 0x1;
        a2 = 1;
        if (v0 != 0) v1 = a0;
        v0 = v1;
        if (t2 != t4) {
        L_00500618:
            charge(ctx, 1);
            t5 = 1;
        L_0050061c:
            charge(ctx, 1);
            v0 = 2;
        } else {
            // 0x005005e4
            charge(ctx, 2);
            if (a1 == 0) {
                lw(v0, a3, 472);
            } else {
                // 0x005005ec
                charge(ctx, 3);
                lw(v0, v0, 40);
                if (v0 == a2) {
                    t5 = 1;
                    goto L_0050061c;
                }
                // 0x005005f8
                charge(ctx, 1);
                lw(v0, a3, 472);
                goto L_005005fc;
            }
        L_005005fc:
            charge(ctx, 3);
            lw(a0, v0, 40);
            v0 = 2;
            if (a0 == a2) {
                // 0x00500608
                charge(ctx, 1);
                lw(v0, a3, 488);
            L_0050060c:
                charge(ctx, 3);
                lw(v1, v0, 40);
                v0 = 2;
                if (v1 == a0) {
                    goto L_00500618;
                }
            }
        }
    } else {
        // 0x0050045c
        charge(ctx, 11);
        lw(v0, a3, 180);
        lw(v1, a3, 184);
        lw(a1, a3, 468);
        lw(a2, a3, 484);
        v0 = addu(v0, v1);
        lw(a0, a3, 500);
        v0 = slt(v0, t3);
        sw(a1, a3, 464);
        sw(a2, a3, 480);
        sw(a0, a3, 496);
        if (v0 == 0) {
            // 0x00500488
            charge(ctx, 3);
            sw(zero, a3, 252);
            sw(zero, a3, 440);
            sw(zero, a3, 436);
        }
        // 0x00500494
        charge(ctx, 3);
        lw(v0, a3, 252);
        if (v0 != 0) {
            lw(v0, a3, 436);
        } else {
            // 0x005004a0
            charge(ctx, 3);
            lw(v0, a3, 440);
            if (v0 != 0) {
                // 0x005004ac
                charge(ctx, 1);
                lw(v0, a3, 436);
                goto L_005004b0;
            }
            sw(zero, a3, 252);
            goto L_005004d8;
        }
    L_005004b0:
        charge(ctx, 2);
        if (v0 != 0) {
            sw(zero, a3, 252);
        } else {
            // 0x005004b8
            charge(ctx, 8);
            lw(v0, a3, 456);
            lw(a0, a3, 472);
            sw(zero, v0, 40);
            lw(v1, a3, 488);
            sw(zero, a0, 40);
            sw(zero, v1, 40);
            lw(t1, a3, 388);
            sw(zero, a3, 252);
        }
    L_005004d8:
        charge(ctx, 3);
        v0 = 3;
        sw(zero, a3, 440);
        if (t1 != v0) {
            // 0x0050050c
            charge(ctx, 5);
            lw(v0, a3, 472);
            v1 = 1;
            lw(a0, v0, 40);
            if (a0 != v1) {
                lw(v0, a3, 436);
            } else {
                // 0x00500520
                charge(ctx, 4);
                lw(v0, a3, 488);
                lw(v1, v0, 40);
                if (v1 != a0) {
                    // 0x00500530
                    charge(ctx, 1);
                    lw(v0, a3, 436);
                    goto L_00500534;
                }
                lw(v0, a3, 476);
            L_00500540:
                charge(ctx, 4);
                v1 = 1;
                lw(a0, v0, 40);
                v0 = 2;
                if (a0 == v1) {
                    // 0x00500550
                    charge(ctx, 1);
                    lw(v1, a3, 492);
                L_00500554:
                    charge(ctx, 5);
                    t5 = a0;
                    lw(v0, v1, 40);
                    v0 = v0 ^ 0x1;
                    if (v0 != 0) t5 = 0;
                    goto L_0050061c;
                }
                goto L_00500620;
            }
        L_00500534:
            charge(ctx, 2);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 2;
            if (!cc) {
                // 0x0050053c
                charge(ctx, 1);
                lw(v0, a3, 476);
                goto L_00500540;
            }
        } else {
            // 0x005004e4
            charge(ctx, 5);
            lw(v1, a3, 456);
            a0 = 1;
            lw(v0, v1, 40);
            if (v0 == a0) {
                lw(v1, a3, 460);
                goto L_00500554;
            }
            // 0x005004f8
            charge(ctx, 3);
            lw(v0, a3, 436);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 2;
            if (!cc) {
                // 0x00500504
                charge(ctx, 2);
                lw(v1, a3, 460);
                goto L_00500554;
            }
        }
    }
L_00500620:
    charge(ctx, 2);
    cc = t1 == v0;  // the condition, before the delay slot changes it
    v0 = slti(t1, 3);
    if (cc) {
        // 0x00500654
        charge(ctx, 1);
        lw(t0, a3, 496);
    L_00500658:
        charge(ctx, 1);
        sw(zero, t0, 40);
    } else {
        // 0x00500628
        charge(ctx, 2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (cc) {
            // 0x00500640
            charge(ctx, 3);
            v0 = 3;
            if (t1 == v0) {
                lw(t0, a3, 464);
                goto L_00500658;
            }
            // 0x0050064c
            charge(ctx, 2);
            sw(zero, t0, 40);
        } else {
            // 0x00500630
            charge(ctx, 2);
            if (t1 == v0) {
                lw(t0, a3, 480);
                goto L_00500658;
            }
            // 0x00500638
            charge(ctx, 2);
            sw(zero, t0, 40);
        }
    }
    // 0x0050065c
    charge(ctx, 34);
    v0 = t5;
    ld(v1, a3, 2104);
    lw(a0, a3, 352);
    sd(v1, t0, 24);
    sw(a0, t0, 44);
    ld(v1, a3, 2112);
    lw(a0, a3, 388);
    sd(v1, t0, 32);
    sw(a0, t0, 48);
    lw(v1, a3, 332);
    sw(v1, t0, 52);
    lw(a0, a3, 408);
    sw(a0, t0, 56);
    lw(v1, a3, 392);
    sw(v1, t0, 60);
    lw(a0, a3, 404);
    sw(a0, t0, 64);
    lw(v1, a3, 412);
    sw(v1, t0, 68);
    lw(a0, a3, 416);
    sw(a0, t0, 72);
    lw(v1, a3, 420);
    sw(v1, t0, 76);
    lw(a0, a3, 424);
    sw(a0, t0, 80);
    lw(v1, a3, 428);
    sw(v1, t0, 84);
    lw(a0, a3, 432);
    sw(a0, t0, 88);
    lw(v1, a3, 344);
    sw(v1, t0, 92);
    lw(a0, a3, 348);
    sw(a0, t0, 96);
}

// 0x005006E8 _decodeOrSkipFrame -- 368 bytes; frame 0x70: s2 sp+0x40, s0 sp+0x20, ra sp+0x60, s3 sp+0x50, s1 sp+0x30
// decode a frame picture (or skip it past the type's limit through the skip callback), then the output.
//   [_decodeOrSkipFrame]
void _decodeOrSkipFrame(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005006e8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = si(-1);
    sd(s2, sp, 0x40);
    sd(s0, sp, 0x20);
    s2 = a0;
    sd(ra, sp, 0x60);
    s0 = 0;
    sd(s3, sp, 0x50);
    sd(s1, sp, 0x30);
    lw(s1, s2, 64);
    if (a2 != v0) {
        // 0x00500714
        charge(ctx, 3);
        v0 = slt(a1, a2);
        a0 = s1;
        if (v0 != 0) {
            goto L_00500720;
        }
        // 0x0050075c
        charge(ctx, 6);
        a1 = 0;
        jal(ctx, 0x50075Cu, gen::fn__updateRefImage_00500430);
        v1 = 1;
        s3 = v0;
        sw(v1, sp, 0x0);
        if (s2 != 0) {
            // 0x00500774
            charge(ctx, 3);
            lw(a2, s2, 64);
            s0 = 1;
            if (a2 == 0) {
            L_005007c4:
                charge(ctx, 1);
                lw(v0, s1, 2168);
            } else {
                // 0x00500780
                charge(ctx, 3);
                lw(a3, a2, 24);
                if (a3 != 0) {
                    // 0x0050078c
                    charge(ctx, 13);
                    lw(v0, a2, 32);
                    s0 = gp;
                    gp = v0;
                    lw(v1, sp, 0x0);
                    v0 = 12;
                    a0 = s2;
                    a1 = sp;
                    mult(t0, v1, v0);
                    v1 = addu(t0, a2);
                    jt = a3.u();  // the target, read before the delay slot
                    link(ctx, 0x5007B0u);  // $ra = the return address
                    lw(a2, v1, 16);
                    call_ptr(ctx, jt);
                    v1 = gp;
                    gp = s0;
                    goto L_005007c0;
                }
                lw(v0, s1, 2168);
            }
            goto L_005007c8;
        }
    L_005007c0:
        charge(ctx, 1);
        s0 = 1;
        goto L_005007c4;
    }
L_00500720:
    charge(ctx, 3);
    lw(v0, s1, 8);
    a0 = s1;
    if (v0 == 0) {
        // 0x0050072c
        charge(ctx, 3);
        sw(zero, s2, 8);
        v0 = 1;
        sw(v0, s1, 8);
    }
    // 0x00500738
    charge(ctx, 4);
    a1 = 0;
    jal(ctx, 0x500738u, gen::fn__updateRefImage_00500430);
    v1 = 0;
    if (v0 != 0) {
        // 0x00500748
        charge(ctx, 3);
        a0 = s1;
        jal(ctx, 0x500748u, gen::fn__decPicture_00500f98);
        v1 = sltu(0, v0);
    }
    // 0x00500754
    charge(ctx, 2);
    s3 = v1;
    goto L_005007c4;
L_005007c8:
    charge(ctx, 2);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x005007d0
        charge(ctx, 8);
        lw(a1, s1, 296);
        a0 = s1;
        link(ctx, 0x5007D8u);  // $ra first: the delay slot below depends on it
        lw(a2, s1, 4);
        call(ctx, gen::fn__sceMpegOutputFrame_00501ba8);
        lw(v1, s1, 388);
        v0 = 3;
        if (v1 == v0) {
            lw(v1, s1, 192);
        } else {
            // 0x005007f0
            charge(ctx, 2);
            if (s0 != 0) {
                lw(v1, s1, 192);
            } else {
                // 0x005007f8
                charge(ctx, 4);
                lw(v0, s1, 304);
                v0 = sltiu(v0, 1);
                sw(v0, s1, 304);
                lw(v1, s1, 192);
            }
        }
        // 0x00500808
        charge(ctx, 6);
        lw(v0, s1, 296);
        v0 = subu(v0, v1);
        sw(v0, s2, 8);
        lw(v1, s1, 304);
        v0 = s3;
        if (v1 == 0) {
            // 0x00500820
            charge(ctx, 7);
            lw(v0, s1, 296);
            lw(v1, s1, 4);
            v0 = addiu(v0, 1);
            v1 = addiu(v1, 1);
            sw(v0, s1, 296);
            sw(v1, s1, 4);
            v0 = s3;
        }
    }
    // 0x0050083c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x60);
    ld(s3, sp, 0x50);
    ld(s2, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x70);
}

// 0x00500E00 _decodeOrSkip -- 68 bytes; frame 0x10: ra sp+0x0
// frame or field picture. [_decodeOrSkip]
void _decodeOrSkip(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00500e00
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = a0;
    sd(ra, sp, 0x0);
    v1 = 3;
    lw(a0, a3, 64);
    lw(v0, a0, 388);
    if (v0 == v1) {
        // 0x00500e30
        charge(ctx, 3);
        a0 = a3;
        jal(ctx, 0x500E30u, gen::fn__decodeOrSkipFrame_005006e8);
        ld(ra, sp, 0x0);
    } else {
        // 0x00500e20
        charge(ctx, 4);
        a0 = a3;
        jal(ctx, 0x500E20u, gen::fn__decodeOrSkipField_00500858);
        ld(ra, sp, 0x0);
    }
    // 0x00500e3c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00500F98 _decPicture -- 204 bytes; frame 0x30: s0 sp+0x0, ra sp+0x20, s1 sp+0x10
// decode the picture data into the current descriptor (mark it complete). [_decPicture]
void _decPicture(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00500f98
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 3;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    s0 = a0;
    sd(s1, sp, 0x10);
    lw(v1, s0, mpeg::kPicStruct);
    cc = v1 != v0;  // the condition, before the delay slot changes it
    v0 = 2;
    if (!cc) {
        // 0x00500fbc
        charge(ctx, 3);
        lw(v0, s0, mpeg::kFieldParity);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 2;
        if (!cc) {
            // 0x00500fc8
            charge(ctx, 6);
            a1 = 0x7C0000;
            a1 = addiu(a1, -9880);  // "odd number of field pictures"
            jal(ctx, 0x500FCCu, gen::fn__sceMpegError_00502668);
            sw(zero, s0, mpeg::kFieldParity);
            lw(v1, s0, mpeg::kPicStruct);
            v0 = 2;
        }
    }
    // 0x00500fe0
    charge(ctx, 2);
    cc = v1 == v0;  // the condition, before the delay slot changes it
    v0 = slti(v1, 3);
    if (cc) {
        // 0x0050101c
        charge(ctx, 2);
        lw(s1, s0, 496);
    } else {
        // 0x00500fe8
        charge(ctx, 2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (cc) {
            // 0x00501000
            charge(ctx, 3);
            v0 = 3;
            a1 = 0x7C0000;
            if (v1 != v0) {
                // 0x00501024
                charge(ctx, 1);
                lw(s1, s0, mpeg::kRefCur);
            L_00501028:
                charge(ctx, 3);
                a1 = addiu(a1, -9848);
                a0 = s0;
                jal(ctx, 0x50102Cu, gen::fn__sceMpegError_00502668);
            } else {
                // 0x0050100c
                charge(ctx, 2);
                lw(s1, s0, mpeg::kRefCur);
            }
        } else {
            // 0x00500ff0
            charge(ctx, 2);
            a1 = 0x7C0000;
            if (v1 != v0) {
                // 0x00500ff8
                charge(ctx, 2);
                lw(s1, s0, mpeg::kRefCur);
                goto L_00501028;
            }
            // 0x00501014
            charge(ctx, 2);
            lw(s1, s0, 480);
        }
    }
    // 0x00501034
    charge(ctx, 5);
    a0 = s0;
    jal(ctx, 0x501034u, gen::fn__sceMpegPictureData0_004fc168);
    v1 = v0;
    v0 = 1;
    if (v1 != 0) {
        // 0x00501048
        charge(ctx, 1);
        sw(v0, s1, 40);
    }
    // 0x0050104c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    v0 = v1;
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00501408 _dispRefImage -- 704 bytes; frame 0x190: s7 sp+0x170, s6 sp+0x160, s5 sp+0x150, s3 sp+0x130, s2 sp+0x120, ra sp+0x180, s1 sp+0x110, s0 sp+0x100, s4 sp+0x140
// hand a complete reference picture to the display: PTS, the picture-info word, the colour conversion or the 8-bit
//   copy. [_dispRefImage]
void _dispRefImage(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00501408
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x190);
    sd(s7, sp, 0x170);
    sd(s6, sp, 0x160);
    sd(s5, sp, 0x150);
    sd(s3, sp, 0x130);
    sd(s2, sp, 0x120);
    s3 = a1;
    sd(ra, sp, 0x180);
    s2 = a0;
    sd(s1, sp, 0x110);
    sd(s0, sp, 0x100);
    sd(s4, sp, 0x140);
    lw(s4, s2, mpeg::kOutInfo);
    lw(v0, s2, 140);
    s5 = addiu(s4, 16);
    s6 = addiu(s4, 24);
    s7 = addiu(s4, 32);
    if (v0 == 0) {
        // 0x005014d8
        charge(ctx, 2);
        ld(v1, s3, 24);
        sd(v1, s5, 0);
    } else {
        // 0x00501450
        charge(ctx, 3);
        ld(v1, s3, 24);
        if (i64(v1) >= 0) {
            sd(v1, s5, 0);
        } else {
            // 0x0050145c
            charge(ctx, 3);
            lw(v0, s2, 152);
            if (i64(v0) < 0) {
                sd(v1, s5, 0);
            } else {
                // 0x00501468
                charge(ctx, 24);
                ld(a1, s2, 160);
                lw(s0, s2, 156);
                a1 = dsll32(a1, 0);
                a1 = dsra32(a1, 0);
                ld(a0, s2, 144);
                s1 = a1 & 0x1;
                s0 = s0 & 0x1;
                s0 = s1 & s0;
                v0 = a0 & 0x1;
                s0 = s0 & v0;
                s0 = dsll32(s0, 0);
                s0 = dsra32(s0, 0);
                // daddu a1: a 64-bit move to itself (no effect)
                jal(ctx, 0x501498u, gen::fn___muldi3_0052ea78);
                v0 = dsll(v0, 31);
                v0 = dsra32(v0, 0);
                lw(v1, s2, 152);
                v0 = addu(v0, s0);
                v1 = addu(v1, v0);
                sd(v1, s4, 16);
                ld(v0, s2, 144);
                s1 = s1 & v0;
                lw(s4, s2, mpeg::kOutInfo);
                if (s1 != 0) {
                    // 0x005014c8
                    charge(ctx, 4);
                    lw(v0, s2, 156);
                    v0 = addiu(v0, 1);
                    sw(v0, s2, 156);
                }
            }
        }
    }
    // 0x005014e0
    charge(ctx, 4);
    lw(v1, s2, 264);
    v0 = 2;
    if (v1 != v0) {
        lw(a2, s3, 64);
    } else {
        // 0x005014f0
        charge(ctx, 3);
        ld(v0, s2, 256);
        if (i64(v0) < 0) {
            lw(a2, s3, 64);
        } else {
            // 0x005014fc
            charge(ctx, 5);
            sd(v0, s5, 0);
            v0 = si(-1);
            sw(zero, s2, 264);
            sd(v0, s2, 256);
            lw(a2, s3, 64);
        }
    }
    // 0x00501510
    charge(ctx, 48);
    t0 = 0x780000;
    lw(a1, s3, 60);
    t0 = addiu(t0, -3136);  // &0x77F3C0
    lw(v0, s3, 52);
    a2 = dsll(a2, 5);
    lw(a3, s3, 44);
    a1 = dsll(a1, 6);
    lw(a0, s3, 56);
    a2 = a2 | a1;
    lw(v1, s3, 48);
    v0 = dsll(v0, 8);
    ld(a1, s3, 32);
    v0 = v0 | a3;
    v1 = dsll(v1, 3);
    a0 = dsll(a0, 7);
    a0 = a0 | v1;
    v0 = v0 | a2;
    sd(a1, s6, 0);
    v0 = v0 | a0;
    sd(v0, s7, 0);
    lw(a1, s2, 244);
    ld(v0, s4, 32);
    lw(v1, s4, 16);
    v0 = dsll(v0, 27);
    v0 = dsra32(v0, 0);
    sw(v1, s2, 152);
    v0 = v0 & 0xF;
    v0 = sll(v0, 2);
    lw(v1, s3, 92);
    v0 = addu(v0, t0);
    lwu(a0, v0, 0);
    sw(v1, s2, 224);
    sd(a0, s2, 160);
    lw(v0, s3, 96);
    sw(v0, s2, 228);
    lw(v1, s3, 68);
    sw(v1, s2, 200);
    lw(v0, s3, 72);
    sw(v0, s2, 204);
    lw(v1, s3, 76);
    sw(v1, s2, 208);
    lw(v0, s3, 80);
    sw(v0, s2, 212);
    lw(v1, s3, 84);
    sw(v1, s2, 216);
    lw(v0, s3, 88);
    sw(v0, s2, 220);
    if (a1 == 0) {
        // 0x005015f4
        charge(ctx, 6);
        lw(v1, s3, 12);
        lw(a0, s3, 16);
        lw(v0, s2, 248);
        mult(v1, v1, a0);
        v0 = slt(v0, v1);
        s0 = v0 ^ 0x1;
    } else {
        // 0x005015d0
        charge(ctx, 5);
        lw(v0, s2, 240);
        lw(v1, s3, 4);
        v0 = slt(v0, v1);
        s0 = 0;
        if (v0 == 0) {
            // 0x005015e4
            charge(ctx, 4);
            lw(v0, s3, 8);
            v0 = slt(a1, v0);
            s0 = v0 ^ 0x1;
        }
    }
    // 0x0050160c
    charge(ctx, 2);
    if (s0 != 0) {
        lw(v1, s3, 40);
    } else {
        // 0x00501614
        charge(ctx, 12);
        a2 = 0x7C0000;
        lw(a3, s3, 4);
        lw(t0, s3, 8);
        a2 = addiu(a2, -9784);  // "Too small buffer size for %dx%d picture\n"
        a0 = sp;
        a1 = 256;
        jal(ctx, 0x501628u, gen::fn_sceSnprintf_00505d90);
        a0 = s2;
        a1 = sp;
        jal(ctx, 0x501634u, gen::fn__sceMpegError_00502668);
        ld(ra, sp, 0x180);
        if (s0 != 0) {
            // 0x00501644
            charge(ctx, 1);
            lw(v1, s3, 40);
            goto L_00501648;
        }
        // 0x005016a0 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(s7, sp, 0x170);
        ld(s6, sp, 0x160);
        ld(s5, sp, 0x150);
        ld(s4, sp, 0x140);
        ld(s3, sp, 0x130);
        ld(s2, sp, 0x120);
        ld(s1, sp, 0x110);
        ld(s0, sp, 0x100);
        sp = addiu(sp, 0x190);
        return;
    }
L_00501648:
    charge(ctx, 3);
    v0 = 1;
    ld(ra, sp, 0x180);
    if (v1 == v0) {
        // 0x00501654
        charge(ctx, 3);
        lw(v0, s2, 196);
        a1 = s3;
        if (v0 == 0) {
            // 0x00501670
            charge(ctx, 3);
            a0 = s2;
            jal(ctx, 0x501670u, gen::fn__cpr8_00501178);
            lw(v0, s2, mpeg::kOutState);
        } else {
            // 0x00501660
            charge(ctx, 4);
            a0 = s2;
            jal(ctx, 0x501660u, gen::fn__sceMpegCscStoreRefImage_00501df8);
            lw(v0, s2, mpeg::kOutState);
        }
        // 0x0050167c
        charge(ctx, 3);
        v1 = 2;
        cc = v0 == v1;  // the condition, before the delay slot changes it
        v0 = 1;
        if (!cc) {
            // 0x00501688
            charge(ctx, 4);
            lw(v0, s2, mpeg::kDecFrame);
            sw(v1, s2, mpeg::kOutState);
            sw(v0, s2, mpeg::kShownFrame);
            v0 = 1;
        }
        // 0x00501698
        charge(ctx, 2);
        sw(v0, s2, mpeg::kPicDone);
        ld(ra, sp, 0x180);
    }
    // 0x005016a0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s7, sp, 0x170);
    ld(s6, sp, 0x160);
    ld(s5, sp, 0x150);
    ld(s4, sp, 0x140);
    ld(s3, sp, 0x130);
    ld(s2, sp, 0x120);
    ld(s1, sp, 0x110);
    ld(s0, sp, 0x100);
    sp = addiu(sp, 0x190);
}

}  // namespace p3fes::game
