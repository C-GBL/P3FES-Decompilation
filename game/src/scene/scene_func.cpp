// Slice scene (game/include/p3fes/game/scene.h has the formats and the records): mt_sceneFunc.c: the scene function layer (move / rotate / fade / motion requests, icons, bezier paths, hit values, the SceneManager tasks, the icon files).
// p3fes_handgen bodies (register for register, block for block as the recompiled ones) with a role comment per
// function and named offsets / globals (each constant equals the literal it replaces; tools check it).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/scene.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_CacheFindFile_001021c0(p3fes::EEContext&);
void fn_H_Cdvd_ReadSync_001023a0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_K_FldFrame_IsPointInTriangle_001aaad0(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sub_19C310_0019c310(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_3182D0_003182d0(p3fes::EEContext&);
void fn_sub_3186E0_003186e0(p3fes::EEContext&);
void fn_sub_318770_00318770(p3fes::EEContext&);
void fn_sub_3189F0_003189f0(p3fes::EEContext&);
void fn_sub_318B00_00318b00(p3fes::EEContext&);
void fn_sub_34FCD0_0034fcd0(p3fes::EEContext&);
void fn_sub_34FCF0_0034fcf0(p3fes::EEContext&);
void fn_sub_34FD10_0034fd10(p3fes::EEContext&);
void fn_sub_350040_00350040(p3fes::EEContext&);
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);
void fn_sub_3B8210_003b8210(p3fes::EEContext&);
void fn_sub_3B8270_003b8270(p3fes::EEContext&);
void fn_sub_3B82C0_003b82c0(p3fes::EEContext&);
void fn_sub_3B83A0_003b83a0(p3fes::EEContext&);
void fn_sub_3B86C0_003b86c0(p3fes::EEContext&);
void fn_sub_3B8A60_003b8a60(p3fes::EEContext&);
void fn_sub_3B8CE0_003b8ce0(p3fes::EEContext&);
void fn_sub_3B8FF0_003b8ff0(p3fes::EEContext&);
void fn_sub_3B9260_003b9260(p3fes::EEContext&);
void fn_sub_3B9500_003b9500(p3fes::EEContext&);
void fn_sub_3BAA70_003baa70(p3fes::EEContext&);
void fn_sub_3BAC40_003bac40(p3fes::EEContext&);
void fn_sub_3BB0C0_003bb0c0(p3fes::EEContext&);
void fn_sub_3BB340_003bb340(p3fes::EEContext&);
void fn_sub_3BB450_003bb450(p3fes::EEContext&);
void fn_sub_3BB9B0_003bb9b0(p3fes::EEContext&);
void fn_sub_3BBA70_003bba70(p3fes::EEContext&);
void fn_sub_3BBAA0_003bbaa0(p3fes::EEContext&);
void fn_sub_3BBC90_003bbc90(p3fes::EEContext&);
void fn_sub_3BBD40_003bbd40(p3fes::EEContext&);
void fn_sub_3BBFD0_003bbfd0(p3fes::EEContext&);
void fn_sub_3BC0E0_003bc0e0(p3fes::EEContext&);
void fn_sub_3BC730_003bc730(p3fes::EEContext&);
void fn_sub_3BC8F0_003bc8f0(p3fes::EEContext&);
void fn_sub_3BC900_003bc900(p3fes::EEContext&);
void fn_sub_3BD0B0_003bd0b0(p3fes::EEContext&);
void fn_sub_3BD130_003bd130(p3fes::EEContext&);
void fn_sub_3BD1C0_003bd1c0(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4C6C60_004c6c60(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace scn;

// 0x003B8210 sub_3B8210 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Update of the "IconEplDestroyDell" task: counts the work's frames down; below zero destroys its EPL (sub_34FCF0),
// clears it and returns -1 (task done), else 0.
void sub_3B8210(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b8210
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(v0, s0, icondel::kFrames);
    v0 = addiu(v0, -1);
    sw(v0, s0, icondel::kFrames);
    if (i64(v0) >= 0) {
        // 0x003b8250
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003b8234
        charge(ctx, 7);
        lw(a0, s0, icondel::kEpl);
        jal(ctx, 0x3B8238u, gen::fn_sub_34FCF0_0034fcf0);
        sw(zero, s0, icondel::kEpl);
        v0 = si(-1);
    }
    // 0x003b8254 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B8270 sub_3B8270 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Destroy of the "IconEplDestroyDell" task: destroys a remaining EPL and frees the work (RwFree).
void sub_3B8270(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b8270
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, icondel::kEpl);
    if (a0 != 0) {
        // 0x003b828c
        charge(ctx, 3);
        jal(ctx, 0x3B828Cu, gen::fn_sub_34FCF0_0034fcf0);
        sw(zero, s0, icondel::kEpl);
    }
    // 0x003b8298
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, g::kLoRwFree);  // 0x96017C the RwFree slot
    jalr(ctx, 0x3B82A4u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B82C0 sub_3B82C0 -- 80 bytes; leaf frame (no stack)
// [MT_SceneFunc_SetShown] (res, on) Sets (on == 1) or clears flag bit 3 (shown / drawn); 1, or 0 for a NULL record.
void sub_3B82C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003b82c0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x003b82d4
        charge(ctx, 3);
        v0 = 1;
        if (a1 != v0) {
            // 0x003b82f4
            charge(ctx, 4);
            lw(v1, a0, res::kFlags);
            v0 = si(-9);
            v0 = v1 & v0;
            sw(v0, a0, res::kFlags);
        } else {
            // 0x003b82e0
            charge(ctx, 5);
            lw(v0, a0, res::kFlags);
            v0 = v0 | 0x8;
            sw(v0, a0, res::kFlags);
        }
        // 0x003b8304
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x003b82c8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b8308 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003B83A0 sub_3B83A0 -- 40 bytes; leaf frame (no stack)
// [MT_SceneFunc_IsShown] (res) Flag bit 3 of a non-NULL record (0 / 1).
void sub_3B83A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x003b83a0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x003b83b4
        charge(ctx, 3);
        lw(v0, a0, res::kFlags);
        v0 = v0 & 0x8;
        v0 = sltu(0, v0);
    } else {
        // 0x003b83a8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b83c0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003B86C0 sub_3B86C0 -- 112 bytes; leaf frame (no stack)
// [MT_SceneFunc_RequestMove] (res, to, $f12 speed) Starts a move: flag bit 0 on, bit 6 off, from = the current
// position, to, speed, state 0; 1, or 0 for NULL.
void sub_3B86C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x003b86c0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x003b86d4
        charge(ctx, 21);
        lw(v0, a0, res::kFlags);
        v1 = v0 | 0x1;
        sw(v1, a0, res::kFlags);
        v0 = si(-65);
        v0 = v1 & v0;
        sw(v0, a0, res::kFlags);
        lwc1(f2, a0, res::kPos);
        lwc1(f1, a0, res::kPosY);
        lwc1(f0, a0, res::kPosZ);
        swc1(f2, a0, res::kMoveFrom);
        swc1(f1, a0, res::kMoveFromY);
        swc1(f0, a0, res::kMoveFromZ);
        lwc1(f2, a1, 0);
        lwc1(f1, a1, 4);
        lwc1(f0, a1, 8);
        swc1(f2, a0, res::kMoveTo);
        swc1(f1, a0, res::kMoveToY);
        swc1(f0, a0, res::kMoveToZ);
        swc1(f12, a0, res::kMoveSpeed);
        sb(zero, a0, res::kMoveState);
        v0 = 1;
    } else {
        // 0x003b86c8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b8728 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003B8A60 sub_3B8A60 -- 204 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_SceneFunc_RequestRotate] (res, to, frames, mode) Starts a rotation: the current and target angles normalised to
// [0, 360) (sub_3BBA70 / sub_3BB9B0), flag bit 2, from / to, state 0, mode byte, frames, time 0; 1, or 0 for NULL.
void sub_3B8A60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x003b8a60
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a2;
    s0 = a3;
    lwc1(f2, a1, 0);
    lwc1(f1, a1, 4);
    lwc1(f0, a1, 8);
    swc1(f2, sp, 0x40);
    swc1(f1, sp, 0x44);
    swc1(f0, sp, 0x48);
    if (s2 != 0) {
        // 0x003b8aac
        charge(ctx, 25);
        jal(ctx, 0x3B8AACu, gen::fn_sub_3BBA70_003bba70);
        a0 = addiu(sp, 0x40);
        jal(ctx, 0x3B8AB8u, gen::fn_sub_3BB9B0_003bb9b0);
        lw(v0, s2, res::kFlags);
        v0 = v0 | 0x4;
        sw(v0, s2, res::kFlags);
        lwc1(f2, s2, res::kRot);
        lwc1(f1, s2, res::kRotY);
        lwc1(f0, s2, res::kRotZ);
        swc1(f2, s2, res::kRotFrom);
        swc1(f1, s2, res::kRotFromY);
        swc1(f0, s2, res::kRotFromZ);
        lwc1(f2, sp, 0x40);
        lwc1(f1, sp, 0x44);
        lwc1(f0, sp, 0x48);
        swc1(f2, s2, res::kRotTo);
        swc1(f1, s2, res::kRotToY);
        swc1(f0, s2, res::kRotToZ);
        sb(zero, s2, res::kRotState);
        sb(s0, s2, res::kRotMode);
        sw(s1, s2, res::kRotFrames);
        sw(zero, s2, res::kRotTime);
        v0 = 1;
    } else {
        // 0x003b8aa0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b8b10 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003B8CE0 sub_3B8CE0 -- 300 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_SceneFunc_RequestFade] (res, alpha, frames, hold) Starts an alpha fade of an effect (type 6: the start alpha
// from the EPL, sub_350040) or an object (type 3: from its model's colour, sub_318B00; +192 = hold == 1): flag
// 0x4000, from / to alpha, frames, time 0; 1, or 0 for other types.
void sub_3B8CE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b8ce0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = a3;
    if (s3 != 0) {
        // 0x003b8d1c
        charge(ctx, 8);
        lhu(v1, s3, res::kId);
        v0 = 0xF0000;
        v0 = v0 | 0xFC00;
        v0 = v1 & v0;
        v1 = sra(v0, 10);
        v0 = 6;
        if (v1 == v0) {
            // 0x003b8da4
            charge(ctx, 7);
            lw(a0, s3, eff::kEpl);
            a1 = addiu(sp, 0x58);
            jal(ctx, 0x3B8DACu, gen::fn_sub_350040_00350040);
            lbu(v1, sp, 0x5B);
        L_003b8dcc:
            charge(ctx, 8);
            lw(v0, s3, res::kFlags);
            v0 = v0 | 0x4000;
            sw(v0, s3, res::kFlags);
            sb(v1, s3, res::kFadeFrom);
            sb(s2, s3, res::kFadeTo);
            sw(s1, s3, res::kFadeFrames);
            sw(zero, s3, res::kFadeTime);
            v0 = 1;
        } else {
            // 0x003b8d3c
            charge(ctx, 3);
            v0 = 3;
            if (v1 == v0) {
                // 0x003b8d50
                charge(ctx, 15);
                lw(a0, s3, npc::kModel);
                jal(ctx, 0x3B8D54u, gen::fn_sub_318B00_00318b00);
                lbu(a1, v0, 0);
                lbu(a0, v0, 1);
                lbu(v1, v0, 2);
                lbu(v0, v0, 3);
                sb(a1, sp, 0x5C);
                sb(a0, sp, 0x5D);
                sb(v1, sp, 0x5E);
                sb(v0, sp, 0x5F);
                lbu(v1, sp, 0x5F);
                v0 = 1;
                if (s0 != v0) {
                    // 0x003b8d98
                    charge(ctx, 3);
                    sb(zero, s3, res::kFadeHold);
                } else {
                    // 0x003b8d8c
                    charge(ctx, 3);
                    sb(v0, s3, res::kFadeHold);
                }
                goto L_003b8dcc;
            }
            // 0x003b8d48
            charge(ctx, 2);
            // 0x003b8dc0
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b8d10
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b8dec (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003B8FF0 sub_3B8FF0 -- 456 bytes; frame 0x90: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [MT_SceneFunc_ChangeMotion] (res, group, minor, blend, loop, wait) Switches the object's motion (types 1 / 3 +296,
// 2 +280, 10 +260) unless it already plays it (sub_3186E0): sub_3189F0, sub_3182D0 with the loop flag (loop == 1),
// sub_318770 when wait > 0, the "motion change" print; clears flag 0x2000; 1, or 0 for other types.
void sub_3B8FF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20};
    // 0x003b8ff0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s5 = a0;
    s4 = a1;
    s3 = a2;
    s6 = a3;
    s2 = t1;
    mov_s(f20, f12);
    if (s5 != 0) {
        // 0x003b9044
        charge(ctx, 8);
        lhu(v1, s5, res::kId);
        v0 = 0xF0000;
        v0 = v0 | 0xFC00;
        v0 = v1 & v0;
        v1 = sra(v0, 10);
        v0 = 10;
        if (v1 == v0) {
            // 0x003b90b4
            charge(ctx, 3);
            lw(s0, s5, fmdl::kModel);
        L_003b90cc:
            charge(ctx, 4);
            s1 = 0;
            v0 = 1;
            if (t0 == v0) {
                // 0x003b90dc
                charge(ctx, 1);
                s1 = s1 | 0x1;
            }
            // 0x003b90e0
            charge(ctx, 8);
            a1 = s4 & 0xFFFF;
            a2 = dsll32(s3, 16);
            a2 = dsra32(a2, 16);
            a0 = s0;
            jal(ctx, 0x3B90F0u, gen::fn_sub_3186E0_003186e0);
            if (v0 == 0) {
                // 0x003b9100
                charge(ctx, 15);
                a1 = s4 & 0xFFFF;
                a0 = s0;
                mov_s(f12, f20);
                jal(ctx, 0x3B910Cu, gen::fn_sub_3189F0_003189f0);
                a1 = s4 & 0xFFFF;
                a2 = dsll32(s3, 16);
                a2 = dsra32(a2, 16);
                a3 = s6 & 0xFFFF;
                t0 = s1 & 0xFFFF;
                a0 = s0;
                jal(ctx, 0x3B912Cu, gen::fn_sub_3182D0_003182d0);
                if (i64(s2) > 0) {
                    // 0x003b913c
                    charge(ctx, 7);
                    mtc1(s2, f0);
                    cvt_s_w(f12, f0);
                    a1 = s4 & 0xFFFF;
                    a0 = s0;
                    jal(ctx, 0x3B9150u, gen::fn_sub_318770_00318770);
                }
                // 0x003b9158
                charge(ctx, 7);
                a0 = 0x6A0000;
                a0 = addiu(a0, 11792);  // "motion change hModel=%x,groupno=%d minorno=%d\n"
                a1 = s0;
                a2 = s4;
                a3 = s3;
                jal(ctx, 0x3B916Cu, gen::fn_printf_005225a8);
            }
            // 0x003b9174
            charge(ctx, 5);
            lw(v1, s5, res::kFlags);
            v0 = si(-8193);
            v0 = v1 & v0;
            sw(v0, s5, res::kFlags);
            v0 = 1;
        } else {
            // 0x003b9064
            charge(ctx, 3);
            v0 = 3;
            if (v1 == v0) {
                // 0x003b90a8
                charge(ctx, 3);
                lw(s0, s5, chr::kModel);
                goto L_003b90cc;
            }
            // 0x003b9070
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x003b909c
                charge(ctx, 3);
                lw(s0, s5, mdl::kModel);
                goto L_003b90cc;
            }
            // 0x003b907c
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x003b9090
                charge(ctx, 3);
                lw(s0, s5, chr::kModel);
                goto L_003b90cc;
            }
            // 0x003b9088
            charge(ctx, 2);
            // 0x003b90c0
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b9038
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b9188 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x003B9260 sub_3B9260 -- 180 bytes; leaf frame (no stack)
// [MT_SceneFunc_QueueMotion] (res, a1..a5, $f12) Queues a motion request (types 1 / 3 at +272, 2 at +256: five words
// and a float) and sets flag 0x2000; 1, or 0 for other types.
void sub_3B9260(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    Fpr f12{ctx, 12};
    // 0x003b9260
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x003b9274
        charge(ctx, 8);
        lhu(v1, a0, res::kId);
        v0 = 0xF0000;
        v0 = v0 | 0xFC00;
        v0 = v1 & v0;
        v1 = sra(v0, 10);
        v0 = 3;
        if (v1 == v0) {
            // 0x003b92cc
            charge(ctx, 3);
            v1 = addiu(a0, 272);
        L_003b92e4:
            charge(ctx, 10);
            lw(v0, a0, res::kFlags);
            v0 = v0 | 0x2000;
            sw(v0, a0, res::kFlags);
            sw(a1, v1, 0);
            sw(a2, v1, 4);
            sw(a3, v1, 8);
            sw(t0, v1, 12);
            sw(t1, v1, 16);
            swc1(f12, v1, 20);
            v0 = 1;
        } else {
            // 0x003b9294
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x003b92c0
                charge(ctx, 3);
                v1 = addiu(a0, 256);
                goto L_003b92e4;
            }
            // 0x003b92a0
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x003b92b4
                charge(ctx, 3);
                v1 = addiu(a0, 272);
                goto L_003b92e4;
            }
            // 0x003b92ac
            charge(ctx, 2);
            // 0x003b92d8
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b9268
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b930c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003B9500 sub_3B9500 -- 80 bytes; leaf frame (no stack)
// [MT_SceneFunc_SetVisible] (res, on) Sets (on == 1) or clears flag bit 1 (the bit the field draw tasks test); 1, or
// 0 for NULL.
void sub_3B9500(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003b9500
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x003b9514
        charge(ctx, 3);
        v0 = 1;
        if (a1 != v0) {
            // 0x003b9534
            charge(ctx, 4);
            lw(v1, a0, res::kFlags);
            v0 = si(-3);
            v0 = v1 & v0;
            sw(v0, a0, res::kFlags);
        } else {
            // 0x003b9520
            charge(ctx, 5);
            lw(v0, a0, res::kFlags);
            v0 = v0 | 0x2;
            sw(v0, a0, res::kFlags);
        }
        // 0x003b9544
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x003b9508
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b9548 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003BAA70 sub_3BAA70 -- 464 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_SceneFunc_GetHitValue] (pos) The value of the field hit under a point: the default from 0x67EF00[major][minor]
// (minor - 49 on random floors 20..28 with minor >= 50; 0 when the major has no row), replaced by the +332 of the
// first type-21 hit whose two triangles (quad +284..+320) contain the point (K_FldFrame_IsPointInTriangle, normal
// 0x6A2DA0) within 100 units in height.
void sub_3BAA70(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x003baa70
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    a0 = 21;
    jal(ctx, 0x3BAA8Cu, gen::fn_sub_3B5D50_003b5d50);
    s0 = v0;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(v1, v0, 0);
    lw(a0, v0, 4);
    v0 = sltiu(v1, 20);
    if (v0 == 0) {
        // 0x003baab0
        charge(ctx, 3);
        at = sltiu(v1, 29);
        if (at != 0) {
            // 0x003baabc
            charge(ctx, 3);
            v0 = sltiu(a0, 50);
            if (v0 == 0) {
                // 0x003baac8
                charge(ctx, 1);
                a0 = addiu(a0, -49);
            }
        }
    }
    // 0x003baacc
    charge(ctx, 7);
    v1 = sll(v1, 2);
    v0 = 0x680000;
    v0 = addiu(v0, -4352);  // &0x67EF00
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x003baaf4
        charge(ctx, 4);
        v0 = addu(v0, a0);
        lbu(s1, v0, 0);
        for (;;) {
            // 0x003bac18
            charge(ctx, 2);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003bab04
            charge(ctx, 20);
            a2 = addiu(sp, 0x40);
            v0 = 0x6A0000;
            ld(v1, v0, 11680);  // 0x6A2DA0
            v0 = 0x6A0000;
            lwc1(f0, v0, 11688);  // 0x6A2DA8
            sd(v1, sp, 0x40);
            swc1(f0, sp, 0x48);
            v0 = addiu(s0, 284);
            sw(v0, sp, 0x50);
            v0 = addiu(s0, 296);
            sw(v0, sp, 0x54);
            v0 = addiu(s0, 308);
            sw(v0, sp, 0x58);
            a0 = s2;
            a1 = addiu(sp, 0x50);
            jal(ctx, 0x3BAB40u, gen::fn_K_FldFrame_IsPointInTriangle_001aaad0);
            v1 = 1;
            if (v0 == v1) {
                // 0x003bab54
                charge(ctx, 10);
                lw(v0, sp, 0x50);
                lwc1(f3, v0, 4);
                lwc1(f2, s2, 4);
                v0 = 0x42C80000;
                mtc1(v0, f1);
                add_s(f0, f1, f3);
                c_lt_s(f2, f0);
                if (!cond(ctx)) {
                    goto L_003bab98;
                }
                // 0x003bab7c
                charge(ctx, 4);
                sub_s(f0, f3, f1);
                c_le_s(f2, f0);
                if (cond(ctx)) {
                    goto L_003bab98;
                }
                goto L_003bab8c_10;
            }
        L_003bab98:
            charge(ctx, 14);
            v0 = addiu(s0, 296);
            sw(v0, sp, 0x50);
            v0 = addiu(s0, 308);
            sw(v0, sp, 0x54);
            v0 = addiu(s0, 320);
            sw(v0, sp, 0x58);
            a0 = s2;
            a1 = addiu(sp, 0x50);
            a2 = addiu(sp, 0x40);
            jal(ctx, 0x3BABBCu, gen::fn_K_FldFrame_IsPointInTriangle_001aaad0);
            v1 = 1;
            if (v0 == v1) {
                // 0x003babd0
                charge(ctx, 10);
                lw(v0, sp, 0x50);
                lwc1(f3, v0, 4);
                lwc1(f2, s2, 4);
                v0 = 0x42C80000;
                mtc1(v0, f1);
                add_s(f0, f1, f3);
                c_lt_s(f2, f0);
                if (!cond(ctx)) {
                    goto L_003bac14;
                }
                // 0x003babf8
                charge(ctx, 4);
                sub_s(f0, f3, f1);
                c_le_s(f2, f0);
                if (cond(ctx)) {
                    goto L_003bac14;
                }
                goto L_003bac08_14;
            }
        L_003bac14:
            charge(ctx, 1);
            lw(s0, s0, 248);
        }
    L_003bac20:
        charge(ctx, 1);
        v0 = s1;
    } else {
        // 0x003baae8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003bac24 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_003bab8c_10:
    charge(ctx, 3);
    lw(s1, s0, hit::kValue);
    goto L_003bac20;
L_003bac08_14:
    charge(ctx, 3);
    lw(s1, s0, hit::kValue);
    goto L_003bac20;
}

// 0x003BAC40 sub_3BAC40 -- 968 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_SceneFunc_SetIcon] (res, icon) The icon EPL over a character (type 1) or object (type 3): icon 10 (the "10ban"
// icon) is created once in +264 ("10ban icon create") and a second call resets it ("10ban icon reset"); any other
// icon swaps the two slots +256 / +260 (+268 toggles): the old EPL is handed to an "IconEplDestroyDell" task
// (sub_3B8210 / sub_3B8270, two frames) and the new one created from the icon file (sub_3BD1C0, sub_34FCD0; asserts
// mt_sceneFunc.c 1690 .. 1763 on failure); 1, or 0 for other types.
void sub_3BAC40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bac40
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    if (s2 != 0) {
        // 0x003bac7c
        charge(ctx, 8);
        lhu(v1, s2, res::kId);
        v0 = 0xF0000;
        v0 = v0 | 0xFC00;
        v0 = v1 & v0;
        v1 = sra(v0, 10);
        s0 = 1;
        if (v1 == s0) {
            // 0x003bac9c
            charge(ctx, 4);
            v1 = s1 & 0xFF;
            v0 = 10;
            if (v1 != v0) {
                // 0x003bad30
                charge(ctx, 3);
                lb(v0, s2, chr::kIconSide);
                if (v0 != 0) {
                    // 0x003bad4c
                    charge(ctx, 1);
                    v0 = 0;
                } else {
                    // 0x003bad3c
                    charge(ctx, 4);
                    v0 = s0;
                    s0 = 0;
                }
                // 0x003bad50
                charge(ctx, 6);
                v0 = sll(v0, 2);
                v0 = addu(v0, s2);
                s4 = addiu(v0, 256);
                lw(s3, v0, 256);
                if (s3 != 0) {
                    // 0x003bad68
                    charge(ctx, 21);
                    a0 = 1;
                    a1 = 8;
                    a2 = 0x40000;
                    v0 = 0x960000;
                    lw(v0, v0, g::kLoRwCalloc);  // 0x960184 the RwCalloc slot
                    jalr(ctx, 0x3BAD7Cu, v0.u());
                    s5 = v0;
                    a0 = 0;
                    a1 = 0x6A0000;
                    a1 = addiu(a1, 11696);  // "IconEplDestroyDell"
                    a2 = 7407;
                    a3 = 0x3C0000;
                    a3 = addiu(a3, -32240);  // &sub_3B8210
                    t0 = 0x3C0000;
                    t0 = addiu(t0, -32144);  // &sub_3B8270
                    t1 = s5;
                    jal(ctx, 0x3BADACu, gen::fn_kwlnTaskCreate_00194b20);
                    if (v0 != 0) {
                        // 0x003badbc
                        charge(ctx, 3);
                        v0 = 2;
                        sw(v0, s5, 0);
                        sw(s3, s5, 4);
                    }
                    // 0x003badc8
                    charge(ctx, 1);
                    sw(zero, s4, 0);
                }
                // 0x003badcc
                charge(ctx, 5);
                a0 = s1 & 0xFF;
                jal(ctx, 0x3BADD0u, gen::fn_sub_3BD1C0_003bd1c0);
                if (v0 != 0) {
                    // 0x003bade0
                    charge(ctx, 9);
                    v1 = sll(s0, 2);
                    v1 = addu(v1, s2);
                    s0 = addiu(v1, 256);
                    a0 = v0;
                    jal(ctx, 0x3BADF0u, gen::fn_sub_34FCD0_0034fcd0);
                    sw(v0, s0, 0);
                    if (v0 == 0) {
                        // 0x003bae04
                        charge(ctx, 5);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, 11736);  // "mt_sceneFunc.c"
                        a1 = 1715;
                        jal(ctx, 0x3BAE10u, gen::fn_sub_19D3F0_0019d3f0);
                    }
                }
                // 0x003bae18
                charge(ctx, 6);
                lb(v0, s2, chr::kIconSide);
                // xor v0: a 64-bit move to itself (no effect)
                v0 = sltiu(v0, 1);
                sb(v0, s2, chr::kIconSide);
            } else {
                // 0x003bacac
                charge(ctx, 3);
                lw(a0, s2, chr::kIconTen);
                if (a0 == 0) {
                    // 0x003bacd8
                    charge(ctx, 5);
                    a0 = v1;
                    jal(ctx, 0x3BACDCu, gen::fn_sub_3BD1C0_003bd1c0);
                    if (v0 != 0) {
                        // 0x003bacec
                        charge(ctx, 6);
                        a0 = v0;
                        jal(ctx, 0x3BACF0u, gen::fn_sub_34FCD0_0034fcd0);
                        sw(v0, s2, chr::kIconTen);
                        if (v0 == 0) {
                            // 0x003bad04
                            charge(ctx, 5);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, 11736);  // "mt_sceneFunc.c"
                            a1 = 1690;
                            jal(ctx, 0x3BAD10u, gen::fn_sub_19D3F0_0019d3f0);
                        }
                        // 0x003bad18
                        charge(ctx, 6);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, 11968);  // "10ban icon create\n"
                        jal(ctx, 0x3BAD20u, gen::fn_printf_005225a8);
                    }
                } else {
                    // 0x003bacb8
                    charge(ctx, 8);
                    jal(ctx, 0x3BACB8u, gen::fn_sub_34FD10_0034fd10);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 11936);  // "10ban icon reset\n"
                    jal(ctx, 0x3BACC8u, gen::fn_printf_005225a8);
                }
            }
            goto L_003bafdc;
        }
        // 0x003bae30
        charge(ctx, 3);
        v0 = 3;
        if (v1 != v0) {
            // 0x003bafd0
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x003bae3c
            charge(ctx, 4);
            v1 = s1 & 0xFF;
            v0 = 10;
            if (v1 != v0) {
                // 0x003baed4
                charge(ctx, 3);
                lb(v0, s2, chr::kIconSide);
                if (v0 != 0) {
                    // 0x003baef0
                    charge(ctx, 1);
                    v1 = 0;
                } else {
                    // 0x003baee0
                    charge(ctx, 4);
                    v1 = s0;
                    s0 = 0;
                }
                // 0x003baef4
                charge(ctx, 9);
                // xor v0: a 64-bit move to itself (no effect)
                v0 = sltiu(v0, 1);
                sb(v0, s2, chr::kIconSide);
                v0 = sll(v1, 2);
                v0 = addu(v0, s2);
                s4 = addiu(v0, 256);
                lw(s3, v0, 256);
                if (s3 != 0) {
                    // 0x003baf18
                    charge(ctx, 21);
                    a0 = 1;
                    a1 = 8;
                    a2 = 0x40000;
                    v0 = 0x960000;
                    lw(v0, v0, g::kLoRwCalloc);  // 0x960184 the RwCalloc slot
                    jalr(ctx, 0x3BAF2Cu, v0.u());
                    s5 = v0;
                    a0 = 0;
                    a1 = 0x6A0000;
                    a1 = addiu(a1, 11696);  // "IconEplDestroyDell"
                    a2 = 7407;
                    a3 = 0x3C0000;
                    a3 = addiu(a3, -32240);  // &sub_3B8210
                    t0 = 0x3C0000;
                    t0 = addiu(t0, -32144);  // &sub_3B8270
                    t1 = s5;
                    jal(ctx, 0x3BAF5Cu, gen::fn_kwlnTaskCreate_00194b20);
                    if (v0 != 0) {
                        // 0x003baf6c
                        charge(ctx, 3);
                        v0 = 2;
                        sw(v0, s5, 0);
                        sw(s3, s5, 4);
                    }
                    // 0x003baf78
                    charge(ctx, 1);
                    sw(zero, s4, 0);
                }
                // 0x003baf7c
                charge(ctx, 5);
                a0 = s1 & 0xFF;
                jal(ctx, 0x3BAF80u, gen::fn_sub_3BD1C0_003bd1c0);
                if (v0 != 0) {
                    // 0x003baf90
                    charge(ctx, 9);
                    v1 = sll(s0, 2);
                    v1 = addu(v1, s2);
                    s0 = addiu(v1, 256);
                    a0 = v0;
                    jal(ctx, 0x3BAFA0u, gen::fn_sub_34FCD0_0034fcd0);
                    sw(v0, s0, 0);
                    if (v0 == 0) {
                        // 0x003bafb4
                        charge(ctx, 7);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, 11736);  // "mt_sceneFunc.c"
                        a1 = 1763;
                        jal(ctx, 0x3BAFC0u, gen::fn_sub_19D3F0_0019d3f0);
                    }
                }
            } else {
                // 0x003bae4c
                charge(ctx, 3);
                lw(a0, s2, chr::kIconTen);
                if (a0 == 0) {
                    // 0x003bae78
                    charge(ctx, 5);
                    a0 = v1;
                    jal(ctx, 0x3BAE7Cu, gen::fn_sub_3BD1C0_003bd1c0);
                    if (v0 != 0) {
                        // 0x003bae8c
                        charge(ctx, 11);
                        a0 = v0;
                        jal(ctx, 0x3BAE90u, gen::fn_sub_34FCD0_0034fcd0);
                        sw(v0, s2, chr::kIconTen);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, 11968);  // "10ban icon create\n"
                        jal(ctx, 0x3BAEA4u, gen::fn_printf_005225a8);
                        lw(v0, s2, chr::kIconTen);
                        if (v0 == 0) {
                            // 0x003baeb8
                            charge(ctx, 7);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, 11736);  // "mt_sceneFunc.c"
                            a1 = 1736;
                            jal(ctx, 0x3BAEC4u, gen::fn_sub_19D3F0_0019d3f0);
                        }
                    }
                } else {
                    // 0x003bae58
                    charge(ctx, 8);
                    jal(ctx, 0x3BAE58u, gen::fn_sub_34FD10_0034fd10);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 11936);  // "10ban icon reset\n"
                    jal(ctx, 0x3BAE68u, gen::fn_printf_005225a8);
                }
            }
        L_003bafdc:
            charge(ctx, 1);
            v0 = 1;
        }
    } else {
        // 0x003bac70
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003bafe0 (the shared epilogue, written out on this path)
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

// 0x003BB0C0 sub_3BB0C0 -- 192 bytes; frame 0x10: ra sp+0x0
// [MT_SceneFunc_SetCtlMode] (res, on) Sets the controller of a character (+484) or object (+496) to mode 3 (on == 1)
// or 0 (sub_19C310); 1, or 0 without one.
void sub_3BB0C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bb0c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    if (a0 != 0) {
        // 0x003bb0e0
        charge(ctx, 8);
        lhu(v1, a0, res::kId);
        v0 = 0xF0000;
        v0 = v0 | 0xFC00;
        v0 = v1 & v0;
        v1 = sra(v0, 10);
        v0 = 3;
        if (v1 == v0) {
            // 0x003bb120
            charge(ctx, 1);
            lw(a2, a0, 496);
        } else {
            // 0x003bb100
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x003bb114
                charge(ctx, 3);
                lw(a2, a0, 484);
            } else {
                // 0x003bb10c
                charge(ctx, 2);
            }
        }
        // 0x003bb124
        charge(ctx, 2);
        if (a2 != 0) {
            // 0x003bb138
            charge(ctx, 3);
            v0 = 1;
            if (a1 != v0) {
                // 0x003bb15c
                charge(ctx, 4);
                a0 = a2;
                a1 = 0;
                jal(ctx, 0x3BB164u, gen::fn_sub_19C310_0019c310);
            } else {
                // 0x003bb144
                charge(ctx, 6);
                a0 = a2;
                a1 = 3;
                jal(ctx, 0x3BB14Cu, gen::fn_sub_19C310_0019c310);
            }
            // 0x003bb16c
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x003bb12c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003bb0d4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003bb170 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003BB340 sub_3BB340 -- 76 bytes; frame 0x10: ra sp+0x0
// [MT_SceneFunc_ResetRes7] Clears +264 of every type-7 resource; returns the list head.
void sub_3BB340(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bb340
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 7;
    jal(ctx, 0x3BB34Cu, gen::fn_sub_3B5D50_003b5d50);
    v1 = v0;
    for (;;) {
        // 0x003bb368
        charge(ctx, 5);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bb360
        charge(ctx, 2);
        sw(zero, v1, snd::kState);
        lw(v1, v1, res::kNext);
    }
    // 0x003bb37c
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003BB450 sub_3BB450 -- 460 bytes; frame 0xF0: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [MT_SceneFunc_OffsetAlongDir] (pos, out, $f12 dist) out = pos - dist * d, d = the direction 0x6A2EF8 rotated by the
// matrix of the three axes 0x6A2EE8.. (sub_4C31B0 / sub_4C6C60); ACC-fused multiply-subtract per component.
void sub_3BB450(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x003bb450
    enter(ctx, 115);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    mov_s(f20, f12);
    mov_s(f22, f13);
    mov_s(f21, f15);
    s0 = a1;
    v0 = 0x6A0000;
    ld(v1, v0, 11992);  // 0x6A2ED8
    v0 = 0x6A0000;
    lwc1(f0, v0, 12000);  // 0x6A2EE0
    sd(v1, sp, 0xE0);
    swc1(f0, sp, 0xE8);
    v0 = 0x6A0000;
    ld(v1, v0, 12008);  // 0x6A2EE8
    v0 = 0x6A0000;
    lwc1(f0, v0, 12016);  // 0x6A2EF0
    sd(v1, sp, 0xA0);
    swc1(f0, sp, 0xA8);
    a1 = addiu(sp, 0x90);
    v0 = 0x6A0000;
    ld(v1, v0, 12024);  // 0x6A2EF8
    v0 = 0x6A0000;
    lwc1(f0, v0, 12032);  // 0x6A2F00
    sd(v1, sp, 0x90);
    swc1(f0, sp, 0x98);
    v0 = 0x6A0000;
    ld(v1, v0, 12040);  // 0x6A2F08
    v0 = 0x6A0000;
    lwc1(f0, v0, 12048);  // 0x6A2F10
    sd(v1, sp, 0x80);
    swc1(f0, sp, 0x88);
    v0 = 0x3F800000;
    sw(v0, sp, 0x68);
    sw(v0, sp, 0x54);
    sw(v0, sp, 0x40);
    sw(zero, sp, 0x50);
    sw(zero, sp, 0x48);
    sw(zero, sp, 0x44);
    sw(zero, sp, 0x64);
    sw(zero, sp, 0x60);
    sw(zero, sp, 0x58);
    sw(zero, sp, 0x78);
    sw(zero, sp, 0x74);
    sw(zero, sp, 0x70);
    lw(v1, sp, 0x4C);
    v0 = 0x20000;
    v0 = v0 | 0x3;
    v0 = v1 | v0;
    sw(v0, sp, 0x4C);
    a0 = addiu(sp, 0x40);
    mov_s(f12, f14);
    a2 = 1;
    jal(ctx, 0x3BB538u, gen::fn_sub_4C31B0_004c31b0);
    a0 = addiu(sp, 0x40);
    a1 = addiu(sp, 0xA0);
    mov_s(f12, f22);
    a2 = 1;
    jal(ctx, 0x3BB550u, gen::fn_sub_4C31B0_004c31b0);
    a0 = addiu(sp, 0x40);
    a1 = addiu(sp, 0x80);
    mov_s(f12, f21);
    a2 = 1;
    jal(ctx, 0x3BB568u, gen::fn_sub_4C31B0_004c31b0);
    a0 = addiu(sp, 0xD0);
    a1 = addiu(sp, 0xE0);
    a2 = addiu(sp, 0x40);
    jal(ctx, 0x3BB57Cu, gen::fn_sub_4C6C60_004c6c60);
    lwc1(f2, s1, 0);
    lwc1(f1, s1, 4);
    lwc1(f0, s1, 8);
    swc1(f2, sp, 0xC0);
    swc1(f1, sp, 0xC4);
    swc1(f0, sp, 0xC8);
    lwc1(f1, sp, 0xD0);
    lwc1(f0, sp, 0xC0);
    mtc1(zero, f2);
    adda_s(f2, f0);
    msub_s(f0, f1, f20);
    swc1(f0, sp, 0xB0);
    lwc1(f1, sp, 0xD4);
    lwc1(f0, sp, 0xC4);
    adda_s(f2, f0);
    msub_s(f0, f1, f20);
    swc1(f0, sp, 0xB4);
    lwc1(f1, sp, 0xD8);
    lwc1(f0, sp, 0xC8);
    adda_s(f2, f0);
    msub_s(f0, f1, f20);
    swc1(f0, sp, 0xB8);
    lwc1(f2, sp, 0xB0);
    lwc1(f1, sp, 0xB4);
    lwc1(f0, sp, 0xB8);
    swc1(f2, s0, 0);
    swc1(f1, s0, 4);
    swc1(f0, s0, 8);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xF0);
}

// 0x003BB9B0 sub_3BB9B0 -- 188 bytes; frame 0x10
// [MT_SceneFunc_NormAngles] (angles) Wraps each of the three angles into [0, 360) by repeated -360 / +360.
void sub_3BB9B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x003bb9b0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    lwc1(f0, a0, 0);
    swc1(f0, sp, 0x0);
    lwc1(f0, a0, 4);
    swc1(f0, sp, 0x4);
    lwc1(f0, a0, 8);
    swc1(f0, sp, 0x8);
    a1 = 0;
    v1 = 0x43B40000;
    mtc1(v1, f2);
    mtc1(zero, f0);
    for (;;) {
        // 0x003bba3c
        charge(ctx, 3);
        v1 = slti(a1, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bb9e4
        charge(ctx, 5);
        v1 = sll(a1, 2);
        v1 = addu(v1, sp);
        v1 = addiu(v1, 0);
        for (;;) {
            // 0x003bba04
            charge(ctx, 4);
            lwc1(f1, v1, 0);
            c_lt_s(f1, f2);
            if (cond(ctx)) {
                break;
            }
            backedge(ctx);
            // 0x003bb9f8
            charge(ctx, 3);
            lwc1(f1, v1, 0);
            sub_s(f1, f1, f2);
            swc1(f1, v1, 0);
        }
        // 0x003bba14
        charge(ctx, 2);
        for (;;) {
            // 0x003bba28
            charge(ctx, 4);
            lwc1(f1, v1, 0);
            c_lt_s(f1, f0);
            if (!cond(ctx)) {
                break;
            }
            backedge(ctx);
            // 0x003bba1c
            charge(ctx, 3);
            lwc1(f1, v1, 0);
            add_s(f1, f1, f2);
            swc1(f1, v1, 0);
        }
        // 0x003bba38
        charge(ctx, 1);
        a1 = addiu(a1, 1);
    }
    // 0x003bba48
    charge(ctx, 9);
    lwc1(f0, sp, 0x0);
    swc1(f0, a0, 0);
    lwc1(f0, sp, 0x4);
    swc1(f0, a0, 4);
    lwc1(f0, sp, 0x8);
    swc1(f0, a0, 8);
    sp = addiu(sp, 0x10);
}

// 0x003BBA70 sub_3BBA70 -- 36 bytes; frame 0x10: ra sp+0x0
// (res) sub_3BB9B0 on the record's rotation (+16).
void sub_3BBA70(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bba70
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = addiu(a0, 16);
    jal(ctx, 0x3BBA7Cu, gen::fn_sub_3BB9B0_003bb9b0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003BBAA0 sub_3BBAA0 -- 228 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// [MT_SceneFunc_AngleDelta] (from, to, out) The per-axis turn from `from` to `to`: (to - from) wrapped to [0, 360),
// then values above 180 become negative (the shorter way).
void sub_3BBAA0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x003bbaa0
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a2;
    lwc1(f1, a1, 0);
    lwc1(f0, a0, 0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x30);
    lwc1(f1, a1, 4);
    lwc1(f0, a0, 4);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x34);
    lwc1(f1, a1, 8);
    lwc1(f0, a0, 8);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x38);
    a0 = addiu(sp, 0x30);
    jal(ctx, 0x3BBAE4u, gen::fn_sub_3BB9B0_003bb9b0);
    lwc1(f0, sp, 0x30);
    swc1(f0, sp, 0x20);
    lwc1(f0, sp, 0x34);
    swc1(f0, sp, 0x24);
    lwc1(f0, sp, 0x38);
    swc1(f0, sp, 0x28);
    a0 = 0;
    v1 = 0x43B40000;
    mtc1(v1, f1);
    v1 = 0x43340000;
    mtc1(v1, f2);
    for (;;) {
        // 0x003bbb4c
        charge(ctx, 3);
        v1 = slti(a0, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bbb20
        charge(ctx, 7);
        v1 = sll(a0, 2);
        v1 = addu(v1, sp);
        v1 = addiu(v1, 32);
        lwc1(f0, v1, 0);
        c_le_s(f0, f2);
        if (!cond(ctx)) {
            // 0x003bbb3c
            charge(ctx, 3);
            sub_s(f0, f1, f0);
            neg_s(f0, f0);
            swc1(f0, v1, 0);
        }
        // 0x003bbb48
        charge(ctx, 1);
        a0 = addiu(a0, 1);
    }
    // 0x003bbb58
    charge(ctx, 11);
    lwc1(f0, sp, 0x20);
    swc1(f0, s0, 0);
    lwc1(f0, sp, 0x24);
    swc1(f0, s0, 4);
    lwc1(f0, sp, 0x28);
    swc1(f0, s0, 8);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003BBC90 sub_3BBC90 -- 176 bytes; leaf frame (no stack)
// [MT_SceneFunc_Bezier] (xs, ys, zs, out_x, out_y, out_z, $f12 t) A cubic Bezier point: each coordinate = (1-t)^3 c0
// + 3t(1-t)^2 c1 + 3t^2(1-t) c2 + t^3 c3 (the four control values at +0..+12 of each array), through ACC (mula /
// madda / madd).
void sub_3BBC90(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f12{ctx, 12};
    // 0x003bbc90
    enter(ctx, 44);  // entry check point + this block's cycles
    v1 = 0x3F800000;
    mtc1(v1, f0);
    sub_s(f3, f0, f12);
    mul_s(f1, f3, f3);
    mul_s(f6, f3, f1);
    lwc1(f0, a0, 0);
    mula_s(f0, f6);
    v1 = 0x40400000;
    mtc1(v1, f2);
    mul_s(f0, f2, f1);
    mul_s(f5, f12, f0);
    lwc1(f0, a0, 4);
    madda_s(f0, f5);
    mul_s(f1, f12, f12);
    mul_s(f0, f2, f3);
    mul_s(f4, f0, f1);
    lwc1(f0, a0, 8);
    madda_s(f0, f4);
    mul_s(f3, f12, f1);
    lwc1(f0, a0, 12);
    madd_s(f2, f0, f3);
    lwc1(f0, a1, 0);
    mula_s(f0, f6);
    lwc1(f0, a1, 4);
    madda_s(f0, f5);
    lwc1(f0, a1, 8);
    madda_s(f0, f4);
    lwc1(f0, a1, 12);
    madd_s(f1, f0, f3);
    lwc1(f0, a2, 0);
    mula_s(f0, f6);
    lwc1(f0, a2, 4);
    madda_s(f0, f5);
    lwc1(f0, a2, 8);
    madda_s(f0, f4);
    lwc1(f0, a2, 12);
    madd_s(f0, f0, f3);
    swc1(f2, a3, 0);
    swc1(f1, t0, 0);
    swc1(f0, t1, 0);
}

// 0x003BBD40 sub_3BBD40 -- 400 bytes; frame 0x40: ra sp+0x0
// [MT_SceneFunc_PathPoint] (path, out, $f12 t) The point of a bezier path: t < 1 picks segment (int)(t / (1 / count))
// and evaluates it at (t minus whole steps of 1 / count while above one step) * count -- at an exact segment boundary
// that is the end (1.0) of the segment the division picked; t >= 1 gives the last segment's end point (local t 1.0).
// Nothing for an empty path.
void sub_3BBD40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x003bbd40
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x0);
    a3 = a1;
    lb(v1, a0, 0);
    if (i64(v1) > 0) {
        // 0x003bbd58
        charge(ctx, 6);
        v0 = 0x3F800000;
        mtc1(v0, f1);
        c_lt_s(f12, f1);
        if (cond(ctx)) {
            // 0x003bbdfc
            charge(ctx, 14);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            div_s(f1, f1, f0);
            div_s(f0, f12, f1);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            a1 = 0;
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            a0 = addu(a0, v0);
            for (;;) {
                // 0x003bbe68
                charge(ctx, 3);
                v0 = slti(a1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003bbe34
                charge(ctx, 13);
                v0 = sll(a1, 1);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v1 = addu(a0, v0);
                v0 = sll(a1, 2);
                lwc1(f0, v1, 4);
                v0 = addu(v0, sp);
                swc1(f0, v0, 48);
                lwc1(f0, v1, 8);
                swc1(f0, v0, 32);
                lwc1(f0, v1, 12);
                swc1(f0, v0, 16);
                a1 = addiu(a1, 1);
            }
            // 0x003bbe74
            charge(ctx, 2);
            for (;;) {
                // 0x003bbe80
                charge(ctx, 6);
                c_le_s(f12, f1);
                if (cond(ctx)) {
                    break;
                }
                backedge(ctx);
                // 0x003bbe7c
                charge(ctx, 1);
                sub_s(f12, f12, f1);
            }
            // 0x003bbe98
            charge(ctx, 10);
            div_s(f12, f12, f1);
            a0 = addiu(sp, 0x30);
            a1 = addiu(sp, 0x20);
            a2 = addiu(sp, 0x10);
            t0 = addiu(a3, 4);
            t1 = addiu(a3, 8);
            jal(ctx, 0x3BBEB8u, gen::fn_sub_3BBC90_003bbc90);
        } else {
            // 0x003bbd70
            charge(ctx, 8);
            a1 = 0;
            v1 = addiu(v1, -1);
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            a0 = addu(a0, v0);
            for (;;) {
                // 0x003bbdc4
                charge(ctx, 3);
                v0 = slti(a1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003bbd90
                charge(ctx, 13);
                v0 = sll(a1, 1);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v1 = addu(a0, v0);
                v0 = sll(a1, 2);
                lwc1(f0, v1, 4);
                v0 = addu(v0, sp);
                swc1(f0, v0, 48);
                lwc1(f0, v1, 8);
                swc1(f0, v0, 32);
                lwc1(f0, v1, 12);
                swc1(f0, v0, 16);
                a1 = addiu(a1, 1);
            }
            // 0x003bbdd0
            charge(ctx, 11);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            a0 = addiu(sp, 0x30);
            a1 = addiu(sp, 0x20);
            a2 = addiu(sp, 0x10);
            t0 = addiu(a3, 4);
            t1 = addiu(a3, 8);
            jal(ctx, 0x3BBDECu, gen::fn_sub_3BBC90_003bbc90);
        }
    }
    // 0x003bbec0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003BBFD0 sub_3BBFD0 -- 260 bytes; frame 0xA0: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// (xs, ys, zs, a, b) Two Bezier points (sub_3BBC90 at $f12 / $f13) into a and b and their distance (sub_4C6AC0) in
// $f0.
void sub_3BBFD0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20};
    // 0x003bbfd0
    enter(ctx, 65);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    mov_s(f20, f13);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    s0 = t0;
    a3 = addiu(sp, 0x9C);
    t0 = addiu(sp, 0x94);
    t1 = addiu(sp, 0x8C);
    jal(ctx, 0x3BC014u, gen::fn_sub_3BBC90_003bbc90);
    mov_s(f12, f20);
    a0 = s4;
    a1 = s3;
    a2 = s2;
    a3 = addiu(sp, 0x98);
    t0 = addiu(sp, 0x90);
    t1 = addiu(sp, 0x88);
    jal(ctx, 0x3BC038u, gen::fn_sub_3BBC90_003bbc90);
    lwc1(f1, sp, 0x98);
    lwc1(f0, sp, 0x9C);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x78);
    lwc1(f1, sp, 0x90);
    lwc1(f0, sp, 0x94);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x7C);
    lwc1(f1, sp, 0x88);
    lwc1(f0, sp, 0x8C);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x80);
    a0 = addiu(sp, 0x78);
    jal(ctx, 0x3BC074u, gen::fn_sub_4C6AC0_004c6ac0);
    lwc1(f1, sp, 0x9C);
    swc1(f1, s1, 0);
    lwc1(f1, sp, 0x94);
    swc1(f1, s1, 4);
    lwc1(f1, sp, 0x8C);
    swc1(f1, s1, 8);
    lwc1(f1, sp, 0x98);
    swc1(f1, s0, 0);
    lwc1(f1, sp, 0x90);
    swc1(f1, s0, 4);
    lwc1(f1, sp, 0x88);
    swc1(f1, s0, 8);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x003BC0E0 sub_3BC0E0 -- 308 bytes; frame 0xA0: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [MT_SceneFunc_PathLength] (path) The path length: per segment 20 chords (sub_3BBFD0); the total stays in $f21 for
