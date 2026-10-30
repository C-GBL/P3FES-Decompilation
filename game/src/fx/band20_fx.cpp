// Phase 5 slice band20 -- the effect system's node / record / instance helpers of 0x324310-0x32E110: mesh and
// effect-record destructors, the node tree's step / destroy / reset and its position / rotation / scale / colour
// propagation through the class table 0x69BE20 (fx_types.h), the class instance's part setters, the 2D particle draw,
// the VU0 maths helpers (camera space, screen projection, cubic, quaternion), the colour track and the
// particle-system scale slots.
// The bodies come from p3fes_handgen (register ABI: arguments in $a0.., the result in $v0) and keep every register,
// frame slot, $ra link, cycle charge and check point of the recompiled body (game/include/p3fes/game/hg_cpu.h); this
// file adds the names: one role comment per function ([proposed name] first), named offsets of the records in
// game/include/p3fes/game/band20.h (a constant replaces only a literal of its own value), the K_Assert(file, line)
// calls (`jr $ra` in retail: a failed check carries on), the RW slots the bodies call through, the float constants of
// the $gp area with their values, and `while` notes on the counted loops.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/band20.h"

namespace p3fes::recomp_gen {
void fn_acosf_0052e9e8(p3fes::EEContext&);
void fn_atan2f_0052ea18(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_3210A0_003210a0(p3fes::EEContext&);
void fn_sub_3210C0_003210c0(p3fes::EEContext&);
void fn_sub_322530_00322530(p3fes::EEContext&);
void fn_sub_322660_00322660(p3fes::EEContext&);
void fn_sub_322DC0_00322dc0(p3fes::EEContext&);
void fn_sub_322F20_00322f20(p3fes::EEContext&);
void fn_sub_322FD0_00322fd0(p3fes::EEContext&);
void fn_sub_3234F0_003234f0(p3fes::EEContext&);
void fn_sub_3237C0_003237c0(p3fes::EEContext&);
void fn_sub_324310_00324310(p3fes::EEContext&);
void fn_sub_3243F0_003243f0(p3fes::EEContext&);
void fn_sub_324510_00324510(p3fes::EEContext&);
void fn_sub_324740_00324740(p3fes::EEContext&);
void fn_sub_3247D0_003247d0(p3fes::EEContext&);
void fn_sub_324820_00324820(p3fes::EEContext&);
void fn_sub_325500_00325500(p3fes::EEContext&);
void fn_sub_3257E0_003257e0(p3fes::EEContext&);
void fn_sub_325B80_00325b80(p3fes::EEContext&);
void fn_sub_325C10_00325c10(p3fes::EEContext&);
void fn_sub_325D60_00325d60(p3fes::EEContext&);
void fn_sub_325E40_00325e40(p3fes::EEContext&);
void fn_sub_326030_00326030(p3fes::EEContext&);
void fn_sub_326280_00326280(p3fes::EEContext&);
void fn_sub_3263B0_003263b0(p3fes::EEContext&);
void fn_sub_326740_00326740(p3fes::EEContext&);
void fn_sub_326C70_00326c70(p3fes::EEContext&);
void fn_sub_326CF0_00326cf0(p3fes::EEContext&);
void fn_sub_326DB0_00326db0(p3fes::EEContext&);
void fn_sub_326E50_00326e50(p3fes::EEContext&);
void fn_sub_326F00_00326f00(p3fes::EEContext&);
void fn_sub_3271C0_003271c0(p3fes::EEContext&);
void fn_sub_3282E0_003282e0(p3fes::EEContext&);
void fn_sub_329800_00329800(p3fes::EEContext&);
void fn_sub_3299B0_003299b0(p3fes::EEContext&);
void fn_sub_329D60_00329d60(p3fes::EEContext&);
void fn_sub_329ED0_00329ed0(p3fes::EEContext&);
void fn_sub_32A120_0032a120(p3fes::EEContext&);
void fn_sub_32B990_0032b990(p3fes::EEContext&);
void fn_sub_32C2B0_0032c2b0(p3fes::EEContext&);
void fn_sub_32CD70_0032cd70(p3fes::EEContext&);
void fn_sub_32D7C0_0032d7c0(p3fes::EEContext&);
void fn_sub_32E110_0032e110(p3fes::EEContext&);
void fn_sub_332070_00332070(p3fes::EEContext&);
void fn_sub_3321D0_003321d0(p3fes::EEContext&);
void fn_sub_3322B0_003322b0(p3fes::EEContext&);
void fn_sub_3322F0_003322f0(p3fes::EEContext&);
void fn_sub_357DD0_00357dd0(p3fes::EEContext&);
void fn_sub_357E30_00357e30(p3fes::EEContext&);
void fn_sub_357EA0_00357ea0(p3fes::EEContext&);
void fn_sub_491A80_00491a80(p3fes::EEContext&);
void fn_sub_494CC0_00494cc0(p3fes::EEContext&);
void fn_sub_494D50_00494d50(p3fes::EEContext&);
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);
void fn_sub_4CAF80_004caf80(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4D0F00_004d0f00(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b20;  // the named offsets and $gp slots of band20.h

// 0x00324310 sub_324310 -- 184 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fxMesh_Destroy](mesh) destroys an effect mesh: its frame (sub_491A80), atomic (sub_4CAF80), each material
// (sub_494CC0), then the block (the RwFree slot).
void sub_324310(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00324310
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, kFmFrame);
    if (a0 != 0) {
        // 0x00324330
        charge(ctx, 2);
        jal(ctx, 0x324330u, gen::fn_sub_491A80_00491a80);
    }
    // 0x00324338
    charge(ctx, 3);
    lw(a0, s1, kFmAtomic);
    if (a0 != 0) {
        // 0x00324344
        charge(ctx, 2);
        jal(ctx, 0x324344u, gen::fn_sub_4CAF80_004caf80);
    }
    // 0x0032434c
    charge(ctx, 3);
    lw(v0, s1, kFmMaterials);
    if (v0 != 0) {
        // 0x00324358
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x00324388
            charge(ctx, 5);
            v1 = s0 & 0xFFFF;
            lh(v0, s1, kFmMaterialCount);
            v0 = slt(v1, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00324364
            charge(ctx, 9);
            v0 = s0 & 0xFFFF;
            v1 = sll(v0, 2);
            lw(v0, s1, kFmMaterials);
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
            jal(ctx, 0x324378u, gen::fn_sub_494CC0_00494cc0);
            v0 = addiu(s0, 1);
            s0 = v0 & 0xFFFF;
        }
    }
    // 0x0032439c
    charge(ctx, 11);
    a0 = s1;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    jalr(ctx, 0x3243A8u, v0.u());
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003243F0 sub_3243F0 -- 128 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fxMesh_SetTexture](mesh, texture) sets the texture on each material.
void sub_3243F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003243f0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = 0;
    for (;;) {
        // 0x00324440
        charge(ctx, 5);
        a0 = s0 & 0xFFFF;
        lh(v1, s2, kFmMaterialCount);
        v1 = slt(a0, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00324418
        charge(ctx, 10);
        v0 = s0 & 0xFFFF;
        v1 = sll(v0, 2);
        lw(v0, s2, kFmMaterials);
        v0 = addu(v0, v1);
        lw(a0, v0, 0);
        a1 = s1;
        jal(ctx, 0x324430u, gen::fn_sub_494D50_00494d50);  // RpMaterialSetTexture-like: (material, texture)
        v1 = addiu(s0, 1);
        s0 = v1 & 0xFFFF;
    }
    // 0x00324454
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00324510 sub_324510 -- 152 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fxMesh_SetTextureByName](mesh, name) looks the texture up (sub_3210C0), sets it on each material and
// drops the lookup's reference (sub_4D0F00).
void sub_324510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00324510
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    a0 = a1;
    jal(ctx, 0x32452Cu, gen::fn_sub_3210C0_003210c0);  // [effLayer] texture by name
    s0 = v0;
    s1 = 0;
    for (;;) {
        // 0x0032456c
        charge(ctx, 5);
        v1 = s1 & 0xFFFF;
        lh(v0, s2, kFmMaterialCount);
        v0 = slt(v1, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00324544
        charge(ctx, 10);
        v0 = s1 & 0xFFFF;
        v1 = sll(v0, 2);
        lw(v0, s2, kFmMaterials);
        v0 = addu(v0, v1);
        lw(a0, v0, 0);
        a1 = s0;
        jal(ctx, 0x32455Cu, gen::fn_sub_494D50_00494d50);  // RpMaterialSetTexture-like: (material, texture)
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFFFF;
    }
    // 0x00324580
    charge(ctx, 10);
    a0 = s0;
    jal(ctx, 0x324584u, gen::fn_sub_4D0F00_004d0f00);  // RwTextureDestroy-like: drops the reference
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00324740 sub_324740 -- 140 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fxEffect_Destroy](rec) destroys an effect record: class slot 1 on its instance (when there is one), its two
// heap blocks (sub_3247D0 / sub_324820), the record.
void sub_324740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00324740
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, kErInstance);
    if (a0 != 0) {
        // 0x0032475c
        charge(ctx, 12);
        lhu(v1, s0, kErClass);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x6A0000;
        v0 = addiu(v0, -16848);  // "0F2"
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        jalr(ctx, 0x324784u, v0.u());
    }
    // 0x0032478c
    charge(ctx, 16);
    a0 = s0;
    jal(ctx, 0x324790u, gen::fn_sub_3247D0_003247d0);
    a0 = s0;
    jal(ctx, 0x32479Cu, gen::fn_sub_324820_00324820);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    jalr(ctx, 0x3247B0u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003247D0 sub_3247D0 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fxEffect_FreeBlockA](rec) frees block A's heap copy (+24) and clears +16 / +20 / +24.
void sub_3247D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003247d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, kErBlockAMem);
    if (a0 != 0) {
        // 0x003247ec
        charge(ctx, 7);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x3247F4u, v0.u());
        sw(zero, s0, kErBlockA);
        sw(zero, s0, kErBlockAEnd);
        sw(zero, s0, kErBlockAMem);
    }
    // 0x00324808 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00324820 sub_324820 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fxEffect_FreeBlockB](rec) frees block B's heap copy (+40) and clears +32 / +36 / +40.
void sub_324820(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00324820
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, kErBlockBMem);
    if (a0 != 0) {
        // 0x0032483c
        charge(ctx, 7);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x324844u, v0.u());
        sw(zero, s0, kErBlockB);
        sw(zero, s0, kErBlockBEnd);
        sw(zero, s0, kErBlockBMem);
    }
    // 0x00324858 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00325500 sub_325500 -- 664 bytes; frame 0xB0: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [fxNode_Step](node, out) one frame of a node tree (frames +132 > 0): the world position from the node's
