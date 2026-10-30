// Phase 5 slice libs2: ACSS, part 4: the sound server -- init / finish, the 16 sound slots, the per-frame server,
// and the ducking object ACSVHL it runs (0x5349F8-0x535688).
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

// 0x005349F8 sub_5349F8 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Server create: in a caller's work of at least 176 bytes (else an error and 0), reset (named by its error text).
//   [ACSSVR_Create]
void sub_5349F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005349f8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = sltiu(a1, 176);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x00534a10
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 3800);  // "E2003091207 ACSSVR_Create : Work pointor is NULL."
        goto L_00534a30;
    }
    // 0x00534a20
    charge(ctx, 2);
    if (a1 == 0) {
        // 0x00534a40
        charge(ctx, 3);
        jal(ctx, 0x534A40u, gen::fn_sub_535178_00535178);
        v0 = s0;
    } else {
        // 0x00534a28
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 3856);  // "E2003091208 ACSSVR_Create : Work size is too small."
    L_00534a30:
        charge(ctx, 4);
        jal(ctx, 0x534A30u, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x00534a4c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00534A60 sub_534A60 -- 36 bytes; frame 0x10: ra sp+0x0
// Server destroy: the reset, when it exists. [ACSSVR_Destroy]
void sub_534A60(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00534a60
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00534a78
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00534a6c
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_535178_00535178(ctx);  // tail call
}

// 0x00534A88 sub_534A88 -- 212 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Server init (counted; named by its error text): the first call initialises ADXT and AIXP, registers the server
//   function with SVM ('adxcs_exec_svr') and makes the ducking object. [ACSSVR_Init]
void sub_534A88(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00534a88
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x534A94u, gen::fn_sub_5351B0_005351b0);
    if (v0 != 0) {
        lw(v1, s0, svr::kInitCnt);
    } else {
        // 0x00534aa4
        charge(ctx, 3);
        lw(v0, s0, svr::kIniting);
        if (v0 != 0) {
            lw(v1, s0, svr::kInitCnt);
            goto L_00534b40;
        }
        // 0x00534ab0
        charge(ctx, 25);
        a0 = s0;
        jal(ctx, 0x534AB0u, gen::fn_sub_535178_00535178);
        v0 = 1;
        link(ctx, 0x534ABCu);  // $ra first: the delay slot below depends on it
        sw(v0, s0, svr::kIniting);
        call(ctx, gen::fn_sub_53EA90_0053ea90);
        jal(ctx, 0x534AC4u, gen::fn_sub_5526B0_005526b0);
        a2 = 0x530000;
        t0 = 0x7C0000;
        a2 = addiu(a2, 20928);  // &sub_5351C0
        t0 = addiu(t0, 3912);  // "adxcs_exec_svr"
        a3 = s0;
        a0 = 2;
        a1 = 4;
        jal(ctx, 0x534AE4u, gen::fn_sub_564FE8_00564fe8);
        a0 = addiu(s0, 68);
        a1 = 96;
        jal(ctx, 0x534AF0u, gen::fn_sub_5351E8_005351e8);
        sw(v0, s0, svr::kVhl);
        a0 = v0;
        jal(ctx, 0x534AFCu, gen::fn_sub_535278_00535278);
        a0 = 0x7C0000;
        a0 = addiu(a0, 3928);  // "E2003053001 ACSSVR_Init : Failed to initialize VHL."
        a1 = s0;
        if (v0 != 0) {
            // 0x00534b30
            charge(ctx, 4);
            link(ctx, 0x534B30u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, svr::kVhl);
            call(ctx, gen::fn_sub_5353A0_005353a0);
            sw(zero, s0, svr::kIniting);
            lw(v1, s0, svr::kInitCnt);
            goto L_00534b40;
        }
        // 0x00534b14
        charge(ctx, 6);
        jal(ctx, 0x534B14u, gen::fn_sub_531A10_00531a10);
        a0 = s0;
        jal(ctx, 0x534B1Cu, gen::fn_sub_534B60_00534b60);
        v0 = 0;
        // 0x00534b4c (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_00534b40:
    charge(ctx, 3);
    v0 = 1;
    v1 = addiu(v1, 1);
    sw(v1, s0, svr::kInitCnt);
    // 0x00534b4c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00534B60 sub_534B60 -- 244 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// Server finish (counted): the last one releases every sound, the ducking object, the SVM entries, AIXP and ADXT;
//   'Too many Finish' below zero. [ACSSVR_Finish]
void sub_534B60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00534b60
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v1, s1, svr::kIniting);
    lw(v0, s1, svr::kInitCnt);
    if (v1 == 0) {
        // 0x00534b84
        charge(ctx, 3);
        v0 = addiu(v0, -1);
        sw(v0, s1, svr::kInitCnt);
        lw(v0, s1, svr::kInitCnt);
    }
    // 0x00534b90
    charge(ctx, 2);
    a0 = 0x7C0000;
    if (i64(v0) < 0) {
        // 0x00534b98
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 3984);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    // 0x00534bb8
    charge(ctx, 2);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 1;
    if (!cc) {
        // 0x00534bc0
        charge(ctx, 2);
        ld(s0, sp, 0x0);
        if (v1 == v0) {
            goto L_00534bc8;
        }
        // 0x00534c40 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_00534bc8:
    charge(ctx, 4);
    s0 = s1;
    s2 = 15;
    lw(a1, s0, 0);
    for (;;) {
        // 0x00534bd8
        charge(ctx, 6);
        s0 = addiu(s0, 4);
        s2 = addiu(s2, -1);
        a0 = s1;
        jal(ctx, 0x534BE0u, gen::fn_sub_534DB0_00534db0);
        if (i64(s2) < 0) {
            break;
        }
        lw(a1, s0, 0);
        backedge(ctx);
    }
    // 0x00534bf0
    charge(ctx, 3);
    lw(a0, s1, svr::kVhl);
    if (a0 == 0) {
        a0 = 2;
    } else {
        // 0x00534bfc
        charge(ctx, 6);
        jal(ctx, 0x534BFCu, gen::fn_sub_5352F8_005352f8);
        link(ctx, 0x534C04u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, svr::kVhl);
        call(ctx, gen::fn_sub_535250_00535250);
        sw(zero, s1, svr::kVhl);
        a0 = 2;
    }
    // 0x00534c14
    charge(ctx, 11);
    a1 = 4;
    jal(ctx, 0x534C14u, gen::fn_sub_564EF8_00564ef8);
    a0 = 5;
    link(ctx, 0x534C20u);  // $ra first: the delay slot below depends on it
    lw(a1, s1, svr::kSvmId);
    call(ctx, gen::fn_sub_564EF8_00564ef8);
    jal(ctx, 0x534C28u, gen::fn_sub_552760_00552760);
    jal(ctx, 0x534C30u, gen::fn_sub_53EC20_0053ec20);
    sw(zero, s1, svr::kIniting);
    ld(s0, sp, 0x0);
    // 0x00534c40 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00534C58 sub_534C58 -- 64 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Finish the server completely (finish while initialised). [ACSSVR_FinishAll]
void sub_534C58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00534c58
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    for (;;) {
        // 0x00534c78
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x534C78u, gen::fn_sub_5351B0_005351b0);
        a0 = s0;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00534c70
        charge(ctx, 2);
        jal(ctx, 0x534C70u, gen::fn_sub_534B60_00534b60);
    }
    // 0x00534c88
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00534C98 sub_534C98 -- 280 bytes; frame 0x40: s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s0 sp+0x0, s1 sp+0x8, ra sp+0x38
// Create a sound in the first free of the 16 slots, from the work (208 bytes for the sound, the rest for its players)
//   and the configuration (named by its error text). [ACSSVR_CreatSnd]
void sub_534C98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00534c98
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    s4 = a0;
    sd(s5, sp, 0x28);
    s5 = 0;
    sd(s6, sp, 0x30);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x38);
    s6 = a1;
    jal(ctx, 0x534CCCu, gen::fn_sub_5351B0_005351b0);
    if (v0 != 0) {
        s1 = 0;
        // 0x00534cf0
        charge(ctx, 2);
        s0 = s4;
        for (;;) {
            // 0x00534cfc
            charge(ctx, 3);
            v0 = slti(s1, 16);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 16;
            if (cc) {
                break;
            }
            // 0x00534d08
            charge(ctx, 5);
            lw(v0, s0, 0);
            if (v0 == 0) {
                goto L_00534d1c_6;
            }
            s0 = addiu(s0, 4);
            backedge(ctx);
            // 0x00534cf8
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
    L_00534d3c:
        charge(ctx, 2);
        a1 = s6;
        if (s1 == v0) {
            // 0x00534d44
            charge(ctx, 3);
            a0 = 0x7C0000;
            a0 = addiu(a0, 4088);  // "E2003053003 ACSSVR_CreatSnd : Can't create sound any more."
            goto L_00534d70;
        }
        // 0x00534d50
        charge(ctx, 6);
        a2 = s2;
        a3 = s3;
        a0 = s5;
        jal(ctx, 0x534D58u, gen::fn_sub_532818_00532818);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = s5;
        if (!cc) {
            // 0x00534d68
            charge(ctx, 2);
            a0 = 0x7C0000;
            a0 = addiu(a0, 4152);  // "E2003053004 ACSSVR_CreatSnd : Failed to create sound."
        L_00534d70:
            charge(ctx, 6);
            jal(ctx, 0x534D70u, gen::fn_sub_531A10_00531a10);
            a0 = s4;
            a1 = s5;
            jal(ctx, 0x534D7Cu, gen::fn_sub_534DB0_00534db0);
            v0 = 0;
        }
    } else {
        // 0x00534cdc
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 4040);  // "E2003053002 ACSSVR_CreatSnd : Not initialized."
        jal(ctx, 0x534CE0u, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x00534d88 (the shared epilogue, written out on this path)
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
L_00534d1c_6:
    charge(ctx, 8);
    a0 = s2;
    s2 = addiu(s2, 208);
    a1 = s3;
    s3 = addiu(s3, -208);
    jal(ctx, 0x534D28u, gen::fn_sub_532788_00532788);
    sw(v0, s0, 0);
    s5 = v0;
    v0 = 16;
    goto L_00534d3c;
}

// 0x00534DB0 sub_534DB0 -- 116 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Destroy a sound: finish it and free its slot. [ACSSVR_DestroySnd]
void sub_534DB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00534db0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    if (s1 != 0) {
        // 0x00534dcc
        charge(ctx, 5);
        a0 = s1;
        s0 = v0;
        jal(ctx, 0x534DD0u, gen::fn_sub_532D30_00532d30);
        v1 = 0;
        for (;;) {
            // 0x00534de0
            charge(ctx, 3);
            v0 = slti(v1, 16);
            v1 = addiu(v1, 1);
            if (v0 == 0) {
                break;
            }
            // 0x00534dec
            charge(ctx, 6);
            lw(v0, s0, 0);
            if (v0 == s1) {
                goto L_00534e04_4;
            }
            s0 = addiu(s0, 4);
            backedge(ctx);
        }
    }
    // 0x00534e10 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    return;
L_00534e04_4:
    charge(ctx, 3);
    a0 = s1;
    jal(ctx, 0x534E04u, gen::fn_sub_5327F0_005327f0);
    sw(zero, s0, 0);
    // 0x00534e10 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00535050 sub_535050 -- 128 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// The server function: the ducking object when enabled, then every sound's frame. [ACSSVR_ExecServer]
void sub_535050(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00535050
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    s2 = a0;
    jal(ctx, 0x535064u, gen::fn_sub_5351B0_005351b0);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00535074
        charge(ctx, 4);
        link(ctx, 0x535074u);  // $ra first: the delay slot below depends on it
        lw(a0, s2, svr::kVhl);
        call(ctx, gen::fn_sub_535348_00535348);
        if (v0 == 0) {
            s0 = s2;
        } else {
            // 0x00535084
            charge(ctx, 3);
            link(ctx, 0x535084u);  // $ra first: the delay slot below depends on it
            lw(a0, s2, svr::kVhl);
            call(ctx, gen::fn_sub_5353A8_005353a8);
            s0 = s2;
        }
        // 0x00535090
        charge(ctx, 2);
        s1 = 15;
        lw(v0, s0, 0);
        for (;;) {
            // 0x00535098
            charge(ctx, 3);
            s0 = addiu(s0, 4);
            a1 = v0;
            if (v0 != 0) {
                // 0x005350a4
                charge(ctx, 2);
                a0 = s2;
                jal(ctx, 0x5350A4u, gen::fn_sub_5350D0_005350d0);
            }
            // 0x005350ac
            charge(ctx, 3);
            s1 = addiu(s1, -1);
            if (i64(s1) < 0) {
                break;
            }
            lw(v0, s0, 0);
            backedge(ctx);
        }
        // 0x005350b8
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x005350bc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005350D0 sub_5350D0 -- 160 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// One sound's frame: the ducking offset for kind-1 sounds, then the sound update. [acssvr_ExecSnd]
void sub_5350D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005350d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x5350E4u, gen::fn_sub_5351B0_005351b0);
    a0 = s0;
    if (v0 != 0) {
        // 0x005350f4
        charge(ctx, 4);
        jal(ctx, 0x5350F4u, gen::fn_sub_532E08_00532e08);
        a0 = s0;
        if (v0 != 0) {
            // 0x00535104
            charge(ctx, 6);
            jal(ctx, 0x535104u, gen::fn_sub_533CC0_00533cc0);
            link(ctx, 0x53510Cu);  // $ra first: the delay slot below depends on it
            lw(a0, s1, svr::kVhl);
            call(ctx, gen::fn_sub_535348_00535348);
            if (v0 != 0) {
                // 0x0053511c
                charge(ctx, 4);
                link(ctx, 0x53511Cu);  // $ra first: the delay slot below depends on it
                lw(a0, s1, svr::kVhl);
                call(ctx, gen::fn_sub_535350_00535350);
                a0 = s0;
                if (v0 != 0) {
                    // 0x0053512c
                    charge(ctx, 5);
                    jal(ctx, 0x53512Cu, gen::fn_sub_533230_00533230);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x00535140
                        charge(ctx, 5);
                        link(ctx, 0x535140u);  // $ra first: the delay slot below depends on it
                        lw(a0, s1, svr::kVhl);
                        call(ctx, gen::fn_sub_535358_00535358);
                        a0 = s0;
                        a1 = v0;
                        jal(ctx, 0x53514Cu, gen::fn_sub_533CA8_00533ca8);
                    }
                }
            }
            // 0x00535154
            charge(ctx, 2);
            a0 = s0;
            jal(ctx, 0x535154u, gen::fn_sub_533CD0_00533cd0);
        }
    }
    // 0x0053515c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00535170 sub_535170 -- 8 bytes; leaf frame (no stack)