// the caller.
void sub_3BC0E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21};
    // 0x003bc0e0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    mtc1(zero, f21);
    s0 = 0;
    for (;;) {
        // 0x003bc1dc
        charge(ctx, 4);
        lb(v0, s1, 0);
        v0 = slt(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bc110
        charge(ctx, 7);
        a1 = 0;
        v0 = sll(s0, 3);
        v0 = addu(v0, s0);
        v0 = sll(v0, 2);
        a0 = addu(s1, v0);
        for (;;) {
            // 0x003bc160
            charge(ctx, 3);
            v0 = slti(a1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003bc12c
            charge(ctx, 13);
            v0 = sll(a1, 1);
            v0 = addu(v0, a1);
            v0 = sll(v0, 2);
            v1 = addu(a0, v0);
            v0 = sll(a1, 2);
            lwc1(f0, v1, 4);
            v0 = addu(v0, sp);
            swc1(f0, v0, 112);
            lwc1(f0, v1, 8);
            swc1(f0, v0, 96);
            lwc1(f0, v1, 12);
            swc1(f0, v0, 80);
            a1 = addiu(a1, 1);
        }
        // 0x003bc16c
        charge(ctx, 4);
        mtc1(zero, f20);
        s2 = 0;
        for (;;) {
            // 0x003bc1c8
            charge(ctx, 3);
            v0 = slti(s2, 20);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003bc17c
            charge(ctx, 19);
            mtc1(s2, f0);
            cvt_s_w(f0, f0);
            lwc1(f1, gp, g::kGpPathZero);  // 0x7CB0B8 f32 0.0
            mul_s(f12, f0, f1);
            v0 = addiu(s2, 1);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            mul_s(f13, f0, f1);
            a0 = addiu(sp, 0x70);
            a1 = addiu(sp, 0x60);
            a2 = addiu(sp, 0x50);
            a3 = addiu(sp, 0x90);
            t0 = addiu(sp, 0x80);
            jal(ctx, 0x3BC1B8u, gen::fn_sub_3BBFD0_003bbfd0);
            add_s(f20, f20, f0);
            s2 = addiu(s2, 1);
        }
        // 0x003bc1d4
        charge(ctx, 2);
        add_s(f21, f21, f20);
        s0 = addiu(s0, 1);
    }
    // 0x003bc1ec
    charge(ctx, 10);
    mov_s(f0, f21);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x003BC730 sub_3BC730 -- 436 bytes; frame 0xD0: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [MT_SceneFunc_PathLengthTo] (path, n) The length of the first n segments (20 chords each), in $f20.
void sub_3BC730(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x003bc730
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    mtc1(zero, f20);
    s1 = 0;
    s2 = 0;
    for (;;) {
        // 0x003bc8a8
        charge(ctx, 4);
        lb(v0, s4, 0);
        v0 = slt(s2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bc76c
        charge(ctx, 2);
        if (s1 == s3) {
            goto L_003bc774_2;
        }
        // 0x003bc780
        charge(ctx, 5);
        a1 = 0;
        v0 = sll(s2, 1);
        a0 = addu(v0, s2);
        for (;;) {
            // 0x003bc7cc
            charge(ctx, 3);
            v0 = slti(a1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003bc794
            charge(ctx, 14);
            v1 = addu(a1, a0);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            v1 = addu(s4, v0);
            v0 = sll(a1, 2);
            lwc1(f0, v1, 4);
            v0 = addu(v0, sp);
            swc1(f0, v0, 144);
            lwc1(f0, v1, 8);
            swc1(f0, v0, 128);
            lwc1(f0, v1, 12);
            swc1(f0, v0, 112);
            a1 = addiu(a1, 1);
        }
        // 0x003bc7d8
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x003bc894
            charge(ctx, 3);
            v0 = slti(s0, 20);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003bc7e4
            charge(ctx, 44);
            mtc1(s0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, gp, g::kGpPathZero);  // 0x7CB0B8 f32 0.0
            mul_s(f12, f1, f0);
            a0 = addiu(sp, 0x90);
            a1 = addiu(sp, 0x80);
            a2 = addiu(sp, 0x70);
            a3 = addiu(sp, 0xCC);
            t0 = addiu(sp, 0xC4);
            t1 = addiu(sp, 0xBC);
            jal(ctx, 0x3BC810u, gen::fn_sub_3BBC90_003bbc90);
            v0 = addiu(s0, 1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, gp, g::kGpPathZero);  // 0x7CB0B8 f32 0.0
            mul_s(f12, f1, f0);
            a0 = addiu(sp, 0x90);
            a1 = addiu(sp, 0x80);
            a2 = addiu(sp, 0x70);
            a3 = addiu(sp, 0xC8);
            t0 = addiu(sp, 0xC0);
            t1 = addiu(sp, 0xB8);
            jal(ctx, 0x3BC848u, gen::fn_sub_3BBC90_003bbc90);
            lwc1(f1, sp, 0xC8);
            lwc1(f0, sp, 0xCC);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xA8);
            lwc1(f1, sp, 0xC0);
            lwc1(f0, sp, 0xC4);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xAC);
            lwc1(f1, sp, 0xB8);
            lwc1(f0, sp, 0xBC);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xB0);
            a0 = addiu(sp, 0xA8);
            jal(ctx, 0x3BC884u, gen::fn_sub_4C6AC0_004c6ac0);
            add_s(f20, f20, f0);
            s0 = addiu(s0, 1);
        }
        // 0x003bc8a0
        charge(ctx, 2);
        s1 = addiu(s1, 1);
        s2 = addiu(s2, 1);
    }
    // 0x003bc8b8
    charge(ctx, 1);
    mtc1(zero, f0);
    // 0x003bc8bc (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xD0);
    return;
L_003bc774_2:
    charge(ctx, 3);
    mov_s(f0, f20);
    // 0x003bc8bc (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x003BC8F0 sub_3BC8F0 -- 16 bytes; leaf frame (no stack)
// [MT_SceneFunc_PathLastSeg] (path) The path's segment count - 1.
void sub_3BC8F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x003bc8f0
    enter(ctx, 4);  // entry check point + this block's cycles
    lb(v0, a0, path::kCount);
    v0 = addiu(v0, -1);
}

