// The game-state data layer of g_data.c / datPersona.c (slice gamedata; gamedata.h documents the records): the party
// member accessors, the social links, money and the party list, the equipment entries and item counts, the day-event
// records and the hero's persona stock. The bodies are p3fes_handgen's (game/include/p3fes/game/hg_cpu.h): register
// for register and block for block as the recompiled bodies -- frame, spills, $ra links, cycle charges and check
// points -- with each function's role, the record offsets and the branch meanings named on top, the inlined id checks
// and the stock searches restructured without gotos (the same statements, charges and check points on every path).
//
// Conventions in the bodies: `pc` 1 is the hero (gGlobalWork +0x24 / +0x60.. / +0x58C..), any other pc a party record
// (0x834010 + 868 * (pc - 2): the bodies compute 868 * pc as ((pc * 31) * 7) * 4 with shifts); the id checks
// `0 <= comu < 30` are inlined everywhere as a bool in a register followed by `if (!ok) K_Assert(file, line)`; K_Assert
// (sub_19D3F0) is `jr $ra` in retail, so a failed check continues with the bad index, as here.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/gamedata.h"

namespace p3fes::recomp_gen {
void fn_MT_Misc_BitChk_003951d0(p3fes::EEContext&);
void fn_clndGetCurrentDay_0017da40(p3fes::EEContext&);
void fn_clndGetCurrentMonth_0017d920(p3fes::EEContext&);
void fn_datCalcClearBadStatus_00300560(p3fes::EEContext&);
void fn_datCalcGetBadStatusNoDown_00300530(p3fes::EEContext&);
void fn_datCalcGetHp_002ffd70(p3fes::EEContext&);
void fn_datCalcGetLevel_002ffcc0(p3fes::EEContext&);
void fn_datCalcGetMaxHp_002ffdf0(p3fes::EEContext&);
void fn_datCalcGetMaxSp_00300100(p3fes::EEContext&);
void fn_datCalcGetSp_002ffd80(p3fes::EEContext&);
void fn_datCalcSetBadStatus_003004f0(p3fes::EEContext&);
void fn_datGetDaysSinceApr5_0016ef20(p3fes::EEContext&);
void fn_datPersonaGetByPcId_00174800(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sub_16C470_0016c470(p3fes::EEContext&);
void fn_sub_16C4F0_0016c4f0(p3fes::EEContext&);
void fn_sub_16C570_0016c570(p3fes::EEContext&);
void fn_sub_16C5F0_0016c5f0(p3fes::EEContext&);
void fn_sub_16C670_0016c670(p3fes::EEContext&);
void fn_sub_16C7E0_0016c7e0(p3fes::EEContext&);
void fn_sub_16C860_0016c860(p3fes::EEContext&);
void fn_sub_16C910_0016c910(p3fes::EEContext&);
void fn_sub_16C920_0016c920(p3fes::EEContext&);
void fn_sub_16C970_0016c970(p3fes::EEContext&);
void fn_sub_16C9F0_0016c9f0(p3fes::EEContext&);
void fn_sub_16CA40_0016ca40(p3fes::EEContext&);
void fn_sub_16CA90_0016ca90(p3fes::EEContext&);
void fn_sub_16CDF0_0016cdf0(p3fes::EEContext&);
void fn_sub_16CEF0_0016cef0(p3fes::EEContext&);
void fn_sub_16CF40_0016cf40(p3fes::EEContext&);
void fn_sub_16CF90_0016cf90(p3fes::EEContext&);
void fn_sub_16D230_0016d230(p3fes::EEContext&);
void fn_sub_16D280_0016d280(p3fes::EEContext&);
void fn_sub_16D560_0016d560(p3fes::EEContext&);
void fn_sub_16D6B0_0016d6b0(p3fes::EEContext&);
void fn_sub_16D8B0_0016d8b0(p3fes::EEContext&);
void fn_sub_16D930_0016d930(p3fes::EEContext&);
void fn_sub_16D980_0016d980(p3fes::EEContext&);
void fn_sub_16D9D0_0016d9d0(p3fes::EEContext&);
void fn_sub_16DA50_0016da50(p3fes::EEContext&);
void fn_sub_16DAD0_0016dad0(p3fes::EEContext&);
void fn_sub_16DB70_0016db70(p3fes::EEContext&);
void fn_sub_16DBA0_0016dba0(p3fes::EEContext&);
void fn_sub_16DBC0_0016dbc0(p3fes::EEContext&);
void fn_sub_16DCE0_0016dce0(p3fes::EEContext&);
void fn_sub_16DD20_0016dd20(p3fes::EEContext&);
void fn_sub_16DD40_0016dd40(p3fes::EEContext&);
void fn_sub_16DD50_0016dd50(p3fes::EEContext&);
void fn_sub_16DD60_0016dd60(p3fes::EEContext&);
void fn_sub_16DD80_0016dd80(p3fes::EEContext&);
void fn_sub_16DDD0_0016ddd0(p3fes::EEContext&);
void fn_sub_16DE50_0016de50(p3fes::EEContext&);
void fn_sub_16DEB0_0016deb0(p3fes::EEContext&);
void fn_sub_16DF30_0016df30(p3fes::EEContext&);
void fn_sub_16DFB0_0016dfb0(p3fes::EEContext&);
void fn_sub_16E100_0016e100(p3fes::EEContext&);
void fn_sub_16E2B0_0016e2b0(p3fes::EEContext&);
void fn_sub_16E410_0016e410(p3fes::EEContext&);
void fn_sub_16E5F0_0016e5f0(p3fes::EEContext&);
void fn_sub_16E670_0016e670(p3fes::EEContext&);
void fn_sub_16E7A0_0016e7a0(p3fes::EEContext&);
void fn_sub_16E850_0016e850(p3fes::EEContext&);
void fn_sub_16E920_0016e920(p3fes::EEContext&);
void fn_sub_16E930_0016e930(p3fes::EEContext&);
void fn_sub_16E990_0016e990(p3fes::EEContext&);
void fn_sub_16E9B0_0016e9b0(p3fes::EEContext&);
void fn_sub_16EA40_0016ea40(p3fes::EEContext&);
void fn_sub_16F3E0_0016f3e0(p3fes::EEContext&);
void fn_sub_16F490_0016f490(p3fes::EEContext&);
void fn_sub_16F720_0016f720(p3fes::EEContext&);
void fn_sub_16F810_0016f810(p3fes::EEContext&);
void fn_sub_16F9F0_0016f9f0(p3fes::EEContext&);
void fn_sub_16FAE0_0016fae0(p3fes::EEContext&);
void fn_sub_16FBD0_0016fbd0(p3fes::EEContext&);
void fn_sub_16FCC0_0016fcc0(p3fes::EEContext&);
void fn_sub_16FDB0_0016fdb0(p3fes::EEContext&);
void fn_sub_16FEA0_0016fea0(p3fes::EEContext&);
void fn_sub_16FF90_0016ff90(p3fes::EEContext&);
void fn_sub_170080_00170080(p3fes::EEContext&);
void fn_sub_170170_00170170(p3fes::EEContext&);
void fn_sub_170260_00170260(p3fes::EEContext&);
void fn_sub_170350_00170350(p3fes::EEContext&);
void fn_sub_170440_00170440(p3fes::EEContext&);
void fn_sub_170530_00170530(p3fes::EEContext&);
void fn_sub_170620_00170620(p3fes::EEContext&);
void fn_sub_170670_00170670(p3fes::EEContext&);
void fn_sub_1706C0_001706c0(p3fes::EEContext&);
void fn_sub_170710_00170710(p3fes::EEContext&);
void fn_sub_170760_00170760(p3fes::EEContext&);
void fn_sub_170860_00170860(p3fes::EEContext&);
void fn_sub_170A40_00170a40(p3fes::EEContext&);
void fn_sub_170AB0_00170ab0(p3fes::EEContext&);
void fn_sub_170B20_00170b20(p3fes::EEContext&);
void fn_sub_170B90_00170b90(p3fes::EEContext&);
void fn_sub_170C00_00170c00(p3fes::EEContext&);
void fn_sub_171060_00171060(p3fes::EEContext&);
void fn_sub_171110_00171110(p3fes::EEContext&);
void fn_sub_171250_00171250(p3fes::EEContext&);
void fn_sub_171360_00171360(p3fes::EEContext&);
void fn_sub_171390_00171390(p3fes::EEContext&);
void fn_sub_1717B0_001717b0(p3fes::EEContext&);
void fn_sub_1717C0_001717c0(p3fes::EEContext&);
void fn_sub_1718B0_001718b0(p3fes::EEContext&);
void fn_sub_171960_00171960(p3fes::EEContext&);
void fn_sub_171AC0_00171ac0(p3fes::EEContext&);
void fn_sub_171B50_00171b50(p3fes::EEContext&);
void fn_sub_171C40_00171c40(p3fes::EEContext&);
void fn_sub_171E90_00171e90(p3fes::EEContext&);
void fn_sub_171F50_00171f50(p3fes::EEContext&);
void fn_sub_1720C0_001720c0(p3fes::EEContext&);
void fn_sub_172160_00172160(p3fes::EEContext&);
void fn_sub_172200_00172200(p3fes::EEContext&);
void fn_sub_1723A0_001723a0(p3fes::EEContext&);
void fn_sub_1724A0_001724a0(p3fes::EEContext&);
void fn_sub_1725A0_001725a0(p3fes::EEContext&);
void fn_sub_172660_00172660(p3fes::EEContext&);
void fn_sub_172820_00172820(p3fes::EEContext&);
void fn_sub_172890_00172890(p3fes::EEContext&);
void fn_sub_1728D0_001728d0(p3fes::EEContext&);
void fn_sub_172990_00172990(p3fes::EEContext&);
void fn_sub_1729A0_001729a0(p3fes::EEContext&);
void fn_sub_1729D0_001729d0(p3fes::EEContext&);
void fn_sub_172A10_00172a10(p3fes::EEContext&);
void fn_sub_172A20_00172a20(p3fes::EEContext&);
void fn_sub_172A30_00172a30(p3fes::EEContext&);
void fn_sub_172AB0_00172ab0(p3fes::EEContext&);
void fn_sub_172AE0_00172ae0(p3fes::EEContext&);
void fn_sub_172B20_00172b20(p3fes::EEContext&);
void fn_sub_172C50_00172c50(p3fes::EEContext&);
void fn_sub_172CC0_00172cc0(p3fes::EEContext&);
void fn_sub_172D70_00172d70(p3fes::EEContext&);
void fn_sub_172E10_00172e10(p3fes::EEContext&);
void fn_sub_172E40_00172e40(p3fes::EEContext&);
void fn_sub_173280_00173280(p3fes::EEContext&);
void fn_sub_173300_00173300(p3fes::EEContext&);
void fn_sub_173330_00173330(p3fes::EEContext&);
void fn_sub_173340_00173340(p3fes::EEContext&);
void fn_sub_173370_00173370(p3fes::EEContext&);
void fn_sub_173580_00173580(p3fes::EEContext&);
void fn_sub_173660_00173660(p3fes::EEContext&);
void fn_sub_173780_00173780(p3fes::EEContext&);
void fn_sub_173A00_00173a00(p3fes::EEContext&);
void fn_sub_173B00_00173b00(p3fes::EEContext&);
void fn_sub_173B60_00173b60(p3fes::EEContext&);
void fn_sub_173BB0_00173bb0(p3fes::EEContext&);
void fn_sub_173C00_00173c00(p3fes::EEContext&);
void fn_sub_173C60_00173c60(p3fes::EEContext&);
void fn_sub_174650_00174650(p3fes::EEContext&);
void fn_sub_174710_00174710(p3fes::EEContext&);
void fn_sub_1748C0_001748c0(p3fes::EEContext&);
void fn_sub_174960_00174960(p3fes::EEContext&);
void fn_sub_1749A0_001749a0(p3fes::EEContext&);
void fn_sub_174A90_00174a90(p3fes::EEContext&);
void fn_sub_174B40_00174b40(p3fes::EEContext&);
void fn_sub_174C10_00174c10(p3fes::EEContext&);
void fn_sub_174E20_00174e20(p3fes::EEContext&);
void fn_sub_174E70_00174e70(p3fes::EEContext&);
void fn_sub_174FB0_00174fb0(p3fes::EEContext&);
void fn_sub_175130_00175130(p3fes::EEContext&);
void fn_sub_175200_00175200(p3fes::EEContext&);
void fn_sub_1752B0_001752b0(p3fes::EEContext&);
void fn_sub_175360_00175360(p3fes::EEContext&);
void fn_sub_175410_00175410(p3fes::EEContext&);
void fn_sub_1754A0_001754a0(p3fes::EEContext&);
void fn_sub_1755C0_001755c0(p3fes::EEContext&);
void fn_sub_1756F0_001756f0(p3fes::EEContext&);
void fn_sub_1757F0_001757f0(p3fes::EEContext&);
void fn_sub_175BE0_00175be0(p3fes::EEContext&);
void fn_sub_175C70_00175c70(p3fes::EEContext&);
void fn_sub_175CA0_00175ca0(p3fes::EEContext&);
void fn_sub_176100_00176100(p3fes::EEContext&);
void fn_sub_1761B0_001761b0(p3fes::EEContext&);
void fn_sub_176210_00176210(p3fes::EEContext&);
void fn_sub_176680_00176680(p3fes::EEContext&);
void fn_sub_17AD90_0017ad90(p3fes::EEContext&);
void fn_sub_17CD30_0017cd30(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_395170_00395170(p3fes::EEContext&);
void fn_sub_3951A0_003951a0(p3fes::EEContext&);
void fn_sub_3BDB80_003bdb80(p3fes::EEContext&);
void fn_sub_3BDD90_003bdd90(p3fes::EEContext&);
void fn_sub_3BDDD0_003bddd0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
namespace pf = gamedata::persona;  // Persona field offsets (gamedata.h)

// 0x0016C470 sub_16C470 [datGetPcLevel] -- 116 bytes; frame 0x10: ra sp+0x0
// sub_16C470(pc): datCalcGetLevel of pc's DatUnit (pc 1: the hero's gGlobalWork +0x24, else party record pc +4).
void sub_16C470(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016c470
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);  // (s16)pc
    v0 = 1;
    if (v1 != v0) {  // a party member (pc 1 is the hero)
        // 0x0016c4a4
        charge(ctx, 12);
        v1 = addiu(v1, -2);  // 868 * (pc - 2) = (((pc - 2) * 31) * 7) * 4:
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &kPartyRecords (pc 2's record)
        v0 = addu(v0, v1);
        a0 = addiu(v0, 4);  // &record(pc)->unit
        jal(ctx, 0x16C4CCu, gen::fn_datCalcGetLevel_002ffcc0);
    } else {
        // 0x0016c48c
        charge(ctx, 6);
        a0 = 0x830000;
        a0 = addiu(a0, 25124);  // &kHeroUnit (gGlobalWork +0x24): the hero's DatUnit
        jal(ctx, 0x16C494u, gen::fn_datCalcGetLevel_002ffcc0);
    }
    // 0x0016c4d4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0016C4F0 sub_16C4F0 [datGetPcHp] -- 116 bytes; frame 0x10: ra sp+0x0
// sub_16C4F0(pc): datCalcGetHp of pc's DatUnit (the hero's or party record pc +4).
void sub_16C4F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016c4f0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);  // (s16)pc
    v0 = 1;
    if (v1 != v0) {  // a party member (pc 1 is the hero)
        // 0x0016c524
        charge(ctx, 12);
        v1 = addiu(v1, -2);  // 868 * (pc - 2) = (((pc - 2) * 31) * 7) * 4:
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &kPartyRecords (pc 2's record)
        v0 = addu(v0, v1);
        a0 = addiu(v0, 4);  // &record(pc)->unit
        jal(ctx, 0x16C54Cu, gen::fn_datCalcGetHp_002ffd70);
    } else {
        // 0x0016c50c
        charge(ctx, 6);
        a0 = 0x830000;
        a0 = addiu(a0, 25124);  // &kHeroUnit (gGlobalWork +0x24): the hero's DatUnit
        jal(ctx, 0x16C514u, gen::fn_datCalcGetHp_002ffd70);
    }
    // 0x0016c554 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0016C570 sub_16C570 [datGetPcSp] -- 116 bytes; frame 0x10: ra sp+0x0
// sub_16C570(pc): datCalcGetSp of pc's DatUnit.
void sub_16C570(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016c570
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);  // (s16)pc
    v0 = 1;
    if (v1 != v0) {  // a party member (pc 1 is the hero)
        // 0x0016c5a4
        charge(ctx, 12);
        v1 = addiu(v1, -2);  // 868 * (pc - 2) = (((pc - 2) * 31) * 7) * 4:
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &kPartyRecords (pc 2's record)
        v0 = addu(v0, v1);
        a0 = addiu(v0, 4);  // &record(pc)->unit
        jal(ctx, 0x16C5CCu, gen::fn_datCalcGetSp_002ffd80);
    } else {
        // 0x0016c58c
        charge(ctx, 6);
        a0 = 0x830000;
        a0 = addiu(a0, 25124);  // &kHeroUnit (gGlobalWork +0x24): the hero's DatUnit
        jal(ctx, 0x16C594u, gen::fn_datCalcGetSp_002ffd80);
    }
    // 0x0016c5d4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0016C5F0 sub_16C5F0 [datGetPcMaxHp] -- 116 bytes; frame 0x10: ra sp+0x0
// sub_16C5F0(pc): datCalcGetMaxHp of pc's DatUnit.
void sub_16C5F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016c5f0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);  // (s16)pc
    v0 = 1;
    if (v1 != v0) {  // a party member (pc 1 is the hero)
        // 0x0016c624
        charge(ctx, 12);
        v1 = addiu(v1, -2);  // 868 * (pc - 2) = (((pc - 2) * 31) * 7) * 4:
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &kPartyRecords (pc 2's record)
        v0 = addu(v0, v1);
        a0 = addiu(v0, 4);  // &record(pc)->unit
        jal(ctx, 0x16C64Cu, gen::fn_datCalcGetMaxHp_002ffdf0);
    } else {
        // 0x0016c60c
        charge(ctx, 6);
        a0 = 0x830000;
        a0 = addiu(a0, 25124);  // &kHeroUnit (gGlobalWork +0x24): the hero's DatUnit
        jal(ctx, 0x16C614u, gen::fn_datCalcGetMaxHp_002ffdf0);
    }
    // 0x0016c654 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0016C670 sub_16C670 [datGetPcMaxSp] -- 116 bytes; frame 0x10: ra sp+0x0
// sub_16C670(pc): datCalcGetMaxSp of pc's DatUnit.
void sub_16C670(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016c670
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);  // (s16)pc
    v0 = 1;
    if (v1 != v0) {  // a party member (pc 1 is the hero)
        // 0x0016c6a4
        charge(ctx, 12);
        v1 = addiu(v1, -2);  // 868 * (pc - 2) = (((pc - 2) * 31) * 7) * 4:
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &kPartyRecords (pc 2's record)
        v0 = addu(v0, v1);
        a0 = addiu(v0, 4);  // &record(pc)->unit
        jal(ctx, 0x16C6CCu, gen::fn_datCalcGetMaxSp_00300100);
    } else {
        // 0x0016c68c
        charge(ctx, 6);
        a0 = 0x830000;
        a0 = addiu(a0, 25124);  // &kHeroUnit (gGlobalWork +0x24): the hero's DatUnit
        jal(ctx, 0x16C694u, gen::fn_datCalcGetMaxSp_00300100);
    }
    // 0x0016c6d4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0016C7E0 sub_16C7E0 [datGetPcExp] -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_16C7E0(pc): pc's experience: the hero's s32 at gGlobalWork +0x68; a member's lives in its persona
// (datPersonaGetByPcId(pc)->exp, +8, via sub_173330; K_Assert line 622 on a null persona).
void sub_16C7E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016c7e0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);  // (s16)pc
    v0 = 1;
    if (v1 != v0) {  // a party member (pc 1 is the hero)
        // 0x0016c810
        charge(ctx, 6);
        a0 = a0 & 0xFFFF;
        jal(ctx, 0x16C814u, gen::fn_datPersonaGetByPcId_00174800);
        s0 = v0;
        if (s0 == 0) {
            // 0x0016c828
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 622;
            jal(ctx, 0x16C834u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 622): returns
        }
        // 0x0016c83c
        charge(ctx, 3);
        a0 = s0;
        jal(ctx, 0x16C840u, gen::fn_sub_173330_00173330);
    } else {
        // 0x0016c800
        charge(ctx, 4);
        v0 = 0x830000;
        lw(v0, v0, 25192);  // kHeroExp (gGlobalWork +0x68)
    }
    // 0x0016c848 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0016C860 sub_16C860 [datGetPcPersonaId] -- 172 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_16C860(pc): the persona id (u16 +2) pc fights with: the hero's current stock slot (kHeroPersonaIdx, K_Assert line
// 633 unless < 12), a member's record persona (+0xDC +2).
void sub_16C860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016c860
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);  // (s16)pc
    v0 = 1;
    if (v1 != v0) {  // a party member (pc 1 is the hero)
        // 0x0016c8d4
        charge(ctx, 9);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 14886);  // &records[0].persona.id (pc 0; + 868 pc)
        v0 = addu(v0, v1);
        lhu(v0, v0, 0);
    } else {
        // 0x0016c880
        charge(ctx, 5);
        v0 = 0x830000;
        lh(s0, v0, 27560);  // kHeroPersonaIdx (gGlobalWork +0x9A8)
        v0 = slti(s0, 12);
        if (v0 == 0) {
            // 0x0016c894
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 633;
            jal(ctx, 0x16C8A0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 633): returns
        }
        // 0x0016c8a8
        charge(ctx, 11);
        v0 = sll(s0, 1);
        v0 = addu(v0, s0);
        v0 = sll(v0, 2);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 27566);  // &kHeroPersonaStock[0].id
        v0 = addu(v0, v1);
        lhu(v0, v0, 0);
    }
    // 0x0016c8f8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0016C910 sub_16C910 [datGetHeroPersonaIdx] -- 16 bytes; leaf frame (no stack)
// sub_16C910(): the hero's current persona stock slot (s16 kHeroPersonaIdx 0x836BA8).
void sub_16C910(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0016c910
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x830000;
    lh(v0, v0, 27560);  // kHeroPersonaIdx (gGlobalWork +0x9A8)
}

// 0x0016C920 sub_16C920 [datGetPcCondition] -- 80 bytes; leaf frame (no stack)
// sub_16C920(pc): pc's condition word (u16 record +0x4C; hero gGlobalWork +0x6C): the battle code reads it
// (datCalcDamage, datCalcCheckHit, btlMainInitStateCondition); sub_16D6B0 changes it.
void sub_16C920(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0016c920
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);  // (s16)pc
    v0 = 1;
    if (v1 != v0) {  // a party member (pc 1 is the hero)
        // 0x0016c944
        charge(ctx, 9);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 14740);  // &records[0] +0x4C condition (pc 0; + 868 pc)
        v0 = addu(v0, v1);
        lhu(v0, v0, 0);
    } else {
        // 0x0016c934
        charge(ctx, 4);
        v0 = 0x830000;
        lhu(v0, v0, 25196);  // kHeroCondition (gGlobalWork +0x6C)
    }
    // 0x0016c968 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016C970 sub_16C970 [datGetPcBadStatus] -- 116 bytes; frame 0x10: ra sp+0x0
// sub_16C970(pc): datCalcGetBadStatusNoDown of pc's DatUnit.
void sub_16C970(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016c970
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);  // (s16)pc
    v0 = 1;
    if (v1 != v0) {  // a party member (pc 1 is the hero)
        // 0x0016c9a4
        charge(ctx, 12);
        v1 = addiu(v1, -2);  // 868 * (pc - 2) = (((pc - 2) * 31) * 7) * 4:
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &kPartyRecords (pc 2's record)
        v0 = addu(v0, v1);
        a0 = addiu(v0, 4);  // &record(pc)->unit
        jal(ctx, 0x16C9CCu, gen::fn_datCalcGetBadStatusNoDown_00300530);
    } else {
        // 0x0016c98c
        charge(ctx, 6);
        a0 = 0x830000;
        a0 = addiu(a0, 25124);  // &kHeroUnit (gGlobalWork +0x24): the hero's DatUnit
        jal(ctx, 0x16C994u, gen::fn_datCalcGetBadStatusNoDown_00300530);
    }
    // 0x0016c9d4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0016C9F0 sub_16C9F0 -- 80 bytes; leaf frame (no stack)
// sub_16C9F0(pc): pc's u16 at record +0x4E (hero gGlobalWork +0x6E), the word sub_16D930 sets.
void sub_16C9F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0016c9f0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);  // (s16)pc
    v0 = 1;
    if (v1 != v0) {  // a party member (pc 1 is the hero)
        // 0x0016ca14
        charge(ctx, 9);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 14742);  // &records[0] +0x4E (pc 0; + 868 pc)
        v0 = addu(v0, v1);
        lhu(v0, v0, 0);
    } else {
        // 0x0016ca04
        charge(ctx, 4);
        v0 = 0x830000;
        lhu(v0, v0, 25198);  // the hero's +0x4E word (gGlobalWork +0x6E)
    }
    // 0x0016ca38 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016CA40 sub_16CA40 -- 80 bytes; leaf frame (no stack)
// sub_16CA40(pc): pc's u16 at record +0x50 (hero gGlobalWork +0x70), the word sub_16D980 sets.
void sub_16CA40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0016ca40
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);  // (s16)pc
    v0 = 1;
    if (v1 != v0) {  // a party member (pc 1 is the hero)
        // 0x0016ca64
        charge(ctx, 9);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 14744);  // &records[0] +0x50 (pc 0; + 868 pc)
        v0 = addu(v0, v1);
        lhu(v0, v0, 0);
    } else {
        // 0x0016ca54
        charge(ctx, 4);
        v0 = 0x830000;
        lhu(v0, v0, 25200);  // the hero's +0x50 word (gGlobalWork +0x70)
    }
    // 0x0016ca88 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016CA90 sub_16CA90 -- 232 bytes; frame 0x10: ra sp+0x0
