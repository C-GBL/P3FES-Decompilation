// Slice tail1: CRI SFD (the Sofdec stream core): the header-info builder, the error callback, the callback table.
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions only (no CRI material was
// opened). Pair tests: tests/game/test_tail1.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/tail1.h"

namespace p3fes::recomp_gen {
void fn_sceLibgcc32GetErxEntries_20_0058bc10(p3fes::EEContext&);
void fn_sub_58B108_0058b108(p3fes::EEContext&);
void fn_sub_58B128_0058b128(p3fes::EEContext&);
void fn_sub_58B140_0058b140(p3fes::EEContext&);
void fn_sub_58B158_0058b158(p3fes::EEContext&);
void fn_sub_58B220_0058b220(p3fes::EEContext&);
void fn_sub_58B248_0058b248(p3fes::EEContext&);
void fn_sub_58B278_0058b278(p3fes::EEContext&);
void fn_sub_58B510_0058b510(p3fes::EEContext&);
void fn_sub_58B560_0058b560(p3fes::EEContext&);
void fn_sub_58B5C8_0058b5c8(p3fes::EEContext&);
void fn_sub_58B720_0058b720(p3fes::EEContext&);
void fn_sub_58B7B0_0058b7b0(p3fes::EEContext&);
void fn_sub_58B868_0058b868(p3fes::EEContext&);
void fn_sub_58B8E0_0058b8e0(p3fes::EEContext&);
void fn_sub_58B978_0058b978(p3fes::EEContext&);
void fn_sub_58BB10_0058bb10(p3fes::EEContext&);
void fn_sub_58BB48_0058bb48(p3fes::EEContext&);
void fn_sub_58BB80_0058bb80(p3fes::EEContext&);
void fn_sub_58BBA8_0058bba8(p3fes::EEContext&);
void fn_sub_58BBB0_0058bbb0(p3fes::EEContext&);
void fn_sub_58BBE8_0058bbe8(p3fes::EEContext&);
void fn_sub_58BC20_0058bc20(p3fes::EEContext&);
void fn_sub_58BD58_0058bd58(p3fes::EEContext&);
void fn_sub_58BE10_0058be10(p3fes::EEContext&);
void fn_sub_58BE28_0058be28(p3fes::EEContext&);
void fn_sub_58BE40_0058be40(p3fes::EEContext&);
void fn_sub_58BEB0_0058beb0(p3fes::EEContext&);
void fn_sub_58BEF0_0058bef0(p3fes::EEContext&);
void fn_sub_58BF88_0058bf88(p3fes::EEContext&);
void fn_sub_58BF98_0058bf98(p3fes::EEContext&);
void fn_sub_58C060_0058c060(p3fes::EEContext&);
void fn_sub_58E250_0058e250(p3fes::EEContext&);
void fn_sub_599100_00599100(p3fes::EEContext&);
void fn_sub_5991B8_005991b8(p3fes::EEContext&);
void fn_sub_599240_00599240(p3fes::EEContext&);
void fn_sub_599290_00599290(p3fes::EEContext&);
void fn_sub_5992E0_005992e0(p3fes::EEContext&);
void fn_sub_59BCD0_0059bcd0(p3fes::EEContext&);
void fn_sub_59CFC0_0059cfc0(p3fes::EEContext&);
void fn_sub_59D050_0059d050(p3fes::EEContext&);
void fn_sub_59D098_0059d098(p3fes::EEContext&);
void fn_sub_59D160_0059d160(p3fes::EEContext&);
void fn_sub_59D2B0_0059d2b0(p3fes::EEContext&);
void fn_sub_59D3A0_0059d3a0(p3fes::EEContext&);
void fn_sub_59D410_0059d410(p3fes::EEContext&);
void fn_sub_59D6A0_0059d6a0(p3fes::EEContext&);
void fn_sub_59DBB0_0059dbb0(p3fes::EEContext&);
void fn_sub_59E178_0059e178(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace tail1;  // the named offsets of p3fes/game/tail1.h
namespace gen = ::p3fes::recomp_gen;

// 0x0058B108 sub_58B108 -- 32 bytes; frame 0x10: ra sp+0x0
// [sfdInitSfh] SFD: initialises SFH with the 32 views at 0x9A7F90 (tail call).
void sub_58B108(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058b108
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0x9A0000;
    sd(ra, sp, 0x0);
    a0 = 32;
    a1 = addiu(a1, 32656);  // &0x9A7F90
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59CFC0_0059cfc0(ctx);  // tail call
}

// 0x0058B128 sub_58B128 -- 20 bytes; frame 0x10: ra sp+0x0
// [sfdFinishSfh] SFD: finishes SFH (tail call to sub_59D050).
void sub_58B128(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0058b128
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59D050_0059d050(ctx);  // tail call
}

// 0x0058B140 sub_58B140 -- 24 bytes; leaf frame (no stack)
// [sfdClearHdrInfo] Clears a header-info record: valid, major, minor, system word and the header size.
void sub_58B140(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x0058b140
    enter(ctx, 6);  // entry check point + this block's cycles
    sw(zero, a0, sfdinfo::kHdrSize);
    sw(zero, a0, 0);
    sw(zero, a0, sfdinfo::kMajor);
    sw(zero, a0, sfdinfo::kMinor);
    sw(zero, a0, sfdinfo::kSysWord4);
}

// 0x0058B158 sub_58B158 -- 16 bytes; leaf frame (no stack)
// [sfdResetHdrInfo] Clears a header-info record's valid flag, system word and header size.
void sub_58B158(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x0058b158
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, sfdinfo::kHdrSize);
    sw(zero, a0, 0);
    sw(zero, a0, sfdinfo::kSysWord4);
}

// 0x0058B220 sub_58B220 -- 36 bytes; frame 0x10: ra sp+0x0
// [sfdIsPrivate2Code] True when the four bytes at p are the private_stream_2 packet start code 0x000001BF.
void sub_58B220(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058b220
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x58B228u, gen::fn_sub_58B248_0058b248);
    v0 = v0 ^ 0x1BF;
    ld(ra, sp, 0x0);
    v0 = sltiu(v0, 1);
    sp = addiu(sp, 0x10);
}

// 0x0058B248 sub_58B248 -- 44 bytes; leaf frame (no stack)
// [sfdReadBe32] The big-endian 32-bit word at p (four lbu).
void sub_58B248(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0058b248
    enter(ctx, 11);  // entry check point + this block's cycles
    lbu(v0, a0, 0);
    lbu(v1, a0, 1);
    v0 = sll(v0, 8);
    lbu(a1, a0, 2);
    v0 = v0 | v1;
    lbu(a2, a0, 3);
    v0 = sll(v0, 8);
    v0 = v0 | a1;
    v0 = sll(v0, 8);
    v0 = v0 | a2;
}

// 0x0058B278 sub_58B278 -- 84 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// [sfdIsSofdecHeader] True when (buf, size) is a Sofdec header: takes an SFH view, parses it (sub_59D2B0), releases it;
// 0 when no view is free.
void sub_58B278(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058b278
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x18);
    jal(ctx, 0x58B284u, gen::fn_sub_59D098_0059d098);
    s0 = v0;
    a1 = sp;
    a0 = s0;
    if (s0 != 0) {
        // 0x0058b29c
        charge(ctx, 8);
        jal(ctx, 0x58B29Cu, gen::fn_sub_59D2B0_0059d2b0);
        a0 = s0;
        lw(v1, sp, 0x0);
        if (v0 == 0) v1 = 0;
        link(ctx, 0x58B2B0u);  // $ra first: the delay slot below depends on it
        sw(v1, sp, 0x0);
        call(ctx, gen::fn_sub_59D160_0059d160);
        lw(v0, sp, 0x0);
    }
    // 0x0058b2bc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0058B510 sub_58B510 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfdGetHdrBuf] The header buffer of a handle: 0 without a buffer object (+14000) or while the byte count of +8060 is
// positive, else the object's data (+12).
void sub_58B510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058b510
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v1, s0, sfd::kHdrBufObj);
    v0 = 0;
    if (v1 != 0) {
        // 0x0058b52c
        charge(ctx, 4);
        jal(ctx, 0x58B52Cu, gen::fn_sub_58E250_0058e250);
        if (i64(v0) <= 0) {
            lw(v0, s0, sfd::kHdrBufObj);
            // 0x0058b548
            charge(ctx, 1);
            v0 = addiu(v0, 12);
        } else {
            // 0x0058b53c
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x0058b54c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0058B560 sub_58B560 -- 100 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfdParseHdrInfo] Parses the header copy of an info record: an SFH view of (+148, +144), sub_58B5C8, release.
void sub_58B560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058b560
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    a0 = addiu(s0, sfdinfo::kHdrCopy);
    sd(ra, sp, 0x10);
    link(ctx, 0x58B578u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, sfdinfo::kHdrSize);
    call(ctx, gen::fn_sub_59D098_0059d098);
    a1 = s0;
    s1 = v0;
    a0 = s1;
    if (s1 == 0) {
        // 0x0058b5b0
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0058b590
    charge(ctx, 8);
    jal(ctx, 0x58B590u, gen::fn_sub_58B5C8_0058b5c8);
    a0 = s1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_59D160_0059d160(ctx);  // tail call
}

// 0x0058B5C8 sub_58B5C8 -- 344 bytes; frame 0x30: s1 sp+0x18, s2 sp+0x20, s0 sp+0x10, ra sp+0x28
// [sfdBuildHdrInfo] The header-info builder (view, info): nothing unless the view is a Sofdec header; version = the
// larger of the header's and its "Ver." text's; the system word +4 (negated below 1.10); the general and system blocks;
// the first stream id of each class (0xBD, 0xBF, audio 0xC0..0xDF, video 0xE0..0xEF); the first audio and video
// stream's entries; valid = 1.
void sub_58B5C8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058b5c8
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x18);
    s1 = a1;
    a1 = sp;
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x28);
    s2 = a0;
    jal(ctx, 0x58B5E4u, gen::fn_sub_59D2B0_0059d2b0);
    lw(v1, sp, 0x0);
    a1 = addiu(sp, 0x4);
    a0 = s2;
    a2 = addiu(sp, 0x8);
    if (v0 == 0) v1 = 0;
    sw(v1, sp, 0x0);
    if (v1 != 0) {
        // 0x0058b608
        charge(ctx, 4);
        jal(ctx, 0x58B608u, gen::fn_sub_59D6A0_0059d6a0);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        lw(v0, sp, 0x4);
        if (!cc) {
            // 0x0058b618
            charge(ctx, 3);
            sw(zero, sp, 0x4);
            sw(zero, sp, 0x8);
            lw(v0, sp, 0x4);
        }
        // 0x0058b624
        charge(ctx, 20);
        a0 = s2;
        lw(v1, sp, 0x8);
        a1 = addiu(sp, 0xC);
        s0 = sll(v0, 1);
        sw(v0, s1, sfdinfo::kMajor);
        s0 = addu(s0, v0);
        sw(v1, s1, sfdinfo::kMinor);
        s0 = sll(s0, 3);
        s0 = addu(s0, v0);
        s0 = sll(s0, 2);
        s0 = addu(s0, v1);
        jal(ctx, 0x58B64Cu, gen::fn_sub_59DBB0_0059dbb0);
        lw(v1, sp, 0xC);
        s0 = slti(s0, 110);
        a1 = s1;
        a0 = s2;
        if (v0 == 0) v1 = 0;
        v0 = subu(0, v1);
        sw(v1, sp, 0xC);
        if (s0 != 0) {
            // 0x0058b674
            charge(ctx, 1);
            sw(v0, sp, 0xC);
        }
        // 0x0058b678
        charge(ctx, 36);
        lw(v0, sp, 0xC);
        link(ctx, 0x58B67Cu);  // $ra first: the delay slot below depends on it
        sw(v0, s1, sfdinfo::kSysWord4);
        call(ctx, gen::fn_sub_58B720_0058b720);
        a0 = s2;
        a1 = addiu(s1, sfdinfo::kSystem);
        jal(ctx, 0x58B688u, gen::fn_sub_58B7B0_0058b7b0);
        a0 = s2;
        a1 = 189;
        a2 = 189;
        jal(ctx, 0x58B698u, gen::fn_sub_58B868_0058b868);
        a0 = s2;
        sw(v0, s1, sfdinfo::kFirstPrivate1);
        a1 = 191;
        a2 = 191;
        jal(ctx, 0x58B6ACu, gen::fn_sub_58B868_0058b868);
        a0 = s2;
        sw(v0, s1, sfdinfo::kFirstPrivate2);
        a1 = 192;
        a2 = 223;
        jal(ctx, 0x58B6C0u, gen::fn_sub_58B868_0058b868);
        a0 = s2;
        sw(v0, s1, sfdinfo::kFirstAudio);
        a1 = 224;
        a2 = 239;
        jal(ctx, 0x58B6D4u, gen::fn_sub_58B868_0058b868);
        a0 = s2;
        sw(v0, s1, sfdinfo::kFirstVideo);
        a2 = addiu(s1, sfdinfo::kAudio);
        link(ctx, 0x58B6E8u);  // $ra first: the delay slot below depends on it
        lw(a1, s1, sfdinfo::kFirstAudio);
        call(ctx, gen::fn_sub_58B8E0_0058b8e0);
        a0 = s2;
        lw(a1, s1, sfdinfo::kFirstVideo);
        a2 = addiu(s1, sfdinfo::kVideo);
        jal(ctx, 0x58B6F8u, gen::fn_sub_58B978_0058b978);
        v0 = 1;
        sw(v0, s1, sfdinfo::kValid);
    }
    // 0x0058b708 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0058B720 sub_58B720 -- 140 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// [sfdGetGeneralInfo] The general block of an info record (+16..+28): the four sfh general getters through sub_58BB10
