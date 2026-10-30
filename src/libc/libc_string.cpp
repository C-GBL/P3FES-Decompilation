// Slice libc: newlib's string and memory functions (<string.h>, bzero, strtok, the scanf character-class builder __sccl).
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions and the C standard only
// (ADR-0010: no GPL or newlib source was opened). Pair tests: tests/game/test_libc.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libc.h"

namespace p3fes::recomp_gen {
void fn___sccl_005287d8(p3fes::EEContext&);
void fn_bzero_0051e118(p3fes::EEContext&);
void fn_memchr_005210d8(p3fes::EEContext&);
void fn_memcmp_005211b8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memmove_00521300(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_strcasecmp_00523dc8(p3fes::EEContext&);
void fn_strcat_00523e68(p3fes::EEContext&);
void fn_strchr_00523f98(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncat_005244c0(p3fes::EEContext&);
void fn_strncpy_00524828(p3fes::EEContext&);
void fn_strrchr_005249e8(p3fes::EEContext&);
void fn_strstr_00524a50(p3fes::EEContext&);
void fn_strtok_00525958(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace libc;  // the named offsets of p3fes/game/libc.h
namespace gen = ::p3fes::recomp_gen;

// 0x0051E118 bzero -- 52 bytes; leaf frame (no stack)
// bzero(p $a0, n $a1): store n zero bytes from p, one byte at a time (n counted down to -1). No result.
void bzero(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, t7{ctx, 15};
    // 0x0051e118
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = addiu(a1, -1);
    t7 = si(-1);
    if (a1 != t7) {
        for (;;) {
            // 0x0051e128: the byte loop
            charge(ctx, 7);
            sb(zero, a0, 0);
            a1 = addiu(a1, -1);
            a0 = addiu(a0, 1);
            if (a1 == t7) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0051e144: return (no result) (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005210D8 memchr -- 224 bytes; leaf frame (no stack)
// memchr(s $a0, c $a1, n $a2) -> $v0: the first byte equal to (unsigned char)c among the n bytes at s, or NULL. With n
// >= 16 and s 16-byte aligned it scans whole quadwords first (MMI: c copied into every byte, the has-zero-byte test (x
// - 0x01..01) & ~x & 0x80..80 on x ^ c, two 64-bit halves OR-ed), then finishes byte by byte from the quadword that
// matched or the < 16-byte tail.
void memchr(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    // 0x005210d8
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = sltiu(a2, 16);
    a1 = a1 & 0xFF;
    if (v0 == 0) {
        // 0x005210e4: n >= 16: s 16-byte aligned?
        charge(ctx, 3);
        v0 = a0 & 0xF;
        a3 = a0;
        if (v0 == 0) {
            // 0x005210f0: c replicated into every byte; the 0x01..01 / 0x80..80 masks
            charge(ctx, 18);
            v1 = dsll(a1, 8);
            v0 = 0x1010000;
            v0 = v0 | 0x101;  // &0x1010101
            v0 = dsll(v0, 16);
            v0 = v0 | 0x101;
            v0 = dsll(v0, 16);
            v0 = v0 | 0x101;
            t2 = v1 + a1;
            v1 = lui(0x8080);
            v1 = v1 | 0x8080;
            v1 = dsll(v1, 16);
            v1 = v1 | 0x8080;
            v1 = dsll(v1, 16);
            v1 = v1 | 0x8080;
            pcpyh(t0, t2);
            pcpyld(t1, t0, t0);
            a0 = v0;
            pcpyld(t0, v1, v1);
            for (;;) {
                // 0x00521138: quadword scan: has-zero-byte test: (x - 0x01..01) & ~x & 0x80..80 on x ^ c (both halves)
                charge(ctx, 11);
                lq(v0, a3, 0);
                pxor(v0, v0, t1);
                pcpyld(t2, a0, a0);
                pnor(v1, zero, v0);
                psubb(v0, v0, t2);
                pand(v0, v0, v1);
                pand(v0, v0, t0);
                pcpyud(v1, v0, t1);
                v0 = v0 | v1;
                if (v0 == 0) {
                    // 0x00521164: no match in these 16 bytes: next quadword
                    charge(ctx, 4);
                    a2 = addiu(a2, -16);
                    v0 = sltiu(a2, 16);
                    a3 = addiu(a3, 16);
                    if (v0 != 0) {
                        goto L_00521174_5;
                    }
                    backedge(ctx);
                    continue;
                }
                a0 = a3;
                break;
            }
        }
    }
L_00521178:
    charge(ctx, 5);
    v0 = lui(0xFFFF);
    a2 = addiu(a2, -1);
    v0 = v0 | 0xFFFF;
    if (a2 == v0) {
        // 0x005211a8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x0052118c: the byte scan (from the matching quadword or the start)
    charge(ctx, 2);
    v1 = lui(0xFFFF);
    v1 = v1 | 0xFFFF;
    for (;;) {
        // 0x00521194: byte == c?
        charge(ctx, 3);
        lbu(v0, a0, 0);
        a2 = addiu(a2, -1);
        if (v0 == a1) {
            goto L_005211b0;
        }
        // 0x005211a0: next byte
        charge(ctx, 2);
        a0 = addiu(a0, 1);
        if (a2 == v1) {
            break;
        }
        backedge(ctx);
    }
    // 0x005211a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = 0;
    return;
L_00521174_5:
    charge(ctx, 1);
    a0 = a3;
    goto L_00521178;
L_005211b0:
    charge(ctx, 2);
    v0 = a0;
}

// 0x005211B8 memcmp -- 148 bytes; leaf frame (no stack)
// memcmp(a $a0, b $a1, n $a2) -> $v0: 0 when the n bytes are equal, else the difference of the first differing bytes
// as unsigned chars (a[i] - b[i]). n >= 16 with both pointers 16-byte aligned compares quadwords (pxor, both halves)
// while they are equal, then the bytes of the differing quadword / the tail one by one.
void memcmp(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005211b8
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = sltiu(a2, 16);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = a0 | a1;
    if (!cc) {
        // 0x005211c4: n >= 16: both 16-byte aligned?
        charge(ctx, 3);
        v0 = v0 & 0xF;
        if (v0 == 0) {
            for (;;) {
                // 0x005211d0: compare a quadword (pxor of the two, both halves)
                charge(ctx, 11);
                lq(v1, a0, 0);
                a3 = sltiu(a2, 32);
                lq(v0, a1, 0);
                a0 = addiu(a0, 16);
                pxor(t0, v0, v1);
                v0 = addiu(a1, 16);
                pcpyud(t2, t0, a3);
                t1 = t2 | t0;
                if (t1 == 0) a1 = v0;
                if (t1 != 0) {
                    a0 = addiu(a0, -16);
                } else {
                    // 0x005211fc: equal: next quadword while >= 16 remain
                    charge(ctx, 2);
                    a2 = addiu(a2, -16);
                    if (a3 == 0) {
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
        }
    }
    // 0x00521204: the byte compare (n counted down to -1)
    charge(ctx, 5);
    v0 = lui(0xFFFF);
    a2 = addiu(a2, -1);
    v0 = v0 | 0xFFFF;
    if (a2 == v0) {
        // 0x00521244 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x00521218
    charge(ctx, 2);
    a3 = lui(0xFFFF);
    a3 = a3 | 0xFFFF;
    for (;;) {
        // 0x00521220: a[i] != b[i]?
        charge(ctx, 4);
        lbu(v1, a0, 0);
        lbu(v0, a1, 0);
        a0 = addiu(a0, 1);
        if (v1 != v0) {
            goto L_00521230_7;
        }
        // 0x00521238: next byte pair
        charge(ctx, 3);
        a2 = addiu(a2, -1);
        a1 = addiu(a1, 1);
        if (a2 == a3) {
            break;
        }
        backedge(ctx);
    }
    // 0x00521244 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = 0;
    return;
L_00521230_7:
    charge(ctx, 2);
    v0 = subu(v1, v0);
}

// 0x00521250 memcpy -- 176 bytes; leaf frame (no stack)
// memcpy(dst $a0, src $a1, n $a2) -> $v0 = dst. n >= 32 with both pointers 16-byte aligned: 32 bytes per iteration as
// two lq/sq pairs, then 8 bytes per ld/sd while >= 8 remain; everything else (and the tail) byte by byte. Overlap is
// not handled (memmove is).
void memcpy(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00521250
    enter(ctx, 4);  // entry check point + this block's cycles
    t0 = a0;
    v0 = sltiu(a2, 32);
    v1 = t0;
    if (v0 == 0) {
        // 0x00521260: n >= 32: both pointers 16-byte aligned?
        charge(ctx, 4);
        v0 = a1 | t0;
        v0 = v0 & 0xF;
        if (v0 == 0) {
            // 0x00521270
            charge(ctx, 1);
            a3 = t0;
            for (;;) {
                // 0x00521274: 32 bytes per iteration (two lq / sq pairs)
                charge(ctx, 11);
                lq(v1, a1, 0);
                a2 = addiu(a2, -32);
                a1 = addiu(a1, 16);
                a0 = sltiu(a2, 32);
                sq(v1, a3, 0);
                a3 = addiu(a3, 16);
                lq(v0, a1, 0);
                a1 = addiu(a1, 16);
                sq(v0, a3, 0);
                a3 = addiu(a3, 16);
                if (a0 != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x005212a0: >= 8 bytes left?
            charge(ctx, 3);
            v0 = sltiu(a2, 8);
            v1 = a3;
            if (v0 == 0) {
                for (;;) {
                    // 0x005212ac: 8 bytes per ld / sd
                    charge(ctx, 7);
                    ld(v1, a1, 0);
                    a2 = addiu(a2, -8);
                    a1 = addiu(a1, 8);
                    v0 = sltiu(a2, 8);
                    sd(v1, a3, 0);
                    a3 = addiu(a3, 8);
                    if (v0 != 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x005212c8
                charge(ctx, 1);
                v1 = a3;
            }
            goto L_005212cc;
        }
        a2 = addiu(a2, -1);
        goto L_005212d0;
    }
L_005212cc:
    charge(ctx, 1);
    a2 = addiu(a2, -1);
L_005212d0:
    charge(ctx, 3);
    v0 = si(-1);
    a0 = v0;
    if (a2 != v0) {
        for (;;) {
            // 0x005212dc: the byte copy (tail or unaligned)
            charge(ctx, 7);
            lbu(v0, a1, 0);
            a2 = addiu(a2, -1);
            a1 = addiu(a1, 1);
            sb(v0, v1, 0);
            v1 = addiu(v1, 1);
            if (a2 == a0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x005212f8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = t0;
}

// 0x00521300 memmove -- 260 bytes; leaf frame (no stack)
// memmove(dst $a0, src $a1, n $a2) -> $v0 = dst. When src < dst < src + n the regions overlap with dst above: copy
// byte by byte from the end down. Otherwise the memcpy order: 32-byte lq/sq blocks when n >= 32 and both pointers are
// 16-byte aligned, 8-byte ld/sd blocks, then bytes.
void memmove(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00521300
    enter(ctx, 4);  // entry check point + this block's cycles
    t0 = a0;
    v0 = sltu(a1, t0);
    v1 = t0;
    if (v0 != 0) {
        // 0x00521310: src < dst: does dst start inside [src, src + n)?
        charge(ctx, 4);
        a3 = addu(a1, a2);
        v0 = sltu(t0, a3);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = si(-1);
        if (cc) {
            goto L_00521358;
        }
        // 0x00521320: overlapping, dst above src: copy backwards
        charge(ctx, 4);
        v1 = addu(t0, a2);
        a2 = addiu(a2, -1);
        a1 = a3;
        if (a2 == v0) {
            // 0x005213fc (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = t0;
            return;
        }
        // 0x00521330
        charge(ctx, 1);
        a0 = v0;
        for (;;) {
            // 0x00521334: one byte from the end down
            charge(ctx, 7);
            a1 = addiu(a1, -1);
            v1 = addiu(v1, -1);
            lbu(v0, a1, 0);
            a2 = addiu(a2, -1);
            sb(v0, v1, 0);
            if (a2 == a0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00521350
        charge(ctx, 2);
        v0 = t0;
        return;
    }
L_00521358:
    charge(ctx, 3);
    v0 = sltiu(a2, 32);
    if (v0 != 0) {
        a2 = addiu(a2, -1);
    } else {
        // 0x00521364: forward copy: both pointers 16-byte aligned?
        charge(ctx, 4);
        v0 = a1 | v1;
        v0 = v0 & 0xF;
        if (v0 != 0) {
            a2 = addiu(a2, -1);
        } else {
            // 0x00521374
            charge(ctx, 1);
            a3 = v1;
            for (;;) {
                // 0x00521378: 32 bytes per iteration (two lq / sq pairs)
                charge(ctx, 11);
                lq(v1, a1, 0);
                a2 = addiu(a2, -32);
                a1 = addiu(a1, 16);
                a0 = sltiu(a2, 32);
                sq(v1, a3, 0);
                a3 = addiu(a3, 16);
                lq(v0, a1, 0);
                a1 = addiu(a1, 16);
                sq(v0, a3, 0);
                a3 = addiu(a3, 16);
                if (a0 != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x005213a4
            charge(ctx, 3);
            v0 = sltiu(a2, 8);
            v1 = a3;
            if (v0 == 0) {
                for (;;) {
                    // 0x005213b0: 8 bytes per ld / sd
                    charge(ctx, 7);
                    ld(v1, a1, 0);
                    a2 = addiu(a2, -8);
                    a1 = addiu(a1, 8);
                    v0 = sltiu(a2, 8);
                    sd(v1, a3, 0);
                    a3 = addiu(a3, 8);
                    if (v0 != 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x005213cc
                charge(ctx, 1);
                v1 = a3;
            }
            // 0x005213d0
            charge(ctx, 1);
            a2 = addiu(a2, -1);
        }
    }
    // 0x005213d4
    charge(ctx, 3);
    v0 = si(-1);
    a0 = v0;
    if (a2 != v0) {
        for (;;) {
            // 0x005213e0: the forward byte copy
            charge(ctx, 7);
            lbu(v0, a1, 0);
            a2 = addiu(a2, -1);
            a1 = addiu(a1, 1);
            sb(v0, v1, 0);
            v1 = addiu(v1, 1);
            if (a2 == a0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x005213fc (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = t0;
}

// 0x00521408 memset -- 192 bytes; leaf frame (no stack)
// memset(s $a0, c $a1, n $a2) -> $v0 = s. n >= 8 with s 16-byte aligned: the byte replicated into a halfword, pcpyh
// into a doubleword and pcpyld into a quadword; 32 bytes per two sq while >= 32 remain, 8 per sd while >= 8 remain;
// the rest (and unaligned / short requests) byte by byte with sb of the low byte of c.
void memset(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    // 0x00521408
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = sltiu(a2, 8);
    v1 = a0;
    if (v0 == 0) {
        // 0x00521414: n >= 8: s 16-byte aligned?
        charge(ctx, 3);
        v0 = a0 & 0xF;
        a3 = a0;
        if (v0 == 0) {
            // 0x00521420: c replicated: byte -> halfword -> doubleword (pcpyh)
            charge(ctx, 8);
            t1 = a1 & 0xFF;
            t2 = sltiu(a2, 32);
            t0 = t1;
            v1 = dsll(t0, 8);
            t0 = v1 | t1;
            pcpyh(v1, t0);
            v0 = sltiu(a2, 8);
            if (t2 == 0) {
                // 0x00521440: n >= 32: the quadword pattern (pcpyld)
                charge(ctx, 1);
                pcpyld(t0, v1, v1);
                for (;;) {
                    // 0x00521444: 32 bytes per two sq
                    charge(ctx, 7);
                    sq(t0, a3, 0);
                    a2 = addiu(a2, -32);
                    a3 = addiu(a3, 16);
                    v0 = sltiu(a2, 32);
                    sq(t0, a3, 0);
                    a3 = addiu(a3, 16);
                    if (v0 != 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00521460
                charge(ctx, 2);
                v0 = sltiu(a2, 8);
            }
            for (;;) {
                // 0x00521474: 8 bytes per sd while >= 8 remain
                charge(ctx, 4);
                if (v0 != 0) {
                    break;
                }
                sd(v1, a3, 0);
                backedge(ctx);
                // 0x00521468
                charge(ctx, 3);
                a2 = addiu(a2, -8);
                a3 = addiu(a3, 8);
                v0 = sltiu(a2, 8);
            }
            // 0x00521484
            charge(ctx, 1);
            v1 = a3;
        }
    }
    // 0x00521488: the byte stores (n counted down to -1)
    charge(ctx, 5);
    v0 = lui(0xFFFF);
    a2 = addiu(a2, -1);
    v0 = v0 | 0xFFFF;
    if (a2 != v0) {
        // 0x0052149c
        charge(ctx, 2);
        v0 = lui(0xFFFF);
        v0 = v0 | 0xFFFF;
        for (;;) {
            // 0x005214a4: one byte
            charge(ctx, 7);
            sb(a1, v1, 0);
            a2 = addiu(a2, -1);
            v1 = addiu(v1, 1);
            if (a2 == v0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x005214c0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
}

// 0x00523DC8 strcasecmp -- 160 bytes; leaf frame (no stack)
// strcasecmp(a $a0, b $a1) -> $v0: compare ignoring case. Each byte is folded to lower case through the <ctype.h>
// class table at 0x7BE9C8 (bit 0 = upper case: +32); stops at the first difference or the end of a; returns the
// difference of the folded bytes as unsigned chars.
void strcasecmp(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    // 0x00523dc8
    enter(ctx, 2);  // entry check point + this block's cycles
    t7 = 0x7C0000;
    t0 = addiu(t7, -5688);  // &0x7BE9C8
    for (;;) {
        // 0x00523dd0: next byte of a; the end of a stops the loop
        charge(ctx, 7);
        lbu(v0, a0, 0);
        t7 = sll(v0, 24);
        a0 = addiu(a0, 1);
        t7 = sra(t7, 24);
        t5 = addu(t7, t0);
        t2 = addiu(t7, 32);
        if (t7 == 0) {
            goto L_00523e60;
        }
        // 0x00523dec: fold both bytes through the class table (bit 0: upper -> +32); equal: go on
        charge(ctx, 13);
        lbu(t1, a1, 0);
        lbu(t5, t5, 0);
        t4 = sll(t1, 24);
        t4 = sra(t4, 24);
        t5 = t5 & 0x1;
        t3 = addu(t4, t0);
        if (t5 == 0) t2 = t7;
        lbu(t7, t3, 0);
        t6 = addiu(t4, 32);
        t7 = t7 & 0x1;
        if (t7 == 0) t6 = t4;
        a1 = addiu(a1, 1);
        if (t2 == t6) {
            backedge(ctx);
            continue;
        }
        break;
    }
    // 0x00523e20: the result: the folded bytes as unsigned chars, subtracted (the shared epilogue, written out on this path)
    charge(ctx, 16);
    t7 = 0x7C0000;
    t5 = t1 & 0xFF;
    t7 = addiu(t7, -5688);  // &0x7BE9C8
    v0 = v0 & 0xFF;
    t4 = addu(t5, t7);
    t2 = addiu(v0, 32);
    t7 = addu(v0, t7);
    t3 = addiu(t5, 32);
    lbu(t6, t7, 0);
    lbu(t7, t4, 0);
    t6 = t6 & 0x1;
    if (t6 != 0) v0 = t2;
    t7 = t7 & 0x1;
    if (t7 != 0) t5 = t3;
    v0 = subu(v0, t5);
    return;
L_00523e60:
    charge(ctx, 2);
    lbu(t1, a1, 0);
    backedge(ctx);
    // 0x00523e20: the result: the folded bytes as unsigned chars, subtracted (the shared epilogue, written out on this path)
    charge(ctx, 16);
    t7 = 0x7C0000;
    t5 = t1 & 0xFF;
    t7 = addiu(t7, -5688);  // &0x7BE9C8
    v0 = v0 & 0xFF;
    t4 = addu(t5, t7);
    t2 = addiu(v0, 32);
    t7 = addu(v0, t7);
    t3 = addiu(t5, 32);
    lbu(t6, t7, 0);
    lbu(t7, t4, 0);
    t6 = t6 & 0x1;
    if (t6 != 0) v0 = t2;
    t7 = t7 & 0x1;
    if (t7 != 0) t5 = t3;
    v0 = subu(v0, t5);
}

// 0x00523E68 strcat -- 300 bytes; frame 0x20: s0 sp+0x0 (sq), ra sp+0x10 (sq)
// strcat(dst $a0, src $a1) -> $v0 = dst: find the NUL of dst (quadword / doubleword has-zero-byte scans when dst is
// 8-byte aligned, then bytes) and copy src there through strcpy.
void strcat(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00523e68
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = s0 & 0x7;
    sq(ra, sp, 0x10);
    if (v0 == 0) {
        // 0x00523e80: dst 8-byte aligned: the word-scan masks; 16-byte aligned?
        charge(ctx, 15);
        v0 = s0 & 0xF;
        v1 = 0x1010000;
        v1 = v1 | 0x101;  // &0x1010101
        v1 = dsll(v1, 16);
        v1 = v1 | 0x101;
        v1 = dsll(v1, 16);
        v1 = v1 | 0x101;
        a0 = lui(0x8080);
        a0 = a0 | 0x8080;
        a0 = dsll(a0, 16);
        a0 = a0 | 0x8080;
        a0 = dsll(a0, 16);
        a0 = a0 | 0x8080;
        ld(a2, s0, 0);
        if (v0 != 0) {
            // 0x00523f18: doubleword scan for the NUL (has-zero-byte test: (x - 0x01..01) & ~x & 0x80..80)
            charge(ctx, 8);
            a3 = v1;
            t0 = a0;
            v1 = a2 - v1;
            v0 = nor(0, a2);
            v1 = v1 & v0;
            v1 = v1 & a0;
            a0 = s0;
            if (v1 == 0) {
                // 0x00523f38
                charge(ctx, 1);
                a2 = addiu(s0, 8);
                for (;;) {
                    // 0x00523f3c
                    charge(ctx, 7);
                    ld(v0, a2, 0);
                    v1 = nor(0, v0);
                    v0 = v0 - a3;
                    v0 = v0 & v1;
                    v0 = v0 & t0;
                    if (v0 != 0) {
                        break;
                    }
                    a2 = addiu(a2, 8);
                    backedge(ctx);
                }
                // 0x00523f58
                charge(ctx, 1);
                a0 = a2;
            }
        } else {
            // 0x00523ebc: quadword scan for the NUL (MMI)
            charge(ctx, 11);
            lq(v0, s0, 0);
            pcpyld(a3, v1, v1);
            pcpyld(t0, a0, a0);
            psubb(v1, v0, a3);
            pnor(v0, zero, v0);
            pand(v1, v1, v0);
            pand(v1, v1, t0);
            pcpyud(v0, v1, v1);
            v1 = v0 | v1;
            a0 = s0;
            if (v1 == 0) {
                // 0x00523ee8
                charge(ctx, 1);
                a2 = addiu(a0, 16);
                for (;;) {
                    // 0x00523eec
                    charge(ctx, 9);
                    lq(v0, a2, 0);
                    pnor(v1, zero, v0);
                    psubb(v0, v0, a3);
                    pand(v0, v0, v1);
                    pand(v0, v0, t0);
                    pcpyud(v1, v0, v0);
                    v0 = v0 | v1;
                    if (v0 != 0) {
                        break;
                    }
                    a2 = addiu(a2, 16);
                    backedge(ctx);
                }
                // 0x00523f10
                charge(ctx, 2);
                a0 = a2;
            }
        }
    }
    for (;;) {
        // 0x00523f5c: the byte scan to the NUL
        charge(ctx, 7);
        lb(v0, a0, 0);
        if (v0 == 0) {
            break;
        }
        a0 = addiu(a0, 1);
        backedge(ctx);
    }
    // 0x00523f78: strcpy(end of dst, src); return dst
    charge(ctx, 7);
    jal(ctx, 0x523F78u, gen::fn_strcpy_00524270);
    v0 = s0;
    lq(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00523F98 strchr -- 400 bytes; leaf frame (no stack)
// strchr(s $a0, c $a1) -> $v0: the first occurrence of (char)c in s, the terminating NUL included (c == 0 returns the
// NUL's address), else NULL. Aligned strings are scanned 16 (MMI) or 8 bytes at a time with two has-zero-byte tests
// per word (the word itself: end of string; the word ^ c-replicated: a match), then byte by byte from the word that
// hit.
void strchr(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00523f98
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = a0 & 0x7;
    a1 = a1 & 0xFF;
    if (v0 == 0) {
        // 0x00523fa4: aligned: c replicated into a doubleword, the masks
        charge(ctx, 20);
        v1 = dsll(a1, 8);
        a2 = 0x1010000;
        a2 = a2 | 0x101;  // &0x1010101
        a2 = dsll(a2, 16);
        a2 = a2 | 0x101;
        a2 = dsll(a2, 16);
        a2 = a2 | 0x101;
        t2 = v1 + a1;
        v1 = a0 & 0xF;
        v0 = dsll(t2, 16);
        t0 = lui(0x8080);
        t0 = t0 | 0x8080;
        t0 = dsll(t0, 16);
        t0 = t0 | 0x8080;
        t0 = dsll(t0, 16);
        t0 = t0 | 0x8080;
        v0 = v0 + t2;
        t2 = dsll32(v0, 0);
        a3 = v0 + t2;
        if (v1 != 0) {
            // 0x00524080: doubleword path: NUL in the first word?
            charge(ctx, 7);
            ld(t1, a0, 0);
            v1 = nor(0, t1);
            v0 = t1 - a2;
            v0 = v0 & v1;
            v0 = v0 & t0;
            if (v0 != 0) {
                lbu(v0, a0, 0);
            } else {
                // 0x0052409c: c in the first word?
                charge(ctx, 7);
                v0 = t1 ^ a3;
                v1 = v0 - a2;
                v0 = nor(0, v0);
                v1 = v1 & v0;
                v1 = v1 & t0;
                if (v1 != 0) {
                    lbu(v0, a0, 0);
                } else {
                    // 0x005240b8
                    charge(ctx, 2);
                    t1 = a2;
                    a0 = addiu(a0, 8);
                    for (;;) {
                        // 0x005240c0: next doubleword: NUL?
                        charge(ctx, 7);
                        ld(a2, a0, 0);
                        v0 = a2 - t1;
                        v1 = nor(0, a2);
                        v0 = v0 & v1;
                        v0 = v0 & t0;
                        cc = v0 != 0;  // the condition, before the delay slot changes it
                        v0 = a2 ^ a3;
                        if (cc) {
                            goto L_00524108;
                        }
                        // 0x005240dc: ... or c?
                        charge(ctx, 6);
                        v1 = nor(0, v0);
                        v0 = v0 - t1;
                        v0 = v0 & v1;
                        v0 = v0 & t0;
                        if (v0 != 0) {
                            break;
                        }
                        a0 = addiu(a0, 8);
                        backedge(ctx);
                    }
                    // 0x005240f4
                    charge(ctx, 2);
                    lbu(v0, a0, 0);
                }
            }
        } else {
            for (;;) {
                // 0x00523ff4: quadword path: NUL in these 16 bytes?
                charge(ctx, 12);
                lq(t1, a0, 0);
                pcpyld(t2, a2, a2);
                pnor(v1, zero, t1);
                psubb(v0, t1, t2);
                pcpyld(a2, t0, t0);
                pand(v0, v0, v1);
                pcpyld(t0, a3, a3);
                pand(v0, v0, a2);
                pcpyud(v1, v0, a3);
                v1 = v0 | v1;
                if (v1 == 0) {
                    // 0x00524024: ... or c? (x ^ c-replicated)
                    charge(ctx, 21);
                    pxor(v0, t1, t0);
                    psubb(v1, v0, t2);
                    pnor(v0, zero, v0);
                    t0 = lui(0x8080);
                    t0 = t0 | 0x8080;
                    t0 = dsll(t0, 16);
                    t0 = t0 | 0x8080;
                    t0 = dsll(t0, 16);
                    t0 = t0 | 0x8080;
                    pand(v1, v1, v0);
                    pand(v1, v1, a2);
                    a2 = 0x1010000;
                    a2 = a2 | 0x101;  // &0x1010101
                    a2 = dsll(a2, 16);
                    a2 = a2 | 0x101;
                    a2 = dsll(a2, 16);
                    a2 = a2 | 0x101;
                    pcpyud(v0, v1, a1);
                    v1 = v0 | v1;
                    if (v1 != 0) {
                        goto L_00524078_4;
                    }
                    a0 = addiu(a0, 16);
                    backedge(ctx);
                    continue;
                }
                lbu(v0, a0, 0);
                break;
            }
        }
        goto L_0052410c;
    }
L_00524108:
    charge(ctx, 1);
    lbu(v0, a0, 0);
L_0052410c:
    charge(ctx, 2);
    if (v0 != 0) {
        backedge(ctx);
        // 0x005240fc: the byte scan: byte == c?
        charge(ctx, 2);
        if (v0 != a1) {
            // 0x00524104: next byte
            charge(ctx, 1);
            a0 = addiu(a0, 1);
            goto L_00524108;
        }
        lbu(v1, a0, 0);
    } else {
        // 0x00524114: at the NUL
        charge(ctx, 1);
        lbu(v1, a0, 0);
    }
    // 0x00524118: return the position when its byte is c (c == 0 finds the NUL), else NULL (the shared epilogue, written out on this path)
    charge(ctx, 4);
    v0 = 0;
    v1 = v1 ^ a1;
    if (v1 == 0) v0 = a0;
    return;
L_00524078_4:
    charge(ctx, 2);
    lbu(v0, a0, 0);
    goto L_0052410c;
}

// 0x00524128 strcmp -- 324 bytes; leaf frame (no stack)
// strcmp(a $a0, b $a1) -> $v0: the difference of the first differing bytes as unsigned chars, 0 when equal. When both
// are 8-byte aligned it compares whole quadwords (16-byte aligned) or doublewords while they are equal and contain no
// NUL (equal words with a NUL mean equal strings: 0), then byte by byte.
void strcmp(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    // 0x00524128
    enter(ctx, 4);  // entry check point + this block's cycles
    t0 = a0 | a1;
    v0 = t0 & 0x7;
    if (v0 != 0) {
        lb(v0, a0, 0);
    } else {
        // 0x00524138: both 8-byte aligned: the masks; 16-byte aligned?
        charge(ctx, 15);
        t1 = t0 & 0xF;
        a3 = 0x1010000;
        a3 = a3 | 0x101;  // &0x1010101
        a3 = dsll(a3, 16);
        a3 = a3 | 0x101;
        a3 = dsll(a3, 16);
        a3 = a3 | 0x101;
        a2 = lui(0x8080);
        a2 = a2 | 0x8080;
        a2 = dsll(a2, 16);
        a2 = a2 | 0x8080;
        a2 = dsll(a2, 16);
        a2 = a2 | 0x8080;
        ld(v0, a1, 0);
        if (t1 != 0) {
            // 0x005241ec: doubleword path: first words equal?
            charge(ctx, 3);
            ld(v1, a0, 0);
            if (v1 != v0) {
                lb(v0, a0, 0);
                goto L_00524258;
            }
            // 0x005241f8
            charge(ctx, 2);
            ld(v0, a0, 0);
            t0 = nor(0, v0);
            for (;;) {
                // 0x00524200: equal word with a NUL: the strings are equal (0)
                charge(ctx, 5);
                v0 = v0 - a3;
                v0 = v0 & t0;
                v0 = v0 & a2;
                a0 = addiu(a0, 8);
                if (v0 != 0) {
                    goto L_00524214_11;
                }
                // 0x0052421c: next doubleword pair
                charge(ctx, 5);
                a1 = addiu(a1, 8);
                ld(v0, a0, 0);
                ld(v1, a1, 0);
                if (v1 != v0) {
                    break;
                }
                t0 = nor(0, v0);
                backedge(ctx);
            }
            // 0x00524230
            charge(ctx, 2);
            lb(v0, a0, 0);
            goto L_00524258;
        }
        // 0x00524174: quadword path: first quadwords equal? (psubw, both halves)
        charge(ctx, 9);
        lq(v1, a0, 0);
        pcpyld(t0, a3, a3);
        lq(v0, a1, 0);
        pcpyld(t2, a2, a2);
        psubw(a3, v0, v1);
        pcpyud(a2, a3, a0);
        v1 = a2 | a3;
        if (v1 != 0) {
            lb(v0, a0, 0);
            goto L_00524258;
        }
        // 0x00524198
        charge(ctx, 2);
        lq(v0, a0, 0);
        pnor(v1, zero, v0);
        for (;;) {
            // 0x005241a0: equal quadword with a NUL: equal (0)
            charge(ctx, 7);
            psubb(v0, v0, t0);
            pand(v0, v0, v1);
            pand(v0, v0, t2);
            pcpyud(v1, v0, a0);
            a2 = v1 | v0;
            a0 = addiu(a0, 16);
            if (a2 != 0) {
                goto L_005241bc_5;
            }
            // 0x005241c4: next quadword pair
            charge(ctx, 8);
            a1 = addiu(a1, 16);
            lq(v0, a0, 0);
            lq(v1, a1, 0);
            psubw(a3, v0, v1);
            pcpyud(a2, a3, a0);
            t1 = a2 | a3;
            if (t1 != 0) {
                break;
            }
            pnor(v1, zero, v0);
            backedge(ctx);
        }
        // 0x005241e4
        charge(ctx, 2);
        lb(v0, a0, 0);
        goto L_00524258;
    }
    for (;;) {
    L_00524258:
        charge(ctx, 2);
        lbu(v1, a0, 0);
        if (v0 != 0) {
            backedge(ctx);
            // 0x00524238: the byte compare
            charge(ctx, 5);
            v0 = sll(v1, 24);
            lb(v1, a1, 0);
            v0 = sra(v0, 24);
            if (v0 == v1) {
                // 0x0052424c: equal bytes: next pair
                charge(ctx, 3);
                a0 = addiu(a0, 1);
                a1 = addiu(a1, 1);
                lb(v0, a0, 0);
                continue;
            }
            lbu(v1, a0, 0);
        }
        break;
    }
    // 0x00524260: the difference of the bytes as unsigned chars (the shared epilogue, written out on this path)
    charge(ctx, 3);
    lbu(v0, a1, 0);
    v0 = subu(v1, v0);
    return;
L_005241bc_5:
    charge(ctx, 2);
    v0 = 0;
    return;
L_00524214_11:
    charge(ctx, 2);
    v0 = 0;
}

// 0x00524270 strcpy -- 276 bytes; leaf frame (no stack)
// strcpy(dst $a0, src $a1) -> $v0 = dst. Both 8-byte aligned: copy whole quadwords (16-aligned) or doublewords while
// they hold no NUL, then the last bytes up to and including the NUL one at a time.
void strcpy(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    // 0x00524270
    enter(ctx, 5);  // entry check point + this block's cycles
    a3 = a0;
    t0 = a1 | a3;
    v0 = t0 & 0x7;
    v1 = a3;
    if (v0 == 0) {
        // 0x00524284: both 8-byte aligned: the masks; 16-byte aligned?
        charge(ctx, 15);
        v0 = t0 & 0xF;
        t1 = 0x1010000;
        t1 = t1 | 0x101;  // &0x1010101
        t1 = dsll(t1, 16);
        t1 = t1 | 0x101;
        t1 = dsll(t1, 16);
        t1 = t1 | 0x101;
        a0 = lui(0x8080);
        a0 = a0 | 0x8080;
        a0 = dsll(a0, 16);
        a0 = a0 | 0x8080;
        a0 = dsll(a0, 16);
        a0 = a0 | 0x8080;
        if (v0 != 0) {
            ld(t2, a1, 0);
            // 0x00524320: doubleword copy while the word holds no NUL
            charge(ctx, 6);
            v0 = t2 - t1;
            v1 = nor(0, t2);
            v0 = v0 & v1;
            v0 = v0 & a0;
            a2 = a3;
            if (v0 == 0) {
                for (;;) {
                    // 0x00524338
                    charge(ctx, 9);
                    sd(t2, a2, 0);
                    a1 = addiu(a1, 8);
                    ld(t2, a1, 0);
                    v0 = nor(0, t2);
                    v1 = t2 - t1;
                    v1 = v1 & v0;
                    v1 = v1 & a0;
                    a2 = addiu(a2, 8);
                    if (v1 != 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        L_0052435c:
            charge(ctx, 1);
            v1 = a2;
        } else {
            // 0x005242c0: quadword copy while the quadword holds no NUL (MMI)
            charge(ctx, 11);
            pcpyld(t2, t1, t1);
            lq(t1, a1, 0);
            pcpyld(t0, a0, a0);
            psubb(v0, t1, t2);
            pnor(v1, zero, t1);
            pand(v0, v0, v1);
            pand(v0, v0, t0);
            pcpyud(a0, v0, t1);
            v1 = v0 | a0;
            a2 = a3;
            if (v1 != 0) {
                goto L_0052435c;
            }
            for (;;) {
                // 0x005242ec
                charge(ctx, 11);
                sq(t1, a2, 0);
                a1 = addiu(a1, 16);
                lq(t1, a1, 0);
                psubb(v0, t1, t2);
                pnor(v1, zero, t1);
                pand(v0, v0, v1);
                pand(v0, v0, t0);
                pcpyud(a0, v0, t1);
                v1 = v0 | a0;
                a2 = addiu(a2, 16);
                if (v1 != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00524318
            charge(ctx, 2);
            v1 = a2;
        }
    }
    for (;;) {
        // 0x00524360: the bytes up to and including the NUL
        charge(ctx, 7);
        lbu(v0, a1, 0);
        a1 = addiu(a1, 1);
        sb(v0, v1, 0);
        v0 = sll(v0, 24);
        v1 = addiu(v1, 1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0052437c
    charge(ctx, 2);
    v0 = a3;
}

// 0x00524388 strlen -- 312 bytes; leaf frame (no stack)
// strlen(s $a0) -> $v0: the number of bytes before the NUL. 8-byte aligned strings are scanned a quadword (16-aligned,
// MMI) or a doubleword at a time with the has-zero-byte test; the final word and unaligned strings byte by byte.
void strlen(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00524388
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = a0 & 0x7;
    a3 = a0;
    if (v0 == 0) {
        // 0x00524394: 8-byte aligned: 16-byte aligned too?
        charge(ctx, 9);
        v1 = a0 & 0xF;
        v0 = 0x1010000;
        v0 = v0 | 0x101;  // &0x1010101
        v0 = dsll(v0, 16);
        v0 = v0 | 0x101;
        v0 = dsll(v0, 16);
        v0 = v0 | 0x101;
        a1 = a0;
        if (v1 != 0) {
            // 0x0052442c: doubleword scan: NUL in the first word?
            charge(ctx, 13);
            ld(v1, a1, 0);
            a0 = lui(0x8080);
            a0 = a0 | 0x8080;
            a0 = dsll(a0, 16);
            a0 = a0 | 0x8080;
            a0 = dsll(a0, 16);
            a0 = a0 | 0x8080;
            v0 = v1 - v0;
            v1 = nor(0, v1);
            v0 = v0 & v1;
            v0 = v0 & a0;
            if (v0 != 0) {
                a0 = a1;
            } else {
                // 0x00524460
                charge(ctx, 7);
                a2 = 0x1010000;
                a2 = a2 | 0x101;  // &0x1010101
                a2 = dsll(a2, 16);
                a2 = a2 | 0x101;
                a2 = dsll(a2, 16);
                a2 = a2 | 0x101;
                a1 = addiu(a1, 8);
                for (;;) {
                    // 0x0052447c: next doubleword
                    charge(ctx, 7);
                    ld(v0, a1, 0);
                    v1 = nor(0, v0);
                    v0 = v0 - a2;
                    v0 = v0 & v1;
                    v0 = v0 & a0;
                    if (v0 != 0) {
                        break;
                    }
                    a1 = addiu(a1, 8);
                    backedge(ctx);
                }
                // 0x00524498
                charge(ctx, 1);
                a0 = a1;
            }
        } else {
            // 0x005243b8: quadword scan: NUL in the first 16 bytes? (MMI)
            charge(ctx, 17);
            lq(v1, a1, 0);
            pcpyld(t0, v0, v0);
            a0 = lui(0x8080);
            a0 = a0 | 0x8080;
            a0 = dsll(a0, 16);
            a0 = a0 | 0x8080;
            a0 = dsll(a0, 16);
            a0 = a0 | 0x8080;
            psubb(v0, v1, t0);
            pnor(v1, zero, v1);
            pcpyld(t1, a0, a0);
            pand(v0, v0, v1);
            pand(v0, v0, t1);
            pcpyud(v1, v0, t0);
            a2 = v1 | v0;
            if (a2 != 0) {
                a0 = a1;
            } else {
                // 0x005243fc
                charge(ctx, 1);
                a1 = addiu(a1, 16);
                for (;;) {
                    // 0x00524400: next quadword
                    charge(ctx, 9);
                    lq(v0, a1, 0);
                    pnor(v1, zero, v0);
                    psubb(v0, v0, t0);
                    pand(v0, v0, v1);
                    pand(a0, v0, t1);
                    pcpyud(v1, a0, a2);
                    v1 = v1 | a0;
                    if (v1 != 0) {
                        break;
                    }
                    a1 = addiu(a1, 16);
                    backedge(ctx);
                }
                // 0x00524424
                charge(ctx, 2);
                a0 = a1;
            }
        }
    }
    for (;;) {
        // 0x0052449c: the byte scan of the last word
        charge(ctx, 7);
        lb(v0, a0, 0);
        if (v0 == 0) {
            break;
        }
        a0 = addiu(a0, 1);
        backedge(ctx);
    }
    // 0x005244b8: length = end - s
    charge(ctx, 2);
    v0 = subu(a0, a3);
}

// 0x005244C0 strncat -- 428 bytes; leaf frame (no stack)
// strncat(dst $a0, src $a1, n $a2) -> $v0 = dst: append at most n bytes of src to dst's NUL and always store a NUL
// after them (the word scans of strcat find dst's end).
void strncat(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    // 0x005244c0
    enter(ctx, 4);  // entry check point + this block's cycles
    t0 = a0;
    v0 = t0 & 0x7;
    if (v0 != 0) {
        lb(v0, a0, 0);
    } else {
        // 0x005244d0: dst 8-byte aligned: 16-byte aligned?
        charge(ctx, 3);
        v1 = t0 & 0xF;
        if (v1 != 0) {
            ld(v0, t0, 0);
            // 0x0052456c: doubleword scan for dst's NUL
            charge(ctx, 18);
            t1 = 0x1010000;
            t1 = t1 | 0x101;  // &0x1010101
            t1 = dsll(t1, 16);
            t1 = t1 | 0x101;
            t1 = dsll(t1, 16);
            t1 = t1 | 0x101;
            a0 = lui(0x8080);
            a0 = a0 | 0x8080;
            a0 = dsll(a0, 16);
            a0 = a0 | 0x8080;
            a0 = dsll(a0, 16);
            a0 = a0 | 0x8080;
            v1 = v0 - t1;
            v0 = nor(0, v0);
            v1 = v1 & v0;
            v1 = v1 & a0;
            a3 = t0;
            if (v1 == 0) {
                // 0x005245b4
                charge(ctx, 1);
                a3 = addiu(a3, 8);
                for (;;) {
                    // 0x005245b8
                    charge(ctx, 7);
                    ld(v0, a3, 0);
                    v1 = nor(0, v0);
                    v0 = v0 - t1;
                    v0 = v0 & v1;
                    v0 = v0 & a0;
                    if (v0 != 0) {
                        break;
                    }
                    a3 = addiu(a3, 8);
                    backedge(ctx);
                }
            }
        } else {
            // 0x005244dc: quadword scan for dst's NUL (MMI)
            charge(ctx, 23);
            a3 = 0x1010000;
            a3 = a3 | 0x101;  // &0x1010101
            a3 = dsll(a3, 16);
            a3 = a3 | 0x101;
            a3 = dsll(a3, 16);
            a3 = a3 | 0x101;
            lq(v0, t0, 0);
            pcpyld(t1, a3, a3);
            a0 = lui(0x8080);
            a0 = a0 | 0x8080;
            a0 = dsll(a0, 16);
            a0 = a0 | 0x8080;
            a0 = dsll(a0, 16);
            a0 = a0 | 0x8080;
            psubb(v1, v0, t1);
            pnor(v0, zero, v0);
            pcpyld(t2, a0, a0);
            pand(v1, v1, v0);
            pand(v1, v1, t2);
            pcpyud(v0, v1, a0);
            v1 = v1 | v0;
            a3 = t0;
            if (v1 == 0) {
                // 0x00524538
                charge(ctx, 2);
                a3 = addiu(a3, 16);
                for (;;) {
                    // 0x00524540
                    charge(ctx, 9);
                    lq(v0, a3, 0);
                    pnor(v1, zero, v0);
                    psubb(v0, v0, t1);
                    pand(v0, v0, v1);
                    pand(v0, v0, t2);
                    pcpyud(v1, v0, a0);
                    v0 = v0 | v1;
                    a3 = addiu(a3, 16);
                    if (v0 != 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00524564
                charge(ctx, 2);
                a3 = addiu(a3, -16);
            }
        }
        // 0x005245d4
        charge(ctx, 2);
        a0 = a3;
        lb(v0, a0, 0);
    }
    // 0x005245dc
    charge(ctx, 2);
    a2 = addiu(a2, -1);
    if (v0 != 0) {
        // 0x005245e4
        charge(ctx, 1);
        a0 = addiu(a0, 1);
        for (;;) {
            // 0x005245e8: the byte scan to the NUL
            charge(ctx, 7);
            lb(v0, a0, 0);
            if (v0 == 0) {
                break;
            }
            a0 = addiu(a0, 1);
            backedge(ctx);
        }
    }
    // 0x00524604: n == 0: nothing appended
    charge(ctx, 4);
    v0 = lui(0xFFFF);
    v0 = v0 | 0xFFFF;
    if (a2 != v0) {
        // 0x00524614: copy the first byte of src
        charge(ctx, 6);
        lbu(v0, a1, 0);
        a1 = addiu(a1, 1);
        sb(v0, a0, 0);
        v0 = sll(v0, 24);
        a0 = addiu(a0, 1);
        if (v0 != 0) {
            // 0x0052462c
            charge(ctx, 3);
            v1 = lui(0xFFFF);
            v1 = v1 | 0xFFFF;
            for (;;) {
                // 0x00524638: count exhausted: terminate
                charge(ctx, 2);
                if (a2 == 0) {
                    sb(zero, a0, 0);
                }
                // 0x00524640
                charge(ctx, 3);
                a2 = addiu(a2, -1);
                if (a2 != v1) {
                    // 0x0052464c: next byte of src
                    charge(ctx, 6);
                    lbu(v0, a1, 0);
                    a1 = addiu(a1, 1);
                    sb(v0, a0, 0);
                    v0 = sll(v0, 24);
                    a0 = addiu(a0, 1);
                    if (v0 != 0) {
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
        }
    }
    // 0x00524664 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = t0;
}

// 0x00524828 strncpy -- 444 bytes; leaf frame (no stack)
// strncpy(dst $a0, src $a1, n $a2) -> $v0 = dst: copy at most n bytes of src; when src is shorter than n, pad with
// NULs up to n (no NUL is added when src has n or more bytes). Aligned blocks of 8 / 16 bytes are copied whole while
// they hold no NUL and n allows.
void strncpy(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00524828
    enter(ctx, 7);  // entry check point + this block's cycles
    t0 = a0;
    a3 = a1 | a0;
    t2 = 16;
    v0 = a3 & 0x7;
    t1 = 8;
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = a3 & 0xF;
    if (!cc) {
        // 0x00524844: aligned: block size 16 or 8; n >= block?
        charge(ctx, 3);
        if (v0 == 0) t1 = t2;
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = sltu(a2, t1);
        if (cc) {
            // 0x005248fc
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x00524904: doubleword path: no NUL in the source word?
                charge(ctx, 19);
                ld(v1, a1, 0);
                t1 = 0x1010000;
                t1 = t1 | 0x101;  // &0x1010101
                t1 = dsll(t1, 16);
                t1 = t1 | 0x101;
                t1 = dsll(t1, 16);
                t1 = t1 | 0x101;
                t2 = lui(0x8080);
                t2 = t2 | 0x8080;
                t2 = dsll(t2, 16);
                t2 = t2 | 0x8080;
                t2 = dsll(t2, 16);
                t2 = t2 | 0x8080;
                v0 = v1 - t1;
                v1 = nor(0, v1);
                v0 = v0 & v1;
                v0 = v0 & t2;
                a3 = t0;
                if (v0 == 0) {
                    // 0x00524950
                    charge(ctx, 2);
                    ld(v1, a1, 0);
                    for (;;) {
                    L_00524958:
                        charge(ctx, 6);
                        a2 = addiu(a2, -8);
                        a1 = addiu(a1, 8);
                        v0 = sltiu(a2, 8);
                        sd(v1, a3, 0);
                        a3 = addiu(a3, 8);
                        if (v0 == 0) {
                            // 0x00524970: next source doubleword: NUL?
                            charge(ctx, 7);
                            ld(v0, a1, 0);
                            v1 = nor(0, v0);
                            v0 = v0 - t1;
                            v0 = v0 & v1;
                            v0 = v0 & t2;
                            if (v0 == 0) {
                                ld(v1, a1, 0);
                                backedge(ctx);
                                continue;
                            }
                        }
                        break;
                    }
                }
            L_0052498c:
                charge(ctx, 1);
                a0 = a3;
            }
        } else {
            // 0x00524850
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x00524858: quadword path: no NUL in the first 16 source bytes?
                charge(ctx, 23);
                a3 = 0x1010000;
                a3 = a3 | 0x101;  // &0x1010101
                a3 = dsll(a3, 16);
                a3 = a3 | 0x101;
                a3 = dsll(a3, 16);
                a3 = a3 | 0x101;
                lq(v1, a1, 0);
                pcpyld(t1, a3, a3);
                pnor(v1, zero, v1);
                a3 = lui(0x8080);
                a3 = a3 | 0x8080;
                a3 = dsll(a3, 16);
                a3 = a3 | 0x8080;
                a3 = dsll(a3, 16);
                a3 = a3 | 0x8080;
                psubb(v0, v1, t1);
                pcpyld(t2, a3, a3);
                pand(v0, v0, v1);
                pand(v0, v0, t2);
                pcpyud(v1, v0, a0);
                v1 = v0 | v1;
                a3 = t0;
                if (v1 != 0) {
                    goto L_0052498c;
                }
                // 0x005248b4: copy the quadword
                charge(ctx, 7);
                lq(v1, a1, 0);
                a2 = addiu(a2, -16);
                a1 = addiu(a1, 16);
                v0 = sltiu(a2, 16);
                sq(v1, a3, 0);
                a3 = addiu(a3, 16);
                if (v0 != 0) {
                    goto L_0052498c;
                }
                // 0x005248d0: next source quadword: NUL? (then the doubleword loop)
                charge(ctx, 9);
                lq(v0, a1, 0);
                pnor(v1, zero, v0);
                psubb(v0, v0, t1);
                pand(v0, v0, v1);
                pand(v0, v0, t2);
                pcpyud(v1, v0, a0);
                v0 = v0 | v1;
                if (v0 == 0) {
                    lq(v1, a1, 0);
                    goto L_00524958;
                }
                // 0x005248f4
                charge(ctx, 2);
                a0 = a3;
            }
        }
    }
    for (;;) {
        // 0x00524990: the byte copy while n > 0
        charge(ctx, 2);
        v0 = a2;
        if (a2 == 0) {
            break;
        }
        // 0x00524998: one byte; stop at the NUL
        charge(ctx, 7);
        lbu(v0, a1, 0);
        a2 = addiu(a2, -1);
        a1 = addiu(a1, 1);
        sb(v0, a0, 0);
        v0 = sll(v0, 24);
        a0 = addiu(a0, 1);
        if (v0 == 0) {
            goto L_005249b4_15;
        }
        backedge(ctx);
    }
    // 0x005249dc (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = t0;
    return;
L_005249b4_15:
    charge(ctx, 3);
    v0 = a2;
    a2 = addiu(a2, -1);
    if (v0 != 0) {
        for (;;) {
            // 0x005249c0: pad with NULs up to n
            charge(ctx, 7);
            sb(zero, a0, 0);
            v0 = a2;
            a0 = addiu(a0, 1);
            a2 = addiu(a2, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x005249dc (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = t0;
}

// 0x005249E8 strrchr -- 100 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// strrchr(s $a0, c $a1) -> $v0: the last occurrence of (char)c in s (NUL included), else NULL: repeated strchr calls
// from the byte after each hit; c == 0 is a single strchr.
void strrchr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005249e8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a0;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s0 = a1;
    s1 = 0;
    if (a1 == 0) {
        // 0x00524a3c: c == 0: strchr finds the terminator
        charge(ctx, 4);
        jal(ctx, 0x524A3Cu, gen::fn_strchr_00523f98);
        s1 = v0;
        backedge(ctx);
    } else {
        for (;;) {
            // 0x00524a08: strchr from the current position
            charge(ctx, 5);
            a0 = v0;
            a1 = s0;
            jal(ctx, 0x524A0Cu, gen::fn_strchr_00523f98);
            if (v0 == 0) {
                break;
            }
            s1 = v0;
            // 0x00524a34: remember the hit; continue after it
            charge(ctx, 2);
            v0 = addiu(v0, 1);
            backedge(ctx);
        }
    }
    // 0x00524a1c: return the last hit (NULL when none) (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00524A50 strstr -- 84 bytes; leaf frame (no stack)
// strstr(hay $a0, needle $a1) -> $v0: the first position where needle occurs in hay; an empty needle returns hay; NULL
// when absent (naive restart one byte later on a mismatch).
void strstr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    // 0x00524a50
    enter(ctx, 3);  // entry check point + this block's cycles
    lb(t7, a0, 0);
    v0 = a0;
    if (t7 == 0) {
        // 0x00524a5c: empty hay: hay when the needle is empty too, else NULL
        charge(ctx, 3);
        lb(t7, a1, 0);
        if (t7 != 0) v0 = 0;
        return;
    }
    // 0x00524a68
    charge(ctx, 1);
    t4 = 0;
    for (;;) {
        // 0x00524a6c: needle[i] == 0: found at v0
        charge(ctx, 4);
        t7 = addu(a1, t4);
        lb(t5, t7, 0);
        t6 = addu(v0, t4);
        if (t5 == 0) {
            break;
        }
        // 0x00524a7c: hay[v0 + i] == needle[i]: next i
        charge(ctx, 3);
        lb(t7, t6, 0);
        t4 = addiu(t4, 1);
        if (t5 == t7) {
            backedge(ctx);
            continue;
        }
        // 0x00524a88: mismatch: next start position (end of hay: NULL)
        charge(ctx, 4);
        v0 = addiu(v0, 1);
        lb(t7, v0, 0);
        if (t7 == 0) {
            goto L_00524a98_6;
        }
        t4 = 0;
        backedge(ctx);
    }
    // 0x00524a9c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_00524a98_6:
    charge(ctx, 1);
    v0 = 0;
    // 0x00524a9c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00525958 strtok -- 184 bytes; frame 0x10: ra sp+0x0
// strtok(s $a0, delim $a1) -> $v0: the next token of s (s == NULL: continue from the saved position, the _reent word
// at +0x5C of *(0x782F30)). Skips leading delimiters; NULL when only delimiters remain; otherwise NUL-terminates the
// token in place and saves the byte after it (NULL at the end of the string).
void strtok(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00525958
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t7 = 0x780000;
    sd(ra, sp, 0x0);
    lw(a2, t7, 12080);  // 0x782F30
    ld(ra, sp, 0x0);
    a2 = addiu(a2, reent::kStrtokLast);  // &_impure_ptr->strtok_last
    sp = addiu(sp, 0x10);
    // 0x00525978: s == NULL: continue from the saved position
    charge(ctx, 2);
    if (a0 != 0) {
        lb(t5, a0, 0);
    } else {
        // 0x00525980: the saved position (NULL: no more tokens)
        charge(ctx, 3);
        lw(a0, a2, 0);
        v0 = 0;
        if (a0 == 0) {
            // 0x00525a08
            charge(ctx, 2);
            return;
        }
        // 0x0052598c
        charge(ctx, 1);
        lb(t5, a0, 0);
        goto L_00525990;
    }
    for (;;) {
    L_00525990:
        charge(ctx, 4);
        t6 = addiu(a1, 1);
        lb(t7, a1, 0);
        a0 = addiu(a0, 1);
        if (t7 != 0) {
            for (;;) {
                // 0x005259a0: skip leading delimiters: byte in delim?
                charge(ctx, 2);
                if (t5 == t7) {
                    lb(t5, a0, 0);
                    backedge(ctx);
                    goto L_00525990;
                }
                // 0x005259a8: next delimiter
                charge(ctx, 3);
                lb(t7, t6, 0);
                t6 = addiu(t6, 1);
                if (t7 != 0) {
                    backedge(ctx);
                    continue;
                }
                break;
            }
        }
        break;
    }
    // 0x005259b4
    charge(ctx, 2);
    if (t5 == 0) {
        // 0x005259bc: only delimiters left: clear the saved position, NULL
        charge(ctx, 3);
        sw(zero, a2, 0);
        v0 = 0;
        return;
    }
    v0 = addiu(a0, -1);
    // 0x005259c8: the token starts here: scan for its end
    charge(ctx, 1);
    lb(t5, a0, 0);
    for (;;) {
    L_005259cc:
        charge(ctx, 3);
        t6 = a1;
        a0 = addiu(a0, 1);
        lb(t7, t6, 0);
        for (;;) {
            // 0x005259d8: byte == delimiter?
            charge(ctx, 2);
            t6 = addiu(t6, 1);
            if (t7 == t5) {
                break;
            }
            // 0x005259f8: end of delim: the byte belongs to the token
            charge(ctx, 2);
            if (t7 == 0) {
                goto L_00525a00_16;
            }
            lb(t7, t6, 0);
            backedge(ctx);
        }
        break;
    }
    // 0x005259e0: a delimiter: NUL it (the next scan starts after it); the string's end: no next position
    charge(ctx, 2);
    if (t7 != 0) {
        sb(zero, a0, -1);
    } else {
        // 0x005259e8
        charge(ctx, 1);
        a0 = 0;
    }
    // 0x005259ec: save the next position (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sw(a0, a2, 0);
    return;
L_00525a00_16:
    charge(ctx, 2);
    lb(t5, a0, 0);
    backedge(ctx);
    goto L_005259cc;
}

// 0x005287D8 __sccl -- 236 bytes; leaf frame (no stack)
// __sccl(tab $a0, fmt $a1) -> $v0: scanf's %[...] scanset builder: fmt points after the '['; a leading '^' inverts.
// Fills the 256-byte tab with the 'not in set' value, marks each listed byte and each a-b range (a '-' before ']' or
// before a smaller byte is literal), stops at ']' (returns the byte after it) or at the end of fmt (returns fmt's
// NUL).
void __sccl(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005287d8
    enter(ctx, 4);  // entry check point + this block's cycles
    lb(t5, a1, 0);
    t7 = 94;
    a1 = addiu(a1, 1);
    if (t5 != t7) {
        // 0x005288bc: no '^': marked bytes are "in the set" (1)
        charge(ctx, 2);
        t3 = 0;
        backedge(ctx);
    } else {
        // 0x005287e8: '^': inverted set
        charge(ctx, 3);
        lb(t5, a1, 0);
        t3 = 1;
        a1 = addiu(a1, 1);
    }
    // 0x005287f4
    charge(ctx, 2);
    t6 = 0;
    t7 = addu(a0, t6);
    for (;;) {
        // 0x005287fc: fill all 256 entries with the "not marked" value
        charge(ctx, 7);
        sb(t3, t7, 0);
        t6 = addiu(t6, 1);
        t7 = slti(t6, 256);
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = addu(a0, t6);
        if (!cc) {
            break;
        }
        backedge(ctx);
    }
    // 0x00528818
    charge(ctx, 2);
    v0 = addiu(a1, -1);
    if (t5 != 0) {
        // 0x00528820: mark value = 1 - fill value; '-' and ']' constants
        charge(ctx, 5);
        t7 = 1;
        t1 = 45;
        t3 = subu(t7, t3);
        t0 = 93;
        t2 = 93;
        for (;;) {
        L_00528834:
            charge(ctx, 3);
            t7 = addu(a0, t5);
            sb(t3, t7, 0);
            lb(t4, a1, 0);
            for (;;) {
                // 0x00528840
                charge(ctx, 2);
                a1 = addiu(a1, 1);
                if (t4 != t1) {
                    break;
                }
                // 0x0052887c: a '-': literal before ']' or a smaller byte, else a range
                charge(ctx, 3);
                lb(t4, a1, 0);
                t7 = slt(t4, t5);
                if (t4 == t2) {
                    goto L_00528890;
                }
                // 0x00528888
                charge(ctx, 2);
                if (t7 != 0) {
                    goto L_00528890;
                }
                a1 = addiu(a1, 1);
                for (;;) {
                    // 0x00528898
                    charge(ctx, 7);
                    t5 = addiu(t5, 1);
                    t7 = addu(a0, t5);
                    t6 = slt(t5, t4);
                    sb(t3, t7, 0);
                    if (t6 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x005288b4
                charge(ctx, 2);
                lb(t4, a1, 0);
                backedge(ctx);
            }
            // 0x00528848
            charge(ctx, 3);
            t7 = slti(t4, 46);
            if (t7 == 0) {
                // 0x0052886c
                charge(ctx, 2);
                v0 = a1;
                if (t4 != t0) {
                    // 0x00528874
                    charge(ctx, 2);
                    t5 = t4;
                    backedge(ctx);
                    continue;
                }
                backedge(ctx);
            } else {
                // 0x00528854
                charge(ctx, 2);
                v0 = addiu(a1, -1);
                if (t4 != 0) {
                    // 0x0052885c
                    charge(ctx, 2);
                    t5 = t4;
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x00528864 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_00528890:
    charge(ctx, 2);
    t5 = 45;
    backedge(ctx);
    goto L_00528834;
}

}  // namespace p3fes::game