// sub_16CA90(pc): copies pc's +0x50 word into its +0x4E word (sub_16D930(pc, sub_16CA40(pc)), inlined read).
void sub_16CA90(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016ca90
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a3 = dsll32(a0, 16);
    a3 = dsra32(a3, 16);
    v0 = 1;
    if (a3 != v0) {
        // 0x0016cabc
        charge(ctx, 9);
        v0 = sll(a3, 5);
        v1 = subu(v0, a3);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 14742);  // &records[0] +0x4E (pc 0; + 868 pc)
        v0 = addu(v0, v1);
        lhu(v0, v0, 0);
    } else {
        // 0x0016caac
        charge(ctx, 4);
        v0 = 0x830000;
        lhu(v0, v0, 25198);  // the hero's +0x4E word (gGlobalWork +0x6E)
    }
    // 0x0016cae0
    charge(ctx, 4);
    a2 = v0 & 0xFFFF;
    v0 = 1;
    if (a3 != v0) {
        // 0x0016cb00
        charge(ctx, 9);
        v0 = sll(a3, 5);
        v1 = subu(v0, a3);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 14744);  // &records[0] +0x50 (pc 0; + 868 pc)
        v0 = addu(v0, v1);
        lhu(v0, v0, 0);
    } else {
        // 0x0016caf0
        charge(ctx, 4);
        v0 = 0x830000;
        lhu(v0, v0, 25200);  // the hero's +0x50 word (gGlobalWork +0x70)
    }
    // 0x0016cb24
    charge(ctx, 6);
    v1 = v0 & 0xFFFF;
    v0 = dsll32(a1, 16);
    v0 = dsra32(v0, 16);
    v0 = addu(a2, v0);
    if (i64(v0) >= 0) {
        // 0x0016cb48
        charge(ctx, 3);
        at = slt(v1, v0);
        if (at != 0) {
            // 0x0016cb54
            charge(ctx, 1);
            v0 = v1;
        }
    } else {
        // 0x0016cb3c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0016cb58
    charge(ctx, 8);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    jal(ctx, 0x16CB60u, gen::fn_sub_16D930_0016d930);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0016CDF0 sub_16CDF0 [datInitPcUnit] -- 252 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_16CDF0(pc): clears pc's 60-byte DatUnit (memset) and sets unit.id = unit.base_id = pc and the byte at unit +0x10
// = 1.
void sub_16CDF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016cdf0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = dsll32(s1, 16);
    s0 = dsra32(s0, 16);
    v0 = 1;
    if (s0 != v0) {
        // 0x0016ce54
        charge(ctx, 32);
        v1 = addiu(s0, -2);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &kPartyRecords (pc 2's record)
        v0 = addu(v0, v1);
        a0 = addiu(v0, 4);  // &record(pc)->unit
        a1 = 0;
        a2 = 60;
        jal(ctx, 0x16CE84u, gen::fn_memset_00521408);
        v1 = sll(s0, 5);
        a0 = subu(v1, s0);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a1 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 14670);  // &records[0].unit.id (pc 0; + 868 pc)
        v1 = addu(v1, a1);
        sh(s1, v1, 0);
        v1 = 0x830000;
        v1 = addiu(v1, 14672);  // &records[0].unit.base_id (pc 0; + 868 pc)
        v1 = addu(v1, a1);
        sh(s1, v1, 0);
        a0 = 1;
        v1 = 0x830000;
        v1 = addiu(v1, 14684);  // &records[0].unit +0x10 (pc 0; + 868 pc)
        v1 = addu(v1, a1);
        sb(a0, v1, 0);
    } else {
        // 0x0016ce18
        charge(ctx, 15);
        a0 = 0x830000;
        a0 = addiu(a0, 25124);  // &kHeroUnit (gGlobalWork +0x24): the hero's DatUnit
        a1 = 0;
        a2 = 60;
        jal(ctx, 0x16CE28u, gen::fn_memset_00521408);
        v1 = 0x830000;
        sh(s1, v1, 25126);  // kHeroUnit.id
        v1 = 0x830000;
        sh(s1, v1, 25128);  // kHeroUnit.base_id
        a0 = 1;
        v1 = 0x830000;
        sb(a0, v1, 25140);  // kHeroUnit +0x10
    }
    // 0x0016ced4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0016CEF0 sub_16CEF0 [datSetHeroLevel] -- 80 bytes; frame 0x10: ra sp+0x0
// sub_16CEF0(pc, level): unit.level (u8 +6) of the hero; any other pc only reaches K_Assert line 770 (member levels
// come from their personas).
void sub_16CEF0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016cef0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = 1;
    if (a0 != v1) {
        // 0x0016cf1c
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 770;
        jal(ctx, 0x16CF28u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 770): returns
    } else {
        // 0x0016cf0c
        charge(ctx, 4);
        v1 = 0x830000;
        sb(a1, v1, 25130);  // kHeroUnit.level
    }
    // 0x0016cf30 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0016CF40 sub_16CF40 [datSetPcHp] -- 80 bytes; leaf frame (no stack)
// sub_16CF40(pc, value): unit.hp (u16 +8) of pc's DatUnit = value.
void sub_16CF40(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016cf40
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = 1;
    if (a0 != v1) {
        // 0x0016cf64
        charge(ctx, 9);
        v1 = sll(a0, 5);
        a0 = subu(v1, a0);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 14676);  // &records[0].unit.hp (pc 0; + 868 pc)
        v1 = addu(v1, a0);
        sh(a1, v1, 0);
    } else {
        // 0x0016cf54
        charge(ctx, 4);
        v1 = 0x830000;
        sh(a1, v1, 25132);  // kHeroUnit.hp
    }
    // 0x0016cf88 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016CF90 sub_16CF90 [datSetPcSp] -- 80 bytes; leaf frame (no stack)
// sub_16CF90(pc, value): unit.sp (u16 +0xA) of pc's DatUnit = value.
void sub_16CF90(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016cf90
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = 1;
    if (a0 != v1) {
        // 0x0016cfb4
        charge(ctx, 9);
        v1 = sll(a0, 5);
        a0 = subu(v1, a0);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 14678);  // &records[0].unit.sp (pc 0; + 868 pc)
        v1 = addu(v1, a0);
        sh(a1, v1, 0);
    } else {
        // 0x0016cfa4
        charge(ctx, 4);
        v1 = 0x830000;
        sh(a1, v1, 25134);  // kHeroUnit.sp
    }
    // 0x0016cfd8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016D230 sub_16D230 [datSetHeroExp] -- 80 bytes; frame 0x10: ra sp+0x0
// sub_16D230(pc, value): the hero's s32 experience (gGlobalWork +0x68) = value; any other pc only reaches K_Assert line
// 858.
void sub_16D230(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016d230
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = 1;
    if (a0 != v1) {
        // 0x0016d25c
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 858;
        jal(ctx, 0x16D268u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 858): returns
    } else {
        // 0x0016d24c
        charge(ctx, 4);
        v1 = 0x830000;
        sw(a1, v1, 25192);  // kHeroExp (gGlobalWork +0x68)
    }
    // 0x0016d270 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0016D280 sub_16D280 [datGetLevelForExp] -- 104 bytes; leaf frame (no stack)
// sub_16D280(exp): the level an experience total reaches on the hero's exp table 0x5DC050 (s32[99], ascending): the
// count of leading entries <= exp, 99 at most.
void sub_16D280(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0016d280
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0;
    a2 = 0;
    a1 = 0x5E0000;
    a1 = addiu(a1, -16304);  // &kHeroExpTable (s32[99])
    for (;;) {  // a2 = i (u8), v0 = the count of entries <= exp
        // 0x0016d2cc
        charge(ctx, 4);
        v1 = a2 & 0xFF;
        v1 = slti(v1, 99);
        if (v1 == 0) {
            // 0x0016d2dc: every entry passed
            charge(ctx, 1);
            v0 = 99;
            break;
        }
        backedge(ctx);
        // 0x0016d298
        charge(ctx, 7);
        v1 = a2 & 0xFF;
        v1 = sll(v1, 2);
        v1 = addu(a1, v1);
        lw(v1, v1, 0);  // kHeroExpTable[i]
        at = slt(a0, v1);
        if (at != 0) {
            // 0x0016d2b4: exp < kHeroExpTable[i]: v0 is the level
            charge(ctx, 2);
            break;
        }
        // 0x0016d2bc
        charge(ctx, 4);
        v0 = addiu(v0, 1);
        v0 = v0 & 0xFF;
        v1 = addiu(a2, 1);
        a2 = v1 & 0xFF;
    }
    // 0x0016d2e0 (the shared epilogue)
    charge(ctx, 2);
}

// 0x0016D560 sub_16D560 [datAddHeroExp] -- 328 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_16D560(pc, exp): adds exp to the hero (gGlobalWork +0x68; any other pc only reaches K_Assert line 901) and
// returns whether the level the new total reaches (the 0x5DC050 scan) differs from the unit's level (datCalcGetLevel).
// For another pc the compare uses the level register left over from the caller ($s1), as the original.
void sub_16D560(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016d560
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = dsll32(a0, 16);
    s0 = dsra32(s0, 16);
    v0 = 1;
    if (s0 != v0) {
        // 0x0016d608
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 901;
        jal(ctx, 0x16D614u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 901): returns
    } else {
        // 0x0016d584
        charge(ctx, 11);
        v0 = 0x830000;
        lw(v0, v0, 25192);  // kHeroExp (gGlobalWork +0x68)
        a0 = addu(v0, a1);
        v0 = 0x830000;
        sw(a0, v0, 25192);  // kHeroExp (gGlobalWork +0x68)
        a1 = 0;
        a2 = 0;
        v1 = 0x5E0000;
        v1 = addiu(v1, -16304);  // &kHeroExpTable (s32[99])
        // the level the new total reaches: sub_16D280 inlined (a2 = i, a1 = the count of table entries <= exp)
        for (;;) {
            // 0x0016d5e8
            charge(ctx, 4);
            v0 = a2 & 0xFF;
            v0 = slti(v0, 99);
            if (v0 == 0) {
                // 0x0016d5f8: every entry passed: 99
                charge(ctx, 1);
                v0 = 99;
                break;
            }
            backedge(ctx);
            // 0x0016d5b0
            charge(ctx, 7);
            v0 = a2 & 0xFF;
            v0 = sll(v0, 2);
            v0 = addu(v1, v0);
            lw(v0, v0, 0);  // kHeroExpTable[i]
            at = slt(a0, v0);
            if (at != 0) {
                // 0x0016d5cc: exp < kHeroExpTable[i]: the count so far
                charge(ctx, 3);
                v0 = a1 & 0xFF;
                break;
            }
            // 0x0016d5d8
            charge(ctx, 4);
            v0 = addiu(a1, 1);
            a1 = v0 & 0xFF;
            v0 = addiu(a2, 1);
            a2 = v0 & 0xFF;
        }
        // 0x0016d5fc: s1 = the new level
        charge(ctx, 3);
        s1 = v0 & 0xFF;
    }
    // 0x0016d61c
    charge(ctx, 3);
    v0 = 1;
    if (s0 != v0) {
        // 0x0016d640
        charge(ctx, 12);
        v1 = addiu(s0, -2);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &kPartyRecords (pc 2's record)
        v0 = addu(v0, v1);
        a0 = addiu(v0, 4);  // &record(pc)->unit
        jal(ctx, 0x16D668u, gen::fn_datCalcGetLevel_002ffcc0);
    } else {
        // 0x0016d628
        charge(ctx, 6);
        a0 = 0x830000;
        a0 = addiu(a0, 25124);  // &kHeroUnit (gGlobalWork +0x24): the hero's DatUnit
        jal(ctx, 0x16D630u, gen::fn_datCalcGetLevel_002ffcc0);
    }
    // 0x0016d670
    charge(ctx, 4);
    v1 = v0 & 0xFF;
    v0 = s1 & 0xFF;
    if (v0 == v1) {
        // 0x0016d68c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0016d680
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0016d690 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0016D6B0 sub_16D6B0 [datSetPcCondition] -- 500 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_16D6B0(pc, condition): sets pc's condition word (+0x4C). When it changes, counter pc + 15 (sub_16F3E0) is set for
// the new condition (5: 60, 3: 50, 2: 1 and counter pc + 25 = 0, 0: 0); leaving condition 3 copies the +0x50 word into
// +0x4E (sub_16D930).
void sub_16D6B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016d6b0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = dsll32(s4, 16);
    s2 = dsra32(s2, 16);
    v1 = 1;
    if (s2 != v1) {
        // 0x0016d6fc
        charge(ctx, 9);
        v1 = sll(s2, 5);
        a0 = subu(v1, s2);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 14740);  // &records[0] +0x4C condition (pc 0; + 868 pc)
        v1 = addu(v1, a0);
        lhu(v1, v1, 0);
    } else {
        // 0x0016d6ec
        charge(ctx, 4);
        v1 = 0x830000;
        lhu(v1, v1, 25196);  // kHeroCondition (gGlobalWork +0x6C)
    }
    // 0x0016d720
    charge(ctx, 4);
    s1 = v1 & 0xFFFF;
    s0 = s3 & 0xFFFF;
    if (s1 != s0) {
        // 0x0016d730
        charge(ctx, 3);
        v1 = 5;
        if (s0 == v1) {
            // 0x0016d7c4
            charge(ctx, 4);
            a0 = addiu(s2, 15);
            a1 = 60;
            jal(ctx, 0x16D7CCu, gen::fn_sub_16F3E0_0016f3e0);
        } else {
            // 0x0016d73c
            charge(ctx, 3);
            v1 = 3;
            if (s0 == v1) {
                // 0x0016d7ac
                charge(ctx, 6);
                a0 = addiu(s2, 15);
                a1 = 50;
                jal(ctx, 0x16D7B4u, gen::fn_sub_16F3E0_0016f3e0);
            } else {
                // 0x0016d748
                charge(ctx, 3);
                v1 = 2;
                if (s0 == v1) {
                    // 0x0016d77c
                    charge(ctx, 12);
                    s5 = dsll32(s4, 16);
                    s5 = dsra32(s5, 16);
                    a0 = addiu(s5, 15);
                    a1 = 1;
                    jal(ctx, 0x16D78Cu, gen::fn_sub_16F3E0_0016f3e0);
                    a0 = addiu(s5, 25);
                    a1 = 0;
                    jal(ctx, 0x16D79Cu, gen::fn_sub_16F3E0_0016f3e0);
                } else {
                    // 0x0016d754
                    charge(ctx, 2);
                    if (s0 == 0) {
                        // 0x0016d764
                        charge(ctx, 6);
                        a0 = addiu(s2, 15);
                        a1 = 0;
                        jal(ctx, 0x16D76Cu, gen::fn_sub_16F3E0_0016f3e0);
                    } else {
                        // 0x0016d75c
                        charge(ctx, 2);
                    }
                }
            }
        }
    }
    // 0x0016d7d4
    charge(ctx, 3);
    v1 = 3;
    if (s1 == v1) {
        // 0x0016d7e0
        charge(ctx, 2);
        if (s0 != v1) {
            // 0x0016d7e8
            charge(ctx, 3);
            v0 = 1;
            if (s2 != v0) {
                // 0x0016d804
                charge(ctx, 9);
                v0 = sll(s2, 5);
                v1 = subu(v0, s2);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 14744);  // &records[0] +0x50 (pc 0; + 868 pc)
                v0 = addu(v0, v1);
                lhu(v0, v0, 0);
            } else {
                // 0x0016d7f4
                charge(ctx, 4);
                v0 = 0x830000;
                lhu(v0, v0, 25200);  // the hero's +0x50 word (gGlobalWork +0x70)
            }
            // 0x0016d828
            charge(ctx, 5);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = s4;
            jal(ctx, 0x16D834u, gen::fn_sub_16D930_0016d930);
        }
    }
    // 0x0016d83c
    charge(ctx, 3);
    v1 = 1;
    if (s2 != v1) {
        // 0x0016d858
        charge(ctx, 9);
        v1 = sll(s2, 5);
        a0 = subu(v1, s2);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 14740);  // &records[0] +0x4C condition (pc 0; + 868 pc)
        v1 = addu(v1, a0);
        sh(s3, v1, 0);
    } else {
        // 0x0016d848
        charge(ctx, 4);
        v1 = 0x830000;
        sh(s3, v1, 25196);  // kHeroCondition (gGlobalWork +0x6C)
    }
    // 0x0016d87c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0016D8B0 sub_16D8B0 [datSetPcBadStatus] -- 116 bytes; frame 0x10: ra sp+0x0
// sub_16D8B0(pc): datCalcSetBadStatus on pc's DatUnit.
void sub_16D8B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016d8b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);  // (s16)pc
    v0 = 1;
    if (v1 != v0) {  // a party member (pc 1 is the hero)
        // 0x0016d8e4
        charge(ctx, 12);
        v1 = addiu(v1, -2);  // 868 * (pc - 2) = (((pc - 2) * 31) * 7) * 4:
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &kPartyRecords (pc 2's record)
        v0 = addu(v0, v1);
        a0 = addiu(v0, 4);  // &record(pc)->unit
        jal(ctx, 0x16D90Cu, gen::fn_datCalcSetBadStatus_003004f0);
    } else {
        // 0x0016d8cc
        charge(ctx, 6);
        a0 = 0x830000;
        a0 = addiu(a0, 25124);  // &kHeroUnit (gGlobalWork +0x24): the hero's DatUnit
        jal(ctx, 0x16D8D4u, gen::fn_datCalcSetBadStatus_003004f0);
    }
    // 0x0016d914 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0016D930 sub_16D930 -- 80 bytes; leaf frame (no stack)
// sub_16D930(pc, value): pc's u16 at record +0x4E (hero gGlobalWork +0x6E) = value.
void sub_16D930(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016d930
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = 1;
    if (a0 != v1) {
        // 0x0016d954
        charge(ctx, 9);
        v1 = sll(a0, 5);
        a0 = subu(v1, a0);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 14742);  // &records[0] +0x4E (pc 0; + 868 pc)
        v1 = addu(v1, a0);
        sh(a1, v1, 0);
    } else {
        // 0x0016d944
        charge(ctx, 4);
        v1 = 0x830000;
        sh(a1, v1, 25198);  // the hero's +0x4E word (gGlobalWork +0x6E)
    }
    // 0x0016d978 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016D980 sub_16D980 -- 80 bytes; leaf frame (no stack)
// sub_16D980(pc, value): pc's u16 at record +0x50 (hero gGlobalWork +0x70) = value.
void sub_16D980(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016d980
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = 1;
    if (a0 != v1) {
        // 0x0016d9a4
        charge(ctx, 9);
        v1 = sll(a0, 5);
        a0 = subu(v1, a0);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 14744);  // &records[0] +0x50 (pc 0; + 868 pc)
        v1 = addu(v1, a0);
        sh(a1, v1, 0);
    } else {
        // 0x0016d994
        charge(ctx, 4);
        v1 = 0x830000;
        sh(a1, v1, 25200);  // the hero's +0x50 word (gGlobalWork +0x70)
    }
    // 0x0016d9c8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016D9D0 sub_16D9D0 [datClearPcBadStatus] -- 116 bytes; frame 0x10: ra sp+0x0
// sub_16D9D0(pc): datCalcClearBadStatus on pc's DatUnit.
void sub_16D9D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016d9d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);  // (s16)pc
    v0 = 1;
    if (v1 != v0) {  // a party member (pc 1 is the hero)
        // 0x0016da04
        charge(ctx, 12);
        v1 = addiu(v1, -2);  // 868 * (pc - 2) = (((pc - 2) * 31) * 7) * 4:
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &kPartyRecords (pc 2's record)
        v0 = addu(v0, v1);
        a0 = addiu(v0, 4);  // &record(pc)->unit
        jal(ctx, 0x16DA2Cu, gen::fn_datCalcClearBadStatus_00300560);
    } else {
        // 0x0016d9ec
        charge(ctx, 6);
        a0 = 0x830000;
        a0 = addiu(a0, 25124);  // &kHeroUnit (gGlobalWork +0x24): the hero's DatUnit
        jal(ctx, 0x16D9F4u, gen::fn_datCalcClearBadStatus_00300560);
    }
    // 0x0016da34 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0016DA50 sub_16DA50 [datSetEquipmentIdx] -- 116 bytes; leaf frame (no stack)
// sub_16DA50(pc, slot, value): pc's s16 equipment index of `slot` = value (hero kHeroEquipment[slot], member record
// +0x54 [slot]); the setter of datGetEquipmentIdx.
void sub_16DA50(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0016da50
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = 1;
    if (a0 != v1) {
        // 0x0016da88
        charge(ctx, 13);
        v1 = sll(a0, 5);
        a0 = subu(v1, a0);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 14748);  // &records[0].equipment_idx (pc 0; + 868 pc)
        a0 = addu(v1, a0);
        v1 = dsll32(a1, 16);
        v1 = dsra32(v1, 16);
        v1 = sll(v1, 1);
        v1 = addu(v1, a0);
        sh(a2, v1, 0);
    } else {
        // 0x0016da64
        charge(ctx, 9);
        v1 = dsll32(a1, 16);
        v1 = dsra32(v1, 16);
        a0 = sll(v1, 1);
        v1 = 0x830000;
        v1 = addiu(v1, 26508);  // &kHeroEquipment (gGlobalWork +0x58C)
        v1 = addu(v1, a0);
        sh(a2, v1, 0);
    }
    // 0x0016dabc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016DAD0 sub_16DAD0 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_16DAD0(pc, value): the byte at DatUnit +0x10 of pc = value; K_Assert line 999 unless value < 11 (sub_16CDF0
// initialises it to 1).
void sub_16DAD0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016dad0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    v1 = dsll32(s0, 16);
    v1 = dsra32(v1, 16);
    v1 = slti(v1, 11);
    if (v1 == 0) {
        // 0x0016dafc
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 999;
        jal(ctx, 0x16DB08u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 999): returns
    }
    // 0x0016db10
    charge(ctx, 5);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    v1 = 1;
    if (a0 != v1) {
        // 0x0016db34
        charge(ctx, 9);
        v1 = sll(a0, 5);
        a0 = subu(v1, a0);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 14684);  // &records[0].unit +0x10 (pc 0; + 868 pc)
        v1 = addu(v1, a0);
        sb(s0, v1, 0);
    } else {
        // 0x0016db24
        charge(ctx, 4);
        v1 = 0x830000;
        sb(s0, v1, 25140);  // kHeroUnit +0x10
    }
    // 0x0016db58 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0016DD80 sub_16DD80 -- 80 bytes; leaf frame (no stack)
// sub_16DD80(pc): the signed byte at DatUnit +0x10 of pc (the getter of sub_16DAD0).
void sub_16DD80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0016dd80
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);  // (s16)pc
    v0 = 1;
    if (v1 != v0) {  // a party member (pc 1 is the hero)
        // 0x0016dda4
        charge(ctx, 9);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 14684);  // &records[0].unit +0x10 (pc 0; + 868 pc)
        v0 = addu(v0, v1);
        lb(v0, v0, 0);
    } else {
        // 0x0016dd94
        charge(ctx, 4);
        v0 = 0x830000;
        lb(v0, v0, 25140);  // kHeroUnit +0x10
    }
    // 0x0016ddc8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016DB70 sub_16DB70 [datComuClearAll] -- 48 bytes; frame 0x10: ra sp+0x0
// sub_16DB70(): clears the 1,288 bytes at gGlobalWork +0x74..+0x57B (memset): the social links, the day-event records
// and the comu dates / counters behind them.
void sub_16DB70(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016db70
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x830000;
    a0 = addiu(a0, 25204);  // &kComuBlock (gGlobalWork +0x74)
    a1 = 0;
    a2 = 1288;
    jal(ctx, 0x16DB88u, gen::fn_memset_00521408);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0016DBA0 sub_16DBA0 [datComuGetRank] -- 32 bytes; leaf frame (no stack)
// sub_16DBA0(comu): the s8 rank of social link `comu` (kComuRank[comu], gGlobalWork +0x76; no range check).
void sub_16DBA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0016dba0
    enter(ctx, 8);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = 0x830000;
    v0 = addiu(v0, 25206);  // &kComuRank
    v0 = addu(v0, v1);
    lb(v0, v0, 0);
}

// 0x0016DCE0 sub_16DCE0 [datComuIsValidId] -- 52 bytes; leaf frame (no stack)
// sub_16DCE0(comu): 0 <= comu < 30 (the social-link id check the band's callers make before every array access).
void sub_16DCE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0016dce0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    bool in_range = false;
    if (i64(v0) >= 0) {
        // 0x0016dcf0
        charge(ctx, 3);
        v0 = slti(v0, 30);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x0016dd08
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x0016dcfc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0016dd0c (the shared epilogue)
    charge(ctx, 2);
}

// 0x0016DD20 sub_16DD20 -- 32 bytes; leaf frame (no stack)
// sub_16DD20(comu): the s8 kComuB[comu] (gGlobalWork +0x10C; sub_16E5F0 / sub_16E670 keep it in 0..9; no range check).
void sub_16DD20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0016dd20
    enter(ctx, 8);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = 0x830000;
    v0 = addiu(v0, 25356);  // &kComuB (gGlobalWork +0x10C)
    v0 = addu(v0, v1);
    lb(v0, v0, 0);
}

// 0x0016DD40 sub_16DD40 -- 16 bytes; leaf frame (no stack)
// sub_16DD40(): the s16 at gGlobalWork +0x74, the first word of the social-link block (set by sub_16E920).
void sub_16DD40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0016dd40
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x830000;
    lh(v0, v0, 25204);  // the social-link block's first s16 (gGlobalWork +0x74)
}

// 0x0016DEB0 sub_16DEB0 [datComuFindByArcana] -- 116 bytes; leaf frame (no stack)
// sub_16DEB0(arcana): the social link of `arcana` with the highest rank: scans the 30 comu ids whose arcana byte
// (0x5E3220) equals arcana, keeps the first with the strictly highest rank; -1 when none.
void sub_16DEB0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x0016deb0
    enter(ctx, 11);  // entry check point + this block's cycles
    a3 = si(-1);
    v0 = a3;
    t0 = 0;
    a2 = dsll32(a0, 16);
    a2 = dsra32(a2, 16);
    a0 = 0x830000;
    a0 = addiu(a0, 25088);  // &gGlobalWork
    a1 = 0x5E0000;
    a1 = addiu(a1, 12832);  // &kComuArcana (s8[30])
    for (;;) {
        // 0x0016df10
        charge(ctx, 3);
        v1 = slti(t0, 30);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0016dedc
        charge(ctx, 4);
        v1 = addu(a1, t0);
        lb(v1, v1, 0);
        if (v1 == a2) {
            // 0x0016deec
            charge(ctx, 5);
            v1 = addu(a0, t0);
            lb(v1, v1, 118);
            at = slt(a3, v1);
            if (at != 0) {
                // 0x0016df00
                charge(ctx, 3);
                v0 = dsll32(t0, 16);
                v0 = dsra32(v0, 16);
                a3 = v1;
            }
        }
        // 0x0016df0c
        charge(ctx, 1);
        t0 = addiu(t0, 1);
    }
    // 0x0016df1c
    charge(ctx, 2);
}

// 0x0016DF30 sub_16DF30 [datComuGetArcana] -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_16DF30(comu): the arcana byte of social link comu (s8 table 0x5E3220 [comu]); K_Assert line 1355 unless 0 <= comu
// < 30.
void sub_16DF30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016df30
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = dsll32(a0, 16);
    s0 = dsra32(s0, 16);
    // v0 = (0 <= s0 < 30): the inlined id check
    bool in_range = false;
    if (i64(s0) >= 0) {
        // 0x0016df4c
        charge(ctx, 3);
        v0 = slti(s0, 30);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x0016df64
        charge(ctx, 1);
        v0 = 1;
    } else {
        charge(ctx, 3);
        v0 = 0;
    }
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x0016df70
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 1355;
        jal(ctx, 0x16DF7Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1355): returns
    }
    // 0x0016df84 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = 0x5E0000;
    v0 = addiu(v0, 12832);  // &kComuArcana (s8[30])
    v0 = addu(v0, s0);
    lb(v0, v0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0016DFB0 sub_16DFB0 [datComuStart] -- 332 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_16DFB0(comu): starts social link comu unless it already has a rank: rank = 0 (sub_16E410), the 0x900/0x920/0x940
// bits and counters reset (sub_171C40 / sub_172200 / sub_171E90), the per-rank bits of ranks 2..10 cleared and rank 1's
// set (sub_1723A0 / sub_1724A0). K_Assert line 1370 unless 0 <= comu < 30.
void sub_16DFB0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016dfb0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    v0 = dsll32(s2, 16);
    v0 = dsra32(v0, 16);
    // v0 = (0 <= v0 < 30): the inlined id check
    bool in_range = false;
    if (i64(v0) >= 0) {
        // 0x0016dfd8
        charge(ctx, 3);
        v0 = slti(v0, 30);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x0016dff0
        charge(ctx, 1);
        v0 = 1;
    } else {
        charge(ctx, 3);
        v0 = 0;
    }
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x0016dffc
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 1370;
        jal(ctx, 0x16E008u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1370): returns
    }
    // 0x0016e010
    charge(ctx, 6);
    a0 = s2;
    jal(ctx, 0x16E014u, gen::fn_sub_16E100_0016e100);
    a1 = 1;
    if (v0 != a1) {
        // 0x0016e028
        charge(ctx, 20);
        a0 = s2;
        jal(ctx, 0x16E02Cu, gen::fn_sub_16E410_0016e410);
        s0 = dsll32(s2, 16);
        s0 = dsra32(s0, 16);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x16E044u, gen::fn_sub_171C40_00171c40);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x16E054u, gen::fn_sub_172200_00172200);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x16E064u, gen::fn_sub_171E90_00171e90);
        s1 = 1;
        for (;;) {
            // 0x0016e0a4
            charge(ctx, 3);
            at = slti(s1, 11);
            if (at == 0) {
                break;
            }
            backedge(ctx);
            // 0x0016e078
            charge(ctx, 11);
            a0 = s0;
            a1 = s1;
            a2 = 0;
            jal(ctx, 0x16E084u, gen::fn_sub_1723A0_001723a0);
            a0 = s0;
            a1 = s1;
            a2 = 0;
            jal(ctx, 0x16E098u, gen::fn_sub_1724A0_001724a0);
            s1 = addiu(s1, 1);
        }
        // 0x0016e0b0
        charge(ctx, 12);
        s0 = dsll32(s2, 16);
        s0 = dsra32(s0, 16);
        a0 = s0;
        a1 = 1;
        a2 = a1;
        jal(ctx, 0x16E0C4u, gen::fn_sub_1723A0_001723a0);
        a0 = s0;
        a1 = 1;
        a2 = a1;
        jal(ctx, 0x16E0D8u, gen::fn_sub_1724A0_001724a0);
    }
    // 0x0016e0e0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0016E100 sub_16E100 [datComuIsActive] -- 144 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_16E100(comu): kComuRank[comu] > 0; K_Assert line 1429 unless 0 <= comu < 30.
