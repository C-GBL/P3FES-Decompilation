// Phase 5 slice facility2 (part 2 of 3): fclShopMisc.c 0x3F1910 .. 0x3FF570 -- the shop item entry, the lineup and sale
// rules, the buy / sell / equipment row drawers, the list window open / close animations, the quantity selector, the
// category lists, the weapon-fusion and trade list builders. p3fes_handgen bodies made readable (see part 1).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/facility2.h"

namespace p3fes::recomp_gen {
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_nmCmdListAddRow_003c5a40(p3fes::EEContext&);
void fn_nmCmdListClose_003c6f10(p3fes::EEContext&);
void fn_nmCmdListDestroy_003c5a20(p3fes::EEContext&);
void fn_nmCmdListMovedDownRow_003c6ce0(p3fes::EEContext&);
void fn_nmCmdListMovedUp_003c6cc0(p3fes::EEContext&);
void fn_nmCmdListPagedDown_003c6ca0(p3fes::EEContext&);
void fn_nmCmdListScrolledRow_003c6d10(p3fes::EEContext&);
void fn_nmCmdListSetDrawFunc_003c5e20(p3fes::EEContext&);
void fn_nmCmdListSetPosition_003c6d40(p3fes::EEContext&);
void fn_nmCmdListSetRowDrawFunc_003c5ee0(p3fes::EEContext&);
void fn_nmCmdListSetUpdateFunc_003c5e80(p3fes::EEContext&);
void fn_nmCmdListStatus28_003c6e10(p3fes::EEContext&);
void fn_nmCmdListStatus_003c6d80(p3fes::EEContext&);
void fn_nmCmdListUpdate_003c6270(p3fes::EEContext&);
void fn_nmListCursorClearEnd_003c4dc0(p3fes::EEContext&);
void fn_nmListCursorNext_003c4c80(p3fes::EEContext&);
void fn_nmListCursorPrev_003c4d20(p3fes::EEContext&);
void fn_nmListCursorSeek_003c4df0(p3fes::EEContext&);
void fn_nmListFindByWord4_003c4bf0(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_16DD50_0016dd50(p3fes::EEContext&);
void fn_sub_16F630_0016f630(p3fes::EEContext&);
void fn_sub_16F9F0_0016f9f0(p3fes::EEContext&);
void fn_sub_16FAE0_0016fae0(p3fes::EEContext&);
void fn_sub_16FBD0_0016fbd0(p3fes::EEContext&);
void fn_sub_16FCC0_0016fcc0(p3fes::EEContext&);
void fn_sub_170760_00170760(p3fes::EEContext&);
void fn_sub_170ED0_00170ed0(p3fes::EEContext&);
void fn_sub_171360_00171360(p3fes::EEContext&);
void fn_sub_1714F0_001714f0(p3fes::EEContext&);
void fn_sub_174A90_00174a90(p3fes::EEContext&);
void fn_sub_1752B0_001752b0(p3fes::EEContext&);
void fn_sub_175410_00175410(p3fes::EEContext&);
void fn_sub_17D060_0017d060(p3fes::EEContext&);
void fn_sub_17D250_0017d250(p3fes::EEContext&);
void fn_sub_17D610_0017d610(p3fes::EEContext&);
void fn_sub_17D6D0_0017d6d0(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_3C49E0_003c49e0(p3fes::EEContext&);
void fn_sub_3C58F0_003c58f0(p3fes::EEContext&);
void fn_sub_3C6EE0_003c6ee0(p3fes::EEContext&);
void fn_sub_3DFF00_003dff00(p3fes::EEContext&);
void fn_sub_3E04E0_003e04e0(p3fes::EEContext&);
void fn_sub_3E0650_003e0650(p3fes::EEContext&);
void fn_sub_3E6DC0_003e6dc0(p3fes::EEContext&);
void fn_sub_3F03E0_003f03e0(p3fes::EEContext&);
void fn_sub_3F1910_003f1910(p3fes::EEContext&);
void fn_sub_3F1A10_003f1a10(p3fes::EEContext&);
void fn_sub_3F1BA0_003f1ba0(p3fes::EEContext&);
void fn_sub_3F2240_003f2240(p3fes::EEContext&);
void fn_sub_3F2320_003f2320(p3fes::EEContext&);
void fn_sub_3F25E0_003f25e0(p3fes::EEContext&);
void fn_sub_3F2D60_003f2d60(p3fes::EEContext&);
void fn_sub_3F2DC0_003f2dc0(p3fes::EEContext&);
void fn_sub_3F3E60_003f3e60(p3fes::EEContext&);
void fn_sub_3F4A90_003f4a90(p3fes::EEContext&);
void fn_sub_3F5AB0_003f5ab0(p3fes::EEContext&);
void fn_sub_3F5D10_003f5d10(p3fes::EEContext&);
void fn_sub_3F5F50_003f5f50(p3fes::EEContext&);
void fn_sub_3F61D0_003f61d0(p3fes::EEContext&);
void fn_sub_3F67E0_003f67e0(p3fes::EEContext&);
void fn_sub_3F6F20_003f6f20(p3fes::EEContext&);
void fn_sub_3F7890_003f7890(p3fes::EEContext&);
void fn_sub_3F9510_003f9510(p3fes::EEContext&);
void fn_sub_3F99D0_003f99d0(p3fes::EEContext&);
void fn_sub_3FA210_003fa210(p3fes::EEContext&);
void fn_sub_3FA520_003fa520(p3fes::EEContext&);
void fn_sub_3FA800_003fa800(p3fes::EEContext&);
void fn_sub_3FAAE0_003faae0(p3fes::EEContext&);
void fn_sub_3FADC0_003fadc0(p3fes::EEContext&);
void fn_sub_3FB0C0_003fb0c0(p3fes::EEContext&);
void fn_sub_3FB2F0_003fb2f0(p3fes::EEContext&);
void fn_sub_3FB530_003fb530(p3fes::EEContext&);
void fn_sub_3FBF10_003fbf10(p3fes::EEContext&);
void fn_sub_3FCA00_003fca00(p3fes::EEContext&);
void fn_sub_3FCBE0_003fcbe0(p3fes::EEContext&);
void fn_sub_3FD140_003fd140(p3fes::EEContext&);
void fn_sub_3FD7E0_003fd7e0(p3fes::EEContext&);
void fn_sub_3FD8E0_003fd8e0(p3fes::EEContext&);
void fn_sub_3FD990_003fd990(p3fes::EEContext&);
void fn_sub_3FE1F0_003fe1f0(p3fes::EEContext&);
void fn_sub_3FE3E0_003fe3e0(p3fes::EEContext&);
void fn_sub_3FE5D0_003fe5d0(p3fes::EEContext&);
void fn_sub_3FE690_003fe690(p3fes::EEContext&);
void fn_sub_3FE7D0_003fe7d0(p3fes::EEContext&);
void fn_sub_3FE850_003fe850(p3fes::EEContext&);
void fn_sub_3FE950_003fe950(p3fes::EEContext&);
void fn_sub_3FEA10_003fea10(p3fes::EEContext&);
void fn_sub_3FEB30_003feb30(p3fes::EEContext&);
void fn_sub_3FEE40_003fee40(p3fes::EEContext&);
void fn_sub_3FEF30_003fef30(p3fes::EEContext&);
void fn_sub_3FF150_003ff150(p3fes::EEContext&);
void fn_sub_3FF460_003ff460(p3fes::EEContext&);
void fn_sub_3FF570_003ff570(p3fes::EEContext&);
void fn_sub_401A00_00401a00(p3fes::EEContext&);
void fn_sub_40E3C0_0040e3c0(p3fes::EEContext&);
void fn_sub_40EB50_0040eb50(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace fac2;  // the records of facility2.h

// 0x003F1910 sub_3F1910 -- 252 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopCountOwned] How many of item a0 the party holds: the item kind (sub_170ED0's out word) 4 -> the stack count
// sub_170760(1, item); kinds 0..3 (equipment) -> the inventory slots 0..299 holding it (sub_16F630(1, slot) == item);
// other kinds -> 0.
void sub_3F1910(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f1910
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    v0 = si(-1);
    sw(v0, sp, 0x4C);
    s0 = 0;
    a1 = addiu(sp, 0x4C);
    jal(ctx, 0x3F1938u, gen::fn_sub_170ED0_00170ed0);
    lw(v1, sp, 0x4C);
    v0 = 4;
    if (v1 == v0) {
        // 0x003f19d0: kind 4: the stack count
        charge(ctx, 7);
        a0 = 1;
        a1 = s1;
        jal(ctx, 0x3F19D8u, gen::fn_sub_170760_00170760);
        v0 = v0 & 0xFFFF;
    } else {
        // 0x003f1950
        charge(ctx, 3);
        v0 = 3;
        if (v1 != v0) {
            // 0x003f195c
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_003f1984;
            }
            // 0x003f1968
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_003f1984;
            }
            // 0x003f1974
            charge(ctx, 2);
            if (v1 == 0) {
                goto L_003f1984;
            }
            // 0x003f197c
            charge(ctx, 2);
            goto L_003f19ec;
        }
    L_003f1984:
        charge(ctx, 5);
        s2 = 0;
        s1 = dsll32(s1, 16);
        s1 = dsra32(s1, 16);
        for (;;) {
            // 0x003f19bc
            charge(ctx, 3);
            v0 = slti(s2, 300);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003f1998: equipment: count the slots holding it
            charge(ctx, 7);
            a0 = 1;
            a1 = s2;
            jal(ctx, 0x3F19A0u, gen::fn_sub_16F630_0016f630);
            v0 = v0 & 0xFFFF;
            if (s1 == v0) {
                // 0x003f19b4
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x003f19b8
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
        // 0x003f19c8
        charge(ctx, 2);
    L_003f19ec:
        charge(ctx, 1);
        v0 = s0;
    }
    // 0x003f19f0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003F1BA0 sub_3F1BA0 -- 544 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopMakeItemEntry] Builds the 28-byte shop item entry a0 (item::) for item a1: cleared, the id, count 0; a key item
// (sub_171360) gets the category of flag word 0x100000; otherwise per kind of sub_170ED0 (the item's record r): kind 4
// category(r +0), price r +12; kind 3 category(r +0), price r +16 and five stats r +4 / +8 / +6 / +10 / +12; kind 2
// (sub_1714F0 on r +12) category(r +4), price r +16, stat D = r +8; kind 1 category(r +4), price r +16, stat C = r +8;
// kind 0 category(r +4), price r +24, stats A / B = r +8 / r +12. Kinds 0..3 set kind 2; 0..2 also the 0x82 mark. A null
// a0 is K_Assert("fclShopMisc.c", 972) (it continues).
void sub_3F1BA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f1ba0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    v0 = si(-1);
    sw(v0, sp, 0x3C);
    if (s1 == 0) {
        // 0x003f1bc8: no entry: K_Assert (retail continues)
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 972;
        jal(ctx, 0x3F1BD4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003f1bdc
    charge(ctx, 12);
    a0 = s1;
    a1 = 0;
    a2 = 28;
    jal(ctx, 0x3F1BE8u, gen::fn_memset_00521408);
    sh(s0, s1, item::kId);
    sh(zero, s1, item::kCount);
    a0 = s0 & 0xFFFF;
    jal(ctx, 0x3F1BFCu, gen::fn_sub_171360_00171360);
    if (v0 == 0) {
        // 0x003f1c24
        charge(ctx, 9);
        a0 = s0;
        a1 = addiu(sp, 0x3C);
        jal(ctx, 0x3F1C2Cu, gen::fn_sub_170ED0_00170ed0);
        s0 = v0;
        lw(a0, sp, 0x3C);
        v1 = 4;
        if (a0 == v1) {
            // 0x003f1d88: kind 4
            charge(ctx, 8);
            lw(a0, s0, 0);
            jal(ctx, 0x3F1D8Cu, gen::fn_sub_3F1A10_003f1a10);
            sw(v0, s1, item::kCategory);
            lw(v1, s0, 12);
            sw(v1, s1, item::kPrice);
            v1 = 2;
            sb(v1, s1, item::kKind);
        } else {
            // 0x003f1c48
            charge(ctx, 3);
            v1 = 3;
            if (a0 == v1) {
                // 0x003f1d38: kind 3: five stats
                charge(ctx, 20);
                lw(a0, s0, 0);
                jal(ctx, 0x3F1D3Cu, gen::fn_sub_3F1A10_003f1a10);
                sw(v0, s1, item::kCategory);
                lw(v1, s0, 16);
                sw(v1, s1, item::kPrice);
                lhu(v1, s0, 4);
                sh(v1, s1, item::kStatA);
                lhu(v1, s0, 8);
                sh(v1, s1, item::kStatB);
                lhu(v1, s0, 6);
                sh(v1, s1, item::kStatC);
                lhu(v1, s0, 10);
                sh(v1, s1, item::kStatD);
                lhu(v1, s0, 12);
                sh(v1, s1, item::kStatE);
                v1 = 2;
                sb(v1, s1, item::kKind);
            } else {
                // 0x003f1c54
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    // 0x003f1cf4: kind 2
                    charge(ctx, 17);
                    lhu(a0, s0, 12);
                    jal(ctx, 0x3F1CF8u, gen::fn_sub_1714F0_001714f0);
                    lw(a0, s0, 4);
                    jal(ctx, 0x3F1D04u, gen::fn_sub_3F1A10_003f1a10);
                    sw(v0, s1, item::kCategory);
                    lw(v1, s0, 16);
                    sw(v1, s1, item::kPrice);
                    lhu(v1, s0, 8);
                    sh(v1, s1, item::kStatD);
                    v1 = 2;
                    sb(v1, s1, item::kKind);
                    v1 = 130;
                    sb(v1, s1, item::kEquip);
                } else {
                    // 0x003f1c60
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x003f1cbc: kind 1
                        charge(ctx, 14);
                        lw(a0, s0, 4);
                        jal(ctx, 0x3F1CC0u, gen::fn_sub_3F1A10_003f1a10);
                        sw(v0, s1, item::kCategory);
                        lw(v1, s0, 16);
                        sw(v1, s1, item::kPrice);
                        lhu(v1, s0, 8);
                        sh(v1, s1, item::kStatC);
                        v1 = 2;
                        sb(v1, s1, item::kKind);
                        v1 = 130;
                        sb(v1, s1, item::kEquip);
                    } else {
                        // 0x003f1c6c
                        charge(ctx, 2);
                        if (a0 == 0) {
                            // 0x003f1c7c: kind 0: attack / hit
                            charge(ctx, 16);
                            lw(a0, s0, 4);
                            jal(ctx, 0x3F1C80u, gen::fn_sub_3F1A10_003f1a10);
                            sw(v0, s1, item::kCategory);
                            lw(v1, s0, 24);
                            sw(v1, s1, item::kPrice);
                            lhu(v1, s0, 8);
                            sh(v1, s1, item::kStatA);
                            lhu(v1, s0, 12);
                            sh(v1, s1, item::kStatB);
                            v1 = 2;
                            sb(v1, s1, item::kKind);
                            v1 = 130;
                            sb(v1, s1, item::kEquip);
                        } else {
                            // 0x003f1c74
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
    } else {
        // 0x003f1c0c: a key item: category of 0x100000
        charge(ctx, 6);
        a0 = 0x100000;
        jal(ctx, 0x3F1C10u, gen::fn_sub_3F1A10_003f1a10);
        sw(v0, s1, item::kCategory);
    }
    // 0x003f1da8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003F2320 sub_3F2320 -- 492 bytes; frame 0x10: ra sp+0x0
// [fclShopApplySale] The sale-day prices of a buy list: a0 -> the list, a1 -> the lineup (lineup::). Marks the list
// (user flag 2); for every lineup entry on sale (flag 1) whose item has a row, the row gets flag 2 and the rate flag (entry
// flag 4 -> row 8, else entry flag 2 -> row 4). Then every row's price becomes (int)(price - k * price) with k = 0.5 (row
// flag 8), 0.3 (flag 4, 0x7CAD7C) or 0.25, and at least 1 when negative; the list is refreshed (sub_3F2D60). Returns 0.
void sub_3F2320(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    // 0x003f2320
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, lst::kState);
    lw(v1, v0, 68);
    lw(v0, v1, 0);
    v0 = v0 | 0x2;
    sw(v0, v1, 0);
    lw(v1, a1, lineup::kEntries);
    v0 = 0;
    for (;;) {
        // 0x003f2408
        charge(ctx, 4);
        lh(a2, a1, lineup::kCount);
        a2 = slt(v0, a2);
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f234c: an entry on sale: find its row
        charge(ctx, 3);
        lh(a3, v1, lent::kId);
        if (a3 != 0) {
            // 0x003f2358
            charge(ctx, 4);
            lb(a2, v1, lent::kFlags);
            a2 = a2 & 0x1;
            if (a2 != 0) {
                // 0x003f2368
                charge(ctx, 5);
                lw(t0, a0, lst::kHead);
                a3 = dsll32(a3, 16);
                a3 = dsra32(a3, 16);
                for (;;) {
                    // 0x003f239c
                    charge(ctx, 2);
                    if (t0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003f237c
                    charge(ctx, 5);
                    lw(a2, t0, node::kPayload);
                    lw(a2, a2, 28);
                    lh(a2, a2, 4);
                    if (a2 == a3) {
                        goto L_003f2390_5;
                    }
                    // 0x003f2398
                    charge(ctx, 1);
                    lw(t0, t0, node::kNext);
                }
                // 0x003f23a4
                charge(ctx, 1);
                t0 = 0;
            L_003f23a8:
                charge(ctx, 2);
                if (t0 != 0) {
                    // 0x003f23b0: its row: on sale + the rate flag
                    charge(ctx, 9);
                    lw(a2, t0, srow::kMat1);
                    lw(t0, a2, 28);
                    lw(a2, t0, srow::kFlags);
                    a2 = a2 | 0x2;
                    sw(a2, t0, srow::kFlags);
                    lb(a3, v1, lent::kFlags);
                    a2 = a3 & 0x4;
                    if (a2 == 0) {
                        // 0x003f23e8
                        charge(ctx, 3);
                        a2 = a3 & 0x2;
                        if (a2 != 0) {
                            // 0x003f23f4
                            charge(ctx, 3);
                            lw(a2, t0, srow::kFlags);
                            a2 = a2 | 0x4;
                            sw(a2, t0, srow::kFlags);
                        }
                    } else {
                        // 0x003f23d4
                        charge(ctx, 5);
                        lw(a2, t0, srow::kFlags);
                        a2 = a2 | 0x8;
                        sw(a2, t0, srow::kFlags);
                    }
                }
            }
        }
        // 0x003f2400
        charge(ctx, 2);
        v1 = addiu(v1, 8);
        v0 = addiu(v0, 1);
    }
    // 0x003f2418: every row: the sale rate
    charge(ctx, 10);
    lw(a3, a0, lst::kHead);
    v0 = 0x3E800000;
    mtc1(v0, f1);
    mtc1(zero, f3);
    lwc1(f2, gp, -32628);  // 0x7CAD7C
    v0 = 0x3F000000;
    mtc1(v0, f4);
    v0 = 1;
    for (;;) {
        // 0x003f24e8
        charge(ctx, 2);
        if (a3 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f2440
        charge(ctx, 6);
        lw(v1, a3, node::kPayload);
        lw(a2, v1, 28);
        lw(a1, a2, srow::kFlags);
        v1 = a1 & 0x8;
        if (v1 == 0) {
            // 0x003f2480
            charge(ctx, 3);
            v1 = a1 & 0x4;
            if (v1 == 0) {
                // 0x003f24b4: 25 % off
                charge(ctx, 8);
                lwc1(f0, a2, srow::kPrice);
                cvt_s_w(f0, f0);
                adda_s(f3, f0);
                msub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                sw(v1, a2, srow::kPrice);
            } else {
                // 0x003f248c: flag 4: 30 % off (0x7CAD7C)
                charge(ctx, 10);
                lwc1(f0, a2, srow::kPrice);
                cvt_s_w(f0, f0);
                adda_s(f3, f0);
                msub_s(f0, f2, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                sw(v1, a2, srow::kPrice);
            }
        } else {
            // 0x003f2458: flag 8: half price
            charge(ctx, 10);
            lwc1(f0, a2, srow::kPrice);
            cvt_s_w(f0, f0);
            adda_s(f3, f0);
            msub_s(f0, f4, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            sw(v1, a2, srow::kPrice);
        }
        // 0x003f24d4
        charge(ctx, 3);
        lw(v1, a2, srow::kPrice);
        if (i64(v1) < 0) {
            // 0x003f24e0: never negative: 1
            charge(ctx, 1);
            sw(v0, a2, srow::kPrice);
        }
        // 0x003f24e4
        charge(ctx, 1);
        lw(a3, a3, node::kNext);
    }
    // 0x003f24f0
    charge(ctx, 7);
    jal(ctx, 0x3F24F0u, gen::fn_sub_3F2D60_003f2d60);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    return;
L_003f2390_5:
    charge(ctx, 2);
    goto L_003f23a8;
}

// 0x003F25E0 sub_3F25E0 -- 860 bytes; frame 0x100: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopFillLineup] Adds the lineup a1's items to the buy list a0 (filters in a2): for each entry with an item --
// 0x400 only kind 0, 0x800 only kinds 1..3; an item of kind <= 0 needs its category's game flag (table 0x6ACC60, -1 =
// none; category 6 is free on the 'AGS_' variant, sub_17D800); condition 1 needs game flag 4880; 0x1000 returns 1 at the
// first item that passes (a test only); 0x2000 skips items already listed (nmListFindByWord4). A new row (key count + 1,
// its node word +4 = the item) is marked 1 with filter 1; unless filter 0x4000, a limited-stock entry (flag 8) whose stock
// (sub_17D060(the shop date key, item, slot)) is 0 is marked sold out (0x20); the item entry is built (sub_3F1BA0) and the
// price becomes price x (the entry's rate, else the lineup's) / 100; sub_3F2DC0 files the row. Returns 0 (1 for the
// 0x1000 test). The asserts ("fclShopMisc.c" 1118) continue in retail.
void sub_3F25E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x003f25e0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
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
    lw(s0, a1, 8);
    s5 = 0;
    fp = a2 & 0x400;
    v0 = a2 & 0x800;
    sq(v0, sp, 0xE0);
    v0 = a2 & 0x1000;
    sq(v0, sp, 0xD0);
    v0 = a2 & 0x2000;
    sq(v0, sp, 0xC0);
    v0 = a2 & 0x1;
    sq(v0, sp, 0xB0);
    v0 = a2 & 0x4000;
    sq(v0, sp, 0xA0);
    for (;;) {
        // 0x003f28f4
        charge(ctx, 4);
        lh(v0, s1, lineup::kCount);
        v0 = slt(s5, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f2650: an item: apply the filters
        charge(ctx, 3);
        lh(s4, s0, lent::kId);
        if (s4 != 0) {
            // 0x003f265c
            charge(ctx, 7);
            s3 = 1;
            a0 = s4;
            a1 = addiu(sp, 0xFC);
            jal(ctx, 0x3F2668u, gen::fn_sub_170ED0_00170ed0);
            if (fp != 0) {
                // 0x003f2678
                charge(ctx, 3);
                lw(v1, sp, 0xFC);
                if (v1 != 0) {
                    // 0x003f2684
                    charge(ctx, 1);
                    s3 = 0;
                }
            }
            // 0x003f2688
            charge(ctx, 3);
            lq(v1, sp, 0xE0);
            if (v1 != 0) {
                // 0x003f2694
                charge(ctx, 4);
                lw(a0, sp, 0xFC);
                v1 = 1;
                if (a0 != v1) {
                    // 0x003f26a4
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 != v1) {
                        // 0x003f26b0
                        charge(ctx, 3);
                        v1 = 3;
                        if (a0 != v1) {
                            // 0x003f26bc
                            charge(ctx, 1);
                            s3 = 0;
                        }
                    }
                }
            }
            // 0x003f26c0: kind <= 0: the category flag of 0x6ACC60
            charge(ctx, 3);
            lw(v1, sp, 0xFC);
            if (i64(v1) <= 0) {
                // 0x003f26cc
                charge(ctx, 7);
                lw(a0, v0, 4);
                jal(ctx, 0x3F26D0u, gen::fn_sub_3F1A10_003f1a10);
                s6 = v0 & 0xFF;
                v0 = 6;
                if (s6 == v0) {
                    // 0x003f26e8
                    charge(ctx, 4);
                    jal(ctx, 0x3F26E8u, gen::fn_sub_17D800_0017d800);
                    if (v0 == 0) {
                        goto L_003f26f8;
                    }
                    goto L_003f272c;
                }
            L_003f26f8:
                charge(ctx, 8);
                v1 = sll(s6, 1);
                v0 = 0x6B0000;
                v0 = addiu(v0, -13216);  // &0x6ACC60
                v0 = addu(v0, v1);
                lh(a0, v0, 0);
                v0 = si(-1);
                if (a0 != v0) {
                    // 0x003f2718
                    charge(ctx, 4);
                    jal(ctx, 0x3F2718u, gen::fn_datGetFlag_0016f190);
                    if (v0 == 0) {
                        // 0x003f2728
                        charge(ctx, 1);
                        s3 = 0;
                    }
                }
            }
        L_003f272c:
            charge(ctx, 4);
            lb(v1, s0, lent::kCond);
            v0 = 1;
            if (v1 == v0) {
                // 0x003f273c: condition 1: game flag 4880
                charge(ctx, 5);
                a0 = 4880;
                jal(ctx, 0x3F2740u, gen::fn_datGetFlag_0016f190);
                if (v0 == 0) {
                    // 0x003f2750
                    charge(ctx, 1);
                    s3 = 0;
                }
            }
            // 0x003f2754: passed
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x003f275c
                charge(ctx, 3);
                lq(v0, sp, 0xD0);
                if (v0 != 0) {
                    goto L_003f2768_21;
                }
                // 0x003f2774: filter 0x2000: skip listed items
                charge(ctx, 3);
                lq(v0, sp, 0xC0);
                if (v0 != 0) {
                    // 0x003f2780
                    charge(ctx, 8);
                    a2 = dsll32(s4, 16);
                    a2 = dsra32(a2, 16);
                    a0 = s2;
                    a1 = addiu(s2, 4);
                    jal(ctx, 0x3F2790u, gen::fn_nmListFindByWord4_003c4bf0);
                    if (v0 != 0) {
                        // 0x003f27a0
                        charge(ctx, 1);
                        s3 = 0;
                    }
                }
                goto L_003f27a4;
            }
        L_003f27a4:
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x003f27ac: add the row
                charge(ctx, 16);
                lhu(v0, s2, lst::kCount);
                a1 = addiu(v0, 1);
                a0 = s2;
                a2 = 32;
                a3 = 0;
                jal(ctx, 0x3F27C0u, gen::fn_nmCmdListAddRow_003c5a40);
                s6 = v0;
                v1 = dsll32(s4, 16);
                v1 = dsra32(v1, 16);
                sw(v1, v0, node::kWord4);
                lw(v0, v0, node::kPayload);
                lw(s3, v0, 28);
                lq(v0, sp, 0xB0);
                if (v0 != 0) {
                    // 0x003f27ec
                    charge(ctx, 3);
                    lw(v0, s3, srow::kFlags);
                    v0 = v0 | 0x1;
                    sw(v0, s3, srow::kFlags);
                }
                // 0x003f27f8
                charge(ctx, 3);
                lq(v0, sp, 0xA0);
                if (v0 == 0) {
                    // 0x003f2804: limited stock: sold out at 0
                    charge(ctx, 4);
                    lb(v0, s0, lent::kFlags);
                    v0 = v0 & 0x8;
                    if (v0 != 0) {
                        // 0x003f2814
                        charge(ctx, 13);
                        lhu(s7, gp, -18008);  // 0x7CE698
                        jal(ctx, 0x3F2818u, gen::fn_sub_3E6DC0_003e6dc0);
                        sh(v0, sp, 0xF8);
                        sh(s7, sp, 0xFA);
                        a1 = s4 & 0xFFFF;
                        lb(a2, s0, lent::kStock);
                        lw(a0, sp, 0xF8);
                        jal(ctx, 0x3F2834u, gen::fn_sub_17D060_0017d060);
                        lhu(v0, v0, 6);
                        if (v0 == 0) {
                            // 0x003f2848
                            charge(ctx, 3);
                            lw(v0, s3, srow::kFlags);
                            v0 = v0 | 0x20;
                            sw(v0, s3, srow::kFlags);
                        }
                    }
                }
                // 0x003f2854: the item entry and the price rate
                charge(ctx, 7);
                a0 = addiu(s3, 4);
                a1 = s4;
                jal(ctx, 0x3F285Cu, gen::fn_sub_3F1BA0_003f1ba0);
                v0 = addiu(s3, 4);
                if (v0 != 0) {
                    // 0x003f2870
                    charge(ctx, 2);
                    if (s1 == 0) {
                        goto L_003f2880;
                    }
                    // 0x003f2878
                    charge(ctx, 2);
                    if (s0 == 0) {
                        goto L_003f2880;
                    }
                    goto L_003f2894;
                }
            L_003f2880:
                charge(ctx, 5);
                a0 = 0x6B0000;
                a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                a1 = 1118;
                jal(ctx, 0x3F288Cu, gen::fn_sub_19D3F0_0019d3f0);
            L_003f2894:
                charge(ctx, 3);
                lh(v1, s0, lent::kRate);
                if (i64(v1) <= 0) {
                    // 0x003f28c0: the entry's rate
                    charge(ctx, 7);
                    lh(v1, s1, lineup::kRate);
                    lw(v0, s3, srow::kPrice);
                    mult(v1, v0, v1);
                    v0 = 100;
                    div(v1, v0);
                    mflo(v0);
                    sw(v0, s3, srow::kPrice);
                } else {
                    // 0x003f28a0: the lineup's rate
                    charge(ctx, 8);
                    lw(v0, s3, srow::kPrice);
                    mult(v1, v0, v1);
                    v0 = 100;
                    div(v1, v0);
                    mflo(v0);
                    sw(v0, s3, srow::kPrice);
                }
                // 0x003f28dc
                charge(ctx, 4);
                a0 = s2;
                a1 = s6;
                jal(ctx, 0x3F28E4u, gen::fn_sub_3F2DC0_003f2dc0);
            }
        }
        // 0x003f28ec
        charge(ctx, 2);
        s0 = addiu(s0, 8);
        s5 = addiu(s5, 1);
    }
    // 0x003f2904
    charge(ctx, 1);
    v0 = 0;
    // 0x003f2908 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x100);
    return;
L_003f2768_21:
    charge(ctx, 3);
    v0 = 1;
    // 0x003f2908 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x100);
}

// 0x003F3E60 sub_3F3E60 -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopRemoveListed] For every row of list a0, removes the row with the same item from list a1 (sub_3C49E0); returns 1
// as soon as one is missing from a1, else 0.
void sub_3F3E60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f3e60
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(s0, a0, lst::kHead);
    for (;;) {
        // 0x003f3ed0
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f3e80
        charge(ctx, 9);
        lw(v0, s0, node::kPayload);
        lw(v0, v0, 28);
        lh(a2, v0, 4);
        a0 = s1;
        a1 = addiu(s1, 4);
        jal(ctx, 0x3F3E94u, gen::fn_nmListFindByWord4_003c4bf0);
        if (v0 == 0) {
            goto L_003f3ec0;
        }
        // 0x003f3ea4
        charge(ctx, 7);
        a0 = s1;
        a1 = addiu(s1, 4);
        a2 = v0;
        jal(ctx, 0x3F3EB0u, gen::fn_sub_3C49E0_003c49e0);
        // 0x003f3ecc
        charge(ctx, 1);
        lw(s0, s0, node::kNext);
    }
    // 0x003f3ed8
    charge(ctx, 1);
    v0 = 0;
    // 0x003f3edc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_003f3ec0:
    charge(ctx, 3);
    v0 = 1;
    // 0x003f3edc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003F4A90 sub_3F4A90 -- 836 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopDrawListHeader] Draws a list's column header strip at (a0 + h +0, a1 + h +2), h = t1 (a 16-bit layout record), with
// alpha (int)(0.82 (0x7CAEF0) x a2 x h +12 / 255); the sprite set by a3: 0 / 1 -> 207 208 213 214 210 211 212, 2 -> 108
// 109 114 115 127 128, 3 -> 157 158, 4 and up -> 193 194 204 205.
void sub_3F4A90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x003f4a90
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lh(v0, t1, 0);
    s2 = addu(s2, v0);
    lh(v0, t1, 2);
    s1 = addu(s1, v0);
    mtc1(a2, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, gp, -32256);  // 0x7CAEF0
    mul_s(f1, f0, f1);
    lh(v0, t1, 12);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    mul_s(f1, f1, f0);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    div_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(s0, f0);
    v0 = 4;
    if (a3 != v0) {
        // 0x003f4b08
        charge(ctx, 3);
        v0 = 3;
        if (a3 == v0) {
            // 0x003f4cec
            charge(ctx, 18);
            mtc1(zero, f12);
            a2 = s0 & 0xFF;
            a0 = s2;
            a1 = s1;
            a3 = 157;
            t0 = 0;
            jal(ctx, 0x3F4D04u, gen::fn_sub_40E3C0_0040e3c0);
            mtc1(zero, f12);
            a2 = s0 & 0xFF;
            a0 = s2;
            a1 = s1;
            a3 = 158;
            t0 = 0;
            jal(ctx, 0x3F4D24u, gen::fn_sub_40E3C0_0040e3c0);
        } else {
            // 0x003f4b14
            charge(ctx, 3);
            v0 = 2;
            if (a3 == v0) {
                // 0x003f4c24
                charge(ctx, 50);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 108;
                t0 = 0;
                jal(ctx, 0x3F4C3Cu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 109;
                t0 = 0;
                jal(ctx, 0x3F4C5Cu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 114;
                t0 = 0;
                jal(ctx, 0x3F4C7Cu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 115;
                t0 = 0;
                jal(ctx, 0x3F4C9Cu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 127;
                t0 = 0;
                jal(ctx, 0x3F4CBCu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 128;
                t0 = 0;
                jal(ctx, 0x3F4CDCu, gen::fn_sub_40E3C0_0040e3c0);
            } else {
                // 0x003f4b20
                charge(ctx, 3);
                v0 = 1;
                if (a3 != v0) {
                    // 0x003f4b2c
                    charge(ctx, 2);
                    if (a3 == 0) {
                        goto L_003f4b3c;
                    }
                    // 0x003f4b34
                    charge(ctx, 2);
                    goto L_003f4d34;
                }
            L_003f4b3c:
                charge(ctx, 58);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 207;
                t0 = 0;
                jal(ctx, 0x3F4B54u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 208;
                t0 = 0;
                jal(ctx, 0x3F4B74u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 213;
                t0 = 0;
                jal(ctx, 0x3F4B94u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 214;
                t0 = 0;
                jal(ctx, 0x3F4BB4u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 210;
                t0 = 0;
                jal(ctx, 0x3F4BD4u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 211;
                t0 = 0;
                jal(ctx, 0x3F4BF4u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 212;
                t0 = 0;
                jal(ctx, 0x3F4C14u, gen::fn_sub_40E3C0_0040e3c0);
            }
        }
        // 0x003f4db4 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        v0 = 0;
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_003f4d34:
    charge(ctx, 32);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a0 = s2;
    a1 = s1;
    a3 = 193;
    t0 = 0;
    jal(ctx, 0x3F4D4Cu, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a0 = s2;
    a1 = s1;
    a3 = 194;
    t0 = 0;
    jal(ctx, 0x3F4D6Cu, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a0 = s2;
    a1 = s1;
    a3 = 204;
    t0 = 0;
    jal(ctx, 0x3F4D8Cu, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a0 = s2;
    a1 = s1;
    a3 = 205;
    t0 = 0;
    jal(ctx, 0x3F4DACu, gen::fn_sub_40E3C0_0040e3c0);
    // 0x003f4db4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003F5AB0 sub_3F5AB0 -- 600 bytes; frame 0x90: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopDrawUserColumnsA] Draws a row's party columns (layout A): sprites 54 55 56 (56 with the category byte) 57 58 59
// at (a0, a1), then for the four party members i: when the member mask of the item's category (byte table 0x7CD908,
// index (category & 0xF00) >> 8) has bit i, the number row user +20 + 2 i ("%d", sub_40EB50) at the column offset of table
// 0x6AEF30, else sprite 60 at the slot (124 (i & 1), 21 (i >> 1)). a4 -> the row node.
void sub_3F5AB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003f5ab0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    a1 = addiu(gp, -21472);  // &0x7CD910
    a0 = addiu(sp, 0x88);
    v1 = 5;
    for (;;) {
        // 0x003f5ae4
        charge(ctx, 7);
        lb(v0, a1, 0);
        a1 = addiu(a1, 1);
        v1 = addiu(v1, -1);
        sb(v0, a0, 0);
        a0 = addiu(a0, 1);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f5b00
    charge(ctx, 4);
    a2 = 0x6B0000;
    a2 = addiu(a2, -4304);  // &0x6AEF30
    a1 = addiu(sp, 0x60);
    a0 = 4;
    for (;;) {
        // 0x003f5b10
        charge(ctx, 9);
        lh(v1, a2, 0);
        lh(v0, a2, 2);
        a2 = addiu(a2, 4);
        a0 = addiu(a0, -1);
        sh(v1, a1, 0);
        sh(v0, a1, 2);
        a1 = addiu(a1, 4);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f5b34
    charge(ctx, 53);
    lw(v0, t0, node::kPayload);
    lw(s0, v0, 28);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 54;
    t0 = 0;
    jal(ctx, 0x3F5B54u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 55;
    t0 = 0;
    jal(ctx, 0x3F5B74u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    lbu(t0, s0, srow::kItemCategory);
    a0 = s4;
    a1 = s3;
    a3 = 56;
    jal(ctx, 0x3F5B94u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 57;
    t0 = 0;
    jal(ctx, 0x3F5BB4u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 58;
    t0 = 0;
    jal(ctx, 0x3F5BD4u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 59;
    t0 = 0;
    jal(ctx, 0x3F5BF4u, gen::fn_sub_40E3C0_0040e3c0);
    s1 = 0;
    for (;;) {
        // 0x003f5cd8
        charge(ctx, 3);
        v1 = slti(s1, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f5c08
        charge(ctx, 10);
        lw(v0, s0, srow::kItemCategory);
        v0 = v0 & 0xF00;
        v0 = sra(v0, 8);
        v0 = addu(v0, sp);
        lb(v1, v0, 136);
        v0 = 1;
        v0 = sllv(v0, s1);
        v0 = v1 & v0;
        if (v0 == 0) {
            // 0x003f5c8c: cannot: sprite 60
            charge(ctx, 18);
            v1 = s1 & 0x1;
            v0 = sll(v1, 5);
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            a0 = addu(s4, v0);
            v0 = sra(s1, 1);
            v1 = v0 & 0x1;
            v0 = sll(v1, 3);
            v1 = subu(v0, v1);
            v0 = sll(v1, 2);
            v0 = subu(v0, v1);
            a1 = addu(s3, v0);
            mtc1(zero, f12);
            a2 = s2 & 0xFF;
            a3 = 60;
            t0 = 0;
            jal(ctx, 0x3F5CCCu, gen::fn_sub_40E3C0_0040e3c0);
        } else {
            // 0x003f5c30: the member can use it: its number
            charge(ctx, 23);
            v0 = sll(s1, 1);
            v0 = addu(s0, v0);
            lh(a2, v0, 20);
            a0 = addiu(sp, 0x70);
            a1 = addiu(gp, -21488);  // "%d"
            jal(ctx, 0x3F5C44u, gen::fn_sprintf_00523ac8);
            v0 = sll(s1, 2);
            v0 = addu(v0, sp);
            v1 = addiu(v0, 96);
            lh(v0, v1, 0);
            a0 = addu(s4, v0);
            lh(v0, v1, 2);
            a1 = addu(s3, v0);
            mtc1(zero, f12);
            a2 = s2 & 0xFF;
            a3 = 1;
            t0 = addiu(sp, 0x70);
            t1 = 2;
            jal(ctx, 0x3F5C7Cu, gen::fn_sub_40EB50_0040eb50);
        }
        // 0x003f5cd4
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x003f5ce4
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x003F5D10 sub_3F5D10 -- 568 bytes; frame 0x90: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopDrawUserColumnsB] sub_3F5AB0 with the sprites 52..56 (53 with the category byte), the member table 0x7CD918, the
// column table 0x6AEF40 and sprite 57 for a member who cannot use the item.
void sub_3F5D10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003f5d10
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    a1 = addiu(gp, -21464);  // &0x7CD918
    a0 = addiu(sp, 0x88);
    v1 = 5;
    for (;;) {
        // 0x003f5d44
        charge(ctx, 7);
        lb(v0, a1, 0);
        a1 = addiu(a1, 1);
        v1 = addiu(v1, -1);
        sb(v0, a0, 0);
        a0 = addiu(a0, 1);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f5d60
    charge(ctx, 4);
    a2 = 0x6B0000;
    a2 = addiu(a2, -4288);  // &0x6AEF40
    a1 = addiu(sp, 0x60);
    a0 = 4;
    for (;;) {
        // 0x003f5d70
        charge(ctx, 9);
        lh(v1, a2, 0);
        lh(v0, a2, 2);
        a2 = addiu(a2, 4);
        a0 = addiu(a0, -1);
        sh(v1, a1, 0);
        sh(v0, a1, 2);
        a1 = addiu(a1, 4);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f5d94
    charge(ctx, 45);
    lw(v0, t0, node::kPayload);
    lw(s0, v0, 28);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 52;
    t0 = 0;
    jal(ctx, 0x3F5DB4u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    lbu(t0, s0, srow::kItemCategory);
    a0 = s4;
    a1 = s3;
    a3 = 53;
    jal(ctx, 0x3F5DD4u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 54;
    t0 = 0;
    jal(ctx, 0x3F5DF4u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 55;
    t0 = 0;
    jal(ctx, 0x3F5E14u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 56;
    t0 = 0;
    jal(ctx, 0x3F5E34u, gen::fn_sub_40E3C0_0040e3c0);
    s1 = 0;
    for (;;) {
        // 0x003f5f18
        charge(ctx, 3);
        v1 = slti(s1, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f5e48
        charge(ctx, 10);
        lw(v0, s0, srow::kItemCategory);
        v0 = v0 & 0xF00;
        v0 = sra(v0, 8);
        v0 = addu(v0, sp);
        lb(v1, v0, 136);
        v0 = 1;
        v0 = sllv(v0, s1);
        v0 = v1 & v0;
        if (v0 == 0) {
            // 0x003f5ecc: cannot: sprite 57
            charge(ctx, 18);
            v1 = s1 & 0x1;
            v0 = sll(v1, 5);
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            a0 = addu(s4, v0);
            v0 = sra(s1, 1);
            v1 = v0 & 0x1;
            v0 = sll(v1, 3);
            v1 = subu(v0, v1);
            v0 = sll(v1, 2);
            v0 = subu(v0, v1);
            a1 = addu(s3, v0);
            mtc1(zero, f12);
            a2 = s2 & 0xFF;
            a3 = 57;
            t0 = 0;
            jal(ctx, 0x3F5F0Cu, gen::fn_sub_40E3C0_0040e3c0);
        } else {
            // 0x003f5e70: the member can use it: its number
            charge(ctx, 23);
            v0 = sll(s1, 1);
            v0 = addu(s0, v0);
            lh(a2, v0, 20);
            a0 = addiu(sp, 0x70);
            a1 = addiu(gp, -21488);  // "%d"
            jal(ctx, 0x3F5E84u, gen::fn_sprintf_00523ac8);
            v0 = sll(s1, 2);
            v0 = addu(v0, sp);
            v1 = addiu(v0, 96);
            lh(v0, v1, 0);
            a0 = addu(s4, v0);
            lh(v0, v1, 2);
            a1 = addu(s3, v0);
            mtc1(zero, f12);
            a2 = s2 & 0xFF;
            a3 = 1;
            t0 = addiu(sp, 0x70);
            t1 = 2;
            jal(ctx, 0x3F5EBCu, gen::fn_sub_40EB50_0040eb50);
        }
        // 0x003f5f14
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x003f5f24
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x003F5F50 sub_3F5F50 -- 632 bytes; frame 0xD0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopDrawUserColumnsC] sub_3F5AB0's layout C (the buy list's equipment rows; run on the shop route): sprite 56 at y +1,
// sprite 57 with the word of table 0x6AEF60 chosen by the category byte, 58 59 60, the member table 0x7CD920, the column
// table 0x6AEF50, sprite 61 for a member who cannot use the item.
void sub_3F5F50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003f5f50
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    a1 = addiu(gp, -21456);  // &0x7CD920
    a0 = addiu(sp, 0xC8);
    v1 = 5;
    for (;;) {
        // 0x003f5f84
        charge(ctx, 7);
        lb(v0, a1, 0);
        a1 = addiu(a1, 1);
        v1 = addiu(v1, -1);
        sb(v0, a0, 0);
        a0 = addiu(a0, 1);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f5fa0
    charge(ctx, 4);
    a2 = 0x6B0000;
    a2 = addiu(a2, -4272);  // &0x6AEF50
    a1 = addiu(sp, 0xA0);
    a0 = 4;
    for (;;) {
        // 0x003f5fb0
        charge(ctx, 9);
        lh(v1, a2, 0);
        lh(v0, a2, 2);
        a2 = addiu(a2, 4);
        a0 = addiu(a0, -1);
        sh(v1, a1, 0);
        sh(v0, a1, 2);
        a1 = addiu(a1, 4);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f5fd4
    charge(ctx, 14);
    lw(v0, t0, node::kPayload);
    lw(s0, v0, 28);
    a1 = addiu(s3, 1);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a3 = 56;
    t0 = 0;
    jal(ctx, 0x3F5FF4u, gen::fn_sub_40E3C0_0040e3c0);
    a2 = 0x6B0000;
    a2 = addiu(a2, -4256);  // &0x6AEF60
    a1 = addiu(sp, 0x60);
    a0 = 7;
    for (;;) {
        // 0x003f600c
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
    // 0x003f6030
    charge(ctx, 38);
    a1 = addiu(s3, 1);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    lbu(v0, s0, srow::kItemCategory);
    v0 = sll(v0, 2);
    v0 = addu(v0, sp);
    lw(t0, v0, 96);
    a0 = s4;
    a3 = 57;
    jal(ctx, 0x3F6054u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 58;
    t0 = 0;
    jal(ctx, 0x3F6074u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 59;
    t0 = 0;
    jal(ctx, 0x3F6094u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 60;
    t0 = 0;
    jal(ctx, 0x3F60B4u, gen::fn_sub_40E3C0_0040e3c0);
    s1 = 0;
    for (;;) {
        // 0x003f6198
        charge(ctx, 3);
        v1 = slti(s1, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f60c8
        charge(ctx, 10);
        lw(v0, s0, srow::kItemCategory);
        v0 = v0 & 0xF00;
        v0 = sra(v0, 8);
        v0 = addu(v0, sp);
        lb(v1, v0, 200);
        v0 = 1;
        v0 = sllv(v0, s1);
        v0 = v1 & v0;
        if (v0 == 0) {
            // 0x003f614c: cannot: sprite 61
            charge(ctx, 18);
            v1 = s1 & 0x1;
            v0 = sll(v1, 5);
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            a0 = addu(s4, v0);
            v0 = sra(s1, 1);
            v1 = v0 & 0x1;
            v0 = sll(v1, 3);
            v1 = subu(v0, v1);
            v0 = sll(v1, 2);
            v0 = subu(v0, v1);
            a1 = addu(s3, v0);
            mtc1(zero, f12);
            a2 = s2 & 0xFF;
            a3 = 61;
            t0 = 0;
            jal(ctx, 0x3F618Cu, gen::fn_sub_40E3C0_0040e3c0);
        } else {
            // 0x003f60f0: the member can use it: its number
            charge(ctx, 23);
            v0 = sll(s1, 1);
            v0 = addu(s0, v0);
            lh(a2, v0, 20);
            a0 = addiu(sp, 0xB0);
            a1 = addiu(gp, -21488);  // "%d"
            jal(ctx, 0x3F6104u, gen::fn_sprintf_00523ac8);
            v0 = sll(s1, 2);
            v0 = addu(v0, sp);
            v1 = addiu(v0, 160);
            lh(v0, v1, 0);
            a0 = addu(s4, v0);
            lh(v0, v1, 2);
            a1 = addu(s3, v0);
            mtc1(zero, f12);
            a2 = s2 & 0xFF;
            a3 = 1;
            t0 = addiu(sp, 0xB0);
            t1 = 2;
            jal(ctx, 0x3F613Cu, gen::fn_sub_40EB50_0040eb50);
        }
        // 0x003f6194
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x003f61a4
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x003F61D0 sub_3F61D0 -- 1552 bytes; frame 0xC0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopDrawCompareA] Draws the equipment comparison of a row (layout A): the member m = (category & 0xF00) >> 8, sprites
// 54 55 56; whether m can use it (byte table 0x7CD928) picks 63 / 64 (dimmed to half alpha where the stat pair table
// 0x6AEF98 has -1) or 61 / 62; then two stat lines (y +27, y +54): with no stat (-1) four dashes (sprite 66), else the
// member's current equipment value (datGetEquipmentIdx(1, m), sub_16FBD0 / sub_16F9F0 for line 1, sub_16FCC0 / sub_16FAE0
// for line 2) and the row's value (+20 + 2 stat) as "%d" at the offsets 0x7CD930 / 0x7CD932 / 0x7CD934 / 0x7CD936, sprite
// 65 between.
void sub_3F61D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x003f61d0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    a1 = addiu(gp, -21448);  // &0x7CD928
    a0 = addiu(sp, 0xB8);
    v1 = 5;
    for (;;) {
        // 0x003f6210
        charge(ctx, 7);
        lb(v0, a1, 0);
        a1 = addiu(a1, 1);
        v1 = addiu(v1, -1);
        sb(v0, a0, 0);
        a0 = addiu(a0, 1);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f622c
    charge(ctx, 12);
    lh(a1, gp, -21440);  // 0x7CD930
    lh(a0, gp, -21438);  // 0x7CD932
    lh(v1, gp, -21436);  // 0x7CD934
    lh(v0, gp, -21434);  // 0x7CD936
    sh(a1, sp, 0xB0);
    sh(a0, sp, 0xB2);
    sh(v1, sp, 0xB4);
    sh(v0, sp, 0xB6);
    a2 = 0x6B0000;
    a2 = addiu(a2, -4200);  // &0x6AEF98
    a1 = addiu(sp, 0xA0);
    a0 = 5;
    for (;;) {
        // 0x003f625c
        charge(ctx, 9);
        lb(v1, a2, 0);
        lb(v0, a2, 1);
        a2 = addiu(a2, 2);
        a0 = addiu(a0, -1);
        sb(v1, a1, 0);
        sb(v0, a1, 1);
        a1 = addiu(a1, 2);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f6280
    charge(ctx, 34);
    lw(v0, t0, node::kPayload);
    lw(s1, v0, 28);
    lw(v0, s1, srow::kItemCategory);
    v0 = v0 & 0xF00;
    s0 = sra(v0, 8);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 54;
    t0 = 0;
    jal(ctx, 0x3F62ACu, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 55;
    t0 = 0;
    jal(ctx, 0x3F62CCu, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    lbu(t0, s1, srow::kItemCategory);
    a0 = s4;
    a1 = s3;
    a3 = 56;
    jal(ctx, 0x3F62ECu, gen::fn_sub_40E3C0_0040e3c0);
    v0 = addu(s0, sp);
    v0 = addiu(v0, 184);
    lb(s5, v0, 0);
    if (s5 != 0) {
        // 0x003f6350
        charge(ctx, 7);
        a0 = s2;
        s6 = sll(s0, 1);
        v0 = addu(s6, sp);
        lb(v1, v0, 160);
        v0 = si(-1);
        if (v1 == v0) {
            // 0x003f636c
            charge(ctx, 8);
            v0 = 0x3F000000;
            mtc1(v0, f1);
            mtc1(s2, f0);
            cvt_s_w(f0, f0);
            mul_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(a0, f0);
        }
        // 0x003f638c
        charge(ctx, 14);
        mtc1(zero, f12);
        a2 = a0 & 0xFF;
        a0 = s4;
        a1 = s3;
        a3 = 63;
        t0 = 0;
        jal(ctx, 0x3F63A4u, gen::fn_sub_40E3C0_0040e3c0);
        a0 = s2;
        v0 = addu(s6, sp);
        lb(v1, v0, 161);
        v0 = si(-1);
        if (v1 == v0) {
            // 0x003f63c4
            charge(ctx, 8);
            v0 = 0x3F000000;
            mtc1(v0, f1);
            mtc1(s2, f0);
            cvt_s_w(f0, f0);
            mul_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(a0, f0);
        }
        // 0x003f63e4
        charge(ctx, 8);
        mtc1(zero, f12);
        a2 = a0 & 0xFF;
        a0 = s4;
        a1 = s3;
        a3 = 64;
        t0 = 0;
        jal(ctx, 0x3F63FCu, gen::fn_sub_40E3C0_0040e3c0);
    } else {
        // 0x003f6308
        charge(ctx, 18);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s4;
        a1 = s3;
        a3 = 61;
        t0 = 0;
        jal(ctx, 0x3F6320u, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s4;
        a1 = s3;
        a3 = 62;
        t0 = 0;
        jal(ctx, 0x3F6340u, gen::fn_sub_40E3C0_0040e3c0);
    }
    // 0x003f6404
    charge(ctx, 15);
    a1 = addiu(s3, 27);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a3 = 55;
    t0 = 0;
    jal(ctx, 0x3F641Cu, gen::fn_sub_40E3C0_0040e3c0);
    s6 = sll(s0, 1);
    v0 = addu(s6, sp);
    v0 = addiu(v0, 160);
    lb(s7, v0, 0);
    v0 = si(-1);
    if (s7 == v0) {
        // 0x003f655c
        charge(ctx, 32);
        a1 = addiu(s3, 27);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s4;
        a3 = 66;
        t0 = 0;
        jal(ctx, 0x3F6574u, gen::fn_sub_40E3C0_0040e3c0);
        a0 = addiu(s4, 17);
        a1 = addiu(s3, 27);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a3 = 66;
        t0 = 0;
        jal(ctx, 0x3F6594u, gen::fn_sub_40E3C0_0040e3c0);
        a0 = addiu(s4, 34);
        a1 = addiu(s3, 27);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a3 = 66;
        t0 = 0;
        jal(ctx, 0x3F65B4u, gen::fn_sub_40E3C0_0040e3c0);
        a0 = addiu(s4, 51);
        a1 = addiu(s3, 27);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a3 = 66;
        t0 = 0;
        jal(ctx, 0x3F65D4u, gen::fn_sub_40E3C0_0040e3c0);
    } else {
        // 0x003f6440
        charge(ctx, 2);
        if (s5 != 0) {
            // 0x003f647c
            charge(ctx, 11);
            a1 = dsll32(s0, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x3F6488u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x3F649Cu, gen::fn_sub_16FBD0_0016fbd0);
            a2 = v0 & 0xFFFF;
        } else {
            // 0x003f6448
            charge(ctx, 13);
            a1 = dsll32(s0, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x3F6454u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x3F6468u, gen::fn_sub_16F9F0_0016f9f0);
            a2 = v0 & 0xFFFF;
        }
        // 0x003f64a8
        charge(ctx, 45);
        a0 = addiu(sp, 0x90);
        a1 = addiu(gp, -21488);  // "%d"
        jal(ctx, 0x3F64B0u, gen::fn_sprintf_00523ac8);
        lh(v0, sp, 0xB0);
        a0 = addu(s4, v0);
        v1 = addiu(s3, 27);
        lh(v0, sp, 0xB2);
        a1 = addu(v1, v0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a3 = 1;
        t0 = addiu(sp, 0x90);
        t1 = 2;
        jal(ctx, 0x3F64E0u, gen::fn_sub_40EB50_0040eb50);
        a1 = addiu(s3, 27);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s4;
        a3 = 65;
        t0 = 0;
        jal(ctx, 0x3F6500u, gen::fn_sub_40E3C0_0040e3c0);
        v0 = sll(s7, 1);
        v0 = addu(v0, s1);
        lh(a2, v0, 20);
        a0 = addiu(sp, 0x90);
        a1 = addiu(gp, -21488);  // "%d"
        jal(ctx, 0x3F651Cu, gen::fn_sprintf_00523ac8);
        lh(v0, sp, 0xB4);
        a0 = addu(s4, v0);
        v1 = addiu(s3, 27);
        lh(v0, sp, 0xB6);
        a1 = addu(v1, v0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a3 = 1;
        t0 = addiu(sp, 0x90);
        t1 = 2;
        jal(ctx, 0x3F654Cu, gen::fn_sub_40EB50_0040eb50);
    }
    // 0x003f65dc
    charge(ctx, 14);
    a1 = addiu(s3, 54);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a3 = 55;
    t0 = 0;
    jal(ctx, 0x3F65F4u, gen::fn_sub_40E3C0_0040e3c0);
    v0 = addu(s6, sp);
    v0 = addiu(v0, 161);
    lb(s6, v0, 0);
    v0 = si(-1);
    if (s6 == v0) {
        // 0x003f6730
        charge(ctx, 32);
        a1 = addiu(s3, 54);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s4;
        a3 = 66;
        t0 = 0;
        jal(ctx, 0x3F6748u, gen::fn_sub_40E3C0_0040e3c0);
        a0 = addiu(s4, 17);
        a1 = addiu(s3, 54);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a3 = 66;
        t0 = 0;
        jal(ctx, 0x3F6768u, gen::fn_sub_40E3C0_0040e3c0);
        a0 = addiu(s4, 34);
        a1 = addiu(s3, 54);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a3 = 66;
        t0 = 0;
        jal(ctx, 0x3F6788u, gen::fn_sub_40E3C0_0040e3c0);
        a0 = addiu(s4, 51);
        a1 = addiu(s3, 54);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a3 = 66;
        t0 = 0;
        jal(ctx, 0x3F67A8u, gen::fn_sub_40E3C0_0040e3c0);
    } else {
        // 0x003f6614
        charge(ctx, 2);
        if (s5 != 0) {
            // 0x003f6650
            charge(ctx, 11);
            a1 = dsll32(s0, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x3F665Cu, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x3F6670u, gen::fn_sub_16FCC0_0016fcc0);
            a2 = v0 & 0xFFFF;
        } else {
            // 0x003f661c
            charge(ctx, 13);
            a1 = dsll32(s0, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x3F6628u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x3F663Cu, gen::fn_sub_16FAE0_0016fae0);
            a2 = v0 & 0xFFFF;
        }
        // 0x003f667c
        charge(ctx, 45);
        a0 = addiu(sp, 0x90);
        a1 = addiu(gp, -21488);  // "%d"
        jal(ctx, 0x3F6684u, gen::fn_sprintf_00523ac8);
        lh(v0, sp, 0xB0);
        a0 = addu(s4, v0);
        v1 = addiu(s3, 54);
        lh(v0, sp, 0xB2);
        a1 = addu(v1, v0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a3 = 1;
        t0 = addiu(sp, 0x90);
        t1 = 2;
        jal(ctx, 0x3F66B4u, gen::fn_sub_40EB50_0040eb50);
        a1 = addiu(s3, 54);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s4;
        a3 = 65;
        t0 = 0;
        jal(ctx, 0x3F66D4u, gen::fn_sub_40E3C0_0040e3c0);
        v0 = sll(s6, 1);
        v0 = addu(v0, s1);
        lh(a2, v0, 20);
        a0 = addiu(sp, 0x90);
        a1 = addiu(gp, -21488);  // "%d"
        jal(ctx, 0x3F66F0u, gen::fn_sprintf_00523ac8);
        lh(v0, sp, 0xB4);
        a0 = addu(s4, v0);
        v1 = addiu(s3, 54);
        lh(v0, sp, 0xB6);
        a1 = addu(v1, v0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a3 = 1;
        t0 = addiu(sp, 0x90);
        t1 = 2;
        jal(ctx, 0x3F6720u, gen::fn_sub_40EB50_0040eb50);
    }
    // 0x003f67b0 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// 0x003F67E0 sub_3F67E0 -- 1852 bytes; frame 0xC0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopDrawCompareB] sub_3F61D0's layout B (the sell / equip lists): a3 = 1 adds sprites 199 200, 0 sprite 177; sprites
// 201 181 and the category digit (sprite 5 at +112 / +8); 202 / 203 or 179 / 180 by the member table 0x7CD930 +8; the two
// stat lines at y +28 / +56 with dashes 206 at half alpha or the values and sprite 182 (tables 0x7CD940.., 0x6AEFA8).
void sub_3F67E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x003f67e0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    a1 = addiu(gp, -21432);  // &0x7CD938
    a0 = addiu(sp, 0xB8);
    v1 = 5;
    for (;;) {
        // 0x003f6820
        charge(ctx, 7);
        lb(v0, a1, 0);
        a1 = addiu(a1, 1);
        v1 = addiu(v1, -1);
        sb(v0, a0, 0);
        a0 = addiu(a0, 1);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f683c
    charge(ctx, 12);
    lh(a1, gp, -21424);  // 0x7CD940
    lh(a0, gp, -21422);  // 0x7CD942
    lh(v1, gp, -21420);  // 0x7CD944
    lh(v0, gp, -21418);  // 0x7CD946
    sh(a1, sp, 0xB0);
    sh(a0, sp, 0xB2);
    sh(v1, sp, 0xB4);
    sh(v0, sp, 0xB6);
    a2 = 0x6B0000;
    a2 = addiu(a2, -4184);  // &0x6AEFA8
    a1 = addiu(sp, 0xA0);
    a0 = 5;
    for (;;) {
        // 0x003f686c
        charge(ctx, 9);
        lb(v1, a2, 0);
        lb(v0, a2, 1);
        a2 = addiu(a2, 2);
        a0 = addiu(a0, -1);
        sb(v1, a1, 0);
        sb(v0, a1, 1);
        a1 = addiu(a1, 2);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f6890
    charge(ctx, 8);
    lw(v0, t1, node::kPayload);
    lw(s6, v0, 28);
    lw(v0, s6, srow::kItemCategory);
    v0 = v0 & 0xF00;
    s0 = sra(v0, 8);
    v0 = 1;
    if (a3 == v0) {
        // 0x003f68e8
        charge(ctx, 16);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s4;
        a1 = s3;
        a3 = 199;
        t0 = 0;
        jal(ctx, 0x3F6900u, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s4;
        a1 = s3;
        a3 = 200;
        t0 = 0;
        jal(ctx, 0x3F6920u, gen::fn_sub_40E3C0_0040e3c0);
    } else {
        // 0x003f68b0
        charge(ctx, 2);
        if (a3 == 0) {
            // 0x003f68c0
            charge(ctx, 10);
            mtc1(zero, f12);
            a2 = s2 & 0xFF;
            a0 = s4;
            a1 = s3;
            a3 = 177;
            t0 = 0;
            jal(ctx, 0x3F68D8u, gen::fn_sub_40E3C0_0040e3c0);
        } else {
            // 0x003f68b8
            charge(ctx, 2);
        }
    }
    // 0x003f6928
    charge(ctx, 29);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 201;
    t0 = 0;
    jal(ctx, 0x3F6940u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 181;
    t0 = 0;
    jal(ctx, 0x3F6960u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s4, 112);
    a1 = addiu(s3, 8);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    lbu(t0, s6, srow::kItemCategory);
    a3 = 5;
    jal(ctx, 0x3F6980u, gen::fn_sub_40E3C0_0040e3c0);
    v0 = addu(s0, sp);
    v0 = addiu(v0, 184);
    lb(s7, v0, 0);
    if (s7 != 0) {
        // 0x003f6a60
        charge(ctx, 8);
        v1 = s2;
        s5 = sll(s0, 1);
        v0 = addu(s5, sp);
        v0 = addiu(v0, 160);
        lb(s1, v0, 0);
        v0 = si(-1);
        if (s1 == v0) {
            // 0x003f6a80
            charge(ctx, 8);
            v0 = 0x3F000000;
            mtc1(v0, f1);
            mtc1(s2, f0);
            cvt_s_w(f0, f0);
            mul_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
        }
        // 0x003f6aa0
        charge(ctx, 15);
        mtc1(zero, f12);
        a2 = v1 & 0xFF;
        a0 = s4;
        a1 = s3;
        a3 = 202;
        t0 = 0;
        jal(ctx, 0x3F6AB8u, gen::fn_sub_40E3C0_0040e3c0);
        v1 = s2;
        v0 = addu(s5, sp);
        v0 = addiu(v0, 161);
        lb(s5, v0, 0);
        v0 = si(-1);
        if (s5 == v0) {
            // 0x003f6adc
            charge(ctx, 8);
            v0 = 0x3F000000;
            mtc1(v0, f1);
            mtc1(s2, f0);
            cvt_s_w(f0, f0);
            mul_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
        }
        // 0x003f6afc
        charge(ctx, 8);
        mtc1(zero, f12);
        a2 = v1 & 0xFF;
        a0 = s4;
        a1 = s3;
        a3 = 203;
        t0 = 0;
        jal(ctx, 0x3F6B14u, gen::fn_sub_40E3C0_0040e3c0);
    } else {
        // 0x003f699c
        charge(ctx, 8);
        v1 = s2;
        s5 = sll(s0, 1);
        v0 = addu(s5, sp);
        v0 = addiu(v0, 160);
        lb(s1, v0, 0);
        v0 = si(-1);
        if (s1 == v0) {
            // 0x003f69bc
            charge(ctx, 8);
            v0 = 0x3F000000;
            mtc1(v0, f1);
            mtc1(s2, f0);
            cvt_s_w(f0, f0);
            mul_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
        }
        // 0x003f69dc
        charge(ctx, 15);
        mtc1(zero, f12);
        a2 = v1 & 0xFF;
        a0 = s4;
        a1 = s3;
        a3 = 179;
        t0 = 0;
        jal(ctx, 0x3F69F4u, gen::fn_sub_40E3C0_0040e3c0);
        v1 = s2;
        v0 = addu(s5, sp);
        v0 = addiu(v0, 161);
        lb(s5, v0, 0);
        v0 = si(-1);
        if (s5 == v0) {
            // 0x003f6a18
            charge(ctx, 8);
            v0 = 0x3F000000;
            mtc1(v0, f1);
            mtc1(s2, f0);
            cvt_s_w(f0, f0);
            mul_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
        }
        // 0x003f6a38
        charge(ctx, 10);
        mtc1(zero, f12);
        a2 = v1 & 0xFF;
        a0 = s4;
        a1 = s3;
        a3 = 180;
        t0 = 0;
        jal(ctx, 0x3F6A50u, gen::fn_sub_40E3C0_0040e3c0);
    }
    // 0x003f6b1c
    charge(ctx, 11);
    a1 = addiu(s3, 28);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a3 = 181;
    t0 = 0;
    jal(ctx, 0x3F6B34u, gen::fn_sub_40E3C0_0040e3c0);
    v0 = si(-1);
    if (s1 == v0) {
        // 0x003f6c64
        charge(ctx, 40);
        v0 = 0x3F000000;
        mtc1(v0, f1);
        mtc1(s2, f0);
        cvt_s_w(f0, f0);
        mul_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(s1, f0);
        a1 = addiu(s3, 28);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a0 = s4;
        a3 = 206;
        t0 = 0;
        jal(ctx, 0x3F6C9Cu, gen::fn_sub_40E3C0_0040e3c0);
        a0 = addiu(s4, 17);
        a1 = addiu(s3, 28);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a3 = 206;
        t0 = 0;
        jal(ctx, 0x3F6CBCu, gen::fn_sub_40E3C0_0040e3c0);
        a0 = addiu(s4, 34);
        a1 = addiu(s3, 28);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a3 = 206;
        t0 = 0;
        jal(ctx, 0x3F6CDCu, gen::fn_sub_40E3C0_0040e3c0);
        a0 = addiu(s4, 51);
        a1 = addiu(s3, 28);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a3 = 206;
        t0 = 0;
        jal(ctx, 0x3F6CFCu, gen::fn_sub_40E3C0_0040e3c0);
    } else {
        // 0x003f6b48
        charge(ctx, 2);
        if (s7 != 0) {
            // 0x003f6b84
            charge(ctx, 11);
            a1 = dsll32(s0, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x3F6B90u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x3F6BA4u, gen::fn_sub_16FBD0_0016fbd0);
            a2 = v0 & 0xFFFF;
        } else {
            // 0x003f6b50
            charge(ctx, 13);
            a1 = dsll32(s0, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x3F6B5Cu, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x3F6B70u, gen::fn_sub_16F9F0_0016f9f0);
            a2 = v0 & 0xFFFF;
        }
        // 0x003f6bb0
        charge(ctx, 45);
        a0 = addiu(sp, 0x90);
        a1 = addiu(gp, -21488);  // "%d"
        jal(ctx, 0x3F6BB8u, gen::fn_sprintf_00523ac8);
        lh(v0, sp, 0xB0);
        a0 = addu(s4, v0);
        v1 = addiu(s3, 28);
        lh(v0, sp, 0xB2);
        a1 = addu(v1, v0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a3 = 1;
        t0 = addiu(sp, 0x90);
        t1 = 2;
        jal(ctx, 0x3F6BE8u, gen::fn_sub_40EB50_0040eb50);
        a1 = addiu(s3, 28);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s4;
        a3 = 182;
        t0 = 0;
        jal(ctx, 0x3F6C08u, gen::fn_sub_40E3C0_0040e3c0);
        v0 = sll(s1, 1);
        v0 = addu(v0, s6);
        lh(a2, v0, 20);
        a0 = addiu(sp, 0x90);
        a1 = addiu(gp, -21488);  // "%d"
        jal(ctx, 0x3F6C24u, gen::fn_sprintf_00523ac8);
        lh(v0, sp, 0xB4);
        a0 = addu(s4, v0);
        v1 = addiu(s3, 28);
        lh(v0, sp, 0xB6);
        a1 = addu(v1, v0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a3 = 1;
        t0 = addiu(sp, 0x90);
        t1 = 2;
        jal(ctx, 0x3F6C54u, gen::fn_sub_40EB50_0040eb50);
    }
    // 0x003f6d04
    charge(ctx, 11);
    a1 = addiu(s3, 56);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a3 = 181;
    t0 = 0;
    jal(ctx, 0x3F6D1Cu, gen::fn_sub_40E3C0_0040e3c0);
    v0 = si(-1);
    if (s5 == v0) {
        // 0x003f6e4c
        charge(ctx, 40);
        v0 = 0x3F000000;
        mtc1(v0, f1);
        mtc1(s2, f0);
        cvt_s_w(f0, f0);
        mul_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(s0, f0);
        a1 = addiu(s3, 56);
        mtc1(zero, f12);
        a2 = s0 & 0xFF;
        a0 = s4;
        a3 = 206;
        t0 = 0;
        jal(ctx, 0x3F6E84u, gen::fn_sub_40E3C0_0040e3c0);
        a0 = addiu(s4, 17);
        a1 = addiu(s3, 56);
        mtc1(zero, f12);
        a2 = s0 & 0xFF;
        a3 = 206;
        t0 = 0;
        jal(ctx, 0x3F6EA4u, gen::fn_sub_40E3C0_0040e3c0);
        a0 = addiu(s4, 34);
        a1 = addiu(s3, 56);
        mtc1(zero, f12);
        a2 = s0 & 0xFF;
        a3 = 206;
        t0 = 0;
        jal(ctx, 0x3F6EC4u, gen::fn_sub_40E3C0_0040e3c0);
        a0 = addiu(s4, 51);
        a1 = addiu(s3, 56);
        mtc1(zero, f12);
        a2 = s0 & 0xFF;
        a3 = 206;
        t0 = 0;
        jal(ctx, 0x3F6EE4u, gen::fn_sub_40E3C0_0040e3c0);
    } else {
        // 0x003f6d30
        charge(ctx, 2);
        if (s7 != 0) {
            // 0x003f6d6c
            charge(ctx, 11);
            a1 = dsll32(s0, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x3F6D78u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x3F6D8Cu, gen::fn_sub_16FCC0_0016fcc0);
            a2 = v0 & 0xFFFF;
        } else {
            // 0x003f6d38
            charge(ctx, 13);
            a1 = dsll32(s0, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x3F6D44u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x3F6D58u, gen::fn_sub_16FAE0_0016fae0);
            a2 = v0 & 0xFFFF;
        }
        // 0x003f6d98
        charge(ctx, 45);
        a0 = addiu(sp, 0x90);
        a1 = addiu(gp, -21488);  // "%d"
        jal(ctx, 0x3F6DA0u, gen::fn_sprintf_00523ac8);
        lh(v0, sp, 0xB0);
        a0 = addu(s4, v0);
        v1 = addiu(s3, 56);
        lh(v0, sp, 0xB2);
        a1 = addu(v1, v0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a3 = 1;
        t0 = addiu(sp, 0x90);
        t1 = 2;
        jal(ctx, 0x3F6DD0u, gen::fn_sub_40EB50_0040eb50);
        a1 = addiu(s3, 56);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s4;
        a3 = 182;
        t0 = 0;
        jal(ctx, 0x3F6DF0u, gen::fn_sub_40E3C0_0040e3c0);
        v0 = sll(s5, 1);
        v0 = addu(v0, s6);
        lh(a2, v0, 20);
        a0 = addiu(sp, 0x90);
        a1 = addiu(gp, -21488);  // "%d"
        jal(ctx, 0x3F6E0Cu, gen::fn_sprintf_00523ac8);
        lh(v0, sp, 0xB4);
        a0 = addu(s4, v0);
        v1 = addiu(s3, 56);
        lh(v0, sp, 0xB6);
        a1 = addu(v1, v0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a3 = 1;
        t0 = addiu(sp, 0x90);
        t1 = 2;
        jal(ctx, 0x3F6E3Cu, gen::fn_sub_40EB50_0040eb50);
    }
    // 0x003f6eec (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// 0x003F6F20 sub_3F6F20 -- 1132 bytes; frame 0xB0: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [fclShopDrawCompareC] The accessory comparison of a row: sprites 117 118 at 0.82 x alpha (0x7CAEF0; the float to byte
// conversion with the 2^31 correction), 119 120, the category digit (sprite 5 at +137 / +8, + 22), 121 122, 123 124 at
// half alpha when the member table 0x7CD940 +8 marks the member, then two lines (y +35 / +62): sprite 125, and 126 at half
// alpha for no stat (-1 in table 0x6AEFB8) or the row's value as "%d" at the offset 0x7CD950.
void sub_3F6F20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x003f6f20
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    a1 = addiu(gp, -21416);  // &0x7CD948
    a0 = addiu(sp, 0xA0);
    v1 = 5;
    for (;;) {
        // 0x003f6f5c
        charge(ctx, 7);
        lb(v0, a1, 0);
        a1 = addiu(a1, 1);
        v1 = addiu(v1, -1);
        sb(v0, a0, 0);
        a0 = addiu(a0, 1);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f6f78
    charge(ctx, 8);
    lh(v1, gp, -21408);  // 0x7CD950
    lh(v0, gp, -21406);  // 0x7CD952
    sh(v1, sp, 0xAC);
    sh(v0, sp, 0xAE);
    a2 = 0x6B0000;
    a2 = addiu(a2, -4168);  // &0x6AEFB8
    a1 = addiu(sp, 0x90);
    a0 = 5;
    for (;;) {
        // 0x003f6f98
        charge(ctx, 9);
        lb(v1, a2, 0);
        lb(v0, a2, 1);
        a2 = addiu(a2, 2);
        a0 = addiu(a0, -1);
        sb(v1, a1, 0);
        sb(v0, a1, 1);
        a1 = addiu(a1, 2);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f6fbc
    charge(ctx, 16);
    lw(v0, t0, node::kPayload);
    lw(s0, v0, 28);
    lw(v0, s0, srow::kItemCategory);
    v0 = v0 & 0xF00;
    s5 = sra(v0, 8);
    mtc1(s2, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, gp, -32256);  // 0x7CAEF0
    mul_s(f20, f0, f1);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x003f7014
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x003f6ffc
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x003f702c
    charge(ctx, 13);
    mtc1(zero, f12);
    a0 = s4;
    a1 = s3;
    a3 = 117;
    t0 = 0;
    jal(ctx, 0x3F7040u, gen::fn_sub_40E3C0_0040e3c0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x003f7078
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x003f7060
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x003f7090
    charge(ctx, 53);
    mtc1(zero, f12);
    a0 = s4;
    a1 = s3;
    a3 = 118;
    t0 = 0;
    jal(ctx, 0x3F70A4u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 119;
    t0 = 0;
    jal(ctx, 0x3F70C4u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 120;
    t0 = 0;
    jal(ctx, 0x3F70E4u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s4, 137);
    a1 = addiu(s3, 8);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    lbu(v0, s0, srow::kItemCategory);
    t0 = addiu(v0, 22);
    a3 = 5;
    jal(ctx, 0x3F7108u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 121;
    t0 = 0;
    jal(ctx, 0x3F7128u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 122;
    t0 = 0;
    jal(ctx, 0x3F7148u, gen::fn_sub_40E3C0_0040e3c0);
    s1 = s2;
    v0 = addu(s5, sp);
    lb(v0, v0, 160);
    if (v0 != 0) {
        // 0x003f7164
        charge(ctx, 8);
        v0 = 0x3F000000;
        mtc1(v0, f1);
        mtc1(s2, f0);
        cvt_s_w(f0, f0);
        mul_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(s1, f0);
    }
    // 0x003f7184
    charge(ctx, 31);
    mtc1(zero, f12);
    a2 = s1 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 123;
    t0 = 0;
    jal(ctx, 0x3F719Cu, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s1 & 0xFF;
    a0 = s4;
    a1 = s3;
    a3 = 124;
    t0 = 0;
    jal(ctx, 0x3F71BCu, gen::fn_sub_40E3C0_0040e3c0);
    a1 = addiu(s3, 35);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a3 = 125;
    t0 = 0;
    jal(ctx, 0x3F71DCu, gen::fn_sub_40E3C0_0040e3c0);
    s1 = sll(s5, 1);
    v0 = addu(s1, sp);
    v0 = addiu(v0, 144);
    lb(v1, v0, 0);
    v0 = si(-1);
    if (v1 == v0) {
        // 0x003f7254
        charge(ctx, 16);
        v0 = 0x3F000000;
        mtc1(v0, f1);
        mtc1(s2, f0);
        cvt_s_w(f0, f0);
        mul_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a1 = addiu(s3, 35);
        mtc1(zero, f12);
        a2 = v0 & 0xFF;
        a0 = s4;
        a3 = 126;
        t0 = 0;
        jal(ctx, 0x3F728Cu, gen::fn_sub_40E3C0_0040e3c0);
    } else {
        // 0x003f7200
        charge(ctx, 21);
        v0 = sll(v1, 1);
        v0 = addu(v0, s0);
        lh(a2, v0, 20);
        a0 = addiu(sp, 0x80);
        a1 = addiu(gp, -21488);  // "%d"
        jal(ctx, 0x3F7214u, gen::fn_sprintf_00523ac8);
        lh(v0, sp, 0xAC);
        a0 = addu(s4, v0);
        v1 = addiu(s3, 35);
        lh(v0, sp, 0xAE);
        a1 = addu(v1, v0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a3 = 1;
        t0 = addiu(sp, 0x80);
        t1 = 2;
        jal(ctx, 0x3F7244u, gen::fn_sub_40EB50_0040eb50);
    }
    // 0x003f7294
    charge(ctx, 14);
    a1 = addiu(s3, 62);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a0 = s4;
    a3 = 125;
    t0 = 0;
    jal(ctx, 0x3F72ACu, gen::fn_sub_40E3C0_0040e3c0);
    v0 = addu(s1, sp);
    v0 = addiu(v0, 145);
    lb(v1, v0, 0);
    v0 = si(-1);
    if (v1 == v0) {
        // 0x003f7320
        charge(ctx, 16);
        v0 = 0x3F000000;
        mtc1(v0, f1);
        mtc1(s2, f0);
        cvt_s_w(f0, f0);
        mul_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a1 = addiu(s3, 62);
        mtc1(zero, f12);
        a2 = v0 & 0xFF;
        a0 = s4;
        a3 = 126;
        t0 = 0;
        jal(ctx, 0x3F7358u, gen::fn_sub_40E3C0_0040e3c0);
    } else {
        // 0x003f72cc
        charge(ctx, 21);
        v0 = sll(v1, 1);
        v0 = addu(v0, s0);
        lh(a2, v0, 20);
        a0 = addiu(sp, 0x80);
        a1 = addiu(gp, -21488);  // "%d"
        jal(ctx, 0x3F72E0u, gen::fn_sprintf_00523ac8);
        lh(v0, sp, 0xAC);
        a0 = addu(s4, v0);
        v1 = addiu(s3, 62);
        lh(v0, sp, 0xAE);
        a1 = addu(v1, v0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a3 = 1;
        t0 = addiu(sp, 0x80);
        t1 = 2;
        jal(ctx, 0x3F7310u, gen::fn_sub_40EB50_0040eb50);
    }
    // 0x003f7360 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x003F7890 sub_3F7890 -- 488 bytes; frame 0x80: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopDrawOwnedCount] Draws a row's owned-count box: a3 = 1 -> sprites (table 0x6AEFF0 words 3 / 5) and the count (row
// +14, "%2d" at 0x7CD954) at (+547, +162); a3 = 0 -> words 0 1 2 and the count at (+149, +153); other a3: nothing.
void sub_3F7890(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003f7890
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    t0 = 0x6B0000;
    t0 = addiu(t0, -4112);  // &0x6AEFF0
    a2 = addiu(sp, 0x70);
    a1 = 3;
    for (;;) {
        // 0x003f78c8
        charge(ctx, 9);
        lh(a0, t0, 0);
        lh(v1, t0, 2);
        t0 = addiu(t0, 4);
        a1 = addiu(a1, -1);
        sh(a0, a2, 0);
        sh(v1, a2, 2);
        a2 = addiu(a2, 4);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f78ec
    charge(ctx, 5);
    lw(v1, t1, node::kPayload);
    lw(s0, v1, 28);
    v1 = 1;
    if (a3 == v1) {
        // 0x003f79c8: a3 = 1
        charge(ctx, 35);
        v0 = sll(a3, 1);
        v0 = addu(v0, a3);
        s4 = sll(v0, 1);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        v0 = addu(s4, sp);
        lh(a3, v0, 112);
        a0 = s3;
        a1 = s2;
        t0 = 0;
        jal(ctx, 0x3F79F0u, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        v0 = addu(s4, sp);
        lh(a3, v0, 116);
        a0 = s3;
        a1 = s2;
        t0 = 0;
        jal(ctx, 0x3F7A14u, gen::fn_sub_40E3C0_0040e3c0);
        lh(a2, s0, srow::kOwned);
        a0 = addiu(sp, 0x60);
        a1 = addiu(gp, -21404);  // "%2d"
        jal(ctx, 0x3F7A28u, gen::fn_sprintf_00523ac8);
        a0 = addiu(s3, 547);
        a1 = addiu(s2, 162);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a3 = 3;
        t0 = addiu(sp, 0x60);
        t1 = 1;
        jal(ctx, 0x3F7A4Cu, gen::fn_sub_40EB50_0040eb50);
    } else {
        // 0x003f7900
        charge(ctx, 2);
        if (a3 == 0) {
            // 0x003f7910: a3 = 0
            charge(ctx, 46);
            v0 = sll(a3, 1);
            v0 = addu(v0, a3);
            s4 = sll(v0, 1);
            mtc1(zero, f12);
            a2 = s1 & 0xFF;
            v0 = addu(s4, sp);
            lh(a3, v0, 112);
            a0 = s3;
            a1 = s2;
            t0 = 0;
            jal(ctx, 0x3F7938u, gen::fn_sub_40E3C0_0040e3c0);
            mtc1(zero, f12);
            a2 = s1 & 0xFF;
            v0 = addu(s4, sp);
            lh(a3, v0, 114);
            a0 = s3;
            a1 = s2;
            t0 = 0;
            jal(ctx, 0x3F795Cu, gen::fn_sub_40E3C0_0040e3c0);
            mtc1(zero, f12);
            a2 = s1 & 0xFF;
            v0 = addu(s4, sp);
            lh(a3, v0, 116);
            a0 = s3;
            a1 = s2;
            t0 = 0;
            jal(ctx, 0x3F7980u, gen::fn_sub_40E3C0_0040e3c0);
            lh(a2, s0, srow::kOwned);
            a0 = addiu(sp, 0x60);
            a1 = addiu(gp, -21404);  // "%2d"
            jal(ctx, 0x3F7994u, gen::fn_sprintf_00523ac8);
            a0 = addiu(s3, 149);
            a1 = addiu(s2, 153);
            mtc1(zero, f12);
            a2 = s1 & 0xFF;
            a3 = 3;
            t0 = addiu(sp, 0x60);
            t1 = 1;
            jal(ctx, 0x3F79B8u, gen::fn_sub_40EB50_0040eb50);
        } else {
            // 0x003f7908
            charge(ctx, 2);
        }
    }
    // 0x003f7a54 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x003F9510 sub_3F9510 -- 984 bytes; frame 0xD0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopDrawListRow] The row drawer of the facility lists (nmCmdListSetRowDrawFunc in sub_3FE3E0 / sub_3FE850 /
// sub_3FEF30): a0 / a1 = x / y, a2 = alpha, a3 -> the list, t0 -> the row. The list mode (user +6) picks the drawer
// called through jalr and the cursor sprite (floats 0x6AF000.. hold the sprite ids 110 / 111 / 136): -5 sub_3F5830 with
// columns 2 and sprite 136, -4 sub_3F55B0 with 6 and 111, -3 / -2 sub_3F55B0 with 2 and 111, else sub_3F55B0 with 0 and
// 110. By the list status: 1 (idle) -> the cursor sprite unless the user flag 1 hides it, then the drawer with column bit 1
// on the cursor row; 20 (closing) -> the same at the user's slide offset (+40 / +42); 12 (opening) -> the rows slide in from
// -30 with the fade frame (up to 5 frames) and the cursor fades in after frame 4.
void sub_3F9510(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x003f9510
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
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
    s5 = a0;
    s4 = a1;
    s7 = a2;
    s3 = a3;
    s2 = t0;
    sw(zero, sp, 0xB0);
    s6 = 0;
    s1 = 0;
    v0 = 0x6B0000;
    lwc1(f2, v0, -4096);  // 0x6AF000
    v0 = 0x6B0000;
    lwc1(f1, v0, -4092);  // 0x6AF004
    v0 = 0x6B0000;
    lwc1(f0, v0, -4088);  // 0x6AF008
    swc1(f2, sp, 0xC0);
    swc1(f1, sp, 0xC4);
    swc1(f0, sp, 0xC8);
    lw(v0, a3, 36);
    lw(v0, v0, 68);
    sq(v0, sp, 0xA0);
    lh(v1, v0, 6);
    v0 = si(-5);
    if (v1 == v0) {
        // 0x003f95f8: mode -5: sub_3F5830
        charge(ctx, 6);
        s1 = 2;
        fp = s1;
        s0 = 0x3F0000;
        s0 = addiu(s0, 22576);  // &sub_3F5830
    } else {
        // 0x003f959c
        charge(ctx, 3);
        v0 = si(-4);
        if (v1 == v0) {
            // 0x003f95e0: mode -4
            charge(ctx, 6);
            s1 = 6;
            fp = 0x1;
            s0 = 0x3F0000;
            s0 = addiu(s0, 21936);  // &sub_3F55B0
        } else {
            // 0x003f95a8
            charge(ctx, 3);
            v0 = si(-3);
            if (v1 != v0) {
                // 0x003f95b4
                charge(ctx, 3);
                v0 = si(-2);
                if (v1 == v0) {
                    goto L_003f95c8;
                }
                // 0x003f95c0
                charge(ctx, 2);
                // 0x003f9610
                charge(ctx, 3);
                fp = 0;
                s0 = 0x3F0000;
                s0 = addiu(s0, 21936);  // &sub_3F55B0
                goto L_003f961c;
            }
        L_003f95c8:
            charge(ctx, 6);
            s1 = 2;
            fp = 0x1;
            s0 = 0x3F0000;
            s0 = addiu(s0, 21936);  // &sub_3F55B0
        }
    }
L_003f961c:
    charge(ctx, 6);
    a0 = s3;
    jal(ctx, 0x3F9620u, gen::fn_nmCmdListStatus28_003c6e10);
    v1 = 1;
    if (v0 == v1) {
        // 0x003f9824: status 1: idle
        charge(ctx, 3);
        lw(v0, s3, lst::kCursor);
        if (v0 != s2) {
            // 0x003f9894
            charge(ctx, 8);
            a0 = s5;
            a1 = s4;
            a2 = s7;
            a3 = s3;
            t0 = s2;
            t1 = s1;
            jalr(ctx, 0x3F98ACu, s0.u());
        } else {
            // 0x003f9830
            charge(ctx, 5);
            lq(v0, sp, 0xA0);
            lw(v0, v0, 0);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x003f9844
                charge(ctx, 10);
                mtc1(zero, f12);
                a2 = s7 & 0xFF;
                v0 = sll(fp, 2);
                v0 = addu(v0, sp);
                lw(a3, v0, 192);
                a0 = s5;
                a1 = s4;
                t0 = 0;
                jal(ctx, 0x3F9864u, gen::fn_sub_40E3C0_0040e3c0);
            }
            // 0x003f986c
            charge(ctx, 10);
            t1 = s1 | 0x1;
            a0 = s5;
            a1 = s4;
            a2 = s7;
            a3 = s3;
            t0 = s2;
            jalr(ctx, 0x3F9884u, s0.u());
        }
    } else {
        // 0x003f9634
        charge(ctx, 3);
        v1 = 20;
        if (v0 == v1) {
            // 0x003f9788: status 20: closing
            charge(ctx, 9);
            lq(v0, sp, 0xA0);
            lh(v0, v0, 40);
            s5 = addu(s5, v0);
            lq(v0, sp, 0xA0);
            lh(v0, v0, 42);
            s4 = addu(s4, v0);
            lw(v0, s3, lst::kCursor);
            if (v0 != s2) {
                // 0x003f97fc
                charge(ctx, 10);
                a0 = s5;
                a1 = s4;
                a2 = s7;
                a3 = s3;
                t0 = s2;
                t1 = s1;
                jalr(ctx, 0x3F9814u, s0.u());
            } else {
                // 0x003f97ac
                charge(ctx, 20);
                mtc1(zero, f12);
                a2 = s7 & 0xFF;
                v0 = sll(fp, 2);
                v0 = addu(v0, sp);
                lw(a3, v0, 192);
                a0 = s5;
                a1 = s4;
                t0 = 0;
                jal(ctx, 0x3F97CCu, gen::fn_sub_40E3C0_0040e3c0);
                t1 = s1 | 0x1;
                a0 = s5;
                a1 = s4;
                a2 = s7;
                a3 = s3;
                t0 = s2;
                jalr(ctx, 0x3F97ECu, s0.u());
            }
        } else {
            // 0x003f9640
            charge(ctx, 3);
            v1 = 12;
            if (v0 == v1) {
                // 0x003f9654: status 12: opening (slide in)
                charge(ctx, 11);
                lw(v1, s3, lst::kState);
                lh(v0, v1, 4);
                lw(v1, v1, 44);
                lw(a1, v1, 20);
                lw(v1, s2, node::kPayload);
                lw(a0, v1, 12);
                lw(v1, a1, 12);
                a0 = subu(a0, v1);
                v1 = slt(v0, a0);
                if (v1 == 0) {
                    // 0x003f9680
                    charge(ctx, 4);
                    s6 = subu(v0, a0);
                    v1 = slti(s6, 5);
                    if (v1 == 0) {
                        // 0x003f9690
                        charge(ctx, 1);
                        s6 = 5;
                    }
                }
                // 0x003f9694
                charge(ctx, 16);
                v1 = sll(s6, 4);
                v1 = subu(v1, s6);
                v1 = sll(v1, 1);
                a1 = 5;
                div(v1, a1);
                mflo(a0);
                v1 = 30;
                v1 = subu(v1, a0);
                s7 = subu(s5, v1);
                v1 = sll(s6, 8);
                v1 = subu(v1, s6);
                div1(v1, a1);
                mflo1(s6);
                v1 = slti(v0, 4);
                if (v1 == 0) {
                    // 0x003f96d4
                    charge(ctx, 4);
                    v1 = addiu(v0, -4);
                    v0 = slti(v1, 5);
                    if (v0 == 0) {
                        // 0x003f96e4
                        charge(ctx, 1);
                        v1 = a1;
                    }
                    // 0x003f96e8
                    charge(ctx, 6);
                    v0 = sll(v1, 8);
                    v1 = subu(v0, v1);
                    v0 = 5;
                    div(v1, v0);
                    mflo(v0);
                    sw(v0, sp, 0xB0);
                }
                // 0x003f9700
                charge(ctx, 3);
                lw(v0, s3, lst::kCursor);
                if (v0 != s2) {
                    // 0x003f9760
                    charge(ctx, 10);
                    a0 = s7;
                    a1 = s4;
                    a2 = s6;
                    a3 = s3;
                    t0 = s2;
                    t1 = s1;
                    jalr(ctx, 0x3F9778u, s0.u());
                } else {
                    // 0x003f970c
                    charge(ctx, 21);
                    mtc1(zero, f12);
                    lbu(v0, sp, 0xB0);
                    a2 = v0;
                    v0 = sll(fp, 2);
                    v0 = addu(v0, sp);
                    lw(a3, v0, 192);
                    a0 = s5;
                    a1 = s4;
                    t0 = 0;
                    jal(ctx, 0x3F9730u, gen::fn_sub_40E3C0_0040e3c0);
                    t1 = s1 | 0x1;
                    a0 = s7;
                    a1 = s4;
                    a2 = s6;
                    a3 = s3;
                    t0 = s2;
                    jalr(ctx, 0x3F9750u, s0.u());
                }
            } else {
                // 0x003f964c
                charge(ctx, 2);
            }
        }
    }
    // 0x003f98b4 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xD0);
}

// 0x003FA210 sub_3FA210 -- 780 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopListWindowAnimA]
// The window animation of a facility list (the command list's update callback, set by the list builders): a0 -> the list,
// s0 = its user area (menu::), keyed on the list status (nmCmdListStatus28) and the fade frame t (win +4):
//   status 20 (closing): x = -160 t / 10 (from t = 11: -160), alpha = 255 - 255 t / 5 (from t = 6: 0);
//   status 12 (opening): x = y = 0, alpha = 255 t / 5 (from 6: 255), then the title bar, the cursor pop and scale as in
//   each variant below; status 1 (idle): nothing. Returns the status.
// Variant A (the trade lists' callback): the bar from frame 6: x = 140 (t - 6) / 4 - 140 for t - 6 < 5 with its alpha 255
// (before frame 6: x -200, alpha 0); the cursor from frame 8: scale 0.001 + 1.079 (t - 8) / 5 for 6 frames with alpha 255
// (before: alpha 0), from frame 13 the pop 3 - 3 (t - 13) / 4 and the scale 1.08 - 0.08 (t - 13) / 4 for 5 frames.
void sub_3FA210(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x003fa210
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, a0, lst::kState);
    lw(s0, v0, win::kUser);
    jal(ctx, 0x3FA22Cu, gen::fn_nmCmdListStatus28_003c6e10);
    v1 = 1;
    if (v0 != v1) {
        // 0x003fa240
        charge(ctx, 3);
        v1 = 20;
        if (v0 == v1) {
            // 0x003fa448: status 20: closing
            charge(ctx, 5);
            lw(v1, s1, lst::kState);
            lh(a0, v1, win::kFrame);
            at = slti(a0, 11);
            if (at == 0) {
                // 0x003fa4a0
                charge(ctx, 2);
                v1 = si(-160);
                sh(v1, s0, menu::kSlideX);
            } else {
                // 0x003fa45c
                charge(ctx, 17);
                v1 = subu(0, a0);
                v1 = sll(v1, 2);
                v1 = subu(v1, a0);
                v1 = sll(v1, 5);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v1 = 0x41200000;
                mtc1(v1, f0);
                div_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                sh(v1, s0, menu::kSlideX);
            }
            // 0x003fa4a8
            charge(ctx, 3);
            at = slti(a0, 6);
            if (at == 0) {
                // 0x003fa500
                charge(ctx, 1);
                sh(zero, s0, menu::kAlpha);
            } else {
                // 0x003fa4b4
                charge(ctx, 19);
                v1 = sll(a0, 8);
                v1 = subu(a0, v1);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v1 = 0x40A00000;
                mtc1(v1, f0);
                div_s(f1, f1, f0);
                v1 = 0x437F0000;
                mtc1(v1, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                sh(v1, s0, menu::kAlpha);
            }
        } else {
            // 0x003fa24c
            charge(ctx, 3);
            v1 = 12;
            if (v0 == v1) {
                // 0x003fa260: status 12: opening
                charge(ctx, 7);
                lw(v1, s1, lst::kState);
                lh(a0, v1, win::kFrame);
                sh(zero, s0, menu::kSlideX);
                sh(zero, s0, menu::kSlideY);
                at = slti(a0, 6);
                if (at == 0) {
                    // 0x003fa2b8
                    charge(ctx, 2);
                    v1 = 255;
                    sh(v1, s0, menu::kAlpha);
                } else {
                    // 0x003fa27c
                    charge(ctx, 15);
                    v1 = sll(a0, 8);
                    v1 = subu(v1, a0);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    v1 = 0x40A00000;
                    mtc1(v1, f0);
                    div_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    sh(v1, s0, menu::kAlpha);
                }
                // 0x003fa2c0
                charge(ctx, 5);
                lw(v1, s1, lst::kState);
                lh(v1, v1, win::kFrame);
                at = slti(v1, 6);
                if (at == 0) {
                    // 0x003fa2e8
                    charge(ctx, 4);
                    a0 = addiu(v1, -6);
                    at = slti(a0, 5);
                    if (at != 0) {
                        // 0x003fa2f8
                        charge(ctx, 23);
                        v1 = sll(a0, 3);
                        a0 = subu(v1, a0);
                        v1 = sll(a0, 2);
                        v1 = addu(a0, v1);
                        v1 = sll(v1, 2);
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                        v1 = 0x40800000;
                        mtc1(v1, f0);
                        div_s(f1, f1, f0);
                        v1 = lui(0xC30C);
                        mtc1(v1, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        sh(v1, s0, menu::kBarX);
                        sh(zero, s0, menu::kBarY);
                        v1 = 255;
                        sh(v1, s0, menu::kBarAlpha);
                    }
                } else {
                    // 0x003fa2d4
                    charge(ctx, 5);
                    v1 = si(-200);
                    sh(v1, s0, menu::kBarX);
                    sh(zero, s0, menu::kBarAlpha);
                }
                // 0x003fa354
                charge(ctx, 5);
                lw(v1, s1, lst::kState);
                lh(a1, v1, win::kFrame);
                at = slti(a1, 8);
                if (at == 0) {
                    // 0x003fa374
                    charge(ctx, 4);
                    a0 = addiu(a1, -8);
                    at = slti(a0, 6);
                    if (at != 0) {
                        // 0x003fa384
                        charge(ctx, 14);
                        v1 = 255;
                        sh(v1, s0, menu::kScaleAlpha);
                        mtc1(a0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, gp, -32208);  // 0x7CAF20
                        mul_s(f1, f0, f1);
                        v1 = 0x40A00000;
                        mtc1(v1, f0);
                        div_s(f1, f1, f0);
                        lwc1(f0, gp, -32204);  // 0x7CAF24
                        add_s(f0, f0, f1);
                        swc1(f0, s0, menu::kScale);
                    }
                } else {
                    // 0x003fa368
                    charge(ctx, 3);
                    sh(zero, s0, menu::kScaleAlpha);
                }
                // 0x003fa3bc
                charge(ctx, 3);
                v1 = slti(a1, 13);
                if (v1 == 0) {
                    // 0x003fa3c8
                    charge(ctx, 4);
                    a0 = addiu(a1, -13);
                    at = slti(a0, 5);
                    if (at != 0) {
                        // 0x003fa3d8
                        charge(ctx, 28);
                        v1 = sll(a0, 2);
                        v1 = subu(a0, v1);
                        mtc1(v1, f0);
                        cvt_s_w(f0, f0);
                        v1 = 0x40800000;
                        mtc1(v1, f2);
                        div_s(f1, f0, f2);
                        v1 = 0x40400000;
                        mtc1(v1, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        sh(v1, s0, menu::kPop);
                        mtc1(a0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, gp, -32200);  // 0x7CAF28
                        mul_s(f0, f0, f1);
                        div_s(f1, f0, f2);
                        lwc1(f0, gp, -32196);  // 0x7CAF2C
                        add_s(f0, f0, f1);
                        swc1(f0, s0, menu::kScale);
                    }
                }
            } else {
                // 0x003fa258
                charge(ctx, 2);
            }
        }
    }
    // 0x003fa504 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003FA520 sub_3FA520 -- 736 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopListWindowAnimB]
// The window animation of a facility list (the command list's update callback, set by the list builders): a0 -> the list,
// s0 = its user area (menu::), keyed on the list status (nmCmdListStatus28) and the fade frame t (win +4):
//   status 20 (closing): x = -160 t / 10 (from t = 11: -160), alpha = 255 - 255 t / 5 (from t = 6: 0);
//   status 12 (opening): x = y = 0, alpha = 255 t / 5 (from 6: 255), then the title bar, the cursor pop and scale as in
//   each variant below; status 1 (idle): nothing. Returns the status.
// Variant B: the bar from frame 0: x = 160 t / 4 - 160 for t < 5 with alpha 255; the cursor as in variant A.
void sub_3FA520(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x003fa520
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, a0, lst::kState);
    lw(s0, v0, win::kUser);
    jal(ctx, 0x3FA53Cu, gen::fn_nmCmdListStatus28_003c6e10);
    v1 = 1;
    if (v0 != v1) {
        // 0x003fa550
        charge(ctx, 3);
        v1 = 20;
        if (v0 == v1) {
            // 0x003fa72c: status 20: closing
            charge(ctx, 5);
            lw(v1, s1, lst::kState);
            lh(a0, v1, win::kFrame);
            at = slti(a0, 11);
            if (at == 0) {
                // 0x003fa784
                charge(ctx, 2);
                v1 = si(-160);
                sh(v1, s0, menu::kSlideX);
            } else {
                // 0x003fa740
                charge(ctx, 17);
                v1 = subu(0, a0);
                v1 = sll(v1, 2);
                v1 = subu(v1, a0);
                v1 = sll(v1, 5);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v1 = 0x41200000;
                mtc1(v1, f0);
                div_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                sh(v1, s0, menu::kSlideX);
            }
            // 0x003fa78c
            charge(ctx, 3);
            at = slti(a0, 6);
            if (at == 0) {
                // 0x003fa7e4
                charge(ctx, 1);
                sh(zero, s0, menu::kAlpha);
            } else {
                // 0x003fa798
                charge(ctx, 19);
                v1 = sll(a0, 8);
                v1 = subu(a0, v1);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v1 = 0x40A00000;
                mtc1(v1, f0);
                div_s(f1, f1, f0);
                v1 = 0x437F0000;
                mtc1(v1, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                sh(v1, s0, menu::kAlpha);
            }
        } else {
            // 0x003fa55c
            charge(ctx, 3);
            v1 = 12;
            if (v0 == v1) {
                // 0x003fa570: status 12: opening
                charge(ctx, 7);
                lw(v1, s1, lst::kState);
                lh(a0, v1, win::kFrame);
                sh(zero, s0, menu::kSlideX);
                sh(zero, s0, menu::kSlideY);
                at = slti(a0, 6);
                if (at == 0) {
                    // 0x003fa5c8
                    charge(ctx, 2);
                    v1 = 255;
                    sh(v1, s0, menu::kAlpha);
                } else {
                    // 0x003fa58c
                    charge(ctx, 15);
                    v1 = sll(a0, 8);
                    v1 = subu(v1, a0);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    v1 = 0x40A00000;
                    mtc1(v1, f0);
                    div_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    sh(v1, s0, menu::kAlpha);
                }
                // 0x003fa5d0
                charge(ctx, 5);
                lw(v1, s1, lst::kState);
                lh(a0, v1, win::kFrame);
                at = slti(a0, 5);
                if (at != 0) {
                    // 0x003fa5e4
                    charge(ctx, 21);
                    v1 = sll(a0, 2);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 5);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    v1 = 0x40800000;
                    mtc1(v1, f0);
                    div_s(f1, f1, f0);
                    v1 = lui(0xC320);
                    mtc1(v1, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    sh(v1, s0, menu::kBarX);
                    sh(zero, s0, menu::kBarY);
                    v1 = 255;
                    sh(v1, s0, menu::kBarAlpha);
                }
                // 0x003fa638
                charge(ctx, 5);
                lw(v1, s1, lst::kState);
                lh(a1, v1, win::kFrame);
                at = slti(a1, 8);
                if (at == 0) {
                    // 0x003fa658
                    charge(ctx, 4);
                    a0 = addiu(a1, -8);
                    at = slti(a0, 6);
                    if (at != 0) {
                        // 0x003fa668
                        charge(ctx, 14);
                        v1 = 255;
                        sh(v1, s0, menu::kScaleAlpha);
                        mtc1(a0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, gp, -32208);  // 0x7CAF20
                        mul_s(f1, f0, f1);
                        v1 = 0x40A00000;
                        mtc1(v1, f0);
                        div_s(f1, f1, f0);
                        lwc1(f0, gp, -32204);  // 0x7CAF24
                        add_s(f0, f0, f1);
                        swc1(f0, s0, menu::kScale);
                    }
                } else {
                    // 0x003fa64c
                    charge(ctx, 3);
                    sh(zero, s0, menu::kScaleAlpha);
                }
                // 0x003fa6a0
                charge(ctx, 3);
                v1 = slti(a1, 13);
                if (v1 == 0) {
                    // 0x003fa6ac
                    charge(ctx, 4);
                    a0 = addiu(a1, -13);
                    at = slti(a0, 5);
                    if (at != 0) {
                        // 0x003fa6bc
                        charge(ctx, 28);
                        v1 = sll(a0, 2);
                        v1 = subu(a0, v1);
                        mtc1(v1, f0);
                        cvt_s_w(f0, f0);
                        v1 = 0x40800000;
                        mtc1(v1, f2);
                        div_s(f1, f0, f2);
                        v1 = 0x40400000;
                        mtc1(v1, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        sh(v1, s0, menu::kPop);
                        mtc1(a0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, gp, -32200);  // 0x7CAF28
                        mul_s(f0, f0, f1);
                        div_s(f1, f0, f2);
                        lwc1(f0, gp, -32196);  // 0x7CAF2C
                        add_s(f0, f0, f1);
                        swc1(f0, s0, menu::kScale);
                    }
                }
            } else {
                // 0x003fa568
                charge(ctx, 2);
            }
        }
    }
    // 0x003fa7e8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003FA800 sub_3FA800 -- 736 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopListWindowAnimC]
// The window animation of a facility list (the command list's update callback, set by the list builders): a0 -> the list,
// s0 = its user area (menu::), keyed on the list status (nmCmdListStatus28) and the fade frame t (win +4):
//   status 20 (closing): x = -160 t / 10 (from t = 11: -160), alpha = 255 - 255 t / 5 (from t = 6: 0);
//   status 12 (opening): x = y = 0, alpha = 255 t / 5 (from 6: 255), then the title bar, the cursor pop and scale as in
//   each variant below; status 1 (idle): nothing. Returns the status.
// Variant C (run on the shop route): the same timings as variant B.
void sub_3FA800(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x003fa800
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, a0, lst::kState);
    lw(s0, v0, win::kUser);
    jal(ctx, 0x3FA81Cu, gen::fn_nmCmdListStatus28_003c6e10);
    v1 = 1;
    if (v0 != v1) {
        // 0x003fa830
        charge(ctx, 3);
        v1 = 20;
        if (v0 == v1) {
            // 0x003faa0c: status 20: closing
            charge(ctx, 5);
            lw(v1, s1, lst::kState);
            lh(a0, v1, win::kFrame);
            at = slti(a0, 11);
            if (at == 0) {
                // 0x003faa64
                charge(ctx, 2);
                v1 = si(-160);
                sh(v1, s0, menu::kSlideX);
            } else {
                // 0x003faa20
                charge(ctx, 17);
                v1 = subu(0, a0);
                v1 = sll(v1, 2);
                v1 = subu(v1, a0);
                v1 = sll(v1, 5);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v1 = 0x41200000;
                mtc1(v1, f0);
                div_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                sh(v1, s0, menu::kSlideX);
            }
            // 0x003faa6c
            charge(ctx, 3);
            at = slti(a0, 6);
            if (at == 0) {
                // 0x003faac4
                charge(ctx, 1);
                sh(zero, s0, menu::kAlpha);
            } else {
                // 0x003faa78
                charge(ctx, 19);
                v1 = sll(a0, 8);
                v1 = subu(a0, v1);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v1 = 0x40A00000;
                mtc1(v1, f0);
                div_s(f1, f1, f0);
                v1 = 0x437F0000;
                mtc1(v1, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                sh(v1, s0, menu::kAlpha);
            }
        } else {
            // 0x003fa83c
            charge(ctx, 3);
            v1 = 12;
            if (v0 == v1) {
                // 0x003fa850: status 12: opening
                charge(ctx, 7);
                lw(v1, s1, lst::kState);
                lh(a0, v1, win::kFrame);
                sh(zero, s0, menu::kSlideX);
                sh(zero, s0, menu::kSlideY);
                at = slti(a0, 6);
                if (at == 0) {
                    // 0x003fa8a8
                    charge(ctx, 2);
                    v1 = 255;
                    sh(v1, s0, menu::kAlpha);
                } else {
                    // 0x003fa86c
                    charge(ctx, 15);
                    v1 = sll(a0, 8);
                    v1 = subu(v1, a0);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    v1 = 0x40A00000;
                    mtc1(v1, f0);
                    div_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    sh(v1, s0, menu::kAlpha);
                }
                // 0x003fa8b0
                charge(ctx, 5);
                lw(v1, s1, lst::kState);
                lh(a0, v1, win::kFrame);
                at = slti(a0, 5);
                if (at != 0) {
                    // 0x003fa8c4
                    charge(ctx, 21);
                    v1 = sll(a0, 2);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 5);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    v1 = 0x40800000;
                    mtc1(v1, f0);
                    div_s(f1, f1, f0);
                    v1 = lui(0xC320);
                    mtc1(v1, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    sh(v1, s0, menu::kBarX);
                    sh(zero, s0, menu::kBarY);
                    v1 = 255;
                    sh(v1, s0, menu::kBarAlpha);
                }
                // 0x003fa918
                charge(ctx, 5);
                lw(v1, s1, lst::kState);
                lh(a1, v1, win::kFrame);
                at = slti(a1, 8);
                if (at == 0) {
                    // 0x003fa938
                    charge(ctx, 4);
                    a0 = addiu(a1, -8);
                    at = slti(a0, 6);
                    if (at != 0) {
                        // 0x003fa948
                        charge(ctx, 14);
                        v1 = 255;
                        sh(v1, s0, menu::kScaleAlpha);
                        mtc1(a0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, gp, -32208);  // 0x7CAF20
                        mul_s(f1, f0, f1);
                        v1 = 0x40A00000;
                        mtc1(v1, f0);
                        div_s(f1, f1, f0);
                        lwc1(f0, gp, -32204);  // 0x7CAF24
                        add_s(f0, f0, f1);
                        swc1(f0, s0, menu::kScale);
                    }
                } else {
                    // 0x003fa92c
                    charge(ctx, 3);
                    sh(zero, s0, menu::kScaleAlpha);
                }
                // 0x003fa980
                charge(ctx, 3);
                v1 = slti(a1, 13);
                if (v1 == 0) {
                    // 0x003fa98c
                    charge(ctx, 4);
                    a0 = addiu(a1, -13);
                    at = slti(a0, 5);
                    if (at != 0) {
                        // 0x003fa99c
                        charge(ctx, 28);
                        v1 = sll(a0, 2);
                        v1 = subu(a0, v1);
                        mtc1(v1, f0);
                        cvt_s_w(f0, f0);
                        v1 = 0x40800000;
                        mtc1(v1, f2);
                        div_s(f1, f0, f2);
                        v1 = 0x40400000;
                        mtc1(v1, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        sh(v1, s0, menu::kPop);
                        mtc1(a0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, gp, -32200);  // 0x7CAF28
                        mul_s(f0, f0, f1);
                        div_s(f1, f0, f2);
                        lwc1(f0, gp, -32196);  // 0x7CAF2C
                        add_s(f0, f0, f1);
                        swc1(f0, s0, menu::kScale);
                    }
                }
            } else {
                // 0x003fa848
                charge(ctx, 2);
            }
        }
    }
    // 0x003faac8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003FAAE0 sub_3FAAE0 -- 736 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopListWindowAnimD]
// The window animation of a facility list (the command list's update callback, set by the list builders): a0 -> the list,
// s0 = its user area (menu::), keyed on the list status (nmCmdListStatus28) and the fade frame t (win +4):
//   status 20 (closing): x = -160 t / 10 (from t = 11: -160), alpha = 255 - 255 t / 5 (from t = 6: 0);
//   status 12 (opening): x = y = 0, alpha = 255 t / 5 (from 6: 255), then the title bar, the cursor pop and scale as in
//   each variant below; status 1 (idle): nothing. Returns the status.
// Variant D: the same timings as variant B (a separate copy in the binary).
void sub_3FAAE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x003faae0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, a0, lst::kState);
    lw(s0, v0, win::kUser);
    jal(ctx, 0x3FAAFCu, gen::fn_nmCmdListStatus28_003c6e10);
    v1 = 1;
    if (v0 != v1) {
        // 0x003fab10
        charge(ctx, 3);
        v1 = 20;
        if (v0 == v1) {
            // 0x003facec: status 20: closing
            charge(ctx, 5);
            lw(v1, s1, lst::kState);
            lh(a0, v1, win::kFrame);
            at = slti(a0, 11);
            if (at == 0) {
                // 0x003fad44
                charge(ctx, 2);
                v1 = si(-160);
                sh(v1, s0, menu::kSlideX);
            } else {
                // 0x003fad00
                charge(ctx, 17);
                v1 = subu(0, a0);
                v1 = sll(v1, 2);
                v1 = subu(v1, a0);
                v1 = sll(v1, 5);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v1 = 0x41200000;
                mtc1(v1, f0);
                div_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                sh(v1, s0, menu::kSlideX);
            }
            // 0x003fad4c
            charge(ctx, 3);
            at = slti(a0, 6);
            if (at == 0) {
                // 0x003fada4
                charge(ctx, 1);
                sh(zero, s0, menu::kAlpha);
            } else {
                // 0x003fad58
                charge(ctx, 19);
                v1 = sll(a0, 8);
                v1 = subu(a0, v1);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v1 = 0x40A00000;
                mtc1(v1, f0);
                div_s(f1, f1, f0);
                v1 = 0x437F0000;
                mtc1(v1, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                sh(v1, s0, menu::kAlpha);
            }
        } else {
            // 0x003fab1c
            charge(ctx, 3);
            v1 = 12;
            if (v0 == v1) {
                // 0x003fab30: status 12: opening
                charge(ctx, 7);
                lw(v1, s1, lst::kState);
                lh(a0, v1, win::kFrame);
                sh(zero, s0, menu::kSlideX);
                sh(zero, s0, menu::kSlideY);
                at = slti(a0, 6);
                if (at == 0) {
                    // 0x003fab88
                    charge(ctx, 2);
                    v1 = 255;
                    sh(v1, s0, menu::kAlpha);
                } else {
                    // 0x003fab4c
                    charge(ctx, 15);
                    v1 = sll(a0, 8);
                    v1 = subu(v1, a0);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    v1 = 0x40A00000;
                    mtc1(v1, f0);
                    div_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    sh(v1, s0, menu::kAlpha);
                }
                // 0x003fab90
                charge(ctx, 5);
                lw(v1, s1, lst::kState);
                lh(a0, v1, win::kFrame);
                at = slti(a0, 5);
                if (at != 0) {
                    // 0x003faba4
                    charge(ctx, 21);
                    v1 = sll(a0, 2);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 5);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    v1 = 0x40800000;
                    mtc1(v1, f0);
                    div_s(f1, f1, f0);
                    v1 = lui(0xC320);
                    mtc1(v1, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    sh(v1, s0, menu::kBarX);
                    sh(zero, s0, menu::kBarY);
                    v1 = 255;
                    sh(v1, s0, menu::kBarAlpha);
                }
                // 0x003fabf8
                charge(ctx, 5);
                lw(v1, s1, lst::kState);
                lh(a1, v1, win::kFrame);
                at = slti(a1, 8);
                if (at == 0) {
                    // 0x003fac18
                    charge(ctx, 4);
                    a0 = addiu(a1, -8);
                    at = slti(a0, 6);
                    if (at != 0) {
                        // 0x003fac28
                        charge(ctx, 14);
                        v1 = 255;
                        sh(v1, s0, menu::kScaleAlpha);
                        mtc1(a0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, gp, -32208);  // 0x7CAF20
                        mul_s(f1, f0, f1);
                        v1 = 0x40A00000;
                        mtc1(v1, f0);
                        div_s(f1, f1, f0);
                        lwc1(f0, gp, -32204);  // 0x7CAF24
                        add_s(f0, f0, f1);
                        swc1(f0, s0, menu::kScale);
                    }
                } else {
                    // 0x003fac0c
                    charge(ctx, 3);
                    sh(zero, s0, menu::kScaleAlpha);
                }
                // 0x003fac60
                charge(ctx, 3);
                v1 = slti(a1, 13);
                if (v1 == 0) {
                    // 0x003fac6c
                    charge(ctx, 4);
                    a0 = addiu(a1, -13);
                    at = slti(a0, 5);
                    if (at != 0) {
                        // 0x003fac7c
                        charge(ctx, 28);
                        v1 = sll(a0, 2);
                        v1 = subu(a0, v1);
                        mtc1(v1, f0);
                        cvt_s_w(f0, f0);
                        v1 = 0x40800000;
                        mtc1(v1, f2);
                        div_s(f1, f0, f2);
                        v1 = 0x40400000;
                        mtc1(v1, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        sh(v1, s0, menu::kPop);
                        mtc1(a0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, gp, -32200);  // 0x7CAF28
                        mul_s(f0, f0, f1);
                        div_s(f1, f0, f2);
                        lwc1(f0, gp, -32196);  // 0x7CAF2C
                        add_s(f0, f0, f1);
                        swc1(f0, s0, menu::kScale);
                    }
                }
            } else {
                // 0x003fab28
                charge(ctx, 2);
            }
        }
    }
    // 0x003fada8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003FADC0 sub_3FADC0 -- 764 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopListWindowAnimE]
// The window animation of a facility list (the command list's update callback, set by the list builders): a0 -> the list,
// s0 = its user area (menu::), keyed on the list status (nmCmdListStatus28) and the fade frame t (win +4):
//   status 20 (closing): x = -160 t / 10 (from t = 11: -160), alpha = 255 - 255 t / 5 (from t = 6: 0);
//   status 12 (opening): x = y = 0, alpha = 255 t / 5 (from 6: 255), then the title bar, the cursor pop and scale as in
//   each variant below; status 1 (idle): nothing. Returns the status.
// Variant E (the weapon-fusion lists): the bar as in variant A; the cursor from frame 1: scale 0.001 + 1.079 (t - 1) / 5
// for 6 frames, from frame 6 the pop 3 - 3 (t - 5) / 3 and the scale 1.08 - 0.08 (t - 5) / 3 for 4 frames.
void sub_3FADC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x003fadc0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, a0, lst::kState);
    lw(s0, v0, win::kUser);
    jal(ctx, 0x3FADDCu, gen::fn_nmCmdListStatus28_003c6e10);
    v1 = 1;
    if (v0 != v1) {
        // 0x003fadf0
        charge(ctx, 3);
        v1 = 20;
        if (v0 == v1) {
            // 0x003fafe8: status 20: closing
            charge(ctx, 5);
            lw(v1, s1, lst::kState);
            lh(a0, v1, win::kFrame);
            at = slti(a0, 11);
            if (at == 0) {
                // 0x003fb040
                charge(ctx, 2);
                v1 = si(-160);
                sh(v1, s0, menu::kSlideX);
            } else {
                // 0x003faffc
                charge(ctx, 17);
                v1 = subu(0, a0);
                v1 = sll(v1, 2);
                v1 = subu(v1, a0);
                v1 = sll(v1, 5);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v1 = 0x41200000;
                mtc1(v1, f0);
                div_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                sh(v1, s0, menu::kSlideX);
            }
            // 0x003fb048
            charge(ctx, 3);
            at = slti(a0, 6);
            if (at == 0) {
                // 0x003fb0a0
                charge(ctx, 1);
                sh(zero, s0, menu::kAlpha);
            } else {
                // 0x003fb054
                charge(ctx, 19);
                v1 = sll(a0, 8);
                v1 = subu(a0, v1);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v1 = 0x40A00000;
                mtc1(v1, f0);
                div_s(f1, f1, f0);
                v1 = 0x437F0000;
                mtc1(v1, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                sh(v1, s0, menu::kAlpha);
            }
        } else {
            // 0x003fadfc
            charge(ctx, 3);
            v1 = 12;
            if (v0 == v1) {
                // 0x003fae10: status 12: opening
                charge(ctx, 7);
                lw(v1, s1, lst::kState);
                lh(a0, v1, win::kFrame);
                sh(zero, s0, menu::kSlideX);
                sh(zero, s0, menu::kSlideY);
                at = slti(a0, 6);
                if (at == 0) {
                    // 0x003fae68
                    charge(ctx, 2);
                    v1 = 255;
                    sh(v1, s0, menu::kAlpha);
                } else {
                    // 0x003fae2c
                    charge(ctx, 15);
                    v1 = sll(a0, 8);
                    v1 = subu(v1, a0);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    v1 = 0x40A00000;
                    mtc1(v1, f0);
                    div_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    sh(v1, s0, menu::kAlpha);
                }
                // 0x003fae70
                charge(ctx, 5);
                lw(v1, s1, lst::kState);
                lh(v1, v1, win::kFrame);
                at = slti(v1, 6);
                if (at == 0) {
                    // 0x003fae98
                    charge(ctx, 4);
                    a0 = addiu(v1, -6);
                    at = slti(a0, 5);
                    if (at != 0) {
                        // 0x003faea8
                        charge(ctx, 23);
                        v1 = sll(a0, 3);
                        a0 = subu(v1, a0);
                        v1 = sll(a0, 2);
                        v1 = addu(a0, v1);
                        v1 = sll(v1, 2);
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                        v1 = 0x40800000;
                        mtc1(v1, f0);
                        div_s(f1, f1, f0);
                        v1 = lui(0xC30C);
                        mtc1(v1, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        sh(v1, s0, menu::kBarX);
                        sh(zero, s0, menu::kBarY);
                        v1 = 255;
                        sh(v1, s0, menu::kBarAlpha);
                    }
                } else {
                    // 0x003fae84
                    charge(ctx, 5);
                    v1 = si(-200);
                    sh(v1, s0, menu::kBarX);
                    sh(zero, s0, menu::kBarAlpha);
                }
                // 0x003faf04
                charge(ctx, 4);
                lw(v1, s1, lst::kState);
                lh(a1, v1, win::kFrame);
                if (i64(a1) > 0) {
                    // 0x003faf20
                    charge(ctx, 4);
                    a0 = addiu(a1, -1);
                    at = slti(a0, 6);
                    if (at != 0) {
                        // 0x003faf30
                        charge(ctx, 14);
                        v1 = 255;
                        sh(v1, s0, menu::kScaleAlpha);
                        mtc1(a0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, gp, -32208);  // 0x7CAF20
                        mul_s(f1, f0, f1);
                        v1 = 0x40A00000;
                        mtc1(v1, f0);
                        div_s(f1, f1, f0);
                        lwc1(f0, gp, -32204);  // 0x7CAF24
                        add_s(f0, f0, f1);
                        swc1(f0, s0, menu::kScale);
                    }
                } else {
                    // 0x003faf14
                    charge(ctx, 3);
                    sh(zero, s0, menu::kScaleAlpha);
                }
                // 0x003faf68
                charge(ctx, 3);
                v1 = slti(a1, 6);
                if (v1 == 0) {
                    // 0x003faf74
                    charge(ctx, 4);
                    a0 = addiu(a1, -5);
                    at = slti(a0, 4);
                    if (at != 0) {
                        // 0x003faf84
                        charge(ctx, 25);
                        v1 = sll(a0, 2);
                        v1 = subu(a0, v1);
                        mtc1(v1, f0);
                        cvt_s_w(f0, f0);
                        v1 = 0x40400000;
                        mtc1(v1, f2);
                        div_s(f0, f0, f2);
                        add_s(f0, f2, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        sh(v1, s0, menu::kPop);
                        mtc1(a0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, gp, -32200);  // 0x7CAF28
                        mul_s(f0, f0, f1);
                        div_s(f1, f0, f2);
                        lwc1(f0, gp, -32196);  // 0x7CAF2C
                        add_s(f0, f0, f1);
                        swc1(f0, s0, menu::kScale);
                    }
                }
            } else {
                // 0x003fae08
                charge(ctx, 2);
            }
        }
    }
    // 0x003fb0a4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003FB0C0 sub_3FB0C0 -- 464 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopQtyOpen] Opens the quantity selector a0 (qsel::) at count 1 (a1 = 0 buying, else selling): flags |= 1 and the
// mode bit (2 buy / 4 sell). Buying: the maximum is 99, or yen / price (sub_16DD50, unsigned) when there is a price, at
// most 99 - owned, and the stock left (sub_17D250(the shop date key, item)) when there is a limit (-1 none); flag 8 when
// the count reached it. Selling: flag 8 when the count reached the owned count (+22). Flag 0x10 when the count is 1. A null
// a0 is K_Assert("fclShopMisc.c", 4090) (it continues).
void sub_3FB0C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fb0c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    if (s1 == 0) {
        // 0x003fb0e0: no selector: K_Assert (retail continues)
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 4090;
        jal(ctx, 0x3FB0ECu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003fb0f4
    charge(ctx, 11);
    lw(v1, s1, qsel::kFlags);
    v1 = v1 | 0x1;
    sw(v1, s1, qsel::kFlags);
    v1 = 1;
    sw(v1, s1, qsel::kCount);
    sh(v1, s1, qsel::kWord4);
    sh(zero, s1, qsel::kWord42);
    sh(zero, s1, qsel::kWord44);
    sh(zero, s1, qsel::kWord46);
    if (s0 == 0) {
        // 0x003fb134: buying
        charge(ctx, 3);
        lw(v1, s1, qsel::kFlags);
        v1 = v1 | 0x2;
        sw(v1, s1, qsel::kFlags);
    } else {
        // 0x003fb120: selling
        charge(ctx, 5);
        lw(v1, s1, qsel::kFlags);
        v1 = v1 | 0x4;
        sw(v1, s1, qsel::kFlags);
    }
    // 0x003fb140
    charge(ctx, 4);
    lw(a1, s1, qsel::kFlags);
    v1 = a1 & 0x2;
    if (v1 == 0) {
        // 0x003fb208
        charge(ctx, 3);
        v1 = a1 & 0x4;
        if (v1 != 0) {
            // 0x003fb214: selling: at the owned count?
            charge(ctx, 5);
            lw(a0, s1, qsel::kCount);
            lh(v1, s1, qsel::kLimit);
            v1 = slt(a0, v1);
            if (v1 != 0) {
                // 0x003fb238
                charge(ctx, 3);
                v1 = si(-9);
                v1 = a1 & v1;
                sw(v1, s1, qsel::kFlags);
            } else {
                // 0x003fb228
                charge(ctx, 4);
                v1 = a1 | 0x8;
                sw(v1, s1, qsel::kFlags);
            }
        }
    } else {
        // 0x003fb150: buying: the maximum
        charge(ctx, 4);
        s0 = 99;
        lw(v0, s1, qsel::kPrice);
        if (v0 != 0) {
            // 0x003fb160: yen / price
            charge(ctx, 5);
            jal(ctx, 0x3FB160u, gen::fn_sub_16DD50_0016dd50);
            lw(v1, s1, qsel::kPrice);
            divu(v0, v1);
            mflo(s0);
        }
        // 0x003fb174
        charge(ctx, 5);
        lh(v1, s1, qsel::kLimit);
        v0 = addu(s0, v1);
        at = slti(v0, 100);
        if (at == 0) {
            // 0x003fb188: at most 99 - owned
            charge(ctx, 2);
            v0 = 99;
            s0 = subu(v0, v1);
        }
        // 0x003fb190: the stock left
        charge(ctx, 11);
        jal(ctx, 0x3FB190u, gen::fn_sub_3E6DC0_003e6dc0);
        sh(v0, sp, 0x3C);
        sh(zero, sp, 0x3E);
        lhu(a1, s1, qsel::kItemId);
        lw(a0, sp, 0x3C);
        jal(ctx, 0x3FB1A8u, gen::fn_sub_17D250_0017d250);
        v1 = si(-1);
        if (v0 != v1) {
            // 0x003fb1bc
            charge(ctx, 3);
            at = slt(v0, s0);
            if (at != 0) {
                // 0x003fb1c8: the stock is the limit
                charge(ctx, 1);
                s0 = v0;
            }
        }
        // 0x003fb1cc
        charge(ctx, 4);
        lw(v1, s1, qsel::kCount);
        v1 = slt(v1, s0);
        if (v1 != 0) {
            // 0x003fb1f0: below the maximum
            charge(ctx, 6);
            lw(a0, s1, qsel::kFlags);
            v1 = si(-9);
            v1 = a0 & v1;
            sw(v1, s1, qsel::kFlags);
        } else {
            // 0x003fb1dc: at the maximum: flag 8
            charge(ctx, 5);
            lw(v1, s1, qsel::kFlags);
            v1 = v1 | 0x8;
            sw(v1, s1, qsel::kFlags);
        }
    }
    // 0x003fb244
    charge(ctx, 4);
    lw(a0, s1, qsel::kCount);
    v1 = 1;
    if (a0 != v1) {
        // 0x003fb268
        charge(ctx, 4);
        lw(a0, s1, qsel::kFlags);
        v1 = si(-17);
        v1 = a0 & v1;
        sw(v1, s1, qsel::kFlags);
    } else {
        // 0x003fb254: count 1: flag 0x10
        charge(ctx, 5);
        lw(v1, s1, qsel::kFlags);
        v1 = v1 | 0x10;
        sw(v1, s1, qsel::kFlags);
    }
    // 0x003fb278 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003FB2F0 sub_3FB2F0 -- 564 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopQtyStepBuy] One frame of the buying quantity selector a0 (qsel::): the pad (0x7E0952 / 0x7E095A) gives the step
// +1 (0x1000 up), -1 (0x4000 down), +10 (0x2000 right) or -10 (0x8000 left); the new count is clamped to 1..99, then to the
// maximum (yen / price, 99 - owned, the stock left; see sub_3FB0C0) with flag 8 at the maximum, flag 0x10 at 1. Returns 1
// when the count went up, 2 when it went down, 0 when it stayed (or no key).
void sub_3FB2F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fb2f0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s1 = 0;
    jal(ctx, 0x3FB310u, gen::fn_sub_16DD50_0016dd50);
    v0 = 0x7E0000;
    lhu(a0, v0, 2386);  // 0x7E0952
    v0 = a0 & 0x1000;
    if (v0 == 0) {
        // 0x003fb32c
        charge(ctx, 5);
        v0 = 0x7E0000;
        lhu(v1, v0, 2394);  // 0x7E095A
        v0 = v1 & 0x1000;
        if (v0 != 0) {
            goto L_003fb340;
        }
        // 0x003fb34c
        charge(ctx, 3);
        v0 = a0 & 0x4000;
        if (v0 == 0) {
            // 0x003fb358
            charge(ctx, 3);
            v0 = v1 & 0x4000;
            if (v0 != 0) {
                goto L_003fb364;
            }
            // 0x003fb370
            charge(ctx, 3);
            v0 = a0 & 0x2000;
            if (v0 == 0) {
                // 0x003fb37c
                charge(ctx, 3);
                v0 = v1 & 0x2000;
                if (v0 != 0) {
                    goto L_003fb388;
                }
                // 0x003fb394
                charge(ctx, 3);
                v0 = a0 & 0x8000;
                if (v0 == 0) {
                    // 0x003fb3a0
                    charge(ctx, 3);
                    v0 = v1 & 0x8000;
                    if (v0 != 0) {
                        goto L_003fb3ac;
                    }
                    goto L_003fb3b0;
                }
            L_003fb3ac:
                charge(ctx, 1);
                s1 = si(-10);
                goto L_003fb3b0;
            }
        L_003fb388:
            charge(ctx, 3);
            s1 = 10;
            goto L_003fb3b0;
        }
    L_003fb364:
        charge(ctx, 3);
        s1 = si(-1);
        goto L_003fb3b0;
    }
L_003fb340:
    charge(ctx, 3);
    s1 = 1;
L_003fb3b0:
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x003fb3b8: a step: clamp to 1..99
        charge(ctx, 5);
        lw(v0, s3, qsel::kCount);
        s2 = addu(v0, s1);
        at = slti(s2, 100);
        if (at != 0) {
            // 0x003fb3d8
            charge(ctx, 2);
            if (i64(s2) <= 0) {
                // 0x003fb3e0
                charge(ctx, 1);
                s2 = 1;
            }
        } else {
            // 0x003fb3cc
            charge(ctx, 3);
            s2 = 99;
        }
        // 0x003fb3e4: the maximum: yen / price
        charge(ctx, 4);
        s0 = 99;
        lw(v0, s3, qsel::kPrice);
        if (v0 != 0) {
            // 0x003fb3f4
            charge(ctx, 5);
            jal(ctx, 0x3FB3F4u, gen::fn_sub_16DD50_0016dd50);
            lw(v1, s3, qsel::kPrice);
            divu(v0, v1);
            mflo(s0);
        }
        // 0x003fb408
        charge(ctx, 5);
        lh(v1, s3, qsel::kLimit);
        v0 = addu(s0, v1);
        at = slti(v0, 100);
        if (at == 0) {
            // 0x003fb41c: at most 99 - owned
            charge(ctx, 2);
            v0 = 99;
            s0 = subu(v0, v1);
        }
        // 0x003fb424: the stock left
        charge(ctx, 11);
        jal(ctx, 0x3FB424u, gen::fn_sub_3E6DC0_003e6dc0);
        sh(v0, sp, 0x5C);
        sh(zero, sp, 0x5E);
        lhu(a1, s3, qsel::kItemId);
        lw(a0, sp, 0x5C);
        jal(ctx, 0x3FB43Cu, gen::fn_sub_17D250_0017d250);
        v1 = si(-1);
        if (v0 != v1) {
            // 0x003fb450
            charge(ctx, 3);
            at = slt(v0, s0);
            if (at != 0) {
                // 0x003fb45c
                charge(ctx, 1);
                s0 = v0;
            }
        }
        // 0x003fb460
        charge(ctx, 3);
        v0 = slt(s2, s0);
        if (v0 != 0) {
            // 0x003fb484: below the maximum
            charge(ctx, 4);
            lw(v1, s3, qsel::kFlags);
            v0 = si(-9);
            v0 = v1 & v0;
            sw(v0, s3, qsel::kFlags);
        } else {
            // 0x003fb46c: at the maximum: flag 8, the count = the maximum
            charge(ctx, 6);
            lw(v0, s3, qsel::kFlags);
            v0 = v0 | 0x8;
            sw(v0, s3, qsel::kFlags);
            s2 = s0;
        }
        // 0x003fb494
        charge(ctx, 3);
        v0 = 1;
        if (s2 != v0) {
            // 0x003fb4b4
            charge(ctx, 4);
            lw(v1, s3, qsel::kFlags);
            v0 = si(-17);
            v0 = v1 & v0;
            sw(v0, s3, qsel::kFlags);
        } else {
            // 0x003fb4a0
            charge(ctx, 5);
            lw(v0, s3, qsel::kFlags);
            v0 = v0 | 0x10;
            sw(v0, s3, qsel::kFlags);
        }
        // 0x003fb4c4: the count changed: store it, 1 up / 2 down
        charge(ctx, 3);
        lw(v0, s3, qsel::kCount);
        if (v0 != s2) {
            // 0x003fb4dc
            charge(ctx, 3);
            sw(s2, s3, qsel::kCount);
            if (i64(s1) <= 0) {
                // 0x003fb4f4
                charge(ctx, 2);
                if (i64(s1) < 0) {
                    // 0x003fb4fc
                    charge(ctx, 1);
                    s1 = 2;
                }
            } else {
                // 0x003fb4e8
                charge(ctx, 3);
                s1 = 1;
            }
            goto L_003fb500;
        }
        // 0x003fb4d0
        charge(ctx, 3);
        v0 = 0;
        // 0x003fb504 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x60);
        return;
    }
L_003fb500:
    charge(ctx, 1);
    v0 = s1;
    // 0x003fb504 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003FB530 sub_3FB530 -- 376 bytes; leaf frame (no stack)
// [fclShopQtyStepSell] One frame of the selling quantity selector a0 (qsel::): the same keys as sub_3FB2F0; the count is
// clamped to 1..owned (+22) with flag 8 at the owned count and 0x10 at 1. Returns 1 up / 2 down / 0 unchanged.
void sub_3FB530(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x003fb530
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0;
    lh(a3, a0, qsel::kLimit);
    v1 = 0x7E0000;
    lhu(a2, v1, 2386);  // 0x7E0952
    v1 = a2 & 0x1000;
    if (v1 == 0) {
        // 0x003fb54c
        charge(ctx, 5);
        v1 = 0x7E0000;
        lhu(a1, v1, 2394);  // 0x7E095A
        v1 = a1 & 0x1000;
        if (v1 != 0) {
            goto L_003fb560;
        }
        // 0x003fb56c
        charge(ctx, 3);
        v1 = a2 & 0x4000;
        if (v1 == 0) {
            // 0x003fb578
            charge(ctx, 3);
            v1 = a1 & 0x4000;
            if (v1 != 0) {
                goto L_003fb584;
            }
            // 0x003fb590
            charge(ctx, 3);
            v1 = a2 & 0x2000;
            if (v1 == 0) {
                // 0x003fb59c
                charge(ctx, 3);
                v1 = a1 & 0x2000;
                if (v1 != 0) {
                    goto L_003fb5a8;
                }
                // 0x003fb5b4
                charge(ctx, 3);
                v1 = a2 & 0x8000;
                if (v1 == 0) {
                    // 0x003fb5c0
                    charge(ctx, 3);
                    v1 = a1 & 0x8000;
                    if (v1 != 0) {
                        goto L_003fb5cc;
                    }
                    goto L_003fb5d0;
                }
            L_003fb5cc:
                charge(ctx, 1);
                v0 = si(-10);
                goto L_003fb5d0;
            }
        L_003fb5a8:
            charge(ctx, 3);
            v0 = 10;
            goto L_003fb5d0;
        }
    L_003fb584:
        charge(ctx, 3);
        v0 = si(-1);
        goto L_003fb5d0;
    }
L_003fb560:
    charge(ctx, 3);
    v0 = 1;
L_003fb5d0:
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x003fb5d8: a step: clamp to 1..owned
        charge(ctx, 5);
        lw(v1, a0, qsel::kCount);
        a2 = addu(v1, v0);
        at = slt(a3, a2);
        if (at == 0) {
            // 0x003fb5f8
            charge(ctx, 2);
            if (i64(a2) <= 0) {
                // 0x003fb600
                charge(ctx, 1);
                a2 = 1;
            }
        } else {
            // 0x003fb5ec
            charge(ctx, 3);
            a2 = a3;
        }
        // 0x003fb604
        charge(ctx, 3);
        v1 = slt(a2, a3);
        if (v1 != 0) {
            // 0x003fb624
            charge(ctx, 4);
            lw(a1, a0, qsel::kFlags);
            v1 = si(-9);
            v1 = a1 & v1;
            sw(v1, a0, qsel::kFlags);
        } else {
            // 0x003fb610
            charge(ctx, 5);
            lw(v1, a0, qsel::kFlags);
            v1 = v1 | 0x8;
            sw(v1, a0, qsel::kFlags);
        }
        // 0x003fb634
        charge(ctx, 3);
        v1 = 1;
        if (a2 != v1) {
            // 0x003fb654
            charge(ctx, 4);
            lw(a1, a0, qsel::kFlags);
            v1 = si(-17);
            v1 = a1 & v1;
            sw(v1, a0, qsel::kFlags);
        } else {
            // 0x003fb640
            charge(ctx, 5);
            lw(v1, a0, qsel::kFlags);
            v1 = v1 | 0x10;
            sw(v1, a0, qsel::kFlags);
        }
        // 0x003fb664: the count changed: store it, 1 up / 2 down
        charge(ctx, 3);
        lw(v1, a0, qsel::kCount);
        if (v1 != a2) {
            // 0x003fb67c
            charge(ctx, 3);
            sw(a2, a0, qsel::kCount);
            if (i64(v0) <= 0) {
                // 0x003fb694
                charge(ctx, 2);
                if (i64(v0) < 0) {
                    // 0x003fb69c
                    charge(ctx, 1);
                    v0 = 2;
                }
            } else {
                // 0x003fb688
                charge(ctx, 3);
                v0 = 1;
            }
        } else {
            // 0x003fb670
            charge(ctx, 3);
            v0 = 0;
        }
    }
    // 0x003fb6a0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003FBF10 sub_3FBF10 -- 16 bytes; leaf frame (no stack)
// [fclShopSetWord3] Stores 3 into the halfword at a0 (the BUY update sub_3E9AF0's request record).
void sub_3FBF10(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x003fbf10
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 3;
    sh(v1, a0, 0);
}

// 0x003FCA00 sub_3FCA00 -- 196 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopDrawFrameSprites] Draws the sprites 82 83 84 80 81 at (0, 0) with alpha a2.
void sub_3FCA00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003fca00
    enter(ctx, 49);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a2;
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a0 = 0;
    a1 = 0;
    a3 = 82;
    t0 = 0;
    jal(ctx, 0x3FCA28u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a0 = 0;
    a1 = 0;
    a3 = 83;
    t0 = 0;
    jal(ctx, 0x3FCA48u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a0 = 0;
    a1 = 0;
    a3 = 84;
    t0 = 0;
    jal(ctx, 0x3FCA68u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a0 = 0;
    a1 = 0;
    a3 = 80;
    t0 = 0;
    jal(ctx, 0x3FCA88u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a0 = 0;
    a1 = 0;
    a3 = 81;
    t0 = 0;
    jal(ctx, 0x3FCAA8u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003FCBE0 sub_3FCBE0 -- 468 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopDrawCategoryRowA] A category row drawer (a2 = alpha, 0 draws nothing; a3 -> the list, t0 -> the row): on the
// cursor row the highlight 95 and a -2 lift; sprites 89 90; the category icon 85 + c with c = (row category & 0xF00) >> 8;
// then c 2 -> 94, 1 -> 93, 0 -> 91 92 (3: none).
void sub_3FCBE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003fcbe0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = 0;
    if (s2 != 0) {
        // 0x003fcc18
        charge(ctx, 5);
        lw(v0, t0, node::kPayload);
        lw(s0, v0, 28);
        lw(v0, a3, lst::kCursor);
        if (t0 == v0) {
            // 0x003fcc2c: the cursor row: highlight
            charge(ctx, 7);
            s1 = 1;
            mtc1(zero, f12);
            a2 = s2 & 0xFF;
            a3 = 95;
            t0 = 0;
            jal(ctx, 0x3FCC40u, gen::fn_sub_40E3C0_0040e3c0);
        }
        // 0x003fcc48
        charge(ctx, 35);
        v0 = sll(s1, 1);
        s5 = subu(0, v0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s4;
        a1 = s3;
        a3 = 89;
        t0 = s5;
        jal(ctx, 0x3FCC68u, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s4;
        a1 = s3;
        a3 = 90;
        t0 = s5;
        jal(ctx, 0x3FCC88u, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        lw(v0, s0, srow::kItemCategory);
        v0 = v0 & 0xF00;
        v0 = sra(v0, 8);
        a3 = addiu(v0, 85);
        a0 = s4;
        a1 = s3;
        t0 = s1;
        jal(ctx, 0x3FCCB4u, gen::fn_sub_40E3C0_0040e3c0);
        lw(v1, s0, srow::kItemCategory);
        v1 = v1 & 0xF00;
        a0 = sra(v1, 8);
        v1 = 3;
        if (a0 != v1) {
            // 0x003fccd4
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                // 0x003fcd6c
                charge(ctx, 8);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 94;
                t0 = s1;
                jal(ctx, 0x3FCD84u, gen::fn_sub_40E3C0_0040e3c0);
            } else {
                // 0x003fcce0
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    // 0x003fcd44
                    charge(ctx, 10);
                    mtc1(zero, f12);
                    a2 = s2 & 0xFF;
                    a0 = s4;
                    a1 = s3;
                    a3 = 93;
                    t0 = s1;
                    jal(ctx, 0x3FCD5Cu, gen::fn_sub_40E3C0_0040e3c0);
                } else {
                    // 0x003fccec
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x003fccfc
                        charge(ctx, 18);
                        mtc1(zero, f12);
                        a2 = s2 & 0xFF;
                        a0 = s4;
                        a1 = s3;
                        a3 = 91;
                        t0 = s1;
                        jal(ctx, 0x3FCD14u, gen::fn_sub_40E3C0_0040e3c0);
                        mtc1(zero, f12);
                        a2 = s2 & 0xFF;
                        a0 = s4;
                        a1 = s3;
                        a3 = 92;
                        t0 = s1;
                        jal(ctx, 0x3FCD34u, gen::fn_sub_40E3C0_0040e3c0);
                    } else {
                        // 0x003fccf4
                        charge(ctx, 2);
                    }
                }
            }
        }
    }
    // 0x003fcd8c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003FD140 sub_3FD140 -- 476 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopDrawCategoryRowB] sub_3FCBE0 with the highlight 83, sprites 77 78, the icon 73 + c and 82 / 81 / 79 80 drawn with
// 1 - lift.
void sub_3FD140(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003fd140
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = 0;
    if (s2 != 0) {
        // 0x003fd178
        charge(ctx, 5);
        lw(v0, t0, node::kPayload);
        lw(s0, v0, 28);
        lw(v0, a3, lst::kCursor);
        if (t0 == v0) {
            // 0x003fd18c: the cursor row: highlight
            charge(ctx, 7);
            s1 = 1;
            mtc1(zero, f12);
            a2 = s2 & 0xFF;
            a3 = 83;
            t0 = 0;
            jal(ctx, 0x3FD1A0u, gen::fn_sub_40E3C0_0040e3c0);
        }
        // 0x003fd1a8
        charge(ctx, 35);
        v0 = sll(s1, 1);
        s5 = subu(0, v0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s4;
        a1 = s3;
        a3 = 77;
        t0 = s5;
        jal(ctx, 0x3FD1C8u, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        a0 = s4;
        a1 = s3;
        a3 = 78;
        t0 = s5;
        jal(ctx, 0x3FD1E8u, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        lw(v0, s0, srow::kItemCategory);
        v0 = v0 & 0xF00;
        v0 = sra(v0, 8);
        a3 = addiu(v0, 73);
        a0 = s4;
        a1 = s3;
        t0 = s1;
        jal(ctx, 0x3FD214u, gen::fn_sub_40E3C0_0040e3c0);
        lw(v1, s0, srow::kItemCategory);
        v1 = v1 & 0xF00;
        a0 = sra(v1, 8);
        v1 = 3;
        if (a0 != v1) {
            // 0x003fd234
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                // 0x003fd2d0
                charge(ctx, 9);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                v0 = 1;
                t0 = subu(v0, s1);
                a0 = s4;
                a1 = s3;
                a3 = 82;
                jal(ctx, 0x3FD2ECu, gen::fn_sub_40E3C0_0040e3c0);
            } else {
                // 0x003fd240
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    // 0x003fd2a8
                    charge(ctx, 10);
                    mtc1(zero, f12);
                    a2 = s2 & 0xFF;
                    t0 = subu(v1, s1);
                    a0 = s4;
                    a1 = s3;
                    a3 = 81;
                    jal(ctx, 0x3FD2C0u, gen::fn_sub_40E3C0_0040e3c0);
                } else {
                    // 0x003fd24c
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x003fd25c
                        charge(ctx, 19);
                        s0 = subu(v1, s1);
                        mtc1(zero, f12);
                        a2 = s2 & 0xFF;
                        a0 = s4;
                        a1 = s3;
                        a3 = 79;
                        t0 = s0;
                        jal(ctx, 0x3FD278u, gen::fn_sub_40E3C0_0040e3c0);
                        mtc1(zero, f12);
                        a2 = s2 & 0xFF;
                        a0 = s4;
                        a1 = s3;
                        a3 = 80;
                        t0 = s0;
                        jal(ctx, 0x3FD298u, gen::fn_sub_40E3C0_0040e3c0);
                    } else {
                        // 0x003fd254
                        charge(ctx, 2);
                    }
                }
            }
        }
    }
    // 0x003fd2f4 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003FD7E0 sub_3FD7E0 -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopFreeCategoryRow] Row-removed callback of the category list: frees the row's element set (+8) and destroys its
// sub-list (+4). Returns 0.
void sub_3FD7E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fd7e0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, node::kPayload);
    lw(a0, s0, cat::kElems);
    jal(ctx, 0x3FD7F4u, gen::fn_sub_3DFF00_003dff00);
    lw(a0, s0, cat::kList);
    jal(ctx, 0x3FD800u, gen::fn_nmCmdListDestroy_003c5a20);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003FD8E0 sub_3FD8E0 -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopOpenCategories] Opens the cursor category's sub-list and starts the animations: the categories work a0 (+0 the
// category list, +8 the window element set): sub-list open (sub_3C6EE0), the window elements 0 and 3 in, the row's
// elements part 1 in with delay 5, the open sound (kind 3).
void sub_3FD8E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fd8e0
    enter(ctx, 41);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, a0, catw::kList);
    lw(v0, v0, 12);
    lw(s0, v0, 20);
    lw(a0, s0, cat::kList);
    jal(ctx, 0x3FD904u, gen::fn_sub_3C6EE0_003c6ee0);
    lw(a0, s1, catw::kElems);
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x3FD91Cu, gen::fn_sub_3E04E0_003e04e0);
    lw(a0, s1, catw::kElems);
    a1 = 3;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x3FD934u, gen::fn_sub_3E04E0_003e04e0);
    lw(a0, s0, cat::kElems);
    a1 = 1;
    a2 = 0;
    a3 = 5;
    jal(ctx, 0x3FD94Cu, gen::fn_sub_3E04E0_003e04e0);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 3;
    jal(ctx, 0x3FD964u, gen::fn_sub_10A4E0_0010a4e0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003FD990 sub_3FD990 -- 804 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopUpdateCategories] One frame of the category lists (the BUY update): steps the window elements, every category's
// sub-list (sub_3FE1F0) and elements; while the cursor sub-list takes input (status bit 30): L1 (0x7E0952 / 0x7E095A bit 4)
// / R1 (bit 8) move to the previous / next category -- sound 5, the old sub-list closes with its elements out, the new one
// opens at the same row (nmListCursorSeek) --; the button 0x20 (0x7E094E / 0x7E0958) closes every sub-list with sound 4
// and the window elements out and returns 1. Else 0.
void sub_3FD990(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fd990
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    lw(s3, a0, 0);
    s2 = 0;
    lw(a0, a0, 8);
    jal(ctx, 0x3FD9BCu, gen::fn_sub_3E0650_003e0650);
    lw(v0, s4, catw::kList);
    lw(s1, v0, 4);
    for (;;) {
        // 0x003fd9f4
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003fd9d4
        charge(ctx, 8);
        lw(s0, s1, node::kPayload);
        lw(a0, s0, cat::kList);
        jal(ctx, 0x3FD9DCu, gen::fn_sub_3FE1F0_003fe1f0);
        lw(a0, s0, cat::kElems);
        jal(ctx, 0x3FD9E8u, gen::fn_sub_3E0650_003e0650);
        lw(s1, s1, node::kNext);
    }
    // 0x003fd9fc
    charge(ctx, 9);
    lw(s1, s3, lst::kCursor);
    lw(s0, s1, 20);
    lw(a0, s0, cat::kList);
    jal(ctx, 0x3FDA08u, gen::fn_nmCmdListStatus_003c6d80);
    v1 = 0x40000000;
    v0 = v0 & v1;
    if (v0 != 0) {
        // 0x003fda20: the sub-list takes input
        charge(ctx, 5);
        v0 = 0x7E0000;
        lhu(a0, v0, 2386);  // 0x7E0952
        v0 = a0 & 0x4;
        if (v0 == 0) {
            // 0x003fda34
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, 2394);  // 0x7E095A
            v0 = v1 & 0x4;
            if (v0 != 0) {
                goto L_003fda48;
            }
            // 0x003fdaf4
            charge(ctx, 3);
            v0 = a0 & 0x8;
            if (v0 == 0) {
                // 0x003fdb00
                charge(ctx, 3);
                v0 = v1 & 0x8;
                if (v0 != 0) {
                    goto L_003fdb0c;
                }
                // 0x003fdbb8
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v0, v0, 2382);  // gPadFlags
                v0 = v0 & 0x20;
                if (v0 == 0) {
                    // 0x003fdbcc: cancel: close everything
                    charge(ctx, 5);
                    v0 = 0x7E0000;
                    lhu(v0, v0, 2392);  // 0x7E0958
                    v0 = v0 & 0x20;
                    if (v0 != 0) {
                        goto L_003fdbe0;
                    }
                    goto L_003fdc7c;
                }
            L_003fdbe0:
                charge(ctx, 10);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 4;
                jal(ctx, 0x3FDBF0u, gen::fn_sub_10A4E0_0010a4e0);
                lw(v0, s4, catw::kList);
                lw(s0, v0, 4);
                for (;;) {
                    // 0x003fdc1c
                    charge(ctx, 3);
                    if (s0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003fdc08
                    charge(ctx, 5);
                    lw(v0, s0, 20);
                    lw(a0, v0, 4);
                    jal(ctx, 0x3FDC10u, gen::fn_nmCmdListClose_003c6f10);
                    lw(s0, s0, 16);
                }
                // 0x003fdc28
                charge(ctx, 21);
                s2 = 1;
                lw(v0, s3, lst::kCursor);
                lw(v0, v0, 20);
                lw(a0, v0, 8);
                a1 = s2;
                a2 = s2;
                a3 = 0;
                jal(ctx, 0x3FDC44u, gen::fn_sub_3E04E0_003e04e0);
                lw(a0, s4, catw::kElems);
                a1 = 0;
                a2 = s2;
                a3 = 0;
                jal(ctx, 0x3FDC5Cu, gen::fn_sub_3E04E0_003e04e0);
                lw(a0, s4, catw::kElems);
                a1 = 3;
                a2 = s2;
                a3 = 0;
                jal(ctx, 0x3FDC74u, gen::fn_sub_3E04E0_003e04e0);
                goto L_003fdc7c;
            }
        L_003fdb0c:
            charge(ctx, 6);
            a0 = s3;
            a1 = addiu(s3, 4);
            jal(ctx, 0x3FDB14u, gen::fn_nmListCursorNext_003c4c80);
            if (s1 != v0) {
                // 0x003fdb24: R1: the next category
                charge(ctx, 37);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 5;
                jal(ctx, 0x3FDB34u, gen::fn_sub_10A4E0_0010a4e0);
                lw(a0, s0, 4);
                jal(ctx, 0x3FDB40u, gen::fn_nmCmdListClose_003c6f10);
                lw(a0, s0, 8);
                a1 = 1;
                a2 = a1;
                a3 = 0;
                jal(ctx, 0x3FDB58u, gen::fn_sub_3E04E0_003e04e0);
                lw(v0, s0, 4);
                lw(v0, v0, 12);
                lw(v0, v0, 0);
                s1 = addiu(v0, -1);
                lw(v0, s3, lst::kCursor);
                lw(s0, v0, 20);
                lw(a0, s0, 8);
                a1 = 1;
                a2 = 0;
                a3 = 5;
                jal(ctx, 0x3FDB88u, gen::fn_sub_3E04E0_003e04e0);
                lw(a0, s0, 4);
                jal(ctx, 0x3FDB94u, gen::fn_sub_3C6EE0_003c6ee0);
                lw(a0, s0, 4);
                a1 = addiu(a0, 4);
                a2 = s1;
                jal(ctx, 0x3FDBA8u, gen::fn_nmListCursorSeek_003c4df0);
            }
            goto L_003fdc7c;
        }
    L_003fda48:
        charge(ctx, 6);
        a0 = s3;
        a1 = addiu(s3, 4);
        jal(ctx, 0x3FDA50u, gen::fn_nmListCursorPrev_003c4d20);
        if (s1 != v0) {
            // 0x003fda60: L1: the previous category
            charge(ctx, 37);
            a0 = 0;
            a1 = 0;
            a2 = 0;
            a3 = 5;
            jal(ctx, 0x3FDA70u, gen::fn_sub_10A4E0_0010a4e0);
            lw(a0, s0, 4);
            jal(ctx, 0x3FDA7Cu, gen::fn_nmCmdListClose_003c6f10);
            lw(a0, s0, 8);
            a1 = 1;
            a2 = a1;
            a3 = 0;
            jal(ctx, 0x3FDA94u, gen::fn_sub_3E04E0_003e04e0);
            lw(v0, s0, 4);
            lw(v0, v0, 12);
            lw(v0, v0, 0);
            s1 = addiu(v0, -1);
            lw(v0, s3, lst::kCursor);
            lw(s0, v0, 20);
            lw(a0, s0, 8);
            a1 = 1;
            a2 = 0;
            a3 = 5;
            jal(ctx, 0x3FDAC4u, gen::fn_sub_3E04E0_003e04e0);
            lw(a0, s0, 4);
            jal(ctx, 0x3FDAD0u, gen::fn_sub_3C6EE0_003c6ee0);
            lw(a0, s0, 4);
            a1 = addiu(a0, 4);
            a2 = s1;
            jal(ctx, 0x3FDAE4u, gen::fn_nmListCursorSeek_003c4df0);
        }
    L_003fdc7c:
        charge(ctx, 4);
        a0 = s3;
        a1 = addiu(s3, 4);
        jal(ctx, 0x3FDC84u, gen::fn_nmListCursorClearEnd_003c4dc0);
    }
    // 0x003fdc8c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = s2;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003FE1F0 sub_3FE1F0 -- 192 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopUpdateCategoryList]
// Steps the command list a0 (nmCmdListUpdate) and plays the cursor sounds: kind 0 when the cursor moved down or scrolled
// (nmCmdListMovedDownRow / nmCmdListScrolledRow), kind 5 when it paged down or moved up. Returns 1 when the update
// returned 3, else 0.
void sub_3FE1F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fe1f0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x3FE204u, gen::fn_nmCmdListUpdate_003c6270);
    v0 = v0 ^ 0x3;
    s0 = sltiu(v0, 1);
    a0 = s1;
    jal(ctx, 0x3FE218u, gen::fn_nmCmdListMovedDownRow_003c6ce0);
    if (v0 == 0) {
        // 0x003fe228
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x3FE22Cu, gen::fn_nmCmdListScrolledRow_003c6d10);
        if (v0 != 0) {
            goto L_003fe23c;
        }
        goto L_003fe254;
    }
L_003fe23c:
    charge(ctx, 6);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x3FE24Cu, gen::fn_sub_10A4E0_0010a4e0);
L_003fe254:
    charge(ctx, 5);
    a0 = s1;
    jal(ctx, 0x3FE258u, gen::fn_nmCmdListPagedDown_003c6ca0);
    if (v0 == 0) {
        // 0x003fe268
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x3FE26Cu, gen::fn_nmCmdListMovedUp_003c6cc0);
        if (v0 != 0) {
            goto L_003fe27c;
        }
        // 0x003fe294 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        v0 = s0;
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_003fe27c:
    charge(ctx, 6);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 5;
    jal(ctx, 0x3FE28Cu, gen::fn_sub_10A4E0_0010a4e0);
    // 0x003fe294 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003FE3E0 sub_3FE3E0 -- 484 bytes; frame 0x70: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopBuildFusionItemList] ARMSCOMBINE: builds the base-item list for shop type a0 -- a command list (88-byte user
// area, 7 rows, spacing 26) with the user's shop type and mode -4; for each of the eight base items of table 0x6AF180
// (4018, 4069..4075) that sub_3F2240 accepts (it fills the 28-byte entry on the stack), a row with that entry (and a walk
// of the persona stock, sub_174A90 for each slot, whose results are unused); sub_3F99D0(list, 0xFF00), open, the callbacks
// (update sub_3FADC0, draw sub_3F4DE0, row draw sub_3F9510), position (57, 72), fade 11 / 6. Returns the list.
void sub_3FE3E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fe3e0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0;
    a1 = 88;
    a2 = 7;
    a3 = 26;
    jal(ctx, 0x3FE408u, gen::fn_sub_3C58F0_003c58f0);
    s1 = v0;
    lw(v0, v0, 36);
    lw(v1, v0, 68);
    sh(s0, v1, menu::kShopType);
    v0 = si(-4);
    sh(v0, v1, menu::kMode);
    s0 = 0;
    for (;;) {
        // 0x003fe4bc
        charge(ctx, 4);
        a2 = 0x6B0000;
        a2 = addiu(a2, -3712);  // &0x6AF180
        a1 = addiu(sp, 0x40);
        a0 = 4;
        for (;;) {
            // 0x003fe4cc
            charge(ctx, 9);
            lh(v1, a2, 0);
            lh(v0, a2, 2);
            a2 = addiu(a2, 4);
            a0 = addiu(a0, -1);
            sh(v1, a1, 0);
            sh(v0, a1, 2);
            a1 = addiu(a1, 4);
            if (i64(a0) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x003fe4f0
        charge(ctx, 3);
        v0 = sltiu(s0, 8);
        if (v0 != 0) {
            // 0x003fe508
            charge(ctx, 3);
            v0 = sll(s0, 1);
            v0 = addu(v0, sp);
            lhu(v0, v0, 64);
        } else {
            // 0x003fe4fc
            charge(ctx, 3);
            v0 = 0;
        }
        // 0x003fe514
        charge(ctx, 3);
        a1 = v0 & 0xFFFF;
        if (a1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003fe434: a base item: accepted?
        charge(ctx, 5);
        a0 = addiu(sp, 0x50);
        jal(ctx, 0x3FE438u, gen::fn_sub_3F2240_003f2240);
        if (v0 != 0) {
            // 0x003fe448: add its row
            charge(ctx, 17);
            lhu(v0, s1, lst::kCount);
            a1 = addiu(v0, 1);
            a0 = s1;
            a2 = 32;
            a3 = 0;
            jal(ctx, 0x3FE45Cu, gen::fn_nmCmdListAddRow_003c5a40);
            lw(v0, v0, 20);
            lw(v0, v0, 28);
            a0 = addiu(v0, 4);
            a1 = addiu(sp, 0x50);
            a2 = 28;
            jal(ctx, 0x3FE478u, gen::fn_memcpy_00521250);
            s2 = 0;
            for (;;) {
                // 0x003fe4a0
                charge(ctx, 6);
                jal(ctx, 0x3FE4A0u, gen::fn_sub_175410_00175410);
                v0 = v0 & 0xFFFF;
                v0 = slt(s2, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003fe48c
                charge(ctx, 5);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x3FE494u, gen::fn_sub_174A90_00174a90);
                s2 = addiu(s2, 1);
            }
        }
        // 0x003fe4b8
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x003fe520
    charge(ctx, 41);
    a0 = s1;
    a1 = 0xFF00;
    jal(ctx, 0x3FE528u, gen::fn_sub_3F99D0_003f99d0);
    a0 = s1;
    jal(ctx, 0x3FE534u, gen::fn_sub_3C6EE0_003c6ee0);
    a0 = s1;
    a1 = 0x400000;
    a1 = addiu(a1, -21056);  // &sub_3FADC0
    jal(ctx, 0x3FE548u, gen::fn_nmCmdListSetUpdateFunc_003c5e80);
    a0 = s1;
    a1 = 0x3F0000;
    a1 = addiu(a1, 19936);  // &sub_3F4DE0
    jal(ctx, 0x3FE55Cu, gen::fn_nmCmdListSetDrawFunc_003c5e20);
    a0 = s1;
    a1 = 0x400000;
    a1 = addiu(a1, -27376);  // &sub_3F9510
    jal(ctx, 0x3FE570u, gen::fn_nmCmdListSetRowDrawFunc_003c5ee0);
    a0 = s1;
    a1 = 57;
    a2 = 72;
    jal(ctx, 0x3FE584u, gen::fn_nmCmdListSetPosition_003c6d40);
    v1 = 11;
    lw(v0, s1, lst::kState);
    sh(v1, v0, 6);
    v1 = 6;
    lw(v0, s1, lst::kState);
    sh(v1, v0, 8);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003FE5D0 sub_3FE5D0 -- 192 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopUpdateFusionItems]
// Steps the command list a0 (nmCmdListUpdate) and plays the cursor sounds: kind 0 when the cursor moved down or scrolled
// (nmCmdListMovedDownRow / nmCmdListScrolledRow), kind 5 when it paged down or moved up. Returns 1 when the update
// returned 3, else 0.
void sub_3FE5D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fe5d0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x3FE5E4u, gen::fn_nmCmdListUpdate_003c6270);
    v0 = v0 ^ 0x3;
    s0 = sltiu(v0, 1);
    a0 = s1;
    jal(ctx, 0x3FE5F8u, gen::fn_nmCmdListMovedDownRow_003c6ce0);
    if (v0 == 0) {
        // 0x003fe608
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x3FE60Cu, gen::fn_nmCmdListScrolledRow_003c6d10);
        if (v0 != 0) {
            goto L_003fe61c;
        }
        goto L_003fe634;
    }
L_003fe61c:
    charge(ctx, 6);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x3FE62Cu, gen::fn_sub_10A4E0_0010a4e0);
L_003fe634:
    charge(ctx, 5);
    a0 = s1;
    jal(ctx, 0x3FE638u, gen::fn_nmCmdListPagedDown_003c6ca0);
    if (v0 == 0) {
        // 0x003fe648
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x3FE64Cu, gen::fn_nmCmdListMovedUp_003c6cc0);
        if (v0 != 0) {
            goto L_003fe65c;
        }
        // 0x003fe674 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        v0 = s0;
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_003fe65c:
    charge(ctx, 6);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 5;
    jal(ctx, 0x3FE66Cu, gen::fn_sub_10A4E0_0010a4e0);
    // 0x003fe674 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003FE690 sub_3FE690 -- 316 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopAddFusionPersonas] ARMSCOMBINE: adds a row per stock persona to list a0 for the base item entry a1: the row's
// item entry is a copy of a1, +20 the persona; when the persona makes an item from it (sub_401A00) +24 is that item's
// category and +28 the item, else both 0; sub_3FE7D0 sets the row flags. Returns 0.
void sub_3FE690(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fe690
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    s2 = 0;
    for (;;) {
        // 0x003fe788
        charge(ctx, 6);
        jal(ctx, 0x3FE788u, gen::fn_sub_175410_00175410);
        v0 = v0 & 0xFFFF;
        v0 = slt(s2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003fe6c4
        charge(ctx, 7);
        a0 = dsll32(s2, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x3FE6CCu, gen::fn_sub_174A90_00174a90);
        s1 = v0;
        if (v0 != 0) {
            // 0x003fe6e0: a persona: add its row
            charge(ctx, 23);
            lhu(v0, s5, lst::kCount);
            a1 = addiu(v0, 1);
            a0 = s5;
            a2 = 32;
            a3 = 0;
            jal(ctx, 0x3FE6F4u, gen::fn_nmCmdListAddRow_003c5a40);
            s3 = v0;
            lw(v0, v0, 20);
            lw(s0, v0, 28);
            a0 = addiu(s0, 4);
            a1 = s4;
            a2 = 28;
            jal(ctx, 0x3FE714u, gen::fn_memcpy_00521250);
            sw(s1, s0, srow::kMat1);
            lh(a0, s4, item::kId);
            a1 = s1;
            a2 = addiu(sp, 0x7E);
            jal(ctx, 0x3FE72Cu, gen::fn_sub_401A00_00401a00);
            if (v0 == 0) {
                // 0x003fe76c: no result
                charge(ctx, 2);
                sw(zero, s0, srow::kMat2);
                sh(zero, s0, srow::kResult);
            } else {
                // 0x003fe73c: it makes an item
                charge(ctx, 12);
                lh(a0, sp, 0x7E);
                a1 = addiu(sp, 0x78);
                jal(ctx, 0x3FE744u, gen::fn_sub_170ED0_00170ed0);
                lw(a0, v0, 4);
                jal(ctx, 0x3FE750u, gen::fn_sub_3F1A10_003f1a10);
                sw(v0, s0, srow::kMat2);
                lh(v0, sp, 0x7E);
                sh(v0, s0, srow::kResult);
            }
            // 0x003fe774
            charge(ctx, 4);
            a0 = s5;
            a1 = s3;
            jal(ctx, 0x3FE77Cu, gen::fn_sub_3FE7D0_003fe7d0);
        }
        // 0x003fe784
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x003fe7a0
    charge(ctx, 11);
    v0 = 0;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x003FE7D0 sub_3FE7D0 -- 116 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopFusionPersonaFlags] A weapon-fusion persona row's flags: 0x10 when it makes nothing (+28 = 0), 0x40 when it is
// the current persona (its id == sub_1752B0()). Returns 0.
void sub_3FE7D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fe7d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a1, node::kPayload);
    lw(s0, v0, 28);
    lh(v0, s0, srow::kResult);
    if (v0 == 0) {
        // 0x003fe7f4
        charge(ctx, 3);
        lw(v0, s0, srow::kFlags);
        v0 = v0 | 0x10;
        sw(v0, s0, srow::kFlags);
    }
    // 0x003fe800
    charge(ctx, 7);
    lw(v0, s0, srow::kMat1);
    lhu(s1, v0, 2);
    jal(ctx, 0x3FE808u, gen::fn_sub_1752B0_001752b0);
    v0 = v0 & 0xFFFF;
    if (s1 == v0) {
        // 0x003fe81c
        charge(ctx, 3);
        lw(v0, s0, srow::kFlags);
        v0 = v0 | 0x40;
        sw(v0, s0, srow::kFlags);
    }
    // 0x003fe828 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003FE850 sub_3FE850 -- 244 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopBuildFusionPersonaList] ARMSCOMBINE: the persona list for shop type a0 and the base item entry a1 -- a command list
// (88 bytes, 6 rows, spacing 30) with mode -5, the rows of sub_3FE690, open, the callbacks of sub_3FE3E0, position (25, 121),
// fade 11 / 6. Returns the list.
void sub_3FE850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fe850
    enter(ctx, 61);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 0;
    a1 = 88;
    a2 = 6;
    a3 = 30;
    jal(ctx, 0x3FE87Cu, gen::fn_sub_3C58F0_003c58f0);
    s0 = v0;
    lw(v0, v0, 36);
    lw(v1, v0, 68);
    sh(s2, v1, menu::kShopType);
    v0 = si(-5);
    sh(v0, v1, menu::kMode);
    a0 = s0;
    a1 = s1;
    a2 = 0;
    jal(ctx, 0x3FE8A8u, gen::fn_sub_3FE690_003fe690);
    a0 = s0;
    jal(ctx, 0x3FE8B4u, gen::fn_sub_3C6EE0_003c6ee0);
    a0 = s0;
    a1 = 0x400000;
    a1 = addiu(a1, -21056);  // &sub_3FADC0
    jal(ctx, 0x3FE8C8u, gen::fn_nmCmdListSetUpdateFunc_003c5e80);
    a0 = s0;
    a1 = 0x3F0000;
    a1 = addiu(a1, 19936);  // &sub_3F4DE0
    jal(ctx, 0x3FE8DCu, gen::fn_nmCmdListSetDrawFunc_003c5e20);
    a0 = s0;
    a1 = 0x400000;
    a1 = addiu(a1, -27376);  // &sub_3F9510
    jal(ctx, 0x3FE8F0u, gen::fn_nmCmdListSetRowDrawFunc_003c5ee0);
    a0 = s0;
    a1 = 25;
    a2 = 121;
    jal(ctx, 0x3FE904u, gen::fn_nmCmdListSetPosition_003c6d40);
    v1 = 11;
    lw(v0, s0, lst::kState);
    sh(v1, v0, 6);
    v1 = 6;
    lw(v0, s0, lst::kState);
    sh(v1, v0, 8);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003FE950 sub_3FE950 -- 192 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopUpdateFusionPersonas]
// Steps the command list a0 (nmCmdListUpdate) and plays the cursor sounds: kind 0 when the cursor moved down or scrolled
// (nmCmdListMovedDownRow / nmCmdListScrolledRow), kind 5 when it paged down or moved up. Returns 1 when the update
// returned 3, else 0.
void sub_3FE950(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fe950
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x3FE964u, gen::fn_nmCmdListUpdate_003c6270);
    v0 = v0 ^ 0x3;
    s0 = sltiu(v0, 1);
    a0 = s1;
    jal(ctx, 0x3FE978u, gen::fn_nmCmdListMovedDownRow_003c6ce0);
    if (v0 == 0) {
        // 0x003fe988
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x3FE98Cu, gen::fn_nmCmdListScrolledRow_003c6d10);
        if (v0 != 0) {
            goto L_003fe99c;
        }
        goto L_003fe9b4;
    }
L_003fe99c:
    charge(ctx, 6);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x3FE9ACu, gen::fn_sub_10A4E0_0010a4e0);
L_003fe9b4:
    charge(ctx, 5);
    a0 = s1;
    jal(ctx, 0x3FE9B8u, gen::fn_nmCmdListPagedDown_003c6ca0);
    if (v0 == 0) {
        // 0x003fe9c8
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x3FE9CCu, gen::fn_nmCmdListMovedUp_003c6cc0);
        if (v0 != 0) {
            goto L_003fe9dc;
        }
        // 0x003fe9f4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        v0 = s0;
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_003fe9dc:
    charge(ctx, 6);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 5;
    jal(ctx, 0x3FE9ECu, gen::fn_sub_10A4E0_0010a4e0);
    // 0x003fe9f4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003FEA10 sub_3FEA10 -- 288 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopAddTradeTable] TRADE: adds the entries of table a1 {entries, count} (14-byte tent::) to list a0: an entry whose
// flag is 0 or set, with an item and a first material count, gets a row (node word +4 = the item, the item entry via
// sub_3F1BA0, the 14 material bytes at +20) and sub_3FEB30 sets its owned count and availability. Returns 0.
void sub_3FEA10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fea10
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    lw(s3, a1, 0);
    s2 = 0;
    for (;;) {
        // 0x003feaf0
        charge(ctx, 4);
        lw(v0, s4, ttab::kCount);
        v0 = slt(s2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003fea4c
        charge(ctx, 3);
        lh(a0, s3, tent::kFlag);
        if (a0 != 0) {
            // 0x003fea58
            charge(ctx, 5);
            jal(ctx, 0x3FEA58u, gen::fn_datGetFlag_0016f190);
            v1 = 1;
            if (v0 == v1) {
                goto L_003fea6c;
            }
            goto L_003feae8;
        }
    L_003fea6c:
        charge(ctx, 3);
        lh(s1, s3, tent::kItem);
        if (s1 != 0) {
            // 0x003fea78
            charge(ctx, 3);
            lh(v0, s3, tent::kMatCount);
            if (v0 != 0) {
                // 0x003fea84: add the row
                charge(ctx, 25);
                lhu(v0, s5, lst::kCount);
                a1 = addiu(v0, 1);
                a0 = s5;
                a2 = 32;
                a3 = 0;
                jal(ctx, 0x3FEA98u, gen::fn_nmCmdListAddRow_003c5a40);
                s6 = v0;
                sw(s1, v0, node::kWord4);
                lw(v0, v0, node::kPayload);
                lw(s0, v0, 28);
                a1 = dsll32(s1, 16);
                a1 = dsra32(a1, 16);
                a0 = addiu(s0, 4);
                jal(ctx, 0x3FEABCu, gen::fn_sub_3F1BA0_003f1ba0);
                a0 = addiu(s0, 20);
                a1 = addiu(s3, 6);
                a2 = 14;
                jal(ctx, 0x3FEAD0u, gen::fn_memcpy_00521250);
                a0 = s5;
                a1 = s6;
                jal(ctx, 0x3FEAE0u, gen::fn_sub_3FEB30_003feb30);
            }
        }
    L_003feae8:
        charge(ctx, 2);
        s3 = addiu(s3, 14);
        s2 = addiu(s2, 1);
    }
    // 0x003feb00
    charge(ctx, 12);
    v0 = 0;
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x003FEB30 sub_3FEB30 -- 784 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopTradeRowState] A TRADE row's owned count and availability: +14 = the owned count of its item (sub_3F1910's rule,
// inline); flag 0x10 when it is 99 or more, or when either material (+20 / +24, 0 = none) is held fewer times than its count
// (+22 / +26). A zero first count is K_Assert("fclShopMisc.c", 5560) (it continues). Returns 0.
void sub_3FEB30(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003feb30
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a1, node::kPayload);
    lw(s0, v0, 28);
    lh(s2, s0, srow::kItem);
    v0 = si(-1);
    sw(v0, sp, 0x5C);
    s3 = 0;
    a0 = s2;
    a1 = addiu(sp, 0x5C);
    jal(ctx, 0x3FEB68u, gen::fn_sub_170ED0_00170ed0);
    lw(v1, sp, 0x5C);
    v0 = 4;
    if (v1 == v0) {
        // 0x003fec00
        charge(ctx, 5);
        a0 = 1;
        a1 = s2;
        jal(ctx, 0x3FEC08u, gen::fn_sub_170760_00170760);
        s3 = v0 & 0xFFFF;
    } else {
        // 0x003feb80
        charge(ctx, 3);
        v0 = 3;
        if (v1 != v0) {
            // 0x003feb8c
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_003febb4;
            }
            // 0x003feb98
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_003febb4;
            }
            // 0x003feba4
            charge(ctx, 2);
            if (v1 == 0) {
                goto L_003febb4;
            }
            // 0x003febac
            charge(ctx, 2);
            goto L_003fec14;
        }
    L_003febb4:
        charge(ctx, 5);
        s1 = 0;
        s2 = dsll32(s2, 16);
        s2 = dsra32(s2, 16);
        for (;;) {
            // 0x003febec
            charge(ctx, 3);
            v0 = slti(s1, 300);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003febc8
            charge(ctx, 7);
            a0 = 1;
            a1 = s1;
            jal(ctx, 0x3FEBD0u, gen::fn_sub_16F630_0016f630);
            v0 = v0 & 0xFFFF;
            if (s2 == v0) {
                // 0x003febe4
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
            // 0x003febe8
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
        // 0x003febf8
        charge(ctx, 2);
    }
L_003fec14:
    charge(ctx, 6);
    sh(s3, s0, srow::kOwned);
    v0 = dsll32(s3, 16);
    v0 = dsra32(v0, 16);
    v0 = slti(v0, 99);
    if (v0 == 0) {
        // 0x003fec2c: 99 owned: unavailable
        charge(ctx, 3);
        lw(v0, s0, srow::kFlags);
        v0 = v0 | 0x10;
        sw(v0, s0, srow::kFlags);
    }
    // 0x003fec38
    charge(ctx, 3);
    lh(v0, s0, srow::kMat1Count);
    if (v0 == 0) {
        // 0x003fec44: no material count: K_Assert (retail continues)
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 5560;
        jal(ctx, 0x3FEC50u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003fec58: the first material
    charge(ctx, 3);
    lh(s1, s0, srow::kMat1);
    if (s1 != 0) {
        // 0x003fec64
        charge(ctx, 11);
        v0 = si(-1);
        sw(v0, sp, 0x58);
        s3 = 0;
        a0 = s1;
        a1 = addiu(sp, 0x58);
        jal(ctx, 0x3FEC78u, gen::fn_sub_170ED0_00170ed0);
        lw(v1, sp, 0x58);
        v0 = 4;
        if (v1 == v0) {
            // 0x003fed10
            charge(ctx, 5);
            a0 = 1;
            a1 = s1;
            jal(ctx, 0x3FED18u, gen::fn_sub_170760_00170760);
            s3 = v0 & 0xFFFF;
        } else {
            // 0x003fec90
            charge(ctx, 3);
            v0 = 3;
            if (v1 != v0) {
                // 0x003fec9c
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    goto L_003fecc4;
                }
                // 0x003feca8
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    goto L_003fecc4;
                }
                // 0x003fecb4
                charge(ctx, 2);
                if (v1 == 0) {
                    goto L_003fecc4;
                }
                // 0x003fecbc
                charge(ctx, 2);
                goto L_003fed24;
            }
        L_003fecc4:
            charge(ctx, 5);
            s2 = 0;
            s1 = dsll32(s1, 16);
            s1 = dsra32(s1, 16);
            for (;;) {
                // 0x003fecfc
                charge(ctx, 3);
                v0 = slti(s2, 300);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003fecd8
                charge(ctx, 7);
                a0 = 1;
                a1 = s2;
                jal(ctx, 0x3FECE0u, gen::fn_sub_16F630_0016f630);
                v0 = v0 & 0xFFFF;
                if (s1 == v0) {
                    // 0x003fecf4
                    charge(ctx, 1);
                    s3 = addiu(s3, 1);
                }
                // 0x003fecf8
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x003fed08
            charge(ctx, 2);
        }
    L_003fed24:
        charge(ctx, 4);
        lh(v0, s0, srow::kMat1Count);
        v0 = slt(s3, v0);
        if (v0 == 0) {
            goto L_003fed34;
        }
    L_003fee10:
        charge(ctx, 3);
        lw(v0, s0, srow::kFlags);
        v0 = v0 | 0x10;
        sw(v0, s0, srow::kFlags);
        // 0x003fee1c (the shared epilogue, written out on this path)
        charge(ctx, 9);
        v0 = 0;
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x60);
        return;
    }
L_003fed34:
    charge(ctx, 3);
    lh(s1, s0, srow::kMat2);
    if (s1 != 0) {
        // 0x003fed40
        charge(ctx, 11);
        v0 = si(-1);
        sw(v0, sp, 0x54);
        s3 = 0;
        a0 = s1;
        a1 = addiu(sp, 0x54);
        jal(ctx, 0x3FED54u, gen::fn_sub_170ED0_00170ed0);
        lw(v1, sp, 0x54);
        v0 = 4;
        if (v1 == v0) {
            // 0x003fedec
            charge(ctx, 5);
            a0 = 1;
            a1 = s1;
            jal(ctx, 0x3FEDF4u, gen::fn_sub_170760_00170760);
            s3 = v0 & 0xFFFF;
        } else {
            // 0x003fed6c
            charge(ctx, 3);
            v0 = 3;
            if (v1 != v0) {
                // 0x003fed78
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    goto L_003feda0;
                }
                // 0x003fed84
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    goto L_003feda0;
                }
                // 0x003fed90
                charge(ctx, 2);
                if (v1 == 0) {
                    goto L_003feda0;
                }
                // 0x003fed98
                charge(ctx, 2);
                goto L_003fee00;
            }
        L_003feda0:
            charge(ctx, 5);
            s2 = 0;
            s1 = dsll32(s1, 16);
            s1 = dsra32(s1, 16);
            for (;;) {
                // 0x003fedd8
                charge(ctx, 3);
                v0 = slti(s2, 300);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003fedb4
                charge(ctx, 7);
                a0 = 1;
                a1 = s2;
                jal(ctx, 0x3FEDBCu, gen::fn_sub_16F630_0016f630);
                v0 = v0 & 0xFFFF;
                if (s1 == v0) {
                    // 0x003fedd0
                    charge(ctx, 1);
                    s3 = addiu(s3, 1);
                }
                // 0x003fedd4
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x003fede4
            charge(ctx, 2);
        }
    L_003fee00:
        charge(ctx, 4);
        lh(v0, s0, srow::kMat2Count);
        at = slt(s3, v0);
        if (at != 0) {
            goto L_003fee10;
        }
    }
    // 0x003fee1c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = 0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003FEE40 sub_3FEE40 -- 240 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopTradeRefresh] Recomputes every TRADE row of list a0 with sub_3F1910 (the same rule as sub_3FEB30). Returns 0.
void sub_3FEE40(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fee40
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, lst::kHead);
    for (;;) {
        // 0x003fef0c
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003fee5c
        charge(ctx, 11);
        lw(v0, s1, node::kPayload);
        lw(s0, v0, 28);
        lh(a0, s0, srow::kItem);
        jal(ctx, 0x3FEE68u, gen::fn_sub_3F1910_003f1910);
        sh(v0, s0, srow::kOwned);
        v0 = dsll32(v0, 16);
        v0 = dsra32(v0, 16);
        v0 = slti(v0, 99);
        if (v0 == 0) {
            // 0x003fee88
            charge(ctx, 3);
            lw(v0, s0, srow::kFlags);
            v0 = v0 | 0x10;
            sw(v0, s0, srow::kFlags);
        }
        // 0x003fee94
        charge(ctx, 3);
        lh(v0, s0, srow::kMat1Count);
        if (v0 == 0) {
            // 0x003feea0
            charge(ctx, 5);
            a0 = 0x6B0000;
            a0 = addiu(a0, -4632);  // "fclShopMisc.c"
            a1 = 5560;
            jal(ctx, 0x3FEEACu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x003feeb4
        charge(ctx, 3);
        lh(a0, s0, srow::kMat1);
        if (a0 != 0) {
            // 0x003feec0
            charge(ctx, 6);
            jal(ctx, 0x3FEEC0u, gen::fn_sub_3F1910_003f1910);
            lh(v1, s0, srow::kMat1Count);
            v0 = slt(v0, v1);
            if (v0 == 0) {
                goto L_003feed8;
            }
        L_003feefc:
            charge(ctx, 3);
            lw(v0, s0, srow::kFlags);
            v0 = v0 | 0x10;
            sw(v0, s0, srow::kFlags);
            goto L_003fef08;
        }
    L_003feed8:
        charge(ctx, 3);
        lh(a0, s0, srow::kMat2);
        if (a0 != 0) {
            // 0x003feee4
            charge(ctx, 6);
            jal(ctx, 0x3FEEE4u, gen::fn_sub_3F1910_003f1910);
            lh(v1, s0, srow::kMat2Count);
            at = slt(v0, v1);
            if (at != 0) {
                goto L_003feefc;
            }
        }
    L_003fef08:
        charge(ctx, 1);
        lw(s1, s1, node::kNext);
    }
    // 0x003fef14
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003FEF30 sub_3FEF30 -- 544 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopBuildTradeList] TRADE: the trade list for shop type a0 (a1 = 1 the trade-ins) -- a command list (88 bytes, 5 rows,
// spacing 26), mode -3 / -2, the base table off_6AD4A8 / off_6AD4A0 (sub_3FEA10); for the trades also the extra tables
// 1..sub_3F03E0(4) of off_6AD4B0 (8 bytes each; an index outside 0..count is K_Assert("fclShopMisc.c", 479)), then the rows
// new since the last visit are marked: sub_17D610(type), the old list sub_3FF150(type, 0), sub_3FF460 marks, the old list
// is destroyed. Open, the callbacks of sub_3FE3E0, position (57, 72), fade 10 / 5. Returns the list.
void sub_3FEF30(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fef30
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    a0 = 0;
    a1 = 88;
    a2 = 5;
    a3 = 26;
    jal(ctx, 0x3FEF68u, gen::fn_sub_3C58F0_003c58f0);
    s3 = v0;
    lw(v0, v0, 36);
    lw(v1, v0, 68);
    sh(s5, v1, menu::kShopType);
    s1 = 0x6B0000;
    s1 = addiu(s1, -11104);  // &0x6AD4A0
    if (s4 != 0) {
        // 0x003fefa4
        charge(ctx, 3);
        v0 = si(-3);
        sh(v0, v1, menu::kMode);
        s0 = addiu(s1, 8);
    } else {
        // 0x003fef90
        charge(ctx, 5);
        v0 = si(-2);
        sh(v0, v1, menu::kMode);
        s0 = s1;
    }
    // 0x003fefb0
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x003fefb8
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 5610;
        jal(ctx, 0x3FEFC4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003fefcc
    charge(ctx, 7);
    a0 = s3;
    a1 = s0;
    a2 = 0;
    jal(ctx, 0x3FEFD8u, gen::fn_sub_3FEA10_003fea10);
    if (s4 == 0) {
        // 0x003fefe8: the trades: the extra tables
        charge(ctx, 7);
        a0 = 4;
        jal(ctx, 0x3FEFECu, gen::fn_sub_3F03E0_003f03e0);
        s0 = v0;
        s2 = 1;
        for (;;) {
            // 0x003ff058
            charge(ctx, 3);
            at = slt(s0, s2);
            if (at != 0) {
                break;
            }
            backedge(ctx);
            // 0x003ff004
            charge(ctx, 2);
            if (i64(s2) >= 0) {
                // 0x003ff00c
                charge(ctx, 4);
                lw(v0, s1, 20);
                at = slt(v0, s2);
                if (at != 0) {
                    goto L_003ff01c;
                }
                goto L_003ff030;
            }
        L_003ff01c:
            charge(ctx, 5);
            a0 = 0x6B0000;
            a0 = addiu(a0, -4632);  // "fclShopMisc.c"
            a1 = 479;
            jal(ctx, 0x3FF028u, gen::fn_sub_19D3F0_0019d3f0);
        L_003ff030:
            charge(ctx, 5);
            v1 = sll(s2, 3);
            lw(v0, s1, 16);
            a1 = addu(v0, v1);
            if (a1 != 0) {
                // 0x003ff044
                charge(ctx, 4);
                a0 = s3;
                a2 = 0;
                jal(ctx, 0x3FF04Cu, gen::fn_sub_3FEA10_003fea10);
            }
            // 0x003ff054
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
    }
    // 0x003ff064
    charge(ctx, 2);
    if (s4 == 0) {
        // 0x003ff06c: mark the new rows
        charge(ctx, 10);
        a0 = s5;
        jal(ctx, 0x3FF070u, gen::fn_sub_17D610_0017d610);
        a0 = s5;
        a1 = s4;
        jal(ctx, 0x3FF080u, gen::fn_sub_3FF150_003ff150);
        s0 = v0;
        if (v0 != 0) {
            // 0x003ff094
            charge(ctx, 7);
            a0 = s3;
            a1 = s0;
            jal(ctx, 0x3FF09Cu, gen::fn_sub_3FF460_003ff460);
            a0 = s0;
            jal(ctx, 0x3FF0A8u, gen::fn_nmCmdListDestroy_003c5a20);
        }
    }
    // 0x003ff0b0
    charge(ctx, 40);
    a0 = s3;
    jal(ctx, 0x3FF0B4u, gen::fn_sub_3C6EE0_003c6ee0);
    a0 = s3;
    a1 = 0x400000;
    a1 = addiu(a1, -21056);  // &sub_3FADC0
    jal(ctx, 0x3FF0C8u, gen::fn_nmCmdListSetUpdateFunc_003c5e80);
    a0 = s3;
    a1 = 0x3F0000;
    a1 = addiu(a1, 19936);  // &sub_3F4DE0
    jal(ctx, 0x3FF0DCu, gen::fn_nmCmdListSetDrawFunc_003c5e20);
    a0 = s3;
    a1 = 0x400000;
    a1 = addiu(a1, -27376);  // &sub_3F9510
    jal(ctx, 0x3FF0F0u, gen::fn_nmCmdListSetRowDrawFunc_003c5ee0);
    a0 = s3;
    a1 = 57;
    a2 = 72;
    jal(ctx, 0x3FF104u, gen::fn_nmCmdListSetPosition_003c6d40);
    v1 = 10;
    lw(v0, s3, lst::kState);
    sh(v1, v0, 6);
    v1 = 5;
    lw(v0, s3, lst::kState);
    sh(v1, v0, 8);
    v0 = s3;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003FF150 sub_3FF150 -- 772 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopBuildOldTradeList] The trade list as it was at the last visit (for sub_3FF460): the progress mask of the 8 flags of
// table 0x6ACC60 is read (with flag 6 free on the 'AGS_' variant), the flags are set to the state sub_17D6D0 saved for shop
// type a0, the list is built as in sub_3FEF30 (asserts 5679 / 479), and the flags are put back. Returns the list.
void sub_3FF150(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ff150
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    a1 = addiu(sp, 0x68);
    jal(ctx, 0x3FF174u, gen::fn_sub_17D6D0_0017d6d0);
    s0 = 0;
    s1 = 0;
    for (;;) {
        // 0x003ff20c
        charge(ctx, 3);
        v0 = sltiu(s1, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003ff18c
        charge(ctx, 8);
        v1 = sll(s1, 1);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13216);  // &0x6ACC60
        v0 = addu(v0, v1);
        lh(a0, v0, 0);
        v0 = si(-1);
        if (a0 != v0) {
            // 0x003ff1ac
            charge(ctx, 4);
            jal(ctx, 0x3FF1ACu, gen::fn_datGetFlag_0016f190);
            if (v0 == 0) {
                goto L_003ff1d8;
            }
            // 0x003ff1bc
            charge(ctx, 7);
            v0 = 1;
            v0 = sllv(v0, s1);
            v0 = v0 & 0xFFFF;
            v0 = s0 | v0;
            s0 = v0 & 0xFFFF;
            goto L_003ff208;
        }
    L_003ff1d8:
        charge(ctx, 3);
        v0 = 6;
        if (s1 == v0) {
            // 0x003ff1e4
            charge(ctx, 4);
            jal(ctx, 0x3FF1E4u, gen::fn_sub_17D800_0017d800);
            if (v0 != 0) {
                // 0x003ff1f4
                charge(ctx, 5);
                v0 = 1;
                v0 = sllv(v0, s1);
                v0 = v0 & 0xFFFF;
                v0 = s0 | v0;
                s0 = v0 & 0xFFFF;
            }
        }
    L_003ff208:
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x003ff218
    charge(ctx, 4);
    lhu(s1, sp, 0x6A);
    s3 = 0;
    for (;;) {
        // 0x003ff298
        charge(ctx, 3);
        v0 = sltiu(s3, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003ff228
        charge(ctx, 3);
        v0 = 6;
        if (s3 == v0) {
            // 0x003ff234
            charge(ctx, 4);
            jal(ctx, 0x3FF234u, gen::fn_sub_17D800_0017d800);
            if (v0 == 0) {
                goto L_003ff244;
            }
            goto L_003ff294;
        }
    L_003ff244:
        charge(ctx, 8);
        v1 = sll(s3, 1);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13216);  // &0x6ACC60
        v0 = addu(v0, v1);
        lh(a0, v0, 0);
        v0 = si(-1);
        if (a0 != v0) {
            // 0x003ff264
            charge(ctx, 5);
            a1 = 1;
            v0 = sllv(a1, s3);
            v0 = s1 & v0;
            if (v0 == 0) {
                // 0x003ff288
                charge(ctx, 3);
                a1 = 0;
                jal(ctx, 0x3FF28Cu, gen::fn_datSetFlag_0016f1f0);
            } else {
                // 0x003ff278
                charge(ctx, 4);
                jal(ctx, 0x3FF278u, gen::fn_datSetFlag_0016f1f0);
            }
        }
    L_003ff294:
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x003ff2a4
    charge(ctx, 13);
    a0 = 0;
    a1 = 88;
    a2 = 5;
    a3 = 26;
    jal(ctx, 0x3FF2B4u, gen::fn_sub_3C58F0_003c58f0);
    s1 = v0;
    lw(v0, v0, 36);
    lw(v1, v0, 68);
    s3 = 0x6B0000;
    s3 = addiu(s3, -11104);  // &0x6AD4A0
    if (s2 != 0) {
        // 0x003ff2ec
        charge(ctx, 3);
        v0 = si(-3);
        sh(v0, v1, menu::kMode);
        s4 = addiu(s3, 8);
    } else {
        // 0x003ff2d8
        charge(ctx, 5);
        v0 = si(-2);
        sh(v0, v1, menu::kMode);
        s4 = s3;
    }
    // 0x003ff2f8
    charge(ctx, 2);
    if (s4 == 0) {
        // 0x003ff300
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 5679;
        jal(ctx, 0x3FF30Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003ff314
    charge(ctx, 7);
    a0 = s1;
    a1 = s4;
    a2 = 0;
    jal(ctx, 0x3FF320u, gen::fn_sub_3FEA10_003fea10);
    if (s2 == 0) {
        // 0x003ff330
        charge(ctx, 4);
        lbu(s2, sp, 0x69);
        s4 = 1;
        for (;;) {
            // 0x003ff394
            charge(ctx, 3);
            at = slt(s2, s4);
            if (at != 0) {
                break;
            }
            backedge(ctx);
            // 0x003ff340
            charge(ctx, 2);
            if (i64(s4) >= 0) {
                // 0x003ff348
                charge(ctx, 4);
                lw(v0, s3, 20);
                at = slt(v0, s4);
                if (at != 0) {
                    goto L_003ff358;
                }
                goto L_003ff36c;
            }
        L_003ff358:
            charge(ctx, 5);
            a0 = 0x6B0000;
            a0 = addiu(a0, -4632);  // "fclShopMisc.c"
            a1 = 479;
            jal(ctx, 0x3FF364u, gen::fn_sub_19D3F0_0019d3f0);
        L_003ff36c:
            charge(ctx, 5);
            v1 = sll(s4, 3);
            lw(v0, s3, 16);
            a1 = addu(v0, v1);
            if (a1 != 0) {
                // 0x003ff380
                charge(ctx, 4);
                a0 = s1;
                a2 = 0;
                jal(ctx, 0x3FF388u, gen::fn_sub_3FEA10_003fea10);
            }
            // 0x003ff390
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        }
    }
    // 0x003ff3a0
    charge(ctx, 4);
    s2 = 0;
    s0 = s0 & 0xFFFF;
    for (;;) {
        // 0x003ff420
        charge(ctx, 3);
        v0 = sltiu(s2, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003ff3b0
        charge(ctx, 3);
        v0 = 6;
        if (s2 == v0) {
            // 0x003ff3bc
            charge(ctx, 4);
            jal(ctx, 0x3FF3BCu, gen::fn_sub_17D800_0017d800);
            if (v0 == 0) {
                goto L_003ff3cc;
            }
            goto L_003ff41c;
        }
    L_003ff3cc:
        charge(ctx, 8);
        v1 = sll(s2, 1);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13216);  // &0x6ACC60
        v0 = addu(v0, v1);
        lh(a0, v0, 0);
        v0 = si(-1);
        if (a0 != v0) {
            // 0x003ff3ec
            charge(ctx, 5);
            a1 = 1;
            v0 = sllv(a1, s2);
            v0 = s0 & v0;
            if (v0 == 0) {
                // 0x003ff410
                charge(ctx, 3);
                a1 = 0;
                jal(ctx, 0x3FF414u, gen::fn_datSetFlag_0016f1f0);
            } else {
                // 0x003ff400
                charge(ctx, 4);
                jal(ctx, 0x3FF400u, gen::fn_datSetFlag_0016f1f0);
            }
        }
    L_003ff41c:
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x003ff42c
    charge(ctx, 10);
    v0 = s1;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003FF460 sub_3FF460 -- 268 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopMarkNewTrades] Marks the rows of list a0 that are new (no row with the item in the old list a1) or whose materials
// changed (+20..+26) with 0x80; matched rows are removed from a1.
void sub_3FF460(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ff460
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    lw(s1, a0, lst::kHead);
    for (;;) {
        // 0x003ff548
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003ff484
        charge(ctx, 10);
        lw(v0, s1, node::kPayload);
        lw(s0, v0, 28);
        lh(a2, s0, srow::kItem);
        a0 = s2;
        a1 = addiu(s2, 4);
        jal(ctx, 0x3FF498u, gen::fn_nmListFindByWord4_003c4bf0);
        a2 = v0;
        if (v0 == 0) {
            // 0x003ff538: new: 0x80
            charge(ctx, 3);
            lw(v1, s0, srow::kFlags);
            v1 = v1 | 0x80;
            sw(v1, s0, srow::kFlags);
        } else {
            // 0x003ff4ac
            charge(ctx, 8);
            lw(v0, a2, 20);
            lw(a0, v0, 28);
            lh(v1, s0, srow::kMat1Count);
            lh(v0, a0, srow::kMat1Count);
            v0 = v1 ^ v0;
            v0 = sltiu(v0, 1);
            if (v0 != 0) {
                // 0x003ff4cc
                charge(ctx, 4);
                lh(v1, s0, srow::kMat1);
                lh(v0, a0, srow::kMat1);
                v0 = v1 ^ v0;
                v0 = sltiu(v0, 1);
            }
            // 0x003ff4dc
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x003ff4e4
                charge(ctx, 4);
                lh(v1, s0, srow::kMat2Count);
                lh(v0, a0, srow::kMat2Count);
                v0 = v1 ^ v0;
                v0 = sltiu(v0, 1);
            }
            // 0x003ff4f4
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x003ff4fc
                charge(ctx, 4);
                lh(v1, s0, srow::kMat2);
                lh(v0, a0, srow::kMat2);
                v0 = v1 ^ v0;
                v0 = sltiu(v0, 1);
            }
            // 0x003ff50c
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x003ff514: changed: 0x80
                charge(ctx, 3);
                lw(v0, s0, srow::kFlags);
                v0 = v0 | 0x80;
                sw(v0, s0, srow::kFlags);
            }
            // 0x003ff520
            charge(ctx, 6);
            a0 = s2;
            a1 = addiu(s2, 4);
            jal(ctx, 0x3FF528u, gen::fn_sub_3C49E0_003c49e0);
        }
        // 0x003ff544
        charge(ctx, 1);
        lw(s1, s1, node::kNext);
    }
    // 0x003ff550
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003FF570 sub_3FF570 -- 192 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopUpdateTradeList]
// Steps the command list a0 (nmCmdListUpdate) and plays the cursor sounds: kind 0 when the cursor moved down or scrolled
// (nmCmdListMovedDownRow / nmCmdListScrolledRow), kind 5 when it paged down or moved up. Returns 1 when the update
// returned 3, else 0.
void sub_3FF570(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ff570
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x3FF584u, gen::fn_nmCmdListUpdate_003c6270);
    v0 = v0 ^ 0x3;
    s0 = sltiu(v0, 1);
    a0 = s1;
    jal(ctx, 0x3FF598u, gen::fn_nmCmdListMovedDownRow_003c6ce0);
    if (v0 == 0) {
        // 0x003ff5a8
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x3FF5ACu, gen::fn_nmCmdListScrolledRow_003c6d10);
        if (v0 != 0) {
            goto L_003ff5bc;
        }
        goto L_003ff5d4;
    }
L_003ff5bc:
    charge(ctx, 6);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x3FF5CCu, gen::fn_sub_10A4E0_0010a4e0);
L_003ff5d4:
    charge(ctx, 5);
    a0 = s1;
    jal(ctx, 0x3FF5D8u, gen::fn_nmCmdListPagedDown_003c6ca0);
    if (v0 == 0) {
        // 0x003ff5e8
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x3FF5ECu, gen::fn_nmCmdListMovedUp_003c6cc0);
        if (v0 != 0) {
            goto L_003ff5fc;
        }
        // 0x003ff614 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        v0 = s0;
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_003ff5fc:
    charge(ctx, 6);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 5;
    jal(ctx, 0x3FF60Cu, gen::fn_sub_10A4E0_0010a4e0);
    // 0x003ff614 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

}  // namespace p3fes::game
