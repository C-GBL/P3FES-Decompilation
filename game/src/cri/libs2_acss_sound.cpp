// Phase 5 slice libs2: ACSS, part 3: the sound object -- create / destroy, the start requests, stop, pause,
// cross-fades between its players, volume / status accessors and the per-frame update (0x532788-0x5349F8).
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

// 0x00532788 sub_532788 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Sound create: in a caller's work of at least 208 bytes (else an error and 0), reset (named by its error text).
//   [ACSSND_Create]
void sub_532788(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532788
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = sltiu(a1, 208);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x005327a0
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 1880);  // "E2003091205 ACSSND_Create : Work pointor is NULL."
        goto L_005327c0;
    }
    // 0x005327b0
    charge(ctx, 2);
    if (a1 == 0) {
        // 0x005327d0
        charge(ctx, 3);
        jal(ctx, 0x5327D0u, gen::fn_sub_533F10_00533f10);
        v0 = s0;
    } else {
        // 0x005327b8
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 1936);  // "E2003091206 ACSSND_Create : Work size is too small."
    L_005327c0:
        charge(ctx, 4);
        jal(ctx, 0x5327C0u, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x005327dc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005327F0 sub_5327F0 -- 36 bytes; frame 0x10: ra sp+0x0
// Sound destroy: the reset, when it exists. [ACSSND_Destroy]
void sub_5327F0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005327f0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00532808
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005327fc
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_533F10_00533f10(ctx);  // tail call
}

// 0x00532818 sub_532818 -- 1304 bytes; frame 0x70: s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, s3 sp+0x38, s7 sp+0x58, s4 sp+0x40, s5 sp+0x48, s6 sp+0x50, fp sp+0x60, ra sp+0x68
// Sound init from a 40-byte configuration and a work area (named by its error text): one or two players (two for
//   cross-fades), each a back end (AIX or ADX) whose player gets the input / PCM buffers the configuration asks for,
//   and a fader; then the AHX buffers, the 256-byte name buffer and the AIX track volumes; 'too small' when the work
//   runs out (everything made so far is finished again). [ACSSND_Init]
void sub_532818(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00532818
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s0, sp, 0x20);
    s0 = 1;
    sd(s1, sp, 0x28);
    s1 = a1;
    sd(s2, sp, 0x30);
    s2 = a0;
    sd(s3, sp, 0x38);
    s3 = 0;
    sd(s7, sp, 0x58);
    s7 = a2;
    sd(s4, sp, 0x40);
    sd(s5, sp, 0x48);
    sd(s6, sp, 0x50);
    sd(fp, sp, 0x60);
    sd(ra, sp, 0x68);
    lw(v0, s2, snd::kInit);
    sw(a3, sp, 0x10);
    if (v0 != s0) {
        // 0x00532864
        charge(ctx, 3);
        lw(v0, s2, snd::kIniting);
        if (v0 == s0) {
            goto L_00532870;
        }
        // 0x00532888
        charge(ctx, 31);
        jal(ctx, 0x532888u, gen::fn_sub_533F10_00533f10);
        sw(s0, s2, snd::kIniting);
        a0 = sp;
        a1 = 0;
        ldl(v0, s1, 7);
        ldr(v0, s1, 0);
        ldl(v1, s1, 15);
        ldr(v1, s1, 8);
        ldl(a2, s1, 23);
        ldr(a2, s1, 16);
        ldl(a3, s1, 31);
        ldr(a3, s1, 24);
        sdl(v0, s2, 127);
        sdr(v0, s2, 120);
        sdl(v1, s2, 135);
        sdr(v1, s2, 128);
        sdl(a2, s2, 143);
        sdr(a2, s2, 136);
        sdl(a3, s2, 151);
        sdr(a3, s2, 144);
        ldl(v0, s1, 39);
        ldr(v0, s1, 32);
        sdl(v0, s2, 159);
        sdr(v0, s2, 152);
        a2 = 12;
        jal(ctx, 0x5328ECu, gen::fn_memset_00521408);
        lw(v1, s1, 4);
        lw(v0, s1, 28);
        sw(v1, sp, 0x0);
        if (v0 != s0) {
            // 0x00532910
            charge(ctx, 1);
            sw(s0, sp, 0x4);
        } else {
            // 0x00532904
            charge(ctx, 3);
            lw(v0, s1, 12);
            sw(v0, sp, 0x4);
        }
        // 0x00532914
        charge(ctx, 5);
        lw(v1, s1, 36);
        a0 = 1;
        lw(v0, s1, 24);
        sw(v1, sp, 0x8);
        if (v0 != a0) {
            // 0x00532938
            charge(ctx, 2);
            sw(a0, s2, snd::kNumPlayer);
            sw(zero, s2, snd::kCross);
        } else {
            // 0x00532928
            charge(ctx, 4);
            v0 = 2;
            sw(a0, s2, snd::kCross);
            sw(v0, s2, snd::kNumPlayer);
        }
        // 0x00532940
        charge(ctx, 3);
        lw(a0, s2, snd::kNumPlayer);
        sw(zero, sp, 0x14);
        if (i64(a0) > 0) {
            // 0x0053294c
            charge(ctx, 9);
            v0 = addiu(s2, 8);
            v1 = 16;
            sw(v0, sp, 0x18);
            s6 = 1000;
            sw(v1, sp, 0x1C);
            s5 = 44;
            fp = addiu(s2, 0x18);
            s4 = s2;
            for (;;) {
                // 0x00532970
                charge(ctx, 3);
                lw(v0, s1, 28);
                a0 = addu(s7, s3);
                if (v0 != 0) {
                    // 0x0053297c
                    charge(ctx, 4);
                    a1 = 16;
                    jal(ctx, 0x53297Cu, gen::fn_sub_532458_00532458);
                    sw(v0, s4, 0);
                    if (v0 == 0) {
                        goto L_00532ca8;
                    }
                    // 0x0053298c
                    charge(ctx, 3);
                    lw(v0, s1, 36);
                    s3 = addiu(s3, 16);
                    if (v0 == 0) {
                        // 0x005329f8
                        charge(ctx, 3);
                        lw(v0, s1, 8);
                        if (s6 == 0) {
                            brk(ctx, 0x532A00u, 0x7u);
                        }
                        // 0x00532a04
                        charge(ctx, 26);
                        lw(v1, s1, 4);
                        div(v0, s6);
                        lw(a0, s1, 0);
                        a1 = sll(v1, 6);
                        lw(a2, s1, 12);
                        a1 = addu(a1, v1);
                        a0 = addiu(a0, 1);
                        a1 = sll(a1, 2);
                        a1 = subu(a1, v1);
                        a1 = sll(a1, 6);
                        mflo(v0);
                        mult(v1, v1, v0);
                        v0 = 25000;
                        mult1(v1, v1, v0);
                        div(v1, s5);
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
                        mult(v0, v0, a2);
                    } else {
                        // 0x00532998
                        charge(ctx, 4);
                        lw(v1, s1, 8);
                        v0 = 25000;
                        if (s6 == 0) {
                            brk(ctx, 0x5329A4u, 0x7u);
                        }
                        // 0x005329a8
                        charge(ctx, 19);
                        div(v1, s6);
                        lw(a0, s1, 0);
                        lw(a1, s1, 12);
                        a0 = addiu(a0, 1);
                        mflo(v1);
                        mult(v1, v1, v0);
                        div(v1, s5);
                        mflo(v1);
                        mult(v1, v1, a0);
                        v0 = addiu(v1, 2048);
                        v1 = addiu(v1, 4095);
                        a0 = slti(v0, 0);
                        if (a0 != 0) v0 = v1;
                        v0 = sra(v0, 11);
                        v0 = sll(v0, 11);
                        at = 0x85A4;
                        v0 = addu(at, v0);
                        mult(v0, v0, a1);
                    }
                    // 0x00532a6c
                    charge(ctx, 10);
                    s0 = addiu(v0, 64);
                    lw(a0, s4, 0);
                    a1 = sp;
                    a2 = addu(s7, s3);
                    lw(v1, a0, 0);
                    lw(v0, v1, 0);
                    a3 = s0;
                    jalr(ctx, 0x532A84u, v0.u());
                    a0 = 0x7C0000;
                    if (v0 == 0) {
                        goto L_00532cb8;
                    }
                    // 0x00532a94
                    charge(ctx, 2);
                    lw(v0, s4, 0);
                    goto L_00532bc0;
                }
                // 0x00532aa0
                charge(ctx, 4);
                a1 = 12;
                jal(ctx, 0x532AA0u, gen::fn_sub_532118_00532118);
                sw(v0, s4, 0);
                if (v0 == 0) {
                    goto L_00532cc0;
                }
                // 0x00532ab0
                charge(ctx, 3);
                lw(v0, s1, 36);
                s3 = addiu(s3, 12);
                if (v0 == 0) {
                    // 0x00532b20
                    charge(ctx, 3);
                    lw(v0, s1, 8);
                    if (s6 == 0) {
                        brk(ctx, 0x532B28u, 0x7u);
                    }
                    // 0x00532b2c
                    charge(ctx, 28);
                    lw(v1, s1, 4);
                    div(v0, s6);
                    lw(a0, s1, 0);
                    a1 = sll(v1, 6);
                    lw(a2, s1, 16);
                    a1 = addu(a1, v1);
                    a0 = addiu(a0, 1);
                    a1 = sll(a1, 2);
                    a1 = subu(a1, v1);
                    a1 = sll(a1, 6);
                    mflo(v0);
                    mult(v1, v1, v0);
                    v0 = 25000;
                    mult1(v1, v1, v0);
                    div(v1, s5);
                    mflo(v1);
                    mult(v1, v1, a0);
                    v0 = addiu(v1, 2048);
                    v1 = addiu(v1, 4095);
                    a0 = slti(v0, 0);
                    if (a0 != 0) v0 = v1;
                    v0 = sra(v0, 11);
                    v0 = sll(v0, 11);
                    v0 = addiu(v0, 36);
                    mult(v0, v0, a2);
                    v0 = addu(v0, a1);
                    s0 = addiu(v0, 64);
                    lw(a0, s4, 0);
                } else {
                    // 0x00532abc
                    charge(ctx, 4);
                    lw(v1, s1, 8);
                    v0 = 25000;
                    if (s6 == 0) {
                        brk(ctx, 0x532AC8u, 0x7u);
                    }
                    // 0x00532acc
                    charge(ctx, 21);
                    div(v1, s6);
                    lw(a0, s1, 0);
                    lw(a1, s1, 16);
                    a0 = addiu(a0, 1);
                    mflo(v1);
                    mult(v1, v1, v0);
                    div(v1, s5);
                    mflo(v1);
                    mult(v1, v1, a0);
                    v0 = addiu(v1, 2048);
                    v1 = addiu(v1, 4095);
                    a0 = slti(v0, 0);
                    if (a0 != 0) v0 = v1;
                    v0 = sra(v0, 11);
                    v0 = sll(v0, 11);
                    v0 = addiu(v0, 36);
                    mult(v0, v0, a1);
                    s0 = 0x85C0;
                    s0 = addu(s0, v0);
                    lw(a0, s4, 0);
                }
                // 0x00532b9c
                charge(ctx, 8);
                a1 = sp;
                a2 = addu(s7, s3);
                lw(v1, a0, 0);
                lw(v0, v1, 0);
                a3 = s0;
                jalr(ctx, 0x532BACu, v0.u());
                a0 = 0x7C0000;
                if (v0 == 0) {
                    goto L_00532cd0;
                }
                // 0x00532bbc
                charge(ctx, 1);
                lw(v0, s4, 0);
            L_00532bc0:
                charge(ctx, 10);
                s3 = addu(s3, s0);
                lw(s0, sp, 0x18);
                sw(v0, fp, 0x0);
                a0 = addu(s7, s3);
                a1 = 68;
                jal(ctx, 0x532BD0u, gen::fn_sub_531A28_00531a28);
                lw(a0, sp, 0x1C);
                v1 = addu(s2, a0);
                sw(v0, v1, 16);
                if (v0 == 0) {
                    goto L_00532cd8;
                }
                // 0x00532be8
                charge(ctx, 12);
                lw(a2, sp, 0x14);
                s3 = addiu(s3, 68);
                lw(a0, s2, snd::kNumPlayer);
                fp = addiu(fp, 0xC);
                lw(a3, sp, 0x1C);
                a2 = addiu(a2, 1);
                v0 = slt(a2, a0);
                sw(a2, sp, 0x14);
                a3 = addiu(a3, 12);
                s4 = addiu(s4, 4);
                sw(a3, sp, 0x1C);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00532c18
            charge(ctx, 2);
            sw(zero, s2, snd::kCurIdx);
            goto L_00532c28;
        }
        // 0x00532c20
        charge(ctx, 2);
        s0 = addiu(s2, 8);
        sw(zero, s2, snd::kCurIdx);
    L_00532c28:
        charge(ctx, 5);
        s4 = 1;
        lw(v0, s2, snd::kPlayers);
        lw(v1, s1, 32);
        sw(v0, s0, 0);
        if (v1 == s4) {
            // 0x00532c3c
            charge(ctx, 6);
            v0 = sll(a0, 1);
            v1 = addu(s7, s3);
            v0 = addu(v0, a0);
            sw(v1, s2, snd::kAhxWork);
            v0 = sll(v0, 12);
            s3 = addu(s3, v0);
        }
        // 0x00532c54
        charge(ctx, 6);
        lw(v1, s1, 28);
        v0 = addu(s7, s3);
        sw(v0, s2, snd::kReqName);
        s3 = addiu(s3, 256);
        sw(v0, s2, snd::kNameBuf);
        if (v1 == s4) {
            // 0x00532c6c
            charge(ctx, 8);
            lw(v0, s1, 12);
            a0 = addu(s7, s3);
            sw(a0, s2, snd::kTrackVol);
            a1 = 0;
            v0 = sll(v0, 2);
            a2 = v0;
            s3 = addu(s3, v0);
            jal(ctx, 0x532C84u, gen::fn_memset_00521408);
        }
        // 0x00532c8c
        charge(ctx, 4);
        lw(v1, sp, 0x10);
        v0 = slt(v1, s3);
        if (v0 == 0) {
            sw(s4, s2, snd::kInit);
            // 0x00532cf8
            charge(ctx, 2);
            v0 = 1;
            sw(zero, s2, snd::kIniting);
        } else {
            // 0x00532c9c
            charge(ctx, 3);
            a0 = 0x7C0000;
            a0 = addiu(a0, 2328);  // "E2003052809 ACSSND_Init : Specified work area size is too small."
        L_00532ce0:
            charge(ctx, 6);
            jal(ctx, 0x532CE0u, gen::fn_sub_531A10_00531a10);
            a0 = s2;
            jal(ctx, 0x532CE8u, gen::fn_sub_532D30_00532d30);
            v0 = 0;
        }
        // 0x00532d00 (the shared epilogue, written out on this path)
        charge(ctx, 12);
        ld(s0, sp, 0x20);
        ld(s1, sp, 0x28);
        ld(s2, sp, 0x30);
        ld(s3, sp, 0x38);
        ld(s4, sp, 0x40);
        ld(s5, sp, 0x48);
        ld(s6, sp, 0x50);
        ld(s7, sp, 0x58);
        ld(fp, sp, 0x60);
        ld(ra, sp, 0x68);
        sp = addiu(sp, 0x70);
        return;
    }
L_00532870:
    charge(ctx, 5);
    a0 = 0x7C0000;
    a0 = addiu(a0, 1992);  // "E2003052806 ACSSND_Init : Already initialized."
    jal(ctx, 0x532874u, gen::fn_sub_531A10_00531a10);
    v0 = 0;
    // 0x00532d00 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(s7, sp, 0x58);
    ld(fp, sp, 0x60);
    ld(ra, sp, 0x68);
    sp = addiu(sp, 0x70);
    return;
L_00532ca8:
    charge(ctx, 3);
    a0 = 0x7C0000;
    a0 = addiu(a0, 2040);  // "E2003091204 ACSSND_Init : Failed to create ACSSBAIX."
    goto L_00532ce0;
L_00532cb8:
    charge(ctx, 2);
    a0 = addiu(a0, 2096);
    goto L_00532ce0;
L_00532cc0:
    charge(ctx, 3);
    a0 = 0x7C0000;
    a0 = addiu(a0, 2152);  // "E2003091204 ACSSND_Init : Failed to create ACSSBADX."
    goto L_00532ce0;
L_00532cd0:
    charge(ctx, 2);
    a0 = addiu(a0, 2208);
    goto L_00532ce0;
L_00532cd8:
    charge(ctx, 2);
    a0 = 0x7C0000;
    a0 = addiu(a0, 2264);  // "E2003091203 ACSSND_Init : Failed to create fader handle."
    goto L_00532ce0;
}