// matrix (VU0), the billboard / inherit modes (sub_3263B0, sub_326280), then for each started child the child's
// transform and class slots 6 / 9 / 8 on its instance.
void sub_325500(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20}, f21{ctx, 21};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00325500
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    lw(v1, a0, kEnFrame);
    if (i64(v1) > 0) {
        // 0x00325534
        charge(ctx, 9);
        lw(s2, s4, kEnMode);
        lqc2(vf10, s4, kEnPos);
        lqc2(vf11, s4, kEnMatrix);
        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
        a1 = addiu(sp, 0xA0);
        sqc2(vf10, a1, 0);
        v1 = s2 & 0x60;
        if (v1 != 0) {
            // 0x00325558
            charge(ctx, 4);
            v1 = lui(0x8000);
            v1 = s2 & v1;
            if (v1 == 0) {
                // 0x00325568
                charge(ctx, 13);
                v1 = addiu(sp, 0x70);
                lq(v0, s4, kEnRot);
                sq(v0, v1, 0);
                a2 = addiu(sp, 0x80);
                jal(ctx, 0x325578u, gen::fn_sub_3263B0_003263b0);
                a0 = s4;
                a1 = addiu(sp, 0x80);
                jal(ctx, 0x325588u, gen::fn_sub_325D60_00325d60);
                v0 = addiu(sp, 0x70);
                lq(v0, v0, 0);
                sq(v0, s4, kEnRot);
            }
        }
        // 0x0032559c
        charge(ctx, 11);
        lw(v1, s4, kEnFrame);
        s1 = addiu(v1, -1);
        lwc1(f1, s4, kEnScale);
        lwc1(f0, s4, kEnScaleBase);
        mul_s(f21, f1, f0);
        lw(s3, s4, kEnChild);
        s0 = lui(0x8000);
        v1 = 0x40A00000;
        mtc1(v1, f20);
        for (;;) {
            // 0x00325754
            charge(ctx, 2);
            if (s3 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003255c8
            charge(ctx, 4);
            lw(v1, s3, 128);
            v1 = slt(s1, v1);
            if (v1 == 0) {
                // 0x003255d8
                charge(ctx, 4);
                lw(v1, s3, 132);
                v1 = v1 & 0x2;
                if (v1 == 0) {
                    // 0x003255e8
                    charge(ctx, 3);
                    v0 = s2 & s0;
                    if (v0 == 0) {
                        // 0x003255f4
                        charge(ctx, 4);
                        lw(v0, s3, 104);
                        v0 = v0 & 0x18;
                        if (v0 != 0) {
                            // 0x00325604
                            charge(ctx, 11);
                            a0 = s3;
                            a1 = addiu(sp, 0xA0);
                            a2 = addiu(sp, 0x90);
                            jal(ctx, 0x325610u, gen::fn_sub_326280_00326280);
                            v0 = addiu(sp, 0xA0);
                            lqc2(vf10, v0, 0);
                            lw(v1, s3, 104);
                            v0 = v1 & 0x4;
                            if (v0 != 0) {
                                // 0x00325630
                                charge(ctx, 4);
                                mfc1(v0, f20);
                                qmtc2(v0, vf2, false);  // qmtc2
                                vadd_bc(0x4, vf10, vf0, vf2, 0);  // vaddx.y
                            }
                            // 0x00325640
                            charge(ctx, 5);
                            v0 = addiu(sp, 0x90);
                            lqc2(vf11, v0, 0);
                            v0 = v1 & 0x80;
                            if (v0 != 0) {
                                // 0x00325654
                                charge(ctx, 4);
                                mfc1(v0, f21);
                                qmtc2(v0, vf2, false);  // qmtc2
                                vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                            }
                            // 0x00325664
                            charge(ctx, 16);
                            vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                            a1 = addiu(sp, 0x90);
                            sqc2(vf10, a1, 0);
                            lw(a0, s3, 144);
                            lhu(v1, a0, 4);
                            v0 = sll(v1, 1);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(v0, v1);
                            v1 = sll(v0, 2);
                            v0 = 0x6A0000;
                            v0 = addiu(v0, -16864);  // "PF2"
                            v0 = addu(v0, v1);
                            lw(v0, v0, 32);
                            if (v0 != 0) {
                                // 0x003256a4
                                charge(ctx, 3);
                                lw(a0, a0, 8);
                                jalr(ctx, 0x3256A8u, v0.u());
                            }
                        }
                        // 0x003256b0
                        charge(ctx, 4);
                        lw(v0, s3, 104);
                        v0 = v0 & 0x60;
                        if (v0 != 0) {
                            // 0x003256c0
                            charge(ctx, 18);
                            a0 = s3;
                            a1 = addiu(sp, 0xA0);
                            a2 = addiu(sp, 0x80);
                            jal(ctx, 0x3256CCu, gen::fn_sub_3263B0_003263b0);
                            lw(a0, s3, 144);
                            lhu(v1, a0, 4);
                            v0 = sll(v1, 1);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(v0, v1);
                            v1 = sll(v0, 2);
                            v0 = 0x6A0000;
                            v0 = addiu(v0, -16864);  // "PF2"
                            v0 = addu(v0, v1);
                            lw(v0, v0, 36);
                            if (v0 != 0) {
                                // 0x00325708
                                charge(ctx, 4);
                                lw(a0, a0, 8);
                                a1 = addiu(sp, 0x80);
                                jalr(ctx, 0x325710u, v0.u());
                            }
                        }
                    }
                    // 0x00325718
                    charge(ctx, 14);
                    lw(v0, s3, 144);
                    lw(a0, v0, 8);
                    lhu(v1, v0, 4);
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -16864);  // "PF2"
                    v0 = addu(v0, v1);
                    lw(v0, v0, 12);
                    jalr(ctx, 0x325748u, v0.u());
                }
            }
            // 0x00325750
            charge(ctx, 1);
            lw(s3, s3, 172);
        }
        // 0x0032575c
        charge(ctx, 4);
        lw(v1, s4, kEnMode);
        v1 = dsll32(v1, 1);
        v1 = dsrl32(v1, 1);
        sw(v1, s4, kEnMode);
    }
    // 0x0032576c (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x003257E0 sub_3257E0 -- 308 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fxNode_Destroy](node) destroys a node tree: each child's effect record (class slot 4 on the instance, the two
// blocks) unless shared, each child, the node (all through the RwFree slot).
void sub_3257E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003257e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(s2, a0, kEnChild);
    for (;;) {
        // 0x003258d8
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00325808
        charge(ctx, 5);
        lw(s1, s2, 172);
        lw(v0, s2, 152);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x0032581c
            charge(ctx, 4);
            lw(s0, s2, 144);
            lw(a0, s0, 8);
            if (a0 != 0) {
                // 0x0032582c
                charge(ctx, 12);
                lhu(v1, s0, 4);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x6A0000;
                v0 = addiu(v0, -16864);  // "PF2"
                v0 = addu(v0, v1);
                lw(v0, v0, 16);
                jalr(ctx, 0x325854u, v0.u());
            }
            // 0x0032585c
            charge(ctx, 3);
            lw(a0, s0, 24);
            if (a0 != 0) {
                // 0x00325868
                charge(ctx, 7);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                jalr(ctx, 0x325870u, v0.u());
                sw(zero, s0, 16);
                sw(zero, s0, 20);
                sw(zero, s0, 24);
            }
            // 0x00325884
            charge(ctx, 3);
            lw(a0, s0, 40);
            if (a0 != 0) {
                // 0x00325890
                charge(ctx, 7);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                jalr(ctx, 0x325898u, v0.u());
                sw(zero, s0, 32);
                sw(zero, s0, 36);
                sw(zero, s0, 40);
            }
            // 0x003258ac
            charge(ctx, 5);
            a0 = s0;
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            jalr(ctx, 0x3258B8u, v0.u());
        }
        // 0x003258c0
        charge(ctx, 6);
        a0 = s2;
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x3258CCu, v0.u());
        s2 = s1;
    }
    // 0x003258e0
    charge(ctx, 13);
    a0 = s3;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    jalr(ctx, 0x3258ECu, v0.u());
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00325B80 sub_325B80 -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fxNode_Reset](node) class slot 7 on every child's instance; frames 0.
void sub_325B80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00325b80
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, kEnChild);
    for (;;) {
        // 0x00325be4
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00325ba0
        charge(ctx, 13);
        lw(a1, s0, 144);
        lhu(a0, a1, 4);
        v1 = sll(a0, 1);
        v1 = addu(v1, a0);
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        a0 = sll(v1, 2);
        v1 = 0x6A0000;
        v1 = addiu(v1, -16864);  // "PF2"
        v1 = addu(v1, a0);
        lw(v1, v1, 28);
        if (v1 != 0) {
            // 0x00325bd4
            charge(ctx, 3);
            lw(a0, a1, 8);
            jalr(ctx, 0x325BD8u, v1.u());
        }
        // 0x00325be0
        charge(ctx, 1);
        lw(s0, s0, 172);
    }
    // 0x00325bec
    charge(ctx, 7);
    sw(zero, s1, kEnFrame);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00325C10 sub_325C10 -- 332 bytes; frame 0x90: ra sp+0x20, s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [fxNode_SetPosition](node, pos*) stores the position, rebuilds the matrix (VU0, sub_357E30) and passes
// each child its transformed position (class slot 8).
void sub_325C10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20}, f21{ctx, 21};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11}, vf28{ctx, 28}, vf29{ctx, 29}, vf30{ctx, 30}, vf31{ctx, 31};
    // 0x00325c10
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s0 = a0;
    lqc2(vf10, a1, 0);
    sqc2(vf10, s0, kEnPos);
    lqc2(vf11, s0, kEnMatrix);
    vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
    v0 = addiu(sp, 0x40);
    sqc2(vf10, v0, 0);
    lqc2(vf10, s0, kEnRot);
    jal(ctx, 0x325C44u, gen::fn_sub_357E30_00357e30);  // [effMisc] VU0 rotation matrix from Euler angles
    v1 = addiu(sp, 0x50);
    sqc2(vf28, v1, 0);
    sqc2(vf29, v1, 16);
    sqc2(vf30, v1, 32);
    sqc2(vf31, v1, 48);
    lwc1(f1, s0, kEnScale);
    lwc1(f0, s0, kEnScaleBase);
    mul_s(f21, f1, f0);
    lw(s0, s0, kEnChild);
    v1 = 0x40A00000;
    mtc1(v1, f20);
    for (;;) {
        // 0x00325d38
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00325c80
        charge(ctx, 6);
        v1 = addiu(sp, 0x40);
        lqc2(vf10, v1, 0);
        lw(a0, s0, 104);
        v1 = a0 & 0x4;
        if (v1 != 0) {
            // 0x00325c98
            charge(ctx, 4);
            mfc1(v0, f20);
            qmtc2(v0, vf2, false);  // qmtc2
            vadd_bc(0x4, vf10, vf0, vf2, 0);  // vaddx.y
        }
        // 0x00325ca8
        charge(ctx, 4);
        lqc2(vf11, s0, 64);
        v1 = a0 & 0x80;
        if (v1 != 0) {
            // 0x00325cb8
            charge(ctx, 4);
            mfc1(v1, f21);
            qmtc2(v1, vf2, false);  // qmtc2
            vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
        }
        // 0x00325cc8
        charge(ctx, 24);
        v1 = addiu(sp, 0x50);
        lqc2(vf28, v1, 0);
        lqc2(vf29, v1, 16);
        lqc2(vf30, v1, 32);
        lqc2(vf31, v1, 48);
        vmula_bc(0xF, vf28, vf11, 0);  // vmulax.xyzw
        vmadda_bc(0xF, vf29, vf11, 1);  // vmadday.xyzw
        vmadd_bc(0xF, vf11, vf30, vf11, 2);  // vmaddz.xyzw
        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
        a1 = addiu(sp, 0x30);
        sqc2(vf10, a1, 0);
        lw(a2, s0, 144);
        lhu(a0, a2, 4);
        v1 = sll(a0, 1);
        v1 = addu(v1, a0);
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        a0 = sll(v1, 2);
        v1 = 0x6A0000;
        v1 = addiu(v1, -16864);  // "PF2"
        v1 = addu(v1, a0);
        lw(v1, v1, 32);
        if (v1 != 0) {
            // 0x00325d28
            charge(ctx, 3);
            lw(a0, a2, 8);
            jalr(ctx, 0x325D2Cu, v1.u());
        }
        // 0x00325d34
        charge(ctx, 1);
        lw(s0, s0, 172);
    }
    // 0x00325d40
    charge(ctx, 7);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00325D60 sub_325D60 -- 220 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fxNode_SetRotation](node, rot*) stores the rotation, rotates the matrix, passes each child its rotation
