// The Tartarus shadows' think code ("ene think proc", 0x44AAF0-0x4534B0 and the leaves around it), hand-decompiled from
// SLUS_216.21 (game/include/p3fes/game/tartarus.h; docs/ANALYSIS/27_unmapped_bands.md section 8, 26_field.md 6.4).
// Phase 5 slice `tartarus`: these replace the recompiled bodies listed in game/replaced.txt; tests/game/test_tartarus.cpp
// runs each against its __recomp body. The register view, the cycle model and the call convention:
// game/src/field/tartarus_cpu.h.
//
// One "ene think proc" task per shadow (created by Y_Stratum_CreateEneThinkTask from the field unit band): its work +1 s8 = the unit's
// index in gFldUnitsEc (448-byte records at 0x86EDA0: +72 used, +84 the scene resource, +364 the think task, +368 the
// collision mover task, +396 the behaviour kind), +2 s8 = the think state (3 roam / chase, 4 wander, 5 contact, 6 off),
// +64 s8 paused (sub_4532D0), +65 s8 a flag (sub_4533E0). The movers' action queues (field_lo.h: work +28 count, +32 + 24 i
// entries) are filled through sub_1AFF70 / sub_1B0020 / sub_1B0220 / sub_1B0250 and cleared by sub_1B00C0.
#include "p3fes/game/tartarus.h"

#include "tartarus_cpu.h"

namespace p3fes::recomp_gen {
void fn_K_Field_Get_001b9120(p3fes::EEContext&);
void fn_sub_1AD940_001ad940(p3fes::EEContext&);
void fn_sub_1B0260_001b0260(p3fes::EEContext&);
void fn_sub_1BF220_001bf220(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_K_Battle_CreateBattleTask_001d8b00(p3fes::EEContext&);
void fn_K_Battle_FindTaskOfUnit_001d8d80(p3fes::EEContext&);
void fn_K_FldEvent_IsUnitHero_001c7b10(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datUnitIsGenusDead_002ff790(p3fes::EEContext&);
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);
void fn_sub_1AAAC0_001aaac0(p3fes::EEContext&);
void fn_sub_1B00C0_001b00c0(p3fes::EEContext&);
void fn_sub_1B0240_001b0240(p3fes::EEContext&);
void fn_sub_1C6450_001c6450(p3fes::EEContext&);
void fn_sub_1C65E0_001c65e0(p3fes::EEContext&);
void fn_sub_1C6D70_001c6d70(p3fes::EEContext&);
void fn_sub_1C6DD0_001c6dd0(p3fes::EEContext&);
void fn_sub_1C7130_001c7130(p3fes::EEContext&);
void fn_sub_1D8E60_001d8e60(p3fes::EEContext&);
void fn_sub_318B60_00318b60(p3fes::EEContext&);
void fn_sub_435060_00435060(p3fes::EEContext&);
void fn_sub_437E20_00437e20(p3fes::EEContext&);
void fn_sub_43A1A0_0043a1a0(p3fes::EEContext&);
void fn_sub_44F060_0044f060(p3fes::EEContext&);
void fn_sub_44F120_0044f120(p3fes::EEContext&);
void fn_sub_44F170_0044f170(p3fes::EEContext&);
void fn_sub_4532D0_004532d0(p3fes::EEContext&);
void fn_sub_4543C0_004543c0(p3fes::EEContext&);
void fn_sub_454400_00454400(p3fes::EEContext&);
void fn_sub_454D00_00454d00(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
void fn_K_FldFrame_CtlGetXGrid_001ad910(p3fes::EEContext&);
void fn_K_FldFrame_CtlGetZGrid_001ad920(p3fes::EEContext&);
void fn_K_Scene_IsRandomFloor_001a0250(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_1A02C0_001a02c0(p3fes::EEContext&);
void fn_sub_1A91B0_001a91b0(p3fes::EEContext&);
void fn_sub_1A9390_001a9390(p3fes::EEContext&);
void fn_sub_1ACC30_001acc30(p3fes::EEContext&);
void fn_sub_1AFA20_001afa20(p3fes::EEContext&);
void fn_sub_1AFF70_001aff70(p3fes::EEContext&);
void fn_sub_1B0020_001b0020(p3fes::EEContext&);
void fn_sub_1B0220_001b0220(p3fes::EEContext&);
void fn_sub_1B0250_001b0250(p3fes::EEContext&);
void fn_sub_1C7160_001c7160(p3fes::EEContext&);
void fn_sub_43C910_0043c910(p3fes::EEContext&);
void fn_sub_44AF60_0044af60(p3fes::EEContext&);
void fn_sub_44B7D0_0044b7d0(p3fes::EEContext&);
void fn_sub_44BEB0_0044beb0(p3fes::EEContext&);
void fn_sub_44D600_0044d600(p3fes::EEContext&);
void fn_sub_44DFC0_0044dfc0(p3fes::EEContext&);
void fn_sub_44E560_0044e560(p3fes::EEContext&);
void fn_sub_44F1C0_0044f1c0(p3fes::EEContext&);
void fn_sub_44F270_0044f270(p3fes::EEContext&);
void fn_sub_44F300_0044f300(p3fes::EEContext&);
void fn_sub_44FAB0_0044fab0(p3fes::EEContext&);
void fn_sub_44FFB0_0044ffb0(p3fes::EEContext&);
void fn_sub_4501B0_004501b0(p3fes::EEContext&);
void fn_sub_450B30_00450b30(p3fes::EEContext&);
void fn_sub_4514A0_004514a0(p3fes::EEContext&);
void fn_sub_451D70_00451d70(p3fes::EEContext&);
void fn_sub_4523C0_004523c0(p3fes::EEContext&);
void fn_sub_452A70_00452a70(p3fes::EEContext&);
void fn_sub_4534B0_004534b0(p3fes::EEContext&);
void fn_sub_453D90_00453d90(p3fes::EEContext&);
void fn_sub_453ED0_00453ed0(p3fes::EEContext&);
void fn_sub_454110_00454110(p3fes::EEContext&);
void fn_Y_Stratum_CreateEneDeadEffectTask_004542c0(p3fes::EEContext&);
void fn_sub_454520_00454520(p3fes::EEContext&);
void fn_sub_454620_00454620(p3fes::EEContext&);
void fn_sub_454F50_00454f50(p3fes::EEContext&);
void fn_Y_Kyoto_CreateWaitTask_00459f60(p3fes::EEContext&);
// @@CALLEES@@
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

namespace gen = ::p3fes::recomp_gen;
using namespace tartarus;
using namespace tart;

struct EneLeaves : Cpu {
    using Cpu::Cpu;

    // 0x44E530 (unit, kind): the think work of a field unit (+364 -> +60): +2 = 5 (contact), +5 = 2, +24 = kind.
    void sub_44E530() {
        enter(9);
        v1 = lw(a0, 364);
        a0 = lw(v1, kTaskWork);
        v1 = si(5);
        sb(a0, 2, v1);
        v1 = si(2);
        sb(a0, 5, v1);
        sb(a0, 24, a1);
    }

    // 0x44F060 (task, pos; $f12 = the distance): pos copied to sp+64, the position of the shadow's model (gFldUnitsEc[work
    // +1] +360 -> +256..) minus it into sp+48, 1 when RwV3dLength (sub_4C6AC0) of that is below $f12, else 0.
    void sub_44F060() {
        enter(39);
        sp = addiu(sp, -80);
        sd(sp, 32, ra);
        sq(s0, sp, 16);
        swc1(20, sp, 0);
        mov_s(20, 12);
        lwc1(2, a1, 0);
        lwc1(1, a1, 4);
        lwc1(0, a1, 8);
        swc1(2, sp, 64);
        swc1(1, sp, 68);
        swc1(0, sp, 72);
        v0 = lw(a0, kTaskWork);
        s0 = 0;
        v1 = lb(v0, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4344);  // 0x86EF08
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        lwc1(1, v0, 256);
        lwc1(0, sp, 64);
        sub_s(0, 1, 0);
        swc1(0, sp, 48);
        lwc1(1, v0, 260);
        lwc1(0, sp, 68);
        sub_s(0, 1, 0);
        swc1(0, sp, 52);
        lwc1(1, v0, 264);
        lwc1(0, sp, 72);
        sub_s(0, 1, 0);
        swc1(0, sp, 56);
        a0 = addiu(sp, 48);
        jal(0x44F0E8u, &gen::fn_sub_4C6AC0_004c6ac0);
        c_lt_s(0, 20);
        if (cond()) {
            charge(1);
            s0 = si(1);
        }
        charge(7);
        v0 = s0;
        ra = ld(sp, 32);
        lq(s0, sp, 16);
        lwc1(20, sp, 0);
        sp = addiu(sp, 80);
    }

    // 0x44F120 (pos): the 800-unit grid column of a world position, (int)((x + 400) / 800) (cvt.w truncates).
    void sub_44F120() {
        enter(20);
        sp = addiu(sp, -16);
        lwc1(2, a0, 0);
        lwc1(1, a0, 4);
        lwc1(0, a0, 8);
        swc1(2, sp, 0);
        swc1(1, sp, 4);
        swc1(0, sp, 8);
        v0 = lui(0x43C8u);
        mtc1(v0, 1);  // 400.0
        lwc1(0, sp, 0);
        add_s(1, 1, 0);
        v0 = lui(0x4448u);
        mtc1(v0, 0);  // 800.0
        div_s(0, 1, 0);
        cvt_w_s(0, 0);
        mfc1(v0, 0);
        sp = addiu(sp, 16);
    }

    // 0x44F170 (pos): the grid row, (int)((z + 400) / 800).
    void sub_44F170() {
        enter(20);
        sp = addiu(sp, -16);
        lwc1(2, a0, 0);
        lwc1(1, a0, 4);
        lwc1(0, a0, 8);
        swc1(2, sp, 0);
        swc1(1, sp, 4);
        swc1(0, sp, 8);
        v0 = lui(0x43C8u);
        mtc1(v0, 1);  // 400.0
        lwc1(0, sp, 8);
        add_s(1, 1, 0);
        v0 = lui(0x4448u);
        mtc1(v0, 0);  // 800.0
        div_s(0, 1, 0);
        cvt_w_s(0, 0);
        mfc1(v0, 0);
        sp = addiu(sp, 16);
    }

    // 0x44F1C0 (a, b; $f12 = the distance): both positions copied to the frame (sp+80 / sp+64), their difference to sp+48,
    // 1 when its length (sub_4C6AC0) is below $f12.
    void sub_44F1C0() {
        enter(36);
        sp = addiu(sp, -96);
        sd(sp, 32, ra);
        sq(s0, sp, 16);
        swc1(20, sp, 0);
        mov_s(20, 12);
        lwc1(2, a0, 0);
        lwc1(1, a0, 4);
        lwc1(0, a0, 8);
        swc1(2, sp, 80);
        swc1(1, sp, 84);
        swc1(0, sp, 88);
        lwc1(2, a1, 0);
        lwc1(1, a1, 4);
        lwc1(0, a1, 8);
        swc1(2, sp, 64);
        swc1(1, sp, 68);
        swc1(0, sp, 72);
        s0 = 0;
        lwc1(1, sp, 80);
        lwc1(0, sp, 64);
        sub_s(0, 1, 0);
        swc1(0, sp, 48);
        lwc1(1, sp, 84);
        lwc1(0, sp, 68);
        sub_s(0, 1, 0);
        swc1(0, sp, 52);
        lwc1(1, sp, 88);
        lwc1(0, sp, 72);
        sub_s(0, 1, 0);
        swc1(0, sp, 56);
        a0 = addiu(sp, 48);
        jal(0x44F23Cu, &gen::fn_sub_4C6AC0_004c6ac0);
        c_lt_s(0, 20);
        if (cond()) {
            charge(1);
            s0 = si(1);
        }
        charge(7);
        v0 = s0;
        ra = ld(sp, 32);
        lq(s0, sp, 16);
        lwc1(20, sp, 0);
        sp = addiu(sp, 96);
    }

    // 0x44F270 (a, b): $f0 = the length (sub_4C6AC0) of a - b (both copied into the 64-byte frame, $ra at sp+0).
    void sub_44F270() {
        enter(33);
        sp = addiu(sp, -64);
        sd(sp, 0, ra);
        lwc1(2, a0, 0);
        lwc1(1, a0, 4);
        lwc1(0, a0, 8);
        swc1(2, sp, 48);
        swc1(1, sp, 52);
        swc1(0, sp, 56);
        lwc1(2, a1, 0);
        lwc1(1, a1, 4);
        lwc1(0, a1, 8);
        swc1(2, sp, 32);
        swc1(1, sp, 36);
        swc1(0, sp, 40);
        lwc1(1, sp, 48);
        lwc1(0, sp, 32);
        sub_s(0, 1, 0);
        swc1(0, sp, 16);
        lwc1(1, sp, 52);
        lwc1(0, sp, 36);
        sub_s(0, 1, 0);
        swc1(0, sp, 20);
        lwc1(1, sp, 56);
        lwc1(0, sp, 40);
        sub_s(0, 1, 0);
        swc1(0, sp, 24);
        a0 = addiu(sp, 16);
        jal(0x44F2DCu, &gen::fn_sub_4C6AC0_004c6ac0);
        ra = ld(sp, 0);
        sp = addiu(sp, 64);
    }

    // 0x4532D0 (paused): for every used shadow (gFldUnitsEc[i] +72 and +84 set): its think work (+364 -> +60) +64 = paused,
    // and sub_1B0260(the mover task of the unit named by that work's +1, paused) (field_lo: sets / clears the mover's pause).
    void sub_4532D0() {
        enter(11);
        sp = addiu(sp, -64);
        sd(sp, 48, ra);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s2 = a0;
        s1 = 0;
        s0 = dsll32(s2, 24);
        s0 = dsra32(s0, 24);
        for (;;) {
            charge(3);
            v1 = slti(s1, 24);
            if (v1 == 0) break;
            backedge();
            charge(10);
            a1 = 0;
            v1 = sll(s1, 3);
            v1 = subu(v1, s1);
            a0 = sll(v1, 6);
            v1 = lui(0x87u);
            v1 = addiu(v1, -4704);  // 0x86EDA0 gFldUnitsEc
            a0 = addu(v1, a0);
            v1 = lw(a0, 72);
            if (v1 != 0) {
                charge(3);
                v1 = lw(a0, 84);
                if (v1 != 0) {
                    charge(1);
                    a1 = si(1);
                }
            }
            charge(4);
            v1 = sltu(zero, a1);
            a1 = si(1);
            if (v1 == a1) {
                charge(5);
                v0 = lw(a0, 364);
                v0 = lw(v0, kTaskWork);
                sb(v0, 64, s2);
                if (s0 == 0) {
                    charge(13);
                    v1 = lb(v0, 1);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                    v0 = addu(v0, v1);
                    a0 = lw(v0, 368);
                    a1 = 0;
                    jal(0x45337Cu, &gen::fn_sub_1B0260_001b0260);
                } else {
                    charge(10);
                    v1 = lb(v0, 1);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                    v0 = addu(v0, v1);
                    a0 = lw(v0, 368);
                    jal(0x4533ACu, &gen::fn_sub_1B0260_001b0260);
                }
            }
            charge(1);
            s1 = addiu(s1, 1);
        }
        charge(7);
        ra = ld(sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 64);
    }

    // 0x4533E0 (flag): for every used shadow, its think work +65 = flag.
    void sub_4533E0() {
        enter(6);
        a5 = 0;
        a1 = si(1);
        a3 = lui(0x87u);
        a3 = addiu(a3, -4704);  // 0x86EDA0 gFldUnitsEc
        for (;;) {
            charge(3);
            v1 = slti(a5, 24);
            if (v1 == 0) break;
            backedge();
            charge(8);
            a4 = 0;
            v1 = sll(a5, 3);
            v1 = subu(v1, a5);
            v1 = sll(v1, 6);
            a2 = addu(a3, v1);
            v1 = lw(a2, 72);
            if (v1 != 0) {
                charge(3);
                v1 = lw(a2, 84);
                if (v1 != 0) {
                    charge(1);
                    a4 = a1;
                }
            }
            charge(3);
            v1 = sltu(zero, a4);
            if (v1 == a1) {
                charge(3);
                v1 = lw(a2, 364);
                v1 = lw(v1, kTaskWork);
                sb(v1, 65, a0);
            }
            charge(1);
            a5 = addiu(a5, 1);
        }
        charge(2);
    }

    // 0x453460: $v0 = the s16 at gp-0x45FC.
    void sub_453460() {
        enter(3);
        v0 = lh(gp, -17916);
    }

    // 0x453470 (value): the s16 at gp-0x45FC = value.
    void sub_453470() {
        enter(3);
        sh(gp, -17916, a0);
    }

    // 0x453480: $v0 = the s8 at gp-0x4600.
    void sub_453480() {
        enter(3);
        v0 = lb(gp, -17920);
    }

    // 0x453490 (task): its work's first byte = 6.
    void sub_453490() {
        enter(5);
        a1 = si(6);
        v1 = lw(a0, kTaskWork);
        sb(v1, 0, a1);
    }

    // 0x4514A0 (ec): a breadth-first walk of the grid from shadow ec's cell towards the player's: the 256-cell visited map
    // (sp+... u16[256]) and two 256-entry frontier lists live in the frame; when both stand in the same cell the best open
    // side by the direction to the player (RwV3dNormalize, sub_4C69F0) gives the first step. The walk is cut after (3 * the
    // behaviour record's +0 range (gp-0x4A60 + 64 * unit +396)) / 800 rounds. Returns 0 when no step was found (or the step
    // is the start), else 1 with the step's cell x / z at the think work's +139 / +140.
    void sub_4514A0() {
        enter(125);
        sp = addiu(sp, -1920);
        sd(sp, 160, ra);
        sq(fp, sp, 144);
        sq(s7, sp, 128);
        sq(s6, sp, 112);
        sq(s5, sp, 96);
        sq(s4, sp, 80);
        sq(s3, sp, 64);
        sq(s2, sp, 48);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(21, sp, 4);
        swc1(20, sp, 0);
        v1 = dsll32(a0, 24);
        v1 = dsra32(v1, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        a0 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4340);  // 0x86EF0C
        v0 = addu(v0, a0);
        v0 = lw(v0, 0);
        v0 = lw(v0, kTaskWork);
        sq(v0, sp, 208);
        mtc1(zero, 21);
        sh(sp, 224, zero);
        fp = si(1);
        s3 = si(-1);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4308);  // 0x86EF2C
        v0 = addu(v0, a0);
        v0 = lw(v0, 0);
        v1 = sll(v0, 6);
        v0 = lw(gp, -19040);
        s0 = addu(v0, v1);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4620);  // 0x86EDF4
        v0 = addu(v0, a0);
        v0 = lw(v0, 0);
        a0 = addiu(sp, 1888);
        a1 = lw(v0, kResController);
        jal(0x451544u, &gen::fn_sub_1AD940_001ad940);
        lq(v0, sp, 208);
        v1 = lb(v0, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, 6132);  // 0x8717F4
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        a0 = addiu(sp, 1872);
        a1 = lw(v0, kResController);
        jal(0x451578u, &gen::fn_sub_1AD940_001ad940);
        sw(sp, 1876, zero);
        v0 = ld(sp, 1888);
        lwc1(0, sp, 1896);
        sd(sp, 1792, v0);
        swc1(0, sp, 1800);
        v1 = ld(sp, 1792);
        lwc1(1, sp, 1800);
        sd(sp, 1856, v1);
        swc1(1, sp, 1864);
        v0 = lui(0x43C8u);
        mtc1(v0, 3);  // 400.0
        lwc1(0, sp, 1856);
        add_s(0, 3, 0);
        v0 = lui(0x4448u);
        mtc1(v0, 2);  // 800.0
        div_s(0, 0, 2);
        cvt_w_s(0, 0);
        mfc1(v0, 0);
        s5 = dsll32(v0, 16);
        s5 = dsra32(s5, 16);
        sd(sp, 1840, v1);
        swc1(1, sp, 1848);
        add_s(0, 3, 1);
        div_s(0, 0, 2);
        cvt_w_s(0, 0);
        mfc1(v0, 0);
        s4 = dsll32(v0, 16);
        s4 = dsra32(s4, 16);
        v0 = ld(sp, 1872);
        lwc1(0, sp, 1880);
        sd(sp, 1776, v0);
        swc1(0, sp, 1784);
        v1 = ld(sp, 1776);
        lwc1(1, sp, 1784);
        sd(sp, 1808, v1);
        swc1(1, sp, 1816);
        add_s(0, 3, 1);
        div_s(0, 0, 2);
        cvt_w_s(0, 0);
        mfc1(v0, 0);
        sd(sp, 1824, v1);
        swc1(1, sp, 1832);
        lwc1(0, sp, 1824);
        add_s(0, 3, 0);
        div_s(0, 0, 2);
        cvt_w_s(0, 0);
        mfc1(v1, 0);
        v0 = sll(v0, 4);
        v0 = addu(v1, v0);
        a0 = dsll32(v0, 16);
        a0 = dsra32(a0, 16);
        v0 = lui(0x4040u);
        mtc1(v0, 1);  // 3.0
        lwc1(0, s0, 0);
        mul_s(0, 1, 0);
        div_s(0, 0, 2);
        cvt_w_s(0, 0);
        mfc1(v0, 0);
        v0 = dsll32(v0, 16);
        v0 = dsra32(v0, 16);
        sq(v0, sp, 192);
        a1 = 0;
        v1 = s3;
        for (;;) {
            charge(3);
            v0 = slti(a1, 256);
            if (v0 == 0) break;
            backedge();
            charge(6);
            v0 = sll(a1, 1);
            v0 = addu(v0, sp);
            sh(v0, 752, zero);
            sh(v0, 1264, v1);
            sh(v0, 240, zero);
            a1 = addiu(a1, 1);
        }
        charge(10);
        s1 = dsll32(s4, 16);
        s1 = dsra32(s1, 16);
        s0 = dsll32(s5, 16);
        s0 = dsra32(s0, 16);
        s2 = dsll32(a0, 16);
        s2 = dsra32(s2, 16);
        v0 = sll(s1, 4);
        v0 = addu(s0, v0);
        if (s2 == v0) {
            charge(10);
            s6 = sll(s1, 8);
            s7 = sll(s0, 4);
            jal(0x4516E8u, &gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s6);
            v0 = addu(v0, s7);
            v0 = lbu(v0, 83);
            v0 = v0 & 0x1u;
            if (v0 != 0) {
                charge(29);
                v0 = lui(0x4448u);
                mtc1(v0, 1);  // 800.0
                mtc1(s5, 0);
                cvt_s_w(0, 0);
                mul_s(2, 1, 0);
                v0 = addiu(s1, -1);
                mtc1(v0, 0);
                cvt_s_w(0, 0);
                mul_s(1, 1, 0);
                lwc1(0, sp, 1872);
                sub_s(0, 2, 0);
                swc1(0, sp, 1904);
                lwc1(0, sp, 1876);
                sub_s(0, 20, 0);
                swc1(0, sp, 1908);
                lwc1(0, sp, 1880);
                sub_s(0, 1, 0);
                swc1(0, sp, 1912);
                a0 = addiu(sp, 1904);
                a1 = a0;
                jal(0x451760u, &gen::fn_sub_4C69F0_004c69f0);
                mtc1(zero, 1);
                c_lt_s(1, 0);
                if (cond()) {
                    charge(2);
                    mov_s(21, 0);
                    s3 = si(1);
                }
            }
            charge(8);
            jal(0x451784u, &gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s6);
            v0 = addu(v0, s7);
            v0 = lbu(v0, 83);
            v0 = v0 & 0x2u;
            if (v0 != 0) {
                charge(28);
                v0 = addiu(s0, -1);
                mtc1(v0, 0);
                cvt_s_w(0, 0);
                v0 = lui(0x4448u);
                mtc1(v0, 1);  // 800.0
                mul_s(2, 1, 0);
                mtc1(s4, 0);
                cvt_s_w(0, 0);
                mul_s(1, 1, 0);
                lwc1(0, sp, 1872);
                sub_s(0, 2, 0);
                swc1(0, sp, 1904);
                lwc1(0, sp, 1876);
                sub_s(0, 20, 0);
                swc1(0, sp, 1908);
                lwc1(0, sp, 1880);
                sub_s(0, 1, 0);
                swc1(0, sp, 1912);
                a0 = addiu(sp, 1904);
                a1 = a0;
                jal(0x451800u, &gen::fn_sub_4C69F0_004c69f0);
                c_lt_s(21, 0);
                if (cond()) {
                    charge(2);
                    mov_s(21, 0);
                    s3 = si(2);
                }
            }
            charge(8);
            jal(0x45181Cu, &gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s6);
            v0 = addu(v0, s7);
            v0 = lbu(v0, 83);
            v0 = v0 & 0x8u;
            if (v0 != 0) {
                charge(28);
                v0 = addiu(s0, 1);
                mtc1(v0, 0);
                cvt_s_w(0, 0);
                v0 = lui(0x4448u);
                mtc1(v0, 1);  // 800.0
                mul_s(2, 1, 0);
                mtc1(s4, 0);
                cvt_s_w(0, 0);
                mul_s(1, 1, 0);
                lwc1(0, sp, 1872);
                sub_s(0, 2, 0);
                swc1(0, sp, 1904);
                lwc1(0, sp, 1876);
                sub_s(0, 20, 0);
                swc1(0, sp, 1908);
                lwc1(0, sp, 1880);
                sub_s(0, 1, 0);
                swc1(0, sp, 1912);
                a0 = addiu(sp, 1904);
                a1 = a0;
                jal(0x451898u, &gen::fn_sub_4C69F0_004c69f0);
                c_lt_s(21, 0);
                if (cond()) {
                    charge(2);
                    mov_s(21, 0);
                    s3 = si(3);
                }
            }
            charge(8);
            jal(0x4518B4u, &gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s6);
            v0 = addu(v0, s7);
            v0 = lbu(v0, 83);
            v0 = v0 & 0x4u;
            if (v0 != 0) {
                charge(27);
                v0 = lui(0x4448u);
                mtc1(v0, 1);  // 800.0
                mtc1(s5, 0);
                cvt_s_w(0, 0);
                mul_s(2, 1, 0);
                v0 = addiu(s1, 1);
                mtc1(v0, 0);
                cvt_s_w(0, 0);
                mul_s(1, 1, 0);
                lwc1(0, sp, 1872);
                sub_s(0, 2, 0);
                swc1(0, sp, 1904);
                lwc1(0, sp, 1876);
                sub_s(0, 20, 0);
                swc1(0, sp, 1908);
                lwc1(0, sp, 1880);
                sub_s(0, 1, 0);
                swc1(0, sp, 1912);
                a0 = addiu(sp, 1904);
                a1 = a0;
                jal(0x45192Cu, &gen::fn_sub_4C69F0_004c69f0);
                c_lt_s(21, 0);
                if (cond()) {
                    charge(1);
                    s3 = si(4);
                }
            }
            charge(5);
            v1 = dsll32(s3, 16);
            v1 = dsra32(v1, 16);
            v0 = si(-1);
            if (v1 == v0) {
                charge(3);
                v0 = 0;
                goto L_00451d2c;
            }
            charge(3);
            v0 = si(4);
            if (v1 != v0) {
                charge(3);
                v0 = si(3);
                if (v1 != v0) {
                    charge(3);
                    v0 = si(2);
                    if (v1 != v0) {
                        charge(3);
                        v0 = si(1);
                        if (v1 != v0) {
                            charge(2);
                        } else {
                            charge(5);
                            v0 = addiu(s4, -1);
                            s4 = dsll32(v0, 16);
                            s4 = dsra32(s4, 16);
                        }
                    } else {
                        charge(5);
                        v0 = addiu(s5, -1);
                        s5 = dsll32(v0, 16);
                        s5 = dsra32(s5, 16);
                    }
                } else {
                    charge(5);
                    v0 = addiu(s5, 1);
                    s5 = dsll32(v0, 16);
                    s5 = dsra32(s5, 16);
                }
            } else {
                charge(3);
                v0 = addiu(s4, 1);
                s4 = dsll32(v0, 16);
                s4 = dsra32(s4, 16);
            }
        }
        charge(17);
        v0 = dsll32(s4, 16);
        v0 = dsra32(v0, 16);
        v1 = sll(v0, 4);
        v0 = dsll32(s5, 16);
        v0 = dsra32(v0, 16);
        s6 = addu(v0, v1);
        v0 = dsll32(s6, 16);
        v0 = dsra32(v0, 16);
        sh(sp, 752, s6);
        v1 = si(1);
        v0 = sll(v0, 1);
        v0 = addu(v0, sp);
        sh(v0, 240, v1);
        lq(v0, sp, 192);
        v0 = dsll32(v0, 16);
        v0 = dsra32(v0, 16);
        sq(v0, sp, 176);
        for (;;) {
            charge(6);
            s5 = 0;
            s4 = 0;
            s7 = dsll32(fp, 16);
            s7 = dsra32(s7, 16);
            for (;;) {
                charge(3);
                v0 = slt(s4, s7);
                if (v0 == 0) break;
                backedge();
                charge(6);
                v0 = sll(s4, 1);
                v0 = addu(v0, sp);
                s3 = lh(v0, 752);
                v0 = sra(s3, 4);
                if (ltz(s3)) {
                    charge(2);
                    v0 = addiu(s3, 15);
                    v0 = sra(v0, 4);
                }
                charge(4);
                s1 = sll(v0, 8);
                v0 = s3 & 0xFu;
                if (ltz(s3)) {
                    charge(2);
                    if (v0 != 0) {
                        charge(1);
                        v0 = addiu(v0, -16);
                    }
                }
                charge(9);
                s0 = sll(v0, 4);
                jal(0x451A80u, &gen::fn_K_Field_Get_001b9120);
                v0 = addu(v0, s1);
                v0 = addu(v0, s0);
                v0 = lbu(v0, 83);
                v0 = v0 & 0x1u;
                if (v0 != 0) {
                    charge(7);
                    v0 = sll(s3, 1);
                    v0 = addu(v0, sp);
                    v0 = addiu(v0, 240);
                    a0 = addiu(v0, -32);
                    v0 = lh(v0, -32);
                    if (v0 == 0) {
                        charge(3);
                        v1 = addiu(s3, -16);
                        if (s2 != v1) {
                            charge(10);
                            v0 = dsll32(s5, 16);
                            v0 = dsra32(v0, 16);
                            v0 = sll(v0, 1);
                            v0 = addu(v0, sp);
                            sh(v0, 1264, v1);
                            v0 = addiu(s5, 1);
                            s5 = dsll32(v0, 16);
                            s5 = dsra32(s5, 16);
                            v0 = si(1);
                            sh(a0, 0, v0);
                        }
                    }
                }
                charge(8);
                jal(0x451AF0u, &gen::fn_K_Field_Get_001b9120);
                v0 = addu(v0, s1);
                v0 = addu(v0, s0);
                v0 = lbu(v0, 83);
                v0 = v0 & 0x8u;
                if (v0 != 0) {
                    charge(7);
                    v0 = sll(s3, 1);
                    v0 = addu(v0, sp);
                    v0 = addiu(v0, 240);
                    a0 = addiu(v0, 2);
                    v0 = lh(v0, 2);
                    if (v0 == 0) {
                        charge(3);
                        v1 = addiu(s3, 1);
                        if (s2 != v1) {
                            charge(10);
                            v0 = dsll32(s5, 16);
                            v0 = dsra32(v0, 16);
                            v0 = sll(v0, 1);
                            v0 = addu(v0, sp);
                            sh(v0, 1264, v1);
                            v0 = addiu(s5, 1);
                            s5 = dsll32(v0, 16);
                            s5 = dsra32(s5, 16);
                            v0 = si(1);
                            sh(a0, 0, v0);
                        }
                    }
                }
                charge(8);
                jal(0x451B60u, &gen::fn_K_Field_Get_001b9120);
                v0 = addu(v0, s1);
                v0 = addu(v0, s0);
                v0 = lbu(v0, 83);
                v0 = v0 & 0x2u;
                if (v0 != 0) {
                    charge(7);
                    v0 = sll(s3, 1);
                    v0 = addu(v0, sp);
                    v0 = addiu(v0, 240);
                    a0 = addiu(v0, -2);
                    v0 = lh(v0, -2);
                    if (v0 == 0) {
                        charge(3);
                        v1 = addiu(s3, -1);
                        if (s2 != v1) {
                            charge(10);
                            v0 = dsll32(s5, 16);
                            v0 = dsra32(v0, 16);
                            v0 = sll(v0, 1);
                            v0 = addu(v0, sp);
                            sh(v0, 1264, v1);
                            v0 = addiu(s5, 1);
                            s5 = dsll32(v0, 16);
                            s5 = dsra32(s5, 16);
                            v0 = si(1);
                            sh(a0, 0, v0);
                        }
                    }
                }
                charge(8);
                jal(0x451BD0u, &gen::fn_K_Field_Get_001b9120);
                v0 = addu(v0, s1);
                v0 = addu(v0, s0);
                v0 = lbu(v0, 83);
                v0 = v0 & 0x4u;
                if (v0 != 0) {
                    charge(7);
                    v0 = sll(s3, 1);
                    v0 = addu(v0, sp);
                    v0 = addiu(v0, 240);
                    a0 = addiu(v0, 32);
                    v0 = lh(v0, 32);
                    if (v0 == 0) {
                        charge(3);
                        v1 = addiu(s3, 16);
                        if (s2 != v1) {
                            charge(10);
                            v0 = dsll32(s5, 16);
                            v0 = dsra32(v0, 16);
                            v0 = sll(v0, 1);
                            v0 = addu(v0, sp);
                            sh(v0, 1264, v1);
                            v0 = addiu(s5, 1);
                            s5 = dsll32(v0, 16);
                            s5 = dsra32(s5, 16);
                            v0 = si(1);
                            sh(a0, 0, v0);
                        }
                    }
                }
                charge(1);
                s4 = addiu(s4, 1);
            }
            charge(6);
            fp = dsll32(s5, 16);
            fp = dsra32(fp, 16);
            a2 = 0;
            a0 = si(-1);
            for (;;) {
                charge(3);
                v0 = slt(a2, fp);
                if (v0 == 0) break;
                backedge();
                charge(9);
                v0 = sll(a2, 1);
                v0 = addu(v0, sp);
                a1 = addiu(v0, 752);
                sh(a1, 0, a0);
                v1 = addiu(v0, 1264);
                v0 = lh(v1, 0);
                sh(a1, 0, v0);
                sh(v1, 0, a0);
                a2 = addiu(a2, 1);
            }
            charge(10);
            v0 = lh(sp, 224);
            v0 = addiu(v0, 1);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            sh(sp, 224, v0);
            v1 = v0;
            lq(v0, sp, 176);
            v0 = slt(v1, v0);
            if (v0 == 0) {
                charge(1);
                s5 = 0;
            }
            charge(4);
            v0 = dsll32(s5, 16);
            v0 = dsra32(v0, 16);
            if (v0 == 0) break;
            backedge();
        }
        charge(3);
        a0 = lh(sp, 752);
        if (a0 == s6) {
            charge(3);
            v0 = 0;
        } else {
            charge(3);
            v1 = a0 & 0xFu;
            if (ltz(a0)) {
                charge(2);
                if (v1 != 0) {
                    charge(1);
                    v1 = addiu(v1, -16);
                }
            }
            charge(5);
            lq(v0, sp, 208);
            sb(v0, 139, v1);
            v1 = sra(a0, 4);
            if (ltz(a0)) {
                charge(2);
                v0 = addiu(a0, 15);
                v1 = sra(v0, 4);
            }
            charge(3);
            lq(v0, sp, 208);
            sb(v0, 140, v1);
            v0 = si(1);
        }
      L_00451d2c:
        charge(15);
        ra = ld(sp, 160);
        lq(fp, sp, 144);
        lq(s7, sp, 128);
        lq(s6, sp, 112);
        lq(s5, sp, 96);
        lq(s4, sp, 80);
        lq(s3, sp, 64);
        lq(s2, sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(21, sp, 4);
        lwc1(20, sp, 0);
        sp = addiu(sp, 1920);
    }

    // 0x452010 (pos): from pos's cell (x0, z0), over i, j < 16, the cells (x0 + i, z0 + j) and (x0 - i, z0 - j)... as
    // compiled: x = x0 + i with z0 + j, and x0 - i with z0 - j, inside the grid, room byte +0 == 1 and kind (+2) != 8; the
    // one with the largest i + j (later wins ties) becomes pos = {800 x, 0, 800 z}; none leaves pos as it was (copied
    // through the frame). Called by the enemy pop scheduler for the Reaper (field_big.cpp).
    void sub_452010() {
        enter(55);
        sp = addiu(sp, -336);
        sd(sp, 144, ra);
        sq(fp, sp, 128);
        sq(s7, sp, 112);
        sq(s6, sp, 96);
        sq(s5, sp, 80);
        sq(s4, sp, 64);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s5 = a0;
        v0 = lui(0x87u);
        v0 = lw(v0, 6132);  // 0x8717F4
        a0 = addiu(sp, 288);
        a1 = lw(v0, kResController);
        jal(0x452050u, &gen::fn_sub_1AD940_001ad940);
        lwc1(2, sp, 288);
        lwc1(1, sp, 292);
        lwc1(0, sp, 296);
        swc1(2, sp, 320);
        swc1(1, sp, 324);
        swc1(0, sp, 328);
        s2 = 0;
        a0 = ld(sp, 320);
        lwc1(3, sp, 328);
        sd(sp, 272, a0);
        swc1(3, sp, 280);
        v1 = lui(0x43C8u);
        mtc1(v1, 2);  // 400.0
        lwc1(0, sp, 272);
        add_s(0, 2, 0);
        v1 = lui(0x4448u);
        mtc1(v1, 1);  // 800.0
        div_s(0, 0, 1);
        cvt_w_s(0, 0);
        mfc1(v1, 0);
        v1 = dsll32(v1, 24);
        v1 = dsra32(v1, 24);
        sq(v1, sp, 224);
        sd(sp, 256, a0);
        swc1(3, sp, 264);
        add_s(0, 2, 3);
        div_s(0, 0, 1);
        cvt_w_s(0, 0);
        mfc1(v1, 0);
        s1 = dsll32(v1, 24);
        s1 = dsra32(s1, 24);
        s4 = 0;
        for (;;) {
            charge(3);
            v1 = slti(s4, 16);
            if (v1 == 0) break;
            backedge();
            charge(17);
            s3 = 0;
            lq(v1, sp, 224);
            v1 = addu(v1, s4);
            sq(v1, sp, 208);
            s0 = dsll32(v1, 24);
            s0 = dsra32(s0, 24);
            v1 = sll(s0, 4);
            sq(v1, sp, 192);
            lq(v1, sp, 224);
            v1 = subu(v1, s4);
            sq(v1, sp, 176);
            s6 = dsll32(v1, 24);
            s6 = dsra32(s6, 24);
            v1 = sll(s6, 4);
            sq(v1, sp, 160);
            for (;;) {
                charge(3);
                v1 = slti(s3, 16);
                if (v1 == 0) break;
                backedge();
                charge(2);
                if (gez(s0)) {
                    charge(3);
                    at = slti(s0, 16);
                    if (at != 0) {
                        charge(5);
                        v1 = addu(s1, s3);
                        v1 = dsll32(v1, 24);
                        v1 = dsra32(v1, 24);
                        if (gez(v1)) {
                            charge(3);
                            at = slti(v1, 16);
                            if (at != 0) {
                                charge(10);
                                s7 = sll(v1, 8);
                                jal(0x452168u, &gen::fn_K_Field_Get_001b9120);
                                lq(v1, sp, 192);
                                v1 = addu(v1, v0);
                                v1 = addu(v1, s7);
                                a0 = lbu(v1, 72);
                                v1 = si(1);
                                if (a0 == v1) {
                                    charge(9);
                                    jal(0x45218Cu, &gen::fn_K_Field_Get_001b9120);
                                    lq(v1, sp, 192);
                                    v1 = addu(v1, v0);
                                    v1 = addu(v1, s7);
                                    a0 = lbu(v1, 74);
                                    v1 = si(8);
                                    if (a0 != v1) {
                                        charge(3);
                                        v1 = si(1);
                                        goto L_004521c0;
                                    }
                                }
                            }
                        }
                    }
                }
                charge(1);
                v1 = 0;
              L_004521c0:
                charge(5);
                a0 = dsll32(v1, 24);
                a0 = dsra32(a0, 24);
                v1 = si(1);
                if (a0 == v1) {
                    charge(6);
                    a0 = addu(s4, s3);
                    v1 = dsll32(s2, 24);
                    v1 = dsra32(v1, 24);
                    at = slt(a0, v1);
                    if (at == 0) {
                        charge(7);
                        s2 = dsll32(a0, 24);
                        s2 = dsra32(s2, 24);
                        lq(v1, sp, 208);
                        fp = dsll32(v1, 24);
                        fp = dsra32(fp, 24);
                        v1 = addu(s1, s3);
                        sb(sp, 240, v1);
                    }
                }
                charge(2);
                if (gez(s6)) {
                    charge(3);
                    at = slti(s6, 16);
                    if (at != 0) {
                        charge(5);
                        v1 = subu(s1, s3);
                        v1 = dsll32(v1, 24);
                        v1 = dsra32(v1, 24);
                        if (gez(v1)) {
                            charge(3);
                            at = slti(v1, 16);
                            if (at != 0) {
                                charge(10);
                                s7 = sll(v1, 8);
                                jal(0x452240u, &gen::fn_K_Field_Get_001b9120);
                                lq(v1, sp, 160);
                                v1 = addu(v1, v0);
                                v1 = addu(v1, s7);
                                a0 = lbu(v1, 72);
                                v1 = si(1);
                                if (a0 == v1) {
                                    charge(9);
                                    jal(0x452264u, &gen::fn_K_Field_Get_001b9120);
                                    lq(v1, sp, 160);
                                    v1 = addu(v1, v0);
                                    v1 = addu(v1, s7);
                                    a0 = lbu(v1, 74);
                                    v1 = si(8);
                                    if (a0 != v1) {
                                        charge(3);
                                        v1 = si(1);
                                        goto L_00452298;
                                    }
                                }
                            }
                        }
                    }
                }
                charge(1);
                v1 = 0;
              L_00452298:
                charge(5);
                a0 = dsll32(v1, 24);
                a0 = dsra32(a0, 24);
                v1 = si(1);
                if (a0 == v1) {
                    charge(6);
                    a0 = addu(s4, s3);
                    v1 = dsll32(s2, 24);
                    v1 = dsra32(v1, 24);
                    at = slt(a0, v1);
                    if (at == 0) {
                        charge(7);
                        s2 = dsll32(a0, 24);
                        s2 = dsra32(s2, 24);
                        lq(v1, sp, 176);
                        fp = dsll32(v1, 24);
                        fp = dsra32(fp, 24);
                        v1 = subu(s1, s3);
                        sb(sp, 240, v1);
                    }
                }
                charge(1);
                s3 = addiu(s3, 1);
            }
            charge(1);
            s4 = addiu(s4, 1);
        }
        charge(4);
        v1 = dsll32(s2, 24);
        v1 = dsra32(v1, 24);
        if (v1 != 0) {
            charge(22);
            v1 = lui(0x4448u);
            mtc1(v1, 1);  // 800.0
            mtc1(fp, 0);
            cvt_s_w(0, 0);
            mul_s(0, 1, 0);
            swc1(0, sp, 304);
            sw(sp, 308, zero);
            v1 = lb(sp, 240);
            mtc1(v1, 0);
            cvt_s_w(0, 0);
            mul_s(0, 1, 0);
            swc1(0, sp, 312);
            lwc1(2, sp, 304);
            lwc1(1, sp, 308);
            lwc1(0, sp, 312);
            swc1(2, s5, 0);
            swc1(1, s5, 4);
            swc1(0, s5, 8);
        } else {
            charge(6);
            lwc1(2, sp, 320);
            lwc1(1, sp, 324);
            lwc1(0, sp, 328);
            swc1(2, s5, 0);
            swc1(1, s5, 4);
            swc1(0, s5, 8);
        }
        charge(13);
        ra = ld(sp, 144);
        lq(fp, sp, 128);
        lq(s7, sp, 112);
        lq(s6, sp, 96);
        lq(s5, sp, 80);
        lq(s4, sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 336);
    }

    // 0x452F70 (out, task): finds the first grid cell with bytes +1 == 1 and kind 8 (the stairs), then over its 2 x 2 cells
    // each open side whose neighbour is not a stair cell: sub_1BF220 for the neighbour (into sp, kept for out) and for the
    // cell itself (into the think work +52 / +56 / +60). out = the last neighbour position.
    void sub_452F70() {
        enter(15);
        sp = addiu(sp, -224);
        sd(sp, 128, ra);
        sq(s7, sp, 112);
        sq(s6, sp, 96);
        sq(s5, sp, 80);
        sq(s4, sp, 64);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s0 = a0;
        s3 = lw(a1, kTaskWork);
        s4 = 0;
        for (;;) {
            charge(3);
            v1 = slti(s4, 16);
            if (v1 == 0) break;
            backedge();
            charge(4);
            s5 = 0;
            s2 = sll(s4, 8);
            for (;;) {
                charge(3);
                v1 = slti(s5, 16);
                if (v1 == 0) break;
                backedge();
                charge(9);
                s1 = sll(s5, 4);
                jal(0x452FC0u, &gen::fn_K_Field_Get_001b9120);
                v1 = addu(s2, v0);
                v1 = addu(v1, s1);
                a0 = lbu(v1, 73);
                v1 = si(1);
                if (a0 == v1) {
                    charge(8);
                    jal(0x452FE0u, &gen::fn_K_Field_Get_001b9120);
                    v1 = addu(s2, v0);
                    v1 = addu(v1, s1);
                    a0 = lbu(v1, 74);
                    v1 = si(8);
                    if (a0 == v1) {
                        charge(4);
                        s6 = s5;
                        s7 = s4;
                        goto found;  // out of both loops
                    }
                }
                charge(1);
                s5 = addiu(s5, 1);
            }
            charge(1);
            s4 = addiu(s4, 1);
        }
    found:
        charge(3);
        s5 = s6;
        for (;;) {
            charge(4);
            v1 = addiu(s6, 2);
            v1 = slt(s5, v1);
            if (v1 == 0) break;
            backedge();
            charge(4);
            s4 = s7;
            s2 = sll(s5, 4);
            for (;;) {
                charge(4);
                v1 = addiu(s7, 2);
                v1 = slt(s4, v1);
                if (v1 == 0) break;
                backedge();
                charge(9);
                s1 = sll(s4, 8);
                jal(0x453050u, &gen::fn_K_Field_Get_001b9120);
                v0 = addu(s2, v0);
                v0 = addu(v0, s1);
                v0 = lbu(v0, 83);
                v0 = v0 & 0x1u;
                if (v0 != 0) {
                    charge(8);
                    jal(0x453070u, &gen::fn_K_Field_Get_001b9120);
                    v0 = addu(s2, v0);
                    v0 = addu(v0, s1);
                    v1 = lbu(v0, -182);
                    v0 = si(8);
                    if (v1 != v0) {
                        charge(17);
                        a1 = s5 & 0xFFFFu;
                        v0 = addiu(s4, -1);
                        a2 = v0 & 0xFFFFu;
                        a0 = addiu(sp, 208);
                        jal(0x4530A0u, &gen::fn_sub_1BF220_001bf220);
                        a1 = s5 & 0xFFFFu;
                        a2 = s4 & 0xFFFFu;
                        a0 = addiu(sp, 192);
                        jal(0x4530B4u, &gen::fn_sub_1BF220_001bf220);
                        lwc1(2, sp, 192);
                        lwc1(1, sp, 196);
                        lwc1(0, sp, 200);
                        swc1(2, s3, 52);
                        swc1(1, s3, 56);
                        swc1(0, s3, 60);
                    }
                }
                charge(8);
                jal(0x4530D4u, &gen::fn_K_Field_Get_001b9120);
                v0 = addu(s2, v0);
                v0 = addu(v0, s1);
                v0 = lbu(v0, 83);
                v0 = v0 & 0x2u;
                if (v0 != 0) {
                    charge(8);
                    jal(0x4530F4u, &gen::fn_K_Field_Get_001b9120);
                    v0 = addu(s2, v0);
                    v0 = addu(v0, s1);
                    v1 = lbu(v0, 58);
                    v0 = si(8);
                    if (v1 != v0) {
                        charge(17);
                        v0 = addiu(s5, -1);
                        a1 = v0 & 0xFFFFu;
                        a2 = s4 & 0xFFFFu;
                        a0 = addiu(sp, 208);
                        jal(0x453124u, &gen::fn_sub_1BF220_001bf220);
                        a1 = s5 & 0xFFFFu;
                        a2 = s4 & 0xFFFFu;
                        a0 = addiu(sp, 176);
                        jal(0x453138u, &gen::fn_sub_1BF220_001bf220);
                        lwc1(2, sp, 176);
                        lwc1(1, sp, 180);
                        lwc1(0, sp, 184);
                        swc1(2, s3, 52);
                        swc1(1, s3, 56);
                        swc1(0, s3, 60);
                    }
                }
                charge(8);
                jal(0x453158u, &gen::fn_K_Field_Get_001b9120);
                v0 = addu(s2, v0);
                v0 = addu(v0, s1);
                v0 = lbu(v0, 83);
                v0 = v0 & 0x4u;
                if (v0 != 0) {
                    charge(8);
                    jal(0x453178u, &gen::fn_K_Field_Get_001b9120);
                    v0 = addu(s2, v0);
                    v0 = addu(v0, s1);
                    v1 = lbu(v0, 330);
                    v0 = si(8);
                    if (v1 != v0) {
                        charge(17);
                        a1 = s5 & 0xFFFFu;
                        v0 = addiu(s4, 1);
                        a2 = v0 & 0xFFFFu;
                        a0 = addiu(sp, 208);
                        jal(0x4531A8u, &gen::fn_sub_1BF220_001bf220);
                        a1 = s5 & 0xFFFFu;
                        a2 = s4 & 0xFFFFu;
                        a0 = addiu(sp, 160);
                        jal(0x4531BCu, &gen::fn_sub_1BF220_001bf220);
                        lwc1(2, sp, 160);
                        lwc1(1, sp, 164);
                        lwc1(0, sp, 168);
                        swc1(2, s3, 52);
                        swc1(1, s3, 56);
                        swc1(0, s3, 60);
                    }
                }
                charge(8);
                jal(0x4531DCu, &gen::fn_K_Field_Get_001b9120);
                v1 = addu(s2, v0);
                v1 = addu(v1, s1);
                v1 = lbu(v1, 83);
                v1 = v1 & 0x8u;
                if (v1 != 0) {
                    charge(8);
                    jal(0x4531FCu, &gen::fn_K_Field_Get_001b9120);
                    v1 = addu(s2, v0);
                    v1 = addu(v1, s1);
                    a0 = lbu(v1, 90);
                    v1 = si(8);
                    if (a0 != v1) {
                        charge(17);
                        v0 = addiu(s5, 1);
                        a1 = v0 & 0xFFFFu;
                        a2 = s4 & 0xFFFFu;
                        a0 = addiu(sp, 208);
                        jal(0x45322Cu, &gen::fn_sub_1BF220_001bf220);
                        a1 = s5 & 0xFFFFu;
                        a2 = s4 & 0xFFFFu;
                        a0 = addiu(sp, 144);
                        jal(0x453240u, &gen::fn_sub_1BF220_001bf220);
                        lwc1(2, sp, 144);
                        lwc1(1, sp, 148);
                        lwc1(0, sp, 152);
                        swc1(2, s3, 52);
                        swc1(1, s3, 56);
                        swc1(0, s3, 60);
                    }
                }
                charge(1);
                s4 = addiu(s4, 1);
            }
            charge(1);
            s5 = addiu(s5, 1);
        }
        charge(18);
        lwc1(2, sp, 208);
        lwc1(1, sp, 212);
        lwc1(0, sp, 216);
        swc1(2, s0, 0);
        swc1(1, s0, 4);
        swc1(0, s0, 8);
        ra = ld(sp, 128);
        lq(s7, sp, 112);
        lq(s6, sp, 96);
        lq(s5, sp, 80);
        lq(s4, sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 224);
    }
};

struct EneLook : EneLeaves {
    using EneLeaves::EneLeaves;

    // 0x44DFC0 (think state 5, contact; the step at work +5): 0 clears the mover's queue (sub_1B00C0 / sub_1B0240 on the
    // unit's +368 task), drops +12, then -- contacted by the hero (K_FldEvent_IsUnitHero of gFldUnitsPc[+24]) with no
    // battle task yet: the s16 gp-0x45FC = this unit, the s8 gp-0x4600 = the party member, step 1, every shadow paused
    // (sub_4532D0(1)) and the party (sub_435060(1)); a party member with a battle task (K_Battle_FindTaskOfUnit): joins it
    // (sub_1D8E60), +12 = the task, step 1; a dead member (datUnitIsGenusDead): back to wandering (sub_4543C0(i, 4), the
    // 0x95C210 byte cleared); else +12 = K_Battle_CreateBattleTask(task, member, unit), step 1, sub_43A1A0. Step 1 and 3
    // wait for the +12 task to end (kwlnTaskExists) and step 2 looks the battle task up again; afterwards the unit, if
    // still used, goes back to state 4 (or, with behaviour kind 4, sub_1AAAC0(+16, 0) and state 3).
    void sub_44DFC0() {
        enter(10);
        sp = addiu(sp, -48);
        sd(sp, 32, ra);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s1 = a0;
        s0 = lw(a0, kTaskWork);
        a0 = lb(s0, 5);
        v1 = si(3);
        if (a0 != v1) {
            charge(3);
            v1 = si(2);
            if (a0 != v1) {
                charge(3);
                v1 = si(1);
                if (a0 != v1) {
                    charge(2);
                    if (a0 != 0) {
                        charge(2);
                    } else {
                        charge(24);
                        v1 = lb(s0, 1);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, -4336);  // 0x86EF10
                        v0 = addu(v0, v1);
                        a0 = lw(v0, 0);
                        jal(0x44E030u, &gen::fn_sub_1B00C0_001b00c0);
                        v1 = lb(s0, 1);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, -4336);  // 0x86EF10
                        v0 = addu(v0, v1);
                        a0 = lw(v0, 0);
                        a1 = 0;
                        jal(0x44E05Cu, &gen::fn_sub_1B0240_001b0240);
                        v0 = lw(s0, 12);
                        if (v0 != 0) {
                            charge(1);
                            sw(s0, 12, zero);
                        }
                        charge(12);
                        v1 = lb(s0, 24);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, 6048);  // 0x8717A0 gFldUnitsPc
                        a0 = addu(v0, v1);
                        jal(0x44E090u, &gen::fn_K_FldEvent_IsUnitHero_001c7b10);
                        v1 = si(1);
                        if (v0 == v1) {
                            charge(11);
                            v1 = lb(s0, 24);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, 6048);  // 0x8717A0 gFldUnitsPc
                            a0 = addu(v0, v1);
                            jal(0x44E0C0u, &gen::fn_K_Battle_FindTaskOfUnit_001d8d80);
                            if (v0 == 0) {
                                charge(13);
                                v0 = lb(s0, 1);
                                sh(gp, -17916, v0);
                                v0 = lb(s0, 24);
                                sb(gp, -17920, v0);
                                a0 = si(1);
                                sb(s0, 5, a0);
                                jal(0x44E0E8u, &gen::fn_sub_4532D0_004532d0);
                                a0 = si(1);
                                jal(0x44E0F4u, &gen::fn_sub_435060_00435060);
                            }
                        } else {
                            charge(11);
                            v1 = lb(s0, 24);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, 6048);  // 0x8717A0 gFldUnitsPc
                            a0 = addu(v0, v1);
                            jal(0x44E120u, &gen::fn_K_Battle_FindTaskOfUnit_001d8d80);
                            if (v0 == 0) {
                                charge(13);
                                v1 = lb(s0, 24);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, 6120);  // 0x8717E8
                                v0 = addu(v0, v1);
                                a0 = lw(v0, 0);
                                jal(0x44E150u, &gen::fn_datUnitIsGenusDead_002ff790);
                                v1 = si(1);
                                if (v0 == v1) {
                                    charge(11);
                                    a0 = lb(s0, 1);
                                    a1 = si(4);
                                    jal(0x44E16Cu, &gen::fn_sub_4543C0_004543c0);
                                    a0 = lb(s0, 1);
                                    v1 = lui(0x96u);
                                    v1 = addiu(v1, -15856);  // 0x95C210
                                    v1 = addu(v1, a0);
                                    sb(v1, 0, zero);
                                } else {
                                    charge(26);
                                    v1 = lb(s0, 24);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, 6048);  // 0x8717A0 gFldUnitsPc
                                    a1 = addu(v0, v1);
                                    v1 = lb(s0, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                    a2 = addu(v0, v1);
                                    a0 = s1;
                                    jal(0x44E1CCu, &gen::fn_K_Battle_CreateBattleTask_001d8b00);
                                    sw(s0, 12, v0);
                                    v0 = si(1);
                                    sb(s0, 5, v0);
                                    a0 = lb(s0, 24);
                                    a1 = lb(s0, 1);
                                    jal(0x44E1E8u, &gen::fn_sub_43A1A0_0043a1a0);
                                }
                            } else {
                                charge(34);
                                v1 = lb(s0, 24);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, 6048);  // 0x8717A0 gFldUnitsPc
                                a0 = addu(v0, v1);
                                jal(0x44E214u, &gen::fn_K_Battle_FindTaskOfUnit_001d8d80);
                                a0 = lb(s0, 1);
                                v1 = sll(a0, 3);
                                v1 = subu(v1, a0);
                                a0 = sll(v1, 6);
                                v1 = lui(0x87u);
                                v1 = addiu(v1, -4704);  // 0x86EDA0 gFldUnitsEc
                                a2 = addu(v1, a0);
                                a0 = v0;
                                a1 = 0;
                                jal(0x44E240u, &gen::fn_sub_1D8E60_001d8e60);
                                v1 = lb(s0, 24);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, 6048);  // 0x8717A0 gFldUnitsPc
                                a0 = addu(v0, v1);
                                jal(0x44E264u, &gen::fn_K_Battle_FindTaskOfUnit_001d8d80);
                                sw(s0, 12, v0);
                                v1 = si(1);
                                sb(s0, 5, v1);
                            }
                        }
                    }
                } else {
                    charge(5);
                    a0 = lw(s0, 12);
                    jal(0x44E284u, &gen::fn_kwlnTaskExists_00195460);
                    if (v0 == 0) {
                        charge(11);
                        a2 = 0;
                        a0 = lb(s0, 1);
                        v1 = sll(a0, 3);
                        v1 = subu(v1, a0);
                        a1 = sll(v1, 6);
                        v1 = lui(0x87u);
                        v1 = addiu(v1, -4632);  // 0x86EDE8
                        v1 = addu(v1, a1);
                        v1 = lw(v1, 0);
                        if (v1 != 0) {
                            charge(6);
                            v1 = lui(0x87u);
                            v1 = addiu(v1, -4620);  // 0x86EDF4
                            v1 = addu(v1, a1);
                            v1 = lw(v1, 0);
                            if (v1 != 0) {
                                charge(1);
                                a2 = si(1);
                            }
                        }
                        charge(3);
                        v1 = sltu(zero, a2);
                        if (v1 == 0) {
                            charge(4);
                            v1 = si(6);
                            sb(s0, 2, v1);
                        } else {
                            charge(7);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -4308);  // 0x86EF2C
                            v0 = addu(v0, a1);
                            v0 = lw(v0, 0);
                            a1 = si(4);
                            if (v0 == a1) {
                                charge(10);
                                a0 = lw(s0, 16);
                                a1 = 0;
                                jal(0x44E31Cu, &gen::fn_sub_1AAAC0_001aaac0);
                                a0 = lb(s0, 1);
                                a1 = si(3);
                                jal(0x44E32Cu, &gen::fn_sub_4543C0_004543c0);
                            } else {
                                charge(9);
                                jal(0x44E33Cu, &gen::fn_sub_4543C0_004543c0);
                                a0 = lb(s0, 1);
                                v1 = lui(0x96u);
                                v1 = addiu(v1, -15856);  // 0x95C210
                                v1 = addu(v1, a0);
                                sb(v1, 0, zero);
                            }
                        }
                    }
                }
            } else {
                charge(3);
                v0 = lw(s0, 12);
                if (v0 != 0) {
                    charge(1);
                    sw(s0, 12, zero);
                }
                charge(12);
                v1 = lb(s0, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6048);  // 0x8717A0 gFldUnitsPc
                a0 = addu(v0, v1);
                jal(0x44E38Cu, &gen::fn_K_Battle_FindTaskOfUnit_001d8d80);
                sw(s0, 12, v0);
                if (v0 != 0) {
                    charge(4);
                    v1 = si(3);
                    sb(s0, 5, v1);
                } else {
                    charge(20);
                    a0 = lb(s0, 1);
                    a1 = si(4);
                    jal(0x44E3B8u, &gen::fn_sub_4543C0_004543c0);
                    a0 = lb(s0, 1);
                    v1 = lui(0x96u);
                    v1 = addiu(v1, -15856);  // 0x95C210
                    v1 = addu(v1, a0);
                    sb(v1, 0, zero);
                    a0 = lb(s0, 1);
                    v1 = sll(a0, 3);
                    v1 = subu(v1, a0);
                    a0 = sll(v1, 6);
                    v1 = lui(0x87u);
                    v1 = addiu(v1, -4308);  // 0x86EF2C
                    v1 = addu(v1, a0);
                    a0 = lw(v1, 0);
                    v1 = si(4);
                    if (a0 == v1) {
                        charge(10);
                        a0 = lw(s0, 16);
                        a1 = 0;
                        jal(0x44E408u, &gen::fn_sub_1AAAC0_001aaac0);
                        a0 = lb(s0, 1);
                        a1 = si(3);
                        jal(0x44E418u, &gen::fn_sub_4543C0_004543c0);
                    }
                }
            }
        } else {
            charge(5);
            a0 = lw(s0, 12);
            jal(0x44E42Cu, &gen::fn_kwlnTaskExists_00195460);
            if (v0 == 0) {
                charge(11);
                a2 = 0;
                a0 = lb(s0, 1);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a1 = sll(v1, 6);
                v1 = lui(0x87u);
                v1 = addiu(v1, -4632);  // 0x86EDE8
                v1 = addu(v1, a1);
                v1 = lw(v1, 0);
                if (v1 != 0) {
                    charge(6);
                    v1 = lui(0x87u);
                    v1 = addiu(v1, -4620);  // 0x86EDF4
                    v1 = addu(v1, a1);
                    v1 = lw(v1, 0);
                    if (v1 != 0) {
                        charge(1);
                        a2 = si(1);
                    }
                }
                charge(3);
                v1 = sltu(zero, a2);
                if (v1 == 0) {
                    charge(4);
                    v1 = si(6);
                    sb(s0, 2, v1);
                } else {
                    charge(19);
                    a1 = si(4);
                    jal(0x44E4A4u, &gen::fn_sub_4543C0_004543c0);
                    a0 = lb(s0, 1);
                    v1 = lui(0x96u);
                    v1 = addiu(v1, -15856);  // 0x95C210
                    v1 = addu(v1, a0);
                    sb(v1, 0, zero);
                    a0 = lb(s0, 1);
                    v1 = sll(a0, 3);
                    v1 = subu(v1, a0);
                    a0 = sll(v1, 6);
                    v1 = lui(0x87u);
                    v1 = addiu(v1, -4308);  // 0x86EF2C
                    v1 = addu(v1, a0);
                    a0 = lw(v1, 0);
                    v1 = si(4);
                    if (a0 == v1) {
                        charge(8);
                        a0 = lw(s0, 16);
                        a1 = 0;
                        jal(0x44E4F4u, &gen::fn_sub_1AAAC0_001aaac0);
                        a0 = lb(s0, 1);
                        a1 = si(3);
                        jal(0x44E504u, &gen::fn_sub_4543C0_004543c0);
                    }
                }
            }
        }
        charge(6);
        ra = ld(sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 48);
    }

    // 0x44E560 (task): picks the shadow's next wander point: its cell (+92 / +93 from the position +96), then up to 100
    // tries of a random direction d = (RpRandom() % 200) / 25 (a jump table over 0..7: -z, -x, +z, +x and the four
    // diagonals at half the distance) and a distance +146 = 400 + (RpRandom() % 4000) / 10 (u16, 2^31 split): the point is
    // taken when it is within the behaviour range (sub_44F060, the record gp-0x4A60 + 64 kind), no other shadow is near it
    // (sub_454400) and sub_454D00 accepts it, and it lies in the shadow's own cell or behind an open side of it (straight
    // directions only); then +120 / +121 = its cell and +4 = 2. After 100 failures: state 4, +4 = 5. Returns d or -1.
    void sub_44E560() {
        enter(33);
        sp = addiu(sp, -144);
        sd(sp, 112, ra);
        sq(s6, sp, 96);
        sq(s5, sp, 80);
        sq(s4, sp, 64);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s4 = a0;
        s1 = lw(a0, kTaskWork);
        s3 = 0;
        s2 = si(-1);
        s5 = 0;
        v1 = lb(s1, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4308);  // 0x86EF2C
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        v1 = sll(v0, 6);
        v0 = lw(gp, -19040);
        s0 = addu(v0, v1);
        a0 = addiu(s1, 96);
        jal(0x44E5C8u, &gen::fn_sub_44F120_0044f120);
        sb(s1, 92, v0);
        a0 = addiu(s1, 96);
        jal(0x44E5D8u, &gen::fn_sub_44F170_0044f170);
        sb(s1, 93, v0);
        for (;;) {
            charge(32);
            jal(0x44E5E4u, &gen::fn_sub_488F30_00488f30);
            v1 = si(200);
            divu(v0, v1);
            mfhi(v1);
            v0 = si(25);
            divu(v1, v0);
            mflo(v0);
            s6 = dsll32(v0, 24);
            s6 = dsra32(s6, 24);
            jal(0x44E60Cu, &gen::fn_sub_488F30_00488f30);
            v1 = si(4000);
            divu(v0, v1);
            mfhi(v1);
            v0 = si(10);
            divu(v1, v0);
            mflo(v0);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = lui(0x43C8u);
            mtc1(v0, 1);  // 400.0
            mtc1(v1, 0);
            cvt_s_w(0, 0);
            add_s(1, 1, 0);
            v0 = lui(0x4F00u);
            mtc1(v0, 0);  // 2^31
            c_le_s(0, 1);
            if (!cond()) {
                charge(6);
                cvt_w_s(0, 1);
                mfc1(v1, 0);
                v1 = v1 & 0xFFFFu;
            } else {
                charge(6);
                sub_s(0, 1, 0);
                cvt_w_s(0, 0);
                mfc1(v1, 0);
                v0 = lui(0x8000u);
                v1 = v1 | v0;
                v1 = v1 & 0xFFFFu;
            }
            charge(6);
            sh(s1, 146, v1);
            v0 = dsll32(s6, 24);
            v0 = dsra32(v0, 24);
            at = sltiu(v0, 8);
            if (at != 0) {
                charge(7);
                v1 = lui(0x7Cu);
                v1 = addiu(v1, -14864);  // 0x7BC5F0
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                switch (w(v0)) {  // jump table 0x7BC5F0
                default:
                    dispatch(v0);
                    return;
                case 0x44E6C8u:  // [0]
                    charge(10);
                    lwc1(2, s1, 96);
                    lwc1(1, s1, 100);
                    lwc1(0, s1, 104);
                    swc1(2, sp, 128);
                    swc1(1, sp, 132);
                    swc1(0, sp, 136);
                    lwc1(1, s1, 104);
                    v0 = lhu(s1, 146);
                    if (gez(v0)) {
                        charge(5);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                    } else {
                        charge(7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1u;
                        v1 = v1 | v0;
                        mtc1(v1, 0);
                        cvt_s_w(0, 0);
                        add_s(0, 0, 0);
                    }
                    charge(10);
                    sub_s(0, 1, 0);
                    swc1(0, sp, 136);
                    a0 = s4;
                    lwc1(12, s0, 0);
                    a1 = addiu(sp, 128);
                    jal(0x44E734u, &gen::fn_sub_44F060_0044f060);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(7);
                    a0 = addiu(sp, 128);
                    a1 = lb(s1, 1);
                    jal(0x44E750u, &gen::fn_sub_454400_00454400);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(6);
                    a0 = addiu(sp, 128);
                    jal(0x44E768u, &gen::fn_sub_454D00_00454d00);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(12);
                    a0 = addiu(sp, 128);
                    jal(0x44E780u, &gen::fn_sub_44F120_0044f120);
                    sb(s1, 120, v0);
                    a0 = addiu(sp, 128);
                    jal(0x44E790u, &gen::fn_sub_44F170_0044f170);
                    sb(s1, 121, v0);
                    v1 = lb(s1, 92);
                    v0 = lbu(s1, 120);
                    if (v1 == v0) {
                        charge(4);
                        v1 = lb(s1, 93);
                        v0 = lbu(s1, 121);
                        if (v1 == v0) {
                            charge(6);
                            s3 = si(1);
                            s2 = 0;
                            v0 = si(2);
                            sb(s1, 4, v0);
                            break;
                        }
                    }
                    charge(12);
                    jal(0x44E7D4u, &gen::fn_K_Field_Get_001b9120);
                    v1 = lb(s1, 93);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    v0 = lb(s1, 92);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    v0 = lbu(v0, 83);
                    v0 = v0 & 0x1u;
                    if (v0 == 0) break;
                    charge(6);
                    s3 = si(1);
                    s2 = 0;
                    v0 = si(2);
                    sb(s1, 4, v0);
                    break;
                case 0x44E81Cu:  // [1]
                    charge(10);
                    lwc1(2, s1, 96);
                    lwc1(1, s1, 100);
                    lwc1(0, s1, 104);
                    swc1(2, sp, 128);
                    swc1(1, sp, 132);
                    swc1(0, sp, 136);
                    lwc1(1, s1, 96);
                    v0 = lhu(s1, 146);
                    if (gez(v0)) {
                        charge(5);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                    } else {
                        charge(7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1u;
                        v1 = v1 | v0;
                        mtc1(v1, 0);
                        cvt_s_w(0, 0);
                        add_s(0, 0, 0);
                    }
                    charge(10);
                    sub_s(0, 1, 0);
                    swc1(0, sp, 128);
                    a0 = s4;
                    lwc1(12, s0, 0);
                    a1 = addiu(sp, 128);
                    jal(0x44E888u, &gen::fn_sub_44F060_0044f060);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(7);
                    a0 = addiu(sp, 128);
                    a1 = lb(s1, 1);
                    jal(0x44E8A4u, &gen::fn_sub_454400_00454400);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(6);
                    a0 = addiu(sp, 128);
                    jal(0x44E8BCu, &gen::fn_sub_454D00_00454d00);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(12);
                    a0 = addiu(sp, 128);
                    jal(0x44E8D4u, &gen::fn_sub_44F120_0044f120);
                    sb(s1, 120, v0);
                    a0 = addiu(sp, 128);
                    jal(0x44E8E4u, &gen::fn_sub_44F170_0044f170);
                    sb(s1, 121, v0);
                    v1 = lb(s1, 92);
                    v0 = lbu(s1, 120);
                    if (v1 == v0) {
                        charge(4);
                        v1 = lb(s1, 93);
                        v0 = lbu(s1, 121);
                        if (v1 == v0) {
                            charge(6);
                            s3 = si(1);
                            s2 = s3;
                            v0 = si(2);
                            sb(s1, 4, v0);
                            break;
                        }
                    }
                    charge(12);
                    jal(0x44E928u, &gen::fn_K_Field_Get_001b9120);
                    v1 = lb(s1, 93);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    v0 = lb(s1, 92);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    v0 = lbu(v0, 83);
                    v0 = v0 & 0x2u;
                    if (v0 == 0) break;
                    charge(6);
                    s3 = si(1);
                    s2 = s3;
                    v0 = si(2);
                    sb(s1, 4, v0);
                    break;
                case 0x44E970u:  // [2]
                    charge(10);
                    lwc1(2, s1, 96);
                    lwc1(1, s1, 100);
                    lwc1(0, s1, 104);
                    swc1(2, sp, 128);
                    swc1(1, sp, 132);
                    swc1(0, sp, 136);
                    lwc1(1, s1, 104);
                    v0 = lhu(s1, 146);
                    if (gez(v0)) {
                        charge(5);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                    } else {
                        charge(7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1u;
                        v1 = v1 | v0;
                        mtc1(v1, 0);
                        cvt_s_w(0, 0);
                        add_s(0, 0, 0);
                    }
                    charge(10);
                    add_s(0, 1, 0);
                    swc1(0, sp, 136);
                    a0 = s4;
                    lwc1(12, s0, 0);
                    a1 = addiu(sp, 128);
                    jal(0x44E9DCu, &gen::fn_sub_44F060_0044f060);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(7);
                    a0 = addiu(sp, 128);
                    a1 = lb(s1, 1);
                    jal(0x44E9F8u, &gen::fn_sub_454400_00454400);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(6);
                    a0 = addiu(sp, 128);
                    jal(0x44EA10u, &gen::fn_sub_454D00_00454d00);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(12);
                    a0 = addiu(sp, 128);
                    jal(0x44EA28u, &gen::fn_sub_44F120_0044f120);
                    sb(s1, 120, v0);
                    a0 = addiu(sp, 128);
                    jal(0x44EA38u, &gen::fn_sub_44F170_0044f170);
                    sb(s1, 121, v0);
                    v1 = lb(s1, 92);
                    v0 = lbu(s1, 120);
                    if (v1 == v0) {
                        charge(4);
                        v1 = lb(s1, 93);
                        v0 = lbu(s1, 121);
                        if (v1 == v0) {
                            charge(5);
                            s3 = si(1);
                            s2 = si(2);
                            sb(s1, 4, s2);
                            break;
                        }
                    }
                    charge(12);
                    jal(0x44EA78u, &gen::fn_K_Field_Get_001b9120);
                    v1 = lb(s1, 93);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    v0 = lb(s1, 92);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    v0 = lbu(v0, 83);
                    v0 = v0 & 0x4u;
                    if (v0 == 0) break;
                    charge(5);
                    s3 = si(1);
                    s2 = si(2);
                    sb(s1, 4, s2);
                    break;
                case 0x44EABCu:  // [3]
                    charge(10);
                    lwc1(2, s1, 96);
                    lwc1(1, s1, 100);
                    lwc1(0, s1, 104);
                    swc1(2, sp, 128);
                    swc1(1, sp, 132);
                    swc1(0, sp, 136);
                    lwc1(1, s1, 96);
                    v0 = lhu(s1, 146);
                    if (gez(v0)) {
                        charge(5);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                    } else {
                        charge(7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1u;
                        v1 = v1 | v0;
                        mtc1(v1, 0);
                        cvt_s_w(0, 0);
                        add_s(0, 0, 0);
                    }
                    charge(10);
                    add_s(0, 1, 0);
                    swc1(0, sp, 128);
                    a0 = s4;
                    lwc1(12, s0, 0);
                    a1 = addiu(sp, 128);
                    jal(0x44EB28u, &gen::fn_sub_44F060_0044f060);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(7);
                    a0 = addiu(sp, 128);
                    a1 = lb(s1, 1);
                    jal(0x44EB44u, &gen::fn_sub_454400_00454400);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(6);
                    a0 = addiu(sp, 128);
                    jal(0x44EB5Cu, &gen::fn_sub_454D00_00454d00);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(12);
                    a0 = addiu(sp, 128);
                    jal(0x44EB74u, &gen::fn_sub_44F120_0044f120);
                    sb(s1, 120, v0);
                    a0 = addiu(sp, 128);
                    jal(0x44EB84u, &gen::fn_sub_44F170_0044f170);
                    sb(s1, 121, v0);
                    v1 = lb(s1, 92);
                    v0 = lbu(s1, 120);
                    if (v1 == v0) {
                        charge(4);
                        v1 = lb(s1, 93);
                        v0 = lbu(s1, 121);
                        if (v1 == v0) {
                            charge(6);
                            s3 = si(1);
                            s2 = si(3);
                            v0 = si(2);
                            sb(s1, 4, v0);
                            break;
                        }
                    }
                    charge(12);
                    jal(0x44EBC8u, &gen::fn_K_Field_Get_001b9120);
                    v1 = lb(s1, 93);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    v0 = lb(s1, 92);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    v0 = lbu(v0, 83);
                    v0 = v0 & 0x8u;
                    if (v0 == 0) break;
                    charge(6);
                    s3 = si(1);
                    s2 = si(3);
                    v0 = si(2);
                    sb(s1, 4, v0);
                    break;
                case 0x44EC10u:  // [4]
                    charge(25);
                    a1 = addiu(sp, 128);
                    lwc1(2, s1, 96);
                    lwc1(1, s1, 100);
                    lwc1(0, s1, 104);
                    swc1(2, sp, 128);
                    swc1(1, sp, 132);
                    swc1(0, sp, 136);
                    v0 = lhu(s1, 146);
                    v0 = srl(v0, 1);
                    mtc1(v0, 0);
                    cvt_s_w(1, 0);
                    lwc1(0, s1, 96);
                    add_s(0, 0, 1);
                    swc1(0, sp, 128);
                    lwc1(0, s1, 104);
                    sub_s(0, 0, 1);
                    swc1(0, sp, 136);
                    a0 = s4;
                    lwc1(12, s0, 0);
                    jal(0x44EC60u, &gen::fn_sub_44F060_0044f060);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(7);
                    a0 = addiu(sp, 128);
                    a1 = lb(s1, 1);
                    jal(0x44EC7Cu, &gen::fn_sub_454400_00454400);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(6);
                    a0 = addiu(sp, 128);
                    jal(0x44EC94u, &gen::fn_sub_454D00_00454d00);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(12);
                    a0 = addiu(sp, 128);
                    jal(0x44ECACu, &gen::fn_sub_44F120_0044f120);
                    sb(s1, 120, v0);
                    a0 = addiu(sp, 128);
                    jal(0x44ECBCu, &gen::fn_sub_44F170_0044f170);
                    sb(s1, 121, v0);
                    v1 = lb(s1, 92);
                    v0 = lbu(s1, 120);
                    if (v1 != v0) break;
                    charge(4);
                    v1 = lb(s1, 93);
                    v0 = lbu(s1, 121);
                    if (v1 != v0) break;
                    charge(6);
                    s3 = si(1);
                    s2 = si(4);
                    v0 = si(2);
                    sb(s1, 4, v0);
                    break;
                case 0x44ED00u:  // [5]
                    charge(25);
                    a1 = addiu(sp, 128);
                    lwc1(2, s1, 96);
                    lwc1(1, s1, 100);
                    lwc1(0, s1, 104);
                    swc1(2, sp, 128);
                    swc1(1, sp, 132);
                    swc1(0, sp, 136);
                    v0 = lhu(s1, 146);
                    v0 = srl(v0, 1);
                    mtc1(v0, 0);
                    cvt_s_w(1, 0);
                    lwc1(0, s1, 96);
                    add_s(0, 0, 1);
                    swc1(0, sp, 128);
                    lwc1(0, s1, 104);
                    add_s(0, 0, 1);
                    swc1(0, sp, 136);
                    a0 = s4;
                    lwc1(12, s0, 0);
                    jal(0x44ED50u, &gen::fn_sub_44F060_0044f060);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(7);
                    a0 = addiu(sp, 128);
                    a1 = lb(s1, 1);
                    jal(0x44ED6Cu, &gen::fn_sub_454400_00454400);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(6);
                    a0 = addiu(sp, 128);
                    jal(0x44ED84u, &gen::fn_sub_454D00_00454d00);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(12);
                    a0 = addiu(sp, 128);
                    jal(0x44ED9Cu, &gen::fn_sub_44F120_0044f120);
                    sb(s1, 120, v0);
                    a0 = addiu(sp, 128);
                    jal(0x44EDACu, &gen::fn_sub_44F170_0044f170);
                    sb(s1, 121, v0);
                    v1 = lb(s1, 92);
                    v0 = lbu(s1, 120);
                    if (v1 != v0) break;
                    charge(4);
                    v1 = lb(s1, 93);
                    v0 = lbu(s1, 121);
                    if (v1 != v0) break;
                    charge(6);
                    s3 = si(1);
                    s2 = si(5);
                    v0 = si(2);
                    sb(s1, 4, v0);
                    break;
                case 0x44EDF0u:  // [6]
                    charge(25);
                    a1 = addiu(sp, 128);
                    lwc1(2, s1, 96);
                    lwc1(1, s1, 100);
                    lwc1(0, s1, 104);
                    swc1(2, sp, 128);
                    swc1(1, sp, 132);
                    swc1(0, sp, 136);
                    v0 = lhu(s1, 146);
                    v0 = srl(v0, 1);
                    mtc1(v0, 0);
                    cvt_s_w(1, 0);
                    lwc1(0, s1, 96);
                    sub_s(0, 0, 1);
                    swc1(0, sp, 128);
                    lwc1(0, s1, 104);
                    sub_s(0, 0, 1);
                    swc1(0, sp, 136);
                    a0 = s4;
                    lwc1(12, s0, 0);
                    jal(0x44EE40u, &gen::fn_sub_44F060_0044f060);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(7);
                    a0 = addiu(sp, 128);
                    a1 = lb(s1, 1);
                    jal(0x44EE5Cu, &gen::fn_sub_454400_00454400);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(6);
                    a0 = addiu(sp, 128);
                    jal(0x44EE74u, &gen::fn_sub_454D00_00454d00);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(12);
                    a0 = addiu(sp, 128);
                    jal(0x44EE8Cu, &gen::fn_sub_44F120_0044f120);
                    sb(s1, 120, v0);
                    a0 = addiu(sp, 128);
                    jal(0x44EE9Cu, &gen::fn_sub_44F170_0044f170);
                    sb(s1, 121, v0);
                    v1 = lb(s1, 92);
                    v0 = lbu(s1, 120);
                    if (v1 != v0) break;
                    charge(4);
                    v1 = lb(s1, 93);
                    v0 = lbu(s1, 121);
                    if (v1 != v0) break;
                    charge(6);
                    s3 = si(1);
                    s2 = si(6);
                    v0 = si(2);
                    sb(s1, 4, v0);
                    break;
                case 0x44EEE0u:  // [7]
                    charge(25);
                    a1 = addiu(sp, 128);
                    lwc1(2, s1, 96);
                    lwc1(1, s1, 100);
                    lwc1(0, s1, 104);
                    swc1(2, sp, 128);
                    swc1(1, sp, 132);
                    swc1(0, sp, 136);
                    v0 = lhu(s1, 146);
                    v0 = srl(v0, 1);
                    mtc1(v0, 0);
                    cvt_s_w(1, 0);
                    lwc1(0, s1, 96);
                    sub_s(0, 0, 1);
                    swc1(0, sp, 128);
                    lwc1(0, s1, 104);
                    add_s(0, 0, 1);
                    swc1(0, sp, 136);
                    a0 = s4;
                    lwc1(12, s0, 0);
                    jal(0x44EF30u, &gen::fn_sub_44F060_0044f060);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(7);
                    a0 = addiu(sp, 128);
                    a1 = lb(s1, 1);
                    jal(0x44EF4Cu, &gen::fn_sub_454400_00454400);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(6);
                    a0 = addiu(sp, 128);
                    jal(0x44EF64u, &gen::fn_sub_454D00_00454d00);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(12);
                    a0 = addiu(sp, 128);
                    jal(0x44EF7Cu, &gen::fn_sub_44F120_0044f120);
                    sb(s1, 120, v0);
                    a0 = addiu(sp, 128);
                    jal(0x44EF8Cu, &gen::fn_sub_44F170_0044f170);
                    sb(s1, 121, v0);
                    v1 = lb(s1, 92);
                    v0 = lbu(s1, 120);
                    if (v1 != v0) break;
                    charge(4);
                    v1 = lb(s1, 93);
                    v0 = lbu(s1, 121);
                    if (v1 != v0) break;
                    charge(4);
                    s3 = si(1);
                    s2 = si(7);
                    v0 = si(2);
                    sb(s1, 4, v0);
                }
            }
            charge(4);
            v0 = dsll32(s3, 24);
            v0 = dsra32(v0, 24);
            if (v0 == 0) {
                charge(3);
                v0 = addiu(s5, 1);
                s5 = dsll32(v0, 16);
                s5 = dsra32(s5, 16);
            }
            charge(5);
            v0 = dsll32(s5, 16);
            v0 = dsra32(v0, 16);
            v0 = slti(v0, 100);
            if (v0 == 0) {
                charge(7);
                s5 = 0;
                s3 = si(1);
                v1 = lw(s4, kTaskWork);
                v0 = si(4);
                sb(v1, 2, v0);
                v0 = si(5);
                sb(v1, 4, v0);
            }
            charge(4);
            v0 = dsll32(s3, 24);
            v0 = dsra32(v0, 24);
            if (v0 != 0) break;
            backedge();
        }
        charge(12);
        v0 = s2;
        ra = ld(sp, 112);
        lq(s6, sp, 96);
        lq(s5, sp, 80);
        lq(s4, sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 144);
    }

    // 0x44F300 (ec): unless gp-0x4634 is 1 with behaviour kind 2: the nearest party member (sub_1C6D70 / sub_1C6DD0) that
    // is closer than the current target (+24) and free of other shadows (sub_454400) becomes the target when the unit can
    // see it (sub_1C65E0) and, for a member other than the hero, sub_437E20 says it can be chased; otherwise, while flag 3173
    // is off, it becomes the target with +3 = 24. Then the target inside the behaviour's sight range (+4) and in front of
    // the model (sub_1C6450 of mdlGetMatrix(+296)) is chased the same way (kind 3 skips the sight test). Every success:
    // sub_4543C0(ec, 3) (chase), the 0x95C210 byte = 1, returns 1.
    void sub_44F300() {
        enter(35);
        sp = addiu(sp, -416);
        sd(sp, 112, ra);
        sq(s5, sp, 96);
        sq(s4, sp, 80);
        sq(s3, sp, 64);
        sq(s2, sp, 48);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(20, sp, 0);
        v1 = dsll32(a0, 24);
        v1 = dsra32(v1, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4340);  // 0x86EF0C
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        s3 = lw(v0, kTaskWork);
        s4 = 0;
        v1 = lb(s3, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4308);  // 0x86EF2C
        v0 = addu(v0, v1);
        a0 = lw(v0, 0);
        v1 = sll(a0, 6);
        v0 = lw(gp, -19040);
        s2 = addu(v0, v1);
        v1 = lb(gp, -17972);
        v0 = si(1);
        if (v1 == v0) {
            charge(3);
            v0 = si(2);
            if (a0 == v0) {
                charge(3);
                v0 = 0;
                charge(11);
                ra = ld(sp, 112);
                lq(s5, sp, 96);
                lq(s4, sp, 80);
                lq(s3, sp, 64);
                lq(s2, sp, 48);
                lq(s1, sp, 32);
                lq(s0, sp, 16);
                lwc1(20, sp, 0);
                sp = addiu(sp, 416);
                return;
            }
        }
        charge(66);
        v1 = lb(s3, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, 6132);  // 0x8717F4
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        a0 = addiu(sp, 384);
        a1 = lw(v0, kResController);
        jal(0x44F3CCu, &gen::fn_sub_1AD940_001ad940);
        s0 = addiu(sp, 384);
        v1 = lb(s3, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4620);  // 0x86EDF4
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        a0 = addiu(sp, 400);
        a1 = lw(v0, kResController);
        jal(0x44F400u, &gen::fn_sub_1AD940_001ad940);
        v0 = addiu(sp, 400);
        lwc1(2, v0, 0);
        lwc1(1, v0, 4);
        lwc1(0, v0, 8);
        swc1(2, sp, 256);
        swc1(1, sp, 260);
        swc1(0, sp, 264);
        lwc1(2, s0, 0);
        lwc1(1, s0, 4);
        lwc1(0, s0, 8);
        swc1(2, sp, 240);
        swc1(1, sp, 244);
        swc1(0, sp, 248);
        lwc1(1, sp, 256);
        lwc1(0, sp, 240);
        sub_s(0, 1, 0);
        swc1(0, sp, 224);
        lwc1(1, sp, 260);
        lwc1(0, sp, 244);
        sub_s(0, 1, 0);
        swc1(0, sp, 228);
        lwc1(1, sp, 264);
        lwc1(0, sp, 248);
        sub_s(0, 1, 0);
        swc1(0, sp, 232);
        a0 = addiu(sp, 224);
        jal(0x44F470u, &gen::fn_sub_4C6AC0_004c6ac0);
        mov_s(20, 0);
        v1 = lb(s3, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
        a0 = addu(v0, v1);
        lwc1(12, s2, 20);
        jal(0x44F49Cu, &gen::fn_sub_1C6D70_001c6d70);
        if (v0 != 0) {
            charge(14);
            v1 = lb(s3, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
            a0 = addu(v0, v1);
            lwc1(12, s2, 20);
            jal(0x44F4CCu, &gen::fn_sub_1C6DD0_001c6dd0);
            s1 = v0;
            v1 = lb(s3, 24);
            if (v1 != s1) {
                charge(55);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6132);  // 0x8717F4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 352);
                a1 = lw(v0, kResController);
                jal(0x44F508u, &gen::fn_sub_1AD940_001ad940);
                s0 = addiu(sp, 352);
                v1 = lb(s3, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 368);
                a1 = lw(v0, kResController);
                jal(0x44F53Cu, &gen::fn_sub_1AD940_001ad940);
                v0 = addiu(sp, 368);
                lwc1(2, v0, 0);
                lwc1(1, v0, 4);
                lwc1(0, v0, 8);
                swc1(2, sp, 208);
                swc1(1, sp, 212);
                swc1(0, sp, 216);
                lwc1(2, s0, 0);
                lwc1(1, s0, 4);
                lwc1(0, s0, 8);
                swc1(2, sp, 192);
                swc1(1, sp, 196);
                swc1(0, sp, 200);
                lwc1(1, sp, 208);
                lwc1(0, sp, 192);
                sub_s(0, 1, 0);
                swc1(0, sp, 176);
                lwc1(1, sp, 212);
                lwc1(0, sp, 196);
                sub_s(0, 1, 0);
                swc1(0, sp, 180);
                lwc1(1, sp, 216);
                lwc1(0, sp, 200);
                sub_s(0, 1, 0);
                swc1(0, sp, 184);
                a0 = addiu(sp, 176);
                jal(0x44F5ACu, &gen::fn_sub_4C6AC0_004c6ac0);
                c_lt_s(0, 20);
                if (cond()) {
                    charge(19);
                    v1 = lb(s3, 24);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, 6132);  // 0x8717F4
                    v0 = addu(v0, v1);
                    v0 = lw(v0, 0);
                    a0 = addiu(sp, 336);
                    a1 = lw(v0, kResController);
                    jal(0x44F5E8u, &gen::fn_sub_1AD940_001ad940);
                    a0 = addiu(sp, 336);
                    a1 = lb(s3, 1);
                    jal(0x44F5F8u, &gen::fn_sub_454400_00454400);
                    v1 = si(1);
                    if (v0 == v1) {
                        charge(14);
                        s0 = dsll32(s1, 24);
                        s0 = dsra32(s0, 24);
                        v1 = lb(s3, 1);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                        a0 = addu(v0, v1);
                        jal(0x44F630u, &gen::fn_sub_1C65E0_001c65e0);
                        v1 = si(1);
                        if (v0 == v1) {
                            charge(4);
                            v0 = dsll32(s0, 24);
                            v0 = dsra32(v0, 24);
                            if (v0 != 0) {
                                charge(8);
                                a0 = s0;
                                jal(0x44F658u, &gen::fn_sub_437E20_00437e20);
                                v1 = dsll32(v0, 24);
                                v1 = dsra32(v1, 24);
                                v0 = si(1);
                                if (v1 == v0) {
                                    charge(13);
                                    a0 = lb(s3, 1);
                                    a1 = si(3);
                                    jal(0x44F67Cu, &gen::fn_sub_4543C0_004543c0);
                                    sb(s3, 24, s0);
                                    s4 = si(1);
                                    v1 = lb(s3, 1);
                                    v0 = lui(0x96u);
                                    v0 = addiu(v0, -15856);  // 0x95C210
                                    v0 = addu(v0, v1);
                                    sb(v0, 0, s4);
                                }
                            } else {
                                charge(13);
                                a0 = lb(s3, 1);
                                a1 = si(3);
                                jal(0x44F6B0u, &gen::fn_sub_4543C0_004543c0);
                                sb(s3, 24, s0);
                                s4 = si(1);
                                v1 = lb(s3, 1);
                                v0 = lui(0x96u);
                                v0 = addiu(v0, -15856);  // 0x95C210
                                v0 = addu(v0, v1);
                                sb(v0, 0, s4);
                            }
                        } else {
                            charge(5);
                            a0 = si(3173);
                            jal(0x44F6E0u, &gen::fn_datGetFlag_0016f190);
                            if (v0 == 0) {
                                charge(13);
                                sb(s3, 24, s0);
                                s4 = si(1);
                                v1 = lb(s3, 1);
                                v0 = lui(0x96u);
                                v0 = addiu(v0, -15856);  // 0x95C210
                                v0 = addu(v0, v1);
                                sb(v0, 0, s4);
                                a0 = lb(s3, 1);
                                a1 = si(3);
                                jal(0x44F714u, &gen::fn_sub_4543C0_004543c0);
                                v0 = si(24);
                                sb(s3, 3, v0);
                            }
                        }
                    }
                }
                charge(57);
                lwc1(20, s2, 4);
                v0 = sll(s1, 3);
                v0 = subu(v0, s1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6132);  // 0x8717F4
                s0 = addu(v0, v1);
                v0 = lw(s0, 0);
                a0 = addiu(sp, 304);
                a1 = lw(v0, kResController);
                jal(0x44F74Cu, &gen::fn_sub_1AD940_001ad940);
                s5 = addiu(sp, 304);
                v1 = lb(s3, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 320);
                a1 = lw(v0, kResController);
                jal(0x44F780u, &gen::fn_sub_1AD940_001ad940);
                v0 = addiu(sp, 320);
                lwc1(2, v0, 0);
                lwc1(1, v0, 4);
                lwc1(0, v0, 8);
                swc1(2, sp, 160);
                swc1(1, sp, 164);
                swc1(0, sp, 168);
                lwc1(2, s5, 0);
                lwc1(1, s5, 4);
                lwc1(0, s5, 8);
                swc1(2, sp, 144);
                swc1(1, sp, 148);
                swc1(0, sp, 152);
                s5 = 0;
                lwc1(1, sp, 160);
                lwc1(0, sp, 144);
                sub_s(0, 1, 0);
                swc1(0, sp, 128);
                lwc1(1, sp, 164);
                lwc1(0, sp, 148);
                sub_s(0, 1, 0);
                swc1(0, sp, 132);
                lwc1(1, sp, 168);
                lwc1(0, sp, 152);
                sub_s(0, 1, 0);
                swc1(0, sp, 136);
                a0 = addiu(sp, 128);
                jal(0x44F7F4u, &gen::fn_sub_4C6AC0_004c6ac0);
                c_lt_s(0, 20);
                if (cond()) {
                    charge(1);
                    s5 = si(1);
                }
                charge(3);
                v0 = si(1);
                if (s5 == v0) {
                    charge(26);
                    v1 = lb(s3, 1);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, -4620);  // 0x86EDF4
                    v0 = addu(v0, v1);
                    v0 = lw(v0, 0);
                    a0 = lw(v0, 296);
                    jal(0x44F83Cu, &gen::fn_sub_318B60_00318b60);
                    s5 = v0;
                    v0 = lw(s0, 0);
                    a0 = addiu(sp, 288);
                    a1 = lw(v0, kResController);
                    jal(0x44F854u, &gen::fn_sub_1AD940_001ad940);
                    a0 = s5;
                    a1 = addiu(sp, 288);
                    lwc1(12, s2, 16);
                    lwc1(13, s2, 20);
                    jal(0x44F86Cu, &gen::fn_sub_1C6450_001c6450);
                    v1 = si(1);
                    if (v0 == v1) {
                        charge(12);
                        v0 = lw(s0, 0);
                        a0 = addiu(sp, 272);
                        a1 = lw(v0, kResController);
                        jal(0x44F88Cu, &gen::fn_sub_1AD940_001ad940);
                        a0 = addiu(sp, 272);
                        a1 = lb(s3, 1);
                        jal(0x44F89Cu, &gen::fn_sub_454400_00454400);
                        v1 = si(1);
                        if (v0 == v1) {
                            charge(13);
                            s0 = dsll32(s1, 24);
                            s0 = dsra32(s0, 24);
                            a0 = lb(s3, 1);
                            v0 = sll(a0, 3);
                            v0 = subu(v0, a0);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -4308);  // 0x86EF2C
                            v0 = addu(v0, v1);
                            v0 = lw(v0, 0);
                            a1 = si(3);
                            if (v0 == a1) {
                                charge(4);
                                v0 = dsll32(s0, 24);
                                v0 = dsra32(v0, 24);
                                if (v0 != 0) {
                                    charge(8);
                                    a0 = s0;
                                    jal(0x44F8F8u, &gen::fn_sub_437E20_00437e20);
                                    v1 = dsll32(v0, 24);
                                    v1 = dsra32(v1, 24);
                                    v0 = si(1);
                                    if (v1 == v0) {
                                        charge(13);
                                        a0 = lb(s3, 1);
                                        a1 = si(3);
                                        jal(0x44F91Cu, &gen::fn_sub_4543C0_004543c0);
                                        sb(s3, 24, s0);
                                        s4 = si(1);
                                        v1 = lb(s3, 1);
                                        v0 = lui(0x96u);
                                        v0 = addiu(v0, -15856);  // 0x95C210
                                        v0 = addu(v0, v1);
                                        sb(v0, 0, s4);
                                    }
                                } else {
                                    charge(11);
                                    jal(0x44F948u, &gen::fn_sub_4543C0_004543c0);
                                    sb(s3, 24, s0);
                                    s4 = si(1);
                                    v1 = lb(s3, 1);
                                    v0 = lui(0x96u);
                                    v0 = addiu(v0, -15856);  // 0x95C210
                                    v0 = addu(v0, v1);
                                    sb(v0, 0, s4);
                                }
                            } else {
                                charge(8);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                a0 = addu(v0, v1);
                                jal(0x44F980u, &gen::fn_sub_1C65E0_001c65e0);
                                v1 = si(1);
                                if (v0 == v1) {
                                    charge(4);
                                    v0 = dsll32(s0, 24);
                                    v0 = dsra32(v0, 24);
                                    if (v0 != 0) {
                                        charge(8);
                                        a0 = s0;
                                        jal(0x44F9A8u, &gen::fn_sub_437E20_00437e20);
                                        v1 = dsll32(v0, 24);
                                        v1 = dsra32(v1, 24);
                                        v0 = si(1);
                                        if (v1 == v0) {
                                            charge(13);
                                            a0 = lb(s3, 1);
                                            a1 = si(3);
                                            jal(0x44F9CCu, &gen::fn_sub_4543C0_004543c0);
                                            sb(s3, 24, s0);
                                            s4 = si(1);
                                            v1 = lb(s3, 1);
                                            v0 = lui(0x96u);
                                            v0 = addiu(v0, -15856);  // 0x95C210
                                            v0 = addu(v0, v1);
                                            sb(v0, 0, s4);
                                        }
                                    } else {
                                        charge(13);
                                        a0 = lb(s3, 1);
                                        a1 = si(3);
                                        jal(0x44FA00u, &gen::fn_sub_4543C0_004543c0);
                                        sb(s3, 24, s0);
                                        s4 = si(1);
                                        v1 = lb(s3, 1);
                                        v0 = lui(0x96u);
                                        v0 = addiu(v0, -15856);  // 0x95C210
                                        v0 = addu(v0, v1);
                                        sb(v0, 0, s4);
                                    }
                                } else {
                                    charge(5);
                                    a0 = si(3173);
                                    jal(0x44FA30u, &gen::fn_datGetFlag_0016f190);
                                    if (v0 == 0) {
                                        charge(13);
                                        sb(s3, 24, s0);
                                        s4 = si(1);
                                        v1 = lb(s3, 1);
                                        v0 = lui(0x96u);
                                        v0 = addiu(v0, -15856);  // 0x95C210
                                        v0 = addu(v0, v1);
                                        sb(v0, 0, s4);
                                        a0 = lb(s3, 1);
                                        a1 = si(3);
                                        jal(0x44FA64u, &gen::fn_sub_4543C0_004543c0);
                                        v0 = si(24);
                                        sb(s3, 3, v0);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        charge(1);
        v0 = s4;
        charge(11);
        ra = ld(sp, 112);
        lq(s5, sp, 96);
        lq(s4, sp, 80);
        lq(s3, sp, 64);
        lq(s2, sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(20, sp, 0);
        sp = addiu(sp, 416);
    }

    // 0x44FAB0 (task): unless +65 is 1 (or gp-0x4634 with kind 2): for each used, living party member: when the unit
    // faces it (sub_1C6450 on the model matrix) and no other shadow is near (sub_454400), the nearest member (sub_1C6DD0)
    // is chased -- kind 3 directly (members other than the hero only when sub_437E20 allows, else the hero within reach
    // K_FldEvent_IsUnitWithinDistOfHero sub_1C7130), other kinds when it can see it (sub_1C65E0), or with flag 3173 off
    // (+3 = 24). Success: chase state (sub_4543C0(i, 3)), +24 = the member, the 0x95C210 byte = 1, returns 1.
    void sub_44FAB0() {
        enter(25);
        sp = addiu(sp, -144);
        sd(sp, 96, ra);
        sq(s5, sp, 80);
        sq(s4, sp, 64);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s1 = lw(a0, kTaskWork);
        s2 = 0;
        v1 = lb(s1, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4308);  // 0x86EF2C
        v0 = addu(v0, v1);
        a0 = lw(v0, 0);
        v1 = sll(a0, 6);
        v0 = lw(gp, -19040);
        s0 = addu(v0, v1);
        v0 = lb(s1, 65);
        v1 = si(1);
        if (v0 == v1) {
            charge(3);
            v0 = 0;
        } else {
            charge(3);
            v0 = lb(gp, -17972);
            if (v0 == v1) {
                charge(3);
                v0 = si(2);
                if (a0 == v0) {
                    charge(3);
                    v0 = 0;
                    charge(10);
                    ra = ld(sp, 96);
                    lq(s5, sp, 80);
                    lq(s4, sp, 64);
                    lq(s3, sp, 48);
                    lq(s2, sp, 32);
                    lq(s1, sp, 16);
                    lq(s0, sp, 0);
                    sp = addiu(sp, 144);
                    return;
                }
            }
            charge(3);
            s3 = 0;
            for (;;) {
                charge(3);
                v0 = slti(s3, 4);
                if (v0 == 0) break;
                backedge();
                charge(10);
                a1 = 0;
                v0 = sll(s3, 3);
                v0 = subu(v0, s3);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6048);  // 0x8717A0 gFldUnitsPc
                s4 = addu(v0, v1);
                a0 = lw(s4, 72);
                if (a0 != 0) {
                    charge(3);
                    v0 = lw(s4, 84);
                    if (v0 != 0) {
                        charge(1);
                        a1 = si(1);
                    }
                }
                charge(4);
                v1 = sltu(zero, a1);
                v0 = si(1);
                if (v1 == v0) {
                    charge(5);
                    jal(0x44FB98u, &gen::fn_datUnitIsGenusDead_002ff790);
                    v1 = si(1);
                    if (v0 != v1) {
                        charge(12);
                        v1 = lb(s1, 1);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                        a0 = addu(v0, v1);
                        lwc1(12, s0, 20);
                        jal(0x44FBCCu, &gen::fn_sub_1C6D70_001c6d70);
                        if (v0 != 0) {
                            charge(27);
                            s5 = addiu(s4, 84);
                            v1 = lb(s1, 1);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                            v0 = addu(v0, v1);
                            v0 = lw(v0, 84);
                            a0 = lw(v0, 296);
                            jal(0x44FC04u, &gen::fn_sub_318B60_00318b60);
                            s4 = v0;
                            v0 = lw(s5, 0);
                            a0 = addiu(sp, 128);
                            a1 = lw(v0, kResController);
                            jal(0x44FC1Cu, &gen::fn_sub_1AD940_001ad940);
                            a0 = s4;
                            a1 = addiu(sp, 128);
                            lwc1(12, s0, 16);
                            lwc1(13, s0, 20);
                            jal(0x44FC34u, &gen::fn_sub_1C6450_001c6450);
                            v1 = si(1);
                            if (v0 == v1) {
                                charge(12);
                                v0 = lw(s5, 0);
                                a0 = addiu(sp, 112);
                                a1 = lw(v0, kResController);
                                jal(0x44FC54u, &gen::fn_sub_1AD940_001ad940);
                                a0 = addiu(sp, 112);
                                a1 = lb(s1, 1);
                                jal(0x44FC64u, &gen::fn_sub_454400_00454400);
                                v1 = si(1);
                                if (v0 == v1) {
                                    charge(22);
                                    v1 = lb(s1, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                    a0 = addu(v0, v1);
                                    lwc1(12, s0, 20);
                                    jal(0x44FC98u, &gen::fn_sub_1C6DD0_001c6dd0);
                                    s4 = v0;
                                    v1 = lb(s1, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                    a0 = addu(v0, v1);
                                    v1 = lw(a0, 396);
                                    v0 = si(3);
                                    if (v1 == v0) {
                                        charge(2);
                                        if (s3 != 0) {
                                            charge(9);
                                            a0 = dsll32(s3, 24);
                                            a0 = dsra32(a0, 24);
                                            jal(0x44FCE0u, &gen::fn_sub_437E20_00437e20);
                                            v1 = dsll32(v0, 24);
                                            v1 = dsra32(v1, 24);
                                            v0 = si(1);
                                            if (v1 == v0) {
                                                charge(13);
                                                a0 = lb(s1, 1);
                                                a1 = si(3);
                                                jal(0x44FD04u, &gen::fn_sub_4543C0_004543c0);
                                                sb(s1, 24, s4);
                                                s2 = si(1);
                                                v1 = lb(s1, 1);
                                                v0 = lui(0x96u);
                                                v0 = addiu(v0, -15856);  // 0x95C210
                                                v0 = addu(v0, v1);
                                                sb(v0, 0, s2);
                                                break;
                                            }
                                        }
                                        charge(13);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                        a0 = addu(v0, v1);
                                        lwc1(12, s0, 20);
                                        jal(0x44FD50u, &gen::fn_sub_1C7130_001c7130);
                                        v1 = si(1);
                                        if (v0 != v1) {
                                            goto L_0044ff68;
                                        }
                                        charge(13);
                                        a0 = lb(s1, 1);
                                        a1 = si(3);
                                        jal(0x44FD6Cu, &gen::fn_sub_4543C0_004543c0);
                                        sb(s1, 24, zero);
                                        s2 = si(1);
                                        v1 = lb(s1, 1);
                                        v0 = lui(0x96u);
                                        v0 = addiu(v0, -15856);  // 0x95C210
                                        v0 = addu(v0, v1);
                                        sb(v0, 0, s2);
                                        break;
                                    }
                                    charge(5);
                                    jal(0x44FD98u, &gen::fn_sub_1C65E0_001c65e0);
                                    v1 = si(1);
                                    if (v0 == v1) {
                                        charge(2);
                                        if (s3 != 0) {
                                            charge(9);
                                            a0 = dsll32(s3, 24);
                                            a0 = dsra32(a0, 24);
                                            jal(0x44FDBCu, &gen::fn_sub_437E20_00437e20);
                                            v1 = dsll32(v0, 24);
                                            v1 = dsra32(v1, 24);
                                            v0 = si(1);
                                            if (v1 != v0) {
                                                goto L_0044ff68;
                                            }
                                            charge(13);
                                            a0 = lb(s1, 1);
                                            a1 = si(3);
                                            jal(0x44FDE0u, &gen::fn_sub_4543C0_004543c0);
                                            sb(s1, 24, s4);
                                            s2 = si(1);
                                            v1 = lb(s1, 1);
                                            v0 = lui(0x96u);
                                            v0 = addiu(v0, -15856);  // 0x95C210
                                            v0 = addu(v0, v1);
                                            sb(v0, 0, s2);
                                            break;
                                        }
                                        charge(13);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                        a0 = addu(v0, v1);
                                        lwc1(12, s0, 20);
                                        jal(0x44FE2Cu, &gen::fn_sub_1C7130_001c7130);
                                        v1 = si(1);
                                        if (v0 != v1) {
                                            goto L_0044ff68;
                                        }
                                        charge(13);
                                        a0 = lb(s1, 1);
                                        a1 = si(3);
                                        jal(0x44FE48u, &gen::fn_sub_4543C0_004543c0);
                                        sb(s1, 24, zero);
                                        s2 = si(1);
                                        v1 = lb(s1, 1);
                                        v0 = lui(0x96u);
                                        v0 = addiu(v0, -15856);  // 0x95C210
                                        v0 = addu(v0, v1);
                                        sb(v0, 0, s2);
                                        break;
                                    }
                                    charge(5);
                                    a0 = si(3173);
                                    jal(0x44FE78u, &gen::fn_datGetFlag_0016f190);
                                    if (v0 == 0) {
                                        charge(2);
                                        if (s3 != 0) {
                                            charge(9);
                                            a0 = dsll32(s3, 24);
                                            a0 = dsra32(a0, 24);
                                            jal(0x44FE98u, &gen::fn_sub_437E20_00437e20);
                                            v0 = dsll32(v0, 24);
                                            v0 = dsra32(v0, 24);
                                            a0 = si(1);
                                            if (v0 != a0) {
                                                goto L_0044ff68;
                                            }
                                            charge(16);
                                            sb(s1, 24, s3);
                                            v1 = lb(s1, 1);
                                            v0 = lui(0x96u);
                                            v0 = addiu(v0, -15856);  // 0x95C210
                                            v0 = addu(v0, v1);
                                            sb(v0, 0, a0);
                                            s2 = dsll32(a0, 24);
                                            s2 = dsra32(s2, 24);
                                            a0 = lb(s1, 1);
                                            a1 = si(3);
                                            jal(0x44FEDCu, &gen::fn_sub_4543C0_004543c0);
                                            v0 = si(24);
                                            sb(s1, 3, v0);
                                            break;
                                        }
                                        charge(13);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                        a0 = addu(v0, v1);
                                        lwc1(12, s0, 20);
                                        jal(0x44FF14u, &gen::fn_sub_1C7130_001c7130);
                                        a0 = si(1);
                                        if (v0 == a0) {
                                            charge(16);
                                            sb(s1, 24, zero);
                                            v1 = lb(s1, 1);
                                            v0 = lui(0x96u);
                                            v0 = addiu(v0, -15856);  // 0x95C210
                                            v0 = addu(v0, v1);
                                            sb(v0, 0, a0);
                                            s2 = dsll32(a0, 24);
                                            s2 = dsra32(s2, 24);
                                            a0 = lb(s1, 1);
                                            a1 = si(3);
                                            jal(0x44FF50u, &gen::fn_sub_4543C0_004543c0);
                                            v0 = si(24);
                                            sb(s1, 3, v0);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
              L_0044ff68:
                charge(1);
                s3 = addiu(s3, 1);
            }
            charge(1);
            v0 = s2;
        }
        charge(10);
        ra = ld(sp, 96);
        lq(s5, sp, 80);
        lq(s4, sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 144);
    }

    // 0x44FFB0 (task): unless +65 is 1: the hero (gFldUnitsPc[0]) used and alive and in front of the model (sub_1C6450):
    // seen (sub_1C65E0) -> chase the hero; not seen but flag 3173 off -> chase with +3 = 24. Returns 1 on success.
    void sub_44FFB0() {
        enter(14);
        sp = addiu(sp, -96);
        sd(sp, 64, ra);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s1 = lw(a0, kTaskWork);
        s2 = 0;
        v0 = lw(gp, -19040);
        s0 = addiu(v0, 64);
        v0 = lb(s1, 65);
        v1 = si(1);
        if (v0 == v1) {
            charge(3);
            v0 = 0;
        } else {
            charge(5);
            a1 = 0;
            v0 = lui(0x87u);
            a0 = lw(v0, 6120);  // 0x8717E8
            if (a0 != 0) {
                charge(4);
                v0 = lui(0x87u);
                v0 = lw(v0, 6132);  // 0x8717F4
                if (v0 != 0) {
                    charge(1);
                    a1 = v1;
                }
            }
            charge(4);
            v1 = sltu(zero, a1);
            v0 = si(1);
            if (v1 == v0) {
                charge(5);
                jal(0x45002Cu, &gen::fn_datUnitIsGenusDead_002ff790);
                v1 = si(1);
                if (v0 != v1) {
                    charge(12);
                    v1 = lb(s1, 1);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                    a0 = addu(v0, v1);
                    lwc1(12, s0, 20);
                    jal(0x450060u, &gen::fn_sub_1C6D70_001c6d70);
                    if (v0 != 0) {
                        charge(27);
                        v1 = lb(s1, 1);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, -4620);  // 0x86EDF4
                        v0 = addu(v0, v1);
                        v0 = lw(v0, 0);
                        a0 = lw(v0, 296);
                        jal(0x450094u, &gen::fn_sub_318B60_00318b60);
                        s3 = v0;
                        v0 = lui(0x87u);
                        v0 = lw(v0, 6132);  // 0x8717F4
                        a0 = addiu(sp, 80);
                        a1 = lw(v0, kResController);
                        jal(0x4500B0u, &gen::fn_sub_1AD940_001ad940);
                        a0 = s3;
                        a1 = addiu(sp, 80);
                        lwc1(12, s0, 16);
                        lwc1(13, s0, 20);
                        jal(0x4500C8u, &gen::fn_sub_1C6450_001c6450);
                        v1 = si(1);
                        if (v0 == v1) {
                            charge(12);
                            v1 = lb(s1, 1);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                            a0 = addu(v0, v1);
                            jal(0x4500F8u, &gen::fn_sub_1C65E0_001c65e0);
                            v1 = si(1);
                            if (v0 == v1) {
                                charge(13);
                                a0 = lb(s1, 1);
                                a1 = si(3);
                                jal(0x450114u, &gen::fn_sub_4543C0_004543c0);
                                sb(s1, 24, zero);
                                s2 = si(1);
                                v1 = lb(s1, 1);
                                v0 = lui(0x96u);
                                v0 = addiu(v0, -15856);  // 0x95C210
                                v0 = addu(v0, v1);
                                sb(v0, 0, s2);
                            } else {
                                charge(5);
                                a0 = si(3173);
                                jal(0x450144u, &gen::fn_datGetFlag_0016f190);
                                if (v0 == 0) {
                                    charge(13);
                                    sb(s1, 24, zero);
                                    s2 = si(1);
                                    v1 = lb(s1, 1);
                                    v0 = lui(0x96u);
                                    v0 = addiu(v0, -15856);  // 0x95C210
                                    v0 = addu(v0, v1);
                                    sb(v0, 0, s2);
                                    a0 = lb(s1, 1);
                                    a1 = si(3);
                                    jal(0x450178u, &gen::fn_sub_4543C0_004543c0);
                                    v0 = si(24);
                                    sb(s1, 3, v0);
                                }
                            }
                        }
                    }
                }
            }
            charge(1);
            v0 = s2;
        }
        charge(8);
        ra = ld(sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 96);
    }

    // 0x4534B0 (ec): one expansion of shadow ec's path search from the cell (+120, +121) (the think work of gFldUnitsEc[ec]
    // +364): for each open side (bits 1 / 2 / 8 / 4 = z - 1, x - 1, x + 1, z + 1) whose neighbour is free of other shadows
    // (sub_454400) or the shadow is of kind 4, and whose path record (+152 + 8 cell: u16 x, z, from x, from z) is still
    // empty: the record is filled, the cell appended to the list +2200 (+148 counts), and when it is the target cell (+139 /
    // +140) the target's record points back and 2 is returned. The cell (0, 0) instead sets work +0 = 42 and returns 1;
    // no new cell returns 0.
    void sub_4534B0() {
        enter(23);
        sp = addiu(sp, -80);
        sd(sp, 48, ra);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        v1 = dsll32(a0, 24);
        v1 = dsra32(v1, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4340);  // 0x86EF0C
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        s2 = lw(v0, kTaskWork);
        v1 = lbu(s2, 139);
        v0 = lbu(s2, 140);
        v0 = sll(v0, 4);
        v0 = addu(v1, v0);
        s1 = v0 & 0xFFu;
        v0 = lbu(s2, 120);
        if (v0 == 0) {
            charge(3);
            v0 = lbu(s2, 121);
            if (v0 == 0) {
                charge(5);
                v0 = si(42);
                sb(s2, 0, v0);
                v0 = si(1);
                charge(7);
                ra = ld(sp, 48);
                lq(s2, sp, 32);
                lq(s1, sp, 16);
                lq(s0, sp, 0);
                sp = addiu(sp, 80);
                return;
            }
        }
        charge(13);
        s0 = lbu(s2, 120);
        jal(0x453530u, &gen::fn_K_Field_Get_001b9120);
        v1 = lbu(s2, 121);
        v1 = sll(v1, 8);
        v1 = addu(v0, v1);
        v0 = s0 & 0xFFu;
        v0 = sll(v0, 4);
        v0 = addu(v1, v0);
        v0 = lbu(v0, 83);
        v0 = v0 & 0x1u;
        if (v0 != 0) {
            charge(4);
            v0 = lui(0x4448u);
            mtc1(v0, 1);  // 800.0
            if (gez(s0)) {
                charge(5);
                mtc1(s0, 0);
                cvt_s_w(0, 0);
            } else {
                charge(7);
                v1 = srl(s0, 1);
                v0 = s0 & 0x1u;
                v1 = v1 | v0;
                mtc1(v1, 0);
                cvt_s_w(0, 0);
                add_s(0, 0, 0);
            }
            charge(19);
            mul_s(0, 1, 0);
            swc1(0, sp, 64);
            v0 = lbu(s2, 121);
            v0 = addiu(v0, -1);
            mtc1(v0, 0);
            cvt_s_w(1, 0);
            v0 = lui(0x4448u);
            mtc1(v0, 0);  // 800.0
            mul_s(0, 0, 1);
            swc1(0, sp, 72);
            a0 = addiu(sp, 64);
            a1 = lb(s2, 1);
            jal(0x4535D8u, &gen::fn_sub_454400_00454400);
            v1 = si(1);
            if (v0 != v1) {
                charge(11);
                v1 = lb(s2, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4308);  // 0x86EF2C
                v0 = addu(v0, v1);
                v1 = lw(v0, 0);
                v0 = si(4);
                if (v1 != v0) {
                    goto L_004536ec;
                }
            }
            charge(12);
            a3 = lbu(s2, 120);
            v0 = lbu(s2, 121);
            v0 = addiu(v0, -1);
            v0 = sll(v0, 4);
            v0 = addu(a3, v0);
            a2 = v0 & 0xFFu;
            v0 = sll(a2, 3);
            a0 = addu(v0, s2);
            a1 = addiu(a0, 152);
            v0 = lh(a0, 152);
            if (v0 == 0) {
                charge(4);
                v1 = addiu(a0, 154);
                v0 = lh(a0, 154);
                if (v0 == 0) {
                    charge(19);
                    sh(a1, 0, a3);
                    v0 = lbu(s2, 121);
                    v0 = addiu(v0, -1);
                    sh(v1, 0, v0);
                    v0 = lbu(s2, 120);
                    sh(a0, 156, v0);
                    v0 = lbu(s2, 121);
                    sh(a0, 158, v0);
                    v0 = lw(s2, 148);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s2);
                    sw(v0, 2200, a2);
                    v0 = lw(s2, 148);
                    v0 = addiu(v0, 1);
                    sw(s2, 148, v0);
                    a0 = lbu(s2, 139);
                    v0 = lh(a1, 0);
                    if (v0 == a0) {
                        charge(4);
                        v1 = lh(v1, 0);
                        v0 = lbu(s2, 140);
                        if (v1 == v0) {
                            charge(14);
                            v0 = s1 & 0xFFu;
                            v0 = sll(v0, 3);
                            v1 = addu(v0, s2);
                            sh(v1, 152, a0);
                            v0 = lbu(s2, 140);
                            sh(v1, 154, v0);
                            v0 = lbu(s2, 139);
                            sh(v1, 156, v0);
                            v0 = lbu(s2, 140);
                            v0 = addiu(v0, 1);
                            sh(v1, 158, v0);
                            v0 = si(2);
                            charge(7);
                            ra = ld(sp, 48);
                            lq(s2, sp, 32);
                            lq(s1, sp, 16);
                            lq(s0, sp, 0);
                            sp = addiu(sp, 80);
                            return;
                        }
                    }
                }
            }
        }
      L_004536ec:
        charge(13);
        s0 = lbu(s2, 120);
        jal(0x4536F0u, &gen::fn_K_Field_Get_001b9120);
        a1 = lbu(s2, 121);
        v1 = sll(a1, 8);
        a0 = addu(v0, v1);
        v1 = s0 & 0xFFu;
        v0 = sll(v1, 4);
        v0 = addu(a0, v0);
        v0 = lbu(v0, 83);
        v0 = v0 & 0x2u;
        if (v0 != 0) {
            charge(11);
            v0 = addiu(v1, -1);
            mtc1(v0, 0);
            cvt_s_w(1, 0);
            v0 = lui(0x4448u);
            mtc1(v0, 0);  // 800.0
            mul_s(0, 0, 1);
            swc1(0, sp, 64);
            if (gez(a1)) {
                charge(5);
                mtc1(a1, 0);
                cvt_s_w(1, 0);
            } else {
                charge(7);
                v1 = srl(a1, 1);
                v0 = a1 & 0x1u;
                v1 = v1 | v0;
                mtc1(v1, 0);
                cvt_s_w(1, 0);
                add_s(1, 1, 1);
            }
            charge(12);
            v0 = lui(0x4448u);
            mtc1(v0, 0);  // 800.0
            mul_s(0, 0, 1);
            swc1(0, sp, 72);
            a0 = addiu(sp, 64);
            a1 = lb(s2, 1);
            jal(0x453798u, &gen::fn_sub_454400_00454400);
            v1 = si(1);
            if (v0 != v1) {
                charge(11);
                v1 = lb(s2, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4308);  // 0x86EF2C
                v0 = addu(v0, v1);
                v1 = lw(v0, 0);
                v0 = si(4);
                if (v1 != v0) {
                    goto L_00453918;
                }
            }
            charge(11);
            v0 = lbu(s2, 121);
            v1 = sll(v0, 4);
            v0 = lbu(s2, 120);
            a1 = addiu(v0, -1);
            v0 = addu(a1, v1);
            v0 = sll(v0, 3);
            a0 = addu(v0, s2);
            v1 = addiu(a0, 152);
            v0 = lh(a0, 152);
            if (v0 == 0) {
                charge(3);
                v0 = lh(a0, 154);
                if (v0 == 0) {
                    charge(48);
                    sh(v1, 0, a1);
                    a0 = lbu(s2, 121);
                    v0 = lbu(s2, 120);
                    v1 = addiu(v0, -1);
                    v0 = sll(a0, 4);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s2);
                    sh(v0, 154, a0);
                    a0 = lbu(s2, 120);
                    v0 = lbu(s2, 121);
                    v1 = sll(v0, 4);
                    v0 = addiu(a0, -1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s2);
                    sh(v0, 156, a0);
                    a0 = lbu(s2, 121);
                    v0 = lbu(s2, 120);
                    v1 = addiu(v0, -1);
                    v0 = sll(a0, 4);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s2);
                    sh(v0, 158, a0);
                    v0 = lbu(s2, 120);
                    v1 = addiu(v0, -1);
                    v0 = lbu(s2, 121);
                    v0 = sll(v0, 4);
                    v1 = addu(v1, v0);
                    v0 = lw(s2, 148);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s2);
                    sw(v0, 2200, v1);
                    v0 = lw(s2, 148);
                    v0 = addiu(v0, 1);
                    sw(s2, 148, v0);
                    a0 = lbu(s2, 139);
                    v0 = lbu(s2, 121);
                    v1 = sll(v0, 4);
                    v0 = lbu(s2, 120);
                    v0 = addiu(v0, -1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 3);
                    v1 = addu(v0, s2);
                    v0 = lh(v1, 152);
                    if (v0 == a0) {
                        charge(4);
                        v1 = lh(v1, 154);
                        v0 = lbu(s2, 140);
                        if (v1 == v0) {
                            charge(14);
                            v0 = s1 & 0xFFu;
                            v0 = sll(v0, 3);
                            v1 = addu(v0, s2);
                            sh(v1, 152, a0);
                            v0 = lbu(s2, 140);
                            sh(v1, 154, v0);
                            v0 = lbu(s2, 139);
                            v0 = addiu(v0, 1);
                            sh(v1, 156, v0);
                            v0 = lbu(s2, 140);
                            sh(v1, 158, v0);
                            v0 = si(2);
                            charge(7);
                            ra = ld(sp, 48);
                            lq(s2, sp, 32);
                            lq(s1, sp, 16);
                            lq(s0, sp, 0);
                            sp = addiu(sp, 80);
                            return;
                        }
                    }
                }
            }
        }
      L_00453918:
        charge(13);
        s0 = lbu(s2, 120);
        jal(0x45391Cu, &gen::fn_K_Field_Get_001b9120);
        a1 = lbu(s2, 121);
        v1 = sll(a1, 8);
        a0 = addu(v0, v1);
        v1 = s0 & 0xFFu;
        v0 = sll(v1, 4);
        v0 = addu(a0, v0);
        v0 = lbu(v0, 83);
        v0 = v0 & 0x8u;
        if (v0 != 0) {
            charge(11);
            v0 = addiu(v1, 1);
            mtc1(v0, 0);
            cvt_s_w(1, 0);
            v0 = lui(0x4448u);
            mtc1(v0, 0);  // 800.0
            mul_s(0, 0, 1);
            swc1(0, sp, 64);
            if (gez(a1)) {
                charge(5);
                mtc1(a1, 0);
                cvt_s_w(1, 0);
            } else {
                charge(7);
                v1 = srl(a1, 1);
                v0 = a1 & 0x1u;
                v1 = v1 | v0;
                mtc1(v1, 0);
                cvt_s_w(1, 0);
                add_s(1, 1, 1);
            }
            charge(12);
            v0 = lui(0x4448u);
            mtc1(v0, 0);  // 800.0
            mul_s(0, 0, 1);
            swc1(0, sp, 72);
            a0 = addiu(sp, 64);
            a1 = lb(s2, 1);
            jal(0x4539C4u, &gen::fn_sub_454400_00454400);
            v1 = si(1);
            if (v0 != v1) {
                charge(11);
                v1 = lb(s2, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4308);  // 0x86EF2C
                v0 = addu(v0, v1);
                v1 = lw(v0, 0);
                v0 = si(4);
                if (v1 != v0) {
                    goto L_00453b44;
                }
            }
            charge(11);
            v0 = lbu(s2, 121);
            v1 = sll(v0, 4);
            v0 = lbu(s2, 120);
            a1 = addiu(v0, 1);
            v0 = addu(a1, v1);
            v0 = sll(v0, 3);
            a0 = addu(v0, s2);
            v1 = addiu(a0, 152);
            v0 = lh(a0, 152);
            if (v0 == 0) {
                charge(3);
                v0 = lh(a0, 154);
                if (v0 == 0) {
                    charge(48);
                    sh(v1, 0, a1);
                    a0 = lbu(s2, 121);
                    v0 = lbu(s2, 120);
                    v1 = addiu(v0, 1);
                    v0 = sll(a0, 4);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s2);
                    sh(v0, 154, a0);
                    a0 = lbu(s2, 120);
                    v0 = lbu(s2, 121);
                    v1 = sll(v0, 4);
                    v0 = addiu(a0, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s2);
                    sh(v0, 156, a0);
                    a0 = lbu(s2, 121);
                    v0 = lbu(s2, 120);
                    v1 = addiu(v0, 1);
                    v0 = sll(a0, 4);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s2);
                    sh(v0, 158, a0);
                    v0 = lbu(s2, 120);
                    v1 = addiu(v0, 1);
                    v0 = lbu(s2, 121);
                    v0 = sll(v0, 4);
                    v1 = addu(v1, v0);
                    v0 = lw(s2, 148);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s2);
                    sw(v0, 2200, v1);
                    v0 = lw(s2, 148);
                    v0 = addiu(v0, 1);
                    sw(s2, 148, v0);
                    a0 = lbu(s2, 139);
                    v0 = lbu(s2, 121);
                    v1 = sll(v0, 4);
                    v0 = lbu(s2, 120);
                    v0 = addiu(v0, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 3);
                    v1 = addu(v0, s2);
                    v0 = lh(v1, 152);
                    if (v0 == a0) {
                        charge(4);
                        v1 = lh(v1, 154);
                        v0 = lbu(s2, 140);
                        if (v1 == v0) {
                            charge(14);
                            v0 = s1 & 0xFFu;
                            v0 = sll(v0, 3);
                            v1 = addu(v0, s2);
                            sh(v1, 152, a0);
                            v0 = lbu(s2, 140);
                            sh(v1, 154, v0);
                            v0 = lbu(s2, 139);
                            v0 = addiu(v0, -1);
                            sh(v1, 156, v0);
                            v0 = lbu(s2, 140);
                            sh(v1, 158, v0);
                            v0 = si(2);
                            charge(7);
                            ra = ld(sp, 48);
                            lq(s2, sp, 32);
                            lq(s1, sp, 16);
                            lq(s0, sp, 0);
                            sp = addiu(sp, 80);
                            return;
                        }
                    }
                }
            }
        }
      L_00453b44:
        charge(13);
        s0 = lbu(s2, 120);
        jal(0x453B48u, &gen::fn_K_Field_Get_001b9120);
        v1 = lbu(s2, 121);
        v1 = sll(v1, 8);
        v1 = addu(v0, v1);
        v0 = s0 & 0xFFu;
        v0 = sll(v0, 4);
        v0 = addu(v1, v0);
        v0 = lbu(v0, 83);
        v0 = v0 & 0x4u;
        if (v0 != 0) {
            charge(4);
            v0 = lui(0x4448u);
            mtc1(v0, 1);  // 800.0
            if (gez(s0)) {
                charge(5);
                mtc1(s0, 0);
                cvt_s_w(0, 0);
            } else {
                charge(7);
                v1 = srl(s0, 1);
                v0 = s0 & 0x1u;
                v1 = v1 | v0;
                mtc1(v1, 0);
                cvt_s_w(0, 0);
                add_s(0, 0, 0);
            }
            charge(19);
            mul_s(0, 1, 0);
            swc1(0, sp, 64);
            v0 = lbu(s2, 121);
            v0 = addiu(v0, 1);
            mtc1(v0, 0);
            cvt_s_w(1, 0);
            v0 = lui(0x4448u);
            mtc1(v0, 0);  // 800.0
            mul_s(0, 0, 1);
            swc1(0, sp, 72);
            a0 = addiu(sp, 64);
            a1 = lb(s2, 1);
            jal(0x453BF0u, &gen::fn_sub_454400_00454400);
            v1 = si(1);
            if (v0 != v1) {
                charge(11);
                v1 = lb(s2, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4308);  // 0x86EF2C
                v0 = addu(v0, v1);
                v1 = lw(v0, 0);
                v0 = si(4);
                if (v1 != v0) {
                    goto L_00453d70;
                }
            }
            charge(11);
            v0 = lbu(s2, 121);
            v0 = addiu(v0, 1);
            v0 = sll(v0, 4);
            a1 = lbu(s2, 120);
            v0 = addu(a1, v0);
            v0 = sll(v0, 3);
            a0 = addu(v0, s2);
            v1 = addiu(a0, 152);
            v0 = lh(a0, 152);
            if (v0 == 0) {
                charge(3);
                v0 = lh(a0, 154);
                if (v0 == 0) {
                    charge(48);
                    sh(v1, 0, a1);
                    v0 = lbu(s2, 121);
                    a0 = addiu(v0, 1);
                    v1 = lbu(s2, 120);
                    v0 = sll(a0, 4);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s2);
                    sh(v0, 154, a0);
                    v1 = lbu(s2, 120);
                    v0 = lbu(s2, 121);
                    v0 = addiu(v0, 1);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s2);
                    sh(v0, 156, v1);
                    a0 = lbu(s2, 121);
                    v1 = lbu(s2, 120);
                    v0 = addiu(a0, 1);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, s2);
                    sh(v0, 158, a0);
                    v0 = lbu(s2, 121);
                    v0 = addiu(v0, 1);
                    v1 = sll(v0, 4);
                    v0 = lbu(s2, 120);
                    v1 = addu(v0, v1);
                    v0 = lw(s2, 148);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s2);
                    sw(v0, 2200, v1);
                    v0 = lw(s2, 148);
                    v0 = addiu(v0, 1);
                    sw(s2, 148, v0);
                    a0 = lbu(s2, 139);
                    v0 = lbu(s2, 121);
                    v0 = addiu(v0, 1);
                    v1 = sll(v0, 4);
                    v0 = lbu(s2, 120);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 3);
                    v1 = addu(v0, s2);
                    v0 = lh(v1, 152);
                    if (v0 == a0) {
                        charge(4);
                        v1 = lh(v1, 154);
                        v0 = lbu(s2, 140);
                        if (v1 == v0) {
                            charge(14);
                            v0 = s1 & 0xFFu;
                            v0 = sll(v0, 3);
                            v1 = addu(v0, s2);
                            sh(v1, 152, a0);
                            v0 = lbu(s2, 140);
                            sh(v1, 154, v0);
                            v0 = lbu(s2, 139);
                            sh(v1, 156, v0);
                            v0 = lbu(s2, 140);
                            v0 = addiu(v0, -1);
                            sh(v1, 158, v0);
                            v0 = si(2);
                            charge(7);
                            ra = ld(sp, 48);
                            lq(s2, sp, 32);
                            lq(s1, sp, 16);
                            lq(s0, sp, 0);
                            sp = addiu(sp, 80);
                            return;
                        }
                    }
                }
            }
        }
      L_00453d70:
        charge(1);
        v0 = 0;
        charge(7);
        ra = ld(sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 80);
    }
};

struct EneStates : EneLook {
    using EneLook::EneLook;

    // 0x453ED0 (ec, x, z, pos, tx, tz; tx / tz in $a4 / $a5): resets shadow ec's path search in its think work: own cell
    // +92 / +93 = +120 / +121 = (x, z), +80 / +96 = pos, the 256 path records (+152 + 8 i) and the frontier list (+2200 +
    // 4 i) cleared, +148 = 0, the start +141 / +142 and target +139 / +140. Same start and target: 0. Else sub_4534B0
    // expands frontier cells (each round pops the list's head into +120 / +121, shifting the 255 others down and
    // recounting +148) until it reports 2 (found) or 1 (the dead end (0, 0) -- then 0 is returned); found: sub_453D90 builds
    // the step list and 1 is returned.
    void sub_453ED0() {
        enter(33);
        sp = addiu(sp, -64);
        sd(sp, 32, ra);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        lwc1(2, a3, 0);
        lwc1(1, a3, 4);
        lwc1(0, a3, 8);
        swc1(2, sp, 48);
        swc1(1, sp, 52);
        swc1(0, sp, 56);
        v1 = dsll32(a0, 24);
        v1 = dsra32(v1, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4340);  // 0x86EF0C
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        s0 = lw(v0, kTaskWork);
        sb(s0, 92, a1);
        sb(s0, 120, a1);
        sb(s0, 93, a2);
        sb(s0, 121, a2);
        lwc1(2, sp, 48);
        lwc1(1, sp, 52);
        lwc1(0, sp, 56);
        swc1(2, s0, 80);
        swc1(1, s0, 84);
        swc1(0, s0, 88);
        v1 = 0;
        for (;;) {
            charge(3);
            v0 = slti(v1, 256);
            if (v0 == 0) break;
            backedge();
            charge(10);
            v0 = sll(v1, 3);
            v0 = addu(s0, v0);
            sh(v0, 152, zero);
            sh(v0, 154, zero);
            sh(v0, 156, zero);
            sh(v0, 158, zero);
            v0 = sll(v1, 2);
            v0 = addu(s0, v0);
            sw(v0, 2200, zero);
            v1 = addiu(v1, 1);
        }
        charge(17);
        sw(s0, 148, zero);
        sb(s0, 141, a1);
        sb(s0, 142, a2);
        sb(s0, 139, a4);
        sb(s0, 140, a5);
        lwc1(2, sp, 48);
        lwc1(1, sp, 52);
        lwc1(0, sp, 56);
        swc1(2, s0, 96);
        swc1(1, s0, 100);
        swc1(0, s0, 104);
        v1 = dsll32(a1, 24);
        v1 = dsra32(v1, 24);
        v0 = dsll32(a4, 24);
        v0 = dsra32(v0, 24);
        if (v1 == v0) {
            charge(6);
            v1 = dsll32(a2, 24);
            v1 = dsra32(v1, 24);
            v0 = dsll32(a5, 24);
            v0 = dsra32(v0, 24);
            if (v1 == v0) {
                charge(3);
                v0 = 0;
                charge(6);
                ra = ld(sp, 32);
                lq(s1, sp, 16);
                lq(s0, sp, 0);
                sp = addiu(sp, 64);
                return;
            }
        }
        charge(1);
        s1 = 0;
        for (;;) {
            charge(19);
            a0 = lb(s0, 1);
            jal(0x453FF8u, &gen::fn_sub_4534B0_004534b0);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            a0 = lb(s0, 1);
            v1 = sll(a0, 3);
            v1 = subu(v1, a0);
            a0 = sll(v1, 6);
            v1 = lui(0x87u);
            v1 = addiu(v1, -4704);  // 0x86EDA0 gFldUnitsEc
            v1 = addu(v1, a0);
            v1 = lw(v1, 364);
            a2 = lw(v1, kTaskWork);
            a1 = lw(a2, 2200);
            sw(a2, 148, zero);
            a3 = 0;
            for (;;) {
                charge(3);
                v1 = slti(a3, 255);
                if (v1 == 0) break;
                backedge();
                charge(6);
                v1 = sll(a3, 2);
                a0 = addu(a2, v1);
                v1 = lw(a0, 2204);
                sw(a0, 2200, v1);
                if (v1 != 0) {
                    charge(3);
                    v1 = lw(a2, 148);
                    v1 = addiu(v1, 1);
                    sw(a2, 148, v1);
                }
                charge(1);
                a3 = addiu(a3, 1);
            }
            charge(11);
            v1 = sll(a1, 3);
            a0 = addu(a2, v1);
            v1 = lh(a0, 152);
            sb(a2, 120, v1);
            v1 = lh(a0, 154);
            sb(a2, 121, v1);
            a0 = dsll32(v0, 24);
            a0 = dsra32(a0, 24);
            v1 = si(1);
            if (a0 == v1) {
                charge(3);
                v0 = si(2);
                s1 = dsll32(v1, 24);
                s1 = dsra32(s1, 24);
            }
            charge(5);
            v1 = dsll32(v0, 24);
            v1 = dsra32(v1, 24);
            v0 = si(2);
            if (v1 == v0) break;
            backedge();
        }
        charge(4);
        v0 = dsll32(s1, 24);
        v0 = dsra32(v0, 24);
        if (v0 == 0) {
            charge(6);
            a0 = lb(s0, 1);
            jal(0x4540D4u, &gen::fn_sub_453D90_00453d90);
            v0 = si(1);
        } else {
            charge(1);
            v0 = 0;
        }
        charge(6);
        ra = ld(sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 64);
    }

    // 0x44B7D0 (think state 4 for behaviour kind 1, the record gp-0x4A60 + 64; sub-state +4 by a jump table at 0x7BC5C0):
    // 0 clears the 0x95C210 byte -> 1; 1 / 2 look for the hero (sub_44FFB0: spotted -> the queue cleared, +7 = record
    // +36, sub-state 9); 1 picks a random point around the unit's position (direction (RpRandom() % 200) / 25 over 8
    // directions by the jump table 0x7BC5A0, distance (RpRandom() % 4000) / 10), sets the mover's speed (sub_1B0250, record
    // +32) and queues a walk there (sub_1AFA20) and a pause of record +24 .. +28 frames (sub_1AFF70) -> 2; 2 waits for the
    // queue to empty (sub_1B0220) -> 1; 5 / 6 walk back to the model's position and return to state 4 (sub_4543C0) once in
    // the start cell; 9 counts +7 down, then chase (sub_4543C0(i, 3)).
    void sub_44B7D0() {
        enter(13);
        sp = addiu(sp, -128);
        sd(sp, 64, ra);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s0 = lw(a0, kTaskWork);
        v1 = lw(gp, -19040);
        s3 = addiu(v1, 64);
        v1 = lb(s0, 4);
        at = sltiu(v1, 10);
        if (at != 0) {
            charge(7);
            a1 = lui(0x7Cu);
            a1 = addiu(a1, -14912);  // 0x7BC5C0
            v1 = sll(v1, 2);
            v1 = addu(v1, a1);
            v1 = lw(v1, 0);
            switch (w(v1)) {  // jump table 0x7BC5C0
            default:
                dispatch(v1);
                return;
            case 0x44B820u:  // [0]
                charge(7);
                v1 = lb(s0, 1);
                v0 = lui(0x96u);
                v0 = addiu(v0, -15856);  // 0x95C210
                v0 = addu(v0, v1);
                sb(v0, 0, zero);
                v0 = si(1);
                sb(s0, 4, v0);
            case 0x44B83Cu:  // [1]
                charge(7);
                jal(0x44B83Cu, &gen::fn_sub_44FFB0_0044ffb0);
                v1 = dsll32(v0, 24);
                v1 = dsra32(v1, 24);
                v0 = si(1);
                if (v1 == v0) {
                    charge(27);
                    v1 = lb(s0, 1);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, -4336);  // 0x86EF10
                    v0 = addu(v0, v1);
                    a0 = lw(v0, 0);
                    a1 = 0;
                    jal(0x44B87Cu, &gen::fn_sub_1B0250_001b0250);
                    v1 = lb(s0, 1);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, -4336);  // 0x86EF10
                    v0 = addu(v0, v1);
                    a0 = lw(v0, 0);
                    jal(0x44B8A4u, &gen::fn_sub_1B00C0_001b00c0);
                    v1 = lw(s3, 36);
                    sb(s0, 7, v1);
                    v1 = si(9);
                    sb(s0, 4, v1);
                    break;
                }
                charge(37);
                jal(0x44B8C4u, &gen::fn_sub_488F30_00488f30);
                v1 = si(200);
                divu(v0, v1);
                mfhi(v1);
                v0 = si(25);
                divu(v1, v0);
                mflo(v0);
                s2 = dsll32(v0, 24);
                s2 = dsra32(s2, 24);
                jal(0x44B8ECu, &gen::fn_sub_488F30_00488f30);
                v1 = si(4000);
                divu(v0, v1);
                mfhi(v1);
                v0 = si(10);
                divu(v1, v0);
                mflo(v0);
                s1 = dsll32(v0, 16);
                s1 = dsra32(s1, 16);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 112);
                a1 = lw(v0, kResController);
                jal(0x44B93Cu, &gen::fn_sub_1AD940_001ad940);
                v0 = dsll32(s2, 24);
                v0 = dsra32(v0, 24);
                at = sltiu(v0, 8);
                if (at != 0) {
                    charge(7);
                    v1 = lui(0x7Cu);
                    v1 = addiu(v1, -14944);  // 0x7BC5A0
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    v0 = lw(v0, 0);
                    switch (w(v0)) {  // jump table 0x7BC5A0
                    default:
                        dispatch(v0);
                        return;
                    case 0x44B974u:  // [0]
                        charge(8);
                        lwc1(1, sp, 120);
                        mtc1(s1, 0);
                        cvt_s_w(0, 0);
                        sub_s(0, 1, 0);
                        swc1(0, sp, 120);
                        goto L_0044bb0c;
                    case 0x44B994u:  // [1]
                        charge(8);
                        lwc1(1, sp, 112);
                        mtc1(s1, 0);
                        cvt_s_w(0, 0);
                        sub_s(0, 1, 0);
                        swc1(0, sp, 112);
                        goto L_0044bb0c;
                    case 0x44B9B4u:  // [2]
                        charge(8);
                        lwc1(1, sp, 120);
                        mtc1(s1, 0);
                        cvt_s_w(0, 0);
                        add_s(0, 1, 0);
                        swc1(0, sp, 120);
                        goto L_0044bb0c;
                    case 0x44B9D4u:  // [3]
                        charge(8);
                        lwc1(1, sp, 112);
                        mtc1(s1, 0);
                        cvt_s_w(0, 0);
                        add_s(0, 1, 0);
                        swc1(0, sp, 112);
                        goto L_0044bb0c;
                    case 0x44B9F4u:  // [4]
                        charge(5);
                        v1 = dsll32(s1, 16);
                        v1 = dsra32(v1, 16);
                        v0 = sra(v1, 1);
                        if (ltz(v1)) {
                            charge(2);
                            v0 = addiu(v1, 1);
                            v0 = sra(v0, 1);
                        }
                        charge(11);
                        lwc1(2, sp, 120);
                        mtc1(v0, 0);
                        cvt_s_w(1, 0);
                        sub_s(0, 2, 1);
                        swc1(0, sp, 120);
                        lwc1(0, sp, 112);
                        add_s(0, 0, 1);
                        swc1(0, sp, 112);
                        goto L_0044bb0c;
                    case 0x44BA3Cu:  // [5]
                        charge(5);
                        v1 = dsll32(s1, 16);
                        v1 = dsra32(v1, 16);
                        v0 = sra(v1, 1);
                        if (ltz(v1)) {
                            charge(2);
                            v0 = addiu(v1, 1);
                            v0 = sra(v0, 1);
                        }
                        charge(11);
                        lwc1(2, sp, 120);
                        mtc1(v0, 0);
                        cvt_s_w(1, 0);
                        add_s(0, 2, 1);
                        swc1(0, sp, 120);
                        lwc1(0, sp, 112);
                        add_s(0, 0, 1);
                        swc1(0, sp, 112);
                        goto L_0044bb0c;
                    case 0x44BA84u:  // [6]
                        charge(5);
                        v1 = dsll32(s1, 16);
                        v1 = dsra32(v1, 16);
                        v0 = sra(v1, 1);
                        if (ltz(v1)) {
                            charge(2);
                            v0 = addiu(v1, 1);
                            v0 = sra(v0, 1);
                        }
                        charge(11);
                        lwc1(2, sp, 120);
                        mtc1(v0, 0);
                        cvt_s_w(1, 0);
                        sub_s(0, 2, 1);
                        swc1(0, sp, 120);
                        lwc1(0, sp, 112);
                        sub_s(0, 0, 1);
                        swc1(0, sp, 112);
                        goto L_0044bb0c;
                    case 0x44BACCu:  // [7]
                        charge(5);
                        v1 = dsll32(s1, 16);
                        v1 = dsra32(v1, 16);
                        v0 = sra(v1, 1);
                        if (gez(v1)) break;
                        charge(2);
                        v0 = addiu(v1, 1);
                        v0 = sra(v0, 1);
                    }
                    charge(9);
                    lwc1(2, sp, 120);
                    mtc1(v0, 0);
                    cvt_s_w(1, 0);
                    add_s(0, 2, 1);
                    swc1(0, sp, 120);
                    lwc1(0, sp, 112);
                    sub_s(0, 0, 1);
                    swc1(0, sp, 112);
                }
              L_0044bb0c:
                charge(25);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, v1);
                a1 = lw(s3, 32);
                a0 = lw(v0, 0);
                jal(0x44BB30u, &gen::fn_sub_1B0250_001b0250);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, v1);
                a0 = lw(v0, 0);
                a1 = addiu(sp, 112);
                lwc1(12, s3, 8);
                jal(0x44BB60u, &gen::fn_sub_1AFA20_001afa20);
                if (v0 == 0) break;
                charge(24);
                s1 = lw(s3, 24);
                jal(0x44BB74u, &gen::fn_sub_488F30_00488f30);
                v1 = lw(s3, 28);
                v1 = subu(v1, s1);
                divu(v0, v1);
                mfhi(v0);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, v1);
                a1 = addu(s1, a0);
                a0 = lw(v0, 0);
                jal(0x44BBB8u, &gen::fn_sub_1AFF70_001aff70);
                v1 = si(2);
                sb(s0, 4, v1);
                break;
            case 0x44BBD0u:  // [2]
                charge(7);
                jal(0x44BBD0u, &gen::fn_sub_44FFB0_0044ffb0);
                v1 = dsll32(v0, 24);
                v1 = dsra32(v1, 24);
                v0 = si(1);
                if (v1 == v0) {
                    charge(27);
                    v1 = lb(s0, 1);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, -4336);  // 0x86EF10
                    v0 = addu(v0, v1);
                    a0 = lw(v0, 0);
                    a1 = 0;
                    jal(0x44BC10u, &gen::fn_sub_1B0250_001b0250);
                    v1 = lb(s0, 1);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, -4336);  // 0x86EF10
                    v0 = addu(v0, v1);
                    a0 = lw(v0, 0);
                    jal(0x44BC38u, &gen::fn_sub_1B00C0_001b00c0);
                    v1 = lw(s3, 36);
                    sb(s0, 7, v1);
                    v1 = si(9);
                    sb(s0, 4, v1);
                    break;
                }
                charge(12);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, v1);
                a0 = lw(v0, 0);
                jal(0x44BC78u, &gen::fn_sub_1B0220_001b0220);
                if (v0 != 0) break;
                charge(4);
                v1 = si(1);
                sb(s0, 4, v1);
                break;
            case 0x44BC98u:  // [5]
                charge(29);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, v1);
                a0 = lw(v0, 0);
                a1 = 0;
                jal(0x44BCBCu, &gen::fn_sub_1B0250_001b0250);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                a0 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v1 = addu(v0, a0);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4344);  // 0x86EF08
                v0 = addu(v0, a0);
                v0 = lw(v0, 0);
                a0 = lw(v1, 0);
                a1 = addiu(v0, 256);
                lwc1(12, s3, 8);
                jal(0x44BCFCu, &gen::fn_sub_1AFA20_001afa20);
                if (v0 == 0) break;
                charge(2);
                v0 = si(6);
                sb(s0, 4, v0);
            case 0x44BD14u:  // [6]
                charge(12);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, v1);
                a0 = lw(v0, 0);
                jal(0x44BD34u, &gen::fn_sub_1B0220_001b0220);
                if (v0 != 0) break;
                charge(31);
                v0 = si(5);
                sb(s0, 4, v0);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4344);  // 0x86EF08
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(v0, 256);
                jal(0x44BD70u, &gen::fn_sub_44F120_0044f120);
                s1 = v0;
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 96);
                a1 = lw(v0, kResController);
                jal(0x44BDA4u, &gen::fn_sub_1AD940_001ad940);
                a0 = addiu(sp, 96);
                jal(0x44BDB0u, &gen::fn_sub_44F120_0044f120);
                if (s1 != v0) break;
                charge(29);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4344);  // 0x86EF08
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(v0, 256);
                jal(0x44BDE4u, &gen::fn_sub_44F170_0044f170);
                s1 = v0;
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 80);
                a1 = lw(v0, kResController);
                jal(0x44BE18u, &gen::fn_sub_1AD940_001ad940);
                a0 = addiu(sp, 80);
                jal(0x44BE24u, &gen::fn_sub_44F170_0044f170);
                if (s1 != v0) break;
                charge(11);
                a0 = lb(s0, 1);
                a1 = si(4);
                jal(0x44BE3Cu, &gen::fn_sub_4543C0_004543c0);
                a0 = lb(s0, 1);
                v1 = lui(0x96u);
                v1 = addiu(v1, -15856);  // 0x95C210
                v1 = addu(v1, a0);
                sb(v1, 0, zero);
                break;
            case 0x44BE60u:  // [9]
                charge(3);
                v1 = lb(s0, 7);
                if (lez(v1)) {
                    charge(6);
                    a0 = lb(s0, 1);
                    a1 = si(3);
                    jal(0x44BE74u, &gen::fn_sub_4543C0_004543c0);
                    break;
                }
                charge(2);
                v1 = addiu(v1, -1);
                sb(s0, 7, v1);
            case 0x44BE8Cu:  // [3], [4], [7], [8]
                break;
            }
        }
        charge(8);
        ra = ld(sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 128);
    }

    // 0x44D600 (think state 3 for behaviour kind 1; sub-state +3): 25 waits for the queue then wanders (state 4); 24 the
    // pursuit sub_454F50(ec, target); 0 starts: an EPL alert above the unit (sub_1A91B0 / sub_1A9390 on sField +4616), the
    // alert SFX (sub_10A4E0) when near the hero, +7 = record +36, the queue cleared -> 1; 1 counts +7 down -> 2; 2 measures
    // the distance to the target (sub_44F270 -> +68), and with a free target (sub_454520) a ground ray (K_FldFrame_Raycast
    // sub_1ACC30) decides: too high (> 50) -> wander, else walk there (sub_1AFA20), +8 = record +40 -> 3; without one -> 4;
    // 3 re-checks sight (sub_44F300), contact in front (sub_1C6450 -> state 5), else counts +8 / waits for the queue -> 2;
    // 4 keeps within 3 * record +20 of the target (sub_454400 / sub_44F1C0 / sub_454520 / sub_454620), else wanders; 5
    // steps aside (sub_1B0020) or sees contact; 7 and 8 do nothing.
    void sub_44D600() {
        enter(12);
        sp = addiu(sp, -352);
        sd(sp, 48, ra);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s1 = lw(a0, kTaskWork);
        v1 = lw(gp, -19040);
        s0 = addiu(v1, 64);
        a1 = lb(s1, 3);
        v1 = si(25);
        if (a1 != v1) {
            charge(3);
            v1 = si(24);
            if (a1 != v1) {
                charge(3);
                v1 = si(8);
                if (a1 != v1) {
                    charge(3);
                    v1 = si(7);
                    if (a1 != v1) {
                        charge(3);
                        v1 = si(5);
                        if (a1 != v1) {
                            charge(3);
                            v1 = si(4);
                            if (a1 != v1) {
                                charge(3);
                                v1 = si(3);
                                if (a1 != v1) {
                                    charge(3);
                                    a0 = si(2);
                                    if (a1 != a0) {
                                        charge(3);
                                        v1 = si(1);
                                        if (a1 != v1) {
                                            charge(2);
                                            if (a1 != 0) {
                                                charge(2);
                                            } else {
                                                charge(52);
                                                v1 = lb(s1, 1);
                                                v0 = sll(v1, 3);
                                                v0 = subu(v0, v1);
                                                v1 = sll(v0, 6);
                                                v0 = lui(0x87u);
                                                v0 = addiu(v0, -4620);  // 0x86EDF4
                                                v0 = addu(v0, v1);
                                                v0 = lw(v0, 0);
                                                a0 = addiu(sp, 304);
                                                a1 = lw(v0, kResController);
                                                jal(0x44D6C8u, &gen::fn_sub_1AD940_001ad940);
                                                lwc1(2, sp, 304);
                                                lwc1(1, sp, 308);
                                                lwc1(0, sp, 312);
                                                swc1(2, sp, 336);
                                                swc1(1, sp, 340);
                                                swc1(0, sp, 344);
                                                lwc1(1, sp, 340);
                                                v0 = lui(0x42C8u);
                                                mtc1(v0, 0);  // 100.0
                                                add_s(0, 1, 0);
                                                swc1(0, sp, 340);
                                                jal(0x44D700u, &gen::fn_K_Field_Get_001b9120);
                                                a0 = lw(v0, 4616);
                                                a1 = addiu(sp, 336);
                                                jal(0x44D710u, &gen::fn_sub_1A91B0_001a91b0);
                                                s2 = v0;
                                                jal(0x44D71Cu, &gen::fn_K_Field_Get_001b9120);
                                                a0 = lw(v0, 4616);
                                                a1 = s2;
                                                a2 = si(3);
                                                jal(0x44D730u, &gen::fn_sub_1A9390_001a9390);
                                                v1 = lb(s1, 1);
                                                v0 = sll(v1, 3);
                                                v0 = subu(v0, v1);
                                                v1 = sll(v0, 6);
                                                v0 = lui(0x87u);
                                                v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                                a0 = addu(v0, v1);
                                                v0 = lui(0x4516u);
                                                mtc1(v0, 12);  // 2400f
                                                jal(0x44D75Cu, &gen::fn_sub_1C7130_001c7130);
                                                a0 = si(1);
                                                if (v0 == a0) {
                                                    charge(5);
                                                    a1 = si(8);
                                                    a2 = si(3);
                                                    a3 = si(4);
                                                    jal(0x44D77Cu, &gen::fn_sub_10A4E0_0010a4e0);
                                                }
                                                charge(38);
                                                v0 = lw(s0, 36);
                                                sb(s1, 7, v0);
                                                v1 = lb(s1, 1);
                                                v0 = sll(v1, 3);
                                                v0 = subu(v0, v1);
                                                v1 = sll(v0, 6);
                                                v0 = lui(0x87u);
                                                v0 = addiu(v0, -4336);  // 0x86EF10
                                                v0 = addu(v0, v1);
                                                a0 = lw(v0, 0);
                                                a1 = 0;
                                                jal(0x44D7B0u, &gen::fn_sub_1B0250_001b0250);
                                                v1 = lb(s1, 1);
                                                v0 = sll(v1, 3);
                                                v0 = subu(v0, v1);
                                                v1 = sll(v0, 6);
                                                v0 = lui(0x87u);
                                                v0 = addiu(v0, -4336);  // 0x86EF10
                                                v0 = addu(v0, v1);
                                                a0 = lw(v0, 0);
                                                jal(0x44D7D8u, &gen::fn_sub_1B00C0_001b00c0);
                                                v1 = lb(s1, 1);
                                                v0 = sll(v1, 3);
                                                v0 = subu(v0, v1);
                                                v1 = sll(v0, 6);
                                                v0 = lui(0x87u);
                                                v0 = addiu(v0, -4336);  // 0x86EF10
                                                v0 = addu(v0, v1);
                                                a0 = lw(v0, 0);
                                                a1 = 0;
                                                jal(0x44D804u, &gen::fn_sub_1B0240_001b0240);
                                                v1 = si(1);
                                                sb(s1, 3, v1);
                                            }
                                        } else {
                                            charge(3);
                                            v1 = lb(s1, 7);
                                            if (lez(v1)) {
                                                charge(3);
                                                sb(s1, 3, a0);
                                            } else {
                                                charge(4);
                                                v1 = addiu(v1, -1);
                                                sb(s1, 7, v1);
                                            }
                                        }
                                    } else {
                                        charge(45);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4336);  // 0x86EF10
                                        v0 = addu(v0, v1);
                                        a0 = lw(v0, 0);
                                        jal(0x44D864u, &gen::fn_sub_1B00C0_001b00c0);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4620);  // 0x86EDF4
                                        v0 = addu(v0, v1);
                                        v0 = lw(v0, 0);
                                        a0 = addiu(sp, 288);
                                        a1 = lw(v0, kResController);
                                        jal(0x44D894u, &gen::fn_sub_1AD940_001ad940);
                                        v0 = lui(0x87u);
                                        v0 = lw(v0, 6132);  // 0x8717F4
                                        a0 = addiu(sp, 272);
                                        a1 = lw(v0, kResController);
                                        jal(0x44D8ACu, &gen::fn_sub_1AD940_001ad940);
                                        a0 = addiu(sp, 288);
                                        a1 = addiu(sp, 272);
                                        jal(0x44D8BCu, &gen::fn_sub_44F270_0044f270);
                                        swc1(0, s1, 68);
                                        v0 = lui(0x87u);
                                        v0 = lw(v0, 6132);  // 0x8717F4
                                        a0 = addiu(sp, 256);
                                        a1 = lw(v0, kResController);
                                        jal(0x44D8D8u, &gen::fn_sub_1AD940_001ad940);
                                        a0 = addiu(sp, 256);
                                        a1 = lb(s1, 1);
                                        jal(0x44D8E8u, &gen::fn_sub_454520_00454520);
                                        if (v0 == 0) {
                                            charge(4);
                                            v1 = si(4);
                                            sb(s1, 3, v1);
                                        } else {
                                            charge(39);
                                            v0 = lui(0x87u);
                                            v0 = lw(v0, 6132);  // 0x8717F4
                                            a0 = addiu(sp, 240);
                                            a1 = lw(v0, kResController);
                                            jal(0x44D918u, &gen::fn_sub_1AD940_001ad940);
                                            a1 = addiu(sp, 320);
                                            lwc1(2, sp, 240);
                                            lwc1(1, sp, 244);
                                            lwc1(0, sp, 248);
                                            swc1(2, sp, 320);
                                            swc1(1, sp, 324);
                                            swc1(0, sp, 328);
                                            lwc1(2, sp, 320);
                                            lwc1(1, sp, 324);
                                            lwc1(0, sp, 328);
                                            swc1(2, sp, 76);
                                            swc1(1, sp, 80);
                                            swc1(0, sp, 84);
                                            a0 = addiu(sp, 64);
                                            lwc1(2, sp, 76);
                                            lwc1(1, sp, 80);
                                            lwc1(0, sp, 84);
                                            swc1(2, sp, 64);
                                            swc1(1, sp, 68);
                                            swc1(0, sp, 72);
                                            v0 = lui(0x43C8u);
                                            sw(sp, 68, v0);
                                            v0 = lui(0xC3C8u);
                                            sw(sp, 80, v0);
                                            jal(0x44D980u, &gen::fn_sub_1ACC30_001acc30);
                                            lwc1(1, sp, 324);
                                            v0 = lui(0x4248u);
                                            mtc1(v0, 0);  // 50f
                                            c_le_s(1, 0);
                                            if (cond()) {
                                                charge(25);
                                                v1 = lb(s1, 1);
                                                v0 = sll(v1, 3);
                                                v0 = subu(v0, v1);
                                                v1 = sll(v0, 6);
                                                v0 = lui(0x87u);
                                                v0 = addiu(v0, -4336);  // 0x86EF10
                                                v0 = addu(v0, v1);
                                                a0 = lw(v0, 0);
                                                a1 = 0;
                                                jal(0x44D9C8u, &gen::fn_sub_1B0250_001b0250);
                                                v1 = lb(s1, 1);
                                                v0 = sll(v1, 3);
                                                v0 = subu(v0, v1);
                                                v1 = sll(v0, 6);
                                                v0 = lui(0x87u);
                                                v0 = addiu(v0, -4336);  // 0x86EF10
                                                v0 = addu(v0, v1);
                                                a0 = lw(v0, 0);
                                                a1 = addiu(sp, 320);
                                                lwc1(12, s0, 12);
                                                jal(0x44D9F8u, &gen::fn_sub_1AFA20_001afa20);
                                                if (v0 == 0) {
                                                    charge(7);
                                                    ra = ld(sp, 48);
                                                    lq(s2, sp, 32);
                                                    lq(s1, sp, 16);
                                                    lq(s0, sp, 0);
                                                    sp = addiu(sp, 352);
                                                    return;
                                                }
                                                charge(4);
                                                v1 = lw(s0, 40);
                                                sb(s1, 8, v1);
                                            } else {
                                                charge(11);
                                                a0 = lb(s1, 1);
                                                a1 = si(4);
                                                jal(0x44DA20u, &gen::fn_sub_4543C0_004543c0);
                                                a0 = lb(s1, 1);
                                                v1 = lui(0x96u);
                                                v1 = addiu(v1, -15856);  // 0x95C210
                                                v1 = addu(v1, a0);
                                                sb(v1, 0, zero);
                                                charge(7);
                                                ra = ld(sp, 48);
                                                lq(s2, sp, 32);
                                                lq(s1, sp, 16);
                                                lq(s0, sp, 0);
                                                sp = addiu(sp, 352);
                                                return;
                                            }
                                            charge(4);
                                            v1 = si(3);
                                            sb(s1, 3, v1);
                                        }
                                    }
                                } else {
                                    charge(8);
                                    a0 = lb(s1, 1);
                                    jal(0x44DA58u, &gen::fn_sub_44F300_0044f300);
                                    a0 = dsll32(v0, 24);
                                    a0 = dsra32(a0, 24);
                                    v1 = si(1);
                                    if (a0 != v1) {
                                        charge(27);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4620);  // 0x86EDF4
                                        v0 = addu(v0, v1);
                                        v0 = lw(v0, 0);
                                        a0 = lw(v0, 296);
                                        jal(0x44DA98u, &gen::fn_sub_318B60_00318b60);
                                        s2 = v0;
                                        v0 = lui(0x87u);
                                        v0 = lw(v0, 6132);  // 0x8717F4
                                        a0 = addiu(sp, 224);
                                        a1 = lw(v0, kResController);
                                        jal(0x44DAB4u, &gen::fn_sub_1AD940_001ad940);
                                        a0 = s2;
                                        a1 = addiu(sp, 224);
                                        lwc1(12, s0, 16);
                                        lwc1(13, s0, 4);
                                        jal(0x44DACCu, &gen::fn_sub_1C6450_001c6450);
                                        v1 = si(1);
                                        if (v0 == v1) {
                                            charge(6);
                                            a0 = lb(s1, 1);
                                            a1 = si(5);
                                            jal(0x44DAE8u, &gen::fn_sub_4543C0_004543c0);
                                        } else {
                                            charge(12);
                                            v1 = lb(s1, 1);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, -4336);  // 0x86EF10
                                            v0 = addu(v0, v1);
                                            a0 = lw(v0, 0);
                                            jal(0x44DB18u, &gen::fn_sub_1B0220_001b0220);
                                            if (v0 == 0) {
                                                charge(2);
                                                v1 = si(2);
                                                sb(s1, 3, v1);
                                            }
                                            charge(3);
                                            v1 = lb(s1, 8);
                                            if (lez(v1)) {
                                                charge(4);
                                                v1 = si(2);
                                                sb(s1, 3, v1);
                                            } else {
                                                charge(4);
                                                v1 = addiu(v1, -1);
                                                sb(s1, 8, v1);
                                            }
                                        }
                                    }
                                }
                            } else {
                                charge(12);
                                v0 = lui(0x87u);
                                v0 = lw(v0, 6132);  // 0x8717F4
                                a0 = addiu(sp, 208);
                                a1 = lw(v0, kResController);
                                jal(0x44DB6Cu, &gen::fn_sub_1AD940_001ad940);
                                a0 = addiu(sp, 208);
                                a1 = lb(s1, 1);
                                jal(0x44DB7Cu, &gen::fn_sub_454400_00454400);
                                if (v0 == 0) {
                                    charge(11);
                                    a0 = lb(s1, 1);
                                    a1 = si(4);
                                    jal(0x44DB94u, &gen::fn_sub_4543C0_004543c0);
                                    a0 = lb(s1, 1);
                                    v1 = lui(0x96u);
                                    v1 = addiu(v1, -15856);  // 0x95C210
                                    v1 = addu(v1, a0);
                                    sb(v1, 0, zero);
                                } else {
                                    charge(28);
                                    v1 = lb(s1, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4620);  // 0x86EDF4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = addiu(sp, 192);
                                    a1 = lw(v0, kResController);
                                    jal(0x44DBE0u, &gen::fn_sub_1AD940_001ad940);
                                    v0 = lui(0x87u);
                                    v0 = lw(v0, 6132);  // 0x8717F4
                                    a0 = addiu(sp, 176);
                                    a1 = lw(v0, kResController);
                                    jal(0x44DBF8u, &gen::fn_sub_1AD940_001ad940);
                                    v0 = lui(0x4040u);
                                    mtc1(v0, 1);  // 3.0
                                    lwc1(0, s0, 20);
                                    mul_s(12, 1, 0);
                                    a0 = addiu(sp, 192);
                                    a1 = addiu(sp, 176);
                                    jal(0x44DC18u, &gen::fn_sub_44F1C0_0044f1c0);
                                    if (v0 == 0) {
                                        charge(11);
                                        a0 = lb(s1, 1);
                                        a1 = si(4);
                                        jal(0x44DC30u, &gen::fn_sub_4543C0_004543c0);
                                        a0 = lb(s1, 1);
                                        v1 = lui(0x96u);
                                        v1 = addiu(v1, -15856);  // 0x95C210
                                        v1 = addu(v1, a0);
                                        sb(v1, 0, zero);
                                    } else {
                                        charge(13);
                                        v0 = lui(0x87u);
                                        v0 = lw(v0, 6132);  // 0x8717F4
                                        a0 = addiu(sp, 160);
                                        a1 = lw(v0, kResController);
                                        jal(0x44DC64u, &gen::fn_sub_1AD940_001ad940);
                                        a0 = addiu(sp, 160);
                                        a1 = lb(s1, 1);
                                        jal(0x44DC74u, &gen::fn_sub_454520_00454520);
                                        v1 = si(1);
                                        if (v0 == v1) {
                                            charge(14);
                                            v1 = lb(s1, 1);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, -4336);  // 0x86EF10
                                            v0 = addu(v0, v1);
                                            a0 = lw(v0, 0);
                                            jal(0x44DCA8u, &gen::fn_sub_1B00C0_001b00c0);
                                            v1 = si(2);
                                            sb(s1, 3, v1);
                                        } else {
                                            charge(27);
                                            v1 = lb(s1, 1);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, -4620);  // 0x86EDF4
                                            v0 = addu(v0, v1);
                                            v0 = lw(v0, 0);
                                            a0 = lw(v0, 296);
                                            jal(0x44DCE4u, &gen::fn_sub_318B60_00318b60);
                                            s2 = v0;
                                            v0 = lui(0x87u);
                                            v0 = lw(v0, 6132);  // 0x8717F4
                                            a0 = addiu(sp, 144);
                                            a1 = lw(v0, kResController);
                                            jal(0x44DD00u, &gen::fn_sub_1AD940_001ad940);
                                            a0 = s2;
                                            a1 = addiu(sp, 144);
                                            lwc1(12, s0, 16);
                                            lwc1(13, s0, 4);
                                            jal(0x44DD18u, &gen::fn_sub_1C6450_001c6450);
                                            v1 = si(1);
                                            if (v0 == v1) {
                                                charge(6);
                                                a0 = lb(s1, 1);
                                                a1 = si(5);
                                                jal(0x44DD34u, &gen::fn_sub_4543C0_004543c0);
                                            } else {
                                                charge(12);
                                                v1 = lb(s1, 1);
                                                v0 = sll(v1, 3);
                                                v0 = subu(v0, v1);
                                                v1 = sll(v0, 6);
                                                v0 = lui(0x87u);
                                                v0 = addiu(v0, -4336);  // 0x86EF10
                                                v0 = addu(v0, v1);
                                                a0 = lw(v0, 0);
                                                jal(0x44DD64u, &gen::fn_sub_1B0220_001b0220);
                                                if (v0 == 0) {
                                                    charge(7);
                                                    a0 = lb(s1, 1);
                                                    jal(0x44DD78u, &gen::fn_sub_454620_00454620);
                                                    v1 = si(5);
                                                    sb(s1, 3, v1);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            charge(13);
                            v0 = lui(0x87u);
                            v0 = lw(v0, 6132);  // 0x8717F4
                            a0 = addiu(sp, 128);
                            a1 = lw(v0, kResController);
                            jal(0x44DDA0u, &gen::fn_sub_1AD940_001ad940);
                            a0 = addiu(sp, 128);
                            a1 = lb(s1, 1);
                            jal(0x44DDB0u, &gen::fn_sub_454520_00454520);
                            v1 = si(1);
                            if (v0 == v1) {
                                charge(14);
                                v1 = lb(s1, 1);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, -4336);  // 0x86EF10
                                v0 = addu(v0, v1);
                                a0 = lw(v0, 0);
                                jal(0x44DDE4u, &gen::fn_sub_1B00C0_001b00c0);
                                v1 = si(2);
                                sb(s1, 3, v1);
                            } else {
                                charge(27);
                                v1 = lb(s1, 1);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, -4620);  // 0x86EDF4
                                v0 = addu(v0, v1);
                                v0 = lw(v0, 0);
                                a0 = lw(v0, 296);
                                jal(0x44DE20u, &gen::fn_sub_318B60_00318b60);
                                s2 = v0;
                                v0 = lui(0x87u);
                                v0 = lw(v0, 6132);  // 0x8717F4
                                a0 = addiu(sp, 112);
                                a1 = lw(v0, kResController);
                                jal(0x44DE3Cu, &gen::fn_sub_1AD940_001ad940);
                                a0 = s2;
                                a1 = addiu(sp, 112);
                                lwc1(12, s0, 16);
                                lwc1(13, s0, 4);
                                jal(0x44DE54u, &gen::fn_sub_1C6450_001c6450);
                                v1 = si(1);
                                if (v0 == v1) {
                                    charge(6);
                                    a0 = lb(s1, 1);
                                    a1 = si(5);
                                    jal(0x44DE70u, &gen::fn_sub_4543C0_004543c0);
                                } else {
                                    charge(12);
                                    v1 = lb(s1, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4336);  // 0x86EF10
                                    v0 = addu(v0, v1);
                                    a0 = lw(v0, 0);
                                    jal(0x44DEA0u, &gen::fn_sub_1B0220_001b0220);
                                    if (v0 == 0) {
                                        charge(32);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4336);  // 0x86EF10
                                        v0 = addu(v0, v1);
                                        a0 = lw(v0, 0);
                                        jal(0x44DED0u, &gen::fn_sub_1B00C0_001b00c0);
                                        v0 = lui(0x87u);
                                        v0 = lw(v0, 6132);  // 0x8717F4
                                        a0 = addiu(sp, 96);
                                        a1 = lw(v0, kResController);
                                        jal(0x44DEE8u, &gen::fn_sub_1AD940_001ad940);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4336);  // 0x86EF10
                                        v0 = addu(v0, v1);
                                        a0 = lw(v0, 0);
                                        a1 = addiu(sp, 96);
                                        a2 = si(5);
                                        jal(0x44DF18u, &gen::fn_sub_1B0020_001b0020);
                                        v1 = si(4);
                                        sb(s1, 3, v1);
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                charge(6);
                a0 = lb(s1, 1);
                a1 = lb(s1, 24);
                jal(0x44DF38u, &gen::fn_sub_454F50_00454f50);
            }
        } else {
            charge(12);
            v1 = lb(s1, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4336);  // 0x86EF10
            v0 = addu(v0, v1);
            a0 = lw(v0, 0);
            jal(0x44DF68u, &gen::fn_sub_1B0220_001b0220);
            if (v0 == 0) {
                charge(9);
                a0 = lb(s1, 1);
                a1 = si(4);
                jal(0x44DF80u, &gen::fn_sub_4543C0_004543c0);
                a0 = lb(s1, 1);
                v1 = lui(0x96u);
                v1 = addiu(v1, -15856);  // 0x95C210
                v1 = addu(v1, a0);
                sb(v1, 0, zero);
            }
        }
        charge(7);
        ra = ld(sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 352);
    }

    // 0x4501B0 (ec): sub-states 2..5 of sub_44D600 for any behaviour kind (its record gp-0x4A60 + 64 * unit +396), with
    // the distance computed inline (RwV3dLength sub_4C6AC0).
    void sub_4501B0() {
        enter(31);
        sp = addiu(sp, -432);
        sd(sp, 64, ra);
        sq(s2, sp, 48);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(20, sp, 0);
        a0 = dsll32(a0, 24);
        a0 = dsra32(a0, 24);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, -4340);  // 0x86EF0C
        v1 = addu(v1, a0);
        v1 = lw(v1, 0);
        s1 = lw(v1, kTaskWork);
        s2 = lb(s1, 1);
        v1 = sll(s2, 3);
        v1 = subu(v1, s2);
        a1 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, -4308);  // 0x86EF2C
        v1 = addu(v1, a1);
        v1 = lw(v1, 0);
        a0 = sll(v1, 6);
        v1 = lw(gp, -19040);
        s0 = addu(v1, a0);
        a0 = lb(s1, 3);
        v1 = si(5);
        if (a0 != v1) {
            charge(3);
            v1 = si(4);
            if (a0 != v1) {
                charge(3);
                v1 = si(3);
                if (a0 != v1) {
                    charge(3);
                    v1 = si(2);
                    if (a0 != v1) {
                        charge(2);
                    } else {
                        charge(78);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, -4336);  // 0x86EF10
                        v0 = addu(v0, a1);
                        a0 = lw(v0, 0);
                        jal(0x450268u, &gen::fn_sub_1B00C0_001b00c0);
                        v1 = lb(s1, 24);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, 6132);  // 0x8717F4
                        v0 = addu(v0, v1);
                        v0 = lw(v0, 0);
                        a0 = addiu(sp, 384);
                        a1 = lw(v0, kResController);
                        jal(0x450298u, &gen::fn_sub_1AD940_001ad940);
                        s2 = addiu(sp, 384);
                        v1 = lb(s1, 1);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, -4620);  // 0x86EDF4
                        v0 = addu(v0, v1);
                        v0 = lw(v0, 0);
                        a0 = addiu(sp, 400);
                        a1 = lw(v0, kResController);
                        jal(0x4502CCu, &gen::fn_sub_1AD940_001ad940);
                        v0 = addiu(sp, 400);
                        lwc1(2, v0, 0);
                        lwc1(1, v0, 4);
                        lwc1(0, v0, 8);
                        swc1(2, sp, 192);
                        swc1(1, sp, 196);
                        swc1(0, sp, 200);
                        lwc1(2, s2, 0);
                        lwc1(1, s2, 4);
                        lwc1(0, s2, 8);
                        swc1(2, sp, 176);
                        swc1(1, sp, 180);
                        swc1(0, sp, 184);
                        lwc1(1, sp, 192);
                        lwc1(0, sp, 176);
                        sub_s(0, 1, 0);
                        swc1(0, sp, 160);
                        lwc1(1, sp, 196);
                        lwc1(0, sp, 180);
                        sub_s(0, 1, 0);
                        swc1(0, sp, 164);
                        lwc1(1, sp, 200);
                        lwc1(0, sp, 184);
                        sub_s(0, 1, 0);
                        swc1(0, sp, 168);
                        a0 = addiu(sp, 160);
                        jal(0x45033Cu, &gen::fn_sub_4C6AC0_004c6ac0);
                        swc1(0, s1, 68);
                        v1 = lb(s1, 24);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, 6132);  // 0x8717F4
                        v0 = addu(v0, v1);
                        v0 = lw(v0, 0);
                        a0 = addiu(sp, 368);
                        a1 = lw(v0, kResController);
                        jal(0x450370u, &gen::fn_sub_1AD940_001ad940);
                        a0 = addiu(sp, 368);
                        a1 = lb(s1, 1);
                        jal(0x450380u, &gen::fn_sub_454520_00454520);
                        if (v0 == 0) {
                            charge(4);
                            v1 = si(4);
                            sb(s1, 3, v1);
                        } else {
                            charge(45);
                            v1 = lb(s1, 24);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, 6132);  // 0x8717F4
                            v0 = addu(v0, v1);
                            v0 = lw(v0, 0);
                            a0 = addiu(sp, 352);
                            a1 = lw(v0, kResController);
                            jal(0x4503C8u, &gen::fn_sub_1AD940_001ad940);
                            a1 = addiu(sp, 416);
                            lwc1(2, sp, 352);
                            lwc1(1, sp, 356);
                            lwc1(0, sp, 360);
                            swc1(2, sp, 416);
                            swc1(1, sp, 420);
                            swc1(0, sp, 424);
                            lwc1(2, sp, 416);
                            lwc1(1, sp, 420);
                            lwc1(0, sp, 424);
                            swc1(2, sp, 92);
                            swc1(1, sp, 96);
                            swc1(0, sp, 100);
                            a0 = addiu(sp, 80);
                            lwc1(2, sp, 92);
                            lwc1(1, sp, 96);
                            lwc1(0, sp, 100);
                            swc1(2, sp, 80);
                            swc1(1, sp, 84);
                            swc1(0, sp, 88);
                            v0 = lui(0x43C8u);
                            sw(sp, 84, v0);
                            v0 = lui(0xC3C8u);
                            sw(sp, 96, v0);
                            jal(0x450430u, &gen::fn_sub_1ACC30_001acc30);
                            lwc1(1, sp, 420);
                            v0 = lui(0x4248u);
                            mtc1(v0, 0);  // 50f
                            c_le_s(1, 0);
                            if (cond()) {
                                charge(25);
                                v1 = lb(s1, 1);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, -4336);  // 0x86EF10
                                v0 = addu(v0, v1);
                                a0 = lw(v0, 0);
                                a1 = 0;
                                jal(0x450478u, &gen::fn_sub_1B0250_001b0250);
                                v1 = lb(s1, 1);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, -4336);  // 0x86EF10
                                v0 = addu(v0, v1);
                                a0 = lw(v0, 0);
                                a1 = addiu(sp, 416);
                                lwc1(12, s0, 12);
                                jal(0x4504A8u, &gen::fn_sub_1AFA20_001afa20);
                                if (v0 == 0) {
                                    charge(8);
                                    ra = ld(sp, 64);
                                    lq(s2, sp, 48);
                                    lq(s1, sp, 32);
                                    lq(s0, sp, 16);
                                    lwc1(20, sp, 0);
                                    sp = addiu(sp, 432);
                                    return;
                                }
                                charge(4);
                                v1 = lw(s0, 40);
                                sb(s1, 8, v1);
                            } else {
                                charge(11);
                                a0 = lb(s1, 1);
                                a1 = si(4);
                                jal(0x4504D0u, &gen::fn_sub_4543C0_004543c0);
                                a0 = lb(s1, 1);
                                v1 = lui(0x96u);
                                v1 = addiu(v1, -15856);  // 0x95C210
                                v1 = addu(v1, a0);
                                sb(v1, 0, zero);
                                charge(8);
                                ra = ld(sp, 64);
                                lq(s2, sp, 48);
                                lq(s1, sp, 32);
                                lq(s0, sp, 16);
                                lwc1(20, sp, 0);
                                sp = addiu(sp, 432);
                                return;
                            }
                            charge(4);
                            v1 = si(3);
                            sb(s1, 3, v1);
                        }
                    }
                } else {
                    charge(8);
                    a0 = s2;
                    jal(0x450508u, &gen::fn_sub_44F300_0044f300);
                    a0 = dsll32(v0, 24);
                    a0 = dsra32(a0, 24);
                    v1 = si(1);
                    if (a0 != v1) {
                        charge(33);
                        v1 = lb(s1, 1);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, -4620);  // 0x86EDF4
                        v0 = addu(v0, v1);
                        v0 = lw(v0, 0);
                        a0 = lw(v0, 296);
                        jal(0x450548u, &gen::fn_sub_318B60_00318b60);
                        s2 = v0;
                        v1 = lb(s1, 24);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, 6132);  // 0x8717F4
                        v0 = addu(v0, v1);
                        v0 = lw(v0, 0);
                        a0 = addiu(sp, 336);
                        a1 = lw(v0, kResController);
                        jal(0x45057Cu, &gen::fn_sub_1AD940_001ad940);
                        a0 = s2;
                        a1 = addiu(sp, 336);
                        lwc1(12, s0, 16);
                        lwc1(13, s0, 4);
                        jal(0x450594u, &gen::fn_sub_1C6450_001c6450);
                        v1 = si(1);
                        if (v0 == v1) {
                            charge(6);
                            a0 = lb(s1, 1);
                            a1 = si(5);
                            jal(0x4505B0u, &gen::fn_sub_4543C0_004543c0);
                        } else {
                            charge(12);
                            v1 = lb(s1, 1);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -4336);  // 0x86EF10
                            v0 = addu(v0, v1);
                            a0 = lw(v0, 0);
                            jal(0x4505E0u, &gen::fn_sub_1B0220_001b0220);
                            if (v0 == 0) {
                                charge(2);
                                v1 = si(2);
                                sb(s1, 3, v1);
                            }
                            charge(3);
                            v1 = lb(s1, 8);
                            if (lez(v1)) {
                                charge(4);
                                v1 = si(2);
                                sb(s1, 3, v1);
                            } else {
                                charge(4);
                                v1 = addiu(v1, -1);
                                sb(s1, 8, v1);
                            }
                        }
                    }
                }
            } else {
                charge(18);
                v1 = lb(s1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6132);  // 0x8717F4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 320);
                a1 = lw(v0, kResController);
                jal(0x45064Cu, &gen::fn_sub_1AD940_001ad940);
                a0 = addiu(sp, 320);
                a1 = s2;
                jal(0x45065Cu, &gen::fn_sub_454400_00454400);
                if (v0 == 0) {
                    charge(11);
                    a0 = lb(s1, 1);
                    a1 = si(4);
                    jal(0x450674u, &gen::fn_sub_4543C0_004543c0);
                    a0 = lb(s1, 1);
                    v1 = lui(0x96u);
                    v1 = addiu(v1, -15856);  // 0x95C210
                    v1 = addu(v1, a0);
                    sb(v1, 0, zero);
                } else {
                    charge(61);
                    v0 = lui(0x4040u);
                    mtc1(v0, 1);  // 3.0
                    lwc1(0, s0, 20);
                    mul_s(20, 1, 0);
                    v1 = lb(s1, 24);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, 6132);  // 0x8717F4
                    v0 = addu(v0, v1);
                    v0 = lw(v0, 0);
                    a0 = addiu(sp, 288);
                    a1 = lw(v0, kResController);
                    jal(0x4506D0u, &gen::fn_sub_1AD940_001ad940);
                    s2 = addiu(sp, 288);
                    v1 = lb(s1, 1);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, -4620);  // 0x86EDF4
                    v0 = addu(v0, v1);
                    v0 = lw(v0, 0);
                    a0 = addiu(sp, 304);
                    a1 = lw(v0, kResController);
                    jal(0x450704u, &gen::fn_sub_1AD940_001ad940);
                    v0 = addiu(sp, 304);
                    lwc1(2, v0, 0);
                    lwc1(1, v0, 4);
                    lwc1(0, v0, 8);
                    swc1(2, sp, 144);
                    swc1(1, sp, 148);
                    swc1(0, sp, 152);
                    lwc1(2, s2, 0);
                    lwc1(1, s2, 4);
                    lwc1(0, s2, 8);
                    swc1(2, sp, 128);
                    swc1(1, sp, 132);
                    swc1(0, sp, 136);
                    s2 = 0;
                    lwc1(1, sp, 144);
                    lwc1(0, sp, 128);
                    sub_s(0, 1, 0);
                    swc1(0, sp, 112);
                    lwc1(1, sp, 148);
                    lwc1(0, sp, 132);
                    sub_s(0, 1, 0);
                    swc1(0, sp, 116);
                    lwc1(1, sp, 152);
                    lwc1(0, sp, 136);
                    sub_s(0, 1, 0);
                    swc1(0, sp, 120);
                    a0 = addiu(sp, 112);
                    jal(0x450778u, &gen::fn_sub_4C6AC0_004c6ac0);
                    c_lt_s(0, 20);
                    if (cond()) {
                        charge(1);
                        s2 = si(1);
                    }
                    charge(2);
                    if (s2 == 0) {
                        charge(11);
                        a0 = lb(s1, 1);
                        a1 = si(4);
                        jal(0x4507A0u, &gen::fn_sub_4543C0_004543c0);
                        a0 = lb(s1, 1);
                        v1 = lui(0x96u);
                        v1 = addiu(v1, -15856);  // 0x95C210
                        v1 = addu(v1, a0);
                        sb(v1, 0, zero);
                    } else {
                        charge(19);
                        v1 = lb(s1, 24);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, 6132);  // 0x8717F4
                        v0 = addu(v0, v1);
                        v0 = lw(v0, 0);
                        a0 = addiu(sp, 272);
                        a1 = lw(v0, kResController);
                        jal(0x4507ECu, &gen::fn_sub_1AD940_001ad940);
                        a0 = addiu(sp, 272);
                        a1 = lb(s1, 1);
                        jal(0x4507FCu, &gen::fn_sub_454520_00454520);
                        v1 = si(1);
                        if (v0 == v1) {
                            charge(14);
                            v1 = lb(s1, 1);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -4336);  // 0x86EF10
                            v0 = addu(v0, v1);
                            a0 = lw(v0, 0);
                            jal(0x450830u, &gen::fn_sub_1B00C0_001b00c0);
                            v1 = si(2);
                            sb(s1, 3, v1);
                        } else {
                            charge(33);
                            v1 = lb(s1, 1);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -4620);  // 0x86EDF4
                            v0 = addu(v0, v1);
                            v0 = lw(v0, 0);
                            a0 = lw(v0, 296);
                            jal(0x45086Cu, &gen::fn_sub_318B60_00318b60);
                            s2 = v0;
                            v1 = lb(s1, 24);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, 6132);  // 0x8717F4
                            v0 = addu(v0, v1);
                            v0 = lw(v0, 0);
                            a0 = addiu(sp, 256);
                            a1 = lw(v0, kResController);
                            jal(0x4508A0u, &gen::fn_sub_1AD940_001ad940);
                            a0 = s2;
                            a1 = addiu(sp, 256);
                            lwc1(12, s0, 16);
                            lwc1(13, s0, 4);
                            jal(0x4508B8u, &gen::fn_sub_1C6450_001c6450);
                            v1 = si(1);
                            if (v0 == v1) {
                                charge(6);
                                a0 = lb(s1, 1);
                                a1 = si(5);
                                jal(0x4508D4u, &gen::fn_sub_4543C0_004543c0);
                            } else {
                                charge(12);
                                v1 = lb(s1, 1);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, -4336);  // 0x86EF10
                                v0 = addu(v0, v1);
                                a0 = lw(v0, 0);
                                jal(0x450904u, &gen::fn_sub_1B0220_001b0220);
                                if (v0 == 0) {
                                    charge(7);
                                    a0 = lb(s1, 1);
                                    jal(0x450918u, &gen::fn_sub_454620_00454620);
                                    v1 = si(5);
                                    sb(s1, 3, v1);
                                }
                            }
                        }
                    }
                }
            }
        } else {
            charge(19);
            v1 = lb(s1, 24);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, 6132);  // 0x8717F4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 240);
            a1 = lw(v0, kResController);
            jal(0x450958u, &gen::fn_sub_1AD940_001ad940);
            a0 = addiu(sp, 240);
            a1 = s2;
            jal(0x450968u, &gen::fn_sub_454520_00454520);
            v1 = si(1);
            if (v0 == v1) {
                charge(14);
                v1 = lb(s1, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, v1);
                a0 = lw(v0, 0);
                jal(0x45099Cu, &gen::fn_sub_1B00C0_001b00c0);
                v1 = si(2);
                sb(s1, 3, v1);
            } else {
                charge(33);
                v1 = lb(s1, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = lw(v0, 296);
                jal(0x4509D8u, &gen::fn_sub_318B60_00318b60);
                s2 = v0;
                v1 = lb(s1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6132);  // 0x8717F4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 224);
                a1 = lw(v0, kResController);
                jal(0x450A0Cu, &gen::fn_sub_1AD940_001ad940);
                a0 = s2;
                a1 = addiu(sp, 224);
                lwc1(12, s0, 16);
                lwc1(13, s0, 4);
                jal(0x450A24u, &gen::fn_sub_1C6450_001c6450);
                v1 = si(1);
                if (v0 == v1) {
                    charge(6);
                    a0 = lb(s1, 1);
                    a1 = si(5);
                    jal(0x450A40u, &gen::fn_sub_4543C0_004543c0);
                } else {
                    charge(12);
                    v1 = lb(s1, 1);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, -4336);  // 0x86EF10
                    v0 = addu(v0, v1);
                    a0 = lw(v0, 0);
                    jal(0x450A70u, &gen::fn_sub_1B0220_001b0220);
                    if (v0 == 0) {
                        charge(36);
                        v1 = lb(s1, 1);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, -4336);  // 0x86EF10
                        v0 = addu(v0, v1);
                        a0 = lw(v0, 0);
                        jal(0x450AA0u, &gen::fn_sub_1B00C0_001b00c0);
                        v1 = lb(s1, 24);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, 6132);  // 0x8717F4
                        v0 = addu(v0, v1);
                        v0 = lw(v0, 0);
                        a0 = addiu(sp, 208);
                        a1 = lw(v0, kResController);
                        jal(0x450AD0u, &gen::fn_sub_1AD940_001ad940);
                        v1 = lb(s1, 1);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, -4336);  // 0x86EF10
                        v0 = addu(v0, v1);
                        a0 = lw(v0, 0);
                        a1 = addiu(sp, 208);
                        a2 = si(5);
                        jal(0x450B00u, &gen::fn_sub_1B0020_001b0020);
                        v1 = si(4);
                        sb(s1, 3, v1);
                    }
                }
            }
        }
        charge(8);
        ra = ld(sp, 64);
        lq(s2, sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(20, sp, 0);
        sp = addiu(sp, 432);
    }

    // 0x450B30 (ec): sub_4501B0 shifted to sub-states 7..10 (7 measure, 8 walk, 9 keep near, 10 step aside); a ground ray
    // higher than 50 goes to 9 instead of back to wandering.
    void sub_450B30() {
        enter(31);
        sp = addiu(sp, -432);
        sd(sp, 64, ra);
        sq(s2, sp, 48);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(20, sp, 0);
        a0 = dsll32(a0, 24);
        a0 = dsra32(a0, 24);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, -4340);  // 0x86EF0C
        v1 = addu(v1, a0);
        v1 = lw(v1, 0);
        s1 = lw(v1, kTaskWork);
        s2 = lb(s1, 1);
        v1 = sll(s2, 3);
        v1 = subu(v1, s2);
        a1 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, -4308);  // 0x86EF2C
        v1 = addu(v1, a1);
        v1 = lw(v1, 0);
        a0 = sll(v1, 6);
        v1 = lw(gp, -19040);
        s0 = addu(v1, a0);
        a0 = lb(s1, 3);
        v1 = si(10);
        if (a0 != v1) {
            charge(3);
            v1 = si(9);
            if (a0 != v1) {
                charge(3);
                v1 = si(8);
                if (a0 != v1) {
                    charge(3);
                    v1 = si(7);
                    if (a0 != v1) {
                        charge(2);
                    } else {
                        charge(78);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, -4336);  // 0x86EF10
                        v0 = addu(v0, a1);
                        a0 = lw(v0, 0);
                        jal(0x450BE8u, &gen::fn_sub_1B00C0_001b00c0);
                        v1 = lb(s1, 24);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, 6132);  // 0x8717F4
                        v0 = addu(v0, v1);
                        v0 = lw(v0, 0);
                        a0 = addiu(sp, 384);
                        a1 = lw(v0, kResController);
                        jal(0x450C18u, &gen::fn_sub_1AD940_001ad940);
                        s2 = addiu(sp, 384);
                        v1 = lb(s1, 1);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, -4620);  // 0x86EDF4
                        v0 = addu(v0, v1);
                        v0 = lw(v0, 0);
                        a0 = addiu(sp, 400);
                        a1 = lw(v0, kResController);
                        jal(0x450C4Cu, &gen::fn_sub_1AD940_001ad940);
                        v0 = addiu(sp, 400);
                        lwc1(2, v0, 0);
                        lwc1(1, v0, 4);
                        lwc1(0, v0, 8);
                        swc1(2, sp, 192);
                        swc1(1, sp, 196);
                        swc1(0, sp, 200);
                        lwc1(2, s2, 0);
                        lwc1(1, s2, 4);
                        lwc1(0, s2, 8);
                        swc1(2, sp, 176);
                        swc1(1, sp, 180);
                        swc1(0, sp, 184);
                        lwc1(1, sp, 192);
                        lwc1(0, sp, 176);
                        sub_s(0, 1, 0);
                        swc1(0, sp, 160);
                        lwc1(1, sp, 196);
                        lwc1(0, sp, 180);
                        sub_s(0, 1, 0);
                        swc1(0, sp, 164);
                        lwc1(1, sp, 200);
                        lwc1(0, sp, 184);
                        sub_s(0, 1, 0);
                        swc1(0, sp, 168);
                        a0 = addiu(sp, 160);
                        jal(0x450CBCu, &gen::fn_sub_4C6AC0_004c6ac0);
                        swc1(0, s1, 68);
                        v1 = lb(s1, 24);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, 6132);  // 0x8717F4
                        v0 = addu(v0, v1);
                        v0 = lw(v0, 0);
                        a0 = addiu(sp, 368);
                        a1 = lw(v0, kResController);
                        jal(0x450CF0u, &gen::fn_sub_1AD940_001ad940);
                        a0 = addiu(sp, 368);
                        a1 = lb(s1, 1);
                        jal(0x450D00u, &gen::fn_sub_454520_00454520);
                        if (v0 == 0) {
                            charge(4);
                            v1 = si(9);
                            sb(s1, 3, v1);
                        } else {
                            charge(45);
                            v1 = lb(s1, 24);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, 6132);  // 0x8717F4
                            v0 = addu(v0, v1);
                            v0 = lw(v0, 0);
                            a0 = addiu(sp, 352);
                            a1 = lw(v0, kResController);
                            jal(0x450D48u, &gen::fn_sub_1AD940_001ad940);
                            a1 = addiu(sp, 416);
                            lwc1(2, sp, 352);
                            lwc1(1, sp, 356);
                            lwc1(0, sp, 360);
                            swc1(2, sp, 416);
                            swc1(1, sp, 420);
                            swc1(0, sp, 424);
                            lwc1(2, sp, 416);
                            lwc1(1, sp, 420);
                            lwc1(0, sp, 424);
                            swc1(2, sp, 92);
                            swc1(1, sp, 96);
                            swc1(0, sp, 100);
                            a0 = addiu(sp, 80);
                            lwc1(2, sp, 92);
                            lwc1(1, sp, 96);
                            lwc1(0, sp, 100);
                            swc1(2, sp, 80);
                            swc1(1, sp, 84);
                            swc1(0, sp, 88);
                            v0 = lui(0x43C8u);
                            sw(sp, 84, v0);
                            v0 = lui(0xC3C8u);
                            sw(sp, 96, v0);
                            jal(0x450DB0u, &gen::fn_sub_1ACC30_001acc30);
                            lwc1(1, sp, 420);
                            v1 = lui(0x4248u);
                            mtc1(v1, 0);  // 50f
                            c_le_s(1, 0);
                            if (cond()) {
                                charge(25);
                                v1 = lb(s1, 1);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, -4336);  // 0x86EF10
                                v0 = addu(v0, v1);
                                a0 = lw(v0, 0);
                                a1 = 0;
                                jal(0x450DF8u, &gen::fn_sub_1B0250_001b0250);
                                v1 = lb(s1, 1);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, -4336);  // 0x86EF10
                                v0 = addu(v0, v1);
                                a0 = lw(v0, 0);
                                a1 = addiu(sp, 416);
                                lwc1(12, s0, 12);
                                jal(0x450E28u, &gen::fn_sub_1AFA20_001afa20);
                                if (v0 == 0) {
                                    charge(8);
                                    ra = ld(sp, 64);
                                    lq(s2, sp, 48);
                                    lq(s1, sp, 32);
                                    lq(s0, sp, 16);
                                    lwc1(20, sp, 0);
                                    sp = addiu(sp, 432);
                                    return;
                                }
                                charge(4);
                                v1 = lw(s0, 40);
                                sb(s1, 8, v1);
                            } else {
                                charge(4);
                                v1 = si(9);
                                sb(s1, 3, v1);
                                charge(8);
                                ra = ld(sp, 64);
                                lq(s2, sp, 48);
                                lq(s1, sp, 32);
                                lq(s0, sp, 16);
                                lwc1(20, sp, 0);
                                sp = addiu(sp, 432);
                                return;
                            }
                            charge(4);
                            v1 = si(8);
                            sb(s1, 3, v1);
                        }
                    }
                } else {
                    charge(8);
                    a0 = s2;
                    jal(0x450E6Cu, &gen::fn_sub_44F300_0044f300);
                    a0 = dsll32(v0, 24);
                    a0 = dsra32(a0, 24);
                    v1 = si(1);
                    if (a0 != v1) {
                        charge(33);
                        v1 = lb(s1, 1);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, -4620);  // 0x86EDF4
                        v0 = addu(v0, v1);
                        v0 = lw(v0, 0);
                        a0 = lw(v0, 296);
                        jal(0x450EACu, &gen::fn_sub_318B60_00318b60);
                        s2 = v0;
                        v1 = lb(s1, 24);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, 6132);  // 0x8717F4
                        v0 = addu(v0, v1);
                        v0 = lw(v0, 0);
                        a0 = addiu(sp, 336);
                        a1 = lw(v0, kResController);
                        jal(0x450EE0u, &gen::fn_sub_1AD940_001ad940);
                        a0 = s2;
                        a1 = addiu(sp, 336);
                        lwc1(12, s0, 16);
                        lwc1(13, s0, 4);
                        jal(0x450EF8u, &gen::fn_sub_1C6450_001c6450);
                        v1 = si(1);
                        if (v0 == v1) {
                            charge(6);
                            a0 = lb(s1, 1);
                            a1 = si(5);
                            jal(0x450F14u, &gen::fn_sub_4543C0_004543c0);
                        } else {
                            charge(12);
                            v1 = lb(s1, 1);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -4336);  // 0x86EF10
                            v0 = addu(v0, v1);
                            a0 = lw(v0, 0);
                            jal(0x450F44u, &gen::fn_sub_1B0220_001b0220);
                            if (v0 == 0) {
                                charge(2);
                                v1 = si(7);
                                sb(s1, 3, v1);
                            }
                            charge(3);
                            v1 = lb(s1, 8);
                            if (lez(v1)) {
                                charge(4);
                                v1 = si(7);
                                sb(s1, 3, v1);
                            } else {
                                charge(4);
                                v1 = addiu(v1, -1);
                                sb(s1, 8, v1);
                            }
                        }
                    }
                }
            } else {
                charge(18);
                v1 = lb(s1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6132);  // 0x8717F4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 320);
                a1 = lw(v0, kResController);
                jal(0x450FB0u, &gen::fn_sub_1AD940_001ad940);
                a0 = addiu(sp, 320);
                a1 = s2;
                jal(0x450FC0u, &gen::fn_sub_454400_00454400);
                if (v0 == 0) {
                    charge(11);
                    a0 = lb(s1, 1);
                    a1 = si(4);
                    jal(0x450FD8u, &gen::fn_sub_4543C0_004543c0);
                    a0 = lb(s1, 1);
                    v1 = lui(0x96u);
                    v1 = addiu(v1, -15856);  // 0x95C210
                    v1 = addu(v1, a0);
                    sb(v1, 0, zero);
                } else {
                    charge(61);
                    v0 = lui(0x4040u);
                    mtc1(v0, 1);  // 3.0
                    lwc1(0, s0, 20);
                    mul_s(20, 1, 0);
                    v1 = lb(s1, 24);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, 6132);  // 0x8717F4
                    v0 = addu(v0, v1);
                    v0 = lw(v0, 0);
                    a0 = addiu(sp, 288);
                    a1 = lw(v0, kResController);
                    jal(0x451034u, &gen::fn_sub_1AD940_001ad940);
                    s2 = addiu(sp, 288);
                    v1 = lb(s1, 1);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, -4620);  // 0x86EDF4
                    v0 = addu(v0, v1);
                    v0 = lw(v0, 0);
                    a0 = addiu(sp, 304);
                    a1 = lw(v0, kResController);
                    jal(0x451068u, &gen::fn_sub_1AD940_001ad940);
                    v0 = addiu(sp, 304);
                    lwc1(2, v0, 0);
                    lwc1(1, v0, 4);
                    lwc1(0, v0, 8);
                    swc1(2, sp, 144);
                    swc1(1, sp, 148);
                    swc1(0, sp, 152);
                    lwc1(2, s2, 0);
                    lwc1(1, s2, 4);
                    lwc1(0, s2, 8);
                    swc1(2, sp, 128);
                    swc1(1, sp, 132);
                    swc1(0, sp, 136);
                    s2 = 0;
                    lwc1(1, sp, 144);
                    lwc1(0, sp, 128);
                    sub_s(0, 1, 0);
                    swc1(0, sp, 112);
                    lwc1(1, sp, 148);
                    lwc1(0, sp, 132);
                    sub_s(0, 1, 0);
                    swc1(0, sp, 116);
                    lwc1(1, sp, 152);
                    lwc1(0, sp, 136);
                    sub_s(0, 1, 0);
                    swc1(0, sp, 120);
                    a0 = addiu(sp, 112);
                    jal(0x4510DCu, &gen::fn_sub_4C6AC0_004c6ac0);
                    c_lt_s(0, 20);
                    if (cond()) {
                        charge(1);
                        s2 = si(1);
                    }
                    charge(2);
                    if (s2 == 0) {
                        charge(11);
                        a0 = lb(s1, 1);
                        a1 = si(4);
                        jal(0x451104u, &gen::fn_sub_4543C0_004543c0);
                        a0 = lb(s1, 1);
                        v1 = lui(0x96u);
                        v1 = addiu(v1, -15856);  // 0x95C210
                        v1 = addu(v1, a0);
                        sb(v1, 0, zero);
                    } else {
                        charge(19);
                        v1 = lb(s1, 24);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, 6132);  // 0x8717F4
                        v0 = addu(v0, v1);
                        v0 = lw(v0, 0);
                        a0 = addiu(sp, 272);
                        a1 = lw(v0, kResController);
                        jal(0x451150u, &gen::fn_sub_1AD940_001ad940);
                        a0 = addiu(sp, 272);
                        a1 = lb(s1, 1);
                        jal(0x451160u, &gen::fn_sub_454520_00454520);
                        v1 = si(1);
                        if (v0 == v1) {
                            charge(14);
                            v1 = lb(s1, 1);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -4336);  // 0x86EF10
                            v0 = addu(v0, v1);
                            a0 = lw(v0, 0);
                            jal(0x451194u, &gen::fn_sub_1B00C0_001b00c0);
                            v1 = si(7);
                            sb(s1, 3, v1);
                        } else {
                            charge(33);
                            v1 = lb(s1, 1);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -4620);  // 0x86EDF4
                            v0 = addu(v0, v1);
                            v0 = lw(v0, 0);
                            a0 = lw(v0, 296);
                            jal(0x4511D0u, &gen::fn_sub_318B60_00318b60);
                            s2 = v0;
                            v1 = lb(s1, 24);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, 6132);  // 0x8717F4
                            v0 = addu(v0, v1);
                            v0 = lw(v0, 0);
                            a0 = addiu(sp, 256);
                            a1 = lw(v0, kResController);
                            jal(0x451204u, &gen::fn_sub_1AD940_001ad940);
                            a0 = s2;
                            a1 = addiu(sp, 256);
                            lwc1(12, s0, 16);
                            lwc1(13, s0, 4);
                            jal(0x45121Cu, &gen::fn_sub_1C6450_001c6450);
                            v1 = si(1);
                            if (v0 == v1) {
                                charge(6);
                                a0 = lb(s1, 1);
                                a1 = si(5);
                                jal(0x451238u, &gen::fn_sub_4543C0_004543c0);
                            } else {
                                charge(12);
                                v1 = lb(s1, 1);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, -4336);  // 0x86EF10
                                v0 = addu(v0, v1);
                                a0 = lw(v0, 0);
                                jal(0x451268u, &gen::fn_sub_1B0220_001b0220);
                                if (v0 == 0) {
                                    charge(7);
                                    a0 = lb(s1, 1);
                                    jal(0x45127Cu, &gen::fn_sub_454620_00454620);
                                    v1 = si(10);
                                    sb(s1, 3, v1);
                                }
                            }
                        }
                    }
                }
            }
        } else {
            charge(19);
            v1 = lb(s1, 24);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, 6132);  // 0x8717F4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 240);
            a1 = lw(v0, kResController);
            jal(0x4512BCu, &gen::fn_sub_1AD940_001ad940);
            a0 = addiu(sp, 240);
            a1 = s2;
            jal(0x4512CCu, &gen::fn_sub_454520_00454520);
            v1 = si(1);
            if (v0 == v1) {
                charge(14);
                v1 = lb(s1, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, v1);
                a0 = lw(v0, 0);
                jal(0x451300u, &gen::fn_sub_1B00C0_001b00c0);
                v1 = si(7);
                sb(s1, 3, v1);
            } else {
                charge(33);
                v1 = lb(s1, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = lw(v0, 296);
                jal(0x45133Cu, &gen::fn_sub_318B60_00318b60);
                s2 = v0;
                v1 = lb(s1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6132);  // 0x8717F4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 224);
                a1 = lw(v0, kResController);
                jal(0x451370u, &gen::fn_sub_1AD940_001ad940);
                a0 = s2;
                a1 = addiu(sp, 224);
                lwc1(12, s0, 16);
                lwc1(13, s0, 4);
                jal(0x451388u, &gen::fn_sub_1C6450_001c6450);
                v1 = si(1);
                if (v0 == v1) {
                    charge(6);
                    a0 = lb(s1, 1);
                    a1 = si(5);
                    jal(0x4513A4u, &gen::fn_sub_4543C0_004543c0);
                } else {
                    charge(12);
                    v1 = lb(s1, 1);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, -4336);  // 0x86EF10
                    v0 = addu(v0, v1);
                    a0 = lw(v0, 0);
                    jal(0x4513D4u, &gen::fn_sub_1B0220_001b0220);
                    if (v0 == 0) {
                        charge(36);
                        v1 = lb(s1, 1);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, -4336);  // 0x86EF10
                        v0 = addu(v0, v1);
                        a0 = lw(v0, 0);
                        jal(0x451404u, &gen::fn_sub_1B00C0_001b00c0);
                        v1 = lb(s1, 24);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, 6132);  // 0x8717F4
                        v0 = addu(v0, v1);
                        v0 = lw(v0, 0);
                        a0 = addiu(sp, 208);
                        a1 = lw(v0, kResController);
                        jal(0x451434u, &gen::fn_sub_1AD940_001ad940);
                        v1 = lb(s1, 1);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, -4336);  // 0x86EF10
                        v0 = addu(v0, v1);
                        a0 = lw(v0, 0);
                        a1 = addiu(sp, 208);
                        a2 = si(5);
                        jal(0x451464u, &gen::fn_sub_1B0020_001b0020);
                        v1 = si(9);
                        sb(s1, 3, v1);
                    }
                }
            }
        }
        charge(8);
        ra = ld(sp, 64);
        lq(s2, sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(20, sp, 0);
        sp = addiu(sp, 432);
    }

    // 0x44AF60 (think state 4 for the other behaviours; sub-state +4 by a jump table at 0x7BC570): 0 records the start cell
    // (+92 / +93 from the controller) and position (+80 / +96 / +108 = the model position) -> 1; 1 picks a wander
    // direction (sub_44E560 -> +138) and looks for the party (sub_44FAB0); 2 turns it into the target +108 / +116 (the
    // distance +146, halved on the diagonals; a jump table at 0x7BC550) -> 3; 3 walks there (speed record +32, sub_1AFA20)
    // -> 4, which pauses record +24 .. +28 frames (sub_1AFF70) and goes back to 1; 5 plans the way home (sub_453ED0 from the
    // controller's cell to the model's; the 0x95C210 byte = 2) -> 6; 6 pops the next path cell (+148 counts down, cells at
    // +3224 + 4 i) and its door (sub_1BF220) -> 7, or -> 8 when done; 7 walks there -> 6; 8 waits for the queue, then state 4.
    void sub_44AF60() {
        enter(24);
        sp = addiu(sp, -144);
        sd(sp, 80, ra);
        sq(s4, sp, 64);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s3 = a0;
        s1 = lw(a0, kTaskWork);
        a1 = lb(s1, 1);
        v1 = sll(a1, 3);
        v1 = subu(v1, a1);
        s0 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, -4308);  // 0x86EF2C
        v1 = addu(v1, s0);
        v1 = lw(v1, 0);
        a1 = sll(v1, 6);
        v1 = lw(gp, -19040);
        s2 = addu(v1, a1);
        v1 = lb(s1, 4);
        at = sltiu(v1, 9);
        if (at != 0) {
            charge(7);
            a1 = lui(0x7Cu);
            a1 = addiu(a1, -14992);  // 0x7BC570
            v1 = sll(v1, 2);
            v1 = addu(v1, a1);
            v1 = lw(v1, 0);
            switch (w(v1)) {  // jump table 0x7BC570
            default:
                dispatch(v1);
                return;
            case 0x44AFDCu:  // [0]
                charge(57);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, s0);
                v0 = lw(v0, 0);
                a0 = lw(v0, kResController);
                jal(0x44AFF0u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                sb(s1, 92, v0);
                v1 = lb(s1, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = lw(v0, kResController);
                jal(0x44B020u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                sb(s1, 93, v0);
                v1 = lb(s1, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 128);
                a1 = lw(v0, kResController);
                jal(0x44B054u, &gen::fn_sub_1AD940_001ad940);
                lwc1(2, sp, 128);
                lwc1(1, sp, 132);
                lwc1(0, sp, 136);
                swc1(2, s1, 80);
                swc1(1, s1, 84);
                swc1(0, s1, 88);
                lwc1(2, s1, 80);
                lwc1(1, s1, 84);
                lwc1(0, s1, 88);
                swc1(2, s1, 96);
                swc1(1, s1, 100);
                swc1(0, s1, 104);
                lwc1(2, s1, 96);
                lwc1(1, s1, 100);
                lwc1(0, s1, 104);
                swc1(2, s1, 108);
                swc1(1, s1, 112);
                swc1(0, s1, 116);
                v1 = lb(s1, 1);
                v0 = lui(0x96u);
                v0 = addiu(v0, -15856);  // 0x95C210
                v0 = addu(v0, v1);
                sb(v0, 0, zero);
                v0 = si(1);
                sb(s1, 4, v0);
            case 0x44B0C0u:  // [1]
                charge(9);
                a0 = s3;
                jal(0x44B0C4u, &gen::fn_sub_44E560_0044e560);
                sb(s1, 138, v0);
                a0 = s3;
                jal(0x44B0D4u, &gen::fn_sub_44FAB0_0044fab0);
                break;
            case 0x44B0E4u:  // [2]
                charge(4);
                v0 = lb(s1, 138);
                at = sltiu(v0, 8);
                if (at != 0) {
                    charge(7);
                    v1 = lui(0x7Cu);
                    v1 = addiu(v1, -15024);  // 0x7BC550
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    v0 = lw(v0, 0);
                    switch (w(v0)) {  // jump table 0x7BC550
                    default:
                        dispatch(v0);
                        return;
                    case 0x44B110u:  // [0]
                        charge(6);
                        lwc1(0, s1, 96);
                        swc1(0, s1, 108);
                        lwc1(1, s1, 104);
                        v0 = lhu(s1, 146);
                        if (gez(v0)) {
                            charge(5);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                        } else {
                            charge(7);
                            v1 = srl(v0, 1);
                            v0 = v0 & 0x1u;
                            v1 = v1 | v0;
                            mtc1(v1, 0);
                            cvt_s_w(0, 0);
                            add_s(0, 0, 0);
                        }
                        charge(4);
                        sub_s(0, 1, 0);
                        swc1(0, s1, 116);
                        break;
                    case 0x44B168u:  // [1]
                        charge(6);
                        lwc1(0, s1, 104);
                        swc1(0, s1, 116);
                        lwc1(1, s1, 96);
                        v0 = lhu(s1, 146);
                        if (gez(v0)) {
                            charge(5);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                        } else {
                            charge(7);
                            v1 = srl(v0, 1);
                            v0 = v0 & 0x1u;
                            v1 = v1 | v0;
                            mtc1(v1, 0);
                            cvt_s_w(0, 0);
                            add_s(0, 0, 0);
                        }
                        charge(4);
                        sub_s(0, 1, 0);
                        swc1(0, s1, 108);
                        break;
                    case 0x44B1C0u:  // [2]
                        charge(6);
                        lwc1(0, s1, 96);
                        swc1(0, s1, 108);
                        lwc1(1, s1, 104);
                        v0 = lhu(s1, 146);
                        if (gez(v0)) {
                            charge(5);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                        } else {
                            charge(7);
                            v1 = srl(v0, 1);
                            v0 = v0 & 0x1u;
                            v1 = v1 | v0;
                            mtc1(v1, 0);
                            cvt_s_w(0, 0);
                            add_s(0, 0, 0);
                        }
                        charge(4);
                        add_s(0, 1, 0);
                        swc1(0, s1, 116);
                        break;
                    case 0x44B218u:  // [3]
                        charge(6);
                        lwc1(0, s1, 104);
                        swc1(0, s1, 116);
                        lwc1(1, s1, 96);
                        v0 = lhu(s1, 146);
                        if (gez(v0)) {
                            charge(5);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                        } else {
                            charge(7);
                            v1 = srl(v0, 1);
                            v0 = v0 & 0x1u;
                            v1 = v1 | v0;
                            mtc1(v1, 0);
                            cvt_s_w(0, 0);
                            add_s(0, 0, 0);
                        }
                        charge(4);
                        add_s(0, 1, 0);
                        swc1(0, s1, 108);
                        break;
                    case 0x44B270u:  // [4]
                        charge(18);
                        v0 = lhu(s1, 146);
                        v0 = srl(v0, 1);
                        mtc1(v0, 0);
                        cvt_s_w(1, 0);
                        lwc1(0, s1, 96);
                        add_s(0, 0, 1);
                        swc1(0, s1, 108);
                        v0 = lhu(s1, 146);
                        v0 = srl(v0, 1);
                        mtc1(v0, 0);
                        cvt_s_w(1, 0);
                        lwc1(0, s1, 104);
                        sub_s(0, 0, 1);
                        swc1(0, s1, 116);
                        break;
                    case 0x44B2B8u:  // [5]
                        charge(18);
                        v0 = lhu(s1, 146);
                        v0 = srl(v0, 1);
                        mtc1(v0, 0);
                        cvt_s_w(1, 0);
                        lwc1(0, s1, 96);
                        add_s(0, 0, 1);
                        swc1(0, s1, 108);
                        v0 = lhu(s1, 146);
                        v0 = srl(v0, 1);
                        mtc1(v0, 0);
                        cvt_s_w(1, 0);
                        lwc1(0, s1, 104);
                        add_s(0, 0, 1);
                        swc1(0, s1, 116);
                        break;
                    case 0x44B300u:  // [6]
                        charge(18);
                        v0 = lhu(s1, 146);
                        v0 = srl(v0, 1);
                        mtc1(v0, 0);
                        cvt_s_w(1, 0);
                        lwc1(0, s1, 96);
                        sub_s(0, 0, 1);
                        swc1(0, s1, 108);
                        v0 = lhu(s1, 146);
                        v0 = srl(v0, 1);
                        mtc1(v0, 0);
                        cvt_s_w(1, 0);
                        lwc1(0, s1, 104);
                        sub_s(0, 0, 1);
                        swc1(0, s1, 116);
                        break;
                    case 0x44B348u:  // [7]
                        charge(16);
                        v0 = lhu(s1, 146);
                        v0 = srl(v0, 1);
                        mtc1(v0, 0);
                        cvt_s_w(1, 0);
                        lwc1(0, s1, 96);
                        sub_s(0, 0, 1);
                        swc1(0, s1, 108);
                        v0 = lhu(s1, 146);
                        v0 = srl(v0, 1);
                        mtc1(v0, 0);
                        cvt_s_w(1, 0);
                        lwc1(0, s1, 104);
                        add_s(0, 0, 1);
                        swc1(0, s1, 116);
                    }
                }
                charge(7);
                v0 = si(3);
                sb(s1, 4, v0);
                a0 = s3;
                jal(0x44B394u, &gen::fn_sub_44FAB0_0044fab0);
                break;
            case 0x44B3A4u:  // [3]
                charge(7);
                jal(0x44B3A4u, &gen::fn_sub_44FAB0_0044fab0);
                a0 = dsll32(v0, 24);
                a0 = dsra32(a0, 24);
                v1 = si(1);
                if (a0 == v1) break;
                charge(25);
                v1 = lb(s1, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, v1);
                a1 = lw(s2, 32);
                a0 = lw(v0, 0);
                jal(0x44B3E4u, &gen::fn_sub_1B0250_001b0250);
                v1 = lb(s1, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, v1);
                a0 = lw(v0, 0);
                a1 = addiu(s1, 108);
                lwc1(12, s2, 8);
                jal(0x44B414u, &gen::fn_sub_1AFA20_001afa20);
                if (v0 == 0) break;
                charge(8);
                lwc1(2, s1, 108);
                lwc1(1, s1, 112);
                lwc1(0, s1, 116);
                swc1(2, s1, 96);
                swc1(1, s1, 100);
                swc1(0, s1, 104);
                v0 = si(4);
                sb(s1, 4, v0);
            case 0x44B444u:  // [4]
                charge(8);
                a0 = s3;
                jal(0x44B448u, &gen::fn_sub_44FAB0_0044fab0);
                a0 = dsll32(v0, 24);
                a0 = dsra32(a0, 24);
                v1 = si(1);
                if (a0 == v1) break;
                charge(22);
                s0 = lw(s2, 24);
                jal(0x44B468u, &gen::fn_sub_488F30_00488f30);
                v1 = lw(s2, 28);
                v1 = subu(v1, s0);
                divu(v0, v1);
                mfhi(v0);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                v1 = lb(s1, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, v1);
                a1 = addu(s0, a0);
                a0 = lw(v0, 0);
                jal(0x44B4ACu, &gen::fn_sub_1AFF70_001aff70);
                if (v0 == 0) break;
                charge(4);
                v1 = si(1);
                sb(s1, 4, v1);
                break;
            case 0x44B4CCu:  // [5]
                charge(66);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, s0);
                v0 = lw(v0, 0);
                a0 = lw(v0, kResController);
                jal(0x44B4E0u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                s4 = dsll32(v0, 24);
                s4 = dsra32(s4, 24);
                v1 = lb(s1, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = lw(v0, kResController);
                jal(0x44B514u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                s3 = dsll32(v0, 24);
                s3 = dsra32(s3, 24);
                v1 = lb(s1, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 112);
                a1 = lw(v0, kResController);
                jal(0x44B54Cu, &gen::fn_sub_1AD940_001ad940);
                v1 = lb(s1, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4344);  // 0x86EF08
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(v0, 256);
                jal(0x44B578u, &gen::fn_sub_44F120_0044f120);
                s2 = dsll32(v0, 24);
                s2 = dsra32(s2, 24);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4344);  // 0x86EF08
                v0 = addu(v0, s0);
                v0 = lw(v0, 0);
                a0 = addiu(v0, 256);
                jal(0x44B59Cu, &gen::fn_sub_44F170_0044f170);
                a5 = dsll32(v0, 24);
                a5 = dsra32(a5, 24);
                a0 = lb(s1, 1);
                a1 = s4;
                a2 = s3;
                a3 = addiu(sp, 112);
                a4 = s2;
                jal(0x44B5C0u, &gen::fn_sub_453ED0_00453ed0);
                v1 = si(1);
                if (v0 == v1) {
                    charge(2);
                    v1 = si(6);
                    sb(s1, 4, v1);
                }
                charge(8);
                a1 = si(2);
                a0 = lb(s1, 1);
                v1 = lui(0x96u);
                v1 = addiu(v1, -15856);  // 0x95C210
                v1 = addu(v1, a0);
                sb(v1, 0, a1);
                break;
            case 0x44B5FCu:  // [6]
                charge(3);
                v1 = lw(s1, 148);
                if (v1 != 0) {
                    charge(44);
                    v0 = addiu(v1, -1);
                    sw(s1, 148, v0);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s1);
                    v0 = lh(v0, 3224);
                    mtc1(v0, 0);
                    cvt_s_w(0, 0);
                    v0 = lui(0x4448u);
                    mtc1(v0, 1);  // 800.0
                    mul_s(0, 1, 0);
                    swc1(0, s1, 108);
                    v0 = lw(s1, 148);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s1);
                    v0 = lh(v0, 3226);
                    mtc1(v0, 0);
                    cvt_s_w(0, 0);
                    mul_s(0, 1, 0);
                    swc1(0, s1, 116);
                    a0 = addiu(s1, 108);
                    jal(0x44B664u, &gen::fn_sub_44F120_0044f120);
                    s0 = v0 & 0xFFFFu;
                    a0 = addiu(s1, 108);
                    jal(0x44B674u, &gen::fn_sub_44F170_0044f170);
                    a2 = v0 & 0xFFFFu;
                    a0 = addiu(sp, 96);
                    a1 = s0;
                    jal(0x44B688u, &gen::fn_sub_1BF220_001bf220);
                    lwc1(2, sp, 96);
                    lwc1(1, sp, 100);
                    lwc1(0, sp, 104);
                    swc1(2, s1, 108);
                    swc1(1, s1, 112);
                    swc1(0, s1, 116);
                    v1 = si(7);
                    sb(s1, 4, v1);
                    break;
                }
                charge(4);
                v1 = si(8);
                sb(s1, 4, v1);
                break;
            case 0x44B6C8u:  // [7]
                charge(21);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, s0);
                a0 = lw(v0, 0);
                a1 = 0;
                jal(0x44B6DCu, &gen::fn_sub_1B0250_001b0250);
                v1 = lb(s1, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, v1);
                a0 = lw(v0, 0);
                a1 = addiu(s1, 108);
                lwc1(12, s2, 12);
                jal(0x44B70Cu, &gen::fn_sub_1AFA20_001afa20);
                if (v0 == 0) break;
                charge(16);
                lwc1(2, s1, 108);
                lwc1(1, s1, 112);
                lwc1(0, s1, 116);
                swc1(2, s1, 96);
                swc1(1, s1, 100);
                swc1(0, s1, 104);
                lwc1(2, s1, 108);
                lwc1(1, s1, 112);
                lwc1(0, s1, 116);
                swc1(2, s1, 80);
                swc1(1, s1, 84);
                swc1(0, s1, 88);
                v1 = si(6);
                sb(s1, 4, v1);
                break;
            case 0x44B75Cu:  // [8]
                charge(8);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, s0);
                a0 = lw(v0, 0);
                jal(0x44B76Cu, &gen::fn_sub_1B0220_001b0220);
                if (v0 != 0) break;
                charge(9);
                a0 = lb(s1, 1);
                a1 = si(4);
                jal(0x44B784u, &gen::fn_sub_4543C0_004543c0);
                a0 = lb(s1, 1);
                v1 = lui(0x96u);
                v1 = addiu(v1, -15856);  // 0x95C210
                v1 = addu(v1, a0);
                sb(v1, 0, zero);
            }
        }
        charge(9);
        ra = ld(sp, 80);
        lq(s4, sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 144);
    }

    // 0x451D70 (task): with a target cell (+139 / +140 not both 0) plans the path from the controller's cell to it
    // (sub_453ED0; found -> +3 = 13, else 15); else sub_4514A0 finds the first step towards the player, and without one
    // the queue is cleared and +108.. = the door of the player's own cell (sub_1BF220), +3 = 15.
    void sub_451D70() {
        enter(10);
        sp = addiu(sp, -176);
        sd(sp, 64, ra);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s3 = lw(a0, kTaskWork);
        s2 = lbu(s3, 139);
        if (s2 == 0) {
            charge(3);
            v0 = lbu(s3, 140);
            if (v0 == 0) {
                charge(5);
                a0 = lb(s3, 1);
                jal(0x451DA8u, &gen::fn_sub_4514A0_004514a0);
                if (v0 != 0) {
                    charge(8);
                    ra = ld(sp, 64);
                    lq(s3, sp, 48);
                    lq(s2, sp, 32);
                    lq(s1, sp, 16);
                    lq(s0, sp, 0);
                    sp = addiu(sp, 176);
                    return;
                }
                charge(84);
                v1 = lb(s3, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, v1);
                a0 = lw(v0, 0);
                jal(0x451DD8u, &gen::fn_sub_1B00C0_001b00c0);
                v1 = lb(s3, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 128);
                a1 = lw(v0, kResController);
                jal(0x451E08u, &gen::fn_sub_1AD940_001ad940);
                v0 = addiu(sp, 128);
                lwc1(2, v0, 0);
                lwc1(1, v0, 4);
                lwc1(0, v0, 8);
                swc1(2, sp, 80);
                swc1(1, sp, 84);
                swc1(0, sp, 88);
                v0 = lui(0x43C8u);
                mtc1(v0, 1);  // 400.0
                lwc1(0, sp, 88);
                add_s(1, 1, 0);
                v0 = lui(0x4448u);
                mtc1(v0, 0);  // 800.0
                div_s(0, 1, 0);
                cvt_w_s(0, 0);
                mfc1(s0, 0);
                v1 = lb(s3, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 144);
                a1 = lw(v0, kResController);
                jal(0x451E7Cu, &gen::fn_sub_1AD940_001ad940);
                v0 = addiu(sp, 144);
                lwc1(2, v0, 0);
                lwc1(1, v0, 4);
                lwc1(0, v0, 8);
                swc1(2, sp, 96);
                swc1(1, sp, 100);
                swc1(0, sp, 104);
                v0 = lui(0x43C8u);
                mtc1(v0, 1);  // 400.0
                lwc1(0, sp, 96);
                add_s(1, 1, 0);
                v0 = lui(0x4448u);
                mtc1(v0, 0);  // 800.0
                div_s(0, 1, 0);
                cvt_w_s(0, 0);
                mfc1(v0, 0);
                a1 = v0 & 0xFFFFu;
                a2 = s0 & 0xFFFFu;
                a0 = addiu(sp, 160);
                jal(0x451ED8u, &gen::fn_sub_1BF220_001bf220);
                lwc1(2, sp, 160);
                lwc1(1, sp, 164);
                lwc1(0, sp, 168);
                swc1(2, s3, 108);
                swc1(1, s3, 112);
                swc1(0, s3, 116);
                v1 = si(15);
                sb(s3, 3, v1);
                charge(8);
                ra = ld(sp, 64);
                lq(s3, sp, 48);
                lq(s2, sp, 32);
                lq(s1, sp, 16);
                lq(s0, sp, 0);
                sp = addiu(sp, 176);
                return;
            }
        }
        charge(50);
        v1 = lb(s3, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4620);  // 0x86EDF4
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        a0 = lw(v0, kResController);
        jal(0x451F2Cu, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
        s1 = dsll32(v0, 24);
        s1 = dsra32(s1, 24);
        v1 = lb(s3, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4620);  // 0x86EDF4
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        a0 = lw(v0, kResController);
        jal(0x451F60u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
        s0 = dsll32(v0, 24);
        s0 = dsra32(s0, 24);
        v1 = lb(s3, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4620);  // 0x86EDF4
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        a0 = addiu(sp, 112);
        a1 = lw(v0, kResController);
        jal(0x451F98u, &gen::fn_sub_1AD940_001ad940);
        a4 = dsll32(s2, 24);
        a4 = dsra32(a4, 24);
        a5 = lb(s3, 140);
        a0 = lb(s3, 1);
        a1 = s1;
        a2 = s0;
        a3 = addiu(sp, 112);
        jal(0x451FBCu, &gen::fn_sub_453ED0_00453ed0);
        v1 = si(1);
        if (v0 == v1) {
            charge(4);
            v1 = si(13);
            sb(s3, 3, v1);
        } else {
            charge(2);
            v1 = si(15);
            sb(s3, 3, v1);
        }
        charge(8);
        ra = ld(sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 176);
    }

    // 0x4523C0 (task, ec): for each other party member i whose sub_43C910 is non-zero: within the record's +20 reach of the
    // shadow and in front of it (sub_1C6450): when it is farther than +20 from the old target point and not on a stair
    // cell, the shadow re-plans to i's cell (sub_453ED0), +24 = i, +3 = 20, returns 1; a member on the stairs instead
    // re-plans to the stored point +40.. (+3 = 20 on success). Returns 0 otherwise.
    void sub_4523C0() {
        enter(34);
        sp = addiu(sp, -400);
        sd(sp, 128, ra);
        sq(s6, sp, 112);
        sq(s5, sp, 96);
        sq(s4, sp, 80);
        sq(s3, sp, 64);
        sq(s2, sp, 48);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(20, sp, 0);
        v1 = dsll32(a1, 24);
        v1 = dsra32(v1, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4340);  // 0x86EF0C
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        s4 = lw(v0, kTaskWork);
        v1 = lb(s4, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4308);  // 0x86EF2C
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        v1 = sll(v0, 6);
        v0 = lw(gp, -19040);
        s3 = addu(v0, v1);
        s5 = 0;
        for (;;) {
            charge(3);
            v0 = slti(s5, 4);
            if (v0 == 0) break;
            backedge();
            charge(3);
            v0 = lb(s4, 24);
            if (s5 != v0) {
                charge(7);
                a0 = dsll32(s5, 24);
                a0 = dsra32(a0, 24);
                jal(0x45245Cu, &gen::fn_sub_43C910_0043c910);
                v0 = v0 & 0xFFFFu;
                if (gtz(v0)) {
                    charge(58);
                    lwc1(20, s3, 20);
                    v0 = sll(s5, 3);
                    v0 = subu(v0, s5);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, 6048);  // 0x8717A0 gFldUnitsPc
                    v0 = addu(v0, v1);
                    s1 = addiu(v0, 84);
                    v0 = lw(v0, 84);
                    a0 = addiu(sp, 368);
                    a1 = lw(v0, kResController);
                    jal(0x45249Cu, &gen::fn_sub_1AD940_001ad940);
                    s0 = addiu(sp, 368);
                    v1 = lb(s4, 1);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                    v0 = addu(v0, v1);
                    v0 = lw(v0, 84);
                    a0 = addiu(sp, 384);
                    a1 = lw(v0, kResController);
                    jal(0x4524D0u, &gen::fn_sub_1AD940_001ad940);
                    v0 = addiu(sp, 384);
                    lwc1(2, v0, 0);
                    lwc1(1, v0, 4);
                    lwc1(0, v0, 8);
                    swc1(2, sp, 272);
                    swc1(1, sp, 276);
                    swc1(0, sp, 280);
                    lwc1(2, s0, 0);
                    lwc1(1, s0, 4);
                    lwc1(0, s0, 8);
                    swc1(2, sp, 256);
                    swc1(1, sp, 260);
                    swc1(0, sp, 264);
                    s0 = 0;
                    lwc1(1, sp, 272);
                    lwc1(0, sp, 256);
                    sub_s(0, 1, 0);
                    swc1(0, sp, 240);
                    lwc1(1, sp, 276);
                    lwc1(0, sp, 260);
                    sub_s(0, 1, 0);
                    swc1(0, sp, 244);
                    lwc1(1, sp, 280);
                    lwc1(0, sp, 264);
                    sub_s(0, 1, 0);
                    swc1(0, sp, 248);
                    a0 = addiu(sp, 240);
                    jal(0x452544u, &gen::fn_sub_4C6AC0_004c6ac0);
                    c_lt_s(0, 20);
                    if (cond()) {
                        charge(1);
                        s0 = si(1);
                    }
                    charge(3);
                    v0 = si(1);
                    if (s0 == v0) {
                        charge(26);
                        v1 = lb(s4, 1);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                        v0 = addu(v0, v1);
                        v0 = lw(v0, 84);
                        a0 = lw(v0, 296);
                        jal(0x45258Cu, &gen::fn_sub_318B60_00318b60);
                        s0 = v0;
                        v0 = lw(s1, 0);
                        a0 = addiu(sp, 352);
                        a1 = lw(v0, kResController);
                        jal(0x4525A4u, &gen::fn_sub_1AD940_001ad940);
                        a0 = s0;
                        a1 = addiu(sp, 352);
                        lwc1(12, s3, 16);
                        lwc1(13, s3, 20);
                        jal(0x4525BCu, &gen::fn_sub_1C6450_001c6450);
                        v1 = si(1);
                        if (v0 == v1) {
                            charge(58);
                            lwc1(20, s3, 20);
                            v1 = lb(s4, 24);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, 6048);  // 0x8717A0 gFldUnitsPc
                            v0 = addu(v0, v1);
                            v0 = lw(v0, 84);
                            a0 = addiu(sp, 320);
                            a1 = lw(v0, kResController);
                            jal(0x4525FCu, &gen::fn_sub_1AD940_001ad940);
                            s0 = addiu(sp, 320);
                            v1 = lb(s4, 1);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                            v0 = addu(v0, v1);
                            v0 = lw(v0, 84);
                            a0 = addiu(sp, 336);
                            a1 = lw(v0, kResController);
                            jal(0x452630u, &gen::fn_sub_1AD940_001ad940);
                            v0 = addiu(sp, 336);
                            lwc1(2, v0, 0);
                            lwc1(1, v0, 4);
                            lwc1(0, v0, 8);
                            swc1(2, sp, 224);
                            swc1(1, sp, 228);
                            swc1(0, sp, 232);
                            lwc1(2, s0, 0);
                            lwc1(1, s0, 4);
                            lwc1(0, s0, 8);
                            swc1(2, sp, 208);
                            swc1(1, sp, 212);
                            swc1(0, sp, 216);
                            s0 = 0;
                            lwc1(1, sp, 224);
                            lwc1(0, sp, 208);
                            sub_s(0, 1, 0);
                            swc1(0, sp, 192);
                            lwc1(1, sp, 228);
                            lwc1(0, sp, 212);
                            sub_s(0, 1, 0);
                            swc1(0, sp, 196);
                            lwc1(1, sp, 232);
                            lwc1(0, sp, 216);
                            sub_s(0, 1, 0);
                            swc1(0, sp, 200);
                            a0 = addiu(sp, 192);
                            jal(0x4526A4u, &gen::fn_sub_4C6AC0_004c6ac0);
                            c_lt_s(0, 20);
                            if (cond()) {
                                charge(1);
                                s0 = si(1);
                            }
                            charge(2);
                            if (s0 == 0) {
                                charge(33);
                                v0 = sll(s5, 3);
                                v0 = subu(v0, s5);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, 6048);  // 0x8717A0 gFldUnitsPc
                                v0 = addu(v0, v1);
                                s1 = addiu(v0, 84);
                                v0 = lw(v0, 84);
                                a0 = lw(v0, kResController);
                                jal(0x4526E8u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                                s0 = dsll32(v0, 16);
                                s0 = dsra32(s0, 16);
                                v0 = lw(s1, 0);
                                a0 = lw(v0, kResController);
                                jal(0x452700u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                                s1 = dsll32(v0, 16);
                                s1 = dsra32(s1, 16);
                                jal(0x452710u, &gen::fn_K_Field_Get_001b9120);
                                v1 = dsll32(s1, 16);
                                v1 = dsra32(v1, 16);
                                v1 = sll(v1, 8);
                                v1 = addu(v0, v1);
                                v0 = dsll32(s0, 16);
                                v0 = dsra32(v0, 16);
                                v0 = sll(v0, 4);
                                v0 = addu(v1, v0);
                                v1 = lbu(v0, 74);
                                v0 = si(8);
                                if (v1 == v0) {
                                    charge(78);
                                    lwc1(2, s4, 40);
                                    lwc1(1, s4, 44);
                                    lwc1(0, s4, 48);
                                    swc1(2, sp, 144);
                                    swc1(1, sp, 148);
                                    swc1(0, sp, 152);
                                    v1 = ld(sp, 144);
                                    lwc1(3, sp, 152);
                                    sd(sp, 160, v1);
                                    swc1(3, sp, 168);
                                    v0 = lui(0x43C8u);
                                    mtc1(v0, 2);  // 400.0
                                    lwc1(0, sp, 168);
                                    add_s(0, 2, 0);
                                    v0 = lui(0x4448u);
                                    mtc1(v0, 1);  // 800.0
                                    div_s(0, 0, 1);
                                    cvt_w_s(0, 0);
                                    mfc1(s2, 0);
                                    sd(sp, 176, v1);
                                    swc1(3, sp, 184);
                                    lwc1(0, sp, 176);
                                    add_s(0, 2, 0);
                                    div_s(0, 0, 1);
                                    cvt_w_s(0, 0);
                                    mfc1(s1, 0);
                                    v1 = lb(s4, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 84);
                                    a0 = lw(v0, kResController);
                                    jal(0x4527D8u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                                    s0 = dsll32(v0, 24);
                                    s0 = dsra32(s0, 24);
                                    v1 = lb(s4, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 84);
                                    a0 = lw(v0, kResController);
                                    jal(0x45280Cu, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                                    s6 = dsll32(v0, 24);
                                    s6 = dsra32(s6, 24);
                                    v1 = lb(s4, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 84);
                                    a0 = addiu(sp, 304);
                                    a1 = lw(v0, kResController);
                                    jal(0x452844u, &gen::fn_sub_1AD940_001ad940);
                                    a4 = dsll32(s1, 24);
                                    a4 = dsra32(a4, 24);
                                    a5 = dsll32(s2, 24);
                                    a5 = dsra32(a5, 24);
                                    a0 = lb(s4, 1);
                                    a1 = s0;
                                    a2 = s6;
                                    a3 = addiu(sp, 304);
                                    jal(0x45286Cu, &gen::fn_sub_453ED0_00453ed0);
                                    v1 = si(1);
                                    if (v0 == v1) {
                                        charge(15);
                                        v1 = lb(s4, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                        v0 = addu(v0, v1);
                                        a0 = lw(v0, 368);
                                        a1 = 0;
                                        jal(0x4528A4u, &gen::fn_sub_1B0240_001b0240);
                                        v0 = si(20);
                                        sb(s4, 3, v0);
                                    }
                                } else {
                                    charge(90);
                                    v1 = lb(s4, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4336);  // 0x86EF10
                                    v0 = addu(v0, v1);
                                    a0 = lw(v0, 0);
                                    jal(0x4528DCu, &gen::fn_sub_1B00C0_001b00c0);
                                    v0 = sll(s5, 3);
                                    v0 = subu(v0, s5);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, 6132);  // 0x8717F4
                                    s3 = addu(v0, v1);
                                    v1 = lb(s4, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4620);  // 0x86EDF4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = lw(v0, kResController);
                                    jal(0x452920u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                                    s2 = dsll32(v0, 24);
                                    s2 = dsra32(s2, 24);
                                    v1 = lb(s4, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4620);  // 0x86EDF4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = lw(v0, kResController);
                                    jal(0x452954u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                                    s1 = dsll32(v0, 24);
                                    s1 = dsra32(s1, 24);
                                    v1 = lb(s4, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4620);  // 0x86EDF4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = addiu(sp, 288);
                                    a1 = lw(v0, kResController);
                                    jal(0x45298Cu, &gen::fn_sub_1AD940_001ad940);
                                    v0 = lw(s3, 0);
                                    a0 = lw(v0, kResController);
                                    jal(0x45299Cu, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                                    s0 = dsll32(v0, 24);
                                    s0 = dsra32(s0, 24);
                                    v0 = lw(s3, 0);
                                    a0 = lw(v0, kResController);
                                    jal(0x4529B4u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                                    a5 = dsll32(v0, 24);
                                    a5 = dsra32(a5, 24);
                                    a0 = lb(s4, 1);
                                    a1 = s2;
                                    a2 = s1;
                                    a3 = addiu(sp, 288);
                                    a4 = s0;
                                    jal(0x4529D8u, &gen::fn_sub_453ED0_00453ed0);
                                    v1 = lb(s4, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4336);  // 0x86EF10
                                    v0 = addu(v0, v1);
                                    a0 = lw(v0, 0);
                                    a1 = 0;
                                    jal(0x452A04u, &gen::fn_sub_1B0240_001b0240);
                                    sb(s4, 24, s5);
                                    v0 = si(20);
                                    sb(s4, 3, v0);
                                    v0 = si(1);
                                    charge(12);
                                    ra = ld(sp, 128);
                                    lq(s6, sp, 112);
                                    lq(s5, sp, 96);
                                    lq(s4, sp, 80);
                                    lq(s3, sp, 64);
                                    lq(s2, sp, 48);
                                    lq(s1, sp, 32);
                                    lq(s0, sp, 16);
                                    lwc1(20, sp, 0);
                                    sp = addiu(sp, 400);
                                    return;
                                }
                            }
                        }
                    }
                }
            }
            charge(1);
            s5 = addiu(s5, 1);
        }
        charge(1);
        v0 = 0;
        charge(12);
        ra = ld(sp, 128);
        lq(s6, sp, 112);
        lq(s5, sp, 96);
        lq(s4, sp, 80);
        lq(s3, sp, 64);
        lq(s2, sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(20, sp, 0);
        sp = addiu(sp, 400);
    }

    // 0x452A70 (ec, pc): when party member pc's position is at least 1600 from the shadow's remembered target point +28..
    // (RwV3dNormalize's length): +28.. = the new position, and the path is planned to the target member's cell
    // (sub_453ED0) -- or, when that member stands on a stair cell, to the stored point +40.. (sub-state 20 on success);
    // returns 1. Closer: 0.
    void sub_452A70() {
        enter(89);
        sp = addiu(sp, -256);
        sd(sp, 80, ra);
        sq(s4, sp, 64);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s4 = a1;
        v1 = dsll32(a0, 24);
        v1 = dsra32(v1, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4340);  // 0x86EF0C
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        s0 = lw(v0, kTaskWork);
        v1 = lb(s0, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, 6132);  // 0x8717F4
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        a0 = lw(v0, kResController);
        jal(0x452ADCu, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
        s3 = dsll32(v0, 16);
        s3 = dsra32(s3, 16);
        v1 = lb(s0, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, 6132);  // 0x8717F4
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        a0 = lw(v0, kResController);
        jal(0x452B10u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
        s2 = dsll32(v0, 16);
        s2 = dsra32(s2, 16);
        v1 = dsll32(s4, 24);
        v1 = dsra32(v1, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, 6132);  // 0x8717F4
        s1 = addu(v0, v1);
        v0 = lw(s1, 0);
        a0 = addiu(sp, 224);
        a1 = lw(v0, kResController);
        jal(0x452B4Cu, &gen::fn_sub_1AD940_001ad940);
        lwc1(1, sp, 224);
        lwc1(0, s0, 28);
        sub_s(0, 1, 0);
        swc1(0, sp, 240);
        v0 = lw(s1, 0);
        a0 = addiu(sp, 208);
        a1 = lw(v0, kResController);
        jal(0x452B70u, &gen::fn_sub_1AD940_001ad940);
        lwc1(1, sp, 212);
        lwc1(0, s0, 32);
        sub_s(0, 1, 0);
        swc1(0, sp, 244);
        v0 = lw(s1, 0);
        a0 = addiu(sp, 192);
        a1 = lw(v0, kResController);
        jal(0x452B94u, &gen::fn_sub_1AD940_001ad940);
        lwc1(1, sp, 200);
        lwc1(0, s0, 36);
        sub_s(0, 1, 0);
        swc1(0, sp, 248);
        a0 = addiu(sp, 240);
        a1 = a0;
        jal(0x452BB4u, &gen::fn_sub_4C69F0_004c69f0);
        v0 = lui(0x44C8u);
        mtc1(v0, 1);  // 1600f
        c_lt_s(0, 1);
        if (!cond()) {
            charge(35);
            v1 = lb(s0, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4336);  // 0x86EF10
            v0 = addu(v0, v1);
            a0 = lw(v0, 0);
            jal(0x452BF4u, &gen::fn_sub_1B00C0_001b00c0);
            v0 = lw(s1, 0);
            a0 = addiu(sp, 176);
            a1 = lw(v0, kResController);
            jal(0x452C08u, &gen::fn_sub_1AD940_001ad940);
            lwc1(2, sp, 176);
            lwc1(1, sp, 180);
            lwc1(0, sp, 184);
            swc1(2, s0, 28);
            swc1(1, s0, 32);
            swc1(0, s0, 36);
            jal(0x452C28u, &gen::fn_K_Field_Get_001b9120);
            v1 = dsll32(s2, 16);
            v1 = dsra32(v1, 16);
            v1 = sll(v1, 8);
            v1 = addu(v0, v1);
            v0 = dsll32(s3, 16);
            v0 = dsra32(v0, 16);
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            v1 = lbu(v0, 74);
            v0 = si(8);
            if (v1 == v0) {
                charge(100);
                v1 = lb(s0, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6132);  // 0x8717F4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = lw(v0, kResController);
                jal(0x452C84u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                v1 = lb(s0, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6132);  // 0x8717F4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = lw(v0, kResController);
                jal(0x452CB0u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                lwc1(2, s0, 40);
                lwc1(1, s0, 44);
                lwc1(0, s0, 48);
                swc1(2, sp, 96);
                swc1(1, sp, 100);
                swc1(0, sp, 104);
                v1 = ld(sp, 96);
                lwc1(3, sp, 104);
                sd(sp, 112, v1);
                swc1(3, sp, 120);
                v0 = lui(0x43C8u);
                mtc1(v0, 2);  // 400.0
                lwc1(0, sp, 120);
                add_s(0, 2, 0);
                v0 = lui(0x4448u);
                mtc1(v0, 1);  // 800.0
                div_s(0, 0, 1);
                cvt_w_s(0, 0);
                mfc1(s4, 0);
                sd(sp, 128, v1);
                swc1(3, sp, 136);
                lwc1(0, sp, 128);
                add_s(0, 2, 0);
                div_s(0, 0, 1);
                cvt_w_s(0, 0);
                mfc1(s3, 0);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = lw(v0, kResController);
                jal(0x452D48u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                s2 = dsll32(v0, 24);
                s2 = dsra32(s2, 24);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = lw(v0, kResController);
                jal(0x452D7Cu, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                s1 = dsll32(v0, 24);
                s1 = dsra32(s1, 24);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 160);
                a1 = lw(v0, kResController);
                jal(0x452DB4u, &gen::fn_sub_1AD940_001ad940);
                a4 = dsll32(s3, 24);
                a4 = dsra32(a4, 24);
                a5 = dsll32(s4, 24);
                a5 = dsra32(a5, 24);
                a0 = lb(s0, 1);
                a1 = s2;
                a2 = s1;
                a3 = addiu(sp, 160);
                jal(0x452DDCu, &gen::fn_sub_453ED0_00453ed0);
                v1 = si(1);
                if (v0 == v1) {
                    charge(13);
                    v1 = lb(s0, 1);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, -4336);  // 0x86EF10
                    v0 = addu(v0, v1);
                    a0 = lw(v0, 0);
                    a1 = 0;
                    jal(0x452E14u, &gen::fn_sub_1B0240_001b0240);
                    v0 = si(20);
                    sb(s0, 3, v0);
                }
                charge(3);
                v0 = si(1);
            } else {
                charge(70);
                v1 = dsll32(s4, 24);
                v1 = dsra32(v1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6132);  // 0x8717F4
                s3 = addu(v0, v1);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = lw(v0, kResController);
                jal(0x452E74u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                s2 = dsll32(v0, 24);
                s2 = dsra32(s2, 24);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = lw(v0, kResController);
                jal(0x452EA8u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                s1 = dsll32(v0, 24);
                s1 = dsra32(s1, 24);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 144);
                a1 = lw(v0, kResController);
                jal(0x452EE0u, &gen::fn_sub_1AD940_001ad940);
                v0 = lw(s3, 0);
                a0 = lw(v0, kResController);
                jal(0x452EF0u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                s4 = dsll32(v0, 24);
                s4 = dsra32(s4, 24);
                v0 = lw(s3, 0);
                a0 = lw(v0, kResController);
                jal(0x452F08u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                a5 = dsll32(v0, 24);
                a5 = dsra32(a5, 24);
                a0 = lb(s0, 1);
                a1 = s2;
                a2 = s1;
                a3 = addiu(sp, 144);
                a4 = s4;
                jal(0x452F2Cu, &gen::fn_sub_453ED0_00453ed0);
                v0 = si(20);
                sb(s0, 3, v0);
                v0 = si(1);
            }
        } else {
            charge(1);
            v0 = 0;
        }
        charge(9);
        ra = ld(sp, 80);
        lq(s4, sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 256);
    }

    // 0x454110 (the think update on fixed floors): state 5 clears the mover's queue and pause and records the shadow in
    // gp-0x45FC (gp-0x4600 = 0); state 4 -> sub_44B7D0; state 3 -> sub_44D600.
    void sub_454110() {
        enter(8);
        sp = addiu(sp, -32);
        sd(sp, 16, ra);
        sq(s0, sp, 0);
        s0 = lw(a0, kTaskWork);
        a1 = lb(s0, 2);
        v1 = si(6);
        if (a1 != v1) {
            charge(3);
            v1 = si(5);
            if (a1 != v1) {
                charge(3);
                v1 = si(4);
                if (a1 != v1) {
                    charge(3);
                    v1 = si(3);
                    if (a1 != v1) {
                        charge(2);
                    } else {
                        charge(4);
                        jal(0x45415Cu, &gen::fn_sub_44D600_0044d600);
                    }
                } else {
                    charge(4);
                    jal(0x45416Cu, &gen::fn_sub_44B7D0_0044b7d0);
                }
            } else {
                charge(24);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, v1);
                a0 = lw(v0, 0);
                jal(0x45419Cu, &gen::fn_sub_1B00C0_001b00c0);
                v1 = lb(s0, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, v1);
                a0 = lw(v0, 0);
                a1 = 0;
                jal(0x4541C8u, &gen::fn_sub_1B0240_001b0240);
                v1 = lb(s0, 1);
                sh(gp, -17916, v1);
                sb(gp, -17920, zero);
            }
        }
        charge(5);
        ra = ld(sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 32);
    }

    // 0x44BEB0 (think state 3 on random floors; sub-state +3): 2..6 -> sub_4501B0, 7..11 -> sub_450B30; 0 alert (as
    // sub_44D600) -> 1; 1 counts +7 down, then by behaviour kind (+396): 1 / 5 seen (sub_1C65E0) -> 2 else 24, 2 -> 7 or 24,
    // 3 -> 12, 4 -> 18; 12 plans to the player's path step (sub_4514A0, sub_453ED0 -> 13 / 15); 13 pops a path cell and its
    // door -> 14; 14 walks there -> 13; 15 waits for the queue, then -> 16 and the dead effect (Y_Stratum_CreateEneDeadEffectTask, the unit's
    // +408..+411 cleared); 17 sub_451D70; 18 / 19 pick the target member (sub_43C910), remember its position (+28..) and
    // plan to it (stairs: to +40..; -> 20 / 22); 20 pops path cells -> 21 / 22; 21 walks (contact in front -> state 5);
    // 22 close in on the target (contact -> 5; on the stairs: step to the stored door +52.. and a "y wait task"
    // Y_Kyoto_CreateWaitTask -> 23); 23 waits for that task -> 19; 24 pursuit (sub_454F50); 25 waits for the queue, then wanders.
    // sub_4523C0 / sub_452A70 may switch or re-plan first in 20..22.
    void sub_44BEB0() {
        enter(25);
        sp = addiu(sp, -448);
        sd(sp, 96, ra);
        sq(s5, sp, 80);
        sq(s4, sp, 64);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s2 = a0;
        s1 = lw(a0, kTaskWork);
        a1 = lb(s1, 1);
        v1 = sll(a1, 3);
        v1 = subu(v1, a1);
        a2 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, -4308);  // 0x86EF2C
        v1 = addu(v1, a2);
        a0 = lw(v1, 0);
        a3 = sll(a0, 6);
        v1 = lw(gp, -19040);
        s0 = addu(v1, a3);
        v1 = lb(s1, 3);
        a3 = slti(v1, 2);
        if (a3 == 0) {
            charge(3);
            at = slti(v1, 7);
            if (at != 0) {
                charge(5);
                a0 = a1;
                jal(0x44BF24u, &gen::fn_sub_4501B0_004501b0);
                charge(10);
                ra = ld(sp, 96);
                lq(s5, sp, 80);
                lq(s4, sp, 64);
                lq(s3, sp, 48);
                lq(s2, sp, 32);
                lq(s1, sp, 16);
                lq(s0, sp, 0);
                sp = addiu(sp, 448);
                return;
            }
        }
        charge(3);
        a3 = slti(v1, 7);
        if (a3 == 0) {
            charge(3);
            at = slti(v1, 12);
            if (at != 0) {
                charge(5);
                a0 = a1;
                jal(0x44BF50u, &gen::fn_sub_450B30_00450b30);
                charge(10);
                ra = ld(sp, 96);
                lq(s5, sp, 80);
                lq(s4, sp, 64);
                lq(s3, sp, 48);
                lq(s2, sp, 32);
                lq(s1, sp, 16);
                lq(s0, sp, 0);
                sp = addiu(sp, 448);
                return;
            }
        }
        charge(3);
        a3 = si(25);
        if (v1 != a3) {
            charge(3);
            a3 = si(24);
            if (v1 != a3) {
                charge(3);
                a3 = si(23);
                if (v1 != a3) {
                    charge(3);
                    a3 = si(22);
                    if (v1 != a3) {
                        charge(3);
                        a3 = si(21);
                        if (v1 != a3) {
                            charge(3);
                            a3 = si(20);
                            if (v1 != a3) {
                                charge(3);
                                a1 = si(19);
                                if (v1 != a1) {
                                    charge(3);
                                    a4 = si(18);
                                    if (v1 != a4) {
                                        charge(3);
                                        a1 = si(17);
                                        if (v1 != a1) {
                                            charge(3);
                                            a1 = si(16);
                                            if (v1 == a1) {
                                                charge(10);
                                                ra = ld(sp, 96);
                                                lq(s5, sp, 80);
                                                lq(s4, sp, 64);
                                                lq(s3, sp, 48);
                                                lq(s2, sp, 32);
                                                lq(s1, sp, 16);
                                                lq(s0, sp, 0);
                                                sp = addiu(sp, 448);
                                                return;
                                            }
                                            charge(3);
                                            a3 = si(15);
                                            if (v1 != a3) {
                                                charge(3);
                                                a1 = si(14);
                                                if (v1 != a1) {
                                                    charge(3);
                                                    a1 = si(13);
                                                    if (v1 != a1) {
                                                        charge(3);
                                                        a3 = si(12);
                                                        if (v1 != a3) {
                                                            charge(3);
                                                            a1 = si(1);
                                                            if (v1 != a1) {
                                                                charge(2);
                                                                if (v1 != 0) {
                                                                    charge(2);
                                                                    charge(10);
                                                                    ra = ld(sp, 96);
                                                                    lq(s5, sp, 80);
                                                                    lq(s4, sp, 64);
                                                                    lq(s3, sp, 48);
                                                                    lq(s2, sp, 32);
                                                                    lq(s1, sp, 16);
                                                                    lq(s0, sp, 0);
                                                                    sp = addiu(sp, 448);
                                                                    return;
                                                                }
                                                                charge(48);
                                                                v0 = lui(0x87u);
                                                                v0 = addiu(v0, -4620);  // 0x86EDF4
                                                                v0 = addu(v0, a2);
                                                                v0 = lw(v0, 0);
                                                                a0 = addiu(sp, 416);
                                                                a1 = lw(v0, kResController);
                                                                jal(0x44C03Cu, &gen::fn_sub_1AD940_001ad940);
                                                                lwc1(2, sp, 416);
                                                                lwc1(1, sp, 420);
                                                                lwc1(0, sp, 424);
                                                                swc1(2, sp, 432);
                                                                swc1(1, sp, 436);
                                                                swc1(0, sp, 440);
                                                                lwc1(1, sp, 436);
                                                                v0 = lui(0x42C8u);
                                                                mtc1(v0, 0);  // 100.0
                                                                add_s(0, 1, 0);
                                                                swc1(0, sp, 436);
                                                                jal(0x44C074u, &gen::fn_K_Field_Get_001b9120);
                                                                a0 = lw(v0, 4616);
                                                                a1 = addiu(sp, 432);
                                                                jal(0x44C084u, &gen::fn_sub_1A91B0_001a91b0);
                                                                s2 = v0;
                                                                jal(0x44C090u, &gen::fn_K_Field_Get_001b9120);
                                                                a0 = lw(v0, 4616);
                                                                a1 = s2;
                                                                a2 = si(3);
                                                                jal(0x44C0A4u, &gen::fn_sub_1A9390_001a9390);
                                                                v1 = lb(s1, 1);
                                                                v0 = sll(v1, 3);
                                                                v0 = subu(v0, v1);
                                                                v1 = sll(v0, 6);
                                                                v0 = lui(0x87u);
                                                                v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                                                a0 = addu(v0, v1);
                                                                v0 = lui(0x4516u);
                                                                mtc1(v0, 12);  // 2400f
                                                                jal(0x44C0D0u, &gen::fn_sub_1C7130_001c7130);
                                                                a0 = si(1);
                                                                if (v0 == a0) {
                                                                    charge(5);
                                                                    a1 = si(8);
                                                                    a2 = si(3);
                                                                    a3 = si(4);
                                                                    jal(0x44C0F0u, &gen::fn_sub_10A4E0_0010a4e0);
                                                                }
                                                                charge(38);
                                                                v0 = lw(s0, 36);
                                                                sb(s1, 7, v0);
                                                                v1 = lb(s1, 1);
                                                                v0 = sll(v1, 3);
                                                                v0 = subu(v0, v1);
                                                                v1 = sll(v0, 6);
                                                                v0 = lui(0x87u);
                                                                v0 = addiu(v0, -4336);  // 0x86EF10
                                                                v0 = addu(v0, v1);
                                                                a0 = lw(v0, 0);
                                                                a1 = 0;
                                                                jal(0x44C124u, &gen::fn_sub_1B0250_001b0250);
                                                                v1 = lb(s1, 1);
                                                                v0 = sll(v1, 3);
                                                                v0 = subu(v0, v1);
                                                                v1 = sll(v0, 6);
                                                                v0 = lui(0x87u);
                                                                v0 = addiu(v0, -4336);  // 0x86EF10
                                                                v0 = addu(v0, v1);
                                                                a0 = lw(v0, 0);
                                                                jal(0x44C14Cu, &gen::fn_sub_1B00C0_001b00c0);
                                                                v1 = lb(s1, 1);
                                                                v0 = sll(v1, 3);
                                                                v0 = subu(v0, v1);
                                                                v1 = sll(v0, 6);
                                                                v0 = lui(0x87u);
                                                                v0 = addiu(v0, -4336);  // 0x86EF10
                                                                v0 = addu(v0, v1);
                                                                a0 = lw(v0, 0);
                                                                a1 = 0;
                                                                jal(0x44C178u, &gen::fn_sub_1B0240_001b0240);
                                                                v1 = si(1);
                                                                sb(s1, 3, v1);
                                                                charge(10);
                                                                ra = ld(sp, 96);
                                                                lq(s5, sp, 80);
                                                                lq(s4, sp, 64);
                                                                lq(s3, sp, 48);
                                                                lq(s2, sp, 32);
                                                                lq(s1, sp, 16);
                                                                lq(s0, sp, 0);
                                                                sp = addiu(sp, 448);
                                                                return;
                                                            }
                                                            charge(3);
                                                            v1 = lb(s1, 7);
                                                            if (lez(v1)) {
                                                                charge(3);
                                                                v1 = si(5);
                                                                if (a0 != v1) {
                                                                    charge(3);
                                                                    v1 = si(4);
                                                                    if (a0 != v1) {
                                                                        charge(3);
                                                                        v1 = si(3);
                                                                        if (a0 != v1) {
                                                                            charge(3);
                                                                            v1 = si(2);
                                                                            if (a0 != v1) {
                                                                                charge(2);
                                                                                if (a0 != a1) {
                                                                                    charge(2);
                                                                                    charge(10);
                                                                                    ra = ld(sp, 96);
                                                                                    lq(s5, sp, 80);
                                                                                    lq(s4, sp, 64);
                                                                                    lq(s3, sp, 48);
                                                                                    lq(s2, sp, 32);
                                                                                    lq(s1, sp, 16);
                                                                                    lq(s0, sp, 0);
                                                                                    sp = addiu(sp, 448);
                                                                                    return;
                                                                                }
                                                                                charge(8);
                                                                                v0 = lui(0x87u);
                                                                                v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                                                                a0 = addu(v0, a2);
                                                                                jal(0x44C1E8u, &gen::fn_sub_1C65E0_001c65e0);
                                                                                v1 = si(1);
                                                                                if (v0 == v1) {
                                                                                    charge(4);
                                                                                    v1 = si(2);
                                                                                    sb(s1, 3, v1);
                                                                                    charge(10);
                                                                                    ra = ld(sp, 96);
                                                                                    lq(s5, sp, 80);
                                                                                    lq(s4, sp, 64);
                                                                                    lq(s3, sp, 48);
                                                                                    lq(s2, sp, 32);
                                                                                    lq(s1, sp, 16);
                                                                                    lq(s0, sp, 0);
                                                                                    sp = addiu(sp, 448);
                                                                                    return;
                                                                                }
                                                                                charge(4);
                                                                                v1 = si(24);
                                                                                sb(s1, 3, v1);
                                                                                charge(10);
                                                                                ra = ld(sp, 96);
                                                                                lq(s5, sp, 80);
                                                                                lq(s4, sp, 64);
                                                                                lq(s3, sp, 48);
                                                                                lq(s2, sp, 32);
                                                                                lq(s1, sp, 16);
                                                                                lq(s0, sp, 0);
                                                                                sp = addiu(sp, 448);
                                                                                return;
                                                                            }
                                                                            charge(8);
                                                                            v0 = lui(0x87u);
                                                                            v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                                                            a0 = addu(v0, a2);
                                                                            jal(0x44C228u, &gen::fn_sub_1C65E0_001c65e0);
                                                                            v1 = si(1);
                                                                            if (v0 == v1) {
                                                                                charge(4);
                                                                                v1 = si(7);
                                                                                sb(s1, 3, v1);
                                                                                charge(10);
                                                                                ra = ld(sp, 96);
                                                                                lq(s5, sp, 80);
                                                                                lq(s4, sp, 64);
                                                                                lq(s3, sp, 48);
                                                                                lq(s2, sp, 32);
                                                                                lq(s1, sp, 16);
                                                                                lq(s0, sp, 0);
                                                                                sp = addiu(sp, 448);
                                                                                return;
                                                                            }
                                                                            charge(4);
                                                                            v1 = si(24);
                                                                            sb(s1, 3, v1);
                                                                            charge(10);
                                                                            ra = ld(sp, 96);
                                                                            lq(s5, sp, 80);
                                                                            lq(s4, sp, 64);
                                                                            lq(s3, sp, 48);
                                                                            lq(s2, sp, 32);
                                                                            lq(s1, sp, 16);
                                                                            lq(s0, sp, 0);
                                                                            sp = addiu(sp, 448);
                                                                            return;
                                                                        }
                                                                        charge(3);
                                                                        sb(s1, 3, a3);
                                                                        charge(10);
                                                                        ra = ld(sp, 96);
                                                                        lq(s5, sp, 80);
                                                                        lq(s4, sp, 64);
                                                                        lq(s3, sp, 48);
                                                                        lq(s2, sp, 32);
                                                                        lq(s1, sp, 16);
                                                                        lq(s0, sp, 0);
                                                                        sp = addiu(sp, 448);
                                                                        return;
                                                                    }
                                                                    charge(3);
                                                                    sb(s1, 3, a4);
                                                                    charge(10);
                                                                    ra = ld(sp, 96);
                                                                    lq(s5, sp, 80);
                                                                    lq(s4, sp, 64);
                                                                    lq(s3, sp, 48);
                                                                    lq(s2, sp, 32);
                                                                    lq(s1, sp, 16);
                                                                    lq(s0, sp, 0);
                                                                    sp = addiu(sp, 448);
                                                                    return;
                                                                }
                                                                charge(8);
                                                                v0 = lui(0x87u);
                                                                v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                                                a0 = addu(v0, a2);
                                                                jal(0x44C280u, &gen::fn_sub_1C65E0_001c65e0);
                                                                v1 = si(1);
                                                                if (v0 == v1) {
                                                                    charge(4);
                                                                    v1 = si(2);
                                                                    sb(s1, 3, v1);
                                                                    charge(10);
                                                                    ra = ld(sp, 96);
                                                                    lq(s5, sp, 80);
                                                                    lq(s4, sp, 64);
                                                                    lq(s3, sp, 48);
                                                                    lq(s2, sp, 32);
                                                                    lq(s1, sp, 16);
                                                                    lq(s0, sp, 0);
                                                                    sp = addiu(sp, 448);
                                                                    return;
                                                                }
                                                                charge(4);
                                                                v1 = si(24);
                                                                sb(s1, 3, v1);
                                                                charge(10);
                                                                ra = ld(sp, 96);
                                                                lq(s5, sp, 80);
                                                                lq(s4, sp, 64);
                                                                lq(s3, sp, 48);
                                                                lq(s2, sp, 32);
                                                                lq(s1, sp, 16);
                                                                lq(s0, sp, 0);
                                                                sp = addiu(sp, 448);
                                                                return;
                                                            }
                                                            charge(4);
                                                            v1 = addiu(v1, -1);
                                                            sb(s1, 7, v1);
                                                            charge(10);
                                                            ra = ld(sp, 96);
                                                            lq(s5, sp, 80);
                                                            lq(s4, sp, 64);
                                                            lq(s3, sp, 48);
                                                            lq(s2, sp, 32);
                                                            lq(s1, sp, 16);
                                                            lq(s0, sp, 0);
                                                            sp = addiu(sp, 448);
                                                            return;
                                                        }
                                                        charge(18);
                                                        v0 = lb(gp, -17972);
                                                        sb(s1, 72, v0);
                                                        v1 = lb(s1, 1);
                                                        v0 = sll(v1, 3);
                                                        v0 = subu(v0, v1);
                                                        v1 = sll(v0, 6);
                                                        v0 = lui(0x87u);
                                                        v0 = addiu(v0, -4336);  // 0x86EF10
                                                        v0 = addu(v0, v1);
                                                        a0 = lw(v0, 0);
                                                        a1 = 0;
                                                        jal(0x44C2F0u, &gen::fn_sub_1B0240_001b0240);
                                                        a0 = lb(s1, 1);
                                                        jal(0x44C2FCu, &gen::fn_sub_4514A0_004514a0);
                                                        if (v0 == 0) {
                                                            charge(56);
                                                            v1 = lb(s1, 1);
                                                            v0 = sll(v1, 3);
                                                            v0 = subu(v0, v1);
                                                            v1 = sll(v0, 6);
                                                            v0 = lui(0x87u);
                                                            v0 = addiu(v0, -4336);  // 0x86EF10
                                                            v0 = addu(v0, v1);
                                                            a0 = lw(v0, 0);
                                                            jal(0x44C32Cu, &gen::fn_sub_1B00C0_001b00c0);
                                                            v1 = lb(s1, 1);
                                                            v0 = sll(v1, 3);
                                                            v0 = subu(v0, v1);
                                                            v1 = sll(v0, 6);
                                                            v0 = lui(0x87u);
                                                            v0 = addiu(v0, -4620);  // 0x86EDF4
                                                            v0 = addu(v0, v1);
                                                            v0 = lw(v0, 0);
                                                            a0 = addiu(sp, 384);
                                                            a1 = lw(v0, kResController);
                                                            jal(0x44C35Cu, &gen::fn_sub_1AD940_001ad940);
                                                            a0 = addiu(sp, 384);
                                                            jal(0x44C368u, &gen::fn_sub_44F120_0044f120);
                                                            s0 = v0 & 0xFFFFu;
                                                            v1 = lb(s1, 1);
                                                            v0 = sll(v1, 3);
                                                            v0 = subu(v0, v1);
                                                            v1 = sll(v0, 6);
                                                            v0 = lui(0x87u);
                                                            v0 = addiu(v0, -4620);  // 0x86EDF4
                                                            v0 = addu(v0, v1);
                                                            v0 = lw(v0, 0);
                                                            a0 = addiu(sp, 368);
                                                            a1 = lw(v0, kResController);
                                                            jal(0x44C39Cu, &gen::fn_sub_1AD940_001ad940);
                                                            a0 = addiu(sp, 368);
                                                            jal(0x44C3A8u, &gen::fn_sub_44F170_0044f170);
                                                            a2 = v0 & 0xFFFFu;
                                                            a0 = addiu(sp, 400);
                                                            a1 = s0;
                                                            jal(0x44C3BCu, &gen::fn_sub_1BF220_001bf220);
                                                            lwc1(2, sp, 400);
                                                            lwc1(1, sp, 404);
                                                            lwc1(0, sp, 408);
                                                            swc1(2, s1, 108);
                                                            swc1(1, s1, 112);
                                                            swc1(0, s1, 116);
                                                            v1 = si(15);
                                                            sb(s1, 3, v1);
                                                            charge(10);
                                                            ra = ld(sp, 96);
                                                            lq(s5, sp, 80);
                                                            lq(s4, sp, 64);
                                                            lq(s3, sp, 48);
                                                            lq(s2, sp, 32);
                                                            lq(s1, sp, 16);
                                                            lq(s0, sp, 0);
                                                            sp = addiu(sp, 448);
                                                            return;
                                                        }
                                                        charge(49);
                                                        v1 = lb(s1, 1);
                                                        v0 = sll(v1, 3);
                                                        v0 = subu(v0, v1);
                                                        v1 = sll(v0, 6);
                                                        v0 = lui(0x87u);
                                                        v0 = addiu(v0, -4620);  // 0x86EDF4
                                                        v0 = addu(v0, v1);
                                                        v0 = lw(v0, 0);
                                                        a0 = lw(v0, kResController);
                                                        jal(0x44C410u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                                                        s2 = dsll32(v0, 24);
                                                        s2 = dsra32(s2, 24);
                                                        v1 = lb(s1, 1);
                                                        v0 = sll(v1, 3);
                                                        v0 = subu(v0, v1);
                                                        v1 = sll(v0, 6);
                                                        v0 = lui(0x87u);
                                                        v0 = addiu(v0, -4620);  // 0x86EDF4
                                                        v0 = addu(v0, v1);
                                                        v0 = lw(v0, 0);
                                                        a0 = lw(v0, kResController);
                                                        jal(0x44C444u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                                                        s0 = dsll32(v0, 24);
                                                        s0 = dsra32(s0, 24);
                                                        v1 = lb(s1, 1);
                                                        v0 = sll(v1, 3);
                                                        v0 = subu(v0, v1);
                                                        v1 = sll(v0, 6);
                                                        v0 = lui(0x87u);
                                                        v0 = addiu(v0, -4620);  // 0x86EDF4
                                                        v0 = addu(v0, v1);
                                                        v0 = lw(v0, 0);
                                                        a0 = addiu(sp, 352);
                                                        a1 = lw(v0, kResController);
                                                        jal(0x44C47Cu, &gen::fn_sub_1AD940_001ad940);
                                                        a4 = lb(s1, 139);
                                                        a5 = lb(s1, 140);
                                                        a0 = lb(s1, 1);
                                                        a1 = s2;
                                                        a2 = s0;
                                                        a3 = addiu(sp, 352);
                                                        jal(0x44C49Cu, &gen::fn_sub_453ED0_00453ed0);
                                                        v1 = si(1);
                                                        if (v0 == v1) {
                                                            charge(4);
                                                            v1 = si(13);
                                                            sb(s1, 3, v1);
                                                            charge(10);
                                                            ra = ld(sp, 96);
                                                            lq(s5, sp, 80);
                                                            lq(s4, sp, 64);
                                                            lq(s3, sp, 48);
                                                            lq(s2, sp, 32);
                                                            lq(s1, sp, 16);
                                                            lq(s0, sp, 0);
                                                            sp = addiu(sp, 448);
                                                            return;
                                                        }
                                                        charge(4);
                                                        v1 = si(15);
                                                        sb(s1, 3, v1);
                                                        charge(10);
                                                        ra = ld(sp, 96);
                                                        lq(s5, sp, 80);
                                                        lq(s4, sp, 64);
                                                        lq(s3, sp, 48);
                                                        lq(s2, sp, 32);
                                                        lq(s1, sp, 16);
                                                        lq(s0, sp, 0);
                                                        sp = addiu(sp, 448);
                                                        return;
                                                    }
                                                    charge(3);
                                                    v1 = lw(s1, 148);
                                                    if (v1 != 0) {
                                                        charge(44);
                                                        v0 = addiu(v1, -1);
                                                        sw(s1, 148, v0);
                                                        v0 = sll(v0, 2);
                                                        v0 = addu(v0, s1);
                                                        v0 = lh(v0, 3224);
                                                        mtc1(v0, 0);
                                                        cvt_s_w(0, 0);
                                                        v0 = lui(0x4448u);
                                                        mtc1(v0, 1);  // 800.0
                                                        mul_s(0, 1, 0);
                                                        swc1(0, s1, 108);
                                                        v0 = lw(s1, 148);
                                                        v0 = sll(v0, 2);
                                                        v0 = addu(v0, s1);
                                                        v0 = lh(v0, 3226);
                                                        mtc1(v0, 0);
                                                        cvt_s_w(0, 0);
                                                        mul_s(0, 1, 0);
                                                        swc1(0, s1, 116);
                                                        a0 = addiu(s1, 108);
                                                        jal(0x44C538u, &gen::fn_sub_44F120_0044f120);
                                                        s0 = v0 & 0xFFFFu;
                                                        a0 = addiu(s1, 108);
                                                        jal(0x44C548u, &gen::fn_sub_44F170_0044f170);
                                                        a2 = v0 & 0xFFFFu;
                                                        a0 = addiu(sp, 336);
                                                        a1 = s0;
                                                        jal(0x44C55Cu, &gen::fn_sub_1BF220_001bf220);
                                                        lwc1(2, sp, 336);
                                                        lwc1(1, sp, 340);
                                                        lwc1(0, sp, 344);
                                                        swc1(2, s1, 108);
                                                        swc1(1, s1, 112);
                                                        swc1(0, s1, 116);
                                                        v1 = si(14);
                                                        sb(s1, 3, v1);
                                                        charge(10);
                                                        ra = ld(sp, 96);
                                                        lq(s5, sp, 80);
                                                        lq(s4, sp, 64);
                                                        lq(s3, sp, 48);
                                                        lq(s2, sp, 32);
                                                        lq(s1, sp, 16);
                                                        lq(s0, sp, 0);
                                                        sp = addiu(sp, 448);
                                                        return;
                                                    }
                                                    charge(3);
                                                    sb(s1, 3, a3);
                                                    charge(10);
                                                    ra = ld(sp, 96);
                                                    lq(s5, sp, 80);
                                                    lq(s4, sp, 64);
                                                    lq(s3, sp, 48);
                                                    lq(s2, sp, 32);
                                                    lq(s1, sp, 16);
                                                    lq(s0, sp, 0);
                                                    sp = addiu(sp, 448);
                                                    return;
                                                }
                                                charge(21);
                                                v0 = lui(0x87u);
                                                v0 = addiu(v0, -4336);  // 0x86EF10
                                                v0 = addu(v0, a2);
                                                a0 = lw(v0, 0);
                                                a1 = 0;
                                                jal(0x44C5ACu, &gen::fn_sub_1B0250_001b0250);
                                                v1 = lb(s1, 1);
                                                v0 = sll(v1, 3);
                                                v0 = subu(v0, v1);
                                                v1 = sll(v0, 6);
                                                v0 = lui(0x87u);
                                                v0 = addiu(v0, -4336);  // 0x86EF10
                                                v0 = addu(v0, v1);
                                                a0 = lw(v0, 0);
                                                a1 = addiu(s1, 108);
                                                lwc1(12, s0, 12);
                                                jal(0x44C5DCu, &gen::fn_sub_1AFA20_001afa20);
                                                if (v0 == 0) {
                                                    charge(10);
                                                    ra = ld(sp, 96);
                                                    lq(s5, sp, 80);
                                                    lq(s4, sp, 64);
                                                    lq(s3, sp, 48);
                                                    lq(s2, sp, 32);
                                                    lq(s1, sp, 16);
                                                    lq(s0, sp, 0);
                                                    sp = addiu(sp, 448);
                                                    return;
                                                }
                                                charge(16);
                                                lwc1(2, s1, 108);
                                                lwc1(1, s1, 112);
                                                lwc1(0, s1, 116);
                                                swc1(2, s1, 96);
                                                swc1(1, s1, 100);
                                                swc1(0, s1, 104);
                                                lwc1(2, s1, 108);
                                                lwc1(1, s1, 112);
                                                lwc1(0, s1, 116);
                                                swc1(2, s1, 80);
                                                swc1(1, s1, 84);
                                                swc1(0, s1, 88);
                                                v1 = si(13);
                                                sb(s1, 3, v1);
                                                charge(10);
                                                ra = ld(sp, 96);
                                                lq(s5, sp, 80);
                                                lq(s4, sp, 64);
                                                lq(s3, sp, 48);
                                                lq(s2, sp, 32);
                                                lq(s1, sp, 16);
                                                lq(s0, sp, 0);
                                                sp = addiu(sp, 448);
                                                return;
                                            }
                                            charge(8);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, -4336);  // 0x86EF10
                                            v0 = addu(v0, a2);
                                            a0 = lw(v0, 0);
                                            jal(0x44C63Cu, &gen::fn_sub_1B0220_001b0220);
                                            if (v0 != 0) {
                                                charge(10);
                                                ra = ld(sp, 96);
                                                lq(s5, sp, 80);
                                                lq(s4, sp, 64);
                                                lq(s3, sp, 48);
                                                lq(s2, sp, 32);
                                                lq(s1, sp, 16);
                                                lq(s0, sp, 0);
                                                sp = addiu(sp, 448);
                                                return;
                                            }
                                            charge(13);
                                            v0 = si(16);
                                            sb(s1, 3, v0);
                                            a1 = 0;
                                            v1 = lb(s1, 1);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            a0 = sll(v0, 6);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, -4632);  // 0x86EDE8
                                            v0 = addu(v0, a0);
                                            v0 = lw(v0, 0);
                                            if (v0 != 0) {
                                                charge(6);
                                                v0 = lui(0x87u);
                                                v0 = addiu(v0, -4620);  // 0x86EDF4
                                                v0 = addu(v0, a0);
                                                v0 = lw(v0, 0);
                                                if (v0 != 0) {
                                                    charge(1);
                                                    a1 = si(1);
                                                }
                                            }
                                            charge(4);
                                            v1 = sltu(zero, a1);
                                            v0 = si(1);
                                            if (v1 == v0) {
                                                charge(28);
                                                v0 = lui(0x87u);
                                                v0 = addiu(v0, -4296);  // 0x86EF38
                                                v0 = addu(v0, a0);
                                                sb(v0, 0, zero);
                                                v1 = lb(s1, 1);
                                                v0 = sll(v1, 3);
                                                v0 = subu(v0, v1);
                                                v1 = sll(v0, 6);
                                                v0 = lui(0x87u);
                                                v0 = addiu(v0, -4295);  // 0x86EF39
                                                v0 = addu(v0, v1);
                                                sb(v0, 0, zero);
                                                v1 = lb(s1, 1);
                                                v0 = sll(v1, 3);
                                                v0 = subu(v0, v1);
                                                v1 = sll(v0, 6);
                                                v0 = lui(0x87u);
                                                v0 = addiu(v0, -4294);  // 0x86EF3A
                                                v0 = addu(v0, v1);
                                                sb(v0, 0, zero);
                                                v1 = lb(s1, 1);
                                                v0 = sll(v1, 3);
                                                v0 = subu(v0, v1);
                                                v1 = sll(v0, 6);
                                                v0 = lui(0x87u);
                                                v0 = addiu(v0, -4293);  // 0x86EF3B
                                                v0 = addu(v0, v1);
                                                sb(v0, 0, zero);
                                            }
                                            charge(5);
                                            a0 = lb(s1, 1);
                                            jal(0x44C720u, &gen::fn_Y_Stratum_CreateEneDeadEffectTask_004542c0);
                                            charge(10);
                                            ra = ld(sp, 96);
                                            lq(s5, sp, 80);
                                            lq(s4, sp, 64);
                                            lq(s3, sp, 48);
                                            lq(s2, sp, 32);
                                            lq(s1, sp, 16);
                                            lq(s0, sp, 0);
                                            sp = addiu(sp, 448);
                                            return;
                                        }
                                        charge(5);
                                        a0 = s2;
                                        jal(0x44C734u, &gen::fn_sub_451D70_00451d70);
                                        charge(10);
                                        ra = ld(sp, 96);
                                        lq(s5, sp, 80);
                                        lq(s4, sp, 64);
                                        lq(s3, sp, 48);
                                        lq(s2, sp, 32);
                                        lq(s1, sp, 16);
                                        lq(s0, sp, 0);
                                        sp = addiu(sp, 448);
                                        return;
                                    }
                                    charge(3);
                                    s3 = 0;
                                    for (;;) {
                                        charge(3);
                                        v0 = slti(s3, 4);
                                        if (v0 == 0) break;
                                        backedge();
                                        charge(10);
                                        a0 = 0;
                                        v0 = sll(s3, 3);
                                        v0 = subu(v0, s3);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, 6048);  // 0x8717A0 gFldUnitsPc
                                        v1 = addu(v0, v1);
                                        v0 = lw(v1, 72);
                                        if (v0 != 0) {
                                            charge(3);
                                            v0 = lw(v1, 84);
                                            if (v0 != 0) {
                                                charge(1);
                                                a0 = si(1);
                                            }
                                        }
                                        charge(4);
                                        v1 = sltu(zero, a0);
                                        v0 = si(1);
                                        if (v1 == v0) {
                                            charge(7);
                                            a0 = dsll32(s3, 24);
                                            a0 = dsra32(a0, 24);
                                            jal(0x44C7A0u, &gen::fn_sub_43C910_0043c910);
                                            v0 = v0 & 0xFFFFu;
                                            if (gtz(v0)) {
                                                charge(1);
                                                sb(s1, 24, s3);
                                            }
                                        }
                                        charge(1);
                                        s3 = addiu(s3, 1);
                                    }
                                    charge(30);
                                    v1 = lb(s1, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4336);  // 0x86EF10
                                    v0 = addu(v0, v1);
                                    a0 = lw(v0, 0);
                                    jal(0x44C7E8u, &gen::fn_sub_1B00C0_001b00c0);
                                    v1 = lb(s1, 24);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, 6132);  // 0x8717F4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = addiu(sp, 320);
                                    a1 = lw(v0, kResController);
                                    jal(0x44C818u, &gen::fn_sub_1AD940_001ad940);
                                    lwc1(2, sp, 320);
                                    lwc1(1, sp, 324);
                                    lwc1(0, sp, 328);
                                    swc1(2, s1, 28);
                                    swc1(1, s1, 32);
                                    swc1(0, s1, 36);
                                    v0 = si(19);
                                    sb(s1, 3, v0);
                                }
                                charge(7);
                                a0 = s2;
                                a1 = lb(s1, 1);
                                jal(0x44C848u, &gen::fn_sub_4523C0_004523c0);
                                v1 = si(1);
                                if (v0 != v1) {
                                    charge(40);
                                    v1 = lb(s1, 24);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, 6132);  // 0x8717F4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = lw(v0, kResController);
                                    jal(0x44C880u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                                    s5 = dsll32(v0, 16);
                                    s5 = dsra32(s5, 16);
                                    v1 = lb(s1, 24);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, 6132);  // 0x8717F4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = lw(v0, kResController);
                                    jal(0x44C8B4u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                                    s4 = dsll32(v0, 16);
                                    s4 = dsra32(s4, 16);
                                    jal(0x44C8C4u, &gen::fn_K_Field_Get_001b9120);
                                    v1 = dsll32(s4, 16);
                                    v1 = dsra32(v1, 16);
                                    v1 = sll(v1, 8);
                                    v1 = addu(v0, v1);
                                    v0 = dsll32(s5, 16);
                                    v0 = dsra32(v0, 16);
                                    v0 = sll(v0, 4);
                                    v0 = addu(v1, v0);
                                    v1 = lbu(v0, 74);
                                    v0 = si(8);
                                    if (v1 == v0) {
                                        charge(86);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4336);  // 0x86EF10
                                        v0 = addu(v0, v1);
                                        a0 = lw(v0, 0);
                                        jal(0x44C91Cu, &gen::fn_sub_1B00C0_001b00c0);
                                        v1 = lb(s1, 24);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, 6132);  // 0x8717F4
                                        v0 = addu(v0, v1);
                                        v0 = lw(v0, 0);
                                        a0 = addiu(sp, 304);
                                        a1 = lw(v0, kResController);
                                        jal(0x44C94Cu, &gen::fn_sub_1AD940_001ad940);
                                        lwc1(2, sp, 304);
                                        lwc1(1, sp, 308);
                                        lwc1(0, sp, 312);
                                        swc1(2, s1, 28);
                                        swc1(1, s1, 32);
                                        swc1(0, s1, 36);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4620);  // 0x86EDF4
                                        v0 = addu(v0, v1);
                                        v0 = lw(v0, 0);
                                        a0 = lw(v0, kResController);
                                        jal(0x44C990u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                                        s2 = dsll32(v0, 24);
                                        s2 = dsra32(s2, 24);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4620);  // 0x86EDF4
                                        v0 = addu(v0, v1);
                                        v0 = lw(v0, 0);
                                        a0 = lw(v0, kResController);
                                        jal(0x44C9C4u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                                        s0 = dsll32(v0, 24);
                                        s0 = dsra32(s0, 24);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4620);  // 0x86EDF4
                                        v0 = addu(v0, v1);
                                        v0 = lw(v0, 0);
                                        a0 = addiu(sp, 288);
                                        a1 = lw(v0, kResController);
                                        jal(0x44C9FCu, &gen::fn_sub_1AD940_001ad940);
                                        a0 = addiu(s1, 40);
                                        jal(0x44CA08u, &gen::fn_sub_44F120_0044f120);
                                        s3 = dsll32(v0, 24);
                                        s3 = dsra32(s3, 24);
                                        a0 = addiu(s1, 40);
                                        jal(0x44CA1Cu, &gen::fn_sub_44F170_0044f170);
                                        a5 = dsll32(v0, 24);
                                        a5 = dsra32(a5, 24);
                                        a0 = lb(s1, 1);
                                        a1 = s2;
                                        a2 = s0;
                                        a3 = addiu(sp, 288);
                                        a4 = s3;
                                        jal(0x44CA40u, &gen::fn_sub_453ED0_00453ed0);
                                        v1 = si(1);
                                        if (v0 == v1) {
                                            charge(15);
                                            v1 = lb(s1, 1);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, -4336);  // 0x86EF10
                                            v0 = addu(v0, v1);
                                            a0 = lw(v0, 0);
                                            a1 = 0;
                                            jal(0x44CA78u, &gen::fn_sub_1B0240_001b0240);
                                            v1 = si(20);
                                            sb(s1, 3, v1);
                                        } else {
                                            charge(4);
                                            v1 = si(18);
                                            sb(s1, 3, v1);
                                        }
                                    } else {
                                        charge(51);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4620);  // 0x86EDF4
                                        v0 = addu(v0, v1);
                                        v0 = lw(v0, 0);
                                        a0 = lw(v0, kResController);
                                        jal(0x44CAC4u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                                        s3 = dsll32(v0, 24);
                                        s3 = dsra32(s3, 24);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4620);  // 0x86EDF4
                                        v0 = addu(v0, v1);
                                        v0 = lw(v0, 0);
                                        a0 = lw(v0, kResController);
                                        jal(0x44CAF8u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                                        s2 = dsll32(v0, 24);
                                        s2 = dsra32(s2, 24);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4620);  // 0x86EDF4
                                        v0 = addu(v0, v1);
                                        v0 = lw(v0, 0);
                                        a0 = addiu(sp, 272);
                                        a1 = lw(v0, kResController);
                                        jal(0x44CB30u, &gen::fn_sub_1AD940_001ad940);
                                        a4 = dsll32(s5, 24);
                                        a4 = dsra32(a4, 24);
                                        a5 = dsll32(s4, 24);
                                        a5 = dsra32(a5, 24);
                                        a0 = lb(s1, 1);
                                        a1 = s3;
                                        a2 = s2;
                                        a3 = addiu(sp, 272);
                                        jal(0x44CB58u, &gen::fn_sub_453ED0_00453ed0);
                                        v1 = si(1);
                                        if (v0 == v1) {
                                            charge(15);
                                            v1 = lb(s1, 1);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, -4336);  // 0x86EF10
                                            v0 = addu(v0, v1);
                                            a0 = lw(v0, 0);
                                            a1 = 0;
                                            jal(0x44CB90u, &gen::fn_sub_1B0240_001b0240);
                                            v1 = si(20);
                                            sb(s1, 3, v1);
                                        } else {
                                            charge(27);
                                            v1 = lb(s1, 24);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, 6132);  // 0x8717F4
                                            v0 = addu(v0, v1);
                                            v0 = lw(v0, 0);
                                            a0 = addiu(sp, 256);
                                            a1 = lw(v0, kResController);
                                            jal(0x44CBD0u, &gen::fn_sub_1AD940_001ad940);
                                            v1 = lb(s1, 1);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, -4336);  // 0x86EF10
                                            v0 = addu(v0, v1);
                                            a0 = lw(v0, 0);
                                            a1 = addiu(sp, 256);
                                            lwc1(12, s0, 12);
                                            jal(0x44CC00u, &gen::fn_sub_1AFA20_001afa20);
                                            v1 = si(1);
                                            if (v0 == v1) {
                                                charge(4);
                                                v1 = si(22);
                                                sb(s1, 3, v1);
                                            }
                                        }
                                    }
                                }
                            } else {
                                charge(6);
                                a0 = s2;
                                jal(0x44CC28u, &gen::fn_sub_4523C0_004523c0);
                                v1 = si(1);
                                if (v0 != v1) {
                                    charge(7);
                                    a0 = lb(s1, 1);
                                    a1 = lb(s1, 24);
                                    jal(0x44CC44u, &gen::fn_sub_452A70_00452a70);
                                    v1 = si(1);
                                    if (v0 != v1) {
                                        charge(3);
                                        v1 = lw(s1, 148);
                                        if (v1 != 0) {
                                            charge(44);
                                            v0 = addiu(v1, -1);
                                            sw(s1, 148, v0);
                                            v0 = sll(v0, 2);
                                            v0 = addu(v0, s1);
                                            v0 = lh(v0, 3224);
                                            mtc1(v0, 0);
                                            cvt_s_w(0, 0);
                                            v0 = lui(0x4448u);
                                            mtc1(v0, 1);  // 800.0
                                            mul_s(0, 1, 0);
                                            swc1(0, s1, 108);
                                            v0 = lw(s1, 148);
                                            v0 = sll(v0, 2);
                                            v0 = addu(v0, s1);
                                            v0 = lh(v0, 3226);
                                            mtc1(v0, 0);
                                            cvt_s_w(0, 0);
                                            mul_s(0, 1, 0);
                                            swc1(0, s1, 116);
                                            a0 = addiu(s1, 108);
                                            jal(0x44CCC0u, &gen::fn_sub_44F120_0044f120);
                                            s0 = v0 & 0xFFFFu;
                                            a0 = addiu(s1, 108);
                                            jal(0x44CCD0u, &gen::fn_sub_44F170_0044f170);
                                            a2 = v0 & 0xFFFFu;
                                            a0 = addiu(sp, 240);
                                            a1 = s0;
                                            jal(0x44CCE4u, &gen::fn_sub_1BF220_001bf220);
                                            lwc1(2, sp, 240);
                                            lwc1(1, sp, 244);
                                            lwc1(0, sp, 248);
                                            swc1(2, s1, 108);
                                            swc1(1, s1, 112);
                                            swc1(0, s1, 116);
                                            v1 = si(21);
                                            sb(s1, 3, v1);
                                        } else {
                                            charge(4);
                                            v1 = si(22);
                                            sb(s1, 3, v1);
                                        }
                                    }
                                }
                            }
                        } else {
                            charge(6);
                            a0 = s2;
                            jal(0x44CD28u, &gen::fn_sub_4523C0_004523c0);
                            v1 = si(1);
                            if (v0 != v1) {
                                charge(7);
                                a0 = lb(s1, 1);
                                a1 = lb(s1, 24);
                                jal(0x44CD44u, &gen::fn_sub_452A70_00452a70);
                                v1 = si(1);
                                if (v0 != v1) {
                                    charge(32);
                                    v1 = lb(s1, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4620);  // 0x86EDF4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = addiu(sp, 224);
                                    a1 = lw(v0, kResController);
                                    jal(0x44CD80u, &gen::fn_sub_1AD940_001ad940);
                                    v1 = lb(s1, 24);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, 6132);  // 0x8717F4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = addiu(sp, 208);
                                    a1 = lw(v0, kResController);
                                    jal(0x44CDB0u, &gen::fn_sub_1AD940_001ad940);
                                    a0 = addiu(sp, 224);
                                    a1 = addiu(sp, 208);
                                    lwc1(12, s0, 4);
                                    jal(0x44CDC4u, &gen::fn_sub_44F1C0_0044f1c0);
                                    v1 = si(1);
                                    if (v0 == v1) {
                                        charge(33);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4620);  // 0x86EDF4
                                        v0 = addu(v0, v1);
                                        v0 = lw(v0, 0);
                                        a0 = lw(v0, 296);
                                        jal(0x44CDFCu, &gen::fn_sub_318B60_00318b60);
                                        s2 = v0;
                                        v1 = lb(s1, 24);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, 6132);  // 0x8717F4
                                        v0 = addu(v0, v1);
                                        v0 = lw(v0, 0);
                                        a0 = addiu(sp, 192);
                                        a1 = lw(v0, kResController);
                                        jal(0x44CE30u, &gen::fn_sub_1AD940_001ad940);
                                        a0 = s2;
                                        a1 = addiu(sp, 192);
                                        lwc1(12, s0, 16);
                                        lwc1(13, s0, 20);
                                        jal(0x44CE48u, &gen::fn_sub_1C6450_001c6450);
                                        v1 = si(1);
                                        if (v0 == v1) {
                                            charge(26);
                                            a0 = lb(s1, 1);
                                            a1 = si(5);
                                            jal(0x44CE64u, &gen::fn_sub_4543C0_004543c0);
                                            a0 = si(1);
                                            v1 = lb(s1, 1);
                                            v0 = lui(0x96u);
                                            v0 = addiu(v0, -15856);  // 0x95C210
                                            v0 = addu(v0, v1);
                                            sb(v0, 0, a0);
                                            v1 = lb(s1, 1);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, -4336);  // 0x86EF10
                                            v0 = addu(v0, v1);
                                            a0 = lw(v0, 0);
                                            jal(0x44CEA4u, &gen::fn_sub_1B00C0_001b00c0);
                                            a0 = lw(s1, 16);
                                            a1 = si(1);
                                            jal(0x44CEB4u, &gen::fn_sub_1AAAC0_001aaac0);
                                            charge(10);
                                            ra = ld(sp, 96);
                                            lq(s5, sp, 80);
                                            lq(s4, sp, 64);
                                            lq(s3, sp, 48);
                                            lq(s2, sp, 32);
                                            lq(s1, sp, 16);
                                            lq(s0, sp, 0);
                                            sp = addiu(sp, 448);
                                            return;
                                        }
                                    }
                                    charge(25);
                                    v1 = lb(s1, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4620);  // 0x86EDF4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = lw(v0, kResController);
                                    jal(0x44CEE8u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                                    s2 = v0;
                                    v1 = lb(s1, 24);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, 6132);  // 0x8717F4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = lw(v0, kResController);
                                    jal(0x44CF18u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                                    if (s2 == v0) {
                                        charge(25);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4620);  // 0x86EDF4
                                        v0 = addu(v0, v1);
                                        v0 = lw(v0, 0);
                                        a0 = lw(v0, kResController);
                                        jal(0x44CF4Cu, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                                        s2 = v0;
                                        v1 = lb(s1, 24);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, 6132);  // 0x8717F4
                                        v0 = addu(v0, v1);
                                        v0 = lw(v0, 0);
                                        a0 = lw(v0, kResController);
                                        jal(0x44CF7Cu, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                                        if (s2 == v0) {
                                            charge(49);
                                            v1 = lb(s1, 1);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, -4336);  // 0x86EF10
                                            v0 = addu(v0, v1);
                                            a0 = lw(v0, 0);
                                            jal(0x44CFACu, &gen::fn_sub_1B00C0_001b00c0);
                                            v1 = lb(s1, 24);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, 6132);  // 0x8717F4
                                            v0 = addu(v0, v1);
                                            v0 = lw(v0, 0);
                                            a0 = addiu(sp, 176);
                                            a1 = lw(v0, kResController);
                                            jal(0x44CFDCu, &gen::fn_sub_1AD940_001ad940);
                                            v1 = lb(s1, 1);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, -4336);  // 0x86EF10
                                            v0 = addu(v0, v1);
                                            a0 = lw(v0, 0);
                                            a1 = addiu(sp, 176);
                                            lwc1(12, s0, 12);
                                            jal(0x44D00Cu, &gen::fn_sub_1AFA20_001afa20);
                                            v1 = lb(s1, 1);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, -4336);  // 0x86EF10
                                            v0 = addu(v0, v1);
                                            a0 = lw(v0, 0);
                                            a1 = 0;
                                            jal(0x44D038u, &gen::fn_sub_1B0240_001b0240);
                                            v1 = si(22);
                                            sb(s1, 3, v1);
                                            charge(10);
                                            ra = ld(sp, 96);
                                            lq(s5, sp, 80);
                                            lq(s4, sp, 64);
                                            lq(s3, sp, 48);
                                            lq(s2, sp, 32);
                                            lq(s1, sp, 16);
                                            lq(s0, sp, 0);
                                            sp = addiu(sp, 448);
                                            return;
                                        }
                                    }
                                    charge(25);
                                    v1 = lb(s1, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4336);  // 0x86EF10
                                    v0 = addu(v0, v1);
                                    a0 = lw(v0, 0);
                                    a1 = 0;
                                    jal(0x44D074u, &gen::fn_sub_1B0250_001b0250);
                                    v1 = lb(s1, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4336);  // 0x86EF10
                                    v0 = addu(v0, v1);
                                    a0 = lw(v0, 0);
                                    a1 = addiu(s1, 108);
                                    lwc1(12, s0, 12);
                                    jal(0x44D0A4u, &gen::fn_sub_1AFA20_001afa20);
                                    if (v0 != 0) {
                                        charge(16);
                                        lwc1(2, s1, 108);
                                        lwc1(1, s1, 112);
                                        lwc1(0, s1, 116);
                                        swc1(2, s1, 96);
                                        swc1(1, s1, 100);
                                        swc1(0, s1, 104);
                                        lwc1(2, s1, 108);
                                        lwc1(1, s1, 112);
                                        lwc1(0, s1, 116);
                                        swc1(2, s1, 80);
                                        swc1(1, s1, 84);
                                        swc1(0, s1, 88);
                                        v1 = si(20);
                                        sb(s1, 3, v1);
                                    }
                                }
                            }
                        }
                    } else {
                        charge(6);
                        a0 = s2;
                        jal(0x44D0F8u, &gen::fn_sub_4523C0_004523c0);
                        v1 = si(1);
                        if (v0 != v1) {
                            charge(7);
                            a0 = lb(s1, 1);
                            a1 = lb(s1, 24);
                            jal(0x44D114u, &gen::fn_sub_452A70_00452a70);
                            v1 = si(1);
                            if (v0 != v1) {
                                charge(32);
                                v1 = lb(s1, 1);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, -4620);  // 0x86EDF4
                                v0 = addu(v0, v1);
                                v0 = lw(v0, 0);
                                a0 = addiu(sp, 160);
                                a1 = lw(v0, kResController);
                                jal(0x44D150u, &gen::fn_sub_1AD940_001ad940);
                                v1 = lb(s1, 24);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, 6132);  // 0x8717F4
                                v0 = addu(v0, v1);
                                v0 = lw(v0, 0);
                                a0 = addiu(sp, 144);
                                a1 = lw(v0, kResController);
                                jal(0x44D180u, &gen::fn_sub_1AD940_001ad940);
                                a0 = addiu(sp, 160);
                                a1 = addiu(sp, 144);
                                lwc1(12, s0, 4);
                                jal(0x44D194u, &gen::fn_sub_44F1C0_0044f1c0);
                                v1 = si(1);
                                if (v0 == v1) {
                                    charge(33);
                                    v1 = lb(s1, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4620);  // 0x86EDF4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = lw(v0, 296);
                                    jal(0x44D1CCu, &gen::fn_sub_318B60_00318b60);
                                    s2 = v0;
                                    v1 = lb(s1, 24);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, 6132);  // 0x8717F4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = addiu(sp, 128);
                                    a1 = lw(v0, kResController);
                                    jal(0x44D200u, &gen::fn_sub_1AD940_001ad940);
                                    a0 = s2;
                                    a1 = addiu(sp, 128);
                                    lwc1(12, s0, 16);
                                    lwc1(13, s0, 20);
                                    jal(0x44D218u, &gen::fn_sub_1C6450_001c6450);
                                    v1 = si(1);
                                    if (v0 != v1) {
                                        goto L_0044d510;
                                    }
                                    charge(26);
                                    a0 = lb(s1, 1);
                                    a1 = si(5);
                                    jal(0x44D234u, &gen::fn_sub_4543C0_004543c0);
                                    a0 = si(1);
                                    v1 = lb(s1, 1);
                                    v0 = lui(0x96u);
                                    v0 = addiu(v0, -15856);  // 0x95C210
                                    v0 = addu(v0, v1);
                                    sb(v0, 0, a0);
                                    v1 = lb(s1, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4336);  // 0x86EF10
                                    v0 = addu(v0, v1);
                                    a0 = lw(v0, 0);
                                    jal(0x44D274u, &gen::fn_sub_1B00C0_001b00c0);
                                    a0 = lw(s1, 16);
                                    a1 = si(1);
                                    jal(0x44D284u, &gen::fn_sub_1AAAC0_001aaac0);
                                    charge(10);
                                    ra = ld(sp, 96);
                                    lq(s5, sp, 80);
                                    lq(s4, sp, 64);
                                    lq(s3, sp, 48);
                                    lq(s2, sp, 32);
                                    lq(s1, sp, 16);
                                    lq(s0, sp, 0);
                                    sp = addiu(sp, 448);
                                    return;
                                }
                                charge(12);
                                v1 = lb(s1, 1);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, -4336);  // 0x86EF10
                                v0 = addu(v0, v1);
                                a0 = lw(v0, 0);
                                jal(0x44D2B4u, &gen::fn_sub_1B0220_001b0220);
                                if (v0 == 0) {
                                    charge(25);
                                    v1 = lb(s1, 1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -4620);  // 0x86EDF4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = lw(v0, kResController);
                                    jal(0x44D2E8u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                                    s3 = v0;
                                    v1 = lb(s1, 24);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, 6132);  // 0x8717F4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = lw(v0, kResController);
                                    jal(0x44D318u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                                    if (s3 == v0) {
                                        charge(25);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4620);  // 0x86EDF4
                                        v0 = addu(v0, v1);
                                        v0 = lw(v0, 0);
                                        a0 = lw(v0, kResController);
                                        jal(0x44D34Cu, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                                        s3 = v0;
                                        v1 = lb(s1, 24);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, 6132);  // 0x8717F4
                                        v0 = addu(v0, v1);
                                        v0 = lw(v0, 0);
                                        a0 = lw(v0, kResController);
                                        jal(0x44D37Cu, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                                        if (s3 == v0) {
                                            charge(37);
                                            v1 = lb(s1, 1);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, -4336);  // 0x86EF10
                                            v0 = addu(v0, v1);
                                            a0 = lw(v0, 0);
                                            a1 = 0;
                                            jal(0x44D3B0u, &gen::fn_sub_1B0240_001b0240);
                                            v1 = lb(s1, 24);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, 6132);  // 0x8717F4
                                            v0 = addu(v0, v1);
                                            v0 = lw(v0, 0);
                                            a0 = addiu(sp, 112);
                                            a1 = lw(v0, kResController);
                                            jal(0x44D3E0u, &gen::fn_sub_1AD940_001ad940);
                                            v1 = lb(s1, 1);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = lui(0x87u);
                                            v0 = addiu(v0, -4336);  // 0x86EF10
                                            v0 = addu(v0, v1);
                                            a0 = lw(v0, 0);
                                            a1 = addiu(sp, 112);
                                            lwc1(12, s0, 12);
                                            jal(0x44D410u, &gen::fn_sub_1AFA20_001afa20);
                                            if (v0 != 0) {
                                                goto L_0044d510;
                                            }
                                            charge(2);
                                            charge(10);
                                            ra = ld(sp, 96);
                                            lq(s5, sp, 80);
                                            lq(s4, sp, 64);
                                            lq(s3, sp, 48);
                                            lq(s2, sp, 32);
                                            lq(s1, sp, 16);
                                            lq(s0, sp, 0);
                                            sp = addiu(sp, 448);
                                            return;
                                        }
                                    }
                                    charge(32);
                                    v1 = lb(s1, 24);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, 6132);  // 0x8717F4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = lw(v0, kResController);
                                    jal(0x44D44Cu, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                                    s0 = sll(v0, 8);
                                    jal(0x44D458u, &gen::fn_K_Field_Get_001b9120);
                                    s0 = addu(v0, s0);
                                    v1 = lb(s1, 24);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 6);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, 6132);  // 0x8717F4
                                    v0 = addu(v0, v1);
                                    v0 = lw(v0, 0);
                                    a0 = lw(v0, kResController);
                                    jal(0x44D488u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                                    v0 = sll(v0, 4);
                                    v0 = addu(s0, v0);
                                    v1 = lbu(v0, 74);
                                    v0 = si(8);
                                    if (v1 == v0) {
                                        charge(15);
                                        v1 = lb(s1, 1);
                                        v0 = sll(v1, 3);
                                        v0 = subu(v0, v1);
                                        v1 = sll(v0, 6);
                                        v0 = lui(0x87u);
                                        v0 = addiu(v0, -4336);  // 0x86EF10
                                        v0 = addu(v0, v1);
                                        a0 = lw(v0, 0);
                                        a1 = addiu(s1, 52);
                                        a2 = si(5);
                                        jal(0x44D4D0u, &gen::fn_sub_1B0020_001b0020);
                                        v0 = lw(s1, 20);
                                        if (v0 != 0) {
                                            charge(1);
                                            sw(s1, 20, zero);
                                        }
                                        charge(10);
                                        a0 = s2;
                                        a1 = si(5);
                                        a2 = 0;
                                        jal(0x44D4F4u, &gen::fn_Y_Kyoto_CreateWaitTask_00459f60);
                                        sw(s1, 20, v0);
                                        v1 = si(23);
                                        sb(s1, 3, v1);
                                        charge(10);
                                        ra = ld(sp, 96);
                                        lq(s5, sp, 80);
                                        lq(s4, sp, 64);
                                        lq(s3, sp, 48);
                                        lq(s2, sp, 32);
                                        lq(s1, sp, 16);
                                        lq(s0, sp, 0);
                                        sp = addiu(sp, 448);
                                        return;
                                    }
                                }
                              L_0044d510:
                                charge(12);
                                v1 = lb(s1, 1);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, -4336);  // 0x86EF10
                                v0 = addu(v0, v1);
                                a0 = lw(v0, 0);
                                jal(0x44D530u, &gen::fn_sub_1B0220_001b0220);
                                if (v0 == 0) {
                                    charge(4);
                                    v1 = si(19);
                                    sb(s1, 3, v1);
                                }
                            }
                        }
                    }
                } else {
                    charge(5);
                    a0 = lw(s1, 20);
                    jal(0x44D554u, &gen::fn_kwlnTaskExists_00195460);
                    if (v0 == 0) {
                        charge(4);
                        v1 = si(19);
                        sb(s1, 3, v1);
                    }
                }
            } else {
                charge(6);
                a0 = a1;
                a1 = lb(s1, 24);
                jal(0x44D57Cu, &gen::fn_sub_454F50_00454f50);
            }
        } else {
            charge(8);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4336);  // 0x86EF10
            v0 = addu(v0, a2);
            a0 = lw(v0, 0);
            jal(0x44D59Cu, &gen::fn_sub_1B0220_001b0220);
            if (v0 == 0) {
                charge(9);
                a0 = lb(s1, 1);
                a1 = si(4);
                jal(0x44D5B4u, &gen::fn_sub_4543C0_004543c0);
                a0 = lb(s1, 1);
                v1 = lui(0x96u);
                v1 = addiu(v1, -15856);  // 0x95C210
                v1 = addu(v1, a0);
                sb(v1, 0, zero);
            }
        }
        charge(10);
        ra = ld(sp, 96);
        lq(s5, sp, 80);
        lq(s4, sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 448);
    }

    // 0x44AAF0 ("ene think proc" update, [Y_Stratum_UpdateEneThinkTask] bands.sym): a shadow whose unit is gone goes to
    // state 6; paused (+64 == 1) does nothing; off random / fixed Tartarus floors (K_Scene_IsRandomFloor / sub_1A02C0) ->
    // sub_454110; else, with behaviour kind 4 or within reach of the hero (sub_1C7160): state 5 -> sub_44DFC0, 4 ->
    // sub_44AF60, 3 -> sub_44BEB0 (and the 0x95C210 byte = 1); out of reach the mover's queue is cleared (sub_1B00C0).
    // Returns 0 (keep running).
    void Y_Stratum_UpdateEneThinkTask() {
        enter(17);
        sp = addiu(sp, -48);
        sd(sp, 32, ra);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s1 = a0;
        s0 = lw(a0, kTaskWork);
        a0 = 0;
        v1 = lb(s0, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4632);  // 0x86EDE8
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        if (v0 != 0) {
            charge(6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4620);  // 0x86EDF4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            if (v0 != 0) {
                charge(1);
                a0 = si(1);
            }
        }
        charge(3);
        v0 = sltu(zero, a0);
        if (v0 == 0) {
            charge(2);
            v0 = si(6);
            sb(s0, 2, v0);
        }
        charge(4);
        v1 = lb(s0, 64);
        v0 = si(1);
        if (v1 == v0) {
            charge(3);
            v0 = 0;
        } else {
            charge(5);
            jal(0x44AB80u, &gen::fn_K_Scene_IsRandomFloor_001a0250);
            v1 = si(1);
            if (v0 != v1) {
                charge(5);
                jal(0x44AB94u, &gen::fn_sub_1A02C0_001a02c0);
                v1 = si(1);
                if (v0 != v1) {
                    charge(6);
                    a0 = s1;
                    jal(0x44ABACu, &gen::fn_sub_454110_00454110);
                    v0 = 0;
                    charge(6);
                    ra = ld(sp, 32);
                    lq(s1, sp, 16);
                    lq(s0, sp, 0);
                    sp = addiu(sp, 48);
                    return;
                }
            }
            charge(11);
            v1 = lb(s0, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            a0 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4308);  // 0x86EF2C
            v0 = addu(v0, a0);
            v1 = lw(v0, 0);
            v0 = si(4);
            if (v1 != v0) {
                charge(11);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                a0 = addu(v0, a0);
                v0 = lui(0x4516u);
                mtc1(v0, 12);  // 2400f
                a1 = lui(0x87u);
                a1 = addiu(a1, 6048);  // 0x8717A0 gFldUnitsPc
                jal(0x44AC08u, &gen::fn_sub_1C7160_001c7160);
                if (v0 == 0) {
                    charge(13);
                    v1 = lb(s0, 1);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, -4336);  // 0x86EF10
                    v0 = addu(v0, v1);
                    a0 = lw(v0, 0);
                    jal(0x44AC38u, &gen::fn_sub_1B00C0_001b00c0);
                    v0 = 0;
                    charge(6);
                    ra = ld(sp, 32);
                    lq(s1, sp, 16);
                    lq(s0, sp, 0);
                    sp = addiu(sp, 48);
                    return;
                }
            }
            charge(4);
            v1 = lb(s0, 2);
            v0 = si(6);
            if (v1 != v0) {
                charge(3);
                v0 = si(5);
                if (v1 != v0) {
                    charge(3);
                    v0 = si(4);
                    if (v1 != v0) {
                        charge(3);
                        v0 = si(3);
                        if (v1 != v0) {
                            charge(2);
                        } else {
                            charge(11);
                            a0 = s1;
                            jal(0x44AC8Cu, &gen::fn_sub_44BEB0_0044beb0);
                            a0 = si(1);
                            v1 = lb(s0, 1);
                            v0 = lui(0x96u);
                            v0 = addiu(v0, -15856);  // 0x95C210
                            v0 = addu(v0, v1);
                            sb(v0, 0, a0);
                        }
                    } else {
                        charge(5);
                        a0 = s1;
                        jal(0x44ACB8u, &gen::fn_sub_44AF60_0044af60);
                    }
                } else {
                    charge(3);
                    a0 = s1;
                    jal(0x44ACCCu, &gen::fn_sub_44DFC0_0044dfc0);
                }
            }
            charge(1);
            v0 = 0;
        }
        charge(6);
        ra = ld(sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 48);
    }
};

// @@STRUCTS@@

}  // namespace

// --- typed entry points -------------------------------------------------------------------------------------------------
void sub_44E530(EEContext& ctx, u64 unit, u64 kind) { set_args(ctx, {unit, kind}); EneLeaves{ctx}.sub_44E530(); }
u32 sub_44F060(EEContext& ctx, u64 task, u64 pos) { set_args(ctx, {task, pos}); EneLeaves{ctx}.sub_44F060(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_44F120(EEContext& ctx, u64 pos) { set_args(ctx, {pos}); EneLeaves{ctx}.sub_44F120(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_44F170(EEContext& ctx, u64 pos) { set_args(ctx, {pos}); EneLeaves{ctx}.sub_44F170(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_44F1C0(EEContext& ctx, u64 a, u64 b) { set_args(ctx, {a, b}); EneLeaves{ctx}.sub_44F1C0(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_44F270(EEContext& ctx, u64 a, u64 b) { set_args(ctx, {a, b}); EneLeaves{ctx}.sub_44F270(); return ctx.fpr[0]; }
void sub_4532D0(EEContext& ctx, u64 paused) { set_args(ctx, {paused}); EneLeaves{ctx}.sub_4532D0(); }
void sub_4533E0(EEContext& ctx, u64 flag) { set_args(ctx, {flag}); EneLeaves{ctx}.sub_4533E0(); }
u32 sub_453460(EEContext& ctx) { EneLeaves{ctx}.sub_453460(); return static_cast<u32>(v0_of(ctx)); }
void sub_453470(EEContext& ctx, u64 value) { set_args(ctx, {value}); EneLeaves{ctx}.sub_453470(); }
u32 sub_453480(EEContext& ctx) { EneLeaves{ctx}.sub_453480(); return static_cast<u32>(v0_of(ctx)); }
void sub_453490(EEContext& ctx, u64 task) { set_args(ctx, {task}); EneLeaves{ctx}.sub_453490(); }
u32 sub_4514A0(EEContext& ctx, u64 ec) { set_args(ctx, {ec}); EneLeaves{ctx}.sub_4514A0(); return static_cast<u32>(v0_of(ctx)); }
void sub_452010(EEContext& ctx, u64 pos) { set_args(ctx, {pos}); EneLeaves{ctx}.sub_452010(); }
void sub_452F70(EEContext& ctx, u64 out, u64 task) { set_args(ctx, {out, task}); EneLeaves{ctx}.sub_452F70(); }
void sub_44DFC0(EEContext& ctx, u64 task) { set_args(ctx, {task}); EneLook{ctx}.sub_44DFC0(); }
u32 sub_44E560(EEContext& ctx, u64 task) { set_args(ctx, {task}); EneLook{ctx}.sub_44E560(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_44F300(EEContext& ctx, u64 ec) { set_args(ctx, {ec}); EneLook{ctx}.sub_44F300(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_44FAB0(EEContext& ctx, u64 task) { set_args(ctx, {task}); EneLook{ctx}.sub_44FAB0(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_44FFB0(EEContext& ctx, u64 task) { set_args(ctx, {task}); EneLook{ctx}.sub_44FFB0(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_4534B0(EEContext& ctx, u64 ec) { set_args(ctx, {ec}); EneLook{ctx}.sub_4534B0(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_453ED0(EEContext& ctx, u64 ec, u64 x, u64 z, u64 pos, u64 tx, u64 tz) { set_args(ctx, {ec, x, z, pos, tx, tz}); EneStates{ctx}.sub_453ED0(); return static_cast<u32>(v0_of(ctx)); }
void sub_44B7D0(EEContext& ctx, u64 task) { set_args(ctx, {task}); EneStates{ctx}.sub_44B7D0(); }
void sub_44D600(EEContext& ctx, u64 task) { set_args(ctx, {task}); EneStates{ctx}.sub_44D600(); }
void sub_4501B0(EEContext& ctx, u64 ec) { set_args(ctx, {ec}); EneStates{ctx}.sub_4501B0(); }
void sub_450B30(EEContext& ctx, u64 ec) { set_args(ctx, {ec}); EneStates{ctx}.sub_450B30(); }
void sub_44AF60(EEContext& ctx, u64 task) { set_args(ctx, {task}); EneStates{ctx}.sub_44AF60(); }
void sub_451D70(EEContext& ctx, u64 task) { set_args(ctx, {task}); EneStates{ctx}.sub_451D70(); }
u32 sub_4523C0(EEContext& ctx, u64 task, u64 ec) { set_args(ctx, {task, ec}); EneStates{ctx}.sub_4523C0(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_452A70(EEContext& ctx, u64 ec, u64 pc) { set_args(ctx, {ec, pc}); EneStates{ctx}.sub_452A70(); return static_cast<u32>(v0_of(ctx)); }
void sub_454110(EEContext& ctx, u64 task) { set_args(ctx, {task}); EneStates{ctx}.sub_454110(); }
void sub_44BEB0(EEContext& ctx, u64 task) { set_args(ctx, {task}); EneStates{ctx}.sub_44BEB0(); }
s32 Y_Stratum_UpdateEneThinkTask(EEContext& ctx, u64 task) { set_args(ctx, {task}); EneStates{ctx}.Y_Stratum_UpdateEneThinkTask(); return static_cast<s32>(v0_of(ctx)); }
// @@API@@

}  // namespace p3fes::game

// =====================================================================================================================
// The recompiled program's entry points (recomp/generated/functions.h signatures)
// =====================================================================================================================
namespace p3fes::recomp_gen {
namespace g = p3fes::game;
void fn_sub_44E530_0044e530(p3fes::EEContext& ctx) { g::EneLeaves{ctx}.sub_44E530(); }
void fn_sub_44F060_0044f060(p3fes::EEContext& ctx) { g::EneLeaves{ctx}.sub_44F060(); }
void fn_sub_44F120_0044f120(p3fes::EEContext& ctx) { g::EneLeaves{ctx}.sub_44F120(); }
void fn_sub_44F170_0044f170(p3fes::EEContext& ctx) { g::EneLeaves{ctx}.sub_44F170(); }
void fn_sub_44F1C0_0044f1c0(p3fes::EEContext& ctx) { g::EneLeaves{ctx}.sub_44F1C0(); }
void fn_sub_44F270_0044f270(p3fes::EEContext& ctx) { g::EneLeaves{ctx}.sub_44F270(); }
void fn_sub_4532D0_004532d0(p3fes::EEContext& ctx) { g::EneLeaves{ctx}.sub_4532D0(); }
void fn_sub_4533E0_004533e0(p3fes::EEContext& ctx) { g::EneLeaves{ctx}.sub_4533E0(); }
void fn_sub_453460_00453460(p3fes::EEContext& ctx) { g::EneLeaves{ctx}.sub_453460(); }
void fn_sub_453470_00453470(p3fes::EEContext& ctx) { g::EneLeaves{ctx}.sub_453470(); }
void fn_sub_453480_00453480(p3fes::EEContext& ctx) { g::EneLeaves{ctx}.sub_453480(); }
void fn_sub_453490_00453490(p3fes::EEContext& ctx) { g::EneLeaves{ctx}.sub_453490(); }
void fn_sub_4514A0_004514a0(p3fes::EEContext& ctx) { g::EneLeaves{ctx}.sub_4514A0(); }
void fn_sub_452010_00452010(p3fes::EEContext& ctx) { g::EneLeaves{ctx}.sub_452010(); }
void fn_sub_452F70_00452f70(p3fes::EEContext& ctx) { g::EneLeaves{ctx}.sub_452F70(); }
void fn_sub_44DFC0_0044dfc0(p3fes::EEContext& ctx) { g::EneLook{ctx}.sub_44DFC0(); }
void fn_sub_44E560_0044e560(p3fes::EEContext& ctx) { g::EneLook{ctx}.sub_44E560(); }
void fn_sub_44F300_0044f300(p3fes::EEContext& ctx) { g::EneLook{ctx}.sub_44F300(); }
void fn_sub_44FAB0_0044fab0(p3fes::EEContext& ctx) { g::EneLook{ctx}.sub_44FAB0(); }
void fn_sub_44FFB0_0044ffb0(p3fes::EEContext& ctx) { g::EneLook{ctx}.sub_44FFB0(); }
void fn_sub_4534B0_004534b0(p3fes::EEContext& ctx) { g::EneLook{ctx}.sub_4534B0(); }
void fn_sub_453ED0_00453ed0(p3fes::EEContext& ctx) { g::EneStates{ctx}.sub_453ED0(); }
void fn_sub_44B7D0_0044b7d0(p3fes::EEContext& ctx) { g::EneStates{ctx}.sub_44B7D0(); }
void fn_sub_44D600_0044d600(p3fes::EEContext& ctx) { g::EneStates{ctx}.sub_44D600(); }
void fn_sub_4501B0_004501b0(p3fes::EEContext& ctx) { g::EneStates{ctx}.sub_4501B0(); }
void fn_sub_450B30_00450b30(p3fes::EEContext& ctx) { g::EneStates{ctx}.sub_450B30(); }
void fn_sub_44AF60_0044af60(p3fes::EEContext& ctx) { g::EneStates{ctx}.sub_44AF60(); }
void fn_sub_451D70_00451d70(p3fes::EEContext& ctx) { g::EneStates{ctx}.sub_451D70(); }
void fn_sub_4523C0_004523c0(p3fes::EEContext& ctx) { g::EneStates{ctx}.sub_4523C0(); }
void fn_sub_452A70_00452a70(p3fes::EEContext& ctx) { g::EneStates{ctx}.sub_452A70(); }
void fn_sub_454110_00454110(p3fes::EEContext& ctx) { g::EneStates{ctx}.sub_454110(); }
void fn_sub_44BEB0_0044beb0(p3fes::EEContext& ctx) { g::EneStates{ctx}.sub_44BEB0(); }
void fn_Y_Stratum_UpdateEneThinkTask_0044aaf0(p3fes::EEContext& ctx) { g::EneStates{ctx}.Y_Stratum_UpdateEneThinkTask(); }
// @@SHIMS@@
}  // namespace p3fes::recomp_gen