// The server's ducking object (+64). [ACSSVR_GetVhl]
void sub_535170(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00535170
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, svr::kVhl);
}

// 0x00535178 sub_535178 -- 52 bytes; leaf frame (no stack)
// Server reset: the 16 slots and the counts cleared. [acssvr_Reset]
void sub_535178(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00535178
    enter(ctx, 2);  // entry check point + this block's cycles
    v1 = 15;
    v0 = addiu(a0, 60);
    for (;;) {
        // 0x00535180
        charge(ctx, 7);
        v1 = addiu(v1, -1);
        sw(zero, v0, 0);
        v0 = addiu(v0, -4);
        if (i64(v1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0053519c
    charge(ctx, 4);
    sw(zero, a0, svr::kSvmId);
    sw(zero, a0, svr::kInitCnt);
    sw(zero, a0, svr::kIniting);
}

// 0x005351B0 sub_5351B0 -- 12 bytes; leaf frame (no stack)
// 1 while the server is initialised (count > 0). [ACSSVR_IsInit]
void sub_5351B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005351b0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, svr::kInitCnt);
    v0 = slt(0, v0);
}

// 0x005351C0 sub_5351C0 -- 40 bytes; frame 0x10: ra sp+0x0
// The SVM server entry: run the server function. [acssvr_SvrFunc]
void sub_5351C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005351c0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0;
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x005351d0
        charge(ctx, 3);
        jal(ctx, 0x5351D0u, gen::fn_sub_535050_00535050);
        v0 = 1;
    }
    // 0x005351dc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005351E8 sub_5351E8 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Ducking object create: in a caller's work of at least 96 bytes (else an error and 0; named by its error text).
