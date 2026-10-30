// The Velvet Room persona fusion code (fclCombine.c / fclCombineMisc.c / fclCombineList.c; fusion.h has the data each
// function works on and the register contract; docs/ANALYSIS/27_unmapped_bands.md §8, band 0x3D02E0-0x3DF49C).
//
// Cycle model (ADR-0013): every charge() below is one `ctx.cycles += N` block of the recompiled body in
// recomp/generated; backedge() sits wherever that body has a check point on a backward jump. Loops whose test block
// comes first ("goto test" in the recompiled body) charge the test block, then take the check point before every
// pass through the body. A block that ends in a `jal` is charged in full before the call (the recompiler keeps the
// call inside its block), so a call's return continues in the same block.
//
// Registers: register-faithful (fusion.h). Each body runs on the Cpu view of the guest context: one variable per GPR
// (64-bit writes keep bits 64..127, as the EE does; the prologue / epilogue spills are 128-bit), the FPU and HI/LO
// operations through the runtime's own instruction semantics. Inside a block a register may be computed in one
// expression where the original took two or three instructions (the sign-extension pairs `dsll32 / dsra32`, the
// `* 14` of a persona-table index): only the final value of a register is observable, at the block's end, its calls
// and its check point. Loads and stores stay in the original order.
#include "p3fes/game/fusion.h"

