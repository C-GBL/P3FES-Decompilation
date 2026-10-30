// The battle code, sixth pass (slice battle6; docs/ANALYSIS/21_battle.md, game/include/p3fes/game/battle6.h for the
// layouts): the battle core of 0x280000-0x28FFFF -- unit geometry and motion lengths, the per-frame unit update, the
// shake / hop / model packets and their callbacks, and the btlAction state updates START, ANALYZE, AUTO (with its
// init) and SUPPORT. The bodies are p3fes_handgen's (frame, spills, $ra links, every register, cycle charges, check
// points); this file names their offsets (battle3.h's b3::, battle4.h's b4::, battle5.h's b5:: records reused, this
// slice's in b6::) and gives each function its role -- proposed names in brackets (ADR-0009), symbols in code are
// functions.json's. Still-recompiled callees are reached through their gen:: entry points (the relaxed callee rule).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/battle6.h"

namespace p3fes::recomp_gen {
void fn_btlActionSetState_00299d60(p3fes::EEContext&);
void fn_datCalcClearEffect_00301540(p3fes::EEContext&);
void fn_datCalcGetHp_002ffd70(p3fes::EEContext&);
void fn_datCalcGetMaxHp_002ffdf0(p3fes::EEContext&);
void fn_datCalcGetMaxSp_00300100(p3fes::EEContext&);
void fn_datCalcGetSp_002ffd80(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_sub_1A0E50_001a0e50(p3fes::EEContext&);
void fn_sub_1FE270_001fe270(p3fes::EEContext&);
void fn_sub_1FE2E0_001fe2e0(p3fes::EEContext&);
void fn_sub_1FE350_001fe350(p3fes::EEContext&);
void fn_sub_1FE4A0_001fe4a0(p3fes::EEContext&);
void fn_sub_1FEB70_001feb70(p3fes::EEContext&);
void fn_sub_1FEBB0_001febb0(p3fes::EEContext&);
void fn_sub_1FF350_001ff350(p3fes::EEContext&);
void fn_sub_1FF370_001ff370(p3fes::EEContext&);
void fn_sub_27E470_0027e470(p3fes::EEContext&);
void fn_sub_27EC10_0027ec10(p3fes::EEContext&);
void fn_sub_27ED20_0027ed20(p3fes::EEContext&);
void fn_sub_280200_00280200(p3fes::EEContext&);
void fn_sub_280DA0_00280da0(p3fes::EEContext&);
void fn_sub_2826D0_002826d0(p3fes::EEContext&);
void fn_sub_283750_00283750(p3fes::EEContext&);
void fn_sub_284470_00284470(p3fes::EEContext&);
void fn_sub_284690_00284690(p3fes::EEContext&);
void fn_sub_284D10_00284d10(p3fes::EEContext&);
void fn_sub_284D60_00284d60(p3fes::EEContext&);
void fn_sub_284D80_00284d80(p3fes::EEContext&);
void fn_sub_285DE0_00285de0(p3fes::EEContext&);
void fn_sub_285E00_00285e00(p3fes::EEContext&);
void fn_sub_285E30_00285e30(p3fes::EEContext&);
void fn_sub_285E50_00285e50(p3fes::EEContext&);
void fn_sub_285EB0_00285eb0(p3fes::EEContext&);
void fn_sub_285ED0_00285ed0(p3fes::EEContext&);
void fn_sub_285F00_00285f00(p3fes::EEContext&);
void fn_sub_285F20_00285f20(p3fes::EEContext&);
void fn_sub_286380_00286380(p3fes::EEContext&);
void fn_sub_2863F0_002863f0(p3fes::EEContext&);
void fn_sub_286480_00286480(p3fes::EEContext&);
void fn_sub_2864A0_002864a0(p3fes::EEContext&);
void fn_sub_286540_00286540(p3fes::EEContext&);
void fn_sub_287490_00287490(p3fes::EEContext&);
void fn_sub_287510_00287510(p3fes::EEContext&);
void fn_sub_287580_00287580(p3fes::EEContext&);
void fn_sub_287740_00287740(p3fes::EEContext&);
void fn_sub_287860_00287860(p3fes::EEContext&);
void fn_sub_2878D0_002878d0(p3fes::EEContext&);
void fn_sub_287B20_00287b20(p3fes::EEContext&);
void fn_sub_287CF0_00287cf0(p3fes::EEContext&);
void fn_sub_289030_00289030(p3fes::EEContext&);
void fn_sub_28A780_0028a780(p3fes::EEContext&);
void fn_sub_28B230_0028b230(p3fes::EEContext&);
void fn_sub_28CA00_0028ca00(p3fes::EEContext&);
void fn_sub_28CF20_0028cf20(p3fes::EEContext&);
void fn_sub_28CF80_0028cf80(p3fes::EEContext&);
void fn_sub_28D080_0028d080(p3fes::EEContext&);
void fn_sub_29A1D0_0029a1d0(p3fes::EEContext&);
void fn_sub_29EE20_0029ee20(p3fes::EEContext&);
void fn_sub_2A3B40_002a3b40(p3fes::EEContext&);
void fn_sub_2B8D60_002b8d60(p3fes::EEContext&);
void fn_sub_2BAF90_002baf90(p3fes::EEContext&);
void fn_sub_2BB8F0_002bb8f0(p3fes::EEContext&);
void fn_sub_2BBD00_002bbd00(p3fes::EEContext&);
void fn_sub_2BBDC0_002bbdc0(p3fes::EEContext&);
void fn_sub_2BBDF0_002bbdf0(p3fes::EEContext&);
void fn_sub_2BBE00_002bbe00(p3fes::EEContext&);
void fn_sub_2BBF80_002bbf80(p3fes::EEContext&);
void fn_sub_2BBFA0_002bbfa0(p3fes::EEContext&);
void fn_sub_2BC0E0_002bc0e0(p3fes::EEContext&);
void fn_sub_2BD230_002bd230(p3fes::EEContext&);
void fn_sub_2BD480_002bd480(p3fes::EEContext&);
void fn_sub_2BD590_002bd590(p3fes::EEContext&);
void fn_sub_2BD850_002bd850(p3fes::EEContext&);
void fn_sub_2BDBD0_002bdbd0(p3fes::EEContext&);
void fn_sub_2BED10_002bed10(p3fes::EEContext&);
void fn_sub_2BFF60_002bff60(p3fes::EEContext&);
void fn_sub_2C0880_002c0880(p3fes::EEContext&);
void fn_sub_2C08A0_002c08a0(p3fes::EEContext&);
void fn_sub_2C0970_002c0970(p3fes::EEContext&);
void fn_sub_2D15A0_002d15a0(p3fes::EEContext&);
void fn_sub_2D1A70_002d1a70(p3fes::EEContext&);
void fn_sub_2D4040_002d4040(p3fes::EEContext&);
void fn_sub_2D5DC0_002d5dc0(p3fes::EEContext&);
void fn_sub_2D7E20_002d7e20(p3fes::EEContext&);
void fn_sub_2DB690_002db690(p3fes::EEContext&);
void fn_sub_2DB740_002db740(p3fes::EEContext&);
void fn_sub_2DBA80_002dba80(p3fes::EEContext&);
void fn_sub_2DBB00_002dbb00(p3fes::EEContext&);
void fn_sub_2DC070_002dc070(p3fes::EEContext&);
void fn_sub_2DD100_002dd100(p3fes::EEContext&);
void fn_sub_2DDBE0_002ddbe0(p3fes::EEContext&);
void fn_sub_2E2D00_002e2d00(p3fes::EEContext&);
void fn_sub_2E2D40_002e2d40(p3fes::EEContext&);
void fn_sub_2FB860_002fb860(p3fes::EEContext&);
void fn_sub_2FD520_002fd520(p3fes::EEContext&);
void fn_sub_302F50_00302f50(p3fes::EEContext&);
void fn_sub_308930_00308930(p3fes::EEContext&);
void fn_sub_317730_00317730(p3fes::EEContext&);
void fn_sub_318770_00318770(p3fes::EEContext&);
void fn_sub_318A30_00318a30(p3fes::EEContext&);
void fn_sub_318A70_00318a70(p3fes::EEContext&);
void fn_sub_318A90_00318a90(p3fes::EEContext&);
void fn_sub_318AD0_00318ad0(p3fes::EEContext&);
void fn_sub_31C7E0_0031c7e0(p3fes::EEContext&);
void fn_sub_31EBE0_0031ebe0(p3fes::EEContext&);
void fn_sub_358030_00358030(p3fes::EEContext&);
void fn_sub_4BE1E0_004be1e0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b3;  // the record offsets and $gp slots of battle3.h
using namespace b4;  // battle4.h's additions
using namespace b5;  // battle5.h's additions
using namespace b6;  // this slice's additions (battle6.h)

// 0x00280200 sub_280200 -- 196 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitPointFromS16] A point on a unit (a0) from a short vector (a1 = s16[3]): the vector times the unit's scale
// (+44) turned by the unit's rotation (+28, sub_4BE1E0) plus its position (+4), written to a2 (f32[3]).
// Arguments: a0 btlUnit, a1 s16[3], a2 out f32[3].
void sub_280200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00280200
    enter(ctx, 49);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    lh(v0, a1, 2);
    mtc1(v0, f0);
    cvt_s_w(f3, f0);
    lh(v0, a1, 4);
    mtc1(v0, f0);
    cvt_s_w(f2, f0);
    lh(v0, a1, 0);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    lwc1(f1, a0, unit::kScale);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x40);
    mul_s(f0, f3, f1);
    swc1(f0, sp, 0x44);
    mul_s(f0, f2, f1);
    swc1(f0, sp, 0x48);
    a0 = addiu(sp, 0x30);
    a1 = addiu(sp, 0x40);
    a2 = 1;
    a3 = addiu(s1, 28);
    jal(ctx, 0x280274u, gen::fn_sub_4BE1E0_004be1e0);
    lwc1(f1, s1, unit4::kPos);
    lwc1(f0, sp, 0x30);
    add_s(f0, f0, f1);
    swc1(f0, s0, 0);
    lwc1(f1, s1, unit4::kPos + 4);
    lwc1(f0, sp, 0x34);
    add_s(f0, f0, f1);
    swc1(f0, s0, 4);
    lwc1(f1, s1, unit4::kPos + 8);
    lwc1(f0, sp, 0x38);
    add_s(f0, f0, f1);
    swc1(f0, s0, 8);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00283750 sub_283750 -- 376 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [btlUnitMotionFrames] The length in frames of a unit's motion a1 at speed f12: the motion row index comes from the
// per-side table 0x693290 (26 bytes per side, by motion; side 1 asks sub_2FB860 first and falls back to the table
// when it answers -1, side 3+ uses row 0); an index beyond the unit's rows (+2520) gives 0, else the row's frames (+4
// of the 10-byte row at +2540; 0 when negative) / (f12 * row speed% (+2) / 100), truncated to s16.
// Arguments: a0 btlUnit, a1 motion, f12 speed.
void sub_283750(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00283750
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    s0 = a1;
    mov_s(f20, f12);
    lbu(v1, a0, unit::kSide);
    v0 = 2;
    bool from_table = true;  // the row index comes from the per-side table 0x693290
    if (v1 != v0) {
        // 0x00283780: side 0 uses the table too
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x00283788
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x0028379c: an enemy asks for its own row first (-1: the table)
                charge(ctx, 7);
                jal(ctx, 0x28379Cu, gen::fn_sub_2FB860_002fb860);
                v1 = dsll32(v0, 16);
                v1 = dsra32(v1, 16);
                v0 = si(-1);
                from_table = v1 == v0;
                if (!from_table) {
                    // 0x002837b8
                    charge(ctx, 2);
                }
            } else {
                // 0x00283794: side 3 and up: row 0
                charge(ctx, 2);
                // 0x00283800
                charge(ctx, 3);
                v1 = 0;
                from_table = false;
            }
        }
    }
    if (from_table) {
        // 0x002837c0: row = table[26 * side + motion]
        charge(ctx, 16);
        lbu(v1, s1, unit::kSide);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 1);
        v0 = 0x690000;
        v0 = addiu(v0, 12944);  // &0x693290
        v1 = addu(v0, v1);
        v0 = s0 & 0xFFFF;
        v0 = addu(v0, v1);
        lbu(v0, v0, 0);
        v0 = dsll32(v0, 16);
        v0 = dsra32(v0, 16);
        // 0x0028380c
        charge(ctx, 2);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
    }
    // 0x00283814: past the unit's rows -> 0, else frames / (speed * row speed% / 100)
    charge(ctx, 6);
    v1 = dsll32(v1, 16);
    v1 = dsra32(v1, 16);
    lhu(v0, s1, unit::kMotionCount);
    at = slt(v1, v0);
    if (at == 0) {
        // 0x002838a8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0028382c
        charge(ctx, 8);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 1);
        lw(v0, s1, unit::kMotionTbl);
        v0 = addu(v1, v0);
        lh(v1, v0, 4);
        if (i64(v1) >= 0) {
            // 0x00283858
            charge(ctx, 18);
            lh(v0, v0, 2);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42C80000;
            mtc1(v0, f0);
            div_s(f0, f1, f0);
            mul_s(f1, f20, f0);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            div_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
        } else {
            // 0x0028384c
            charge(ctx, 3);
            v0 = 0;
        }
        // 0x002838a0
        charge(ctx, 2);
    }
    // 0x002838ac (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00284470 sub_284470 -- 356 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPktShakeUpdate] Update callback of the unit shake packet (sub_2849A0 creates it; data {unit, f32 amplitude, u32
