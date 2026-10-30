// Phase 5 slice field7, part 1 (field7_lbox.h): the debug window, list box and colour box of the 0x1A0000 band, and the
// camera debug-shape tasks' update / destroy pairs. Started from p3fes_handgen's bodies (register for register, block
// for block as the recompiled ones; game/include/p3fes/game/hg_cpu.h) and made readable on top: a role comment per
// function, named work / item offsets, structured control flow (one host flag where two states shared a block), block
// roles. Every path keeps the original's statements, charges and check points in order; tests/game/test_field7_lbox.cpp
// pairs them.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/field7_lbox.h"

namespace p3fes::recomp_gen {
void fn_geometryLock_00493370(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1A2200_001a2200(p3fes::EEContext&);
void fn_sub_1A2390_001a2390(p3fes::EEContext&);
void fn_sub_1A23D0_001a23d0(p3fes::EEContext&);
void fn_sub_1A23E0_001a23e0(p3fes::EEContext&);
void fn_sub_1A3B10_001a3b10(p3fes::EEContext&);
void fn_sub_1A3BE0_001a3be0(p3fes::EEContext&);
void fn_sub_1A3C30_001a3c30(p3fes::EEContext&);
void fn_sub_1A3F20_001a3f20(p3fes::EEContext&);
void fn_sub_1A4010_001a4010(p3fes::EEContext&);
void fn_sub_1A4050_001a4050(p3fes::EEContext&);
void fn_sub_1A4090_001a4090(p3fes::EEContext&);
void fn_sub_1A4110_001a4110(p3fes::EEContext&);
void fn_sub_1A41F0_001a41f0(p3fes::EEContext&);
void fn_sub_1A4260_001a4260(p3fes::EEContext&);
void fn_sub_1A4330_001a4330(p3fes::EEContext&);
void fn_sub_1A4380_001a4380(p3fes::EEContext&);
void fn_sub_1A44A0_001a44a0(p3fes::EEContext&);
void fn_sub_1A4660_001a4660(p3fes::EEContext&);
void fn_sub_1A46C0_001a46c0(p3fes::EEContext&);
void fn_sub_1A47E0_001a47e0(p3fes::EEContext&);
void fn_sub_1A4830_001a4830(p3fes::EEContext&);
void fn_sub_1A4B40_001a4b40(p3fes::EEContext&);
void fn_sub_1A4B70_001a4b70(p3fes::EEContext&);
void fn_sub_1A4CA0_001a4ca0(p3fes::EEContext&);
void fn_sub_1E7B10_001e7b10(p3fes::EEContext&);
void fn_sub_1E7C20_001e7c20(p3fes::EEContext&);
void fn_sub_359B40_00359b40(p3fes::EEContext&);
void fn_sub_359E50_00359e50(p3fes::EEContext&);
void fn_sub_4933D0_004933d0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace f7::lbox;

// 0x001A2200 sub_1A2200 -- 396 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A2200(parent, rect, frame_rgba, fill_rgba) [dbgKskWindowCreate]: allocates the 84-byte window work and
// creates "ksk window" (priority 4207; update sub_1A1550, destroy sub_1A2170): +4 = 1 (shown), the rect x/y/w/h (+12..+24,
// int words copied as words), the frame and fill colours (+28, +32), then a scratch buffer of (x / 8) * (y / 8) + 32 bytes
// (C division: the +7 fix-up for negatives) at +72 and +76 (its size at +68). Returns the task, or 0 without memory.
void sub_1A2200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x001a2200
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s5 = a1;
    s4 = a2;
    s3 = a3;
    s0 = 0x960000;
    s0 = addiu(s0, 388);  // &0x960184
    a0 = 1;
    a1 = kWinWorkSize;
    a2 = 0x40000;
    lw(v0, s0, 0);  // 0x960184
    jalr(ctx, 0x1A2248u, v0.u());
    s1 = v0;
    if (s1 != 0) {
        // 0x001a2268
        charge(ctx, 43);
        a0 = s2;
        a1 = 4207;
        a2 = 0x680000;
        a2 = addiu(a2, -29976);  // "ksk window"
        a3 = 0x1A0000;
        a3 = addiu(a3, 5456);  // &sub_1A1550
        t0 = 0x1A0000;
        t0 = addiu(t0, 8560);  // &sub_1A2170
        t1 = s1;
        jal(ctx, 0x1A228Cu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s2 = v0;
        v0 = 1;
        sw(v0, s1, kWinVisible);
        lwc1(f3, s5, 0);
        lwc1(f2, s5, 4);
        lwc1(f1, s5, 8);
        lwc1(f0, s5, 12);
        swc1(f3, s1, kWinRect + 0);
        swc1(f2, s1, kWinRect + 4);
        swc1(f1, s1, kWinRect + 8);
        swc1(f0, s1, kWinRect + 12);
        lbu(a1, s4, 0);
        lbu(a0, s4, 1);
        lbu(v1, s4, 2);
        lbu(v0, s4, 3);
        sb(a1, s1, kWinFrameRgba + 0);
        sb(a0, s1, kWinFrameRgba + 1);
        sb(v1, s1, kWinFrameRgba + 2);
        sb(v0, s1, kWinFrameRgba + 3);
        lbu(a1, s3, 0);
        lbu(a0, s3, 1);
        lbu(v1, s3, 2);
        lbu(v0, s3, 3);
        sb(a1, s1, kWinFillRgba + 0);
        sb(a0, s1, kWinFillRgba + 1);
        sb(v1, s1, kWinFillRgba + 2);
        sb(v0, s1, kWinFillRgba + 3);
        a2 = addiu(s1, kWinBufSize);
        lw(v0, s5, 0);
        a0 = sra(v0, 3);
        if (i64(v0) < 0) {
            // 0x001a2314
            charge(ctx, 2);
            v0 = addiu(v0, 7);
            a0 = sra(v0, 3);
        }
        // 0x001a231c
        charge(ctx, 4);
        lw(v1, s5, 4);
        v0 = sra(v1, 3);
        if (i64(v1) < 0) {
            // 0x001a232c
            charge(ctx, 2);
            v0 = addiu(v1, 7);
            v0 = sra(v0, 3);
        }
        // 0x001a2334
        charge(ctx, 12);
        mult(v0, a0, v0);
        a1 = addiu(v0, 32);
        sw(a1, a2, 0);
        s3 = addiu(s1, kWinBuf);
        a0 = 1;
        a2 = 0x40000;
        lw(v0, s0, 0);
        jalr(ctx, 0x1A2350u, v0.u());
        sw(v0, s3, 0);
        sw(v0, s1, kWinBufCur);
        v0 = s2;
    } else {
        // 0x001a225c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a2364 (the shared epilogue, written out on this path)
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

// 0x001A2390 sub_1A2390 -- 56 bytes; leaf frame (no stack)
// sub_1A2390(window task) [dbgKskWindowIsBusy]: 1 while the window animates; 0 in state 6 (open) or 8 (closed; its
// update sub_1A1550 then ends the task).
void sub_1A2390(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x001a2390
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, kTaskWork);
    lw(v1, v0, kWinState);
    v0 = 6;
    bool settled = v1 == v0;  // state 6 or 8 (the original's shared block 0x1a23b0)
    if (!settled) {
        // 0x001a23a4
        charge(ctx, 3);
        v0 = 8;
        settled = v1 == v0;
    }
    if (settled) {
        // 0x001a23b0
        charge(ctx, 3);
        v0 = 0;
    } else {
        // 0x001a23bc
        charge(ctx, 1);
        v0 = 1;
    }
    // 0x001a23c0 (the epilogue)
    charge(ctx, 2);
}

// 0x001A23D0 sub_1A23D0 -- 16 bytes; leaf frame (no stack)
// sub_1A23D0(window task, on) [dbgKskWindowSetVisible]: work +4 (the draw flag the update tests with the 2-D band).
void sub_1A23D0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001a23d0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, kTaskWork);
    sw(a1, v1, kWinVisible);
}

// 0x001A23E0 sub_1A23E0 -- 824 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A23E0(window task, rect) [dbgKskWindowSetRect]: only in state 6 (open): rewrites the window geometry from the int
// rect (copied to the frame at sp+0x60): the four 2-pixel border strips and the background quad -- four vertices of
// 12 bytes each, groups of 48 in the geometry's morph target (+92 -> +20) -- with the depth from sub_1E7C20(0xFFF0;
// 0xFFE0 for the background) set by sub_1E7B10, between geometryLock(geom, 2) and sub_4933D0 (unlock).
void sub_1A23E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x001a23e0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lwc1(f3, a1, 0);
    lwc1(f2, a1, 4);
    lwc1(f1, a1, 8);
    lwc1(f0, a1, 12);
    swc1(f3, sp, 0x60);
    swc1(f2, sp, 0x64);
    swc1(f1, sp, 0x68);
    swc1(f0, sp, 0x6C);
    lw(s3, a0, kTaskWork);
    lw(a0, s3, kWinState);
    v1 = 6;
    if (a0 == v1) {
        // 0x001a2430
        charge(ctx, 177);
        lw(v0, s3, kWinClump);
        lw(a0, v0, 24);
        a1 = 2;
        jal(ctx, 0x1A243Cu, gen::fn_geometryLock_00493370);
        lw(v0, s3, kWinClump);
        lw(v0, v0, 24);
        lw(v0, v0, 92);
        lw(s0, v0, 20);
        lw(v1, sp, 0x60);
        mtc1(v1, f0);
        cvt_s_w(f3, f0);
        swc1(f3, s0, 0);
        lw(s2, sp, 0x64);
        mtc1(s2, f0);
        cvt_s_w(f2, f0);
        swc1(f2, s0, 4);
        lw(v0, sp, 0x68);
        s1 = addu(v1, v0);
        mtc1(s1, f0);
        cvt_s_w(f1, f0);
        swc1(f1, s0, 12);
        swc1(f2, s0, 16);
        swc1(f3, s0, 24);
        v0 = addiu(s2, 2);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, s0, 28);
        swc1(f1, s0, 36);
        swc1(f0, s0, 40);
        a0 = 0xFFF0;
        jal(ctx, 0x1A24BCu, gen::fn_sub_1E7C20_001e7c20);
        a0 = s0;
        mov_s(f12, f0);
        jal(ctx, 0x1A24CCu, gen::fn_sub_1E7B10_001e7b10);
        lw(v0, s3, kWinClump);
        lw(v0, v0, 24);
        lw(v0, v0, 92);
        lw(v1, v0, 20);
        s4 = addiu(v1, 48);
        v0 = addiu(s1, -2);
        mtc1(v0, f0);
        cvt_s_w(f3, f0);
        swc1(f3, v1, 48);
        mtc1(s2, f0);
        cvt_s_w(f2, f0);
        swc1(f2, v1, 52);
        mtc1(s1, f0);
        cvt_s_w(f1, f0);
        swc1(f1, v1, 60);
        swc1(f2, v1, 64);
        swc1(f3, v1, 72);
        lw(v0, sp, 0x6C);
        s0 = addu(s2, v0);
        mtc1(s0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, v1, 76);
        swc1(f1, v1, 84);
        swc1(f0, v1, 88);
        a0 = 0xFFF0;
        jal(ctx, 0x1A2548u, gen::fn_sub_1E7C20_001e7c20);
        a0 = s4;
        mov_s(f12, f0);
        jal(ctx, 0x1A2558u, gen::fn_sub_1E7B10_001e7b10);
        lw(v0, s3, kWinClump);
        lw(v0, v0, 24);
        lw(v0, v0, 92);
        lw(v1, v0, 20);
        s4 = addiu(v1, 96);
        lwc1(f0, sp, 0x60);
        cvt_s_w(f3, f0);
        swc1(f3, v1, 96);
        v0 = addiu(s0, -2);
        mtc1(v0, f0);
        cvt_s_w(f2, f0);
        swc1(f2, v1, 100);
        mtc1(s1, f0);
        cvt_s_w(f1, f0);
        swc1(f1, v1, 108);
        swc1(f2, v1, 112);
        swc1(f3, v1, 120);
        mtc1(s0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, v1, 124);
        swc1(f1, v1, 132);
        swc1(f0, v1, 136);
        a0 = 0xFFF0;
        jal(ctx, 0x1A25C8u, gen::fn_sub_1E7C20_001e7c20);
        a0 = s4;
        mov_s(f12, f0);
        jal(ctx, 0x1A25D8u, gen::fn_sub_1E7B10_001e7b10);
        lw(v0, s3, kWinClump);
        lw(v0, v0, 24);
        lw(v0, v0, 92);
        lw(v1, v0, 20);
        s4 = addiu(v1, 144);
        lw(v0, sp, 0x60);
        mtc1(v0, f0);
        cvt_s_w(f3, f0);
        swc1(f3, v1, 144);
        mtc1(s2, f0);
        cvt_s_w(f2, f0);
        swc1(f2, v1, 148);
        v0 = addiu(v0, 2);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        swc1(f1, v1, 156);
        swc1(f2, v1, 160);
        swc1(f3, v1, 168);
        mtc1(s0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, v1, 172);
        swc1(f1, v1, 180);
        swc1(f0, v1, 184);
        a0 = 0xFFF0;
        jal(ctx, 0x1A2650u, gen::fn_sub_1E7C20_001e7c20);
        a0 = s4;
        mov_s(f12, f0);
        jal(ctx, 0x1A2660u, gen::fn_sub_1E7B10_001e7b10);
        lw(v0, s3, kWinClump);
        lw(v0, v0, 24);
        lw(v0, v0, 92);
        lw(v0, v0, 20);
        s4 = addiu(v0, 192);
        lwc1(f0, sp, 0x60);
        cvt_s_w(f3, f0);
        swc1(f3, v0, 192);
        mtc1(s2, f0);
        cvt_s_w(f2, f0);
        swc1(f2, v0, 196);
        mtc1(s1, f0);
        cvt_s_w(f1, f0);
        swc1(f1, v0, 204);
        swc1(f2, v0, 208);
        swc1(f3, v0, 216);
        mtc1(s0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, v0, 220);
        swc1(f1, v0, 228);
        swc1(f0, v0, 232);
        a0 = 0xFFE0;
        jal(ctx, 0x1A26CCu, gen::fn_sub_1E7C20_001e7c20);
        a0 = s4;
        mov_s(f12, f0);
        jal(ctx, 0x1A26DCu, gen::fn_sub_1E7B10_001e7b10);
        lw(v0, s3, kWinClump);
        lw(a0, v0, 24);
        jal(ctx, 0x1A26ECu, gen::fn_sub_4933D0_004933d0);
    }
    // 0x001a26f4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x001A3B10 sub_1A3B10 -- 208 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A3B10(parent, x, y, kind) [dbgListBoxCreate]: allocates the 68-byte list-box work and creates "ksk list box"
