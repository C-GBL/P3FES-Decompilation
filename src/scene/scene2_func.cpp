// Slice scene2 (game/include/p3fes/game/scene2.h has the records): mt_sceneFunc.c's SceneManager
// task -- the per-resource update, the scene camera and its shake, the sorted effect draw.
// p3fes_handgen bodies (register for register, block for block as the recompiled ones) with a role comment per
// function and named offsets / globals (each constant equals the literal it replaces; a script checks the bodies stay
// token-identical to the generator's output).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/scene.h"
#include "p3fes/game/scene2.h"

namespace p3fes::recomp_gen {
void fn_acos_0052e9a0(p3fes::EEContext&);
void fn_dptofp_005318a0(p3fes::EEContext&);
void fn_fptodp_00530da0(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_qsort_005225f8(p3fes::EEContext&);
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1A4580_001a4580(p3fes::EEContext&);
void fn_sub_318AD0_00318ad0(p3fes::EEContext&);
void fn_sub_318B00_00318b00(p3fes::EEContext&);
void fn_sub_319050_00319050(p3fes::EEContext&);
void fn_sub_319070_00319070(p3fes::EEContext&);
void fn_sub_34FD30_0034fd30(p3fes::EEContext&);
void fn_sub_34FD70_0034fd70(p3fes::EEContext&);
void fn_sub_34FF90_0034ff90(p3fes::EEContext&);
void fn_sub_34FFC0_0034ffc0(p3fes::EEContext&);
void fn_sub_350040_00350040(p3fes::EEContext&);
void fn_sub_358030_00358030(p3fes::EEContext&);
void fn_sub_3B55B0_003b55b0(p3fes::EEContext&);
void fn_sub_3B5D10_003b5d10(p3fes::EEContext&);
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);
void fn_sub_3B7460_003b7460(p3fes::EEContext&);
void fn_sub_3B79A0_003b79a0(p3fes::EEContext&);
void fn_sub_3B8540_003b8540(p3fes::EEContext&);
void fn_sub_3B88C0_003b88c0(p3fes::EEContext&);
void fn_sub_3B8FF0_003b8ff0(p3fes::EEContext&);
void fn_sub_3B9610_003b9610(p3fes::EEContext&);
void fn_sub_3BAA70_003baa70(p3fes::EEContext&);
void fn_sub_3BAC40_003bac40(p3fes::EEContext&);
void fn_sub_3BB010_003bb010(p3fes::EEContext&);
void fn_sub_3BB060_003bb060(p3fes::EEContext&);
void fn_sub_3BB450_003bb450(p3fes::EEContext&);
void fn_sub_3BB620_003bb620(p3fes::EEContext&);
void fn_sub_3BB7A0_003bb7a0(p3fes::EEContext&);
void fn_sub_3BB9B0_003bb9b0(p3fes::EEContext&);
void fn_sub_3BBAA0_003bbaa0(p3fes::EEContext&);
void fn_sub_3BBB90_003bbb90(p3fes::EEContext&);
void fn_sub_3BBC90_003bbc90(p3fes::EEContext&);
void fn_sub_3BBD40_003bbd40(p3fes::EEContext&);
void fn_sub_3BBED0_003bbed0(p3fes::EEContext&);
void fn_sub_3BC0E0_003bc0e0(p3fes::EEContext&);
void fn_sub_3BC220_003bc220(p3fes::EEContext&);
void fn_sub_3BC900_003bc900(p3fes::EEContext&);
void fn_sub_3BC940_003bc940(p3fes::EEContext&);
void fn_sub_3BCC80_003bcc80(p3fes::EEContext&);
void fn_sub_3BCCB0_003bccb0(p3fes::EEContext&);
void fn_sub_3BCD80_003bcd80(p3fes::EEContext&);
void fn_sub_3BCDA0_003bcda0(p3fes::EEContext&);
void fn_sub_3BCEB0_003bceb0(p3fes::EEContext&);
void fn_sub_3BD010_003bd010(p3fes::EEContext&);
void fn_sub_3BD230_003bd230(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C35D0_004c35d0(p3fes::EEContext&);
void fn_sub_4C3880_004c3880(p3fes::EEContext&);
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4CB7F0_004cb7f0(p3fes::EEContext&);
void fn_sub_4CB930_004cb930(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace scene2;

// 0x003B8540 sub_3B8540 -- 324 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_SceneFunc_DirAngle] (from, to, out_dir, out_angle) The direction from -> to (not normalised) into out_dir and its
// heading in degrees (acos of the dot of the normalised direction, y then zeroed, with the axis 0x6A2DC8, x 57.29578
// (0x7CAF18), negative when x < 0) into *out_angle: 1; a zero-length direction returns 0 and writes nothing.
void sub_3B8540(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12};
    // 0x003b8540
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a2;
    s0 = a3;
    v0 = 0x6A0000;
    ld(v1, v0, 11720);  // 0x6A2DC8
    v0 = 0x6A0000;
    lwc1(f0, v0, 11728);  // 0x6A2DD0
    sd(v1, sp, 0x30);
    swc1(f0, sp, 0x38);
    lwc1(f1, a1, 0);
    lwc1(f0, a0, 0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x50);
    lwc1(f1, a1, 4);
    lwc1(f0, a0, 4);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x54);
    lwc1(f1, a1, 8);
    lwc1(f0, a0, 8);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    a0 = addiu(sp, 0x40);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x3B85A8u, gen::fn_sub_4C69F0_004c69f0);
    mtc1(zero, f5);
    c_eq_s(f5, f0);
    if (!cond(ctx)) {
        // 0x003b85d0
        charge(ctx, 27);
        swc1(f5, sp, 0x44);
        lwc1(f4, sp, 0x48);
        lwc1(f3, sp, 0x38);
        lwc1(f2, sp, 0x40);
        lwc1(f1, sp, 0x30);
        lwc1(f0, sp, 0x34);
        mul_s(f0, f5, f0);
        adda_s(f5, f0);
        madd_s(f0, f2, f1);
        adda_s(f5, f0);
        madd_s(f12, f4, f3);
        jal(ctx, 0x3B85FCu, gen::fn_fptodp_00530da0);
        a0 = v0;
        jal(ctx, 0x3B8608u, gen::fn_acos_0052e9a0);
        a0 = v0;
        jal(ctx, 0x3B8614u, gen::fn_dptofp_005318a0);
        lwc1(f1, gp, -32216);  // 0x7CAF18
        mul_s(f2, f1, f0);
        lwc1(f1, sp, 0x40);
        mtc1(zero, f0);
        c_lt_s(f1, f0);
        if (cond(ctx)) {
            // 0x003b863c
            charge(ctx, 4);
            v0 = lui(0xBF80);
            mtc1(v0, f0);
            mul_s(f2, f2, f0);
        }
        // 0x003b864c
        charge(ctx, 8);
        swc1(f2, s0, 0);
        lwc1(f2, sp, 0x50);
        lwc1(f1, sp, 0x54);
        lwc1(f0, sp, 0x58);
        swc1(f2, s1, 0);
        swc1(f1, s1, 4);
        swc1(f0, s1, 8);
        v0 = 1;
    } else {
        // 0x003b85c4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b866c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003B88C0 sub_3B88C0 -- 296 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_SceneFunc_RequestPathMove] (res, path, loop, $f12 speed) Starts a bezier path move: flag bit 0 on, 0x40 off (on
// again when loop == 1), speed +88, kind 2, distance 0; the 304-byte path block +84 is allocated once (RwMalloc, hint
// 0x40000; asserts mt_sceneFunc.c 571) and the path copied into it; +96 = its length (sub_3BC0E0), printed ("path bezier
// max kyori = %f"). 1, or 0 for NULL.
void sub_3B88C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x003b88c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    if (s1 != 0) {
        // 0x003b88ec
        charge(ctx, 9);
        lw(v0, s1, scn::res::kFlags);
        v1 = v0 | 0x1;
        sw(v1, s1, scn::res::kFlags);
        v0 = si(-65);
        v0 = v1 & v0;
        sw(v0, s1, scn::res::kFlags);
        v0 = 1;
        if (a2 == v0) {
            // 0x003b8910
            charge(ctx, 3);
            lw(v0, s1, scn::res::kFlags);
            v0 = v0 | 0x40;
            sw(v0, s1, scn::res::kFlags);
        }
        // 0x003b891c
        charge(ctx, 7);
        swc1(f12, s1, res::kMoveSpeed);
        v0 = 2;
        sb(v0, s1, res::kMoveKind);
        sw(zero, s1, res::kMoveTime);
        lw(v0, s1, res::kPathBlock);
        if (v0 == 0) {
            // 0x003b8938
            charge(ctx, 9);
            a0 = 304;
            a1 = 0x40000;
            v0 = 0x960000;
            lw(v0, v0, g::kLoRwMalloc);  // 0x960178
            jalr(ctx, 0x3B8948u, v0.u());
            sw(v0, s1, res::kPathBlock);
            if (v0 == 0) {
                // 0x003b895c
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 11736);  // "mt_sceneFunc.c"
                a1 = 571;
                jal(ctx, 0x3B8968u, gen::fn_sub_19D3F0_0019d3f0);
            }
        }
        // 0x003b8970
        charge(ctx, 2);
        lw(a1, s1, res::kPathBlock);
        a0 = 38;
        for (;;) {
            // 0x003b8978
            charge(ctx, 9);
            lw(v1, s0, 0);
            lw(v0, s0, 4);
            s0 = addiu(s0, 8);
            a0 = addiu(a0, -1);
            sw(v1, a1, 0);
            sw(v0, a1, 4);
            a1 = addiu(a1, 8);
            if (i64(a0) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x003b899c
        charge(ctx, 13);
        lw(a0, s1, res::kPathBlock);
        jal(ctx, 0x3B89A0u, gen::fn_sub_3BC0E0_003bc0e0);
        swc1(f0, s1, res::kMoveFrames);
        mov_s(f12, f0);
        jal(ctx, 0x3B89B0u, gen::fn_fptodp_00530da0);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11760);  // "path bezier max kyori = %f \n"
        a1 = v0;
        jal(ctx, 0x3B89C4u, gen::fn_printf_005225a8);
        v0 = 1;
    } else {
        // 0x003b88e0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b89d0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003B9610 sub_3B9610 -- 5208 bytes; frame 0x100: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [MT_SceneFunc_UpdateRes] (res) The SceneManager's per-frame update of one resource: the steps this frame (flag 0x20:
// +244, taken once; else 1 while flag bit 3 is clear, 0 when set); the move (flag bit 0, kind +80: 0 at +88 per step
// until within one step -- "move idou end"; 1 timed over +96 frames, linear or eased (+81) -- "move length0 end" for 0
// frames; 2 along the path +84 (sub_3BC220), the heading taken from the path unless bit 3, looping with 0x40), the
// rotation (flag bit 2: +128 frames, eased by +125, through the shorter turn sub_3BBAA0), the angles wrapped
// (sub_3BB9B0), the scale (0x8000, +136 -> +148 over +160), the alpha fade (0x4000: effects through their EPL colour,
// objects through the model colour with the "tokushu trans" switch unless the target is 255 or +192 is 0), the type-7
// fov tween (0x400; its time base is +92, the move time -- a quirk of the original), the icon EPLs (types 1 / 3: +256 ..
// +264; type 6: +260; sub_34FD30), a queued motion (0x2000: once the model's motion slot is ready, sub_3B8FF0) and the
// footsteps (+168..+176: sub_10A4E0 with the floor's hit value). Every changed transform is applied (sub_3B7460).
void sub_3B9610(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x003b9610
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s0 = a0;
    s3 = 0;
    if (s0 != 0) {
        // 0x003b9644
        charge(ctx, 4);
        lw(v1, s0, scn::res::kFlags);
        // the steps of this frame: flag 0x20 takes +244 once (then cleared), else 1 while flag bit 3 is clear, 0 when set
        v0 = v1 & 0x20;
        if (v0 == 0) {
            // 0x003b9670
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                // 0x003b967c
                charge(ctx, 1);
                s3 = 1;
            }
        } else {
            // 0x003b9654
            charge(ctx, 7);
            lw(s3, s0, res::kPendingSteps);
            v0 = si(-33);
            v0 = v1 & v0;
            sw(v0, s0, scn::res::kFlags);
            sw(zero, s0, res::kPendingSteps);
        }
        // 0x003b9680
        charge(ctx, 2);
        if (i64(s3) < 0) {
            // 0x003b9688
            charge(ctx, 1);
            s3 = 0;
        }
        // 0x003b968c
        charge(ctx, 4);
        lw(v0, s0, scn::res::kFlags);
        // the move request (flag bit 0)
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x003b969c
            charge(ctx, 16);
            lwc1(f2, s0, scn::res::kMoveTo);
            lwc1(f1, s0, scn::res::kMoveToY);
            lwc1(f0, s0, scn::res::kMoveToZ);
            swc1(f2, sp, 0xE8);
            swc1(f1, sp, 0xEC);
            swc1(f0, sp, 0xF0);
            a0 = addiu(s0, 4);
            lwc1(f2, s0, scn::res::kPos);
            lwc1(f1, s0, scn::res::kPosY);
            lwc1(f0, s0, scn::res::kPosZ);
            swc1(f2, sp, 0xD8);
            swc1(f1, sp, 0xDC);
            swc1(f0, sp, 0xE0);
            // by kind: 0 at a speed (below), 1 timed, 2 along the bezier path
            lbu(v1, s0, res::kMoveKind);
            if (v1 != 0) {
                // 0x003b9818
                charge(ctx, 3);
                v0 = 1;
                if (v1 != v0) {
                    // 0x003b9bf4
                    charge(ctx, 3);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x003b9c00
                        charge(ctx, 12);
                        lw(a0, s0, res::kPathBlock);
                        lwc1(f12, s0, res::kMoveTime);
                        lwc1(f13, s0, res::kMoveFrames);
                        a1 = addiu(sp, 0xA8);
                        a2 = addiu(sp, 0x98);
                        jal(ctx, 0x3B9C14u, gen::fn_sub_3BC220_003bc220);
                        lwc1(f1, s0, res::kMoveFrames);
                        lwc1(f0, s0, res::kMoveTime);
                        c_lt_s(f0, f1);
                        if (!cond(ctx)) {
                            // 0x003b9c30
                            charge(ctx, 4);
                            lw(v1, s0, scn::res::kFlags);
                            v0 = v1 & 0x40;
                            if (v0 == 0) {
                                // 0x003b9c50
                                charge(ctx, 3);
                                v0 = si(-2);
                                v0 = v1 & v0;
                                sw(v0, s0, scn::res::kFlags);
                            } else {
                                // 0x003b9c40
                                charge(ctx, 4);
                                sub_s(f0, f0, f1);
                                swc1(f0, s0, res::kMoveTime);
                            }
                        }
                        // 0x003b9c5c
                        charge(ctx, 9);
                        lwc1(f2, sp, 0xA8);
                        lwc1(f1, sp, 0xAC);
                        lwc1(f0, sp, 0xB0);
                        swc1(f2, s0, scn::res::kPos);
                        swc1(f1, s0, scn::res::kPosY);
                        swc1(f0, s0, scn::res::kPosZ);
                        v1 = 0;
                        for (;;) {
                            // 0x003b9c94
                            charge(ctx, 3);
                            v0 = slt(v1, s3);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x003b9c80
                            charge(ctx, 5);
                            lwc1(f1, s0, res::kMoveSpeed);
                            lwc1(f0, s0, res::kMoveTime);
                            add_s(f0, f0, f1);
                            swc1(f0, s0, res::kMoveTime);
                            v1 = addiu(v1, 1);
                        }
                        // 0x003b9ca0
                        charge(ctx, 10);
                        a0 = s0;
                        a1 = addiu(s0, 4);
                        a2 = 0;
                        a3 = 0;
                        jal(ctx, 0x3B9CB0u, gen::fn_sub_3B7460_003b7460);
                        lw(v0, s0, scn::res::kFlags);
                        v0 = v0 & 0x8;
                        if (v0 == 0) {
                            // 0x003b9cc8
                            charge(ctx, 12);
                            a2 = addiu(s0, 16);
                            lwc1(f2, sp, 0x98);
                            lwc1(f1, sp, 0x9C);
                            lwc1(f0, sp, 0xA0);
                            swc1(f2, s0, scn::res::kRot);
                            swc1(f1, s0, scn::res::kRotY);
                            swc1(f0, s0, scn::res::kRotZ);
                            a0 = s0;
                            a1 = 0;
                            a3 = 0;
                            jal(ctx, 0x3B9CF0u, gen::fn_sub_3B7460_003b7460);
                        }
                    }
                } else {
                    // 0x003b9824
                    charge(ctx, 15);
                    lwc1(f1, s0, scn::res::kMoveFrom);
                    lwc1(f0, sp, 0xE8);
                    sub_s(f0, f0, f1);
                    swc1(f0, sp, 0xC8);
                    lwc1(f1, s0, scn::res::kMoveFromY);
                    lwc1(f0, sp, 0xEC);
                    sub_s(f0, f0, f1);
                    swc1(f0, sp, 0xCC);
                    lwc1(f1, s0, scn::res::kMoveFromZ);
                    lwc1(f0, sp, 0xF0);
                    sub_s(f0, f0, f1);
                    swc1(f0, sp, 0xD0);
                    lw(v0, s0, res::kMoveFrames);
                    if (v0 != 0) {
                        // 0x003b98a0
                        charge(ctx, 2);
                        if (i64(v0) < 0) {
                            // 0x003b98bc
                            charge(ctx, 7);
                            v1 = srl(v0, 1);
                            v0 = v0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f1, f0);
                            add_s(f1, f1, f1);
                        } else {
                            // 0x003b98a8
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                        }
                        // 0x003b98d8
                        charge(ctx, 8);
                        lwc1(f0, sp, 0xC8);
                        div_s(f0, f0, f1);
                        swc1(f0, sp, 0xC8);
                        lw(v0, s0, res::kMoveFrames);
                        if (i64(v0) < 0) {
                            // 0x003b990c
                            charge(ctx, 7);
                            v1 = srl(v0, 1);
                            v0 = v0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f1, f0);
                            add_s(f1, f1, f1);
                        } else {
                            // 0x003b98f8
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                        }
                        // 0x003b9928
                        charge(ctx, 8);
                        lwc1(f0, sp, 0xCC);
                        div_s(f0, f0, f1);
                        swc1(f0, sp, 0xCC);
                        lw(v0, s0, res::kMoveFrames);
                        if (i64(v0) < 0) {
                            // 0x003b995c
                            charge(ctx, 7);
                            v1 = srl(v0, 1);
                            v0 = v0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f1, f0);
                            add_s(f1, f1, f1);
                        } else {
                            // 0x003b9948
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                        }
                        // 0x003b9978
                        charge(ctx, 8);
                        lwc1(f0, sp, 0xD0);
                        div_s(f0, f0, f1);
                        swc1(f0, sp, 0xD0);
                        // kind 1: the per-frame delta (to - from) / frames, applied linearly (easing 0) or through the curve of +81 (1..5)
                        lbu(a0, s0, res::kMoveEase);
                        at = sltiu(a0, 6);
                        if (at != 0) {
                            // 0x003b9998
                            charge(ctx, 7);
                            v1 = 0x7C0000;
                            v1 = addiu(v1, -19664);  // &0x7BB330
                            v0 = sll(a0, 2);
                            v0 = addu(v0, v1);
                            lw(v0, v0, 0);
                            switch (v0.u()) {
                            case 0x3B99B4u:  // table[0]
                                // 0x003b99b4
                                charge(ctx, 3);
                                lw(v0, s0, res::kMoveTime);
                                if (i64(v0) < 0) {
                                    // 0x003b99d4
                                    charge(ctx, 7);
                                    v1 = srl(v0, 1);
                                    v0 = v0 & 0x1;
                                    v1 = v1 | v0;
                                    mtc1(v1, f0);
                                    cvt_s_w(f3, f0);
                                    add_s(f3, f3, f3);
                                } else {
                                    // 0x003b99c0
                                    charge(ctx, 5);
                                    mtc1(v0, f0);
                                    cvt_s_w(f3, f0);
                                }
                                // 0x003b99f0
                                charge(ctx, 10);
                                lwc1(f2, sp, 0xC8);
                                lwc1(f1, s0, scn::res::kMoveFrom);
                                mtc1(zero, f0);
                                adda_s(f0, f1);
                                madd_s(f0, f2, f3);
                                swc1(f0, s0, scn::res::kPos);
                                lw(v0, s0, res::kMoveTime);
                                if (i64(v0) < 0) {
                                    // 0x003b9a2c
                                    charge(ctx, 7);
                                    v1 = srl(v0, 1);
                                    v0 = v0 & 0x1;
                                    v1 = v1 | v0;
                                    mtc1(v1, f0);
                                    cvt_s_w(f3, f0);
                                    add_s(f3, f3, f3);
                                } else {
                                    // 0x003b9a18
                                    charge(ctx, 5);
                                    mtc1(v0, f0);
                                    cvt_s_w(f3, f0);
                                }
                                // 0x003b9a48
                                charge(ctx, 10);
                                lwc1(f2, sp, 0xCC);
                                lwc1(f1, s0, scn::res::kMoveFromY);
                                mtc1(zero, f0);
                                adda_s(f0, f1);
                                madd_s(f0, f2, f3);
                                swc1(f0, s0, scn::res::kPosY);
                                lw(v0, s0, res::kMoveTime);
                                if (i64(v0) < 0) {
                                    // 0x003b9a84
                                    charge(ctx, 7);
                                    v1 = srl(v0, 1);
                                    v0 = v0 & 0x1;
                                    v1 = v1 | v0;
                                    mtc1(v1, f0);
                                    cvt_s_w(f3, f0);
                                    add_s(f3, f3, f3);
                                } else {
                                    // 0x003b9a70
                                    charge(ctx, 5);
                                    mtc1(v0, f0);
                                    cvt_s_w(f3, f0);
                                }
                                // 0x003b9aa0
                                charge(ctx, 9);
                                lwc1(f2, sp, 0xD0);
                                lwc1(f1, s0, scn::res::kMoveFromZ);
                                mtc1(zero, f0);
                                adda_s(f0, f1);
                                madd_s(f0, f2, f3);
                                swc1(f0, s0, scn::res::kPosZ);
                                break;
                            case 0x3B9AC4u:  // table[1, 2, 3, 4, 5]
                                // 0x003b9ac4
                                charge(ctx, 3);
                                lw(v0, s0, res::kMoveFrames);
                                if (i64(v0) < 0) {
                                    // 0x003b9ae4
                                    charge(ctx, 7);
                                    v1 = srl(v0, 1);
                                    v0 = v0 & 0x1;
                                    v1 = v1 | v0;
                                    mtc1(v1, f0);
                                    cvt_s_w(f12, f0);
                                    add_s(f12, f12, f12);
                                } else {
                                    // 0x003b9ad0
                                    charge(ctx, 5);
                                    mtc1(v0, f0);
                                    cvt_s_w(f12, f0);
                                }
                                // 0x003b9b00
                                charge(ctx, 3);
                                lw(v0, s0, res::kMoveTime);
                                if (i64(v0) < 0) {
                                    // 0x003b9b20
                                    charge(ctx, 7);
                                    v1 = srl(v0, 1);
                                    v0 = v0 & 0x1;
                                    v1 = v1 | v0;
                                    mtc1(v1, f0);
                                    cvt_s_w(f13, f0);
                                    add_s(f13, f13, f13);
                                } else {
                                    // 0x003b9b0c
                                    charge(ctx, 5);
                                    mtc1(v0, f0);
                                    cvt_s_w(f13, f0);
                                }
                                // 0x003b9b3c
                                charge(ctx, 19);
                                jal(ctx, 0x3B9B3Cu, gen::fn_sub_3BBED0_003bbed0);
                                lwc1(f2, sp, 0xC8);
                                lwc1(f1, s0, scn::res::kMoveFrom);
                                mtc1(zero, f3);
                                adda_s(f3, f1);
                                madd_s(f1, f2, f0);
                                swc1(f1, s0, scn::res::kPos);
                                lwc1(f2, sp, 0xCC);
                                lwc1(f1, s0, scn::res::kMoveFromY);
                                adda_s(f3, f1);
                                madd_s(f1, f2, f0);
                                swc1(f1, s0, scn::res::kPosY);
                                lwc1(f2, sp, 0xD0);
                                lwc1(f1, s0, scn::res::kMoveFromZ);
                                adda_s(f3, f1);
                                madd_s(f0, f2, f0);
                                swc1(f0, s0, scn::res::kPosZ);
                                break;
                            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                tail(ctx, v0.u());
                                return;
                            }
                        }
                        // 0x003b9b88
                        charge(ctx, 5);
                        lw(v1, s0, res::kMoveTime);
                        lw(v0, s0, res::kMoveFrames);
                        v0 = sltu(v1, v0);
                        if (v0 != 0) {
                            // 0x003b9bcc
                            charge(ctx, 2);
                            v0 = addu(v1, s3);
                            sw(v0, s0, res::kMoveTime);
                        } else {
                            // 0x003b9b9c
                            charge(ctx, 12);
                            lwc1(f2, sp, 0xE8);
                            lwc1(f1, sp, 0xEC);
                            lwc1(f0, sp, 0xF0);
                            swc1(f2, s0, scn::res::kPos);
                            swc1(f1, s0, scn::res::kPosY);
                            swc1(f0, s0, scn::res::kPosZ);
                            lw(v1, s0, scn::res::kFlags);
                            v0 = si(-2);
                            v0 = v1 & v0;
                            sw(v0, s0, scn::res::kFlags);
                        }
                    } else {
                        // 0x003b9860
                        charge(ctx, 16);
                        lwc1(f2, sp, 0xE8);
                        lwc1(f1, sp, 0xEC);
                        lwc1(f0, sp, 0xF0);
                        swc1(f2, a0, 0);
                        swc1(f1, a0, 4);
                        swc1(f0, a0, 8);
                        lw(v1, s0, scn::res::kFlags);
                        v0 = si(-2);
                        a1 = v1 & v0;
                        sw(a1, s0, scn::res::kFlags);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, 11872);  // "move length0  end=%d\n"
                        jal(ctx, 0x3B9890u, gen::fn_printf_005225a8);
                    }
                    // 0x003b9bd4
                    charge(ctx, 8);
                    a0 = s0;
                    a1 = addiu(s0, 4);
                    a2 = 0;
                    a3 = 0;
                    jal(ctx, 0x3B9BE4u, gen::fn_sub_3B7460_003b7460);
                }
            } else {
                // 0x003b96dc
                charge(ctx, 17);
                lwc1(f1, sp, 0xE8);
                lwc1(f0, sp, 0xD8);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xC8);
                lwc1(f1, sp, 0xEC);
                lwc1(f0, sp, 0xDC);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xCC);
                lwc1(f1, sp, 0xF0);
                lwc1(f0, sp, 0xE0);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xD0);
                a0 = addiu(sp, 0xC8);
                jal(ctx, 0x3B9710u, gen::fn_sub_4C6AC0_004c6ac0);
                mov_s(f20, f0);
                s1 = s3;
                for (;;) {
                    // 0x003b9720
                    charge(ctx, 5);
                    lwc1(f0, s0, res::kMoveSpeed);
                    c_le_s(f20, f0);
                    v0 = 1;
                    if (!cond(ctx)) {
                        // 0x003b9734
                        charge(ctx, 1);
                        v0 = 0;
                    }
                    // 0x003b9738
                    charge(ctx, 3);
                    v0 = v0 ^ 0x1;
                    if (v0 == 0) {
                        goto L_003b9744_13;
                    }
                    // 0x003b9784
                    charge(ctx, 6);
                    a0 = addiu(sp, 0xB8);
                    a1 = addiu(sp, 0xC8);
                    jal(ctx, 0x3B978Cu, gen::fn_sub_4C69F0_004c69f0);
                    if (i64(s1) > 0) {
                        // 0x003b979c
                        charge(ctx, 20);
                        lwc1(f2, s0, res::kMoveSpeed);
                        lwc1(f1, sp, 0xB8);
                        lwc1(f0, s0, scn::res::kPos);
                        mtc1(zero, f3);
                        adda_s(f3, f0);
                        madd_s(f0, f1, f2);
                        swc1(f0, s0, scn::res::kPos);
                        lwc1(f2, s0, res::kMoveSpeed);
                        lwc1(f1, sp, 0xBC);
                        lwc1(f0, s0, scn::res::kPosY);
                        adda_s(f3, f0);
                        madd_s(f0, f1, f2);
                        swc1(f0, s0, scn::res::kPosY);
                        lwc1(f2, s0, res::kMoveSpeed);
                        lwc1(f1, sp, 0xC0);
                        lwc1(f0, s0, scn::res::kPosZ);
                        adda_s(f3, f0);
                        madd_s(f0, f1, f2);
                        swc1(f0, s0, scn::res::kPosZ);
                    }
                    // 0x003b97ec
                    charge(ctx, 3);
                    s1 = addiu(s1, -1);
                    if (i64(s1) > 0) {
                        backedge(ctx);
                        continue;
                    }
                    break;
                }
            L_003b97f8:
                charge(ctx, 8);
                a0 = s0;
                a1 = addiu(s0, 4);
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x3B9808u, gen::fn_sub_3B7460_003b7460);
            }
        }
        // 0x003b9cf8
        charge(ctx, 4);
        lw(v0, s0, scn::res::kFlags);
        // the rotation request (flag bit 2): 0 frames -> the target; a first frame only arms the time; then the shorter turn, linear or eased by +125
        v0 = v0 & 0x4;
        if (v0 != 0) {
            // 0x003b9d08
            charge(ctx, 3);
            lw(v0, s0, scn::res::kRotFrames);
            if (v0 != 0) {
                // 0x003b9d5c
                charge(ctx, 3);
                lw(v0, s0, scn::res::kRotTime);
                if (v0 != 0) {
                    // 0x003b9d78
                    charge(ctx, 8);
                    a0 = addiu(s0, 100);
                    a1 = addiu(s0, 112);
                    a2 = addiu(sp, 0x88);
                    jal(ctx, 0x3B9D84u, gen::fn_sub_3BBAA0_003bbaa0);
                    lw(a1, s0, scn::res::kRotFrames);
                    if (i64(a1) < 0) {
                        // 0x003b9dac
                        charge(ctx, 7);
                        v1 = srl(a1, 1);
                        v0 = a1 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x003b9d98
                        charge(ctx, 5);
                        mtc1(a1, f0);
                        cvt_s_w(f1, f0);
                    }
                    // 0x003b9dc8
                    charge(ctx, 12);
                    lwc1(f0, sp, 0x88);
                    div_s(f22, f0, f1);
                    lwc1(f0, sp, 0x8C);
                    div_s(f21, f0, f1);
                    lwc1(f0, sp, 0x90);
                    div_s(f20, f0, f1);
                    lbu(a0, s0, res::kRotEase);
                    at = sltiu(a0, 6);
                    if (at != 0) {
                        // 0x003b9df8
                        charge(ctx, 7);
                        v1 = 0x7C0000;
                        v1 = addiu(v1, -19696);  // &0x7BB310
                        v0 = sll(a0, 2);
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                        switch (v0.u()) {
                        case 0x3B9E14u:  // table[0]
                            // 0x003b9e14
                            charge(ctx, 3);
                            lw(a0, s0, scn::res::kRotTime);
                            if (i64(a0) < 0) {
                                // 0x003b9e34
                                charge(ctx, 7);
                                v1 = srl(a0, 1);
                                v0 = a0 & 0x1;
                                v1 = v1 | v0;
                                mtc1(v1, f0);
                                cvt_s_w(f2, f0);
                                add_s(f2, f2, f2);
                            } else {
                                // 0x003b9e20
                                charge(ctx, 5);
                                mtc1(a0, f0);
                                cvt_s_w(f2, f0);
                            }
                            // 0x003b9e50
                            charge(ctx, 8);
                            lwc1(f1, s0, scn::res::kRotFrom);
                            mtc1(zero, f0);
                            adda_s(f0, f1);
                            madd_s(f0, f22, f2);
                            swc1(f0, sp, 0x78);
                            if (i64(a0) < 0) {
                                // 0x003b9e84
                                charge(ctx, 7);
                                v1 = srl(a0, 1);
                                v0 = a0 & 0x1;
                                v1 = v1 | v0;
                                mtc1(v1, f0);
                                cvt_s_w(f2, f0);
                                add_s(f2, f2, f2);
                            } else {
                                // 0x003b9e70
                                charge(ctx, 5);
                                mtc1(a0, f0);
                                cvt_s_w(f2, f0);
                            }
                            // 0x003b9ea0
                            charge(ctx, 8);
                            lwc1(f1, s0, scn::res::kRotFromY);
                            mtc1(zero, f0);
                            adda_s(f0, f1);
                            madd_s(f0, f21, f2);
                            swc1(f0, sp, 0x7C);
                            if (i64(a0) < 0) {
                                // 0x003b9ed4
                                charge(ctx, 7);
                                v1 = srl(a0, 1);
                                v0 = a0 & 0x1;
                                v1 = v1 | v0;
                                mtc1(v1, f0);
                                cvt_s_w(f2, f0);
                                add_s(f2, f2, f2);
                            } else {
                                // 0x003b9ec0
                                charge(ctx, 5);
                                mtc1(a0, f0);
                                cvt_s_w(f2, f0);
                            }
                            // 0x003b9ef0
                            charge(ctx, 8);
                            lwc1(f1, s0, scn::res::kRotFromZ);
                            mtc1(zero, f0);
                            adda_s(f0, f1);
                            madd_s(f0, f20, f2);
                            swc1(f0, sp, 0x80);
                            break;
                        case 0x3B9F10u:  // table[1, 2, 3, 4, 5]
                            // 0x003b9f10
                            charge(ctx, 2);
                            if (i64(a1) < 0) {
                                // 0x003b9f2c
                                charge(ctx, 7);
                                v1 = srl(a1, 1);
                                v0 = a1 & 0x1;
                                v1 = v1 | v0;
                                mtc1(v1, f0);
                                cvt_s_w(f12, f0);
                                add_s(f12, f12, f12);
                            } else {
                                // 0x003b9f18
                                charge(ctx, 5);
                                mtc1(a1, f0);
                                cvt_s_w(f12, f0);
                            }
                            // 0x003b9f48
                            charge(ctx, 3);
                            lw(v0, s0, scn::res::kRotTime);
                            if (i64(v0) < 0) {
                                // 0x003b9f68
                                charge(ctx, 7);
                                v1 = srl(v0, 1);
                                v0 = v0 & 0x1;
                                v1 = v1 | v0;
                                mtc1(v1, f0);
                                cvt_s_w(f13, f0);
                                add_s(f13, f13, f13);
                            } else {
                                // 0x003b9f54
                                charge(ctx, 5);
                                mtc1(v0, f0);
                                cvt_s_w(f13, f0);
                            }
                            // 0x003b9f84
                            charge(ctx, 17);
                            a0 = a0 & 0xFF;
                            jal(ctx, 0x3B9F88u, gen::fn_sub_3BBED0_003bbed0);
                            lwc1(f1, s0, scn::res::kRotFrom);
                            mtc1(zero, f2);
                            adda_s(f2, f1);
                            madd_s(f1, f22, f0);
                            swc1(f1, sp, 0x78);
                            lwc1(f1, s0, scn::res::kRotFromY);
                            adda_s(f2, f1);
                            madd_s(f1, f21, f0);
                            swc1(f1, sp, 0x7C);
                            lwc1(f1, s0, scn::res::kRotFromZ);
                            adda_s(f2, f1);
                            madd_s(f0, f20, f0);
                            swc1(f0, sp, 0x80);
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v0.u());
                            return;
                        }
                    }
                    // 0x003b9fc8
                    charge(ctx, 12);
                    a0 = addiu(s0, 16);
                    lwc1(f2, sp, 0x78);
                    lwc1(f1, sp, 0x7C);
                    lwc1(f0, sp, 0x80);
                    swc1(f2, s0, scn::res::kRot);
                    swc1(f1, s0, scn::res::kRotY);
                    swc1(f0, s0, scn::res::kRotZ);
                    lw(v1, s0, scn::res::kRotTime);
                    lw(v0, s0, scn::res::kRotFrames);
                    v0 = sltu(v1, v0);
                    if (v0 != 0) {
                        // 0x003ba028
                        charge(ctx, 2);
                        v0 = addu(v1, s3);
                        sw(v0, s0, scn::res::kRotTime);
                    } else {
                        // 0x003b9ff8
                        charge(ctx, 12);
                        lwc1(f2, s0, scn::res::kRotTo);
                        lwc1(f1, s0, scn::res::kRotToY);
                        lwc1(f0, s0, scn::res::kRotToZ);
                        swc1(f2, a0, 0);
                        swc1(f1, a0, 4);
                        swc1(f0, a0, 8);
                        lw(v1, s0, scn::res::kFlags);
                        v0 = si(-5);
                        v0 = v1 & v0;
                        sw(v0, s0, scn::res::kFlags);
                    }
                    // 0x003ba030
                    charge(ctx, 2);
                    if (s3 != 0) {
                        // 0x003ba038
                        charge(ctx, 6);
                        a0 = s0;
                        a1 = 0;
                        a2 = addiu(s0, 16);
                        a3 = 0;
                        jal(ctx, 0x3BA048u, gen::fn_sub_3B7460_003b7460);
                    }
                } else {
                    // 0x003b9d68
                    charge(ctx, 4);
                    v0 = addu(v0, s3);
                    sw(v0, s0, scn::res::kRotTime);
                }
            } else {
                // 0x003b9d14
                charge(ctx, 18);
                a2 = addiu(s0, 16);
                lwc1(f2, s0, scn::res::kRotTo);
                lwc1(f1, s0, scn::res::kRotToY);
                lwc1(f0, s0, scn::res::kRotToZ);
                swc1(f2, s0, scn::res::kRot);
                swc1(f1, s0, scn::res::kRotY);
                swc1(f0, s0, scn::res::kRotZ);
                lw(v1, s0, scn::res::kFlags);
                v0 = si(-5);
                v0 = v1 & v0;
                sw(v0, s0, scn::res::kFlags);
                a0 = s0;
                a1 = 0;
                a3 = 0;
                jal(ctx, 0x3B9D4Cu, gen::fn_sub_3B7460_003b7460);
            }
        }
        // 0x003ba050
        charge(ctx, 7);
        a0 = addiu(s0, 16);
        jal(ctx, 0x3BA054u, gen::fn_sub_3BB9B0_003bb9b0);
        lw(v1, s0, scn::res::kFlags);
        // the scale tween (flag 0x8000): from + (to - from) / frames * time; 0 frames -> the target
        v1 = v1 & 0x8000;
        if (v1 != 0) {
            // 0x003ba06c
            charge(ctx, 4);
            a2 = addiu(s0, 136);
            lw(v1, s0, res::kScaleFrames);
            if (v1 != 0) {
                // 0x003ba0c8
                charge(ctx, 2);
                if (i64(v1) < 0) {
                    // 0x003ba0e4
                    charge(ctx, 7);
                    a0 = srl(v1, 1);
                    v1 = v1 & 0x1;
                    a0 = a0 | v1;
                    mtc1(a0, f0);
                    cvt_s_w(f4, f0);
                    add_s(f4, f4, f4);
                } else {
                    // 0x003ba0d0
                    charge(ctx, 5);
                    mtc1(v1, f0);
                    cvt_s_w(f4, f0);
                }
                // 0x003ba100
                charge(ctx, 10);
                lw(a1, a2, 28);
                lwc1(f3, a2, 0);
                lwc1(f0, a2, 12);
                sub_s(f0, f0, f3);
                div_s(f2, f0, f4);
                if (i64(a1) < 0) {
                    // 0x003ba13c
                    charge(ctx, 7);
                    a0 = srl(a1, 1);
                    v1 = a1 & 0x1;
                    a0 = a0 | v1;
                    mtc1(a0, f0);
                    cvt_s_w(f1, f0);
                    add_s(f1, f1, f1);
                } else {
                    // 0x003ba128
                    charge(ctx, 5);
                    mtc1(a1, f0);
                    cvt_s_w(f1, f0);
                }
                // 0x003ba158
                charge(ctx, 14);
                mtc1(zero, f0);
                adda_s(f0, f3);
                madd_s(f0, f2, f1);
                swc1(f0, sp, 0x68);
                lwc1(f3, a2, 4);
                lwc1(f0, a2, 16);
                sub_s(f0, f0, f3);
                div_s(f2, f0, f4);
                if (i64(a1) < 0) {
                    // 0x003ba1a4
                    charge(ctx, 7);
                    a0 = srl(a1, 1);
                    v1 = a1 & 0x1;
                    a0 = a0 | v1;
                    mtc1(a0, f0);
                    cvt_s_w(f1, f0);
                    add_s(f1, f1, f1);
                } else {
                    // 0x003ba190
                    charge(ctx, 5);
                    mtc1(a1, f0);
                    cvt_s_w(f1, f0);
                }
                // 0x003ba1c0
                charge(ctx, 14);
                mtc1(zero, f0);
                adda_s(f0, f3);
                madd_s(f0, f2, f1);
                swc1(f0, sp, 0x6C);
                lwc1(f3, a2, 8);
                lwc1(f0, a2, 20);
                sub_s(f0, f0, f3);
                div_s(f2, f0, f4);
                if (i64(a1) < 0) {
                    // 0x003ba20c
                    charge(ctx, 7);
                    a0 = srl(a1, 1);
                    v1 = a1 & 0x1;
                    a0 = a0 | v1;
                    mtc1(a0, f0);
                    cvt_s_w(f1, f0);
                    add_s(f1, f1, f1);
                } else {
                    // 0x003ba1f8
                    charge(ctx, 5);
                    mtc1(a1, f0);
                    cvt_s_w(f1, f0);
                }
                // 0x003ba228
                charge(ctx, 17);
                mtc1(zero, f0);
                adda_s(f0, f3);
                madd_s(f0, f2, f1);
                swc1(f0, sp, 0x70);
                a1 = addiu(s0, 28);
                lwc1(f2, sp, 0x68);
                lwc1(f1, sp, 0x6C);
                lwc1(f0, sp, 0x70);
                swc1(f2, s0, scn::res::kScale);
                swc1(f1, s0, scn::res::kScaleY);
                swc1(f0, s0, scn::res::kScaleZ);
                lw(a0, a2, 28);
                lw(v1, a2, 24);
                v1 = sltu(a0, v1);
                if (v1 != 0) {
                    // 0x003ba2a0
                    charge(ctx, 2);
                    v1 = addu(a0, s3);
                    sw(v1, a2, 28);
                } else {
                    // 0x003ba26c
                    charge(ctx, 13);
                    lwc1(f2, a2, 12);
                    lwc1(f1, a2, 16);
                    lwc1(f0, a2, 20);
                    swc1(f2, a1, 0);
                    swc1(f1, a1, 4);
                    swc1(f0, a1, 8);
                    lw(a0, s0, scn::res::kFlags);
                    v1 = lui(0xFFFF);
                    v1 = v1 | 0x7FFF;
                    v1 = a0 & v1;
                    sw(v1, s0, scn::res::kFlags);
                }
                // 0x003ba2a8
                charge(ctx, 2);
                if (s3 != 0) {
                    // 0x003ba2b0
                    charge(ctx, 6);
                    a0 = s0;
                    a1 = 0;
                    a2 = 0;
                    a3 = addiu(s0, 28);
                    jal(ctx, 0x3BA2C0u, gen::fn_sub_3B7460_003b7460);
                }
            } else {
                // 0x003ba07c
                charge(ctx, 19);
                a3 = addiu(s0, 28);
                lwc1(f2, a2, 12);
                lwc1(f1, a2, 16);
                lwc1(f0, a2, 20);
                swc1(f2, s0, scn::res::kScale);
                swc1(f1, s0, scn::res::kScaleY);
                swc1(f0, s0, scn::res::kScaleZ);
                lw(v1, s0, scn::res::kFlags);
                v0 = lui(0xFFFF);
                v0 = v0 | 0x7FFF;
                v0 = v1 & v0;
                sw(v0, s0, scn::res::kFlags);
                a0 = s0;
                a1 = 0;
                a2 = 0;
                jal(ctx, 0x3BA0B8u, gen::fn_sub_3B7460_003b7460);
            }
        }
        // 0x003ba2c8
        charge(ctx, 4);
        lw(a0, s0, scn::res::kFlags);
        // the alpha fade (flag 0x4000): this frame's alpha, then by type -- 6 the EPL colour, 3 the model colour ("tokushu trans" unless 255 or no hold)
        v1 = a0 & 0x4000;
        if (v1 != 0) {
            // 0x003ba2d8
            charge(ctx, 3);
            lw(a2, s0, scn::res::kFadeFrames);
            if (a2 != 0) {
                // 0x003ba2fc
                charge(ctx, 4);
                lw(a1, s0, scn::res::kFadeTime);
                v1 = sltu(a1, a2);
                if (v1 != 0) {
                    // 0x003ba324
                    charge(ctx, 3);
                    lbu(v1, s0, scn::res::kFadeFrom);
                    if (i64(v1) < 0) {
                        // 0x003ba344
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f0);
                        cvt_s_w(f3, f0);
                        add_s(f3, f3, f3);
                    } else {
                        // 0x003ba330
                        charge(ctx, 5);
                        mtc1(v1, f0);
                        cvt_s_w(f3, f0);
                    }
                    // 0x003ba360
                    charge(ctx, 3);
                    lbu(v1, s0, scn::res::kFadeTo);
                    if (i64(v1) < 0) {
                        // 0x003ba380
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f0);
                    } else {
                        // 0x003ba36c
                        charge(ctx, 5);
                        mtc1(v1, f0);
                        cvt_s_w(f0, f0);
                    }
                    // 0x003ba39c
                    charge(ctx, 3);
                    sub_s(f1, f0, f3);
                    if (i64(a2) < 0) {
                        // 0x003ba3bc
                        charge(ctx, 7);
                        a0 = srl(a2, 1);
                        v1 = a2 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f0);
                    } else {
                        // 0x003ba3a8
                        charge(ctx, 5);
                        mtc1(a2, f0);
                        cvt_s_w(f0, f0);
                    }
                    // 0x003ba3d8
                    charge(ctx, 8);
                    div_s(f2, f1, f0);
                    if (i64(a1) < 0) {
                        // 0x003ba40c
                        charge(ctx, 7);
                        a0 = srl(a1, 1);
                        v1 = a1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f0);
                        cvt_s_w(f1, f0);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x003ba3f8
                        charge(ctx, 5);
                        mtc1(a1, f0);
                        cvt_s_w(f1, f0);
                    }
                    // 0x003ba428
                    charge(ctx, 10);
                    mtc1(zero, f0);
                    adda_s(f0, f3);
                    madd_s(f1, f2, f1);
                    v1 = 0x4F000000;
                    mtc1(v1, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x003ba468
                        charge(ctx, 6);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(a0, f0);
                        v1 = lui(0x8000);
                        a0 = a0 | v1;
                        a0 = a0 & 0xFF;
                    } else {
                        // 0x003ba450
                        charge(ctx, 6);
                        cvt_w_s(f0, f1);
                        mfc1(a0, f0);
                        a0 = a0 & 0xFF;
                    }
                    // 0x003ba480
                    charge(ctx, 4);
                    s1 = a0 & 0xFF;
                    lw(v1, s0, scn::res::kFadeTime);
                    v1 = addu(v1, s3);
                    sw(v1, s0, scn::res::kFadeTime);
                } else {
                    // 0x003ba30c
                    charge(ctx, 6);
                    lbu(s1, s0, scn::res::kFadeTo);
                    v1 = si(-16385);
                    v1 = a0 & v1;
                    sw(v1, s0, scn::res::kFlags);
                }
            } else {
                // 0x003ba2e4
                charge(ctx, 6);
                lbu(s1, s0, scn::res::kFadeTo);
                v1 = si(-16385);
                v1 = a0 & v1;
                sw(v1, s0, scn::res::kFlags);
            }
            // 0x003ba490
            charge(ctx, 8);
            lhu(a0, s0, scn::res::kId);
            v1 = 0xF0000;
            v1 = v1 | 0xFC00;
            v1 = a0 & v1;
            a0 = sra(v1, 10);
            v1 = 6;
            if (a0 == v1) {
                // 0x003ba56c
                charge(ctx, 9);
                lw(a0, s0, eff::kEpl);
                a1 = addiu(sp, 0xF8);
                jal(ctx, 0x3BA574u, gen::fn_sub_350040_00350040);
                sb(s1, sp, 0xFB);
                lw(a0, s0, eff::kEpl);
                a1 = addiu(sp, 0xF8);
                jal(ctx, 0x3BA588u, gen::fn_sub_34FF90_0034ff90);
            } else {
                // 0x003ba4b0
                charge(ctx, 3);
                v1 = 3;
                if (a0 == v1) {
                    // 0x003ba4c4
                    charge(ctx, 16);
                    lw(a0, s0, res::kModel13);
                    jal(ctx, 0x3BA4C8u, gen::fn_sub_318B00_00318b00);
                    lbu(a1, v0, 0);
                    lbu(a0, v0, 1);
                    lbu(v1, v0, 2);
                    lbu(v0, v0, 3);
                    sb(a1, sp, 0xFC);
                    sb(a0, sp, 0xFD);
                    sb(v1, sp, 0xFE);
                    sb(v0, sp, 0xFF);
                    sb(s1, sp, 0xFF);
                    lbu(v0, sp, 0xFF);
                    at = slti(v0, 255);
                    if (at == 0) {
                        // 0x003ba548
                        charge(ctx, 3);
                        lw(a0, s0, res::kModel13);
                        jal(ctx, 0x3BA54Cu, gen::fn_sub_319070_00319070);
                    } else {
                        // 0x003ba504
                        charge(ctx, 3);
                        lb(v0, s0, res::kFadeHold);
                        if (v0 == 0) {
                            // 0x003ba534
                            charge(ctx, 5);
                            lw(a0, s0, res::kModel13);
                            jal(ctx, 0x3BA538u, gen::fn_sub_319070_00319070);
                        } else {
                            // 0x003ba510
                            charge(ctx, 9);
                            lw(a0, s0, res::kModel13);
                            jal(ctx, 0x3BA514u, gen::fn_sub_319050_00319050);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, 11904);  // "tokushu trans on\n"
                            jal(ctx, 0x3BA524u, gen::fn_printf_005225a8);
                        }
                    }
                    // 0x003ba554
                    charge(ctx, 6);
                    lw(a0, s0, res::kModel13);
                    a1 = addiu(sp, 0xFC);
                    jal(ctx, 0x3BA55Cu, gen::fn_sub_318AD0_00318ad0);
                } else {
                    // 0x003ba4bc
                    charge(ctx, 2);
                }
            }
        }
        // 0x003ba590
        charge(ctx, 4);
        lw(v1, s0, scn::res::kFlags);
        // the type-7 fov tween (flag 0x400): its time base is +92 (the move time; a quirk), its own counter +208 only ends it
        v1 = v1 & 0x400;
        if (v1 != 0) {
            // 0x003ba5a0
            charge(ctx, 8);
            lhu(a0, s0, scn::res::kId);
            v1 = 0xF0000;
            v1 = v1 | 0xFC00;
            v1 = a0 & v1;
            a0 = sra(v1, 10);
            v1 = 7;
            if (a0 == v1) {
                // 0x003ba5c8
                charge(ctx, 6);
                lw(a2, s0, res::kTweenFrames);
                lwc1(f4, s0, res::kTweenFrom);
                lwc1(f3, s0, res::kTweenTo);
                lw(a1, s0, res::kTweenTime);
                if (i64(a2) > 0) {
                    // 0x003ba5fc
                    charge(ctx, 10);
                    sub_s(f1, f3, f4);
                    mtc1(a2, f0);
                    cvt_s_w(f0, f0);
                    div_s(f2, f1, f0);
                    lw(v1, s0, res::kMoveTime);
                    if (i64(v1) < 0) {
                        // 0x003ba638
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f0);
                        cvt_s_w(f1, f0);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x003ba624
                        charge(ctx, 5);
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                    }
                    // 0x003ba654
                    charge(ctx, 8);
                    mtc1(zero, f0);
                    adda_s(f0, f4);
                    madd_s(f0, f2, f1);
                    swc1(f0, s0, res::kTypeWord);
                    v1 = slt(a1, a2);
                    if (v1 != 0) {
                        // 0x003ba690
                        charge(ctx, 3);
                        lw(v1, s0, res::kTweenTime);
                        v1 = addu(v1, s3);
                        sw(v1, s0, res::kTweenTime);
                    } else {
                        // 0x003ba674
                        charge(ctx, 7);
                        swc1(f3, s0, res::kTypeWord);
                        lw(a0, s0, scn::res::kFlags);
                        v1 = si(-1025);
                        v1 = a0 & v1;
                        sw(v1, s0, scn::res::kFlags);
                    }
                } else {
                    // 0x003ba5e0
                    charge(ctx, 7);
                    swc1(f3, s0, res::kTypeWord);
                    lw(a0, s0, scn::res::kFlags);
                    v1 = si(-1025);
                    v1 = a0 & v1;
                    sw(v1, s0, scn::res::kFlags);
                }
            } else {
                // 0x003ba5c0
                charge(ctx, 2);
            }
        }
        // 0x003ba69c
        charge(ctx, 8);
        // the EPLs that follow the resource: types 1 / 3 the three icon slots, type 6 the effect (sub_34FD30)
        lhu(a0, s0, scn::res::kId);
        v1 = 0xF0000;
        v1 = v1 | 0xFC00;
        v1 = a0 & v1;
        a0 = sra(v1, 10);
        v1 = 1;
        if (a0 != v1) {
            // 0x003ba6fc
            charge(ctx, 3);
            v1 = 3;
            if (a0 != v1) {
                // 0x003ba748
                charge(ctx, 3);
                v1 = 6;
                if (a0 == v1) {
                    // 0x003ba754
                    charge(ctx, 3);
                    lw(a0, s0, eff::kEpl);
                    if (a0 != 0) {
                        // 0x003ba760
                        charge(ctx, 2);
                        jal(ctx, 0x3BA760u, gen::fn_sub_34FD30_0034fd30);
                    }
                }
            } else {
                // 0x003ba708
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x003ba734
                    charge(ctx, 3);
                    v1 = slti(s1, 3);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003ba714
                    charge(ctx, 5);
                    v1 = sll(s1, 2);
                    v1 = addu(s0, v1);
                    lw(a0, v1, 256);
                    if (a0 != 0) {
                        // 0x003ba728
                        charge(ctx, 2);
                        jal(ctx, 0x3BA728u, gen::fn_sub_34FD30_0034fd30);
                    }
                    // 0x003ba730
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                }
                // 0x003ba740
                charge(ctx, 2);
            }
        } else {
            // 0x003ba6bc
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x003ba6e8
                charge(ctx, 3);
                v1 = slti(s1, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003ba6c8
                charge(ctx, 5);
                v1 = sll(s1, 2);
                v1 = addu(s0, v1);
                lw(a0, v1, 256);
                if (a0 != 0) {
                    // 0x003ba6dc
                    charge(ctx, 2);
                    jal(ctx, 0x3BA6DCu, gen::fn_sub_34FD30_0034fd30);
                }
                // 0x003ba6e4
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x003ba6f4
            charge(ctx, 2);
        }
        // 0x003ba768
        charge(ctx, 4);
        lw(v1, s0, scn::res::kFlags);
        // a queued motion (flag 0x2000): played (sub_3B8FF0) once the model's motion slot is ready (156-byte slots, byte +238)
        v1 = v1 & 0x2000;
        if (v1 != 0) {
            // 0x003ba778
            charge(ctx, 10);
            v1 = 0;
            a2 = 0;
            lhu(a1, s0, scn::res::kId);
            a0 = 0xF0000;
            a0 = a0 | 0xFC00;
            a0 = a1 & a0;
            a1 = sra(a0, 10);
            a0 = 3;
            if (a1 == a0) {
                // 0x003ba7e0
                charge(ctx, 2);
                v1 = addiu(s0, 272);
                lw(a2, s0, res::kModel13);
            } else {
                // 0x003ba7a0
                charge(ctx, 3);
                a0 = 2;
                if (a1 == a0) {
                    // 0x003ba7d0
                    charge(ctx, 4);
                    v1 = addiu(s0, 256);
                    lw(a2, s0, res::kModel2);
                } else {
                    // 0x003ba7ac
                    charge(ctx, 3);
                    a0 = 1;
                    if (a1 == a0) {
                        // 0x003ba7c0
                        charge(ctx, 4);
                        v1 = addiu(s0, 272);
                        lw(a2, s0, res::kModel13);
                    } else {
                        // 0x003ba7b8
                        charge(ctx, 2);
                    }
                }
            }
            // 0x003ba7e8
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x003ba7f0
                charge(ctx, 11);
                lw(a1, v1, 0);
                a0 = sll(a1, 2);
                a0 = addu(a0, a1);
                a0 = sll(a0, 3);
                a0 = subu(a0, a1);
                a0 = sll(a0, 2);
                a0 = addu(a0, a2);
                lbu(a2, a0, 238);
                a0 = 1;
                if (a2 == a0) {
                    // 0x003ba81c
                    charge(ctx, 12);
                    a0 = s0;
                    lw(a2, v1, 4);
                    lw(a3, v1, 8);
                    lw(t0, v1, 12);
                    lw(t1, v1, 16);
                    lwc1(f12, v1, 20);
                    jal(ctx, 0x3BA834u, gen::fn_sub_3B8FF0_003b8ff0);
                    lw(a0, s0, scn::res::kFlags);
                    v1 = si(-8193);
                    v1 = a0 & v1;
                    sw(v1, s0, scn::res::kFlags);
                }
            }
        }
        // 0x003ba84c
        charge(ctx, 5);
        s2 = addiu(s0, 168);
        // the footsteps (+168): 1 while moving, 2 while turning -- a step every +174 frames after the +176 delay, one last step when it ends; sub_10A4E0(0, bank +170, 1, index +169 + 4 x the floor's hit value)
        lbu(a0, s0, res::kStepMode);
        v1 = 2;
        if (a0 != v1) {
            // 0x003ba860
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                goto L_003ba87c;
            }
            // 0x003ba86c
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x003ba874
                charge(ctx, 2);
            }
            // 0x003baa3c (the shared epilogue, written out on this path)
            charge(ctx, 11);
            ld(ra, sp, 0x50);
            lq(s3, sp, 0x40);
            lq(s2, sp, 0x30);
            lq(s1, sp, 0x20);
            lq(s0, sp, 0x10);
            lwc1(f22, sp, 0x8);
            lwc1(f21, sp, 0x4);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0x100);
            return;
        }
    L_003ba87c:
        charge(ctx, 3);
        v1 = 1;
        if (a0 != v1) {
            // 0x003ba8fc
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                // 0x003ba908
                charge(ctx, 4);
                lw(v1, s0, scn::res::kFlags);
                v1 = v1 & 0x4;
                if (v1 != 0) {
                L_003ba97c:
                    charge(ctx, 2);
                    if (s3 != 0) {
                        // 0x003ba984
                        charge(ctx, 3);
                        lhu(v1, s2, 8);
                        if (i64(v1) <= 0) {
                            // 0x003ba9a0
                            charge(ctx, 3);
                            lhu(v1, s2, 4);
                            if (v1 == 0) {
                                // 0x003ba9ac
                                charge(ctx, 21);
                                a0 = addiu(s0, 4);
                                jal(ctx, 0x3BA9B0u, gen::fn_sub_3BAA70_003baa70);
                                s1 = addiu(s0, 168);
                                lbu(a1, s0, res::kStepBank);
                                lbu(v1, s0, res::kStepIndex);
                                v0 = sll(v0, 2);
                                v0 = addu(v1, v0);
                                a3 = dsll32(v0, 16);
                                a3 = dsra32(a3, 16);
                                a0 = 0;
                                a2 = 1;
                                jal(ctx, 0x3BA9DCu, gen::fn_sub_10A4E0_0010a4e0);
                                lbu(v1, s1, 1);
                                v1 = addiu(v1, 1);
                                sb(v1, s1, 1);
                                lbu(v1, s1, 1);
                                v1 = slti(v1, 4);
                                if (v1 == 0) {
                                    // 0x003baa00
                                    charge(ctx, 1);
                                    sb(zero, s1, 1);
                                }
                            }
                            // 0x003baa04
                            charge(ctx, 8);
                            lhu(v1, s2, 4);
                            v1 = addiu(v1, 1);
                            sh(v1, s2, 4);
                            lhu(a0, s2, 6);
                            lhu(v1, s2, 4);
                            v1 = slt(v1, a0);
                            if (v1 == 0) {
                                // 0x003baa24
                                charge(ctx, 2);
                                if (i64(a0) > 0) {
                                    // 0x003baa38
                                    charge(ctx, 1);
                                    sh(zero, s2, 4);
                                } else {
                                    // 0x003baa2c
                                    charge(ctx, 3);
                                    sb(zero, s2, 0);
                                }
                            }
                        } else {
                            // 0x003ba990
                            charge(ctx, 4);
                            v1 = addiu(v1, -1);
                            sh(v1, s2, 8);
                        }
                    }
                } else {
                    // 0x003ba918
                    charge(ctx, 22);
                    sb(zero, s2, 0);
                    a0 = addiu(s0, 4);
                    jal(ctx, 0x3BA920u, gen::fn_sub_3BAA70_003baa70);
                    s1 = addiu(s0, 168);
                    lbu(a1, s0, res::kStepBank);
                    lbu(v1, s0, res::kStepIndex);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    a3 = dsll32(v0, 16);
                    a3 = dsra32(a3, 16);
                    a0 = 0;
                    a2 = 1;
                    jal(ctx, 0x3BA94Cu, gen::fn_sub_10A4E0_0010a4e0);
                    lbu(v1, s1, 1);
                    v1 = addiu(v1, 1);
                    sb(v1, s1, 1);
                    lbu(v1, s1, 1);
                    v1 = slti(v1, 4);
                    if (v1 == 0) {
                        // 0x003ba970
                        charge(ctx, 3);
                        sb(zero, s1, 1);
                    }
                }
            }
        } else {
            // 0x003ba888
            charge(ctx, 4);
            lw(v1, s0, scn::res::kFlags);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                goto L_003ba97c;
            }
            // 0x003ba898
            charge(ctx, 22);
            sb(zero, s2, 0);
            a0 = addiu(s0, 4);
            jal(ctx, 0x3BA8A0u, gen::fn_sub_3BAA70_003baa70);
            s1 = addiu(s0, 168);
            lbu(a1, s0, res::kStepBank);
            lbu(v1, s0, res::kStepIndex);
            v0 = sll(v0, 2);
            v0 = addu(v1, v0);
            a3 = dsll32(v0, 16);
            a3 = dsra32(a3, 16);
            a0 = 0;
            a2 = 1;
            jal(ctx, 0x3BA8CCu, gen::fn_sub_10A4E0_0010a4e0);
            lbu(v1, s1, 1);
            v1 = addiu(v1, 1);
            sb(v1, s1, 1);
            lbu(v1, s1, 1);
            v1 = slti(v1, 4);
            if (v1 == 0) {
                // 0x003ba8f0
                charge(ctx, 3);
                sb(zero, s1, 1);
            }
        }
    }
    // 0x003baa3c (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x100);
    return;
