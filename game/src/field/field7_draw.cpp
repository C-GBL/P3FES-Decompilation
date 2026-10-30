// Phase 5 slice field7, part 3 (field7_draw.h): the frame helpers, the circle draw, the matrix angles, the model fade,
// the k_clump.c draw lists and the translucent queue of the 0x1A0000 band. Started from p3fes_handgen's bodies
// (register for register, block for block as the recompiled ones; game/include/p3fes/game/hg_cpu.h) and made readable
// on top: a role comment per function, named offsets, structured control flow (one host flag where five tests shared
// a block), block roles. Every path keeps the original's statements, charges and check points in order;
// tests/game/test_field7_draw.cpp pairs them.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/field7_draw.h"

namespace p3fes::recomp_gen {
void fn_atan2f_0052ea18(p3fes::EEContext&);
void fn_atomicGetWorldBoundingSphere_004912b0(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_geometryLock_00493370(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchyByName_00194fe0(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1A13B0_001a13b0(p3fes::EEContext&);
void fn_sub_1A1540_001a1540(p3fes::EEContext&);
void fn_sub_1A4DF0_001a4df0(p3fes::EEContext&);
void fn_sub_1A4E50_001a4e50(p3fes::EEContext&);
void fn_sub_1A4ED0_001a4ed0(p3fes::EEContext&);
void fn_sub_1A4F40_001a4f40(p3fes::EEContext&);
void fn_sub_1A5000_001a5000(p3fes::EEContext&);
void fn_sub_1A56B0_001a56b0(p3fes::EEContext&);
void fn_sub_1A56C0_001a56c0(p3fes::EEContext&);
void fn_sub_1A56D0_001a56d0(p3fes::EEContext&);
void fn_sub_1A5700_001a5700(p3fes::EEContext&);
void fn_sub_1A57A0_001a57a0(p3fes::EEContext&);
void fn_sub_1A5AA0_001a5aa0(p3fes::EEContext&);
void fn_sub_1A5B30_001a5b30(p3fes::EEContext&);
void fn_sub_1A5BC0_001a5bc0(p3fes::EEContext&);
void fn_sub_1A5E70_001a5e70(p3fes::EEContext&);
void fn_sub_1A5F30_001a5f30(p3fes::EEContext&);
void fn_sub_1A60A0_001a60a0(p3fes::EEContext&);
void fn_sub_1A6260_001a6260(p3fes::EEContext&);
void fn_sub_1A6290_001a6290(p3fes::EEContext&);
void fn_sub_1A7030_001a7030(p3fes::EEContext&);
void fn_sub_1A70A0_001a70a0(p3fes::EEContext&);
void fn_sub_1A71A0_001a71a0(p3fes::EEContext&);
void fn_sub_1A74B0_001a74b0(p3fes::EEContext&);
void fn_sub_1A7660_001a7660(p3fes::EEContext&);
void fn_sub_1A76E0_001a76e0(p3fes::EEContext&);
void fn_sub_1A8820_001a8820(p3fes::EEContext&);
void fn_sub_1A8910_001a8910(p3fes::EEContext&);
void fn_sub_1A8920_001a8920(p3fes::EEContext&);
void fn_sub_1A89C0_001a89c0(p3fes::EEContext&);
void fn_sub_1ACC30_001acc30(p3fes::EEContext&);
void fn_sub_318AD0_00318ad0(p3fes::EEContext&);
void fn_sub_359B40_00359b40(p3fes::EEContext&);
void fn_sub_466640_00466640(p3fes::EEContext&);
void fn_sub_48A2A0_0048a2a0(p3fes::EEContext&);
void fn_sub_48A2C0_0048a2c0(p3fes::EEContext&);
void fn_sub_48A3F0_0048a3f0(p3fes::EEContext&);
void fn_sub_48A480_0048a480(p3fes::EEContext&);
void fn_sub_4933D0_004933d0(p3fes::EEContext&);
void fn_sub_4C2CC0_004c2cc0(p3fes::EEContext&);
void fn_sub_4C2D20_004c2d20(p3fes::EEContext&);
void fn_sub_4C2F10_004c2f10(p3fes::EEContext&);
void fn_sub_4C2FB0_004c2fb0(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C35D0_004c35d0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4C9DF0_004c9df0(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4D1110_004d1110(p3fes::EEContext&);
void fn_sub_4D1170_004d1170(p3fes::EEContext&);
void fn_sub_4D11F0_004d11f0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace f7::draw;

// 0x001A13B0 sub_1A13B0 -- 268 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A13B0(texture, list) [K_TexFilterCollect]: a texture-dictionary callback (7 data references): prints
// "%s filter mode = %x" (name +16, filter byte +80); a texture whose name the global dictionary (sub_4D11F0) does not
// find yet (sub_4D1170) is added to it (sub_4D1110), and a 68-byte record holding the name (RW calloc, strcpy) is
// appended to the list at *list (next at +64). Returns the texture (the callback goes on).
void sub_1A13B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a13b0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s2 = a1;
    lbu(a2, a0, 80);
    a0 = 0x680000;
    a0 = addiu(a0, -30000);  // "%s filter mode = %x\n"
    a1 = addiu(s0, 16);
    jal(ctx, 0x1A13DCu, gen::fn_printf_005225a8);
    jal(ctx, 0x1A13E4u, gen::fn_sub_4D11F0_004d11f0);
    a0 = v0;
    a1 = addiu(s0, 16);
    jal(ctx, 0x1A13F4u, gen::fn_sub_4D1170_004d1170);
    if (v0 == 0) {
        // 0x001a1410
        charge(ctx, 21);
        jal(ctx, 0x1A1410u, gen::fn_sub_4D11F0_004d11f0);
        a0 = v0;
        a1 = s0;
        jal(ctx, 0x1A1420u, gen::fn_sub_4D1110_004d1110);
        a0 = 1;
        a1 = 68;
        a2 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 388);  // 0x960184
        jalr(ctx, 0x1A143Cu, v0.u());
        s1 = v0;
        a0 = s1;
        a1 = addiu(s0, 16);
        jal(ctx, 0x1A1450u, gen::fn_strcpy_00524270);
        lw(v0, s2, 0);
        if (v0 != 0) {
            // 0x001a1470
            charge(ctx, 3);
            v1 = addiu(v0, 64);
            for (;;) {
                // 0x001a1480
                charge(ctx, 6);
                lw(v0, v1, 0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001a147c
                charge(ctx, 1);
                v1 = addiu(v0, 64);
            }
            // 0x001a1498
            charge(ctx, 1);
            sw(s1, v1, 0);
        } else {
            // 0x001a1464
            charge(ctx, 3);
            sw(s1, s2, 0);
        }
        // 0x001a149c
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x001a1404
        charge(ctx, 3);
        v0 = s0;
    }
    // 0x001a14a0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001A1540 sub_1A1540 -- 12 bytes; leaf frame (no stack)
// sub_1A1540() [K_ReturnZero]: returns 0 (a stub the field 0x1E band calls).
void sub_1A1540(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x001a1540
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x001A4DF0 sub_1A4DF0 -- 88 bytes; frame 0x10
// sub_1A4DF0(out, task) [K_FldObj_GetPos]: copies the object's position (work +48..+56) to out (a 12-byte zeroed
// frame copy is made on the stack first and not used: retail's struct init).
void sub_1A4DF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001a4df0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    lw(a2, a1, 60);
    a1 = addiu(sp, 0x0);
    v1 = 12;
    if (a1 != 0) {
        for (;;) {
            // 0x001a4e08
            charge(ctx, 7);
            sb(zero, a1, 0);
            a1 = addiu(a1, 1);
            v1 = addiu(v1, -1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x001a4e24 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lwc1(f2, a2, kFramePos + 0);
    lwc1(f1, a2, kFramePos + 4);
    lwc1(f0, a2, kFramePos + 8);
    swc1(f2, a0, 0);
    swc1(f1, a0, 4);
    swc1(f0, a0, 8);
    sp = addiu(sp, 0x10);
}

// 0x001A4E50 sub_1A4E50 -- 12 bytes; leaf frame (no stack)
// sub_1A4E50(task) [K_Task_GetWork]: task +60.
void sub_1A4E50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001a4e50
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, kTaskWork);
}

// 0x001A4ED0 sub_1A4ED0 -- 108 bytes; frame 0x20: ra sp+0x0
// sub_1A4ED0(task, vec, scale) [K_FldObj_TranslateScaled]: translates the work's frame (task +60) by vec * $f12
// (RwFrameTranslate sub_4C35D0, combine 2 = post-concat).
void sub_1A4ED0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x001a4ed0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    lw(a0, a0, kTaskWork);
    v0 = addiu(sp, 0x10);
    lwc1(f2, a1, 0);
    lwc1(f1, a1, 4);
    lwc1(f0, a1, 8);
    swc1(f2, sp, 0x10);
    swc1(f1, sp, 0x14);
    swc1(f0, sp, 0x18);
    lwc1(f0, sp, 0x10);
    mul_s(f0, f0, f12);
    swc1(f0, sp, 0x10);
    lwc1(f0, sp, 0x14);
    mul_s(f0, f0, f12);
    swc1(f0, sp, 0x14);
    lwc1(f0, sp, 0x18);
    mul_s(f0, f0, f12);
    swc1(f0, sp, 0x18);
    a1 = v0;
    a2 = 2;
    jal(ctx, 0x1A4F24u, gen::fn_sub_4C35D0_004c35d0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001A4F40 sub_1A4F40 -- 192 bytes; frame 0x60: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_1A4F40(task, axis, angle) [K_FldObj_RotateInPlace]: rotates the frame (task +60) about `axis` by $f12 degrees
// around its own position: translate by -position (+48..+56 of the frame, times -1.0), RwFrameRotate (sub_4C31B0,
// combine 2 = post-concat), translate back.
void sub_1A4F40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x001a4f40
    enter(ctx, 48);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a1;
    mov_s(f20, f12);
    lw(s0, a0, kTaskWork);
    lwc1(f2, s0, kFramePos + 0);
    lwc1(f1, s0, kFramePos + 4);
    lwc1(f0, s0, kFramePos + 8);
    swc1(f2, sp, 0x50);
    swc1(f1, sp, 0x54);
    swc1(f0, sp, 0x58);
    v0 = lui(0xBF80);
    mtc1(v0, f1);
    lwc1(f0, sp, 0x50);
    mul_s(f0, f1, f0);
    swc1(f0, sp, 0x40);
    lwc1(f0, sp, 0x54);
    mul_s(f0, f1, f0);
    swc1(f0, sp, 0x44);
    lwc1(f0, sp, 0x58);
    mul_s(f0, f1, f0);
    swc1(f0, sp, 0x48);
    a0 = s0;
    a1 = addiu(sp, 0x40);
    a2 = 2;
    jal(ctx, 0x1A4FB0u, gen::fn_sub_4C35D0_004c35d0);
    a0 = s0;
    a1 = s1;
    mov_s(f12, f20);
    a2 = 2;
    jal(ctx, 0x1A4FC8u, gen::fn_sub_4C31B0_004c31b0);
    a0 = s0;
    a1 = addiu(sp, 0x50);
    a2 = 2;
    jal(ctx, 0x1A4FDCu, gen::fn_sub_4C35D0_004c35d0);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001A5000 sub_1A5000 -- 232 bytes; frame 0x60: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1A5000(task) [K_FldObj_SnapToGround]: casts a ray from the frame's position (+48..+56) down 800 units
// (sub_1ACC30, the collision ray query); on a hit moves the frame to the hit point + 3 in y and rebuilds it (identity
// matrix sub_4C2CC0, sub_4C2D20 copy, sub_4C2F10 orthonormalise). Returns the query's result.
void sub_1A5000(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001a5000
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, kTaskWork);
    lwc1(f2, v0, kFramePos + 0);
    lwc1(f1, v0, kFramePos + 4);
    lwc1(f0, v0, kFramePos + 8);
    swc1(f2, sp, 0x2C);
    swc1(f1, sp, 0x30);
    swc1(f0, sp, 0x34);
    a0 = addiu(sp, 0x20);
    lwc1(f2, sp, 0x2C);
    lwc1(f1, sp, 0x30);
    lwc1(f0, sp, 0x34);
    swc1(f2, sp, 0x20);
    swc1(f1, sp, 0x24);
    swc1(f0, sp, 0x28);
    lwc1(f1, sp, 0x30);
    v0 = 0x44480000;
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x30);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x1A5064u, gen::fn_sub_1ACC30_001acc30);
    v1 = 1;
    if (v0 == v1) {
        // 0x001a5078
        charge(ctx, 23);
        lwc1(f1, sp, 0x54);
        v0 = 0x40400000;
        mtc1(v0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0x54);
        lw(s0, s0, 60);
        lwc1(f2, sp, 0x50);
        lwc1(f1, sp, 0x54);
        lwc1(f0, sp, 0x58);
        swc1(f2, s0, kFramePos + 0);
        swc1(f1, s0, kFramePos + 4);
        swc1(f0, s0, kFramePos + 8);
        a0 = addiu(sp, 0x40);
        jal(ctx, 0x1A50B0u, gen::fn_sub_4C2CC0_004c2cc0);
        a0 = s0;
        a1 = addiu(sp, 0x40);
        jal(ctx, 0x1A50C0u, gen::fn_sub_4C2D20_004c2d20);
        a0 = s0;
        jal(ctx, 0x1A50CCu, gen::fn_sub_4C2F10_004c2f10);
    }
    // 0x001a50d4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001A56B0 sub_1A56B0 -- 16 bytes; leaf frame (no stack)
// sub_1A56B0(task, value) [K_CircleDraw_SetWord0]: work +0 (the "circle draw" task of Y_Kyoto_CreateKyotoNpcThinkTask).
void sub_1A56B0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001a56b0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, kTaskWork);
    sw(a1, v1, 0);
}

// 0x001A56C0 sub_1A56C0 -- 16 bytes; leaf frame (no stack)
// sub_1A56C0(task, value) [K_CircleDraw_SetWord4]: work +4.
void sub_1A56C0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001a56c0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, kTaskWork);
    sw(a1, v1, 4);
}

// 0x001A56D0 sub_1A56D0 -- 40 bytes; leaf frame (no stack)
// sub_1A56D0(task, pos) [K_CircleDraw_SetCentre]: copies the vec3 at pos to the circle's record (work +8 -> +8..+16).
void sub_1A56D0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001a56d0
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(v1, a0, kTaskWork);
    lw(v1, v1, kCircleRecord);
    lwc1(f2, a1, 0);
    lwc1(f1, a1, 4);
    lwc1(f0, a1, 8);
    swc1(f2, v1, kCircleCentre + 0);
    swc1(f1, v1, kCircleCentre + 4);
    swc1(f0, v1, kCircleCentre + 8);
}

// 0x001A5700 sub_1A5700 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A5700(task, rgba) [K_CircleDraw_SetColour]: writes the colour into all 34 prelit vertex colours of the circle's
// geometry (record +20 -> atomic, +24 geometry, +48 colours) between geometryLock(geom, 4095) and sub_4933D0.
void sub_1A5700(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a5700
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(v0, a0, kTaskWork);
    lw(v0, v0, kCircleRecord);
    lw(v0, v0, kCircleAtomic);
    lw(s0, v0, 24);
    a0 = s0;
    a1 = 4095;
    jal(ctx, 0x1A572Cu, gen::fn_geometryLock_00493370);
    lw(a3, s0, 48);
    t0 = 0;
    for (;;) {
        // 0x001a5770
        charge(ctx, 3);
        v0 = slti(t0, kCircleVertices);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001a5744
        charge(ctx, 11);
        v0 = sll(t0, 2);
        a2 = addu(a3, v0);
        lbu(a1, s1, 0);
        lbu(a0, s1, 1);
        lbu(v1, s1, 2);
        lbu(v0, s1, 3);
        sb(a1, a2, 0);
        sb(a0, a2, 1);
        sb(v1, a2, 2);
        sb(v0, a2, 3);
        t0 = addiu(t0, 1);
    }
    // 0x001a577c
    charge(ctx, 9);
    a0 = s0;
    jal(ctx, 0x1A5780u, gen::fn_sub_4933D0_004933d0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001A57A0 sub_1A57A0 -- 760 bytes; frame 0x80: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// sub_1A57A0(task, angle, radius) [K_CircleDraw_SetArc]: stores the arc angle ($f12, clamped to 0..360) and radius
// ($f13) in the record, then rebuilds the fan: vertex 0 = the centre, vertices 1..32 = rim points at
// (cos t * radius + x, y, sin t * radius + z) (R5900 adda / madd: the fused product-sum is kept), t stepping by
// full * fraction / 32 from full * (0.5 - fraction) / 2 -- full = the turn at 0x7CAEE8, fraction = angle / 360, so the
// arc is centred --, and vertex 33 closes it: the rim point at the start angle again (= vertex 1) when the angle is
// exactly 360, else a copy of vertex 32.
void sub_1A57A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x001a57a0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s1, a0, kTaskWork);
    lw(v0, s1, kCircleRecord);
    swc1(f13, v0, kCircleRadius);
    lw(v0, s1, kCircleRecord);
    swc1(f12, v0, kCircleAngle);
    lw(v0, s1, 8);
    lwc1(f1, v0, 0);
    mtc1(zero, f0);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        // 0x001a57fc
        charge(ctx, 1);
        swc1(f0, v0, 0);
    }
    // 0x001a5800
    charge(ctx, 8);
    lw(v1, s1, 8);
    lwc1(f1, v1, 0);
    v0 = 0x43B40000;
    mtc1(v0, f0);
    c_le_s(f1, f0);
    if (!cond(ctx)) {
        // 0x001a5820
        charge(ctx, 1);
        swc1(f0, v1, 0);
    }
    // 0x001a5824
    charge(ctx, 11);
    lw(v1, s1, 8);
    v0 = 0x43B40000;
    mtc1(v0, f1);
    lwc1(f0, v1, 0);
    div_s(f22, f0, f1);
    v0 = 0x3F000000;
    mtc1(v0, f0);
    c_le_s(f22, f0);
    if (!cond(ctx)) {
        // 0x001a5880
        charge(ctx, 8);
        lwc1(f20, gp, -32264);  // 0x7CAEE8
        sub_s(f1, f22, f0);
        v0 = 0x40000000;
        mtc1(v0, f0);
        div_s(f0, f1, f0);
        neg_s(f0, f0);
        mul_s(f21, f20, f0);
    } else {
        // 0x001a5850
        charge(ctx, 12);
        lwc1(f20, gp, -32264);  // 0x7CAEE8
        sub_s(f0, f0, f22);
        mul_s(f1, f20, f0);
        v0 = 0x40000000;
        mtc1(v0, f0);
        div_s(f21, f1, f0);
    }
    // 0x001a58a0
    charge(ctx, 27);
    lw(v0, v1, kCircleAtomic);
    lw(s3, v0, 24);
    a0 = s3;
    a1 = 4095;
    jal(ctx, 0x1A58B0u, gen::fn_geometryLock_00493370);
    lw(v0, s3, 92);
    lw(s0, v0, 20);
    lw(v0, s1, 8);
    lwc1(f0, v0, 8);
    swc1(f0, s0, 0);
    lw(v0, s1, 8);
    lwc1(f0, v0, 12);
    swc1(f0, s0, 4);
    lw(v0, s1, 8);
    lwc1(f0, v0, 16);
    swc1(f0, s0, 8);
    mul_s(f1, f20, f22);
    v0 = 0x42000000;
    mtc1(v0, f0);
    div_s(f20, f1, f0);
    s2 = 0;
    mov_s(f22, f21);
    for (;;) {
        // 0x001a5988
        charge(ctx, 3);
        v0 = slti(s2, 32);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001a590c
        charge(ctx, 31);
        lw(s5, s1, 8);
        v0 = sll(s2, 1);
        v0 = addu(v0, s2);
        v0 = sll(v0, 2);
        s4 = addu(s0, v0);
        mov_s(f12, f22);
        jal(ctx, 0x1A5924u, gen::fn_cosf_0052e6d8);
        lwc1(f3, s5, 4);
        lwc1(f2, s5, 8);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        swc1(f0, s4, 12);
        lw(v0, s1, 8);
        lwc1(f0, v0, 12);
        swc1(f0, s4, 16);
        lw(s5, s1, 8);
        mov_s(f12, f22);
        jal(ctx, 0x1A595Cu, gen::fn_sinf_0052e878);
        lwc1(f3, s5, 4);
        lwc1(f2, s5, 16);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        swc1(f0, s4, 20);
        add_s(f22, f22, f20);
        s2 = addiu(s2, 1);
    }
    // 0x001a5994
    charge(ctx, 8);
    lw(s4, s1, 8);
    lwc1(f1, s4, 0);
    v0 = 0x43B40000;
    mtc1(v0, f0);
    c_eq_s(f0, f1);
    if (!cond(ctx)) {
        // 0x001a5a30
        charge(ctx, 10);
        v0 = sll(s2, 1);
        v0 = addu(v0, s2);
        v0 = sll(v0, 2);
        v0 = addu(s0, v0);
        lwc1(f0, v0, 0);
        swc1(f0, v0, 12);
        lwc1(f0, v0, 4);
        swc1(f0, v0, 16);
        lwc1(f0, v0, 8);
        swc1(f0, v0, 20);
    } else {
        // 0x001a59b4
        charge(ctx, 31);
        v0 = sll(s2, 1);
        v0 = addu(v0, s2);
        s2 = sll(v0, 2);
        mov_s(f12, f21);
        jal(ctx, 0x1A59C4u, gen::fn_cosf_0052e6d8);
        lwc1(f3, s4, 4);
        lwc1(f2, s4, 8);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        v1 = addu(s2, s0);
        swc1(f0, v1, 12);
        lw(v0, s1, 8);
        lwc1(f0, v0, 12);
        swc1(f0, v1, 16);
        lw(s1, s1, 8);
        mov_s(f12, f21);
        jal(ctx, 0x1A5A00u, gen::fn_sinf_0052e878);
        lwc1(f3, s1, 4);
        lwc1(f2, s1, 16);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        v0 = addu(s2, s0);
        swc1(f0, v0, 20);
    }
    // 0x001a5a58
    charge(ctx, 16);
    a0 = s3;
    jal(ctx, 0x1A5A5Cu, gen::fn_sub_4933D0_004933d0);
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x001A5AA0 sub_1A5AA0 -- 132 bytes; frame 0x50: ra sp+0x0
// sub_1A5AA0(matrix) [K_Mtx_GetYawDeg]: copies the 64-byte RwMatrix to the stack, orthonormalises the copy
// (sub_4C2FB0) and returns -atan2f(right.z, right.x) * 180 / pi in $f0 (pi from 0x7CAE58): the turn about y.
void sub_1A5AA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13};
    // 0x001a5aa0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x0);
    a2 = addiu(sp, 0x10);
    a1 = 8;
    for (;;) {
        // 0x001a5ab0
        charge(ctx, 9);
        lw(v1, a0, 0);
        lw(v0, a0, 4);
        a0 = addiu(a0, 8);
        a1 = addiu(a1, -1);
        sw(v1, a2, 0);
        sw(v0, a2, 4);
        a2 = addiu(a2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x001a5ad4
    charge(ctx, 20);
    a0 = addiu(sp, 0x10);
    a1 = a0;
    jal(ctx, 0x1A5ADCu, gen::fn_sub_4C2FB0_004c2fb0);
    lwc1(f12, sp, 0x18);
    lwc1(f13, sp, 0x10);
    jal(ctx, 0x1A5AECu, gen::fn_atan2f_0052ea18);
    neg_s(f1, f0);
    v0 = 0x43340000;
    mtc1(v0, f0);
    mul_s(f1, f0, f1);
    lwc1(f0, gp, -32408);  // 0x7CAE58
    div_s(f0, f1, f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001A5B30 sub_1A5B30 -- 136 bytes; frame 0x50: ra sp+0x0
// sub_1A5B30(matrix) [K_Mtx_GetPitchDeg]: as sub_1A5AA0 with -atan2f(up.z, up.y): the tilt about x.
void sub_1A5B30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13};
    // 0x001a5b30
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x0);
    a2 = addiu(sp, 0x10);
    a1 = 8;
    for (;;) {
        // 0x001a5b40
        charge(ctx, 9);
        lw(v1, a0, 0);
        lw(v0, a0, 4);
        a0 = addiu(a0, 8);
        a1 = addiu(a1, -1);
        sw(v1, a2, 0);
        sw(v0, a2, 4);
        a2 = addiu(a2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x001a5b64
    charge(ctx, 21);
    a0 = addiu(sp, 0x10);
    a1 = a0;
    jal(ctx, 0x1A5B6Cu, gen::fn_sub_4C2FB0_004c2fb0);
    v0 = addiu(sp, 0x20);
    lwc1(f12, v0, 8);
    lwc1(f13, v0, 4);
    jal(ctx, 0x1A5B80u, gen::fn_atan2f_0052ea18);
    neg_s(f1, f0);
    v0 = 0x43340000;
    mtc1(v0, f0);
    mul_s(f1, f0, f1);
    lwc1(f0, gp, -32408);  // 0x7CAE58
    div_s(f0, f1, f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001A5BC0 sub_1A5BC0 -- 132 bytes; frame 0x50: ra sp+0x0
// sub_1A5BC0(matrix) [K_Mtx_GetRollDeg]: as sub_1A5AA0 with atan2f(up.x, up.y) (not negated): the tilt about z.
void sub_1A5BC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13};
    // 0x001a5bc0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x0);
    a2 = addiu(sp, 0x10);
    a1 = 8;
    for (;;) {
        // 0x001a5bd0
        charge(ctx, 9);
        lw(v1, a0, 0);
        lw(v0, a0, 4);
        a0 = addiu(a0, 8);
        a1 = addiu(a1, -1);
        sw(v1, a2, 0);
        sw(v0, a2, 4);
        a2 = addiu(a2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x001a5bf4
    charge(ctx, 20);
    a0 = addiu(sp, 0x10);
    a1 = a0;
    jal(ctx, 0x1A5BFCu, gen::fn_sub_4C2FB0_004c2fb0);
    v0 = addiu(sp, 0x20);
    lwc1(f12, v0, 0);
    lwc1(f13, v0, 4);
    jal(ctx, 0x1A5C10u, gen::fn_atan2f_0052ea18);
    v0 = 0x43340000;
    mtc1(v0, f1);
    mul_s(f1, f1, f0);
    lwc1(f0, gp, -32408);  // 0x7CAE58
    div_s(f0, f1, f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001A5E70 sub_1A5E70 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1A5E70(task) [destroy]: frees the work (RW free slot 0x96017C).
void sub_1A5E70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a5e70
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1A5E84u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A5F30 sub_1A5F30 -- 360 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1A5F30(task) [K_MdlFade_Update]: a model alpha fade: with frames left (+16 > 0) the alpha (+12) moves 1 / frames
// of the way to the target (+8), the colour from 0x7CC1DC with that alpha (float to byte with the 2^31 fix-up) is
// set on the model (+4, mdlSetColor sub_318AD0) and the counter drops -- returns 0; at 0 frames the target alpha is
// set and it returns -1 (task done). sinf(frames * 0x7CAF38 / 30) is evaluated first and its result is unused.
void sub_1A5F30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x001a5f30
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, kTaskWork);
    lwc1(f0, s0, kFadeFrames);
    cvt_s_w(f1, f0);
    lwc1(f0, gp, -32184);  // 0x7CAF38
    mul_s(f1, f0, f1);
    v0 = 0x41F00000;
    mtc1(v0, f0);
    div_s(f12, f1, f0);
    jal(ctx, 0x1A5F6Cu, gen::fn_sinf_0052e878);
    lwc1(f0, gp, -27412);  // 0x7CC1DC
    swc1(f0, sp, 0x2C);
    lw(v0, s0, kFadeFrames);
    if (i64(v0) > 0) {
        // 0x001a5ff4
        charge(ctx, 15);
        lwc1(f0, s0, kFadeTarget);
        lwc1(f2, s0, kFadeAlpha);
        sub_s(f1, f0, f2);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        div_s(f0, f1, f0);
        add_s(f1, f2, f0);
        swc1(f1, s0, kFadeAlpha);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x001a6048
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x001a6030
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x001a6060
        charge(ctx, 9);
        sb(v1, sp, 0x2F);
        lw(a0, s0, kFadeModel);
        a1 = addiu(sp, 0x2C);
        jal(ctx, 0x1A606Cu, gen::fn_sub_318AD0_00318ad0);
        lw(v0, s0, kFadeFrames);
        v0 = addiu(v0, -1);
        sw(v0, s0, kFadeFrames);
        v0 = 0;
    } else {
        // 0x001a5f88
        charge(ctx, 7);
        lwc1(f1, s0, kFadeTarget);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x001a5fbc
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x001a5fa4
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x001a5fd4
        charge(ctx, 8);
        sb(v1, sp, 0x2F);
        lw(a0, s0, kFadeModel);
        a1 = addiu(sp, 0x2C);
        jal(ctx, 0x1A5FE0u, gen::fn_sub_318AD0_00318ad0);
        v0 = si(-1);
    }
    // 0x001a6084 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001A60A0 sub_1A60A0 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1A60A0(task) [destroy]: frees the work (RW free slot 0x96017C).
void sub_1A60A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a60a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1A60B4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A6260 sub_1A6260 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1A6260(task) [K_Task_KillTarget]: destroys the task tree whose task is work +0 (kwlnTaskDestroyWithHierarchy)
// and returns -1 (this task ends too).
void sub_1A6260(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a6260
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, kTaskWork);
    lw(a0, v0, 0);
    jal(ctx, 0x1A6270u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    v0 = si(-1);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A6290 sub_1A6290 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1A6290(task) [destroy]: frees the work (RW free slot 0x96017C).
void sub_1A6290(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a6290
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1A62A4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A7030 sub_1A7030 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1A7030(task) [K_CpuDraw_Kill]: destroys every "cpu draw" task tree (kwlnTaskDestroyWithHierarchyByName) and
// returns -1.
void sub_1A7030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a7030
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x680000;
    a0 = addiu(a0, -29736);  // "cpu draw"
    jal(ctx, 0x1A7040u, gen::fn_kwlnTaskDestroyWithHierarchyByName_00194fe0);
    v0 = si(-1);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A70A0 sub_1A70A0 -- 204 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A70A0(atomic, data) [K_Clump_AtomicCallback]: an RpClumpForAllAtomics callback: when the atomic's geometry
// (+24) passes sub_48A2C0, a pipeline other than 0 / 1 / 3 (sub_48A480) is reset (sub_48A3F0) and the atomic is set up
// with `data` (sub_48A2A0); otherwise sub_466640(data). Returns the atomic.
void sub_1A70A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a70a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(a0, a0, 24);
    jal(ctx, 0x1A70BCu, gen::fn_sub_48A2C0_0048a2c0);
    if (v0 == 0) {
        // 0x001a7144
        charge(ctx, 3);
        a0 = s0;
        jal(ctx, 0x1A7148u, gen::fn_sub_466640_00466640);
    } else {
        // 0x001a70cc
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x1A70D0u, gen::fn_sub_48A480_0048a480);
        if (v0 != 0) {
            // 0x001a70e0
            charge(ctx, 3);
            v1 = 3;
            if (v0 != v1) {
                // 0x001a70ec
                charge(ctx, 3);
                a1 = 2;
                if (v0 == a1) {
                    // 0x001a710c
                    charge(ctx, 5);
                    a0 = s1;
                    jal(ctx, 0x1A7110u, gen::fn_sub_48A3F0_0048a3f0);
                } else {
                    // 0x001a70f8
                    charge(ctx, 3);
                    v1 = 1;
                    if (v0 != v1) {
                        // 0x001a7104
                        charge(ctx, 2);
                        // 0x001a7120
                        charge(ctx, 3);
                        a0 = s1;
                        jal(ctx, 0x1A7124u, gen::fn_sub_48A3F0_0048a3f0);
                    }
                }
            }
        }
        // 0x001a712c
        charge(ctx, 6);
        a0 = s1;
        a1 = s0;
        jal(ctx, 0x1A7134u, gen::fn_sub_48A2A0_0048a2a0);
    }
    // 0x001a7150 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001A71A0 sub_1A71A0 -- 464 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A71A0(lists, kind, value, flagged, arg) [K_Clump_AddDrawNode]: allocates a 44-byte node (RW calloc; not
// checked): +0 value, +4 = 1 and lists[1]++ when flagged == 1, +8 arg, four 1.0f (+12..+24), +28 the list number,
// pushed on the head of the list for `kind` (0 and 1 -> lists[2], 2 -> [5], 3 -> [9], 4 -> [10], 5 -> [3], 6 -> [4],
// 7 -> [6], 8 -> [7], 9 -> [8]; next at +40; any other kind is not linked); lists[0]++. Returns the node.
void sub_1A71A0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a71a0
    enter(ctx, 23);  // entry check point + this block's cycles
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
    s0 = t0;
    a0 = 1;
    a1 = kDrawNodeSize;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1A71E4u, v0.u());
    sw(s2, v0, 0);
    a0 = 1;
    if (s1 == a0) {
        // 0x001a71fc
        charge(ctx, 4);
        lw(v1, s4, kListsFlagged);
        v1 = addiu(v1, 1);
        sw(v1, s4, kListsFlagged);
        sw(a0, v0, 4);
    }
    // 0x001a720c
    charge(ctx, 9);
    sw(s0, v0, 8);
    v1 = 0x3F800000;
    sw(v1, v0, 12);
    sw(v1, v0, 16);
    sw(v1, v0, 20);
    sw(v1, v0, 24);
    at = sltiu(s3, 10);
    if (at != 0) {
        // 0x001a7230
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 27296);  // &0x7B6AA0
        v1 = sll(s3, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x1A724Cu:  // table[0, 1]
            // 0x001a724c
            charge(ctx, 7);
            v1 = 1;
            sw(v1, v0, 28);
            lw(v1, s4, 8);
            sw(v1, v0, kDrawNodeNext);
            sw(v0, s4, 8);
            break;
        case 0x1A7268u:  // table[2]
            // 0x001a7268
            charge(ctx, 7);
            v1 = 2;
            sw(v1, v0, 28);
            lw(v1, s4, 20);
            sw(v1, v0, kDrawNodeNext);
            sw(v0, s4, 20);
            break;
        case 0x1A7284u:  // table[3]
            // 0x001a7284
            charge(ctx, 7);
            v1 = 3;
            sw(v1, v0, 28);
            lw(v1, s4, 36);
            sw(v1, v0, kDrawNodeNext);
            sw(v0, s4, 36);
            break;
        case 0x1A72A0u:  // table[4]
            // 0x001a72a0
            charge(ctx, 7);
            v1 = 4;
            sw(v1, v0, 28);
            lw(v1, s4, 40);
            sw(v1, v0, kDrawNodeNext);
            sw(v0, s4, 40);
            break;
        case 0x1A72BCu:  // table[5]
            // 0x001a72bc
            charge(ctx, 7);
            v1 = 5;
            sw(v1, v0, 28);
            lw(v1, s4, 12);
            sw(v1, v0, kDrawNodeNext);
            sw(v0, s4, 12);
            break;
        case 0x1A72D8u:  // table[6]
            // 0x001a72d8
            charge(ctx, 7);
            v1 = 6;
            sw(v1, v0, 28);
            lw(v1, s4, 16);
            sw(v1, v0, kDrawNodeNext);
            sw(v0, s4, 16);
            break;
        case 0x1A72F4u:  // table[7]
            // 0x001a72f4
            charge(ctx, 7);
            v1 = 7;
            sw(v1, v0, 28);
            lw(v1, s4, 24);
            sw(v1, v0, kDrawNodeNext);
            sw(v0, s4, 24);
            break;
        case 0x1A7310u:  // table[8]
            // 0x001a7310
            charge(ctx, 7);
            v1 = 8;
            sw(v1, v0, 28);
            lw(v1, s4, 28);
            sw(v1, v0, kDrawNodeNext);
            sw(v0, s4, 28);
            break;
        case 0x1A732Cu:  // table[9]
            // 0x001a732c
            charge(ctx, 5);
            v1 = 9;
            sw(v1, v0, 28);
            lw(v1, s4, 32);
            sw(v1, v0, kDrawNodeNext);
            sw(v0, s4, 32);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x001a7340 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    lw(v1, s4, kListsNodes);
    v1 = addiu(v1, 1);
    sw(v1, s4, kListsNodes);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001A74B0 sub_1A74B0 -- 36 bytes; leaf frame (no stack)
// sub_1A74B0(material, out) [K_MatFindOpaque]: a material callback: *out = 1 when the colour's alpha (+7) is 255.
// Returns the material.
void sub_1A74B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001a74b0
    enter(ctx, 4);  // entry check point + this block's cycles
    lbu(v1, a0, 7);
    v0 = 255;
    if (v1 == v0) {
        // 0x001a74c0
        charge(ctx, 2);
        v0 = 1;
        sw(v0, a1, 0);
    }
    // 0x001a74c8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = a0;
}

// 0x001A7660 sub_1A7660 -- 116 bytes; leaf frame (no stack)
// sub_1A7660(lists) [K_Clump_HasDrawNodes]: 1 when the lists exist, hold nodes (+0) and any of the lists +12, +16,
// +20, +36 or +40 is non-empty; else 0.
void sub_1A7660(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001a7660
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x001a7674
        charge(ctx, 3);
        lw(v0, a0, kListsNodes);
        bool any = false;  // a non-empty list (the original's shared block 0x1a76c8)
        if (v0 != 0) {
            // 0x001a7680: the lists +16, +12, +20, +36, +40 in this order, up to the first non-empty one
            charge(ctx, 3);
            lw(v0, a0, 16);
            any = v0 != 0;
            if (!any) {
                // 0x001a768c
                charge(ctx, 3);
                lw(v0, a0, 12);
                any = v0 != 0;
            }
            if (!any) {
                // 0x001a7698
                charge(ctx, 3);
                lw(v0, a0, 20);
                any = v0 != 0;
            }
            if (!any) {
                // 0x001a76a4
                charge(ctx, 3);
                lw(v0, a0, 36);
                any = v0 != 0;
            }
            if (!any) {
                // 0x001a76b0
                charge(ctx, 3);
                lw(v0, a0, 40);
                any = v0 != 0;
            }
        }
        if (any) {
            // 0x001a76c8
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x001a76bc
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001a7668
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a76cc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001A76E0 sub_1A76E0 -- 36 bytes; leaf frame (no stack)
// sub_1A76E0(lists) [K_Clump_HasList8]: 1 when the lists exist and list +32 is non-empty.
void sub_1A76E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001a76e0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x001a76f4
        charge(ctx, 2);
        lw(v0, a0, 32);
        v0 = sltu(0, v0);
    } else {
        // 0x001a76e8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a76fc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001A8820 sub_1A8820 -- 192 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1A8820(atomic) [K_Clump_DrawAtomicCulled]: for an atomic with the render flag (+2 bit 2) and a geometry (+24):
// when its world bounding sphere is inside the camera frustum (0x960070, sub_4C9DF0) it is rendered through its
// callback (+72), and with the debug flag (gp 0x7CE154 == 1) a wire sphere (colour 0x7CC208) is drawn around it.
// Returns the atomic.
void sub_1A8820(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x001a8820
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lbu(v0, a0, 2);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x001a884c
        charge(ctx, 3);
        lw(v0, s0, 24);
        if (v0 != 0) {
            // 0x001a8858
            charge(ctx, 9);
            jal(ctx, 0x1A8858u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
            v1 = 0x960000;
            lw(a0, v1, 112);  // 0x960070
            a1 = v0;
            jal(ctx, 0x1A886Cu, gen::fn_sub_4C9DF0_004c9df0);
            if (v0 != 0) {
                // 0x001a887c
                charge(ctx, 8);
                a0 = s0;
                lw(v0, s0, 72);
                jalr(ctx, 0x1A8884u, v0.u());
                lw(v1, gp, -19356);  // 0x7CE154
                v0 = 1;
                if (v1 == v0) {
                    // 0x001a889c
                    charge(ctx, 11);
                    lwc1(f0, gp, -27368);  // 0x7CC208
                    swc1(f0, sp, 0x2C);
                    a0 = s0;
                    jal(ctx, 0x1A88A8u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
                    a0 = v0;
                    lwc1(f12, v0, 12);
                    a1 = addiu(sp, 0x2C);
                    a2 = 0;
                    jal(ctx, 0x1A88C0u, gen::fn_sub_359B40_00359b40);
                }
            }
        }
        // 0x001a88c8
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x001a8840
        charge(ctx, 3);
        v0 = s0;
    }
    // 0x001a88cc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001A8910 sub_1A8910 -- 12 bytes; leaf frame (no stack)
// sub_1A8910(out) [K_ShadowCam_Clear]: *out = 0 (kwlnRootUpdateShadowNodeCameraTask).
void sub_1A8910(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x001a8910
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(zero, a0, 0);
}

// 0x001A8920 sub_1A8920 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A8920(queue, node) [K_Clump_QueueTranslucent]: appends the 44-byte node to the translucent queue (count +0,
// nodes from +4; k_clump.c 1003 asserts a count below 128, K_Assert returns in retail).
void sub_1A8920(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a8920
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, a0, 0);
    v1 = slti(v1, kQueueMax);
    if (v1 == 0) {
        // 0x001a8948
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, -29576);  // "k_clump.c"
        a1 = 1003;
        jal(ctx, 0x1A8954u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001a895c
    charge(ctx, 9);
    lw(a0, s1, 0);
    v1 = sll(a0, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, s1);
    a1 = addiu(v1, kQueueNodes);
    a0 = 11;
    for (;;) {
        // 0x001a8980
        charge(ctx, 7);
        lw(v1, s0, 0);
        s0 = addiu(s0, 4);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        a1 = addiu(a1, 4);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x001a899c
    charge(ctx, 9);
    lw(v1, s1, 0);
    v1 = addiu(v1, 1);
    sw(v1, s1, 0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001A89C0 sub_1A89C0 -- 332 bytes; frame 0x70: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// sub_1A89C0(a, b) [K_Clump_CompareDepth]: the translucent queue's qsort comparator: (int)(|A - cam| - |B - cam|) with
// the camera position from the main camera's frame (sub_198590 -> +4, sub_4CB2F0 LTM +48..+56) and each node's
// clump frame position; vector lengths by sub_4C6AC0. Far first is the caller's order.
void sub_1A89C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20}, f21{ctx, 21};
    // 0x001a89c0
    enter(ctx, 83);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    s0 = a1;
    jal(ctx, 0x1A89E0u, gen::fn_sub_198590_00198590);
    lw(a0, v0, 4);
    jal(ctx, 0x1A89ECu, gen::fn_sub_4CB2F0_004cb2f0);
    lwc1(f2, v0, 48);
    lwc1(f1, v0, 52);
    lwc1(f0, v0, 56);
    swc1(f2, sp, 0x40);
    swc1(f1, sp, 0x44);
    swc1(f0, sp, 0x48);
    lw(v0, s1, 0);
    lw(a0, v0, 4);
    jal(ctx, 0x1A8A14u, gen::fn_sub_4CB2F0_004cb2f0);
    lwc1(f1, v0, 48);
    lwc1(f0, sp, 0x40);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x60);
    lwc1(f21, sp, 0x44);
    lw(v0, s1, 0);
    lw(a0, v0, 4);
    jal(ctx, 0x1A8A38u, gen::fn_sub_4CB2F0_004cb2f0);
    lwc1(f0, v0, 52);
    sub_s(f0, f0, f21);
    swc1(f0, sp, 0x64);
    lwc1(f20, sp, 0x48);
    lw(v0, s1, 0);
    lw(a0, v0, 4);
    jal(ctx, 0x1A8A58u, gen::fn_sub_4CB2F0_004cb2f0);
    lwc1(f0, v0, 56);
    sub_s(f0, f0, f20);
    swc1(f0, sp, 0x68);
    lw(v0, s0, 0);
    lw(a0, v0, 4);
    jal(ctx, 0x1A8A74u, gen::fn_sub_4CB2F0_004cb2f0);
    lwc1(f1, v0, 48);
    lwc1(f0, sp, 0x40);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x50);
    lw(v0, s0, 0);
    lw(a0, v0, 4);
    jal(ctx, 0x1A8A94u, gen::fn_sub_4CB2F0_004cb2f0);
    lwc1(f0, v0, 52);
    sub_s(f0, f0, f21);
    swc1(f0, sp, 0x54);
    lw(v0, s0, 0);
    lw(a0, v0, 4);
    jal(ctx, 0x1A8AB0u, gen::fn_sub_4CB2F0_004cb2f0);
    lwc1(f0, v0, 56);
    sub_s(f0, f0, f20);
    swc1(f0, sp, 0x58);
    a0 = addiu(sp, 0x60);
    jal(ctx, 0x1A8AC8u, gen::fn_sub_4C6AC0_004c6ac0);
    mov_s(f20, f0);
    a0 = addiu(sp, 0x50);
    jal(ctx, 0x1A8AD8u, gen::fn_sub_4C6AC0_004c6ac0);
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

}  // namespace p3fes::game