//   [ACSVHL_Create]
void sub_5351E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005351e8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = sltiu(a1, 96);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x00535200
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 4216);  // "E2003091209 ACSVHL_Create : Work pointor is NULL."
        goto L_00535220;
    }
    // 0x00535210
    charge(ctx, 2);
    if (a1 == 0) {
        // 0x00535230
        charge(ctx, 3);
        jal(ctx, 0x535230u, gen::fn_sub_5355B8_005355b8);
        v0 = s0;
    } else {
        // 0x00535218
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 4272);  // "E2003091210 ACSVHL_Create : Work size is too small."
    L_00535220:
        charge(ctx, 4);
        jal(ctx, 0x535220u, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x0053523c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00535250 sub_535250 -- 36 bytes; frame 0x10: ra sp+0x0
// Ducking object destroy: the reset, when it exists. [ACSVHL_Destroy]
void sub_535250(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00535250
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00535268
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0053525c
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5355B8_005355b8(ctx);  // tail call
}

// 0x00535278 sub_535278 -- 128 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Ducking object init (named by its error text): its fader in the work at +8, started silent. [ACSVHL_Init]
void sub_535278(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00535278
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, vhl::kFader);
    a0 = addiu(s0, 8);
    if (v0 != 0) {
        // 0x00535294
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 4328);  // "E2003091600 ACSVHL_Init : Already initialized."
        goto L_005352bc;
    }
    // 0x005352a0
    charge(ctx, 7);
    a1 = 68;
    jal(ctx, 0x5352A0u, gen::fn_sub_531A28_00531a28);
    a1 = 0;
    a0 = 0x7C0000;
    sw(v0, s0, vhl::kFader);
    a0 = addiu(a0, 4376);  // "E2003091601 ACSVHL_Init : Failed to initialize ACSFDR."
    if (v0 != 0) {
        // 0x005352d0
        charge(ctx, 6);
        a0 = v0;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x5352DCu, gen::fn_sub_531B00_00531b00);
        v0 = 1;
    } else {
    L_005352bc:
        charge(ctx, 4);
        jal(ctx, 0x5352BCu, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x005352e8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005352F8 sub_5352F8 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Ducking object finish: destroy its fader. [ACSVHL_Finish]
void sub_5352F8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005352f8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, vhl::kFader);
    a0 = v0;
    if (v0 != 0) {
        // 0x00535314
        charge(ctx, 3);
        jal(ctx, 0x535314u, gen::fn_sub_531A90_00531a90);
        sw(zero, s0, vhl::kFader);
    }
    // 0x00535320 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00535348 sub_535348 -- 8 bytes; leaf frame (no stack)
// Ducking enabled flag (+76). [ACSVHL_IsEnable]
void sub_535348(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00535348
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, vhl::kEnable);
}

