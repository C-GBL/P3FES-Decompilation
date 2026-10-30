// The shadows' movement helpers, the symbol-direction marker, the unit status bytes, the party members' think
// switches and skill use, and the Kyoto NPC helpers (0x453D90-0x457470), hand-decompiled from SLUS_216.21
// (game/include/p3fes/game/tartarus.h; docs/ANALYSIS/27_unmapped_bands.md section 8). Phase 5 slice `tartarus`: these
// replace the recompiled bodies listed in game/replaced.txt; tests/game/test_tartarus.cpp runs each against its __recomp
// body. The register view, the cycle model and the call convention: game/src/field/tartarus_cpu.h.
//
// Units: gFldUnitsEc (24 shadows at 0x86EDA0) and gFldUnitsPc (4 party members at 0x8717A0), 448 bytes each, +72 used,
// +84 scene resource, +360 model, +364 think task, +368 mover task, +396 behaviour kind, +408..+412 the status bytes the
// field event / mini-map read; the four NPC slots at 0x86E6A0 come before the shadows. A party member's think work
// (gFldUnitsPc[i] +364 -> +60) holds its mode at +4704 with +4631 / +4662 its change flags, and the skill-use state at
// +4646 (target) / +4663..+4665 / +4667 (a 50-frame timer) / +4668.. (aim points).
#include "p3fes/game/tartarus.h"

#include "tartarus_cpu.h"

namespace p3fes::recomp_gen {
void fn_K_Field_Get_001b9120(p3fes::EEContext&);
void fn_sub_1A0DC0_001a0dc0(p3fes::EEContext&);
void fn_sub_1A91B0_001a91b0(p3fes::EEContext&);
void fn_sub_1ACC30_001acc30(p3fes::EEContext&);
void fn_sub_1AD870_001ad870(p3fes::EEContext&);
void fn_sub_1AD940_001ad940(p3fes::EEContext&);
void fn_sub_1ADC20_001adc20(p3fes::EEContext&);
void fn_sub_1ADFF0_001adff0(p3fes::EEContext&);
void fn_sub_1AF930_001af930(p3fes::EEContext&);
void fn_sub_1AFA20_001afa20(p3fes::EEContext&);
void fn_sub_316F70_00316f70(p3fes::EEContext&);
void fn_sub_3182D0_003182d0(p3fes::EEContext&);
void fn_sub_3B5D10_003b5d10(p3fes::EEContext&);
void fn_sub_3B6030_003b6030(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C3880_004c3880(p3fes::EEContext&);
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);
void fn_datUnitIsGenusDead_002ff790(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_16C4F0_0016c4f0(p3fes::EEContext&);
void fn_sub_16C570_0016c570(p3fes::EEContext&);
void fn_sub_16CF40_0016cf40(p3fes::EEContext&);
void fn_sub_16CF90_0016cf90(p3fes::EEContext&);
void fn_sub_17B500_0017b500(p3fes::EEContext&);
void fn_sub_17B5B0_0017b5b0(p3fes::EEContext&);
void fn_sub_17B860_0017b860(p3fes::EEContext&);
void fn_sub_18BEE0_0018bee0(p3fes::EEContext&);
void fn_sub_1A9760_001a9760(p3fes::EEContext&);
void fn_sub_1B00C0_001b00c0(p3fes::EEContext&);
void fn_sub_1B0250_001b0250(p3fes::EEContext&);
void fn_sub_1C7130_001c7130(p3fes::EEContext&);
void fn_sub_1DDE00_001dde00(p3fes::EEContext&);
void fn_sub_318ED0_00318ed0(p3fes::EEContext&);
void fn_sub_43B980_0043b980(p3fes::EEContext&);
void fn_sub_43BDA0_0043bda0(p3fes::EEContext&);
void fn_sub_454A70_00454a70(p3fes::EEContext&);
void fn_sub_457340_00457340(p3fes::EEContext&);
void fn_sub_457390_00457390(p3fes::EEContext&);
void fn_sub_4573D0_004573d0(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
// @@CALLEES@@
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

namespace gen = ::p3fes::recomp_gen;
using namespace tartarus;
using namespace tart;

struct SymLeaves : Cpu {
    using Cpu::Cpu;

    // 0x453D90 (ec): builds shadow ec's step list (s16 pairs at think work +3224 + 4 i, all 256 cleared first): from the
    // target cell (+139 / +140) it follows each path record's "from" cell (+156 / +158 of the record +152 + 8 cell) until
    // the start (+141 / +142), counting the steps in +148; at most 100 rounds.
    void sub_453D90() {
        enter(16);
        a0 = dsll32(a0, 24);
        a0 = dsra32(a0, 24);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, -4340);  // 0x86EF0C
        v1 = addu(v1, a0);
        v1 = lw(v1, 0);
        v1 = lw(v1, kTaskWork);
        a1 = 0;
        a0 = 0;
        sw(v1, 148, zero);
        a3 = 0;
        for (;;) {
            charge(3);
            a2 = slti(a3, 256);
            if (a2 == 0) break;
            backedge();
            charge(5);
            a2 = sll(a3, 2);
            a2 = addu(v1, a2);
            sh(a2, 3224, zero);
            sh(a2, 3226, zero);
            a3 = addiu(a3, 1);
        }
        charge(11);
        a4 = lbu(v1, 139);
        a3 = lbu(v1, 140);
        a2 = lw(v1, 148);
        a2 = sll(a2, 2);
        a2 = addu(a2, v1);
        sh(a2, 3224, a4);
        a2 = lw(v1, 148);
        a2 = sll(a2, 2);
        a2 = addu(a2, v1);
        sh(a2, 3226, a3);
        a5 = si(1);
        for (;;) {
            charge(16);
            a6 = lw(v1, 148);
            a2 = sll(a6, 2);
            a4 = addu(v1, a2);
            a2 = lh(a4, 3226);
            a3 = sll(a2, 4);
            a2 = lh(a4, 3224);
            a2 = addu(a2, a3);
            a2 = sll(a2, 3);
            a2 = addu(v1, a2);
            a4 = lh(a2, 156);
            a3 = lh(a2, 158);
            a2 = addiu(a6, 1);
            sw(v1, 148, a2);
            a2 = lbu(v1, 141);
            if (a4 == a2) {
                charge(3);
                a2 = lbu(v1, 142);
                if (a3 == a2) {
                    charge(3);
                    a1 = a5;
                    goto L_00453eac;
                }
            }
            charge(14);
            a2 = sll(a3, 4);
            a2 = addu(a4, a2);
            a2 = sll(a2, 3);
            a4 = addu(v1, a2);
            a3 = lh(a4, 152);
            a2 = lw(v1, 148);
            a2 = sll(a2, 2);
            a2 = addu(v1, a2);
            sh(a2, 3224, a3);
            a3 = lh(a4, 154);
            a2 = lw(v1, 148);
            a2 = sll(a2, 2);
            a2 = addu(v1, a2);
            sh(a2, 3226, a3);
          L_00453eac:
            charge(4);
            a0 = addiu(a0, 1);
            a2 = slti(a0, 100);
            if (a2 == 0) {
                charge(1);
                a1 = a5;
            }
            charge(2);
            if (a1 != 0) break;
            backedge();
        }
        charge(2);
    }

    // 0x4541F0 ("y_ene_dead effect proc" update, [Y_Stratum_UpdateEneDeadEffectTask] bands.sym): state +0 == 1 returns -1
    // (done); state 0 raises the point (+4..: +8 += 100), starts the effect there (sub_1A91B0 on sField +4612) and sets
    // state 1; any other state returns 0 (as does state 0).
    void Y_Stratum_UpdateEneDeadEffectTask() {
        enter(8);
        sp = addiu(sp, -32);
        sd(sp, 16, ra);
        sq(s0, sp, 0);
        s0 = lw(a0, kTaskWork);
        v1 = lb(s0, 0);
        v0 = si(1);
        if (v1 != v0) {
            charge(2);
            if (v1 != 0) {
                charge(2);
            } else {
                charge(16);
                lwc1(1, s0, 8);
                v0 = lui(0x42C8u);
                mtc1(v0, 0);  // 100.0
                add_s(0, 1, 0);
                swc1(0, s0, 8);
                jal(0x454238u, &gen::fn_K_Field_Get_001b9120);
                a0 = lw(v0, 4612);
                a1 = addiu(s0, 4);
                jal(0x454248u, &gen::fn_sub_1A91B0_001a91b0);
                v0 = si(1);
                sb(s0, 0, v0);
            }
        } else {
            charge(3);
            v0 = si(-1);
            charge(5);
            ra = ld(sp, 16);
            lq(s0, sp, 0);
            sp = addiu(sp, 32);
            return;
        }
        charge(1);
        v0 = 0;
        charge(5);
        ra = ld(sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 32);
    }

    // 0x4543C0 (ec, state): the think work of gFldUnitsEc[ec] (+364 -> +60): +2 = state, the sub-states +3 / +4 / +5 = 0.
    void sub_4543C0() {
        enter(16);
        a0 = dsll32(a0, 24);
        a0 = dsra32(a0, 24);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, -4340);  // 0x86EF0C
        v1 = addu(v1, a0);
        v1 = lw(v1, 0);
        v1 = lw(v1, kTaskWork);
        sb(v1, 2, a1);
        sb(v1, 3, zero);
        sb(v1, 4, zero);
        sb(v1, 5, zero);
    }

    // 0x454400 (pos, ec): behaviour kind 4 always 1; else a vertical ray at pos from y +400 to -400 (K_FldFrame_Raycast
    // sub_1ACC30 on the frame's ray record): hit with the height at most 50 -> 1, else 0.
    void sub_454400() {
        enter(47);
        sp = addiu(sp, -64);
        sd(sp, 0, ra);
        a2 = addiu(sp, 48);
        lwc1(2, a0, 0);
        lwc1(1, a0, 4);
        lwc1(0, a0, 8);
        swc1(2, sp, 48);
        swc1(1, sp, 52);
        swc1(0, sp, 56);
        v1 = dsll32(a1, 24);
        v1 = dsra32(v1, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4340);  // 0x86EF0C
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        v1 = lw(v0, kTaskWork);
        lwc1(2, sp, 48);
        lwc1(1, sp, 52);
        lwc1(0, sp, 56);
        swc1(2, sp, 28);
        swc1(1, sp, 32);
        swc1(0, sp, 36);
        a0 = addiu(sp, 16);
        lwc1(2, sp, 28);
        lwc1(1, sp, 32);
        lwc1(0, sp, 36);
        swc1(2, sp, 16);
        swc1(1, sp, 20);
        swc1(0, sp, 24);
        v0 = lui(0x43C8u);
        sw(sp, 20, v0);
        v0 = lui(0xC3C8u);
        sw(sp, 32, v0);
        v1 = lb(v1, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4308);  // 0x86EF2C
        v0 = addu(v0, v1);
        v1 = lw(v0, 0);
        v0 = si(4);
        if (v1 == v0) {
            charge(3);
            v0 = si(1);
        } else {
            charge(6);
            a1 = a2;
            jal(0x4544CCu, &gen::fn_sub_1ACC30_001acc30);
            v1 = si(1);
            if (v0 == v1) {
                charge(7);
                lwc1(1, sp, 52);
                v0 = lui(0x4248u);
                mtc1(v0, 0);  // 50f
                c_le_s(1, 0);
                if (!cond()) {
                    charge(1);
                    v1 = 0;
                }
                charge(3);
                v0 = v1;
            } else {
                charge(1);
                v0 = 0;
            }
        }
        charge(4);
        ra = ld(sp, 0);
        sp = addiu(sp, 64);
    }

    // 0x454520 (pos, ec): 1 when the distance (sub_4C6AC0) from the model's position (unit +360 -> +256..) to pos is below
    // the behaviour record's range (gp-0x4A60 + 64 kind, +0).
    void sub_454520() {
        enter(55);
        sp = addiu(sp, -80);
        sd(sp, 32, ra);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        lwc1(2, a0, 0);
        lwc1(1, a0, 4);
        lwc1(0, a0, 8);
        swc1(2, sp, 64);
        swc1(1, sp, 68);
        swc1(0, sp, 72);
        v1 = dsll32(a1, 24);
        v1 = dsra32(v1, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4340);  // 0x86EF0C
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        v0 = lw(v0, kTaskWork);
        s0 = 0;
        v1 = lb(v0, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        a0 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4308);  // 0x86EF2C
        v0 = addu(v0, a0);
        v0 = lw(v0, 0);
        v1 = sll(v0, 6);
        v0 = lw(gp, -19040);
        s1 = addu(v0, v1);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4344);  // 0x86EF08
        v0 = addu(v0, a0);
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
        jal(0x4545E4u, &gen::fn_sub_4C6AC0_004c6ac0);
        lwc1(1, s1, 0);
        c_lt_s(0, 1);
        if (cond()) {
            charge(1);
            s0 = si(1);
        }
        charge(7);
        v0 = s0;
        ra = ld(sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 80);
    }

