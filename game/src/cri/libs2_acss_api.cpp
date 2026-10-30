// Phase 5 slice libs2: ACSS, part 5: the public entry points -- thunks into parts 1-4, the create / destroy /
// ducking ones through the server pointer 0x793F44 (0x54D030-0x54D528).
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

// 0x0054D030 setenv -- 44 bytes; frame 0x10: ra sp+0x0
// Public: create a sound on the server 0x793F44 points at. [ACSND_Create]
void setenv(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d030
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x790000;
    sd(ra, sp, 0x0);
    v0 = a1;
    a1 = a0;
    lw(a0, v1, 16196);  // 0x793F44
    ld(ra, sp, 0x0);
    a3 = a2;
    a2 = v0;
    sp = addiu(sp, 0x10);
    gen::fn_sub_534C98_00534c98(ctx);  // tail call
}

// 0x0054D060 unsetenv -- 32 bytes; frame 0x10: ra sp+0x0
// Public: destroy a sound. [ACSND_Destroy]
void unsetenv(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d060
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(ra, sp, 0x0);
    a1 = a0;
    lw(a0, v0, 16196);  // 0x793F44
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_534DB0_00534db0(ctx);  // tail call
}

// 0x0054D080 valloc -- 576 bytes, 3 chunks; frame 0x10: ra sp+0x0
// Public: the work size a configuration needs (208 for the sound, per player the back end, its buffers and the fader;
//   AHX and AIX track extras). [ACSND_CalcWorkSize]
void valloc(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0054d080
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(ra, sp, 0x0);
    a1 = a0;
    lw(a0, v0, 16196);  // 0x793F44
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00534e28
    charge(ctx, 4);
    t1 = a1;
    lw(t2, t1, 28);
    lw(v0, t1, 36);
    if (t2 != 0) {
        // 0x00534e38
        charge(ctx, 2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 1000;
        if (cc) {
            // 0x00534ea8
            charge(ctx, 3);
            lw(a2, t1, 8);
            if (v0 == 0) {
                brk(ctx, 0x534EB0u, 0x7u);
            }
            // 0x00534eb4
            charge(ctx, 29);
            lw(v1, t1, 4);
            div(a2, v0);
            v0 = 44;
            a1 = sll(v1, 6);
            a3 = 25000;
            a1 = addu(a1, v1);
            a1 = sll(a1, 2);
            lw(a0, t1, 0);
            a1 = subu(a1, v1);
            lw(t0, t1, 12);
            a0 = addiu(a0, 1);
            a1 = sll(a1, 6);
            mflo(a2);
            mult(v1, v1, a2);
            mult1(v1, v1, a3);
            div(v1, v0);
            mflo(v1);
            mult(v1, v1, a0);
            v0 = addiu(v1, 2048);
            v1 = addiu(v1, 4095);
            a0 = slti(v0, 0);
            if (a0 != 0) v0 = v1;
            v0 = sra(v0, 11);
            v0 = sll(v0, 11);
            v0 = addu(v0, a1);
            v0 = addiu(v0, 36);
            mult(v0, v0, t0);
            a1 = addiu(v0, 80);
        } else {
            // 0x00534e40
            charge(ctx, 6);
            lw(v1, t1, 8);
            a2 = 25000;
            a1 = 44;
            div(v1, v0);
            if (v0 == 0) {
                brk(ctx, 0x534E54u, 0x7u);
            }
            // 0x00534e58
            charge(ctx, 19);
            lw(a0, t1, 0);
            lw(a3, t1, 12);
            a0 = addiu(a0, 1);
            mflo(v1);
            mult(v1, v1, a2);
            div1(v1, a1);
            mflo1(v1);
            mult(v1, v1, a0);
            v0 = addiu(v1, 2048);
            v1 = addiu(v1, 4095);
            a0 = slti(v0, 0);
            if (a0 != 0) v0 = v1;
            v0 = sra(v0, 11);
            v0 = sll(v0, 11);
            at = 0x85A4;
            v0 = addu(at, v0);
            mult(v0, v0, a3);
            a1 = addiu(v0, 80);
        }
        goto L_00535014;
    }
    // 0x00534f28
    charge(ctx, 2);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 1000;
    if (cc) {
        // 0x00534f98
        charge(ctx, 3);
        lw(a2, t1, 8);
        if (v0 == 0) {
            brk(ctx, 0x534FA0u, 0x7u);
        }
        // 0x00534fa4
        charge(ctx, 28);
        lw(v1, t1, 4);
        div(a2, v0);
        v0 = 44;
        a1 = sll(v1, 6);
        a3 = 25000;
        a1 = addu(a1, v1);
        a1 = sll(a1, 2);
        lw(a0, t1, 0);
        a1 = subu(a1, v1);
        lw(t0, t1, 16);
        a0 = addiu(a0, 1);
        a1 = sll(a1, 6);
        mflo(a2);
        mult(v1, v1, a2);
        mult1(v1, v1, a3);
        div(v1, v0);
        mflo(v1);
        mult(v1, v1, a0);
        v0 = addiu(v1, 2048);
        v1 = addiu(v1, 4095);
        a0 = slti(v0, 0);
        if (a0 != 0) v0 = v1;
        v0 = sra(v0, 11);
        v0 = sll(v0, 11);
        v0 = addiu(v0, 36);
        mult(v0, v0, t0);
        v0 = addu(v0, a1);
        a1 = addiu(v0, 76);
    L_00535014:
        charge(ctx, 1);
        lw(v1, t1, 32);
    } else {
        // 0x00534f30
        charge(ctx, 6);
        lw(v1, t1, 8);
        a2 = 25000;
        a1 = 44;
        div(v1, v0);
        if (v0 == 0) {
            brk(ctx, 0x534F44u, 0x7u);
        }
        // 0x00534f48
        charge(ctx, 20);
        lw(a0, t1, 0);
        lw(a3, t1, 16);
        a0 = addiu(a0, 1);
        mflo(v1);
        mult(v1, v1, a2);
        div1(v1, a1);
        mflo1(v1);
        mult(v1, v1, a0);
        v0 = addiu(v1, 2048);
        v1 = addiu(v1, 4095);
        a0 = slti(v0, 0);
        if (a0 != 0) v0 = v1;
        v0 = sra(v0, 11);
        v0 = sll(v0, 11);
        v0 = addiu(v0, 36);
        mult(v0, v0, a3);
        a1 = 0x85CC;
        a1 = addu(a1, v0);
        lw(v1, t1, 32);
    }
    // 0x00535018
    charge(ctx, 8);
    v0 = addiu(a1, 12288);
    lw(a0, t1, 24);
    if (v1 != 0) a1 = v0;
    a1 = addiu(a1, 68);
    v0 = sll(a1, 1);
    if (a0 != 0) a1 = v0;
    v1 = addiu(a1, 464);
    if (t2 != 0) {
        // 0x00535038
        charge(ctx, 3);
        lw(v0, t1, 12);
        v0 = sll(v0, 2);
        v1 = addu(v1, v0);
    }
    // 0x00535044 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = v1;
}

// 0x0054D0A0 pvalloc -- 20 bytes; frame 0x10: ra sp+0x0
// Public: start a named file. [ACSND_StartFname]
void pvalloc(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d0a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_532E10_00532e10(ctx);  // tail call
}

// 0x0054D0B8 sub_54D0B8 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: start a partition file. [ACSND_StartAfs]
void sub_54D0B8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d0b8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_532E70_00532e70(ctx);  // tail call
}

