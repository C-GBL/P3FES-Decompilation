// Phase 5 slice libs2: ACSS, part 2: the two player back ends -- ADX (over ADXT) and AIX (over AIXP) -- and their
// method tables (0x532118-0x532788).
// p3fes_handgen bodies (game/include/p3fes/game/hg_cpu.h); every statement, charge and check point is the
// generator's. Roles, proposed names and the record layouts: game/include/p3fes/game/libs2.h.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs2.h"

namespace p3fes::recomp_gen {
void fn__ZNKSt9basic_iosIcSt11char_traitsIcEE10exceptionsEv_00533450(p3fes::EEContext&);
void fn__ZNKSt9basic_iosIcSt11char_traitsIcEE3tieEv_0_00533590(p3fes::EEContext&);
void fn_atan2l_00531998(p3fes::EEContext&);
void fn_atan2l_5_0054d390(p3fes::EEContext&);
void fn_coshl_005319c8(p3fes::EEContext&);
void fn_coshl_4_0054d130(p3fes::EEContext&);
void fn_coshl_5_0054d3c0(p3fes::EEContext&);
void fn_cosl_005319b0(p3fes::EEContext&);
void fn_cosl_4_0054d118(p3fes::EEContext&);
void fn_cosl_5_0054d3a8(p3fes::EEContext&);
void fn_dpmul_00531230(p3fes::EEContext&);
void fn_dptofp_005318a0(p3fes::EEContext&);
void fn_expl_005319e0(p3fes::EEContext&);
void fn_expl_5_0054d3d8(p3fes::EEContext&);
void fn_fptodp_00530da0(p3fes::EEContext&);
void fn_hypotf_005319f8(p3fes::EEContext&);
void fn_hypotf_4_0054d160(p3fes::EEContext&);
void fn_hypotf_5_0054d3f0(p3fes::EEContext&);
void fn_litodp_00531720(p3fes::EEContext&);
void fn_log10_0052e9b8(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_pow_0052e9d0(p3fes::EEContext&);
void fn_pvalloc_0054d0a0(p3fes::EEContext&);
void fn_rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_00535398(p3fes::EEContext&);
void fn_setenv_0054d030(p3fes::EEContext&);
void fn_strncpy_00524828(p3fes::EEContext&);
void fn_sub_531A10_00531a10(p3fes::EEContext&);
void fn_sub_531A28_00531a28(p3fes::EEContext&);
void fn_sub_531A90_00531a90(p3fes::EEContext&);
void fn_sub_531AB8_00531ab8(p3fes::EEContext&);
void fn_sub_531AC0_00531ac0(p3fes::EEContext&);
void fn_sub_531AC8_00531ac8(p3fes::EEContext&);
void fn_sub_531AD0_00531ad0(p3fes::EEContext&);
void fn_sub_531B00_00531b00(p3fes::EEContext&);
void fn_sub_531BC0_00531bc0(p3fes::EEContext&);
void fn_sub_531C00_00531c00(p3fes::EEContext&);
void fn_sub_531D40_00531d40(p3fes::EEContext&);
void fn_sub_531D48_00531d48(p3fes::EEContext&);
void fn_sub_531D58_00531d58(p3fes::EEContext&);
void fn_sub_531D68_00531d68(p3fes::EEContext&);
void fn_sub_531DD8_00531dd8(p3fes::EEContext&);
void fn_sub_531E60_00531e60(p3fes::EEContext&);
void fn_sub_531F90_00531f90(p3fes::EEContext&);
void fn_sub_5320B8_005320b8(p3fes::EEContext&);
void fn_sub_5320E8_005320e8(p3fes::EEContext&);
void fn_sub_532118_00532118(p3fes::EEContext&);
void fn_sub_532180_00532180(p3fes::EEContext&);
void fn_sub_5321A8_005321a8(p3fes::EEContext&);
void fn_sub_532230_00532230(p3fes::EEContext&);
void fn_sub_532268_00532268(p3fes::EEContext&);
void fn_sub_532280_00532280(p3fes::EEContext&);
void fn_sub_532298_00532298(p3fes::EEContext&);
void fn_sub_5322B0_005322b0(p3fes::EEContext&);
void fn_sub_5322C8_005322c8(p3fes::EEContext&);
void fn_sub_5322E0_005322e0(p3fes::EEContext&);
void fn_sub_5322F8_005322f8(p3fes::EEContext&);
void fn_sub_532310_00532310(p3fes::EEContext&);
void fn_sub_532380_00532380(p3fes::EEContext&);
void fn_sub_5323A8_005323a8(p3fes::EEContext&);
void fn_sub_5323C0_005323c0(p3fes::EEContext&);
void fn_sub_5323F0_005323f0(p3fes::EEContext&);
void fn_sub_532420_00532420(p3fes::EEContext&);
void fn_sub_532438_00532438(p3fes::EEContext&);
void fn_sub_532440_00532440(p3fes::EEContext&);
void fn_sub_532458_00532458(p3fes::EEContext&);
void fn_sub_5324C0_005324c0(p3fes::EEContext&);
void fn_sub_5324E8_005324e8(p3fes::EEContext&);
void fn_sub_532580_00532580(p3fes::EEContext&);
void fn_sub_5325B8_005325b8(p3fes::EEContext&);
void fn_sub_5325D8_005325d8(p3fes::EEContext&);
void fn_sub_5325F0_005325f0(p3fes::EEContext&);
void fn_sub_532608_00532608(p3fes::EEContext&);
void fn_sub_532628_00532628(p3fes::EEContext&);
void fn_sub_532640_00532640(p3fes::EEContext&);
void fn_sub_532658_00532658(p3fes::EEContext&);
void fn_sub_532670_00532670(p3fes::EEContext&);
void fn_sub_532688_00532688(p3fes::EEContext&);
void fn_sub_5326F0_005326f0(p3fes::EEContext&);
void fn_sub_532718_00532718(p3fes::EEContext&);
void fn_sub_532740_00532740(p3fes::EEContext&);
void fn_sub_532748_00532748(p3fes::EEContext&);
void fn_sub_532760_00532760(p3fes::EEContext&);
void fn_sub_532768_00532768(p3fes::EEContext&);
void fn_sub_532788_00532788(p3fes::EEContext&);
void fn_sub_5327F0_005327f0(p3fes::EEContext&);
void fn_sub_532818_00532818(p3fes::EEContext&);
void fn_sub_532D30_00532d30(p3fes::EEContext&);
void fn_sub_532E08_00532e08(p3fes::EEContext&);
void fn_sub_532E10_00532e10(p3fes::EEContext&);
void fn_sub_532E70_00532e70(p3fes::EEContext&);
void fn_sub_532EC0_00532ec0(p3fes::EEContext&);
void fn_sub_532F10_00532f10(p3fes::EEContext&);
void fn_sub_532F60_00532f60(p3fes::EEContext&);
void fn_sub_5330A8_005330a8(p3fes::EEContext&);
void fn_sub_533160_00533160(p3fes::EEContext&);
void fn_sub_5331A8_005331a8(p3fes::EEContext&);
void fn_sub_5331F0_005331f0(p3fes::EEContext&);
void fn_sub_533230_00533230(p3fes::EEContext&);
void fn_sub_533238_00533238(p3fes::EEContext&);
void fn_sub_533340_00533340(p3fes::EEContext&);
void fn_sub_5334A8_005334a8(p3fes::EEContext&);
void fn_sub_533570_00533570(p3fes::EEContext&);
void fn_sub_533578_00533578(p3fes::EEContext&);
void fn_sub_533580_00533580(p3fes::EEContext&);
void fn_sub_5335A0_005335a0(p3fes::EEContext&);
void fn_sub_5335B0_005335b0(p3fes::EEContext&);
void fn_sub_5336C0_005336c0(p3fes::EEContext&);
void fn_sub_5337A8_005337a8(p3fes::EEContext&);
void fn_sub_533808_00533808(p3fes::EEContext&);
void fn_sub_533880_00533880(p3fes::EEContext&);
void fn_sub_533900_00533900(p3fes::EEContext&);
void fn_sub_533950_00533950(p3fes::EEContext&);
void fn_sub_5339A8_005339a8(p3fes::EEContext&);
void fn_sub_533A18_00533a18(p3fes::EEContext&);
void fn_sub_533A88_00533a88(p3fes::EEContext&);
void fn_sub_533AC8_00533ac8(p3fes::EEContext&);
void fn_sub_533CA0_00533ca0(p3fes::EEContext&);
void fn_sub_533CA8_00533ca8(p3fes::EEContext&);
void fn_sub_533CC0_00533cc0(p3fes::EEContext&);
void fn_sub_533CD0_00533cd0(p3fes::EEContext&);
void fn_sub_533E98_00533e98(p3fes::EEContext&);
void fn_sub_533F10_00533f10(p3fes::EEContext&);
void fn_sub_534010_00534010(p3fes::EEContext&);
void fn_sub_534308_00534308(p3fes::EEContext&);
void fn_sub_5343D8_005343d8(p3fes::EEContext&);
void fn_sub_534488_00534488(p3fes::EEContext&);
void fn_sub_534530_00534530(p3fes::EEContext&);
void fn_sub_534538_00534538(p3fes::EEContext&);
void fn_sub_534678_00534678(p3fes::EEContext&);
void fn_sub_534728_00534728(p3fes::EEContext&);
void fn_sub_5347C0_005347c0(p3fes::EEContext&);
void fn_sub_534888_00534888(p3fes::EEContext&);
void fn_sub_534960_00534960(p3fes::EEContext&);
void fn_sub_5349C8_005349c8(p3fes::EEContext&);
void fn_sub_5349F8_005349f8(p3fes::EEContext&);
void fn_sub_534A60_00534a60(p3fes::EEContext&);
void fn_sub_534A88_00534a88(p3fes::EEContext&);
void fn_sub_534B60_00534b60(p3fes::EEContext&);
void fn_sub_534C58_00534c58(p3fes::EEContext&);
void fn_sub_534C98_00534c98(p3fes::EEContext&);
void fn_sub_534DB0_00534db0(p3fes::EEContext&);
void fn_sub_535050_00535050(p3fes::EEContext&);
void fn_sub_5350D0_005350d0(p3fes::EEContext&);
void fn_sub_535170_00535170(p3fes::EEContext&);
void fn_sub_535178_00535178(p3fes::EEContext&);
void fn_sub_5351B0_005351b0(p3fes::EEContext&);
void fn_sub_5351C0_005351c0(p3fes::EEContext&);
void fn_sub_5351E8_005351e8(p3fes::EEContext&);
void fn_sub_535250_00535250(p3fes::EEContext&);
void fn_sub_535278_00535278(p3fes::EEContext&);
void fn_sub_5352F8_005352f8(p3fes::EEContext&);
void fn_sub_535348_00535348(p3fes::EEContext&);
void fn_sub_535350_00535350(p3fes::EEContext&);
void fn_sub_535358_00535358(p3fes::EEContext&);
void fn_sub_535388_00535388(p3fes::EEContext&);
void fn_sub_535390_00535390(p3fes::EEContext&);
void fn_sub_5353A0_005353a0(p3fes::EEContext&);
void fn_sub_5353A8_005353a8(p3fes::EEContext&);
void fn_sub_5355B8_005355b8(p3fes::EEContext&);
void fn_sub_535610_00535610(p3fes::EEContext&);
void fn_sub_535618_00535618(p3fes::EEContext&);
void fn_sub_535668_00535668(p3fes::EEContext&);
void fn_sub_53AE08_0053ae08(p3fes::EEContext&);
void fn_sub_53EA90_0053ea90(p3fes::EEContext&);
void fn_sub_53EC20_0053ec20(p3fes::EEContext&);
void fn_sub_547BC0_00547bc0(p3fes::EEContext&);
void fn_sub_547F30_00547f30(p3fes::EEContext&);
void fn_sub_548048_00548048(p3fes::EEContext&);
void fn_sub_548678_00548678(p3fes::EEContext&);
void fn_sub_548768_00548768(p3fes::EEContext&);
void fn_sub_549480_00549480(p3fes::EEContext&);
void fn_sub_549530_00549530(p3fes::EEContext&);
void fn_sub_54A138_0054a138(p3fes::EEContext&);
void fn_sub_54A3C0_0054a3c0(p3fes::EEContext&);
void fn_sub_54A530_0054a530(p3fes::EEContext&);
void fn_sub_54B088_0054b088(p3fes::EEContext&);
void fn_sub_54B2E8_0054b2e8(p3fes::EEContext&);
void fn_sub_54B3A0_0054b3a0(p3fes::EEContext&);
void fn_sub_54B4D0_0054b4d0(p3fes::EEContext&);
void fn_sub_54D0B8_0054d0b8(p3fes::EEContext&);
void fn_sub_54D0D0_0054d0d0(p3fes::EEContext&);
void fn_sub_54D0E8_0054d0e8(p3fes::EEContext&);
void fn_sub_54D178_0054d178(p3fes::EEContext&);
void fn_sub_54D190_0054d190(p3fes::EEContext&);
void fn_sub_54D1A8_0054d1a8(p3fes::EEContext&);
void fn_sub_54D1C0_0054d1c0(p3fes::EEContext&);
void fn_sub_54D1D8_0054d1d8(p3fes::EEContext&);
void fn_sub_54D1F0_0054d1f0(p3fes::EEContext&);
void fn_sub_54D208_0054d208(p3fes::EEContext&);
void fn_sub_54D238_0054d238(p3fes::EEContext&);
void fn_sub_54D250_0054d250(p3fes::EEContext&);
void fn_sub_54D268_0054d268(p3fes::EEContext&);
void fn_sub_54D280_0054d280(p3fes::EEContext&);
void fn_sub_54D298_0054d298(p3fes::EEContext&);
void fn_sub_54D2B0_0054d2b0(p3fes::EEContext&);
void fn_sub_54D2C8_0054d2c8(p3fes::EEContext&);
void fn_sub_54D2E0_0054d2e0(p3fes::EEContext&);
void fn_sub_54D2F8_0054d2f8(p3fes::EEContext&);
void fn_sub_54D310_0054d310(p3fes::EEContext&);
void fn_sub_54D328_0054d328(p3fes::EEContext&);
void fn_sub_54D340_0054d340(p3fes::EEContext&);
void fn_sub_54D358_0054d358(p3fes::EEContext&);
void fn_sub_54D378_0054d378(p3fes::EEContext&);
void fn_sub_54D408_0054d408(p3fes::EEContext&);
void fn_sub_54D420_0054d420(p3fes::EEContext&);
void fn_sub_54D438_0054d438(p3fes::EEContext&);
void fn_sub_54D450_0054d450(p3fes::EEContext&);
void fn_sub_54D468_0054d468(p3fes::EEContext&);
void fn_sub_54D490_0054d490(p3fes::EEContext&);
void fn_sub_54D4B8_0054d4b8(p3fes::EEContext&);
void fn_sub_54D4F0_0054d4f0(p3fes::EEContext&);
void fn_sub_54F5C0_0054f5c0(p3fes::EEContext&);
void fn_sub_54F708_0054f708(p3fes::EEContext&);
void fn_sub_5526B0_005526b0(p3fes::EEContext&);
void fn_sub_552760_00552760(p3fes::EEContext&);
void fn_sub_552830_00552830(p3fes::EEContext&);
void fn_sub_5528B0_005528b0(p3fes::EEContext&);
void fn_sub_552BD0_00552bd0(p3fes::EEContext&);
void fn_sub_552EA8_00552ea8(p3fes::EEContext&);
void fn_sub_552EC8_00552ec8(p3fes::EEContext&);
void fn_sub_553028_00553028(p3fes::EEContext&);
void fn_sub_5530D0_005530d0(p3fes::EEContext&);
void fn_sub_553188_00553188(p3fes::EEContext&);
void fn_sub_553230_00553230(p3fes::EEContext&);
void fn_sub_5533D8_005533d8(p3fes::EEContext&);
void fn_sub_553590_00553590(p3fes::EEContext&);
void fn_sub_553658_00553658(p3fes::EEContext&);
void fn_sub_5540E8_005540e8(p3fes::EEContext&);
void fn_sub_5649A8_005649a8(p3fes::EEContext&);
void fn_sub_5649C0_005649c0(p3fes::EEContext&);
void fn_sub_564A20_00564a20(p3fes::EEContext&);
void fn_sub_564A38_00564a38(p3fes::EEContext&);
void fn_sub_564EF8_00564ef8(p3fes::EEContext&);
void fn_sub_564FE8_00564fe8(p3fes::EEContext&);
void fn_sub_5655E8_005655e8(p3fes::EEContext&);
void fn_unsetenv_0054d060(p3fes::EEContext&);
void fn_valloc_0054d080(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace libs2;

// 0x00532118 sub_532118 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADX back end create: in a caller's work of at least 12 bytes (else an error and 0), reset (named by its error
//   text). [ACSSBADX_Create]
void sub_532118(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532118
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = sltiu(a1, 12);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x00532130
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 1376);  // "E2003052800 ACSSBADX_Create : Work pointor is NULL."
        goto L_00532150;
    }
    // 0x00532140
    charge(ctx, 2);
    if (a1 == 0) {
        // 0x00532160
        charge(ctx, 3);
        jal(ctx, 0x532160u, gen::fn_sub_532440_00532440);
        v0 = s0;
    } else {
        // 0x00532148
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 1432);  // "E2003091200 ACSSBADX_Create : Work size is too small."
    L_00532150:
        charge(ctx, 4);
        jal(ctx, 0x532150u, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x0053216c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00532180 sub_532180 -- 36 bytes; frame 0x10: ra sp+0x0
// ADX back end destroy: the reset, when it exists. [ACSSBADX_Destroy]
void sub_532180(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532180
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00532198
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0053218c
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_532440_00532440(ctx);  // tail call
}

// 0x005321A8 sub_5321A8 -- 132 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADX back end method 0, create the player: ADXT_Create (or the 0x547F30 variant when the configuration asks for it)
//   in the work after the 12-byte back end; keeps the channel count; an error and 0 on failure (named by its error
//   text). [ACSSBADX_CreateHndl]
void sub_5321A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005321a8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    a1 = a2;
    lw(v0, s1, 8);
    a0 = a1;
    if (v0 == 0) {
        // 0x005321e0
        charge(ctx, 4);
        lw(a0, s1, 0);
        a2 = addiu(a3, -12);
        jal(ctx, 0x5321E4u, gen::fn_sub_547BC0_00547bc0);
        sw(v0, s0, bad::kHndl);
    } else {
        // 0x005321d0
        charge(ctx, 4);
        a1 = addiu(a3, -12);
        jal(ctx, 0x5321D0u, gen::fn_sub_547F30_00547f30);
        sw(v0, s0, bad::kHndl);
    }
    // 0x005321f0
    charge(ctx, 3);
    lw(v0, s0, bad::kHndl);
    if (v0 != 0) {
        lw(v1, s1, 0);
        // 0x00532210
        charge(ctx, 2);
        v0 = 1;
        sw(v1, s0, bad::kNch);
    } else {
        // 0x005321fc
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 1488);  // "E2003052802 ACSSBADX_CreateHndl : Failed to create handle."
        jal(ctx, 0x532200u, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x00532218 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00532230 sub_532230 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADX back end method 1: destroy the ADXT player. [ACSSBADX_DestroyHndl]
void sub_532230(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532230
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, bad::kHndl);
    a0 = v0;
    if (v0 != 0) {
        // 0x0053224c
        charge(ctx, 3);
        jal(ctx, 0x53224Cu, gen::fn_sub_548048_00548048);
        sw(zero, s0, bad::kHndl);
    }
    // 0x00532258 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00532268 sub_532268 -- 24 bytes; frame 0x10: ra sp+0x0
// ADX back end method 2: start a named file (ADXT_StartFname). [ACSSBADX_StartFname]
void sub_532268(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532268
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_54B2E8_0054b2e8(ctx);  // tail call
}

// 0x00532280 sub_532280 -- 24 bytes; frame 0x10: ra sp+0x0
// ADX back end method 3: start a partition file (ADXT_StartAfs). [ACSSBADX_StartAfs]
void sub_532280(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532280
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_54B088_0054b088(ctx);  // tail call
}

// 0x00532298 sub_532298 -- 24 bytes; frame 0x10: ra sp+0x0
// ADX back end method 4: start from memory (0x54B3A0). [ACSSBADX_StartMem]
void sub_532298(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532298
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_54B3A0_0054b3a0(ctx);  // tail call
}

// 0x005322B0 sub_5322B0 -- 24 bytes; frame 0x10: ra sp+0x0
// ADX back end method 5: start a memory index entry (ADXT_StartMemIdx). [ACSSBADX_StartMemIdx]
void sub_5322B0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005322b0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_54B4D0_0054b4d0(ctx);  // tail call
}

// 0x005322C8 sub_5322C8 -- 24 bytes; frame 0x10: ra sp+0x0
// ADX back end method 6: stop (ADXT_Stop). [ACSSBADX_Stop]
void sub_5322C8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005322c8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_548678_00548678(ctx);  // tail call
}

// 0x005322E0 sub_5322E0 -- 24 bytes; frame 0x10: ra sp+0x0
// ADX back end method 7: pause / resume (ADXT_Pause). [ACSSBADX_Pause]
void sub_5322E0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005322e0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_54A3C0_0054a3c0(ctx);  // tail call
}

// 0x005322F8 sub_5322F8 -- 24 bytes; frame 0x10: ra sp+0x0
// ADX back end method 8: the pause state (ADXT_GetStatPause). [ACSSBADX_GetStatPause]
void sub_5322F8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005322f8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_54A530_0054a530(ctx);  // tail call
}