// (class slot 9), then the position again (sub_325C10).
void sub_325D60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Vf vf10{ctx, 10}, vf11{ctx, 11}, vf28{ctx, 28}, vf29{ctx, 29}, vf30{ctx, 30};
    // 0x00325d60
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lqc2(vf10, a1, 0);
    sqc2(vf10, s1, kEnRot);
    v0 = addiu(sp, 0x40);
    sqc2(vf10, v0, 0);
    jal(ctx, 0x325D84u, gen::fn_sub_357E30_00357e30);  // [effMisc] VU0 rotation matrix from Euler angles
    lqc2(vf10, s1, kEnRow1);
    vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
    vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
    vmadd_bc(0xF, vf10, vf30, vf10, 2);  // vmaddz.xyzw
    sqc2(vf10, s1, kEnMatrix);
    lw(s0, s1, kEnChild);
    for (;;) {
        // 0x00325e0c
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00325dac
        charge(ctx, 20);
        lqc2(vf10, s0, 80);
        v0 = addiu(sp, 0x40);
        lqc2(vf11, v0, 0);
        jal(ctx, 0x325DB8u, gen::fn_sub_357DD0_00357dd0);  // [effMisc] VU0 vector x matrix
        a1 = addiu(sp, 0x30);
        sqc2(vf10, a1, 0);
        lw(a0, s0, 144);
        lhu(v1, a0, 4);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x6A0000;
        v0 = addiu(v0, -16864);  // "PF2"
        v0 = addu(v0, v1);
        lw(v0, v0, 36);
        if (v0 != 0) {
            // 0x00325dfc
            charge(ctx, 3);
            lw(a0, a0, 8);
            jalr(ctx, 0x325E00u, v0.u());
        }
        // 0x00325e08
        charge(ctx, 1);
        lw(s0, s0, 172);
    }
    // 0x00325e14
    charge(ctx, 10);
    a0 = s1;
    a1 = addiu(s1, kEnPos);
    jal(ctx, 0x325E1Cu, gen::fn_sub_325C10_00325c10);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00325E40 sub_325E40 -- 484 bytes; frame 0x60: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [fxNode_SetScale](node, scale $f12) stores the scale; each child gets it (class slot 10, or slot 11 with its
// scaled row for mode bit 8) and, for mode bit 7, its rescaled position (slot 8).
void sub_325E40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00325e40
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    swc1(f12, a0, kEnScale);
    lwc1(f0, a0, kEnScaleBase);
    mul_s(f21, f12, f0);
    lw(s0, a0, kEnChild);
    v1 = 0x40A00000;
    mtc1(v1, f20);
    for (;;) {
        // 0x00325ffc
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00325e7c
        charge(ctx, 4);
        lw(v1, s0, 104);
        v1 = v1 & 0x100;
        if (v1 != 0) {
            // 0x00325eec
            charge(ctx, 6);
            lqc2(vf10, s0, 32);
            lwc1(f0, s0, 96);
            lw(v1, s0, 132);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x00325f04
                charge(ctx, 1);
                mul_s(f0, f0, f21);
            }
            // 0x00325f08
            charge(ctx, 19);
            mfc1(v1, f0);
            qmtc2(v1, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            a1 = addiu(sp, 0x40);
            sqc2(vf10, a1, 0);
            lw(a2, s0, 144);
            lhu(a0, a2, 4);
            v1 = sll(a0, 1);
            v1 = addu(v1, a0);
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 0x6A0000;
            v1 = addiu(v1, -16864);  // "PF2"
            v1 = addu(v1, a0);
            lw(v1, v1, 44);
            if (v1 != 0) {
                // 0x00325f54
                charge(ctx, 3);
                lw(a0, a2, 8);
                jalr(ctx, 0x325F58u, v1.u());
            }
        } else {
            // 0x00325e8c
            charge(ctx, 5);
            lwc1(f12, s0, 96);
            lw(v1, s0, 132);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x00325ea0
                charge(ctx, 1);
                mul_s(f12, f12, f21);
            }
            // 0x00325ea4
            charge(ctx, 13);
            lw(a1, s0, 144);
            lhu(a0, a1, 4);
            v1 = sll(a0, 1);
            v1 = addu(v1, a0);
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 0x6A0000;
            v1 = addiu(v1, -16864);  // "PF2"
            v1 = addu(v1, a0);
            lw(v1, v1, 40);
            if (v1 != 0) {
                // 0x00325ed8
                charge(ctx, 5);
                lw(a0, a1, 8);
                jalr(ctx, 0x325EDCu, v1.u());
            }
        }
        // 0x00325f60
        charge(ctx, 4);
        lw(a0, s0, 104);
        v1 = a0 & 0x80;
        if (v1 != 0) {
            // 0x00325f70
            charge(ctx, 6);
            lqc2(vf10, s1, kEnPos);
            lqc2(vf11, s1, kEnMatrix);
            vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
            v1 = a0 & 0x4;
            if (v1 != 0) {
                // 0x00325f88
                charge(ctx, 4);
                mfc1(v0, f20);
                qmtc2(v0, vf2, false);  // qmtc2
                vadd_bc(0x4, vf10, vf0, vf2, 0);  // vaddx.y
            }
            // 0x00325f98
            charge(ctx, 21);
            lqc2(vf11, s0, 64);
            mfc1(v1, f21);
            qmtc2(v1, vf2, false);  // qmtc2
            vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
            vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
            a1 = addiu(sp, 0x50);
            sqc2(vf10, a1, 0);
            lw(a2, s0, 144);
            lhu(a0, a2, 4);
            v1 = sll(a0, 1);
            v1 = addu(v1, a0);
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 0x6A0000;
            v1 = addiu(v1, -16864);  // "PF2"
            v1 = addu(v1, a0);
            lw(v1, v1, 32);
            if (v1 != 0) {
                // 0x00325fec
                charge(ctx, 3);
                lw(a0, a2, 8);
                jalr(ctx, 0x325FF0u, v1.u());
            }
        }
        // 0x00325ff8
        charge(ctx, 1);
        lw(s0, s0, 172);
    }
    // 0x00326004
    charge(ctx, 8);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00326030 sub_326030 -- 292 bytes; frame 0x50: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// [fxNode_SetColour](node, rgba) stores the colour and gives each child its own colour x this one (VU0,
// 1 / 255 = 0x7CAE4C; class slot 12).
void sub_326030(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f20{ctx, 20};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00326030
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    sw(a1, a0, kEnColour);
    sw(a1, sp, 0x4C);
    v0 = addiu(sp, 0x4C);
    lwc1(f20, gp, -32420);  // 0x7CAE4C = 0.00392157f
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v1, f20);
    qmtc2(v1, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    v1 = addiu(sp, 0x30);
    sqc2(vf10, v1, 0);
    lw(s0, a0, kEnChild);
    if (s0 != 0) {
        // 0x00326088
        charge(ctx, 2);
        for (;;) {
            // 0x00326134
            charge(ctx, 2);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00326090
            charge(ctx, 37);
            lw(v0, s0, 100);
            sw(v0, sp, 0x48);
            v0 = addiu(sp, 0x48);
            lw(v0, v0, 0);
            pextlb(v0, zero, v0);
            pextlh(v0, zero, v0);
            qmtc2(v0, vf10, false);  // qmtc2
            vitof0(0xF, vf10, vf10);  // vitof0.xyzw
            mfc1(v1, f20);
            qmtc2(v1, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            v1 = addiu(sp, 0x30);
            lqc2(vf11, v1, 0);
            vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
            v1 = 0x437F0000;
            qmtc2(v1, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
            qmfc2(v1, vf10, false);  // qmfc2
            ppach(v1, zero, v1);
            ppacb(v1, zero, v1);
            sw(v1, sp, 0x44);
            lw(a1, sp, 0x44);
            lw(a2, s0, 144);
            lhu(a0, a2, 4);
            v1 = sll(a0, 1);
            v1 = addu(v1, a0);
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            v1 = 0x6A0000;
            v1 = addiu(v1, -16864);  // "PF2"
            v1 = addu(v1, a0);
            lw(v1, v1, 48);
            if (v1 != 0) {
                // 0x00326124
                charge(ctx, 3);
                lw(a0, a2, 8);
                jalr(ctx, 0x326128u, v1.u());
            }
            // 0x00326130
            charge(ctx, 1);
            lw(s0, s0, 172);
        }
    }
    // 0x0032613c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00326280 sub_326280 -- 296 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fxNode_BillboardRotation](node, out) for mode bits 3 / 4: the rotation that turns the node to the
// camera (sub_329800; bit 4 keeps it upright).
void sub_326280(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00326280
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    lw(v1, a0, kEnMode);
    v0 = v1 & 0x18;
    if (v0 != 0) {
        // 0x003262b8
        charge(ctx, 4);
        lqc2(vf10, s1, kEnPos);
        v0 = v1 & 0x10;
        if (v0 != 0) {
            // 0x003262c8
            charge(ctx, 6);
            mtc1(zero, f0);
            mfc1(v0, f0);
            qmtc2(v0, vf2, false);  // qmtc2
            vadd_bc(0x4, vf10, vf0, vf2, 0);  // vaddx.y
        }
        // 0x003262e0
        charge(ctx, 21);
        vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
        vadd_bc(0x8, vf2, vf2, vf2, 1);  // vaddy.x
        vadd_bc(0x8, vf2, vf2, vf2, 2);  // vaddz.x
        vsqrt(vf2, 0);  // vsqrt
        vwaitq(ctx);
        cfc2(v0, 22, false);  // cfc2
        mtc1(v0, f0);
        sw(v0, sp, 0x40);
        sw(v0, sp, 0x44);
        sw(v0, sp, 0x48);
        a0 = a1;
        a1 = addiu(sp, 0x30);
        jal(ctx, 0x326310u, gen::fn_sub_329800_00329800);
        v1 = addiu(sp, 0x30);
        lqc2(vf10, v1, 0);
        vsub(0xE, vf10, vf0, vf10);  // vsub.xyz
        lw(v1, s1, kEnMode);
        a0 = v1 & 0x10;
        if (a0 != 0) {
            // 0x00326334
            charge(ctx, 6);
            mtc1(zero, f0);
            mfc1(v0, f0);
            qmtc2(v0, vf2, false);  // qmtc2
            vadd_bc(0x4, vf10, vf0, vf2, 0);  // vaddx.y
        }
        // 0x0032634c
        charge(ctx, 12);
        vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
        vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
        vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
        vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
        vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
        vwaitq(ctx);
        vmulq(0xE, vf10, vf10);  // vmulq.xyz
        v1 = addiu(sp, 0x40);
        lqc2(vf11, v1, 0);
        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
        if (a0 != 0) {
            // 0x0032637c
            charge(ctx, 4);
            lw(v0, s1, 68);
            qmtc2(v0, vf2, false);  // qmtc2
            vadd_bc(0x4, vf10, vf0, vf2, 0);  // vaddx.y
        }
        // 0x0032638c
        charge(ctx, 1);
        sqc2(vf10, s0, 0);
    } else {
        // 0x003262a8
        charge(ctx, 4);
        lq(v0, s1, kEnPos);
        sq(v0, s0, 0);
    }
    // 0x00326390 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003263B0 sub_3263B0 -- 224 bytes; frame 0x50: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [fxNode_FaceCamera](node, out) for mode bits 5 / 6: the Euler angles towards the camera (acosf / atan2f,
// sub_357EA0); else the node's own rotation.
void sub_3263B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20};
    Vf vf10{ctx, 10}, vf11{ctx, 11};
    // 0x003263b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    s0 = a2;
    lw(v0, a0, kEnMode);
    v0 = v0 & 0x60;
    if (v0 != 0) {
        // 0x003263ec
        charge(ctx, 8);
        a0 = a1;
        a1 = addiu(sp, 0x40);
        jal(ctx, 0x3263F4u, gen::fn_sub_329800_00329800);
        lw(v0, s1, kEnMode);
        v0 = v0 & 0x40;
        if (v0 == 0) {
            // 0x00326418
            charge(ctx, 5);
            lwc1(f0, sp, 0x44);
            neg_s(f12, f0);
            jal(ctx, 0x326420u, gen::fn_acosf_0052e9e8);
            neg_s(f20, f0);
        } else {
            // 0x0032640c
            charge(ctx, 3);
            mtc1(zero, f20);
        }
        // 0x0032642c
        charge(ctx, 13);
        lwc1(f12, sp, 0x40);
        lwc1(f13, sp, 0x48);
        jal(ctx, 0x326434u, gen::fn_atan2f_0052ea18);
        mtc1(zero, f14);
        mov_s(f12, f20);
        mov_s(f13, f0);
        jal(ctx, 0x326448u, gen::fn_sub_357EA0_00357ea0);
        lw(v1, s1, kEnMode);
        v1 = v1 & 0x40;
        if (v1 != 0) {
            // 0x00326460
            charge(ctx, 4);
            vmove(0xF, vf11, vf10);  // vmove.xyzw
            lqc2(vf10, s1, kEnRot);
            jal(ctx, 0x326468u, gen::fn_sub_357DD0_00357dd0);  // [effMisc] VU0 vector x matrix
        }
        // 0x00326470
        charge(ctx, 1);
        sqc2(vf10, s0, 0);
    } else {
        // 0x003263dc
        charge(ctx, 4);
        lq(v0, s1, kEnRot);
        sq(v0, s0, 0);
    }
    // 0x00326474 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00326740 sub_326740 -- 384 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fxInst_Destroy](inst) destroys a class instance: its effect records and node trees (counts from the particle
// system or +0), the two models, the owned particle system, the mesh, the block.
void sub_326740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00326740
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, a0, kFiNodesMem);
    if (v0 != 0) {
        // 0x00326764
        charge(ctx, 3);
        lw(v0, s2, kFiPsys);
        if (v0 == 0) {
            // 0x0032677c
            charge(ctx, 1);
            lw(s0, s2, kFiCount);
        } else {
            // 0x00326770
            charge(ctx, 3);
            lw(s0, v0, 8);
        }
        // 0x00326780
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x003267a8
            charge(ctx, 3);
            v0 = sltu(s1, s0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0032678c
            charge(ctx, 7);
            v1 = sll(s1, 2);
            lw(v0, s2, kFiNodes);
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
            jal(ctx, 0x32679Cu, gen::fn_sub_324740_00324740);
            s1 = addiu(s1, 1);
        }
        // 0x003267b4
        charge(ctx, 5);
        lw(a0, s2, kFiNodesMem);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x3267C0u, v0.u());
    }
    // 0x003267c8
    charge(ctx, 3);
    lw(v0, s2, kFiTreesMem);
    if (v0 != 0) {
        // 0x003267d4
        charge(ctx, 3);
        lw(v0, s2, kFiPsys);
        if (v0 == 0) {
            // 0x003267ec
            charge(ctx, 1);
            lw(s0, s2, kFiCount);
        } else {
            // 0x003267e0
            charge(ctx, 3);
            lw(s0, v0, 8);
        }
        // 0x003267f0
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x00326818
            charge(ctx, 3);
            v0 = sltu(s1, s0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003267fc
            charge(ctx, 7);
            v1 = sll(s1, 2);
            lw(v0, s2, kFiTrees);
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
            jal(ctx, 0x32680Cu, gen::fn_sub_3257E0_003257e0);
            s1 = addiu(s1, 1);
        }
        // 0x00326824
        charge(ctx, 5);
        lw(a0, s2, kFiTreesMem);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x326830u, v0.u());
    }
    // 0x00326838
    charge(ctx, 3);
    lw(a0, s2, kFiModelA);
    if (a0 != 0) {
        // 0x00326844
        charge(ctx, 2);
        jal(ctx, 0x326844u, gen::fn_sub_322660_00322660);
    }
    // 0x0032684c
    charge(ctx, 3);
    lw(a0, s2, kFiModelB);
    if (a0 != 0) {
        // 0x00326858
        charge(ctx, 2);
        jal(ctx, 0x326858u, gen::fn_sub_322F20_00322f20);
    }
    // 0x00326860
    charge(ctx, 4);
    lbu(v0, s2, kFiOwns);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x00326870
        charge(ctx, 3);
        lw(a0, s2, kFiPsys);
        jal(ctx, 0x326874u, gen::fn_sub_3321D0_003321d0);
    }
    // 0x0032687c
    charge(ctx, 3);
    lw(a0, s2, kFiMesh);
    if (a0 != 0) {
        // 0x00326888
        charge(ctx, 2);
        jal(ctx, 0x326888u, gen::fn_sub_3237C0_003237c0);
    }
    // 0x00326890
    charge(ctx, 12);
    a0 = s2;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    jalr(ctx, 0x32689Cu, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00326C70 sub_326C70 -- 116 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fxInst_SetPsys](inst, type, arg) replaces the particle system (sub_332070) and marks it owned.