// 0x0054D0D0 sub_54D0D0 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: start from memory. [ACSND_StartMem]
void sub_54D0D0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d0d0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_532EC0_00532ec0(ctx);  // tail call
}

// 0x0054D0E8 sub_54D0E8 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: start a memory index entry. [ACSND_StartMemIdx]
void sub_54D0E8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d0e8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_532F10_00532f10(ctx);  // tail call
}

// 0x0054D118 cosl_4 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: pause / resume. [ACSND_Pause]
void cosl_4(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d118
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5330A8_005330a8(ctx);  // tail call
}

// 0x0054D130 coshl_4 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: the pause state. [ACSND_GetStatPause]
void coshl_4(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d130
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533160_00533160(ctx);  // tail call
}

// 0x0054D160 hypotf_4 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: the creation parameters. [ACSND_GetCprm]
void hypotf_4(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d160
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5331F0_005331f0(ctx);  // tail call
}

// 0x0054D178 sub_54D178 -- 28 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Public: set the kind (+140). [ACSND_SetKind]
void sub_54D178(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d178
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00533228
    charge(ctx, 2);
    sb(a1, a0, snd::kKind);
}

// 0x0054D190 sub_54D190 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: the kind. [ACSND_GetKind]
void sub_54D190(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d190
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533230_00533230(ctx);  // tail call
}

// 0x0054D1A8 sub_54D1A8 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: set the volume. [ACSND_SetOutVol]
void sub_54D1A8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d1a8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533238_00533238(ctx);  // tail call
}