// 0x00532D30 sub_532D30 -- 216 bytes; frame 0x30: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Sound finish: destroy every player's fader, back-end player and back end. [ACSSND_Finish]
void sub_532D30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532d30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    lw(v0, s1, snd::kInit);
    if (v0 == v1) {
        lw(v0, s1, snd::kNumPlayer);
    } else {
        // 0x00532d5c
        charge(ctx, 3);
        lw(v0, s1, snd::kIniting);
        ld(s0, sp, 0x0);
        if (v0 == v1) {
            // 0x00532d68
            charge(ctx, 1);
            lw(v0, s1, snd::kNumPlayer);
            goto L_00532d6c;
        }
        // 0x00532df0 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_00532d6c:
    charge(ctx, 4);
    s3 = 0;
    sw(zero, s1, snd::kInit);
    sw(zero, s1, snd::kIniting);
    if (i64(v0) > 0) {
        // 0x00532d7c
        charge(ctx, 3);
        s0 = s1;
        s2 = addiu(s1, 32);
        for (;;) {
            // 0x00532d88
            charge(ctx, 6);
            lw(a0, s2, 0);
            s2 = addiu(s2, 12);
            jal(ctx, 0x532D8Cu, gen::fn_sub_531A90_00531a90);
            lw(v0, s0, 0);
            a0 = v0;
            if (v0 != 0) {
                // 0x00532da0
                charge(ctx, 7);
                lw(v0, v0, 0);
                lw(v1, v0, 4);
                jalr(ctx, 0x532DA8u, v1.u());
                lw(v0, s1, snd::kCprmAix);
                if (v0 == 0) {
                    // 0x00532dd0
                    charge(ctx, 2);
                    link(ctx, 0x532DD0u);  // $ra first: the delay slot below depends on it
                    lw(a0, s0, 0);
                    call(ctx, gen::fn_sub_532180_00532180);
                    goto L_00532dd8;
                }
                // 0x00532dbc
                charge(ctx, 4);
                link(ctx, 0x532DBCu);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 0);
                call(ctx, gen::fn_sub_5324C0_005324c0);
                lw(v0, s1, snd::kNumPlayer);
                goto L_00532ddc;
            }
        L_00532dd8:
            charge(ctx, 1);
            lw(v0, s1, snd::kNumPlayer);
        L_00532ddc:
            charge(ctx, 4);
            s3 = addiu(s3, 1);
            v0 = slt(s3, v0);
            s0 = addiu(s0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00532dec
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x00532df0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00532E08 sub_532E08 -- 8 bytes; leaf frame (no stack)
// Sound initialised flag (+80). [ACSSND_IsInit]
void sub_532E08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00532e08
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, snd::kInit);
}

// 0x00532E10 sub_532E10 -- 92 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Start a named file (named by its error text): the name copied into the sound's buffer (256), request type 0, then
//   the start. [ACSSND_StartFname]
void sub_532E10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532e10
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, snd::kInit);
    if (v0 == 0) {
        // 0x00532e2c
        charge(ctx, 6);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        a0 = addiu(a0, 2400);  // "E2003052810 ACSSND_StartFname : Not initialized."
        sp = addiu(sp, 0x10);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    lw(a0, s0, snd::kReqName);
    // 0x00532e48
    charge(ctx, 9);
    a2 = 256;
    link(ctx, 0x532E4Cu);  // $ra first: the delay slot below depends on it
    sw(zero, s0, snd::kReqType);
    call(ctx, gen::fn_strncpy_00524828);
    a0 = s0;
    ld(ra, sp, 0x8);
    a1 = addiu(a0, 48);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_534010_00534010(ctx);  // tail call
}

// 0x00532E70 sub_532E70 -- 76 bytes; frame 0x10: ra sp+0x0
// Start a partition file (request type 1: partition, file; named by its error text). [ACSSND_StartAfs]
void sub_532E70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532e70
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = a0;
    sd(ra, sp, 0x0);
    a3 = a1;
    lw(v0, v1, 80);
    a1 = addiu(v1, 48);
    if (v0 == 0) {
        // 0x00532e8c
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 2456);  // "E2003052900 ACSSND_StartAfs : Not initialized."
        sp = addiu(sp, 0x10);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    // 0x00532ea0
    charge(ctx, 7);
    ld(ra, sp, 0x0);
    v0 = 1;
    sw(a3, v1, 56);
    sw(a2, v1, 60);
    sw(v0, v1, 48);
    sp = addiu(sp, 0x10);
    gen::fn_sub_534010_00534010(ctx);  // tail call
}

// 0x00532EC0 sub_532EC0 -- 76 bytes; frame 0x10: ra sp+0x0
// Start from memory (request type 2: address, size; named by its error text). [ACSSND_StartMem]
void sub_532EC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532ec0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = a0;
    sd(ra, sp, 0x0);
    a3 = a1;
    lw(v0, v1, 80);
    a1 = addiu(v1, 48);
    if (v0 == 0) {
        // 0x00532edc
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 2504);  // "E2003060602 ACSSND_StartMem : Not initialized."
        sp = addiu(sp, 0x10);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    // 0x00532ef0
    charge(ctx, 7);
    ld(ra, sp, 0x0);
    v0 = 2;
    sw(a3, v1, 64);
    sw(a2, v1, 68);
    sw(v0, v1, 48);
    sp = addiu(sp, 0x10);
    gen::fn_sub_534010_00534010(ctx);  // tail call
}