L_003b9744_13:
    charge(ctx, 16);
    lwc1(f2, sp, 0xE8);
    lwc1(f1, sp, 0xEC);
    lwc1(f0, sp, 0xF0);
    swc1(f2, s0, scn::res::kPos);
    swc1(f1, s0, scn::res::kPosY);
    swc1(f0, s0, scn::res::kPosZ);
    lw(v1, s0, scn::res::kFlags);
    v0 = si(-2);
    a1 = v1 & v0;
    sw(a1, s0, scn::res::kFlags);
    a0 = 0x6A0000;
    a0 = addiu(a0, 11840);  // "move idou end=%d\n"
    jal(ctx, 0x3B9774u, gen::fn_printf_005225a8);
    goto L_003b97f8;
}

// 0x003BB060 sub_3BB060 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [MT_SceneFunc_SetNpcIcon] (n, icon) The icon EPL over NPC resource 0xC00 | (n & 0x3FF) (sub_3BAC40); 0 when the
// resource is missing.
void sub_3BB060(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bb060
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0xC00;
    a0 = v0 & 0xFFFF;
    jal(ctx, 0x3BB080u, gen::fn_sub_3B5D10_003b5d10);
    a0 = v0;
    if (a0 != 0) {
        // 0x003bb094
        charge(ctx, 3);
        a1 = s0 & 0xFF;
        jal(ctx, 0x3BB098u, gen::fn_sub_3BAC40_003bac40);
    }
    // 0x003bb0a0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BB620 sub_3BB620 -- 376 bytes; frame 0x110: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [MT_SceneFunc_CameraEye] (out, camera, $f12 dist) The type-7 camera's eye: from its position -- or, with a target id
// (+268) that is found, from the target's position shifted by -15 x the normalised first row of the matrix of (that
// position, the camera's angles) in x and z (sub_3B79A0, sub_4C69F0), with dist replaced by +260 -- moved back by dist
// along the view direction of the camera's angles (sub_3BB450; +z for unturned angles: out = pos - dist x (0, 0, 1)).
void sub_3BB620(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f20{ctx, 20};
    // 0x003bb620
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a0;
    s1 = a1;
    mov_s(f20, f12);
    lwc1(f2, a1, scn::res::kPos);
    lwc1(f1, a1, scn::res::kPosY);
    lwc1(f0, a1, scn::res::kPosZ);
    swc1(f2, sp, 0x100);
    swc1(f1, sp, 0x104);
    swc1(f0, sp, 0x108);
    lwc1(f2, a1, scn::res::kRot);
    lwc1(f1, a1, scn::res::kRotY);
    lwc1(f0, a1, scn::res::kRotZ);
    swc1(f2, sp, 0xF0);
    swc1(f1, sp, 0xF4);
    swc1(f0, sp, 0xF8);
    lhu(a0, a1, cam::kTarget);
    if (a0 != 0) {
        // 0x003bb67c
        charge(ctx, 4);
        jal(ctx, 0x3BB67Cu, gen::fn_sub_3B5D10_003b5d10);
        if (v0 != 0) {
            // 0x003bb68c
            charge(ctx, 15);
            lwc1(f0, v0, scn::res::kPos);
            swc1(f0, sp, 0x100);
            lwc1(f0, v0, scn::res::kPosY);
            swc1(f0, sp, 0x104);
            lwc1(f0, v0, scn::res::kPosZ);
            swc1(f0, sp, 0x108);
            lwc1(f20, s1, cam::kDist);
            a0 = addiu(sp, 0x40);
            a1 = addiu(sp, 0x100);
            a2 = addiu(sp, 0xF0);
            jal(ctx, 0x3BB6B4u, gen::fn_sub_3B79A0_003b79a0);
            a2 = addiu(sp, 0x40);
            a1 = addiu(sp, 0x80);
            a0 = 8;
            for (;;) {
                // 0x003bb6c8
                charge(ctx, 9);
                lw(v1, a2, 0);
                lw(v0, a2, 4);
                a2 = addiu(a2, 8);
                a0 = addiu(a0, -1);
                sw(v1, a1, scn::res::kId);
                sw(v0, a1, scn::res::kPos);
                a1 = addiu(a1, 8);
                if (i64(a0) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x003bb6ec
            charge(ctx, 22);
            a1 = addiu(sp, 0xD0);
            ld(v0, sp, 0x80);
            lwc1(f0, sp, 0x88);
            sd(v0, sp, 0xD0);
            swc1(f0, sp, 0xD8);
            a0 = addiu(sp, 0xC0);
            jal(ctx, 0x3BB704u, gen::fn_sub_4C69F0_004c69f0);
            v0 = 0x41700000;
            mtc1(v0, f3);
            lwc1(f1, sp, 0xC0);
            lwc1(f0, sp, 0x100);
            mtc1(zero, f2);
            adda_s(f2, f0);
            msub_s(f0, f3, f1);
            swc1(f0, sp, 0x100);
            lwc1(f1, sp, 0xC8);
            lwc1(f0, sp, 0x108);
            adda_s(f2, f0);
            msub_s(f0, f3, f1);
            swc1(f0, sp, 0x108);
        }
    }
    // 0x003bb744
    charge(ctx, 21);
    a0 = addiu(sp, 0x100);
    mov_s(f12, f20);
    lwc1(f13, sp, 0xF0);
    lwc1(f14, sp, 0xF4);
    lwc1(f15, sp, 0xF8);
    a1 = addiu(sp, 0xE0);
    jal(ctx, 0x3BB75Cu, gen::fn_sub_3BB450_003bb450);
    lwc1(f2, sp, 0xE0);
    lwc1(f1, sp, 0xE4);
    lwc1(f0, sp, 0xE8);
    swc1(f2, s0, 0);
    swc1(f1, s0, 4);
    swc1(f0, s0, 8);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x110);
}

// 0x003BB7A0 sub_3BB7A0 -- 520 bytes; frame 0xB0: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_SceneFunc_ApplyCamera] (camera) Places the main RW camera (sub_198590, its frame +4) at a type-7 resource: the eye
// (sub_3BB620) back into the record, a fresh matrix (identity, flags 0x20003) turned by the three axes 0x6A2F18 /
// 0x6A2F28 / 0x6A2F38 (sub_4C31B0, pre-concatenated) and translated to the eye, plus the shake offset (sub_3BC900) when
// the shake is on; the frame transform set (sub_4CB930 / sub_4CB7F0), the matrix freed and the camera updated
// (sub_1A4580). Nothing without a camera or frame.
void sub_3BB7A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x003bb7a0
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    jal(ctx, 0x3BB7BCu, gen::fn_sub_198590_00198590);
    s2 = v0;
    v1 = 0x6A0000;
    ld(a0, v1, 12056);  // 0x6A2F18
    v1 = 0x6A0000;
    lwc1(f0, v1, 12064);  // 0x6A2F20
    sd(a0, sp, 0x90);
    swc1(f0, sp, 0x98);
    v1 = 0x6A0000;
    ld(a0, v1, 12072);  // 0x6A2F28
    v1 = 0x6A0000;
    lwc1(f0, v1, 12080);  // 0x6A2F30
    sd(a0, sp, 0x80);
    swc1(f0, sp, 0x88);
    v1 = 0x6A0000;
    ld(a0, v1, 12088);  // 0x6A2F38
    v1 = 0x6A0000;
    lwc1(f0, v1, 12096);  // 0x6A2F40
    sd(a0, sp, 0x70);
    swc1(f0, sp, 0x78);
    lw(s1, v0, 4);
    if (s3 != 0) {
        // 0x003bb81c
        charge(ctx, 2);
        if (s2 == 0) {
            goto L_003bb82c;
        }
        // 0x003bb824
        charge(ctx, 2);
        if (s1 == 0) {
            goto L_003bb82c;
        }
        // 0x003bb834
        charge(ctx, 61);
        mtc1(zero, f12);
        a0 = addiu(sp, 0xA0);
        a1 = s3;
        // the eye back into the record, then a fresh identity matrix turned by the three axes and moved to the eye
        jal(ctx, 0x3BB840u, gen::fn_sub_3BB620_003bb620);
        lwc1(f2, sp, 0xA0);
        lwc1(f1, sp, 0xA4);
        lwc1(f0, sp, 0xA8);
        swc1(f2, s3, scn::res::kPos);
        swc1(f1, s3, scn::res::kPosY);
        swc1(f0, s3, scn::res::kPosZ);
        jal(ctx, 0x3BB860u, gen::fn_sub_4C38C0_004c38c0);
        s0 = v0;
        v1 = 0x3F800000;
        sw(v1, v0, 40);
        sw(v1, v0, 20);
        sw(v1, v0, 0);
        sw(zero, v0, 16);
        sw(zero, v0, 8);
        sw(zero, v0, 4);
        sw(zero, v0, 36);
        sw(zero, v0, 32);
        sw(zero, v0, 24);
        sw(zero, v0, 56);
        sw(zero, v0, 52);
        sw(zero, v0, 48);
        lw(a0, v0, 12);
        v1 = 0x20000;
        v1 = v1 | 0x3;
        v1 = a0 | v1;
        sw(v1, v0, 12);
        a0 = s0;
        a1 = addiu(sp, 0x90);
        lwc1(f12, s3, scn::res::kRotY);
        a2 = 1;
        jal(ctx, 0x3BB8C4u, gen::fn_sub_4C31B0_004c31b0);
        a0 = s0;
        a1 = addiu(sp, 0x80);
        lwc1(f12, s3, scn::res::kRot);
        a2 = 1;
        jal(ctx, 0x3BB8DCu, gen::fn_sub_4C31B0_004c31b0);
        a0 = s0;
        a1 = addiu(sp, 0x70);
        lwc1(f12, s3, scn::res::kRotZ);
        a2 = 1;
        jal(ctx, 0x3BB8F4u, gen::fn_sub_4C31B0_004c31b0);
        a0 = s0;
        a1 = addiu(sp, 0xA0);
        a2 = 2;
        jal(ctx, 0x3BB908u, gen::fn_sub_4C35D0_004c35d0);
        a0 = addiu(sp, 0x68);
        jal(ctx, 0x3BB914u, gen::fn_sub_3BC900_003bc900);
        a2 = 1;
        if (v0 == a2) {
            // 0x003bb928
            charge(ctx, 9);
            lwc1(f0, sp, 0x68);
            swc1(f0, sp, 0x58);
            lwc1(f0, sp, 0x6C);
            swc1(f0, sp, 0x5C);
            sw(zero, sp, 0x60);
            a0 = s0;
            a1 = addiu(sp, 0x58);
            jal(ctx, 0x3BB944u, gen::fn_sub_4C35D0_004c35d0);
        }
        // 0x003bb94c
        charge(ctx, 15);
        a0 = s1;
        jal(ctx, 0x3BB950u, gen::fn_sub_4CB930_004cb930);
        a0 = s1;
        a1 = s0;
        a2 = 0;
        jal(ctx, 0x3BB964u, gen::fn_sub_4CB7F0_004cb7f0);
        a0 = s0;
        jal(ctx, 0x3BB970u, gen::fn_sub_4C3880_004c3880);
        a0 = s2;
        lwc1(f12, s3, cam::kFov);
        jal(ctx, 0x3BB980u, gen::fn_sub_1A4580_001a4580);
        // 0x003bb988 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0xB0);
        return;
    }
L_003bb82c:
    charge(ctx, 2);
    // 0x003bb988 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x003BBB90 sub_3BBB90 -- 256 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// [MT_SceneFunc_DirToAngles] (dir, out) The heading of a direction as angles {0, a, 0} in degrees (acos of the
// normalised direction, y then zeroed, against 0x6A2F48, negative for x < 0); {0, 0, 0} for a zero-length direction.
void sub_3BBB90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12};
    // 0x003bbb90
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a2 = a0;
    s0 = a1;
    v0 = 0x6A0000;
    ld(v1, v0, 12104);  // 0x6A2F48
    v0 = 0x6A0000;
    lwc1(f0, v0, 12112);  // 0x6A2F50
    sd(v1, sp, 0x30);
    swc1(f0, sp, 0x38);
    a0 = addiu(sp, 0x20);
    a1 = a2;
    jal(ctx, 0x3BBBC4u, gen::fn_sub_4C69F0_004c69f0);
    mtc1(zero, f5);
    c_eq_s(f5, f0);
    if (!cond(ctx)) {
        // 0x003bbbf4
        charge(ctx, 27);
        swc1(f5, sp, 0x24);
        lwc1(f4, sp, 0x28);
        lwc1(f3, sp, 0x38);
        lwc1(f2, sp, 0x20);
        lwc1(f1, sp, 0x30);
        lwc1(f0, sp, 0x34);
        mul_s(f0, f5, f0);
        adda_s(f5, f0);
        madd_s(f0, f2, f1);
        adda_s(f5, f0);
        madd_s(f12, f4, f3);
        jal(ctx, 0x3BBC20u, gen::fn_fptodp_00530da0);
        a0 = v0;
        jal(ctx, 0x3BBC2Cu, gen::fn_acos_0052e9a0);
        a0 = v0;
        jal(ctx, 0x3BBC38u, gen::fn_dptofp_005318a0);
        lwc1(f1, gp, -32216);  // 0x7CAF18
        mul_s(f2, f1, f0);
        lwc1(f1, sp, 0x20);
        mtc1(zero, f0);
        c_lt_s(f1, f0);
        if (cond(ctx)) {
            // 0x003bbc60
            charge(ctx, 4);
            v1 = lui(0xBF80);
            mtc1(v1, f0);
            mul_s(f2, f2, f0);
        }
        // 0x003bbc70
        charge(ctx, 3);
        swc1(f2, s0, 4);
        sw(zero, s0, 0);
        sw(zero, s0, 8);
    } else {
        // 0x003bbbe0
        charge(ctx, 5);
        swc1(f5, s0, 0);
        swc1(f5, s0, 4);
        swc1(f5, s0, 8);
    }
    // 0x003bbc7c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003BBED0 sub_3BBED0 -- 256 bytes; frame 0x170: ra sp+0x20, s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [MT_SceneFunc_Ease] (curve, $f12 t) The eased parameter of curve row `curve` (< 6; asserts mt_sceneFunc.c 2432): a
// one-segment path through (0, c0), (c1, c2), (c3, 1) .. built on the stack from the four values of sub_3B55B0(curve),
// evaluated at t (sub_3BBD40); the result's y in $f0.
void sub_3BBED0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21};
    // 0x003bbed0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x170);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s0 = a0;
    mov_s(f21, f12);
    mov_s(f20, f13);
    v0 = sltiu(s0, 6);
    if (v0 == 0) {
        // 0x003bbefc
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11736);  // "mt_sceneFunc.c"
        a1 = 2432;
        jal(ctx, 0x3BBF08u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003bbf10
    charge(ctx, 5);
    mtc1(zero, f0);
    c_eq_s(f0, f21);
    if (!cond(ctx)) {
        // 0x003bbf34
        charge(ctx, 3);
        div_s(f20, f20, f21);
    } else {
        // 0x003bbf24
        charge(ctx, 4);
        v0 = 0x3F800000;
        mtc1(v0, f20);
    }
    // 0x003bbf40
    charge(ctx, 36);
    v0 = 1;
    sb(v0, sp, 0x30);
    sw(zero, sp, 0x34);
    sw(zero, sp, 0x38);
    sw(zero, sp, 0x3C);
    a0 = s0;
    jal(ctx, 0x3BBF58u, gen::fn_sub_3B55B0_003b55b0);
    lwc1(f0, v0, 0);
    swc1(f0, sp, 0x40);
    lwc1(f0, v0, 8);
    swc1(f0, sp, 0x44);
    sw(zero, sp, 0x48);
    lwc1(f0, v0, 4);
    swc1(f0, sp, 0x4C);
    lwc1(f0, v0, 12);
    swc1(f0, sp, 0x50);
    sw(zero, sp, 0x54);
    v0 = 0x3F800000;
    sw(v0, sp, 0x58);
    sw(v0, sp, 0x5C);
    sw(zero, sp, 0x60);
    a0 = addiu(sp, 0x30);
    mov_s(f12, f20);
    a1 = addiu(sp, 0x160);
    jal(ctx, 0x3BBFA4u, gen::fn_sub_3BBD40_003bbd40);
    lwc1(f0, sp, 0x164);
    mul_s(f0, f0, f21);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x170);
}