// 0x0054D1C0 sub_54D1C0 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: the volume. [ACSND_GetOutVol]
void sub_54D1C0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d1c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn__ZNKSt9basic_iosIcSt11char_traitsIcEE10exceptionsEv_00533450(ctx);  // tail call
}

// 0x0054D1D8 sub_54D1D8 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: set an AIX track's volume. [ACSND_SetTrackVol]
void sub_54D1D8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d1d8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533340_00533340(ctx);  // tail call
}

// 0x0054D1F0 sub_54D1F0 -- 92 bytes, 3 chunks; frame 0x10: ra sp+0x0
// Public: an AIX track's volume (0 for ADX or a track out of range). [ACSND_GetTrackVol]
void sub_54D1F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d1f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00533458
    charge(ctx, 3);
    lw(v1, a0, 148);
    v0 = 0;
    if (v1 == 0) {
        // 0x0053349c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x00533464
    charge(ctx, 2);
    if (i64(a1) < 0) {
        // 0x0053347c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x0053346c
    charge(ctx, 4);
    lw(v0, a0, 132);
    v0 = slt(a1, v0);
    if (v0 == 0) {
        // 0x0053347c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    lw(a0, a0, 192);
    // 0x00533488
    charge(ctx, 2);
    v0 = 0;
    if (a0 != 0) {
        // 0x00533490
        charge(ctx, 3);
        v1 = sll(a1, 2);
        v1 = addu(v1, a0);
        lw(v0, v1, 0);
    }
    // 0x0053349c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0054D208 sub_54D208 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: set the loop flag. [ACSND_SetLpFlg]
void sub_54D208(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d208
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5334A8_005334a8(ctx);  // tail call
}

// 0x0054D238 sub_54D238 -- 28 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Public: set the fade-in frames (+172). [ACSND_SetFadeInTime]
void sub_54D238(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d238
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00533560
    charge(ctx, 2);
    sw(a1, a0, snd::kFadeInTime);
}

// 0x0054D250 sub_54D250 -- 28 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Public: set the volume-change frames (+176). [ACSND_SetVolChgTime]
void sub_54D250(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d250
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00533568
    charge(ctx, 2);
    sw(a1, a0, snd::kVolChgTime);
}

// 0x0054D268 sub_54D268 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: the fade-out frames. [ACSND_GetFadeOutTime]
void sub_54D268(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d268
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533570_00533570(ctx);  // tail call
}

// 0x0054D280 sub_54D280 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: the fade-in frames. [ACSND_GetFadeInTime]
void sub_54D280(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d280
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533578_00533578(ctx);  // tail call
}

// 0x0054D298 sub_54D298 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: the volume-change frames. [ACSND_GetVolChgTime]
void sub_54D298(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d298
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533580_00533580(ctx);  // tail call
}

// 0x0054D2B0 sub_54D2B0 -- 28 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Public: set the cross-fade offset (+180). [ACSND_SetCrossOffset]
void sub_54D2B0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d2b0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00533588
    charge(ctx, 2);
    sw(a1, a0, snd::kCrossOffset);
}

// 0x0054D2C8 sub_54D2C8 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: the cross-fade offset. [ACSND_GetCrossOffset]
void sub_54D2C8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d2c8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn__ZNKSt9basic_iosIcSt11char_traitsIcEE3tieEv_0_00533590(ctx);  // tail call
}

// 0x0054D2E0 sub_54D2E0 -- 28 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Public: set the hold frames (+184). [ACSND_SetHoldTime]
void sub_54D2E0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d2e0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00533598
    charge(ctx, 2);
    sw(a1, a0, snd::kHoldTime);
}

// 0x0054D2F8 sub_54D2F8 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: the hold frames. [ACSND_GetHoldTime]
void sub_54D2F8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d2f8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5335A0_005335a0(ctx);  // tail call
}

// 0x0054D310 sub_54D310 -- 28 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Public: set the callback (+204). [ACSND_SetCbFunc]
void sub_54D310(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d310
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x005335a8
    charge(ctx, 2);
    sw(a1, a0, snd::kCbFunc);
}

// 0x0054D328 sub_54D328 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: attach AHX. [ACSND_AttachAhx]
void sub_54D328(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d328
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5335B0_005335b0(ctx);  // tail call
}

// 0x0054D340 sub_54D340 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: detach AHX. [ACSND_DetachAhx]
void sub_54D340(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d340
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5336C0_005336c0(ctx);  // tail call
}