// count}): marks the unit changed; once the amplitude is 0.5 or less it zeroes the shake offset (+16), clears motion
// flag 1 and returns 1 (done); else the offset is the rotated shake axis (0x697870 through the unit's rotation) times
// amplitude * (0.5 + 0.5 * sub_358030(0)), its sign alternating with the count, the amplitude decays by *0x7CAE10,
// motion flag 1 is set, the count steps and it returns 0.
// Arguments: a0 the packet data.
void sub_284470(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x00284470
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, pshake::kUnit);
    lw(v0, s0, unit::kModelFlags);
    v0 = v0 | 0x4;
    sw(v0, s0, unit::kModelFlags);
    lwc1(f1, a0, pshake::kAmp);
    v0 = 0x3F000000;
    mtc1(v0, f0);
    c_le_s(f1, f0);
    if (cond(ctx)) {
        // 0x00284588
        charge(ctx, 9);
        sw(zero, s0, unit4::kShakeOff);
        sw(zero, s0, unit4::kShakeOff + 4);
        sw(zero, s0, unit4::kShakeOff + 8);
        lhu(v0, s0, unit5::kMotionFlags);
        v0 = v0 & 0xFFFE;
        sh(v0, s0, unit5::kMotionFlags);
        v0 = 1;
    } else {
        // 0x002844b0
        charge(ctx, 11);
        a0 = addiu(sp, 0x30);
        a1 = 0x690000;
        a1 = addiu(a1, 30832);  // &0x697870
        a2 = 1;
        a3 = addiu(s0, 28);
        jal(ctx, 0x2844C4u, gen::fn_sub_4BE1E0_004be1e0);
        lw(v0, s1, pshake::kCount);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x00284510
            charge(ctx, 12);
            a0 = 0;
            jal(ctx, 0x284514u, gen::fn_sub_358030_00358030);
            v0 = 0x3F000000;
            mtc1(v0, f2);
            mtc1(zero, f1);
            adda_s(f1, f2);
            madd_s(f1, f2, f0);
            lwc1(f0, s1, pshake::kAmp);
            neg_s(f0, f0);
            mul_s(f1, f0, f1);
        } else {
            // 0x002844dc
            charge(ctx, 13);
            a0 = 0;
            jal(ctx, 0x2844E0u, gen::fn_sub_358030_00358030);
            v0 = 0x3F000000;
            mtc1(v0, f2);
            mtc1(zero, f1);
            adda_s(f1, f2);
            madd_s(f1, f2, f0);
            lwc1(f0, s1, pshake::kAmp);
            mul_s(f1, f0, f1);
        }
        // 0x00284540
        charge(ctx, 18);
        lwc1(f0, sp, 0x30);
        mul_s(f0, f0, f1);
        swc1(f0, s0, unit4::kShakeOff);
        lwc1(f0, sp, 0x34);
        mul_s(f0, f0, f1);
        swc1(f0, s0, unit4::kShakeOff + 4);
        lwc1(f0, sp, 0x38);
        mul_s(f0, f0, f1);
        swc1(f0, s0, unit4::kShakeOff + 8);
        lwc1(f1, s1, pshake::kAmp);
        lwc1(f0, gp, -32480);  // 0x7CAE10
        mul_s(f0, f1, f0);
        swc1(f0, s1, pshake::kAmp);
        lhu(v0, s0, unit5::kMotionFlags);
        v0 = v0 | 0x1;
        sh(v0, s0, unit5::kMotionFlags);
        // 0x002845ac
        charge(ctx, 4);
        lw(v0, s1, pshake::kCount);
        v0 = addiu(v0, 1);
        sw(v0, s1, pshake::kCount);
        v0 = 0;
    }
    // 0x002845bc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00284690 sub_284690 -- 592 bytes; frame 0x60: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [btlPktHopUpdate] Update callback of the unit hop packet (data {f32 start[3], unit +12, u16 frames +16, u16 step
// +18, f32 t +20}): marks the unit changed; on step 0 notes the start point and t = 0.5; t advances by 1 / (2 *
// frames); the offset along the rotated axis 0x697870 is max(75, 1.25 * radius * scale) times the arc 2 * (4t(1-t)...
// - 0.5) and the packet ends (returns 1) once that factor reaches *0x7CAEA4; the position is start + offset unless
// the unit is pinned (flag 0x400); the step counts.
// Arguments: a0 the packet data.
void sub_284690(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f20{ctx, 20};
    // 0x00284690
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    lw(s0, a0, phop::kUnit);
    lw(v0, s0, unit::kModelFlags);
    v0 = v0 | 0x4;
    sw(v0, s0, unit::kModelFlags);
    lhu(v0, a0, phop::kStep);
    if (v0 == 0) {
        // 0x002846c4
        charge(ctx, 8);
        v0 = 0x3F000000;
        sw(v0, s1, phop::kT);
        lwc1(f2, s0, unit4::kPos);
        lwc1(f1, s0, unit4::kPos + 4);
        lwc1(f0, s0, unit4::kPos + 8);
        swc1(f2, s1, phop::kStart);
        swc1(f1, s1, phop::kStart + 4);
        swc1(f0, s1, phop::kStart + 8);
    }
    // 0x002846e4
    charge(ctx, 3);
    lhu(v0, s1, phop::kFrames);
    if (i64(v0) < 0) {
        // 0x00284704
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002846f0
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00284720
    charge(ctx, 49);
    v0 = 0x40000000;
    mtc1(v0, f5);
    mul_s(f1, f5, f0);
    v0 = 0x3F800000;
    mtc1(v0, f0);
    div_s(f1, f0, f1);
    lwc1(f0, s1, phop::kT);
    add_s(f4, f0, f1);
    swc1(f4, s1, phop::kT);
    v0 = 0x40800000;
    mtc1(v0, f3);
    v0 = lui(0xC000);
    mtc1(v0, f0);
    mul_s(f2, f0, f4);
    v0 = lui(0xBF80);
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madda_s(f2, f4);
    madd_s(f1, f3, f4);
    v0 = 0x3F000000;
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    mul_s(f20, f5, f0);
    a0 = addiu(sp, 0x40);
    a1 = 0x690000;
    a1 = addiu(a1, 30832);  // &0x697870
    a2 = 1;
    a3 = addiu(s0, 28);
    jal(ctx, 0x2847A8u, gen::fn_sub_4BE1E0_004be1e0);
    lwc1(f1, s0, unit::kRadius);
    lwc1(f0, s0, unit::kScale);
    mul_s(f1, f1, f0);
    v0 = 0x3FA00000;
    mtc1(v0, f0);
    mul_s(f1, f0, f1);
    v0 = 0x42960000;
    mtc1(v0, f0);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        // 0x002847e4
        charge(ctx, 1);
        mov_s(f1, f0);
    }
    // 0x002847e8
    charge(ctx, 4);
    lwc1(f0, gp, -32332);  // 0x7CAEA4
    c_lt_s(f20, f0);
    if (!cond(ctx)) {
        // 0x0028482c
        charge(ctx, 10);
        lwc1(f0, sp, 0x40);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x40);
        lwc1(f0, sp, 0x44);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x44);
        lwc1(f0, sp, 0x48);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x48);
        v0 = 1;
    } else {
        // 0x002847f8
        charge(ctx, 13);
        mul_s(f1, f1, f20);
        lwc1(f0, sp, 0x40);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x40);
        lwc1(f0, sp, 0x44);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x44);
        lwc1(f0, sp, 0x48);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x48);
        v0 = 0;
    }
    // 0x00284854
    charge(ctx, 4);
    lw(v1, s0, unit::kFlags);
    v1 = v1 & 0x400;
    if (v1 == 0) {
        // 0x00284864
        charge(ctx, 21);
        lwc1(f1, s1, phop::kStart);
        lwc1(f0, sp, 0x40);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0x50);
        lwc1(f1, s1, phop::kStart + 4);
        lwc1(f0, sp, 0x44);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0x54);
        lwc1(f1, s1, phop::kStart + 8);
        lwc1(f0, sp, 0x48);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0x58);
        lwc1(f2, sp, 0x50);
        lwc1(f1, sp, 0x54);
        lwc1(f0, sp, 0x58);
        swc1(f2, s0, unit4::kPos);
        swc1(f1, s0, unit4::kPos + 4);
        swc1(f0, s0, unit4::kPos + 8);
        lw(v1, s0, unit::kModelFlags);
        v1 = v1 | 0x4;
        sw(v1, s0, unit::kModelFlags);
    }
    // 0x002848b8 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    lhu(v1, s1, phop::kStep);
    v1 = addiu(v1, 1);
    sh(v1, s1, phop::kStep);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00284D10 sub_284D10 -- 80 bytes; frame 0x10: ra sp+0x0
// [btlPktModelResetUpdate] Update callback of packet kind 258 (sub_284D80): when the unit (data +0) has a model (flag
// 2) it calls sub_318770(model, 0); returns 1 (done at once).
// Arguments: a0 the packet data.
void sub_284D10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00284d10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lh(a1, a0, pdunit::kArg4);
    lw(v1, a0, pdunit::kUnit);
    lw(v0, v1, unit::kModelFlags);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x00284d30
        charge(ctx, 7);
        mtc1(a1, f0);
        cvt_s_w(f12, f0);
        lw(a0, v1, unit::kModel);
        a1 = 0;
        jal(ctx, 0x284D44u, gen::fn_sub_318770_00318770);
    }
    // 0x00284d4c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00284D60 sub_284D60 -- 24 bytes; leaf frame (no stack)
// [btlPktUnitRelease] End callback shared by the unit packets: releases the unit (data +0) -- its busy count (+160)
// minus one.
// Arguments: a0 the packet data.
void sub_284D60(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00284d60
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, pdunit::kUnit);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, unit::kBusy);
}

// 0x00284D80 sub_284D80 -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPktCreateModelReset] Creates packet kind 258 (8 data bytes) for unit a0 with the word a1 at data +4: init
// sub_284CF0, update btlPktModelResetUpdate, end btlPktUnitRelease. Returns the packet.
// Arguments: a0 btlUnit, a1 u16.
void sub_284D80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00284d80
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 258;
    a1 = 8;
    jal(ctx, 0x284DA0u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 19696);  // &sub_284CF0
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 19728);  // &sub_284D10
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 19808);  // &sub_284D60
    sw(v1, v0, pkt::kOnEnd);
    lw(v1, v0, pkt::kData);
    sw(s1, v1, 0);
    sh(s0, v1, 4);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00285DE0 sub_285DE0 -- 24 bytes; leaf frame (no stack)
// [btlPktUnitHold275] Init callback of packet kind 275: holds the unit (data +0): busy count (+160) plus one.
// Arguments: a0 the packet data.
void sub_285DE0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00285de0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, pdunit::kUnit);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, unit::kBusy);
}

// 0x00285E00 sub_285E00 -- 40 bytes; frame 0x10: ra sp+0x0
// [btlPktUnitCall275] Update callback of packet kind 275: sub_287490(unit); returns 1.
// Arguments: a0 the packet data.
void sub_285E00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00285e00
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, pdunit::kUnit);
    jal(ctx, 0x285E0Cu, gen::fn_sub_287490_00287490);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00285E30 sub_285E30 -- 24 bytes; leaf frame (no stack)
// [btlPktUnitRelease275] End callback of packet kind 275: busy count minus one.
// Arguments: a0 the packet data.
void sub_285E30(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00285e30
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, pdunit::kUnit);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, unit::kBusy);
}

// 0x00285E50 sub_285E50 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlPktCreate275] Creates packet kind 275 (4 data bytes: the unit a0) with the callbacks 0x285DE0 / 0x285E00 /
// 0x285E30; the boss handlers sub_2EABF0 / sub_2EB2C0 use it.
// Arguments: a0 btlUnit.
void sub_285E50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00285e50
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 275;
    a1 = 4;
    jal(ctx, 0x285E68u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 24032);  // &sub_285DE0
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 24064);  // &sub_285E00
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 24112);  // &sub_285E30
    sw(v1, v0, pkt::kOnEnd);
    lw(v1, v0, pkt::kData);
    sw(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00285EB0 sub_285EB0 -- 24 bytes; leaf frame (no stack)
// [btlPktUnitHold276] Init callback of packet kind 276: holds the unit (busy count plus one).
// Arguments: a0 the packet data.
void sub_285EB0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00285eb0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, pdunit::kUnit);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, unit::kBusy);
}

// 0x00285ED0 sub_285ED0 -- 40 bytes; frame 0x10: ra sp+0x0
// [btlPktUnitCall276] Update callback of packet kind 276: sub_287510(unit); returns 1.
// Arguments: a0 the packet data.
void sub_285ED0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00285ed0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, pdunit::kUnit);
    jal(ctx, 0x285EDCu, gen::fn_sub_287510_00287510);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00285F00 sub_285F00 -- 24 bytes; leaf frame (no stack)
