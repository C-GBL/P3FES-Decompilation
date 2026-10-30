// Slice libs3: newlib's mprec Bigint arithmetic (the allocating half) and strtod.
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions, the pseudocode reference and
// the public C standard / MPEG standards only (ADR-0010: no newlib, GPL or CRI source was opened).
// Pair tests: tests/game/test_libs3.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs3.h"

namespace p3fes::recomp_gen {
void fn__Balloc_00521578(p3fes::EEContext&);
void fn__Bfree_00521620(p3fes::EEContext&);
void fn___fixdfdi_0052ed30(p3fes::EEContext&);
void fn___floatdidf_0052eac8(p3fes::EEContext&);
void fn___mcmp_00521e70(p3fes::EEContext&);
void fn___mdiff_00521ed8(p3fes::EEContext&);
void fn__calloc_r_0051e178(p3fes::EEContext&);
void fn__d2b_005222c0(p3fes::EEContext&);
void fn__hi0bits_00521888(p3fes::EEContext&);
void fn__i2b_005219c8(p3fes::EEContext&);
void fn__lo0bits_00521908(p3fes::EEContext&);
void fn__lshift_00521d10(p3fes::EEContext&);
void fn__multadd_00521650(p3fes::EEContext&);
void fn__multiply_00521a00(p3fes::EEContext&);
void fn__pow5mult_00521c08(p3fes::EEContext&);
void fn__ratio_00522440(p3fes::EEContext&);
void fn__s2b_00521758(p3fes::EEContext&);
void fn__strtod_r_00524aa8(p3fes::EEContext&);
void fn__ulp_00522058(p3fes::EEContext&);
void fn_dpadd_00531170(p3fes::EEContext&);
void fn_dpcmp_005316d0(p3fes::EEContext&);
void fn_dpdiv_00531480(p3fes::EEContext&);
void fn_dpmul_00531230(p3fes::EEContext&);
void fn_dpsub_005311c8(p3fes::EEContext&);
void fn_dptofp_005318a0(p3fes::EEContext&);
void fn_dptoli_005317d0(p3fes::EEContext&);
void fn_litodp_00531720(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_strtod_005258f8(p3fes::EEContext&);
void fn_strtodf_00525920(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x00521578 _Balloc -- 168 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// mprec's Bigint allocator _Balloc(reent, k): the _reent's free-list table (+0x4C, allocated on first use with
// _calloc_r(16, 4)) has one list per size class; a block of class k (room for 1 << k words) is popped from its list, or
// allocated with _calloc_r(1, 24 + 4 * ((1 << k) - 1)) and given k / maxwds; sign and wds are cleared. Returns the
// Bigint, or 0 when an allocation fails.
void _Balloc(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00521578
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s0 = a0;
    s1 = a1;
    lw(t6, a0, libc::reent::kFreelist);  // the free-list table, one list per class
    a1 = 4;
    if (t6 == 0) {
        // 0x0052159c
        charge(ctx, 6);
        a2 = 16;
        jal(ctx, 0x52159Cu, gen::fn__calloc_r_0051e178);
        sw(v0, s0, libc::reent::kFreelist);
        t7 = 0;
        t6 = v0;
        if (v0 != 0) {
            goto L_005215b4;
        }
        // 0x005215dc (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        v0 = t7;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_005215b4:
    charge(ctx, 5);
    t7 = sll(s1, 2);
    t6 = addu(t7, t6);
    lw(v0, t6, 0);
    t7 = 1;
    if (v0 != 0) {
        // 0x005215c8
        charge(ctx, 2);
        lw(t7, v0, 0);
        sw(t7, t6, 0);
        goto L_005215d0;
    }
    // 0x005215f4
    charge(ctx, 8);
    a0 = s0;
    s0 = sllv(t7, s1);
    a1 = 1;
    a2 = sll(s0, 2);
    a2 = addiu(a2, 20);
    jal(ctx, 0x521604u, gen::fn__calloc_r_0051e178);
    t7 = 0;
    if (v0 == 0) {
        backedge(ctx);
    } else {
        // 0x00521614
        charge(ctx, 3);
        sw(s1, v0, 4);
        sw(s0, v0, 8);
        backedge(ctx);
    L_005215d0:
        charge(ctx, 3);
        sw(zero, v0, 16);
        t7 = v0;
        sw(zero, v0, 12);
    }
    // 0x005215dc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    v0 = t7;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00521650 _multadd -- 260 bytes; frame 0x30: s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, s0 sp+0x0, s2 sp+0x10, ra sp+0x28
// mprec's _multadd(reent, b, m, a): b = b * m + a word by word (16-bit halves: no 64-bit multiply), growing the Bigint
// by one word (a new Bigint from _Balloc, memcpy of the words, _Bfree of the old) when the final carry needs it.
// Returns b (possibly the new block).
void _multadd(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00521650
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t2 = addiu(a1, 20);
    sd(s1, sp, 0x8);
    t1 = 0;
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    s1 = a3;
    sd(s0, sp, 0x0);
    s3 = a1;
    sd(s2, sp, 0x10);
    s4 = a0;
    sd(ra, sp, 0x28);
    lw(s2, a1, 16);
    for (;;) {
        // 0x00521684
        charge(ctx, 17);
        lw(t5, t2, 0);
        t1 = addiu(t1, 1);
        t3 = slt(t1, s2);
        t7 = t5 & 0xFFFF;
        mult(t7, t7, a2);
        t5 = srl(t5, 16);
        mult1(t5, t5, a2);
        t7 = addu(t7, s1);
        t4 = srl(t7, 16);
        t5 = addu(t5, t4);
        t7 = t7 & 0xFFFF;
        t6 = sll(t5, 16);
        s1 = srl(t5, 16);
        t6 = addu(t6, t7);
        sw(t6, t2, 0);
        t2 = addiu(t2, 4);
        if (t3 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005216c8
    charge(ctx, 2);
    v0 = s3;
    if (s1 != 0) {
        // 0x005216d0
        charge(ctx, 4);
        lw(t7, s3, 8);
        t7 = slt(s2, t7);
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = sll(s2, 2);
        if (!cc) {
            // 0x005216e0
            charge(ctx, 16);
            lw(a1, s3, 4);
            a0 = s4;
            a1 = addiu(a1, 1);
            jal(ctx, 0x5216E8u, gen::fn__Balloc_00521578);
            lw(a2, s3, 16);
            a1 = addiu(s3, 12);
            s0 = v0;
            a0 = addiu(v0, 12);
            a2 = sll(a2, 2);
            a2 = addiu(a2, 8);
            jal(ctx, 0x521704u, gen::fn_memcpy_00521250);
            a1 = s3;
            a0 = s4;
            jal(ctx, 0x521710u, gen::fn__Bfree_00521620);
            s3 = s0;
            t7 = sll(s2, 2);
        }
        // 0x00521720
        charge(ctx, 5);
        t7 = addu(t7, s3);
        s2 = addiu(s2, 1);
        sw(s1, t7, 20);
        sw(s2, s3, 16);
        v0 = s3;
    }
    // 0x00521734 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00521758 _s2b -- 300 bytes; frame 0x40: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s1 sp+0x8, ra sp+0x30
// mprec's _s2b(reent, s, nd0, nd, y9): the decimal digit string s (nd digits, nd0 before the decimal point, the first
// nine already in y9) as a Bigint: starts from y9 and folds in each further digit with _multadd(b, 10, digit), skipping
// the decimal point.
void _s2b(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t4{ctx, 12}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00521758
    enter(ctx, 20);  // entry check point + this block's cycles
    t7 = 9;
    t6 = addiu(a3, 8);
    div(t6, t7);
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    t4 = 1;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    s0 = a1;
    sd(s4, sp, 0x20);
    s2 = a0;
    sd(s5, sp, 0x28);
    s3 = a2;
    sd(s1, sp, 0x8);
    s4 = t0;
    sd(ra, sp, 0x30);
    s5 = a3;
    a1 = 0;
    if (t7 == 0) {
        brk(ctx, 0x5217A4u, 0x7u);
    }
    // 0x005217a8
    charge(ctx, 4);
    mflo(t6);
    t7 = slt(t4, t6);
    a0 = s2;
    if (t7 != 0) {
        for (;;) {
            // 0x005217b8
            charge(ctx, 7);
            t4 = sll(t4, 1);
            t7 = slt(t4, t6);
            a1 = addiu(a1, 1);
            if (t7 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005217d4
        charge(ctx, 1);
        a0 = s2;
    }
    // 0x005217d8
    charge(ctx, 7);
    s1 = 9;
    jal(ctx, 0x5217D8u, gen::fn__Balloc_00521578);
    t7 = 1;
    sw(s4, v0, 20);
    t6 = slti(s3, 10);
    sw(t7, v0, 16);
    if (t6 != 0) {
        // 0x0052187c
        charge(ctx, 2);
        s0 = addiu(s0, 10);
        backedge(ctx);
    } else {
        // 0x005217f4
        charge(ctx, 1);
        s0 = addiu(s0, 9);
        for (;;) {
            // 0x005217f8
            charge(ctx, 10);
            lb(a3, s0, 0);
            a1 = v0;
            a0 = s2;
            a2 = 10;
            a3 = addiu(a3, -48);
            s1 = addiu(s1, 1);
            jal(ctx, 0x52180Cu, gen::fn__multadd_00521650);
            t7 = slt(s1, s3);
            s0 = addiu(s0, 1);
            if (t7 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00521820
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00521824
    charge(ctx, 3);
    t7 = slt(s1, s5);
    s1 = subu(s5, s1);
    if (t7 != 0) {
        // 0x00521830
        charge(ctx, 1);
        lb(a3, s0, 0);
        for (;;) {
            // 0x00521834
            charge(ctx, 9);
            s1 = addiu(s1, -1);
            a1 = v0;
            a0 = s2;
            a2 = 10;
            a3 = addiu(a3, -48);
            s0 = addiu(s0, 1);
            jal(ctx, 0x521848u, gen::fn__multadd_00521650);
            if (s1 == 0) {
                break;
            }
            lb(a3, s0, 0);
            backedge(ctx);
        }
    }
    // 0x00521858 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x005219C8 _i2b -- 52 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// mprec's _i2b(reent, i): a one-word Bigint (class 1) holding i.
void _i2b(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, t7{ctx, 15}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005219c8
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a1;
    a1 = 1;
    jal(ctx, 0x5219D8u, gen::fn__Balloc_00521578);
    sw(s0, v0, 20);
    t7 = 1;
    sw(t7, v0, 16);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00521A00 _multiply -- 516 bytes; frame 0x30: s0 sp+0x0, s4 sp+0x20, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x28
// mprec's _multiply(reent, a, b): the schoolbook product a * b (the longer operand outside, 16-bit halves of each word
// of the shorter one), in a new Bigint of the needed class with trailing zero words trimmed.
void _multiply(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00521a00
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s4, sp, 0x20);
    sd(s1, sp, 0x8);
    s0 = a1;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x28);
    lw(s3, a1, 16);
    lw(s2, a2, 16);
    t7 = slt(s3, s2);
    s4 = a2;
    if (t7 != 0) {
        // 0x00521a34
        charge(ctx, 4);
        lw(s3, a2, 16);
        s0 = a2;
        lw(s2, a1, 16);
        s4 = a1;
    }
    // 0x00521a44
    charge(ctx, 12);
    lw(t7, s0, 8);
    s1 = addu(s3, s2);
    lw(a1, s0, 4);
    t7 = slt(t7, s1);
    a1 = addu(a1, t7);
    jal(ctx, 0x521A54u, gen::fn__Balloc_00521578);
    t8 = addiu(v0, 20);
    t9 = sll(s1, 2);
    v1 = addu(t8, t9);
    t7 = sltu(t8, v1);
    t1 = t8;
    if (t7 != 0) {
        // 0x00521a74
        charge(ctx, 1);
        sw(zero, t1, 0);
        for (;;) {
            // 0x00521a78
            charge(ctx, 7);
            t1 = addiu(t1, 4);
            t7 = sltu(t1, v1);
            if (t7 == 0) {
                break;
            }
            sw(zero, t1, 0);
            backedge(ctx);
        }
    }
    // 0x00521a94
    charge(ctx, 9);
    a2 = addiu(s4, 20);
    v1 = addiu(s0, 20);
    t7 = sll(s3, 2);
    t6 = sll(s2, 2);
    s0 = addu(a2, t6);
    a1 = addu(v1, t7);
    t7 = sltu(a2, s0);
    a0 = t8;
    if (t7 != 0) {
        for (;;) {
            // 0x00521ab8
            charge(ctx, 4);
            lw(t7, a2, 0);
            a3 = t7 & 0xFFFF;
            t2 = a0;
            if (a3 != 0) {
                // 0x00521ac8
                charge(ctx, 2);
                t1 = v1;
                t0 = 0;
                for (;;) {
                    // 0x00521ad0
                    charge(ctx, 20);
                    lw(t7, t1, 0);
                    lw(t5, t2, 0);
                    t6 = t7 & 0xFFFF;
                    t1 = addiu(t1, 4);
                    mult(t6, t6, a3);
                    t7 = srl(t7, 16);
                    mult1(t7, t7, a3);
                    t4 = t5 & 0xFFFF;
                    t5 = srl(t5, 16);
                    t3 = sltu(t1, a1);
                    t6 = addu(t6, t4);
                    t6 = addu(t6, t0);
                    t7 = addu(t7, t5);
                    t0 = srl(t6, 16);
                    sh(t6, t2, 0);
                    t7 = addu(t7, t0);
                    sh(t7, t2, 2);
                    t0 = srl(t7, 16);
                    t2 = addiu(t2, 4);
                    if (t3 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00521b20
                charge(ctx, 2);
                sw(t0, t2, 0);
                lw(t7, a2, 0);
            }
            // 0x00521b28
            charge(ctx, 3);
            a3 = srl(t7, 16);
            t2 = a0;
            if (a3 != 0) {
                // 0x00521b34
                charge(ctx, 4);
                lw(t7, a0, 0);
                t1 = v1;
                t0 = 0;
                t3 = t7;
                for (;;) {
                    // 0x00521b44
                    charge(ctx, 21);
                    lw(t5, t1, 0);
                    t6 = srl(t3, 16);
                    sh(t7, t2, 0);
                    t1 = addiu(t1, 4);
                    t7 = t5 & 0xFFFF;
                    t4 = sltu(t1, a1);
                    mult(t7, t7, a3);
                    t5 = srl(t5, 16);
                    mult1(t5, t5, a3);
                    t7 = addu(t7, t6);
                    t6 = addu(t7, t0);
                    sh(t6, t2, 2);
                    t0 = srl(t6, 16);
                    t2 = addiu(t2, 4);
                    lw(t7, t2, 0);
                    t6 = t7 & 0xFFFF;
                    t3 = t7;
                    t5 = addu(t5, t6);
                    t7 = addu(t5, t0);
                    t0 = srl(t7, 16);
                    if (t4 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00521b98
                charge(ctx, 1);
                sw(t7, t2, 0);
            }
            // 0x00521b9c
            charge(ctx, 4);
            a2 = addiu(a2, 4);
            t7 = sltu(a2, s0);
            a0 = addiu(a0, 4);
            if (t7 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00521bac
    charge(ctx, 2);
    t2 = addu(t8, t9);
    if (i64(s1) > 0) {
        // 0x00521bb4
        charge(ctx, 4);
        t2 = addiu(t2, -4);
        lw(t7, t2, 0);
        if (t7 != 0) {
            sw(s1, v0, 16);
        } else {
            // 0x00521bc4
            charge(ctx, 1);
            s1 = addiu(s1, -1);
            for (;;) {
                // 0x00521bc8
                charge(ctx, 2);
                if (i64(s1) > 0) {
                    // 0x00521bd0
                    charge(ctx, 4);
                    t2 = addiu(t2, -4);
                    lw(t7, t2, 0);
                    if (t7 != 0) {
                        goto L_00521be0;
                    }
                    s1 = addiu(s1, -1);
                    backedge(ctx);
                    continue;
                }
                sw(s1, v0, 16);
                break;
            }
        }
        // 0x00521be4 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
L_00521be0:
    charge(ctx, 1);
    sw(s1, v0, 16);
    // 0x00521be4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00521C08 _pow5mult -- 260 bytes; frame 0x30: s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, s0 sp+0x0, s2 sp+0x10, ra sp+0x28
// mprec's _pow5mult(reent, b, k): b * 5^k -- the k % 4 part through _multadd with 5, 25 or 125 (table 0x7C04E8), the
// rest by squaring the cached 5^4 Bigint (built with _i2b(625), kept in the _reent's +0x48 list) and multiplying in the
// needed powers; frees the replaced Bigints.
void _pow5mult(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00521c08
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t6 = a2 & 0x3;
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    s1 = a2;
    sd(s0, sp, 0x0);
    s3 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x28);
    s4 = a0;
    if (t6 != 0) {
        // 0x00521c38
        charge(ctx, 8);
        t7 = 0x7C0000;
        t6 = sll(t6, 2);
        t7 = addiu(t7, -5272);  // &0x7BEB68
        a3 = 0;
        t6 = addu(t6, t7);
        link(ctx, 0x521C4Cu);  // $ra first: the delay slot below depends on it
        lw(a2, t6, -4);
        call(ctx, gen::fn__multadd_00521650);
        s3 = v0;
    }
    // 0x00521c58
    charge(ctx, 3);
    s1 = sra(s1, 2);
    v0 = s3;
    if (s1 != 0) {
        // 0x00521c64
        charge(ctx, 3);
        lw(s2, s4, 72);
        t7 = s1 & 0x1;
        if (s2 == 0) {
            // 0x00521c70
            charge(ctx, 6);
            a0 = s4;
            a1 = 625;
            jal(ctx, 0x521C74u, gen::fn__i2b_005219c8);
            sw(v0, s4, 72);
            s2 = v0;
            sw(zero, v0, 0);
        L_00521c88:
            charge(ctx, 1);
            t7 = s1 & 0x1;
        }
        // 0x00521c8c
        charge(ctx, 2);
        s1 = sra(s1, 1);
        if (t7 != 0) {
            // 0x00521c94
            charge(ctx, 9);
            a1 = s3;
            a2 = s2;
            a0 = s4;
            jal(ctx, 0x521C9Cu, gen::fn__multiply_00521a00);
            s0 = v0;
            a1 = s3;
            a0 = s4;
            s3 = s0;
            jal(ctx, 0x521CB0u, gen::fn__Bfree_00521620);
        }
        // 0x00521cb8
        charge(ctx, 2);
        v0 = s3;
        if (s1 != 0) {
            // 0x00521cc0
            charge(ctx, 3);
            lw(v0, s2, 0);
            if (v0 != 0) {
                s2 = v0;
                backedge(ctx);
            } else {
                // 0x00521ccc
                charge(ctx, 8);
                a1 = s2;
                a2 = s2;
                a0 = s4;
                jal(ctx, 0x521CD4u, gen::fn__multiply_00521a00);
                sw(v0, s2, 0);
                sw(zero, v0, 0);
                s2 = v0;
                backedge(ctx);
            }
            goto L_00521c88;
        }
    }
    // 0x00521cec (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00521D10 _lshift -- 348 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s5 sp+0x28, s4 sp+0x20, ra sp+0x30
// mprec's _lshift(reent, b, k): b << k in a new Bigint (whole words, then the bit shift with the carry out of the top
// word), freeing b.
void _lshift(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00521d10
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s0 = a2;
    sd(s3, sp, 0x18);
    s1 = sra(a2, 5);
    sd(s5, sp, 0x28);
    sd(s4, sp, 0x20);
    s3 = a1;
    sd(ra, sp, 0x30);
    s5 = a0;
    lw(t6, a1, 16);
    lw(t5, a1, 8);
    t6 = addu(s1, t6);
    s2 = addiu(t6, 1);
    t7 = slt(t5, s2);
    lw(a1, a1, 4);
    if (t7 != 0) {
        for (;;) {
            // 0x00521d5c
            charge(ctx, 7);
            t5 = sll(t5, 1);
            t7 = slt(t5, s2);
            a1 = addiu(a1, 1);
            if (t7 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00521d78
    charge(ctx, 5);
    a0 = s5;
    jal(ctx, 0x521D78u, gen::fn__Balloc_00521578);
    s4 = v0;
    t5 = addiu(v0, 20);
    if (i64(s1) > 0) {
        // 0x00521d8c
        charge(ctx, 2);
        t7 = t5;
        t5 = s1;
        for (;;) {
            // 0x00521d94
            charge(ctx, 7);
            sw(zero, t7, 0);
            t5 = addiu(t5, -1);
            t7 = addiu(t7, 4);
            if (t5 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00521db0
        charge(ctx, 1);
        t5 = t7;
    }
    // 0x00521db4
    charge(ctx, 6);
    lw(t7, s3, 16);
    t4 = addiu(s3, 20);
    s0 = s0 & 0x1F;
    t7 = sll(t7, 2);
    t3 = addu(t4, t7);
    if (s0 == 0) {
        for (;;) {
            // 0x00521e48
            charge(ctx, 7);
            lw(t7, t4, 0);
            sw(t7, t5, 0);
            t4 = addiu(t4, 4);
            t7 = sltu(t4, t3);
            t5 = addiu(t5, 4);
            if (t7 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00521e64
        charge(ctx, 2);
        t7 = addiu(s2, -1);
        backedge(ctx);
    } else {
        // 0x00521dcc
        charge(ctx, 3);
        t7 = 32;
        t6 = 0;
        t2 = subu(t7, s0);
        for (;;) {
            // 0x00521dd8
            charge(ctx, 10);
            lw(t7, t4, 0);
            t7 = sllv(t7, s0);
            t7 = t7 | t6;
            sw(t7, t5, 0);
            lw(t6, t4, 0);
            t5 = addiu(t5, 4);
            t4 = addiu(t4, 4);
            t7 = sltu(t4, t3);
            t6 = srlv(t6, t2);
            if (t7 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00521e00
        charge(ctx, 2);
        sw(t6, t5, 0);
        if (t6 != 0) {
            // 0x00521e08
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
        // 0x00521e0c
        charge(ctx, 1);
        t7 = addiu(s2, -1);
    }
    // 0x00521e10
    charge(ctx, 14);
    a0 = s5;
    sw(t7, s4, 16);
    a1 = s3;
    jal(ctx, 0x521E18u, gen::fn__Bfree_00521620);
    v0 = s4;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00521ED8 __mdiff -- 380 bytes; frame 0x30: s1 sp+0x8, s3 sp+0x18, s2 sp+0x10, s0 sp+0x0, ra sp+0x20
// mprec's __mdiff(reent, a, b): |a - b| as a new Bigint with the sign word set when a < b (compared with __mcmp; a zero
// Bigint for a == b), borrow propagated through 16-bit halves.
void __mdiff(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00521ed8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(s2, sp, 0x10);
    s1 = a1;
    s3 = a0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    s2 = a2;
    a1 = a2;
    a0 = s1;
    jal(ctx, 0x521F00u, gen::fn___mcmp_00521e70);
    a0 = s3;
    if (v0 != 0) {
        // 0x00521f40
        charge(ctx, 2);
        s0 = 0;
        if (i64(v0) < 0) {
            // 0x00521f48
            charge(ctx, 4);
            v0 = s1;
            s0 = 1;
            s1 = s2;
            s2 = v0;
        }
        // 0x00521f58
        charge(ctx, 14);
        lw(a1, s1, 4);
        a0 = s3;
        jal(ctx, 0x521F5Cu, gen::fn__Balloc_00521578);
        lw(t1, s1, 16);
        a0 = addiu(s1, 20);
        lw(t7, s2, 16);
        a1 = addiu(s2, 20);
        t6 = sll(t1, 2);
        sw(s0, v0, 12);
        t7 = sll(t7, 2);
        a3 = addu(a0, t6);
        t0 = addu(a1, t7);
        t2 = addiu(v0, 20);
        t3 = 0;
        for (;;) {
            // 0x00521f90
            charge(ctx, 19);
            lw(t5, a0, 0);
            lw(t7, a1, 0);
            t6 = t5 & 0xFFFF;
            a0 = addiu(a0, 4);
            t4 = t7 & 0xFFFF;
            t5 = srl(t5, 16);
            t6 = subu(t6, t4);
            t7 = srl(t7, 16);
            t6 = addu(t6, t3);
            t5 = subu(t5, t7);
            t3 = sra(t6, 16);
            sh(t6, t2, 0);
            t5 = addu(t5, t3);
            a1 = addiu(a1, 4);
            sh(t5, t2, 2);
            t3 = sra(t5, 16);
            t7 = sltu(a1, t0);
            t2 = addiu(t2, 4);
            if (t7 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00521fdc
        charge(ctx, 3);
        t7 = sltu(a0, a3);
        t6 = t2;
        if (t7 != 0) {
            for (;;) {
                // 0x00521fe8
                charge(ctx, 13);
                lw(t7, a0, 0);
                t6 = t7 & 0xFFFF;
                a0 = addiu(a0, 4);
                t6 = addu(t6, t3);
                t7 = srl(t7, 16);
                t3 = sra(t6, 16);
                sh(t6, t2, 0);
                t5 = addu(t7, t3);
                sh(t5, t2, 2);
                t6 = sltu(a0, a3);
                t3 = sra(t5, 16);
                t2 = addiu(t2, 4);
                if (t6 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0052201c
            charge(ctx, 1);
            t6 = t2;
        }
        // 0x00522020
        charge(ctx, 4);
        t6 = addiu(t6, -4);
        lw(t7, t6, 0);
        if (t7 != 0) {
            sw(t1, v0, 16);
            backedge(ctx);
        } else {
            for (;;) {
                // 0x00522030
                charge(ctx, 7);
                t6 = addiu(t6, -4);
                lw(t7, t6, 0);
                t1 = addiu(t1, -1);
                if (t7 != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0052204c
            charge(ctx, 2);
            sw(t1, v0, 16);
            backedge(ctx);
        }
    } else {
        // 0x00521f10
        charge(ctx, 5);
        a1 = 0;
        jal(ctx, 0x521F10u, gen::fn__Balloc_00521578);
        t7 = 1;
        sw(zero, v0, 20);
        sw(t7, v0, 16);
    }
    // 0x00521f24 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005222C0 _d2b -- 380 bytes; frame 0x50: s0 sp+0x10, s4 sp+0x30, s5 sp+0x38, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, ra sp+0x40
// mprec's _d2b(reent, d, &e, &bits): the double d (the 64-bit argument) as a Bigint of its significand with trailing
// zero bits removed (_lo0bits); *e = the binary exponent of the lowest bit, *bits = the significant bits (denormals
// counted from the top bit with _hi0bits).
void _d2b(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005222c0
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x10);
    sd(s4, sp, 0x30);
    sd(s5, sp, 0x38);
    s0 = a1;
    sd(s1, sp, 0x18);
    s4 = a2;
    sd(s2, sp, 0x20);
    s5 = a3;
    sd(s3, sp, 0x28);
    sd(ra, sp, 0x40);
    a1 = 1;
    jal(ctx, 0x5222ECu, gen::fn__Balloc_00521578);
    t7 = 0x7FFF0000;
    t5 = dsra32(s0, 0);
    t7 = t7 | 0xFFFF;
    t6 = 0xF0000;
    t7 = t5 & t7;
    t6 = t6 | 0xFFFF;
    t7 = dsll32(t7, 0);
    s0 = dsll32(s0, 0);
    t7 = dsrl32(t7, 0);
    t5 = t5 & t6;
    s0 = dsrl32(s0, 0);
    sw(t5, sp, 0x4);
    t7 = dsll32(t7, 0);
    s1 = v0;
    s0 = s0 | t7;
    s2 = dsrl32(s0, 20);
    s3 = addiu(v0, 20);
    if (s2 != 0) {
        // 0x0052233c
        charge(ctx, 3);
        t7 = 0x100000;
        t7 = t5 | t7;
        sw(t7, sp, 0x4);
    }
    // 0x00522348
    charge(ctx, 4);
    a1 = dsll32(s0, 0);
    a1 = dsra32(a1, 0);
    a0 = addiu(sp, 0x4);
    if (a1 == 0) {
        // 0x00522420
        charge(ctx, 7);
        s0 = 1;
        jal(ctx, 0x522420u, gen::fn__lo0bits_00521908);
        lw(t7, sp, 0x4);
        v0 = addiu(v0, 32);
        t6 = 1;
        sw(t7, s1, 20);
        backedge(ctx);
    } else {
        // 0x00522358
        charge(ctx, 5);
        sw(a1, sp, 0x0);
        a0 = sp;
        jal(ctx, 0x52235Cu, gen::fn__lo0bits_00521908);
        lw(t6, sp, 0x4);
        if (v0 == 0) {
            // 0x00522414
            charge(ctx, 3);
            lw(t7, sp, 0x0);
            sw(t7, s1, 20);
            backedge(ctx);
        } else {
            // 0x0052236c
            charge(ctx, 8);
            t5 = subu(0, v0);
            lw(t7, sp, 0x0);
            t6 = sllv(t6, t5);
            t7 = t7 | t6;
            sw(t7, s1, 20);
            lw(t6, sp, 0x4);
            t6 = srlv(t6, v0);
            sw(t6, sp, 0x4);
        }
        // 0x0052238c
        charge(ctx, 6);
        lw(t5, sp, 0x4);
        t6 = 2;
        t7 = 1;
        if (t5 == 0) t6 = t7;
        sw(t5, s3, 4);
        s0 = t6;
    }
    // 0x005223a4
    charge(ctx, 2);
    sw(t6, s1, 16);
    if (s2 == 0) {
        // 0x005223ec
        charge(ctx, 10);
        t6 = addiu(v0, -1074);
        t7 = sll(s0, 2);
        sw(t6, s4, 0);
        t7 = addu(s3, t7);
        s0 = sll(s0, 5);
        link(ctx, 0x522400u);  // $ra first: the delay slot below depends on it
        lw(a0, t7, -4);
        call(ctx, gen::fn__hi0bits_00521888);
        s0 = subu(s0, v0);
        sw(s0, s5, 0);
        backedge(ctx);
    } else {
        // 0x005223ac
        charge(ctx, 6);
        t6 = addu(s2, v0);
        t7 = 53;
        t6 = addiu(t6, -1075);
        t7 = subu(t7, v0);
        sw(t6, s4, 0);
        sw(t7, s5, 0);
    }
    // 0x005223c4 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = s1;
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00524AA8 _strtod_r -- 3664 bytes; frame 0xB0: s5 sp+0x88, s6 sp+0x90, fp sp+0xA0, s0 sp+0x60, s1 sp+0x68, s2 sp+0x70, s3 sp+0x78, s4 sp+0x80, s7 sp+0x98, ra sp+0xA8
// newlib's _strtod_r(reent, s, &end): decimal to double -- sign, digits, decimal point, exponent; small cases straight
// in double arithmetic (soft-float dpmul / dpdiv with the powers of ten), overflow and underflow with ERANGE (34) in
// reent->errno, and the general case corrected against the exact Bigint comparison (_s2b, _d2b, _pow5mult, _lshift,
// __mdiff, _ratio, _ulp) until the result is the nearest double the soft-float library can represent. *end = the first
// unread character (s when there is no number). The double comes back in $v0.
void _strtod_r(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00524aa8
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    t2 = 0;
    sd(s5, sp, 0x88);
    t1 = 0;
    sd(s6, sp, 0x90);
    sd(fp, sp, 0xA0);
    s5 = 0;
    sd(s0, sp, 0x60);
    s6 = a0;
    sd(s1, sp, 0x68);
    fp = a1;
    sd(s2, sp, 0x70);
    sd(s3, sp, 0x78);
    sd(s4, sp, 0x80);
    sd(s7, sp, 0x98);
    sd(ra, sp, 0xA8);
    sw(a2, sp, 0x8);
    sw(zero, sp, 0x10);
    for (;;) {
        // 0x00524af0
        charge(ctx, 6);
        lbu(t4, fp, 0x0);
        t6 = sll(t4, 24);
        t6 = sra(t6, 24);
        t7 = sltiu(t6, 46);
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = sll(t6, 2);
        if (cc) {
            goto L_00524b98;
        }
        // 0x00524b08
        charge(ctx, 6);
        t6 = 0x7C0000;
        t6 = addiu(t6, -4872);  // "@KR"
        t7 = addu(t7, t6);
        lw(t5, t7, 0);
        switch (t5.u()) {
        case 0x524B20u:  // table[45]
            goto L_00524b20;
        case 0x524B28u:  // table[43]
            goto L_00524b28;
        case 0x524B40u:  // table[0]
            goto L_00524b40;
        case 0x524B98u:  // table[1, 2, 3, 4, 5, 6, 7, 8, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 44]
            goto L_00524b98;
        case 0x5258F0u:  // table[9, 10, 11, 12, 13, 32]
            // 0x005258f0
            charge(ctx, 2);
            fp = addiu(fp, 0x1);
            backedge(ctx);
            continue;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, t5.u());
            return;
        }
    }
L_00524b20:
    charge(ctx, 2);
    t4 = 1;
    sw(t4, sp, 0x10);
L_00524b28:
    charge(ctx, 6);
    fp = addiu(fp, 0x1);
    lbu(t4, fp, 0x0);
    t7 = sll(t4, 24);
    t7 = sra(t7, 24);
    t6 = sll(t4, 24);
    if (t7 == 0) {
    L_00524b40:
        charge(ctx, 1);
        fp = a1;
        goto L_00524b44;
    }
L_00524b9c:
    charge(ctx, 4);
    t7 = 48;
    t6 = sra(t6, 24);
    a0 = sll(t4, 24);
    if (t6 == t7) {
        // 0x00524bac
        charge(ctx, 4);
        t7 = fp;
        t1 = 1;
        t6 = 48;
        t7 = addiu(t7, 1);
        for (;;) {
            // 0x00524bbc
            charge(ctx, 7);
            lbu(t4, t7, 0);
            t5 = sll(t4, 24);
            t5 = sra(t5, 24);
            if (t5 != t6) {
                break;
            }
            t7 = addiu(t7, 1);
            backedge(ctx);
        }
        // 0x00524bd8
        charge(ctx, 2);
        fp = t7;
        if (t5 != 0) {
            // 0x00524be0
            charge(ctx, 1);
            a0 = sll(t4, 24);
            goto L_00524be4;
        }
        backedge(ctx);
    L_00524b44:
        charge(ctx, 1);
        lw(t5, sp, 0x8);
        goto L_00524b48;
    }
L_00524be4:
    charge(ctx, 8);
    sw(fp, sp, 0x20);
    a0 = sra(a0, 24);
    sw(zero, sp, 0x30);
    s1 = 0;
    t5 = 0;
    t7 = slti(a0, 48);
    s2 = 0;
    if (t7 == 0) {
        // 0x00524c04
        charge(ctx, 3);
        t7 = slti(a0, 58);
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = 46;
        if (!cc) {
            // 0x00524c10
            charge(ctx, 2);
            t6 = 10;
            t7 = slti(s2, 9);
            for (;;) {
                // 0x00524c18
                charge(ctx, 2);
                lw(t4, sp, 0x30);
                if (t7 == 0) {
                    // 0x005258d0
                    charge(ctx, 3);
                    t7 = slti(s2, 16);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = dsll(s1, 2);
                    if (cc) {
                        backedge(ctx);
                    } else {
                        // 0x005258dc
                        charge(ctx, 5);
                        t7 = t7 + s1;
                        t7 = dsll(t7, 1);
                        t7 = a0 + t7;
                        s1 = daddiu(t7, -48);
                        backedge(ctx);
                    }
                } else {
                    // 0x00524c20
                    charge(ctx, 4);
                    mult(t7, t4, t6);
                    t7 = addu(t7, a0);
                    t7 = addiu(t7, -48);
                    sw(t7, sp, 0x30);
                }
                // 0x00524c30
                charge(ctx, 5);
                fp = addiu(fp, 0x1);
                lb(a0, fp, 0x0);
                t7 = slti(a0, 48);
                s2 = addiu(s2, 1);
                if (t7 == 0) {
                    // 0x00524c44
                    charge(ctx, 3);
                    t7 = slti(a0, 58);
                    cc = t7 != 0;  // the condition, before the delay slot changes it
                    t7 = slti(s2, 9);
                    if (cc) {
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
            goto L_00524c50;
        }
        goto L_00524c54;
    }
L_00524c50:
    charge(ctx, 1);
    t7 = 46;
L_00524c54:
    charge(ctx, 2);
    sw(s2, sp, 0xC);
    if (a0 == t7) {
        // 0x00524c5c
        charge(ctx, 3);
        fp = addiu(fp, 0x1);
        lb(a0, fp, 0x0);
        if (s2 != 0) {
            // 0x005258b8
            charge(ctx, 4);
            t3 = addiu(a0, -48);
            t7 = sltiu(t3, 10);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = 101;
            if (!cc) {
                // 0x005258c8
                charge(ctx, 2);
                backedge(ctx);
                for (;;) {
                L_00524cbc:
                    charge(ctx, 2);
                    t2 = addiu(t2, 1);
                    if (t3 != 0) {
                        // 0x00524cc4
                        charge(ctx, 4);
                        v0 = 1;
                        t7 = slt(v0, t2);
                        t5 = addu(t5, t2);
                        if (t7 != 0) {
                            // 0x00524cd4
                            charge(ctx, 5);
                            lw(a0, sp, 0x30);
                            a3 = s2;
                            t4 = addiu(t2, -1);
                            t6 = 10;
                            t7 = slti(a3, 9);
                            for (;;) {
                                // 0x00524ce8
                                charge(ctx, 2);
                                a3 = addiu(a3, 1);
                                if (t7 == 0) {
                                    // 0x005258a0
                                    charge(ctx, 3);
                                    t7 = slti(a3, 17);
                                    cc = t7 == 0;  // the condition, before the delay slot changes it
                                    t7 = dsll(s1, 2);
                                    if (cc) {
                                        backedge(ctx);
                                    } else {
                                        // 0x005258ac
                                        charge(ctx, 3);
                                        t7 = t7 + s1;
                                        s1 = dsll(t7, 1);
                                        backedge(ctx);
                                    }
                                } else {
                                    // 0x00524cf0
                                    charge(ctx, 1);
                                    mult(a0, a0, t6);
                                }
                                // 0x00524cf4
                                charge(ctx, 3);
                                t4 = addiu(t4, -1);
                                t7 = slti(a3, 9);
                                if (t4 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x00524d00
                            charge(ctx, 2);
                            sw(a0, sp, 0x30);
                            s2 = a3;
                        }
                        // 0x00524d08
                        charge(ctx, 3);
                        t7 = slti(s2, 9);
                        s2 = addiu(s2, 1);
                        if (t7 == 0) {
                            // 0x00525884
                            charge(ctx, 3);
                            t7 = slti(s2, 17);
                            cc = t7 == 0;  // the condition, before the delay slot changes it
                            t7 = dsll(s1, 2);
                            if (cc) {
                                backedge(ctx);
                            } else {
                                // 0x00525890
                                charge(ctx, 4);
                                t7 = t7 + s1;
                                t7 = dsll(t7, 1);
                                s1 = t3 + t7;
                                backedge(ctx);
                            }
                        } else {
                            // 0x00524d14
                            charge(ctx, 5);
                            lw(t6, sp, 0x30);
                            t7 = 10;
                            mult(t7, t6, t7);
                            t7 = addu(t7, t3);
                            sw(t7, sp, 0x30);
                        }
                        // 0x00524d28
                        charge(ctx, 1);
                        t2 = 0;
                    }
                    // 0x00524d2c
                    charge(ctx, 6);
                    fp = addiu(fp, 0x1);
                    lb(a0, fp, 0x0);
                    t7 = addiu(a0, -48);
                    t6 = sltiu(t7, 10);
                    t3 = t7;
                    if (t6 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                goto L_00524d44;
            }
            backedge(ctx);
        } else {
            // 0x00524c68
            charge(ctx, 3);
            t7 = 48;
            cc = a0 != t7;  // the condition, before the delay slot changes it
            t7 = addiu(a0, -49);
            if (!cc) {
                // 0x00524c74
                charge(ctx, 2);
                t7 = fp;
                t6 = 48;
                for (;;) {
                    // 0x00524c7c
                    charge(ctx, 7);
                    t7 = addiu(t7, 1);
                    lb(a0, t7, 0);
                    t2 = addiu(t2, 1);
                    if (a0 != t6) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00524c98
                charge(ctx, 2);
                fp = t7;
                t7 = addiu(a0, -49);
            }
            // 0x00524ca0
            charge(ctx, 3);
            t7 = sltiu(t7, 9);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = 101;
            if (!cc) {
                // 0x00524cac
                charge(ctx, 4);
                t5 = t2;
                sw(fp, sp, 0x20);
                t3 = addiu(a0, -48);
                t2 = 0;
                goto L_00524cbc;
            }
        }
        goto L_00524d48;
    }
L_00524d44:
    charge(ctx, 1);
    t7 = 101;
L_00524d48:
    charge(ctx, 2);
    sd(zero, sp, 0x18);
    if (a0 != t7) {
        // 0x00524d50
        charge(ctx, 3);
        t7 = 69;
        if (a0 == t7) {
            goto L_00524d5c;
        }
    L_00524e80:
        charge(ctx, 2);
        ld(t6, sp, 0x18);
        if (s2 != 0) {
            // 0x00524ea0
            charge(ctx, 17);
            t7 = slti(s2, 17);
            s3 = 16;
            lw(a0, sp, 0x30);
            t6 = t6 - t5;
            if (t7 != 0) s3 = s2;
            t4 = dsll32(t6, 0);
            sd(t6, sp, 0x18);
            t4 = dsra32(t4, 0);
            link(ctx, 0x524EC0u);  // $ra first: the delay slot below depends on it
            sw(t4, sp, 0x54);
            call(ctx, gen::fn_litodp_00531720);
            lw(t5, sp, 0xC);
            lw(t6, sp, 0xC);
            lw(s0, sp, 0x54);
            if (t6 == 0) t5 = s2;
            lw(t7, sp, 0x30);
            sw(t5, sp, 0xC);
            if (i64(t7) < 0) {
                // 0x00524ee4
                charge(ctx, 4);
                a1 = 1055;
                a0 = v0;
                a1 = dsll32(a1, 20);
                jal(ctx, 0x524EECu, gen::fn_dpadd_00531170);
            }
            // 0x00524ef4
            charge(ctx, 3);
            t7 = slti(s3, 10);
            s5 = v0;
            if (t7 == 0) {
                // 0x00524f00
                charge(ctx, 9);
                t6 = 0x7C0000;
                t7 = sll(s3, 3);
                t6 = addiu(t6, -5256);  // &0x7BEB78
                a1 = v0;
                t7 = addu(t7, t6);
                link(ctx, 0x524F14u);  // $ra first: the delay slot below depends on it
                ld(a0, t7, -72);
                call(ctx, gen::fn_dpmul_00531230);
                s5 = v0;
                if (i64(s1) < 0) {
                    // 0x00525850
                    charge(ctx, 9);
                    t7 = dsrl(s1, 1);
                    a0 = s1 & 0x1;
                    a0 = a0 | t7;
                    jal(ctx, 0x525858u, gen::fn___floatdidf_0052eac8);
                    a0 = v0;
                    a1 = v0;
                    jal(ctx, 0x525864u, gen::fn_dpadd_00531170);
                    a0 = s5;
                    backedge(ctx);
                } else {
                    // 0x00524f24
                    charge(ctx, 3);
                    a0 = s1;
                    jal(ctx, 0x524F24u, gen::fn___floatdidf_0052eac8);
                    a0 = s5;
                }
                // 0x00524f30
                charge(ctx, 3);
                a1 = v0;
                jal(ctx, 0x524F30u, gen::fn_dpadd_00531170);
                s5 = v0;
            }
            // 0x00524f3c
            charge(ctx, 4);
            t7 = subu(s2, s3);
            s0 = addu(s0, t7);
            sw(zero, sp, 0x50);
            if (i64(s0) > 0) {
                // 0x00524f4c
                charge(ctx, 3);
                v0 = s0 & 0xF;
                t7 = 0x7C0000;
                if (v0 != 0) {
                    // 0x00524f58
                    charge(ctx, 7);
                    t6 = sll(v0, 3);
                    t7 = addiu(t7, -5256);
                    a1 = s5;
                    t6 = addu(t6, t7);
                    link(ctx, 0x524F68u);  // $ra first: the delay slot below depends on it
                    ld(a0, t6, 0);
                    call(ctx, gen::fn_dpmul_00531230);
                    s5 = v0;
                }
                // 0x00524f74
                charge(ctx, 4);
                t7 = si(-16);
                s0 = s0 & t7;
                t7 = slti(s0, 309);
                if (s0 == 0) {
                    goto L_005250c0;
                }
                // 0x00524f84
                charge(ctx, 2);
                if (t7 == 0) {
                    goto L_00524f8c;
                }
                s0 = sra(s0, 4);
                // 0x00524fe8
                charge(ctx, 2);
                t7 = slti(s0, 2);
                if (s0 == 0) {
                    goto L_005250c0;
                }
                // 0x00524ff0
                charge(ctx, 2);
                t4 = 0;
                if (t7 == 0) {
                    // 0x00524ff8
                    charge(ctx, 4);
                    s1 = s0;
                    t7 = 0x7C0000;
                    s3 = t4;
                    s0 = addiu(t7, -5056);  // &0x7BEC40
                    for (;;) {
                        // 0x00525008
                        charge(ctx, 3);
                        t7 = s1 & 0x1;
                        if (t7 == 0) {
                            s1 = sra(s1, 1);
                        } else {
                            // 0x00525014
                            charge(ctx, 5);
                            ld(a0, s0, 0);
                            a1 = s5;
                            jal(ctx, 0x525018u, gen::fn_dpmul_00531230);
                            s5 = v0;
                            s1 = sra(s1, 1);
                        }
                        // 0x00525028
                        charge(ctx, 4);
                        s0 = addiu(s0, 8);
                        t7 = slti(s1, 2);
                        s3 = addiu(s3, 1);
                        if (t7 != 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00525038
                    charge(ctx, 1);
                    t4 = s3;
                }
                // 0x0052503c
                charge(ctx, 24);
                t6 = lui(0xFCB0);
                t5 = dsra32(s5, 0);
                t7 = 0x7C0000;
                s0 = si(-1);
                t7 = addiu(t7, -5056);  // &0x7BEC40
                t5 = addu(t5, t6);
                t4 = sll(t4, 3);
                s0 = dsrl32(s0, 0);
                t4 = addu(t4, t7);
                t5 = dsll32(t5, 0);
                s5 = s5 & s0;
                ld(a0, t4, 0);
                s5 = s5 | t5;
                a1 = s5;
                jal(ctx, 0x525070u, gen::fn_dpmul_00531230);
                t6 = dsra32(v0, 0);
                t7 = 0x7FF00000;
                t7 = t6 & t7;
                s1 = dsll32(t7, 0);
                s1 = dsrl32(s1, 0);
                t7 = 0x7CA00000;
                t7 = sltu(t7, s1);
                cc = t7 != 0;  // the condition, before the delay slot changes it
                t7 = 34;
                if (cc) {
                    backedge(ctx);
                    goto L_00524f90;
                }
                // 0x0052509c
                charge(ctx, 4);
                t7 = 0x7C900000;
                t7 = sltu(t7, s1);
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = 0x7FEF0000;
                if (cc) {
                    // 0x00525728
                    charge(ctx, 6);
                    t7 = 0x3500000;
                    s5 = v0 & s0;
                    t7 = addu(t6, t7);
                    t7 = dsll32(t7, 0);
                    s5 = s5 | t7;
                    backedge(ctx);
                } else {
                    // 0x005250ac
                    charge(ctx, 5);
                    s5 = v0 & s0;
                    t7 = t7 | 0xFFFF;
                    t7 = dsll32(t7, 0);
                    s5 = s5 | t7;
                    s5 = s5 | s0;
                }
                goto L_005250c0;
            }
            // 0x00525740
            charge(ctx, 2);
            lw(a1, sp, 0x20);
            if (i64(s0) < 0) {
                // 0x00525748
                charge(ctx, 4);
                s0 = subu(0, s0);
                v0 = s0 & 0xF;
                t7 = 0x7C0000;
                if (v0 != 0) {
                    // 0x00525758
                    charge(ctx, 7);
                    t6 = sll(v0, 3);
                    t7 = addiu(t7, -5256);
                    a0 = s5;
                    t6 = addu(t6, t7);
                    link(ctx, 0x525768u);  // $ra first: the delay slot below depends on it
                    ld(a1, t6, 0);
                    call(ctx, gen::fn_dpdiv_00531480);
                    s5 = v0;
                }
                // 0x00525774
                charge(ctx, 4);
                t7 = si(-16);
                s0 = s0 & t7;
                cc = s0 == 0;  // the condition, before the delay slot changes it
                s0 = sra(s0, 4);
                if (cc) {
                    backedge(ctx);
                L_005250c0:
                    charge(ctx, 1);
                    lw(a1, sp, 0x20);
                    goto L_005250c4;
                }
                // 0x00525784
                charge(ctx, 3);
                t7 = slti(s0, 32);
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = slti(s0, 2);
                if (cc) {
                    backedge(ctx);
                L_005253a0:
                    charge(ctx, 5);
                    t7 = 34;
                    lw(t5, sp, 0x50);
                    sw(t7, s6, 0);
                    s5 = 0;
                    if (t5 == 0) {
                        backedge(ctx);
                        goto L_00524b44;
                    }
                    // 0x005253b4
                    charge(ctx, 2);
                    lw(a1, sp, 0x48);
                    backedge(ctx);
                    goto L_00524fa8;
                }
                // 0x00525790
                charge(ctx, 2);
                t4 = 0;
                if (t7 == 0) {
                    // 0x00525798
                    charge(ctx, 4);
                    s1 = s0;
                    t7 = 0x7C0000;
                    s3 = t4;
                    s0 = addiu(t7, -5016);  // &0x7BEC68
                    for (;;) {
                        // 0x005257a8
                        charge(ctx, 3);
                        t7 = s1 & 0x1;
                        if (t7 == 0) {
                            s1 = sra(s1, 1);
                        } else {
                            // 0x005257b4
                            charge(ctx, 5);
                            ld(a0, s0, 0);
                            a1 = s5;
                            jal(ctx, 0x5257B8u, gen::fn_dpmul_00531230);
                            s5 = v0;
                            s1 = sra(s1, 1);
                        }
                        // 0x005257c8
                        charge(ctx, 4);
                        s0 = addiu(s0, 8);
                        t7 = slti(s1, 2);
                        s3 = addiu(s3, 1);
                        if (t7 != 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x005257d8
                    charge(ctx, 1);
                    t4 = s3;
                }
                // 0x005257dc
                charge(ctx, 16);
                t7 = 0x7C0000;
                sd(s5, sp, 0x40);
                t6 = sll(t4, 3);
                t7 = addiu(t7, -5016);  // &0x7BEC68
                t6 = addu(t6, t7);
                a1 = s5;
                ld(s0, t6, 0);
                s1 = 0;
                a0 = s0;
                jal(ctx, 0x5257FCu, gen::fn_dpmul_00531230);
                a0 = v0;
                s5 = v0;
                a1 = s1;
                jal(ctx, 0x52580Cu, gen::fn_dpcmp_005316d0);
                if (v0 != 0) {
                    lw(a1, sp, 0x20);
                    backedge(ctx);
                    goto L_005250c4;
                }
                // 0x0052581c
                charge(ctx, 11);
                ld(a0, sp, 0x40);
                a1 = a0;
                jal(ctx, 0x525820u, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s0;
                jal(ctx, 0x52582Cu, gen::fn_dpmul_00531230);
                a0 = v0;
                a1 = s1;
                jal(ctx, 0x525838u, gen::fn_dpcmp_005316d0);
                s5 = 1;
                if (v0 == 0) {
                    backedge(ctx);
                    goto L_005253a0;
                }
                // 0x00525848
                charge(ctx, 2);
                lw(a1, sp, 0x20);
                backedge(ctx);
                goto L_005250c4;
            }
            backedge(ctx);
        L_005250c4:
            charge(ctx, 9);
            a3 = s2;
            lw(a2, sp, 0xC);
            a0 = s6;
            link(ctx, 0x5250D0u);  // $ra first: the delay slot below depends on it
            lw(t0, sp, 0x30);
            call(ctx, gen::fn__s2b_00521758);
            t6 = addiu(v0, 12);
            sw(v0, sp, 0x50);
            sw(t6, sp, 0x58);
            lw(t7, sp, 0x50);
            for (;;) {
                // 0x005250e8
                charge(ctx, 23);
                a0 = s6;
                link(ctx, 0x5250ECu);  // $ra first: the delay slot below depends on it
                lw(a1, t7, 4);
                call(ctx, gen::fn__Balloc_00521578);
                lw(t4, sp, 0x50);
                a0 = addiu(v0, 12);
                lw(a1, sp, 0x58);
                lw(a2, t4, 16);
                sw(v0, sp, 0x4C);
                a2 = sll(a2, 2);
                a2 = addiu(a2, 8);
                jal(ctx, 0x52510Cu, gen::fn_memcpy_00521250);
                a0 = s6;
                a1 = s5;
                a2 = sp;
                a3 = addiu(sp, 0x4);
                jal(ctx, 0x525120u, gen::fn__d2b_005222c0);
                sw(v0, sp, 0x48);
                a0 = s6;
                a1 = 1;
                jal(ctx, 0x525130u, gen::fn__i2b_005219c8);
                ld(t5, sp, 0x18);
                s7 = v0;
                if (i64(t5) < 0) {
                    // 0x00525710
                    charge(ctx, 6);
                    lw(t6, sp, 0x54);
                    s4 = 0;
                    s1 = 0;
                    s2 = subu(0, t6);
                    a2 = s2;
                    backedge(ctx);
                } else {
                    // 0x00525144
                    charge(ctx, 4);
                    lw(s1, sp, 0x54);
                    a2 = 0;
                    s2 = 0;
                    s4 = s1;
                }
                // 0x00525154
                charge(ctx, 3);
                lw(t7, sp, 0x0);
                if (i64(t7) < 0) {
                    s1 = subu(s1, t7);
                } else {
                    // 0x00525160
                    charge(ctx, 1);
                    s2 = addu(s2, t7);
                }
                // 0x00525164
                charge(ctx, 7);
                lw(t5, sp, 0x4);
                t4 = addiu(t7, 1075);
                t7 = addu(t7, t5);
                v0 = addiu(t7, -1);
                t6 = slti(v0, -1022);
                s3 = s2;
                if (t6 == 0) {
                    // 0x00525180
                    charge(ctx, 2);
                    t7 = 54;
                    t4 = subu(t7, t5);
                }
                // 0x00525188
                charge(ctx, 9);
                v0 = addu(s1, t4);
                s2 = addu(s2, t4);
                s1 = v0;
                t7 = slt(s2, v0);
                if (t7 != 0) v0 = s2;
                t6 = slt(s3, v0);
                if (t6 != 0) v0 = s3;
                if (i64(v0) > 0) {
                    // 0x005251ac
                    charge(ctx, 3);
                    s3 = subu(s3, v0);
                    s2 = subu(s2, v0);
                    s1 = subu(s1, v0);
                }
                // 0x005251b8
                charge(ctx, 2);
                a1 = s7;
                if (i64(a2) > 0) {
                    // 0x005251c0
                    charge(ctx, 12);
                    a0 = s6;
                    jal(ctx, 0x5251C0u, gen::fn__pow5mult_00521c08);
                    lw(a2, sp, 0x48);
                    a0 = s6;
                    a1 = v0;
                    s7 = v0;
                    jal(ctx, 0x5251D4u, gen::fn__multiply_00521a00);
                    lw(a1, sp, 0x48);
                    s0 = v0;
                    a0 = s6;
                    jal(ctx, 0x5251E4u, gen::fn__Bfree_00521620);
                    sw(s0, sp, 0x48);
                }
                // 0x005251f0
                charge(ctx, 2);
                lw(a1, sp, 0x48);
                if (i64(s2) > 0) {
                    // 0x005251f8
                    charge(ctx, 4);
                    a2 = s2;
                    a0 = s6;
                    jal(ctx, 0x5251FCu, gen::fn__lshift_00521d10);
                    sw(v0, sp, 0x48);
                }
                // 0x00525208
                charge(ctx, 2);
                lw(a1, sp, 0x4C);
                if (i64(s4) > 0) {
                    // 0x00525210
                    charge(ctx, 4);
                    a2 = s4;
                    a0 = s6;
                    jal(ctx, 0x525214u, gen::fn__pow5mult_00521c08);
                    sw(v0, sp, 0x4C);
                }
                // 0x00525220
                charge(ctx, 2);
                lw(a1, sp, 0x4C);
                if (i64(s1) > 0) {
                    // 0x00525228
                    charge(ctx, 4);
                    a2 = s1;
                    a0 = s6;
                    jal(ctx, 0x52522Cu, gen::fn__lshift_00521d10);
                    sw(v0, sp, 0x4C);
                }
                // 0x00525238
                charge(ctx, 2);
                a1 = s7;
                if (i64(s3) > 0) {
                    // 0x00525240
                    charge(ctx, 4);
                    a2 = s3;
                    a0 = s6;
                    jal(ctx, 0x525244u, gen::fn__lshift_00521d10);
                    s7 = v0;
                }
                // 0x00525250
                charge(ctx, 12);
                lw(a1, sp, 0x48);
                a0 = s6;
                link(ctx, 0x525258u);  // $ra first: the delay slot below depends on it
                lw(a2, sp, 0x4C);
                call(ctx, gen::fn___mdiff_00521ed8);
                lw(s2, v0, 12);
                s4 = v0;
                a0 = v0;
                a1 = s7;
                link(ctx, 0x525270u);  // $ra first: the delay slot below depends on it
                sw(zero, v0, 12);
                call(ctx, gen::fn___mcmp_00521e70);
                if (i64(v0) < 0) {
                    goto L_00525280_119;
                }
                // 0x00525300
                charge(ctx, 2);
                a0 = s4;
                if (v0 == 0) {
                    goto L_00525308_124;
                }
                // 0x005253f8
                charge(ctx, 9);
                a1 = s7;
                jal(ctx, 0x5253F8u, gen::fn__ratio_00522440);
                a1 = 1;
                s0 = v0;
                a0 = v0;
                a1 = dsll32(a1, 30);
                jal(ctx, 0x52540Cu, gen::fn_dpcmp_005316d0);
                if (i64(v0) <= 0) {
                    // 0x0052541c
                    charge(ctx, 2);
                    t7 = si(-4096);
                    if (s2 != 0) {
                        // 0x00525424
                        charge(ctx, 3);
                        s0 = 1023;
                        s0 = dsll32(s0, 20);
                        s1 = s0;
                        goto L_00525430;
                    }
                    // 0x0052565c
                    charge(ctx, 4);
                    t7 = dsrl(t7, 12);
                    t7 = s5 & t7;
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = 1;
                    if (!cc) {
                        // 0x0052566c
                        charge(ctx, 2);
                        s0 = 1023;
                        if (s5 == t7) {
                            backedge(ctx);
                            goto L_005253a0;
                        }
                        // 0x00525674
                        charge(ctx, 4);
                        s1 = si(-1025);
                        s0 = dsll32(s0, 20);
                        s1 = dsll32(s1, 20);
                        backedge(ctx);
                        goto L_00525430;
                    }
                    // 0x00525684
                    charge(ctx, 6);
                    a1 = 1023;
                    a0 = s0;
                    a1 = dsll32(a1, 20);
                    jal(ctx, 0x52568Cu, gen::fn_dpcmp_005316d0);
                    if (i64(v0) >= 0) {
                        a1 = 511;
                        // 0x005256b8
                        charge(ctx, 5);
                        a0 = s0;
                        a1 = dsll32(a1, 21);
                        jal(ctx, 0x5256BCu, gen::fn_dpmul_00531230);
                        s0 = v0;
                        backedge(ctx);
                    } else {
                        // 0x0052569c
                        charge(ctx, 2);
                        s0 = 511;
                        s0 = dsll32(s0, 21);
                    }
                    // 0x005256a4
                    charge(ctx, 5);
                    a0 = 0;
                    a1 = s0;
                    jal(ctx, 0x5256A8u, gen::fn_dpsub_005311c8);
                    s1 = v0;
                    backedge(ctx);
                    goto L_00525430;
                }
                a1 = 511;
                // 0x005256d0
                charge(ctx, 6);
                a0 = s0;
                a1 = dsll32(a1, 21);
                jal(ctx, 0x5256D4u, gen::fn_dpmul_00531230);
                s0 = v0;
                s1 = v0;
                if (s2 == 0) {
                    // 0x005256e8
                    charge(ctx, 4);
                    a0 = 0;
                    a1 = v0;
                    jal(ctx, 0x5256ECu, gen::fn_dpsub_005311c8);
                    s1 = v0;
                }
                // 0x005256f8
                charge(ctx, 6);
                a1 = 511;
                a0 = s1;
                a1 = dsll32(a1, 21);
                jal(ctx, 0x525700u, gen::fn_dpadd_00531170);
                s1 = v0;
                backedge(ctx);
            L_00525430:
                charge(ctx, 8);
                t6 = dsra32(s5, 0);
                s3 = 0x7FF00000;
                t7 = t6 & s3;
                sw(t7, sp, 0x30);
                lw(t4, sp, 0x30);
                t7 = 0x7FE00000;
                cc = t4 != t7;  // the condition, before the delay slot changes it
                t7 = 0x3400000;
                if (!cc) {
                    // 0x00525450
                    charge(ctx, 23);
                    t7 = lui(0xFCB0);
                    sd(s5, sp, 0x40);
                    t7 = addu(t6, t7);
                    t6 = si(-1);
                    t7 = dsll32(t7, 0);
                    t6 = dsrl32(t6, 0);
                    s5 = s5 & t6;
                    s5 = s5 | t7;
                    a0 = s5;
                    jal(ctx, 0x525470u, gen::fn__ulp_00522058);
                    a1 = v0;
                    a0 = s1;
                    jal(ctx, 0x52547Cu, gen::fn_dpmul_00531230);
                    a0 = v0;
                    a1 = s5;
                    jal(ctx, 0x525488u, gen::fn_dpadd_00531170);
                    t7 = 0x7C9F0000;
                    t5 = dsra32(v0, 0);
                    t7 = t7 | 0xFFFF;
                    t6 = t5 & s3;
                    t7 = sltu(t7, t6);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = si(-2047);
                    if (cc) {
                        // 0x00525514
                        charge(ctx, 7);
                        t6 = si(-1);
                        t7 = 0x3500000;
                        t6 = dsrl32(t6, 0);
                        t7 = addu(t5, t7);
                        s5 = v0 & t6;
                        t7 = dsll32(t7, 0);
                        s5 = s5 | t7;
                        goto L_00525530;
                    }
                    // 0x005254ac
                    charge(ctx, 5);
                    ld(t4, sp, 0x40);
                    t7 = dsll32(t7, 20);
                    t7 = nor(0, t7);
                    t5 = si(-1);
                    if (t4 == t7) {
                        backedge(ctx);
                        break;
                    }
                    // 0x005254c0
                    charge(ctx, 8);
                    t7 = 0x7FEF0000;
                    t5 = dsrl32(t5, 0);
                    t7 = t7 | 0xFFFF;
                    s5 = v0 & t5;
                    t7 = dsll32(t7, 0);
                    s5 = s5 | t7;
                    s5 = s5 | t5;
                    lw(a1, sp, 0x48);
                    goto L_005254e0;
                }
                // 0x005255e0
                charge(ctx, 3);
                t7 = sltu(t7, t4);
                a0 = 1023;
                if (t7 == 0) {
                    // 0x005255ec
                    charge(ctx, 5);
                    a1 = s0;
                    a0 = dsll32(a0, 20);
                    jal(ctx, 0x5255F0u, gen::fn_dpcmp_005316d0);
                    a1 = 511;
                    if (i64(v0) <= 0) {
                        // 0x00525600
                        charge(ctx, 9);
                        a0 = s0;
                        a1 = dsll32(a1, 21);
                        jal(ctx, 0x525604u, gen::fn_dpadd_00531170);
                        a0 = v0;
                        jal(ctx, 0x52560Cu, gen::fn_dptoli_005317d0);
                        a0 = v0;
                        jal(ctx, 0x525614u, gen::fn_litodp_00531720);
                        s1 = v0;
                        if (s2 == 0) {
                            // 0x00525624
                            charge(ctx, 4);
                            a1 = v0;
                            a0 = 0;
                            jal(ctx, 0x525628u, gen::fn_dpsub_005311c8);
                            s1 = v0;
                        }
                    }
                }
                // 0x00525634
                charge(ctx, 10);
                a0 = s5;
                jal(ctx, 0x525634u, gen::fn__ulp_00522058);
                a1 = v0;
                a0 = s1;
                jal(ctx, 0x525640u, gen::fn_dpmul_00531230);
                a1 = s5;
                a0 = v0;
                jal(ctx, 0x52564Cu, gen::fn_dpadd_00531170);
                s5 = v0;
                backedge(ctx);
            L_00525530:
                charge(ctx, 10);
                t6 = 0x7FF00000;
                t7 = dsra32(s5, 0);
                t7 = t7 & t6;
                lw(t6, sp, 0x30);
                s1 = dsll32(t7, 0);
                s1 = dsrl32(s1, 0);
                t5 = dsll32(t6, 0);
                t5 = dsrl32(t5, 0);
                lw(a1, sp, 0x48);
                if (t5 != s1) {
                    backedge(ctx);
                L_005254e0:
                    charge(ctx, 13);
                    a0 = s6;
                    jal(ctx, 0x5254E0u, gen::fn__Bfree_00521620);
                    lw(a1, sp, 0x4C);
                    a0 = s6;
                    jal(ctx, 0x5254ECu, gen::fn__Bfree_00521620);
                    a0 = s6;
                    a1 = s7;
                    jal(ctx, 0x5254F8u, gen::fn__Bfree_00521620);
                    a0 = s6;
                    a1 = s4;
                    jal(ctx, 0x525504u, gen::fn__Bfree_00521620);
                    lw(t7, sp, 0x50);
                    backedge(ctx);
                    continue;
                }
                // 0x00525558
                charge(ctx, 9);
                a0 = s0;
                jal(ctx, 0x525558u, gen::fn___fixdfdi_0052ed30);
                a0 = v0;
                jal(ctx, 0x525560u, gen::fn___floatdidf_0052eac8);
                a0 = s0;
                a1 = v0;
                jal(ctx, 0x52556Cu, gen::fn_dpsub_005311c8);
                s0 = v0;
                if (s2 == 0) {
                    // 0x0052557c
                    charge(ctx, 5);
                    t7 = si(-4096);
                    t7 = dsrl(t7, 12);
                    t7 = s5 & t7;
                    t4 = 0x7C0000;
                    if (t7 != 0) {
                        goto L_00525590;
                    }
                    // 0x005255d0
                    charge(ctx, 4);
                    a0 = v0;
                    t4 = addiu(t4, -4880);
                    ld(a1, t4, 0);
                    backedge(ctx);
                L_005255b4:
                    charge(ctx, 4);
                    jal(ctx, 0x5255B4u, gen::fn_dpcmp_005316d0);
                    lw(a1, sp, 0x48);
                    if (i64(v0) < 0) {
                        backedge(ctx);
                        goto L_00524fa8;
                    }
                    // 0x005255c4
                    charge(ctx, 2);
                    backedge(ctx);
                    goto L_005254e0;
                }
            L_00525590:
                charge(ctx, 7);
                t7 = 0x7C0000;
                a0 = s0;
                t7 = addiu(t7, -4896);  // &0x7BECE0
                link(ctx, 0x52559Cu);  // $ra first: the delay slot below depends on it
                ld(a1, t7, 0);
                call(ctx, gen::fn_dpcmp_005316d0);
                t7 = 0x7C0000;
                if (i64(v0) < 0) {
                    backedge(ctx);
                    goto L_00524fa4;
                }
                // 0x005255ac
                charge(ctx, 2);
                a1 = s0;
                ld(a0, t7, -4888);
                goto L_005255b4;
            }
        L_00524f8c:
            charge(ctx, 1);
            t7 = 34;
        L_00524f90:
            charge(ctx, 5);
            lw(t4, sp, 0x50);
            t6 = 0x7C0000;
            sw(t7, s6, 0);
            ld(s5, t6, -4976);  // 0x7BEC90
            if (t4 == 0) {
                backedge(ctx);
                goto L_00524b44;
            }
        L_00524fa4:
            charge(ctx, 1);
            lw(a1, sp, 0x48);
        L_00524fa8:
            charge(ctx, 16);
            a0 = s6;
            jal(ctx, 0x524FA8u, gen::fn__Bfree_00521620);
            lw(a1, sp, 0x4C);
            a0 = s6;
            jal(ctx, 0x524FB4u, gen::fn__Bfree_00521620);
            a0 = s6;
            a1 = s7;
            jal(ctx, 0x524FC0u, gen::fn__Bfree_00521620);
            lw(a1, sp, 0x50);
            a0 = s6;
            jal(ctx, 0x524FCCu, gen::fn__Bfree_00521620);
            a0 = s6;
            a1 = s4;
            jal(ctx, 0x524FD8u, gen::fn__Bfree_00521620);
            lw(t5, sp, 0x8);
            backedge(ctx);
        } else {
            // 0x00524e88
            charge(ctx, 2);
            lw(t5, sp, 0x8);
            if (t2 != 0) {
                backedge(ctx);
            } else {
                // 0x00524e90
                charge(ctx, 2);
                if (t1 != 0) {
                    backedge(ctx);
                } else {
                    // 0x00524e98
                    charge(ctx, 2);
                    fp = a1;
                    backedge(ctx);
                }
            }
        }
        goto L_00524b48;
    }
L_00524d5c:
    charge(ctx, 2);
    if (s2 != 0) {
        a1 = fp;
    } else {
        // 0x00524d64
        charge(ctx, 2);
        if (t2 != 0) {
            a1 = fp;
            goto L_00524d78;
        }
        // 0x00524d6c
        charge(ctx, 2);
        if (t1 == 0) {
            fp = a1;
            backedge(ctx);
            goto L_00524b44;
        }
        // 0x00524d74
        charge(ctx, 1);
        a1 = fp;
        goto L_00524d78;
    }
L_00524d78:
    charge(ctx, 5);
    fp = addiu(fp, 0x1);
    t7 = 43;
    lb(a0, fp, 0x0);
    t3 = 0;
    if (a0 != t7) {
        // 0x00524d8c
        charge(ctx, 3);
        t7 = 45;
        cc = a0 != t7;  // the condition, before the delay slot changes it
        t7 = addiu(a0, -48);
        if (!cc) {
            // 0x00524d98
            charge(ctx, 1);
            t3 = 1;
            goto L_00524d9c;
        }
        goto L_00524da8;
    }
L_00524d9c:
    charge(ctx, 3);
    fp = addiu(fp, 0x1);
    lb(a0, fp, 0x0);
    t7 = addiu(a0, -48);
L_00524da8:
    charge(ctx, 3);
    t7 = sltiu(t7, 10);
    cc = t7 == 0;  // the condition, before the delay slot changes it
    t7 = 48;
    if (cc) {
        // 0x0052587c
        charge(ctx, 2);
        fp = a1;
        backedge(ctx);
    } else {
        // 0x00524db4
        charge(ctx, 2);
        cc = a0 != t7;  // the condition, before the delay slot changes it
        t7 = addiu(a0, -49);
        if (!cc) {
            // 0x00524dbc
            charge(ctx, 3);
            t7 = fp;
            t6 = 48;
            t7 = addiu(t7, 1);
            for (;;) {
                // 0x00524dc8
                charge(ctx, 7);
                lb(a0, t7, 0);
                if (a0 != t6) {
                    break;
                }
                t7 = addiu(t7, 1);
                backedge(ctx);
            }
            // 0x00524de4
            charge(ctx, 2);
            fp = t7;
            t7 = addiu(a0, -49);
        }
        // 0x00524dec
        charge(ctx, 3);
        t7 = sltiu(t7, 9);
        t4 = fp;
        if (t7 == 0) {
            // 0x00525874
            charge(ctx, 2);
            sd(zero, sp, 0x18);
            backedge(ctx);
        } else {
            // 0x00524df8
            charge(ctx, 7);
            a0 = addiu(a0, -48);
            sd(a0, sp, 0x18);
            fp = addiu(fp, 0x1);
            lb(a0, fp, 0x0);
            t7 = slti(a0, 48);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = subu(fp, t4);
            if (!cc) {
                // 0x00524e14
                charge(ctx, 3);
                t7 = slti(a0, 58);
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = subu(fp, t4);
                if (!cc) {
                    // 0x00524e20
                    charge(ctx, 1);
                    ld(t6, sp, 0x18);
                    for (;;) {
                        // 0x00524e24
                        charge(ctx, 10);
                        fp = addiu(fp, 0x1);
                        t7 = dsll(t6, 2);
                        t7 = t7 + t6;
                        t7 = dsll(t7, 1);
                        t7 = a0 + t7;
                        lb(a0, fp, 0x0);
                        t7 = daddiu(t7, -48);
                        t6 = slti(a0, 48);
                        sd(t7, sp, 0x18);
                        if (t6 == 0) {
                            // 0x00524e4c
                            charge(ctx, 3);
                            t7 = slti(a0, 58);
                            ld(t6, sp, 0x18);
                            if (t7 != 0) {
                                backedge(ctx);
                                continue;
                            }
                        }
                        break;
                    }
                    // 0x00524e58
                    charge(ctx, 1);
                    t7 = subu(fp, t4);
                }
            }
            // 0x00524e5c
            charge(ctx, 7);
            t6 = 0x980000;
            ld(t4, sp, 0x18);
            t7 = slti(t7, 9);
            t6 = t6 | 0x967F;  // &0x98967F
            if (t7 == 0) t4 = t6;
            sd(t4, sp, 0x18);
            if (t3 != 0) {
                // 0x00524e78
                charge(ctx, 2);
                t4 = 0 - t4;
                sd(t4, sp, 0x18);
            }
        }
    }
    goto L_00524e80;
L_00524b48:
    charge(ctx, 2);
    if (t5 != 0) {
        sw(fp, t5, 0);
    }
    // 0x00524b50
    charge(ctx, 3);
    lw(t6, sp, 0x10);
    v0 = s5;
    if (t6 != 0) {
        // 0x00524b5c
        charge(ctx, 3);
        a1 = s5;
        a0 = 0;
        jal(ctx, 0x524B60u, gen::fn_dpsub_005311c8);
    }
    // 0x00524b68 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x60);
    ld(s1, sp, 0x68);
    ld(s2, sp, 0x70);
    ld(s3, sp, 0x78);
    ld(s4, sp, 0x80);
    ld(s5, sp, 0x88);
    ld(s6, sp, 0x90);
    ld(s7, sp, 0x98);
    ld(fp, sp, 0xA0);
    ld(ra, sp, 0xA8);
    sp = addiu(sp, 0xB0);
    return;
L_00524b98:
    charge(ctx, 1);
    t6 = sll(t4, 24);
    goto L_00524b9c;
L_00525280_119:
    charge(ctx, 2);
    t7 = si(-4096);
    if (s2 != 0) {
        backedge(ctx);
        goto L_00524fa4;
    }
    // 0x00525288
    charge(ctx, 4);
    t7 = dsrl(t7, 12);
    t7 = s5 & t7;
    if (t7 == 0) {
        // 0x00525298
        charge(ctx, 10);
        a1 = s4;
        a0 = s6;
        a2 = 1;
        jal(ctx, 0x5252A0u, gen::fn__lshift_00521d10);
        s4 = v0;
        a0 = v0;
        a1 = s7;
        jal(ctx, 0x5252B0u, gen::fn___mcmp_00521e70);
        t7 = dsra32(s5, 0);
        if (i64(v0) <= 0) {
            backedge(ctx);
        } else {
        L_005252c0:
            charge(ctx, 16);
            t6 = 0x7FF00000;
            t7 = t7 & t6;
            t5 = lui(0xFFF0);
            t7 = addu(t7, t5);
            t6 = si(-1);
            v0 = dsll32(t7, 0);
            t6 = dsrl32(t6, 0);
            t7 = 0xF0000;
            v0 = dsrl32(v0, 0);
            t7 = t7 | 0xFFFF;
            s5 = s5 & t6;
            t7 = v0 | t7;
            t7 = dsll32(t7, 0);
            s5 = s5 | t7;
            s5 = s5 | t6;
            backedge(ctx);
        }
        goto L_00524fa4;
    }
    lw(a1, sp, 0x48);
    backedge(ctx);
    goto L_00524fa8;
L_00525308_124:
    charge(ctx, 2);
    t6 = si(-4096);
    if (s2 != 0) {
        // 0x00525310
        charge(ctx, 4);
        t6 = dsrl(t6, 12);
        t7 = s5 & t6;
        cc = t7 != t6;  // the condition, before the delay slot changes it
        t7 = dsll32(s5, 0);
        if (cc) {
            goto L_0052535c;
        }
        // 0x00525320
        charge(ctx, 15);
        t7 = dsra32(s5, 0);
        t6 = 0x7FF00000;
        t7 = t7 & t6;
        t5 = 0x100000;
        t7 = addu(t7, t5);
        s5 = dsll32(s5, 0);
        t7 = dsll32(t7, 0);
        s5 = dsrl32(s5, 0);
        t7 = dsrl32(t7, 0);
        t6 = si(-1);
        t7 = dsll32(t7, 0);
        t6 = dsll32(t6, 0);
        s5 = s5 | t7;
        s5 = s5 & t6;
        backedge(ctx);
        goto L_00524fa4;
    }
    // 0x005253d8
    charge(ctx, 5);
    t7 = si(-4096);
    t7 = dsrl(t7, 12);
    t7 = s5 & t7;
    if (t7 == 0) {
        // 0x005253ec
        charge(ctx, 2);
        t7 = dsra32(s5, 0);
        backedge(ctx);
        goto L_005252c0;
    }
    t7 = dsll32(s5, 0);
    backedge(ctx);
L_0052535c:
    charge(ctx, 4);
    t7 = dsra32(t7, 0);
    t7 = t7 & 0x1;
    lw(a1, sp, 0x48);
    if (t7 == 0) {
        backedge(ctx);
        goto L_00524fa8;
    }
    // 0x0052536c
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x005253bc
        charge(ctx, 7);
        a0 = s5;
        jal(ctx, 0x5253BCu, gen::fn__ulp_00522058);
        a1 = s5;
        a0 = v0;
        jal(ctx, 0x5253C8u, gen::fn_dpadd_00531170);
        s5 = v0;
        backedge(ctx);
        goto L_00524fa4;
    }
    // 0x00525374
    charge(ctx, 11);
    a0 = s5;
    jal(ctx, 0x525374u, gen::fn__ulp_00522058);
    a0 = s5;
    a1 = v0;
    jal(ctx, 0x525380u, gen::fn_dpsub_005311c8);
    a0 = v0;
    a1 = 0;
    s5 = v0;
    jal(ctx, 0x525390u, gen::fn_dpcmp_005316d0);
    lw(a1, sp, 0x48);
    if (v0 == 0) {
        goto L_005253a0;
    }
    backedge(ctx);
    goto L_00524fa8;
}

// 0x005258F8 strtod -- 40 bytes; frame 0x10: ra sp+0x0
// strtod(s, &end) = _strtod_r(_impure_ptr, s, &end), a tail call.
void strtod(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005258f8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t7 = a0;
    sd(ra, sp, 0x0);
    t6 = 0x780000;
    a2 = a1;
    lw(a0, t6, 12080);  // 0x782F30
    ld(ra, sp, 0x0);
    a1 = t7;
    sp = addiu(sp, 0x10);
    gen::fn__strtod_r_00524aa8(ctx);  // tail call
}

// 0x00525920 strtodf -- 52 bytes; frame 0x10: ra sp+0x0
// strtodf(s, &end): _strtod_r(_impure_ptr, s, &end) narrowed to a float by dptofp (the float in $f0).
void strtodf(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00525920
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t6 = a0;
    t7 = 0x780000;
    sd(ra, sp, 0x0);
    a2 = a1;
    lw(a0, t7, 12080);  // 0x782F30
    a1 = t6;
    jal(ctx, 0x525938u, gen::fn__strtod_r_00524aa8);
    a0 = v0;
    jal(ctx, 0x525940u, gen::fn_dptofp_005318a0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