// 0x00532310 sub_532310 -- 108 bytes; frame 0x10: ra sp+0x0
// ADX back end method 9: the status, ADXT's 0..6 mapped through the table 0x7C0610 (0 stop, 1 preparing = opening /
//   buffering, 2 playing = playing / decode end, 3 play end, 4 error; above 6 also 4). [ACSSBADX_GetStat]
void sub_532310(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532310
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    link(ctx, 0x532318u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, 4);
    call(ctx, gen::fn_sub_548768_00548768);
    v1 = v0;
    v0 = sltiu(v1, 7);
    if (v0 == 0) {
        v1 = 4;
    } else {
        // 0x00532330
        charge(ctx, 6);
        v0 = sll(v1, 2);
        v1 = 0x7C0000;
        v1 = addu(v1, v0);
        lw(v1, v1, 1552);
        switch (v1.u()) {
        case 0x532348u:  // table[0]
            // 0x00532348
            charge(ctx, 2);
            v1 = 0;
            break;
        case 0x532350u:  // table[1, 2]
            // 0x00532350
            charge(ctx, 2);
            v1 = 1;
            break;
        case 0x532358u:  // table[3, 4]
            // 0x00532358
            charge(ctx, 2);
            v1 = 2;
            break;
        case 0x532360u:  // table[5]
            // 0x00532360
            charge(ctx, 2);
            v1 = 3;
            break;
        case 0x532368u:  // table[6]
            // 0x00532368
            charge(ctx, 1);
            v1 = 4;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x0053236c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    v0 = v1;
    sp = addiu(sp, 0x10);
}

// 0x00532380 sub_532380 -- 36 bytes; frame 0x10: ra sp+0x0
// ADX back end method 10: set the volume (clamped below at -960). [ACSSBADX_SetOutVol]
void sub_532380(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532380
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = si(-960);
    sd(ra, sp, 0x0);
    v0 = slti(a1, -960);
    if (v0 != 0) a1 = v1;
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_549480_00549480(ctx);  // tail call
}

// 0x005323A8 sub_5323A8 -- 24 bytes; frame 0x10: ra sp+0x0
// ADX back end method 11: the volume (0x549530). [ACSSBADX_GetOutVol]
void sub_5323A8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005323a8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_549530_00549530(ctx);  // tail call
}

// 0x005323C0 sub_5323C0 -- 44 bytes; frame 0x10: ra sp+0x0
// ADX back end method 12: set a track's volume -- track 0 only. [ACSSBADX_SetTrackVol]
void sub_5323C0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005323c0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a1 != 0) {
        // 0x005323e0
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005323cc
    charge(ctx, 5);
    lw(a0, a0, 4);
    a1 = a2;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_549480_00549480(ctx);  // tail call
}

