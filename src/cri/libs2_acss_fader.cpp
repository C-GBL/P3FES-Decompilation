// Phase 5 slice libs2: ACSS, part 1: the SVM lock thunks, the error reporter and the volume fader
// (0x531998-0x532118).
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

// 0x00531998 atan2l -- 20 bytes; frame 0x10: ra sp+0x0
// ACSS's copy of the SVM resource lock (type 2): a tail call into SVM. [acss_LockRsc]
void atan2l(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00531998
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5649A8_005649a8(ctx);  // tail call
}

// 0x005319B0 cosl -- 20 bytes; frame 0x10: ra sp+0x0
// ACSS's copy of the SVM resource unlock (type 2). [acss_UnlockRsc]
void cosl(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005319b0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564A20_00564a20(ctx);  // tail call
}

// 0x005319C8 coshl -- 20 bytes; frame 0x10: ra sp+0x0
// ACSS's copy of the SVM lock, type 3: the sound methods that touch both players take it. [acss_Lock]
void coshl(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005319c8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5649C0_005649c0(ctx);  // tail call
}

// 0x005319E0 expl -- 20 bytes; frame 0x10: ra sp+0x0
// ACSS's copy of the SVM unlock, type 3. [acss_Unlock]
void expl(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005319e0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564A38_00564a38(ctx);  // tail call
}

// 0x005319F8 hypotf -- 20 bytes; frame 0x10: ra sp+0x0
// ACSS's copy of SVM's test-and-set (a guarded flag set to 1: returns 1 when it was not 1 before). [acss_TestAndSet]
void hypotf(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005319f8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5655E8_005655e8(ctx);  // tail call
}

// 0x00531A10 sub_531A10 -- 20 bytes; frame 0x10: ra sp+0x0
// Report an ACSS error: the text goes to the ADX error reporter 0x53AE08. [acss_CallErr]
void sub_531A10(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00531a10
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
}

// 0x00531A28 sub_531A28 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Fader create: in a caller's work of at least 68 bytes (else an error and 0), reset (named by its error text).
//   [ACSFDR_Create]
void sub_531A28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00531a28
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = sltiu(a1, 68);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x00531a40
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 1192);  // "E2003052803 ACSFDR_Create : Work pointor is NULL."
        goto L_00531a60;
    }
    // 0x00531a50
    charge(ctx, 2);
    if (a1 == 0) {
        // 0x00531a70
        charge(ctx, 3);
        jal(ctx, 0x531A70u, gen::fn_sub_531D68_00531d68);
        v0 = s0;
    } else {
        // 0x00531a58
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 1248);  // "E2003091202 ACSFDR_Create : Work size is too small."
    L_00531a60:
        charge(ctx, 4);
        jal(ctx, 0x531A60u, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x00531a7c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00531A90 sub_531A90 -- 36 bytes; frame 0x10: ra sp+0x0
// Fader destroy: the reset, when the fader exists. [ACSFDR_Destroy]
void sub_531A90(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00531a90
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00531aa8
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00531a9c
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_531D68_00531d68(ctx);  // tail call
}

// 0x00531AB8 sub_531AB8 -- 8 bytes; leaf frame (no stack)
// Fader state (+0, s8): 0 idle, 1 waiting out the delay, 2 fading, 3 holding at the target. [ACSFDR_GetStat]
void sub_531AB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00531ab8
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, fdr::kStat);
}

// 0x00531AC0 sub_531AC0 -- 8 bytes; leaf frame (no stack)
// Fader frame counter (+8). [ACSFDR_GetTime]
void sub_531AC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00531ac0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, fdr::kTime);
}

// 0x00531AC8 sub_531AC8 -- 8 bytes; leaf frame (no stack)
// Fader volume (+28, dB x 10: 0 full, -960 silent). [ACSFDR_GetVolume]
void sub_531AC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00531ac8
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, fdr::kVolume);
}

// 0x00531AD0 sub_531AD0 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Fader set volume: +28 = the volume, +32 = its level (sub_531F90). [ACSFDR_SetVolume]
void sub_531AD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00531ad0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    link(ctx, 0x531AE0u);  // $ra first: the delay slot below depends on it
    sw(a1, s0, fdr::kVolume);
    call(ctx, gen::fn_sub_531F90_00531f90);
    sw(v0, s0, fdr::kLevel);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00531B00 sub_531B00 -- 192 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// Fader start (fader, target volume, frames, delay, hold): the old target kept as the previous one, the per-frame