void sub_326C70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00326c70
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    lw(a0, a0, kFiPsys);
    if (a0 != 0) {
        // 0x00326c9c
        charge(ctx, 2);
        jal(ctx, 0x326C9Cu, gen::fn_sub_3321D0_003321d0);
    }
    // 0x00326ca4
    charge(ctx, 16);
    a0 = s1 & 0xFFFF;
    lw(a1, s2, kFiCount);
    a2 = s0;
    jal(ctx, 0x326CB0u, gen::fn_sub_332070_00332070);
    sw(v0, s2, kFiPsys);
    lbu(v1, s2, kFiOwns);
    v1 = v1 | 0x1;
    sb(v1, s2, kFiOwns);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00326CF0 sub_326CF0 -- 192 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fxInst_SetMesh](inst, n, kind) replaces the mesh: kind 2 -> sub_3234F0(n, 0x200000A7), kinds 1 / 4 ->
// sub_3234F0(n, 0x20080027), kind 7 and the rest none (the old mesh is freed first).
void sub_326CF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00326cf0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    lw(a0, a0, kFiMesh);
    if (a0 != 0) {
        // 0x00326d1c
        charge(ctx, 2);
        jal(ctx, 0x326D1Cu, gen::fn_sub_3237C0_003237c0);
    }
    // 0x00326d24
    charge(ctx, 3);
    v1 = 7;
    if (s0 != v1) {
        // 0x00326d30
        charge(ctx, 3);
        v1 = 2;
        if (s0 == v1) {
            // 0x00326d7c
            charge(ctx, 6);
            a0 = s1 & 0xFFFF;
            v0 = 0x20000000;
            a1 = v0 | 0xA7;
            jal(ctx, 0x326D88u, gen::fn_sub_3234F0_003234f0);
            sw(v0, s2, kFiMesh);
        } else {
            // 0x00326d3c
            charge(ctx, 3);
            v1 = 4;
            if (s0 != v1) {
                // 0x00326d48
                charge(ctx, 3);
                v1 = 1;
                if (s0 != v1) {
                    // 0x00326d54: any other kind -- no mesh
                    charge(ctx, 2);
                    // 0x00326d94 (the shared epilogue, written out on this path)
                    charge(ctx, 7);
                    ld(ra, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x40);
                    return;
                }
            }
            // 0x00326d5c: kinds 4 and 1
            charge(ctx, 8);
            a0 = s1 & 0xFFFF;
            v0 = 0x20080000;
            a1 = v0 | 0x27;
            jal(ctx, 0x326D68u, gen::fn_sub_3234F0_003234f0);
            sw(v0, s2, 80);
        }
    }
    // 0x00326d94 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00326DB0 sub_326DB0 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fxInst_SetTextureById](inst, id) the texture by id (sub_3210A0): its half size / 16 into +84 / +88, set
// on the mesh's material.
void sub_326DB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00326db0
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = a1 & 0xFFFF;
    jal(ctx, 0x326DC4u, gen::fn_sub_3210A0_003210a0);  // [effLayer] texture by id
    a1 = v0;
    lw(v0, v0, 0);
    lwc1(f0, v0, 16);
    cvt_s_w(f3, f0);
    lwc1(f0, v0, 12);
    cvt_s_w(f0, f0);
    v0 = 0x40000000;
    mtc1(v0, f2);
    div_s(f0, f0, f2);
    v0 = 0x41800000;
    mtc1(v0, f1);
    div_s(f0, f0, f1);
    swc1(f0, s0, kFiTexU);
    div_s(f0, f3, f2);
    div_s(f0, f0, f1);
    swc1(f0, s0, kFiTexV);
    lw(v0, s0, kFiMesh);
    lw(v0, v0, 16);
    lw(v0, v0, 24);
    lw(v0, v0, 32);
    lw(a0, v0, 0);
    jal(ctx, 0x326E28u, gen::fn_sub_494D50_00494d50);  // RpMaterialSetTexture-like: (material, texture)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00326E50 sub_326E50 -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fxInst_SetTextureByName](inst, name) the same by name, dropping the lookup's reference.
void sub_326E50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00326e50
    enter(ctx, 43);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = a1;
    jal(ctx, 0x326E68u, gen::fn_sub_3210C0_003210c0);  // [effLayer] texture by name
    s0 = v0;
    lw(v0, v0, 0);
    lwc1(f0, v0, 16);
    cvt_s_w(f3, f0);
    lwc1(f0, v0, 12);
    cvt_s_w(f0, f0);
    v0 = 0x40000000;
    mtc1(v0, f2);
    div_s(f0, f0, f2);
    v0 = 0x41800000;
    mtc1(v0, f1);
    div_s(f0, f0, f1);
    swc1(f0, s1, kFiTexU);
    div_s(f0, f3, f2);
    div_s(f0, f0, f1);
    swc1(f0, s1, kFiTexV);
    lw(v0, s1, kFiMesh);
    lw(v0, v0, 16);
    lw(v0, v0, 24);
    lw(v0, v0, 32);
    lw(a0, v0, 0);
    a1 = s0;
    jal(ctx, 0x326ED0u, gen::fn_sub_494D50_00494d50);  // RpMaterialSetTexture-like: (material, texture)
    a0 = s0;
    jal(ctx, 0x326EDCu, gen::fn_sub_4D0F00_004d0f00);  // RwTextureDestroy-like: drops the reference
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00326F00 sub_326F00 -- 84 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fxInst_SetModelA](inst, arg) replaces model A (sub_322660 / sub_322530).
void sub_326F00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00326f00
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(a0, a0, kFiModelA);
    if (a0 != 0) {
        // 0x00326f24
        charge(ctx, 2);
        jal(ctx, 0x326F24u, gen::fn_sub_322660_00322660);
    }
    // 0x00326f2c
    charge(ctx, 10);
    a0 = s0;
    jal(ctx, 0x326F30u, gen::fn_sub_322530_00322530);
    sw(v0, s1, kFiModelA);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003271C0 sub_3271C0 -- 84 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fxInst_SetModelB](inst, arg) replaces model B (sub_322F20 / sub_322DC0).
void sub_3271C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003271c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(a0, a0, kFiModelB);
    if (a0 != 0) {
        // 0x003271e4
        charge(ctx, 2);
        jal(ctx, 0x3271E4u, gen::fn_sub_322F20_00322f20);
    }
    // 0x003271ec
    charge(ctx, 10);
    a0 = s0;
    jal(ctx, 0x3271F0u, gen::fn_sub_322DC0_00322dc0);
    sw(v0, s1, kFiModelB);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003282E0 sub_3282E0 -- 4208 bytes; frame 0x270: ra sp+0x70, s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f31 sp+0x2C, f30 sp+0x28, f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [fxPsys_Draw2D](inst) draws a particle system's particles as screen quads (class 7 path: Im2D through the