// 0x0054D358 sub_54D358 -- 28 bytes; frame 0x10: ra sp+0x0
// Public: set the fader curve. [ACSND_SetFadeCurve]
void sub_54D358(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d358
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = sll(a1, 24);
    sd(ra, sp, 0x0);
    a1 = sra(a1, 24);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533E98_00533e98(ctx);  // tail call
}

// 0x0054D378 sub_54D378 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: the current ADXT handle. [ACSND_GetActiveAdxt]
void sub_54D378(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d378
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5337A8_005337a8(ctx);  // tail call
}

// 0x0054D390 atan2l_5 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: the next ADXT handle. [ACSND_GetNextAdxt]
void atan2l_5(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d390
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533808_00533808(ctx);  // tail call
}

// 0x0054D3A8 cosl_5 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: player n's ADXT handle. [ACSND_GetAdxt]
void cosl_5(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d3a8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533880_00533880(ctx);  // tail call
}

// 0x0054D3C0 coshl_5 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: the number of ADXT players. [ACSND_GetNumAdxt]
void coshl_5(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d3c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533900_00533900(ctx);  // tail call
}

// 0x0054D3D8 expl_5 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: the current AIXP handle. [ACSND_GetActiveAixp]
void expl_5(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d3d8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533950_00533950(ctx);  // tail call
}

// 0x0054D3F0 hypotf_5 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: the next AIXP handle. [ACSND_GetNextAixp]
void hypotf_5(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d3f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5339A8_005339a8(ctx);  // tail call
}

// 0x0054D408 sub_54D408 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: player n's AIXP handle. [ACSND_GetAixp]
void sub_54D408(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d408
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533A18_00533a18(ctx);  // tail call
}

// 0x0054D420 sub_54D420 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: the number of AIXP players. [ACSND_GetNumAixp]
void sub_54D420(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d420
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533A88_00533a88(ctx);  // tail call
}

// 0x0054D438 sub_54D438 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: cancel the running fade. [ACSND_CancelFading]
void sub_54D438(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d438
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533AC8_00533ac8(ctx);  // tail call
}

// 0x0054D450 sub_54D450 -- 20 bytes; frame 0x10: ra sp+0x0
// Public: the busy flag. [ACSND_IsBusy]
void sub_54D450(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d450
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533CA0_00533ca0(ctx);  // tail call
}

// 0x0054D468 sub_54D468 -- 52 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Public: enable ducking (the server's ACSVHL +76 = 1). [ACSVHL_Enable]
void sub_54D468(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d468
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(a0, v0, 16196);  // 0x793F44
    sd(ra, sp, 0x0);
    jal(ctx, 0x54D478u, gen::fn_sub_535170_00535170);
    ld(ra, sp, 0x0);
    a0 = v0;
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00535330
    charge(ctx, 3);
    v0 = 1;
    sw(v0, a0, 76);
}

// 0x0054D490 sub_54D490 -- 48 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Public: disable ducking. [ACSVHL_Disable]
void sub_54D490(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d490
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(a0, v0, 16196);  // 0x793F44
    sd(ra, sp, 0x0);
    jal(ctx, 0x54D4A0u, gen::fn_sub_535170_00535170);
    ld(ra, sp, 0x0);
    a0 = v0;
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00535340
    charge(ctx, 2);
    sw(zero, a0, 76);
}

// 0x0054D4B8 sub_54D4B8 -- 64 bytes, 2 chunks; frame 0x10: s0 sp+0x0, ra sp+0x8
// Public: set the ducking lowering frames (+84). [ACSVHL_SetDownTime]
void sub_54D4B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d4b8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    s0 = a0;
    lw(a0, v0, 16196);  // 0x793F44
    sd(ra, sp, 0x8);
    jal(ctx, 0x54D4D0u, gen::fn_sub_535170_00535170);
    a1 = s0;
    ld(ra, sp, 0x8);
    a0 = v0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00535370
    charge(ctx, 2);
    sw(a1, a0, 84);
}

// 0x0054D4F0 sub_54D4F0 -- 64 bytes, 2 chunks; frame 0x10: s0 sp+0x0, ra sp+0x8
// Public: set the ducking restoring frames (+88). [ACSVHL_SetUpTime]
void sub_54D4F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d4f0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    s0 = a0;
    lw(a0, v0, 16196);  // 0x793F44
    sd(ra, sp, 0x8);
    jal(ctx, 0x54D508u, gen::fn_sub_535170_00535170);
    a1 = s0;
    ld(ra, sp, 0x8);
    a0 = v0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00535378
    charge(ctx, 2);
    sw(a1, a0, 88);
}

}  // namespace p3fes::game