// 0x003BC900 sub_3BC900 -- 60 bytes; leaf frame (no stack)
// (out) The reference point (0x95AFF0 / 0x95AFF4) when one is set (u16 0x7CE658): 1, else 0.
void sub_3BC900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28};
    Fpr f0{ctx, 0};
    // 0x003bc900
    enter(ctx, 3);  // entry check point + this block's cycles
    lhu(v0, gp, g::kGpRefPointSet);  // 0x7CE658 u16: a reference point is set
    if (v0 != 0) {
        // 0x003bc918
        charge(ctx, 7);
        v0 = 0x960000;
        lwc1(f0, v0, g::kLoRefPointX);  // 0x95AFF0 f32: the reference point x
        swc1(f0, a0, 0);
        v0 = 0x960000;
        lwc1(f0, v0, g::kLoRefPointZ);  // 0x95AFF4 f32: the reference point z
        swc1(f0, a0, 4);
        v0 = 1;
    } else {
        // 0x003bc90c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003bc934 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003BD0B0 sub_3BD0B0 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [MT_SceneFunc_CreateManagerTasks] Creates "SceneManager Task" (priority 110; update sub_3BCCB0, destroy sub_3BCD80)
// and its child "SceneManager Draw" (2109; sub_3BD010); returns the parent.
void sub_3BD0B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bd0b0
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 12128);  // "SceneManager Task"
    a2 = 110;
    a3 = 0x3C0000;
    a3 = addiu(a3, -13136);  // &sub_3BCCB0
    t0 = 0x3C0000;
    t0 = addiu(t0, -12928);  // &sub_3BCD80
    t1 = 0;
    jal(ctx, 0x3BD0E0u, gen::fn_kwlnTaskCreate_00194b20);
    s0 = v0;
    a0 = s0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 12160);  // "SceneManager Draw"
    a2 = 2109;
    a3 = 0x3C0000;
    a3 = addiu(a3, -12272);  // &sub_3BD010
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x3BD10Cu, gen::fn_kwlnTaskCreate_00194b20);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BD130 sub_3BD130 -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_SceneFunc_LoadIcons] Requests and reads the 25 icon EPL files of 0x6A3130 ("icon/ICON1.EPL" ..) into the H_Cdvd
// cache, keeping each request at 0x95B000 + 4 i (kwlnInitMain).
void sub_3BD130(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bd130
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    for (;;) {
        // 0x003bd194
        charge(ctx, 3);
        v1 = slti(s0, 25);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bd14c
        charge(ctx, 7);
        a1 = sll(s0, 2);
        v1 = 0x6A0000;
        v1 = addiu(v1, 12592);  // &0x6A3130
        v1 = addu(v1, a1);
        lw(a0, v1, 0);
        if (a0 != 0) {
            // 0x003bd168
            charge(ctx, 10);
            v0 = 0x960000;
            v0 = addiu(v0, -20480);  // &0x95B000
            s1 = addu(v0, a1);
            a1 = 0;
            jal(ctx, 0x3BD178u, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s1, 0);
            a0 = v0;
            jal(ctx, 0x3BD188u, gen::fn_H_Cdvd_ReadSync_001023a0);
        }
        // 0x003bd190
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x003bd1a0
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003BD1C0 sub_3BD1C0 -- 100 bytes; frame 0x20: ra sp+0x0
// [MT_SceneFunc_GetIconFile] (icon) The cached data of icon file `icon` (< 26 and named; H_Cdvd_CacheFindFile), else
// 0.
void sub_3BD1C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bd1c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    at = sltiu(a0, 26);
    if (at != 0) {
        // 0x003bd1e0
        charge(ctx, 7);
        v1 = sll(a0, 2);
        v0 = 0x6A0000;
        v0 = addiu(v0, 12592);  // &0x6A3130
        v0 = addu(v0, v1);
        lw(a0, v0, 0);
        if (a0 != 0) {
            // 0x003bd208
            charge(ctx, 3);
            a1 = addiu(sp, 0x1C);
            jal(ctx, 0x3BD20Cu, gen::fn_H_Cdvd_CacheFindFile_001021c0);
        } else {
            // 0x003bd1fc
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003bd1d4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003bd214 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
