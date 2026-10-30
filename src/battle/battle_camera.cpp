// The battle camera band 0x2A0050-0x2B7058 (game/include/p3fes/game/battle_camera.h), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/27_unmapped_bands.md "battle camera"). Phase 5 slice `battle_camera`: these replace the recompiled
// bodies listed in game/replaced.txt; tests/game/test_battle_camera.cpp runs each against its __recomp body.
//
// This file: the screen / unit colour packets and their per-frame callbacks (0x2A0050-0x2A1DB0), the battle camera
// object's key ring and interpolation (0x2A1E00-0x2A3160), the small battle helpers (0x2A32F0-0x2A3D70), the camera
// set / switch layer (0x2A38F0, 0x2A3B00, 0x2A3BA0, 0x2A3E80, 0x2A42A0-0x2A4C50) and the leaf helpers at the band's end
// (0x2B6490-0x2B7000). battle_camera_states.cpp holds the camera work states of the table 0x6939F0.
//
// The packet idiom (battle_actions.cpp): a creator calls sub_27EC10(kind, size) -- a btl packet with `size` bytes of
// data at *(packet + 120) -- and installs its per-frame callback at packet + 108; the queue driver calls the callback
// with the data in $a0 until it returns non-zero.
#include "battle_camera_cpu.h"

namespace p3fes::recomp_gen {
// Callees (still recompiled, or replaced by other slices: through their generated entry points).
void fn_sub_27EC10_0027ec10(p3fes::EEContext&);  // a btl packet (kind, data size) (battle_task)
void fn_sub_19F8F0_0019f8f0(p3fes::EEContext&);
void fn_sub_19FD40_0019fd40(p3fes::EEContext&);
void fn_sub_19FD70_0019fd70(p3fes::EEContext&);
void fn_sub_27F730_0027f730(p3fes::EEContext&);  // btlUnit: set its RGBA colour (unit, rgba word)
void fn_sub_2D6290_002d6290(p3fes::EEContext&);  // (action)
void fn_sub_4BE310_004be310(p3fes::EEContext&);  // quaternion slerp setup (q0, q1, out)
void fn_sub_48D370_0048d370(p3fes::EEContext&);  // RwFrame: translate (frame, vector, ...)
void fn_sub_48D480_0048d480(p3fes::EEContext&);
void fn_datCalcChkBadStatus_00300580(p3fes::EEContext&);
void fn_sub_2D5F50_002d5f50(p3fes::EEContext&);
void fn_sub_2FDFE0_002fdfe0(p3fes::EEContext&);
void fn_sub_308A50_00308a50(p3fes::EEContext&);
void fn_sub_4BE1E0_004be1e0(p3fes::EEContext&);
void fn_sub_282C30_00282c30(p3fes::EEContext&);
void fn_sub_2835E0_002835e0(p3fes::EEContext&);
void fn_sub_283BA0_00283ba0(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);
void fn_sub_27F770_0027f770(p3fes::EEContext&);
void fn_sub_27F790_0027f790(p3fes::EEContext&);
void fn_sub_27FFB0_0027ffb0(p3fes::EEContext&);  // btlUnit position (unit, out)
void fn_sub_2D1FD0_002d1fd0(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);  // the main camera (draw_layer)
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);  // vector normalise (out, in)
void fn_sub_358A30_00358a30(p3fes::EEContext&);
void fn_sub_359380_00359380(p3fes::EEContext&);
void fn_sub_48DA30_0048da30(p3fes::EEContext&);
void fn_sub_2F8EB0_002f8eb0(p3fes::EEContext&);
void fn_sub_351BB0_00351bb0(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);
void fn_sub_2F8840_002f8840(p3fes::EEContext&);
void fn_sub_4BDCB0_004bdcb0(p3fes::EEContext&);
void fn_sub_2D21E0_002d21e0(p3fes::EEContext&);
void fn_sub_2880E0_002880e0(p3fes::EEContext&);
void fn_datCalcGetHeldWeaponType_00308c60(p3fes::EEContext&);
void fn_sub_2D5BF0_002d5bf0(p3fes::EEContext&);
void fn_sub_3093A0_003093a0(p3fes::EEContext&);
void fn_btlTargetGetSideMask_002d1600(p3fes::EEContext&);
void fn_sub_2D62D0_002d62d0(p3fes::EEContext&);
void fn_datCalcIsHpSkill_002d6370(p3fes::EEContext&);
void fn_sub_2D63B0_002d63b0(p3fes::EEContext&);
// this slice (through the generated entry points, which are the shims below)
#define P3FES_BCAM_DECL(name, addr) void fn_##name##_##addr(p3fes::EEContext&);
P3FES_BCAM_BODIES(P3FES_BCAM_DECL)
#undef P3FES_BCAM_DECL
}  // namespace p3fes::recomp_gen