    // 0x454620 (ec): the direction from the model to the target point (+40.., RwV3dNormalize sub_4C69F0) times the range
    // (record +0) from the model gives a point; farther than 150 from the target, on a good ground (sub_454400's ray, kind 4
    // passes) it is queued as a walk (sub_1AFA20) and 1 returned; else 0.
    void sub_454620() {
        enter(180);
        sp = addiu(sp, -240);
        sd(sp, 32, ra);
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
        s1 = lw(v0, kTaskWork);
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
        jal(0x4546ACu, &gen::fn_sub_1AD940_001ad940);
        lwc1(1, sp, 192);
        v1 = lb(s1, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4344);  // 0x86EF08
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        lwc1(0, v0, 256);
        sub_s(0, 1, 0);
        swc1(0, sp, 224);
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
        jal(0x45470Cu, &gen::fn_sub_1AD940_001ad940);
        lwc1(1, sp, 180);
        v1 = lb(s1, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4344);  // 0x86EF08
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        lwc1(0, v0, 260);
        sub_s(0, 1, 0);
        swc1(0, sp, 228);
        v1 = lb(s1, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, 6132);  // 0x8717F4
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        a0 = addiu(sp, 160);
        a1 = lw(v0, kResController);
        jal(0x45476Cu, &gen::fn_sub_1AD940_001ad940);
        lwc1(1, sp, 168);
        v1 = lb(s1, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4344);  // 0x86EF08
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        lwc1(0, v0, 264);
        sub_s(0, 1, 0);
        swc1(0, sp, 232);
        a0 = addiu(sp, 224);
        a1 = a0;
        jal(0x4547ACu, &gen::fn_sub_4C69F0_004c69f0);
        lwc1(5, s0, 0);
        lwc1(0, sp, 228);
        mul_s(4, 0, 5);
        lwc1(0, sp, 232);
        mul_s(3, 0, 5);
        lwc1(2, sp, 224);
        v1 = lb(s1, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4344);  // 0x86EF08
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        lwc1(1, v0, 256);
        mtc1(zero, 0);
        adda_s(0, 1);
        madd_s(0, 2, 5);
        swc1(0, sp, 224);
        lwc1(0, v0, 260);
        add_s(0, 4, 0);
        swc1(0, sp, 228);
        lwc1(0, v0, 264);
        add_s(0, 3, 0);
        swc1(0, sp, 232);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4620);  // 0x86EDF4
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        a0 = addiu(sp, 144);
        a1 = lw(v0, kResController);
        jal(0x454834u, &gen::fn_sub_1AD940_001ad940);
        lwc1(1, sp, 144);
        lwc1(0, sp, 224);
        sub_s(0, 0, 1);
        swc1(0, sp, 208);
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
        jal(0x454874u, &gen::fn_sub_1AD940_001ad940);
        lwc1(1, sp, 132);
        lwc1(0, sp, 228);
        sub_s(0, 0, 1);
        swc1(0, sp, 212);
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
        jal(0x4548B4u, &gen::fn_sub_1AD940_001ad940);
        lwc1(1, sp, 120);
        lwc1(0, sp, 232);
        sub_s(0, 0, 1);
        swc1(0, sp, 216);
        a0 = addiu(sp, 208);
        jal(0x4548D0u, &gen::fn_sub_4C6AC0_004c6ac0);
        v0 = lui(0x4316u);
        mtc1(v0, 1);  // 150f
        c_le_s(0, 1);
        if (!cond()) {
            charge(45);
            v1 = lb(s1, 1);
            v0 = ld(sp, 224);
            lwc1(0, sp, 232);
            sd(sp, 80, v0);
            swc1(0, sp, 88);
            a1 = addiu(sp, 96);
            v0 = ld(sp, 80);
            lwc1(2, sp, 88);
            sd(sp, 96, v0);
            swc1(2, sp, 104);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4340);  // 0x86EF0C
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            v1 = lw(v0, kTaskWork);
            lwc1(1, sp, 80);
            lwc1(0, sp, 84);
            swc1(1, sp, 60);
            swc1(0, sp, 64);
            swc1(2, sp, 68);
            a0 = addiu(sp, 48);
            lwc1(2, sp, 60);
            lwc1(1, sp, 64);
            lwc1(0, sp, 68);
            swc1(2, sp, 48);
            swc1(1, sp, 52);
            swc1(0, sp, 56);
            v0 = lui(0x43C8u);
            sw(sp, 52, v0);
            v0 = lui(0xC3C8u);
            sw(sp, 64, v0);
            v1 = lb(v1, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4308);  // 0x86EF2C
            v0 = addu(v0, v1);
            v1 = lw(v0, 0);
            v0 = si(4);
            if (v1 == v0) {
                charge(3);
                v1 = si(1);
            } else {
                charge(5);
                jal(0x4549B0u, &gen::fn_sub_1ACC30_001acc30);
                v1 = si(1);
                if (v0 == v1) {
                    charge(7);
                    lwc1(1, sp, 100);
                    v0 = lui(0x4248u);
                    mtc1(v0, 0);  // 50f
                    c_le_s(1, 0);
                    if (!cond()) {
                        goto L_004549f4;
                    }
                    charge(2);
                    goto L_004549f8;
                }
                charge(3);
                v1 = 0;
                goto L_004549f8;
              L_004549f4:
                charge(1);
                v1 = 0;
            }
          L_004549f8:
            charge(3);
            v0 = si(1);
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
                a1 = addiu(sp, 224);
                lwc1(12, s0, 12);
                jal(0x454A2Cu, &gen::fn_sub_1AFA20_001afa20);
                v1 = si(1);
                if (v0 == v1) {
                    charge(3);
                    v0 = v1;
                    charge(6);
                    ra = ld(sp, 32);
                    lq(s1, sp, 16);
                    lq(s0, sp, 0);
                    sp = addiu(sp, 240);
                    return;
                }
            }
        }
        charge(1);
        v0 = 0;
        charge(6);
        ra = ld(sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 240);
    }

    // 0x454A70 (ec, pos): sub_454620 for the given point, without the 150 test; the walk is queued when the ground is good.
    void sub_454A70() {
        enter(118);
        sp = addiu(sp, -144);
        sd(sp, 32, ra);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        lwc1(2, a1, 0);
        lwc1(1, a1, 4);
        lwc1(0, a1, 8);
        swc1(2, sp, 128);
        swc1(1, sp, 132);
        swc1(0, sp, 136);
        v1 = dsll32(a0, 24);
        v1 = dsra32(v1, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4340);  // 0x86EF0C
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        s1 = lw(v0, kTaskWork);
        v1 = lb(s1, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        a0 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4308);  // 0x86EF2C
        v0 = addu(v0, a0);
        v0 = lw(v0, 0);
        v1 = sll(v0, 6);
        v0 = lw(gp, -19040);
        s0 = addu(v0, v1);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4344);  // 0x86EF08
        v0 = addu(v0, a0);
        v0 = lw(v0, 0);
        lwc1(1, v0, 256);
        lwc1(0, sp, 128);
        sub_s(0, 0, 1);
        swc1(0, sp, 112);
        lwc1(1, v0, 260);
        lwc1(0, sp, 132);
        sub_s(0, 0, 1);
        swc1(0, sp, 116);
        lwc1(1, v0, 264);
        lwc1(0, sp, 136);
        sub_s(0, 0, 1);
        swc1(0, sp, 120);
        a0 = addiu(sp, 112);
        a1 = a0;
        jal(0x454B34u, &gen::fn_sub_4C69F0_004c69f0);
        lwc1(5, s0, 0);
        lwc1(0, sp, 116);
        mul_s(4, 0, 5);
        lwc1(0, sp, 120);
        mul_s(3, 0, 5);
        lwc1(2, sp, 112);
        v1 = lb(s1, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4344);  // 0x86EF08
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        lwc1(1, v0, 256);
        mtc1(zero, 0);
        adda_s(0, 1);
        madd_s(0, 2, 5);
        swc1(0, sp, 112);
        lwc1(0, v0, 260);
        add_s(0, 4, 0);
        swc1(0, sp, 116);
        lwc1(0, v0, 264);
        add_s(0, 3, 0);
        swc1(0, sp, 120);
        v0 = ld(sp, 112);
        lwc1(0, sp, 120);
        sd(sp, 80, v0);
        swc1(0, sp, 88);
        a1 = addiu(sp, 96);
        v0 = ld(sp, 80);
        lwc1(2, sp, 88);
        sd(sp, 96, v0);
        swc1(2, sp, 104);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4340);  // 0x86EF0C
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        v1 = lw(v0, kTaskWork);
        lwc1(1, sp, 80);
        lwc1(0, sp, 84);
        swc1(1, sp, 60);
        swc1(0, sp, 64);
        swc1(2, sp, 68);
        a0 = addiu(sp, 48);
        lwc1(2, sp, 60);
        lwc1(1, sp, 64);
        lwc1(0, sp, 68);
        swc1(2, sp, 48);
        swc1(1, sp, 52);
        swc1(0, sp, 56);
        v0 = lui(0x43C8u);
        sw(sp, 52, v0);
        v0 = lui(0xC3C8u);
        sw(sp, 64, v0);
        v1 = lb(v1, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4308);  // 0x86EF2C
        v0 = addu(v0, v1);
        v1 = lw(v0, 0);
        v0 = si(4);
        if (v1 == v0) {
            charge(3);
            v1 = si(1);
        } else {
            charge(5);
            jal(0x454C54u, &gen::fn_sub_1ACC30_001acc30);
            v1 = si(1);
            if (v0 == v1) {
                charge(7);
                lwc1(1, sp, 100);
                v0 = lui(0x4248u);
                mtc1(v0, 0);  // 50f
                c_le_s(1, 0);
                if (!cond()) {
                    goto L_00454c98;
                }
                charge(2);
                goto L_00454c9c;
            }
            charge(3);
            v1 = 0;
            goto L_00454c9c;
          L_00454c98:
            charge(1);
            v1 = 0;
        }
      L_00454c9c:
        charge(3);
        v0 = si(1);
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
            a1 = addiu(sp, 112);
            lwc1(12, s0, 12);
            jal(0x454CD0u, &gen::fn_sub_1AFA20_001afa20);
            v0 = si(1);
        } else {
            charge(1);
            v0 = 0;
        }
        charge(6);
        ra = ld(sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 144);
    }

    // 0x454D00 (pos): pos's cell must be a room (+0 == 1); inside the cell (x, z offsets from its low edge) the middle band
    // 150 .. 650 is free, the margins need the matching open side (bits 2 / 8 / 1 / 4 for the low x / high x / low z / high z
    // margin); corners are refused only through those sides' tests as compiled.
    void sub_454D00() {
        enter(64);
        sp = addiu(sp, -112);
        sd(sp, 48, ra);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(21, sp, 4);
        swc1(20, sp, 0);
        lwc1(2, a0, 0);
        lwc1(1, a0, 4);
        lwc1(0, a0, 8);
        swc1(2, sp, 96);
        swc1(1, sp, 100);
        swc1(0, sp, 104);
        a0 = ld(sp, 96);
        lwc1(1, sp, 104);
        sd(sp, 80, a0);
        swc1(1, sp, 88);
        v0 = lui(0x43C8u);
        mtc1(v0, 4);  // 400.0
        lwc1(0, sp, 80);
        add_s(0, 4, 0);
        v0 = lui(0x4448u);
        mtc1(v0, 3);  // 800.0
        div_s(0, 0, 3);
        cvt_w_s(0, 0);
        mfc1(v0, 0);
        v1 = dsll32(v0, 24);
        v1 = dsra32(v1, 24);
        sd(sp, 64, a0);
        swc1(1, sp, 72);
        add_s(0, 4, 1);
        div_s(0, 0, 3);
        cvt_w_s(0, 0);
        mfc1(v0, 0);
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
        mtc1(v1, 0);
        cvt_s_w(1, 0);
        lwc1(0, sp, 96);
        mtc1(zero, 2);
        adda_s(2, 0);
        msub_s(0, 3, 1);
        add_s(20, 4, 0);
        mtc1(v0, 0);
        cvt_s_w(1, 0);
        lwc1(0, sp, 104);
        adda_s(2, 0);
        msub_s(0, 3, 1);
        add_s(21, 4, 0);
        s1 = sll(v0, 8);
        s0 = sll(v1, 4);
        jal(0x454DE0u, &gen::fn_K_Field_Get_001b9120);
        v0 = addu(v0, s1);
        v0 = addu(v0, s0);
        v1 = lbu(v0, 72);
        v0 = si(1);
        if (v1 != v0) {
            charge(3);
            v0 = 0;
        } else {
            charge(6);
            v0 = lui(0x4316u);
            mtc1(v0, 1);  // 150f
            c_lt_s(21, 1);
            if (cond()) {
                charge(3);
                c_lt_s(20, 1);
                if (cond()) {
                    goto L_00454f28;
                }
                charge(7);
                v0 = si(650);
                mtc1(v0, 0);
                cvt_s_w(0, 0);
                c_le_s(20, 0);
                if (!cond()) {
                    goto L_00454f28;
                }
                charge(9);
                jal(0x454E4Cu, &gen::fn_K_Field_Get_001b9120);
                v0 = addu(v0, s1);
                v0 = addu(v0, s0);
                v0 = lbu(v0, 83);
                v0 = v0 & 0x1u;
                v0 = sltu(zero, v0);
                charge(8);
                ra = ld(sp, 48);
                lq(s1, sp, 32);
                lq(s0, sp, 16);
                lwc1(21, sp, 4);
                lwc1(20, sp, 0);
                sp = addiu(sp, 112);
                return;
            }
            charge(7);
            v0 = si(650);
            mtc1(v0, 0);
            cvt_s_w(0, 0);
            c_le_s(21, 0);
            if (!cond()) {
                charge(3);
                c_lt_s(20, 1);
                if (cond()) {
                    goto L_00454f28;
                }
                charge(3);
                c_le_s(20, 0);
                if (!cond()) {
                    goto L_00454f28;
                }
                charge(9);
                jal(0x454EA4u, &gen::fn_K_Field_Get_001b9120);
                v0 = addu(v0, s1);
                v0 = addu(v0, s0);
                v0 = lbu(v0, 83);
                v0 = v0 & 0x4u;
                v0 = sltu(zero, v0);
                charge(8);
                ra = ld(sp, 48);
                lq(s1, sp, 32);
                lq(s0, sp, 16);
                lwc1(21, sp, 4);
                lwc1(20, sp, 0);
                sp = addiu(sp, 112);
                return;
            }
            charge(3);
            c_lt_s(20, 1);
            if (cond()) {
                charge(9);
                jal(0x454ED4u, &gen::fn_K_Field_Get_001b9120);
                v0 = addu(v0, s1);
                v0 = addu(v0, s0);
                v0 = lbu(v0, 83);
                v0 = v0 & 0x2u;
                v0 = sltu(zero, v0);
                charge(8);
                ra = ld(sp, 48);
                lq(s1, sp, 32);
                lq(s0, sp, 16);
                lwc1(21, sp, 4);
                lwc1(20, sp, 0);
                sp = addiu(sp, 112);
                return;
            }
            charge(3);
            c_le_s(20, 0);
            if (!cond()) {
                charge(9);
                jal(0x454F04u, &gen::fn_K_Field_Get_001b9120);
                v0 = addu(v0, s1);
                v0 = addu(v0, s0);
                v0 = lbu(v0, 83);
                v0 = v0 & 0x8u;
                v0 = sltu(zero, v0);
                charge(8);
                ra = ld(sp, 48);
                lq(s1, sp, 32);
                lq(s0, sp, 16);
                lwc1(21, sp, 4);
                lwc1(20, sp, 0);
                sp = addiu(sp, 112);
                return;
            }
          L_00454f28:
            charge(1);
            v0 = si(1);
        }
        charge(8);
        ra = ld(sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(21, sp, 4);
        lwc1(20, sp, 0);
        sp = addiu(sp, 112);
    }

    // 0x455B50: party members 1..3: +412 = (think +4629 == 1), +410 = think +1, +411 = (think +1 == 5); shadows: +408 = the
    // target member (+24), +409 = the path target cell (+139 + 16 +140), +410 = the state (+2), +411 = 0, +412 = paused.
    void sub_455B50() {
        enter(9);
        a1 = si(1);
        v1 = a1;
        a0 = lui(0x87u);
        a0 = addiu(a0, 6048);  // 0x8717A0 gFldUnitsPc
        a3 = a1;
        a4 = si(5);
        t4 = a1;
        for (;;) {
            charge(3);
            a2 = slti(a1, 4);
            if (a2 == 0) break;
            backedge();
            charge(8);
            a6 = 0;
            a2 = sll(a1, 3);
            a2 = subu(a2, a1);
            a2 = sll(a2, 6);
            a5 = addu(a0, a2);
            a2 = lw(a5, 72);
            if (a2 != 0) {
                charge(3);
                a2 = lw(a5, 84);
                if (a2 != 0) {
                    charge(1);
                    a6 = v1;
                }
            }
            charge(3);
            a2 = sltu(zero, a6);
            if (a2 == t4) {
                charge(11);
                a2 = sll(a1, 3);
                a2 = subu(a2, a1);
                a2 = sll(a2, 6);
                a6 = addu(a0, a2);
                a2 = lw(a6, 364);
                a7 = lw(a2, kTaskWork);
                a5 = addiu(a6, 412);
                sb(a6, 412, zero);
                a2 = lb(a7, 4629);
                if (a2 == t4) {
                    charge(1);
                    sb(a5, 0, t4);
                }
                charge(11);
                a2 = sll(a1, 3);
                a2 = subu(a2, a1);
                a2 = sll(a2, 6);
                a6 = addu(a0, a2);
                a2 = lb(a7, 1);
                sb(a6, 410, a2);
                a5 = addiu(a6, 411);
                sb(a6, 411, zero);
                a2 = lb(a7, 1);
                if (a2 == a4) {
                    charge(1);
                    sb(a5, 0, a3);
                }
            }
            charge(1);
            a1 = addiu(a1, 1);
        }
        charge(6);
        v1 = 0;
        a4 = si(1);
        a5 = lui(0x87u);
        a5 = addiu(a5, -4704);  // 0x86EDA0 gFldUnitsEc
        for (;;) {
            charge(3);
            a0 = slti(v1, 24);
            if (a0 == 0) break;
            backedge();
            charge(8);
            a2 = 0;
            a0 = sll(v1, 3);
            a0 = subu(a0, v1);
            a0 = sll(a0, 6);
            a1 = addu(a5, a0);
            a0 = lw(a1, 72);
            if (a0 != 0) {
                charge(3);
                a0 = lw(a1, 84);
                if (a0 != 0) {
                    charge(1);
                    a2 = a4;
                }
            }
            charge(3);
            a0 = sltu(zero, a2);
            if (a0 == a4) {
                charge(21);
                a0 = sll(v1, 3);
                a0 = subu(a0, v1);
                a0 = sll(a0, 6);
                a3 = addu(a5, a0);
                a0 = lw(a3, 364);
                a2 = lw(a0, kTaskWork);
                a0 = lb(a2, 24);
                sb(a3, 408, a0);
                a1 = lbu(a2, 139);
                a0 = lbu(a2, 140);
                a0 = sll(a0, 4);
                a0 = addu(a1, a0);
                sb(a3, 409, a0);
                a0 = lb(a2, 2);
                sb(a3, 410, a0);
                sb(a3, 411, zero);
                a1 = addiu(a3, 412);
                sb(a3, 412, zero);
                a0 = lb(a2, 64);
                if (a0 == a4) {
                    charge(1);
                    sb(a1, 0, a4);
                }
            }
            charge(1);
            v1 = addiu(v1, 1);
        }
        charge(2);
    }

    // 0x455CF0: party members 1..3: +410 / +412 = 0; shadows: +408 .. +412 = 0.
    void sub_455CF0() {
        enter(7);
        a5 = si(1);
        a1 = a5;
        a3 = lui(0x87u);
        a3 = addiu(a3, 6048);  // 0x8717A0 gFldUnitsPc
        a0 = a5;
        for (;;) {
            charge(3);
            v1 = slti(a5, 4);
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
            if (v1 == a0) {
                charge(6);
                v1 = sll(a5, 3);
                v1 = subu(v1, a5);
                v1 = sll(v1, 6);
                v1 = addu(a3, v1);
                sb(v1, 410, zero);
                sb(v1, 412, zero);
            }
            charge(1);
            a5 = addiu(a5, 1);
        }
        charge(6);
        a3 = 0;
        a0 = si(1);
        a2 = lui(0x87u);
        a2 = addiu(a2, -4704);  // 0x86EDA0 gFldUnitsEc
        for (;;) {
            charge(3);
            v1 = slti(a3, 24);
            if (v1 == 0) break;
            backedge();
            charge(8);
            a4 = 0;
            v1 = sll(a3, 3);
            v1 = subu(v1, a3);
            v1 = sll(v1, 6);
            a1 = addu(a2, v1);
            v1 = lw(a1, 72);
            if (v1 != 0) {
                charge(3);
                v1 = lw(a1, 84);
                if (v1 != 0) {
                    charge(1);
                    a4 = a0;
                }
            }
            charge(3);
            v1 = sltu(zero, a4);
            if (v1 == a0) {
                charge(9);
                v1 = sll(a3, 3);
                v1 = subu(v1, a3);
                v1 = sll(v1, 6);
                v1 = addu(a2, v1);
                sb(v1, 408, zero);
                sb(v1, 409, zero);
                sb(v1, 410, zero);
                sb(v1, 411, zero);
                sb(v1, 412, zero);
            }
            charge(1);
            a3 = addiu(a3, 1);
        }
        charge(2);
    }

    // 0x4561D0 (task; $f12 / $f13): the symbol-direction work's centre +288 / +292.
    void sub_4561D0() {
        enter(5);
        v1 = lw(a0, kTaskWork);
        swc1(12, v1, 288);
        swc1(13, v1, 292);
    }

    // 0x4561F0 (task): the four 2D corners (the table 0x6B4A90, as {x, 0, z}) are turned by an RW matrix rotated about the
    // axis 0x6B4A78 ($f12 the work's angle) and placed at the centre: work +16 + 64 i / +20 + 64 i = centre + turned x / z.
    void sub_4561F0() {
        enter(19);
        sp = addiu(sp, -240);
        sd(sp, 80, ra);
        sq(s3, sp, 64);
        sq(s2, sp, 48);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(20, sp, 0);
        mov_s(20, 12);
        s0 = lw(a0, kTaskWork);
        v0 = lui(0x6Bu);
        v1 = ld(v0, 19064);  // 0x6B4A78
        v0 = lui(0x6Bu);
        lwc1(0, v0, 19072);  // 0x6B4A80
        sd(sp, 224, v1);
        swc1(0, sp, 232);
        a2 = lui(0x6Bu);
        a2 = addiu(a2, 19088);  // 0x6B4A90
        a1 = addiu(sp, 96);
        a0 = si(4);
        for (;;) {
            charge(9);
            v1 = lw(a2, 0);
            v0 = lw(a2, 4);
            a2 = addiu(a2, 8);
            a0 = addiu(a0, -1);
            sw(a1, 0, v1);
            sw(a1, 4, v0);
            a1 = addiu(a1, 8);
            if (lez(a0)) break;
            backedge();
        }
        charge(3);
        a0 = 0;
        for (;;) {
            charge(3);
            v0 = slti(a0, 4);
            if (v0 == 0) break;
            backedge();
            charge(14);
            v0 = sll(a0, 3);
            v0 = addu(v0, sp);
            v1 = addiu(v0, 96);
            v0 = sll(a0, 1);
            v0 = addu(v0, a0);
            v0 = sll(v0, 2);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 176);
            lwc1(0, v1, 0);
            swc1(0, v0, 0);
            lwc1(0, v1, 4);
            swc1(0, v0, 8);
            sw(v0, 4, zero);
            a0 = addiu(a0, 1);
        }
        charge(8);
        jal(0x4562B0u, &gen::fn_sub_4C38C0_004c38c0);
        s2 = v0;
        mtc1(zero, 0);
        c_lt_s(20, 0);
        if (!cond()) {
            charge(6);
            v0 = lui(0x4334u);
            mtc1(v0, 0);  // 180f
            sub_s(20, 20, 0);
        } else {
            charge(4);
            v0 = lui(0x4334u);
            mtc1(v0, 0);  // 180f
            add_s(20, 20, 0);
        }
        charge(10);
        lwc1(0, s0, 312);
        add_s(12, 20, 0);
        a0 = s2;
        a1 = addiu(sp, 224);
        a2 = si(2);
        jal(0x45630Cu, &gen::fn_sub_4C31B0_004c31b0);
        s1 = 0;
        for (;;) {
            charge(3);
            v0 = slti(s1, 4);
            if (v0 == 0) break;
            backedge();
            charge(21);
            v0 = sll(s1, 1);
            v0 = addu(v0, s1);
            v0 = sll(v0, 2);
            v0 = addu(v0, sp);
            s3 = addiu(v0, 128);
            a0 = s3;
            a1 = addiu(v0, 176);
            a2 = s2;
            jal(0x456340u, &gen::fn_sub_4C6BE0_004c6be0);
            v0 = sll(s1, 6);
            v0 = addu(s0, v0);
            lwc1(1, s0, 288);
            lwc1(0, s3, 0);
            add_s(0, 1, 0);
            swc1(0, v0, 16);
            lwc1(1, s0, 292);
            lwc1(0, s3, 8);
            add_s(0, 1, 0);
            swc1(0, v0, 20);
            s1 = addiu(s1, 1);
        }
        charge(12);
        a0 = s2;
        jal(0x456384u, &gen::fn_sub_4C3880_004c3880);
        ra = ld(sp, 80);
        lq(s3, sp, 64);
        lq(s2, sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(20, sp, 0);
        sp = addiu(sp, 240);
    }

    // 0x4563B0 (task; $f12): the symbol-direction work's angle +312.
    void sub_4563B0() {
        enter(4);
        v1 = lw(a0, kTaskWork);
        swc1(12, v1, 312);
    }

    // 0x4563C0 (task, floor): +300 = (u8) floor.
    void sub_4563C0() {
        enter(4);
        v1 = lw(a0, kTaskWork);
        sb(v1, 300, a1);
    }

    // 0x4563D0 (task, xy): +304 / +308 = the two f32 of $a1 (spilled to sp+8, copied through $f1 / $f0).
    void sub_4563D0() {
        enter(10);
        sp = addiu(sp, -16);
        sd(sp, 8, a1);
        v1 = lw(a0, kTaskWork);
        lwc1(1, sp, 8);
        lwc1(0, sp, 12);
        swc1(1, v1, 304);
        swc1(0, v1, 308);
        sp = addiu(sp, 16);
    }

    // 0x456400 (task, value): +328 = (u8) value.
    void sub_456400() {
        enter(4);
        v1 = lw(a0, kTaskWork);
        sb(v1, 328, a1);
    }

    // 0x456410 .. 0x456620 (pc): party member pc's think work (gFldUnitsPc[pc] +364 -> +60): mode +4704 = 0 .. 7 (one
    // function each), the change flag +4631 = 1, +4662 = 0.
    void sub_456410() {
        enter(16);
        a0 = dsll32(a0, 24);
        a0 = dsra32(a0, 24);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, 6412);  // 0x87190C
        v1 = addu(v1, a0);
        v1 = lw(v1, 0);
        a0 = lw(v1, kTaskWork);
        sb(a0, 4704, zero);
        v1 = si(1);
        sb(a0, 4631, v1);
        sb(a0, 4662, zero);
    }

    // 0x456450 (pc): mode 1.
    void sub_456450() {
        enter(16);
        a0 = dsll32(a0, 24);
        a0 = dsra32(a0, 24);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, 6412);  // 0x87190C
        v1 = addu(v1, a0);
        v1 = lw(v1, 0);
        a0 = lw(v1, kTaskWork);
        v1 = si(1);
        sb(a0, 4704, v1);
        sb(a0, 4631, v1);
        sb(a0, 4662, zero);
    }

    // 0x456490 (pc): mode 2.
    void sub_456490() {
        enter(17);
        a0 = dsll32(a0, 24);
        a0 = dsra32(a0, 24);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, 6412);  // 0x87190C
        v1 = addu(v1, a0);
        v1 = lw(v1, 0);
        a0 = lw(v1, kTaskWork);
        v1 = si(2);
        sb(a0, 4704, v1);
        v1 = si(1);
        sb(a0, 4631, v1);
        sb(a0, 4662, zero);
    }

    // 0x4564E0 (pc): mode 3.
    void sub_4564E0() {
        enter(17);
        a0 = dsll32(a0, 24);
        a0 = dsra32(a0, 24);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, 6412);  // 0x87190C
        v1 = addu(v1, a0);
        v1 = lw(v1, 0);
        a0 = lw(v1, kTaskWork);
        v1 = si(3);
        sb(a0, 4704, v1);
        v1 = si(1);
        sb(a0, 4631, v1);
        sb(a0, 4662, zero);
    }

    // 0x456530 (pc): mode 4.
    void sub_456530() {
        enter(17);
        a0 = dsll32(a0, 24);
        a0 = dsra32(a0, 24);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, 6412);  // 0x87190C
        v1 = addu(v1, a0);
        v1 = lw(v1, 0);
        a0 = lw(v1, kTaskWork);
        v1 = si(4);
        sb(a0, 4704, v1);
        v1 = si(1);
        sb(a0, 4631, v1);
        sb(a0, 4662, zero);
    }

    // 0x456580 (pc): mode 5.
    void sub_456580() {
        enter(17);
        a0 = dsll32(a0, 24);
        a0 = dsra32(a0, 24);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, 6412);  // 0x87190C
        v1 = addu(v1, a0);
        v1 = lw(v1, 0);
        a0 = lw(v1, kTaskWork);
        v1 = si(5);
        sb(a0, 4704, v1);
        v1 = si(1);
        sb(a0, 4631, v1);
        sb(a0, 4662, zero);
    }

    // 0x4565D0 (pc): mode 6.
    void sub_4565D0() {
        enter(17);
        a0 = dsll32(a0, 24);
        a0 = dsra32(a0, 24);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, 6412);  // 0x87190C
        v1 = addu(v1, a0);
        v1 = lw(v1, 0);
        a0 = lw(v1, kTaskWork);
        v1 = si(6);
        sb(a0, 4704, v1);
        v1 = si(1);
        sb(a0, 4631, v1);
        sb(a0, 4662, zero);
    }

    // 0x456620 (pc): mode 7.
    void sub_456620() {
        enter(17);
        a0 = dsll32(a0, 24);
        a0 = dsra32(a0, 24);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, 6412);  // 0x87190C
        v1 = addu(v1, a0);
        v1 = lw(v1, 0);
        a0 = lw(v1, kTaskWork);
        v1 = si(7);
        sb(a0, 4704, v1);
        v1 = si(1);
        sb(a0, 4631, v1);
        sb(a0, 4662, zero);
    }

    // 0x457340 (pc, kind, target): party member pc's skill use: +4664 = 1, +4663 = 0, +4665 = kind, s16 +4646 = target.
    void sub_457340() {
        enter(19);
        a0 = dsll32(a0, 24);
        a0 = dsra32(a0, 24);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, 6412);  // 0x87190C
        v1 = addu(v1, a0);
        v1 = lw(v1, 0);
        a0 = lw(v1, kTaskWork);
        v1 = si(1);
        sb(a0, 4664, v1);
        sb(a0, 4663, zero);
        sb(a0, 4665, a1);
        v1 = dsll32(a2, 24);
        v1 = dsra32(v1, 24);
        sh(a0, 4646, v1);
    }

    // 0x457390 (pc): the s8 +4665 of pc's think work.
    void sub_457390() {
        enter(13);
        v1 = dsll32(a0, 24);
        v1 = dsra32(v1, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, 6412);  // 0x87190C
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        v0 = lw(v0, kTaskWork);
        v0 = lb(v0, 4665);
    }

    // 0x4573D0 (pc): the s8 at +4646 (the low byte of the s16 target).
    void sub_4573D0() {
        enter(13);
        v1 = dsll32(a0, 24);
        v1 = dsra32(v1, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, 6412);  // 0x87190C
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        v0 = lw(v0, kTaskWork);
        v0 = lb(v0, 4646);
    }

    // 0x457410: the address of the first of the four 448-byte NPC units at 0x86E6A0 whose +72 is 0; 0 when all are used.
    void sub_457410() {
        enter(6);
        v0 = 0;
        a2 = 0;
        a1 = lui(0x87u);
        a1 = addiu(a1, -6496);  // 0x86E6A0
        for (;;) {
            charge(3);
            v1 = slti(a2, 4);
            if (v1 == 0) break;
            backedge();
            charge(7);
            v1 = sll(a2, 3);
            v1 = subu(v1, a2);
            v1 = sll(v1, 6);
            a0 = addu(a1, v1);
            v1 = lw(a0, 72);
            if (v1 == 0) {
                charge(3);
                v0 = a0;
                break;
            }
            charge(1);
            a2 = addiu(a2, 1);
        }
        charge(2);
    }

    // 0x457470 (slot): NPC unit 0x86E6A0 + 448 slot: unused or already with a resource -> 1; while its model streams
    // (mdlStreamRead sub_316F70 of +80) -> 0; when it is in: a character resource (MT_Scene_CreateResModelChar sub_3B6030(slot
    // + 10, 0, model)), +84 = MT_Scene_GetRes (sub_3B5D10), the model's animation (sub_3182D0(model, 0, 0, 16, 1)), the
    // controller turned by the axis 0x6B4B20 (sub_1ADFF0), placed at the unit's +360 -> +256 (sub_1ADC20), the resource's
    // draw flag (sub_1A0DC0(id, 1)), the controller flag 0x40000000 (sub_1AD870) and a collision mover (sub_1AF930) -> +368; 1.
    void sub_457470() {
        enter(20);
        sp = addiu(sp, -64);
        sd(sp, 32, ra);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s1 = a0;
        v0 = lui(0x6Bu);
        v1 = ld(v0, 19232);  // 0x6B4B20
        v0 = lui(0x6Bu);
        lwc1(0, v0, 19240);  // 0x6B4B28
        sd(sp, 48, v1);
        swc1(0, sp, 56);
        v0 = sll(s1, 3);
        v0 = subu(v0, s1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -6496);  // 0x86E6A0
        s0 = addu(v0, v1);
        v0 = lw(s0, 72);
        if (v0 == 0) {
            charge(3);
            v0 = si(1);
        } else {
            charge(3);
            v0 = lw(s0, 84);
            if (v0 != 0) {
                charge(3);
                v0 = si(1);
            } else {
                charge(5);
                a0 = lw(s0, 80);
                jal(0x4574E8u, &gen::fn_sub_316F70_00316f70);
                if (v0 == 0) {
                    charge(3);
                    v0 = 0;
                } else {
                    charge(46);
                    v0 = addiu(s1, 10);
                    a0 = v0 & 0xFFFFu;
                    a1 = 0;
                    a2 = lw(s0, 80);
                    jal(0x457514u, &gen::fn_sub_3B6030_003b6030);
                    a0 = v0 & 0xFFFFu;
                    jal(0x457520u, &gen::fn_sub_3B5D10_003b5d10);
                    sw(s0, 84, v0);
                    a0 = lw(s0, 80);
                    a1 = 0;
                    a2 = 0;
                    a3 = si(16);
                    a4 = si(1);
                    jal(0x457540u, &gen::fn_sub_3182D0_003182d0);
                    v1 = lw(s0, 84);
                    v0 = lw(s0, 360);
                    a0 = lw(v1, kResController);
                    a1 = addiu(sp, 48);
                    lwc1(12, v0, 268);
                    jal(0x45755Cu, &gen::fn_sub_1ADFF0_001adff0);
                    v1 = lw(s0, 84);
                    v0 = lw(s0, 360);
                    a0 = lw(v1, kResController);
                    a1 = addiu(v0, 256);
                    jal(0x457574u, &gen::fn_sub_1ADC20_001adc20);
                    v0 = lw(s0, 84);
                    a0 = lhu(v0, 0);
                    a1 = si(1);
                    jal(0x457588u, &gen::fn_sub_1A0DC0_001a0dc0);
                    v0 = lw(s0, 84);
                    a0 = lw(v0, kResController);
                    a1 = lui(0x4000u);
                    jal(0x45759Cu, &gen::fn_sub_1AD870_001ad870);
                    a0 = 0;
                    a1 = lw(s0, 84);
                    jal(0x4575ACu, &gen::fn_sub_1AF930_001af930);
                    sw(s0, 368, v0);
                    v0 = si(1);
                }
            }
        }
        charge(6);
        ra = ld(sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 64);
    }
};