// 0x005323F0 sub_5323F0 -- 48 bytes; frame 0x10: ra sp+0x0
// ADX back end method 13: a track's volume -- track 0 only, else 0. [ACSSBADX_GetTrackVol]
void sub_5323F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005323f0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a1 != 0) {
        // 0x00532410
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        v0 = 0;
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005323fc
    charge(ctx, 4);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_549530_00549530(ctx);  // tail call
}

// 0x00532420 sub_532420 -- 24 bytes; frame 0x10: ra sp+0x0
// ADX back end method 14: set the loop flag (ADXT_SetLpFlg). [ACSSBADX_SetLpFlg]
void sub_532420(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532420
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_54A138_0054a138(ctx);  // tail call
}

// 0x00532438 sub_532438 -- 8 bytes; leaf frame (no stack)
// ADX back end method 15: the ADXT handle (+4). [ACSSBADX_GetHndl]
void sub_532438(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00532438
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, bad::kHndl);
}

// 0x00532440 sub_532440 -- 24 bytes; leaf frame (no stack)
// ADX back end reset: the method table 0x7C0520, no player, no channels. [acssbadx_Reset]
void sub_532440(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4};
    // 0x00532440
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7C0000;
    sw(zero, a0, bad::kNch);
    v0 = addiu(v0, 1312);  // &0x7C0520
    sw(zero, a0, bad::kHndl);
    sw(v0, a0, bad::kVtbl);
}