#include "p3fes_recomp_rt.h"

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);   // K_Assert(file, line): `jr $ra` in retail
void fn_memset_00521408(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);   // RpRandom
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);   // the scenario mode (The Answer)
void fn_clndGetCurrentMoonPhase_00181b10(p3fes::EEContext&);
void fn_sub_16C470_0016c470(p3fes::EEContext&);   // the level of party member a0 (1 = the hero)
void fn_sub_16DBA0_0016dba0(p3fes::EEContext&);   // the social link rank of a link id
void fn_sub_16DEB0_0016deb0(p3fes::EEContext&);   // arcana -> social link id
void fn_sub_16E100_0016e100(p3fes::EEContext&);   // the social link has started
void fn_sub_174A90_00174a90(p3fes::EEContext&);   // the hero's persona count
void fn_sub_175410_00175410(p3fes::EEContext&);   // the hero's persona of slot a0
void fn_sub_1749A0_001749a0(p3fes::EEContext&);   // the hero holds persona id a0
void fn_sub_174B40_00174b40(p3fes::EEContext&);   // the hero's persona list: remove id a0
void fn_sub_174E20_00174e20(p3fes::EEContext&);   // the hero's persona list: a free / matching slot for id a0
void fn_sub_175130_00175130(p3fes::EEContext&);   // the hero's persona list: id a0 (re)registered
void fn_sub_1752B0_001752b0(p3fes::EEContext&);   // the hero's current persona id
void fn_sub_176680_00176680(p3fes::EEContext&);   // persona instance init from an id
void fn_sub_176840_00176840(p3fes::EEContext&);   // persona: the skill count
void fn_sub_176990_00176990(p3fes::EEContext&);   // persona: the slot of a skill (-1 none)
void fn_sub_176A30_00176a30(p3fes::EEContext&);   // persona: add a skill
void fn_sub_176AC0_00176ac0(p3fes::EEContext&);   // persona: inherit from the ingredients
void fn_sub_176C80_00176c80(p3fes::EEContext&);   // persona: copy the experience
void fn_sub_3C3F80_003c3f80(p3fes::EEContext&);   // social band: the link counter
void fn_sub_3C44D0_003c44d0(p3fes::EEContext&);   // [nmListCreate] (RwHeapMalloc, kept recompiled)
void fn_sub_3C45F0_003c45f0(p3fes::EEContext&);   // [nmListDestroy] (RwFree, kept recompiled)
void fn_nmListAppendNew_003c4910(p3fes::EEContext&);   // [nmListAppendNew]
void fn_nmListRemoveFiltered_003c4e70(p3fes::EEContext&);   // [nmListRemoveFiltered]
void fn_nmSequenceAddStep_003c5240(p3fes::EEContext&);   // [nmSequenceAddStep]
void fn_nmObjPayloadWord12_003c5460(p3fes::EEContext&);   // [nmObjPayloadWord12]
void fn_sub_3C5470_003c5470(p3fes::EEContext&);   // [nmNodePayloadWord40]
void fn_nmSequenceCallAll36_003c5760(p3fes::EEContext&);   // [nmSequenceCallAll36]
void fn_nmCmdListDestroy_003c5a20(p3fes::EEContext&);   // [nmCmdListDestroy]
void fn_nmCmdListDraw_003c6380(p3fes::EEContext&);   // [nmCmdListDraw]
void fn_nmCmdListClose_003c6f10(p3fes::EEContext&);   // [nmCmdListClose]
void fn_nmCmdListCloseNow_003c6f50(p3fes::EEContext&);   // [nmCmdListCloseNow]
void fn_sub_3D74F0_003d74f0(p3fes::EEContext&);   // the skill inheritance (fusion_menu.cpp)
void fn_sub_3DDB00_003ddb00(p3fes::EEContext&);   // the list's persona panel draw
void fn_sub_3DE160_003de160(p3fes::EEContext&);   // the list's status panel draw
void fn_sub_3DFAC0_003dfac0(p3fes::EEContext&);   // facility elements: the owner's element state
void fn_sub_3DFF00_003dff00(p3fes::EEContext&);   // facility elements: destroy a list
void fn_sub_3E0650_003e0650(p3fes::EEContext&);   // facility elements: remove the finished
void fn_sub_3E0680_003e0680(p3fes::EEContext&);   // facility elements: call fn(list, elem, arg) on each
// this slice (called through their entry points, as the original's jal)
void fn_sub_3D5510_003d5510(p3fes::EEContext&);
void fn_sub_3D5A40_003d5a40(p3fes::EEContext&);
void fn_sub_3D5BB0_003d5bb0(p3fes::EEContext&);
void fn_sub_3D5E60_003d5e60(p3fes::EEContext&);
void fn_sub_3D6200_003d6200(p3fes::EEContext&);
void fn_sub_3D64A0_003d64a0(p3fes::EEContext&);
void fn_sub_3D6740_003d6740(p3fes::EEContext&);
void fn_sub_3D6910_003d6910(p3fes::EEContext&);
void fn_sub_3D6AE0_003d6ae0(p3fes::EEContext&);
void fn_sub_3D6E60_003d6e60(p3fes::EEContext&);
void fn_sub_3D7A30_003d7a30(p3fes::EEContext&);
void fn_sub_3D7AC0_003d7ac0(p3fes::EEContext&);
void fn_sub_3D7DA0_003d7da0(p3fes::EEContext&);
void fn_sub_3D8370_003d8370(p3fes::EEContext&);
void fn_sub_3DA3E0_003da3e0(p3fes::EEContext&);
void fn_sub_3DED40_003ded40(p3fes::EEContext&);
void fn_sub_3DF090_003df090(p3fes::EEContext&);
void fn_sub_3DF220_003df220(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {
namespace fusion::detail {

namespace gen = ::p3fes::recomp_gen;

// The sign-extension idioms of the band (`dsll32 x, n; dsra32 x, m`): the low 16 bits / the low 10 bits as a signed
// value, and one bit as 0 / -1.
constexpr u64 seh(u64 x) { return dsra32(dsll32(x, 16), 16); }
constexpr u64 sext10(u64 x) { return dsra32(dsll32(x, 22), 22); }
constexpr u64 bit_of(u64 x, unsigned b) { return dsra32(dsll32(x, 31 - b), 31); }  // b < 32
// `sll t, x, 3; subu t, t, x; sll t, t, 1`: x * 14, the persona-table stride
constexpr u64 mul14(u64 x) { return sll(subu(sll(x, 3), x), 1); }
// `sll t, x, 1; addu t, t, x; sll t, t, 2`: x * 12, the stock-list stride
constexpr u64 mul12(u64 x) { return sll(addu(sll(x, 1), x), 2); }
// `sll t, x, 2; addu t, t, x; sll t, t, 1; addu t, t, x; sll t, t, 1`: x * 22, the arcana-chart stride
constexpr u64 mul22(u64 x) { return sll(addu(sll(addu(sll(x, 2), x), 1), x), 1); }

// --- the Cpu helpers the header declares ------------------------------------------------------------------------------
void Cpu::k_assert(u32 file, u32 line, u32 pc) {
    a0 = sx(file);  // lui a0, 0x6A; addiu a0, a0, file
    a1 = line;
    jal(pc, gen::fn_sub_19D3F0_0019d3f0);
}

void Cpu::open_frame(u32 size, u32 ra_off, u32 s_base, unsigned n) {
    sp = addiu(sp, -static_cast<s32>(size));
    sd(sp + ra_off, ra);
    for (unsigned i = n; i-- > 0;) sq(sp + s_base + 16 * i, Gpr{c, i == 8 ? 30u : GPR_S0 + i});
}

void Cpu::close_frame(u32 size, u32 ra_off, u32 s_base, unsigned n) {
    ra = ld(sp + ra_off);
    for (unsigned i = n; i-- > 0;) {
        Gpr s{c, i == 8 ? 30u : GPR_S0 + i};
        lq(s, sp + s_base + 16 * i);
    }
    sp = addiu(sp, static_cast<s32>(size));
}

// The bodies, named as the functions they are (fusion.h documents each).
class Fu : public Cpu {
public:
    using Cpu::Cpu;

    // [fclCombine.c]
    void sub_3D02E0();
    void sub_3D0600();
    void sub_3D21D0();
    void sub_3D25C0();
    void take_step(s32 slot, u32 pc);
    void sub_3D2640();
    void sub_3D26C0();
    void payload_nop(u32 pc);
    void sub_3D2710();
    void sub_3D2C00();
    void sub_3D2DD0();
    void sub_3D2EF0();
    void sub_3D3010();
    void sub_3D3280();
    void sub_3D35C0();
    void sub_3D3B70();
    void sub_3D3C20();
    void sub_3D3CA0();
    // [fclCombineMisc.c]
    void sub_3D5510();
    void sub_3D5730();
    void sub_3D5850();
    void sub_3D58A0();
    void sub_3D58C0();
    void sub_3D5A40();
    void sub_3D5BB0();
    void sub_3D5C90();
    void sub_3D5CD0();
    void sub_3D5DC0();
    void sub_3D5E60();
    void sub_3D6200();
    void sub_3D64A0();
    void sub_3D6740();
    void sub_3D6910();
    void sub_3D6AE0();
    void sub_3D6C90();
    void sub_3D6E60();
    void sub_3D6F80();
    void sub_3D7180();
    void sub_3D71D0();
    void sub_3D72F0();
    void sub_3D74B0();
    void sub_3D7A30();
    void find_result(bool up, u32 line, u32 pc1, u32 pc2, u32 pc3);
    void sub_3D7AC0();
    void sub_3D7DA0();
    void sub_3D8080();
    void sub_3D8230();
    void sub_3D8260();
    void sub_3D8370();
    void sub_3D84C0();
    void sub_3D8630();
    void sub_3D8830();
    // [fclCombineList.c]
    void sub_3D9C90();
    void sub_3DA2A0();
    void sub_3DA3A0();
    void sub_3DA3E0();
    void sub_3DA470();
    void sub_3DA570();
    void sub_3DB580();
    void sub_3DB5E0();
    void sub_3DC210();
    void sub_3DEB20();
    void sub_3DEB80();
    void sub_3DEC00();
    void sub_3DECD0();
    void sub_3DED40();
    void sub_3DED70();
    void sub_3DEE80();
    void sub_3DEF10();
    void sub_3DEF40();
    void sub_3DEF80();
    void sub_3DF010();
    void sub_3DF090();
    void sub_3DF100();
    void sub_3DF220();
};

// =====================================================================================================================
// [fclCombineMisc.c] the fusion rules
// =====================================================================================================================

// sub_3D5510 [fclCombineMatchRecipe]: $a0 the 40-byte match record (+0 flags, +8 the matched stock personas[8]),
// $a1 the recipe, $a2 how many ingredients must match, $a3 the stock list. For each non-zero ingredient (bits 0..9 a
// persona id, or with bit 14 an arcana) takes the first stock entry not used yet whose persona id (arcana) matches;
// sets flag bit 0 when a "must be present" ingredient (bit 15) found nothing or fewer than $a2 matched. Returns 1, or 0
// for an empty recipe.
void Fu::sub_3D5510() {
    enter(12);
    open_frame(80, 64, 0, 4);
    s3 = a0;  // out
    s2 = a1;  // recipe
    s1 = a2;  // need
    s0 = a3;  // stock
    if (s3 == 0 || (charge(2), s2 == 0) || (charge(2), s0 == 0)) {
        charge(5);
        k_assert(kCombineMiscFile, 40, 0x3d555c);
    }
    charge(3);
    v0 = lhu(s2);
    if (v0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(7);
        t5 = 0;          // matched count
        t1 = 0;          // used stock mask
        t0 = addiu(s2, 4);
        t4 = 0;          // ingredient index
        v1 = 1;
        for (;;) {
            charge(5);
            t6 = seh(t4);
            v0 = slti(t6, 8);
            if (v0 == 0) break;
            backedge();
            charge(8);
            a3 = addiu(addu(t0, sll(t6, 1)), 4);  // &recipe->ingredients[i]
            v0 = lh(a3);
            a2 = sext10(v0);                      // the persona id (or arcana)
            if (a2 != 0) {
                charge(5);
                t2 = 0;                           // found
                t3 = 0;                           // stock index
                a1 = lw(gp - 18640);              // the persona table
                for (;;) {
                    charge(5);
                    a0 = seh(t3);
                    v0 = slti(a0, 12);
                    if (v0 == 0) break;
                    backedge();
                    charge(7);
                    v0 = addu(s0, mul12(a0));
                    a0 = lw(v0 + 4);              // stock[j].persona
                    bool next = a0 == 0;
                    if (!next) {
                        charge(7);
                        v0 = seh(t3);
                        s2 = lhu(a0 + 2);         // its id
                        v0 = sllv(v1, v0);        // 1 << j
                        t7 = t1 & v0;
                        next = t7 != 0;
                    }
                    if (!next) {
                        charge(5);
                        t7 = lb(a3 + 1);
                        t7 = bit_of(t7, 6);       // bit 14: match the arcana
                        if (t7 != 0) {
                            charge(6);
                            s2 = s2 & 0xffffu;
                            t7 = addu(a1, mul14(s2));
                            s2 = lbu(t7 + 2);
                        }
                        charge(3);
                        t7 = s2 & 0xffffu;
                        next = t7 != a2;
                    }
                    if (!next) {
                        charge(10);
                        a1 = addu(s3, sll(t6, 2));
                        sw(a1 + 8, a0);           // out->matched[i] = persona
                        t1 = t1 | v0;
                        v0 = addiu(t5, 1);
                        t5 = seh(v0);             // ++matched
                        t2 = v1;
                        break;
                    }
                    charge(3);
                    v0 = addiu(t3, 1);
                    t3 = seh(v0);
                }
                charge(5);
                v0 = lb(a3 + 1);
                v0 = bit_of(v0, 7);               // bit 15: must be present
                if (v0 != 0) {
                    charge(4);
                    v0 = seh(t2);
                    if (v0 == 0) {
                        charge(3);
                        v0 = lw(s3);
                        v0 = v0 | 0x1u;
                        sw(s3, v0);
                    }
                }
            }
            charge(3);
            v0 = addiu(t4, 1);
            t4 = seh(v0);
        }
        charge(5);
        v0 = seh(t5);
        v0 = slt(v0, s1);
        if (v0 == 0) {
            charge(3);
            v0 = 1;
        } else {
            charge(4);
            v0 = lw(s3);
            v0 = v0 | 0x1u;
            sw(s3, v0);
            v0 = 1;
        }
    }
    charge(8);
    close_frame(80, 64, 0, 4);
}

// sub_3D5730 [fclCombineGetRecipe]: $a0 the 40-byte match record, $a1 the category (0..4: 2..6 ingredients), $a2 the
// recipe index, $a3 the stock list. 0 past the category's count, for an unavailable result (sub_3D5BB0) or an empty
// recipe; else clears the record, stores the recipe at +4 and returns sub_3D5510(record, recipe, category + 2, stock).
void Fu::sub_3D5730() {
    enter(12);
    open_frame(80, 64, 0, 4);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = a3;
    if (s3 == 0) {
        charge(5);
        k_assert(kCombineMiscFile, 88, 0x3d576c);
    }
    charge(8);
    v1 = sll(s2, 3);
    v0 = addu(addiu(lui(0x6a), 24388), v1);
    v0 = lw(v0);  // categories[category].count
    at = slt(s1, v0);
    if (at == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(11);
        v0 = addu(addiu(lui(0x6a), 24384), v1);
        v1 = sll(s1, 5);
        v0 = lw(v0);  // categories[category].table
        s1 = addu(v0, v1);
        a0 = lhu(s1);
        jal(0x3d57bc, gen::fn_sub_3D5BB0_003d5bb0);
        if (v0 == 0) {
            charge(3);
            v0 = 0;
        } else {
            charge(3);
            v0 = lhu(s1);
            if (v0 == 0) {
                charge(3);
                v0 = 0;
            } else {
                charge(14);
                a0 = s3;
                a1 = 0;
                a2 = 40;
                jal(0x3d57fc, gen::fn_memset_00521408);
                sw(s3 + 4, s1);
                a2 = addiu(s2, 2);
                a0 = s3;
                a1 = s1;
                a3 = s0;
                jal(0x3d5818, gen::fn_sub_3D5510_003d5510);
                v0 = seh(v0);
            }
        }
    }
    charge(8);
    close_frame(80, 64, 0, 4);
}

// sub_3D5850 [fclCombineTable6A5FC0]: copies the five words at 0x6A5FC0 into a 32-byte frame and returns word $a0
// (no bounds check: an index past 4 reads the frame or the caller's stack).
void Fu::sub_3D5850() {
    enter(5);
    sp = addiu(sp, -32);
    a2 = addiu(lui(0x6a), 24512);
    a1 = addiu(sp, 0);
    v1 = 5;
    for (;;) {
        charge(7);
        v0 = lw(a2);
        a2 = addiu(a2, 4);
        v1 = addiu(v1, -1);
        sw(a1, v0);
        a1 = addiu(a1, 4);
        if (sgn(v1) <= 0) break;
        backedge();
    }
    charge(6);
    v0 = addu(sll(a0, 2), sp);
    v0 = lw(v0);
    sp = addiu(sp, 32);
}

// sub_3D58A0: a tail wrapper of sub_3C3F80 in its own 16-byte frame.
void Fu::sub_3D58A0() {
    enter(8);
    open_frame(16, 0, 0, 0);
    jal(0x3d58a8, gen::fn_sub_3C3F80_003c3f80);
    close_frame(16, 0, 0, 0);
}

// sub_3D58C0 [fclCombineCalcPrice]: $a0 a social link id (s16), $a1 a level. With r = rank(link) / 2.5 + 1 (the rank
// from sub_16DBA0, read three times) and L = level: x = (L + r)^3 - L^3, then
// (int)(x * gp[-32084] + (gp[-31980] - gp[-31984] * L) + 15) through ACC (adda / msub / adda / madd). $f20 is
// spilled at sp + 0 and restored. One block: the three calls are inside it.
void Fu::sub_3D58C0() {
    static constexpr u32 kPc[3] = {0x3d58e4, 0x3d5930, 0x3d5980};
    enter(94);
    open_frame(64, 48, 16, 2);
    swc1(F20, sp);
    s1 = a0;
    s0 = a1;
    for (int k = 0; k < 3; ++k) {
        a0 = seh(s1);
        jal(kPc[k], gen::fn_sub_16DBA0_0016dba0);
        mtc1(v0, F0);
        cvt_s_w(F1, F0);
        v0 = lui(0x4020u);  // 2.5f
        mtc1(v0, F0);
        div_s(F1, F1, F0);
        v0 = lui(0x3f80u);  // 1.0f
        mtc1(v0, F0);
        add_s(F1, F0, F1);  // r
        mtc1(s0, F0);
        if (k == 0) {
            cvt_s_w(F0, F0);
            add_s(F20, F0, F1);     // L + r
        } else if (k == 1) {
            cvt_s_w(F0, F0);
            add_s(F0, F0, F1);
            mul_s(F20, F20, F0);    // (L + r)^2
        } else {
            cvt_s_w(F4, F0);        // L
            add_s(F0, F4, F1);
            mul_s(F1, F0, F20);     // (L + r)^3
        }
    }
    mult(v0, s0, s0);
    mult(v0, s0, v0);               // L^3
    mtc1(v0, F0);
    cvt_s_w(F0, F0);
    sub_s(F1, F1, F0);
    lwc1(F0, gp - 32084);
    mul_s(F3, F0, F1);
    lwc1(F2, gp - 31984);
    lwc1(F0, gp - 31980);
    mtc1(zero, F1);
    adda_s(F1, F0);
    msub_s(F2, F2, F4);
    v0 = lui(0x4170u);              // 15.0f
    mtc1(v0, F0);
    adda_s(F1, F0);
    madd_s(F0, F2, F3);
    cvt_w_s(F0, F0);
    mfc1(v0, F0);
    ra = ld(sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F20, sp);
    sp = addiu(sp, 64);
}

// sub_3D5A40 [fclCombineRecipeMask]: $a0 the recipe, $a1 how many ingredients must match (unused), $a2 a u16 persona-id
// array, $a3 its length, $t0 an optional s16 out (the matched count). The sub_3D5510 walk over a plain id array: returns
// the mask of the array entries the ingredients took, 0 for an empty recipe or when a "must be present" ingredient
// found nothing (then the count is not stored).
void Fu::sub_3D5A40() {
    enter(3);
    v0 = lhu(a0);
    if (v0 == 0) {
        charge(3);
        v0 = 0;
        charge(2);
        return;
    }
    charge(8);
    t7 = 0;          // matched count
    v0 = 0;          // used mask
    t3 = addiu(a0, 4);
    t6 = 0;          // ingredient index
    t2 = lw(gp - 18640);
    a0 = 1;
    for (;;) {
        charge(5);
        a1 = seh(t6);
        v1 = slti(a1, 8);
        if (v1 == 0) break;
        backedge();
        charge(8);
        v1 = addu(t3, sll(a1, 1));
        t1 = addiu(v1, 4);   // &recipe->ingredients[i]
        v1 = lh(v1 + 4);
        a1 = sext10(v1);
        if (a1 != 0) {
            charge(4);
            t4 = 0;          // found
            t5 = 0;          // array index
            for (;;) {
                charge(5);
                t8 = seh(t5);
                v1 = slt(t8, a3);
                if (v1 == 0) break;
                backedge();
                charge(4);
                v1 = sllv(a0, t8);
                t9 = v0 & v1;
                if (t9 == 0) {
                    charge(5);
                    t9 = lb(t1 + 1);
                    t9 = bit_of(t9, 6);
                    if (t9 != 0) {
                        charge(10);
                        t8 = addu(a2, sll(t8, 1));
                        t9 = lhu(t8);
                        t8 = addu(t2, mul14(t9));
                        t8 = lbu(t8 + 2);     // the persona's arcana
                    } else {
                        charge(3);
                        t8 = addu(a2, sll(t8, 1));
                        t8 = lhu(t8);
                    }
                    charge(3);
                    t8 = t8 & 0xffffu;
                    if (t8 == a1) {
                        charge(7);
                        v0 = v0 | v1;
                        v1 = addiu(t7, 1);
                        t7 = seh(v1);
                        t4 = a0;
                        break;
                    }
                }
                charge(3);
                v1 = addiu(t5, 1);
                t5 = seh(v1);
            }
            charge(5);
            v1 = lb(t1 + 1);
            v1 = bit_of(v1, 7);
            if (v1 != 0) {
                charge(4);
                v1 = seh(t4);
                if (v1 == 0) {
                    charge(3);
                    v0 = 0;
                    charge(2);
                    return;
                }
            }
        }
        charge(3);
        v1 = addiu(t6, 1);
        t6 = seh(v1);
    }
    charge(2);
    if (t0 != 0) {
        charge(1);
        sh(t0, t7);
    }
    charge(2);
}

// sub_3D5BB0 [fclCombineIsPersonaAvailable]: $a0 a persona id. Walks the 67 rules at 0x6A5410: a rule for this persona
// with mode bit 0 makes it unavailable while its flag is clear; one with mode bit 1 makes it unavailable unless such a
// flag is set (1 at the first set flag). Personas without rules are available.
void Fu::sub_3D5BB0() {
    enter(10);
    open_frame(64, 48, 0, 3);
    s1 = 1;              // result when no rule decides
    s2 = 0;              // rule index
    s0 = a0 & 0xffffu;
    for (;;) {
        charge(3);
        v0 = sltiu(s2, 67);
        if (v0 == 0) break;
        backedge();
        charge(7);
        v1 = sll(s2, 3);
        a0 = addu(addiu(lui(0x6a), 21520), v1);  // &rules[i]
        v0 = lh(a0 + 4);
        if (s0 == v0) {
            charge(4);
            v1 = lh(a0 + 6);
            v0 = v1 & 0x1u;
            if (v0 != 0) {
                charge(5);
                a0 = lw(a0);
                jal(0x3d5c08, gen::fn_datGetFlag_0016f190);
                if (v0 == 0) {
                    charge(3);
                    v0 = 0;
                    charge(7);
                    close_frame(64, 48, 0, 3);
                    return;
                }
            } else {
                charge(3);
                v0 = v1 & 0x2u;
                if (v0 != 0) {
                    charge(7);
                    s1 = 0;
                    a0 = lw(a0);
                    jal(0x3d5c38, gen::fn_datGetFlag_0016f190);
                    v1 = 1;
                    if (v0 == v1) {
                        charge(3);
                        v0 = v1;
                        charge(7);
                        close_frame(64, 48, 0, 3);
                        return;
                    }
                }
            }
        }
        charge(1);
        s2 = addiu(s2, 1);
    }
    charge(1);
    v0 = s1;
    charge(7);
    close_frame(64, 48, 0, 3);
}

// sub_3D5C90 [fclCombineGetScenarioWord]: 0x6A4E10 in The Answer (sub_17D800 != 0), else 0x6A4BA0 (the address).
void Fu::sub_3D5C90() {
    enter(6);
    open_frame(16, 0, 0, 0);
    jal(0x3d5c98, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        charge(4);
        v0 = addiu(lui(0x6a), 19984);
    } else {
        charge(2);
        v0 = addiu(lui(0x6a), 19360);
    }
    charge(4);
    close_frame(16, 0, 0, 0);
}

// sub_3D5CD0 [fclCombineBuildStock]: $a0 the 144-byte stock list. Clears it, then for every slot below the hero's
// persona count (sub_175410) that holds a persona (sub_174A90) appends {0, persona, &table[persona->id]}. Returns the
// entry count.
void Fu::sub_3D5CD0() {
    enter(15);
    open_frame(80, 64, 0, 4);
    s2 = a0;  // stock
    s0 = 0;   // entries
    a1 = 0;
    a2 = 144;
    jal(0x3d5cf8, gen::fn_memset_00521408);
    s1 = 0;   // slot
    for (;;) {
        charge(8);
        s3 = seh(s1);
        jal(0x3d5d7c, gen::fn_sub_175410_00175410);
        v0 = v0 & 0xffffu;
        v0 = slt(s3, v0);
        if (v0 == 0) break;
        backedge();
        charge(5);
        a0 = s1;
        jal(0x3d5d10, gen::fn_sub_174A90_00174a90);
        if (v0 != 0) {
            charge(18);
            a0 = seh(s0);
            v1 = mul12(a0);
            a0 = addu(s2, v1);       // &stock[n]
            sw(a0, zero);
            sw(a0 + 4, v0);          // the persona
            v1 = lhu(v0 + 2);
            v1 = mul14(v1);
            v0 = lw(gp - 18640);
            v0 = addu(v0, v1);
            sw(a0 + 8, v0);          // its table record
            v0 = addiu(s0, 1);
            s0 = seh(v0);
        }
        charge(3);
        v0 = addiu(s1, 1);
        s1 = seh(v0);
    }
    charge(10);
    v0 = seh(s0);
    close_frame(80, 64, 0, 4);
}

// sub_3D5DC0 [fclCombineRankLetter]: $a0 a persona id. The s16 at 0x6A53B0 + 2 * rank, where rank is the social link
// rank of the persona's arcana (sub_16DEB0 -> sub_16DBA0) once that link has started (sub_16E100), else 0.
void Fu::sub_3D5DC0() {
    enter(19);
    open_frame(48, 32, 0, 2);
    s0 = 0;
    v1 = a0 & 0xffffu;
    s1 = mul14(v1);
    v0 = lw(gp - 18640);
    v0 = addu(s1, v0);
    a0 = lbu(v0 + 2);   // arcana
    jal(0x3d5df0, gen::fn_sub_16DEB0_0016deb0);
    a0 = v0;
    jal(0x3d5dfc, gen::fn_sub_16E100_0016e100);
    if (v0 != 0) {
        charge(10);
        v0 = lw(gp - 18640);
        v0 = addu(s1, v0);
        a0 = lbu(v0 + 2);
        jal(0x3d5e18, gen::fn_sub_16DEB0_0016deb0);
        a0 = v0;
        jal(0x3d5e24, gen::fn_sub_16DBA0_0016dba0);
        s0 = dsra32(dsll32(v0, 24), 24);  // (s8)
    }
    charge(11);
    v1 = sll(s0, 1);
    v0 = addu(addiu(lui(0x6a), 21424), v1);
    v0 = lh(v0);
    close_frame(48, 32, 0, 2);
}

// sub_3D5E60 [fclCombineTriangleArcana]: $a0..$a2 three personas. Copies them into a 16-byte frame array and sorts it
// with the three compare-and-swap steps of the 6-byte pair table at gp - 21856 (retail: {0,2}, {0,1}, {1,2}): the
// pair swaps when the first's level (+4) is lower, or equal with a lower arcana -- the highest persona ends first. Then the arcana r of the two lower ones on
// the triangle chart 0x6A58E9 and r with the highest one's arcana on 0x6A5AD9 (0 when either step has none).
void Fu::sub_3D5E60() {
    enter(9);
    open_frame(96, 48, 0, 3);
    v1 = addiu(sp, 64);
    v0 = 16;
    if (v1 != 0) {  // the inlined memset of the array (16 bytes)
        for (;;) {
            charge(7);
            sb(v1, zero);
            v1 = addiu(v1, 1);
            v0 = addiu(v0, -1);
            if (v0 == 0) break;
            backedge();
        }
    }
    charge(6);
    sw(sp + 64, a0);
    sw(sp + 68, a1);
    sw(sp + 72, a2);
    t1 = addiu(gp, -21856);
    t0 = addiu(sp, 88);
    a3 = 3;
    for (;;) {  // copy the 6-byte pair table into the frame
        charge(9);
        v1 = lb(t1);
        v0 = lb(t1 + 1);
        t1 = addiu(t1, 2);
        a3 = addiu(a3, -1);
        sb(t0, v1);
        sb(t0 + 1, v0);
        t0 = addiu(t0, 2);
        if (sgn(a3) <= 0) break;
        backedge();
    }
    charge(2);
    if (a0 == 0 || (charge(2), a1 == 0) || (charge(2), a2 == 0)) {
        charge(5);
        k_assert(kCombineMiscFile, 305, 0x3d5f00);
    }
    charge(4);
    a0 = 0;
    v1 = lw(gp - 18640);
    for (;;) {
        charge(5);
        v0 = seh(a0);
        v0 = slti(v0, 3);
        if (v0 == 0) break;
        backedge();
        charge(20);
        v0 = addu(sll(seh(a0), 1), sp);
        a1 = addiu(v0, 88);              // &pairs[k]
        v0 = lb(a1 + 1);
        v0 = addiu(addu(sll(v0, 2), sp), 64);
        t0 = lw(v0);                     // p[pairs[k].second]
        a3 = lbu(t0 + 4);
        v0 = lb(a1);
        v0 = addiu(addu(sll(v0, 2), sp), 64);
        v0 = lw(v0);                     // p[pairs[k].first]
        a2 = lbu(v0 + 4);
        a1 = slt(a2, a3);
        bool swap = a1 != 0;
        if (!swap) {
            charge(2);
            if (a2 == a3) {
                charge(15);
                a2 = lhu(v0 + 2);
                a1 = addu(v1, mul14(a2));
                a3 = lbu(a1 + 2);
                a2 = lhu(t0 + 2);
                a1 = addu(v1, mul14(a2));
                a1 = lbu(a1 + 2);
                at = slt(a1, a3);
                swap = at != 0;
            }
        }
        if (swap) {
            charge(18);
            a1 = addu(sll(seh(a0), 1), sp);
            a3 = addiu(a1, 88);
            a1 = lb(a3);
            a2 = addiu(addu(sll(a1, 2), sp), 64);
            sw(sp + 76, v0);
            v0 = lb(a3 + 1);
            a1 = addiu(addu(sll(v0, 2), sp), 64);
            v0 = lw(a1);
            sw(a2, v0);
            v0 = lw(sp + 76);
            sw(a1, v0);
        }
        charge(3);
        v0 = addiu(a0, 1);
        a0 = seh(v0);
    }
    charge(25);
    v0 = lw(gp - 18640);
    a0 = addiu(v0, 2);                   // &table[0].arcana
    v0 = lw(sp + 64);
    v1 = lhu(v0 + 2);
    v0 = addu(a0, mul14(v1));
    s2 = lbu(v0);                        // arcana of p[0]
    v0 = lw(sp + 68);
    v1 = lhu(v0 + 2);
    v0 = addu(a0, mul14(v1));
    s0 = lbu(v0);                        // arcana of p[1]
    v0 = lw(sp + 72);
    v1 = lhu(v0 + 2);
    v0 = addu(a0, mul14(v1));
    s1 = lbu(v0);                        // arcana of p[2]
    bool bad;
    if (s2 == 0) {
        bad = true;
    } else {
        charge(3);
        v0 = s0 & 0xffu;
        bad = v0 == 0;
        if (!bad) {
            charge(3);
            v0 = s1 & 0xffu;
            bad = v0 == 0;
        }
    }
    if (bad) {
        charge(5);
        k_assert(kCombineMiscFile, 322, 0x3d609c);
    }
    charge(3);
    s0 = s0 & 0xffu;
    if (s0 == 0 || (charge(3), v0 = s1 & 0xffu, v0 == 0)) {
        charge(5);
        k_assert(kCombineMiscFile, 128, 0x3d60c8);
    }
    charge(4);
    a0 = s1 & 0xffu;
    at = slt(s0, a0);
    if (at != 0) {
        charge(12);
        v1 = mul22(s0);
        v0 = addu(addiu(lui(0x6a), 22761), v1);
        v0 = addu(a0, v0);
        v0 = lbu(v0);                    // chart1[22 * p1 + p2]
    } else {
        charge(10);
        v1 = mul22(a0);
        v0 = addu(addiu(lui(0x6a), 22761), v1);
        v0 = addu(s0, v0);
        v0 = lbu(v0);                    // chart1[22 * p2 + p1]
    }
    charge(3);
    s0 = v0 & 0xffu;
    if (s0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(2);
        if (s2 == 0 || (charge(2), s0 == 0)) {
            charge(5);
            k_assert(kCombineMiscFile, 128, 0x3d616c);
        }
        charge(3);
        at = slt(s2, s0);
        if (at != 0) {
            charge(12);
            v1 = mul22(s2);
            v0 = addu(addiu(lui(0x6a), 23257), v1);
            v0 = addu(s0, v0);
            v0 = lbu(v0);                // chart2[22 * p0 + r]
        } else {
            charge(10);
            v1 = mul22(s0);
            v0 = addu(addiu(lui(0x6a), 23257), v1);
            v0 = addu(s2, v0);
            v0 = lbu(v0);                // chart2[22 * r + p0]
        }
    }
    charge(7);
    close_frame(96, 48, 0, 3);
}

// sub_3D6200 [fclCombineSpecial]: $a0 the 52-byte persona out, $a1 the category, $a2 a u16 persona-id array, $a3 its
// length. The first recipe of the category whose ingredients all match the array (sub_3D5A40, at least category + 2 of
// them) and whose result is available (the rule walk of sub_3D5BB0, inline) becomes the persona (sub_176680) with the
// recipe's skills added (sub_176990 / sub_176840) until one is refused; returns the result's arcana, 0 when no recipe
// fits. The minimum count is kept in a 128-bit frame slot (sq / lq: the whole $v0 register as it was).
void Fu::sub_3D6200() {
    enter(17);
    open_frame(208, 144, 0, 9);
    s4 = a0;  // out
    s3 = a1;  // category
    s5 = a2;  // ids
    s7 = a3;  // count
    bool bad = s4 == 0;
    if (!bad) {
        charge(2);
        bad = s5 == 0;
        if (!bad) {
            charge(3);
            v0 = slti(s3, 5);
            bad = v0 == 0;
        }
    }
    if (bad) {
        charge(5);
        k_assert(kCombineMiscFile, 335, 0x3d6264);
    }
    charge(16);
    v1 = sll(s3, 3);
    v0 = addu(addiu(lui(0x6a), 24384), v1);
    s1 = lw(v0);   // the recipe
    v0 = addu(addiu(lui(0x6a), 24388), v1);
    fp = lw(v0);   // the recipe count
    s2 = 0;
    v0 = addiu(s3, 2);
    v0 = seh(v0);
    sq(sp + 176, v0);
    for (;;) {
        charge(3);
        v0 = slt(s2, fp);
        if (v0 == 0) break;
        backedge();
        charge(15);
        sh(sp + 206, zero);
        v0 = addiu(s3, 2);
        a1 = seh(v0);
        a0 = s1;
        a2 = s5;
        a3 = s7;
        t0 = addiu(sp, 206);
        jal(0x3d62cc, gen::fn_sub_3D5A40_003d5a40);
        a0 = lh(sp + 206);
        lq(v1, sp + 176);
        v1 = slt(a0, v1);
        if (v1 != 0) {
            charge(1);
            v0 = 0;   // too few matched
        } else {
            charge(2);
        }
        charge(2);
        if (v0 != 0) {
            charge(6);
            v0 = lhu(s1);
            sq(sp + 160, v0);
            s6 = 1;
            s0 = 0;
            bool decided = false;
            for (;;) {
                charge(3);
                v0 = sltiu(s0, 67);
                if (v0 == 0) break;
                backedge();
                charge(8);
                v1 = sll(s0, 3);
                a0 = addu(addiu(lui(0x6a), 21520), v1);
                v1 = lh(a0 + 4);
                lq(v0, sp + 160);
                if (v0 == v1) {
                    charge(4);
                    v1 = lh(a0 + 6);
                    v0 = v1 & 0x1u;
                    if (v0 != 0) {
                        charge(5);
                        a0 = lw(a0);
                        jal(0x3d6348, gen::fn_datGetFlag_0016f190);
                        if (v0 == 0) {
                            charge(3);
                            v1 = 0;
                            decided = true;
                            break;
                        }
                    } else {
                        charge(3);
                        v0 = v1 & 0x2u;
                        if (v0 != 0) {
                            charge(7);
                            s6 = 0;
                            a0 = lw(a0);
                            jal(0x3d6378, gen::fn_datGetFlag_0016f190);
                            v1 = 1;
                            if (v0 == v1) {
                                charge(2);
                                decided = true;
                                break;
                            }
                        }
                    }
                }
                charge(1);
                s0 = addiu(s0, 1);
            }
            if (!decided) {
                charge(1);
                v1 = s6;
            }
            charge(2);
            if (v1 != 0) {
                // the result: the persona and the recipe's skills
                charge(7);
                a0 = s4;
                a1 = lhu(s1);
                jal(0x3d63b8, gen::fn_sub_176680_00176680);
                s0 = 0;
                for (;;) {
                    charge(3);
                    v0 = slti(s0, 4);
                    if (v0 == 0) break;
                    backedge();
                    charge(6);
                    v0 = addu(s1, sll(s0, 1));
                    s2 = addiu(v0, 24);
                    a1 = lhu(v0 + 24);
                    if (a1 != 0) {
                        charge(6);
                        a0 = s4;
                        jal(0x3d63e8, gen::fn_sub_176990_00176990);
                        v1 = si(-1);
                        if (v0 == v1) {
                            charge(6);
                            a0 = s4;
                            a1 = lhu(s2);
                            jal(0x3d6404, gen::fn_sub_176840_00176840);
                            if (v0 == 0) break;
                        }
                    }
                    charge(1);
                    s0 = addiu(s0, 1);
                }
                charge(9);
                v1 = lhu(s4 + 2);
                v1 = mul14(v1);
                v0 = lw(gp - 18640);
                v0 = addu(v1, v0);
                v0 = lbu(v0 + 2);
                charge(13);
                close_frame(208, 144, 0, 9);
                return;
            }
        }
        charge(2);
        s1 = addiu(s1, 32);
        s2 = addiu(s2, 1);
    }
    charge(1);
    v0 = 0;
    charge(13);
    close_frame(208, 144, 0, 9);
}

// sub_3D64A0 [fclCombineNormal]: $a0 the 52-byte persona out, $a1 / $a2 two persona ids. A special recipe of two
// (sub_3D6200 category 0) wins: returns 2. Else the arcana r from the normal chart 0x6A56B9; none -> the out is cleared,
// 0. Target level = (level0 + level1) / 2 + 1 (C division, u8). When both ingredients are of arcana r the result is the
// best persona of r at or below the target (sub_3D7DA0), else the first at or above it (sub_3D7AC0), the two
// ingredients excluded (a 24-byte id list in the frame); found -> the persona (sub_176680), 1; else 0.
void Fu::sub_3D64A0() {
    enter(15);
    open_frame(144, 96, 0, 6);
    s4 = a0;  // out
    s3 = a1;  // id0
    s2 = a2;  // id1
    sh(sp + 140, s3);
    sh(sp + 142, s2);
    bool bad = s4 == 0;
    if (!bad) {
        charge(3);
        v0 = s3 & 0xffffu;
        bad = v0 == 0;
        if (!bad) {
            charge(3);
            v0 = s2 & 0xffffu;
            bad = v0 == 0;
        }
    }
    if (bad) {
        charge(5);
        k_assert(kCombineMiscFile, 373, 0x3d6500);
    }
    charge(9);
    a0 = s4;
    a1 = 0;
    a2 = addiu(sp, 140);
    a3 = 2;
    jal(0x3d6518, gen::fn_sub_3D6200_003d6200);
    v0 = v0 & 0xffu;
    if (v0 != 0) {
        charge(3);
        v0 = 2;
        charge(10);
        close_frame(144, 96, 0, 6);
        return;
    }
    charge(16);
    v1 = s2 & 0xffffu;
    s1 = mul14(v1);
    v0 = lw(gp - 18640);
    a0 = addiu(v0, 2);
    v0 = addu(a0, s1);
    s5 = lbu(v0);                 // arcana of id1
    v1 = s3 & 0xffffu;
    v0 = addu(a0, mul14(v1));
    s0 = lbu(v0);                 // arcana of id0
    if (s0 == 0 || (charge(3), v0 = s5 & 0xffu, v0 == 0)) {
        charge(5);
        k_assert(kCombineMiscFile, 128, 0x3d6590);
    }
    charge(4);
    a0 = s5 & 0xffu;
    at = slt(s0, a0);
    if (at != 0) {
        charge(12);
        v1 = mul22(s0);
        v0 = addu(addiu(lui(0x6a), 22201), v1);
        v0 = addu(a0, v0);
        v0 = lbu(v0);                 // chart[22 * a0 + a1]
    } else {
        charge(10);
        v1 = mul22(a0);
        v0 = addu(addiu(lui(0x6a), 22201), v1);
        v0 = addu(s0, v0);
        v0 = lbu(v0);                 // chart[22 * a1 + a0]
    }
    charge(3);
    s0 = v0 & 0xffu;              // r
    if (s0 == 0) {
        charge(8);
        a0 = s4;
        a1 = 0;
        a2 = 52;
        jal(0x3d6618, gen::fn_memset_00521408);
        v0 = 0;
        charge(10);
        close_frame(144, 96, 0, 6);
        return;
    }
    charge(21);
    a0 = addiu(sp, 112);
    a1 = 0;
    a2 = 24;
    jal(0x3d6638, gen::fn_memset_00521408);
    sh(sp + 112, s3);             // the exclusion list
    sh(sp + 114, s2);
    a2 = lw(gp - 18640);
    a1 = addiu(a2, 3);
    v1 = s3 & 0xffffu;
    a0 = mul14(v1);
    v0 = addu(a1, a0);
    v1 = lbu(v0);
    v0 = addu(a1, s1);
    v0 = lbu(v0);
    v1 = addu(v1, v0);            // level0 + level1
    v0 = sra(v1, 1);
    if (sgn(v1) < 0) {
        charge(2);
        v0 = addiu(v1, 1);
        v0 = sra(v0, 1);
    }
    charge(7);
    v0 = addiu(v0, 1);
    a1 = v0 & 0xffu;              // the target level
    v1 = addiu(a2, 2);
    v0 = addu(v1, a0);
    v0 = lbu(v0);
    bool same = s0 == v0;
    if (same) {
        charge(4);
        v0 = addu(v1, s1);
        v0 = lbu(v0);
        same = s0 == v0;
    }
    if (same) {
        charge(7);
        a0 = s0;
        a2 = addiu(sp, 112);
        jal(0x3d66bc, gen::fn_sub_3D7DA0_003d7da0);
    } else {
        charge(7);
        a0 = s0;
        a2 = addiu(sp, 112);
        jal(0x3d66e4, gen::fn_sub_3D7AC0_003d7ac0);
    }
    a1 = v0 & 0xffffu;
    if (a1 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(4);
        a0 = s4;
        jal(0x3d6708, gen::fn_sub_176680_00176680);
        v0 = 1;
    }
    charge(10);
    close_frame(144, 96, 0, 6);
}

// sub_3D6740 [fclCombineTriangle]: $a0 the 52-byte persona out, $a1..$a3 three personas. A special recipe of three
// (category 1) wins: 2. Else the arcana from sub_3D5E60; none -> the out is cleared, 0. Target level = (sum of the three
// base levels) / 3 + 5; the result is the first persona of that arcana at or above it (sub_3D7AC0, the three excluded);
// found -> 1, else 0.
void Fu::sub_3D6740() {
    enter(19);
    open_frame(128, 80, 0, 5);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    v0 = lhu(a1 + 2);
    sh(sp + 120, v0);
    v0 = lhu(a2 + 2);
    sh(sp + 122, v0);
    v0 = lhu(a3 + 2);
    sh(sp + 124, v0);
    if (s4 == 0 || (charge(2), s3 == 0) || (charge(2), s2 == 0) || (charge(2), s1 == 0)) {
        charge(5);
        k_assert(kCombineMiscFile, 416, 0x3d67b0);
    }
    charge(9);
    a0 = s4;
    a1 = 1;
    a2 = addiu(sp, 120);
    a3 = 3;
    jal(0x3d67c8, gen::fn_sub_3D6200_003d6200);
    v0 = v0 & 0xffu;
    if (v0 != 0) {
        charge(3);
        v0 = 2;
        charge(9);
        close_frame(128, 80, 0, 5);
        return;
    }
    charge(8);
    a0 = s3;
    a1 = s2;
    a2 = s1;
    jal(0x3d67f4, gen::fn_sub_3D5E60_003d5e60);
    s0 = v0 & 0xffu;
    if (s0 == 0) {
        charge(8);
        a0 = s4;
        a1 = 0;
        a2 = 52;
        jal(0x3d6814, gen::fn_memset_00521408);
        v0 = 0;
        charge(9);
        close_frame(128, 80, 0, 5);
        return;
    }
    charge(42);
    a0 = addiu(sp, 96);
    a1 = 0;
    a2 = 24;
    jal(0x3d6834, gen::fn_memset_00521408);
    v1 = lhu(s3 + 2);
    sh(sp + 96, v1);
    a2 = lhu(s2 + 2);
    sh(sp + 98, a2);
    a1 = lhu(s1 + 2);
    sh(sp + 100, a1);
    v0 = lw(gp - 18640);
    a0 = addiu(v0, 3);
    v0 = addu(a0, mul14(v1));
    v1 = lbu(v0);
    v0 = addu(a0, mul14(a2));
    v0 = lbu(v0);
    v1 = addu(v1, v0);
    v0 = addu(a0, mul14(a1));
    v0 = lbu(v0);
    v1 = addu(v0, v1);            // the level sum
    v0 = 3;
    div(v1, v0);
    mflo(v0);
    v0 = addiu(v0, 5);
    a1 = v0 & 0xffu;
    a0 = s0;
    a2 = addiu(sp, 96);
    jal(0x3d68bc, gen::fn_sub_3D7AC0_003d7ac0);
    a1 = v0 & 0xffffu;
    if (a1 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(4);
        a0 = s4;
        jal(0x3d68e0, gen::fn_sub_176680_00176680);
        v0 = 1;
    }
    charge(9);
    close_frame(128, 80, 0, 5);
}

// The five-word copy loop several bodies open with (`for (n = 5; n > 0; --n) *dst++ = *src++` from a .data table into
// their frame): $a1 the source, $a0 the destination, $v1 the counter, as the originals leave them.
#define FUSION_COPY5()                       \
    for (;;) {                               \
        charge(7);                           \
        v0 = lw(a1);                         \
        a1 = addiu(a1, 4);                   \
        v1 = addiu(v1, -1);                  \
        sw(a0, v0);                          \
        a0 = addiu(a0, 4);                   \
        if (sgn(v1) <= 0) break;             \
        backedge();                          \
    }

// sub_3D6910 [fclCombineByKind]: $a0 the 52-byte persona out, $a1 the kind (0 normal, 1 triangle, 2..4 the larger
// special fusions), $a2 the ingredient personas (pointer array). The ingredient count is 0x6A5FE0[kind] (2..6, copied
// to the frame). Kind 0 -> sub_3D64A0 on the two ids, 1 -> sub_3D6740 on the three personas, else the ids into a u16
// frame array and a special recipe (sub_3D6200; result 2). A result inherits from the ingredients (sub_176AC0); returns
// the fusion's result code (0 none, 1 normal, 2 special).
void Fu::sub_3D6910() {
    enter(13);
    open_frame(128, 64, 0, 4);
    s3 = a0;  // out
    s2 = a1;  // kind
    s1 = a2;  // personas
    a1 = addiu(lui(0x6a), 24544);
    a0 = addiu(sp, 80);
    v1 = 5;
    FUSION_COPY5()
    charge(2);
    if (s1 == 0 || (charge(3), v0 = slti(s2, 5), v0 == 0)) {
        charge(5);
        k_assert(kCombineMiscFile, 450, 0x3d6980);
    }
    charge(11);
    a0 = s3;
    a1 = 0;
    a2 = 52;
    jal(0x3d6994, gen::fn_memset_00521408);
    v0 = addu(sll(s2, 2), sp);
    s0 = lw(v0 + 80);  // the ingredient count
    v0 = 1;
    if (s2 == v0) {
        charge(9);
        a0 = s3;
        a1 = lw(s1);
        a2 = lw(s1 + 4);
        a3 = lw(s1 + 8);
        jal(0x3d6a08, gen::fn_sub_3D6740_003d6740);
        s2 = v0 & 0xffu;
    } else if (charge(2), s2 == 0) {
        charge(10);
        v1 = lw(s1);
        v0 = lw(s1 + 4);
        a0 = s3;
        a1 = lhu(v1 + 2);
        a2 = lhu(v0 + 2);
        jal(0x3d69d8, gen::fn_sub_3D64A0_003d64a0);
        s2 = v0 & 0xffu;
    } else {
        charge(2);
        charge(3);
        a0 = 0;
        for (;;) {
            charge(3);
            v0 = slt(a0, s0);
            if (v0 == 0) break;
            backedge();
            charge(5);
            v0 = addu(s1, sll(a0, 2));
            v0 = lw(v0);
            if (v0 != 0) {
                charge(4);
                v1 = lhu(v0 + 2);
                v0 = addu(sll(a0, 1), sp);
                sh(v0 + 112, v1);
            }
            charge(1);
            a0 = addiu(a0, 1);
        }
        charge(9);
        a0 = s3;
        a1 = s2;
        a2 = addiu(sp, 112);
        a3 = s0;
        jal(0x3d6a78, gen::fn_sub_3D6200_003d6200);
        v0 = v0 & 0xffu;
        if (v0 == 0) {
            charge(3);
            v0 = 0;
            charge(8);
            close_frame(128, 64, 0, 4);
            return;
        }
        charge(1);
        s2 = 2;
        goto inherit;
    }
    if (s2 == 0) {
        charge(3);
        v0 = 0;
        charge(8);
        close_frame(128, 64, 0, 4);
        return;
    }
inherit:
    charge(6);
    a0 = s3;
    a1 = s1;
    a2 = s0;
    jal(0x3d6aa8, gen::fn_sub_176AC0_00176ac0);
    v0 = s2 & 0xffu;
    charge(8);
    close_frame(128, 64, 0, 4);
}

// sub_3D6AE0 [fclCombinePreview]: $a0 the 84-byte fusion result, $a1 the kind, $a2 the ingredient personas. Clears the
// result, fuses into result + 4 (sub_3D6910; flag bit 2 for a special result), keeps a copy of the fused persona in the
// frame, runs the inheritance (sub_3D7A30 with the count 0x6A6000[kind]), sets flag bit 1 when the result's level is
// above the hero's (sub_16C470(1)), then the stat deltas (+56, against the copy) and the skills the inheritance added
// (+62: each skill slot that changed, 0 for the unchanged). Returns the fusion's result code.
void Fu::sub_3D6AE0() {
    enter(13);
    open_frame(176, 64, 0, 4);
    s3 = a0;  // result
    s2 = a1;  // kind
    s1 = a2;  // personas
    a1 = addiu(lui(0x6a), 24576);
    a0 = addiu(sp, 144);
    v1 = 5;
    FUSION_COPY5()
    charge(19);
    a0 = s3;
    a1 = 0;
    a2 = 84;
    jal(0x3d6b3c, gen::fn_memset_00521408);
    a0 = addiu(sp, 80);
    a1 = 0;
    a2 = 52;
    jal(0x3d6b50, gen::fn_memset_00521408);
    a0 = addiu(s3, 4);
    a1 = s2;
    a2 = s1;
    jal(0x3d6b64, gen::fn_sub_3D6910_003d6910);
    s0 = v0 & 0xffu;
    v0 = 2;
    if (s0 == v0) {
        charge(3);
        v0 = lw(s3);
        v0 = v0 | 0x4u;
        sw(s3, v0);
    }
    charge(20);
    a0 = addiu(sp, 80);
    a1 = addiu(s3, 4);
    a2 = 52;
    jal(0x3d6b94, gen::fn_memcpy_00521250);  // the copy before the inheritance
    v0 = addu(sll(s2, 2), sp);
    a0 = addiu(s3, 4);
    a1 = s1;
    a2 = lw(v0 + 144);
    jal(0x3d6bb0, gen::fn_sub_3D7A30_003d7a30);
    s1 = lbu(s3 + 8);                         // the result's level
    a0 = 1;
    jal(0x3d6bc0, gen::fn_sub_16C470_0016c470);
    v0 = v0 & 0xffu;
    at = slt(v0, s1);
    if (at != 0) {
        charge(3);
        v0 = lw(s3);
        v0 = v0 | 0x2u;
        sw(s3, v0);
    }
    charge(3);
    a1 = 0;
    for (;;) {
        charge(3);
        v0 = slti(a1, 5);
        if (v0 == 0) break;
        backedge();
        charge(7);
        a0 = addu(s3, a1);
        v1 = lbu(a0 + 32);
        v0 = addu(a1, sp);
        v0 = lbu(v0 + 108);
        v0 = subu(v1, v0);
        sb(a0 + 56, v0);                      // stat delta
        a1 = addiu(a1, 1);
    }
    charge(3);
    a1 = 0;
    for (;;) {
        charge(3);
        v0 = slti(a1, 8);
        if (v0 == 0) break;
        backedge();
        charge(7);
        v0 = sll(a1, 1);
        a0 = addu(s3, v0);
        v1 = lhu(a0 + 16);
        v0 = addu(v0, sp);
        v0 = lhu(v0 + 92);
        if (v1 != v0) {
            charge(3);
            sh(a0 + 62, v1);                  // an added skill
        } else {
            charge(1);
            sh(a0 + 62, zero);
        }
        charge(1);
        a1 = addiu(a1, 1);
    }
    charge(9);
    v0 = s0;
    close_frame(176, 64, 0, 4);
}

// sub_3D6C90 [fclCombineRollAccident]: $a0 the kind. With flag 3037 clear: kind 0 -> RpRandom() % 0xFFFF * 36 /
// 0xFFFF < 6, kind 1 -> (* 9) < 3; with it set: kind 0 -> (<< 12) < 64, kind 1 -> (<< 10) < 32. Kind 2 draws a number and
// never succeeds (the compiled 0 / 0xFFFF < 0); other kinds -> 0. The HI/LO of the last divu stay as left.
void Fu::sub_3D6C90() {
    enter(9);
    open_frame(32, 16, 0, 1);
    s0 = a0;
    a0 = 3037;
    jal(0x3d6ca4, gen::fn_datGetFlag_0016f190);
    bool hit = false;
    if (v0 != 0) {
        charge(3);
        v0 = 2;
        if (s0 == v0) {
            charge(7);
            jal(0x3d6d58, gen::fn_sub_488F30_00488f30);
            v0 = 0xffffu;
            divu(zero, v0);
            mflo(v0);
            hit = sgn(v0) < 0;
        } else if (charge(3), v0 = 1, s0 == v0) {
            charge(12);
            jal(0x3d6d1c, gen::fn_sub_488F30_00488f30);
            a0 = 0xffffu;
            divu(v0, a0);
            mfhi(v1);
            v0 = addu(sll(v1, 3), v1);     // * 9
            divu(v0, a0);
            mflo(v0);
            at = slti(v0, 3);
            hit = at != 0;
        } else if (charge(2), s0 == 0) {
            charge(13);
            jal(0x3d6cdc, gen::fn_sub_488F30_00488f30);
            a0 = 0xffffu;
            divu(v0, a0);
            mfhi(v1);
            v0 = sll(addu(sll(v1, 3), v1), 2);  // * 36
            divu(v0, a0);
            mflo(v0);
            at = slti(v0, 6);
            hit = at != 0;
        } else {
            charge(2);
        }
    } else {
        charge(3);
        v0 = 2;
        if (s0 == v0) {
            charge(7);
            jal(0x3d6e18, gen::fn_sub_488F30_00488f30);
            v0 = 0xffffu;
            divu(zero, v0);
            mflo(v0);
            hit = sgn(v0) < 0;
        } else if (charge(3), v0 = 1, s0 == v0) {
            charge(11);
            jal(0x3d6de0, gen::fn_sub_488F30_00488f30);
            v1 = 0xffffu;
            divu(v0, v1);
            mfhi(v0);
            v0 = sll(v0, 10);
            divu(v0, v1);
            mflo(v0);
            at = slti(v0, 32);
            hit = at != 0;
        } else if (charge(2), s0 == 0) {
            charge(11);
            jal(0x3d6da8, gen::fn_sub_488F30_00488f30);
            v1 = 0xffffu;
            divu(v0, v1);
            mfhi(v0);
            v0 = sll(v0, 12);
            divu(v0, v1);
            mflo(v0);
            at = slti(v0, 64);
            hit = at != 0;
        } else {
            charge(2);
        }
    }
    if (hit) {
        charge(3);
        v0 = 1;
    } else {
        charge(1);
        v0 = 0;
    }
    charge(5);
    close_frame(32, 16, 0, 1);
}

// sub_3D6E60 [fclCombineCopyAddedSkills]: $a0 a fusion result, $a1 another one. Adds each skill $a1 recorded as added
// (+62) to the result's persona (sub_176990 / sub_176840) unless it holds 8 (sub_176A30 >= 8: returns 0 at once), then
// recomputes the result's added-skill list against its persona as it was (a frame copy). Returns 0.
void Fu::sub_3D6E60() {
    enter(16);
    open_frame(144, 64, 0, 4);
    s2 = a0;
    s1 = a1;
    a0 = addiu(sp, 80);
    a1 = addiu(s2, 4);
    a2 = 52;
    jal(0x3d6e8c, gen::fn_memcpy_00521250);
    s0 = 0;
    for (;;) {
        charge(3);
        v0 = slti(s0, 8);
        if (v0 == 0) break;
        backedge();
        charge(5);
        v0 = addu(s1, sll(s0, 1));
        s3 = lhu(v0 + 62);
        if (s3 != 0) {
            charge(6);
            a0 = addiu(s2, 4);
            jal(0x3d6eb8, gen::fn_sub_176A30_00176a30);
            v0 = slti(v0, 8);
            if (v0 == 0) {
                charge(3);
                v0 = 0;
                charge(8);
                close_frame(144, 64, 0, 4);
                return;
            }
            charge(7);
            a1 = s3 & 0xffffu;
            a0 = addiu(s2, 4);
            jal(0x3d6ee0, gen::fn_sub_176990_00176990);
            v1 = si(-1);
            if (v0 == v1) {
                charge(4);
                a1 = s3 & 0xffffu;
                a0 = addiu(s2, 4);
                jal(0x3d6efc, gen::fn_sub_176840_00176840);
            }
        }
        charge(1);
        s0 = addiu(s0, 1);
    }
    charge(3);
    a1 = 0;
    for (;;) {
        charge(3);
        v0 = slti(a1, 8);
        if (v0 == 0) break;
        backedge();
        charge(7);
        v0 = sll(a1, 1);
        a0 = addu(s2, v0);
        v1 = lhu(a0 + 16);
        v0 = addu(v0, sp);
        v0 = lhu(v0 + 92);
        if (v1 != v0) {
            charge(3);
            sh(a0 + 62, v1);
        } else {
            charge(1);
            sh(a0 + 62, zero);
        }
        charge(1);
        a1 = addiu(a1, 1);
    }
    charge(1);
    v0 = 0;
    charge(8);
    close_frame(144, 64, 0, 4);
}

// sub_3D7180 [fclCombineRoll50]: RpRandom() % 0xFFFF * 1000 / 0xFFFF < 500.
void Fu::sub_3D7180() {
    enter(19);
    open_frame(16, 0, 0, 0);
    jal(0x3d7188, gen::fn_sub_488F30_00488f30);
    a0 = 0xffffu;
    divu(v0, a0);
    mfhi(v1);
    v0 = sll(addu(sll(subu(sll(v1, 5), v1), 2), v1), 3);  // * 1000
    divu(v0, a0);
    mflo(v0);
    v0 = slti(v0, 500);
    close_frame(16, 0, 0, 0);
}

// sub_3D6F80 [fclCombineAccidentRandom]: $a0 the 84-byte result, $a1 the fusion result it replaces, $a2 the exclusion
// list. Draws an arcana 2..20 (RpRandom % 0xFFFF * 19 / 0xFFFF + 2) and a level hero - 10 + (0..11) clamped to 1..99,
// takes sub_3D7AC0's persona and draws again while the hero holds it (sub_1749A0) or it is $a1's persona; none -> 0.
// Else the persona (sub_176680) must lie within [hero - 10, hero + 1] (else 0); then $a1's added skills
// (sub_3D6E60) and its experience (sub_176C80), 1.
void Fu::sub_3D6F80() {
    enter(12);
    open_frame(96, 80, 0, 5);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    if (s2 == 0 || (charge(2), s3 == 0)) {
        charge(5);
        k_assert(kCombineMiscFile, 696, 0x3d6fc4);
    }
    charge(5);
    a0 = s3;
    a1 = 0;
    a2 = 84;
    jal(0x3d6fd8, gen::fn_memset_00521408);
    for (;;) {
        charge(30);
        jal(0x3d6fe0, gen::fn_sub_488F30_00488f30);
        a0 = 0xffffu;
        divu(v0, a0);
        mfhi(v1);
        v0 = addu(sll(addu(sll(v1, 3), v1), 1), v1);  // * 19
        divu(v0, a0);
        mflo(v0);
        s0 = addiu(v0, 2);                              // the arcana
        jal(0x3d7010, gen::fn_sub_488F30_00488f30);
        a0 = 0xffffu;
        divu(v0, a0);
        mfhi(v1);
        v0 = sll(addu(sll(v1, 1), v1), 2);              // * 12
        divu(v0, a0);
        mflo(s4);
        a0 = 1;
        jal(0x3d703c, gen::fn_sub_16C470_0016c470);
        v0 = v0 & 0xffu;
        v0 = addu(v0, s4);
        v0 = addiu(v0, -10);
        if (sgn(v0) <= 0) {
            charge(3);
            v0 = 1;
        } else {
            charge(3);
            at = slti(v0, 100);
            if (at == 0) {
                charge(1);
                v0 = 99;
            }
        }
        charge(11);
        a0 = s0 & 0xffu;
        a1 = v0 & 0xffu;
        a2 = s1;
        jal(0x3d7080, gen::fn_sub_3D7AC0_003d7ac0);
        s0 = v0 & 0xffffu;
        a0 = s0;
        jal(0x3d7090, gen::fn_sub_1749A0_001749a0);
        if (v0 != 0) {
            backedge();
            continue;
        }
        charge(4);
        v1 = s0 & 0xffffu;
        v0 = lhu(s2 + 6);
        if (v0 == v1) {
            backedge();
            continue;
        }
        break;
    }
    charge(2);
    if (v1 == 0) {
        charge(3);
        v0 = 0;
        charge(9);
        close_frame(96, 80, 0, 5);
        return;
    }
    charge(13);
    a0 = addiu(s3, 4);
    a1 = s0;
    jal(0x3d70cc, gen::fn_sub_176680_00176680);
    s0 = lbu(s3 + 8);
    a0 = 1;
    jal(0x3d70dc, gen::fn_sub_16C470_0016c470);
    v1 = v0 & 0xffu;
    v0 = addiu(v1, -10);
    at = slt(s0, v0);
    bool in_range = false;
    if (at == 0) {
        charge(4);
        v0 = addiu(v1, 1);
        v0 = slt(v0, s0);
        in_range = v0 == 0;
    }
    if (in_range) {
        charge(3);
        v0 = 1;
    } else {
        charge(1);
        v0 = 0;
    }
    charge(2);
    if (v0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(9);
        a0 = s3;
        a1 = s2;
        jal(0x3d7134, gen::fn_sub_3D6E60_003d6e60);
        a0 = addiu(s3, 4);
        a1 = addiu(s2, 4);
        jal(0x3d7144, gen::fn_sub_176C80_00176c80);
        v0 = 1;
    }
    charge(9);
    close_frame(96, 80, 0, 5);
}

// sub_3D71D0 [fclCombineAccidentFool]: $a0 the 84-byte result, $a1 the fusion result it replaces, $a2 the exclusion
// list. The best Fool persona at or below hero level + 3 (sub_3D7DA0(1, ..)); none, held by the hero or $a1's own
// persona -> 0; else the persona, $a1's added skills and experience, 1.
void Fu::sub_3D71D0() {
    enter(10);
    open_frame(64, 48, 0, 3);
    s1 = a0;
    s0 = a1;
    s2 = a2;
    if (s0 == 0 || (charge(2), s1 == 0)) {
        charge(5);
        k_assert(kCombineMiscFile, 741, 0x3d720c);
    }
    charge(18);
    a0 = s1;
    a1 = 0;
    a2 = 84;
    jal(0x3d7220, gen::fn_memset_00521408);
    a0 = 1;
    jal(0x3d722c, gen::fn_sub_16C470_0016c470);
    v0 = v0 & 0xffu;
    v0 = addiu(v0, 3);
    a1 = v0 & 0xffu;
    a0 = 1;
    a2 = s2;
    jal(0x3d7248, gen::fn_sub_3D7DA0_003d7da0);
    s2 = v0 & 0xffffu;
    if (s2 == 0) {
        charge(3);
        v0 = 0;
        charge(7);
        close_frame(64, 48, 0, 3);
        return;
    }
    charge(5);
    a0 = s2;
    jal(0x3d726c, gen::fn_sub_1749A0_001749a0);
    bool refuse = v0 != 0;
    if (!refuse) {
        charge(3);
        v0 = lhu(s0 + 6);
        refuse = v0 == s2;
    }
    if (refuse) {
        charge(3);
        v0 = 0;
    } else {
        charge(13);
        a0 = addiu(s1, 4);
        a1 = s2;
        jal(0x3d729c, gen::fn_sub_176680_00176680);
        a0 = s1;
        a1 = s0;
        jal(0x3d72ac, gen::fn_sub_3D6E60_003d6e60);
        a0 = addiu(s1, 4);
        a1 = addiu(s0, 4);
        jal(0x3d72bc, gen::fn_sub_176C80_00176c80);
        v0 = 1;
    }
    charge(7);
    close_frame(64, 48, 0, 3);
}

// sub_3D72F0 [fclCombineRollBonus]: $a0 a 52-byte persona. Reads its arcana's social rank (the value is unused), then
// from hero level 10 on: chance = table[id].rate * 0x6A53D0[moon phase] / 100 (s16 moon factors: 200 at the new and
// full moons); when RpRandom % 0xFFFF * 100 / 0xFFFF < chance, flag bit 2 of +0 is set and bit 3 too unless a second
// draw (* 1000) falls below the persona's limit from the one-entry {s16 id, s16 limit} table at gp - 21864 (-1 -> 0).
// Returns 0.
void Fu::sub_3D72F0() {
    enter(24);
    open_frame(48, 32, 0, 2);
    s1 = a0;
    v1 = lhu(a0 + 2);
    v1 = mul14(v1);
    v0 = lw(gp - 18640);
    v0 = addu(v1, v0);
    a0 = lbu(v0 + 2);
    jal(0x3d7320, gen::fn_sub_16DEB0_0016deb0);
    a0 = v0;
    jal(0x3d732c, gen::fn_sub_16DBA0_0016dba0);
    a0 = 1;
    jal(0x3d7338, gen::fn_sub_16C470_0016c470);
    v0 = v0 & 0xffu;
    at = slti(v0, 10);
    if (at != 0) {
        charge(3);
        v0 = 0;
        charge(6);
        close_frame(48, 32, 0, 2);
        return;
    }
    charge(34);
    jal(0x3d735c, gen::fn_clndGetCurrentMoonPhase_00181b10);
    v0 = v0 & 0xffu;
    v1 = sll(v0, 1);
    v0 = addu(addiu(lui(0x6a), 21456), v1);
    a0 = lh(v0);                         // the moon factor
    v1 = lhu(s1 + 2);
    v1 = mul14(v1);
    v0 = lw(gp - 18640);
    v0 = addu(v1, v0);
    v0 = lbu(v0 + 12);                   // the base rate
    mult(v1, v0, a0);
    v0 = 100;
    div(v1, v0);
    mflo(s0);                            // the chance
    jal(0x3d73a8, gen::fn_sub_488F30_00488f30);
    a0 = 0xffffu;
    divu(v0, a0);
    mfhi(v1);
    v0 = sll(v1, 2);
    v1 = addu(v0, v1);
    v0 = sll(v1, 2);
    v0 = addu(v1, v0);
    v0 = sll(v0, 2);                     // * 100
    divu(v0, a0);
    mflo(v0);
    at = sltu(v0, s0);
    if (at != 0) {
        charge(4);
        a2 = 0;
        v1 = addiu(gp, -21864);
        bool found = false;
        for (;;) {
            charge(2);
            if (a2 != 0) break;
            backedge();
            charge(6);
            a1 = sll(a2, 2);
            a0 = lhu(s1 + 2);
            v0 = addu(v1, a1);
            v0 = lh(v0);
            if (a0 == v0) {
                charge(5);
                v0 = addu(addiu(gp, -21862), a1);
                s0 = lh(v0);             // the limit
                found = true;
                break;
            }
            charge(1);
            a2 = addiu(a2, 1);
        }
        if (!found) {
            charge(1);
            s0 = si(-1);
        }
        charge(3);
        v0 = si(-1);
        if (s0 == v0) {
            charge(1);
            s0 = 0;
        }
        charge(18);
        v0 = lhu(s1);
        v0 = v0 | 0x4u;
        sh(s1, v0);
        jal(0x3d744c, gen::fn_sub_488F30_00488f30);
        a0 = 0xffffu;
        divu(v0, a0);
        mfhi(v1);
        v0 = sll(addu(sll(subu(sll(v1, 5), v1), 2), v1), 3);  // * 1000
        divu(v0, a0);
        mflo(v0);
        v0 = sltu(v0, s0);
        if (v0 == 0) {
            charge(3);
            v0 = lhu(s1);
            v0 = v0 | 0x8u;
            sh(s1, v0);
        }
    }
    charge(1);
    v0 = 0;
    charge(6);
    close_frame(48, 32, 0, 2);
}

// sub_3D74B0 [fclCombineTable6A5630]: the word 0x6A5630[table[id].byte13].
void Fu::sub_3D74B0() {
    enter(14);
    a1 = lw(gp - 18640);
    v1 = a0 & 0xffffu;
    v0 = addu(mul14(v1), a1);
    v0 = lbu(v0 + 13);
    v1 = sll(v0, 2);
    v0 = addu(addiu(lui(0x6a), 22064), v1);
    v0 = lw(v0);
}

// sub_3D7A30 [fclCombineInherit]: $a0 a 52-byte persona, $a1 the ingredient personas, $a2 their count. Reads the
// arcana's social rank (unused), runs the skill inheritance sub_3D74F0 (fusion_menu.cpp), returns 0.
void Fu::sub_3D7A30() {
    enter(33);
    open_frame(64, 48, 0, 3);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    v1 = lhu(a0 + 2);
    v1 = mul14(v1);
    v0 = lw(gp - 18640);
    v0 = addu(v1, v0);
    a0 = lbu(v0 + 2);
    jal(0x3d7a6c, gen::fn_sub_16DEB0_0016deb0);
    a0 = v0;
    jal(0x3d7a78, gen::fn_sub_16DBA0_0016dba0);
    a0 = s2;
    a1 = s1;
    a2 = s0;
    jal(0x3d7a8c, gen::fn_sub_3D74F0_003d74f0);
    v0 = 0;
    close_frame(64, 48, 0, 3);
}

// The body of sub_3D7AC0 / sub_3D7DA0 [fclCombineFindResultUp / Down]: $a0 an arcana, $a1 a target level, $a2 a
// 12-entry u16 exclusion list. Over persona ids 0..191 of that arcana that are fusion results (flags bits 0 and 1
// clear) and available (the rule walk of sub_3D5BB0, inline): `best` = the highest base level (the first of equals);
// `pick` = among those not excluded with level >= target (up) / <= target (down), the lowest (up) / highest (down)
// level, the first of equals. Returns pick, else best when its level is below the target (both directions), else 0.
// K_Assert when the arcana has no persona at all. The arcana sits in a 128-bit frame slot (sq / lq of $v0). The two
// bodies differ only in the two level compares (and in the register the first one uses: $v0 up, $at down).
void Fu::find_result(bool up, u32 line, u32 pc1, u32 pc2, u32 pc3) {
    enter(20);
    open_frame(176, 144, 0, 9);
    fp = a2;   // exclusion list
    s3 = 0;    // pick
    s2 = 0;    // best
    s4 = 0;    // id
    v0 = a0 & 0xffu;
    sq(sp + 160, v0);
    s7 = a1 & 0xffu;  // target level
    for (;;) {
        charge(4);
        s0 = s4 & 0xffffu;
        v0 = slti(s0, 192);
        if (v0 == 0) break;
        backedge();
        charge(10);
        a0 = lw(gp - 18640);
        v1 = s4 & 0xffffu;
        s5 = mul14(v1);
        a0 = addu(a0, s5);           // &table[id]
        v1 = lbu(a0 + 2);
        lq(v0, sp + 160);
        bool skip = v0 != v1;
        if (!skip) {
            charge(4);
            v1 = lhu(a0);
            v0 = v1 & 0x1u;
            if (v0 != 0) {
                charge(3);
                v0 = 0;
            } else {
                charge(3);
                v0 = v1 & 0x2u;
                if (v0 != 0) {
                    charge(3);
                    v0 = 0;
                } else {
                    charge(1);
                    v0 = 1;
                }
            }
            charge(2);
            skip = v0 == 0;
        }
        if (!skip) {  // the availability rules
            charge(4);
            s6 = 1;
            s1 = 0;
            bool decided = false;
            for (;;) {
                charge(3);
                v0 = sltiu(s1, 67);
                if (v0 == 0) break;
                backedge();
                charge(7);
                v1 = sll(s1, 3);
                a0 = addu(addiu(lui(0x6a), 21520), v1);
                v0 = lh(a0 + 4);
                if (s0 == v0) {
                    charge(4);
                    v1 = lh(a0 + 6);
                    v0 = v1 & 0x1u;
                    if (v0 != 0) {
                        charge(5);
                        a0 = lw(a0);
                        jal(pc1, gen::fn_datGetFlag_0016f190);
                        if (v0 == 0) {
                            charge(3);
                            v1 = 0;
                            decided = true;
                            break;
                        }
                    } else {
                        charge(3);
                        v0 = v1 & 0x2u;
                        if (v0 != 0) {
                            charge(7);
                            s6 = 0;
                            a0 = lw(a0);
                            jal(pc2, gen::fn_datGetFlag_0016f190);
                            v1 = 1;
                            if (v0 == v1) {
                                charge(2);
                                decided = true;
                                break;
                            }
                        }
                    }
                }
                charge(1);
                s1 = addiu(s1, 1);
            }
            if (!decided) {
                charge(1);
                v1 = s6;
            }
            charge(2);
            skip = v1 == 0;
        }
        if (!skip) {
            // best: the highest level so far
            charge(3);
            v1 = s2 & 0xffffu;
            bool take = v1 == 0;
            if (!take) {
                charge(11);
                a0 = lw(gp - 18640);
                v0 = addu(a0, mul14(v1));
                v1 = lbu(v0 + 3);
                v0 = addu(a0, s5);
                v0 = lbu(v0 + 3);
                at = slt(v1, v0);
                take = at != 0;
            }
            if (take) {
                charge(1);
                s2 = s4 & 0xffffu;
            }
            charge(6);
            v0 = lw(gp - 18640);
            v0 = addu(v0, s5);
            a1 = lbu(v0 + 3);            // this level
            bool out_of_range;
            if (up) {
                v0 = slt(a1, s7);
                out_of_range = v0 != 0;
            } else {
                at = slt(s7, a1);
                out_of_range = at != 0;
            }
            if (!out_of_range) {
                charge(3);
                v1 = 0;
                bool excluded = false;
                for (;;) {
                    charge(3);
                    v0 = slti(v1, 12);
                    if (v0 == 0) break;
                    backedge();
                    charge(5);
                    v0 = addu(fp, sll(v1, 1));
                    v0 = lhu(v0);
                    if (s0 == v0) {
                        charge(3);
                        v0 = 1;
                        excluded = true;
                        break;
                    }
                    charge(1);
                    v1 = addiu(v1, 1);
                }
                if (!excluded) {
                    charge(1);
                    v0 = 0;
                }
                charge(2);
                if (v0 == 0) {
                    charge(3);
                    a0 = s3 & 0xffffu;
                    bool better = a0 == 0;
                    if (!better) {
                        charge(9);
                        v1 = lw(gp - 18640);
                        v0 = addu(v1, mul14(a0));
                        v0 = lbu(v0 + 3);        // pick's level
                        at = up ? slt(a1, v0) : slt(v0, a1);
                        better = at != 0;
                    }
                    if (better) {
                        charge(1);
                        s3 = s4 & 0xffffu;
                    }
                }
            }
        }
        charge(2);
        v0 = addiu(s4, 1);
        s4 = v0 & 0xffffu;
    }
    charge(2);
    if (s2 == 0) {
        charge(5);
        k_assert(kCombineMiscFile, line, pc3);
    }
    charge(3);
    v0 = s3 & 0xffffu;
    if (v0 == 0) {
        charge(10);
        a0 = lw(gp - 18640);
        v1 = s2 & 0xffffu;
        v0 = addu(mul14(v1), a0);
        v0 = lbu(v0 + 3);
        at = slt(v0, s7);
        if (at != 0) {
            charge(1);
            s3 = v1;
        }
    }
    charge(14);
    v0 = s3;
    close_frame(176, 144, 0, 9);
}

void Fu::sub_3D7AC0() { find_result(true, 1115, 0x3d7bb8, 0x3d7be8, 0x3d7d1c); }

void Fu::sub_3D7DA0() { find_result(false, 1148, 0x3d7e98, 0x3d7ec8, 0x3d7ffc); }

// sub_3D8080 [fclCombineCommit]: $a0 the 84-byte fusion result, $a1 the ingredient personas, $a2 their count. Copies the
// ingredient ids into the frame; each that is not the hero's current persona (sub_1752B0) leaves the hero's list
// (sub_174B40; K_Assert when it was not there). The result goes into the slot sub_174E20 gives for its id (the slot's
// flags ORed with the result's), then the current persona: the result when the current one was an ingredient (and
// that one is removed), else the current one again (sub_175130). Returns 1, or 0 without a slot.
void Fu::sub_3D8080() {
    enter(16);
    open_frame(128, 80, 0, 5);
    s0 = a0;  // result
    s2 = a1;  // personas
    s4 = a2;  // count
    jal(0x3d80a8, gen::fn_sub_1752B0_001752b0);
    s1 = v0 & 0xffffu;  // the current persona id
    s3 = 0;             // it was an ingredient
    if (s0 == 0 || (charge(2), s2 == 0) || (charge(2), s4 == 0)) {
        charge(5);
        k_assert(kCombineMiscFile, 1165, 0x3d80dc);
    }
    charge(3);
    a1 = 0;
    for (;;) {
        charge(3);
        v0 = slt(a1, s4);
        if (v0 == 0) break;
        backedge();
        charge(7);
        a0 = sll(a1, 2);
        v0 = addu(s2, a0);
        v0 = lw(v0);
        v1 = lhu(v0 + 2);
        v0 = addu(a0, sp);
        sw(v0 + 96, v1);
        a1 = addiu(a1, 1);
    }
    charge(3);
    s2 = 0;
    for (;;) {
        charge(3);
        v0 = slt(s2, s4);
        if (v0 == 0) break;
        backedge();
        charge(6);
        v0 = addiu(addu(sll(s2, 2), sp), 96);
        v0 = lw(v0);
        if (s1 == v0) {
            charge(1);
            s3 = 1;
        } else {
            charge(5);
            a0 = v0 & 0xffffu;
            jal(0x3d8140, gen::fn_sub_174B40_00174b40);
            if (v0 == 0) {
                charge(7);
                k_assert(kCombineMiscFile, 1172, 0x3d815c);
            }
        }
        charge(1);
        s2 = addiu(s2, 1);
    }
    charge(6);
    a0 = lhu(s0 + 6);
    jal(0x3d8184, gen::fn_sub_174E20_00174e20);
    s2 = v0;
    if (v0 == 0) {
        charge(3);
        v0 = 0;
        charge(9);
        close_frame(128, 80, 0, 5);
        return;
    }
    charge(11);
    v1 = lhu(s2);
    v0 = lhu(s0 + 4);
    s4 = v1 | v0;
    a0 = s2;
    a1 = addiu(s0, 4);
    a2 = 52;
    jal(0x3d81bc, gen::fn_memcpy_00521250);
    sh(s2, s4);
    if (s3 != 0) {
        charge(8);
        a0 = lhu(s0 + 6);
        jal(0x3d81d4, gen::fn_sub_175130_00175130);
        a0 = s1 & 0xffffu;
        jal(0x3d81e0, gen::fn_sub_174B40_00174b40);
    } else {
        charge(3);
        a0 = s1 & 0xffffu;
        jal(0x3d81f4, gen::fn_sub_175130_00175130);
    }
    charge(1);
    v0 = 1;
    charge(9);
    close_frame(128, 80, 0, 5);
}

// sub_3D8230 [fclCombineResultRegistered]: the hero holds the result's persona (sub_1749A0(result + 6) != 0).
void Fu::sub_3D8230() {
    enter(10);
    open_frame(16, 0, 0, 0);
    a0 = lhu(a0 + 6);
    jal(0x3d823c, gen::fn_sub_1749A0_001749a0);
    v0 = sltu(zero, v0);
    close_frame(16, 0, 0, 0);
}

// sub_3D8260 [fclCombineNormalPartnerMask]: $a0 the stock list, $a1 the first ingredient's index (0..11). The mask of
// the other stock entries with a persona that fuse with it (sub_3D64A0 into a frame persona returns non-zero).
void Fu::sub_3D8260() {
    enter(12);
    open_frame(160, 80, 0, 5);
    s4 = a0;  // stock
    s3 = a1;  // first
    s1 = 0;   // mask
    if (s4 == 0 || (charge(2), sgn(s3) < 0) || (charge(3), v0 = slti(s3, 12), v0 == 0)) {
        charge(5);
        k_assert(kCombineMiscFile, 1226, 0x3d82b0);
    }
    charge(7);
    s2 = 0;
    v0 = mul12(s3);
    s0 = addu(s4, v0);         // &stock[first]
    for (;;) {
        charge(3);
        v0 = slti(s2, 12);
        if (v0 == 0) break;
        backedge();
        charge(7);
        v0 = addu(s4, mul12(s2));
        v0 = lw(v0 + 4);
        if (v0 != 0) {
            charge(3);
            a1 = lhu(v0 + 2);
            if (a1 != 0) {
                charge(2);
                if (s2 != s3) {
                    charge(7);
                    v0 = lw(s0 + 4);
                    a0 = addiu(sp, 96);
                    a2 = lhu(v0 + 2);
                    jal(0x3d8310, gen::fn_sub_3D64A0_003d64a0);
                    if (v0 != 0) {
                        charge(3);
                        v0 = 1;
                        v0 = sllv(v0, s2);
                        s1 = s1 | v0;
                    }
                }
            }
        }
        charge(1);
        s2 = addiu(s2, 1);
    }
    charge(10);
    v0 = s1;
    close_frame(160, 80, 0, 5);
}

// sub_3D8370 [fclCombineTrianglePartnerMask]: $a0 the stock list, $a1 / $a2 the first two ingredients' indices. The mask
// of the other stock entries that complete a triangle fusion with them (sub_3D6740 into a frame persona; called with
// the candidate first, then the two chosen ones).
void Fu::sub_3D8370() {
    enter(15);
    open_frame(192, 112, 0, 7);
    s5 = a0;  // stock
    s4 = a1;  // first
    s3 = a2;  // second
    s1 = 0;   // mask
    bool bad = s5 == 0;
    if (!bad) { charge(2); bad = sgn(s4) < 0; }
    if (!bad) { charge(3); at = slti(s4, 12); bad = at == 0; }
    if (!bad) { charge(2); bad = sgn(s3) < 0; }
    if (!bad) { charge(3); v0 = slti(s3, 12); bad = v0 == 0; }
    if (bad) {
        charge(5);
        k_assert(kCombineMiscFile, 1244, 0x3d83e0);
    }
    charge(11);
    s2 = 0;
    v0 = mul12(s3);
    s0 = addu(s5, v0);   // &stock[second]
    v0 = mul12(s4);
    s6 = addu(s5, v0);   // &stock[first]
    for (;;) {
        charge(3);
        v0 = slti(s2, 12);
        if (v0 == 0) break;
        backedge();
        charge(7);
        v0 = addu(s5, mul12(s2));
        a1 = lw(v0 + 4);
        if (a1 != 0) {
            charge(3);
            v0 = lhu(a1 + 2);
            if (v0 != 0 && (charge(2), s2 != s4) && (charge(2), s2 != s3)) {
                charge(7);
                a0 = addiu(sp, 128);
                a2 = lw(s6 + 4);
                a3 = lw(s0 + 4);
                jal(0x3d8458, gen::fn_sub_3D6740_003d6740);
                if (v0 != 0) {
                    charge(3);
                    v0 = 1;
                    v0 = sllv(v0, s2);
                    s1 = s1 | v0;
                }
            }
        }
        charge(1);
        s2 = addiu(s2, 1);
    }
    charge(12);
    v0 = s1;
    close_frame(192, 112, 0, 7);
}

// sub_3D84C0 [fclCombineAnyRecipeAvailable]: $a1 the category ($a0 unused). 1 when some recipe of the category has an
// available result (the rule walk of sub_3D5BB0, inline), else 0. Opens with an empty 12-pass loop (the compiled
// remains of a cleared local array).
void Fu::sub_3D84C0() {
    enter(11);
    open_frame(112, 96, 0, 6);
    v1 = 0;
    for (;;) {
        charge(6);
        v0 = slti(v1, 12);
        if (v0 == 0) break;
        backedge();
        charge(1);
        v1 = addiu(v1, 1);
    }
    charge(12);
    v1 = sll(a1, 3);
    v0 = addu(addiu(lui(0x6a), 24384), v1);
    s5 = lw(v0);  // the recipe
    v0 = addu(addiu(lui(0x6a), 24388), v1);
    s1 = lw(v0);  // the count
    s2 = 0;
    for (;;) {
        charge(3);
        v0 = slt(s2, s1);
        if (v0 == 0) break;
        backedge();
        charge(5);
        s0 = lhu(s5);  // the result
        s3 = 1;
        s4 = 0;
        bool decided = false;
        for (;;) {
            charge(3);
            v0 = sltiu(s4, 67);
            if (v0 == 0) break;
            backedge();
            charge(7);
            v1 = sll(s4, 3);
            a0 = addu(addiu(lui(0x6a), 21520), v1);
            v0 = lh(a0 + 4);
            if (s0 == v0) {
                charge(4);
                v1 = lh(a0 + 6);
                v0 = v1 & 0x1u;
                if (v0 != 0) {
                    charge(5);
                    a0 = lw(a0);
                    jal(0x3d857c, gen::fn_datGetFlag_0016f190);
                    if (v0 == 0) {
                        charge(3);
                        v1 = 0;
                        decided = true;
                        break;
                    }
                } else {
                    charge(3);
                    v0 = v1 & 0x2u;
                    if (v0 != 0) {
                        charge(7);
                        s3 = 0;
                        a0 = lw(a0);
                        jal(0x3d85ac, gen::fn_datGetFlag_0016f190);
                        v1 = 1;
                        if (v0 == v1) {
                            charge(2);
                            decided = true;
                            break;
                        }
                    }
                }
            }
            charge(1);
            s4 = addiu(s4, 1);
        }
        if (!decided) {
            charge(1);
            v1 = s3;
        }
        charge(2);
        if (v1 != 0) {
            charge(3);
            v0 = 1;
            charge(10);
            close_frame(112, 96, 0, 6);
            return;
        }
        charge(2);
        s5 = addiu(s5, 32);
        s2 = addiu(s2, 1);
    }
    charge(1);
    v0 = 0;
    charge(10);
    close_frame(112, 96, 0, 6);
}

// sub_3D8630 [fclCombineAnyRecipeInStock]: $a0 the stock list, $a1 the category. Collects the stock's persona ids into
// a 12-entry u16 frame array (entries without a persona keep the frame's old bytes), then 1 when some recipe of the
// category matches it (sub_3D5A40, at least category + 2 ingredients) and has an available result, else 0.
void Fu::sub_3D8630() {
    enter(14);
    open_frame(176, 128, 0, 8);
    s5 = a1;  // category
    a2 = 0;
    for (;;) {
        charge(3);
        v0 = slti(a2, 12);
        if (v0 == 0) break;
        backedge();
        charge(7);
        a1 = sll(a2, 1);
        v0 = sll(addu(a1, a2), 2);
        v0 = addu(a0, v0);
        v0 = lw(v0 + 4);
        if (v0 != 0) {
            charge(3);
            v1 = lhu(v0 + 2);
            v0 = addu(a1, sp);
            sh(v0 + 144, v1);
        }
        charge(1);
        a2 = addiu(a2, 1);
    }
    charge(15);
    v1 = sll(s5, 3);
    v0 = addu(addiu(lui(0x6a), 24384), v1);
    s4 = lw(v0);  // the recipe
    v0 = addu(addiu(lui(0x6a), 24388), v1);
    s0 = lw(v0);  // the count
    s1 = 0;
    v0 = addiu(s5, 2);
    s6 = seh(v0); // the minimum match
    for (;;) {
        charge(3);
        v0 = slt(s1, s0);
        if (v0 == 0) break;
        backedge();
        charge(14);
        sh(sp + 174, zero);
        v0 = addiu(s5, 2);
        a1 = seh(v0);
        a0 = s4;
        a2 = addiu(sp, 144);
        a3 = 12;
        t0 = addiu(sp, 174);
        jal(0x3d86fc, gen::fn_sub_3D5A40_003d5a40);
        v1 = lh(sp + 174);
        v1 = slt(v1, s6);
        if (v1 != 0) {
            charge(1);
            v0 = 0;
        } else {
            charge(2);
        }
        charge(2);
        if (v0 != 0) {
            charge(5);
            s7 = lhu(s4);
            s2 = 1;
            s3 = 0;
            bool decided = false;
            for (;;) {
                charge(3);
                v0 = sltiu(s3, 67);
                if (v0 == 0) break;
                backedge();
                charge(7);
                v1 = sll(s3, 3);
                a0 = addu(addiu(lui(0x6a), 21520), v1);
                v0 = lh(a0 + 4);
                if (s7 == v0) {
                    charge(4);
                    v1 = lh(a0 + 6);
                    v0 = v1 & 0x1u;
                    if (v0 != 0) {
                        charge(5);
                        a0 = lw(a0);
                        jal(0x3d876c, gen::fn_datGetFlag_0016f190);
                        if (v0 == 0) {
                            charge(3);
                            v1 = 0;
                            decided = true;
                            break;
                        }
                    } else {
                        charge(3);
                        v0 = v1 & 0x2u;
                        if (v0 != 0) {
                            charge(7);
                            s2 = 0;
                            a0 = lw(a0);
                            jal(0x3d879c, gen::fn_datGetFlag_0016f190);
                            v1 = 1;
                            if (v0 == v1) {
                                charge(2);
                                decided = true;
                                break;
                            }
                        }
                    }
                }
                charge(1);
                s3 = addiu(s3, 1);
            }
            if (!decided) {
                charge(1);
                v1 = s2;
            }
            charge(2);
            if (v1 != 0) {
                charge(3);
                v0 = 1;
                charge(12);
                close_frame(176, 128, 0, 8);
                return;
            }
        }
        charge(2);
        s4 = addiu(s4, 32);
        s1 = addiu(s1, 1);
    }
    charge(1);
    v0 = 0;
    charge(12);
    close_frame(176, 128, 0, 8);
}

// sub_3D8830 [fclCombineRecipeCount]: the recipe count of category $a0 (0x6A5F44 + 8 * a0).
void Fu::sub_3D8830() {
    enter(7);
    v1 = sll(a0, 3);
    v0 = addu(addiu(lui(0x6a), 24388), v1);
    v0 = lw(v0);
}

// =====================================================================================================================
// [fclCombine.c] the sequence object and the menu step helpers
// =====================================================================================================================

// sub_3D02E0 [fclCombineGetRoot]: the word at gp - 18028.
void Fu::sub_3D02E0() {
    enter(3);
    v0 = lw(gp - 18028);
}

// sub_3D0600 [fclCombineIsActive]: the word at gp - 18028 != 0.
void Fu::sub_3D0600() {
    enter(4);
    v0 = lw(gp - 18028);
    v0 = sltu(zero, v0);
}

// sub_3D2C00 / sub_3D2EF0: return 0 (step callbacks).
void Fu::sub_3D2C00() {
    enter(3);
    v0 = 0;
}

void Fu::sub_3D2EF0() {
    enter(3);
    v0 = 0;
}

// sub_3D3010 [fclCombineMenuClosed]: $a0 a menu holder: 1 when it or its window (+0) is missing, else bit 0 of the
// window's state word (+4).
void Fu::sub_3D3010() {
    enter(2);
    if (a0 == 0 || (charge(3), v0 = lw(a0), v0 == 0)) {
        charge(3);
        v0 = 1;
    } else {
        charge(3);
        v0 = lw(v0 + 4);
        v0 = v0 & 0x1u;
        v0 = sltu(zero, v0);
    }
    charge(2);
}

// =====================================================================================================================
// [fclCombineList.c] the list menu and the facility element lists
// =====================================================================================================================

// sub_3DEF10 [fclElemSpacing]: 0 for n < 2 (unsigned), else 9 * (n + 1).
void Fu::sub_3DEF10() {
    enter(3);
    at = sltiu(a0, 2);
    if (at == 0) {
        charge(5);
        v1 = addiu(a0, 1);
        v0 = addu(sll(v1, 3), v1);
    } else {
        charge(1);
        v0 = 0;
    }
    charge(2);
}

// sub_3DEF40 [fclElemOffset]: $a0 a width, $a1 n, $a2 i: width / 2 (arithmetic) - (n < 2 ? 0 : i * width / (n - 1)) + 90.
// HI/LO keep the mult / div results.
void Fu::sub_3DEF40() {
    enter(3);
    at = slti(a1, 2);
    if (at == 0) {
        charge(6);
        mult(v1, a2, a0);
        v0 = addiu(a1, -1);
        div(v1, v0);
        mflo(v1);
    } else {
        charge(1);
        v1 = 0;
    }
    charge(5);
    v0 = sra(a0, 1);
    v0 = subu(v0, v1);
    v0 = addiu(v0, 90);
}

// sub_3DEB20 [fclCombineListCopySelection]: $a0 the list. Copies list->slot count (+12) words from the owner's selection
// (((list+20)->+12->+20)->+28, words at +108) into the selected array (+24), the count to +16. $v0 untouched.
void Fu::sub_3DEB20() {
    enter(8);
    v1 = lw(a0 + 20);
    v1 = lw(v1 + 12);
    v1 = lw(v1 + 20);
    a3 = lw(v1 + 28);
    t0 = 0;
    t1 = 0;
    for (;;) {
        charge(4);
        v1 = lw(a0 + 12);
        v1 = slt(t1, v1);
        if (v1 == 0) break;
        backedge();
        charge(8);
        a2 = sll(t1, 2);
        v1 = addu(a3, a2);
        a1 = lw(v1 + 108);
        v1 = lw(a0 + 24);
        v1 = addu(v1, a2);
        sw(v1, a1);
        t0 = addiu(t0, 1);
        t1 = addiu(t1, 1);
    }
    charge(3);
    sw(a0 + 16, t0);
}

// sub_3DF100 [fclElemSetParams]: $a0 an element, $a1 a parameter block: +0 word -> +16; the s16 pairs +8 / +10 / +16 /
// +20 set both the current and the start value (+24/+20, +26/+22, +34/+32, +40/+38) unless they are -32768 (then the
// current one restarts from the start value); +12 / +14 / +18 / +22 set +28 / +30 / +36 / +42 unless -32768; +24 -> +44,
// +26 -> +48. Returns the element.
void Fu::sub_3DF100() {
    enter(6);
    v0 = lw(a1);
    sw(a0 + 16, v0);
    // a pair: current + start, or restart from the start value
    auto pair = [&](s32 src, s32 cur, s32 start, bool first) {
        if (!first) charge(4);
        v1 = lh(a1 + src);
        v0 = si(-32768);
        if (v1 == v0) {
            charge(4);
            v0 = lh(a0 + start);
            sh(a0 + cur, v0);
        } else {
            charge(2);
            sh(a0 + cur, v1);
            sh(a0 + start, v1);
        }
    };
    auto single = [&](s32 src, s32 dst) {
        charge(4);
        v1 = lh(a1 + src);
        v0 = si(-32768);
        if (v1 != v0) {
            charge(1);
            sh(a0 + dst, v1);
        }
    };
    pair(8, 24, 20, true);
    pair(10, 26, 22, false);
    single(12, 28);
    single(14, 30);
    pair(16, 34, 32, false);
    single(18, 36);
    pair(20, 40, 38, false);
    single(22, 42);
    charge(7);
    v0 = lh(a1 + 24);
    sh(a0 + 44, v0);
    v0 = lhu(a1 + 26);
    sh(a0 + 48, v0);
    v0 = a0;
}

// sub_3DA3E0 [fclCombineListGetSelected]: $a0 the list, $a1 an index: selected[index] (+24) when index < the slot count
// (+12), else 0.
void Fu::sub_3DA3E0() {
    enter(8);
    open_frame(48, 32, 0, 2);
    s1 = a0;
    s0 = a1;
    if (s1 == 0) {
        charge(5);
        k_assert(kCombineListFile, 1041, 0x3da40c);
    }
    charge(4);
    v0 = lw(s1 + 12);
    at = slt(s0, v0);
    if (at == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(6);
        v1 = sll(s0, 2);
        v0 = lw(s1 + 24);
        v0 = addu(v0, v1);
        v0 = lw(v0);
        if (v0 != 0) {
            charge(2);
        } else {
            charge(1);
            v0 = 0;
        }
    }
    charge(6);
    close_frame(48, 32, 0, 2);
}

// sub_3DA470 [fclCombineListIsSelected]: $a0 the list, $a1 a persona: the persona when it is among the first
// list->selected count (+16) entries of the selected array (sub_3DA3E0 inlined, its K_Assert included), else 0.
void Fu::sub_3DA470() {
    enter(9);
    open_frame(64, 48, 0, 3);
    s2 = a0;
    s1 = a1;
    if (s2 == 0) {
        charge(5);
        k_assert(kCombineListFile, 1080, 0x3da4a0);
    }
    charge(2);
    if (s1 == 0) {
        charge(3);
        v0 = 0;
        charge(7);
        close_frame(64, 48, 0, 3);
        return;
    }
    charge(3);
    s0 = 0;
    for (;;) {
        charge(4);
        v0 = lw(s2 + 16);
        v0 = slt(s0, v0);
        if (v0 == 0) break;
        backedge();
        charge(2);
        if (s2 == 0) {
            charge(5);
            k_assert(kCombineListFile, 1041, 0x3da4dc);
        }
        charge(4);
        v0 = lw(s2 + 12);
        at = slt(s0, v0);
        if (at == 0) {
            charge(3);
            v0 = 0;
        } else {
            charge(6);
            v1 = lw(s2 + 24);
            v0 = sll(s0, 2);
            v0 = addu(v1, v0);
            v0 = lw(v0);
            if (v0 != 0) {
                charge(2);
            } else {
                charge(1);
                v0 = 0;
            }
        }
        charge(2);
        if (v0 == s1) {
            charge(3);
            v0 = s1;
            charge(7);
            close_frame(64, 48, 0, 3);
            return;
        }
        charge(1);
        s0 = addiu(s0, 1);
    }
    charge(1);
    v0 = 0;
    charge(7);
    close_frame(64, 48, 0, 3);
}

// sub_3DA570 [fclCombineListPreviewAll]: $a0 the list. Copies the selected personas (+24, +16 of them) into a 32-byte
// frame array; for every row (the row list +20; row payload +28 -> the row record: +8 its persona, +12 an 84-byte
// fusion result): a persona already selected gets its result cleared, any other is appended to the frame array for a
// preview fusion of the list's kind (+4; sub_3D6AE0) and taken off again.
void Fu::sub_3DA570() {
    enter(24);
    open_frame(128, 80, 0, 5);
    s4 = a0;             // list
    v0 = lw(a0 + 20);
    s3 = lw(v0 + 4);     // the first row
    s2 = lw(a0 + 4);     // the kind
    a0 = addiu(sp, 96);
    a1 = 0;
    a2 = 32;
    jal(0x3da5a8, gen::fn_memset_00521408);
    v0 = lw(s4 + 16);
    a2 = sll(v0, 2);
    a0 = addiu(sp, 96);
    a1 = lw(s4 + 24);
    jal(0x3da5c0, gen::fn_memcpy_00521250);
    for (;;) {
        charge(2);
        if (s3 == 0) break;
        backedge();
        charge(5);
        v0 = lw(s3 + 20);
        s0 = lw(v0 + 28);  // the row record
        s1 = 0;
        bool found = false;
        for (;;) {  // the index of the row's persona among the selected (sub_3DA3E0 inlined)
            charge(4);
            v0 = lw(s4 + 12);
            v0 = slt(s1, v0);
            if (v0 == 0) break;
            backedge();
            charge(2);
            if (s4 == 0) {
                charge(5);
                k_assert(kCombineListFile, 1041, 0x3da5f8);
            }
            charge(4);
            v0 = lw(s4 + 12);
            at = slt(s1, v0);
            if (at == 0) {
                charge(3);
                v1 = 0;
            } else {
                charge(6);
                v1 = lw(s4 + 24);
                v0 = sll(s1, 2);
                v0 = addu(v1, v0);
                v1 = lw(v0);
                if (v1 != 0) {
                    charge(2);
                } else {
                    charge(1);
                    v1 = 0;
                }
            }
            charge(3);
            v0 = lw(s0 + 8);
            if (v1 == v0) {
                charge(2);
                found = true;
                break;
            }
            charge(1);
            s1 = addiu(s1, 1);
        }
        if (!found) {
            charge(1);
            s1 = si(-1);
        }
        charge(3);
        v0 = si(-1);
        if (s1 == v0) {
            charge(16);
            v1 = lw(s0 + 8);
            v0 = lw(s4 + 16);
            v0 = addu(sll(v0, 2), sp);
            sw(v0 + 96, v1);           // append the row's persona
            a0 = addiu(s0, 12);
            a1 = s2;
            a2 = addiu(sp, 96);
            jal(0x3da698, gen::fn_sub_3D6AE0_003d6ae0);
            v1 = lw(s4 + 16);
            v1 = addu(sll(v1, 2), sp);
            sw(v1 + 96, zero);
        } else {
            charge(5);
            a0 = addiu(s0, 12);
            a1 = 0;
            a2 = 84;
            jal(0x3da6c4, gen::fn_memset_00521408);
        }
        charge(1);
        s3 = lw(s3 + 16);
    }
    charge(9);
    close_frame(128, 80, 0, 5);
}

// sub_3DA2A0 [fclCombineListMarkTriangle]: $a0 the list. Finds the row whose persona is selected[0] (its index i), then
// sets every row record's +4 to the mask of triangle partners (sub_3D8370 on the stock list +284 with i and the row's
// index), 0 for rows without a persona and for row i. With no such row the last row seen (or the caller's $s4) gets
// the 0, as in the original.
void Fu::sub_3DA2A0() {
    enter(13);
    open_frame(96, 80, 0, 5);
    s3 = a0;  // list
    s1 = 0;   // index
    v1 = lw(a0 + 20);
    s2 = lw(v1 + 4);
    for (;;) {
        charge(2);
        if (s2 == 0) break;
        backedge();
        charge(5);
        v1 = lw(s2 + 20);
        s4 = lw(v1 + 28);
        s0 = lw(s4 + 8);
        if (s0 != 0) {
            charge(6);
            a0 = s3;
            a1 = 0;
            jal(0x3da2f0, gen::fn_sub_3DA3E0_003da3e0);
            if (s0 == v0) break;
        }
        charge(2);
        s2 = lw(s2 + 16);
        s1 = addiu(s1, 1);
    }
    charge(6);
    sw(s4 + 4, zero);
    s2 = 0;
    v1 = lw(s3 + 20);
    s0 = lw(v1 + 4);
    for (;;) {
        charge(2);
        if (s0 == 0) break;
        backedge();
        charge(5);
        v1 = lw(s0 + 20);
        s4 = lw(v1 + 28);
        v1 = lw(s4 + 8);
        if (v1 != 0 && (charge(2), s2 != s1)) {
            charge(8);
            a0 = addiu(s3, 284);
            a1 = s1;
            a2 = s2;
            jal(0x3da350, gen::fn_sub_3D8370_003d8370);
            sw(s4 + 4, v0);
        } else {
            charge(1);
            sw(s4 + 4, zero);
        }
        charge(2);
        s2 = addiu(s2, 1);
        s0 = lw(s0 + 16);
    }
    charge(9);
    close_frame(96, 80, 0, 5);
}

// sub_3D9C90 [fclCombineListRowFree]: $a1 a row node: destroys the row record's element list (record +96;
// sub_3DFF00). A row-remove callback.
void Fu::sub_3D9C90() {
    enter(11);
    open_frame(16, 0, 0, 0);
    v0 = lw(a1 + 20);
    v0 = lw(v0 + 28);
    a0 = lw(v0 + 96);
    jal(0x3d9ca4, gen::fn_sub_3DFF00_003dff00);
    close_frame(16, 0, 0, 0);
}

// sub_3DED40 [fclElemListDestroy]: $a0 an element list holder (+4 the nm list object): destroys the list (sub_3C45F0)
// when the holder exists.
void Fu::sub_3DED40() {
    enter(4);
    open_frame(16, 0, 0, 0);
    if (a0 != 0) {
        charge(3);
        a0 = lw(a0 + 4);
        jal(0x3ded54, gen::fn_sub_3C45F0_003c45f0);
    }
    charge(4);
    close_frame(16, 0, 0, 0);
}

// sub_3DED70 [fclElemListRemoveFiltered]: nmListRemoveFiltered on the holder's list object.
void Fu::sub_3DED70() {
    enter(9);
    open_frame(16, 0, 0, 0);
    a0 = lw(a0 + 4);
    jal(0x3ded7c, gen::fn_nmListRemoveFiltered_003c4e70);
    close_frame(16, 0, 0, 0);
}

// sub_3DECD0 [fclElemListCreate]: $a0 the owner. A list object of 20 payload bytes with the remove filter 0x3DF4A0
// (sub_3C44D0, kept recompiled); its payload holds {owner, the object}; returns the payload.
void Fu::sub_3DECD0() {
    enter(6);
    open_frame(32, 16, 0, 1);
    s0 = a0;
    if (s0 == 0) {
        charge(5);
        k_assert(kCombineListFile, 2622, 0x3decf4);
    }
    charge(16);
    a0 = 20;
    a1 = 0;
    a2 = 0;
    a3 = addiu(lui(0x3eu), -2912);  // 0x3DF4A0
    jal(0x3ded10, gen::fn_sub_3C44D0_003c44d0);
    v1 = lw(v0 + 36);
    sw(v1 + 4, v0);
    sw(v1, s0);
    v0 = v1;
    close_frame(32, 16, 0, 1);
}

// sub_3DF090 [fclElemNew]: $a0 the holder, $a1 the extra payload size. Appends a node of 56 + extra bytes keyed by the
// list's count + 1 (nmListAppendNew); the element (node payload) gets +4 its node, +52 the extra area (when extra != 0),
// +12 = 0 and flag bit 2 (+8: finished). Returns the element.
void Fu::sub_3DF090() {
    enter(14);
    open_frame(32, 16, 0, 1);
    s0 = a1;
    a0 = lw(a0 + 4);
    v0 = lhu(a0 + 16);
    a1 = addiu(v0, 1);
    a2 = addiu(s0, 56);
    jal(0x3df0b0, gen::fn_nmListAppendNew_003c4910);
    v1 = lw(v0 + 20);
    sw(v1 + 4, v0);
    if (s0 != 0) {
        charge(2);
        v0 = addiu(v1, 56);
        sw(v1 + 52, v0);
    }
    charge(10);
    sw(v1 + 12, zero);
    v0 = lw(v1 + 8);
    v0 = v0 | 0x4u;
    sw(v1 + 8, v0);
    v0 = v1;
    close_frame(32, 16, 0, 1);
}

// sub_3DF010 [fclElemAllDone]: $a0 the holder. 1 when the owner has no element state (sub_3DFAC0 == 0) or every element
// is finished (flag bit 2), else 0.
void Fu::sub_3DF010() {
    enter(9);
    open_frame(32, 16, 0, 1);
    v0 = lw(a0 + 4);
    s0 = lw(v0 + 4);  // the first node
    jal(0x3df024, gen::fn_sub_3DFAC0_003dfac0);
    if (v0 == 0) {
        charge(3);
        v0 = 1;
        charge(5);
        close_frame(32, 16, 0, 1);
        return;
    }
    for (;;) {
        charge(2);
        if (s0 == 0) break;
        backedge();
        charge(5);
        v0 = lw(s0 + 20);
        v0 = lw(v0 + 8);
        v0 = v0 & 0x4u;
        if (v0 == 0) {
            charge(3);
            v0 = 0;
            charge(5);
            close_frame(32, 16, 0, 1);
            return;
        }
        charge(1);
        s0 = lw(s0 + 16);
    }
    charge(1);
    v0 = 1;
    charge(5);
    close_frame(32, 16, 0, 1);
}

// sub_3DEF80 [fclElemRestartAll]: $a0 the holder. 0 without an element state; else every finished element restarts
// (sub_3DF220(elem, elem+0, 1, elem+16, state+32 (s16), 0)); returns 1.
void Fu::sub_3DEF80() {
    enter(11);
    open_frame(48, 32, 0, 2);
    v0 = lw(a0 + 4);
    s1 = lw(v0 + 4);
    jal(0x3def98, gen::fn_sub_3DFAC0_003dfac0);
    s0 = v0;
    if (s0 == 0) {
        charge(3);
        v0 = 0;
        charge(6);
        close_frame(48, 32, 0, 2);
        return;
    }
    for (;;) {
        charge(2);
        if (s1 == 0) break;
        backedge();
        charge(5);
        a0 = lw(s1 + 20);
        v0 = lw(a0 + 8);
        v0 = v0 & 0x4u;
        if (v0 != 0) {
            charge(7);
            t0 = lh(s0 + 32);
            a1 = lw(a0);
            a2 = 1;
            a3 = lw(a0 + 16);
            t1 = 0;
            jal(0x3defe0, gen::fn_sub_3DF220_003df220);
        }
        charge(1);
        s1 = lw(s1 + 16);
    }
    charge(1);
    v0 = 1;
    charge(6);
    close_frame(48, 32, 0, 2);
}

// sub_3DEE80 [fclElemAdd]: $a0 the holder, $a1..$a3, $t0, $t1 the start parameters: a new element without extra
// payload (sub_3DF090) started with them (sub_3DF220); returns the element.
void Fu::sub_3DEE80() {
    enter(36);
    open_frame(112, 96, 0, 6);
    s5 = a1;
    s4 = a2;
    s3 = a3;
    s2 = t0;
    s1 = t1;
    a1 = 0;
    jal(0x3deeb8, gen::fn_sub_3DF090_003df090);
    s0 = v0;
    a0 = s0;
    a1 = s5;
    a2 = s4;
    a3 = s3;
    t0 = s2;
    t1 = s1;
    jal(0x3deedc, gen::fn_sub_3DF220_003df220);
    v0 = s0;
    close_frame(112, 96, 0, 6);
}

// sub_3DF220 [fclElemStart]: $a0 an element, $a1 a word (-> +0), $a2 the mode, $a3 a word (-> +16), $t0 an angle step,
// $t1 a s16 (-> +44). Only a finished element (flag bit 2) starts. Mode 0: centre (320, 504) for both positions, +38/+40
// = 0, +42 = 255, the angle +32/+34/+36 = $t0; mode 1: the current values become the start values, +42 = 0, the new angle
// +36 = $t0 and flag bit 1. Both: +48 = 10 and the target (+28, +30) = (320 + 464 cos a, 504 - 464 sin a) with
// a = angle * gp[-32220] (cosf / sinf; $f20 / $f21 spilled at sp + 0 / 4). Any started element: +16, +44, +0, +12 = 1,
// flag bit 2 cleared.
void Fu::sub_3DF220() {
    enter(18);
    open_frame(128, 112, 16, 6);
    swc1(F21, sp + 4);
    swc1(F20, sp);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    s0 = t0;
    s5 = t1;
    if (s4 == 0) {
        charge(5);
        k_assert(kCombineListFile, 2843, 0x3df274);
    }
    charge(4);
    v1 = lw(s4 + 8);
    v1 = v1 & 0x4u;
    if (v1 != 0) {
        // the target position on the circle of radius 464 around (320, 504)
        auto target = [&](u32 pc_cos, u32 pc_sin) {
            v0 = lh(s4 + 36);
            mtc1(v0, F0);
            cvt_s_w(F1, F0);
            lwc1(F0, gp - 32220);
            mul_s(F21, F0, F1);
            mov_s(F12, F21);
            jal(pc_cos, gen::fn_cosf_0052e6d8);
            v0 = lui(0x43e8u);  // 464.0f
            mtc1(v0, F1);
            mul_s(F20, F1, F0);
            mov_s(F12, F21);
            jal(pc_sin, gen::fn_sinf_0052e878);
            v1 = lui(0x43e8u);
            mtc1(v1, F1);
            mul_s(F1, F1, F0);
            v1 = lui(0x43a0u);  // 320.0f
            mtc1(v1, F0);
            add_s(F0, F0, F20);
            cvt_w_s(F0, F0);
            mfc1(v1, F0);
            sh(s4 + 28, v1);
            v1 = lui(0x43fcu);  // 504.0f
            mtc1(v1, F0);
            sub_s(F0, F0, F1);
            cvt_w_s(F0, F0);
            mfc1(v1, F0);
            sh(s4 + 30, v1);
        };
        charge(3);
        v1 = 1;
        if (s2 == v1) {
            charge(51);
            v0 = lh(s4 + 20);
            sh(s4 + 24, v0);
            v0 = lh(s4 + 22);
            sh(s4 + 26, v0);
            v0 = lh(s4 + 38);
            sh(s4 + 40, v0);
            sh(s4 + 42, zero);
            v0 = lh(s4 + 32);
            sh(s4 + 34, v0);
            sh(s4 + 36, s0);
            v0 = 10;
            sh(s4 + 48, v0);
            target(0x3df3c8, 0x3df3e4);
            v1 = lw(s4 + 8);
            v1 = v1 | 0x2u;
            sw(s4 + 8, v1);
        } else if (charge(2), s2 == 0) {
            charge(53);
            v0 = 320;
            sh(s4 + 20, v0);
            sh(s4 + 24, v0);
            v0 = 504;
            sh(s4 + 22, v0);
            sh(s4 + 26, v0);
            sh(s4 + 38, zero);
            sh(s4 + 40, zero);
            v0 = 255;
            sh(s4 + 42, v0);
            sh(s4 + 36, s0);
            sh(s4 + 34, s0);
            sh(s4 + 32, s0);
            v0 = 10;
            sh(s4 + 48, v0);
            target(0x3df300, 0x3df31c);
        } else {
            charge(2);
        }
        charge(9);
        sw(s4 + 16, s1);
        sh(s4 + 44, s5);
        sw(s4, s3);
        v1 = 1;
        sw(s4 + 12, v1);
        a0 = lw(s4 + 8);
        v1 = si(-5);
        v1 = a0 & v1;
        sw(s4 + 8, v1);
    }
    charge(12);
    ra = ld(sp + 112);
    lq(s5, sp + 96);
    lq(s4, sp + 80);
    lq(s3, sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F21, sp + 4);
    lwc1(F20, sp);
    sp = addiu(sp, 128);
}

// =====================================================================================================================
// [fclCombine.c] the menu steps on the fclCombine sequence object (gp - 18028; nm_message.h [nmSequence])
// =====================================================================================================================

// sub_3D21D0 [fclCombineCallAll]: nmSequenceCallAll36(root); returns 0.
void Fu::sub_3D21D0() {
    enter(10);
    open_frame(16, 0, 0, 0);
    a0 = lw(gp - 18028);
    jal(0x3d21dc, gen::fn_nmSequenceCallAll36_003c5760);
    v0 = 0;
    close_frame(16, 0, 0, 0);
}

// sub_3D25C0 [fclCombineAddStep6]: $a0 a work record (may be 0). Copies the 36-byte step descriptor 0x6A4620 into the
// frame (two lq / sq and an lwc1 / swc1 through $f0), adds it as step 6 with delay 0 and life 2 (nmSequenceAddStep) and keeps
// the step at work + 40.
void Fu::sub_3D25C0() {
    enter(8);
    open_frame(80, 16, 0, 1);
    s0 = a0;
    a1 = addiu(lui(0x6a), 17952);
    a0 = addiu(sp, 32);
    v1 = 2;
    for (;;) {
        charge(7);
        lq(v0, a1);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(a0, v0);
        a0 = addiu(a0, 16);
        if (sgn(v1) <= 0) break;
        backedge();
    }
    charge(11);
    lwc1(F0, a1);
    swc1(F0, a0);
    a0 = lw(gp - 18028);
    a1 = 6;
    a2 = addiu(sp, 32);
    a3 = 0;
    t0 = 2;
    jal(0x3d2618, gen::fn_nmSequenceAddStep_003c5240);
    if (s0 != 0) {
        charge(1);
        sw(s0 + 40, v0);
    }
    charge(5);
    close_frame(80, 16, 0, 1);
}

// sub_3D2640 / sub_3D3C20 [fclCombineTakeStep40 / 24]: $a0 a work record. The step kept at `slot`: when it exists and
// its owner record's state (+20 -> +20) has bit 3 (done), the slot is cleared and the step payload's first word
// returned (sub_3C5470); else -1.
void Fu::take_step(s32 slot, u32 pc) {
    enter(7);
    open_frame(32, 16, 0, 1);
    s0 = a0;
    a0 = lw(a0 + slot);
    if (a0 == 0 || (charge(3), v0 = lw(a0 + 20), v0 == 0)) {
        charge(3);
        v0 = si(-1);
    } else {
        charge(4);
        v0 = lw(v0 + 20);
        v0 = v0 & 0x8u;
        if (v0 != 0) {
            charge(6);
            jal(pc, gen::fn_sub_3C5470_003c5470);
            sw(s0 + slot, zero);
            v0 = lw(v0);
        } else {
            charge(1);
            v0 = si(-1);
        }
    }
    charge(5);
    close_frame(32, 16, 0, 1);
}

void Fu::sub_3D2640() { take_step(40, 0x3d2684); }

// sub_3D26C0 [fclCombineStepClear]: a step callback ($a0 the object, $a1 the node): nmObjPayloadWord12(obj) (result unused),
// then the node payload's words +4 / +8 / +12 cleared; returns 0.
void Fu::sub_3D26C0() {
    enter(18);
    open_frame(32, 16, 0, 1);
    s0 = a1;
    jal(0x3d26d0, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = s0;
    jal(0x3d26dc, gen::fn_sub_3C5470_003c5470);
    sw(v0 + 12, zero);
    sw(v0 + 8, zero);
    sw(v0 + 4, zero);
    v0 = 0;
    close_frame(32, 16, 0, 1);
}

// sub_3D2710 / sub_3D2DD0 [fclCombineStepNop]: step callbacks that read the node payload (sub_3C5470) and return 0.
void Fu::payload_nop(u32 pc) {
    enter(10);
    open_frame(16, 0, 0, 0);
    a0 = a1;
    jal(pc, gen::fn_sub_3C5470_003c5470);
    v0 = 0;
    close_frame(16, 0, 0, 0);
}

void Fu::sub_3D2710() { payload_nop(0x3d271c); }
void Fu::sub_3D2DD0() { payload_nop(0x3d2ddc); }

// sub_3D3280 [fclCombineMenuClose]: $a0 a menu holder: closes its command window (+0 -> +8) at once (nmCmdListClose, then
// nmCmdListCloseNow) when both exist.
void Fu::sub_3D3280() {
    enter(5);
    open_frame(32, 16, 0, 1);
    if (a0 == 0 || (charge(3), v1 = lw(a0), v1 == 0)) {
        charge(2);
    } else {
        charge(7);
        s0 = lw(v1 + 8);
        a0 = s0;
        jal(0x3d32b0, gen::fn_nmCmdListClose_003c6f10);
        a0 = s0;
        jal(0x3d32bc, gen::fn_nmCmdListCloseNow_003c6f50);
    }
    charge(5);
    close_frame(32, 16, 0, 1);
}

// sub_3D35C0 [fclCombineStepFree]: a step callback: frees the payload's element holder (+16, sub_3DED40), its element
// list (+20, sub_3DFF00) and its command window (+8, nmCmdListDestroy); returns 0.
void Fu::sub_3D35C0() {
    enter(22);
    open_frame(32, 16, 0, 1);
    a0 = a1;
    jal(0x3d35d0, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    a0 = lw(v0 + 16);
    jal(0x3d35e0, gen::fn_sub_3DED40_003ded40);
    a0 = lw(s0 + 20);
    jal(0x3d35ec, gen::fn_sub_3DFF00_003dff00);
    a0 = lw(s0 + 8);
    jal(0x3d35f8, gen::fn_nmCmdListDestroy_003c5a20);
    v0 = 0;
    close_frame(32, 16, 0, 1);
}

// sub_3D3B70 [fclCombineAddStep2]: $a0 a work record (may be 0), $a1 a word. Step 2 of the 36-byte descriptor 0x6A4870
// (delay 0, life 2), kept at work + 24; the step payload's +8 = $a1. Returns the step.
void Fu::sub_3D3B70() {
    enter(11);
    open_frame(112, 48, 0, 3);
    s1 = a0;
    s0 = a1;
    a1 = addiu(lui(0x6a), 18544);
    a0 = addiu(sp, 64);
    v1 = 2;
    for (;;) {
        charge(7);
        lq(v0, a1);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(a0, v0);
        a0 = addiu(a0, 16);
        if (sgn(v1) <= 0) break;
        backedge();
    }
    charge(15);
    lwc1(F0, a1);
    swc1(F0, a0);
    a0 = lw(gp - 18028);
    a1 = 2;
    a2 = addiu(sp, 64);
    a3 = 0;
    t0 = a1;
    jal(0x3d3bd4, gen::fn_nmSequenceAddStep_003c5240);
    s2 = v0;
    a0 = s2;
    jal(0x3d3be4, gen::fn_sub_3C5470_003c5470);
    if (s1 != 0) {
        charge(1);
        sw(s1 + 24, s2);
    }
    charge(9);
    sw(v0 + 8, s0);
    v0 = s2;
    close_frame(112, 48, 0, 3);
}

void Fu::sub_3D3C20() { take_step(24, 0x3d3c64); }

// sub_3D3CA0 [fclCombineStepMarkDone]: a step callback: the node payload's +4 = 1; returns 0.
void Fu::sub_3D3CA0() {
    enter(12);
    open_frame(16, 0, 0, 0);
    a0 = a1;
    jal(0x3d3cac, gen::fn_sub_3C5470_003c5470);
    v1 = 1;
    sw(v0 + 4, v1);
    v0 = 0;
    close_frame(16, 0, 0, 0);
}

// sub_3DA3A0 [fclCombineListFree]: $a0 the list: destroys its element list (+428, sub_3DFF00) and its command window
// (+20, nmCmdListDestroy).
void Fu::sub_3DA3A0() {
    enter(15);
    open_frame(32, 16, 0, 1);
    s0 = lw(a0 + 20);
    a0 = lw(a0 + 428);
    jal(0x3da3b4, gen::fn_sub_3DFF00_003dff00);
    a0 = s0;
    jal(0x3da3c0, gen::fn_nmCmdListDestroy_003c5a20);
    close_frame(32, 16, 0, 1);
}

// sub_3DB580 [fclCombineListDraw]: $a0 the list (may be 0): draws its command window (+20, nmCmdListDraw), the persona
// panel (sub_3DDB00) and the status panel (+116, sub_3DE160); returns 0.
void Fu::sub_3DB580() {
    enter(6);
    open_frame(32, 16, 0, 1);
    s0 = a0;
    if (s0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(10);
        a0 = lw(s0 + 20);
        jal(0x3db5a8, gen::fn_nmCmdListDraw_003c6380);
        a0 = s0;
        jal(0x3db5b4, gen::fn_sub_3DDB00_003ddb00);
        a0 = addiu(s0, 116);
        jal(0x3db5c0, gen::fn_sub_3DE160_003de160);
        v0 = 0;
    }
    charge(5);
    close_frame(32, 16, 0, 1);
}

// sub_3DB5E0 [fclCombineListRemoveFiltered]: $a0 a command window object: removes the finished elements (sub_3E0650)
// of the owner list's element list (+36 -> +68 -> +428) and of every row record's (+96).
void Fu::sub_3DB5E0() {
    enter(12);
    open_frame(32, 16, 0, 1);
    s0 = a0;
    v0 = lw(a0 + 36);
    v0 = lw(v0 + 68);
    a0 = lw(v0 + 428);
    jal(0x3db5fc, gen::fn_sub_3E0650_003e0650);
    s0 = lw(s0 + 4);
    for (;;) {
        charge(2);
        if (s0 == 0) break;
        backedge();
        charge(6);
        v0 = lw(s0 + 20);
        v0 = lw(v0 + 28);
        a0 = lw(v0 + 96);
        jal(0x3db61c, gen::fn_sub_3E0650_003e0650);
        s0 = lw(s0 + 16);
    }
    charge(5);
    close_frame(32, 16, 0, 1);
}

// sub_3DC210 / sub_3DEB80 [fclCombineListRefresh2 / fclCombineListRefresh]: command-window callbacks ($a3 the window
// object). With the owner list's element list (+36 -> +68; elements +428) they run the row text builder sub_3DB650 on
// every element (sub_3E0680), then nmListRemoveFiltered on the window with the owner's bit 16 set; sub_3DC210 clears and sets the
// bit again around a second pass. The bit ends clear.
void Fu::sub_3DC210() {
    enter(45);
    open_frame(48, 32, 0, 2);
    s1 = a3;
    v0 = lw(a3 + 36);
    s0 = lw(v0 + 68);            // the owner list
    a0 = lw(s0 + 428);
    a1 = addiu(lui(0x3eu), -18864);  // sub_3DB650
    a2 = s1;
    jal(0x3dc23c, gen::fn_sub_3E0680_003e0680);
    v1 = lw(s0);
    v0 = lui(0x1u);
    v0 = v1 | v0;
    sw(s0, v0);
    a0 = s1;
    jal(0x3dc258, gen::fn_nmListRemoveFiltered_003c4e70);
    v1 = lw(s0);
    v0 = lui(0xfffeu) | 0xffffu;
    v1 = v1 & v0;
    sw(s0, v1);
    v0 = lui(0x1u);
    v0 = v1 | v0;
    sw(s0, v0);
    a0 = lw(s0 + 428);
    a1 = addiu(lui(0x3eu), -18864);
    a2 = s1;
    jal(0x3dc290, gen::fn_sub_3E0680_003e0680);
    a0 = lw(s0);
    v1 = lui(0xfffeu) | 0xffffu;
    v1 = a0 & v1;
    sw(s0, v1);
    close_frame(48, 32, 0, 2);
}

void Fu::sub_3DEB80() {
    enter(31);
    open_frame(48, 32, 0, 2);
    s1 = a3;
    v0 = lw(a3 + 36);
    s0 = lw(v0 + 68);
    a0 = lw(s0 + 428);
    a1 = addiu(lui(0x3eu), -18864);  // sub_3DB650
    a2 = s1;
    jal(0x3debac, gen::fn_sub_3E0680_003e0680);
    v1 = lw(s0);
    v0 = lui(0x1u);
    v0 = v1 | v0;
    sw(s0, v0);
    a0 = s1;
    jal(0x3debc8, gen::fn_nmListRemoveFiltered_003c4e70);
    a0 = lw(s0);
    v1 = lui(0xfffeu) | 0xffffu;
    v1 = a0 & v1;
    sw(s0, v1);
    close_frame(48, 32, 0, 2);
}

// sub_3DEC00 [fclCombineListDrawRow]: the row-draw callback ($a0 x, $a1 y, $a2 colour, $a3 the window object, $t0 the
// row node). Fills a 28-byte frame record {x, y, s16 colour, s16 flags (bit 0: the row is the cursor, window +12), the
// owner list, the row record, the window, the row} and runs the row drawer sub_3DD260 on the row record's elements
// (+96; sub_3E0680).
void Fu::sub_3DEC00() {
    enter(24);
    open_frame(128, 80, 0, 5);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    s0 = t0;
    a0 = addiu(sp, 96);
    a1 = 0;
    a2 = 28;
    jal(0x3dec3c, gen::fn_memset_00521408);
    v0 = lw(s1 + 36);
    a0 = lw(v0 + 68);
    v0 = lw(s0 + 20);
    v1 = lw(v0 + 28);
    v0 = lw(s1 + 12);
    if (s0 == v0) {
        charge(3);
        v0 = lh(sp + 106);
        v0 = v0 | 0x1u;
        sh(sp + 106, v0);
    }
    charge(22);
    sw(sp + 96, s4);
    sw(sp + 100, s3);
    sh(sp + 104, s2);
    sw(sp + 108, a0);
    sw(sp + 112, v1);
    sw(sp + 116, s1);
    sw(sp + 120, s0);
    a0 = lw(v1 + 96);
    a1 = addiu(lui(0x3eu), -11680);  // sub_3DD260
    a2 = addiu(sp, 96);
    jal(0x3dec98, gen::fn_sub_3E0680_003e0680);
    close_frame(128, 80, 0, 5);
}

}  // namespace fusion::detail

// --- the public entry points (fusion.h) ---------------------------------------------------------------------------------
namespace {
using fusion::detail::Fu;
inline u64 run(EEContext& ctx, void (Fu::*body)(), std::initializer_list<u64> args) {
    unsigned r = GPR_A0;
    for (u64 a : args) ee::core::set_gpr64(ctx, r++, a);  // $a0..$a3, then $t0 / $t1
    (Fu(ctx).*body)();
    return ee::core::gpr64(ctx, GPR_V0);
}
}  // namespace

u64 sub_3D02E0(EEContext& ctx) { return run(ctx, &Fu::sub_3D02E0, {}); }
u64 sub_3D0600(EEContext& ctx) { return run(ctx, &Fu::sub_3D0600, {}); }
u64 sub_3D21D0(EEContext& ctx) { return run(ctx, &Fu::sub_3D21D0, {}); }
u64 sub_3D25C0(EEContext& ctx, u64 work) { return run(ctx, &Fu::sub_3D25C0, {work}); }
u64 sub_3D2640(EEContext& ctx, u64 work) { return run(ctx, &Fu::sub_3D2640, {work}); }
u64 sub_3D26C0(EEContext& ctx, u64 obj, u64 node) { return run(ctx, &Fu::sub_3D26C0, {obj, node}); }
u64 sub_3D2710(EEContext& ctx, u64 obj, u64 node) { return run(ctx, &Fu::sub_3D2710, {obj, node}); }
u64 sub_3D2C00(EEContext& ctx) { return run(ctx, &Fu::sub_3D2C00, {}); }
u64 sub_3D2DD0(EEContext& ctx, u64 obj, u64 node) { return run(ctx, &Fu::sub_3D2DD0, {obj, node}); }
u64 sub_3D2EF0(EEContext& ctx) { return run(ctx, &Fu::sub_3D2EF0, {}); }
u64 sub_3D3010(EEContext& ctx, u64 menu) { return run(ctx, &Fu::sub_3D3010, {menu}); }
u64 sub_3D3280(EEContext& ctx, u64 menu) { return run(ctx, &Fu::sub_3D3280, {menu}); }
u64 sub_3D35C0(EEContext& ctx, u64 obj, u64 node) { return run(ctx, &Fu::sub_3D35C0, {obj, node}); }
u64 sub_3D3B70(EEContext& ctx, u64 work, u64 arg) { return run(ctx, &Fu::sub_3D3B70, {work, arg}); }
u64 sub_3D3C20(EEContext& ctx, u64 work) { return run(ctx, &Fu::sub_3D3C20, {work}); }
u64 sub_3D3CA0(EEContext& ctx, u64 obj, u64 node) { return run(ctx, &Fu::sub_3D3CA0, {obj, node}); }
u64 sub_3D5510(EEContext& ctx, u64 out, u64 recipe, u64 need, u64 stock) { return run(ctx, &Fu::sub_3D5510, {out, recipe, need, stock}); }
u64 sub_3D5730(EEContext& ctx, u64 out, u64 category, u64 index, u64 stock) { return run(ctx, &Fu::sub_3D5730, {out, category, index, stock}); }
u64 sub_3D5850(EEContext& ctx, u64 index) { return run(ctx, &Fu::sub_3D5850, {index}); }
u64 sub_3D58A0(EEContext& ctx) { return run(ctx, &Fu::sub_3D58A0, {}); }
u64 sub_3D58C0(EEContext& ctx, u64 link, u64 level) { return run(ctx, &Fu::sub_3D58C0, {link, level}); }
u64 sub_3D5A40(EEContext& ctx, u64 recipe, u64 need, u64 ids, u64 count, u64 found) { return run(ctx, &Fu::sub_3D5A40, {recipe, need, ids, count, found}); }
u64 sub_3D5BB0(EEContext& ctx, u64 persona) { return run(ctx, &Fu::sub_3D5BB0, {persona}); }
u64 sub_3D5C90(EEContext& ctx) { return run(ctx, &Fu::sub_3D5C90, {}); }
u64 sub_3D5CD0(EEContext& ctx, u64 stock) { return run(ctx, &Fu::sub_3D5CD0, {stock}); }
u64 sub_3D5DC0(EEContext& ctx, u64 persona) { return run(ctx, &Fu::sub_3D5DC0, {persona}); }
u64 sub_3D5E60(EEContext& ctx, u64 p0, u64 p1, u64 p2) { return run(ctx, &Fu::sub_3D5E60, {p0, p1, p2}); }
u64 sub_3D6200(EEContext& ctx, u64 out, u64 category, u64 ids, u64 count) { return run(ctx, &Fu::sub_3D6200, {out, category, ids, count}); }
u64 sub_3D64A0(EEContext& ctx, u64 out, u64 id0, u64 id1) { return run(ctx, &Fu::sub_3D64A0, {out, id0, id1}); }
u64 sub_3D6740(EEContext& ctx, u64 out, u64 p0, u64 p1, u64 p2) { return run(ctx, &Fu::sub_3D6740, {out, p0, p1, p2}); }
u64 sub_3D6910(EEContext& ctx, u64 out, u64 kind, u64 personas) { return run(ctx, &Fu::sub_3D6910, {out, kind, personas}); }
u64 sub_3D6AE0(EEContext& ctx, u64 result, u64 kind, u64 personas) { return run(ctx, &Fu::sub_3D6AE0, {result, kind, personas}); }
u64 sub_3D6C90(EEContext& ctx, u64 kind) { return run(ctx, &Fu::sub_3D6C90, {kind}); }
u64 sub_3D6E60(EEContext& ctx, u64 result, u64 from) { return run(ctx, &Fu::sub_3D6E60, {result, from}); }
u64 sub_3D6F80(EEContext& ctx, u64 result, u64 from, u64 exclude) { return run(ctx, &Fu::sub_3D6F80, {result, from, exclude}); }
u64 sub_3D7180(EEContext& ctx) { return run(ctx, &Fu::sub_3D7180, {}); }
u64 sub_3D71D0(EEContext& ctx, u64 result, u64 from, u64 exclude) { return run(ctx, &Fu::sub_3D71D0, {result, from, exclude}); }
u64 sub_3D72F0(EEContext& ctx, u64 result) { return run(ctx, &Fu::sub_3D72F0, {result}); }
u64 sub_3D74B0(EEContext& ctx, u64 persona) { return run(ctx, &Fu::sub_3D74B0, {persona}); }
u64 sub_3D7A30(EEContext& ctx, u64 persona, u64 personas, u64 count) { return run(ctx, &Fu::sub_3D7A30, {persona, personas, count}); }
u64 sub_3D7AC0(EEContext& ctx, u64 arcana, u64 level, u64 exclude) { return run(ctx, &Fu::sub_3D7AC0, {arcana, level, exclude}); }
u64 sub_3D7DA0(EEContext& ctx, u64 arcana, u64 level, u64 exclude) { return run(ctx, &Fu::sub_3D7DA0, {arcana, level, exclude}); }
u64 sub_3D8080(EEContext& ctx, u64 result, u64 personas, u64 count) { return run(ctx, &Fu::sub_3D8080, {result, personas, count}); }
u64 sub_3D8230(EEContext& ctx, u64 result) { return run(ctx, &Fu::sub_3D8230, {result}); }
u64 sub_3D8260(EEContext& ctx, u64 stock, u64 first) { return run(ctx, &Fu::sub_3D8260, {stock, first}); }
u64 sub_3D8370(EEContext& ctx, u64 stock, u64 first, u64 second) { return run(ctx, &Fu::sub_3D8370, {stock, first, second}); }
u64 sub_3D84C0(EEContext& ctx, u64 unused, u64 category) { return run(ctx, &Fu::sub_3D84C0, {unused, category}); }
u64 sub_3D8630(EEContext& ctx, u64 stock, u64 category) { return run(ctx, &Fu::sub_3D8630, {stock, category}); }
u64 sub_3D8830(EEContext& ctx, u64 category) { return run(ctx, &Fu::sub_3D8830, {category}); }
u64 sub_3D9C90(EEContext& ctx, u64 obj, u64 node) { return run(ctx, &Fu::sub_3D9C90, {obj, node}); }
u64 sub_3DA2A0(EEContext& ctx, u64 list) { return run(ctx, &Fu::sub_3DA2A0, {list}); }
u64 sub_3DA3A0(EEContext& ctx, u64 list) { return run(ctx, &Fu::sub_3DA3A0, {list}); }
u64 sub_3DA3E0(EEContext& ctx, u64 list, u64 index) { return run(ctx, &Fu::sub_3DA3E0, {list, index}); }
u64 sub_3DA470(EEContext& ctx, u64 list, u64 persona) { return run(ctx, &Fu::sub_3DA470, {list, persona}); }
u64 sub_3DA570(EEContext& ctx, u64 list) { return run(ctx, &Fu::sub_3DA570, {list}); }
u64 sub_3DB580(EEContext& ctx, u64 list) { return run(ctx, &Fu::sub_3DB580, {list}); }
u64 sub_3DB5E0(EEContext& ctx, u64 list) { return run(ctx, &Fu::sub_3DB5E0, {list}); }
u64 sub_3DC210(EEContext& ctx, u64 a0, u64 a1, u64 a2, u64 obj) { return run(ctx, &Fu::sub_3DC210, {a0, a1, a2, obj}); }
u64 sub_3DEB20(EEContext& ctx, u64 list) { return run(ctx, &Fu::sub_3DEB20, {list}); }
u64 sub_3DEB80(EEContext& ctx, u64 a0, u64 a1, u64 a2, u64 obj) { return run(ctx, &Fu::sub_3DEB80, {a0, a1, a2, obj}); }
u64 sub_3DEC00(EEContext& ctx, u64 a0, u64 a1, u64 a2, u64 obj, u64 row) { return run(ctx, &Fu::sub_3DEC00, {a0, a1, a2, obj, row}); }
u64 sub_3DECD0(EEContext& ctx, u64 owner) { return run(ctx, &Fu::sub_3DECD0, {owner}); }
u64 sub_3DED40(EEContext& ctx, u64 elems) { return run(ctx, &Fu::sub_3DED40, {elems}); }
u64 sub_3DED70(EEContext& ctx, u64 elems) { return run(ctx, &Fu::sub_3DED70, {elems}); }
u64 sub_3DEE80(EEContext& ctx, u64 elems, u64 a1, u64 a2, u64 a3, u64 t0, u64 t1) { return run(ctx, &Fu::sub_3DEE80, {elems, a1, a2, a3, t0, t1}); }
u64 sub_3DEF10(EEContext& ctx, u64 n) { return run(ctx, &Fu::sub_3DEF10, {n}); }
u64 sub_3DEF40(EEContext& ctx, u64 width, u64 n, u64 i) { return run(ctx, &Fu::sub_3DEF40, {width, n, i}); }
u64 sub_3DEF80(EEContext& ctx, u64 elems) { return run(ctx, &Fu::sub_3DEF80, {elems}); }
u64 sub_3DF010(EEContext& ctx, u64 elems) { return run(ctx, &Fu::sub_3DF010, {elems}); }
u64 sub_3DF090(EEContext& ctx, u64 elems, u64 extra) { return run(ctx, &Fu::sub_3DF090, {elems, extra}); }
u64 sub_3DF100(EEContext& ctx, u64 elem, u64 desc) { return run(ctx, &Fu::sub_3DF100, {elem, desc}); }
u64 sub_3DF220(EEContext& ctx, u64 elem, u64 a1, u64 a2, u64 a3, u64 t0, u64 t1) { return run(ctx, &Fu::sub_3DF220, {elem, a1, a2, a3, t0, t1}); }

}  // namespace p3fes::game

// --- the recompiled program's entry points --------------------------------------------------------------------------------
namespace p3fes::recomp_gen {
namespace fd = ::p3fes::game::fusion::detail;
#define FUSION_SHIM(name, addr) \
    void fn_##name##_##addr(p3fes::EEContext& ctx) { fd::Fu(ctx).name(); }
FUSION_SHIM(sub_3D02E0, 003d02e0)
FUSION_SHIM(sub_3D0600, 003d0600)
FUSION_SHIM(sub_3D21D0, 003d21d0)
FUSION_SHIM(sub_3D25C0, 003d25c0)
FUSION_SHIM(sub_3D2640, 003d2640)
FUSION_SHIM(sub_3D26C0, 003d26c0)
FUSION_SHIM(sub_3D2710, 003d2710)
FUSION_SHIM(sub_3D2C00, 003d2c00)
FUSION_SHIM(sub_3D2DD0, 003d2dd0)
FUSION_SHIM(sub_3D2EF0, 003d2ef0)
FUSION_SHIM(sub_3D3010, 003d3010)
FUSION_SHIM(sub_3D3280, 003d3280)
FUSION_SHIM(sub_3D35C0, 003d35c0)
FUSION_SHIM(sub_3D3B70, 003d3b70)
FUSION_SHIM(sub_3D3C20, 003d3c20)
FUSION_SHIM(sub_3D3CA0, 003d3ca0)
FUSION_SHIM(sub_3D5510, 003d5510)
FUSION_SHIM(sub_3D5730, 003d5730)
FUSION_SHIM(sub_3D5850, 003d5850)
FUSION_SHIM(sub_3D58A0, 003d58a0)
FUSION_SHIM(sub_3D58C0, 003d58c0)
FUSION_SHIM(sub_3D5A40, 003d5a40)
FUSION_SHIM(sub_3D5BB0, 003d5bb0)
FUSION_SHIM(sub_3D5C90, 003d5c90)
FUSION_SHIM(sub_3D5CD0, 003d5cd0)
FUSION_SHIM(sub_3D5DC0, 003d5dc0)
FUSION_SHIM(sub_3D5E60, 003d5e60)
FUSION_SHIM(sub_3D6200, 003d6200)
FUSION_SHIM(sub_3D64A0, 003d64a0)
FUSION_SHIM(sub_3D6740, 003d6740)
FUSION_SHIM(sub_3D6910, 003d6910)
FUSION_SHIM(sub_3D6AE0, 003d6ae0)
FUSION_SHIM(sub_3D6C90, 003d6c90)
FUSION_SHIM(sub_3D6E60, 003d6e60)
FUSION_SHIM(sub_3D6F80, 003d6f80)
FUSION_SHIM(sub_3D7180, 003d7180)
FUSION_SHIM(sub_3D71D0, 003d71d0)
FUSION_SHIM(sub_3D72F0, 003d72f0)
FUSION_SHIM(sub_3D74B0, 003d74b0)
FUSION_SHIM(sub_3D7A30, 003d7a30)
FUSION_SHIM(sub_3D7AC0, 003d7ac0)
FUSION_SHIM(sub_3D7DA0, 003d7da0)
FUSION_SHIM(sub_3D8080, 003d8080)
FUSION_SHIM(sub_3D8230, 003d8230)
FUSION_SHIM(sub_3D8260, 003d8260)
FUSION_SHIM(sub_3D8370, 003d8370)
FUSION_SHIM(sub_3D84C0, 003d84c0)
FUSION_SHIM(sub_3D8630, 003d8630)
FUSION_SHIM(sub_3D8830, 003d8830)
FUSION_SHIM(sub_3D9C90, 003d9c90)
FUSION_SHIM(sub_3DA2A0, 003da2a0)
FUSION_SHIM(sub_3DA3A0, 003da3a0)
FUSION_SHIM(sub_3DA3E0, 003da3e0)
FUSION_SHIM(sub_3DA470, 003da470)
FUSION_SHIM(sub_3DA570, 003da570)
FUSION_SHIM(sub_3DB580, 003db580)
FUSION_SHIM(sub_3DB5E0, 003db5e0)
FUSION_SHIM(sub_3DC210, 003dc210)
FUSION_SHIM(sub_3DEB20, 003deb20)
FUSION_SHIM(sub_3DEB80, 003deb80)
FUSION_SHIM(sub_3DEC00, 003dec00)
FUSION_SHIM(sub_3DECD0, 003decd0)
FUSION_SHIM(sub_3DED40, 003ded40)
FUSION_SHIM(sub_3DED70, 003ded70)
FUSION_SHIM(sub_3DEE80, 003dee80)
FUSION_SHIM(sub_3DEF10, 003def10)
FUSION_SHIM(sub_3DEF40, 003def40)
FUSION_SHIM(sub_3DEF80, 003def80)
FUSION_SHIM(sub_3DF010, 003df010)
FUSION_SHIM(sub_3DF090, 003df090)
FUSION_SHIM(sub_3DF100, 003df100)
FUSION_SHIM(sub_3DF220, 003df220)
#undef FUSION_SHIM
}  // namespace p3fes::recomp_gen
