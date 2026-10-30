// Slice tail1: CRI SFH (the Sofdec stream header parser) and the SFX handle pool.
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions only (no CRI material was
// opened). Pair tests: tests/game/test_tail1.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/tail1.h"

namespace p3fes::recomp_gen {
void fn_memcmp_005211b8(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_21_0059cfa0(p3fes::EEContext&);
void fn_strstr_00524a50(p3fes::EEContext&);
void fn_sub_59CFB0_0059cfb0(p3fes::EEContext&);
void fn_sub_59CFC0_0059cfc0(p3fes::EEContext&);
void fn_sub_59D050_0059d050(p3fes::EEContext&);
void fn_sub_59D098_0059d098(p3fes::EEContext&);
void fn_sub_59D160_0059d160(p3fes::EEContext&);
void fn_sub_59D1B0_0059d1b0(p3fes::EEContext&);
void fn_sub_59D1C8_0059d1c8(p3fes::EEContext&);
void fn_sub_59D1E0_0059d1e0(p3fes::EEContext&);
void fn_sub_59D230_0059d230(p3fes::EEContext&);
void fn_sub_59D240_0059d240(p3fes::EEContext&);
void fn_sub_59D288_0059d288(p3fes::EEContext&);
void fn_sub_59D2B0_0059d2b0(p3fes::EEContext&);
void fn_sub_59D3A0_0059d3a0(p3fes::EEContext&);
void fn_sub_59D410_0059d410(p3fes::EEContext&);
void fn_sub_59D4E0_0059d4e0(p3fes::EEContext&);
void fn_sub_59D528_0059d528(p3fes::EEContext&);
void fn_sub_59D598_0059d598(p3fes::EEContext&);
void fn_sub_59D608_0059d608(p3fes::EEContext&);
void fn_sub_59D6A0_0059d6a0(p3fes::EEContext&);
void fn_sub_59D770_0059d770(p3fes::EEContext&);
void fn_sub_59D848_0059d848(p3fes::EEContext&);
void fn_sub_59D898_0059d898(p3fes::EEContext&);
void fn_sub_59D8E8_0059d8e8(p3fes::EEContext&);
void fn_sub_59D938_0059d938(p3fes::EEContext&);
void fn_sub_59D988_0059d988(p3fes::EEContext&);
void fn_sub_59D9E8_0059d9e8(p3fes::EEContext&);
void fn_sub_59DA70_0059da70(p3fes::EEContext&);
void fn_sub_59DAC0_0059dac0(p3fes::EEContext&);
void fn_sub_59DB10_0059db10(p3fes::EEContext&);
void fn_sub_59DB60_0059db60(p3fes::EEContext&);
void fn_sub_59DBB0_0059dbb0(p3fes::EEContext&);
void fn_sub_59DC18_0059dc18(p3fes::EEContext&);
void fn_sub_59DC68_0059dc68(p3fes::EEContext&);
void fn_sub_59DCB8_0059dcb8(p3fes::EEContext&);
void fn_sub_59DD08_0059dd08(p3fes::EEContext&);
void fn_sub_59DD40_0059dd40(p3fes::EEContext&);
void fn_sub_59DD78_0059dd78(p3fes::EEContext&);
void fn_sub_59DDF0_0059ddf0(p3fes::EEContext&);
void fn_sub_59DE68_0059de68(p3fes::EEContext&);
void fn_sub_59DEC0_0059dec0(p3fes::EEContext&);
void fn_sub_59DF30_0059df30(p3fes::EEContext&);
void fn_sub_59DFB0_0059dfb0(p3fes::EEContext&);
void fn_sub_59E020_0059e020(p3fes::EEContext&);
void fn_sub_59E090_0059e090(p3fes::EEContext&);
void fn_sub_59E100_0059e100(p3fes::EEContext&);
void fn_sub_59E178_0059e178(p3fes::EEContext&);
void fn_sub_59E228_0059e228(p3fes::EEContext&);
void fn_sub_59E298_0059e298(p3fes::EEContext&);
void fn_sub_59E308_0059e308(p3fes::EEContext&);
void fn_sub_59E378_0059e378(p3fes::EEContext&);
void fn_sub_59E3E8_0059e3e8(p3fes::EEContext&);
void fn_sub_59E460_0059e460(p3fes::EEContext&);
void fn_sub_59E4D0_0059e4d0(p3fes::EEContext&);
void fn_sub_59E558_0059e558(p3fes::EEContext&);
void fn_sub_59E5E0_0059e5e0(p3fes::EEContext&);
void fn_sub_59E670_0059e670(p3fes::EEContext&);
void fn_sub_59E6E0_0059e6e0(p3fes::EEContext&);
void fn_sub_59E720_0059e720(p3fes::EEContext&);
void fn_sub_59E760_0059e760(p3fes::EEContext&);
void fn_sub_59E7A8_0059e7a8(p3fes::EEContext&);
void fn_sub_59E800_0059e800(p3fes::EEContext&);
void fn_sub_59E808_0059e808(p3fes::EEContext&);
void fn_sub_59E860_0059e860(p3fes::EEContext&);
void fn_sub_59E8B0_0059e8b0(p3fes::EEContext&);
void fn_sub_59E8F0_0059e8f0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace tail1;  // the named offsets of p3fes/game/tail1.h
namespace gen = ::p3fes::recomp_gen;

// 0x0059CFA0 sceLibgcc32GetErxEntries_21 -- 12 bytes; leaf frame (no stack)
// [sfhGetVersionStr] Returns the module's version banner string in $v0 (the 12-byte "return a constant address" shape).
// The FLIRT name is a false match (the same few instructions as the SDK function; this is CRI code). SFH: "CRI
// SFH/PS2EE Ver.1.19".
void sceLibgcc32GetErxEntries_21(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059cfa0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7D0000;
    v0 = addiu(v0, -23152);  // "\nCRI SFH/PS2EE Ver.1.19 Build:Mar  1 2005 10:54:03\n"
}

// 0x0059CFB0 sub_59CFB0 -- 12 bytes; leaf frame (no stack)
// [sfhIsState2] True when a0 == 2 (a view state test; no caller in the ELF).
void sub_59CFB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0059cfb0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = a0 ^ 0x2;
    v0 = sltiu(v0, 1);
}

// 0x0059CFC0 sub_59CFC0 -- 160 bytes, 2 chunks; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// [sfhInit] SFH init (count, views): only the first init does the work: banner stored, every view cleared, the pool =
// {count, 0 used, views}. Two chunks (the tail at 0x59D1A0).
void sub_59CFC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059cfc0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x9B0000;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s0, sp, 0x0);
    a0 = addiu(v0, -13340);  // &0x9ACBE4
    sd(ra, sp, 0x18);
    lw(v0, a0, 0);  // 0x9ACBE4
    v1 = addiu(v0, 1);
    if (i64(v0) > 0) {
        // 0x0059d038
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059cff0
    charge(ctx, 18);
    sw(v1, a0, 0);
    s0 = 0x9B0000;
    s0 = addiu(s0, -13360);  // &0x9ACBD0
    jal(ctx, 0x59CFF8u, gen::fn_sceLibgcc32GetErxEntries_21_0059cfa0);
    a0 = s2;
    sw(v0, s0, 0);  // 0x9ACBD0
    a1 = s1;
    jal(ctx, 0x59D008u, gen::fn_sub_59D1E0_0059d1e0);
    a0 = 0x9B0000;
    a1 = s2;
    ld(s2, sp, 0x10);
    a2 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    a0 = addiu(a0, -13352);  // &0x9ACBD8
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    // 0x0059d1a0
    charge(ctx, 4);
    sw(a2, a0, 8);
    sw(a1, a0, 0);
    sw(zero, a0, 4);
}

// 0x0059D050 sub_59D050 -- 84 bytes, 2 chunks; frame 0x10: ra sp+0x0
// [sfhFinish] SFH finish: the last finish clears the pool.
void sub_59D050(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059d050
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x9B0000;
    sd(ra, sp, 0x0);
    v1 = addiu(v1, -13340);  // &0x9ACBE4
    lw(v0, v1, 0);  // 0x9ACBE4
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x9ACBE4
    if (i64(v0) > 0) {
        // 0x0059d088
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0059d070
    charge(ctx, 5);
    a0 = 0x9B0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, -13352);  // &0x9ACBD8
    sp = addiu(sp, 0x10);
    // 0x0059d190
    charge(ctx, 4);
    sw(zero, a0, 8);
    sw(zero, a0, 0);
    sw(zero, a0, 4);
}

// 0x0059D098 sub_59D098 -- 200 bytes; frame 0x40: s2 sp+0x10, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, ra sp+0x38
// [sfhCreateView] SFH take a view for (buf, size): the first free view (state 0), set taken with the buffer; 0 when
// every view is in use (used >= count).
void sub_59D098(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059d098
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0;
    sd(s2, sp, 0x10);
    s2 = 0;
    sd(s4, sp, 0x20);
    s4 = a1;
    sd(s5, sp, 0x28);
    s5 = a0;
    sd(s6, sp, 0x30);
    s6 = 0x9B0000;
    sd(s0, sp, 0x0);
    a0 = addiu(s6, -13352);  // &0x9ACBD8
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x38);
    lw(s1, a0, 0);  // 0x9ACBD8
    lw(v1, a0, 4);  // 0x9ACBDC
    v1 = slt(v1, s1);
    lw(s3, a0, 8);  // 0x9ACBE0
    if (v1 != 0) {
        // 0x0059d0e8
        charge(ctx, 2);
        s0 = 0;
        v0 = slt(s0, s1);
        for (;;) {
            // 0x0059d0f0
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x0059d0f8
                charge(ctx, 7);
                v0 = sll(s0, 4);
                s0 = addiu(s0, 1);
                s2 = addu(s3, v0);
                a0 = s2;
                jal(ctx, 0x59D104u, gen::fn_sub_59D230_0059d230);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = slt(s0, s1);
                if (!cc) {
                    goto L_0059d114_4;
                }
                backedge(ctx);
                continue;
            }
            a0 = s2;
            break;
        }
    L_0059d118:
        charge(ctx, 8);
        a1 = s5;
        a2 = s4;
        jal(ctx, 0x59D11Cu, gen::fn_sub_59D1C8_0059d1c8);
        a0 = addiu(s6, -13352);
        lw(v1, a0, 4);
        v0 = s2;
        v1 = addiu(v1, 1);
        sw(v1, a0, 4);
    }
    // 0x0059d138 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
    return;
