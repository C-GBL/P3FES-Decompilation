// SKILL.TBL lookups of datCalc.c (game/include/p3fes/game/battle.h), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/21_battle.md sections 3.2 and 5): the physical flag, the field-usable flag, the element
// bit and the status -> element map used by the affinity checks. Phase 5: these replace the recompiled
// bodies listed in game/replaced.txt; tests/game/test_battle.cpp runs each against its __recomp body
// with the real battle/SKILL.TBL when it is available.
//
// Virtual time per ADR-0013 (block costs from recomp/generated/fn_0024_002ff2f0_00315c20.cpp). K_Assert
// (sub_19D3F0) is `jr $ra` in retail, so an out-of-range id still indexes the table; the call is kept
// through guest::call for its check point and two cycles.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): all 4 functions here are now p3fes_handgen's register-faithful
// bodies (the hand versions differed from the original: frame/spills 3, scratch GPRs 1). Each keeps the notes of its
// earlier hand version above it; what this header says about how the bodies were written describes those earlier
// versions.
#include "p3fes/game/battle.h"

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line)
void fn_datCalcGetSkillElement_003082f0(p3fes::EEContext&);  // datCalcGetSkillElement(unit, skill), still recompiled
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

using namespace btl;

}  // namespace

// 0x00300AF0 datCalcIsSkillUsableOnField -- 104 bytes; leaf frame (no stack)
// 0x300AF0 datCalcIsSkillUsableOnField(id): ids below 464 whose record is not physical (flags0 bit 1 clear)
// and has flags1 bit 0 set. No assertion: an id out of range returns 0.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datCalcIsSkillUsableOnField(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::charge, hg::enter, hg::lbu, hg::lw, hg::sll, hg::slti, hg::sltu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00300af0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = a0 & 0xFFFF;
    v0 = slti(v1, 464);
    if (v0 != 0) {
        // 0x00300b0c
        charge(ctx, 11);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        lw(v0, gp, -18680);  // gBtlSkillTbl
        v1 = addu(v0, v1);
        lbu(v0, v1, 0);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x00300b44
            charge(ctx, 3);
            lbu(v0, v1, 1);
            v0 = v0 & 0x1;
            v0 = sltu(0, v0);
        } else {
            // 0x00300b38
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00300b00
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00300b50 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003088B0 datCalcIsPhysicalSkill -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x3088B0 datCalcIsPhysicalSkill(id): flags0 bit 1 (K_Assert line 4059 for id >= 464, then the read).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datCalcIsPhysicalSkill(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::slti, hg::sltu, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003088b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = s0 & 0xFFFF;
    v0 = slti(v0, 464);
    if (v0 == 0) {
        // 0x003088d0
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -21888);  // "datCalc.c"
        a1 = 4059;
        jal(ctx, 0x3088DCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003088e4 (the shared epilogue, written out on this path)
    charge(ctx, 16);
    v1 = s0 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    lw(v0, gp, -18680);  // gBtlSkillTbl
    v0 = addu(v0, v1);
    lbu(v0, v0, 0);
    v0 = v0 & 0x2;
    v0 = sltu(0, v0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u32 datCalcIsPhysicalSkill(EEContext& ctx, u32 skill_id) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(skill_id)));
    datCalcIsPhysicalSkill(ctx);
    return static_cast<u32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x003080C0 datCalcGetElementBit -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x3080C0 datCalcGetElementBit(element): 1 << (element + 1) for the 19 element rows -1..18 (K_Assert line
// 3752 above 18; the shift count is taken modulo 32, as sllv does).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datCalcGetElementBit(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd,
          hg::sllv, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003080c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = dsll32(a0, 16);
    s0 = dsra32(s0, 16);
    v0 = slti(s0, 19);
    if (v0 == 0) {
        // 0x003080e0
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -21888);  // "datCalc.c"
        a1 = 3752;
        jal(ctx, 0x3080ECu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003080f4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v1 = addiu(s0, 1);
    v0 = 1;
    v0 = sllv(v0, v1);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00308120 datCalcGetElementForStatus -- 452 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x308120 datCalcGetElementForStatus(skill, status_bit): when a skill is given its element is taken through
// datCalcGetSkillElement(NULL, skill) and an element of 8 (dark) wins; otherwise (and for every other
// element) the status bit selects the element row from the table above. The compiler keeps the element in
// $s0, so the no-match path returns the caller's $s0 when no skill was given (K_Assert line 3817 is a no-op).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void datCalcGetElementForStatus(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::si,
          hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00308120
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x00308148
        charge(ctx, 9);
        a1 = a0 & 0xFFFF;
        a0 = 0;
        jal(ctx, 0x308150u, gen::fn_datCalcGetSkillElement_003082f0);
        s0 = dsll32(v0, 16);
        s0 = dsra32(s0, 16);
        v0 = 8;
        if (s0 != v0) {
            goto L_00308174;
        }
        // 0x0030816c
        charge(ctx, 2);
        // 0x003082cc (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_00308174:
    charge(ctx, 3);
    v0 = 0x100000;
    if (s1 == v0) {
        // 0x003082a8
        charge(ctx, 3);
        s0 = 7;
    } else {
        // 0x00308180
        charge(ctx, 3);
        v0 = 0x80000;
        if (s1 == v0) {
            // 0x0030829c
            charge(ctx, 3);
            s0 = 9;
        } else {
            // 0x0030818c
            charge(ctx, 3);
            v0 = 1024;
            if (s1 == v0) {
                // 0x00308290
                charge(ctx, 3);
                s0 = 7;
            } else {
                // 0x00308198
                charge(ctx, 3);
                v0 = 512;
                if (s1 == v0) {
                    // 0x00308284
                    charge(ctx, 3);
                    s0 = 7;
                } else {
                    // 0x003081a4
                    charge(ctx, 3);
                    v0 = 256;
                    if (s1 == v0) {
                        // 0x00308278
                        charge(ctx, 3);
                        s0 = 7;
                    } else {
                        // 0x003081b0
                        charge(ctx, 3);
                        v0 = 128;
                        if (s1 == v0) {
                            // 0x0030826c
                            charge(ctx, 3);
                            s0 = 11;
                        } else {
                            // 0x003081bc
                            charge(ctx, 3);
                            v0 = 64;
                            if (s1 == v0) {
                                // 0x00308260
                                charge(ctx, 3);
                                s0 = 5;
                            } else {
                                // 0x003081c8
                                charge(ctx, 3);
                                v0 = 32;
                                if (s1 == v0) {
                                    // 0x00308254
                                    charge(ctx, 3);
                                    s0 = 4;
                                } else {
                                    // 0x003081d4
                                    charge(ctx, 3);
                                    v0 = 16;
                                    if (s1 == v0) {
                                        // 0x00308248
                                        charge(ctx, 3);
                                        s0 = 15;
                                    } else {
                                        // 0x003081e0
                                        charge(ctx, 3);
                                        v0 = 8;
                                        if (s1 == v0) {
                                            // 0x0030823c
                                            charge(ctx, 3);
                                            s0 = 14;
                                        } else {
                                            // 0x003081ec
                                            charge(ctx, 3);
                                            v0 = 4;
                                            if (s1 == v0) {
                                                // 0x00308230
                                                charge(ctx, 3);
                                                s0 = 13;
                                            } else {
                                                // 0x003081f8
                                                charge(ctx, 3);
                                                v0 = 2;
                                                if (s1 == v0) {
                                                    // 0x00308224
                                                    charge(ctx, 3);
                                                    s0 = 12;
                                                } else {
                                                    // 0x00308204
                                                    charge(ctx, 3);
                                                    v0 = 1;
                                                    if (s1 == v0) {
                                                        // 0x00308218
                                                        charge(ctx, 3);
                                                        s0 = 10;
                                                    } else {
                                                        // 0x00308210
                                                        charge(ctx, 2);
                                                        // 0x003082b4
                                                        charge(ctx, 5);
                                                        a0 = 0x6A0000;
                                                        a0 = addiu(a0, -21888);  // "datCalc.c"
                                                        a1 = 3817;
                                                        jal(ctx, 0x3082C0u, gen::fn_sub_19D3F0_0019d3f0);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x003082c8
    charge(ctx, 1);
    v0 = s0;
    // 0x003082cc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------
namespace p3fes::recomp_gen {
using namespace p3fes::game;
}  // namespace p3fes::recomp_gen