// (priority 4207; update sub_1A2A80, destroy sub_1A3A60): position (+16, +20), size 128 x 128 (+24, +28), 10 visible
// rows (+52), the frame style (+8; sub_1A2A80 picks the window colours by it). Returns the task, or 0 without memory.
void sub_1A3B10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a3b10
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    a0 = 1;
    a1 = kBoxWorkSize;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1A3B50u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001a3b70
        charge(ctx, 19);
        a0 = s4;
        a1 = 4207;
        a2 = 0x680000;
        a2 = addiu(a2, -29960);  // "ksk list box"
        a3 = 0x1A0000;
        a3 = addiu(a3, 10880);  // &sub_1A2A80
        t0 = 0x1A0000;
        t0 = addiu(t0, 14944);  // &sub_1A3A60
        t1 = s0;
        jal(ctx, 0x1A3B94u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        sw(s3, s0, kBoxX);
        sw(s2, s0, kBoxY);
        v1 = 128;
        sw(v1, s0, kBoxW);
        sw(v1, s0, kBoxH);
        v1 = 10;
        sw(v1, s0, kBoxRows);
        sw(s1, s0, kBoxStyle);
    } else {
        // 0x001a3b64
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a3bbc (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001A3BE0 sub_1A3BE0 -- 16 bytes; leaf frame (no stack)
// sub_1A3BE0(box task, value) [dbgListBoxSetWord4]: work +4.
void sub_1A3BE0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001a3be0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, kTaskWork);
    sw(a1, v1, kBoxWord4);
}