// 0x003BC220 sub_3BC220 -- 1292 bytes; frame 0x170: ra sp+0x70, s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [MT_SceneFunc_PathAt] (path, out_pos, out_angles, $f12 dist, $f13 length) The point at distance `dist` along a bezier
// path (20 chords per segment, the chord interpolated) and its heading (sub_3BBB90 of the local direction) into
// out_angles; dist >= length gives the last point with the last chord's heading (and returns 1.0).
void sub_3BC220(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24};
    // 0x003bc220
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x170);
    sd(ra, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    mov_s(f24, f12);
    s3 = a1;
    s2 = a2;
    mtc1(zero, f23);
    lb(v1, a0, 0);
    v0 = 0x3F800000;
    mtc1(v0, f1);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    div_s(f1, f1, f0);
    v0 = 0x41A00000;
    mtc1(v0, f0);
    div_s(f21, f1, f0);
    mov_s(f20, f23);
    c_le_s(f13, f24);
    if (!cond(ctx)) {
        // 0x003bc420
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x003bc6e0
            charge(ctx, 4);
            lb(v0, s4, 0);
            v0 = slt(s1, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003bc42c
            charge(ctx, 5);
            a1 = 0;
            v0 = sll(s1, 1);
            a0 = addu(v0, s1);
            for (;;) {
                // 0x003bc478
                charge(ctx, 3);
                v0 = slti(a1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003bc440
                charge(ctx, 14);
                v1 = addu(a1, a0);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                v1 = addu(s4, v0);
                v0 = sll(a1, 2);
                lwc1(f0, v1, 4);
                v0 = addu(v0, sp);
                swc1(f0, v0, 160);
                lwc1(f0, v1, 8);
                swc1(f0, v0, 144);
                lwc1(f0, v1, 12);
                swc1(f0, v0, 128);
                a1 = addiu(a1, 1);
            }
            // 0x003bc484
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x003bc6d0
                charge(ctx, 3);
                v0 = slti(s0, 20);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003bc490
                charge(ctx, 56);
                mtc1(s0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, gp, -32660);  // 0x7CAD5C
                mul_s(f22, f1, f0);
                mov_s(f12, f22);
                a0 = addiu(sp, 0xA0);
                a1 = addiu(sp, 0x90);
                a2 = addiu(sp, 0x80);
                a3 = addiu(sp, 0x154);
                t0 = addiu(sp, 0x14C);
                t1 = addiu(sp, 0x144);
                jal(ctx, 0x3BC4C0u, gen::fn_sub_3BBC90_003bbc90);
                v0 = addiu(s0, 1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, gp, -32660);  // 0x7CAD5C
                mul_s(f12, f1, f0);
                a0 = addiu(sp, 0xA0);
                a1 = addiu(sp, 0x90);
                a2 = addiu(sp, 0x80);
                a3 = addiu(sp, 0x150);
                t0 = addiu(sp, 0x148);
                t1 = addiu(sp, 0x140);
                jal(ctx, 0x3BC4F8u, gen::fn_sub_3BBC90_003bbc90);
                lwc1(f1, sp, 0x150);
                lwc1(f0, sp, 0x154);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xC8);
                lwc1(f1, sp, 0x148);
                lwc1(f0, sp, 0x14C);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xCC);
                lwc1(f1, sp, 0x140);
                lwc1(f0, sp, 0x144);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xD0);
                a0 = addiu(sp, 0xC8);
                jal(ctx, 0x3BC534u, gen::fn_sub_4C6AC0_004c6ac0);
                lwc1(f9, sp, 0x154);
                lwc1(f8, sp, 0x14C);
                lwc1(f7, sp, 0x144);
                lwc1(f2, sp, 0x150);
                swc1(f2, sp, 0x118);
                lwc1(f6, sp, 0x148);
                swc1(f6, sp, 0x11C);
                lwc1(f5, sp, 0x140);
                swc1(f5, sp, 0x120);
                add_s(f23, f23, f0);
                c_lt_s(f23, f24);
                if (!cond(ctx)) {
                    goto L_003bc570_11;
                }
                // 0x003bc6c8
                charge(ctx, 2);
                add_s(f20, f20, f21);
                s0 = addiu(s0, 1);
            }
            // 0x003bc6dc
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
        // 0x003bc6f0
        charge(ctx, 1);
        mtc1(zero, f0);
    } else {
        // 0x003bc2a4
        charge(ctx, 12);
        v0 = dsll32(v1, 24);
        v0 = dsra32(v0, 24);
        v1 = addiu(v0, -1);
        v0 = sll(v1, 1);
        v1 = addu(v0, v1);
        a1 = 0;
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        a0 = addu(s4, v0);
        for (;;) {
            // 0x003bc308
            charge(ctx, 3);
            v0 = slti(a1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003bc2d4
            charge(ctx, 13);
            v0 = sll(a1, 1);
            v0 = addu(v0, a1);
            v0 = sll(v0, 2);
            v1 = addu(a0, v0);
            v0 = sll(a1, 2);
            lwc1(f0, v1, 4);
            v0 = addu(v0, sp);
            swc1(f0, v0, 160);
            lwc1(f0, v1, 8);
            swc1(f0, v0, 144);
            lwc1(f0, v1, 12);
            swc1(f0, v0, 128);
            a1 = addiu(a1, 1);
        }
        // 0x003bc314
        charge(ctx, 67);
        lwc1(f12, gp, -32332);  // 0x7CAEA4
        a0 = addiu(sp, 0xA0);
        a1 = addiu(sp, 0x90);
        a2 = addiu(sp, 0x80);
        a3 = addiu(sp, 0x16C);
        t0 = addiu(sp, 0x164);
        t1 = addiu(sp, 0x15C);
        jal(ctx, 0x3BC330u, gen::fn_sub_3BBC90_003bbc90);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        a0 = addiu(sp, 0xA0);
        a1 = addiu(sp, 0x90);
        a2 = addiu(sp, 0x80);
        a3 = addiu(sp, 0x168);
        t0 = addiu(sp, 0x160);
        t1 = addiu(sp, 0x158);
        jal(ctx, 0x3BC358u, gen::fn_sub_3BBC90_003bbc90);
        lwc1(f1, sp, 0x168);
        lwc1(f0, sp, 0x16C);
        sub_s(f0, f1, f0);
        swc1(f0, sp, 0xD8);
        lwc1(f1, sp, 0x160);
        lwc1(f0, sp, 0x164);
        sub_s(f0, f1, f0);
        swc1(f0, sp, 0xDC);
        lwc1(f1, sp, 0x158);
        lwc1(f0, sp, 0x15C);
        sub_s(f0, f1, f0);
        swc1(f0, sp, 0xE0);
        a0 = addiu(sp, 0xD8);
        jal(ctx, 0x3BC394u, gen::fn_sub_4C6AC0_004c6ac0);
        lwc1(f5, sp, 0x168);
        swc1(f5, sp, 0x118);
        lwc1(f4, sp, 0x160);
        swc1(f4, sp, 0x11C);
        lwc1(f3, sp, 0x158);
        swc1(f3, sp, 0x120);
        lwc1(f2, sp, 0x118);
        lwc1(f1, sp, 0x11C);
        lwc1(f0, sp, 0x120);
        swc1(f2, s3, 0);
        swc1(f1, s3, 4);
        swc1(f0, s3, 8);
        lwc1(f0, sp, 0x16C);
        sub_s(f0, f5, f0);
        swc1(f0, sp, 0x108);
        lwc1(f0, sp, 0x164);
        sub_s(f0, f4, f0);
        swc1(f0, sp, 0x10C);
        lwc1(f0, sp, 0x15C);
        sub_s(f0, f3, f0);
        swc1(f0, sp, 0x110);
        a0 = addiu(sp, 0xE8);
        a1 = addiu(sp, 0x108);
        jal(ctx, 0x3BC3F8u, gen::fn_sub_4C69F0_004c69f0);
        a0 = addiu(sp, 0xE8);
        a1 = s2;
        jal(ctx, 0x3BC408u, gen::fn_sub_3BBB90_003bbb90);
        v0 = 0x3F800000;
        mtc1(v0, f0);
    }
    // 0x003bc6f4 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    ld(ra, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x170);
    return;
L_003bc570_11:
    charge(ctx, 86);
    sub_s(f1, f23, f24);
    div_s(f1, f1, f0);
    v0 = 0x3F800000;
    mtc1(v0, f0);
    sub_s(f4, f0, f1);
    mul_s(f3, f21, f4);
    add_s(f20, f20, f3);
    sub_s(f2, f2, f9);
    swc1(f2, sp, 0x108);
    sub_s(f0, f6, f8);
    swc1(f0, sp, 0x10C);
    sub_s(f0, f5, f7);
    swc1(f0, sp, 0x110);
    mtc1(zero, f1);
    adda_s(f1, f9);
    madd_s(f0, f2, f4);
    swc1(f0, s3, 0);
    lwc1(f0, sp, 0x10C);
    adda_s(f1, f8);
    madd_s(f0, f0, f4);
    swc1(f0, s3, 4);
    lwc1(f0, sp, 0x110);
    adda_s(f1, f7);
    madd_s(f0, f0, f4);
    swc1(f0, s3, 8);
    add_s(f21, f22, f3);
    mov_s(f12, f21);
    a0 = addiu(sp, 0xA0);
    a1 = addiu(sp, 0x90);
    a2 = addiu(sp, 0x80);
    a3 = addiu(sp, 0x13C);
    t0 = addiu(sp, 0x134);
    t1 = addiu(sp, 0x12C);
    jal(ctx, 0x3BC600u, gen::fn_sub_3BBC90_003bbc90);
    lwc1(f0, gp, -32212);  // 0x7CAF1C
    sub_s(f12, f21, f0);
    a0 = addiu(sp, 0xA0);
    a1 = addiu(sp, 0x90);
    a2 = addiu(sp, 0x80);
    a3 = addiu(sp, 0x138);
    t0 = addiu(sp, 0x130);
    t1 = addiu(sp, 0x128);
    jal(ctx, 0x3BC628u, gen::fn_sub_3BBC90_003bbc90);
    lwc1(f1, sp, 0x138);
    lwc1(f0, sp, 0x13C);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xB8);
    lwc1(f1, sp, 0x130);
    lwc1(f0, sp, 0x134);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xBC);
    lwc1(f1, sp, 0x128);
    lwc1(f0, sp, 0x12C);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xC0);
    a0 = addiu(sp, 0xB8);
    jal(ctx, 0x3BC664u, gen::fn_sub_4C6AC0_004c6ac0);
    lwc1(f1, sp, 0x13C);
    lwc1(f0, sp, 0x138);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xF8);
    lwc1(f1, sp, 0x134);
    lwc1(f0, sp, 0x130);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xFC);
    lwc1(f1, sp, 0x12C);
    lwc1(f0, sp, 0x128);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x100);
    a0 = addiu(sp, 0xE8);
    a1 = addiu(sp, 0xF8);
    jal(ctx, 0x3BC6A4u, gen::fn_sub_4C69F0_004c69f0);
    a0 = addiu(sp, 0xE8);
    a1 = s2;
    jal(ctx, 0x3BC6B4u, gen::fn_sub_3BBB90_003bbb90);
    mov_s(f0, f20);
    // 0x003bc6f4 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    ld(ra, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x170);
}

