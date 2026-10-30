// Phase 5 slice field7, part 4 (field7_ud.h): the RpUserData frame searches of the 0x1A0000 band (the int entries the
// models' "per3HelperId" and the field objects' "per3FieldObject*" arrays carry). Started from p3fes_handgen's bodies
// (register for register, block for block as the recompiled ones; game/include/p3fes/game/hg_cpu.h) and made readable
// on top: a role comment per function, named record offsets, structured control flow (the early exits of the nested
// searches as a host flag after the loops: each path keeps its statements, charges and check points in order).
// tests/game/test_field7_ud.cpp pairs them.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/field7_ud.h"

namespace p3fes::recomp_gen {
void fn_memset_00521408(p3fes::EEContext&);
void fn_name__C9type_info_0_0048ef10(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_sub_1A69A0_001a69a0(p3fes::EEContext&);
void fn_sub_1A6AF0_001a6af0(p3fes::EEContext&);
void fn_sub_1A6D20_001a6d20(p3fes::EEContext&);
void fn_sub_1A6E90_001a6e90(p3fes::EEContext&);
void fn_sub_48EDE0_0048ede0(p3fes::EEContext&);
void fn_sub_48EE30_0048ee30(p3fes::EEContext&);
void fn_sub_48EF20_0048ef20(p3fes::EEContext&);
void fn_sub_48EF30_0048ef30(p3fes::EEContext&);
void fn_sub_48EF40_0048ef40(p3fes::EEContext&);
void fn_sub_4CB6E0_004cb6e0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace f7::ud;

// 0x001A69A0 sub_1A69A0 -- 324 bytes; frame 0xB0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq), s0 sp+0xA4
// sub_1A69A0(clump, name, id) [K_Clump_FindFrameByUserId]: the frame of the clump's hierarchy that carries an int
// user-data entry `name` (RpUserData: sub_48EDE0 count, sub_48EE30 n-th array, sub_48EF10 its name, sub_48EF20 its
// format, 1 = int, sub_48EF30 entries, sub_48EF40 the n-th int) with the value `id`: the root frame (clump +4) is
// searched here, its descendants by RwFrameForAllChildren (sub_4CB6E0) with the callback sub_1A6860 on a stack
// record {name[64], result +64, id +68}. Returns the frame, or 0. The models' helper lookups (mdlModelGetHelperPos /
// Matrix) ask for "per3HelperId".
void sub_1A69A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a69a0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a2;
    lw(s1, a0, 4);  // s1 = the clump's root frame
    a0 = addiu(sp, 0x60);  // the record's name (a1 = name)
    jal(ctx, 0x1A69C8u, gen::fn_strcpy_00524270);
    sw(zero, sp, 0xA0);  // record +64: the frame found
    sw(s0, sp, 0xA4);    // record +68: the id
    s3 = 0;              // s3 = array index
    bool found = false;  // the root frame holds it (the original's exit block 0x1a6a5c)
    for (;;) {
        // 0x001a6a8c
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x1A6A90u, gen::fn_sub_48EDE0_0048ede0);
        v0 = slt(s3, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001a69e4
        charge(ctx, 14);
        a0 = s1;
        a1 = s3;
        jal(ctx, 0x1A69ECu, gen::fn_sub_48EE30_0048ee30);
        s0 = v0;
        a0 = s0;
        jal(ctx, 0x1A69FCu, gen::fn_name__C9type_info_0_0048ef10);
        a0 = v0;
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x1A6A0Cu, gen::fn_strcmp_00524128);
        if (v0 == 0) {
            // 0x001a6a1c
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x001a6a70
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x1A6A74u, gen::fn_sub_48EF30_0048ef30);
                v0 = slt(s2, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001a6a28
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x1A6A2Cu, gen::fn_sub_48EF20_0048ef20);
                v1 = 1;
                if (v0 == v1) {
                    // 0x001a6a40
                    charge(ctx, 7);
                    lw(s4, sp, 0xA4);
                    a0 = s0;
                    a1 = s2;
                    jal(ctx, 0x1A6A4Cu, gen::fn_sub_48EF40_0048ef40);
                    if (s4 == v0) {
                        found = true;
                        break;
                    }
                }
                // 0x001a6a6c
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            if (found) {
                break;
            }
        }
        // 0x001a6a88
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    if (found) {
        // 0x001a6a5c: the root frame
        charge(ctx, 4);
        sw(s1, sp, 0xA0);
        v0 = s1;
    } else {
        // 0x001a6aa4: the descendants (RwFrameForAllChildren with sub_1A6860), then the record's result
        charge(ctx, 7);
        a0 = s1;
        a1 = 0x1A0000;
        a1 = addiu(a1, 26720);  // &sub_1A6860
        a2 = addiu(sp, 0x60);
        jal(ctx, 0x1A6AB4u, gen::fn_sub_4CB6E0_004cb6e0);
        lw(v0, sp, 0xA0);
    }
    // 0x001a6ac0 (the epilogue)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x001A6AF0 sub_1A6AF0 -- 272 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A6AF0(frame, record) [K_Frame_CountUserInts]: an RwFrameForAllChildren callback: adds the number of int
// entries of the frame's user-data arrays named record->name to record +64, then recurses into the children with
// itself. Returns the frame (the walk goes on).
void sub_1A6AF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a6af0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = 0;
    for (;;) {
        // 0x001a6ba8
        charge(ctx, 6);
        a0 = s4;
        jal(ctx, 0x1A6BACu, gen::fn_sub_48EDE0_0048ede0);
        v0 = slt(s2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001a6b20
        charge(ctx, 14);
        a0 = s4;
        a1 = s2;
        jal(ctx, 0x1A6B28u, gen::fn_sub_48EE30_0048ee30);
        s0 = v0;
        a0 = s0;
        jal(ctx, 0x1A6B38u, gen::fn_name__C9type_info_0_0048ef10);
        a0 = v0;
        a1 = s3;
        jal(ctx, 0x1A6B48u, gen::fn_strcmp_00524128);
        if (v0 == 0) {
            // 0x001a6b58
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x001a6b8c
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x1A6B90u, gen::fn_sub_48EF30_0048ef30);
                v0 = slt(s1, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001a6b64
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x1A6B68u, gen::fn_sub_48EF20_0048ef20);
                v1 = 1;
                if (v0 == v1) {
                    // 0x001a6b7c
                    charge(ctx, 3);
                    lw(v0, s3, kRecTotal);
                    v0 = addiu(v0, 1);
                    sw(v0, s3, kRecTotal);
                }
                // 0x001a6b88
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
        }
        // 0x001a6ba4
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x001a6bc0
    charge(ctx, 16);
    a0 = s4;
    a1 = 0x1A0000;
    a1 = addiu(a1, 27376);  // &sub_1A6AF0
    a2 = s3;
    jal(ctx, 0x1A6BD0u, gen::fn_sub_4CB6E0_004cb6e0);
    v0 = s4;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001A6D20 sub_1A6D20 -- 356 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A6D20(frame, record) [K_Frame_FindNthUserInt]: an RwFrameForAllChildren callback over the search record
// {name[64], wanted n +64, counter +68, found +72, value +76, frame +80}: once found it returns 0 (stop); otherwise
// each int entry of an array named record->name either is the n-th (value and frame stored, found = 1, return 0) or
// counts; then it recurses into the children with itself and returns the frame.
void sub_1A6D20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a6d20
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    lw(v1, a1, kRecFound);
    v0 = 1;
    if (v1 != v0) {
        // 0x001a6d60
        charge(ctx, 3);
        s2 = 0;               // s2 = array index
        bool found = false;  // the n-th entry is here (the original's exit block 0x1a6dd8)
        for (;;) {
            // 0x001a6e2c
            charge(ctx, 6);
            a0 = s4;
            jal(ctx, 0x1A6E30u, gen::fn_sub_48EDE0_0048ede0);
            v0 = slt(s2, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001a6d6c
            charge(ctx, 14);
            a0 = s4;
            a1 = s2;
            jal(ctx, 0x1A6D74u, gen::fn_sub_48EE30_0048ee30);
            s0 = v0;
            a0 = s0;
            jal(ctx, 0x1A6D84u, gen::fn_name__C9type_info_0_0048ef10);
            a0 = v0;
            a1 = s3;
            jal(ctx, 0x1A6D94u, gen::fn_strcmp_00524128);
            if (v0 == 0) {
                // 0x001a6da4
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x001a6e10
                    charge(ctx, 6);
                    a0 = s0;
                    jal(ctx, 0x1A6E14u, gen::fn_sub_48EF30_0048ef30);
                    v0 = slt(s1, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001a6db0
                    charge(ctx, 6);
                    a0 = s0;
                    jal(ctx, 0x1A6DB4u, gen::fn_sub_48EF20_0048ef20);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x001a6dc8
                        charge(ctx, 4);
                        lw(v1, s3, kRecWanted);
                        lw(v0, s3, kRecCount);
                        if (v1 == v0) {
                            found = true;
                            break;
                        }
                        // 0x001a6e04: not yet -- count it
                        charge(ctx, 2);
                        v0 = addiu(v0, 1);
                        sw(v0, s3, kRecCount);
                    }
                    // 0x001a6e0c
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                }
                if (found) {
                    break;
                }
            }
            // 0x001a6e28
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
        if (found) {
            // 0x001a6dd8: store the value and the frame, found = 1, stop the walk
            charge(ctx, 11);
            a0 = s0;
            a1 = s1;
            jal(ctx, 0x1A6DE0u, gen::fn_sub_48EF40_0048ef40);
            sw(v0, s3, kRecValue);
            sw(s4, s3, kRecFrame);
            v0 = 1;
            sw(v0, s3, kRecFound);
            v0 = 0;
        } else {
            // 0x001a6e44: on into the children
            charge(ctx, 7);
            a0 = s4;
            a1 = 0x1A0000;
            a1 = addiu(a1, 27936);  // &sub_1A6D20
            a2 = s3;
            jal(ctx, 0x1A6E54u, gen::fn_sub_4CB6E0_004cb6e0);
            v0 = s4;
        }
    } else {
        // 0x001a6d54: already found -- stop
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a6e60 (the epilogue)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001A6E90 sub_1A6E90 -- 392 bytes; frame 0xC0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq), s0 sp+0xA0
// sub_1A6E90(out, clump, name, n) [K_Clump_GetNthUserInt]: the n-th int user-data entry named `name` in the clump's
// frame hierarchy, root first (as sub_1A6D20, on a zeroed 84-byte stack record), then the descendants through
// RwFrameForAllChildren + sub_1A6D20; out[0] = the value, out[1] = its frame (both as the record left them: 0 / 0 when
// nothing matched). The field loader (sub_1B32F0 / sub_1B3480) reads "per3FieldObjectResid", "...Type", "...Collis",
// "...Id", "...Anim" with it.
void sub_1A6E90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x001a6e90
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s2 = a2;
    s0 = a3;
    lw(s1, a1, 4);  // s1 = the clump's root frame
    a0 = addiu(sp, 0x60);
    a1 = 0;
    a2 = kRecSize;
    jal(ctx, 0x1A6EC8u, gen::fn_memset_00521408);
    a0 = addiu(sp, 0x60);
    a1 = s2;
    jal(ctx, 0x1A6ED8u, gen::fn_strcpy_00524270);
    sw(s0, sp, 0xA0);    // record +64: n
    s3 = 0;              // s3 = array index
    bool found = false;  // the root frame holds it (the original's exit block 0x1a6f5c)
    for (;;) {
        // 0x001a6fb4
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x1A6FB8u, gen::fn_sub_48EDE0_0048ede0);
        v0 = slt(s3, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001a6ef0
        charge(ctx, 14);
        a0 = s1;
        a1 = s3;
        jal(ctx, 0x1A6EF8u, gen::fn_sub_48EE30_0048ee30);
        s0 = v0;
        a0 = s0;
        jal(ctx, 0x1A6F08u, gen::fn_name__C9type_info_0_0048ef10);
        a0 = v0;
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x1A6F18u, gen::fn_strcmp_00524128);
        if (v0 == 0) {
            // 0x001a6f28
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x001a6f98
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x1A6F9Cu, gen::fn_sub_48EF30_0048ef30);
                v0 = slt(s2, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001a6f34
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x1A6F38u, gen::fn_sub_48EF20_0048ef20);
                v1 = 1;
                if (v0 == v1) {
                    // 0x001a6f4c
                    charge(ctx, 4);
                    lw(v1, sp, 0xA0);
                    lw(v0, sp, 0xA4);
                    if (v1 == v0) {
                        found = true;
                        break;
                    }
                    // 0x001a6f8c: not yet -- count it
                    charge(ctx, 2);
                    v0 = addiu(v0, 1);
                    sw(v0, sp, 0xA4);
                }
                // 0x001a6f94
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            if (found) {
                break;
            }
        }
        // 0x001a6fb0
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    if (found) {
        // 0x001a6f5c: the root frame's entry -- value and frame into the record, then out
        charge(ctx, 12);
        a0 = s0;
        a1 = s2;
        jal(ctx, 0x1A6F64u, gen::fn_sub_48EF40_0048ef40);
        sw(v0, sp, 0xAC);
        sw(s1, sp, 0xB0);
        lwc1(f1, sp, 0xAC);
        lwc1(f0, sp, 0xB0);
        swc1(f1, s4, 0);
        swc1(f0, s4, 4);
    } else {
        // 0x001a6fcc: the descendants (RwFrameForAllChildren with sub_1A6D20), then out = the record's value / frame
        charge(ctx, 10);
        a0 = s1;
        a1 = 0x1A0000;
        a1 = addiu(a1, 27936);  // &sub_1A6D20
        a2 = addiu(sp, 0x60);
        jal(ctx, 0x1A6FDCu, gen::fn_sub_4CB6E0_004cb6e0);
        lwc1(f1, sp, 0xAC);
        lwc1(f0, sp, 0xB0);
        swc1(f1, s4, 0);
        swc1(f0, s4, 4);
    }
    // 0x001a6ff4 (the epilogue)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

}  // namespace p3fes::game
