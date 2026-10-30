// Phase 5 slice unblock, part rw (game/include/p3fes/game/unblock.h):
// RenderWare callees -- particle-tank create / lock / unlock, the spline segment, atomic / geometry / material /
// camera / frame helpers, the texture name read, the sky device's VU0 transforms, a stub.
// These functions were kept recompiled only because other slices' pair tests stood them in with recorders; slice
// unblock rewrote those checks as guest-memory checks (docs/INTEGRATION_LOG.md, "unblock"). Started from p3fes_handgen's
// bodies (register for register, block for block as the recompiled ones; game/include/p3fes/game/hg_cpu.h): every path
// keeps the original's statements, cycle charges and check points in order; the role comments name what each does.
// Pair tests: tests/game/test_unblock.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/unblock.h"

namespace p3fes::recomp_gen {
void fn_sub_469A90_00469a90(p3fes::EEContext&);
void fn_sub_473FB0_00473fb0(p3fes::EEContext&);
void fn_sub_474210_00474210(p3fes::EEContext&);
void fn_sub_474260_00474260(p3fes::EEContext&);
void fn_sub_474640_00474640(p3fes::EEContext&);
void fn_sub_4747F0_004747f0(p3fes::EEContext&);
void fn_sub_48D270_0048d270(p3fes::EEContext&);
void fn_sub_491A80_00491a80(p3fes::EEContext&);
void fn_sub_492D10_00492d10(p3fes::EEContext&);
void fn_sub_493B60_00493b60(p3fes::EEContext&);
void fn_sub_494CC0_00494cc0(p3fes::EEContext&);
void fn_sub_494D50_00494d50(p3fes::EEContext&);
void fn_sub_49C230_0049c230(p3fes::EEContext&);
void fn_sub_4C1C50_004c1c50(p3fes::EEContext&);
void fn_sub_4C1D10_004c1d10(p3fes::EEContext&);
void fn_sub_4C47E0_004c47e0(p3fes::EEContext&);
void fn_sub_4C6560_004c6560(p3fes::EEContext&);
void fn_sub_4CA030_004ca030(p3fes::EEContext&);
void fn_sub_4CB270_004cb270(p3fes::EEContext&);
void fn_sub_4D0BE0_004d0be0(p3fes::EEContext&);
void fn_sub_4D0F00_004d0f00(p3fes::EEContext&);
void fn_sub_4D1840_004d1840(p3fes::EEContext&);
void fn_sub_4D18C0_004d18c0(p3fes::EEContext&);
void fn_sub_4E3E40_004e3e40(p3fes::EEContext&);
void fn_sub_4E3EC0_004e3ec0(p3fes::EEContext&);
void fn_sub_4E3F20_004e3f20(p3fes::EEContext&);
void fn_sub_4E3FC0_004e3fc0(p3fes::EEContext&);
void fn_sub_4E4020_004e4020(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x00469A90 sub_469A90 -- 8 bytes; leaf frame (no stack)
// [stub] Returns 1 (a callback stub).
void sub_469A90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00469a90
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}

// 0x00474210 sub_474210 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [RpPTank] [proposed: RpPTankAtomicCreate] sub_474260($a0, the format of sub_473FB0($a1), off_77B1D0).
void sub_474210(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00474210
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t9 = a2;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = a1;
    jal(ctx, 0x474224u, gen::fn_sub_473FB0_00473fb0);
    a3 = 0x780000;
    a0 = s0;
    a2 = t9;
    a1 = v0;
    a3 = addiu(a3, -20016);  // "@UG"
    jal(ctx, 0x47423Cu, gen::fn_sub_474260_00474260);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00474640 sub_474640 -- 432 bytes; leaf frame (no stack)
// [RpPTank] [proposed: RpPTankAtomicLock] Locks one stream ($a2: position, colour, size, ...) of a particle tank atomic:
// writes {pointer, stride} to $a1, marks the stream locked; {0, 0} when the tank has no such stream.
void sub_474640(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00474640
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v0, gp, -17792);  // 0x7CE770
    v0 = addu(a0, v0);
    lw(v0, v0, 0);
    v1 = addiu(v0, 80);
    lw(v0, v0, 168);
    v0 = v0 & a2;
    if (v0 == 0) {
        // 0x004747d0
        charge(ctx, 4);
        sw(zero, a1, 0);
        v0 = 0;
        sw(zero, a1, 4);
    } else {
        // 0x00474660
        charge(ctx, 3);
        v0 = 256;
        if (a2 == v0) {
            // 0x00474774
            charge(ctx, 4);
            lwc1(f1, v1, 68);
            lwc1(f0, v1, 72);
            swc1(f1, a1, 0);
            swc1(f0, a1, 4);
        L_00474784:
            charge(ctx, 1);
            lw(v0, v1, 84);
        } else {
            // 0x0047466c
            charge(ctx, 3);
            v0 = 128;
            if (a2 == v0) {
                // 0x00474760
                charge(ctx, 5);
                lwc1(f1, v1, 60);
                lwc1(f0, v1, 64);
                swc1(f1, a1, 0);
                swc1(f0, a1, 4);
                goto L_00474784;
            }
            // 0x00474678
            charge(ctx, 3);
            v0 = 64;
            if (a2 == v0) {
                // 0x0047474c
                charge(ctx, 5);
                lwc1(f1, v1, 44);
                lwc1(f0, v1, 48);
                swc1(f1, a1, 0);
                swc1(f0, a1, 4);
                goto L_00474784;
            }
            // 0x00474684
            charge(ctx, 3);
            v0 = 32;
            if (a2 == v0) {
                // 0x00474738
                charge(ctx, 5);
                lwc1(f1, v1, 52);
                lwc1(f0, v1, 56);
                swc1(f1, a1, 0);
                swc1(f0, a1, 4);
                goto L_00474784;
            }
            // 0x00474690
            charge(ctx, 3);
            v0 = 16;
            if (a2 == v0) {
                // 0x00474724
                charge(ctx, 5);
                lwc1(f1, v1, 20);
                lwc1(f0, v1, 24);
                swc1(f1, a1, 0);
                swc1(f0, a1, 4);
                goto L_00474784;
            }
            // 0x0047469c
            charge(ctx, 3);
            v0 = 8;
            if (a2 == v0) {
                // 0x00474710
                charge(ctx, 5);
                lwc1(f1, v1, 12);
                lwc1(f0, v1, 16);
                swc1(f1, a1, 0);
                swc1(f0, a1, 4);
                goto L_00474784;
            }
            // 0x004746a8
            charge(ctx, 3);
            v0 = 4;
            if (a2 == v0) {
                // 0x004746fc
                charge(ctx, 5);
                lwc1(f1, v1, 28);
                lwc1(f0, v1, 32);
                swc1(f1, a1, 0);
                swc1(f0, a1, 4);
                goto L_00474784;
            }
            // 0x004746b4
            charge(ctx, 3);
            v0 = 2;
            if (a2 == v0) {
                // 0x004746e8
                charge(ctx, 5);
                lwc1(f1, v1, 36);
                lwc1(f0, v1, 40);
                swc1(f1, a1, 0);
                swc1(f0, a1, 4);
                goto L_00474784;
            }
            // 0x004746c0
            charge(ctx, 3);
            v0 = 1;
            if (a2 == v0) {
                // 0x004746d4
                charge(ctx, 5);
                lwc1(f1, v1, 4);
                lwc1(f0, v1, 8);
                swc1(f1, a1, 0);
                swc1(f0, a1, 4);
                goto L_00474784;
            }
            // 0x004746cc
            charge(ctx, 2);
            lw(v0, v1, 84);
        }
        // 0x00474788
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x004747e0
            charge(ctx, 2);
            sw(v0, a1, 4);
            backedge(ctx);
        }
        // 0x00474790
        charge(ctx, 3);
        lw(v0, a1, 0);
        if (v0 != 0) {
            // 0x0047479c
            charge(ctx, 4);
            v1 = 0x40000000;
            v0 = a3 & v1;
            if (v0 == v1) {
                // 0x004747ac
                charge(ctx, 7);
                lw(v0, gp, -17792);  // 0x7CE770
                a1 = a3 | a2;
                v0 = addu(a0, v0);
                lw(v1, v0, 0);
                lw(v0, v1, 60);
                v0 = v0 | a1;
                sw(v0, v1, 60);
            }
        }
        // 0x004747c8
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004747e8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004747F0 sub_4747F0 -- 40 bytes; leaf frame (no stack)
// [RpPTank] [proposed: RpPTankAtomicUnlock] Moves the locked streams (+60) into the dirty mask (+64).
void sub_4747F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x004747f0
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(v1, gp, -17792);  // 0x7CE770
    v0 = a0;
    v1 = addu(a0, v1);
    lw(a1, v1, 0);
    lw(a0, a1, 64);
    lw(v1, a1, 60);
    v1 = a0 | v1;
    sw(v1, a1, 64);
    sw(zero, a1, 60);
}

// 0x0048D270 sub_48D270 -- 252 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [RtSpline] [proposed: RtSplineFindPosition] Evaluates the spline control segment $a1 (open / closed by +12) at $f12;
// "control point out of range" errors through the RW error handler.
void sub_48D270(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0048d270
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    if (i64(s1) >= 0) {
        // 0x0048d294
        charge(ctx, 4);
        lw(v1, s2, 12);
        v0 = 2;
        if (v1 == v0) {
            // 0x0048d2c4
            charge(ctx, 3);
            lw(v0, s2, 8);
            v0 = addiu(v0, -3);
        } else {
            // 0x0048d2a4
            charge(ctx, 3);
            a0 = 1;
            if (v1 == a0) {
                // 0x0048d2b8
                charge(ctx, 3);
                lw(v0, s2, 8);
                v0 = addiu(v0, -2);
            } else {
                // 0x0048d2b0
                charge(ctx, 2);
                v0 = 258;
                // 0x0048d2d0
                charge(ctx, 6);
                link(ctx, 0x48D2D0u);  // $ra first: the delay slot below depends on it
                sw(v0, sp, 0x40);
                call(ctx, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x44);
                a0 = addiu(sp, 0x40);
                jal(ctx, 0x48D2DCu, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
            }
        }
        // 0x0048d2e8
        charge(ctx, 3);
        at = slt(s1, v0);
        if (at == 0) {
            goto L_0048d328;
        }
        // 0x0048d2f4
        charge(ctx, 13);
        lw(v1, s2, 20);
        v0 = sll(s1, 1);
        a0 = addu(v0, s1);
        a0 = sll(a0, 2);
        v0 = s0;
        v1 = addu(v1, a0);
        lwc1(f2, v1, 0);
        lwc1(f1, v1, 4);
        lwc1(f0, v1, 8);
        swc1(f2, s0, 0);
        swc1(f1, s0, 4);
        swc1(f0, s0, 8);
        // 0x0048d354 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_0048d328:
    charge(ctx, 11);
    v1 = 258;
    v0 = lui(0x8000);
    a1 = 0x780000;
    sw(v1, sp, 0x48);
    a0 = v0 | 0x3;
    a1 = addiu(a1, -9024);  // "control point out of range"
    jal(ctx, 0x48D33Cu, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0x4C);
    a0 = addiu(sp, 0x48);
    jal(ctx, 0x48D348u, gen::fn_sub_4C1C50_004c1c50);
    v0 = 0;
    // 0x0048d354 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00491A80 sub_491A80 -- 192 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [RpAtomic] [proposed: RpAtomicDestroy] Destroys an atomic: plugin destructors (0x77DCE0), geometry, interpolator /
// frame links, the world sector link, then the block back to its free list (slot 0x96018C).
void sub_491A80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00491a80
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    s1 = a0;
    sq(s0, sp, 0x0);
    a0 = 0x780000;
    a1 = s1;
    a0 = addiu(a0, -8992);  // &0x77DCE0
    jal(ctx, 0x491A9Cu, gen::fn_sub_4C6560_004c6560);
    lw(a0, s1, 20);
    if (a0 != 0) {
        // 0x00491ab0
        charge(ctx, 2);
        jal(ctx, 0x491AB0u, gen::fn_sub_4C47E0_004c47e0);
    }
    // 0x00491ab8
    charge(ctx, 3);
    lw(a0, s1, 24);
    if (a0 != 0) {
        // 0x00491ac4
        charge(ctx, 2);
        if (a0 != 0) {
            // 0x00491acc
            charge(ctx, 2);
            jal(ctx, 0x491ACCu, gen::fn_sub_493B60_00493b60);
        }
        // 0x00491ad4
        charge(ctx, 4);
        sw(zero, s1, 24);
        lw(s0, s1, 4);
        if (s0 != 0) {
            // 0x00491ae4
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x491AE4u, gen::fn_sub_49C230_0049c230);
            if (v0 != 0) {
                // 0x00491af4
                charge(ctx, 2);
                a0 = s0;
                jal(ctx, 0x491AF4u, gen::fn_sub_4CB270_004cb270);
            }
        }
    }
    // 0x00491afc
    charge(ctx, 17);
    a0 = s1;
    jal(ctx, 0x491AFCu, gen::fn_sub_4D18C0_004d18c0);
    lw(a0, gp, -17616);  // 0x7CE820
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070
    v0 = 0x960000;
    lw(v0, v0, 396);  // 0x96018C
    v1 = addu(v1, a0);
    lw(a0, v1, 0);
    a1 = s1;
    jalr(ctx, 0x491B20u, v0.u());
    ld(ra, sp, 0x20);
    v0 = 1;
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00492D10 sub_492D10 -- 52 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [RpAtomic] [proposed: RpAtomicSetFrame] Links the frame (sub_4D1840) and marks the atomic dirty (+3 |= 1).
void sub_492D10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00492d10
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x492D1Cu, gen::fn_sub_4D1840_004d1840);
    lbu(v1, s0, 3);
    v0 = s0;
    v1 = v1 | 0x1;
    sb(v1, s0, 3);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00494CC0 sub_494CC0 -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [RpGeometry] [proposed: RpGeometryDestroy] Drops a reference (+24); the last one runs the plugin destructors, releases
// the material (sub_494D50(geometry, 0)) and frees the block (slot 0x96018C).
void sub_494CC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00494cc0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lh(v1, a0, 24);
    s0 = a0;
    if (v1 == v0) {
        // 0x00494cf0
        charge(ctx, 18);
        a0 = 0x780000;
        a1 = s0;
        a0 = addiu(a0, -8864);  // &0x77DD60
        jal(ctx, 0x494CF8u, gen::fn_sub_4C6560_004c6560);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x494D04u, gen::fn_sub_494D50_00494d50);
        lw(a0, gp, -17584);  // 0x7CE840
        v1 = 0x960000;
        v1 = addiu(v1, 112);  // &0x960070
        v0 = 0x960000;
        lw(v0, v0, 396);  // 0x96018C
        v1 = addu(v1, a0);
        lw(a0, v1, 0);
        a1 = s0;
        jalr(ctx, 0x494D28u, v0.u());
        backedge(ctx);
    } else {
        // 0x00494cdc
        charge(ctx, 3);
        lh(v0, s0, 24);
        v0 = addiu(v0, -1);
        sh(v0, s0, 24);
    }
    // 0x00494ce8
    charge(ctx, 2);
    v0 = 1;
    // 0x00494d38
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00494D50 sub_494D50 -- 88 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [RpMaterial] [proposed: RpMaterialSetTexture] Takes a reference on the new texture (+84), destroys the old one and
// stores the new one.
void sub_494D50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00494d50
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    s1 = a0;
    if (s0 != 0) {
        // 0x00494d6c
        charge(ctx, 3);
        lw(v0, s0, 84);
        v0 = addiu(v0, 1);
        sw(v0, s0, 84);
    }
    // 0x00494d78
    charge(ctx, 3);
    lw(a0, s1, 0);
    if (a0 != 0) {
        // 0x00494d84
        charge(ctx, 2);
        jal(ctx, 0x494D84u, gen::fn_sub_4D0F00_004d0f00);
    }
    // 0x00494d8c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(s0, s1, 0);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004CA030 sub_4CA030 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [RwCamera] [proposed: RwCameraDestroy] Plugin destructors (0x77E5E0), the frame unlinked (sub_4D18C0), the block back to
// its free list.
void sub_4CA030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ca030
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0x780000;
    a1 = s0;
    a0 = addiu(a0, -6688);  // &0x77E5E0
    jal(ctx, 0x4CA048u, gen::fn_sub_4C6560_004c6560);
    a0 = s0;
    jal(ctx, 0x4CA050u, gen::fn_sub_4D18C0_004d18c0);
    lw(a0, gp, -17360);  // 0x7CE920
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070
    v0 = 0x960000;
    lw(v0, v0, 396);  // 0x96018C
    v1 = addu(v1, a0);
    lw(a0, v1, 0);
    a1 = s0;
    jalr(ctx, 0x4CA074u, v0.u());
    ld(ra, sp, 0x10);
    v0 = 1;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004D0BE0 sub_4D0BE0 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [RwTexture] Reads a texture name from the stream through the slot 0x9600D8 ($a1 == 0: an empty name).
void sub_4D0BE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d0be0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (a1 == 0) {
        // 0x004d0c10
        charge(ctx, 2);
        sw(zero, s0, 0);
        v0 = s0;
    } else {
        // 0x004d0bf4
        charge(ctx, 7);
        v0 = 0x960000;
        lw(v0, v0, 216);  // 0x9600D8
        a2 = 0;
        jalr(ctx, 0x4D0BFCu, v0.u());
        if (v0 == 0) s0 = 0;
        v0 = s0;
    }
    // 0x004d0c18 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004D1840 sub_4D1840 -- 116 bytes; frame 0x10: ra sp+0x0
// [RwFrame] [proposed: frameLinkObject] Links an object (+4 frame, +8 / +12 list links) into frame $a1's object list
// (+144), unlinking it from the old one; the frame is marked dirty (sub_4CB270).
void sub_4D1840(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d1840
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, 4);
    if (v1 != 0) {
        // 0x004d188c
        charge(ctx, 7);
        lw(a2, a0, 8);
        lw(v1, a0, 12);
        sw(a2, v1, 0);
        lw(a2, a0, 12);
        lw(v1, a0, 8);
        sw(a2, v1, 4);
        backedge(ctx);
    }
    // 0x004d1854
    charge(ctx, 2);
    sw(a1, a0, 4);
    if (a1 == 0) {
        // 0x004d18a8
        charge(ctx, 1);
        ld(ra, sp, 0x0);
    } else {
        // 0x004d185c
        charge(ctx, 12);
        lw(a2, a1, 144);
        v0 = addiu(a1, 144);
        v1 = addiu(a0, 8);
        sw(a2, a0, 8);
        sw(v0, a0, 12);
        lw(v0, a1, 144);
        a0 = a1;
        sw(v1, v0, 4);
        link(ctx, 0x4D187Cu);  // $ra first: the delay slot below depends on it
        sw(v1, a1, 144);
        call(ctx, gen::fn_sub_4CB270_004cb270);
        ld(ra, sp, 0x0);
    }
    // 0x004d18ac (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x004E3E40 sub_4E3E40 -- 116 bytes; leaf frame (no stack)
// [sky VU0] [proposed: _rwSkyMatrixMultiply] VU0 macro mode: the product of two 4 x 4 matrices.
void sub_4E3E40(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Vf vf0{ctx, 0}, vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf4{ctx, 4}, vf5{ctx, 5}, vf6{ctx, 6}, vf7{ctx, 7}, vf8{ctx, 8}, vf9{ctx, 9}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12}, vf13{ctx, 13};
    // 0x004e3e40
    enter(ctx, 29);  // entry check point + this block's cycles
    lqc2(vf1, a1, 0);
    lqc2(vf2, a1, 16);
    lqc2(vf3, a1, 32);
    lqc2(vf4, a1, 48);
    lqc2(vf5, a2, 0);
    lqc2(vf6, a2, 16);
    lqc2(vf7, a2, 32);
    lqc2(vf8, a2, 48);
    lqc2(vf13, a0, 0);
    vmula_bc(0xE, vf5, vf1, 0);  // vmulax.xyz
    vmadda_bc(0xE, vf6, vf1, 1);  // vmadday.xyz
    vmadd_bc(0xE, vf9, vf7, vf1, 2);  // vmaddz.xyz
    vmula_bc(0xE, vf5, vf2, 0);  // vmulax.xyz
    vmadda_bc(0xE, vf6, vf2, 1);  // vmadday.xyz
    vmadd_bc(0xE, vf10, vf7, vf2, 2);  // vmaddz.xyz
    vmove(0x1, vf9, vf13);  // vmove.w
    vmula_bc(0xE, vf5, vf3, 0);  // vmulax.xyz
    vmadda_bc(0xE, vf6, vf3, 1);  // vmadday.xyz
    vmadd_bc(0xE, vf11, vf7, vf3, 2);  // vmaddz.xyz
    vmula_bc(0xE, vf5, vf4, 0);  // vmulax.xyz
    vmadda_bc(0xE, vf6, vf4, 1);  // vmadday.xyz
    vmadda_bc(0xE, vf7, vf4, 2);  // vmaddaz.xyz
    vmadd_bc(0xE, vf12, vf8, vf0, 3);  // vmaddw.xyz
    sqc2(vf9, a0, 0);
    sqc2(vf10, a0, 16);
    sqc2(vf11, a0, 32);
    sqc2(vf12, a0, 48);
}