// 0x003BC940 sub_3BC940 -- 688 bytes; frame 0x50: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [MT_SceneFunc_UpdateShake] The camera shake, once a frame: off -> the offset words 0x95AFF0..0x95AFFC cleared; on with
// no frames left -> switched off; else each axis with an amplitude a wanders randomly (sub_358030) inside +-a * band
// (0x7CD560 / 0x7CD564) or drifts back towards 0 by 0.5 a (1 + r), clamped to +-a; then both amplitudes lose 1 /
// (frames + 5) and the frames count down.
void sub_3BC940(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f20{ctx, 20}, f21{ctx, 21};
    // 0x003bc940
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lwc1(f1, gp, g::kGpShakeRateX);  // 0x7CD560
    lwc1(f0, gp, g::kGpShakeRateZ);  // 0x7CD564
    swc1(f1, sp, 0x40);
    swc1(f0, sp, 0x44);
    // off: the offset words are cleared; on without frames: switched off
    lhu(v1, gp, g::kGpShakeOn);  // 0x7CE658
    if (v1 != 0) {
        // 0x003bc99c
        charge(ctx, 3);
        lh(v1, gp, g::kGpShakeFrames);  // 0x7CE65C
        if (v1 != 0) {
            // 0x003bc9b4
            charge(ctx, 3);
            lhu(v1, gp, g::kGpShakeAmpX);  // 0x7CE660
            if (i64(v1) < 0) {
                // 0x003bc9d4
                charge(ctx, 7);
                a0 = srl(v1, 1);
                v1 = v1 & 0x1;
                a0 = a0 | v1;
                mtc1(a0, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x003bc9c0
                charge(ctx, 5);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
            }
            // 0x003bc9f0
            charge(ctx, 6);
            lwc1(f0, gp, g::kGpShakeScale);  // 0x7CADA0
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0x48);
            lhu(v1, gp, g::kGpShakeAmpZ);  // 0x7CE664
            if (i64(v1) < 0) {
                // 0x003bca1c
                charge(ctx, 7);
                a0 = srl(v1, 1);
                v1 = v1 & 0x1;
                a0 = a0 | v1;
                mtc1(a0, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x003bca08
                charge(ctx, 5);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
            }
            // 0x003bca38
            charge(ctx, 6);
            lwc1(f0, gp, g::kGpShakeScale);  // 0x7CADA0
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0x4C);
            s0 = 0;
            for (;;) {
                // 0x003bcb70
                charge(ctx, 3);
                v1 = slti(s0, 2);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003bca50
                charge(ctx, 9);
                v1 = sll(s0, 2);
                v1 = addu(v1, sp);
                v1 = addiu(v1, 72);
                lwc1(f20, v1, 0);
                mtc1(zero, f0);
                c_eq_s(f0, f20);
                if (!cond(ctx)) {
                    // 0x003bca74
                    charge(ctx, 24);
                    a0 = 0;
                    jal(ctx, 0x3BCA78u, gen::fn_sub_358030_00358030);
                    a1 = sll(s0, 2);
                    a0 = addu(a1, sp);
                    v1 = addiu(a0, 72);
                    lwc1(f4, v1, 0);
                    v1 = 0x3F000000;
                    mtc1(v1, f1);
                    mul_s(f0, f4, f0);
                    mula_s(f1, f0);
                    mtc1(zero, f3);
                    madd_s(f21, f1, f4);
                    v1 = 0x960000;
                    v1 = addiu(v1, -20496);  // &0x95AFF0
                    s1 = addu(v1, a1);
                    lwc1(f2, s1, 0);
                    abs_s(f1, f2);
                    lwc1(f0, a0, 64);
                    mul_s(f0, f4, f0);
                    c_lt_s(f1, f0);
                    if (cond(ctx)) {
                        // 0x003bcb00
                        charge(ctx, 16);
                        a0 = 0;
                        jal(ctx, 0x3BCB04u, gen::fn_sub_358030_00358030);
                        v1 = 0x3F000000;
                        mtc1(v1, f1);
                        sub_s(f0, f0, f1);
                        mul_s(f3, f21, f0);
                        v1 = 0x40000000;
                        mtc1(v1, f2);
                        lwc1(f1, s1, 0);
                        mtc1(zero, f0);
                        adda_s(f0, f1);
                        madd_s(f0, f2, f3);
                        swc1(f0, s1, 0);
                    } else {
                        // 0x003bcad4
                        charge(ctx, 3);
                        c_le_s(f2, f3);
                        if (!cond(ctx)) {
                            // 0x003bcaf0
                            charge(ctx, 4);
                            sub_s(f0, f2, f21);
                            swc1(f0, s1, 0);
                        } else {
                            // 0x003bcae0
                            charge(ctx, 4);
                            add_s(f0, f2, f21);
                            swc1(f0, s1, 0);
                        }
                    }
                    // 0x003bcb40
                    charge(ctx, 5);
                    neg_s(f1, f20);
                    lwc1(f0, s1, 0);
                    c_lt_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x003bcb54
                        charge(ctx, 1);
                        swc1(f1, s1, 0);
                    }
                    // 0x003bcb58
                    charge(ctx, 4);
                    lwc1(f0, s1, 0);
                    c_le_s(f0, f20);
                    if (!cond(ctx)) {
                        // 0x003bcb68
                        charge(ctx, 1);
                        swc1(f20, s1, 0);
                    }
                }
                // 0x003bcb6c
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x003bcb7c
            charge(ctx, 3);
            lh(a2, gp, g::kGpShakeFrames);  // 0x7CE65C
            if (i64(a2) > 0) {
                // 0x003bcb88
                charge(ctx, 13);
                a1 = addiu(a2, 5);
                lhu(a0, gp, g::kGpShakeAmpX);  // 0x7CE660
                div(a0, a1);
                mflo(v1);
                v1 = v1 & 0xFFFF;
                v1 = subu(a0, v1);
                sh(v1, gp, g::kGpShakeAmpX);  // 0x7CE660
                lhu(a0, gp, g::kGpShakeAmpZ);  // 0x7CE664
                div1(a0, a1);
                mflo1(v1);
                v1 = v1 & 0xFFFF;
                v1 = subu(a0, v1);
                sh(v1, gp, g::kGpShakeAmpZ);  // 0x7CE664
            }
            // 0x003bcbbc
            charge(ctx, 2);
            if (i64(a2) > 0) {
                // 0x003bcbc4
                charge(ctx, 3);
                lh(v1, gp, g::kGpShakeFrames);  // 0x7CE65C
                v1 = addiu(v1, -1);
                sh(v1, gp, g::kGpShakeFrames);  // 0x7CE65C
            }
        } else {
            // 0x003bc9a8
            charge(ctx, 3);
            sh(zero, gp, g::kGpShakeOn);  // 0x7CE658
        }
    } else {
        // 0x003bc974
        charge(ctx, 10);
        v1 = 0x960000;
        sw(zero, v1, g::kLoShakeX);  // 0x95AFF0
        v1 = 0x960000;
        sw(zero, v1, g::kLoShakeZ);  // 0x95AFF4
        v1 = 0x960000;
        sw(zero, v1, g::kLoShakeW2);  // 0x95AFF8
        v1 = 0x960000;
        sw(zero, v1, g::kLoShakeW3);  // 0x95AFFC
    }
    // 0x003bcbd0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003BCCB0 sub_3BCCB0 -- 204 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Update of "SceneManager Task": the shake (sub_3BC940), every resource of types 1..21 through sub_3B9610, then the
// first type-7 camera that is active (+264 == 1) applied (sub_3BB7A0); returns 0 (run again).
void sub_3BCCB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bccb0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    // the camera shake, then every resource of the types 1..21
    jal(ctx, 0x3BCCC0u, gen::fn_sub_3BC940_003bc940);
    s1 = 1;
    for (;;) {
        // 0x003bcd10
        charge(ctx, 3);
        v0 = slti(s1, 22);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bccd4
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x3BCCD8u, gen::fn_sub_3B5D50_003b5d50);
        s0 = v0;
        for (;;) {
            // 0x003bccfc
            charge(ctx, 4);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003bccec
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x3BCCF0u, gen::fn_sub_3B9610_003b9610);
            lw(s0, s0, scn::res::kNext);
        }
        // 0x003bcd0c
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x003bcd1c
    charge(ctx, 6);
    a0 = 7;
    jal(ctx, 0x3BCD20u, gen::fn_sub_3B5D50_003b5d50);
    v1 = 1;
    for (;;) {
        // 0x003bcd58
        charge(ctx, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bcd34
        charge(ctx, 3);
        lw(a0, v0, cam::kActive);
        if (a0 == v1) {
            goto L_003bcd40_8;
        }
        // 0x003bcd54
        charge(ctx, 1);
        lw(v0, v0, scn::res::kNext);
    }
    // 0x003bcd60 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_003bcd40_8:
    charge(ctx, 5);
    a0 = v0;
    jal(ctx, 0x3BCD44u, gen::fn_sub_3BB7A0_003bb7a0);
    // 0x003bcd60 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003BCD80 sub_3BCD80 -- 32 bytes; frame 0x10: ra sp+0x0
// Destroy of "SceneManager Task": a tail call of sub_3BCC80.
void sub_3BCD80(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x003bcd80
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3BCD88u, gen::fn_sub_3BCC80_003bcc80);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003BCDA0 sub_3BCDA0 -- 272 bytes; frame 0xF0: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [MT_SceneFunc_CompareEffDepth] (a, b) qsort comparator of two type-6 resources (pointers to pointers): the distance of
// b's EPL position from the camera (sub_34FFC0, the RW camera frame's position) minus a's, as an int -- far ones first.
void sub_3BCDA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x003bcda0
    enter(ctx, 68);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    s0 = a1;
    jal(ctx, 0x3BCDBCu, gen::fn_sub_198590_00198590);
    lw(a0, v0, 4);
    jal(ctx, 0x3BCDC8u, gen::fn_sub_4CB2F0_004cb2f0);
    lwc1(f2, v0, 48);
    lwc1(f1, v0, 52);
    lwc1(f0, v0, 56);
    swc1(f2, sp, 0xC0);
    swc1(f1, sp, 0xC4);
    swc1(f0, sp, 0xC8);
    lw(s0, s0, 0);
    lw(v0, s1, 0);
    lw(a0, v0, 260);
    a1 = addiu(sp, 0x80);
    jal(ctx, 0x3BCDF8u, gen::fn_sub_34FFC0_0034ffc0);
    lw(a0, s0, eff::kEpl);
    a1 = addiu(sp, 0x40);
    jal(ctx, 0x3BCE08u, gen::fn_sub_34FFC0_0034ffc0);
    v1 = addiu(sp, 0xB0);
    v0 = addiu(sp, 0x70);
    lwc1(f0, v1, 0);
    lwc1(f3, sp, 0xC0);
    sub_s(f0, f0, f3);
    swc1(f0, sp, 0xE0);
    lwc1(f2, sp, 0xC4);
    lwc1(f0, v1, 4);
    sub_s(f0, f0, f2);
    swc1(f0, sp, 0xE4);
    lwc1(f1, sp, 0xC8);
    lwc1(f0, v1, 8);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0xE8);
    lwc1(f0, v0, 0);
    sub_s(f0, f0, f3);
    swc1(f0, sp, 0xD0);
    lwc1(f0, v0, 4);
    sub_s(f0, f0, f2);
    swc1(f0, sp, 0xD4);
    lwc1(f0, v0, 8);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0xD8);
    a0 = addiu(sp, 0xE0);
    jal(ctx, 0x3BCE70u, gen::fn_sub_4C6AC0_004c6ac0);
    mov_s(f20, f0);
    a0 = addiu(sp, 0xD0);
    jal(ctx, 0x3BCE80u, gen::fn_sub_4C6AC0_004c6ac0);
    sub_s(f0, f20, f0);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xF0);
}

