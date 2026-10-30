// Slice battle_camera, part 5 (game/include/p3fes/game/battle_camera_5.h), hand-decompiled from SLUS_216.21.
// battle_camera.cpp has the band's overview, battle_camera_cpu.h the register-faithful Cpu view and the cycle
// model; tests/game/test_battle_camera_5.cpp runs each body against its __recomp body.
//
// This file: the small camera work states of the camera table 0x6939F0 (20-byte rows {init, update, flag, flag, name};
// row k at 0x6939F0 + 20k, its name string at +16; the camera set layer sub_2A38F0 calls a row's init with the camera
// work record gBtl+32 in $a0, the camera update calls the row's update the same way), the thirteen empty update rows,
// the camera-kind picker sub_2A7830 and the leaf helpers at the band's end: the camera sequence records (sub_2B6BF0 /
// sub_2B6CD0 / sub_2B6BD0 over the 244-byte sequence tables at 0x693D10..0x694D90), the enemy size census sub_2B6DE0 /
// sub_2B6F70 and the per-side camera slots sub_2B7000.
#include "battle_camera_cpu.h"
#include "p3fes/game/battle_camera_5.h"

namespace p3fes::recomp_gen {
// Callees (still recompiled, or replaced by other slices: through their generated entry points).
void fn_sub_27FFB0_0027ffb0(p3fes::EEContext&);   // btlUnit position (unit, out)
void fn_sub_2D6290_002d6290(p3fes::EEContext&);   // (action) (battle_calc2)
void fn_datCalcIsHpSkill_002d6370(p3fes::EEContext&);   // (skill) (battle_calc2)
void fn_sub_2D63B0_002d63b0(p3fes::EEContext&);   // (sub-object, skill, 1) (battle_calc2)
void fn_btlTargetGetSideMask_002d1600(p3fes::EEContext&);   // (target record) -> the targets' side bits (battle_calc2)
void fn_sub_2D62D0_002d62d0(p3fes::EEContext&);   // (action) (battle_calc2)
void fn_sub_2880E0_002880e0(p3fes::EEContext&);   // btlUnit motion (unit, motion)
void fn_sub_2F8EB0_002f8eb0(p3fes::EEContext&);   // an enemy's swing motion (unit, skill) (battle_calc2)
void fn_sub_2835E0_002835e0(p3fes::EEContext&);   // a motion's strike time (unit, motion; $f12 speed)
void fn_sub_2D5BF0_002d5bf0(p3fes::EEContext&);   // (unit) (battle_calc2)
void fn_datCalcGetHeldWeaponType_00308c60(p3fes::EEContext&);  // (DatUnit) (battle_calc)
void fn_sub_3093A0_003093a0(p3fes::EEContext&);   // (DatUnit) (battle_calc)
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);  // (n) (battle_data)
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);  // (DatUnit, delta) (battle)
void fn_sub_351BB0_00351bb0(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game::bcam {

using namespace btl_cam;

namespace btl_cam5 {
// --- the camera work record gBtl+32 (the table rows' $a0) ------------------------------------------------------------
inline constexpr s32 kCamKey = 156;          // the record's key block (sub_2A3E80's second argument)
inline constexpr s32 kCamFlag220 = 220;      // u32: non-zero = the action camera is already set (sub_2AB2A0)
inline constexpr s32 kCamSubject = 224;      // u32: the subject btlAction
inline constexpr s32 kCamSeq = 236;          // the camera sequence record (sub_2B6BF0 / sub_2B6CD0; 20 bytes)
inline constexpr s32 kCamParam = 256;        // the state's parameter word: a target btlAction / a yaw in degrees
inline constexpr s32 kCamParamF = 268;       // f32 (rows 10 / 15) / u16 + u16 (row 13: 0 and the strike time)
inline constexpr s32 kCamStrike = 270;       // u16: row 13's strike time (sub_2835E0)
inline constexpr s32 kCamPhase = 272;        // u32 / u16: the state's phase
inline constexpr s32 kCamPhase2 = 276;       // u32
inline constexpr s32 kCamTarget10 = 280;     // u32: row 10's target (the subject's first target when set)
inline constexpr s32 kCamTarget15 = 284;     // u32: row 15's target
inline constexpr s32 kCamMotionUnit = 288;   // u32: the btlUnit whose motion is played (sub_2A3750 / sub_2880E0)
inline constexpr s32 kCamMotion = 292;       // u16: that motion
// --- btlAction / btlUnit ---------------------------------------------------------------------------------------------
inline constexpr s32 kActFlags2 = 26;        // u16: bit 0 a combatant
inline constexpr s32 kActUnit = 48;          // u32: btlUnit*
inline constexpr s32 kActTarget0 = 56;       // u32: the first chosen target (the target record starts here)
inline constexpr s32 kActSkill = 110;        // s16: the skill of the chosen command
inline constexpr s32 kUnitScale = 44;        // f32: the unit's scale
inline constexpr s32 kUnitWidth = 140;       // f32: the unit's width (times the scale)
inline constexpr s32 kUnitHeight = 144;      // f32: the unit's height (times the scale)
inline constexpr s32 kUnitSide = 162;        // u8: 0 party, 1 enemy
inline constexpr s32 kUnitClass = 164;       // u16: the party member's camera class (row 12's sequence table index)
inline constexpr s32 kUnitSubObject = 2560;  // u32: the unit's sub-object (persona)
inline constexpr s32 kUnitDat = 2604;        // u32: DatUnit*
inline constexpr s32 kUnitNextA = 2608;      // u32: next btlUnit in its side's list A
// --- gBtl ------------------------------------------------------------------------------------------------------------
inline constexpr s32 kGFlags = 12;           // u32: bit 21 a scripted battle
inline constexpr s32 kGCamRepeat = 266;      // u16: how often the current camera was set again in a row (sub_2A38F0)
inline constexpr s32 kGEnemyListA = 348;     // u32: the enemies' list A (gBtl+340 + 8)
inline constexpr s32 kGSetupEnemies = 3004;  // u32: the setup block's enemy group (+8 the ENCOUNT index)
inline constexpr s32 kGSideSlots0 = 2620;    // u32[4]: the party's camera slots (sub_2B7000)
inline constexpr s32 kGSideSlots1 = 2636;    // u32[4]: the enemies'
// --- the camera sequence record (sub_2B6BF0): +0 / +4 two words, +8 u16, +10 s16 the step (-1 = none yet), +12 u16
// the frame in the step, +14 u16 flags (bit 0 running, bit 1 the coin flip, bits 2..4 the caller's flags 2 / 4 / 8),
// +16 the sequence table: u16 count at +0, 60-byte steps from +4 (step +0 s16 frames, +24 u16 the camera kind)
inline constexpr s32 kSeqFlags = 14;
inline constexpr s32 kSeqTable = 16;
}  // namespace btl_cam5
using namespace btl_cam5;

class Cpu5 final : public Cpu {
public:
    using Cpu::Cpu;
#define P3FES_BCAM_BODY_5(name, addr) void name();
    P3FES_BCAM_BODIES_5(P3FES_BCAM_BODY_5)
#undef P3FES_BCAM_BODY_5

private:
    void aim_at_subject(u32 fn, u32 scale_hi, s32 flags);
    void random_yaw(u32 fn);
    void aim_target_key(u64 cycles, u32 link);
    // `lui d, hi; addiu d, d, lo`: a data address (lo < 0x8000 everywhere here)
    void la(Gpr& d, u32 addr) {
        d = lui(addr >> 16);
        d = addiu(d, static_cast<s32>(addr & 0xffff));
    }
    // `lhu v1, off(rec); ori v1, v1, bit; sh v1, off(rec)`
    void set_flag16(const Gpr& rec, s32 off, u32 bit) {
        lhu(v1, rec, off);
        v1 = v1 | bit;
        sh(v1, rec, off);
    }
    // `lhu v1, off(s1); addiu v1, v1, 1; sh v1, off(s1)`
    void count16(s32 off) {
        lhu(v1, s1, off);
        v1 = addiu(v1, 1);
        sh(v1, s1, off);
    }
};

// =====================================================================================================================
// The small camera work states
// =====================================================================================================================

// The aim-at-subject body compiled four times (rows 9 / 16 / 17 / 5, at `fn`): when the subject is a combatant, the
// camera key block (record +156) looks at its unit's position (sub_27FFB0 into sp+48) with the distance
// unit+144 * unit+44 * scale (the float whose high half is `scale_hi`) in $f12 and the sub_2A3E80 flags `flags`. The
// subject's unit lives in $s0, the record in $s1.
void Cpu5::aim_at_subject(u32 fn, u32 scale_hi, s32 flags) {
    enter(8);
    sp = addiu(sp, -64);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    lw(a0, a0, kCamSubject);
    if (a0 != 0) {
        charge(4);
        lhu(v1, a0, kActFlags2);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            charge(18);
            lw(s0, a0, kActUnit);
            a0 = s0;
            a1 = addiu(sp, 48);
            jal(fn + 0x3c, rg::fn_sub_27FFB0_0027ffb0);
            lwc1(F1, s0, kUnitHeight);
            lwc1(F0, s0, kUnitScale);
            mul_s(F1, F1, F0);
            lif(v0, scale_hi, F0);
            mul_s(F12, F0, F1);
            lw(a0, s1, kCamSubject);
            a1 = addiu(s1, kCamKey);
            a2 = addiu(sp, 48);
            a3 = li(flags);
            jal(fn + 0x70, rg::fn_sub_2A3E80_002a3e80);
        }
    }
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// 0x2A5460 sub_2A5460(record): row 9 OWN's update: aim at the subject, distance half its height, flags 49.
void Cpu5::sub_2A5460() { aim_at_subject(0x2a5460, 0x3f00, 49); }
// 0x2A5F40 sub_2A5F40(record): row 16 SKILL_RECITE_P's update: aim at the subject, a quarter of its height, flags 49.
void Cpu5::sub_2A5F40() { aim_at_subject(0x2a5f40, 0x3e80, 49); }
// 0x2A6560 sub_2A6560(record): row 17 SKILL_RECITE_E's update: aim at the subject, a quarter of its height, flags 51.
void Cpu5::sub_2A6560() { aim_at_subject(0x2a6560, 0x3e80, 51); }
// 0x2B4720 sub_2B4720(record): row 5 REINFORCE's update: aim at the subject, half its height, flags 49.
void Cpu5::sub_2B4720() { aim_at_subject(0x2b4720, 0x3f00, 49); }

// The random-yaw init compiled twice (rows 6 / 36, at `fn`): record +256 = (float)datCalcRand(360) (as u32 -> float),
// then sub_2A3E80(subject, 0, 0, 64) with $f12 = 0.
void Cpu5::random_yaw(u32 fn) {
    enter(9);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    a0 = li(360);
    jal(fn + 0x14, rg::fn_datCalcRand_002ffbc0);
    u2f(F0, F0, v0, v1, v0);
    charge(13);
    swc1(F0, s0, kCamParam);
    mtc1(zero, F12);
    lw(a0, s0, kCamSubject);
    a1 = 0;
    a2 = 0;
    a3 = li(64);
    jal(fn + 0x6c, rg::fn_sub_2A3E80_002a3e80);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// 0x2B4F40 sub_2B4F40(record): row 6 ROUNDUP's init: a random yaw.
void Cpu5::sub_2B4F40() { random_yaw(0x2b4f40); }
// 0x2B5650 sub_2B5650(record): row 36 NYX FEATHER's init: a random yaw.
void Cpu5::sub_2B5650() { random_yaw(0x2b5650); }

// 0x2B4BC0 sub_2B4BC0(record): row 4 ASSIST's init: sub_2A3E80(subject, 0, 0, 0) with $f12 = 0.
void Cpu5::sub_2B4BC0() {
    enter(13);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    mtc1(zero, F12);
    lw(a0, a0, kCamSubject);
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(0x2b4bdc, rg::fn_sub_2A3E80_002a3e80);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// 0x2B55D0 sub_2B55D0(record): row 35 CHANGE FORM's init: sub_351BB0(8).
void Cpu5::sub_2B55D0() {
    enter(9);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    a0 = li(8);
    jal(0x2b55dc, rg::fn_sub_351BB0_00351bb0);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// The tail of rows 10 and 15's updates: the key block (record +156) looks at the target key (record +256) with the
// distance record +268 ($f12) and flags 51; `cycles` = the block's charge, `link` = the jal's.
void Cpu5::aim_target_key(u64 cycles, u32 link) {
    charge(cycles);
    a1 = addiu(t0, kCamKey);
    a2 = addiu(t0, kCamParam);
    lwc1(F12, t0, kCamParamF);
    a3 = li(51);
    jal(link, rg::fn_sub_2A3E80_002a3e80);
}

// 0x2B0210 sub_2B0210(record): row 10 ATTACK_SHORT's update: while the subject (a combatant) still has one target and it
// is the record's +280, the key block keeps looking at the target key (+156 at +256, distance +268, flags 51).
void Cpu5::sub_2B0210() {
    enter(6);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    a3 = a0;
    lw(a0, a0, kCamSubject);
    if (a0 != 0) {
        charge(4);
        lhu(a1, a0, kActTargetCount);
        v1 = li(1);
        if (a1 == v1) {
            charge(4);
            lw(a1, a3, kCamTarget10);
            lw(v1, a0, kActTarget0);
            if (a1 == v1) {
                charge(4);
                lhu(v1, a0, kActFlags2);
                v1 = v1 & 0x1;
                if (v1 != 0) {
                    charge(6);
                    a1 = addiu(a3, kCamKey);
                    a2 = addiu(a3, kCamParam);
                    lwc1(F12, a3, kCamParamF);
                    a3 = li(51);
                    jal(0x2b0268, rg::fn_sub_2A3E80_002a3e80);
                }
            }
        }
    }
    charge(4);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// 0x2B1CF0 sub_2B1CF0(record): row 15 ATTACK_COMB's update: as row 10's (one target, the record's +284, a combatant)
// but only for a party subject, and not in a scripted battle (gBtl+12 bit 21) whose ENCOUNT index is 436. The two
// arms (gBtl+266 == 0 / otherwise) do the same at different costs.
void Cpu5::sub_2B1CF0() {
    enter(6);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    t0 = a0;
    lw(a0, a0, kCamSubject);
    do {
        if (a0 == 0) break;
        charge(4);
        lhu(a1, a0, kActTargetCount);
        v1 = li(1);
        if (a1 != v1) break;
        charge(4);
        lw(a1, t0, kCamTarget15);
        lw(v1, a0, kActTarget0);
        if (a1 != v1) break;
        charge(4);
        lhu(v1, a0, kActFlags2);
        a3 = v1 & 0x1;
        if (a3 == 0) break;
        charge(4);
        lw(v1, a0, kActUnit);
        lbu(v1, v1, kUnitSide);
        if (v1 != 0) break;
        charge(6);
        gbtl(a2);
        lw(a1, a2, kGFlags);
        v1 = lui(0x20);
        v1 = a1 & v1;
        if (v1 != 0) {
            charge(5);
            lw(v1, a2, kGSetupEnemies);
            lhu(a1, v1, 8);
            v1 = li(436);
            if (a1 == v1) break;
        }
        charge(4);
        lhu(a1, a2, kGCamRepeat);
        v1 = li(1);
        bool first = false;  // gBtl+266 == 0
        if (a1 != v1) {
            charge(2);
            if (a1 == 0) first = true;
            else charge(2);
        }
        charge(2);
        if (a0 == 0) break;
        charge(2);
        if (a3 == 0) break;
        if (first) aim_target_key(8, 0x2b1db4);
        else aim_target_key(6, 0x2b1de4);
    } while (false);
    charge(4);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// 0x2B1E00 sub_2B1E00(record): row 12 ATTACK_DOWN_P's init. record +256 = the subject's first target. For a party
// subject: the camera sequence of its class (3 when sub_2D5BF0(unit), else unit+164) through the 11-row jump table
// 0x7B7CD0 -- class 1 the weapon's table 0x693D10 + 244 * datCalcGetHeldWeaponType(DatUnit), 2 0x6944B0, 3 by
// sub_3093A0(DatUnit) (1 / 2 / 3 -> 0x6945B0 / 0x6946A4 / 0x694798), 4 / 5 / 7 / 8 / 9 / 10 -> 0x694890 / 0x694990 /
// 0x694A90 / 0x694B90 / 0x694C90 / 0x694D90, 0 / 6 and others keep $s1 (the caller's) -- starts in the sequence record
// +236 (sub_2B6BF0(rec, subject, target, table, 3)); its first step (sub_2B6CD0) picks the camera: kind 1 (step +28)
// = sub_2A3E80(subject, 0, 0, 1) then (..., 8) and phase 1, any other sub_2A3E80(subject, 0, 0, 10) and phase 0; then
// +276 = 0. A jump-table word outside the table's labels is a tail jump (the recompiled body's).
void Cpu5::sub_2B1E00() {
    enter(14);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    lw(v1, a0, kCamSubject);
    lw(v1, v1, kActTarget0);
    sw(v1, a0, kCamParam);
    lw(v1, a0, kCamSubject);
    lw(s0, v1, kActUnit);
    lbu(v1, s0, kUnitSide);
    if (v1 == 0) {
        charge(5);
        a0 = s0;
        jal(0x2b1e3c, rg::fn_sub_2D5BF0_002d5bf0);
        if (v0 != 0) {
            charge(3);
            v0 = li(3);
        } else {
            charge(1);
            lhu(v0, s0, kUnitClass);
        }
        charge(4);
        v0 = v0 & 0xffff;
        at = sltiu(v0, 11);
        if (at != 0) {
            charge(7);
            la(v1, 0x7b7cd0);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (static_cast<u32>(v0)) {
            case 0x2b1e88:  // class 1: by the held weapon (244-byte tables from 0x693D10)
                charge(14);
                lw(a0, s0, kUnitDat);
                jal(0x2b1e8c, rg::fn_datCalcGetHeldWeaponType_00308c60);
                v1 = v0 & 0xff;
                v0 = sll(v1, 4);
                v0 = subu(v0, v1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                la(v0, 0x693d10);
                s1 = addu(v0, v1);
                break;
            case 0x2b1ec0:
                charge(4);
                la(s1, 0x6944b0);
                break;
            case 0x2b1ed0:  // class 3: by sub_3093A0
                charge(7);
                lw(a0, s0, kUnitDat);
                jal(0x2b1ed4, rg::fn_sub_3093A0_003093a0);
                v1 = v0 & 0xff;
                v0 = li(3);
                if (v1 == v0) {
                    charge(4);
                    la(s1, 0x694798);
                    break;
                }
                charge(3);
                v0 = li(2);
                if (v1 == v0) {
                    charge(4);
                    la(s1, 0x6946a4);
                    break;
                }
                charge(3);
                v0 = li(1);
                if (v1 == v0) {
                    charge(4);
                    la(s1, 0x6945b0);
                    break;
                }
                charge(2);
                break;
            case 0x2b1f3c:
                charge(4);
                la(s1, 0x694890);
                break;
            case 0x2b1f4c:
                charge(4);
                la(s1, 0x694990);
                break;
            case 0x2b1f5c:
                charge(4);
                la(s1, 0x694a90);
                break;
            case 0x2b1f6c:
                charge(4);
                la(s1, 0x694b90);
                break;
            case 0x2b1f7c:
                charge(4);
                la(s1, 0x694c90);
                break;
            case 0x2b1f8c:
                charge(2);
                la(s1, 0x694d90);
                break;
            case 0x2b1f94:  // classes 0 and 6
                break;
            default:
                jr_unknown(v0);
                return;
            }
        }
        charge(12);
        lw(a1, s2, kCamSubject);
        a0 = addiu(s2, kCamSeq);
        lw(a2, a1, kActTarget0);
        a3 = s1;
        t0 = li(3);
        jal(0x2b1fa8, rg::fn_sub_2B6BF0_002b6bf0);
        a0 = addiu(s2, kCamSeq);
        jal(0x2b1fb4, rg::fn_sub_2B6CD0_002b6cd0);
        if (v0 != 0) {
            charge(4);
            lhu(v0, v0, 28);
            a3 = li(1);
            if (v0 == a3) {
                charge(17);
                mtc1(zero, F12);
                lw(a0, s2, kCamSubject);
                a1 = 0;
                a2 = 0;
                jal(0x2b1fe4, rg::fn_sub_2A3E80_002a3e80);
                mtc1(zero, F12);
                lw(a0, s2, kCamSubject);
                a1 = 0;
                a2 = 0;
                a3 = li(8);
                jal(0x2b2000, rg::fn_sub_2A3E80_002a3e80);
                v1 = li(1);
                sw(v1, s2, kCamPhase);
            } else {
                charge(8);
                mtc1(zero, F12);
                lw(a0, s2, kCamSubject);
                a1 = 0;
                a2 = 0;
                a3 = li(10);
                jal(0x2b202c, rg::fn_sub_2A3E80_002a3e80);
                sw(zero, s2, kCamPhase);
            }
        }
        charge(1);
        sw(zero, s2, kCamPhase2);
    }
    charge(7);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// 0x2B2800 sub_2B2800(record): row 13 ATTACK_DOWN_E's init: the subject unit's swing motion for its skill
// (sub_2F8EB0(unit, skill); -1 -> 4), record +270 = its strike time sub_2835E0(unit, motion) at speed 1.0, +256 = the
// subject's first target, +268 = 0.
void Cpu5::sub_2B2800() {
    enter(14);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lw(v0, a0, kCamSubject);
    lh(a1, v0, kActSkill);
    lw(a0, v0, kActUnit);
    jal(0x2b281c, rg::fn_sub_2F8EB0_002f8eb0);
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    v0 = li(-1);
    if (a0 == v0) {
        charge(1);
        a0 = li(4);
    }
    charge(17);
    lw(v1, s0, kCamSubject);
    a1 = a0 & 0xffff;
    lif(v0, 0x3f80, F12);
    lw(a0, v1, kActUnit);
    jal(0x2b2850, rg::fn_sub_2835E0_002835e0);
    sh(v0, s0, kCamStrike);
    lw(v1, s0, kCamSubject);
    lw(v1, v1, kActTarget0);
    sw(v1, s0, kCamParam);
    sh(zero, s0, kCamParamF);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// 0x2AB2A0 sub_2AB2A0(record): the motion step of the skill cameras: for a combatant subject, unless +220 is set the
// camera aims at it (sub_2A3E80(subject, 0, 0, 3), $f12 = 0); then when sub_2A3750(record, motion unit +288) allows
// it, the motion +292 is played on that unit (sub_2880E0).
void Cpu5::sub_2AB2A0() {
    enter(7);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lw(a0, a0, kCamSubject);
    if (a0 != 0) {
        charge(4);
        lhu(v1, a0, kActFlags2);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            charge(3);
            lw(v0, s0, kCamFlag220);
            if (v0 == 0) {
                charge(6);
                mtc1(zero, F12);
                a1 = 0;
                a2 = 0;
                a3 = li(3);
                jal(0x2ab2e8, rg::fn_sub_2A3E80_002a3e80);
            }
            charge(6);
            a0 = s0;
            lw(a1, s0, kCamMotionUnit);
            jal(0x2ab2f8, rg::fn_sub_2A3750_002a3750);
            if (v0 != 0) {
                charge(4);
                lw(a0, s0, kCamMotionUnit);
                lhu(a1, s0, kCamMotion);
                jal(0x2ab310, rg::fn_sub_2880E0_002880e0);
            }
        }
    }
    charge(5);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// 0x2AD770 sub_2AD770(record): row 22 SKILL_EXEC_EC's update, by the phase (u16 +272) through the 7-row jump table
// 0x7B7CB0: phase 1 aims at a combatant subject (as row 9: half its height, flags 49); phase 6 plays the motion of a
// combatant subject's motion unit when sub_2A3750 allows it (as sub_2AB2A0); the others (and phases >= 7) do nothing.
// A jump-table word outside the table's labels is a tail jump (the recompiled body's).
void Cpu5::sub_2AD770() {
    enter(9);
    sp = addiu(sp, -64);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lhu(v1, a0, kCamPhase);
    at = sltiu(v1, 7);
    if (at != 0) {
        charge(7);
        la(a1, 0x7b7cb0);
        v1 = sll(v1, 2);
        v1 = addu(v1, a1);
        lw(v1, v1, 0);
        switch (static_cast<u32>(v1)) {
        case 0x2ad7b0:  // phase 1
            charge(3);
            lw(a0, s0, kCamSubject);
            if (a0 == 0) break;
            charge(4);
            lhu(v1, a0, kActFlags2);
            v1 = v1 & 0x1;
            if (v1 == 0) break;
            charge(20);
            lw(s1, a0, kActUnit);
            a0 = s1;
            a1 = addiu(sp, 48);
            jal(0x2ad7d8, rg::fn_sub_27FFB0_0027ffb0);
            lwc1(F1, s1, kUnitHeight);
            lwc1(F0, s1, kUnitScale);
            mul_s(F1, F1, F0);
            lif(v0, 0x3f00, F0);
            mul_s(F12, F0, F1);
            lw(a0, s0, kCamSubject);
            a1 = addiu(s0, kCamKey);
            a2 = addiu(sp, 48);
            a3 = li(49);
            jal(0x2ad80c, rg::fn_sub_2A3E80_002a3e80);
            break;
        case 0x2ad81c:  // phase 6 ($a0 is still the record for sub_2A3750)
            charge(3);
            lw(v1, s0, kCamSubject);
            if (v1 == 0) break;
            charge(4);
            lhu(v1, v1, kActFlags2);
            v1 = v1 & 0x1;
            if (v1 == 0) break;
            charge(5);
            lw(a1, s0, kCamMotionUnit);
            jal(0x2ad83c, rg::fn_sub_2A3750_002a3750);
            if (v0 == 0) break;
            charge(4);
            lw(a0, s0, kCamMotionUnit);
            lhu(a1, s0, kCamMotion);
            jal(0x2ad854, rg::fn_sub_2880E0_002880e0);
            break;
        case 0x2ad85c:  // phases 0, 2..5
            break;
        default:
            jr_unknown(v1);
            return;
        }
    }
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// 0x2A7830 sub_2A7830(record): the camera kind (1..6) for the subject's command, by its skill (s16 +110):
//   * sub_2D6290(subject) set: 1 when its first target is itself; 2 when sub_2A32F0(record) or datCalcIsHpSkill(skill) is 0;
//     else 4, except a party subject whose sub-object fails sub_2D63B0(sub-object, skill, 1) gets 2;
//   * otherwise by the targets' sides btlTargetGetSideMask(target record): both (3) -> 6; a party subject whose targets include
//     side bit 0: 6 when sub_2D62D0(subject), 1 when it targets itself, else datCalcIsHpSkill(skill) ? 4 : 2; any other
//     subject: datCalcIsHpSkill(skill) ? 5 : 3.
void Cpu5::sub_2A7830() {
    enter(11);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    lw(a0, a0, kCamSubject);
    lh(s0, a0, kActSkill);
    jal(0x2a784c, rg::fn_sub_2D6290_002d6290);
    if (v0 != 0) {
        charge(4);
        lw(v1, s1, kCamSubject);
        lw(v0, v1, kActTarget0);
        if (v0 == v1) {
            charge(3);
            v0 = li(1);
        } else {
            charge(5);
            a0 = s1;
            jal(0x2a787c, rg::fn_sub_2A32F0_002a32f0);
            if (v0 != 0) {
                charge(3);
                v0 = li(2);
            } else {
                charge(5);
                a0 = s0;
                jal(0x2a789c, rg::fn_datCalcIsHpSkill_002d6370);
                if (v0 == 0) {
                    charge(3);
                    v0 = li(2);
                } else {
                    charge(5);
                    lw(v0, s1, kCamSubject);
                    lw(v1, v0, kActUnit);
                    lbu(v0, v1, kUnitSide);
                    bool four = v0 != 0;
                    if (!four) {
                        charge(7);
                        lw(a0, v1, kUnitSubObject);
                        a1 = s0;
                        a2 = li(1);
                        jal(0x2a78d8, rg::fn_sub_2D63B0_002d63b0);
                        four = v0 != 0;
                        if (!four) {
                            charge(3);
                            v0 = li(2);
                        }
                    }
                    if (four) {
                        charge(3);
                        v0 = li(4);
                    }
                }
            }
        }
    } else {
        charge(9);
        lw(v0, s1, kCamSubject);
        a0 = addiu(v0, kActTarget0);
        jal(0x2a7908, rg::fn_btlTargetGetSideMask_002d1600);
        a1 = v0 & 0xffff;
        v1 = a1 & 0x3;
        v0 = li(3);
        if (v1 == v0) {
            charge(3);
            v0 = li(6);
        } else {
            charge(5);
            lw(a0, s1, kCamSubject);
            lw(v0, a0, kActUnit);
            lbu(v0, v0, kUnitSide);
            bool other = v0 != 0;  // an enemy subject, or no side-0 target
            if (!other) {
                charge(3);
                v0 = a1 & 0x1;
                other = v0 == 0;
            }
            if (!other) {
                charge(4);
                jal(0x2a7950, rg::fn_sub_2D62D0_002d62d0);
                if (v0 != 0) {
                    charge(3);
                    v0 = li(6);
                } else {
                    charge(4);
                    lw(v1, s1, kCamSubject);
                    lw(v0, v1, kActTarget0);
                    if (v0 == v1) {
                        charge(3);
                        v0 = li(1);
                    } else {
                        charge(5);
                        a0 = s0;
                        jal(0x2a798c, rg::fn_datCalcIsHpSkill_002d6370);
                        if (v0 != 0) {
                            charge(3);
                            v0 = li(4);
                        } else {
                            charge(1);
                            v0 = li(2);
                        }
                        charge(2);
                    }
                }
            } else {
                charge(5);
                a0 = s0;
                jal(0x2a79b8, rg::fn_datCalcIsHpSkill_002d6370);
                if (v0 == 0) {
                    charge(3);
                    v0 = li(3);
                } else {
                    charge(1);
                    v0 = li(5);
                }
            }
        }
    }
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// =====================================================================================================================
// The empty update rows (`jr ra; nop`)
// =====================================================================================================================

// 0x2A6ED0 nullsub_87: row 18 MOVE_TARGET's update.
void Cpu5::nullsub_87() { enter(2); }
// 0x2A7380 nullsub_88: row 19 MOVE_TARGET_A's update.
void Cpu5::nullsub_88() { enter(2); }
// 0x2A7820 nullsub_89: row 20 MOVE_HOME's update.
void Cpu5::nullsub_89() { enter(2); }
// 0x2ADC70 nullsub_90: row 23 SKILL_EXEC_ONE's update.
void Cpu5::nullsub_90() { enter(2); }
// 0x2ADCC0 nullsub_91: row 24 SKILL_EXEC_REC's update.
void Cpu5::nullsub_91() { enter(2); }
// 0x2ADD00 nullsub_92: row 25 SKILL_EXEC_PS's update.
void Cpu5::nullsub_92() { enter(2); }
// 0x2AE250 nullsub_93: row 28 COMMAND's update.
void Cpu5::nullsub_93() { enter(2); }
// 0x2AE4C0 nullsub_94: row 26 PERSONA's update.
void Cpu5::nullsub_94() { enter(2); }
// 0x2AE730 nullsub_95: row 27 OVERLIMIT's update.
void Cpu5::nullsub_95() { enter(2); }
// 0x2B1050 nullsub_96: row 11 ATTACK_LONG's update.
void Cpu5::nullsub_96() { enter(2); }
// 0x2B2EA0 nullsub_97: row 14 ATTACK_SLIP's update.
void Cpu5::nullsub_97() { enter(2); }
// 0x2B3330 nullsub_98: row 30 FREE's update.
void Cpu5::nullsub_98() { enter(2); }
// 0x2B3680 nullsub_99: row 31 RESET's update.
void Cpu5::nullsub_99() { enter(2); }

// =====================================================================================================================
// The leaf helpers at the band's end
// =====================================================================================================================

// 0x2B6490 sub_2B6490(): the default camera sequence: memcpy(0x694C90, 0x6941D4, 244) ($v0 = memcpy's).
void Cpu5::sub_2B6490() {
    enter(13);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    la(a0, 0x694c90);
    la(a1, 0x6941d4);
    a2 = li(244);
    jal(0x2b64ac, rg::fn_memcpy_00521250);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// 0x2B6BD0 sub_2B6BD0(seq): 1 while the camera sequence record runs (+14 bit 0).
void Cpu5::sub_2B6BD0() {
    enter(5);
    lhu(v0, a0, kSeqFlags);
    v0 = v0 & 0x1;
    v0 = sltu(zero, v0);
}

// 0x2B6BF0 sub_2B6BF0(seq, a1, a2, table, flags t0): starts a camera sequence: +0 = a1, +4 = a2, +16 = the table,
// +8 = 0, +10 = -1 (no step yet), +12 = 0, +14 bit 0 set and bit 1 cleared; flags bit 0: bit 1 on a coin flip
// (datCalcRand(100) >= 50); bits 1 / 2 / 3 -> +14 bits 2 / 3 / 4.
void Cpu5::sub_2B6BF0() {
    enter(22);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    sw(a1, a0, 0);
    sw(a2, a0, 4);
    sw(a3, a0, kSeqTable);
    sh(zero, a0, 8);
    v1 = li(-1);
    sh(v1, a0, 10);
    sh(zero, a0, 12);
    set_flag16(a0, kSeqFlags, 0x1);
    lhu(v1, a0, kSeqFlags);
    v1 = v1 & 0xfffd;
    sh(v1, a0, kSeqFlags);
    s0 = t0 & 0xffff;
    v1 = s0 & 0x1;
    if (v1 != 0) {
        charge(6);
        a0 = li(100);
        jal(0x2b6c4c, rg::fn_datCalcRand_002ffbc0);
        v1 = sltiu(v0, 50);
        if (v1 == 0) {
            charge(3);
            set_flag16(s1, kSeqFlags, 0x2);
        }
    }
    charge(3);
    v1 = s0 & 0x2;
    if (v1 != 0) {
        charge(3);
        set_flag16(s1, kSeqFlags, 0x4);
    }
    charge(3);
    v1 = s0 & 0x4;
    if (v1 != 0) {
        charge(3);
        set_flag16(s1, kSeqFlags, 0x8);
    }
    charge(3);
    v1 = s0 & 0x8;
    if (v1 != 0) {
        charge(3);
        set_flag16(s1, kSeqFlags, 0x10);
    }
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// 0x2B6CD0 sub_2B6CD0(seq): the camera sequence's current step, or 0 (not running, no table, past the table's count or
// past step 3). The step index is +10 (s16), or the next one when there is none yet (-1) or the frame counter +12 has
// reached the step's frames (step +0); the index is not written back. Steps are 60 bytes from table +4.
void Cpu5::sub_2B6CD0() {
    enter(4);
    lhu(v0, a0, kSeqFlags);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(4);
        lw(a2, a0, kSeqTable);
        lh(a3, a0, 10);
        if (a2 == 0) {
            charge(3);
            v0 = 0;
        } else {
            charge(5);
            a1 = dsll32(a3, 16);
            a1 = dsra32(a1, 16);
            v0 = li(-1);
            bool next = a1 == v0;
            if (!next) {
                charge(9);
                lhu(v1, a0, 12);
                v0 = sll(a1, 4);
                v0 = subu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, a2);
                lh(v0, v0, 4);
                v0 = slt(v1, v0);
                next = v0 == 0;
            }
            if (next) {
                charge(3);
                v0 = addiu(a3, 1);
                a3 = dsll32(v0, 16);
                a3 = dsra32(a3, 16);
            }
            charge(6);
            v1 = dsll32(a3, 16);
            v1 = dsra32(v1, 16);
            lhu(v0, a2, 0);
            at = slt(v1, v0);
            if (at == 0) {
                charge(3);
                v0 = 0;
            } else {
                charge(3);
                v0 = slti(v1, 4);
                if (v0 == 0) {
                    charge(3);
                    v0 = 0;
                } else {
                    charge(5);
                    v0 = sll(v1, 4);
                    v0 = subu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(a2, v0);
                    v0 = addiu(v0, 4);
                }
            }
        }
    }
    charge(2);
}

// 0x2B6DB0 sub_2B6DB0(p): memset(p, 0, 20) -- a camera sequence record cleared ($v0 = memset's).
void Cpu5::sub_2B6DB0() {
    enter(10);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    a1 = 0;
    a2 = li(20);
    jal(0x2b6dc0, rg::fn_memset_00521408);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// 0x2B6DE0 sub_2B6DE0(counts): the enemy size census: counts (u16[4]) cleared, then for every living enemy (the list
// gBtl+348 along +2608; datCalcIsDead(DatUnit, 0) == 0) with width w = +140 * scale and height h = +144 * scale:
// w <= 200: h <= 75 -> counts[0]++, h <= 125 -> counts[1]++, h <= 200 -> counts[2]++; 200 < w <= 300: h <= 125 ->
// counts[1]++, h <= 200 -> counts[2]++; w > 300: counts[2]++; and counts[3]++ for each.
void Cpu5::sub_2B6DE0() {
    enter(13);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    a1 = 0;
    a2 = li(8);
    jal(0x2b6dfc, rg::fn_memset_00521408);
    gbtl(v1);
    lw(s0, v1, kGEnemyListA);
    for (;;) {
        charge(2);
        if (s0 == 0) break;
        backedge();
        charge(6);
        lw(a0, s0, kUnitDat);
        a1 = 0;
        jal(0x2b6e1c, rg::fn_datCalcIsDead_0030b5a0);
        if (v0 == 0) {
            charge(11);
            lwc1(F1, s0, kUnitScale);
            lwc1(F0, s0, kUnitHeight);
            mul_s(F3, F0, F1);
            lwc1(F0, s0, kUnitWidth);
            mul_s(F2, F0, F1);
            lif(v1, 0x4348, F1);  // 200.0
            c_le_s(F2, F1);
            if (cc()) {
                charge(6);
                lif(v1, 0x4296, F0);  // 75.0
                c_le_s(F3, F0);
                if (cc()) {
                    charge(5);
                    count16(0);
                } else {
                    charge(6);
                    lif(v1, 0x42fa, F0);  // 125.0
                    c_le_s(F3, F0);
                    if (cc()) {
                        charge(5);
                        count16(2);
                    } else {
                        charge(3);
                        c_le_s(F3, F1);
                        if (cc()) {
                            charge(5);
                            count16(4);
                        }
                    }
                }
            } else {
                charge(6);
                lif(v1, 0x4396, F0);  // 300.0
                c_le_s(F2, F0);
                if (cc()) {
                    charge(6);
                    lif(v1, 0x42fa, F0);  // 125.0
                    c_le_s(F3, F0);
                    if (cc()) {
                        charge(5);
                        count16(2);
                    } else {
                        charge(3);
                        c_le_s(F3, F1);
                        if (cc()) {
                            charge(5);
                            count16(4);
                        }
                    }
                } else {
                    charge(3);
                    count16(4);
                }
            }
            charge(3);
            count16(6);
        }
        charge(1);
        lw(s0, s0, kUnitNextA);
    }
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// 0x2B6F70 sub_2B6F70(counts): the first of the 24 rows of 0x694F10 (224 bytes each; u16 limits at +216 / +218 / +220)
// whose three limits are all >= counts[0..2] (sub_2B6DE0's census), else 23.
void Cpu5::sub_2B6F70() {
    enter(5);
    v0 = 0;
    la(a3, 0x694f10);
    for (;;) {
        charge(4);
        v1 = v0 & 0xffff;
        v1 = sltiu(v1, 24);
        if (v1 == 0) {
            charge(1);
            v0 = li(23);
            break;
        }
        backedge();
        charge(10);
        a1 = v0 & 0xffff;
        v1 = sll(a1, 3);
        v1 = subu(v1, a1);
        v1 = sll(v1, 5);
        a2 = addu(a3, v1);
        lhu(a1, a0, 0);
        lhu(v1, a2, 216);
        at = slt(v1, a1);
        if (at == 0) {
            charge(5);
            lhu(a1, a0, 2);
            lhu(v1, a2, 218);
            at = slt(v1, a1);
            if (at == 0) {
                charge(5);
                lhu(a1, a0, 4);
                lhu(v1, a2, 220);
                at = slt(v1, a1);
                if (at == 0) {
                    charge(2);  // found: $v0 is the row
                    break;
                }
            }
        }
        charge(2);
        v0 = addiu(v0, 1);
        v0 = v0 & 0xffff;
    }
    charge(2);
}

// 0x2B7000 sub_2B7000(unit, slot, value): a side's camera slot: gBtl+2620 + 4 * slot (party) or gBtl+2636 + 4 * slot
// (enemies) = value; any other side byte does nothing.
void Cpu5::sub_2B7000() {
    enter(4);
    lbu(a0, a0, kUnitSide);
    v1 = li(1);
    if (a0 == v1) {
        charge(5);
        gbtl(a0);
        v1 = a1 & 0xffff;
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        sw(a2, v1, kGSideSlots1);
    } else {
        charge(2);
        if (a0 == 0) {
            charge(7);
            gbtl(a0);
            v1 = a1 & 0xffff;
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            sw(a2, v1, kGSideSlots0);
        } else {
            charge(2);
        }
    }
    charge(2);
}

}  // namespace p3fes::game::bcam

namespace p3fes::game {
#define P3FES_BCAM_API_5(name, addr) \
    void name(EEContext& ctx) { bcam::Cpu5(ctx).name(); }
P3FES_BCAM_BODIES_5(P3FES_BCAM_API_5)
#undef P3FES_BCAM_API_5
}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------------
namespace p3fes::recomp_gen {
#define P3FES_BCAM_SHIM_5(name, addr) \
    void fn_##name##_##addr(p3fes::EEContext& ctx) { ::p3fes::game::bcam::Cpu5(ctx).name(); }
P3FES_BCAM_BODIES_5(P3FES_BCAM_SHIM_5)
#undef P3FES_BCAM_SHIM_5
}  // namespace p3fes::recomp_gen
