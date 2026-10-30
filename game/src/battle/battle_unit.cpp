// datCalc.c accessors over the 60-byte battle unit record (game/include/p3fes/game/battle.h), hand-decompiled
// from SLUS_216.21 (docs/ANALYSIS/21_battle.md section 2.2): HP/SP with the party cap, the bad-status word
// and the buff/debuff nibbles. Phase 5: these replace the recompiled bodies listed in game/replaced.txt;
// tests/game/test_battle.cpp runs each against its __recomp body.
//
// Virtual time per ADR-0013: the guest::enter/charge lines mirror the `ctx.cycles += N` blocks of
// recomp/generated/fn_0024_002ff2f0_00315c20.cpp on the executed path. K_Assert (sub_19D3F0) is `jr $ra`
// in the retail ELF, so a failed range check continues with the same loads; the call stays a guest::call
// for its check point and two cycles (as in game/src/script/script_ops.cpp).
//
// Faithfulness audit (2026-10-21, tools/ours/audit): all 12 functions here are now p3fes_handgen's register-faithful
// bodies (the hand versions differed from the original: faults only 5, scratch GPRs 5, frame/spills 2). Each keeps
// the notes of its earlier hand version above it; what this header says about how the bodies were written describes
// those earlier versions.
#include "p3fes/game/battle.h"

#include "p3fes/game/guest.h"
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line)
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

using namespace btl;

}  // namespace

// 0x002FFD70 datCalcGetHp -- 12 bytes; leaf frame (no stack)
// 0x2FFD70 datCalcGetHp(unit): the u16 at +8.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datCalcGetHp(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lhu;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x002ffd70
    enter(ctx, 3);  // entry check point + this block's cycles
    lhu(v0, a0, 8);
}

// 0x002FFD80 datCalcGetSp -- 12 bytes; leaf frame (no stack)
// 0x2FFD80 datCalcGetSp(unit): the u16 at +0xA.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datCalcGetSp(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lhu;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x002ffd80
    enter(ctx, 3);  // entry check point + this block's cycles
    lhu(v0, a0, 10);
}

// 0x002FFD90 datCalcSetHp -- 48 bytes; leaf frame (no stack)
// 0x2FFD90 datCalcSetHp(unit, hp) and 0x2FFDC0 datCalcSetSp(unit, sp): capped at 999 for party members.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datCalcSetHp(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lhu, hg::sh, hg::slti;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x002ffd90
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = a1 & 0xFFFF;
    at = slti(v1, 1000);
    if (at == 0) {
        // 0x002ffda0
        charge(ctx, 4);
        lhu(v1, a0, 0);
        v1 = v1 & 0x4;
        if (v1 == 0) {
            // 0x002ffdb0
            charge(ctx, 1);
            a1 = 999;
        }
    }
    // 0x002ffdb4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sh(a1, a0, 8);
}

// 0x002FFDC0 datCalcSetSp -- 48 bytes; leaf frame (no stack)
// 0x2FFD90 datCalcSetHp(unit, hp) and 0x2FFDC0 datCalcSetSp(unit, sp): capped at 999 for party members.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datCalcSetSp(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lhu, hg::sh, hg::slti;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x002ffdc0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = a1 & 0xFFFF;
    at = slti(v1, 1000);
    if (at == 0) {
        // 0x002ffdd0
        charge(ctx, 4);
        lhu(v1, a0, 0);
        v1 = v1 & 0x4;
        if (v1 == 0) {
            // 0x002ffde0
            charge(ctx, 1);
            a1 = 999;
        }
    }
    // 0x002ffde4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sh(a1, a0, 10);
}

// 0x00300550 datCalcGetBadStatus -- 12 bytes; leaf frame (no stack)
// 0x300550 datCalcGetBadStatus(unit): the whole word at +0xC.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datCalcGetBadStatus(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00300550
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 12);
}

// 0x00300530 datCalcGetBadStatusNoDown -- 20 bytes; leaf frame (no stack)
// 0x300530 datCalcGetBadStatusNoDown(unit): the low 20 bits (dsll32/dsrl32 by 12).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datCalcGetBadStatusNoDown(EEContext& ctx) {
    using hg::Gpr, hg::dsll32, hg::dsrl32, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00300530
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, 12);
    v0 = dsll32(v0, 12);
    v0 = dsrl32(v0, 12);
}

// 0x003004F0 datCalcSetBadStatus -- 64 bytes; leaf frame (no stack)
// 0x3004F0 datCalcSetBadStatus(unit, bits): a non-zero low 20 bits replaces the status field; the high
// 12 bits of `bits` are always or-ed in. Returns the final word (the value $v0 holds on return).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datCalcSetBadStatus(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::dsll32, hg::dsrl32, hg::enter, hg::lui, hg::lw, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x003004f0
    enter(ctx, 4);  // entry check point + this block's cycles
    a2 = dsll32(a1, 12);
    a2 = dsrl32(a2, 12);
    if (a2 != 0) {
        // 0x00300500
        charge(ctx, 5);
        lw(v1, a0, 12);
        v0 = lui(0xFFF0);
        v0 = v1 & v0;
        v0 = v0 | a2;
        sw(v0, a0, 12);
    }
    // 0x00300514 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = lui(0xFFF0);
    v1 = a1 & v0;
    lw(v0, a0, 12);
    v0 = v0 | v1;
    sw(v0, a0, 12);
}

// 0x00300560 datCalcClearBadStatus -- 24 bytes; leaf frame (no stack)
// 0x300560 datCalcClearBadStatus(unit, bits): word &= ~bits; returns the word.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datCalcClearBadStatus(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::nor, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00300560
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = nor(a1, 0);
    lw(v0, a0, 12);
    v0 = v0 & v1;
    sw(v0, a0, 12);
}