struct SymBig : SymLeaves {
    using SymLeaves::SymLeaves;

    // 0x454F50 (ec, pc): the pursuit step of sub-state 24: clears the queue, then by RpRandom() % 100 (>= 50: from the
    // member to the shadow, else the other way) normalises the line between them (RwV3dNormalize sub_4C69F0); 300 or more
    // apart: the point 400 along the turned axis 0x6B4A48; closer: 400 past the member, tested with the ground ray (kind 4
    // passes) and, when bad, retried along the other direction. The mover's speed is reset (sub_1B0250(.., 0)); a point
    // inside the behaviour range with good ground is walked to (sub_1AFA20), else sub_454A70 tries a range-long step; either
    // success sets sub-state 25 and plays SFX (1, 8, 3, 6) (sub_10A4E0).
    void sub_454F50() {
        enter(55);
        sp = addiu(sp, -800);
        sd(sp, 96, ra);
        sq(s4, sp, 80);
        sq(s3, sp, 64);
        sq(s2, sp, 48);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(23, sp, 12);
        swc1(22, sp, 8);
        swc1(21, sp, 4);
        swc1(20, sp, 0);
        s3 = a1;
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
        v0 = lui(0x6Bu);
        v1 = ld(v0, 19016);  // 0x6B4A48
        v0 = lui(0x6Bu);
        lwc1(0, v0, 19024);  // 0x6B4A50
        sd(sp, 768, v1);
        swc1(0, sp, 776);
        v1 = lb(s2, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        a0 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4308);  // 0x86EF2C
        v0 = addu(v0, a0);
        v0 = lw(v0, 0);
        v1 = sll(v0, 6);
        v0 = lw(gp, -19040);
        s1 = addu(v0, v1);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4336);  // 0x86EF10
        v0 = addu(v0, a0);
        a0 = lw(v0, 0);
        jal(0x454FFCu, &gen::fn_sub_1B00C0_001b00c0);
        jal(0x455004u, &gen::fn_sub_488F30_00488f30);
        v1 = si(100);
        divu(v0, v1);
        mfhi(v0);
        s0 = dsll32(v0, 16);
        s0 = dsra32(s0, 16);
        at = slti(s0, 50);
        if (at != 0) {
            charge(73);
            v1 = dsll32(s3, 24);
            v1 = dsra32(v1, 24);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, 6132);  // 0x8717F4
            s4 = addu(v0, v1);
            v1 = lb(s2, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4620);  // 0x86EDF4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 736);
            a1 = lw(v0, kResController);
            jal(0x455074u, &gen::fn_sub_1AD940_001ad940);
            lwc1(20, sp, 736);
            v0 = lw(s4, 0);
            a0 = addiu(sp, 720);
            a1 = lw(v0, kResController);
            jal(0x45508Cu, &gen::fn_sub_1AD940_001ad940);
            lwc1(0, sp, 720);
            sub_s(0, 20, 0);
            swc1(0, sp, 784);
            v1 = lb(s2, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4620);  // 0x86EDF4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 704);
            a1 = lw(v0, kResController);
            jal(0x4550C8u, &gen::fn_sub_1AD940_001ad940);
            lwc1(20, sp, 708);
            v0 = lw(s4, 0);
            a0 = addiu(sp, 688);
            a1 = lw(v0, kResController);
            jal(0x4550E0u, &gen::fn_sub_1AD940_001ad940);
            lwc1(0, sp, 692);
            sub_s(0, 20, 0);
            swc1(0, sp, 788);
            v1 = lb(s2, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4620);  // 0x86EDF4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 672);
            a1 = lw(v0, kResController);
            jal(0x45511Cu, &gen::fn_sub_1AD940_001ad940);
            lwc1(20, sp, 680);
            v0 = lw(s4, 0);
            a0 = addiu(sp, 656);
            a1 = lw(v0, kResController);
            jal(0x455134u, &gen::fn_sub_1AD940_001ad940);
            lwc1(0, sp, 664);
            sub_s(0, 20, 0);
            swc1(0, sp, 792);
        } else {
            charge(71);
            v1 = dsll32(s3, 24);
            v1 = dsra32(v1, 24);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, 6132);  // 0x8717F4
            s4 = addu(v0, v1);
            v1 = lb(s2, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4620);  // 0x86EDF4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 624);
            a1 = lw(v0, kResController);
            jal(0x455198u, &gen::fn_sub_1AD940_001ad940);
            lwc1(20, sp, 624);
            v0 = lw(s4, 0);
            a0 = addiu(sp, 640);
            a1 = lw(v0, kResController);
            jal(0x4551B0u, &gen::fn_sub_1AD940_001ad940);
            lwc1(0, sp, 640);
            sub_s(0, 0, 20);
            swc1(0, sp, 784);
            v1 = lb(s2, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4620);  // 0x86EDF4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 592);
            a1 = lw(v0, kResController);
            jal(0x4551ECu, &gen::fn_sub_1AD940_001ad940);
            lwc1(20, sp, 596);
            v0 = lw(s4, 0);
            a0 = addiu(sp, 608);
            a1 = lw(v0, kResController);
            jal(0x455204u, &gen::fn_sub_1AD940_001ad940);
            lwc1(0, sp, 612);
            sub_s(0, 0, 20);
            swc1(0, sp, 788);
            v1 = lb(s2, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4620);  // 0x86EDF4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 560);
            a1 = lw(v0, kResController);
            jal(0x455240u, &gen::fn_sub_1AD940_001ad940);
            lwc1(20, sp, 568);
            v0 = lw(s4, 0);
            a0 = addiu(sp, 576);
            a1 = lw(v0, kResController);
            jal(0x455258u, &gen::fn_sub_1AD940_001ad940);
            lwc1(0, sp, 584);
            sub_s(0, 0, 20);
            swc1(0, sp, 792);
        }
        charge(10);
        a0 = addiu(sp, 784);
        a1 = a0;
        jal(0x455274u, &gen::fn_sub_4C69F0_004c69f0);
        v0 = lui(0x4396u);
        mtc1(v0, 1);  // 300f
        c_lt_s(0, 1);
        if (cond()) {
            charge(173);
            v1 = dsll32(s3, 24);
            v1 = dsra32(v1, 24);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, 6132);  // 0x8717F4
            s4 = addu(v0, v1);
            v1 = lb(s2, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4620);  // 0x86EDF4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 544);
            a1 = lw(v0, kResController);
            jal(0x4552DCu, &gen::fn_sub_1AD940_001ad940);
            lwc1(20, sp, 544);
            v0 = lw(s4, 0);
            a0 = addiu(sp, 528);
            a1 = lw(v0, kResController);
            jal(0x4552F4u, &gen::fn_sub_1AD940_001ad940);
            lwc1(0, sp, 528);
            sub_s(0, 20, 0);
            swc1(0, sp, 784);
            v1 = lb(s2, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4620);  // 0x86EDF4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 512);
            a1 = lw(v0, kResController);
            jal(0x455330u, &gen::fn_sub_1AD940_001ad940);
            lwc1(20, sp, 516);
            v0 = lw(s4, 0);
            a0 = addiu(sp, 496);
            a1 = lw(v0, kResController);
            jal(0x455348u, &gen::fn_sub_1AD940_001ad940);
            lwc1(0, sp, 500);
            sub_s(0, 20, 0);
            swc1(0, sp, 788);
            v1 = lb(s2, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4620);  // 0x86EDF4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 480);
            a1 = lw(v0, kResController);
            jal(0x455384u, &gen::fn_sub_1AD940_001ad940);
            lwc1(20, sp, 488);
            v0 = lw(s4, 0);
            a0 = addiu(sp, 464);
            a1 = lw(v0, kResController);
            jal(0x45539Cu, &gen::fn_sub_1AD940_001ad940);
            lwc1(0, sp, 472);
            sub_s(0, 20, 0);
            swc1(0, sp, 792);
            a0 = addiu(sp, 784);
            a1 = a0;
            jal(0x4553B8u, &gen::fn_sub_4C69F0_004c69f0);
            v0 = lui(0x43C8u);
            mtc1(v0, 20);  // 400.0
            lwc1(0, sp, 784);
            mul_s(23, 20, 0);
            lwc1(0, sp, 788);
            mul_s(22, 20, 0);
            lwc1(0, sp, 792);
            mul_s(21, 20, 0);
            v1 = lb(s2, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4620);  // 0x86EDF4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 448);
            a1 = lw(v0, kResController);
            jal(0x455408u, &gen::fn_sub_1AD940_001ad940);
            lwc1(0, sp, 448);
            add_s(0, 23, 0);
            swc1(0, sp, 752);
            v1 = lb(s2, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4620);  // 0x86EDF4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 432);
            a1 = lw(v0, kResController);
            jal(0x455444u, &gen::fn_sub_1AD940_001ad940);
            lwc1(0, sp, 436);
            add_s(0, 22, 0);
            swc1(0, sp, 756);
            v1 = lb(s2, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4620);  // 0x86EDF4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 416);
            a1 = lw(v0, kResController);
            jal(0x455480u, &gen::fn_sub_1AD940_001ad940);
            lwc1(0, sp, 424);
            add_s(0, 21, 0);
            swc1(0, sp, 760);
            v1 = lb(s2, 1);
            v0 = ld(sp, 752);
            lwc1(0, sp, 760);
            sd(sp, 192, v0);
            swc1(0, sp, 200);
            a1 = addiu(sp, 256);
            v0 = ld(sp, 192);
            lwc1(2, sp, 200);
            sd(sp, 256, v0);
            swc1(2, sp, 264);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4340);  // 0x86EF0C
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            v1 = lw(v0, kTaskWork);
            lwc1(1, sp, 192);
            lwc1(0, sp, 196);
            swc1(1, sp, 156);
            swc1(0, sp, 160);
            swc1(2, sp, 164);
            a0 = addiu(sp, 144);
            lwc1(2, sp, 156);
            lwc1(1, sp, 160);
            lwc1(0, sp, 164);
            swc1(2, sp, 144);
            swc1(1, sp, 148);
            swc1(0, sp, 152);
            v0 = lui(0x43C8u);
            sw(sp, 148, v0);
            v0 = lui(0xC3C8u);
            sw(sp, 160, v0);
            v1 = lb(v1, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4308);  // 0x86EF2C
            v0 = addu(v0, v1);
            v1 = lw(v0, 0);
            v0 = si(4);
            if (v1 == v0) {
                charge(3);
                v1 = si(1);
            } else {
                charge(5);
                jal(0x455554u, &gen::fn_sub_1ACC30_001acc30);
                v1 = si(1);
                if (v0 == v1) {
                    charge(7);
                    lwc1(1, sp, 260);
                    v0 = lui(0x4248u);
                    mtc1(v0, 0);  // 50f
                    c_le_s(1, 0);
                    if (!cond()) {
                        goto L_00455598;
                    }
                    charge(2);
                    goto L_0045559c;
                }
                charge(3);
                v1 = 0;
                goto L_0045559c;
              L_00455598:
                charge(1);
                v1 = 0;
            }
          L_0045559c:
            charge(2);
            if (v1 == 0) {
                charge(12);
                v1 = lb(s2, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4620);  // 0x86EDF4
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 752);
                a1 = lw(v0, kResController);
                jal(0x4555CCu, &gen::fn_sub_1AD940_001ad940);
            }
            charge(3);
            at = slti(s0, 50);
            if (at != 0) {
                charge(37);
                v1 = dsll32(s3, 24);
                v1 = dsra32(v1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6132);  // 0x8717F4
                s0 = addu(v0, v1);
                v0 = lw(s0, 0);
                a0 = addiu(sp, 400);
                a1 = lw(v0, kResController);
                jal(0x45560Cu, &gen::fn_sub_1AD940_001ad940);
                lwc1(1, sp, 400);
                lwc1(0, sp, 752);
                sub_s(0, 0, 1);
                swc1(0, sp, 784);
                v0 = lw(s0, 0);
                a0 = addiu(sp, 384);
                a1 = lw(v0, kResController);
                jal(0x455630u, &gen::fn_sub_1AD940_001ad940);
                lwc1(1, sp, 388);
                lwc1(0, sp, 756);
                sub_s(0, 0, 1);
                swc1(0, sp, 788);
                v0 = lw(s0, 0);
                a0 = addiu(sp, 368);
                a1 = lw(v0, kResController);
                jal(0x455654u, &gen::fn_sub_1AD940_001ad940);
                lwc1(1, sp, 376);
                lwc1(0, sp, 760);
                sub_s(0, 0, 1);
                swc1(0, sp, 792);
            } else {
                charge(35);
                v1 = dsll32(s3, 24);
                v1 = dsra32(v1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6132);  // 0x8717F4
                s0 = addu(v0, v1);
                v0 = lw(s0, 0);
                a0 = addiu(sp, 352);
                a1 = lw(v0, kResController);
                jal(0x4556A0u, &gen::fn_sub_1AD940_001ad940);
                lwc1(1, sp, 352);
                lwc1(0, sp, 752);
                sub_s(0, 1, 0);
                swc1(0, sp, 784);
                v0 = lw(s0, 0);
                a0 = addiu(sp, 336);
                a1 = lw(v0, kResController);
                jal(0x4556C4u, &gen::fn_sub_1AD940_001ad940);
                lwc1(1, sp, 340);
                lwc1(0, sp, 756);
                sub_s(0, 1, 0);
                swc1(0, sp, 788);
                v0 = lw(s0, 0);
                a0 = addiu(sp, 320);
                a1 = lw(v0, kResController);
                jal(0x4556E8u, &gen::fn_sub_1AD940_001ad940);
                lwc1(1, sp, 328);
                lwc1(0, sp, 760);
                sub_s(0, 1, 0);
                swc1(0, sp, 792);
            }
            charge(33);
            a0 = addiu(sp, 784);
            a1 = a0;
            jal(0x455708u, &gen::fn_sub_4C69F0_004c69f0);
            lwc1(6, sp, 772);
            lwc1(5, sp, 792);
            lwc1(2, sp, 776);
            lwc1(4, sp, 788);
            mula_s(4, 2);
            msub_s(3, 5, 6);
            lwc1(1, sp, 784);
            lwc1(0, sp, 768);
            mula_s(5, 0);
            msub_s(2, 1, 2);
            mula_s(1, 6);
            msub_s(1, 4, 0);
            v0 = lui(0x43C8u);
            mtc1(v0, 0);  // 400.0
            mul_s(3, 3, 0);
            mul_s(2, 2, 0);
            mul_s(1, 1, 0);
            lwc1(0, sp, 752);
            add_s(0, 0, 3);
            swc1(0, sp, 752);
            lwc1(0, sp, 756);
            add_s(0, 0, 2);
            swc1(0, sp, 756);
            lwc1(0, sp, 760);
            add_s(0, 0, 1);
            swc1(0, sp, 760);
        } else {
            charge(63);
            lwc1(6, sp, 772);
            lwc1(5, sp, 792);
            lwc1(1, sp, 776);
            lwc1(4, sp, 788);
            mula_s(4, 1);
            msub_s(3, 5, 6);
            lwc1(2, sp, 784);
            lwc1(0, sp, 768);
            mula_s(5, 0);
            msub_s(1, 2, 1);
            mula_s(2, 6);
            msub_s(0, 4, 0);
            v0 = lui(0x43C8u);
            mtc1(v0, 20);  // 400.0
            mul_s(23, 3, 20);
            mul_s(22, 1, 20);
            mul_s(21, 0, 20);
            v1 = lb(s2, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4620);  // 0x86EDF4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 304);
            a1 = lw(v0, kResController);
            jal(0x4557F4u, &gen::fn_sub_1AD940_001ad940);
            lwc1(0, sp, 304);
            add_s(0, 23, 0);
            swc1(0, sp, 752);
            v1 = lb(s2, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4620);  // 0x86EDF4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 288);
            a1 = lw(v0, kResController);
            jal(0x455830u, &gen::fn_sub_1AD940_001ad940);
            lwc1(0, sp, 292);
            add_s(0, 22, 0);
            swc1(0, sp, 756);
            v1 = lb(s2, 1);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, -4620);  // 0x86EDF4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 272);
            a1 = lw(v0, kResController);
            jal(0x45586Cu, &gen::fn_sub_1AD940_001ad940);
            lwc1(0, sp, 280);
            add_s(0, 21, 0);
            swc1(0, sp, 760);
        }
        charge(59);
        v1 = lb(s2, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4336);  // 0x86EF10
        v0 = addu(v0, v1);
        a0 = lw(v0, 0);
        a1 = 0;
        jal(0x4558A4u, &gen::fn_sub_1B0250_001b0250);
        v0 = ld(sp, 752);
        lwc1(0, sp, 760);
        sd(sp, 240, v0);
        swc1(0, sp, 248);
        v1 = lb(s2, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4340);  // 0x86EF0C
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        v0 = lw(v0, kTaskWork);
        s3 = 0;
        v1 = lb(v0, 1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        a0 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4308);  // 0x86EF2C
        v0 = addu(v0, a0);
        v0 = lw(v0, 0);
        v1 = sll(v0, 6);
        v0 = lw(gp, -19040);
        s0 = addu(v0, v1);
        v0 = lui(0x87u);
        v0 = addiu(v0, -4344);  // 0x86EF08
        v0 = addu(v0, a0);
        v0 = lw(v0, 0);
        lwc1(1, v0, 256);
        lwc1(0, sp, 240);
        sub_s(0, 1, 0);
        swc1(0, sp, 224);
        lwc1(1, v0, 260);
        lwc1(0, sp, 244);
        sub_s(0, 1, 0);
        swc1(0, sp, 228);
        lwc1(1, v0, 264);
        lwc1(0, sp, 248);
        sub_s(0, 1, 0);
        swc1(0, sp, 232);
        a0 = addiu(sp, 224);
        jal(0x455954u, &gen::fn_sub_4C6AC0_004c6ac0);
        lwc1(1, s0, 0);
        c_lt_s(0, 1);
        if (cond()) {
            charge(1);
            s3 = si(1);
        }
        charge(2);
        if (s3 == 0) {
            charge(7);
            a0 = lb(s2, 1);
            a1 = addiu(sp, 752);
            jal(0x455980u, &gen::fn_sub_454A70_00454a70);
            a0 = si(1);
            if (v0 == a0) {
                charge(9);
                v0 = si(25);
                sb(s2, 3, v0);
                a1 = si(8);
                a2 = si(3);
                a3 = si(6);
                jal(0x4559A8u, &gen::fn_sub_10A4E0_0010a4e0);
            }
        } else {
            charge(44);
            a0 = lb(s2, 1);
            v1 = ld(sp, 752);
            lwc1(0, sp, 760);
            sd(sp, 176, v1);
            swc1(0, sp, 184);
            a1 = addiu(sp, 208);
            v1 = ld(sp, 176);
            lwc1(2, sp, 184);
            sd(sp, 208, v1);
            swc1(2, sp, 216);
            v1 = sll(a0, 3);
            v1 = subu(v1, a0);
            a0 = sll(v1, 6);
            v1 = lui(0x87u);
            v1 = addiu(v1, -4340);  // 0x86EF0C
            v1 = addu(v1, a0);
            v1 = lw(v1, 0);
            a2 = lw(v1, kTaskWork);
            lwc1(1, sp, 176);
            lwc1(0, sp, 180);
            swc1(1, sp, 124);
            swc1(0, sp, 128);
            swc1(2, sp, 132);
            a0 = addiu(sp, 112);
            lwc1(2, sp, 124);
            lwc1(1, sp, 128);
            lwc1(0, sp, 132);
            swc1(2, sp, 112);
            swc1(1, sp, 116);
            swc1(0, sp, 120);
            swc1(20, sp, 116);
            v1 = lui(0xC3C8u);
            sw(sp, 128, v1);
            a2 = lb(a2, 1);
            v1 = sll(a2, 3);
            v1 = subu(v1, a2);
            a2 = sll(v1, 6);
            v1 = lui(0x87u);
            v1 = addiu(v1, -4308);  // 0x86EF2C
            v1 = addu(v1, a2);
            a2 = lw(v1, 0);
            v1 = si(4);
            if (a2 == v1) {
                charge(3);
                a0 = si(1);
            } else {
                charge(5);
                jal(0x455A74u, &gen::fn_sub_1ACC30_001acc30);
                a0 = si(1);
                if (v0 == a0) {
                    charge(7);
                    lwc1(1, sp, 212);
                    v1 = lui(0x4248u);
                    mtc1(v1, 0);  // 50f
                    c_le_s(1, 0);
                    if (!cond()) {
                        goto L_00455ab8;
                    }
                    charge(2);
                    goto L_00455abc;
                }
                charge(3);
                a0 = 0;
                goto L_00455abc;
              L_00455ab8:
                charge(1);
                a0 = 0;
            }
          L_00455abc:
            charge(3);
            v1 = si(1);
            if (a0 == v1) {
                charge(20);
                v1 = lb(s2, 1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, -4336);  // 0x86EF10
                v0 = addu(v0, v1);
                a0 = lw(v0, 0);
                a1 = addiu(sp, 752);
                lwc1(12, s1, 12);
                jal(0x455AF0u, &gen::fn_sub_1AFA20_001afa20);
                v0 = si(25);
                sb(s2, 3, v0);
                a0 = si(1);
                a1 = si(8);
                a2 = si(3);
                a3 = si(6);
                jal(0x455B10u, &gen::fn_sub_10A4E0_0010a4e0);
            }
        }
        charge(13);
        ra = ld(sp, 96);
        lq(s4, sp, 80);
        lq(s3, sp, 64);
        lq(s2, sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(23, sp, 12);
        lwc1(22, sp, 8);
        lwc1(21, sp, 4);
        lwc1(20, sp, 0);
        sp = addiu(sp, 800);
    }

    // 0x456EA0 (_, pc, target): unless another member already aims a kind-4 skill at the target (sub_4573D0 / sub_457390),
    // pc's support skill for the target (sub_43BDA0) is used: the EPL between the target's two hand points (sub_318ED0 of
    // its model, 80 below their middle) through sub_1A9760 on sField +16 (SFX 1, 8, 3, 2 near the hero, else effect
    // parameters 3 / 2), the target's label (sub_18BEE0 on sField +40 when present), the skill applied (sub_17B860), the
    // target's idle animation when alive (sub_1DDE00 / sub_3182D0), the HP or SP cost by the skill's cost kind (sub_17B500:
    // 1 HP via sub_16C4F0 / datSetHp, 2 SP via sub_16C570 / sub_16CF90, cost sub_17B5B0), and sub_457340(pc, 4, target).
    void sub_456EA0() {
        enter(27);
        sp = addiu(sp, -208);
        sd(sp, 128, ra);
        sq(s7, sp, 112);
        sq(s6, sp, 96);
        sq(s5, sp, 80);
        sq(s4, sp, 64);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s5 = a1;
        s4 = a2;
        s2 = dsll32(s5, 24);
        s2 = dsra32(s2, 24);
        v0 = sll(s2, 3);
        v0 = subu(v0, s2);
        s1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, 6412);  // 0x87190C
        v0 = addu(v0, s1);
        v0 = lw(v0, 0);
        s7 = lw(v0, kTaskWork);
        s3 = si(1);
        s0 = dsll32(s4, 24);
        s0 = dsra32(s0, 24);
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
                charge(2);
                if (s3 != s2) {
                    charge(8);
                    a0 = dsll32(s3, 24);
                    a0 = dsra32(a0, 24);
                    jal(0x456F64u, &gen::fn_sub_4573D0_004573d0);
                    v0 = dsll32(v0, 24);
                    v0 = dsra32(v0, 24);
                    if (s0 == v0) {
                        charge(9);
                        a0 = dsll32(s3, 24);
                        a0 = dsra32(a0, 24);
                        jal(0x456F84u, &gen::fn_sub_457390_00457390);
                        a0 = dsll32(v0, 24);
                        a0 = dsra32(a0, 24);
                        v1 = si(4);
                        if (a0 == v1) {
                            charge(12);
                            ra = ld(sp, 128);
                            lq(s7, sp, 112);
                            lq(s6, sp, 96);
                            lq(s5, sp, 80);
                            lq(s4, sp, 64);
                            lq(s3, sp, 48);
                            lq(s2, sp, 32);
                            lq(s1, sp, 16);
                            lq(s0, sp, 0);
                            sp = addiu(sp, 208);
                            return;
                        }
                    }
                }
            }
            charge(1);
            s3 = addiu(s3, 1);
        }
        charge(9);
        a0 = s5;
        a1 = s4;
        jal(0x456FB8u, &gen::fn_sub_43BDA0_0043bda0);
        a0 = dsll32(v0, 16);
        a0 = dsra32(a0, 16);
        v1 = si(-1);
        if (a0 != v1) {
            charge(58);
            v1 = dsll32(s4, 24);
            v1 = dsra32(v1, 24);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            s0 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, 6132);  // 0x8717F4
            s6 = addu(v0, s0);
            v0 = lw(s6, 0);
            a0 = addiu(sp, 144);
            a1 = lw(v0, kResController);
            jal(0x457000u, &gen::fn_sub_1AD940_001ad940);
            lwc1(2, sp, 144);
            lwc1(1, sp, 148);
            lwc1(0, sp, 152);
            swc1(2, sp, 192);
            swc1(1, sp, 196);
            swc1(0, sp, 200);
            s2 = si(-1);
            s3 = s2;
            v0 = lw(s6, 0);
            a0 = lw(v0, 296);
            a1 = si(2);
            a2 = addiu(sp, 176);
            jal(0x457038u, &gen::fn_sub_318ED0_00318ed0);
            lwc1(1, sp, 176);
            lwc1(0, sp, 192);
            add_s(4, 1, 0);
            swc1(4, sp, 160);
            lwc1(1, sp, 180);
            lwc1(0, sp, 196);
            add_s(3, 1, 0);
            swc1(3, sp, 164);
            lwc1(1, sp, 184);
            lwc1(0, sp, 200);
            add_s(2, 1, 0);
            swc1(2, sp, 168);
            v0 = lui(0x4000u);
            mtc1(v0, 1);  // 2.0
            div_s(0, 4, 1);
            swc1(0, sp, 160);
            div_s(0, 3, 1);
            swc1(0, sp, 164);
            div_s(0, 2, 1);
            swc1(0, sp, 168);
            v0 = lui(0x87u);
            v0 = addiu(v0, 6048);  // 0x8717A0 gFldUnitsPc
            a0 = addu(v0, s0);
            v0 = lui(0x4516u);
            mtc1(v0, 12);  // 2400f
            jal(0x4570A8u, &gen::fn_sub_1C7130_001c7130);
            a0 = si(1);
            if (v0 == a0) {
                charge(7);
                a1 = si(8);
                a2 = si(3);
                a3 = si(2);
                jal(0x4570C8u, &gen::fn_sub_10A4E0_0010a4e0);
            } else {
                charge(2);
                s3 = si(3);
                s2 = si(2);
            }
            charge(20);
            lwc1(1, sp, 164);
            v0 = lui(0x42A0u);
            mtc1(v0, 0);  // 80f
            sub_s(0, 1, 0);
            swc1(0, sp, 164);
            jal(0x4570F8u, &gen::fn_K_Field_Get_001b9120);
            a0 = lw(v0, 16);
            a1 = si(2);
            a2 = addiu(sp, 160);
            a3 = s3;
            a4 = s2;
            jal(0x457114u, &gen::fn_sub_1A9760_001a9760);
            jal(0x45711Cu, &gen::fn_K_Field_Get_001b9120);
            v0 = lw(v0, 40);
            if (v0 != 0) {
                charge(10);
                jal(0x457130u, &gen::fn_K_Field_Get_001b9120);
                v1 = lui(0x87u);
                v1 = addiu(v1, 6472);  // 0x871948
                v1 = addu(v1, s0);
                a1 = lhu(v1, 0);
                a0 = lw(v0, 40);
                a2 = 0;
                jal(0x457150u, &gen::fn_sub_18BEE0_0018bee0);
            }
            charge(28);
            a1 = lb(s7, 4646);
            a0 = s5;
            jal(0x457160u, &gen::fn_sub_43BDA0_0043bda0);
            s3 = v0 & 0xFFFFu;
            v1 = dsll32(s4, 24);
            v1 = dsra32(v1, 24);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            s2 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, 6472);  // 0x871948
            s0 = addu(v0, s2);
            s1 = addu(v0, s1);
            a0 = lh(s1, 0);
            a1 = lh(s0, 0);
            a2 = s3;
            a3 = 0;
            jal(0x4571A0u, &gen::fn_sub_17B860_0017b860);
            v0 = lui(0x87u);
            v0 = addiu(v0, 6120);  // 0x8717E8
            v0 = addu(v0, s2);
            a0 = lw(v0, 0);
            jal(0x4571B8u, &gen::fn_datUnitIsGenusDead_002ff790);
            if (v0 == 0) {
                charge(19);
                v1 = dsll32(s4, 24);
                v1 = dsra32(v1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                s2 = sll(v0, 6);
                a0 = lhu(s0, 0);
                jal(0x4571E0u, &gen::fn_sub_1DDE00_001dde00);
                a2 = dsll32(v0, 16);
                a2 = dsra32(a2, 16);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6128);  // 0x8717F0
                v0 = addu(v0, s2);
                a0 = lw(v0, 0);
                a1 = 0;
                a3 = 0;
                a4 = si(1);
                jal(0x45720Cu, &gen::fn_sub_3182D0_003182d0);
            }
            charge(8);
            a0 = lh(s1, 0);
            a1 = s3;
            jal(0x45721Cu, &gen::fn_sub_17B500_0017b500);
            v1 = v0 & 0xFFFFu;
            v0 = si(1);
            if (v1 == v0) {
                charge(24);
                v1 = dsll32(s5, 24);
                v1 = dsra32(v1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6472);  // 0x871948
                s1 = addu(v0, v1);
                a0 = lh(s1, 0);
                jal(0x457258u, &gen::fn_sub_16C4F0_0016c4f0);
                s0 = v0 & 0xFFFFu;
                a0 = lh(s1, 0);
                a1 = s3;
                jal(0x45726Cu, &gen::fn_sub_17B5B0_0017b5b0);
                v0 = subu(s0, v0);
                a1 = dsll32(v0, 16);
                a1 = dsra32(a1, 16);
                a0 = lh(s1, 0);
                jal(0x457284u, &gen::fn_sub_16CF40_0016cf40);
            } else {
                charge(3);
                v0 = si(2);
                if (v1 == v0) {
                    charge(22);
                    v1 = dsll32(s5, 24);
                    v1 = dsra32(v1, 24);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, 6472);  // 0x871948
                    s1 = addu(v0, v1);
                    a0 = lh(s1, 0);
                    jal(0x4572C4u, &gen::fn_sub_16C570_0016c570);
                    s0 = v0 & 0xFFFFu;
                    a0 = lh(s1, 0);
                    a1 = s3;
                    jal(0x4572D8u, &gen::fn_sub_17B5B0_0017b5b0);
                    v0 = subu(s0, v0);
                    a1 = dsll32(v0, 16);
                    a1 = dsra32(a1, 16);
                    a0 = lh(s1, 0);
                    jal(0x4572F0u, &gen::fn_sub_16CF90_0016cf90);
                }
            }
            charge(5);
            a0 = s5;
            a1 = si(4);
            a2 = s4;
            jal(0x457304u, &gen::fn_sub_457340_00457340);
        }
        charge(12);
        ra = ld(sp, 128);
        lq(s7, sp, 112);
        lq(s6, sp, 96);
        lq(s5, sp, 80);
        lq(s4, sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 208);
    }

    // 0x456670 (_, pc): the s8 timer +4667 counts to 50; then, unless another member aims a kind-3 skill at pc, pc's skill
    // for itself (sub_43B980(pc, pc)) is cast with the EPL 6 (sub_1A9760) and SFX (1, 8, 3, 1) near the hero; skills 202 /
    // 203 are applied through sub_17B860; the HP / SP cost as sub_456EA0; sub_457340(pc, 2, pc). Between the casts the aim
    // point +4668.. follows pc's model (sub_1AD940).
    void sub_456670() {
        enter(26);
        sp = addiu(sp, -144);
        sd(sp, 80, ra);
        sq(s4, sp, 64);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s0 = a1;
        s3 = dsll32(s0, 24);
        s3 = dsra32(s3, 24);
        v0 = sll(s3, 3);
        v0 = subu(v0, s3);
        s2 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, 6412);  // 0x87190C
        v0 = addu(v0, s2);
        v0 = lw(v0, 0);
        s1 = lw(v0, kTaskWork);
        v0 = lb(s1, 4667);
        v0 = addiu(v0, 1);
        sb(s1, 4667, v0);
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
        at = slti(v0, 50);
        if (at != 0) {
            charge(16);
            v0 = lui(0x87u);
            v0 = addiu(v0, 6132);  // 0x8717F4
            v0 = addu(v0, s2);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 112);
            a1 = lw(v0, kResController);
            jal(0x4566F0u, &gen::fn_sub_1AD940_001ad940);
            lwc1(2, sp, 112);
            lwc1(1, sp, 116);
            lwc1(0, sp, 120);
            swc1(2, s1, 4668);
            swc1(1, s1, 4672);
            swc1(0, s1, 4676);
        } else {
            charge(4);
            sb(s1, 4667, zero);
            s1 = si(1);
            for (;;) {
                charge(3);
                v0 = slti(s1, 4);
                if (v0 == 0) break;
                backedge();
                charge(10);
                a0 = 0;
                v0 = sll(s1, 3);
                v0 = subu(v0, s1);
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
                    charge(2);
                    if (s1 != s3) {
                        charge(8);
                        a0 = dsll32(s1, 24);
                        a0 = dsra32(a0, 24);
                        jal(0x456780u, &gen::fn_sub_4573D0_004573d0);
                        v0 = dsll32(v0, 24);
                        v0 = dsra32(v0, 24);
                        if (s3 == v0) {
                            charge(9);
                            a0 = dsll32(s1, 24);
                            a0 = dsra32(a0, 24);
                            jal(0x4567A0u, &gen::fn_sub_457390_00457390);
                            a0 = dsll32(v0, 24);
                            a0 = dsra32(a0, 24);
                            v1 = si(3);
                            if (a0 == v1) {
                                charge(9);
                                ra = ld(sp, 80);
                                lq(s4, sp, 64);
                                lq(s3, sp, 48);
                                lq(s2, sp, 32);
                                lq(s1, sp, 16);
                                lq(s0, sp, 0);
                                sp = addiu(sp, 144);
                                return;
                            }
                        }
                    }
                }
                charge(1);
                s1 = addiu(s1, 1);
            }
            charge(9);
            a0 = s0;
            a1 = s0;
            jal(0x4567D4u, &gen::fn_sub_43B980_0043b980);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            v1 = si(-1);
            if (a0 != v1) {
                charge(31);
                v1 = dsll32(s0, 24);
                v1 = dsra32(v1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                s1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6132);  // 0x8717F4
                v0 = addu(v0, s1);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 96);
                a1 = lw(v0, kResController);
                jal(0x45681Cu, &gen::fn_sub_1AD940_001ad940);
                lwc1(2, sp, 96);
                lwc1(1, sp, 100);
                lwc1(0, sp, 104);
                swc1(2, sp, 128);
                swc1(1, sp, 132);
                swc1(0, sp, 136);
                s3 = si(-1);
                s4 = s3;
                v0 = lui(0x87u);
                v0 = addiu(v0, 6048);  // 0x8717A0 gFldUnitsPc
                a0 = addu(v0, s1);
                v0 = lui(0x4516u);
                mtc1(v0, 12);  // 2400f
                jal(0x456858u, &gen::fn_sub_1C7130_001c7130);
                a0 = si(1);
                if (v0 == a0) {
                    charge(7);
                    a1 = si(8);
                    a2 = si(3);
                    a3 = a0;
                    jal(0x456878u, &gen::fn_sub_10A4E0_0010a4e0);
                } else {
                    charge(2);
                    s4 = si(3);
                    s3 = a0;
                }
                charge(18);
                jal(0x456890u, &gen::fn_K_Field_Get_001b9120);
                a0 = lw(v0, 16);
                a1 = si(6);
                a2 = addiu(sp, 128);
                a3 = s4;
                a4 = s3;
                jal(0x4568ACu, &gen::fn_sub_1A9760_001a9760);
                a0 = s0;
                a1 = s0;
                jal(0x4568BCu, &gen::fn_sub_43B980_0043b980);
                s1 = dsll32(v0, 16);
                s1 = dsra32(s1, 16);
                a2 = si(202);
                if (s1 == a2) {
                    charge(16);
                    v1 = dsll32(s0, 24);
                    v1 = dsra32(v1, 24);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, 6472);  // 0x871948
                    v0 = addu(v0, v1);
                    v0 = lh(v0, 0);
                    a0 = v0;
                    a1 = a0;
                    a3 = 0;
                    jal(0x456908u, &gen::fn_sub_17B860_0017b860);
                } else {
                    charge(3);
                    a2 = si(203);
                    if (s1 == a2) {
                        charge(14);
                        v1 = dsll32(s0, 24);
                        v1 = dsra32(v1, 24);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, 6472);  // 0x871948
                        v0 = addu(v0, v1);
                        v0 = lh(v0, 0);
                        a0 = v0;
                        a1 = a0;
                        a3 = 0;
                        jal(0x456954u, &gen::fn_sub_17B860_0017b860);
                    }
                }
                charge(11);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6472);  // 0x871948
                v0 = addu(v0, s2);
                a0 = lh(v0, 0);
                a1 = s1 & 0xFFFFu;
                jal(0x456970u, &gen::fn_sub_17B500_0017b500);
                v1 = v0 & 0xFFFFu;
                v0 = si(1);
                if (v1 == v0) {
                    charge(24);
                    v1 = dsll32(s0, 24);
                    v1 = dsra32(v1, 24);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, 6472);  // 0x871948
                    s3 = addu(v0, v1);
                    a0 = lh(s3, 0);
                    jal(0x4569ACu, &gen::fn_sub_16C4F0_0016c4f0);
                    s2 = v0 & 0xFFFFu;
                    a0 = lh(s3, 0);
                    a1 = s1 & 0xFFFFu;
                    jal(0x4569C0u, &gen::fn_sub_17B5B0_0017b5b0);
                    v0 = subu(s2, v0);
                    a1 = dsll32(v0, 16);
                    a1 = dsra32(a1, 16);
                    a0 = lh(s3, 0);
                    jal(0x4569D8u, &gen::fn_sub_16CF40_0016cf40);
                } else {
                    charge(3);
                    v0 = si(2);
                    if (v1 == v0) {
                        charge(22);
                        v1 = dsll32(s0, 24);
                        v1 = dsra32(v1, 24);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, 6472);  // 0x871948
                        s3 = addu(v0, v1);
                        a0 = lh(s3, 0);
                        jal(0x456A18u, &gen::fn_sub_16C570_0016c570);
                        s2 = v0 & 0xFFFFu;
                        a0 = lh(s3, 0);
                        a1 = s1 & 0xFFFFu;
                        jal(0x456A2Cu, &gen::fn_sub_17B5B0_0017b5b0);
                        v0 = subu(s2, v0);
                        a1 = dsll32(v0, 16);
                        a1 = dsra32(a1, 16);
                        a0 = lh(s3, 0);
                        jal(0x456A44u, &gen::fn_sub_16CF90_0016cf90);
                    }
                }
                charge(5);
                a0 = s0;
                a1 = si(2);
                a2 = s0;
                jal(0x456A58u, &gen::fn_sub_457340_00457340);
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

    // 0x456A90 (_, pc, target): sub_456670 aimed at another member: the skill sub_43B980(pc, target), applied with
    // sub_17B860(pc's id, target's id, skill, 0), the cost, sub_457340(pc, 3, target); between the casts both aim points
    // (+4668.. pc's, +4680.. the target's) follow the models.
    void sub_456A90() {
        enter(27);
        sp = addiu(sp, -160);
        sd(sp, 80, ra);
        sq(s4, sp, 64);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s1 = a1;
        s0 = a2;
        s3 = dsll32(s1, 24);
        s3 = dsra32(s3, 24);
        v0 = sll(s3, 3);
        v0 = subu(v0, s3);
        v1 = sll(v0, 6);
        v0 = lui(0x87u);
        v0 = addiu(v0, 6412);  // 0x87190C
        v0 = addu(v0, v1);
        v0 = lw(v0, 0);
        s2 = lw(v0, kTaskWork);
        v0 = lb(s2, 4667);
        v0 = addiu(v0, 1);
        sb(s2, 4667, v0);
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
        at = slti(v0, 50);
        if (at != 0) {
            charge(35);
            v0 = lui(0x87u);
            v0 = addiu(v0, 6132);  // 0x8717F4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 128);
            a1 = lw(v0, kResController);
            jal(0x456B14u, &gen::fn_sub_1AD940_001ad940);
            lwc1(2, sp, 128);
            lwc1(1, sp, 132);
            lwc1(0, sp, 136);
            swc1(2, s2, 4668);
            swc1(1, s2, 4672);
            swc1(0, s2, 4676);
            v1 = dsll32(s0, 24);
            v1 = dsra32(v1, 24);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = lui(0x87u);
            v0 = addiu(v0, 6132);  // 0x8717F4
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            a0 = addiu(sp, 112);
            a1 = lw(v0, kResController);
            jal(0x456B60u, &gen::fn_sub_1AD940_001ad940);
            lwc1(2, sp, 112);
            lwc1(1, sp, 116);
            lwc1(0, sp, 120);
            swc1(2, s2, 4680);
            swc1(1, s2, 4684);
            swc1(0, s2, 4688);
        } else {
            charge(6);
            sb(s2, 4667, zero);
            s4 = si(1);
            s2 = dsll32(s0, 24);
            s2 = dsra32(s2, 24);
            for (;;) {
                charge(3);
                v0 = slti(s4, 4);
                if (v0 == 0) break;
                backedge();
                charge(10);
                a0 = 0;
                v0 = sll(s4, 3);
                v0 = subu(v0, s4);
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
                    charge(2);
                    if (s4 != s3) {
                        charge(8);
                        a0 = dsll32(s4, 24);
                        a0 = dsra32(a0, 24);
                        jal(0x456BF8u, &gen::fn_sub_4573D0_004573d0);
                        v0 = dsll32(v0, 24);
                        v0 = dsra32(v0, 24);
                        if (s2 == v0) {
                            charge(9);
                            a0 = dsll32(s4, 24);
                            a0 = dsra32(a0, 24);
                            jal(0x456C18u, &gen::fn_sub_457390_00457390);
                            a0 = dsll32(v0, 24);
                            a0 = dsra32(a0, 24);
                            v1 = si(3);
                            if (a0 == v1) {
                                charge(9);
                                ra = ld(sp, 80);
                                lq(s4, sp, 64);
                                lq(s3, sp, 48);
                                lq(s2, sp, 32);
                                lq(s1, sp, 16);
                                lq(s0, sp, 0);
                                sp = addiu(sp, 160);
                                return;
                            }
                        }
                    }
                }
                charge(1);
                s4 = addiu(s4, 1);
            }
            charge(9);
            a0 = s1;
            a1 = s0;
            jal(0x456C4Cu, &gen::fn_sub_43B980_0043b980);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            v1 = si(-1);
            if (a0 != v1) {
                charge(31);
                v1 = dsll32(s0, 24);
                v1 = dsra32(v1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                s2 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6132);  // 0x8717F4
                v0 = addu(v0, s2);
                v0 = lw(v0, 0);
                a0 = addiu(sp, 96);
                a1 = lw(v0, kResController);
                jal(0x456C94u, &gen::fn_sub_1AD940_001ad940);
                lwc1(2, sp, 96);
                lwc1(1, sp, 100);
                lwc1(0, sp, 104);
                swc1(2, sp, 144);
                swc1(1, sp, 148);
                swc1(0, sp, 152);
                s3 = si(-1);
                s4 = s3;
                v0 = lui(0x87u);
                v0 = addiu(v0, 6048);  // 0x8717A0 gFldUnitsPc
                a0 = addu(v0, s2);
                v0 = lui(0x4516u);
                mtc1(v0, 12);  // 2400f
                jal(0x456CD0u, &gen::fn_sub_1C7130_001c7130);
                a0 = si(1);
                if (v0 == a0) {
                    charge(7);
                    a1 = si(8);
                    a2 = si(3);
                    a3 = a0;
                    jal(0x456CF0u, &gen::fn_sub_10A4E0_0010a4e0);
                } else {
                    charge(2);
                    s4 = si(3);
                    s3 = a0;
                }
                charge(37);
                jal(0x456D08u, &gen::fn_K_Field_Get_001b9120);
                a0 = lw(v0, 16);
                a1 = si(6);
                a2 = addiu(sp, 144);
                a3 = s4;
                a4 = s3;
                jal(0x456D24u, &gen::fn_sub_1A9760_001a9760);
                a0 = s1;
                a1 = s0;
                jal(0x456D34u, &gen::fn_sub_43B980_0043b980);
                s3 = v0 & 0xFFFFu;
                v1 = dsll32(s1, 24);
                v1 = dsra32(v1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = lui(0x87u);
                v0 = addiu(v0, 6472);  // 0x871948
                s4 = addu(v0, v1);
                a0 = lh(s4, 0);
                v0 = addu(v0, s2);
                a1 = lh(v0, 0);
                a2 = s3;
                a3 = 0;
                jal(0x456D74u, &gen::fn_sub_17B860_0017b860);
                a0 = lh(s4, 0);
                a1 = s3;
                jal(0x456D84u, &gen::fn_sub_17B500_0017b500);
                v1 = v0 & 0xFFFFu;
                v0 = si(1);
                if (v1 == v0) {
                    charge(24);
                    v1 = dsll32(s1, 24);
                    v1 = dsra32(v1, 24);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, 6472);  // 0x871948
                    s4 = addu(v0, v1);
                    a0 = lh(s4, 0);
                    jal(0x456DC0u, &gen::fn_sub_16C4F0_0016c4f0);
                    s2 = v0 & 0xFFFFu;
                    a0 = lh(s4, 0);
                    a1 = s3;
                    jal(0x456DD4u, &gen::fn_sub_17B5B0_0017b5b0);
                    v0 = subu(s2, v0);
                    a1 = dsll32(v0, 16);
                    a1 = dsra32(a1, 16);
                    a0 = lh(s4, 0);
                    jal(0x456DECu, &gen::fn_sub_16CF40_0016cf40);
                } else {
                    charge(3);
                    v0 = si(2);
                    if (v1 == v0) {
                        charge(22);
                        v1 = dsll32(s1, 24);
                        v1 = dsra32(v1, 24);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, 6472);  // 0x871948
                        s4 = addu(v0, v1);
                        a0 = lh(s4, 0);
                        jal(0x456E2Cu, &gen::fn_sub_16C570_0016c570);
                        s2 = v0 & 0xFFFFu;
                        a0 = lh(s4, 0);
                        a1 = s3;
                        jal(0x456E40u, &gen::fn_sub_17B5B0_0017b5b0);
                        v0 = subu(s2, v0);
                        a1 = dsll32(v0, 16);
                        a1 = dsra32(a1, 16);
                        a0 = lh(s4, 0);
                        jal(0x456E58u, &gen::fn_sub_16CF90_0016cf90);
                    }
                }
                charge(5);
                a0 = s1;
                a1 = si(3);
                a2 = s0;
                jal(0x456E6Cu, &gen::fn_sub_457340_00457340);
            }
        }
        charge(9);
        ra = ld(sp, 80);
        lq(s4, sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 160);
    }
};