// 0x00532F10 sub_532F10 -- 76 bytes; frame 0x10: ra sp+0x0
// Start a memory index entry (request type 3: index, entry; named by its error text). [ACSSND_StartMemIdx]
void sub_532F10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532f10
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = a0;
    sd(ra, sp, 0x0);
    a3 = a1;
    lw(v0, v1, 80);
    a1 = addiu(v1, 48);
    if (v0 == 0) {
        // 0x00532f2c
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 2552);  // "E2003060603 ACSSND_StartMemIdx : Not initialized."
        sp = addiu(sp, 0x10);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    // 0x00532f40
    charge(ctx, 7);
    ld(ra, sp, 0x0);
    v0 = 3;
    sw(a3, v1, 72);
    sw(a2, v1, 76);
    sw(v0, v1, 48);
    sp = addiu(sp, 0x10);
    gen::fn_sub_534010_00534010(ctx);  // tail call
}

// 0x00532F60 sub_532F60 -- 324 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Stop: fade the current player out (the fade-out frames +168, then stop); when paused stop it at once and silence
//   its fader, and the other player's too in cross-fade mode. [ACSSND_Stop]
void sub_532F60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00532f60
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v0, s0, snd::kInit);
    a0 = 0x7C0000;
    if (v0 == 0) {
        // 0x00532f84
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 2608);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    // 0x00532fa0
    charge(ctx, 19);
    jal(ctx, 0x532FA0u, gen::fn_coshl_005319c8);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x532FACu, gen::fn_sub_534530_00534530);
    lw(v0, s0, snd::kCurIdx);
    a0 = s0;
    a2 = 0;
    a1 = sll(v0, 1);
    a3 = 2;
    a1 = addu(a1, v0);
    a1 = sll(a1, 2);
    a1 = addu(s0, a1);
    a1 = addiu(a1, 24);
    jal(ctx, 0x532FD4u, gen::fn_sub_534488_00534488);
    lw(v1, s0, snd::kPause);
    v0 = 1;
    if (v1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00532fec
        charge(ctx, 22);
        lw(v1, s0, snd::kCurIdx);
        s1 = addiu(s0, 8);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, s1);
        lw(a0, v0, 16);
        lw(v1, a0, 0);
        lw(v0, v1, 24);
        s2 = addiu(s0, 16);
        jalr(ctx, 0x533010u, v0.u());
        lw(v1, s0, snd::kCurIdx);
        a1 = si(-960);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, s2);
        link(ctx, 0x533030u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 16);
        call(ctx, gen::fn_sub_531AD0_00531ad0);
        lw(v0, s0, snd::kCross);
        if (v0 == 0) {
            ld(s0, sp, 0x0);
        } else {
            // 0x00533044
            charge(ctx, 19);
            lw(v1, s0, snd::kPrevIdx);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, s1);
            lw(a0, v0, 16);
            lw(v1, a0, 0);
            lw(v0, v1, 24);
            jalr(ctx, 0x533064u, v0.u());
            lw(v1, s0, snd::kPrevIdx);
            a1 = si(-960);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, s2);
            link(ctx, 0x533084u);  // $ra first: the delay slot below depends on it
            lw(a0, v0, 16);
            call(ctx, gen::fn_sub_531AD0_00531ad0);
            ld(s0, sp, 0x0);
        }
    }
    // 0x00533090
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_expl_005319e0(ctx);  // tail call
}

// 0x005330A8 sub_5330A8 -- 184 bytes; frame 0x30: s1 sp+0x8, s3 sp+0x18, s0 sp+0x0, s2 sp+0x10, ra sp+0x20
// Pause / resume every player; the flag kept at +96 (named by its error text). [ACSSND_Pause]
void sub_5330A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005330a8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    lw(v0, s1, snd::kInit);
    s3 = a1;
    if (v0 == 0) {
        // 0x005330d0
        charge(ctx, 9);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 2656);  // "E2003052902 ACSSND_Pause : Not initialized."
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    // 0x005330f8
    charge(ctx, 5);
    s2 = 0;
    jal(ctx, 0x5330F8u, gen::fn_coshl_005319c8);
    lw(v0, s1, snd::kNumPlayer);
    if (i64(v0) <= 0) {
        sw(s3, s1, snd::kPause);
    } else {
        // 0x0053310c
        charge(ctx, 3);
        s0 = addiu(s1, 24);
        lw(a0, s0, 0);
        for (;;) {
            // 0x00533118
            charge(ctx, 10);
            s0 = addiu(s0, 12);
            a1 = s3;
            lw(v0, a0, 0);
            lw(v1, v0, 28);
            s2 = addiu(s2, 1);
            jalr(ctx, 0x533128u, v1.u());
            lw(v0, s1, snd::kNumPlayer);
            v0 = slt(s2, v0);
            if (v0 == 0) {
                break;
            }
            lw(a0, s0, 0);
            backedge(ctx);
        }
        // 0x00533140
        charge(ctx, 1);
        sw(s3, s1, snd::kPause);
    }
    // 0x00533144
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_expl_005319e0(ctx);  // tail call
}

// 0x00533160 sub_533160 -- 72 bytes; frame 0x10: ra sp+0x0
// The current player's pause state (4 when not initialised; named by its error text). [ACSSND_GetStatPause]
void sub_533160(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00533160
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 80);
    if (v0 != 0) {
        lw(v0, a0, 8);
        // 0x00533188
        charge(ctx, 5);
        lw(v1, v0, 0);
        a0 = v0;
        lw(v0, v1, 32);
        jalr(ctx, 0x533194u, v0.u());
    } else {
        // 0x00533174
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 2704);  // "E2003062001 ACSSND_GetStatPause : Not initialized."
        jal(ctx, 0x533178u, gen::fn_sub_531A10_00531a10);
        v0 = 4;
    }
    // 0x0053319c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005331A8 sub_5331A8 -- 72 bytes; frame 0x10: ra sp+0x0
// The current player's status (method 9; 4 when not initialised; named by its error text). [ACSSND_GetStat]
void sub_5331A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005331a8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 80);
    if (v0 != 0) {
        lw(v0, a0, 8);
        // 0x005331d0
        charge(ctx, 5);
        lw(v1, v0, 0);
        a0 = v0;
        lw(v0, v1, 36);
        jalr(ctx, 0x5331DCu, v0.u());
    } else {
        // 0x005331bc
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 2760);  // "E2003060200 ACSSND_GetStat : Not initialized."
        jal(ctx, 0x5331C0u, gen::fn_sub_531A10_00531a10);
        v0 = 4;
    }
    // 0x005331e4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005331F0 sub_5331F0 -- 52 bytes; frame 0x10: ra sp+0x0
// The sound's creation parameters (the configuration at +120; 0 when not initialised; named by its error text).
//   [ACSSND_GetCprm]
void sub_5331F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005331f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    lw(v1, v0, 80);
    v0 = addiu(v0, 120);
    if (v1 == 0) {
        // 0x00533208
        charge(ctx, 4);
        a0 = 0x7C0000;
        a0 = addiu(a0, 2808);  // "E2003060604 ACSSND_GetCprm : Not initialized."
        jal(ctx, 0x53320Cu, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x00533218 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00533230 sub_533230 -- 8 bytes; leaf frame (no stack)
// The sound's kind (+140, s8: kind 1 is lowered while a kind-2 sound plays). [ACSSND_GetKind]
void sub_533230(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00533230
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, snd::kKind);
}

// 0x00533238 sub_533238 -- 260 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, s3 sp+0x18, ra sp+0x20
// Set the volume (named by its error text): kept at +188; unless the current player is fading in, fade it to the new
//   volume over +176 frames (hold +184). [ACSSND_SetOutVol]
void sub_533238(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00533238
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    lw(v0, s2, snd::kInit);
    s0 = a1;
    if (v0 == 0) {
        // 0x00533260
        charge(ctx, 9);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 2856);  // "E2003052903 ACSSND_SetOutVol : Not initialized."
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    // 0x00533288
    charge(ctx, 14);
    jal(ctx, 0x533288u, gen::fn_coshl_005319c8);
    a1 = 1;
    lw(v1, s2, snd::kCurIdx);
    a2 = 1;
    sw(s0, s2, snd::kOutVol);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(s2, v0);
    s3 = addiu(v0, 24);
    lb(v1, s3, 4);
    a0 = s2;
    if (v1 != a2) {
        // 0x005332c0
        charge(ctx, 24);
        jal(ctx, 0x5332C0u, gen::fn_sub_534530_00534530);
        a3 = 0;
        lw(s1, s3, 8);
        a1 = s0;
        lw(t0, s2, snd::kHoldTime);
        s0 = 0x530000;
        lw(a2, s2, snd::kVolChgTime);
        a0 = s1;
        s0 = addiu(s0, 18888);  // &sub_5349C8
        jal(ctx, 0x5332E4u, gen::fn_sub_531B00_00531b00);
        a3 = 2;
        a0 = s1;
        a1 = s0;
        a2 = s2;
        jal(ctx, 0x5332F8u, gen::fn_sub_531D48_00531d48);
        a0 = s1;
        a1 = s0;
        a2 = s2;
        a3 = 5;
        jal(ctx, 0x53330Cu, gen::fn_sub_531D58_00531d58);
        v0 = 3;
        sb(v0, s3, 4);
        sb(zero, s3, 5);
    }
    // 0x00533320
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_expl_005319e0(ctx);  // tail call
}

// 0x00533340 sub_533340 -- 272 bytes; frame 0x30: s0 sp+0x0, s3 sp+0x18, s4 sp+0x20, s1 sp+0x8, s2 sp+0x10, ra sp+0x28
// Set an AIX track's volume (named by its error text): kept in the track array +192 and sent to every player with the
//   sound's volume added. [ACSSND_SetTrackVol]
void sub_533340(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00533340
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x28);
    lw(v0, s0, snd::kInit);
    s4 = a2;
    if (v0 == 0) {
        // 0x00533370
        charge(ctx, 10);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 2904);  // "E2003061002 ACSSND_SetTrackVol : Not initialized."
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    // 0x00533398
    charge(ctx, 3);
    lw(v0, s0, snd::kCprmAix);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005333a4
        charge(ctx, 2);
        if (i64(s3) < 0) {
            ld(s0, sp, 0x0);
        } else {
            // 0x005333ac
            charge(ctx, 4);
            lw(v0, s0, snd::kCprmNumTrack);
            v0 = slt(s3, v0);
            if (v0 == 0) {
                ld(s0, sp, 0x0);
            } else {
                // 0x005333bc
                charge(ctx, 3);
                lw(a0, s0, snd::kTrackVol);
                v0 = sll(s3, 2);
                if (a0 != 0) {
                    // 0x005333c8
                    charge(ctx, 6);
                    v1 = 1;
                    v0 = addu(v0, a0);
                    sw(s4, v0, 0);
                    lb(a0, s0, snd::kBusy);
                    if (a0 != v1) {
                        lw(v0, s0, snd::kNumPlayer);
                    } else {
                        // 0x005333e0
                        charge(ctx, 3);
                        lw(v0, s0, snd::kPause);
                        if (v0 == a0) {
                            // 0x005333ec
                            charge(ctx, 1);
                            lw(v0, s0, snd::kNumPlayer);
                            goto L_005333f0;
                        }
                        ld(s0, sp, 0x0);
                        // 0x00533434 (the shared epilogue, written out on this path)
                        charge(ctx, 7);
                        ld(s1, sp, 0x8);
                        ld(s2, sp, 0x10);
                        ld(s3, sp, 0x18);
                        ld(s4, sp, 0x20);
                        ld(ra, sp, 0x28);
                        sp = addiu(sp, 0x30);
                        return;
                    }
                L_005333f0:
                    charge(ctx, 2);
                    s2 = 0;
                    if (i64(v0) > 0) {
                        // 0x005333f8
                        charge(ctx, 2);
                        s1 = addiu(s0, 24);
                        lw(a0, s1, 0);
                        for (;;) {
                            // 0x00533400
                            charge(ctx, 12);
                            s1 = addiu(s1, 12);
                            lw(a2, s0, snd::kOutVol);
                            a1 = s3;
                            lw(v0, a0, 0);
                            s2 = addiu(s2, 1);
                            lw(v1, v0, 48);
                            a2 = addu(a2, s4);
                            jalr(ctx, 0x533418u, v1.u());
                            lw(v0, s0, snd::kNumPlayer);
                            v0 = slt(s2, v0);
                            if (v0 == 0) {
                                break;
                            }
                            lw(a0, s1, 0);
                            backedge(ctx);
                        }
                    }
                }
                // 0x00533430
                charge(ctx, 1);
                ld(s0, sp, 0x0);
            }
        }
    }
    // 0x00533434 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00533450 _ZNKSt9basic_iosIcSt11char_traitsIcEE10exceptionsEv -- 8 bytes; leaf frame (no stack)