L_0059d114_4:
    charge(ctx, 1);
    a0 = s2;
    goto L_0059d118;
}

// 0x0059D160 sub_59D160 -- 48 bytes; frame 0x10: ra sp+0x0
// [sfhDestroyView] SFH release a view (cleared; used - 1).
void sub_59D160(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059d160
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x59D168u, gen::fn_sub_59D1B0_0059d1b0);
    v1 = 0x9B0000;
    ld(ra, sp, 0x0);
    v1 = addiu(v1, -13352);  // &0x9ACBD8
    lw(v0, v1, 4);  // 0x9ACBDC
    v0 = addiu(v0, -1);
    sw(v0, v1, 4);  // 0x9ACBDC
    sp = addiu(sp, 0x10);
}

// 0x0059D1B0 sub_59D1B0 -- 20 bytes; leaf frame (no stack)
// [sfhClearView] Clears a view (four words).
void sub_59D1B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x0059d1b0
    enter(ctx, 5);  // entry check point + this block's cycles
    sw(zero, a0, sfh::kVersion);
    sw(zero, a0, sfh::kState);
    sw(zero, a0, sfh::kBuf);
    sw(zero, a0, sfh::kSize);
}

// 0x0059D1C8 sub_59D1C8 -- 20 bytes; leaf frame (no stack)
// [sfhSetView] Sets a view taken with (buf, size); returns 1.
void sub_59D1C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0059d1c8
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 1;
    sw(a2, a0, sfh::kSize);
    sw(v0, a0, sfh::kState);
    sw(a1, a0, sfh::kBuf);
}