// 0x004E3EC0 sub_4E3EC0 -- 96 bytes; leaf frame (no stack)
// [sky VU0] [proposed: _rwSkyV3dTransformPoints] Transforms points by a matrix (VU0 macro mode).
void sub_4E3EC0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Vf vf0{ctx, 0}, vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf4{ctx, 4}, vf5{ctx, 5};
    // 0x004e3ec0
    enter(ctx, 24);  // entry check point + this block's cycles
    lqc2(vf1, a2, 0);
    lqc2(vf2, a2, 16);
    lqc2(vf3, a2, 32);
    lqc2(vf4, a2, 48);
    lwu(v1, a1, 0);
    lwu(at, a1, 4);
    lwu(v0, a1, 8);
    at = dsll32(at, 0);
    at = at | v1;
    pcpyld(v0, v0, at);
    qmtc2(v0, vf5, false);  // qmtc2
    vmula_bc(0xE, vf1, vf5, 0);  // vmulax.xyz
    vmadda_bc(0xE, vf2, vf5, 1);  // vmadday.xyz
    vmadda_bc(0xE, vf3, vf5, 2);  // vmaddaz.xyz
    vmadd_bc(0xE, vf5, vf4, vf0, 3);  // vmaddw.xyz
    qmfc2(at, vf5, false);  // qmfc2
    v0 = dsrl32(at, 0);
    pcpyud(v1, at, at);
    sw(at, a0, 0);
    sw(v0, a0, 4);
    sw(v1, a0, 8);
    v0 = a0;
}