// 0x00535350 sub_535350 -- 8 bytes; leaf frame (no stack)
// Ducking state (+80, s8: 0 idle, 1 lowering, 2 low, 3 restoring). [ACSVHL_GetStat]
void sub_535350(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00535350
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, vhl::kStat);
}

// 0x00535358 sub_535358 -- 24 bytes; frame 0x10: ra sp+0x0
// The ducking volume (its fader's). [ACSVHL_GetVolume]
void sub_535358(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00535358
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_531AC8_00531ac8(ctx);  // tail call
}

// 0x00535388 sub_535388 -- 8 bytes; leaf frame (no stack)
// Ducking lowering frames (+84). [ACSVHL_GetDownTime]
void sub_535388(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00535388
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, vhl::kDownTime);
}

// 0x00535390 sub_535390 -- 8 bytes; leaf frame (no stack)
// Ducking restoring frames (+88). [ACSVHL_GetUpTime]
void sub_535390(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00535390
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, vhl::kUpTime);
}

// 0x00535398 rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc -- 8 bytes; leaf frame (no stack)
// Ducking depth (+92, dB x 10). (A FLIRT name.) [ACSVHL_GetDepth]
void rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00535398
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, vhl::kDepth);
}

// 0x005353A0 sub_5353A0 -- 8 bytes; leaf frame (no stack)
// Ducking object owner: the server (+0). [ACSVHL_SetServer]
void sub_5353A0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x005353a0
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, vhl::kServer);
}