void sub_16E100(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016e100
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = dsll32(a0, 16);
    s0 = dsra32(s0, 16);
    // v0 = (0 <= s0 < 30): the inlined id check
    bool in_range = false;
    if (i64(s0) >= 0) {
        // 0x0016e11c
        charge(ctx, 3);
        v0 = slti(s0, 30);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x0016e134
        charge(ctx, 1);
        v0 = 1;
    } else {
        charge(ctx, 3);
        v0 = 0;
    }
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x0016e140
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 1429;
        jal(ctx, 0x16E14Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1429): returns
    }
    // 0x0016e154
    charge(ctx, 6);
    v0 = 0x830000;
    v0 = addiu(v0, 25206);  // &kComuRank
    v0 = addu(v0, s0);
    lb(v0, v0, 0);
    if (i64(v0) > 0) {
        // 0x0016e178
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x0016e16c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0016e17c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0016E2B0 sub_16E2B0 [datComuAddPoints] -- 352 bytes; frame 0x70: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_16E2B0(comu, points): adds points to social link comu when 0 <= comu < 30 and 0 < rank < 10: scaled by
// sub_3BDB80()'s float when a persona of the link's arcana is held (sub_16DBC0), then clamped to the rank's threshold
// (the s32 table sub_3BDD90(comu) [rank - 1], K_Assert line 1495 on a null table), which also sets the next rank's
// 'ready' bit (sub_1723A0(comu, rank + 1, 1)).
void sub_16E2B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f20{ctx, 20};
    // 0x0016e2b0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s3 = a0;
    s2 = a1;
    a0 = dsll32(s3, 16);
    a0 = dsra32(a0, 16);
    v1 = 0x830000;
    v1 = addiu(v1, 25206);  // &kComuRank
    v1 = addu(v1, a0);
    lb(s1, v1, 0);
    // v1 = (0 <= a0 < 30): the inlined id check
    bool in_range = false;
    if (i64(a0) >= 0) {
        // 0x0016e2f4
        charge(ctx, 3);
        v1 = slti(a0, 30);
        in_range = v1 != 0;
    }
    if (in_range) {
        // 0x0016e30c
        charge(ctx, 1);
        v1 = 1;
    } else {
        charge(ctx, 3);
        v1 = 0;
    }
    charge(ctx, 2);
    if (v1 != 0) {
        // 0x0016e318
        charge(ctx, 3);
        at = slti(s1, 10);
        if (at != 0) {
            // 0x0016e324
            charge(ctx, 2);
            if (i64(s1) > 0) {
                // 0x0016e32c
                charge(ctx, 7);
                a0 = s3;
                a1 = addiu(sp, 0x6C);
                jal(ctx, 0x16E334u, gen::fn_sub_16DBC0_0016dbc0);
                v1 = 1;
                if (v0 == v1) {
                    // 0x0016e348
                    charge(ctx, 8);
                    mtc1(s2, f0);
                    cvt_s_w(f20, f0);
                    jal(ctx, 0x16E354u, gen::fn_sub_3BDB80_003bdb80);
                    mul_s(f0, f20, f0);
                    cvt_w_s(f0, f0);
                    mfc1(s2, f0);
                }
                // 0x0016e368
                charge(ctx, 14);
                a0 = dsll32(s3, 16);
                a0 = dsra32(a0, 16);
                v1 = sll(a0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 25236);  // &kComuPoints (gGlobalWork +0x94)
                s0 = addu(v0, v1);
                lw(v0, s0, 0);
                v0 = addu(v0, s2);
                sw(v0, s0, 0);
                jal(ctx, 0x16E38Cu, gen::fn_sub_3BDD90_003bdd90);
                s2 = v0;
                if (s2 == 0) {
                    // 0x0016e3a0
                    charge(ctx, 5);
                    a0 = 0x5E0000;
                    a0 = addiu(a0, 12440);  // "g_data.c"
                    a1 = 1495;
                    jal(ctx, 0x16E3ACu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1495): returns
                }
                // 0x0016e3b4
                charge(ctx, 7);
                v1 = sll(s1, 2);
                v1 = addu(v1, s2);
                lw(a1, v1, -4);
                lw(v1, s0, 0);
                at = sltu(v1, a1);
                if (at == 0) {
                    // 0x0016e3d0
                    charge(ctx, 7);
                    a0 = dsll32(s3, 16);
                    a0 = dsra32(a0, 16);
                    sw(a1, s0, 0);
                    a1 = addiu(s1, 1);
                    a2 = 1;
                    jal(ctx, 0x16E3E4u, gen::fn_sub_1723A0_001723a0);
                }
            }
        }
    }
    // 0x0016e3ec (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0016E410 sub_16E410 [datComuSetRank] -- 472 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_16E410(comu, rank): sets social link comu's rank (K_Assert line 1516 unless rank < 11): refreshes its +0x166
// counter (sub_171B50); points = 0 below rank 2, else the table sub_3BDD90(comu) [rank - 2] (K_Assert line 1528 on a
// null table); the per-rank bits 1..10 set up to the rank (sub_1723A0 / sub_1724A0); kComuB[comu] = 0 (sub_16E5F0).
void sub_16E410(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016e410
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s3 = a1;
    s0 = dsll32(s3, 24);
    s0 = dsra32(s0, 24);
    at = slti(s0, 11);
    if (at == 0) {
        // 0x0016e448
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 1516;
        jal(ctx, 0x16E454u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1516): returns
    }
    // 0x0016e45c
    charge(ctx, 12);
    s1 = dsll32(s2, 16);
    s1 = dsra32(s1, 16);
    v0 = 0x830000;
    v0 = addiu(v0, 25206);  // &kComuRank
    v0 = addu(v0, s1);
    sb(s3, v0, 0);
    a0 = s1;
    jal(ctx, 0x16E478u, gen::fn_sub_171B50_00171b50);
    at = slti(s0, 2);
    if (at != 0) {
        // 0x0016e48c
        charge(ctx, 2);
        // v0 = (0 <= s1 < 30): the inlined id check
        bool in_range = false;
        if (i64(s1) >= 0) {
            // 0x0016e494
            charge(ctx, 3);
            v0 = slti(s1, 30);
            in_range = v0 != 0;
        }
        if (in_range) {
            // 0x0016e4ac
            charge(ctx, 1);
            v0 = 1;
        } else {
            charge(ctx, 3);
            v0 = 0;
        }
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x0016e4b8
            charge(ctx, 5);
            v1 = sll(s1, 2);
            v0 = 0x830000;
            v0 = addiu(v0, 25236);  // &kComuPoints (gGlobalWork +0x94)
            v0 = addu(v0, v1);
            sw(zero, v0, 0);
        }
    }
    // 0x0016e4cc
    charge(ctx, 3);
    at = slti(s0, 2);
    if (at == 0) {
        // 0x0016e4d8
        charge(ctx, 3);
        at = slti(s0, 11);
        if (at != 0) {
            // 0x0016e4e4
            charge(ctx, 6);
            a0 = s1;
            jal(ctx, 0x16E4E8u, gen::fn_sub_3BDD90_003bdd90);
            s3 = v0;
            if (s3 == 0) {
                // 0x0016e4fc
                charge(ctx, 5);
                a0 = 0x5E0000;
                a0 = addiu(a0, 12440);  // "g_data.c"
                a1 = 1528;
                jal(ctx, 0x16E508u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1528): returns
            }
            // 0x0016e510
            charge(ctx, 5);
            v0 = sll(s0, 2);
            v0 = addu(v0, s3);
            lw(a0, v0, -8);
            // v0 = (0 <= s1 < 30): the inlined id check
            bool in_range2 = false;
            if (i64(s1) >= 0) {
                // 0x0016e524
                charge(ctx, 3);
                v0 = slti(s1, 30);
                in_range2 = v0 != 0;
            }
            if (in_range2) {
                // 0x0016e53c
                charge(ctx, 1);
                v0 = 1;
            } else {
                charge(ctx, 3);
                v0 = 0;
            }
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x0016e548
                charge(ctx, 5);
                v1 = sll(s1, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 25236);  // &kComuPoints (gGlobalWork +0x94)
                v0 = addu(v0, v1);
                sw(a0, v0, 0);
            }
        }
    }
    // 0x0016e55c
    charge(ctx, 3);
    s4 = 1;
    for (;;) {
        // 0x0016e5a8
        charge(ctx, 3);
        at = slti(s4, 11);
        if (at == 0) {
            break;
        }
        backedge(ctx);
        // 0x0016e568
        charge(ctx, 4);
        s3 = 0;
        at = slt(s0, s4);
        if (at == 0) {
            // 0x0016e578
            charge(ctx, 1);
            s3 = 1;
        }
        // 0x0016e57c
        charge(ctx, 11);
        a0 = s1;
        a1 = s4;
        a2 = s3;
        jal(ctx, 0x16E588u, gen::fn_sub_1723A0_001723a0);
        a0 = s1;
        a1 = s4;
        a2 = s3;
        jal(ctx, 0x16E59Cu, gen::fn_sub_1724A0_001724a0);
        s4 = addiu(s4, 1);
    }
    // 0x0016e5b4
    charge(ctx, 13);
    a0 = s2;
    a1 = 0;
    jal(ctx, 0x16E5BCu, gen::fn_sub_16E5F0_0016e5f0);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0016E5F0 sub_16E5F0 -- 128 bytes; leaf frame (no stack)
// sub_16E5F0(comu, value): kComuB[comu] = value clamped to 0..9 when 0 <= comu < 30.
void sub_16E5F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016e5f0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    // v1 = (0 <= v1 < 30): the inlined id check
    bool in_range = false;
    if (i64(v1) >= 0) {
        // 0x0016e600
        charge(ctx, 3);
        v1 = slti(v1, 30);
        in_range = v1 != 0;
    }
    if (in_range) {
        // 0x0016e618
        charge(ctx, 1);
        v1 = 1;
    } else {
        charge(ctx, 3);
        v1 = 0;
    }
    charge(ctx, 2);
    if (v1 != 0) {
        // 0x0016e624
        charge(ctx, 10);
        a0 = dsll32(a0, 16);
        a0 = dsra32(a0, 16);
        v1 = 0x830000;
        v1 = addiu(v1, 25356);  // &kComuB (gGlobalWork +0x10C)
        a0 = addu(v1, a0);
        sb(a1, a0, 0);
        v1 = dsll32(a1, 24);
        v1 = dsra32(v1, 24);
        if (i64(v1) < 0) {
            // 0x0016e64c
            charge(ctx, 1);
            sb(zero, a0, 0);
        }
        // 0x0016e650
        charge(ctx, 4);
        lb(v1, a0, 0);
        v1 = slti(v1, 10);
        if (v1 == 0) {
            // 0x0016e660
            charge(ctx, 2);
            v1 = 9;
            sb(v1, a0, 0);
        }
    }
    // 0x0016e668 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016E670 sub_16E670 -- 296 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_16E670(comu): kComuB[comu] += 1, clamped to 0..9, when 0 <= comu < 30 and the link has a rank; else printf("no
// exist comu %s %d", "g_data.c", 1568).
void sub_16E670(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016e670
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = dsll32(s0, 16);
    s1 = dsra32(s1, 16);
    // v1 = (0 <= s1 < 30): the inlined id check
    bool in_range = false;
    if (i64(s1) >= 0) {
        // 0x0016e694
        charge(ctx, 3);
        v1 = slti(s1, 30);
        in_range = v1 != 0;
    }
    if (in_range) {
        // 0x0016e6ac
        charge(ctx, 1);
        v1 = 1;
    } else {
        charge(ctx, 3);
        v1 = 0;
    }
    charge(ctx, 2);
    if (v1 != 0) {
        // 0x0016e6b8
        charge(ctx, 2);
        // v1 = (0 <= s1 < 30): the inlined id check
        bool in_range2 = false;
        if (i64(s1) >= 0) {
            // 0x0016e6c0
            charge(ctx, 3);
            v1 = slti(s1, 30);
            in_range2 = v1 != 0;
        }
        if (in_range2) {
            // 0x0016e6d8
            charge(ctx, 1);
            v1 = 1;
        } else {
            charge(ctx, 3);
            v1 = 0;
        }
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0016e6e4
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 1429;
            jal(ctx, 0x16E6F0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1429): returns
        }
        // 0x0016e6f8
        charge(ctx, 6);
        v1 = 0x830000;
        v1 = addiu(v1, 25206);  // &kComuRank
        v1 = addu(v1, s1);
        lb(v1, v1, 0);
        if (i64(v1) > 0) {
            // 0x0016e734
            charge(ctx, 12);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            v1 = 0x830000;
            v1 = addiu(v1, 25356);  // &kComuB (gGlobalWork +0x10C)
            a0 = addu(v1, a0);
            lb(v1, a0, 0);
            v1 = addiu(v1, 1);
            sb(v1, a0, 0);
            v1 = dsll32(v1, 24);
            v1 = dsra32(v1, 24);
            if (i64(v1) < 0) {
                // 0x0016e764
                charge(ctx, 1);
                sb(zero, a0, 0);
            }
            // 0x0016e768
            charge(ctx, 4);
            lb(v1, a0, 0);
            v1 = slti(v1, 10);
            if (v1 == 0) {
                // 0x0016e778
                charge(ctx, 2);
                v1 = 9;
                sb(v1, a0, 0);
            }
        } else {
            // 0x0016e710
            charge(ctx, 9);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12896);  // "no exist comu %s %d"
            a1 = 0x5E0000;
            a1 = addiu(a1, 12440);  // "g_data.c"
            a2 = 1568;
            jal(ctx, 0x16E724u, gen::fn_printf_005225a8);
        }
    }
    // 0x0016e780 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0016E7A0 sub_16E7A0 -- 168 bytes; leaf frame (no stack)
// sub_16E7A0(comu, value): kComuDay[comu] (s16, gGlobalWork +0x12A) = value clamped to 0..360 when 0 <= comu < 30.
void sub_16E7A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016e7a0
    enter(ctx, 4);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    // v1 = (0 <= a0 < 30): the inlined id check
    bool in_range = false;
    if (i64(a0) >= 0) {
        // 0x0016e7b0
        charge(ctx, 3);
        v1 = slti(a0, 30);
        in_range = v1 != 0;
    }
    if (in_range) {
        // 0x0016e7c8
        charge(ctx, 1);
        v1 = 1;
    } else {
        charge(ctx, 3);
        v1 = 0;
    }
    charge(ctx, 2);
    if (v1 != 0) {
        // 0x0016e7d4
        charge(ctx, 4);
        v1 = dsll32(a1, 16);
        v1 = dsra32(v1, 16);
        if (i64(v1) >= 0) {
            // 0x0016e800
            charge(ctx, 3);
            at = slti(v1, 361);
            if (at != 0) {
                // 0x0016e82c
                charge(ctx, 5);
                a0 = sll(a0, 1);
                v1 = 0x830000;
                v1 = addiu(v1, 25386);  // &kComuDay (gGlobalWork +0x12A)
                v1 = addu(v1, a0);
                sh(a1, v1, 0);
            } else {
                // 0x0016e80c
                charge(ctx, 8);
                a1 = 360;
                a0 = sll(a0, 1);
                v1 = 0x830000;
                v1 = addiu(v1, 25386);  // &kComuDay (gGlobalWork +0x12A)
                v1 = addu(v1, a0);
                sh(a1, v1, 0);
            }
        } else {
            // 0x0016e7e4
            charge(ctx, 7);
            a0 = sll(a0, 1);
            v1 = 0x830000;
            v1 = addiu(v1, 25386);  // &kComuDay (gGlobalWork +0x12A)
            v1 = addu(v1, a0);
            sh(zero, v1, 0);
        }
    }
    // 0x0016e840 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016E850 sub_16E850 [datComuDaysSince] -- 208 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_16E850(comu): days since kComuDay[comu] (datGetDaysSinceApr5() - stamp, s16; K_Assert line 1620 on a negative
// result), 0 when the stamp is 0. K_Assert line 1612 unless 0 <= comu < 30.
void sub_16E850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016e850
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = dsll32(a0, 16);
    s0 = dsra32(s0, 16);
    // v0 = (0 <= s0 < 30): the inlined id check
    bool in_range = false;
    if (i64(s0) >= 0) {
        // 0x0016e86c
        charge(ctx, 3);
        v0 = slti(s0, 30);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x0016e884
        charge(ctx, 1);
        v0 = 1;
    } else {
        charge(ctx, 3);
        v0 = 0;
    }
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x0016e890
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 1612;
        jal(ctx, 0x16E89Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1612): returns
    }
    // 0x0016e8a4
    charge(ctx, 7);
    v1 = sll(s0, 1);
    v0 = 0x830000;
    v0 = addiu(v0, 25386);  // &kComuDay (gGlobalWork +0x12A)
    s0 = addu(v0, v1);
    lh(v0, s0, 0);
    if (v0 != 0) {
        // 0x0016e8cc
        charge(ctx, 10);
        jal(ctx, 0x16E8CCu, gen::fn_datGetDaysSinceApr5_0016ef20);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
        lh(v0, s0, 0);
        v0 = subu(v1, v0);
        s0 = dsll32(v0, 16);
        s0 = dsra32(s0, 16);
        if (i64(s0) < 0) {
            // 0x0016e8f4
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 1620;
            jal(ctx, 0x16E900u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1620): returns
        }
        // 0x0016e908
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x0016e8c0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0016e90c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0016E920 sub_16E920 -- 16 bytes; leaf frame (no stack)
// sub_16E920(value): the s16 at gGlobalWork +0x74 = value (sub_16DD40's word).
void sub_16E920(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x0016e920
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 0x830000;
    sh(a0, v1, 25204);  // the social-link block's first s16 (gGlobalWork +0x74)
}

// 0x001717B0 sub_1717B0 [datComuGetBlock] -- 16 bytes; leaf frame (no stack)
// sub_1717B0(): the address of the social-link block (gGlobalWork +0x74).
void sub_1717B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x001717b0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x830000;
    v0 = addiu(v0, 25204);  // &kComuBlock (gGlobalWork +0x74)
}

// 0x001717C0 sub_1717C0 -- 240 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1717C0(comu): MT_Misc_BitChk(0x900 + comu) == 1 || MT_Misc_BitChk(0x920 + comu) == 1 (K_Assert lines 2768 / 2755
// unless 0 <= comu < 30).
void sub_1717C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001717c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = dsll32(s1, 16);
    s0 = dsra32(s0, 16);
    // v0 = (0 <= s0 < 30): the inlined id check
    bool in_range = false;
    if (i64(s0) >= 0) {
        // 0x001717e4
        charge(ctx, 3);
        v0 = slti(s0, 30);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x001717fc
        charge(ctx, 1);
        v0 = 1;
    } else {
        charge(ctx, 3);
        v0 = 0;
    }
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x00171808
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 2768;
        jal(ctx, 0x171814u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2768): returns
    }
    // 0x0017181c
    charge(ctx, 6);
    a0 = addiu(s1, 2304);
    jal(ctx, 0x171820u, gen::fn_MT_Misc_BitChk_003951d0);  // bit 0x900 + comu
    v1 = 1;
    bool result = true;  // 1 when either bit is set
    if (v0 != v1) {
        // 0x00171834: the 0x900 bit is clear: v1 = (0 <= comu < 30), the second inlined id check
        charge(ctx, 2);
        bool ok = false;
        if (i64(s0) >= 0) {
            // 0x0017183c
            charge(ctx, 3);
            v0 = slti(s0, 30);
            ok = v0 != 0;
        }
        if (!ok) {
            // 0x00171848
            charge(ctx, 1);
            v1 = 0;
        }
        // 0x0017184c
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00171854
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 2755;
            jal(ctx, 0x171860u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2755): returns
        }
        // 0x00171868
        charge(ctx, 8);
        a0 = addiu(s1, 2336);
        jal(ctx, 0x17186Cu, gen::fn_MT_Misc_BitChk_003951d0);  // bit 0x920 + comu
        v0 = v0 ^ 0x1;
        v1 = sltiu(v0, 1);
        v0 = 1;
        if (v1 != v0) {
            // 0x00171894: neither bit: 0
            charge(ctx, 1);
            v0 = 0;
            result = false;
        }
    }
    if (result) {
        // 0x00171888
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00171898 (the shared epilogue)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001718B0 sub_1718B0 -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1718B0(comu): kComuE[comu] += 1, capped at 32 (s16, gGlobalWork +0x1DE); K_Assert line 2784 unless 0 <= comu <
// 30.
void sub_1718B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001718b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0x830000;
    s0 = addiu(s0, 25204);  // &kComuBlock (gGlobalWork +0x74)
    v1 = dsll32(s1, 16);
    v1 = dsra32(v1, 16);
    // v1 = (0 <= v1 < 30): the inlined id check
    bool in_range = false;
    if (i64(v1) >= 0) {
        // 0x001718dc
        charge(ctx, 3);
        v1 = slti(v1, 30);
        in_range = v1 != 0;
    }
    if (in_range) {
        // 0x001718f4
        charge(ctx, 1);
        v1 = 1;
    } else {
        charge(ctx, 3);
        v1 = 0;
    }
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x00171900
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 2784;
        jal(ctx, 0x17190Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2784): returns
    }
    // 0x00171914
    charge(ctx, 7);
    v1 = sll(s1, 1);
    v1 = addu(v1, s0);
    a0 = addiu(v1, 362);
    lhu(v1, v1, 362);
    at = slti(v1, 32);
    if (at == 0) {
        // 0x00171940
        charge(ctx, 2);
        v1 = 32;
        sh(v1, a0, 0);
    } else {
        // 0x00171930
        charge(ctx, 4);
        v1 = addiu(v1, 1);
        sh(v1, a0, 0);
    }
    // 0x00171948 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00171960 sub_171960 -- 344 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_171960(comu, value): kComuC[comu] -= value (s16, gGlobalWork +0x166) while it is below 1000 and the link has a
// rank other than 0 and 10 (K_Assert lines 2816 / 1429); it stays >= 1 while the day-event record holds this comu
// (sub_172C50) and never goes below 0.
void sub_171960(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00171960
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    sh(zero, sp, 0x5E);
    a0 = 0x830000;
    a0 = addiu(a0, 25204);  // &kComuBlock (gGlobalWork +0x74)
    v1 = sll(s3, 1);
    v1 = addu(v1, a0);
    s1 = addiu(v1, 242);
    lh(v1, v1, 242);
    at = slti(v1, 1000);
    if (at != 0) {
        // 0x001719a8
        charge(ctx, 4);
        s0 = dsll32(s3, 16);
        s0 = dsra32(s0, 16);
        // v1 = (0 <= s0 < 30): the inlined id check
        bool in_range = false;
        if (i64(s0) >= 0) {
            // 0x001719b8
            charge(ctx, 3);
            v1 = slti(s0, 30);
            in_range = v1 != 0;
        }
        if (in_range) {
            // 0x001719d0
            charge(ctx, 1);
            v1 = 1;
        } else {
            charge(ctx, 3);
            v1 = 0;
        }
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x001719dc
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 2816;
            jal(ctx, 0x1719E8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2816): returns
        }
        // 0x001719f0
        charge(ctx, 2);
        // v1 = (0 <= s0 < 30): the inlined id check
        bool in_range2 = false;
        if (i64(s0) >= 0) {
            // 0x001719f8
            charge(ctx, 3);
            v1 = slti(s0, 30);
            in_range2 = v1 != 0;
        }
        if (in_range2) {
            // 0x00171a10
            charge(ctx, 1);
            v1 = 1;
        } else {
            charge(ctx, 3);
            v1 = 0;
        }
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00171a1c
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 1429;
            jal(ctx, 0x171A28u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1429): returns
        }
        // 0x00171a30
        charge(ctx, 6);
        v1 = 0x830000;
        v1 = addiu(v1, 25206);  // &kComuRank
        v1 = addu(v1, s0);
        lb(a0, v1, 0);
        if (i64(a0) > 0) {
            // 0x00171a48
            charge(ctx, 3);
            v1 = 10;
            if (a0 != v1) {
                // 0x00171a54
                charge(ctx, 8);
                lh(v0, s1, 0);
                v0 = subu(v0, s2);
                sh(v0, s1, 0);
                a0 = addiu(sp, 0x5E);
                jal(ctx, 0x171A64u, gen::fn_sub_172C50_00172c50);
                if (v0 != 0) {
                    // 0x00171a74
                    charge(ctx, 3);
                    lh(v1, sp, 0x5E);
                    if (v1 == s3) {
                        // 0x00171a80
                        charge(ctx, 2);
                        v1 = 1;
                        sh(v1, s1, 0);
                    }
                }
                // 0x00171a88
                charge(ctx, 3);
                lh(v1, s1, 0);
                if (i64(v1) < 0) {
                    // 0x00171a94
                    charge(ctx, 1);
                    sh(zero, s1, 0);
                }
            }
        }
    }
    // 0x00171a98 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00171AC0 sub_171AC0 -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_171AC0(comu): kComuC[comu] (s16, gGlobalWork +0x166); K_Assert line 2848 unless 0 <= comu < 30.
void sub_171AC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00171ac0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0x830000;
    s0 = addiu(s0, 25204);  // &kComuBlock (gGlobalWork +0x74)
    v0 = dsll32(s1, 16);
    v0 = dsra32(v0, 16);
    // v0 = (0 <= v0 < 30): the inlined id check
    bool in_range = false;
    if (i64(v0) >= 0) {
        // 0x00171aec
        charge(ctx, 3);
        v0 = slti(v0, 30);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x00171b04
        charge(ctx, 1);
        v0 = 1;
    } else {
        charge(ctx, 3);
        v0 = 0;
    }
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x00171b10
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 2848;
        jal(ctx, 0x171B1Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2848): returns
    }
    // 0x00171b24 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = sll(s1, 1);
    v0 = addu(v0, s0);
    lh(v0, v0, 242);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00171B50 sub_171B50 -- 232 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_171B50(comu): kComuC[comu] = the s16 table sub_3BDDD0() [comu] (the link's initial value); K_Assert lines 2860 /
// 2800 unless 0 <= comu < 30.
void sub_171B50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00171b50
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s3 = dsll32(s0, 16);
    s3 = dsra32(s3, 16);
    // v0 = (0 <= s3 < 30): the inlined id check
    bool in_range = false;
    if (i64(s3) >= 0) {
        // 0x00171b7c
        charge(ctx, 3);
        v0 = slti(s3, 30);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x00171b94
        charge(ctx, 1);
        v0 = 1;
    } else {
        charge(ctx, 3);
        v0 = 0;
    }
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x00171ba0
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 2860;
        jal(ctx, 0x171BACu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2860): returns
    }
    // 0x00171bb4
    charge(ctx, 9);
    jal(ctx, 0x171BB4u, gen::fn_sub_3BDDD0_003bddd0);
    s2 = sll(s0, 1);
    v1 = addu(v0, s2);
    lh(s1, v1, 0);
    s0 = 0x830000;
    s0 = addiu(s0, 25204);  // &kComuBlock (gGlobalWork +0x74)
    // v1 = (0 <= s3 < 30): the inlined id check
    bool in_range2 = false;
    if (i64(s3) >= 0) {
        // 0x00171bd8
        charge(ctx, 3);
        v1 = slti(s3, 30);
        in_range2 = v1 != 0;
    }
    if (in_range2) {
        // 0x00171bf0
        charge(ctx, 1);
        v1 = 1;
    } else {
        charge(ctx, 3);
        v1 = 0;
    }
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x00171bfc
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 2800;
        jal(ctx, 0x171C08u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2800): returns
    }
    // 0x00171c10 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v1 = addu(s2, s0);
    sh(s1, v1, 242);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00171C40 sub_171C40 -- 580 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_171C40(comu, on): sets (on == 1) or clears bit 0x900 + comu. Setting, when the bit was clear: kComuE[comu] += 1