// (-1 when missing; the third reads 2 instead of -1).
void sub_58B720(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058b720
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x5A0000;
    sd(s1, sp, 0x8);
    s1 = a1;
    a1 = addiu(v0, -10168);  // &sub_59D848
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x58B73Cu, gen::fn_sub_58BB10_0058bb10);
    a1 = 0x5A0000;
    sw(v0, s1, 16);
    a1 = addiu(a1, -10088);  // &sub_59D898
    a0 = s0;
    jal(ctx, 0x58B750u, gen::fn_sub_58BB10_0058bb10);
    a1 = 0x5A0000;
    sw(v0, s1, 20);
    a1 = addiu(a1, -10008);  // &sub_59D8E8
    a0 = s0;
    jal(ctx, 0x58B764u, gen::fn_sub_58BB10_0058bb10);
    a1 = 0x5A0000;
    v1 = si(-1);
    a0 = s0;
    a1 = addiu(a1, -9928);  // &sub_59D938
    sw(v0, s1, 24);
    if (v0 == v1) {
        // 0x0058b784
        charge(ctx, 2);
        v0 = 2;
        sw(v0, s1, 24);
    }
    // 0x0058b78c
    charge(ctx, 8);
    jal(ctx, 0x58B78Cu, gen::fn_sub_58BB10_0058bb10);
    sw(v0, s1, 28);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0058B7B0 sub_58B7B0 -- 180 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfdGetSystemInfo] The system block of an info record (seven words): the sfh system getters through sub_58BB10.