// 0x004E3F20 sub_4E3F20 -- 148 bytes; leaf frame (no stack)
// [sky VU0] Transforms $a2 points by a matrix (VU0 macro mode, a loop).
void sub_4E3F20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t9{ctx, 25};
    Vf vf0{ctx, 0}, vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf4{ctx, 4}, vf5{ctx, 5}, vf6{ctx, 6};
    // 0x004e3f20
    enter(ctx, 12);  // entry check point + this block's cycles
    t0 = a0;
    lqc2(vf1, a3, 0);
    lqc2(vf2, a3, 16);
    lqc2(vf3, a3, 32);
    lqc2(vf4, a3, 48);
    lwu(t5, a1, 0);
    lwu(t3, a1, 4);
    lwu(t4, a1, 8);
    t3 = dsll32(t3, 0);
    t3 = t3 | t5;
    pcpyld(t4, t4, t3);
    qmtc2(t4, vf5, false);  // qmtc2
    for (;;) {
        // 0x004e3f50
        charge(ctx, 2);
        a1 = addiu(a1, 12);
        if (i64(a2) <= 0) {
            break;
        }
        // 0x004e3f58
        charge(ctx, 20);
        vmula_bc(0xE, vf1, vf5, 0);  // vmulax.xyz
        vmadda_bc(0xE, vf2, vf5, 1);  // vmadday.xyz
        vmadda_bc(0xE, vf3, vf5, 2);  // vmaddaz.xyz
        vmadd_bc(0xE, vf6, vf4, vf0, 3);  // vmaddw.xyz
        lwu(t5, a1, 0);
        lwu(t3, a1, 4);
        lwu(t4, a1, 8);
        a2 = addiu(a2, -1);
        t3 = dsll32(t3, 0);
        t3 = t3 | t5;
        pcpyld(t4, t4, t3);
        qmtc2(t4, vf5, false);  // qmtc2
        qmfc2(t9, vf6, false);  // qmfc2
        v0 = dsrl32(t9, 0);
        pcpyud(v1, t9, t9);
        sw(t9, a0, 0);
        sw(v0, a0, 4);
        sw(v1, a0, 8);
        a0 = addiu(a0, 12);
        backedge(ctx);
    }
    // 0x004e3fa8
    charge(ctx, 3);
    v0 = t0;
}