// 0x005353A8 sub_5353A8 -- 524 bytes; frame 0x30: s0 sp+0x0, ra sp+0x20, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18
// Ducking frame: is a kind-2 sound playing (status 1 / 2 and not paused)?  Then lower the volume by the depth (state
//   1 -> 2); when none is, restore it (state 3 -> 0), resuming a half-done fade from where it is; then step the
//   fader. [acsvhl_ExecServer]
void sub_5353A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005353a8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 0;
    sd(s3, sp, 0x18);
    s3 = 0;
    lw(v1, s1, vhl::kServer);
    for (;;) {
        // 0x005353d0
        charge(ctx, 5);
        v0 = sll(s2, 2);
        v0 = addu(v0, v1);
        lw(s0, v0, 0);
        if (s0 == 0) {
            s2 = addiu(s2, 1);
        } else {
            // 0x005353e4
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x5353E4u, gen::fn_sub_532E08_00532e08);
            if (v0 == 0) {
                s2 = addiu(s2, 1);
            } else {
                // 0x005353f4
                charge(ctx, 5);
                a0 = s0;
                jal(ctx, 0x5353F4u, gen::fn_sub_533230_00533230);
                v1 = 2;
                if (v0 != v1) {
                    s2 = addiu(s2, 1);
                } else {
                    // 0x00535408
                    charge(ctx, 6);
                    a0 = s0;
                    jal(ctx, 0x535408u, gen::fn_sub_5331A8_005331a8);
                    v1 = v0;
                    v0 = sltiu(v1, 5);
                    if (v0 == 0) {
                        s2 = addiu(s2, 1);
                    } else {
                        // 0x00535420
                        charge(ctx, 6);
                        v0 = sll(v1, 2);
                        v1 = 0x7C0000;
                        v1 = addu(v1, v0);
                        lw(v1, v1, 4432);
                        switch (v1.u()) {
                        case 0x535438u:  // table[1, 2]
                            // 0x00535438
                            charge(ctx, 4);
                            a0 = s0;
                            jal(ctx, 0x535438u, gen::fn_sub_533160_00533160);
                            v1 = 1;
                            if (v0 == 0) s3 = v1;
                            break;
                        case 0x535448u:  // table[0, 3, 4]
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v1.u());
                            return;
                        }
                        // 0x00535448
                        charge(ctx, 1);
                        s2 = addiu(s2, 1);
                    }
                }
            }
        }
        // 0x0053544c
        charge(ctx, 3);
        v0 = slti(s2, 16);
        if (v0 == 0) {
            break;
        }
        lw(v1, s1, vhl::kServer);
        backedge(ctx);
    }
    // 0x00535458
    charge(ctx, 4);
    lb(v1, s1, vhl::kStat);
    a0 = 1;
    v0 = slti(v1, 2);
    if (v1 == a0) {
        // 0x005354b8
        charge(ctx, 2);
        if (s3 != 0) {
            // 0x005354d8
            charge(ctx, 4);
            link(ctx, 0x5354D8u);  // $ra first: the delay slot below depends on it
            lw(a0, s1, vhl::kFader);
            call(ctx, gen::fn_sub_531AB8_00531ab8);
            if (v0 != 0) {
                lw(a0, s1, vhl::kFader);
            } else {
                // 0x005354e8
                charge(ctx, 5);
                a0 = s1;
                a1 = 2;
                jal(ctx, 0x5354ECu, gen::fn_sub_535610_00535610);
                lw(a0, s1, vhl::kFader);
            }
        } else {
            // 0x005354c0
            charge(ctx, 6);
            a0 = s1;
            jal(ctx, 0x5354C0u, gen::fn_sub_535618_00535618);
            lw(a0, s1, vhl::kFader);
            a1 = 0;
            a2 = v0;
        L_00535510:
            charge(ctx, 8);
            a3 = 0;
            t0 = 0;
            jal(ctx, 0x535514u, gen::fn_sub_531B00_00531b00);
            a0 = s1;
            a1 = 3;
            jal(ctx, 0x535520u, gen::fn_sub_535610_00535610);
            lw(a0, s1, vhl::kFader);
        }
    } else {
        // 0x00535468
        charge(ctx, 2);
        if (v0 == 0) {
            v0 = 2;
            // 0x00535480
            charge(ctx, 2);
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = 3;
            if (cc) {
                // 0x00535500
                charge(ctx, 2);
                lw(a0, s1, vhl::kFader);
                if (s3 == 0) {
                    // 0x00535508
                    charge(ctx, 2);
                    a1 = 0;
                    lw(a2, s1, vhl::kUpTime);
                    goto L_00535510;
                }
            } else {
                // 0x00535488
                charge(ctx, 2);
                if (v1 == v0) {
                    // 0x00535530
                    charge(ctx, 2);
                    if (s3 != a0) {
                        // 0x00535578
                        charge(ctx, 4);
                        link(ctx, 0x535578u);  // $ra first: the delay slot below depends on it
                        lw(a0, s1, vhl::kFader);
                        call(ctx, gen::fn_sub_531AB8_00531ab8);
                        if (v0 != 0) {
                            lw(a0, s1, vhl::kFader);
                        } else {
                            // 0x00535588
                            charge(ctx, 4);
                            a0 = s1;
                            a1 = 0;
                            jal(ctx, 0x53558Cu, gen::fn_sub_535610_00535610);
                            lw(a0, s1, vhl::kFader);
                        }
                    } else {
                        // 0x00535538
                        charge(ctx, 8);
                        a0 = s1;
                        jal(ctx, 0x535538u, gen::fn_sub_535668_00535668);
                        lw(a1, s1, vhl::kDepth);
                        lw(a0, s1, vhl::kFader);
                        a2 = v0;
                        a1 = subu(0, a1);
                        a3 = 0;
                        t0 = 0;
                    L_00535558:
                        charge(ctx, 7);
                        jal(ctx, 0x535558u, gen::fn_sub_531B00_00531b00);
                        a0 = s1;
                        a1 = 1;
                        jal(ctx, 0x535564u, gen::fn_sub_535610_00535610);
                        lw(a0, s1, vhl::kFader);
                    }
                } else {
                    // 0x00535490
                    charge(ctx, 2);
                    lw(a0, s1, vhl::kFader);
                }
            }
        } else {
            // 0x00535470
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00535498
                charge(ctx, 2);
                cc = s3 != a0;  // the condition, before the delay slot changes it
                lw(a0, s1, vhl::kFader);
                if (!cc) {
                    // 0x005354a0
                    charge(ctx, 6);
                    lw(a1, s1, vhl::kDepth);
                    a3 = 0;
                    t0 = 0;
                    lw(a2, s1, vhl::kDownTime);
                    a1 = subu(0, a1);
                    goto L_00535558;
                }
            } else {
                // 0x00535478
                charge(ctx, 2);
                lw(a0, s1, vhl::kFader);
            }
        }
    }
    // 0x00535598
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_531C00_00531c00(ctx);  // tail call
}

