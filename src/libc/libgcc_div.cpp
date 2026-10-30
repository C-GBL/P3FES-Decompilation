// Slice libc: the 64-bit integer multiply / divide helpers the compiler calls (__muldi3, __divdi3, ...).
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions and the C standard only
// (ADR-0010: no GPL or newlib source was opened). Pair tests: tests/game/test_libc.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libc.h"

namespace p3fes::recomp_gen {
void fn___divdi3_0052eeb0(p3fes::EEContext&);
void fn___moddi3_0052f6a0(p3fes::EEContext&);
void fn___muldi3_0052ea78(p3fes::EEContext&);
void fn___udivdi3_0052fe98(p3fes::EEContext&);
void fn___udivmoddi4_0052efd8(p3fes::EEContext&);
void fn___udivmoddi4_0_0052f7d0(p3fes::EEContext&);
void fn___udivmoddi4_2_00530598(p3fes::EEContext&);
void fn___umoddi3_00530578(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace libc;  // the named offsets of p3fes/game/libc.h
namespace gen = ::p3fes::recomp_gen;

// 0x0052EA78 __muldi3 -- 76 bytes; leaf frame (no stack)
// __muldi3(a $a0, b $a1) -> $v0: the 64-bit product a * b (mod 2^64; long long travels in one 64-bit register). lo(a)
// * lo(b) as a full 64-bit unsigned product (multu1 into HI1/LO1, read back with pmfhl.lw / pcpyud), plus the cross
// terms lo(a)*hi(b) + hi(a)*lo(b) (mult / madd on LO) added into the high word.
void __muldi3(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t7{ctx, 15};
    // 0x0052ea78
    enter(ctx, 19);  // entry check point + this block's cycles
    v0 = dsll32(a0, 0);
    t7 = dsra32(a1, 0);
    v0 = dsra32(v0, 0);
    a1 = dsll32(a1, 0);
    mult(zero, v0, t7);
    a1 = dsra32(a1, 0);
    multu1(zero, v0, a1);
    a0 = dsra32(a0, 0);
    madd(a0, a0, a1);
    pmfhl(at, 0);
    pcpyud(at, at, zero);
    v0 = at;
    t7 = dsra32(v0, 0);
    v0 = dsll32(v0, 0);
    t7 = addu(t7, a0);
    v0 = dsrl32(v0, 0);
    t7 = dsll32(t7, 0);
    v0 = v0 | t7;
}

// 0x0052EEB0 __divdi3 -- 296 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// __divdi3(a $a0, b $a1) -> $v0: the signed 64-bit quotient a / b truncated toward zero: both operands made
// non-negative (the sign of the result in $s1), __udivmoddi4(|a|, |b|, NULL), negated when the signs differ. (Division
// by zero follows __udivmoddi4: the divu of the zero high half traps with break 7.)
void __divdi3(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0052eeb0
    enter(ctx, 20);  // entry check point + this block's cycles
    t7 = dsll32(a0, 0);
    t6 = dsll32(a1, 0);
    t7 = dsra32(t7, 0);
    sp = addiu(sp, -0x20);
    t7 = subu(0, t7);
    sd(s1, sp, 0x8);
    t6 = dsra32(t6, 0);
    sd(s0, sp, 0x0);
    t5 = dsll32(t7, 0);
    sd(ra, sp, 0x10);
    t6 = subu(0, t6);
    t7 = dsra32(a0, 0);
    t6 = dsll32(t6, 0);
    t4 = dsra32(a1, 0);
    t5 = dsrl32(t5, 0);
    t6 = dsrl32(t6, 0);
    s1 = 0;
    t1 = subu(0, t7);
    t0 = subu(0, t4);
    if (i64(t7) < 0) {
        // 0x0052ef00: a < 0: negate a (64-bit, by halves); result sign flips
        charge(ctx, 13);
        t7 = si(-1);
        s1 = si(-1);
        t7 = dsll32(t7, 0);
        t3 = t3 & t7;
        t3 = t3 | t5;
        t7 = dsll32(t3, 0);
        t7 = dsra32(t7, 0);
        t3 = dsll32(t3, 0);
        t7 = sltu(0, t7);
        t3 = dsrl32(t3, 0);
        t7 = subu(t1, t7);
        t7 = dsll32(t7, 0);
        a0 = t3 | t7;
    }
    // 0x0052ef34
    charge(ctx, 2);
    t7 = si(-1);
    if (i64(t4) < 0) {
        // 0x0052ef3c: b < 0: negate b; result sign flips
        charge(ctx, 12);
        s1 = nor(0, s1);
        t7 = dsll32(t7, 0);
        t2 = t2 & t7;
        t2 = t2 | t6;
        t7 = dsll32(t2, 0);
        t7 = dsra32(t7, 0);
        t2 = dsll32(t2, 0);
        t7 = sltu(0, t7);
        t2 = dsrl32(t2, 0);
        t7 = subu(t0, t7);
        t7 = dsll32(t7, 0);
        a1 = t2 | t7;
    }
    // 0x0052ef6c: __udivmoddi4(|a|, |b|, NULL), then the negated quotient prepared
    charge(ctx, 14);
    a2 = 0;
    jal(ctx, 0x52EF6Cu, gen::fn___udivmoddi4_0052efd8);
    t7 = dsll32(v0, 0);
    t6 = si(-1);
    t7 = dsra32(t7, 0);
    t6 = dsll32(t6, 0);
    t7 = subu(0, t7);
    s0 = s0 & t6;
    t7 = dsll32(t7, 0);
    t6 = dsra32(v0, 0);
    t7 = dsrl32(t7, 0);
    t6 = subu(0, t6);
    s0 = s0 | t7;
    if (s1 != 0) {
        // 0x0052efa4: signs differed: the negated quotient
        charge(ctx, 8);
        t7 = dsll32(s0, 0);
        t7 = dsra32(t7, 0);
        s0 = dsll32(s0, 0);
        t7 = sltu(0, t7);
        s0 = dsrl32(s0, 0);
        t7 = subu(t6, t7);
        t7 = dsll32(t7, 0);
        v0 = s0 | t7;
    }
    // 0x0052efc4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0052EFD8 __udivmoddi4 -- 1736 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10
// __udivmoddi4(n $a0, d $a1, rem $a2) -> $v0: unsigned 64-bit n / d, and *rem = n % d when rem is not NULL. Schoolbook
// division on 32-bit digits: d < 2^32 divides one or two digits, d >= 2^32 gives a one-digit quotient; each two-by-one
// digit step normalises the divisor by its leading-zero count (the 256-byte bit-length table at 0x7C0388) and divides
// in 16-bit halves with divu plus the usual at-most-two corrections. divu by zero raises break 7, as the original
// does.
void __udivmoddi4(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052efd8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t1 = dsra32(a1, 0);
    sd(s1, sp, 0x8);
    a1 = dsll32(a1, 0);
    t8 = dsll32(a0, 0);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    s1 = a2;
    t2 = dsra32(a0, 0);
    a1 = dsra32(a1, 0);
    t8 = dsra32(t8, 0);
    if (t1 != 0) {
        // 0x0052f400: d >= 2^32: the quotient is one digit (0 when hi(n) < hi(d))
        charge(ctx, 3);
        t7 = sltu(t2, t1);
        a3 = 0;
        if (t7 == 0) {
            // 0x0052f40c
            charge(ctx, 4);
            t7 = 0xFFFF;
            t7 = sltu(t7, t1);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0xFF0000;
            if (cc) {
                // 0x0052f684
                charge(ctx, 7);
                t6 = 16;
                t7 = t7 | 0xFFFF;
                t5 = 24;
                t7 = sltu(t7, t1);
                t4 = t6;
                if (t7 != 0) t4 = t5;
                backedge(ctx);
            } else {
                // 0x0052f41c
                charge(ctx, 4);
                t7 = 8;
                t6 = sltiu(t1, 256);
                t4 = t7;
                if (t6 != 0) t4 = 0;
            }
            // 0x0052f42c: leading zeros of hi(d) from the bit-length table; normalisation shift
            charge(ctx, 10);
            t6 = 0x7C0000;
            t7 = srlv(t1, t4);
            t6 = addiu(t6, 904);  // &0x7C0388
            t3 = 32;
            t7 = addu(t7, t6);
            lbu(t5, t7, 0);
            t5 = addu(t5, t4);
            t9 = subu(t3, t5);
            s0 = subu(t3, t9);
            if (t9 == 0) {
                // 0x0052f454: hi(d) already normalised: q = (n >= d)
                charge(ctx, 3);
                t7 = sltu(t1, t2);
                t5 = subu(t8, a1);
                if (t7 == 0) {
                    // 0x0052f460
                    charge(ctx, 3);
                    t7 = sltu(t8, a1);
                    a3 = 0;
                    if (t7 == 0) {
                        // 0x0052f46c
                        charge(ctx, 1);
                        t5 = subu(t8, a1);
                        goto L_0052f470;
                    }
                    goto L_0052f484;
                }
            L_0052f470:
                charge(ctx, 5);
                t6 = subu(t2, t1);
                t7 = sltu(t8, t5);
                a3 = 1;
                t2 = subu(t6, t7);
                t8 = t5;
                goto L_0052f484;
            }
            // 0x0052f4c0: normalise d and n, then the 2-by-1 step in 16-bit halves
            charge(ctx, 15);
            t6 = sllv(t1, t9);
            t7 = srlv(a1, s0);
            t4 = srlv(t2, s0);
            t1 = t6 | t7;
            t5 = sllv(t2, t9);
            t3 = srl(t1, 16);
            a2 = t1 & 0xFFFF;
            divu(t4, t3);
            t7 = srlv(t8, s0);
            t2 = t5 | t7;
            a1 = sllv(a1, t9);
            t5 = srl(t2, 16);
            t8 = sllv(t8, t9);
            if (t3 == 0) {
                brk(ctx, 0x52F4F8u, 0x7u);
            }
            // 0x0052f4fc
            charge(ctx, 9);
            mfhi(t6);
            mflo(t4);
            mflo(a3);
            t6 = sll(t6, 16);
            mult(v1, t4, a2);
            t6 = t6 | t5;
            t7 = sltu(t6, v1);
            if (t7 == 0) {
                t6 = subu(t6, v1);
            } else {
                // 0x0052f520
                charge(ctx, 4);
                t6 = addu(t6, t1);
                t7 = sltu(t6, t1);
                a3 = addiu(t4, -1);
                if (t7 == 0) {
                    // 0x0052f530
                    charge(ctx, 3);
                    t7 = sltu(t6, v1);
                    if (t7 != 0) {
                        // 0x0052f53c
                        charge(ctx, 2);
                        a3 = addiu(a3, -1);
                        t6 = addu(t6, t1);
                        goto L_0052f544;
                    }
                    t6 = subu(t6, v1);
                    goto L_0052f548;
                }
            L_0052f544:
                charge(ctx, 1);
                t6 = subu(t6, v1);
            }
        L_0052f548:
            charge(ctx, 4);
            t5 = t2 & 0xFFFF;
            divu(t6, t3);
            if (t3 == 0) {
                brk(ctx, 0x52F554u, 0x7u);
            }
            // 0x0052f558
            charge(ctx, 9);
            mflo(t7);
            mfhi(t6);
            mflo(t4);
            t6 = sll(t6, 16);
            mult(v1, t7, a2);
            a2 = t6 | t5;
            t7 = sltu(a2, v1);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = sll(a3, 16);
            if (!cc) {
                // 0x0052f57c
                charge(ctx, 4);
                a2 = addu(a2, t1);
                t7 = sltu(a2, t1);
                t4 = addiu(t4, -1);
                if (t7 == 0) {
                    // 0x0052f58c
                    charge(ctx, 3);
                    t7 = sltu(a2, v1);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = sll(a3, 16);
                    if (!cc) {
                        // 0x0052f598
                        charge(ctx, 2);
                        t4 = addiu(t4, -1);
                        a2 = addu(a2, t1);
                        goto L_0052f5a0;
                    }
                    goto L_0052f5a4;
                }
            L_0052f5a0:
                charge(ctx, 1);
                t7 = sll(a3, 16);
            }
        L_0052f5a4:
            charge(ctx, 16);
            t6 = a1 & 0xFFFF;
            a3 = t7 | t4;
            a2 = subu(a2, v1);
            t7 = a3 & 0xFFFF;
            t4 = srl(a1, 16);
            mult(s2, t7, t6);
            mult1(t3, t7, t4);
            t5 = srl(a3, 16);
            t2 = a2;
            mult(t6, t5, t6);
            t7 = srl(s2, 16);
            t3 = addu(t3, t7);
            t3 = addu(t3, t6);
            t6 = sltu(t3, t6);
            mult1(t4, t5, t4);
            if (t6 != 0) {
                // 0x0052f5e4
                charge(ctx, 2);
                t7 = 0x10000;
                t4 = addu(t4, t7);
            }
            // 0x0052f5ec
            charge(ctx, 7);
            t6 = srl(t3, 16);
            t5 = sll(t3, 16);
            a0 = addu(t4, t6);
            t7 = s2 & 0xFFFF;
            t6 = sltu(t2, a0);
            t3 = addu(t5, t7);
            if (t6 == 0) {
                // 0x0052f608
                charge(ctx, 2);
                t7 = sltu(t8, t3);
                if (a0 == t2) {
                    // 0x0052f610
                    charge(ctx, 2);
                    if (t7 != 0) {
                        goto L_0052f618;
                    }
                }
                goto L_0052f630;
            }
        L_0052f618:
            charge(ctx, 6);
            t5 = subu(t3, a1);
            t6 = subu(a0, t1);
            t7 = sltu(t3, t5);
            a3 = addiu(a3, -1);
            a0 = subu(t6, t7);
            t3 = t5;
        L_0052f630:
            charge(ctx, 2);
            s2 = 0;
            if (s1 == 0) {
                backedge(ctx);
            } else {
                // 0x0052f638
                charge(ctx, 19);
                t5 = subu(t8, t3);
                t4 = subu(a2, a0);
                t6 = sltu(t8, t5);
                t2 = subu(t4, t6);
                t5 = srlv(t5, t9);
                t7 = sllv(t2, s0);
                t6 = si(-1);
                t7 = t7 | t5;
                t6 = dsll32(t6, 0);
                t7 = dsll32(t7, 0);
                t0 = t0 & t6;
                t7 = dsrl32(t7, 0);
                t6 = srlv(t2, t9);
                t0 = t0 | t7;
                t6 = dsll32(t6, 0);
                t0 = dsll32(t0, 0);
                t0 = dsrl32(t0, 0);
                t0 = t0 | t6;
                backedge(ctx);
            L_0052f160:
                charge(ctx, 1);
                sd(t0, s1, 0);
            }
            // 0x0052f164 (the shared epilogue, written out on this path)
            charge(ctx, 17);
            t6 = si(-1);
            ld(s0, sp, 0x0);
            t7 = dsll32(a3, 0);
            ld(s1, sp, 0x8);
            t6 = dsll32(t6, 0);
            t7 = dsrl32(t7, 0);
            v0 = v0 & t6;
            t5 = dsll32(s2, 0);
            v0 = v0 | t7;
            ld(s2, sp, 0x10);
            t5 = dsrl32(t5, 0);
            v0 = dsll32(v0, 0);
            t5 = dsll32(t5, 0);
            v0 = dsrl32(v0, 0);
            v0 = v0 | t5;
            sp = addiu(sp, 0x20);
            return;
        }
    L_0052f484:
        charge(ctx, 2);
        s2 = 0;
        if (s1 != 0) {
            // 0x0052f48c
            charge(ctx, 13);
            t6 = si(-1);
            t7 = dsll32(t8, 0);
            t6 = dsll32(t6, 0);
            t7 = dsrl32(t7, 0);
            t0 = t0 & t6;
            t5 = dsll32(t2, 0);
            t0 = t0 | t7;
            t5 = dsrl32(t5, 0);
            t0 = dsll32(t0, 0);
            t5 = dsll32(t5, 0);
            t0 = dsrl32(t0, 0);
            t0 = t0 | t5;
            backedge(ctx);
            goto L_0052f160;
        }
        backedge(ctx);
    } else {
        // 0x0052f008
        charge(ctx, 3);
        t7 = sltu(t2, a1);
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = 0xFFFF;
        if (cc) {
            // 0x0052f1c4
            charge(ctx, 2);
            t7 = sltu(t7, a1);
            if (a1 == 0) {
                // 0x0052f1cc
                charge(ctx, 4);
                t7 = 1;
                divu(t7, t1);
                if (a1 == 0) {
                    brk(ctx, 0x52F1D8u, 0x7u);
                }
                // 0x0052f1dc
                charge(ctx, 3);
                mflo(a1);
                t7 = 0xFFFF;
                t7 = sltu(t7, a1);
            }
            // 0x0052f1e8
            charge(ctx, 2);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0xFF0000;
            if (cc) {
                // 0x0052f3e4
                charge(ctx, 7);
                t6 = 16;
                t7 = t7 | 0xFFFF;
                t5 = 24;
                t7 = sltu(t7, a1);
                t4 = t6;
                if (t7 != 0) t4 = t5;
                backedge(ctx);
            } else {
                // 0x0052f1f0
                charge(ctx, 4);
                t7 = 8;
                t6 = sltiu(a1, 256);
                t4 = t7;
                if (t6 != 0) t4 = 0;
            }
            // 0x0052f200
            charge(ctx, 10);
            t6 = 0x7C0000;
            t7 = srlv(a1, t4);
            t6 = addiu(t6, 904);  // &0x7C0388
            t3 = 32;
            t7 = addu(t7, t6);
            lbu(t5, t7, 0);
            t5 = addu(t5, t4);
            t9 = subu(t3, t5);
            s0 = subu(t3, t9);
            if (t9 != 0) {
                // 0x0052f2fc
                charge(ctx, 13);
                a1 = sllv(a1, t9);
                t1 = srl(a1, 16);
                t4 = srlv(t2, s0);
                divu(t4, t1);
                v1 = a1 & 0xFFFF;
                t6 = srlv(t8, s0);
                t7 = sllv(t2, t9);
                t2 = t7 | t6;
                a3 = t1;
                t6 = srl(t2, 16);
                t8 = sllv(t8, t9);
                if (t1 == 0) {
                    brk(ctx, 0x52F32Cu, 0x7u);
                }
                // 0x0052f330
                charge(ctx, 9);
                mfhi(t5);
                mflo(t4);
                mflo(a0);
                t5 = sll(t5, 16);
                mult(t3, t4, v1);
                t6 = t5 | t6;
                t7 = sltu(t6, t3);
                a2 = v1;
                if (t7 != 0) {
                    // 0x0052f354
                    charge(ctx, 4);
                    t6 = addu(t6, a1);
                    t7 = sltu(t6, a1);
                    a0 = addiu(t4, -1);
                    if (t7 != 0) {
                        goto L_0052f378;
                    }
                    // 0x0052f364
                    charge(ctx, 3);
                    t7 = sltu(t6, t3);
                    if (t7 != 0) {
                        // 0x0052f370
                        charge(ctx, 2);
                        a0 = addiu(a0, -1);
                        t6 = addu(t6, a1);
                        goto L_0052f378;
                    }
                    t6 = subu(t6, t3);
                    goto L_0052f37c;
                }
            L_0052f378:
                charge(ctx, 1);
                t6 = subu(t6, t3);
            L_0052f37c:
                charge(ctx, 4);
                t5 = t2 & 0xFFFF;
                divu(t6, a3);
                if (a3 == 0) {
                    brk(ctx, 0x52F388u, 0x7u);
                }
                // 0x0052f38c
                charge(ctx, 9);
                mflo(t7);
                mfhi(t6);
                mflo(a3);
                t6 = sll(t6, 16);
                mult(t3, t7, a2);
                t4 = t6 | t5;
                t7 = sltu(t4, t3);
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = sll(a0, 16);
                if (!cc) {
                    // 0x0052f3b0
                    charge(ctx, 4);
                    t4 = addu(t4, a1);
                    t7 = sltu(t4, a1);
                    a3 = addiu(a3, -1);
                    if (t7 == 0) {
                        // 0x0052f3c0
                        charge(ctx, 3);
                        t7 = sltu(t4, t3);
                        cc = t7 == 0;  // the condition, before the delay slot changes it
                        t7 = sll(a0, 16);
                        if (!cc) {
                            // 0x0052f3cc
                            charge(ctx, 2);
                            a3 = addiu(a3, -1);
                            t4 = addu(t4, a1);
                            goto L_0052f3d4;
                        }
                        goto L_0052f3d8;
                    }
                L_0052f3d4:
                    charge(ctx, 1);
                    t7 = sll(a0, 16);
                }
            L_0052f3d8:
                charge(ctx, 3);
                t2 = subu(t4, t3);
                s2 = t7 | a3;
                backedge(ctx);
            } else {
                // 0x0052f228
                charge(ctx, 4);
                t2 = subu(t2, a1);
                s2 = 1;
                t1 = srl(a1, 16);
                v1 = a1 & 0xFFFF;
            }
            // 0x0052f238
            charge(ctx, 4);
            divu(t2, t1);
            t4 = srl(t8, 16);
            if (t1 == 0) {
                brk(ctx, 0x52F244u, 0x7u);
            }
            // 0x0052f248
            charge(ctx, 9);
            mfhi(t6);
            mflo(t5);
            mflo(a3);
            t6 = sll(t6, 16);
            mult(t3, t5, v1);
            t6 = t6 | t4;
            t7 = sltu(t6, t3);
            if (t7 == 0) {
                t6 = subu(t6, t3);
            } else {
                // 0x0052f26c
                charge(ctx, 4);
                t6 = addu(t6, a1);
                t7 = sltu(t6, a1);
                a3 = addiu(t5, -1);
                if (t7 == 0) {
                    // 0x0052f27c
                    charge(ctx, 3);
                    t7 = sltu(t6, t3);
                    if (t7 != 0) {
                        // 0x0052f288
                        charge(ctx, 2);
                        a3 = addiu(a3, -1);
                        t6 = addu(t6, a1);
                        goto L_0052f290;
                    }
                    t6 = subu(t6, t3);
                    goto L_0052f294;
                }
            L_0052f290:
                charge(ctx, 1);
                t6 = subu(t6, t3);
            }
        L_0052f294:
            charge(ctx, 4);
            t5 = t8 & 0xFFFF;
            divu(t6, t1);
            if (t1 == 0) {
                brk(ctx, 0x52F2A0u, 0x7u);
            }
            // 0x0052f2a4
            charge(ctx, 9);
            mflo(t7);
            mfhi(t6);
            mflo(t2);
            t6 = sll(t6, 16);
            mult(t3, t7, v1);
            a0 = t6 | t5;
            t7 = sltu(a0, t3);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = sll(a3, 16);
            if (!cc) {
                // 0x0052f2c8
                charge(ctx, 4);
                a0 = addu(a0, a1);
                t7 = sltu(a0, a1);
                t2 = addiu(t2, -1);
                if (t7 == 0) {
                    // 0x0052f2d8
                    charge(ctx, 3);
                    t7 = sltu(a0, t3);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = sll(a3, 16);
                    if (!cc) {
                        // 0x0052f2e4
                        charge(ctx, 2);
                        a0 = addu(a0, a1);
                        t2 = addiu(t2, -1);
                        goto L_0052f2ec;
                    }
                    goto L_0052f2f0;
                }
            L_0052f2ec:
                charge(ctx, 1);
                t7 = sll(a3, 16);
            }
        L_0052f2f0:
            charge(ctx, 3);
            t8 = subu(a0, t3);
            a3 = t7 | t2;
            backedge(ctx);
        } else {
            // 0x0052f014
            charge(ctx, 3);
            t7 = sltu(t7, a1);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0xFF0000;
            if (cc) {
                // 0x0052f1a8
                charge(ctx, 7);
                t6 = 16;
                t7 = t7 | 0xFFFF;
                t5 = 24;
                t7 = sltu(t7, a1);
                t4 = t6;
                if (t7 != 0) t4 = t5;
                backedge(ctx);
            } else {
                // 0x0052f020
                charge(ctx, 4);
                t7 = 8;
                t6 = sltiu(a1, 256);
                t4 = t7;
                if (t6 != 0) t4 = 0;
            }
            // 0x0052f030
            charge(ctx, 10);
            t6 = 0x7C0000;
            t7 = srlv(a1, t4);
            t6 = addiu(t6, 904);  // &0x7C0388
            t3 = 32;
            t7 = addu(t7, t6);
            lbu(t5, t7, 0);
            t5 = addu(t5, t4);
            t9 = subu(t3, t5);
            t7 = subu(t3, t9);
            if (t9 != 0) {
                // 0x0052f058
                charge(ctx, 5);
                t6 = sllv(t2, t9);
                t7 = srlv(t8, t7);
                a1 = sllv(a1, t9);
                t2 = t6 | t7;
                t8 = sllv(t8, t9);
            }
            // 0x0052f06c
            charge(ctx, 6);
            t3 = srl(a1, 16);
            t1 = a1 & 0xFFFF;
            divu(t2, t3);
            t5 = srl(t8, 16);
            if (t3 == 0) {
                brk(ctx, 0x52F080u, 0x7u);
            }
            // 0x0052f084
            charge(ctx, 9);
            mflo(t7);
            mfhi(t6);
            mflo(t4);
            t6 = sll(t6, 16);
            mult(t2, t7, t1);
            t6 = t6 | t5;
            t7 = sltu(t6, t2);
            if (t7 == 0) {
                t6 = subu(t6, t2);
            } else {
                // 0x0052f0a8
                charge(ctx, 4);
                t6 = addu(t6, a1);
                t7 = sltu(t6, a1);
                t4 = addiu(t4, -1);
                if (t7 == 0) {
                    // 0x0052f0b8
                    charge(ctx, 3);
                    t7 = sltu(t6, t2);
                    if (t7 != 0) {
                        // 0x0052f0c4
                        charge(ctx, 2);
                        t4 = addiu(t4, -1);
                        t6 = addu(t6, a1);
                        goto L_0052f0cc;
                    }
                    t6 = subu(t6, t2);
                    goto L_0052f0d0;
                }
            L_0052f0cc:
                charge(ctx, 1);
                t6 = subu(t6, t2);
            }
        L_0052f0d0:
            charge(ctx, 4);
            t5 = t8 & 0xFFFF;
            divu(t6, t3);
            if (t3 == 0) {
                brk(ctx, 0x52F0DCu, 0x7u);
            }
            // 0x0052f0e0
            charge(ctx, 9);
            mflo(t7);
            mfhi(t6);
            mflo(t3);
            t6 = sll(t6, 16);
            mult(t2, t7, t1);
            a0 = t6 | t5;
            t7 = sltu(a0, t2);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = sll(t4, 16);
            if (!cc) {
                // 0x0052f104
                charge(ctx, 4);
                a0 = addu(a0, a1);
                t7 = sltu(a0, a1);
                t3 = addiu(t3, -1);
                if (t7 == 0) {
                    // 0x0052f114
                    charge(ctx, 3);
                    t7 = sltu(a0, t2);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = sll(t4, 16);
                    if (!cc) {
                        // 0x0052f120
                        charge(ctx, 2);
                        a0 = addu(a0, a1);
                        t3 = addiu(t3, -1);
                        goto L_0052f128;
                    }
                    goto L_0052f12c;
                }
            L_0052f128:
                charge(ctx, 1);
                t7 = sll(t4, 16);
            }
        L_0052f12c:
            charge(ctx, 3);
            t8 = subu(a0, t2);
            a3 = t7 | t3;
            s2 = 0;
        }
        // 0x0052f138
        charge(ctx, 2);
        t7 = srlv(t8, t9);
        if (s1 != 0) {
            // 0x0052f140
            charge(ctx, 8);
            t6 = si(-1);
            t7 = dsll32(t7, 0);
            t6 = dsll32(t6, 0);
            t0 = t0 & t6;
            t7 = dsrl32(t7, 0);
            t0 = t0 | t7;
            t0 = dsll32(t0, 0);
            t0 = dsrl32(t0, 0);
            goto L_0052f160;
        }
    }
    // 0x0052f164 (the shared epilogue, written out on this path)
    charge(ctx, 17);
    t6 = si(-1);
    ld(s0, sp, 0x0);
    t7 = dsll32(a3, 0);
    ld(s1, sp, 0x8);
    t6 = dsll32(t6, 0);
    t7 = dsrl32(t7, 0);
    v0 = v0 & t6;
    t5 = dsll32(s2, 0);
    v0 = v0 | t7;
    ld(s2, sp, 0x10);
    t5 = dsrl32(t5, 0);
    v0 = dsll32(v0, 0);
    t5 = dsll32(t5, 0);
    v0 = dsrl32(v0, 0);
    v0 = v0 | t5;
    sp = addiu(sp, 0x20);
}

// 0x0052F6A0 __moddi3 -- 304 bytes; frame 0x30: s1 sp+0x18, s0 sp+0x10, ra sp+0x20
// __moddi3(a $a0, b $a1) -> $v0: the signed 64-bit remainder a % b (sign of a): |a|, |b| into __udivmoddi4_0 with the
// remainder slot on the stack, negated when a < 0.
void __moddi3(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0052f6a0
    enter(ctx, 20);  // entry check point + this block's cycles
    t7 = dsll32(a0, 0);
    t6 = dsll32(a1, 0);
    t7 = dsra32(t7, 0);
    sp = addiu(sp, -0x30);
    t7 = subu(0, t7);
    sd(s1, sp, 0x18);
    t6 = dsra32(t6, 0);
    sd(s0, sp, 0x10);
    t5 = dsll32(t7, 0);
    sd(ra, sp, 0x20);
    t6 = subu(0, t6);
    t7 = dsra32(a0, 0);
    t6 = dsll32(t6, 0);
    t4 = dsra32(a1, 0);
    t5 = dsrl32(t5, 0);
    t6 = dsrl32(t6, 0);
    s1 = 0;
    t1 = subu(0, t7);
    t0 = subu(0, t4);
    if (i64(t7) < 0) {
        // 0x0052f6f0
        charge(ctx, 13);
        t7 = si(-1);
        s1 = si(-1);
        t7 = dsll32(t7, 0);
        t3 = t3 & t7;
        t3 = t3 | t5;
        t7 = dsll32(t3, 0);
        t7 = dsra32(t7, 0);
        t3 = dsll32(t3, 0);
        t7 = sltu(0, t7);
        t3 = dsrl32(t3, 0);
        t7 = subu(t1, t7);
        t7 = dsll32(t7, 0);
        a0 = t3 | t7;
    }
    // 0x0052f724
    charge(ctx, 2);
    t7 = si(-1);
    if (i64(t4) < 0) {
        // 0x0052f72c
        charge(ctx, 11);
        t7 = dsll32(t7, 0);
        t2 = t2 & t7;
        t2 = t2 | t6;
        t7 = dsll32(t2, 0);
        t7 = dsra32(t7, 0);
        t2 = dsll32(t2, 0);
        t7 = sltu(0, t7);
        t2 = dsrl32(t2, 0);
        t7 = subu(t0, t7);
        t7 = dsll32(t7, 0);
        a1 = t2 | t7;
    }
    // 0x0052f758
    charge(ctx, 4);
    a2 = sp;
    jal(ctx, 0x52F758u, gen::fn___udivmoddi4_0_0052f7d0);
    ld(t5, sp, 0x0);
    if (s1 != 0) {
        // 0x0052f768
        charge(ctx, 20);
        t6 = si(-1);
        t6 = dsll32(t6, 0);
        t7 = dsll32(t5, 0);
        s0 = s0 & t6;
        t7 = dsra32(t7, 0);
        t5 = dsra32(t5, 0);
        t7 = subu(0, t7);
        t5 = subu(0, t5);
        t7 = dsll32(t7, 0);
        t7 = dsrl32(t7, 0);
        s0 = s0 | t7;
        t6 = dsll32(s0, 0);
        t6 = dsra32(t6, 0);
        s0 = dsll32(s0, 0);
        t6 = sltu(0, t6);
        s0 = dsrl32(s0, 0);
        t5 = subu(t5, t6);
        t5 = dsll32(t5, 0);
        s0 = s0 | t5;
        sd(s0, sp, 0x0);
    }
    // 0x0052f7b8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(v0, sp, 0x0);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0052F7D0 __udivmoddi4_0 -- 1736 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10
// __udivmoddi4_0: a second, byte-identical copy of __udivmoddi4 (the one __moddi3 calls; libgcc inlines the helper
// into each division routine's object).
void __udivmoddi4_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052f7d0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t1 = dsra32(a1, 0);
    sd(s1, sp, 0x8);
    a1 = dsll32(a1, 0);
    t8 = dsll32(a0, 0);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    s1 = a2;
    t2 = dsra32(a0, 0);
    a1 = dsra32(a1, 0);
    t8 = dsra32(t8, 0);
    if (t1 != 0) {
        // 0x0052fbf8
        charge(ctx, 3);
        t7 = sltu(t2, t1);
        a3 = 0;
        if (t7 == 0) {
            // 0x0052fc04
            charge(ctx, 4);
            t7 = 0xFFFF;
            t7 = sltu(t7, t1);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0xFF0000;
            if (cc) {
                // 0x0052fe7c
                charge(ctx, 7);
                t6 = 16;
                t7 = t7 | 0xFFFF;
                t5 = 24;
                t7 = sltu(t7, t1);
                t4 = t6;
                if (t7 != 0) t4 = t5;
                backedge(ctx);
            } else {
                // 0x0052fc14
                charge(ctx, 4);
                t7 = 8;
                t6 = sltiu(t1, 256);
                t4 = t7;
                if (t6 != 0) t4 = 0;
            }
            // 0x0052fc24
            charge(ctx, 10);
            t6 = 0x7C0000;
            t7 = srlv(t1, t4);
            t6 = addiu(t6, 904);  // &0x7C0388
            t3 = 32;
            t7 = addu(t7, t6);
            lbu(t5, t7, 0);
            t5 = addu(t5, t4);
            t9 = subu(t3, t5);
            s0 = subu(t3, t9);
            if (t9 == 0) {
                // 0x0052fc4c
                charge(ctx, 3);
                t7 = sltu(t1, t2);
                t5 = subu(t8, a1);
                if (t7 == 0) {
                    // 0x0052fc58
                    charge(ctx, 3);
                    t7 = sltu(t8, a1);
                    a3 = 0;
                    if (t7 == 0) {
                        // 0x0052fc64
                        charge(ctx, 1);
                        t5 = subu(t8, a1);
                        goto L_0052fc68;
                    }
                    goto L_0052fc7c;
                }
            L_0052fc68:
                charge(ctx, 5);
                t6 = subu(t2, t1);
                t7 = sltu(t8, t5);
                a3 = 1;
                t2 = subu(t6, t7);
                t8 = t5;
                goto L_0052fc7c;
            }
            // 0x0052fcb8
            charge(ctx, 15);
            t6 = sllv(t1, t9);
            t7 = srlv(a1, s0);
            t4 = srlv(t2, s0);
            t1 = t6 | t7;
            t5 = sllv(t2, t9);
            t3 = srl(t1, 16);
            a2 = t1 & 0xFFFF;
            divu(t4, t3);
            t7 = srlv(t8, s0);
            t2 = t5 | t7;
            a1 = sllv(a1, t9);
            t5 = srl(t2, 16);
            t8 = sllv(t8, t9);
            if (t3 == 0) {
                brk(ctx, 0x52FCF0u, 0x7u);
            }
            // 0x0052fcf4
            charge(ctx, 9);
            mfhi(t6);
            mflo(t4);
            mflo(a3);
            t6 = sll(t6, 16);
            mult(v1, t4, a2);
            t6 = t6 | t5;
            t7 = sltu(t6, v1);
            if (t7 == 0) {
                t6 = subu(t6, v1);
            } else {
                // 0x0052fd18
                charge(ctx, 4);
                t6 = addu(t6, t1);
                t7 = sltu(t6, t1);
                a3 = addiu(t4, -1);
                if (t7 == 0) {
                    // 0x0052fd28
                    charge(ctx, 3);
                    t7 = sltu(t6, v1);
                    if (t7 != 0) {
                        // 0x0052fd34
                        charge(ctx, 2);
                        a3 = addiu(a3, -1);
                        t6 = addu(t6, t1);
                        goto L_0052fd3c;
                    }
                    t6 = subu(t6, v1);
                    goto L_0052fd40;
                }
            L_0052fd3c:
                charge(ctx, 1);
                t6 = subu(t6, v1);
            }
        L_0052fd40:
            charge(ctx, 4);
            t5 = t2 & 0xFFFF;
            divu(t6, t3);
            if (t3 == 0) {
                brk(ctx, 0x52FD4Cu, 0x7u);
            }
            // 0x0052fd50
            charge(ctx, 9);
            mflo(t7);
            mfhi(t6);
            mflo(t4);
            t6 = sll(t6, 16);
            mult(v1, t7, a2);
            a2 = t6 | t5;
            t7 = sltu(a2, v1);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = sll(a3, 16);
            if (!cc) {
                // 0x0052fd74
                charge(ctx, 4);
                a2 = addu(a2, t1);
                t7 = sltu(a2, t1);
                t4 = addiu(t4, -1);
                if (t7 == 0) {
                    // 0x0052fd84
                    charge(ctx, 3);
                    t7 = sltu(a2, v1);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = sll(a3, 16);
                    if (!cc) {
                        // 0x0052fd90
                        charge(ctx, 2);
                        t4 = addiu(t4, -1);
                        a2 = addu(a2, t1);
                        goto L_0052fd98;
                    }
                    goto L_0052fd9c;
                }
            L_0052fd98:
                charge(ctx, 1);
                t7 = sll(a3, 16);
            }
        L_0052fd9c:
            charge(ctx, 16);
            t6 = a1 & 0xFFFF;
            a3 = t7 | t4;
            a2 = subu(a2, v1);
            t7 = a3 & 0xFFFF;
            t4 = srl(a1, 16);
            mult(s2, t7, t6);
            mult1(t3, t7, t4);
            t5 = srl(a3, 16);
            t2 = a2;
            mult(t6, t5, t6);
            t7 = srl(s2, 16);
            t3 = addu(t3, t7);
            t3 = addu(t3, t6);
            t6 = sltu(t3, t6);
            mult1(t4, t5, t4);
            if (t6 != 0) {
                // 0x0052fddc
                charge(ctx, 2);
                t7 = 0x10000;
                t4 = addu(t4, t7);
            }
            // 0x0052fde4
            charge(ctx, 7);
            t6 = srl(t3, 16);
            t5 = sll(t3, 16);
            a0 = addu(t4, t6);
            t7 = s2 & 0xFFFF;
            t6 = sltu(t2, a0);
            t3 = addu(t5, t7);
            if (t6 == 0) {
                // 0x0052fe00
                charge(ctx, 2);
                t7 = sltu(t8, t3);
                if (a0 == t2) {
                    // 0x0052fe08
                    charge(ctx, 2);
                    if (t7 != 0) {
                        goto L_0052fe10;
                    }
                }
                goto L_0052fe28;
            }
        L_0052fe10:
            charge(ctx, 6);
            t5 = subu(t3, a1);
            t6 = subu(a0, t1);
            t7 = sltu(t3, t5);
            a3 = addiu(a3, -1);
            a0 = subu(t6, t7);
            t3 = t5;
        L_0052fe28:
            charge(ctx, 2);
            s2 = 0;
            if (s1 == 0) {
                backedge(ctx);
            } else {
                // 0x0052fe30
                charge(ctx, 19);
                t5 = subu(t8, t3);
                t4 = subu(a2, a0);
                t6 = sltu(t8, t5);
                t2 = subu(t4, t6);
                t5 = srlv(t5, t9);
                t7 = sllv(t2, s0);
                t6 = si(-1);
                t7 = t7 | t5;
                t6 = dsll32(t6, 0);
                t7 = dsll32(t7, 0);
                t0 = t0 & t6;
                t7 = dsrl32(t7, 0);
                t6 = srlv(t2, t9);
                t0 = t0 | t7;
                t6 = dsll32(t6, 0);
                t0 = dsll32(t0, 0);
                t0 = dsrl32(t0, 0);
                t0 = t0 | t6;
                backedge(ctx);
            L_0052f958:
                charge(ctx, 1);
                sd(t0, s1, 0);
            }
            // 0x0052f95c (the shared epilogue, written out on this path)
            charge(ctx, 17);
            t6 = si(-1);
            ld(s0, sp, 0x0);
            t7 = dsll32(a3, 0);
            ld(s1, sp, 0x8);
            t6 = dsll32(t6, 0);
            t7 = dsrl32(t7, 0);
            v0 = v0 & t6;
            t5 = dsll32(s2, 0);
            v0 = v0 | t7;
            ld(s2, sp, 0x10);
            t5 = dsrl32(t5, 0);
            v0 = dsll32(v0, 0);
            t5 = dsll32(t5, 0);
            v0 = dsrl32(v0, 0);
            v0 = v0 | t5;
            sp = addiu(sp, 0x20);
            return;
        }
    L_0052fc7c:
        charge(ctx, 2);
        s2 = 0;
        if (s1 != 0) {
            // 0x0052fc84
            charge(ctx, 13);
            t6 = si(-1);
            t7 = dsll32(t8, 0);
            t6 = dsll32(t6, 0);
            t7 = dsrl32(t7, 0);
            t0 = t0 & t6;
            t5 = dsll32(t2, 0);
            t0 = t0 | t7;
            t5 = dsrl32(t5, 0);
            t0 = dsll32(t0, 0);
            t5 = dsll32(t5, 0);
            t0 = dsrl32(t0, 0);
            t0 = t0 | t5;
            backedge(ctx);
            goto L_0052f958;
        }
        backedge(ctx);
    } else {
        // 0x0052f800
        charge(ctx, 3);
        t7 = sltu(t2, a1);
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = 0xFFFF;
        if (cc) {
            // 0x0052f9bc
            charge(ctx, 2);
            t7 = sltu(t7, a1);
            if (a1 == 0) {
                // 0x0052f9c4
                charge(ctx, 4);
                t7 = 1;
                divu(t7, t1);
                if (a1 == 0) {
                    brk(ctx, 0x52F9D0u, 0x7u);
                }
                // 0x0052f9d4
                charge(ctx, 3);
                mflo(a1);
                t7 = 0xFFFF;
                t7 = sltu(t7, a1);
            }
            // 0x0052f9e0
            charge(ctx, 2);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0xFF0000;
            if (cc) {
                // 0x0052fbdc
                charge(ctx, 7);
                t6 = 16;
                t7 = t7 | 0xFFFF;
                t5 = 24;
                t7 = sltu(t7, a1);
                t4 = t6;
                if (t7 != 0) t4 = t5;
                backedge(ctx);
            } else {
                // 0x0052f9e8
                charge(ctx, 4);
                t7 = 8;
                t6 = sltiu(a1, 256);
                t4 = t7;
                if (t6 != 0) t4 = 0;
            }
            // 0x0052f9f8
            charge(ctx, 10);
            t6 = 0x7C0000;
            t7 = srlv(a1, t4);
            t6 = addiu(t6, 904);  // &0x7C0388
            t3 = 32;
            t7 = addu(t7, t6);
            lbu(t5, t7, 0);
            t5 = addu(t5, t4);
            t9 = subu(t3, t5);
            s0 = subu(t3, t9);
            if (t9 != 0) {
                // 0x0052faf4
                charge(ctx, 13);
                a1 = sllv(a1, t9);
                t1 = srl(a1, 16);
                t4 = srlv(t2, s0);
                divu(t4, t1);
                v1 = a1 & 0xFFFF;
                t6 = srlv(t8, s0);
                t7 = sllv(t2, t9);
                t2 = t7 | t6;
                a3 = t1;
                t6 = srl(t2, 16);
                t8 = sllv(t8, t9);
                if (t1 == 0) {
                    brk(ctx, 0x52FB24u, 0x7u);
                }
                // 0x0052fb28
                charge(ctx, 9);
                mfhi(t5);
                mflo(t4);
                mflo(a0);
                t5 = sll(t5, 16);
                mult(t3, t4, v1);
                t6 = t5 | t6;
                t7 = sltu(t6, t3);
                a2 = v1;
                if (t7 != 0) {
                    // 0x0052fb4c
                    charge(ctx, 4);
                    t6 = addu(t6, a1);
                    t7 = sltu(t6, a1);
                    a0 = addiu(t4, -1);
                    if (t7 != 0) {
                        goto L_0052fb70;
                    }
                    // 0x0052fb5c
                    charge(ctx, 3);
                    t7 = sltu(t6, t3);
                    if (t7 != 0) {
                        // 0x0052fb68
                        charge(ctx, 2);
                        a0 = addiu(a0, -1);
                        t6 = addu(t6, a1);
                        goto L_0052fb70;
                    }
                    t6 = subu(t6, t3);
                    goto L_0052fb74;
                }
            L_0052fb70:
                charge(ctx, 1);
                t6 = subu(t6, t3);
            L_0052fb74:
                charge(ctx, 4);
                t5 = t2 & 0xFFFF;
                divu(t6, a3);
                if (a3 == 0) {
                    brk(ctx, 0x52FB80u, 0x7u);
                }
                // 0x0052fb84
                charge(ctx, 9);
                mflo(t7);
                mfhi(t6);
                mflo(a3);
                t6 = sll(t6, 16);
                mult(t3, t7, a2);
                t4 = t6 | t5;
                t7 = sltu(t4, t3);
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = sll(a0, 16);
                if (!cc) {
                    // 0x0052fba8
                    charge(ctx, 4);
                    t4 = addu(t4, a1);
                    t7 = sltu(t4, a1);
                    a3 = addiu(a3, -1);
                    if (t7 == 0) {
                        // 0x0052fbb8
                        charge(ctx, 3);
                        t7 = sltu(t4, t3);
                        cc = t7 == 0;  // the condition, before the delay slot changes it
                        t7 = sll(a0, 16);
                        if (!cc) {
                            // 0x0052fbc4
                            charge(ctx, 2);
                            a3 = addiu(a3, -1);
                            t4 = addu(t4, a1);
                            goto L_0052fbcc;
                        }
                        goto L_0052fbd0;
                    }
                L_0052fbcc:
                    charge(ctx, 1);
                    t7 = sll(a0, 16);
                }
            L_0052fbd0:
                charge(ctx, 3);
                t2 = subu(t4, t3);
                s2 = t7 | a3;
                backedge(ctx);
            } else {
                // 0x0052fa20
                charge(ctx, 4);
                t2 = subu(t2, a1);
                s2 = 1;
                t1 = srl(a1, 16);
                v1 = a1 & 0xFFFF;
            }
            // 0x0052fa30
            charge(ctx, 4);
            divu(t2, t1);
            t4 = srl(t8, 16);
            if (t1 == 0) {
                brk(ctx, 0x52FA3Cu, 0x7u);
            }
            // 0x0052fa40
            charge(ctx, 9);
            mfhi(t6);
            mflo(t5);
            mflo(a3);
            t6 = sll(t6, 16);
            mult(t3, t5, v1);
            t6 = t6 | t4;
            t7 = sltu(t6, t3);
            if (t7 == 0) {
                t6 = subu(t6, t3);
            } else {
                // 0x0052fa64
                charge(ctx, 4);
                t6 = addu(t6, a1);
                t7 = sltu(t6, a1);
                a3 = addiu(t5, -1);
                if (t7 == 0) {
                    // 0x0052fa74
                    charge(ctx, 3);
                    t7 = sltu(t6, t3);
                    if (t7 != 0) {
                        // 0x0052fa80
                        charge(ctx, 2);
                        a3 = addiu(a3, -1);
                        t6 = addu(t6, a1);
                        goto L_0052fa88;
                    }
                    t6 = subu(t6, t3);
                    goto L_0052fa8c;
                }
            L_0052fa88:
                charge(ctx, 1);
                t6 = subu(t6, t3);
            }
        L_0052fa8c:
            charge(ctx, 4);
            t5 = t8 & 0xFFFF;
            divu(t6, t1);
            if (t1 == 0) {
                brk(ctx, 0x52FA98u, 0x7u);
            }
            // 0x0052fa9c
            charge(ctx, 9);
            mflo(t7);
            mfhi(t6);
            mflo(t2);
            t6 = sll(t6, 16);
            mult(t3, t7, v1);
            a0 = t6 | t5;
            t7 = sltu(a0, t3);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = sll(a3, 16);
            if (!cc) {
                // 0x0052fac0
                charge(ctx, 4);
                a0 = addu(a0, a1);
                t7 = sltu(a0, a1);
                t2 = addiu(t2, -1);
                if (t7 == 0) {
                    // 0x0052fad0
                    charge(ctx, 3);
                    t7 = sltu(a0, t3);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = sll(a3, 16);
                    if (!cc) {
                        // 0x0052fadc
                        charge(ctx, 2);
                        a0 = addu(a0, a1);
                        t2 = addiu(t2, -1);
                        goto L_0052fae4;
                    }
                    goto L_0052fae8;
                }
            L_0052fae4:
                charge(ctx, 1);
                t7 = sll(a3, 16);
            }
        L_0052fae8:
            charge(ctx, 3);
            t8 = subu(a0, t3);
            a3 = t7 | t2;
            backedge(ctx);
        } else {
            // 0x0052f80c
            charge(ctx, 3);
            t7 = sltu(t7, a1);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0xFF0000;
            if (cc) {
                // 0x0052f9a0
                charge(ctx, 7);
                t6 = 16;
                t7 = t7 | 0xFFFF;
                t5 = 24;
                t7 = sltu(t7, a1);
                t4 = t6;
                if (t7 != 0) t4 = t5;
                backedge(ctx);
            } else {
                // 0x0052f818
                charge(ctx, 4);
                t7 = 8;
                t6 = sltiu(a1, 256);
                t4 = t7;
                if (t6 != 0) t4 = 0;
            }
            // 0x0052f828
            charge(ctx, 10);
            t6 = 0x7C0000;
            t7 = srlv(a1, t4);
            t6 = addiu(t6, 904);  // &0x7C0388
            t3 = 32;
            t7 = addu(t7, t6);
            lbu(t5, t7, 0);
            t5 = addu(t5, t4);
            t9 = subu(t3, t5);
            t7 = subu(t3, t9);
            if (t9 != 0) {
                // 0x0052f850
                charge(ctx, 5);
                t6 = sllv(t2, t9);
                t7 = srlv(t8, t7);
                a1 = sllv(a1, t9);
                t2 = t6 | t7;
                t8 = sllv(t8, t9);
            }
            // 0x0052f864
            charge(ctx, 6);
            t3 = srl(a1, 16);
            t1 = a1 & 0xFFFF;
            divu(t2, t3);
            t5 = srl(t8, 16);
            if (t3 == 0) {
                brk(ctx, 0x52F878u, 0x7u);
            }
            // 0x0052f87c
            charge(ctx, 9);
            mflo(t7);
            mfhi(t6);
            mflo(t4);
            t6 = sll(t6, 16);
            mult(t2, t7, t1);
            t6 = t6 | t5;
            t7 = sltu(t6, t2);
            if (t7 == 0) {
                t6 = subu(t6, t2);
            } else {
                // 0x0052f8a0
                charge(ctx, 4);
                t6 = addu(t6, a1);
                t7 = sltu(t6, a1);
                t4 = addiu(t4, -1);
                if (t7 == 0) {
                    // 0x0052f8b0
                    charge(ctx, 3);
                    t7 = sltu(t6, t2);
                    if (t7 != 0) {
                        // 0x0052f8bc
                        charge(ctx, 2);
                        t4 = addiu(t4, -1);
                        t6 = addu(t6, a1);
                        goto L_0052f8c4;
                    }
                    t6 = subu(t6, t2);
                    goto L_0052f8c8;
                }
            L_0052f8c4:
                charge(ctx, 1);
                t6 = subu(t6, t2);
            }
        L_0052f8c8:
            charge(ctx, 4);
            t5 = t8 & 0xFFFF;
            divu(t6, t3);
            if (t3 == 0) {
                brk(ctx, 0x52F8D4u, 0x7u);
            }
            // 0x0052f8d8
            charge(ctx, 9);
            mflo(t7);
            mfhi(t6);
            mflo(t3);
            t6 = sll(t6, 16);
            mult(t2, t7, t1);
            a0 = t6 | t5;
            t7 = sltu(a0, t2);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = sll(t4, 16);
            if (!cc) {
                // 0x0052f8fc
                charge(ctx, 4);
                a0 = addu(a0, a1);
                t7 = sltu(a0, a1);
                t3 = addiu(t3, -1);
                if (t7 == 0) {
                    // 0x0052f90c
                    charge(ctx, 3);
                    t7 = sltu(a0, t2);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = sll(t4, 16);
                    if (!cc) {
                        // 0x0052f918
                        charge(ctx, 2);
                        a0 = addu(a0, a1);
                        t3 = addiu(t3, -1);
                        goto L_0052f920;
                    }
                    goto L_0052f924;
                }
            L_0052f920:
                charge(ctx, 1);
                t7 = sll(t4, 16);
            }
        L_0052f924:
            charge(ctx, 3);
            t8 = subu(a0, t2);
            a3 = t7 | t3;
            s2 = 0;
        }
        // 0x0052f930
        charge(ctx, 2);
        t7 = srlv(t8, t9);
        if (s1 != 0) {
            // 0x0052f938
            charge(ctx, 8);
            t6 = si(-1);
            t7 = dsll32(t7, 0);
            t6 = dsll32(t6, 0);
            t0 = t0 & t6;
            t7 = dsrl32(t7, 0);
            t0 = t0 | t7;
            t0 = dsll32(t0, 0);
            t0 = dsrl32(t0, 0);
            goto L_0052f958;
        }
    }
    // 0x0052f95c (the shared epilogue, written out on this path)
    charge(ctx, 17);
    t6 = si(-1);
    ld(s0, sp, 0x0);
    t7 = dsll32(a3, 0);
    ld(s1, sp, 0x8);
    t6 = dsll32(t6, 0);
    t7 = dsrl32(t7, 0);
    v0 = v0 & t6;
    t5 = dsll32(s2, 0);
    v0 = v0 | t7;
    ld(s2, sp, 0x10);
    t5 = dsrl32(t5, 0);
    v0 = dsll32(v0, 0);
    t5 = dsll32(t5, 0);
    v0 = dsrl32(v0, 0);
    v0 = v0 | t5;
    sp = addiu(sp, 0x20);
}

// 0x0052FE98 __udivdi3 -- 1760 bytes; frame 0x10: ra sp+0x0
// __udivdi3(n $a0, d $a1) -> $v0: unsigned 64-bit n / d: the __udivmoddi4 algorithm inlined without the remainder
// store.
void __udivdi3(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052fe98
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 0;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0052feb0
    charge(ctx, 12);
    sp = addiu(sp, -0x20);
    t1 = dsra32(a1, 0);
    sd(s1, sp, 0x8);
    a1 = dsll32(a1, 0);
    t8 = dsll32(a0, 0);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    s1 = a2;
    t2 = dsra32(a0, 0);
    a1 = dsra32(a1, 0);
    t8 = dsra32(t8, 0);
    if (t1 != 0) {
        // 0x005302d8
        charge(ctx, 3);
        t7 = sltu(t2, t1);
        a3 = 0;
        if (t7 == 0) {
            // 0x005302e4
            charge(ctx, 4);
            t7 = 0xFFFF;
            t7 = sltu(t7, t1);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0xFF0000;
            if (cc) {
                // 0x0053055c
                charge(ctx, 7);
                t6 = 16;
                t7 = t7 | 0xFFFF;
                t5 = 24;
                t7 = sltu(t7, t1);
                t4 = t6;
                if (t7 != 0) t4 = t5;
                backedge(ctx);
            } else {
                // 0x005302f4
                charge(ctx, 4);
                t7 = 8;
                t6 = sltiu(t1, 256);
                t4 = t7;
                if (t6 != 0) t4 = 0;
            }
            // 0x00530304
            charge(ctx, 10);
            t6 = 0x7C0000;
            t7 = srlv(t1, t4);
            t6 = addiu(t6, 904);  // &0x7C0388
            t3 = 32;
            t7 = addu(t7, t6);
            lbu(t5, t7, 0);
            t5 = addu(t5, t4);
            t9 = subu(t3, t5);
            s0 = subu(t3, t9);
            if (t9 == 0) {
                // 0x0053032c
                charge(ctx, 3);
                t7 = sltu(t1, t2);
                t5 = subu(t8, a1);
                if (t7 == 0) {
                    // 0x00530338
                    charge(ctx, 3);
                    t7 = sltu(t8, a1);
                    a3 = 0;
                    if (t7 == 0) {
                        // 0x00530344
                        charge(ctx, 1);
                        t5 = subu(t8, a1);
                        goto L_00530348;
                    }
                    goto L_0053035c;
                }
            L_00530348:
                charge(ctx, 5);
                t6 = subu(t2, t1);
                t7 = sltu(t8, t5);
                a3 = 1;
                t2 = subu(t6, t7);
                t8 = t5;
                goto L_0053035c;
            }
            // 0x00530398
            charge(ctx, 15);
            t6 = sllv(t1, t9);
            t7 = srlv(a1, s0);
            t4 = srlv(t2, s0);
            t1 = t6 | t7;
            t5 = sllv(t2, t9);
            t3 = srl(t1, 16);
            a2 = t1 & 0xFFFF;
            divu(t4, t3);
            t7 = srlv(t8, s0);
            t2 = t5 | t7;
            a1 = sllv(a1, t9);
            t5 = srl(t2, 16);
            t8 = sllv(t8, t9);
            if (t3 == 0) {
                brk(ctx, 0x5303D0u, 0x7u);
            }
            // 0x005303d4
            charge(ctx, 9);
            mfhi(t6);
            mflo(t4);
            mflo(a3);
            t6 = sll(t6, 16);
            mult(v1, t4, a2);
            t6 = t6 | t5;
            t7 = sltu(t6, v1);
            if (t7 == 0) {
                t6 = subu(t6, v1);
            } else {
                // 0x005303f8
                charge(ctx, 4);
                t6 = addu(t6, t1);
                t7 = sltu(t6, t1);
                a3 = addiu(t4, -1);
                if (t7 == 0) {
                    // 0x00530408
                    charge(ctx, 3);
                    t7 = sltu(t6, v1);
                    if (t7 != 0) {
                        // 0x00530414
                        charge(ctx, 2);
                        a3 = addiu(a3, -1);
                        t6 = addu(t6, t1);
                        goto L_0053041c;
                    }
                    t6 = subu(t6, v1);
                    goto L_00530420;
                }
            L_0053041c:
                charge(ctx, 1);
                t6 = subu(t6, v1);
            }
        L_00530420:
            charge(ctx, 4);
            t5 = t2 & 0xFFFF;
            divu(t6, t3);
            if (t3 == 0) {
                brk(ctx, 0x53042Cu, 0x7u);
            }
            // 0x00530430
            charge(ctx, 9);
            mflo(t7);
            mfhi(t6);
            mflo(t4);
            t6 = sll(t6, 16);
            mult(v1, t7, a2);
            a2 = t6 | t5;
            t7 = sltu(a2, v1);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = sll(a3, 16);
            if (!cc) {
                // 0x00530454
                charge(ctx, 4);
                a2 = addu(a2, t1);
                t7 = sltu(a2, t1);
                t4 = addiu(t4, -1);
                if (t7 == 0) {
                    // 0x00530464
                    charge(ctx, 3);
                    t7 = sltu(a2, v1);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = sll(a3, 16);
                    if (!cc) {
                        // 0x00530470
                        charge(ctx, 2);
                        t4 = addiu(t4, -1);
                        a2 = addu(a2, t1);
                        goto L_00530478;
                    }
                    goto L_0053047c;
                }
            L_00530478:
                charge(ctx, 1);
                t7 = sll(a3, 16);
            }
        L_0053047c:
            charge(ctx, 16);
            t6 = a1 & 0xFFFF;
            a3 = t7 | t4;
            a2 = subu(a2, v1);
            t7 = a3 & 0xFFFF;
            t4 = srl(a1, 16);
            mult(s2, t7, t6);
            mult1(t3, t7, t4);
            t5 = srl(a3, 16);
            t2 = a2;
            mult(t6, t5, t6);
            t7 = srl(s2, 16);
            t3 = addu(t3, t7);
            t3 = addu(t3, t6);
            t6 = sltu(t3, t6);
            mult1(t4, t5, t4);
            if (t6 != 0) {
                // 0x005304bc
                charge(ctx, 2);
                t7 = 0x10000;
                t4 = addu(t4, t7);
            }
            // 0x005304c4
            charge(ctx, 7);
            t6 = srl(t3, 16);
            t5 = sll(t3, 16);
            a0 = addu(t4, t6);
            t7 = s2 & 0xFFFF;
            t6 = sltu(t2, a0);
            t3 = addu(t5, t7);
            if (t6 == 0) {
                // 0x005304e0
                charge(ctx, 2);
                t7 = sltu(t8, t3);
                if (a0 == t2) {
                    // 0x005304e8
                    charge(ctx, 2);
                    if (t7 != 0) {
                        goto L_005304f0;
                    }
                }
                goto L_00530508;
            }
        L_005304f0:
            charge(ctx, 6);
            t5 = subu(t3, a1);
            t6 = subu(a0, t1);
            t7 = sltu(t3, t5);
            a3 = addiu(a3, -1);
            a0 = subu(t6, t7);
            t3 = t5;
        L_00530508:
            charge(ctx, 2);
            s2 = 0;
            if (s1 == 0) {
                backedge(ctx);
            } else {
                // 0x00530510
                charge(ctx, 19);
                t5 = subu(t8, t3);
                t4 = subu(a2, a0);
                t6 = sltu(t8, t5);
                t2 = subu(t4, t6);
                t5 = srlv(t5, t9);
                t7 = sllv(t2, s0);
                t6 = si(-1);
                t7 = t7 | t5;
                t6 = dsll32(t6, 0);
                t7 = dsll32(t7, 0);
                t0 = t0 & t6;
                t7 = dsrl32(t7, 0);
                t6 = srlv(t2, t9);
                t0 = t0 | t7;
                t6 = dsll32(t6, 0);
                t0 = dsll32(t0, 0);
                t0 = dsrl32(t0, 0);
                t0 = t0 | t6;
                backedge(ctx);
            L_00530038:
                charge(ctx, 1);
                sd(t0, s1, 0);
            }
            // 0x0053003c (the shared epilogue, written out on this path)
            charge(ctx, 17);
            t6 = si(-1);
            ld(s0, sp, 0x0);
            t7 = dsll32(a3, 0);
            ld(s1, sp, 0x8);
            t6 = dsll32(t6, 0);
            t7 = dsrl32(t7, 0);
            v0 = v0 & t6;
            t5 = dsll32(s2, 0);
            v0 = v0 | t7;
            ld(s2, sp, 0x10);
            t5 = dsrl32(t5, 0);
            v0 = dsll32(v0, 0);
            t5 = dsll32(t5, 0);
            v0 = dsrl32(v0, 0);
            v0 = v0 | t5;
            sp = addiu(sp, 0x20);
            return;
        }
    L_0053035c:
        charge(ctx, 2);
        s2 = 0;
        if (s1 != 0) {
            // 0x00530364
            charge(ctx, 13);
            t6 = si(-1);
            t7 = dsll32(t8, 0);
            t6 = dsll32(t6, 0);
            t7 = dsrl32(t7, 0);
            t0 = t0 & t6;
            t5 = dsll32(t2, 0);
            t0 = t0 | t7;
            t5 = dsrl32(t5, 0);
            t0 = dsll32(t0, 0);
            t5 = dsll32(t5, 0);
            t0 = dsrl32(t0, 0);
            t0 = t0 | t5;
            backedge(ctx);
            goto L_00530038;
        }
        backedge(ctx);
    } else {
        // 0x0052fee0
        charge(ctx, 3);
        t7 = sltu(t2, a1);
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = 0xFFFF;
        if (cc) {
            // 0x0053009c
            charge(ctx, 2);
            t7 = sltu(t7, a1);
            if (a1 == 0) {
                // 0x005300a4
                charge(ctx, 4);
                t7 = 1;
                divu(t7, t1);
                if (a1 == 0) {
                    brk(ctx, 0x5300B0u, 0x7u);
                }
                // 0x005300b4
                charge(ctx, 3);
                mflo(a1);
                t7 = 0xFFFF;
                t7 = sltu(t7, a1);
            }
            // 0x005300c0
            charge(ctx, 2);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0xFF0000;
            if (cc) {
                // 0x005302bc
                charge(ctx, 7);
                t6 = 16;
                t7 = t7 | 0xFFFF;
                t5 = 24;
                t7 = sltu(t7, a1);
                t4 = t6;
                if (t7 != 0) t4 = t5;
                backedge(ctx);
            } else {
                // 0x005300c8
                charge(ctx, 4);
                t7 = 8;
                t6 = sltiu(a1, 256);
                t4 = t7;
                if (t6 != 0) t4 = 0;
            }
            // 0x005300d8
            charge(ctx, 10);
            t6 = 0x7C0000;
            t7 = srlv(a1, t4);
            t6 = addiu(t6, 904);  // &0x7C0388
            t3 = 32;
            t7 = addu(t7, t6);
            lbu(t5, t7, 0);
            t5 = addu(t5, t4);
            t9 = subu(t3, t5);
            s0 = subu(t3, t9);
            if (t9 != 0) {
                // 0x005301d4
                charge(ctx, 13);
                a1 = sllv(a1, t9);
                t1 = srl(a1, 16);
                t4 = srlv(t2, s0);
                divu(t4, t1);
                v1 = a1 & 0xFFFF;
                t6 = srlv(t8, s0);
                t7 = sllv(t2, t9);
                t2 = t7 | t6;
                a3 = t1;
                t6 = srl(t2, 16);
                t8 = sllv(t8, t9);
                if (t1 == 0) {
                    brk(ctx, 0x530204u, 0x7u);
                }
                // 0x00530208
                charge(ctx, 9);
                mfhi(t5);
                mflo(t4);
                mflo(a0);
                t5 = sll(t5, 16);
                mult(t3, t4, v1);
                t6 = t5 | t6;
                t7 = sltu(t6, t3);
                a2 = v1;
                if (t7 != 0) {
                    // 0x0053022c
                    charge(ctx, 4);
                    t6 = addu(t6, a1);
                    t7 = sltu(t6, a1);
                    a0 = addiu(t4, -1);
                    if (t7 != 0) {
                        goto L_00530250;
                    }
                    // 0x0053023c
                    charge(ctx, 3);
                    t7 = sltu(t6, t3);
                    if (t7 != 0) {
                        // 0x00530248
                        charge(ctx, 2);
                        a0 = addiu(a0, -1);
                        t6 = addu(t6, a1);
                        goto L_00530250;
                    }
                    t6 = subu(t6, t3);
                    goto L_00530254;
                }
            L_00530250:
                charge(ctx, 1);
                t6 = subu(t6, t3);
            L_00530254:
                charge(ctx, 4);
                t5 = t2 & 0xFFFF;
                divu(t6, a3);
                if (a3 == 0) {
                    brk(ctx, 0x530260u, 0x7u);
                }
                // 0x00530264
                charge(ctx, 9);
                mflo(t7);
                mfhi(t6);
                mflo(a3);
                t6 = sll(t6, 16);
                mult(t3, t7, a2);
                t4 = t6 | t5;
                t7 = sltu(t4, t3);
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = sll(a0, 16);
                if (!cc) {
                    // 0x00530288
                    charge(ctx, 4);
                    t4 = addu(t4, a1);
                    t7 = sltu(t4, a1);
                    a3 = addiu(a3, -1);
                    if (t7 == 0) {
                        // 0x00530298
                        charge(ctx, 3);
                        t7 = sltu(t4, t3);
                        cc = t7 == 0;  // the condition, before the delay slot changes it
                        t7 = sll(a0, 16);
                        if (!cc) {
                            // 0x005302a4
                            charge(ctx, 2);
                            a3 = addiu(a3, -1);
                            t4 = addu(t4, a1);
                            goto L_005302ac;
                        }
                        goto L_005302b0;
                    }
                L_005302ac:
                    charge(ctx, 1);
                    t7 = sll(a0, 16);
                }
            L_005302b0:
                charge(ctx, 3);
                t2 = subu(t4, t3);
                s2 = t7 | a3;
                backedge(ctx);
            } else {
                // 0x00530100
                charge(ctx, 4);
                t2 = subu(t2, a1);
                s2 = 1;
                t1 = srl(a1, 16);
                v1 = a1 & 0xFFFF;
            }
            // 0x00530110
            charge(ctx, 4);
            divu(t2, t1);
            t4 = srl(t8, 16);
            if (t1 == 0) {
                brk(ctx, 0x53011Cu, 0x7u);
            }
            // 0x00530120
            charge(ctx, 9);
            mfhi(t6);
            mflo(t5);
            mflo(a3);
            t6 = sll(t6, 16);
            mult(t3, t5, v1);
            t6 = t6 | t4;
            t7 = sltu(t6, t3);
            if (t7 == 0) {
                t6 = subu(t6, t3);
            } else {
                // 0x00530144
                charge(ctx, 4);
                t6 = addu(t6, a1);
                t7 = sltu(t6, a1);
                a3 = addiu(t5, -1);
                if (t7 == 0) {
                    // 0x00530154
                    charge(ctx, 3);
                    t7 = sltu(t6, t3);
                    if (t7 != 0) {
                        // 0x00530160
                        charge(ctx, 2);
                        a3 = addiu(a3, -1);
                        t6 = addu(t6, a1);
                        goto L_00530168;
                    }
                    t6 = subu(t6, t3);
                    goto L_0053016c;
                }
            L_00530168:
                charge(ctx, 1);
                t6 = subu(t6, t3);
            }
        L_0053016c:
            charge(ctx, 4);
            t5 = t8 & 0xFFFF;
            divu(t6, t1);
            if (t1 == 0) {
                brk(ctx, 0x530178u, 0x7u);
            }
            // 0x0053017c
            charge(ctx, 9);
            mflo(t7);
            mfhi(t6);
            mflo(t2);
            t6 = sll(t6, 16);
            mult(t3, t7, v1);
            a0 = t6 | t5;
            t7 = sltu(a0, t3);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = sll(a3, 16);
            if (!cc) {
                // 0x005301a0
                charge(ctx, 4);
                a0 = addu(a0, a1);
                t7 = sltu(a0, a1);
                t2 = addiu(t2, -1);
                if (t7 == 0) {
                    // 0x005301b0
                    charge(ctx, 3);
                    t7 = sltu(a0, t3);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = sll(a3, 16);
                    if (!cc) {
                        // 0x005301bc
                        charge(ctx, 2);
                        a0 = addu(a0, a1);
                        t2 = addiu(t2, -1);
                        goto L_005301c4;
                    }
                    goto L_005301c8;
                }
            L_005301c4:
                charge(ctx, 1);
                t7 = sll(a3, 16);
            }
        L_005301c8:
            charge(ctx, 3);
            t8 = subu(a0, t3);
            a3 = t7 | t2;
            backedge(ctx);
        } else {
            // 0x0052feec
            charge(ctx, 3);
            t7 = sltu(t7, a1);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0xFF0000;
            if (cc) {
                // 0x00530080
                charge(ctx, 7);
                t6 = 16;
                t7 = t7 | 0xFFFF;
                t5 = 24;
                t7 = sltu(t7, a1);
                t4 = t6;
                if (t7 != 0) t4 = t5;
                backedge(ctx);
            } else {
                // 0x0052fef8
                charge(ctx, 4);
                t7 = 8;
                t6 = sltiu(a1, 256);
                t4 = t7;
                if (t6 != 0) t4 = 0;
            }
            // 0x0052ff08
            charge(ctx, 10);
            t6 = 0x7C0000;
            t7 = srlv(a1, t4);
            t6 = addiu(t6, 904);  // &0x7C0388
            t3 = 32;
            t7 = addu(t7, t6);
            lbu(t5, t7, 0);
            t5 = addu(t5, t4);
            t9 = subu(t3, t5);
            t7 = subu(t3, t9);
            if (t9 != 0) {
                // 0x0052ff30
                charge(ctx, 5);
                t6 = sllv(t2, t9);
                t7 = srlv(t8, t7);
                a1 = sllv(a1, t9);
                t2 = t6 | t7;
                t8 = sllv(t8, t9);
            }
            // 0x0052ff44
            charge(ctx, 6);
            t3 = srl(a1, 16);
            t1 = a1 & 0xFFFF;
            divu(t2, t3);
            t5 = srl(t8, 16);
            if (t3 == 0) {
                brk(ctx, 0x52FF58u, 0x7u);
            }
            // 0x0052ff5c
            charge(ctx, 9);
            mflo(t7);
            mfhi(t6);
            mflo(t4);
            t6 = sll(t6, 16);
            mult(t2, t7, t1);
            t6 = t6 | t5;
            t7 = sltu(t6, t2);
            if (t7 == 0) {
                t6 = subu(t6, t2);
            } else {
                // 0x0052ff80
                charge(ctx, 4);
                t6 = addu(t6, a1);
                t7 = sltu(t6, a1);
                t4 = addiu(t4, -1);
                if (t7 == 0) {
                    // 0x0052ff90
                    charge(ctx, 3);
                    t7 = sltu(t6, t2);
                    if (t7 != 0) {
                        // 0x0052ff9c
                        charge(ctx, 2);
                        t4 = addiu(t4, -1);
                        t6 = addu(t6, a1);
                        goto L_0052ffa4;
                    }
                    t6 = subu(t6, t2);
                    goto L_0052ffa8;
                }
            L_0052ffa4:
                charge(ctx, 1);
                t6 = subu(t6, t2);
            }
        L_0052ffa8:
            charge(ctx, 4);
            t5 = t8 & 0xFFFF;
            divu(t6, t3);
            if (t3 == 0) {
                brk(ctx, 0x52FFB4u, 0x7u);
            }
            // 0x0052ffb8
            charge(ctx, 9);
            mflo(t7);
            mfhi(t6);
            mflo(t3);
            t6 = sll(t6, 16);
            mult(t2, t7, t1);
            a0 = t6 | t5;
            t7 = sltu(a0, t2);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = sll(t4, 16);
            if (!cc) {
                // 0x0052ffdc
                charge(ctx, 4);
                a0 = addu(a0, a1);
                t7 = sltu(a0, a1);
                t3 = addiu(t3, -1);
                if (t7 == 0) {
                    // 0x0052ffec
                    charge(ctx, 3);
                    t7 = sltu(a0, t2);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = sll(t4, 16);
                    if (!cc) {
                        // 0x0052fff8
                        charge(ctx, 2);
                        a0 = addu(a0, a1);
                        t3 = addiu(t3, -1);
                        goto L_00530000;
                    }
                    goto L_00530004;
                }
            L_00530000:
                charge(ctx, 1);
                t7 = sll(t4, 16);
            }
        L_00530004:
            charge(ctx, 3);
            t8 = subu(a0, t2);
            a3 = t7 | t3;
            s2 = 0;
        }
        // 0x00530010
        charge(ctx, 2);
        t7 = srlv(t8, t9);
        if (s1 != 0) {
            // 0x00530018
            charge(ctx, 8);
            t6 = si(-1);
            t7 = dsll32(t7, 0);
            t6 = dsll32(t6, 0);
            t0 = t0 & t6;
            t7 = dsrl32(t7, 0);
            t0 = t0 | t7;
            t0 = dsll32(t0, 0);
            t0 = dsrl32(t0, 0);
            goto L_00530038;
        }
    }
    // 0x0053003c (the shared epilogue, written out on this path)
    charge(ctx, 17);
    t6 = si(-1);
    ld(s0, sp, 0x0);
    t7 = dsll32(a3, 0);
    ld(s1, sp, 0x8);
    t6 = dsll32(t6, 0);
    t7 = dsrl32(t7, 0);
    v0 = v0 & t6;
    t5 = dsll32(s2, 0);
    v0 = v0 | t7;
    ld(s2, sp, 0x10);
    t5 = dsrl32(t5, 0);
    v0 = dsll32(v0, 0);
    t5 = dsll32(t5, 0);
    v0 = dsrl32(v0, 0);
    v0 = v0 | t5;
    sp = addiu(sp, 0x20);
}

// 0x00530578 __umoddi3 -- 32 bytes; frame 0x20: ra sp+0x10
// __umoddi3(n $a0, d $a1) -> $v0: unsigned 64-bit n % d: __udivmoddi4_2(n, d, &slot) and the slot read back from the
// 32-byte frame.
void __umoddi3(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00530578
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    a2 = sp;
    jal(ctx, 0x530580u, gen::fn___udivmoddi4_2_00530598);
    ld(v0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00530598 __udivmoddi4_2 -- 1736 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10
// __udivmoddi4_2: the third copy of __udivmoddi4 (called by __umoddi3).
void __udivmoddi4_2(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00530598
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t1 = dsra32(a1, 0);
    sd(s1, sp, 0x8);
    a1 = dsll32(a1, 0);
    t8 = dsll32(a0, 0);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    s1 = a2;
    t2 = dsra32(a0, 0);
    a1 = dsra32(a1, 0);
    t8 = dsra32(t8, 0);
    if (t1 != 0) {
        // 0x005309c0
        charge(ctx, 3);
        t7 = sltu(t2, t1);
        a3 = 0;
        if (t7 == 0) {
            // 0x005309cc
            charge(ctx, 4);
            t7 = 0xFFFF;
            t7 = sltu(t7, t1);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0xFF0000;
            if (cc) {
                // 0x00530c44
                charge(ctx, 7);
                t6 = 16;
                t7 = t7 | 0xFFFF;
                t5 = 24;
                t7 = sltu(t7, t1);
                t4 = t6;
                if (t7 != 0) t4 = t5;
                backedge(ctx);
            } else {
                // 0x005309dc
                charge(ctx, 4);
                t7 = 8;
                t6 = sltiu(t1, 256);
                t4 = t7;
                if (t6 != 0) t4 = 0;
            }
            // 0x005309ec
            charge(ctx, 10);
            t6 = 0x7C0000;
            t7 = srlv(t1, t4);
            t6 = addiu(t6, 904);  // &0x7C0388
            t3 = 32;
            t7 = addu(t7, t6);
            lbu(t5, t7, 0);
            t5 = addu(t5, t4);
            t9 = subu(t3, t5);
            s0 = subu(t3, t9);
            if (t9 == 0) {
                // 0x00530a14
                charge(ctx, 3);
                t7 = sltu(t1, t2);
                t5 = subu(t8, a1);
                if (t7 == 0) {
                    // 0x00530a20
                    charge(ctx, 3);
                    t7 = sltu(t8, a1);
                    a3 = 0;
                    if (t7 == 0) {
                        // 0x00530a2c
                        charge(ctx, 1);
                        t5 = subu(t8, a1);
                        goto L_00530a30;
                    }
                    goto L_00530a44;
                }
            L_00530a30:
                charge(ctx, 5);
                t6 = subu(t2, t1);
                t7 = sltu(t8, t5);
                a3 = 1;
                t2 = subu(t6, t7);
                t8 = t5;
                goto L_00530a44;
            }
            // 0x00530a80
            charge(ctx, 15);
            t6 = sllv(t1, t9);
            t7 = srlv(a1, s0);
            t4 = srlv(t2, s0);
            t1 = t6 | t7;
            t5 = sllv(t2, t9);
            t3 = srl(t1, 16);
            a2 = t1 & 0xFFFF;
            divu(t4, t3);
            t7 = srlv(t8, s0);
            t2 = t5 | t7;
            a1 = sllv(a1, t9);
            t5 = srl(t2, 16);
            t8 = sllv(t8, t9);
            if (t3 == 0) {
                brk(ctx, 0x530AB8u, 0x7u);
            }
            // 0x00530abc
            charge(ctx, 9);
            mfhi(t6);
            mflo(t4);
            mflo(a3);
            t6 = sll(t6, 16);
            mult(v1, t4, a2);
            t6 = t6 | t5;
            t7 = sltu(t6, v1);
            if (t7 == 0) {
                t6 = subu(t6, v1);
            } else {
                // 0x00530ae0
                charge(ctx, 4);
                t6 = addu(t6, t1);
                t7 = sltu(t6, t1);
                a3 = addiu(t4, -1);
                if (t7 == 0) {
                    // 0x00530af0
                    charge(ctx, 3);
                    t7 = sltu(t6, v1);
                    if (t7 != 0) {
                        // 0x00530afc
                        charge(ctx, 2);
                        a3 = addiu(a3, -1);
                        t6 = addu(t6, t1);
                        goto L_00530b04;
                    }
                    t6 = subu(t6, v1);
                    goto L_00530b08;
                }
            L_00530b04:
                charge(ctx, 1);
                t6 = subu(t6, v1);
            }
        L_00530b08:
            charge(ctx, 4);
            t5 = t2 & 0xFFFF;
            divu(t6, t3);
            if (t3 == 0) {
                brk(ctx, 0x530B14u, 0x7u);
            }
            // 0x00530b18
            charge(ctx, 9);
            mflo(t7);
            mfhi(t6);
            mflo(t4);
            t6 = sll(t6, 16);
            mult(v1, t7, a2);
            a2 = t6 | t5;
            t7 = sltu(a2, v1);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = sll(a3, 16);
            if (!cc) {
                // 0x00530b3c
                charge(ctx, 4);
                a2 = addu(a2, t1);
                t7 = sltu(a2, t1);
                t4 = addiu(t4, -1);
                if (t7 == 0) {
                    // 0x00530b4c
                    charge(ctx, 3);
                    t7 = sltu(a2, v1);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = sll(a3, 16);
                    if (!cc) {
                        // 0x00530b58
                        charge(ctx, 2);
                        t4 = addiu(t4, -1);
                        a2 = addu(a2, t1);
                        goto L_00530b60;
                    }
                    goto L_00530b64;
                }
            L_00530b60:
                charge(ctx, 1);
                t7 = sll(a3, 16);
            }
        L_00530b64:
            charge(ctx, 16);
            t6 = a1 & 0xFFFF;
            a3 = t7 | t4;
            a2 = subu(a2, v1);
            t7 = a3 & 0xFFFF;
            t4 = srl(a1, 16);
            mult(s2, t7, t6);
            mult1(t3, t7, t4);
            t5 = srl(a3, 16);
            t2 = a2;
            mult(t6, t5, t6);
            t7 = srl(s2, 16);
            t3 = addu(t3, t7);
            t3 = addu(t3, t6);
            t6 = sltu(t3, t6);
            mult1(t4, t5, t4);
            if (t6 != 0) {
                // 0x00530ba4
                charge(ctx, 2);
                t7 = 0x10000;
                t4 = addu(t4, t7);
            }
            // 0x00530bac
            charge(ctx, 7);
            t6 = srl(t3, 16);
            t5 = sll(t3, 16);
            a0 = addu(t4, t6);
            t7 = s2 & 0xFFFF;
            t6 = sltu(t2, a0);
            t3 = addu(t5, t7);
            if (t6 == 0) {
                // 0x00530bc8
                charge(ctx, 2);
                t7 = sltu(t8, t3);
                if (a0 == t2) {
                    // 0x00530bd0
                    charge(ctx, 2);
                    if (t7 != 0) {
                        goto L_00530bd8;
                    }
                }
                goto L_00530bf0;
            }
        L_00530bd8:
            charge(ctx, 6);
            t5 = subu(t3, a1);
            t6 = subu(a0, t1);
            t7 = sltu(t3, t5);
            a3 = addiu(a3, -1);
            a0 = subu(t6, t7);
            t3 = t5;
        L_00530bf0:
            charge(ctx, 2);
            s2 = 0;
            if (s1 == 0) {
                backedge(ctx);
            } else {
                // 0x00530bf8
                charge(ctx, 19);
                t5 = subu(t8, t3);
                t4 = subu(a2, a0);
                t6 = sltu(t8, t5);
                t2 = subu(t4, t6);
                t5 = srlv(t5, t9);
                t7 = sllv(t2, s0);
                t6 = si(-1);
                t7 = t7 | t5;
                t6 = dsll32(t6, 0);
                t7 = dsll32(t7, 0);
                t0 = t0 & t6;
                t7 = dsrl32(t7, 0);
                t6 = srlv(t2, t9);
                t0 = t0 | t7;
                t6 = dsll32(t6, 0);
                t0 = dsll32(t0, 0);
                t0 = dsrl32(t0, 0);
                t0 = t0 | t6;
                backedge(ctx);
            L_00530720:
                charge(ctx, 1);
                sd(t0, s1, 0);
            }
            // 0x00530724 (the shared epilogue, written out on this path)
            charge(ctx, 17);
            t6 = si(-1);
            ld(s0, sp, 0x0);
            t7 = dsll32(a3, 0);
            ld(s1, sp, 0x8);
            t6 = dsll32(t6, 0);
            t7 = dsrl32(t7, 0);
            v0 = v0 & t6;
            t5 = dsll32(s2, 0);
            v0 = v0 | t7;
            ld(s2, sp, 0x10);
            t5 = dsrl32(t5, 0);
            v0 = dsll32(v0, 0);
            t5 = dsll32(t5, 0);
            v0 = dsrl32(v0, 0);
            v0 = v0 | t5;
            sp = addiu(sp, 0x20);
            return;
        }
    L_00530a44:
        charge(ctx, 2);
        s2 = 0;
        if (s1 != 0) {
            // 0x00530a4c
            charge(ctx, 13);
            t6 = si(-1);
            t7 = dsll32(t8, 0);
            t6 = dsll32(t6, 0);
            t7 = dsrl32(t7, 0);
            t0 = t0 & t6;
            t5 = dsll32(t2, 0);
            t0 = t0 | t7;
            t5 = dsrl32(t5, 0);
            t0 = dsll32(t0, 0);
            t5 = dsll32(t5, 0);
            t0 = dsrl32(t0, 0);
            t0 = t0 | t5;
            backedge(ctx);
            goto L_00530720;
        }
        backedge(ctx);
    } else {
        // 0x005305c8
        charge(ctx, 3);
        t7 = sltu(t2, a1);
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = 0xFFFF;
        if (cc) {
            // 0x00530784
            charge(ctx, 2);
            t7 = sltu(t7, a1);
            if (a1 == 0) {
                // 0x0053078c
                charge(ctx, 4);
                t7 = 1;
                divu(t7, t1);
                if (a1 == 0) {
                    brk(ctx, 0x530798u, 0x7u);
                }
                // 0x0053079c
                charge(ctx, 3);
                mflo(a1);
                t7 = 0xFFFF;
                t7 = sltu(t7, a1);
            }
            // 0x005307a8
            charge(ctx, 2);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0xFF0000;
            if (cc) {
                // 0x005309a4
                charge(ctx, 7);
                t6 = 16;
                t7 = t7 | 0xFFFF;
                t5 = 24;
                t7 = sltu(t7, a1);
                t4 = t6;
                if (t7 != 0) t4 = t5;
                backedge(ctx);
            } else {
                // 0x005307b0
                charge(ctx, 4);
                t7 = 8;
                t6 = sltiu(a1, 256);
                t4 = t7;
                if (t6 != 0) t4 = 0;
            }
            // 0x005307c0
            charge(ctx, 10);
            t6 = 0x7C0000;
            t7 = srlv(a1, t4);
            t6 = addiu(t6, 904);  // &0x7C0388
            t3 = 32;
            t7 = addu(t7, t6);
            lbu(t5, t7, 0);
            t5 = addu(t5, t4);
            t9 = subu(t3, t5);
            s0 = subu(t3, t9);
            if (t9 != 0) {
                // 0x005308bc
                charge(ctx, 13);
                a1 = sllv(a1, t9);
                t1 = srl(a1, 16);
                t4 = srlv(t2, s0);
                divu(t4, t1);
                v1 = a1 & 0xFFFF;
                t6 = srlv(t8, s0);
                t7 = sllv(t2, t9);
                t2 = t7 | t6;
                a3 = t1;
                t6 = srl(t2, 16);
                t8 = sllv(t8, t9);
                if (t1 == 0) {
                    brk(ctx, 0x5308ECu, 0x7u);
                }
                // 0x005308f0
                charge(ctx, 9);
                mfhi(t5);
                mflo(t4);
                mflo(a0);
                t5 = sll(t5, 16);
                mult(t3, t4, v1);
                t6 = t5 | t6;
                t7 = sltu(t6, t3);
                a2 = v1;
                if (t7 != 0) {
                    // 0x00530914
                    charge(ctx, 4);
                    t6 = addu(t6, a1);
                    t7 = sltu(t6, a1);
                    a0 = addiu(t4, -1);
                    if (t7 != 0) {
                        goto L_00530938;
                    }
                    // 0x00530924
                    charge(ctx, 3);
                    t7 = sltu(t6, t3);
                    if (t7 != 0) {
                        // 0x00530930
                        charge(ctx, 2);
                        a0 = addiu(a0, -1);
                        t6 = addu(t6, a1);
                        goto L_00530938;
                    }
                    t6 = subu(t6, t3);
                    goto L_0053093c;
                }
            L_00530938:
                charge(ctx, 1);
                t6 = subu(t6, t3);
            L_0053093c:
                charge(ctx, 4);
                t5 = t2 & 0xFFFF;
                divu(t6, a3);
                if (a3 == 0) {
                    brk(ctx, 0x530948u, 0x7u);
                }
                // 0x0053094c
                charge(ctx, 9);
                mflo(t7);
                mfhi(t6);
                mflo(a3);
                t6 = sll(t6, 16);
                mult(t3, t7, a2);
                t4 = t6 | t5;
                t7 = sltu(t4, t3);
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = sll(a0, 16);
                if (!cc) {
                    // 0x00530970
                    charge(ctx, 4);
                    t4 = addu(t4, a1);
                    t7 = sltu(t4, a1);
                    a3 = addiu(a3, -1);
                    if (t7 == 0) {
                        // 0x00530980
                        charge(ctx, 3);
                        t7 = sltu(t4, t3);
                        cc = t7 == 0;  // the condition, before the delay slot changes it
                        t7 = sll(a0, 16);
                        if (!cc) {
                            // 0x0053098c
                            charge(ctx, 2);
                            a3 = addiu(a3, -1);
                            t4 = addu(t4, a1);
                            goto L_00530994;
                        }
                        goto L_00530998;
                    }
                L_00530994:
                    charge(ctx, 1);
                    t7 = sll(a0, 16);
                }
            L_00530998:
                charge(ctx, 3);
                t2 = subu(t4, t3);
                s2 = t7 | a3;
                backedge(ctx);
            } else {
                // 0x005307e8
                charge(ctx, 4);
                t2 = subu(t2, a1);
                s2 = 1;
                t1 = srl(a1, 16);
                v1 = a1 & 0xFFFF;
            }
            // 0x005307f8
            charge(ctx, 4);
            divu(t2, t1);
            t4 = srl(t8, 16);
            if (t1 == 0) {
                brk(ctx, 0x530804u, 0x7u);
            }
            // 0x00530808
            charge(ctx, 9);
            mfhi(t6);
            mflo(t5);
            mflo(a3);
            t6 = sll(t6, 16);
            mult(t3, t5, v1);
            t6 = t6 | t4;
            t7 = sltu(t6, t3);
            if (t7 == 0) {
                t6 = subu(t6, t3);
            } else {
                // 0x0053082c
                charge(ctx, 4);
                t6 = addu(t6, a1);
                t7 = sltu(t6, a1);
                a3 = addiu(t5, -1);
                if (t7 == 0) {
                    // 0x0053083c
                    charge(ctx, 3);
                    t7 = sltu(t6, t3);
                    if (t7 != 0) {
                        // 0x00530848
                        charge(ctx, 2);
                        a3 = addiu(a3, -1);
                        t6 = addu(t6, a1);
                        goto L_00530850;
                    }
                    t6 = subu(t6, t3);
                    goto L_00530854;
                }
            L_00530850:
                charge(ctx, 1);
                t6 = subu(t6, t3);
            }
        L_00530854:
            charge(ctx, 4);
            t5 = t8 & 0xFFFF;
            divu(t6, t1);
            if (t1 == 0) {
                brk(ctx, 0x530860u, 0x7u);
            }
            // 0x00530864
            charge(ctx, 9);
            mflo(t7);
            mfhi(t6);
            mflo(t2);
            t6 = sll(t6, 16);
            mult(t3, t7, v1);
            a0 = t6 | t5;
            t7 = sltu(a0, t3);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = sll(a3, 16);
            if (!cc) {
                // 0x00530888
                charge(ctx, 4);
                a0 = addu(a0, a1);
                t7 = sltu(a0, a1);
                t2 = addiu(t2, -1);
                if (t7 == 0) {
                    // 0x00530898
                    charge(ctx, 3);
                    t7 = sltu(a0, t3);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = sll(a3, 16);
                    if (!cc) {
                        // 0x005308a4
                        charge(ctx, 2);
                        a0 = addu(a0, a1);
                        t2 = addiu(t2, -1);
                        goto L_005308ac;
                    }
                    goto L_005308b0;
                }
            L_005308ac:
                charge(ctx, 1);
                t7 = sll(a3, 16);
            }
        L_005308b0:
            charge(ctx, 3);
            t8 = subu(a0, t3);
            a3 = t7 | t2;
            backedge(ctx);
        } else {
            // 0x005305d4
            charge(ctx, 3);
            t7 = sltu(t7, a1);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0xFF0000;
            if (cc) {
                // 0x00530768
                charge(ctx, 7);
                t6 = 16;
                t7 = t7 | 0xFFFF;
                t5 = 24;
                t7 = sltu(t7, a1);
                t4 = t6;
                if (t7 != 0) t4 = t5;
                backedge(ctx);
            } else {
                // 0x005305e0
                charge(ctx, 4);
                t7 = 8;
                t6 = sltiu(a1, 256);
                t4 = t7;
                if (t6 != 0) t4 = 0;
            }
            // 0x005305f0
            charge(ctx, 10);
            t6 = 0x7C0000;
            t7 = srlv(a1, t4);
            t6 = addiu(t6, 904);  // &0x7C0388
            t3 = 32;
            t7 = addu(t7, t6);
            lbu(t5, t7, 0);
            t5 = addu(t5, t4);
            t9 = subu(t3, t5);
            t7 = subu(t3, t9);
            if (t9 != 0) {
                // 0x00530618
                charge(ctx, 5);
                t6 = sllv(t2, t9);
                t7 = srlv(t8, t7);
                a1 = sllv(a1, t9);
                t2 = t6 | t7;
                t8 = sllv(t8, t9);
            }
            // 0x0053062c
            charge(ctx, 6);
            t3 = srl(a1, 16);
            t1 = a1 & 0xFFFF;
            divu(t2, t3);
            t5 = srl(t8, 16);
            if (t3 == 0) {
                brk(ctx, 0x530640u, 0x7u);
            }
            // 0x00530644
            charge(ctx, 9);
            mflo(t7);
            mfhi(t6);
            mflo(t4);
            t6 = sll(t6, 16);
            mult(t2, t7, t1);
            t6 = t6 | t5;
            t7 = sltu(t6, t2);
            if (t7 == 0) {
                t6 = subu(t6, t2);
            } else {
                // 0x00530668
                charge(ctx, 4);
                t6 = addu(t6, a1);
                t7 = sltu(t6, a1);
                t4 = addiu(t4, -1);
                if (t7 == 0) {
                    // 0x00530678
                    charge(ctx, 3);
                    t7 = sltu(t6, t2);
                    if (t7 != 0) {
                        // 0x00530684
                        charge(ctx, 2);
                        t4 = addiu(t4, -1);
                        t6 = addu(t6, a1);
                        goto L_0053068c;
                    }
                    t6 = subu(t6, t2);
                    goto L_00530690;
                }
            L_0053068c:
                charge(ctx, 1);
                t6 = subu(t6, t2);
            }
        L_00530690:
            charge(ctx, 4);
            t5 = t8 & 0xFFFF;
            divu(t6, t3);
            if (t3 == 0) {
                brk(ctx, 0x53069Cu, 0x7u);
            }
            // 0x005306a0
            charge(ctx, 9);
            mflo(t7);
            mfhi(t6);
            mflo(t3);
            t6 = sll(t6, 16);
            mult(t2, t7, t1);
            a0 = t6 | t5;
            t7 = sltu(a0, t2);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = sll(t4, 16);
            if (!cc) {
                // 0x005306c4
                charge(ctx, 4);
                a0 = addu(a0, a1);
                t7 = sltu(a0, a1);
                t3 = addiu(t3, -1);
                if (t7 == 0) {
                    // 0x005306d4
                    charge(ctx, 3);
                    t7 = sltu(a0, t2);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = sll(t4, 16);
                    if (!cc) {
                        // 0x005306e0
                        charge(ctx, 2);
                        a0 = addu(a0, a1);
                        t3 = addiu(t3, -1);
                        goto L_005306e8;
                    }
                    goto L_005306ec;
                }
            L_005306e8:
                charge(ctx, 1);
                t7 = sll(t4, 16);
            }
        L_005306ec:
            charge(ctx, 3);
            t8 = subu(a0, t2);
            a3 = t7 | t3;
            s2 = 0;
        }
        // 0x005306f8
        charge(ctx, 2);
        t7 = srlv(t8, t9);
        if (s1 != 0) {
            // 0x00530700
            charge(ctx, 8);
            t6 = si(-1);
            t7 = dsll32(t7, 0);
            t6 = dsll32(t6, 0);
            t0 = t0 & t6;
            t7 = dsrl32(t7, 0);
            t0 = t0 | t7;
            t0 = dsll32(t0, 0);
            t0 = dsrl32(t0, 0);
            goto L_00530720;
        }
    }
    // 0x00530724 (the shared epilogue, written out on this path)
    charge(ctx, 17);
    t6 = si(-1);
    ld(s0, sp, 0x0);
    t7 = dsll32(a3, 0);
    ld(s1, sp, 0x8);
    t6 = dsll32(t6, 0);
    t7 = dsrl32(t7, 0);
    v0 = v0 & t6;
    t5 = dsll32(s2, 0);
    v0 = v0 | t7;
    ld(s2, sp, 0x10);
    t5 = dsrl32(t5, 0);
    v0 = dsll32(v0, 0);
    t5 = dsll32(t5, 0);
    v0 = dsrl32(v0, 0);
    v0 = v0 | t5;
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