// capped at 32 (sub_1718B0 inlined), kComuC[comu] = 0, the bit set; then bit 0x987 (2439) set. Clearing: the bit
// cleared and kComuC[comu] reloaded from sub_3BDDD0() (sub_171B50 inlined). K_Assert lines 2876 / 2784 / 2800 / 2860
// unless 0 <= comu < 30.
void sub_171C40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00171c40
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s0 = a1;
    s1 = dsll32(s2, 16);
    s1 = dsra32(s1, 16);
    // v0 = (0 <= s1 < 30): the inlined id check
    bool in_range = false;
    if (i64(s1) >= 0) {
        // 0x00171c70
        charge(ctx, 3);
        v0 = slti(s1, 30);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x00171c88
        charge(ctx, 1);
        v0 = 1;
    } else {
        charge(ctx, 3);
        v0 = 0;
    }
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x00171c94
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 2876;
        jal(ctx, 0x171CA0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2876): returns
    }
    // 0x00171ca8
    charge(ctx, 3);
    v0 = 1;
    if (s0 != v0) {
        // 0x00171db4
        charge(ctx, 5);
        a0 = addiu(s2, 2304);
        jal(ctx, 0x171DB8u, gen::fn_sub_3951A0_003951a0);
        // v0 = (0 <= s1 < 30): the inlined id check
        bool in_range2 = false;
        if (i64(s1) >= 0) {
            // 0x00171dc8
            charge(ctx, 3);
            v0 = slti(s1, 30);
            in_range2 = v0 != 0;
        }
        if (in_range2) {
            // 0x00171de0
            charge(ctx, 1);
            v0 = 1;
        } else {
            charge(ctx, 3);
            v0 = 0;
        }
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x00171dec
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 2860;
            jal(ctx, 0x171DF8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2860): returns
        }
        // 0x00171e00
        charge(ctx, 9);
        jal(ctx, 0x171E00u, gen::fn_sub_3BDDD0_003bddd0);
        s3 = sll(s2, 1);
        v1 = addu(v0, s3);
        lh(s2, v1, 0);
        s0 = 0x830000;
        s0 = addiu(s0, 25204);  // &kComuBlock (gGlobalWork +0x74)
        // v1 = (0 <= s1 < 30): the inlined id check
        bool in_range3 = false;
        if (i64(s1) >= 0) {
            // 0x00171e24
            charge(ctx, 3);
            v1 = slti(s1, 30);
            in_range3 = v1 != 0;
        }
        if (in_range3) {
            // 0x00171e3c
            charge(ctx, 1);
            v1 = 1;
        } else {
            charge(ctx, 3);
            v1 = 0;
        }
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00171e48
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 2800;
            jal(ctx, 0x171E54u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2800): returns
        }
        // 0x00171e5c
        charge(ctx, 2);
        v1 = addu(s3, s0);
        sh(s2, v1, 242);
    } else {
        // 0x00171cb4
        charge(ctx, 5);
        a0 = addiu(s2, 2304);
        jal(ctx, 0x171CB8u, gen::fn_MT_Misc_BitChk_003951d0);
        if (v0 == 0) {
            // 0x00171cc8
            charge(ctx, 4);
            s3 = 0x830000;
            s3 = addiu(s3, 25204);  // &kComuBlock (gGlobalWork +0x74)
            // v0 = (0 <= s1 < 30): the inlined id check
            bool in_range4 = false;
            if (i64(s1) >= 0) {
                // 0x00171cd8
                charge(ctx, 3);
                v0 = slti(s1, 30);
                in_range4 = v0 != 0;
            }
            if (in_range4) {
                // 0x00171cf0
                charge(ctx, 1);
                v0 = 1;
            } else {
                charge(ctx, 3);
                v0 = 0;
            }
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x00171cfc
                charge(ctx, 5);
                a0 = 0x5E0000;
                a0 = addiu(a0, 12440);  // "g_data.c"
                a1 = 2784;
                jal(ctx, 0x171D08u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2784): returns
            }
            // 0x00171d10
            charge(ctx, 7);
            s0 = sll(s2, 1);
            v0 = addu(s0, s3);
            v1 = addiu(v0, 362);
            lhu(v0, v0, 362);
            at = slti(v0, 32);
            if (at == 0) {
                // 0x00171d3c
                charge(ctx, 2);
                v0 = 32;
                sh(v0, v1, 0);
            } else {
                // 0x00171d2c
                charge(ctx, 4);
                v0 = addiu(v0, 1);
                sh(v0, v1, 0);
            }
            // 0x00171d44
            charge(ctx, 4);
            s3 = 0x830000;
            s3 = addiu(s3, 25204);  // &kComuBlock (gGlobalWork +0x74)
            // v0 = (0 <= s1 < 30): the inlined id check
            bool in_range5 = false;
            if (i64(s1) >= 0) {
                // 0x00171d54
                charge(ctx, 3);
                v0 = slti(s1, 30);
                in_range5 = v0 != 0;
            }
            if (in_range5) {
                // 0x00171d6c
                charge(ctx, 1);
                v0 = 1;
            } else {
                charge(ctx, 3);
                v0 = 0;
            }
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x00171d78
                charge(ctx, 5);
                a0 = 0x5E0000;
                a0 = addiu(a0, 12440);  // "g_data.c"
                a1 = 2800;
                jal(ctx, 0x171D84u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2800): returns
            }
            // 0x00171d8c
            charge(ctx, 5);
            v0 = addu(s0, s3);
            sh(zero, v0, 242);
            a0 = addiu(s2, 2304);
            jal(ctx, 0x171D98u, gen::fn_sub_395170_00395170);
        }
        // 0x00171da0
        charge(ctx, 5);
        a0 = 2439;
        jal(ctx, 0x171DA4u, gen::fn_sub_395170_00395170);
    }
    // 0x00171e64 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00171E90 sub_171E90 -- 188 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_171E90(comu, value): kComuE[comu] = value capped at 32; K_Assert line 2904 unless 0 <= comu < 30.
void sub_171E90(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00171e90
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = 0x830000;
    s0 = addiu(s0, 25204);  // &kComuBlock (gGlobalWork +0x74)
    v1 = dsll32(s2, 16);
    v1 = dsra32(v1, 16);
    // v1 = (0 <= v1 < 30): the inlined id check
    bool in_range = false;
    if (i64(v1) >= 0) {
        // 0x00171ec4
        charge(ctx, 3);
        v1 = slti(v1, 30);
        in_range = v1 != 0;
    }
    if (in_range) {
        // 0x00171edc
        charge(ctx, 1);
        v1 = 1;
    } else {
        charge(ctx, 3);
        v1 = 0;
    }
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x00171ee8
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 2904;
        jal(ctx, 0x171EF4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2904): returns
    }
    // 0x00171efc
    charge(ctx, 4);
    v1 = s1 & 0xFFFF;
    at = slti(v1, 33);
    if (at != 0) {
        // 0x00171f24
        charge(ctx, 3);
        v1 = sll(s2, 1);
        v1 = addu(v1, s0);
        sh(s1, v1, 362);
    } else {
        // 0x00171f0c
        charge(ctx, 6);
        a0 = 32;
        v1 = sll(s2, 1);
        v1 = addu(v1, s0);
        sh(a0, v1, 362);
    }
    // 0x00171f30 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00171F50 sub_171F50 -- 360 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_171F50(comu, on): sets (on == 1) or clears bit 0x920 + comu. Setting, when the bit was clear: kComuE[comu] += 1
// (sub_1718B0), kComuDay2[comu] (s16, gGlobalWork +0x1A2) = today, the bit set. K_Assert lines 2971 / 2934 / 2955
// unless 0 <= comu < 30.
void sub_171F50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00171f50
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1;
    s2 = dsll32(s0, 16);
    s2 = dsra32(s2, 16);
    // v0 = (0 <= s2 < 30): the inlined id check
    bool in_range = false;
    if (i64(s2) >= 0) {
        // 0x00171f7c
        charge(ctx, 3);
        v0 = slti(s2, 30);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x00171f94
        charge(ctx, 1);
        v0 = 1;
    } else {
        charge(ctx, 3);
        v0 = 0;
    }
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x00171fa0
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 2971;
        jal(ctx, 0x171FACu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2971): returns
    }
    // 0x00171fb4
    charge(ctx, 3);
    v0 = 1;
    if (s1 != v0) {
        // 0x00172090
        charge(ctx, 3);
        a0 = addiu(s0, 2336);
        jal(ctx, 0x172094u, gen::fn_sub_3951A0_003951a0);
    } else {
        // 0x00171fc0
        charge(ctx, 5);
        a0 = addiu(s0, 2336);
        jal(ctx, 0x171FC4u, gen::fn_MT_Misc_BitChk_003951d0);
        if (v0 == 0) {
            // 0x00171fd4
            charge(ctx, 2);
            // v0 = (0 <= s2 < 30): the inlined id check
            bool in_range2 = false;
            if (i64(s2) >= 0) {
                // 0x00171fdc
                charge(ctx, 3);
                v0 = slti(s2, 30);
                in_range2 = v0 != 0;
            }
            if (in_range2) {
                // 0x00171ff4
                charge(ctx, 1);
                v0 = 1;
            } else {
                charge(ctx, 3);
                v0 = 0;
            }
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x00172000
                charge(ctx, 5);
                a0 = 0x5E0000;
                a0 = addiu(a0, 12440);  // "g_data.c"
                a1 = 2934;
                jal(ctx, 0x17200Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2934): returns
            }
            // 0x00172014
            charge(ctx, 7);
            a0 = s0;
            jal(ctx, 0x172018u, gen::fn_sub_1718B0_001718b0);
            s1 = 0x830000;
            s1 = addiu(s1, 25204);  // &kComuBlock (gGlobalWork +0x74)
            // v0 = (0 <= s2 < 30): the inlined id check
            bool in_range3 = false;
            if (i64(s2) >= 0) {
                // 0x00172030
                charge(ctx, 3);
                v0 = slti(s2, 30);
                in_range3 = v0 != 0;
            }
            if (in_range3) {
                // 0x00172048
                charge(ctx, 1);
                v0 = 1;
            } else {
                charge(ctx, 3);
                v0 = 0;
            }
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x00172054
                charge(ctx, 5);
                a0 = 0x5E0000;
                a0 = addiu(a0, 12440);  // "g_data.c"
                a1 = 2955;
                jal(ctx, 0x172060u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2955): returns
            }
            // 0x00172068
            charge(ctx, 10);
            v0 = 0x830000;
            lh(v1, v0, 26524);  // g_datDaysSinceApr5
            v0 = sll(s0, 1);
            v0 = addu(v0, s1);
            sh(v1, v0, 302);
            a0 = addiu(s0, 2336);
            jal(ctx, 0x172080u, gen::fn_sub_395170_00395170);
        }
    }
    // 0x0017209c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001720C0 sub_1720C0 -- 156 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1720C0(comu, out): *out = kComuDay2[comu] (s16 +0x1A2) and returns the u16 kComuF[comu] (gGlobalWork +0x21A);
// K_Assert line 2992 unless 0 <= comu < 30.
void sub_1720C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001720c0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s0 = a1;
    s1 = 0x830000;
    s1 = addiu(s1, 25204);  // &kComuBlock (gGlobalWork +0x74)
    v0 = dsll32(s2, 16);
    v0 = dsra32(v0, 16);
    // v0 = (0 <= v0 < 30): the inlined id check
    bool in_range = false;
    if (i64(v0) >= 0) {
        // 0x001720f4
        charge(ctx, 3);
        v0 = slti(v0, 30);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x0017210c
        charge(ctx, 1);
        v0 = 1;
    } else {
        charge(ctx, 3);
        v0 = 0;
    }
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x00172118
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 2992;
        jal(ctx, 0x172124u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2992): returns
    }
    // 0x0017212c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    v0 = sll(s2, 1);
    v1 = addu(v0, s1);
    lh(v0, v1, 302);
    sw(v0, s0, 0);
    lhu(v0, v1, 422);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00172160 sub_172160 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_172160(comu): MT_Misc_BitChk(0x940 + comu) == 1; K_Assert line 3036 unless 0 <= comu < 30.
void sub_172160(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00172160
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = dsll32(s0, 16);
    v0 = dsra32(v0, 16);
    // v0 = (0 <= v0 < 30): the inlined id check
    bool in_range = false;
    if (i64(v0) >= 0) {
        // 0x00172180
        charge(ctx, 3);
        v0 = slti(v0, 30);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x00172198
        charge(ctx, 1);
        v0 = 1;
    } else {
        charge(ctx, 3);
        v0 = 0;
    }
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x001721a4
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 3036;
        jal(ctx, 0x1721B0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 3036): returns
    }
    // 0x001721b8
    charge(ctx, 6);
    a0 = addiu(s0, 2368);
    jal(ctx, 0x1721BCu, gen::fn_MT_Misc_BitChk_003951d0);
    v1 = 1;
    if (v0 != v1) {
        // 0x001721dc
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x001721d0
        charge(ctx, 3);
        v0 = v1;
    }
    // 0x001721e0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00172200 sub_172200 -- 412 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_172200(comu, on): sets (on == 1: bits 0x940 + comu and 0x988) or clears bit 0x940 + comu; clearing also clears
// bit 0x900 + comu and reloads kComuC[comu] from sub_3BDDD0() (K_Assert line 2800 unless sub_16DCE0(comu)). K_Assert
// lines 3051 / 2876 / 2860 unless 0 <= comu < 30.
void sub_172200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00172200
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s2 = a1;
    s1 = dsll32(s0, 16);
    s1 = dsra32(s1, 16);
    // v0 = (0 <= s1 < 30): the inlined id check
    bool in_range = false;
    if (i64(s1) >= 0) {
        // 0x00172230
        charge(ctx, 3);
        v0 = slti(s1, 30);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x00172248
        charge(ctx, 1);
        v0 = 1;
    } else {
        charge(ctx, 3);
        v0 = 0;
    }
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x00172254
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 3051;
        jal(ctx, 0x172260u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 3051): returns
    }
    // 0x00172268
    charge(ctx, 3);
    v0 = 1;
    if (s2 != v0) {
        // 0x00172294
        charge(ctx, 5);
        a0 = addiu(s0, 2368);
        jal(ctx, 0x172298u, gen::fn_sub_3951A0_003951a0);
        // v0 = (0 <= s1 < 30): the inlined id check
        bool in_range2 = false;
        if (i64(s1) >= 0) {
            // 0x001722a8
            charge(ctx, 3);
            v0 = slti(s1, 30);
            in_range2 = v0 != 0;
        }
        if (in_range2) {
            // 0x001722c0
            charge(ctx, 1);
            v0 = 1;
        } else {
            charge(ctx, 3);
            v0 = 0;
        }
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x001722cc
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 2876;
            jal(ctx, 0x1722D8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2876): returns
        }
        // 0x001722e0
        charge(ctx, 5);
        a0 = addiu(s0, 2304);
        jal(ctx, 0x1722E4u, gen::fn_sub_3951A0_003951a0);
        // v0 = (0 <= s1 < 30): the inlined id check
        bool in_range3 = false;
        if (i64(s1) >= 0) {
            // 0x001722f4
            charge(ctx, 3);
            v0 = slti(s1, 30);
            in_range3 = v0 != 0;
        }
        if (in_range3) {
            // 0x0017230c
            charge(ctx, 1);
            v0 = 1;
        } else {
            charge(ctx, 3);
            v0 = 0;
        }
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x00172318
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 2860;
            jal(ctx, 0x172324u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2860): returns
        }
        // 0x0017232c
        charge(ctx, 13);
        jal(ctx, 0x17232Cu, gen::fn_sub_3BDDD0_003bddd0);
        s3 = sll(s0, 1);
        v0 = addu(v0, s3);
        lh(s2, v0, 0);
        s1 = 0x830000;
        s1 = addiu(s1, 25204);  // &kComuBlock (gGlobalWork +0x74)
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x172350u, gen::fn_sub_16DCE0_0016dce0);
        if (v0 == 0) {
            // 0x00172360
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 2800;
            jal(ctx, 0x17236Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2800): returns
        }
        // 0x00172374
        charge(ctx, 2);
        v1 = addu(s3, s1);
        sh(s2, v1, 242);
    } else {
        // 0x00172274
        charge(ctx, 8);
        a0 = addiu(s0, 2368);
        jal(ctx, 0x172278u, gen::fn_sub_395170_00395170);
        a0 = 2440;
        jal(ctx, 0x172284u, gen::fn_sub_395170_00395170);
    }
    // 0x0017237c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001723A0 sub_1723A0 [datComuSetRankReady] -- 256 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1723A0(comu, rank, on): sets (on == 1) or clears flag bit 0x400 + 32 comu + rank - 1 when 0 < rank < 11 (K_Assert
// lines 3072 / 3075 on rank <= 0 or comu out of 0..29).
void sub_1723A0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001723a0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    a0 = addiu(s2, -1);
    v1 = sll(s3, 5);
    v1 = addiu(v1, 1024);
    s0 = addu(a0, v1);
    if (i64(s2) <= 0) {
        // 0x001723dc
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 3072;
        jal(ctx, 0x1723E8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 3072): returns
    }
    // 0x001723f0
    charge(ctx, 4);
    v1 = dsll32(s3, 16);
    v1 = dsra32(v1, 16);
    // v1 = (0 <= v1 < 30): the inlined id check
    bool in_range = false;
    if (i64(v1) >= 0) {
        // 0x00172400
        charge(ctx, 3);
        v1 = slti(v1, 30);
        in_range = v1 != 0;
    }
    if (in_range) {
        // 0x00172418
        charge(ctx, 1);
        v1 = 1;
    } else {
        charge(ctx, 3);
        v1 = 0;
    }
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x00172424
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 3075;
        jal(ctx, 0x172430u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 3075): returns
    }
    // 0x00172438: only ranks 1..10 touch a bit
    charge(ctx, 2);
    bool rank_ok = false;
    if (i64(s2) > 0) {
        // 0x00172440
        charge(ctx, 3);
        at = slti(s2, 11);
        rank_ok = at != 0;
    }
    if (rank_ok) {
        // 0x00172454: MT_Misc_BitOn / BitOff(0x400 + 32 comu + rank - 1)
        charge(ctx, 3);
        v0 = 1;
        if (s1 != v0) {
            // 0x00172474
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x172478u, gen::fn_sub_3951A0_003951a0);
        } else {
            // 0x00172460
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x172464u, gen::fn_sub_395170_00395170);
        }
    } else {
        // 0x0017244c
        charge(ctx, 2);
    }
    // 0x00172480 (the shared epilogue)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001724A0 sub_1724A0 [datComuSetRankSeen] -- 256 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1724A0(comu, rank, on): sub_1723A0 for the second per-rank bit row, 0x410 + 32 comu + rank - 1 (K_Assert lines
// 3095 / 3097).
void sub_1724A0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001724a0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    a0 = addiu(s2, -1);
    v1 = sll(s3, 5);
    v1 = addiu(v1, 1040);
    s0 = addu(a0, v1);
    if (i64(s2) <= 0) {
        // 0x001724dc
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 3095;
        jal(ctx, 0x1724E8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 3095): returns
    }
    // 0x001724f0
    charge(ctx, 4);
    v1 = dsll32(s3, 16);
    v1 = dsra32(v1, 16);
    // v1 = (0 <= v1 < 30): the inlined id check
    bool in_range = false;
    if (i64(v1) >= 0) {
        // 0x00172500
        charge(ctx, 3);
        v1 = slti(v1, 30);
        in_range = v1 != 0;
    }
    if (in_range) {
        // 0x00172518
        charge(ctx, 1);
        v1 = 1;
    } else {
        charge(ctx, 3);
        v1 = 0;
    }
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x00172524
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 3097;
        jal(ctx, 0x172530u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 3097): returns
    }
    // 0x00172538: only ranks 1..10 touch a bit
    charge(ctx, 2);
    bool rank_ok = false;
    if (i64(s2) > 0) {
        // 0x00172540
        charge(ctx, 3);
        at = slti(s2, 11);
        rank_ok = at != 0;
    }
    if (rank_ok) {
        // 0x00172554: MT_Misc_BitOn / BitOff(0x410 + 32 comu + rank - 1)
        charge(ctx, 3);
        v0 = 1;
        if (s1 != v0) {
            // 0x00172574
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x172578u, gen::fn_sub_3951A0_003951a0);
        } else {
            // 0x00172560
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x172564u, gen::fn_sub_395170_00395170);
        }
    } else {
        // 0x0017254c
        charge(ctx, 2);
    }
    // 0x00172580 (the shared epilogue)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001725A0 sub_1725A0 [datComuRankUp] -- 184 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1725A0(comu): when sub_172660(comu) finds a ready rank, raises social link comu by one (sub_16E410(comu, rank +
// 1)); K_Assert line 3118 unless 0 <= comu < 30. The rank byte is read before the check.
void sub_1725A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001725a0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v1 = dsll32(s0, 16);
    v1 = dsra32(v1, 16);
    v0 = 0x830000;
    v0 = addiu(v0, 25206);  // &kComuRank
    v0 = addu(v0, v1);
    lb(s1, v0, 0);
    // v0 = (0 <= v1 < 30): the inlined id check
    bool in_range = false;
    if (i64(v1) >= 0) {
        // 0x001725d4
        charge(ctx, 3);
        v0 = slti(v1, 30);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x001725ec
        charge(ctx, 1);
        v0 = 1;
    } else {
        charge(ctx, 3);
        v0 = 0;
    }
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x001725f8
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 3118;
        jal(ctx, 0x172604u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 3118): returns
    }
    // 0x0017260c
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x172610u, gen::fn_sub_172660_00172660);
    v1 = 1;
    if (v0 == v1) {
        // 0x00172624
        charge(ctx, 7);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        v0 = addiu(s1, 1);
        a1 = dsll32(v0, 24);
        a1 = dsra32(a1, 24);
        jal(ctx, 0x172638u, gen::fn_sub_16E410_0016e410);
    }
    // 0x00172640 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00172660 sub_172660 [datComuHasPendingRank] -- 240 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_172660(comu): 1 when some rank 1..10 of comu has its 0x400 bit set and its 0x410 bit clear; K_Assert line 3135
// unless 0 <= comu < 30.
void sub_172660(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00172660
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    v0 = dsll32(s1, 16);
    v0 = dsra32(v0, 16);
    // v0 = (0 <= v0 < 30): the inlined id check
    bool in_range = false;
    if (i64(v0) >= 0) {
        // 0x0017268c
        charge(ctx, 3);
        v0 = slti(v0, 30);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x001726a4
        charge(ctx, 1);
        v0 = 1;
    } else {
        charge(ctx, 3);
        v0 = 0;
    }
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x001726b0
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 3135;
        jal(ctx, 0x1726BCu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 3135): returns
    }
    // 0x001726c4
    charge(ctx, 6);
    s0 = 1;
    v0 = sll(s1, 5);
    s2 = addiu(v0, 1040);  // 0x410 + 32 comu: the 'seen' bit row
    s1 = addiu(v0, 1024);  // 0x400 + 32 comu: the 'ready' bit row
    for (;;) {  // s0 = rank 1..10
        // 0x00172720
        charge(ctx, 3);
        at = slti(s0, 11);
        if (at == 0) {
            // 0x0017272c: no pending rank
            charge(ctx, 1);
            v0 = 0;
            break;
        }
        backedge(ctx);
        // 0x001726dc
        charge(ctx, 8);
        v0 = addiu(s0, -1);
        s3 = addu(v0, s2);
        a0 = addu(v0, s1);
        jal(ctx, 0x1726E8u, gen::fn_MT_Misc_BitChk_003951d0);  // ready?
        v1 = 1;
        if (v0 == v1) {
            // 0x001726fc
            charge(ctx, 5);
            a0 = s3;
            jal(ctx, 0x172700u, gen::fn_MT_Misc_BitChk_003951d0);  // seen?
            if (v0 == 0) {
                // 0x00172710: ready and not seen
                charge(ctx, 3);
                v0 = 1;
                break;
            }
        }
        // 0x0017271c
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00172730 (the shared epilogue)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0016DD50 sub_16DD50 [datGetMoney] -- 16 bytes; leaf frame (no stack)
// sub_16DD50(): the s32 money (gGlobalWork +0x44DC).
void sub_16DD50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0016dd50
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x840000;
    lw(v0, v0, -22820);  // kMoney (gGlobalWork +0x44DC)
}

// 0x0016DD60 sub_16DD60 [datGetPartyMember] -- 28 bytes; leaf frame (no stack)
// sub_16DD60(i): party slot i's s16 pc id (gGlobalWork +0x44E0 [i]; 0 = empty).
void sub_16DD60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0016dd60
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = sll(a0, 1);
    v0 = 0x840000;
    v0 = addiu(v0, -22816);  // &kParty (gGlobalWork +0x44E0)
    v0 = addu(v0, v1);
    lh(v0, v0, 0);
}