// 0x005355B8 sub_5355B8 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Ducking object reset: lowering 30 frames, restoring 60, depth 120. [acsvhl_Reset]
void sub_5355B8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005355b8
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    a0 = addiu(s0, 8);
    sw(zero, s0, vhl::kServer);
    a2 = 68;
    link(ctx, 0x5355D8u);  // $ra first: the delay slot below depends on it
    sw(zero, s0, vhl::kFader);
    call(ctx, gen::fn_memset_00521408);
    sw(zero, s0, vhl::kEnable);
    v1 = 30;
    a0 = 60;
    v0 = 120;
    sw(v1, s0, vhl::kDownTime);
    sw(v0, s0, vhl::kDepth);
    sw(a0, s0, vhl::kUpTime);
    sb(zero, s0, vhl::kStat);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00535610 sub_535610 -- 8 bytes; leaf frame (no stack)
// Set the ducking state (+80). [acsvhl_SetStat]
void sub_535610(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00535610
    enter(ctx, 2);  // entry check point + this block's cycles
    sb(a1, a0, vhl::kStat);
}

// 0x00535618 sub_535618 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Lowering frames left from the current volume (the down frames scaled by volume / -depth). [acsvhl_CalcDownTime]
void sub_535618(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00535618
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    link(ctx, 0x535628u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, vhl::kFader);
    call(ctx, gen::fn_sub_531AC8_00531ac8);
    lw(a0, s0, vhl::kDownTime);
    lw(v1, s0, vhl::kDepth);
    mult(v0, v0, a0);
    v1 = subu(0, v1);
    if (v1 == 0) {
        brk(ctx, 0x535644u, 0x7u);
    }
    // 0x00535648
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    div(v0, v1);
    mflo(v0);
    v0 = subu(a0, v0);
    sp = addiu(sp, 0x10);
}

// 0x00535668 sub_535668 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Restoring frames left from the current volume (the up frames scaled by volume / -depth). [acsvhl_CalcUpTime]
void sub_535668(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00535668
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    link(ctx, 0x535678u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, vhl::kFader);
    call(ctx, gen::fn_sub_531AC8_00531ac8);
    lw(a0, s0, vhl::kUpTime);
    lw(v1, s0, vhl::kDepth);
    mult(v0, v0, a0);
    v1 = subu(0, v1);
    if (v1 == 0) {
        brk(ctx, 0x535694u, 0x7u);
    }
    // 0x00535698
    charge(ctx, 8);
    lw(a0, s0, vhl::kDownTime);
    ld(ra, sp, 0x8);
    div(v0, v1);
    ld(s0, sp, 0x0);
    mflo(v0);
    v0 = subu(a0, v0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