// The sound's volume (+188). (A FLIRT name.) [ACSSND_GetOutVol]
void _ZNKSt9basic_iosIcSt11char_traitsIcEE10exceptionsEv(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00533450
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, snd::kOutVol);
}

// 0x005334A8 sub_5334A8 -- 172 bytes; frame 0x30: s1 sp+0x8, s3 sp+0x18, s0 sp+0x0, s2 sp+0x10, ra sp+0x20
// Method 14 (loop flag) on every player (named by its error text). [ACSSND_SetLpFlg]
void sub_5334A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005334a8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    lw(v0, s1, snd::kInit);
    s3 = a1;
    if (v0 == 0) {
        // 0x005334d0
        charge(ctx, 9);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 2960);  // "E2003052904 ACSSND_SetLpFlg : Not initialized."
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    // 0x005334f8
    charge(ctx, 3);
    lw(v0, s1, snd::kNumPlayer);
    s2 = 0;
    if (i64(v0) > 0) {
        // 0x00533504
        charge(ctx, 3);
        s0 = addiu(s1, 24);
        lw(a0, s0, 0);
        for (;;) {
            // 0x00533510
            charge(ctx, 10);
            s0 = addiu(s0, 12);
            a1 = s3;
            lw(v0, a0, 0);
            lw(v1, v0, 56);
            s2 = addiu(s2, 1);
            jalr(ctx, 0x533520u, v1.u());
            lw(v0, s1, snd::kNumPlayer);
            v0 = slt(s2, v0);
            if (v0 == 0) {
                break;
            }
            lw(a0, s0, 0);
            backedge(ctx);
        }
    }
    // 0x00533538 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00533570 sub_533570 -- 8 bytes; leaf frame (no stack)
// Fade-out frames (+168). [ACSSND_GetFadeOutTime]
void sub_533570(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00533570
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, snd::kFadeOutTime);
}

// 0x00533578 sub_533578 -- 8 bytes; leaf frame (no stack)
// Fade-in frames (+172). [ACSSND_GetFadeInTime]
void sub_533578(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00533578
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, snd::kFadeInTime);
}

// 0x00533580 sub_533580 -- 8 bytes; leaf frame (no stack)
// Volume-change frames (+176). [ACSSND_GetVolChgTime]
void sub_533580(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00533580
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, snd::kVolChgTime);
}

// 0x00533590 _ZNKSt9basic_iosIcSt11char_traitsIcEE3tieEv_0 -- 8 bytes; leaf frame (no stack)
// Cross-fade offset (+180). (A FLIRT name.) [ACSSND_GetCrossOffset]
void _ZNKSt9basic_iosIcSt11char_traitsIcEE3tieEv_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00533590
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, snd::kCrossOffset);
}

// 0x005335A0 sub_5335A0 -- 8 bytes; leaf frame (no stack)
// Hold frames (+184). [ACSSND_GetHoldTime]
void sub_5335A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005335a0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, snd::kHoldTime);
}

// 0x005335B0 sub_5335B0 -- 272 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Attach AHX to every player's ADXT (the AHX work at +108, 12,288 bytes each; named by its error text).
//   [ACSSND_AttachAhx]
void sub_5335B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005335b0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    lw(v0, s0, snd::kInit);
    if (v0 == 0) {
        // 0x005335d8
        charge(ctx, 9);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 3008);  // "E2003052911 ACSSND_AttachAhx : Not initialized."
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    lw(v0, s0, snd::kCprmAhx);
    // 0x00533600
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x00533608
        charge(ctx, 9);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 3056);  // "E2003052912 ACSSND_AttachAhx : Can't use AHX."
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    lw(v0, s0, snd::kNumPlayer);
    // 0x00533630
    charge(ctx, 2);
    s1 = 0;
    if (i64(v0) > 0) {
        // 0x00533638
        charge(ctx, 4);
        s3 = 1;
        s2 = 0;
        lw(v0, s0, snd::kCprmAix);
        for (;;) {
            // 0x00533648
            charge(ctx, 2);
            a1 = s1;
            if (v0 != s3) {
                // 0x00533670
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x533670u, gen::fn_sub_533880_00533880);
                lw(a1, s0, snd::kAhxWork);
            } else {
                // 0x00533650
                charge(ctx, 7);
                a0 = s0;
                jal(ctx, 0x533650u, gen::fn_sub_533A18_00533a18);
                a1 = 0;
                a0 = v0;
                jal(ctx, 0x53365Cu, gen::fn_sub_553230_00553230);
                lw(a1, s0, snd::kAhxWork);
            }
            // 0x0053367c
            charge(ctx, 10);
            a0 = v0;
            a2 = 12288;
            s1 = addiu(s1, 1);
            a1 = addu(a1, s2);
            s2 = addiu(s2, 12288);
            jal(ctx, 0x53368Cu, gen::fn_sub_54F5C0_0054f5c0);
            lw(v0, s0, snd::kNumPlayer);
            v0 = slt(s1, v0);
            if (v0 == 0) {
                break;
            }
            lw(v0, s0, snd::kCprmAix);
            backedge(ctx);
        }
    }
    // 0x005336a4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005336C0 sub_5336C0 -- 228 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Detach AHX from every player's ADXT (named by its error text). [ACSSND_DetachAhx]
void sub_5336C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005336c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v0, s0, snd::kInit);
    if (v0 == 0) {
        // 0x005336e4
        charge(ctx, 8);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 3104);  // "E2003052913 ACSSND_DetachAhx : Not initialized."
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    lw(v0, s0, snd::kCprmAhx);
    // 0x00533708
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x00533710
        charge(ctx, 8);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 3152);  // "E2003052914 ACSSND_DetachAhx : Can't use AHX."
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    lw(v0, s0, snd::kNumPlayer);
    // 0x00533730
    charge(ctx, 2);
    s1 = 0;
    if (i64(v0) > 0) {
        // 0x00533738
        charge(ctx, 2);
        s2 = 1;
        lw(v0, s0, snd::kCprmAix);
        for (;;) {
            // 0x00533740
            charge(ctx, 2);
            if (v0 != s2) {
                a0 = s0;
                // 0x00533768
                charge(ctx, 3);
                a1 = s1;
                jal(ctx, 0x533768u, gen::fn_sub_533880_00533880);
                a0 = v0;
            } else {
                // 0x00533748
                charge(ctx, 8);
                a1 = s1;
                a0 = s0;
                jal(ctx, 0x53374Cu, gen::fn_sub_533A18_00533a18);
                a1 = 0;
                a0 = v0;
                jal(ctx, 0x533758u, gen::fn_sub_553230_00553230);
                a0 = v0;
            }
            // 0x00533774
            charge(ctx, 6);
            s1 = addiu(s1, 1);
            jal(ctx, 0x533774u, gen::fn_sub_54F708_0054f708);
            lw(v0, s0, snd::kNumPlayer);
            v0 = slt(s1, v0);
            if (v0 == 0) {
                break;
            }
            lw(v0, s0, snd::kCprmAix);
            backedge(ctx);
        }
    }
    // 0x0053378c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005337A8 sub_5337A8 -- 96 bytes; frame 0x10: ra sp+0x0
