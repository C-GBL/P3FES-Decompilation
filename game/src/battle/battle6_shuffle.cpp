// The battle code, sixth pass (slice battle6; docs/ANALYSIS/21_battle.md, game/include/p3fes/game/battle6.h for the
// layouts): Shuffle Time -- its cameras (sfl_camera.c), the pose nodes they and the cards animate with (gc_pose.c),
// the cards' update and shuffle (sfl_card.c), the card cursor (sfl_cursor.c), the persona-select banner (sfl_psel2.c)
// and the persona status (sfl_persona.c). The bodies are p3fes_handgen's (frame, spills, $ra links, every register,
// cycle charges, check points); this file names their offsets (battle3.h's b3::, battle4.h's b4::, battle5.h's b5::
// records reused, this slice's in b6::) and gives each function its role -- proposed names in brackets (ADR-0009),
// symbols in code are functions.json's. Still-recompiled callees are reached through their gen:: entry points (the
// relaxed callee rule).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/battle6.h"

namespace p3fes::recomp_gen {
void fn_RpSkyRenderStateSet_004d7f60(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_fclMisc_CreatePsStatusTasks_003c9850(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_1749A0_001749a0(p3fes::EEContext&);
void fn_sub_176680_00176680(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_20AC90_0020ac90(p3fes::EEContext&);
void fn_sub_20C400_0020c400(p3fes::EEContext&);
void fn_sub_20C500_0020c500(p3fes::EEContext&);
void fn_sub_20C660_0020c660(p3fes::EEContext&);
void fn_sub_20CC80_0020cc80(p3fes::EEContext&);
void fn_sub_20D770_0020d770(p3fes::EEContext&);
void fn_sub_20E510_0020e510(p3fes::EEContext&);
void fn_sub_20E590_0020e590(p3fes::EEContext&);
void fn_sub_20EC50_0020ec50(p3fes::EEContext&);
void fn_sub_21A120_0021a120(p3fes::EEContext&);
void fn_sub_21CCA0_0021cca0(p3fes::EEContext&);
void fn_sub_21D3B0_0021d3b0(p3fes::EEContext&);
void fn_sub_21D890_0021d890(p3fes::EEContext&);
void fn_sub_21D8E0_0021d8e0(p3fes::EEContext&);
void fn_sub_21D950_0021d950(p3fes::EEContext&);
void fn_sub_21EA00_0021ea00(p3fes::EEContext&);
void fn_sub_21EAC0_0021eac0(p3fes::EEContext&);
void fn_sub_21EB80_0021eb80(p3fes::EEContext&);
void fn_sub_24D160_0024d160(p3fes::EEContext&);
void fn_sub_24D1C0_0024d1c0(p3fes::EEContext&);
void fn_sub_24D280_0024d280(p3fes::EEContext&);
void fn_sub_24D2E0_0024d2e0(p3fes::EEContext&);
void fn_sub_24D3B0_0024d3b0(p3fes::EEContext&);
void fn_sub_24D430_0024d430(p3fes::EEContext&);
void fn_sub_24D4C0_0024d4c0(p3fes::EEContext&);
void fn_sub_24D5E0_0024d5e0(p3fes::EEContext&);
void fn_sub_24D7D0_0024d7d0(p3fes::EEContext&);
void fn_sub_24D8D0_0024d8d0(p3fes::EEContext&);
void fn_sub_24D940_0024d940(p3fes::EEContext&);
void fn_sub_24D9A0_0024d9a0(p3fes::EEContext&);
void fn_sub_24DA20_0024da20(p3fes::EEContext&);
void fn_sub_24DA60_0024da60(p3fes::EEContext&);
void fn_sub_24DB90_0024db90(p3fes::EEContext&);
void fn_sub_24DC10_0024dc10(p3fes::EEContext&);
void fn_sub_24DC90_0024dc90(p3fes::EEContext&);
void fn_sub_24F090_0024f090(p3fes::EEContext&);
void fn_sub_24F210_0024f210(p3fes::EEContext&);
void fn_sub_24F2C0_0024f2c0(p3fes::EEContext&);
void fn_sub_24F350_0024f350(p3fes::EEContext&);
void fn_sub_24F410_0024f410(p3fes::EEContext&);
void fn_sub_24F780_0024f780(p3fes::EEContext&);
void fn_sub_24F7F0_0024f7f0(p3fes::EEContext&);
void fn_sub_24F960_0024f960(p3fes::EEContext&);
void fn_sub_24F9F0_0024f9f0(p3fes::EEContext&);
void fn_sub_24FAA0_0024faa0(p3fes::EEContext&);
void fn_sub_24FBA0_0024fba0(p3fes::EEContext&);
void fn_sub_24FC40_0024fc40(p3fes::EEContext&);
void fn_sub_24FD10_0024fd10(p3fes::EEContext&);
void fn_sub_24FD20_0024fd20(p3fes::EEContext&);
void fn_sub_24FD40_0024fd40(p3fes::EEContext&);
void fn_sub_24FD80_0024fd80(p3fes::EEContext&);
void fn_sub_24FDC0_0024fdc0(p3fes::EEContext&);
void fn_sub_24FE20_0024fe20(p3fes::EEContext&);
void fn_sub_24FE40_0024fe40(p3fes::EEContext&);
void fn_sub_24FF10_0024ff10(p3fes::EEContext&);
void fn_sub_250280_00250280(p3fes::EEContext&);
void fn_sub_2503F0_002503f0(p3fes::EEContext&);
void fn_sub_250480_00250480(p3fes::EEContext&);
void fn_sub_250500_00250500(p3fes::EEContext&);
void fn_sub_2505B0_002505b0(p3fes::EEContext&);
void fn_sub_2508C0_002508c0(p3fes::EEContext&);
void fn_sub_250A30_00250a30(p3fes::EEContext&);
void fn_sub_250B90_00250b90(p3fes::EEContext&);
void fn_sub_250BE0_00250be0(p3fes::EEContext&);
void fn_sub_250C70_00250c70(p3fes::EEContext&);
void fn_sub_250CF0_00250cf0(p3fes::EEContext&);
void fn_sub_250E70_00250e70(p3fes::EEContext&);
void fn_sub_250EF0_00250ef0(p3fes::EEContext&);
void fn_sub_250F80_00250f80(p3fes::EEContext&);
void fn_sub_251010_00251010(p3fes::EEContext&);
void fn_sub_251030_00251030(p3fes::EEContext&);
void fn_sub_253A40_00253a40(p3fes::EEContext&);
void fn_sub_255440_00255440(p3fes::EEContext&);
void fn_sub_2554F0_002554f0(p3fes::EEContext&);
void fn_sub_2564C0_002564c0(p3fes::EEContext&);
void fn_sub_256F20_00256f20(p3fes::EEContext&);
void fn_sub_256FA0_00256fa0(p3fes::EEContext&);
void fn_sub_257D00_00257d00(p3fes::EEContext&);
void fn_sub_257D90_00257d90(p3fes::EEContext&);
void fn_sub_258540_00258540(p3fes::EEContext&);
void fn_sub_258B40_00258b40(p3fes::EEContext&);
void fn_sub_258F80_00258f80(p3fes::EEContext&);
void fn_sub_259190_00259190(p3fes::EEContext&);
void fn_sub_25A130_0025a130(p3fes::EEContext&);
void fn_sub_25A440_0025a440(p3fes::EEContext&);
void fn_sub_25A7D0_0025a7d0(p3fes::EEContext&);
void fn_sub_25AAD0_0025aad0(p3fes::EEContext&);
void fn_sub_25B300_0025b300(p3fes::EEContext&);
void fn_sub_25B3B0_0025b3b0(p3fes::EEContext&);
void fn_sub_260A50_00260a50(p3fes::EEContext&);
void fn_sub_260C20_00260c20(p3fes::EEContext&);
void fn_sub_261480_00261480(p3fes::EEContext&);
void fn_sub_27BC00_0027bc00(p3fes::EEContext&);
void fn_sub_27BD10_0027bd10(p3fes::EEContext&);
void fn_sub_27BDF0_0027bdf0(p3fes::EEContext&);
void fn_sub_27BF60_0027bf60(p3fes::EEContext&);
void fn_sub_27BFB0_0027bfb0(p3fes::EEContext&);
void fn_sub_34FD30_0034fd30(p3fes::EEContext&);
void fn_sub_34FD70_0034fd70(p3fes::EEContext&);
void fn_sub_34FDF0_0034fdf0(p3fes::EEContext&);
void fn_sub_34FE30_0034fe30(p3fes::EEContext&);
void fn_sub_34FF70_0034ff70(p3fes::EEContext&);
void fn_sub_34FF90_0034ff90(p3fes::EEContext&);
void fn_sub_3C9B00_003c9b00(p3fes::EEContext&);
void fn_sub_3C9CD0_003c9cd0(p3fes::EEContext&);
void fn_sub_3C9D00_003c9d00(p3fes::EEContext&);
void fn_sub_3C9E00_003c9e00(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
void fn_sub_4BDCB0_004bdcb0(p3fes::EEContext&);
void fn_sub_4BDDE0_004bdde0(p3fes::EEContext&);
void fn_sub_4C3880_004c3880(p3fes::EEContext&);
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4CB750_004cb750(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b3;  // the record offsets and $gp slots of battle3.h
using namespace b4;  // battle4.h's additions
using namespace b5;  // battle5.h's additions
using namespace b6;  // this slice's additions (battle6.h)

// 0x0024D160 sub_24D160 -- 92 bytes; frame 0x10: ra sp+0x0
// [sflCameraTerm] Closes the Shuffle Time camera work (K_Assert lines 59 / 78) and clears its $gp slot 0x7CE33C.
void sub_24D160(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024d160
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpSflCamera);  // the Shuffle Time cameras (sfl_camera.c) 0x7CE33C
    if (v1 == 0) {
        // 0x0024d174
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 59;
        jal(ctx, 0x24D180u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024d188
    charge(ctx, 3);
    lw(v1, gp, kGpSflCamera);  // the Shuffle Time cameras (sfl_camera.c) 0x7CE33C
    if (v1 == 0) {
        // 0x0024d194
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 78;
        jal(ctx, 0x24D1A0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024d1a8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sw(zero, gp, kGpSflCamera);  // the Shuffle Time cameras (sfl_camera.c) 0x7CE33C
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0024D1C0 sub_24D1C0 -- 188 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflCameraUpdate] Per-frame update of the Shuffle Time camera work (K_Assert lines 59 / 88: not inside a draw,
// *0x960070 clear): while active (flag 1) with a camera picked (flag 2) it finds the picked camera record (+12,
// sflCameraFind), steps it (sflCameraStep) and copies its rotation and position into the RW camera (sflCameraApply).
void sub_24D1C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024d1c0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpSflCamera);  // the Shuffle Time cameras (sfl_camera.c) 0x7CE33C
    if (v1 == 0) {
        // 0x0024d1dc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 59;
        jal(ctx, 0x24D1E8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024d1f0
    charge(ctx, 5);
    lw(s0, gp, kGpSflCamera);  // the Shuffle Time cameras (sfl_camera.c) 0x7CE33C
    v1 = 0x960000;
    lw(v1, v1, 112);  // 0x960070
    if (v1 != 0) {
        // 0x0024d204
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 88;
        jal(ctx, 0x24D210u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024d218
    charge(ctx, 5);
    lw(v1, s0, sflcam::kFlags);
    a0 = nor(v1, 0);
    v1 = a0 & 0x1;
    if (v1 == 0) {
        // 0x0024d22c
        charge(ctx, 3);
        v1 = a0 & 0x2;
        if (v1 == 0) {
            // 0x0024d238
            charge(ctx, 11);
            lhu(a0, s0, sflcam::kPicked);
            jal(ctx, 0x24D23Cu, gen::fn_sub_24D430_0024d430);
            s1 = v0;
            a0 = s1;
            jal(ctx, 0x24D24Cu, gen::fn_sub_24D5E0_0024d5e0);
            lw(a0, s0, sflcam::kRwCamera);
            a1 = s1;
            jal(ctx, 0x24D25Cu, gen::fn_sub_24D7D0_0024d7d0);
        }
    }
    // 0x0024d264 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0024D280 sub_24D280 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflCameraSetRwCamera] Sets the Shuffle Time camera work's RW camera (+16 = a0) and marks it active (flag 1;
// K_Assert line 59).
// Arguments: a0 the RW camera.
void sub_24D280(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024d280
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpSflCamera);  // the Shuffle Time cameras (sfl_camera.c) 0x7CE33C
    if (v1 == 0) {
        // 0x0024d29c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 59;
        jal(ctx, 0x24D2A8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024d2b0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    lw(a0, gp, kGpSflCamera);  // the Shuffle Time cameras (sfl_camera.c) 0x7CE33C
    sw(s0, a0, sflcam::kRwCamera);
    lw(v1, a0, sflcam::kFlags);
    v1 = v1 | 0x1;
    sw(v1, a0, sflcam::kFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0024D2E0 sub_24D2E0 -- 200 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflCameraAdd] Adds the camera record a1 under the id a0 to the Shuffle Time camera list (K_Assert line 121: the id
// is new): record +4 the id, appended after the tail (+8 / +12 the links), its time +64 = 0.
// Arguments: a0 u16 id, a1 the camera record.
void sub_24D2E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024d2e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s0 = a1;
    lw(v0, gp, kGpSflCamera);  // the Shuffle Time cameras (sfl_camera.c) 0x7CE33C
    if (v0 == 0) {
        // 0x0024d308
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 59;
        jal(ctx, 0x24D314u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024d31c
    charge(ctx, 6);
    lw(s1, gp, kGpSflCamera);  // the Shuffle Time cameras (sfl_camera.c) 0x7CE33C
    a0 = s2;
    jal(ctx, 0x24D324u, gen::fn_sub_24D3B0_0024d3b0);
    if (v0 != 0) {
        // 0x0024d334
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 121;
        jal(ctx, 0x24D340u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024d348
    charge(ctx, 4);
    sh(s2, s0, sflcamrec::kId);
    lw(v1, s1, sflcam::kHead);
    if (v1 == 0) {
        // 0x0024d378
        charge(ctx, 4);
        sw(zero, s0, sflcamrec::kNext);
        sw(zero, s0, sflcamrec::kPrev);
        sw(s0, s1, sflcam::kHead);
        sw(s0, s1, sflcam::kTail);
    } else {
        // 0x0024d358
        charge(ctx, 8);
        lw(v1, s1, sflcam::kTail);
        sw(v1, s0, sflcamrec::kPrev);
        sw(zero, s0, sflcamrec::kNext);
        lw(v1, s1, sflcam::kTail);
        sw(s0, v1, sflcamrec::kNext);
        sw(s0, s1, sflcam::kTail);
    }
    // 0x0024d388 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    sw(zero, s0, sflcamrec::kTime);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0024D3B0 sub_24D3B0 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflCameraExists] Nonzero when the Shuffle Time camera list has a record with the id a0.
// Arguments: a0 u16 id.
void sub_24D3B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024d3b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpSflCamera);  // the Shuffle Time cameras (sfl_camera.c) 0x7CE33C
    if (v0 == 0) {
        // 0x0024d3cc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 59;
        jal(ctx, 0x24D3D8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024d3e0
    charge(ctx, 5);
    lw(v0, gp, kGpSflCamera);  // the Shuffle Time cameras (sfl_camera.c) 0x7CE33C
    lw(a0, v0, sflcam::kHead);
    v1 = s0 & 0xFFFF;  // the id looked for
    bool found = false;
    for (;;) {  // walk the camera list
        // 0x0024d410
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0024d3f4
        charge(ctx, 3);
        lhu(v0, a0, sflcamrec::kId);
        if (v0 == v1) {
            found = true;
            break;
        }
        // 0x0024d40c
        charge(ctx, 1);
        lw(a0, a0, sflcamrec::kNext);
    }
    if (found) {
        // 0x0024d400
        charge(ctx, 3);
        v0 = 1;
    } else {
        // 0x0024d418
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0024d41c (the epilogue)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0024D430 sub_24D430 -- 144 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflCameraFind] The Shuffle Time camera record with the id a0 (K_Assert line 175 when none; returns 0 then).
// Arguments: a0 u16 id.
void sub_24D430(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024d430
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpSflCamera);  // the Shuffle Time cameras (sfl_camera.c) 0x7CE33C
    if (v0 == 0) {
        // 0x0024d44c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 59;
        jal(ctx, 0x24D458u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024d460
    charge(ctx, 5);
    lw(v0, gp, kGpSflCamera);  // the Shuffle Time cameras (sfl_camera.c) 0x7CE33C
    lw(v0, v0, sflcam::kHead);
    a0 = s0 & 0xFFFF;  // the id looked for
    bool found = false;
    for (;;) {  // walk the camera list
        // 0x0024d48c
        charge(ctx, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0024d474
        charge(ctx, 3);
        lhu(v1, v0, sflcamrec::kId);
        if (v1 == a0) {
            found = true;
            break;
        }
        // 0x0024d488
        charge(ctx, 1);
        lw(v0, v0, sflcamrec::kNext);
    }
    if (found) {
        // 0x0024d480: the record is the result
        charge(ctx, 2);
    } else {
        // 0x0024d494: K_Assert(line 175), result 0
        charge(ctx, 6);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 175;
        jal(ctx, 0x24D4A0u, gen::fn_sub_19D3F0_0019d3f0);
        v0 = 0;
    }
    // 0x0024d4ac (the epilogue)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0024D4C0 sub_24D4C0 -- 276 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflCameraPick] Picks the Shuffle Time camera a0 (K_Assert line 175 when missing): +12 = the id, flag 2; a record
// of kind 1 restarts its orientation node (+168, sub_24F090), points its position node's first child at the record's
// anchor (+52, sub_2503F0) and restarts the position node (+68).
// Arguments: a0 u16 id.
void sub_24D4C0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024d4c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v1, gp, kGpSflCamera);  // the Shuffle Time cameras (sfl_camera.c) 0x7CE33C
    if (v1 == 0) {
        // 0x0024d4e4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 59;
        jal(ctx, 0x24D4F0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024d4f8
    charge(ctx, 3);
    lw(s0, gp, kGpSflCamera);  // the Shuffle Time cameras (sfl_camera.c) 0x7CE33C
    if (s0 == 0) {
        // 0x0024d504
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 59;
        jal(ctx, 0x24D510u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024d518
    charge(ctx, 5);
    lw(v1, gp, kGpSflCamera);  // the Shuffle Time cameras (sfl_camera.c) 0x7CE33C
    lw(s1, v1, sflcam::kHead);
    a0 = s2 & 0xFFFF;  // the id looked for (sflCameraFind inlined)
    bool found = false;
    for (;;) {
        // 0x0024d544
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0024d52c
        charge(ctx, 3);
        lhu(v1, s1, sflcamrec::kId);
        if (v1 == a0) {
            found = true;
            break;
        }
        // 0x0024d540
        charge(ctx, 1);
        lw(s1, s1, sflcamrec::kNext);
    }
    if (found) {
        // 0x0024d538
        charge(ctx, 2);
    } else {
        // 0x0024d54c: K_Assert(line 175), no record
        charge(ctx, 6);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 175;
        jal(ctx, 0x24D558u, gen::fn_sub_19D3F0_0019d3f0);
        s1 = 0;
    }
    // 0x0024d564: pick it; a kind-1 record restarts its nodes
    charge(ctx, 8);
    sh(s2, s0, sflcam::kPicked);
    lw(v1, s0, sflcam::kFlags);
    v1 = v1 | 0x2;
    sw(v1, s0, sflcam::kFlags);
    lw(a0, s1, sflcamrec::kKind);
    v1 = 1;
    if (a0 == v1) {
        // 0x0024d58c
        charge(ctx, 11);
        a0 = addiu(s1, sflcamrec::kRotNode);
        jal(ctx, 0x24D590u, gen::fn_sub_24F090_0024f090);
        a0 = addiu(s1, sflcamrec::kPosNode);
        a1 = 0;
        lw(a2, s1, sflcamrec::kAnchor);
        jal(ctx, 0x24D5A4u, gen::fn_sub_2503F0_002503f0);
        a0 = addiu(s1, sflcamrec::kPosNode);
        jal(ctx, 0x24D5B0u, gen::fn_sub_24F090_0024f090);
    } else {
        // 0x0024d584
        charge(ctx, 2);
    }
    // 0x0024d5b8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0024D5E0 sub_24D5E0 -- 484 bytes; frame 0x70: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflCameraStep] Steps a Shuffle Time camera record (a0; K_Assert lines 208 / 252: kind 1 only): time +64 += 1.0
// (16.16); the position follows the position node (+68 -> +32, flag +48); with a look-at node (+56 / +60) it builds
// an orthonormal frame looking from the position at the node's point (sub_4C6AC0 / sub_4C69F0, cross products) into
// the record's matrix (+16, sub_4BDCB0) through a scratch matrix (sub_4C38C0 / sub_4C3880).
// Arguments: a0 the camera record.
void sub_24D5E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6};
    // 0x0024d5e0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, a0, sflcamrec::kKind);
    if (v0 == 0) {
        // 0x0024d600
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 208;
        jal(ctx, 0x24D60Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024d614
    charge(ctx, 11);
    jal(ctx, 0x24D614u, gen::fn_sub_4C38C0_004c38c0);
    s0 = v0;
    lw(v1, s1, sflcamrec::kTime);
    v0 = 0x10000;
    v0 = addu(v1, v0);
    sw(v0, s1, sflcamrec::kTime);
    lw(v0, s1, sflcamrec::kKind);
    v1 = 1;
    if (v0 == v1) {
        // 0x0024d648
        charge(ctx, 3);
        lw(v0, s1, sflcamrec::kFollowPos);
        if (v0 == v1) {
            // 0x0024d65c
            charge(ctx, 4);
            a0 = addiu(s1, 68);
            a1 = addiu(s1, 32);
            jal(ctx, 0x24D664u, gen::fn_sub_24F960_0024f960);
        } else {
            // 0x0024d654
            charge(ctx, 2);
        }
        // 0x0024d66c
        charge(ctx, 4);
        lw(v1, s1, sflcamrec::kLookAtOn);
        v0 = 1;
        if (v1 == v0) {
            // 0x0024d684
            charge(ctx, 66);
            lw(a0, s1, sflcamrec::kLookAt);
            a1 = addiu(sp, 0x30);
            jal(ctx, 0x24D68Cu, gen::fn_sub_24F960_0024f960);
            lwc1(f1, s1, sflcamrec::kPos);
            lwc1(f0, sp, 0x30);
            sub_s(f0, f0, f1);
            swc1(f0, sp, 0x60);
            lwc1(f1, s1, sflcamrec::kPos + 4);
            lwc1(f0, sp, 0x34);
            sub_s(f0, f0, f1);
            swc1(f0, sp, 0x64);
            lwc1(f1, s1, sflcamrec::kPos + 8);
            lwc1(f0, sp, 0x38);
            sub_s(f0, f0, f1);
            swc1(f0, sp, 0x68);
            a0 = addiu(sp, 0x60);
            jal(ctx, 0x24D6C8u, gen::fn_sub_4C6AC0_004c6ac0);
            a0 = addiu(sp, 0x60);
            a1 = a0;
            jal(ctx, 0x24D6D8u, gen::fn_sub_4C69F0_004c69f0);
            lwc1(f6, sp, 0x64);
            lwc1(f5, sp, 0x68);
            mtc1(zero, f1);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            mula_s(f0, f5);
            msub_s(f4, f1, f6);
            swc1(f4, sp, 0x50);
            lwc1(f3, sp, 0x60);
            mula_s(f1, f3);
            msub_s(f2, f1, f5);
            swc1(f2, sp, 0x54);
            mula_s(f1, f6);
            msub_s(f1, f0, f3);
            swc1(f1, sp, 0x58);
            mula_s(f6, f1);
            msub_s(f0, f5, f2);
            swc1(f0, sp, 0x40);
            mula_s(f5, f4);
            msub_s(f0, f3, f1);
            swc1(f0, sp, 0x44);
            mula_s(f3, f2);
            msub_s(f0, f6, f4);
            swc1(f0, sp, 0x48);
            a0 = addiu(s0, 32);
            a1 = addiu(sp, 0x60);
            jal(ctx, 0x24D74Cu, gen::fn_sub_4C69F0_004c69f0);
            a0 = s0;
            a1 = addiu(sp, 0x50);
            jal(ctx, 0x24D75Cu, gen::fn_sub_4C69F0_004c69f0);
            a0 = addiu(s0, 16);
            a1 = addiu(sp, 0x40);
            jal(ctx, 0x24D76Cu, gen::fn_sub_4C69F0_004c69f0);
            a0 = addiu(s1, 16);
            a1 = s0;
            jal(ctx, 0x24D77Cu, gen::fn_sub_4BDCB0_004bdcb0);
        } else {
            // 0x0024d67c
            charge(ctx, 2);
        }
    } else {
        // 0x0024d640
        charge(ctx, 2);
        // 0x0024d78c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 252;
        jal(ctx, 0x24D798u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024d7a0
    charge(ctx, 9);
    a0 = s0;
    jal(ctx, 0x24D7A4u, gen::fn_sub_4C3880_004c3880);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0024D7D0 sub_24D7D0 -- 256 bytes; frame 0x10: ra sp+0x0
// [sflCameraApply] Copies a Shuffle Time camera record's rotation into the RW camera's frame (a0 +4): the quaternion
// a1 +16..+28 becomes the 3x3 matrix (2 / |q|^2 scaling), the translation cleared, the matrix flags 3, then
// RwFrameUpdateObjects (sub_4CB750).
// Arguments: a0 the RW camera, a1 the record.
void sub_24D7D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12};
    // 0x0024d7d0
    enter(ctx, 64);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, rwcam::kFrame);
    lwc1(f4, a1, sflcamrec::kQuat + 4);
    lwc1(f12, a1, sflcamrec::kQuat);
    lwc1(f11, a1, sflcamrec::kQuat + 8);
    lwc1(f3, a1, sflcamrec::kQuat + 12);
    mula_s(f4, f4);
    madda_s(f12, f12);
    madda_s(f11, f11);
    madd_s(f1, f3, f3);
    v0 = 0x40000000;
    mtc1(v0, f0);
    div_s(f0, f0, f1);
    mul_s(f2, f12, f0);
    mul_s(f1, f4, f0);
    mul_s(f0, f11, f0);
    mul_s(f10, f2, f3);
    mul_s(f9, f1, f3);
    mul_s(f8, f0, f3);
    mul_s(f7, f12, f2);
    mul_s(f6, f4, f1);
    mul_s(f5, f11, f0);
    mul_s(f4, f4, f0);
    mul_s(f3, f11, f2);
    mul_s(f2, f12, f1);
    add_s(f0, f6, f5);
    v0 = 0x3F800000;
    mtc1(v0, f1);
    sub_s(f0, f1, f0);
    swc1(f0, a0, 16);
    add_s(f0, f2, f8);
    swc1(f0, a0, 20);
    sub_s(f0, f3, f9);
    swc1(f0, a0, 24);
    sub_s(f0, f2, f8);
    swc1(f0, a0, 32);
    add_s(f0, f5, f7);
    sub_s(f0, f1, f0);
    swc1(f0, a0, 36);
    add_s(f0, f4, f10);
    swc1(f0, a0, 40);
    add_s(f0, f3, f9);
    swc1(f0, a0, 48);
    sub_s(f0, f4, f10);
    swc1(f0, a0, 52);
    add_s(f0, f7, f6);
    sub_s(f0, f1, f0);
    swc1(f0, a0, 56);
    sw(zero, a0, 64);
    sw(zero, a0, 68);
    sw(zero, a0, 72);
    v0 = 3;
    sw(v0, a0, 28);
    a1 = addiu(a1, 32);
    a2 = 2;
    jal(ctx, 0x24D8B8u, gen::fn_sub_4CB750_004cb750);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0024D8D0 sub_24D8D0 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflCameraInitRecord] Initialises a Shuffle Time camera record (a0): kind 1, the position / look-at flags +48 / +56
// set, its orientation node (+168) as a random-wobble node (sub_24FD20) and its position node (+68) as a sum node
// (sub_24FD40), both reset (sub_24DA60).
// Arguments: a0 the camera record.
void sub_24D8D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024d8d0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = 1;
    sw(v0, a0, sflcamrec::kKind);
    sw(v0, a0, sflcamrec::kFollowPos);
    sw(v0, a0, sflcamrec::kLookAtOn);
    a0 = addiu(s0, 168);
    jal(ctx, 0x24D8F4u, gen::fn_sub_24FD20_0024fd20);
    a0 = addiu(s0, 168);
    jal(ctx, 0x24D900u, gen::fn_sub_24DA60_0024da60);
    a0 = addiu(s0, 68);
    jal(ctx, 0x24D90Cu, gen::fn_sub_24FD40_0024fd40);
    a0 = addiu(s0, 68);
    jal(ctx, 0x24D918u, gen::fn_sub_24DA60_0024da60);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0024D940 sub_24D940 -- 84 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflCameraSetAnchor] Sets a Shuffle Time camera record's anchor node (+52 = a1; K_Assert line 292: kind set).
// Arguments: a0 the record, a1 a pose node.
void sub_24D940(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024d940
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, a0, sflcamrec::kKind);
    if (v1 == 0) {
        // 0x0024d964
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 292;
        jal(ctx, 0x24D970u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024d978 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(s0, s1, sflcamrec::kAnchor);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0024D9A0 sub_24D9A0 -- 84 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflCameraSetLookAt] Sets a Shuffle Time camera record's look-at node (+60 = a1; K_Assert line 297).
// Arguments: a0 the record, a1 a pose node.
void sub_24D9A0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024d9a0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, a0, sflcamrec::kKind);
    if (v1 == 0) {
        // 0x0024d9c4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 297;
        jal(ctx, 0x24D9D0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024d9d8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(s0, s1, sflcamrec::kLookAt);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0024DA20 sub_24DA20 -- 60 bytes; frame 0x10: ra sp+0x0
// [gcPoseTerm] Closes the gc_pose work (K_Assert line 93) and clears its $gp slot 0x7CE340.
void sub_24DA20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024da20
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpGcPose);  // the pose nodes (gc_pose.c) 0x7CE340
    if (v1 == 0) {
        // 0x0024da34
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 93;
        jal(ctx, 0x24DA40u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024da48 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sw(zero, gp, kGpGcPose);  // the pose nodes (gc_pose.c) 0x7CE340
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0024DB90 sub_24DB90 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [gcPoseTickAll] Advances every active gc_pose node by one frame (K_Assert line 93): time += 1.0 (16.16) and dirty
// (gcPoseAddTime).
void sub_24DB90(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024db90
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpGcPose);  // the pose nodes (gc_pose.c) 0x7CE340
    if (v1 == 0) {
        // 0x0024dba8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 93;
        jal(ctx, 0x24DBB4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024dbbc
    charge(ctx, 4);
    lw(v1, gp, kGpGcPose);  // the pose nodes (gc_pose.c) 0x7CE340
    lw(s0, v1, gcpose::kHead);
    for (;;) {
        // 0x0024dbf4
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0024dbcc
        charge(ctx, 5);
        lw(v1, s0, pose::kFlags);
        v1 = nor(v1, 0);
        v1 = v1 & 0x1;
        if (v1 == 0) {
            // 0x0024dbe0
            charge(ctx, 4);
            a0 = s0;
            a1 = 0x10000;
            jal(ctx, 0x24DBE8u, gen::fn_sub_251010_00251010);
        }
        // 0x0024dbf0
        charge(ctx, 1);
        lw(s0, s0, pose::kNext);
    }
    // 0x0024dbfc
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0024DC10 sub_24DC10 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [gcPoseEvalAll] Evaluates every gc_pose node (K_Assert line 93): clears the evaluation stack (+520) and runs
// gcPoseEval on each node of the list.
void sub_24DC10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024dc10
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpGcPose);  // the pose nodes (gc_pose.c) 0x7CE340
    if (v1 == 0) {
        // 0x0024dc28
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 93;
        jal(ctx, 0x24DC34u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024dc3c
    charge(ctx, 5);
    lw(v1, gp, kGpGcPose);  // the pose nodes (gc_pose.c) 0x7CE340
    sw(zero, v1, gcpose::kDepth);
    lw(s0, v1, gcpose::kHead);
    for (;;) {
        // 0x0024dc60
        charge(ctx, 4);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0024dc50
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x24DC54u, gen::fn_sub_24DC90_0024dc90);
        lw(s0, s0, pose::kNext);
    }
    // 0x0024dc70
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0024DC90 sub_24DC90 -- 5108 bytes; frame 0x120: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [gcPoseEval] Evaluates a gc_pose node (a0) and the dirty nodes it depends on, depth first on the work's 128-entry
// stack (+8, count +520; K_Assert lines 230 / 306 / 408 / 452 / 530 on overflow). A gc_pose.c node (100 bytes): +4
// next, +8 flags (1 active, 2 dirty), +12 kind (0 a position, 1 a direction, 2 an orientation), +16 its time (16.16
// frames), +20 the value (f32[3], or a quaternion f32[4] for kind 2), +32 the position mode / +36 the orientation
// mode, then the mode's words. A dirty active node whose inputs are clean computes its value and turns clean:
// positions -- 0 fixed, 1 a wander (every +88 frames a new random target within +-range/2 (+84, libc rand), a spline
// toward it (gcPoseWanderSpline), scaled by +96), 2 the sum of up to three child positions, 3 a timed move (+36: 1 a
// constant-acceleration arc start + v*t + a*t^2/2 in 1/30 s units, 0 a straight lerp start -> end over +44, stopping
// at the end time); directions (kind 1, mode word +32 = 1) the second position minus the first (+40 minus +36;
// another nonzero mode asserts, line 425); orientations -- 1 a look-at quaternion from two directions (sub_4BDDE0
// about the axes, the y axis when parallel), 2 the product of up to three child orientations, 3 a timed spin (+52
// axis, angle by time), 4 a wobble (random angles over +100 frames times +108, gcPoseWobbleSpline), kind / mode
// errors assert (lines 381 / 425 / 677 / 683).
// Arguments: a0 the node.
void sub_24DC90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x0024dc90: push the node on the evaluation stack (K_Assert line 230 when the stack is not empty)
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    lw(v1, gp, kGpGcPose);  // the pose nodes (gc_pose.c) 0x7CE340
    if (v1 == 0) {
        // 0x0024dcc8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 93;
        jal(ctx, 0x24DCD4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024dcdc
    charge(ctx, 10);
    lw(s0, gp, kGpGcPose);  // the pose nodes (gc_pose.c) 0x7CE340
    v1 = 0x690000;
    ld(a0, v1, -5712);  // 0x68E9B0
    v1 = 0x690000;
    lwc1(f0, v1, -5704);  // 0x68E9B8
    sd(a0, sp, 0xB0);
    swc1(f0, sp, 0xB8);
    lw(v1, s0, gcpose::kDepth);
    if (v1 != 0) {
        // 0x0024dd04
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 230;
        jal(ctx, 0x24DD10u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024dd18
    charge(ctx, 11);
    lw(v1, s0, gcpose::kDepth);
    v1 = sll(v1, 2);
    v1 = addu(v1, s0);
    sw(s1, v1, 8);
    lw(v1, s0, gcpose::kDepth);
    v1 = addiu(v1, 1);
    sw(v1, s0, gcpose::kDepth);
    lwc1(f21, sp, 0xB4);
    lwc1(f20, sp, 0xB8);
    for (;;) {
        // 0x0024f048
        charge(ctx, 3);
        lw(v1, s0, gcpose::kDepth);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0024dd44: the node on top of the stack: only an active (0x1) dirty (0x2) node is evaluated
        charge(ctx, 7);
        v1 = sll(v1, 2);
        v1 = addu(s0, v1);
        lw(s1, v1, 4);
        lw(a0, s1, pose::kFlags);
        v1 = a0 & 0x1;
        if (v1 != 0) {
            // 0x0024dd60
            charge(ctx, 3);
            v1 = a0 & 0x2;
            if (v1 == 0) {
                goto L_0024f02c;
            }
            // 0x0024dd6c: by its kind
            charge(ctx, 4);
            lw(v1, s1, pose::kKind);
            a2 = 2;
            if (v1 == a2) {
                // 0x0024e5a4: kind 2, an orientation: by its mode (+36)
                charge(ctx, 4);
                lw(a0, s1, pose::kW36);
                v1 = 4;
                if (a0 == v1) {
                    // 0x0024ec04: mode 4, a wobble: every +100 frames new random target angles (libc rand) and the
                    // spline toward them
                    charge(ctx, 16);
                    s2 = addiu(s1, 40);
                    lw(v0, s1, pose::kW100);
                    v1 = sll(v0, 16);
                    lw(v0, s1, pose::kTime);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    div_s(f3, f1, f0);
                    v0 = slt(v0, v1);
                    if (v0 == 0) {
                        // 0x0024ec44
                        charge(ctx, 30);
                        lwc1(f1, s2, 24);
                        lwc1(f0, s2, 36);
                        sub_s(f3, f1, f0);
                        swc1(f3, sp, 0x110);
                        lwc1(f1, s2, 28);
                        lwc1(f0, s2, 40);
                        sub_s(f2, f1, f0);
                        swc1(f2, sp, 0x114);
                        lwc1(f1, s2, 32);
                        lwc1(f0, s2, 44);
                        sub_s(f1, f1, f0);
                        swc1(f1, sp, 0x118);
                        neg_s(f0, f3);
                        swc1(f0, sp, 0xF0);
                        neg_s(f0, f2);
                        swc1(f0, sp, 0xF4);
                        neg_s(f0, f1);
                        swc1(f0, sp, 0xF8);
                        lwc1(f2, s2, 36);
                        lwc1(f1, s2, 40);
                        lwc1(f0, s2, 44);
                        swc1(f2, s2, 0);
                        swc1(f1, s2, 4);
                        swc1(f0, s2, 8);
                        lwc1(f22, s2, 48);
                        jal(ctx, 0x24ECA8u, gen::fn_sub_488F30_00488f30);
                        v0 = v0 & 0xFFF;
                        if (i64(v0) < 0) {
                            // 0x0024ecd0
                            charge(ctx, 7);
                            v1 = srl(v0, 1);
                            v0 = v0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x0024ecbc
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x0024ecec
                        charge(ctx, 17);
                        mul_s(f1, f22, f0);
                        v0 = 0x45800000;
                        mtc1(v0, f0);
                        div_s(f1, f1, f0);
                        v0 = 0x40000000;
                        mtc1(v0, f0);
                        div_s(f0, f22, f0);
                        sub_s(f0, f0, f1);
                        swc1(f0, sp, 0x110);
                        lwc1(f22, s2, 52);
                        jal(ctx, 0x24ED1Cu, gen::fn_sub_488F30_00488f30);
                        v0 = v0 & 0xFFF;
                        if (i64(v0) < 0) {
                            // 0x0024ed44
                            charge(ctx, 7);
                            v1 = srl(v0, 1);
                            v0 = v0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x0024ed30
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x0024ed60
                        charge(ctx, 17);
                        mul_s(f1, f22, f0);
                        v0 = 0x45800000;
                        mtc1(v0, f0);
                        div_s(f1, f1, f0);
                        v0 = 0x40000000;
                        mtc1(v0, f0);
                        div_s(f0, f22, f0);
                        sub_s(f0, f0, f1);
                        swc1(f0, sp, 0x114);
                        lwc1(f22, s2, 56);
                        jal(ctx, 0x24ED90u, gen::fn_sub_488F30_00488f30);
                        v0 = v0 & 0xFFF;
                        if (i64(v0) < 0) {
                            // 0x0024edb8
                            charge(ctx, 7);
                            v1 = srl(v0, 1);
                            v0 = v0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x0024eda4
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x0024edd4
                        charge(ctx, 30);
                        mul_s(f1, f22, f0);
                        v0 = 0x45800000;
                        mtc1(v0, f0);
                        div_s(f1, f1, f0);
                        v0 = 0x40000000;
                        mtc1(v0, f0);
                        div_s(f0, f22, f0);
                        sub_s(f0, f0, f1);
                        swc1(f0, sp, 0x118);
                        lwc1(f2, sp, 0x110);
                        lwc1(f1, sp, 0x114);
                        lwc1(f0, sp, 0x118);
                        swc1(f2, s2, 36);
                        swc1(f1, s2, 40);
                        swc1(f0, s2, 44);
                        a0 = s1;
                        a1 = addiu(sp, 0xF0);
                        jal(ctx, 0x24EE20u, gen::fn_sub_250280_00250280);
                        sw(zero, s1, pose::kTime);
                        lwc1(f0, s1, pose::kTime);
                        cvt_s_w(f1, f0);
                        lw(v0, s2, 60);
                        v0 = sll(v0, 16);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f3, f1, f0);
                    }
                    // 0x0024ee4c: the wobble's angles along the spline, times the scale (+108), as rotations about x,
                    // y and z (sub_4BDDE0) into the quaternion
                    charge(ctx, 108);
                    v1 = 0x3F800000;
                    mtc1(v1, f0);
                    sub_s(f2, f0, f3);
                    lwc1(f0, s2, 36);
                    mul_s(f0, f0, f3);
                    mul_s(f6, f3, f0);
                    v0 = 0x40400000;
                    mtc1(v0, f1);
                    lwc1(f0, s2, 24);
                    mul_s(f0, f1, f0);
                    mul_s(f0, f0, f3);
                    mul_s(f5, f3, f0);
                    lwc1(f0, s2, 0);
                    mul_s(f0, f0, f2);
                    mul_s(f4, f2, f0);
                    lwc1(f0, s2, 12);
                    mul_s(f0, f1, f0);
                    mul_s(f0, f0, f3);
                    mul_s(f0, f2, f0);
                    mula_s(f2, f0);
                    madda_s(f2, f4);
                    madda_s(f2, f5);
                    madd_s(f0, f3, f6);
                    swc1(f0, sp, 0xE0);
                    lwc1(f4, s2, 40);
                    mul_s(f4, f4, f3);
                    mul_s(f7, f3, f4);
                    lwc1(f4, s2, 28);
                    mul_s(f4, f1, f4);
                    mul_s(f4, f4, f3);
                    mul_s(f6, f3, f4);
                    lwc1(f4, s2, 4);
                    mul_s(f4, f4, f2);
                    mul_s(f5, f2, f4);
                    lwc1(f4, s2, 16);
                    mul_s(f4, f1, f4);
                    mul_s(f4, f4, f3);
                    mul_s(f4, f2, f4);
                    mula_s(f2, f4);
                    madda_s(f2, f5);
                    madda_s(f2, f6);
                    madd_s(f8, f3, f7);
                    swc1(f8, sp, 0xE4);
                    lwc1(f4, s2, 44);
                    mul_s(f4, f4, f3);
                    mul_s(f7, f3, f4);
                    lwc1(f4, s2, 32);
                    mul_s(f4, f1, f4);
                    mul_s(f4, f4, f3);
                    mul_s(f6, f3, f4);
                    lwc1(f4, s2, 8);
                    mul_s(f4, f4, f2);
                    mul_s(f5, f2, f4);
                    lwc1(f4, s2, 20);
                    mul_s(f1, f1, f4);
                    mul_s(f1, f1, f3);
                    mul_s(f1, f2, f1);
                    mula_s(f2, f1);
                    madda_s(f2, f5);
                    madda_s(f2, f6);
                    madd_s(f2, f3, f7);
                    swc1(f2, sp, 0xE8);
                    lwc1(f1, s2, 68);
                    mul_s(f12, f0, f1);
                    swc1(f12, sp, 0xE0);
                    mul_s(f0, f8, f1);
                    swc1(f0, sp, 0xE4);
                    mul_s(f0, f2, f1);
                    swc1(f0, sp, 0xE8);
                    sw(v1, sp, 0xA0);
                    sw(zero, sp, 0xA4);
                    sw(zero, sp, 0xA8);
                    a0 = addiu(sp, 0x90);
                    a1 = addiu(sp, 0xA0);
                    a2 = 0;
                    jal(ctx, 0x24EF7Cu, gen::fn_sub_4BDDE0_004bdde0);
                    sw(zero, sp, 0xA0);
                    v0 = 0x3F800000;
                    sw(v0, sp, 0xA4);
                    sw(zero, sp, 0xA8);
                    a0 = addiu(sp, 0x90);
                    a1 = addiu(sp, 0xA0);
                    lwc1(f12, sp, 0xE4);
                    a2 = 2;
                    jal(ctx, 0x24EFA4u, gen::fn_sub_4BDDE0_004bdde0);
                    sw(zero, sp, 0xA0);
                    sw(zero, sp, 0xA4);
                    v0 = 0x3F800000;
                    sw(v0, sp, 0xA8);
                    a0 = addiu(sp, 0x90);
                    a1 = addiu(sp, 0xA0);
                    lwc1(f12, sp, 0xE8);
                    a2 = 2;
                    jal(ctx, 0x24EFCCu, gen::fn_sub_4BDDE0_004bdde0);
                    lwc1(f3, sp, 0x90);
                    lwc1(f2, sp, 0x94);
                    lwc1(f1, sp, 0x98);
                    lwc1(f0, sp, 0x9C);
                    swc1(f3, s1, pose::kValue);
                    swc1(f2, s1, pose::kValue + 4);
                    swc1(f1, s1, pose::kValue + 8);
                    swc1(f0, s1, pose::kPosMode);
                    goto L_0024f02c;
                }
                // 0x0024e5b4
                charge(ctx, 3);
                v1 = 3;
                if (a0 == v1) {
                    // 0x0024eaa0: mode 3, a spin: a running spin clamps the time to its duration (+48)
                    charge(ctx, 5);
                    s2 = addiu(s1, 40);
                    lw(v1, s1, pose::kW44);
                    v1 = v1 & 0x1;
                    if (v1 != 0) {
                        // 0x0024eab4
                        charge(ctx, 5);
                        lw(a0, s2, 8);
                        lw(v1, s1, pose::kTime);
                        v1 = slt(v1, a0);
                        if (v1 == 0) {
                            // 0x0024eac8
                            charge(ctx, 1);
                            sw(a0, s1, pose::kTime);
                        }
                    }
                    // 0x0024eacc: the angle by the time (curve +40: 1 decelerating, 0 linear) about the axis (+52,
                    // sub_4BDDE0)
                    charge(ctx, 4);
                    lw(v1, s2, 4);
                    v1 = v1 & 0x1;
                    if (v1 != 0) {
                        // 0x0024eadc
                        charge(ctx, 4);
                        lw(a0, s2, 0);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x0024eb60
                            charge(ctx, 27);
                            a1 = addiu(s2, 12);
                            lwc1(f0, s1, pose::kTime);
                            cvt_s_w(f1, f0);
                            v0 = 0x49F00000;
                            mtc1(v0, f0);
                            div_s(f3, f1, f0);
                            lwc1(f2, s2, 32);
                            v0 = 0x3F000000;
                            mtc1(v0, f1);
                            lwc1(f0, s2, 36);
                            mul_s(f0, f1, f0);
                            mul_s(f0, f0, f3);
                            mula_s(f3, f0);
                            madd_s(f1, f2, f3);
                            lwc1(f0, s2, 24);
                            add_s(f1, f0, f1);
                            lwc1(f0, gp, -32264);  // 0x7CAEE8
                            div_s(f1, f1, f0);
                            v0 = 0x43B40000;
                            mtc1(v0, f0);
                            mul_s(f12, f0, f1);
                            a0 = addiu(s1, 20);
                            a2 = 0;
                            jal(ctx, 0x24EBC4u, gen::fn_sub_4BDDE0_004bdde0);
                        } else {
                            // 0x0024eaec
                            charge(ctx, 2);
                            if (a0 == 0) {
                                // 0x0024eafc
                                charge(ctx, 25);
                                a1 = addiu(s2, 12);
                                lwc1(f0, s1, pose::kTime);
                                cvt_s_w(f1, f0);
                                lwc1(f0, s2, 8);
                                cvt_s_w(f0, f0);
                                div_s(f3, f1, f0);
                                lwc1(f2, s2, 24);
                                lwc1(f0, s2, 28);
                                sub_s(f1, f0, f2);
                                mtc1(zero, f0);
                                adda_s(f0, f2);
                                madd_s(f1, f3, f1);
                                lwc1(f0, gp, -32264);  // 0x7CAEE8
                                div_s(f1, f1, f0);
                                v0 = 0x43B40000;
                                mtc1(v0, f0);
                                mul_s(f12, f0, f1);
                                a0 = addiu(s1, 20);
                                a2 = 0;
                                jal(ctx, 0x24EB50u, gen::fn_sub_4BDDE0_004bdde0);
                            } else {
                                // 0x0024eaf4
                                charge(ctx, 2);
                            }
                        }
                    }
                    // 0x0024ebcc: past the duration the spin stops (+44 bit 1)
                    charge(ctx, 4);
                    lw(a1, s2, 4);
                    v1 = a1 & 0x1;
                    if (v1 != 0) {
                        // 0x0024ebdc
                        charge(ctx, 5);
                        lw(a0, s1, pose::kTime);
                        lw(v1, s2, 8);
                        v1 = slt(a0, v1);
                        if (v1 == 0) {
                            // 0x0024ebf0
                            charge(ctx, 5);
                            v1 = si(-2);
                            v1 = a1 & v1;
                            sw(v1, s2, 4);
                        }
                    }
                    goto L_0024f02c;
                }
                // 0x0024e5c0
                charge(ctx, 2);
                if (a0 == a2) {
                    // 0x0024e8d0: mode 2, a product: the dirty children (+40..+48) are evaluated first
                    charge(ctx, 5);
                    s3 = addiu(s1, 40);
                    a0 = 0;
                    s4 = 0;
                    for (;;) {
                        // 0x0024e954
                        charge(ctx, 3);
                        v1 = slti(s4, 3);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0024e8e4
                        charge(ctx, 5);
                        v1 = sll(s4, 2);
                        s2 = addu(s3, v1);
                        lw(v1, s2, 0);
                        if (v1 != 0) {
                            // 0x0024e8f8
                            charge(ctx, 5);
                            lw(v1, v1, 8);
                            v1 = nor(v1, 0);
                            v1 = v1 & 0x2;
                            if (v1 == 0) {
                                // 0x0024e90c
                                charge(ctx, 4);
                                lw(v1, s0, gcpose::kDepth);
                                v1 = slti(v1, 128);
                                if (v1 == 0) {
                                    // 0x0024e91c
                                    charge(ctx, 5);
                                    a0 = 0x690000;
                                    a0 = addiu(a0, -5728);  // "gc_pose.c"
                                    a1 = 530;
                                    jal(ctx, 0x24E928u, gen::fn_sub_19D3F0_0019d3f0);
                                }
                                // 0x0024e930
                                charge(ctx, 8);
                                lw(a1, s2, 0);
                                lw(a0, s0, gcpose::kDepth);
                                v1 = addiu(a0, 1);
                                sw(v1, s0, gcpose::kDepth);
                                v1 = sll(a0, 2);
                                v1 = addu(s0, v1);
                                sw(a1, v1, 8);
                                a0 = 1;
                            }
                        }
                        // 0x0024e950
                        charge(ctx, 1);
                        s4 = addiu(s4, 1);
                    }
                    // 0x0024e960: the children's quaternions multiplied in order into the value
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x0024e968
                        charge(ctx, 4);
                        s4 = 0;
                        s2 = 0;
                        for (;;) {
                            // 0x0024ea6c
                            charge(ctx, 3);
                            v1 = slti(s2, 3);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0024e978
                            charge(ctx, 5);
                            v1 = sll(s2, 2);
                            v1 = addu(s3, v1);
                            lw(a0, v1, 0);
                            if (a0 != 0) {
                                // 0x0024e98c
                                charge(ctx, 2);
                                if (s4 != 0) {
                                    // 0x0024e9ac
                                    charge(ctx, 47);
                                    a1 = addiu(sp, 0x70);
                                    jal(ctx, 0x24E9B0u, gen::fn_sub_24FBA0_0024fba0);
                                    lwc1(f11, sp, 0x74);
                                    lwc1(f10, sp, 0x94);
                                    lwc1(f9, sp, 0x70);
                                    lwc1(f8, sp, 0x90);
                                    lwc1(f7, sp, 0x78);
                                    lwc1(f6, sp, 0x98);
                                    lwc1(f5, sp, 0x7C);
                                    lwc1(f4, sp, 0x9C);
                                    mula_s(f10, f11);
                                    mtc1(zero, f3);
                                    madda_s(f8, f9);
                                    madd_s(f1, f6, f7);
                                    mul_s(f0, f4, f5);
                                    sub_s(f0, f0, f1);
                                    swc1(f0, sp, 0x8C);
                                    mula_s(f10, f7);
                                    msub_s(f0, f6, f11);
                                    swc1(f0, sp, 0x80);
                                    mula_s(f6, f9);
                                    msub_s(f2, f8, f7);
                                    swc1(f2, sp, 0x84);
                                    mula_s(f8, f11);
                                    msub_s(f1, f10, f9);
                                    swc1(f1, sp, 0x88);
                                    adda_s(f3, f0);
                                    madd_s(f0, f9, f4);
                                    swc1(f0, sp, 0x80);
                                    adda_s(f3, f2);
                                    madd_s(f2, f11, f4);
                                    swc1(f2, sp, 0x84);
                                    adda_s(f3, f1);
                                    madd_s(f1, f7, f4);
                                    swc1(f1, sp, 0x88);
                                    adda_s(f3, f0);
                                    madd_s(f0, f8, f5);
                                    swc1(f0, sp, 0x80);
                                    adda_s(f3, f2);
                                    madd_s(f0, f10, f5);
                                    swc1(f0, sp, 0x84);
                                    adda_s(f3, f1);
                                    madd_s(f0, f6, f5);
                                    swc1(f0, sp, 0x88);
                                    lq(v1, sp, 0x80);
                                    sq(v1, sp, 0x90);
                                } else {
                                    // 0x0024e994
                                    charge(ctx, 6);
                                    a1 = addiu(sp, 0x90);
                                    jal(ctx, 0x24E998u, gen::fn_sub_24FBA0_0024fba0);
                                    s4 = 1;
                                }
                            }
                            // 0x0024ea68
                            charge(ctx, 1);
                            s2 = addiu(s2, 1);
                        }
                        // 0x0024ea78
                        charge(ctx, 10);
                        lwc1(f3, sp, 0x90);
                        lwc1(f2, sp, 0x94);
                        lwc1(f1, sp, 0x98);
                        lwc1(f0, sp, 0x9C);
                        swc1(f3, s1, pose::kValue);
                        swc1(f2, s1, pose::kValue + 4);
                        swc1(f1, s1, pose::kValue + 8);
                        swc1(f0, s1, pose::kPosMode);
                        goto L_0024f02c;
                    }
                } else {
                    // 0x0024e5c8
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 != v1) {
                        // 0x0024e5d4
                        charge(ctx, 2);
                        if (a0 != 0) {
                            // 0x0024e5dc
                            charge(ctx, 2);
                            // 0x0024effc
                            charge(ctx, 7);
                            a0 = 0x690000;
                            a0 = addiu(a0, -5728);  // "gc_pose.c"
                            a1 = 677;
                            jal(ctx, 0x24F008u, gen::fn_sub_19D3F0_0019d3f0);
                        }
                        goto L_0024f02c;
                    }
                    // 0x0024e5e4: mode 1, a look-at: the two direction children (+40 / +44) are evaluated first
                    charge(ctx, 5);
                    s3 = addiu(s1, 40);
                    a0 = 0;
                    s4 = 0;
                    for (;;) {
                        // 0x0024e660
                        charge(ctx, 3);
                        v1 = slti(s4, 2);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0024e5f8
                        charge(ctx, 8);
                        v1 = sll(s4, 2);
                        s2 = addu(s3, v1);
                        lw(v1, s2, 0);
                        lw(v1, v1, 8);
                        v1 = nor(v1, 0);
                        v1 = v1 & 0x2;
                        if (v1 == 0) {
                            // 0x0024e618
                            charge(ctx, 4);
                            lw(v1, s0, gcpose::kDepth);
                            v1 = slti(v1, 128);
                            if (v1 == 0) {
                                // 0x0024e628
                                charge(ctx, 5);
                                a0 = 0x690000;
                                a0 = addiu(a0, -5728);  // "gc_pose.c"
                                a1 = 452;
                                jal(ctx, 0x24E634u, gen::fn_sub_19D3F0_0019d3f0);
                            }
                            // 0x0024e63c
                            charge(ctx, 8);
                            lw(a1, s2, 0);
                            lw(a0, s0, gcpose::kDepth);
                            v1 = addiu(a0, 1);
                            sw(v1, s0, gcpose::kDepth);
                            v1 = sll(a0, 2);
                            v1 = addu(s0, v1);
                            sw(a1, v1, 8);
                            a0 = 1;
                        }
                        // 0x0024e65c
                        charge(ctx, 1);
                        s4 = addiu(s4, 1);
                    }
                    // 0x0024e66c: the rotation that turns the first direction onto the second, about their cross
                    // product (the y axis when they are parallel), then the second turn about the new up (sub_4BDDE0)
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x0024e674
                        charge(ctx, 53);
                        lw(a0, s3, 0);
                        jal(ctx, 0x24E678u, gen::fn_sub_24FAA0_0024faa0);
                        s4 = v0;
                        lw(a0, s3, 4);
                        jal(ctx, 0x24E688u, gen::fn_sub_24FAA0_0024faa0);
                        s2 = v0;
                        a0 = addiu(sp, 0xE0);
                        a1 = s4;
                        jal(ctx, 0x24E69Cu, gen::fn_sub_4C69F0_004c69f0);
                        a0 = addiu(sp, 0xD0);
                        a1 = s2;
                        jal(ctx, 0x24E6ACu, gen::fn_sub_4C69F0_004c69f0);
                        lwc1(f7, sp, 0xD4);
                        lwc1(f6, sp, 0xE4);
                        lwc1(f5, sp, 0xD0);
                        lwc1(f0, sp, 0xE0);
                        lwc1(f4, sp, 0xD8);
                        lwc1(f3, sp, 0xE8);
                        mula_s(f6, f7);
                        mtc1(zero, f2);
                        madda_s(f0, f5);
                        madd_s(f1, f3, f4);
                        adda_s(f2, f5);
                        msub_s(f0, f0, f1);
                        swc1(f0, sp, 0xC0);
                        adda_s(f2, f7);
                        msub_s(f0, f6, f1);
                        swc1(f0, sp, 0xC4);
                        adda_s(f2, f4);
                        msub_s(f0, f3, f1);
                        swc1(f0, sp, 0xC8);
                        a0 = addiu(sp, 0xC0);
                        a1 = a0;
                        jal(ctx, 0x24E708u, gen::fn_sub_4C69F0_004c69f0);
                        lwc1(f5, sp, 0xC4);
                        lwc1(f4, sp, 0xC0);
                        lwc1(f3, sp, 0xC8);
                        lwc1(f2, sp, 0xB0);
                        mula_s(f5, f21);
                        mtc1(zero, f1);
                        madda_s(f4, f2);
                        madd_s(f6, f3, f20);
                        v0 = lui(0xBF80);
                        mtc1(v0, f0);
                        c_eq_s(f0, f6);
                        if (!cond(ctx)) {
                            // 0x0024e748
                            charge(ctx, 6);
                            v0 = 0x3F800000;
                            mtc1(v0, f0);
                            c_eq_s(f0, f6);
                            if (cond(ctx)) {
                                goto L_0024e760;
                            }
                            // 0x0024e778
                            charge(ctx, 12);
                            mul_s(f0, f5, f20);
                            adda_s(f1, f0);
                            msub_s(f0, f3, f21);
                            swc1(f0, sp, 0xA0);
                            mul_s(f0, f3, f2);
                            adda_s(f1, f0);
                            msub_s(f0, f4, f20);
                            swc1(f0, sp, 0xA4);
                            mul_s(f0, f4, f21);
                            adda_s(f1, f0);
                            msub_s(f0, f5, f2);
                            swc1(f0, sp, 0xA8);
                            goto L_0024e7a8;
                        }
                    L_0024e760:
                        charge(ctx, 6);
                        sw(zero, sp, 0xA0);
                        v0 = 0x3F800000;
                        sw(v0, sp, 0xA4);
                        sw(zero, sp, 0xA8);
                    L_0024e7a8:
                        charge(ctx, 32);
                        v0 = 0x43340000;
                        mtc1(v0, f1);
                        v0 = 0x3F800000;
                        mtc1(v0, f0);
                        sub_s(f0, f6, f0);
                        mul_s(f1, f1, f0);
                        v0 = 0x40000000;
                        mtc1(v0, f0);
                        div_s(f12, f1, f0);
                        a0 = addiu(s1, 20);
                        a1 = addiu(sp, 0xA0);
                        a2 = 0;
                        jal(ctx, 0x24E7E0u, gen::fn_sub_4BDDE0_004bdde0);
                        lwc1(f7, sp, 0xC4);
                        lwc1(f6, sp, 0xD4);
                        lwc1(f5, sp, 0xC0);
                        lwc1(f4, sp, 0xD0);
                        lwc1(f3, sp, 0xC8);
                        lwc1(f2, sp, 0xD8);
                        mula_s(f6, f7);
                        mtc1(zero, f1);
                        madda_s(f4, f5);
                        madd_s(f8, f2, f3);
                        v0 = lui(0xBF80);
                        mtc1(v0, f0);
                        c_eq_s(f0, f8);
                        if (!cond(ctx)) {
                            // 0x0024e828
                            charge(ctx, 6);
                            v0 = 0x3F800000;
                            mtc1(v0, f0);
                            c_eq_s(f0, f8);
                            if (cond(ctx)) {
                                goto L_0024e840;
                            }
                            // 0x0024e858
                            charge(ctx, 12);
                            mul_s(f0, f6, f3);
                            adda_s(f1, f0);
                            msub_s(f0, f2, f7);
                            swc1(f0, sp, 0xA0);
                            mul_s(f0, f2, f5);
                            adda_s(f1, f0);
                            msub_s(f0, f4, f3);
                            swc1(f0, sp, 0xA4);
                            mul_s(f0, f4, f7);
                            adda_s(f1, f0);
                            msub_s(f0, f6, f5);
                            swc1(f0, sp, 0xA8);
                            goto L_0024e888;
                        }
                    L_0024e840:
                        charge(ctx, 6);
                        sw(zero, sp, 0xA0);
                        v0 = 0x3F800000;
                        sw(v0, sp, 0xA4);
                        sw(zero, sp, 0xA8);
                    L_0024e888:
                        charge(ctx, 18);
                        v0 = 0x43340000;
                        mtc1(v0, f1);
                        v0 = 0x3F800000;
                        mtc1(v0, f0);
                        sub_s(f0, f8, f0);
                        mul_s(f1, f1, f0);
                        v0 = 0x40000000;
                        mtc1(v0, f0);
                        div_s(f12, f1, f0);
                        a0 = addiu(s1, 20);
                        a1 = addiu(sp, 0xA0);
                        a2 = 2;
                        jal(ctx, 0x24E8C0u, gen::fn_sub_4BDDE0_004bdde0);
                        goto L_0024f02c;
                    }
                }
            } else {
                // 0x0024dd7c: kind 1, a direction (mode +32 = 1)
                charge(ctx, 3);
                a1 = 1;
                if (v1 == a1) {
                    // 0x0024e484
                    charge(ctx, 3);
                    lw(v1, s1, pose::kPosMode);
                    if (v1 != a1) {
                        // 0x0024e490
                        charge(ctx, 2);
                        if (v1 != 0) {
                            // 0x0024e498
                            charge(ctx, 2);
                            // 0x0024e588
                            charge(ctx, 7);
                            a0 = 0x690000;
                            a0 = addiu(a0, -5728);  // "gc_pose.c"
                            a1 = 425;
                            jal(ctx, 0x24E594u, gen::fn_sub_19D3F0_0019d3f0);
                        }
                        goto L_0024f02c;
                    }
                    // 0x0024e4a0: its two position children (+36 / +40) are evaluated first
                    charge(ctx, 5);
                    s3 = addiu(s1, 36);
                    a0 = 0;
                    s4 = 0;
                    for (;;) {
                        // 0x0024e51c
                        charge(ctx, 3);
                        v1 = slti(s4, 2);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0024e4b4
                        charge(ctx, 8);
                        v1 = sll(s4, 2);
                        s2 = addu(s3, v1);
                        lw(v1, s2, 0);
                        lw(v1, v1, 8);
                        v1 = nor(v1, 0);
                        v1 = v1 & 0x2;
                        if (v1 == 0) {
                            // 0x0024e4d4
                            charge(ctx, 4);
                            lw(v1, s0, gcpose::kDepth);
                            v1 = slti(v1, 128);
                            if (v1 == 0) {
                                // 0x0024e4e4
                                charge(ctx, 5);
                                a0 = 0x690000;
                                a0 = addiu(a0, -5728);  // "gc_pose.c"
                                a1 = 408;
                                jal(ctx, 0x24E4F0u, gen::fn_sub_19D3F0_0019d3f0);
                            }
                            // 0x0024e4f8
                            charge(ctx, 8);
                            lw(a1, s2, 0);
                            lw(a0, s0, gcpose::kDepth);
                            v1 = addiu(a0, 1);
                            sw(v1, s0, gcpose::kDepth);
                            v1 = sll(a0, 2);
                            v1 = addu(s0, v1);
                            sw(a1, v1, 8);
                            a0 = 1;
                        }
                        // 0x0024e518
                        charge(ctx, 1);
                        s4 = addiu(s4, 1);
                    }
                    // 0x0024e528: the value = the second position minus the first (sub_24F960)
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x0024e530
                        charge(ctx, 22);
                        lw(a0, s3, 0);
                        a1 = addiu(sp, 0x110);
                        jal(ctx, 0x24E538u, gen::fn_sub_24F960_0024f960);
                        lw(a0, s3, 4);
                        a1 = addiu(sp, 0x100);
                        jal(ctx, 0x24E548u, gen::fn_sub_24F960_0024f960);
                        lwc1(f1, sp, 0x100);
                        lwc1(f0, sp, 0x110);
                        sub_s(f0, f1, f0);
                        swc1(f0, s1, pose::kValue);
                        lwc1(f1, sp, 0x104);
                        lwc1(f0, sp, 0x114);
                        sub_s(f0, f1, f0);
                        swc1(f0, s1, pose::kValue + 4);
                        lwc1(f1, sp, 0x108);
                        lwc1(f0, sp, 0x118);
                        sub_s(f0, f1, f0);
                        swc1(f0, s1, pose::kValue + 8);
                        goto L_0024f02c;
                    }
                } else {
                    // 0x0024dd88
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x0024dd90
                        charge(ctx, 2);
                        // 0x0024f018
                        charge(ctx, 5);
                        a0 = 0x690000;
                        a0 = addiu(a0, -5728);  // "gc_pose.c"
                        a1 = 683;
                        jal(ctx, 0x24F024u, gen::fn_sub_19D3F0_0019d3f0);
                        goto L_0024f02c;
                    }
                    // 0x0024dd98: kind 0, a position: by its mode (+32)
                    charge(ctx, 4);
                    lw(a0, s1, pose::kPosMode);
                    v1 = 3;
                    if (a0 == v1) {
                        // 0x0024e274: mode 3, a timed move: a running move clamps the time to its duration (+44)
                        charge(ctx, 5);
                        a2 = addiu(s1, 36);
                        lw(v1, s1, pose::kW40);
                        v1 = v1 & 0x1;
                        if (v1 != 0) {
                            // 0x0024e288
                            charge(ctx, 5);
                            lw(a0, a2, 8);
                            lw(v1, s1, pose::kTime);
                            v1 = slt(v1, a0);
                            if (v1 == 0) {
                                // 0x0024e29c
                                charge(ctx, 1);
                                sw(a0, s1, pose::kTime);
                            }
                        }
                        // 0x0024e2a0: curve 1: start + (velocity + acceleration * t / 2) * t (t = time / 1966080:
                        // seconds); curve 0: the lerp start -> end by time / duration
                        charge(ctx, 4);
                        lw(v1, a2, 4);
                        v1 = v1 & 0x1;
                        if (v1 != 0) {
                            // 0x0024e2b0
                            charge(ctx, 4);
                            lw(a0, a2, 0);
                            v1 = 1;
                            if (a0 == v1) {
                                // 0x0024e390
                                charge(ctx, 40);
                                lwc1(f0, s1, pose::kTime);
                                cvt_s_w(f1, f0);
                                v1 = 0x49F00000;
                                mtc1(v1, f0);
                                div_s(f4, f1, f0);
                                v1 = 0x3F000000;
                                mtc1(v1, f0);
                                mul_s(f3, f0, f4);
                                lwc1(f0, a2, 12);
                                mul_s(f2, f0, f3);
                                lwc1(f0, a2, 16);
                                mul_s(f1, f0, f3);
                                lwc1(f0, a2, 20);
                                mul_s(f3, f0, f3);
                                lwc1(f0, a2, 24);
                                add_s(f2, f2, f0);
                                lwc1(f0, a2, 28);
                                add_s(f1, f1, f0);
                                lwc1(f0, a2, 32);
                                add_s(f0, f3, f0);
                                mul_s(f3, f2, f4);
                                mul_s(f2, f1, f4);
                                mul_s(f1, f0, f4);
                                lwc1(f0, a2, 36);
                                add_s(f0, f0, f3);
                                swc1(f0, sp, 0x110);
                                lwc1(f0, a2, 40);
                                add_s(f0, f0, f2);
                                swc1(f0, sp, 0x114);
                                lwc1(f0, a2, 44);
                                add_s(f0, f0, f1);
                                swc1(f0, sp, 0x118);
                                lwc1(f2, sp, 0x110);
                                lwc1(f1, sp, 0x114);
                                lwc1(f0, sp, 0x118);
                                swc1(f2, s1, pose::kValue);
                                swc1(f1, s1, pose::kValue + 4);
                                swc1(f0, s1, pose::kValue + 8);
                            } else {
                                // 0x0024e2c0
                                charge(ctx, 2);
                                if (a0 == 0) {
                                    // 0x0024e2d0
                                    charge(ctx, 48);
                                    lwc1(f0, s1, pose::kTime);
                                    cvt_s_w(f1, f0);
                                    lwc1(f0, a2, 8);
                                    cvt_s_w(f0, f0);
                                    div_s(f5, f1, f0);
                                    lwc1(f2, a2, 24);
                                    lwc1(f1, a2, 28);
                                    lwc1(f0, a2, 32);
                                    swc1(f2, sp, 0x110);
                                    swc1(f1, sp, 0x114);
                                    swc1(f0, sp, 0x118);
                                    lwc1(f2, a2, 12);
                                    lwc1(f1, a2, 16);
                                    lwc1(f0, a2, 20);
                                    swc1(f2, sp, 0x100);
                                    swc1(f1, sp, 0x104);
                                    swc1(f0, sp, 0x108);
                                    lwc1(f1, a2, 24);
                                    lwc1(f0, sp, 0x100);
                                    sub_s(f4, f0, f1);
                                    swc1(f4, sp, 0x100);
                                    lwc1(f1, a2, 28);
                                    lwc1(f0, sp, 0x104);
                                    sub_s(f3, f0, f1);
                                    swc1(f3, sp, 0x104);
                                    lwc1(f1, a2, 32);
                                    lwc1(f0, sp, 0x108);
                                    sub_s(f2, f0, f1);
                                    swc1(f2, sp, 0x108);
                                    mul_s(f1, f4, f5);
                                    swc1(f1, sp, 0x100);
                                    mul_s(f0, f3, f5);
                                    swc1(f0, sp, 0x104);
                                    mul_s(f0, f2, f5);
                                    swc1(f0, sp, 0x108);
                                    lwc1(f0, sp, 0x110);
                                    add_s(f0, f1, f0);
                                    swc1(f0, s1, pose::kValue);
                                    lwc1(f1, sp, 0x104);
                                    lwc1(f0, sp, 0x114);
                                    add_s(f0, f1, f0);
                                    swc1(f0, s1, pose::kValue + 4);
                                    lwc1(f1, sp, 0x108);
                                    lwc1(f0, sp, 0x118);
                                    add_s(f0, f1, f0);
                                    swc1(f0, s1, pose::kValue + 8);
                                } else {
                                    // 0x0024e2c8
                                    charge(ctx, 2);
                                }
                            }
                        }
                        // 0x0024e430: past the duration the move stops (+40 bit 1)
                        charge(ctx, 4);
                        lw(a1, a2, 4);
                        v1 = a1 & 0x1;
                        if (v1 != 0) {
                            // 0x0024e440
                            charge(ctx, 5);
                            lw(a0, s1, pose::kTime);
                            lw(v1, a2, 8);
                            v1 = slt(a0, v1);
                            if (v1 == 0) {
                                // 0x0024e454
                                charge(ctx, 5);
                                v1 = si(-2);
                                v1 = a1 & v1;
                                sw(v1, a2, 4);
                            }
                        }
                        goto L_0024f02c;
                    }
                    // 0x0024dda8
                    charge(ctx, 2);
                    if (a0 != a2) {
                        // 0x0024ddb0
                        charge(ctx, 2);
                        if (a0 != 0) {
                            // 0x0024ddb8
                            charge(ctx, 2);
                            if (a0 == a1) {
                                // 0x0024ddc8: mode 1, a wander: every +88 frames a new random target within +-range /
                                // 2 (+84) and the spline toward it
                                charge(ctx, 16);
                                s2 = addiu(s1, 36);
                                lw(v1, s1, pose::kW88);
                                a0 = sll(v1, 16);
                                lw(v1, s1, pose::kTime);
                                mtc1(v1, f0);
                                cvt_s_w(f1, f0);
                                mtc1(a0, f0);
                                cvt_s_w(f0, f0);
                                div_s(f2, f1, f0);
                                v1 = slt(v1, a0);
                                if (v1 == 0) {
                                    // 0x0024de08
                                    charge(ctx, 30);
                                    lwc1(f1, s2, 24);
                                    lwc1(f0, s2, 36);
                                    sub_s(f3, f1, f0);
                                    swc1(f3, sp, 0x110);
                                    lwc1(f1, s2, 28);
                                    lwc1(f0, s2, 40);
                                    sub_s(f2, f1, f0);
                                    swc1(f2, sp, 0x114);
                                    lwc1(f1, s2, 32);
                                    lwc1(f0, s2, 44);
                                    sub_s(f1, f1, f0);
                                    swc1(f1, sp, 0x118);
                                    neg_s(f0, f3);
                                    swc1(f0, sp, 0xF0);
                                    neg_s(f0, f2);
                                    swc1(f0, sp, 0xF4);
                                    neg_s(f0, f1);
                                    swc1(f0, sp, 0xF8);
                                    lwc1(f2, s2, 36);
                                    lwc1(f1, s2, 40);
                                    lwc1(f0, s2, 44);
                                    swc1(f2, s2, 0);
                                    swc1(f1, s2, 4);
                                    swc1(f0, s2, 8);
                                    lwc1(f22, s2, 48);
                                    jal(ctx, 0x24DE6Cu, gen::fn_sub_488F30_00488f30);
                                    v0 = v0 & 0xFFF;
                                    if (i64(v0) < 0) {
                                        // 0x0024de94
                                        charge(ctx, 7);
                                        v1 = srl(v0, 1);
                                        v0 = v0 & 0x1;
                                        v1 = v1 | v0;
                                        mtc1(v1, f0);
                                        cvt_s_w(f0, f0);
                                        add_s(f0, f0, f0);
                                    } else {
                                        // 0x0024de80
                                        charge(ctx, 5);
                                        mtc1(v0, f0);
                                        cvt_s_w(f0, f0);
                                    }
                                    // 0x0024deb0
                                    charge(ctx, 17);
                                    mul_s(f1, f22, f0);
                                    v0 = 0x45800000;
                                    mtc1(v0, f0);
                                    div_s(f1, f1, f0);
                                    v0 = 0x40000000;
                                    mtc1(v0, f0);
                                    div_s(f0, f22, f0);
                                    sub_s(f0, f0, f1);
                                    swc1(f0, sp, 0x110);
                                    lwc1(f22, s2, 48);
                                    jal(ctx, 0x24DEE0u, gen::fn_sub_488F30_00488f30);
                                    v0 = v0 & 0xFFF;
                                    if (i64(v0) < 0) {
                                        // 0x0024df08
                                        charge(ctx, 7);
                                        v1 = srl(v0, 1);
                                        v0 = v0 & 0x1;
                                        v1 = v1 | v0;
                                        mtc1(v1, f0);
                                        cvt_s_w(f0, f0);
                                        add_s(f0, f0, f0);
                                    } else {
                                        // 0x0024def4
                                        charge(ctx, 5);
                                        mtc1(v0, f0);
                                        cvt_s_w(f0, f0);
                                    }
                                    // 0x0024df24
                                    charge(ctx, 17);
                                    mul_s(f1, f22, f0);
                                    v0 = 0x45800000;
                                    mtc1(v0, f0);
                                    div_s(f1, f1, f0);
                                    v0 = 0x40000000;
                                    mtc1(v0, f0);
                                    div_s(f0, f22, f0);
                                    sub_s(f0, f0, f1);
                                    swc1(f0, sp, 0x114);
                                    lwc1(f22, s2, 48);
                                    jal(ctx, 0x24DF54u, gen::fn_sub_488F30_00488f30);
                                    v0 = v0 & 0xFFF;
                                    if (i64(v0) < 0) {
                                        // 0x0024df7c
                                        charge(ctx, 7);
                                        v1 = srl(v0, 1);
                                        v0 = v0 & 0x1;
                                        v1 = v1 | v0;
                                        mtc1(v1, f0);
                                        cvt_s_w(f0, f0);
                                        add_s(f0, f0, f0);
                                    } else {
                                        // 0x0024df68
                                        charge(ctx, 5);
                                        mtc1(v0, f0);
                                        cvt_s_w(f0, f0);
                                    }
                                    // 0x0024df98
                                    charge(ctx, 30);
                                    mul_s(f1, f22, f0);
                                    v0 = 0x45800000;
                                    mtc1(v0, f0);
                                    div_s(f1, f1, f0);
                                    v0 = 0x40000000;
                                    mtc1(v0, f0);
                                    div_s(f0, f22, f0);
                                    sub_s(f0, f0, f1);
                                    swc1(f0, sp, 0x118);
                                    lwc1(f2, sp, 0x110);
                                    lwc1(f1, sp, 0x114);
                                    lwc1(f0, sp, 0x118);
                                    swc1(f2, s2, 36);
                                    swc1(f1, s2, 40);
                                    swc1(f0, s2, 44);
                                    a0 = s1;
                                    a1 = addiu(sp, 0xF0);
                                    jal(ctx, 0x24DFE4u, gen::fn_sub_24F7F0_0024f7f0);
                                    sw(zero, s1, pose::kTime);
                                    lwc1(f0, s1, pose::kTime);
                                    cvt_s_w(f1, f0);
                                    lw(v1, s2, 52);
                                    v1 = sll(v1, 16);
                                    mtc1(v1, f0);
                                    cvt_s_w(f0, f0);
                                    div_s(f2, f1, f0);
                                }
                                // 0x0024e010: the wander point along the spline, times the scale (+96)
                                charge(ctx, 77);
                                v1 = 0x3F800000;
                                mtc1(v1, f0);
                                sub_s(f1, f0, f2);
                                lwc1(f0, s2, 36);
                                mul_s(f0, f0, f2);
                                mul_s(f6, f2, f0);
                                v1 = 0x40400000;
                                mtc1(v1, f0);
                                lwc1(f3, s2, 24);
                                mul_s(f3, f0, f3);
                                mul_s(f3, f3, f2);
                                mul_s(f5, f2, f3);
                                lwc1(f3, s2, 0);
                                mul_s(f3, f3, f1);
                                mul_s(f4, f1, f3);
                                lwc1(f3, s2, 12);
                                mul_s(f3, f0, f3);
                                mul_s(f3, f3, f2);
                                mul_s(f3, f1, f3);
                                mula_s(f1, f3);
                                madda_s(f1, f4);
                                madda_s(f1, f5);
                                madd_s(f3, f2, f6);
                                swc1(f3, s1, pose::kValue);
                                lwc1(f3, s2, 40);
                                mul_s(f3, f3, f2);
                                mul_s(f6, f2, f3);
                                lwc1(f3, s2, 28);
                                mul_s(f3, f0, f3);
                                mul_s(f3, f3, f2);
                                mul_s(f5, f2, f3);
                                lwc1(f3, s2, 4);
                                mul_s(f3, f3, f1);
                                mul_s(f4, f1, f3);
                                lwc1(f3, s2, 16);
                                mul_s(f3, f0, f3);
                                mul_s(f3, f3, f2);
                                mul_s(f3, f1, f3);
                                mula_s(f1, f3);
                                madda_s(f1, f4);
                                madda_s(f1, f5);
                                madd_s(f3, f2, f6);
                                swc1(f3, s1, pose::kValue + 4);
                                lwc1(f3, s2, 44);
                                mul_s(f3, f3, f2);
                                mul_s(f6, f2, f3);
                                lwc1(f3, s2, 32);
                                mul_s(f3, f0, f3);
                                mul_s(f3, f3, f2);
                                mul_s(f5, f2, f3);
                                lwc1(f3, s2, 8);
                                mul_s(f3, f3, f1);
                                mul_s(f4, f1, f3);
                                lwc1(f3, s2, 20);
                                mul_s(f0, f0, f3);
                                mul_s(f0, f0, f2);
                                mul_s(f0, f1, f0);
                                mula_s(f1, f0);
                                madda_s(f1, f4);
                                madda_s(f1, f5);
                                madd_s(f0, f2, f6);
                                swc1(f0, s1, pose::kValue + 8);
                                lwc1(f1, s1, pose::kValue);
                                lwc1(f0, s2, 60);
                                mul_s(f0, f1, f0);
                                swc1(f0, s1, pose::kValue);
                                lwc1(f1, s1, pose::kValue + 4);
                                lwc1(f0, s2, 60);
                                mul_s(f0, f1, f0);
                                swc1(f0, s1, pose::kValue + 4);
                                lwc1(f1, s1, pose::kValue + 8);
                                lwc1(f0, s2, 60);
                                mul_s(f0, f1, f0);
                                swc1(f0, s1, pose::kValue + 8);
                            } else {
                                // 0x0024ddc0
                                charge(ctx, 2);
                                // 0x0024e468
                                charge(ctx, 7);
                                a0 = 0x690000;
                                a0 = addiu(a0, -5728);  // "gc_pose.c"
                                a1 = 381;
                                jal(ctx, 0x24E474u, gen::fn_sub_19D3F0_0019d3f0);
                            }
                        }
                        goto L_0024f02c;
                    }
                    // 0x0024e144: mode 2, a sum: the dirty children (+36..+44) are evaluated first
                    charge(ctx, 5);
                    s3 = addiu(s1, 36);
                    a0 = 0;
                    s4 = 0;
                    for (;;) {
                        // 0x0024e1c8
                        charge(ctx, 3);
                        v1 = slti(s4, 3);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0024e158
                        charge(ctx, 5);
                        v1 = sll(s4, 2);
                        s2 = addu(s3, v1);
                        lw(v1, s2, 0);
                        if (v1 != 0) {
                            // 0x0024e16c
                            charge(ctx, 5);
                            lw(v1, v1, 8);
                            v1 = nor(v1, 0);
                            v1 = v1 & 0x2;
                            if (v1 == 0) {
                                // 0x0024e180
                                charge(ctx, 4);
                                lw(v1, s0, gcpose::kDepth);
                                v1 = slti(v1, 128);
                                if (v1 == 0) {
                                    // 0x0024e190
                                    charge(ctx, 5);
                                    a0 = 0x690000;
                                    a0 = addiu(a0, -5728);  // "gc_pose.c"
                                    a1 = 306;
                                    jal(ctx, 0x24E19Cu, gen::fn_sub_19D3F0_0019d3f0);
                                }
                                // 0x0024e1a4
                                charge(ctx, 8);
                                lw(a1, s2, 0);
                                lw(a0, s0, gcpose::kDepth);
                                v1 = addiu(a0, 1);
                                sw(v1, s0, gcpose::kDepth);
                                v1 = sll(a0, 2);
                                v1 = addu(s0, v1);
                                sw(a1, v1, 8);
                                a0 = 1;
                            }
                        }
                        // 0x0024e1c4
                        charge(ctx, 1);
                        s4 = addiu(s4, 1);
                    }
                    // 0x0024e1d4: the value = the sum of the children's positions
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x0024e1dc
                        charge(ctx, 6);
                        sw(zero, sp, 0x110);
                        sw(zero, sp, 0x114);
                        sw(zero, sp, 0x118);
                        s2 = 0;
                        for (;;) {
                            // 0x0024e248
                            charge(ctx, 3);
                            v1 = slti(s2, 3);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0024e1f4
                            charge(ctx, 5);
                            v1 = sll(s2, 2);
                            v1 = addu(s3, v1);
                            lw(a0, v1, 0);
                            if (a0 != 0) {
                                // 0x0024e208
                                charge(ctx, 15);
                                a1 = addiu(sp, 0x100);
                                jal(ctx, 0x24E20Cu, gen::fn_sub_24F960_0024f960);
                                lwc1(f1, sp, 0x110);
                                lwc1(f0, sp, 0x100);
                                add_s(f0, f1, f0);
                                swc1(f0, sp, 0x110);
                                lwc1(f1, sp, 0x114);
                                lwc1(f0, sp, 0x104);
                                add_s(f0, f1, f0);
                                swc1(f0, sp, 0x114);
                                lwc1(f1, sp, 0x118);
                                lwc1(f0, sp, 0x108);
                                add_s(f0, f1, f0);
                                swc1(f0, sp, 0x118);
                            }
                            // 0x0024e244
                            charge(ctx, 1);
                            s2 = addiu(s2, 1);
                        }
                        // 0x0024e254
                        charge(ctx, 8);
                        lwc1(f2, sp, 0x110);
                        lwc1(f1, sp, 0x114);
                        lwc1(f0, sp, 0x118);
                        swc1(f2, s1, pose::kValue);
                        swc1(f1, s1, pose::kValue + 4);
                        swc1(f0, s1, pose::kValue + 8);
                        goto L_0024f02c;
                    }
                }
            }
            continue;
        }
    L_0024f02c:
        charge(ctx, 7);
        lw(a0, s1, pose::kFlags);
        v1 = si(-3);
        v1 = a0 & v1;
        sw(v1, s1, pose::kFlags);
        lw(v1, s0, gcpose::kDepth);
        v1 = addiu(v1, -1);
        sw(v1, s0, gcpose::kDepth);
    }
    // 0x0024f054
    charge(ctx, 12);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x120);
}

// 0x0024F210 sub_24F210 -- 164 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [gcPoseSetWander] Sets a wander position node's parameters (K_Assert 779 / 780: kind 0, mode 1): range +84 = f12,
// period +88 = a1 frames, +92 = f13; marks it dirty.
// Arguments: a0 node, a1 frames, f12 range, f13.
void sub_24F210(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0024f210
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s0 = a0;
    mov_s(f21, f12);
    s1 = a1;
    mov_s(f20, f13);
    lw(v1, a0, pose::kKind);
    if (v1 != 0) {
        // 0x0024f244
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 779;
        jal(ctx, 0x24F250u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024f258
    charge(ctx, 4);
    lw(a0, s0, pose::kPosMode);
    v1 = 1;
    if (a0 != v1) {
        // 0x0024f268
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 780;
        jal(ctx, 0x24F274u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024f27c (the shared epilogue, written out on this path)
    charge(ctx, 14);
    swc1(f21, s0, pose::kW84);
    sw(s1, s0, pose::kW88);
    swc1(f20, s0, pose::kW92);
    lw(v1, s0, pose::kFlags);
    v1 = v1 | 0x2;
    sw(v1, s0, pose::kFlags);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0024F2C0 sub_24F2C0 -- 132 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// [gcPoseSetWanderScale] Sets a wander position node's scale (+96 = f12; K_Assert 795 / 796) and marks it dirty.
// Arguments: a0 node, f12 scale.
void sub_24F2C0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x0024f2c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a0;
    mov_s(f20, f12);
    lw(v1, a0, pose::kKind);
    if (v1 != 0) {
        // 0x0024f2e4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 795;
        jal(ctx, 0x24F2F0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024f2f8
    charge(ctx, 4);
    lw(a0, s0, pose::kPosMode);
    v1 = 1;
    if (a0 != v1) {
        // 0x0024f308
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 796;
        jal(ctx, 0x24F314u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024f31c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    swc1(f20, s0, pose::kW96);
    lw(v1, s0, pose::kFlags);
    v1 = v1 | 0x2;
    sw(v1, s0, pose::kFlags);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0024F350 sub_24F350 -- 188 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcPoseWanderRestart] Restarts a wander position node (K_Assert 809 / 810) with the defaults range 10.0, period
// 180, +92 10.0, scale 1.0: new random start / target (gcPoseWanderPick) and the spline from (0, 0, +92)
// (gcPoseWanderSpline).
// Arguments: a0 node.
void sub_24F350(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0024f350
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, pose::kKind);
    if (v0 != 0) {
        // 0x0024f370
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 809;
        jal(ctx, 0x24F37Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024f384
    charge(ctx, 4);
    lw(v1, s0, pose::kPosMode);
    v0 = 1;
    if (v1 != v0) {
        // 0x0024f394
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 810;
        jal(ctx, 0x24F3A0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024f3a8
    charge(ctx, 25);
    s1 = addiu(s0, 36);
    v1 = 0x41200000;
    sw(v1, s0, pose::kW84);
    v0 = 180;
    sw(v0, s0, pose::kW88);
    sw(v1, s0, pose::kW92);
    v0 = 0x3F800000;
    sw(v0, s0, pose::kW96);
    a0 = s0;
    jal(ctx, 0x24F3CCu, gen::fn_sub_24F410_0024f410);
    sw(zero, sp, 0x30);
    sw(zero, sp, 0x34);
    lwc1(f0, s1, 56);
    swc1(f0, sp, 0x38);
    a0 = s0;
    a1 = addiu(sp, 0x30);
    jal(ctx, 0x24F3ECu, gen::fn_sub_24F7F0_0024f7f0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0024F410 sub_24F410 -- 868 bytes; frame 0x50: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [gcPoseWanderPick] Picks a wander position node's current and target points (K_Assert 833 / 834): +36..+44 and
// +72..+80, each axis range/2 - range * (rand() & 0xFFF) / 4096 (libc rand, sub_488F30).
// Arguments: a0 node.
void sub_24F410(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20};
    // 0x0024f410
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    lw(v0, a0, pose::kKind);
    if (v0 != 0) {
        // 0x0024f434
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 833;
        jal(ctx, 0x24F440u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024f448
    charge(ctx, 4);
    lw(v1, s1, pose::kPosMode);
    v0 = 1;
    if (v1 != v0) {
        // 0x0024f458
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 834;
        jal(ctx, 0x24F464u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024f46c
    charge(ctx, 7);
    s0 = addiu(s1, 36);
    lwc1(f20, s1, pose::kW84);
    jal(ctx, 0x24F474u, gen::fn_sub_488F30_00488f30);
    v0 = v0 & 0xFFF;
    if (i64(v0) < 0) {
        // 0x0024f49c
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0024f488
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0024f4b8
    charge(ctx, 17);
    mul_s(f1, f20, f0);
    v0 = 0x45800000;
    mtc1(v0, f0);
    div_s(f1, f1, f0);
    v0 = 0x40000000;
    mtc1(v0, f0);
    div_s(f0, f20, f0);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x40);
    lwc1(f20, s0, 48);
    jal(ctx, 0x24F4E8u, gen::fn_sub_488F30_00488f30);
    v0 = v0 & 0xFFF;
    if (i64(v0) < 0) {
        // 0x0024f510
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0024f4fc
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0024f52c
    charge(ctx, 17);
    mul_s(f1, f20, f0);
    v0 = 0x45800000;
    mtc1(v0, f0);
    div_s(f1, f1, f0);
    v0 = 0x40000000;
    mtc1(v0, f0);
    div_s(f0, f20, f0);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x44);
    lwc1(f20, s0, 48);
    jal(ctx, 0x24F55Cu, gen::fn_sub_488F30_00488f30);
    v0 = v0 & 0xFFF;
    if (i64(v0) < 0) {
        // 0x0024f584
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0024f570
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0024f5a0
    charge(ctx, 23);
    mul_s(f1, f20, f0);
    v0 = 0x45800000;
    mtc1(v0, f0);
    div_s(f1, f1, f0);
    v0 = 0x40000000;
    mtc1(v0, f0);
    div_s(f0, f20, f0);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x48);
    lwc1(f2, sp, 0x40);
    lwc1(f1, sp, 0x44);
    lwc1(f0, sp, 0x48);
    swc1(f2, s0, 0);
    swc1(f1, s0, 4);
    swc1(f0, s0, 8);
    lwc1(f20, s0, 48);
    jal(ctx, 0x24F5E8u, gen::fn_sub_488F30_00488f30);
    v0 = v0 & 0xFFF;
    if (i64(v0) < 0) {
        // 0x0024f610
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0024f5fc
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0024f62c
    charge(ctx, 17);
    mul_s(f1, f20, f0);
    v0 = 0x45800000;
    mtc1(v0, f0);
    div_s(f1, f1, f0);
    v0 = 0x40000000;
    mtc1(v0, f0);
    div_s(f0, f20, f0);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x40);
    lwc1(f20, s0, 48);
    jal(ctx, 0x24F65Cu, gen::fn_sub_488F30_00488f30);
    v0 = v0 & 0xFFF;
    if (i64(v0) < 0) {
        // 0x0024f684
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0024f670
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0024f6a0
    charge(ctx, 17);
    mul_s(f1, f20, f0);
    v0 = 0x45800000;
    mtc1(v0, f0);
    div_s(f1, f1, f0);
    v0 = 0x40000000;
    mtc1(v0, f0);
    div_s(f0, f20, f0);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x44);
    lwc1(f20, s0, 48);
    jal(ctx, 0x24F6D0u, gen::fn_sub_488F30_00488f30);
    v1 = v0 & 0xFFF;
    if (i64(v1) < 0) {
        // 0x0024f6f8
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0024f6e4
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0024f714 (the shared epilogue, written out on this path)
    charge(ctx, 24);
    mul_s(f1, f20, f0);
    v1 = 0x45800000;
    mtc1(v1, f0);
    div_s(f1, f1, f0);
    v1 = 0x40000000;
    mtc1(v1, f0);
    div_s(f0, f20, f0);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x48);
    lwc1(f2, sp, 0x40);
    lwc1(f1, sp, 0x44);
    lwc1(f0, sp, 0x48);
    swc1(f2, s0, 36);
    swc1(f1, s0, 40);
    swc1(f0, s0, 44);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0024F780 sub_24F780 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [gcPoseMoveStop] Stops a timed-move position node (K_Assert 853 / 854: kind 0, mode 3): +40 = 0.
// Arguments: a0 node.
void sub_24F780(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024f780
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, pose::kKind);
    if (v1 != 0) {
        // 0x0024f79c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 853;
        jal(ctx, 0x24F7A8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024f7b0
    charge(ctx, 4);
    lw(a0, s0, pose::kPosMode);
    v1 = 3;
    if (a0 != v1) {
        // 0x0024f7c0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 854;
        jal(ctx, 0x24F7CCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024f7d4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    sw(zero, s0, pose::kW40);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0024F7F0 sub_24F7F0 -- 368 bytes; frame 0x50: ra sp+0x10, s0 sp+0x0 (sq)
// [gcPoseWanderSpline] Builds a wander position node's spline toward its target (a0, a1 = the start tangent f32[3]):
// +48 = +36 + a1, the normalised chords to and from the target and their cross products give the control point +60 =
// +72 + (cross) * +92.
// Arguments: a0 node, a1 f32[3].
void sub_24F7F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7};
    // 0x0024f7f0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v1 = addiu(sp, 0x20);
    v0 = 12;
    if (v1 != 0) {
        for (;;) {
            // 0x0024f80c
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
    // 0x0024f828
    charge(ctx, 78);
    s0 = addiu(a0, 36);
    lwc1(f1, a0, pose::kW36);
    lwc1(f0, a1, 0);
    add_s(f0, f1, f0);
    swc1(f0, a0, pose::kW48);
    lwc1(f1, a0, pose::kW40);
    lwc1(f0, a1, 4);
    add_s(f0, f1, f0);
    swc1(f0, a0, 52);
    lwc1(f1, a0, pose::kW44);
    lwc1(f0, a1, 8);
    add_s(f0, f1, f0);
    swc1(f0, a0, 56);
    lwc1(f3, a0, pose::kW72);
    lwc1(f0, sp, 0x20);
    sub_s(f0, f0, f3);
    swc1(f0, sp, 0x40);
    lwc1(f2, a0, 76);
    lwc1(f0, sp, 0x24);
    sub_s(f0, f0, f2);
    swc1(f0, sp, 0x44);
    lwc1(f1, a0, 80);
    lwc1(f0, sp, 0x28);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x48);
    lwc1(f0, a0, pose::kW36);
    sub_s(f0, f3, f0);
    swc1(f0, sp, 0x30);
    lwc1(f0, a0, pose::kW40);
    sub_s(f0, f2, f0);
    swc1(f0, sp, 0x34);
    lwc1(f0, a0, pose::kW44);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x38);
    a0 = addiu(sp, 0x40);
    a1 = a0;
    jal(ctx, 0x24F8B8u, gen::fn_sub_4C69F0_004c69f0);
    a0 = addiu(sp, 0x30);
    a1 = a0;
    jal(ctx, 0x24F8C8u, gen::fn_sub_4C69F0_004c69f0);
    lwc1(f7, sp, 0x44);
    lwc1(f1, sp, 0x38);
    lwc1(f6, sp, 0x48);
    lwc1(f2, sp, 0x34);
    mula_s(f2, f6);
    msub_s(f5, f1, f7);
    lwc1(f0, sp, 0x30);
    lwc1(f4, sp, 0x40);
    mula_s(f1, f4);
    msub_s(f1, f0, f6);
    mula_s(f0, f7);
    msub_s(f0, f2, f4);
    mula_s(f1, f6);
    msub_s(f3, f0, f7);
    mula_s(f0, f4);
    msub_s(f2, f5, f6);
    mula_s(f5, f7);
    msub_s(f1, f1, f4);
    lwc1(f0, s0, 56);
    mul_s(f3, f3, f0);
    mul_s(f2, f2, f0);
    mul_s(f1, f1, f0);
    lwc1(f0, s0, 36);
    add_s(f0, f0, f3);
    swc1(f0, s0, 24);
    lwc1(f0, s0, 40);
    add_s(f0, f0, f2);
    swc1(f0, s0, 28);
    lwc1(f0, s0, 44);
    add_s(f0, f0, f1);
    swc1(f0, s0, 32);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0024FAA0 sub_24FAA0 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [gcPoseGetVector] A position or direction node's value (node + 20; K_Assert line 910 for an orientation).
// Arguments: a0 node.
void sub_24FAA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024faa0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, pose::kPosMode);
    v0 = slti(v0, 2);
    if (v0 == 0) {
        // 0x0024fac0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 910;
        jal(ctx, 0x24FACCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024fad4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = addiu(s0, 20);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0024FBA0 sub_24FBA0 -- 152 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcPoseGetQuat] Copies an orientation node's quaternion (+20..+32) to a1 (K_Assert 934 / 935: kind 2, mode < 5).
// Arguments: a0 node, a1 out f32[4].
void sub_24FBA0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0024fba0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(a0, a0, pose::kKind);
    v1 = 2;
    if (a0 != v1) {
        // 0x0024fbc8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 934;
        jal(ctx, 0x24FBD4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024fbdc
    charge(ctx, 4);
    lw(v1, s1, pose::kW36);
    v1 = slti(v1, 5);
    if (v1 == 0) {
        // 0x0024fbec
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 935;
        jal(ctx, 0x24FBF8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024fc00 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    lwc1(f3, s1, pose::kValue);
    lwc1(f2, s1, pose::kValue + 4);
    lwc1(f1, s1, pose::kValue + 8);
    lwc1(f0, s1, pose::kPosMode);
    swc1(f3, s0, 0);
    swc1(f2, s0, 4);
    swc1(f1, s0, 8);
    swc1(f0, s0, 12);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0024FC40 sub_24FC40 -- 200 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcPoseSetQuat] Sets a fixed orientation node's quaternion from a1 (K_Assert 942 / 953: kind 2, modes 0..3).
// Arguments: a0 node, a1 f32[4].
void sub_24FC40(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0024fc40
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(a0, a0, pose::kKind);
    v1 = 2;
    if (a0 != v1) {
        // 0x0024fc68
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 942;
        jal(ctx, 0x24FC74u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024fc7c
    charge(ctx, 4);
    lw(a0, s1, pose::kW36);  // the orientation mode: 3, 2, 1 or 0 take the quaternion
    v1 = 3;
    bool accepted = true;
    if (a0 != v1) {
        // 0x0024fc8c
        charge(ctx, 3);
        v1 = 2;
        if (a0 != v1) {
            // 0x0024fc98
            charge(ctx, 3);
            v1 = 1;
            if (a0 != v1) {
                // 0x0024fca4
                charge(ctx, 2);
                accepted = a0 == 0;
            }
        }
    }
    if (!accepted) {
        // 0x0024fcac: K_Assert(line 953), nothing stored
        charge(ctx, 2);
        // 0x0024fcdc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 953;
        jal(ctx, 0x24FCE8u, gen::fn_sub_19D3F0_0019d3f0);
        // 0x0024fcf0 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x0024fcb4: the quaternion a1[0..3] -> the node's value
    charge(ctx, 10);
    lwc1(f3, s0, 0);
    lwc1(f2, s0, 4);
    lwc1(f1, s0, 8);
    lwc1(f0, s0, 12);
    swc1(f3, s1, pose::kValue);
    swc1(f2, s1, pose::kValue + 4);
    swc1(f1, s1, pose::kValue + 8);
    swc1(f0, s1, pose::kValue + 12);
    // 0x0024fcf0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0024FD10 sub_24FD10 -- 16 bytes; leaf frame (no stack)
// [gcPoseInitFixed] Makes a0 a fixed position node (kind 0, mode 0).
// Arguments: a0 node.
void sub_24FD10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x0024fd10
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, pose::kKind);
    sw(zero, a0, pose::kPosMode);
}

// 0x0024FD20 sub_24FD20 -- 20 bytes; leaf frame (no stack)
// [gcPoseInitWander] Makes a0 a wander position node (kind 0, mode 1).
// Arguments: a0 node.
void sub_24FD20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0024fd20
    enter(ctx, 5);  // entry check point + this block's cycles
    sw(zero, a0, pose::kKind);
    v1 = 1;
    sw(v1, a0, pose::kPosMode);
}

// 0x0024FD40 sub_24FD40 -- 64 bytes; leaf frame (no stack)
// [gcPoseInitSum] Makes a0 a sum position node (kind 0, mode 2) with no children.
// Arguments: a0 node.
void sub_24FD40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0024fd40
    enter(ctx, 7);  // entry check point + this block's cycles
    sw(zero, a0, pose::kKind);
    v1 = 2;
    sw(v1, a0, pose::kPosMode);
    a0 = addiu(a0, 36);
    a1 = 0;
    for (;;) {
        // 0x0024fd6c
        charge(ctx, 3);
        v1 = slti(a1, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0024fd5c
        charge(ctx, 4);
        v1 = sll(a1, 2);
        v1 = addu(a0, v1);
        sw(zero, v1, 0);
        a1 = addiu(a1, 1);
    }
    // 0x0024fd78
    charge(ctx, 2);
}

// 0x0024FD80 sub_24FD80 -- 20 bytes; leaf frame (no stack)
// [gcPoseInitMove] Makes a0 a timed-move position node (kind 0, mode 3).
// Arguments: a0 node.
void sub_24FD80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0024fd80
    enter(ctx, 5);  // entry check point + this block's cycles
    sw(zero, a0, pose::kKind);
    v1 = 3;
    sw(v1, a0, pose::kPosMode);
}

// 0x0024FDC0 sub_24FDC0 -- 64 bytes; leaf frame (no stack)
// [gcPoseInitProduct] Makes a0 a product orientation node (kind 2, mode 2) with no children.
// Arguments: a0 node.
void sub_24FDC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0024fdc0
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = 2;
    sw(v1, a0, pose::kKind);
    sw(v1, a0, pose::kW36);
    a0 = addiu(a0, 40);
    a1 = 0;
    for (;;) {
        // 0x0024fdec
        charge(ctx, 3);
        v1 = slti(a1, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0024fddc
        charge(ctx, 4);
        v1 = sll(a1, 2);
        v1 = addu(a0, v1);
        sw(zero, v1, 0);
        a1 = addiu(a1, 1);
    }
    // 0x0024fdf8
    charge(ctx, 2);
}

// 0x0024FE20 sub_24FE20 -- 24 bytes; leaf frame (no stack)
// [gcPoseInitWobble] Makes a0 a wobble orientation node (kind 2, mode 4).
// Arguments: a0 node.
void sub_24FE20(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x0024fe20
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 2;
    sw(v1, a0, pose::kKind);
    v1 = 4;
    sw(v1, a0, pose::kW36);
}

// 0x0024FE40 sub_24FE40 -- 204 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcPoseWobbleRestart] Restarts a wobble orientation node (K_Assert 1051 / 1052) with the defaults ranges (5.0,
// 15.0, 15.0), period 180, +104 1.0, scale 1.0: new random angles (gcPoseWobblePick) and the spline from (0, 0,
// +104).
// Arguments: a0 node.
void sub_24FE40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0024fe40
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, pose::kKind);
    v0 = 2;
    if (v1 != v0) {
        // 0x0024fe64
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1051;
        jal(ctx, 0x24FE70u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024fe78
    charge(ctx, 4);
    lw(v1, s0, pose::kW36);
    v0 = 4;
    if (v1 != v0) {
        // 0x0024fe88
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1052;
        jal(ctx, 0x24FE94u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024fe9c
    charge(ctx, 28);
    s1 = addiu(s0, 40);
    v0 = 0x40A00000;
    sw(v0, s0, pose::kW88);
    v0 = 0x41700000;
    sw(v0, s0, pose::kW92);
    sw(v0, s0, pose::kW96);
    v0 = 180;
    sw(v0, s0, pose::kW100);
    v0 = 0x3F800000;
    sw(v0, s0, pose::kW104);
    sw(v0, s0, pose::kW108);
    a0 = s0;
    jal(ctx, 0x24FECCu, gen::fn_sub_24FF10_0024ff10);
    sw(zero, sp, 0x30);
    sw(zero, sp, 0x34);
    lwc1(f0, s1, 64);
    swc1(f0, sp, 0x38);
    a0 = s0;
    a1 = addiu(sp, 0x30);
    jal(ctx, 0x24FEECu, gen::fn_sub_250280_00250280);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0024FF10 sub_24FF10 -- 872 bytes; frame 0x50: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [gcPoseWobblePick] Picks a wobble orientation node's current and target angles (K_Assert 1076 / 1077): +40..+48 and
// +76..+84, each range/2 - range * (rand() & 0xFFF) / 4096 with the per-axis ranges +88..+96.
// Arguments: a0 node.
void sub_24FF10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20};
    // 0x0024ff10
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    lw(v1, a0, pose::kKind);
    v0 = 2;
    if (v1 != v0) {
        // 0x0024ff38
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1076;
        jal(ctx, 0x24FF44u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024ff4c
    charge(ctx, 4);
    lw(v1, s1, pose::kW36);
    v0 = 4;
    if (v1 != v0) {
        // 0x0024ff5c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1077;
        jal(ctx, 0x24FF68u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024ff70
    charge(ctx, 7);
    s0 = addiu(s1, 40);
    lwc1(f20, s1, pose::kW88);
    jal(ctx, 0x24FF78u, gen::fn_sub_488F30_00488f30);
    v0 = v0 & 0xFFF;
    if (i64(v0) < 0) {
        // 0x0024ffa0
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0024ff8c
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0024ffbc
    charge(ctx, 17);
    mul_s(f1, f20, f0);
    v0 = 0x45800000;
    mtc1(v0, f0);
    div_s(f1, f1, f0);
    v0 = 0x40000000;
    mtc1(v0, f0);
    div_s(f0, f20, f0);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x40);
    lwc1(f20, s0, 52);
    jal(ctx, 0x24FFECu, gen::fn_sub_488F30_00488f30);
    v0 = v0 & 0xFFF;
    if (i64(v0) < 0) {
        // 0x00250014
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00250000
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00250030
    charge(ctx, 17);
    mul_s(f1, f20, f0);
    v0 = 0x45800000;
    mtc1(v0, f0);
    div_s(f1, f1, f0);
    v0 = 0x40000000;
    mtc1(v0, f0);
    div_s(f0, f20, f0);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x44);
    lwc1(f20, s0, 56);
    jal(ctx, 0x250060u, gen::fn_sub_488F30_00488f30);
    v0 = v0 & 0xFFF;
    if (i64(v0) < 0) {
        // 0x00250088
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00250074
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002500a4
    charge(ctx, 23);
    mul_s(f1, f20, f0);
    v0 = 0x45800000;
    mtc1(v0, f0);
    div_s(f1, f1, f0);
    v0 = 0x40000000;
    mtc1(v0, f0);
    div_s(f0, f20, f0);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x48);
    lwc1(f2, sp, 0x40);
    lwc1(f1, sp, 0x44);
    lwc1(f0, sp, 0x48);
    swc1(f2, s0, 0);
    swc1(f1, s0, 4);
    swc1(f0, s0, 8);
    lwc1(f20, s0, 48);
    jal(ctx, 0x2500ECu, gen::fn_sub_488F30_00488f30);
    v0 = v0 & 0xFFF;
    if (i64(v0) < 0) {
        // 0x00250114
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00250100
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00250130
    charge(ctx, 17);
    mul_s(f1, f20, f0);
    v0 = 0x45800000;
    mtc1(v0, f0);
    div_s(f1, f1, f0);
    v0 = 0x40000000;
    mtc1(v0, f0);
    div_s(f0, f20, f0);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x40);
    lwc1(f20, s0, 52);
    jal(ctx, 0x250160u, gen::fn_sub_488F30_00488f30);
    v0 = v0 & 0xFFF;
    if (i64(v0) < 0) {
        // 0x00250188
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00250174
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002501a4
    charge(ctx, 17);
    mul_s(f1, f20, f0);
    v0 = 0x45800000;
    mtc1(v0, f0);
    div_s(f1, f1, f0);
    v0 = 0x40000000;
    mtc1(v0, f0);
    div_s(f0, f20, f0);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x44);
    lwc1(f20, s0, 56);
    jal(ctx, 0x2501D4u, gen::fn_sub_488F30_00488f30);
    v1 = v0 & 0xFFF;
    if (i64(v1) < 0) {
        // 0x002501fc
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002501e8
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00250218 (the shared epilogue, written out on this path)
    charge(ctx, 24);
    mul_s(f1, f20, f0);
    v1 = 0x45800000;
    mtc1(v1, f0);
    div_s(f1, f1, f0);
    v1 = 0x40000000;
    mtc1(v1, f0);
    div_s(f0, f20, f0);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x48);
    lwc1(f2, sp, 0x40);
    lwc1(f1, sp, 0x44);
    lwc1(f0, sp, 0x48);
    swc1(f2, s0, 36);
    swc1(f1, s0, 40);
    swc1(f0, s0, 44);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00250280 sub_250280 -- 368 bytes; frame 0x50: ra sp+0x10, s0 sp+0x0 (sq)
// [gcPoseWobbleSpline] Builds a wobble orientation node's spline toward its target angles (as gcPoseWanderSpline, one
// word further on: +52 = +40 + a1, control point +64 from +76, scale +104).
// Arguments: a0 node, a1 f32[3].
void sub_250280(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7};
    // 0x00250280
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v1 = addiu(sp, 0x20);
    v0 = 12;
    if (v1 != 0) {
        for (;;) {
            // 0x0025029c
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
    // 0x002502b8
    charge(ctx, 78);
    s0 = addiu(a0, 40);
    lwc1(f1, a0, pose::kW40);
    lwc1(f0, a1, 0);
    add_s(f0, f1, f0);
    swc1(f0, a0, 52);
    lwc1(f1, a0, pose::kW44);
    lwc1(f0, a1, 4);
    add_s(f0, f1, f0);
    swc1(f0, a0, 56);
    lwc1(f1, a0, pose::kW48);
    lwc1(f0, a1, 8);
    add_s(f0, f1, f0);
    swc1(f0, a0, pose::kW60);
    lwc1(f3, a0, 76);
    lwc1(f0, sp, 0x20);
    sub_s(f0, f0, f3);
    swc1(f0, sp, 0x40);
    lwc1(f2, a0, 80);
    lwc1(f0, sp, 0x24);
    sub_s(f0, f0, f2);
    swc1(f0, sp, 0x44);
    lwc1(f1, a0, pose::kW84);
    lwc1(f0, sp, 0x28);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x48);
    lwc1(f0, a0, pose::kW40);
    sub_s(f0, f3, f0);
    swc1(f0, sp, 0x30);
    lwc1(f0, a0, pose::kW44);
    sub_s(f0, f2, f0);
    swc1(f0, sp, 0x34);
    lwc1(f0, a0, pose::kW48);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x38);
    a0 = addiu(sp, 0x40);
    a1 = a0;
    jal(ctx, 0x250348u, gen::fn_sub_4C69F0_004c69f0);
    a0 = addiu(sp, 0x30);
    a1 = a0;
    jal(ctx, 0x250358u, gen::fn_sub_4C69F0_004c69f0);
    lwc1(f7, sp, 0x44);
    lwc1(f1, sp, 0x38);
    lwc1(f6, sp, 0x48);
    lwc1(f2, sp, 0x34);
    mula_s(f2, f6);
    msub_s(f5, f1, f7);
    lwc1(f0, sp, 0x30);
    lwc1(f4, sp, 0x40);
    mula_s(f1, f4);
    msub_s(f1, f0, f6);
    mula_s(f0, f7);
    msub_s(f0, f2, f4);
    mula_s(f1, f6);
    msub_s(f3, f0, f7);
    mula_s(f0, f4);
    msub_s(f2, f5, f6);
    mula_s(f5, f7);
    msub_s(f1, f1, f4);
    lwc1(f0, s0, 64);
    mul_s(f3, f3, f0);
    mul_s(f2, f2, f0);
    mul_s(f1, f1, f0);
    lwc1(f0, s0, 36);
    add_s(f0, f0, f3);
    swc1(f0, s0, 24);
    lwc1(f0, s0, 40);
    add_s(f0, f0, f2);
    swc1(f0, s0, 28);
    lwc1(f0, s0, 44);
    add_s(f0, f0, f1);
    swc1(f0, s0, 32);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002503F0 sub_2503F0 -- 140 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcPoseSetSumChild] Sets child a1 (0..2) of a sum position node to a2 (K_Assert 1116 / 1117).
// Arguments: a0 node, a1 index, a2 child node.
void sub_2503F0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002503f0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s2 = a1;
    s0 = a2;
    lw(a0, a0, pose::kPosMode);
    v1 = 2;
    if (a0 != v1) {
        // 0x00250420
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1116;
        jal(ctx, 0x25042Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250434
    charge(ctx, 3);
    v1 = slti(s2, 3);
    if (v1 == 0) {
        // 0x00250440
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1117;
        jal(ctx, 0x25044Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250454 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v1 = sll(s2, 2);
    v1 = addu(v1, s1);
    sw(s0, v1, 36);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00250480 sub_250480 -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [gcPoseMoveHalt] Stops a timed-move position node's run flag (+40 bit 1; K_Assert 1126 / 1127).
// Arguments: a0 node.
void sub_250480(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00250480
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, pose::kKind);
    if (v1 != 0) {
        // 0x0025049c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1126;
        jal(ctx, 0x2504A8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002504b0
    charge(ctx, 4);
    lw(a0, s0, pose::kPosMode);
    v1 = 3;
    if (a0 != v1) {
        // 0x002504c0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1127;
        jal(ctx, 0x2504CCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002504d4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a0, s0, pose::kW40);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, s0, pose::kW40);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00250500 sub_250500 -- 172 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcPoseMoveLinear] Starts a straight timed move of a position node (K_Assert line 1137: mode 3): kind 0 (lerp), the
// end +48 = a1, the start +60 = the current value, time 0, duration +44 = a2 frames (16.16), running.
// Arguments: a0 node, a1 f32[3] end, a2 frames.
void sub_250500(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x00250500
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s2 = a1;
    s1 = a2;
    lw(a0, a0, pose::kPosMode);
    v1 = 3;
    if (a0 != v1) {
        // 0x00250530
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1137;
        jal(ctx, 0x25053Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250544
    charge(ctx, 26);
    sw(zero, s0, pose::kW36);
    lwc1(f2, s2, 0);
    lwc1(f1, s2, 4);
    lwc1(f0, s2, 8);
    swc1(f2, s0, pose::kW48);
    swc1(f1, s0, 52);
    swc1(f0, s0, 56);
    lwc1(f2, s0, pose::kValue);
    lwc1(f1, s0, pose::kValue + 4);
    lwc1(f0, s0, pose::kValue + 8);
    swc1(f2, s0, pose::kW60);
    swc1(f1, s0, 64);
    swc1(f0, s0, 68);
    sw(zero, s0, pose::kTime);
    v1 = sll(s1, 16);
    sw(v1, s0, pose::kW44);
    lw(v1, s0, pose::kW40);
    v1 = v1 | 0x1;
    sw(v1, s0, pose::kW40);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002505B0 sub_2505B0 -- 776 bytes; frame 0xC0: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [gcPoseMoveCurve] Starts a curved timed move (K_Assert 1193 / 1194): kind 1, the start velocity a3 (+60), the end
// a1 (+84), the start = the current value (+72); the acceleration +48 is solved so that the arc starting with
// velocity v reaches the end in a2 frames (t = a2 / 30 s, a = 2 (d - v t) / t^2 corrected along the velocity's
// direction); duration a2 frames, running.
// Arguments: a0 node, a1 f32[3] end, a2 frames, a3 f32[3] start velocity.
void sub_2505B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x002505b0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    s0 = a1;
    s2 = a2;
    s5 = a3;
    lw(v0, a0, pose::kKind);
    if (v0 != 0) {
        // 0x002505fc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1193;
        jal(ctx, 0x250608u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250610
    charge(ctx, 4);
    lw(v1, s1, pose::kPosMode);
    v0 = 3;
    if (v1 != v0) {
        // 0x00250620
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1194;
        jal(ctx, 0x25062Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250634
    charge(ctx, 161);
    s4 = sll(s2, 16);
    mtc1(s4, f0);
    cvt_s_w(f1, f0);
    v0 = 0x49F00000;
    mtc1(v0, f0);
    div_s(f22, f1, f0);
    s3 = addiu(s1, 36);
    v0 = 1;
    sw(v0, s1, pose::kW36);
    s2 = addiu(s3, 12);
    lwc1(f2, s5, 0);
    lwc1(f1, s5, 4);
    lwc1(f0, s5, 8);
    swc1(f2, s1, pose::kW60);
    swc1(f1, s1, 64);
    swc1(f0, s1, 68);
    lwc1(f2, s0, 0);
    lwc1(f1, s0, 4);
    lwc1(f0, s0, 8);
    swc1(f2, s1, pose::kW84);
    swc1(f1, s1, pose::kW88);
    swc1(f0, s1, pose::kW92);
    lwc1(f2, s1, pose::kValue);
    lwc1(f1, s1, pose::kValue + 4);
    lwc1(f0, s1, pose::kValue + 8);
    swc1(f2, s1, pose::kW72);
    swc1(f1, s1, 76);
    swc1(f0, s1, 80);
    lwc1(f1, s1, pose::kW84);
    lwc1(f0, s1, pose::kW72);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xB0);
    lwc1(f1, s1, pose::kW88);
    lwc1(f0, s1, 76);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xB4);
    lwc1(f1, s1, pose::kW92);
    lwc1(f0, s1, 80);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xB8);
    a0 = addiu(sp, 0xA0);
    a1 = addiu(sp, 0xB0);
    jal(ctx, 0x2506E4u, gen::fn_sub_4C69F0_004c69f0);
    a0 = addiu(sp, 0x90);
    a1 = addiu(s2, 12);
    jal(ctx, 0x2506F4u, gen::fn_sub_4C69F0_004c69f0);
    lwc1(f5, sp, 0xA8);
    lwc1(f4, sp, 0x98);
    lwc1(f3, sp, 0xA0);
    lwc1(f2, sp, 0x90);
    lwc1(f1, sp, 0xA4);
    lwc1(f0, sp, 0x94);
    mula_s(f1, f0);
    madda_s(f3, f2);
    madd_s(f23, f5, f4);
    a0 = addiu(s2, 12);
    jal(ctx, 0x250724u, gen::fn_sub_4C6AC0_004c6ac0);
    mul_s(f1, f23, f0);
    lwc1(f0, sp, 0xA0);
    mul_s(f21, f0, f1);
    a0 = addiu(s2, 12);
    jal(ctx, 0x25073Cu, gen::fn_sub_4C6AC0_004c6ac0);
    mul_s(f1, f23, f0);
    lwc1(f0, sp, 0xA4);
    mul_s(f20, f0, f1);
    a0 = addiu(s2, 12);
    jal(ctx, 0x250754u, gen::fn_sub_4C6AC0_004c6ac0);
    mul_s(f1, f23, f0);
    lwc1(f0, sp, 0xA8);
    mul_s(f7, f0, f1);
    mul_s(f2, f21, f22);
    swc1(f2, sp, 0x80);
    mul_s(f1, f20, f22);
    swc1(f1, sp, 0x84);
    mul_s(f3, f7, f22);
    swc1(f3, sp, 0x88);
    lwc1(f0, sp, 0xB0);
    sub_s(f2, f2, f0);
    swc1(f2, sp, 0x80);
    lwc1(f0, sp, 0xB4);
    sub_s(f1, f1, f0);
    swc1(f1, sp, 0x84);
    lwc1(f0, sp, 0xB8);
    sub_s(f0, f3, f0);
    swc1(f0, sp, 0x88);
    v1 = 0x40000000;
    mtc1(v1, f6);
    mul_s(f5, f2, f6);
    swc1(f5, sp, 0x80);
    mul_s(f4, f1, f6);
    swc1(f4, sp, 0x84);
    mul_s(f2, f0, f6);
    swc1(f2, sp, 0x88);
    mul_s(f1, f22, f22);
    v1 = lui(0xBF80);
    mtc1(v1, f0);
    div_s(f3, f0, f1);
    mul_s(f0, f5, f3);
    swc1(f0, sp, 0x80);
    mul_s(f0, f4, f3);
    swc1(f0, sp, 0x84);
    mul_s(f0, f2, f3);
    swc1(f0, sp, 0x88);
    lwc1(f0, s2, 12);
    sub_s(f2, f0, f21);
    lwc1(f0, s2, 16);
    sub_s(f1, f0, f20);
    lwc1(f0, s2, 20);
    sub_s(f0, f0, f7);
    mul_s(f2, f2, f22);
    mul_s(f1, f1, f22);
    mul_s(f0, f0, f22);
    mul_s(f2, f2, f6);
    mul_s(f1, f1, f6);
    mul_s(f0, f0, f6);
    mul_s(f5, f2, f3);
    mul_s(f4, f1, f3);
    mul_s(f3, f0, f3);
    lwc1(f2, sp, 0x80);
    lwc1(f1, sp, 0x84);
    lwc1(f0, sp, 0x88);
    swc1(f2, s2, 0);
    swc1(f1, s2, 4);
    swc1(f0, s2, 8);
    lwc1(f0, s2, 0);
    add_s(f0, f0, f5);
    swc1(f0, s2, 0);
    lwc1(f0, s2, 4);
    add_s(f0, f0, f4);
    swc1(f0, s2, 4);
    lwc1(f0, s2, 8);
    add_s(f0, f0, f3);
    swc1(f0, s2, 8);
    sw(zero, s1, pose::kTime);
    sw(s4, s3, 8);
    lw(v1, s3, 4);
    v1 = v1 | 0x1;
    sw(v1, s3, 4);
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// 0x002508C0 sub_2508C0 -- 364 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcPoseMoveEaseOut] Starts a decelerating timed move (K_Assert 1238 / 1239): kind 1 from the current value to a1 in
// a2 frames, arriving at rest: velocity +60 = 2 d / t, acceleration +48 = -2 d / t^2 (t = a2 / 30 s).
// Arguments: a0 node, a1 f32[3] end, a2 frames.
void sub_2508C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5};
    // 0x002508c0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    s2 = a2;
    lw(v1, a0, pose::kKind);
    if (v1 != 0) {
        // 0x002508ec
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1238;
        jal(ctx, 0x2508F8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250900
    charge(ctx, 4);
    lw(a0, s1, pose::kPosMode);
    v1 = 3;
    if (a0 != v1) {
        // 0x00250910
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1239;
        jal(ctx, 0x25091Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250924
    charge(ctx, 66);
    a0 = sll(s2, 16);
    mtc1(a0, f0);
    cvt_s_w(f1, f0);
    v1 = 0x49F00000;
    mtc1(v1, f0);
    div_s(f5, f1, f0);
    v1 = 1;
    sw(v1, s1, pose::kW36);
    lwc1(f2, s0, 0);
    lwc1(f1, s0, 4);
    lwc1(f0, s0, 8);
    swc1(f2, s1, pose::kW84);
    swc1(f1, s1, pose::kW88);
    swc1(f0, s1, pose::kW92);
    lwc1(f2, s1, pose::kValue);
    lwc1(f1, s1, pose::kValue + 4);
    lwc1(f0, s1, pose::kValue + 8);
    swc1(f2, s1, pose::kW72);
    swc1(f1, s1, 76);
    swc1(f0, s1, 80);
    mul_s(f1, f5, f5);
    v1 = 0x40000000;
    mtc1(v1, f0);
    div_s(f2, f0, f1);
    lwc1(f1, s1, pose::kW84);
    lwc1(f0, s1, pose::kW72);
    sub_s(f0, f1, f0);
    mul_s(f4, f0, f2);
    lwc1(f1, s1, pose::kW88);
    lwc1(f0, s1, 76);
    sub_s(f0, f1, f0);
    mul_s(f3, f0, f2);
    lwc1(f1, s1, pose::kW92);
    lwc1(f0, s1, 80);
    sub_s(f0, f1, f0);
    mul_s(f2, f0, f2);
    v1 = lui(0xBF80);
    mtc1(v1, f1);
    mul_s(f0, f1, f4);
    swc1(f0, s1, pose::kW48);
    mul_s(f0, f1, f3);
    swc1(f0, s1, 52);
    mul_s(f0, f1, f2);
    swc1(f0, s1, 56);
    mul_s(f0, f4, f5);
    swc1(f0, s1, pose::kW60);
    mul_s(f0, f3, f5);
    swc1(f0, s1, 64);
    mul_s(f0, f2, f5);
    swc1(f0, s1, 68);
    sw(zero, s1, pose::kTime);
    sw(a0, s1, pose::kW44);
    lw(v1, s1, pose::kW40);
    v1 = v1 | 0x1;
    sw(v1, s1, pose::kW40);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00250A30 sub_250A30 -- 352 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcPoseMoveEaseIn] Starts an accelerating timed move (K_Assert 1269 / 1270): kind 1 from rest to a1 in a2 frames:
// velocity 0, acceleration 2 d / t^2.
// Arguments: a0 node, a1 f32[3] end, a2 frames.
void sub_250A30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00250a30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    s2 = a2;
    lw(v1, a0, pose::kKind);
    if (v1 != 0) {
        // 0x00250a5c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1269;
        jal(ctx, 0x250A68u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250a70
    charge(ctx, 4);
    lw(a0, s1, pose::kPosMode);
    v1 = 3;
    if (a0 != v1) {
        // 0x00250a80
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1270;
        jal(ctx, 0x250A8Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250a94
    charge(ctx, 63);
    a0 = sll(s2, 16);
    mtc1(a0, f0);
    cvt_s_w(f1, f0);
    v1 = 0x49F00000;
    mtc1(v1, f0);
    div_s(f3, f1, f0);
    v1 = 1;
    sw(v1, s1, pose::kW36);
    lwc1(f2, s0, 0);
    lwc1(f1, s0, 4);
    lwc1(f0, s0, 8);
    swc1(f2, s1, pose::kW84);
    swc1(f1, s1, pose::kW88);
    swc1(f0, s1, pose::kW92);
    lwc1(f2, s1, pose::kValue);
    lwc1(f1, s1, pose::kValue + 4);
    lwc1(f0, s1, pose::kValue + 8);
    swc1(f2, s1, pose::kW72);
    swc1(f1, s1, 76);
    swc1(f0, s1, 80);
    mul_s(f1, f3, f3);
    v1 = 0x40000000;
    mtc1(v1, f0);
    div_s(f2, f0, f1);
    lwc1(f1, s1, pose::kW84);
    lwc1(f0, s1, pose::kW72);
    sub_s(f0, f1, f0);
    mul_s(f0, f0, f2);
    swc1(f0, sp, 0x40);
    lwc1(f1, s1, pose::kW88);
    lwc1(f0, s1, 76);
    sub_s(f0, f1, f0);
    mul_s(f0, f0, f2);
    swc1(f0, sp, 0x44);
    lwc1(f1, s1, pose::kW92);
    lwc1(f0, s1, 80);
    sub_s(f0, f1, f0);
    mul_s(f0, f0, f2);
    swc1(f0, sp, 0x48);
    lwc1(f2, sp, 0x40);
    lwc1(f1, sp, 0x44);
    lwc1(f0, sp, 0x48);
    swc1(f2, s1, pose::kW48);
    swc1(f1, s1, 52);
    swc1(f0, s1, 56);
    sw(zero, s1, pose::kW60);
    sw(zero, s1, 64);
    sw(zero, s1, 68);
    sw(zero, s1, pose::kTime);
    sw(a0, s1, pose::kW44);
    lw(v1, s1, pose::kW40);
    v1 = v1 | 0x1;
    sw(v1, s1, pose::kW40);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00250B90 sub_250B90 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [gcPoseMoveIsRunning] Nonzero while a timed-move position node runs (+40 bit 1; K_Assert line 1298).
// Arguments: a0 node.
void sub_250B90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00250b90
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, pose::kPosMode);
    v0 = 3;
    if (v1 != v0) {
        // 0x00250bb0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1298;
        jal(ctx, 0x250BBCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250bc4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, s0, pose::kW40);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00250BE0 sub_250BE0 -- 144 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcPoseSetProductChild] Sets child a1 of a product orientation node to a2 (K_Assert 1327 / 1328).
// Arguments: a0 node, a1 index, a2 child node.
void sub_250BE0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00250be0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    lw(a0, a0, pose::kKind);
    v1 = 2;
    if (a0 != v1) {
        // 0x00250c10
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1327;
        jal(ctx, 0x250C1Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250c24
    charge(ctx, 4);
    lw(a0, s2, pose::kW36);
    v1 = 2;
    if (a0 != v1) {
        // 0x00250c34
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1328;
        jal(ctx, 0x250C40u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250c48 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v1 = sll(s1, 2);
    v1 = addu(v1, s2);
    sw(s0, v1, 40);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00250C70 sub_250C70 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [gcPoseSpinHalt] Stops a spin orientation node (+44 bit 1; K_Assert 1337 / 1338: kind 2, mode 3).
// Arguments: a0 node.
void sub_250C70(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00250c70
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, pose::kKind);
    v1 = 2;
    if (a0 != v1) {
        // 0x00250c90
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1337;
        jal(ctx, 0x250C9Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250ca4
    charge(ctx, 4);
    lw(a0, s0, pose::kW36);
    v1 = 3;
    if (a0 != v1) {
        // 0x00250cb4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1338;
        jal(ctx, 0x250CC0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250cc8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a0, s0, pose::kW44);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, s0, pose::kW44);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00250E70 sub_250E70 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [gcPoseSpinIsRunning] Nonzero while a spin orientation node runs (+44 bit 1; K_Assert 1405 / 1406).
// Arguments: a0 node.
void sub_250E70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00250e70
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, pose::kKind);
    v0 = 2;
    if (v1 != v0) {
        // 0x00250e90
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1405;
        jal(ctx, 0x250E9Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250ea4
    charge(ctx, 4);
    lw(v1, s0, pose::kW36);
    v0 = 3;
    if (v1 != v0) {
        // 0x00250eb4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1406;
        jal(ctx, 0x250EC0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250ec8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, s0, pose::kW44);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00250EF0 sub_250EF0 -- 136 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// [gcPoseSetWobbleScale] Sets a wobble orientation node's scale (+108 = f12; K_Assert 1416 / 1417) and marks it
// dirty.
// Arguments: a0 node, f12 scale.
void sub_250EF0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x00250ef0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a0;
    mov_s(f20, f12);
    lw(a0, a0, pose::kKind);
    v1 = 2;
    if (a0 != v1) {
        // 0x00250f18
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1416;
        jal(ctx, 0x250F24u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250f2c
    charge(ctx, 4);
    lw(a0, s0, pose::kW36);
    v1 = 4;
    if (a0 != v1) {
        // 0x00250f3c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1417;
        jal(ctx, 0x250F48u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250f50 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    swc1(f20, s0, pose::kW108);
    lw(v1, s0, pose::kFlags);
    v1 = v1 | 0x2;
    sw(v1, s0, pose::kFlags);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00250F80 sub_250F80 -- 140 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflProjectToScreen] Projects the world point a1 to the screen (a0 = f32[2]): the active camera's view matrix
// (sub_198590 +32, sub_4C6BE0), then x * 640 / w and y * 448 / w.
// Arguments: a0 out f32[2], a1 f32[3].
void sub_250F80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00250f80
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    jal(ctx, 0x250F98u, gen::fn_sub_198590_00198590);
    a0 = addiu(sp, 0x30);
    a1 = s0;
    a2 = addiu(v0, 32);
    jal(ctx, 0x250FACu, gen::fn_sub_4C6BE0_004c6be0);
    lwc1(f1, sp, 0x30);
    lwc1(f0, sp, 0x38);
    div_s(f1, f1, f0);
    v1 = 0x44200000;
    mtc1(v1, f0);
    mul_s(f0, f0, f1);
    swc1(f0, s1, 0);
    lwc1(f1, sp, 0x34);
    lwc1(f0, sp, 0x38);
    div_s(f1, f1, f0);
    v1 = 0x43E00000;
    mtc1(v1, f0);
    mul_s(f0, f0, f1);
    swc1(f0, s1, 4);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00251010 sub_251010 -- 32 bytes; leaf frame (no stack)
// [gcPoseAddTime] Adds a1 to a pose node's time (+16) and marks it dirty.
// Arguments: a0 node, a1 16.16 frames.
void sub_251010(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00251010
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v1, a0, pose::kTime);
    v1 = addu(v1, a1);
    sw(v1, a0, pose::kTime);
    lw(v1, a0, pose::kFlags);
    v1 = v1 | 0x2;
    sw(v1, a0, pose::kFlags);
}

// 0x00251030 sub_251030 -- 20 bytes; leaf frame (no stack)
// [gcPoseTouch] Marks a pose node dirty (+8 bit 2).
// Arguments: a0 node.
void sub_251030(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00251030
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, a0, pose::kFlags);
    v1 = v1 | 0x2;
    sw(v1, a0, pose::kFlags);
}

// 0x00253A40 sub_253A40 -- 4432 bytes; frame 0xD0: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [sflCardsUpdate] Per-frame update of the Shuffle Time cards (sfl_card.c; K_Assert line 188): clears the 'models
// loading' flag 0x200 once sub_21A120 says so; while open: counts frames (+75392); flag 0x20 holds while left / right
// (0x8000 / 0x2000 held) stay down; the deal (flag 0x10): phase +75704 = 0 flies each card in at its own frame
// (+75708[i] * +75912; the 'i%d c%d' printf, an accelerating move +75916 frames long, sound 1/0/6/2), and once every
// card landed lays them out (gcPoseMove...) -> phase 1, where they turn over one by one every 3 frames (decelerating
// moves, sound 6 / 2 when each lands) until none moves; otherwise the cursor: left / right (the pad words 0x7E0952 /
// 0x7E095A) step the selected card (+75692) with wrap-around (sub_25B300 / sub_25B3B0, sound 0) and set flag 0x20 at
// the ends. Then the effect phases (flag 0x40, +75888): 1 the pick (the chosen card wobbles), 2 the fade out /
// shuffle (sfl_cardShuffle) / fade in of +75904 over 6 + 5 + 6 frames, 3 a 30-frame fade in, 4 a 16-frame fade out, 5
// the switch to card +75908 over 30 frames (the other cards fade out) with the orientation from +75776; every card's
// update (sfl_cardUpdate); and the pick's finish (the chosen card flies to the centre with sound 1/0/6/15 unless flag
// 0x2000; the others spin away).
void sub_253A40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20};
    // 0x00253a40
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    lw(v1, gp, kGpSflCard);  // the Shuffle Time cards (sfl_card.c) 0x7CE354
    if (v1 == 0) {
        // 0x00253a68
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x253A74u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00253a7c: the models-loading flag (0x200) clears once sub_21A120 says so
    charge(ctx, 11);
    lw(s1, gp, kGpSflCard);  // the Shuffle Time cards (sfl_card.c) 0x7CE354
    v1 = 0x690000;
    ld(a0, v1, -5616);  // 0x68EA10
    v1 = 0x690000;
    lwc1(f0, v1, -5608);  // 0x68EA18
    sd(a0, sp, 0xA8);
    swc1(f0, sp, 0xB0);
    lw(v1, s1, sflcard::kFlags);
    v1 = v1 & 0x200;
    if (v1 != 0) {
        // 0x00253aa8
        charge(ctx, 4);
        jal(ctx, 0x253AA8u, gen::fn_sub_21A120_0021a120);
        if (v0 == 0) {
            // 0x00253ab8
            charge(ctx, 4);
            lw(a0, s1, sflcard::kFlags);
            v1 = si(-513);
            v1 = a0 & v1;
            sw(v1, s1, sflcard::kFlags);
        }
    }
    // 0x00253ac8: open: count the frames (+75392); the "held at an end" flag 0x20 clears once left / right (0x8000 /
    // 0x2000, held) are released
    charge(ctx, 5);
    lw(v1, s1, sflcard::kFlags);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x00253adc
        charge(ctx, 11);
        v0 = 0x10000;
        v0 = addu(s1, v0);
        lw(v0, v0, 9856);
        v1 = addiu(v0, 1);
        v0 = 0x10000;
        v0 = addu(s1, v0);
        sw(v1, v0, 9856);
        lw(a1, s1, sflcard::kFlags);
        v0 = a1 & 0x20;
        if (v0 != 0) {
            // 0x00253b08
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(a0, v0, 2380);  // 0x7E094C
            v0 = a0 & 0x8000;
            if (v0 == 0) {
                // 0x00253b1c
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v1, v0, 2390);  // 0x7E0956
                v0 = v1 & 0x8000;
                if (v0 == 0) {
                    // 0x00253b30
                    charge(ctx, 3);
                    v0 = a0 & 0x2000;
                    if (v0 == 0) {
                        // 0x00253b3c
                        charge(ctx, 3);
                        v0 = v1 & 0x2000;
                        if (v0 == 0) {
                            // 0x00253b48
                            charge(ctx, 3);
                            v0 = si(-33);
                            v0 = a1 & v0;
                            sw(v0, s1, sflcard::kFlags);
                        }
                    }
                }
            }
        }
        // 0x00253b54: the deal (0x4 / 0x8 / 0x10 states) or the cursor
        charge(ctx, 4);
        lw(a0, s1, sflcard::kFlags);
        v0 = a0 & 0x4;
        if (v0 != 0) {
            // 0x00253b64
            charge(ctx, 4);
            v1 = nor(a0, 0);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                goto L_00253d08;
            }
            // 0x00253b74
            charge(ctx, 3);
            v0 = v1 & 0x20;
            if (v0 == 0) {
                goto L_00253d08;
            }
            // 0x00253b80: the cursor: left (the pad's 0x8000 bit, pressed) or right (0x2000) moves the selection
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(a0, v0, 2386);  // 0x7E0952
            v0 = a0 & 0x8000;
            if (v0 == 0) {
                // 0x00253b94
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v1, v0, 2394);  // 0x7E095A
                v0 = v1 & 0x8000;
                if (v0 != 0) {
                    goto L_00253ba8;
                }
                // 0x00253c40
                charge(ctx, 3);
                v0 = a0 & 0x2000;
                if (v0 == 0) {
                    // 0x00253c4c
                    charge(ctx, 3);
                    v0 = v1 & 0x2000;
                    if (v0 != 0) {
                        goto L_00253c58;
                    }
                    goto L_002541f4;
                }
            L_00253c58:
                charge(ctx, 10);
                v0 = 0x10000;
                v0 = addu(s1, v0);
                lw(v1, v0, 10156);
                v0 = 0x10000;
                v0 = addu(s1, v0);
                lw(v0, v0, 9852);
                v0 = addiu(v0, -1);
                at = slt(v1, v0);
                if (at == 0) {
                    // 0x00253cd0
                    charge(ctx, 6);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    sw(zero, v0, 10156);
                    a0 = 0;
                    jal(ctx, 0x253CE0u, gen::fn_sub_25B3B0_0025b3b0);
                } else {
                    // 0x00253c80
                    charge(ctx, 15);
                    a0 = addiu(v1, 1);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    sw(a0, v0, 10156);
                    jal(ctx, 0x253C90u, gen::fn_sub_25B300_0025b300);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v1, v0, 10156);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v0, v0, 9852);
                    v0 = addiu(v0, -1);
                    if (v1 == v0) {
                        // 0x00253cbc
                        charge(ctx, 5);
                        lw(v0, s1, sflcard::kFlags);
                        v0 = v0 | 0x20;
                        sw(v0, s1, sflcard::kFlags);
                    }
                }
                // 0x00253ce8: the cursor sound (sound request 0, 0, 0, 0)
                charge(ctx, 8);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x253CF8u, gen::fn_sub_10A4E0_0010a4e0);
                goto L_002541f4;
            }
        L_00253ba8:
            charge(ctx, 5);
            v0 = 0x10000;
            v0 = addu(s1, v0);
            lw(v0, v0, 10156);
            if (i64(v0) <= 0) {
                // 0x00253bfc
                charge(ctx, 9);
                v0 = 0x10000;
                v0 = addu(s1, v0);
                lw(v0, v0, 9852);
                a0 = addiu(v0, -1);
                v0 = 0x10000;
                v0 = addu(s1, v0);
                sw(a0, v0, 10156);
                jal(ctx, 0x253C18u, gen::fn_sub_25B3B0_0025b3b0);
            } else {
                // 0x00253bbc
                charge(ctx, 11);
                a0 = addiu(v0, -1);
                v0 = 0x10000;
                v0 = addu(s1, v0);
                sw(a0, v0, 10156);
                jal(ctx, 0x253BCCu, gen::fn_sub_25B300_0025b300);
                v0 = 0x10000;
                v0 = addu(s1, v0);
                lw(v0, v0, 10156);
                if (v0 == 0) {
                    // 0x00253be8
                    charge(ctx, 5);
                    lw(v0, s1, sflcard::kFlags);
                    v0 = v0 | 0x20;
                    sw(v0, s1, sflcard::kFlags);
                }
            }
            // 0x00253c20
            charge(ctx, 8);
            a0 = 0;
            a1 = 0;
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x253C30u, gen::fn_sub_10A4E0_0010a4e0);
            goto L_002541f4;
        }
    L_00253d08:
        charge(ctx, 3);
        v0 = a0 & 0x10;
        if (v0 != 0) {
            // 0x00253d14
            charge(ctx, 6);
            v0 = 0x10000;
            v0 = addu(s1, v0);
            lw(v1, v0, 10168);
            v0 = 1;
            if (v1 == v0) {
                // 0x00254034: deal phase 1: each card turns over at 3 * its index frames (a decelerating move into
                // its place)
                charge(ctx, 10);
                v0 = 0x10000;
                v0 = addu(s1, v0);
                lw(v0, v0, 10164);
                v1 = addiu(v0, 1);
                v0 = 0x10000;
                v0 = addu(s1, v0);
                sw(v1, v0, 10164);
                s2 = 0;
                for (;;) {
                    // 0x00254104
                    charge(ctx, 6);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v0, v0, 9852);
                    v0 = slt(s2, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0025405c
                    charge(ctx, 9);
                    a0 = s2;
                    jal(ctx, 0x254060u, gen::fn_sub_255440_00255440);
                    s0 = v0;
                    lw(v0, v0, card::kFlags);
                    v0 = nor(v0, 0);
                    v0 = v0 & 0x40;
                    if (v0 == 0) {
                        // 0x00254080
                        charge(ctx, 8);
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        lw(v1, v0, 10164);
                        v0 = sll(s2, 1);
                        v0 = addu(v0, s2);
                        v0 = slt(v1, v0);
                        if (v0 == 0) {
                            // 0x002540a0
                            charge(ctx, 24);
                            a0 = s0;
                            a1 = addiu(sp, 0x90);
                            a2 = addiu(sp, 0xCC);
                            jal(ctx, 0x2540ACu, gen::fn_sub_256F20_00256f20);
                            a0 = addiu(sp, 0xC0);
                            a1 = s2;
                            lw(a2, sp, 0x90);
                            v0 = 0x10000;
                            v0 = addu(s1, v0);
                            lw(a3, v0, 9852);
                            jal(ctx, 0x2540CCu, gen::fn_sub_257D00_00257d00);
                            a0 = addiu(s0, 4244);
                            a1 = addiu(sp, 0xC0);
                            a2 = 10;
                            jal(ctx, 0x2540E0u, gen::fn_sub_2508C0_002508c0);
                            lw(v0, s0, card::kFlags);
                            v1 = v0 | 0x20;
                            sw(v1, s0, card::kFlags);
                            v0 = si(-65);
                            v0 = v1 & v0;
                            sw(v0, s0, card::kFlags);
                        }
                    }
                    // 0x00254100
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0025411c: the turn-over sound for the card due this frame (3 * i + 6)
                charge(ctx, 3);
                s2 = 0;
                for (;;) {
                    // 0x00254164
                    charge(ctx, 6);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v0, v0, 9852);
                    v0 = slt(s2, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00254128
                    charge(ctx, 8);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v1, v0, 10164);
                    v0 = sll(s2, 1);
                    v0 = addu(v0, s2);
                    v0 = addiu(v0, 6);
                    if (v1 == v0) {
                        // 0x00254148
                        charge(ctx, 6);
                        a0 = 1;
                        a1 = 0;
                        a2 = 6;
                        a3 = 2;
                        jal(ctx, 0x254158u, gen::fn_sub_10A4E0_0010a4e0);
                    }
                    // 0x00254160
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0025417c: once no card moves the deal ends (flag 0x10)
                charge(ctx, 3);
                s2 = 0;
                for (;;) {
                    // 0x002541b8
                    charge(ctx, 6);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v0, v0, 9852);
                    v0 = slt(s2, v0);
                    if (v0 != 0) {
                        backedge(ctx);
                        // 0x00254188
                        charge(ctx, 8);
                        a0 = s2;
                        jal(ctx, 0x25418Cu, gen::fn_sub_255440_00255440);
                        s0 = v0;
                        lw(v1, v0, card::kFlags);
                        v0 = v1 & 0x40;
                        if (v0 == 0) {
                            // 0x002541a8
                            charge(ctx, 3);
                            v0 = v1 & 0x20;
                            if (v0 == 0) {
                                // 0x002541b4
                                charge(ctx, 1);
                                s2 = addiu(s2, 1);
                                continue;
                            }
                        }
                    }
                    break;
                }
                // 0x002541d0
                charge(ctx, 5);
                v0 = 0x10000;
                v0 = addu(s1, v0);
                lw(v0, v0, 9852);
                if (s2 == v0) {
                    // 0x002541e4
                    charge(ctx, 4);
                    lw(v1, s1, sflcard::kFlags);
                    v0 = si(-17);
                    v0 = v1 & v0;
                    sw(v0, s1, sflcard::kFlags);
                }
            } else {
                // 0x00253d2c: deal phase 0: each card flies in at its own frame (+75708[i] * +75912), 200 above its
                // place
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x00253d3c
                    charge(ctx, 10);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v0, v0, 10164);
                    v1 = addiu(v0, 1);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    sw(v1, v0, 10164);
                    s2 = 0;
                    for (;;) {
                        // 0x00253e70
                        charge(ctx, 6);
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        lw(v0, v0, 9852);
                        v0 = slt(s2, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00253d64
                        charge(ctx, 8);
                        a0 = s2;
                        jal(ctx, 0x253D68u, gen::fn_sub_255440_00255440);
                        s0 = v0;
                        lw(v0, v0, card::kFlags);
                        v0 = v0 & 0x40;
                        if (v0 == 0) {
                            // 0x00253d84
                            charge(ctx, 16);
                            v0 = sll(s2, 2);
                            v0 = addu(s1, v0);
                            at = 0x10000;
                            at = at | 0x27BC;
                            v0 = addu(v0, at);
                            lw(a2, v0, 0);
                            v0 = 0x10000;
                            v0 = addu(s1, v0);
                            lw(a3, v0, 10164);
                            v0 = 0x10000;
                            v0 = addu(s1, v0);
                            lw(v0, v0, 10376);
                            mult(v0, a2, v0);
                            v0 = slt(a3, v0);
                            if (v0 == 0) {
                                // 0x00253dc4
                                charge(ctx, 42);
                                a0 = 0x690000;
                                a0 = addiu(a0, -5600);  // "%d  i%d c%d\n"
                                a1 = s2;
                                jal(ctx, 0x253DD0u, gen::fn_printf_005225a8);
                                a0 = s0;
                                a1 = addiu(sp, 0x90);
                                a2 = addiu(sp, 0xCC);
                                jal(ctx, 0x253DE4u, gen::fn_sub_256F20_00256f20);
                                a0 = addiu(sp, 0xC0);
                                a1 = s2;
                                lw(a2, sp, 0x90);
                                v0 = 0x10000;
                                v0 = addu(s1, v0);
                                lw(a3, v0, 9852);
                                jal(ctx, 0x253E04u, gen::fn_sub_257D00_00257d00);
                                lwc1(f1, sp, 0xC4);
                                v0 = 0x43480000;
                                mtc1(v0, f0);
                                add_s(f0, f1, f0);
                                swc1(f0, sp, 0xC4);
                                a0 = addiu(s0, 4244);
                                a1 = addiu(sp, 0xC0);
                                v0 = 0x10000;
                                v0 = addu(s1, v0);
                                lw(a2, v0, 10380);
                                jal(ctx, 0x253E38u, gen::fn_sub_250A30_00250a30);
                                lw(v0, s0, card::kFlags);
                                v0 = v0 | 0x20;
                                sw(v0, s0, card::kFlags);
                                v0 = v0 | 0x40;
                                sw(v0, s0, card::kFlags);
                                a0 = 1;
                                a1 = 0;
                                a2 = 6;
                                a3 = 2;
                                jal(ctx, 0x253E64u, gen::fn_sub_10A4E0_0010a4e0);
                            }
                        }
                        // 0x00253e6c
                        charge(ctx, 1);
                        s2 = addiu(s2, 1);
                    }
                    // 0x00253e88: once every card has landed ...
                    charge(ctx, 3);
                    s2 = 0;
                    for (;;) {
                        // 0x00253ec8
                        charge(ctx, 6);
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        lw(v0, v0, 9852);
                        v0 = slt(s2, v0);
                        if (v0 != 0) {
                            backedge(ctx);
                            // 0x00253e94
                            charge(ctx, 9);
                            a0 = s2;
                            jal(ctx, 0x253E98u, gen::fn_sub_255440_00255440);
                            s0 = v0;
                            lw(v1, v0, card::kFlags);
                            v0 = nor(v1, 0);
                            v0 = v0 & 0x40;
                            if (v0 == 0) {
                                // 0x00253eb8
                                charge(ctx, 3);
                                v0 = v1 & 0x20;
                                if (v0 == 0) {
                                    // 0x00253ec4
                                    charge(ctx, 1);
                                    s2 = addiu(s2, 1);
                                    continue;
                                }
                            }
                        }
                        break;
                    }
                    // 0x00253ee0: ... they are laid out (400 above, a straight move) and phase 1 begins
                    charge(ctx, 5);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v0, v0, 9852);
                    if (s2 == v0) {
                        // 0x00253ef4
                        charge(ctx, 3);
                        s2 = 0;
                        for (;;) {
                            // 0x00253f1c
                            charge(ctx, 6);
                            v0 = 0x10000;
                            v0 = addu(s1, v0);
                            lw(v0, v0, 9852);
                            v0 = slt(s2, v0);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00253f00
                            charge(ctx, 7);
                            a0 = s2;
                            jal(ctx, 0x253F04u, gen::fn_sub_255440_00255440);
                            v1 = sll(s2, 2);
                            v1 = addu(v1, sp);
                            sw(v0, v1, 112);
                            s2 = addiu(s2, 1);
                        }
                        // 0x00253f34
                        charge(ctx, 3);
                        a1 = 0;
                        for (;;) {
                            // 0x00253f64
                            charge(ctx, 6);
                            v0 = 0x10000;
                            v0 = addu(s1, v0);
                            lw(v0, v0, 9852);
                            v0 = slt(a1, v0);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00253f40
                            charge(ctx, 9);
                            a0 = sll(a1, 2);
                            v1 = addu(s1, a0);
                            v0 = 0x10000;
                            v0 = addu(v1, v0);
                            lw(v1, v0, 10172);
                            v0 = addu(a0, sp);
                            lw(v0, v0, 112);
                            sw(v1, v0, 16);
                            a1 = addiu(a1, 1);
                        }
                        // 0x00253f7c
                        charge(ctx, 3);
                        s2 = 0;
                        for (;;) {
                            // 0x00253ff8
                            charge(ctx, 6);
                            v0 = 0x10000;
                            v0 = addu(s1, v0);
                            lw(v0, v0, 9852);
                            v0 = slt(s2, v0);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00253f88
                            charge(ctx, 28);
                            a0 = s2;
                            jal(ctx, 0x253F8Cu, gen::fn_sub_255440_00255440);
                            s0 = v0;
                            a0 = s0;
                            a1 = addiu(sp, 0x90);
                            a2 = addiu(sp, 0xCC);
                            jal(ctx, 0x253FA4u, gen::fn_sub_256F20_00256f20);
                            a0 = addiu(sp, 0xC0);
                            a1 = s2;
                            lw(a2, sp, 0x90);
                            v0 = 0x10000;
                            v0 = addu(s1, v0);
                            lw(a3, v0, 9852);
                            jal(ctx, 0x253FC4u, gen::fn_sub_257D00_00257d00);
                            lwc1(f1, sp, 0xC4);
                            v0 = 0x43C80000;
                            mtc1(v0, f0);
                            add_s(f0, f1, f0);
                            swc1(f0, sp, 0xC4);
                            a0 = addiu(s0, 4244);
                            a1 = addiu(sp, 0xC0);
                            jal(ctx, 0x253FECu, gen::fn_sub_24F9F0_0024f9f0);
                            s2 = addiu(s2, 1);
                        }
                        // 0x00254010
                        charge(ctx, 9);
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        sw(zero, v0, 10164);
                        v1 = 1;
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        sw(v1, v0, 10168);
                    }
                } else {
                    // 0x00253d34
                    charge(ctx, 2);
                }
            }
        }
    L_002541f4:
        charge(ctx, 4);
        lw(v0, s1, sflcard::kFlags);
        v0 = v0 & 0x40;
        if (v0 != 0) {
            // 0x00254204
            charge(ctx, 6);
            v0 = 0x10000;
            v0 = addu(s1, v0);
            lw(v0, v0, 10352);
            at = sltiu(v0, 6);
            if (at != 0) {
                // 0x0025421c
                charge(ctx, 7);
                v1 = 0x7B0000;
                v1 = addiu(v1, 31024);  // "$H%"
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x254238u:  // table[1]: effect 1, the pick
                    // 0x00254238
                    charge(ctx, 6);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v1, v0, 10356);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x00254260
                        charge(ctx, 47);
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        lw(v0, v0, 10364);
                        v1 = addiu(v0, 1);
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        sw(v1, v0, 10364);
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        lwc1(f0, v0, 10364);
                        cvt_s_w(f1, f0);
                        v0 = 0x41200000;
                        mtc1(v0, f0);
                        div_s(f20, f1, f0);
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        lw(a0, v0, 10156);
                        jal(ctx, 0x2542A8u, gen::fn_sub_255440_00255440);
                        s0 = v0;
                        v0 = 0x3F800000;
                        mtc1(v0, f0);
                        sub_s(f20, f0, f20);
                        a0 = addiu(s0, 4144);
                        mov_s(f12, f20);
                        jal(ctx, 0x2542CCu, gen::fn_sub_24F2C0_0024f2c0);
                        a0 = addiu(s0, 4568);
                        mov_s(f12, f20);
                        jal(ctx, 0x2542DCu, gen::fn_sub_250EF0_00250ef0);
                        a0 = addiu(s0, 4044);
                        jal(ctx, 0x2542E8u, gen::fn_sub_251030_00251030);
                        a0 = addiu(s0, 4044);
                        jal(ctx, 0x2542F4u, gen::fn_sub_24DC90_0024dc90);
                        a0 = addiu(s0, 4344);
                        jal(ctx, 0x254300u, gen::fn_sub_251030_00251030);
                        a0 = addiu(s0, 4344);
                        jal(ctx, 0x25430Cu, gen::fn_sub_24DC90_0024dc90);
                    } else {
                        // 0x00254250
                        charge(ctx, 2);
                        if (v1 != 0) {
                            // 0x00254258
                            charge(ctx, 2);
                        }
                    }
                    break;
                case 0x25431Cu:  // table[2]: effect 2, the shuffle: fade out (6), shuffle, wait (5), fade in (6)
                    // 0x0025431c
                    charge(ctx, 6);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v1, v0, 10360);
                    a0 = 2;
                    if (v1 == a0) {
                        // 0x00254448
                        charge(ctx, 30);
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        lw(v0, v0, 10364);
                        v1 = addiu(v0, 1);
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        sw(v1, v0, 10364);
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        lwc1(f0, v0, 10364);
                        cvt_s_w(f1, f0);
                        v0 = 0x40C00000;
                        mtc1(v0, f0);
                        div_s(f1, f1, f0);
                        v0 = 0x43800000;
                        mtc1(v0, f0);
                        mul_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        sw(v1, v0, 10368);
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        lw(v1, v0, 10364);
                        v0 = 6;
                        if (v1 == v0) {
                            // 0x002544c0
                            charge(ctx, 9);
                            lw(v1, s1, sflcard::kFlags);
                            v0 = si(-129);
                            v1 = v1 & v0;
                            sw(v1, s1, sflcard::kFlags);
                            v0 = si(-65);
                            v0 = v1 & v0;
                            sw(v0, s1, sflcard::kFlags);
                        }
                    } else {
                        // 0x00254334
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x00254400
                            charge(ctx, 10);
                            v0 = 0x10000;
                            v0 = addu(s1, v0);
                            lw(v0, v0, 10364);
                            v1 = addiu(v0, 1);
                            v0 = 0x10000;
                            v0 = addu(s1, v0);
                            sw(v1, v0, 10364);
                            v0 = 5;
                            if (v1 == v0) {
                                // 0x00254428
                                charge(ctx, 8);
                                v0 = 0x10000;
                                v0 = addu(s1, v0);
                                sw(zero, v0, 10364);
                                v0 = 0x10000;
                                v0 = addu(s1, v0);
                                sw(a0, v0, 10360);
                            }
                        } else {
                            // 0x00254340
                            charge(ctx, 2);
                            if (v1 == 0) {
                                // 0x00254350
                                charge(ctx, 33);
                                v0 = 0x10000;
                                v0 = addu(s1, v0);
                                lw(v0, v0, 10364);
                                v1 = addiu(v0, 1);
                                v0 = 0x10000;
                                v0 = addu(s1, v0);
                                sw(v1, v0, 10364);
                                v0 = 0x10000;
                                v0 = addu(s1, v0);
                                lwc1(f0, v0, 10364);
                                cvt_s_w(f1, f0);
                                v0 = 0x40C00000;
                                mtc1(v0, f0);
                                div_s(f2, f1, f0);
                                v0 = 0x43800000;
                                mtc1(v0, f1);
                                v0 = 0x3F800000;
                                mtc1(v0, f0);
                                sub_s(f0, f0, f2);
                                mul_s(f0, f1, f0);
                                cvt_w_s(f0, f0);
                                mfc1(v1, f0);
                                v0 = 0x10000;
                                v0 = addu(s1, v0);
                                sw(v1, v0, 10368);
                                v0 = 0x10000;
                                v0 = addu(s1, v0);
                                lw(v1, v0, 10364);
                                v0 = 6;
                                if (v1 == v0) {
                                    // 0x002543d4
                                    charge(ctx, 11);
                                    jal(ctx, 0x2543D4u, gen::fn_sub_258B40_00258b40);
                                    v0 = 0x10000;
                                    v0 = addu(s1, v0);
                                    sw(zero, v0, 10364);
                                    v1 = 1;
                                    v0 = 0x10000;
                                    v0 = addu(s1, v0);
                                    sw(v1, v0, 10360);
                                }
                            } else {
                                // 0x00254348
                                charge(ctx, 2);
                            }
                        }
                    }
                    break;
                case 0x2544E4u:  // table[3]: effect 3, fade in over 30 frames
                    // 0x002544e4
                    charge(ctx, 30);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v0, v0, 10364);
                    v1 = addiu(v0, 1);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    sw(v1, v0, 10364);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lwc1(f0, v0, 10364);
                    cvt_s_w(f1, f0);
                    v0 = 0x41F00000;
                    mtc1(v0, f0);
                    div_s(f1, f1, f0);
                    v0 = 0x43800000;
                    mtc1(v0, f0);
                    mul_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    sw(v1, v0, 10368);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v1, v0, 10364);
                    v0 = 30;
                    if (v1 == v0) {
                        // 0x0025455c
                        charge(ctx, 9);
                        lw(v1, s1, sflcard::kFlags);
                        v0 = si(-65);
                        v1 = v1 & v0;
                        sw(v1, s1, sflcard::kFlags);
                        v0 = si(-257);
                        v0 = v1 & v0;
                        sw(v0, s1, sflcard::kFlags);
                    }
                    break;
                case 0x254580u:  // table[4]: effect 4, fade out over 16 frames
                    // 0x00254580
                    charge(ctx, 33);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v0, v0, 10364);
                    v1 = addiu(v0, 1);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    sw(v1, v0, 10364);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lwc1(f0, v0, 10364);
                    cvt_s_w(f1, f0);
                    v0 = 0x41800000;
                    mtc1(v0, f0);
                    div_s(f2, f1, f0);
                    v0 = 0x43800000;
                    mtc1(v0, f1);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    sub_s(f0, f0, f2);
                    mul_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    sw(v1, v0, 10368);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v1, v0, 10364);
                    v0 = 16;
                    if (v1 == v0) {
                        // 0x00254604
                        charge(ctx, 9);
                        lw(v1, s1, sflcard::kFlags);
                        v0 = si(-65);
                        v1 = v1 & v0;
                        sw(v1, s1, sflcard::kFlags);
                        v0 = si(-2049);
                        v0 = v1 & v0;
                        sw(v0, s1, sflcard::kFlags);
                    }
                    break;
                case 0x254628u:  // table[5]: effect 5, switch to card +75908 over 30 frames (the others fade out)
                    // 0x00254628
                    charge(ctx, 19);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v0, v0, 10364);
                    v1 = addiu(v0, 1);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    sw(v1, v0, 10364);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x41F00000;
                    mtc1(v0, f0);
                    div_s(f2, f1, f0);
                    at = slti(v1, 31);
                    if (at != 0) {
                        // 0x00254674
                        charge(ctx, 12);
                        s2 = 0;
                        v0 = 0x43800000;
                        mtc1(v0, f1);
                        v0 = 0x3F800000;
                        mtc1(v0, f0);
                        sub_s(f0, f0, f2);
                        mul_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(s0, f0);
                        for (;;) {
                            // 0x002546cc
                            charge(ctx, 6);
                            v0 = 0x10000;
                            v0 = addu(s1, v0);
                            lw(v0, v0, 9852);
                            v0 = slt(s2, v0);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x002546a4
                            charge(ctx, 5);
                            v0 = 0x10000;
                            v0 = addu(s1, v0);
                            lw(v0, v0, 10156);
                            if (s2 != v0) {
                                // 0x002546b8
                                charge(ctx, 4);
                                a0 = s2;
                                jal(ctx, 0x2546BCu, gen::fn_sub_255440_00255440);
                                sw(s0, v0, card::kAlpha);
                            }
                            // 0x002546c8
                            charge(ctx, 1);
                            s2 = addiu(s2, 1);
                        }
                    }
                    // 0x002546e4
                    charge(ctx, 6);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v1, v0, 10364);
                    v0 = 30;
                    if (v1 == v0) {
                        // 0x002546fc
                        charge(ctx, 33);
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        lw(a0, v0, 10156);
                        jal(ctx, 0x254708u, gen::fn_sub_255440_00255440);
                        sw(zero, v0, card::kAlpha);
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        lw(a0, v0, 10372);
                        v0 = 0x10000;
                        v0 = addu(s1, v0);
                        sw(a0, v0, 10156);
                        jal(ctx, 0x25472Cu, gen::fn_sub_255440_00255440);
                        s0 = v0;
                        v1 = 256;
                        sw(v1, v0, card::kAlpha);
                        a0 = addiu(sp, 0xC0);
                        a1 = addiu(s0, 24);
                        jal(ctx, 0x254748u, gen::fn_sub_257D90_00257d90);
                        a0 = addiu(s0, 4244);
                        a1 = addiu(sp, 0xC0);
                        jal(ctx, 0x254758u, gen::fn_sub_24F9F0_0024f9f0);
                        mtc1(zero, f12);
                        a0 = addiu(s0, 4144);
                        jal(ctx, 0x254768u, gen::fn_sub_24F2C0_0024f2c0);
                        mtc1(zero, f12);
                        a0 = addiu(s0, 4568);
                        jal(ctx, 0x254778u, gen::fn_sub_250EF0_00250ef0);
                    }
                    // 0x00254780
                    charge(ctx, 22);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(a0, v0, 10156);
                    jal(ctx, 0x25478Cu, gen::fn_sub_255440_00255440);
                    s0 = v0;
                    at = 0x10000;
                    at = at | 0x2800;
                    a0 = addu(s1, at);
                    a1 = addiu(sp, 0x60);
                    jal(ctx, 0x2547A8u, gen::fn_sub_24FBA0_0024fba0);
                    a0 = addiu(s0, 4456);
                    a1 = addiu(sp, 0x60);
                    jal(ctx, 0x2547B8u, gen::fn_sub_24FC40_0024fc40);
                    v0 = 0x10000;
                    v0 = addu(s1, v0);
                    lw(v1, v0, 10364);
                    v0 = 90;
                    if (v1 == v0) {
                        // 0x002547d8
                        charge(ctx, 7);
                        lw(v1, s1, sflcard::kFlags);
                        v0 = si(-65);
                        v1 = v1 & v0;
                        sw(v1, s1, sflcard::kFlags);
                        v0 = si(-4097);
                        v0 = v1 & v0;
                        sw(v0, s1, sflcard::kFlags);
                    }
                    // 0x002547f4
                    charge(ctx, 12);
                    a0 = addiu(s0, 4044);
                    jal(ctx, 0x2547F8u, gen::fn_sub_251030_00251030);
                    a0 = addiu(s0, 4044);
                    jal(ctx, 0x254804u, gen::fn_sub_24DC90_0024dc90);
                    a0 = addiu(s0, 4344);
                    jal(ctx, 0x254810u, gen::fn_sub_251030_00251030);
                    a0 = addiu(s0, 4344);
                    jal(ctx, 0x25481Cu, gen::fn_sub_24DC90_0024dc90);
                    break;
                case 0x254824u:  // table[0]: effect 0: none
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            }
        }
        // 0x00254824
        charge(ctx, 6);
        jal(ctx, 0x254824u, gen::fn_sub_2554F0_002554f0);
        s2 = v0;
        s3 = 0;
        for (;;) {
            // 0x00254858
            charge(ctx, 3);
            v1 = slt(s3, s2);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0025483c
            charge(ctx, 7);
            a0 = s3;
            jal(ctx, 0x254840u, gen::fn_sub_255440_00255440);
            a0 = v0;
            jal(ctx, 0x25484Cu, gen::fn_sub_2564C0_002564c0);
            s3 = addiu(s3, 1);
        }
        // 0x00254864
        charge(ctx, 4);
        lw(v1, s1, sflcard::kFlags);
        v1 = v1 & 0x40;
        if (v1 != 0) {
            // 0x00254874
            charge(ctx, 6);
            v1 = 0x10000;
            v1 = addu(s1, v1);
            lw(v1, v1, 10352);
            a1 = 1;
            if (v1 == a1) {
                // 0x00254910
                charge(ctx, 6);
                v1 = 0x10000;
                v1 = addu(s1, v1);
                lw(a0, v1, 10356);
                v1 = 2;
                if (a0 == v1) {
                    // 0x00254b48
                    charge(ctx, 5);
                    a0 = addiu(s0, 4244);
                    jal(ctx, 0x254B4Cu, gen::fn_sub_250B90_00250b90);
                    if (v0 == 0) {
                        // 0x00254b5c
                        charge(ctx, 4);
                        lw(a0, s1, sflcard::kFlags);
                        v1 = si(-65);
                        v1 = a0 & v1;
                        sw(v1, s1, sflcard::kFlags);
                    }
                } else {
                    // 0x00254928
                    charge(ctx, 2);
                    if (a0 == a1) {
                        // 0x00254a08
                        charge(ctx, 3);
                        s0 = 0;
                        for (;;) {
                            // 0x00254a4c
                            charge(ctx, 6);
                            v1 = 0x10000;
                            v1 = addu(s1, v1);
                            lw(v1, v1, 9852);
                            v1 = slt(s0, v1);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00254a14
                            charge(ctx, 5);
                            v1 = 0x10000;
                            v1 = addu(s1, v1);
                            lw(v1, v1, 10156);
                            if (s0 != v1) {
                                // 0x00254a28
                                charge(ctx, 8);
                                a0 = s0;
                                jal(ctx, 0x254A2Cu, gen::fn_sub_255440_00255440);
                                a0 = addiu(v0, 4456);
                                jal(ctx, 0x254A38u, gen::fn_sub_250E70_00250e70);
                                if (v0 != 0) {
                                    break;
                                }
                                goto L_00254a48;
                            }
                        L_00254a48:
                            charge(ctx, 1);
                            s0 = addiu(s0, 1);
                        }
                        // 0x00254a64
                        charge(ctx, 5);
                        v1 = 0x10000;
                        v1 = addu(s1, v1);
                        lw(v1, v1, 9852);
                        if (s0 == v1) {
                            // 0x00254a78
                            charge(ctx, 37);
                            v0 = 0x10000;
                            v0 = addu(s1, v0);
                            lw(a0, v0, 10156);
                            jal(ctx, 0x254A84u, gen::fn_sub_255440_00255440);
                            s0 = v0;
                            v0 = 0x43A00000;
                            sw(v0, sp, 0xB8);
                            v0 = 0x43380000;
                            sw(v0, sp, 0xBC);
                            v0 = 0x43480000;
                            mtc1(v0, f12);
                            a0 = addiu(s0, 24);
                            jal(ctx, 0x254AACu, gen::fn_sub_20C500_0020c500);
                            a0 = addiu(s0, 24);
                            a1 = addiu(sp, 0xB8);
                            mov_s(f12, f0);
                            a2 = addiu(sp, 0xC0);
                            jal(ctx, 0x254AC4u, gen::fn_sub_20C400_0020c400);
                            lwc1(f1, sp, 0xC4);
                            v0 = 0x42C80000;
                            mtc1(v0, f0);
                            add_s(f0, f1, f0);
                            swc1(f0, sp, 0xC4);
                            a0 = addiu(s0, 4244);
                            a1 = addiu(sp, 0xC0);
                            a2 = 10;
                            jal(ctx, 0x254AF0u, gen::fn_sub_250500_00250500);
                            lw(v1, s1, sflcard::kFlags);
                            v1 = nor(v1, 0);
                            v1 = v1 & 0x2000;
                            if (v1 != 0) {
                                // 0x00254b0c
                                charge(ctx, 6);
                                a0 = 1;
                                a1 = 0;
                                a2 = 6;
                                a3 = 15;
                                jal(ctx, 0x254B1Cu, gen::fn_sub_10A4E0_0010a4e0);
                            }
                            // 0x00254b24
                            charge(ctx, 9);
                            v1 = 0x10000;
                            v1 = addu(s1, v1);
                            sw(zero, v1, 10364);
                            a0 = 2;
                            v1 = 0x10000;
                            v1 = addu(s1, v1);
                            sw(a0, v1, 10356);
                        }
                    } else {
                        // 0x00254930
                        charge(ctx, 2);
                        if (a0 == 0) {
                            // 0x00254940
                            charge(ctx, 10);
                            v0 = 0x10000;
                            v0 = addu(s1, v0);
                            lw(a0, v0, 10156);
                            jal(ctx, 0x25494Cu, gen::fn_sub_255440_00255440);
                            a0 = addiu(v0, 4456);
                            jal(ctx, 0x254958u, gen::fn_sub_250E70_00250e70);
                            if (v0 == 0) {
                                // 0x00254968
                                charge(ctx, 3);
                                s2 = 0;
                                for (;;) {
                                    // 0x002549d8
                                    charge(ctx, 6);
                                    v1 = 0x10000;
                                    v1 = addu(s1, v1);
                                    lw(v1, v1, 9852);
                                    v1 = slt(s2, v1);
                                    if (v1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x00254974
                                    charge(ctx, 5);
                                    v1 = 0x10000;
                                    v1 = addu(s1, v1);
                                    lw(v1, v1, 10156);
                                    if (s2 != v1) {
                                        // 0x00254988
                                        charge(ctx, 19);
                                        a0 = s2;
                                        jal(ctx, 0x25498Cu, gen::fn_sub_255440_00255440);
                                        s0 = v0;
                                        mtc1(zero, f12);
                                        a0 = addiu(s0, 4456);
                                        a1 = addiu(sp, 0xA8);
                                        lwc1(f13, gp, -32184);  // 0x7CAF38
                                        a2 = 12;
                                        jal(ctx, 0x2549ACu, gen::fn_sub_250CF0_00250cf0);
                                        sw(zero, s0, card::kFadeFrame);
                                        v1 = 12;
                                        sw(v1, s0, card::kFadeFrames);
                                        v1 = 3;
                                        sw(v1, s0, card::kFadeKind);
                                        lw(v1, s0, card::kFlags);
                                        v1 = v1 | 0x200;
                                        sw(v1, s0, card::kFlags);
                                    }
                                    // 0x002549d4
                                    charge(ctx, 1);
                                    s2 = addiu(s2, 1);
                                }
                                // 0x002549f0
                                charge(ctx, 6);
                                a0 = 1;
                                v1 = 0x10000;
                                v1 = addu(s1, v1);
                                sw(a0, v1, 10356);
                            }
                        } else {
                            // 0x00254938
                            charge(ctx, 2);
                        }
                    }
                }
            } else {
                // 0x0025488c
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x0025489c
                    charge(ctx, 3);
                    s0 = 0;
                    for (;;) {
                        // 0x002548cc
                        charge(ctx, 6);
                        v1 = 0x10000;
                        v1 = addu(s1, v1);
                        lw(v1, v1, 9852);
                        v1 = slt(s0, v1);
                        if (v1 != 0) {
                            backedge(ctx);
                            // 0x002548a8
                            charge(ctx, 8);
                            a0 = s0;
                            jal(ctx, 0x2548ACu, gen::fn_sub_255440_00255440);
                            a0 = addiu(v0, 4456);
                            jal(ctx, 0x2548B8u, gen::fn_sub_250E70_00250e70);
                            if (v0 == 0) {
                                // 0x002548c8
                                charge(ctx, 1);
                                s0 = addiu(s0, 1);
                                continue;
                            }
                        }
                        break;
                    }
                    // 0x002548e4
                    charge(ctx, 5);
                    v1 = 0x10000;
                    v1 = addu(s1, v1);
                    lw(v1, v1, 9852);
                    if (s0 == v1) {
                        // 0x002548f8
                        charge(ctx, 6);
                        lw(a0, s1, sflcard::kFlags);
                        v1 = si(-65);
                        v1 = a0 & v1;
                        sw(v1, s1, sflcard::kFlags);
                    }
                } else {
                    // 0x00254894
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00254b6c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x002564C0 sub_2564C0 -- 2652 bytes; frame 0x130: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [sflCardUpdate] Per-frame update of one Shuffle Time card (a0; K_Assert lines 188 / 1603): the flipped cards' sway
// (a 90 frame cycle, -1000 * sin) into their point lights; a fade (flag 0x200, +4684: 3 in, 2 out over +4692 frames,
// 1 re-dirty the nodes, 0 the linked cards' nodes); the card's position / orientation from its pose nodes (+4044 /
// +4344, gcPoseGetQuat) into its model (sub_20AC90), or for a stacked card (flag 8) its children's; the point light
// of a highlighted card (flag 0x80) towards the camera (sub_34FF90..sub_34FD70) with alpha +4700; finally each
// model's colour alpha = 255 * the cards' fade (+75904) * the card's own (+4704) (sub_20CC80, the glow sub_20D770 for
// flag 0x80).
// Arguments: a0 the card.
void sub_2564C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x002564c0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpSflCard);  // the Shuffle Time cards (sfl_card.c) 0x7CE354
    if (v0 == 0) {
        // 0x002564f4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x256500u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00256508
    charge(ctx, 65);
    lw(s0, gp, kGpSflCard);  // the Shuffle Time cards (sfl_card.c) 0x7CE354
    v0 = 0x10000;
    v0 = addu(s0, v0);
    lwc1(f0, v0, 9856);
    cvt_s_w(f1, f0);
    v0 = 0x43960000;
    mtc1(v0, f0);
    div_s(f0, f1, f0);
    neg_s(f1, f0);
    v0 = 0x40000000;
    mtc1(v0, f0);
    mul_s(f1, f0, f1);
    lwc1(f0, gp, -32184);  // 0x7CAF38
    mul_s(f20, f0, f1);
    mov_s(f12, f20);
    jal(ctx, 0x25654Cu, gen::fn_sinf_0052e878);
    v0 = lui(0xC47A);
    mtc1(v0, f1);
    mul_s(f0, f1, f0);
    swc1(f0, sp, 0x100);
    mov_s(f12, f20);
    jal(ctx, 0x25656Cu, gen::fn_cosf_0052e6d8);
    v0 = lui(0xC348);
    mtc1(v0, f3);
    v0 = 0x43B40000;
    mtc1(v0, f2);
    mtc1(zero, f1);
    adda_s(f1, f2);
    madd_s(f0, f3, f0);
    swc1(f0, sp, 0x108);
    v0 = 0x10000;
    v0 = addu(s0, v0);
    lwc1(f0, v0, 9856);
    cvt_s_w(f1, f0);
    v0 = 0x42A00000;
    mtc1(v0, f0);
    div_s(f1, f1, f0);
    v0 = 0x40000000;
    mtc1(v0, f0);
    mul_s(f1, f0, f1);
    lwc1(f0, gp, -32184);  // 0x7CAF38
    mul_s(f12, f0, f1);
    jal(ctx, 0x2565D0u, gen::fn_cosf_0052e6d8);
    v0 = 0x42C80000;
    mtc1(v0, f3);
    v0 = 0x42F00000;
    mtc1(v0, f2);
    mtc1(zero, f1);
    adda_s(f1, f2);
    madd_s(f0, f3, f0);
    swc1(f0, sp, 0x104);
    lw(v0, s1, card::kFlags);
    v0 = v0 & 0x80;
    if (v0 != 0) {
        // 0x0025660c
        charge(ctx, 7);
        lw(v0, s1, card::kSway);
        v1 = addiu(v0, 1);
        sw(v1, s1, card::kSway);
        v0 = 90;
        div(v1, v0);
        mfhi(v0);
        sw(v0, s1, card::kSway);
    }
    // 0x00256628
    charge(ctx, 9);
    a0 = s1;
    a1 = addiu(sp, 0xC0);
    a2 = addiu(sp, 0x128);
    jal(ctx, 0x256634u, gen::fn_sub_256FA0_00256fa0);
    a0 = 0;
    lw(v1, sp, 0x128);
    for (;;) {
        // 0x00256674
        charge(ctx, 3);
        v0 = slt(a0, v1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0025664c
        charge(ctx, 10);
        v0 = sll(a0, 2);
        v0 = addu(v0, sp);
        lw(v0, v0, 192);
        lwc1(f2, sp, 0x100);
        lwc1(f1, sp, 0x104);
        lwc1(f0, sp, 0x108);
        swc1(f2, v0, 4012);
        swc1(f1, v0, 4016);
        swc1(f0, v0, 4020);
        a0 = addiu(a0, 1);
    }
    // 0x00256680
    charge(ctx, 4);
    lw(v0, s1, card::kFlags);
    v0 = v0 & 0x200;
    if (v0 != 0) {
        // 0x00256690
        charge(ctx, 7);
        lw(v0, s1, card::kFadeFrame);
        v0 = addiu(v0, 1);
        sw(v0, s1, card::kFadeFrame);
        lw(v1, s1, card::kFadeKind);
        v0 = 3;
        if (v1 == v0) {
            // 0x00256848
            charge(ctx, 13);
            lwc1(f0, s1, card::kFadeFrame);
            cvt_s_w(f1, f0);
            lwc1(f0, s1, card::kFadeFrames);
            cvt_s_w(f0, f0);
            div_s(f1, f1, f0);
            v0 = 0x43800000;
            mtc1(v0, f0);
            mul_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sw(v0, s1, card::kGlow);
        } else {
            // 0x002566ac
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x00256800
                charge(ctx, 18);
                lwc1(f0, s1, card::kFadeFrame);
                cvt_s_w(f1, f0);
                lwc1(f0, s1, card::kFadeFrames);
                cvt_s_w(f0, f0);
                div_s(f2, f1, f0);
                v0 = 0x43800000;
                mtc1(v0, f1);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f0, f0, f2);
                mul_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v0, f0);
                sw(v0, s1, card::kGlow);
            } else {
                // 0x002566b8
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00256790
                    charge(ctx, 28);
                    lwc1(f0, s1, card::kFadeFrame);
                    cvt_s_w(f1, f0);
                    lwc1(f0, s1, card::kFadeFrames);
                    cvt_s_w(f0, f0);
                    div_s(f20, f1, f0);
                    a0 = addiu(s1, 4144);
                    mov_s(f12, f20);
                    jal(ctx, 0x2567B0u, gen::fn_sub_24F2C0_0024f2c0);
                    a0 = addiu(s1, 4568);
                    mov_s(f12, f20);
                    jal(ctx, 0x2567C0u, gen::fn_sub_250EF0_00250ef0);
                    a0 = addiu(s1, 4044);
                    jal(ctx, 0x2567CCu, gen::fn_sub_251030_00251030);
                    a0 = addiu(s1, 4044);
                    jal(ctx, 0x2567D8u, gen::fn_sub_24DC90_0024dc90);
                    a0 = addiu(s1, 4344);
                    jal(ctx, 0x2567E4u, gen::fn_sub_251030_00251030);
                    a0 = addiu(s1, 4344);
                    jal(ctx, 0x2567F0u, gen::fn_sub_24DC90_0024dc90);
                } else {
                    // 0x002566c4
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x002566d4
                        charge(ctx, 17);
                        lwc1(f0, s1, card::kFadeFrame);
                        cvt_s_w(f1, f0);
                        lwc1(f0, s1, card::kFadeFrames);
                        cvt_s_w(f0, f0);
                        div_s(f20, f1, f0);
                        a0 = s1;
                        a1 = addiu(sp, 0xC0);
                        a2 = addiu(sp, 0x12C);
                        jal(ctx, 0x2566F4u, gen::fn_sub_259190_00259190);
                        s2 = 0;
                        v0 = 0x3F800000;
                        mtc1(v0, f0);
                        sub_s(f20, f0, f20);
                        for (;;) {
                            // 0x00256778
                            charge(ctx, 4);
                            lw(v0, sp, 0x12C);
                            v0 = slt(s2, v0);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00256718
                            charge(ctx, 24);
                            v0 = sll(s2, 2);
                            v0 = addu(v0, sp);
                            lw(s3, v0, 192);
                            a0 = addiu(s3, 4144);
                            mov_s(f12, f20);
                            jal(ctx, 0x25672Cu, gen::fn_sub_24F2C0_0024f2c0);
                            a0 = addiu(s3, 4568);
                            mov_s(f12, f20);
                            jal(ctx, 0x25673Cu, gen::fn_sub_250EF0_00250ef0);
                            a0 = addiu(s3, 4044);
                            jal(ctx, 0x256748u, gen::fn_sub_251030_00251030);
                            a0 = addiu(s3, 4044);
                            jal(ctx, 0x256754u, gen::fn_sub_24DC90_0024dc90);
                            a0 = addiu(s3, 4344);
                            jal(ctx, 0x256760u, gen::fn_sub_251030_00251030);
                            a0 = addiu(s3, 4344);
                            jal(ctx, 0x25676Cu, gen::fn_sub_24DC90_0024dc90);
                            s2 = addiu(s2, 1);
                        }
                        // 0x00256788
                        charge(ctx, 2);
                    } else {
                        // 0x002566cc
                        charge(ctx, 2);
                    }
                }
            }
        }
        // 0x0025687c
        charge(ctx, 4);
        lw(v1, s1, card::kFadeFrame);
        lw(v0, s1, card::kFadeFrames);
        if (v1 == v0) {
            // 0x0025688c
            charge(ctx, 4);
            lw(v1, s1, card::kFlags);
            v0 = si(-513);
            v0 = v1 & v0;
            sw(v0, s1, card::kFlags);
        }
    }
    // 0x0025689c
    charge(ctx, 5);
    lw(v1, s1, card::kFlags);
    v0 = nor(v1, 0);
    v0 = v0 & 0x8;
    if (v0 == 0) {
        // 0x00256934
        charge(ctx, 3);
        v0 = v1 & 0x10;
        if (v0 == 0) {
            // 0x00256a38
            charge(ctx, 3);
            v0 = v1 & 0x20;
            if (v0 != 0) {
                // 0x00256a44
                charge(ctx, 5);
                a0 = addiu(s1, 4244);
                jal(ctx, 0x256A48u, gen::fn_sub_250B90_00250b90);
                if (v0 == 0) {
                    // 0x00256a58
                    charge(ctx, 4);
                    lw(v1, s1, card::kFlags);
                    v0 = si(-33);
                    v0 = v1 & v0;
                    sw(v0, s1, card::kFlags);
                }
            }
        } else {
            // 0x00256940
            charge(ctx, 3);
            v0 = v1 & 0x20;
            if (v0 == 0) {
                // 0x0025694c
                charge(ctx, 5);
                a0 = 0x690000;
                a0 = addiu(a0, -5632);  // "sfl_card.c"
                a1 = 1603;
                jal(ctx, 0x256958u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x00256960
            charge(ctx, 8);
            a0 = s1;
            a1 = addiu(sp, 0xC0);
            a2 = addiu(sp, 0x12C);
            jal(ctx, 0x25696Cu, gen::fn_sub_259190_00259190);
            s3 = 0;
            for (;;) {
                // 0x002569c4
                charge(ctx, 4);
                lw(v1, sp, 0x12C);
                v0 = slt(s3, v1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00256980
                charge(ctx, 7);
                v0 = sll(s3, 2);
                v0 = addu(v0, sp);
                lw(s2, v0, 192);
                lw(v0, s2, 0);
                v0 = v0 & 0x20;
                if (v0 != 0) {
                    // 0x0025699c
                    charge(ctx, 5);
                    a0 = addiu(s2, 4244);
                    jal(ctx, 0x2569A0u, gen::fn_sub_250B90_00250b90);
                    if (v0 == 0) {
                        // 0x002569b0
                        charge(ctx, 4);
                        lw(v1, s2, 0);
                        v0 = si(-33);
                        v0 = v1 & v0;
                        sw(v0, s2, 0);
                    }
                }
                // 0x002569c0
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
            // 0x002569d4
            charge(ctx, 3);
            a0 = 0;
            for (;;) {
                // 0x00256a00
                charge(ctx, 3);
                v0 = slt(a0, v1);
                if (v0 != 0) {
                    backedge(ctx);
                    // 0x002569e0
                    charge(ctx, 7);
                    v0 = sll(a0, 2);
                    v0 = addu(v0, sp);
                    lw(v0, v0, 192);
                    lw(v0, v0, 0);
                    v0 = v0 & 0x20;
                    if (v0 == 0) {
                        // 0x002569fc
                        charge(ctx, 1);
                        a0 = addiu(a0, 1);
                        continue;
                    }
                }
                break;
            }
            // 0x00256a0c
            charge(ctx, 2);
            if (a0 == v1) {
                // 0x00256a14
                charge(ctx, 9);
                lw(v1, s1, card::kFlags);
                v0 = si(-17);
                v1 = v1 & v0;
                sw(v1, s1, card::kFlags);
                v0 = si(-33);
                v0 = v1 & v0;
                sw(v0, s1, card::kFlags);
            }
        }
        // 0x00256a68
        charge(ctx, 14);
        a0 = s1;
        a1 = addiu(sp, 0x90);
        a2 = addiu(sp, 0x12C);
        jal(ctx, 0x256A74u, gen::fn_sub_259190_00259190);
        a0 = s1;
        a1 = addiu(sp, 0x70);
        a2 = addiu(sp, 0x11C);
        jal(ctx, 0x256A88u, gen::fn_sub_256FA0_00256fa0);
        lw(v0, s1, card::kFlags);
        v0 = v0 & 0x10;
        if (v0 == 0) {
            // 0x00256b24
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x00256b84
                charge(ctx, 4);
                lw(v0, sp, 0x11C);
                v0 = slt(s2, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00256b30
                charge(ctx, 21);
                lw(s3, sp, 0x70);
                a0 = addiu(s1, 4044);
                a1 = addiu(s3, 56);
                jal(ctx, 0x256B3Cu, gen::fn_sub_24F960_0024f960);
                a0 = addiu(s1, 4344);
                a1 = addiu(sp, 0xB0);
                jal(ctx, 0x256B4Cu, gen::fn_sub_24FBA0_0024fba0);
                lwc1(f3, sp, 0xB0);
                lwc1(f2, sp, 0xB4);
                lwc1(f1, sp, 0xB8);
                lwc1(f0, sp, 0xBC);
                swc1(f3, s3, 40);
                swc1(f2, s3, 44);
                swc1(f1, s3, 48);
                swc1(f0, s3, 52);
                a0 = addiu(s3, 24);
                jal(ctx, 0x256B78u, gen::fn_sub_20AC90_0020ac90);
                s2 = addiu(s2, 1);
            }
        } else {
            // 0x00256aa0
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x00256b0c
                charge(ctx, 4);
                lw(v0, sp, 0x11C);
                v0 = slt(s2, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00256aac
                charge(ctx, 24);
                v0 = sll(s2, 2);
                v0 = addu(v0, sp);
                lw(s4, v0, 144);
                lw(s3, v0, 112);
                a0 = addiu(s4, 4044);
                a1 = addiu(s3, 56);
                jal(ctx, 0x256AC4u, gen::fn_sub_24F960_0024f960);
                a0 = addiu(s4, 4344);
                a1 = addiu(sp, 0xB0);
                jal(ctx, 0x256AD4u, gen::fn_sub_24FBA0_0024fba0);
                lwc1(f3, sp, 0xB0);
                lwc1(f2, sp, 0xB4);
                lwc1(f1, sp, 0xB8);
                lwc1(f0, sp, 0xBC);
                swc1(f3, s3, 40);
                swc1(f2, s3, 44);
                swc1(f1, s3, 48);
                swc1(f0, s3, 52);
                a0 = addiu(s3, 24);
                jal(ctx, 0x256B00u, gen::fn_sub_20AC90_0020ac90);
                s2 = addiu(s2, 1);
            }
            // 0x00256b1c
            charge(ctx, 2);
        }
    } else {
        // 0x002568b0
        charge(ctx, 3);
        v0 = v1 & 0x20;
        if (v0 != 0) {
            // 0x002568bc
            charge(ctx, 5);
            a0 = addiu(s1, 4244);
            jal(ctx, 0x2568C0u, gen::fn_sub_250B90_00250b90);
            if (v0 == 0) {
                // 0x002568d0
                charge(ctx, 4);
                lw(v1, s1, card::kFlags);
                v0 = si(-33);
                v0 = v1 & v0;
                sw(v0, s1, card::kFlags);
            }
        }
        // 0x002568e0
        charge(ctx, 21);
        a0 = addiu(s1, 4044);
        a1 = addiu(s1, 56);
        jal(ctx, 0x2568E8u, gen::fn_sub_24F960_0024f960);
        a0 = addiu(s1, 4344);
        a1 = addiu(sp, 0xB0);
        jal(ctx, 0x2568F8u, gen::fn_sub_24FBA0_0024fba0);
        lwc1(f3, sp, 0xB0);
        lwc1(f2, sp, 0xB4);
        lwc1(f1, sp, 0xB8);
        lwc1(f0, sp, 0xBC);
        swc1(f3, s1, card::kQuat);
        swc1(f2, s1, card::kQuat + 4);
        swc1(f1, s1, card::kQuat + 8);
        swc1(f0, s1, card::kQuat + 12);
        a0 = addiu(s1, 24);
        jal(ctx, 0x256924u, gen::fn_sub_20AC90_0020ac90);
    }
    // 0x00256b94
    charge(ctx, 4);
    lw(v0, s1, card::kFlags);
    v0 = v0 & 0x80;
    if (v0 != 0) {
        // 0x00256ba4
        charge(ctx, 3);
        lw(v0, s1, card::kGlow);
        if (v0 != 0) {
            // 0x00256bb0
            charge(ctx, 14);
            jal(ctx, 0x256BB0u, gen::fn_sub_198590_00198590);
            lw(a0, v0, 4);
            jal(ctx, 0x256BBCu, gen::fn_sub_4CB2F0_004cb2f0);
            s3 = addiu(v0, 48);
            a0 = s1;
            a1 = addiu(sp, 0xC0);
            a2 = addiu(sp, 0x128);
            jal(ctx, 0x256BD4u, gen::fn_sub_256FA0_00256fa0);
            s4 = 0;
            for (;;) {
                // 0x00256d84
                charge(ctx, 4);
                lw(v0, sp, 0x128);
                v0 = slt(s4, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00256be8
                charge(ctx, 63);
                v0 = sll(s4, 2);
                v0 = addu(v0, sp);
                lw(s2, v0, 192);
                a0 = addiu(s1, 4044);
                a1 = addiu(sp, 0x110);
                jal(ctx, 0x256BFCu, gen::fn_sub_24F960_0024f960);
                lwc1(f1, sp, 0x114);
                v0 = 0x42480000;
                mtc1(v0, f0);
                sub_s(f2, f1, f0);
                swc1(f2, sp, 0x114);
                lwc1(f1, sp, 0x110);
                lwc1(f0, s3, 0);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xE0);
                lwc1(f0, s3, 4);
                sub_s(f0, f2, f0);
                swc1(f0, sp, 0xE4);
                lwc1(f1, s3, 8);
                lwc1(f0, sp, 0x118);
                sub_s(f0, f0, f1);
                swc1(f0, sp, 0xE8);
                a0 = addiu(sp, 0xE0);
                a1 = a0;
                jal(ctx, 0x256C50u, gen::fn_sub_4C69F0_004c69f0);
                lwc1(f3, sp, 0xE0);
                swc1(f3, sp, 0xE0);
                lwc1(f2, sp, 0xE4);
                swc1(f2, sp, 0xE4);
                lwc1(f1, sp, 0xE8);
                swc1(f1, sp, 0xE8);
                lwc1(f0, sp, 0x110);
                add_s(f0, f3, f0);
                swc1(f0, sp, 0xF0);
                lwc1(f0, sp, 0x114);
                add_s(f0, f2, f0);
                swc1(f0, sp, 0xF4);
                lwc1(f0, sp, 0x118);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0xF8);
                v0 = 255;
                sb(v0, sp, 0x120);
                sb(v0, sp, 0x121);
                sb(v0, sp, 0x122);
                lwc1(f0, s1, card::kGlow);
                cvt_s_w(f1, f0);
                v0 = 0x437F0000;
                mtc1(v0, f0);
                mul_s(f1, f0, f1);
                v0 = 0x43800000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x00256cfc
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x00256ce4
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x00256d14
                charge(ctx, 28);
                sb(v1, sp, 0x123);
                lw(a0, s2, 4680);
                a1 = addiu(sp, 0x120);
                jal(ctx, 0x256D20u, gen::fn_sub_34FF90_0034ff90);
                lw(a0, s2, 4680);
                lwc1(f12, gp, -32656);  // 0x7CAD60
                jal(ctx, 0x256D30u, gen::fn_sub_34FF70_0034ff70);
                lw(a0, s2, 4680);
                a1 = addiu(sp, 0xF0);
                jal(ctx, 0x256D40u, gen::fn_sub_34FDF0_0034fdf0);
                v0 = lui(0x8000);
                mtc1(v0, f12);
                mtc1(zero, f13);
                lw(a0, s2, 4680);
                mov_s(f14, f13);
                jal(ctx, 0x256D5Cu, gen::fn_sub_34FE30_0034fe30);
                lw(a0, s2, 4680);
                jal(ctx, 0x256D68u, gen::fn_sub_34FD30_0034fd30);
                lw(a0, s2, 4680);
                a1 = 5;
                jal(ctx, 0x256D78u, gen::fn_sub_34FD70_0034fd70);
                s4 = addiu(s4, 1);
            }
        }
    }
    // 0x00256d94
    charge(ctx, 8);
    a0 = s1;
    a1 = addiu(sp, 0xC0);
    a2 = addiu(sp, 0x128);
    jal(ctx, 0x256DA0u, gen::fn_sub_256FA0_00256fa0);
    s3 = 0;
    for (;;) {
        // 0x00256ee0
        charge(ctx, 4);
        lw(v1, sp, 0x128);
        v1 = slt(s3, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00256db4
        charge(ctx, 19);
        v0 = sll(s3, 2);
        v0 = addu(v0, sp);
        lw(s2, v0, 192);
        v0 = 0x10000;
        v0 = addu(s0, v0);
        lwc1(f0, v0, 10368);
        cvt_s_w(f0, f0);
        v0 = 0x43800000;
        mtc1(v0, f1);
        div_s(f20, f0, f1);
        lwc1(f0, s2, 4704);
        cvt_s_w(f0, f0);
        div_s(f21, f0, f1);
        lw(v0, s1, card::kFlags);
        v0 = v0 & 0x80;
        if (v0 != 0) {
            // 0x00256e00
            charge(ctx, 14);
            lwc1(f0, s1, card::kSway);
            cvt_s_w(f1, f0);
            v0 = 0x42B40000;
            mtc1(v0, f0);
            div_s(f1, f1, f0);
            v0 = 0x40000000;
            mtc1(v0, f0);
            mul_s(f1, f0, f1);
            lwc1(f0, gp, -32184);  // 0x7CAF38
            mul_s(f12, f0, f1);
            jal(ctx, 0x256E30u, gen::fn_sinf_0052e878);
        }
        // 0x00256e38
        charge(ctx, 15);
        v0 = 255;
        sb(v0, sp, 0x124);
        sb(v0, sp, 0x125);
        sb(v0, sp, 0x126);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f0, f0, f20);
        mul_s(f1, f0, f21);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x00256e8c
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00256e74
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00256ea4
        charge(ctx, 9);
        sb(v1, sp, 0x127);
        a0 = addiu(s2, 24);
        a1 = addiu(sp, 0x124);
        jal(ctx, 0x256EB0u, gen::fn_sub_20CC80_0020cc80);
        lw(v1, s1, card::kFlags);
        v1 = v1 & 0x80;
        if (v1 != 0) {
            // 0x00256ec8
            charge(ctx, 5);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            a0 = addiu(s2, 24);
            jal(ctx, 0x256ED4u, gen::fn_sub_20D770_0020d770);
        }
        // 0x00256edc
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x00256ef0
    charge(ctx, 11);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x130);
}

// 0x00258B40 sub_258B40 -- 1076 bytes; frame 0xC0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflCardsShuffle] Shuffles the Shuffle Time cards (K_Assert lines 188 / 1146): releases the stacked cards
// (sub_258F80), then permutes the slot numbers 0..n-1 (n = +75388) with (rand() & 15) + 1024 random swaps of two
// different slots (libc rand, sub_488F30), gives each card (by its old slot, +16) its new slot, and sends every card
// to its new place: x from sub_20C660(slot, n), y 184, projected (sub_20C500 / sub_20C400) and 100 further, a
// straight move with the wander / wobble restarted.
void sub_258B40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00258b40
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpSflCard);  // the Shuffle Time cards (sfl_card.c) 0x7CE354
    if (v0 == 0) {
        // 0x00258b6c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x258B78u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00258b80
    charge(ctx, 4);
    lw(s0, gp, kGpSflCard);  // the Shuffle Time cards (sfl_card.c) 0x7CE354
    s1 = 0;
    for (;;) {
        // 0x00258bb8
        charge(ctx, 6);
        v0 = 0x10000;
        v0 = addu(s0, v0);
        lw(v1, v0, 9860);
        v0 = slt(s1, v1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00258b90
        charge(ctx, 10);
        v0 = addiu(v1, -1);
        v0 = subu(v0, s1);
        v0 = sll(v0, 2);
        v1 = addu(s0, v0);
        v0 = 0x10000;
        v0 = addu(v1, v0);
        lw(a0, v0, 9828);
        jal(ctx, 0x258BACu, gen::fn_sub_258F80_00258f80);
        s1 = addiu(s1, 1);
    }
    // 0x00258bd0
    charge(ctx, 6);
    a0 = 0;
    v0 = 0x10000;
    v0 = addu(s0, v0);
    lw(v1, v0, 9852);
    for (;;) {
        // 0x00258bf8
        charge(ctx, 3);
        v0 = slt(a0, v1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00258be8
        charge(ctx, 4);
        v0 = sll(a0, 2);
        v0 = addu(v0, sp);
        sw(a0, v0, 112);
        a0 = addiu(a0, 1);
    }
    // 0x00258c04
    charge(ctx, 8);
    s1 = 1024;
    jal(ctx, 0x258C08u, gen::fn_sub_488F30_00488f30);
    v1 = v0 & 0xF;
    s5 = addu(s1, v1);
    s1 = 0;
    for (;;) {
        // 0x00258cac
        charge(ctx, 3);
        v1 = slt(s1, s5);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00258c24
        charge(ctx, 18);
        jal(ctx, 0x258C24u, gen::fn_sub_488F30_00488f30);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        lw(v1, v1, 9852);
        divu(v0, v1);
        mfhi(s4);
        jal(ctx, 0x258C40u, gen::fn_sub_488F30_00488f30);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        lw(v1, v1, 9852);
        v1 = addiu(v1, -1);
        divu(v0, v1);
        mfhi(a0);
        v1 = slt(a0, s4);
        if (v1 != 0) {
            // 0x00258c78
            charge(ctx, 2);
            a3 = s4;
            s4 = a0;
        } else {
            // 0x00258c6c
            charge(ctx, 3);
            a3 = addiu(a0, 1);
        }
        // 0x00258c80
        charge(ctx, 11);
        v1 = sll(s4, 2);
        v1 = addu(v1, sp);
        a2 = addiu(v1, 112);
        lw(a1, a2, 0);
        v1 = sll(a3, 2);
        v1 = addu(v1, sp);
        a0 = addiu(v1, 112);
        lw(v1, a0, 0);
        sw(v1, a2, 0);
        sw(a1, a0, 0);
        s1 = addiu(s1, 1);
    }
    // 0x00258cb8
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x00258d54
        charge(ctx, 6);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        lw(v1, v1, 9852);
        v1 = slt(s1, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00258cc4
        charge(ctx, 3);
        lw(v1, gp, kGpSflCard);  // the Shuffle Time cards (sfl_card.c) 0x7CE354
        if (v1 == 0) {
            // 0x00258cd0
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -5632);  // "sfl_card.c"
            a1 = 188;
            jal(ctx, 0x258CDCu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x00258ce4
        charge(ctx, 6);
        lw(a0, gp, kGpSflCard);  // the Shuffle Time cards (sfl_card.c) 0x7CE354
        v1 = 0x10000;
        v1 = addu(a0, v1);
        lw(a0, v1, 9820);
        for (;;) {
            // 0x00258d20
            charge(ctx, 2);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00258cfc
            charge(ctx, 5);
            s3 = a0;
            lw(v1, a0, 0);
            v1 = v1 & 0x2;
            if (v1 == 0) {
                // 0x00258d10
                charge(ctx, 3);
                lw(v1, a0, 16);
                if (v1 == s1) {
                    break;
                }
                goto L_00258d1c;
            }
        L_00258d1c:
            charge(ctx, 1);
            lw(a0, a0, 4036);
        }
        // 0x00258d28
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x00258d30
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -5632);  // "sfl_card.c"
            a1 = 1146;
            jal(ctx, 0x258D3Cu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x00258d44
        charge(ctx, 4);
        v1 = sll(s1, 2);
        v1 = addu(v1, sp);
        sw(s3, v1, 144);
        s1 = addiu(s1, 1);
    }
    // 0x00258d6c
    charge(ctx, 3);
    a1 = 0;
    for (;;) {
        // 0x00258d90
        charge(ctx, 6);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        lw(v1, v1, 9852);
        v1 = slt(a1, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00258d78
        charge(ctx, 6);
        v1 = sll(a1, 2);
        v1 = addu(v1, sp);
        lw(a0, v1, 112);
        lw(v1, v1, 144);
        sw(a0, v1, 16);
        a1 = addiu(a1, 1);
    }
    // 0x00258da8
    charge(ctx, 7);
    lw(a0, s0, sflcard::kFlags);
    v1 = si(-17);
    v1 = a0 & v1;
    sw(v1, s0, sflcard::kFlags);
    s1 = 0;
    for (;;) {
        // 0x00258f34
        charge(ctx, 6);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        lw(v1, v1, 9852);
        v1 = slt(s1, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00258dc4
        charge(ctx, 3);
        lw(v0, gp, kGpSflCard);  // the Shuffle Time cards (sfl_card.c) 0x7CE354
        if (v0 == 0) {
            // 0x00258dd0
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -5632);  // "sfl_card.c"
            a1 = 188;
            jal(ctx, 0x258DDCu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x00258de4
        charge(ctx, 6);
        lw(v1, gp, kGpSflCard);  // the Shuffle Time cards (sfl_card.c) 0x7CE354
        v0 = 0x10000;
        v0 = addu(v1, v0);
        lw(v1, v0, 9820);
        for (;;) {
            // 0x00258e20
            charge(ctx, 2);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00258dfc
            charge(ctx, 5);
            s2 = v1;
            lw(v0, v1, 0);
            v0 = v0 & 0x2;
            if (v0 == 0) {
                // 0x00258e10
                charge(ctx, 3);
                lw(v0, v1, 16);
                if (v0 == s1) {
                    break;
                }
                goto L_00258e1c;
            }
        L_00258e1c:
            charge(ctx, 1);
            lw(v1, v1, 4036);
        }
        // 0x00258e28
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00258e30
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -5632);  // "sfl_card.c"
            a1 = 1146;
            jal(ctx, 0x258E3Cu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x00258e44
        charge(ctx, 60);
        a0 = s2;
        a1 = addiu(sp, 0x90);
        a2 = addiu(sp, 0xBC);
        jal(ctx, 0x258E50u, gen::fn_sub_256FA0_00256fa0);
        lw(a0, s2, 16);
        v0 = 0x10000;
        v0 = addu(s0, v0);
        lw(a1, v0, 9852);
        jal(ctx, 0x258E68u, gen::fn_sub_20C660_0020c660);
        swc1(f0, sp, 0xA8);
        v0 = 0x43380000;
        sw(v0, sp, 0xAC);
        lw(v1, sp, 0x90);
        v0 = 0x42B40000;
        mtc1(v0, f12);
        a0 = addiu(v1, 24);
        jal(ctx, 0x258E8Cu, gen::fn_sub_20C500_0020c500);
        lw(v0, sp, 0x90);
        a0 = addiu(v0, 24);
        a1 = addiu(sp, 0xA8);
        mov_s(f12, f0);
        a2 = addiu(sp, 0xB0);
        jal(ctx, 0x258EA8u, gen::fn_sub_20C400_0020c400);
        lwc1(f1, sp, 0xB4);
        v0 = 0x42C80000;
        mtc1(v0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xB4);
        a0 = addiu(s2, 4244);
        jal(ctx, 0x258ECCu, gen::fn_sub_250480_00250480);
        a0 = addiu(s2, 4244);
        a1 = addiu(sp, 0xB0);
        jal(ctx, 0x258EDCu, gen::fn_sub_24F9F0_0024f9f0);
        a0 = addiu(s2, 4456);
        jal(ctx, 0x258EE8u, gen::fn_sub_250C70_00250c70);
        a0 = addiu(s2, 4144);
        jal(ctx, 0x258EF4u, gen::fn_sub_24F410_0024f410);
        a0 = addiu(s2, 4568);
        jal(ctx, 0x258F00u, gen::fn_sub_24FF10_0024ff10);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        a0 = addiu(s2, 4144);
        jal(ctx, 0x258F14u, gen::fn_sub_24F2C0_0024f2c0);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        a0 = addiu(s2, 4568);
        jal(ctx, 0x258F28u, gen::fn_sub_250EF0_00250ef0);
        s1 = addiu(s1, 1);
    }
    // 0x00258f4c
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// 0x0025A130 sub_25A130 -- 780 bytes; frame 0x20: ra sp+0x0
// [sflCursorUpdate] Per-frame update of the Shuffle Time card cursor (sfl_cursor.c; K_Assert line 71) while open: the
// 60-frame blink counter (+52); a running move (flag 2) by its kind (+3232): 0 slides the cursor from +4 to +16 over
// 4 frames (into +28), 1 waits 4 frames, 2 waits 16, 3 waits 16 then closes; each of the six card marks (528 bytes
// from +64): the selected one (+48) brightens (+64 by 25 and +68 by 64 up to 256), the others fade (8 / 12 per
// frame); then places the quads (sub_25AAD0(256)).
void sub_25A130(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7};
    // 0x0025a130
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpSflCursor);  // the Shuffle Time card cursor (sfl_cursor.c) 0x7CE360
    if (v1 == 0) {
        // 0x0025a144
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5192);  // "sfl_cursor.c"
        a1 = 71;
        jal(ctx, 0x25A150u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025a158
    charge(ctx, 6);
    lw(v1, gp, kGpSflCursor);  // the Shuffle Time card cursor (sfl_cursor.c) 0x7CE360
    lw(a0, v1, sflcur::kFlags);
    a0 = nor(a0, 0);
    a0 = a0 & 0x1;
    if (a0 == 0) {
        // 0x0025a170
        charge(ctx, 11);
        lw(v0, v1, sflcur::kBlink);
        a0 = addiu(v0, 1);
        sw(a0, v1, sflcur::kBlink);
        v0 = 60;
        div(a0, v0);
        mfhi(v0);
        sw(v0, v1, sflcur::kBlink);
        lw(v0, v1, sflcur::kFlags);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x0025a19c
            charge(ctx, 4);
            lw(a0, v1, sflcur::kMoveKind);
            v0 = 2;
            if (a0 == v0) {
                // 0x0025a300
                charge(ctx, 6);
                lw(v0, v1, sflcur::kMoveFrame);
                a0 = addiu(v0, 1);
                sw(a0, v1, sflcur::kMoveFrame);
                v0 = 16;
                if (a0 == v0) {
                    // 0x0025a318
                    charge(ctx, 4);
                    lw(a0, v1, sflcur::kFlags);
                    v0 = si(-3);
                    v0 = a0 & v0;
                    sw(v0, v1, sflcur::kFlags);
                }
            } else {
                // 0x0025a1ac
                charge(ctx, 3);
                v0 = 3;
                if (a0 == v0) {
                    // 0x0025a2c4
                    charge(ctx, 6);
                    lw(v0, v1, sflcur::kMoveFrame);
                    a0 = addiu(v0, 1);
                    sw(a0, v1, sflcur::kMoveFrame);
                    v0 = 16;
                    if (a0 == v0) {
                        // 0x0025a2dc
                        charge(ctx, 9);
                        lw(a0, v1, sflcur::kFlags);
                        v0 = si(-3);
                        a0 = a0 & v0;
                        sw(a0, v1, sflcur::kFlags);
                        v0 = si(-2);
                        v0 = a0 & v0;
                        sw(v0, v1, sflcur::kFlags);
                    }
                } else {
                    // 0x0025a1b8
                    charge(ctx, 3);
                    v0 = 1;
                    if (a0 == v0) {
                        // 0x0025a294
                        charge(ctx, 6);
                        lw(v0, v1, sflcur::kMoveFrame);
                        a0 = addiu(v0, 1);
                        sw(a0, v1, sflcur::kMoveFrame);
                        v0 = 4;
                        if (a0 == v0) {
                            // 0x0025a2ac
                            charge(ctx, 6);
                            lw(a0, v1, sflcur::kFlags);
                            v0 = si(-3);
                            v0 = a0 & v0;
                            sw(v0, v1, sflcur::kFlags);
                        }
                    } else {
                        // 0x0025a1c4
                        charge(ctx, 2);
                        if (a0 == 0) {
                            // 0x0025a1d4
                            charge(ctx, 6);
                            lw(v0, v1, sflcur::kMoveFrame);
                            a0 = addiu(v0, 1);
                            sw(a0, v1, sflcur::kMoveFrame);
                            v0 = 4;
                            if (a0 == v0) {
                                // 0x0025a1ec
                                charge(ctx, 4);
                                lw(a0, v1, sflcur::kFlags);
                                v0 = si(-3);
                                v0 = a0 & v0;
                                sw(v0, v1, sflcur::kFlags);
                            }
                            // 0x0025a1fc
                            charge(ctx, 38);
                            lwc1(f0, v1, sflcur::kMoveFrame);
                            cvt_s_w(f1, f0);
                            v0 = 0x40800000;
                            mtc1(v0, f0);
                            div_s(f7, f1, f0);
                            lwc1(f6, v1, sflcur::kFrom);
                            lwc1(f0, v1, sflcur::kTo);
                            sub_s(f5, f0, f6);
                            swc1(f5, sp, 0x10);
                            lwc1(f4, v1, sflcur::kFrom + 4);
                            lwc1(f0, v1, sflcur::kTo + 4);
                            sub_s(f2, f0, f4);
                            swc1(f2, sp, 0x14);
                            lwc1(f3, v1, sflcur::kFrom + 8);
                            lwc1(f0, v1, sflcur::kTo + 8);
                            sub_s(f1, f0, f3);
                            swc1(f1, sp, 0x18);
                            mul_s(f0, f5, f7);
                            swc1(f0, sp, 0x10);
                            mul_s(f2, f2, f7);
                            swc1(f2, sp, 0x14);
                            mul_s(f1, f1, f7);
                            swc1(f1, sp, 0x18);
                            add_s(f0, f0, f6);
                            swc1(f0, sp, 0x10);
                            add_s(f0, f2, f4);
                            swc1(f0, sp, 0x14);
                            add_s(f0, f1, f3);
                            swc1(f0, sp, 0x18);
                            lwc1(f2, sp, 0x10);
                            lwc1(f1, sp, 0x14);
                            lwc1(f0, sp, 0x18);
                            swc1(f2, v1, sflcur::kPos);
                            swc1(f1, v1, sflcur::kPos + 4);
                            swc1(f0, v1, sflcur::kPos + 8);
                        } else {
                            // 0x0025a1cc
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
        // 0x0025a328
        charge(ctx, 4);
        a2 = 0;
        a0 = 256;
        for (;;) {
            // 0x0025a418
            charge(ctx, 3);
            v0 = slti(a2, 6);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0025a338
            charge(ctx, 8);
            v0 = sll(a2, 5);
            v0 = addu(v0, a2);
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            a1 = addiu(v0, 64);
            lw(v0, v1, sflcur::kSel);
            if (a2 != v0) {
                // 0x0025a38c
                charge(ctx, 3);
                lw(v0, a1, 0);
                if (v0 != 0) {
                    // 0x0025a398
                    charge(ctx, 2);
                    v0 = addiu(v0, -8);
                    sw(v0, a1, 0);
                }
                // 0x0025a3a0
                charge(ctx, 3);
                lw(v0, a1, 0);
                if (i64(v0) < 0) {
                    // 0x0025a3ac
                    charge(ctx, 1);
                    sw(zero, a1, 0);
                }
            } else {
                // 0x0025a358
                charge(ctx, 4);
                lw(v0, a1, 0);
                at = slti(v0, 256);
                if (at != 0) {
                    // 0x0025a368
                    charge(ctx, 2);
                    v0 = addiu(v0, 25);
                    sw(v0, a1, 0);
                }
                // 0x0025a370
                charge(ctx, 4);
                lw(v0, a1, 0);
                at = slti(v0, 257);
                if (at == 0) {
                    // 0x0025a380
                    charge(ctx, 3);
                    sw(a0, a1, 0);
                }
            }
            // 0x0025a3b0
            charge(ctx, 3);
            lw(v0, v1, sflcur::kSel);
            if (a2 != v0) {
                // 0x0025a3f0
                charge(ctx, 3);
                lw(v0, a1, 4);
                if (v0 != 0) {
                    // 0x0025a3fc
                    charge(ctx, 2);
                    v0 = addiu(v0, -12);
                    sw(v0, a1, 4);
                }
                // 0x0025a404
                charge(ctx, 3);
                lw(v0, a1, 4);
                if (i64(v0) < 0) {
                    // 0x0025a410
                    charge(ctx, 1);
                    sw(zero, a1, 4);
                }
            } else {
                // 0x0025a3bc
                charge(ctx, 4);
                lw(v0, a1, 4);
                at = slti(v0, 256);
                if (at != 0) {
                    // 0x0025a3cc
                    charge(ctx, 2);
                    v0 = addiu(v0, 64);
                    sw(v0, a1, 4);
                }
                // 0x0025a3d4
                charge(ctx, 4);
                lw(v0, a1, 4);
                at = slti(v0, 257);
                if (at == 0) {
                    // 0x0025a3e4
                    charge(ctx, 3);
                    sw(a0, a1, 4);
                }
            }
            // 0x0025a414
            charge(ctx, 1);
            a2 = addiu(a2, 1);
        }
        // 0x0025a424
        charge(ctx, 2);
        jal(ctx, 0x25A424u, gen::fn_sub_25AAD0_0025aad0);
    }
    // 0x0025a42c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0025A440 sub_25A440 -- 908 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflCursorDraw] Draws the Shuffle Time card cursor (K_Assert line 71; the draw-1 task): the 2D render states, the
// frame quads (+3248 / +3504 with texture 4, +3760 with texture 2 of the second set), then per card mark the
// selection quad (the selected one, and the previous one +44 during a kind-1 move) and the glow quad while its
// brightness (+64) is nonzero.
void sub_25A440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025a440
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpSflCursor);  // the Shuffle Time card cursor (sfl_cursor.c) 0x7CE360
    if (v1 == 0) {
        // 0x0025a468
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5192);  // "sfl_cursor.c"
        a1 = 71;
        jal(ctx, 0x25A474u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025a47c
    charge(ctx, 6);
    lw(s2, gp, kGpSflCursor);  // the Shuffle Time card cursor (sfl_cursor.c) 0x7CE360
    lw(v1, s2, sflcur::kFlags);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x0025a494
        charge(ctx, 109);
        s1 = 0x960000;
        s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
        a0 = 9;
        a1 = 2;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x25A4A8u, v0.u());
        a0 = 20;
        a1 = 2;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x25A4BCu, v0.u());
        a0 = 8;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x25A4D0u, v0.u());
        a0 = 6;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x25A4E4u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x25A4F8u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x25A508u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 4;
        jal(ctx, 0x25A514u, gen::fn_sub_20E510_0020e510);
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x25A528u, v0.u());
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s2, 3248);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25A550u, v0.u());
        a0 = addiu(s2, 3248);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25A570u, v0.u());
        a0 = addiu(s2, 3504);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25A590u, v0.u());
        a0 = addiu(s2, 3504);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25A5B0u, v0.u());
        a0 = 2;
        jal(ctx, 0x25A5BCu, gen::fn_sub_20E590_0020e590);
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x25A5D0u, v0.u());
        a0 = addiu(s2, 3760);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25A5F0u, v0.u());
        a0 = addiu(s2, 3760);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25A610u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x1801;
        jal(ctx, 0x25A624u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 72;
        jal(ctx, 0x25A634u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s3 = 0;
        for (;;) {
            // 0x0025a79c
            charge(ctx, 3);
            v1 = slti(s3, 6);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0025a648
            charge(ctx, 10);
            v1 = sll(s3, 5);
            v1 = addu(v1, s3);
            v1 = sll(v1, 4);
            v1 = addu(s2, v1);
            s0 = addiu(v1, 64);
            a1 = 0;
            lw(v1, s2, sflcur::kFlags);
            v1 = v1 & 0x2;
            if (v1 != 0) {
                // 0x0025a670
                charge(ctx, 4);
                lw(a0, s2, sflcur::kMoveKind);
                v1 = 1;
                if (a0 != v1) {
                    goto L_0025a6a4;
                }
                // 0x0025a680
                charge(ctx, 3);
                lw(v1, s2, sflcur::kSel);
                if (s3 != v1) {
                    // 0x0025a68c
                    charge(ctx, 3);
                    lw(v1, s2, sflcur::kPrevSel);
                    if (s3 == v1) {
                        goto L_0025a698;
                    }
                    goto L_0025a6b4;
                }
            L_0025a698:
                charge(ctx, 3);
                a1 = 1;
                goto L_0025a6b4;
            }
        L_0025a6a4:
            charge(ctx, 3);
            lw(v1, s2, sflcur::kSel);
            if (s3 == v1) {
                // 0x0025a6b0
                charge(ctx, 1);
                a1 = 1;
            }
        L_0025a6b4:
            charge(ctx, 2);
            if (a1 != 0) {
                // 0x0025a6bc
                charge(ctx, 26);
                a0 = 2;
                jal(ctx, 0x25A6C0u, gen::fn_sub_20E510_0020e510);
                a0 = 1;
                a1 = v0;
                lw(v0, s1, 0);
                jalr(ctx, 0x25A6D4u, v0.u());
                s4 = 0x960000;
                s4 = addiu(s4, 156);  // &0x96009C
                a0 = addiu(s0, 16);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s4, 0);  // 0x96009C
                jalr(ctx, 0x25A6FCu, v0.u());
                a0 = addiu(s0, 16);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s4, 0);  // 0x96009C
                jalr(ctx, 0x25A71Cu, v0.u());
            }
            // 0x0025a724
            charge(ctx, 3);
            lw(v1, s0, 0);
            if (v1 != 0) {
                // 0x0025a730
                charge(ctx, 26);
                a0 = 1;
                jal(ctx, 0x25A734u, gen::fn_sub_20E510_0020e510);
                a0 = 1;
                a1 = v0;
                lw(v0, s1, 0);
                jalr(ctx, 0x25A748u, v0.u());
                s4 = 0x960000;
                s4 = addiu(s4, 156);  // &0x96009C
                a0 = addiu(s0, 272);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s4, 0);  // 0x96009C
                jalr(ctx, 0x25A770u, v0.u());
                a0 = addiu(s0, 272);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s4, 0);  // 0x96009C
                jalr(ctx, 0x25A790u, v0.u());
            }
            // 0x0025a798
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
    }
    // 0x0025a7a8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0025A7D0 sub_25A7D0 -- 668 bytes; frame 0x60: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [sflCursorOpen] Opens the Shuffle Time card cursor (K_Assert line 71): flags cleared, the frame quads' UVs from the
// texture sizes (117 x 32 and 63 x 20 cells), the cursor's start point (sub_258540(0, +28)), every mark's quads at
// full texture, places them (sub_25AAD0), selection 0, move kind 2, flags 1 | 2.
void sub_25A7D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x0025a7d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v0, gp, kGpSflCursor);  // the Shuffle Time card cursor (sfl_cursor.c) 0x7CE360
    if (v0 == 0) {
        // 0x0025a7fc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5192);  // "sfl_cursor.c"
        a1 = 71;
        jal(ctx, 0x25A808u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025a810
    charge(ctx, 77);
    lw(s0, gp, kGpSflCursor);  // the Shuffle Time card cursor (sfl_cursor.c) 0x7CE360
    sw(zero, s0, sflcur::kFlags);
    a0 = 4;
    jal(ctx, 0x25A81Cu, gen::fn_sub_20E510_0020e510);
    lwc1(f0, v0, 12);
    cvt_s_w(f2, f0);
    lwc1(f0, v0, 16);
    cvt_s_w(f1, f0);
    v0 = 0x3F800000;
    mtc1(v0, f0);
    div_s(f22, f0, f2);
    swc1(f22, sp, 0x50);
    mtc1(zero, f0);
    div_s(f0, f0, f1);
    swc1(f0, sp, 0x54);
    v0 = 0x42EA0000;
    mtc1(v0, f0);
    div_s(f20, f0, f2);
    swc1(f20, sp, 0x58);
    v0 = 0x42000000;
    mtc1(v0, f0);
    div_s(f21, f0, f1);
    swc1(f21, sp, 0x5C);
    a0 = addiu(s0, 3248);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x25A888u, gen::fn_sub_21EB80_0021eb80);
    swc1(f22, sp, 0x50);
    swc1(f21, sp, 0x54);
    swc1(f20, sp, 0x58);
    swc1(f21, sp, 0x5C);
    a0 = addiu(s0, 3504);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x25A8A8u, gen::fn_sub_21EB80_0021eb80);
    a0 = 2;
    jal(ctx, 0x25A8B4u, gen::fn_sub_20E590_0020e590);
    lwc1(f0, v0, 12);
    cvt_s_w(f2, f0);
    lwc1(f0, v0, 16);
    cvt_s_w(f1, f0);
    mtc1(zero, f0);
    div_s(f0, f0, f2);
    swc1(f0, sp, 0x50);
    v0 = 0x42A80000;
    mtc1(v0, f0);
    div_s(f0, f0, f1);
    swc1(f0, sp, 0x54);
    v0 = 0x427C0000;
    mtc1(v0, f0);
    div_s(f0, f0, f2);
    swc1(f0, sp, 0x58);
    v0 = 0x41A00000;
    mtc1(v0, f0);
    div_s(f0, f0, f1);
    swc1(f0, sp, 0x5C);
    a0 = addiu(s0, 3760);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x25A920u, gen::fn_sub_21EB80_0021eb80);
    a0 = 0;
    a1 = addiu(s0, 28);
    jal(ctx, 0x25A930u, gen::fn_sub_258540_00258540);
    s1 = 0;
    for (;;) {
        // 0x0025aa0c
        charge(ctx, 3);
        v0 = slti(s1, 6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0025a944
        charge(ctx, 50);
        v0 = sll(s1, 5);
        v0 = addu(v0, s1);
        v0 = sll(v0, 4);
        v0 = addu(s0, v0);
        s2 = addiu(v0, 64);
        sw(zero, v0, 64);
        sw(zero, v0, 68);
        a0 = 2;
        jal(ctx, 0x25A964u, gen::fn_sub_20E510_0020e510);
        lwc1(f0, v0, 12);
        cvt_s_w(f3, f0);
        lwc1(f0, v0, 16);
        cvt_s_w(f2, f0);
        mtc1(zero, f1);
        div_s(f0, f1, f3);
        swc1(f0, sp, 0x50);
        div_s(f0, f1, f2);
        swc1(f0, sp, 0x54);
        div_s(f0, f3, f3);
        swc1(f0, sp, 0x58);
        div_s(f0, f2, f2);
        swc1(f0, sp, 0x5C);
        a0 = addiu(s2, 16);
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x25A9ACu, gen::fn_sub_21EB80_0021eb80);
        a0 = 1;
        jal(ctx, 0x25A9B8u, gen::fn_sub_20E510_0020e510);
        lwc1(f0, v0, 12);
        cvt_s_w(f3, f0);
        lwc1(f0, v0, 16);
        cvt_s_w(f2, f0);
        mtc1(zero, f1);
        div_s(f0, f1, f3);
        swc1(f0, sp, 0x50);
        div_s(f0, f1, f2);
        swc1(f0, sp, 0x54);
        div_s(f0, f3, f3);
        swc1(f0, sp, 0x58);
        div_s(f0, f2, f2);
        swc1(f0, sp, 0x5C);
        a0 = addiu(s2, 272);
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x25AA00u, gen::fn_sub_21EB80_0021eb80);
        s1 = addiu(s1, 1);
    }
    // 0x0025aa18
    charge(ctx, 21);
    jal(ctx, 0x25AA18u, gen::fn_sub_25AAD0_0025aad0);
    sw(zero, s0, sflcur::kSel);
    sw(zero, s0, sflcur::kMoveFrame);
    v1 = 2;
    sw(v1, s0, sflcur::kMoveKind);
    lw(v1, s0, sflcur::kFlags);
    v1 = v1 | 0x2;
    sw(v1, s0, sflcur::kFlags);
    v1 = v1 | 0x1;
    sw(v1, s0, sflcur::kFlags);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00260A50 sub_260A50 -- 380 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflPselOpen] Opens the persona-select banner (sfl_psel2.c; K_Assert line 87): the plates 52 / 53 / 54 / 58 of the
// panel texture set (sub_20EC50) into the quads +1040 / +1296 / +1552 / +1808 with alpha 30 / 30 / 30 / 50
// (sub_21EA00 / sub_21EAC0), three more alphas 50, resets the frame counters (sub_260C20), places the quads
// (sfl_pselLayout) and sets flag 1.
void sub_260A50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00260a50
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpSflPsel);  // the persona-select work (sfl_psel2.c) 0x7CE378
    if (v0 == 0) {
        // 0x00260a6c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5096);  // "sfl_psel2.c"
        a1 = 87;
        jal(ctx, 0x260A78u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00260a80
    charge(ctx, 83);
    lw(s0, gp, kGpSflPsel);  // the persona-select work (sfl_psel2.c) 0x7CE378
    jal(ctx, 0x260A84u, gen::fn_sub_20EC50_0020ec50);
    s1 = v0;
    a0 = s1;
    a1 = 52;
    jal(ctx, 0x260A98u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 1040);
    a1 = v0;
    jal(ctx, 0x260AA8u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = 30;
    jal(ctx, 0x260AB4u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s0, 1040);
    mov_s(f12, f0);
    jal(ctx, 0x260AC4u, gen::fn_sub_21EAC0_0021eac0);
    a0 = s1;
    a1 = 53;
    jal(ctx, 0x260AD4u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 1296);
    a1 = v0;
    jal(ctx, 0x260AE4u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = 30;
    jal(ctx, 0x260AF0u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s0, 1296);
    mov_s(f12, f0);
    jal(ctx, 0x260B00u, gen::fn_sub_21EAC0_0021eac0);
    a0 = s1;
    a1 = 54;
    jal(ctx, 0x260B10u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 1552);
    a1 = v0;
    jal(ctx, 0x260B20u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = 30;
    jal(ctx, 0x260B2Cu, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s0, 1552);
    mov_s(f12, f0);
    jal(ctx, 0x260B3Cu, gen::fn_sub_21EAC0_0021eac0);
    a0 = s1;
    a1 = 58;
    jal(ctx, 0x260B4Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 1808);
    a1 = v0;
    jal(ctx, 0x260B5Cu, gen::fn_sub_21D3B0_0021d3b0);
    a0 = 50;
    jal(ctx, 0x260B68u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s0, 1808);
    mov_s(f12, f0);
    jal(ctx, 0x260B78u, gen::fn_sub_21EAC0_0021eac0);
    a0 = 50;
    jal(ctx, 0x260B84u, gen::fn_sub_21EA00_0021ea00);
    swc1(f0, s0, 2072);
    swc1(f0, s0, 2136);
    swc1(f0, s0, 2200);
    jal(ctx, 0x260B98u, gen::fn_sub_260C20_00260c20);
    jal(ctx, 0x260BA0u, gen::fn_sub_261480_00261480);
    lw(v1, s0, psel6::kFlags);
    v1 = v1 | 0x1;
    sw(v1, s0, psel6::kFlags);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00261480 sub_261480 -- 4700 bytes; frame 0x90: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [sflPselLayout] Lays out the persona-select banner for the current frame (K_Assert line 87): by the mode (+4: 0
// opening, 1 closing) each quad slides and fades over its own frame span (the plates 52..54 over 5 / 6 frames, the
// band over 8 / 10, ...) toward its place under the plate heights (texture sizes + 109), the band 544 px wide;
// colours and positions through sub_21D8E0 / sub_21D950 / sub_21D890, the banner's fixed corners (224, 352).
void sub_261480(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00261480
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v0, gp, kGpSflPsel);  // the persona-select work (sfl_psel2.c) 0x7CE378
    if (v0 == 0) {
        // 0x002614b0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5096);  // "sfl_psel2.c"
        a1 = 87;
        jal(ctx, 0x2614BCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002614c4
    charge(ctx, 14);
    lw(s0, gp, kGpSflPsel);  // the persona-select work (sfl_psel2.c) 0x7CE378
    jal(ctx, 0x2614C8u, gen::fn_sub_20EC50_0020ec50);
    s1 = v0;
    a0 = s1;
    a1 = 52;
    jal(ctx, 0x2614DCu, gen::fn_sub_21CCA0_0021cca0);
    lw(a1, v0, 12);
    lw(a0, v0, 16);
    lw(v1, s0, psel6::kMode);
    v0 = 1;
    if (v1 == v0) {
        // 0x002615a4
        charge(ctx, 4);
        lw(v0, s0, psel6::kFrame);
        at = slti(v0, 3);
        if (at == 0) {
            // 0x00261610
            charge(ctx, 4);
            v0 = 0x431C0000;
            sw(v0, sp, 0x60);
            sw(v0, sp, 0x64);
            mtc1(zero, f21);
        } else {
            // 0x002615b4
            charge(ctx, 23);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x40400000;
            mtc1(v0, f0);
            div_s(f2, f1, f0);
            v0 = 0x43160000;
            mtc1(v0, f0);
            mul_s(f1, f2, f0);
            v0 = 0x40C00000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x60);
            swc1(f0, sp, 0x64);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f21, f0, f2);
        }
    } else {
        // 0x002614fc
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0026150c
            charge(ctx, 6);
            v0 = 0x3F800000;
            mtc1(v0, f21);
            lw(v0, s0, psel6::kFrame);
            at = slti(v0, 5);
            if (at == 0) {
                // 0x00261590
                charge(ctx, 5);
                v0 = 0x40C00000;
                sw(v0, sp, 0x60);
                sw(v0, sp, 0x64);
            } else {
                // 0x00261524
                charge(ctx, 27);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x40A00000;
                mtc1(v0, f0);
                div_s(f5, f1, f0);
                v0 = 0x40C00000;
                mtc1(v0, f4);
                mtc1(a0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f4, f0);
                add_s(f3, f4, f0);
                sub_s(f2, f4, f0);
                sub_s(f0, f4, f3);
                mtc1(zero, f1);
                adda_s(f1, f3);
                madd_s(f0, f5, f0);
                swc1(f0, sp, 0x60);
                sub_s(f0, f4, f2);
                adda_s(f1, f2);
                madd_s(f0, f5, f0);
                swc1(f0, sp, 0x64);
            }
        } else {
            // 0x00261504
            charge(ctx, 2);
        }
    }
    // 0x00261620
    charge(ctx, 26);
    mtc1(a1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x68);
    mtc1(a0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x6C);
    a0 = addiu(s0, 1040);
    a1 = addiu(sp, 0x60);
    jal(ctx, 0x261648u, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 0x8C);
    sb(v0, sp, 0x8D);
    sb(v0, sp, 0x8E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f21);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x002616a0
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00261688
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x002616b8
    charge(ctx, 15);
    sb(v1, sp, 0x8F);
    a0 = addiu(s0, 1040);
    a1 = addiu(sp, 0x8C);
    jal(ctx, 0x2616C4u, gen::fn_sub_21D950_0021d950);
    a0 = s1;
    a1 = 53;
    jal(ctx, 0x2616D4u, gen::fn_sub_21CCA0_0021cca0);
    lw(s3, v0, 12);
    lw(s2, v0, 16);
    lw(v1, s0, psel6::kMode);
    v0 = 1;
    if (v1 == v0) {
        // 0x002617bc
        charge(ctx, 4);
        lw(v0, s0, psel6::kFrame);
        at = slti(v0, 3);
        if (at == 0) {
            // 0x00261838
            charge(ctx, 8);
            v0 = 0x432D0000;
            sw(v0, sp, 0x60);
            v0 = 259;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x64);
            mtc1(zero, f21);
        } else {
            // 0x002617cc
            charge(ctx, 27);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x40400000;
            mtc1(v0, f0);
            div_s(f2, f1, f0);
            v0 = 0x43160000;
            mtc1(v0, f0);
            mul_s(f1, f2, f0);
            v0 = 0x41B80000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x60);
            v0 = 0x42DA0000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x64);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f21, f0, f2);
        }
    } else {
        // 0x002616f4
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00261704
            charge(ctx, 6);
            v0 = 0x3F800000;
            mtc1(v0, f21);
            lw(v0, s0, psel6::kFrame);
            at = slti(v0, 6);
            if (at == 0) {
                // 0x002617a4
                charge(ctx, 6);
                v0 = 0x41B80000;
                sw(v0, sp, 0x60);
                v0 = 0x42DA0000;
                sw(v0, sp, 0x64);
            } else {
                // 0x0026171c
                charge(ctx, 34);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x40C00000;
                mtc1(v0, f0);
                div_s(f20, f1, f0);
                a0 = s1;
                a1 = 53;
                jal(ctx, 0x261744u, gen::fn_sub_21CCA0_0021cca0);
                lwc1(f0, v0, 16);
                v0 = 0x42DA0000;
                mtc1(v0, f4);
                cvt_s_w(f0, f0);
                add_s(f1, f4, f0);
                v0 = 0x41B80000;
                mtc1(v0, f0);
                add_s(f3, f0, f1);
                sub_s(f2, f4, f1);
                sub_s(f0, f0, f3);
                mtc1(zero, f1);
                adda_s(f1, f3);
                madd_s(f0, f20, f0);
                swc1(f0, sp, 0x60);
                sub_s(f0, f4, f2);
                adda_s(f1, f2);
                madd_s(f0, f20, f0);
                swc1(f0, sp, 0x64);
            }
        } else {
            // 0x002616fc
            charge(ctx, 2);
        }
    }
    // 0x00261858
    charge(ctx, 26);
    mtc1(s3, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x68);
    mtc1(s2, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x6C);
    a0 = addiu(s0, 1296);
    a1 = addiu(sp, 0x60);
    jal(ctx, 0x261880u, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 0x8C);
    sb(v0, sp, 0x8D);
    sb(v0, sp, 0x8E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f21);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x002618d8
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x002618c0
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x002618f0
    charge(ctx, 15);
    sb(v1, sp, 0x8F);
    a0 = addiu(s0, 1296);
    a1 = addiu(sp, 0x8C);
    jal(ctx, 0x2618FCu, gen::fn_sub_21D950_0021d950);
    a0 = s1;
    a1 = 54;
    jal(ctx, 0x26190Cu, gen::fn_sub_21CCA0_0021cca0);
    lw(s3, v0, 12);
    lw(s2, v0, 16);
    lw(v1, s0, psel6::kMode);
    v0 = 1;
    if (v1 == v0) {
        // 0x00261a04
        charge(ctx, 4);
        lw(v0, s0, psel6::kFrame);
        at = slti(v0, 3);
        if (at == 0) {
            // 0x00261a80
            charge(ctx, 5);
            v0 = 0x43850000;
            sw(v0, sp, 0x60);
            v0 = 0x432C0000;
            sw(v0, sp, 0x64);
            mtc1(zero, f21);
        } else {
            // 0x00261a14
            charge(ctx, 27);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x40400000;
            mtc1(v0, f0);
            div_s(f2, f1, f0);
            v0 = 0x43160000;
            mtc1(v0, f0);
            mul_s(f1, f2, f0);
            v0 = 0x42E80000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x60);
            v0 = 0x41B00000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x64);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f21, f0, f2);
        }
    } else {
        // 0x0026192c
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0026193c
            charge(ctx, 6);
            v0 = 0x3F800000;
            mtc1(v0, f21);
            lw(v0, s0, psel6::kFrame);
            at = slti(v0, 6);
            if (at == 0) {
                // 0x002619ec
                charge(ctx, 6);
                v0 = 0x42E80000;
                sw(v0, sp, 0x60);
                v0 = 0x41B00000;
                sw(v0, sp, 0x64);
            } else {
                // 0x00261954
                charge(ctx, 38);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x40C00000;
                mtc1(v0, f0);
                div_s(f20, f1, f0);
                a0 = s1;
                a1 = 53;
                jal(ctx, 0x26197Cu, gen::fn_sub_21CCA0_0021cca0);
                lwc1(f0, v0, 16);
                v0 = 0x42DA0000;
                mtc1(v0, f1);
                cvt_s_w(f0, f0);
                add_s(f1, f1, f0);
                v0 = 0x42E80000;
                mtc1(v0, f0);
                add_s(f4, f0, f1);
                v0 = 0x41B00000;
                mtc1(v0, f3);
                sub_s(f2, f3, f1);
                sub_s(f0, f0, f4);
                mtc1(zero, f1);
                adda_s(f1, f4);
                madd_s(f0, f20, f0);
                swc1(f0, sp, 0x60);
                sub_s(f0, f3, f2);
                adda_s(f1, f2);
                madd_s(f0, f20, f0);
                swc1(f0, sp, 0x64);
            }
        } else {
            // 0x00261934
            charge(ctx, 2);
        }
    }
    // 0x00261a94
    charge(ctx, 26);
    mtc1(s3, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x68);
    mtc1(s2, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x6C);
    a0 = addiu(s0, 1552);
    a1 = addiu(sp, 0x60);
    jal(ctx, 0x261ABCu, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 0x8C);
    sb(v0, sp, 0x8D);
    sb(v0, sp, 0x8E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f21);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00261b14
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00261afc
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00261b2c
    charge(ctx, 9);
    sb(v1, sp, 0x8F);
    a0 = addiu(s0, 1552);
    a1 = addiu(sp, 0x8C);
    jal(ctx, 0x261B38u, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, psel6::kMode);
    v0 = 1;
    if (v1 == v0) {
        // 0x00261cb0
        charge(ctx, 4);
        lw(v0, s0, psel6::kFrame);
        at = slti(v0, 10);
        if (at == 0) {
            // 0x00261d88
            charge(ctx, 35);
            v0 = 0x44880000;
            mtc1(v0, f0);
            div_s(f0, f0, f22);
            div_s(f4, f0, f22);
            v0 = 0x43A00000;
            mtc1(v0, f0);
            add_s(f3, f0, f4);
            swc1(f3, sp, 0x70);
            v0 = 0x44200000;
            mtc1(v0, f0);
            div_s(f0, f0, f22);
            neg_s(f0, f0);
            div_s(f0, f0, f22);
            add_s(f2, f4, f0);
            swc1(f2, sp, 0x74);
            v0 = 0x43E00000;
            mtc1(v0, f0);
            div_s(f0, f0, f22);
            neg_s(f0, f0);
            div_s(f0, f0, f22);
            add_s(f1, f4, f0);
            swc1(f1, sp, 0x78);
            v0 = 0x43600000;
            mtc1(v0, f0);
            add_s(f0, f0, f4);
            swc1(f0, sp, 0x7C);
            swc1(f1, sp, 0x60);
            swc1(f0, sp, 0x64);
            swc1(f3, sp, 0x68);
            swc1(f2, sp, 0x6C);
        } else {
            // 0x00261cc0
            charge(ctx, 50);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41200000;
            mtc1(v0, f0);
            div_s(f7, f1, f0);
            v0 = 0x40000000;
            mtc1(v0, f0);
            sqrt_s(f8, f0);
            v0 = 0x44580000;
            mtc1(v0, f6);
            sw(v0, sp, 0x70);
            v0 = 0x43600000;
            mtc1(v0, f5);
            sw(v0, sp, 0x74);
            v0 = 0x43A00000;
            mtc1(v0, f4);
            sw(v0, sp, 0x78);
            v0 = 0x44400000;
            mtc1(v0, f3);
            sw(v0, sp, 0x7C);
            lwc1(f2, gp, -32000);  // 0x7CAFF0
            v0 = 0x43800000;
            mtc1(v0, f1);
            mtc1(zero, f0);
            adda_s(f0, f1);
            msub_s(f0, f2, f8);
            div_s(f1, f0, f8);
            v0 = 0x44080000;
            mtc1(v0, f0);
            sub_s(f1, f0, f1);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f0, f0, f7);
            mul_s(f1, f0, f1);
            sub_s(f0, f4, f1);
            swc1(f0, sp, 0x60);
            sub_s(f0, f3, f1);
            swc1(f0, sp, 0x64);
            sub_s(f0, f6, f1);
            swc1(f0, sp, 0x68);
            sub_s(f0, f5, f1);
            swc1(f0, sp, 0x6C);
        }
    } else {
        // 0x00261b50
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00261b60
            charge(ctx, 4);
            lw(v1, s0, psel6::kFrame);
            at = slti(v1, 8);
            if (at == 0) {
                // 0x00261c28
                charge(ctx, 34);
                v0 = 0x43A00000;
                mtc1(v0, f5);
                sw(v0, sp, 0x60);
                v0 = 0x44200000;
                mtc1(v0, f0);
                div_s(f0, f0, f22);
                neg_s(f0, f0);
                div_s(f4, f0, f22);
                swc1(f4, sp, 0x64);
                v0 = 0x43E00000;
                mtc1(v0, f0);
                div_s(f0, f0, f22);
                neg_s(f0, f0);
                div_s(f3, f0, f22);
                swc1(f3, sp, 0x68);
                v0 = 0x43600000;
                mtc1(v0, f2);
                sw(v0, sp, 0x6C);
                v0 = 0x44880000;
                mtc1(v0, f0);
                div_s(f1, f0, f22);
                add_s(f0, f3, f1);
                swc1(f0, sp, 0x70);
                add_s(f0, f2, f1);
                swc1(f0, sp, 0x74);
                add_s(f0, f5, f1);
                swc1(f0, sp, 0x78);
                add_s(f0, f4, f1);
                swc1(f0, sp, 0x7C);
            } else {
                // 0x00261b70
                charge(ctx, 46);
                v0 = 0x40000000;
                mtc1(v0, f0);
                sqrt_s(f6, f0);
                v0 = 0x43A00000;
                mtc1(v0, f5);
                sw(v0, sp, 0x60);
                v0 = 0x44200000;
                mtc1(v0, f0);
                div_s(f0, f0, f6);
                neg_s(f0, f0);
                div_s(f4, f0, f6);
                swc1(f4, sp, 0x64);
                v0 = 0x43E00000;
                mtc1(v0, f0);
                div_s(f0, f0, f6);
                neg_s(f0, f0);
                div_s(f3, f0, f6);
                swc1(f3, sp, 0x68);
                v0 = 0x43600000;
                mtc1(v0, f2);
                sw(v0, sp, 0x6C);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41000000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x44880000;
                mtc1(v0, f0);
                mul_s(f0, f0, f1);
                div_s(f1, f0, f6);
                add_s(f0, f3, f1);
                swc1(f0, sp, 0x70);
                add_s(f0, f2, f1);
                swc1(f0, sp, 0x74);
                add_s(f0, f5, f1);
                swc1(f0, sp, 0x78);
                add_s(f0, f4, f1);
                swc1(f0, sp, 0x7C);
            }
        } else {
            // 0x00261b58
            charge(ctx, 2);
        }
    }
    // 0x00261e14
    charge(ctx, 23);
    a0 = addiu(s0, 16);
    a1 = addiu(sp, 0x60);
    jal(ctx, 0x261E1Cu, gen::fn_sub_21D890_0021d890);
    a0 = 50;
    jal(ctx, 0x261E28u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s0, 16);
    mov_s(f12, f0);
    jal(ctx, 0x261E38u, gen::fn_sub_21EAC0_0021eac0);
    sb(zero, sp, 0x8C);
    sb(zero, sp, 0x8D);
    sb(zero, sp, 0x8E);
    sb(zero, sp, 0x8F);
    a0 = addiu(s0, 16);
    a1 = addiu(sp, 0x8C);
    jal(ctx, 0x261E58u, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, psel6::kMode);
    v0 = 1;
    if (v1 == v0) {
        // 0x00261f24
        charge(ctx, 9);
        v0 = 0x40000000;
        mtc1(v0, f0);
        sqrt_s(f7, f0);
        lw(v0, s0, psel6::kFrame);
        at = slti(v0, 10);
        if (at == 0) {
            // 0x00262054
            charge(ctx, 9);
            mtc1(zero, f21);
            sw(zero, sp, 0x60);
            sw(zero, sp, 0x64);
            sw(zero, sp, 0x68);
            sw(zero, sp, 0x6C);
            sw(zero, sp, 0x70);
            sw(zero, sp, 0x74);
            sw(zero, sp, 0x78);
            sw(zero, sp, 0x7C);
        } else {
            // 0x00261f48
            charge(ctx, 67);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41200000;
            mtc1(v0, f0);
            div_s(f2, f1, f0);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f21, f0, f2);
            v0 = 0x43800000;
            mtc1(v0, f0);
            div_s(f1, f0, f7);
            lwc1(f0, gp, -32000);  // 0x7CAFF0
            sub_s(f0, f1, f0);
            div_s(f1, f0, f7);
            v0 = 0x44080000;
            mtc1(v0, f0);
            sub_s(f0, f0, f1);
            mul_s(f2, f2, f0);
            v0 = 0x42200000;
            mtc1(v0, f6);
            div_s(f1, f6, f7);
            v0 = 0x43A00000;
            mtc1(v0, f0);
            sub_s(f0, f0, f1);
            add_s(f5, f0, f2);
            swc1(f5, sp, 0x60);
            v0 = lui(0xC3A0);
            mtc1(v0, f0);
            sub_s(f0, f0, f1);
            add_s(f4, f0, f2);
            swc1(f4, sp, 0x64);
            v0 = lui(0xC360);
            mtc1(v0, f0);
            sub_s(f0, f0, f1);
            add_s(f3, f0, f2);
            swc1(f3, sp, 0x68);
            v0 = 0x43600000;
            mtc1(v0, f0);
            sub_s(f0, f0, f1);
            add_s(f2, f0, f2);
            swc1(f2, sp, 0x6C);
            v0 = 0x43580000;
            mtc1(v0, f0);
            div_s(f0, f0, f7);
            add_s(f0, f6, f0);
            div_s(f1, f0, f7);
            add_s(f0, f3, f1);
            swc1(f0, sp, 0x70);
            add_s(f0, f2, f1);
            swc1(f0, sp, 0x74);
            add_s(f0, f5, f1);
            swc1(f0, sp, 0x78);
            add_s(f0, f4, f1);
            swc1(f0, sp, 0x7C);
        }
    } else {
        // 0x00261e70
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00261e80
            charge(ctx, 41);
            v0 = 0x40000000;
            mtc1(v0, f0);
            sqrt_s(f1, f0);
            v0 = 0x43A00000;
            mtc1(v0, f5);
            sw(v0, sp, 0x60);
            v0 = 0x44200000;
            mtc1(v0, f0);
            div_s(f0, f0, f1);
            neg_s(f0, f0);
            div_s(f4, f0, f1);
            swc1(f4, sp, 0x64);
            v0 = 0x43E00000;
            mtc1(v0, f0);
            div_s(f0, f0, f1);
            neg_s(f0, f0);
            div_s(f3, f0, f1);
            swc1(f3, sp, 0x68);
            v0 = 0x43600000;
            mtc1(v0, f2);
            sw(v0, sp, 0x6C);
            v0 = 0x43580000;
            mtc1(v0, f0);
            div_s(f0, f0, f1);
            div_s(f1, f0, f1);
            add_s(f0, f3, f1);
            swc1(f0, sp, 0x70);
            add_s(f0, f2, f1);
            swc1(f0, sp, 0x74);
            add_s(f0, f5, f1);
            swc1(f0, sp, 0x78);
            add_s(f0, f4, f1);
            swc1(f0, sp, 0x7C);
            v0 = 0x3F800000;
            mtc1(v0, f21);
        } else {
            // 0x00261e78
            charge(ctx, 2);
        }
    }
    // 0x00262078
    charge(ctx, 27);
    a0 = addiu(s0, 272);
    a1 = addiu(sp, 0x60);
    jal(ctx, 0x262080u, gen::fn_sub_21D890_0021d890);
    a0 = 35;
    jal(ctx, 0x26208Cu, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s0, 272);
    mov_s(f12, f0);
    jal(ctx, 0x26209Cu, gen::fn_sub_21EAC0_0021eac0);
    v0 = 4;
    sb(v0, sp, 0x8C);
    v0 = 41;
    sb(v0, sp, 0x8D);
    v0 = 70;
    sb(v0, sp, 0x8E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f21);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x002620fc
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x002620e4
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00262114
    charge(ctx, 9);
    sb(v1, sp, 0x8F);
    a0 = addiu(s0, 272);
    a1 = addiu(sp, 0x8C);
    jal(ctx, 0x262120u, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, psel6::kMode);
    v0 = 1;
    if (v1 == v0) {
        // 0x002621c4
        charge(ctx, 59);
        lwc1(f0, s0, psel6::kFrame);
        cvt_s_w(f1, f0);
        v0 = 0x41200000;
        mtc1(v0, f0);
        div_s(f2, f1, f0);
        v0 = 0x40000000;
        mtc1(v0, f0);
        sqrt_s(f8, f0);
        v0 = 0x43800000;
        mtc1(v0, f0);
        div_s(f7, f0, f8);
        lwc1(f0, gp, -32000);  // 0x7CAFF0
        sub_s(f0, f7, f0);
        div_s(f1, f0, f8);
        v0 = 0x44080000;
        mtc1(v0, f0);
        sub_s(f0, f0, f1);
        mul_s(f6, f2, f0);
        v0 = 0x43A00000;
        mtc1(v0, f5);
        add_s(f0, f5, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x60);
        v0 = lui(0xC3A0);
        mtc1(v0, f4);
        add_s(f0, f4, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x64);
        v0 = lui(0xC360);
        mtc1(v0, f3);
        add_s(f0, f3, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x68);
        v0 = 0x43600000;
        mtc1(v0, f2);
        add_s(f0, f2, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x6C);
        div_s(f1, f7, f8);
        add_s(f0, f3, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x70);
        add_s(f0, f2, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x74);
        add_s(f0, f5, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x78);
        add_s(f0, f4, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x7C);
    } else {
        // 0x00262138
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00262148
            charge(ctx, 31);
            v0 = 0x40000000;
            mtc1(v0, f0);
            sqrt_s(f1, f0);
            v0 = 0x43A00000;
            mtc1(v0, f5);
            sw(v0, sp, 0x60);
            v0 = lui(0xC3A0);
            mtc1(v0, f4);
            sw(v0, sp, 0x64);
            v0 = lui(0xC360);
            mtc1(v0, f3);
            sw(v0, sp, 0x68);
            v0 = 0x43600000;
            mtc1(v0, f2);
            sw(v0, sp, 0x6C);
            v0 = 0x43800000;
            mtc1(v0, f0);
            div_s(f0, f0, f1);
            div_s(f1, f0, f1);
            add_s(f0, f3, f1);
            swc1(f0, sp, 0x70);
            add_s(f0, f2, f1);
            swc1(f0, sp, 0x74);
            add_s(f0, f5, f1);
            swc1(f0, sp, 0x78);
            add_s(f0, f4, f1);
            swc1(f0, sp, 0x7C);
        } else {
            // 0x00262140
            charge(ctx, 2);
        }
    }
    // 0x002622b0
    charge(ctx, 67);
    a0 = addiu(s0, 528);
    a1 = addiu(sp, 0x60);
    jal(ctx, 0x2622B8u, gen::fn_sub_21D890_0021d890);
    a0 = 35;
    jal(ctx, 0x2622C4u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s0, 528);
    mov_s(f12, f0);
    jal(ctx, 0x2622D4u, gen::fn_sub_21EAC0_0021eac0);
    v0 = 79;
    sb(v0, sp, 0x8C);
    v0 = 164;
    sb(v0, sp, 0x8D);
    v0 = 255;
    sb(v0, sp, 0x8E);
    sb(v0, sp, 0x8F);
    a0 = addiu(s0, 528);
    a1 = addiu(sp, 0x8C);
    jal(ctx, 0x262300u, gen::fn_sub_21D950_0021d950);
    sw(zero, sp, 0x60);
    sw(zero, sp, 0x64);
    v0 = 0x44200000;
    sw(v0, sp, 0x68);
    v0 = 0x43E00000;
    sw(v0, sp, 0x6C);
    a0 = addiu(s0, 1808);
    a1 = addiu(sp, 0x60);
    jal(ctx, 0x262328u, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 0x8C);
    sb(v0, sp, 0x8D);
    sb(v0, sp, 0x8E);
    sb(v0, sp, 0x8F);
    a0 = addiu(s0, 1808);
    a1 = addiu(sp, 0x8C);
    jal(ctx, 0x26234Cu, gen::fn_sub_21D950_0021d950);
    v1 = 517;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, s0, 2064);
    a1 = 0x43E00000;
    sw(a1, s0, 2068);
    a0 = 0x44200000;
    sw(a0, s0, 2128);
    v1 = 325;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, s0, 2132);
    sw(a0, s0, 2192);
    sw(a1, s0, 2196);
    v1 = 79;
    sb(v1, sp, 0x8C);
    v1 = 164;
    sb(v1, sp, 0x8D);
    v1 = 255;
    sb(v1, sp, 0x8E);
    sb(v1, sp, 0x8F);
    lbu(v1, sp, 0x8C);
    if (i64(v1) < 0) {
        // 0x002623d0
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002623bc
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002623ec
    charge(ctx, 4);
    swc1(f0, s0, 2096);
    lbu(v1, sp, 0x8D);
    if (i64(v1) < 0) {
        // 0x00262410
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002623fc
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0026242c
    charge(ctx, 4);
    swc1(f0, s0, 2100);
    lbu(v1, sp, 0x8E);
    if (i64(v1) < 0) {
        // 0x00262450
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0026243c
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0026246c
    charge(ctx, 4);
    swc1(f0, s0, 2104);
    lbu(v1, sp, 0x8F);
    if (i64(v1) < 0) {
        // 0x00262490
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0026247c
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002624ac
    charge(ctx, 4);
    swc1(f0, s0, 2108);
    lbu(v1, sp, 0x8C);
    if (i64(v1) < 0) {
        // 0x002624d0
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002624bc
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002624ec
    charge(ctx, 4);
    swc1(f0, s0, 2160);
    lbu(v1, sp, 0x8D);
    if (i64(v1) < 0) {
        // 0x00262510
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002624fc
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0026252c
    charge(ctx, 4);
    swc1(f0, s0, 2164);
    lbu(v1, sp, 0x8E);
    if (i64(v1) < 0) {
        // 0x00262550
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0026253c
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0026256c
    charge(ctx, 4);
    swc1(f0, s0, 2168);
    lbu(v1, sp, 0x8F);
    if (i64(v1) < 0) {
        // 0x00262590
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0026257c
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002625ac
    charge(ctx, 4);
    swc1(f0, s0, 2172);
    lbu(v1, sp, 0x8C);
    if (i64(v1) < 0) {
        // 0x002625d0
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002625bc
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002625ec
    charge(ctx, 4);
    swc1(f0, s0, 2224);
    lbu(v1, sp, 0x8D);
    if (i64(v1) < 0) {
        // 0x00262610
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002625fc
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0026262c
    charge(ctx, 4);
    swc1(f0, s0, 2228);
    lbu(v1, sp, 0x8E);
    if (i64(v1) < 0) {
        // 0x00262650
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0026263c
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0026266c
    charge(ctx, 4);
    swc1(f0, s0, 2232);
    lbu(v1, sp, 0x8F);
    if (i64(v1) < 0) {
        // 0x00262690
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0026267c
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002626ac (the shared epilogue, written out on this path)
    charge(ctx, 12);
    swc1(f0, s0, 2236);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x0027BC00 sub_27BC00 -- 272 bytes; frame 0x80: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflPersonaOpen] Opens the Shuffle Time persona status for persona a0 (sfl_persona.c; K_Assert line 41): its record
// (sub_1749A0, or a fresh 52-byte one built by sub_176680 on the stack when it has none), a status task set
// (fclMisc_CreatePsStatusTasks(0, 0, 5, 5)) into +4 showing it, sub_3C9CD0(-1), sub_3C9D00(8), page 1; +8 = the
// persona, flags 1 | 2.
// Arguments: a0 persona id.
void sub_27BC00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027bc00
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, gp, kGpSflPersona);  // the shuffle persona panel (sfl_persona.c) 0x7CE3E8
    if (v0 == 0) {
        // 0x0027bc24
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4136);  // "sfl_persona.c"
        a1 = 41;
        jal(ctx, 0x27BC30u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027bc38
    charge(ctx, 8);
    lw(s0, gp, kGpSflPersona);  // the shuffle persona panel (sfl_persona.c) 0x7CE3E8
    sh(s2, s0, sflpersona::kPersona);
    a0 = s2;
    jal(ctx, 0x27BC44u, gen::fn_sub_1749A0_001749a0);
    s1 = v0;
    if (s1 == 0) {
        // 0x0027bc58
        charge(ctx, 10);
        a0 = addiu(sp, 0x40);
        a1 = 0;
        a2 = 52;
        jal(ctx, 0x27BC64u, gen::fn_memset_00521408);
        a0 = addiu(sp, 0x40);
        a1 = s2;
        jal(ctx, 0x27BC74u, gen::fn_sub_176680_00176680);
        s1 = addiu(sp, 0x40);
    }
    // 0x0027bc80
    charge(ctx, 36);
    a0 = 0;
    a1 = 0;
    a2 = 5;
    a3 = a2;
    jal(ctx, 0x27BC90u, gen::fn_fclMisc_CreatePsStatusTasks_003c9850);
    sw(v0, s0, sflpersona::kStatus);
    a0 = v0;
    a1 = s1;
    a2 = 0;
    jal(ctx, 0x27BCA8u, gen::fn_sub_3C9B00_003c9b00);
    lw(a0, s0, sflpersona::kStatus);
    a1 = si(-1);
    jal(ctx, 0x27BCB8u, gen::fn_sub_3C9CD0_003c9cd0);
    lw(a0, s0, sflpersona::kStatus);
    a1 = 8;
    jal(ctx, 0x27BCC8u, gen::fn_sub_3C9D00_003c9d00);
    lw(a0, s0, sflpersona::kStatus);
    a1 = 1;
    jal(ctx, 0x27BCD8u, gen::fn_sub_3C9E00_003c9e00);
    lw(v1, s0, sflpersona::kFlags);
    v1 = v1 | 0x2;
    sw(v1, s0, sflpersona::kFlags);
    v1 = v1 | 0x1;
    sw(v1, s0, sflpersona::kFlags);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x0027BD10 sub_27BD10 -- 212 bytes; frame 0x70: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflPersonaSet] Switches the Shuffle Time persona status to persona a0 (K_Assert line 107: a different one), with a
// stack record when it has none; flag 2.
// Arguments: a0 persona id.
void sub_27BD10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027bd10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpSflPersona);  // the shuffle persona panel (sfl_persona.c) 0x7CE3E8
    if (v0 == 0) {
        // 0x0027bd30
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4136);  // "sfl_persona.c"
        a1 = 41;
        jal(ctx, 0x27BD3Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027bd44
    charge(ctx, 5);
    lw(s0, gp, kGpSflPersona);  // the shuffle persona panel (sfl_persona.c) 0x7CE3E8
    lhu(v1, s0, sflpersona::kPersona);
    v0 = s1 & 0xFFFF;
    if (v1 == v0) {
        // 0x0027bd58
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4136);  // "sfl_persona.c"
        a1 = 107;
        jal(ctx, 0x27BD64u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027bd6c
    charge(ctx, 6);
    sh(s1, s0, sflpersona::kPersona);
    a0 = s1;
    jal(ctx, 0x27BD74u, gen::fn_sub_1749A0_001749a0);
    if (v0 == 0) {
        // 0x0027bd84
        charge(ctx, 10);
        a0 = addiu(sp, 0x30);
        a1 = 0;
        a2 = 52;
        jal(ctx, 0x27BD90u, gen::fn_memset_00521408);
        a0 = addiu(sp, 0x30);
        a1 = s1;
        jal(ctx, 0x27BDA0u, gen::fn_sub_176680_00176680);
        v0 = addiu(sp, 0x30);
    }
    // 0x0027bdac
    charge(ctx, 14);
    lw(a0, s0, sflpersona::kStatus);
    a1 = v0;
    a2 = 0;
    jal(ctx, 0x27BDB8u, gen::fn_sub_3C9B00_003c9b00);
    lw(v1, s0, sflpersona::kFlags);
    v1 = v1 | 0x2;
    sw(v1, s0, sflpersona::kFlags);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0027BDF0 sub_27BDF0 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflPersonaClose] Closes the Shuffle Time persona status: destroys its task set and clears flag 1 (K_Assert line
// 41).
void sub_27BDF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027bdf0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpSflPersona);  // the shuffle persona panel (sfl_persona.c) 0x7CE3E8
    if (v0 == 0) {
        // 0x0027be08
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4136);  // "sfl_persona.c"
        a1 = 41;
        jal(ctx, 0x27BE14u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027be1c
    charge(ctx, 13);
    lw(s0, gp, kGpSflPersona);  // the shuffle persona panel (sfl_persona.c) 0x7CE3E8
    lw(a0, s0, sflpersona::kStatus);
    jal(ctx, 0x27BE24u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    lw(a0, s0, sflpersona::kFlags);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, s0, sflpersona::kFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027BF60 sub_27BF60 -- 68 bytes; frame 0x10: ra sp+0x0
// [sflPersonaIsShown] Flag 2 of the Shuffle Time persona status (a persona is shown; K_Assert line 41).
void sub_27BF60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027bf60
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpSflPersona);  // the shuffle persona panel (sfl_persona.c) 0x7CE3E8
    if (v0 == 0) {
        // 0x0027bf74
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4136);  // "sfl_persona.c"
        a1 = 41;
        jal(ctx, 0x27BF80u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027bf88 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpSflPersona);  // the shuffle persona panel (sfl_persona.c) 0x7CE3E8
    lw(v0, v0, sflpersona::kFlags);
    v0 = v0 & 0x2;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027BFB0 sub_27BFB0 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflPersonaHide] Starts hiding the Shuffle Time persona status: sub_3C9D00(16), frame +12 = 0, flag 8 (K_Assert
// line 41).
void sub_27BFB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027bfb0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpSflPersona);  // the shuffle persona panel (sfl_persona.c) 0x7CE3E8
    if (v0 == 0) {
        // 0x0027bfc8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4136);  // "sfl_persona.c"
        a1 = 41;
        jal(ctx, 0x27BFD4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027bfdc
    charge(ctx, 14);
    lw(s0, gp, kGpSflPersona);  // the shuffle persona panel (sfl_persona.c) 0x7CE3E8
    lw(a0, s0, sflpersona::kStatus);
    a1 = 16;
    jal(ctx, 0x27BFE8u, gen::fn_sub_3C9D00_003c9d00);
    sw(zero, s0, sflpersona::kHideFrame);
    lw(v1, s0, sflpersona::kFlags);
    v1 = v1 | 0x8;
    sw(v1, s0, sflpersona::kFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