// 0x0059D1E0 sub_59D1E0 -- 80 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhClearViews] Clears count views from the array (16 bytes each).
void sub_59D1E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059d1e0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a0;
    sd(s0, sp, 0x0);
    a0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    if (i64(v0) > 0) {
        // 0x0059d1fc
        charge(ctx, 3);
        s1 = a0;
        s0 = v0;
        a0 = s1;
        for (;;) {
            // 0x0059d208
            charge(ctx, 5);
            s1 = addiu(s1, sfh::kViewSize);
            s0 = addiu(s0, -1);
            jal(ctx, 0x59D20Cu, gen::fn_sub_59D1B0_0059d1b0);
            a0 = s1;
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0059d21c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059D230 sub_59D230 -- 12 bytes; leaf frame (no stack)
// [sfhIsFree] True when a view is free (state 0).
void sub_59D230(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0059d230
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, sfh::kState);
    v0 = sltiu(v0, 1);
}

// 0x0059D240 sub_59D240 -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfhIsReadable] The getters' gate: the view is usable (sub_59D288) and its version is 1.07 or at least 1.10.
void sub_59D240(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059d240
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x59D24Cu, gen::fn_sub_59D288_0059d288);
    a0 = 107;
    if (v0 != 0) {
        // 0x0059d25c
        charge(ctx, 3);
        lw(v0, s0, sfh::kVersion);
        v1 = slti(v0, 110);
        if (v0 != a0) {
            // 0x0059d268
            charge(ctx, 2);
            v0 = 0;
            if (v1 == 0) {
                goto L_0059d270;
            }
            // 0x0059d274 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(s0, sp, 0x0);
            ld(ra, sp, 0x8);
            sp = addiu(sp, 0x10);
            return;
        }
    L_0059d270:
        charge(ctx, 1);
        v0 = 1;
    }
    // 0x0059d274 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0059D288 sub_59D288 -- 40 bytes; leaf frame (no stack)
// [sfhIsParsed] True when the view state is 2 (Sofdec) or larger, or below -1; false for -1, 0 and 1.
void sub_59D288(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059d288
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, sfh::kState);
    v1 = slti(v0, -1);
    v0 = slti(v0, 2);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 1;
    if (!cc) {
        // 0x0059d29c
        charge(ctx, 2);
        v0 = 0;
        if (v1 != 0) {
            // 0x0059d2a4
            charge(ctx, 1);
            v0 = 1;
        }
    }
    // 0x0059d2a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0059D2B0 sub_59D2B0 -- 240 bytes; frame 0x40: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, ra sp+0x30
// [sfhParse] SFH parse (view, &ok): a taken view of at least 2,048 bytes whose bytes +32.. are "SofdecStream" (24 bytes
// with the padding) becomes state 2 with version = 100 * major + minor (sub_59D6A0) and *ok = 1; a short or foreign
// buffer becomes state -1. A free view returns 0 at once.
void sub_59D2B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059d2b0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(s3, sp, 0x28);
    s3 = 1;
    sd(ra, sp, 0x30);
    sw(zero, s2, 0);
    lw(v0, s0, sfh::kBuf);
    s1 = addiu(v0, sfh::kHdrId);
    jal(ctx, 0x59D2DCu, gen::fn_sub_59D230_0059d230);
    if (v0 != s3) {
        lw(v0, s0, sfh::kSize);
        // 0x0059d2f8
        charge(ctx, 3);
        v0 = sltiu(v0, 2048);
        a1 = 0x7D0000;
        if (v0 == 0) {
            // 0x0059d318
            charge(ctx, 8);
            a0 = s1;
            a2 = 24;
            a1 = addiu(a1, -23096);
            jal(ctx, 0x59D320u, gen::fn_memcmp_005211b8);
            a0 = s0;
            a1 = sp;
            a2 = addiu(sp, 0x4);
            if (v0 == 0) {
                // 0x0059d348
                charge(ctx, 5);
                v0 = 2;
                link(ctx, 0x59D34Cu);  // $ra first: the delay slot below depends on it
                sw(v0, s0, 0);
                call(ctx, gen::fn_sub_59D6A0_0059d6a0);
                lw(v1, sp, 0x0);
                if (v0 != 0) {
                    // 0x0059d35c
                    charge(ctx, 10);
                    v0 = 1;
                    lw(a1, sp, 0x4);
                    a0 = sll(v1, 1);
                    a0 = addu(a0, v1);
                    a0 = sll(a0, 3);
                    a0 = addu(a0, v1);
                    a0 = sll(a0, 2);
                    a0 = addu(a0, a1);
                    sw(a0, s0, sfh::kVersion);
                    sw(s3, s2, 0);
                }
            } else {
                // 0x0059d338
                charge(ctx, 4);
                v0 = si(-1);
                sw(v0, s0, 0);
                v0 = 0;
            }
        } else {
            // 0x0059d304
            charge(ctx, 4);
            v1 = si(-1);
            v0 = 0;
            sw(v1, s0, 0);
        }
    } else {
        // 0x0059d2ec
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0059d384 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0059D3A0 sub_59D3A0 -- 108 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// [sfhHasStream] SFH *found = the header lists stream id a1 (the stream table, sub_59D4E0); returns 1 when readable.
void sub_59D3A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059d3a0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a1 & 0xFF;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    sw(zero, s2, 0);
    link(ctx, 0x59D3C0u);  // $ra first: the delay slot below depends on it
    lw(s0, a0, sfh::kBuf);
    call(ctx, gen::fn_sub_59D240_0059d240);
    a1 = s1;
    a0 = s0;
    if (v0 != 0) {
        // 0x0059d3d4
        charge(ctx, 4);
        jal(ctx, 0x59D3D4u, gen::fn_sub_59D4E0_0059d4e0);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (cc) {
            // 0x0059d3f0
            charge(ctx, 1);
            sw(zero, s2, 0);
        } else {
            // 0x0059d3e4
            charge(ctx, 2);
            sw(v0, s2, 0);
        }
    }
    // 0x0059d3f4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059D410 sub_59D410 -- 208 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [sfhGetEntryFlag] SFH the entry flag of stream id a1 (version >= 1.10): byte +32 of its entry for audio (sub_59E6E0)
// or video (sub_59E720) ids.
void sub_59D410(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059d410
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0;
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    lw(v1, s1, sfh::kVersion);
    v1 = slti(v1, 110);
    a0 = s0;
    if (v1 == 0) {
        // 0x0059d444
        charge(ctx, 8);
        jal(ctx, 0x59D444u, gen::fn_sub_59E760_0059e760);
        a2 = 224;
        v1 = v0;
        v0 = 192;
        a0 = s1;
        a1 = s0;
        if (v1 == v0) {
            // 0x0059d478
            charge(ctx, 6);
            jal(ctx, 0x59D478u, gen::fn_sub_59DE68_0059de68);
            a0 = s0;
            v1 = v0;
            a1 = v1;
            if (v1 != 0) {
                // 0x0059d490
                charge(ctx, 4);
                jal(ctx, 0x59D490u, gen::fn_sub_59E6E0_0059e6e0);
                sw(v0, s2, 0);
            L_0059d4c4:
                charge(ctx, 1);
                v0 = 1;
            }
            goto L_0059d4c8;
        }
        // 0x0059d464
        charge(ctx, 2);
        v0 = 0;
        if (v1 == a2) {
            // 0x0059d4a0
            charge(ctx, 6);
            a1 = s0;
            jal(ctx, 0x59D4A0u, gen::fn_sub_59DE68_0059de68);
            a0 = s0;
            v1 = v0;
            a1 = v1;
            if (v1 != 0) {
                // 0x0059d4b8
                charge(ctx, 3);
                jal(ctx, 0x59D4B8u, gen::fn_sub_59E720_0059e720);
                sw(v0, s2, 0);
                goto L_0059d4c4;
            }
            goto L_0059d4c8;
        }
        // 0x0059d46c
        charge(ctx, 2);
        ld(s0, sp, 0x0);
        // 0x0059d4cc (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0059d4c8:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0059d4cc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059D4E0 sub_59D4E0 -- 72 bytes; leaf frame (no stack)
// [sfhFindStream] The stream-table entry (26 entries of 64 bytes from +384) whose stream_id byte (+24) is a1, or 0.
void sub_59D4E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0059d4e0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = addiu(a0, sfh::kHdrStreams);
    a3 = 0;
    lbu(v0, v1, sfh::kStrId);
    a2 = 0;
    for (;;) {
        // 0x0059d510
        charge(ctx, 3);
        if (v0 == a1) {
            goto L_0059d51c_4;
        }
        a2 = addiu(a2, 1);
        backedge(ctx);
        // 0x0059d4f8
        charge(ctx, 4);
        v0 = sll(a2, 6);
        v1 = slti(a2, 26);
        v0 = addu(a0, v0);
        if (v1 != 0) {
            // 0x0059d508
            charge(ctx, 2);
            v1 = addiu(v0, sfh::kHdrStreams);
            lbu(v0, v1, sfh::kStrId);
            continue;
        }
        break;
    }
    // 0x0059d520 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a3;
    return;
L_0059d51c_4:
    charge(ctx, 1);
    a3 = v1;
    // 0x0059d520 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a3;
}

// 0x0059D528 sub_59D528 -- 112 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetText0] Copies the 12 characters at header +64 into a 13-byte string (cleared first).
void sub_59D528(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059d528
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    lw(v0, a0, sfh::kBuf);
    s1 = addiu(v0, sfh::kHdrText0);
    jal(ctx, 0x59D540u, gen::fn_sub_59D240_0059d240);
    a0 = s0;
    a1 = 0;
    a2 = 13;
    if (v0 != 0) {
        // 0x0059d558
        charge(ctx, 11);
        jal(ctx, 0x59D558u, gen::fn_memset_00521408);
        v0 = 1;
        ldl(v1, s1, 7);
        ldr(v1, s1, 0);
        lwl(a0, s1, 11);
        lwr(a0, s1, 8);
        sdl(v1, s0, 7);
        sdr(v1, s0, 0);
        swl(a0, s0, 11);
        swr(a0, s0, 8);
    }
    // 0x0059d584 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059D598 sub_59D598 -- 112 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetText1] Copies the 12 characters at header +76 into a 13-byte string (cleared first).
void sub_59D598(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059d598
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    sb(zero, s0, 0);
    link(ctx, 0x59D5B0u);  // $ra first: the delay slot below depends on it
    lw(s1, a0, sfh::kBuf);
    call(ctx, gen::fn_sub_59D240_0059d240);
    a0 = s0;
    a1 = 0;
    a2 = 13;
    if (v0 != 0) {
        // 0x0059d5c8
        charge(ctx, 11);
        jal(ctx, 0x59D5C8u, gen::fn_memset_00521408);
        v0 = 1;
        ldl(v1, s1, 83);
        ldr(v1, s1, 76);
        lwl(a0, s1, 87);
        lwr(a0, s1, 84);
        sdl(v1, s0, 7);
        sdr(v1, s0, 0);
        swl(a0, s0, 11);
        swr(a0, s0, 8);
    }
    // 0x0059d5f4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059D608 sub_59D608 -- 148 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetCreator] Copies the 32 characters at header +96 (the creator text with "Ver.") into a 33-byte string; needs
// only a parsed view.
void sub_59D608(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059d608
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    sb(zero, s0, 0);
    lw(v0, a0, sfh::kBuf);
    s1 = addiu(v0, sfh::kHdrCreator);
    jal(ctx, 0x59D624u, gen::fn_sub_59D288_0059d288);
    a0 = s0;
    a1 = 0;
    a2 = 33;
    if (v0 != 0) {
        // 0x0059d63c
        charge(ctx, 19);
        jal(ctx, 0x59D63Cu, gen::fn_memset_00521408);
        v0 = 1;
        ldl(v1, s1, 7);
        ldr(v1, s1, 0);
        ldl(a0, s1, 15);
        ldr(a0, s1, 8);
        ldl(a1, s1, 23);
        ldr(a1, s1, 16);
        ldl(a2, s1, 31);
        ldr(a2, s1, 24);
        sdl(v1, s0, 7);
        sdr(v1, s0, 0);
        sdl(a0, s0, 15);
        sdr(a0, s0, 8);
        sdl(a1, s0, 23);
        sdr(a1, s0, 16);
        sdl(a2, s0, 31);
        sdr(a2, s0, 24);
    }
    // 0x0059d688 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059D6A0 sub_59D6A0 -- 204 bytes; frame 0x70: s0 sp+0x40, s1 sp+0x48, s2 sp+0x50, s3 sp+0x58, ra sp+0x60
// [sfhGetVersion] SFH version: the larger of the header's bytes (+56 major, +57 minor) and the "Ver.x.y" of its creator
// text, compared as 100 * major + minor.
void sub_59D6A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059d6a0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s0, sp, 0x40);
    sd(s1, sp, 0x48);
    s1 = a1;
    sd(s2, sp, 0x50);
    s2 = a2;
    sd(s3, sp, 0x58);
    a1 = sp;
    sd(ra, sp, 0x60);
    sw(zero, s1, 0);
    lw(v0, a0, sfh::kBuf);
    sw(zero, s2, 0);
    s0 = addiu(v0, sfh::kHdrId);
    jal(ctx, 0x59D6D0u, gen::fn_sub_59D608_0059d608);
    a0 = sp;
    a1 = addiu(sp, 0x30);
    a2 = addiu(sp, 0x34);
    if (v0 != 0) {
        // 0x0059d6e8
        charge(ctx, 6);
        lbu(s3, s0, sfh::kIdVerMinor);
        link(ctx, 0x59D6ECu);  // $ra first: the delay slot below depends on it
        lbu(s0, s0, sfh::kIdVerMajor);
        call(ctx, gen::fn_sub_59D988_0059d988);
        v1 = sll(s0, 1);
        v1 = addu(v1, s0);
        if (v0 != 0) {
            // 0x0059d700
            charge(ctx, 15);
            lw(a0, sp, 0x30);
            v1 = sll(v1, 3);
            lw(a1, sp, 0x34);
            v1 = addu(v1, s0);
            v0 = sll(a0, 1);
            v1 = sll(v1, 2);
            v0 = addu(v0, a0);
            v1 = addu(v1, s3);
            v0 = sll(v0, 3);
            v0 = addu(v0, a0);
            v0 = sll(v0, 2);
            v0 = addu(v0, a1);
            v1 = slt(v1, v0);
            if (v1 != 0) {
                sw(a0, s1, 0);
                // 0x0059d748
                charge(ctx, 1);
                sw(a1, s2, 0);
            } else {
                // 0x0059d73c
                charge(ctx, 3);
                sw(s0, s1, 0);
                sw(s3, s2, 0);
            }
            // 0x0059d74c
            charge(ctx, 1);
            v0 = 1;
        }
    }
    // 0x0059d750 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x40);
    ld(s1, sp, 0x48);
    ld(s2, sp, 0x50);
    ld(s3, sp, 0x58);
    ld(ra, sp, 0x60);
    sp = addiu(sp, 0x70);
}

// 0x0059D770 sub_59D770 -- 212 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetText2] Copies the 64 characters at header +224 into a 65-byte string (cleared first).
void sub_59D770(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059d770
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    sb(zero, s0, 0);
    lw(v0, a0, sfh::kBuf);
    s1 = addiu(v0, sfh::kHdrText2);
    jal(ctx, 0x59D78Cu, gen::fn_sub_59D240_0059d240);
    a0 = s0;
    a1 = 0;
    a2 = 65;
    if (v0 != 0) {
        // 0x0059d7a4
        charge(ctx, 35);
        jal(ctx, 0x59D7A4u, gen::fn_memset_00521408);
        v0 = 1;
        ldl(v1, s1, 7);
        ldr(v1, s1, 0);
        ldl(a0, s1, 15);
        ldr(a0, s1, 8);
        ldl(a1, s1, 23);
        ldr(a1, s1, 16);
        ldl(a2, s1, 31);
        ldr(a2, s1, 24);
        sdl(v1, s0, 7);
        sdr(v1, s0, 0);
        sdl(a0, s0, 15);
        sdr(a0, s0, 8);
        sdl(a1, s0, 23);
        sdr(a1, s0, 16);
        sdl(a2, s0, 31);
        sdr(a2, s0, 24);
        ldl(v1, s1, 39);
        ldr(v1, s1, 32);
        ldl(a0, s1, 47);
        ldr(a0, s1, 40);
        ldl(a1, s1, 55);
        ldr(a1, s1, 48);
        ldl(a2, s1, 63);
        ldr(a2, s1, 56);
        sdl(v1, s0, 39);
        sdr(v1, s0, 32);
        sdl(a0, s0, 47);
        sdr(a0, s0, 40);
        sdl(a1, s0, 55);
        sdr(a1, s0, 48);
        sdl(a2, s0, 63);
        sdr(a2, s0, 56);
    }
    // 0x0059d830 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059D848 sub_59D848 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetGeneral0] General-block getter: *out = word +0 of header +128; returns 1 when readable.
void sub_59D848(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059d848
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    sw(zero, s1, 0);
    lw(v0, a0, sfh::kBuf);
    s0 = addiu(v0, sfh::kHdrGeneral);
    jal(ctx, 0x59D864u, gen::fn_sub_59D240_0059d240);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0059d874
        charge(ctx, 4);
        lw(v1, s0, 0);
        v0 = 1;
        sw(v1, s1, 0);
        ld(s0, sp, 0x0);
    }
    // 0x0059d884 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059D898 sub_59D898 -- 80 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetGeneral4] General-block getter: *out = byte +4 (-1 when not readable) of header +128; returns 1 when readable.
void sub_59D898(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059d898
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = si(-1);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    sw(v0, s1, 0);
    lw(v1, a0, sfh::kBuf);
    s0 = addiu(v1, sfh::kHdrGeneral);
    jal(ctx, 0x59D8B8u, gen::fn_sub_59D240_0059d240);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0059d8c8
        charge(ctx, 4);
        lbu(v1, s0, 4);
        v0 = 1;
        sw(v1, s1, 0);
        ld(s0, sp, 0x0);
    }
    // 0x0059d8d8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059D8E8 sub_59D8E8 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetGeneral8] General-block getter: *out = halfword +8 (signed) of header +128; returns 1 when readable.
void sub_59D8E8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059d8e8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    sw(zero, s1, 0);
    lw(v0, a0, sfh::kBuf);
    s0 = addiu(v0, sfh::kHdrGeneral);
    jal(ctx, 0x59D904u, gen::fn_sub_59D240_0059d240);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0059d914
        charge(ctx, 4);
        lh(v1, s0, 8);
        v0 = 1;
        sw(v1, s1, 0);
        ld(s0, sp, 0x0);
    }
    // 0x0059d924 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059D938 sub_59D938 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetGeneral12] General-block getter: *out = word +12 of header +128; returns 1 when readable.
void sub_59D938(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059d938
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    sw(zero, s1, 0);
    lw(v0, a0, sfh::kBuf);
    s0 = addiu(v0, sfh::kHdrGeneral);
    jal(ctx, 0x59D954u, gen::fn_sub_59D240_0059d240);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0059d964
        charge(ctx, 4);
        lw(v1, s0, 12);
        v0 = 1;
        sw(v1, s1, 0);
        ld(s0, sp, 0x0);
    }
    // 0x0059d974 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059D988 sub_59D988 -- 96 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhParseVerText] Finds "Ver." in a text and reads the two numbers after it (sub_59D9E8 twice); 0 when there is none.
void sub_59D988(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059d988
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7D0000;
    sd(s0, sp, 0x0);
    s0 = a1;
    a1 = addiu(v0, -23064);  // "Ver."
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a2;
    jal(ctx, 0x59D9A4u, gen::fn_strstr_00524a50);
    a1 = s0;
    v1 = v0;
    a0 = addiu(v1, 4);
    if (v1 != 0) {
        // 0x0059d9bc
        charge(ctx, 6);
        jal(ctx, 0x59D9BCu, gen::fn_sub_59D9E8_0059d9e8);
        a1 = s1;
        a0 = addiu(v0, 1);
        jal(ctx, 0x59D9C8u, gen::fn_sub_59D9E8_0059d9e8);
        v0 = 1;
    }
    // 0x0059d9d4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059D9E8 sub_59D9E8 -- 136 bytes; leaf frame (no stack)
// [sfhReadDecimal] Reads a decimal number at p up to '.', ' ', NUL or a non-digit; *out = the number (0 when it does
// not start with a digit); returns the address of the character that ended it.
void sub_59D9E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x0059d9e8
    enter(ctx, 4);  // entry check point + this block's cycles
    lb(v1, a0, 0);
    v0 = 46;
    a2 = 0;
    if (v1 != v0) {
        // 0x0059d9f8
        charge(ctx, 3);
        v0 = 32;
        if (v1 == v0) {
            sw(a2, a1, 0);
        } else {
            // 0x0059da04
            charge(ctx, 2);
            if (v1 == 0) {
                sw(a2, a1, 0);
            } else {
                // 0x0059da0c
                charge(ctx, 4);
                v0 = addiu(v1, -48);
                v0 = sltiu(v0, 10);
                if (v0 == 0) {
                    sw(a2, a1, 0);
                } else {
                    // 0x0059da1c
                    charge(ctx, 3);
                    t0 = 46;
                    a3 = 32;
                    v0 = sll(a2, 2);
                    for (;;) {
                        // 0x0059da28
                        charge(ctx, 8);
                        a0 = addiu(a0, 1);
                        v0 = addu(v0, a2);
                        v0 = sll(v0, 1);
                        v0 = addu(v0, v1);
                        lb(v1, a0, 0);
                        a2 = addiu(v0, -48);
                        v0 = addiu(v1, -48);
                        if (v1 == t0) {
                            goto L_0059da64;
                        }
                        // 0x0059da48
                        charge(ctx, 2);
                        if (v1 == a3) {
                            sw(a2, a1, 0);
                        } else {
                            // 0x0059da50
                            charge(ctx, 2);
                            if (v1 != 0) {
                                // 0x0059da58
                                charge(ctx, 3);
                                v0 = sltiu(v0, 10);
                                if (v0 == 0) {
                                    goto L_0059da64;
                                }
                                v0 = sll(a2, 2);
                                backedge(ctx);
                                continue;
                            }
                            sw(a2, a1, 0);
                        }
                        break;
                    }
                }
            }
        }
        // 0x0059da68 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = a0;
        return;
    }
L_0059da64:
    charge(ctx, 1);
    sw(a2, a1, 0);
    // 0x0059da68 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
}

// 0x0059DA70 sub_59DA70 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetSystem0] System-block getter: *out = byte +0 of header +176; returns 1 when readable.
void sub_59DA70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059da70
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    sw(zero, s1, 0);
    lw(v0, a0, sfh::kBuf);
    s0 = addiu(v0, sfh::kHdrSystem);
    jal(ctx, 0x59DA8Cu, gen::fn_sub_59D240_0059d240);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0059da9c
        charge(ctx, 4);
        lbu(v1, s0, 0);
        v0 = 1;
        sw(v1, s1, 0);
        ld(s0, sp, 0x0);
    }
    // 0x0059daac (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059DAC0 sub_59DAC0 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetSystem1] System-block getter: *out = byte +1 of header +176; returns 1 when readable.
void sub_59DAC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059dac0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    sw(zero, s1, 0);
    lw(v0, a0, sfh::kBuf);
    s0 = addiu(v0, sfh::kHdrSystem);
    jal(ctx, 0x59DADCu, gen::fn_sub_59D240_0059d240);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0059daec
        charge(ctx, 4);
        lbu(v1, s0, 1);
        v0 = 1;
        sw(v1, s1, 0);
        ld(s0, sp, 0x0);
    }
    // 0x0059dafc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059DB10 sub_59DB10 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetSystem2] System-block getter: *out = byte +2 of header +176; returns 1 when readable.
void sub_59DB10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059db10
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    sw(zero, s1, 0);
    lw(v0, a0, sfh::kBuf);
    s0 = addiu(v0, sfh::kHdrSystem);
    jal(ctx, 0x59DB2Cu, gen::fn_sub_59D240_0059d240);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0059db3c
        charge(ctx, 4);
        lbu(v1, s0, 2);
        v0 = 1;
        sw(v1, s1, 0);
        ld(s0, sp, 0x0);
    }
    // 0x0059db4c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059DB60 sub_59DB60 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetSystem3] System-block getter: *out = byte +3 of header +176; returns 1 when readable.
void sub_59DB60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059db60
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    sw(zero, s1, 0);
    lw(v0, a0, sfh::kBuf);
    s0 = addiu(v0, sfh::kHdrSystem);
    jal(ctx, 0x59DB7Cu, gen::fn_sub_59D240_0059d240);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0059db8c
        charge(ctx, 4);
        lbu(v1, s0, 3);
        v0 = 1;
        sw(v1, s1, 0);
        ld(s0, sp, 0x0);
    }
    // 0x0059db9c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059DBB0 sub_59DBB0 -- 104 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [sfhGetSystem4] System-block getter: *out = word +4 of header +176 for versions >= 1.10.