// 0x003BCEB0 sub_3BCEB0 -- 352 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_SceneFunc_DrawSortedEffects] (first) Collects the visible (flag bit 1) effects with an EPL and draw pass 0 from a
// type-6 list into an RwMalloc'd array, sorts them back to front (qsort, sub_3BCDA0) and draws each (sub_34FD70(epl,
// 3)); frees the array.
void sub_3BCEB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bceb0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    s0 = a0;
    for (;;) {
        // 0x003bcf0c
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bced4
        charge(ctx, 4);
        lw(v0, a0, scn::res::kFlags);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x003bcee4
            charge(ctx, 3);
            lw(v0, a0, eff::kEpl);
            if (v0 != 0) {
                // 0x003bcef0
                charge(ctx, 3);
                lb(v0, a0, eff::kPass);
                if (v0 == 0) {
                    // 0x003bcf04
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                } else {
                    // 0x003bcefc
                    charge(ctx, 2);
                }
            }
        }
        // 0x003bcf08
        charge(ctx, 1);
        lw(a0, a0, scn::res::kNext);
    }
    // 0x003bcf14
    charge(ctx, 11);
    a0 = sll(s1, 2);
    a1 = 0x40000;
    // the array of the effects to sort (RwMalloc, 4 bytes each), filled in list order
    v0 = 0x960000;
    lw(v0, v0, g::kLoRwMalloc);  // 0x960178
    jalr(ctx, 0x3BCF24u, v0.u());
    s2 = v0;
    v1 = 0;
    a0 = s0;
    for (;;) {
        // 0x003bcf84
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bcf40
        charge(ctx, 4);
        lw(v0, a0, scn::res::kFlags);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x003bcf50
            charge(ctx, 3);
            lw(v0, a0, eff::kEpl);
            if (v0 != 0) {
                // 0x003bcf5c
                charge(ctx, 3);
                lb(v0, a0, eff::kPass);
                if (v0 == 0) {
                    // 0x003bcf70
                    charge(ctx, 4);
                    v0 = sll(v1, 2);
                    v0 = addu(s2, v0);
                    sw(a0, v0, 0);
                    v1 = addiu(v1, 1);
                } else {
                    // 0x003bcf68
                    charge(ctx, 2);
                }
            }
        }
        // 0x003bcf80
        charge(ctx, 1);
        lw(a0, a0, scn::res::kNext);
    }
    // 0x003bcf8c
    charge(ctx, 10);
    a0 = s2;
    a1 = s1;
    a2 = 4;
    a3 = 0x3C0000;
    a3 = addiu(a3, -12896);  // &sub_3BCDA0
    jal(ctx, 0x3BCFA0u, gen::fn_qsort_005225f8);
    s0 = 0;
    for (;;) {
        // 0x003bcfd4
        charge(ctx, 3);
        v0 = slt(s0, s1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bcfb4
        charge(ctx, 8);
        v0 = sll(s0, 2);
        v0 = addu(s2, v0);
        lw(v0, v0, 0);
        lw(a0, v0, eff::kEpl);
        a1 = 3;
        jal(ctx, 0x3BCFC8u, gen::fn_sub_34FD70_0034fd70);
        s0 = addiu(s0, 1);
    }
    // 0x003bcfe0
    charge(ctx, 12);
    a0 = s2;
    v0 = 0x960000;
    lw(v0, v0, g::kLoRwFree);  // 0x96017C
    jalr(ctx, 0x3BCFECu, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003BD010 sub_3BD010 -- 156 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Update of "SceneManager Draw": the sorted effects (sub_3BCEB0), then the visible pass-1 effects in list order
// (sub_34FD70); returns 0.
void sub_3BD010(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bd010
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 6;
    jal(ctx, 0x3BD020u, gen::fn_sub_3B5D50_003b5d50);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x3BD030u, gen::fn_sub_3BCEB0_003bceb0);
    for (;;) {
        // 0x003bd08c
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bd040
        charge(ctx, 4);
        lw(v0, s0, scn::res::kFlags);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x003bd050
            charge(ctx, 3);
            lw(a0, s0, eff::kEpl);
            if (a0 != 0) {
                // 0x003bd05c
                charge(ctx, 4);
                lb(v1, s0, eff::kPass);
                v0 = 1;
                if (v1 == v0) {
                    // 0x003bd07c
                    charge(ctx, 3);
                    a1 = 6;
                    jal(ctx, 0x3BD080u, gen::fn_sub_34FD70_0034fd70);
                } else {
                    // 0x003bd06c
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x003bd074
                        charge(ctx, 2);
                    }
                }
            }
        }
        // 0x003bd088
        charge(ctx, 1);
        lw(s0, s0, scn::res::kNext);
    }
    // 0x003bd094
    charge(ctx, 6);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BD230 sub_3BD230 -- 68 bytes; frame 0x10: ra sp+0x0
// A script command (COMM handler): parameter 0 read and dropped, then sub_3BB010(0x400, parameter 1 & 0xFF); returns 1.
void sub_3BD230(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bd230
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x3BD23Cu, gen::fn_scrGetIntPara_0035ed20);
    a0 = 1;
    jal(ctx, 0x3BD248u, gen::fn_scrGetIntPara_0035ed20);
    a1 = v0 & 0xFF;
    a0 = 1024;
    jal(ctx, 0x3BD258u, gen::fn_sub_3BB010_003bb010);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