void sub_58B7B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058b7b0
    enter(ctx, 45);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x5A0000;
    sd(s0, sp, 0x0);
    s0 = a1;
    a1 = addiu(v0, -9616);  // &sub_59DA70
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x58B7CCu, gen::fn_sub_58BB10_0058bb10);
    a1 = 0x5A0000;
    sw(v0, s0, 0);
    a0 = s1;
    a1 = addiu(a1, -9536);  // &sub_59DAC0
    jal(ctx, 0x58B7E0u, gen::fn_sub_58BB10_0058bb10);
    a1 = 0x5A0000;
    sw(v0, s0, 4);
    a0 = s1;
    a1 = addiu(a1, -9456);  // &sub_59DB10
    jal(ctx, 0x58B7F4u, gen::fn_sub_58BB10_0058bb10);
    a1 = 0x5A0000;
    sw(v0, s0, 8);
    a0 = s1;
    a1 = addiu(a1, -9376);  // &sub_59DB60
    jal(ctx, 0x58B808u, gen::fn_sub_58BB10_0058bb10);
    a1 = 0x5A0000;
    sw(v0, s0, 12);
    a0 = s1;
    a1 = addiu(a1, -9192);  // &sub_59DC18
    jal(ctx, 0x58B81Cu, gen::fn_sub_58BB10_0058bb10);
    a1 = 0x5A0000;
    sw(v0, s0, 16);
    a0 = s1;
    a1 = addiu(a1, -9112);  // &sub_59DC68
    jal(ctx, 0x58B830u, gen::fn_sub_58BB10_0058bb10);
    a1 = 0x5A0000;
    sw(v0, s0, 20);
    a0 = s1;
    a1 = addiu(a1, -9032);  // &sub_59DCB8
    jal(ctx, 0x58B844u, gen::fn_sub_58BB10_0058bb10);
    sw(v0, s0, 24);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0058B868 sub_58B868 -- 120 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// [sfdFirstStreamId] The first stream id in [lo, hi] the header lists (sub_59D3A0), or 0 (also 0 when hi < lo).