void sub_59DBB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059dbb0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(ra, sp, 0x18);
    sw(zero, s2, 0);
    lw(v0, s0, sfh::kBuf);
    s1 = addiu(v0, sfh::kHdrSystem);
    jal(ctx, 0x59DBD4u, gen::fn_sub_59D240_0059d240);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0059dbe4
        charge(ctx, 4);
        lw(v1, s0, sfh::kVersion);
        v1 = slti(v1, 110);
        v0 = 0;
        if (v1 == 0) {
            // 0x0059dbf4
            charge(ctx, 3);
            lw(v1, s1, 4);
            v0 = 1;
            sw(v1, s2, 0);
        }
        // 0x0059dc00
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x0059dc04 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059DC18 sub_59DC18 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetSystem8] System-block getter: *out = word +8 of header +176; returns 1 when readable.
void sub_59DC18(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059dc18
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    sw(zero, s1, 0);
    lw(v0, a0, sfh::kBuf);
    s0 = addiu(v0, sfh::kHdrSystem);
    jal(ctx, 0x59DC34u, gen::fn_sub_59D240_0059d240);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0059dc44
        charge(ctx, 4);
        lw(v1, s0, 8);
        v0 = 1;
        sw(v1, s1, 0);
        ld(s0, sp, 0x0);
    }
    // 0x0059dc54 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059DC68 sub_59DC68 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetSystem12] System-block getter: *out = word +12 of header +176; returns 1 when readable.