// 0x001A3C30 sub_1A3C30 -- 388 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A3C30(box task) [dbgListBoxLayout]: sizes the box to its items: the widest item in characters -- label length,
// + 1 + the string (kind 1), + 1 + strlen("FALSE") (kind 2, a flag), + 9 or + 11 (kind 3, an int; 11 when +536, the hex
// flag, is set), + 8 (kind 4, a float) -- gives width = 12 * chars + 4 (+24); height = 12 * min(count, visible rows) + 4
// (+28); and when the window exists (+40) its rect is updated (sub_1A23E0 with &work +16).
void sub_1A3C30(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a3c30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, kTaskWork);
    lw(s3, s0, kBoxItems);
    s2 = 0;
    for (;;) {
        // 0x001a3d24
        charge(ctx, 2);
        if (s3 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001a3c5c
        charge(ctx, 8);
        a0 = addiu(s3, kItemLabel);
        jal(ctx, 0x1A3C60u, gen::fn_strlen_00524388);
        s1 = v0;
        lw(a0, s3, kItemKind);
        v1 = 4;
        if (a0 == v1) {
            // 0x001a3d0c
            charge(ctx, 1);
            s1 = addiu(s1, 8);
        } else {
            // 0x001a3c7c
            charge(ctx, 3);
            v1 = 3;
            if (a0 == v1) {
                // 0x001a3ce8
                charge(ctx, 3);
                lw(v1, s3, kItemHex);
                if (v1 != 0) {
                    // 0x001a3d00
                    charge(ctx, 3);
                    s1 = addiu(s1, 11);
                } else {
                    // 0x001a3cf4
                    charge(ctx, 3);
                    s1 = addiu(s1, 9);
                }
            } else {
                // 0x001a3c88
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    // 0x001a3ccc
                    charge(ctx, 7);
                    a0 = addiu(gp, -27504);  // "FALSE"
                    jal(ctx, 0x1A3CD0u, gen::fn_strlen_00524388);
                    v1 = addiu(v0, 1);
                    s1 = addu(s1, v1);
                } else {
                    // 0x001a3c94
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x001a3cb0
                        charge(ctx, 7);
                        a0 = addiu(s3, kItemText);
                        jal(ctx, 0x1A3CB4u, gen::fn_strlen_00524388);
                        v1 = addiu(v0, 1);
                        s1 = addu(s1, v1);
                    } else {
                        // 0x001a3ca0
                        charge(ctx, 2);
                        if (a0 != 0) {
                            // 0x001a3ca8
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
        // 0x001a3d10
        charge(ctx, 3);
        at = sltu(s2, s1);
        if (at != 0) {
            // 0x001a3d1c
            charge(ctx, 1);
            s2 = s1;
        }
        // 0x001a3d20
        charge(ctx, 1);
        lw(s3, s3, kItemNext);
    }
    // 0x001a3d2c
    charge(ctx, 19);
    v1 = sll(s2, 1);
    v1 = addu(v1, s2);
    v1 = sll(v1, 2);
    v1 = addiu(v1, 4);
    sw(v1, s0, kBoxW);
    lw(a0, s0, kBoxCount);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    a1 = addiu(v1, 4);
    lw(a0, s0, kBoxRows);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addiu(v1, 4);
    sw(v1, s0, kBoxH);
    at = slt(a1, v1);
    if (at != 0) {
        // 0x001a3d78
        charge(ctx, 1);
        sw(a1, s0, kBoxH);
    }
    // 0x001a3d7c
    charge(ctx, 3);
    lw(a0, s0, kBoxWindow);
    if (a0 != 0) {
        // 0x001a3d88
        charge(ctx, 3);
        a1 = addiu(s0, kBoxX);
        jal(ctx, 0x1A3D8Cu, gen::fn_sub_1A23E0_001a23e0);
    }
    // 0x001a3d94 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001A3F20 sub_1A3F20 -- 240 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A3F20(box task, label) [dbgListBoxAddItem]: allocates a 556-byte item (k_lbox.c 795 asserts the allocation;
// K_Assert returns in retail, so a failed one writes through NULL), copies the label (+8), kind 0, id = the box's next id
// (+64, then incremented), walks to the list's tail -- setting the item's prev (+548) to each node on the way, so it
// ends as the last one -- appends it, counts it (+56) and re-lays the box out. Returns the new id.
void sub_1A3F20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a3f20
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s3 = a1;
    lw(s1, a0, kTaskWork);
    a0 = 1;
    a1 = kItemSize;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1A3F58u, v0.u());
    s0 = v0;
    if (s0 == 0) {
        // 0x001a3f6c
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, -29944);  // "k_lbox.c"
        a1 = 795;
        jal(ctx, 0x1A3F78u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001a3f80
    charge(ctx, 13);
    a0 = addiu(s0, kItemLabel);
    a1 = s3;
    jal(ctx, 0x1A3F88u, gen::fn_strcpy_00524270);
    sw(zero, s0, kItemKind);
    lw(v0, s1, kBoxNextId);
    sw(v0, s0, kItemId);
    lw(v0, s1, kBoxNextId);
    v0 = addiu(v0, 1);
    sw(v0, s1, kBoxNextId);
    v1 = addiu(s1, kBoxItems);
    for (;;) {
        // 0x001a3fc0
        charge(ctx, 4);
        lw(v0, v1, 0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001a3fb4
        charge(ctx, 3);
        sw(v0, s0, kItemPrev);
        lw(v0, v1, 0);
        v1 = addiu(v0, kItemNext);
    }
    // 0x001a3fd0
    charge(ctx, 16);
    sw(s0, v1, 0);
    lw(v0, s1, kBoxCount);
    v0 = addiu(v0, 1);
    sw(v0, s1, kBoxCount);
    a0 = s2;
    jal(ctx, 0x1A3FE4u, gen::fn_sub_1A3C30_001a3c30);
    lw(v0, s0, kItemId);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001A4010 sub_1A4010 -- 56 bytes; frame 0x10: ra sp+0x0
// sub_1A4010(box task, id) [dbgListBoxGetLabel]: the item's label (item + 8), or 0 when no item has that id (sub_1A4330).
void sub_1A4010(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a4010
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1A4018u, gen::fn_sub_1A4330_001a4330);
    if (v0 != 0) {
        // 0x001a4034
        charge(ctx, 1);
        v0 = addiu(v0, kItemLabel);
    } else {
        // 0x001a4028
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a4038 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A4050 sub_1A4050 -- 56 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1A4050(box task, id, value) [dbgListBoxSetItemWord540]: item +540 = value when the item exists.
void sub_1A4050(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a4050
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a2;
    jal(ctx, 0x1A4060u, gen::fn_sub_1A4330_001a4330);
    if (v0 != 0) {
        // 0x001a4070
        charge(ctx, 1);
        sw(s0, v0, kItemWord540);
    }
    // 0x001a4074 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001A4090 sub_1A4090 -- 120 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A4090(box task, id, text) [dbgListBoxSetString]: a still-plain item (kind 0) becomes a string item (kind 1); the
// text (when non-NULL) is copied to +264; the box is re-laid out. Items that already have a kind are left alone.
void sub_1A4090(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a4090
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    jal(ctx, 0x1A40A8u, gen::fn_sub_1A4330_001a4330);
    if (v0 != 0) {
        // 0x001a40b8
        charge(ctx, 3);
        lw(v1, v0, kItemKind);
        if (v1 == 0) {
            // 0x001a40c4
            charge(ctx, 4);
            v1 = 1;
            sw(v1, v0, kItemKind);
            if (s0 != 0) {
                // 0x001a40d4
                charge(ctx, 4);
                a0 = addiu(v0, kItemText);
                a1 = s0;
                jal(ctx, 0x1A40DCu, gen::fn_strcpy_00524270);
            }
            // 0x001a40e4
            charge(ctx, 3);
            a0 = s1;
            jal(ctx, 0x1A40E8u, gen::fn_sub_1A3C30_001a3c30);
        }
    }
    // 0x001a40f0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001A4110 sub_1A4110 -- 148 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A4110(box task, id, value, min, max, hex) [dbgListBoxSetInt]: a plain item becomes an int item (kind 3): value
// +520, min +528, max +532, hex flag +536; re-layout.
void sub_1A4110(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a4110
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    jal(ctx, 0x1A4140u, gen::fn_sub_1A4330_001a4330);
    if (v0 != 0) {
        // 0x001a4150
        charge(ctx, 3);
        lw(v1, v0, kItemKind);
        if (v1 == 0) {
            // 0x001a415c
            charge(ctx, 9);
            v1 = 3;
            sw(v1, v0, kItemKind);
            sw(s3, v0, kItemValue);
            sw(s2, v0, kItemMin);
            sw(s1, v0, kItemMax);
            sw(s0, v0, kItemHex);
            a0 = s4;
            jal(ctx, 0x1A4178u, gen::fn_sub_1A3C30_001a3c30);
        }
    }
    // 0x001a4180 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001A41F0 sub_1A41F0 -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A41F0(box task, id, value) [dbgListBoxSetFlag]: a plain item becomes a flag item (kind 2): value +520, range
// 0..1 (+528 = 0, +532 = 1); re-layout.
void sub_1A41F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a41f0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    jal(ctx, 0x1A4208u, gen::fn_sub_1A4330_001a4330);
    if (v0 != 0) {
        // 0x001a4218
        charge(ctx, 3);
        lw(v1, v0, kItemKind);
        if (v1 == 0) {
            // 0x001a4224
            charge(ctx, 9);
            v1 = 2;
            sw(v1, v0, kItemKind);
            sw(s0, v0, kItemValue);
            sw(zero, v0, kItemMin);
            v1 = 1;
            sw(v1, v0, kItemMax);
            a0 = s1;
            jal(ctx, 0x1A4240u, gen::fn_sub_1A3C30_001a3c30);
        }
    }
    // 0x001a4248 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001A4260 sub_1A4260 -- 144 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A4260(box task, id, value, min, max) [dbgListBoxSetFloat]: a plain item becomes a float item (kind 4): +524 =
// (float)value, min +528, max +532 (ints); re-layout.
void sub_1A4260(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x001a4260
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a2;
    s1 = a3;
    s0 = t0;
    jal(ctx, 0x1A4288u, gen::fn_sub_1A4330_001a4330);
    if (v0 != 0) {
        // 0x001a4298
        charge(ctx, 3);
        lw(v1, v0, kItemKind);
        if (v1 == 0) {
            // 0x001a42a4
            charge(ctx, 11);
            v1 = 4;
            sw(v1, v0, kItemKind);
            mtc1(s2, f0);
            cvt_s_w(f0, f0);
            swc1(f0, v0, kItemFloat);
            sw(s1, v0, kItemMin);
            sw(s0, v0, kItemMax);
            a0 = s3;
            jal(ctx, 0x1A42C8u, gen::fn_sub_1A3C30_001a3c30);
        }
    }
    // 0x001a42d0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001A4380 sub_1A4380 -- 288 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A4380(box task, id) [dbgListBoxRemoveItem]: finds the item (id -1: none; an id that is not in the list walks
// off the end through NULL, as in retail), unlinks it (prev / next at +548 / +552, the head at +60), frees it (RW free
// slot 0x96017C), uncounts it; an empty box resets head / top / cursor (+60, +44, +48); otherwise, when the count is
// below the visible rows and top + cursor >= the count, the top becomes count - 1 and the cursor 0. Re-layout.
void sub_1A4380(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a4380
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, kTaskWork);
    lw(a0, s0, kBoxItems);
    v1 = si(-1);
    if (a1 != v1) {
        for (;;) {
            // 0x001a43b8
            charge(ctx, 6);
            lw(v1, a0, kItemId);
            if (v1 == a1) {
                break;
            }
            backedge(ctx);
            // 0x001a43b4
            charge(ctx, 1);
            lw(a0, a0, kItemNext);
        }
    } else {
        // 0x001a43a8
        charge(ctx, 3);
        a0 = 0;
    }
    // 0x001a43d0
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x001a43d8
        charge(ctx, 3);
        lw(v1, a0, kItemPrev);
        if (v1 == 0) {
            // 0x001a43f4
            charge(ctx, 2);
            lw(v0, a0, kItemNext);
            sw(v0, s0, kBoxItems);
        } else {
            // 0x001a43e4
            charge(ctx, 4);
            lw(v0, a0, kItemNext);
            sw(v0, v1, kItemNext);
        }
        // 0x001a43fc
        charge(ctx, 3);
        lw(v1, a0, kItemNext);
        if (v1 != 0) {
            // 0x001a4408
            charge(ctx, 2);
            lw(v0, a0, kItemPrev);
            sw(v0, v1, kItemPrev);
        }
        // 0x001a4410
        charge(ctx, 9);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x1A4418u, v0.u());
        lw(v0, s0, kBoxCount);
        a0 = addiu(v0, -1);
        sw(a0, s0, kBoxCount);
        if (a0 != 0) {
            // 0x001a4448
            charge(ctx, 4);
            lw(v0, s0, kBoxRows);
            at = slt(a0, v0);
            if (at != 0) {
                // 0x001a4458
                charge(ctx, 6);
                lw(v1, s0, kBoxTop);
                lw(v0, s0, kBoxCursor);
                v0 = addu(v1, v0);
                v0 = slt(v0, a0);
                if (v0 == 0) {
                    // 0x001a4470
                    charge(ctx, 3);
                    v0 = addiu(a0, -1);
                    sw(v0, s0, kBoxTop);
                    sw(zero, s0, kBoxCursor);
                }
            }
        } else {
            // 0x001a4434
            charge(ctx, 5);
            sw(zero, s0, kBoxItems);
            sw(zero, s0, kBoxTop);
            sw(zero, s0, kBoxCursor);
        }
        // 0x001a447c
        charge(ctx, 3);
        a0 = s1;
        jal(ctx, 0x1A4480u, gen::fn_sub_1A3C30_001a3c30);
    }
    // 0x001a4488 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001A44A0 sub_1A44A0 -- 100 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A44A0(box task) [dbgListBoxClear]: frees every item (RW free slot), then count, top and cursor = 0 (the head
// pointer +60 is left as it was).
void sub_1A44A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a44a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, kTaskWork);
    lw(a0, s0, kBoxItems);
    for (;;) {
        // 0x001a44d8
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001a44c0
        charge(ctx, 6);
        lw(s1, a0, kItemNext);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x1A44CCu, v0.u());
        a0 = s1;
    }
    // 0x001a44e0
    charge(ctx, 9);
    sw(zero, s0, kBoxCount);
    sw(zero, s0, kBoxTop);
    sw(zero, s0, kBoxCursor);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001A4660 sub_1A4660 -- 84 bytes; frame 0x10: ra sp+0x0
// sub_1A4660(task) [K_Draw_UpdatePointTask]: the camera debug point's draw: when enabled (+0), a wire sphere of radius
// 10.0 ($f12) at work +4 in the colour at +16 (sub_359B40, save 1). Returns 0.
void sub_1A4660(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x001a4660
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, kTaskWork);
    lw(v0, v1, kDbgOn);
    if (v0 != 0) {
        // 0x001a4684
        charge(ctx, 8);
        v0 = 0x41200000;
        mtc1(v0, f12);
        a0 = addiu(v1, kDbgPos);
        a1 = addiu(v1, kDbgPointRgba);
        a2 = 1;
        jal(ctx, 0x1A4698u, gen::fn_sub_359B40_00359b40);
        v0 = 0;
    } else {
        // 0x001a4678
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a46a4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A46C0 sub_1A46C0 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1A46C0(task) [K_Draw_DestroyPointTask]: frees the work (RW free slot 0x96017C).
void sub_1A46C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a46c0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1A46D4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A47E0 sub_1A47E0 -- 72 bytes; frame 0x10: ra sp+0x0
// sub_1A47E0(task) [K_Draw_UpdateCylinderTask]: the camera controller's debug cylinder: when enabled (+0), a wire
// cylinder at work +4 with radius +16 and height +20 ($f12 / $f13) in the colour at 0x7CC1B8 (sub_359E50, save 1).
// Returns 0.
void sub_1A47E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x001a47e0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, kTaskWork);
    lw(v0, v1, kDbgOn);
    if (v0 != 0) {
        // 0x001a47f8
        charge(ctx, 7);
        a0 = addiu(v1, kDbgPos);
        lwc1(f12, v1, kDbgCylRadius);
        lwc1(f13, v1, kDbgCylHeight);
        a1 = addiu(gp, -27448);  // &0x7CC1B8
        a2 = 1;
        jal(ctx, 0x1A480Cu, gen::fn_sub_359E50_00359e50);
    }
    // 0x001a4814 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A4830 sub_1A4830 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1A4830(task) [K_Draw_DestroyCylinderTask]: frees the work (RW free slot 0x96017C).
void sub_1A4830(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a4830
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1A4844u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A4B40 sub_1A4B40 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1A4B40(task) [dbgColorBoxDestroy]: frees the "color box" work (RW free slot 0x96017C).
void sub_1A4B40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a4b40
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1A4B54u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A4B70 sub_1A4B70 -- 156 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A4B70(parent, target) [dbgColorBoxCreate]: allocates the 12-byte work and creates "color box" (priority 10;
// update sub_1A4940 -- left recompiled: it calls the stood-in list-box getters --, destroy sub_1A4B40) with +8 = target.
// Returns the task, or 0 without memory. Called by sub_3407E0 (the effect editor).
void sub_1A4B70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a4b70
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 1;
    a1 = kColorBoxWorkSize;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1A4BA0u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001a4bc0
        charge(ctx, 12);
        a0 = s2;
        a1 = 10;
        a2 = 0x680000;
        a2 = addiu(a2, -29880);  // "color box"
        a3 = 0x1A0000;
        a3 = addiu(a3, 18752);  // &sub_1A4940
        t0 = 0x1A0000;
        t0 = addiu(t0, 19264);  // &sub_1A4B40
        t1 = s0;
        jal(ctx, 0x1A4BE4u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        sw(s1, s0, kColorBoxTarget);
    } else {
        // 0x001a4bb4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a4bf0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001A4CA0 sub_1A4CA0 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1A4CA0(task) [K_Draw_DestroyShapeTask]: frees the work of the debug-shape task (update sub_1A4C10).
void sub_1A4CA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a4ca0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1A4CB4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