// [btlPktUnitRelease276] End callback of packet kind 276: busy count minus one.
// Arguments: a0 the packet data.
void sub_285F00(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00285f00
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, pdunit::kUnit);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, unit::kBusy);
}

// 0x00285F20 sub_285F20 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlPktCreate276] Creates packet kind 276 (the unit a0) with the callbacks 0x285EB0 / 0x285ED0 / 0x285F00
// (sub_2EABF0 / sub_2EB2C0).
// Arguments: a0 btlUnit.
void sub_285F20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00285f20
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 276;
    a1 = 4;
    jal(ctx, 0x285F38u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 24240);  // &sub_285EB0
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 24272);  // &sub_285ED0
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 24320);  // &sub_285F00
    sw(v1, v0, pkt::kOnEnd);
    lw(v1, v0, pkt::kData);
    sw(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00286380 sub_286380 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlPktModelFxInit] Init callback of the model effect packet (kind 273): holds the unit; unless the data flags have
// 0x10 it starts the model's effect (sub_31C7E0) when the model's effect slot (+1016) is free, and marks it started
// (data +12 = 1).
// Arguments: a0 the packet data.
void sub_286380(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00286380
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a1, a0, pdunit::kUnit);
    lhu(v1, a1, unit::kBusy);
    v1 = addiu(v1, 1);
    sh(v1, a1, unit::kBusy);
    lhu(v1, a0, pdunit::kFlags);
    v1 = v1 & 0x10;
    if (v1 == 0) {
        // 0x002863b0
        charge(ctx, 4);
        lw(a0, a1, unit::kModel);
        lw(v1, a0, mdl6::kFxSlot);
        if (v1 == 0) {
            // 0x002863c0
            charge(ctx, 2);
            jal(ctx, 0x2863C0u, gen::fn_sub_31C7E0_0031c7e0);
        }
        // 0x002863c8
        charge(ctx, 2);
        v1 = 1;
        sw(v1, s0, pdunit::kStarted);
    }
    // 0x002863d0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002863F0 sub_2863F0 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlPktModelFxUpdate] Update callback of the model effect packet: starts the effect on the first update if the init
// did not (returns 0), then returns 1 once the model's effect (+1016) finished (sub_31EBE0), else 0.
// Arguments: a0 the packet data.
void sub_2863F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002863f0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, pdunit::kUnit);
    lw(v0, a0, pdunit::kStarted);
    bool running;  // the result is 0 (the packet goes on)
    if (v0 == 0) {
        // 0x00286410: not started yet -- start the model's effect when its slot is free
        charge(ctx, 4);
        lw(a0, v1, unit::kModel);
        lw(v0, a0, mdl6::kFxSlot);
        if (v0 == 0) {
            // 0x00286420
            charge(ctx, 2);
            jal(ctx, 0x286420u, gen::fn_sub_31C7E0_0031c7e0);
        }
        // 0x00286428
        charge(ctx, 4);
        v0 = 1;
        sw(v0, s0, pdunit::kStarted);
        running = true;
    } else {
        // 0x00286438: started -- has the model's effect finished?
        charge(ctx, 6);
        lw(v0, v1, unit::kModel);
        a0 = addiu(v0, mdl6::kFxSlot);
        jal(ctx, 0x286440u, gen::fn_sub_31EBE0_0031ebe0);
        running = v0 == 0;
    }
    if (running) {
        // 0x0028645c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00286450
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00286460 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00286480 sub_286480 -- 24 bytes; leaf frame (no stack)
// [btlPktModelFxEnd] End callback of the model effect packet: busy count minus one.
// Arguments: a0 the packet data.
void sub_286480(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00286480
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, pdunit::kUnit);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, unit::kBusy);
}

// 0x002864A0 sub_2864A0 -- 156 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPktCreateModelFx] Creates the model effect packet (kind 273, 16 data bytes) for unit a0: clears the packet's
// byte +71 bit 1, callbacks btlPktModelFxInit / Update / End; data {unit, u16 side + 1, u16 a1, u16 a2, started 0};
// the REINFORCE / SUMMON updates (sub_294D40 / sub_295160) use it.
// Arguments: a0 btlUnit, a1 / a2 u16.
void sub_2864A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002864a0
    enter(ctx, 39);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 273;
    a1 = 16;
    jal(ctx, 0x2864C8u, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xFE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x280000;
    v1 = addiu(v1, 25472);  // &sub_286380
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 25584);  // &sub_2863F0
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 25728);  // &sub_286480
    sw(v1, v0, pkt::kOnEnd);
    lw(a0, v0, pkt::kData);
    sw(s2, a0, 0);
    sh(s0, a0, 8);
    lbu(v1, s2, unit::kSide);
    v1 = addiu(v1, 1);
    sh(v1, a0, 4);
    sh(s1, a0, 6);
    sw(zero, a0, 12);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00286540 sub_286540 -- 3772 bytes; frame 0xB0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitsUpdate] Per-frame update of every battle unit (btlUpdateTask), the four unit lists in turn: the walk /
