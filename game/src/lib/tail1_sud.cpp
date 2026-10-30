// Slice tail1: CRI SUD (the Sofdec utility module): the <SUDPS_> tag and the time base.
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions only (no CRI material was
// opened). Pair tests: tests/game/test_tail1.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/tail1.h"

namespace p3fes::recomp_gen {
void fn___divdi3_0052eeb0(p3fes::EEContext&);
void fn_atoi_0051e0f0(p3fes::EEContext&);
void fn_memcmp_005211b8(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_23_005a1158(p3fes::EEContext&);
void fn_strncpy_00524828(p3fes::EEContext&);
void fn_sub_5A1218_005a1218(p3fes::EEContext&);
void fn_sub_5A12F8_005a12f8(p3fes::EEContext&);
void fn_sub_5A1790_005a1790(p3fes::EEContext&);
void fn_sub_5A1858_005a1858(p3fes::EEContext&);
void fn_sub_5A1B58_005a1b58(p3fes::EEContext&);
void fn_sub_5A1B68_005a1b68(p3fes::EEContext&);
void fn_sub_5A1B80_005a1b80(p3fes::EEContext&);
void fn_sub_5A1C08_005a1c08(p3fes::EEContext&);
void fn_sub_5A1CE0_005a1ce0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace tail1;  // the named offsets of p3fes/game/tail1.h
namespace gen = ::p3fes::recomp_gen;

// 0x005A1158 sceLibgcc32GetErxEntries_23 -- 12 bytes; leaf frame (no stack)
// [sudGetVersionStr] Returns the module's version banner string in $v0 (the 12-byte "return a constant address" shape).
// The FLIRT name is a false match (the same few instructions as the SDK function; this is CRI code). SUD: "CRI
// SUD/PS2EE Ver.0.05".
void sceLibgcc32GetErxEntries_23(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005a1158
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7D0000;
    v0 = addiu(v0, -21648);  // "\nCRI SUD/PS2EE Ver.0.05 Build:Mar  1 2005 10:54:11\n"
}

// 0x005A1218 sub_5A1218 -- 224 bytes; frame 0x60: s0 sp+0x30, s1 sp+0x38, s2 sp+0x40, s3 sp+0x48, ra sp+0x50
// [sudPutTagChars] Writes three characters at p+2..p+4 of a SUD tag: each the first character of a string picked by
// idx[0..2] from the three two-entry string tables 0x7CABE0 / 0x7CABF8 / 0x7CAC10 (copied to the stack; strncpy of one
// byte).
void sub_5A1218(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a1218
    enter(ctx, 56);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v1 = 0x7D0000;
    sd(s0, sp, 0x30);
    s0 = a0;
    sd(s1, sp, 0x38);
    s1 = addiu(sp, 0x10);
    sd(s2, sp, 0x40);
    s2 = addiu(sp, 0x20);
    sd(s3, sp, 0x48);
    s3 = a1;
    sd(ra, sp, 0x50);
    a1 = 0x7D0000;
    t2 = addiu(v1, -21536);  // &0x7CABE0
    ldl(a3, t2, 7);  // 0x7CABE7
    ldr(a3, t2, 0);  // 0x7CABE0
    sdl(a3, sp, 0x7);
    sdr(a3, sp, 0x0);
    a2 = 0x7D0000;
    t1 = addiu(a1, -21512);  // &0x7CABF8
    ldl(v1, t1, 7);  // 0x7CABFF
    ldr(v1, t1, 0);  // 0x7CABF8
    sdl(v1, s1, 7);
    sdr(v1, s1, 0);
    a0 = addiu(s0, 2);
    lw(v0, s3, 0);
    a3 = addiu(a2, -21488);  // &0x7CAC10
    ldl(t2, a3, 7);  // 0x7CAC17
    ldr(t2, a3, 0);  // 0x7CAC10
    sdl(t2, s2, 7);
    sdr(t2, s2, 0);
    a2 = 1;
    v0 = sll(v0, 2);
    v1 = addu(sp, v0);
    link(ctx, 0x5A129Cu);  // $ra first: the delay slot below depends on it
    lw(a1, v1, 0);
    call(ctx, gen::fn_strncpy_00524828);
    lw(v1, s3, 4);
    a0 = addiu(s0, 3);
    a2 = 1;
    v1 = sll(v1, 2);
    s1 = addu(s1, v1);
    link(ctx, 0x5A12B8u);  // $ra first: the delay slot below depends on it
    lw(a1, s1, 0);
    call(ctx, gen::fn_strncpy_00524828);
    lw(v1, s3, 8);
    a0 = addiu(s0, 4);
    a2 = 1;
    v1 = sll(v1, 2);
    s2 = addu(s2, v1);
    link(ctx, 0x5A12D4u);  // $ra first: the delay slot below depends on it
    lw(a1, s2, 0);
    call(ctx, gen::fn_strncpy_00524828);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(ra, sp, 0x50);
    sp = addiu(sp, 0x60);
}

// 0x005A12F8 sub_5A12F8 -- 68 bytes; frame 0x20: ra sp+0x10
// [sudTagNumber] The two-digit number at tag +16 / +17 (atoi of a two-character copy), or 0 for a null tag or a
// negative length. The copy at sp+0 / sp+1 has no terminator: atoi reads on into whatever the stack holds at sp+2
// (test_tail1 shows a digit there becoming a third digit).
void sub_5A12F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a12f8
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a0;
    sd(ra, sp, 0x10);
    if (v0 != 0) {
        // 0x005a1308
        charge(ctx, 2);
        if (i64(a1) < 0) {
            goto L_005a1310;
        }
        // 0x005a1318
        charge(ctx, 6);
        lb(v1, v0, 16);
        lb(a1, v0, 17);
        sb(v1, sp, 0x0);
        sb(a1, sp, 0x1);
        a0 = sp;
        jal(ctx, 0x5A1328u, gen::fn_atoi_0051e0f0);
        // 0x005a1330 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_005a1310:
    charge(ctx, 2);
    v0 = 0;
    // 0x005a1330 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005A1790 sub_5A1790 -- 200 bytes; frame 0x40: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s1 sp+0x8, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// [sudFindTag] Scans (buf, len) for a "<SUDPS_>" tag (a '<' first, then the 8-byte compare); *tag / *taglen = its
// address and 35 (the last one found), or 0 / 0.
void sub_5A1790(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a1790
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = a3;
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(s1, sp, 0x8);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x30);
    sw(zero, s2, 0);
    sw(zero, s3, 0);
    if (s0 != 0) {
        // 0x005a17c8
        charge(ctx, 2);
        if (i64(a1) <= 0) {
            ld(s0, sp, 0x0);
        } else {
            // 0x005a17d0
            charge(ctx, 2);
            if (i64(a1) > 0) {
                // 0x005a17d8
                charge(ctx, 4);
                s1 = a1;
                s5 = 0x7D0000;
                s4 = 0x7D0000;
                for (;;) {
                    // 0x005a17e8
                    charge(ctx, 8);
                    a0 = s0;
                    a1 = addiu(s5, -21480);
                    a2 = 1;
                    jal(ctx, 0x5A17F0u, gen::fn_memcmp_005211b8);
                    a0 = s0;
                    a1 = addiu(s4, -21592);
                    a2 = 8;
                    if (v0 == 0) {
                        // 0x005a1808
                        charge(ctx, 4);
                        jal(ctx, 0x5A1808u, gen::fn_memcmp_005211b8);
                        if (v0 == 0) {
                            // 0x005a1818
                            charge(ctx, 4);
                            sw(s0, s3, 0);
                            a0 = s0;
                            jal(ctx, 0x5A181Cu, gen::fn_sub_5A1858_005a1858);
                            sw(v0, s2, 0);
                            goto L_005a1828;
                        }
                        s1 = addiu(s1, -1);
                        goto L_005a182c;
                    }
                L_005a1828:
                    charge(ctx, 1);
                    s1 = addiu(s1, -1);
                L_005a182c:
                    charge(ctx, 2);
                    s0 = addiu(s0, 1);
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                goto L_005a1834;
            }
            ld(s0, sp, 0x0);
        }
        // 0x005a1838 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        return;
    }
L_005a1834:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x005a1838 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x005A1858 sub_5A1858 -- 12 bytes; leaf frame (no stack)
// [sudTagLength] The length of a SUD tag: 35, or 0 for a null pointer.
void sub_5A1858(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005a1858
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 35;
    if (a0 == 0) v0 = 0;
}

// 0x005A1B58 sub_5A1B58 -- 16 bytes; leaf frame (no stack)
// [sudTimeBaseIsUnset] True when the time base (u64 0x7B5060) is below 2.
void sub_5A1B58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x005a1b58
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    ld(v0, v1, 20576);  // 0x7B5060
    v0 = sltiu(v0, 2);
}

// 0x005A1B68 sub_5A1B68 -- 20 bytes; frame 0x10: ra sp+0x0
// [sudSetTimeBase2] Sets the time base (tail call to sub_5A1CE0).
void sub_5A1B68(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005a1b68
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5A1CE0_005a1ce0(ctx);  // tail call
}

// 0x005A1B80 sub_5A1B80 -- 12 bytes; leaf frame (no stack)
// [sudGetTimeBase] Returns the time base (u64 0x7B5060).
void sub_5A1B80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x005a1b80
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    ld(v0, v1, 20576);  // 0x7B5060
}

// 0x005A1C08 sub_5A1C08 -- 36 bytes; frame 0x10: ra sp+0x0
// [sudDivTimeBase] Converts a count to time units: a0 / time base (__divdi3, 64-bit).
void sub_5A1C08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a1c08
    enter(ctx, 9);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    ld(a1, v0, 20576);  // 0x7B5060
    sd(ra, sp, 0x0);
    jal(ctx, 0x5A1C18u, gen::fn___divdi3_0052eeb0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005A1CE0 sub_5A1CE0 -- 12 bytes; leaf frame (no stack)
// [sudSetTimeBase] Sets the time base (u64 0x7B5060); returns 0x7B0000 -- what the lui of the address left in $v0.
void sub_5A1CE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005a1ce0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sd(a0, v0, 20576);  // 0x7B5060
}

}  // namespace p3fes::game
