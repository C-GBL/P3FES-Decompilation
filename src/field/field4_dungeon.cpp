// Tartarus (slice field4; field4.h documents the grid, the dungeon work and the floor table): k_dungeon.c's floor
// generator (sub_1BD450 -> sub_1BCAC0, drawing from RpRandom only), the block builder (sub_1BD8C0 / sub_1BB300: block
// models, field objects and the HBN markers turned and moved into place), the floor-kind pick, and the "automatic
// dungeon" task (create / update / destroy, the next-floor request). p3fes_handgen bodies (hg_cpu.h) with roles,
// proposed names in brackets, named offsets and annotated states; sub_1BF340 restructured without gotos (the same
// statements, charges and check points on every path).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/field4.h"

namespace p3fes::recomp_gen {
void fn_K_Field_Get_001b9120(p3fes::EEContext&);
void fn_K_Field_SetShouldShutdown_001ba880(p3fes::EEContext&);
void fn_K_FldDungeon_CreateTask_001bfbc0(p3fes::EEContext&);
void fn_K_FldDungeon_GetCurrentFloor_001bff20(p3fes::EEContext&);
void fn_K_FldDungeon_UpdateTask_001bf570(p3fes::EEContext&);
void fn_K_Scene_IsRandomFloor_001a0250(p3fes::EEContext&);
void fn_Y_Stratum_CreateStratumPartsTask_00447e70(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_k_Field_CreateFieldRootTask_001ba5f0(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_16DD60_0016dd60(p3fes::EEContext&);
void fn_sub_16F380_0016f380(p3fes::EEContext&);
void fn_sub_16F3E0_0016f3e0(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_19FF10_0019ff10(p3fes::EEContext&);
void fn_sub_1A0150_001a0150(p3fes::EEContext&);
void fn_sub_1A02C0_001a02c0(p3fes::EEContext&);
void fn_sub_1A5C50_001a5c50(p3fes::EEContext&);
void fn_sub_1A9080_001a9080(p3fes::EEContext&);
void fn_sub_1A9180_001a9180(p3fes::EEContext&);
void fn_sub_1A91B0_001a91b0(p3fes::EEContext&);
void fn_sub_1A9400_001a9400(p3fes::EEContext&);
void fn_sub_1A9470_001a9470(p3fes::EEContext&);
void fn_sub_1B3C90_001b3c90(p3fes::EEContext&);
void fn_sub_1B5380_001b5380(p3fes::EEContext&);
void fn_sub_1BAA50_001baa50(p3fes::EEContext&);
void fn_sub_1BAB60_001bab60(p3fes::EEContext&);
void fn_sub_1BB090_001bb090(p3fes::EEContext&);
void fn_sub_1BB300_001bb300(p3fes::EEContext&);
void fn_sub_1BC630_001bc630(p3fes::EEContext&);
void fn_sub_1BCAC0_001bcac0(p3fes::EEContext&);
void fn_sub_1BD450_001bd450(p3fes::EEContext&);
void fn_sub_1BD8C0_001bd8c0(p3fes::EEContext&);
void fn_sub_1BF220_001bf220(p3fes::EEContext&);
void fn_sub_1BF340_001bf340(p3fes::EEContext&);
void fn_sub_1BFAF0_001bfaf0(p3fes::EEContext&);
void fn_sub_1BFCC0_001bfcc0(p3fes::EEContext&);
void fn_sub_1C0190_001c0190(p3fes::EEContext&);
void fn_sub_1C0210_001c0210(p3fes::EEContext&);
void fn_sub_1C02E0_001c02e0(p3fes::EEContext&);
void fn_sub_1C03F0_001c03f0(p3fes::EEContext&);
void fn_sub_1C0440_001c0440(p3fes::EEContext&);
void fn_sub_1C0740_001c0740(p3fes::EEContext&);
void fn_sub_1C07F0_001c07f0(p3fes::EEContext&);
void fn_sub_1D4180_001d4180(p3fes::EEContext&);
void fn_sub_1E6AF0_001e6af0(p3fes::EEContext&);
void fn_sub_316B40_00316b40(p3fes::EEContext&);
void fn_sub_316F70_00316f70(p3fes::EEContext&);
void fn_sub_3174E0_003174e0(p3fes::EEContext&);
void fn_sub_3B5D10_003b5d10(p3fes::EEContext&);
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);
void fn_sub_3B65D0_003b65d0(p3fes::EEContext&);
void fn_sub_3B66B0_003b66b0(p3fes::EEContext&);
void fn_sub_3B6790_003b6790(p3fes::EEContext&);
void fn_sub_3B6870_003b6870(p3fes::EEContext&);
void fn_sub_3B6B90_003b6b90(p3fes::EEContext&);
void fn_sub_3B6C50_003b6c50(p3fes::EEContext&);
void fn_sub_3B6D10_003b6d10(p3fes::EEContext&);
void fn_sub_3B6DD0_003b6dd0(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C3880_004c3880(p3fes::EEContext&);
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x001BB300 sub_1BB300 [K_FldDungeon_BuildBlock] -- 4912 bytes; frame 0x190: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// sub_1BB300(scene, x, z): builds the Tartarus block whose origin is grid cell (x, z) (from sub_1BD8C0 for every
// cell; nothing happens unless the cell is a floor cell (+0) and a block origin (+1)). K_Assert k_dungeon.c 313 / 314
// when x + width - 1 / z + depth - 1 leave the 16 x 16 grid (they return in retail). Then:
//  1. the block's world position: x = 800 x + 400 (width - 1) and z = 800 z + 400 (depth - 1) (each a madd through
//     ACC: f0 * f1 + f21 * f20 with the 400 / 800 floats of $f0 / $f21), y = 300 * the cell's level (+10);
//  2. a clone of the block model of the cell's kind (sField +4460 [kind], sub_1B5380) at that position, turned
//     (rot + 2) & 3 quarter turns, registered as a scene resource (sub_3B6790) whose id (0x3000 + 16 z + x) goes to
//     +4 of every covered cell; the resource drawn (sub_1A0150(id, 1)) and the draw list refreshed (sub_19FF10);
//  3. the clone's field objects as scene resources of their own (models type 10 via MT_Scene_CreateResModelFld,
//     EPLs type 11) parented to the block (+256), then the clone's object table emptied;
//  4. with hit data (+2620, an HBN version 0x10000..0x10003): on random floors the block's markers -- hit quads
//     (sub_3B6870, each corner turned and moved like the block: an RwMatrix rotated by 90 (rot + 2) degrees about
//     0x6833B0, RwV3dTransformPoints, + the position), enemy spawn points (type 15, sub_3B6B90), treasure points
//     (type 16, sub_3B6C50), v1.1+ type 17 (sub_3B6D10), v1.3+ up to four exits / stairs (type 18, sub_3B6DD0;
//     K_Assert 530 for five or more) whose ids are written to the +12 link words of the block's cells in the order
//     the rotation gives (1 marker: the origin cell; 3 / 4 markers: the four cells of a 2 x 2 room, rotated);
//     each marker's yaw = 90 (rot + 2) + its own, wrapped below 360.
void sub_1BB300(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x001bb300
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x190);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
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
    s7 = a0;
    s5 = a1;
    s4 = a2;
    v0 = 0x680000;
    ld(v1, v0, 13232);  // 0x6833B0
    v0 = 0x680000;
    lwc1(f0, v0, 13240);  // 0x6833B8
    sd(v1, sp, 0x170);
    swc1(f0, sp, 0x178);
    v0 = s4 & 0xFFFF;
    s1 = sll(v0, 8);
    v0 = s5 & 0xFFFF;
    s6 = sll(v0, 4);
    jal(ctx, 0x1BB368u, gen::fn_K_Field_Get_001b9120);
    v1 = addu(v0, s1);
    v1 = addu(v1, s6);
    lbu(v1, v1, f4::gcell::kState);
    if (v1 != 0) {
        // 0x001bb384
        charge(ctx, 7);
        jal(ctx, 0x1BB384u, gen::fn_K_Field_Get_001b9120);
        v1 = addu(v0, s1);
        v1 = addu(v1, s6);
        lbu(v1, v1, f4::gcell::kHead);
        if (v1 != 0) {
            // 0x001bb3a0
            charge(ctx, 13);
            v0 = s5 & 0xFFFF;
            sw(v0, sp, 0x100);
            jal(ctx, 0x1BB3A8u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s1);
            v0 = addu(v0, s6);
            lbu(v1, v0, f4::gcell::kWidth);
            lw(v0, sp, 0x100);
            v0 = addu(v0, v1);
            v0 = addiu(v0, -1);
            v0 = slti(v0, 16);
            if (v0 == 0) {
                // 0x001bb3d4
                charge(ctx, 5);
                a0 = 0x680000;
                a0 = addiu(a0, 13216);  // "k_dungeon.c"
                a1 = 313;
                jal(ctx, 0x1BB3E0u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x001bb3e8
            charge(ctx, 13);
            v0 = s4 & 0xFFFF;
            sw(v0, sp, 0x110);
            jal(ctx, 0x1BB3F0u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s1);
            v0 = addu(v0, s6);
            lbu(v1, v0, f4::gcell::kDepth);
            lw(v0, sp, 0x110);
            v0 = addu(v0, v1);
            v0 = addiu(v0, -1);
            v0 = slti(v0, 16);
            if (v0 == 0) {
                // 0x001bb41c
                charge(ctx, 5);
                a0 = 0x680000;
                a0 = addiu(a0, 13216);  // "k_dungeon.c"
                a1 = 314;
                jal(ctx, 0x1BB428u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x001bb430
            charge(ctx, 8);
            v0 = s4 & 0xFFFF;
            s2 = sll(v0, 8);
            v0 = s5 & 0xFFFF;
            s3 = sll(v0, 4);
            v0 = 0x44480000;
            mtc1(v0, f21);
            if (i64(s5) < 0) {
                // 0x001bb464
                charge(ctx, 7);
                v1 = srl(s5, 1);
                v0 = s5 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f20, f0);
                add_s(f20, f20, f20);
            } else {
                // 0x001bb450
                charge(ctx, 5);
                mtc1(s5, f0);
                cvt_s_w(f20, f0);
            }
            // 0x001bb480
            charge(ctx, 32);
            jal(ctx, 0x1BB480u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            v0 = addu(v0, s3);
            lbu(v0, v0, f4::gcell::kWidth);
            v0 = addiu(v0, -1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x43C80000;
            mtc1(v0, f0);
            mula_s(f0, f1);
            madd_s(f0, f21, f20);
            swc1(f0, sp, 0x180);
            jal(ctx, 0x1BB4BCu, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            v0 = addu(v0, s3);
            lb(v0, v0, f4::gcell::kHeight);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x43960000;
            mtc1(v0, f0);
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0x184);
            v0 = 0x44480000;
            mtc1(v0, f21);
            if (i64(s4) < 0) {
                // 0x001bb514
                charge(ctx, 7);
                v1 = srl(s4, 1);
                v0 = s4 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f20, f0);
                add_s(f20, f20, f20);
            } else {
                // 0x001bb500
                charge(ctx, 5);
                mtc1(s4, f0);
                cvt_s_w(f20, f0);
            }
            // 0x001bb530
            charge(ctx, 33);
            jal(ctx, 0x1BB530u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            v0 = addu(v0, s3);
            lbu(v0, v0, f4::gcell::kDepth);
            v0 = addiu(v0, -1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x43C80000;
            mtc1(v0, f0);
            mula_s(f0, f1);
            madd_s(f0, f21, f20);
            swc1(f0, sp, 0x188);
            jal(ctx, 0x1BB56Cu, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            v0 = addu(v0, s3);
            lbu(v0, v0, f4::gcell::kKind);
            s0 = sll(v0, 2);
            jal(ctx, 0x1BB584u, gen::fn_K_Field_Get_001b9120);
            s0 = addu(v0, s0);
            jal(ctx, 0x1BB590u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            v0 = addu(v0, s3);
            lbu(v0, v0, f4::gcell::kRot);
            v1 = addiu(v0, 2);
            v0 = v1 & 0x3;
            if (i64(v1) < 0) {
                // 0x001bb5b4
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x001bb5bc
                    charge(ctx, 1);
                    v0 = addiu(v0, -4);
                }
            }
            // 0x001bb5c0
            charge(ctx, 25);
            a2 = v0 & 0xFFFF;
            lw(a0, s0, 4460);
            a1 = addiu(sp, 0x180);
            jal(ctx, 0x1BB5CCu, gen::fn_sub_1B5380_001b5380);
            sw(v0, sp, 0x124);
            a0 = s7;
            a1 = v0;
            jal(ctx, 0x1BB5E0u, gen::fn_sub_3B6790_003b6790);
            s0 = v0 & 0xFFFF;
            a0 = s0;
            jal(ctx, 0x1BB5F0u, gen::fn_sub_3B5D10_003b5d10);
            sq(v0, sp, 0xD0);
            a0 = s0;
            a1 = 1;
            jal(ctx, 0x1BB604u, gen::fn_sub_1A0150_001a0150);
            jal(ctx, 0x1BB60Cu, gen::fn_sub_19FF10_0019ff10);
            fp = 0;
            s7 = addu(s2, s3);
            for (;;) {
                // 0x001bb680
                charge(ctx, 7);
                jal(ctx, 0x1BB680u, gen::fn_K_Field_Get_001b9120);
                v0 = addu(s7, v0);
                lbu(v0, v0, f4::gcell::kDepth);
                v0 = slt(fp, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001bb624
                charge(ctx, 6);
                s2 = 0;
                lw(v0, sp, 0x110);
                v0 = addu(v0, fp);
                s3 = sll(v0, 8);
                for (;;) {
                    // 0x001bb660
                    charge(ctx, 7);
                    jal(ctx, 0x1BB660u, gen::fn_K_Field_Get_001b9120);
                    v0 = addu(s7, v0);
                    lbu(v0, v0, f4::gcell::kWidth);
                    v0 = slt(s2, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001bb63c
                    charge(ctx, 9);
                    jal(ctx, 0x1BB63Cu, gen::fn_K_Field_Get_001b9120);
                    v1 = addu(s3, v0);
                    lw(v0, sp, 0x100);
                    v0 = addu(v0, s2);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    sh(s0, v0, f4::gcell::kResId);
                    s2 = addiu(s2, 1);
                }
                // 0x001bb67c
                charge(ctx, 1);
                fp = addiu(fp, 0x1);
            }
            // 0x001bb69c
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x001bb758
                charge(ctx, 5);
                lw(v0, sp, 0x124);
                lw(v0, v0, 280);
                v0 = sltu(s2, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001bb6a8
                charge(ctx, 8);
                v0 = sll(s2, 1);
                v0 = addu(v0, s2);
                v1 = sll(v0, 3);
                lw(v0, sp, 0x124);
                s3 = addu(v0, v1);
                lhu(v1, s3, 284);
                if (v1 != 0) {
                    // 0x001bb704
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x001bb710
                        charge(ctx, 13);
                        a0 = 11;
                        jal(ctx, 0x1BB714u, gen::fn_sub_1A5C50_001a5c50);
                        a0 = v0;
                        lw(a1, s3, 300);
                        jal(ctx, 0x1BB724u, gen::fn_sub_3B66B0_003b66b0);
                        s0 = v0 & 0xFFFF;
                        a0 = s0;
                        jal(ctx, 0x1BB734u, gen::fn_sub_3B5D10_003b5d10);
                        lq(v1, sp, 0xD0);
                        sw(v1, v0, 256);
                    }
                } else {
                    // 0x001bb6c8
                    charge(ctx, 15);
                    a0 = 10;
                    jal(ctx, 0x1BB6CCu, gen::fn_sub_1A5C50_001a5c50);
                    a0 = v0;
                    lw(a1, s3, 296);
                    jal(ctx, 0x1BB6DCu, gen::fn_sub_3B65D0_003b65d0);
                    s0 = v0 & 0xFFFF;
                    a0 = s0;
                    jal(ctx, 0x1BB6ECu, gen::fn_sub_3B5D10_003b5d10);
                    lq(v1, sp, 0xD0);
                    sw(v1, v0, 256);
                }
                // 0x001bb744
                charge(ctx, 5);
                a0 = s0;
                a1 = 1;
                jal(ctx, 0x1BB74Cu, gen::fn_sub_1A0150_001a0150);
                s2 = addiu(s2, 1);
            }
            // 0x001bb76c
            charge(ctx, 15);
            lw(v0, sp, 0x124);
            sw(zero, v0, 280);
            jal(ctx, 0x1BB774u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s1);
            v0 = addu(v0, s6);
            lbu(v0, v0, f4::gcell::kKind);
            s0 = sll(v0, 2);
            jal(ctx, 0x1BB78Cu, gen::fn_K_Field_Get_001b9120);
            v1 = addu(v0, s0);
            lw(v1, v1, f4::fld::kRes);
            lw(v1, v1, 2620);
            if (v1 != 0) {
                // 0x001bb7a8
                charge(ctx, 18);
                jal(ctx, 0x1BB7A8u, gen::fn_sub_4C38C0_004c38c0);
                s2 = v0;
                jal(ctx, 0x1BB7B4u, gen::fn_K_Field_Get_001b9120);
                v0 = addu(v0, s1);
                v0 = addu(v0, s6);
                lbu(v0, v0, f4::gcell::kKind);
                s0 = sll(v0, 2);
                jal(ctx, 0x1BB7CCu, gen::fn_K_Field_Get_001b9120);
                v0 = addu(v0, s0);
                lw(v0, v0, f4::fld::kRes);
                lw(s0, v0, 2620);
                lw(a0, s0, 4);
                v1 = 0x10000;
                if (a0 != v1) {
                    // 0x001bb7fc
                    charge(ctx, 3);
                    v0 = v1 | 0x1;
                    if (a0 != v0) {
                        // 0x001bb814
                        charge(ctx, 3);
                        v0 = v1 | 0x2;
                        if (a0 != v0) {
                            // 0x001bb82c
                            charge(ctx, 1);
                            s3 = addiu(s0, 72);
                        } else {
                            // 0x001bb820
                            charge(ctx, 3);
                            s3 = addiu(s0, 56);
                        }
                    } else {
                        // 0x001bb808
                        charge(ctx, 3);
                        s3 = addiu(s0, 48);
                    }
                } else {
                    // 0x001bb7f0
                    charge(ctx, 3);
                    s3 = addiu(s0, 40);
                }
                // 0x001bb830
                charge(ctx, 3);
                sw(zero, sp, 0xF0);
                for (;;) {
                    // 0x001bb9e0
                    charge(ctx, 5);
                    lw(v1, s0, 8);
                    lw(v0, sp, 0xF0);
                    v0 = sltu(v0, v1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001bb83c
                    charge(ctx, 5);
                    jal(ctx, 0x1BB83Cu, gen::fn_K_Scene_IsRandomFloor_001a0250);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x001bb850
                        charge(ctx, 25);
                        lhu(v0, s3, 0);
                        a0 = v0 & 0x3FF;
                        a1 = addiu(s3, 8);
                        lwc1(f12, s3, 20);
                        lwc1(f13, s3, 24);
                        lwc1(f14, s3, 28);
                        lwr(a2, s3, 4);
                        lwl(a2, s3, 7);
                        jal(ctx, 0x1BB870u, gen::fn_sub_3B6870_003b6870);
                        a0 = v0 & 0xFFFF;
                        jal(ctx, 0x1BB87Cu, gen::fn_sub_3B5D10_003b5d10);
                        sq(v0, sp, 0xC0);
                        paddub(v1, v0, zero);
                        a0 = addiu(v1, 284);
                        a1 = addiu(v1, 260);
                        lwc1(f12, v0, 272);
                        lwc1(f13, v0, 276);
                        lwc1(f14, v0, 280);
                        jal(ctx, 0x1BB8A0u, gen::fn_sub_1E6AF0_001e6af0);
                        sw(zero, sp, 0xE0);
                        for (;;) {
                            // 0x001bb9c0
                            charge(ctx, 4);
                            lw(v0, sp, 0xE0);
                            v0 = slti(v0, 4);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x001bb8b4
                            charge(ctx, 8);
                            jal(ctx, 0x1BB8B4u, gen::fn_K_Field_Get_001b9120);
                            v0 = addu(s7, v0);
                            lbu(v0, v0, f4::gcell::kRot);
                            v1 = addiu(v0, 2);
                            v0 = v1 & 0x3;
                            if (i64(v1) < 0) {
                                // 0x001bb8d4
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x001bb8dc
                                    charge(ctx, 1);
                                    v0 = addiu(v0, -4);
                                }
                            }
                            // 0x001bb8e0
                            charge(ctx, 56);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            v0 = 0x42B40000;
                            mtc1(v0, f0);
                            mul_s(f12, f0, f1);
                            v0 = 0x3F800000;
                            sw(v0, s2, 40);
                            sw(v0, s2, 20);
                            sw(v0, s2, 0);
                            sw(zero, s2, 16);
                            sw(zero, s2, 8);
                            sw(zero, s2, 4);
                            sw(zero, s2, 36);
                            sw(zero, s2, 32);
                            sw(zero, s2, 24);
                            sw(zero, s2, 56);
                            sw(zero, s2, 52);
                            sw(zero, s2, 48);
                            lw(v1, s2, 12);
                            v0 = 0x20000;
                            v0 = v0 | 0x3;
                            v0 = v1 | v0;
                            sw(v0, s2, 12);
                            a0 = s2;
                            a1 = addiu(sp, 0x170);
                            a2 = 2;
                            jal(ctx, 0x1BB950u, gen::fn_sub_4C31B0_004c31b0);
                            lw(v0, sp, 0xE0);
                            v1 = sll(v0, 1);
                            v0 = addu(v1, v0);
                            v1 = sll(v0, 2);
                            lq(v0, sp, 0xC0);
                            fp = addu(v0, v1);
                            a0 = addiu(fp, 0x11C);
                            a1 = a0;
                            a2 = s2;
                            jal(ctx, 0x1BB97Cu, gen::fn_sub_4C6BE0_004c6be0);
                            lwc1(f1, fp, 0x11C);
                            lwc1(f0, sp, 0x180);
                            add_s(f0, f1, f0);
                            swc1(f0, fp, 0x11C);
                            lwc1(f1, fp, 0x120);
                            lwc1(f0, sp, 0x184);
                            add_s(f0, f1, f0);
                            swc1(f0, fp, 0x120);
                            lwc1(f1, fp, 0x124);
                            lwc1(f0, sp, 0x188);
                            add_s(f0, f1, f0);
                            swc1(f0, fp, 0x124);
                            lw(v0, sp, 0xE0);
                            v0 = addiu(v0, 1);
                            sw(v0, sp, 0xE0);
                        }
                    }
                    // 0x001bb9d0
                    charge(ctx, 4);
                    lw(v0, sp, 0xF0);
                    v0 = addiu(v0, 1);
                    sw(v0, sp, 0xF0);
                    s3 = addiu(s3, 32);
                }
                // 0x001bb9f4
                charge(ctx, 4);
                a0 = 0;
                lw(v1, s0, 16);
                for (;;) {
                    // 0x001bba0c
                    charge(ctx, 5);
                    v0 = sltu(a0, v1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001bba04
                    charge(ctx, 2);
                    a0 = addiu(a0, 1);
                    s3 = addiu(s3, 20);
                }
                // 0x001bba20
                charge(ctx, 3);
                fp = 0;
                for (;;) {
                    // 0x001bbba0
                    charge(ctx, 4);
                    lw(v0, s0, 24);
                    v0 = sltu(fp, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001bba2c
                    charge(ctx, 5);
                    jal(ctx, 0x1BBA2Cu, gen::fn_K_Scene_IsRandomFloor_001a0250);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x001bba40
                        charge(ctx, 14);
                        lwc1(f2, s3, 4);
                        lwc1(f1, s3, 8);
                        lwc1(f0, s3, 12);
                        swc1(f2, sp, 0x160);
                        swc1(f1, sp, 0x164);
                        swc1(f0, sp, 0x168);
                        jal(ctx, 0x1BBA58u, gen::fn_K_Field_Get_001b9120);
                        v0 = addu(s7, v0);
                        lbu(v0, v0, f4::gcell::kRot);
                        v1 = addiu(v0, 2);
                        v0 = v1 & 0x3;
                        if (i64(v1) < 0) {
                            // 0x001bba78
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x001bba80
                                charge(ctx, 1);
                                v0 = addiu(v0, -4);
                            }
                        }
                        // 0x001bba84
                        charge(ctx, 54);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x42B40000;
                        mtc1(v0, f0);
                        mul_s(f20, f0, f1);
                        v0 = 0x3F800000;
                        sw(v0, s2, 40);
                        sw(v0, s2, 20);
                        sw(v0, s2, 0);
                        sw(zero, s2, 16);
                        sw(zero, s2, 8);
                        sw(zero, s2, 4);
                        sw(zero, s2, 36);
                        sw(zero, s2, 32);
                        sw(zero, s2, 24);
                        sw(zero, s2, 56);
                        sw(zero, s2, 52);
                        sw(zero, s2, 48);
                        lw(v1, s2, 12);
                        v0 = 0x20000;
                        v0 = v0 | 0x3;
                        v0 = v1 | v0;
                        sw(v0, s2, 12);
                        a0 = s2;
                        a1 = addiu(sp, 0x170);
                        mov_s(f12, f20);
                        a2 = 2;
                        jal(ctx, 0x1BBAF8u, gen::fn_sub_4C31B0_004c31b0);
                        a0 = addiu(sp, 0x160);
                        a1 = a0;
                        a2 = s2;
                        jal(ctx, 0x1BBB0Cu, gen::fn_sub_4C6BE0_004c6be0);
                        lwc1(f1, sp, 0x160);
                        lwc1(f0, sp, 0x180);
                        add_s(f0, f1, f0);
                        swc1(f0, sp, 0x160);
                        lwc1(f1, sp, 0x164);
                        lwc1(f0, sp, 0x184);
                        add_s(f0, f1, f0);
                        swc1(f0, sp, 0x164);
                        lwc1(f1, sp, 0x168);
                        lwc1(f0, sp, 0x188);
                        add_s(f0, f1, f0);
                        swc1(f0, sp, 0x168);
                        lwc1(f0, s3, 16);
                        add_s(f20, f20, f0);
                        v0 = 0x43B40000;
                        mtc1(v0, f0);
                        for (;;) {
                            // 0x001bbb60
                            charge(ctx, 6);
                            c_le_s(f20, f0);
                            if (cond(ctx)) {
                                break;
                            }
                            backedge(ctx);
                            // 0x001bbb5c
                            charge(ctx, 1);
                            sub_s(f20, f20, f0);
                        }
                        // 0x001bbb78
                        charge(ctx, 8);
                        a0 = 15;
                        jal(ctx, 0x1BBB7Cu, gen::fn_sub_1A5C50_001a5c50);
                        a0 = v0;
                        a1 = addiu(sp, 0x160);
                        mov_s(f12, f20);
                        jal(ctx, 0x1BBB90u, gen::fn_sub_3B6B90_003b6b90);
                    }
                    // 0x001bbb98
                    charge(ctx, 2);
                    fp = addiu(fp, 0x1);
                    s3 = addiu(s3, 20);
                }
                // 0x001bbbb0
                charge(ctx, 3);
                fp = 0;
                for (;;) {
                    // 0x001bbd30
                    charge(ctx, 4);
                    lw(v0, s0, 32);
                    v0 = sltu(fp, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001bbbbc
                    charge(ctx, 5);
                    jal(ctx, 0x1BBBBCu, gen::fn_K_Scene_IsRandomFloor_001a0250);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x001bbbd0
                        charge(ctx, 14);
                        lwc1(f2, s3, 4);
                        lwc1(f1, s3, 8);
                        lwc1(f0, s3, 12);
                        swc1(f2, sp, 0x150);
                        swc1(f1, sp, 0x154);
                        swc1(f0, sp, 0x158);
                        jal(ctx, 0x1BBBE8u, gen::fn_K_Field_Get_001b9120);
                        v0 = addu(s7, v0);
                        lbu(v0, v0, f4::gcell::kRot);
                        v1 = addiu(v0, 2);
                        v0 = v1 & 0x3;
                        if (i64(v1) < 0) {
                            // 0x001bbc08
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x001bbc10
                                charge(ctx, 1);
                                v0 = addiu(v0, -4);
                            }
                        }
                        // 0x001bbc14
                        charge(ctx, 54);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x42B40000;
                        mtc1(v0, f0);
                        mul_s(f20, f0, f1);
                        v0 = 0x3F800000;
                        sw(v0, s2, 40);
                        sw(v0, s2, 20);
                        sw(v0, s2, 0);
                        sw(zero, s2, 16);
                        sw(zero, s2, 8);
                        sw(zero, s2, 4);
                        sw(zero, s2, 36);
                        sw(zero, s2, 32);
                        sw(zero, s2, 24);
                        sw(zero, s2, 56);
                        sw(zero, s2, 52);
                        sw(zero, s2, 48);
                        lw(v1, s2, 12);
                        v0 = 0x20000;
                        v0 = v0 | 0x3;
                        v0 = v1 | v0;
                        sw(v0, s2, 12);
                        a0 = s2;
                        a1 = addiu(sp, 0x170);
                        mov_s(f12, f20);
                        a2 = 2;
                        jal(ctx, 0x1BBC88u, gen::fn_sub_4C31B0_004c31b0);
                        a0 = addiu(sp, 0x150);
                        a1 = a0;
                        a2 = s2;
                        jal(ctx, 0x1BBC9Cu, gen::fn_sub_4C6BE0_004c6be0);
                        lwc1(f1, sp, 0x150);
                        lwc1(f0, sp, 0x180);
                        add_s(f0, f1, f0);
                        swc1(f0, sp, 0x150);
                        lwc1(f1, sp, 0x154);
                        lwc1(f0, sp, 0x184);
                        add_s(f0, f1, f0);
                        swc1(f0, sp, 0x154);
                        lwc1(f1, sp, 0x158);
                        lwc1(f0, sp, 0x188);
                        add_s(f0, f1, f0);
                        swc1(f0, sp, 0x158);
                        lwc1(f0, s3, 16);
                        add_s(f20, f20, f0);
                        v0 = 0x43B40000;
                        mtc1(v0, f0);
                        for (;;) {
                            // 0x001bbcf0
                            charge(ctx, 6);
                            c_le_s(f20, f0);
                            if (cond(ctx)) {
                                break;
                            }
                            backedge(ctx);
                            // 0x001bbcec
                            charge(ctx, 1);
                            sub_s(f20, f20, f0);
                        }
                        // 0x001bbd08
                        charge(ctx, 8);
                        a0 = 16;
                        jal(ctx, 0x1BBD0Cu, gen::fn_sub_1A5C50_001a5c50);
                        a0 = v0;
                        a1 = addiu(sp, 0x150);
                        mov_s(f12, f20);
                        jal(ctx, 0x1BBD20u, gen::fn_sub_3B6C50_003b6c50);
                    }
                    // 0x001bbd28
                    charge(ctx, 2);
                    fp = addiu(fp, 0x1);
                    s3 = addiu(s3, 20);
                }
                // 0x001bbd40
                charge(ctx, 6);
                lw(v0, s0, 4);
                at = 0x10000;
                at = at | 0x1;
                at = sltu(v0, at);
                if (at == 0) {
                    // 0x001bbd58
                    charge(ctx, 3);
                    fp = 0;
                    for (;;) {
                        // 0x001bbed8
                        charge(ctx, 4);
                        lw(v0, s0, 40);
                        v0 = sltu(fp, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001bbd64
                        charge(ctx, 5);
                        jal(ctx, 0x1BBD64u, gen::fn_K_Scene_IsRandomFloor_001a0250);
                        v1 = 1;
                        if (v0 == v1) {
                            // 0x001bbd78
                            charge(ctx, 14);
                            lwc1(f2, s3, 4);
                            lwc1(f1, s3, 8);
                            lwc1(f0, s3, 12);
                            swc1(f2, sp, 0x140);
                            swc1(f1, sp, 0x144);
                            swc1(f0, sp, 0x148);
                            jal(ctx, 0x1BBD90u, gen::fn_K_Field_Get_001b9120);
                            v0 = addu(s7, v0);
                            lbu(v0, v0, f4::gcell::kRot);
                            v1 = addiu(v0, 2);
                            v0 = v1 & 0x3;
                            if (i64(v1) < 0) {
                                // 0x001bbdb0
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x001bbdb8
                                    charge(ctx, 1);
                                    v0 = addiu(v0, -4);
                                }
                            }
                            // 0x001bbdbc
                            charge(ctx, 54);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            v0 = 0x42B40000;
                            mtc1(v0, f0);
                            mul_s(f20, f0, f1);
                            v0 = 0x3F800000;
                            sw(v0, s2, 40);
                            sw(v0, s2, 20);
                            sw(v0, s2, 0);
                            sw(zero, s2, 16);
                            sw(zero, s2, 8);
                            sw(zero, s2, 4);
                            sw(zero, s2, 36);
                            sw(zero, s2, 32);
                            sw(zero, s2, 24);
                            sw(zero, s2, 56);
                            sw(zero, s2, 52);
                            sw(zero, s2, 48);
                            lw(v1, s2, 12);
                            v0 = 0x20000;
                            v0 = v0 | 0x3;
                            v0 = v1 | v0;
                            sw(v0, s2, 12);
                            a0 = s2;
                            a1 = addiu(sp, 0x170);
                            mov_s(f12, f20);
                            a2 = 2;
                            jal(ctx, 0x1BBE30u, gen::fn_sub_4C31B0_004c31b0);
                            a0 = addiu(sp, 0x140);
                            a1 = a0;
                            a2 = s2;
                            jal(ctx, 0x1BBE44u, gen::fn_sub_4C6BE0_004c6be0);
                            lwc1(f1, sp, 0x140);
                            lwc1(f0, sp, 0x180);
                            add_s(f0, f1, f0);
                            swc1(f0, sp, 0x140);
                            lwc1(f1, sp, 0x144);
                            lwc1(f0, sp, 0x184);
                            add_s(f0, f1, f0);
                            swc1(f0, sp, 0x144);
                            lwc1(f1, sp, 0x148);
                            lwc1(f0, sp, 0x188);
                            add_s(f0, f1, f0);
                            swc1(f0, sp, 0x148);
                            lwc1(f0, s3, 16);
                            add_s(f20, f20, f0);
                            v0 = 0x43B40000;
                            mtc1(v0, f0);
                            for (;;) {
                                // 0x001bbe98
                                charge(ctx, 6);
                                c_le_s(f20, f0);
                                if (cond(ctx)) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x001bbe94
                                charge(ctx, 1);
                                sub_s(f20, f20, f0);
                            }
                            // 0x001bbeb0
                            charge(ctx, 8);
                            a0 = 17;
                            jal(ctx, 0x1BBEB4u, gen::fn_sub_1A5C50_001a5c50);
                            a0 = v0;
                            a1 = addiu(sp, 0x140);
                            mov_s(f12, f20);
                            jal(ctx, 0x1BBEC8u, gen::fn_sub_3B6D10_003b6d10);
                        }
                        // 0x001bbed0
                        charge(ctx, 2);
                        fp = addiu(fp, 0x1);
                        s3 = addiu(s3, 20);
                    }
                }
                // 0x001bbee8
                charge(ctx, 6);
                lw(v1, s0, 4);
                at = 0x10000;
                at = at | 0x2;
                at = sltu(v1, at);
                if (at == 0) {
                    // 0x001bbf00
                    charge(ctx, 3);
                    lw(v0, s0, 48);
                    v0 = sll(v0, 5);
                    s3 = addu(s3, v0);
                }
                // 0x001bbf0c
                charge(ctx, 5);
                at = 0x10000;
                at = at | 0x3;
                at = sltu(v1, at);
                if (at == 0) {
                    // 0x001bbf20
                    charge(ctx, 4);
                    lw(v0, s0, 56);
                    at = sltiu(v0, 5);
                    if (at == 0) {
                        // 0x001bbf30
                        charge(ctx, 5);
                        a0 = 0x680000;
                        a0 = addiu(a0, 13216);  // "k_dungeon.c"
                        a1 = 530;
                        jal(ctx, 0x1BBF3Cu, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x001bbf44
                    charge(ctx, 3);
                    fp = 0;
                    for (;;) {
                        // 0x001bc0cc
                        charge(ctx, 4);
                        lw(v1, s0, 56);
                        v0 = sltu(fp, v1);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001bbf50
                        charge(ctx, 14);
                        lwc1(f2, s3, 4);
                        lwc1(f1, s3, 8);
                        lwc1(f0, s3, 12);
                        swc1(f2, sp, 0x128);
                        swc1(f1, sp, 0x12C);
                        swc1(f0, sp, 0x130);
                        jal(ctx, 0x1BBF68u, gen::fn_K_Field_Get_001b9120);
                        v0 = addu(s7, v0);
                        lbu(v0, v0, f4::gcell::kRot);
                        v1 = addiu(v0, 2);
                        v0 = v1 & 0x3;
                        if (i64(v1) < 0) {
                            // 0x001bbf88
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x001bbf90
                                charge(ctx, 1);
                                v0 = addiu(v0, -4);
                            }
                        }
                        // 0x001bbf94
                        charge(ctx, 54);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x42B40000;
                        mtc1(v0, f0);
                        mul_s(f20, f0, f1);
                        v0 = 0x3F800000;
                        sw(v0, s2, 40);
                        sw(v0, s2, 20);
                        sw(v0, s2, 0);
                        sw(zero, s2, 16);
                        sw(zero, s2, 8);
                        sw(zero, s2, 4);
                        sw(zero, s2, 36);
                        sw(zero, s2, 32);
                        sw(zero, s2, 24);
                        sw(zero, s2, 56);
                        sw(zero, s2, 52);
                        sw(zero, s2, 48);
                        lw(v1, s2, 12);
                        v0 = 0x20000;
                        v0 = v0 | 0x3;
                        v0 = v1 | v0;
                        sw(v0, s2, 12);
                        a0 = s2;
                        a1 = addiu(sp, 0x170);
                        mov_s(f12, f20);
                        a2 = 2;
                        jal(ctx, 0x1BC008u, gen::fn_sub_4C31B0_004c31b0);
                        a0 = addiu(sp, 0x128);
                        a1 = a0;
                        a2 = s2;
                        jal(ctx, 0x1BC01Cu, gen::fn_sub_4C6BE0_004c6be0);
                        lwc1(f1, sp, 0x128);
                        lwc1(f0, sp, 0x180);
                        add_s(f0, f1, f0);
                        swc1(f0, sp, 0x128);
                        lwc1(f1, sp, 0x12C);
                        lwc1(f0, sp, 0x184);
                        add_s(f0, f1, f0);
                        swc1(f0, sp, 0x12C);
                        lwc1(f1, sp, 0x130);
                        lwc1(f0, sp, 0x188);
                        add_s(f0, f1, f0);
                        swc1(f0, sp, 0x130);
                        lwc1(f0, s3, 16);
                        add_s(f20, f20, f0);
                        v0 = 0x43B40000;
                        mtc1(v0, f0);
                        for (;;) {
                            // 0x001bc070
                            charge(ctx, 6);
                            c_le_s(f20, f0);
                            if (cond(ctx)) {
                                break;
                            }
                            backedge(ctx);
                            // 0x001bc06c
                            charge(ctx, 1);
                            sub_s(f20, f20, f0);
                        }
                        // 0x001bc088
                        charge(ctx, 17);
                        v0 = sll(fp, 1);
                        v0 = addu(v0, sp);
                        v0 = addiu(v0, 312);
                        sq(v0, sp, 0xB0);
                        a0 = 18;
                        jal(ctx, 0x1BC09Cu, gen::fn_sub_1A5C50_001a5c50);
                        lq(v1, sp, 0xB0);
                        sh(v0, v1, 0);
                        paddub(v0, v1, zero);
                        lhu(a0, v0, 0);
                        a1 = addiu(sp, 0x128);
                        mov_s(f12, f20);
                        jal(ctx, 0x1BC0BCu, gen::fn_sub_3B6DD0_003b6dd0);
                        fp = addiu(fp, 0x1);
                        s3 = addiu(s3, 20);
                    }
                    // 0x001bc0dc
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 != v0) {
                        // 0x001bc108
                        charge(ctx, 3);
                        v0 = 3;
                        if (v1 != v0) {
                            // 0x001bc37c
                            charge(ctx, 3);
                            v0 = 4;
                            if (v1 == v0) {
                                // 0x001bc388
                                charge(ctx, 8);
                                jal(ctx, 0x1BC388u, gen::fn_K_Field_Get_001b9120);
                                v0 = addu(v0, s1);
                                v0 = addu(v0, s6);
                                lbu(v1, v0, f4::gcell::kRot);
                                v0 = 3;
                                if (v1 == v0) {
                                    // 0x001bc568
                                    charge(ctx, 32);
                                    v0 = s4 & 0xFFFF;
                                    s1 = sll(v0, 8);
                                    v0 = s5 & 0xFFFF;
                                    s0 = sll(v0, 4);
                                    lhu(s3, sp, 0x13C);
                                    jal(ctx, 0x1BC57Cu, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s1);
                                    v0 = addu(v0, s0);
                                    sw(s3, v0, f4::gcell::kLink);
                                    v0 = s5 & 0xFFFF;
                                    s5 = sll(v0, 4);
                                    lhu(s3, sp, 0x138);
                                    jal(ctx, 0x1BC59Cu, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s1);
                                    v0 = addu(v0, s5);
                                    sw(s3, v0, 100);
                                    v0 = s4 & 0xFFFF;
                                    s1 = sll(v0, 8);
                                    lhu(s3, sp, 0x13E);
                                    jal(ctx, 0x1BC5BCu, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s1);
                                    v0 = addu(v0, s0);
                                    sw(s3, v0, 340);
                                    lhu(s0, sp, 0x13A);
                                    jal(ctx, 0x1BC5D4u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s1);
                                    v0 = addu(v0, s5);
                                    sw(s0, v0, 356);
                                } else {
                                    // 0x001bc3a8
                                    charge(ctx, 3);
                                    v0 = 2;
                                    if (v1 == v0) {
                                        // 0x001bc4e0
                                        charge(ctx, 34);
                                        v0 = s4 & 0xFFFF;
                                        s1 = sll(v0, 8);
                                        v0 = s5 & 0xFFFF;
                                        s0 = sll(v0, 4);
                                        lhu(s3, sp, 0x13E);
                                        jal(ctx, 0x1BC4F4u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s1);
                                        v0 = addu(v0, s0);
                                        sw(s3, v0, f4::gcell::kLink);
                                        v0 = s5 & 0xFFFF;
                                        s5 = sll(v0, 4);
                                        lhu(s3, sp, 0x13C);
                                        jal(ctx, 0x1BC514u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s1);
                                        v0 = addu(v0, s5);
                                        sw(s3, v0, 100);
                                        v0 = s4 & 0xFFFF;
                                        s1 = sll(v0, 8);
                                        lhu(s3, sp, 0x13A);
                                        jal(ctx, 0x1BC534u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s1);
                                        v0 = addu(v0, s0);
                                        sw(s3, v0, 340);
                                        lhu(s0, sp, 0x138);
                                        jal(ctx, 0x1BC54Cu, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s1);
                                        v0 = addu(v0, s5);
                                        sw(s0, v0, 356);
                                    } else {
                                        // 0x001bc3b4
                                        charge(ctx, 3);
                                        v0 = 1;
                                        if (v1 == v0) {
                                            // 0x001bc458
                                            charge(ctx, 34);
                                            v0 = s4 & 0xFFFF;
                                            s1 = sll(v0, 8);
                                            v0 = s5 & 0xFFFF;
                                            s0 = sll(v0, 4);
                                            lhu(s3, sp, 0x13A);
                                            jal(ctx, 0x1BC46Cu, gen::fn_K_Field_Get_001b9120);
                                            v0 = addu(v0, s1);
                                            v0 = addu(v0, s0);
                                            sw(s3, v0, f4::gcell::kLink);
                                            v0 = s5 & 0xFFFF;
                                            s5 = sll(v0, 4);
                                            lhu(s3, sp, 0x13E);
                                            jal(ctx, 0x1BC48Cu, gen::fn_K_Field_Get_001b9120);
                                            v0 = addu(v0, s1);
                                            v0 = addu(v0, s5);
                                            sw(s3, v0, 100);
                                            v0 = s4 & 0xFFFF;
                                            s1 = sll(v0, 8);
                                            lhu(s3, sp, 0x138);
                                            jal(ctx, 0x1BC4ACu, gen::fn_K_Field_Get_001b9120);
                                            v0 = addu(v0, s1);
                                            v0 = addu(v0, s0);
                                            sw(s3, v0, 340);
                                            lhu(s0, sp, 0x13C);
                                            jal(ctx, 0x1BC4C4u, gen::fn_K_Field_Get_001b9120);
                                            v0 = addu(v0, s1);
                                            v0 = addu(v0, s5);
                                            sw(s0, v0, 356);
                                        } else {
                                            // 0x001bc3c0
                                            charge(ctx, 2);
                                            if (v1 == 0) {
                                                // 0x001bc3d0
                                                charge(ctx, 34);
                                                v0 = s4 & 0xFFFF;
                                                s1 = sll(v0, 8);
                                                v0 = s5 & 0xFFFF;
                                                s0 = sll(v0, 4);
                                                lhu(s3, sp, 0x138);
                                                jal(ctx, 0x1BC3E4u, gen::fn_K_Field_Get_001b9120);
                                                v0 = addu(v0, s1);
                                                v0 = addu(v0, s0);
                                                sw(s3, v0, f4::gcell::kLink);
                                                v0 = s5 & 0xFFFF;
                                                s5 = sll(v0, 4);
                                                lhu(s3, sp, 0x13A);
                                                jal(ctx, 0x1BC404u, gen::fn_K_Field_Get_001b9120);
                                                v0 = addu(v0, s1);
                                                v0 = addu(v0, s5);
                                                sw(s3, v0, 100);
                                                v0 = s4 & 0xFFFF;
                                                s1 = sll(v0, 8);
                                                lhu(s3, sp, 0x13C);
                                                jal(ctx, 0x1BC424u, gen::fn_K_Field_Get_001b9120);
                                                v0 = addu(v0, s1);
                                                v0 = addu(v0, s0);
                                                sw(s3, v0, 340);
                                                lhu(s0, sp, 0x13E);
                                                jal(ctx, 0x1BC43Cu, gen::fn_K_Field_Get_001b9120);
                                                v0 = addu(v0, s1);
                                                v0 = addu(v0, s5);
                                                sw(s0, v0, 356);
                                            } else {
                                                // 0x001bc3c8
                                                charge(ctx, 2);
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            // 0x001bc114
                            charge(ctx, 8);
                            jal(ctx, 0x1BC114u, gen::fn_K_Field_Get_001b9120);
                            v0 = addu(v0, s1);
                            v0 = addu(v0, s6);
                            lbu(v1, v0, f4::gcell::kRot);
                            v0 = 3;
                            if (v1 == v0) {
                                // 0x001bc2f4
                                charge(ctx, 34);
                                v0 = s4 & 0xFFFF;
                                s3 = sll(v0, 8);
                                v0 = s5 & 0xFFFF;
                                s1 = sll(v0, 4);
                                lhu(s0, sp, 0x13A);
                                jal(ctx, 0x1BC308u, gen::fn_K_Field_Get_001b9120);
                                v0 = addu(v0, s3);
                                v0 = addu(v0, s1);
                                sw(s0, v0, f4::gcell::kLink);
                                v0 = s5 & 0xFFFF;
                                s0 = sll(v0, 4);
                                s5 = si(-1);
                                jal(ctx, 0x1BC328u, gen::fn_K_Field_Get_001b9120);
                                v0 = addu(v0, s3);
                                v0 = addu(v0, s0);
                                sw(s5, v0, 100);
                                v0 = s4 & 0xFFFF;
                                s3 = sll(v0, 8);
                                lhu(s4, sp, 0x13C);
                                jal(ctx, 0x1BC348u, gen::fn_K_Field_Get_001b9120);
                                v0 = addu(v0, s3);
                                v0 = addu(v0, s1);
                                sw(s4, v0, 340);
                                lhu(s1, sp, 0x138);
                                jal(ctx, 0x1BC360u, gen::fn_K_Field_Get_001b9120);
                                v0 = addu(v0, s3);
                                v0 = addu(v0, s0);
                                sw(s1, v0, 356);
                            } else {
                                // 0x001bc134
                                charge(ctx, 3);
                                v0 = 2;
                                if (v1 == v0) {
                                    // 0x001bc26c
                                    charge(ctx, 34);
                                    v0 = s4 & 0xFFFF;
                                    s3 = sll(v0, 8);
                                    v0 = s5 & 0xFFFF;
                                    s1 = sll(v0, 4);
                                    lhu(s0, sp, 0x13C);
                                    jal(ctx, 0x1BC280u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s3);
                                    v0 = addu(v0, s1);
                                    sw(s0, v0, f4::gcell::kLink);
                                    v0 = s5 & 0xFFFF;
                                    s0 = sll(v0, 4);
                                    lhu(s5, sp, 0x13A);
                                    jal(ctx, 0x1BC2A0u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s3);
                                    v0 = addu(v0, s0);
                                    sw(s5, v0, 100);
                                    v0 = s4 & 0xFFFF;
                                    s4 = sll(v0, 8);
                                    lhu(s3, sp, 0x138);
                                    jal(ctx, 0x1BC2C0u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s4);
                                    v0 = addu(v0, s1);
                                    sw(s3, v0, 340);
                                    s1 = si(-1);
                                    jal(ctx, 0x1BC2D8u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s4);
                                    v0 = addu(v0, s0);
                                    sw(s1, v0, 356);
                                } else {
                                    // 0x001bc140
                                    charge(ctx, 3);
                                    v0 = 1;
                                    if (v1 == v0) {
                                        // 0x001bc1e4
                                        charge(ctx, 34);
                                        v0 = s4 & 0xFFFF;
                                        s3 = sll(v0, 8);
                                        v0 = s5 & 0xFFFF;
                                        s1 = sll(v0, 4);
                                        lhu(s0, sp, 0x138);
                                        jal(ctx, 0x1BC1F8u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s3);
                                        v0 = addu(v0, s1);
                                        sw(s0, v0, f4::gcell::kLink);
                                        v0 = s5 & 0xFFFF;
                                        s0 = sll(v0, 4);
                                        lhu(s5, sp, 0x13C);
                                        jal(ctx, 0x1BC218u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s3);
                                        v0 = addu(v0, s0);
                                        sw(s5, v0, 100);
                                        v0 = s4 & 0xFFFF;
                                        s3 = sll(v0, 8);
                                        s4 = si(-1);
                                        jal(ctx, 0x1BC238u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s3);
                                        v0 = addu(v0, s1);
                                        sw(s4, v0, 340);
                                        lhu(s1, sp, 0x13A);
                                        jal(ctx, 0x1BC250u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s3);
                                        v0 = addu(v0, s0);
                                        sw(s1, v0, 356);
                                    } else {
                                        // 0x001bc14c
                                        charge(ctx, 2);
                                        if (v1 == 0) {
                                            // 0x001bc15c
                                            charge(ctx, 34);
                                            v0 = s4 & 0xFFFF;
                                            s1 = sll(v0, 8);
                                            v0 = s5 & 0xFFFF;
                                            s0 = sll(v0, 4);
                                            s3 = si(-1);
                                            jal(ctx, 0x1BC170u, gen::fn_K_Field_Get_001b9120);
                                            v0 = addu(v0, s1);
                                            v0 = addu(v0, s0);
                                            sw(s3, v0, f4::gcell::kLink);
                                            v0 = s5 & 0xFFFF;
                                            s5 = sll(v0, 4);
                                            lhu(s3, sp, 0x138);
                                            jal(ctx, 0x1BC190u, gen::fn_K_Field_Get_001b9120);
                                            v0 = addu(v0, s1);
                                            v0 = addu(v0, s5);
                                            sw(s3, v0, 100);
                                            v0 = s4 & 0xFFFF;
                                            s1 = sll(v0, 8);
                                            lhu(s3, sp, 0x13A);
                                            jal(ctx, 0x1BC1B0u, gen::fn_K_Field_Get_001b9120);
                                            v0 = addu(v0, s1);
                                            v0 = addu(v0, s0);
                                            sw(s3, v0, 340);
                                            lhu(s0, sp, 0x13C);
                                            jal(ctx, 0x1BC1C8u, gen::fn_K_Field_Get_001b9120);
                                            v0 = addu(v0, s1);
                                            v0 = addu(v0, s5);
                                            sw(s0, v0, 356);
                                        } else {
                                            // 0x001bc154
                                            charge(ctx, 2);
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        // 0x001bc0e8
                        charge(ctx, 8);
                        lhu(s0, sp, 0x138);
                        jal(ctx, 0x1BC0ECu, gen::fn_K_Field_Get_001b9120);
                        v0 = addu(v0, s1);
                        v0 = addu(v0, s6);
                        sw(s0, v0, f4::gcell::kLink);
                    }
                }
                // 0x001bc5e8
                charge(ctx, 3);
                a0 = s2;
                jal(ctx, 0x1BC5ECu, gen::fn_sub_4C3880_004c3880);
            }
        }
    }
    // 0x001bc5f4 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
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
    sp = addiu(sp, 0x190);
}

// 0x001BCAC0 sub_1BCAC0 [K_FldDungeon_GrowFloor] -- 2444 bytes; frame 0x170: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1BCAC0(set, x, z, fromX, fromZ): the recursive step of the floor generator (sub_1BD450). Nothing happens on a
// taken cell (+0), after a failure (0x7CE264 == 1) or on the border ring (x or z 0 or 15). At the seed cell
// (sField +62 / +63) it places the set's start pattern (0x67FA26, or 0x681866 in The Answer: 430 halves per set,
// copied as 43 halves) turned by sField +65 (sub_1BAB60) and stamped into the grid (sub_1BB090). Elsewhere it draws
// patterns until one fits (sub_1BC630 moves the origin so the pattern's door meets the cell it came from), counting
// placements in 0x7CE260 (10,000 or more: the attempt fails, 0x7CE264 = 1): at the start cell (sField +60 / +61)
// a dead end (pattern 5) when fewer than two neighbours open toward it, else (RpRandom & 7) + 1, rejecting the
// kinds 2 / 4 next to a kind 1 / 3 cell of the cell it came from; the turn = RpRandom & 3 (0x67F720 / 0x681560:
// 43 halves per pattern). Unless sField flags bit 0, the free cells around the new block whose side faces a closed
// door are marked 2 (reserved). Then, for every cell of the block and every open door (cell +11 bits 4..7:
// z-1, x-1, z+1, x+1), it recurses into the neighbour with this cell as the origin. Every grid access re-fetches
// &sField (K_Field_Get) as the original; the offsets -184 / -173 / +56 / +67 / +328 / +339 / +88 / +99 .. are cell
// fields of the neighbours (72 + 16 dx + 256 dz + field).
void sub_1BCAC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x001bcac0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x170);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    s5 = a3;
    s6 = t0;
    s4 = sll(s0, 8);
    s3 = sll(s1, 4);
    jal(ctx, 0x1BCB08u, gen::fn_K_Field_Get_001b9120);
    v1 = addu(v0, s4);
    v1 = addu(v1, s3);
    lbu(v1, v1, 72);
    if (v1 == 0) {
        // 0x001bcb24
        charge(ctx, 4);
        lw(a0, gp, f4::gpv::kGenFailed);  // 0x7CE264
        v1 = 1;
        if (a0 != v1) {
            // 0x001bcb34
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x001bcb3c
                charge(ctx, 3);
                v1 = 15;
                if (s1 == v1) {
                    goto L_001bcb58;
                }
                // 0x001bcb48
                charge(ctx, 2);
                if (s0 == 0) {
                    goto L_001bcb58;
                }
                // 0x001bcb50
                charge(ctx, 2);
                if (s0 == v1) {
                    goto L_001bcb58;
                }
                // 0x001bcb60
                charge(ctx, 5);
                jal(ctx, 0x1BCB60u, gen::fn_K_Field_Get_001b9120);
                lbu(v1, v0, 62);
                if (s1 == v1) {
                    // 0x001bcb74
                    charge(ctx, 5);
                    jal(ctx, 0x1BCB74u, gen::fn_K_Field_Get_001b9120);
                    lbu(v1, v0, 63);
                    if (s0 != v1) {
                        goto L_001bcc58;
                    }
                    // 0x001bcb88
                    charge(ctx, 4);
                    jal(ctx, 0x1BCB88u, gen::fn_sub_17D800_0017d800);
                    if (v0 != 0) {
                        // 0x001bcbd8
                        charge(ctx, 7);
                        v0 = 860;
                        mult(v1, s2, v0);
                        v0 = 0x680000;
                        v0 = addiu(v0, 6246);  // &0x681866
                        a1 = addu(v0, v1);
                        a0 = addiu(sp, 0x110);
                        v1 = 43;
                        for (;;) {
                            // 0x001bcbf4
                            charge(ctx, 7);
                            lh(v0, a1, 0);
                            a1 = addiu(a1, 2);
                            v1 = addiu(v1, -1);
                            sh(v0, a0, 0);
                            a0 = addiu(a0, 2);
                            if (i64(v1) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    } else {
                        // 0x001bcb98
                        charge(ctx, 7);
                        v0 = 860;
                        mult(v1, s2, v0);
                        v0 = 0x680000;
                        v0 = addiu(v0, -1498);  // &0x67FA26
                        a1 = addu(v0, v1);
                        a0 = addiu(sp, 0x110);
                        v1 = 43;
                        for (;;) {
                            // 0x001bcbb4
                            charge(ctx, 7);
                            lh(v0, a1, 0);
                            a1 = addiu(a1, 2);
                            v1 = addiu(v1, -1);
                            sh(v0, a0, 0);
                            a0 = addiu(a0, 2);
                            if (i64(v1) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x001bcbd0
                        charge(ctx, 2);
                    }
                    // 0x001bcc10
                    charge(ctx, 18);
                    jal(ctx, 0x1BCC10u, gen::fn_K_Field_Get_001b9120);
                    lbu(v1, v0, 65);
                    v0 = 1;
                    a1 = sllv(v0, v1);
                    a0 = addiu(sp, 0x110);
                    jal(ctx, 0x1BCC28u, gen::fn_sub_1BAB60_001bab60);
                    jal(ctx, 0x1BCC30u, gen::fn_K_Field_Get_001b9120);
                    lbu(a3, v0, 65);
                    a1 = s1 & 0xFFFF;
                    a2 = s0 & 0xFFFF;
                    a0 = addiu(sp, 0x110);
                    jal(ctx, 0x1BCC48u, gen::fn_sub_1BB090_001bb090);
                L_001bd29c:
                    charge(ctx, 3);
                    s6 = 0;
                    for (;;) {
                        // 0x001bd408
                        charge(ctx, 4);
                        lbu(v1, sp, 0x112);
                        v1 = sltu(s6, v1);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001bd2a8
                        charge(ctx, 9);
                        s7 = 0;
                        s5 = addu(s0, s6);
                        v1 = sll(s5, 8);
                        sq(v1, sp, 0xB0);
                        fp = addiu(s5, -0x1);
                        v1 = addiu(s5, 1);
                        sw(v1, sp, 0x100);
                        for (;;) {
                            // 0x001bd3f4
                            charge(ctx, 4);
                            lbu(v1, sp, 0x111);
                            v1 = sltu(s7, v1);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x001bd2cc
                            charge(ctx, 12);
                            s3 = 0;
                            s4 = addu(s1, s7);
                            a0 = sll(s4, 4);
                            lq(v1, sp, 0xB0);
                            v1 = addu(v1, a0);
                            sq(v1, sp, 0xA0);
                            v1 = addiu(s4, -1);
                            sw(v1, sp, 0xF0);
                            v1 = addiu(s4, 1);
                            sw(v1, sp, 0xE0);
                            for (;;) {
                                // 0x001bd3e4
                                charge(ctx, 3);
                                v1 = sltiu(s3, 4);
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x001bd2fc
                                charge(ctx, 11);
                                jal(ctx, 0x1BD2FCu, gen::fn_K_Field_Get_001b9120);
                                lq(v1, sp, 0xA0);
                                v1 = addu(v1, v0);
                                lbu(a1, v1, 83);
                                v1 = addiu(s3, 4);
                                a0 = 1;
                                v1 = sllv(a0, v1);
                                v1 = v1 & a1;
                                if (v1 != 0) {
                                    // 0x001bd328
                                    charge(ctx, 3);
                                    v1 = 3;
                                    if (s3 == v1) {
                                        // 0x001bd3c4
                                        charge(ctx, 7);
                                        a0 = s2;
                                        lw(a1, sp, 0xE0);
                                        a2 = s5;
                                        a3 = s4;
                                        t0 = s5;
                                        jal(ctx, 0x1BD3D8u, gen::fn_sub_1BCAC0_001bcac0);
                                    } else {
                                        // 0x001bd334
                                        charge(ctx, 3);
                                        v1 = 2;
                                        if (s3 == v1) {
                                            // 0x001bd3a0
                                            charge(ctx, 9);
                                            a0 = s2;
                                            a1 = s4;
                                            lw(a2, sp, 0x100);
                                            a3 = s4;
                                            t0 = s5;
                                            jal(ctx, 0x1BD3B4u, gen::fn_sub_1BCAC0_001bcac0);
                                        } else {
                                            // 0x001bd340
                                            charge(ctx, 2);
                                            if (s3 == a0) {
                                                // 0x001bd37c
                                                charge(ctx, 9);
                                                a0 = s2;
                                                lw(a1, sp, 0xF0);
                                                a2 = s5;
                                                a3 = s4;
                                                t0 = s5;
                                                jal(ctx, 0x1BD390u, gen::fn_sub_1BCAC0_001bcac0);
                                            } else {
                                                // 0x001bd348
                                                charge(ctx, 2);
                                                if (s3 == 0) {
                                                    // 0x001bd358
                                                    charge(ctx, 9);
                                                    a0 = s2;
                                                    a1 = s4;
                                                    a2 = fp;
                                                    a3 = s4;
                                                    t0 = s5;
                                                    jal(ctx, 0x1BD36Cu, gen::fn_sub_1BCAC0_001bcac0);
                                                } else {
                                                    // 0x001bd350
                                                    charge(ctx, 2);
                                                }
                                            }
                                        }
                                    }
                                }
                                // 0x001bd3e0
                                charge(ctx, 1);
                                s3 = addiu(s3, 1);
                            }
                            // 0x001bd3f0
                            charge(ctx, 1);
                            s7 = addiu(s7, 1);
                        }
                        // 0x001bd404
                        charge(ctx, 1);
                        s6 = addiu(s6, 1);
                    }
                    // 0x001bd418 (the shared epilogue, written out on this path)
                    charge(ctx, 13);
                    ld(ra, sp, 0x90);
                    lq(fp, sp, 0x80);
                    lq(s7, sp, 0x70);
                    lq(s6, sp, 0x60);
                    lq(s5, sp, 0x50);
                    lq(s4, sp, 0x40);
                    lq(s3, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x170);
                    return;
                }
            L_001bcc58:
                charge(ctx, 13);
                sw(zero, gp, f4::gpv::kGenSteps);  // 0x7CE260
                s3 = addu(s4, s3);
                a0 = sll(s6, 8);
                v1 = sll(s5, 4);
                s6 = addu(a0, v1);
                v1 = 860;
                mult(a0, s2, v1);
                v1 = 0x680000;
                v1 = addiu(v1, -2272);  // &0x67F720
                s7 = addu(v1, a0);
                v1 = 0x680000;
                v1 = addiu(v1, 5472);  // &0x681560
                fp = addu(v1, a0);
                for (;;) {
                    // 0x001bcc8c
                    charge(ctx, 6);
                    lw(v1, gp, f4::gpv::kGenSteps);  // 0x7CE260
                    v1 = addiu(v1, 1);
                    sw(v1, gp, f4::gpv::kGenSteps);  // 0x7CE260
                    at = sltiu(v1, 10001);
                    if (at == 0) {
                        goto L_001bcca4_18;
                    }
                    // 0x001bccb4
                    charge(ctx, 5);
                    jal(ctx, 0x1BCCB4u, gen::fn_K_Field_Get_001b9120);
                    lbu(v0, v0, 60);
                    if (s1 == v0) {
                        // 0x001bccc8
                        charge(ctx, 5);
                        jal(ctx, 0x1BCCC8u, gen::fn_K_Field_Get_001b9120);
                        lbu(v0, v0, 61);
                        if (s0 != v0) {
                            goto L_001bcde4;
                        }
                        // 0x001bccdc
                        charge(ctx, 7);
                        s4 = 0;
                        jal(ctx, 0x1BCCE0u, gen::fn_K_Field_Get_001b9120);
                        v0 = addu(s3, v0);
                        lbu(v0, v0, -184);
                        if (v0 != 0) {
                            // 0x001bccf8
                            charge(ctx, 7);
                            jal(ctx, 0x1BCCF8u, gen::fn_K_Field_Get_001b9120);
                            v0 = addu(s3, v0);
                            lbu(v0, v0, -173);
                            v0 = v0 & 0x40;
                            if (v0 != 0) {
                                // 0x001bcd14
                                charge(ctx, 1);
                                s4 = addiu(s4, 1);
                            }
                        }
                        // 0x001bcd18
                        charge(ctx, 6);
                        jal(ctx, 0x1BCD18u, gen::fn_K_Field_Get_001b9120);
                        v0 = addu(s3, v0);
                        lbu(v0, v0, 56);
                        if (v0 != 0) {
                            // 0x001bcd30
                            charge(ctx, 7);
                            jal(ctx, 0x1BCD30u, gen::fn_K_Field_Get_001b9120);
                            v0 = addu(s3, v0);
                            lbu(v0, v0, 67);
                            v0 = v0 & 0x80;
                            if (v0 != 0) {
                                // 0x001bcd4c
                                charge(ctx, 1);
                                s4 = addiu(s4, 1);
                            }
                        }
                        // 0x001bcd50
                        charge(ctx, 6);
                        jal(ctx, 0x1BCD50u, gen::fn_K_Field_Get_001b9120);
                        v0 = addu(s3, v0);
                        lbu(v0, v0, 328);
                        if (v0 != 0) {
                            // 0x001bcd68
                            charge(ctx, 7);
                            jal(ctx, 0x1BCD68u, gen::fn_K_Field_Get_001b9120);
                            v0 = addu(s3, v0);
                            lbu(v0, v0, 339);
                            v0 = v0 & 0x10;
                            if (v0 != 0) {
                                // 0x001bcd84
                                charge(ctx, 1);
                                s4 = addiu(s4, 1);
                            }
                        }
                        // 0x001bcd88
                        charge(ctx, 6);
                        jal(ctx, 0x1BCD88u, gen::fn_K_Field_Get_001b9120);
                        v1 = addu(s3, v0);
                        lbu(v1, v1, 88);
                        if (v1 != 0) {
                            // 0x001bcda0
                            charge(ctx, 7);
                            jal(ctx, 0x1BCDA0u, gen::fn_K_Field_Get_001b9120);
                            v1 = addu(s3, v0);
                            lbu(v1, v1, 99);
                            v1 = v1 & 0x20;
                            if (v1 != 0) {
                                // 0x001bcdbc
                                charge(ctx, 1);
                                s4 = addiu(s4, 1);
                            }
                        }
                        // 0x001bcdc0
                        charge(ctx, 3);
                        at = slti(s4, 2);
                        if (at == 0) {
                            backedge(ctx);
                            continue;
                        }
                        // 0x001bcdcc
                        charge(ctx, 6);
                        s4 = 5;
                        jal(ctx, 0x1BCDD0u, gen::fn_sub_488F30_00488f30);
                        s5 = v0 & 0x3;
                    L_001bce68:
                        charge(ctx, 4);
                        jal(ctx, 0x1BCE68u, gen::fn_sub_17D800_0017d800);
                        if (v0 != 0) {
                            // 0x001bceb0
                            charge(ctx, 5);
                            v0 = 86;
                            mult(v0, s4, v0);
                            a1 = addu(fp, v0);
                            a0 = addiu(sp, 0x110);
                            v1 = 43;
                            for (;;) {
                                // 0x001bcec4
                                charge(ctx, 7);
                                lh(v0, a1, 0);
                                a1 = addiu(a1, 2);
                                v1 = addiu(v1, -1);
                                sh(v0, a0, 0);
                                a0 = addiu(a0, 2);
                                if (i64(v1) <= 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                        } else {
                            // 0x001bce78
                            charge(ctx, 5);
                            v0 = 86;
                            mult(v0, s4, v0);
                            a1 = addu(s7, v0);
                            a0 = addiu(sp, 0x110);
                            v1 = 43;
                            for (;;) {
                                // 0x001bce8c
                                charge(ctx, 7);
                                lh(v0, a1, 0);
                                a1 = addiu(a1, 2);
                                v1 = addiu(v1, -1);
                                sh(v0, a0, 0);
                                a0 = addiu(a0, 2);
                                if (i64(v1) <= 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x001bcea8
                            charge(ctx, 2);
                        }
                        // 0x001bcee0
                        charge(ctx, 15);
                        v0 = 1;
                        a1 = sllv(v0, s5);
                        a0 = addiu(sp, 0x110);
                        jal(ctx, 0x1BCEECu, gen::fn_sub_1BAB60_001bab60);
                        sw(s1, sp, 0x16C);
                        sw(s0, sp, 0x168);
                        a0 = addiu(sp, 0x110);
                        a1 = addiu(sp, 0x16C);
                        a2 = addiu(sp, 0x168);
                        jal(ctx, 0x1BCF08u, gen::fn_sub_1BC630_001bc630);
                        v1 = 1;
                        if (v0 == v1) {
                            break;
                        }
                        backedge(ctx);
                        continue;
                    }
                L_001bcde4:
                    charge(ctx, 10);
                    jal(ctx, 0x1BCDE4u, gen::fn_sub_488F30_00488f30);
                    v0 = v0 & 0x7;
                    s4 = addiu(v0, 1);
                    jal(ctx, 0x1BCDF4u, gen::fn_sub_488F30_00488f30);
                    s5 = v0 & 0x3;
                    v0 = 2;
                    if (s4 != v0) {
                        // 0x001bce0c
                        charge(ctx, 3);
                        v0 = 4;
                        if (s4 != v0) {
                            goto L_001bce68;
                        }
                        goto L_001bce18;
                    }
                L_001bce18:
                    charge(ctx, 6);
                    jal(ctx, 0x1BCE18u, gen::fn_K_Field_Get_001b9120);
                    v0 = addu(s6, v0);
                    lbu(v0, v0, 72);
                    if (v0 == 0) {
                        goto L_001bce68;
                    }
                    // 0x001bce30
                    charge(ctx, 7);
                    jal(ctx, 0x1BCE30u, gen::fn_K_Field_Get_001b9120);
                    v1 = addu(s6, v0);
                    lbu(a0, v1, 74);
                    v1 = 1;
                    if (a0 == v1) {
                        backedge(ctx);
                        continue;
                    }
                    // 0x001bce4c
                    charge(ctx, 7);
                    jal(ctx, 0x1BCE4Cu, gen::fn_K_Field_Get_001b9120);
                    v1 = addu(s6, v0);
                    lbu(a0, v1, 74);
                    v1 = 3;
                    if (a0 != v1) {
                        goto L_001bce68;
                    }
                    backedge(ctx);
                }
                // 0x001bcf1c
                charge(ctx, 15);
                lhu(a1, sp, 0x16C);
                lhu(a2, sp, 0x168);
                a3 = dsll32(s5, 16);
                a3 = dsra32(a3, 16);
                a0 = addiu(sp, 0x110);
                jal(ctx, 0x1BCF30u, gen::fn_sub_1BB090_001bb090);
                lw(s1, sp, 0x16C);
                lw(s0, sp, 0x168);
                jal(ctx, 0x1BCF40u, gen::fn_K_Field_Get_001b9120);
                lw(v1, v0, 56);
                v1 = v1 & 0x1;
                if (v1 == 0) {
                    // 0x001bcf58
                    charge(ctx, 3);
                    s5 = 0;
                    for (;;) {
                        // 0x001bd28c
                        charge(ctx, 4);
                        lbu(v1, sp, 0x112);
                        v1 = sltu(s5, v1);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001bcf64
                        charge(ctx, 11);
                        s6 = 0;
                        v1 = addu(s0, s5);
                        s4 = sll(v1, 8);
                        s7 = addiu(s4, -184);
                        fp = addiu(s4, -0xA8);
                        v1 = addiu(s4, -200);
                        sq(v1, sp, 0xD0);
                        v1 = addiu(s4, -440);
                        sq(v1, sp, 0xC0);
                        for (;;) {
                            // 0x001bd278
                            charge(ctx, 4);
                            lbu(v1, sp, 0x111);
                            v1 = sltu(s6, v1);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x001bcf90
                            charge(ctx, 9);
                            v0 = addu(s1, s6);
                            s3 = sll(v0, 4);
                            jal(ctx, 0x1BCF98u, gen::fn_K_Field_Get_001b9120);
                            v0 = addu(s7, v0);
                            v0 = addu(v0, s3);
                            lbu(v0, v0, 0);
                            if (v0 == 0) {
                                // 0x001bcfb4
                                charge(ctx, 8);
                                jal(ctx, 0x1BCFB4u, gen::fn_K_Field_Get_001b9120);
                                v0 = addu(s4, v0);
                                v0 = addu(v0, s3);
                                lbu(v0, v0, 83);
                                v0 = v0 & 0x10;
                                if (v0 == 0) {
                                    // 0x001bcfd4
                                    charge(ctx, 8);
                                    jal(ctx, 0x1BCFD4u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(fp, v0);
                                    v0 = addu(v0, s3);
                                    lbu(v1, v0, 0);
                                    v0 = 1;
                                    if (v1 != v0) {
                                        // 0x001bcff4
                                        charge(ctx, 9);
                                        jal(ctx, 0x1BCFF4u, gen::fn_K_Field_Get_001b9120);
                                        lq(v1, sp, 0xD0);
                                        v0 = addu(v1, v0);
                                        v0 = addu(v0, s3);
                                        lbu(v1, v0, 0);
                                        v0 = 1;
                                        if (v1 != v0) {
                                            // 0x001bd018
                                            charge(ctx, 9);
                                            jal(ctx, 0x1BD018u, gen::fn_K_Field_Get_001b9120);
                                            lq(v1, sp, 0xC0);
                                            v0 = addu(v1, v0);
                                            v0 = addu(v0, s3);
                                            lbu(v1, v0, 0);
                                            v0 = 1;
                                            if (v1 != v0) {
                                                // 0x001bd03c
                                                charge(ctx, 6);
                                                jal(ctx, 0x1BD03Cu, gen::fn_K_Field_Get_001b9120);
                                                v0 = addu(s7, v0);
                                                v1 = addu(v0, s3);
                                                v0 = 2;
                                                sb(v0, v1, 0);
                                            }
                                        }
                                    }
                                }
                            }
                            // 0x001bd054
                            charge(ctx, 7);
                            jal(ctx, 0x1BD054u, gen::fn_K_Field_Get_001b9120);
                            v0 = addu(s4, v0);
                            v0 = addu(v0, s3);
                            lbu(v0, v0, 56);
                            if (v0 == 0) {
                                // 0x001bd070
                                charge(ctx, 8);
                                jal(ctx, 0x1BD070u, gen::fn_K_Field_Get_001b9120);
                                v0 = addu(s4, v0);
                                v0 = addu(v0, s3);
                                lbu(v0, v0, 83);
                                v0 = v0 & 0x20;
                                if (v0 == 0) {
                                    // 0x001bd090
                                    charge(ctx, 9);
                                    jal(ctx, 0x1BD090u, gen::fn_K_Field_Get_001b9120);
                                    lq(v1, sp, 0xD0);
                                    v0 = addu(v1, v0);
                                    v0 = addu(v0, s3);
                                    lbu(v1, v0, 0);
                                    v0 = 1;
                                    if (v1 != v0) {
                                        // 0x001bd0b4
                                        charge(ctx, 8);
                                        jal(ctx, 0x1BD0B4u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(s4, v0);
                                        v0 = addu(v0, s3);
                                        lbu(v1, v0, 312);
                                        v0 = 1;
                                        if (v1 != v0) {
                                            // 0x001bd0d4
                                            charge(ctx, 8);
                                            jal(ctx, 0x1BD0D4u, gen::fn_K_Field_Get_001b9120);
                                            v0 = addu(s4, v0);
                                            v0 = addu(v0, s3);
                                            lbu(v1, v0, 40);
                                            v0 = 1;
                                            if (v1 != v0) {
                                                // 0x001bd0f4
                                                charge(ctx, 6);
                                                jal(ctx, 0x1BD0F4u, gen::fn_K_Field_Get_001b9120);
                                                v0 = addu(s4, v0);
                                                v1 = addu(v0, s3);
                                                v0 = 2;
                                                sb(v0, v1, 56);
                                            }
                                        }
                                    }
                                }
                            }
                            // 0x001bd10c
                            charge(ctx, 7);
                            jal(ctx, 0x1BD10Cu, gen::fn_K_Field_Get_001b9120);
                            v0 = addu(s4, v0);
                            v0 = addu(v0, s3);
                            lbu(v0, v0, 328);
                            if (v0 == 0) {
                                // 0x001bd128
                                charge(ctx, 8);
                                jal(ctx, 0x1BD128u, gen::fn_K_Field_Get_001b9120);
                                v0 = addu(s4, v0);
                                v0 = addu(v0, s3);
                                lbu(v0, v0, 83);
                                v0 = v0 & 0x40;
                                if (v0 == 0) {
                                    // 0x001bd148
                                    charge(ctx, 8);
                                    jal(ctx, 0x1BD148u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(s4, v0);
                                    v0 = addu(v0, s3);
                                    lbu(v1, v0, 344);
                                    v0 = 1;
                                    if (v1 != v0) {
                                        // 0x001bd168
                                        charge(ctx, 8);
                                        jal(ctx, 0x1BD168u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(s4, v0);
                                        v0 = addu(v0, s3);
                                        lbu(v1, v0, 312);
                                        v0 = 1;
                                        if (v1 != v0) {
                                            // 0x001bd188
                                            charge(ctx, 8);
                                            jal(ctx, 0x1BD188u, gen::fn_K_Field_Get_001b9120);
                                            v0 = addu(s4, v0);
                                            v0 = addu(v0, s3);
                                            lbu(v1, v0, 584);
                                            v0 = 1;
                                            if (v1 != v0) {
                                                // 0x001bd1a8
                                                charge(ctx, 6);
                                                jal(ctx, 0x1BD1A8u, gen::fn_K_Field_Get_001b9120);
                                                v0 = addu(s4, v0);
                                                v1 = addu(v0, s3);
                                                v0 = 2;
                                                sb(v0, v1, 328);
                                            }
                                        }
                                    }
                                }
                            }
                            // 0x001bd1c0
                            charge(ctx, 7);
                            jal(ctx, 0x1BD1C0u, gen::fn_K_Field_Get_001b9120);
                            v1 = addu(s4, v0);
                            v1 = addu(v1, s3);
                            lbu(v1, v1, 88);
                            if (v1 == 0) {
                                // 0x001bd1dc
                                charge(ctx, 8);
                                jal(ctx, 0x1BD1DCu, gen::fn_K_Field_Get_001b9120);
                                v1 = addu(s4, v0);
                                v1 = addu(v1, s3);
                                lbu(v1, v1, 83);
                                v1 = v1 & 0x80;
                                if (v1 == 0) {
                                    // 0x001bd1fc
                                    charge(ctx, 8);
                                    jal(ctx, 0x1BD1FCu, gen::fn_K_Field_Get_001b9120);
                                    v1 = addu(fp, v0);
                                    v1 = addu(v1, s3);
                                    lbu(a0, v1, 0);
                                    v1 = 1;
                                    if (a0 != v1) {
                                        // 0x001bd21c
                                        charge(ctx, 8);
                                        jal(ctx, 0x1BD21Cu, gen::fn_K_Field_Get_001b9120);
                                        v1 = addu(s4, v0);
                                        v1 = addu(v1, s3);
                                        lbu(a0, v1, 344);
                                        v1 = 1;
                                        if (a0 != v1) {
                                            // 0x001bd23c
                                            charge(ctx, 8);
                                            jal(ctx, 0x1BD23Cu, gen::fn_K_Field_Get_001b9120);
                                            v1 = addu(s4, v0);
                                            v1 = addu(v1, s3);
                                            lbu(a0, v1, 104);
                                            v1 = 1;
                                            if (a0 != v1) {
                                                // 0x001bd25c
                                                charge(ctx, 6);
                                                jal(ctx, 0x1BD25Cu, gen::fn_K_Field_Get_001b9120);
                                                v1 = addu(s4, v0);
                                                a0 = addu(v1, s3);
                                                v1 = 2;
                                                sb(v1, a0, 88);
                                            }
                                        }
                                    }
                                }
                            }
                            // 0x001bd274
                            charge(ctx, 1);
                            s6 = addiu(s6, 1);
                        }
                        // 0x001bd288
                        charge(ctx, 1);
                        s5 = addiu(s5, 1);
                    }
                }
                goto L_001bd29c;
            }
        L_001bcb58:
            charge(ctx, 2);
        }
    }
    // 0x001bd418 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x170);
    return;
L_001bcca4_18:
    charge(ctx, 4);
    v1 = 1;
    sw(v1, gp, f4::gpv::kGenFailed);  // 0x7CE264
    // 0x001bd418 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x170);
}

// 0x001BD450 sub_1BD450 [K_FldDungeon_GenerateFloor] -- 1136 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1BD450(set): generates a random floor's grid in sField +72 (from sub_1B10F0 step 8; set = major - 20, or - 40 in
// The Answer). Loop until the start cell (sField +60 / +61) is a floor cell of kind 4 (stairs) and no failure is
// pending: clear the failure flag and the placed-block counter, clear the 4,096-byte grid, mark the border ring
// (rows 0 / 15 and columns 0 / 15) 2; draw the start cell (RpRandom % 12 + 2 for x and z until a free cell; turn
// RpRandom & 3 -> +64), then the seed cell (RpRandom % 11 + 2, until the cell and its +x, +z, +x+z neighbours are
// free; turn -> +65); grow the floor from the seed (sub_1BCAC0(set, seedX, seedZ, 0, 0)); count the floor cells
// and the kind-4 cells: fewer than +66 or more than +67 floor cells, or fewer than two kind-4 cells, fail the
// attempt. Inputs: the set, sField +66 / +67, The Answer flag and the RpRandom state -- nothing else (field4.h).
void sub_1BD450(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001bd450
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s6 = a0;
    for (;;) {
        // 0x001bd804
        charge(ctx, 16);
        jal(ctx, 0x1BD804u, gen::fn_K_Field_Get_001b9120);
        lbu(v0, v0, f4::fld::kStartZ);
        s0 = sll(v0, 8);
        jal(ctx, 0x1BD814u, gen::fn_K_Field_Get_001b9120);
        s0 = addu(v0, s0);
        jal(ctx, 0x1BD820u, gen::fn_K_Field_Get_001b9120);
        lbu(v0, v0, f4::fld::kStartX);
        v0 = sll(v0, 4);
        v0 = addu(s0, v0);
        lbu(v1, v0, f4::gcell::kState);
        v0 = 1;
        if (v1 != v0) {
            backedge(ctx);
        } else {
            goto L_001bd844_32;
        }
    L_001bd480:
        charge(ctx, 12);
        sw(zero, gp, f4::gpv::kGenFailed);  // 0x7CE264
        sw(zero, gp, f4::gpv::kGenPlaced);  // 0x7CE25C
        jal(ctx, 0x1BD488u, gen::fn_K_Field_Get_001b9120);
        a0 = addiu(v0, f4::fld::kGrid);
        a1 = 0;
        a2 = 4096;
        jal(ctx, 0x1BD49Cu, gen::fn_memset_00521408);
        s1 = 0;
        for (;;) {
            // 0x001bd4dc
            charge(ctx, 3);
            v0 = sltiu(s1, 16);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001bd4b0
            charge(ctx, 11);
            s0 = sll(s1, 4);
            s2 = 2;
            jal(ctx, 0x1BD4B8u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s0);
            sb(s2, v0, f4::gcell::kState);
            jal(ctx, 0x1BD4C8u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s0);
            sb(s2, v0, f4::gcell::kLastRow);
            s1 = addiu(s1, 1);
        }
        // 0x001bd4e8
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x001bd520
            charge(ctx, 3);
            v0 = sltiu(s1, 16);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001bd4f4
            charge(ctx, 11);
            s0 = sll(s1, 8);
            s2 = 2;
            jal(ctx, 0x1BD4FCu, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s0);
            sb(s2, v0, f4::gcell::kState);
            jal(ctx, 0x1BD50Cu, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s0);
            sb(s2, v0, f4::gcell::kLastCol);
            s1 = addiu(s1, 1);
        }
        // 0x001bd52c
        charge(ctx, 10);
        jal(ctx, 0x1BD52Cu, gen::fn_K_Field_Get_001b9120);
        sb(zero, v0, f4::fld::kStartX);
        s0 = 0;
        jal(ctx, 0x1BD53Cu, gen::fn_K_Field_Get_001b9120);
        sb(zero, v0, f4::fld::kStartZ);
        s2 = s0;
        for (;;) {
            // 0x001bd5c4
            charge(ctx, 9);
            jal(ctx, 0x1BD5C4u, gen::fn_K_Field_Get_001b9120);
            v1 = sll(s2, 8);
            v1 = addu(v0, v1);
            v0 = sll(s0, 4);
            v0 = addu(v1, v0);
            lbu(v0, v0, f4::gcell::kState);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001bd554
            charge(ctx, 28);
            jal(ctx, 0x1BD554u, gen::fn_sub_488F30_00488f30);
            v1 = 12;
            divu(v0, v1);
            mfhi(v0);
            v0 = addiu(v0, 2);
            s0 = v0 & 0xFF;
            jal(ctx, 0x1BD570u, gen::fn_K_Field_Get_001b9120);
            sb(s0, v0, f4::fld::kStartX);
            s0 = s0 & 0xFF;
            jal(ctx, 0x1BD580u, gen::fn_sub_488F30_00488f30);
            v1 = 12;
            divu(v0, v1);
            mfhi(v0);
            v0 = addiu(v0, 2);
            s1 = v0 & 0xFF;
            jal(ctx, 0x1BD59Cu, gen::fn_K_Field_Get_001b9120);
            sb(s1, v0, f4::fld::kStartZ);
            s2 = s1 & 0xFF;
            jal(ctx, 0x1BD5ACu, gen::fn_sub_488F30_00488f30);
            s1 = v0 & 0x3;
            jal(ctx, 0x1BD5B8u, gen::fn_K_Field_Get_001b9120);
            sb(s1, v0, f4::fld::kStartRot);
        }
        // 0x001bd5e8
        charge(ctx, 10);
        jal(ctx, 0x1BD5E8u, gen::fn_K_Field_Get_001b9120);
        sb(zero, v0, f4::fld::kSeedX);
        s0 = 0;
        jal(ctx, 0x1BD5F8u, gen::fn_K_Field_Get_001b9120);
        sb(zero, v0, f4::fld::kSeedZ);
        s2 = s0;
        for (;;) {
            // 0x001bd680
            charge(ctx, 9);
            s1 = sll(s2, 8);
            s0 = sll(s0, 4);
            jal(ctx, 0x1BD688u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s1);
            v0 = addu(v0, s0);
            lbu(v0, v0, f4::gcell::kState);
            if (v0 != 0) {
                backedge(ctx);
            } else {
                goto L_001bd6a4_13;
            }
        L_001bd610:
            charge(ctx, 28);
            jal(ctx, 0x1BD610u, gen::fn_sub_488F30_00488f30);
            v1 = 11;
            divu(v0, v1);
            mfhi(v0);
            v0 = addiu(v0, 2);
            s0 = v0 & 0xFF;
            jal(ctx, 0x1BD62Cu, gen::fn_K_Field_Get_001b9120);
            sb(s0, v0, f4::fld::kSeedX);
            s0 = s0 & 0xFF;
            jal(ctx, 0x1BD63Cu, gen::fn_sub_488F30_00488f30);
            v1 = 11;
            divu(v0, v1);
            mfhi(v0);
            v0 = addiu(v0, 2);
            s1 = v0 & 0xFF;
            jal(ctx, 0x1BD658u, gen::fn_K_Field_Get_001b9120);
            sb(s1, v0, f4::fld::kSeedZ);
            s2 = s1 & 0xFF;
            jal(ctx, 0x1BD668u, gen::fn_sub_488F30_00488f30);
            s1 = v0 & 0x3;
            jal(ctx, 0x1BD674u, gen::fn_K_Field_Get_001b9120);
            sb(s1, v0, f4::fld::kSeedRot);
        }
    L_001bd6f8_16:
        charge(ctx, 17);
        jal(ctx, 0x1BD6F8u, gen::fn_K_Field_Get_001b9120);
        lbu(s0, v0, f4::fld::kSeedX);
        jal(ctx, 0x1BD704u, gen::fn_K_Field_Get_001b9120);
        lbu(a2, v0, f4::fld::kSeedZ);
        a0 = s6;
        a1 = s0;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x1BD720u, gen::fn_sub_1BCAC0_001bcac0);
        s1 = 0;
        s3 = 0;
        s2 = 0;
        for (;;) {
            // 0x001bd7ac
            charge(ctx, 3);
            v0 = sltiu(s1, 16);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001bd73c
            charge(ctx, 4);
            s4 = 0;
            s0 = sll(s1, 8);
            for (;;) {
                // 0x001bd79c
                charge(ctx, 3);
                v0 = sltiu(s4, 16);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001bd74c
                charge(ctx, 9);
                s5 = sll(s4, 4);
                jal(ctx, 0x1BD750u, gen::fn_K_Field_Get_001b9120);
                v0 = addu(s0, v0);
                v0 = addu(v0, s5);
                lbu(v1, v0, f4::gcell::kState);
                v0 = 1;
                if (v1 == v0) {
                    // 0x001bd770
                    charge(ctx, 1);
                    s3 = addiu(s3, 1);
                }
                // 0x001bd774
                charge(ctx, 8);
                jal(ctx, 0x1BD774u, gen::fn_K_Field_Get_001b9120);
                v0 = addu(s0, v0);
                v0 = addu(v0, s5);
                lbu(v1, v0, f4::gcell::kKind);
                v0 = 4;
                if (v1 == v0) {
                    // 0x001bd794
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x001bd798
                charge(ctx, 1);
                s4 = addiu(s4, 1);
            }
            // 0x001bd7a8
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
        // 0x001bd7b8
        charge(ctx, 6);
        jal(ctx, 0x1BD7B8u, gen::fn_K_Field_Get_001b9120);
        lbu(v0, v0, f4::fld::kMaxCells);
        at = slt(v0, s3);
        if (at == 0) {
            // 0x001bd7d0
            charge(ctx, 6);
            jal(ctx, 0x1BD7D0u, gen::fn_K_Field_Get_001b9120);
            lbu(v0, v0, f4::fld::kMinCells);
            at = slt(s3, v0);
            if (at != 0) {
                goto L_001bd7e8;
            }
            goto L_001bd7f0;
        }
    L_001bd7e8:
        charge(ctx, 2);
        v0 = 1;
        sw(v0, gp, f4::gpv::kGenFailed);  // 0x7CE264
    L_001bd7f0:
        charge(ctx, 3);
        at = slti(s2, 2);
        if (at != 0) {
            // 0x001bd7fc
            charge(ctx, 2);
            v0 = 1;
            sw(v0, gp, f4::gpv::kGenFailed);  // 0x7CE264
        }
    }
L_001bd894_34:
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_001bd6a4_13:
    charge(ctx, 7);
    jal(ctx, 0x1BD6A4u, gen::fn_K_Field_Get_001b9120);
    v0 = addu(v0, s1);
    v0 = addu(v0, s0);
    lbu(v0, v0, 88);
    if (v0 != 0) {
        backedge(ctx);
        goto L_001bd610;
    }
    // 0x001bd6c0
    charge(ctx, 7);
    jal(ctx, 0x1BD6C0u, gen::fn_K_Field_Get_001b9120);
    v0 = addu(v0, s1);
    v0 = addu(v0, s0);
    lbu(v0, v0, 328);
    if (v0 != 0) {
        backedge(ctx);
        goto L_001bd610;
    }
    // 0x001bd6dc
    charge(ctx, 7);
    jal(ctx, 0x1BD6DCu, gen::fn_K_Field_Get_001b9120);
    v0 = addu(v0, s1);
    v0 = addu(v0, s0);
    lbu(v0, v0, 344);
    if (v0 == 0) {
        goto L_001bd6f8_16;
    }
    backedge(ctx);
    goto L_001bd610;
L_001bd844_32:
    charge(ctx, 16);
    jal(ctx, 0x1BD844u, gen::fn_K_Field_Get_001b9120);
    lbu(v0, v0, f4::fld::kStartZ);
    s0 = sll(v0, 8);
    jal(ctx, 0x1BD854u, gen::fn_K_Field_Get_001b9120);
    s0 = addu(v0, s0);
    jal(ctx, 0x1BD860u, gen::fn_K_Field_Get_001b9120);
    lbu(v1, v0, f4::fld::kStartX);
    v1 = sll(v1, 4);
    v1 = addu(s0, v1);
    lbu(a0, v1, f4::gcell::kKind);
    v1 = 4;
    if (a0 != v1) {
        backedge(ctx);
        goto L_001bd480;
    }
    // 0x001bd884
    charge(ctx, 4);
    lw(a0, gp, f4::gpv::kGenFailed);  // 0x7CE264
    v1 = 1;
    if (a0 != v1) {
        goto L_001bd894_34;
    }
    backedge(ctx);
    goto L_001bd480;
}

// 0x001BD8C0 sub_1BD8C0 [K_FldDungeon_BuildAllBlocks] -- 132 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1BD8C0(): builds every block of the grid: sub_1BB300(scene = 16 z + x, x, z) for z, x in 0..15.
void sub_1BD8C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001bd8c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = 0;
    for (;;) {
        // 0x001bd91c
        charge(ctx, 3);
        v1 = slti(s2, 16);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001bd8e0
        charge(ctx, 4);
        s1 = 0;
        s0 = sll(s2, 4);
        for (;;) {
            // 0x001bd90c
            charge(ctx, 3);
            v1 = slti(s1, 16);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001bd8f0
            charge(ctx, 7);
            v0 = addu(s1, s0);
            a0 = v0 & 0xFFFF;
            a1 = s1 & 0xFFFF;
            a2 = s2 & 0xFFFF;
            jal(ctx, 0x1BD900u, gen::fn_sub_1BB300_001bb300);
            s1 = addiu(s1, 1);
        }
        // 0x001bd918
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x001bd928
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001BF220 sub_1BF220 [K_FldDungeon_GetCellExitPos] -- 276 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1BF220(out, x, z): out = the position of the exit / stairs marker (type 18 scene resource) whose id (low 10
// bits) is the cell's link word (+12), on random and fixed floors; (0, 0, 0) otherwise or when none matches. Callers:
// the Y_* enemy-think and NPC layers (0x42FD80..0x452F70).
void sub_1BF220(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    constexpr s32 kResNext = 248, kResPos = 256;  // scene resource: the next of its type, the position
    // 0x001bf220
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;  // out
    s0 = a1;  // x
    s3 = a2;  // z
    a0 = 18;  // the exit / stairs markers
    jal(ctx, 0x1BF248u, gen::fn_sub_3B5D50_003b5d50);
    s1 = v0;
    a0 = addiu(sp, 0x50);  // the position, (0, 0, 0) unless found
    a1 = 0;
    a2 = 12;
    jal(ctx, 0x1BF260u, gen::fn_memset_00521408);
    jal(ctx, 0x1BF268u, gen::fn_K_Scene_IsRandomFloor_001a0250);
    v1 = 1;
    bool tartarus = v0 == v1;
    if (!tartarus) {
        // 0x001bf27c
        charge(ctx, 5);
        jal(ctx, 0x1BF27Cu, gen::fn_sub_1A02C0_001a02c0);  // a fixed floor
        v1 = 1;
        tartarus = v0 == v1;
    }
    if (tartarus) {
        // 0x001bf290: s0 = the cell's offset 256 z + 16 x
        charge(ctx, 7);
        v1 = s3 & 0xFFFF;
        a0 = sll(v1, 8);
        v1 = s0 & 0xFFFF;
        v1 = sll(v1, 4);
        s0 = addu(a0, v1);
        for (;;) {
            // 0x001bf2f4
            charge(ctx, 2);
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001bf2ac: the marker whose id is the cell's link word
            charge(ctx, 9);
            lhu(v0, s1, 0);
            s3 = v0 & 0x3FF;
            jal(ctx, 0x1BF2B4u, gen::fn_K_Field_Get_001b9120);
            v1 = addu(s0, v0);
            lw(v1, v1, f4::gcell::kLink);
            v1 = v1 & 0x3FF;
            if (s3 == v1) {
                // 0x001bf2d0: found: its position
                charge(ctx, 8);
                lwc1(f2, s1, kResPos);
                lwc1(f1, s1, kResPos + 4);
                lwc1(f0, s1, kResPos + 8);
                swc1(f2, sp, 0x50);
                swc1(f1, sp, 0x54);
                swc1(f0, sp, 0x58);
                break;
            }
            // 0x001bf2f0
            charge(ctx, 1);
            lw(s1, s1, kResNext);
        }
    }
    // 0x001bf2fc (the shared epilogue): out = the position
    charge(ctx, 14);
    lwc1(f2, sp, 0x50);
    lwc1(f1, sp, 0x54);
    lwc1(f0, sp, 0x58);
    swc1(f2, s2, 0);
    swc1(f1, s2, 4);
    swc1(f0, s2, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001BF340 sub_1BF340 [K_FldDungeon_PickFloorKind] -- 560 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1BF340(entry) -> the floor kind (26_field.md 6.3), from the g_data counters (sub_16F380 get / sub_16F3E0 set):
// c12 the highest floor reached, c58 the countdown length, c59 the countdown, c60 the percent chance, c61 / c62 /
// c55 / c54 the weights of kinds 1..4. 0 at or above c12; a countdown below 1 is reset (c59 = c58) -> 0; a floor
// entry with a minor (+2 != 0) -> 0; a countdown above 1 counts down (c59 - 1) -> 0; at 1: RpRandom % 100 >= c60 -> 0
// (the countdown stays at 1: the next floor rolls again), else the countdown is reset and the weighted pick
// RpRandom % (c61 + c62 + c55 + c54) gives 1 / 2 / 3, or 4 when one of the party slots 0..2 holds a member
// (sub_16DD60 > 0), else 0.
void sub_1BF340(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    constexpr s32 kHighestFloor = 12, kCountdownLength = 58, kCountdown = 59, kChance = 60;
    constexpr s32 kWeight1 = 61, kWeight2 = 62, kWeight3 = 55, kWeight4 = 54;
    // 0x001bf340
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;  // the floor entry
    a0 = kCountdown;
    jal(ctx, 0x1BF360u, gen::fn_sub_16F380_0016f380);
    s1 = v0;  // the countdown
    jal(ctx, 0x1BF36Cu, gen::fn_K_FldDungeon_GetCurrentFloor_001bff20);
    s0 = v0;
    a0 = kHighestFloor;
    jal(ctx, 0x1BF37Cu, gen::fn_sub_16F380_0016f380);
    v0 = sltu(s0, v0);
    if (v0 == 0) {
        // 0x001bf390: at or above the highest floor reached
        charge(ctx, 3);
        v0 = 0;
    } else {
        // 0x001bf39c
        charge(ctx, 3);
        a1 = addiu(s1, -1);
        if (i64(a1) < 0) {
            // 0x001bf3a8: the countdown ran out: reset it
            charge(ctx, 9);
            a0 = kCountdownLength;
            jal(ctx, 0x1BF3ACu, gen::fn_sub_16F380_0016f380);
            a0 = kCountdown;
            a1 = v0;
            jal(ctx, 0x1BF3BCu, gen::fn_sub_16F3E0_0016f3e0);
            // 0x001bf54c
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x001bf3cc
            charge(ctx, 3);
            lhu(v0, s2, f4::dngfloor::kMinor);
            if (v0 != 0) {
                // 0x001bf54c: a scripted floor entry
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x001bf3d8
                charge(ctx, 2);
                if (a1 != 0) {
                    // 0x001bf540: count down (c59 = countdown - 1)
                    charge(ctx, 3);
                    a0 = kCountdown;
                    jal(ctx, 0x1BF544u, gen::fn_sub_16F3E0_0016f3e0);
                    // 0x001bf54c
                    charge(ctx, 1);
                    v0 = 0;
                } else {
                    // 0x001bf3e0: the countdown is at 1: roll RpRandom % 100 against c60
                    charge(ctx, 11);
                    jal(ctx, 0x1BF3E0u, gen::fn_sub_488F30_00488f30);
                    v1 = 100;
                    divu(v0, v1);
                    mfhi(s0);
                    a0 = kChance;
                    jal(ctx, 0x1BF3F8u, gen::fn_sub_16F380_0016f380);
                    at = slt(s0, v0);
                    if (at == 0) {
                        // 0x001bf54c: no special floor this time
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x001bf40c: the weighted pick; s0 / s3 / s2 = the cumulative weights of kinds 1 / 2 / 3
                        charge(ctx, 33);
                        a0 = kWeight1;
                        jal(ctx, 0x1BF410u, gen::fn_sub_16F380_0016f380);
                        s0 = v0;
                        a0 = kWeight2;
                        jal(ctx, 0x1BF420u, gen::fn_sub_16F380_0016f380);
                        s3 = v0;
                        a0 = kWeight3;
                        jal(ctx, 0x1BF430u, gen::fn_sub_16F380_0016f380);
                        s2 = v0;
                        a0 = kWeight4;
                        jal(ctx, 0x1BF440u, gen::fn_sub_16F380_0016f380);
                        s1 = v0;
                        s3 = addu(s0, s3);
                        s2 = addu(s2, s3);
                        jal(ctx, 0x1BF454u, gen::fn_sub_488F30_00488f30);
                        v1 = addu(s1, s2);
                        divu(v0, v1);
                        mfhi(s1);  // the pick
                        a0 = kCountdownLength;
                        jal(ctx, 0x1BF46Cu, gen::fn_sub_16F380_0016f380);
                        a0 = kCountdown;
                        a1 = v0;
                        jal(ctx, 0x1BF47Cu, gen::fn_sub_16F3E0_0016f3e0);
                        at = slt(s1, s0);
                        if (at != 0) {
                            // 0x001bf490
                            charge(ctx, 3);
                            v0 = 1;
                        } else {
                            // 0x001bf49c (the original tests pick < w1 a second time)
                            charge(ctx, 3);
                            v0 = slt(s1, s0);
                            bool two = false;
                            if (v0 == 0) {
                                // 0x001bf4a8
                                charge(ctx, 3);
                                at = slt(s1, s3);
                                two = at != 0;
                            }
                            if (two) {
                                // 0x001bf4b4
                                charge(ctx, 3);
                                v0 = 2;
                            } else {
                                // 0x001bf4c0
                                charge(ctx, 3);
                                v0 = slt(s1, s3);
                                bool three = false;
                                if (v0 == 0) {
                                    // 0x001bf4cc
                                    charge(ctx, 3);
                                    at = slt(s1, s2);
                                    three = at != 0;
                                }
                                if (three) {
                                    // 0x001bf4d8
                                    charge(ctx, 3);
                                    v0 = 3;
                                } else {
                                    // 0x001bf4e4: kind 4 needs a member in party slots 0..2
                                    charge(ctx, 3);
                                    s0 = 0;
                                    for (;;) {
                                        // 0x001bf510
                                        charge(ctx, 3);
                                        v0 = slti(s0, 3);
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                        // 0x001bf4f0
                                        charge(ctx, 7);
                                        a0 = s0;
                                        jal(ctx, 0x1BF4F4u, gen::fn_sub_16DD60_0016dd60);
                                        v0 = dsll32(v0, 16);
                                        v0 = dsra32(v0, 16);
                                        if (i64(v0) > 0) {
                                            break;
                                        }
                                        // 0x001bf50c
                                        charge(ctx, 1);
                                        s0 = addiu(s0, 1);
                                    }
                                    // 0x001bf51c
                                    charge(ctx, 3);
                                    at = slti(s0, 3);
                                    if (at == 0) {
                                        // 0x001bf534
                                        charge(ctx, 3);
                                        v0 = 0;
                                    } else {
                                        // 0x001bf528
                                        charge(ctx, 3);
                                        v0 = 4;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x001bf550 (the shared epilogue)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001BF570 K_FldDungeon_UpdateTask -- 1408 bytes; frame 0xC0: ra sp+0x60, s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq)
// K_FldDungeon_UpdateTask(task) -> 0, or -1 to be destroyed: the "automatic dungeon" (26_field.md 6.1; work:
// field4.h dng). Jump table 0x7B6B80:
//   0 wait for fobj000, the dungeon script (sub_1C0210 -> +52 / +56), the battle-effect pack and EPLs; floor table
//     +32 = gFldDngFloorsData; the floor's EPL "field/effect/DNG%02d.EPL" (entry +13; none when the next entry's
//     +13 is 255)                                                                                      -> 1
//   1 the EPL ready -> its instance (+48)                                                            -> 2
//   2 the floor kind (+40, sub_1BF340), the next-floor flag word 0x86E580 = 0, the floor's field root (+24) with
//     flags entry.flags | 0x80000000, the entry +8 and the floor's cell bounds; on the block-entry floors
//     {2, 17, 65, 115, 165, 215} outside The Answer the root is held (sub_1BAA50) for the stratum title (flag 5153)
//     -> 8, else                                                                                       -> 3
//   3 the floor runs; the shutdown word +12 -> 9
//   4..6 one frame each (a floor change requested by sub_1BFCC0)                                       -> 7
//   7 as 0..2 for the next floor, the flags or-ed into +36                                            -> 3 / 8
//   8 the stratum title done: flag 5153 off, the root released                                         -> 3
//   9 -> -1.
void K_FldDungeon_UpdateTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001bf570
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x60);
    sq(s2, sp, 0x50);
    sq(s1, sp, 0x40);
    sq(s0, sp, 0x30);
    s2 = a0;
    lw(s0, a0, f4::kTaskWork);
    lw(a0, s0, f4::dng::kState);
    at = sltiu(a0, 10);
    if (at != 0) {
        // 0x001bf59c
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 27520);  // &0x7B6B80
        v0 = sll(a0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x1BF5B8u:  // table[0]  -- state 0: models, dungeon script, packs ready; the floor table and the floor EPL -> 1
            // 0x001bf5b8
            charge(ctx, 3);
            lw(a0, gp, f4::gpv::kFloorObj0);  // 0x7CE280
            if (a0 != 0) {
                // 0x001bf5c4
                charge(ctx, 4);
                jal(ctx, 0x1BF5C4u, gen::fn_sub_316F70_00316f70);
                if (v0 != 0) {
                    goto L_001bf5d4;
                }
                goto L_001bfad0;
            }
        L_001bf5d4:
            charge(ctx, 5);
            lw(a0, s0, f4::dng::kScript);
            jal(ctx, 0x1BF5D8u, gen::fn_sub_1C0210_001c0210);
            if (v0 != 0) {
                // 0x001bf5e8
                charge(ctx, 5);
                sw(zero, s0, f4::dng::kScript);
                jal(ctx, 0x1BF5ECu, gen::fn_sub_1C0440_001c0440);
                if (v0 != 0) {
                    // 0x001bf5fc
                    charge(ctx, 4);
                    jal(ctx, 0x1BF5FCu, gen::fn_sub_1C0740_001c0740);
                    if (v0 != 0) {
                        // 0x001bf60c
                        charge(ctx, 10);
                        v1 = 0x860000;
                        v1 = addiu(v1, 32608);  // &gFldDngFloorsData
                        sw(v1, s0, f4::dng::kFloorTable);
                        lw(v0, s0, f4::dng::kFloor);
                        v0 = sll(v0, 4);
                        v1 = addu(v0, v1);
                        lbu(v0, v1, 29);
                        at = slti(v0, 255);
                        if (at == 0) {
                            // 0x001bf670
                            charge(ctx, 1);
                            sw(zero, s0, f4::dng::kEpl);
                        } else {
                            // 0x001bf634
                            charge(ctx, 15);
                            lbu(a2, v1, 13);
                            a0 = addiu(sp, 0x70);
                            a1 = 0x680000;
                            a1 = addiu(a1, 13280);  // "field/effect/DNG%02d.EPL"
                            jal(ctx, 0x1BF644u, gen::fn_sprintf_00523ac8);
                            a0 = s2;
                            a1 = addiu(sp, 0x70);
                            a2 = si(-1);
                            a3 = 0;
                            jal(ctx, 0x1BF65Cu, gen::fn_sub_1A9080_001a9080);
                            sw(v0, s0, f4::dng::kEpl);
                        }
                        // 0x001bf674
                        charge(ctx, 3);
                        lw(v0, s0, f4::dng::kState);
                        v0 = addiu(v0, 1);
                        sw(v0, s0, f4::dng::kState);
                    // state 1: (shares its body with 2 through the original's gotos) the EPL instance (the state's entry)
                    L_001bf680:
                        charge(ctx, 4);
                        v1 = addiu(sp, 0xB0);
                        v0 = 12;
                        if (v1 != 0) {
                            for (;;) {
                                // 0x001bf690
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
                        // 0x001bf6ac
                        charge(ctx, 3);
                        lw(a0, s0, f4::dng::kEpl);
                        if (a0 != 0) {
                            // 0x001bf6b8
                            charge(ctx, 4);
                            jal(ctx, 0x1BF6B8u, gen::fn_sub_1A9180_001a9180);
                            if (v0 != 0) {
                                // 0x001bf6c8
                                charge(ctx, 5);
                                lw(a0, s0, f4::dng::kEpl);
                                a1 = addiu(sp, 0xB0);
                                jal(ctx, 0x1BF6D0u, gen::fn_sub_1A91B0_001a91b0);
                                sw(v0, s0, f4::dng::kEplObj);
                                goto L_001bf6dc;
                            }
                            goto L_001bfad0;
                        }
                    L_001bf6dc:
                        charge(ctx, 3);
                        lw(v0, s0, f4::dng::kState);
                        v0 = addiu(v0, 1);
                        sw(v0, s0, f4::dng::kState);
                    // state 2: the floor kind and the floor's field root (block-entry floors: the stratum title, 8) -> 3 (the state's entry)
                    L_001bf6e8:
                        charge(ctx, 45);
                        lw(v0, s0, f4::dng::kFloor);
                        v1 = sll(v0, 4);
                        lw(v0, s0, f4::dng::kFloorTable);
                        a0 = addu(v0, v1);
                        jal(ctx, 0x1BF6F8u, gen::fn_sub_1BF340_001bf340);
                        sw(v0, s0, f4::dng::kKind);
                        v0 = 0x870000;
                        sw(zero, v0, -6784);  // 0x86E580
                        lw(v1, s0, f4::dng::kFloorTable);
                        lw(v0, s0, f4::dng::kFloor);
                        v0 = sll(v0, 4);
                        v0 = addu(v0, v1);
                        lw(v1, v0, 8);
                        v0 = lui(0x8000);
                        v0 = v1 | v0;
                        sw(v0, s0, f4::dng::kFlags);
                        lw(v0, s0, f4::dng::kFloor);
                        v1 = sll(v0, 4);
                        lw(v0, s0, f4::dng::kFloorTable);
                        v1 = addu(v1, v0);
                        lbu(v0, v1, 7);
                        sd(v0, sp, 0x0);
                        lh(v0, v1, 4);
                        sd(v0, sp, 0x8);
                        v0 = si(-1);
                        sd(v0, sp, 0x10);
                        sd(v0, sp, 0x18);
                        sd(v0, sp, 0x20);
                        sd(v0, sp, 0x28);
                        lhu(a3, s0, f4::dng::kEntry);
                        a0 = s2;
                        lhu(a1, v1, 0);
                        lhu(a2, v1, 2);
                        t0 = 0;
                        t1 = 0;
                        lw(t2, s0, f4::dng::kFlags);
                        lbu(t3, v1, 6);
                        jal(ctx, 0x1BF780u, gen::fn_k_Field_CreateFieldRootTask_001ba5f0);
                        sw(v0, s0, f4::dng::kRoot);
                        sw(zero, s0, f4::dng::kFlags);
                        s1 = 0;
                        for (;;) {
                            // 0x001bf7d0
                            charge(ctx, 3);
                            v0 = sltiu(s1, 6);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x001bf79c
                            charge(ctx, 4);
                            jal(ctx, 0x1BF79Cu, gen::fn_sub_17D800_0017d800);
                            if (v0 == 0) {
                                // 0x001bf7ac
                                charge(ctx, 8);
                                lw(a0, s0, f4::dng::kFloor);
                                v1 = sll(s1, 2);
                                v0 = 0x680000;
                                v0 = addiu(v0, 13248);  // &0x6833C0
                                v0 = addu(v0, v1);
                                lw(v0, v0, 0);
                                if (a0 == v0) {
                                    break;
                                }
                                goto L_001bf7cc;
                            }
                        L_001bf7cc:
                            charge(ctx, 1);
                            s1 = addiu(s1, 1);
                        }
                        // 0x001bf7dc
                        charge(ctx, 3);
                        at = sltiu(s1, 6);
                        if (at == 0) {
                            // 0x001bf830
                            charge(ctx, 5);
                            lw(v0, s0, f4::dng::kState);
                            v0 = addiu(v0, 1);
                            sw(v0, s0, f4::dng::kState);
                        } else {
                            // 0x001bf7e8
                            charge(ctx, 18);
                            lw(a0, s0, f4::dng::kRoot);
                            a1 = 1;
                            jal(ctx, 0x1BF7F0u, gen::fn_sub_1BAA50_001baa50);
                            a0 = 5153;
                            a1 = 1;
                            jal(ctx, 0x1BF800u, gen::fn_datSetFlag_0016f1f0);
                            a0 = s2;
                            a1 = 0;
                            a2 = 0;
                            jal(ctx, 0x1BF814u, gen::fn_Y_Stratum_CreateStratumPartsTask_00447e70);
                            sw(v0, s0, f4::dng::kStratum);
                            v0 = 8;
                            sw(v0, s0, f4::dng::kState);
                        }
                    }
                }
            }
        L_001bfad0:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x1BF680u:  // table[1]  -- state 1: (shares its body with 2 through the original's gotos) the EPL instance
            goto L_001bf680;
        case 0x1BF6E8u:  // table[2]  -- state 2: the floor kind and the floor's field root (block-entry floors: the stratum title, 8) -> 3
            goto L_001bf6e8;
        case 0x1BF844u:  // table[3]  -- state 3: the floor runs; the shutdown word +12 -> 9
            // 0x001bf844
            charge(ctx, 4);
            lw(v1, s0, f4::dng::kShutdown);
            v0 = 1;
            if (v1 == v0) {
                // 0x001bf854
                charge(ctx, 4);
                v0 = 9;
                sw(v0, s0, f4::dng::kState);
            }
            goto L_001bfad0;
        case 0x1BF864u:  // table[4, 5, 6]  -- states 4..6: one frame each (a floor change) -> 7
            // 0x001bf864
            charge(ctx, 4);
            v0 = addiu(a0, 1);
            sw(v0, s0, f4::dng::kState);
            goto L_001bfad0;
        case 0x1BF874u:  // table[7]  -- state 7: the next floor's root (as 0..2) -> 3 / 8
            // 0x001bf874
            charge(ctx, 4);
            v1 = addiu(sp, 0xA0);
            v0 = 12;
            if (v1 != 0) {
                for (;;) {
                    // 0x001bf884
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
            // 0x001bf8a0
            charge(ctx, 3);
            lw(a0, gp, f4::gpv::kFloorObj0);  // 0x7CE280
            if (a0 != 0) {
                // 0x001bf8ac
                charge(ctx, 4);
                jal(ctx, 0x1BF8ACu, gen::fn_sub_316F70_00316f70);
                if (v0 != 0) {
                    goto L_001bf8bc;
                }
                goto L_001bfad0;
            }
        L_001bf8bc:
            charge(ctx, 5);
            lw(a0, s0, f4::dng::kScript);
            jal(ctx, 0x1BF8C0u, gen::fn_sub_1C0210_001c0210);
            if (v0 != 0) {
                // 0x001bf8d0
                charge(ctx, 5);
                sw(zero, s0, f4::dng::kScript);
                jal(ctx, 0x1BF8D4u, gen::fn_sub_1C0440_001c0440);
                if (v0 != 0) {
                    // 0x001bf8e4
                    charge(ctx, 4);
                    jal(ctx, 0x1BF8E4u, gen::fn_sub_1C0740_001c0740);
                    if (v0 != 0) {
                        // 0x001bf8f4
                        charge(ctx, 3);
                        lw(a0, s0, f4::dng::kEpl);
                        if (a0 != 0) {
                            // 0x001bf900
                            charge(ctx, 4);
                            jal(ctx, 0x1BF900u, gen::fn_sub_1A9180_001a9180);
                            if (v0 != 0) {
                                // 0x001bf910
                                charge(ctx, 5);
                                lw(a0, s0, f4::dng::kEpl);
                                a1 = addiu(sp, 0xA0);
                                jal(ctx, 0x1BF918u, gen::fn_sub_1A91B0_001a91b0);
                                sw(v0, s0, f4::dng::kEplObj);
                                goto L_001bf924;
                            }
                            goto L_001bfad0;
                        }
                    L_001bf924:
                        charge(ctx, 45);
                        lw(v0, s0, f4::dng::kFloor);
                        v1 = sll(v0, 4);
                        lw(v0, s0, f4::dng::kFloorTable);
                        a0 = addu(v0, v1);
                        jal(ctx, 0x1BF934u, gen::fn_sub_1BF340_001bf340);
                        sw(v0, s0, f4::dng::kKind);
                        v0 = 0x870000;
                        sw(zero, v0, -6784);  // 0x86E580
                        lw(v1, s0, f4::dng::kFloorTable);
                        lw(v0, s0, f4::dng::kFloor);
                        v0 = sll(v0, 4);
                        v0 = addu(v0, v1);
                        lw(v1, s0, f4::dng::kFlags);
                        lw(v0, v0, 8);
                        v0 = v1 | v0;
                        sw(v0, s0, f4::dng::kFlags);
                        lw(v0, s0, f4::dng::kFloor);
                        v1 = sll(v0, 4);
                        lw(v0, s0, f4::dng::kFloorTable);
                        v1 = addu(v1, v0);
                        lbu(v0, v1, 7);
                        sd(v0, sp, 0x0);
                        lh(v0, v1, 4);
                        sd(v0, sp, 0x8);
                        v0 = si(-1);
                        sd(v0, sp, 0x10);
                        sd(v0, sp, 0x18);
                        sd(v0, sp, 0x20);
                        sd(v0, sp, 0x28);
                        lhu(a3, s0, f4::dng::kEntry);
                        a0 = s2;
                        lhu(a1, v1, 0);
                        lhu(a2, v1, 2);
                        t0 = 0;
                        t1 = 0;
                        lw(t2, s0, f4::dng::kFlags);
                        lbu(t3, v1, 6);
                        jal(ctx, 0x1BF9BCu, gen::fn_k_Field_CreateFieldRootTask_001ba5f0);
                        sw(v0, s0, f4::dng::kRoot);
                        sw(zero, s0, f4::dng::kFlags);
                        s1 = 0;
                        for (;;) {
                            // 0x001bfa0c
                            charge(ctx, 3);
                            v0 = sltiu(s1, 6);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x001bf9d8
                            charge(ctx, 4);
                            jal(ctx, 0x1BF9D8u, gen::fn_sub_17D800_0017d800);
                            if (v0 == 0) {
                                // 0x001bf9e8
                                charge(ctx, 8);
                                lw(a0, s0, f4::dng::kFloor);
                                v1 = sll(s1, 2);
                                v0 = 0x680000;
                                v0 = addiu(v0, 13248);  // &0x6833C0
                                v0 = addu(v0, v1);
                                lw(v0, v0, 0);
                                if (a0 == v0) {
                                    break;
                                }
                                goto L_001bfa08;
                            }
                        L_001bfa08:
                            charge(ctx, 1);
                            s1 = addiu(s1, 1);
                        }
                        // 0x001bfa18
                        charge(ctx, 3);
                        at = sltiu(s1, 6);
                        if (at == 0) {
                            // 0x001bfa6c
                            charge(ctx, 4);
                            v0 = 3;
                            sw(v0, s0, f4::dng::kState);
                        } else {
                            // 0x001bfa24
                            charge(ctx, 18);
                            lw(a0, s0, f4::dng::kRoot);
                            a1 = 1;
                            jal(ctx, 0x1BFA2Cu, gen::fn_sub_1BAA50_001baa50);
                            a0 = 5153;
                            a1 = 1;
                            jal(ctx, 0x1BFA3Cu, gen::fn_datSetFlag_0016f1f0);
                            a0 = s2;
                            a1 = 0;
                            a2 = 0;
                            jal(ctx, 0x1BFA50u, gen::fn_Y_Stratum_CreateStratumPartsTask_00447e70);
                            sw(v0, s0, f4::dng::kStratum);
                            v0 = 8;
                            sw(v0, s0, f4::dng::kState);
                        }
                    }
                }
            }
            goto L_001bfad0;
        case 0x1BFA7Cu:  // table[8]  -- state 8: the stratum title done: flag 5153 off, the root released -> 3
            // 0x001bfa7c
            charge(ctx, 6);
            lw(a0, s0, f4::dng::kStratum);
            jal(ctx, 0x1BFA80u, gen::fn_kwlnTaskExists_00195460);
            v1 = 1;
            if (v0 != v1) {
                // 0x001bfa94
                charge(ctx, 12);
                a0 = 5153;
                a1 = 0;
                jal(ctx, 0x1BFA9Cu, gen::fn_datSetFlag_0016f1f0);
                lw(a0, s0, f4::dng::kRoot);
                a1 = 0;
                jal(ctx, 0x1BFAACu, gen::fn_sub_1BAA50_001baa50);
                v0 = 3;
                sw(v0, s0, f4::dng::kState);
            }
            goto L_001bfad0;
        case 0x1BFAC4u:  // table[9]  -- state 9: -> -1 (destroyed)
            // 0x001bfac4
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x001bfad4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x60);
        lq(s2, sp, 0x50);
        lq(s1, sp, 0x40);
        lq(s0, sp, 0x30);
        sp = addiu(sp, 0xC0);
        return;
    }
    goto L_001bfad0;
}

// 0x001BFAF0 sub_1BFAF0 [K_FldDungeon_DestroyTask] -- 200 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1BFAF0(task): the dungeon task's destroy: the battle-effect EPLs and the dungeon script freed (sub_1C07F0,
// sub_1C02E0), the dungeon slot 0x7CE268 and the scene's major cleared, the nine block resources (dword_86BDC0)
// destroyed, fobj000 released (0x7CE280, 0x86E694), the work freed.
void sub_1BFAF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001bfaf0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x1BFB08u, gen::fn_sub_1C07F0_001c07f0);
    jal(ctx, 0x1BFB10u, gen::fn_sub_1C02E0_001c02e0);
    sw(zero, gp, f4::gpv::kDungeonTask);  // 0x7CE268
    lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
    sw(zero, v0, f4::scene::kMajor);
    s0 = 0;
    for (;;) {
        // 0x001bfb5c
        charge(ctx, 3);
        v0 = slti(s0, 9);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001bfb30
        charge(ctx, 7);
        v1 = sll(s0, 2);
        v0 = 0x870000;
        v0 = addiu(v0, -16960);  // &0x86BDC0
        s2 = addu(v0, v1);
        lw(a0, s2, 0);
        if (a0 != 0) {
            // 0x001bfb4c
            charge(ctx, 3);
            jal(ctx, 0x1BFB4Cu, gen::fn_sub_1B3C90_001b3c90);
            sw(zero, s2, 0);
        }
        // 0x001bfb58
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x001bfb68
    charge(ctx, 3);
    lw(a0, gp, f4::gpv::kFloorObj0);  // 0x7CE280
    if (a0 != 0) {
        // 0x001bfb74
        charge(ctx, 5);
        jal(ctx, 0x1BFB74u, gen::fn_sub_3174E0_003174e0);
        sw(zero, gp, f4::gpv::kFloorObj0);  // 0x7CE280
        v0 = 0x870000;
        sw(zero, v0, -6508);  // 0x86E694
    }
    // 0x001bfb88
    charge(ctx, 12);
    lw(a0, s1, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1BFB94u, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001BFBC0 K_FldDungeon_CreateTask -- 248 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// K_FldDungeon_CreateTask(parent, floor, entry) -> the "automatic dungeon " task (64-byte work, priority 10) into
// 0x7CE268; +4 floor, +8 entry; from floor 2 on also fobj000 (0x7CE280), the dungeon script request (+20,
// sub_1C0190) and the battle-effect pack (sub_1C03F0).
void K_FldDungeon_CreateTask(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001bfbc0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 1;
    a1 = 64;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1BFBF8u, v0.u());
    s3 = v0;
    if (s3 != 0) {
        // 0x001bfc18
        charge(ctx, 18);
        a0 = s2;
        a1 = 10;
        a2 = 0x680000;
        a2 = addiu(a2, 13312);  // "automatic dungeon "
        a3 = 0x1C0000;
        a3 = addiu(a3, -2704);  // &K_FldDungeon_UpdateTask
        t0 = 0x1C0000;
        t0 = addiu(t0, -1296);  // &sub_1BFAF0
        t1 = s3;
        jal(ctx, 0x1BFC3Cu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s2 = v0;
        sw(v0, gp, f4::gpv::kDungeonTask);  // 0x7CE268
        sw(s1, s3, 4);
        sw(s0, s3, 8);
        at = sltiu(s1, 2);
        if (at == 0) {
            // 0x001bfc60
            charge(ctx, 13);
            a0 = 4;
            a1 = 0xFFFF;
            a2 = 0x680000;
            a2 = addiu(a2, 13344);  // "field/grmd/fobj000.RMD"
            a3 = 0;
            jal(ctx, 0x1BFC74u, gen::fn_sub_316B40_00316b40);
            sw(v0, gp, f4::gpv::kFloorObj0);  // 0x7CE280
            jal(ctx, 0x1BFC80u, gen::fn_sub_1C0190_001c0190);
            sw(v0, s3, 20);
            jal(ctx, 0x1BFC8Cu, gen::fn_sub_1C03F0_001c03f0);
        }
        // 0x001bfc94
        charge(ctx, 1);
        v0 = s2;
    } else {
        // 0x001bfc0c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001bfc98 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001BFCC0 sub_1BFCC0 [K_FldDungeon_GoToNextFloor] -- 568 bytes; frame 0x70: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1BFCC0() (the COMM handler sub_1C2580): moves the dungeon to floor + 1: its root's hold cleared, the encounter
// EPL stopped (sField +4608, sub_1A9470), sub_1D4180; the floor EPL kept when the next entry's +13 is the same, else
// replaced ("DNG%02d.EPL", or none for 255); fobj000 / the dungeon script / the battle-effect pack requested again;
// when the next entry's {major, minor} differ, flags bit 31 for the next root and (random / fixed floors) the nine
// block resources destroyed; floor + 1, the current root shut down (K_Field_SetShouldShutdown), state 4.
void sub_1BFCC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001bfcc0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, f4::gpv::kDungeonTask);  // 0x7CE268
    if (v1 != 0) {
        // 0x001bfce0
        charge(ctx, 17);
        lw(s0, v1, 60);
        sw(zero, s0, 8);
        jal(ctx, 0x1BFCE8u, gen::fn_K_Field_Get_001b9120);
        lw(a0, v0, f4::fld::kEplDamage);
        jal(ctx, 0x1BFCF4u, gen::fn_sub_1A9470_001a9470);
        jal(ctx, 0x1BFCFCu, gen::fn_sub_1D4180_001d4180);
        lw(v0, s0, 4);
        v1 = sll(v0, 4);
        lw(v0, s0, 32);
        v0 = addu(v1, v0);
        lbu(v1, v0, 13);
        lbu(v0, v0, 29);
        if (v1 == v0) {
            // 0x001bfda0
            charge(ctx, 3);
            lw(a0, s0, 44);
            if (a0 != 0) {
                // 0x001bfdac
                charge(ctx, 3);
                lw(a1, s0, 48);
                jal(ctx, 0x1BFDB0u, gen::fn_sub_1A9400_001a9400);
            }
        } else {
            // 0x001bfd24
            charge(ctx, 3);
            lw(a0, s0, 44);
            if (a0 != 0) {
                // 0x001bfd30
                charge(ctx, 2);
                jal(ctx, 0x1BFD30u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
            }
            // 0x001bfd38
            charge(ctx, 9);
            lw(v0, s0, 4);
            v1 = sll(v0, 4);
            lw(v0, s0, 32);
            v0 = addiu(v0, 29);
            v0 = addu(v0, v1);
            lbu(a2, v0, 0);
            at = slti(a2, 255);
            if (at == 0) {
                // 0x001bfd94
                charge(ctx, 3);
                sw(zero, s0, 44);
            } else {
                // 0x001bfd5c
                charge(ctx, 14);
                a0 = addiu(sp, 0x40);
                a1 = 0x680000;
                a1 = addiu(a1, 13280);  // "field/effect/DNG%02d.EPL"
                jal(ctx, 0x1BFD68u, gen::fn_sprintf_00523ac8);
                lw(a0, gp, f4::gpv::kDungeonTask);  // 0x7CE268
                a1 = addiu(sp, 0x40);
                a2 = si(-1);
                a3 = 0;
                jal(ctx, 0x1BFD80u, gen::fn_sub_1A9080_001a9080);
                sw(v0, s0, 44);
            }
        }
        // 0x001bfdb8
        charge(ctx, 5);
        lw(v0, s0, 4);
        v0 = addiu(v0, 1);
        at = sltiu(v0, 2);
        if (at == 0) {
            // 0x001bfdcc
            charge(ctx, 3);
            lw(v0, gp, f4::gpv::kFloorObj0);  // 0x7CE280
            if (v0 == 0) {
                // 0x001bfdd8
                charge(ctx, 8);
                a0 = 4;
                a1 = 0xFFFF;
                a2 = 0x680000;
                a2 = addiu(a2, 13344);  // "field/grmd/fobj000.RMD"
                a3 = 0;
                jal(ctx, 0x1BFDECu, gen::fn_sub_316B40_00316b40);
                sw(v0, gp, f4::gpv::kFloorObj0);  // 0x7CE280
            }
            // 0x001bfdf8
            charge(ctx, 5);
            jal(ctx, 0x1BFDF8u, gen::fn_sub_1C0190_001c0190);
            sw(v0, s0, 20);
            jal(ctx, 0x1BFE04u, gen::fn_sub_1C03F0_001c03f0);
        }
        // 0x001bfe0c
        charge(ctx, 8);
        lw(v0, s0, 4);
        v1 = sll(v0, 4);
        lw(v0, s0, 32);
        a0 = addu(v0, v1);
        lhu(v1, a0, 0);
        lhu(v0, a0, 16);
        if (v1 == v0) {
            // 0x001bfe2c
            charge(ctx, 4);
            lhu(v1, a0, 2);
            lhu(v0, a0, 18);
            if (v1 != v0) {
                goto L_001bfe3c;
            }
            goto L_001bfeb8;
        }
    L_001bfe3c:
        charge(ctx, 9);
        lw(v1, s0, 36);
        v0 = lui(0x8000);
        v0 = v1 | v0;
        sw(v0, s0, 36);
        jal(ctx, 0x1BFE4Cu, gen::fn_K_Scene_IsRandomFloor_001a0250);
        v1 = 1;
        if (v0 != v1) {
            // 0x001bfe60
            charge(ctx, 5);
            jal(ctx, 0x1BFE60u, gen::fn_sub_1A02C0_001a02c0);
            v1 = 1;
            if (v0 == v1) {
                goto L_001bfe74;
            }
            goto L_001bfeb8;
        }
    L_001bfe74:
        charge(ctx, 3);
        s2 = 0;
        for (;;) {
            // 0x001bfeac
            charge(ctx, 3);
            v0 = slti(s2, 9);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001bfe80
            charge(ctx, 7);
            v1 = sll(s2, 2);
            v0 = 0x870000;
            v0 = addiu(v0, -16960);  // &0x86BDC0
            s1 = addu(v0, v1);
            lw(a0, s1, 0);
            if (a0 != 0) {
                // 0x001bfe9c
                charge(ctx, 3);
                jal(ctx, 0x1BFE9Cu, gen::fn_sub_1B3C90_001b3c90);
                sw(zero, s1, 0);
            }
            // 0x001bfea8
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
    L_001bfeb8:
        charge(ctx, 9);
        lw(v0, s0, 4);
        v0 = addiu(v0, 1);
        sw(v0, s0, 4);
        lw(a0, s0, 24);
        a1 = 1;
        jal(ctx, 0x1BFECCu, gen::fn_K_Field_SetShouldShutdown_001ba880);
        v1 = 4;
        sw(v1, s0, 0);
    }
    // 0x001bfedc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

}  // namespace p3fes::game