void sub_58B868(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058b868
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s1, sp, 0x18);
    s1 = a2;
    v0 = slt(s1, s0);
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x28);
    s2 = a0;
    if (v0 == 0) {
        // 0x0058b890
        charge(ctx, 2);
        a1 = s0 & 0xFF;
        for (;;) {
            // 0x0058b898
            charge(ctx, 5);
            a0 = s2;
            a2 = sp;
            jal(ctx, 0x58B89Cu, gen::fn_sub_59D3A0_0059d3a0);
            lw(v1, sp, 0x0);
            if (v0 != 0) {
                // 0x0058b8ac
                charge(ctx, 2);
                v0 = s0;
                if (v1 != 0) {
                    break;
                }
                goto L_0058b8b4;
            }
        L_0058b8b4:
            charge(ctx, 4);
            s0 = addiu(s0, 1);
            v0 = slt(s1, s0);
            a1 = s0 & 0xFF;
            if (v0 != 0) {
                goto L_0058b8c4;
            }
            backedge(ctx);
        }
        // 0x0058b8c8 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x10);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
L_0058b8c4:
    charge(ctx, 1);
    v0 = 0;
    // 0x0058b8c8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0058B8E0 sub_58B8E0 -- 148 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [sfdGetAudioInfo] The audio block of an info record: the four audio-entry getters for stream id a1 (nothing when a1 =
// 0).
void sub_58B8E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058b8e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    if (s0 != 0) {
        // 0x0058b904
        charge(ctx, 22);
        a2 = 0x5A0000;
        a2 = addiu(a2, -8512);  // &sub_59DEC0
        jal(ctx, 0x58B908u, gen::fn_sub_58BB48_0058bb48);
        a2 = 0x5A0000;
        sw(v0, s2, 0);
        a2 = addiu(a2, -8400);  // &sub_59DF30
        a0 = s1;
        a1 = s0;
        jal(ctx, 0x58B920u, gen::fn_sub_58BB48_0058bb48);
        a2 = 0x5A0000;
        sw(v0, s2, 4);
        a2 = addiu(a2, -8272);  // &sub_59DFB0
        a0 = s1;
        a1 = s0;
        jal(ctx, 0x58B938u, gen::fn_sub_58BB48_0058bb48);
        a2 = 0x5A0000;
        sw(v0, s2, 8);
        a0 = s1;
        a1 = s0;
        a2 = addiu(a2, -8160);  // &sub_59E020
        jal(ctx, 0x58B950u, gen::fn_sub_58BB48_0058bb48);
        sw(v0, s2, 12);
    }
    // 0x0058b95c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0058B978 sub_58B978 -- 408 bytes; frame 0x50: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, ra sp+0x40
// [sfdGetVideoInfo] The video block of an info record for stream id a1: entry bytes +25 / +26, the picture size (-1 /
// -1 when missing), the frame rate, the entry flag (sub_59D410: kind byte +32 == 1) and, when set, seven more entry fields.
void sub_58B978(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058b978
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x5A0000;
    sd(s0, sp, 0x10);
    s0 = a2;
    a2 = addiu(v0, -8048);  // &sub_59E090
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(s3, sp, 0x28);
    s3 = addiu(s0, 8);
    sd(s4, sp, 0x30);
    s4 = addiu(s0, 12);
    sd(s5, sp, 0x38);
    s5 = s2 & 0xFF;
    sd(ra, sp, 0x40);
    s1 = a0;
    jal(ctx, 0x58B9B4u, gen::fn_sub_58BB48_0058bb48);
    a2 = 0x5A0000;
    sw(v0, s0, 0);
    a2 = addiu(a2, -7936);  // &sub_59E100
    a0 = s1;
    a1 = s2;
    jal(ctx, 0x58B9CCu, gen::fn_sub_58BB48_0058bb48);
    a0 = s1;
    sw(v0, s0, 4);
    a1 = s5;
    a2 = s3;
    a3 = s4;
    jal(ctx, 0x58B9E4u, gen::fn_sub_59E178_0059e178);
    a2 = 0x5A0000;
    a2 = addiu(a2, -7640);  // &sub_59E228
    a0 = s1;
    a1 = s2;
    v1 = si(-1);
    if (v0 == 0) {
        // 0x0058ba04
        charge(ctx, 2);
        sw(v1, s3, 0);
        sw(v1, s4, 0);
    }
    // 0x0058ba0c
    charge(ctx, 17);
    jal(ctx, 0x58BA0Cu, gen::fn_sub_58BB48_0058bb48);
    a0 = s1;
    sw(v0, s0, 16);
    a2 = sp;
    a1 = s5;
    jal(ctx, 0x58BA20u, gen::fn_sub_59D410_0059d410);
    a2 = 0x5A0000;
    lw(v1, sp, 0x0);
    a2 = addiu(a2, -7528);  // &sub_59E298
    a0 = s1;
    a1 = s2;
    if (v0 == 0) v1 = 0;
    v0 = sltu(0, v1);
    sw(v1, sp, 0x0);
    sw(v0, s0, 20);
    if (v1 != 0) {
        // 0x0058ba50
        charge(ctx, 39);
        jal(ctx, 0x58BA50u, gen::fn_sub_58BB48_0058bb48);
        a2 = 0x5A0000;
        sw(v0, s0, 24);
        a2 = addiu(a2, -7416);  // &sub_59E308
        a0 = s1;
        a1 = s2;
        jal(ctx, 0x58BA68u, gen::fn_sub_58BB48_0058bb48);
        a2 = 0x5A0000;
        sw(v0, s0, 28);
        a2 = addiu(a2, -7304);  // &sub_59E378
        a0 = s1;
        a1 = s2;
        jal(ctx, 0x58BA80u, gen::fn_sub_58BB48_0058bb48);
        a2 = 0x5A0000;
        sw(v0, s0, 32);
        a2 = addiu(a2, -7192);  // &sub_59E3E8
        a0 = s1;
        a1 = s2;
        jal(ctx, 0x58BA98u, gen::fn_sub_58BB48_0058bb48);
        a2 = 0x5A0000;
        sw(v0, s0, 36);
        a2 = addiu(a2, -7072);  // &sub_59E460
        a0 = s1;
        a1 = s2;
        jal(ctx, 0x58BAB0u, gen::fn_sub_58BB48_0058bb48);
        a2 = 0x5A0000;
        sw(v0, s0, 40);
        a2 = addiu(a2, -6960);  // &sub_59E4D0
        a0 = s1;
        a1 = s2;
        jal(ctx, 0x58BAC8u, gen::fn_sub_58BB48_0058bb48);
        a2 = 0x5A0000;
        sw(v0, s0, 44);
        a0 = s1;
        a1 = s2;
        a2 = addiu(a2, -6824);  // &sub_59E558
        jal(ctx, 0x58BAE0u, gen::fn_sub_58BB48_0058bb48);
        sw(v0, s0, 48);
    }
    // 0x0058baec (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0058BB10 sub_58BB10 -- 52 bytes; frame 0x20: ra sp+0x10
// [sfdCallGetter] Calls getter(view, &out) through jalr; returns out, or -1 when the getter failed.
void sub_58BB10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058bb10
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a1;
    sd(ra, sp, 0x10);
    a1 = sp;
    jalr(ctx, 0x58BB1Cu, v0.u());
    a0 = si(-1);
    lw(v1, sp, 0x0);
    v0 = v0 ^ 0x0;
    ld(ra, sp, 0x10);
    if (v0 != 0) a0 = v1;
    v0 = a0;
    sp = addiu(sp, 0x20);
}

// 0x0058BB48 sub_58BB48 -- 56 bytes; frame 0x20: ra sp+0x10
// [sfdCallStreamGetter] Calls getter(view, id, &out) through jalr; returns out, or -1 when the getter failed.
void sub_58BB48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058bb48
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a2;
    sd(ra, sp, 0x10);
    a1 = a1 & 0xFF;
    a2 = sp;
    jalr(ctx, 0x58BB58u, v0.u());
    a0 = si(-1);
    lw(v1, sp, 0x0);
    v0 = v0 ^ 0x0;
    ld(ra, sp, 0x10);
    if (v0 != 0) a0 = v1;
    v0 = a0;
    sp = addiu(sp, 0x20);
}