// 0x0016E930 sub_16E930 [datSetMoney] -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_16E930(value): money = value; K_Assert line 1674 unless value < 10,000,000 (unsigned).
void sub_16E930(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016e930
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    at = 0x980000;
    at = at | 0x9680;  // 10,000,000 (the money limit)
    at = sltu(s0, at);
    if (at == 0) {
        // 0x0016e954
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 1674;
        jal(ctx, 0x16E960u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1674): returns
    }
    // 0x0016e968 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v1 = 0x840000;
    sw(s0, v1, -22820);  // kMoney (gGlobalWork +0x44DC)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0016E990 sub_16E990 [datSetPartyMember] -- 28 bytes; leaf frame (no stack)
// sub_16E990(i, pc): party slot i = pc (s16 gGlobalWork +0x44E0 [i]).
void sub_16E990(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016e990
    enter(ctx, 7);  // entry check point + this block's cycles
    a0 = sll(a0, 1);
    v1 = 0x840000;
    v1 = addiu(v1, -22816);  // &kParty (gGlobalWork +0x44E0)
    v1 = addu(v1, a0);
    sh(a1, v1, 0);
}

// 0x0016E9B0 sub_16E9B0 [datAddMoney] -- 144 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_16E9B0(delta): money += delta clamped to 0..9,999,999, stored through sub_16E930's check (K_Assert line 1674);
// returns the new money.
void sub_16E9B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016e9b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = 0x840000;
    lw(v0, v0, -22820);  // kMoney (gGlobalWork +0x44DC)
    s0 = addu(a0, v0);
    at = 0x980000;
    at = at | 0x9680;  // 10,000,000 (the money limit)
    at = slt(s0, at);
    if (at != 0) {
        // 0x0016e9ec
        charge(ctx, 2);
        if (i64(s0) < 0) {
            // 0x0016e9f4
            charge(ctx, 1);
            s0 = 0;
        }
    } else {
        // 0x0016e9dc
        charge(ctx, 4);
        v0 = 0x980000;
        s0 = v0 | 0x967F;  // 9,999,999 (the money cap)
    }
    // 0x0016e9f8
    charge(ctx, 5);
    at = 0x980000;
    at = at | 0x9680;  // 10,000,000 (the money limit)
    at = sltu(s0, at);
    if (at == 0) {
        // 0x0016ea0c
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 1674;
        jal(ctx, 0x16EA18u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1674): returns
    }
    // 0x0016ea20 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 0x840000;
    sw(s0, v0, -22820);  // kMoney (gGlobalWork +0x44DC)
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0016EA40 sub_16EA40 [datCheckMoneyDelta] -- 60 bytes; leaf frame (no stack)
// sub_16EA40(delta): where money + delta falls: 1 at or over 10,000,000, -1 below 0, else 0.
void sub_16EA40(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4};
    // 0x0016ea40
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 0x840000;
    lw(v0, v0, -22820);  // kMoney (gGlobalWork +0x44DC)
    v0 = addu(a0, v0);
    at = 0x980000;
    at = at | 0x9680;  // 10,000,000 (the money limit)
    at = slt(v0, at);
    if (at != 0) {
        // 0x0016ea6c
        charge(ctx, 2);
        v0 = slt(v0, 0);
        v0 = subu(0, v0);
    } else {
        // 0x0016ea60
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0016ea74 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016DDD0 sub_16DDD0 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_16DDD0(i): kCounter8[i] += 1 capped at 200 (u8[8] at gGlobalWork +0x573); K_Assert line 1257 unless i < 8.
void sub_16DDD0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016ddd0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    // K_Assert(line 1257) unless 0 <= i < 8
    at = slti(s0, 8);
    bool in_range = false;
    if (at != 0) {
        // 0x0016ddec
        charge(ctx, 2);
        in_range = i64(s0) >= 0;
    }
    if (!in_range) {
        // 0x0016ddf4
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 1257;
        jal(ctx, 0x16DE00u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1257): returns
    }
    // 0x0016de08: kCounter8[i] = min(kCounter8[i] + 1, 200)
    charge(ctx, 7);
    v1 = 0x830000;
    v1 = addiu(v1, 26483);  // &kCounter8 (gGlobalWork +0x573)
    a0 = addu(v1, s0);
    lbu(v1, a0, 0);
    at = slti(v1, 200);
    if (at == 0) {
        // 0x0016de34
        charge(ctx, 2);
        v1 = 200;
        sb(v1, a0, 0);
    } else {
        // 0x0016de24
        charge(ctx, 4);
        v1 = addiu(v1, 1);
        sb(v1, a0, 0);
    }
    // 0x0016de3c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0016DE50 sub_16DE50 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_16DE50(i): kCounter8[i] (u8 gGlobalWork +0x573 [i]); K_Assert line 1290 unless i < 8.
void sub_16DE50(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016de50
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    // K_Assert(line 1290) unless 0 <= i < 8
    at = slti(s0, 8);
    bool in_range = false;
    if (at != 0) {
        // 0x0016de6c
        charge(ctx, 2);
        in_range = i64(s0) >= 0;
    }
    if (!in_range) {
        // 0x0016de74
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 1290;
        jal(ctx, 0x16DE80u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1290): returns
    }
    // 0x0016de88: return kCounter8[i] (the shared epilogue)
    charge(ctx, 9);
    v0 = 0x830000;
    v0 = addiu(v0, 26483);  // &kCounter8 (gGlobalWork +0x573)
    v0 = addu(v0, s0);
    lbu(v0, v0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0016F490 sub_16F490 [datCountEquipmentEntries] -- 408 bytes; leaf frame (no stack)
// sub_16F490(owner): the number of used 20-byte equipment entries (u16 id != 0) of owner: -1 the 20 at 0x833E80, 1 the
// hero's 300 (*gGlobalWork +0x594), < 256 a member's 4 (record +0x5C), else the 4 at record (owner - 256) +0x180.
void sub_16F490(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0016f490
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0;
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = si(-1);
    if (a0 != v1) {
        // 0x0016f4f4
        charge(ctx, 3);
        v1 = 1;
        if (a0 != v1) {
            // 0x0016f54c
            charge(ctx, 3);
            v1 = slti(a0, 256);
            if (v1 != 0) {
                // 0x0016f5c4
                charge(ctx, 11);
                a1 = 0;
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x830000;
                v1 = addiu(v1, 16400);  // &kPartyRecords (pc 2's record)
                a0 = addu(v1, a0);
                for (;;) {
                    // 0x0016f614
                    charge(ctx, 3);
                    v1 = slti(a1, 4);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0016f5f0
                    charge(ctx, 7);
                    v1 = sll(a1, 2);
                    v1 = addu(v1, a1);
                    v1 = sll(v1, 2);
                    v1 = addu(a0, v1);
                    lhu(v1, v1, -1644);
                    if (v1 != 0) {
                        // 0x0016f60c
                        charge(ctx, 1);
                        v0 = addiu(v0, 1);
                    }
                    // 0x0016f610
                    charge(ctx, 1);
                    a1 = addiu(a1, 1);
                }
            } else {
                // 0x0016f558
                charge(ctx, 11);
                a2 = 0;
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x830000;
                v1 = addiu(v1, 16400);  // &kPartyRecords (pc 2's record)
                a1 = addu(v1, a0);
                for (;;) {
                    // 0x0016f5b0
                    charge(ctx, 3);
                    v1 = slti(a2, 4);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0016f584
                    charge(ctx, 9);
                    v1 = sll(a2, 2);
                    v1 = addu(v1, a2);
                    v1 = sll(v1, 2);
                    a0 = addu(a1, v1);
                    v1 = lui(0xFFFD);
                    v1 = addu(a0, v1);
                    lhu(v1, v1, -26952);
                    if (v1 != 0) {
                        // 0x0016f5a8
                        charge(ctx, 1);
                        v0 = addiu(v0, 1);
                    }
                    // 0x0016f5ac
                    charge(ctx, 1);
                    a2 = addiu(a2, 1);
                }
                // 0x0016f5bc
                charge(ctx, 2);
            }
        } else {
            // 0x0016f500
            charge(ctx, 5);
            a1 = 0;
            v1 = 0x830000;
            lw(a0, v1, 26516);  // kHeroEquipmentStock (gGlobalWork +0x594): EquipEntry[300]*
            for (;;) {
                // 0x0016f538
                charge(ctx, 3);
                v1 = slti(a1, 300);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0016f514
                charge(ctx, 7);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(a0, v1);
                lhu(v1, v1, 0);
                if (v1 != 0) {
                    // 0x0016f530
                    charge(ctx, 1);
                    v0 = addiu(v0, 1);
                }
                // 0x0016f534
                charge(ctx, 1);
                a1 = addiu(a1, 1);
            }
            // 0x0016f544
            charge(ctx, 2);
        }
    } else {
        // 0x0016f4a8
        charge(ctx, 5);
        a1 = 0;
        a0 = 0x830000;
        a0 = addiu(a0, 16000);  // &kTempEquipment (owner -1, 20 entries)
        for (;;) {
            // 0x0016f4e0
            charge(ctx, 3);
            v1 = slti(a1, 20);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0016f4bc
            charge(ctx, 7);
            v1 = sll(a1, 2);
            v1 = addu(v1, a1);
            v1 = sll(v1, 2);
            v1 = addu(a0, v1);
            lhu(v1, v1, 0);
            if (v1 != 0) {
                // 0x0016f4d8
                charge(ctx, 1);
                v0 = addiu(v0, 1);
            }
            // 0x0016f4dc
            charge(ctx, 1);
            a1 = addiu(a1, 1);
        }
        // 0x0016f4ec
        charge(ctx, 2);
    }
    // 0x0016f620 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016F720 sub_16F720 -- 236 bytes; leaf frame (no stack)
// sub_16F720(owner, idx): equipment entry idx of owner: the s32 at +4 (owner -1 / hero / member / owner >= 256 as
// sub_16F630).
void sub_16F720(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016f720
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x0016f758
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x0016f788
            charge(ctx, 3);
            v0 = slti(v1, 256);
            if (v0 != 0) {
                // 0x0016f7d0
                charge(ctx, 13);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 14760);  // &records[0].equipment[0] +4
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
            } else {
                // 0x0016f794
                charge(ctx, 15);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x800000;
                v0 = addiu(v0, -10548);  // &records[0].equipment2[0] +4 - 256 * 868
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
            }
        } else {
            // 0x0016f764
            charge(ctx, 9);
            v0 = 0x830000;
            lw(v1, v0, 26516);  // kHeroEquipmentStock (gGlobalWork +0x594): EquipEntry[300]*
            v0 = sll(a1, 2);
            v0 = addu(v0, a1);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 4);
        }
    } else {
        // 0x0016f734
        charge(ctx, 9);
        v0 = sll(a1, 2);
        v0 = addu(v0, a1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16004);  // &kTempEquipment[0] +4
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
    }
    // 0x0016f804 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016F810 sub_16F810 -- 236 bytes; leaf frame (no stack)
// sub_16F810(owner, idx): equipment entry idx of owner: the u8 at +8.
void sub_16F810(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016f810
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x0016f848
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x0016f878
            charge(ctx, 3);
            v0 = slti(v1, 256);
            if (v0 != 0) {
                // 0x0016f8c0
                charge(ctx, 13);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 14764);  // &records[0].equipment[0] +8
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lbu(v0, v0, 0);
            } else {
                // 0x0016f884
                charge(ctx, 15);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x800000;
                v0 = addiu(v0, -10544);  // &records[0].equipment2[0] +8 - 256 * 868
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lbu(v0, v0, 0);
            }
        } else {
            // 0x0016f854
            charge(ctx, 9);
            v0 = 0x830000;
            lw(v1, v0, 26516);  // kHeroEquipmentStock (gGlobalWork +0x594): EquipEntry[300]*
            v0 = sll(a1, 2);
            v0 = addu(v0, a1);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lbu(v0, v0, 8);
        }
    } else {
        // 0x0016f824
        charge(ctx, 9);
        v0 = sll(a1, 2);
        v0 = addu(v0, a1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16008);  // &kTempEquipment[0] +8
        v0 = addu(v0, v1);
        lbu(v0, v0, 0);
    }
    // 0x0016f8f4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016F9F0 sub_16F9F0 [datGetEquipmentPower] -- 236 bytes; leaf frame (no stack)
// sub_16F9F0(owner, idx): equipment entry idx of owner: u16 +0xA, the weapon power (datCalcGetWeaponParam's 0).
void sub_16F9F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016f9f0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x0016fa28
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x0016fa58
            charge(ctx, 3);
            v0 = slti(v1, 256);
            if (v0 != 0) {
                // 0x0016faa0
                charge(ctx, 13);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 14766);  // &records[0].equipment[0].power
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lhu(v0, v0, 0);
            } else {
                // 0x0016fa64
                charge(ctx, 15);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x800000;
                v0 = addiu(v0, -10542);  // &records[0].equipment2[0].power - 256 * 868
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lhu(v0, v0, 0);
            }
        } else {
            // 0x0016fa34
            charge(ctx, 9);
            v0 = 0x830000;
            lw(v1, v0, 26516);  // kHeroEquipmentStock (gGlobalWork +0x594): EquipEntry[300]*
            v0 = sll(a1, 2);
            v0 = addu(v0, a1);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lhu(v0, v0, 10);
        }
    } else {
        // 0x0016fa04
        charge(ctx, 9);
        v0 = sll(a1, 2);
        v0 = addu(v0, a1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16010);  // &kTempEquipment[0].power
        v0 = addu(v0, v1);
        lhu(v0, v0, 0);
    }
    // 0x0016fad4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016FAE0 sub_16FAE0 [datGetEquipmentAccuracy] -- 236 bytes; leaf frame (no stack)
// sub_16FAE0(owner, idx): equipment entry idx of owner: u16 +0xC, the weapon accuracy (datCalcGetWeaponParam's 1).
void sub_16FAE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016fae0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x0016fb18
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x0016fb48
            charge(ctx, 3);
            v0 = slti(v1, 256);
            if (v0 != 0) {
                // 0x0016fb90
                charge(ctx, 13);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 14768);  // &records[0].equipment[0].accuracy
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lhu(v0, v0, 0);
            } else {
                // 0x0016fb54
                charge(ctx, 15);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x800000;
                v0 = addiu(v0, -10540);  // &records[0].equipment2[0].accuracy - 256 * 868
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lhu(v0, v0, 0);
            }
        } else {
            // 0x0016fb24
            charge(ctx, 9);
            v0 = 0x830000;
            lw(v1, v0, 26516);  // kHeroEquipmentStock (gGlobalWork +0x594): EquipEntry[300]*
            v0 = sll(a1, 2);
            v0 = addu(v0, a1);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lhu(v0, v0, 12);
        }
    } else {
        // 0x0016faf4
        charge(ctx, 9);
        v0 = sll(a1, 2);
        v0 = addu(v0, a1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16012);  // &kTempEquipment[0].accuracy
        v0 = addu(v0, v1);
        lhu(v0, v0, 0);
    }
    // 0x0016fbc4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016FBD0 sub_16FBD0 [datGetEquipmentEvasion] -- 236 bytes; leaf frame (no stack)
// sub_16FBD0(owner, idx): equipment entry idx of owner: u16 +0xE, the armour evasion (datCalcGetArmorParam).
void sub_16FBD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016fbd0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x0016fc08
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x0016fc38
            charge(ctx, 3);
            v0 = slti(v1, 256);
            if (v0 != 0) {
                // 0x0016fc80
                charge(ctx, 13);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 14770);  // &records[0].equipment[0].evasion
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lhu(v0, v0, 0);
            } else {
                // 0x0016fc44
                charge(ctx, 15);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x800000;
                v0 = addiu(v0, -10538);  // &records[0].equipment2[0].evasion - 256 * 868
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lhu(v0, v0, 0);
            }
        } else {
            // 0x0016fc14
            charge(ctx, 9);
            v0 = 0x830000;
            lw(v1, v0, 26516);  // kHeroEquipmentStock (gGlobalWork +0x594): EquipEntry[300]*
            v0 = sll(a1, 2);
            v0 = addu(v0, a1);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lhu(v0, v0, 14);
        }
    } else {
        // 0x0016fbe4
        charge(ctx, 9);
        v0 = sll(a1, 2);
        v0 = addu(v0, a1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16014);  // &kTempEquipment[0].evasion
        v0 = addu(v0, v1);
        lhu(v0, v0, 0);
    }
    // 0x0016fcb4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016FCC0 sub_16FCC0 [datGetEquipmentDefense] -- 236 bytes; leaf frame (no stack)
// sub_16FCC0(owner, idx): equipment entry idx of owner: u16 +0x10, the armour defense (datCalcGetArmorParam).
void sub_16FCC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016fcc0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x0016fcf8
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x0016fd28
            charge(ctx, 3);
            v0 = slti(v1, 256);
            if (v0 != 0) {
                // 0x0016fd70
                charge(ctx, 13);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 14772);  // &records[0].equipment[0].defense
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lhu(v0, v0, 0);
            } else {
                // 0x0016fd34
                charge(ctx, 15);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x800000;
                v0 = addiu(v0, -10536);  // &records[0].equipment2[0].defense - 256 * 868
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lhu(v0, v0, 0);
            }
        } else {
            // 0x0016fd04
            charge(ctx, 9);
            v0 = 0x830000;
            lw(v1, v0, 26516);  // kHeroEquipmentStock (gGlobalWork +0x594): EquipEntry[300]*
            v0 = sll(a1, 2);
            v0 = addu(v0, a1);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lhu(v0, v0, 16);
        }
    } else {
        // 0x0016fcd4
        charge(ctx, 9);
        v0 = sll(a1, 2);
        v0 = addu(v0, a1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16016);  // &kTempEquipment[0].defense
        v0 = addu(v0, v1);
        lhu(v0, v0, 0);
    }
    // 0x0016fda4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016FDB0 sub_16FDB0 [datGetEquipmentEntry] -- 236 bytes; leaf frame (no stack)
// sub_16FDB0(owner, idx): the address of equipment entry idx of owner (-1 0x833E80, hero *gGlobalWork +0x594, member
// record +0x5C, owner >= 256 record +0x180).
void sub_16FDB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016fdb0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x0016fde4
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x0016fe10
            charge(ctx, 3);
            v0 = slti(v1, 256);
            if (v0 != 0) {
                // 0x0016fe5c
                charge(ctx, 14);
                v1 = addiu(v1, -2);  // 868 * (pc - 2) = (((pc - 2) * 31) * 7) * 4:
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 16400);  // &kPartyRecords (pc 2's record)
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                v0 = addiu(v0, 92);
            } else {
                // 0x0016fe1c
                charge(ctx, 16);
                v1 = addiu(v1, -258);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 16400);  // &kPartyRecords (pc 2's record)
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                v0 = addiu(v0, 384);
            }
        } else {
            // 0x0016fdf0
            charge(ctx, 8);
            v0 = sll(a1, 2);
            v0 = addu(v0, a1);
            v1 = sll(v0, 2);
            v0 = 0x830000;
            lw(v0, v0, 26516);  // kHeroEquipmentStock (gGlobalWork +0x594): EquipEntry[300]*
            v0 = addu(v0, v1);
        }
    } else {
        // 0x0016fdc4
        charge(ctx, 8);
        v0 = sll(a1, 2);
        v0 = addu(v0, a1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16000);  // &kTempEquipment (owner -1, 20 entries)
        v0 = addu(v0, v1);
    }
    // 0x0016fe94 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016FEA0 sub_16FEA0 [datSetEquipmentItemId] -- 236 bytes; leaf frame (no stack)
// sub_16FEA0(owner, idx, value): equipment entry idx of owner: u16 item id (+0) = value.
void sub_16FEA0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0016fea0
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = si(-1);
    if (a0 != v1) {
        // 0x0016fed8
        charge(ctx, 3);
        v1 = 1;
        if (a0 != v1) {
            // 0x0016ff08
            charge(ctx, 3);
            v1 = slti(a0, 256);
            if (v1 != 0) {
                // 0x0016ff50
                charge(ctx, 13);
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x830000;
                v1 = addiu(v1, 14756);  // &records[0].equipment[0] (pc 0; + 868 pc)
                a0 = addu(v1, a0);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                sh(a2, v1, 0);
            } else {
                // 0x0016ff14
                charge(ctx, 15);
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x800000;
                v1 = addiu(v1, -10552);  // &records[0].equipment2[0] - 256 * 868 (owner >= 256)
                a0 = addu(v1, a0);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                sh(a2, v1, 0);
            }
        } else {
            // 0x0016fee4
            charge(ctx, 9);
            v1 = sll(a1, 2);
            v1 = addu(v1, a1);
            a0 = sll(v1, 2);
            v1 = 0x830000;
            lw(v1, v1, 26516);  // kHeroEquipmentStock (gGlobalWork +0x594): EquipEntry[300]*
            v1 = addu(v1, a0);
            sh(a2, v1, 0);
        }
    } else {
        // 0x0016feb4
        charge(ctx, 9);
        v1 = sll(a1, 2);
        v1 = addu(v1, a1);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 16000);  // &kTempEquipment (owner -1, 20 entries)
        v1 = addu(v1, a0);
        sh(a2, v1, 0);
    }
    // 0x0016ff84 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0016FF90 sub_16FF90 -- 236 bytes; leaf frame (no stack)
// sub_16FF90(owner, idx, value): equipment entry idx of owner: s32 +4 = value.
void sub_16FF90(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0016ff90
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = si(-1);
    if (a0 != v1) {
        // 0x0016ffc8
        charge(ctx, 3);
        v1 = 1;
        if (a0 != v1) {
            // 0x0016fff8
            charge(ctx, 3);
            v1 = slti(a0, 256);
            if (v1 != 0) {
                // 0x00170040
                charge(ctx, 13);
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x830000;
                v1 = addiu(v1, 14760);  // &records[0].equipment[0] +4
                a0 = addu(v1, a0);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                sw(a2, v1, 0);
            } else {
                // 0x00170004
                charge(ctx, 15);
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x800000;
                v1 = addiu(v1, -10548);  // &records[0].equipment2[0] +4 - 256 * 868
                a0 = addu(v1, a0);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                sw(a2, v1, 0);
            }
        } else {
            // 0x0016ffd4
            charge(ctx, 9);
            v1 = 0x830000;
            lw(a0, v1, 26516);  // kHeroEquipmentStock (gGlobalWork +0x594): EquipEntry[300]*
            v1 = sll(a1, 2);
            v1 = addu(v1, a1);
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            sw(a2, v1, 4);
        }
    } else {
        // 0x0016ffa4
        charge(ctx, 9);
        v1 = sll(a1, 2);
        v1 = addu(v1, a1);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 16004);  // &kTempEquipment[0] +4
        v1 = addu(v1, a0);
        sw(a2, v1, 0);
    }
    // 0x00170074 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00170080 sub_170080 -- 236 bytes; leaf frame (no stack)
// sub_170080(owner, idx, value): equipment entry idx of owner: u8 +8 = value.
void sub_170080(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00170080
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = si(-1);
    if (a0 != v1) {
        // 0x001700b8
        charge(ctx, 3);
        v1 = 1;
        if (a0 != v1) {
            // 0x001700e8
            charge(ctx, 3);
            v1 = slti(a0, 256);
            if (v1 != 0) {
                // 0x00170130
                charge(ctx, 13);
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x830000;
                v1 = addiu(v1, 14764);  // &records[0].equipment[0] +8
                a0 = addu(v1, a0);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                sb(a2, v1, 0);
            } else {
                // 0x001700f4
                charge(ctx, 15);
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x800000;
                v1 = addiu(v1, -10544);  // &records[0].equipment2[0] +8 - 256 * 868
                a0 = addu(v1, a0);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                sb(a2, v1, 0);
            }
        } else {
            // 0x001700c4
            charge(ctx, 9);
            v1 = 0x830000;
            lw(a0, v1, 26516);  // kHeroEquipmentStock (gGlobalWork +0x594): EquipEntry[300]*
            v1 = sll(a1, 2);
            v1 = addu(v1, a1);
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            sb(a2, v1, 8);
        }
    } else {
        // 0x00170094
        charge(ctx, 9);
        v1 = sll(a1, 2);
        v1 = addu(v1, a1);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 16008);  // &kTempEquipment[0] +8
        v1 = addu(v1, a0);
        sb(a2, v1, 0);
    }
    // 0x00170164 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00170170 sub_170170 [datSetEquipmentEffect] -- 236 bytes; leaf frame (no stack)
// sub_170170(owner, idx, value): equipment entry idx of owner: u8 effect (+9) = value.
void sub_170170(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00170170
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = si(-1);
    if (a0 != v1) {
        // 0x001701a8
        charge(ctx, 3);
        v1 = 1;
        if (a0 != v1) {
            // 0x001701d8
            charge(ctx, 3);
            v1 = slti(a0, 256);
            if (v1 != 0) {
                // 0x00170220
                charge(ctx, 13);
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x830000;
                v1 = addiu(v1, 14765);  // &records[0].equipment[0].effect
                a0 = addu(v1, a0);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                sb(a2, v1, 0);
            } else {
                // 0x001701e4
                charge(ctx, 15);
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x800000;
                v1 = addiu(v1, -10543);  // &records[0].equipment2[0].effect - 256 * 868
                a0 = addu(v1, a0);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                sb(a2, v1, 0);
            }
        } else {
            // 0x001701b4
            charge(ctx, 9);
            v1 = 0x830000;
            lw(a0, v1, 26516);  // kHeroEquipmentStock (gGlobalWork +0x594): EquipEntry[300]*
            v1 = sll(a1, 2);
            v1 = addu(v1, a1);
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            sb(a2, v1, 9);
        }
    } else {
        // 0x00170184
        charge(ctx, 9);
        v1 = sll(a1, 2);
        v1 = addu(v1, a1);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 16009);  // &kTempEquipment[0].effect
        v1 = addu(v1, a0);
        sb(a2, v1, 0);
    }
    // 0x00170254 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00170260 sub_170260 [datSetEquipmentPower] -- 236 bytes; leaf frame (no stack)
// sub_170260(owner, idx, value): equipment entry idx of owner: u16 power (+0xA) = value.
void sub_170260(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00170260
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = si(-1);
    if (a0 != v1) {
        // 0x00170298
        charge(ctx, 3);
        v1 = 1;
        if (a0 != v1) {
            // 0x001702c8
            charge(ctx, 3);
            v1 = slti(a0, 256);
            if (v1 != 0) {
                // 0x00170310
                charge(ctx, 13);
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x830000;
                v1 = addiu(v1, 14766);  // &records[0].equipment[0].power
                a0 = addu(v1, a0);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                sh(a2, v1, 0);
            } else {
                // 0x001702d4
                charge(ctx, 15);
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x800000;
                v1 = addiu(v1, -10542);  // &records[0].equipment2[0].power - 256 * 868
                a0 = addu(v1, a0);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                sh(a2, v1, 0);
            }
        } else {
            // 0x001702a4
            charge(ctx, 9);
            v1 = 0x830000;
            lw(a0, v1, 26516);  // kHeroEquipmentStock (gGlobalWork +0x594): EquipEntry[300]*
            v1 = sll(a1, 2);
            v1 = addu(v1, a1);
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            sh(a2, v1, 10);
        }
    } else {
        // 0x00170274
        charge(ctx, 9);
        v1 = sll(a1, 2);
        v1 = addu(v1, a1);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 16010);  // &kTempEquipment[0].power
        v1 = addu(v1, a0);
        sh(a2, v1, 0);
    }
    // 0x00170344 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00170350 sub_170350 [datSetEquipmentAccuracy] -- 236 bytes; leaf frame (no stack)
// sub_170350(owner, idx, value): equipment entry idx of owner: u16 accuracy (+0xC) = value.
void sub_170350(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00170350
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = si(-1);
    if (a0 != v1) {
        // 0x00170388
        charge(ctx, 3);
        v1 = 1;
        if (a0 != v1) {
            // 0x001703b8
            charge(ctx, 3);
            v1 = slti(a0, 256);
            if (v1 != 0) {
                // 0x00170400
                charge(ctx, 13);
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x830000;
                v1 = addiu(v1, 14768);  // &records[0].equipment[0].accuracy
                a0 = addu(v1, a0);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                sh(a2, v1, 0);
            } else {
                // 0x001703c4
                charge(ctx, 15);
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x800000;
                v1 = addiu(v1, -10540);  // &records[0].equipment2[0].accuracy - 256 * 868
                a0 = addu(v1, a0);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                sh(a2, v1, 0);
            }
        } else {
            // 0x00170394
            charge(ctx, 9);
            v1 = 0x830000;
            lw(a0, v1, 26516);  // kHeroEquipmentStock (gGlobalWork +0x594): EquipEntry[300]*
            v1 = sll(a1, 2);
            v1 = addu(v1, a1);
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            sh(a2, v1, 12);
        }
    } else {
        // 0x00170364
        charge(ctx, 9);
        v1 = sll(a1, 2);
        v1 = addu(v1, a1);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 16012);  // &kTempEquipment[0].accuracy
        v1 = addu(v1, a0);
        sh(a2, v1, 0);
    }
    // 0x00170434 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00170440 sub_170440 [datSetEquipmentEvasion] -- 236 bytes; leaf frame (no stack)
// sub_170440(owner, idx, value): equipment entry idx of owner: u16 evasion (+0xE) = value.
void sub_170440(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00170440
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = si(-1);
    if (a0 != v1) {
        // 0x00170478
        charge(ctx, 3);
        v1 = 1;
        if (a0 != v1) {
            // 0x001704a8
            charge(ctx, 3);
            v1 = slti(a0, 256);
            if (v1 != 0) {
                // 0x001704f0
                charge(ctx, 13);
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x830000;
                v1 = addiu(v1, 14770);  // &records[0].equipment[0].evasion
                a0 = addu(v1, a0);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                sh(a2, v1, 0);
            } else {
                // 0x001704b4
                charge(ctx, 15);
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x800000;
                v1 = addiu(v1, -10538);  // &records[0].equipment2[0].evasion - 256 * 868
                a0 = addu(v1, a0);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                sh(a2, v1, 0);
            }
        } else {
            // 0x00170484
            charge(ctx, 9);
            v1 = 0x830000;
            lw(a0, v1, 26516);  // kHeroEquipmentStock (gGlobalWork +0x594): EquipEntry[300]*
            v1 = sll(a1, 2);
            v1 = addu(v1, a1);
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            sh(a2, v1, 14);
        }
    } else {
        // 0x00170454
        charge(ctx, 9);
        v1 = sll(a1, 2);
        v1 = addu(v1, a1);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 16014);  // &kTempEquipment[0].evasion
        v1 = addu(v1, a0);
        sh(a2, v1, 0);
    }
    // 0x00170524 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00170530 sub_170530 [datSetEquipmentDefense] -- 236 bytes; leaf frame (no stack)