// 0x00532458 sub_532458 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// AIX back end create: in a caller's work of at least 16 bytes (else an error and 0), reset (named by its error
//   text). [ACSSBAIX_Create]
void sub_532458(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532458
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = sltiu(a1, 16);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x00532470
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 1648);  // "E2003052803 ACSSBAIX_Create : Work pointor is NULL."
        goto L_00532490;
    }
    // 0x00532480
    charge(ctx, 2);
    if (a1 == 0) {
        // 0x005324a0
        charge(ctx, 3);
        jal(ctx, 0x5324A0u, gen::fn_sub_532768_00532768);
        v0 = s0;
    } else {
        // 0x00532488
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 1704);  // "E2003091201 ACSSBAIX_Create : Work size is too small."
    L_00532490:
        charge(ctx, 4);
        jal(ctx, 0x532490u, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x005324ac (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005324C0 sub_5324C0 -- 36 bytes; frame 0x10: ra sp+0x0
// AIX back end destroy: the reset, when it exists. [ACSSBAIX_Destroy]
void sub_5324C0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005324c0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x005324d8
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005324cc
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_532768_00532768(ctx);  // tail call
}

// 0x005324E8 sub_5324E8 -- 148 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// AIX back end method 0, create the player: an AIXP handle (0x5528B0 or 0x552830 by the configuration) in the work
//   after the 16-byte back end; keeps channels and tracks; an error and 0 on failure. [ACSSBAIX_CreateHndl]
void sub_5324E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005324e8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = a3;
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    a3 = addiu(v1, -16);
    lw(v0, s0, 8);
    a1 = a2;
    if (v0 == 0) {
        // 0x00532528
        charge(ctx, 4);
        lw(a0, s0, 4);
        link(ctx, 0x53252Cu);  // $ra first: the delay slot below depends on it
        lw(a1, s0, 0);
        call(ctx, gen::fn_sub_552830_00552830);
        sw(v0, s1, bai::kHndl);
    } else {
        // 0x00532514
        charge(ctx, 5);
        lw(a0, s0, 4);
        a2 = a3;
        jal(ctx, 0x532518u, gen::fn_sub_5528B0_005528b0);
        sw(v0, s1, bai::kHndl);
    }
    // 0x00532538
    charge(ctx, 3);
    lw(v0, s1, bai::kHndl);
    if (v0 != 0) {
        lw(a0, s0, 4);
        // 0x00532558
        charge(ctx, 4);
        v0 = 1;
        sw(a0, s1, bai::kNumTrack);
        lw(v1, s0, 0);
        sw(v1, s1, bai::kNch);
    } else {
        // 0x00532544
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 1760);  // "E2003052805 ACSSBAIX_Create : Failed to create handle."
        jal(ctx, 0x532548u, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x00532568 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00532580 sub_532580 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// AIX back end method 1: destroy the AIXP handle. [ACSSBAIX_DestroyHndl]
void sub_532580(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532580
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, bai::kHndl);
    a0 = v0;
    if (v0 != 0) {
        // 0x0053259c
        charge(ctx, 3);
        jal(ctx, 0x53259Cu, gen::fn_sub_552BD0_00552bd0);
        sw(zero, s0, bai::kHndl);
    }
    // 0x005325a8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005325B8 sub_5325B8 -- 28 bytes; frame 0x10: ra sp+0x0
// AIX back end method 2: start a named file (0x552EA8). [ACSSBAIX_StartFname]
void sub_5325B8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005325b8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 0;
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_552EA8_00552ea8(ctx);  // tail call
}

// 0x005325D8 sub_5325D8 -- 24 bytes; frame 0x10: ra sp+0x0
// AIX back end method 3: start a partition file (0x552EC8). [ACSSBAIX_StartAfs]
void sub_5325D8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005325d8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_552EC8_00552ec8(ctx);  // tail call
}