// The current player's ADXT handle (0 for AIX; named by its error text). [ACSSND_GetActiveAdxt]
void sub_5337A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005337a8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a0;
    sd(ra, sp, 0x0);
    lw(v0, a1, 80);
    if (v0 != 0) {
        lw(a0, a1, 148);
        // 0x005337d8
        charge(ctx, 3);
        v1 = 1;
        v0 = 0;
        if (a0 != v1) {
            // 0x005337e4
            charge(ctx, 6);
            lw(v0, a1, 8);
            lw(v1, v0, 0);
            a0 = v0;
            lw(v0, v1, 60);
            jalr(ctx, 0x5337F4u, v0.u());
        }
    } else {
        // 0x005337c0
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 3200);  // "E2003052905 ACSSND_GetActiveAdxt : Not initialized."
        jal(ctx, 0x5337C4u, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x005337fc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00533808 sub_533808 -- 120 bytes; frame 0x10: ra sp+0x0
// The next player's ADXT handle (0 for AIX; named by its error text). [ACSSND_GetNextAdxt]
void sub_533808(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00533808
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a0;
    sd(ra, sp, 0x0);
    lw(v0, a1, 80);
    if (v0 != 0) {
        lw(a0, a1, 148);
        // 0x00533838
        charge(ctx, 3);
        v1 = 1;
        v0 = 0;
        if (a0 != v1) {
            // 0x00533844
            charge(ctx, 12);
            lw(v0, a1, 16);
            lw(v1, a1, 160);
            v0 = addiu(v0, 1);
            v1 = slt(v0, v1);
            if (v1 == 0) v0 = 0;
            v0 = sll(v0, 2);
            v0 = addu(a1, v0);
            lw(a0, v0, 0);
            lw(v1, a0, 0);
            lw(v0, v1, 60);
            jalr(ctx, 0x53386Cu, v0.u());
        }
    } else {
        // 0x00533820
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 3256);  // "E2003061000 ACSSND_GetNextAdxt : Not initialized."
        jal(ctx, 0x533824u, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x00533874 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00533880 sub_533880 -- 124 bytes; frame 0x10: ra sp+0x0
// Player n's ADXT handle (0 for AIX or n out of range; named by its error text). [ACSSND_GetAdxt]
void sub_533880(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00533880
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = a0;
    sd(ra, sp, 0x0);
    lw(v0, a2, 80);
    if (v0 == 0) {
        // 0x00533898
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 3312);  // "E2003052906 ACSSND_GetAdxt : Not initialized."
        jal(ctx, 0x53389Cu, gen::fn_sub_531A10_00531a10);
        v0 = 0;
        goto L_005338f0;
    }
    lw(a0, a2, 148);
    // 0x005338b0
    charge(ctx, 3);
    v1 = 1;
    v0 = 0;
    if (a0 == v1) {
    L_005338f0:
        charge(ctx, 1);
        ld(ra, sp, 0x0);
    } else {
        // 0x005338bc
        charge(ctx, 2);
        ld(ra, sp, 0x0);
        if (i64(a1) >= 0) {
            // 0x005338c4
            charge(ctx, 4);
            lw(v0, a2, 160);
            v0 = slt(a1, v0);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (!cc) {
                // 0x005338d4
                charge(ctx, 7);
                v0 = sll(a1, 2);
                v0 = addu(a2, v0);
                lw(a0, v0, 0);
                lw(v1, a0, 0);
                lw(v0, v1, 60);
                jalr(ctx, 0x5338E8u, v0.u());
                goto L_005338f0;
            }
        }
    }
    // 0x005338f4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00533900 sub_533900 -- 76 bytes; frame 0x10: ra sp+0x0
// The number of ADXT players (0 for AIX; named by its error text). [ACSSND_GetNumAdxt]
void sub_533900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00533900
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a0;
    sd(ra, sp, 0x0);
    lw(v0, a1, 80);
    if (v0 != 0) {
        lw(a0, a1, 148);
        // 0x00533930
        charge(ctx, 3);
        v1 = 1;
        v0 = 0;
        if (a0 != v1) {
            // 0x0053393c
            charge(ctx, 1);
            lw(v0, a1, 160);
        }
    } else {
        // 0x00533918
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 3360);  // "E2003052907 ACSSND_GetNumAdxt : Not initialized."
        jal(ctx, 0x53391Cu, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x00533940 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00533950 sub_533950 -- 84 bytes; frame 0x10: ra sp+0x0
// The current player's AIXP handle (0 for ADX; named by its error text). [ACSSND_GetActiveAixp]
void sub_533950(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00533950
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 80);
    if (v0 != 0) {
        lw(v1, a0, 148);
        // 0x00533978
        charge(ctx, 2);
        v0 = 0;
        if (v1 != 0) {
            // 0x00533980
            charge(ctx, 6);
            lw(v0, a0, 8);
            lw(v1, v0, 0);
            a0 = v0;
            lw(v0, v1, 60);
            jalr(ctx, 0x533990u, v0.u());
        }
    } else {
        // 0x00533964
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 3416);  // "E2003052908 ACSSND_GetActiveAixp : Not initialized."
        jal(ctx, 0x533968u, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x00533998 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005339A8 sub_5339A8 -- 108 bytes; frame 0x10: ra sp+0x0
// The next player's AIXP handle (0 for ADX; named by its error text). [ACSSND_GetNextAixp]
void sub_5339A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005339a8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 80);
    if (v0 != 0) {
        lw(v1, a0, 148);
        // 0x005339d0
        charge(ctx, 2);
        v0 = 0;
        if (v1 != 0) {
            // 0x005339d8
            charge(ctx, 12);
            lw(v0, a0, 16);
            lw(v1, a0, 160);
            v0 = addiu(v0, 1);
            v1 = slt(v0, v1);
            if (v1 == 0) v0 = 0;
            v0 = sll(v0, 2);
            v0 = addu(a0, v0);
            lw(a0, v0, 0);
            lw(v1, a0, 0);
            lw(v0, v1, 60);
            jalr(ctx, 0x533A00u, v0.u());
        }
    } else {
        // 0x005339bc
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 3472);  // "E2003061001 ACSSND_GetNextAixp : Not initialized."
        jal(ctx, 0x5339C0u, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x00533a08 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00533A18 sub_533A18 -- 112 bytes; frame 0x10: ra sp+0x0
// Player n's AIXP handle (0 for ADX or n out of range; named by its error text). [ACSSND_GetAixp]
void sub_533A18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00533a18
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 80);
    if (v0 == 0) {
        // 0x00533a2c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 3528);  // "E2003052909 ACSSND_GetAixp : Not initialized."
        jal(ctx, 0x533A30u, gen::fn_sub_531A10_00531a10);
        v0 = 0;
        goto L_00533a7c;
    }
    lw(v1, a0, 148);
    // 0x00533a40
    charge(ctx, 2);
    v0 = 0;
    if (v1 == 0) {
    L_00533a7c:
        charge(ctx, 1);
        ld(ra, sp, 0x0);
    } else {
        // 0x00533a48
        charge(ctx, 2);
        ld(ra, sp, 0x0);
        if (i64(a1) >= 0) {
            // 0x00533a50
            charge(ctx, 4);
            lw(v0, a0, 160);
            v0 = slt(a1, v0);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (!cc) {
                // 0x00533a60
                charge(ctx, 7);
                v0 = sll(a1, 2);
                v0 = addu(a0, v0);
                lw(a0, v0, 0);
                lw(v1, a0, 0);
                lw(v0, v1, 60);
                jalr(ctx, 0x533A74u, v0.u());
                goto L_00533a7c;
            }
        }
    }
    // 0x00533a80 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00533A88 sub_533A88 -- 64 bytes; frame 0x10: ra sp+0x0
// The number of AIXP players (0 for ADX; named by its error text). [ACSSND_GetNumAixp]
void sub_533A88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00533a88
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 80);
    if (v0 != 0) {
        lw(v1, a0, 148);
        // 0x00533ab0
        charge(ctx, 2);
        v0 = 0;
        if (v1 != 0) {
            // 0x00533ab8
            charge(ctx, 1);
            lw(v0, a0, 160);
        }
    } else {
        // 0x00533a9c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 3576);  // "E2003052910 ACSSND_GetNumAixp : Not initialized."
        jal(ctx, 0x533AA0u, gen::fn_sub_531A10_00531a10);
        v0 = 0;
    }
    // 0x00533abc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00533AC8 sub_533AC8 -- 472 bytes; frame 0x40: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// Cancel the running fade (named by its error text): fade-in <-> fade-out with the callbacks swapped and the fader
//   reversed; in cross-fade mode the other player is switched back (and reversed too while it still fades).
//   [ACSSND_CancelFading]
void sub_533AC8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00533ac8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x30);
    lw(v0, s1, snd::kInit);
    ld(s0, sp, 0x0);
    if (v0 == 0) {
        // 0x00533af8
        charge(ctx, 10);
        a0 = 0x7C0000;
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 3632);  // "E2003053007 ACSSND_CancelFading : Not initialized."
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    // 0x00533b20
    charge(ctx, 6);
    jal(ctx, 0x533B20u, gen::fn_sub_533CA0_00533ca0);
    s4 = v0;
    v0 = 1;
    ld(s0, sp, 0x0);
    if (s4 != v0) {
        // 0x00533c80
        charge(ctx, 8);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        return;
    }
    // 0x00533b38
    charge(ctx, 11);
    jal(ctx, 0x533B38u, gen::fn_coshl_005319c8);
    lw(v1, s1, snd::kCurIdx);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(s1, v0);
    s2 = addiu(v0, 24);
    lb(s3, s2, 4);
    lw(s5, s2, 8);
    if (s3 == s4) {
        // 0x00533b80
        charge(ctx, 16);
        v0 = 2;
        s0 = 0x530000;
        sb(v0, s2, 4);
        s0 = addiu(s0, 18888);  // &sub_5349C8
        a3 = 1;
        a0 = s5;
        a1 = s0;
        a2 = s1;
        jal(ctx, 0x533B9Cu, gen::fn_sub_531D48_00531d48);
        a0 = s5;
        a1 = s0;
        a2 = s1;
        a3 = 4;
        jal(ctx, 0x533BB0u, gen::fn_sub_531D58_00531d58);
        sb(zero, s2, 5);
    } else {
        // 0x00533b64
        charge(ctx, 3);
        v0 = slti(s3, 2);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 2;
        if (!cc) {
            // 0x00533b70
            charge(ctx, 2);
            s0 = 0x530000;
            if (s3 == v0) {
                // 0x00533bc0
                charge(ctx, 13);
                sb(s4, s2, 4);
                s0 = addiu(s0, 18888);
                a3 = 0;
                a0 = s5;
                a1 = s0;
                a2 = s1;
                jal(ctx, 0x533BD4u, gen::fn_sub_531D48_00531d48);
                a0 = s5;
                a1 = s0;
                a2 = s1;
                a3 = 3;
                jal(ctx, 0x533BE8u, gen::fn_sub_531D58_00531d58);
                sb(s3, s2, 5);
            } else {
                // 0x00533b78
                charge(ctx, 2);
            }
        }
    }
    // 0x00533bf4
    charge(ctx, 5);
    a0 = s5;
    jal(ctx, 0x533BF4u, gen::fn_sub_531BC0_00531bc0);
    lw(v0, s1, snd::kCross);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 1;
    if (!cc) {
        // 0x00533c08
        charge(ctx, 3);
        lb(v1, s2, 4);
        ld(s0, sp, 0x0);
        if (v1 == v0) {
            // 0x00533c14
            charge(ctx, 10);
            a0 = s1;
            jal(ctx, 0x533C14u, gen::fn_sub_534728_00534728);
            lw(v0, s1, snd::kCurIdx);
            v1 = sll(v0, 1);
            v1 = addu(v1, v0);
            v1 = sll(v1, 2);
            v1 = addu(s1, v1);
            lb(v0, v1, 28);
            if (v0 == 0) {
                // 0x00533c50
                charge(ctx, 2);
                a0 = s1;
                jal(ctx, 0x533C50u, gen::fn_sub_534678_00534678);
                goto L_00533c58;
            }
            // 0x00533c3c
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x533C3Cu, gen::fn_sub_533AC8_00533ac8);
            ld(s0, sp, 0x0);
        }
        goto L_00533c5c;
    }
L_00533c58:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
L_00533c5c:
    charge(ctx, 8);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
    gen::fn_expl_005319e0(ctx);  // tail call
}

// 0x00533CA0 sub_533CA0 -- 8 bytes; leaf frame (no stack)
// The busy flag (+164, s8: set while a start / stop / fade is under way). [ACSSND_IsBusy]
void sub_533CA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00533ca0
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, snd::kBusy);
}

// 0x00533CA8 sub_533CA8 -- 24 bytes; leaf frame (no stack)
// Add a ducking offset to the sound (+196) and mark it ducked (+200). [acssnd_AddDuck]
void sub_533CA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00533ca8
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, snd::kDuck);
    v1 = 1;
    sw(v1, a0, snd::kDucked);
    v0 = addu(v0, a1);
    sw(v0, a0, snd::kDuck);
}

// 0x00533CC0 sub_533CC0 -- 12 bytes; leaf frame (no stack)
// Clear the ducking offset and mark. [acssnd_ClearDuck]
void sub_533CC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x00533cc0
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(zero, a0, snd::kDucked);
    sw(zero, a0, snd::kDuck);
}