// sub_170530(owner, idx, value): equipment entry idx of owner: u16 defense (+0x10) = value.
void sub_170530(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00170530
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = si(-1);
    if (a0 != v1) {
        // 0x00170568
        charge(ctx, 3);
        v1 = 1;
        if (a0 != v1) {
            // 0x00170598
            charge(ctx, 3);
            v1 = slti(a0, 256);
            if (v1 != 0) {
                // 0x001705e0
                charge(ctx, 13);
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x830000;
                v1 = addiu(v1, 14772);  // &records[0].equipment[0].defense
                a0 = addu(v1, a0);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                sh(a2, v1, 0);
            } else {
                // 0x001705a4
                charge(ctx, 15);
                v1 = sll(a0, 5);
                a0 = subu(v1, a0);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 2);
                v1 = 0x800000;
                v1 = addiu(v1, -10536);  // &records[0].equipment2[0].defense - 256 * 868
                a0 = addu(v1, a0);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                sh(a2, v1, 0);
            }
        } else {
            // 0x00170574
            charge(ctx, 9);
            v1 = 0x830000;
            lw(a0, v1, 26516);  // kHeroEquipmentStock (gGlobalWork +0x594): EquipEntry[300]*
            v1 = sll(a1, 2);
            v1 = addu(v1, a1);
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            sh(a2, v1, 16);
        }
    } else {
        // 0x00170544
        charge(ctx, 9);
        v1 = sll(a1, 2);
        v1 = addu(v1, a1);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 16016);  // &kTempEquipment[0].defense
        v1 = addu(v1, a0);
        sh(a2, v1, 0);
    }
    // 0x00170614 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00170620 sub_170620 -- 72 bytes; leaf frame (no stack)
// sub_170620(pc, i): the address record(pc) + 0x5C + 4 i (a word of the member's equipment entries; callers sub_17FD30
// / sub_17FE10).
void sub_170620(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00170620
    enter(ctx, 18);  // entry check point + this block's cycles
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v1 = addiu(v0, -2);
    v0 = sll(v1, 5);
    v1 = subu(v0, v1);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 2);
    v0 = 0x830000;
    v0 = addiu(v0, 16400);  // &kPartyRecords (pc 2's record)
    v1 = addu(v0, v1);
    v0 = dsll32(a1, 16);
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    v0 = addiu(v0, 172);
}

// 0x00170670 sub_170670 -- 68 bytes; leaf frame (no stack)
// sub_170670(pc, i): the u16 at record(pc) +0xAC + 4 i (the first half of a {u16, u16} pair; callers in the battle
// band).
void sub_170670(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00170670
    enter(ctx, 17);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = sll(v1, 5);
    v1 = subu(v0, v1);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 2);
    v0 = 0x830000;
    v0 = addiu(v0, 14836);  // &records[0] +0xAC pairs (pc 0; + 868 pc)
    v1 = addu(v0, v1);
    v0 = dsll32(a1, 16);
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lhu(v0, v0, 0);
}

// 0x001706C0 sub_1706C0 -- 68 bytes; leaf frame (no stack)
// sub_1706C0(pc, i): the s16 at record(pc) +0xAE + 4 i (the second half of the pair).
void sub_1706C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001706c0
    enter(ctx, 17);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = sll(v1, 5);
    v1 = subu(v0, v1);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 2);
    v0 = 0x830000;
    v0 = addiu(v0, 14838);  // &records[0] +0xAE (pc 0; + 868 pc)
    v1 = addu(v0, v1);
    v0 = dsll32(a1, 16);
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lh(v0, v0, 0);
}

// 0x00170710 sub_170710 -- 68 bytes; leaf frame (no stack)
// sub_170710(pc, i, value): the s16 at record(pc) +0xAE + 4 i = value.
void sub_170710(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00170710
    enter(ctx, 17);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = sll(a0, 5);
    a0 = subu(v1, a0);
    v1 = sll(a0, 3);
    v1 = subu(v1, a0);
    a0 = sll(v1, 2);
    v1 = 0x830000;
    v1 = addiu(v1, 14838);  // &records[0] +0xAE (pc 0; + 868 pc)
    a0 = addu(v1, a0);
    v1 = dsll32(a1, 16);
    v1 = dsra32(v1, 16);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    sh(a2, v1, 0);
}

// 0x00170A40 sub_170A40 [datGetPouchItemId] -- 100 bytes; leaf frame (no stack)
// sub_170A40(pc, i): member pc's pouch slot i: the u16 item id at record +0x310 + 4 i (pc >= 256 counts as pc - 256).
void sub_170A40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00170a40
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v0 = slti(v0, 256);
    if (v0 == 0) {
        // 0x00170a54
        charge(ctx, 3);
        v0 = addiu(a0, -256);
        a0 = dsll32(v0, 16);
        a0 = dsra32(a0, 16);
    }
    // 0x00170a60 (the shared epilogue, written out on this path)
    charge(ctx, 17);
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = sll(v1, 5);
    v1 = subu(v0, v1);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 2);
    v0 = 0x830000;
    v0 = addiu(v0, 15448);  // &records[0].pouch[0].id (pc 0; + 868 pc)
    v1 = addu(v0, v1);
    v0 = dsll32(a1, 16);
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lhu(v0, v0, 0);
}

// 0x00170AB0 sub_170AB0 [datGetPouchItemNum] -- 100 bytes; leaf frame (no stack)
// sub_170AB0(pc, i): member pc's pouch slot i: the s16 count at record +0x312 + 4 i.
void sub_170AB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00170ab0
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v0 = slti(v0, 256);
    if (v0 == 0) {
        // 0x00170ac4
        charge(ctx, 3);
        v0 = addiu(a0, -256);
        a0 = dsll32(v0, 16);
        a0 = dsra32(a0, 16);
    }
    // 0x00170ad0 (the shared epilogue, written out on this path)
    charge(ctx, 17);
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = sll(v1, 5);
    v1 = subu(v0, v1);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 2);
    v0 = 0x830000;
    v0 = addiu(v0, 15450);  // &records[0].pouch[0].num (pc 0; + 868 pc)
    v1 = addu(v0, v1);
    v0 = dsll32(a1, 16);
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lh(v0, v0, 0);
}

// 0x00170B20 sub_170B20 [datSetPouchItemId] -- 100 bytes; leaf frame (no stack)
// sub_170B20(pc, i, value): member pc's pouch slot i: item id = value.
void sub_170B20(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00170b20
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v1 = slti(v1, 256);
    if (v1 == 0) {
        // 0x00170b34
        charge(ctx, 3);
        v1 = addiu(a0, -256);
        a0 = dsll32(v1, 16);
        a0 = dsra32(a0, 16);
    }
    // 0x00170b40 (the shared epilogue, written out on this path)
    charge(ctx, 17);
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = sll(a0, 5);
    a0 = subu(v1, a0);
    v1 = sll(a0, 3);
    v1 = subu(v1, a0);
    a0 = sll(v1, 2);
    v1 = 0x830000;
    v1 = addiu(v1, 15448);  // &records[0].pouch[0].id (pc 0; + 868 pc)
    a0 = addu(v1, a0);
    v1 = dsll32(a1, 16);
    v1 = dsra32(v1, 16);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    sh(a2, v1, 0);
}

// 0x00170B90 sub_170B90 [datSetPouchItemNum] -- 100 bytes; leaf frame (no stack)
// sub_170B90(pc, i, value): member pc's pouch slot i: count = value.
void sub_170B90(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00170b90
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v1 = slti(v1, 256);
    if (v1 == 0) {
        // 0x00170ba4
        charge(ctx, 3);
        v1 = addiu(a0, -256);
        a0 = dsll32(v1, 16);
        a0 = dsra32(a0, 16);
    }
    // 0x00170bb0 (the shared epilogue, written out on this path)
    charge(ctx, 17);
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = sll(a0, 5);
    a0 = subu(v1, a0);
    v1 = sll(a0, 3);
    v1 = subu(v1, a0);
    a0 = sll(v1, 2);
    v1 = 0x830000;
    v1 = addiu(v1, 15450);  // &records[0].pouch[0].num (pc 0; + 868 pc)
    a0 = addu(v1, a0);
    v1 = dsll32(a1, 16);
    v1 = dsra32(v1, 16);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    sh(a2, v1, 0);
}

// 0x00170760 sub_170760 [datGetItemNum] -- 256 bytes; leaf frame (no stack)
// sub_170760(owner, id): how many of item id (>= 4000) owner holds: the hero's u16 count table (*gGlobalWork +0x598)[id
// - 4000], owner -1 the u16 table 0x831CE0 [id], a member (< 256) none, owner >= 256 the pouch of record (owner - 256)
// +0x310 when an entry's id equals owner (the original compares with the owner, not the item).
void sub_170760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00170760
    enter(ctx, 5);  // entry check point + this block's cycles
    a3 = dsll32(a0, 16);
    a3 = dsra32(a3, 16);
    v0 = 1;
    if (a3 != v0) {
        // 0x00170798
        charge(ctx, 3);
        v0 = si(-1);
        if (a3 != v0) {
            // 0x001707c8
            charge(ctx, 3);
            v0 = slti(a3, 256);
            if (v0 != 0) {
                // 0x00170854
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x001707d4
                charge(ctx, 11);
                t0 = 0;
                v0 = sll(a3, 5);
                v1 = subu(v0, a3);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                a2 = sll(v0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 16400);  // &kPartyRecords (pc 2's record)
                a1 = addu(v0, a2);
                // a1 = kPartyRecords + 868 owner; a1 + 4 i + 0xFFFD0000 - 26552 = 0x7FD858 + 868 owner + 4 i, the pouch
                // entry i of record (owner - 256)
                for (;;) {
                    // 0x0017083c
                    charge(ctx, 3);
                    v0 = slti(t0, 20);
                    if (v0 == 0) {
                        // 0x00170848: no entry: 0
                        charge(ctx, 3);
                        v0 = 0;
                        break;
                    }
                    backedge(ctx);
                    // 0x00170800
                    charge(ctx, 7);
                    a0 = sll(t0, 2);
                    v1 = addu(a1, a0);
                    v0 = lui(0xFFFD);
                    v0 = addu(v1, v0);
                    lhu(v0, v0, -26552);  // pouch[i].id
                    if (a3 == v0) {
                        // 0x0017081c: the entry whose id equals the owner (sic): its count
                        charge(ctx, 7);
                        v0 = 0x800000;
                        v0 = addiu(v0, -10150);  // &records[0].pouch[0].num - 256 * 868 (owner >= 256)
                        v0 = addu(v0, a2);
                        v0 = addu(a0, v0);
                        lhu(v0, v0, 0);  // pouch[i].num
                        break;
                    }
                    // 0x00170838
                    charge(ctx, 1);
                    t0 = addiu(t0, 1);
                }
            }
        } else {
            // 0x001707a4
            charge(ctx, 9);
            v0 = dsll32(a1, 16);
            v0 = dsra32(v0, 16);
            v1 = sll(v0, 1);
            v0 = 0x830000;
            v0 = addiu(v0, 7392);  // &kTempItemNum (owner -1)
            v0 = addu(v0, v1);
            lhu(v0, v0, 0);
        }
    } else {
        // 0x00170774
        charge(ctx, 9);
        v0 = 0x830000;
        lw(v1, v0, 26520);  // kHeroItemNum (gGlobalWork +0x598): u16 counts, biased by item 4000
        v0 = dsll32(a1, 16);
        v0 = dsra32(v0, 16);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        lhu(v0, v0, -8000);  // kHeroItemNum[id - 4000]
    }
    // 0x00170858 (the shared epilogue)
    charge(ctx, 2);
}