// 0x005325F0 sub_5325F0 -- 24 bytes; frame 0x10: ra sp+0x0
// AIX back end method 4: start from memory (0x553028). [ACSSBAIX_StartMem]
void sub_5325F0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005325f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_553028_00553028(ctx);  // tail call
}

// 0x00532608 sub_532608 -- 28 bytes; frame 0x10: ra sp+0x0
// AIX back end method 5: memory index starts are not supported (an error; named by its error text).
//   [ACSSBAIX_StartMemIdx]
void sub_532608(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532608
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x7C0000;
    sd(ra, sp, 0x0);
    a0 = addiu(a0, 1816);  // "E2003060601 ACSSBAIX_StartMemIdx : Not supported."
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_531A10_00531a10(ctx);  // tail call
}

// 0x00532628 sub_532628 -- 24 bytes; frame 0x10: ra sp+0x0
// AIX back end method 6: stop (0x5530D0). [ACSSBAIX_Stop]
void sub_532628(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532628
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5530D0_005530d0(ctx);  // tail call
}

// 0x00532640 sub_532640 -- 24 bytes; frame 0x10: ra sp+0x0
// AIX back end method 7: pause / resume (0x553590). [ACSSBAIX_Pause]
void sub_532640(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532640
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_553590_00553590(ctx);  // tail call
}