// 0x00300580 datCalcChkBadStatus -- 20 bytes; leaf frame (no stack)
// 0x300580 datCalcChkBadStatus(unit, bits): any of `bits` set.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datCalcChkBadStatus(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sltu;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00300580
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, 12);
    v0 = v0 & a1;
    v0 = sltu(0, v0);
}

// 0x0030B5A0 datCalcIsDead -- 60 bytes; leaf frame (no stack)
// 0x30B5A0 datCalcIsDead(unit, hp_delta): the dead bit (0x80000), or hp + delta not above zero.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datCalcIsDead(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::charge, hg::enter, hg::lhu, hg::lw, hg::slt, hg::sltu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0030b5a0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, a0, 12);
    v0 = 0x80000;
    v0 = v1 & v0;
    v0 = sltu(0, v0);
    if (v0 == 0) {
        // 0x0030b5c4
        charge(ctx, 4);
        lhu(v0, a0, 8);
        v0 = addu(v0, a1);
        v0 = slt(0, v0);
        v0 = v0 ^ 0x1;
    } else {
        // 0x0030b5b8
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0030b5d4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00300F60 datCalcGetEffectLevel -- 196 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x300F60 datCalcGetEffectLevel(unit, slot): the signed nibble of slot 0..16 (K_Assert line 1030 for
// slots above 20; the nibble is still read, from byte +0x1C + slot/2).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datCalcGetEffectLevel(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::lbu, hg::ld,
          hg::lq, hg::sd, hg::slti, hg::sq, hg::sra;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00300f60
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1;
    v0 = s1 & 0xFF;
    v0 = slti(v0, 21);
    if (v0 == 0) {
        // 0x00300f88
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -21888);  // "datCalc.c"
        a1 = 1030;
        jal(ctx, 0x300F94u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00300f9c
    charge(ctx, 6);
    a0 = s1 & 0xFF;
    v0 = sra(a0, 1);
    v1 = v0 & 0xFFFF;
    v0 = a0 & 0x1;
    if (v0 == 0) {
        // 0x00300fd4
        charge(ctx, 6);
        v0 = v1 & 0xFFFF;
        v0 = addu(v0, s0);
        lbu(v0, v0, 28);
        v0 = v0 & 0xF;
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
    } else {
        // 0x00300fb4
        charge(ctx, 8);
        v0 = v1 & 0xFFFF;
        v0 = addu(v0, s0);
        lbu(v0, v0, 28);
        v0 = sra(v0, 4);
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
    }
    // 0x00300fec
    charge(ctx, 5);
    v0 = dsll32(v0, 24);
    v0 = dsra32(v0, 24);
    at = slti(v0, 8);
    if (at == 0) {
        // 0x00301000
        charge(ctx, 3);
        v0 = addiu(v0, -15);
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
    }
    // 0x0030100c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
s32 datCalcGetEffectLevel(EEContext& ctx, u32 unit, u32 slot) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(unit)));
    ee::core::set_gpr64(ctx, GPR_A1, ee::core::sext32(static_cast<u32>(slot)));
    datCalcGetEffectLevel(ctx);
    return static_cast<s32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x00301750 datCalcGetEffectState -- 284 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x301750 datCalcGetEffectState(unit, slot): the nibble for slots 0..16, bit `slot` of +0x14 for 17..20
// (K_Assert line 1208 above 20; the shift then uses the low five bits of the slot).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datCalcGetEffectState(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::lbu, hg::ld,
          hg::lq, hg::lw, hg::sd, hg::sllv, hg::slti, hg::sltu, hg::sq, hg::sra;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00301750
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s2 = a1;
    s1 = s2 & 0xFF;
    v0 = slti(s1, 21);
    if (v0 == 0) {
        // 0x0030177c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -21888);  // "datCalc.c"
        a1 = 1208;
        jal(ctx, 0x301788u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00301790
    charge(ctx, 3);
    at = slti(s1, 17);
    if (at == 0) {
        // 0x00301834
        charge(ctx, 7);
        v0 = 1;
        v1 = sllv(v0, s1);
        lw(v0, s0, 20);
        v0 = v0 & v1;
        v0 = sltu(0, v0);
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
    } else {
        // 0x0030179c
        charge(ctx, 3);
        v0 = slti(s1, 21);
        if (v0 == 0) {
            // 0x003017a8
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, -21888);  // "datCalc.c"
            a1 = 1030;
            jal(ctx, 0x3017B4u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x003017bc
        charge(ctx, 6);
        a0 = s2 & 0xFF;
        v0 = sra(a0, 1);
        v1 = v0 & 0xFFFF;
        v0 = a0 & 0x1;
        if (v0 == 0) {
            // 0x003017f4
            charge(ctx, 6);
            v0 = v1 & 0xFFFF;
            v0 = addu(v0, s0);
            lbu(v0, v0, 28);
            v0 = v0 & 0xF;
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
        } else {
            // 0x003017d4
            charge(ctx, 8);
            v0 = v1 & 0xFFFF;
            v0 = addu(v0, s0);
            lbu(v0, v0, 28);
            v0 = sra(v0, 4);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
        }
        // 0x0030180c
        charge(ctx, 5);
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
        at = slti(v0, 8);
        if (at == 0) {
            // 0x00301820
            charge(ctx, 3);
            v0 = addiu(v0, -15);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
        }
        // 0x0030182c
        charge(ctx, 2);
    }
    // 0x00301850 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------
// The two setters leave $v0 alone, as the originals do (no value is computed into it).
namespace p3fes::recomp_gen {
using namespace p3fes::game;
}  // namespace p3fes::recomp_gen