// 0x00533CD0 sub_533CD0 -- 452 bytes; frame 0x30: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Per-frame sound update: ducked -> re-send every player's volume; else step every fading player's fader and re-send
//   its volume, then the fade bookkeeping; a paused sound whose stop completed is released. [ACSSND_ExecServer]
void sub_533CD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00533cd0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    lw(v0, s1, snd::kInit);
    a0 = 0x7C0000;
    if (v0 == 0) {
        // 0x00533cf8
        charge(ctx, 8);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 3688);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    // 0x00533d18
    charge(ctx, 5);
    s0 = 1;
    jal(ctx, 0x533D18u, gen::fn_coshl_005319c8);
    lw(v0, s1, snd::kPause);
    if (v0 == s0) {
        // 0x00533d2c
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_expl_005319e0(ctx);  // tail call
        return;
    }
    lb(v0, s1, snd::kBusy);
    // 0x00533d48
    charge(ctx, 2);
    if (v0 != s0) {
        lw(v0, s1, snd::kDucked);
        // 0x00533e38
        charge(ctx, 2);
        cc = v0 != s0;  // the condition, before the delay slot changes it
        ld(s0, sp, 0x0);
        if (!cc) {
            // 0x00533e40
            charge(ctx, 3);
            lw(v0, s1, snd::kNumPlayer);
            s3 = 0;
            if (i64(v0) > 0) {
                // 0x00533e4c
                charge(ctx, 3);
                s0 = addiu(s1, 24);
                a1 = s0;
                for (;;) {
                    // 0x00533e58
                    charge(ctx, 8);
                    s0 = addiu(s0, 12);
                    a0 = s1;
                    s3 = addiu(s3, 1);
                    jal(ctx, 0x533E60u, gen::fn_sub_534888_00534888);
                    lw(v0, s1, snd::kNumPlayer);
                    v0 = slt(s3, v0);
                    a1 = s0;
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00533e78
                charge(ctx, 1);
                ld(s0, sp, 0x0);
            }
        }
    L_00533e7c:
        charge(ctx, 6);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_expl_005319e0(ctx);  // tail call
        return;
    }
    // 0x00533d50
    charge(ctx, 3);
    lw(v0, s1, snd::kPlaying);
    if (v0 != s0) {
        lw(v1, s1, snd::kNumPlayer);
    } else {
        // 0x00533d5c
        charge(ctx, 9);
        lw(v1, s1, snd::kCurIdx);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, s1);
        link(ctx, 0x533D70u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 32);
        call(ctx, gen::fn_sub_531AB8_00531ab8);
        if (v0 == s0) {
            lw(v1, s1, snd::kNumPlayer);
            goto L_00533ddc;
        }
        // 0x00533d80
        charge(ctx, 8);
        lw(a0, s1, snd::kCur);
        lw(v1, a0, 0);
        lw(v0, v1, 36);
        jalr(ctx, 0x533D8Cu, v0.u());
        v1 = 2;
        if (v0 != v1) {
            ld(s0, sp, 0x0);
            // 0x00533dc0
            charge(ctx, 6);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            gen::fn_expl_005319e0(ctx);  // tail call
            return;
        }
        // 0x00533da0
        charge(ctx, 7);
        lw(a0, s1, snd::kCur);
        lw(v1, a0, 0);
        lw(v0, v1, 28);
        a1 = 0;
        jalr(ctx, 0x533DACu, v0.u());
        sw(zero, s1, snd::kPlaying);
        // 0x00533dd8
        charge(ctx, 1);
        lw(v1, s1, snd::kNumPlayer);
        goto L_00533ddc;
    }
L_00533ddc:
    charge(ctx, 2);
    s3 = 0;
    if (i64(v1) > 0) {
        // 0x00533de4
        charge(ctx, 3);
        s2 = addiu(s1, 24);
        s0 = addiu(s1, 32);
        for (;;) {
            // 0x00533df0
            charge(ctx, 3);
            lb(v0, s0, -4);
            if (v0 == 0) {
                s3 = addiu(s3, 1);
            } else {
                // 0x00533dfc
                charge(ctx, 7);
                link(ctx, 0x533DFCu);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 0);
                call(ctx, gen::fn_sub_531C00_00531c00);
                a0 = s1;
                a1 = s2;
                jal(ctx, 0x533E08u, gen::fn_sub_534888_00534888);
                lw(v1, s1, snd::kNumPlayer);
                s3 = addiu(s3, 1);
            }
            // 0x00533e18
            charge(ctx, 4);
            s2 = addiu(s2, 12);
            v0 = slt(s3, v1);
            s0 = addiu(s0, 12);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00533e28
    charge(ctx, 4);
    a0 = s1;
    jal(ctx, 0x533E28u, gen::fn_sub_5347C0_005347c0);
    ld(s0, sp, 0x0);
    goto L_00533e7c;
}

// 0x00533E98 sub_533E98 -- 116 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// Set every player's fader curve. [ACSSND_SetFadeCurve]
void sub_533E98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00533e98
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 0;
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    lw(v0, s1, snd::kNumPlayer);
    s3 = a1;
    if (i64(v0) > 0) {
        // 0x00533ec4
        charge(ctx, 3);
        s0 = addiu(s1, 32);
        lw(a0, s0, 0);
        for (;;) {
            // 0x00533ed0
            charge(ctx, 8);
            s0 = addiu(s0, 12);
            a1 = s3;
            s2 = addiu(s2, 1);
            jal(ctx, 0x533ED8u, gen::fn_sub_531D40_00531d40);
            lw(v0, s1, snd::kNumPlayer);
            v0 = slt(s2, v0);
            if (v0 == 0) {
                break;
            }
            lw(a0, s0, 0);
            backedge(ctx);
        }
    }
    // 0x00533ef0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00533F10 sub_533F10 -- 256 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Sound reset: every field cleared; fade-out 30 frames, hold 60. [acssnd_Reset]
void sub_533F10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00533f10
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = s0;
    sd(s2, sp, 0x10);
    s2 = addiu(s0, 24);
    sd(s3, sp, 0x18);
    s3 = 1;
    sd(ra, sp, 0x20);
    sw(zero, s0, snd::kCur);
    sw(zero, s0, snd::kPrev);
    sw(zero, s0, snd::kCurIdx);
    sw(zero, s0, snd::kPrevIdx);
    sw(zero, s1, 0);
    for (;;) {
        // 0x00533f50
        charge(ctx, 9);
        s1 = addiu(s1, 4);
        a0 = s2;
        s2 = addiu(s2, 12);
        s3 = addiu(s3, -1);
        a1 = 0;
        a2 = 12;
        jal(ctx, 0x533F64u, gen::fn_memset_00521408);
        if (i64(s3) < 0) {
            break;
        }
        sw(zero, s1, 0);
        backedge(ctx);
    }
    // 0x00533f74
    charge(ctx, 39);
    a0 = addiu(s0, 48);
    a1 = 0;
    a2 = 32;
    jal(ctx, 0x533F7Cu, gen::fn_memset_00521408);
    sw(zero, s0, snd::kInit);
    sw(zero, s0, snd::kIniting);
    a0 = addiu(s0, 120);
    sw(zero, s0, snd::kField88);
    a1 = 0;
    sw(zero, s0, snd::kCross);
    a2 = 40;
    sw(zero, s0, snd::kPause);
    sw(zero, s0, snd::kPlaying);
    sw(zero, s0, snd::kField104);
    sw(zero, s0, snd::kAhxWork);
    sw(zero, s0, snd::kNameBuf);
    link(ctx, 0x533FB4u);  // $ra first: the delay slot below depends on it
    sw(zero, s0, snd::kField116);
    call(ctx, gen::fn_memset_00521408);
    sw(zero, s0, snd::kNumPlayer);
    v0 = 30;
    v1 = 60;
    sw(v0, s0, snd::kFadeOutTime);
    sw(v1, s0, snd::kHoldTime);
    sw(zero, s0, snd::kCbFunc);
    sb(zero, s0, snd::kBusy);
    sw(zero, s0, snd::kFadeInTime);
    sw(zero, s0, snd::kVolChgTime);
    sw(zero, s0, snd::kCrossOffset);
    sw(zero, s0, snd::kOutVol);
    sw(zero, s0, snd::kTrackVol);
    sw(zero, s0, snd::kDuck);
    sw(zero, s0, snd::kDucked);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00534010 sub_534010 -- 756 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s4 sp+0x20, s2 sp+0x10, s3 sp+0x18, ra sp+0x28
