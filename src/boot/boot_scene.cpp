// Phase 5 slice boot, part 3 (boot_scene.h): the scene-draw and shadow tasks, 0x199C60-0x19FF10. Started from
// p3fes_handgen's bodies (register for register, block for block as the recompiled ones; game/include/p3fes/game/
// hg_cpu.h) and made readable on top: a role comment per function, structured control flow, block roles. Every path
// keeps the original's statements, charges and check points in order; tests/game/test_boot_scene.cpp pairs them.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/boot_scene.h"

namespace p3fes::recomp_gen {
void fn_K_Field_Get_001b9120(p3fes::EEContext&);
void fn_K_FldSrc_DrawFieldOpaque_001b3e50(p3fes::EEContext&);
void fn_K_FldSrc_DrawFieldTrans_001b4720(p3fes::EEContext&);
void fn_K_SceneDraw_CreateTasks_0019f730(p3fes::EEContext&);
void fn_K_SceneDraw_UpdateDrwOpcFldTask_0019d410(p3fes::EEContext&);
void fn_RpSkyRenderStateSet_004d7f60(p3fes::EEContext&);
void fn_RwCameraBeginUpdate_004c9d10(p3fes::EEContext&);
void fn_RwCameraClear_004c9e90(p3fes::EEContext&);
void fn_RwCameraEndUpdate_004c9d00(p3fes::EEContext&);
void fn_atomicGetWorldBoundingSphere_004912b0(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_drawGradientQuad_001997e0(p3fes::EEContext&);
void fn_geometryLock_00493370(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_qsort_005225f8(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sub_198540_00198540(p3fes::EEContext&);
void fn_sub_198560_00198560(p3fes::EEContext&);
void fn_sub_198570_00198570(p3fes::EEContext&);
void fn_sub_198580_00198580(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_1985B0_001985b0(p3fes::EEContext&);
void fn_sub_1985D0_001985d0(p3fes::EEContext&);
void fn_sub_199C60_00199c60(p3fes::EEContext&);
void fn_sub_199CF0_00199cf0(p3fes::EEContext&);
void fn_sub_19AB30_0019ab30(p3fes::EEContext&);
void fn_sub_19AB80_0019ab80(p3fes::EEContext&);
void fn_sub_19B2B0_0019b2b0(p3fes::EEContext&);
void fn_sub_19BEB0_0019beb0(p3fes::EEContext&);
void fn_sub_19C320_0019c320(p3fes::EEContext&);
void fn_sub_19C4B0_0019c4b0(p3fes::EEContext&);
void fn_sub_19D270_0019d270(p3fes::EEContext&);
void fn_sub_19D2A0_0019d2a0(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_19D4A0_0019d4a0(p3fes::EEContext&);
void fn_sub_19DB10_0019db10(p3fes::EEContext&);
void fn_sub_19DE40_0019de40(p3fes::EEContext&);
void fn_sub_19DE80_0019de80(p3fes::EEContext&);
void fn_sub_19E1B0_0019e1b0(p3fes::EEContext&);
void fn_sub_19E1F0_0019e1f0(p3fes::EEContext&);
void fn_sub_19E330_0019e330(p3fes::EEContext&);
void fn_sub_19EE40_0019ee40(p3fes::EEContext&);
void fn_sub_19F8F0_0019f8f0(p3fes::EEContext&);
void fn_sub_19FDD0_0019fdd0(p3fes::EEContext&);
void fn_sub_19FE20_0019fe20(p3fes::EEContext&);
void fn_sub_19FE70_0019fe70(p3fes::EEContext&);
void fn_sub_19FEC0_0019fec0(p3fes::EEContext&);
void fn_sub_19FF10_0019ff10(p3fes::EEContext&);
void fn_sub_1A0040_001a0040(p3fes::EEContext&);
void fn_sub_1A01C0_001a01c0(p3fes::EEContext&);
void fn_sub_1A0A50_001a0a50(p3fes::EEContext&);
void fn_sub_1A0D80_001a0d80(p3fes::EEContext&);
void fn_sub_1B56F0_001b56f0(p3fes::EEContext&);
void fn_sub_1B5950_001b5950(p3fes::EEContext&);
void fn_sub_1B5990_001b5990(p3fes::EEContext&);
void fn_sub_1B59C0_001b59c0(p3fes::EEContext&);
void fn_sub_1B5A00_001b5a00(p3fes::EEContext&);
void fn_sub_1BD950_001bd950(p3fes::EEContext&);
void fn_sub_316F70_00316f70(p3fes::EEContext&);
void fn_sub_3176C0_003176c0(p3fes::EEContext&);
void fn_sub_317A20_00317a20(p3fes::EEContext&);
void fn_sub_318A90_00318a90(p3fes::EEContext&);
void fn_sub_318AD0_00318ad0(p3fes::EEContext&);
void fn_sub_318B00_00318b00(p3fes::EEContext&);
void fn_sub_318B60_00318b60(p3fes::EEContext&);
void fn_sub_318B80_00318b80(p3fes::EEContext&);
void fn_sub_318B90_00318b90(p3fes::EEContext&);
void fn_sub_318ED0_00318ed0(p3fes::EEContext&);
void fn_sub_319010_00319010(p3fes::EEContext&);
void fn_sub_319230_00319230(p3fes::EEContext&);
void fn_sub_34FD70_0034fd70(p3fes::EEContext&);
void fn_sub_34FDF0_0034fdf0(p3fes::EEContext&);
void fn_sub_3B5D10_003b5d10(p3fes::EEContext&);
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);
void fn_sub_464120_00464120(p3fes::EEContext&);
void fn_sub_4916D0_004916d0(p3fes::EEContext&);
void fn_sub_491880_00491880(p3fes::EEContext&);
void fn_sub_4919B0_004919b0(p3fes::EEContext&);
void fn_sub_492D10_00492d10(p3fes::EEContext&);
void fn_sub_492E20_00492e20(p3fes::EEContext&);
void fn_sub_493210_00493210(p3fes::EEContext&);
void fn_sub_493230_00493230(p3fes::EEContext&);
void fn_sub_4933D0_004933d0(p3fes::EEContext&);
void fn_sub_493710_00493710(p3fes::EEContext&);
void fn_sub_493B60_00493b60(p3fes::EEContext&);
void fn_sub_4944B0_004944b0(p3fes::EEContext&);
void fn_sub_494BE0_00494be0(p3fes::EEContext&);
void fn_sub_49C160_0049c160(p3fes::EEContext&);
void fn_sub_4C2CC0_004c2cc0(p3fes::EEContext&);
void fn_sub_4C2D20_004c2d20(p3fes::EEContext&);
void fn_sub_4C2F10_004c2f10(p3fes::EEContext&);
void fn_sub_4C2FB0_004c2fb0(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4C9D70_004c9d70(p3fes::EEContext&);
void fn_sub_4C9DB0_004c9db0(p3fes::EEContext&);
void fn_sub_4C9F00_004c9f00(p3fes::EEContext&);
void fn_sub_4C9F90_004c9f90(p3fes::EEContext&);
void fn_sub_4CA030_004ca030(p3fes::EEContext&);
void fn_sub_4CA090_004ca090(p3fes::EEContext&);
void fn_sub_4CAF10_004caf10(p3fes::EEContext&);
void fn_sub_4CAF80_004caf80(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4CB750_004cb750(p3fes::EEContext&);
void fn_sub_4CB7F0_004cb7f0(p3fes::EEContext&);
void fn_sub_4CB930_004cb930(p3fes::EEContext&);
void fn_sub_4CDE90_004cde90(p3fes::EEContext&);
void fn_sub_4CE0F0_004ce0f0(p3fes::EEContext&);
void fn_sub_4D0BE0_004d0be0(p3fes::EEContext&);
void fn_sub_4D0E40_004d0e40(p3fes::EEContext&);
void fn_sub_4D1840_004d1840(p3fes::EEContext&);
void fn_sub_4F1780_004f1780(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x00199C60 sub_199C60 -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_199C60(camera) [K_Shadow_DestroyCamera]: destroys a shadow camera (k_shadow.c): when non-null, its frame
// (camera +4: detached with sub_4D1840(camera, 0) and destroyed with sub_4CAF80), its Z raster (+100, cleared and
// destroyed with sub_4CDE90), clears the frame-buffer word (+96, the texture's raster, not owned), then the camera
// (sub_4CA030).
void sub_199C60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00199c60
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    if (s1 != 0) {
        // 0x00199c7c
        charge(ctx, 3);
        lw(s0, s1, 4);
        if (s0 != 0) {
            // 0x00199c88
            charge(ctx, 6);
            a1 = 0;
            jal(ctx, 0x199C8Cu, gen::fn_sub_4D1840_004d1840);
            a0 = s0;
            jal(ctx, 0x199C98u, gen::fn_sub_4CAF80_004caf80);
        }
        // 0x00199ca0
        charge(ctx, 3);
        lw(a0, s1, 100);
        if (a0 != 0) {
            // 0x00199cac
            charge(ctx, 3);
            sw(zero, s1, 100);
            jal(ctx, 0x199CB0u, gen::fn_sub_4CDE90_004cde90);
        }
        // 0x00199cb8
        charge(ctx, 3);
        lw(v0, s1, 96);
        if (v0 != 0) {
            // 0x00199cc4
            charge(ctx, 1);
            sw(zero, s1, 96);
        }
        // 0x00199cc8
        charge(ctx, 3);
        a0 = s1;
        jal(ctx, 0x199CCCu, gen::fn_sub_4CA030_004ca030);
    }
    // 0x00199cd4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00199CF0 sub_199CF0 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_199CF0(atomic, acc) [K_Shadow_AccumulateBounds]: a clump's atomic callback: keeps the atomic with the largest
// world bounding sphere (atomicGetWorldBoundingSphere) -- acc +0..+8 its centre, +20 the atomic -- while acc +12 sums
// the radii and acc +16 counts the atomics; returns the atomic (continue).
void sub_199CF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x00199cf0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    jal(ctx, 0x199D08u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
    lwc1(f1, v0, 12);
    lwc1(f0, s0, 12);
    c_le_s(f1, f0);
    if (!cond(ctx)) {
        // 0x00199d24
        charge(ctx, 10);
        a0 = s1;
        jal(ctx, 0x199D28u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
        lwc1(f2, v0, 0);
        lwc1(f1, v0, 4);
        lwc1(f0, v0, 8);
        swc1(f2, s0, 0);
        swc1(f1, s0, 4);
        swc1(f0, s0, 8);
        sw(s1, s0, 20);
    }
    // 0x00199d4c
    charge(ctx, 17);
    a0 = s1;
    jal(ctx, 0x199D50u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
    lwc1(f1, v0, 12);
    lwc1(f0, s0, 12);
    add_s(f0, f0, f1);
    swc1(f0, s0, 12);
    lw(v0, s0, 16);
    v0 = addiu(v0, 1);
    sw(v0, s0, 16);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0019AB30 sub_19AB30 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_19AB30(atomic, data) [K_Shadow_AtomicCallback]: data +8 = atomic, then sub_464120 on it; returns the atomic.
// Installed by the shadow renderer (data reference; sub_19A420 beside it).
void sub_19AB30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0019ab30
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a3 = a1;
    sw(s0, a1, 8);
    lw(a1, a1, 0);
    a2 = 0x1A0000;
    a2 = addiu(a2, -23520);  // &sub_19A420
    jal(ctx, 0x19AB54u, gen::fn_sub_464120_00464120);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0019B2B0 sub_19B2B0 -- 2616 bytes; frame 0x180: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_19B2B0(task) [K_Shadow_UpdateRenderTexTask] ("renderTex for shadow", made by sub_19BEB0): one character's
// shadow. Work (140 bytes): +0 step, +4 paused (1: nothing), +8 owner id, +10 kind, +12 the owner resource, +16 its
// model, +20 / +24 size, +44..+56 centre, +60..+72 the rendered kind's texture, raster, camera and buffer, +76 the
// disc record. Runs only while the owner is visible (flag word +40 bit 1).
//   step 0 (set-up, once the model is ready: sub_316F70): kind 1 measures the model (the clump walk sub_4916D0 with
//     sub_199CF0: the biggest atomic's bounding sphere -> centre with x = z = 0, size 90); kind 2 sub_319010(model);
//     kinds 3 / 4 build the disc: a material with the colour 0x7CC140..0x7CC143 (sub_494BE0), a geometry of 34
//     vertices and 32 triangles (sub_493710(34, 32, 74): a fan around the centre (0, 5, 0) with radius *+76 and the
//     angle step 0x7CAF04), vertex colours, its bounding sphere (sub_492E20), an atomic (sub_491880 / sub_4919B0)
//     with a frame (sub_4CAF10 / sub_492D10); kind 0 goes straight to step 1; then step 1;
//   step 1 (every frame): draws the shadow by kind -- the rendered texture projected around the model's position,
//     the disc atomic placed under the model (sub_4C2CC0 / sub_4C2D20 / sub_4C2F10, sub_4CB750) and drawn on the main
//     camera between RwCameraBeginUpdate / RwCameraEndUpdate with the render states set for it;
//   step 2: -1 (the task ends).
void sub_19B2B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20};
    // 0x0019b2b0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x180);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    lw(s0, a0, 60);
    lw(v0, s0, 12);
    lw(v0, v0, 40);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x0019b2f4
        charge(ctx, 4);
        lw(v0, s0, 4);
        a2 = 1;
        if (v0 != a2) {
            // 0x0019b310
            charge(ctx, 4);
            lw(a1, s0, 0);
            a0 = 2;
            if (a1 == a0) {
                // 0x0019bcb0
                charge(ctx, 3);
                v0 = si(-1);
            } else {
                // 0x0019b320
                charge(ctx, 2);
                if (a1 == a2) {
                    // 0x0019b6fc
                    charge(ctx, 4);
                    lhu(v1, s0, 10);
                    v0 = 3;
                    bool disc_draw = true;  // host-side: kinds 3 / 4 end with the disc draw (0x19bb88)
                    if (v1 != v0) {
                        // 0x0019b70c
                        charge(ctx, 3);
                        v0 = 4;
                        if (v1 == v0) {
                            // 0x0019b91c
                            charge(ctx, 7);
                            jal(ctx, 0x19B91Cu, gen::fn_sub_198590_00198590);
                            a0 = v0;
                            jal(ctx, 0x19B928u, gen::fn_RwCameraBeginUpdate_004c9d10);
                            if (v0 != 0) {
                                // 0x0019b938
                                charge(ctx, 4);
                                v1 = addiu(sp, 0x170);
                                v0 = 12;
                                if (v1 != 0) {
                                    for (;;) {
                                        // 0x0019b948
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
                                // 0x0019b964
                                charge(ctx, 5);
                                lw(a0, s0, 16);
                                jal(ctx, 0x19B968u, gen::fn_sub_318B60_00318b60);
                                a2 = addiu(sp, 0xB0);
                                a1 = 8;
                                for (;;) {
                                    // 0x0019b978
                                    charge(ctx, 9);
                                    lw(a0, v0, 0);
                                    lw(v1, v0, 4);
                                    v0 = addiu(v0, 8);
                                    a1 = addiu(a1, -1);
                                    sw(a0, a2, 0);
                                    sw(v1, a2, 4);
                                    a2 = addiu(a2, 8);
                                    if (i64(a1) <= 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x0019b99c
                                charge(ctx, 3);
                                a1 = addiu(sp, 0xB0);
                                a0 = addiu(sp, 0x70);
                                v1 = 4;
                                for (;;) {
                                    // 0x0019b9a8
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
                                // 0x0019b9c4
                                charge(ctx, 5);
                                lwc1(f1, s0, 128);
                                lwc1(f0, s0, 136);
                                c_le_s(f1, f0);
                                if (cond(ctx)) {
                                    // 0x0019ba08
                                    charge(ctx, 10);
                                    v0 = lui(0xBF80);
                                    sw(v0, sp, 0x160);
                                    v0 = 0x3F800000;
                                    sw(v0, sp, 0x164);
                                    sw(v0, sp, 0x168);
                                    lwc1(f0, s0, 116);
                                    add_s(f1, f0, f0);
                                    lwc1(f0, sp, 0xA0);
                                    sub_s(f0, f1, f0);
                                    swc1(f0, sp, 0xA0);
                                } else {
                                    // 0x0019b9d8
                                    charge(ctx, 12);
                                    v0 = 0x3F800000;
                                    sw(v0, sp, 0x160);
                                    sw(v0, sp, 0x164);
                                    v0 = lui(0xBF80);
                                    sw(v0, sp, 0x168);
                                    lwc1(f0, s0, 124);
                                    add_s(f1, f0, f0);
                                    lwc1(f0, sp, 0xA8);
                                    sub_s(f0, f1, f0);
                                    swc1(f0, sp, 0xA8);
                                }
                                // 0x0019ba30
                                charge(ctx, 62);
                                lw(v1, s0, 16);
                                lhu(v0, v1, 216);
                                v0 = v0 | 0x4;
                                sh(v0, v1, 216);
                                lw(a0, s0, 16);
                                a1 = addiu(sp, 0x160);
                                a2 = 2;
                                jal(ctx, 0x19BA4Cu, gen::fn_sub_318A90_00318a90);
                                lw(a0, s0, 16);
                                jal(ctx, 0x19BA58u, gen::fn_sub_318B60_00318b60);
                                lwc1(f2, sp, 0xA0);
                                lwc1(f1, sp, 0xA4);
                                lwc1(f0, sp, 0xA8);
                                swc1(f2, v0, 48);
                                swc1(f1, v0, 52);
                                swc1(f0, v0, 56);
                                a0 = addiu(sp, 0x150);
                                jal(ctx, 0x19BA7Cu, gen::fn_sub_4C2CC0_004c2cc0);
                                lw(a0, s0, 16);
                                jal(ctx, 0x19BA88u, gen::fn_sub_318B60_00318b60);
                                a0 = v0;
                                a1 = addiu(sp, 0x150);
                                jal(ctx, 0x19BA98u, gen::fn_sub_4C2D20_004c2d20);
                                lw(a0, s0, 16);
                                jal(ctx, 0x19BAA4u, gen::fn_sub_318B60_00318b60);
                                a0 = v0;
                                jal(ctx, 0x19BAB0u, gen::fn_sub_4C2F10_004c2f10);
                                lw(v1, s0, 16);
                                lhu(v0, v1, 216);
                                v0 = v0 | 0x40;
                                sh(v0, v1, 216);
                                lw(a0, s0, 16);
                                jal(ctx, 0x19BACCu, gen::fn_sub_3176C0_003176c0);
                                lw(a0, s0, 16);
                                jal(ctx, 0x19BAD8u, gen::fn_sub_318B90_00318b90);
                                lw(a0, s0, 16);
                                jal(ctx, 0x19BAE4u, gen::fn_sub_317A20_00317a20);
                                lw(v1, s0, 16);
                                lhu(v0, v1, 216);
                                v0 = v0 & 0xFFBF;
                                sh(v0, v1, 216);
                                a0 = 20;
                                a1 = 2;
                                v0 = 0x960000;
                                lw(v0, v0, 144);  // pfn_RwRenderStateSet
                                jalr(ctx, 0x19BB0Cu, v0.u());
                                lw(a0, s0, 16);
                                jal(ctx, 0x19BB18u, gen::fn_sub_318B60_00318b60);
                                a2 = addiu(sp, 0xB0);
                                a1 = 8;
                                for (;;) {
                                    // 0x0019bb28
                                    charge(ctx, 9);
                                    lw(a0, a2, 0);
                                    lw(v1, a2, 4);
                                    a2 = addiu(a2, 8);
                                    a1 = addiu(a1, -1);
                                    sw(a0, v0, 0);
                                    sw(v1, v0, 4);
                                    v0 = addiu(v0, 8);
                                    if (i64(a1) <= 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x0019bb4c
                                charge(ctx, 15);
                                lw(v1, s0, 16);
                                lhu(v0, v1, 216);
                                v0 = v0 & 0xFFFB;
                                sh(v0, v1, 216);
                                lw(a0, s0, 16);
                                jal(ctx, 0x19BB60u, gen::fn_sub_3176C0_003176c0);
                                lw(a0, s0, 16);
                                jal(ctx, 0x19BB6Cu, gen::fn_sub_318B90_00318b90);
                                jal(ctx, 0x19BB74u, gen::fn_sub_198590_00198590);
                                a0 = v0;
                                jal(ctx, 0x19BB80u, gen::fn_RwCameraEndUpdate_004c9d00);
                            }
                        } else {
                            // 0x0019b718
                            charge(ctx, 2);
                            if (v1 != a0) {
                                // 0x0019b720
                                charge(ctx, 2);
                                if (v1 == a2) {
                                    // 0x0019b738
                                    charge(ctx, 45);
                                    sw(v0, sp, 0x138);
                                    lwc1(f20, s0, 24);
                                    lw(a0, s0, 16);
                                    jal(ctx, 0x19B744u, gen::fn_sub_318B60_00318b60);
                                    lwc1(f0, v0, 48);
                                    add_s(f0, f20, f0);
                                    swc1(f0, sp, 0x120);
                                    lw(a0, s0, 16);
                                    jal(ctx, 0x19B75Cu, gen::fn_sub_318B60_00318b60);
                                    lwc1(f0, v0, 52);
                                    add_s(f0, f20, f0);
                                    swc1(f0, sp, 0x124);
                                    lw(a0, s0, 16);
                                    jal(ctx, 0x19B774u, gen::fn_sub_318B60_00318b60);
                                    lwc1(f0, v0, 56);
                                    add_s(f0, f20, f0);
                                    swc1(f0, sp, 0x128);
                                    lw(a0, s0, 16);
                                    jal(ctx, 0x19B78Cu, gen::fn_sub_318B60_00318b60);
                                    lwc1(f0, v0, 48);
                                    sub_s(f0, f0, f20);
                                    swc1(f0, sp, 0x12C);
                                    lw(a0, s0, 16);
                                    jal(ctx, 0x19B7A4u, gen::fn_sub_318B60_00318b60);
                                    lwc1(f0, v0, 52);
                                    sub_s(f0, f0, f20);
                                    swc1(f0, sp, 0x130);
                                    lw(a0, s0, 16);
                                    jal(ctx, 0x19B7BCu, gen::fn_sub_318B60_00318b60);
                                    lwc1(f0, v0, 56);
                                    sub_s(f0, f0, f20);
                                    swc1(f0, sp, 0x134);
                                    jal(ctx, 0x19B7D0u, gen::fn_sub_198590_00198590);
                                    a0 = v0;
                                    jal(ctx, 0x19B7DCu, gen::fn_RwCameraBeginUpdate_004c9d10);
                                    if (v0 != 0) {
                                        // 0x0019b7ec
                                        charge(ctx, 13);
                                        a0 = 12;
                                        jal(ctx, 0x19B7F0u, gen::fn_sub_3B5D50_003b5d50);
                                        s2 = v0;
                                        s1 = 0x960000;
                                        s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
                                        a0 = 14;
                                        a1 = 0;
                                        lw(v0, s1, 0);  // pfn_RwRenderStateSet
                                        jalr(ctx, 0x19B810u, v0.u());
                                        if (s2 != 0) {
                                            // 0x0019b820
                                            charge(ctx, 5);
                                            lw(v0, s2, 352);
                                            lw(v0, v0, 0);
                                            v0 = v0 & 0x1;
                                            if (v0 == 0) {
                                                // 0x0019b874
                                                charge(ctx, 27);
                                                v0 = 3;
                                                sw(v0, sp, 0x138);
                                                lw(a0, s0, 16);
                                                jal(ctx, 0x19B880u, gen::fn_sub_318B60_00318b60);
                                                a3 = addiu(sp, 0x120);
                                                lwc1(f2, v0, 48);
                                                lwc1(f1, v0, 52);
                                                lwc1(f0, v0, 56);
                                                swc1(f2, sp, 0x120);
                                                swc1(f1, sp, 0x124);
                                                swc1(f0, sp, 0x128);
                                                lwc1(f1, s0, 24);
                                                swc1(f1, sp, 0x12C);
                                                v0 = 0x3F800000;
                                                mtc1(v0, f12);
                                                v0 = 0x40000000;
                                                mtc1(v0, f0);
                                                div_s(f13, f1, f0);
                                                lw(a0, s0, 68);
                                                lw(a1, s0, 64);
                                                a2 = 1;
                                                t0 = 0;
                                                lw(t1, s0, 72);
                                                jal(ctx, 0x19B8D8u, gen::fn_sub_19AB80_0019ab80);
                                            } else {
                                                // 0x0019b834
                                                charge(ctx, 16);
                                                v0 = 0x3F800000;
                                                mtc1(v0, f12);
                                                v0 = 0x40000000;
                                                mtc1(v0, f1);
                                                lwc1(f0, s0, 24);
                                                div_s(f13, f0, f1);
                                                lw(a0, s0, 68);
                                                lw(a1, s0, 64);
                                                a2 = 0;
                                                a3 = addiu(sp, 0x120);
                                                t0 = 0;
                                                lw(t1, s0, 72);
                                                jal(ctx, 0x19B864u, gen::fn_sub_19AB80_0019ab80);
                                            }
                                            // 0x0019b8e0
                                            charge(ctx, 4);
                                            lw(v0, gp, -19484);  // 0x7CE0D4
                                            a1 = 1;
                                            if (v0 == a1) {
                                                // 0x0019b8f0
                                                charge(ctx, 4);
                                                a0 = 14;
                                                lw(v0, s1, 0);
                                                jalr(ctx, 0x19B8F8u, v0.u());
                                            }
                                            // 0x0019b900
                                            charge(ctx, 7);
                                            jal(ctx, 0x19B900u, gen::fn_sub_198590_00198590);
                                            a0 = v0;
                                            jal(ctx, 0x19B90Cu, gen::fn_RwCameraEndUpdate_004c9d00);
                                        }
                                    }
                                } else {
                                    // 0x0019b728
                                    charge(ctx, 2);
                                    if (v1 != 0) {
                                        // 0x0019b730
                                        charge(ctx, 2);
                                    }
                                }
                            }
                            disc_draw = false;
                        }
                    }
                    if (disc_draw) {
                        // 0x0019bb88: the disc under the model's position
                        charge(ctx, 23);
                        lw(a0, s0, 16);
                        jal(ctx, 0x19BB8Cu, gen::fn_sub_318B60_00318b60);
                        a1 = addiu(sp, 0x140);
                        lwc1(f2, v0, 48);
                        lwc1(f1, v0, 52);
                        lwc1(f0, v0, 56);
                        swc1(f2, sp, 0x140);
                        swc1(f1, sp, 0x144);
                        swc1(f0, sp, 0x148);
                        lw(v0, s0, 76);
                        lw(v0, v0, 4);
                        lw(a0, v0, 4);
                        a2 = 0;
                        jal(ctx, 0x19BBC0u, gen::fn_sub_4CB750_004cb750);
                        jal(ctx, 0x19BBC8u, gen::fn_sub_198590_00198590);
                        a0 = v0;
                        jal(ctx, 0x19BBD4u, gen::fn_RwCameraBeginUpdate_004c9d10);
                        if (v0 != 0) {
                            // 0x0019bbe4
                            charge(ctx, 40);
                            s1 = 0x960000;
                            s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
                            a0 = 7;
                            a1 = 2;
                            lw(v0, s1, 0);  // pfn_RwRenderStateSet
                            jalr(ctx, 0x19BBF8u, v0.u());
                            a0 = 6;
                            a1 = 1;
                            lw(v0, s1, 0);  // pfn_RwRenderStateSet
                            jalr(ctx, 0x19BC0Cu, v0.u());
                            a0 = 8;
                            a1 = 0;
                            lw(v0, s1, 0);  // pfn_RwRenderStateSet
                            jalr(ctx, 0x19BC20u, v0.u());
                            a0 = 14;
                            a1 = 0;
                            lw(v0, s1, 0);  // pfn_RwRenderStateSet
                            jalr(ctx, 0x19BC34u, v0.u());
                            a0 = 2;
                            a1 = 68;
                            jal(ctx, 0x19BC44u, gen::fn_RpSkyRenderStateSet_004d7f60);
                            a0 = 3;
                            v0 = 0x70000;
                            a1 = v0 | 0x17FB;
                            jal(ctx, 0x19BC58u, gen::fn_RpSkyRenderStateSet_004d7f60);
                            lw(v0, s0, 76);
                            lw(a0, v0, 4);
                            lw(v0, a0, 72);
                            jalr(ctx, 0x19BC6Cu, v0.u());
                            lw(v0, gp, -19484);  // 0x7CE0D4
                            a1 = 1;
                            if (v0 == a1) {
                                // 0x0019bc84
                                charge(ctx, 4);
                                a0 = 14;
                                lw(v0, s1, 0);
                                jalr(ctx, 0x19BC8Cu, v0.u());
                            }
                            // 0x0019bc94
                            charge(ctx, 7);
                            jal(ctx, 0x19BC94u, gen::fn_sub_198590_00198590);
                            a0 = v0;
                            jal(ctx, 0x19BCA0u, gen::fn_RwCameraEndUpdate_004c9d00);
                        }
                    }
                } else {
                    // 0x0019b328
                    charge(ctx, 2);
                    if (a1 == 0) {
                        // 0x0019b338
                        charge(ctx, 4);
                        lhu(v1, s0, 10);
                        v0 = 3;
                        bool disc_setup = true;  // host-side: kinds 3 / 4 build the disc (0x19b450)
                        if (v1 != v0) {
                            // 0x0019b348
                            charge(ctx, 3);
                            v0 = 4;
                            disc_setup = v1 == v0;
                            if (!disc_setup) {
                                // 0x0019b354
                                charge(ctx, 2);
                                if (v1 == a0) {
                                    // 0x0019b41c
                                    charge(ctx, 5);
                                    lw(a0, s0, 16);
                                    jal(ctx, 0x19B420u, gen::fn_sub_316F70_00316f70);
                                    if (v0 != 0) {
                                        // 0x0019b430
                                        charge(ctx, 8);
                                        lw(a0, s0, 16);
                                        jal(ctx, 0x19B434u, gen::fn_sub_319010_00319010);
                                        lw(v0, s0, 0);
                                        v0 = addiu(v0, 1);
                                        sw(v0, s0, 0);
                                    }
                                } else {
                                    // 0x0019b35c
                                    charge(ctx, 2);
                                    if (v1 == a2) {
                                        // 0x0019b384
                                        charge(ctx, 5);
                                        lw(a0, s0, 16);
                                        jal(ctx, 0x19B388u, gen::fn_sub_316F70_00316f70);
                                        if (v0 != 0) {
                                            // 0x0019b398
                                            charge(ctx, 33);
                                            a0 = addiu(sp, 0x100);
                                            a1 = 0;
                                            a2 = 24;
                                            jal(ctx, 0x19B3A4u, gen::fn_memset_00521408);
                                            lw(a0, s0, 16);
                                            jal(ctx, 0x19B3B0u, gen::fn_sub_318B80_00318b80);
                                            a0 = v0;
                                            a1 = 0x1A0000;
                                            a1 = addiu(a1, -25360);  // &sub_199CF0
                                            a2 = addiu(sp, 0x100);
                                            jal(ctx, 0x19B3C8u, gen::fn_sub_4916D0_004916d0);
                                            lw(v0, sp, 0x114);
                                            sw(v0, s0, 20);
                                            v0 = 0x42B40000;
                                            sw(v0, s0, 24);
                                            lwc1(f2, sp, 0x100);
                                            lwc1(f1, sp, 0x104);
                                            lwc1(f0, sp, 0x108);
                                            swc1(f2, s0, 44);
                                            swc1(f1, s0, 48);
                                            swc1(f0, s0, 52);
                                            sw(zero, s0, 44);
                                            sw(zero, s0, 52);
                                            lwc1(f0, sp, 0x10C);
                                            swc1(f0, s0, 56);
                                            lw(v0, s0, 0);
                                            v0 = addiu(v0, 1);
                                            sw(v0, s0, 0);
                                        }
                                    } else {
                                        // 0x0019b364
                                        charge(ctx, 2);
                                        if (v1 == 0) {
                                            // 0x0019b374
                                            charge(ctx, 4);
                                            v0 = addiu(a1, 1);
                                            sw(v0, s0, 0);
                                        } else {
                                            // 0x0019b36c
                                            charge(ctx, 2);
                                        }
                                    }
                                }
                            }
                        }
                        if (disc_setup) {
                            // 0x0019b450: kinds 3 / 4 -- the disc geometry, atomic and frame, once the model is ready
                            charge(ctx, 5);
                            lw(a0, s0, 16);
                            jal(ctx, 0x19B454u, gen::fn_sub_316F70_00316f70);
                            if (v0 != 0) {
                                // 0x0019b464
                                charge(ctx, 24);
                                jal(ctx, 0x19B464u, gen::fn_sub_494BE0_00494be0);
                                lw(v1, s0, 76);
                                sw(v0, v1, 8);
                                lw(v0, s0, 76);
                                lw(a2, v0, 8);
                                lbu(a1, gp, -27568);  // 0x7CC140
                                lbu(a0, gp, -27567);  // 0x7CC141
                                lbu(v1, gp, -27566);  // 0x7CC142
                                lbu(v0, gp, -27565);  // 0x7CC143
                                sb(a1, a2, 4);
                                sb(a0, a2, 5);
                                sb(v1, a2, 6);
                                sb(v0, a2, 7);
                                a0 = 34;
                                a1 = 32;
                                a2 = 74;
                                jal(ctx, 0x19B4A8u, gen::fn_sub_493710_00493710);
                                s1 = v0;
                                lw(s3, v0, 44);
                                s2 = 0;
                                for (;;) {
                                    // 0x0019b508
                                    charge(ctx, 3);
                                    v0 = slti(s2, 32);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x0019b4c4
                                    charge(ctx, 17);
                                    v0 = addiu(s2, 2);
                                    a3 = v0 & 0xFFFF;
                                    v0 = addiu(s2, 1);
                                    t0 = v0 & 0xFFFF;
                                    a0 = s1;
                                    a1 = s3;
                                    a2 = 0;
                                    jal(ctx, 0x19B4E0u, gen::fn_sub_493210_00493210);
                                    lw(v0, s0, 76);
                                    a0 = s1;
                                    a1 = s3;
                                    lw(a2, v0, 8);
                                    jal(ctx, 0x19B4F8u, gen::fn_sub_493230_00493230);
                                    s3 = addiu(s3, 8);
                                    s2 = addiu(s2, 1);
                                }
                                // 0x0019b514
                                charge(ctx, 10);
                                lw(v0, s1, 92);
                                lw(s3, v0, 20);
                                mtc1(zero, f20);
                                sw(zero, s3, 0);
                                v0 = 0x40A00000;
                                sw(v0, s3, 4);
                                sw(zero, s3, 8);
                                s4 = 0;
                                for (;;) {
                                    // 0x0019b598
                                    charge(ctx, 3);
                                    v0 = slti(s4, 32);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x0019b53c
                                    charge(ctx, 23);
                                    v0 = sll(s4, 1);
                                    v0 = addu(v0, s4);
                                    v0 = sll(v0, 2);
                                    s2 = addu(s3, v0);
                                    mov_s(f12, f20);
                                    jal(ctx, 0x19B550u, gen::fn_cosf_0052e6d8);
                                    lw(v0, s0, 76);
                                    lwc1(f1, v0, 0);
                                    mul_s(f0, f1, f0);
                                    swc1(f0, s2, 12);
                                    v0 = 0x40A00000;
                                    sw(v0, s2, 16);
                                    mov_s(f12, f20);
                                    jal(ctx, 0x19B574u, gen::fn_sinf_0052e878);
                                    lw(v0, s0, 76);
                                    lwc1(f1, v0, 0);
                                    mul_s(f0, f1, f0);
                                    swc1(f0, s2, 20);
                                    lwc1(f0, gp, -32236);  // 0x7CAF04
                                    add_s(f20, f20, f0);
                                    s4 = addiu(s4, 1);
                                }
                                // 0x0019b5a4
                                charge(ctx, 30);
                                v0 = sll(s4, 1);
                                v0 = addu(v0, s4);
                                s2 = sll(v0, 2);
                                mtc1(zero, f12);
                                jal(ctx, 0x19B5B4u, gen::fn_cosf_0052e6d8);
                                lw(v0, s0, 76);
                                lwc1(f1, v0, 0);
                                mul_s(f0, f1, f0);
                                v1 = addu(s2, s3);
                                swc1(f0, v1, 12);
                                v0 = 0x40A00000;
                                sw(v0, v1, 16);
                                mtc1(zero, f12);
                                jal(ctx, 0x19B5DCu, gen::fn_sinf_0052e878);
                                lw(v0, s0, 76);
                                lwc1(f1, v0, 0);
                                mul_s(f0, f1, f0);
                                v0 = addu(s2, s3);
                                swc1(f0, v0, 20);
                                lw(v1, s1, 48);
                                sb(zero, v1, 0);
                                sb(zero, v1, 1);
                                sb(zero, v1, 2);
                                v0 = 128;
                                sb(v0, v1, 3);
                                a0 = 0;
                                for (;;) {
                                    // 0x0019b638
                                    charge(ctx, 3);
                                    v0 = slti(a0, 33);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x0019b61c
                                    charge(ctx, 7);
                                    v0 = sll(a0, 2);
                                    v0 = addu(v1, v0);
                                    sb(zero, v0, 4);
                                    sb(zero, v0, 5);
                                    sb(zero, v0, 6);
                                    sb(zero, v0, 7);
                                    a0 = addiu(a0, 1);
                                }
                                // 0x0019b644
                                charge(ctx, 46);
                                a0 = s1;
                                jal(ctx, 0x19B648u, gen::fn_sub_4933D0_004933d0);
                                lw(s2, s1, 92);
                                a0 = s2;
                                a1 = addiu(sp, 0xF0);
                                jal(ctx, 0x19B65Cu, gen::fn_sub_492E20_00492e20);
                                lwc1(f3, sp, 0xF0);
                                lwc1(f2, sp, 0xF4);
                                lwc1(f1, sp, 0xF8);
                                lwc1(f0, sp, 0xFC);
                                swc1(f3, s2, 4);
                                swc1(f2, s2, 8);
                                swc1(f1, s2, 12);
                                swc1(f0, s2, 16);
                                jal(ctx, 0x19B684u, gen::fn_sub_491880_00491880);
                                lw(v1, s0, 76);
                                sw(v0, v1, 4);
                                lw(v0, s0, 76);
                                lw(a0, v0, 4);
                                a1 = s1;
                                a2 = 0;
                                jal(ctx, 0x19B6A4u, gen::fn_sub_4919B0_004919b0);
                                a0 = s1;
                                jal(ctx, 0x19B6B0u, gen::fn_sub_493B60_00493b60);
                                jal(ctx, 0x19B6B8u, gen::fn_sub_4CAF10_004caf10);
                                lw(v1, s0, 76);
                                lw(a0, v1, 4);
                                a1 = v0;
                                jal(ctx, 0x19B6CCu, gen::fn_sub_492D10_00492d10);
                                lw(v0, s0, 76);
                                lw(v0, v0, 4);
                                lw(a0, v0, 4);
                                jal(ctx, 0x19B6E0u, gen::fn_sub_4CB930_004cb930);
                                lw(v0, s0, 0);
                                v0 = addiu(v0, 1);
                                sw(v0, s0, 0);
                            }
                        }
                    } else {
                        // 0x0019b330
                        charge(ctx, 2);
                    }
                }
                // 0x0019bcbc: keep running
                charge(ctx, 1);
                v0 = 0;
            }
        } else {
            // 0x0019b304
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0019b2e8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0019bcc0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x180);
}

// 0x0019BEB0 sub_19BEB0 -- 1088 bytes; frame 0x90: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_19BEB0(parent, owner id, kind) [K_Shadow_CreateRenderTexTask]: RwCalloc(1, 140), kwlnTaskCreate(parent,
// "renderTex for shadow", 0x104B, sub_19B2B0, sub_19BCF0, work); +8 id, +10 kind. Walks the light list
// (sub_3B5D50(19)): the first light's position -> +116..+124; with a second light the projection axis (+128..+136) is
// x or z by which distance is larger, and the kind becomes 4. Kind 3 / 4: a 12-byte disc record (radius 0x41F00000 =
// 30.0) at +76. Kind 1: a texture (sub_4D0E40, K_Assert k_shadow.c 1517 if it fails) with filter / address bytes 2 /
// 0x33, a 128 x 128 x 32 camera raster (sub_4CE0F0(128, 128, 32, 0x505)) bound to it, a camera with a frame turned to
// the constant 0x678920 (sub_4CB930 / sub_4CB750), a 128 x 128 Z raster, a parallel projection (sub_4C9F00(camera,
// 2)), added to the current world (sub_198540(*0x7CE0CC), sub_49C160), and a 21,712-byte buffer at +72. Finally the
// owner (id kind (id & 0xFC00) >> 10 == 1 or 3) is looked up (sub_3B5D10; K_Assert 1546 / 1555) -> +12, its model
// (+296) -> +16. Callers: sub_3B6030, sub_3B6270.
void sub_19BEB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0019beb0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s4 = a1;
    s5 = a2;
    s2 = 0;
    s1 = 0x960000;
    s1 = addiu(s1, 388);  // &0x960184
    a0 = 1;
    a1 = 140;
    a2 = 0x40000;
    lw(v0, s1, 0);  // 0x960184
    jalr(ctx, 0x19BEFCu, v0.u());
    s3 = v0;
    if (s3 != 0) {
        // 0x0019bf1c
        charge(ctx, 23);
        a0 = s0;
        a1 = 0x680000;
        a1 = addiu(a1, -30416);  // "renderTex for shadow"
        a2 = 4171;
        a3 = 0x1A0000;
        a3 = addiu(a3, -19792);  // &sub_19B2B0
        t0 = 0x1A0000;
        t0 = addiu(t0, -17168);  // &sub_19BCF0
        t1 = s3;
        jal(ctx, 0x19BF40u, gen::fn_kwlnTaskCreate_00194b20);
        s6 = v0;
        sh(s4, s3, 8);
        s0 = addiu(s3, 10);
        sh(s5, s3, 10);
        a0 = 19;
        jal(ctx, 0x19BF5Cu, gen::fn_sub_3B5D50_003b5d50);
        a0 = 0x3F800000;
        v1 = 4;
        a1 = 1;
        for (;;) {
            // 0x0019bff8
            charge(ctx, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0019bf78
            charge(ctx, 2);
            if (s2 == 0) {
                // 0x0019bf80
                charge(ctx, 6);
                lwc1(f2, v0, 256);
                lwc1(f1, v0, 260);
                lwc1(f0, v0, 264);
                swc1(f2, s3, 116);
                swc1(f1, s3, 120);
                swc1(f0, s3, 124);
            }
            // 0x0019bf98
            charge(ctx, 2);
            if (s2 == a1) {
                // 0x0019bfa0
                charge(ctx, 11);
                lwc1(f1, s3, 116);
                lwc1(f0, v0, 256);
                sub_s(f0, f1, f0);
                abs_s(f2, f0);
                lwc1(f1, s3, 124);
                lwc1(f0, v0, 264);
                sub_s(f0, f1, f0);
                abs_s(f0, f0);
                c_le_s(f2, f0);
                if (cond(ctx)) {
                    // 0x0019bfe0
                    charge(ctx, 3);
                    sw(zero, s3, 128);
                    sw(zero, s3, 132);
                    sw(a0, s3, 136);
                } else {
                    // 0x0019bfcc
                    charge(ctx, 5);
                    sw(a0, s3, 128);
                    sw(zero, s3, 132);
                    sw(zero, s3, 136);
                }
                // 0x0019bfec
                charge(ctx, 1);
                sh(v1, s0, 0);
            }
            // 0x0019bff0
            charge(ctx, 2);
            s2 = addiu(s2, 1);
            lw(v0, v0, 248);
        }
        // 0x0019c000: by kind (+10)
        charge(ctx, 4);
        lhu(v1, s0, 0);
        v0 = 3;
        bool disc = true;  // host-side: kind 3 or 4 (a disc record)
        if (v1 != v0) {
            // 0x0019c010
            charge(ctx, 3);
            v0 = 4;
            disc = v1 == v0;
            if (!disc) {
                // 0x0019c01c
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x0019c030: kind 1 -- the texture, its raster, the camera
                    charge(ctx, 7);
                    s0 = addiu(s3, 60);
                    a0 = 0;
                    jal(ctx, 0x19C038u, gen::fn_sub_4D0E40_004d0e40);
                    sw(v0, s0, 0);
                    if (v0 == 0) {
                        // 0x0019c04c
                        charge(ctx, 5);
                        a0 = 0x680000;
                        a0 = addiu(a0, -30392);  // "k_shadow.c"
                        a1 = 1517;
                        jal(ctx, 0x19C058u, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x0019c060
                    charge(ctx, 22);
                    lw(a0, s3, 60);
                    lw(v1, a0, 80);
                    v0 = si(-256);
                    v0 = v1 & v0;
                    v0 = v0 | 0x2;
                    sw(v0, a0, 80);
                    lw(a0, s3, 60);
                    lw(v1, a0, 80);
                    v0 = lui(0xFFFF);
                    v0 = v0 | 0xFF;
                    v0 = v1 & v0;
                    v0 = v0 | 0x3300;
                    sw(v0, a0, 80);
                    a0 = 128;
                    a1 = a0;
                    a2 = 32;
                    a3 = 1285;
                    jal(ctx, 0x19C0A4u, gen::fn_sub_4CE0F0_004ce0f0);
                    s2 = v0;
                    if (s2 != 0) {
                        // 0x0019c0b8
                        charge(ctx, 4);
                        a0 = s2;
                        a1 = 1;
                        jal(ctx, 0x19C0C0u, gen::fn_sub_4F1780_004f1780);
                    }
                    // 0x0019c0c8
                    charge(ctx, 11);
                    s5 = addiu(s3, 64);
                    sw(s2, s3, 64);
                    lw(a0, s0, 0);
                    a1 = s2;
                    jal(ctx, 0x19C0D8u, gen::fn_sub_4D0BE0_004d0be0);
                    jal(ctx, 0x19C0E0u, gen::fn_sub_4CA090_004ca090);  // the shadow camera
                    s0 = v0;
                    bool camera_ok = false;  // host-side: camera, frame and Z raster all made
                    if (s0 != 0) {
                        // 0x0019c0f4
                        charge(ctx, 24);
                        v0 = 0x680000;
                        ld(v1, v0, -30432);  // 0x678920
                        v0 = 0x680000;
                        lwc1(f0, v0, -30424);  // 0x678928
                        sd(v1, sp, 0x80);
                        swc1(f0, sp, 0x88);
                        jal(ctx, 0x19C10Cu, gen::fn_sub_4CAF10_004caf10);
                        a0 = s0;
                        a1 = v0;
                        jal(ctx, 0x19C11Cu, gen::fn_sub_4D1840_004d1840);
                        s2 = addiu(s0, 4);
                        lw(a0, s0, 4);
                        jal(ctx, 0x19C12Cu, gen::fn_sub_4CB930_004cb930);
                        lw(a0, s2, 0);
                        a1 = addiu(sp, 0x80);
                        a2 = 0;
                        jal(ctx, 0x19C140u, gen::fn_sub_4CB750_004cb750);
                        lw(v0, s2, 0);
                        if (v0 != 0) {
                            // 0x0019c154: a 128 x 128 Z raster
                            charge(ctx, 8);
                            a0 = 128;
                            a1 = a0;
                            a2 = 0;
                            a3 = 1;
                            jal(ctx, 0x19C164u, gen::fn_sub_4CE0F0_004ce0f0);
                            if (v0 != 0) {
                                // 0x0019c174: parallel projection
                                charge(ctx, 7);
                                sw(v0, s0, 100);
                                a0 = s0;
                                a1 = 2;
                                jal(ctx, 0x19C180u, gen::fn_sub_4C9F00_004c9f00);
                                camera_ok = true;
                            }
                        }
                    }
                    if (!camera_ok) {
                        // 0x0019c190: destroy what was made, no camera
                        charge(ctx, 4);
                        a0 = s0;
                        jal(ctx, 0x19C194u, gen::fn_sub_199C60_00199c60);
                        s0 = 0;
                    }
                    // 0x0019c1a0: the camera (+68) joins the current world, renders into the texture's raster; the buffer
                    charge(ctx, 21);
                    s2 = addiu(s3, 68);
                    sw(s0, s3, 68);
                    lw(a0, gp, -19492);  // 0x7CE0CC
                    jal(ctx, 0x19C1ACu, gen::fn_sub_198540_00198540);
                    a0 = v0;
                    lw(a1, s2, 0);
                    jal(ctx, 0x19C1BCu, gen::fn_sub_49C160_0049c160);
                    lw(v1, s5, 0);
                    lw(v0, s2, 0);
                    sw(v1, v0, 96);
                    a0 = 1;
                    a1 = 21712;
                    a2 = 0x40000;
                    lw(v0, s1, 0);
                    jalr(ctx, 0x19C1E0u, v0.u());
                    sw(v0, s3, 72);
                } else {
                    // 0x0019c028
                    charge(ctx, 2);
                }
            }
        }
        if (disc) {
            // 0x0019c1f4: the disc record (radius 30.0) at +76
            charge(ctx, 10);
            s0 = addiu(s3, 76);
            a0 = 1;
            a1 = 12;
            a2 = 0x40000;
            lw(v0, s1, 0);
            jalr(ctx, 0x19C208u, v0.u());
            sw(v0, s0, 0);
            v1 = 0x41F00000;
            sw(v1, v0, 0);
        }
        // 0x0019c21c: the owner by its id's kind ((id & 0xFC00) >> 10: 1 or 3)
        charge(ctx, 8);
        v1 = s4 & 0xFFFF;
        v0 = 0xF0000;
        v0 = v0 | 0xFC00;
        v0 = v1 & v0;
        v1 = sra(v0, 10);
        v0 = 1;
        if (v1 != v0) {
            // 0x0019c27c
            charge(ctx, 3);
            v0 = 3;
            if (v1 == v0) {
                // 0x0019c288
                charge(ctx, 7);
                a0 = s4;
                jal(ctx, 0x19C28Cu, gen::fn_sub_3B5D10_003b5d10);
                s0 = v0;
                sw(s0, s3, 12);
                if (s0 == 0) {
                    // 0x0019c2a4
                    charge(ctx, 5);
                    a0 = 0x680000;
                    a0 = addiu(a0, -30392);  // "k_shadow.c"
                    a1 = 1555;
                    jal(ctx, 0x19C2B0u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x0019c2b8
                charge(ctx, 2);
                lw(v0, s0, 296);
                sw(v0, s3, 16);
            }
        } else {
            // 0x0019c23c
            charge(ctx, 7);
            a0 = s4;
            jal(ctx, 0x19C240u, gen::fn_sub_3B5D10_003b5d10);
            s0 = v0;
            sw(s0, s3, 12);
            if (s0 == 0) {
                // 0x0019c258
                charge(ctx, 5);
                a0 = 0x680000;
                a0 = addiu(a0, -30392);  // "k_shadow.c"
                a1 = 1546;
                jal(ctx, 0x19C264u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x0019c26c
            charge(ctx, 4);
            lw(v0, s0, 296);
            sw(v0, s3, 16);
        }
        // 0x0019c2c0
        charge(ctx, 1);
        v0 = s6;
    } else {
        // 0x0019bf10
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0019c2c4 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x0019C320 sub_19C320 -- 368 bytes; frame 0x70: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_19C320(task, radius) [K_Shadow_SetDiscRadius]: for a disc shadow (work +76): stores the radius and, when the
// disc has a geometry (+4 -> atomic -> +24 geometry), locks it (geometryLock 0xFFF) and rewrites its 34 vertices: the
// centre (0, 5, 0) and 33 rim points (r cos a, 5, r sin a) with the angle stepping by the float 0x7CAF04; then
// unlocks (sub_4933D0). Callers: the field's shadow users sub_1C2DD0, sub_1E3940, sub_1E3F10, sub_1E4BC0.
void sub_19C320(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0019c320
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    lw(s3, a0, 60);
    lw(v1, s3, 76);
    if (v1 != 0) {
        // 0x0019c350
        charge(ctx, 5);
        swc1(f12, v1, 0);
        lw(v1, s3, 76);
        lw(v1, v1, 4);
        if (v1 != 0) {
            // 0x0019c364
            charge(ctx, 15);
            lw(s0, v1, 24);
            a0 = s0;
            a1 = 4095;
            jal(ctx, 0x19C370u, gen::fn_geometryLock_00493370);
            lw(v0, s0, 92);
            lw(s2, v0, 20);
            mtc1(zero, f20);
            sw(zero, s2, 0);
            v0 = 0x40A00000;
            sw(v0, s2, 4);
            sw(zero, s2, 8);
            s4 = 0;
            for (;;) {
                // 0x0019c3fc
                charge(ctx, 3);
                v0 = slti(s4, 32);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0019c3a0
                charge(ctx, 23);
                v0 = sll(s4, 1);
                v0 = addu(v0, s4);
                v0 = sll(v0, 2);
                s1 = addu(s2, v0);
                mov_s(f12, f20);
                jal(ctx, 0x19C3B4u, gen::fn_cosf_0052e6d8);
                lw(v0, s3, 76);
                lwc1(f1, v0, 0);
                mul_s(f0, f1, f0);
                swc1(f0, s1, 12);
                v0 = 0x40A00000;
                sw(v0, s1, 16);
                mov_s(f12, f20);
                jal(ctx, 0x19C3D8u, gen::fn_sinf_0052e878);
                lw(v0, s3, 76);
                lwc1(f1, v0, 0);
                mul_s(f0, f1, f0);
                swc1(f0, s1, 20);
                lwc1(f0, gp, -32236);  // 0x7CAF04
                add_s(f20, f20, f0);
                s4 = addiu(s4, 1);
            }
            // 0x0019c408
            charge(ctx, 24);
            v0 = sll(s4, 1);
            v0 = addu(v0, s4);
            s1 = sll(v0, 2);
            mtc1(zero, f12);
            jal(ctx, 0x19C418u, gen::fn_cosf_0052e6d8);
            lw(v0, s3, 76);
            lwc1(f1, v0, 0);
            mul_s(f0, f1, f0);
            v1 = addu(s1, s2);
            swc1(f0, v1, 12);
            v0 = 0x40A00000;
            sw(v0, v1, 16);
            mtc1(zero, f12);
            jal(ctx, 0x19C440u, gen::fn_sinf_0052e878);
            lw(v0, s3, 76);
            lwc1(f1, v0, 0);
            mul_s(f0, f1, f0);
            v0 = addu(s1, s2);
            swc1(f0, v0, 20);
            a0 = s0;
            jal(ctx, 0x19C460u, gen::fn_sub_4933D0_004933d0);
        }
    }
    // 0x0019c468 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0019C4B0 sub_19C4B0 -- 3520 bytes; frame 0x140: ra sp+0x90, s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// sub_19C4B0(task) [K_Shadow_UpdateMapCameraTask] ("shadow map camera", priority 0x814): step 1 renders the shadow
// maps of the characters (resource list 1) and the NPCs (list 3) that have a real-time shadow (shadow record kind 1):
// the three lights' flag byte +2 are cleared for the pass, each shadow camera is aimed (a matrix from the owner's
// frame or sub_1A0A50 / sub_1A0D80, sub_4C2CC0 / sub_4C2D20 / sub_4C2F10), its view window set from the shadow size
// (doubled when sub_1A01C0() == 1), cleared (RwCameraClear with the colour at 0x7CE138) and the model drawn black
// (its colour saved and restored, sub_318AD0, its five material flags cleared, sub_317A20), then three gradient
// quads (drawGradientQuad, 0x678960..0x67896C) soften the edge; K_Assert(k_shadow.c, 1903) when the camera cannot
// begin. Step 2 ends the task (-1).
void sub_19C4B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0019c4b0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s0, a0, 60);
    a0 = 1;
    jal(ctx, 0x19C4E8u, gen::fn_sub_3B5D50_003b5d50);
    s3 = v0;
    a0 = 3;
    jal(ctx, 0x19C4F8u, gen::fn_sub_3B5D50_003b5d50);
    s2 = v0;
    lw(v1, s0, 0);
    v0 = 2;
    if (v1 == v0) {
        // 0x0019d228
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x0019c514
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x0019c540
            charge(ctx, 26);
            jal(ctx, 0x19C540u, gen::fn_sub_198570_00198570);
            lbu(s5, v0, 2);
            jal(ctx, 0x19C54Cu, gen::fn_sub_198570_00198570);
            sb(zero, v0, 2);
            jal(ctx, 0x19C558u, gen::fn_sub_198570_00198570);
            jal(ctx, 0x19C560u, gen::fn_sub_198580_00198580);
            lbu(s6, v0, 2);
            jal(ctx, 0x19C56Cu, gen::fn_sub_198580_00198580);
            sb(zero, v0, 2);
            jal(ctx, 0x19C578u, gen::fn_sub_198580_00198580);
            jal(ctx, 0x19C580u, gen::fn_sub_198560_00198560);
            lbu(s7, v0, 2);
            jal(ctx, 0x19C58Cu, gen::fn_sub_198560_00198560);
            sb(zero, v0, 2);
            jal(ctx, 0x19C598u, gen::fn_sub_198560_00198560);
            for (;;) {
                // 0x0019cc34
                charge(ctx, 2);
                if (s3 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0019c5a8
                charge(ctx, 4);
                lw(v0, s3, 40);
                v0 = v0 & 0x2;
                if (v0 != 0) {
                    // 0x0019c5b8
                    charge(ctx, 6);
                    lw(v0, s3, 484);
                    lw(a0, v0, 60);
                    lhu(v1, a0, 10);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x0019c5d0
                        charge(ctx, 5);
                        lw(s1, a0, 68);
                        lwc1(f20, a0, 24);
                        lw(v0, a0, 0);
                        if (i64(v0) > 0) {
                            // 0x0019c5e4
                            charge(ctx, 14);
                            lw(a0, s3, 296);
                            jal(ctx, 0x19C5E8u, gen::fn_sub_318B60_00318b60);
                            lwc1(f2, v0, 48);
                            lwc1(f1, v0, 52);
                            lwc1(f0, v0, 56);
                            swc1(f2, sp, 0x128);
                            swc1(f1, sp, 0x12C);
                            swc1(f0, sp, 0x130);
                            lw(v1, s3, 40);
                            v0 = lui(0x8000);
                            v0 = v1 & v0;
                            if (v0 == 0) {
                                // 0x0019c69c
                                charge(ctx, 32);
                                jal(ctx, 0x19C69Cu, gen::fn_sub_1A0A50_001a0a50);
                                s0 = addiu(s1, 4);
                                lw(s4, s1, 4);
                                lwc1(f2, v0, 0);
                                lwc1(f1, v0, 4);
                                lwc1(f0, v0, 8);
                                swc1(f2, s4, 16);
                                swc1(f1, s4, 20);
                                swc1(f0, s4, 24);
                                lwc1(f2, v0, 16);
                                lwc1(f1, v0, 20);
                                lwc1(f0, v0, 24);
                                swc1(f2, s4, 32);
                                swc1(f1, s4, 36);
                                swc1(f0, s4, 40);
                                lwc1(f2, v0, 32);
                                lwc1(f1, v0, 36);
                                lwc1(f0, v0, 40);
                                swc1(f2, s4, 48);
                                swc1(f1, s4, 52);
                                swc1(f0, s4, 56);
                                a0 = addiu(sp, 0xF8);
                                jal(ctx, 0x19C6F8u, gen::fn_sub_4C2CC0_004c2cc0);
                                a0 = addiu(s4, 16);
                                a1 = addiu(sp, 0xF8);
                                jal(ctx, 0x19C708u, gen::fn_sub_4C2D20_004c2d20);
                                a0 = addiu(s4, 16);
                                jal(ctx, 0x19C714u, gen::fn_sub_4C2F10_004c2f10);
                            } else {
                                // 0x0019c61c
                                charge(ctx, 32);
                                s0 = addiu(s1, 4);
                                lw(s4, s1, 4);
                                lwc1(f2, s3, 336);
                                lwc1(f1, s3, 340);
                                lwc1(f0, s3, 344);
                                swc1(f2, s4, 16);
                                swc1(f1, s4, 20);
                                swc1(f0, s4, 24);
                                lwc1(f2, s3, 352);
                                lwc1(f1, s3, 356);
                                lwc1(f0, s3, 360);
                                swc1(f2, s4, 32);
                                swc1(f1, s4, 36);
                                swc1(f0, s4, 40);
                                lwc1(f2, s3, 368);
                                lwc1(f1, s3, 372);
                                lwc1(f0, s3, 376);
                                swc1(f2, s4, 48);
                                swc1(f1, s4, 52);
                                swc1(f0, s4, 56);
                                a0 = addiu(sp, 0x108);
                                jal(ctx, 0x19C670u, gen::fn_sub_4C2CC0_004c2cc0);
                                a0 = addiu(s4, 16);
                                a1 = addiu(sp, 0x108);
                                jal(ctx, 0x19C680u, gen::fn_sub_4C2D20_004c2d20);
                                a0 = addiu(s4, 16);
                                jal(ctx, 0x19C68Cu, gen::fn_sub_4C2F10_004c2f10);
                            }
                            // 0x0019c71c
                            charge(ctx, 19);
                            lwc1(f0, gp, -32576);  // 0x7CADB0
                            mul_s(f21, f0, f20);
                            v0 = 0x41200000;
                            mtc1(v0, f0);
                            mul_s(f12, f0, f21);
                            a0 = s1;
                            jal(ctx, 0x19C738u, gen::fn_sub_4C9DB0_004c9db0);
                            lwc1(f0, gp, -32204);  // 0x7CAF24
                            mul_s(f12, f0, f21);
                            a0 = s1;
                            jal(ctx, 0x19C74Cu, gen::fn_sub_4C9D70_004c9d70);
                            jal(ctx, 0x19C754u, gen::fn_sub_1A01C0_001a01c0);
                            v1 = 1;
                            if (v0 != v1) {
                                // 0x0019c790
                                charge(ctx, 6);
                                lwc1(f0, gp, -32576);  // 0x7CADB0
                                mul_s(f1, f0, f20);
                                lwc1(f0, gp, -31648);  // 0x7CB150
                                mul_s(f0, f0, f1);
                                swc1(f0, sp, 0xF0);
                                swc1(f0, sp, 0xF4);
                            } else {
                                // 0x0019c768
                                charge(ctx, 10);
                                lwc1(f0, gp, -32576);  // 0x7CADB0
                                mul_s(f1, f0, f20);
                                v0 = 0x40000000;
                                mtc1(v0, f0);
                                mul_s(f0, f0, f1);
                                swc1(f0, sp, 0xF0);
                                swc1(f0, sp, 0xF4);
                            }
                            // 0x0019c7a8
                            charge(ctx, 69);
                            a0 = s1;
                            a1 = addiu(sp, 0xF0);
                            jal(ctx, 0x19C7B0u, gen::fn_sub_4C9F90_004c9f90);
                            lwc1(f1, sp, 0x12C);
                            v0 = 0x40000000;
                            mtc1(v0, f0);
                            div_s(f0, f20, f0);
                            add_s(f4, f1, f0);
                            swc1(f4, sp, 0x12C);
                            lw(s0, s0, 0);
                            lwc1(f0, s0, 64);
                            neg_s(f3, f0);
                            swc1(f3, sp, 0xE0);
                            lwc1(f0, s0, 68);
                            neg_s(f2, f0);
                            swc1(f2, sp, 0xE4);
                            lwc1(f0, s0, 72);
                            neg_s(f1, f0);
                            swc1(f1, sp, 0xE8);
                            lwc1(f0, sp, 0x128);
                            add_s(f6, f3, f0);
                            swc1(f6, sp, 0xE0);
                            add_s(f5, f2, f4);
                            swc1(f5, sp, 0xE4);
                            lwc1(f0, sp, 0x130);
                            add_s(f4, f1, f0);
                            swc1(f4, sp, 0xE8);
                            lwc1(f3, s0, 48);
                            v0 = lui(0xBF00);
                            mtc1(v0, f1);
                            lwc1(f0, s1, 132);
                            mul_s(f2, f1, f0);
                            mtc1(zero, f1);
                            adda_s(f1, f6);
                            madd_s(f0, f3, f2);
                            swc1(f0, sp, 0xE0);
                            lwc1(f0, s0, 52);
                            adda_s(f1, f5);
                            madd_s(f0, f0, f2);
                            swc1(f0, sp, 0xE4);
                            lwc1(f0, s0, 56);
                            adda_s(f1, f4);
                            madd_s(f0, f0, f2);
                            swc1(f0, sp, 0xE8);
                            a0 = s0;
                            a1 = addiu(sp, 0xE0);
                            a2 = 2;
                            jal(ctx, 0x19C870u, gen::fn_sub_4CB750_004cb750);
                            a0 = s0;
                            jal(ctx, 0x19C87Cu, gen::fn_sub_4CB2F0_004cb2f0);
                            a0 = v0;
                            a1 = v0;
                            jal(ctx, 0x19C88Cu, gen::fn_sub_4C2FB0_004c2fb0);
                            a0 = s1;
                            a1 = addiu(gp, -19384);  // &0x7CE138
                            a2 = 3;
                            jal(ctx, 0x19C8A0u, gen::fn_RwCameraClear_004c9e90);
                            a0 = s1;
                            jal(ctx, 0x19C8ACu, gen::fn_RwCameraBeginUpdate_004c9d10);
                            if (v0 == 0) {
                                // 0x0019cc1c
                                charge(ctx, 5);
                                a0 = 0x680000;
                                a0 = addiu(a0, -30392);  // "k_shadow.c"
                                a1 = 1903;
                                jal(ctx, 0x19CC28u, gen::fn_sub_19D3F0_0019d3f0);
                            } else {
                                // 0x0019c8bc
                                charge(ctx, 20);
                                lw(a0, s3, 296);
                                jal(ctx, 0x19C8C0u, gen::fn_sub_318B00_00318b00);
                                lbu(a1, v0, 0);
                                lbu(a0, v0, 1);
                                lbu(v1, v0, 2);
                                lbu(v0, v0, 3);
                                sb(a1, sp, 0x13C);
                                sb(a0, sp, 0x13D);
                                sb(v1, sp, 0x13E);
                                sb(v0, sp, 0x13F);
                                a1 = addiu(sp, 0x138);
                                lwc1(f0, gp, -27564);  // 0x7CC144
                                swc1(f0, sp, 0x138);
                                lw(a0, s3, 296);
                                jal(ctx, 0x19C8F8u, gen::fn_sub_318AD0_00318ad0);
                                a0 = 0;
                                for (;;) {
                                    // 0x0019c930
                                    charge(ctx, 3);
                                    v0 = slti(a0, 5);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x0019c90c
                                    charge(ctx, 9);
                                    v0 = sll(a0, 1);
                                    v0 = addu(v0, a0);
                                    v1 = sll(v0, 2);
                                    lw(v0, s3, 296);
                                    v1 = addu(v0, v1);
                                    lbu(v0, v1, 948);
                                    v0 = v0 & 0xFE;
                                    sb(v0, v1, 948);
                                    a0 = addiu(a0, 1);
                                }
                                // 0x0019c93c
                                charge(ctx, 6);
                                a0 = 1;
                                sw(a0, gp, -19352);  // 0x7CE158
                                lw(v1, s3, 296);
                                lhu(v0, v1, 212);
                                if (v0 == a0) {
                                    // 0x0019c954: model kind 1 with sub-kind 2, 4, 5, 7 or 8: 0x7CC1EC = 0 for the pass
                                    charge(ctx, 4);
                                    lhu(v1, v1, 214);
                                    v0 = 2;
                                    bool listed = true;  // host-side: the sub-kind is one of the five
                                    if (v1 != v0) {
                                        // 0x0019c964
                                        charge(ctx, 3);
                                        v0 = 4;
                                        listed = v1 == v0;
                                        if (!listed) {
                                            // 0x0019c970
                                            charge(ctx, 3);
                                            v0 = 5;
                                            listed = v1 == v0;
                                            if (!listed) {
                                                // 0x0019c97c
                                                charge(ctx, 3);
                                                v0 = 7;
                                                listed = v1 == v0;
                                                if (!listed) {
                                                    // 0x0019c988 (7 compared again)
                                                    charge(ctx, 2);
                                                    listed = v1 == v0;
                                                    if (!listed) {
                                                        // 0x0019c990
                                                        charge(ctx, 3);
                                                        v0 = 8;
                                                        listed = v1 == v0;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if (listed) {
                                        // 0x0019c99c
                                        charge(ctx, 1);
                                        sw(zero, gp, -27396);  // 0x7CC1EC
                                    }
                                }
                                // 0x0019c9a0: draw the model in its shadow pass (+216 bit 2 set around sub_317A20)
                                charge(ctx, 17);
                                lw(v1, s3, 296);
                                lhu(v0, v1, 216);
                                v0 = v0 | 0x4;
                                sh(v0, v1, 216);
                                lw(a0, s3, 296);
                                jal(ctx, 0x19C9B4u, gen::fn_sub_317A20_00317a20);
                                lw(v1, s3, 296);
                                lhu(v0, v1, 216);
                                v0 = v0 & 0xFFFB;
                                sh(v0, v1, 216);
                                v0 = 1;
                                sw(v0, gp, -27396);  // 0x7CC1EC
                                sw(zero, gp, -19352);  // 0x7CE158
                                a0 = 0;
                                for (;;) {
                                    // 0x0019ca08
                                    charge(ctx, 3);
                                    v0 = slti(a0, 5);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x0019c9e4
                                    charge(ctx, 9);
                                    v0 = sll(a0, 1);
                                    v0 = addu(v0, a0);
                                    v1 = sll(v0, 2);
                                    lw(v0, s3, 296);
                                    v1 = addu(v0, v1);
                                    lbu(v0, v1, 948);
                                    v0 = v0 | 0x1;
                                    sb(v0, v1, 948);
                                    a0 = addiu(a0, 1);
                                }
                                // 0x0019ca14
                                charge(ctx, 121);
                                lw(a0, s3, 296);
                                a1 = addiu(sp, 0x13C);
                                jal(ctx, 0x19CA1Cu, gen::fn_sub_318AD0_00318ad0);
                                s4 = 0x960000;
                                s4 = addiu(s4, 144);  // &pfn_RwRenderStateSet
                                a0 = 14;
                                a1 = 0;
                                lw(v0, s4, 0);  // pfn_RwRenderStateSet
                                jalr(ctx, 0x19CA38u, v0.u());
                                a0 = 6;
                                a1 = 0;
                                lw(v0, s4, 0);  // pfn_RwRenderStateSet
                                jalr(ctx, 0x19CA4Cu, v0.u());
                                a0 = 8;
                                a1 = 0;
                                lw(v0, s4, 0);  // pfn_RwRenderStateSet
                                jalr(ctx, 0x19CA60u, v0.u());
                                a0 = 7;
                                a1 = 2;
                                lw(v0, s4, 0);  // pfn_RwRenderStateSet
                                jalr(ctx, 0x19CA74u, v0.u());
                                a0 = 1;
                                a1 = 0;
                                lw(v0, s4, 0);  // pfn_RwRenderStateSet
                                jalr(ctx, 0x19CA88u, v0.u());
                                a0 = 2;
                                a1 = 68;
                                jal(ctx, 0x19CA98u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                a0 = 3;
                                v0 = 0x70000;
                                a1 = v0 | 0x17FB;
                                jal(ctx, 0x19CAACu, gen::fn_RpSkyRenderStateSet_004d7f60);
                                s0 = 0x960000;
                                s0 = addiu(s0, 136);  // &g_rwIm2DNearScreenZ
                                mtc1(zero, f12);
                                v0 = 0x43000000;
                                mtc1(v0, f14);
                                v0 = 0x42400000;
                                mtc1(v0, f15);
                                v0 = 0x3F800000;
                                mtc1(v0, f1);
                                lwc1(f0, s1, 128);
                                div_s(f17, f1, f0);
                                mov_s(f13, f12);
                                a0 = 0x680000;
                                a0 = addiu(a0, -30368);  // &0x678960
                                a1 = 0x680000;
                                a1 = addiu(a1, -30364);  // &0x678964
                                lwc1(f16, s0, 0);  // g_rwIm2DNearScreenZ
                                jal(ctx, 0x19CAF8u, gen::fn_drawGradientQuad_001997e0);
                                a0 = 2;
                                a1 = 68;
                                jal(ctx, 0x19CB08u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                a0 = 3;
                                v0 = 0x30000;
                                a1 = v0 | 0xC803;
                                jal(ctx, 0x19CB1Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
                                mtc1(zero, f12);
                                v0 = 0x42400000;
                                mtc1(v0, f13);
                                v0 = 0x43000000;
                                mtc1(v0, f14);
                                v0 = 0x42980000;
                                mtc1(v0, f15);
                                v0 = 0x3F800000;
                                mtc1(v0, f1);
                                lwc1(f0, s1, 128);
                                div_s(f17, f1, f0);
                                a0 = 0x680000;
                                a0 = addiu(a0, -30364);  // &0x678964
                                a1 = 0x680000;
                                a1 = addiu(a1, -30360);  // &0x678968
                                lwc1(f16, s0, 0);  // g_rwIm2DNearScreenZ
                                jal(ctx, 0x19CB64u, gen::fn_drawGradientQuad_001997e0);
                                mtc1(zero, f12);
                                v0 = 0x42980000;
                                mtc1(v0, f13);
                                v0 = 0x43000000;
                                mtc1(v0, f14);
                                v0 = 0x3F800000;
                                mtc1(v0, f1);
                                lwc1(f0, s1, 128);
                                div_s(f17, f1, f0);
                                mov_s(f15, f14);
                                a0 = 0x680000;
                                a0 = addiu(a0, -30360);  // &0x678968
                                a1 = 0x680000;
                                a1 = addiu(a1, -30356);  // &0x67896C
                                lwc1(f16, s0, 0);  // g_rwIm2DNearScreenZ
                                jal(ctx, 0x19CBA8u, gen::fn_drawGradientQuad_001997e0);
                                a0 = 2;
                                a1 = 68;
                                jal(ctx, 0x19CBB8u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                a0 = 3;
                                v0 = 0x70000;
                                a1 = v0 | 0x17FB;
                                jal(ctx, 0x19CBCCu, gen::fn_RpSkyRenderStateSet_004d7f60);
                                a0 = 20;
                                a1 = 2;
                                lw(v0, s4, 0);  // pfn_RwRenderStateSet
                                jalr(ctx, 0x19CBE0u, v0.u());
                                lw(v0, gp, -19484);  // 0x7CE0D4
                                a1 = 1;
                                if (v0 == a1) {
                                    // 0x0019cbf8
                                    charge(ctx, 4);
                                    a0 = 14;
                                    lw(v0, s4, 0);
                                    jalr(ctx, 0x19CC00u, v0.u());
                                }
                                // 0x0019cc08
                                charge(ctx, 5);
                                a0 = s1;
                                jal(ctx, 0x19CC0Cu, gen::fn_RwCameraEndUpdate_004c9d00);
                            }
                        }
                    }
                }
                // 0x0019cc30
                charge(ctx, 1);
                lw(s3, s3, 248);
            }
            // 0x0019cc3c
            charge(ctx, 2);
            for (;;) {
                // 0x0019d1d0
                charge(ctx, 2);
                if (s2 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0019cc44
                charge(ctx, 4);
                lw(v0, s2, 40);
                v0 = v0 & 0x2;
                if (v0 != 0) {
                    // 0x0019cc54
                    charge(ctx, 6);
                    lw(v0, s2, 496);
                    lw(a0, v0, 60);
                    lhu(v1, a0, 10);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x0019cc6c
                        charge(ctx, 5);
                        lw(s1, a0, 68);
                        lwc1(f20, a0, 24);
                        lw(v0, a0, 0);
                        if (i64(v0) > 0) {
                            // 0x0019cc80
                            charge(ctx, 14);
                            lw(a0, s2, 296);
                            jal(ctx, 0x19CC84u, gen::fn_sub_318B60_00318b60);
                            lwc1(f2, v0, 48);
                            lwc1(f1, v0, 52);
                            lwc1(f0, v0, 56);
                            swc1(f2, sp, 0x118);
                            swc1(f1, sp, 0x11C);
                            swc1(f0, sp, 0x120);
                            lw(v1, s2, 40);
                            v0 = lui(0x8000);
                            v0 = v1 & v0;
                            if (v0 == 0) {
                                // 0x0019cd38
                                charge(ctx, 32);
                                jal(ctx, 0x19CD38u, gen::fn_sub_1A0D80_001a0d80);
                                s0 = addiu(s1, 4);
                                lw(s3, s1, 4);
                                lwc1(f2, v0, 0);
                                lwc1(f1, v0, 4);
                                lwc1(f0, v0, 8);
                                swc1(f2, s3, 16);
                                swc1(f1, s3, 20);
                                swc1(f0, s3, 24);
                                lwc1(f2, v0, 16);
                                lwc1(f1, v0, 20);
                                lwc1(f0, v0, 24);
                                swc1(f2, s3, 32);
                                swc1(f1, s3, 36);
                                swc1(f0, s3, 40);
                                lwc1(f2, v0, 32);
                                lwc1(f1, v0, 36);
                                lwc1(f0, v0, 40);
                                swc1(f2, s3, 48);
                                swc1(f1, s3, 52);
                                swc1(f0, s3, 56);
                                a0 = addiu(sp, 0xC0);
                                jal(ctx, 0x19CD94u, gen::fn_sub_4C2CC0_004c2cc0);
                                a0 = addiu(s3, 16);
                                a1 = addiu(sp, 0xC0);
                                jal(ctx, 0x19CDA4u, gen::fn_sub_4C2D20_004c2d20);
                                a0 = addiu(s3, 16);
                                jal(ctx, 0x19CDB0u, gen::fn_sub_4C2F10_004c2f10);
                            } else {
                                // 0x0019ccb8
                                charge(ctx, 32);
                                s0 = addiu(s1, 4);
                                lw(s3, s1, 4);
                                lwc1(f2, s2, 336);
                                lwc1(f1, s2, 340);
                                lwc1(f0, s2, 344);
                                swc1(f2, s3, 16);
                                swc1(f1, s3, 20);
                                swc1(f0, s3, 24);
                                lwc1(f2, s2, 352);
                                lwc1(f1, s2, 356);
                                lwc1(f0, s2, 360);
                                swc1(f2, s3, 32);
                                swc1(f1, s3, 36);
                                swc1(f0, s3, 40);
                                lwc1(f2, s2, 368);
                                lwc1(f1, s2, 372);
                                lwc1(f0, s2, 376);
                                swc1(f2, s3, 48);
                                swc1(f1, s3, 52);
                                swc1(f0, s3, 56);
                                a0 = addiu(sp, 0xD0);
                                jal(ctx, 0x19CD0Cu, gen::fn_sub_4C2CC0_004c2cc0);
                                a0 = addiu(s3, 16);
                                a1 = addiu(sp, 0xD0);
                                jal(ctx, 0x19CD1Cu, gen::fn_sub_4C2D20_004c2d20);
                                a0 = addiu(s3, 16);
                                jal(ctx, 0x19CD28u, gen::fn_sub_4C2F10_004c2f10);
                            }
                            // 0x0019cdb8
                            charge(ctx, 19);
                            lwc1(f0, gp, -32576);  // 0x7CADB0
                            mul_s(f21, f0, f20);
                            v0 = 0x41200000;
                            mtc1(v0, f0);
                            mul_s(f12, f0, f21);
                            a0 = s1;
                            jal(ctx, 0x19CDD4u, gen::fn_sub_4C9DB0_004c9db0);
                            lwc1(f0, gp, -32204);  // 0x7CAF24
                            mul_s(f12, f0, f21);
                            a0 = s1;
                            jal(ctx, 0x19CDE8u, gen::fn_sub_4C9D70_004c9d70);
                            jal(ctx, 0x19CDF0u, gen::fn_sub_1A01C0_001a01c0);
                            v1 = 1;
                            if (v0 != v1) {
                                // 0x0019ce2c
                                charge(ctx, 6);
                                lwc1(f0, gp, -32576);  // 0x7CADB0
                                mul_s(f1, f0, f20);
                                lwc1(f0, gp, -31648);  // 0x7CB150
                                mul_s(f0, f0, f1);
                                swc1(f0, sp, 0xB8);
                                swc1(f0, sp, 0xBC);
                            } else {
                                // 0x0019ce04
                                charge(ctx, 10);
                                lwc1(f0, gp, -32576);  // 0x7CADB0
                                mul_s(f1, f0, f20);
                                v0 = 0x40000000;
                                mtc1(v0, f0);
                                mul_s(f0, f0, f1);
                                swc1(f0, sp, 0xB8);
                                swc1(f0, sp, 0xBC);
                            }
                            // 0x0019ce44
                            charge(ctx, 69);
                            a0 = s1;
                            a1 = addiu(sp, 0xB8);
                            jal(ctx, 0x19CE4Cu, gen::fn_sub_4C9F90_004c9f90);
                            lwc1(f1, sp, 0x11C);
                            v0 = 0x40000000;
                            mtc1(v0, f0);
                            div_s(f0, f20, f0);
                            add_s(f4, f1, f0);
                            swc1(f4, sp, 0x11C);
                            lw(s0, s0, 0);
                            lwc1(f0, s0, 64);
                            neg_s(f3, f0);
                            swc1(f3, sp, 0xA8);
                            lwc1(f0, s0, 68);
                            neg_s(f2, f0);
                            swc1(f2, sp, 0xAC);
                            lwc1(f0, s0, 72);
                            neg_s(f1, f0);
                            swc1(f1, sp, 0xB0);
                            lwc1(f0, sp, 0x118);
                            add_s(f6, f3, f0);
                            swc1(f6, sp, 0xA8);
                            add_s(f5, f2, f4);
                            swc1(f5, sp, 0xAC);
                            lwc1(f0, sp, 0x120);
                            add_s(f4, f1, f0);
                            swc1(f4, sp, 0xB0);
                            lwc1(f3, s0, 48);
                            v0 = lui(0xBF00);
                            mtc1(v0, f1);
                            lwc1(f0, s1, 132);
                            mul_s(f2, f1, f0);
                            mtc1(zero, f1);
                            adda_s(f1, f6);
                            madd_s(f0, f3, f2);
                            swc1(f0, sp, 0xA8);
                            lwc1(f0, s0, 52);
                            adda_s(f1, f5);
                            madd_s(f0, f0, f2);
                            swc1(f0, sp, 0xAC);
                            lwc1(f0, s0, 56);
                            adda_s(f1, f4);
                            madd_s(f0, f0, f2);
                            swc1(f0, sp, 0xB0);
                            a0 = s0;
                            a1 = addiu(sp, 0xA8);
                            a2 = 2;
                            jal(ctx, 0x19CF0Cu, gen::fn_sub_4CB750_004cb750);
                            a0 = s0;
                            jal(ctx, 0x19CF18u, gen::fn_sub_4CB2F0_004cb2f0);
                            a0 = v0;
                            a1 = v0;
                            jal(ctx, 0x19CF28u, gen::fn_sub_4C2FB0_004c2fb0);
                            a0 = s1;
                            a1 = addiu(gp, -19384);  // &0x7CE138
                            a2 = 3;
                            jal(ctx, 0x19CF3Cu, gen::fn_RwCameraClear_004c9e90);
                            a0 = s1;
                            jal(ctx, 0x19CF48u, gen::fn_RwCameraBeginUpdate_004c9d10);
                            if (v0 == 0) {
                                // 0x0019d1b8
                                charge(ctx, 5);
                                a0 = 0x680000;
                                a0 = addiu(a0, -30392);  // "k_shadow.c"
                                a1 = 2032;
                                jal(ctx, 0x19D1C4u, gen::fn_sub_19D3F0_0019d3f0);
                            } else {
                                // 0x0019cf58
                                charge(ctx, 3);
                                a0 = 0;
                                for (;;) {
                                    // 0x0019cf88
                                    charge(ctx, 3);
                                    v0 = slti(a0, 5);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x0019cf64
                                    charge(ctx, 9);
                                    v0 = sll(a0, 1);
                                    v0 = addu(v0, a0);
                                    v1 = sll(v0, 2);
                                    lw(v0, s2, 296);
                                    v1 = addu(v0, v1);
                                    lbu(v0, v1, 948);
                                    v0 = v0 & 0xFE;
                                    sb(v0, v1, 948);
                                    a0 = addiu(a0, 1);
                                }
                                // 0x0019cf94
                                charge(ctx, 17);
                                v0 = 1;
                                sw(v0, gp, -19352);  // 0x7CE158
                                lw(v1, s2, 296);
                                lhu(v0, v1, 216);
                                v0 = v0 | 0x4;
                                sh(v0, v1, 216);
                                lw(a0, s2, 296);
                                jal(ctx, 0x19CFB0u, gen::fn_sub_317A20_00317a20);
                                lw(v1, s2, 296);
                                lhu(v0, v1, 216);
                                v0 = v0 & 0xFFFB;
                                sh(v0, v1, 216);
                                sw(zero, gp, -19352);  // 0x7CE158
                                a0 = 0;
                                for (;;) {
                                    // 0x0019cffc
                                    charge(ctx, 3);
                                    v0 = slti(a0, 5);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x0019cfd8
                                    charge(ctx, 9);
                                    v0 = sll(a0, 1);
                                    v0 = addu(v0, a0);
                                    v1 = sll(v0, 2);
                                    lw(v0, s2, 296);
                                    v1 = addu(v0, v1);
                                    lbu(v0, v1, 948);
                                    v0 = v0 | 0x1;
                                    sb(v0, v1, 948);
                                    a0 = addiu(a0, 1);
                                }
                                // 0x0019d008
                                charge(ctx, 99);
                                s3 = 0x960000;
                                s3 = addiu(s3, 144);  // &pfn_RwRenderStateSet
                                a0 = 14;
                                a1 = 0;
                                lw(v0, s3, 0);  // pfn_RwRenderStateSet
                                jalr(ctx, 0x19D01Cu, v0.u());
                                a0 = 6;
                                a1 = 0;
                                lw(v0, s3, 0);  // pfn_RwRenderStateSet
                                jalr(ctx, 0x19D030u, v0.u());
                                a0 = 8;
                                a1 = 0;
                                lw(v0, s3, 0);  // pfn_RwRenderStateSet
                                jalr(ctx, 0x19D044u, v0.u());
                                a0 = 7;
                                a1 = 2;
                                lw(v0, s3, 0);  // pfn_RwRenderStateSet
                                jalr(ctx, 0x19D058u, v0.u());
                                a0 = 1;
                                a1 = 0;
                                lw(v0, s3, 0);  // pfn_RwRenderStateSet
                                jalr(ctx, 0x19D06Cu, v0.u());
                                a0 = 2;
                                a1 = 68;
                                jal(ctx, 0x19D07Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
                                a0 = 3;
                                v0 = 0x70000;
                                a1 = v0 | 0x17FB;
                                jal(ctx, 0x19D090u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                s0 = 0x960000;
                                s0 = addiu(s0, 136);  // &g_rwIm2DNearScreenZ
                                mtc1(zero, f12);
                                v0 = 0x43000000;
                                mtc1(v0, f14);
                                v0 = 0x42400000;
                                mtc1(v0, f15);
                                v0 = 0x3F800000;
                                mtc1(v0, f1);
                                lwc1(f0, s1, 128);
                                div_s(f17, f1, f0);
                                mov_s(f13, f12);
                                a0 = 0x680000;
                                a0 = addiu(a0, -30368);  // &0x678960
                                a1 = 0x680000;
                                a1 = addiu(a1, -30364);  // &0x678964
                                lwc1(f16, s0, 0);  // g_rwIm2DNearScreenZ
                                jal(ctx, 0x19D0DCu, gen::fn_drawGradientQuad_001997e0);
                                a0 = 2;
                                a1 = 68;
                                jal(ctx, 0x19D0ECu, gen::fn_RpSkyRenderStateSet_004d7f60);
                                a0 = 3;
                                v0 = 0x30000;
                                a1 = v0 | 0xC803;
                                jal(ctx, 0x19D100u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                mtc1(zero, f12);
                                v0 = 0x42400000;
                                mtc1(v0, f13);
                                v0 = 0x43000000;
                                mtc1(v0, f14);
                                v0 = 0x3F800000;
                                mtc1(v0, f1);
                                lwc1(f0, s1, 128);
                                div_s(f17, f1, f0);
                                mov_s(f15, f14);
                                a0 = 0x680000;
                                a0 = addiu(a0, -30364);  // &0x678964
                                a1 = 0x680000;
                                a1 = addiu(a1, -30360);  // &0x678968
                                lwc1(f16, s0, 0);  // g_rwIm2DNearScreenZ
                                jal(ctx, 0x19D144u, gen::fn_drawGradientQuad_001997e0);
                                a0 = 2;
                                a1 = 68;
                                jal(ctx, 0x19D154u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                a0 = 3;
                                v0 = 0x70000;
                                a1 = v0 | 0x17FB;
                                jal(ctx, 0x19D168u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                a0 = 20;
                                a1 = 2;
                                lw(v0, s3, 0);  // pfn_RwRenderStateSet
                                jalr(ctx, 0x19D17Cu, v0.u());
                                lw(v0, gp, -19484);  // 0x7CE0D4
                                a1 = 1;
                                if (v0 == a1) {
                                    // 0x0019d194
                                    charge(ctx, 4);
                                    a0 = 14;
                                    lw(v0, s3, 0);
                                    jalr(ctx, 0x19D19Cu, v0.u());
                                }
                                // 0x0019d1a4
                                charge(ctx, 5);
                                a0 = s1;
                                jal(ctx, 0x19D1A8u, gen::fn_RwCameraEndUpdate_004c9d00);
                            }
                        }
                    }
                }
                // 0x0019d1cc
                charge(ctx, 1);
                lw(s2, s2, 248);
            }
            // 0x0019d1d8
            charge(ctx, 20);
            s0 = s5 & 0xFF;
            jal(ctx, 0x19D1DCu, gen::fn_sub_198570_00198570);
            sb(s0, v0, 2);
            jal(ctx, 0x19D1E8u, gen::fn_sub_198570_00198570);
            s0 = s6 & 0xFF;
            jal(ctx, 0x19D1F4u, gen::fn_sub_198580_00198580);
            sb(s0, v0, 2);
            jal(ctx, 0x19D200u, gen::fn_sub_198580_00198580);
            s0 = s7 & 0xFF;
            jal(ctx, 0x19D20Cu, gen::fn_sub_198560_00198560);
            sb(s0, v0, 2);
            jal(ctx, 0x19D218u, gen::fn_sub_198560_00198560);
        } else {
            // 0x0019c520
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0019c530
                charge(ctx, 4);
                v0 = addiu(v1, 1);
                sw(v0, s0, 0);
            } else {
                // 0x0019c528
                charge(ctx, 2);
            }
        }
        // 0x0019d234
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0019d238 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    ld(ra, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x140);
}

// 0x0019D270 sub_19D270 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_19D270(task): destroy callback of "shadow map camera": RwFree(work).
void sub_19D270(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0019d270
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x19D284u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0019D2A0 sub_19D2A0 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_19D2A0(parent) [K_Shadow_CreateMapCameraTask]: RwCalloc(1, 8), kwlnTaskCreate(parent, "shadow map camera",
// 0x814 (2068), sub_19C4B0, sub_19D270, work). Caller: K_SceneDraw_CreateTasks.
void sub_19D2A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0019d2a0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1;
    a1 = 8;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x19D2C4u, v0.u());
    if (v0 != 0) {
        // 0x0019d2e0
        charge(ctx, 11);
        a0 = s0;
        a1 = 0x680000;
        a1 = addiu(a1, -30352);  // "shadow map camera"
        a2 = 2068;
        a3 = 0x1A0000;
        a3 = addiu(a3, -15184);  // &sub_19C4B0
        t0 = 0x1A0000;
        t0 = addiu(t0, -11664);  // &sub_19D270
        t1 = v0;
        jal(ctx, 0x19D304u, gen::fn_kwlnTaskCreate_00194b20);
    } else {
        // 0x0019d2d4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0019d30c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0019D410 K_SceneDraw_UpdateDrwOpcFldTask -- 140 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// K_SceneDraw_UpdateDrwOpcFldTask(task): "draw opac field" (priority 0x816 = 2070): when the field record (K_Field_Get)
// has no +52 word, sub_1BD950 first; then for every field source of the resource list 12 (sub_3B5D50(12), linked by
// +248) whose flag word +40 has bit 1: K_FldSrc_DrawFieldOpaque(main camera, source +352). Returns 0.
void K_SceneDraw_UpdateDrwOpcFldTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0019d410
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 12;
    jal(ctx, 0x19D420u, gen::fn_sub_3B5D50_003b5d50);
    s0 = v0;
    jal(ctx, 0x19D42Cu, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, 52);
    if (v0 == 0) {
        // 0x0019d440
        charge(ctx, 4);
        jal(ctx, 0x19D440u, gen::fn_sub_1BD950_001bd950);
    }
    for (;;) {
        // 0x0019d47c
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0019d450
        charge(ctx, 4);
        lw(v0, s0, 40);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x0019d460
            charge(ctx, 6);
            jal(ctx, 0x19D460u, gen::fn_sub_198590_00198590);
            a0 = v0;
            lw(a1, s0, 352);
            jal(ctx, 0x19D470u, gen::fn_K_FldSrc_DrawFieldOpaque_001b3e50);
        }
        // 0x0019d478
        charge(ctx, 1);
        lw(s0, s0, 248);
    }
    // 0x0019d484
    charge(ctx, 6);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0019D4A0 sub_19D4A0 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_19D4A0(task) [K_SceneDraw_UpdateDrwTrnFldTask]: "draw trans field" (priority 0x104D = 4173): only while the
// field major (the first word of the field work *0x7CD540) is below 200: for every visible field source (list 12, flag
// bit 1) K_FldSrc_DrawFieldTrans(main camera, source +352). Returns 0.
void sub_19D4A0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0019d4a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -22448);  // 0x7CD540
    lw(v0, v0, 0);
    at = slti(v0, 200);
    if (at != 0) {
        // 0x0019d4c0
        charge(ctx, 6);
        a0 = 12;
        jal(ctx, 0x19D4C4u, gen::fn_sub_3B5D50_003b5d50);
        s0 = v0;
        for (;;) {
            // 0x0019d504
            charge(ctx, 2);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0019d4d8
            charge(ctx, 4);
            lw(v0, s0, 40);
            v0 = v0 & 0x2;
            if (v0 != 0) {
                // 0x0019d4e8
                charge(ctx, 6);
                jal(ctx, 0x19D4E8u, gen::fn_sub_198590_00198590);
                a0 = v0;
                lw(a1, s0, 352);
                jal(ctx, 0x19D4F8u, gen::fn_K_FldSrc_DrawFieldTrans_001b4720);
            }
            // 0x0019d500
            charge(ctx, 1);
            lw(s0, s0, 248);
        }
    }
    // 0x0019d50c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0019DE40 sub_19DE40 -- 56 bytes; frame 0x10: ra sp+0x0
// sub_19DE40(task) [K_SceneDraw_UpdateDrwTrnFldObjTask]: "draw trans field object" (priority 0x104C = 4172): sub_19DB10
// while the field major is below 200. Returns 0.
void sub_19DE40(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0019de40
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -22448);  // 0x7CD540
    lw(v0, v0, 0);
    at = slti(v0, 200);
    if (at != 0) {
        // 0x0019de5c
        charge(ctx, 2);
        jal(ctx, 0x19DE5Cu, gen::fn_sub_19DB10_0019db10);
    }
    // 0x0019de64 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0019E1B0 sub_19E1B0 -- 56 bytes; frame 0x10: ra sp+0x0
// sub_19E1B0(task) [K_SceneDraw_UpdateDrwTrnFldObjPreCharTask]: "draw trans field obj preChar" (priority 0x82F = 2095):
// sub_19DE80 while the field major is below 200. Returns 0.
void sub_19E1B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0019e1b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -22448);  // 0x7CD540
    lw(v0, v0, 0);
    at = slti(v0, 200);
    if (at != 0) {
        // 0x0019e1cc
        charge(ctx, 2);
        jal(ctx, 0x19E1CCu, gen::fn_sub_19DE80_0019de80);
    }
    // 0x0019e1d4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0019E1F0 sub_19E1F0 -- 316 bytes; frame 0x70: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// sub_19E1F0(a, b) [K_SceneDraw_CompareCameraDistance]: the qsort comparator of the character draw: the distance from the
// main camera's position (its frame's matrix, sub_4CB2F0, +48..+56) to the model position (the matrix of resource
// +296, sub_318B60, +48..+56) of *a minus that of *b (sub_4C6AC0 = the vector length), as an int.
void sub_19E1F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0019e1f0
    enter(ctx, 79);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    s0 = a1;
    jal(ctx, 0x19E210u, gen::fn_sub_198590_00198590);
    lw(a0, v0, 4);
    jal(ctx, 0x19E21Cu, gen::fn_sub_4CB2F0_004cb2f0);
    lwc1(f2, v0, 48);
    lwc1(f1, v0, 52);
    lwc1(f0, v0, 56);
    swc1(f2, sp, 0x40);
    swc1(f1, sp, 0x44);
    swc1(f0, sp, 0x48);
    lw(s1, s1, 0);
    lw(s0, s0, 0);
    lw(a0, s1, 296);
    jal(ctx, 0x19E248u, gen::fn_sub_318B60_00318b60);
    lwc1(f1, v0, 48);
    lwc1(f0, sp, 0x40);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x60);
    lwc1(f21, sp, 0x44);
    lw(a0, s1, 296);
    jal(ctx, 0x19E268u, gen::fn_sub_318B60_00318b60);
    lwc1(f0, v0, 52);
    sub_s(f0, f0, f21);
    swc1(f0, sp, 0x64);
    lwc1(f20, sp, 0x48);
    lw(a0, s1, 296);
    jal(ctx, 0x19E284u, gen::fn_sub_318B60_00318b60);
    lwc1(f0, v0, 56);
    sub_s(f0, f0, f20);
    swc1(f0, sp, 0x68);
    lw(a0, s0, 296);
    jal(ctx, 0x19E29Cu, gen::fn_sub_318B60_00318b60);
    lwc1(f1, v0, 48);
    lwc1(f0, sp, 0x40);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x50);
    lw(a0, s0, 296);
    jal(ctx, 0x19E2B8u, gen::fn_sub_318B60_00318b60);
    lwc1(f0, v0, 52);
    sub_s(f0, f0, f21);
    swc1(f0, sp, 0x54);
    lw(a0, s0, 296);
    jal(ctx, 0x19E2D0u, gen::fn_sub_318B60_00318b60);
    lwc1(f0, v0, 56);
    sub_s(f0, f0, f20);
    swc1(f0, sp, 0x58);
    a0 = addiu(sp, 0x60);
    jal(ctx, 0x19E2E8u, gen::fn_sub_4C6AC0_004c6ac0);
    mov_s(f20, f0);
    a0 = addiu(sp, 0x50);
    jal(ctx, 0x19E2F8u, gen::fn_sub_4C6AC0_004c6ac0);
    sub_s(f0, f20, f0);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0019E330 sub_19E330 -- 2828 bytes; frame 0x250: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_19E330(task) [K_SceneDraw_UpdateDrwCharModelTask]: "draw character model" (priority 0x824 = 2084, k_sceneDraw.c).
// Takes the light settings of the three lights (sub_198560 / 570 / 580) and the light records of lists 4 / 5; puts the
// characters (resource list 1) in a 64-entry frame array (K_Assert line 471 past 64) and, when the field work's +24
// word is 1, sorts it with qsort (sub_19E1F0: nearest first); then from the array's end down (far to near): sets the lights for the
// character (its own light colours / matrices at +300 / +316 / +336 / +400 / +416 when flag bit 31, its key light only
// with bit 30, else the field's from the light record), and a visible one (flag bit 1) is drawn on the main camera
// (sub_317A20 on model +296, plus model +488 with flag 0x20000000) with up to three effect markers (+256..+264) placed
// at the model's bone 2 or 175 above its position (sub_318ED0 / sub_34FDF0 / sub_34FD70); K_Assert line 549 when the
// camera cannot begin. Then the NPCs (list 3) and the other lists are drawn the same way in one camera pass (only
// opaque models: colour alpha 255).
void sub_19E330(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0019e330
    enter(ctx, 56);  // entry check point + this block's cycles
    sp = addiu(sp, -0x250);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 1;
    jal(ctx, 0x19E35Cu, gen::fn_sub_3B5D50_003b5d50);
    s4 = v0;
    a0 = 3;
    jal(ctx, 0x19E36Cu, gen::fn_sub_3B5D50_003b5d50);
    s1 = v0;
    a0 = 2;
    jal(ctx, 0x19E37Cu, gen::fn_sub_3B5D50_003b5d50);
    s0 = v0;
    a0 = 5;
    jal(ctx, 0x19E38Cu, gen::fn_sub_3B5D50_003b5d50);
    s2 = v0;
    a0 = 4;
    jal(ctx, 0x19E39Cu, gen::fn_sub_3B5D50_003b5d50);
    s6 = v0;
    jal(ctx, 0x19E3A8u, gen::fn_sub_198560_00198560);
    lwc1(f3, v0, 24);
    lwc1(f2, v0, 28);
    lwc1(f1, v0, 32);
    lwc1(f0, v0, 36);
    swc1(f3, sp, 0x230);
    swc1(f2, sp, 0x234);
    swc1(f1, sp, 0x238);
    swc1(f0, sp, 0x23C);
    jal(ctx, 0x19E3D0u, gen::fn_sub_198570_00198570);
    lwc1(f3, v0, 24);
    lwc1(f2, v0, 28);
    lwc1(f1, v0, 32);
    lwc1(f0, v0, 36);
    swc1(f3, sp, 0x220);
    swc1(f2, sp, 0x224);
    swc1(f1, sp, 0x228);
    swc1(f0, sp, 0x22C);
    jal(ctx, 0x19E3F8u, gen::fn_sub_198570_00198570);
    lw(v0, v0, 4);
    a2 = addiu(v0, 16);
    a1 = addiu(sp, 0x1E0);
    a0 = 8;
    for (;;) {
        // 0x0019e410
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
    // 0x0019e434
    charge(ctx, 16);
    jal(ctx, 0x19E434u, gen::fn_sub_198580_00198580);
    lwc1(f3, v0, 24);
    lwc1(f2, v0, 28);
    lwc1(f1, v0, 32);
    lwc1(f0, v0, 36);
    swc1(f3, sp, 0x1D0);
    swc1(f2, sp, 0x1D4);
    swc1(f1, sp, 0x1D8);
    swc1(f0, sp, 0x1DC);
    jal(ctx, 0x19E45Cu, gen::fn_sub_198580_00198580);
    lw(v0, v0, 4);
    a2 = addiu(v0, 16);
    a1 = addiu(sp, 0x190);
    a0 = 8;
    for (;;) {
        // 0x0019e474
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
    // 0x0019e498
    charge(ctx, 8);
    a0 = addiu(sp, 0x90);
    a1 = 0;
    a2 = 256;
    jal(ctx, 0x19E4A4u, gen::fn_memset_00521408);
    s3 = 0;
    for (;;) {
        // 0x0019e4ec
        charge(ctx, 2);
        if (s4 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0019e4b8
        charge(ctx, 3);
        v0 = sltiu(s3, 64);
        if (v0 == 0) {
            // 0x0019e4c4
            charge(ctx, 5);
            a0 = 0x680000;
            a0 = addiu(a0, -30328);  // "k_sceneDraw.c"
            a1 = 471;
            jal(ctx, 0x19E4D0u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x0019e4d8
        charge(ctx, 5);
        v0 = sll(s3, 2);
        v0 = addu(v0, sp);
        sw(s4, v0, 144);
        lw(s4, s4, 248);
        s3 = addiu(s3, 1);
    }
    // 0x0019e4f4
    charge(ctx, 5);
    lw(v0, gp, -22448);  // 0x7CD540
    lw(v1, v0, 24);
    v0 = 1;
    if (v1 == v0) {
        // 0x0019e508
        charge(ctx, 7);
        a0 = addiu(sp, 0x90);
        a1 = s3;
        a2 = 4;
        a3 = 0x1A0000;
        a3 = addiu(a3, -7696);  // &sub_19E1F0
        jal(ctx, 0x19E51Cu, gen::fn_qsort_005225f8);
    }
    // 0x0019e524
    charge(ctx, 3);
    s5 = addiu(s3, -1);
    for (;;) {
        // 0x0019e82c
        charge(ctx, 2);
        if (i64(s5) < 0) {
            break;
        }
        backedge(ctx);
        // 0x0019e530
        charge(ctx, 28);
        jal(ctx, 0x19E530u, gen::fn_sub_198560_00198560);
        a0 = v0;
        a1 = addiu(s6, 256);
        jal(ctx, 0x19E540u, gen::fn_sub_4944B0_004944b0);
        jal(ctx, 0x19E548u, gen::fn_sub_198580_00198580);
        a0 = v0;
        a1 = addiu(s6, 272);
        jal(ctx, 0x19E558u, gen::fn_sub_4944B0_004944b0);
        jal(ctx, 0x19E560u, gen::fn_sub_198580_00198580);
        lw(a0, v0, 4);
        a1 = addiu(s6, 288);
        a2 = 0;
        jal(ctx, 0x19E574u, gen::fn_sub_4CB7F0_004cb7f0);
        v0 = sll(s5, 2);
        v0 = addu(v0, sp);
        s3 = addiu(v0, 144);
        lw(s4, s3, 0);
        lw(v1, s4, 40);
        v0 = lui(0x8000);
        v0 = v1 & v0;
        if (v0 == 0) {
            // 0x0019e638
            charge(ctx, 4);
            v0 = 0x40000000;
            v0 = v1 & v0;
            if (v0 == 0) {
                // 0x0019e688
                charge(ctx, 13);
                jal(ctx, 0x19E688u, gen::fn_sub_198570_00198570);
                a0 = v0;
                a1 = addiu(s6, 352);
                jal(ctx, 0x19E698u, gen::fn_sub_4944B0_004944b0);
                jal(ctx, 0x19E6A0u, gen::fn_sub_198570_00198570);
                lw(a0, v0, 4);
                a1 = addiu(s6, 368);
                a2 = 0;
                jal(ctx, 0x19E6B4u, gen::fn_sub_4CB7F0_004cb7f0);
            } else {
                // 0x0019e648
                charge(ctx, 16);
                jal(ctx, 0x19E648u, gen::fn_sub_198570_00198570);
                a0 = v0;
                a1 = addiu(s4, 400);
                jal(ctx, 0x19E658u, gen::fn_sub_4944B0_004944b0);
                jal(ctx, 0x19E660u, gen::fn_sub_198570_00198570);
                lw(v1, s3, 0);
                lw(a0, v0, 4);
                a1 = addiu(v1, 416);
                a2 = 0;
                jal(ctx, 0x19E678u, gen::fn_sub_4CB7F0_004cb7f0);
            }
        } else {
            // 0x0019e5a0
            charge(ctx, 38);
            jal(ctx, 0x19E5A0u, gen::fn_sub_198560_00198560);
            a0 = v0;
            a1 = addiu(s4, 300);
            jal(ctx, 0x19E5B0u, gen::fn_sub_4944B0_004944b0);
            jal(ctx, 0x19E5B8u, gen::fn_sub_198580_00198580);
            lw(v1, s3, 0);
            a0 = v0;
            a1 = addiu(v1, 316);
            jal(ctx, 0x19E5CCu, gen::fn_sub_4944B0_004944b0);
            jal(ctx, 0x19E5D4u, gen::fn_sub_198570_00198570);
            lw(v1, s3, 0);
            a0 = v0;
            a1 = addiu(v1, 400);
            jal(ctx, 0x19E5E8u, gen::fn_sub_4944B0_004944b0);
            jal(ctx, 0x19E5F0u, gen::fn_sub_198580_00198580);
            lw(v1, s3, 0);
            lw(a0, v0, 4);
            a1 = addiu(v1, 336);
            a2 = 0;
            jal(ctx, 0x19E608u, gen::fn_sub_4CB7F0_004cb7f0);
            jal(ctx, 0x19E610u, gen::fn_sub_198570_00198570);
            lw(v1, s3, 0);
            lw(a0, v0, 4);
            a1 = addiu(v1, 416);
            a2 = 0;
            jal(ctx, 0x19E628u, gen::fn_sub_4CB7F0_004cb7f0);
        }
        // 0x0019e6bc
        charge(ctx, 5);
        lw(v0, s3, 0);
        lw(v0, v0, 40);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x0019e6d0
            charge(ctx, 7);
            jal(ctx, 0x19E6D0u, gen::fn_sub_198590_00198590);
            a0 = v0;
            jal(ctx, 0x19E6DCu, gen::fn_RwCameraBeginUpdate_004c9d10);
            if (v0 == 0) {
                // 0x0019e814
                charge(ctx, 5);
                a0 = 0x680000;
                a0 = addiu(a0, -30328);  // "k_sceneDraw.c"
                a1 = 549;
                jal(ctx, 0x19E820u, gen::fn_sub_19D3F0_0019d3f0);
            } else {
                // 0x0019e6ec
                charge(ctx, 11);
                v0 = sll(s5, 2);
                v0 = addu(v0, sp);
                s4 = addiu(v0, 144);
                lw(v0, s4, 0);
                lw(a0, v0, 296);
                jal(ctx, 0x19E700u, gen::fn_sub_317A20_00317a20);
                lw(v0, s4, 0);
                lw(a0, v0, 488);
                if (a0 != 0) {
                    // 0x0019e718
                    charge(ctx, 5);
                    lw(v1, v0, 40);
                    v0 = 0x20000000;
                    v0 = v1 & v0;
                    if (v0 != 0) {
                        // 0x0019e72c
                        charge(ctx, 2);
                        jal(ctx, 0x19E72Cu, gen::fn_sub_317A20_00317a20);
                    }
                }
                // 0x0019e734
                charge(ctx, 3);
                s4 = 0;
                for (;;) {
                    // 0x0019e7ec
                    charge(ctx, 3);
                    v0 = slti(s4, 3);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0019e740
                    charge(ctx, 6);
                    lw(v1, s3, 0);
                    v0 = sll(s4, 2);
                    v0 = addu(v1, v0);
                    lw(v0, v0, 256);
                    if (v0 != 0) {
                        // 0x0019e758
                        charge(ctx, 7);
                        lw(a0, v1, 296);
                        a1 = 2;
                        a2 = addiu(sp, 0x240);
                        jal(ctx, 0x19E764u, gen::fn_sub_318ED0_00318ed0);
                        if (v0 == 0) {
                            // 0x0019e774
                            charge(ctx, 16);
                            lw(v0, s3, 0);
                            lw(a0, v0, 296);
                            jal(ctx, 0x19E77Cu, gen::fn_sub_318B60_00318b60);
                            lwc1(f2, v0, 48);
                            lwc1(f1, v0, 52);
                            lwc1(f0, v0, 56);
                            swc1(f2, sp, 0x240);
                            swc1(f1, sp, 0x244);
                            swc1(f0, sp, 0x248);
                            lwc1(f1, sp, 0x244);
                            v0 = 0x432F0000;
                            mtc1(v0, f0);
                            add_s(f0, f1, f0);
                            swc1(f0, sp, 0x244);
                        }
                        // 0x0019e7b4
                        charge(ctx, 13);
                        s7 = sll(s4, 2);
                        lw(v0, s3, 0);
                        v0 = addu(v0, s7);
                        lw(a0, v0, 256);
                        a1 = addiu(sp, 0x240);
                        jal(ctx, 0x19E7C8u, gen::fn_sub_34FDF0_0034fdf0);
                        lw(v0, s3, 0);
                        v0 = addu(v0, s7);
                        lw(a0, v0, 256);
                        a1 = 5;
                        jal(ctx, 0x19E7E0u, gen::fn_sub_34FD70_0034fd70);
                    }
                    // 0x0019e7e8
                    charge(ctx, 1);
                    s4 = addiu(s4, 1);
                }
                // 0x0019e7f8
                charge(ctx, 7);
                jal(ctx, 0x19E7F8u, gen::fn_sub_198590_00198590);
                a0 = v0;
                jal(ctx, 0x19E804u, gen::fn_RwCameraEndUpdate_004c9d00);
            }
        }
        // 0x0019e828
        charge(ctx, 1);
        s5 = addiu(s5, -1);
    }
    // 0x0019e834
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x0019e83c
        charge(ctx, 39);
        jal(ctx, 0x19E83Cu, gen::fn_sub_198560_00198560);
        a0 = v0;
        a1 = addiu(s2, 256);
        jal(ctx, 0x19E84Cu, gen::fn_sub_4944B0_004944b0);
        jal(ctx, 0x19E854u, gen::fn_sub_198580_00198580);
        a0 = v0;
        a1 = addiu(s2, 272);
        jal(ctx, 0x19E864u, gen::fn_sub_4944B0_004944b0);
        jal(ctx, 0x19E86Cu, gen::fn_sub_198570_00198570);
        a0 = v0;
        a1 = addiu(s2, 352);
        jal(ctx, 0x19E87Cu, gen::fn_sub_4944B0_004944b0);
        jal(ctx, 0x19E884u, gen::fn_sub_198580_00198580);
        lw(a0, v0, 4);
        a1 = addiu(s2, 288);
        a2 = 0;
        jal(ctx, 0x19E898u, gen::fn_sub_4CB7F0_004cb7f0);
        jal(ctx, 0x19E8A0u, gen::fn_sub_198570_00198570);
        lw(a0, v0, 4);
        a1 = addiu(s2, 368);
        a2 = 0;
        jal(ctx, 0x19E8B4u, gen::fn_sub_4CB7F0_004cb7f0);
        jal(ctx, 0x19E8BCu, gen::fn_sub_198590_00198590);
        a0 = v0;
        jal(ctx, 0x19E8C8u, gen::fn_RwCameraBeginUpdate_004c9d10);
        if (v0 == 0) {
            // 0x0019ea38
            charge(ctx, 5);
            a0 = 0x680000;
            a0 = addiu(a0, -30328);  // "k_sceneDraw.c"
            a1 = 610;
            jal(ctx, 0x19EA44u, gen::fn_sub_19D3F0_0019d3f0);
        } else {
            // 0x0019e8d8
            charge(ctx, 2);
            for (;;) {
                // 0x0019ea14
                charge(ctx, 2);
                if (s1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0019e8e0
                charge(ctx, 7);
                lw(a0, s1, 296);
                jal(ctx, 0x19E8E4u, gen::fn_sub_318B00_00318b00);
                lbu(v0, v0, 3);
                at = slti(v0, 255);
                if (at == 0) {
                    // 0x0019e908
                    charge(ctx, 5);
                    lw(v1, s1, 40);
                    v0 = lui(0x8000);
                    v0 = v1 & v0;
                    if (v0 == 0) {
                        // 0x0019e91c
                        charge(ctx, 3);
                        v0 = v1 & 0x2;
                        if (v0 != 0) {
                            // 0x0019e928
                            charge(ctx, 6);
                            lw(a0, s1, 296);
                            jal(ctx, 0x19E92Cu, gen::fn_sub_317A20_00317a20);
                            lw(a0, s1, 492);
                            if (a0 != 0) {
                                // 0x0019e940
                                charge(ctx, 5);
                                lw(v1, s1, 40);
                                v0 = 0x20000000;
                                v0 = v1 & v0;
                                if (v0 != 0) {
                                    // 0x0019e954
                                    charge(ctx, 2);
                                    jal(ctx, 0x19E954u, gen::fn_sub_317A20_00317a20);
                                }
                            }
                            // 0x0019e95c
                            charge(ctx, 3);
                            s2 = 0;
                            for (;;) {
                                // 0x0019ea04
                                charge(ctx, 3);
                                v0 = slti(s2, 3);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x0019e968
                                charge(ctx, 5);
                                v0 = sll(s2, 2);
                                v0 = addu(s1, v0);
                                lw(v0, v0, 256);
                                if (v0 != 0) {
                                    // 0x0019e97c
                                    charge(ctx, 7);
                                    lw(a0, s1, 296);
                                    a1 = 2;
                                    a2 = addiu(sp, 0x240);
                                    jal(ctx, 0x19E988u, gen::fn_sub_318ED0_00318ed0);
                                    if (v0 == 0) {
                                        // 0x0019e998
                                        charge(ctx, 15);
                                        lw(a0, s1, 296);
                                        jal(ctx, 0x19E99Cu, gen::fn_sub_318B60_00318b60);
                                        lwc1(f2, v0, 48);
                                        lwc1(f1, v0, 52);
                                        lwc1(f0, v0, 56);
                                        swc1(f2, sp, 0x240);
                                        swc1(f1, sp, 0x244);
                                        swc1(f0, sp, 0x248);
                                        lwc1(f1, sp, 0x244);
                                        v0 = 0x432F0000;
                                        mtc1(v0, f0);
                                        add_s(f0, f1, f0);
                                        swc1(f0, sp, 0x244);
                                    }
                                    // 0x0019e9d4
                                    charge(ctx, 11);
                                    v0 = sll(s2, 2);
                                    v0 = addu(s1, v0);
                                    s3 = addiu(v0, 256);
                                    lw(a0, v0, 256);
                                    a1 = addiu(sp, 0x240);
                                    jal(ctx, 0x19E9E8u, gen::fn_sub_34FDF0_0034fdf0);
                                    lw(a0, s3, 0);
                                    a1 = 5;
                                    jal(ctx, 0x19E9F8u, gen::fn_sub_34FD70_0034fd70);
                                }
                                // 0x0019ea00
                                charge(ctx, 1);
                                s2 = addiu(s2, 1);
                            }
                        }
                    }
                    // 0x0019ea10
                    charge(ctx, 1);
                    lw(s1, s1, 248);
                } else {
                    // 0x0019e8fc
                    charge(ctx, 3);
                    lw(s1, s1, 248);
                }
            }
            // 0x0019ea1c
            charge(ctx, 7);
            jal(ctx, 0x19EA1Cu, gen::fn_sub_198590_00198590);
            a0 = v0;
            jal(ctx, 0x19EA28u, gen::fn_RwCameraEndUpdate_004c9d00);
        }
    }
    // 0x0019ea4c
    charge(ctx, 6);
    a0 = 3;
    jal(ctx, 0x19EA50u, gen::fn_sub_3B5D50_003b5d50);
    s2 = v0;
    for (;;) {
        // 0x0019ec64
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0019ea64
        charge(ctx, 7);
        lw(a0, s2, 296);
        jal(ctx, 0x19EA68u, gen::fn_sub_318B00_00318b00);
        lbu(v0, v0, 3);
        at = slti(v0, 255);
        if (at == 0) {
            // 0x0019ea8c
            charge(ctx, 5);
            lw(v1, s2, 40);
            v0 = lui(0x8000);
            v0 = v1 & v0;
            if (v0 != 0) {
                // 0x0019eaa0
                charge(ctx, 3);
                v0 = v1 & 0x2;
                if (v0 != 0) {
                    // 0x0019eaac
                    charge(ctx, 39);
                    jal(ctx, 0x19EAACu, gen::fn_sub_198560_00198560);
                    a0 = v0;
                    a1 = addiu(s2, 300);
                    jal(ctx, 0x19EABCu, gen::fn_sub_4944B0_004944b0);
                    jal(ctx, 0x19EAC4u, gen::fn_sub_198580_00198580);
                    a0 = v0;
                    a1 = addiu(s2, 316);
                    jal(ctx, 0x19EAD4u, gen::fn_sub_4944B0_004944b0);
                    jal(ctx, 0x19EADCu, gen::fn_sub_198570_00198570);
                    a0 = v0;
                    a1 = addiu(s2, 400);
                    jal(ctx, 0x19EAECu, gen::fn_sub_4944B0_004944b0);
                    jal(ctx, 0x19EAF4u, gen::fn_sub_198580_00198580);
                    lw(a0, v0, 4);
                    a1 = addiu(s2, 336);
                    a2 = 0;
                    jal(ctx, 0x19EB08u, gen::fn_sub_4CB7F0_004cb7f0);
                    jal(ctx, 0x19EB10u, gen::fn_sub_198570_00198570);
                    lw(a0, v0, 4);
                    a1 = addiu(s2, 416);
                    a2 = 0;
                    jal(ctx, 0x19EB24u, gen::fn_sub_4CB7F0_004cb7f0);
                    jal(ctx, 0x19EB2Cu, gen::fn_sub_198590_00198590);
                    a0 = v0;
                    jal(ctx, 0x19EB38u, gen::fn_RwCameraBeginUpdate_004c9d10);
                    if (v0 == 0) {
                        // 0x0019ec4c
                        charge(ctx, 5);
                        a0 = 0x680000;
                        a0 = addiu(a0, -30328);  // "k_sceneDraw.c"
                        a1 = 665;
                        jal(ctx, 0x19EC58u, gen::fn_sub_19D3F0_0019d3f0);
                    } else {
                        // 0x0019eb48
                        charge(ctx, 6);
                        lw(a0, s2, 296);
                        jal(ctx, 0x19EB4Cu, gen::fn_sub_317A20_00317a20);
                        lw(a0, s2, 492);
                        if (a0 != 0) {
                            // 0x0019eb60
                            charge(ctx, 5);
                            lw(v1, s2, 40);
                            v0 = 0x20000000;
                            v0 = v1 & v0;
                            if (v0 != 0) {
                                // 0x0019eb74
                                charge(ctx, 2);
                                jal(ctx, 0x19EB74u, gen::fn_sub_317A20_00317a20);
                            }
                        }
                        // 0x0019eb7c
                        charge(ctx, 3);
                        s1 = 0;
                        for (;;) {
                            // 0x0019ec24
                            charge(ctx, 3);
                            v0 = slti(s1, 3);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0019eb88
                            charge(ctx, 5);
                            v0 = sll(s1, 2);
                            v0 = addu(s2, v0);
                            lw(v0, v0, 256);
                            if (v0 != 0) {
                                // 0x0019eb9c
                                charge(ctx, 7);
                                lw(a0, s2, 296);
                                a1 = 2;
                                a2 = addiu(sp, 0x240);
                                jal(ctx, 0x19EBA8u, gen::fn_sub_318ED0_00318ed0);
                                if (v0 == 0) {
                                    // 0x0019ebb8
                                    charge(ctx, 15);
                                    lw(a0, s2, 296);
                                    jal(ctx, 0x19EBBCu, gen::fn_sub_318B60_00318b60);
                                    lwc1(f2, v0, 48);
                                    lwc1(f1, v0, 52);
                                    lwc1(f0, v0, 56);
                                    swc1(f2, sp, 0x240);
                                    swc1(f1, sp, 0x244);
                                    swc1(f0, sp, 0x248);
                                    lwc1(f1, sp, 0x244);
                                    v0 = 0x432F0000;
                                    mtc1(v0, f0);
                                    add_s(f0, f1, f0);
                                    swc1(f0, sp, 0x244);
                                }
                                // 0x0019ebf4
                                charge(ctx, 11);
                                v0 = sll(s1, 2);
                                v0 = addu(s2, v0);
                                s3 = addiu(v0, 256);
                                lw(a0, v0, 256);
                                a1 = addiu(sp, 0x240);
                                jal(ctx, 0x19EC08u, gen::fn_sub_34FDF0_0034fdf0);
                                lw(a0, s3, 0);
                                a1 = 5;
                                jal(ctx, 0x19EC18u, gen::fn_sub_34FD70_0034fd70);
                            }
                            // 0x0019ec20
                            charge(ctx, 1);
                            s1 = addiu(s1, 1);
                        }
                        // 0x0019ec30
                        charge(ctx, 7);
                        jal(ctx, 0x19EC30u, gen::fn_sub_198590_00198590);
                        a0 = v0;
                        jal(ctx, 0x19EC3Cu, gen::fn_RwCameraEndUpdate_004c9d00);
                    }
                }
            }
            // 0x0019ec60
            charge(ctx, 1);
            lw(s2, s2, 248);
        } else {
            // 0x0019ea80
            charge(ctx, 3);
            lw(s2, s2, 248);
        }
    }
    // 0x0019ec6c
    charge(ctx, 2);
    for (;;) {
        // 0x0019ed80
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0019ec74
        charge(ctx, 4);
        lw(v1, s0, 40);
        v0 = v1 & 0x2;
        if (v0 != 0) {
            // 0x0019ec84
            charge(ctx, 4);
            v0 = 0x10000;
            v0 = v1 & v0;
            if (v0 != 0) {
                // 0x0019ec94
                charge(ctx, 39);
                jal(ctx, 0x19EC94u, gen::fn_sub_198560_00198560);
                a0 = v0;
                a1 = addiu(s0, 284);
                jal(ctx, 0x19ECA4u, gen::fn_sub_4944B0_004944b0);
                jal(ctx, 0x19ECACu, gen::fn_sub_198580_00198580);
                a0 = v0;
                a1 = addiu(s0, 300);
                jal(ctx, 0x19ECBCu, gen::fn_sub_4944B0_004944b0);
                jal(ctx, 0x19ECC4u, gen::fn_sub_198570_00198570);
                a0 = v0;
                a1 = addiu(s0, 384);
                jal(ctx, 0x19ECD4u, gen::fn_sub_4944B0_004944b0);
                jal(ctx, 0x19ECDCu, gen::fn_sub_198580_00198580);
                lw(a0, v0, 4);
                a1 = addiu(s0, 320);
                a2 = 0;
                jal(ctx, 0x19ECF0u, gen::fn_sub_4CB7F0_004cb7f0);
                jal(ctx, 0x19ECF8u, gen::fn_sub_198570_00198570);
                lw(a0, v0, 4);
                a1 = addiu(s0, 400);
                a2 = 0;
                jal(ctx, 0x19ED0Cu, gen::fn_sub_4CB7F0_004cb7f0);
                jal(ctx, 0x19ED14u, gen::fn_sub_198590_00198590);
                a0 = v0;
                jal(ctx, 0x19ED20u, gen::fn_RwCameraBeginUpdate_004c9d10);
                if (v0 == 0) {
                    // 0x0019ed68
                    charge(ctx, 5);
                    a0 = 0x680000;
                    a0 = addiu(a0, -30328);  // "k_sceneDraw.c"
                    a1 = 695;
                    jal(ctx, 0x19ED74u, gen::fn_sub_19D3F0_0019d3f0);
                } else {
                    // 0x0019ed30
                    charge(ctx, 14);
                    lw(a0, s0, 280);
                    a1 = 3;
                    jal(ctx, 0x19ED38u, gen::fn_sub_319230_00319230);
                    lw(a0, s0, 280);
                    jal(ctx, 0x19ED44u, gen::fn_sub_317A20_00317a20);
                    jal(ctx, 0x19ED4Cu, gen::fn_sub_198590_00198590);
                    a0 = v0;
                    jal(ctx, 0x19ED58u, gen::fn_RwCameraEndUpdate_004c9d00);
                }
            }
        }
        // 0x0019ed7c
        charge(ctx, 1);
        lw(s0, s0, 248);
    }
    // 0x0019ed88
    charge(ctx, 45);
    jal(ctx, 0x19ED88u, gen::fn_sub_198560_00198560);
    a0 = v0;
    a1 = addiu(sp, 0x230);
    jal(ctx, 0x19ED98u, gen::fn_sub_4944B0_004944b0);
    jal(ctx, 0x19EDA0u, gen::fn_sub_198580_00198580);
    a0 = v0;
    a1 = addiu(sp, 0x1D0);
    jal(ctx, 0x19EDB0u, gen::fn_sub_4944B0_004944b0);
    jal(ctx, 0x19EDB8u, gen::fn_sub_198570_00198570);
    a0 = v0;
    a1 = addiu(sp, 0x220);
    jal(ctx, 0x19EDC8u, gen::fn_sub_4944B0_004944b0);
    jal(ctx, 0x19EDD0u, gen::fn_sub_198580_00198580);
    lw(a0, v0, 4);
    a1 = addiu(sp, 0x190);
    a2 = 0;
    jal(ctx, 0x19EDE4u, gen::fn_sub_4CB7F0_004cb7f0);
    jal(ctx, 0x19EDECu, gen::fn_sub_198570_00198570);
    lw(a0, v0, 4);
    a1 = addiu(sp, 0x1E0);
    a2 = 0;
    jal(ctx, 0x19EE00u, gen::fn_sub_4CB7F0_004cb7f0);
    v0 = 0;
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x250);
}

// 0x0019EE40 sub_19EE40 -- 316 bytes; frame 0x70: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// sub_19EE40(a, b) [K_SceneDraw_CompareCameraDistance2]: the same comparator as sub_19E1F0 (an identical body: camera
// distance of *a minus that of *b).
void sub_19EE40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0019ee40
    enter(ctx, 79);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    s0 = a1;
    jal(ctx, 0x19EE60u, gen::fn_sub_198590_00198590);
    lw(a0, v0, 4);
    jal(ctx, 0x19EE6Cu, gen::fn_sub_4CB2F0_004cb2f0);
    lwc1(f2, v0, 48);
    lwc1(f1, v0, 52);
    lwc1(f0, v0, 56);
    swc1(f2, sp, 0x40);
    swc1(f1, sp, 0x44);
    swc1(f0, sp, 0x48);
    lw(s1, s1, 0);
    lw(s0, s0, 0);
    lw(a0, s1, 296);
    jal(ctx, 0x19EE98u, gen::fn_sub_318B60_00318b60);
    lwc1(f1, v0, 48);
    lwc1(f0, sp, 0x40);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x60);
    lwc1(f21, sp, 0x44);
    lw(a0, s1, 296);
    jal(ctx, 0x19EEB8u, gen::fn_sub_318B60_00318b60);
    lwc1(f0, v0, 52);
    sub_s(f0, f0, f21);
    swc1(f0, sp, 0x64);
    lwc1(f20, sp, 0x48);
    lw(a0, s1, 296);
    jal(ctx, 0x19EED4u, gen::fn_sub_318B60_00318b60);
    lwc1(f0, v0, 56);
    sub_s(f0, f0, f20);
    swc1(f0, sp, 0x68);
    lw(a0, s0, 296);
    jal(ctx, 0x19EEECu, gen::fn_sub_318B60_00318b60);
    lwc1(f1, v0, 48);
    lwc1(f0, sp, 0x40);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x50);
    lw(a0, s0, 296);
    jal(ctx, 0x19EF08u, gen::fn_sub_318B60_00318b60);
    lwc1(f0, v0, 52);
    sub_s(f0, f0, f21);
    swc1(f0, sp, 0x54);
    lw(a0, s0, 296);
    jal(ctx, 0x19EF20u, gen::fn_sub_318B60_00318b60);
    lwc1(f0, v0, 56);
    sub_s(f0, f0, f20);
    swc1(f0, sp, 0x58);
    a0 = addiu(sp, 0x60);
    jal(ctx, 0x19EF38u, gen::fn_sub_4C6AC0_004c6ac0);
    mov_s(f20, f0);
    a0 = addiu(sp, 0x50);
    jal(ctx, 0x19EF48u, gen::fn_sub_4C6AC0_004c6ac0);
    sub_s(f0, f20, f0);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0019F730 K_SceneDraw_CreateTasks -- 444 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// K_SceneDraw_CreateTasks(parent): "scene draw CTL" (kwlnTaskCreateWithAutoPriority(parent, 10, ...), no callbacks)
// and its children, in priority order: "shadow map camera" (sub_19D2A0, 2068), "draw opac field" (2070), "draw opac
// field object" (2071), "draw character model" (2084), "draw trans field obj preChar" (2095), "draw persona model"
// (4168), "draw trans field object" (4172), "draw trans field" (4173), "draw trans field(sort)" (4183) and "draw trans
// NPC(sort)" (4183). Returns the control task. Caller: kwlnRootUpdateTask state 0.
void K_SceneDraw_CreateTasks(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0019f730
    enter(ctx, 111);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a1 = 10;
    a2 = 0x680000;
    a2 = addiu(a2, -30312);  // "scene draw CTL"
    a3 = 0;
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x19F754u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x19F764u, gen::fn_sub_19D2A0_0019d2a0);
    a0 = s0;
    a1 = 0x680000;
    a1 = addiu(a1, -30288);  // "draw opac field"
    a2 = 2070;
    a3 = 0x1A0000;
    a3 = addiu(a3, -11248);  // &K_SceneDraw_UpdateDrwOpcFldTask
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x19F78Cu, gen::fn_kwlnTaskCreate_00194b20);
    a0 = s0;
    a1 = 0x680000;
    a1 = addiu(a1, -30272);  // "draw opac field object"
    a2 = 2071;
    a3 = 0x1A0000;
    a3 = addiu(a3, -10368);  // &K_SceneDraw_UpdateDrwOpcFldObjTask
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x19F7B4u, gen::fn_kwlnTaskCreate_00194b20);
    a0 = s0;
    a1 = 0x680000;
    a1 = addiu(a1, -30240);  // "draw character model"
    a2 = 2084;
    a3 = 0x1A0000;
    a3 = addiu(a3, -7376);  // &sub_19E330
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x19F7DCu, gen::fn_kwlnTaskCreate_00194b20);
    a0 = s0;
    a1 = 0x680000;
    a1 = addiu(a1, -30208);  // "draw trans field obj preChar"
    a2 = 2095;
    a3 = 0x1A0000;
    a3 = addiu(a3, -7760);  // &sub_19E1B0
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x19F804u, gen::fn_kwlnTaskCreate_00194b20);
    a0 = s0;
    a1 = 0x680000;
    a1 = addiu(a1, -30176);  // "draw persona model"
    a2 = 4168;
    a3 = 0x1A0000;
    a3 = addiu(a3, -2960);  // &sub_19F470
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x19F82Cu, gen::fn_kwlnTaskCreate_00194b20);
    a0 = s0;
    a1 = 0x680000;
    a1 = addiu(a1, -30144);  // "draw trans field object"
    a2 = 4172;
    a3 = 0x1A0000;
    a3 = addiu(a3, -8640);  // &sub_19DE40
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x19F854u, gen::fn_kwlnTaskCreate_00194b20);
    a0 = s0;
    a1 = 0x680000;
    a1 = addiu(a1, -30112);  // "draw trans field"
    a2 = 4173;
    a3 = 0x1A0000;
    a3 = addiu(a3, -11104);  // &sub_19D4A0
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x19F87Cu, gen::fn_kwlnTaskCreate_00194b20);
    a0 = s0;
    a1 = 0x680000;
    a1 = addiu(a1, -30080);  // "draw trans field(sort)"
    a2 = 4183;
    a3 = 0x1A0000;
    a3 = addiu(a3, -10960);  // &sub_19D530
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x19F8A4u, gen::fn_kwlnTaskCreate_00194b20);
    a0 = s0;
    a1 = 0x680000;
    a1 = addiu(a1, -30048);  // "draw trans NPC(sort)"
    a2 = 4183;
    a3 = 0x1A0000;
    a3 = addiu(a3, -4224);  // &sub_19EF80
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x19F8CCu, gen::fn_kwlnTaskCreate_00194b20);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0019F8F0 sub_19F8F0 -- 1092 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_19F8F0(float scale[4]) [K_SceneDraw_SetColorScale]: applies an RGBA scale to the scene: every field source
// (list 12) gets it (sub_1B56F0); sub_1A0040(1, 1) when some colour factor and the alpha are positive, else (0, 1);
// the clear colour = the base clear colour (sub_1985D0) scaled and clamped to 255 (sub_1985B0); the fog colour bytes
// 0x7CE0D8..0x7CE0E4 = the base bytes 0x7CE0E8..0x7CE0F4 scaled the same way. Callers: sub_29FAA0, sub_2A0440,
// sub_3556D0.
void sub_19F8F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0019f8f0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 12;
    jal(ctx, 0x19F908u, gen::fn_sub_3B5D50_003b5d50);
    s0 = v0;
    for (;;) {
        // 0x0019f930
        charge(ctx, 3);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0019f91c
        charge(ctx, 5);
        lw(a0, s0, 352);
        a1 = s1;
        jal(ctx, 0x19F924u, gen::fn_sub_1B56F0_001b56f0);
        lw(s0, s0, 248);
    }
    // 0x0019f93c: sub_1A0040(on, 1) -- on when a colour factor (r, g or b) and the alpha factor are positive
    charge(ctx, 6);
    lwc1(f0, s1, 0);
    mtc1(zero, f1);
    c_le_s(f0, f1);
    bool any_colour = true;  // host-side: r, g or b > 0 (the original tests them in that order)
    if (cond(ctx)) {
        // 0x0019f954: r <= 0
        charge(ctx, 4);
        lwc1(f0, s1, 4);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0019f964: g <= 0
            charge(ctx, 4);
            lwc1(f0, s1, 8);
            c_le_s(f0, f1);
            any_colour = !cond(ctx);
        }
    }
    bool on = false;  // host-side: ... and the alpha factor > 0
    if (any_colour) {
        // 0x0019f974
        charge(ctx, 6);
        lwc1(f1, s1, 12);
        mtc1(zero, f0);
        c_le_s(f1, f0);
        on = !cond(ctx);
    }
    if (!on) {
        // 0x0019f98c
        charge(ctx, 6);
        a0 = 0;
        a1 = 1;
        jal(ctx, 0x19F994u, gen::fn_sub_1A0040_001a0040);
    } else {
        // 0x0019f9a4
        charge(ctx, 4);
        a0 = 1;
        a1 = a0;
        jal(ctx, 0x19F9ACu, gen::fn_sub_1A0040_001a0040);
    }
    // 0x0019f9b4: the clear colour = the base clear colour scaled, clamped to 255
    charge(ctx, 23);
    jal(ctx, 0x19F9B4u, gen::fn_sub_1985D0_001985d0);
    lbu(a1, v0, 0);
    lbu(a0, v0, 1);
    lbu(v1, v0, 2);
    lbu(v0, v0, 3);
    sb(a1, sp, 0x3C);
    sb(a0, sp, 0x3D);
    sb(v1, sp, 0x3E);
    sb(v0, sp, 0x3F);
    lbu(v0, gp, -19452);  // 0x7CE0F4
    v1 = sll(v0, 24);
    lbu(v0, gp, -19464);  // 0x7CE0E8
    v0 = sll(v0, 16);
    v1 = v1 | v0;
    lbu(v0, gp, -19460);  // 0x7CE0EC
    v0 = sll(v0, 8);
    v1 = v0 | v1;
    lbu(v0, gp, -19456);  // 0x7CE0F0
    s0 = v0 | v1;
    lbu(v0, sp, 0x3C);
    if (i64(v0) < 0) {
        // 0x0019fa24
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0019fa10
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0019fa40
    charge(ctx, 7);
    lwc1(f0, s1, 0);
    mul_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    lbu(v0, sp, 0x3D);
    if (i64(v0) < 0) {
        // 0x0019fa70
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0019fa5c
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0019fa8c
    charge(ctx, 7);
    lwc1(f0, s1, 4);
    mul_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(a1, f0);
    lbu(v0, sp, 0x3E);
    if (i64(v0) < 0) {
        // 0x0019fabc
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0019faa8
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0019fad8
    charge(ctx, 7);
    lwc1(f0, s1, 8);
    mul_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(a2, f0);
    lbu(v0, sp, 0x3F);
    if (i64(v0) < 0) {
        // 0x0019fb08
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0019faf4
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0019fb24
    charge(ctx, 8);
    lwc1(f0, s1, 12);
    mul_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    at = sltiu(v0, 256);
    if (at == 0) {
        // 0x0019fb44
        charge(ctx, 1);
        v0 = 255;
    }
    // 0x0019fb48
    charge(ctx, 3);
    at = sltiu(a2, 256);
    if (at == 0) {
        // 0x0019fb54
        charge(ctx, 1);
        a2 = 255;
    }
    // 0x0019fb58
    charge(ctx, 3);
    at = sltiu(a1, 256);
    if (at == 0) {
        // 0x0019fb64
        charge(ctx, 1);
        a1 = 255;
    }
    // 0x0019fb68
    charge(ctx, 3);
    at = sltiu(a0, 256);
    if (at == 0) {
        // 0x0019fb74
        charge(ctx, 1);
        a0 = 255;
    }
    // 0x0019fb78
    charge(ctx, 10);
    a0 = a0 & 0xFF;
    a1 = a1 & 0xFF;
    a2 = a2 & 0xFF;
    a3 = v0 & 0xFF;
    jal(ctx, 0x19FB88u, gen::fn_sub_1985B0_001985b0);
    v1 = srl(s0, 16);
    v1 = v1 & 0xFF;
    if (i64(v1) < 0) {
        // 0x0019fbb4
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0019fba0
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0019fbd0
    charge(ctx, 8);
    lwc1(f0, s1, 0);
    mul_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(a3, f0);
    v1 = srl(s0, 8);
    v1 = v1 & 0xFF;
    if (i64(v1) < 0) {
        // 0x0019fc04
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0019fbf0
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0019fc20
    charge(ctx, 7);
    lwc1(f0, s1, 4);
    mul_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(a2, f0);
    v1 = s0 & 0xFF;
    if (i64(v1) < 0) {
        // 0x0019fc50
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0019fc3c
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0019fc6c
    charge(ctx, 8);
    lwc1(f0, s1, 8);
    mul_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(a1, f0);
    v1 = srl(s0, 24);
    v1 = v1 & 0xFF;
    if (i64(v1) < 0) {
        // 0x0019fca0
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0019fc8c
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0019fcbc
    charge(ctx, 7);
    lwc1(f0, s1, 12);
    mul_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(v1, f0);
    at = sltiu(a3, 256);
    if (at == 0) {
        // 0x0019fcd8
        charge(ctx, 1);
        a3 = 255;
    }
    // 0x0019fcdc
    charge(ctx, 4);
    sb(a3, gp, -19480);  // 0x7CE0D8
    at = sltiu(a2, 256);
    if (at == 0) {
        // 0x0019fcec
        charge(ctx, 1);
        a2 = 255;
    }
    // 0x0019fcf0
    charge(ctx, 4);
    sb(a2, gp, -19476);  // 0x7CE0DC
    at = sltiu(a1, 256);
    if (at == 0) {
        // 0x0019fd00
        charge(ctx, 1);
        a1 = 255;
    }
    // 0x0019fd04
    charge(ctx, 4);
    sb(a1, gp, -19472);  // 0x7CE0E0
    at = sltiu(v1, 256);
    if (at == 0) {
        // 0x0019fd14
        charge(ctx, 1);
        v1 = 255;
    }
    // 0x0019fd18 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sb(v1, gp, -19468);  // 0x7CE0E4
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0019FDD0 sub_19FDD0 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_19FDD0(arg): sub_3B5D50(12) (result unused), then sub_1B5950(field work +36, arg). Caller: sub_1B61F0.
void sub_19FDD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0019fdd0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 12;
    jal(ctx, 0x19FDE4u, gen::fn_sub_3B5D50_003b5d50);
    lw(v0, gp, -22448);  // 0x7CD540
    lw(a0, v0, 36);
    a1 = s0;
    jal(ctx, 0x19FDF8u, gen::fn_sub_1B5950_001b5950);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0019FE20 sub_19FE20 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_19FE20(arg): sub_3B5D50(12), then sub_1B5990(field work +36, arg). Caller: sub_1B61F0.
void sub_19FE20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0019fe20
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 12;
    jal(ctx, 0x19FE34u, gen::fn_sub_3B5D50_003b5d50);
    lw(v0, gp, -22448);  // 0x7CD540
    lw(a0, v0, 36);
    a1 = s0;
    jal(ctx, 0x19FE48u, gen::fn_sub_1B5990_001b5990);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0019FE70 sub_19FE70 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_19FE70(arg): sub_3B5D50(12), then sub_1B59C0(field work +36, arg). Caller: sub_1B61F0.
void sub_19FE70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0019fe70
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 12;
    jal(ctx, 0x19FE84u, gen::fn_sub_3B5D50_003b5d50);
    lw(v0, gp, -22448);  // 0x7CD540
    lw(a0, v0, 36);
    a1 = s0;
    jal(ctx, 0x19FE98u, gen::fn_sub_1B59C0_001b59c0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0019FEC0 sub_19FEC0 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_19FEC0(arg): sub_3B5D50(12), then sub_1B5A00(field work +36, arg). Callers: sub_1B61F0, sub_1BA8D0.
void sub_19FEC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0019fec0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 12;
    jal(ctx, 0x19FED4u, gen::fn_sub_3B5D50_003b5d50);
    lw(v0, gp, -22448);  // 0x7CD540
    lw(a0, v0, 36);
    a1 = s0;
    jal(ctx, 0x19FEE8u, gen::fn_sub_1B5A00_001b5a00);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0019FF10 sub_19FF10 -- 292 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_19FF10() [K_SceneDraw_ResetFieldLightFrame]: resets the frame of the field record sub_3B5D50(12): +256 = (c, c,
// c, 0) with c the float 0x7CAD7C, +272 = (0.5, 0.5, 0.5, 0), the matrix at +288 = identity (with flags +300 |=
// 0x20003), then two rotations of it (sub_4C31B0 with the axes (0, 1, 0) and (1, 0, 0), mode 2). Callers: sub_1B10F0,
// sub_1BB300.
void sub_19FF10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x0019ff10
    enter(ctx, 73);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 12;
    jal(ctx, 0x19FF28u, gen::fn_sub_3B5D50_003b5d50);
    s2 = addiu(v0, 256);
    a0 = 12;
    jal(ctx, 0x19FF38u, gen::fn_sub_3B5D50_003b5d50);
    s1 = addiu(v0, 272);
    a0 = 12;
    jal(ctx, 0x19FF48u, gen::fn_sub_3B5D50_003b5d50);
    s0 = addiu(v0, 288);
    lwc1(f0, gp, -32628);  // 0x7CAD7C
    swc1(f0, s2, 0);
    swc1(f0, s2, 4);
    swc1(f0, s2, 8);
    sw(zero, s2, 12);
    v1 = 0x3F000000;
    sw(v1, s1, 0);
    sw(v1, s1, 4);
    sw(v1, s1, 8);
    sw(zero, s1, 12);
    a1 = 0x3F800000;
    sw(a1, v0, 328);
    sw(a1, v0, 308);
    sw(a1, v0, 288);
    sw(zero, v0, 304);
    sw(zero, v0, 296);
    sw(zero, v0, 292);
    sw(zero, v0, 324);
    sw(zero, v0, 320);
    sw(zero, v0, 312);
    sw(zero, v0, 344);
    sw(zero, v0, 340);
    sw(zero, v0, 336);
    lw(a0, v0, 300);
    v1 = 0x20000;
    v1 = v1 | 0x3;
    v1 = a0 | v1;
    sw(v1, v0, 300);
    sw(zero, sp, 0x40);
    sw(a1, sp, 0x44);
    sw(zero, sp, 0x48);
    v0 = lui(0xC334);
    mtc1(v0, f12);
    a0 = s0;
    a1 = addiu(sp, 0x40);
    a2 = 2;
    jal(ctx, 0x19FFE4u, gen::fn_sub_4C31B0_004c31b0);
    v0 = 0x3F800000;
    sw(v0, sp, 0x40);
    sw(zero, sp, 0x44);
    sw(zero, sp, 0x48);
    v0 = lui(0xC234);
    mtc1(v0, f12);
    a0 = s0;
    a1 = addiu(sp, 0x40);
    a2 = 2;
    jal(ctx, 0x1A0010u, gen::fn_sub_4C31B0_004c31b0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

}  // namespace p3fes::game