// 0x0058BB80 sub_58BB80 -- 36 bytes; leaf frame (no stack)
// [sfdCopySysWords] Copies the info record's system words 1..3 (handle +156..+164) to handle +2352..+2360.
void sub_58BB80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0058bb80
    enter(ctx, 9);  // entry check point + this block's cycles
    a1 = addiu(a0, 152);
    a0 = addiu(a0, 2316);
    lw(v0, a1, 4);
    sw(v0, a0, 36);
    lw(v1, a1, 8);
    sw(v1, a0, 40);
    lw(v0, a1, 12);
    sw(v0, a0, 44);
}

// 0x0058BBA8 sub_58BBA8 -- 8 bytes; leaf frame (no stack)
// [sfdReturn2] Returns 2 (jr $ra / li v0, 2).
void sub_58BBA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058bba8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 2;
}

// 0x0058BBB0 sub_58BBB0 -- 56 bytes; leaf frame (no stack)
// [sfdGetHdrVersion] The handle's header version 100 * major + minor, or 0 before a header was parsed.
void sub_58BBB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0058bbb0
    enter(ctx, 4);  // entry check point + this block's cycles
    a0 = addiu(a0, sfd::kHandleInfo);
    lw(v1, a0, 0);
    v0 = 0;
    if (v1 != 0) {
        // 0x0058bbc0
        charge(ctx, 8);
        lw(v1, a0, 4);
        lw(a0, a0, 8);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, a0);
    }
    // 0x0058bbe0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0058BBE8 sub_58BBE8 -- 36 bytes; leaf frame (no stack)