// 0x004E3FC0 sub_4E3FC0 -- 88 bytes; leaf frame (no stack)
// [sky VU0] [proposed: _rwSkyV3dTransformVectors] Transforms vectors (no translation) by a matrix.
void sub_4E3FC0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Vf vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf4{ctx, 4};
    // 0x004e3fc0
    enter(ctx, 22);  // entry check point + this block's cycles
    lqc2(vf1, a2, 0);
    lqc2(vf2, a2, 16);
    lqc2(vf3, a2, 32);
    lwu(at, a1, 0);
    lwu(v0, a1, 4);
    lwu(v1, a1, 8);
    v0 = dsll32(v0, 0);
    v0 = v0 | at;
    pcpyld(v1, v1, v0);
    qmtc2(v1, vf4, false);  // qmtc2
    vmula_bc(0xE, vf1, vf4, 0);  // vmulax.xyz
    vmadda_bc(0xE, vf2, vf4, 1);  // vmadday.xyz
    vmadd_bc(0xE, vf4, vf3, vf4, 2);  // vmaddz.xyz
    qmfc2(at, vf4, false);  // qmfc2
    v0 = dsrl32(at, 0);
    pcpyud(v1, at, at);
    sw(at, a0, 0);
    sw(v0, a0, 4);
    sw(v1, a0, 8);
    v0 = a0;
}