//   level step from the current volume to the target in the given frames (sub_531DD8), delay and hold frames; frames
//   > 0: state 1 (the delay counts first, then the fade); frames <= 0: the volume jumps to the target and state 2
//   (the next update finishes). [ACSFDR_Start]
void sub_531B00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00531b00
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = t0;
    sd(s2, sp, 0x10);
    s2 = a3;
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(s4, sp, 0x20);
    s4 = a0;
    sd(ra, sp, 0x28);
    a2 = s0;
    a3 = s3;
    lw(v0, s4, fdr::kTarget);
    lw(a1, s4, fdr::kVolume);
    sw(s0, s4, fdr::kTarget);
    link(ctx, 0x531B44u);  // $ra first: the delay slot below depends on it
    sw(v0, s4, fdr::kPrevTarget);
    call(ctx, gen::fn_sub_531DD8_00531dd8);
    a0 = s4;
    a1 = s0;
    sw(v0, s4, fdr::kStep);
    sw(s2, s4, fdr::kDelay);
    sw(s1, s4, fdr::kHold);
    sw(zero, s4, fdr::kTime);
    sw(zero, s4, fdr::kEndTime);
    if (i64(s3) > 0) {
        // 0x00531b98
        charge(ctx, 10);
        v0 = 1;
        ld(s0, sp, 0x0);
        sb(v0, s4, fdr::kStat);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x00531b6c
    charge(ctx, 10);
    v0 = 2;
    ld(s0, sp, 0x0);
    sb(v0, s4, fdr::kStat);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    gen::fn_sub_531AD0_00531ad0(ctx);  // tail call
}

// 0x00531BC0 sub_531BC0 -- 60 bytes; leaf frame (no stack)
// Fader reverse: swap target and previous target, negate the step; a holding fader fades again (state 2).
//   [ACSFDR_Reverse]
void sub_531BC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00531bc0
    enter(ctx, 11);  // entry check point + this block's cycles
    a3 = a0;
    a2 = 3;
    lw(v0, a3, 4);
    lw(a1, a3, 36);
    lw(v1, a3, 40);
    v0 = subu(0, v0);
    lb(a0, a3, 0);
    sw(v1, a3, 36);
    sw(a1, a3, 40);
    sw(v0, a3, 4);
    if (a0 == a2) {
        // 0x00531bec
        charge(ctx, 2);
        v0 = 2;
        sb(v0, a3, 0);
    }
    // 0x00531bf4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00531C00 sub_531C00 -- 316 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Fader per-frame update: count the frame; after the delay call the start callback; step the level (clamped to