// @@STRUCTS@@

}  // namespace

// --- typed entry points -------------------------------------------------------------------------------------------------
void sub_453D90(EEContext& ctx, u64 ec) { set_args(ctx, {ec}); SymLeaves{ctx}.sub_453D90(); }
s32 Y_Stratum_UpdateEneDeadEffectTask(EEContext& ctx, u64 task) { set_args(ctx, {task}); SymLeaves{ctx}.Y_Stratum_UpdateEneDeadEffectTask(); return static_cast<s32>(v0_of(ctx)); }
void sub_4543C0(EEContext& ctx, u64 ec, u64 state) { set_args(ctx, {ec, state}); SymLeaves{ctx}.sub_4543C0(); }
u32 sub_454400(EEContext& ctx, u64 pos, u64 ec) { set_args(ctx, {pos, ec}); SymLeaves{ctx}.sub_454400(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_454520(EEContext& ctx, u64 pos, u64 ec) { set_args(ctx, {pos, ec}); SymLeaves{ctx}.sub_454520(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_454620(EEContext& ctx, u64 ec) { set_args(ctx, {ec}); SymLeaves{ctx}.sub_454620(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_454A70(EEContext& ctx, u64 ec, u64 pos) { set_args(ctx, {ec, pos}); SymLeaves{ctx}.sub_454A70(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_454D00(EEContext& ctx, u64 pos) { set_args(ctx, {pos}); SymLeaves{ctx}.sub_454D00(); return static_cast<u32>(v0_of(ctx)); }
void sub_455B50(EEContext& ctx) { SymLeaves{ctx}.sub_455B50(); }
void sub_455CF0(EEContext& ctx) { SymLeaves{ctx}.sub_455CF0(); }
void sub_4561D0(EEContext& ctx, u64 task) { set_args(ctx, {task}); SymLeaves{ctx}.sub_4561D0(); }
void sub_4561F0(EEContext& ctx, u64 task) { set_args(ctx, {task}); SymLeaves{ctx}.sub_4561F0(); }
void sub_4563B0(EEContext& ctx, u64 task) { set_args(ctx, {task}); SymLeaves{ctx}.sub_4563B0(); }
void sub_4563C0(EEContext& ctx, u64 task, u64 floor) { set_args(ctx, {task, floor}); SymLeaves{ctx}.sub_4563C0(); }
void sub_4563D0(EEContext& ctx, u64 task, u64 xy) { set_args(ctx, {task, xy}); SymLeaves{ctx}.sub_4563D0(); }
void sub_456400(EEContext& ctx, u64 task, u64 value) { set_args(ctx, {task, value}); SymLeaves{ctx}.sub_456400(); }
void sub_456410(EEContext& ctx, u64 pc) { set_args(ctx, {pc}); SymLeaves{ctx}.sub_456410(); }
void sub_456450(EEContext& ctx, u64 pc) { set_args(ctx, {pc}); SymLeaves{ctx}.sub_456450(); }
void sub_456490(EEContext& ctx, u64 pc) { set_args(ctx, {pc}); SymLeaves{ctx}.sub_456490(); }
void sub_4564E0(EEContext& ctx, u64 pc) { set_args(ctx, {pc}); SymLeaves{ctx}.sub_4564E0(); }
void sub_456530(EEContext& ctx, u64 pc) { set_args(ctx, {pc}); SymLeaves{ctx}.sub_456530(); }
void sub_456580(EEContext& ctx, u64 pc) { set_args(ctx, {pc}); SymLeaves{ctx}.sub_456580(); }
void sub_4565D0(EEContext& ctx, u64 pc) { set_args(ctx, {pc}); SymLeaves{ctx}.sub_4565D0(); }
void sub_456620(EEContext& ctx, u64 pc) { set_args(ctx, {pc}); SymLeaves{ctx}.sub_456620(); }
void sub_457340(EEContext& ctx, u64 pc, u64 kind, u64 target) { set_args(ctx, {pc, kind, target}); SymLeaves{ctx}.sub_457340(); }
u32 sub_457390(EEContext& ctx, u64 pc) { set_args(ctx, {pc}); SymLeaves{ctx}.sub_457390(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_4573D0(EEContext& ctx, u64 pc) { set_args(ctx, {pc}); SymLeaves{ctx}.sub_4573D0(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_457410(EEContext& ctx) { SymLeaves{ctx}.sub_457410(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_457470(EEContext& ctx, u64 slot) { set_args(ctx, {slot}); SymLeaves{ctx}.sub_457470(); return static_cast<u32>(v0_of(ctx)); }
void sub_454F50(EEContext& ctx, u64 ec, u64 pc) { set_args(ctx, {ec, pc}); SymBig{ctx}.sub_454F50(); }
void sub_456EA0(EEContext& ctx, u64 unused, u64 pc, u64 target) { set_args(ctx, {unused, pc, target}); SymBig{ctx}.sub_456EA0(); }
void sub_456670(EEContext& ctx, u64 unused, u64 pc) { set_args(ctx, {unused, pc}); SymBig{ctx}.sub_456670(); }
void sub_456A90(EEContext& ctx, u64 unused, u64 pc, u64 target) { set_args(ctx, {unused, pc, target}); SymBig{ctx}.sub_456A90(); }
// @@API@@

}  // namespace p3fes::game

// =====================================================================================================================
// The recompiled program's entry points (recomp/generated/functions.h signatures)
// =====================================================================================================================
namespace p3fes::recomp_gen {
namespace g = p3fes::game;
void fn_sub_453D90_00453d90(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_453D90(); }
void fn_Y_Stratum_UpdateEneDeadEffectTask_004541f0(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.Y_Stratum_UpdateEneDeadEffectTask(); }
void fn_sub_4543C0_004543c0(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_4543C0(); }
void fn_sub_454400_00454400(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_454400(); }
void fn_sub_454520_00454520(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_454520(); }
void fn_sub_454620_00454620(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_454620(); }
void fn_sub_454A70_00454a70(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_454A70(); }
void fn_sub_454D00_00454d00(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_454D00(); }
void fn_sub_455B50_00455b50(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_455B50(); }
void fn_sub_455CF0_00455cf0(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_455CF0(); }
void fn_sub_4561D0_004561d0(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_4561D0(); }
void fn_sub_4561F0_004561f0(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_4561F0(); }
void fn_sub_4563B0_004563b0(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_4563B0(); }
void fn_sub_4563C0_004563c0(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_4563C0(); }
void fn_sub_4563D0_004563d0(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_4563D0(); }
void fn_sub_456400_00456400(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_456400(); }
void fn_sub_456410_00456410(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_456410(); }
void fn_sub_456450_00456450(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_456450(); }
void fn_sub_456490_00456490(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_456490(); }
void fn_sub_4564E0_004564e0(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_4564E0(); }
void fn_sub_456530_00456530(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_456530(); }
void fn_sub_456580_00456580(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_456580(); }
void fn_sub_4565D0_004565d0(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_4565D0(); }
void fn_sub_456620_00456620(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_456620(); }
void fn_sub_457340_00457340(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_457340(); }
void fn_sub_457390_00457390(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_457390(); }
void fn_sub_4573D0_004573d0(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_4573D0(); }
void fn_sub_457410_00457410(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_457410(); }
void fn_sub_457470_00457470(p3fes::EEContext& ctx) { g::SymLeaves{ctx}.sub_457470(); }
void fn_sub_454F50_00454f50(p3fes::EEContext& ctx) { g::SymBig{ctx}.sub_454F50(); }
void fn_sub_456EA0_00456ea0(p3fes::EEContext& ctx) { g::SymBig{ctx}.sub_456EA0(); }
void fn_sub_456670_00456670(p3fes::EEContext& ctx) { g::SymBig{ctx}.sub_456670(); }
void fn_sub_456A90_00456a90(p3fes::EEContext& ctx) { g::SymBig{ctx}.sub_456A90(); }
// @@SHIMS@@
}  // namespace p3fes::recomp_gen