// The common start (named by its error text): busy; in cross-fade mode switch to the other player, fade the old one
//   out and the new one in (the cross offset +180 delaying one of them); else stop a playing player and fade in; then
//   send the volume and the stored start request (sub_534308). [ACSSND_Start]
void sub_534010(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00534010
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = 0;
    sd(s4, sp, 0x20);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x28);
    lw(v0, s0, snd::kInit);
    s4 = a1;
    if (v0 == 0) {
        // 0x00534040
        charge(ctx, 10);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 3744);  // "E2003060600 ACSSND_Start : Not initialized."
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        gen::fn_sub_531A10_00531a10(ctx);  // tail call
        return;
    }
    // 0x00534068
    charge(ctx, 8);
    jal(ctx, 0x534068u, gen::fn_coshl_005319c8);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x534074u, gen::fn_sub_534530_00534530);
    lw(a2, s0, snd::kCrossOffset);
    if (i64(a2) >= 0) {
        s2 = a2;
        // 0x00534098
        charge(ctx, 1);
        s3 = 0;
    } else {
        // 0x00534088
        charge(ctx, 3);
        s3 = subu(0, a2);
        s2 = 0;
    }
    // 0x0053409c
    charge(ctx, 3);
    lw(v0, s0, snd::kCross);
    a0 = s0;
    if (v0 == 0) {
        // 0x00534200
        charge(ctx, 8);
        lw(a0, s0, snd::kCur);
        lw(v1, a0, 0);
        lw(v0, v1, 36);
        jalr(ctx, 0x53420Cu, v0.u());
        v1 = 2;
        if (v0 != v1) {
            lw(a0, s0, snd::kCur);
        } else {
            // 0x00534220
            charge(ctx, 4);
            lw(v1, s0, snd::kPause);
            v0 = 1;
            if (v1 == v0) {
                // 0x00534230
                charge(ctx, 1);
                lw(a0, s0, snd::kCur);
                goto L_00534234;
            }
            lw(v0, s0, snd::kCurIdx);
            // 0x00534280
            charge(ctx, 9);
            a0 = s0;
            a2 = 0;
            a3 = 1;
            a1 = sll(v0, 1);
            a1 = addu(a1, v0);
            a1 = sll(a1, 2);
            a1 = addu(s0, a1);
            a1 = addiu(a1, 24);
            jal(ctx, 0x53429Cu, gen::fn_sub_534488_00534488);
            goto L_005342a4;
        }
    L_00534234:
        charge(ctx, 19);
        a1 = 1;
        lw(v1, a0, 0);
        lw(v0, v1, 28);
        s1 = 1;
        jalr(ctx, 0x534240u, v0.u());
        v1 = 1;
        lw(v0, s0, snd::kCurIdx);
        a0 = s0;
        sw(v1, s0, snd::kPlaying);
        a2 = 0;
        a1 = sll(v0, 1);
        a3 = 0;
        a1 = addu(a1, v0);
        a1 = sll(a1, 2);
        a1 = addu(s0, a1);
        a1 = addiu(a1, 24);
        jal(ctx, 0x534270u, gen::fn_sub_5343D8_005343d8);
    } else {
        // 0x005340a8
        charge(ctx, 21);
        s1 = addiu(s0, 8);
        jal(ctx, 0x5340A8u, gen::fn_sub_534678_00534678);
        lw(a0, s0, snd::kCur);
        lw(v1, a0, 0);
        lw(v0, v1, 28);
        a1 = 1;
        jalr(ctx, 0x5340BCu, v0.u());
        v1 = 1;
        lw(a0, s0, snd::kPrevIdx);
        sw(v1, s0, snd::kPlaying);
        v0 = sll(a0, 1);
        v0 = addu(v0, a0);
        v0 = sll(v0, 2);
        v0 = addu(v0, s1);
        lw(a0, v0, 16);
        lw(v1, a0, 0);
        lw(v0, v1, 36);
        jalr(ctx, 0x5340ECu, v0.u());
        cc = v0 != 0;  // the condition, before the delay slot changes it
        lw(v0, s0, snd::kCurIdx);
        if (cc) {
            // 0x00534128
            charge(ctx, 10);
            a2 = s2;
            a0 = s0;
            a3 = 0;
            a1 = sll(v0, 1);
            a1 = addu(a1, v0);
            a1 = sll(a1, 2);
            a1 = addu(s0, a1);
            a1 = addiu(a1, 24);
            jal(ctx, 0x534144u, gen::fn_sub_5343D8_005343d8);
            lw(v1, s0, snd::kPrevIdx);
        } else {
            // 0x005340fc
            charge(ctx, 11);
            a0 = s0;
            a2 = 0;
            a3 = 0;
            a1 = sll(v0, 1);
            a1 = addu(a1, v0);
            a1 = sll(a1, 2);
            a1 = addu(s0, a1);
            a1 = addiu(a1, 24);
            jal(ctx, 0x534118u, gen::fn_sub_5343D8_005343d8);
            lw(v1, s0, snd::kPrevIdx);
        }
        // 0x00534150
        charge(ctx, 11);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, s1);
        lw(a0, v0, 16);
        lw(v1, a0, 0);
        lw(v0, v1, 36);
        jalr(ctx, 0x53416Cu, v0.u());
        a2 = s3;
        if (v0 != 0) {
            // 0x0053417c
            charge(ctx, 13);
            lw(v0, s0, snd::kPrevIdx);
            a0 = s0;
            a3 = 2;
            a1 = sll(v0, 1);
            a1 = addu(a1, v0);
            a1 = sll(a1, 2);
            a1 = addu(s0, a1);
            a1 = addiu(a1, 24);
            jal(ctx, 0x534198u, gen::fn_sub_534488_00534488);
            lw(v1, s0, snd::kPause);
            v0 = 1;
            if (v1 == v0) {
                // 0x005341b0
                charge(ctx, 18);
                lw(v1, s0, snd::kPrevIdx);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                v0 = addu(v0, s1);
                lw(a0, v0, 16);
                lw(v1, a0, 0);
                lw(v0, v1, 24);
                jalr(ctx, 0x5341D0u, v0.u());
                lw(v1, s0, snd::kPrevIdx);
                a1 = si(-960);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                v0 = addu(v0, s0);
                link(ctx, 0x5341F0u);  // $ra first: the delay slot below depends on it
                lw(a0, v0, 32);
                call(ctx, gen::fn_sub_531AD0_00531ad0);
                goto L_005341f8;
            }
            s1 = 1;
            goto L_005342a4;
        }
    L_005341f8:
        charge(ctx, 2);
        s1 = 1;
    }
L_005342a4:
    charge(ctx, 5);
    jal(ctx, 0x5342A4u, gen::fn_expl_005319e0);
    v0 = 1;
    if (s1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005342b8
        charge(ctx, 12);
        lw(v0, s0, snd::kCurIdx);
        a0 = s0;
        a1 = sll(v0, 1);
        a1 = addu(a1, v0);
        a1 = sll(a1, 2);
        a1 = addu(s0, a1);
        a1 = addiu(a1, 24);
        jal(ctx, 0x5342D0u, gen::fn_sub_534888_00534888);
        a0 = s0;
        a1 = s4;
        jal(ctx, 0x5342DCu, gen::fn_sub_534308_00534308);
        ld(s0, sp, 0x0);
    }
    // 0x005342e8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00534308 sub_534308 -- 208 bytes; frame 0x10: ra sp+0x0