// [sfdGetVideoWord6] The video block's word +24 when a header was parsed and its entry flag (+20) is set, else -1.
void sub_58BBE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0058bbe8
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, sfd::kHandleInfo);
    a0 = addiu(a0, 212);
    v0 = si(-1);
    if (v1 != 0) {
        // 0x0058bbf8
        charge(ctx, 3);
        lw(v1, a0, 20);
        if (v1 != 0) {
            lw(v0, a0, 24);
        }
    }
    // 0x0058bc04 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0058BC10 sceLibgcc32GetErxEntries_20 -- 12 bytes; leaf frame (no stack)
// [sfdGetVersionStr] Returns the module's version banner string in $v0 (the 12-byte "return a constant address" shape).
// The FLIRT name is a false match (the same few instructions as the SDK function; this is CRI code). SFD: "CRI
// SFD/PS2EE Ver.1.958".
void sceLibgcc32GetErxEntries_20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058bc10
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7D0000;
    v0 = addiu(v0, -24736);  // "\nCRI SFD/PS2EE Ver.1.958 Build:Mar  1 2005 10:53:48\n"
}

// 0x0058BC20 sub_58BC20 -- 12 bytes; leaf frame (no stack)
// [sfdCheckHandleSize] True when the second argument is the SFD handle size 0x37B0 (14,256 bytes).
void sub_58BC20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5};
    // 0x0058bc20
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = a1 ^ 0x37B0;
    v0 = sltiu(v0, 1);
}

// 0x0058BD58 sub_58BD58 -- 16 bytes; leaf frame (no stack)
// [sfdClearWork508] Clears the two words at +508 / +512 of the work block.
void sub_58BD58(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x0058bd58
    enter(ctx, 4);  // entry check point + this block's cycles
    a0 = addiu(a0, 508);
    sw(zero, a0, 4);
    sw(zero, a0, 0);
}

// 0x0058BE10 sub_58BE10 -- 20 bytes; frame 0x10: ra sp+0x0
// [sfdClearErrGlobal] Clears the global error record (tail call to sub_58BE28).
void sub_58BE10(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0058be10
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE28_0058be28(ctx);  // tail call
}

// 0x0058BE28 sub_58BE28 -- 24 bytes; leaf frame (no stack)
// [sfdClearErrRec] Clears five words (an error record and its two following words).
void sub_58BE28(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x0058be28
    enter(ctx, 6);  // entry check point + this block's cycles
    sw(zero, a0, 16);
    sw(zero, a0, 0);
    sw(zero, a0, 4);
    sw(zero, a0, 8);
    sw(zero, a0, 12);
}

// 0x0058BE40 sub_58BE40 -- 112 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// [sfdSetError] SFD raise(handle, code), 133 callers: nothing for code 0; else the handle's record (+2552) -- and a
// positive valid word (+72) is negated -- or, for a null handle, the global record 0x7B470C. Returns the code.
void sub_58BE40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058be40
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x10);
    if (s1 != 0) {
        // 0x0058be60
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x0058be80
            charge(ctx, 5);
            a0 = addiu(s0, sfd::kHandleErr);
            jal(ctx, 0x58BE80u, gen::fn_sub_58BEB0_0058beb0);
            lw(v0, s0, sfd::kHandleValid);
            v1 = subu(0, v0);
            if (i64(v0) > 0) {
                // 0x0058be94
                charge(ctx, 1);
                sw(v1, s0, sfd::kHandleValid);
            }
            // 0x0058be98
            charge(ctx, 1);
            v0 = s1;
        } else {
            // 0x0058be68
            charge(ctx, 5);
            a0 = 0x7B0000;
            a0 = addiu(a0, 18188);  // &0x7B470C
            jal(ctx, 0x58BE6Cu, gen::fn_sub_58BEB0_0058beb0);
            v0 = s1;
        }
    }
    // 0x0058be9c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0058BEB0 sub_58BEB0 -- 64 bytes; frame 0x10: ra sp+0x0