//   0..3238200), convert it back to a volume, stop at the target (state 3) and after the hold frames call the end
//   callback and go idle. [ACSFDR_ExecServer]
void sub_531C00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00531c00
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x531C10u, gen::fn_sub_531AB8_00531ab8);
    s1 = v0;
    if (s1 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00531c24
        charge(ctx, 6);
        lw(v0, s0, fdr::kTime);
        lw(v1, s0, fdr::kDelay);
        v0 = addiu(v0, 1);
        v1 = slt(v0, v1);
        sw(v0, s0, fdr::kTime);
        if (v1 == 0) {
            // 0x00531c3c
            charge(ctx, 3);
            v0 = 1;
            if (s1 != v0) {
                v0 = 2;
            } else {
                // 0x00531c48
                charge(ctx, 5);
                s1 = 2;
                a0 = s0;
                link(ctx, 0x531C50u);  // $ra first: the delay slot below depends on it
                sb(s1, s0, fdr::kStat);
                call(ctx, gen::fn_sub_5320B8_005320b8);
                v0 = 2;
            }
            // 0x00531c5c
            charge(ctx, 2);
            cc = s1 != v0;  // the condition, before the delay slot changes it
            v0 = 3;
            if (!cc) {
                // 0x00531c64
                charge(ctx, 17);
                lw(v0, s0, fdr::kLevel);
                a2 = 0x310000;
                lw(a3, s0, fdr::kStep);
                a2 = a2 | 0x6938;  // &0x316938
                a1 = a2;
                a0 = s0;
                v0 = addu(v0, a3);
                v1 = slti(v0, 0);
                if (v1 != 0) v0 = 0;
                a2 = slt(a2, v0);
                if (a2 == 0) a1 = v0;
                link(ctx, 0x531C90u);  // $ra first: the delay slot below depends on it
                sw(a1, s0, fdr::kLevel);
                call(ctx, gen::fn_sub_531E60_00531e60);
                lw(a0, s0, fdr::kStep);
                v1 = v0;
                sw(v1, s0, fdr::kVolume);
                if (i64(a0) > 0) {
                    // 0x00531ca8
                    charge(ctx, 4);
                    lw(a1, s0, fdr::kTarget);
                    v0 = slt(v1, a1);
                    if (v0 != 0) {
                        goto L_00531cb8;
                    }
                    a0 = s0;
                L_00531ce0:
                    charge(ctx, 6);
                    s1 = 3;
                    jal(ctx, 0x531CE0u, gen::fn_sub_531AD0_00531ad0);
                    lw(v0, s0, fdr::kTime);
                    sb(s1, s0, fdr::kStat);
                    sw(v0, s0, fdr::kEndTime);
                    v0 = 3;
                    goto L_00531cf8;
                }
            L_00531cb8:
                charge(ctx, 2);
                if (i64(a0) < 0) {
                    // 0x00531cc0
                    charge(ctx, 4);
                    lw(a1, s0, fdr::kTarget);
                    v0 = slt(a1, v1);
                    if (v0 != 0) {
                        goto L_00531cd0;
                    }
                    a0 = s0;
                    goto L_00531ce0;
                }
            L_00531cd0:
                charge(ctx, 2);
                v0 = 3;
                if (a0 == 0) {
                    // 0x00531cd8
                    charge(ctx, 2);
                    lw(a1, s0, fdr::kTarget);
                    a0 = s0;
                    goto L_00531ce0;
                }
            }
        L_00531cf8:
            charge(ctx, 2);
            if (s1 != v0) {
                ld(s0, sp, 0x0);
            } else {
                // 0x00531d00
                charge(ctx, 7);
                lw(v0, s0, fdr::kTime);
                lw(v1, s0, fdr::kEndTime);
                lw(a0, s0, fdr::kHold);
                v0 = subu(v0, v1);
                v0 = slt(v0, a0);
                if (v0 == 0) {
                    // 0x00531d1c
                    charge(ctx, 3);
                    sb(zero, s0, fdr::kStat);
                    a0 = s0;
                    jal(ctx, 0x531D20u, gen::fn_sub_5320E8_005320e8);
                    goto L_00531d28;
                }
                ld(s0, sp, 0x0);
            }
            // 0x00531d2c (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x10);
            sp = addiu(sp, 0x20);
            return;
        }
    L_00531d28:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x00531d2c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00531D40 sub_531D40 -- 8 bytes; leaf frame (no stack)
// Fader curve (+24, u8): 0 = level 3238200 x 10^(dB / 200), 1 = the logarithmic alternative. [ACSFDR_SetCurve]
void sub_531D40(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00531d40
    enter(ctx, 2);  // entry check point + this block's cycles
    sb(a1, a0, fdr::kCurve);
}

// 0x00531D48 sub_531D48 -- 16 bytes; leaf frame (no stack)
// Fader start callback {function, two arguments} at +44. [ACSFDR_SetStartCb]
void sub_531D48(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00531d48
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(a3, a0, fdr::kStartArg2);
    sw(a1, a0, fdr::kStartCb);
    sw(a2, a0, fdr::kStartArg1);
}

// 0x00531D58 sub_531D58 -- 16 bytes; leaf frame (no stack)
// Fader end callback {function, two arguments} at +56. [ACSFDR_SetEndCb]
void sub_531D58(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00531d58
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(a3, a0, fdr::kEndArg2);
    sw(a1, a0, fdr::kEndCb);
    sw(a2, a0, fdr::kEndArg1);
}

// 0x00531D68 sub_531D68 -- 108 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Fader reset: idle, every count 0, volume / target / previous target -960, both callbacks cleared. [acsfdr_Reset]
void sub_531D68(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00531d68
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = si(-960);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    a0 = addiu(s0, 44);
    sw(v0, s0, fdr::kPrevTarget);
    a1 = 0;
    sb(zero, s0, fdr::kStat);
    a2 = 12;
    sw(zero, s0, fdr::kStep);
    sw(zero, s0, fdr::kTime);
    sw(zero, s0, fdr::kEndTime);
    sw(zero, s0, fdr::kDelay);
    sw(zero, s0, fdr::kHold);
    sb(zero, s0, fdr::kCurve);
    sw(v0, s0, fdr::kVolume);
    sw(zero, s0, fdr::kLevel);
    link(ctx, 0x531DB0u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, fdr::kTarget);
    call(ctx, gen::fn_memset_00521408);
    a0 = addiu(s0, 56);
    ld(ra, sp, 0x8);
    a1 = 0;
    ld(s0, sp, 0x0);
    a2 = 12;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x00531DD8 sub_531DD8 -- 132 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// The per-frame level step from one volume (the current one) to another over n frames ((level(to) - level(from)) / n;
//   n <= 0 gives the whole range 3238200 at once). [acsfdr_CalcStep]
void sub_531DD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00531dd8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a3;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s0, sp, 0x0);
    a1 = a2;
    sd(ra, sp, 0x20);
    if (i64(s1) <= 0) {
        // 0x00531e38
        charge(ctx, 2);
        v0 = 0x310000;
        v0 = v0 | 0x6938;  // &0x316938
    } else {
        // 0x00531e04
        charge(ctx, 8);
        jal(ctx, 0x531E04u, gen::fn_sub_531F90_00531f90);
        a0 = s2;
        a1 = s3;
        s0 = v0;
        jal(ctx, 0x531E14u, gen::fn_sub_531F90_00531f90);
        if (s1 == 0) {
            brk(ctx, 0x531E20u, 0x7u);
        }
        // 0x00531e24
        charge(ctx, 5);
        s0 = subu(s0, v0);
        div(s0, s1);
        mflo(s0);
        v0 = s0;
    }
    // 0x00531e40 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00531E60 sub_531E60 -- 304 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Level -> volume (dB x 10): 0 -> -960, 3238200 -> 0, else 200 log10(level / 3238200) (curve 0) or the inverse of
//   curve 1, clamped to -960..0. [acsfdr_LevelToVol]
void sub_531E60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00531e60
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = si(-960);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    if (s0 != 0) {
        // 0x00531e7c
        charge(ctx, 4);
        s1 = 0x310000;
        s1 = s1 | 0x6938;  // &0x316938
        v0 = 0;
        if (s0 != s1) {
            // 0x00531e8c
            charge(ctx, 3);
            lb(a0, a0, 24);
            v0 = 1;
            if (a0 != 0) {
                // 0x00531e98
                charge(ctx, 2);
                if (a0 != v0) {
                    goto L_00531ea0;
                }
                // 0x00531ef0
                charge(ctx, 24);
                a0 = 0x811C;
                a0 = dsll32(a0, 15);
                jal(ctx, 0x531EF4u, gen::fn_log10_0052e9b8);
                a0 = v0;
                jal(ctx, 0x531EFCu, gen::fn_dptofp_005318a0);
                v0 = subu(s1, s0);
                mtc1(v0, f1);
                cvt_s_w(f1, f1);
                v1 = 0x7C0000;
                lwc1(f12, v1, 1184);  // 0x7C04A0
                cvt_s_w(f12, f12);
                mul_s(f0, f0, f1);
                div_s(f12, f0, f12);
                jal(ctx, 0x531F2Cu, gen::fn_fptodp_00530da0);
                a0 = 0x8048;
                a0 = dsll32(a0, 15);
                a1 = v0;
                jal(ctx, 0x531F3Cu, gen::fn_pow_0052e9d0);
                a0 = v0;
                jal(ctx, 0x531F44u, gen::fn_dptofp_005318a0);
                neg_s(f0, f0);
                goto L_00531f50;
            }
        L_00531ea0:
            charge(ctx, 20);
            v0 = 0x7C0000;
            mtc1(s0, f0);
            cvt_s_w(f0, f0);
            lwc1(f12, v0, 1184);  // 0x7C04A0
            cvt_s_w(f12, f12);
            div_s(f12, f0, f12);
            jal(ctx, 0x531EC0u, gen::fn_fptodp_00530da0);
            a0 = v0;
            jal(ctx, 0x531EC8u, gen::fn_log10_0052e9b8);
            a1 = 0x80D2;
            a1 = dsll32(a1, 15);
            a0 = v0;
            jal(ctx, 0x531ED8u, gen::fn_dpmul_00531230);
            a0 = v0;
            jal(ctx, 0x531EE0u, gen::fn_dptofp_005318a0);
        L_00531f50:
            charge(ctx, 5);
            at = lui(0xC470);
            mtc1(at, f1);
            c_lt_s(f1, f0);
            if (!cond(ctx)) {
                mov_s(f0, f1);
            }
            // 0x00531f64
            charge(ctx, 4);
            mtc1(zero, f1);
            c_lt_s(f0, f1);
            if (!cond(ctx)) {
                mov_s(f0, f1);
            }
            // 0x00531f74
            charge(ctx, 2);
            cvt_w_s(f1, f0);
            mfc1(v0, f1);
        }
    }
    // 0x00531f7c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00531F90 sub_531F90 -- 292 bytes; frame 0x20: s0 sp+0x0, ra sp+0x8, f20 sp+0x10
// Volume (dB x 10) -> level: 0 -> 3238200, -960 -> 0, else 3238200 x 10^(vol / 200) (curve 0) or 3238200 log10(-vol)
//   / log10(960) (curve 1), clamped to 0..3238200. [acsfdr_VolToLevel]
void sub_531F90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00531f90
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x310000;
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(ra, sp, 0x8);
    v0 = v0 | 0x6938;  // &0x316938
    swc1(f20, sp, 0x10);
    if (s0 != 0) {
        // 0x00531fb0
        charge(ctx, 3);
        v1 = si(-960);
        v0 = 0;
        if (s0 != v1) {
            // 0x00531fbc
            charge(ctx, 3);
            lb(a0, a0, 24);
            v0 = 1;
            if (a0 != 0) {
                // 0x00531fc8
                charge(ctx, 2);
                if (a0 != v0) {
                    goto L_00531fd0;
                }
                // 0x00532020
                charge(ctx, 20);
                a0 = 0x811C;
                a0 = dsll32(a0, 15);
                jal(ctx, 0x532024u, gen::fn_log10_0052e9b8);
                a0 = v0;
                jal(ctx, 0x53202Cu, gen::fn_dptofp_005318a0);
                a0 = subu(0, s0);
                mov_s(f20, f0);
                jal(ctx, 0x532038u, gen::fn_litodp_00531720);
                a0 = v0;
                jal(ctx, 0x532044u, gen::fn_log10_0052e9b8);
                a0 = v0;
                jal(ctx, 0x53204Cu, gen::fn_dptofp_005318a0);
                v0 = 0x7C0000;
                lwc1(f1, v0, 1184);  // 0x7C04A0
                cvt_s_w(f1, f1);
                mul_s(f1, f1, f0);
                div_s(f0, f1, f20);
                goto L_00532070;
            }
        L_00531fd0:
            charge(ctx, 20);
            mtc1(s0, f0);
            cvt_s_w(f0, f0);
            at = 0x43480000;
            mtc1(at, f12);
            div_s(f12, f0, f12);
            jal(ctx, 0x531FECu, gen::fn_fptodp_00530da0);
            a0 = 0x8048;
            a0 = dsll32(a0, 15);
            a1 = v0;
            jal(ctx, 0x531FFCu, gen::fn_pow_0052e9d0);
            a0 = v0;
            jal(ctx, 0x532004u, gen::fn_dptofp_005318a0);
            at = 0x4A450000;
            at = at | 0xA4E0;
            mtc1(at, f1);
            mul_s(f0, f0, f1);
        L_00532070:
            charge(ctx, 4);
            mtc1(zero, f1);
            c_lt_s(f1, f0);
            if (!cond(ctx)) {
                mov_s(f0, f1);
            }
            // 0x00532080
            charge(ctx, 6);
            at = 0x4A450000;
            at = at | 0xA4E0;
            mtc1(at, f1);
            c_lt_s(f0, f1);
            if (!cond(ctx)) {
                mov_s(f0, f1);
            }
            // 0x00532098
            charge(ctx, 2);
            cvt_w_s(f1, f0);
            mfc1(v0, f1);
        }
    }
    // 0x005320a0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005320B8 sub_5320B8 -- 48 bytes; frame 0x10: ra sp+0x0
// Call the fader's start callback (+44) with its two arguments; 0 when there is none, else 1. [acsfdr_CallStartCb]
void sub_5320B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005320b8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 44);
    if (v0 == 0) {
        v0 = 0;
    } else {
        // 0x005320cc
        charge(ctx, 4);
        lw(a1, a0, 52);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x5320D0u);  // $ra = the return address
        lw(a0, a0, 48);
        call_ptr(ctx, jt);
        v0 = 1;
    }
    // 0x005320dc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005320E8 sub_5320E8 -- 48 bytes; frame 0x10: ra sp+0x0
// Call the fader's end callback (+56) with its two arguments; 0 when there is none, else 1. [acsfdr_CallEndCb]
void sub_5320E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005320e8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 56);
    if (v0 == 0) {
        v0 = 0;
    } else {
        // 0x005320fc
        charge(ctx, 4);
        lw(a1, a0, 64);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x532100u);  // $ra = the return address
        lw(a0, a0, 60);
        call_ptr(ctx, jt);
        v0 = 1;
    }
    // 0x0053210c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