// 0x004E4020 sub_4E4020 -- 140 bytes; leaf frame (no stack)
// [sky VU0] Transforms $a2 vectors by a matrix (a loop).
void sub_4E4020(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, t9{ctx, 25};
    Vf vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf5{ctx, 5}, vf6{ctx, 6};
    // 0x004e4020
    enter(ctx, 11);  // entry check point + this block's cycles
    t0 = a0;
    lqc2(vf1, a3, 0);
    lqc2(vf2, a3, 16);
    lqc2(vf3, a3, 32);
    lwu(t8, a1, 0);
    lwu(t6, a1, 4);
    lwu(t7, a1, 8);
    t6 = dsll32(t6, 0);
    t6 = t6 | t8;
    pcpyld(t7, t7, t6);
    qmtc2(t7, vf5, false);  // qmtc2
    for (;;) {
        // 0x004e404c
        charge(ctx, 2);
        a1 = addiu(a1, 12);
        if (i64(a2) <= 0) {
            break;
        }
        // 0x004e4054
        charge(ctx, 19);
        vmula_bc(0xE, vf1, vf5, 0);  // vmulax.xyz
        vmadda_bc(0xE, vf2, vf5, 1);  // vmadday.xyz
        vmadd_bc(0xE, vf6, vf3, vf5, 2);  // vmaddz.xyz
        lwu(t8, a1, 0);
        lwu(t6, a1, 4);
        lwu(t7, a1, 8);
        a2 = addiu(a2, -1);
        t6 = dsll32(t6, 0);
        t6 = t6 | t8;
        pcpyld(t7, t7, t6);
        qmtc2(t7, vf5, false);  // qmtc2
        qmfc2(t9, vf6, false);  // qmfc2
        v0 = dsrl32(t9, 0);
        pcpyud(v1, t9, t9);
        sw(t9, a0, 0);
        sw(v0, a0, 4);
        sw(v1, a0, 8);
        a0 = addiu(a0, 12);
        backedge(ctx);
    }
    // 0x004e40a0
    charge(ctx, 3);
    v0 = t0;
}

}  // namespace p3fes::game