// [sfdCallErrFn] SFD error-record call: the code is stored only when none is pending (the first error sticks), then
// fn(arg) when code != 0 and fn is set.
void sub_58BEB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0058beb0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, err::kCode);
    v1 = a1;
    if (v0 == 0) {
        // 0x0058bec4
        charge(ctx, 1);
        sw(v1, a0, err::kCode);
    }
    // 0x0058bec8
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x0058bed0
        charge(ctx, 3);
        lw(v0, a0, err::kFn);
        if (v0 != 0) {
            // 0x0058bedc
            charge(ctx, 3);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x58BEDCu);  // $ra = the return address
            lw(a0, a0, err::kArg);
            call_ptr(ctx, jt);
            ld(ra, sp, 0x0);
        }
    }
    // 0x0058bee8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x0058BEF0 sub_58BEF0 -- 148 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [sfdEntryErrFunc] SFD set the error callback (handle, fn, arg): a bad handle raises 0xFF000101 on the global record;
// else the handle's (+2552) or the global record gets {fn, arg}. Returns 0.
void sub_58BEF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058bef0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    if (s0 == 0) {
        // 0x0058bf14
        charge(ctx, 5);
        a0 = 0x7B0000;
        a0 = addiu(a0, 18188);  // &0x7B470C
        jal(ctx, 0x58BF18u, gen::fn_sub_58BF88_0058bf88);
        ld(s0, sp, 0x0);
        // 0x0058bf6c (the shared epilogue, written out on this path)
        charge(ctx, 6);
        v0 = 0;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0058bf28
    charge(ctx, 5);
    jal(ctx, 0x58BF28u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x0058bf3c
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x101;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0058bf58
    charge(ctx, 5);
    a0 = addiu(s0, sfd::kHandleErr);
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x58BF60u, gen::fn_sub_58BF88_0058bf88);
    ld(s0, sp, 0x0);
    // 0x0058bf6c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 0;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0058BF88 sub_58BF88 -- 12 bytes; leaf frame (no stack)
// [sfdSetErrRec] Stores {fn, arg} into an error record.
void sub_58BF88(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0058bf88
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a2, a0, err::kArg);
    sw(a1, a0, err::kFn);
}