// Send the stored start request to the current player (methods 2..5 by the request type; 3 for another type).
//   [acssnd_StartPlayer]
void sub_534308(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00534308
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    lw(v1, a1, 0);
    if (v1 == v0) {
        lw(v0, a0, 8);
        // 0x00534368
        charge(ctx, 8);
        lw(a2, a1, 12);
        lw(v1, v0, 0);
        a0 = v0;
        lw(a3, v1, 12);
        jt = a3.u();  // the target, read before the delay slot
        link(ctx, 0x534378u);  // $ra = the return address
        lw(a1, a1, 8);
        call_ptr(ctx, jt);
        ld(ra, sp, 0x0);
    } else {
        // 0x00534320
        charge(ctx, 2);
        if (v1 == 0) {
            lw(v0, a0, 8);
            // 0x00534348
            charge(ctx, 7);
            lw(a1, a1, 4);
            lw(v1, v0, 0);
            lw(a2, v1, 8);
            a0 = v0;
            jalr(ctx, 0x534354u, a2.u());
            ld(ra, sp, 0x0);
        } else {
            // 0x00534328
            charge(ctx, 3);
            v0 = 2;
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = 3;
            if (cc) {
                // 0x00534388
                charge(ctx, 9);
                lw(v0, a0, 8);
                lw(a2, a1, 20);
                lw(v1, v0, 0);
                a0 = v0;
                lw(a3, v1, 16);
                jt = a3.u();  // the target, read before the delay slot
                link(ctx, 0x53439Cu);  // $ra = the return address
                lw(a1, a1, 16);
                call_ptr(ctx, jt);
                ld(ra, sp, 0x0);
            } else {
                // 0x00534334
                charge(ctx, 2);
                ld(ra, sp, 0x0);
                if (v1 == v0) {
                    // 0x005343b0
                    charge(ctx, 8);
                    lw(v0, a0, 8);
                    lw(a2, a1, 28);
                    lw(v1, v0, 0);
                    a0 = v0;
                    lw(a3, v1, 20);
                    jt = a3.u();  // the target, read before the delay slot
                    link(ctx, 0x5343C4u);  // $ra = the return address
                    lw(a1, a1, 24);
                    call_ptr(ctx, jt);
                    ld(ra, sp, 0x0);
                } else {
                    // 0x0053433c
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x005343d0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x005343D8 sub_5343D8 -- 176 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, ra sp+0x28, s2 sp+0x10
// Begin a fade-in on a player record: from silence to the sound's volume over the fade-in frames (+172) after the
//   given delay, the fader callbacks set, player state 2 with the given next action. [acssnd_FadeIn]
void sub_5343D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005343d8
    enter(ctx, 44);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    s4 = a3;
    sd(ra, sp, 0x28);
    a1 = si(-960);
    sd(s2, sp, 0x10);
    lw(s2, s3, ply::kFader);
    a0 = s2;
    jal(ctx, 0x53440Cu, gen::fn_sub_531AD0_00531ad0);
    a0 = s2;
    lw(t0, s1, snd::kHoldTime);
    a3 = s0;
    lw(a1, s1, snd::kOutVol);
    s0 = 0x530000;
    lw(a2, s1, snd::kFadeInTime);
    s0 = addiu(s0, 18888);  // &sub_5349C8
    jal(ctx, 0x53442Cu, gen::fn_sub_531B00_00531b00);
    a3 = 1;
    a0 = s2;
    a1 = s0;
    a2 = s1;
    jal(ctx, 0x534440u, gen::fn_sub_531D48_00531d48);
    a0 = s2;
    a1 = s0;
    a2 = s1;
    a3 = 4;
    jal(ctx, 0x534454u, gen::fn_sub_531D58_00531d58);
    v0 = 2;
    sb(s4, s3, ply::kAction);
    sb(v0, s3, ply::kFade);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00534488 sub_534488 -- 164 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, ra sp+0x28, s2 sp+0x10
// Begin a fade-out on a player record: to silence over the fade-out frames (+168) after the given delay, player state
//   1 with the given next action. [acssnd_FadeOut]
void sub_534488(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00534488
    enter(ctx, 41);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = a2;
    sd(s0, sp, 0x0);
    s0 = 0x530000;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    s4 = a3;
    sd(ra, sp, 0x28);
    s0 = addiu(s0, 18888);  // &sub_5349C8
    sd(s2, sp, 0x10);
    a3 = v0;
    a1 = si(-960);
    lw(s2, s3, ply::kFader);
    lw(t0, s1, snd::kHoldTime);
    lw(a2, s1, snd::kFadeOutTime);
    a0 = s2;
    jal(ctx, 0x5344D0u, gen::fn_sub_531B00_00531b00);
    a3 = 0;
    a0 = s2;
    a1 = s0;
    a2 = s1;
    jal(ctx, 0x5344E4u, gen::fn_sub_531D48_00531d48);
    a0 = s2;
    a1 = s0;
    a2 = s1;
    a3 = 3;
    jal(ctx, 0x5344F8u, gen::fn_sub_531D58_00531d58);
    v0 = 1;
    sb(s4, s3, ply::kAction);
    sb(v0, s3, ply::kFade);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00534530 sub_534530 -- 8 bytes; leaf frame (no stack)
// Set the busy flag (+164). [acssnd_SetBusy]
void sub_534530(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00534530
    enter(ctx, 2);  // entry check point + this block's cycles
    sb(a1, a0, snd::kBusy);
}

// 0x00534538 sub_534538 -- 316 bytes; frame 0x30: s1 sp+0x8, s3 sp+0x18, s0 sp+0x0, s2 sp+0x10, ra sp+0x20
// A player's fade ended: run its next action (1 start the pending request with a fade-in, 2 stop, 3 pause).
//   [acssnd_FadeEnd]
void sub_534538(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00534538
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    lb(s2, s3, ply::kAction);
    v1 = slti(s2, 2);
    if (s2 == v0) {
        // 0x00534590
        charge(ctx, 35);
        jal(ctx, 0x534590u, gen::fn_coshl_005319c8);
        a1 = 1;
        lw(v1, s1, snd::kCrossOffset);
        a0 = s1;
        lw(v0, s1, snd::kFadeOutTime);
        s0 = subu(v1, v0);
        v0 = slt(v0, v1);
        if (v0 == 0) s0 = 0;
        jal(ctx, 0x5345B0u, gen::fn_sub_534530_00534530);
        lw(a0, s3, ply::kBackend);
        lw(v1, a0, 0);
        lw(v0, v1, 28);
        a1 = 1;
        jalr(ctx, 0x5345C4u, v0.u());
        sw(s2, s1, snd::kPlaying);
        a2 = s0;
        a3 = 0;
        a0 = s1;
        a1 = s3;
        jal(ctx, 0x5345DCu, gen::fn_sub_5343D8_005343d8);
        jal(ctx, 0x5345E4u, gen::fn_expl_005319e0);
        a0 = s1;
        a1 = s3;
        jal(ctx, 0x5345F0u, gen::fn_sub_534888_00534888);
        a0 = s1;
        ld(s0, sp, 0x0);
        a1 = addiu(a0, 48);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_534308_00534308(ctx);  // tail call
        return;
    }
    // 0x00534568
    charge(ctx, 2);
    if (v1 != 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00534570
        charge(ctx, 3);
        v0 = 2;
        cc = s2 == v0;  // the condition, before the delay slot changes it
        v0 = 3;
        if (cc) {
            // 0x00534620
            charge(ctx, 7);
            lw(v0, s3, ply::kBackend);
            lw(v1, v0, 0);
            lw(a1, v1, 24);
            a0 = v0;
            jalr(ctx, 0x53462Cu, a1.u());
            ld(s0, sp, 0x0);
            goto L_0053465c;
        }
        // 0x0053457c
        charge(ctx, 2);
        ld(s0, sp, 0x0);
        if (s2 == v0) {
            // 0x00534640
            charge(ctx, 7);
            lw(v0, s3, ply::kBackend);
            a1 = 1;
            lw(v1, v0, 0);
            lw(a2, v1, 28);
            a0 = v0;
            jalr(ctx, 0x534650u, a2.u());
            ld(s0, sp, 0x0);
            goto L_0053465c;
        }
        // 0x00534584
        charge(ctx, 2);
        ld(s1, sp, 0x8);
        // 0x00534660 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_0053465c:
    charge(ctx, 1);
    ld(s1, sp, 0x8);
    // 0x00534660 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00534678 sub_534678 -- 176 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Switch to the other player (cross-fade): pause off a still-playing current one, current <- next.
//   [acssnd_NextPlayer]
void sub_534678(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00534678
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x534684u, gen::fn_coshl_005319c8);
    lw(v0, s0, snd::kPause);
    v1 = 1;
    if (v0 == 0) {
        // 0x00534698
        charge(ctx, 3);
        lw(v0, s0, snd::kPlaying);
        if (v0 == v1) {
            // 0x005346a4
            charge(ctx, 6);
            lw(v0, s0, snd::kCur);
            a1 = 0;
            lw(v1, v0, 0);
            lw(a2, v1, 28);
            a0 = v0;
            jalr(ctx, 0x5346B4u, a2.u());
            goto L_005346bc;
        }
        lw(v0, s0, snd::kCurIdx);
        goto L_005346c0;
    }
L_005346bc:
    charge(ctx, 1);
    lw(v0, s0, snd::kCurIdx);
L_005346c0:
    charge(ctx, 6);
    lw(v1, s0, snd::kNumPlayer);
    a0 = addiu(v0, 1);
    sw(v0, s0, snd::kPrevIdx);
    v1 = slt(a0, v1);
    sw(a0, s0, snd::kCurIdx);
    if (v1 == 0) {
        // 0x005346d8
        charge(ctx, 1);
        sw(zero, s0, snd::kCurIdx);
    }
    // 0x005346dc
    charge(ctx, 19);
    lw(a2, s0, snd::kPrevIdx);
    a1 = addiu(s0, 8);
    lw(a0, s0, snd::kCurIdx);
    v0 = sll(a2, 1);
    ld(ra, sp, 0x8);
    v0 = addu(v0, a2);
    v1 = sll(a0, 1);
    v0 = sll(v0, 2);
    v1 = addu(v1, a0);
    v0 = addu(v0, a1);
    v1 = sll(v1, 2);
    lw(a0, v0, 16);
    v1 = addu(v1, a1);
    sw(a0, s0, snd::kPrev);
    ld(s0, sp, 0x0);
    lw(v0, v1, 16);
    sw(v0, a1, 0);
    sp = addiu(sp, 0x10);
    gen::fn_expl_005319e0(ctx);  // tail call
}

// 0x00534728 sub_534728 -- 148 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Switch back to the previous player. [acssnd_PrevPlayer]
void sub_534728(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00534728
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x534734u, gen::fn_coshl_005319c8);
    lw(v0, s0, snd::kCurIdx);
    a1 = addiu(s0, 8);
    v0 = addiu(v0, -1);
    sw(v0, s0, snd::kCurIdx);
    if (i64(v0) < 0) {
        // 0x00534750
        charge(ctx, 3);
        lw(v0, s0, snd::kNumPlayer);
        v0 = addiu(v0, -1);
        sw(v0, s0, snd::kCurIdx);
    }
    // 0x0053475c
    charge(ctx, 8);
    lw(v0, s0, snd::kCurIdx);
    v1 = sll(v0, 1);
    a0 = addiu(v0, -1);
    v1 = addu(v1, v0);
    sw(a0, s0, snd::kPrevIdx);
    v1 = sll(v1, 2);
    a2 = addu(v1, a1);
    if (i64(a0) < 0) {
        // 0x0053477c
        charge(ctx, 3);
        lw(v0, s0, snd::kNumPlayer);
        v0 = addiu(v0, -1);
        sw(v0, s0, snd::kPrevIdx);
    }
    // 0x00534788
    charge(ctx, 13);
    lw(v1, s0, snd::kPrevIdx);
    ld(ra, sp, 0x8);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, a1);
    lw(v1, v0, 16);
    sw(v1, s0, snd::kPrev);
    ld(s0, sp, 0x0);
    lw(v0, a2, 16);
    sw(v0, a1, 0);
    sp = addiu(sp, 0x10);
    gen::fn_expl_005319e0(ctx);  // tail call
}

// 0x005347C0 sub_5347C0 -- 196 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// Fade bookkeeping: run the next action of every player whose fader went idle; when all are idle, call the sound's
//   callback (event 6) and clear busy. [acssnd_CheckFade]
void sub_5347C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005347c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    lw(v0, s1, snd::kNumPlayer);
    s2 = 0;
    if (i64(v0) > 0) {
        // 0x005347e4
        charge(ctx, 1);
        s0 = addiu(s1, 24);
        for (;;) {
            // 0x005347e8
            charge(ctx, 4);
            link(ctx, 0x5347E8u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 8);
            call(ctx, gen::fn_sub_531AB8_00531ab8);
            if (v0 != 0) {
                lw(v0, s1, snd::kNumPlayer);
            } else {
                // 0x005347f8
                charge(ctx, 3);
                lb(v0, s0, 4);
                a1 = s0;
                if (v0 != 0) {
                    // 0x00534804
                    charge(ctx, 3);
                    sb(zero, s0, 4);
                    a0 = s1;
                    jal(ctx, 0x534808u, gen::fn_sub_534538_00534538);
                }
                // 0x00534810
                charge(ctx, 1);
                lw(v0, s1, snd::kNumPlayer);
            }
            // 0x00534814
            charge(ctx, 4);
            s2 = addiu(s2, 1);
            v0 = slt(s2, v0);
            s0 = addiu(s0, 12);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00534824
    charge(ctx, 5);
    a0 = s1;
    jal(ctx, 0x534824u, gen::fn_sub_534960_00534960);
    v1 = 1;
    if (v0 != v1) {
        ld(s0, sp, 0x0);
        // 0x00534870
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00534838
    charge(ctx, 3);
    lw(v0, s1, snd::kCbFunc);
    a0 = s1;
    if (v0 != 0) {
        // 0x00534844
        charge(ctx, 2);
        a1 = 6;
        jalr(ctx, 0x534844u, v0.u());
    }
    // 0x0053484c
    charge(ctx, 8);
    a0 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    a1 = 0;
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_534530_00534530(ctx);  // tail call
}

// 0x00534888 sub_534888 -- 216 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, s3 sp+0x18, ra sp+0x20
// Send a player's volume: the fader volume plus the sound's volume and ducking (AIX: per track, with the track
//   volumes). [acssnd_SendVolume]
void sub_534888(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00534888
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    lw(v1, s0, snd::kCprmAix);
    lw(s3, s2, ply::kFader);
    if (v1 != v0) {
        // 0x00534920
        charge(ctx, 9);
        a0 = s3;
        jal(ctx, 0x534920u, gen::fn_sub_531AC8_00531ac8);
        lw(a1, s0, snd::kDuck);
        lw(a0, s2, ply::kBackend);
        a1 = addu(v0, a1);
        lw(v1, a0, 0);
        lw(v0, v1, 40);
        jalr(ctx, 0x53493Cu, v0.u());
    L_00534944:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    } else {
        // 0x005348b8
        charge(ctx, 3);
        lw(v0, s0, snd::kCprmNumTrack);
        s1 = 0;
        if (i64(v0) <= 0) {
            goto L_00534944;
        }
        // 0x005348c4
        charge(ctx, 1);
        for (;;) {
            // 0x005348c8
            charge(ctx, 20);
            a0 = s3;
            jal(ctx, 0x5348C8u, gen::fn_sub_531AC8_00531ac8);
            lw(a0, s0, snd::kTrackVol);
            lw(a1, s2, ply::kBackend);
            v1 = sll(s1, 2);
            v1 = addu(v1, a0);
            lw(t0, s0, snd::kDuck);
            lw(a2, v1, 0);
            a0 = a1;
            lw(a3, a1, 0);
            a1 = s1;
            a2 = addu(a2, v0);
            s1 = addiu(s1, 1);
            lw(v1, a3, 48);
            a2 = addu(a2, t0);
            jalr(ctx, 0x534900u, v1.u());
            lw(v0, s0, snd::kCprmNumTrack);
            v0 = slt(s1, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00534918
        charge(ctx, 2);
        ld(s0, sp, 0x0);
    }
    // 0x00534948 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00534960 sub_534960 -- 104 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// 1 when every player's fader is idle. [acssnd_IsAllFadeEnd]
void sub_534960(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00534960
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s0, sp, 0x0);
    s0 = addiu(s2, 32);
    sd(s1, sp, 0x8);
    s1 = 0;
    sd(ra, sp, 0x18);
    for (;;) {
        // 0x00534980
        charge(ctx, 4);
        lw(v1, s2, snd::kNumPlayer);
        v0 = slt(s1, v1);
        if (v0 != 0) {
            // 0x00534990
            charge(ctx, 5);
            lw(a0, s0, 0);
            s0 = addiu(s0, 12);
            jal(ctx, 0x534994u, gen::fn_sub_531AB8_00531ab8);
            if (v0 != 0) {
                goto L_005349a4_3;
            }
            s1 = addiu(s1, 1);
            backedge(ctx);
            continue;
        }
        v0 = s1 ^ v1;
        break;
    }
    // 0x005349ac (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    v0 = sltiu(v0, 1);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    return;
L_005349a4_3:
    charge(ctx, 2);
    lw(v1, s2, snd::kNumPlayer);
    v0 = s1 ^ v1;
    // 0x005349ac (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    v0 = sltiu(v0, 1);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005349C8 sub_5349C8 -- 48 bytes; frame 0x10: ra sp+0x0
// The fader callback: call the sound's callback (+204) with the event number. [acssnd_FaderCb]
void sub_5349C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005349c8
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x005349d8
        charge(ctx, 3);
        lw(v0, v0, 204);
        if (v0 != 0) {
            // 0x005349e4
            charge(ctx, 2);
            jalr(ctx, 0x5349E4u, v0.u());
            goto L_005349ec;
        }
        ld(ra, sp, 0x0);
        // 0x005349f0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_005349ec:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x005349f0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