// 0x00170860 sub_170860 [datSetItemNum] -- 476 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_170860(owner, id, count): sets owner's count of item id (K_Assert line 2341 unless count < 100): hero / owner -1
// tables as sub_170760; owner >= 256 the pouch entry whose id equals owner, else the first empty one (count 0 also
// clears the entry's id).
void sub_170860(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00170860
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = s1 & 0xFFFF;
    at = slti(s0, 100);
    if (at == 0) {
        // 0x00170894
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 2341;
        jal(ctx, 0x1708A0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2341): returns
    }
    // 0x001708a8
    charge(ctx, 5);
    a3 = dsll32(s3, 16);
    a3 = dsra32(a3, 16);
    v1 = 1;
    if (a3 != v1) {
        // 0x001708e0
        charge(ctx, 3);
        v1 = si(-1);
        if (a3 != v1) {
            // 0x00170910
            charge(ctx, 3);
            v1 = slti(a3, 256);
            if (v1 == 0) {
                // 0x0017091c
                charge(ctx, 11);
                t1 = 0;
                v1 = sll(a3, 5);
                a0 = subu(v1, a3);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a2 = sll(v1, 2);
                v1 = 0x830000;
                v1 = addiu(v1, 16400);  // &kPartyRecords (pc 2's record)
                t0 = addu(v1, a2);
                // the pouch of record (owner - 256) as in sub_170760: first the entry whose id equals the owner (sic),
                // else the first empty one; a1 = 4 * its index
                bool hit = false;
                for (;;) {
                    // 0x001709a0
                    charge(ctx, 3);
                    v1 = slti(t1, 20);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00170948
                    charge(ctx, 7);
                    a1 = sll(t1, 2);
                    a0 = addu(t0, a1);
                    v1 = lui(0xFFFD);
                    v1 = addu(a0, v1);
                    lhu(v1, v1, -26552);  // pouch[i].id
                    if (a3 == v1) {
                        hit = true;  // 0x00170964
                        break;
                    }
                    // 0x0017099c
                    charge(ctx, 1);
                    t1 = addiu(t1, 1);
                }
                if (!hit) {
                    // 0x001709ac
                    charge(ctx, 3);
                    a3 = 0;
                    for (;;) {
                        // 0x00170a10
                        charge(ctx, 3);
                        v1 = slti(a3, 20);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001709b8
                        charge(ctx, 7);
                        a1 = sll(a3, 2);
                        a0 = addu(t0, a1);
                        v1 = lui(0xFFFD);
                        v1 = addu(a0, v1);
                        lhu(v1, v1, -26552);  // pouch[i].id
                        if (v1 == 0) {
                            hit = true;  // 0x001709d4
                            break;
                        }
                        // 0x00170a0c
                        charge(ctx, 1);
                        a3 = addiu(a3, 1);
                    }
                }
                if (hit) {
                    // 0x00170964 / 0x001709d4 (the same block twice): pouch[i].num = count; count 0 also clears the id
                    charge(ctx, 7);
                    v1 = 0x800000;
                    v1 = addiu(v1, -10150);  // &records[0].pouch[0].num - 256 * 868 (owner >= 256)
                    v1 = addu(v1, a2);
                    v1 = addu(a1, v1);
                    sh(s1, v1, 0);
                    if (s0 == 0) {
                        // 0x00170980 / 0x001709f0
                        charge(ctx, 5);
                        v1 = 0x800000;
                        v1 = addiu(v1, -10152);  // &records[0].pouch[0].id - 256 * 868 (owner >= 256)
                        v1 = addu(v1, a2);
                        v1 = addu(a1, v1);
                        sh(zero, v1, 0);
                    }
                    // 0x00170994 / 0x00170a04
                    charge(ctx, 2);
                }
            }
        } else {
            // 0x001708ec
            charge(ctx, 9);
            v1 = dsll32(s2, 16);
            v1 = dsra32(v1, 16);
            a0 = sll(v1, 1);
            v1 = 0x830000;
            v1 = addiu(v1, 7392);  // &kTempItemNum (owner -1)
            v1 = addu(v1, a0);
            sh(s1, v1, 0);
        }
    } else {
        // 0x001708bc
        charge(ctx, 9);
        v1 = 0x830000;
        lw(a0, v1, 26520);  // kHeroItemNum (gGlobalWork +0x598): u16 counts, biased by item 4000
        v1 = dsll32(s2, 16);
        v1 = dsra32(v1, 16);
        v1 = sll(v1, 1);
        v1 = addu(v1, a0);
        sh(s1, v1, -8000);
    }
    // 0x00170a1c (the shared epilogue)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00170C00 sub_170C00 [datAddItemNum] -- 348 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_170C00(owner, id, delta): owner's count of item id += delta clamped to 0..99 (sub_170760's read inlined), stored
// with sub_170860; returns the new count.
void sub_170C00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00170c00
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    t2 = dsll32(a0, 16);
    t2 = dsra32(t2, 16);
    v0 = 1;
    if (t2 != v0) {
        // 0x00170c44
        charge(ctx, 3);
        v0 = si(-1);
        if (t2 != v0) {
            // 0x00170c74
            charge(ctx, 3);
            v0 = slti(t2, 256);
            if (v0 != 0) {
                // 0x00170d00
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x00170c80
                charge(ctx, 11);
                t3 = 0;
                v0 = sll(t2, 5);
                v1 = subu(v0, t2);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                t1 = sll(v0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 16400);  // &kPartyRecords (pc 2's record)
                t0 = addu(v0, t1);
                // sub_170760's pouch scan (the entry whose id equals the owner)
                for (;;) {
                    // 0x00170ce8
                    charge(ctx, 3);
                    v0 = slti(t3, 20);
                    if (v0 == 0) {
                        // 0x00170cf4
                        charge(ctx, 3);
                        v0 = 0;
                        break;
                    }
                    backedge(ctx);
                    // 0x00170cac
                    charge(ctx, 7);
                    a3 = sll(t3, 2);
                    v1 = addu(t0, a3);
                    v0 = lui(0xFFFD);
                    v0 = addu(v1, v0);
                    lhu(v0, v0, -26552);  // pouch[i].id
                    if (t2 == v0) {
                        // 0x00170cc8
                        charge(ctx, 7);
                        v0 = 0x800000;
                        v0 = addiu(v0, -10150);  // &records[0].pouch[0].num - 256 * 868 (owner >= 256)
                        v0 = addu(v0, t1);
                        v0 = addu(a3, v0);
                        lhu(v0, v0, 0);  // pouch[i].num
                        break;
                    }
                    // 0x00170ce4
                    charge(ctx, 1);
                    t3 = addiu(t3, 1);
                }
            }
        } else {
            // 0x00170c50
            charge(ctx, 9);
            v0 = dsll32(a1, 16);
            v0 = dsra32(v0, 16);
            v1 = sll(v0, 1);
            v0 = 0x830000;
            v0 = addiu(v0, 7392);  // &kTempItemNum (owner -1)
            v0 = addu(v0, v1);
            lhu(v0, v0, 0);
        }
    } else {
        // 0x00170c20
        charge(ctx, 9);
        v0 = 0x830000;
        lw(v1, v0, 26520);  // kHeroItemNum (gGlobalWork +0x598): u16 counts, biased by item 4000
        v0 = dsll32(a1, 16);
        v0 = dsra32(v0, 16);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        lhu(v0, v0, -8000);  // kHeroItemNum[id - 4000]
    }
    // 0x00170d04: s0 = clamp(count + delta, 0, 99)
    charge(ctx, 7);
    v1 = dsll32(a2, 16);
    v1 = dsra32(v1, 16);
    v0 = v0 & 0xFFFF;
    s0 = addu(v1, v0);
    v0 = slti(s0, 99);
    if (v0 != 0) {
        // 0x00170d2c
        charge(ctx, 2);
        if (i64(s0) < 0) {
            // 0x00170d34
            charge(ctx, 1);
            s0 = 0;
        }
    } else {
        // 0x00170d20
        charge(ctx, 3);
        s0 = 99;
    }
    // 0x00170d38
    charge(ctx, 9);
    a2 = s0 & 0xFFFF;
    jal(ctx, 0x170D3Cu, gen::fn_sub_170860_00170860);  // sub_170860(owner, id, s0): $a0 / $a1 still the caller's
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00171060 sub_171060 [datItemLocalIndex] -- 176 bytes; leaf frame (no stack)
// sub_171060(id): the index of item id within its kind: id mod 1000 for the five 1000-wide kinds (0..999, 1000..,
// 2000.., 3000.., 4000.., 5000..).
void sub_171060(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4};
    // 0x00171060
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    at = slti(v0, 1000);
    if (at == 0) {
        // 0x0017107c
        charge(ctx, 3);
        at = slti(v0, 2000);
        if (at == 0) {
            // 0x0017109c
            charge(ctx, 3);
            at = slti(v0, 3000);
            if (at == 0) {
                // 0x001710bc
                charge(ctx, 3);
                at = slti(v0, 4000);
                if (at == 0) {
                    // 0x001710dc
                    charge(ctx, 3);
                    at = slti(v0, 5000);
                    if (at == 0) {
                        // 0x001710fc
                        charge(ctx, 3);
                        v0 = addiu(v0, -5000);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                    } else {
                        // 0x001710e8
                        charge(ctx, 5);
                        v0 = addiu(v0, -4000);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                    }
                } else {
                    // 0x001710c8
                    charge(ctx, 5);
                    v0 = addiu(v0, -3000);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                }
            } else {
                // 0x001710a8
                charge(ctx, 5);
                v0 = addiu(v0, -2000);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
            }
        } else {
            // 0x00171088
            charge(ctx, 5);
            v0 = addiu(v0, -1000);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
        }
    } else {
        // 0x00171074
        charge(ctx, 2);
    }
    // 0x00171108 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00171110 sub_171110 [datGetItemName] -- 308 bytes; leaf frame (no stack)
// sub_171110(id, column): the name pointer of item id: per kind a table of 20-byte records (< 1000 0x5DDDC0, < 2000
// 0x5DABF0, < 3000 0x5D6C70) at + 4 * column, or a pointer table (< 4000 0x5DE8E0, 4000.. 0x5DE880, >= 5000 0x5DE040).
void sub_171110(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00171110
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    at = slti(v1, 1000);
    if (at == 0) {
        // 0x00171158
        charge(ctx, 3);
        at = slti(v1, 2000);
        if (at == 0) {
            // 0x00171198
            charge(ctx, 3);
            at = slti(v1, 3000);
            if (at == 0) {
                // 0x001711d8
                charge(ctx, 3);
                at = slti(v1, 4000);
                if (at == 0) {
                    // 0x00171200
                    charge(ctx, 3);
                    at = slti(v1, 5000);
                    if (at == 0) {
                        // 0x00171228
                        charge(ctx, 5);
                        v1 = sll(v1, 2);
                        v0 = 0x5E0000;
                        v0 = addiu(v0, -8128);  // &kItemNames5 (ids >= 5000; indexed by id)
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                    } else {
                        // 0x0017120c
                        charge(ctx, 7);
                        v1 = sll(v1, 2);
                        v0 = 0x5E0000;
                        v0 = addiu(v0, -6016);  // &kItemNames4 (ids 4000..4999; indexed by id)
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                    }
                } else {
                    // 0x001711e4
                    charge(ctx, 7);
                    v1 = sll(v1, 2);
                    v0 = 0x5E0000;
                    v0 = addiu(v0, -5920);  // &kItemNames3 (ids 3000..3999; indexed by id)
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                }
            } else {
                // 0x001711a4
                charge(ctx, 13);
                v0 = sll(v1, 2);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x5D0000;
                v0 = addiu(v0, 27776);  // "_efc0_03_00.bin"
                v1 = addu(v0, v1);
                v0 = dsll32(a1, 16);
                v0 = dsra32(v0, 16);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
            }
        } else {
            // 0x00171164
            charge(ctx, 13);
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            v0 = 0x5E0000;
            v0 = addiu(v0, -21520);  // &kItemNames1 (ids 1000..1999)
            v1 = addu(v0, v1);
            v0 = dsll32(a1, 16);
            v0 = dsra32(v0, 16);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
        }
    } else {
        // 0x00171124
        charge(ctx, 13);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x5E0000;
        v0 = addiu(v0, -8768);  // &kItemNames0 (ids < 1000)
        v1 = addu(v0, v1);
        v0 = dsll32(a1, 16);
        v0 = dsra32(v0, 16);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
    }
    // 0x0017123c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00171250 sub_171250 [datGetItemKind] -- 116 bytes; leaf frame (no stack)
// sub_171250(id): the kind of item id: 0 below 1000, 1 below 2000, 2 below 3000, 3 below 4000, else 4.
void sub_171250(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4};
    // 0x00171250
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    at = slti(v0, 1000);
    if (at == 0) {
        // 0x00171270
        charge(ctx, 3);
        at = slti(v0, 2000);
        if (at == 0) {
            // 0x00171288
            charge(ctx, 3);
            at = slti(v0, 3000);
            if (at == 0) {
                // 0x001712a0
                charge(ctx, 3);
                at = slti(v0, 4000);
                if (at == 0) {
                    // 0x001712b8
                    charge(ctx, 1);
                    v0 = 4;
                } else {
                    // 0x001712ac
                    charge(ctx, 3);
                    v0 = 3;
                }
            } else {
                // 0x00171294
                charge(ctx, 3);
                v0 = 2;
            }
        } else {
            // 0x0017127c
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x00171264
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001712bc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00171360 sub_171360 [datIsKeyItem] -- 40 bytes; leaf frame (no stack)
// sub_171360(id): 5000 <= id < 5128 (the item ids whose possession is a flag bit, sub_171390).
void sub_171360(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4};
    // 0x00171360
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = a0 & 0xFFFF;
    at = slti(v0, 5000);
    if (at == 0) {
        // 0x0017137c
        charge(ctx, 1);
        v0 = slti(v0, 5128);
    } else {
        // 0x00171370
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00171380 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00171390 sub_171390 [datSetKeyItemFlag] -- 284 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_171390(id): datSetFlag(id - 0x1188) for 5000 <= id < 5128 (K_Assert line 2558 outside), inlined: K_Assert line
// 1933 unless the flag < 0x1600, printf("hit \n") for flag 0x1376.
void sub_171390(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00171390
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = s0 & 0xFFFF;
    at = slti(s1, 5000);
    if (at == 0) {
        // 0x001713c0
        charge(ctx, 3);
        v1 = slti(s1, 5128);
        if (v1 != 0) {
            // 0x001713d8
            charge(ctx, 1);
            v1 = 1;
        } else {
            // 0x001713cc
            charge(ctx, 3);
            v1 = 0;
        }
    } else {
        // 0x001713b4
        charge(ctx, 3);
        v1 = 0;
    }
    // 0x001713dc
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x001713e4
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 2558;
        jal(ctx, 0x1713F0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 2558): returns
    }
    // 0x001713f8
    charge(ctx, 3);
    s1 = addiu(s1, -4488);  // the flag: id - 0x1188 (datSetFlag inlined from here)
    // K_Assert(line 1933) unless 0 <= flag < 0x1600
    bool in_range = false;
    if (i64(s1) >= 0) {
        // 0x00171404
        charge(ctx, 3);
        v1 = slti(s1, 5632);
        in_range = v1 != 0;
    }
    if (!in_range) {
        // 0x00171410
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 1933;
        jal(ctx, 0x17141Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1933): returns
    }
    // 0x00171424: the debug print for flag 0x1376
    charge(ctx, 3);
    v1 = 4982;
    if (s1 == v1) {
        // 0x00171430
        charge(ctx, 3);
        a0 = addiu(gp, -27976);  // "hit \n"
        jal(ctx, 0x171434u, gen::fn_printf_005225a8);
    }
    // 0x0017143c
    charge(ctx, 5);
    v1 = s0 & 0xFFFF;
    a2 = addiu(v1, -4488);
    a0 = a2 & 0x1F;
    if (i64(a2) < 0) {
        // 0x00171450
        charge(ctx, 2);
        if (a0 != 0) {
            // 0x00171458
            charge(ctx, 1);
            a0 = addiu(a0, -32);
        }
    }
    // 0x0017145c
    charge(ctx, 5);
    v1 = 1;
    a1 = sllv(v1, a0);
    v1 = sra(a2, 5);
    if (i64(a2) < 0) {
        // 0x00171470
        charge(ctx, 2);
        v1 = addiu(a2, 31);
        v1 = sra(v1, 5);
    }
    // 0x00171478 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    a0 = sll(v1, 2);
    v1 = 0x840000;
    v1 = addiu(v1, -24036);  // &g_datFlagWords
    a0 = addu(v1, a0);
    lw(v1, a0, 0);
    v1 = v1 | a1;
    sw(v1, a0, 0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00172820 sub_172820 -- 60 bytes; frame 0x10: ra sp+0x0
// sub_172820(value): sets bit 0x400 of flag word 0x83A34C (flag 0x98A) and the hero's condition (sub_16D6B0(1, value)).
void sub_172820(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00172820
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0x840000;
    lw(v0, v0, -23732);  // flag word 76 (flags 0x980..0x99F)
    v1 = v0 | 0x400;
    v0 = 0x840000;
    sw(v1, v0, -23732);  // flag word 76 (flags 0x980..0x99F)
    a1 = a0 & 0xFFFF;
    a0 = 1;
    jal(ctx, 0x172844u, gen::fn_sub_16D6B0_0016d6b0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00172890 sub_172890 [datEventAClear] -- 60 bytes; frame 0x10: ra sp+0x0
// sub_172890(): clears bit 0x980 (MT_Misc_BitOff) and the 56-byte record A at gGlobalWork +0x258.
void sub_172890(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00172890
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 2432;
    jal(ctx, 0x17289Cu, gen::fn_sub_3951A0_003951a0);
    a0 = 0x830000;
    a0 = addiu(a0, 25688);  // &kEventA (gGlobalWork +0x258)
    a1 = 0;
    a2 = 56;
    jal(ctx, 0x1728B4u, gen::fn_memset_00521408);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001728D0 sub_1728D0 [datEventASet] -- 192 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1728D0(src): record A = the 56 bytes at src (bit 0x980 cleared, record cleared, bit set, then 7 doubleword
// copies), its +0x10 word = 0 (sub_172A20); K_Assert line 3228 unless record A +4 < 5.
void sub_1728D0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001728d0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0x830000;
    s0 = addiu(s0, 25204);  // &kComuBlock (gGlobalWork +0x74)
    a0 = 2432;
    jal(ctx, 0x1728F0u, gen::fn_sub_3951A0_003951a0);
    a0 = 0x830000;
    a0 = addiu(a0, 25688);  // &kEventA (gGlobalWork +0x258)
    a1 = 0;
    a2 = 56;
    jal(ctx, 0x172908u, gen::fn_memset_00521408);
    a0 = 2432;
    jal(ctx, 0x172914u, gen::fn_sub_395170_00395170);
    a1 = addiu(s0, 484);  // &kEventA (gGlobalWork +0x258)
    a0 = 7;
    for (;;) {
        // 0x00172924
        charge(ctx, 9);
        lw(v1, s1, 0);
        lw(v0, s1, 4);
        s1 = addiu(s1, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00172948
    charge(ctx, 7);
    a0 = 0;
    jal(ctx, 0x17294Cu, gen::fn_sub_172A20_00172a20);
    lw(v1, s0, 488);
    at = slti(v1, 5);
    if (at == 0) {
        // 0x00172964
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 3228;
        jal(ctx, 0x172970u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 3228): returns
    }
    // 0x00172978 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00172990 sub_172990 [datEventAGet] -- 16 bytes; leaf frame (no stack)
// sub_172990(): the address of record A (gGlobalWork +0x258).
void sub_172990(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00172990
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x830000;
    v0 = addiu(v0, 25688);  // &kEventA (gGlobalWork +0x258)
}

// 0x001729A0 sub_1729A0 [datEventAIsSet] -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1729A0(): MT_Misc_BitChk(0x980) == 1.
void sub_1729A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001729a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 2432;
    jal(ctx, 0x1729ACu, gen::fn_MT_Misc_BitChk_003951d0);
    v0 = v0 ^ 0x1;
    v0 = sltiu(v0, 1);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001729D0 sub_1729D0 -- 52 bytes; leaf frame (no stack)
// sub_1729D0(out): *out = record A's u8 at +0x24 and returns 1, or 0 when it is 0xFF.
void sub_1729D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x001729d0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x830000;
    v0 = addiu(v0, 25688);  // &kEventA (gGlobalWork +0x258)
    lbu(v1, v0, 36);  // kEventA +0x24
    v0 = 255;
    if (v1 == v0) {
        // 0x001729f8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x001729e8
        charge(ctx, 4);
        sw(v1, a0, 0);
        v0 = 1;
    }
    // 0x001729fc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00172A10 sub_172A10 -- 16 bytes; leaf frame (no stack)
// sub_172A10(): record A's u8 at +8.
void sub_172A10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00172a10
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x830000;
    lbu(v0, v0, 25696);  // kEventA +8
}

// 0x00172A20 sub_172A20 -- 16 bytes; leaf frame (no stack)
// sub_172A20(value): record A's s32 at +0x10 = value.
void sub_172A20(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00172a20
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 0x830000;
    sw(a0, v1, 25704);  // kEventA +0x10
}

// 0x00172A30 sub_172A30 -- 24 bytes; leaf frame (no stack)
// sub_172A30(): record A's +0x10 word == 1.
void sub_172A30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00172a30
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x830000;
    lw(v0, v0, 25704);  // kEventA +0x10
    v0 = v0 ^ 0x1;
    v0 = sltiu(v0, 1);
}

// 0x00172AB0 sub_172AB0 -- 44 bytes; leaf frame (no stack)
// sub_172AB0(value): the u8 at gGlobalWork +0x290 = 1, the s16 at +0x292 = value, the s16 at +0x294 = today
// (datGetDaysSinceApr5's day).
void sub_172AB0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00172ab0
    enter(ctx, 11);  // entry check point + this block's cycles
    a1 = 1;
    v1 = 0x830000;
    sb(a1, v1, 25744);  // gGlobalWork +0x290
    v1 = 0x830000;
    sh(a0, v1, 25746);  // gGlobalWork +0x292
    v1 = 0x830000;
    lh(a0, v1, 26524);  // g_datDaysSinceApr5
    v1 = 0x830000;
    sh(a0, v1, 25748);  // gGlobalWork +0x294
}

// 0x00172AE0 sub_172AE0 [datEventBClear] -- 60 bytes; frame 0x10: ra sp+0x0
// sub_172AE0(): clears bit 0x983 and the 56-byte record B at gGlobalWork +0x2BC.
void sub_172AE0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00172ae0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 2435;
    jal(ctx, 0x172AECu, gen::fn_sub_3951A0_003951a0);
    a0 = 0x830000;
    a0 = addiu(a0, 25788);  // &kEventB (gGlobalWork +0x2BC)
    a1 = 0;
    a2 = 56;
    jal(ctx, 0x172B04u, gen::fn_memset_00521408);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00172B20 sub_172B20 -- 88 bytes; frame 0x20: ra sp+0x0
// sub_172B20(): when record B is set (sub_172C50), sub_17AD90() and the clear of sub_172AE0; returns sub_172C50's
// result.
void sub_172B20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00172b20
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    a0 = addiu(sp, 0x1E);
    jal(ctx, 0x172B2Cu, gen::fn_sub_172C50_00172c50);
    if (v0 != 0) {
        // 0x00172b3c
        charge(ctx, 11);
        jal(ctx, 0x172B3Cu, gen::fn_sub_17AD90_0017ad90);
        a0 = 2435;
        jal(ctx, 0x172B48u, gen::fn_sub_3951A0_003951a0);
        a0 = 0x830000;
        a0 = addiu(a0, 25788);  // &kEventB (gGlobalWork +0x2BC)
        a1 = 0;
        a2 = 56;
        jal(ctx, 0x172B60u, gen::fn_memset_00521408);
    }
    // 0x00172b68 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00172C50 sub_172C50 [datEventBGet] -- 100 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_172C50(out): when bit 0x983 is set: *out (s16) = record B's first byte, returns the record's address; else 0.
void sub_172C50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00172c50
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0x830000;
    s0 = addiu(s0, 25788);  // &kEventB (gGlobalWork +0x2BC)
    a0 = 2435;
    jal(ctx, 0x172C70u, gen::fn_MT_Misc_BitChk_003951d0);
    v1 = 1;
    if (v0 != v1) {
        // 0x00172c98
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00172c84
        charge(ctx, 5);
        lbu(v0, s0, 0);
        sh(v0, s1, 0);
        v0 = s0;
    }
    // 0x00172c9c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00172CC0 sub_172CC0 [datComuSetDate] -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_172CC0(comu): kComuMonth[comu] / kComuDayOfMonth[comu] (u8 gGlobalWork +0x534 / +0x552) = today's month and day
// (clndGetCurrentMonth / clndGetCurrentDay); K_Assert line 3391 unless 0 <= comu < 30.
void sub_172CC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00172cc0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    v0 = dsll32(s1, 16);
    v0 = dsra32(v0, 16);
    // v0 = (0 <= v0 < 30): the inlined id check
    bool in_range = false;
    if (i64(v0) >= 0) {
        // 0x00172ce4
        charge(ctx, 3);
        v0 = slti(v0, 30);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x00172cfc
        charge(ctx, 1);
        v0 = 1;
    } else {
        charge(ctx, 3);
        v0 = 0;
    }
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x00172d08
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 3391;
        jal(ctx, 0x172D14u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 3391): returns
    }
    // 0x00172d1c
    charge(ctx, 21);
    jal(ctx, 0x172D1Cu, gen::fn_clndGetCurrentMonth_0017d920);
    s0 = v0;
    jal(ctx, 0x172D28u, gen::fn_clndGetCurrentDay_0017da40);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    v1 = 0x830000;
    v1 = addiu(v1, 26420);  // &kComuMonth (gGlobalWork +0x534)
    v1 = addu(v1, a0);
    sb(s0, v1, 0);
    v1 = 0x830000;
    v1 = addiu(v1, 26450);  // &kComuDayOfMonth (gGlobalWork +0x552)
    v1 = addu(v1, a0);
    sb(v0, v1, 0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00172D70 sub_172D70 [datComuListToday] -- 160 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_172D70(out): writes the comu ids whose stored month / day equal today's to out[] (s32) and returns their count.
void sub_172D70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00172d70
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = 0;
    jal(ctx, 0x172D8Cu, gen::fn_clndGetCurrentMonth_0017d920);
    s0 = v0;
    jal(ctx, 0x172D98u, gen::fn_clndGetCurrentDay_0017da40);
    a2 = 0;
    a1 = 0x830000;
    a1 = addiu(a1, 25088);  // &gGlobalWork
    for (;;) {
        // 0x00172de4
        charge(ctx, 3);
        v1 = slti(a2, 30);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00172db4
        charge(ctx, 4);
        a0 = addu(a1, a2);
        lb(v1, a0, 1332);
        if (v1 == s0) {
            // 0x00172dc4
            charge(ctx, 3);
            lb(v1, a0, 1362);
            if (v1 == v0) {
                // 0x00172dd0
                charge(ctx, 4);
                v1 = sll(s1, 2);
                v1 = addu(s2, v1);
                sw(a2, v1, 0);
                s1 = addiu(s1, 1);
            }
        }
        // 0x00172de0
        charge(ctx, 1);
        a2 = addiu(a2, 1);
    }
    // 0x00172df0
    charge(ctx, 8);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00172E10 sub_172E10 -- 48 bytes; frame 0x10: ra sp+0x0
// sub_172E10(): clears the 36-byte array at gGlobalWork +0x298 (the date change's reset, datSetDaysSinceApr5).
void sub_172E10(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00172e10
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x830000;
    a0 = addiu(a0, 25752);  // &gGlobalWork +0x298
    a1 = 0;
    a2 = 36;
    jal(ctx, 0x172E28u, gen::fn_memset_00521408);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00172E40 sub_172E40 -- 16 bytes; leaf frame (no stack)
// sub_172E40(): the address of the array at gGlobalWork +0x298.
void sub_172E40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00172e40
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x830000;
    v0 = addiu(v0, 25752);  // &gGlobalWork +0x298
}

// 0x00173280 sub_173280 [datPersonaGetArcana] -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_173280(id): the arcana (u8 +2) of persona id in the 14-byte persona table (*0x7CE420); K_Assert line 38 unless id
// < 256.
void sub_173280(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00173280
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = s0 & 0xFFFF;
    v0 = slti(v0, 256);
    if (v0 == 0) {
        // 0x001732a0
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 38;
        jal(ctx, 0x1732ACu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 38): returns
    }
    // 0x001732b4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    lw(a0, gp, -18640);  // kPersonaTable: the 14-byte persona records ($gp - 0x48D0)
    v1 = s0 & 0xFFFF;
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, a0);
    lbu(v0, v0, 2);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00173300 sub_173300 [datPersonaGetLevelByPcId] -- 36 bytes; frame 0x10: ra sp+0x0
// sub_173300(pc): datPersonaGetByPcId(pc)->level (u8 +4).
void sub_173300(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00173300
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x173308u, gen::fn_datPersonaGetByPcId_00174800);
    lbu(v0, v0, pf::kLevel);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00173330 sub_173330 [datPersonaGetExp] -- 12 bytes; leaf frame (no stack)
// sub_173330(persona): persona->exp (s32 +8).
void sub_173330(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00173330
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, pf::kExp);
}

// 0x00173340 sub_173340 [datPersonaGetNextLevelExp] -- 44 bytes; frame 0x10: ra sp+0x0
// sub_173340(persona): sub_176210(persona, persona->level + 1), the experience the next level needs (a tail call in its
// own frame).
void sub_173340(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00173340
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lbu(v0, a0, pf::kLevel);
    v0 = addiu(v0, 1);
    a1 = v0 & 0xFFFF;
    jal(ctx, 0x173354u, gen::fn_sub_176210_00176210);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00173370 sub_173370 [datPersonaGetSkills] -- 12 bytes; leaf frame (no stack)
// sub_173370(persona): &persona->skills (persona + 12, u16[8]).
void sub_173370(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00173370
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = addiu(a0, 12);
}

// 0x00173580 sub_173580 -- 220 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_173580(persona, stat): persona stat `stat` without the equipment bonus: base (u8 +0x1C) + bonus A (sub_173B00) +
// bonus B (sub_173C00), capped at 99 (u8); K_Assert line 316 unless stat < 5.
void sub_173580(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00173580
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    v0 = s0 & 0xFFFF;
    v0 = slti(v0, 5);
    if (v0 == 0) {
        // 0x001735b0
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 316;
        jal(ctx, 0x1735BCu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 316): returns
    }
    // 0x001735c4
    charge(ctx, 28);
    v0 = s0 & 0xFFFF;
    v0 = addu(v0, s1);
    lbu(v0, v0, pf::kBaseStats);
    s3 = dsll32(v0, 16);
    s3 = dsra32(s3, 16);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x1735E0u, gen::fn_sub_173B00_00173b00);
    s2 = dsll32(v0, 24);
    s2 = dsra32(s2, 24);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x1735F8u, gen::fn_sub_173C00_00173c00);
    a0 = dsll32(v0, 24);
    a0 = dsra32(a0, 24);
    v1 = dsll32(s3, 16);
    v1 = dsra32(v1, 16);
    v0 = dsll32(s2, 16);
    v0 = dsra32(v0, 16);
    v0 = addu(v1, v0);
    v0 = addu(a0, v0);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = slti(v1, 99);
    if (v0 == 0) {
        // 0x00173634
        charge(ctx, 1);
        v1 = 99;
    }
    // 0x00173638 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = v1 & 0xFF;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00173660 sub_173660 [datPersonaGetTotalStat] -- 284 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_173660(persona, stat): persona stat `stat`: base + bonus A + bonus B + the equipment bonus (sub_173C60), clamped
// to 0..99 (u8); K_Assert line 316 unless stat < 5.
void sub_173660(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00173660
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    v0 = s1 & 0xFFFF;
    v0 = slti(v0, 5);
    if (v0 == 0) {
        // 0x00173694
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 316;
        jal(ctx, 0x1736A0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 316): returns
    }
    // 0x001736a8
    charge(ctx, 37);
    v0 = s1 & 0xFFFF;
    v0 = addu(v0, s2);
    lbu(v0, v0, pf::kBaseStats);
    s4 = dsll32(v0, 16);
    s4 = dsra32(s4, 16);
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x1736C4u, gen::fn_sub_173B00_00173b00);
    s3 = dsll32(v0, 24);
    s3 = dsra32(s3, 24);
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x1736DCu, gen::fn_sub_173C00_00173c00);
    s0 = dsll32(v0, 24);
    s0 = dsra32(s0, 24);
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x1736F4u, gen::fn_sub_173C60_00173c60);
    a0 = dsll32(v0, 24);
    a0 = dsra32(a0, 24);
    v1 = dsll32(s4, 16);
    v1 = dsra32(v1, 16);
    v0 = dsll32(s3, 16);
    v0 = dsra32(v0, 16);
    v1 = addu(v1, v0);
    v0 = dsll32(s0, 16);
    v0 = dsra32(v0, 16);
    v0 = addu(v0, v1);
    v0 = addu(a0, v0);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    at = slti(v0, 100);
    if (at != 0) {
        // 0x00173748
        charge(ctx, 2);
        if (i64(v0) < 0) {
            // 0x00173750
            charge(ctx, 1);
            v0 = 0;
        }
    } else {
        // 0x0017373c
        charge(ctx, 3);
        v0 = 99;
    }
    // 0x00173754 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = v0 & 0xFF;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00173780 sub_173780 -- 328 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_173780(slot, stat): sub_173660 for the hero's stock slot `slot` (sub_174A90; K_Assert line 402 on an empty slot).
void sub_173780(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00173780
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x1737A8u, gen::fn_sub_174A90_00174a90);
    s1 = v0;
    if (s1 == 0) {
        // 0x001737bc
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 402;
        jal(ctx, 0x1737C8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 402): returns
    }
    // 0x001737d0
    charge(ctx, 4);
    v0 = s2 & 0xFFFF;
    v0 = slti(v0, 5);
    if (v0 == 0) {
        // 0x001737e0
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 316;
        jal(ctx, 0x1737ECu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 316): returns
    }
    // 0x001737f4
    charge(ctx, 37);
    v0 = s2 & 0xFFFF;
    v0 = addu(v0, s1);
    lbu(v0, v0, pf::kBaseStats);
    s4 = dsll32(v0, 16);
    s4 = dsra32(s4, 16);
    a0 = s1;
    a1 = s2;
    jal(ctx, 0x173810u, gen::fn_sub_173B00_00173b00);
    s3 = dsll32(v0, 24);
    s3 = dsra32(s3, 24);
    a0 = s1;
    a1 = s2;
    jal(ctx, 0x173828u, gen::fn_sub_173C00_00173c00);
    s0 = dsll32(v0, 24);
    s0 = dsra32(s0, 24);
    a0 = s1;
    a1 = s2;
    jal(ctx, 0x173840u, gen::fn_sub_173C60_00173c60);
    a0 = dsll32(v0, 24);
    a0 = dsra32(a0, 24);
    v1 = dsll32(s4, 16);
    v1 = dsra32(v1, 16);
    v0 = dsll32(s3, 16);
    v0 = dsra32(v0, 16);
    v1 = addu(v1, v0);
    v0 = dsll32(s0, 16);
    v0 = dsra32(v0, 16);
    v0 = addu(v0, v1);
    v0 = addu(a0, v0);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    at = slti(v0, 100);
    if (at != 0) {
        // 0x00173894
        charge(ctx, 2);
        if (i64(v0) < 0) {
            // 0x0017389c
            charge(ctx, 1);
            v0 = 0;
        }
    } else {
        // 0x00173888
        charge(ctx, 3);
        v0 = 99;
    }
    // 0x001738a0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = v0 & 0xFF;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00173A00 sub_173A00 -- 248 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_173A00(persona, stat): sub_173580's sum (base + bonus A + bonus B, at most 99) as an s16; K_Assert lines 423 /
// 316 unless stat < 5.
void sub_173A00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00173a00
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    s2 = s0 & 0xFFFF;
    v0 = slti(s2, 5);
    if (v0 == 0) {
        // 0x00173a30
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 423;
        jal(ctx, 0x173A3Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 423): returns
    }
    // 0x00173a44
    charge(ctx, 3);
    v0 = slti(s2, 5);
    if (v0 == 0) {
        // 0x00173a50
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 316;
        jal(ctx, 0x173A5Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 316): returns
    }
    // 0x00173a64
    charge(ctx, 28);
    v0 = s0 & 0xFFFF;
    v0 = addu(v0, s1);
    lbu(v0, v0, pf::kBaseStats);
    s3 = dsll32(v0, 16);
    s3 = dsra32(s3, 16);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x173A80u, gen::fn_sub_173B00_00173b00);
    s2 = dsll32(v0, 24);
    s2 = dsra32(s2, 24);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x173A98u, gen::fn_sub_173C00_00173c00);
    a0 = dsll32(v0, 24);
    a0 = dsra32(a0, 24);
    v1 = dsll32(s3, 16);
    v1 = dsra32(v1, 16);
    v0 = dsll32(s2, 16);
    v0 = dsra32(v0, 16);
    v0 = addu(v1, v0);
    v0 = addu(a0, v0);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    v1 = slti(v0, 99);
    if (v1 == 0) {
        // 0x00173ad4
        charge(ctx, 1);
        v0 = 99;
    }
    // 0x00173ad8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00173B00 sub_173B00 [datPersonaGetBonusA] -- 96 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_173B00(persona, stat): persona->bonus_a[stat] (s8 +0x21); K_Assert line 454 unless stat < 5.
void sub_173B00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00173b00
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    v0 = s0 & 0xFFFF;
    v0 = slti(v0, 5);
    if (v0 == 0) {
        // 0x00173b28
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 454;
        jal(ctx, 0x173B34u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 454): returns
    }
    // 0x00173b3c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s0 & 0xFFFF;
    v0 = addu(v0, s1);
    lb(v0, v0, pf::kBonusA);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00173B60 sub_173B60 [datPersonaSetBonusAByPcId] -- 68 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_173B60(pc, stat, value): datPersonaGetByPcId(pc)->bonus_a[stat] = value.
void sub_173B60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00173b60
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    jal(ctx, 0x173B78u, gen::fn_datPersonaGetByPcId_00174800);
    v1 = s1 & 0xFFFF;
    v1 = addu(v1, v0);
    sb(s0, v1, pf::kBonusA);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00173BB0 sub_173BB0 [datPersonaAddBonusAByPcId] -- 80 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_173BB0(pc, stat, value): datPersonaGetByPcId(pc)->bonus_a[stat] += value.
void sub_173BB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00173bb0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    jal(ctx, 0x173BC8u, gen::fn_datPersonaGetByPcId_00174800);
    v1 = s1 & 0xFFFF;
    a1 = addu(v1, v0);
    a0 = s0 & 0xFF;
    lbu(v1, a1, pf::kBonusA);
    v1 = addu(v1, a0);
    sb(v1, a1, pf::kBonusA);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00173C00 sub_173C00 [datPersonaGetBonusB] -- 96 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_173C00(persona, stat): persona->bonus_b[stat] (s8 +0x26); K_Assert line 503 unless stat < 5.
void sub_173C00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00173c00
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    v0 = s0 & 0xFFFF;
    v0 = slti(v0, 5);
    if (v0 == 0) {
        // 0x00173c28
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 503;
        jal(ctx, 0x173C34u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 503): returns
    }
    // 0x00173c3c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s0 & 0xFFFF;
    v0 = addu(v0, s1);
    lb(v0, v0, pf::kBonusB);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00174650 sub_174650 [datPersonaAddBaseStat] -- 184 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_174650(persona, stat, delta): persona->base_stats[stat] += delta clamped to 0..99, returned (u8); K_Assert line
// 722 unless stat < 5.
void sub_174650(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00174650
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    v0 = s1 & 0xFFFF;
    v0 = slti(v0, 5);
    if (v0 == 0) {
        // 0x00174680
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 722;
        jal(ctx, 0x17468Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 722): returns
    }
    // 0x00174694
    charge(ctx, 14);
    v0 = s1 & 0xFFFF;
    v0 = addu(v0, s2);
    a0 = addiu(v0, 28);
    lbu(v0, v0, pf::kBaseStats);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = dsll32(s0, 24);
    v0 = dsra32(v0, 24);
    v0 = addu(v1, v0);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    at = slti(v1, 100);
    if (at != 0) {
        // 0x001746d8
        charge(ctx, 2);
        if (i64(v1) < 0) {
            // 0x001746e0
            charge(ctx, 1);
            v1 = 0;
        }
    } else {
        // 0x001746cc
        charge(ctx, 3);
        v1 = 99;
    }
    // 0x001746e4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = v1 & 0xFF;
    sb(v1, a0, 0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00174710 sub_174710 -- 228 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_174710(slot, stat, delta): sub_174650 on the hero's stock slot `slot` (sub_174A90; K_Assert line 747 on an empty
// slot).
void sub_174710(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00174710
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    s0 = a2;
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x174734u, gen::fn_sub_174A90_00174a90);
    s1 = v0;
    if (s1 == 0) {
        // 0x00174748
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 747;
        jal(ctx, 0x174754u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 747): returns
    }
    // 0x0017475c
    charge(ctx, 4);
    v0 = s2 & 0xFFFF;
    v0 = slti(v0, 5);
    if (v0 == 0) {
        // 0x0017476c
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 722;
        jal(ctx, 0x174778u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 722): returns
    }
    // 0x00174780
    charge(ctx, 14);
    v0 = s2 & 0xFFFF;
    v0 = addu(v0, s1);
    a0 = addiu(v0, 28);
    lbu(v0, v0, pf::kBaseStats);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = dsll32(s0, 24);
    v0 = dsra32(v0, 24);
    v0 = addu(v1, v0);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    at = slti(v1, 100);
    if (at != 0) {
        // 0x001747c4
        charge(ctx, 2);
        if (i64(v1) < 0) {
            // 0x001747cc
            charge(ctx, 1);
            v1 = 0;
        }
    } else {
        // 0x001747b8
        charge(ctx, 3);
        v1 = 99;
    }
    // 0x001747d0 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = v1 & 0xFF;
    sb(v1, a0, 0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001748C0 sub_1748C0 [datPersonaFindFreeSlot] -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1748C0(): the first hero stock slot below the stock size (sub_175410) whose flag bit 0 is clear, -1 when the
// stock is full.
void sub_1748C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001748c0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    for (;;) {  // s0 = slot, while slot < sub_175410() (the stock size, called every iteration)
        // 0x00174928
        charge(ctx, 7);
        s1 = s0 & 0xFFFF;
        jal(ctx, 0x17492Cu, gen::fn_sub_175410_00175410);
        v0 = v0 & 0xFFFF;
        v0 = slt(s1, v0);
        if (v0 == 0) {
            // 0x00174944: the stock is full
            charge(ctx, 1);
            v0 = si(-1);
            break;
        }
        backedge(ctx);
        // 0x001748dc: gGlobalWork + 52 slot + 0x9AC = &kHeroPersonaStock[slot] (52 = ((slot * 3) * 4 + slot) * 4)
        charge(ctx, 13);
        v1 = s0 & 0xFFFF;
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 25088);  // &gGlobalWork
        v0 = addu(v0, v1);
        lhu(v0, v0, 2476);  // kHeroPersonaStock[slot].flags (gGlobalWork +0x9AC)
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x00174910: a free slot: (s16)slot
            charge(ctx, 4);
            v0 = dsll32(s0, 16);
            v0 = dsra32(v0, 16);
            break;
        }
        // 0x00174920
        charge(ctx, 2);
        v0 = addiu(s0, 1);
        s0 = v0 & 0xFFFF;
    }
    // 0x00174948 (the shared epilogue)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00174960 sub_174960 [datPersonaIsSlotUsed] -- 60 bytes; leaf frame (no stack)
// sub_174960(slot): flag bit 0 of hero stock slot `slot` (no range check).
void sub_174960(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00174960
    enter(ctx, 15);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    v0 = 0x830000;
    v0 = addiu(v0, 27564);  // &kHeroPersonaStock
    v0 = addu(v0, v1);
    lhu(v0, v0, 0);
    v0 = v0 & 0x1;
    v0 = sltu(0, v0);
}

// 0x001749A0 sub_1749A0 [datPersonaFindById] -- 228 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1749A0(id): the hero stock entry (sub_174A90) holding persona id, 0 when none.
void sub_1749A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001749a0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    s0 = dsll32(a0, 16);
    s0 = dsra32(s0, 16);
    for (;;) {
        // 0x00174a20
        charge(ctx, 7);
        s2 = s1 & 0xFFFF;
        jal(ctx, 0x174A24u, gen::fn_sub_175410_00175410);
        v0 = v0 & 0xFFFF;
        v0 = slt(s2, v0);
        if (v0 == 0) {
            // 0x00174a3c: not held: slot -1
            charge(ctx, 1);
            a0 = si(-1);
            break;
        }
        backedge(ctx);
        // 0x001749c8
        charge(ctx, 13);
        v1 = s1 & 0xFFFF;
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 25088);  // &gGlobalWork
        v1 = addu(v0, v1);
        lhu(v0, v1, 2476);  // kHeroPersonaStock[slot].flags
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x001749fc
            charge(ctx, 3);
            lhu(v0, v1, 2478);  // kHeroPersonaStock[slot].id
            if (v0 == s0) {
                // 0x00174a08: found: a0 = (s16)slot
                charge(ctx, 4);
                a0 = dsll32(s1, 16);
                a0 = dsra32(a0, 16);
                break;
            }
        }
        // 0x00174a18
        charge(ctx, 2);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFFFF;
    }
    // 0x00174a40: sub_174A90(slot), or 0 when slot == -1
    charge(ctx, 5);
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x00174a60
        charge(ctx, 2);
        jal(ctx, 0x174A60u, gen::fn_sub_174A90_00174a90);
    } else {
        // 0x00174a54
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00174a68 (the shared epilogue)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00174B40 sub_174B40 [datPersonaRemoveById] -- 196 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_174B40(id): sub_174C10 on the hero stock slot holding persona id (-1 when none, which sub_174C10 asserts on).
void sub_174B40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00174b40
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    s0 = dsll32(a0, 16);
    s0 = dsra32(s0, 16);
    for (;;) {
        // 0x00174bc0
        charge(ctx, 7);
        s2 = s1 & 0xFFFF;
        jal(ctx, 0x174BC4u, gen::fn_sub_175410_00175410);
        v0 = v0 & 0xFFFF;
        v0 = slt(s2, v0);
        if (v0 == 0) {
            // 0x00174bdc: not held: slot -1
            charge(ctx, 1);
            a0 = si(-1);
            break;
        }
        backedge(ctx);
        // 0x00174b68
        charge(ctx, 13);
        v1 = s1 & 0xFFFF;
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 25088);  // &gGlobalWork
        v1 = addu(v0, v1);
        lhu(v0, v1, 2476);  // kHeroPersonaStock[slot].flags
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x00174b9c
            charge(ctx, 3);
            lhu(v0, v1, 2478);  // kHeroPersonaStock[slot].id
            if (v0 == s0) {
                // 0x00174ba8: found: a0 = (s16)slot
                charge(ctx, 4);
                a0 = dsll32(s1, 16);
                a0 = dsra32(a0, 16);
                break;
            }
        }
        // 0x00174bb8
        charge(ctx, 2);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFFFF;
    }
    // 0x00174be0: the call with the slot (or -1)
    charge(ctx, 9);
    jal(ctx, 0x174BE0u, gen::fn_sub_174C10_00174c10);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00174E20 sub_174E20 [datPersonaAddChecked] -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_174E20(id): sub_174E70(id) with K_Assert line 908 when the stock is full.
void sub_174E20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00174e20
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x174E2Cu, gen::fn_sub_174E70_00174e70);
    s0 = v0;
    if (s0 == 0) {
        // 0x00174e40
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 908;
        jal(ctx, 0x174E4Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 908): returns
    }
    // 0x00174e54 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00174E70 sub_174E70 [datPersonaAdd] -- 308 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_174E70(id): puts a new persona of id into the first free hero stock slot: sub_176680(entry, id) builds it, flags
