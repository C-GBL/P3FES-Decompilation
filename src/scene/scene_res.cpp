// Slice scene (game/include/p3fes/game/scene.h has the formats and the records): resrcManager.c (the scene resource manager) and mt_scene.c (the scene record, the typed resource creators, delete, transforms).
// p3fes_handgen bodies (register for register, block for block as the recompiled ones) with a role comment per
// function and named offsets / globals (each constant equals the literal it replaces; tools check it).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/scene.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_FileExists_001008b0(p3fes::EEContext&);
void fn_K_Field_Get_001b9120(p3fes::EEContext&);
void fn_acosf_0052e9e8(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcat_00523e68(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1B3C90_001b3c90(p3fes::EEContext&);
void fn_sub_1E6AF0_001e6af0(p3fes::EEContext&);
void fn_sub_3174E0_003174e0(p3fes::EEContext&);
void fn_sub_318A30_00318a30(p3fes::EEContext&);
void fn_sub_318A50_00318a50(p3fes::EEContext&);
void fn_sub_318A90_00318a90(p3fes::EEContext&);
void fn_sub_318B70_00318b70(p3fes::EEContext&);
void fn_sub_34FCF0_0034fcf0(p3fes::EEContext&);
void fn_sub_34FE80_0034fe80(p3fes::EEContext&);
void fn_sub_3B4FC0_003b4fc0(p3fes::EEContext&);
void fn_sub_3B5020_003b5020(p3fes::EEContext&);
void fn_sub_3B50D0_003b50d0(p3fes::EEContext&);
void fn_sub_3B5360_003b5360(p3fes::EEContext&);
void fn_sub_3B5430_003b5430(p3fes::EEContext&);
void fn_sub_3B54C0_003b54c0(p3fes::EEContext&);
void fn_sub_3B5550_003b5550(p3fes::EEContext&);
void fn_sub_3B5620_003b5620(p3fes::EEContext&);
void fn_sub_3B58C0_003b58c0(p3fes::EEContext&);
void fn_sub_3B5980_003b5980(p3fes::EEContext&);
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);
void fn_sub_3B5E90_003b5e90(p3fes::EEContext&);
void fn_sub_3B5F70_003b5f70(p3fes::EEContext&);
void fn_sub_3B6180_003b6180(p3fes::EEContext&);
void fn_sub_3B63C0_003b63c0(p3fes::EEContext&);
void fn_sub_3B6440_003b6440(p3fes::EEContext&);
void fn_sub_3B66B0_003b66b0(p3fes::EEContext&);
void fn_sub_3B6790_003b6790(p3fes::EEContext&);
void fn_sub_3B6870_003b6870(p3fes::EEContext&);
void fn_sub_3B69A0_003b69a0(p3fes::EEContext&);
void fn_sub_3B6AD0_003b6ad0(p3fes::EEContext&);
void fn_sub_3B6B90_003b6b90(p3fes::EEContext&);
void fn_sub_3B6C50_003b6c50(p3fes::EEContext&);
void fn_sub_3B6D10_003b6d10(p3fes::EEContext&);
void fn_sub_3B6DD0_003b6dd0(p3fes::EEContext&);
void fn_sub_3B6E90_003b6e90(p3fes::EEContext&);
void fn_sub_3B6F50_003b6f50(p3fes::EEContext&);
void fn_sub_3B7090_003b7090(p3fes::EEContext&);
void fn_sub_3B7460_003b7460(p3fes::EEContext&);
void fn_sub_3B78B0_003b78b0(p3fes::EEContext&);
void fn_sub_3B7930_003b7930(p3fes::EEContext&);
void fn_sub_3B79A0_003b79a0(p3fes::EEContext&);
void fn_sub_3B7AC0_003b7ac0(p3fes::EEContext&);
void fn_sub_4C2F30_004c2f30(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C32A0_004c32a0(p3fes::EEContext&);
void fn_sub_4C35D0_004c35d0(p3fes::EEContext&);
void fn_sub_4C3880_004c3880(p3fes::EEContext&);
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4CB590_004cb590(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace scn;

// 0x003B4FC0 sub_3B4FC0 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [resrcMngCreate] Creates a resource manager: an 88-byte RwMalloc block (hint 0x40000), zeroed -- the 22 list heads,
// one per resource type (MT_Scene_Load stores it at scene +8).
void sub_3B4FC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b4fc0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 88;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, g::kLoRwMalloc);  // 0x960178 the RwMalloc slot
    jalr(ctx, 0x3B4FDCu, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 88;
    jal(ctx, 0x3B4FF4u, gen::fn_memset_00521408);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B5020 sub_3B5020 -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [resrcMngDestroy] (mgr) Deletes every resource of every type (sub_3B5360 on each list head until the list is empty)
// and frees the manager; a NULL manager does nothing.
void sub_3B5020(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b5020
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    if (s1 != 0) {
        // 0x003b503c
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x003b508c
            charge(ctx, 3);
            v0 = slti(s0, 22);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b5048
            charge(ctx, 6);
            a1 = s0 & 0xFF;
            a0 = s1;
            jal(ctx, 0x3B5050u, gen::fn_sub_3B5430_003b5430);
            for (;;) {
                // 0x003b5080
                charge(ctx, 2);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003b5060
                charge(ctx, 8);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x3B5068u, gen::fn_sub_3B5360_003b5360);
                a1 = s0 & 0xFF;
                a0 = s1;
                jal(ctx, 0x3B5078u, gen::fn_sub_3B5430_003b5430);
            }
            // 0x003b5088
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x003b5098
        charge(ctx, 5);
        a0 = s1;
        v0 = 0x960000;
        lw(v0, v0, g::kLoRwFree);  // 0x96017C the RwFree slot
        jalr(ctx, 0x3B50A4u, v0.u());
    }
    // 0x003b50ac (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003B50D0 sub_3B50D0 -- 644 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [resrcMngAddRes] (mgr, id) Allocates and links a resource record: type = (id & 0xFC00) >> 10 (>= 22: "warning!! not
// known resrc!!" and 0), the record size from the type (jump table 0x7BB250: 1 496, 2 464, 3 544, 4/5 432, 6 264, 7
// 272, 8 256, 10 304, 11 264, 12 368, 13/21 336, 14..19 272, 20 288; types 0 and 9 have none -> 0), zeroed, +0 = id,
// scale = 1.0; an id already on the list frees the block, prints "warning!! duplicate resID!! not regist!" and
// returns 0 (K_Assert line 168); else it is appended at the list tail (+248 next, +252 prev) and returned.
void sub_3B50D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b50d0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    s3 = s0 & 0xFFFF;
    v0 = 0xF0000;
    v0 = v0 | 0xFC00;
    v0 = s3 & v0;
    s2 = sra(v0, 10);
    s4 = 0;
    v0 = slti(s2, 22);
    if (v0 != 0) {
        // 0x003b5140
        charge(ctx, 3);
        at = sltiu(s2, 22);
        if (at != 0) {
            // 0x003b514c
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -19888);  // &0x7BB250
            v0 = sll(s2, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x3B5168u:  // table[1]
                // 0x003b5168
                charge(ctx, 3);
                s4 = 496;
                break;
            case 0x3B5174u:  // table[2]
                // 0x003b5174
                charge(ctx, 3);
                s4 = 464;
                break;
            case 0x3B5180u:  // table[3]
                // 0x003b5180
                charge(ctx, 3);
                s4 = 544;
                break;
            case 0x3B518Cu:  // table[4]
                // 0x003b518c
                charge(ctx, 3);
                s4 = 432;
                break;
            case 0x3B5198u:  // table[5]
                // 0x003b5198
                charge(ctx, 3);
                s4 = 432;
                break;
            case 0x3B51A4u:  // table[6]
                // 0x003b51a4
                charge(ctx, 3);
                s4 = 264;
                break;
            case 0x3B51B0u:  // table[7]
                // 0x003b51b0
                charge(ctx, 3);
                s4 = 272;
                break;
            case 0x3B51BCu:  // table[8]
                // 0x003b51bc
                charge(ctx, 3);
                s4 = 256;
                break;
            case 0x3B51C8u:  // table[10]
                // 0x003b51c8
                charge(ctx, 3);
                s4 = 304;
                break;
            case 0x3B51D4u:  // table[11]
                // 0x003b51d4
                charge(ctx, 3);
                s4 = 264;
                break;
            case 0x3B51E0u:  // table[12]
                // 0x003b51e0
                charge(ctx, 3);
                s4 = 368;
                break;
            case 0x3B51ECu:  // table[13, 21]
                // 0x003b51ec
                charge(ctx, 3);
                s4 = 336;
                break;
            case 0x3B51F8u:  // table[14, 15, 16, 17, 18, 19]
                // 0x003b51f8
                charge(ctx, 3);
                s4 = 272;
                break;
            case 0x3B5204u:  // table[20]
                // 0x003b5204
                charge(ctx, 1);
                s4 = 288;
                break;
            case 0x3B5208u:  // table[0, 9]
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x003b5208
        charge(ctx, 2);
        if (s4 != 0) {
            // 0x003b521c
            charge(ctx, 23);
            a0 = s4;
            a1 = 0x40000;
            v0 = 0x960000;
            lw(v0, v0, g::kLoRwMalloc);  // 0x960178 the RwMalloc slot
            jalr(ctx, 0x3B522Cu, v0.u());
            s5 = v0;
            a0 = s5;
            a1 = 0;
            a2 = s4;
            jal(ctx, 0x3B5244u, gen::fn_memset_00521408);
            sh(s0, s5, res::kId);
            v0 = 0x3F800000;
            sw(v0, s5, res::kScaleZ);
            sw(v0, s5, res::kScaleY);
            sw(v0, s5, res::kScale);
            v0 = sll(s2, 2);
            v1 = addu(s1, v0);
            lw(a1, v1, 0);
            a0 = a1;
            for (;;) {
                // 0x003b52d4
                charge(ctx, 2);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003b5278
                charge(ctx, 3);
                lhu(v0, a0, res::kId);
                if (v0 == s3) {
                    goto L_003b5284_22;
                }
                // 0x003b52d0
                charge(ctx, 1);
                lw(a0, a0, res::kNext);
            }
            // 0x003b52dc
            charge(ctx, 2);
            if (a1 == 0) {
                // 0x003b531c
                charge(ctx, 3);
                sw(s5, v1, 0);
                sw(zero, s5, res::kNext);
                sw(zero, s5, res::kPrev);
            } else {
                // 0x003b52e4
                charge(ctx, 2);
                for (;;) {
                    // 0x003b52f0
                    charge(ctx, 6);
                    lw(v0, a1, res::kNext);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003b52ec
                    charge(ctx, 1);
                    a1 = v0;
                }
                // 0x003b5308
                charge(ctx, 5);
                sw(s5, a1, res::kNext);
                sw(a1, s5, res::kPrev);
                sw(zero, s5, res::kNext);
            }
            // 0x003b5328
            charge(ctx, 1);
            v0 = s5;
        } else {
            // 0x003b5210
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b511c
        charge(ctx, 9);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10896);  // "warning!! not known resrc!! %s\n"
        a1 = 0x6A0000;
        a1 = addiu(a1, 10928);  // "resrcManager.c"
        jal(ctx, 0x3B512Cu, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b532c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_003b5284_22:
    charge(ctx, 19);
    a0 = s5;
    v0 = 0x960000;
    lw(v0, v0, g::kLoRwFree);  // 0x96017C the RwFree slot
    jalr(ctx, 0x3B5290u, v0.u());
    a0 = 0x6A0000;
    a0 = addiu(a0, 10944);  // "warning!! duplicate resID!! not regist!%s\n"
    a1 = 0x6A0000;
    a1 = addiu(a1, 10928);  // "resrcManager.c"
    jal(ctx, 0x3B52A8u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 10928);  // "resrcManager.c"
    a1 = 168;
    jal(ctx, 0x3B52BCu, gen::fn_sub_19D3F0_0019d3f0);
    v0 = 0;
    // 0x003b532c (the shared epilogue, written out on this path)
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

// 0x003B5360 sub_3B5360 -- 204 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [resrcMngDeleteRes] (mgr, res) Unlinks `res` from its type list (the head when it has no prev), frees its owned
// block (+84) and the record (RwFree); a record not on the list is left alone.
void sub_3B5360(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b5360
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lhu(a1, a1, res::kId);
    v1 = 0xF0000;
    v1 = v1 | 0xFC00;
    v1 = a1 & v1;
    v1 = sra(v1, 10);
    v1 = sll(v1, 2);
    a1 = addu(a0, v1);
    lw(v1, a1, 0);
    for (;;) {
        // 0x003b5410
        charge(ctx, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b5398
        charge(ctx, 2);
        if (s0 == v1) {
            goto L_003b53a0_2;
        }
        // 0x003b540c
        charge(ctx, 1);
        lw(v1, v1, res::kNext);
    }
    // 0x003b5418 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_003b53a0_2:
    charge(ctx, 4);
    lw(a0, v1, res::kPrev);
    lw(v1, v1, res::kNext);
    if (a0 == 0) {
        // 0x003b53b0
        charge(ctx, 2);
        lw(v0, s0, res::kNext);
        sw(v0, a1, 0);
    }
    // 0x003b53b8
    charge(ctx, 2);
    if (v1 != 0) {
        // 0x003b53c0
        charge(ctx, 1);
        sw(a0, v1, res::kPrev);
    }
    // 0x003b53c4
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x003b53cc
        charge(ctx, 1);
        sw(v1, a0, res::kNext);
    }
    // 0x003b53d0
    charge(ctx, 3);
    lw(a0, s0, res::kOwnedBlock);
    if (a0 != 0) {
        // 0x003b53dc
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, g::kLoRwFree);  // 0x96017C the RwFree slot
        jalr(ctx, 0x3B53E4u, v0.u());
        sw(zero, s0, res::kOwnedBlock);
    }
    // 0x003b53f0
    charge(ctx, 7);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, g::kLoRwFree);  // 0x96017C the RwFree slot
    jalr(ctx, 0x3B53FCu, v0.u());
    // 0x003b5418 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B5430 sub_3B5430 -- 48 bytes; leaf frame (no stack)
// [resrcMngGetListHead] (mgr, type) The head of the type list (type < 22; else 0).
void sub_3B5430(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003b5430
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = a1 & 0xFF;
    v0 = slti(v1, 22);
    if (v0 != 0) {
        // 0x003b544c
        charge(ctx, 3);
        v0 = sll(v1, 2);
        v0 = addu(a0, v0);
        lw(v0, v0, 0);
    } else {
        // 0x003b5440
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b5458 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003B54C0 sub_3B54C0 -- 132 bytes; leaf frame (no stack)
// [resrcMngFindRes] (mgr, id) The record with this id on its type list (0 for type 0, type >= 22 or none).
void sub_3B54C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003b54c0
    enter(ctx, 8);  // entry check point + this block's cycles
    a1 = a1 & 0xFFFF;
    v0 = 0xF0000;
    v0 = v0 | 0xFC00;
    v0 = a1 & v0;
    v0 = sra(v0, 10);
    v1 = v0 & 0xFF;
    if (v1 != 0) {
        // 0x003b54ec
        charge(ctx, 3);
        v0 = slti(v1, 22);
        if (v0 != 0) {
            // 0x003b5504
            charge(ctx, 5);
            v0 = sll(v1, 2);
            v0 = addu(a0, v0);
            lw(v0, v0, 0);
            for (;;) {
                // 0x003b5530
                charge(ctx, 2);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003b5518
                charge(ctx, 3);
                lhu(v1, v0, res::kId);
                if (v1 == a1) {
                    goto L_003b5524_6;
                }
                // 0x003b552c
                charge(ctx, 1);
                lw(v0, v0, res::kNext);
            }
            // 0x003b5538
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x003b54f8
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b54e0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b553c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_003b5524_6:
    charge(ctx, 2);
    // 0x003b553c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003B5550 sub_3B5550 -- 84 bytes; leaf frame (no stack)
// [resrcMngCountRes] (mgr, type) How many records the type list holds (0 for type >= 22).
void sub_3B5550(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003b5550
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0;
    a1 = a1 & 0xFF;
    v1 = slti(a1, 22);
    if (v1 != 0) {
        // 0x003b556c
        charge(ctx, 5);
        v1 = sll(a1, 2);
        v1 = addu(a0, v1);
        lw(v1, v1, 0);
        for (;;) {
            // 0x003b5588
            charge(ctx, 5);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b5580
            charge(ctx, 2);
            v0 = addiu(v0, 1);
            lw(v1, v1, res::kNext);
        }
    } else {
        // 0x003b5564
        charge(ctx, 2);
    }
    // 0x003b559c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003B5620 sub_3B5620 -- 308 bytes; frame 0x130: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_Scene_FieldModelExists] (major, minor) 1 when "field/model/fMMM_NNN.rws" exists (H_Cdvd_FileExists), else 0
// (the Tartarus-floor test after it changes nothing: both branches return 1).
void sub_3B5620(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b5620
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1;
    a0 = addiu(sp, 0xB0);
    a1 = 0x6A0000;
    a1 = addiu(a1, 11088);  // "field/model/f"
    jal(ctx, 0x3B5644u, gen::fn_strcpy_00524270);
    a0 = addiu(sp, 0x30);
    a1 = addiu(gp, -22440);  // "%03d"
    a2 = s0;
    jal(ctx, 0x3B5658u, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0xB0);
    a1 = addiu(sp, 0x30);
    jal(ctx, 0x3B5668u, gen::fn_strcat_00523e68);
    a0 = addiu(sp, 0x30);
    a1 = addiu(gp, -22432);  // "_%03d"
    a2 = s1;
    jal(ctx, 0x3B567Cu, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0xB0);
    a1 = addiu(sp, 0x30);
    jal(ctx, 0x3B568Cu, gen::fn_strcat_00523e68);
    a0 = addiu(sp, 0xB0);
    a1 = addiu(gp, -22424);  // ".rws"
    jal(ctx, 0x3B569Cu, gen::fn_strcat_00523e68);
    a0 = addiu(sp, 0xB0);
    jal(ctx, 0x3B56A8u, gen::fn_H_Cdvd_FileExists_001008b0);
    if (v0 != 0) {
        // 0x003b56c4
        charge(ctx, 4);
        v0 = 1;
        v1 = slti(s0, 20);
        if (v1 == 0) {
            // 0x003b56d4
            charge(ctx, 3);
            at = slti(s0, 29);
            if (at == 0) {
                goto L_003b56e8;
            }
            // 0x003b56e0
            charge(ctx, 2);
            if (s1 != 0) {
                goto L_003b56e8;
            }
        L_003b5738:
            charge(ctx, 1);
            v0 = 1;
            // 0x003b573c (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x130);
            return;
        }
    L_003b56e8:
        charge(ctx, 3);
        v1 = slti(s0, 51);
        if (v1 == 0) {
            // 0x003b56f4
            charge(ctx, 3);
            at = slti(s0, 59);
            if (at != 0) {
                goto L_003b5738;
            }
            goto L_003b5700;
        }
    L_003b5700:
        charge(ctx, 3);
        v1 = slti(s0, 40);
        if (v1 == 0) {
            // 0x003b570c
            charge(ctx, 3);
            at = slti(s0, 49);
            if (at == 0) {
                goto L_003b5720;
            }
            // 0x003b5718
            charge(ctx, 2);
            if (s1 == 0) {
                goto L_003b5738;
            }
            goto L_003b5720;
        }
    L_003b5720:
        charge(ctx, 3);
        v1 = slti(s0, 71);
        if (v1 == 0) {
            // 0x003b572c
            charge(ctx, 3);
            at = slti(s0, 79);
            if (at != 0) {
                goto L_003b5738;
            }
        }
    } else {
        // 0x003b56b8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b573c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x130);
}

// 0x003B58C0 sub_3B58C0 -- 180 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [MT_Scene_SetNpcSet] (set) Sets the scene's NPC placement set (+20). Scene loaded (flags bit 0): the same set marks
// every type-3 resource visible (flag bit 1); another set sets flags bit 1 (reload the NPCs) and the field loader's
// step (sField +4184) to 30.
void sub_3B58C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b58c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a3, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    a2 = addiu(a3, 12);
    lw(a1, a3, scene::kFlags);
    v1 = a1 & 0x1;
    if (v1 == 0) {
        // 0x003b595c
        charge(ctx, 1);
        sh(a0, a3, scene::kNpcSet);
    } else {
        // 0x003b58e4
        charge(ctx, 5);
        lh(v1, a3, scene::kNpcSet);
        v0 = dsll32(a0, 16);
        v0 = dsra32(v0, 16);
        if (v1 == v0) {
            // 0x003b5920
            charge(ctx, 6);
            a0 = 3;
            jal(ctx, 0x3B5924u, gen::fn_sub_3B5D50_003b5d50);
            a0 = v0;
            for (;;) {
                // 0x003b5948
                charge(ctx, 3);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003b5938
                charge(ctx, 4);
                lw(v1, a0, res::kFlags);
                v1 = v1 | 0x2;
                sw(v1, a0, res::kFlags);
                lw(a0, a0, res::kNext);
            }
            // 0x003b5954
            charge(ctx, 2);
        } else {
            // 0x003b58f8
            charge(ctx, 10);
            v0 = a1 | 0x2;
            sw(v0, a2, 0);
            lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
            sh(a0, v0, 20);
            s0 = 30;
            jal(ctx, 0x3B590Cu, gen::fn_K_Field_Get_001b9120);
            sw(s0, v0, 4184);
        }
    }
    // 0x003b5960 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B5980 sub_3B5980 -- 140 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [MT_Scene_SetEnvSub] (sub) Sets the scene's ENV sub-id (+22). Scene loaded and the id changes: flags bit 2 (reload
// the ENV) and, unless an NPC reload is pending (bit 1), the loader step 40.
void sub_3B5980(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b5980
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a1, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    a3 = addiu(a1, 12);
    lw(a2, a1, scene::kFlags);
    v1 = a2 & 0x1;
    if (v1 == 0) {
        // 0x003b59f4
        charge(ctx, 1);
        sh(a0, a1, scene::kEnvSub);
    } else {
        // 0x003b59a4
        charge(ctx, 5);
        lh(a1, a1, scene::kEnvSub);
        v1 = dsll32(a0, 16);
        v1 = dsra32(v1, 16);
        if (a1 != v1) {
            // 0x003b59b8
            charge(ctx, 9);
            v1 = a2 | 0x4;
            sw(v1, a3, 0);
            lw(v1, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
            sh(a0, v1, scene::kEnvSub);
            lw(v1, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
            lw(v1, v1, scene::kFlags);
            v1 = v1 & 0x2;
            if (v1 == 0) {
                // 0x003b59dc
                charge(ctx, 6);
                s0 = 40;
                jal(ctx, 0x3B59E0u, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, 4184);
            }
        }
    }
    // 0x003b59f8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B5D50 sub_3B5D50 -- 68 bytes; frame 0x10: ra sp+0x0
// [MT_Scene_GetResListHead] (type) The head of the scene manager's type list (0 without a manager).
void sub_3B5D50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b5d50
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(v0, v0, scene::kResMgr);
    if (v0 != 0) {
        // 0x003b5d74
        charge(ctx, 4);
        a1 = a0 & 0xFF;
        a0 = v0;
        jal(ctx, 0x3B5D7Cu, gen::fn_sub_3B5430_003b5430);
    } else {
        // 0x003b5d68
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b5d84 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003B5E90 sub_3B5E90 -- 216 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [MT_Scene_CreateResPos] (n) Registers position resource 0x2000 | (n & 0x3FF) (type 8); the id only when it is type
// 8 ("this resId not postion" otherwise, unreachable) and the record was made, else 0. "not found active resmanager"
// without a manager.
void sub_3B5E90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b5e90
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x2000;
    s0 = v0 & 0xFFFF;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b5ed8
        charge(ctx, 8);
        v1 = s0 & 0xFFFF;
        v0 = 0xF0000;
        v0 = v0 | 0xFC00;
        v0 = v1 & v0;
        v1 = sra(v0, 10);
        v0 = 8;
        if (v1 == v0) {
            // 0x003b5f14
            charge(ctx, 5);
            a1 = s0;
            jal(ctx, 0x3B5F18u, gen::fn_sub_3B50D0_003b50d0);
            if (v0 != 0) {
                // 0x003b5f34
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x003b5f3c
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 11240);  // "mt_scene.c"
                    a1 = 471;
                    jal(ctx, 0x3B5F48u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x003b5f50
                charge(ctx, 1);
                v0 = s0;
            } else {
                // 0x003b5f28
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003b5ef8
            charge(ctx, 7);
            a0 = 0x6A0000;
            a0 = addiu(a0, 11216);  // "this resId not postion\n"
            jal(ctx, 0x3B5F00u, gen::fn_printf_005225a8);
            v0 = 0;
        }
    } else {
        // 0x003b5ebc
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B5EC4u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b5f54 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B5F70 sub_3B5F70 -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [MT_Scene_CreateRes7] (n) Registers type-7 resource 0x1C00 | n with +256 = 35.0; the id or 0.
void sub_3B5F70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b5f70
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x1C00;
    s0 = v0 & 0xFFFF;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b5fb8
        charge(ctx, 5);
        a1 = s0;
        jal(ctx, 0x3B5FBCu, gen::fn_sub_3B50D0_003b50d0);
        if (v0 != 0) {
            // 0x003b5fd8
            charge(ctx, 3);
            v1 = 0x420C0000;
            sw(v1, v0, snd::kRadius);
            v0 = s0;
        } else {
            // 0x003b5fcc
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b5f9c
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B5FA4u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b5fe4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B6180 sub_3B6180 -- 228 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_Scene_CreateResModel] (n, model) Registers type-2 resource 0x800 | n for an existing model (+280) and places
// the model at the origin (sub_318A30 with a zero vector from the stack); 0 for a NULL model.
void sub_3B6180(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b6180
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    v1 = addiu(sp, 0x30);
    v0 = 12;
    if (v1 != 0) {
        for (;;) {
            // 0x003b61a4
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
    // 0x003b61c0
    charge(ctx, 8);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x800;
    s1 = v0 & 0xFFFF;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b61fc
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x003b6210
            charge(ctx, 5);
            a1 = s1;
            jal(ctx, 0x3B6214u, gen::fn_sub_3B50D0_003b50d0);
            if (v0 != 0) {
                // 0x003b6230
                charge(ctx, 7);
                sw(s0, v0, mdl::kModel);
                a0 = s0;
                a1 = addiu(sp, 0x30);
                a2 = 0;
                jal(ctx, 0x3B6240u, gen::fn_sub_318A30_00318a30);
                v0 = s1;
            } else {
                // 0x003b6224
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003b6204
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b61e0
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B61E8u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b624c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B63C0 sub_3B63C0 -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [MT_Scene_CreateResLightChar] (n) Registers type-4 resource 0x1000 | n (MT_Scene_Load: the character light); the id
// or 0.
void sub_3B63C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b63c0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x1000;
    s0 = v0 & 0xFFFF;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b6408
        charge(ctx, 5);
        a1 = s0;
        jal(ctx, 0x3B640Cu, gen::fn_sub_3B50D0_003b50d0);
        if (v0 == 0) {
            // 0x003b641c
            charge(ctx, 1);
            s0 = 0;
        }
        // 0x003b6420
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x003b63ec
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B63F4u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b6424 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B6440 sub_3B6440 -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [MT_Scene_CreateResLightNpc] (n) Registers type-5 resource 0x1400 | n (the NPC light); the id or 0.
void sub_3B6440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b6440
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x1400;
    s0 = v0 & 0xFFFF;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b6488
        charge(ctx, 5);
        a1 = s0;
        jal(ctx, 0x3B648Cu, gen::fn_sub_3B50D0_003b50d0);
        if (v0 == 0) {
            // 0x003b649c
            charge(ctx, 1);
            s0 = 0;
        }
        // 0x003b64a0
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x003b646c
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B6474u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b64a4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B66B0 sub_3B66B0 -- 220 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_Scene_CreateResFieldEpl] (n, epl) Registers type-11 resource 0x2C00 | n for an EPL handle (+260), shown (flag
// 8); 0 for a NULL handle.
void sub_3B66B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b66b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    v1 = addiu(sp, 0x30);
    v0 = 12;
    if (v1 != 0) {
        for (;;) {
            // 0x003b66d4
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
    // 0x003b66f0
    charge(ctx, 8);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x2C00;
    s1 = v0 & 0xFFFF;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b672c
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x003b6740
            charge(ctx, 5);
            a1 = s1;
            jal(ctx, 0x3B6744u, gen::fn_sub_3B50D0_003b50d0);
            if (v0 != 0) {
                // 0x003b6760
                charge(ctx, 5);
                sw(s0, v0, eff::kEpl);
                lw(v1, v0, res::kFlags);
                v1 = v1 | 0x8;
                sw(v1, v0, res::kFlags);
                v0 = s1;
            } else {
                // 0x003b6754
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003b6734
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b6710
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B6718u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b6774 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B6790 sub_3B6790 -- 220 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_Scene_CreateResBlock] (n, data) Registers type-12 resource 0x3000 | n (a Tartarus block: 0x3000 + 16 z + x)
// with its block data (+352), shown; 0 for NULL data.
void sub_3B6790(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b6790
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    v1 = addiu(sp, 0x30);
    v0 = 12;
    if (v1 != 0) {
        for (;;) {
            // 0x003b67b4
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
    // 0x003b67d0
    charge(ctx, 8);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x3000;
    s1 = v0 & 0xFFFF;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b680c
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x003b6820
            charge(ctx, 5);
            a1 = s1;
            jal(ctx, 0x3B6824u, gen::fn_sub_3B50D0_003b50d0);
            if (v0 != 0) {
                // 0x003b6840
                charge(ctx, 5);
                sw(s0, v0, blk::kBlockData);
                lw(v1, v0, res::kFlags);
                v1 = v1 | 0x8;
                sw(v1, v0, res::kFlags);
                v0 = s1;
            } else {
                // 0x003b6834
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003b6814
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b67f0
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B67F8u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b6854 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B6870 sub_3B6870 -- 300 bytes; frame 0x60: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [MT_Scene_CreateResHit] (n, pos, rgba, $f12 width, $f13 depth, $f14 turn) Registers type-13 field hit 0x3400 | n:
// the colour bytes (+256), the position (+260), width / depth / turn (+272 / +276 / +280) and its quad (+284,
// sub_1E6AF0: the width x depth rectangle centred on the origin, turned about y, moved to the position), shown.
void sub_3B6870(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x003b6870
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a1;
    mov_s(f22, f12);
    mov_s(f21, f13);
    mov_s(f20, f14);
    sw(a2, sp, 0x5C);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x3400;
    s1 = v0 & 0xFFFF;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b68e0
        charge(ctx, 6);
        a1 = s1;
        jal(ctx, 0x3B68E4u, gen::fn_sub_3B50D0_003b50d0);
        s0 = v0;
        if (s0 != 0) {
            // 0x003b6904
            charge(ctx, 28);
            lwc1(f2, s2, 0);
            lwc1(f1, s2, 4);
            lwc1(f0, s2, 8);
            swc1(f2, s0, hit::kPos);
            swc1(f1, s0, hit::kPosY);
            swc1(f0, s0, hit::kPosZ);
            swc1(f22, s0, hit::kWidth);
            swc1(f21, s0, hit::kDepth);
            swc1(f20, s0, hit::kTurn);
            lbu(a1, sp, 0x5C);
            lbu(a0, sp, 0x5D);
            lbu(v1, sp, 0x5E);
            lbu(v0, sp, 0x5F);
            sb(a1, s0, hit::kRgba);
            sb(a0, s0, hit::kRgbaG);
            sb(v1, s0, hit::kRgbaB);
            sb(v0, s0, hit::kRgbaA);
            a0 = addiu(s0, 284);
            a1 = s2;
            mov_s(f12, f22);
            mov_s(f13, f21);
            mov_s(f14, f20);
            jal(ctx, 0x3B695Cu, gen::fn_sub_1E6AF0_001e6af0);
            lw(v0, s0, res::kFlags);
            v0 = v0 | 0x8;
            sw(v0, s0, res::kFlags);
            v0 = s1;
        } else {
            // 0x003b68f8
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b68c4
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B68CCu, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b6974 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003B69A0 sub_3B69A0 -- 300 bytes; frame 0x60: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [MT_Scene_CreateResHit21] (n, pos, rgba, $f12 width, $f13 depth, $f14 turn) As sub_3B6870 for the type-21 hit
// 0x5400 | n.
void sub_3B69A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x003b69a0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a1;
    mov_s(f22, f12);
    mov_s(f21, f13);
    mov_s(f20, f14);
    sw(a2, sp, 0x5C);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x5400;
    s1 = v0 & 0xFFFF;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b6a10
        charge(ctx, 6);
        a1 = s1;
        jal(ctx, 0x3B6A14u, gen::fn_sub_3B50D0_003b50d0);
        s0 = v0;
        if (s0 != 0) {
            // 0x003b6a34
            charge(ctx, 28);
            lwc1(f2, s2, 0);
            lwc1(f1, s2, 4);
            lwc1(f0, s2, 8);
            swc1(f2, s0, hit::kPos);
            swc1(f1, s0, hit::kPosY);
            swc1(f0, s0, hit::kPosZ);
            swc1(f22, s0, hit::kWidth);
            swc1(f21, s0, hit::kDepth);
            swc1(f20, s0, hit::kTurn);
            lbu(a1, sp, 0x5C);
            lbu(a0, sp, 0x5D);
            lbu(v1, sp, 0x5E);
            lbu(v0, sp, 0x5F);
            sb(a1, s0, hit::kRgba);
            sb(a0, s0, hit::kRgbaG);
            sb(v1, s0, hit::kRgbaB);
            sb(v0, s0, hit::kRgbaA);
            a0 = addiu(s0, 284);
            a1 = s2;
            mov_s(f12, f22);
            mov_s(f13, f21);
            mov_s(f14, f20);
            jal(ctx, 0x3B6A8Cu, gen::fn_sub_1E6AF0_001e6af0);
            lw(v0, s0, res::kFlags);
            v0 = v0 | 0x8;
            sw(v0, s0, res::kFlags);
            v0 = s1;
        } else {
            // 0x003b6a28
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b69f4
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B69FCu, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b6aa4 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003B6AD0 sub_3B6AD0 -- 192 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [MT_Scene_CreateResPoint14] (n, point, $f12) Registers marker 0x3800 | n (type 14): point (+256), angle (+268),
// shown.
void sub_3B6AD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x003b6ad0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a1;
    mov_s(f20, f12);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x3800;
    s1 = v0 & 0xFFFF;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b6b28
        charge(ctx, 5);
        a1 = s1;
        jal(ctx, 0x3B6B2Cu, gen::fn_sub_3B50D0_003b50d0);
        if (v0 != 0) {
            // 0x003b6b48
            charge(ctx, 11);
            lwc1(f2, s0, 0);
            lwc1(f1, s0, 4);
            lwc1(f0, s0, 8);
            swc1(f2, v0, pos::kPoint);
            swc1(f1, v0, pos::kPointY);
            swc1(f0, v0, pos::kPointZ);
            swc1(f20, v0, pos::kAngle);
            lw(v1, v0, res::kFlags);
            v1 = v1 | 0x8;
            sw(v1, v0, res::kFlags);
            v0 = s1;
        } else {
            // 0x003b6b3c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b6b0c
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B6B14u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b6b74 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B6B90 sub_3B6B90 -- 192 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [MT_Scene_CreateResPoint15] (n, point, $f12) Marker 0x3C00 | n (type 15: enemies), as sub_3B6AD0.
void sub_3B6B90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x003b6b90
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a1;
    mov_s(f20, f12);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x3C00;
    s1 = v0 & 0xFFFF;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b6be8
        charge(ctx, 5);
        a1 = s1;
        jal(ctx, 0x3B6BECu, gen::fn_sub_3B50D0_003b50d0);
        if (v0 != 0) {
            // 0x003b6c08
            charge(ctx, 11);
            lwc1(f2, s0, 0);
            lwc1(f1, s0, 4);
            lwc1(f0, s0, 8);
            swc1(f2, v0, pos::kPoint);
            swc1(f1, v0, pos::kPointY);
            swc1(f0, v0, pos::kPointZ);
            swc1(f20, v0, pos::kAngle);
            lw(v1, v0, res::kFlags);
            v1 = v1 | 0x8;
            sw(v1, v0, res::kFlags);
            v0 = s1;
        } else {
            // 0x003b6bfc
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b6bcc
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B6BD4u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b6c34 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B6C50 sub_3B6C50 -- 192 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [MT_Scene_CreateResPoint16] (n, point, $f12) Marker 0x4000 | n (type 16), as sub_3B6AD0.
void sub_3B6C50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x003b6c50
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a1;
    mov_s(f20, f12);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x4000;
    s1 = v0 & 0xFFFF;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b6ca8
        charge(ctx, 5);
        a1 = s1;
        jal(ctx, 0x3B6CACu, gen::fn_sub_3B50D0_003b50d0);
        if (v0 != 0) {
            // 0x003b6cc8
            charge(ctx, 11);
            lwc1(f2, s0, 0);
            lwc1(f1, s0, 4);
            lwc1(f0, s0, 8);
            swc1(f2, v0, pos::kPoint);
            swc1(f1, v0, pos::kPointY);
            swc1(f0, v0, pos::kPointZ);
            swc1(f20, v0, pos::kAngle);
            lw(v1, v0, res::kFlags);
            v1 = v1 | 0x8;
            sw(v1, v0, res::kFlags);
            v0 = s1;
        } else {
            // 0x003b6cbc
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b6c8c
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B6C94u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b6cf4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B6D10 sub_3B6D10 -- 192 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [MT_Scene_CreateResPoint17] (n, point, $f12) Marker 0x4400 | n (type 17), as sub_3B6AD0.
void sub_3B6D10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x003b6d10
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a1;
    mov_s(f20, f12);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x4400;
    s1 = v0 & 0xFFFF;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b6d68
        charge(ctx, 5);
        a1 = s1;
        jal(ctx, 0x3B6D6Cu, gen::fn_sub_3B50D0_003b50d0);
        if (v0 != 0) {
            // 0x003b6d88
            charge(ctx, 11);
            lwc1(f2, s0, 0);
            lwc1(f1, s0, 4);
            lwc1(f0, s0, 8);
            swc1(f2, v0, pos::kPoint);
            swc1(f1, v0, pos::kPointY);
            swc1(f0, v0, pos::kPointZ);
            swc1(f20, v0, pos::kAngle);
            lw(v1, v0, res::kFlags);
            v1 = v1 | 0x8;
            sw(v1, v0, res::kFlags);
            v0 = s1;
        } else {
            // 0x003b6d7c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b6d4c
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B6D54u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b6db4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B6DD0 sub_3B6DD0 -- 192 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [MT_Scene_CreateResPoint18] (n, point, $f12) Marker 0x4800 | n (type 18), as sub_3B6AD0.
void sub_3B6DD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x003b6dd0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a1;
    mov_s(f20, f12);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x4800;
    s1 = v0 & 0xFFFF;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b6e28
        charge(ctx, 5);
        a1 = s1;
        jal(ctx, 0x3B6E2Cu, gen::fn_sub_3B50D0_003b50d0);
        if (v0 != 0) {
            // 0x003b6e48
            charge(ctx, 11);
            lwc1(f2, s0, 0);
            lwc1(f1, s0, 4);
            lwc1(f0, s0, 8);
            swc1(f2, v0, pos::kPoint);
            swc1(f1, v0, pos::kPointY);
            swc1(f0, v0, pos::kPointZ);
            swc1(f20, v0, pos::kAngle);
            lw(v1, v0, res::kFlags);
            v1 = v1 | 0x8;
            sw(v1, v0, res::kFlags);
            v0 = s1;
        } else {
            // 0x003b6e3c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b6e0c
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B6E14u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b6e74 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B6E90 sub_3B6E90 -- 192 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [MT_Scene_CreateResPoint19] (n, point, $f12) Marker 0x4C00 | n (type 19), as sub_3B6AD0.
void sub_3B6E90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x003b6e90
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a1;
    mov_s(f20, f12);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x4C00;
    s1 = v0 & 0xFFFF;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b6ee8
        charge(ctx, 5);
        a1 = s1;
        jal(ctx, 0x3B6EECu, gen::fn_sub_3B50D0_003b50d0);
        if (v0 != 0) {
            // 0x003b6f08
            charge(ctx, 11);
            lwc1(f2, s0, 0);
            lwc1(f1, s0, 4);
            lwc1(f0, s0, 8);
            swc1(f2, v0, pos::kPoint);
            swc1(f1, v0, pos::kPointY);
            swc1(f0, v0, pos::kPointZ);
            swc1(f20, v0, pos::kAngle);
            lw(v1, v0, res::kFlags);
            v1 = v1 | 0x8;
            sw(v1, v0, res::kFlags);
            v0 = s1;
        } else {
            // 0x003b6efc
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b6ecc
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B6ED4u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b6f34 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B6F50 sub_3B6F50 -- 316 bytes; frame 0x70: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [MT_Scene_CreateResCamera] (n, kind, matrix, eye, $f12, $f14) Registers camera 0x5000 | n (type 20): kind (+256),
// $f12 (+260), a new RW matrix (sub_4C38C0) filled with the caller's 64 bytes (+264), the eye (+268), $f13 as left
// (+280), $f14 (+284), shown.
void sub_3B6F50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x003b6f50
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a1;
    mov_s(f22, f12);
    s3 = a2;
    s2 = a3;
    mov_s(f21, f13);
    mov_s(f20, f14);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x5000;
    s1 = v0 & 0xFFFF;
    lw(v0, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b6fcc
        charge(ctx, 6);
        a1 = s1;
        jal(ctx, 0x3B6FD0u, gen::fn_sub_3B50D0_003b50d0);
        s0 = v0;
        if (s0 != 0) {
            // 0x003b6ff0
            charge(ctx, 6);
            sw(s4, s0, cam::kKind);
            swc1(f22, s0, cam::kFov);
            jal(ctx, 0x3B6FF8u, gen::fn_sub_4C38C0_004c38c0);
            sw(v0, s0, cam::kMatrix);
            a1 = 8;
            for (;;) {
                // 0x003b7008
                charge(ctx, 9);
                lw(a0, s3, 0);
                lw(v1, s3, 4);
                s3 = addiu(s3, 8);
                a1 = addiu(a1, -1);
                sw(a0, v0, 0);
                sw(v1, v0, 4);
                v0 = addiu(v0, 8);
                if (i64(a1) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x003b702c
            charge(ctx, 12);
            lwc1(f2, s2, 0);
            lwc1(f1, s2, 4);
            lwc1(f0, s2, 8);
            swc1(f2, s0, cam::kEye);
            swc1(f1, s0, cam::kEyeY);
            swc1(f0, s0, cam::kEyeZ);
            swc1(f21, s0, cam::kNear);
            swc1(f20, s0, cam::kFar);
            lw(v0, s0, res::kFlags);
            v0 = v0 | 0x8;
            sw(v0, s0, res::kFlags);
            v0 = s1;
        } else {
            // 0x003b6fe4
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b6fb0
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B6FB8u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b705c (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x70);
}

// 0x003B7090 sub_3B7090 -- 972 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_Scene_DeleteRes] (id) Deletes a scene resource with what it owns, by type: 1 the controller task tree (+480),
// the three icon EPLs, the shadow model (+488, through its clump); 2 the model (+280); 3 the task (+488), the model
// (+296), the icons, blocks +512 / +520, the sub-model (+492); 6 / 11 the EPL (+260); 10 both models; 12 the block
// data (sub_1B3C90); 20 the camera matrix; each with its "delete ... =0x%x" print; then resrcMngDeleteRes. Unknown
// ids do nothing; no manager prints "not found active resmanager".
void sub_3B7090(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b7090
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a1 = a0;
    lw(v1, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(s2, v1, scene::kResMgr);
    if (s2 != 0) {
        // 0x003b70d8
        charge(ctx, 2);
        if (s2 != 0) {
            // 0x003b70ec
            charge(ctx, 4);
            a0 = s2;
            jal(ctx, 0x3B70F0u, gen::fn_sub_3B54C0_003b54c0);
            s0 = v0;
        } else {
            // 0x003b70e0
            charge(ctx, 3);
            s0 = 0;
        }
        // 0x003b70fc
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x003b7104
            charge(ctx, 8);
            lhu(v1, s0, res::kId);
            v0 = 0xF0000;
            v0 = v0 | 0xFC00;
            v0 = v1 & v0;
            v0 = sra(v0, 10);
            at = sltiu(v0, 22);
            if (at != 0) {
                // 0x003b7124
                charge(ctx, 7);
                v1 = 0x7C0000;
                v1 = addiu(v1, -19792);  // "(t;"
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x3B7140u:  // table[1]
                    // 0x003b7140
                    charge(ctx, 10);
                    lw(s1, s0, chr::kModel);
                    lw(a0, s0, chr::kTask);
                    jal(ctx, 0x3B7148u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    sw(zero, s0, chr::kTask);
                    sw(zero, s0, chr::kCtl);
                    sw(zero, s0, chr::kModel);
                    s3 = 0;
                    for (;;) {
                        // 0x003b7190
                        charge(ctx, 3);
                        v0 = slti(s3, 3);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x003b7168
                        charge(ctx, 6);
                        v0 = sll(s3, 2);
                        v0 = addu(s0, v0);
                        s4 = addiu(v0, 256);
                        lw(a0, v0, 256);
                        if (a0 != 0) {
                            // 0x003b7180
                            charge(ctx, 3);
                            jal(ctx, 0x3B7180u, gen::fn_sub_34FCF0_0034fcf0);
                            sw(zero, s4, 0);
                        }
                        // 0x003b718c
                        charge(ctx, 1);
                        s3 = addiu(s3, 1);
                    }
                    // 0x003b719c
                    charge(ctx, 3);
                    lw(a0, s0, 488);
                    if (a0 != 0) {
                        // 0x003b71a8
                        charge(ctx, 9);
                        jal(ctx, 0x3B71A8u, gen::fn_sub_318B70_00318b70);
                        a0 = v0;
                        jal(ctx, 0x3B71B4u, gen::fn_sub_4CB590_004cb590);
                        lw(a0, s0, 488);
                        jal(ctx, 0x3B71C0u, gen::fn_sub_3174E0_003174e0);
                        sw(zero, s0, 488);
                    }
                    // 0x003b71cc
                    charge(ctx, 7);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 11296);  // "delete model data =0x%x\n"
                    a1 = s1;
                    jal(ctx, 0x3B71D8u, gen::fn_printf_005225a8);
                    break;
                case 0x3B71E8u:  // table[2]
                    // 0x003b71e8
                    charge(ctx, 12);
                    lw(s1, s0, mdl::kModel);
                    a0 = s1;
                    jal(ctx, 0x3B71F0u, gen::fn_sub_3174E0_003174e0);
                    sw(zero, s0, mdl::kModel);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 11296);  // "delete model data =0x%x\n"
                    a1 = s1;
                    jal(ctx, 0x3B7208u, gen::fn_printf_005225a8);
                    break;
                case 0x3B7218u:  // table[3]
                    // 0x003b7218
                    charge(ctx, 13);
                    lw(s3, s0, chr::kModel);
                    lw(a0, s0, 488);
                    jal(ctx, 0x3B7220u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    sw(zero, s0, 488);
                    sw(zero, s0, npc::kCtl);
                    a0 = s3;
                    jal(ctx, 0x3B7234u, gen::fn_sub_3174E0_003174e0);
                    sw(zero, s0, chr::kModel);
                    s1 = 0;
                    for (;;) {
                        // 0x003b7274
                        charge(ctx, 3);
                        v0 = slti(s1, 3);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x003b724c
                        charge(ctx, 6);
                        v0 = sll(s1, 2);
                        v0 = addu(s0, v0);
                        s4 = addiu(v0, 256);
                        lw(a0, v0, 256);
                        if (a0 != 0) {
                            // 0x003b7264
                            charge(ctx, 3);
                            jal(ctx, 0x3B7264u, gen::fn_sub_34FCF0_0034fcf0);
                            sw(zero, s4, 0);
                        }
                        // 0x003b7270
                        charge(ctx, 1);
                        s1 = addiu(s1, 1);
                    }
                    // 0x003b7280
                    charge(ctx, 3);
                    lw(a0, s0, npc::kBlockA);
                    if (a0 != 0) {
                        // 0x003b728c
                        charge(ctx, 4);
                        v0 = 0x960000;
                        lw(v0, v0, g::kLoRwFree);  // 0x96017C the RwFree slot
                        jalr(ctx, 0x3B7294u, v0.u());
                    }
                    // 0x003b729c
                    charge(ctx, 3);
                    lw(a0, s0, npc::kBlockB);
                    if (a0 != 0) {
                        // 0x003b72a8
                        charge(ctx, 4);
                        v0 = 0x960000;
                        lw(v0, v0, g::kLoRwFree);  // 0x96017C the RwFree slot
                        jalr(ctx, 0x3B72B0u, v0.u());
                    }
                    // 0x003b72b8
                    charge(ctx, 3);
                    lw(a0, s0, npc::kSubModel);
                    if (a0 != 0) {
                        // 0x003b72c4
                        charge(ctx, 3);
                        jal(ctx, 0x3B72C4u, gen::fn_sub_3174E0_003174e0);
                        sw(zero, s0, npc::kSubModel);
                    }
                    // 0x003b72d0
                    charge(ctx, 7);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 11296);  // "delete model data =0x%x\n"
                    a1 = s3;
                    jal(ctx, 0x3B72DCu, gen::fn_printf_005225a8);
                    break;
                case 0x3B72ECu:  // table[6]
                    // 0x003b72ec
                    charge(ctx, 3);
                    lw(a0, s0, 260);
                    if (a0 != 0) {
                        // 0x003b72f8
                        charge(ctx, 10);
                        jal(ctx, 0x3B72F8u, gen::fn_sub_34FCF0_0034fcf0);
                        sw(zero, s0, 260);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, 11328);  // "delete eff res =0x%x\n"
                        a1 = s0;
                        jal(ctx, 0x3B7310u, gen::fn_printf_005225a8);
                    }
                    break;
                case 0x3B7320u:  // table[10]
                    // 0x003b7320
                    charge(ctx, 8);
                    lw(s1, s0, 260);
                    a0 = s1;
                    jal(ctx, 0x3B7328u, gen::fn_sub_3174E0_003174e0);
                    sw(zero, s0, 260);
                    lw(a0, s0, fmdl::kSubModel);
                    if (a0 != 0) {
                        // 0x003b7340
                        charge(ctx, 3);
                        jal(ctx, 0x3B7340u, gen::fn_sub_3174E0_003174e0);
                        sw(zero, s0, fmdl::kSubModel);
                    }
                    // 0x003b734c
                    charge(ctx, 7);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 11360);  // "delete field model data =0x%x\n"
                    a1 = s1;
                    jal(ctx, 0x3B7358u, gen::fn_printf_005225a8);
                    break;
                case 0x3B7368u:  // table[11]
                    // 0x003b7368
                    charge(ctx, 3);
                    lw(a0, s0, 260);
                    if (a0 != 0) {
                        // 0x003b7374
                        charge(ctx, 10);
                        jal(ctx, 0x3B7374u, gen::fn_sub_34FCF0_0034fcf0);
                        sw(zero, s0, 260);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, 11392);  // "delete field eff res =0x%x\n"
                        a1 = s0;
                        jal(ctx, 0x3B738Cu, gen::fn_printf_005225a8);
                    }
                    break;
                case 0x3B739Cu:  // table[12]
                    // 0x003b739c
                    charge(ctx, 3);
                    lw(a0, s0, blk::kBlockData);
                    if (a0 != 0) {
                        // 0x003b73a8
                        charge(ctx, 10);
                        jal(ctx, 0x3B73A8u, gen::fn_sub_1B3C90_001b3c90);
                        sw(zero, s0, blk::kBlockData);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, 11424);  // "delete field res =0x%x\n"
                        a1 = s0;
                        jal(ctx, 0x3B73C0u, gen::fn_printf_005225a8);
                    }
                    break;
                case 0x3B73D0u:  // table[13, 21]
                    // 0x003b73d0
                    charge(ctx, 7);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 11456);  // "delete field hit res =0x%x\n"
                    a1 = s0;
                    jal(ctx, 0x3B73DCu, gen::fn_printf_005225a8);
                    break;
                case 0x3B73ECu:  // table[14, 15, 16]
                    // 0x003b73ec
                    charge(ctx, 7);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 11488);  // "delete field pos res =0x%x\n"
                    a1 = s0;
                    jal(ctx, 0x3B73F8u, gen::fn_printf_005225a8);
                    break;
                case 0x3B7408u:  // table[20]
                    // 0x003b7408
                    charge(ctx, 8);
                    lw(a0, s0, 264);
                    jal(ctx, 0x3B740Cu, gen::fn_sub_4C3880_004c3880);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 11520);  // "delete field camera res =0x%x\n"
                    a1 = s0;
                    jal(ctx, 0x3B7420u, gen::fn_printf_005225a8);
                    break;
                case 0x3B7428u:  // table[0, 4, 5, 7, 8, 9, 17, 18, 19]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            }
            // 0x003b7428
            charge(ctx, 4);
            a0 = s2;
            a1 = s0;
            jal(ctx, 0x3B7430u, gen::fn_sub_3B5360_003b5360);
        }
    } else {
        // 0x003b70c0
        charge(ctx, 6);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B70C8u, gen::fn_printf_005225a8);
    }
    // 0x003b7438 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003B7460 sub_3B7460 -- 1100 bytes; frame 0xF0: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_Scene_ApplyTransform] (res, pos, rot, scale) Copies the non-NULL vectors into the record and applies the
// transform to its object: models (types 1 / 3 +296, 2 +280, 10 +260) are rotated by the record's angles about y
// (replacing), x and z (pre-concatenated; the axes 0x6A2D20 / 0x6A2D30 / 0x6A2D40, sub_318A50), then scaled
// (sub_318A90) and translated (sub_318A30) post-concatenated; effects (type 6) get the matrix of sub_3B79A0
// (sub_34FE80). "mdlHandle not found!" / "effect Handle not found!" for a missing object.
void sub_3B7460(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x003b7460
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v1 = 0x6A0000;
    ld(a0, v1, 11552);  // 0x6A2D20
    v1 = 0x6A0000;
    lwc1(f0, v1, 11560);  // 0x6A2D28
    sd(a0, sp, 0xE0);
    swc1(f0, sp, 0xE8);
    v1 = 0x6A0000;
    ld(a0, v1, 11568);  // 0x6A2D30
    v1 = 0x6A0000;
    lwc1(f0, v1, 11576);  // 0x6A2D38
    sd(a0, sp, 0xD0);
    swc1(f0, sp, 0xD8);
    v1 = 0x6A0000;
    ld(a0, v1, 11584);  // 0x6A2D40
    v1 = 0x6A0000;
    lwc1(f0, v1, 11592);  // 0x6A2D48
    sd(a0, sp, 0xC0);
    swc1(f0, sp, 0xC8);
    v1 = 0x6A0000;
    ld(a0, v1, 11600);  // 0x6A2D50
    v1 = 0x6A0000;
    lwc1(f0, v1, 11608);  // 0x6A2D58
    sd(a0, sp, 0xB0);
    swc1(f0, sp, 0xB8);
    if (s0 != 0) {
        // 0x003b74dc
        charge(ctx, 2);
        if (a1 != 0) {
            // 0x003b74e4
            charge(ctx, 6);
            lwc1(f2, a1, 0);
            lwc1(f1, a1, 4);
            lwc1(f0, a1, 8);
            swc1(f2, s0, res::kPos);
            swc1(f1, s0, res::kPosY);
            swc1(f0, s0, res::kPosZ);
        }
        // 0x003b74fc
        charge(ctx, 2);
        if (a2 != 0) {
            // 0x003b7504
            charge(ctx, 6);
            lwc1(f2, a2, 0);
            lwc1(f1, a2, 4);
            lwc1(f0, a2, 8);
            swc1(f2, s0, res::kRot);
            swc1(f1, s0, res::kRotY);
            swc1(f0, s0, res::kRotZ);
        }
        // 0x003b751c
        charge(ctx, 2);
        if (a3 != 0) {
            // 0x003b7524
            charge(ctx, 6);
            lwc1(f2, a3, 0);
            lwc1(f1, a3, 4);
            lwc1(f0, a3, 8);
            swc1(f2, s0, res::kScale);
            swc1(f1, s0, res::kScaleY);
            swc1(f0, s0, res::kScaleZ);
        }
        // 0x003b753c
        charge(ctx, 14);
        lwc1(f2, s0, res::kScale);
        lwc1(f1, s0, res::kScaleY);
        lwc1(f0, s0, res::kScaleZ);
        swc1(f2, sp, 0xB0);
        swc1(f1, sp, 0xB4);
        swc1(f0, sp, 0xB8);
        lhu(a0, s0, res::kId);
        v1 = 0xF0000;
        v1 = v1 | 0xFC00;
        v1 = a0 & v1;
        a0 = sra(v1, 10);
        v1 = 10;
        if (a0 == v1) {
            // 0x003b7800
            charge(ctx, 3);
            lw(s1, s0, 260);
            if (s1 != 0) {
                // 0x003b7824
                charge(ctx, 28);
                a0 = s1;
                a1 = addiu(sp, 0xE0);
                lwc1(f12, s0, res::kRotY);
                a2 = 0;
                jal(ctx, 0x3B7834u, gen::fn_sub_318A50_00318a50);
                a0 = s1;
                a1 = addiu(sp, 0xD0);
                lwc1(f12, s0, res::kRot);
                a2 = 1;
                jal(ctx, 0x3B784Cu, gen::fn_sub_318A50_00318a50);
                a0 = s1;
                a1 = addiu(sp, 0xC0);
                lwc1(f12, s0, res::kRotZ);
                a2 = 1;
                jal(ctx, 0x3B7864u, gen::fn_sub_318A50_00318a50);
                a0 = s1;
                a1 = addiu(sp, 0xB0);
                a2 = 2;
                jal(ctx, 0x3B7878u, gen::fn_sub_318A90_00318a90);
                a0 = s1;
                a1 = addiu(s0, 4);
                a2 = 2;
                jal(ctx, 0x3B788Cu, gen::fn_sub_318A30_00318a30);
            } else {
                // 0x003b780c
                charge(ctx, 6);
                a0 = 0x6A0000;
                a0 = addiu(a0, 11616);  // "mdlHandle not found!\n"
                jal(ctx, 0x3B7814u, gen::fn_printf_005225a8);
            }
        } else {
            // 0x003b7574
            charge(ctx, 3);
            v1 = 6;
            if (a0 == v1) {
                // 0x003b7780
                charge(ctx, 3);
                lw(v0, s0, 260);
                if (v0 != 0) {
                    // 0x003b77a4
                    charge(ctx, 8);
                    a0 = addiu(sp, 0x30);
                    a1 = addiu(s0, 4);
                    a2 = addiu(s0, 16);
                    jal(ctx, 0x3B77B0u, gen::fn_sub_3B79A0_003b79a0);
                    a2 = addiu(sp, 0x30);
                    a1 = addiu(sp, 0x70);
                    a0 = 8;
                    for (;;) {
                        // 0x003b77c4
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
                    // 0x003b77e8
                    charge(ctx, 6);
                    lw(a0, s0, 260);
                    a1 = addiu(sp, 0x70);
                    jal(ctx, 0x3B77F0u, gen::fn_sub_34FE80_0034fe80);
                } else {
                    // 0x003b778c
                    charge(ctx, 6);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 11648);  // "effect Handle not found!\n"
                    jal(ctx, 0x3B7794u, gen::fn_printf_005225a8);
                }
            } else {
                // 0x003b7580
                charge(ctx, 3);
                v1 = 3;
                if (a0 == v1) {
                    // 0x003b76e4
                    charge(ctx, 3);
                    lw(s1, s0, 296);
                    if (s1 != 0) {
                        // 0x003b7708
                        charge(ctx, 30);
                        a0 = s1;
                        a1 = addiu(sp, 0xE0);
                        lwc1(f12, s0, res::kRotY);
                        a2 = 0;
                        jal(ctx, 0x3B7718u, gen::fn_sub_318A50_00318a50);
                        a0 = s1;
                        a1 = addiu(sp, 0xD0);
                        lwc1(f12, s0, res::kRot);
                        a2 = 1;
                        jal(ctx, 0x3B7730u, gen::fn_sub_318A50_00318a50);
                        a0 = s1;
                        a1 = addiu(sp, 0xC0);
                        lwc1(f12, s0, res::kRotZ);
                        a2 = 1;
                        jal(ctx, 0x3B7748u, gen::fn_sub_318A50_00318a50);
                        a0 = s1;
                        a1 = addiu(sp, 0xB0);
                        a2 = 2;
                        jal(ctx, 0x3B775Cu, gen::fn_sub_318A90_00318a90);
                        a0 = s1;
                        a1 = addiu(s0, 4);
                        a2 = 2;
                        jal(ctx, 0x3B7770u, gen::fn_sub_318A30_00318a30);
                    } else {
                        // 0x003b76f0
                        charge(ctx, 6);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, 11616);  // "mdlHandle not found!\n"
                        jal(ctx, 0x3B76F8u, gen::fn_printf_005225a8);
                    }
                } else {
                    // 0x003b758c
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 == v1) {
                        // 0x003b7648
                        charge(ctx, 3);
                        lw(s1, s0, 280);
                        if (s1 != 0) {
                            // 0x003b766c
                            charge(ctx, 30);
                            a0 = s1;
                            a1 = addiu(sp, 0xE0);
                            lwc1(f12, s0, res::kRotY);
                            a2 = 0;
                            jal(ctx, 0x3B767Cu, gen::fn_sub_318A50_00318a50);
                            a0 = s1;
                            a1 = addiu(sp, 0xD0);
                            lwc1(f12, s0, res::kRot);
                            a2 = 1;
                            jal(ctx, 0x3B7694u, gen::fn_sub_318A50_00318a50);
                            a0 = s1;
                            a1 = addiu(sp, 0xC0);
                            lwc1(f12, s0, res::kRotZ);
                            a2 = 1;
                            jal(ctx, 0x3B76ACu, gen::fn_sub_318A50_00318a50);
                            a0 = s1;
                            a1 = addiu(sp, 0xB0);
                            a2 = 2;
                            jal(ctx, 0x3B76C0u, gen::fn_sub_318A90_00318a90);
                            a0 = s1;
                            a1 = addiu(s0, 4);
                            a2 = 2;
                            jal(ctx, 0x3B76D4u, gen::fn_sub_318A30_00318a30);
                        } else {
                            // 0x003b7654
                            charge(ctx, 6);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, 11616);  // "mdlHandle not found!\n"
                            jal(ctx, 0x3B765Cu, gen::fn_printf_005225a8);
                        }
                    } else {
                        // 0x003b7598
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x003b75ac
                            charge(ctx, 3);
                            lw(s1, s0, 296);
                            if (s1 != 0) {
                                // 0x003b75d0
                                charge(ctx, 30);
                                a0 = s1;
                                a1 = addiu(sp, 0xE0);
                                lwc1(f12, s0, res::kRotY);
                                a2 = 0;
                                jal(ctx, 0x3B75E0u, gen::fn_sub_318A50_00318a50);
                                a0 = s1;
                                a1 = addiu(sp, 0xD0);
                                lwc1(f12, s0, res::kRot);
                                a2 = 1;
                                jal(ctx, 0x3B75F8u, gen::fn_sub_318A50_00318a50);
                                a0 = s1;
                                a1 = addiu(sp, 0xC0);
                                lwc1(f12, s0, res::kRotZ);
                                a2 = 1;
                                jal(ctx, 0x3B7610u, gen::fn_sub_318A50_00318a50);
                                a0 = s1;
                                a1 = addiu(sp, 0xB0);
                                a2 = 2;
                                jal(ctx, 0x3B7624u, gen::fn_sub_318A90_00318a90);
                                a0 = s1;
                                a1 = addiu(s0, 4);
                                a2 = 2;
                                jal(ctx, 0x3B7638u, gen::fn_sub_318A30_00318a30);
                            } else {
                                // 0x003b75b8
                                charge(ctx, 6);
                                a0 = 0x6A0000;
                                a0 = addiu(a0, 11616);  // "mdlHandle not found!\n"
                                jal(ctx, 0x3B75C0u, gen::fn_printf_005225a8);
                            }
                        } else {
                            // 0x003b75a4
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
    }
    // 0x003b7894 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xF0);
}

// 0x003B78B0 sub_3B78B0 -- 124 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_Scene_SetResPosRot] (id, pos, rot) Finds the scene resource and applies a position and rotation (sub_3B7460,
// scale kept).
void sub_3B78B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b78b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a3 = a0;
    s1 = a1;
    s0 = a2;
    lw(v1, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v1, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b78e8
        charge(ctx, 4);
        a1 = a3;
        jal(ctx, 0x3B78ECu, gen::fn_sub_3B54C0_003b54c0);
        a0 = v0;
    } else {
        // 0x003b78dc
        charge(ctx, 3);
        a0 = 0;
    }
    // 0x003b78f8
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x003b7900
        charge(ctx, 5);
        a1 = s1;
        a2 = s0;
        a3 = 0;
        jal(ctx, 0x3B790Cu, gen::fn_sub_3B7460_003b7460);
    }
    // 0x003b7914 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003B7930 sub_3B7930 -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [MT_Scene_SetResScale] (id, scale) Finds the scene resource and applies a scale (sub_3B7460).
void sub_3B7930(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b7930
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a2 = a0;
    s0 = a1;
    lw(v1, gp, g::kGpSceneRecord);  // 0x7CD540 -> the scene record 0x95AFC0
    lw(a0, v1, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b7960
        charge(ctx, 4);
        a1 = a2;
        jal(ctx, 0x3B7964u, gen::fn_sub_3B54C0_003b54c0);
        a0 = v0;
    } else {
        // 0x003b7954
        charge(ctx, 3);
        a0 = 0;
    }
    // 0x003b7970
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x003b7978
        charge(ctx, 5);
        a1 = 0;
        a2 = 0;
        a3 = s0;
        jal(ctx, 0x3B7984u, gen::fn_sub_3B7460_003b7460);
    }
    // 0x003b798c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B79A0 sub_3B79A0 -- 280 bytes; frame 0x80: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MT_Scene_RotMatrix] (out, pos, rot) A 64-byte RW matrix: the identity rotated about y by rot.y, x by rot.x, z by
// rot.z (degrees; the axes 0x6A2A70 / 0x6A2A60 / 0x6A2A80, sub_4C31B0 pre-concatenated), translated by pos
// (sub_4C35D0, post-concatenated), copied to `out`.
void sub_3B79A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003b79a0
    enter(ctx, 54);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    v0 = 0x3F800000;
    sw(v0, sp, 0x68);
    sw(v0, sp, 0x54);
    sw(v0, sp, 0x40);
    sw(zero, sp, 0x50);
    sw(zero, sp, 0x48);
    sw(zero, sp, 0x44);
    sw(zero, sp, 0x64);
    sw(zero, sp, 0x60);
    sw(zero, sp, 0x58);
    sw(zero, sp, 0x78);
    sw(zero, sp, 0x74);
    sw(zero, sp, 0x70);
    lw(v1, sp, 0x4C);
    v0 = 0x20000;
    v0 = v0 | 0x3;
    v0 = v1 | v0;
    sw(v0, sp, 0x4C);
    a0 = addiu(sp, 0x40);
    a1 = 0x6A0000;
    a1 = addiu(a1, 10864);  // &0x6A2A70
    lwc1(f12, a2, 4);
    a2 = 1;
    jal(ctx, 0x3B7A1Cu, gen::fn_sub_4C31B0_004c31b0);
    a0 = addiu(sp, 0x40);
    a1 = 0x6A0000;
    a1 = addiu(a1, 10848);  // &0x6A2A60
    lwc1(f12, s0, 0);
    a2 = 1;
    jal(ctx, 0x3B7A38u, gen::fn_sub_4C31B0_004c31b0);
    a0 = addiu(sp, 0x40);
    a1 = 0x6A0000;
    a1 = addiu(a1, 10880);  // &0x6A2A80
    lwc1(f12, s0, 8);
    a2 = 1;
    jal(ctx, 0x3B7A54u, gen::fn_sub_4C31B0_004c31b0);
    a0 = addiu(sp, 0x40);
    a1 = s1;
    a2 = 2;
    jal(ctx, 0x3B7A68u, gen::fn_sub_4C35D0_004c35d0);
    a2 = addiu(sp, 0x40);
    a1 = 8;
    for (;;) {
        // 0x003b7a78
        charge(ctx, 9);
        lw(a0, a2, 0);
        lw(v1, a2, 4);
        a2 = addiu(a2, 8);
        a1 = addiu(a1, -1);
        sw(a0, s2, 0);
        sw(v1, s2, 4);
        s2 = addiu(s2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003b7a9c
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x003B7AC0 sub_3B7AC0 -- 1872 bytes; frame 0x2F0: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [MT_Scene_MatrixToEuler] (matrix, out_angles, out_pos) Splits a matrix into its position (out_pos) and three angles
// in degrees: the rotation about z from the right vector against the projected axes (sign from +4), about y from the
// at vector's xz direction (360 - a when x < 0), about x from the at vector rotated back; asserts (mt_scene.c
// 1525..1645) on zero-length normalisations.
void sub_3B7AC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x003b7ac0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2F0);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s3 = a1;
    a3 = addiu(sp, 0x220);
    a1 = 8;
    for (;;) {
        // 0x003b7aec
        charge(ctx, 9);
        lw(v1, a0, 0);
        lw(v0, a0, 4);
        a0 = addiu(a0, 8);
        a1 = addiu(a1, -1);
        sw(v1, a3, 0);
        sw(v0, a3, 4);
        a3 = addiu(a3, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003b7b10
    charge(ctx, 30);
    v0 = addiu(sp, 0x250);
    lwc1(f2, v0, 0);
    lwc1(f1, v0, 4);
    lwc1(f0, v0, 8);
    swc1(f2, a2, 0);
    swc1(f1, a2, 4);
    swc1(f0, a2, 8);
    sw(zero, v0, 0);
    sw(zero, v0, 4);
    sw(zero, v0, 8);
    s2 = addiu(sp, 0x220);
    s1 = addiu(sp, 0x230);
    s0 = addiu(sp, 0x240);
    sw(zero, sp, 0x2E0);
    v0 = 0x3F800000;
    sw(v0, sp, 0x2E4);
    sw(zero, sp, 0x2E8);
    a0 = addiu(sp, 0x2E0);
    a1 = addiu(sp, 0x2B0);
    ld(v0, sp, 0x2E0);
    lwc1(f0, sp, 0x2E8);
    sd(v0, sp, 0x2B0);
    swc1(f0, sp, 0x2B8);
    jal(ctx, 0x3B7B6Cu, gen::fn_sub_4C69F0_004c69f0);
    mtc1(zero, f1);
    c_eq_s(f1, f0);
    if (cond(ctx)) {
        // 0x003b7b88
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11240);  // "mt_scene.c"
        a1 = 1525;
        jal(ctx, 0x3B7B94u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b7b9c
    charge(ctx, 28);
    lwc1(f6, sp, 0x2E4);
    lwc1(f5, sp, 0x2E8);
    lwc1(f4, s0, 8);
    lwc1(f3, s0, 4);
    mula_s(f3, f5);
    msub_s(f0, f4, f6);
    swc1(f0, sp, 0x2C0);
    lwc1(f2, sp, 0x2E0);
    lwc1(f1, s0, 0);
    mula_s(f4, f2);
    msub_s(f0, f1, f5);
    swc1(f0, sp, 0x2C4);
    mula_s(f1, f6);
    msub_s(f0, f3, f2);
    swc1(f0, sp, 0x2C8);
    a0 = addiu(sp, 0x2C0);
    a1 = addiu(sp, 0x2B0);
    ld(v0, sp, 0x2C0);
    lwc1(f0, sp, 0x2C8);
    sd(v0, sp, 0x2B0);
    swc1(f0, sp, 0x2B8);
    jal(ctx, 0x3B7BF0u, gen::fn_sub_4C69F0_004c69f0);
    mtc1(zero, f1);
    c_eq_s(f1, f0);
    if (cond(ctx)) {
        // 0x003b7c0c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11240);  // "mt_scene.c"
        a1 = 1529;
        jal(ctx, 0x3B7C18u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b7c20
    charge(ctx, 28);
    lwc1(f6, sp, 0x2C8);
    lwc1(f5, sp, 0x2C4);
    lwc1(f4, s0, 4);
    lwc1(f3, s0, 8);
    mula_s(f5, f3);
    msub_s(f0, f6, f4);
    swc1(f0, sp, 0x290);
    lwc1(f2, sp, 0x2C0);
    lwc1(f1, s0, 0);
    mula_s(f6, f1);
    msub_s(f0, f2, f3);
    swc1(f0, sp, 0x294);
    mula_s(f2, f4);
    msub_s(f0, f5, f1);
    swc1(f0, sp, 0x298);
    a0 = addiu(sp, 0x290);
    a1 = addiu(sp, 0x2B0);
    ld(v0, sp, 0x290);
    lwc1(f0, sp, 0x298);
    sd(v0, sp, 0x2B0);
    swc1(f0, sp, 0x2B8);
    jal(ctx, 0x3B7C74u, gen::fn_sub_4C69F0_004c69f0);
    mtc1(zero, f1);
    c_eq_s(f1, f0);
    if (cond(ctx)) {
        // 0x003b7c90
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11240);  // "mt_scene.c"
        a1 = 1533;
        jal(ctx, 0x3B7C9Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b7ca4
    charge(ctx, 23);
    ld(v0, sp, 0x290);
    lwc1(f0, sp, 0x298);
    sd(v0, sp, 0x2A0);
    swc1(f0, sp, 0x2A8);
    lwc1(f1, s1, 0);
    lwc1(f0, sp, 0x2A0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x280);
    lwc1(f21, sp, 0x2A4);
    lwc1(f0, s1, 4);
    sub_s(f0, f0, f21);
    swc1(f0, sp, 0x284);
    lwc1(f20, sp, 0x2A8);
    lwc1(f0, s1, 8);
    sub_s(f0, f0, f20);
    swc1(f0, sp, 0x288);
    a0 = addiu(sp, 0x280);
    jal(ctx, 0x3B7CE8u, gen::fn_sub_4C6AC0_004c6ac0);
    lwc1(f1, gp, -32204);  // 0x7CAF24
    c_le_s(f0, f1);
    if (!cond(ctx)) {
        // 0x003b7d0c
        charge(ctx, 11);
        lwc1(f3, s1, 8);
        lwc1(f2, s1, 0);
        lwc1(f1, sp, 0x2A0);
        lwc1(f0, s1, 4);
        mula_s(f0, f21);
        madda_s(f2, f1);
        madd_s(f12, f3, f20);
        jal(ctx, 0x3B7D28u, gen::fn_acosf_0052e9e8);
        lwc1(f1, gp, -32188);  // 0x7CAF34
        mul_s(f20, f1, f0);
    } else {
        // 0x003b7d00
        charge(ctx, 3);
        mtc1(zero, f20);
    }
    // 0x003b7d38
    charge(ctx, 6);
    lwc1(f1, s2, 4);
    mtc1(zero, f0);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        // 0x003b7d50
        charge(ctx, 4);
        v0 = lui(0xBF80);
        mtc1(v0, f0);
        mul_s(f20, f20, f0);
    }
    // 0x003b7d60
    charge(ctx, 53);
    v0 = 0x3F800000;
    sw(v0, sp, 0x208);
    sw(v0, sp, 0x1F4);
    sw(v0, sp, 0x1E0);
    sw(zero, sp, 0x1F0);
    sw(zero, sp, 0x1E8);
    sw(zero, sp, 0x1E4);
    sw(zero, sp, 0x204);
    sw(zero, sp, 0x200);
    sw(zero, sp, 0x1F8);
    sw(zero, sp, 0x218);
    sw(zero, sp, 0x214);
    sw(zero, sp, 0x210);
    lw(v1, sp, 0x1EC);
    v0 = 0x20000;
    v0 = v0 | 0x3;
    v0 = v1 | v0;
    sw(v0, sp, 0x1EC);
    a0 = addiu(sp, 0x1E0);
    a1 = 0x6A0000;
    a1 = addiu(a1, 10880);  // &0x6A2A80
    mov_s(f12, f20);
    a2 = 1;
    jal(ctx, 0x3B7DBCu, gen::fn_sub_4C31B0_004c31b0);
    a0 = addiu(sp, 0x1A0);
    a1 = addiu(sp, 0x1E0);
    jal(ctx, 0x3B7DCCu, gen::fn_sub_4C32A0_004c32a0);
    a0 = addiu(sp, 0x160);
    a1 = addiu(sp, 0x1A0);
    a2 = addiu(sp, 0x220);
    jal(ctx, 0x3B7DE0u, gen::fn_sub_4C2F30_004c2f30);
    s0 = addiu(sp, 0x180);
    lwc1(f0, s0, 0);
    swc1(f0, sp, 0x2E0);
    sw(zero, sp, 0x2E4);
    lwc1(f0, s0, 8);
    swc1(f0, sp, 0x2E8);
    a0 = addiu(sp, 0x2E0);
    a1 = addiu(sp, 0x2B0);
    ld(v0, sp, 0x2E0);
    lwc1(f0, sp, 0x2E8);
    sd(v0, sp, 0x2B0);
    swc1(f0, sp, 0x2B8);
    jal(ctx, 0x3B7E18u, gen::fn_sub_4C69F0_004c69f0);
    mtc1(zero, f1);
    c_eq_s(f1, f0);
    if (cond(ctx)) {
        // 0x003b7e34
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11240);  // "mt_scene.c"
        a1 = 1587;
        jal(ctx, 0x3B7E40u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b7e48
    charge(ctx, 19);
    a0 = addiu(sp, 0x2D0);
    lwc1(f2, s0, 0);
    lwc1(f1, s0, 4);
    lwc1(f0, s0, 8);
    swc1(f2, sp, 0x2D0);
    swc1(f1, sp, 0x2D4);
    swc1(f0, sp, 0x2D8);
    a1 = addiu(sp, 0x2B0);
    ld(v0, sp, 0x2D0);
    lwc1(f0, sp, 0x2D8);
    sd(v0, sp, 0x2B0);
    swc1(f0, sp, 0x2B8);
    jal(ctx, 0x3B7E78u, gen::fn_sub_4C69F0_004c69f0);
    mtc1(zero, f1);
    c_eq_s(f1, f0);
    if (cond(ctx)) {
        // 0x003b7e94
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11240);  // "mt_scene.c"
        a1 = 1591;
        jal(ctx, 0x3B7EA0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b7ea8
    charge(ctx, 19);
    lwc1(f1, sp, 0x2D0);
    lwc1(f0, sp, 0x2E0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x270);
    lwc1(f1, sp, 0x2D4);
    lwc1(f0, sp, 0x2E4);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x274);
    lwc1(f1, sp, 0x2D8);
    lwc1(f0, sp, 0x2E8);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x278);
    a0 = addiu(sp, 0x270);
    jal(ctx, 0x3B7EDCu, gen::fn_sub_4C6AC0_004c6ac0);
    lwc1(f1, gp, -32204);  // 0x7CAF24
    c_le_s(f0, f1);
    if (!cond(ctx)) {
        // 0x003b7f00
        charge(ctx, 13);
        lwc1(f5, sp, 0x2D8);
        lwc1(f4, sp, 0x2E8);
        lwc1(f3, sp, 0x2D0);
        lwc1(f2, sp, 0x2E0);
        lwc1(f1, sp, 0x2D4);
        lwc1(f0, sp, 0x2E4);
        mula_s(f1, f0);
        madda_s(f3, f2);
        madd_s(f12, f5, f4);
        jal(ctx, 0x3B7F24u, gen::fn_acosf_0052e9e8);
        lwc1(f1, gp, -32188);  // 0x7CAF34
        mul_s(f21, f1, f0);
    } else {
        // 0x003b7ef4
        charge(ctx, 3);
        mtc1(zero, f21);
    }
    // 0x003b7f34
    charge(ctx, 6);
    lwc1(f1, s0, 4);
    mtc1(zero, f0);
    c_le_s(f1, f0);
    if (!cond(ctx)) {
        // 0x003b7f4c
        charge(ctx, 4);
        v0 = lui(0xBF80);
        mtc1(v0, f0);
        mul_s(f21, f21, f0);
    }
    // 0x003b7f5c
    charge(ctx, 86);
    v0 = 0x3F800000;
    sw(v0, sp, 0x148);
    sw(v0, sp, 0x134);
    sw(v0, sp, 0x120);
    sw(zero, sp, 0x130);
    sw(zero, sp, 0x128);
    sw(zero, sp, 0x124);
    sw(zero, sp, 0x144);
    sw(zero, sp, 0x140);
    sw(zero, sp, 0x138);
    sw(zero, sp, 0x158);
    sw(zero, sp, 0x154);
    sw(zero, sp, 0x150);
    lw(v1, sp, 0x12C);
    v0 = 0x20000;
    v0 = v0 | 0x3;
    v0 = v1 | v0;
    sw(v0, sp, 0x12C);
    a0 = addiu(sp, 0x120);
    a1 = 0x6A0000;
    a1 = addiu(a1, 10880);  // &0x6A2A80
    mov_s(f12, f20);
    a2 = 1;
    jal(ctx, 0x3B7FB8u, gen::fn_sub_4C31B0_004c31b0);
    a0 = addiu(sp, 0xE0);
    a1 = addiu(sp, 0x120);
    jal(ctx, 0x3B7FC8u, gen::fn_sub_4C32A0_004c32a0);
    a0 = addiu(sp, 0xA0);
    a1 = addiu(sp, 0xE0);
    a2 = addiu(sp, 0x220);
    jal(ctx, 0x3B7FDCu, gen::fn_sub_4C2F30_004c2f30);
    v0 = 0x3F800000;
    sw(v0, sp, 0x148);
    sw(v0, sp, 0x134);
    sw(v0, sp, 0x120);
    sw(zero, sp, 0x130);
    sw(zero, sp, 0x128);
    sw(zero, sp, 0x124);
    sw(zero, sp, 0x144);
    sw(zero, sp, 0x140);
    sw(zero, sp, 0x138);
    sw(zero, sp, 0x158);
    sw(zero, sp, 0x154);
    sw(zero, sp, 0x150);
    lw(v1, sp, 0x12C);
    v0 = 0x20000;
    v0 = v0 | 0x3;
    v0 = v1 | v0;
    sw(v0, sp, 0x12C);
    a0 = addiu(sp, 0x120);
    a1 = 0x6A0000;
    a1 = addiu(a1, 10848);  // &0x6A2A60
    mov_s(f12, f21);
    a2 = 1;
    jal(ctx, 0x3B8040u, gen::fn_sub_4C31B0_004c31b0);
    a0 = addiu(sp, 0xE0);
    a1 = addiu(sp, 0x120);
    jal(ctx, 0x3B8050u, gen::fn_sub_4C32A0_004c32a0);
    a0 = addiu(sp, 0x60);
    a1 = addiu(sp, 0xE0);
    a2 = addiu(sp, 0xA0);
    jal(ctx, 0x3B8064u, gen::fn_sub_4C2F30_004c2f30);
    s0 = addiu(sp, 0x80);
    sw(zero, sp, 0x2E0);
    sw(zero, sp, 0x2E4);
    v0 = 0x3F800000;
    sw(v0, sp, 0x2E8);
    a0 = addiu(sp, 0x2E0);
    a1 = addiu(sp, 0x2B0);
    ld(v0, sp, 0x2E0);
    lwc1(f0, sp, 0x2E8);
    sd(v0, sp, 0x2B0);
    swc1(f0, sp, 0x2B8);
    jal(ctx, 0x3B8098u, gen::fn_sub_4C69F0_004c69f0);
    mtc1(zero, f1);
    c_eq_s(f1, f0);
    if (cond(ctx)) {
        // 0x003b80b4
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11240);  // "mt_scene.c"
        a1 = 1641;
        jal(ctx, 0x3B80C0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b80c8
    charge(ctx, 19);
    a0 = addiu(sp, 0x2D0);
    lwc1(f2, s0, 0);
    lwc1(f1, s0, 4);
    lwc1(f0, s0, 8);
    swc1(f2, sp, 0x2D0);
    swc1(f1, sp, 0x2D4);
    swc1(f0, sp, 0x2D8);
    a1 = addiu(sp, 0x2B0);
    ld(v0, sp, 0x2D0);
    lwc1(f0, sp, 0x2D8);
    sd(v0, sp, 0x2B0);
    swc1(f0, sp, 0x2B8);
    jal(ctx, 0x3B80F8u, gen::fn_sub_4C69F0_004c69f0);
    mtc1(zero, f1);
    c_eq_s(f1, f0);
    if (cond(ctx)) {
        // 0x003b8114
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11240);  // "mt_scene.c"
        a1 = 1645;
        jal(ctx, 0x3B8120u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b8128
    charge(ctx, 19);
    lwc1(f1, sp, 0x2D0);
    lwc1(f0, sp, 0x2E0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x260);
    lwc1(f1, sp, 0x2D4);
    lwc1(f0, sp, 0x2E4);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x264);
    lwc1(f1, sp, 0x2D8);
    lwc1(f0, sp, 0x2E8);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x268);
    a0 = addiu(sp, 0x260);
    jal(ctx, 0x3B815Cu, gen::fn_sub_4C6AC0_004c6ac0);
    lwc1(f1, gp, -32204);  // 0x7CAF24
    c_le_s(f0, f1);
    if (!cond(ctx)) {
        // 0x003b8180
        charge(ctx, 13);
        lwc1(f5, sp, 0x2D8);
        lwc1(f4, sp, 0x2E8);
        lwc1(f3, sp, 0x2D0);
        lwc1(f2, sp, 0x2E0);
        lwc1(f1, sp, 0x2D4);
        lwc1(f0, sp, 0x2E4);
        mula_s(f1, f0);
        madda_s(f3, f2);
        madd_s(f12, f5, f4);
        jal(ctx, 0x3B81A4u, gen::fn_acosf_0052e9e8);
        lwc1(f1, gp, -32188);  // 0x7CAF34
        mul_s(f2, f1, f0);
    } else {
        // 0x003b8174
        charge(ctx, 3);
        mtc1(zero, f2);
    }
    // 0x003b81b4
    charge(ctx, 6);
    lwc1(f1, sp, 0x2D0);
    mtc1(zero, f0);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        // 0x003b81cc
        charge(ctx, 4);
        v1 = 0x43B40000;
        mtc1(v1, f0);
        sub_s(f2, f0, f2);
    }
    // 0x003b81dc (the shared epilogue, written out on this path)
    charge(ctx, 13);
    swc1(f21, s3, 0);
    swc1(f2, s3, 4);
    swc1(f20, s3, 8);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x2F0);
}

}  // namespace p3fes::game