void sub_59DC68(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059dc68
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    sw(zero, s1, 0);
    lw(v0, a0, sfh::kBuf);
    s0 = addiu(v0, sfh::kHdrSystem);
    jal(ctx, 0x59DC84u, gen::fn_sub_59D240_0059d240);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0059dc94
        charge(ctx, 4);
        lw(v1, s0, 12);
        v0 = 1;
        sw(v1, s1, 0);
        ld(s0, sp, 0x0);
    }
    // 0x0059dca4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059DCB8 sub_59DCB8 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetSystem16] System-block getter: *out = word +16 of header +176; returns 1 when readable.
void sub_59DCB8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059dcb8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    sw(zero, s1, 0);
    lw(v0, a0, sfh::kBuf);
    s0 = addiu(v0, sfh::kHdrSystem);
    jal(ctx, 0x59DCD4u, gen::fn_sub_59D240_0059d240);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0059dce4
        charge(ctx, 4);
        lw(v1, s0, 16);
        v0 = 1;
        sw(v1, s1, 0);
        ld(s0, sp, 0x0);
    }
    // 0x0059dcf4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059DD08 sub_59DD08 -- 52 bytes; leaf frame (no stack)
// [sfhGetSystem20] System-block getter: *out = word +20 of header +176 for versions >= 2.25 (no readability gate).
void sub_59DD08(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0059dd08
    enter(ctx, 8);  // entry check point + this block's cycles
    a2 = a1;
    lw(a1, a0, sfh::kBuf);
    sw(zero, a2, 0);
    v0 = 0;
    lw(v1, a0, sfh::kVersion);
    v1 = slti(v1, 225);
    a1 = addiu(a1, sfh::kHdrSystem);
    if (v1 == 0) {
        // 0x0059dd28
        charge(ctx, 3);
        lw(v1, a1, 20);
        v0 = 1;
        sw(v1, a2, 0);
    }
    // 0x0059dd34 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0059DD40 sub_59DD40 -- 52 bytes; leaf frame (no stack)
// [sfhGetSystem24] System-block getter: *out = word +24 of header +176 for versions >= 2.25 (no readability gate).
void sub_59DD40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0059dd40
    enter(ctx, 8);  // entry check point + this block's cycles
    a2 = a1;
    lw(a1, a0, sfh::kBuf);
    sw(zero, a2, 0);
    v0 = 0;
    lw(v1, a0, sfh::kVersion);
    v1 = slti(v1, 225);
    a1 = addiu(a1, sfh::kHdrSystem);
    if (v1 == 0) {
        // 0x0059dd60
        charge(ctx, 3);
        lw(v1, a1, 24);
        v0 = 1;
        sw(v1, a2, 0);
    }
    // 0x0059dd6c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0059DD78 sub_59DD78 -- 116 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetStreamText0] Copies the first 12 characters of stream id a1's entry into a 13-byte string.
void sub_59DD78(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059dd78
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = a1 & 0xFF;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    link(ctx, 0x59DD90u);  // $ra first: the delay slot below depends on it
    sb(zero, s0, 0);
    call(ctx, gen::fn_sub_59DE68_0059de68);
    a0 = s0;
    s1 = v0;
    a1 = 0;
    a2 = 13;
    if (s1 != 0) {
        // 0x0059ddac
        charge(ctx, 11);
        jal(ctx, 0x59DDACu, gen::fn_memset_00521408);
        v0 = 1;
        ldl(v1, s1, 7);
        ldr(v1, s1, 0);
        lwl(a0, s1, 11);
        lwr(a0, s1, 8);
        sdl(v1, s0, 7);
        sdr(v1, s0, 0);
        swl(a0, s0, 11);
        swr(a0, s0, 8);
    }
    // 0x0059ddd8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059DDF0 sub_59DDF0 -- 116 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetStreamText1] Copies the 12 characters at +12 of stream id a1's entry into a 13-byte string.
void sub_59DDF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ddf0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = a1 & 0xFF;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    link(ctx, 0x59DE08u);  // $ra first: the delay slot below depends on it
    sb(zero, s0, 0);
    call(ctx, gen::fn_sub_59DE68_0059de68);
    a0 = s0;
    s1 = v0;
    a1 = 0;
    a2 = 13;
    if (s1 != 0) {
        // 0x0059de24
        charge(ctx, 11);
        jal(ctx, 0x59DE24u, gen::fn_memset_00521408);
        v0 = 1;
        ldl(v1, s1, 19);
        ldr(v1, s1, 12);
        lwl(a0, s1, 23);
        lwr(a0, s1, 20);
        sdl(v1, s0, 7);
        sdr(v1, s0, 0);
        swl(a0, s0, 11);
        swr(a0, s0, 8);
    }
    // 0x0059de50 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059DE68 sub_59DE68 -- 84 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfhGetStream] The entry of stream id a1 when the view is readable (sub_59D4E0), else 0; 19 callers.
void sub_59DE68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059de68
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    link(ctx, 0x59DE7Cu);  // $ra first: the delay slot below depends on it
    lw(s1, a0, sfh::kBuf);
    call(ctx, gen::fn_sub_59D240_0059d240);
    a1 = s0;
    a0 = s1;
    if (v0 == 0) {
        // 0x0059dea8
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059de90
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_59D4E0_0059d4e0(ctx);  // tail call
}

// 0x0059DEC0 sub_59DEC0 -- 112 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// [sfhGetAudio25] Audio-entry getter: for an audio stream id (0xC0..0xDF) *out = byte +25 (-1 by default) of its entry.
void sub_59DEC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059dec0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = si(-1);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sw(v0, s2, 0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    a1 = s0;
    jal(ctx, 0x59DEE4u, gen::fn_sub_59DE68_0059de68);
    s1 = v0;
    a0 = s0;
    if (s1 != 0) {
        // 0x0059def8
        charge(ctx, 5);
        jal(ctx, 0x59DEF8u, gen::fn_sub_59E760_0059e760);
        v1 = 192;
        cc = v0 != v1;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x0059df0c
            charge(ctx, 3);
            lbu(v1, s1, 25);
            v0 = 1;
            sw(v1, s2, 0);
        }
    }
    // 0x0059df18 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059DF30 sub_59DF30 -- 128 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// [sfhGetAudio26] Audio-entry getter: for an audio stream id (0xC0..0xDF) *out = byte +26, only when byte +25 is 1 of
// its entry.
void sub_59DF30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059df30
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sw(zero, s2, 0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    a1 = s0;
    jal(ctx, 0x59DF50u, gen::fn_sub_59DE68_0059de68);
    s1 = v0;
    a0 = s0;
    if (s1 != 0) {
        // 0x0059df64
        charge(ctx, 5);
        jal(ctx, 0x59DF64u, gen::fn_sub_59E760_0059e760);
        v1 = 192;
        a0 = 1;
        if (v0 == v1) {
            // 0x0059df80
            charge(ctx, 3);
            lbu(v1, s1, 25);
            v0 = 0;
            if (v1 == a0) {
                // 0x0059df8c
                charge(ctx, 3);
                lbu(v1, s1, 26);
                v0 = 1;
                sw(v1, s2, 0);
            }
        } else {
            // 0x0059df78
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x0059df98 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059DFB0 sub_59DFB0 -- 108 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// [sfhGetAudio27] Audio-entry getter: for an audio stream id (0xC0..0xDF) *out = byte +27 of its entry.
void sub_59DFB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059dfb0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sw(zero, s2, 0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    a1 = s0;
    jal(ctx, 0x59DFD0u, gen::fn_sub_59DE68_0059de68);
    s1 = v0;
    a0 = s0;
    if (s1 != 0) {
        // 0x0059dfe4
        charge(ctx, 5);
        jal(ctx, 0x59DFE4u, gen::fn_sub_59E760_0059e760);
        v1 = 192;
        cc = v0 != v1;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x0059dff8
            charge(ctx, 3);
            lbu(v1, s1, 27);
            v0 = 1;
            sw(v1, s2, 0);
        }
    }
    // 0x0059e004 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059E020 sub_59E020 -- 108 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// [sfhGetAudio28] Audio-entry getter: for an audio stream id (0xC0..0xDF) *out = word +28 of its entry.
void sub_59E020(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059e020
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sw(zero, s2, 0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    a1 = s0;
    jal(ctx, 0x59E040u, gen::fn_sub_59DE68_0059de68);
    s1 = v0;
    a0 = s0;
    if (s1 != 0) {
        // 0x0059e054
        charge(ctx, 5);
        jal(ctx, 0x59E054u, gen::fn_sub_59E760_0059e760);
        v1 = 192;
        cc = v0 != v1;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x0059e068
            charge(ctx, 3);
            lw(v1, s1, 28);
            v0 = 1;
            sw(v1, s2, 0);
        }
    }
    // 0x0059e074 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059E090 sub_59E090 -- 112 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// [sfhGetVideo25] Video-entry getter: for a video stream id (0xE0..0xEF) *out = entry byte +25 (-1 by default).
void sub_59E090(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059e090
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = si(-1);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sw(v0, s2, 0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    a1 = s0;
    jal(ctx, 0x59E0B4u, gen::fn_sub_59DE68_0059de68);
    s1 = v0;
    a0 = s0;
    if (s1 != 0) {
        // 0x0059e0c8
        charge(ctx, 5);
        jal(ctx, 0x59E0C8u, gen::fn_sub_59E760_0059e760);
        v1 = 224;
        cc = v0 != v1;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x0059e0dc
            charge(ctx, 3);
            lbu(v1, s1, 25);
            v0 = 1;
            sw(v1, s2, 0);
        }
    }
    // 0x0059e0e8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059E100 sub_59E100 -- 116 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// [sfhGetVideo26] Video-entry getter: *out = entry halfword +26, with 0xFFFF read as 0.
void sub_59E100(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059e100
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sw(zero, s2, 0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    a1 = s0;
    jal(ctx, 0x59E120u, gen::fn_sub_59DE68_0059de68);
    s1 = v0;
    a0 = s0;
    if (s1 != 0) {
        // 0x0059e134
        charge(ctx, 5);
        jal(ctx, 0x59E134u, gen::fn_sub_59E760_0059e760);
        v1 = 224;
        cc = v0 != v1;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x0059e148
            charge(ctx, 5);
            lhu(v1, s1, 26);
            v0 = 1;
            a0 = v1 ^ 0xFFFF;
            if (a0 == 0) v1 = 0;
            sw(v1, s2, 0);
        }
    }
    // 0x0059e15c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059E178 sub_59E178 -- 176 bytes; frame 0x30: s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, ra sp+0x20
// [sfhGetVideoSize] Video-entry getter: the picture size packed as an MPEG sequence header packs it: *w = byte28 << 4 |
// byte29 >> 4, *h = (byte29 << 8 | byte30) & 0xFFF (each 12 bits).
void sub_59E178(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059e178
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sw(zero, s2, 0);
    sw(zero, s3, 0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x20);
    a1 = s0;
    jal(ctx, 0x59E1A4u, gen::fn_sub_59DE68_0059de68);
    s1 = v0;
    a0 = s0;
    if (s1 != 0) {
        // 0x0059e1b8
        charge(ctx, 5);
        jal(ctx, 0x59E1B8u, gen::fn_sub_59E760_0059e760);
        v1 = 224;
        cc = v0 != v1;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x0059e1cc
            charge(ctx, 16);
            a1 = addiu(s1, sfh::kVidSize);
            v0 = 1;
            lbu(a0, a1, 0);
            sw(a0, s2, 0);
            a0 = sll(a0, 4);
            lbu(v1, a1, 1);
            v1 = srl(v1, 4);
            a0 = a0 | v1;
            sw(a0, s2, 0);
            lbu(v1, a1, 1);
            sw(v1, s3, 0);
            v1 = sll(v1, 8);
            lbu(a0, a1, 2);
            v1 = v1 | a0;
            v1 = v1 & 0xFFF;
            sw(v1, s3, 0);
        }
    }
    // 0x0059e20c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0059E228 sub_59E228 -- 112 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// [sfhGetVideoFrameRate] Video-entry getter: *out = the frame rate x 1,000 of the entry's frame_rate_code (+31,
// sub_59E670).
void sub_59E228(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059e228
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sw(zero, s2, 0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    a1 = s0;
    jal(ctx, 0x59E248u, gen::fn_sub_59DE68_0059de68);
    s1 = v0;
    a0 = s0;
    if (s1 != 0) {
        // 0x0059e25c
        charge(ctx, 5);
        jal(ctx, 0x59E25Cu, gen::fn_sub_59E760_0059e760);
        v1 = 224;
        cc = v0 != v1;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x0059e270
            charge(ctx, 4);
            link(ctx, 0x59E270u);  // $ra first: the delay slot below depends on it
            lbu(a0, s1, sfh::kVidFrameRate);
            call(ctx, gen::fn_sub_59E670_0059e670);
            sw(v0, s2, 0);
            v0 = 1;
        }
    }
    // 0x0059e280 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059E298 sub_59E298 -- 112 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// [sfhGetVideo33] Video-entry getter for a usable video entry (sub_59E720): *out = byte +33 (-1 by default).
void sub_59E298(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059e298
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = si(-1);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sw(v0, s2, 0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    a1 = s0;
    jal(ctx, 0x59E2BCu, gen::fn_sub_59DE68_0059de68);
    s1 = v0;
    a0 = s0;
    a1 = s1;
    if (s1 != 0) {
        // 0x0059e2d4
        charge(ctx, 4);
        jal(ctx, 0x59E2D4u, gen::fn_sub_59E720_0059e720);
        ld(s0, sp, 0x0);
        if (v0 != 0) {
            // 0x0059e2e4
            charge(ctx, 3);
            lbu(v1, s1, 33);
            v0 = 1;
            sw(v1, s2, 0);
            goto L_0059e2f0;
        }
        // 0x0059e2f4 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0059e2f0:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0059e2f4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059E308 sub_59E308 -- 112 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// [sfhGetVideo34] Video-entry getter for a usable video entry (sub_59E720): *out = byte +34 (-1 by default).
void sub_59E308(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059e308
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = si(-1);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sw(v0, s2, 0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    a1 = s0;
    jal(ctx, 0x59E32Cu, gen::fn_sub_59DE68_0059de68);
    s1 = v0;
    a0 = s0;
    a1 = s1;
    if (s1 != 0) {
        // 0x0059e344
        charge(ctx, 4);
        jal(ctx, 0x59E344u, gen::fn_sub_59E720_0059e720);
        ld(s0, sp, 0x0);
        if (v0 != 0) {
            // 0x0059e354
            charge(ctx, 3);
            lbu(v1, s1, 34);
            v0 = 1;
            sw(v1, s2, 0);
            goto L_0059e360;
        }
        // 0x0059e364 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0059e360:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0059e364 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059E378 sub_59E378 -- 112 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// [sfhGetVideoFlag0] Video-entry getter for a usable video entry (sub_59E720): *out = bit 0 of byte +35.
void sub_59E378(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059e378
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sw(zero, s2, 0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    a1 = s0;
    jal(ctx, 0x59E398u, gen::fn_sub_59DE68_0059de68);
    s1 = v0;
    a0 = s0;
    a1 = s1;
    if (s1 != 0) {
        // 0x0059e3b0
        charge(ctx, 4);
        jal(ctx, 0x59E3B0u, gen::fn_sub_59E720_0059e720);
        ld(s0, sp, 0x0);
        if (v0 != 0) {
            // 0x0059e3c0
            charge(ctx, 4);
            lbu(v1, s1, sfh::kVidFlags);
            v0 = 1;
            v1 = v1 & 0x1;
            sw(v1, s2, 0);
            goto L_0059e3d0;
        }
        // 0x0059e3d4 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0059e3d0:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0059e3d4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059E3E8 sub_59E3E8 -- 116 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// [sfhGetVideoFlag4] Video-entry getter for a usable video entry (sub_59E720): *out = bit 4 of byte +35.
void sub_59E3E8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059e3e8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sw(zero, s2, 0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    a1 = s0;
    jal(ctx, 0x59E408u, gen::fn_sub_59DE68_0059de68);
    s1 = v0;
    a0 = s0;
    a1 = s1;
    if (s1 != 0) {
        // 0x0059e420
        charge(ctx, 4);
        jal(ctx, 0x59E420u, gen::fn_sub_59E720_0059e720);
        ld(s0, sp, 0x0);
        if (v0 != 0) {
            // 0x0059e430
            charge(ctx, 5);
            lbu(v1, s1, sfh::kVidFlags);
            v0 = 1;
            v1 = v1 & 0x10;
            v1 = sltu(0, v1);
            sw(v1, s2, 0);
            goto L_0059e444;
        }
        // 0x0059e448 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0059e444:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0059e448 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059E460 sub_59E460 -- 108 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// [sfhGetVideo36] Video-entry getter for a usable video entry (sub_59E720): *out = byte +36.
void sub_59E460(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059e460
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sw(zero, s2, 0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    a1 = s0;
    jal(ctx, 0x59E480u, gen::fn_sub_59DE68_0059de68);
    s1 = v0;
    a0 = s0;
    a1 = s1;
    if (s1 != 0) {
        // 0x0059e498
        charge(ctx, 4);
        jal(ctx, 0x59E498u, gen::fn_sub_59E720_0059e720);
        ld(s0, sp, 0x0);
        if (v0 != 0) {
            // 0x0059e4a8
            charge(ctx, 3);
            lbu(v1, s1, 36);
            v0 = 1;
            sw(v1, s2, 0);
            goto L_0059e4b4;
        }
        // 0x0059e4b8 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0059e4b4:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0059e4b8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059E4D0 sub_59E4D0 -- 132 bytes; frame 0x30: s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, ra sp+0x20
// [sfhGetVideo37] Video-entry getter for a usable video entry (sub_59E720): *out = byte +37, -1 when 64 or more.
void sub_59E4D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059e4d0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = si(-1);
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sw(s3, s2, 0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x20);
    a1 = s0;
    jal(ctx, 0x59E4F8u, gen::fn_sub_59DE68_0059de68);
    s1 = v0;
    a0 = s0;
    a1 = s1;
    if (s1 != 0) {
        // 0x0059e510
        charge(ctx, 4);
        jal(ctx, 0x59E510u, gen::fn_sub_59E720_0059e720);
        ld(s0, sp, 0x0);
        if (v0 != 0) {
            // 0x0059e520
            charge(ctx, 4);
            lbu(v0, s1, 37);
            v1 = slti(v0, 64);
            sw(v0, s2, 0);
            if (v1 == 0) {
                // 0x0059e530
                charge(ctx, 1);
                sw(s3, s2, 0);
            }
            // 0x0059e534
            charge(ctx, 1);
            v0 = 1;
            goto L_0059e538;
        }
        // 0x0059e53c (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_0059e538:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0059e53c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0059E558 sub_59E558 -- 132 bytes; frame 0x30: s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, ra sp+0x20
// [sfhGetVideo38] Video-entry getter for a usable video entry (sub_59E720): *out = byte +38, -1 when 64 or more.
void sub_59E558(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059e558
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = si(-1);
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sw(s3, s2, 0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x20);
    a1 = s0;
    jal(ctx, 0x59E580u, gen::fn_sub_59DE68_0059de68);
    s1 = v0;
    a0 = s0;
    a1 = s1;
    if (s1 != 0) {
        // 0x0059e598
        charge(ctx, 4);
        jal(ctx, 0x59E598u, gen::fn_sub_59E720_0059e720);
        ld(s0, sp, 0x0);
        if (v0 != 0) {
            // 0x0059e5a8
            charge(ctx, 4);
            lbu(v0, s1, 38);
            v1 = slti(v0, 64);
            sw(v0, s2, 0);
            if (v1 == 0) {
                // 0x0059e5b8
                charge(ctx, 1);
                sw(s3, s2, 0);
            }
            // 0x0059e5bc
            charge(ctx, 1);
            v0 = 1;
            goto L_0059e5c0;
        }
        // 0x0059e5c4 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_0059e5c0:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0059e5c4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0059E5E0 sub_59E5E0 -- 140 bytes; frame 0x30: s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x20
// [sfhGetVideo39] Video-entry getter for a usable video entry (sub_59E720): *out = byte +39 (versions >= 2.10; -1 by
// default).
void sub_59E5E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059e5e0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = si(-1);
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sw(v0, s3, 0);
    a1 = s0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    s2 = a0;
    jal(ctx, 0x59E60Cu, gen::fn_sub_59DE68_0059de68);
    s1 = v0;
    a0 = s0;
    a1 = s1;
    if (s1 != 0) {
        // 0x0059e624
        charge(ctx, 4);
        jal(ctx, 0x59E624u, gen::fn_sub_59E720_0059e720);
        ld(s0, sp, 0x0);
        if (v0 != 0) {
            // 0x0059e634
            charge(ctx, 4);
            lw(v1, s2, sfh::kVersion);
            v1 = slti(v1, 210);
            v0 = 0;
            if (v1 == 0) {
                // 0x0059e644
                charge(ctx, 3);
                lbu(v1, s1, 39);
                v0 = 1;
                sw(v1, s3, 0);
                goto L_0059e650;
            }
        }
        // 0x0059e654 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_0059e650:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0059e654 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0059E670 sub_59E670 -- 112 bytes; leaf frame (no stack)
// [sfhFrameRateFromCode] MPEG frame_rate_code -> frames per 1,000 s (ISO/IEC 13818-2 table 6-4): 1 23,976, 2 24,000, 3
// 25,000, 4 29,970, 5 30,000, 6 50,000, 7 59,940, 8 60,000; any other code 0 (the jump table 0x7CA5F0).
void sub_59E670(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0059e670
    enter(ctx, 4);  // entry check point + this block's cycles
    a0 = addiu(a0, -1);
    v0 = sltiu(a0, 8);
    if (v0 == 0) {
        // 0x0059e6d8
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x0059e680
    charge(ctx, 6);
    v0 = sll(a0, 2);
    v1 = 0x7D0000;
    v1 = addu(v1, v0);
    lw(v1, v1, -23056);
    switch (v1.u()) {
    case 0x59E698u:  // table[0]
        // 0x0059e698
        charge(ctx, 2);
        v0 = 23976;
        return;
    case 0x59E6A0u:  // table[1]
        // 0x0059e6a0
        charge(ctx, 2);
        v0 = 24000;
        return;
    case 0x59E6A8u:  // table[2]
        // 0x0059e6a8
        charge(ctx, 2);
        v0 = 25000;
        return;
    case 0x59E6B0u:  // table[3]
        // 0x0059e6b0
        charge(ctx, 2);
        v0 = 29970;
        return;
    case 0x59E6B8u:  // table[4]
        // 0x0059e6b8
        charge(ctx, 2);
        v0 = 30000;
        return;
    case 0x59E6C0u:  // table[5]
        // 0x0059e6c0
        charge(ctx, 2);
        v0 = 0xC350;
        return;
    case 0x59E6C8u:  // table[6]
        // 0x0059e6c8
        charge(ctx, 2);
        v0 = 0xEA24;
        return;
    case 0x59E6D0u:  // table[7]
        // 0x0059e6d0
        charge(ctx, 2);
        v0 = 0xEA60;
        return;
    default:  // not one of the table's targets: the dispatch table, as the recompiled body
        tail(ctx, v1.u());
        return;
    }
}

// 0x0059E6E0 sub_59E6E0 -- 64 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfhAudioEntryFlag] 1 for an audio stream id whose entry kind (+32) is 1; 0 for kind 0, kinds 2.. and other ids.
void sub_59E6E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059e6e0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a1;
    jal(ctx, 0x59E6ECu, gen::fn_sub_59E760_0059e760);
    v1 = 192;
    cc = v0 != v1;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x0059e700
        charge(ctx, 4);
        lbu(v1, s0, sfh::kStrKind);
        v0 = sltu(0, v1);
        v1 = sltiu(v1, 2);
        if (v1 == 0) v0 = 0;
    }
    // 0x0059e710 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0059E720 sub_59E720 -- 64 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfhVideoEntryFlag] 1 for a video stream id whose entry kind (+32) is 1; 0 for kind 0, kinds 2.. and other ids (the
// gate of the video getters).
void sub_59E720(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059e720
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a1;
    jal(ctx, 0x59E72Cu, gen::fn_sub_59E760_0059e760);
    v1 = 224;
    cc = v0 != v1;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x0059e740
        charge(ctx, 4);
        lbu(v1, s0, sfh::kStrKind);
        v0 = sltu(0, v1);
        v1 = sltiu(v1, 2);
        if (v1 == 0) v0 = 0;
    }
    // 0x0059e750 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0059E760 sub_59E760 -- 68 bytes; leaf frame (no stack)
// [sfhStreamClass] Stream-id class (ISO/IEC 13818-1 table 2-18): 0xC0..0xDF -> 0xC0 (audio), 0xE0..0xEF -> 0xE0
// (video), 0xBD and 0xBF -> 0xBD (private), anything else 0.
void sub_59E760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0059e760
    enter(ctx, 7);  // entry check point + this block's cycles
    a1 = a0;
    v0 = 192;
    v1 = addiu(a1, -192);
    a0 = addiu(a1, -224);
    v1 = sltiu(v1, 32);
    a0 = sltiu(a0, 16);
    if (v1 == 0) {
        // 0x0059e77c
        charge(ctx, 2);
        v0 = 224;
        if (a0 == 0) {
            // 0x0059e784
            charge(ctx, 3);
            v0 = 189;
            v1 = 191;
            if (a1 != v0) {
                // 0x0059e790
                charge(ctx, 2);
                v0 = 0;
                if (a1 == v1) {
                    // 0x0059e798
                    charge(ctx, 1);
                    v0 = 189;
                }
            }
        }
    }
    // 0x0059e79c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0059E7A8 sub_59E7A8 -- 84 bytes; frame 0x10: ra sp+0x0
// [sfxInitPool] SFX handle pool init: clears the 296-byte pool 0x7B47F0 and sets its capacity to 8.
void sub_59E7A8(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059e7a8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0059e7c0
    charge(ctx, 15);
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(s0, sp, 0x0);
    s0 = 0x7B0000;
    s0 = addiu(s0, 18416);  // &0x7B47F0
    a2 = 296;
    sd(ra, sp, 0x8);
    a0 = s0;
    jal(ctx, 0x59E7DCu, gen::fn_memset_00521408);
    v1 = 8;
    sw(v1, s0, 4);  // 0x7B47F4
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0059E800 sub_59E800 -- 8 bytes; leaf frame (no stack)
// [sfxNullHook] An empty function (jr $ra / nop). The FLIRT name is a false match (the same few instructions as the SDK
// function; this is CRI code). Byte-identical to nullsub_1 0x1007F0, which font2 already replaced: same contract, same
// pair tests. (SFX)
void sub_59E800(EEContext& ctx) {
    using namespace hg;
    // 0x0059e800
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0059E808 sub_59E808 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfxCreate] SFX create a handle: the first free pool entry (sub_59E860) is initialised (sub_59E8B0), marked in use
// and counted; 0 when the pool is full.
void sub_59E808(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059e808
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    jal(ctx, 0x59E814u, gen::fn_sub_59E860_0059e860);
    s0 = v0;
    a0 = s0;
    if (s0 != 0) {
        // 0x0059e828
        charge(ctx, 10);
        jal(ctx, 0x59E828u, gen::fn_sub_59E8B0_0059e8b0);
        v1 = 0x7B0000;
        v1 = addiu(v1, 18416);  // &0x7B47F0
        a1 = 1;
        lw(a0, v1, 0);  // 0x7B47F0
        v0 = s0;
        a0 = addiu(a0, 1);
        sw(a0, v1, 0);  // 0x7B47F0
        sw(a1, s0, 0);
    }
    // 0x0059e850 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0059E860 sub_59E860 -- 80 bytes; leaf frame (no stack)
// [sfxFindFree] SFX the first free entry (word 0 == 0) of the pool (36-byte entries from 0x7B47F8, capacity at
// 0x7B47F4), or 0.
void sub_59E860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0059e860
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    a2 = 0;
    v0 = addiu(v0, 18416);  // &0x7B47F0
    lw(a1, v0, 4);  // 0x7B47F4
    v0 = addiu(v0, 8);  // &0x7B47F8
    if (i64(a1) > 0) {
        // 0x0059e878
        charge(ctx, 2);
        a0 = v0;
        for (;;) {
            // 0x0059e880
            charge(ctx, 4);
            lw(v1, a0, 0);
            v0 = a0;
            a0 = addiu(a0, 36);
            if (v1 == 0) {
                break;
            }
            // 0x0059e890
            charge(ctx, 5);
            a2 = addiu(a2, 1);
            v0 = slt(a2, a1);
            if (v0 == 0) {
                goto L_0059e8a4;
            }
            backedge(ctx);
        }
        // 0x0059e8a8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0059e8a4:
    charge(ctx, 1);
    v0 = 0;
    // 0x0059e8a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0059E8B0 sub_59E8B0 -- 60 bytes; leaf frame (no stack)
// [sfxSetDefaults] SFX entry defaults: +4 = 1, +8 = 0, +12 = 31, +16 = 100, bytes +20 / +21 / +22 = 0 / 64 / 128;
// returns entry + 8.
void sub_59E8B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x0059e8b0
    enter(ctx, 15);  // entry check point + this block's cycles
    v1 = addiu(a0, 20);
    v0 = addiu(a0, 8);
    t1 = 31;
    a1 = 100;
    a3 = 1;
    t0 = 64;
    a2 = si(-128);
    sw(a1, v0, 8);
    sw(t1, v0, 4);
    sw(zero, v0, 0);
    sw(a3, a0, 4);
    sb(a2, v1, 2);
    sb(t0, v1, 1);
    sb(zero, v1, 0);
}

// 0x0059E8F0 sub_59E8F0 -- 40 bytes; leaf frame (no stack)
// [sfxDestroy] SFX destroy a handle: entry word 0 = 0 and the pool count - 1 (nothing for a null handle).
void sub_59E8F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0059e8f0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x0059e8f8
        charge(ctx, 6);
        sw(zero, a0, 0);
        v1 = 0x7B0000;
        v1 = addiu(v1, 18416);  // &0x7B47F0
        lw(v0, v1, 0);  // 0x7B47F0
        v0 = addiu(v0, -1);
        sw(v0, v1, 0);  // 0x7B47F0
    }
    // 0x0059e910 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

}  // namespace p3fes::game
