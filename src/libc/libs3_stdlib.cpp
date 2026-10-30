// Slice libs3: qsort and newlib's heap internals (_malloc_r, its arena growth, _realloc_r).
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions, the pseudocode reference and
// the public C standard / MPEG standards only (ADR-0010: no newlib, GPL or CRI source was opened).
// Pair tests: tests/game/test_libs3.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs3.h"

namespace p3fes::recomp_gen {
void fn___malloc_lock_005214c8(p3fes::EEContext&);
void fn___malloc_unlock_00521520(p3fes::EEContext&);
void fn__free_r_0051fbb0(p3fes::EEContext&);
void fn__malloc_r_005209c0(p3fes::EEContext&);
void fn__realloc_r_00522fc0(p3fes::EEContext&);
void fn__sbrk_r_00523930(p3fes::EEContext&);
void fn_malloc_extend_top_00520768(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_qsort_005225f8(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x00520768 malloc_extend_top -- 596 bytes; frame 0x50: s6 sp+0x30, s3 sp+0x18, s1 sp+0x8, s2 sp+0x10, s4 sp+0x20, s5 sp+0x28, s7 sp+0x38, s0 sp+0x0, ra sp+0x40
// newlib's malloc_extend_top(reent, size): grows the top chunk -- asks _sbrk_r for the size plus the top pad and page
// rounding, accepts memory contiguous with the old top (or re-bases the top chunk on a new region, fixing the alignment
// with a second sbrk and freeing the old top through _free_r), updates the sbrk total and its maximum.
void malloc_extend_top(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00520768
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    t7 = 0x780000;
    sd(s6, sp, 0x30);
    a1 = dsll32(a1, 0);
    sd(s3, sp, 0x18);
    a1 = dsrl32(a1, 0);
    sd(s1, sp, 0x8);
    s6 = addiu(t7, 12096);  // &0x782F40
    sd(s2, sp, 0x10);
    t7 = 0x780000;
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(s7, sp, 0x38);
    s4 = si(-1);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x40);
    s7 = a0;
    lw(s3, s6, 8);  // 0x782F48
    ld(t6, t7, 13136);  // 0x783350
    lw(t5, s3, 4);
    t7 = si(-4);
    a1 = a1 + t6;
    s5 = t5 & t7;
    a1 = daddiu(a1, 16);
    t7 = 0x780000;
    s2 = dsll32(a1, 0);
    lw(t6, t7, 13144);  // 0x783358
    s2 = dsra32(s2, 0);
    s1 = addu(s3, s5);
    if (t6 != s4) {
        // 0x005207e0
        charge(ctx, 7);
        t7 = dsll32(s2, 0);
        t6 = si(-4096);
        t7 = dsrl32(t7, 0);
        t7 = daddiu(t7, 4095);
        t7 = t7 & t6;
        s2 = dsll32(t7, 0);
        s2 = dsra32(s2, 0);
    }
    // 0x005207fc
    charge(ctx, 4);
    a1 = s2;
    jal(ctx, 0x5207FCu, gen::fn__sbrk_r_00523930);
    s0 = v0;
    if (v0 != s4) {
        // 0x0052080c
        charge(ctx, 3);
        t7 = sltu(v0, s1);
        t6 = 0x780000;
        if (t7 != 0) {
            // 0x00520818
            charge(ctx, 2);
            if (s3 == s6) {
                // 0x00520820
                charge(ctx, 1);
                t6 = 0x780000;
                goto L_00520824;
            }
            ld(s0, sp, 0x0);
            // 0x00520884 (the shared epilogue, written out on this path)
            charge(ctx, 10);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(s4, sp, 0x20);
            ld(s5, sp, 0x28);
            ld(s6, sp, 0x30);
            ld(s7, sp, 0x38);
            ld(ra, sp, 0x40);
            sp = addiu(sp, 0x50);
            return;
        }
    L_00520824:
        charge(ctx, 4);
        lw(t7, t6, 13168);
        t7 = addu(t7, s2);
        sw(t7, t6, 13168);
        if (s0 == s1) {
            // 0x00520834
            charge(ctx, 3);
            t7 = s0 & 0xFFF;
            t5 = 0x780000;
            if (t7 != 0) {
                goto L_005208b0;
            }
            // 0x00520840
            charge(ctx, 4);
            v0 = addu(s2, s5);
            lw(t6, s6, 8);
            t7 = v0 | 0x1;
            sw(t7, t6, 4);
            goto L_00520850;
        }
        // 0x005208ac
        charge(ctx, 1);
        t5 = 0x780000;
    L_005208b0:
        charge(ctx, 4);
        t7 = si(-1);
        lw(t6, t5, 13144);
        if (t6 != t7) {
            t5 = 0x780000;
            // 0x005209a8
            charge(ctx, 5);
            t6 = subu(s0, s1);
            lw(t7, t5, 13168);
            t7 = addu(t7, t6);
            sw(t7, t5, 13168);
            backedge(ctx);
        } else {
            // 0x005208c0
            charge(ctx, 1);
            sw(s0, t5, 13144);
        }
        // 0x005208c4
        charge(ctx, 4);
        t7 = addiu(s0, 8);
        a1 = t7 & 0xF;
        t7 = 16;
        if (a1 == 0) {
            // 0x005209a0
            charge(ctx, 2);
            s1 = 0;
            backedge(ctx);
        } else {
            // 0x005208d4
            charge(ctx, 2);
            s1 = subu(t7, a1);
            s0 = addu(s0, s1);
        }
        // 0x005208dc
        charge(ctx, 13);
        t7 = addu(s0, s2);
        t6 = 4096;
        t7 = t7 & 0xFFF;
        a0 = s7;
        t6 = t6 - t7;
        t6 = dsll32(t6, 0);
        t6 = dsra32(t6, 0);
        s1 = addu(s1, t6);
        a1 = s1;
        jal(ctx, 0x5208FCu, gen::fn__sbrk_r_00523930);
        t7 = si(-1);
        t5 = 0x780000;
        if (v0 == t7) {
            // 0x00520910
            charge(ctx, 2);
            s1 = 0;
            v0 = s0;
        }
        // 0x00520918
        charge(ctx, 11);
        t7 = subu(v0, s0);
        lw(t6, t5, 13168);
        v0 = addu(t7, s1);
        t7 = 0x780000;
        t4 = v0 | 0x1;
        t6 = addu(t6, s1);
        t7 = addiu(t7, 12096);  // &0x782F40
        sw(t6, t5, 13168);
        sw(s0, t7, 8);  // 0x782F48
        sw(t4, s0, 4);
        if (s3 == t7) {
            backedge(ctx);
        L_00520850:
            charge(ctx, 1);
            t2 = 0x780000;
        L_00520854:
            charge(ctx, 11);
            t1 = 0x780000;
            t7 = 0x780000;
            ld(t4, t2, 13152);
            lw(t6, t7, 13168);  // 0x783370
            ld(t5, t1, 13160);  // 0x783368
            t7 = sltu(t4, t6);
            t3 = sltu(t5, t6);
            if (t7 != 0) t4 = t6;
            if (t3 != 0) t5 = t6;
            sd(t4, t2, 13152);
            sd(t5, t1, 13160);  // 0x783368
        } else {
            // 0x00520944
            charge(ctx, 3);
            t7 = sltiu(s5, 16);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = 1;
            if (cc) {
                // 0x00520958
                charge(ctx, 13);
                lw(t6, s3, 4);
                t5 = addiu(s5, -12);
                t7 = si(-16);
                t4 = 5;
                s5 = t5 & t7;
                t6 = t6 & 0x1;
                t6 = t6 | s5;
                t7 = addu(s3, s5);
                sw(t6, s3, 4);
                t5 = sltiu(s5, 16);
                sw(t4, t7, 8);
                sw(t4, t7, 4);
                if (t5 != 0) {
                    backedge(ctx);
                    goto L_00520850;
                }
                // 0x0052098c
                charge(ctx, 5);
                a1 = addiu(s3, 8);
                a0 = s7;
                jal(ctx, 0x520990u, gen::fn__free_r_0051fbb0);
                t2 = 0x780000;
                backedge(ctx);
                goto L_00520854;
            }
            // 0x00520950
            charge(ctx, 2);
            sw(t7, s0, 4);
            backedge(ctx);
        }
    }
    // 0x00520880
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x00520884 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x005209C0 _malloc_r -- 1768 bytes; frame 0x30: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// newlib's malloc core _malloc_r(reent, size): rounds the request up ((size + 19) & ~15, at least 16), then under
// __malloc_lock (interrupts off) takes an exact-size small bin (requests below 504 bytes; the bin array at 0x782F40),
// the last remainder, sorts the unsorted chunks into their bins, scans the bin map for the next fitting chunk
// (splitting off the rest as the new remainder) or carves the top chunk, growing it through malloc_extend_top. Returns
// the user pointer, or 0.
void _malloc_r(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005209c0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a1 = addiu(a1, 19);  // the chunk size: (size + 19) & ~15, at least 16
    sd(s2, sp, 0x10);
    t7 = sltiu(a1, 31);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    s2 = a0;
    if (t7 != 0) {
        // 0x005210a0
        charge(ctx, 2);
        s1 = 16;
        backedge(ctx);
    } else {
        // 0x005209ec
        charge(ctx, 2);
        t7 = si(-16);
        s1 = a1 & t7;
    }
    // 0x005209f4
    charge(ctx, 5);
    a0 = s2;
    jal(ctx, 0x5209F4u, gen::fn___malloc_lock_005214c8);
    t7 = sltiu(s1, 504);
    s4 = 0x780000;
    if (t7 != 0) {
        // 0x00520a08
        charge(ctx, 5);
        t7 = addiu(s4, 12096);
        t4 = addu(s1, t7);
        lw(s0, t4, 12);
        t0 = srl(s1, 3);
        if (s0 == t4) {
            // 0x00520a78
            charge(ctx, 1);
            t0 = addiu(t0, 2);
            goto L_00520a7c;
        }
        // 0x00520a1c
        charge(ctx, 10);
        lw(t6, s0, 4);
        t7 = si(-4);
        lw(a3, s0, 12);
        a0 = s2;
        t2 = t6 & t7;
        lw(t1, s0, 8);
        t6 = addu(s0, t2);
        lw(t7, t6, 4);
        sw(t1, a3, 8);
        sw(a3, t1, 12);
        goto L_00520a44;
    }
    // 0x00520fa0
    charge(ctx, 3);
    t6 = srl(s1, 9);
    t0 = srl(s1, 3);
    if (t6 != 0) {
        // 0x00520fac
        charge(ctx, 3);
        t7 = sltiu(t6, 5);
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = srl(s1, 6);
        if (cc) {
            // 0x00521050
            charge(ctx, 3);
            t7 = sltiu(t6, 21);
            t0 = addiu(t6, 91);
            if (t7 != 0) {
                backedge(ctx);
            } else {
                // 0x0052105c
                charge(ctx, 3);
                t7 = sltiu(t6, 85);
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = srl(s1, 12);
                if (cc) {
                    // 0x00521070
                    charge(ctx, 3);
                    t7 = sltiu(t6, 341);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = srl(s1, 15);
                    if (cc) {
                        // 0x00521084
                        charge(ctx, 3);
                        t7 = sltiu(t6, 1365);
                        cc = t7 == 0;  // the condition, before the delay slot changes it
                        t7 = srl(s1, 18);
                        if (cc) {
                            // 0x00521098
                            charge(ctx, 2);
                            t0 = 126;
                            backedge(ctx);
                        } else {
                            // 0x00521090
                            charge(ctx, 2);
                            t0 = addiu(t7, 124);
                            backedge(ctx);
                        }
                    } else {
                        // 0x0052107c
                        charge(ctx, 2);
                        t0 = addiu(t7, 119);
                        backedge(ctx);
                    }
                } else {
                    // 0x00521068
                    charge(ctx, 2);
                    t0 = addiu(t7, 110);
                    backedge(ctx);
                }
            }
        } else {
            // 0x00520fb8
            charge(ctx, 1);
            t0 = addiu(t7, 56);
        }
    }
    // 0x00520fbc
    charge(ctx, 7);
    s4 = 0x780000;
    t6 = sll(t0, 3);
    t7 = addiu(s4, 12096);  // &0x782F40
    t5 = addu(t6, t7);
    lw(s0, t5, 12);
    if (s0 != t5) {
        // 0x00520fd8
        charge(ctx, 2);
        t4 = si(-4);
        lw(t7, s0, 4);
        for (;;) {
            // 0x00520fe0
            charge(ctx, 9);
            t2 = t7 & t4;
            t7 = subu(t2, s1);
            t6 = subu(s1, t2);
            t3 = dsll32(t7, 0);
            t6 = dsll32(t6, 0);
            t6 = dsrl32(t6, 0);
            t7 = sltu(t2, s1);
            t3 = dsrl32(t3, 0);
            if (t7 != 0) {
                // 0x00521004
                charge(ctx, 1);
                t3 = 0 - t6;
            }
            // 0x00521008
            charge(ctx, 3);
            t7 = slti(t3, 16);
            if (t7 == 0) {
                t0 = addiu(t0, -1);
                break;
            }
            // 0x00521014
            charge(ctx, 2);
            t6 = addu(s0, t2);
            if (i64(t3) >= 0) {
                goto L_00521030;
            }
            // 0x0052101c
            charge(ctx, 3);
            lw(s0, s0, 12);
            if (s0 == t5) {
                break;
            }
            lw(t7, s0, 4);
            backedge(ctx);
        }
        // 0x00521028
        charge(ctx, 2);
        t0 = addiu(t0, 1);
        backedge(ctx);
        goto L_00520a7c;
    }
    t0 = addiu(t0, 1);
    backedge(ctx);
L_00520a7c:
    charge(ctx, 5);
    t7 = 0x780000;
    t7 = addiu(t7, 12104);  // "@/x"
    lw(s0, t7, 8);  // 0x782F50
    t6 = si(-4);
    if (s0 != t7) {
        // 0x00520a90
        charge(ctx, 5);
        lw(t7, s0, 4);
        t2 = t7 & t6;
        t5 = sltu(t2, s1);
        t7 = subu(s1, t2);
        if (t5 == 0) {
            // 0x00520f90
            charge(ctx, 4);
            t7 = subu(t2, s1);
            t3 = dsll32(t7, 0);
            t3 = dsrl32(t3, 0);
            backedge(ctx);
        } else {
            // 0x00520aa4
            charge(ctx, 3);
            t7 = dsll32(t7, 0);
            t7 = dsrl32(t7, 0);
            t3 = 0 - t7;
        }
        // 0x00520ab0
        charge(ctx, 3);
        t7 = slti(t3, 16);
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = 0x780000;
        if (!cc) {
            // 0x00520abc
            charge(ctx, 17);
            t7 = s1 | 0x1;
            t6 = 0x780000;
            sw(t7, s0, 4);
            a1 = addu(s0, s1);
            t6 = addiu(t6, 12104);  // "@/x"
            t4 = dsll32(t3, 0);
            t7 = t3 | 0x1;
            sw(a1, t6, 8);  // 0x782F50
            t4 = dsra32(t4, 0);
            sw(a1, t6, 12);  // 0x782F54
            t7 = dsll32(t7, 0);
            sw(t6, a1, 8);
            t7 = dsra32(t7, 0);
            t5 = addu(a1, t4);
            sw(t7, a1, 4);
            a0 = s2;
            sw(t4, t5, 0);
        L_00520b00:
            charge(ctx, 2);
            sw(t6, a1, 12);
            backedge(ctx);
            goto L_00520a4c;
        }
        // 0x00520b08
        charge(ctx, 4);
        t5 = addiu(t7, 12104);
        sw(t5, t5, 12);
        sw(t5, t5, 8);
        if (i64(t3) < 0) {
            // 0x00520b28
            charge(ctx, 3);
            t7 = sltiu(t2, 512);
            t4 = srl(t2, 3);
            if (t7 == 0) {
                // 0x00520e98
                charge(ctx, 3);
                t6 = srl(t2, 9);
                t7 = sltiu(t6, 5);
                if (t6 != 0) {
                    // 0x00520ea4
                    charge(ctx, 2);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = srl(t2, 6);
                    if (cc) {
                        // 0x00520f40
                        charge(ctx, 3);
                        t7 = sltiu(t6, 21);
                        t4 = addiu(t6, 91);
                        if (t7 != 0) {
                            backedge(ctx);
                        } else {
                            // 0x00520f4c
                            charge(ctx, 3);
                            t7 = sltiu(t6, 85);
                            cc = t7 == 0;  // the condition, before the delay slot changes it
                            t7 = srl(t2, 12);
                            if (cc) {
                                // 0x00520f60
                                charge(ctx, 3);
                                t7 = sltiu(t6, 341);
                                cc = t7 == 0;  // the condition, before the delay slot changes it
                                t7 = srl(t2, 15);
                                if (cc) {
                                    // 0x00520f74
                                    charge(ctx, 3);
                                    t7 = sltiu(t6, 1365);
                                    cc = t7 == 0;  // the condition, before the delay slot changes it
                                    t7 = srl(t2, 18);
                                    if (cc) {
                                        // 0x00520f88
                                        charge(ctx, 2);
                                        t4 = 126;
                                        backedge(ctx);
                                    } else {
                                        // 0x00520f80
                                        charge(ctx, 2);
                                        t4 = addiu(t7, 124);
                                        backedge(ctx);
                                    }
                                } else {
                                    // 0x00520f6c
                                    charge(ctx, 2);
                                    t4 = addiu(t7, 119);
                                    backedge(ctx);
                                }
                            } else {
                                // 0x00520f58
                                charge(ctx, 2);
                                t4 = addiu(t7, 110);
                                backedge(ctx);
                            }
                        }
                    } else {
                        // 0x00520eac
                        charge(ctx, 1);
                        t4 = addiu(t7, 56);
                    }
                }
                // 0x00520eb0
                charge(ctx, 6);
                t7 = sll(t4, 3);
                t3 = addiu(s4, 12096);
                a3 = addu(t7, t3);
                lw(t1, a3, 8);
                if (t1 != a3) {
                    lw(t7, t1, 4);
                    // 0x00520f04
                    charge(ctx, 5);
                    t6 = si(-4);
                    t7 = t7 & t6;
                    t7 = sltu(t2, t7);
                    if (t7 == 0) {
                        lw(a3, t1, 12);
                        backedge(ctx);
                    } else {
                        // 0x00520f18
                        charge(ctx, 1);
                        lw(t1, t1, 8);
                        for (;;) {
                            // 0x00520f1c
                            charge(ctx, 2);
                            if (t1 != a3) {
                                // 0x00520f24
                                charge(ctx, 5);
                                lw(t7, t1, 4);
                                t7 = t7 & t6;
                                t7 = sltu(t2, t7);
                                if (t7 == 0) {
                                    goto L_00520f38_76;
                                }
                                lw(t1, t1, 8);
                                backedge(ctx);
                                continue;
                            }
                            lw(a3, t1, 12);
                            backedge(ctx);
                            break;
                        }
                    }
                } else {
                    // 0x00520ec8
                    charge(ctx, 11);
                    t6 = addiu(t4, 3);
                    t7 = slti(t4, 0);
                    if (t7 != 0) t4 = t6;
                    t5 = sra(t4, 2);
                    lw(t6, t3, 4);
                    t7 = 1;
                    t7 = dsllv(t7, t5);
                    t7 = dsll32(t7, 0);
                    t7 = dsra32(t7, 0);
                    t6 = t6 | t7;
                    sw(t6, t3, 4);
                }
            L_00520ef4:
                charge(ctx, 4);
                sw(a3, s0, 12);
                sw(t1, s0, 8);
                sw(s0, t1, 12);
                backedge(ctx);
            } else {
                // 0x00520b34
                charge(ctx, 15);
                t5 = addiu(t5, -8);
                t7 = sll(t4, 3);
                lw(t6, t5, 4);
                a3 = addu(t7, t5);
                t4 = srl(t4, 2);
                t7 = 1;
                lw(t1, a3, 8);
                t7 = dsllv(t7, t4);
                sw(a3, s0, 12);
                t7 = dsll32(t7, 0);
                sw(t1, s0, 8);
                t7 = dsra32(t7, 0);
                sw(s0, t1, 12);
                t6 = t6 | t7;
                sw(t6, t5, 4);
            }
            // 0x00520b70
            charge(ctx, 1);
            sw(s0, a3, 8);
            goto L_00520b74;
        }
        // 0x00520b18
        charge(ctx, 4);
        t6 = addu(s0, t2);
        a0 = s2;
        lw(t7, t6, 4);
        backedge(ctx);
    L_00520a44:
        charge(ctx, 2);
        t7 = t7 | 0x1;
        sw(t7, t6, 4);
    L_00520a4c:
        charge(ctx, 3);
        jal(ctx, 0x520A4Cu, gen::fn___malloc_unlock_00521520);
        v0 = addiu(s0, 8);
        // 0x00520a58 (the shared epilogue, written out on this path)
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
L_00520b74:
    charge(ctx, 11);
    t7 = slti(t0, 0);
    t5 = addiu(t0, 3);
    if (t7 == 0) t5 = t0;
    t6 = addiu(s4, 12096);
    t5 = sra(t5, 2);
    lwu(t4, t6, 4);
    t7 = 1;
    t1 = dsllv(t7, t5);
    t6 = sltu(t4, t1);
    t7 = addiu(s4, 12096);
    if (t6 == 0) {
        // 0x00520ba0
        charge(ctx, 3);
        t7 = t1 & t4;
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = 0x780000;
        if (!cc) {
            // 0x00520bac
            charge(ctx, 6);
            t7 = si(-4);
            t1 = dsll(t1, 1);
            t7 = t0 & t7;
            t6 = t1 & t4;
            t0 = addiu(t7, 4);
            if (t6 == 0) {
                // 0x00520bc4
                charge(ctx, 1);
                t6 = t4;
                for (;;) {
                    // 0x00520bc8
                    charge(ctx, 7);
                    t1 = dsll(t1, 1);
                    t7 = t1 & t6;
                    t0 = addiu(t0, 4);
                    if (t7 != 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00520be4
            charge(ctx, 1);
            t7 = 0x780000;
        }
        // 0x00520be8
        charge(ctx, 5);
        a1 = addiu(t7, 12096);
        v1 = t7;
        a0 = a1;
        v0 = a1;
        t7 = sll(t0, 3);
        for (;;) {
            // 0x00520bfc
            charge(ctx, 4);
            a2 = t0;
            t4 = addu(t7, a1);
            t5 = t4;
            lw(s0, t5, 12);
            for (;;) {
                // 0x00520c0c
                charge(ctx, 2);
                t7 = slti(t0, 63);
                if (s0 != t5) {
                    // 0x00520c14
                    charge(ctx, 2);
                    a3 = si(-4);
                    lw(t7, s0, 4);
                    for (;;) {
                        // 0x00520c1c
                        charge(ctx, 9);
                        t2 = t7 & a3;
                        t7 = subu(t2, s1);
                        t6 = subu(s1, t2);
                        t3 = dsll32(t7, 0);
                        t6 = dsll32(t6, 0);
                        t6 = dsrl32(t6, 0);
                        t7 = sltu(t2, s1);
                        t3 = dsrl32(t3, 0);
                        if (t7 != 0) {
                            // 0x00520c40
                            charge(ctx, 1);
                            t3 = 0 - t6;
                        }
                        // 0x00520c44
                        charge(ctx, 3);
                        t7 = slti(t3, 16);
                        if (t7 == 0) {
                            lw(t1, s0, 8);
                            goto L_00520e44;
                        }
                        // 0x00520c50
                        charge(ctx, 2);
                        t6 = addu(s0, t2);
                        if (i64(t3) >= 0) {
                            goto L_00520e20;
                        }
                        // 0x00520c58
                        charge(ctx, 3);
                        lw(s0, s0, 12);
                        if (s0 == t5) {
                            break;
                        }
                        lw(t7, s0, 4);
                        backedge(ctx);
                    }
                    // 0x00520c64
                    charge(ctx, 1);
                    t7 = slti(t0, 63);
                }
                // 0x00520c68
                charge(ctx, 2);
                t5 = addiu(t5, 8);
                if (t7 != 0) {
                    // 0x00520c70
                    charge(ctx, 2);
                    t5 = addiu(t5, 8);
                    t0 = addiu(t0, 1);
                }
                // 0x00520c78
                charge(ctx, 4);
                t0 = addiu(t0, 1);
                t7 = t0 & 0x3;
                if (t7 == 0) {
                    break;
                }
                lw(s0, t5, 12);
                backedge(ctx);
            }
            // 0x00520c88
            charge(ctx, 5);
            t7 = dsll32(t1, 0);
            t5 = addiu(v1, 12096);
            t7 = dsra32(t7, 0);
            t6 = nor(0, t7);
            t7 = a2 & 0x3;
            for (;;) {
                // 0x00520c9c
                charge(ctx, 2);
                a2 = addiu(a2, -1);
                if (t7 == 0) {
                    goto L_00520ca4_41;
                }
                // 0x00520e08
                charge(ctx, 4);
                t4 = addiu(t4, -8);
                lw(t7, t4, 8);
                cc = t7 == t4;  // the condition, before the delay slot changes it
                t7 = a2 & 0x3;
                if (!cc) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00520e18
            charge(ctx, 2);
            lwu(t6, a0, 4);
            backedge(ctx);
        L_00520cb4:
            charge(ctx, 4);
            t1 = dsll(t1, 1);
            t7 = sltu(t6, t1);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = addiu(s4, 12096);
            if (cc) {
                goto L_00520d04;
            }
            // 0x00520cc4
            charge(ctx, 2);
            t7 = t1 & t6;
            if (t1 == 0) {
                goto L_00520d00;
            }
            // 0x00520ccc
            charge(ctx, 2);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = sll(t0, 3);
            if (cc) {
                backedge(ctx);
            } else {
                // 0x00520cd4
                charge(ctx, 1);
                lwu(t6, v0, 4);
                for (;;) {
                    // 0x00520cd8
                    charge(ctx, 7);
                    t1 = dsll(t1, 1);
                    t7 = t1 & t6;
                    t0 = addiu(t0, 4);
                    if (t7 != 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00520cf4
                charge(ctx, 2);
                t7 = sll(t0, 3);
                backedge(ctx);
            }
        }
    L_00520e20:
        charge(ctx, 7);
        lw(a3, s0, 12);
        lw(t7, t6, 4);
        a0 = s2;
        lw(t1, s0, 8);
        t7 = t7 | 0x1;
        sw(t7, t6, 4);
        sw(t1, a3, 8);
    L_00520e3c:
        charge(ctx, 2);
        sw(a3, t1, 12);
        backedge(ctx);
        goto L_00520a4c;
    }
L_00520d04:
    charge(ctx, 7);
    lw(t6, t7, 8);
    lw(t5, t6, 4);
    t7 = si(-4);
    t5 = t5 & t7;
    t6 = sltu(t5, s1);
    t7 = subu(s1, t5);
    if (t6 == 0) {
        // 0x00520df8
        charge(ctx, 4);
        t7 = subu(t5, s1);
        t3 = dsll32(t7, 0);
        t3 = dsrl32(t3, 0);
        backedge(ctx);
    } else {
        // 0x00520d20
        charge(ctx, 3);
        t7 = dsll32(t7, 0);
        t7 = dsrl32(t7, 0);
        t3 = 0 - t7;
    }
    // 0x00520d2c
    charge(ctx, 8);
    s0 = addiu(s4, 12096);
    s3 = si(-4);
    lw(t6, s0, 8);
    lw(t7, t6, 4);
    t7 = t7 & s3;
    t7 = sltu(t7, s1);
    a0 = s2;
    if (t7 == 0) {
        // 0x00520d4c
        charge(ctx, 3);
        t7 = slti(t3, 16);
        t4 = addiu(s4, 12096);
        if (t7 != 0) {
            goto L_00520d58;
        }
    L_00520dbc:
        charge(ctx, 11);
        t5 = s1 | 0x1;
        lw(s0, t4, 8);
        t6 = t3 | 0x1;
        t6 = dsll32(t6, 0);
        a0 = s2;
        sw(t5, s0, 4);
        t7 = addu(s0, s1);
        t6 = dsra32(t6, 0);
        sw(t7, t4, 8);
        sw(t6, t7, 4);
        backedge(ctx);
        goto L_00520a4c;
    }
L_00520d58:
    charge(ctx, 8);
    a1 = s1;
    jal(ctx, 0x520D58u, gen::fn_malloc_extend_top_00520768);
    lw(t7, s0, 8);
    lw(t6, t7, 4);
    t6 = t6 & s3;
    t7 = sltu(t6, s1);
    cc = t7 == 0;  // the condition, before the delay slot changes it
    t7 = subu(s1, t6);
    if (cc) {
        // 0x00520de8
        charge(ctx, 4);
        t7 = subu(t6, s1);
        t3 = dsll32(t7, 0);
        t3 = dsrl32(t3, 0);
        backedge(ctx);
    } else {
        // 0x00520d78
        charge(ctx, 3);
        t7 = dsll32(t7, 0);
        t7 = dsrl32(t7, 0);
        t3 = 0 - t7;
    }
    // 0x00520d84
    charge(ctx, 8);
    t6 = addiu(s4, 12096);
    lw(t5, t6, 8);
    lw(t7, t5, 4);
    t6 = si(-4);
    t7 = t7 & t6;
    t7 = sltu(t7, s1);
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = slti(t3, 16);
    if (!cc) {
        // 0x00520da4
        charge(ctx, 2);
        t4 = addiu(s4, 12096);
        if (t7 == 0) {
            goto L_00520dbc;
        }
        goto L_00520dac;
    }
L_00520dac:
    charge(ctx, 4);
    a0 = s2;
    jal(ctx, 0x520DACu, gen::fn___malloc_unlock_00521520);
    v0 = 0;
    backedge(ctx);
    // 0x00520a58 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    return;
L_00520ca4_41:
    charge(ctx, 4);
    lw(t7, t5, 4);
    t7 = t7 & t6;
    sw(t7, t5, 4);
    lwu(t6, a0, 4);
    goto L_00520cb4;
L_00520d00:
    charge(ctx, 1);
    t7 = addiu(s4, 12096);
    goto L_00520d04;
L_00520e44:
    charge(ctx, 21);
    t5 = s1 | 0x1;
    lw(a3, s0, 12);
    t6 = 0x780000;
    a1 = addu(s0, s1);
    sw(t5, s0, 4);
    sw(t1, a3, 8);
    t6 = addiu(t6, 12104);  // "@/x"
    t4 = dsll32(t3, 0);
    sw(a3, t1, 12);
    t7 = t3 | 0x1;
    sw(a1, t6, 8);  // 0x782F50
    t4 = dsra32(t4, 0);
    sw(a1, t6, 12);  // 0x782F54
    t7 = dsll32(t7, 0);
    sw(t6, a1, 8);
    t7 = dsra32(t7, 0);
    t5 = addu(a1, t4);
    sw(t4, t5, 0);
    a0 = s2;
    sw(t7, a1, 4);
    backedge(ctx);
    goto L_00520b00;
L_00520f38_76:
    charge(ctx, 2);
    lw(a3, t1, 12);
    backedge(ctx);
    goto L_00520ef4;
L_00521030:
    charge(ctx, 8);
    lw(a3, s0, 12);
    lw(t7, t6, 4);
    a0 = s2;
    lw(t1, s0, 8);
    t7 = t7 | 0x1;
    sw(t1, a3, 8);
    sw(t7, t6, 4);
    backedge(ctx);
    goto L_00520e3c;
}

// 0x005225F8 qsort -- 2364 bytes; frame 0xB0: s3 sp+0x78, s6 sp+0x90, s7 sp+0x98, s0 sp+0x60, s1 sp+0x68, s2 sp+0x70, s4 sp+0x80, s5 sp+0x88, fp sp+0xA0, ra sp+0xA8
// qsort(base, n, size, cmp): the classic engineered quicksort -- insertion sort below 7 elements, the median of three
// (of nine above 40) as the pivot, a three-way partition that gathers the elements equal to the pivot at both ends and
// swaps them to the middle, recursion on the smaller side and a loop on the larger; elements are swapped as 64-bit
// doublewords when base and size are multiples of 8 (a single doubleword when size == 8) and byte by byte otherwise
// (long is 64-bit in this build). cmp(a, b) is called through jalr with $ra and the frame of the original.
void qsort(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005225f8
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(s3, sp, 0x78);
    sd(s6, sp, 0x90);
    sd(s7, sp, 0x98);
    s3 = a2;
    sd(s0, sp, 0x60);
    s6 = a0;
    sd(s1, sp, 0x68);
    s7 = a3;
    sd(s2, sp, 0x70);
    sd(s4, sp, 0x80);
    sd(s5, sp, 0x88);
    sd(fp, sp, 0xA0);
    sd(ra, sp, 0xA8);
    sw(a1, sp, 0x0);
    for (;;) {
        // 0x00522634
        charge(ctx, 3);
        t7 = s6 & 0x7;
        fp = 0x2;  // the swap type: 2 bytewise, 1 by doublewords (base and size multiples of 8), 0 size == 8
        if (t7 == 0) {
            // 0x00522640
            charge(ctx, 3);
            t7 = s3 & 0x7;
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = s3 ^ 0x8;
            if (!cc) {
                // 0x0052264c
                charge(ctx, 1);
                fp = sltu(0, t7);
            }
        }
        // 0x00522650
        charge(ctx, 4);
        lw(t5, sp, 0x0);
        t7 = sltiu(t5, 7);  // fewer than 7 elements: insertion sort
        sw(zero, sp, 0x8);
        if (t7 != 0) {
            break;
        }
        // 0x00522780
        charge(ctx, 6);
        lw(t5, sp, 0x0);
        t7 = srl(t5, 1);
        t6 = sltiu(t5, 8);
        mult(t7, t7, s3);
        s2 = addu(s6, t7);
        if (t6 != 0) {
            // 0x00522f28
            charge(ctx, 3);
            lw(t6, sp, 0x0);
            s5 = addiu(t6, -1);
            backedge(ctx);
        } else {
            // 0x00522798
            charge(ctx, 6);
            s5 = addiu(t5, -1);
            s0 = s6;
            mult(t7, s5, s3);
            t6 = sltiu(t5, 41);  // more than 40 elements: the pivot is the median of three medians
            s4 = addu(s6, t7);
            if (t6 == 0) {
                // 0x005227b0
                charge(ctx, 12);
                t7 = srl(t5, 3);
                a0 = s6;
                mult(t6, t7, s3);
                t7 = sll(t6, 1);
                sw(t6, sp, 0x4);
                s0 = addu(s6, t6);
                sw(t7, sp, 0x10);
                a1 = s0;
                s1 = addu(s6, t7);
                jalr(ctx, 0x5227D0u, s7.u());
                a0 = s0;
                if (i64(v0) >= 0) {
                    // 0x00522ef8
                    charge(ctx, 4);
                    a1 = s1;
                    jalr(ctx, 0x522EF8u, s7.u());
                    if (i64(v0) > 0) {
                        a0 = s0;
                        backedge(ctx);
                    } else {
                        // 0x00522f08
                        charge(ctx, 7);
                        a0 = s6;
                        a1 = s1;
                        jalr(ctx, 0x522F0Cu, s7.u());
                        v0 = slti(v0, 0);
                        a0 = s6;
                        if (v0 == 0) a0 = s1;
                        backedge(ctx);
                    }
                } else {
                    // 0x005227e0
                    charge(ctx, 4);
                    a1 = s1;
                    jalr(ctx, 0x5227E0u, s7.u());
                    if (i64(v0) < 0) {
                        a0 = s0;
                    } else {
                        // 0x005227f0
                        charge(ctx, 6);
                        a0 = s6;
                        a1 = s1;
                        jalr(ctx, 0x5227F4u, s7.u());
                        v0 = slti(v0, 0);
                        a0 = s1;
                        if (v0 == 0) a0 = s6;
                    }
                }
                // 0x00522808
                charge(ctx, 10);
                lw(t5, sp, 0x4);
                s0 = a0;
                a1 = s2;
                t5 = subu(s2, t5);
                sw(t5, sp, 0x14);
                jt = s7.u();  // the target, read before the delay slot
                link(ctx, 0x52281Cu);  // $ra = the return address
                lw(a0, sp, 0x14);
                call_ptr(ctx, jt);
                lw(t6, sp, 0x4);
                s1 = addu(s2, t6);
                if (i64(v0) >= 0) {
                    // 0x00522ec8
                    charge(ctx, 5);
                    a0 = s2;
                    a1 = s1;
                    jalr(ctx, 0x522ECCu, s7.u());
                    if (i64(v0) > 0) {
                        a0 = s2;
                        backedge(ctx);
                    } else {
                        // 0x00522edc
                        charge(ctx, 7);
                        lw(a0, sp, 0x14);
                        a1 = s1;
                        jalr(ctx, 0x522EE0u, s7.u());
                        lw(a0, sp, 0x14);
                        v0 = slti(v0, 0);
                        if (v0 == 0) a0 = s1;
                        backedge(ctx);
                    }
                } else {
                    // 0x00522830
                    charge(ctx, 5);
                    a0 = s2;
                    a1 = s1;
                    jalr(ctx, 0x522834u, s7.u());
                    if (i64(v0) < 0) {
                        a0 = s2;
                    } else {
                        // 0x00522844
                        charge(ctx, 6);
                        lw(a0, sp, 0x14);
                        a1 = s1;
                        jalr(ctx, 0x522848u, s7.u());
                        lw(a0, sp, 0x14);
                        v0 = slti(v0, 0);
                        if (v0 != 0) a0 = s1;
                    }
                }
                // 0x0052285c
                charge(ctx, 11);
                lw(t7, sp, 0x10);
                s2 = a0;
                lw(t5, sp, 0x4);
                t7 = subu(s4, t7);
                sw(t7, sp, 0x18);
                s1 = subu(s4, t5);
                a1 = s1;
                jt = s7.u();  // the target, read before the delay slot
                link(ctx, 0x522878u);  // $ra = the return address
                lw(a0, sp, 0x18);
                call_ptr(ctx, jt);
                a0 = s1;
                if (i64(v0) >= 0) {
                    // 0x00522e9c
                    charge(ctx, 4);
                    a1 = s4;
                    jalr(ctx, 0x522E9Cu, s7.u());
                    if (i64(v0) > 0) {
                        a0 = s1;
                        backedge(ctx);
                    } else {
                        // 0x00522eac
                        charge(ctx, 7);
                        lw(a0, sp, 0x18);
                        a1 = s4;
                        jalr(ctx, 0x522EB0u, s7.u());
                        lw(a0, sp, 0x18);
                        v0 = slti(v0, 0);
                        if (v0 == 0) a0 = s4;
                        backedge(ctx);
                    }
                } else {
                    // 0x00522888
                    charge(ctx, 4);
                    a1 = s4;
                    jalr(ctx, 0x522888u, s7.u());
                    a0 = s1;
                    if (i64(v0) >= 0) {
                        // 0x00522898
                        charge(ctx, 6);
                        lw(a0, sp, 0x18);
                        a1 = s4;
                        jalr(ctx, 0x52289Cu, s7.u());
                        lw(a0, sp, 0x18);
                        v0 = slti(v0, 0);
                        if (v0 != 0) a0 = s4;
                    }
                }
                // 0x005228b0
                charge(ctx, 1);
                s4 = a0;
            }
            // 0x005228b4
            charge(ctx, 5);
            a0 = s0;
            a1 = s2;
            jalr(ctx, 0x5228B8u, s7.u());
            a0 = s2;
            if (i64(v0) >= 0) {
                // 0x00522e70
                charge(ctx, 4);
                a1 = s4;
                jalr(ctx, 0x522E70u, s7.u());
                if (i64(v0) > 0) {
                    a0 = s2;
                    backedge(ctx);
                } else {
                    // 0x00522e80
                    charge(ctx, 7);
                    a0 = s0;
                    a1 = s4;
                    jalr(ctx, 0x522E84u, s7.u());
                    v0 = slti(v0, 0);
                    a0 = s0;
                    if (v0 == 0) a0 = s4;
                    backedge(ctx);
                }
            } else {
                // 0x005228c8
                charge(ctx, 4);
                a1 = s4;
                jalr(ctx, 0x5228C8u, s7.u());
                a0 = s2;
                if (i64(v0) >= 0) {
                    // 0x005228d8
                    charge(ctx, 6);
                    a0 = s0;
                    a1 = s4;
                    jalr(ctx, 0x5228DCu, s7.u());
                    v0 = slti(v0, 0);
                    a0 = s4;
                    if (v0 == 0) a0 = s0;
                }
            }
            // 0x005228f0
            charge(ctx, 1);
            s2 = a0;
        }
        // 0x005228f4
        charge(ctx, 2);
        t7 = slti(fp, 2);
        if (fp != 0) {
            // 0x00522df8
            charge(ctx, 2);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = srl(s3, 3);
            if (cc) {
                // 0x00522e38
                charge(ctx, 4);
                t4 = dsll32(s3, 0);
                a0 = s2;
                t4 = dsrl32(t4, 0);
                t5 = s6;
                for (;;) {
                    // 0x00522e48
                    charge(ctx, 8);
                    lb(t6, t5, 0);
                    t4 = daddiu(t4, -1);
                    lbu(t7, a0, 0);
                    sb(t7, t5, 0);
                    sb(t6, a0, 0);
                    t5 = addiu(t5, 1);
                    a0 = addiu(a0, 1);
                    if (i64(t4) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00522e68
                charge(ctx, 2);
                mult(t7, s5, s3);
                backedge(ctx);
            } else {
                // 0x00522e00
                charge(ctx, 4);
                a0 = s2;
                t4 = dsll32(t7, 0);
                t5 = s6;
                t4 = dsrl32(t4, 0);
                for (;;) {
                    // 0x00522e10
                    charge(ctx, 8);
                    ld(t6, t5, 0);
                    t4 = daddiu(t4, -1);
                    ld(t7, a0, 0);
                    sd(t7, t5, 0);
                    sd(t6, a0, 0);
                    t5 = addiu(t5, 8);
                    a0 = addiu(a0, 8);
                    if (i64(t4) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00522e30
                charge(ctx, 2);
                mult(t7, s5, s3);
                backedge(ctx);
            }
        } else {
            // 0x005228fc
            charge(ctx, 5);
            ld(t6, s6, 0);
            ld(t7, s2, 0);
            sd(t7, s6, 0);
            sd(t6, s2, 0);
            mult(t7, s5, s3);
        }
        // 0x00522910
        charge(ctx, 9);
        s2 = addu(s6, s3);
        t5 = slti(fp, 2);
        sw(s2, sp, 0x54);
        t6 = srl(s3, 3);
        sw(t5, sp, 0x1C);
        sw(t6, sp, 0x20);
        s4 = s2;
        s5 = addu(s6, t7);
        s1 = s5;
        for (;;) {
        L_00522934:
            charge(ctx, 3);
            s0 = sltu(s1, s2);
            a0 = s2;
            if (s0 == 0) {
                // 0x00522940
                charge(ctx, 4);
                a1 = s6;
                jalr(ctx, 0x522940u, s7.u());
                if (i64(v0) <= 0) {
                    // 0x00522d48
                    charge(ctx, 2);
                    if (v0 != 0) {
                        s2 = addu(s2, s3);
                        backedge(ctx);
                    } else {
                        // 0x00522d50
                        charge(ctx, 3);
                        t7 = 1;
                        sw(t7, sp, 0x8);
                        if (fp != 0) {
                            // 0x00522d78
                            charge(ctx, 3);
                            lw(t5, sp, 0x1C);
                            lw(t6, sp, 0x20);
                            if (t5 == 0) {
                                // 0x00522dbc
                                charge(ctx, 4);
                                t3 = dsll32(s3, 0);
                                t4 = s4;
                                t3 = dsrl32(t3, 0);
                                t5 = s2;
                                for (;;) {
                                    // 0x00522dcc
                                    charge(ctx, 8);
                                    lb(t6, t4, 0);
                                    t3 = daddiu(t3, -1);
                                    lbu(t7, t5, 0);
                                    sb(t7, t4, 0);
                                    sb(t6, t5, 0);
                                    t4 = addiu(t4, 1);
                                    t5 = addiu(t5, 1);
                                    if (i64(t3) <= 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x00522dec
                                charge(ctx, 2);
                                s4 = addu(s4, s3);
                                backedge(ctx);
                            } else {
                                // 0x00522d84
                                charge(ctx, 4);
                                t4 = s4;
                                t5 = s2;
                                t3 = dsll32(t6, 0);
                                t3 = dsrl32(t3, 0);
                                for (;;) {
                                    // 0x00522d94
                                    charge(ctx, 8);
                                    ld(t6, t4, 0);
                                    t3 = daddiu(t3, -1);
                                    ld(t7, t5, 0);
                                    sd(t7, t4, 0);
                                    sd(t6, t5, 0);
                                    t4 = addiu(t4, 8);
                                    t5 = addiu(t5, 8);
                                    if (i64(t3) <= 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x00522db4
                                charge(ctx, 2);
                                s4 = addu(s4, s3);
                                backedge(ctx);
                            }
                        } else {
                            // 0x00522d5c
                            charge(ctx, 5);
                            ld(t6, s4, 0);
                            ld(t7, s2, 0);
                            sd(t7, s4, 0);
                            sd(t6, s2, 0);
                            s4 = addu(s4, s3);
                        }
                        // 0x00522d70
                        charge(ctx, 2);
                        s2 = addu(s2, s3);
                        backedge(ctx);
                    }
                    continue;
                }
            }
            // 0x00522950
            charge(ctx, 4);
            t7 = slti(fp, 2);
            t5 = srl(s3, 3);
            sw(t7, sp, 0x30);
            sw(t5, sp, 0x40);
            for (;;) {
                // 0x00522960
                charge(ctx, 2);
                lw(t7, sp, 0x8);
                if (s0 != 0) {
                    break;
                }
                // 0x00522968
                charge(ctx, 5);
                a0 = s1;
                a1 = s6;
                jalr(ctx, 0x52296Cu, s7.u());
                if (i64(v0) < 0) {
                    goto L_0052297c_45;
                }
                // 0x00522a20
                charge(ctx, 2);
                if (v0 != 0) {
                    s1 = subu(s1, s3);
                } else {
                    // 0x00522a28
                    charge(ctx, 3);
                    t6 = 1;
                    sw(t6, sp, 0x8);
                    if (fp != 0) {
                        // 0x00522a54
                        charge(ctx, 3);
                        lw(t7, sp, 0x30);
                        t4 = s1;
                        if (t7 == 0) {
                            // 0x00522a98
                            charge(ctx, 3);
                            t3 = dsll32(s3, 0);
                            t3 = dsrl32(t3, 0);
                            t5 = s5;
                            for (;;) {
                                // 0x00522aa4
                                charge(ctx, 8);
                                lb(t6, t4, 0);
                                t3 = daddiu(t3, -1);
                                lbu(t7, t5, 0);
                                sb(t7, t4, 0);
                                sb(t6, t5, 0);
                                t4 = addiu(t4, 1);
                                t5 = addiu(t5, 1);
                                if (i64(t3) <= 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x00522ac4
                            charge(ctx, 2);
                            s5 = subu(s5, s3);
                            backedge(ctx);
                        } else {
                            // 0x00522a60
                            charge(ctx, 4);
                            lw(t5, sp, 0x40);
                            t3 = dsll32(t5, 0);
                            t3 = dsrl32(t3, 0);
                            t5 = s5;
                            for (;;) {
                                // 0x00522a70
                                charge(ctx, 8);
                                ld(t6, t4, 0);
                                t3 = daddiu(t3, -1);
                                ld(t7, t5, 0);
                                sd(t7, t4, 0);
                                sd(t6, t5, 0);
                                t4 = addiu(t4, 8);
                                t5 = addiu(t5, 8);
                                if (i64(t3) <= 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x00522a90
                            charge(ctx, 2);
                            s5 = subu(s5, s3);
                            backedge(ctx);
                        }
                    } else {
                        // 0x00522a34
                        charge(ctx, 5);
                        ld(t6, s1, 0);
                        ld(t7, s5, 0);
                        sd(t7, s1, 0);
                        sd(t6, s5, 0);
                        s5 = subu(s5, s3);
                    }
                    // 0x00522a48
                    charge(ctx, 1);
                    s1 = subu(s1, s3);
                }
                // 0x00522a4c
                charge(ctx, 2);
                s0 = sltu(s1, s2);
                backedge(ctx);
            }
            break;
        }
        // 0x00522ad0
        charge(ctx, 2);
        cc = t7 != 0;  // the condition, before the delay slot changes it
        lw(t7, sp, 0x0);
        if (!cc) {
            goto L_00522ad8_68;
        }
        // 0x00522bd8
        charge(ctx, 8);
        v0 = subu(s2, s4);
        t6 = subu(s4, s6);
        t3 = v0;
        mult(t5, t7, s3);
        t7 = slt(t6, v0);
        if (t7 != 0) v0 = t6;
        s4 = addu(s6, t5);
        if (i64(v0) > 0) {
            // 0x00522bf8
            charge(ctx, 3);
            t7 = slti(fp, 2);
            t5 = subu(s2, v0);
            if (t7 != 0) {
                // 0x00522c04
                charge(ctx, 5);
                t7 = srl(v0, 3);
                t4 = t5;
                v0 = dsll32(t7, 0);
                t5 = s6;
                v0 = dsrl32(v0, 0);
                for (;;) {
                    // 0x00522c18
                    charge(ctx, 8);
                    ld(t6, t5, 0);
                    v0 = daddiu(v0, -1);
                    ld(t7, t4, 0);
                    sd(t7, t5, 0);
                    sd(t6, t4, 0);
                    t5 = addiu(t5, 8);
                    t4 = addiu(t4, 8);
                    if (i64(v0) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                goto L_00522c38;
            }
            // 0x00522d10
            charge(ctx, 4);
            v0 = dsll32(v0, 0);
            t4 = t5;
            v0 = dsrl32(v0, 0);
            t5 = s6;
            for (;;) {
                // 0x00522d20
                charge(ctx, 8);
                lb(t6, t5, 0);
                v0 = daddiu(v0, -1);
                lbu(t7, t4, 0);
                sb(t7, t5, 0);
                sb(t6, t4, 0);
                t5 = addiu(t5, 1);
                t4 = addiu(t4, 1);
                if (i64(v0) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00522d40
            charge(ctx, 2);
            t6 = subu(s4, s5);
            backedge(ctx);
            goto L_00522c3c;
        }
    L_00522c38:
        charge(ctx, 1);
        t6 = subu(s4, s5);
    L_00522c3c:
        charge(ctx, 6);
        s0 = subu(s5, s1);
        v0 = subu(t6, s3);
        t7 = sltu(s0, v0);
        if (t7 != 0) v0 = s0;
        t7 = slti(fp, 2);
        if (i64(v0) > 0) {
            // 0x00522c54
            charge(ctx, 2);
            t5 = subu(s4, v0);
            if (t7 != 0) {
                // 0x00522c5c
                charge(ctx, 4);
                t7 = srl(v0, 3);
                a0 = s2;
                v0 = dsll32(t7, 0);
                v0 = dsrl32(v0, 0);
                for (;;) {
                    // 0x00522c6c
                    charge(ctx, 8);
                    ld(t6, a0, 0);
                    v0 = daddiu(v0, -1);
                    ld(t7, t5, 0);
                    sd(t7, a0, 0);
                    sd(t6, t5, 0);
                    a0 = addiu(a0, 8);
                    t5 = addiu(t5, 8);
                    if (i64(v0) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                goto L_00522c8c;
            }
            // 0x00522cd8
            charge(ctx, 3);
            v0 = dsll32(v0, 0);
            a0 = s2;
            v0 = dsrl32(v0, 0);
            for (;;) {
                // 0x00522ce4
                charge(ctx, 8);
                lb(t6, a0, 0);
                v0 = daddiu(v0, -1);
                lbu(t7, t5, 0);
                sb(t7, a0, 0);
                sb(t6, t5, 0);
                a0 = addiu(a0, 1);
                t5 = addiu(t5, 1);
                if (i64(v0) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00522d04
            charge(ctx, 2);
            t7 = sltu(s3, t3);
            backedge(ctx);
            goto L_00522c90;
        }
    L_00522c8c:
        charge(ctx, 1);
        t7 = sltu(s3, t3);
    L_00522c90:
        charge(ctx, 2);
        a0 = s6;
        if (t7 != 0) {
            // 0x00522c98
            charge(ctx, 3);
            divu(t3, s3);
            if (s3 == 0) {
                brk(ctx, 0x522CA0u, 0x7u);
            }
            // 0x00522ca4
            charge(ctx, 4);
            a2 = s3;
            a3 = s7;
            mflo(a1);
            jal(ctx, 0x522CACu, gen::fn_qsort_005225f8);
        }
        // 0x00522cb4
        charge(ctx, 3);
        t7 = sltu(s3, s0);
        s6 = subu(s4, s0);
        if (t7 == 0) {
            backedge(ctx);
            goto L_005226b8;
        }
        // 0x00522cc0
        charge(ctx, 3);
        divu(s0, s3);
        if (s3 == 0) {
            brk(ctx, 0x522CC8u, 0x7u);
        }
        // 0x00522ccc
        charge(ctx, 3);
        mflo(t7);
        sw(t7, sp, 0x0);
        backedge(ctx);
    }
    // 0x00522660
    charge(ctx, 6);
    mult(t6, t5, s3);
    s2 = addu(s6, s3);
    a1 = addu(s6, t6);
    t7 = sltu(s2, a1);
    s4 = slti(fp, 2);
    if (t7 != 0) {
        // 0x00522678
        charge(ctx, 3);
        sw(a1, sp, 0xC);
        s5 = srl(s3, 3);
        s0 = s2;
        for (;;) {
            // 0x00522684
            charge(ctx, 3);
            t7 = sltu(s6, s0);
            a1 = s0;
            if (t7 != 0) {
                // 0x00522690
                charge(ctx, 5);
                s1 = subu(s0, s3);
                a0 = s1;
                jalr(ctx, 0x522694u, s7.u());
                if (i64(v0) > 0) {
                    // 0x005226e8
                    charge(ctx, 2);
                    if (fp != 0) {
                        // 0x00522708
                        charge(ctx, 2);
                        t4 = dsll32(s5, 0);
                        if (s4 == 0) {
                            // 0x00522744
                            charge(ctx, 4);
                            t4 = dsll32(s3, 0);
                            a0 = s0;
                            t4 = dsrl32(t4, 0);
                            t5 = s1;
                            for (;;) {
                                // 0x00522754
                                charge(ctx, 8);
                                lb(t6, a0, 0);
                                t4 = daddiu(t4, -1);
                                lbu(t7, t5, 0);
                                sb(t7, a0, 0);
                                sb(t6, t5, 0);
                                a0 = addiu(a0, 1);
                                t5 = addiu(t5, 1);
                                if (i64(t4) <= 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x00522774
                            charge(ctx, 2);
                            s0 = s1;
                            backedge(ctx);
                        } else {
                            // 0x00522710
                            charge(ctx, 3);
                            a0 = s0;
                            t4 = dsrl32(t4, 0);
                            t5 = s1;
                            for (;;) {
                                // 0x0052271c
                                charge(ctx, 8);
                                ld(t6, a0, 0);
                                t4 = daddiu(t4, -1);
                                ld(t7, t5, 0);
                                sd(t7, a0, 0);
                                sd(t6, t5, 0);
                                a0 = addiu(a0, 8);
                                t5 = addiu(t5, 8);
                                if (i64(t4) <= 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0052273c
                            charge(ctx, 2);
                            s0 = s1;
                            backedge(ctx);
                        }
                    } else {
                        // 0x005226f0
                        charge(ctx, 6);
                        ld(t6, s0, 0);
                        ld(t7, s1, 0);
                        sd(t7, s0, 0);
                        sd(t6, s1, 0);
                        s0 = s1;
                        backedge(ctx);
                    }
                    continue;
                }
            }
            // 0x005226a4
            charge(ctx, 5);
            lw(t6, sp, 0xC);
            s2 = addu(s2, s3);
            t7 = sltu(s2, t6);
            s0 = s2;
            if (t7 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
L_005226b8:
    charge(ctx, 1);
    ld(s0, sp, 0x60);
    // 0x005226bc (the shared epilogue, written out on this path)
    charge(ctx, 11);
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
L_0052297c_45:
    charge(ctx, 2);
    t7 = slti(fp, 2);
    if (fp != 0) {
        // 0x005229a8
        charge(ctx, 2);
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = srl(s3, 3);
        if (cc) {
            // 0x005229e8
            charge(ctx, 4);
            t3 = dsll32(s3, 0);
            t4 = s2;
            t3 = dsrl32(t3, 0);
            t5 = s1;
            for (;;) {
                // 0x005229f8
                charge(ctx, 8);
                lb(t6, t4, 0);
                t3 = daddiu(t3, -1);
                lbu(t7, t5, 0);
                sb(t7, t4, 0);
                sb(t6, t5, 0);
                t4 = addiu(t4, 1);
                t5 = addiu(t5, 1);
                if (i64(t3) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00522a18
            charge(ctx, 2);
            t6 = 1;
            backedge(ctx);
        } else {
            // 0x005229b0
            charge(ctx, 4);
            t4 = s2;
            t3 = dsll32(t7, 0);
            t5 = s1;
            t3 = dsrl32(t3, 0);
            for (;;) {
                // 0x005229c0
                charge(ctx, 8);
                ld(t6, t4, 0);
                t3 = daddiu(t3, -1);
                ld(t7, t5, 0);
                sd(t7, t4, 0);
                sd(t6, t5, 0);
                t4 = addiu(t4, 8);
                t5 = addiu(t5, 8);
                if (i64(t3) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x005229e0
            charge(ctx, 2);
            t6 = 1;
            backedge(ctx);
        }
    } else {
        // 0x00522984
        charge(ctx, 5);
        ld(t6, s2, 0);
        ld(t7, s1, 0);
        sd(t7, s2, 0);
        sd(t6, s1, 0);
        t6 = 1;
    }
    // 0x00522998
    charge(ctx, 4);
    s2 = addu(s2, s3);
    sw(t6, sp, 0x8);
    s1 = subu(s1, s3);
    backedge(ctx);
    goto L_00522934;
L_00522ad8_68:
    charge(ctx, 7);
    lw(t5, sp, 0x0);
    lw(s2, sp, 0x54);
    mult(t6, t5, s3);
    a1 = addu(s6, t6);
    t7 = sltu(s2, a1);
    s4 = slti(fp, 2);
    if (t7 == 0) {
        backedge(ctx);
        goto L_005226b8;
    }
    // 0x00522af4
    charge(ctx, 3);
    sw(a1, sp, 0x50);
    s5 = srl(s3, 3);
    s0 = s2;
    for (;;) {
        // 0x00522b00
        charge(ctx, 3);
        t7 = sltu(s6, s0);
        a1 = s0;
        if (t7 != 0) {
            // 0x00522b0c
            charge(ctx, 5);
            s1 = subu(s0, s3);
            a0 = s1;
            jalr(ctx, 0x522B10u, s7.u());
            if (i64(v0) > 0) {
                // 0x00522b40
                charge(ctx, 2);
                if (fp != 0) {
                    // 0x00522b60
                    charge(ctx, 2);
                    t4 = dsll32(s5, 0);
                    if (s4 == 0) {
                        // 0x00522b9c
                        charge(ctx, 4);
                        t4 = dsll32(s3, 0);
                        a0 = s0;
                        t4 = dsrl32(t4, 0);
                        t5 = s1;
                        for (;;) {
                            // 0x00522bac
                            charge(ctx, 8);
                            lb(t6, a0, 0);
                            t4 = daddiu(t4, -1);
                            lbu(t7, t5, 0);
                            sb(t7, a0, 0);
                            sb(t6, t5, 0);
                            a0 = addiu(a0, 1);
                            t5 = addiu(t5, 1);
                            if (i64(t4) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x00522bcc
                        charge(ctx, 2);
                        s0 = s1;
                        backedge(ctx);
                    } else {
                        // 0x00522b68
                        charge(ctx, 3);
                        a0 = s0;
                        t4 = dsrl32(t4, 0);
                        t5 = s1;
                        for (;;) {
                            // 0x00522b74
                            charge(ctx, 8);
                            ld(t6, a0, 0);
                            t4 = daddiu(t4, -1);
                            ld(t7, t5, 0);
                            sd(t7, a0, 0);
                            sd(t6, t5, 0);
                            a0 = addiu(a0, 8);
                            t5 = addiu(t5, 8);
                            if (i64(t4) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x00522b94
                        charge(ctx, 2);
                        s0 = s1;
                        backedge(ctx);
                    }
                } else {
                    // 0x00522b48
                    charge(ctx, 6);
                    ld(t6, s0, 0);
                    ld(t7, s1, 0);
                    sd(t7, s0, 0);
                    sd(t6, s1, 0);
                    s0 = s1;
                    backedge(ctx);
                }
                continue;
            }
        }
        // 0x00522b20
        charge(ctx, 5);
        lw(t6, sp, 0x50);
        s2 = addu(s2, s3);
        t7 = sltu(s2, t6);
        if (t7 == 0) {
            break;
        }
        s0 = s2;
        backedge(ctx);
    }
    // 0x00522b34
    charge(ctx, 2);
    ld(s0, sp, 0x60);
    backedge(ctx);
    // 0x005226bc (the shared epilogue, written out on this path)
    charge(ctx, 11);
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
}

// 0x00522FC0 _realloc_r -- 1424 bytes; frame 0x60: s4 sp+0x30, s5 sp+0x38, fp sp+0x50, s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s6 sp+0x40, s7 sp+0x48, ra sp+0x58
// newlib's _realloc_r(reent, ptr, size): realloc(NULL) is malloc; under __malloc_lock it shrinks in place (freeing the
// tail), grows into a free next chunk or the top, merges with a free previous chunk (copying the contents down), or
// allocates a new chunk with _malloc_r, copies the old contents (inline word copies for short blocks, memcpy for long
// ones) and frees the old one with _free_r. Returns the new pointer or 0.
void _realloc_r(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00522fc0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s4, sp, 0x30);
    sd(s5, sp, 0x38);
    sd(fp, sp, 0x50);
    s4 = a1;
    sd(s0, sp, 0x10);
    s5 = a2;
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    sd(s3, sp, 0x28);
    sd(s6, sp, 0x40);
    sd(s7, sp, 0x48);
    sd(ra, sp, 0x58);
    fp = a0;
    if (a1 == 0) {
        // 0x00522ffc
        charge(ctx, 13);
        ld(s0, sp, 0x10);
        a1 = a2;
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(s3, sp, 0x28);
        ld(s4, sp, 0x30);
        ld(s5, sp, 0x38);
        ld(s6, sp, 0x40);
        ld(s7, sp, 0x48);
        ld(fp, sp, 0x50);
        ld(ra, sp, 0x58);
        sp = addiu(sp, 0x60);
        gen::fn__malloc_r_005209c0(ctx);  // tail call
        return;
    }
    // 0x00523030
    charge(ctx, 10);
    s0 = addiu(s4, -8);
    jal(ctx, 0x523030u, gen::fn___malloc_lock_005214c8);
    lw(t5, s0, 4);
    t7 = si(-4);
    t4 = addiu(s5, 19);
    s2 = s0;
    s3 = t5 & t7;
    t6 = sltiu(t4, 31);
    s1 = s3;
    if (t6 != 0) {
        // 0x00523548
        charge(ctx, 2);
        s6 = 16;
        backedge(ctx);
    } else {
        // 0x00523058
        charge(ctx, 2);
        t7 = si(-16);
        s6 = t4 & t7;
    }
    // 0x00523060
    charge(ctx, 3);
    t7 = sltu(s1, s6);
    cc = t7 == 0;  // the condition, before the delay slot changes it
    t7 = 0x780000;
    if (!cc) {
        // 0x0052306c
        charge(ctx, 5);
        t3 = addu(s2, s1);
        t1 = addiu(t7, 12096);
        lw(t2, t1, 8);
        t7 = si(-2);
        if (t3 != t2) {
            // 0x00523080
            charge(ctx, 7);
            lw(t4, t3, 4);
            t7 = t4 & t7;
            t7 = addu(t3, t7);
            lw(t6, t7, 4);
            t6 = t6 & 0x1;
            if (t6 == 0) {
                goto L_0052309c;
            }
            t3 = 0;
            // 0x00523538
            charge(ctx, 2);
            t4 = 0;
            backedge(ctx);
            // 0x0052311c
            charge(ctx, 1);
            lw(t7, s2, 4);
            goto L_00523120;
        }
        // 0x00523540
        charge(ctx, 2);
        lw(t4, t3, 4);
        backedge(ctx);
    L_0052309c:
        charge(ctx, 3);
        t7 = si(-4);
        t4 = t4 & t7;
        if (t3 != t2) {
            // 0x0052350c
            charge(ctx, 4);
            t6 = addu(t4, s1);
            t7 = sltu(t6, s6);
            if (t7 == 0) {
                // 0x0052351c
                charge(ctx, 7);
                lw(t2, t3, 8);
                s3 = t6;
                lw(t4, t3, 12);
                s1 = addiu(s2, 8);
                sw(t2, t4, 8);
                sw(t4, t2, 12);
                backedge(ctx);
                goto L_00523338;
            }
            lw(t7, s2, 4);
            backedge(ctx);
        L_00523120:
            charge(ctx, 3);
            t7 = t7 & 0x1;
            a1 = s5;
            if (t7 == 0) {
                // 0x0052312c
                charge(ctx, 6);
                lw(t7, s2, 0);
                s7 = subu(s2, t7);
                lw(t6, s7, 4);
                t7 = si(-4);
                t5 = t6 & t7;
                if (t3 != 0) {
                    // 0x00523144
                    charge(ctx, 4);
                    t7 = 0x780000;
                    lw(t6, t7, 12104);  // 0x782F48
                    t7 = addu(t4, t5);
                    if (t3 != t6) {
                        // 0x005234cc
                        charge(ctx, 4);
                        t7 = addu(t7, s1);
                        t6 = sltu(t7, s6);
                        a2 = addiu(s1, -4);
                        if (t6 != 0) {
                            backedge(ctx);
                            goto L_00523270;
                        }
                        // 0x005234dc
                        charge(ctx, 12);
                        lw(t2, t3, 8);
                        lw(t4, t3, 12);
                        s3 = t7;
                        s0 = s7;
                        s1 = addiu(s7, 8);
                        sw(t2, t4, 8);
                        t7 = sltiu(a2, 37);
                        sw(t4, t2, 12);
                        lw(t2, s7, 8);
                        lw(t4, s7, 12);
                        sw(t2, t4, 8);
                        backedge(ctx);
                    L_005232a4:
                        charge(ctx, 2);
                        sw(t4, t2, 12);
                        if (t7 == 0) {
                            // 0x005233a4
                            charge(ctx, 5);
                            a1 = s4;
                            a0 = s1;
                            jal(ctx, 0x5233A8u, gen::fn_memcpy_00521250);
                            lw(t5, s0, 4);
                            backedge(ctx);
                        } else {
                            // 0x005232ac
                            charge(ctx, 4);
                            t3 = s4;
                            t7 = sltiu(a2, 20);
                            t4 = s1;
                            if (t7 == 0) {
                                // 0x005232bc
                                charge(ctx, 8);
                                lw(t7, s4, 0);
                                t3 = addiu(s4, 8);
                                t4 = addiu(s0, 16);
                                t5 = sltiu(a2, 28);
                                sw(t7, s0, 8);
                                lw(t6, s4, 4);
                                sw(t6, s0, 12);
                                if (t5 == 0) {
                                    // 0x005232dc
                                    charge(ctx, 8);
                                    lw(t7, s4, 8);
                                    t5 = sltiu(a2, 36);
                                    t3 = addiu(s4, 16);
                                    t4 = addiu(s0, 24);
                                    sw(t7, s0, 16);
                                    lw(t6, s4, 12);
                                    sw(t6, s0, 20);
                                    if (t5 == 0) {
                                        // 0x005232fc
                                        charge(ctx, 6);
                                        lw(t6, s4, 16);
                                        t3 = addiu(s4, 24);
                                        t4 = addiu(s0, 32);
                                        sw(t6, s0, 24);
                                        lw(t7, s4, 20);
                                        sw(t7, s0, 28);
                                    }
                                }
                            }
                            // 0x00523314
                            charge(ctx, 9);
                            lw(t7, t3, 0);
                            sw(t7, t4, 0);
                            t3 = addiu(t3, 4);
                            lw(t6, t3, 0);
                            t4 = addiu(t4, 4);
                            sw(t6, t4, 0);
                            lw(t7, t3, 4);
                            sw(t7, t4, 4);
                            lw(t5, s7, 4);
                        }
                    L_00523338:
                        charge(ctx, 4);
                        t3 = subu(s3, s6);
                        t7 = sltiu(t3, 16);
                        cc = t7 != 0;  // the condition, before the delay slot changes it
                        t7 = t5 & 0x1;
                        if (cc) {
                            // 0x00523388
                            charge(ctx, 7);
                            t7 = t7 | s3;
                            t5 = addu(s0, s3);
                            sw(t7, s0, 4);
                            lw(t6, t5, 4);
                            t6 = t6 | 0x1;
                            sw(t6, t5, 4);
                            backedge(ctx);
                        } else {
                            // 0x00523348
                            charge(ctx, 12);
                            t6 = addu(s0, s6);
                            t7 = t7 | s6;
                            t4 = t3 | 0x1;
                            sw(t7, s0, 4);
                            t5 = addu(t6, t3);
                            a1 = addiu(t6, 8);
                            a0 = fp;
                            sw(t4, t6, 4);
                            lw(t7, t5, 4);
                            t7 = t7 | 0x1;
                            link(ctx, 0x523370u);  // $ra first: the delay slot below depends on it
                            sw(t7, t5, 4);
                            call(ctx, gen::fn__free_r_0051fbb0);
                        }
                        // 0x00523378
                        charge(ctx, 4);
                        a0 = fp;
                        jal(ctx, 0x523378u, gen::fn___malloc_unlock_00521520);
                        v0 = s1;
                        backedge(ctx);
                    } else {
                        // 0x00523154
                        charge(ctx, 6);
                        t6 = addu(t4, t5);
                        t7 = addiu(s6, 16);
                        t6 = addu(t6, s1);
                        t7 = sltu(t6, t7);
                        sw(t6, sp, 0x0);
                        if (t7 != 0) {
                            goto L_00523270;
                        }
                        // 0x0052316c
                        charge(ctx, 8);
                        lw(t4, s7, 12);
                        a2 = addiu(s1, -4);
                        lw(t2, s7, 8);
                        s3 = addiu(s7, 8);
                        t7 = sltiu(a2, 37);
                        sw(t2, t4, 8);
                        sw(t4, t2, 12);
                        if (t7 == 0) {
                            // 0x00523258
                            charge(ctx, 5);
                            a1 = s4;
                            a0 = s3;
                            jal(ctx, 0x52325Cu, gen::fn_memcpy_00521250);
                            lw(t6, sp, 0x0);
                            backedge(ctx);
                        } else {
                            // 0x0052318c
                            charge(ctx, 4);
                            t3 = s4;
                            t7 = sltiu(a2, 20);
                            t4 = s3;
                            if (t7 == 0) {
                                // 0x0052319c
                                charge(ctx, 8);
                                lw(t7, s4, 0);
                                t3 = addiu(s4, 8);
                                t4 = addiu(s7, 16);
                                t5 = sltiu(a2, 28);
                                sw(t7, s7, 8);
                                lw(t6, s4, 4);
                                sw(t6, s7, 12);
                                if (t5 == 0) {
                                    // 0x005231bc
                                    charge(ctx, 8);
                                    lw(t7, s4, 8);
                                    t5 = sltiu(a2, 36);
                                    t3 = addiu(s4, 16);
                                    t4 = addiu(s7, 24);
                                    sw(t7, s7, 16);
                                    lw(t6, s4, 12);
                                    sw(t6, s7, 20);
                                    if (t5 == 0) {
                                        // 0x005231dc
                                        charge(ctx, 6);
                                        lw(t6, s4, 16);
                                        t3 = addiu(s4, 24);
                                        t4 = addiu(s7, 32);
                                        sw(t6, s7, 24);
                                        lw(t7, s4, 20);
                                        sw(t7, s7, 28);
                                    }
                                }
                            }
                            // 0x005231f4
                            charge(ctx, 9);
                            lw(t7, t3, 0);
                            sw(t7, t4, 0);
                            t3 = addiu(t3, 4);
                            lw(t6, t3, 0);
                            t4 = addiu(t4, 4);
                            sw(t6, t4, 0);
                            lw(t7, t3, 4);
                            sw(t7, t4, 4);
                            lw(t6, sp, 0x0);
                        }
                        // 0x00523218
                        charge(ctx, 12);
                        t5 = addu(s7, s6);
                        a0 = fp;
                        t7 = subu(t6, s6);
                        t7 = t7 | 0x1;
                        t6 = 0x780000;
                        sw(t7, t5, 4);
                        sw(t5, t6, 12104);  // 0x782F48
                        lw(t7, s7, 4);
                        t7 = t7 & 0x1;
                        t7 = t7 | s6;
                        sw(t7, s7, 4);
                    L_00523248:
                        charge(ctx, 4);
                        jal(ctx, 0x523248u, gen::fn___malloc_unlock_00521520);
                        v0 = s3;
                        backedge(ctx);
                    }
                    // 0x005230ec (the shared epilogue, written out on this path)
                    charge(ctx, 12);
                    ld(s0, sp, 0x10);
                    ld(s1, sp, 0x18);
                    ld(s2, sp, 0x20);
                    ld(s3, sp, 0x28);
                    ld(s4, sp, 0x30);
                    ld(s5, sp, 0x38);
                    ld(s6, sp, 0x40);
                    ld(s7, sp, 0x48);
                    ld(fp, sp, 0x50);
                    ld(ra, sp, 0x58);
                    sp = addiu(sp, 0x60);
                    return;
                }
            L_00523270:
                charge(ctx, 2);
                t6 = addu(t5, s1);
                if (s7 == 0) {
                    // 0x005233b8
                    charge(ctx, 1);
                    a1 = s5;
                    goto L_005233bc;
                }
                // 0x00523278
                charge(ctx, 3);
                t7 = sltu(t6, s6);
                a1 = s5;
                if (t7 != 0) {
                    goto L_005233bc;
                }
                // 0x00523284
                charge(ctx, 8);
                lw(t4, s7, 12);
                a2 = addiu(s1, -4);
                lw(t2, s7, 8);
                s0 = s7;
                s3 = t6;
                s1 = addiu(s7, 8);
                sw(t2, t4, 8);
                t7 = sltiu(a2, 37);
                goto L_005232a4;
            }
        L_005233bc:
            charge(ctx, 4);
            a0 = fp;
            jal(ctx, 0x5233BCu, gen::fn__malloc_r_005209c0);
            s3 = v0;
            if (v0 != 0) {
                // 0x005233dc
                charge(ctx, 7);
                lw(t5, s2, 4);
                t7 = si(-2);
                s0 = addiu(v0, -8);
                t7 = t5 & t7;
                t7 = addu(s2, t7);
                a2 = addiu(s1, -4);
                if (s0 == t7) {
                    // 0x005233f8
                    charge(ctx, 5);
                    lw(t6, s0, 4);
                    t7 = si(-4);
                    t6 = t6 & t7;
                    s0 = s2;
                    s3 = addu(s1, t6);
                    goto L_0052340c;
                }
                // 0x00523414
                charge(ctx, 3);
                t7 = sltiu(a2, 37);
                t3 = s4;
                if (t7 == 0) {
                    // 0x005234b8
                    charge(ctx, 5);
                    a0 = v0;
                    a1 = s4;
                    jal(ctx, 0x5234BCu, gen::fn_memcpy_00521250);
                    a0 = fp;
                    backedge(ctx);
                } else {
                    // 0x00523420
                    charge(ctx, 3);
                    t7 = sltiu(a2, 20);
                    t4 = v0;
                    if (t7 == 0) {
                        // 0x0052342c
                        charge(ctx, 8);
                        lw(t7, s4, 0);
                        t3 = addiu(s4, 8);
                        t4 = addiu(v0, 8);
                        t5 = sltiu(a2, 28);
                        sw(t7, v0, 0);
                        lw(t6, s4, 4);
                        sw(t6, v0, 4);
                        if (t5 == 0) {
                            // 0x0052344c
                            charge(ctx, 8);
                            lw(t7, s4, 8);
                            t5 = sltiu(a2, 36);
                            t3 = addiu(s4, 16);
                            t4 = addiu(v0, 16);
                            sw(t7, v0, 8);
                            lw(t6, s4, 12);
                            sw(t6, v0, 12);
                            if (t5 == 0) {
                                // 0x0052346c
                                charge(ctx, 6);
                                lw(t6, s4, 16);
                                t3 = addiu(s4, 24);
                                t4 = addiu(v0, 24);
                                sw(t6, v0, 16);
                                lw(t7, s4, 20);
                                sw(t7, v0, 20);
                            }
                        }
                    }
                    // 0x00523484
                    charge(ctx, 9);
                    lw(t7, t3, 0);
                    sw(t7, t4, 0);
                    t3 = addiu(t3, 4);
                    lw(t6, t3, 0);
                    t4 = addiu(t4, 4);
                    sw(t6, t4, 0);
                    lw(t7, t3, 4);
                    sw(t7, t4, 4);
                    a0 = fp;
                }
                // 0x005234a8
                charge(ctx, 4);
                a1 = s4;
                jal(ctx, 0x5234A8u, gen::fn__free_r_0051fbb0);
                a0 = fp;
                backedge(ctx);
                goto L_00523248;
            }
            // 0x005233cc
            charge(ctx, 4);
            a0 = fp;
            jal(ctx, 0x5233CCu, gen::fn___malloc_unlock_00521520);
            v0 = 0;
            backedge(ctx);
        } else {
            // 0x005230a8
            charge(ctx, 5);
            t6 = addu(t4, s1);
            t7 = addiu(s6, 16);
            t7 = sltu(t6, t7);
            if (t7 != 0) {
                lw(t7, s2, 4);
                goto L_00523120;
            }
            // 0x005230bc
            charge(ctx, 12);
            t7 = subu(t6, s6);
            a0 = fp;
            t6 = addu(s2, s6);
            t7 = t7 | 0x1;
            sw(t7, t6, 4);
            sw(t6, t1, 8);
            lw(t7, s2, 4);
            t7 = t7 & 0x1;
            t7 = t7 | s6;
            link(ctx, 0x5230E0u);  // $ra first: the delay slot below depends on it
            sw(t7, s2, 4);
            call(ctx, gen::fn___malloc_unlock_00521520);
            v0 = addiu(s2, 8);
        }
        // 0x005230ec (the shared epilogue, written out on this path)
        charge(ctx, 12);
        ld(s0, sp, 0x10);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(s3, sp, 0x28);
        ld(s4, sp, 0x30);
        ld(s5, sp, 0x38);
        ld(s6, sp, 0x40);
        ld(s7, sp, 0x48);
        ld(fp, sp, 0x50);
        ld(ra, sp, 0x58);
        sp = addiu(sp, 0x60);
        return;
    }
L_0052340c:
    charge(ctx, 2);
    s1 = addiu(s2, 8);
    backedge(ctx);
    goto L_00523338;
}

}  // namespace p3fes::game