// 0x00532658 sub_532658 -- 24 bytes; frame 0x10: ra sp+0x0
// AIX back end method 8: the pause state (0x553658, whose error text names it AIXP_GetStatPause).
//   [ACSSBAIX_GetStatPause]
void sub_532658(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532658
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_553658_00553658(ctx);  // tail call
}

// 0x00532670 sub_532670 -- 24 bytes; frame 0x10: ra sp+0x0
// AIX back end method 9: the status (0x553188, the AIXP handle's +1). [ACSSBAIX_GetStat]
void sub_532670(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532670
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_553188_00553188(ctx);  // tail call
}

// 0x00532688 sub_532688 -- 104 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// AIX back end method 10: set the volume of every track (method 12 per track, +12 tracks). [ACSSBAIX_SetOutVol]
void sub_532688(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532688
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = 0;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v0, s1, bai::kNumTrack);
    s2 = a1;
    if (i64(v0) > 0) {
        // 0x005326b0
        charge(ctx, 2);
        a1 = s0;
        for (;;) {
            // 0x005326b8
            charge(ctx, 8);
            s0 = addiu(s0, 1);
            a0 = s1;
            a2 = s2;
            jal(ctx, 0x5326C0u, gen::fn_sub_532718_00532718);
            lw(v0, s1, bai::kNumTrack);
            v0 = slt(s0, v0);
            a1 = s0;
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x005326d8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005326F0 sub_5326F0 -- 36 bytes; frame 0x10: ra sp+0x0
// AIX back end method 11: the volume, read from track 0's ADXT player. [ACSSBAIX_GetOutVol]
void sub_5326F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005326f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(ra, sp, 0x0);
    link(ctx, 0x5326FCu);  // $ra first: the delay slot below depends on it
    lw(a0, a0, 4);
    call(ctx, gen::fn_sub_553230_00553230);
    ld(ra, sp, 0x0);
    a0 = v0;
    sp = addiu(sp, 0x10);
    gen::fn_sub_549530_00549530(ctx);  // tail call
}

// 0x00532718 sub_532718 -- 36 bytes; frame 0x10: ra sp+0x0
// AIX back end method 12: set one track's volume (clamped below at -960; 0x5540E8). [ACSSBAIX_SetTrackVol]
void sub_532718(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532718
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = si(-960);
    sd(ra, sp, 0x0);
    v0 = slti(a2, -960);
    if (v0 != 0) a2 = v1;
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5540E8_005540e8(ctx);  // tail call
}

// 0x00532740 sub_532740 -- 8 bytes; leaf frame (no stack)
// AIX back end method 13: a track's volume -- always 0. [ACSSBAIX_GetTrackVol]
void sub_532740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00532740
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00532748 sub_532748 -- 24 bytes; frame 0x10: ra sp+0x0
// AIX back end method 14: set the loop flag (0x5533D8, the AIXP handle's +432). [ACSSBAIX_SetLpFlg]
void sub_532748(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532748
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5533D8_005533d8(ctx);  // tail call
}

// 0x00532760 sub_532760 -- 8 bytes; leaf frame (no stack)
// AIX back end method 15: the AIXP handle (+4). [ACSSBAIX_GetHndl]
void sub_532760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00532760
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, bai::kHndl);
}

// 0x00532768 sub_532768 -- 28 bytes; leaf frame (no stack)
// AIX back end reset: the method table 0x7C0630, no handle, no channels, no tracks. [acssbaix_Reset]
void sub_532768(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4};
    // 0x00532768
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0x7C0000;
    sw(zero, a0, bai::kNumTrack);
    v0 = addiu(v0, 1584);  // &0x7C0630
    sw(zero, a0, bai::kHndl);
    sw(v0, a0, bai::kVtbl);
    sw(zero, a0, bai::kNch);
}

}  // namespace p3fes::game