// RwIm2DRenderPrimitive slot; per particle the projected position, size, rotation by sin / cos, colour).
void sub_3282E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29}, f30{ctx, 30}, f31{ctx, 31};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11}, vf28{ctx, 28}, vf29{ctx, 29}, vf30{ctx, 30}, vf31{ctx, 31};
    // 0x003282e0
    enter(ctx, 51);  // entry check point + this block's cycles
    sp = addiu(sp, -0x270);
    sd(ra, sp, 0x70);
    sq(s3, sp, 0x60);
    sq(s2, sp, 0x50);
    sq(s1, sp, 0x40);
    sq(s0, sp, 0x30);
    swc1(f31, sp, 0x2C);
    swc1(f30, sp, 0x28);
    swc1(f29, sp, 0x24);
    swc1(f28, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s3 = a0;
    lw(v0, a0, 4);
    sw(v0, sp, 0x268);
    v0 = addiu(sp, 0x268);
    lwc1(f20, gp, -32232);  // 0x7CAF08 = 0.00392157f
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f20);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    v0 = addiu(sp, 0x220);
    sqc2(vf10, v0, 0);
    lw(s1, a0, 76);
    lw(s2, s1, 24);
    v0 = 0x960000;
    lwc1(f23, v0, 140);  // 0x96008C (the Im2D 1 / near-z word)
    v0 = 0x960000;
    lwc1(f24, v0, 136);  // g_rwIm2DNearScreenZ
    jal(ctx, 0x328380u, gen::fn_sub_198590_00198590);  // the current camera / render context
    lwc1(f21, v0, 132);
    jal(ctx, 0x32838Cu, gen::fn_sub_198590_00198590);  // the current camera / render context
    lwc1(f22, v0, 128);
    lw(s0, s1, 8);
    lhu(v1, s3, 12);
    v0 = 7;
    if (v1 == v0) {
        // 0x003283b4
        charge(ctx, 4);
        lw(v0, s1, 12);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x00328aec
            charge(ctx, 43);
            a0 = s1;
            a1 = addiu(sp, 0x100);
            jal(ctx, 0x328AF4u, gen::fn_sub_3322F0_003322f0);
            a0 = s1;
            a1 = addiu(sp, 0x110);
            jal(ctx, 0x328B04u, gen::fn_sub_3322B0_003322b0);
            v0 = addiu(sp, 0x100);
            lqc2(vf10, v0, 0);
            jal(ctx, 0x328B14u, gen::fn_sub_357E30_00357e30);  // [effMisc] VU0 rotation matrix from Euler angles
            v0 = addiu(sp, 0x110);
            lqc2(vf31, v0, 0);
            v0 = addiu(sp, 0xC0);
            sqc2(vf28, v0, 0);
            sqc2(vf29, v0, 16);
            sqc2(vf30, v0, 32);
            sqc2(vf31, v0, 48);
            s1 = 0;
            v0 = 0x437F0000;
            mtc1(v0, f0);
            swc1(f0, sp, 0x9C);
            v0 = 0x42000000;
            mtc1(v0, f31);
            v0 = lui(0xC000);
            mtc1(v0, f0);
            swc1(f0, sp, 0x98);
            v0 = 0x40000000;
            mtc1(v0, f0);
            swc1(f0, sp, 0x94);
            mtc1(zero, f30);
            v0 = 0x3F800000;
            mtc1(v0, f29);
            v0 = 0x44200000;
            mtc1(v0, f28);
            v0 = 0x43E00000;
            mtc1(v0, f27);
            for (;;) {  // while (s1 < s0)
                // 0x003292dc
                charge(ctx, 3);
                v0 = slt(s1, s0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00328b98
                charge(ctx, 3);
                lw(v0, s2, 16);
                if (i64(v0) >= 0) {
                    // 0x00328ba4
                    charge(ctx, 52);
                    v0 = addiu(sp, 0xC0);
                    lqc2(vf28, v0, 0);
                    lqc2(vf29, v0, 16);
                    lqc2(vf30, v0, 32);
                    lqc2(vf31, v0, 48);
                    lqc2(vf10, s2, 0);
                    vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
                    vmadda_bc(0xF, vf30, vf10, 2);  // vmaddaz.xyzw
                    vmadd_bc(0xF, vf10, vf31, vf0, 3);  // vmaddw.xyzw
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -15152);  // &0x69C4D0
                    sqc2(vf10, v0, 0);  // 0x69C4D0
                    v0 = 0x6A0000;
                    lwc1(f0, v0, -15152);  // 0x69C4D0
                    swc1(f0, sp, 0x248);
                    v0 = 0x6A0000;
                    lwc1(f0, v0, -15148);  // 0x69C4D4
                    swc1(f0, sp, 0x24C);
                    v0 = 0x6A0000;
                    lwc1(f0, v0, -15144);  // 0x69C4D8
                    swc1(f0, sp, 0x250);
                    lw(v0, s2, 20);
                    sw(v0, sp, 0x260);
                    v0 = addiu(sp, 0x260);
                    lw(v0, v0, 0);
                    pextlb(v0, zero, v0);
                    pextlh(v0, zero, v0);
                    qmtc2(v0, vf10, false);  // qmtc2
                    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
                    mfc1(v0, f20);
                    qmtc2(v0, vf2, false);  // qmtc2
                    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                    v0 = addiu(sp, 0x220);
                    lqc2(vf11, v0, 0);
                    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                    lwc1(f0, sp, 0x9C);
                    mfc1(v0, f0);
                    qmtc2(v0, vf2, false);  // qmtc2
                    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                    vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                    qmfc2(v0, vf10, false);  // qmfc2
                    ppach(v0, zero, v0);
                    ppacb(v0, zero, v0);
                    sw(v0, sp, 0x258);
                    lw(v0, sp, 0x258);
                    sw(v0, sp, 0x26C);
                    lbu(v0, sp, 0x26F);
                    if (v0 != 0) {
                        // 0x00328c74
                        charge(ctx, 28);
                        lw(a1, s2, 16);
                        lw(a0, s3, 72);
                        a2 = addiu(sp, 0xA0);
                        jal(ctx, 0x328C80u, gen::fn_sub_322FD0_00322fd0);
                        lw(v0, sp, 0xB0);
                        a0 = 1;
                        lw(a1, v0, 0);
                        v0 = 0x960000;
                        lw(v0, v0, 144);  // pfn_RwRenderStateSet
                        jalr(ctx, 0x328C9Cu, v0.u());
                        lwc1(f2, s2, 24);
                        lwc1(f0, sp, 0xA8);
                        div_s(f1, f0, f31);
                        lwc1(f0, sp, 0xA0);
                        mul_s(f0, f1, f0);
                        mul_s(f0, f2, f0);
                        swc1(f0, sp, 0x90);
                        lwc1(f0, sp, 0xAC);
                        div_s(f1, f0, f31);
                        lwc1(f0, sp, 0xA4);
                        mul_s(f0, f1, f0);
                        mul_s(f0, f2, f0);
                        swc1(f0, sp, 0x8C);
                        lbu(a1, sp, 0x26C);
                        if (i64(a1) < 0) {
                            // 0x00328cf8
                            charge(ctx, 7);
                            v1 = srl(a1, 1);
                            v0 = a1 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328ce4
                            charge(ctx, 5);
                            mtc1(a1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328d14
                        charge(ctx, 4);
                        swc1(f0, sp, 0x140);
                        lbu(a0, sp, 0x26D);
                        if (i64(a0) < 0) {
                            // 0x00328d38
                            charge(ctx, 7);
                            v1 = srl(a0, 1);
                            v0 = a0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328d24
                            charge(ctx, 5);
                            mtc1(a0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328d54
                        charge(ctx, 4);
                        swc1(f0, sp, 0x144);
                        lbu(v1, sp, 0x26E);
                        if (i64(v1) < 0) {
                            // 0x00328d78
                            charge(ctx, 7);
                            a2 = srl(v1, 1);
                            v0 = v1 & 0x1;
                            a2 = a2 | v0;
                            mtc1(a2, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328d64
                            charge(ctx, 5);
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328d94
                        charge(ctx, 4);
                        swc1(f0, sp, 0x148);
                        lbu(v0, sp, 0x26F);
                        if (i64(v0) < 0) {
                            // 0x00328db8
                            charge(ctx, 7);
                            a3 = srl(v0, 1);
                            a2 = v0 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328da4
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328dd4
                        charge(ctx, 3);
                        swc1(f0, sp, 0x14C);
                        if (i64(a1) < 0) {
                            // 0x00328df4
                            charge(ctx, 7);
                            a3 = srl(a1, 1);
                            a2 = a1 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328de0
                            charge(ctx, 5);
                            mtc1(a1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328e10
                        charge(ctx, 3);
                        swc1(f0, sp, 0x180);
                        if (i64(a0) < 0) {
                            // 0x00328e30
                            charge(ctx, 7);
                            a3 = srl(a0, 1);
                            a2 = a0 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328e1c
                            charge(ctx, 5);
                            mtc1(a0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328e4c
                        charge(ctx, 3);
                        swc1(f0, sp, 0x184);
                        if (i64(v1) < 0) {
                            // 0x00328e6c
                            charge(ctx, 7);
                            a3 = srl(v1, 1);
                            a2 = v1 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328e58
                            charge(ctx, 5);
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328e88
                        charge(ctx, 3);
                        swc1(f0, sp, 0x188);
                        if (i64(v0) < 0) {
                            // 0x00328ea8
                            charge(ctx, 7);
                            a3 = srl(v0, 1);
                            a2 = v0 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328e94
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328ec4
                        charge(ctx, 3);
                        swc1(f0, sp, 0x18C);
                        if (i64(a1) < 0) {
                            // 0x00328ee4
                            charge(ctx, 7);
                            a3 = srl(a1, 1);
                            a2 = a1 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328ed0
                            charge(ctx, 5);
                            mtc1(a1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328f00
                        charge(ctx, 3);
                        swc1(f0, sp, 0x1C0);
                        if (i64(a0) < 0) {
                            // 0x00328f20
                            charge(ctx, 7);
                            a3 = srl(a0, 1);
                            a2 = a0 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328f0c
                            charge(ctx, 5);
                            mtc1(a0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328f3c
                        charge(ctx, 3);
                        swc1(f0, sp, 0x1C4);
                        if (i64(v1) < 0) {
                            // 0x00328f5c
                            charge(ctx, 7);
                            a3 = srl(v1, 1);
                            a2 = v1 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328f48
                            charge(ctx, 5);
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328f78
                        charge(ctx, 3);
                        swc1(f0, sp, 0x1C8);
                        if (i64(v0) < 0) {
                            // 0x00328f98
                            charge(ctx, 7);
                            a3 = srl(v0, 1);
                            a2 = v0 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328f84
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328fb4
                        charge(ctx, 3);
                        swc1(f0, sp, 0x1CC);
                        if (i64(a1) < 0) {
                            // 0x00328fd4
                            charge(ctx, 7);
                            a2 = srl(a1, 1);
                            a1 = a1 & 0x1;
                            a2 = a2 | a1;
                            mtc1(a2, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328fc0
                            charge(ctx, 5);
                            mtc1(a1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328ff0
                        charge(ctx, 3);
                        swc1(f0, sp, 0x200);
                        if (i64(a0) < 0) {
                            // 0x00329010
                            charge(ctx, 7);
                            a1 = srl(a0, 1);
                            a0 = a0 & 0x1;
                            a1 = a1 | a0;
                            mtc1(a1, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328ffc
                            charge(ctx, 5);
                            mtc1(a0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x0032902c
                        charge(ctx, 3);
                        swc1(f0, sp, 0x204);
                        if (i64(v1) < 0) {
                            // 0x0032904c
                            charge(ctx, 7);
                            a0 = srl(v1, 1);
                            v1 = v1 & 0x1;
                            a0 = a0 | v1;
                            mtc1(a0, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00329038
                            charge(ctx, 5);
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00329068
                        charge(ctx, 3);
                        swc1(f0, sp, 0x208);
                        if (i64(v0) < 0) {
                            // 0x00329088
                            charge(ctx, 7);
                            v1 = srl(v0, 1);
                            v0 = v0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00329074
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x003290a4
                        charge(ctx, 18);
                        swc1(f0, sp, 0x20C);
                        jal(ctx, 0x3290A8u, gen::fn_sub_198590_00198590);  // the current camera / render context
                        a0 = addiu(sp, 0x238);
                        a1 = addiu(sp, 0x248);
                        a2 = addiu(v0, 32);
                        jal(ctx, 0x3290BCu, gen::fn_sub_4C6BE0_004c6be0);
                        lwc1(f1, sp, 0x240);
                        lwc1(f0, sp, 0x23C);
                        div_s(f2, f0, f1);
                        lwc1(f0, sp, 0x238);
                        div_s(f1, f0, f1);
                        lwc1(f0, sp, 0x98);
                        c_lt_s(f1, f0);
                        if (!cond(ctx)) {
                            // 0x003290ec
                            charge(ctx, 4);
                            lwc1(f0, sp, 0x94);
                            c_le_s(f1, f0);
                            if (!cond(ctx)) {
                                goto L_0032911c;
                            }
                            // 0x003290fc
                            charge(ctx, 4);
                            lwc1(f0, sp, 0x98);
                            c_lt_s(f2, f0);
                            if (cond(ctx)) {
                                goto L_0032911c;
                            }
                            // 0x0032910c
                            charge(ctx, 4);
                            lwc1(f0, sp, 0x94);
                            c_le_s(f2, f0);
                            if (!cond(ctx)) {
                                goto L_0032911c;
                            }
                            // 0x00329128
                            charge(ctx, 1);
                            v0 = 0;
                            goto L_0032912c;
                        }
                    L_0032911c:
                        charge(ctx, 3);
                        v0 = 1;
                    L_0032912c:
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x00329134
                            charge(ctx, 14);
                            lwc1(f3, sp, 0x240);
                            sub_s(f1, f24, f23);
                            sub_s(f0, f22, f21);
                            div_s(f1, f1, f0);
                            sub_s(f0, f3, f21);
                            mul_s(f2, f0, f1);
                            div_s(f1, f22, f3);
                            mtc1(zero, f0);
                            adda_s(f0, f23);
                            madd_s(f26, f1, f2);
                            c_lt_s(f26, f30);
                            if (cond(ctx)) {
                                // 0x0032916c
                                charge(ctx, 1);
                                mov_s(f26, f30);
                            }
                            // 0x00329170
                            charge(ctx, 89);
                            div_s(f25, f29, f26);
                            lwc1(f12, s2, 28);
                            jal(ctx, 0x329188u, gen::fn_cosf_0052e6d8);
                            swc1(f0, sp, 0x88);
                            lwc1(f12, s2, 28);
                            jal(ctx, 0x329198u, gen::fn_sinf_0052e878);
                            lwc1(f2, sp, 0x90);
                            lwc1(f1, sp, 0x88);
                            mul_s(f8, f2, f1);
                            lwc1(f2, sp, 0x8C);
                            mul_s(f7, f2, f1);
                            lwc1(f1, sp, 0x90);
                            mul_s(f6, f1, f0);
                            mov_s(f1, f2);
                            mul_s(f5, f1, f0);
                            swc1(f30, sp, 0x130);
                            swc1(f30, sp, 0x134);
                            swc1(f29, sp, 0x170);
                            swc1(f30, sp, 0x174);
                            swc1(f30, sp, 0x1B0);
                            swc1(f29, sp, 0x1B4);
                            swc1(f29, sp, 0x1F0);
                            swc1(f29, sp, 0x1F4);
                            neg_s(f4, f8);
                            lwc1(f3, sp, 0x238);
                            lwc1(f2, sp, 0x240);
                            add_s(f0, f4, f5);
                            add_s(f0, f3, f0);
                            div_s(f0, f0, f2);
                            mul_s(f0, f28, f0);
                            swc1(f0, sp, 0x120);
                            neg_s(f1, f6);
                            lwc1(f0, sp, 0x23C);
                            sub_s(f9, f1, f7);
                            sub_s(f9, f0, f9);
                            div_s(f9, f9, f2);
                            mul_s(f9, f27, f9);
                            swc1(f9, sp, 0x124);
                            swc1(f26, sp, 0x128);
                            swc1(f25, sp, 0x138);
                            add_s(f9, f8, f5);
                            add_s(f9, f3, f9);
                            div_s(f9, f9, f2);
                            mul_s(f9, f28, f9);
                            swc1(f9, sp, 0x160);
                            sub_s(f9, f6, f7);
                            sub_s(f9, f0, f9);
                            div_s(f9, f9, f2);
                            mul_s(f9, f27, f9);
                            swc1(f9, sp, 0x164);
                            swc1(f26, sp, 0x168);
                            swc1(f25, sp, 0x178);
                            sub_s(f4, f4, f5);
                            add_s(f4, f3, f4);
                            div_s(f4, f4, f2);
                            mul_s(f4, f28, f4);
                            swc1(f4, sp, 0x1A0);
                            add_s(f1, f1, f7);
                            sub_s(f1, f0, f1);
                            div_s(f1, f1, f2);
                            mul_s(f1, f27, f1);
                            swc1(f1, sp, 0x1A4);
                            swc1(f26, sp, 0x1A8);
                            swc1(f25, sp, 0x1B8);
                            sub_s(f1, f8, f5);
                            add_s(f1, f3, f1);
                            div_s(f1, f1, f2);
                            mul_s(f1, f28, f1);
                            swc1(f1, sp, 0x1E0);
                            add_s(f1, f6, f7);
                            sub_s(f0, f0, f1);
                            div_s(f0, f0, f2);
                            mul_s(f0, f27, f0);
                            swc1(f0, sp, 0x1E4);
                            swc1(f26, sp, 0x1E8);
                            swc1(f25, sp, 0x1F8);
                            a0 = 4;
                            a1 = addiu(sp, 0x120);
                            a2 = a0;
                            v0 = 0x960000;
                            lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
                            jalr(ctx, 0x3292CCu, v0.u());
                        }
                    }
                }
                // 0x003292d4
                charge(ctx, 2);
                s1 = addiu(s1, 1);
                s2 = addiu(s2, 32);
            }
        } else {
            // 0x003283c4
            charge(ctx, 5);
            s1 = 0;
            sub_s(f25, f22, f21);
            sub_s(f24, f24, f23);
            for (;;) {  // while (s1 < s0)
                // 0x00328ad8
                charge(ctx, 3);
                v0 = slt(s1, s0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003283d8
                charge(ctx, 3);
                lw(a1, s2, 16);
                if (i64(a1) >= 0) {
                    // 0x003283e4
                    charge(ctx, 28);
                    lw(v0, s2, 20);
                    sw(v0, sp, 0x264);
                    v0 = addiu(sp, 0x264);
                    lw(v0, v0, 0);
                    pextlb(v0, zero, v0);
                    pextlh(v0, zero, v0);
                    qmtc2(v0, vf10, false);  // qmtc2
                    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
                    mfc1(v0, f20);
                    qmtc2(v0, vf2, false);  // qmtc2
                    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                    v0 = addiu(sp, 0x220);
                    lqc2(vf11, v0, 0);
                    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                    v0 = 0x437F0000;
                    qmtc2(v0, vf2, false);  // qmtc2
                    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                    vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                    qmfc2(v0, vf10, false);  // qmfc2
                    ppach(v0, zero, v0);
                    ppacb(v0, zero, v0);
                    sw(v0, sp, 0x25C);
                    lw(v0, sp, 0x25C);
                    sw(v0, sp, 0x26C);
                    lbu(v0, sp, 0x26F);
                    if (v0 != 0) {
                        // 0x00328454
                        charge(ctx, 27);
                        lw(a0, s3, 72);
                        a2 = addiu(sp, 0xA0);
                        jal(ctx, 0x32845Cu, gen::fn_sub_322FD0_00322fd0);
                        lw(v0, sp, 0xB0);
                        a0 = 1;
                        lw(a1, v0, 0);
                        v0 = 0x960000;
                        lw(v0, v0, 144);  // pfn_RwRenderStateSet
                        jalr(ctx, 0x328478u, v0.u());
                        lwc1(f3, s2, 24);
                        v0 = 0x42000000;
                        mtc1(v0, f2);
                        lwc1(f0, sp, 0xA8);
                        div_s(f1, f0, f2);
                        lwc1(f0, sp, 0xA0);
                        mul_s(f0, f1, f0);
                        mul_s(f29, f3, f0);
                        lwc1(f0, sp, 0xAC);
                        div_s(f1, f0, f2);
                        lwc1(f0, sp, 0xA4);
                        mul_s(f0, f1, f0);
                        mul_s(f28, f3, f0);
                        lbu(a1, sp, 0x26C);
                        if (i64(a1) < 0) {
                            // 0x003284d4
                            charge(ctx, 7);
                            v1 = srl(a1, 1);
                            v0 = a1 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x003284c0
                            charge(ctx, 5);
                            mtc1(a1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x003284f0
                        charge(ctx, 4);
                        swc1(f0, sp, 0x140);
                        lbu(a0, sp, 0x26D);
                        if (i64(a0) < 0) {
                            // 0x00328514
                            charge(ctx, 7);
                            v1 = srl(a0, 1);
                            v0 = a0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328500
                            charge(ctx, 5);
                            mtc1(a0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328530
                        charge(ctx, 4);
                        swc1(f0, sp, 0x144);
                        lbu(v1, sp, 0x26E);
                        if (i64(v1) < 0) {
                            // 0x00328554
                            charge(ctx, 7);
                            a2 = srl(v1, 1);
                            v0 = v1 & 0x1;
                            a2 = a2 | v0;
                            mtc1(a2, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328540
                            charge(ctx, 5);
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328570
                        charge(ctx, 4);
                        swc1(f0, sp, 0x148);
                        lbu(v0, sp, 0x26F);
                        if (i64(v0) < 0) {
                            // 0x00328594
                            charge(ctx, 7);
                            a3 = srl(v0, 1);
                            a2 = v0 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328580
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x003285b0
                        charge(ctx, 3);
                        swc1(f0, sp, 0x14C);
                        if (i64(a1) < 0) {
                            // 0x003285d0
                            charge(ctx, 7);
                            a3 = srl(a1, 1);
                            a2 = a1 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x003285bc
                            charge(ctx, 5);
                            mtc1(a1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x003285ec
                        charge(ctx, 3);
                        swc1(f0, sp, 0x180);
                        if (i64(a0) < 0) {
                            // 0x0032860c
                            charge(ctx, 7);
                            a3 = srl(a0, 1);
                            a2 = a0 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x003285f8
                            charge(ctx, 5);
                            mtc1(a0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328628
                        charge(ctx, 3);
                        swc1(f0, sp, 0x184);
                        if (i64(v1) < 0) {
                            // 0x00328648
                            charge(ctx, 7);
                            a3 = srl(v1, 1);
                            a2 = v1 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328634
                            charge(ctx, 5);
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328664
                        charge(ctx, 3);
                        swc1(f0, sp, 0x188);
                        if (i64(v0) < 0) {
                            // 0x00328684
                            charge(ctx, 7);
                            a3 = srl(v0, 1);
                            a2 = v0 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328670
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x003286a0
                        charge(ctx, 3);
                        swc1(f0, sp, 0x18C);
                        if (i64(a1) < 0) {
                            // 0x003286c0
                            charge(ctx, 7);
                            a3 = srl(a1, 1);
                            a2 = a1 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x003286ac
                            charge(ctx, 5);
                            mtc1(a1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x003286dc
                        charge(ctx, 3);
                        swc1(f0, sp, 0x1C0);
                        if (i64(a0) < 0) {
                            // 0x003286fc
                            charge(ctx, 7);
                            a3 = srl(a0, 1);
                            a2 = a0 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x003286e8
                            charge(ctx, 5);
                            mtc1(a0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328718
                        charge(ctx, 3);
                        swc1(f0, sp, 0x1C4);
                        if (i64(v1) < 0) {
                            // 0x00328738
                            charge(ctx, 7);
                            a3 = srl(v1, 1);
                            a2 = v1 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328724
                            charge(ctx, 5);
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328754
                        charge(ctx, 3);
                        swc1(f0, sp, 0x1C8);
                        if (i64(v0) < 0) {
                            // 0x00328774
                            charge(ctx, 7);
                            a3 = srl(v0, 1);
                            a2 = v0 & 0x1;
                            a3 = a3 | a2;
                            mtc1(a3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328760
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328790
                        charge(ctx, 3);
                        swc1(f0, sp, 0x1CC);
                        if (i64(a1) < 0) {
                            // 0x003287b0
                            charge(ctx, 7);
                            a2 = srl(a1, 1);
                            a1 = a1 & 0x1;
                            a2 = a2 | a1;
                            mtc1(a2, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x0032879c
                            charge(ctx, 5);
                            mtc1(a1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x003287cc
                        charge(ctx, 3);
                        swc1(f0, sp, 0x200);
                        if (i64(a0) < 0) {
                            // 0x003287ec
                            charge(ctx, 7);
                            a1 = srl(a0, 1);
                            a0 = a0 & 0x1;
                            a1 = a1 | a0;
                            mtc1(a1, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x003287d8
                            charge(ctx, 5);
                            mtc1(a0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328808
                        charge(ctx, 3);
                        swc1(f0, sp, 0x204);
                        if (i64(v1) < 0) {
                            // 0x00328828
                            charge(ctx, 7);
                            a0 = srl(v1, 1);
                            v1 = v1 & 0x1;
                            a0 = a0 | v1;
                            mtc1(a0, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328814
                            charge(ctx, 5);
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328844
                        charge(ctx, 3);
                        swc1(f0, sp, 0x208);
                        if (i64(v0) < 0) {
                            // 0x00328864
                            charge(ctx, 7);
                            v1 = srl(v0, 1);
                            v0 = v0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x00328850
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x00328880
                        charge(ctx, 25);
                        swc1(f0, sp, 0x20C);
                        lwc1(f0, s2, 0);
                        swc1(f0, sp, 0x248);
                        lwc1(f0, s2, 4);
                        swc1(f0, sp, 0x24C);
                        lwc1(f0, s2, 8);
                        swc1(f0, sp, 0x250);
                        jal(ctx, 0x32889Cu, gen::fn_sub_198590_00198590);  // the current camera / render context
                        a0 = addiu(sp, 0x238);
                        a1 = addiu(sp, 0x248);
                        a2 = addiu(v0, 32);
                        jal(ctx, 0x3288B0u, gen::fn_sub_4C6BE0_004c6be0);
                        lwc1(f1, sp, 0x240);
                        lwc1(f0, sp, 0x23C);
                        div_s(f3, f0, f1);
                        lwc1(f0, sp, 0x238);
                        div_s(f2, f0, f1);
                        v0 = lui(0xC000);
                        mtc1(v0, f1);
                        c_lt_s(f2, f1);
                        if (!cond(ctx)) {
                            // 0x003288e4
                            charge(ctx, 6);
                            v0 = 0x40000000;
                            mtc1(v0, f0);
                            c_le_s(f2, f0);
                            if (!cond(ctx)) {
                                goto L_00328914;
                            }
                            // 0x003288fc
                            charge(ctx, 3);
                            c_lt_s(f3, f1);
                            if (cond(ctx)) {
                                goto L_00328914;
                            }
                            // 0x00328908
                            charge(ctx, 3);
                            c_le_s(f3, f0);
                            if (!cond(ctx)) {
                                goto L_00328914;
                            }
                            // 0x00328920
                            charge(ctx, 1);
                            v0 = 0;
                            goto L_00328924;
                        }
                    L_00328914:
                        charge(ctx, 3);
                        v0 = 1;
                    L_00328924:
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x0032892c
                            charge(ctx, 12);
                            lwc1(f3, sp, 0x240);
                            sub_s(f1, f3, f21);
                            div_s(f0, f24, f25);
                            mul_s(f2, f1, f0);
                            div_s(f1, f22, f3);
                            mtc1(zero, f0);
                            adda_s(f0, f23);
                            madd_s(f26, f1, f2);
                            c_lt_s(f26, f0);
                            if (cond(ctx)) {
                                // 0x0032895c
                                charge(ctx, 1);
                                mov_s(f26, f0);
                            }
                            // 0x00328960
                            charge(ctx, 92);
                            v0 = 0x3F800000;
                            mtc1(v0, f0);
                            div_s(f27, f0, f26);
                            lwc1(f12, s2, 28);
                            jal(ctx, 0x32897Cu, gen::fn_cosf_0052e6d8);
                            mov_s(f30, f0);
                            lwc1(f12, s2, 28);
                            jal(ctx, 0x32898Cu, gen::fn_sinf_0052e878);
                            mul_s(f10, f29, f30);
                            mul_s(f9, f28, f30);
                            mul_s(f8, f29, f0);
                            mul_s(f7, f28, f0);
                            sw(zero, sp, 0x130);
                            sw(zero, sp, 0x134);
                            v0 = 0x3F800000;
                            sw(v0, sp, 0x170);
                            sw(zero, sp, 0x174);
                            sw(zero, sp, 0x1B0);
                            sw(v0, sp, 0x1B4);
                            sw(v0, sp, 0x1F0);
                            sw(v0, sp, 0x1F4);
                            neg_s(f6, f10);
                            lwc1(f5, sp, 0x238);
                            lwc1(f4, sp, 0x240);
                            add_s(f0, f6, f7);
                            add_s(f0, f5, f0);
                            div_s(f0, f0, f4);
                            v0 = 0x44200000;
                            mtc1(v0, f3);
                            mul_s(f0, f3, f0);
                            swc1(f0, sp, 0x120);
                            neg_s(f2, f8);
                            lwc1(f1, sp, 0x23C);
                            sub_s(f0, f2, f9);
                            sub_s(f0, f1, f0);
                            div_s(f11, f0, f4);
                            v0 = 0x43E00000;
                            mtc1(v0, f0);
                            mul_s(f11, f0, f11);
                            swc1(f11, sp, 0x124);
                            swc1(f26, sp, 0x128);
                            swc1(f27, sp, 0x138);
                            add_s(f11, f10, f7);
                            add_s(f11, f5, f11);
                            div_s(f11, f11, f4);
                            mul_s(f11, f3, f11);
                            swc1(f11, sp, 0x160);
                            sub_s(f11, f8, f9);
                            sub_s(f11, f1, f11);
                            div_s(f11, f11, f4);
                            mul_s(f11, f0, f11);
                            swc1(f11, sp, 0x164);
                            swc1(f26, sp, 0x168);
                            swc1(f27, sp, 0x178);
                            sub_s(f6, f6, f7);
                            add_s(f6, f5, f6);
                            div_s(f6, f6, f4);
                            mul_s(f6, f3, f6);
                            swc1(f6, sp, 0x1A0);
                            add_s(f2, f2, f9);
                            sub_s(f2, f1, f2);
                            div_s(f2, f2, f4);
                            mul_s(f2, f0, f2);
                            swc1(f2, sp, 0x1A4);
                            swc1(f26, sp, 0x1A8);
                            swc1(f27, sp, 0x1B8);
                            sub_s(f2, f10, f7);
                            add_s(f2, f5, f2);
                            div_s(f2, f2, f4);
                            mul_s(f2, f3, f2);
                            swc1(f2, sp, 0x1E0);
                            add_s(f2, f8, f9);
                            sub_s(f1, f1, f2);
                            div_s(f1, f1, f4);
                            mul_s(f0, f0, f1);
                            swc1(f0, sp, 0x1E4);
                            swc1(f26, sp, 0x1E8);
                            swc1(f27, sp, 0x1F8);
                            a0 = 4;
                            a1 = addiu(sp, 0x120);
                            a2 = a0;
                            v0 = 0x960000;
                            lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
                            jalr(ctx, 0x328AC8u, v0.u());
                        }
                    }
                }
                // 0x00328ad0
                charge(ctx, 2);
                s1 = addiu(s1, 1);
                s2 = addiu(s2, 32);
            }
            // 0x00328ae4
            charge(ctx, 2);
        }
    } else {
        // 0x003283ac
        charge(ctx, 2);
    }
    // 0x003292e8
    charge(ctx, 26);
    a0 = 1;
    a1 = 0;
    v0 = 0x960000;
    lw(v0, v0, 144);  // pfn_RwRenderStateSet
    jalr(ctx, 0x3292F8u, v0.u());
    ld(ra, sp, 0x70);
    lq(s3, sp, 0x60);
    lq(s2, sp, 0x50);
    lq(s1, sp, 0x40);
    lq(s0, sp, 0x30);
    lwc1(f31, sp, 0x2C);
    lwc1(f30, sp, 0x28);
    lwc1(f29, sp, 0x24);
    lwc1(f28, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x270);
}

// 0x00329800 sub_329800 -- 144 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fxCameraSpace](pos*, out) a point in the camera's space (the camera frame's matrix, sub_4CB2F0; VU0).
void sub_329800(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00329800
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    jal(ctx, 0x329818u, gen::fn_sub_198590_00198590);  // the current camera / render context
    lw(a0, v0, 4);
    jal(ctx, 0x329824u, gen::fn_sub_4CB2F0_004cb2f0);
    lwc1(f0, v0, 48);
    swc1(f0, sp, 0x30);
    lwc1(f0, v0, 52);
    swc1(f0, sp, 0x34);
    lwc1(f0, v0, 56);
    swc1(f0, sp, 0x38);
    sw(zero, sp, 0x3C);
    lqc2(vf10, s1, 0);
    v1 = addiu(sp, 0x30);
    lqc2(vf11, v1, 0);
    vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
    vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
    vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
    vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
    vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
    vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
    vwaitq(ctx);
    vmulq(0xE, vf10, vf10);  // vmulq.xyz
    sqc2(vf10, s0, 0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003299B0 sub_3299B0 -- 176 bytes; frame 0x40: ra sp+0x0
// [fxToScreen](pos*) -> vf10 projects a point to the 640 x 448 screen through the camera (sub_4C6BE0).
void sub_3299B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    Vf vf10{ctx, 10};
    // 0x003299b0
    enter(ctx, 44);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x0);
    v0 = 0x6A0000;
    v0 = addiu(v0, -15152);  // &0x69C4D0
    sqc2(vf10, v0, 0);  // 0x69C4D0
    v0 = 0x6A0000;
    lwc1(f0, v0, -15152);  // 0x69C4D0
    swc1(f0, sp, 0x20);
    v0 = 0x6A0000;
    lwc1(f0, v0, -15148);  // 0x69C4D4
    swc1(f0, sp, 0x24);
    v0 = 0x6A0000;
    lwc1(f0, v0, -15144);  // 0x69C4D8
    swc1(f0, sp, 0x28);
    jal(ctx, 0x3299E8u, gen::fn_sub_198590_00198590);  // the current camera / render context
    a2 = addiu(v0, 32);
    a0 = addiu(sp, 0x30);
    a1 = addiu(sp, 0x20);
    jal(ctx, 0x3299FCu, gen::fn_sub_4C6BE0_004c6be0);
    lwc1(f0, sp, 0x38);
    lwc1(f1, sp, 0x30);
    div_s(f2, f1, f0);
    v0 = 0x44200000;
    mtc1(v0, f1);
    mul_s(f1, f1, f2);
    swc1(f1, sp, 0x10);
    lwc1(f1, sp, 0x34);
    div_s(f2, f1, f0);
    v0 = 0x43E00000;
    mtc1(v0, f1);
    mul_s(f1, f1, f2);
    swc1(f1, sp, 0x14);
    sw(zero, sp, 0x18);
    sw(zero, sp, 0x1C);
    v0 = addiu(sp, 0x10);
    lqc2(vf10, v0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00329D60 sub_329D60 -- 364 bytes; frame 0x70
// [fxCubic](p[4], t $f12, out) a cubic curve point from four control vectors (VU0; t, t^2, t^3).
void sub_329D60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12};
    Vf vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12};
    // 0x00329d60
    enter(ctx, 91);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    mul_s(f5, f12, f12);
    mul_s(f4, f5, f12);
    v1 = 0x3F000000;
    sw(v1, sp, 0x40);
    sw(v1, sp, 0x44);
    sw(v1, sp, 0x48);
    lqc2(vf10, a0, 16);
    lqc2(vf11, a0, 0);
    vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
    vmove(0xF, vf12, vf10);  // vmove.xyzw
    lqc2(vf10, a0, 32);
    lqc2(vf11, a0, 16);
    vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
    vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
    v1 = addiu(sp, 0x40);
    lqc2(vf11, v1, 0);
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    a2 = addiu(sp, 0x60);
    sqc2(vf10, a2, 0);
    lqc2(vf10, a0, 32);
    lqc2(vf11, a0, 16);
    vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
    vmove(0xF, vf12, vf10);  // vmove.xyzw
    lqc2(vf10, a0, 48);
    lqc2(vf11, a0, 32);
    vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
    vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
    lqc2(vf11, v1, 0);
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    a1 = addiu(sp, 0x50);
    sqc2(vf10, a1, 0);
    v1 = 0x40400000;
    mtc1(v1, f0);
    mul_s(f3, f0, f5);
    v1 = 0x40000000;
    mtc1(v1, f2);
    mul_s(f0, f2, f4);
    sub_s(f1, f0, f3);
    v1 = 0x3F800000;
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0x0);
    swc1(f0, sp, 0x4);
    swc1(f0, sp, 0x8);
    mtc1(zero, f1);
    adda_s(f1, f4);
    msub_s(f0, f2, f5);
    add_s(f0, f12, f0);
    swc1(f0, sp, 0x10);
    swc1(f0, sp, 0x14);
    swc1(f0, sp, 0x18);
    sub_s(f0, f4, f5);
    swc1(f0, sp, 0x20);
    swc1(f0, sp, 0x24);
    swc1(f0, sp, 0x28);
    v1 = lui(0xC000);
    mtc1(v1, f0);
    adda_s(f1, f3);
    madd_s(f0, f0, f4);
    swc1(f0, sp, 0x30);
    swc1(f0, sp, 0x34);
    swc1(f0, sp, 0x38);
    v1 = addiu(sp, 0x0);
    lqc2(vf10, v1, 0);
    lqc2(vf11, a0, 16);
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    vmove(0xF, vf12, vf10);  // vmove.xyzw
    v1 = addiu(sp, 0x10);
    lqc2(vf10, v1, 0);
    lqc2(vf11, a2, 0);
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    vadd(0xF, vf12, vf12, vf10);  // vadd.xyzw
    v1 = addiu(sp, 0x20);
    lqc2(vf10, v1, 0);
    lqc2(vf11, a1, 0);
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    vadd(0xF, vf12, vf12, vf10);  // vadd.xyzw
    v1 = addiu(sp, 0x30);
    lqc2(vf10, v1, 0);
    lqc2(vf11, a0, 32);
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
    sp = addiu(sp, 0x70);
}

// 0x00329ED0 sub_329ED0 -- 584 bytes; frame 0x10
// [fxQuatFromMatrix](m) the quaternion of a rotation matrix (the trace method; the largest diagonal element
// when the trace + 1 < 1).
void sub_329ED0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    Vf vf10{ctx, 10};
    // 0x00329ed0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    lwc1(f3, a0, 20);
    lwc1(f2, a0, 0);
    lwc1(f4, a0, 40);
    v1 = 0x3F800000;
    mtc1(v1, f1);
    add_s(f0, f2, f3);
    add_s(f0, f4, f0);
    add_s(f0, f1, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x00329f80
        charge(ctx, 4);
        c_le_s(f2, f3);
        v1 = 1;
        if (cond(ctx)) {
            // 0x00329f90
            charge(ctx, 1);
            v1 = 0;
        }
        // 0x00329f94
        charge(ctx, 10);
        v1 = v1 ^ 0x1;
        a2 = v1 & 0xFF;
        v1 = sll(a2, 4);
        a1 = addu(a0, v1);
        v1 = sll(a2, 2);
        v1 = addu(a1, v1);
        lwc1(f0, v1, 0);
        c_le_s(f4, f0);
        if (!cond(ctx)) {
            // 0x00329fbc
            charge(ctx, 1);
            a2 = 2;
        }
        // 0x00329fc0
        charge(ctx, 41);
        a3 = a2 & 0xFF;
        v1 = addiu(a3, 1);
        a2 = 3;
        div(v1, a2);
        mfhi(v1);
        a1 = v1 & 0xFF;
        v1 = addiu(a1, 1);
        div(v1, a2);
        mfhi(v1);
        t2 = v1 & 0xFF;
        v1 = sll(a1, 2);
        a1 = sll(a1, 4);
        t1 = addu(a0, a1);
        a1 = addu(t1, v1);
        lwc1(f1, a1, 0);
        t0 = sll(a3, 2);
        a1 = sll(a3, 4);
        a3 = addu(a0, a1);
        a1 = addu(a3, t0);
        lwc1(f0, a1, 0);
        sub_s(f1, f0, f1);
        a2 = sll(t2, 2);
        a1 = sll(t2, 4);
        a1 = addu(a0, a1);
        a0 = addu(a1, a2);
        lwc1(f0, a0, 0);
        sub_s(f0, f1, f0);
        a0 = 0x3F800000;
        mtc1(a0, f1);
        add_s(f0, f1, f0);
        sqrt_s(f2, f0);
        a0 = 0x40000000;
        mtc1(a0, f0);
        mul_s(f2, f0, f2);
        mtc1(zero, f0);
        c_eq_s(f0, f2);
        if (cond(ctx)) {
            // 0x0032a0e8
            charge(ctx, 7);
            a0 = addu(t0, sp);
            swc1(f1, a0, 0);
            v1 = addu(v1, sp);
            swc1(f0, v1, 0);
            v1 = addu(a2, sp);
            swc1(f0, v1, 0);
            swc1(f0, sp, 0xC);
        } else {
            // 0x0032a064
            charge(ctx, 33);
            a0 = 0x40800000;
            mtc1(a0, f0);
            div_s(f0, f2, f0);
            a0 = addu(t0, sp);
            swc1(f0, a0, 0);
            a0 = addu(a3, v1);
            lwc1(f1, a0, 0);
            a0 = addu(t1, t0);
            lwc1(f0, a0, 0);
            add_s(f0, f1, f0);
            div_s(f0, f0, f2);
            a0 = addu(v1, sp);
            swc1(f0, a0, 0);
            a0 = addu(a3, a2);
            lwc1(f1, a0, 0);
            a0 = addu(a1, t0);
            lwc1(f0, a0, 0);
            add_s(f0, f1, f0);
            div_s(f0, f0, f2);
            a0 = addu(a2, sp);
            swc1(f0, a0, 0);
            a0 = addu(t1, a2);
            lwc1(f1, a0, 0);
            v1 = addu(a1, v1);
            lwc1(f0, v1, 0);
            sub_s(f0, f1, f0);
            div_s(f0, f0, f2);
            neg_s(f0, f0);
            swc1(f0, sp, 0xC);
        }
    } else {
        // 0x00329f00
        charge(ctx, 32);
        sqrt_s(f1, f0);
        v1 = 0x40000000;
        mtc1(v1, f0);
        mul_s(f2, f0, f1);
        v1 = 0x40800000;
        mtc1(v1, f0);
        div_s(f0, f2, f0);
        neg_s(f0, f0);
        swc1(f0, sp, 0xC);
        lwc1(f1, a0, 24);
        lwc1(f0, a0, 36);
        sub_s(f0, f1, f0);
        div_s(f0, f0, f2);
        swc1(f0, sp, 0x0);
        lwc1(f1, a0, 32);
        lwc1(f0, a0, 8);
        sub_s(f0, f1, f0);
        div_s(f0, f0, f2);
        swc1(f0, sp, 0x4);
        lwc1(f1, a0, 4);
        lwc1(f0, a0, 16);
        sub_s(f0, f1, f0);
        div_s(f0, f0, f2);
        swc1(f0, sp, 0x8);
    }
    // 0x0032a104 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v1 = addiu(sp, 0x0);
    lqc2(vf10, v1, 0);
    sp = addiu(sp, 0x10);
}

// 0x0032A120 sub_32A120 -- 1044 bytes; frame 0x10
// [fxColourTrack](track, alpha*, t, length) -> RGBA samples a colour track: kind 0 one colour, kind 1
// two keys (the middle at +16 x length), kind 2 three (+16, +24); RGB interpolated, alpha = *alpha << 24; length 0 ->
// the first colour with that alpha.
void sub_32A120(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x0032a120
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    if (a3 != 0) {
        // 0x0032a14c
        charge(ctx, 7);
        mtc1(a3, f0);
        cvt_s_w(f0, f0);
        lbu(v1, a0, 0);
        v0 = 2;
        if (v1 == v0) {
            // 0x0032a248
            charge(ctx, 8);
            lwc1(f1, a0, 16);
            mul_s(f1, f1, f0);
            cvt_w_s(f1, f1);
            mfc1(t0, f1);
            at = slt(a2, t0);
            if (at == 0) {
                // 0x0032a2a0
                charge(ctx, 8);
                lwc1(f1, a0, 24);
                mul_s(f1, f1, f0);
                cvt_w_s(f1, f1);
                mfc1(v1, f1);
                at = slt(a2, v1);
                if (at == 0) {
                    // 0x0032a300
                    charge(ctx, 16);
                    lw(t1, a0, 20);
                    lw(a0, a0, 8);
                    v0 = subu(a3, v1);
                    mtc1(v0, f1);
                    cvt_s_w(f2, f1);
                    v0 = subu(a2, v1);
                    mtc1(v0, f1);
                    cvt_s_w(f1, f1);
                    div_s(f3, f1, f2);
                } else {
                    // 0x0032a2c0
                    charge(ctx, 16);
                    lw(t1, a0, 12);
                    lw(a0, a0, 20);
                    v0 = subu(v1, t0);
                    mtc1(v0, f1);
                    cvt_s_w(f2, f1);
                    v0 = subu(a2, t0);
                    mtc1(v0, f1);
                    cvt_s_w(f1, f1);
                    div_s(f3, f1, f2);
                }
            } else {
                // 0x0032a268
                charge(ctx, 14);
                lw(t1, a0, 4);
                lw(a0, a0, 12);
                mtc1(a2, f1);
                cvt_s_w(f2, f1);
                mtc1(t0, f1);
                cvt_s_w(f1, f1);
                div_s(f3, f2, f1);
            }
        } else {
            // 0x0032a168
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x0032a1b0
                charge(ctx, 8);
                lwc1(f1, a0, 16);
                mul_s(f1, f1, f0);
                cvt_w_s(f1, f1);
                mfc1(v1, f1);
                at = slt(a2, v1);
                if (at == 0) {
                    // 0x0032a208
                    charge(ctx, 16);
                    lw(t1, a0, 12);
                    lw(a0, a0, 8);
                    v0 = subu(a3, v1);
                    mtc1(v0, f1);
                    cvt_s_w(f2, f1);
                    v0 = subu(a2, v1);
                    mtc1(v0, f1);
                    cvt_s_w(f1, f1);
                    div_s(f3, f1, f2);
                } else {
                    // 0x0032a1d0
                    charge(ctx, 14);
                    lw(t1, a0, 4);
                    lw(a0, a0, 12);
                    mtc1(a2, f1);
                    cvt_s_w(f2, f1);
                    mtc1(v1, f1);
                    cvt_s_w(f1, f1);
                    div_s(f3, f2, f1);
                }
            } else {
                // 0x0032a174
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x0032a184
                    charge(ctx, 11);
                    lw(t1, a0, 4);
                    lw(a0, a0, 8);
                    mtc1(a2, f1);
                    cvt_s_w(f1, f1);
                    div_s(f3, f1, f0);
                } else {
                    // 0x0032a17c
                    charge(ctx, 2);
                    // 0x0032a340
                    charge(ctx, 3);
                    lw(t1, a0, 4);
                    lw(a0, a0, 8);
                    mtc1(zero, f3);
                }
            }
        }
        // 0x0032a34c
        charge(ctx, 57);
        sw(a0, sp, 0xC);
        v0 = addiu(sp, 0xC);
        lwc1(f1, gp, -32420);  // 0x7CAE4C = 0.00392157f
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f1);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        vmove(0xF, vf11, vf10);  // vmove.xyzw
        sw(t1, sp, 0x8);
        v0 = addiu(sp, 0x8);
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f1);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v0 = 0x3F800000;
        mtc1(v0, f2);
        sub_s(f1, f2, f3);
        mfc1(v0, f1);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        mfc1(v0, f3);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
        v0 = 0x437F0000;
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
        qmfc2(v0, vf10, false);  // qmfc2
        ppach(v0, zero, v0);
        ppacb(v0, zero, v0);
        sw(v0, sp, 0x4);
        lw(a0, sp, 0x4);
        lwc1(f1, a1, 8);
        mul_s(f1, f1, f0);
        cvt_w_s(f1, f1);
        mfc1(v0, f1);
        lwc1(f1, a1, 12);
        mul_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        at = slt(a2, v0);
        if (at == 0) {
            // 0x0032a460
            charge(ctx, 3);
            at = slt(v1, a2);
            if (at != 0) {
                // 0x0032a46c
                charge(ctx, 12);
                v0 = subu(a3, a2);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = subu(a3, v1);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                div_s(f2, f1, f0);
            }
        } else {
            // 0x0032a430
            charge(ctx, 12);
            mtc1(a2, f0);
            cvt_s_w(f1, f0);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            div_s(f2, f1, f0);
        }
        // 0x0032a49c
        charge(ctx, 3);
        lw(v0, a1, 0);
        if (i64(v0) < 0) {
            // 0x0032a4bc
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x0032a4a8
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
        }
        // 0x0032a4d8
        charge(ctx, 7);
        mul_s(f1, f0, f2);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0032a504
            charge(ctx, 5);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
        } else {
            // 0x0032a4f4
            charge(ctx, 4);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
        }
        // 0x0032a518
        charge(ctx, 4);
        v1 = sll(v1, 24);
        v0 = dsll32(a0, 8);
        v0 = dsrl32(v0, 8);
        v0 = v0 | v1;
    } else {
        // 0x0032a12c
        charge(ctx, 8);
        lw(v0, a0, 4);
        v1 = dsll32(v0, 8);
        v1 = dsrl32(v1, 8);
        lw(v0, a1, 0);
        v0 = sll(v0, 24);
        v0 = v1 | v0;
    }
    // 0x0032a528 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sp = addiu(sp, 0x10);
}

// 0x0032B990 sub_32B990 -- 152 bytes; leaf frame (no stack)
// [fxPsysScaleA](psys, s $f12) a particle-system type's scale slot: live parameters = base x s for its
// size fields (+100, +104, +116 / +124 / +132, +200, +204, +212, +216, +224).
void sub_32B990(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x0032b990
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(a2, a0, 32);
    lw(a1, a0, 36);
    lwc1(f0, a1, 100);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 100);
    lwc1(f0, a1, 104);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 104);
    a3 = 0;
    for (;;) {
        // 0x0032b9d8
        charge(ctx, 3);
        v1 = sltiu(a3, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0032b9bc
        charge(ctx, 7);
        a0 = sll(a3, 3);
        v1 = addu(a1, a0);
        lwc1(f0, v1, 116);
        mul_s(f0, f0, f12);
        v1 = addu(a2, a0);
        swc1(f0, v1, 116);
        a3 = addiu(a3, 1);
    }
    // 0x0032b9e4
    charge(ctx, 17);
    lwc1(f0, a1, 200);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 200);
    lwc1(f0, a1, 204);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 204);
    lwc1(f0, a1, 212);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 212);
    lwc1(f0, a1, 216);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 216);
    lwc1(f0, a1, 224);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 224);
}

// 0x0032C2B0 sub_32C2B0 -- 140 bytes; leaf frame (no stack)
// [fxPsysScaleB](psys, s $f12) the same for another type's fields.
void sub_32C2B0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x0032c2b0
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(a2, a0, 32);
    lw(a1, a0, 36);
    lwc1(f0, a1, 100);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 100);
    lwc1(f0, a1, 104);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 104);
    a3 = 0;
    for (;;) {
        // 0x0032c2f8
        charge(ctx, 3);
        v1 = sltiu(a3, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0032c2dc
        charge(ctx, 7);
        a0 = sll(a3, 3);
        v1 = addu(a1, a0);
        lwc1(f0, v1, 116);
        mul_s(f0, f0, f12);
        v1 = addu(a2, a0);
        swc1(f0, v1, 116);
        a3 = addiu(a3, 1);
    }
    // 0x0032c304
    charge(ctx, 14);
    lwc1(f0, a1, 200);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 200);
    lwc1(f0, a1, 208);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 208);
    lwc1(f0, a1, 216);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 216);
    lwc1(f0, a1, 220);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 220);
}

// 0x0032CD70 sub_32CD70 -- 152 bytes; leaf frame (no stack)
// [fxPsysScaleC](psys, s $f12) the same for another type's fields.
void sub_32CD70(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x0032cd70
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(a2, a0, 32);
    lw(a1, a0, 36);
    lwc1(f0, a1, 100);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 100);
    lwc1(f0, a1, 104);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 104);
    a3 = 0;
    for (;;) {
        // 0x0032cdb8
        charge(ctx, 3);
        v1 = sltiu(a3, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0032cd9c
        charge(ctx, 7);
        a0 = sll(a3, 3);
        v1 = addu(a1, a0);
        lwc1(f0, v1, 116);
        mul_s(f0, f0, f12);
        v1 = addu(a2, a0);
        swc1(f0, v1, 116);
        a3 = addiu(a3, 1);
    }
    // 0x0032cdc4
    charge(ctx, 17);
    lwc1(f0, a1, 200);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 200);
    lwc1(f0, a1, 204);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 204);
    lwc1(f0, a1, 212);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 212);
    lwc1(f0, a1, 228);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 228);
    lwc1(f0, a1, 240);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 240);
}

// 0x0032D7C0 sub_32D7C0 -- 128 bytes; leaf frame (no stack)
// [fxPsysScaleD](psys, s $f12) the same for another type's fields.
void sub_32D7C0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x0032d7c0
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(a2, a0, 32);
    lw(a1, a0, 36);
    lwc1(f0, a1, 100);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 100);
    lwc1(f0, a1, 104);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 104);
    a3 = 0;
    for (;;) {
        // 0x0032d808
        charge(ctx, 3);
        v1 = sltiu(a3, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0032d7ec
        charge(ctx, 7);
        a0 = sll(a3, 3);
        v1 = addu(a1, a0);
        lwc1(f0, v1, 116);
        mul_s(f0, f0, f12);
        v1 = addu(a2, a0);
        swc1(f0, v1, 116);
        a3 = addiu(a3, 1);
    }
    // 0x0032d814
    charge(ctx, 11);
    lwc1(f0, a1, 200);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 200);
    lwc1(f0, a1, 208);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 208);
    lwc1(f0, a1, 228);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 228);
}

// 0x0032E110 sub_32E110 -- 140 bytes; leaf frame (no stack)
// [fxPsysScaleE](psys, s $f12) the same for another type's fields.
void sub_32E110(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x0032e110
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(a2, a0, 32);
    lw(a1, a0, 36);
    lwc1(f0, a1, 100);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 100);
    lwc1(f0, a1, 104);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 104);
    a3 = 0;
    for (;;) {
        // 0x0032e158
        charge(ctx, 3);
        v1 = sltiu(a3, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0032e13c
        charge(ctx, 7);
        a0 = sll(a3, 3);
        v1 = addu(a1, a0);
        lwc1(f0, v1, 116);
        mul_s(f0, f0, f12);
        v1 = addu(a2, a0);
        swc1(f0, v1, 116);
        a3 = addiu(a3, 1);
    }
    // 0x0032e164
    charge(ctx, 14);
    lwc1(f0, a1, 200);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 200);
    lwc1(f0, a1, 216);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 216);
    lwc1(f0, a1, 224);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 224);
    lwc1(f0, a1, 228);
    mul_s(f0, f0, f12);
    swc1(f0, a2, 228);
}

}  // namespace p3fes::game