// 0x0058BF98 sub_58BF98 -- 200 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfdGetErrInf] SFD get the error record: 20 bytes from the handle (+2552) or the global record to out; a bad handle
// raises 0xFF000102.
void sub_58BF98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058bf98
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    if (s0 == 0) {
        // 0x0058bfb4
        charge(ctx, 14);
        v0 = 0x7B0000;
        v0 = addiu(v0, 17776);  // &0x7B4570
        ldl(v1, v0, 419);  // 0x7B4713
        ldr(v1, v0, 412);  // 0x7B470C
        ldl(a0, v0, 427);  // 0x7B471B
        ldr(a0, v0, 420);  // 0x7B4714
        lw(a1, v0, 428);  // 0x7B471C
        sdl(v1, s1, 7);
        sdr(v1, s1, 0);
        sdl(a0, s1, 15);
        sdr(a0, s1, 8);
        sw(a1, s1, 16);
        ld(s0, sp, 0x0);
        // 0x0058c04c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        v0 = 0;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0058bff0
    charge(ctx, 5);
    jal(ctx, 0x58BFF0u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x0058c004
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x102;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0058c020
    charge(ctx, 11);
    ldl(v0, s0, 2559);
    ldr(v0, s0, 2552);
    ldl(v1, s0, 2567);
    ldr(v1, s0, 2560);
    lw(a0, s0, 2568);
    sdl(v0, s1, 7);
    sdr(v0, s1, 0);
    sdl(v1, s1, 15);
    sdr(v1, s1, 8);
    sw(a0, s1, 16);
    ld(s0, sp, 0x0);
    // 0x0058c04c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0058C060 sub_58C060 -- 36 bytes; leaf frame (no stack)
// [sfdCheckHandle] SFD handle check: 0 for a non-null handle whose valid word (+72) is non-zero (remembered in
// 0x7B4568), else -1.
void sub_58C060(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058c060
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = si(-1);
    if (a0 != 0) {
        // 0x0058c068
        charge(ctx, 3);
        lw(v1, a0, sfd::kHandleValid);
        cc = v1 == 0;  // the condition, before the delay slot changes it
        v1 = 0x7B0000;
        if (!cc) {
            // 0x0058c074
            charge(ctx, 2);
            v0 = 0;
            sw(a0, v1, 17768);
        }
    }
    // 0x0058c07c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0058E250 sub_58E250 -- 12 bytes; leaf frame (no stack)
// [sfdBufObjCount] The byte count at +32 of the handle's buffer object (+8060).
void sub_58E250(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0058e250
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, sfd::kBufObj);
    lw(v0, v1, 32);
}

// 0x00599100 sub_599100 -- 180 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [sfdSetParam] SFD set parameter (handle, id, value): on a handle (bad: raises 0xFF000112) both id tables (+2572,
// +2972, each through the sub_5992E0 filter); for a null handle every open handle's first table and the global default
// table (0x7B4570[id]).
void sub_599100(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599100
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    if (s0 == 0) {
        // 0x00599124
        charge(ctx, 9);
        a0 = s1;
        a1 = s2;
        jal(ctx, 0x599128u, gen::fn_sub_5991B8_005991b8);
        v0 = sll(s1, 2);
        at = 0x7B0000;
        at = addu(at, v0);
        sw(s2, at, 17776);
        ld(s0, sp, 0x0);
        // 0x0059919c (the shared epilogue, written out on this path)
        charge(ctx, 6);
        v0 = 0;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00599148
    charge(ctx, 5);
    jal(ctx, 0x599148u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x0059915c
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x112;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00599178
    charge(ctx, 9);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x599180u, gen::fn_sub_599240_00599240);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x599190u, gen::fn_sub_599290_00599290);
    ld(s0, sp, 0x0);
    // 0x0059919c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 0;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005991B8 sub_5991B8 -- 136 bytes; frame 0x30: s0 sp+0x0, ra sp+0x28, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20
// [sfdSetParamAll] Sets parameter id = value (first table) on each of the eight open handles (0x7B4774) that pass the
// handle check.
void sub_5991B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005991b8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x7B0000;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x28);
    sd(s1, sp, 0x8);
    s1 = 7;
    sd(s2, sp, 0x10);
    s2 = addiu(v0, 18292);  // &0x7B4774
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    s4 = a0;
    lw(s0, s2, 0);  // 0x7B4774
    for (;;) {
        // 0x005991f0
        charge(ctx, 7);
        s2 = addiu(s2, 4);
        a0 = s0;
        jal(ctx, 0x5991F4u, gen::fn_sub_58C060_0058c060);
        a0 = s0;
        a1 = s4;
        a2 = s3;
        if (v0 == 0) {
            // 0x0059920c
            charge(ctx, 2);
            jal(ctx, 0x59920Cu, gen::fn_sub_599240_00599240);
        }
        // 0x00599214
        charge(ctx, 3);
        s1 = addiu(s1, -1);
        if (i64(s1) < 0) {
            break;
        }
        lw(s0, s2, 0);
        backedge(ctx);
    }
    // 0x00599220
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00599240 sub_599240 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [sfdSetParamA] First parameter table: handle +2572 [id] = value, when sub_5992E0 allows it.
void sub_599240(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599240
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a0;
    jal(ctx, 0x59925Cu, gen::fn_sub_5992E0_005992e0);
    s0 = sll(s0, 2);
    if (v0 != 0) {
        // 0x0059926c
        charge(ctx, 2);
        v0 = addu(s0, s2);
        sw(s1, v0, sfd::kParams);
    }
    // 0x00599274 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00599290 sub_599290 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [sfdSetParamB] Second parameter table: handle +2972 [id] = value, when sub_5992E0 allows it.
void sub_599290(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599290
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a0;
    jal(ctx, 0x5992ACu, gen::fn_sub_5992E0_005992e0);
    s0 = sll(s0, 2);
    if (v0 != 0) {
        // 0x005992bc
        charge(ctx, 2);
        v0 = addu(s0, s2);
        sw(s1, v0, sfd::kParams2);
    }
    // 0x005992c4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005992E0 sub_5992E0 -- 136 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [sfdParamAllowed] Parameter filter: refuses (id 6, value 1) when stream record 3 is inactive and (id 5, value 1) when
// stream record 2 is inactive; allows everything else.
void sub_5992E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005992e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 6;
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(ra, sp, 0x18);
    if (s0 == v0) {
        // 0x00599308
        charge(ctx, 3);
        v0 = 1;
        if (s1 != v0) {
            v0 = 5;
        L_00599328:
            charge(ctx, 2);
            cc = s0 != v0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (!cc) {
                // 0x00599330
                charge(ctx, 2);
                if (s1 != v0) {
                    ld(s0, sp, 0x0);
                } else {
                    // 0x00599338
                    charge(ctx, 5);
                    a0 = s2;
                    a1 = 2;
                    jal(ctx, 0x59933Cu, gen::fn_sub_59BCD0_0059bcd0);
                    ld(s0, sp, 0x0);
                    if (v0 != 0) {
                        // 0x0059934c
                        charge(ctx, 1);
                        v0 = 1;
                        goto L_00599350;
                    }
                }
                // 0x00599354 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(s1, sp, 0x8);
                ld(s2, sp, 0x10);
                ld(ra, sp, 0x18);
                sp = addiu(sp, 0x20);
                return;
            }
        L_00599350:
            charge(ctx, 1);
            ld(s0, sp, 0x0);
        } else {
            // 0x00599314
            charge(ctx, 4);
            a1 = 3;
            jal(ctx, 0x599314u, gen::fn_sub_59BCD0_0059bcd0);
            if (v0 != 0) {
                goto L_00599324;
            }
            ld(s0, sp, 0x0);
        }
        // 0x00599354 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_00599324:
    charge(ctx, 1);
    v0 = 5;
    goto L_00599328;
}

// 0x0059BCD0 sub_59BCD0 -- 28 bytes; leaf frame (no stack)
// [sfdStreamActive] True when stream record n (68 bytes each from +7996) is active (word 0 != 0).
void sub_59BCD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0059bcd0
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = sll(a1, 4);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    lw(v0, a0, sfd::kStreamRecs);
    v0 = sltu(0, v0);
}

}  // namespace p3fes::game