namespace p3fes::game::bcam {

using namespace btl_cam;

// =====================================================================================================================
// The screen / unit colour packets (kinds 1538..1543) and their callbacks
// =====================================================================================================================

// 0x2A0050 sub_2A0050(a0 = colour A, a1 = colour B, a2 = colour C, a3 = a word, t0 = a halfword): a unit colour / light
// fade packet (kind 1538, 108 data bytes, callback sub_29FAA0). The three RGBA words become three float colours (each
// byte * 1/255, the $gp constant gp-32232) at data +0 / +32 / +64; data +96 = a3, +104 = t0 (u16).
void Cpu::sub_2A0050() {
    enter(24);
    sp = addiu(sp, -112);
    sd(ra, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    s0 = t0;
    a0 = li(kPktUnitColour);
    a1 = li(108);
    jal(0x2a0088, rg::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2a);
    v1 = addiu(v1, -1376);  // sub_29FAA0
    sw(v1, v0, kPktCallback);
    lw(v1, v0, kPktData);
    colour_to_floats(s4, 108, 0, 7);
    colour_to_floats(s3, 108, 32, 7);
    colour_to_floats(s2, 108, 64, 14);
    sw(s1, v1, 96);
    sh(s0, v1, 104);
    ld(ra, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 112);
}

// 0x2A1080 sub_2A1080(a0, a1): a scene packet (kind 1539, 92 data bytes, callback sub_2A0440): data +80 = a0, +88 = a1
// (u16).
void Cpu::sub_2A1080() {
    enter(22);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    s0 = a1;
    a0 = li(kPktScene);
    a1 = li(92);
    jal(0x2a10a0, rg::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2a);
    v1 = addiu(v1, 1088);  // sub_2A0440
    sw(v1, v0, kPktCallback);
    lw(v1, v0, kPktData);
    sw(s1, v1, 80);
    sh(s0, v1, 88);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// 0x2A10E0 sub_2A10E0(data): the per-frame callback of the screen colour fade (sub_2A1280's packet). data +0..+12 the
// target colour, +16..+28 the start colour (taken from gBtl+564 on the first frame), +32 the frames, +36 the frame
// counter. While frame < frames: gBtl+564..576 = lerp(start, target, frame / frames) (as u32 -> float), frame++,
// returns 0; then gBtl+564 = the target, returns 1.
void Cpu::sub_2A10E0() {
    enter(4);
    sp = addiu(sp, -16);
    lw(v0, a0, 36);
    if (v0 == 0) {
        charge(9);
        gbtl(v0);
        copy_vec4(v0, kScreenColour, a0, 16);
    }
    charge(5);
    lw(a1, a0, 32);
    lw(v0, a0, 36);
    at = sltu(v0, a1);
    if (at != 0) {
        charge(2);
        u2f(F1, F0, v0, v1, v0);
        charge(2);
        u2f(F0, F0, a1, v1, v0);
        charge(38);
        // F3 = t, F2 = 1 - t; sp+0.. = data+0.. * t + data+16.. * (1 - t)
        div_s(F3, F1, F0);
        lif(v0, 0x3f80, F0);
        sub_s(F2, F0, F3);
        for (int k = 0; k < 4; ++k) {
            lwc1(F1, a0, 16 + 4 * k);
            lwc1(F0, a0, 4 * k);
            mula_s(F0, F3);
            madd_s(F0, F1, F2);
            swc1(F0, sp, 4 * k);
        }
        gbtl(v0);
        copy_vec4(sp, 0, v0, kScreenColour);
        charge(4);
        lw(v0, a0, 36);
        v0 = addiu(v0, 1);
        sw(v0, a0, 36);
        v0 = 0;
    } else {
        charge(12);
        gbtl(v0);
        copy_vec4(a0, 0, v0, kScreenColour);
        v0 = li(1);
    }
    charge(3);
    sp = addiu(sp, 16);
}

// 0x2A1280 sub_2A1280(a0 = target RGBA, a1 = frames): the screen colour fade packet (kind 1540, 40 data bytes, callback
// sub_2A10E0): data +0..+12 the target as floats (bytes * 1/255), +32 = frames.
void Cpu::sub_2A1280() {
    enter(18);
    sp = addiu(sp, -64);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    s0 = a1;
    a0 = li(kPktScreenFade);
    a1 = li(40);
    jal(0x2a12a0, rg::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2a);
    v1 = addiu(v1, 4320);  // sub_2A10E0
    sw(v1, v0, kPktCallback);
    lw(a1, v0, kPktData);
    // the bytes of a0 through the frame word sp+60, into a1 (scratch v1 / a0)
    sw(s1, sp, 60);
    for (int k = 0; k < 4; ++k) {
        lbu(v1, sp, 60 + k);
        u2f(F1, F0, v1, a0, v1);
        charge(k < 3 ? 6 : 10);
        lwc1(F0, gp, kGpInv255);
        mul_s(F0, F0, F1);
        swc1(F0, a1, 4 * k);
    }
    sw(s0, a1, 32);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// 0x2A1400 sub_2A1400(data): the per-frame callback of sub_2A16C0's packet: the fade back to the battle's base screen
// colour (the four bytes at gp-18424 as floats * 1/255). data +0..+12 the start (gBtl+564 on the first frame), +16 the
// frames, +20 the frame counter; the same lerp and result as sub_2A10E0.
void Cpu::sub_2A1400() {
    enter(4);
    sp = addiu(sp, -32);
    lw(v0, a0, 20);
    if (v0 == 0) {
        charge(9);
        gbtl(v0);
        copy_vec4(v0, kScreenColour, a0, 0);
    }
    charge(3);
    for (int k = 0; k < 4; ++k) {
        lbu(v0, gp, kGpBaseColour + k);
        u2f(F1, F0, v0, v1, v0);
        charge(k < 3 ? 6 : 8);
        lwc1(F0, gp, kGpInv255);
        mul_s(F0, F0, F1);
        swc1(F0, sp, 4 * k);
    }
    lw(a1, a0, 16);
    lw(v0, a0, 20);
    at = sltu(v0, a1);
    if (at != 0) {
        charge(2);
        u2f(F1, F0, v0, v1, v0);
        charge(2);
        u2f(F0, F0, a1, v1, v0);
        charge(38);
        // F3 = t, F2 = 1 - t; sp+16.. = sp+0.. * t + data * (1 - t)
        div_s(F3, F1, F0);
        lif(v0, 0x3f80, F0);
        sub_s(F2, F0, F3);
        for (int k = 0; k < 4; ++k) {
            lwc1(F1, a0, 4 * k);
            lwc1(F0, sp, 4 * k);
            mula_s(F0, F3);
            madd_s(F0, F1, F2);
            swc1(F0, sp, 16 + 4 * k);
        }
        gbtl(v0);
        copy_vec4(sp, 16, v0, kScreenColour);
        charge(4);
        lw(v0, a0, 20);
        v0 = addiu(v0, 1);
        sw(v0, a0, 20);
        v0 = 0;
    } else {
        charge(12);
        gbtl(v0);
        copy_vec4(sp, 0, v0, kScreenColour);
        v0 = li(1);
    }
    charge(3);
    sp = addiu(sp, 32);
}

// 0x2A16C0 sub_2A16C0(a0 = frames): the fade back to the base screen colour (kind 1541, 24 data bytes, callback
// sub_2A1400): data +16 = frames.
void Cpu::sub_2A16C0() {
    enter(18);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    a0 = li(kPktScreenRestore);
    a1 = li(24);
    jal(0x2a16d8, rg::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2a);
    v1 = addiu(v1, 5120);  // sub_2A1400
    sw(v1, v0, kPktCallback);
    lw(v1, v0, kPktData);
    sw(s0, v1, 16);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// 0x2A1710 sub_2A1710(data): the per-frame callback of the unit fade-out (sub_2A1B00's packet). data +0 the acting
// btlAction, +4 the frames, +8 the frame counter, +12 its skill (u16). Returns 1 at once while gBtl+16 bit 3 is set, for
// a skill whose SKILL.TBL +17 is 16, or when the action has fewer than two targets and its own unit is an enemy. The
// sides to fade: sub_2D6290(action) ? the actor's own side bit (1 << unit+162) : both (3); when the actor is a party
// unit and none of its targets is an enemy, returns 1. Alpha = (1 - frame / frames) * 255 while frame < frames (then
// 0 and the result 1, else 0): every visible unit (+2546 != 0, +156 bit 0 clear) of a faded side but the actor's own
// gets its RGB with that alpha (sub_27F730), every target is reset to alpha 255, and frame++.
void Cpu::sub_2A1710() {
    enter(18);
    sp = addiu(sp, -144);
    sd(ra, sp, 112);
    sq(s6, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s4 = a0;
    s1 = li(1);
    lw(s3, a0, 0);
    lhu(v1, a0, 12);
    gbtl(v0);
    lw(v0, v0, btl_task::kFlags2);
    v0 = v0 & 0x8;
    if (v0 != 0) {
        charge(3);
        v0 = s1;
        return epilogue_2A1710();
    }
    charge(12);
    lw(a0, gp, kGpSkillTbl);
    skill_record(v0, v1, a0);
    lbu(v1, v0, 17);
    v0 = li(16);
    if (v1 == v0) {
        charge(3);
        v0 = s1;
        return epilogue_2A1710();
    }
    charge(4);
    lhu(v0, s3, kActTargetCount);
    at = slti(v0, 2);
    if (at != 0) {
        charge(4);
        lw(v0, s3, btl_task::kActUnit);
        lbu(v0, v0, btl_task::kUnitSide);
        if (v0 != 0) {
            charge(3);
            v0 = s1;
            return epilogue_2A1710();
        }
    }
    charge(5);
    a0 = s3;
    jal(0x2a17d0, rg::fn_sub_2D6290_002d6290);
    if (v0 != 0) {
        charge(7);
        lw(v0, s3, btl_task::kActUnit);
        lbu(v1, v0, btl_task::kUnitSide);
        v0 = li(1);
        v0 = sllv(v0, v1);
        v0 = v0 & 0xffff;
    } else {
        charge(1);
        v0 = li(3);
    }
    charge(5);
    v0 = v0 & 0xffff;
    lw(v1, s3, btl_task::kActUnit);
    lbu(v1, v1, btl_task::kUnitSide);
    if (v1 == 0) {
        // a party actor: done unless one of its targets is an enemy
        charge(5);
        a1 = li(1);
        a2 = 0;
        lhu(a0, s3, kActTargetCount);
        for (;;) {
            charge(4);
            v1 = a2 & 0xffff;
            v1 = slt(v1, a0);
            if (v1 == 0) break;
            backedge();
            charge(8);
            v1 = a2 & 0xffff;
            v1 = sll(v1, 2);
            v1 = addu(s3, v1);
            lw(v1, v1, kActTargets);
            lw(v1, v1, btl_task::kActUnit);
            lbu(v1, v1, btl_task::kUnitSide);
            if (v1 != 0) {
                charge(3);
                a1 = 0;
                break;
            }
            charge(2);
            v1 = addiu(a2, 1);
            a2 = v1 & 0xffff;
        }
        charge(2);
        if (a1 != 0) {
            charge(3);
            v0 = li(1);
            return epilogue_2A1710();
        }
    }
    charge(5);
    lw(a1, s4, 4);
    lw(v1, s4, 8);
    at = sltu(v1, a1);
    if (at != 0) {
        charge(2);
        u2f(F1, F0, v1, a0, v1);
        charge(2);
        u2f(F0, F0, a1, a0, v1);
        charge(17);
        div_s(F1, F1, F0);
        lif(v1, 0x3f80, F0);
        sub_s(F1, F0, F1);
        lif(v1, 0x437f, F0);  // 255.0
        mul_s(F1, F0, F1);
        f2u(a0, F1, v1, 0xff);
        charge(4);
        s5 = a0 & 0xff;
        s1 = 0;
    } else {
        charge(1);
        s5 = 0;
    }
    charge(4);
    s0 = 0;
    s6 = v0 & 0xffff;
    // the faded sides' units (gBtl+336 + 8 * side, along +2612)
    for (;;) {
        charge(4);
        v0 = s0 & 0xffff;
        v0 = slti(v0, 2);
        if (v0 == 0) break;
        backedge();
        charge(7);
        v0 = s0 & 0xffff;
        v1 = sll(v0, 3);
        gbtl(v0);
        v0 = addu(v0, v1);
        lw(s2, v0, kSideListB);
        for (;;) {
            charge(2);
            if (s2 == 0) break;
            backedge();
            charge(6);
            lbu(v1, s2, btl_task::kUnitSide);
            v0 = li(1);
            v0 = sllv(v0, v1);
            v0 = s6 & v0;
            if (v0 != 0) {
                charge(3);
                lhu(v0, s2, kUnitModelId);
                if (v0 != 0) {
                    charge(4);
                    lw(v0, s2, btl_task::kUnitFlags);
                    v0 = v0 & 0x1;
                    if (v0 == 0) {
                        charge(3);
                        lw(v0, s3, btl_task::kActUnit);
                        if (s2 != v0) {
                            charge(13);
                            unit_rgba_to_frame(s2, 140);
                            sb(s5, sp, 143);
                            a0 = s2;
                            lw(a1, sp, 140);
                            jal(0x2a1a24, rg::fn_sub_27F730_0027f730);
                        }
                    }
                }
            }
            charge(1);
            lw(s2, s2, kUnitNextB);
        }
        charge(2);
        v0 = addiu(s0, 1);
        s0 = v0 & 0xffff;
    }
    charge(3);
    s0 = 0;
    // the targets back to alpha 255
    for (;;) {
        charge(5);
        v1 = s0 & 0xffff;
        lhu(v0, s3, kActTargetCount);
        v0 = slt(v1, v0);
        if (v0 == 0) break;
        backedge();
        charge(20);
        v0 = s0 & 0xffff;
        v0 = sll(v0, 2);
        v0 = addu(s3, v0);
        lw(v0, v0, kActTargets);
        lw(a0, v0, btl_task::kActUnit);
        lbu(a2, a0, 48);
        lbu(a1, a0, 49);
        lbu(v1, a0, 50);
        lbu(v0, a0, 51);
        sb(a2, sp, 136);
        sb(a1, sp, 137);
        sb(v1, sp, 138);
        sb(v0, sp, 139);
        v0 = li(255);
        sb(v0, sp, 139);
        lw(a1, sp, 136);
        jal(0x2a1a9c, rg::fn_sub_27F730_0027f730);
        v0 = addiu(s0, 1);
        s0 = v0 & 0xffff;
    }
    charge(4);
    lw(v0, s4, 8);
    v0 = addiu(v0, 1);
    sw(v0, s4, 8);
    v0 = s1;
    epilogue_2A1710();
}
void Cpu::epilogue_2A1710() {
    charge(11);
    ld(ra, sp, 112);
    lq(s6, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 144);
}

// 0x2A1B00 sub_2A1B00(a0 = action, a1 = skill, a2 = frames): the unit fade-out packet (kind 1542, 16 data bytes,
// callback sub_2A1710): data +0 = action, +4 = frames, +12 = skill (u16), +8 = 0.
void Cpu::sub_2A1B00() {
    enter(27);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = li(kPktUnitFade);
    a1 = li(16);
    jal(0x2a1b28, rg::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2a);
    v1 = addiu(v1, 5904);  // sub_2A1710
    sw(v1, v0, kPktCallback);
    lw(v1, v0, kPktData);
    sw(s2, v1, 0);
    sw(s0, v1, 4);
    sh(s1, v1, 12);
    sw(zero, v1, 8);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// 0x2A1B70 sub_2A1B70(data): the per-frame callback of the unit fade-in (sub_2A1DB0's packet). Returns 1 at once when
// gBtl+12 bit 22 and gBtl+24 bit 4 are both set. data +0 the frames, +4 the frame counter: alpha = frame / frames * 255
// while frame < frames (then 255 and the result 1, else 0); every visible unit of both sides whose alpha is below it
// gets it (sub_27F730), and frame++.
void Cpu::sub_2A1B70() {
    enter(15);
    sp = addiu(sp, -128);
    sd(ra, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    gbtl(a0);
    lw(v1, a0, btl_task::kFlags);
    v0 = lui(0x40);
    v0 = v1 & v0;
    if (v0 != 0) {
        charge(4);
        lhu(v0, a0, btl_task::kEndFlags);
        v0 = v0 & 0x10;
        if (v0 != 0) {
            charge(3);
            v0 = li(1);
            return epilogue_2A1B70();
        }
    }
    charge(6);
    s3 = li(1);
    lw(a0, s0, 0);
    lw(v0, s0, 4);
    at = sltu(v0, a0);
    if (at != 0) {
        charge(2);
        u2f(F1, F0, v0, v1, v0);
        charge(2);
        u2f(F0, F0, a0, v1, v0);
        charge(13);
        div_s(F1, F1, F0);
        lif(v0, 0x437f, F0);  // 255.0
        mul_s(F1, F0, F1);
        f2u(v1, F1, v0, 0xff);
        charge(4);
        s2 = v1 & 0xff;
        s3 = 0;
    } else {
        charge(1);
        s2 = dli(255);
    }
    charge(4);
    s4 = 0;
    s1 = s2 & 0xff;
    for (;;) {
        charge(4);
        v0 = s4 & 0xffff;
        v0 = slti(v0, 2);
        if (v0 == 0) break;
        backedge();
        charge(7);
        v0 = s4 & 0xffff;
        v1 = sll(v0, 3);
        gbtl(v0);
        v0 = addu(v0, v1);
        lw(s5, v0, kSideListB);
        for (;;) {
            charge(2);
            if (s5 == 0) break;
            backedge();
            charge(3);
            lhu(v0, s5, kUnitModelId);
            if (v0 != 0) {
                charge(4);
                lw(v0, s5, btl_task::kUnitFlags);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    charge(12);
                    unit_rgba_to_frame(s5, 124);
                    lbu(v0, sp, 127);
                    at = slt(v0, s1);
                    if (at != 0) {
                        charge(5);
                        sb(s2, sp, 127);
                        a0 = s5;
                        lw(a1, sp, 124);
                        jal(0x2a1d4c, rg::fn_sub_27F730_0027f730);
                    }
                }
            }
            charge(1);
            lw(s5, s5, kUnitNextB);
        }
        charge(2);
        v0 = addiu(s4, 1);
        s4 = v0 & 0xffff;
    }
    charge(4);
    lw(v0, s0, 4);
    v0 = addiu(v0, 1);
    sw(v0, s0, 4);
    v0 = s3;
    epilogue_2A1B70();
}
void Cpu::epilogue_2A1B70() {
    charge(10);
    ld(ra, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 128);
}

// 0x2A1DB0 sub_2A1DB0(a0 = frames): the unit fade-in packet (kind 1543, 8 data bytes, callback sub_2A1B70): data +0 =
// frames.
void Cpu::sub_2A1DB0() {
    enter(18);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    a0 = li(kPktUnitFadeIn);
    a1 = li(8);
    jal(0x2a1dc8, rg::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2a);
    v1 = addiu(v1, 7024);  // sub_2A1B70
    sw(v1, v0, kPktCallback);
    lw(v1, v0, kPktData);
    sw(s0, v1, 0);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// =====================================================================================================================
// Small battle helpers of the camera states (0x2A32F0-0x2A3850)
// =====================================================================================================================

// 0x2A32F0 sub_2A32F0(record): whether the subject's camera is skipped: 0 without a subject (record+224), else 1 when
// sub_2FDFE0(record) says so, when the subject's unit has bad status 0x80 (datCalcChkBadStatus(DatUnit, 128)), or when
// sub_2D5F50(subject) is non-zero.
void Cpu::sub_2A32F0() {
    enter(6);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    lw(s0, a0, kRcSubject);
    if (s0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(4);
        jal(0x2a3314, rg::fn_sub_2FDFE0_002fdfe0);
        if (v0 != 0) {
            charge(3);
            v0 = li(1);
        } else {
            charge(7);
            lw(v0, s0, btl_task::kActUnit);
            lw(a0, v0, btl_task::kUnitDat);
            a1 = li(128);
            jal(0x2a333c, rg::fn_datCalcChkBadStatus_00300580);
            if (v0 != 0) {
                charge(3);
                v0 = li(1);
            } else {
                charge(4);
                a0 = s0;
                jal(0x2a335c, rg::fn_sub_2D5F50_002d5f50);
                v0 = sltu(zero, v0);
            }
        }
    }
    charge(5);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// The persona check of sub_2A3380 / sub_2A3420 (v0 = the subject unit's sub-object, a1 = the skill): the sub-object's
// 88-byte record (*(gp-18628) + 88 * its +164) with bit 0 set -> 0; else the skill's 28-byte attribute record
// (*(gp-18672) + 28 * skill) with flag 0x10 -> 0, else 1. Charges its blocks; the caller's next block follows.
void Cpu::skill_needs_camera() {
    bool skip = false;
    if (v0 != 0) {
        charge(12);
        lhu(v1, v0, kUnPersonaIdx);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 3);
        lw(v0, gp, kGpPersonaTbl);
        v0 = addu(v0, v1);
        lhu(v0, v0, 0);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            charge(3);
            v0 = 0;
            skip = true;
        }
    }
    if (!skip) {
        charge(10);
        skill_attr_flags(a1);
        v0 = v0 & 0x10;
        if (v0 != 0) {
            charge(3);
            v0 = 0;
        } else {
            charge(1);
            v0 = li(1);
        }
    }
}
// v0 = the flags halfword (+2) of skill `skill`'s 28-byte attribute record (*(gp-18672)); a0 / v1 scratch
void Cpu::skill_attr_flags(const Gpr& skill) {
    lw(a0, gp, kGpSkillAttr);
    v1 = skill & 0xffff;
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    lhu(v0, v0, 2);
}

// 0x2A3380 sub_2A3380(record): whether the subject's skill (+110) gets a camera (skill_needs_camera: 0 for a persona
// whose record has bit 0, or a skill with attribute flag 0x10; else 1).
void Cpu::sub_2A3380() {
    enter(6);
    lw(v1, a0, kRcSubject);
    lw(v0, v1, btl_task::kActUnit);
    lw(v0, v0, kUnPersona);
    lhu(a1, v1, kAcSkill);
    skill_needs_camera();
    charge(2);
}

// 0x2A3420 sub_2A3420(record): 1 at once while gBtl+12 bit 21 is set; else 1 when the subject's skill gets a camera
// (sub_2A3380's test) and its attribute flags have 0x20, otherwise 0.
void Cpu::sub_2A3420() {
    enter(6);
    gbtl(v0);
    lw(v1, v0, btl_task::kFlags);
    v0 = lui(0x20);
    v0 = v1 & v0;
    if (v0 != 0) {
        charge(3);
        v0 = li(1);
    } else {
        charge(6);
        lw(v0, a0, kRcSubject);
        lhu(a1, v0, kAcSkill);
        lw(v0, v0, btl_task::kActUnit);
        lw(v0, v0, kUnPersona);
        skill_needs_camera();
        charge(2);
        bool one = false;
        if (v0 != 0) {
            charge(10);
            skill_attr_flags(a1);
            v0 = v0 & 0x20;
            if (v0 != 0) {
                charge(3);
                v0 = li(1);
                one = true;
            }
        }
        if (!one) {
            charge(1);
            v0 = 0;
        }
    }
    charge(2);
}

// 0x2A3520 sub_2A3520(record): the subject's move kind (+108) is 3 (0 without a subject).
void Cpu::sub_2A3520() {
    enter(3);
    lw(v0, a0, kRcSubject);
    if (v0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(3);
        lhu(v0, v0, kAcMoveKind);
        v0 = v0 ^ 0x3;
        v0 = sltiu(v0, 1);
    }
    charge(2);
}

// 0x2A3550 sub_2A3550(record): sub_308A50(the subject's +114 halfword), 0 without a subject.
void Cpu::sub_2A3550() {
    enter(5);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v0, a0, kRcSubject);
    if (v0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(3);
        lhu(a0, v0, kAcItem);
        jal(0x2a3574, rg::fn_sub_308A50_00308a50);
    }
    charge(4);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// One axis of sub_2A3590: the key's coordinate at s1+`axis` beyond +-1500 is pulled back along the key's view
// direction (sub_4BE1E0(sp+64, (0, 0, 1) at 0x697890, 1, key rotation s1+12)) so that it lands on the limit: out (s0) =
// key + dir * ((|coord| - 1500) / |dir.axis|) (not when the direction's axis component is 0); v0 = 1 when beyond.
void Cpu::clamp_axis_2A3590(s32 axis, u32 link, u64 after) {
    lwc1(F0, s1, axis);
    abs_s(F1, F0);
    v1 = li(1500);
    mtc1(v1, F0);
    cvt_s_w(F0, F0);
    c_le_s(F1, F0);
    if (cc()) {
        charge(after);
        return;
    }
    charge(2);
    if (s0 != 0) {
        charge(14);
        sub_s(F20, F1, F0);
        a0 = addiu(sp, 64);
        a1 = lui(0x69);
        a1 = addiu(a1, 30864);  // 0x697890: (0, 0, 1)
        a2 = li(1);
        a3 = addiu(s1, 12);
        jal(link, rg::fn_sub_4BE1E0_004be1e0);
        const unsigned fd = axis == 0 ? F1 : F3;
        lwc1(fd, sp, 64 + axis);
        mtc1(zero, F0);
        c_eq_s(F0, fd);
        if (!cc()) {
            charge(22);
            abs_s(F0, fd);
            div_s(F2, F20, F0);
            if (axis == 0) {
                mul_s(F1, F1, F2);
                swc1(F1, sp, 64);
                lwc1(F0, sp, 68);
                mul_s(F0, F0, F2);
                swc1(F0, sp, 68);
                lwc1(F0, sp, 72);
                mul_s(F0, F0, F2);
                swc1(F0, sp, 72);
            } else {
                lwc1(F0, sp, 64);
                mul_s(F1, F0, F2);
                swc1(F1, sp, 64);
                lwc1(F0, sp, 68);
                mul_s(F0, F0, F2);
                swc1(F0, sp, 68);
                mul_s(F0, F3, F2);
                swc1(F0, sp, 72);
            }
            lwc1(F0, s1, 0);
            add_s(F0, F0, F1);
            swc1(F0, s0, 0);
            lwc1(F1, s1, 4);
            lwc1(F0, sp, 68);
            add_s(F0, F1, F0);
            swc1(F0, s0, 4);
            lwc1(F1, s1, 8);
            lwc1(F0, sp, 72);
            add_s(F0, F1, F0);
            swc1(F0, s0, 8);
        }
    }
    charge(1);
    v0 = li(1);
    charge(after);
}

// 0x2A3590 sub_2A3590(key, out): keeps a camera key inside the arena: x (+0) and then z (+8) beyond +-1500 are pulled
// back along the key's view direction into `out` (clamp_axis_2A3590; out may be 0: only the test). Returns 1 when
// either was beyond, else 0.
void Cpu::sub_2A3590() {
    enter(17);
    sp = addiu(sp, -80);
    sd(ra, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F20, sp, 0);
    s1 = a0;
    s0 = a1;
    v0 = 0;
    clamp_axis_2A3590(0, 0x2a35f4, 9);
    clamp_axis_2A3590(8, 0x2a36b4, 7);
    ld(ra, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 80);
}

// 0x2A3750 sub_2A3750(record, unit): whether the unit's current motion has reached its strike: 0 without a unit, when
// its +51 byte is 0 or its +152 bit 1 is clear; else motion = (s16) sub_282C30(unit), strike = (s16)
// sub_2835E0(unit, motion; $f12 = 1.0), returns !(sub_283BA0(unit) < strike) as signed halfwords.
void Cpu::sub_2A3750() {
    enter(7);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s0 = a1;
    if (s0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(3);
        lbu(v0, s0, 51);
        if (v0 == 0) {
            charge(3);
            v0 = 0;
        } else {
            charge(4);
            lw(v0, s0, 152);
            v0 = v0 & 0x2;
            if (v0 == 0) {
                charge(3);
                v0 = 0;
            } else {
                charge(22);
                a0 = s0;
                jal(0x2a37b0, rg::fn_sub_282C30_00282c30);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                a1 = v0 & 0xffff;
                lif(v0, 0x3f80, F12);
                a0 = s0;
                jal(0x2a37d0, rg::fn_sub_2835E0_002835e0);
                s1 = dsll32(v0, 16);
                s1 = dsra32(s1, 16);
                a0 = s0;
                jal(0x2a37e4, rg::fn_sub_283BA0_00283ba0);
                v1 = dsll32(v0, 16);
                v1 = dsra32(v1, 16);
                v0 = dsll32(s1, 16);
                v0 = dsra32(v0, 16);
                v0 = slt(v1, v0);
                v0 = v0 ^ 0x1;
            }
        }
    }
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// 0x2A3820 sub_2A3820(record): whether the subject's skill (+110) has attribute flag 0x4000 (its 28-byte record at
// *(gp-18672)).
void Cpu::sub_2A3820() {
    enter(12);
    lw(v0, a0, kRcSubject);
    lhu(v1, v0, kAcSkill);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 2);
    lw(v0, gp, kGpSkillAttr);
    v0 = addu(v1, v0);
    lhu(v0, v0, 2);
    v0 = v0 & 0x4000;
    v0 = sltu(zero, v0);
}

// 0x2A3850 sub_2A3850(record): 1 when one of the subject's targets (+56, +106 of them) has a unit that is dead
// (datCalcIsDead(DatUnit, 0)), else 0.
void Cpu::sub_2A3850() {
    enter(8);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    lw(s0, a0, kRcSubject);
    s1 = 0;
    for (;;) {
        charge(5);
        v1 = s1 & 0xffff;
        lhu(v0, s0, kActTargetCount);
        v0 = slt(v1, v0);
        if (v0 == 0) {
            charge(1);
            v0 = 0;
            break;
        }
        backedge();
        charge(6);
        v0 = s1 & 0xffff;
        v0 = sll(v0, 2);
        v0 = addu(s0, v0);
        lw(v0, v0, kActTargets);
        if (v0 != 0) {
            charge(3);
            lw(v0, v0, btl_task::kActUnit);
            if (v0 != 0) {
                charge(6);
                lw(a0, v0, btl_task::kUnitDat);
                a1 = 0;
                jal(0x2a389c, rg::fn_datCalcIsDead_0030b5a0);
                if (v0 != 0) {
                    charge(3);
                    v0 = li(1);
                    break;
                }
            }
        }
        charge(2);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xffff;
    }
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// =====================================================================================================================
// The camera set / switch layer
// =====================================================================================================================

// 0x2A38F0 sub_2A38F0(id, subject, hide_units): switches the battle camera to row `id`. The row is sub_2F8840(id) (a
// boss band's own table) or, when that returns 0, the camera table row 0x6939F0 + 20 * id ({+0 init, +4 update, +8
// restart flag, +12 flag}). Setting the camera that is already current (gBtl+240) does nothing unless the row's +8 flag
// is set. The history shift of gBtl+258.. never runs (the compiled loop tests `beqz` on a counter that starts at 2);
// gBtl+260 = the old id, gBtl+266 counts repeats of the same id (else 0); gBtl+240 = id, +248 = +252 = 0, +256 = the
// subject; gBtl+244 bit 1 = the row's +12 flag. With hide_units, sub_2A42A0 hides every unit's flag 7; then the row's
// init runs through `jalr` with the camera work record gBtl+32 in $a0.
void Cpu::sub_2A38F0() {
    enter(14);
    sp = addiu(sp, -80);
    sd(ra, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    jal(0x2a3914, rg::fn_sub_2F8840_002f8840);
    s0 = v0;
    if (v0 == 0) {
        charge(7);
        a0 = s3 & 0xffff;  // the row: 0x6939F0 + 20 * id
        v1 = sll(a0, 2);
        v1 = addu(v1, a0);
        a0 = sll(v1, 2);
        v1 = lui(0x69);
        v1 = addiu(v1, 14832);
        s0 = addu(v1, a0);
    }
    charge(5);
    a2 = s3 & 0xffff;
    gbtl(v1);
    lhu(v1, v1, kBtCamId);
    if (v1 == a2) {
        charge(3);
        lw(v1, s0, 8);
        if (v1 == 0) return epilogue_2A38F0();
    }
    charge(3);
    a3 = dli(2);
    for (;;) {  // (dead: the counter starts at 2 and the loop runs while it is 0)
        charge(3);
        v1 = a3 & 0xffff;
        if (v1 != 0) break;
        backedge();
        charge(10);
        lw(a1, gp, kGpBtl);
        v1 = sll(v1, 1);
        v1 = addu(a1, v1);
        lhu(a0, v1, kBtCamHistory);
        v1 = a3 & 0xffff;
        v1 = sll(v1, 1);
        v1 = addu(a1, v1);
        sh(a0, v1, kBtCamHistory + 2);
        v1 = addiu(a3, -1);
        a3 = v1 & 0xffff;
    }
    charge(7);
    lw(a0, gp, kGpBtl);
    lhu(v1, a0, kBtCamId);
    sh(v1, a0, kBtCamHistory + 2);
    lw(a0, gp, kGpBtl);
    lhu(v1, a0, kBtCamId);
    if (v1 == a2) {
        charge(5);
        lhu(v1, a0, kBtCamRepeat);
        v1 = addiu(v1, 1);
        sh(v1, a0, kBtCamRepeat);
    } else {
        charge(1);
        sh(zero, a0, kBtCamRepeat);
    }
    charge(11);
    gbtl(v1);
    sh(s3, v1, kBtCamId);
    gbtl(v1);
    sw(zero, v1, kBtCam248);
    gbtl(v1);
    sw(zero, v1, kBtCam252);
    gbtl(v1);
    sw(s2, v1, kBtCamSubject);
    lw(v1, s0, 12);
    if (v1 != 0) {
        charge(6);
        gbtl(a0);
        lw(v1, a0, kBtCamFlags);
        v1 = v1 | 0x2;
        sw(v1, a0, kBtCamFlags);
    } else {
        charge(5);
        gbtl(a1);
        lw(a0, a1, kBtCamFlags);
        v1 = li(-3);
        v1 = a0 & v1;
        sw(v1, a1, kBtCamFlags);
    }
    charge(2);
    if (s1 != 0) {
        charge(2);
        jal(0x2a3a38, rg::fn_sub_2A42A0_002a42a0);
    }
    charge(3);
    lw(v1, s0, 0);
    if (v1 != 0) {
        charge(4);
        gbtl(v0);
        a0 = addiu(v0, kBtCamRec);
        jalr(v1, 0x2a3a54);  // the row's init (camera work record)
    }
    epilogue_2A38F0();
}
void Cpu::epilogue_2A38F0() {
    charge(8);
    ld(ra, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 80);
}

// 0x2A3A80 sub_2A3A80(): the current camera id (gBtl+240).
void Cpu::sub_2A3A80() {
    enter(4);
    gbtl(v0);
    lhu(v0, v0, kBtCamId);
}

// 0x2A3A90 sub_2A3A90(action): forgets a btlAction that goes away: the camera's subject (gBtl+256) is cleared when its
// +8 word equals the action's, and while camera 12 is current the same for the parameter word gBtl+288.
void Cpu::sub_2A3A90() {
    enter(5);
    gbtl(v1);
    a2 = addiu(v1, kBtCamSubject);
    lw(v1, v1, kBtCamSubject);
    if (v1 != 0) {
        charge(4);
        lw(a1, v1, 8);
        lw(v1, a0, 8);
        if (a1 == v1) {
            charge(1);
            sw(zero, a2, 0);
        }
        charge(5);
        gbtl(a3);
        lhu(a1, a3, kBtCamId);
        v1 = li(12);
        if (a1 != v1) {
            charge(2);
        } else {
            charge(4);
            a2 = addiu(a3, kBtCamParam);
            lw(v1, a3, kBtCamParam);
            if (v1 != 0) {
                charge(4);
                lw(a1, v1, 8);
                lw(v1, a0, 8);
                if (a1 == v1) {
                    charge(1);
                    sw(zero, a2, 0);
                }
            }
        }
    }
    charge(2);
}

// 0x2A3B00 sub_2A3B00(data): the callback of sub_2A3B40's packet: sub_2A38F0(data+4 (u16), data+0, 1); returns 1.
void Cpu::sub_2A3B00() {
    enter(13);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    v0 = a0;
    lhu(a0, a0, 4);
    lw(a1, v0, 0);
    a2 = li(1);
    jal(0x2a3b18, rg::fn_sub_2A38F0_002a38f0);
    v0 = li(1);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// 0x2A3B40 sub_2A3B40(subject, id): the camera switch packet (kind 512, 8 data bytes, callback sub_2A3B00): data +0 =
// subject, +4 = id (u16).
void Cpu::sub_2A3B40() {
    enter(22);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    s0 = a1;
    a0 = li(kPktCameraSet);
    a1 = li(8);
    jal(0x2a3b60, rg::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2a);
    v1 = addiu(v1, 15104);  // sub_2A3B00
    sw(v1, v0, kPktCallback);
    lw(v1, v0, kPktData);
    sw(s1, v1, 0);
    sh(s0, v1, 4);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// 0x2A3BA0 sub_2A3BA0(data): the callback of sub_2A3D70's packet: a scripted camera move. Camera 1 is set
// (sub_2A38F0(1, data+0, 1)); the start key (sp+80: position + rotation) is the current key gBtl+188 when data+56 is set,
// else data+4 looking at data+16 (sub_2A4690, up (0, 1, 0) at 0x697880); the end key (sp+108) data+28 looking at
// data+40. The camera object gBtl+32 is reset (flags 1, ring empty) and gets four keys: start, the interpolations at 1/3
// and 2/3 (sub_2A1E00 with the $gp constants gp-32056 / gp-32676), end; its duration +164 = data+52 * 60 (sub_2A3110's
// eased curve: +180 = 0.5, flags bit 1 off, bit 2 on). Returns 1.
void Cpu::sub_2A3BA0() {
    enter(13);
    sp = addiu(sp, -144);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    a0 = li(1);
    lw(a1, s0, 0);
    a2 = a0;
    jal(0x2a3bc0, rg::fn_sub_2A38F0_002a38f0);
    lw(v0, s0, 56);
    if (v0 != 0) {
        charge(7);
        gbtl(v0);
        a0 = addiu(sp, 80);
        a1 = addiu(v0, kBtCamKey);
        jal(0x2a3be0, rg::fn_sub_2A4470_002a4470);
    } else {
        charge(13);
        a0 = addiu(sp, 92);
        a1 = addiu(s0, 4);
        a2 = addiu(s0, 16);
        a3 = lui(0x69);
        a3 = addiu(a3, 30848);  // 0x697880: (0, 1, 0)
        jal(0x2a3c04, rg::fn_sub_2A4690_002a4690);
        copy_vec3(s0, 4, sp, 80);
    }
    charge(80);
    a0 = addiu(sp, 120);
    a1 = addiu(s0, 28);
    a2 = addiu(s0, 40);
    a3 = lui(0x69);
    a3 = addiu(a3, 30848);
    jal(0x2a3c38, rg::fn_sub_2A4690_002a4690);
    copy_vec3(s0, 28, sp, 108);
    // the camera object gBtl+32: flags 1, the ring empty
    gbtl(v1);
    s1 = addiu(v1, kBtCamRec);
    v0 = li(1);
    sh(v0, v1, kBtCamRec + 0);
    sh(zero, v1, kBtCamRec + 116);
    sh(zero, v1, kBtCamRec + 118);
    sh(zero, v1, kBtCamRec + 120);
    sw(zero, v1, kBtCamRec + 128);
    sw(zero, v1, kBtCamRec + 124);
    a0 = s1;
    a1 = addiu(sp, 80);
    a2 = addiu(sp, 92);
    jal(0x2a3c88, rg::fn_sub_2A2050_002a2050);
    a0 = addiu(sp, 48);
    a1 = addiu(sp, 80);
    a2 = addiu(sp, 108);
    lwc1(F12, gp, kGpOneThird);
    jal(0x2a3ca0, rg::fn_sub_2A1E00_002a1e00);
    a0 = s1;
    a1 = addiu(sp, 48);
    a2 = addiu(sp, 60);
    jal(0x2a3cb4, rg::fn_sub_2A2050_002a2050);
    a0 = addiu(sp, 48);
    a1 = addiu(sp, 80);
    a2 = addiu(sp, 108);
    lwc1(F12, gp, kGpTwoThirds);
    jal(0x2a3ccc, rg::fn_sub_2A1E00_002a1e00);
    a0 = s1;
    a1 = addiu(sp, 48);
    a2 = addiu(sp, 60);
    jal(0x2a3ce0, rg::fn_sub_2A2050_002a2050);
    a0 = s1;
    a1 = addiu(sp, 108);
    a2 = addiu(sp, 120);
    jal(0x2a3cf4, rg::fn_sub_2A2050_002a2050);
    // the duration: data+52 * 2 * 60 / 2, eased
    gbtl(v1);
    lif(v0, 0x4000, F2);  // 2.0
    lwc1(F0, s0, 52);
    mul_s(F1, F2, F0);
    lif(v0, 0x4270, F0);  // 60.0
    mul_s(F0, F0, F1);
    div_s(F0, F0, F2);
    swc1(F0, v1, kBtCamRec + 132);
    v0 = lui(0x3f00);  // 0.5
    sw(v0, v1, kBtCamRec + 148);
    lhu(v0, v1, kBtCamRec + 0);
    v0 = v0 & 0xfffd;
    sh(v0, v1, kBtCamRec + 0);
    lhu(v0, v1, kBtCamRec + 0);
    v0 = v0 | 0x4;
    sh(v0, v1, kBtCamRec + 0);
    v0 = li(1);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 144);
}

// 0x2A3D70 sub_2A3D70(subject, eye0, at0, eye1, at1 ($t0); $f12 seconds): the scripted camera move packet (kind 513,
// 60 data bytes, callback sub_2A3BA0): data +0 subject, +52 the seconds; +4 / +16 the start eye / target (both given;
// else +56 = 1: start from the current key), +28 / +40 the end eye / target.
void Cpu::sub_2A3D70() {
    enter(26);
    sp = addiu(sp, -112);
    sd(ra, sp, 96);
    sq(s4, sp, 80);
    sq(s3, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F20, sp, 0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    s0 = t0;
    mov_s(F20, F12);
    a0 = li(kPktCameraMove);
    a1 = li(60);
    jal(0x2a3db0, rg::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2a);
    v1 = addiu(v1, 15264);  // sub_2A3BA0
    sw(v1, v0, kPktCallback);
    lw(a0, v0, kPktData);
    sw(s4, a0, 0);
    swc1(F20, a0, 52);
    bool both = false;
    if (s3 != 0) {
        charge(2);
        both = s2 != 0;
    }
    if (both) {
        charge(15);
        copy_vec3(s3, 0, a0, 4);
        copy_vec3(s2, 0, a0, 16);
        sw(zero, a0, 56);
    } else {
        charge(2);
        v1 = li(1);
        sw(v1, a0, 56);
    }
    charge(22);
    copy_vec3(s1, 0, a0, 28);
    copy_vec3(s0, 0, a0, 40);
    ld(ra, sp, 96);
    lq(s4, sp, 80);
    lq(s3, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 112);
}

// The range test of sub_2A3E80: x = sp+xo against [sp+lo, sp+hi] taken in either order (lo >= x >= hi or
// lo <= x <= hi, the edges included as compiled); x / lo are loaded into $f2 / $f1 here.
bool Cpu::in_span_2A3E80(s32 lo, s32 hi, s32 xo) {
    lwc1(F2, sp, xo);
    lwc1(F1, sp, lo);
    c_lt_s(F1, F2);
    if (!cc()) {
        charge(4);
        lwc1(F0, sp, hi);
        c_le_s(F0, F2);
        if (cc()) return true;
    }
    charge(3);
    c_le_s(F1, F2);
    if (!cc()) return false;
    charge(4);
    lwc1(F0, sp, hi);
    c_lt_s(F0, F2);
    return !cc();
}
// sub_2A3E80's "show": the unit's flag 2 set (sub_27F790), with `also4` its flag 4 cleared (sub_27F770); unless flag
// 0x10 was asked (s0) the unit's +55 byte becomes 255.
void Cpu::show_unit_2A3E80(u32 link2, u32 link4, bool also4) {
    a0 = s1;
    a1 = li(2);
    jal(link2, rg::fn_sub_27F790_0027f790);
    if (also4) {
        a0 = s1;
        a1 = li(4);
        jal(link4, rg::fn_sub_27F770_0027f770);
    }
}

// 0x2A3E80 sub_2A3E80(subject, eye, at, flags; $f12 distance): which units the camera shows. Nothing while gBtl+16
// bit 2 is set. For every combatant btlAction (the list gBtl+332 along +1192, +26 bit 0) whose unit has +156 bit 3:
//   flags 0x40: shown (sub_27F790(unit, 2)); else the current actor (gBtl+328) with flags 0x04, the subject itself with
//   0x01, one of the subject's targets with 0x02: shown and its flag 4 cleared (sub_27F770(unit, 4)); a unit on the
//   subject's side with 0x08: shown. Each "shown" also sets the unit's +55 byte to 255 unless flags has 0x10.
//   Otherwise (and when the subject's targets were checked without a match) the unit is hidden (sub_27F770(unit, 2);
//   +55 = 0 unless flags 0x20; flag 4 set with 0x80 (sub_27F790(unit, 4))) when it stands closer to the line eye -> at
//   than `distance`: with both points given, its position (sub_27FFB0) on the x/z plane must lie inside the span of the
//   two points (sub_2D1FD0 gives the span and the distance in $f0), and the distance minus the unit's +144 * +44
//   must be <= $f12; without them `distance` is 0.
void Cpu::sub_2A3E80() {
    enter(21);
    sp = addiu(sp, -304);
    sd(ra, sp, 160);
    sq(s8, sp, 144);
    sq(s7, sp, 128);
    sq(s6, sp, 112);
    sq(s5, sp, 96);
    sq(s4, sp, 80);
    sq(s3, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F20, sp, 0);
    s4 = a0;
    s3 = a1;
    s5 = a2;
    mov_s(F20, F12);
    gbtl(a0);
    lw(v1, a0, btl_task::kFlags2);
    v1 = v1 & 0x4;
    if (v1 != 0) return epilogue_2A3E80();
    // the two points on the x/z plane at sp+256 / sp+264 (no points: distance 0)
    bool points = false;
    charge(2);
    if (s3 != 0) {
        charge(2);
        points = s5 != 0;
    }
    if (points) {
        charge(10);
        lwc1(F0, s3, 0);
        swc1(F0, sp, 256);
        lwc1(F0, s3, 8);
        swc1(F0, sp, 260);
        lwc1(F0, s5, 0);
        swc1(F0, sp, 264);
        lwc1(F0, s5, 8);
        swc1(F0, sp, 268);
    } else {
        charge(1);
        mtc1(zero, F20);
    }
    charge(17);
    lw(s2, a0, btl_task::kActionList);
    a0 = a3 & 0xffff;
    s7 = a0 & 0x40;
    s0 = a0 & 0x10;
    s8 = a0 & 0x4;
    // the other flag bits in 128-bit frame slots (whole registers, as compiled)
    v1 = a0 & 0x1;
    sq(v1, sp, 240);
    v1 = a0 & 0x2;
    sq(v1, sp, 224);
    v1 = a0 & 0x8;
    sq(v1, sp, 208);
    v1 = a0 & 0x20;
    sq(v1, sp, 192);
    v1 = a0 & 0x80;
    sq(v1, sp, 176);
    for (;;) {
        charge(2);
        if (s2 == 0) break;
        backedge();
        unit_pass_2A3E80();
        charge(1);
        lw(s2, s2, kAcNextInList);
    }
    epilogue_2A3E80();
}
// One btlAction (s2) of sub_2A3E80's pass; returns where the original goes on to the next action.
void Cpu::unit_pass_2A3E80() {
    // "shown" with the +55 byte unless flag 0x10
    const auto alpha = [this] {
        if (s0 != 0) return;
        charge(4);
        v1 = li(255);
        sb(v1, s1, 55);
    };
    charge(4);
    lhu(v1, s2, btl_task::kActFlags2);
    v1 = v1 & 0x1;
    if (v1 == 0) return;
    charge(5);
    lw(s1, s2, btl_task::kActUnit);
    lw(v1, s1, btl_task::kUnitFlags);
    v1 = v1 & 0x8;
    if (v1 == 0) return;
    charge(2);
    if (s7 != 0) {
        charge(6);
        show_unit_2A3E80(0x2a3f88, 0, false);
        return alpha();
    }
    charge(4);
    gbtl(v1);
    lw(v1, v1, btl_task::kCurrentAction);
    if (s2 == v1) {
        charge(2);
        if (s8 != 0) {
            charge(10);
            show_unit_2A3E80(0x2a3fc8, 0x2a3fd8, true);
            return alpha();
        }
    }
    charge(2);
    if (s4 != 0) {
        charge(2);
        if (s2 == s4) {
            charge(3);
            lq(v1, sp, 240);
            if (v1 != 0) {
                charge(10);
                show_unit_2A3E80(0x2a401c, 0x2a402c, true);
                return alpha();
            }
        }
        charge(3);
        lq(v1, sp, 224);
        if (v1 != 0) {
            // one of the subject's targets?
            charge(4);
            a1 = 0;
            lhu(a0, s4, kActTargetCount);
            for (;;) {
                charge(4);
                s6 = a1 & 0xffff;
                v1 = slt(s6, a0);
                if (v1 == 0) break;
                backedge();
                charge(6);
                v1 = a1 & 0xffff;
                v1 = sll(v1, 2);
                v1 = addu(s4, v1);
                lw(v1, v1, kActTargets);
                if (s2 == v1) {
                    charge(10);
                    show_unit_2A3E80(0x2a4088, 0x2a4098, true);
                    alpha();
                    break;
                }
                charge(2);
                v1 = addiu(a1, 1);
                a1 = v1 & 0xffff;
            }
            charge(3);
            lhu(v1, s4, kActTargetCount);
            if (s6 != v1) return;  // (a target: done, whatever the loop left)
        }
        charge(5);
        lbu(a0, s1, btl_task::kUnitSide);
        lw(v1, s4, btl_task::kActUnit);
        lbu(v1, v1, btl_task::kUnitSide);
        if (a0 == v1) {
            charge(3);
            lq(v1, sp, 208);
            if (v1 != 0) {
                charge(6);
                show_unit_2A3E80(0x2a4104, 0, false);
                return alpha();
            }
        }
    }
    // hidden when close to the line between the points
    charge(2);
    bool points = false;
    if (s3 != 0) {
        charge(2);
        points = s5 != 0;
    }
    if (points) {
        charge(25);
        a0 = s1;
        a1 = addiu(sp, 288);
        jal(0x2a413c, rg::fn_sub_27FFB0_0027ffb0);
        lwc1(F0, sp, 288);
        swc1(F0, sp, 272);
        lwc1(F0, sp, 296);
        swc1(F0, sp, 276);
        a0 = addiu(sp, 256);
        a1 = addiu(sp, 264);
        a2 = addiu(sp, 272);
        a3 = addiu(sp, 280);
        jal(0x2a4164, rg::fn_sub_2D1FD0_002d1fd0);
        // $f3 = the distance ($f0) - the unit's +144 * +44
        lwc1(F3, s1, kUnSize);
        lwc1(F2, s1, kUnScale);
        mtc1(zero, F1);
        adda_s(F1, F0);
        msub_s(F3, F3, F2);
        if (!in_span_2A3E80(256, 264, 280)) return;
        charge(5);
        if (!in_span_2A3E80(260, 268, 284)) {
            charge(2);
            return;
        }
    } else {
        charge(1);
        mtc1(zero, F3);
    }
    charge(3);
    c_le_s(F3, F20);
    if (!cc()) return;
    charge(7);
    a0 = s1;
    a1 = li(2);
    jal(0x2a4224, rg::fn_sub_27F770_0027f770);
    lq(v1, sp, 192);
    if (v1 == 0) {
        charge(1);
        sb(zero, s1, 55);
    }
    charge(3);
    lq(v1, sp, 176);
    if (v1 != 0) {
        charge(4);
        a0 = s1;
        a1 = li(4);
        jal(0x2a4250, rg::fn_sub_27F790_0027f790);
    }
}
void Cpu::epilogue_2A3E80() {
    charge(14);
    ld(ra, sp, 160);
    lq(s8, sp, 144);
    lq(s7, sp, 128);
    lq(s6, sp, 112);
    lq(s5, sp, 96);
    lq(s4, sp, 80);
    lq(s3, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 304);
}

// 0x2A42A0 sub_2A42A0(): every unit of both sides' lists (gBtl+336 + 8 * side, along +2612) gets its flag 7 set
// (sub_27F790(unit, 7)): hidden before a camera switch.
void Cpu::sub_2A42A0() {
    enter(7);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s0 = 0;
    for (;;) {
        charge(4);
        v1 = s0 & 0xffff;
        v1 = slti(v1, 2);
        if (v1 == 0) break;
        backedge();
        charge(7);
        v1 = s0 & 0xffff;
        a0 = sll(v1, 3);
        gbtl(v1);
        v1 = addu(v1, a0);
        lw(s1, v1, kSideListB);
        for (;;) {
            charge(3);
            if (s1 == 0) break;
            backedge();
            charge(5);
            a0 = s1;
            a1 = li(7);
            jal(0x2a42e0, rg::fn_sub_27F790_0027f790);
            lw(s1, s1, kUnitNextB);
        }
        charge(2);
        v1 = addiu(s0, 1);
        s0 = v1 & 0xffff;
    }
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// 0x2A4330 sub_2A4330(): the near-camera fade: for every unit with +156 bit 3 in both sides' lists, the distance from
// the main camera's position (sub_198590()->+4 frame, its matrix +16 position +48) to the unit (sub_27FFB0, length by
// sub_4C6AC0): within 200 + the unit's +144 * +44 its flag 1 is cleared (sub_27F770(unit, 1)), else set
// (sub_27F790(unit, 1)).
void Cpu::sub_2A4330() {
    enter(12);
    sp = addiu(sp, -96);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    jal(0x2a4344, rg::fn_sub_198590_00198590);
    lw(v1, v0, 4);
    s0 = addiu(v1, 16);
    s1 = 0;
    for (;;) {
        charge(4);
        v1 = s1 & 0xffff;
        v1 = slti(v1, 2);
        if (v1 == 0) break;
        backedge();
        charge(7);
        v1 = s1 & 0xffff;
        a0 = sll(v1, 3);
        gbtl(v1);
        v1 = addu(v1, a0);
        lw(s2, v1, kSideListB);
        for (;;) {
            charge(2);
            if (s2 == 0) break;
            backedge();
            charge(4);
            lw(v1, s2, btl_task::kUnitFlags);
            v1 = v1 & 0x8;
            if (v1 != 0) {
                charge(30);
                a0 = s2;
                a1 = addiu(sp, 80);
                jal(0x2a4394, rg::fn_sub_27FFB0_0027ffb0);
                for (int k = 0; k < 3; ++k) {
                    lwc1(F1, s0, 48 + 4 * k);
                    lwc1(F0, sp, 80 + 4 * k);
                    sub_s(F0, F1, F0);
                    swc1(F0, sp, 64 + 4 * k);
                }
                a0 = addiu(sp, 64);
                jal(0x2a43d0, rg::fn_sub_4C6AC0_004c6ac0);
                lwc1(F4, s2, kUnSize);
                lwc1(F3, s2, kUnScale);
                lif(v0, 0x4348, F2);  // 200.0
                mtc1(zero, F1);
                adda_s(F1, F2);
                madd_s(F1, F4, F3);
                c_le_s(F0, F1);
                if (cc()) {
                    charge(6);
                    a0 = s2;
                    a1 = li(1);
                    jal(0x2a440c, rg::fn_sub_27F770_0027f770);
                } else {
                    charge(4);
                    a0 = s2;
                    a1 = li(1);
                    jal(0x2a4424, rg::fn_sub_27F790_0027f790);
                }
            }
            charge(1);
            lw(s2, s2, kUnitNextB);
        }
        charge(2);
        v1 = addiu(s1, 1);
        s1 = v1 & 0xffff;
    }
    charge(7);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 96);
}

// 0x2A4470 / 0x2A44B0 / 0x2A44F0 sub_2A4470 / sub_2A44B0 / sub_2A44F0(dst, src): copy a camera key (position f32[3]
// at +0, rotation quaternion f32[4] at +12). Three identical bodies.
void Cpu::copy_key() {
    enter(16);
    copy_vec3(a1, 0, a0, 0);
    copy_vec4(a1, 12, a0, 12);
}
void Cpu::sub_2A4470() { copy_key(); }
void Cpu::sub_2A44B0() { copy_key(); }
void Cpu::sub_2A44F0() { copy_key(); }

// 0x2A4530 sub_2A4530(out, at, eye, up): a look-at matrix: out+48 = eye, out+32 = forward = normalise(at - eye),
// out+0 = right = normalise(up x forward), out+16 = forward x right (sub_4C69F0 normalises in place; the cross
// products through ACC: mula / msub).
void Cpu::sub_2A4530() {
    enter(86);
    sp = addiu(sp, -96);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    s0 = a3;
    copy_vec3(a2, 0, a0, 48);
    for (int k = 0; k < 3; ++k) {
        lwc1(F1, a1, 4 * k);
        lwc1(F0, a2, 4 * k);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 80 + 4 * k);
    }
    a0 = addiu(sp, 80);
    a1 = a0;
    jal(0x2a4598, rg::fn_sub_4C69F0_004c69f0);
    copy_vec3(sp, 80, s1, 32);
    // right = up x forward
    lwc1(F6, sp, 84);
    lwc1(F5, sp, 88);
    lwc1(F4, s0, 8);
    lwc1(F3, s0, 4);
    mula_s(F3, F5);
    msub_s(F0, F4, F6);
    swc1(F0, sp, 64);
    lwc1(F2, sp, 80);
    lwc1(F1, s0, 0);
    mula_s(F4, F2);
    msub_s(F0, F1, F5);
    swc1(F0, sp, 68);
    mula_s(F1, F6);
    msub_s(F0, F3, F2);
    swc1(F0, sp, 72);
    a0 = addiu(sp, 64);
    a1 = a0;
    jal(0x2a45fc, rg::fn_sub_4C69F0_004c69f0);
    copy_vec3(sp, 64, s1, 0);
    // up' = forward x right
    lwc1(F6, sp, 68);
    lwc1(F5, sp, 88);
    lwc1(F4, sp, 72);
    lwc1(F3, sp, 84);
    mula_s(F3, F4);
    msub_s(F0, F5, F6);
    swc1(F0, sp, 48);
    lwc1(F2, sp, 80);
    lwc1(F1, sp, 64);
    mula_s(F5, F1);
    msub_s(F0, F2, F4);
    swc1(F0, sp, 52);
    mula_s(F2, F6);
    msub_s(F0, F3, F1);
    swc1(F0, sp, 56);
    copy_vec3(sp, 48, s1, 16);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 96);
}

// 0x2A4690 sub_2A4690(out quaternion, eye, at, up): the rotation of a camera at `eye` looking at `at`: the look-at
// matrix (sub_2A4530 into its frame at sp+32) converted to a quaternion (sub_4BDCB0(out, matrix)).
void Cpu::sub_2A4690() {
    enter(19);
    sp = addiu(sp, -96);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    v0 = a1;
    a0 = addiu(sp, 32);
    a1 = a2;
    a2 = v0;
    jal(0x2a46b0, rg::fn_sub_2A4530_002a4530);
    a0 = s0;
    a1 = addiu(sp, 32);
    jal(0x2a46c0, rg::fn_sub_4BDCB0_004bdcb0);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 96);
}

// 0x2A4C50 sub_2A4C50(): sets gBtl+244 bit 0.
void Cpu::sub_2A4C50() {
    enter(6);
    gbtl(a0);
    lw(v1, a0, kBtCamFlags);
    v1 = v1 | 0x1;
    sw(v1, a0, kBtCamFlags);
}

// =====================================================================================================================
}  // namespace p3fes::game::bcam

namespace p3fes::game {
#define P3FES_BCAM_API(name, addr) \
    void name(EEContext& ctx) { bcam::Cpu(ctx).name(); }
P3FES_BCAM_BODIES(P3FES_BCAM_API)
#undef P3FES_BCAM_API
}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------------
namespace p3fes::recomp_gen {
#define P3FES_BCAM_SHIM(name, addr) \
    void fn_##name##_##addr(p3fes::EEContext& ctx) { ::p3fes::game::bcam::Cpu(ctx).name(); }
P3FES_BCAM_BODIES(P3FES_BCAM_SHIM)
#undef P3FES_BCAM_SHIM
}  // namespace p3fes::recomp_gen