// motion steps (sub_280DA0, sub_2826D0), a persona's instance (side 2, sub_1A0E50), the enemies' boss hook (side 1,
// sub_2FD520). For units with a model: sub_29EE20; the fade alpha (+55) steps 28 toward 255 while shown (not hidden,
// or flagged 4) and toward 0 otherwise; a colour fade (+76 frames, over 8 steps) moves +64..+66 from +72..+74 toward
// +68..+70. When something changed (flag 4): the model matrix from the rotation quaternion (+28), the scale (+44) and
// the position plus the shake offset (+4 / +16) (sub_318A70 / A90 / A30), the tint = the four RGBA bytes +48 * +52 *
// +60 * +64 (each 1/255, rounded) into +78..+81 (sub_318AD0); an opaque tint (alpha 254+) selects render mode 0x7381B
// and the model passes 2 / 5 (sub_287CF0), a blended one the transparent passes (sub_287B20, not for personas); the
// model's render mode (+232) and its five attachments' follow; sub_2D4040; flag 4 clears. Then the model's pending
// update (+216 bit 4, sub_317730) and the status aura (+2552): a new aura colour (sub_2BBFA0 vs sub_2BBDF0) starts an
// 8-step colour fade, then the aura gets the tint and is updated.
void sub_286540(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12};
    // 0x00286540: the four unit lists in turn (side s at gBtl +340 + 8 * s)
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = 0;
    for (;;) {
        // 0x002873cc
        charge(ctx, 3);
        v1 = sltiu(s3, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00286568: one side: its units along btlUnit +2608
        charge(ctx, 6);
        a0 = sll(s3, 3);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        v1 = addu(v1, a0);
        lw(s4, v1, 340);
        for (;;) {
            // 0x002873c0
            charge(ctx, 2);
            if (s4 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00286580: a unit: the walk and motion steps (sub_280DA0, sub_2826D0), then the side hooks
            charge(ctx, 9);
            a0 = s4;
            jal(ctx, 0x286584u, gen::fn_sub_280DA0_00280da0);
            a0 = s4;
            jal(ctx, 0x286590u, gen::fn_sub_2826D0_002826d0);
            v1 = 2;
            if (s3 == v1) {
                // 0x002865cc: side 2 (a persona) with a model and an instance handle: the instance update
                // (sub_1A0E50)
                charge(ctx, 4);
                lw(v1, s4, unit::kModelFlags);
                v1 = v1 & 0x2;
                if (v1 != 0) {
                    // 0x002865dc
                    charge(ctx, 3);
                    lhu(a0, s4, unit5::kInstHandle);
                    if (a0 != 0) {
                        // 0x002865e8
                        charge(ctx, 5);
                        lbu(v0, s4, unit::kPersonaPose);
                        v0 = v0 ^ 0x1;
                        a1 = sltiu(v0, 1);
                        jal(ctx, 0x2865F4u, gen::fn_sub_1A0E50_001a0e50);
                    }
                }
            } else {
                // 0x002865a4: side 1 (an enemy): the boss rules' per-unit hook (sub_2FD520)
                charge(ctx, 3);
                v1 = 1;
                if (s3 == v1) {
                    // 0x002865b8
                    charge(ctx, 5);
                    a0 = s4;
                    jal(ctx, 0x2865BCu, gen::fn_sub_2FD520_002fd520);
                } else {
                    // 0x002865b0
                    charge(ctx, 2);
                }
            }
            // 0x002865fc: only units with a model (flag 2) go on
            charge(ctx, 4);
            lw(v1, s4, unit::kModelFlags);
            v1 = v1 & 0x2;
            if (v1 != 0) {
                // 0x0028660c: sub_29EE20, then the fade alpha (+55): fade in while +0 has neither 0x1 nor 0x2 (or has
                // 0x4), out otherwise
                charge(ctx, 7);
                a0 = s4;
                jal(ctx, 0x286610u, gen::fn_sub_29EE20_0029ee20);
                lhu(a0, s4, unit6::kShowFlags);
                v1 = a0 & 0x3;
                if (v1 != 0) {
                    // 0x00286628
                    charge(ctx, 3);
                    v1 = a0 & 0x4;
                    if (v1 != 0) {
                        goto L_0028666c;
                    }
                    // 0x00286634
                    charge(ctx, 4);
                    lbu(v1, s4, unit6::kFadeAlpha);
                    at = slti(v1, 29);
                    if (at != 0) {
                        // 0x00286654
                        charge(ctx, 1);
                        sb(zero, s4, unit6::kFadeAlpha);
                    } else {
                        // 0x00286644
                        charge(ctx, 4);
                        v1 = addiu(v1, -28);
                        sb(v1, s4, unit6::kFadeAlpha);
                    }
                    // 0x00286658
                    charge(ctx, 5);
                    lw(v1, s4, unit::kModelFlags);
                    v1 = v1 | 0x4;
                    sw(v1, s4, unit::kModelFlags);
                    goto L_002866ac;
                }
            L_0028666c:
                charge(ctx, 4);
                lbu(v1, s4, unit6::kFadeAlpha);
                at = slti(v1, 255);
                if (at != 0) {
                    // 0x0028667c
                    charge(ctx, 3);
                    at = slti(v1, 227);
                    if (at == 0) {
                        // 0x00286698
                        charge(ctx, 2);
                        v1 = 255;
                        sb(v1, s4, unit6::kFadeAlpha);
                    } else {
                        // 0x00286688
                        charge(ctx, 4);
                        v1 = addiu(v1, 28);
                        sb(v1, s4, unit6::kFadeAlpha);
                    }
                    // 0x002866a0
                    charge(ctx, 3);
                    lw(v1, s4, unit::kModelFlags);
                    v1 = v1 | 0x4;
                    sw(v1, s4, unit::kModelFlags);
                }
            L_002866ac:
                charge(ctx, 3);
                lhu(v1, s4, unit6::kFadeSteps);
                if (i64(v1) > 0) {
                    // 0x002866b8
                    charge(ctx, 2);
                    if (i64(v1) < 0) {
                        // 0x002866d4
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f0);
                        cvt_s_w(f1, f0);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x002866c0
                        charge(ctx, 5);
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                    }
                    // 0x002866f0
                    charge(ctx, 17);
                    v1 = 0x41000000;
                    mtc1(v1, f0);
                    div_s(f2, f1, f0);
                    lbu(a1, s4, unit6::kFadeTo);
                    lbu(v1, s4, unit6::kFadeFrom);
                    v1 = subu(v1, a1);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    mul_s(f1, f2, f0);
                    v1 = 0x4F000000;
                    mtc1(v1, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x00286744
                        charge(ctx, 5);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(a0, f0);
                        v1 = lui(0x8000);
                        a0 = a0 | v1;
                    } else {
                        // 0x00286734
                        charge(ctx, 4);
                        cvt_w_s(f0, f1);
                        mfc1(a0, f0);
                    }
                    // 0x00286758
                    charge(ctx, 15);
                    v1 = addu(a1, a0);
                    sb(v1, s4, unit6::kFadeColour);
                    lbu(a1, s4, 73);
                    lbu(v1, s4, 69);
                    v1 = subu(v1, a1);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    mul_s(f1, f2, f0);
                    v1 = 0x4F000000;
                    mtc1(v1, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x002867a4
                        charge(ctx, 5);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(a0, f0);
                        v1 = lui(0x8000);
                        a0 = a0 | v1;
                    } else {
                        // 0x00286794
                        charge(ctx, 4);
                        cvt_w_s(f0, f1);
                        mfc1(a0, f0);
                    }
                    // 0x002867b8
                    charge(ctx, 15);
                    v1 = addu(a1, a0);
                    sb(v1, s4, 65);
                    lbu(a1, s4, 74);
                    lbu(v1, s4, 70);
                    v1 = subu(v1, a1);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    mul_s(f1, f2, f0);
                    v1 = 0x4F000000;
                    mtc1(v1, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x00286804
                        charge(ctx, 5);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(a0, f0);
                        v1 = lui(0x8000);
                        a0 = a0 | v1;
                    } else {
                        // 0x002867f4
                        charge(ctx, 4);
                        cvt_w_s(f0, f1);
                        mfc1(a0, f0);
                    }
                    // 0x00286818
                    charge(ctx, 8);
                    v1 = addu(a1, a0);
                    sb(v1, s4, 66);
                    lw(v1, s4, unit::kModelFlags);
                    v1 = v1 | 0x4;
                    sw(v1, s4, unit::kModelFlags);
                    lhu(v1, s4, unit6::kFadeSteps);
                    v1 = addiu(v1, -1);
                    sh(v1, s4, unit6::kFadeSteps);
                }
                // 0x00286838: something changed (flag 4)?
                charge(ctx, 4);
                lw(v1, s4, unit::kModelFlags);
                v1 = v1 & 0x4;
                if (v1 != 0) {
                    // 0x00286848: the model matrix: the rotation quaternion (+28..+40) as a 3x3 matrix (sub_318A70),
                    // the scale (+44, sub_318A90), the position plus the shake offset (sub_318A30); then the tint
                    // channels: +48 * +52 * +60 * +64 (1/255 each), back to 0..255 with rounding
                    charge(ctx, 96);
                    lwc1(f3, s4, unit4::kRot);
                    lwc1(f2, s4, unit4::kRot + 4);
                    lwc1(f1, s4, unit4::kRot + 8);
                    lwc1(f0, s4, unit4::kRot + 12);
                    mul_s(f12, f3, f3);
                    mul_s(f11, f2, f2);
                    mul_s(f10, f1, f1);
                    mul_s(f9, f2, f1);
                    mul_s(f8, f1, f3);
                    mul_s(f7, f3, f2);
                    mul_s(f6, f0, f3);
                    mul_s(f5, f0, f2);
                    mul_s(f4, f0, f1);
                    add_s(f0, f11, f10);
                    v0 = 0x40000000;
                    mtc1(v0, f3);
                    v0 = 0x3F800000;
                    mtc1(v0, f2);
                    mtc1(zero, f1);
                    adda_s(f1, f2);
                    msub_s(f0, f3, f0);
                    swc1(f0, sp, 0x60);
                    add_s(f0, f7, f4);
                    mul_s(f0, f3, f0);
                    swc1(f0, sp, 0x64);
                    sub_s(f0, f8, f5);
                    mul_s(f0, f3, f0);
                    swc1(f0, sp, 0x68);
                    sub_s(f0, f7, f4);
                    mul_s(f0, f3, f0);
                    swc1(f0, sp, 0x70);
                    add_s(f0, f12, f10);
                    adda_s(f1, f2);
                    msub_s(f0, f3, f0);
                    swc1(f0, sp, 0x74);
                    add_s(f0, f9, f6);
                    mul_s(f0, f3, f0);
                    swc1(f0, sp, 0x78);
                    add_s(f0, f8, f5);
                    mul_s(f0, f3, f0);
                    swc1(f0, sp, 0x80);
                    sub_s(f0, f9, f6);
                    mul_s(f0, f3, f0);
                    swc1(f0, sp, 0x84);
                    add_s(f0, f12, f11);
                    adda_s(f1, f2);
                    msub_s(f0, f3, f0);
                    swc1(f0, sp, 0x88);
                    sw(zero, sp, 0x90);
                    sw(zero, sp, 0x94);
                    sw(zero, sp, 0x98);
                    v0 = 3;
                    sw(v0, sp, 0x6C);
                    lw(a0, s4, unit::kModel);
                    a1 = addiu(sp, 0x60);
                    a2 = 0;
                    jal(ctx, 0x28692Cu, gen::fn_sub_318A70_00318a70);
                    lwc1(f0, s4, unit::kScale);
                    swc1(f0, sp, 0xA8);
                    swc1(f0, sp, 0xA4);
                    swc1(f0, sp, 0xA0);
                    lw(a0, s4, unit::kModel);
                    a1 = addiu(sp, 0xA0);
                    a2 = 2;
                    jal(ctx, 0x286950u, gen::fn_sub_318A90_00318a90);
                    lwc1(f1, s4, unit4::kPos);
                    lwc1(f0, s4, unit4::kShakeOff);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0xA0);
                    lwc1(f1, s4, unit4::kPos + 4);
                    lwc1(f0, s4, unit4::kShakeOff + 4);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0xA4);
                    lwc1(f1, s4, unit4::kPos + 8);
                    lwc1(f0, s4, unit4::kShakeOff + 8);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0xA8);
                    lw(a0, s4, unit::kModel);
                    a1 = addiu(sp, 0xA0);
                    a2 = 2;
                    jal(ctx, 0x286994u, gen::fn_sub_318A30_00318a30);
                    lbu(a1, s4, unit::kColour);
                    lbu(a0, s4, unit::kColour + 1);
                    lbu(v1, s4, unit::kColour + 2);
                    lbu(v0, s4, unit::kColour + 3);
                    sb(a1, sp, 0xAC);
                    sb(a0, sp, 0xAD);
                    sb(v1, sp, 0xAE);
                    sb(v0, sp, 0xAF);
                    lbu(v0, s4, 53);
                    if (i64(v0) < 0) {
                        // 0x002869dc
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x002869c8
                        charge(ctx, 5);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                    }
                    // 0x002869f8
                    charge(ctx, 5);
                    lwc1(f0, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f2, f0, f1);
                    lbu(v0, sp, 0xAD);
                    if (i64(v0) < 0) {
                        // 0x00286a20
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00286a0c
                        charge(ctx, 5);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                    }
                    // 0x00286a3c
                    charge(ctx, 6);
                    lwc1(f0, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f0, f0, f1);
                    mul_s(f0, f0, f2);
                    lbu(v0, s4, 54);
                    if (i64(v0) < 0) {
                        // 0x00286a68
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00286a54
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x00286a84
                    charge(ctx, 5);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f3, f1, f2);
                    lbu(v0, sp, 0xAE);
                    if (i64(v0) < 0) {
                        // 0x00286aac
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00286a98
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x00286ac8
                    charge(ctx, 6);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f1, f1, f2);
                    mul_s(f6, f1, f3);
                    lbu(v0, s4, unit6::kFadeAlpha);
                    if (i64(v0) < 0) {
                        // 0x00286af4
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00286ae0
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x00286b10
                    charge(ctx, 5);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f3, f1, f2);
                    lbu(v0, sp, 0xAF);
                    if (i64(v0) < 0) {
                        // 0x00286b38
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00286b24
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x00286b54
                    charge(ctx, 6);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f1, f1, f2);
                    mul_s(f5, f1, f3);
                    lbu(v0, s4, unit6::kColour2);
                    if (i64(v0) < 0) {
                        // 0x00286b80
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00286b6c
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x00286b9c
                    charge(ctx, 5);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f3, f1, f2);
                    lbu(v0, sp, 0xAC);
                    if (i64(v0) < 0) {
                        // 0x00286bc4
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00286bb0
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x00286be0
                    charge(ctx, 36);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f1, f1, f2);
                    mul_s(f1, f1, f3);
                    v0 = 0x437F0000;
                    mtc1(v0, f4);
                    v0 = 0x3F000000;
                    mtc1(v0, f3);
                    mtc1(zero, f2);
                    adda_s(f2, f3);
                    madd_s(f1, f4, f1);
                    cvt_w_s(f1, f1);
                    mfc1(v0, f1);
                    sb(v0, sp, 0xAC);
                    adda_s(f2, f3);
                    madd_s(f0, f4, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                    sb(v0, sp, 0xAD);
                    adda_s(f2, f3);
                    madd_s(f0, f4, f6);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                    sb(v0, sp, 0xAE);
                    adda_s(f2, f3);
                    madd_s(f0, f4, f5);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                    sb(v0, sp, 0xAF);
                    lbu(v0, s4, 61);
                    if (i64(v0) < 0) {
                        // 0x00286c84
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00286c70
                        charge(ctx, 5);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                    }
                    // 0x00286ca0
                    charge(ctx, 5);
                    lwc1(f0, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f2, f0, f1);
                    lbu(v0, sp, 0xAD);
                    if (i64(v0) < 0) {
                        // 0x00286cc8
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00286cb4
                        charge(ctx, 5);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                    }
                    // 0x00286ce4
                    charge(ctx, 6);
                    lwc1(f0, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f0, f0, f1);
                    mul_s(f0, f0, f2);
                    lbu(v0, s4, 62);
                    if (i64(v0) < 0) {
                        // 0x00286d10
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00286cfc
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x00286d2c
                    charge(ctx, 5);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f3, f1, f2);
                    lbu(v0, sp, 0xAE);
                    if (i64(v0) < 0) {
                        // 0x00286d54
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00286d40
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x00286d70
                    charge(ctx, 6);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f1, f1, f2);
                    mul_s(f6, f1, f3);
                    lbu(v0, s4, 63);
                    if (i64(v0) < 0) {
                        // 0x00286d9c
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00286d88
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x00286db8
                    charge(ctx, 5);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f3, f1, f2);
                    lbu(v0, sp, 0xAF);
                    if (i64(v0) < 0) {
                        // 0x00286de0
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00286dcc
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x00286dfc
                    charge(ctx, 6);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f1, f1, f2);
                    mul_s(f5, f1, f3);
                    lbu(v0, s4, unit6::kColour3);
                    if (i64(v0) < 0) {
                        // 0x00286e28
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00286e14
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x00286e44
                    charge(ctx, 5);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f3, f1, f2);
                    lbu(v0, sp, 0xAC);
                    if (i64(v0) < 0) {
                        // 0x00286e6c
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00286e58
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x00286e88
                    charge(ctx, 36);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f1, f1, f2);
                    mul_s(f1, f1, f3);
                    v0 = 0x437F0000;
                    mtc1(v0, f4);
                    v0 = 0x3F000000;
                    mtc1(v0, f3);
                    mtc1(zero, f2);
                    adda_s(f2, f3);
                    madd_s(f1, f4, f1);
                    cvt_w_s(f1, f1);
                    mfc1(v0, f1);
                    sb(v0, sp, 0xAC);
                    adda_s(f2, f3);
                    madd_s(f0, f4, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                    sb(v0, sp, 0xAD);
                    adda_s(f2, f3);
                    madd_s(f0, f4, f6);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                    sb(v0, sp, 0xAE);
                    adda_s(f2, f3);
                    madd_s(f0, f4, f5);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                    sb(v0, sp, 0xAF);
                    lbu(v0, s4, 65);
                    if (i64(v0) < 0) {
                        // 0x00286f2c
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00286f18
                        charge(ctx, 5);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                    }
                    // 0x00286f48
                    charge(ctx, 5);
                    lwc1(f0, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f2, f0, f1);
                    lbu(v0, sp, 0xAD);
                    if (i64(v0) < 0) {
                        // 0x00286f70
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00286f5c
                        charge(ctx, 5);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                    }
                    // 0x00286f8c
                    charge(ctx, 6);
                    lwc1(f0, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f0, f0, f1);
                    mul_s(f0, f0, f2);
                    lbu(v0, s4, 66);
                    if (i64(v0) < 0) {
                        // 0x00286fb8
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00286fa4
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x00286fd4
                    charge(ctx, 5);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f3, f1, f2);
                    lbu(v0, sp, 0xAE);
                    if (i64(v0) < 0) {
                        // 0x00286ffc
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00286fe8
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x00287018
                    charge(ctx, 6);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f1, f1, f2);
                    mul_s(f6, f1, f3);
                    lbu(v0, s4, 67);
                    if (i64(v0) < 0) {
                        // 0x00287044
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00287030
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x00287060
                    charge(ctx, 5);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f3, f1, f2);
                    lbu(v0, sp, 0xAF);
                    if (i64(v0) < 0) {
                        // 0x00287088
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00287074
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x002870a4
                    charge(ctx, 6);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f1, f1, f2);
                    mul_s(f5, f1, f3);
                    lbu(v0, s4, unit6::kFadeColour);
                    if (i64(v0) < 0) {
                        // 0x002870d0
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x002870bc
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x002870ec
                    charge(ctx, 5);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f3, f1, f2);
                    lbu(v0, sp, 0xAC);
                    if (i64(v0) < 0) {
                        // 0x00287114
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f1);
                        cvt_s_w(f2, f1);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x00287100
                        charge(ctx, 5);
                        mtc1(v0, f1);
                        cvt_s_w(f2, f1);
                    }
                    // 0x00287130
                    charge(ctx, 37);
                    lwc1(f1, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
                    mul_s(f1, f1, f2);
                    mul_s(f1, f1, f3);
                    v0 = 0x437F0000;
                    mtc1(v0, f4);
                    v0 = 0x3F000000;
                    mtc1(v0, f3);
                    mtc1(zero, f2);
                    adda_s(f2, f3);
                    madd_s(f1, f4, f1);
                    cvt_w_s(f1, f1);
                    mfc1(v0, f1);
                    sb(v0, sp, 0xAC);
                    adda_s(f2, f3);
                    madd_s(f0, f4, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                    sb(v0, sp, 0xAD);
                    adda_s(f2, f3);
                    madd_s(f0, f4, f6);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                    sb(v0, sp, 0xAE);
                    adda_s(f2, f3);
                    madd_s(f0, f4, f5);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                    sb(v0, sp, 0xAF);
                    lbu(v0, sp, 0xAF);
                    v0 = slti(v0, 254);
                    if (v0 != 0) {
                        // 0x002871fc: a blended tint (alpha < 254): the transparent passes (sub_287B20) except for a
                        // persona
                        charge(ctx, 3);
                        a1 = 2;
                        if (s3 != a1) {
                            // 0x00287208
                            charge(ctx, 9);
                            v0 = 0x70000;
                            s0 = v0 | 0x37FB;
                            a0 = s4;
                            jal(ctx, 0x287214u, gen::fn_sub_287B20_00287b20);
                            a0 = s4;
                            a1 = 5;
                            jal(ctx, 0x287224u, gen::fn_sub_287B20_00287b20);
                        }
                    } else {
                        // 0x002871c4: an opaque tint: alpha 255, the opaque render mode, the model passes 2 / 5
                        // (sub_287CF0)
                        charge(ctx, 14);
                        v0 = 255;
                        sb(v0, sp, 0xAF);
                        v0 = 0x70000;
                        s0 = v0 | 0x37FB;
                        a0 = s4;
                        a1 = 2;
                        jal(ctx, 0x2871DCu, gen::fn_sub_287CF0_00287cf0);
                        a0 = s4;
                        a1 = 5;
                        jal(ctx, 0x2871ECu, gen::fn_sub_287CF0_00287cf0);
                    }
                    // 0x0028722c: a new render mode goes to the model (+232) and its five attachments
                    charge(ctx, 5);
                    lw(v0, s4, unit::kModel);
                    v1 = addiu(v0, 232);
                    lw(v0, v0, mdl6::kRenderMode);
                    if (v0 != s0) {
                        // 0x00287240
                        charge(ctx, 4);
                        sw(s0, v1, 0);
                        a0 = 0;
                        for (;;) {
                            // 0x00287278
                            charge(ctx, 3);
                            v0 = sltiu(a0, 5);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00287250
                            charge(ctx, 8);
                            lw(v1, s4, unit::kModel);
                            v0 = sll(a0, 1);
                            v0 = addu(v0, a0);
                            v0 = sll(v0, 2);
                            v0 = addu(v1, v0);
                            lw(v0, v0, 952);
                            if (v0 != 0) {
                                // 0x00287270
                                charge(ctx, 1);
                                sw(s0, v0, 232);
                            }
                            // 0x00287274
                            charge(ctx, 1);
                            a0 = addiu(a0, 1);
                        }
                    }
                    // 0x00287284: store the tint (+78..+81) and give it to the model (sub_318AD0); sub_2D4040; flag 4
                    // clears
                    charge(ctx, 19);
                    a1 = addiu(sp, 0xAC);
                    lbu(a2, sp, 0xAC);
                    lbu(a0, sp, 0xAD);
                    lbu(v1, sp, 0xAE);
                    lbu(v0, sp, 0xAF);
                    sb(a2, s4, unit6::kTint);
                    sb(a0, s4, 79);
                    sb(v1, s4, 80);
                    sb(v0, s4, 81);
                    lw(a0, s4, unit::kModel);
                    jal(ctx, 0x2872ACu, gen::fn_sub_318AD0_00318ad0);
                    a0 = s4;
                    jal(ctx, 0x2872B8u, gen::fn_sub_2D4040_002d4040);
                    lw(a0, s4, unit::kModelFlags);
                    v1 = si(-5);
                    v1 = a0 & v1;
                    sw(v1, s4, unit::kModelFlags);
                }
                // 0x002872d0: the model's pending update (+216, sub_317730)
                charge(ctx, 5);
                lw(a0, s4, unit::kModel);
                lhu(v1, a0, mdl::kFlags);
                v1 = v1 & 0x4;
                if (v1 != 0) {
                    // 0x002872e4
                    charge(ctx, 2);
                    jal(ctx, 0x2872E4u, gen::fn_sub_317730_00317730);
                }
                // 0x002872ec: the status aura (+2552): a changed colour (sub_2BBFA0 vs sub_2BBDF0) starts an 8-step
                // colour fade; then the aura gets the tint and is updated
                charge(ctx, 3);
                lw(v1, s4, unit5::kFxHandleA);
                if (v1 != 0) {
                    // 0x002872f8
                    charge(ctx, 5);
                    a0 = s4;
                    jal(ctx, 0x2872FCu, gen::fn_sub_287580_00287580);
                    if (v0 != 0) {
                        // 0x0028730c
                        charge(ctx, 3);
                        lw(v0, s4, unit::kDat);
                        if (v0 != 0) {
                            // 0x00287318
                            charge(ctx, 15);
                            lw(v0, v0, dat::kStatus);
                            s2 = dsll32(v0, 12);
                            s2 = dsrl32(s2, 12);
                            a0 = s2;
                            jal(ctx, 0x287328u, gen::fn_sub_2BBFA0_002bbfa0);
                            s1 = dsll32(v0, 16);
                            s1 = dsra32(s1, 16);
                            lw(a0, s4, unit5::kFxHandleA);
                            jal(ctx, 0x28733Cu, gen::fn_sub_2BBDF0_002bbdf0);
                            v0 = dsll32(v0, 16);
                            v0 = dsra32(v0, 16);
                            if (s1 != v0) {
                                // 0x00287354
                                charge(ctx, 18);
                                a0 = s2;
                                a1 = addiu(s4, 72);
                                jal(ctx, 0x28735Cu, gen::fn_sub_2BC0E0_002bc0e0);
                                lbu(a1, s4, unit6::kFadeColour);
                                lbu(a0, s4, 65);
                                lbu(v1, s4, 66);
                                lbu(v0, s4, 67);
                                sb(a1, s4, unit6::kFadeFrom);
                                sb(a0, s4, 69);
                                sb(v1, s4, 70);
                                sb(v0, s4, 71);
                                v0 = 8;
                                sh(v0, s4, unit6::kFadeSteps);
                                lw(a0, s4, unit5::kFxHandleA);
                                a1 = s1;
                                jal(ctx, 0x287394u, gen::fn_sub_2BBDC0_002bbdc0);
                            }
                        }
                        // 0x0028739c
                        charge(ctx, 8);
                        lw(a0, s4, unit5::kFxHandleA);
                        lwr(a1, s4, 78);
                        lwl(a1, s4, 81);
                        jal(ctx, 0x2873A8u, gen::fn_sub_2BBF80_002bbf80);
                        lw(a0, s4, unit5::kFxHandleA);
                        jal(ctx, 0x2873B4u, gen::fn_sub_2BBE00_002bbe00);
                    }
                }
            }
            // 0x002873bc
            charge(ctx, 1);
            lw(s4, s4, unit::kNext);
        }
        // 0x002873c8
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x002873d8
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x00287860 sub_287860 -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlUnitReleaseAttachments] Releases what a unit (a0) carries before it is destroyed (sub_2879F0): sub_287740; with
// a child unit (+2560) sub_2878D0; the status aura (+2552) through sub_2BBD00 and the effect handle (+2556) through
// sub_2BB8F0, each cleared.
// Arguments: a0 btlUnit.
void sub_287860(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00287860
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x287870u, gen::fn_sub_287740_00287740);
    lw(a0, s0, unit5::kChild);
    if (a0 != 0) {
        // 0x00287884
        charge(ctx, 2);
        jal(ctx, 0x287884u, gen::fn_sub_2878D0_002878d0);
    }
    // 0x0028788c
    charge(ctx, 3);
    lw(a0, s0, unit5::kFxHandleA);
    if (a0 != 0) {
        // 0x00287898
        charge(ctx, 3);
        jal(ctx, 0x287898u, gen::fn_sub_2BBD00_002bbd00);
        sw(zero, s0, unit5::kFxHandleA);
    }
    // 0x002878a4
    charge(ctx, 3);
    lw(a0, s0, unit::kAura);
    if (a0 != 0) {
        // 0x002878b0
        charge(ctx, 3);
        jal(ctx, 0x2878B0u, gen::fn_sub_2BB8F0_002bb8f0);
        sw(zero, s0, unit::kAura);
    }
    // 0x002878bc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0028B230 sub_28B230 -- 1488 bytes; frame 0x80: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlActionUpdateStart] btlAction state START, update: unless the battle is over or an effect packet of the kinds
// 1792 / 1284 / 1286 / 769 / 260 still runs: with regeneration bits (+1156) left it plays the lowest one -- 0x1 / 0x2
// / 0x4 HP 2 / 4 / 6 % (skills 547..549, effect 47), 0x8 / 0x10 / 0x20 SP 3 / 5 / 7 (550..552, effect 48), 0x40 /
// 0x80 HP 8 % (607 / 608, effect 57) -- clears it and queues the skill name (sub_2BD590), the effect of gBtl
// +3108[effect], the sound (12, 2, 11; 10 for 607 / 608), the heal (sub_2D7E20) and the HP / SP gauges; with none
// left, as START's init: BAD (11) / START HOME (3) by the unit's status, SUPPORT (10) without one.
// Arguments: a0 btlAction.
void sub_28B230(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0028b230
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v1, gbtl::kFlags);
    v1 = 0x80000;
    v1 = a0 & v1;
    if (v1 == 0) {
        // 0x0028b268
        charge(ctx, 5);
        a0 = 1792;
        jal(ctx, 0x28B26Cu, gen::fn_sub_27E470_0027e470);
        if (v0 == 0) {
            // 0x0028b27c
            charge(ctx, 5);
            a0 = 1284;
            jal(ctx, 0x28B280u, gen::fn_sub_27E470_0027e470);
            if (v0 == 0) {
                // 0x0028b290
                charge(ctx, 5);
                a0 = 1286;
                jal(ctx, 0x28B294u, gen::fn_sub_27E470_0027e470);
                if (v0 == 0) {
                    // 0x0028b2a4
                    charge(ctx, 5);
                    a0 = 769;
                    jal(ctx, 0x28B2A8u, gen::fn_sub_27E470_0027e470);
                    if (v0 == 0) {
                        // 0x0028b2b8
                        charge(ctx, 5);
                        a0 = 260;
                        jal(ctx, 0x28B2BCu, gen::fn_sub_27E470_0027e470);
                        if (v0 == 0) {
                            // 0x0028b2cc
                            charge(ctx, 3);
                            lw(v0, s4, act::kAoaLeader);
                            if (v0 != 0) {
                                // 0x0028b2d8
                                charge(ctx, 22);
                                a0 = s4;
                                jal(ctx, 0x28B2DCu, gen::fn_sub_28A780_0028a780);
                                a0 = addiu(sp, 0x60);
                                jal(ctx, 0x28B2E8u, gen::fn_sub_2D5DC0_002d5dc0);
                                s3 = 0;
                                s2 = 0;
                                lw(v0, s4, act::kUnit);
                                lw(a0, v0, unit::kDat);
                                jal(ctx, 0x28B300u, gen::fn_datCalcGetMaxHp_002ffdf0);
                                s0 = v0 & 0xFFFF;
                                lw(v0, s4, act::kUnit);
                                lw(a0, v0, unit::kDat);
                                jal(ctx, 0x28B314u, gen::fn_datCalcGetMaxSp_00300100);
                                s1 = si(-1);
                                lw(v0, s4, act::kAoaLeader);
                                v1 = v0 & 0x1;
                                if (v1 == 0) {
                                    // 0x0028b378
                                    charge(ctx, 3);
                                    v1 = v0 & 0x2;
                                    if (v1 == 0) {
                                        // 0x0028b3cc
                                        charge(ctx, 3);
                                        v1 = v0 & 0x4;
                                        if (v1 == 0) {
                                            // 0x0028b420
                                            charge(ctx, 3);
                                            v1 = v0 & 0x8;
                                            if (v1 == 0) {
                                                // 0x0028b454
                                                charge(ctx, 3);
                                                v1 = v0 & 0x10;
                                                if (v1 == 0) {
                                                    // 0x0028b488
                                                    charge(ctx, 3);
                                                    v1 = v0 & 0x20;
                                                    if (v1 == 0) {
                                                        // 0x0028b4bc
                                                        charge(ctx, 3);
                                                        v1 = v0 & 0x40;
                                                        if (v1 == 0) {
                                                            // 0x0028b510
                                                            charge(ctx, 3);
                                                            v1 = v0 & 0x80;
                                                            if (v1 != 0) {
                                                                // 0x0028b51c
                                                                charge(ctx, 16);
                                                                s3 = 608;
                                                                s1 = 10;
                                                                s2 = 57;
                                                                a0 = s0 & 0xFFFF;
                                                                v1 = sll(a0, 2);
                                                                a0 = addu(v1, a0);
                                                                v1 = sll(a0, 2);
                                                                v1 = addu(a0, v1);
                                                                a0 = sll(v1, 2);
                                                                v1 = 1250;
                                                                div(a0, v1);
                                                                mflo(v1);
                                                                sw(v1, sp, 0x60);
                                                                v1 = si(-129);
                                                                v0 = v0 & v1;
                                                                sw(v0, s4, act::kAoaLeader);
                                                            }
                                                        } else {
                                                            // 0x0028b4c8
                                                            charge(ctx, 18);
                                                            s3 = 607;
                                                            s1 = 10;
                                                            s2 = 57;
                                                            a0 = s0 & 0xFFFF;
                                                            v1 = sll(a0, 2);
                                                            a0 = addu(v1, a0);
                                                            v1 = sll(a0, 2);
                                                            v1 = addu(a0, v1);
                                                            a0 = sll(v1, 2);
                                                            v1 = 1250;
                                                            div(a0, v1);
                                                            mflo(v1);
                                                            sw(v1, sp, 0x60);
                                                            v1 = si(-65);
                                                            v0 = v0 & v1;
                                                            sw(v0, s4, act::kAoaLeader);
                                                        }
                                                    } else {
                                                        // 0x0028b494
                                                        charge(ctx, 10);
                                                        s3 = 552;
                                                        s1 = 11;
                                                        s2 = 48;
                                                        v1 = 7;
                                                        sw(v1, sp, 0x64);
                                                        v1 = si(-33);
                                                        v0 = v0 & v1;
                                                        sw(v0, s4, act::kAoaLeader);
                                                    }
                                                } else {
                                                    // 0x0028b460
                                                    charge(ctx, 10);
                                                    s3 = 551;
                                                    s1 = 11;
                                                    s2 = 48;
                                                    v1 = 5;
                                                    sw(v1, sp, 0x64);
                                                    v1 = si(-17);
                                                    v0 = v0 & v1;
                                                    sw(v0, s4, act::kAoaLeader);
                                                }
                                            } else {
                                                // 0x0028b42c
                                                charge(ctx, 10);
                                                s3 = 550;
                                                s1 = 11;
                                                s2 = 48;
                                                v1 = 3;
                                                sw(v1, sp, 0x64);
                                                v1 = si(-9);
                                                v0 = v0 & v1;
                                                sw(v0, s4, act::kAoaLeader);
                                            }
                                        } else {
                                            // 0x0028b3d8
                                            charge(ctx, 18);
                                            s3 = 549;
                                            s1 = 11;
                                            s2 = 47;
                                            a0 = s0 & 0xFFFF;
                                            v1 = sll(a0, 2);
                                            a0 = addu(v1, a0);
                                            v1 = sll(a0, 2);
                                            v1 = addu(a0, v1);
                                            a0 = sll(v1, 2);
                                            v1 = 1666;
                                            div(a0, v1);
                                            mflo(v1);
                                            sw(v1, sp, 0x60);
                                            v1 = si(-5);
                                            v0 = v0 & v1;
                                            sw(v0, s4, act::kAoaLeader);
                                        }
                                    } else {
                                        // 0x0028b384
                                        charge(ctx, 18);
                                        s3 = 548;
                                        s1 = 11;
                                        s2 = 47;
                                        a0 = s0 & 0xFFFF;
                                        v1 = sll(a0, 2);
                                        a0 = addu(v1, a0);
                                        v1 = sll(a0, 2);
                                        v1 = addu(a0, v1);
                                        a0 = sll(v1, 2);
                                        v1 = 2500;
                                        div(a0, v1);
                                        mflo(v1);
                                        sw(v1, sp, 0x60);
                                        v1 = si(-3);
                                        v0 = v0 & v1;
                                        sw(v0, s4, act::kAoaLeader);
                                    }
                                } else {
                                    // 0x0028b330
                                    charge(ctx, 18);
                                    s3 = 547;
                                    s1 = 11;
                                    s2 = 47;
                                    a0 = s0 & 0xFFFF;
                                    v1 = sll(a0, 2);
                                    a0 = addu(v1, a0);
                                    v1 = sll(a0, 2);
                                    v1 = addu(a0, v1);
                                    a0 = sll(v1, 2);
                                    v1 = 5000;
                                    div(a0, v1);
                                    mflo(v1);
                                    sw(v1, sp, 0x60);
                                    v1 = si(-2);
                                    v0 = v0 & v1;
                                    sw(v0, s4, act::kAoaLeader);
                                }
                                // 0x0028b55c
                                charge(ctx, 3);
                                lw(v0, sp, 0x60);
                                if (v0 == 0) {
                                    // 0x0028b568
                                    charge(ctx, 3);
                                    lw(v0, sp, 0x64);
                                    if (v0 == 0) {
                                        goto L_0028b768;
                                    }
                                    goto L_0028b574;
                                }
                            L_0028b574:
                                charge(ctx, 44);
                                lw(a0, s4, act::kUnit);
                                a1 = s3;
                                jal(ctx, 0x28B57Cu, gen::fn_sub_2BD590_002bd590);
                                a0 = v0;
                                ld(v1, s4, act::kUid);
                                sd(v1, v0, 96);
                                a1 = 3;
                                jal(ctx, 0x28B594u, gen::fn_sub_27ED20_0027ed20);
                                lw(a0, s4, act::kUnit);
                                jal(ctx, 0x28B5A0u, gen::fn_sub_2BD480_002bd480);
                                a0 = v0;
                                ld(v1, s4, act::kUid);
                                sd(v1, v0, 96);
                                a1 = 1;
                                jal(ctx, 0x28B5B8u, gen::fn_sub_27ED20_0027ed20);
                                lw(a1, s4, act::kUnit);
                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                v0 = s2 & 0xFFFF;
                                v0 = sll(v0, 2);
                                v0 = addu(v0, v1);
                                lw(a0, v0, 3108);
                                a2 = a1;
                                a3 = 1;
                                t0 = 0;
                                jal(ctx, 0x28B5E4u, gen::fn_sub_2BAF90_002baf90);
                                s2 = v0;
                                v1 = 3;
                                sh(v1, v0, 72);
                                ld(v1, s4, act::kUid);
                                sd(v1, v0, 96);
                                a0 = s2;
                                a1 = 2;
                                jal(ctx, 0x28B608u, gen::fn_sub_27ED20_0027ed20);
                                v1 = dsll32(s1, 16);
                                v1 = dsra32(v1, 16);
                                v0 = si(-1);
                                if (v1 != v0) {
                                    // 0x0028b624
                                    charge(ctx, 11);
                                    a2 = s1 & 0xFFFF;
                                    a0 = 12;
                                    a1 = 2;
                                    jal(ctx, 0x28B630u, gen::fn_sub_2DD100_002dd100);
                                    a0 = v0;
                                    ld(v1, s4, act::kUid);
                                    sd(v1, v0, 96);
                                    a1 = 1;
                                    jal(ctx, 0x28B648u, gen::fn_sub_27ED20_0027ed20);
                                }
                                // 0x0028b650
                                charge(ctx, 42);
                                a0 = s4;
                                a1 = s4;
                                a2 = addiu(sp, 0x60);
                                a3 = 1;
                                t0 = a3;
                                jal(ctx, 0x28B664u, gen::fn_sub_2D7E20_002d7e20);
                                s0 = v0;
                                v1 = 11;
                                sb(v1, v0, 0);
                                ld(v1, s2, 88);
                                sd(v1, v0, 8);
                                ld(v1, s4, act::kUid);
                                sd(v1, v0, 96);
                                a0 = s0;
                                a1 = 1;
                                jal(ctx, 0x28B690u, gen::fn_sub_27ED20_0027ed20);
                                lw(a0, s4, act::kUnit);
                                a1 = a0;
                                a2 = si(-1);
                                a3 = 0;
                                t0 = 0;
                                t1 = 0;
                                t2 = 1;
                                t3 = addiu(sp, 0x60);
                                jal(ctx, 0x28B6B8u, gen::fn_sub_2BDBD0_002bdbd0);
                                a0 = v0;
                                v1 = 4;
                                sb(v1, v0, 0);
                                ld(v1, s0, 88);
                                sd(v1, v0, 8);
                                lbu(v1, v0, 71);
                                v1 = v1 & 0xDF;
                                sb(v1, v0, 71);
                                a1 = 3;
                                jal(ctx, 0x28B6E4u, gen::fn_sub_27ED20_0027ed20);
                                lw(v0, sp, 0x60);
                                if (v0 != 0) {
                                    // 0x0028b6f8
                                    charge(ctx, 16);
                                    lw(a0, s4, act::kUnit);
                                    a1 = 0;
                                    a2 = 0;
                                    jal(ctx, 0x28B704u, gen::fn_sub_2BD230_002bd230);
                                    a0 = v0;
                                    v1 = 4;
                                    sb(v1, v0, 0);
                                    ld(v1, s0, 88);
                                    sd(v1, v0, 8);
                                    lbu(v1, v0, 71);
                                    v1 = v1 & 0xDF;
                                    sb(v1, v0, 71);
                                    a1 = 3;
                                    jal(ctx, 0x28B730u, gen::fn_sub_27ED20_0027ed20);
                                }
                                // 0x0028b738
                                charge(ctx, 12);
                                a0 = s4;
                                a1 = 9;
                                jal(ctx, 0x28B740u, gen::fn_sub_2A3B40_002a3b40);
                                a0 = v0;
                                ld(v1, s4, act::kUid);
                                sd(v1, v0, 96);
                                a1 = 0;
                                jal(ctx, 0x28B758u, gen::fn_sub_27ED20_0027ed20);
                                // 0x0028b7dc (the shared epilogue, written out on this path)
                                charge(ctx, 9);
                                ld(ra, sp, 0x50);
                                lq(s4, sp, 0x40);
                                lq(s3, sp, 0x30);
                                lq(s2, sp, 0x20);
                                lq(s1, sp, 0x10);
                                lq(s0, sp, 0x0);
                                sp = addiu(sp, 0x80);
                                return;
                            }
                        L_0028b768:
                            charge(ctx, 8);
                            lw(v0, s4, 48);
                            lw(a0, v0, 2604);
                            jal(ctx, 0x28B770u, gen::fn_sub_302F50_00302f50);
                            v0 = dsll32(v0, 24);
                            v0 = dsra32(v0, 24);
                            if (i64(v0) < 0) {
                                // 0x0028b7a0
                                charge(ctx, 5);
                                a0 = s4;
                                jal(ctx, 0x28B7A4u, gen::fn_sub_2DC070_002dc070);
                                if (v0 == 0) {
                                    // 0x0028b7cc
                                    charge(ctx, 4);
                                    a0 = s4;
                                    a1 = 3;
                                    jal(ctx, 0x28B7D4u, gen::fn_btlActionSetState_00299d60);
                                } else {
                                    // 0x0028b7b4
                                    charge(ctx, 6);
                                    a0 = s4;
                                    a1 = 11;
                                    jal(ctx, 0x28B7BCu, gen::fn_btlActionSetState_00299d60);
                                }
                            } else {
                                // 0x0028b788
                                charge(ctx, 6);
                                a0 = s4;
                                a1 = 10;
                                jal(ctx, 0x28B790u, gen::fn_btlActionSetState_00299d60);
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x0028b7dc (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x0028CA00 sub_28CA00 -- 928 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlActionUpdateAnalyze] btlAction state ANALYZE, update (row 7), a step machine in +1156 (unless effect packet
// 2048 runs): 1 the analysed unit (sub_2DB690 / sub_289030) alive and in the battle: the flags 320 / 321 pick the
// analysis panel (sub_1FE2E0 / sub_1FE270), the camera on it, fades, sounds, the command menu hidden (gBtl 0x4000) ->
// 2, else -> 4; 2 when the panel is open, its message (sub_2DBB00 / sub_2E2D00) -> 3; 3 on confirm / cancel (pad bits
// 0x40 / 0x20) closes it (sub_1FE350), the menu back -> 5; 4 queues the 'cannot analyse' line (sub_2DB740 kind 10) ->
// 6; 5 waits for the panel to close -> 6; 6 ends: an action flagged 4 hands over to PACKET (30) with gBtl 0x400000 /
// +24 bits 0xC, else back to the resume state (+20) after sub_1FE4A0 / sub_2BED10; the step resets.
// Arguments: a0 btlAction.
void sub_28CA00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0028ca00
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 2048;
    jal(ctx, 0x28CA1Cu, gen::fn_sub_27E470_0027e470);
    if (v0 == 0) {
        // 0x0028ca2c
        charge(ctx, 4);
        lw(v1, s0, act::kAoaLeader);
        at = sltiu(v1, 7);
        if (at != 0) {
            // 0x0028ca3c
            charge(ctx, 7);
            a0 = 0x7B0000;
            a0 = addiu(a0, 31584);  // &0x7B7B60
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
            switch (v1.u()) {
            case 0x28CA58u:  // table[1]: step 1, open the analysis of the unit the cursor points at
                // 0x0028ca58
                charge(ctx, 9);
                jal(ctx, 0x28CA58u, gen::fn_sub_2DB690_002db690);
                s1 = v0;
                a0 = s1 & 0xFFFF;
                jal(ctx, 0x28CA68u, gen::fn_sub_289030_00289030);
                s2 = v0;
                if (s2 != 0) {
                    // 0x0028ca7c
                    charge(ctx, 6);
                    lw(a0, s2, unit::kDat);
                    a1 = 0;
                    jal(ctx, 0x28CA84u, gen::fn_datCalcIsDead_0030b5a0);
                    if (v0 != 0) {
                        goto L_0028cba8;
                    }
                    // 0x0028ca94
                    charge(ctx, 4);
                    lw(v0, s2, unit::kFlags);
                    v0 = v0 & 0x8;
                    if (v0 == 0) {
                        goto L_0028cba8;
                    }
                    // 0x0028caa4
                    charge(ctx, 5);
                    a0 = 320;
                    jal(ctx, 0x28CAA8u, gen::fn_datGetFlag_0016f190);
                    if (v0 == 0) {
                        // 0x0028cacc
                        charge(ctx, 5);
                        a0 = 321;
                        jal(ctx, 0x28CAD0u, gen::fn_datGetFlag_0016f190);
                        if (v0 != 0) {
                            // 0x0028cae0
                            charge(ctx, 3);
                            a0 = s1;
                            jal(ctx, 0x28CAE4u, gen::fn_sub_1FE270_001fe270);
                        }
                    } else {
                        // 0x0028cab8
                        charge(ctx, 5);
                        a0 = s1;
                        jal(ctx, 0x28CABCu, gen::fn_sub_1FE2E0_001fe2e0);
                    }
                    // 0x0028caec
                    charge(ctx, 36);
                    a0 = s2;
                    jal(ctx, 0x28CAF0u, gen::fn_sub_29A1D0_0029a1d0);
                    s1 = v0;
                    a0 = s0;
                    jal(ctx, 0x28CB00u, gen::fn_sub_28A780_0028a780);
                    a0 = 3;
                    a1 = 4095;
                    jal(ctx, 0x28CB10u, gen::fn_sub_2B8D60_002b8d60);
                    a0 = v0;
                    ld(v1, s0, act::kUid);
                    sd(v1, v0, 96);
                    a1 = 0;
                    jal(ctx, 0x28CB28u, gen::fn_sub_27ED20_0027ed20);
                    a0 = s1;
                    a1 = 3;
                    jal(ctx, 0x28CB38u, gen::fn_sub_2A3B40_002a3b40);
                    a0 = v0;
                    ld(v1, s0, act::kUid);
                    sd(v1, v0, 96);
                    a1 = 0;
                    jal(ctx, 0x28CB50u, gen::fn_sub_27ED20_0027ed20);
                    jal(ctx, 0x28CB58u, gen::fn_sub_2DBA80_002dba80);
                    jal(ctx, 0x28CB60u, gen::fn_sub_2DDBE0_002ddbe0);
                    jal(ctx, 0x28CB68u, gen::fn_sub_2D1A70_002d1a70);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x0028cb7c
                        charge(ctx, 7);
                        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, a0, gbtl::kFlags);
                        v0 = si(-16385);
                        v0 = v1 & v0;
                        sw(v0, a0, gbtl::kFlags);
                        jal(ctx, 0x28CB90u, gen::fn_sub_1FF350_001ff350);
                    }
                    // 0x0028cb98
                    charge(ctx, 4);
                    v1 = 2;
                    sw(v1, s0, act::kAoaLeader);
                    break;
                }
            L_0028cba8:
                charge(ctx, 6);
                jal(ctx, 0x28CBA8u, gen::fn_sub_2DBA80_002dba80);
                v1 = 4;
                sw(v1, s0, act::kAoaLeader);
                break;
            case 0x28CBC0u:  // table[2]: step 2, the panel is open: its message
                // 0x0028cbc0
                charge(ctx, 4);
                jal(ctx, 0x28CBC0u, gen::fn_sub_1FEBB0_001febb0);
                if (v0 == 0) {
                    // 0x0028cbd0
                    charge(ctx, 8);
                    jal(ctx, 0x28CBD0u, gen::fn_sub_2DB690_002db690);
                    a0 = v0 & 0xFFFF;
                    jal(ctx, 0x28CBDCu, gen::fn_sub_289030_00289030);
                    a0 = v0;
                    if (a0 != 0) {
                        // 0x0028cbf0
                        charge(ctx, 4);
                        jal(ctx, 0x28CBF0u, gen::fn_sub_2DBB00_002dbb00);
                        if (i64(v0) >= 0) {
                            // 0x0028cc00
                            charge(ctx, 3);
                            a0 = v0 & 0xFFFF;
                            jal(ctx, 0x28CC04u, gen::fn_sub_2E2D00_002e2d00);
                        }
                    }
                    // 0x0028cc0c
                    charge(ctx, 4);
                    v1 = 3;
                    sw(v1, s0, act::kAoaLeader);
                }
                break;
            case 0x28CC1Cu:  // table[3]: step 3, wait for confirm / cancel
                // 0x0028cc1c
                charge(ctx, 5);
                v1 = 0x7E0000;
                lhu(a1, v1, 2382);  // gPadFlags
                v1 = a1 & 0x40;
                if (v1 == 0) {
                    // 0x0028cc30
                    charge(ctx, 5);
                    v1 = 0x7E0000;
                    lhu(a0, v1, 2392);  // 0x7E0958
                    v1 = a0 & 0x40;
                    if (v1 != 0) {
                        goto L_0028cc5c;
                    }
                    // 0x0028cc44
                    charge(ctx, 3);
                    v1 = a1 & 0x20;
                    if (v1 != 0) {
                        goto L_0028cc5c;
                    }
                    // 0x0028cc50
                    charge(ctx, 3);
                    v1 = a0 & 0x20;
                    if (v1 != 0) {
                        goto L_0028cc5c;
                    }
                    break;
                }
            L_0028cc5c:
                charge(ctx, 7);
                jal(ctx, 0x28CC5Cu, gen::fn_sub_1FE350_001fe350);
                jal(ctx, 0x28CC64u, gen::fn_sub_2D1A70_002d1a70);
                v1 = 1;
                if (v0 == v1) {
                    // 0x0028cc78
                    charge(ctx, 6);
                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v1, gbtl::kFlags);
                    v0 = v0 | 0x4000;
                    sw(v0, v1, gbtl::kFlags);
                    jal(ctx, 0x28CC88u, gen::fn_sub_1FF370_001ff370);
                }
                // 0x0028cc90
                charge(ctx, 4);
                v1 = 5;
                sw(v1, s0, act::kAoaLeader);
                break;
            case 0x28CCA0u:  // table[4]: step 4, the "cannot analyse" line
                // 0x0028cca0
                charge(ctx, 15);
                a0 = s0;
                a1 = 10;
                a2 = 0;
                a3 = 0;
                t0 = 0;
                jal(ctx, 0x28CCB4u, gen::fn_sub_2DB740_002db740);
                a0 = v0;
                a1 = 1;
                jal(ctx, 0x28CCC4u, gen::fn_sub_27ED20_0027ed20);
                v1 = 6;
                sw(v1, s0, act::kAoaLeader);
                break;
            case 0x28CCDCu:  // table[5]: step 5, wait for the panel to close
                // 0x0028ccdc
                charge(ctx, 4);
                jal(ctx, 0x28CCDCu, gen::fn_sub_1FEBB0_001febb0);
                if (v0 == 0) {
                    // 0x0028ccec
                    charge(ctx, 4);
                    jal(ctx, 0x28CCECu, gen::fn_sub_1FEB70_001feb70);
                    if (v0 == 0) {
                        // 0x0028ccfc
                        charge(ctx, 4);
                        v1 = 6;
                        sw(v1, s0, act::kAoaLeader);
                    }
                }
                break;
            case 0x28CD0Cu:  // table[6]: step 6, the end of the state
                // 0x0028cd0c
                charge(ctx, 6);
                jal(ctx, 0x28CD0Cu, gen::fn_sub_2E2D40_002e2d40);
                lhu(v0, s0, act::kFlags);
                v0 = v0 & 0x4;
                if (v0 == 0) {
                    // 0x0028cd60
                    charge(ctx, 8);
                    jal(ctx, 0x28CD60u, gen::fn_sub_1FE4A0_001fe4a0);
                    jal(ctx, 0x28CD68u, gen::fn_sub_2BED10_002bed10);
                    a0 = s0;
                    lhu(a1, s0, act6::kNextState);
                    jal(ctx, 0x28CD78u, gen::fn_btlActionSetState_00299d60);
                } else {
                    // 0x0028cd24
                    charge(ctx, 15);
                    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v1, a0, gbtl::kFlags);
                    v0 = 0x400000;
                    v0 = v1 | v0;
                    sw(v0, a0, gbtl::kFlags);
                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lhu(v0, v1, gbtl::kFxRequest);
                    v0 = v0 | 0xC;
                    sh(v0, v1, gbtl::kFxRequest);
                    a0 = s0;
                    a1 = 30;
                    jal(ctx, 0x28CD50u, gen::fn_btlActionSetState_00299d60);
                }
                // 0x0028cd80
                charge(ctx, 1);
                sw(zero, s0, act::kAoaLeader);
                break;
            case 0x28CD84u:  // table[0]: step 0: nothing
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
        }
    }
    // 0x0028cd84 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0028CF20 sub_28CF20 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlActionInitAuto] btlAction state AUTO, init (row 9): resets the target list (sub_2D15A0 of +56), fills the
// target candidates (sub_2BFF60 into +136) and the cursor (sub_2C0970).
// Arguments: a0 btlAction.
void sub_28CF20(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0028cf20
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = addiu(s0, 56);
    jal(ctx, 0x28CF34u, gen::fn_sub_2D15A0_002d15a0);
    a0 = s0;
    a1 = addiu(s0, 136);
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x28CF4Cu, gen::fn_sub_2BFF60_002bff60);
    a0 = addiu(s0, 136);
    jal(ctx, 0x28CF58u, gen::fn_sub_2C0970_002c0970);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0028CF80 sub_28CF80 -- 240 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlActionUpdateAuto] btlAction state AUTO, update: command kind 1 (attack) with the unit's attack skill
// (sub_308930), the first candidate as the single target (sub_2C0880 / sub_2C08A0); the hero (side 0, id 1) gets the
// voice line packet kind 1; gBtl 0x4000000 sets the action's flag 0x4000; flag 2, state READY (12).
// Arguments: a0 btlAction.
void sub_28CF80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0028cf80
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = 1;
    sh(v0, a0, act::kCmdKind);
    lw(v0, a0, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x28CFA0u, gen::fn_sub_308930_00308930);
    sh(v0, s0, act::kCmdSkill);
    a0 = addiu(s0, 136);
    jal(ctx, 0x28CFB0u, gen::fn_sub_2C0880_002c0880);
    sw(v0, s0, act::kTargets);
    v0 = 1;
    sh(v0, s0, act::kTargetCount);
    a0 = addiu(s0, 136);
    lw(a1, s0, act::kTargets);
    jal(ctx, 0x28CFCCu, gen::fn_sub_2C08A0_002c08a0);
    lw(v1, s0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 == 0) {
        // 0x0028cfe4
        charge(ctx, 4);
        lhu(v0, v1, unit::kId);
        a1 = 1;
        if (v0 == a1) {
            // 0x0028cff4
            charge(ctx, 10);
            a0 = s0;
            a2 = 0;
            a3 = 0;
            t0 = 0;
            jal(ctx, 0x28D004u, gen::fn_sub_2DB740_002db740);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x28D014u, gen::fn_sub_27ED20_0027ed20);
        }
    }
    // 0x0028d01c
    charge(ctx, 6);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, v0, gbtl::kFlags);
    v0 = 0x4000000;
    v0 = v1 & v0;
    if (v0 != 0) {
        // 0x0028d034
        charge(ctx, 3);
        lhu(v0, s0, act::kFlags);
        v0 = v0 | 0x4000;
        sh(v0, s0, act::kFlags);
    }
    // 0x0028d040
    charge(ctx, 12);
    lhu(v0, s0, act::kFlags);
    v0 = v0 | 0x2;
    sh(v0, s0, act::kFlags);
    a0 = s0;
    a1 = 12;
    jal(ctx, 0x28D054u, gen::fn_btlActionSetState_00299d60);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0028D080 sub_28D080 -- 1248 bytes; frame 0x70: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlActionUpdateSupport] btlAction state SUPPORT, update (row 10; unless effect packet 1286 runs): the first of the
// unit's timed effects that ran out (sub_302F50, kinds 0..16 by a jump table) is cleared (datCalcClearEffect: 0 / 1
// together, 2 / 4 together, else its own) and its end message plays (sub_2BD850 with 22 + 2 * kind for the party, one
// more for an enemy; 70 / 71 and 90..97 for the later kinds) with the voice packet 9; kind 9 also drops HP and SP to
// 1 (a damage packet of 1 - HP / 1 - SP, sub_2D7E20). The state repeats until none is left, then BAD (11) or START
// HOME (3) by sub_2DC070.
// Arguments: a0 btlAction.
void sub_28D080(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0028d080
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    a0 = 1286;
    jal(ctx, 0x28D0A0u, gen::fn_sub_27E470_0027e470);
    if (v0 == 0) {
        // 0x0028d0b0
        charge(ctx, 8);
        lw(s0, s2, act::kUnit);
        lw(a0, s0, unit::kDat);
        jal(ctx, 0x28D0B8u, gen::fn_sub_302F50_00302f50);
        v0 = v0 & 0xFF;
        s1 = 0;
        if (i64(v0) >= 0) {
            // 0x0028d0d0
            charge(ctx, 3);
            at = sltiu(v0, 17);
            if (at != 0) {
                // 0x0028d0dc
                charge(ctx, 7);
                v1 = 0x7B0000;
                v1 = addiu(v1, 31616);  // &0x7B7B80
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x28D0F8u:  // table[0, 1]: kinds 0 / 1: message 22 (23 for an enemy)
                    // 0x0028d0f8
                    charge(ctx, 3);
                    lbu(v0, s0, unit::kSide);
                    if (v0 != 0) {
                        // 0x0028d110
                        charge(ctx, 1);
                        s3 = 23;
                    } else {
                        // 0x0028d104
                        charge(ctx, 3);
                        s3 = 22;
                    }
                    // 0x0028d114
                    charge(ctx, 10);
                    lw(a0, s0, unit::kDat);
                    a1 = 0;
                    jal(ctx, 0x28D11Cu, gen::fn_datCalcClearEffect_00301540);
                    lw(a0, s0, unit::kDat);
                    a1 = 1;
                    jal(ctx, 0x28D12Cu, gen::fn_datCalcClearEffect_00301540);
                    break;
                case 0x28D13Cu:  // table[2, 4]: kinds 2 / 4: message 24 / 25
                    // 0x0028d13c
                    charge(ctx, 3);
                    lbu(v0, s0, unit::kSide);
                    if (v0 != 0) {
                        // 0x0028d154
                        charge(ctx, 1);
                        s3 = 25;
                    } else {
                        // 0x0028d148
                        charge(ctx, 3);
                        s3 = 24;
                    }
                    // 0x0028d158
                    charge(ctx, 10);
                    lw(a0, s0, unit::kDat);
                    a1 = 4;
                    jal(ctx, 0x28D160u, gen::fn_datCalcClearEffect_00301540);
                    lw(a0, s0, unit::kDat);
                    a1 = 2;
                    jal(ctx, 0x28D170u, gen::fn_datCalcClearEffect_00301540);
                    break;
                case 0x28D180u:  // table[3]: kind 3: message 26 / 27
                    // 0x0028d180
                    charge(ctx, 3);
                    lbu(v0, s0, unit::kSide);
                    if (v0 != 0) {
                        // 0x0028d198
                        charge(ctx, 1);
                        s3 = 27;
                    } else {
                        // 0x0028d18c
                        charge(ctx, 3);
                        s3 = 26;
                    }
                    // 0x0028d19c
                    charge(ctx, 6);
                    lw(a0, s0, unit::kDat);
                    a1 = 3;
                    jal(ctx, 0x28D1A4u, gen::fn_datCalcClearEffect_00301540);
                    break;
                case 0x28D1B4u:  // table[5]: kind 5: message 28 / 29
                    // 0x0028d1b4
                    charge(ctx, 3);
                    lbu(v0, s0, unit::kSide);
                    if (v0 != 0) {
                        // 0x0028d1cc
                        charge(ctx, 1);
                        s3 = 29;
                    } else {
                        // 0x0028d1c0
                        charge(ctx, 3);
                        s3 = 28;
                    }
                    // 0x0028d1d0
                    charge(ctx, 6);
                    lw(a0, s0, unit::kDat);
                    a1 = 5;
                    jal(ctx, 0x28D1D8u, gen::fn_datCalcClearEffect_00301540);
                    break;
                case 0x28D1E8u:  // table[6]: kind 6: message 30 / 31
                    // 0x0028d1e8
                    charge(ctx, 3);
                    lbu(v0, s0, unit::kSide);
                    if (v0 != 0) {
                        // 0x0028d200
                        charge(ctx, 1);
                        s3 = 31;
                    } else {
                        // 0x0028d1f4
                        charge(ctx, 3);
                        s3 = 30;
                    }
                    // 0x0028d204
                    charge(ctx, 6);
                    lw(a0, s0, unit::kDat);
                    a1 = 6;
                    jal(ctx, 0x28D20Cu, gen::fn_datCalcClearEffect_00301540);
                    break;
                case 0x28D21Cu:  // table[7]: kind 7: message 32 / 33
                    // 0x0028d21c
                    charge(ctx, 3);
                    lbu(v0, s0, unit::kSide);
                    if (v0 != 0) {
                        // 0x0028d234
                        charge(ctx, 1);
                        s3 = 33;
                    } else {
                        // 0x0028d228
                        charge(ctx, 3);
                        s3 = 32;
                    }
                    // 0x0028d238
                    charge(ctx, 6);
                    lw(a0, s0, unit::kDat);
                    a1 = 7;
                    jal(ctx, 0x28D240u, gen::fn_datCalcClearEffect_00301540);
                    break;
                case 0x28D250u:  // table[8]: kind 8: message 34 / 35
                    // 0x0028d250
                    charge(ctx, 3);
                    lbu(v0, s0, unit::kSide);
                    if (v0 != 0) {
                        // 0x0028d268
                        charge(ctx, 1);
                        s3 = 35;
                    } else {
                        // 0x0028d25c
                        charge(ctx, 3);
                        s3 = 34;
                    }
                    // 0x0028d26c
                    charge(ctx, 6);
                    lw(a0, s0, unit::kDat);
                    a1 = 8;
                    jal(ctx, 0x28D274u, gen::fn_datCalcClearEffect_00301540);
                    break;
                case 0x28D284u:  // table[9]: kind 9: message 36 / 37, and HP / SP drop to 1
                    // 0x0028d284
                    charge(ctx, 3);
                    lbu(v0, s0, unit::kSide);
                    if (v0 != 0) {
                        // 0x0028d29c
                        charge(ctx, 1);
                        s3 = 37;
                    } else {
                        // 0x0028d290
                        charge(ctx, 3);
                        s3 = 36;
                    }
                    // 0x0028d2a0
                    charge(ctx, 7);
                    lw(a0, s0, unit::kDat);
                    a1 = 9;
                    jal(ctx, 0x28D2A8u, gen::fn_datCalcClearEffect_00301540);
                    s1 = 1;
                    break;
                case 0x28D2BCu:  // table[10]: kind 10: message 38 / 39
                    // 0x0028d2bc
                    charge(ctx, 3);
                    lbu(v0, s0, unit::kSide);
                    if (v0 != 0) {
                        // 0x0028d2d4
                        charge(ctx, 1);
                        s3 = 39;
                    } else {
                        // 0x0028d2c8
                        charge(ctx, 3);
                        s3 = 38;
                    }
                    // 0x0028d2d8
                    charge(ctx, 6);
                    lw(a0, s0, unit::kDat);
                    a1 = 10;
                    jal(ctx, 0x28D2E0u, gen::fn_datCalcClearEffect_00301540);
                    break;
                case 0x28D2F0u:  // table[11]: kind 11: message 70 / 71
                    // 0x0028d2f0
                    charge(ctx, 3);
                    lbu(v0, s0, unit::kSide);
                    if (v0 != 0) {
                        // 0x0028d308
                        charge(ctx, 1);
                        s3 = 71;
                    } else {
                        // 0x0028d2fc
                        charge(ctx, 3);
                        s3 = 70;
                    }
                    // 0x0028d30c
                    charge(ctx, 6);
                    lw(a0, s0, unit::kDat);
                    a1 = 11;
                    jal(ctx, 0x28D314u, gen::fn_datCalcClearEffect_00301540);
                    break;
                case 0x28D324u:  // table[13]: kind 13: message 90 / 91
                    // 0x0028d324
                    charge(ctx, 3);
                    lbu(v0, s0, unit::kSide);
                    if (v0 != 0) {
                        // 0x0028d33c
                        charge(ctx, 1);
                        s3 = 91;
                    } else {
                        // 0x0028d330
                        charge(ctx, 3);
                        s3 = 90;
                    }
                    // 0x0028d340
                    charge(ctx, 6);
                    lw(a0, s0, unit::kDat);
                    a1 = 13;
                    jal(ctx, 0x28D348u, gen::fn_datCalcClearEffect_00301540);
                    break;
                case 0x28D358u:  // table[14]: kind 14: message 92 / 93
                    // 0x0028d358
                    charge(ctx, 3);
                    lbu(v0, s0, unit::kSide);
                    if (v0 != 0) {
                        // 0x0028d370
                        charge(ctx, 1);
                        s3 = 93;
                    } else {
                        // 0x0028d364
                        charge(ctx, 3);
                        s3 = 92;
                    }
                    // 0x0028d374
                    charge(ctx, 6);
                    lw(a0, s0, unit::kDat);
                    a1 = 14;
                    jal(ctx, 0x28D37Cu, gen::fn_datCalcClearEffect_00301540);
                    break;
                case 0x28D38Cu:  // table[15]: kind 15: message 94 / 95
                    // 0x0028d38c
                    charge(ctx, 3);
                    lbu(v0, s0, unit::kSide);
                    if (v0 != 0) {
                        // 0x0028d3a4
                        charge(ctx, 1);
                        s3 = 95;
                    } else {
                        // 0x0028d398
                        charge(ctx, 3);
                        s3 = 94;
                    }
                    // 0x0028d3a8
                    charge(ctx, 6);
                    lw(a0, s0, unit::kDat);
                    a1 = 15;
                    jal(ctx, 0x28D3B0u, gen::fn_datCalcClearEffect_00301540);
                    break;
                case 0x28D3C0u:  // table[16]: kind 16: message 96 / 97
                    // 0x0028d3c0
                    charge(ctx, 3);
                    lbu(v0, s0, unit::kSide);
                    if (v0 != 0) {
                        // 0x0028d3d8
                        charge(ctx, 1);
                        s3 = 97;
                    } else {
                        // 0x0028d3cc
                        charge(ctx, 3);
                        s3 = 96;
                    }
                    // 0x0028d3dc
                    charge(ctx, 6);
                    lw(a0, s0, unit::kDat);
                    a1 = 16;
                    jal(ctx, 0x28D3E4u, gen::fn_datCalcClearEffect_00301540);
                    break;
                case 0x28D3F4u:  // table[12]: kind 12: no message
                L_0028d3f4:
                    charge(ctx, 1);
                    s3 = 0;
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
                goto L_0028d3f8;
            }
            goto L_0028d3f4;
        }
    L_0028d504:
        charge(ctx, 5);
        a0 = s2;
        jal(ctx, 0x28D508u, gen::fn_sub_2DC070_002dc070);
        if (v0 == 0) {
            // 0x0028d530
            charge(ctx, 4);
            a0 = s2;
            a1 = 3;
            jal(ctx, 0x28D538u, gen::fn_btlActionSetState_00299d60);
        } else {
            // 0x0028d518
            charge(ctx, 6);
            a0 = s2;
            a1 = 11;
            jal(ctx, 0x28D520u, gen::fn_btlActionSetState_00299d60);
        }
    }
    // 0x0028d540 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_0028d3f8:
    charge(ctx, 2);
    if (s3 == 0) {
        goto L_0028d504;
    }
    // 0x0028d400
    charge(ctx, 25);
    a0 = s2;
    jal(ctx, 0x28D404u, gen::fn_sub_28A780_0028a780);
    a0 = s2;
    a1 = 9;
    jal(ctx, 0x28D414u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    ld(v1, s2, 0);
    sd(v1, v0, 96);
    a1 = 0;
    jal(ctx, 0x28D42Cu, gen::fn_sub_27ED20_0027ed20);
    lw(a0, s2, 48);
    a1 = s3;
    jal(ctx, 0x28D43Cu, gen::fn_sub_2BD850_002bd850);
    a0 = v0;
    ld(v1, s2, 0);
    sd(v1, v0, 96);
    a1 = 3;
    jal(ctx, 0x28D454u, gen::fn_sub_27ED20_0027ed20);
    if (s1 != 0) {
        // 0x0028d464
        charge(ctx, 13);
        a0 = addiu(sp, 0x50);
        jal(ctx, 0x28D468u, gen::fn_sub_2D5DC0_002d5dc0);
        lw(v0, s2, 48);
        lw(a0, v0, 2604);
        jal(ctx, 0x28D478u, gen::fn_datCalcGetHp_002ffd70);
        v0 = v0 & 0xFFFF;
        v0 = addiu(v0, -1);
        v0 = subu(0, v0);
        sw(v0, sp, 0x50);
        if (i64(v0) >= 0) {
            // 0x0028d498
            charge(ctx, 1);
            sw(zero, sp, 0x50);
        }
        // 0x0028d49c
        charge(ctx, 10);
        lw(v0, s2, 48);
        lw(a0, v0, 2604);
        jal(ctx, 0x28D4A4u, gen::fn_datCalcGetSp_002ffd80);
        v0 = v0 & 0xFFFF;
        v0 = addiu(v0, -1);
        v0 = subu(0, v0);
        sw(v0, sp, 0x54);
        if (i64(v0) >= 0) {
            // 0x0028d4c4
            charge(ctx, 1);
            sw(zero, sp, 0x54);
        }
        // 0x0028d4c8
        charge(ctx, 13);
        a0 = s2;
        a1 = s2;
        a2 = addiu(sp, 0x50);
        a3 = 1;
        t0 = a3;
        jal(ctx, 0x28D4DCu, gen::fn_sub_2D7E20_002d7e20);
        a0 = v0;
        ld(v1, s2, 0);
        sd(v1, v0, 96);
        a1 = 1;
        jal(ctx, 0x28D4F4u, gen::fn_sub_27ED20_0027ed20);
    }
    // 0x0028d4fc
    charge(ctx, 2);
    // 0x0028d540 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

}  // namespace p3fes::game