// = (flags & 0xC) | 1, sub_17CD30(entry) registers it; returns the entry, 0 when the stock is full.
void sub_174E70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00174e70
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0;
    for (;;) {
        // 0x00174ee0
        charge(ctx, 7);
        s2 = s0 & 0xFFFF;
        jal(ctx, 0x174EE4u, gen::fn_sub_175410_00175410);
        v0 = v0 & 0xFFFF;
        v0 = slt(s2, v0);
        if (v0 == 0) {
            // 0x00174efc: the stock is full: -1
            charge(ctx, 1);
            v0 = si(-1);
            break;
        }
        backedge(ctx);
        // 0x00174e94
        charge(ctx, 13);
        v1 = s0 & 0xFFFF;
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 25088);  // &gGlobalWork
        v0 = addu(v0, v1);
        lhu(v0, v0, 2476);  // kHeroPersonaStock[slot].flags
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x00174ec8: a free slot: (s16)slot
            charge(ctx, 4);
            v0 = dsll32(s0, 16);
            v0 = dsra32(v0, 16);
            break;
        }
        // 0x00174ed8
        charge(ctx, 2);
        v0 = addiu(s0, 1);
        s0 = v0 & 0xFFFF;
    }
    // 0x00174f00: fill the slot (or 0 when -1)
    charge(ctx, 5);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x00174f20
        charge(ctx, 26);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        s2 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 25088);  // &gGlobalWork
        v0 = addu(v0, s2);
        s0 = addiu(v0, 2476);
        a0 = s0;
        a1 = s1;
        jal(ctx, 0x174F4Cu, gen::fn_sub_176680_00176680);
        v0 = 0x830000;
        v0 = addiu(v0, 27564);  // &kHeroPersonaStock
        v1 = addu(v0, s2);
        lhu(v0, v1, 0);
        v0 = v0 & 0xC;
        sh(v0, v1, 0);
        lhu(v0, v1, 0);
        v0 = v0 | 0x1;
        sh(v0, v1, 0);
        a0 = s0;
        jal(ctx, 0x174F7Cu, gen::fn_sub_17CD30_0017cd30);
        v0 = s0;
    } else {
        // 0x00174f14
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00174f88 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00174FB0 sub_174FB0 [datPersonaAddCopy] -- 384 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_174FB0(src): copies the 52-byte persona at src into the first free hero stock slot (K_Assert lines 944 / 945 on a
// null src or an id outside 1..255), flags = (flags & 0xC) | 1, sub_17CD30(entry); returns 1, 0 when the stock is full.
void sub_174FB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00174fb0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    if (s1 == 0) {
        // 0x00174fd0
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 944;
        jal(ctx, 0x174FDCu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 944): returns
    }
    // 0x00174fe4
    charge(ctx, 3);
    lhu(v0, s1, pf::kId);
    bool ok = false;  // the K_Assert below runs unless both tests pass
    if (v0 != 0) {
        // 0x00174ff0
        charge(ctx, 3);
        v0 = slti(v0, 256);
        ok = v0 != 0;
    }
    if (!ok) {
        // 0x00174ffc
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 945;
        jal(ctx, 0x175008u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 945): returns
    }
    // 0x00175010
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x00175068
        charge(ctx, 7);
        s2 = s0 & 0xFFFF;
        jal(ctx, 0x17506Cu, gen::fn_sub_175410_00175410);
        v0 = v0 & 0xFFFF;
        v0 = slt(s2, v0);
        if (v0 == 0) {
            // 0x00175084: the stock is full: -1
            charge(ctx, 1);
            v0 = si(-1);
            break;
        }
        backedge(ctx);
        // 0x0017501c
        charge(ctx, 13);
        v1 = s0 & 0xFFFF;
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 25088);  // &gGlobalWork
        v0 = addu(v0, v1);
        lhu(v0, v0, 2476);  // kHeroPersonaStock[slot].flags
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x00175050: a free slot: (s16)slot
            charge(ctx, 4);
            v0 = dsll32(s0, 16);
            v0 = dsra32(v0, 16);
            break;
        }
        // 0x00175060
        charge(ctx, 2);
        v0 = addiu(s0, 1);
        s0 = v0 & 0xFFFF;
    }
    // 0x00175088: fill the slot (or 0 when -1)
    charge(ctx, 5);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x001750a8
        charge(ctx, 27);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        s2 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 25088);  // &gGlobalWork
        v0 = addu(v0, s2);
        s0 = addiu(v0, 2476);
        a0 = s0;
        a1 = s1;
        a2 = 52;
        jal(ctx, 0x1750D8u, gen::fn_memcpy_00521250);
        v0 = 0x830000;
        v0 = addiu(v0, 27564);  // &kHeroPersonaStock
        v1 = addu(v0, s2);
        lhu(v0, v1, 0);
        v0 = v0 & 0xC;
        sh(v0, v1, 0);
        lhu(v0, v1, 0);
        v0 = v0 | 0x1;
        sh(v0, v1, 0);
        a0 = s0;
        jal(ctx, 0x175108u, gen::fn_sub_17CD30_0017cd30);
        v0 = 1;
    } else {
        // 0x0017509c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00175114 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00175130 sub_175130 [datPersonaSelectById] -- 196 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_175130(id): sub_175200 on the hero stock slot holding persona id (-1 when none).
void sub_175130(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00175130
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    s0 = dsll32(a0, 16);
    s0 = dsra32(s0, 16);
    for (;;) {
        // 0x001751b0
        charge(ctx, 7);
        s2 = s1 & 0xFFFF;
        jal(ctx, 0x1751B4u, gen::fn_sub_175410_00175410);
        v0 = v0 & 0xFFFF;
        v0 = slt(s2, v0);
        if (v0 == 0) {
            // 0x001751cc: not held: slot -1
            charge(ctx, 1);
            a0 = si(-1);
            break;
        }
        backedge(ctx);
        // 0x00175158
        charge(ctx, 13);
        v1 = s1 & 0xFFFF;
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 25088);  // &gGlobalWork
        v1 = addu(v0, v1);
        lhu(v0, v1, 2476);  // kHeroPersonaStock[slot].flags
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x0017518c
            charge(ctx, 3);
            lhu(v0, v1, 2478);  // kHeroPersonaStock[slot].id
            if (v0 == s0) {
                // 0x00175198: found: a0 = (s16)slot
                charge(ctx, 4);
                a0 = dsll32(s1, 16);
                a0 = dsra32(a0, 16);
                break;
            }
        }
        // 0x001751a8
        charge(ctx, 2);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFFFF;
    }
    // 0x001751d0: the call with the slot (or -1)
    charge(ctx, 9);
    jal(ctx, 0x1751D0u, gen::fn_sub_175200_00175200);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00175200 sub_175200 [datPersonaSelectSlot] -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_175200(slot): makes stock slot `slot` the hero's current persona (kHeroPersonaIdx) when it is used, returns 1;
// else 0. K_Assert line 970 unless 0 <= slot < the stock size.
void sub_175200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00175200
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = dsll32(s1, 16);
    s0 = dsra32(s0, 16);
    bool ok = false;  // the K_Assert below runs unless both tests pass
    if (i64(s0) >= 0) {
        // 0x00175224
        charge(ctx, 6);
        jal(ctx, 0x175224u, gen::fn_sub_175410_00175410);
        v0 = v0 & 0xFFFF;
        v0 = slt(s0, v0);
        ok = v0 != 0;
    }
    if (!ok) {
        // 0x0017523c
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 970;
        jal(ctx, 0x175248u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 970): returns
    }
    // 0x00175250
    charge(ctx, 12);
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v0 = sll(v0, 2);
    v0 = addu(v0, s0);
    v1 = sll(v0, 2);
    v0 = 0x830000;
    v0 = addiu(v0, 27564);  // &kHeroPersonaStock
    v0 = addu(v0, v1);
    lhu(v0, v0, 0);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x0017528c
        charge(ctx, 3);
        v0 = 0x830000;
        sh(s1, v0, 27560);  // kHeroPersonaIdx (gGlobalWork +0x9A8)
        v0 = 1;
    } else {
        // 0x00175280
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00175298 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001752B0 sub_1752B0 [datPersonaGetCurrentId] -- 176 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1752B0(): the persona id (u16 +2) of the hero's current stock slot; K_Assert lines 989 / 990 on a slot out of
// range or empty.
void sub_1752B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001752b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = 0x830000;
    lh(s0, v0, 27560);  // kHeroPersonaIdx (gGlobalWork +0x9A8)
    bool ok = false;  // the K_Assert below runs unless both tests pass
    if (i64(s0) >= 0) {
        // 0x001752cc
        charge(ctx, 6);
        jal(ctx, 0x1752CCu, gen::fn_sub_175410_00175410);
        v0 = v0 & 0xFFFF;
        v0 = slt(s0, v0);
        ok = v0 != 0;
    }
    if (!ok) {
        // 0x001752e4
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 989;
        jal(ctx, 0x1752F0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 989): returns
    }
    // 0x001752f8
    charge(ctx, 12);
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v0 = sll(v0, 2);
    v0 = addu(v0, s0);
    s0 = sll(v0, 2);
    v0 = 0x830000;
    v0 = addiu(v0, 27564);  // &kHeroPersonaStock
    v0 = addu(v0, s0);
    lhu(v0, v0, 0);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x00175328
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 990;
        jal(ctx, 0x175334u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 990): returns
    }
    // 0x0017533c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = 0x830000;
    v0 = addiu(v0, 27566);  // &kHeroPersonaStock[0].id
    v0 = addu(v0, s0);
    lhu(v0, v0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00175360 sub_175360 [datPersonaGetCurrentSlot] -- 164 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_175360(): the hero's current stock slot (s16 kHeroPersonaIdx); K_Assert lines 1000 / 1001 on a slot out of range
// or empty.
void sub_175360(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00175360
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = 0x830000;
    lh(s0, v0, 27560);  // kHeroPersonaIdx (gGlobalWork +0x9A8)
    bool ok = false;  // the K_Assert below runs unless both tests pass
    if (i64(s0) >= 0) {
        // 0x0017537c
        charge(ctx, 6);
        jal(ctx, 0x17537Cu, gen::fn_sub_175410_00175410);
        v0 = v0 & 0xFFFF;
        v0 = slt(s0, v0);
        ok = v0 != 0;
    }
    if (!ok) {
        // 0x00175394
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 1000;
        jal(ctx, 0x1753A0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1000): returns
    }
    // 0x001753a8
    charge(ctx, 12);
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v0 = sll(v0, 2);
    v0 = addu(v0, s0);
    v1 = sll(v0, 2);
    v0 = 0x830000;
    v0 = addiu(v0, 27564);  // &kHeroPersonaStock
    v0 = addu(v0, v1);
    lhu(v0, v0, 0);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x001753d8
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 1001;
        jal(ctx, 0x1753E4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1001): returns
    }
    // 0x001753ec (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001754A0 sub_1754A0 [datPersonaSetStockLevel] -- 284 bytes; frame 0x10: ra sp+0x0
// sub_1754A0(level): sets the stock-size bits of kPersonaStockFlags (0x83A45C, mask 0x3007) for level 0..5: none /
// 0x1000 / 0x3000 / 0x3001 / 0x3003 / 0x3007 (sizes 4 / 6 / 8 / 9 / 10 / 12, sub_175410); K_Assert line 1066 for
// another level (jump table 0x7B6480).
void sub_1754A0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001754a0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = 0x840000;
    lw(a1, v1, -23460);  // kPersonaStockFlags
    v1 = si(-4097);
    a1 = a1 & v1;
    v1 = si(-8193);
    a1 = a1 & v1;
    v1 = si(-2);
    a1 = a1 & v1;
    v1 = si(-3);
    a1 = a1 & v1;
    v1 = si(-5);
    a1 = a1 & v1;
    v1 = 0x840000;
    sw(a1, v1, -23460);  // kPersonaStockFlags
    v1 = a0 & 0xFFFF;
    at = sltiu(v1, 6);
    if (at == 0) {
        // 0x00175598
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 1066;
        jal(ctx, 0x1755A4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1066): returns
    } else {
        // 0x001754f0
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 25728);  // &jpt_175504 (sub_1754A0's jump table)
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x17550Cu:  // table[1]
            // 0x0017550c
            charge(ctx, 5);
            a0 = a1 | 0x1000;
            v1 = 0x840000;
            sw(a0, v1, -23460);  // kPersonaStockFlags
            break;
        case 0x175520u:  // table[2]
            // 0x00175520
            charge(ctx, 6);
            v1 = a1 | 0x1000;
            a0 = v1 | 0x2000;
            v1 = 0x840000;
            sw(a0, v1, -23460);  // kPersonaStockFlags
            break;
        case 0x175538u:  // table[3]
            // 0x00175538
            charge(ctx, 7);
            v1 = a1 | 0x1000;
            v1 = v1 | 0x2000;
            a0 = v1 | 0x1;
            v1 = 0x840000;
            sw(a0, v1, -23460);  // kPersonaStockFlags
            break;
        case 0x175554u:  // table[4]
            // 0x00175554
            charge(ctx, 8);
            v1 = a1 | 0x1000;
            v1 = v1 | 0x2000;
            v1 = v1 | 0x1;
            a0 = v1 | 0x2;
            v1 = 0x840000;
            sw(a0, v1, -23460);  // kPersonaStockFlags
            break;
        case 0x175574u:  // table[5]
            // 0x00175574
            charge(ctx, 9);
            v1 = a1 | 0x1000;
            v1 = v1 | 0x2000;
            v1 = v1 | 0x1;
            v1 = v1 | 0x2;
            a0 = v1 | 0x4;
            v1 = 0x840000;
            sw(a0, v1, -23460);  // kPersonaStockFlags
            break;
        case 0x1755ACu:  // table[0]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x001755ac (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001755C0 sub_1755C0 [datPersonaGetStockLevel] -- 300 bytes; frame 0x10: ra sp+0x0
// sub_1755C0(): the stock level 0..5 of kPersonaStockFlags: the size sub_175410 would return (12 / 10 / 9 / 8 / 6 / 4,
// inlined) mapped through jump table 0x7B64A0 on size - 4 to 5 / 4 / 3 / 2 / 1 / 0 -- the inverse of sub_1754A0. The
// table's other cases (sizes 5, 7, 11) reach K_Assert line 1086 and return 0xFFFF.
void sub_1755C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001755c0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0x840000;
    lw(v1, v0, -23460);  // kPersonaStockFlags
    v0 = v1 & 0x4;
    if (v0 == 0) {
        // 0x001755e8
        charge(ctx, 3);
        v0 = v1 & 0x2;
        if (v0 == 0) {
            // 0x00175600
            charge(ctx, 3);
            v0 = v1 & 0x1;
            if (v0 == 0) {
                // 0x00175618
                charge(ctx, 3);
                v0 = v1 & 0x2000;
                if (v0 == 0) {
                    // 0x00175630
                    charge(ctx, 3);
                    v0 = v1 & 0x1000;
                    if (v0 == 0) {
                        // 0x00175648
                        charge(ctx, 1);
                        v0 = 4;
                    } else {
                        // 0x0017563c
                        charge(ctx, 3);
                        v0 = 6;
                    }
                } else {
                    // 0x00175624
                    charge(ctx, 3);
                    v0 = 8;
                }
            } else {
                // 0x0017560c
                charge(ctx, 3);
                v0 = 9;
            }
        } else {
            // 0x001755f4
            charge(ctx, 3);
            v0 = 10;
        }
    } else {
        // 0x001755dc
        charge(ctx, 3);
        v0 = 12;
    }
    // 0x0017564c
    charge(ctx, 5);
    v0 = v0 & 0xFFFF;
    v0 = addiu(v0, -4);
    at = sltiu(v0, 9);
    if (at != 0) {
        // 0x00175660
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 25760);  // &jpt_175674 (sub_1755C0's jump table)
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x17567Cu:  // table[0]
            // 0x0017567c
            charge(ctx, 3);
            v0 = 0;
            break;
        case 0x175688u:  // table[2]
            // 0x00175688
            charge(ctx, 3);
            v0 = 1;
            break;
        case 0x175694u:  // table[4]
            // 0x00175694
            charge(ctx, 3);
            v0 = 2;
            break;
        case 0x1756A0u:  // table[5]
            // 0x001756a0
            charge(ctx, 3);
            v0 = 3;
            break;
        case 0x1756ACu:  // table[6]
            // 0x001756ac
            charge(ctx, 3);
            v0 = 4;
            break;
        case 0x1756B8u:  // table[8]
            // 0x001756b8
            charge(ctx, 3);
            v0 = 5;
            break;
        case 0x1756C4u:  // table[1, 3, 7]
        L_001756c4:
            charge(ctx, 6);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12920);  // "datPersona.c"
            a1 = 1086;
            jal(ctx, 0x1756D0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1086): returns
            v0 = 0xFFFF;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x001756dc (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // a size above 12 (unreachable: the size is one of the six above) shares the table's K_Assert case
    goto L_001756c4;
}

// 0x001756F0 sub_1756F0 [datPersonaCountStock] -- 252 bytes; leaf frame (no stack)
// sub_1756F0(): the number of used hero stock slots below the stock size (sub_175410 inlined).
void sub_1756F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x001756f0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0;
    v1 = 0x840000;
    lw(a0, v1, -23460);  // kPersonaStockFlags
    v1 = a0 & 0x4;
    if (v1 == 0) {
        // 0x00175714
        charge(ctx, 3);
        v1 = a0 & 0x2;
        if (v1 == 0) {
            // 0x0017572c
            charge(ctx, 3);
            v1 = a0 & 0x1;
            if (v1 == 0) {
                // 0x00175744
                charge(ctx, 3);
                v1 = a0 & 0x2000;
                if (v1 == 0) {
                    // 0x0017575c
                    charge(ctx, 3);
                    v1 = a0 & 0x1000;
                    if (v1 == 0) {
                        // 0x00175774
                        charge(ctx, 1);
                        v1 = 4;
                    } else {
                        // 0x00175768
                        charge(ctx, 3);
                        v1 = 6;
                    }
                } else {
                    // 0x00175750
                    charge(ctx, 3);
                    v1 = 8;
                }
            } else {
                // 0x00175738
                charge(ctx, 3);
                v1 = 9;
            }
        } else {
            // 0x00175720
            charge(ctx, 3);
            v1 = 10;
        }
    } else {
        // 0x00175708
        charge(ctx, 3);
        v1 = 12;
    }
    // 0x00175778
    charge(ctx, 6);
    a3 = 0;
    a2 = v1 & 0xFFFF;
    a0 = 0x830000;
    a0 = addiu(a0, 25088);  // &gGlobalWork
    for (;;) {
        // 0x001757d4
        charge(ctx, 4);
        v1 = a3 & 0xFFFF;
        v1 = slt(v1, a2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00175790
        charge(ctx, 13);
        a1 = dsll32(a3, 16);
        a1 = dsra32(a1, 16);
        v1 = sll(a1, 1);
        v1 = addu(v1, a1);
        v1 = sll(v1, 2);
        v1 = addu(v1, a1);
        v1 = sll(v1, 2);
        v1 = addu(a0, v1);
        lhu(v1, v1, 2476);
        v1 = v1 & 0x1;
        v1 = sltu(0, v1);
        if (v1 != 0) {
            // 0x001757c4
            charge(ctx, 2);
            v0 = addiu(v0, 1);
            v0 = v0 & 0xFFFF;
        }
        // 0x001757cc
        charge(ctx, 2);
        v1 = addiu(a3, 1);
        a3 = v1 & 0xFFFF;
    }
    // 0x001757e4
    charge(ctx, 2);
}

// 0x001757F0 sub_1757F0 [datPersonaClearStock] -- 48 bytes; frame 0x10: ra sp+0x0
// sub_1757F0(): clears the hero's 12 stock slots (624 bytes at gGlobalWork +0x9AC).
void sub_1757F0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001757f0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x830000;
    a0 = addiu(a0, 27564);  // &kHeroPersonaStock
    a1 = 0;
    a2 = 624;
    jal(ctx, 0x175808u, gen::fn_memset_00521408);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00175BE0 sub_175BE0 [datPersonaClearPc] -- 144 bytes; frame 0x10: ra sp+0x0
// sub_175BE0(pc): pc 1: kHeroPersonaIdx = -1 and the 12 stock slots cleared; else member pc's 52-byte persona (record
// +0xDC) cleared.
void sub_175BE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00175be0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);  // (s16)pc
    v0 = 1;
    if (v1 != v0) {  // a party member (pc 1 is the hero)
        // 0x00175c28
        charge(ctx, 14);
        v1 = addiu(v1, -2);  // 868 * (pc - 2) = (((pc - 2) * 31) * 7) * 4:
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x830000;
        v0 = addiu(v0, 16400);  // &kPartyRecords (pc 2's record)
        v0 = addu(v0, v1);
        a0 = addiu(v0, 220);
        a1 = 0;
        a2 = 52;
        jal(ctx, 0x175C58u, gen::fn_memset_00521408);
    } else {
        // 0x00175bfc
        charge(ctx, 11);
        v1 = si(-1);
        v0 = 0x830000;
        sh(v1, v0, 27560);  // kHeroPersonaIdx (gGlobalWork +0x9A8)
        a0 = 0x830000;
        a0 = addiu(a0, 27564);  // &kHeroPersonaStock
        a1 = 0;
        a2 = 624;
        jal(ctx, 0x175C18u, gen::fn_memset_00521408);
    }
    // 0x00175c60 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00175C70 sub_175C70 -- 48 bytes; frame 0x10: ra sp+0x0
// sub_175C70(): clears the 13,312-byte table at gGlobalWork +0xC1C (256 x 52 bytes: a persona record per persona id).
void sub_175C70(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00175c70
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x830000;
    a0 = addiu(a0, 28188);  // &gGlobalWork +0xC1C (256 x 52 bytes)
    a1 = 0;
    a2 = 13312;
    jal(ctx, 0x175C88u, gen::fn_memset_00521408);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00175CA0 sub_175CA0 [datPersonaIsPartyPersona] -- 52 bytes; leaf frame (no stack)
// sub_175CA0(persona): 0xC0 <= persona->id < 0xE0: a party member's persona (the ids sub_173C60 / sub_176210 take from
// the member table).
void sub_175CA0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00175ca0
    enter(ctx, 4);  // entry check point + this block's cycles
    lhu(v1, a0, pf::kId);  // persona->id
    v0 = slti(v1, 192);
    bool party = false;  // 0xC0 <= id < 0xE0
    if (v0 == 0) {
        // 0x00175cb0
        charge(ctx, 3);
        at = slti(v1, 224);
        party = at != 0;
    }
    if (party) {
        // 0x00175cbc
        charge(ctx, 3);
        v0 = 1;
    } else {
        // 0x00175cc8
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x00175ccc (the shared epilogue)
    charge(ctx, 2);
}

// 0x00176100 sub_176100 [datPersonaApplyLevelUp] -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_176100(persona, up): applies a level-up record (sub_175CE0's 40 bytes) to persona: level += up[0], base_stats[i]
// += up[34 + i]; K_Assert line 1362 on an id outside 1..255.
void sub_176100(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00176100
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lhu(v1, a0, pf::kId);
    bool ok = false;  // the K_Assert below runs unless both tests pass
    if (v1 != 0) {
        // 0x00176124
        charge(ctx, 3);
        v1 = slti(v1, 256);
        ok = v1 != 0;
    }
    if (!ok) {
        // 0x00176130
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12920);  // "datPersona.c"
        a1 = 1362;
        jal(ctx, 0x17613Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line 1362): returns
    }
    // 0x00176144
    charge(ctx, 7);
    lbu(a0, s1, pf::kLevel);
    lbu(v1, s0, 0);
    v1 = addu(a0, v1);
    sb(v1, s1, pf::kLevel);
    a2 = 0;
    for (;;) {
        // 0x00176184
        charge(ctx, 4);
        v1 = a2 & 0xFFFF;
        v1 = slti(v1, 5);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00176160
        charge(ctx, 9);
        a0 = a2 & 0xFFFF;
        v1 = addu(s0, a0);
        a1 = addu(s1, a0);
        lbu(a0, a1, pf::kBaseStats);
        lbu(v1, v1, pf::kUpStats);
        v1 = addu(a0, v1);
        sb(v1, a1, pf::kBaseStats);
        v1 = addiu(a2, 1);
        a2 = v1 & 0xFFFF;
    }
    // 0x00176194
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001761B0 sub_1761B0 [datPersonaCanLevelUp] -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1761B0(persona): level < 99 and exp >= the experience the next level needs (sub_176210(persona, level + 1)).
void sub_1761B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001761b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lbu(v1, a0, pf::kLevel);
    v0 = slti(v1, 99);
    if (v0 != 0) {
        // 0x001761dc
        charge(ctx, 7);
        v0 = addiu(v1, 1);
        a1 = v0 & 0xFFFF;
        jal(ctx, 0x1761E4u, gen::fn_sub_176210_00176210);
        lw(v1, s0, pf::kExp);
        v0 = sltu(v1, v0);
        v0 = v0 ^ 0x1;
    } else {
        // 0x001761d0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001761f8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
