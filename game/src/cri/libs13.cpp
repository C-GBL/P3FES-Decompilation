// Phase 5 slice libs13: CRI Sofdec's SFD core around the video decoder (0x590008-0x59C5E0) -- the picture-header and
// time-code steps, the frame pool and its frame records, the sceMpeg / IPU input path with its video-input ring,
// the handle's status machine and end checks, handle creation / destruction / recreation, the transfer graph, the
// clock and the profiler log.
// p3fes_handgen bodies (game/include/p3fes/game/hg_cpu.h); every statement, charge and check point is the
// generator's. The roles come from reading the instructions; the record offsets are in game/include/p3fes/game/libs13.h
// (libs13:: constants; each equals the literal it replaces). Names are symbols/ names (ADR-0009).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs13.h"
#include "p3fes/game/movies_native.h"

namespace p3fes::recomp_gen {
void fn___divdi3_0052eeb0(p3fes::EEContext&);
void fn__sceCreateSema_00503160(p3fes::EEContext&);
void fn__sceSignalSema_00503180(p3fes::EEContext&);
void fn__sceWaitSema_005031a0(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_my_malloc_1_00597448(p3fes::EEContext&);
void fn_sceInsockGetErrnoMode_1_00597438(p3fes::EEContext&);
void fn_sceInsockSetErrnoMode_1_00597428(p3fes::EEContext&);
void fn_sceMpegAddCallback_00500c90(p3fes::EEContext&);
void fn_sceMpegCreate_004ffe78(p3fes::EEContext&);
void fn_sceMpegDelete_00500ad0(p3fes::EEContext&);
void fn_sceMpegGetPictureRAW8_00500b60(p3fes::EEContext&);
void fn_sceMpegGetPicture_00500b18(p3fes::EEContext&);
void fn_sceMpegInit_00500a20(p3fes::EEContext&);
void fn_sceMpegReset_00500bb8(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_sub_562E10_00562e10(p3fes::EEContext&);
void fn_sub_56F4B8_0056f4b8(p3fes::EEContext&);
void fn_sub_575410_00575410(p3fes::EEContext&);
void fn_sub_575880_00575880(p3fes::EEContext&);
void fn_sub_577FC8_00577fc8(p3fes::EEContext&);
void fn_sub_578160_00578160(p3fes::EEContext&);
void fn_sub_578D98_00578d98(p3fes::EEContext&);
void fn_sub_579078_00579078(p3fes::EEContext&);
void fn_sub_579080_00579080(p3fes::EEContext&);
void fn_sub_579138_00579138(p3fes::EEContext&);
void fn_sub_579240_00579240(p3fes::EEContext&);
void fn_sub_5792A0_005792a0(p3fes::EEContext&);
void fn_sub_579410_00579410(p3fes::EEContext&);
void fn_sub_579428_00579428(p3fes::EEContext&);
void fn_sub_579450_00579450(p3fes::EEContext&);
void fn_sub_57B440_0057b440(p3fes::EEContext&);
void fn_sub_57B5B0_0057b5b0(p3fes::EEContext&);
void fn_sub_57B5C8_0057b5c8(p3fes::EEContext&);
void fn_sub_57B648_0057b648(p3fes::EEContext&);
void fn_sub_57BAF0_0057baf0(p3fes::EEContext&);
void fn_sub_57BC10_0057bc10(p3fes::EEContext&);
void fn_sub_588740_00588740(p3fes::EEContext&);
void fn_sub_588A10_00588a10(p3fes::EEContext&);
void fn_sub_588D38_00588d38(p3fes::EEContext&);
void fn_sub_589510_00589510(p3fes::EEContext&);
void fn_sub_589530_00589530(p3fes::EEContext&);
void fn_sub_589550_00589550(p3fes::EEContext&);
void fn_sub_5895F0_005895f0(p3fes::EEContext&);
void fn_sub_589D10_00589d10(p3fes::EEContext&);
void fn_sub_589D30_00589d30(p3fes::EEContext&);
void fn_sub_589D80_00589d80(p3fes::EEContext&);
void fn_sub_589F38_00589f38(p3fes::EEContext&);
void fn_sub_589FD0_00589fd0(p3fes::EEContext&);
void fn_sub_58A038_0058a038(p3fes::EEContext&);
void fn_sub_58B140_0058b140(p3fes::EEContext&);
void fn_sub_58B158_0058b158(p3fes::EEContext&);
void fn_sub_58BE28_0058be28(p3fes::EEContext&);
void fn_sub_58BE40_0058be40(p3fes::EEContext&);
void fn_sub_58BEF0_0058bef0(p3fes::EEContext&);
void fn_sub_58C060_0058c060(p3fes::EEContext&);
void fn_sub_58C100_0058c100(p3fes::EEContext&);
void fn_sub_58C118_0058c118(p3fes::EEContext&);
void fn_sub_58E5E8_0058e5e8(p3fes::EEContext&);
void fn_sub_58E670_0058e670(p3fes::EEContext&);
void fn_sub_58E800_0058e800_at_0058e888(p3fes::EEContext&);
void fn_sub_58FEC8_0058fec8(p3fes::EEContext&);
void fn_sub_58FF70_0058ff70(p3fes::EEContext&);
void fn_sub_590008_00590008(p3fes::EEContext&);
void fn_sub_590360_00590360(p3fes::EEContext&);
void fn_sub_590408_00590408(p3fes::EEContext&);
void fn_sub_590430_00590430(p3fes::EEContext&);
void fn_sub_5905F0_005905f0(p3fes::EEContext&);
void fn_sub_590878_00590878(p3fes::EEContext&);
void fn_sub_590948_00590948(p3fes::EEContext&);
void fn_sub_590A28_00590a28(p3fes::EEContext&);
void fn_sub_590AE8_00590ae8(p3fes::EEContext&);
void fn_sub_590DF8_00590df8(p3fes::EEContext&);
void fn_sub_590EF0_00590ef0(p3fes::EEContext&);
void fn_sub_590FD0_00590fd0(p3fes::EEContext&);
void fn_sub_591118_00591118(p3fes::EEContext&);
void fn_sub_591168_00591168(p3fes::EEContext&);
void fn_sub_591298_00591298(p3fes::EEContext&);
void fn_sub_5913B8_005913b8(p3fes::EEContext&);
void fn_sub_5913F0_005913f0(p3fes::EEContext&);
void fn_sub_5915A8_005915a8(p3fes::EEContext&);
void fn_sub_5916A0_005916a0(p3fes::EEContext&);
void fn_sub_591700_00591700(p3fes::EEContext&);
void fn_sub_591808_00591808(p3fes::EEContext&);
void fn_sub_591858_00591858(p3fes::EEContext&);
void fn_sub_5918A8_005918a8(p3fes::EEContext&);
void fn_sub_591988_00591988(p3fes::EEContext&);
void fn_sub_591C80_00591c80(p3fes::EEContext&);
void fn_sub_591F38_00591f38(p3fes::EEContext&);
void fn_sub_592240_00592240(p3fes::EEContext&);
void fn_sub_5922C8_005922c8(p3fes::EEContext&);
void fn_sub_5923E0_005923e0(p3fes::EEContext&);
void fn_sub_5923E0_005923e0_at_00592488(p3fes::EEContext&);
void fn_sub_592570_00592570(p3fes::EEContext&);
void fn_sub_592618_00592618(p3fes::EEContext&);
void fn_sub_592790_00592790(p3fes::EEContext&);
void fn_sub_592958_00592958(p3fes::EEContext&);
void fn_sub_5929B0_005929b0(p3fes::EEContext&);
void fn_sub_592B10_00592b10(p3fes::EEContext&);
void fn_sub_592D08_00592d08(p3fes::EEContext&);
void fn_sub_592DD0_00592dd0(p3fes::EEContext&);
void fn_sub_592E80_00592e80(p3fes::EEContext&);
void fn_sub_592EA0_00592ea0(p3fes::EEContext&);
void fn_sub_592F38_00592f38(p3fes::EEContext&);
void fn_sub_5930C8_005930c8(p3fes::EEContext&);
void fn_sub_593200_00593200(p3fes::EEContext&);
void fn_sub_593468_00593468(p3fes::EEContext&);
void fn_sub_593590_00593590(p3fes::EEContext&);
void fn_sub_593700_00593700(p3fes::EEContext&);
void fn_sub_593878_00593878(p3fes::EEContext&);
void fn_sub_5938C0_005938c0(p3fes::EEContext&);
void fn_sub_593900_00593900(p3fes::EEContext&);
void fn_sub_593958_00593958(p3fes::EEContext&);
void fn_sub_593968_00593968(p3fes::EEContext&);
void fn_sub_593978_00593978(p3fes::EEContext&);
void fn_sub_593A18_00593a18(p3fes::EEContext&);
void fn_sub_593AA0_00593aa0(p3fes::EEContext&);
void fn_sub_593AB0_00593ab0(p3fes::EEContext&);
void fn_sub_593AC8_00593ac8(p3fes::EEContext&);
void fn_sub_593AE0_00593ae0(p3fes::EEContext&);
void fn_sub_593B10_00593b10(p3fes::EEContext&);
void fn_sub_593B38_00593b38(p3fes::EEContext&);
void fn_sub_593DB0_00593db0(p3fes::EEContext&);
void fn_sub_593E08_00593e08(p3fes::EEContext&);
void fn_sub_593EA0_00593ea0(p3fes::EEContext&);
void fn_sub_593FB0_00593fb0(p3fes::EEContext&);
void fn_sub_593FE8_00593fe8(p3fes::EEContext&);
void fn_sub_594108_00594108(p3fes::EEContext&);
void fn_sub_5941A8_005941a8(p3fes::EEContext&);
void fn_sub_5942E8_005942e8(p3fes::EEContext&);
void fn_sub_5943D8_005943d8(p3fes::EEContext&);
void fn_sub_594428_00594428(p3fes::EEContext&);
void fn_sub_5944A8_005944a8(p3fes::EEContext&);
void fn_sub_5946A8_005946a8(p3fes::EEContext&);
void fn_sub_5947A8_005947a8(p3fes::EEContext&);
void fn_sub_594AC0_00594ac0(p3fes::EEContext&);
void fn_sub_594B68_00594b68(p3fes::EEContext&);
void fn_sub_594B78_00594b78(p3fes::EEContext&);
void fn_sub_594B88_00594b88(p3fes::EEContext&);
void fn_sub_594C38_00594c38(p3fes::EEContext&);
void fn_sub_594EC8_00594ec8(p3fes::EEContext&);
void fn_sub_595010_00595010(p3fes::EEContext&);
void fn_sub_595038_00595038(p3fes::EEContext&);
void fn_sub_595060_00595060(p3fes::EEContext&);
void fn_sub_595110_00595110(p3fes::EEContext&);
void fn_sub_595138_00595138(p3fes::EEContext&);
void fn_sub_5951A8_005951a8(p3fes::EEContext&);
void fn_sub_595208_00595208(p3fes::EEContext&);
void fn_sub_595260_00595260(p3fes::EEContext&);
void fn_sub_595390_00595390(p3fes::EEContext&);
void fn_sub_5954D8_005954d8(p3fes::EEContext&);
void fn_sub_5954E8_005954e8(p3fes::EEContext&);
void fn_sub_595700_00595700(p3fes::EEContext&);
void fn_sub_595718_00595718(p3fes::EEContext&);
void fn_sub_595868_00595868(p3fes::EEContext&);
void fn_sub_5959D0_005959d0(p3fes::EEContext&);
void fn_sub_5959E0_005959e0(p3fes::EEContext&);
void fn_sub_595B30_00595b30(p3fes::EEContext&);
void fn_sub_595B58_00595b58(p3fes::EEContext&);
void fn_sub_595D10_00595d10(p3fes::EEContext&);
void fn_sub_595E28_00595e28(p3fes::EEContext&);
void fn_sub_595E50_00595e50(p3fes::EEContext&);
void fn_sub_595E68_00595e68(p3fes::EEContext&);
void fn_sub_595E98_00595e98(p3fes::EEContext&);
void fn_sub_595F58_00595f58(p3fes::EEContext&);
void fn_sub_596008_00596008(p3fes::EEContext&);
void fn_sub_596038_00596038(p3fes::EEContext&);
void fn_sub_5960E0_005960e0(p3fes::EEContext&);
void fn_sub_596168_00596168(p3fes::EEContext&);
void fn_sub_596230_00596230(p3fes::EEContext&);
void fn_sub_5962D0_005962d0(p3fes::EEContext&);
void fn_sub_596340_00596340(p3fes::EEContext&);
void fn_sub_596348_00596348(p3fes::EEContext&);
void fn_sub_5963B0_005963b0(p3fes::EEContext&);
void fn_sub_596460_00596460(p3fes::EEContext&);
void fn_sub_5965E0_005965e0(p3fes::EEContext&);
void fn_sub_5966C0_005966c0(p3fes::EEContext&);
void fn_sub_596760_00596760(p3fes::EEContext&);
void fn_sub_596898_00596898(p3fes::EEContext&);
void fn_sub_596908_00596908(p3fes::EEContext&);
void fn_sub_596978_00596978(p3fes::EEContext&);
void fn_sub_596A40_00596a40(p3fes::EEContext&);
void fn_sub_596A98_00596a98(p3fes::EEContext&);
void fn_sub_596B28_00596b28(p3fes::EEContext&);
void fn_sub_596C28_00596c28(p3fes::EEContext&);
void fn_sub_596CC0_00596cc0(p3fes::EEContext&);
void fn_sub_596D28_00596d28(p3fes::EEContext&);
void fn_sub_596D68_00596d68(p3fes::EEContext&);
void fn_sub_596F98_00596f98(p3fes::EEContext&);
void fn_sub_597000_00597000(p3fes::EEContext&);
void fn_sub_597078_00597078(p3fes::EEContext&);
void fn_sub_597088_00597088(p3fes::EEContext&);
void fn_sub_597100_00597100(p3fes::EEContext&);
void fn_sub_5971D0_005971d0(p3fes::EEContext&);
void fn_sub_5971E8_005971e8(p3fes::EEContext&);
void fn_sub_597288_00597288(p3fes::EEContext&);
void fn_sub_597330_00597330(p3fes::EEContext&);
void fn_sub_597340_00597340(p3fes::EEContext&);
void fn_sub_5973C0_005973c0(p3fes::EEContext&);
void fn_sub_5974A8_005974a8(p3fes::EEContext&);
void fn_sub_597878_00597878(p3fes::EEContext&);
void fn_sub_5978E8_005978e8(p3fes::EEContext&);
void fn_sub_597968_00597968(p3fes::EEContext&);
void fn_sub_597C28_00597c28(p3fes::EEContext&);
void fn_sub_597D20_00597d20(p3fes::EEContext&);
void fn_sub_597DC8_00597dc8(p3fes::EEContext&);
void fn_sub_597E20_00597e20(p3fes::EEContext&);
void fn_sub_597E80_00597e80(p3fes::EEContext&);
void fn_sub_597E98_00597e98(p3fes::EEContext&);
void fn_sub_597FA0_00597fa0(p3fes::EEContext&);
void fn_sub_598030_00598030(p3fes::EEContext&);
void fn_sub_5980C8_005980c8(p3fes::EEContext&);
void fn_sub_598140_00598140(p3fes::EEContext&);
void fn_sub_5982A0_005982a0(p3fes::EEContext&);
void fn_sub_5982E0_005982e0(p3fes::EEContext&);
void fn_sub_598470_00598470(p3fes::EEContext&);
void fn_sub_598640_00598640(p3fes::EEContext&);
void fn_sub_598688_00598688(p3fes::EEContext&);
void fn_sub_598D20_00598d20(p3fes::EEContext&);
void fn_sub_598D90_00598d90(p3fes::EEContext&);
void fn_sub_598E18_00598e18(p3fes::EEContext&);
void fn_sub_598E88_00598e88(p3fes::EEContext&);
void fn_sub_598EE8_00598ee8(p3fes::EEContext&);
void fn_sub_599240_00599240(p3fes::EEContext&);
void fn_sub_599408_00599408(p3fes::EEContext&);
void fn_sub_599810_00599810(p3fes::EEContext&);
void fn_sub_599A30_00599a30(p3fes::EEContext&);
void fn_sub_599A78_00599a78(p3fes::EEContext&);
void fn_sub_599E08_00599e08(p3fes::EEContext&);
void fn_sub_59A028_0059a028(p3fes::EEContext&);
void fn_sub_59A150_0059a150(p3fes::EEContext&);
void fn_sub_59A168_0059a168(p3fes::EEContext&);
void fn_sub_59A508_0059a508(p3fes::EEContext&);
void fn_sub_59A560_0059a560(p3fes::EEContext&);
void fn_sub_59A578_0059a578(p3fes::EEContext&);
void fn_sub_59A600_0059a600(p3fes::EEContext&);
void fn_sub_59A860_0059a860(p3fes::EEContext&);
void fn_sub_59A870_0059a870(p3fes::EEContext&);
void fn_sub_59A910_0059a910(p3fes::EEContext&);
void fn_sub_59A9D8_0059a9d8(p3fes::EEContext&);
void fn_sub_59AD80_0059ad80(p3fes::EEContext&);
void fn_sub_59AE88_0059ae88(p3fes::EEContext&);
void fn_sub_59AEC0_0059aec0(p3fes::EEContext&);
void fn_sub_59B048_0059b048(p3fes::EEContext&);
void fn_sub_59B198_0059b198(p3fes::EEContext&);
void fn_sub_59B210_0059b210(p3fes::EEContext&);
void fn_sub_59B3A8_0059b3a8(p3fes::EEContext&);
void fn_sub_59B490_0059b490(p3fes::EEContext&);
void fn_sub_59B4B0_0059b4b0(p3fes::EEContext&);
void fn_sub_59B620_0059b620(p3fes::EEContext&);
void fn_sub_59B6D8_0059b6d8(p3fes::EEContext&);
void fn_sub_59B720_0059b720(p3fes::EEContext&);
void fn_sub_59B840_0059b840(p3fes::EEContext&);
void fn_sub_59B930_0059b930(p3fes::EEContext&);
void fn_sub_59B9D0_0059b9d0(p3fes::EEContext&);
void fn_sub_59BA70_0059ba70(p3fes::EEContext&);
void fn_sub_59BA90_0059ba90(p3fes::EEContext&);
void fn_sub_59BAB0_0059bab0(p3fes::EEContext&);
void fn_sub_59BAD0_0059bad0(p3fes::EEContext&);
void fn_sub_59BAF0_0059baf0(p3fes::EEContext&);
void fn_sub_59BAF0_0059baf0_at_0059bb10(p3fes::EEContext&);
void fn_sub_59BB50_0059bb50(p3fes::EEContext&);
void fn_sub_59BB88_0059bb88(p3fes::EEContext&);
void fn_sub_59BC20_0059bc20(p3fes::EEContext&);
void fn_sub_59BC88_0059bc88(p3fes::EEContext&);
void fn_sub_59BCB8_0059bcb8(p3fes::EEContext&);
void fn_sub_59BCD0_0059bcd0(p3fes::EEContext&);
void fn_sub_59C358_0059c358(p3fes::EEContext&);
void fn_sub_59C418_0059c418(p3fes::EEContext&);
void fn_sub_59C480_0059c480(p3fes::EEContext&);
void fn_sub_59C5E0_0059c5e0(p3fes::EEContext&);
void fn_sub_5A1A30_005a1a30(p3fes::EEContext&);
void fn_sub_5A1B58_005a1b58(p3fes::EEContext&);
void fn_sub_5A1B80_005a1b80(p3fes::EEContext&);
void fn_viBufCreate_00594130(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace libs13;

// 0x00590008 sub_590008 -- 856 bytes; frame 0x70: s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, s4 sp+0x40, s5 sp+0x48, s6 sp+0x50, s7 sp+0x58, fp sp+0x60, s3 sp+0x38, ra sp+0x68
// Video decoder, the picture-header step of an SFD handle: sets the MPV window, reads the next header from the input
//   chunk (sub_579450) and charges the bytes it took, reads the picture info (sub_579138; error -16773371); with flag
//   0x40, a sequence-size check and the param-95 callback may refuse the picture (*a4 = -2); sets the skip mark
//   work+372 by picture type and format, the temporal-reference change (+268 / +272), the param-77 / 78 user-data
//   callback; then the time stamp (sub_590360) and, when the flag mask matches, the time-code chain (sub_5905F0,
//   sub_590948, sub_590EF0, sub_590FD0, sub_591168).
void sub_590008(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00590008
    enter(ctx, 52);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s0, sp, 0x20);
    s0 = a2;
    sd(s1, sp, 0x28);
    sd(s2, sp, 0x30);
    sd(s4, sp, 0x40);
    s4 = a0;
    sd(s5, sp, 0x48);
    sd(s6, sp, 0x50);
    s6 = t0;
    sd(s7, sp, 0x58);
    sd(fp, sp, 0x60);
    fp = a1;
    sd(s3, sp, 0x38);
    sd(ra, sp, 0x68);
    lw(s3, s4, sfd::kVdecWork);
    sw(a3, sp, 0x10);
    s7 = addiu(s3, 4224);
    s5 = addiu(s3, 140);
    lw(v0, s3, 0);
    sw(v0, sp, 0x14);
    sw(zero, s7, 16);
    lw(a1, s7, 12);
    lw(a0, sp, 0x14);
    link(ctx, 0x590068u);  // $ra first: the delay slot below depends on it
    lw(a2, s7, 8);
    call(ctx, gen::fn_sub_579410_00579410);
    a0 = s0;
    a2 = 1;
    a1 = 0;
    jal(ctx, 0x590078u, gen::fn_sub_562E10_00562e10);
    a1 = s0;
    lw(a0, sp, 0x14);
    s2 = v0;
    jal(ctx, 0x590088u, gen::fn_sub_579450_00579450);
    a0 = s0;
    sw(v0, s6, 0);
    a1 = 0;
    a2 = 1;
    jal(ctx, 0x59009Cu, gen::fn_sub_562E10_00562e10);
    a0 = s4;
    s1 = subu(v0, s2);
    lw(a1, s6, 0);
    a3 = lui(0xFF00);
    a2 = s1;
    a3 = a3 | 0xF04;
    jal(ctx, 0x5900B8u, gen::fn_sub_58FF70_0058ff70);
    a0 = s4;
    s0 = v0;
    a1 = s1;
    jal(ctx, 0x5900C8u, gen::fn_sub_58FEC8_0058fec8);
    v0 = s0;
    if (s0 == 0) {
        // 0x005900d8
        charge(ctx, 4);
        lw(v1, s6, 0);
        s0 = si(-2);
        v0 = 0;
        if (v1 == s0) {
            goto L_00590330;
        }
        // 0x005900e8
        charge(ctx, 6);
        lw(a0, sp, 0x14);
        a1 = s5;
        jal(ctx, 0x5900ECu, gen::fn_sub_579138_00579138);
        v1 = v0;
        sw(v1, s6, 0);
        if (v1 == 0) {
            // 0x00590118
            charge(ctx, 4);
            lw(v1, sp, 0x10);
            s1 = v1 & 0x40;
            if (s1 == 0) {
                lw(a0, s5, 24);
            } else {
                // 0x00590128
                charge(ctx, 3);
                lw(a0, s4, 2316);
                a1 = 95;
                if (i64(a0) > 0) {
                    // 0x00590134
                    charge(ctx, 3);
                    lw(v1, s5, 0);
                    if (a0 != v1) {
                        sw(s0, s6, 0);
                    } else {
                        // 0x00590140
                        charge(ctx, 4);
                        lw(a0, s4, 2320);
                        lw(v1, s5, 4);
                        if (a0 == v1) {
                            goto L_00590158;
                        }
                        // 0x00590150
                        charge(ctx, 2);
                        sw(s0, s6, 0);
                    }
                    goto L_00590330;
                }
            L_00590158:
                charge(ctx, 8);
                a0 = s4;
                jal(ctx, 0x590158u, gen::fn_sub_599408_00599408);
                a0 = s4;
                s0 = v0;
                a1 = 95;
                jal(ctx, 0x590168u, gen::fn_sub_599408_00599408);
                a0 = v0;
                if (s0 != 0) {
                    // 0x00590178
                    charge(ctx, 5);
                    lw(a1, s5, 0);
                    jt = s0.u();  // the target, read before the delay slot
                    link(ctx, 0x59017Cu);  // $ra = the return address
                    lw(a2, s5, 4);
                    call_ptr(ctx, jt);
                    v1 = si(-2);
                    if (v0 == 0) {
                        goto L_00590198;
                    }
                    // 0x0059018c
                    charge(ctx, 3);
                    v0 = 0;
                    sw(v1, s6, 0);
                    goto L_00590330;
                }
            L_00590198:
                charge(ctx, 1);
                lw(a0, s5, 24);
            }
            // 0x0059019c
            charge(ctx, 3);
            a2 = 1;
            if (a0 == a2) {
                // 0x005901a8
                charge(ctx, 2);
                sw(zero, s3, 372);
                goto L_00590210;
            }
            lw(a1, s4, 56);
            // 0x005901b0
            charge(ctx, 3);
            v0 = 3;
            if (a1 != v0) {
                lw(a0, sp, 0x14);
            L_00590214:
                charge(ctx, 1);
                a2 = addiu(s7, 16);
            } else {
                // 0x005901bc
                charge(ctx, 3);
                lw(v1, s3, 356);
                v0 = 2;
                if (v1 == 0) {
                L_00590210:
                    charge(ctx, 1);
                    lw(a0, sp, 0x14);
                    goto L_00590214;
                }
                // 0x005901c8
                charge(ctx, 2);
                lw(v1, v1, 112);
                if (a0 != v0) {
                    // 0x005901f8
                    charge(ctx, 2);
                    cc = a0 != a1;  // the condition, before the delay slot changes it
                    lw(a0, sp, 0x14);
                    if (!cc) {
                        // 0x00590200
                        charge(ctx, 4);
                        lw(v0, s5, 20);
                        v0 = slt(v0, v1);
                        if (v0 == 0) {
                            sw(a2, s3, 372);
                        }
                        goto L_00590210;
                    }
                    goto L_00590214;
                }
                // 0x005901d0
                charge(ctx, 4);
                lw(v0, s5, 20);
                v0 = slt(v0, v1);
                lw(a0, sp, 0x14);
                if (v0 == 0) {
                    goto L_00590214;
                }
                // 0x005901e0
                charge(ctx, 3);
                v0 = slti(v1, 512);
                if (v0 != 0) {
                    // 0x005901ec
                    charge(ctx, 2);
                    sw(a2, s3, 372);
                    goto L_00590210;
                }
                a2 = addiu(s7, 16);
            }
            // 0x00590218
            charge(ctx, 6);
            a1 = 0;
            jal(ctx, 0x590218u, gen::fn_sub_579428_00579428);
            lw(v0, s3, 268);
            lw(v1, s5, 48);
            cc = v0 == v1;  // the condition, before the delay slot changes it
            v0 = 1;
            if (cc) {
                // 0x00590240
                charge(ctx, 1);
                sw(zero, s3, 272);
            } else {
                // 0x00590230
                charge(ctx, 3);
                sw(v1, s3, 268);
                sw(v0, s3, 272);
            }
            // 0x00590244
            charge(ctx, 2);
            if (s1 == 0) {
                lw(a0, fp, 0x0);
            } else {
                // 0x0059024c
                charge(ctx, 9);
                a1 = 77;
                a0 = s4;
                jal(ctx, 0x590250u, gen::fn_sub_599408_00599408);
                a0 = s4;
                a1 = 78;
                s1 = v0;
                jal(ctx, 0x590260u, gen::fn_sub_599408_00599408);
                s0 = v0;
                if (s1 != 0) {
                    // 0x00590270
                    charge(ctx, 6);
                    lw(a0, fp, 0x0);
                    a2 = 1;
                    link(ctx, 0x590278u);  // $ra first: the delay slot below depends on it
                    lw(a1, fp, 0x4);
                    call(ctx, gen::fn_sub_578160_00578160);
                    a0 = s0;
                    if (v0 != 0) {
                        // 0x00590288
                        charge(ctx, 4);
                        lw(a1, fp, 0x0);
                        a2 = subu(v0, a1);
                        a2 = addiu(a2, 4);
                        jalr(ctx, 0x590290u, s1.u());
                    }
                }
                // 0x00590298
                charge(ctx, 1);
                lw(a0, fp, 0x0);
            }
            // 0x0059029c
            charge(ctx, 17);
            a2 = 4;
            link(ctx, 0x5902A0u);  // $ra first: the delay slot below depends on it
            lw(a1, fp, 0x4);
            call(ctx, gen::fn_sub_578160_00578160);
            a0 = s4;
            lw(t1, s3, 272);
            a1 = s5;
            a2 = v0;
            a3 = sp;
            t0 = addiu(sp, 0x8);
            jal(ctx, 0x5902BCu, gen::fn_sub_590360_00590360);
            lw(v1, s3, 120);
            lw(a1, sp, 0x10);
            v0 = 0;
            ld(a0, sp, 0x8);
            v1 = a1 & v1;
            sd(a0, s3, 4384);
            if (v1 != 0) {
                // 0x005902e0
                charge(ctx, 20);
                lw(a2, s3, 272);
                a0 = s4;
                a1 = s5;
                jal(ctx, 0x5902E8u, gen::fn_sub_5905F0_005905f0);
                a0 = s4;
                lw(a3, s3, 272);
                a1 = s5;
                link(ctx, 0x5902FCu);  // $ra first: the delay slot below depends on it
                ld(a2, sp, 0x0);
                call(ctx, gen::fn_sub_590948_00590948);
                a0 = s4;
                a1 = s5;
                jal(ctx, 0x590308u, gen::fn_sub_590EF0_00590ef0);
                a0 = s4;
                a1 = s5;
                jal(ctx, 0x590314u, gen::fn_sub_590FD0_00590fd0);
                a0 = s4;
                lw(a1, sp, 0x14);
                a2 = s5;
                a3 = fp;
                jal(ctx, 0x590328u, gen::fn_sub_591168_00591168);
            }
            goto L_00590330;
        }
        // 0x00590100
        charge(ctx, 6);
        a1 = lui(0xFF00);
        a0 = s4;
        a1 = a1 | 0xF05;
        jal(ctx, 0x590108u, gen::fn_sub_58BE40_0058be40);
        ld(s0, sp, 0x20);
        // 0x00590334 (the shared epilogue, written out on this path)
        charge(ctx, 11);
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
L_00590330:
    charge(ctx, 1);
    ld(s0, sp, 0x20);
    // 0x00590334 (the shared epilogue, written out on this path)
    charge(ctx, 11);
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
}

// 0x00590360 sub_590360 -- 168 bytes; frame 0x50: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s4 sp+0x30, s5 sp+0x38, s3 sp+0x28, ra sp+0x40
// The picture's time stamp: both outs -1; with a chunk address, the stream's time stamp for it (sub_5980C8) and, when
//   one is found, its conversion (sub_590430).
void sub_590360(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00590360
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v1 = si(-1);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = t0;
    sd(s2, sp, 0x20);
    s2 = t1;
    sd(s4, sp, 0x30);
    s4 = a3;
    sd(s5, sp, 0x38);
    s5 = a1;
    sd(s3, sp, 0x28);
    v0 = addiu(s0, 8120);
    sd(ra, sp, 0x40);
    a3 = sp;
    lw(s3, v0, 8);
    lw(a1, v0, 16);
    sd(v1, s4, 0);
    sd(v1, s1, 0);
    if (a2 != 0) {
        // 0x005903b4
        charge(ctx, 8);
        jal(ctx, 0x5903B4u, gen::fn_sub_5980C8_005980c8);
        a0 = addiu(s0, 3376);
        ld(v0, sp, 0x0);
        a3 = sp;
        t1 = s1;
        t0 = s2;
        if (i64(v0) >= 0) {
            // 0x005903d4
            charge(ctx, 4);
            a1 = addiu(s3, 280);
            a2 = s5;
            jal(ctx, 0x5903D8u, gen::fn_sub_590430_00590430);
            sd(v0, s4, 0);
        }
    }
    // 0x005903e4 (the shared epilogue, written out on this path)
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

// 0x00590408 sub_590408 -- 40 bytes; leaf frame (no stack)
// Resets a time-stamp record: words 0..2 and 6 = 0, the 64-bit word at +16 and word 7 = -1.
void sub_590408(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00590408
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = addiu(a0, 16);
    v1 = si(-1);
    a1 = si(-1);
    sw(zero, a0, 8);
    sw(zero, a0, 0);
    sw(zero, a0, 4);
    sd(v1, v0, 0);
    sw(a1, v0, 12);
    sw(zero, v0, 8);
}

// 0x005905F0 sub_5905F0 -- 644 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s4 sp+0x20, s5 sp+0x28, s3 sp+0x18, ra sp+0x30
// The temporal-reference table (64 x {u16 count, u16 sum} at handle+4576): a new sequence clears it, otherwise the
//   slots skipped since the reference are cleared; stores the picture's field count and the running sum, and for a B
//   picture (type 3) patches the reference picture's sum and calls sub_590878.
void sub_5905F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005905f0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s4, sp, 0x20);
    s4 = a2;
    sd(s5, sp, 0x28);
    s5 = addiu(s2, 3376);
    sd(s3, sp, 0x18);
    a0 = s0;
    sd(ra, sp, 0x30);
    a1 = addiu(s2, 3404);
    s1 = addiu(s2, 4576);
    link(ctx, 0x59062Cu);  // $ra first: the delay slot below depends on it
    lw(s3, s2, sfd::kVdecWork);
    call(ctx, gen::fn_sub_591118_00591118);
    v1 = si(-1);
    if (s4 != 0) {
        // 0x0059063c
        charge(ctx, 3);
        a2 = 63;
        v0 = addiu(s2, 4828);
        for (;;) {
            // 0x00590648
            charge(ctx, 7);
            a2 = addiu(a2, -1);
            sh(v1, v0, 0);
            v0 = addiu(v0, -4);
            if (i64(a2) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00590664
        charge(ctx, 5);
        v0 = si(-1);
        lw(a3, s0, 20);
        sh(v0, s1, 2);
        lw(t2, s0, 24);
        goto L_005906f8;
    }
    // 0x00590678
    charge(ctx, 5);
    lw(t2, s0, 24);
    v0 = addiu(t2, -1);
    v0 = sltiu(v0, 2);
    lw(a3, s0, 20);
    if (v0 == 0) {
    L_005906f8:
        charge(ctx, 1);
        v1 = slti(a3, 0);
    } else {
        // 0x0059068c
        charge(ctx, 10);
        lw(v0, s3, 356);
        lw(a0, v0, 112);
        a1 = addiu(a3, 1024);
        t0 = a3;
        v1 = slt(a3, a0);
        a2 = addiu(a0, 1);
        if (v1 != 0) t0 = a1;
        v0 = slt(a2, t0);
        v1 = slti(a3, 0);
        if (v0 != 0) {
            // 0x005906b4
            charge(ctx, 1);
            a1 = si(-1);
            for (;;) {
                // 0x005906b8
                charge(ctx, 13);
                v1 = slti(a2, 0);
                a0 = addiu(a2, 63);
                v0 = a2;
                if (v1 != 0) v0 = a0;
                v0 = sra(v0, 6);
                v0 = sll(v0, 6);
                v0 = subu(a2, v0);
                a2 = addiu(a2, 1);
                v0 = sll(v0, 2);
                v1 = slt(a2, t0);
                v0 = addu(v0, s1);
                sh(a1, v0, 0);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x005906ec
            charge(ctx, 2);
            v1 = slti(a3, 0);
        }
    }
    // 0x005906fc
    charge(ctx, 11);
    a0 = addiu(a3, 63);
    v0 = a3;
    lhu(a1, s5, 56);
    if (v1 != 0) v0 = a0;
    t0 = sra(v0, 6);
    v1 = sll(t0, 6);
    t0 = subu(a3, v1);
    t1 = sll(t0, 2);
    v0 = addu(t1, s1);
    sh(a1, v0, 0);
    if (s4 == 0) {
        // 0x00590730
        charge(ctx, 2);
        a2 = 0;
        if (a3 != 0) {
            // 0x00590768
            charge(ctx, 2);
            a3 = si(-1);
        L_00590770:
            charge(ctx, 1);
            v1 = subu(t0, a2);
            for (;;) {
                // 0x00590774
                charge(ctx, 15);
                a2 = addiu(a2, 1);
                a1 = addiu(v1, 63);
                v1 = addiu(v1, 126);
                a0 = slti(a1, 0);
                v0 = a1;
                if (a0 != 0) v0 = v1;
                a0 = slti(a2, 64);
                v0 = sra(v0, 6);
                v1 = sll(v0, 6);
                v0 = subu(a1, v1);
                v0 = sll(v0, 2);
                v0 = addu(v0, s1);
                lh(v1, v0, 0);
                lhu(a1, v0, 0);
                if (v1 != a3) {
                    backedge(ctx);
                    goto L_00590750;
                }
                // 0x005907b0
                charge(ctx, 2);
                v1 = subu(t0, a2);
                if (a0 != 0) {
                    backedge(ctx);
                    continue;
                }
                break;
            }
        } else {
            // 0x00590738
            charge(ctx, 4);
            lh(v1, s1, 2);
            v0 = si(-1);
            if (v1 != v0) {
                a3 = si(-1);
                goto L_00590770;
            }
            // 0x00590748
            charge(ctx, 2);
            sh(zero, s1, 2);
        }
    } else {
        // 0x00590728
        charge(ctx, 2);
        sh(zero, v0, 2);
    }
L_005907b8:
    charge(ctx, 5);
    a1 = addu(t1, s1);
    v1 = 3;
    lhu(v0, a1, 2);
    sh(v0, s5, 58);
    if (t2 != v1) {
        // 0x00590850 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        return;
    }
    // 0x005907cc
    charge(ctx, 3);
    lh(v0, a1, 0);
    lhu(v1, a1, 0);
    if (v0 == 0) {
        // 0x00590850 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        return;
    }
    // 0x005907d8
    charge(ctx, 29);
    lw(t1, s3, 356);
    a0 = s2;
    lhu(a3, a1, 2);
    lw(a2, t1, 112);
    a1 = t1;
    a3 = addu(v1, a3);
    t0 = addiu(a2, 63);
    v0 = a2;
    v1 = slti(a2, 0);
    if (v1 != 0) v0 = t0;
    v0 = sra(v0, 6);
    v1 = sll(v0, 6);
    v0 = subu(a2, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, s1);
    sh(a3, v0, 2);
    link(ctx, 0x590818u);  // $ra first: the delay slot below depends on it
    sh(a3, t1, 46);
    call(ctx, gen::fn_sub_590878_00590878);
    a0 = s2;
    lw(a1, s3, 356);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
    gen::fn_sub_5923E0_005923e0_at_00592488(ctx);  // tail call
    return;
L_00590750:
    charge(ctx, 5);
    lhu(v0, v0, 2);
    v1 = addu(t1, s1);
    v0 = addu(a1, v0);
    sh(v0, v1, 2);
    goto L_005907b8;
}

// 0x00590948 sub_590948 -- 220 bytes; frame 0x30: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// The time-code source: when param 52 is unset and the picture has no time stamp but a GOP time code (sub_590A28),
//   param 52 = 1; then, with param 52 = 1, builds the time code (sub_590AE8).
void sub_590948(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00590948
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a1;
    a1 = 52;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    s4 = a3;
    jal(ctx, 0x590974u, gen::fn_sub_599408_00599408);
    s0 = v0;
    v0 = 1;
    if (s0 == 0) {
        // 0x00590988
        charge(ctx, 2);
        a0 = s2;
        if (i64(s3) < 0) {
            // 0x00590990
            charge(ctx, 3);
            lw(v0, s1, 48);
            a1 = 52;
            if (v0 == 0) {
            L_005909c4:
                charge(ctx, 1);
                a2 = 1;
            L_005909c8:
                charge(ctx, 2);
                s0 = 1;
                jal(ctx, 0x5909C8u, gen::fn_sub_599240_00599240);
            L_005909d0:
                charge(ctx, 1);
                v0 = 1;
            } else {
                // 0x0059099c
                charge(ctx, 3);
                lb(v0, s1, 87);
                a2 = 1;
                if (v0 != 0) {
                    goto L_005909c8;
                }
                // 0x005909a8
                charge(ctx, 2);
                if (s4 != 0) {
                    // 0x005909b0
                    charge(ctx, 4);
                    a1 = s1;
                    jal(ctx, 0x5909B0u, gen::fn_sub_590A28_00590a28);
                    a0 = s2;
                    if (v0 != 0) {
                        goto L_005909c0;
                    }
                    goto L_005909d0;
                }
                v0 = 1;
            }
            goto L_005909d4;
        }
    L_005909c0:
        charge(ctx, 1);
        a1 = 52;
        goto L_005909c4;
    }
L_005909d4:
    charge(ctx, 2);
    cc = s0 != v0;  // the condition, before the delay slot changes it
    ld(s0, sp, 0x0);
    if (cc) {
        // 0x00590a08
        charge(ctx, 7);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x005909dc
    charge(ctx, 11);
    a0 = s2;
    ld(s2, sp, 0x10);
    a1 = s1;
    ld(s1, sp, 0x8);
    a2 = s3;
    ld(s3, sp, 0x18);
    a3 = s4;
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    gen::fn_sub_590AE8_00590ae8(ctx);  // tail call
}

// 0x00590AE8 sub_590AE8 -- 780 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Builds the picture's time code (handle+3404): from a time stamp, frames = PTS * 2 / rate (sub_57BC10) split into
//   h:m:s:f at the rate 0x7CA068[code], with the drop-frame tables 0x7CA090 (29.97) / 0x7CA0B0 (59.94); otherwise
//   from the GOP time code advanced by the field count (sub_590DF8), or the previous one copied, or zero.
void sub_590AE8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00590ae8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = a0;
    sd(s0, sp, 0x0);
    s0 = addiu(t0, 3376);
    sd(s1, sp, 0x8);
    a0 = a2;
    sd(ra, sp, 0x10);
    lw(s1, a1, 20);
    lw(a2, a1, 28);
    lw(a1, a1, 16);
    if (a3 != 0) {
        // 0x00590b14
        charge(ctx, 2);
        ld(ra, sp, 0x10);
        if (i64(a0) < 0) {
            goto L_00590b38;
        }
        // 0x00590b1c
        charge(ctx, 6);
        a3 = s1;
        ld(s1, sp, 0x8);
        ld(s0, sp, 0x0);
        t0 = addiu(t0, 3404);
        sp = addiu(sp, 0x20);
        // 0x00590be0
        charge(ctx, 34);
        sp = addiu(sp, -0x40);
        sd(s0, sp, 0x0);
        s0 = a1;
        v0 = sll(s0, 2);
        sd(s4, sp, 0x20);
        s4 = 0x7D0000;
        s4 = addu(s4, v0);
        lw(s4, s4, -23872);
        sd(s2, sp, 0x10);
        s2 = a2;
        a1 = sll(s4, 1);
        a2 = 0x55D0000;
        a2 = a2 | 0x4A80;
        sd(s1, sp, 0x8);
        sd(s3, sp, 0x18);
        s1 = a3;
        sd(s5, sp, 0x28);
        sd(ra, sp, 0x30);
        s3 = 0x7D0000;
        s3 = addu(s3, v0);
        lw(s3, s3, -24472);
        s5 = t0;
        jal(ctx, 0x590C34u, gen::fn_sub_57BC10_0057bc10);
        a1 = dsll32(v0, 0);
        a1 = dsra32(a1, 0);
        sw(s0, s5, 0);
        v1 = a1 & 0x1;
        a1 = sra(a1, 1);
        a1 = subu(a1, s1);
        sw(s2, s5, 4);
        v0 = slti(a1, 0);
        sh(v1, s5, 30);
        if (v0 != 0) a1 = 0;
        if (s2 == 0) {
            // 0x00590d78
            charge(ctx, 1);
            div(a1, s3);
        L_00590d7c:
            charge(ctx, 5);
            a1 = 60;
            v1 = 60;
            a0 = 60;
            if (s3 == 0) {
                brk(ctx, 0x590D8Cu, 0x7u);
            }
            // 0x00590d90
            charge(ctx, 12);
            a2 = 60;
            mflo(v0);
            mfhi(a3);
            div(v0, v1);
            mflo(v0);
            mfhi(a0);
            div(v0, v1);
            v1 = a0;
            mflo(v0);
            mfhi(a1);
            t2 = v0;
            t1 = a1;
        } else {
            // 0x00590c68
            charge(ctx, 3);
            v0 = 29970;
            cc = s4 == v0;  // the condition, before the delay slot changes it
            v0 = 0xEA24;
            if (!cc) {
                // 0x00590c74
                charge(ctx, 2);
                if (s4 != v0) {
                    div(a1, s3);
                    goto L_00590d7c;
                }
                // 0x00590c7c
                charge(ctx, 2);
                v0 = 0x7D0000;
                // 0x00590c98
                charge(ctx, 1);
                t0 = addiu(v0, -24400);
                goto L_00590c9c;
            }
            // 0x00590c88
            charge(ctx, 3);
            v0 = 0x7D0000;
            t0 = addiu(v0, -24432);  // &0x7CA090
        L_00590c9c:
            charge(ctx, 4);
            lw(v0, t0, 0);
            div(a1, v0);
            if (v0 == 0) {
                brk(ctx, 0x590CA8u, 0x7u);
            }
            // 0x00590cac
            charge(ctx, 12);
            lw(v1, t0, 4);
            lw(a2, t0, 8);
            mfhi(a0);
            mflo(a1);
            div(a0, v1);
            t2 = a1;
            mfhi(v0);
            mflo(a0);
            a1 = v0;
            v0 = slt(a1, a2);
            t3 = a0;
            if (v0 == 0) {
                // 0x00590d00
                charge(ctx, 5);
                lw(v0, t0, 12);
                a1 = subu(a1, a2);
                div(a1, v0);
                if (v0 == 0) {
                    brk(ctx, 0x590D10u, 0x7u);
                }
                // 0x00590d14
                charge(ctx, 7);
                lw(a2, t0, 16);
                mfhi(v1);
                mflo(a0);
                a1 = v1;
                v0 = slt(a1, a2);
                t1 = addiu(a0, 1);
                if (v0 == 0) {
                    // 0x00590d40
                    charge(ctx, 5);
                    lw(v0, t0, 20);
                    a1 = subu(a1, a2);
                    div(a1, v0);
                    if (v0 == 0) {
                        brk(ctx, 0x590D50u, 0x7u);
                    }
                    // 0x00590d54
                    charge(ctx, 4);
                    mflo(v1);
                    mfhi(a0);
                    v1 = addiu(v1, 1);
                    a3 = a0;
                } else {
                    // 0x00590d30
                    charge(ctx, 4);
                    lw(v0, t0, 28);
                    v1 = 0;
                    a3 = addu(a1, v0);
                }
            } else {
                // 0x00590cdc
                charge(ctx, 5);
                lw(v0, t0, 20);
                t1 = 0;
                div(a1, v0);
                if (v0 == 0) {
                    brk(ctx, 0x590CECu, 0x7u);
                }
                // 0x00590cf0
                charge(ctx, 4);
                mfhi(a0);
                mflo(v1);
                a3 = a0;
            }
            // 0x00590d64
            charge(ctx, 4);
            lw(v0, t0, 24);
            mult(a0, v0, t3);
            t1 = addu(a0, t1);
        }
        // 0x00590dc0 (the shared epilogue, written out on this path)
        charge(ctx, 13);
        sw(a3, s5, 20);
        sw(t2, s5, 8);
        sw(t1, s5, 12);
        sw(v1, s5, 16);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        return;
    }
L_00590b38:
    charge(ctx, 3);
    lw(v0, s0, 104);
    if (v0 != 0) {
        // 0x00590b70
        charge(ctx, 2);
        a0 = addiu(s0, 108);
        if (a3 == 0) {
            // 0x00590b98
            charge(ctx, 12);
            lw(v1, s0, 108);
            lw(a0, s0, 112);
            lw(a1, s0, 116);
            lw(a2, s0, 120);
            lw(a3, s0, 124);
            lw(v0, s0, 128);
            sw(v1, s0, 28);
            sw(v0, s0, 48);
            sw(a0, s0, 32);
            sw(a1, s0, 36);
            sw(a2, s0, 40);
            sw(a3, s0, 44);
        } else {
            // 0x00590b78
            charge(ctx, 8);
            a1 = addiu(s0, 28);
            jal(ctx, 0x590B78u, gen::fn_sub_590DF8_00590df8);
            v0 = sll(s1, 2);
            lhu(v1, s0, 58);
            v0 = addu(v0, s0);
            sh(v1, s0, 1202);
            sh(v1, v0, 1202);
        }
    L_00590bc8:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    } else {
        // 0x00590b44
        charge(ctx, 3);
        lw(v0, t0, sfd::kHdrObj);
        if (v0 == 0) {
            // 0x00590b50
            charge(ctx, 7);
            sw(a1, s0, 28);
            sw(zero, s0, 48);
            sw(zero, s0, 32);
            sw(zero, s0, 36);
            sw(zero, s0, 40);
            sw(zero, s0, 44);
            goto L_00590bc8;
        }
        ld(s0, sp, 0x0);
    }
    // 0x00590bcc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00590DF8 sub_590DF8 -- 248 bytes; leaf frame (no stack)
// Advances a time code by its field count: frames + extra + 1 + fields / 2, carried into seconds, minutes and hours
//   at the rate 0x7CA068[code]; drop-frame: frame 0 / 1 of a minute not divisible by 10 becomes 2.
void sub_590DF8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00590df8
    enter(ctx, 27);  // entry check point + this block's cycles
    t5 = a0;
    t0 = 60;
    lh(v1, t5, 28);
    t2 = 60;
    lh(v0, t5, 30);
    t4 = 60;
    lw(a3, t5, 24);
    t3 = 60;
    t6 = addu(v1, v0);
    lw(t7, t5, 0);
    lw(a0, t5, 20);
    v0 = srl(t6, 31);
    v0 = addu(t6, v0);
    a2 = sll(t7, 2);
    a0 = addu(a0, a3);
    v1 = 0x7D0000;
    v1 = addu(v1, a2);
    lw(v1, v1, -24472);
    v0 = sra(v0, 1);
    t1 = addiu(a0, 1);
    t1 = addu(t1, v0);
    v0 = sll(v0, 1);
    div(t1, v1);
    lw(a0, t5, 16);
    lw(a2, t5, 12);
    if (v1 == 0) {
        brk(ctx, 0x590E60u, 0x7u);
    }
    // 0x00590e64
    charge(ctx, 15);
    lw(t2, t5, 8);
    lw(v1, t5, 4);
    t6 = subu(t6, v0);
    mflo(a3);
    mfhi(t1);
    a0 = addu(a0, a3);
    div(a0, t0);
    mflo(a0);
    mfhi(a3);
    a2 = addu(a2, a0);
    div(a2, t0);
    mflo(a2);
    mfhi(a0);
    t2 = addu(t2, a2);
    if (v1 != 0) {
        // 0x00590ea0
        charge(ctx, 2);
        if (a3 == 0) {
            // 0x00590ea8
            charge(ctx, 4);
            v0 = 10;
            div(a0, v0);
            if (v0 == 0) {
                brk(ctx, 0x590EB4u, 0x7u);
            }
            // 0x00590eb8
            charge(ctx, 3);
            mfhi(v1);
            cc = v1 == 0;  // the condition, before the delay slot changes it
            v1 = sltiu(t1, 2);
            if (!cc) {
                // 0x00590ec4
                charge(ctx, 2);
                v0 = 2;
                if (v1 != 0) t1 = v0;
            }
            goto L_00590ecc;
        }
        sw(t7, a1, 0);
        // 0x00590ed0 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        sh(t6, a1, 30);
        lw(v0, t5, 4);
        sw(t2, a1, 8);
        sw(v0, a1, 4);
        sw(a0, a1, 12);
        sw(a3, a1, 16);
        sw(t1, a1, 20);
        return;
    }
L_00590ecc:
    charge(ctx, 1);
    sw(t7, a1, 0);
    // 0x00590ed0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    sh(t6, a1, 30);
    lw(v0, t5, 4);
    sw(t2, a1, 8);
    sw(v0, a1, 4);
    sw(a0, a1, 12);
    sw(a3, a1, 16);
    sw(t1, a1, 20);
}

// 0x00590EF0 sub_590EF0 -- 224 bytes; frame 0x50: s0 sp+0x30, s1 sp+0x38, ra sp+0x40
// Once (flag +3436): converts the picture's time code to a time (sub_59A870) and keeps it as the first time code
//   (+3440, time at +3472 / +3476).
void sub_590EF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00590ef0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x30);
    sd(s1, sp, 0x38);
    s1 = a0;
    sd(ra, sp, 0x40);
    s0 = addiu(s1, 3436);
    lw(v0, s0, 0);
    a0 = sp;
    if (v0 == 0) {
        // 0x00590f14
        charge(ctx, 42);
        a1 = addiu(sp, 0x20);
        a2 = addiu(sp, 0x24);
        ldl(v0, s1, 3411);
        ldr(v0, s1, 3404);
        ldl(v1, s1, 3419);
        ldr(v1, s1, 3412);
        ldl(a3, s1, 3427);
        ldr(a3, s1, 3420);
        ldl(t0, s1, 3435);
        ldr(t0, s1, 3428);
        sdl(v0, sp, 0x7);
        sdr(v0, sp, 0x0);
        sdl(v1, sp, 0xF);
        sdr(v1, sp, 0x8);
        sdl(a3, sp, 0x17);
        sdr(a3, sp, 0x10);
        sdl(t0, sp, 0x1F);
        sdr(t0, sp, 0x18);
        link(ctx, 0x590F5Cu);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x18);
        call(ctx, gen::fn_sub_59A870_0059a870);
        lw(v0, sp, 0x20);
        v1 = 1;
        lw(a0, sp, 0x24);
        ldl(a1, sp, 0x7);
        ldr(a1, sp, 0x0);
        ldl(a2, sp, 0xF);
        ldr(a2, sp, 0x8);
        ldl(a3, sp, 0x17);
        ldr(a3, sp, 0x10);
        ldl(t0, sp, 0x1F);
        ldr(t0, sp, 0x18);
        sdl(a1, s1, 3447);
        sdr(a1, s1, 3440);
        sdl(a2, s1, 3455);
        sdr(a2, s1, 3448);
        sdl(a3, s1, 3463);
        sdr(a3, s1, 3456);
        sdl(t0, s1, 3471);
        sdr(t0, s1, 3464);
        sw(v1, s0, 0);
        sw(v0, s0, 36);
        sw(a0, s0, 40);
    }
    // 0x00590fbc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00590FD0 sub_590FD0 -- 324 bytes; frame 0x40: s0 sp+0x30, ra sp+0x38
// The latest time code: converts the picture's time code (sub_59A870) into the record at +3568 and, when its time is
//   at least the kept one (+3480 + 36), copies it there.
void sub_590FD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00590fd0
    enter(ctx, 55);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x30);
    s0 = a0;
    sd(ra, sp, 0x38);
    a1 = addiu(sp, 0x20);
    a0 = sp;
    ldl(v0, s0, 3411);
    ldr(v0, s0, 3404);
    ldl(v1, s0, 3419);
    ldr(v1, s0, 3412);
    ldl(a3, s0, 3427);
    ldr(a3, s0, 3420);
    ldl(t0, s0, 3435);
    ldr(t0, s0, 3428);
    sdl(v0, sp, 0x7);
    sdr(v0, sp, 0x0);
    sdl(v1, sp, 0xF);
    sdr(v1, sp, 0x8);
    sdl(a3, sp, 0x17);
    sdr(a3, sp, 0x10);
    sdl(t0, sp, 0x1F);
    sdr(t0, sp, 0x18);
    a2 = addiu(sp, 0x24);
    jal(ctx, 0x591028u, gen::fn_sub_59A870_0059a870);
    ldl(v0, sp, 0x7);
    ldr(v0, sp, 0x0);
    ldl(v1, sp, 0xF);
    ldr(v1, sp, 0x8);
    ldl(a0, sp, 0x17);
    ldr(a0, sp, 0x10);
    ldl(a1, sp, 0x1F);
    ldr(a1, sp, 0x18);
    sdl(v0, s0, 3579);
    sdr(v0, s0, 3572);
    sdl(v1, s0, 3587);
    sdr(v1, s0, 3580);
    sdl(a0, s0, 3595);
    sdr(a0, s0, 3588);
    sdl(a1, s0, 3603);
    sdr(a1, s0, 3596);
    v0 = addiu(s0, 3436);
    a2 = addiu(s0, 3568);
    s0 = addiu(s0, 3480);
    lw(a0, v0, 36);
    a1 = 1;
    lw(v1, sp, 0x20);
    lw(v0, sp, 0x24);
    v1 = subu(v1, a0);
    sw(a1, a2, 0);
    sw(v1, a2, 36);
    sw(v0, a2, 40);
    lw(v0, s0, 36);
    v1 = slt(v1, v0);
    if (v1 != 0) {
        ld(s0, sp, 0x30);
    } else {
        // 0x005910ac
        charge(ctx, 23);
        ldl(a3, a2, 7);
        ldr(a3, a2, 0);
        ldl(t0, a2, 15);
        ldr(t0, a2, 8);
        ldl(v0, a2, 23);
        ldr(v0, a2, 16);
        ldl(v1, a2, 31);
        ldr(v1, a2, 24);
        sdl(a3, s0, 7);
        sdr(a3, s0, 0);
        sdl(t0, s0, 15);
        sdr(t0, s0, 8);
        sdl(v0, s0, 23);
        sdr(v0, s0, 16);
        sdl(v1, s0, 31);
        sdr(v1, s0, 24);
        ldl(a3, a2, 39);
        ldr(a3, a2, 32);
        lw(t0, a2, 40);
        sdl(a3, s0, 39);
        sdr(a3, s0, 32);
        sw(t0, s0, 40);
        ld(s0, sp, 0x30);
    }
    // 0x00591108 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x00591118 sub_591118 -- 80 bytes; leaf frame (no stack)
// Copies the GOP time-code fields of an MPV picture info (rate, drop flag, h, m, s, f, the byte at +84) into a time-
//   code record; field count 0.
void sub_591118(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00591118
    enter(ctx, 20);  // entry check point + this block's cycles
    lw(v0, a0, 16);
    sw(v0, a1, 0);
    lw(v1, a0, 28);
    sw(v1, a1, 4);
    lw(v0, a0, 32);
    sw(v0, a1, 8);
    lw(v1, a0, 36);
    sw(v1, a1, 12);
    lw(v0, a0, 40);
    sw(v0, a1, 16);
    lw(v1, a0, 44);
    sw(v1, a1, 20);
    lw(a2, a0, 20);
    sw(a2, a1, 24);
    lbu(v0, a0, 84);
    sh(zero, a1, 30);
    v0 = sll(v0, 24);
    v0 = sra(v0, 24);
    sh(v0, a1, 28);
}

// 0x00591168 sub_591168 -- 300 bytes; frame 0x50: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s4 sp+0x30, s5 sp+0x38, s3 sp+0x28, ra sp+0x40
// After a picture header: the sequence size (sub_579240; error -16773354), the rates (sub_5792A0), the decode-delay
//   limit work+276 (param 60: the smaller of the VBV delay and sub_589510, else 0); then the header object's video
//   record (sub_591298), the sequence record (sub_5913B8) and the frame pool (sub_5913F0).
void sub_591168(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00591168
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0;
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a1;
    sd(s2, sp, 0x20);
    s2 = addiu(s0, 2316);
    sd(s4, sp, 0x30);
    s4 = a3;
    sd(s5, sp, 0x38);
    s5 = a2;
    sd(s3, sp, 0x28);
    a0 = s1;
    sd(ra, sp, 0x40);
    a1 = sp;
    lw(v1, s2, 16);
    lw(s3, s0, sfd::kVdecWork);
    if (v1 == 0) {
        // 0x005911b4
        charge(ctx, 4);
        jal(ctx, 0x5911B4u, gen::fn_sub_579240_00579240);
        a0 = s1;
        if (v0 == 0) {
            // 0x005911e0
            charge(ctx, 10);
            a1 = addiu(sp, 0x4);
            a2 = addiu(sp, 0x8);
            a3 = addiu(sp, 0xC);
            jal(ctx, 0x5911E8u, gen::fn_sub_5792A0_005792a0);
            a0 = s0;
            a1 = 60;
            jal(ctx, 0x5911F4u, gen::fn_sub_599408_00599408);
            a0 = s0;
            a1 = 1;
            if (v0 != 0) {
                // 0x00591210
                charge(ctx, 7);
                jal(ctx, 0x591210u, gen::fn_sub_589510_00589510);
                lw(v1, sp, 0xC);
                a0 = v0;
                v0 = si(-1);
                cc = v1 != v0;  // the condition, before the delay slot changes it
                v0 = slt(v1, a0);
                if (!cc) {
                    // 0x0059122c
                    charge(ctx, 3);
                    lw(v1, sp, 0x4);
                    sw(v1, sp, 0xC);
                    v0 = slt(v1, a0);
                }
                // 0x00591238
                charge(ctx, 2);
                if (v0 == 0) v1 = a0;
                sw(v1, s3, 276);
            } else {
                // 0x00591208
                charge(ctx, 2);
                sw(zero, s3, 276);
            }
            // 0x00591240
            charge(ctx, 12);
            lw(a1, sp, 0x0);
            a2 = s4;
            a0 = s0;
            jal(ctx, 0x591248u, gen::fn_sub_591298_00591298);
            a0 = s2;
            lw(a1, sp, 0x0);
            a2 = s5;
            link(ctx, 0x59125Cu);  // $ra first: the delay slot below depends on it
            lw(a3, sp, 0x4);
            call(ctx, gen::fn_sub_5913B8_005913b8);
            a0 = s0;
            a1 = s2;
            jal(ctx, 0x591268u, gen::fn_sub_5913F0_005913f0);
            goto L_00591270;
        }
        // 0x005911c4
        charge(ctx, 6);
        a1 = lui(0xFF00);
        a0 = s0;
        a1 = a1 | 0xF16;
        jal(ctx, 0x5911CCu, gen::fn_sub_58BE40_0058be40);
        ld(s0, sp, 0x10);
        // 0x00591274 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(s3, sp, 0x28);
        ld(s4, sp, 0x30);
        ld(s5, sp, 0x38);
        ld(ra, sp, 0x40);
        sp = addiu(sp, 0x50);
        return;
    }
L_00591270:
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    // 0x00591274 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00591298 sub_591298 -- 284 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Fills the header object's video record once (its word 0 still 0): the VBV size capped at 512, the sequence block
//   (sub_575410), the bit rate x 50 or 0 for the variable-rate marker 0x3FFFF, the first time code.
void sub_591298(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00591298
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    s3 = a0;
    jal(ctx, 0x5912B8u, gen::fn_sub_593700_00593700);
    s0 = v0;
    if (s0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005912cc
        charge(ctx, 3);
        lw(v0, s0, 0);
        if (v0 != 0) {
            ld(s0, sp, 0x0);
        } else {
            // 0x005912d8
            charge(ctx, 17);
            lw(a2, s2, 4);
            a3 = 512;
            v1 = addiu(s0, 56);
            lw(a1, s2, 0);
            v0 = slti(a2, 513);
            a0 = v1;
            if (v0 == 0) a2 = a3;
            s2 = addiu(s3, 3376);
            link(ctx, 0x5912F8u);  // $ra first: the delay slot below depends on it
            sw(a2, v1, 512);
            call(ctx, gen::fn_sub_575410_00575410);
            v1 = sll(s1, 1);
            v0 = 0x30000;
            v1 = addu(v1, s1);
            v1 = sll(v1, 3);
            v0 = v0 | 0xFFFF;
            v1 = addu(v1, s1);
            if (s1 != v0) {
                // 0x00591328
                charge(ctx, 4);
                v1 = sll(v1, 1);
                v0 = 1;
                sw(v0, s0, 8);
                sw(v1, s0, 4);
            } else {
                // 0x0059131c
                charge(ctx, 3);
                sw(zero, s0, 4);
                sw(zero, s0, 8);
            }
            // 0x00591338
            charge(ctx, 25);
            ldl(v0, s2, 67);
            ldr(v0, s2, 60);
            ldl(v1, s2, 75);
            ldr(v1, s2, 68);
            ldl(a0, s2, 83);
            ldr(a0, s2, 76);
            ldl(a1, s2, 91);
            ldr(a1, s2, 84);
            sdl(v0, s0, 19);
            sdr(v0, s0, 12);
            sdl(v1, s0, 27);
            sdr(v1, s0, 20);
            sdl(a0, s0, 35);
            sdr(a0, s0, 28);
            sdl(a1, s0, 43);
            sdr(a1, s0, 36);
            ldl(v0, s2, 99);
            ldr(v0, s2, 92);
            lw(v1, s2, 100);
            sdl(v0, s0, 51);
            sdr(v0, s0, 44);
            sw(v1, s0, 52);
            v0 = 1;
            sw(v0, s0, 0);
            ld(s0, sp, 0x0);
        }
    }
    // 0x0059139c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005913B8 sub_5913B8 -- 52 bytes; leaf frame (no stack)
// Stores the sequence record: width, height, the rate words, the byte count, the aspect.
void sub_5913B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x005913b8
    enter(ctx, 13);  // entry check point + this block's cycles
    lw(v1, a2, 0);
    lw(t0, a2, 16);
    sw(v1, a0, 0);
    lw(v0, a2, 4);
    sw(v0, a0, 4);
    lw(v1, a2, 8);
    sw(v1, a0, 8);
    lw(v0, a2, 12);
    sw(a3, a0, 32);
    sw(v0, a0, 12);
    sw(t0, a0, 20);
    sw(a1, a0, 16);
}

// 0x005913F0 sub_5913F0 -- 440 bytes; frame 0x10: ra sp+0x0
// The frame pool: the picture must fit the configured maximum (errors -16773353 / -16773352); frame size =
//   macroblocks x 1,024 (format 2) or x 384, + 64; carves the frame buffers from work+36 into work+48.., the count to
//   work+376, and resets the frame records (sub_592DD0).
void sub_5913F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005913f0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t5 = a0;
    sd(ra, sp, 0x0);
    lw(t4, t5, sfd::kVdecWork);
    lw(a3, a1, 4);
    t3 = addiu(t4, 4);
    lw(a2, a1, 0);
    lw(v0, t3, 8);
    lw(v1, t3, 12);
    mult(a1, a2, a3);
    lw(t6, t5, 56);
    mult(v0, v0, v1);
    v0 = slt(v0, a1);
    lw(t1, t3, 28);
    if (v0 != 0) {
        // 0x0059142c
        charge(ctx, 5);
        a1 = lui(0xFF00);
        ld(ra, sp, 0x0);
        a1 = a1 | 0xF17;
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00591440
    charge(ctx, 10);
    a1 = addiu(a2, 15);
    v1 = slti(a2, 0);
    v0 = slti(a3, 0);
    a0 = addiu(a3, 15);
    if (v1 != 0) a2 = a1;
    v1 = 2;
    if (v0 != 0) a3 = a0;
    a1 = sra(a2, 4);
    v0 = sra(a3, 4);
    if (t6 != v1) {
        // 0x00591478
        charge(ctx, 4);
        mult(v1, a1, v0);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 7);
    } else {
        // 0x00591468
        charge(ctx, 3);
        mult(v0, a1, v0);
        v0 = sll(v0, 10);
    }
    // 0x00591488
    charge(ctx, 13);
    t2 = addiu(v0, 64);
    lw(v1, t3, 20);
    t0 = 2;
    lw(v0, t3, 24);
    a3 = addiu(v1, 15);
    a1 = slti(v1, 0);
    a2 = addiu(v0, 15);
    a0 = slti(v0, 0);
    if (a1 != 0) v1 = a3;
    if (a0 != 0) v0 = a2;
    v1 = sra(v1, 4);
    v0 = sra(v0, 4);
    if (t6 == t0) {
        // 0x005914bc
        charge(ctx, 6);
        mult(v0, v1, v0);
        v0 = sll(v0, 10);
        v0 = addiu(v0, 64);
        v0 = sltu(v0, t2);
        if (v0 != 0) {
            goto L_00591500;
        }
        // 0x005914d4
        charge(ctx, 2);
        lw(v0, t3, 32);
        goto L_00591518;
    }
    // 0x005914e0
    charge(ctx, 8);
    mult(v1, v1, v0);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 7);
    v0 = addiu(v0, 64);
    v0 = sltu(v0, t2);
    if (v0 != 0) {
    L_00591500:
        charge(ctx, 6);
        a1 = lui(0xFF00);
        ld(ra, sp, 0x0);
        a0 = t5;
        a1 = a1 | 0xF18;
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    lw(v0, t3, 32);
L_00591518:
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x00591558
        charge(ctx, 2);
        if (i64(t1) <= 0) {
            sw(t1, t4, vdec::kFrameCount);
        } else {
            // 0x00591560
            charge(ctx, 2);
            a1 = t1;
            a1 = addiu(a1, -1);
            for (;;) {
                // 0x00591568
                charge(ctx, 7);
                cc = a1 != 0;  // the condition, before the delay slot changes it
                a1 = addiu(a1, -1);
                if (!cc) {
                    break;
                }
                backedge(ctx);
            }
        L_00591584:
            charge(ctx, 1);
            sw(t1, t4, vdec::kFrameCount);
        }
    } else {
        // 0x00591520
        charge(ctx, 2);
        a1 = 0;
        if (i64(t1) <= 0) {
            goto L_00591584;
        }
        // 0x00591528
        charge(ctx, 2);
        a0 = v0;
        v1 = addiu(t4, 48);
        for (;;) {
            // 0x00591530
            charge(ctx, 7);
            a1 = addiu(a1, 1);
            sw(a0, v1, 0);
            v0 = slt(a1, t1);
            v1 = addiu(v1, 4);
            a0 = addu(a0, t2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0059154c
        charge(ctx, 2);
        sw(t1, t4, vdec::kFrameCount);
    }
    // 0x00591588
    charge(ctx, 8);
    a1 = addiu(t4, 48);
    a2 = t1;
    a0 = addiu(t4, vdec::kFrames);
    jal(ctx, 0x591590u, gen::fn_sub_592DD0_00592dd0);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005915A8 sub_5915A8 -- 244 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s1 sp+0x8, ra sp+0x28
// Whether to decode the next picture: no when param 39 is set; the pending result when the skip byte (+228) is set;
//   otherwise the skip checks (sub_591808, sub_591858, sub_5918A8, sub_5916A0, sub_591988) and the decision's record
//   (sub_591700).
void sub_5915A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005915a8
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    s3 = 1;
    sd(s4, sp, 0x20);
    s4 = a1;
    sd(s1, sp, 0x8);
    a1 = 47;
    sd(ra, sp, 0x28);
    link(ctx, 0x5915D4u);  // $ra first: the delay slot below depends on it
    lw(s1, s0, sfd::kVdecWork);
    call(ctx, gen::fn_sub_599408_00599408);
    s2 = addiu(s1, 140);
    if (v0 != s3) {
        // 0x005915e4
        charge(ctx, 5);
        a0 = s0;
        a1 = 39;
        jal(ctx, 0x5915E8u, gen::fn_sub_599408_00599408);
        if (v0 != s3) {
            lb(v0, s2, 88);
            // 0x00591600
            charge(ctx, 2);
            a0 = s0;
            if (v0 == 0) {
                // 0x00591610
                charge(ctx, 4);
                link(ctx, 0x591610u);  // $ra first: the delay slot below depends on it
                lw(s1, s2, 24);
                call(ctx, gen::fn_sub_591808_00591808);
                s3 = 1;
                if (v0 == 0) {
                    // 0x00591620
                    charge(ctx, 5);
                    a0 = s0;
                    a1 = s1;
                    jal(ctx, 0x591624u, gen::fn_sub_591858_00591858);
                    a0 = s0;
                    if (v0 == 0) {
                        // 0x00591634
                        charge(ctx, 5);
                        a2 = s4;
                        a1 = s1;
                        jal(ctx, 0x591638u, gen::fn_sub_5918A8_005918a8);
                        a0 = s0;
                        if (v0 == 0) {
                            // 0x00591648
                            charge(ctx, 4);
                            a1 = s1;
                            jal(ctx, 0x591648u, gen::fn_sub_5916A0_005916a0);
                            if (v0 == 0) {
                                // 0x00591658
                                charge(ctx, 4);
                                a1 = s1;
                                a0 = s0;
                                jal(ctx, 0x59165Cu, gen::fn_sub_591988_00591988);
                                s3 = sltu(0, v0);
                                goto L_00591668;
                            }
                            a0 = s0;
                        }
                    }
                    goto L_0059166c;
                }
            L_00591668:
                charge(ctx, 1);
                a0 = s0;
            L_0059166c:
                charge(ctx, 4);
                a1 = s2;
                a2 = s3;
                jal(ctx, 0x591670u, gen::fn_sub_591700_00591700);
                v0 = s3;
            } else {
                // 0x00591608
                charge(ctx, 2);
                lw(v0, s1, 364);
            }
        } else {
            // 0x005915f8
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x0059167c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x005916A0 sub_5916A0 -- 92 bytes; leaf frame (no stack)
// Skip-mode check (work+116): mode 3 skips B pictures (type 3), mode 2 P and B (types 2..3).
void sub_5916A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005916a0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v0, a0, sfd::kVdecWork);
    a0 = a1;
    v1 = 3;
    a2 = 0;
    lw(a1, v0, 116);
    v0 = sltiu(a1, 4);
    if (a1 == v1) {
        // 0x005916e8
        charge(ctx, 2);
        v0 = a0 ^ a1;
        a2 = sltiu(v0, 1);
    L_005916f0:
        charge(ctx, 1);
        v0 = a2;
        // 0x005916f4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x005916bc
    charge(ctx, 2);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = a2;
    if (cc) {
        // 0x005916f4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x005916c4
    charge(ctx, 3);
    v0 = 2;
    cc = a1 != v0;  // the condition, before the delay slot changes it
    v0 = a2;
    if (cc) {
        // 0x005916f4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x005916d0
    charge(ctx, 4);
    v0 = addiu(a0, -2);
    v0 = sltiu(v0, 2);
    if (v0 != 0) {
        a2 = 1;
        goto L_005916f0;
    }
    // 0x005916e0
    charge(ctx, 2);
    v0 = a2;
}

// 0x00591858 sub_591858 -- 80 bytes; leaf frame (no stack)
// Whether the picture type's decoding is disabled: param 2 (I), 3 (P), 4 (B) zero; other types 1.
void sub_591858(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00591858
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 2;
    a0 = addiu(a0, 2572);
    if (a1 == v0) {
        // 0x00591898
        charge(ctx, 1);
        lw(v0, a0, 12);
    L_0059189c:
        charge(ctx, 1);
        v0 = sltiu(v0, 1);
        // 0x005918a0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x00591864
    charge(ctx, 3);
    v0 = sltiu(a1, 3);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 3;
    if (cc) {
        // 0x00591888
        charge(ctx, 2);
        if (a1 == v0) {
            lw(v0, a0, 16);
            goto L_0059189c;
        }
        // 0x00591890
        charge(ctx, 2);
        v0 = 1;
        return;
    }
    // 0x00591870
    charge(ctx, 3);
    v0 = 1;
    if (a1 == v0) {
        lw(v0, a0, 8);
        goto L_0059189c;
    }
    // 0x0059187c
    charge(ctx, 2);
    // 0x005918a0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00591C80 sub_591C80 -- 692 bytes; frame 0xA0: s4 sp+0x70, s6 sp+0x80, s7 sp+0x88, fp sp+0x90, s0 sp+0x50, s1 sp+0x58, s2 sp+0x60, s3 sp+0x68, s5 sp+0x78, ra sp+0x98
// Decodes one picture: a frame record and the output descriptor (sub_591F38), the reference sizes (sub_592240), the
//   user data (sub_592790), the display time code (sub_5922C8); decodes it (sub_595390) between two clock reads
//   (sub_59B3A8, profile sub_59B4B0), charges the bytes and errors (sub_58FF70 / sub_58FEC8); on success the frame's
//   user data, sizes and time, the pending-frame rotation (work+360), the frame state (2 or the reference state), and
//   the decode counter callback (sub_597100).
void sub_591C80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00591c80
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(s4, sp, 0x70);
    s4 = a0;
    sd(s6, sp, 0x80);
    s6 = addiu(s4, 2552);
    sd(s7, sp, 0x88);
    s7 = a1;
    sd(fp, sp, 0x90);
    v0 = addiu(s4, 2384);
    sd(s0, sp, 0x50);
    a2 = sp;
    sd(s1, sp, 0x58);
    a3 = addiu(sp, 0x30);
    sd(s2, sp, 0x60);
    sd(s3, sp, 0x68);
    sd(s5, sp, 0x78);
    sd(ra, sp, 0x98);
    lw(s3, s4, sfd::kVdecWork);
    sw(v0, sp, 0x3C);
    fp = addiu(s3, 0x8C);
    lw(v0, s3, 0);
    a1 = fp;
    link(ctx, 0x591CD8u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x40);
    call(ctx, gen::fn_sub_591F38_00591f38);
    if (v0 != 0) {
        v0 = 0;
    } else {
        // 0x00591ce8
        charge(ctx, 57);
        a2 = addiu(sp, 0x34);
        a3 = addiu(sp, 0x38);
        a0 = s4;
        a1 = s3;
        jal(ctx, 0x591CF4u, gen::fn_sub_592240_00592240);
        a1 = addiu(s3, 4236);
        lw(v0, sp, 0x30);
        link(ctx, 0x591D04u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 84);
        call(ctx, gen::fn_sub_592790_00592790);
        a0 = s4;
        jal(ctx, 0x591D0Cu, gen::fn_sub_5922C8_005922c8);
        jal(ctx, 0x591D14u, gen::fn_sub_59B3A8_0059b3a8);
        a0 = s7;
        a1 = 0;
        a2 = 1;
        s2 = v0;
        jal(ctx, 0x591D28u, gen::fn_sub_562E10_00562e10);
        a1 = s7;
        lw(a0, sp, 0x40);
        a2 = sp;
        a3 = s4;
        s0 = v0;
        jal(ctx, 0x591D40u, gen::fn_sub_595390_00595390);
        a0 = s7;
        a2 = 1;
        a1 = 0;
        s1 = v0;
        jal(ctx, 0x591D54u, gen::fn_sub_562E10_00562e10);
        s5 = subu(v0, s0);
        jal(ctx, 0x591D5Cu, gen::fn_sub_59B3A8_0059b3a8);
        lw(a0, fp, 0x18);
        a1 = v0 - s2;
        a0 = sll(a0, 5);
        a0 = addu(s4, a0);
        a0 = addiu(a0, 14016);
        jal(ctx, 0x591D74u, gen::fn_sub_59B4B0_0059b4b0);
        lw(v0, s6, 12);
        lw(a2, sp, 0x28);
        a3 = lui(0xFF00);
        lw(t0, sp, 0x2C);
        a1 = s1;
        lw(v1, s6, 16);
        v0 = addu(v0, a2);
        sw(v0, s6, 12);
        a0 = s4;
        v1 = addu(v1, t0);
        a2 = s5;
        sw(v1, s6, 16);
        a3 = a3 | 0xF06;
        jal(ctx, 0x591DACu, gen::fn_sub_58FF70_0058ff70);
        a0 = s4;
        s0 = v0;
        a1 = s5;
        jal(ctx, 0x591DBCu, gen::fn_sub_58FEC8_0058fec8);
        if (s0 == 0) {
            // 0x00591de0
            charge(ctx, 2);
            if (i64(s5) <= 0) {
                lw(v0, s3, 360);
                // 0x00591ef0
                charge(ctx, 2);
                if (v0 != 0) {
                    v0 = 0;
                } else {
                    // 0x00591ef8
                    charge(ctx, 3);
                    link(ctx, 0x591EF8u);  // $ra first: the delay slot below depends on it
                    lw(a0, sp, 0x30);
                    call(ctx, gen::fn_sub_593AA0_00593aa0);
                    v0 = 0;
                }
            } else {
                // 0x00591de8
                charge(ctx, 28);
                a1 = 0;
                a0 = s4;
                jal(ctx, 0x591DECu, gen::fn_sub_593968_00593968);
                a0 = s4;
                link(ctx, 0x591DF8u);  // $ra first: the delay slot below depends on it
                lw(a1, sp, 0x30);
                call(ctx, gen::fn_sub_5923E0_005923e0);
                a0 = s4;
                lw(a1, sp, 0x30);
                a2 = s7;
                jal(ctx, 0x591E08u, gen::fn_sub_592570_00592570);
                lw(a0, s3, 136);
                lw(v1, sp, 0x30);
                a3 = 3;
                lw(a2, fp, 0x38);
                sw(a0, v1, 72);
                lw(v1, sp, 0x34);
                lw(v0, sp, 0x28);
                lw(a1, s3, 372);
                lw(a0, sp, 0x30);
                v0 = addu(v0, v1);
                v0 = addu(v0, a1);
                sw(v0, a0, 64);
                lw(v1, sp, 0x2C);
                lw(v0, sp, 0x38);
                lw(a0, sp, 0x30);
                v1 = addu(v1, v0);
                sw(v1, a0, 68);
                if (a2 == a3) {
                    // 0x00591e70
                    charge(ctx, 1);
                    sw(zero, s3, 360);
                } else {
                    // 0x00591e58
                    charge(ctx, 3);
                    lw(v0, s3, 360);
                    if (v0 != 0) {
                        sw(zero, s3, 360);
                    } else {
                        // 0x00591e64
                        charge(ctx, 3);
                        lw(v0, sp, 0x30);
                        sw(v0, s3, 360);
                    }
                }
                // 0x00591e74
                charge(ctx, 4);
                lw(v0, s3, 360);
                sw(zero, s3, 364);
                sw(zero, s3, 368);
                if (v0 == 0) {
                    // 0x00591e84
                    charge(ctx, 4);
                    lw(v1, s4, 56);
                    v0 = 3;
                    if (v1 == v0) {
                        // 0x00591e94
                        charge(ctx, 5);
                        lw(v0, fp, 0x18);
                        v0 = addiu(v0, -1);
                        v0 = sltiu(v0, 2);
                        if (v0 == 0) {
                            goto L_00591eb8;
                        }
                        // 0x00591ea8
                        charge(ctx, 4);
                        link(ctx, 0x591EA8u);  // $ra first: the delay slot below depends on it
                        lw(a0, sp, 0x30);
                        call(ctx, gen::fn_sub_593AC8_00593ac8);
                        lw(v0, sp, 0x3C);
                        goto L_00591ec4;
                    }
                L_00591eb8:
                    charge(ctx, 3);
                    link(ctx, 0x591EB8u);  // $ra first: the delay slot below depends on it
                    lw(a0, sp, 0x30);
                    call(ctx, gen::fn_sub_593AB0_00593ab0);
                    lw(v0, sp, 0x3C);
                L_00591ec4:
                    charge(ctx, 5);
                    lw(a0, sp, 0x40);
                    a2 = addiu(v0, 12);
                    a1 = addiu(v0, 8);
                    jal(ctx, 0x591ECCu, gen::fn_sub_57B5B0_0057b5b0);
                    sw(zero, s3, 132);
                }
                // 0x00591ed8
                charge(ctx, 6);
                lw(a2, fp, 0x18);
                a0 = s4;
                a1 = 1;
                jal(ctx, 0x591EE0u, gen::fn_sub_597100_00597100);
                v0 = 0;
            }
        } else {
            // 0x00591dcc
            charge(ctx, 4);
            link(ctx, 0x591DCCu);  // $ra first: the delay slot below depends on it
            lw(a0, sp, 0x30);
            call(ctx, gen::fn_sub_593AA0_00593aa0);
            v0 = s0;
        }
    }
    // 0x00591f04 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x50);
    ld(s1, sp, 0x58);
    ld(s2, sp, 0x60);
    ld(s3, sp, 0x68);
    ld(s4, sp, 0x70);
    ld(s5, sp, 0x78);
    ld(s6, sp, 0x80);
    ld(s7, sp, 0x88);
    ld(fp, sp, 0x90);
    ld(ra, sp, 0x98);
    sp = addiu(sp, 0xA0);
}

// 0x00591F38 sub_591F38 -- 776 bytes; frame 0x40: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s0 sp+0x0, ra sp+0x30
// Takes the pending or a free frame record (sub_593A18; none: busy mark, -1), copies the 32-byte picture info into it
//   and its time; format 3 rotates the reference frames (the oldest released by sub_593B10; work+352 / +356) and
//   computes the Y / C plane addresses of the output descriptor; other formats flip the double buffer at work+320.
void sub_591F38(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00591f38
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = a0;
    sd(s4, sp, 0x20);
    s4 = a3;
    sd(s5, sp, 0x28);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x30);
    lw(s0, s3, sfd::kVdecWork);
    lw(v0, s0, 360);
    s5 = addiu(s3, 2384);
    if (v0 != 0) {
        // 0x00591f78
        charge(ctx, 2);
        sw(v0, s4, 0);
        goto L_00591fa0;
    }
    // 0x00591f80
    charge(ctx, 4);
    jal(ctx, 0x591F80u, gen::fn_sub_593A18_00593a18);
    sw(v0, s4, 0);
    if (v0 != 0) {
    L_00591fa0:
        charge(ctx, 7);
        lw(t2, s4, 0);
        v1 = s2;
        a0 = addiu(t2, 92);
        v0 = s2 | a0;
        v0 = v0 & 0x7;
        a1 = t2;
        if (v0 == 0) {
            // 0x00592020
            charge(ctx, 1);
            v0 = addiu(s2, 128);
            for (;;) {
                // 0x00592024
                charge(ctx, 13);
                ld(a2, v1, 0);
                ld(a3, v1, 8);
                ld(t0, v1, 16);
                ld(t1, v1, 24);
                sd(a2, a0, 0);
                sd(a3, a0, 8);
                sd(t0, a0, 16);
                sd(t1, a0, 24);
                v1 = addiu(v1, 32);
                a0 = addiu(a0, 32);
                if (v1 == v0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00592058
            charge(ctx, 1);
            ld(v0, s0, 4384);
        } else {
            // 0x00591fbc
            charge(ctx, 1);
            v0 = addiu(s2, 128);
            for (;;) {
                // 0x00591fc0
                charge(ctx, 21);
                ldl(a2, v1, 7);
                ldr(a2, v1, 0);
                ldl(a3, v1, 15);
                ldr(a3, v1, 8);
                ldl(t0, v1, 23);
                ldr(t0, v1, 16);
                ldl(t1, v1, 31);
                ldr(t1, v1, 24);
                sdl(a2, a0, 7);
                sdr(a2, a0, 0);
                sdl(a3, a0, 15);
                sdr(a3, a0, 8);
                sdl(t0, a0, 23);
                sdr(t0, a0, 16);
                sdl(t1, a0, 31);
                sdr(t1, a0, 24);
                v1 = addiu(v1, 32);
                a0 = addiu(a0, 32);
                if (v1 == v0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00592014
            charge(ctx, 2);
            ld(v0, s0, 4384);
        }
        // 0x0059205c
        charge(ctx, 4);
        v1 = 3;
        lw(a0, s3, 56);
        sd(v0, a1, 224);
        if (a0 != v1) {
            // 0x00592170
            charge(ctx, 5);
            lw(v0, s2, 24);
            v0 = addiu(v0, -1);
            v0 = sltiu(v0, 2);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            lw(v0, s0, 312);
            if (!cc) {
                // 0x00592184
                charge(ctx, 8);
                lw(v1, s0, 316);
                sw(a1, s0, 356);
                v0 = v0 ^ 0x1;
                v1 = v1 ^ 0x1;
                sw(v0, s0, 312);
                sw(v1, s0, 316);
                lw(t2, s4, 0);
                lw(v0, s0, 312);
            }
            // 0x005921a4
            charge(ctx, 22);
            a0 = addiu(s0, 320);
            lw(v1, s0, 316);
            v0 = sll(v0, 4);
            v0 = addu(v0, a0);
            v1 = sll(v1, 4);
            ldl(a1, v0, 7);
            ldr(a1, v0, 0);
            ldl(a2, v0, 15);
            ldr(a2, v0, 8);
            sdl(a1, s1, 7);
            sdr(a1, s1, 0);
            sdl(a2, s1, 15);
            v1 = addu(v1, a0);
            sdr(a2, s1, 8);
            ldl(t1, v1, 7);
            ldr(t1, v1, 0);
            ldl(v0, v1, 15);
            ldr(v0, v1, 8);
            sdl(t1, s1, 23);
            sdr(t1, s1, 16);
            sdl(v0, s1, 31);
            sdr(v0, s1, 24);
        } else {
            // 0x0059206c
            charge(ctx, 5);
            lw(v0, s2, 24);
            v0 = addiu(v0, -1);
            v0 = sltiu(v0, 2);
            if (v0 == 0) {
                lw(v1, s2, 0);
            } else {
                // 0x00592080
                charge(ctx, 3);
                lw(v0, s0, 360);
                if (v0 != 0) {
                    lw(v1, s2, 0);
                } else {
                    // 0x0059208c
                    charge(ctx, 8);
                    link(ctx, 0x59208Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, s0, 352);
                    call(ctx, gen::fn_sub_593B10_00593b10);
                    lw(v0, s0, 356);
                    sw(v0, s0, 352);
                    lw(v1, s4, 0);
                    sw(v1, s0, 356);
                    lw(t2, s4, 0);
                    lw(v1, s2, 0);
                }
            }
            // 0x005920ac
            charge(ctx, 48);
            lw(t0, s2, 4);
            v0 = addiu(v1, 15);
            v1 = addiu(v1, 30);
            a0 = slti(v0, 0);
            a1 = addiu(t0, 15);
            if (a0 != 0) v0 = v1;
            t1 = slti(a1, 0);
            v0 = sra(v0, 4);
            t0 = addiu(t0, 30);
            a0 = sll(v0, 4);
            v0 = sll(v0, 3);
            a3 = addiu(a0, 63);
            a0 = addiu(a0, 126);
            a2 = addiu(v0, 63);
            v0 = addiu(v0, 126);
            v1 = slti(a3, 0);
            if (t1 != 0) a1 = t0;
            if (v1 != 0) a3 = a0;
            v1 = slti(a2, 0);
            if (v1 != 0) a2 = v0;
            lw(v1, s0, 352);
            a3 = sra(a3, 6);
            a1 = sra(a1, 4);
            mult(v0, a3, a1);
            a3 = sll(a3, 6);
            a2 = sra(a2, 6);
            lw(a0, s0, 356);
            mult1(a1, a2, a1);
            a2 = sll(a2, 6);
            lw(t0, v1, 8);
            lw(t1, a0, 8);
            v0 = sll(v0, 10);
            sh(a3, s1, 30);
            a0 = addu(t1, v0);
            v0 = addu(t0, v0);
            a1 = sll(a1, 9);
            sh(a2, s1, 28);
            v1 = addu(a0, a1);
            a1 = addu(v0, a1);
            sw(a1, s1, 4);
            sw(v1, s1, 20);
            sh(a3, s1, 14);
            sh(a2, s1, 12);
            sw(t0, s1, 8);
            sw(v0, s1, 0);
            sw(t1, s1, 24);
            sw(a0, s1, 16);
        }
        // 0x005921fc
        charge(ctx, 8);
        lw(v1, t2, 8);
        a0 = addiu(t2, 92);
        sw(zero, s1, 44);
        v0 = 0;
        sw(zero, s1, 40);
        sw(v1, s1, 32);
        sw(a0, s1, 36);
        sw(zero, s5, 44);
    } else {
        // 0x00591f90
        charge(ctx, 4);
        v1 = 1;
        v0 = si(-1);
        sw(v1, s5, 44);
    }
    // 0x0059221c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00592240 sub_592240 -- 132 bytes; leaf frame (no stack)
// The reference frames' byte sizes for format 3: a P picture its forward frame's, a B picture both; else 0.
void sub_592240(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00592240
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(t0, a0, 56);
    v0 = 3;
    a0 = a1;
    if (t0 != v0) {
        // 0x005922b8
        charge(ctx, 1);
        sw(zero, a2, 0);
        // 0x005922bc (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sw(zero, a3, 0);
        return;
    }
    // 0x00592250
    charge(ctx, 4);
    lw(v1, a0, 164);
    v0 = 2;
    a1 = sltiu(v1, 3);
    if (v1 == v0) {
        // 0x00592278
        charge(ctx, 6);
        lw(v0, a0, 352);
        lw(v1, v0, 64);
        sw(v1, a2, 0);
        lw(a0, v0, 68);
        sw(a0, a3, 0);
        return;
    }
    // 0x00592260
    charge(ctx, 2);
    if (a1 != 0) {
        sw(zero, a2, 0);
        // 0x005922bc (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sw(zero, a3, 0);
        return;
    }
    // 0x00592268
    charge(ctx, 2);
    if (v1 != t0) {
        // 0x00592270
        charge(ctx, 2);
        sw(zero, a2, 0);
        // 0x005922bc (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sw(zero, a3, 0);
        return;
    }
    lw(a1, a0, 356);
    // 0x00592290
    charge(ctx, 10);
    lw(a0, a0, 352);
    lw(v1, a1, 64);
    lw(v0, a0, 64);
    v0 = addu(v0, v1);
    sw(v0, a2, 0);
    lw(v1, a0, 68);
    lw(v0, a1, 68);
    v1 = addu(v1, v0);
    sw(v1, a3, 0);
}

// 0x005922C8 sub_5922C8 -- 280 bytes; frame 0x50: s0 sp+0x30, s1 sp+0x38, s2 sp+0x40, ra sp+0x48
// Once (flag +3656): the display time code: the latest time code, its field count cleared unless the B type is
//   decoded, converted (sub_59A870), stored at +3660.
void sub_5922C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005922c8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x30);
    s0 = a0;
    sd(s1, sp, 0x38);
    s1 = addiu(s0, 3656);
    sd(s2, sp, 0x40);
    sd(ra, sp, 0x48);
    lw(v0, s1, 0);
    s2 = addiu(s0, 3436);
    if (v0 == 0) {
        // 0x005922f0
        charge(ctx, 21);
        ldl(v0, s0, 3579);
        ldr(v0, s0, 3572);
        ldl(v1, s0, 3587);
        ldr(v1, s0, 3580);
        ldl(a2, s0, 3595);
        ldr(a2, s0, 3588);
        ldl(a3, s0, 3603);
        ldr(a3, s0, 3596);
        sdl(v0, sp, 0x7);
        sdr(v0, sp, 0x0);
        sdl(v1, sp, 0xF);
        sdr(v1, sp, 0x8);
        sdl(a2, sp, 0x17);
        sdr(a2, sp, 0x10);
        sdl(a3, sp, 0x1F);
        sdr(a3, sp, 0x18);
        a1 = 3;
        jal(ctx, 0x592330u, gen::fn_sub_5916A0_005916a0);
        a0 = s0;
        a1 = 3;
        if (v0 == 0) {
            // 0x00592344
            charge(ctx, 5);
            jal(ctx, 0x592344u, gen::fn_sub_591858_00591858);
            lw(v1, sp, 0x18);
            if (v0 == 0) v1 = 0;
            sw(v1, sp, 0x18);
        }
        // 0x00592358
        charge(ctx, 28);
        a0 = sp;
        a1 = addiu(sp, 0x20);
        a2 = addiu(sp, 0x24);
        jal(ctx, 0x592360u, gen::fn_sub_59A870_0059a870);
        a1 = 1;
        ldl(v0, sp, 0x7);
        ldr(v0, sp, 0x0);
        ldl(v1, sp, 0xF);
        ldr(v1, sp, 0x8);
        ldl(a0, sp, 0x17);
        ldr(a0, sp, 0x10);
        ldl(a2, sp, 0x1F);
        ldr(a2, sp, 0x18);
        sdl(v0, s0, 3667);
        sdr(v0, s0, 3660);
        sdl(v1, s0, 3675);
        sdr(v1, s0, 3668);
        sdl(a0, s0, 3683);
        sdr(a0, s0, 3676);
        sdl(a2, s0, 3691);
        sdr(a2, s0, 3684);
        lw(v0, sp, 0x20);
        lw(v1, s2, 36);
        lw(a0, sp, 0x24);
        v0 = subu(v0, v1);
        sw(a1, s1, 0);
        sw(v0, s1, 36);
        sw(a0, s1, 40);
    }
    // 0x005923c8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x00592570 sub_592570 -- 168 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// The frame's user data: a reference picture keeps the work copy; the input's user-data block (sub_592618) of kind 3
//   is copied into the frame's buffer, otherwise the work copy is.
void sub_592570(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00592570
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s1, sp, 0x18);
    s1 = a2;
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x28);
    lw(v0, s0, 116);
    lw(s2, a0, sfd::kVdecWork);
    v0 = addiu(v0, -1);
    v0 = sltiu(v0, 2);
    a0 = addiu(s2, 4244);
    if (v0 != 0) {
        // 0x005925a4
        charge(ctx, 2);
        link(ctx, 0x5925A4u);  // $ra first: the delay slot below depends on it
        lw(a1, s0, 84);
        call(ctx, gen::fn_sub_592790_00592790);
    }
    // 0x005925ac
    charge(ctx, 9);
    a1 = sp;
    a0 = s1;
    a2 = addiu(sp, 0x4);
    a3 = addiu(sp, 0x8);
    jal(ctx, 0x5925B8u, gen::fn_sub_592618_00592618);
    lw(v0, sp, 0x0);
    v1 = 3;
    a1 = addiu(s2, 4244);
    if (v0 != v1) {
        // 0x005925f8
        charge(ctx, 2);
        link(ctx, 0x5925F8u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 84);
        call(ctx, gen::fn_sub_592790_00592790);
    } else {
        // 0x005925d0
        charge(ctx, 9);
        lw(v0, s0, 84);
        lw(a1, sp, 0x4);
        lw(a2, sp, 0x8);
        link(ctx, 0x5925DCu);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 0);
        call(ctx, gen::fn_memcpy_00521250);
        lw(v1, s0, 84);
        lw(v0, sp, 0x8);
        sw(v0, v1, 4);
    }
    // 0x00592600 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00592618 sub_592618 -- 372 bytes; frame 0x50: s0 sp+0x10, s1 sp+0x18, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, s2 sp+0x20, ra sp+0x40
// Finds the user-data block of the input chunk through the reader's get / release callbacks (+24 / +28): start-code
//   searches (sub_578160 / sub_577FC8), the kind from the table 0x7CA0D0, a miss counted in 0x7B47A4.
void sub_592618(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00592618
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    s1 = a1;
    sd(s3, sp, 0x28);
    s3 = a0;
    sd(s4, sp, 0x30);
    s4 = a2;
    sd(s5, sp, 0x38);
    s5 = a3;
    sd(s2, sp, 0x20);
    a2 = 0x7FFF0000;
    sd(ra, sp, 0x40);
    a3 = sp;
    sw(zero, s1, 0);
    a1 = 1;
    lw(v1, s3, 0);
    a2 = a2 | 0xFFFF;
    sw(zero, s4, 0);
    lw(v0, v1, 24);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x592668u);  // $ra = the return address
    sw(zero, s5, 0);
    call_ptr(ctx, jt);
    a2 = 204;
    lw(a0, sp, 0x0);
    link(ctx, 0x592678u);  // $ra first: the delay slot below depends on it
    lw(a1, sp, 0x4);
    call(ctx, gen::fn_sub_578160_00578160);
    s0 = v0;
    v1 = 0x7B0000;
    if (s0 != 0) {
        // 0x0059268c
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x59268Cu, gen::fn_sub_577FC8_00577fc8);
        v0 = v0 & 0x4;
        lw(a1, sp, 0x4);
        if (v0 == 0) {
        L_00592750:
            charge(ctx, 1);
            lw(v1, s3, 0);
        } else {
            // 0x005926a0
            charge(ctx, 6);
            lw(a2, sp, 0x0);
            v0 = subu(s0, a2);
            v0 = addiu(v0, 6);
            v0 = slt(a1, v0);
            v1 = 0x7B0000;
            if (v0 != 0) {
                goto L_00592730;
            }
            // 0x005926b8
            charge(ctx, 10);
            lbu(v0, s0, 5);
            a0 = 3;
            v0 = dsrl(v0, 3);
            v0 = v0 & 0x7;
            v0 = sll(v0, 2);
            v1 = 0x7D0000;
            v1 = addu(v1, v0);
            lw(v1, v1, -24368);
            sw(v1, s1, 0);
            if (v1 != a0) {
                goto L_00592750;
            }
            // 0x005926e0
            charge(ctx, 9);
            v0 = subu(a2, s0);
            a2 = 34;
            s2 = addu(v0, a1);
            a0 = s0;
            a1 = s2;
            jal(ctx, 0x5926F0u, gen::fn_sub_578160_00578160);
            s1 = v0;
            if (s1 != 0) {
                // 0x00592704
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x592704u, gen::fn_sub_577FC8_00577fc8);
                v0 = v0 & 0x20;
                a0 = s0;
                if (v0 != 0) {
                    // 0x00592718
                    charge(ctx, 5);
                    a1 = s2;
                    a2 = 2;
                    jal(ctx, 0x59271Cu, gen::fn_sub_578160_00578160);
                    cc = v0 != 0;  // the condition, before the delay slot changes it
                    v0 = subu(v0, s1);
                    if (!cc) {
                        // 0x0059272c
                        charge(ctx, 1);
                        v1 = 0x7B0000;
                        goto L_00592730;
                    }
                    // 0x00592748
                    charge(ctx, 2);
                    sw(s1, s4, 0);
                    sw(v0, s5, 0);
                }
                goto L_00592750;
            }
            lw(v1, s3, 0);
        }
        goto L_00592754;
    }
L_00592730:
    charge(ctx, 5);
    v1 = addiu(v1, 18340);
    lw(v0, v1, 0);
    v0 = addiu(v0, 1);
    sw(v0, v1, 0);
    goto L_00592750;
L_00592754:
    charge(ctx, 14);
    a0 = s3;
    a1 = 1;
    lw(v0, v1, 28);
    a2 = sp;
    jalr(ctx, 0x592760u, v0.u());
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00592790 sub_592790 -- 68 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Copies one {ptr, size} buffer into another (memcpy) and its size.
void sub_592790(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00592790
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    lw(a0, s1, 0);
    lw(a1, s0, 0);
    link(ctx, 0x5927B0u);  // $ra first: the delay slot below depends on it
    lw(a2, s0, 4);
    call(ctx, gen::fn_memcpy_00521250);
    lw(v1, s0, 4);
    ld(ra, sp, 0x10);
    sw(v1, s1, 4);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
}

// 0x00592958 sub_592958 -- 88 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// Adds the stream's consumed byte count (sub_5895F0 / sub_589D80) to the handle's 64-bit total (+2464).
void sub_592958(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00592958
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(ra, sp, 0x18);
    a2 = sp;
    link(ctx, 0x59296Cu);  // $ra first: the delay slot below depends on it
    lw(a1, s0, 8136);
    call(ctx, gen::fn_sub_5895F0_005895f0);
    lw(v0, sp, 0x0);
    a1 = addiu(sp, 0x4);
    a2 = addiu(sp, 0x8);
    a0 = v0;
    if (v0 != 0) {
        // 0x00592988
        charge(ctx, 6);
        jal(ctx, 0x592988u, gen::fn_sub_589D80_00589d80);
        ld(a0, s0, 2464);
        link(ctx, 0x592994u);  // $ra first: the delay slot below depends on it
        lw(a1, sp, 0x4);
        call(ctx, gen::fn_sub_589F38_00589f38);
        sd(v0, s0, 2464);
    }
    // 0x005929a0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005929B0 sub_5929B0 -- 348 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// Creates the video decoder of an SFD handle (when it has video): the work at +9128 (sub_592B10), the sceMpeg path
//   (sub_594C38), an MPV handle (sub_57B440; error -16773366) with the header callback 0x592EF8 (error -16773365),
//   the MPV params from params 0 / 1 and the format; restores the saved state (0x9ACB60..) in recreate mode.
void sub_5929B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005929b0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 5;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    s2 = addiu(s1, sfd::kVdecArea);
    jal(ctx, 0x5929CCu, gen::fn_sub_599408_00599408);
    a1 = s2;
    a0 = s1;
    if (v0 == 0) {
        // 0x00592af4 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x005929e0
    charge(ctx, 4);
    link(ctx, 0x5929E0u);  // $ra first: the delay slot below depends on it
    sw(s2, s1, sfd::kVdecWork);
    call(ctx, gen::fn_sub_592B10_00592b10);
    a0 = s1;
    if (v0 != 0) {
        // 0x00592af4 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x005929f0
    charge(ctx, 10);
    jal(ctx, 0x5929F0u, gen::fn_sub_594C38_00594c38);
    jal(ctx, 0x5929F8u, gen::fn_sub_57B440_0057b440);
    s0 = v0;
    a1 = 0x590000;
    a1 = addiu(a1, 12024);  // &sub_592EF8
    a0 = s0;
    a2 = s1;
    if (s0 == 0) {
        // 0x00592a18
        charge(ctx, 9);
        a1 = lui(0xFF00);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = 0;
        ld(s2, sp, 0x10);
        a1 = a1 | 0xF0A;
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00592a40
    charge(ctx, 4);
    jal(ctx, 0x592A40u, gen::fn_sub_578D98_00578d98);
    a1 = 0;
    if (v0 != 0) {
        // 0x00592a50
        charge(ctx, 11);
        a0 = s0;
        jal(ctx, 0x592A50u, gen::fn_sub_5930C8_005930c8);
        a0 = 0;
        a1 = lui(0xFF00);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a1 = a1 | 0xF0B;
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00592a80
    charge(ctx, 21);
    a0 = s1;
    jal(ctx, 0x592A80u, gen::fn_sub_599408_00599408);
    a0 = s0;
    a2 = v0;
    a1 = 1;
    jal(ctx, 0x592A90u, gen::fn_sub_57B648_0057b648);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x592A9Cu, gen::fn_sub_599408_00599408);
    a0 = s0;
    a1 = 2;
    a2 = v0;
    jal(ctx, 0x592AACu, gen::fn_sub_57B648_0057b648);
    a0 = s0;
    lw(a2, s1, 56);
    a1 = 6;
    jal(ctx, 0x592ABCu, gen::fn_sub_57B648_0057b648);
    link(ctx, 0x592AC4u);  // $ra first: the delay slot below depends on it
    sw(s0, s2, 0);
    call(ctx, gen::fn_sceInsockGetErrnoMode_1_00597438);
    a0 = s1;
    if (v0 != 0) {
        // 0x00592ad4
        charge(ctx, 7);
        v0 = 0x9B0000;
        v1 = 0x9B0000;
        lw(a1, v0, -13472);  // 0x9ACB60
        v0 = 0x9B0000;
        lw(a2, v1, -13468);  // 0x9ACB64
        link(ctx, 0x592AE8u);
        lw(a3, v0, -13464);
        gen::fn_sub_58E800_0058e800_at_0058e888(ctx);
    }
    // 0x00592af0
    charge(ctx, 1);
    v0 = 0;
    // 0x00592af4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00592B10 sub_592B10 -- 504 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Initialises the video work: validates and copies the saved configuration 0x9ACAF0.. (sub_592D08; error -16773355),
//   the defaults (+116 = 5, +120 = 192, ...), the 16 frame records (sub_592DD0), the decode-info and time-stamp
//   records.
void sub_592B10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00592b10
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a1;
    jal(ctx, 0x592B1Cu, gen::fn_sub_592D08_00592d08);
    ld(ra, sp, 0x8);
    if (v0 != 0) {
        // 0x00592b2c
        charge(ctx, 6);
        a1 = lui(0xFF00);
        ld(s0, sp, 0x0);
        a0 = 0;
        a1 = a1 | 0xF15;
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00592b48
    charge(ctx, 100);
    v0 = 0x9B0000;
    a0 = 0x9B0000;
    a3 = addiu(v0, -13584);  // &0x9ACAF0
    ldl(v1, a3, 7);  // 0x9ACAF7
    ldr(v1, a3, 0);  // 0x9ACAF0
    ldl(a1, a3, 15);  // 0x9ACAFF
    ldr(a1, a3, 8);  // 0x9ACAF8
    ldl(a2, a3, 23);  // 0x9ACB07
    ldr(a2, a3, 16);  // 0x9ACB00
    sdl(v1, s0, 11);
    sdr(v1, s0, 4);
    sdl(a1, s0, 19);
    sdr(a1, s0, 12);
    sdl(a2, s0, 27);
    sdr(a2, s0, 20);
    ldl(v1, a3, 31);  // 0x9ACB0F
    ldr(v1, a3, 24);  // 0x9ACB08
    lw(a1, a3, 32);  // 0x9ACB10
    sdl(v1, s0, 35);
    sdr(v1, s0, 28);
    sw(a1, s0, 36);
    v1 = addiu(s0, 48);
    a3 = 5;
    v0 = 0x9B0000;
    t3 = addiu(a0, -13544);  // &0x9ACB18
    ldl(t0, t3, 7);  // 0x9ACB1F
    ldr(t0, t3, 0);  // 0x9ACB18
    sdl(t0, s0, 47);
    sdr(t0, s0, 40);
    t0 = 192;
    t1 = 1;
    a1 = v1;
    t3 = addiu(v0, -13536);  // &0x9ACB20
    ldl(a0, t3, 7);  // 0x9ACB27
    ldr(a0, t3, 0);  // 0x9ACB20
    ldl(a2, t3, 15);  // 0x9ACB2F
    ldr(a2, t3, 8);  // 0x9ACB28
    ldl(t2, t3, 23);  // 0x9ACB37
    ldr(t2, t3, 16);  // 0x9ACB30
    sdl(a0, v1, 7);
    sdr(a0, v1, 0);
    sdl(a2, v1, 15);
    sdr(a2, v1, 8);
    sdl(t2, v1, 23);
    sdr(t2, v1, 16);
    ldl(a0, t3, 31);  // 0x9ACB3F
    ldr(a0, t3, 24);  // 0x9ACB38
    ldl(a2, t3, 39);  // 0x9ACB47
    ldr(a2, t3, 32);  // 0x9ACB40
    ldl(t2, t3, 47);  // 0x9ACB4F
    ldr(t2, t3, 40);  // 0x9ACB48
    sdl(a0, v1, 31);
    sdr(a0, v1, 24);
    sdl(a2, v1, 39);
    sdr(a2, v1, 32);
    sdl(t2, v1, 47);
    sdr(t2, v1, 40);
    ldl(a0, t3, 55);  // 0x9ACB57
    ldr(a0, t3, 48);  // 0x9ACB50
    ldl(a2, t3, 63);  // 0x9ACB5F
    ldr(a2, t3, 56);  // 0x9ACB58
    sdl(a0, v1, 55);
    sdr(a0, v1, 48);
    sdl(a2, v1, 63);
    sdr(a2, v1, 56);
    a2 = 16;
    sw(a3, s0, 116);
    a0 = addiu(s0, vdec::kFrames);
    sw(t0, s0, 120);
    sw(t1, s0, 316);
    sw(zero, s0, 0);
    sw(zero, s0, 112);
    sw(zero, s0, 312);
    sw(zero, s0, 124);
    sw(zero, s0, 128);
    sw(zero, s0, 352);
    sw(zero, s0, 356);
    sw(zero, s0, 360);
    sw(zero, s0, 364);
    sw(zero, s0, 368);
    link(ctx, 0x592C88u);  // $ra first: the delay slot below depends on it
    sw(zero, s0, 372);
    call(ctx, gen::fn_sub_592DD0_00592dd0);
    sw(zero, s0, 132);
    sw(zero, s0, 136);
    a0 = addiu(s0, 140);
    jal(ctx, 0x592C98u, gen::fn_sub_592E80_00592e80);
    v1 = si(-1);
    v0 = 0x7FFF0000;
    sw(v1, s0, 268);
    v0 = v0 | 0xFFFF;
    sw(zero, s0, 272);
    sw(v0, s0, 276);
    a0 = addiu(s0, 280);
    jal(ctx, 0x592CB8u, gen::fn_sub_590408_00590408);
    a0 = addiu(s0, 4224);
    jal(ctx, 0x592CC0u, gen::fn_sub_592EA0_00592ea0);
    a0 = 15;
    v0 = addiu(s0, 4372);
    v1 = addiu(s0, 4068);
    for (;;) {
        // 0x00592cd8
        charge(ctx, 7);
        a0 = addiu(a0, -1);
        sw(v0, v1, 0);
        v1 = addiu(v1, -240);
        v0 = addiu(v0, -8);
        if (i64(a0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00592cf4
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    v0 = 0;
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00592D08 sub_592D08 -- 196 bytes; leaf frame (no stack)
// Validates the saved video configuration: frame count 1..16, the frame buffers, the pointer tables.
void sub_592D08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00592d08
    enter(ctx, 7);  // entry check point + this block's cycles
    a1 = 0x9B0000;
    v1 = addiu(a1, -13584);  // &0x9ACAF0
    lw(v0, v1, 28);  // 0x9ACB0C
    v0 = addiu(v0, -1);
    v0 = sltiu(v0, 16);
    if (v0 == 0) {
        // 0x00592d24 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = si(-1);
        return;
    }
    lw(v0, v1, 16);  // 0x9ACB00
    // 0x00592d30
    charge(ctx, 2);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x9B0000;
    if (!cc) {
        // 0x00592d38
        charge(ctx, 3);
        lw(v0, v1, 32);
        if (v0 != 0) {
            // 0x00592dc4 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = 0;
            return;
        }
        // 0x00592d44
        charge(ctx, 1);
        v0 = 0x9B0000;
        goto L_00592d48;
    }
L_00592d48:
    charge(ctx, 4);
    v1 = 0;
    a0 = addiu(v0, -13544);
    lw(v0, a0, 0);
    for (;;) {
        // 0x00592d58
        charge(ctx, 2);
        a0 = addiu(a0, 4);
        if (v0 == 0) {
            backedge(ctx);
            // 0x00592d24 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = si(-1);
            return;
        }
        // 0x00592d60
        charge(ctx, 7);
        v1 = addiu(v1, 1);
        v0 = slti(v1, 2);
        if (v0 == 0) {
            break;
        }
        lw(v0, a0, 0);
        backedge(ctx);
    }
    // 0x00592d7c
    charge(ctx, 4);
    v0 = addiu(a1, -13584);
    lw(a0, v0, 28);
    v1 = 0;
    if (i64(a0) <= 0) {
        // 0x00592dc4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x00592d8c
    charge(ctx, 5);
    v0 = 0x9B0000;
    a1 = a0;
    a0 = addiu(v0, -13536);  // &0x9ACB20
    lw(v0, a0, 0);  // 0x9ACB20
    for (;;) {
        // 0x00592da0
        charge(ctx, 2);
        a0 = addiu(a0, 4);
        if (v0 == 0) {
            backedge(ctx);
            // 0x00592d24 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = si(-1);
            return;
        }
        // 0x00592da8
        charge(ctx, 7);
        v1 = addiu(v1, 1);
        v0 = slt(v1, a1);
        if (v0 == 0) {
            break;
        }
        lw(v0, a0, 0);
        backedge(ctx);
    }
    // 0x00592dc4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = 0;
}

// 0x00592DD0 sub_592DD0 -- 176 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// Resets n frame records (240 bytes): state 0, the buffer from the table, the time records (sub_599A30, sub_592E80),
//   +88 = -1.
void sub_592DD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00592dd0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    if (i64(a2) > 0) {
        // 0x00592df4
        charge(ctx, 5);
        s2 = a1;
        s1 = a2;
        s4 = 1;
        s3 = si(-1);
        for (;;) {
            // 0x00592e08
            charge(ctx, 22);
            sw(zero, s0, 0);
            a0 = addiu(s0, 12);
            sw(zero, s0, 4);
            a1 = 0;
            s1 = addiu(s1, -1);
            jal(ctx, 0x592E18u, gen::fn_sub_599A30_00599a30);
            lw(v0, s2, 0);
            sw(zero, s0, 56);
            a0 = addiu(s0, 92);
            sw(v0, s0, 8);
            s2 = addiu(s2, 4);
            sw(s4, s0, 60);
            sw(zero, s0, 64);
            sw(zero, s0, 68);
            sw(zero, s0, 72);
            sw(zero, s0, 76);
            sw(zero, s0, 80);
            link(ctx, 0x592E4Cu);  // $ra first: the delay slot below depends on it
            sw(s3, s0, 88);
            call(ctx, gen::fn_sub_592E80_00592e80);
            sw(zero, s0, 232);
            s0 = addiu(s0, 240);
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00592e60 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00592E80 sub_592E80 -- 28 bytes; frame 0x10: ra sp+0x0
// Fills 32 words with -1 (sub_575880).
void sub_592E80(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00592e80
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = si(-1);
    sd(ra, sp, 0x0);
    a2 = 32;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_575880_00575880(ctx);  // tail call
}

// 0x00592EA0 sub_592EA0 -- 84 bytes; leaf frame (no stack)
// Clears a record of 7 words and 16 word pairs.
void sub_592EA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00592ea0
    enter(ctx, 12);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    a1 = 16;
    sw(zero, a0, 4);
    t0 = addiu(a0, 16);
    sw(zero, a0, 8);
    a3 = addiu(a0, 12);
    sw(zero, a0, 12);
    a2 = 15;
    sw(zero, a0, 16);
    sw(zero, a0, 20);
    sw(zero, a0, 24);
    for (;;) {
        // 0x00592ed0
        charge(ctx, 7);
        v0 = addu(a3, a1);
        v1 = addu(t0, a1);
        a2 = addiu(a2, -1);
        sw(zero, v0, 0);
        sw(zero, v1, 0);
        a1 = addiu(a1, 8);
        if (i64(a2) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00592eec
    charge(ctx, 2);
}

// 0x00592F38 sub_592F38 -- 396 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// Destroys the video decoder: saves the configuration into 0x9ACAF0.. and 0x9ACB60.., releases the sceMpeg path
//   (sub_595060), the MPV handle (sub_5930C8; error -16773364).
void sub_592F38(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00592f38
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    lw(s0, s2, sfd::kVdecWork);
    lw(s1, s0, 0);
    v0 = 0;
    if (s1 == 0) {
        // 0x005930ac (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00592f60
    charge(ctx, 75);
    v0 = 0x9B0000;
    v1 = 0x9B0000;
    t4 = addiu(v0, -13584);  // &0x9ACAF0
    ldl(t1, s0, 11);
    ldr(t1, s0, 4);
    ldl(t2, s0, 19);
    ldr(t2, s0, 12);
    ldl(t3, s0, 27);
    ldr(t3, s0, 20);
    sdl(t1, t4, 7);  // 0x9ACAF7
    sdr(t1, t4, 0);  // 0x9ACAF0
    sdl(t2, t4, 15);  // 0x9ACAFF
    sdr(t2, t4, 8);  // 0x9ACAF8
    sdl(t3, t4, 23);  // 0x9ACB07
    sdr(t3, t4, 16);  // 0x9ACB00
    ldl(t1, s0, 35);
    ldr(t1, s0, 28);
    lw(t2, s0, 36);
    sdl(t1, t4, 31);  // 0x9ACB0F
    sdr(t1, t4, 24);  // 0x9ACB08
    sw(t2, t4, 32);  // 0x9ACB10
    a1 = 0x9B0000;
    a2 = 0x9B0000;
    a3 = 0x9B0000;
    t3 = addiu(v1, -13544);  // &0x9ACB18
    ldl(v0, s0, 47);
    ldr(v0, s0, 40);
    sdl(v0, t3, 7);  // 0x9ACB1F
    sdr(v0, t3, 0);  // 0x9ACB18
    t0 = 0x9B0000;
    t1 = addiu(a1, -13536);  // &0x9ACB20
    ldl(t4, s0, 55);
    ldr(t4, s0, 48);
    ldl(v0, s0, 63);
    ldr(v0, s0, 56);
    ldl(v1, s0, 71);
    ldr(v1, s0, 64);
    sdl(t4, t1, 7);  // 0x9ACB27
    sdr(t4, t1, 0);  // 0x9ACB20
    sdl(v0, t1, 15);  // 0x9ACB2F
    sdr(v0, t1, 8);  // 0x9ACB28
    sdl(v1, t1, 23);  // 0x9ACB37
    sdr(v1, t1, 16);  // 0x9ACB30
    ldl(t4, s0, 79);
    ldr(t4, s0, 72);
    ldl(v0, s0, 87);
    ldr(v0, s0, 80);
    ldl(v1, s0, 95);
    ldr(v1, s0, 88);
    sdl(t4, t1, 31);  // 0x9ACB3F
    sdr(t4, t1, 24);  // 0x9ACB38
    sdl(v0, t1, 39);  // 0x9ACB47
    sdr(v0, t1, 32);  // 0x9ACB40
    sdl(v1, t1, 47);  // 0x9ACB4F
    sdr(v1, t1, 40);  // 0x9ACB48
    ldl(t4, s0, 103);
    ldr(t4, s0, 96);
    ldl(v0, s0, 111);
    ldr(v0, s0, 104);
    sdl(t4, t1, 55);  // 0x9ACB57
    sdr(t4, t1, 48);  // 0x9ACB50
    sdl(v0, t1, 63);  // 0x9ACB5F
    sdr(v0, t1, 56);  // 0x9ACB58
    lw(v0, s0, 4224);
    sw(v0, a2, -13472);  // 0x9ACB60
    lw(v1, s0, 4228);
    sw(v1, a3, -13468);  // 0x9ACB64
    lw(v0, s0, 4232);
    link(ctx, 0x593070u);  // $ra first: the delay slot below depends on it
    sw(v0, t0, -13464);
    call(ctx, gen::fn_sub_595060_00595060);
    a0 = s1;
    jal(ctx, 0x593078u, gen::fn_sub_5930C8_005930c8);
    a1 = lui(0xFF00);
    a0 = s2;
    if (v0 != 0) {
        // 0x0059308c
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        a1 = a1 | 0xF0C;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x005930a8
    charge(ctx, 1);
    sw(zero, s0, 0);
    // 0x005930ac (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005930C8 sub_5930C8 -- 20 bytes; frame 0x10: ra sp+0x0
// Destroys an MPV handle (sub_57B5C8).
void sub_5930C8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005930c8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_57B5C8_0057b5c8(ctx);  // tail call
}

// 0x00593200 sub_593200 -- 520 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s1 sp+0x8, ra sp+0x20
// Fills a frame's output record for the application from the frame record: buffers, sizes, format, times and the
//   picture bytes.
void sub_593200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00593200
    enter(ctx, 52);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x20);
    link(ctx, 0x593224u);  // $ra first: the delay slot below depends on it
    lw(s1, s0, sfd::kVdecWork);
    call(ctx, gen::fn_sub_593900_00593900);
    t2 = 1;
    t1 = addiu(s3, 92);
    sw(t2, v0, 0);
    t0 = addiu(v0, 8);
    lw(v1, t1, 24);
    lw(v0, t1, 0);
    sw(v1, t0, 16);
    sw(v0, t0, 0);
    lw(a2, s0, 56);
    lw(v0, t1, 4);
    lw(a0, s3, 8);
    sw(v0, t0, 4);
    lw(a1, s3, 84);
    lw(v0, t1, 8);
    lw(a3, t1, 64);
    sw(v0, t0, 8);
    sw(s3, s1, 112);
    lw(v0, t1, 12);
    sw(a2, t0, 28);
    sw(v0, t0, 12);
    sw(a0, t0, 32);
    lw(v0, s3, 56);
    sw(a1, t0, 56);
    sw(v0, t0, 20);
    sw(t0, s2, 0);
    lw(v0, s3, 60);
    sw(v0, t0, 24);
    lw(v1, s3, 64);
    sw(v1, t0, 36);
    lw(v0, s3, 68);
    sw(v0, t0, 40);
    lw(v1, s3, 72);
    sw(v1, t0, 44);
    lw(v0, s3, 76);
    sw(v0, t0, 48);
    lw(v1, s3, 80);
    sw(v1, t0, 52);
    lw(v0, t1, 68);
    sw(a3, t0, 60);
    sw(v0, t0, 64);
    if (a3 != 0) {
        // 0x005932e0
        charge(ctx, 1);
        sw(t2, t0, 72);
    } else {
        // 0x005932d0
        charge(ctx, 3);
        v0 = 2;
        sw(v0, t0, 72);
    }
    // 0x005932e4
    charge(ctx, 73);
    ld(v1, s3, 224);
    lw(v0, s2, 0);
    sd(v1, v0, 80);
    lw(a0, s2, 0);
    lw(v0, t1, 56);
    sw(v0, a0, 88);
    lw(v1, s2, 0);
    lw(v0, t1, 60);
    sw(v0, v1, 92);
    lw(a0, s2, 0);
    lw(v0, t1, 72);
    sw(v0, a0, 96);
    lw(v1, s2, 0);
    lw(v0, t1, 76);
    sw(v0, v1, 100);
    lw(a0, s2, 0);
    lhu(v0, t1, 80);
    sh(v0, a0, 104);
    lw(v1, s2, 0);
    lhu(v0, t1, 82);
    sh(v0, v1, 106);
    lw(a0, s2, 0);
    lbu(v0, t1, 85);
    sb(v0, a0, 108);
    lw(v1, s2, 0);
    lbu(v0, t1, 86);
    sb(v0, v1, 109);
    lw(a0, s2, 0);
    lbu(v0, t1, 87);
    sb(v0, a0, 110);
    lw(v1, s2, 0);
    lbu(v0, t1, 89);
    sb(v0, v1, 111);
    lw(a0, s2, 0);
    lbu(v0, t1, 90);
    sb(v0, a0, 112);
    lw(v1, s2, 0);
    lbu(v0, t1, 91);
    ld(s0, sp, 0x0);
    sb(v0, v1, 113);
    ld(s1, sp, 0x8);
    lw(a0, s2, 0);
    lbu(v0, t1, 92);
    ld(s3, sp, 0x18);
    sb(v0, a0, 114);
    ld(ra, sp, 0x20);
    lw(v1, s2, 0);
    lbu(v0, t1, 93);
    sb(v0, v1, 115);
    lw(a0, s2, 0);
    lbu(v0, t1, 94);
    sb(v0, a0, 116);
    lw(v1, s2, 0);
    lbu(v0, t1, 95);
    sb(v0, v1, 117);
    lw(a0, s2, 0);
    lbu(v0, t1, 96);
    sb(v0, a0, 118);
    lw(v1, s2, 0);
    lbu(v0, t1, 97);
    sb(v0, v1, 119);
    lw(a0, s2, 0);
    lbu(v0, t1, 98);
    sb(v0, a0, 120);
    lw(v1, s2, 0);
    lbu(v0, t1, 99);
    sb(v0, v1, 121);
    lw(a0, s2, 0);
    lbu(v0, t1, 100);
    ld(s2, sp, 0x10);
    sb(v0, a0, 122);
    sp = addiu(sp, 0x30);
}

// 0x00593468 sub_593468 -- 292 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Releases a frame given by the application (by output record or by frame); errors -16773345 / -16773362 / -16773361.
void sub_593468(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00593468
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 2;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    lw(v0, s0, 88);
    lw(s3, s0, sfd::kVdecWork);
    if (v0 == v1) {
        // 0x00593498
        charge(ctx, 6);
        a1 = a2;
        jal(ctx, 0x593498u, gen::fn_sub_5938C0_005938c0);
        s1 = v0;
        a1 = lui(0xFF00);
        a0 = s0;
        if (s1 != 0) {
            // 0x005934d0
            charge(ctx, 4);
            a1 = s1;
            jal(ctx, 0x5934D0u, gen::fn_sub_593900_00593900);
            s2 = v0;
            goto L_00593560;
        }
        // 0x005934b0
        charge(ctx, 8);
        ld(s0, sp, 0x0);
        a1 = a1 | 0xF1F;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x005934e0
    charge(ctx, 9);
    jal(ctx, 0x5934E0u, gen::fn_sub_593590_00593590);
    v1 = 1;
    s2 = v0;
    a1 = lui(0xFF00);
    lw(v0, s2, 0);
    a0 = s0;
    a1 = a1 | 0xF0E;
    if (v0 != v1) {
        // 0x00593504
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00593520
    charge(ctx, 8);
    a1 = s1;
    jal(ctx, 0x593520u, gen::fn_sub_593878_00593878);
    a0 = s0;
    s1 = v0;
    lw(v0, s3, 112);
    a1 = lui(0xFF00);
    a1 = a1 | 0xF0F;
    if (v0 != s1) {
        // 0x00593540
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
L_00593560:
    charge(ctx, 11);
    sw(zero, s2, 0);
    a0 = s1;
    jal(ctx, 0x593564u, gen::fn_sub_593AE0_00593ae0);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00593590 sub_593590 -- 8 bytes; leaf frame (no stack)
// An output record's header: a1 - 8.
void sub_593590(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5};
    // 0x00593590
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = addiu(a1, -8);
}

// 0x00593700 sub_593700 -- 48 bytes; leaf frame (no stack)
// The header object's video record (+2768) while no picture was decoded, else 0.
void sub_593700(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00593700
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, a0, sfd::kHdrObj);
    v0 = 0;
    lw(a0, a0, sfd::kVdecWork);
    a1 = addiu(v1, 2768);
    if (v1 != 0) {
        // 0x00593714
        charge(ctx, 5);
        lw(v0, a0, 136);
        v1 = 0;
        v1 = slt(v1, v0);
        v0 = 0;
        if (v1 == 0) v0 = a1;
    }
    // 0x00593728 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00593878 sub_593878 -- 72 bytes; leaf frame (no stack)
// The frame record (work+384 + 240 i) whose output record (handle+5816 + 136 i) is a1; 0 when none of 16.
void sub_593878(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00593878
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, sfd::kVdecWork);
    a0 = addiu(a0, 5808);
    a3 = 0;
    a2 = addiu(v0, vdec::kFrames);
    v1 = addiu(a0, 8);
    for (;;) {
        // 0x00593890
        charge(ctx, 4);
        a0 = addiu(a0, 136);
        v0 = a2;
        a2 = addiu(a2, 240);
        if (v1 == a1) {
            break;
        }
        // 0x005938a0
        charge(ctx, 5);
        a3 = addiu(a3, 1);
        v0 = slti(a3, 16);
        v1 = addiu(a0, 8);
        if (v0 == 0) {
            goto L_005938b4_3;
        }
        backedge(ctx);
    }
    // 0x005938b8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_005938b4_3:
    charge(ctx, 1);
    v0 = 0;
    // 0x005938b8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00593900 sub_593900 -- 72 bytes; leaf frame (no stack)
// The output record (handle+5808 + 136 i) of frame record a1; 0 when none.
void sub_593900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00593900
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, sfd::kVdecWork);
    a3 = 0;
    lw(a2, v0, vdec::kFrameCount);
    v1 = addiu(v0, vdec::kFrames);
    if (i64(a2) > 0) {
        // 0x00593914
        charge(ctx, 1);
        a0 = addiu(a0, 5808);
        for (;;) {
            // 0x00593918
            charge(ctx, 3);
            v0 = a0;
            a0 = addiu(a0, 136);
            if (v1 == a1) {
                break;
            }
            // 0x00593924
            charge(ctx, 6);
            a3 = addiu(a3, 1);
            v0 = slt(a3, a2);
            v1 = addiu(v1, 240);
            if (v0 == 0) {
                goto L_0059393c;
            }
            backedge(ctx);
        }
        // 0x00593940 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0059393c:
    charge(ctx, 1);
    v0 = 0;
    // 0x00593940 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00593958 sub_593958 -- 12 bytes; leaf frame (no stack)
// work+124 (the end mark).
void sub_593958(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00593958
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, sfd::kVdecWork);
    lw(v0, v1, 124);
}

// 0x00593968 sub_593968 -- 12 bytes; leaf frame (no stack)
// work+128 = a1.
void sub_593968(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00593968
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, sfd::kVdecWork);
    sw(a1, v0, 128);
}

// 0x00593978 sub_593978 -- 160 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// Under the lock: the number of decoded frames (state 2 or 4) not yet shown (+88 = -1); -1 when none and the end mark
//   is 1.
void sub_593978(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00593978
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(ra, sp, 0x18);
    a0 = sp;
    jal(ctx, 0x593988u, gen::fn_sub_58C100_0058c100);
    lw(a2, s0, sfd::kVdecWork);
    s0 = 0;
    lw(v0, a2, vdec::kFrameCount);
    a0 = addiu(a2, vdec::kFrames);
    if (i64(v0) > 0) {
        // 0x005939a4
        charge(ctx, 5);
        a1 = v0;
        t1 = 2;
        t0 = 4;
        a3 = si(-1);
        for (;;) {
            // 0x005939b8
            charge(ctx, 3);
            lw(v0, a0, 0);
            if (v0 == t1) {
                lw(v0, a0, 88);
            } else {
                // 0x005939c4
                charge(ctx, 2);
                if (v0 == t0) {
                    // 0x005939cc
                    charge(ctx, 1);
                    lw(v0, a0, 88);
                    goto L_005939d0;
                }
                a1 = addiu(a1, -1);
                goto L_005939e0;
            }
        L_005939d0:
            charge(ctx, 4);
            v1 = addiu(s0, 1);
            v0 = v0 ^ a3;
            if (v0 == 0) s0 = v1;
            a1 = addiu(a1, -1);
        L_005939e0:
            charge(ctx, 2);
            a0 = addiu(a0, 240);
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x005939e8
    charge(ctx, 4);
    lw(v1, a2, 124);
    v0 = 1;
    cc = v1 != v0;  // the condition, before the delay slot changes it
    v0 = si(-1);
    if (!cc) {
        // 0x005939f8
        charge(ctx, 1);
        if (s0 == 0) s0 = v0;
    }
    // 0x005939fc
    charge(ctx, 7);
    a0 = sp;
    jal(ctx, 0x5939FCu, gen::fn_sub_58C118_0058c118);
    v0 = s0;
    ld(ra, sp, 0x18);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00593A18 sub_593A18 -- 136 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// Under the lock: takes a free frame record (state 0 -> 1); 0 when all are in use.
void sub_593A18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00593a18
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(ra, sp, 0x18);
    a0 = sp;
    jal(ctx, 0x593A28u, gen::fn_sub_58C100_0058c100);
    lw(v0, s0, sfd::kVdecWork);
    v1 = 0;
    lw(a0, v0, vdec::kFrameCount);
    s0 = addiu(v0, vdec::kFrames);
    if (i64(a0) > 0) {
        // 0x00593a44
        charge(ctx, 2);
        ld(v0, s0, 0);
        for (;;) {
            // 0x00593a60
            charge(ctx, 5);
            if (v0 == 0) {
                goto L_00593a74_5;
            }
            v1 = addiu(v1, 1);
            backedge(ctx);
            // 0x00593a50
            charge(ctx, 3);
            v0 = slt(v1, a0);
            s0 = addiu(s0, 240);
            if (v0 != 0) {
                // 0x00593a5c
                charge(ctx, 1);
                ld(v0, s0, 0);
                continue;
            }
            break;
        }
    }
L_00593a7c:
    charge(ctx, 9);
    v0 = v1 ^ a0;
    a0 = sp;
    if (v0 == 0) s0 = 0;
    jal(ctx, 0x593A84u, gen::fn_sub_58C118_0058c118);
    ld(ra, sp, 0x18);
    v0 = s0;
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x20);
    return;
L_00593a74_5:
    charge(ctx, 2);
    v0 = 1;
    sw(v0, s0, 0);
    goto L_00593a7c;
}

// 0x00593AB0 sub_593AB0 -- 20 bytes; leaf frame (no stack)
// Marks a frame decoded (state 2).
void sub_593AB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00593ab0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 2;
    if (a0 != 0) {
        // 0x00593ab8
        charge(ctx, 1);
        sw(v0, a0, 0);
    }
    // 0x00593abc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00593AE0 sub_593AE0 -- 44 bytes; leaf frame (no stack)
// Marks a frame shown: state 4 -> 3, else 0; +88 = -1.
void sub_593AE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00593ae0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 4;
    if (a0 != 0) {
        // 0x00593ae8
        charge(ctx, 3);
        lw(v1, a0, 0);
        if (v1 != v0) {
            sw(zero, a0, 0);
        } else {
            // 0x00593af4
            charge(ctx, 2);
            v0 = 3;
            sw(v0, a0, 0);
        }
        // 0x00593afc
        charge(ctx, 2);
        v0 = si(-1);
        sw(v0, a0, 88);
    }
    // 0x00593b04 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00593B38 sub_593B38 -- 188 bytes; frame 0x50: s0 sp+0x10, s2 sp+0x20, s1 sp+0x18, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, ra sp+0x40
// Under the lock: the oldest (smallest time) decoded frame not yet shown.
void sub_593B38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00593b38
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x10);
    s0 = a0;
    a0 = sp;
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x18);
    sd(s3, sp, 0x28);
    sd(s4, sp, 0x30);
    sd(s5, sp, 0x38);
    sd(ra, sp, 0x40);
    s2 = 0;
    jal(ctx, 0x593B60u, gen::fn_sub_58C100_0058c100);
    lw(v0, s0, sfd::kVdecWork);
    lw(v1, v0, vdec::kFrameCount);
    s0 = addiu(v0, vdec::kFrames);
    if (i64(v1) > 0) {
        // 0x00593b78
        charge(ctx, 4);
        s1 = v1;
        s5 = 2;
        s4 = 4;
        s3 = si(-1);
        for (;;) {
            // 0x00593b88
            charge(ctx, 3);
            lw(v0, s0, 0);
            if (v0 == s5) {
                lw(v0, s0, 88);
            } else {
                // 0x00593b94
                charge(ctx, 2);
                if (v0 == s4) {
                    // 0x00593b9c
                    charge(ctx, 1);
                    lw(v0, s0, 88);
                    goto L_00593ba0;
                }
                s1 = addiu(s1, -1);
                goto L_00593bbc;
            }
        L_00593ba0:
            charge(ctx, 2);
            if (v0 != s3) {
                s1 = addiu(s1, -1);
            } else {
                // 0x00593ba8
                charge(ctx, 5);
                a0 = s2;
                a1 = s0;
                jal(ctx, 0x593BACu, gen::fn_sub_593FB0_00593fb0);
                if (v0 != 0) s2 = s0;
                s1 = addiu(s1, -1);
            }
        L_00593bbc:
            charge(ctx, 2);
            s0 = addiu(s0, 240);
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00593bc4
    charge(ctx, 12);
    a0 = sp;
    jal(ctx, 0x593BC4u, gen::fn_sub_58C118_0058c118);
    v0 = s2;
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00593DB0 sub_593DB0 -- 84 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Get-frame entry: handle check (sub_58C060; error -16776829), then sub_593E08.
void sub_593DB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00593db0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x593DBCu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = s0;
    a1 = a1 | 0x183;
    if (v0 == 0) {
        // 0x00593de8
        charge(ctx, 3);
        jal(ctx, 0x593DE8u, gen::fn_sub_593E08_00593e08);
        v0 = sltu(0, v0);
    } else {
        // 0x00593dd4
        charge(ctx, 4);
        a0 = 0;
        jal(ctx, 0x593DD4u, gen::fn_sub_58BE40_0058be40);
        v0 = 0;
    }
    // 0x00593df4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00593E08 sub_593E08 -- 152 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// Under the lock: while playing (status 4), the oldest decoded frame (sub_593EA0) when its time is due (param 15,
//   sub_59AEC0).
void sub_593E08(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00593e08
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(ra, sp, 0x18);
    a0 = sp;
    jal(ctx, 0x593E18u, gen::fn_sub_58C100_0058c100);
    a0 = s0;
    lw(v1, s0, 72);
    v0 = 4;
    a1 = addiu(sp, 0x4);
    a2 = addiu(sp, 0x8);
    if (v1 == v0) {
        // 0x00593e40
        charge(ctx, 6);
        jal(ctx, 0x593E40u, gen::fn_sub_593EA0_00593ea0);
        a0 = s0;
        lw(v0, sp, 0x8);
        a1 = 15;
        if (v0 != 0) {
            // 0x00593e58
            charge(ctx, 4);
            jal(ctx, 0x593E58u, gen::fn_sub_599408_00599408);
            a0 = s0;
            if (v0 != 0) {
                // 0x00593e68
                charge(ctx, 7);
                lw(v0, sp, 0x8);
                lw(a2, v0, 60);
                link(ctx, 0x593E70u);  // $ra first: the delay slot below depends on it
                lw(a1, v0, 56);
                call(ctx, gen::fn_sub_59AEC0_0059aec0);
                lw(v1, sp, 0x8);
                if (v0 == 0) v1 = 0;
                sw(v1, sp, 0x8);
            }
        }
    } else {
        // 0x00593e38
        charge(ctx, 2);
        sw(zero, sp, 0x8);
    }
    // 0x00593e84
    charge(ctx, 7);
    a0 = sp;
    jal(ctx, 0x593E84u, gen::fn_sub_58C118_0058c118);
    lw(v0, sp, 0x8);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00593EA0 sub_593EA0 -- 272 bytes; frame 0x50: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s4 sp+0x20, s3 sp+0x18, s5 sp+0x28, s6 sp+0x30, s7 sp+0x38, ra sp+0x40
// The oldest and the second-oldest decoded frames not yet shown (0 when fewer).
void sub_593EA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00593ea0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s4, sp, 0x20);
    s4 = 0;
    sd(s3, sp, 0x18);
    sd(s5, sp, 0x28);
    sd(s6, sp, 0x30);
    sd(s7, sp, 0x38);
    sd(ra, sp, 0x40);
    lw(v0, a0, sfd::kVdecWork);
    sw(zero, s2, 0);
    lw(v1, v0, vdec::kFrameCount);
    s0 = addiu(v0, vdec::kFrames);
    sw(zero, s1, 0);
    if (i64(v1) > 0) {
        // 0x00593eec
        charge(ctx, 5);
        s3 = v1;
        s7 = 2;
        s6 = 4;
        s5 = si(-1);
        for (;;) {
            // 0x00593f00
            charge(ctx, 3);
            lw(v0, s0, 0);
            if (v0 == s7) {
                lw(v0, s0, 88);
            } else {
                // 0x00593f0c
                charge(ctx, 2);
                if (v0 == s6) {
                    // 0x00593f14
                    charge(ctx, 1);
                    lw(v0, s0, 88);
                    goto L_00593f18;
                }
                s3 = addiu(s3, -1);
                goto L_00593f5c;
            }
        L_00593f18:
            charge(ctx, 2);
            if (v0 != s5) {
                s3 = addiu(s3, -1);
            } else {
                // 0x00593f20
                charge(ctx, 6);
                lw(a0, s2, 0);
                a1 = s0;
                s4 = addiu(s4, 1);
                jal(ctx, 0x593F28u, gen::fn_sub_593FB0_00593fb0);
                a1 = s0;
                if (v0 == 0) {
                    // 0x00593f48
                    charge(ctx, 4);
                    link(ctx, 0x593F48u);  // $ra first: the delay slot below depends on it
                    lw(a0, s1, 0);
                    call(ctx, gen::fn_sub_593FB0_00593fb0);
                    if (v0 != 0) {
                        sw(s0, s1, 0);
                    }
                } else {
                    // 0x00593f38
                    charge(ctx, 4);
                    lw(v0, s2, 0);
                    sw(v0, s1, 0);
                    sw(s0, s2, 0);
                }
                // 0x00593f58
                charge(ctx, 1);
                s3 = addiu(s3, -1);
            }
        L_00593f5c:
            charge(ctx, 2);
            s0 = addiu(s0, 240);
            if (s3 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00593f64
    charge(ctx, 2);
    v0 = 1;
    if (i64(s4) <= 0) {
        // 0x00593f6c
        charge(ctx, 2);
        sw(zero, s2, 0);
        goto L_00593f80;
    }
    // 0x00593f78
    charge(ctx, 2);
    ld(s0, sp, 0x0);
    if (s4 == v0) {
    L_00593f80:
        charge(ctx, 2);
        sw(zero, s1, 0);
        ld(s0, sp, 0x0);
    }
    // 0x00593f88 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00593FB0 sub_593FB0 -- 28 bytes; leaf frame (no stack)
// Whether frame b is older than frame a (time at +56); 1 when a is null.
void sub_593FB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00593fb0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
    if (a0 != 0) {
        // 0x00593fb8
        charge(ctx, 3);
        lw(v1, a0, 56);
        lw(v0, a1, 56);
        v0 = slt(v0, v1);
    }
    // 0x00593fc4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00593FE8 sub_593FE8 -- 76 bytes; leaf frame (no stack)
// Video-input ring: the 2 KiB sector of an address, 0 at the end mark.
void sub_593FE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00593fe8
    enter(ctx, 11);  // entry check point + this block's cycles
    a3 = a0;
    v1 = 0xFFF0000;
    lw(a0, a3, 8);
    v1 = v1 | 0xFFFF;
    lw(a2, a3, 4);
    a0 = sll(a0, 4);
    a0 = addu(a0, a2);
    a0 = addiu(a0, 16);
    a0 = a0 & v1;
    v0 = 0;
    if (a1 != a0) {
        // 0x00594014
        charge(ctx, 6);
        lw(v0, a3, 0);
        v0 = subu(a1, v0);
        a0 = addiu(v0, 2047);
        v1 = slti(v0, 0);
        if (v1 != 0) v0 = a0;
        v0 = sra(v0, 11);
    }
    // 0x0059402c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00594108 sub_594108 -- 36 bytes; leaf frame (no stack)
// Packs a DMA tag: (addr << 32) | (id << 28) | qwc.
void sub_594108(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00594108
    enter(ctx, 9);  // entry check point + this block's cycles
    a2 = dsll32(a2, 0);
    a1 = dsll32(a1, 0);
    a2 = dsrl(a2, 4);
    a3 = dsll32(a3, 0);
    a1 = a1 | a2;
    a3 = dsrl32(a3, 0);
    a1 = a1 | a3;
    sd(a1, a0, 0);
}

// 0x00594130 viBufCreate -- 120 bytes; frame 0x30: s0 sp+0x20, ra sp+0x28
// The video-input ring buffer for the IPU path: base, the uncached tag area, size in 2 KiB sectors, a semaphore, the
//   tag chain (sub_5941A8).
void viBufCreate(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00594130
    enter(ctx, 30);  // entry check point + this block's cycles
    v0 = 0xFFF0000;
    sp = addiu(sp, -0x30);
    v0 = v0 | 0xFFFF;
    v1 = 0x20000000;
    a2 = a2 & v0;
    v0 = 1;
    sd(s0, sp, 0x20);
    s0 = a0;
    a2 = a2 | v1;
    t2 = sll(a3, 11);
    sd(ra, sp, 0x28);
    a0 = sp;
    sw(t1, s0, 84);
    sw(t2, s0, 24);
    sw(a3, s0, 8);
    sw(a1, s0, 0);
    sw(t0, s0, 80);
    sw(a2, s0, 4);
    sw(v0, sp, 0x4);
    link(ctx, 0x59417Cu);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x8);
    call(ctx, gen::fn__sceCreateSema_00503160);
    sw(v0, s0, 64);
    a0 = s0;
    jal(ctx, 0x594188u, gen::fn_sub_5941A8_005941a8);
    sd(zero, s0, 72);
    ld(ra, sp, 0x28);
    v0 = 1;
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005942E8 sub_5942E8 -- 236 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// Video-input ring, under its semaphore: the free space as up to two pieces split at the wrap.
void sub_5942E8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005942e8
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    s4 = t0;
    sd(ra, sp, 0x28);
    link(ctx, 0x594318u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 64);
    call(ctx, gen::fn__sceWaitSema_005031a0);
    lw(v1, s0, 12);
    lw(a1, s0, 16);
    lw(a2, s0, 20);
    v1 = addu(v1, a1);
    lw(a0, s0, 24);
    v1 = sll(v1, 11);
    lw(v0, s0, 8);
    v1 = addu(v1, a2);
    if (a0 == 0) {
        brk(ctx, 0x594344u, 0x7u);
    }
    // 0x00594348
    charge(ctx, 10);
    div(v1, a0);
    v0 = subu(v0, a1);
    v0 = sll(v0, 11);
    v0 = addiu(v0, -4096);
    a1 = subu(v0, a2);
    mfhi(a3);
    a0 = subu(a0, a3);
    v0 = slt(a0, a1);
    if (v0 != 0) {
        sw(a0, s1, 0);
        // 0x00594390
        charge(ctx, 8);
        lw(a0, s0, 0);
        lw(v0, s0, 24);
        v1 = addu(a0, a3);
        v0 = subu(v0, a3);
        sw(v1, s2, 0);
        v0 = subu(a1, v0);
        sw(a0, s3, 0);
        sw(v0, s4, 0);
    } else {
        // 0x00594370
        charge(ctx, 7);
        lw(v0, s0, 0);
        sw(a1, s1, 0);
        v0 = addu(v0, a3);
        sw(zero, s4, 0);
        sw(v0, s2, 0);
        sw(zero, s3, 0);
    }
    // 0x005943b0
    charge(ctx, 9);
    lw(a0, s0, 64);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    gen::fn__sceSignalSema_00503180(ctx);  // tail call
}

// 0x005943D8 sub_5943D8 -- 80 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Video-input ring, under its semaphore: adds n written bytes (count +20, 64-bit total +72).
void sub_5943D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005943d8
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    link(ctx, 0x5943F0u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 64);
    call(ctx, gen::fn__sceWaitSema_005031a0);
    lw(v1, s0, 20);
    ld(v0, s0, 72);
    v1 = addu(v1, s1);
    lw(a0, s0, 64);
    v0 = s1 + v0;
    ld(s1, sp, 0x8);
    sw(v1, s0, 20);
    sd(v0, s0, 72);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    gen::fn__sceSignalSema_00503180(ctx);  // tail call
}

// 0x00594428 sub_594428 -- 128 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Video-input ring, under its semaphore: removes n consumed bytes; spins forever on an underflow, as the original.
void sub_594428(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00594428
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    link(ctx, 0x594440u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 64);
    call(ctx, gen::fn__sceWaitSema_005031a0);
    lw(v1, s0, 20);
    ld(v0, s0, 72);
    v1 = subu(v1, s1);
    v0 = v0 - s1;
    sw(v1, s0, 20);
    sd(v0, s0, 72);
    if (i64(v1) < 0) {
        // 0x00594464
        charge(ctx, 1);
        for (;;) {
            // 0x00594468
            charge(ctx, 7);
            backedge(ctx);
        }
    }
    // 0x00594488
    charge(ctx, 8);
    link(ctx, 0x594488u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 64);
    call(ctx, gen::fn__sceSignalSema_00503180);
    v0 = s1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00594B68 sub_594B68 -- 12 bytes; leaf frame (no stack)
// Sets the IPU-decode switch 0x7B47A8.
void sub_594B68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00594b68
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sw(a0, v0, 18344);  // 0x7B47A8
}

// 0x00594B78 sub_594B78 -- 16 bytes; leaf frame (no stack)
// Whether the handle decodes through sceMpeg (work+4392).
void sub_594B78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00594b78
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, sfd::kVdecWork);
    lw(v0, v1, vdec::kIpu);
    v0 = sltu(0, v0);
}

// 0x00594B88 sub_594B88 -- 276 bytes, 2 chunks; frame 0x10: ra sp+0x0
// With the IPU switch on: sceMpegInit and clears the saved sceMpeg record (72 bytes at 0x9ACB70).
void sub_594B88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00594b88
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, 18344);  // 0x7B47A8
    sd(ra, sp, 0x0);
    if (v1 == 0) {
        // 0x00594bc0
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00594b9c
    charge(ctx, 9);
    if (native::movies::service()) {  // modernize layer 4 (movies_native.h): no sceMpegInit / sceIpuInit
        link(ctx, 0x594B9Cu);
    } else {
        jal(ctx, 0x594B9Cu, gen::fn_sceMpegInit_00500a20);
    }
    a0 = 0x9B0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, -13456);  // &0x9ACB70
    a1 = 0;
    a2 = 72;
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x005757b0
    charge(ctx, 5);
    a1 = sll(a1, 24);
    v0 = a2 & 0xF;
    a1 = sra(a1, 24);
    a0 = addu(a0, a2);
    if (v0 != 0) {
        // 0x005757c4
        charge(ctx, 1);
        for (;;) {
            // 0x005757c8
            charge(ctx, 7);
            a0 = addiu(a0, -1);
            v0 = addiu(v0, -1);
            sb(a1, a0, 0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x005757e4
    charge(ctx, 3);
    a2 = srl(a2, 4);
    if (a2 != 0) {
        for (;;) {
            // 0x005757f0
            charge(ctx, 34);
            a0 = addiu(a0, -1);
            a2 = addiu(a2, -1);
            sb(a1, a0, 0);
            a0 = addiu(a0, -1);
            sb(a1, a0, 0);
            a0 = addiu(a0, -1);
            sb(a1, a0, 0);
            a0 = addiu(a0, -1);
            sb(a1, a0, 0);
            a0 = addiu(a0, -1);
            sb(a1, a0, 0);
            a0 = addiu(a0, -1);
            sb(a1, a0, 0);
            a0 = addiu(a0, -1);
            sb(a1, a0, 0);
            a0 = addiu(a0, -1);
            sb(a1, a0, 0);
            a0 = addiu(a0, -1);
            sb(a1, a0, 0);
            a0 = addiu(a0, -1);
            sb(a1, a0, 0);
            a0 = addiu(a0, -1);
            sb(a1, a0, 0);
            a0 = addiu(a0, -1);
            sb(a1, a0, 0);
            a0 = addiu(a0, -1);
            sb(a1, a0, 0);
            a0 = addiu(a0, -1);
            sb(a1, a0, 0);
            a0 = addiu(a0, -1);
            sb(a1, a0, 0);
            a0 = addiu(a0, -1);
            sb(a1, a0, 0);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00575878 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00594C38 sub_594C38 -- 532 bytes; frame 0x50: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, fp sp+0x40, s0 sp+0x0, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s7 sp+0x38, ra sp+0x48
// Sets up the sceMpeg path of a video work: the buffer sizes, sceMpegCreate and its four callbacks (or the saved
//   record, sub_595110), the input ring (viBufCreate: 256 sectors, 512 tags) and its DMA.
void sub_594C38(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00594c38
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x7B0000;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s3, sp, 0x18);
    sd(fp, sp, 0x40);
    sd(s0, sp, 0x0);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(s6, sp, 0x30);
    sd(s7, sp, 0x38);
    sd(ra, sp, 0x48);
    lw(v1, v0, 18344);  // 0x7B47A8
    lw(a1, s2, sfd::kVdecWork);
    a2 = addiu(a1, 4);
    s1 = addiu(a1, vdec::kIpu);
    s3 = addiu(a1, 4432);
    fp = addiu(a1, 0x11F8);
    if (v1 != 0) {
        // 0x00594c90
        charge(ctx, 11);
        lw(a0, a2, 12);
        lw(v1, a2, 8);
        lw(a3, a1, 40);
        mult(v1, v1, a0);
        v0 = sll(v1, 3);
        v0 = addu(v0, v1);
        a0 = srl(v0, 31);
        v0 = addu(v0, a0);
        v0 = sra(v0, 1);
        s4 = addiu(v0, 10240);
        if (a3 != 0) {
            // 0x00594ce0
            charge(ctx, 7);
            lw(v0, a1, 44);
            a0 = si(-64);
            v1 = addiu(a3, 63);
            v0 = addiu(v0, 63);
            v1 = v1 & a0;
            v0 = v0 & a0;
            sw(v1, a1, 40);
        } else {
            // 0x00594cbc
            charge(ctx, 9);
            lw(v0, a2, 16);
            a0 = si(-64);
            v0 = addiu(v0, 63);
            v0 = v0 & a0;
            v1 = addu(v0, s4);
            sw(v0, a1, 40);
            v1 = addiu(v1, 63);
            v0 = v1 & a0;
        }
        // 0x00594cfc
        charge(ctx, 14);
        sw(v0, a1, 44);
        lw(s6, a1, 44);
        a0 = si(-64);
        lw(s0, a1, 40);
        v0 = 0x80000;
        v0 = v0 | 0x3F;
        v0 = addu(v0, s6);
        s5 = v0 & a0;
        v1 = addiu(s5, 4175);
        s7 = v1 & a0;
        jal(ctx, 0x594D20u, gen::fn_sceInsockGetErrnoMode_1_00597438);
        v1 = 1;
        a1 = s0;
        if (v0 == v1) {
            // 0x00594da8
            charge(ctx, 3);
            a0 = s2;
            jal(ctx, 0x594DA8u, gen::fn_sub_595110_00595110);
            s0 = addiu(s1, 112);
        } else if (native::movies::MoviesService* nm = native::movies::service()) {
            // modernize layer 4 (movies_native.h): the native decoder instead of sceMpegCreate + its callbacks
            charge(ctx, 29);
            sfd_native_mpeg_create(ctx, *nm, s3.u() - static_cast<u32>(native::movies::kWorkMpeg));
            s0 = addiu(s1, 112);
        } else {
            // 0x00594d34
            charge(ctx, 29);
            a2 = s4;
            a0 = s3;
            jal(ctx, 0x594D38u, gen::fn_sceMpegCreate_004ffe78);
            a2 = 0x590000;
            a2 = addiu(a2, 20064);  // &sub_594E60
            a0 = s3;
            a1 = 0;
            a3 = s2;
            jal(ctx, 0x594D50u, gen::fn_sceMpegAddCallback_00500c90);
            a2 = 0x590000;
            a2 = addiu(a2, 20328);  // &sub_594F68
            a0 = s3;
            a1 = 1;
            a3 = s2;
            jal(ctx, 0x594D68u, gen::fn_sceMpegAddCallback_00500c90);
            a2 = 0x590000;
            a2 = addiu(a2, 20496);  // &sub_595010
            a0 = s3;
            a1 = 2;
            a3 = s2;
            jal(ctx, 0x594D80u, gen::fn_sceMpegAddCallback_00500c90);
            a2 = 0x590000;
            a0 = s3;
            a2 = addiu(a2, 20536);  // &sub_595038
            a3 = s2;
            a1 = 3;
            jal(ctx, 0x594D98u, gen::fn_sceMpegAddCallback_00500c90);
            s0 = addiu(s1, 112);
        }
        // 0x00594db4
        charge(ctx, 26);
        a1 = s6;
        a2 = s5;
        t0 = s7;
        a3 = 256;
        t1 = 512;
        a0 = s0;
        jal(ctx, 0x594DC8u, gen::fn_viBufCreate_00594130);
        a0 = s0;
        jal(ctx, 0x594DD0u, gen::fn_sub_5944A8_005944a8);
        a0 = s0;
        jal(ctx, 0x594DD8u, gen::fn_sub_5946A8_005946a8);
        v1 = 1;
        v0 = si(-1);
        sb(zero, s1, 16);
        sb(zero, s1, 17);
        sb(zero, s1, 18);
        sw(v1, s1, 0);
        sw(zero, s1, 32);
        sw(v0, fp, 0x0);
        sw(zero, fp, 0x4);
        sw(zero, s1, 4);
        sw(zero, s1, 8);
        sw(zero, s1, 12);
        sw(zero, s1, 20);
        sw(zero, s1, 24);
        sw(zero, s1, 28);
    } else {
        // 0x00594c88
        charge(ctx, 2);
        sw(zero, s1, 0);
    }
    // 0x00594e1c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(fp, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x00594EC8 sub_594EC8 -- 160 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// Feeds a chunk to the input ring: the free pieces (sub_5942E8), the copy (sub_595260), the count (sub_5943D8).
void sub_594EC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00594ec8
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a2;
    sd(s1, sp, 0x18);
    s1 = a1;
    a2 = addiu(sp, 0x4);
    a3 = addiu(sp, 0x8);
    a1 = sp;
    t0 = addiu(sp, 0xC);
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x28);
    s2 = a0;
    jal(ctx, 0x594EF4u, gen::fn_sub_5942E8_005942e8);
    lw(a0, sp, 0x0);
    v0 = 0xFFF0000;
    lw(a2, sp, 0x8);
    v0 = v0 | 0xFFFF;
    v1 = 0x20000000;
    lw(a1, sp, 0x4);
    lw(a3, sp, 0xC);
    a0 = a0 & v0;
    a2 = a2 & v0;
    t0 = s1;
    t1 = s0;
    a0 = a0 | v1;
    a2 = a2 | v1;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x594F34u, gen::fn_sub_595260_00595260);
    a0 = s2;
    s0 = v0;
    a1 = s0;
    jal(ctx, 0x594F44u, gen::fn_sub_5943D8_005943d8);
    v0 = s0;
    ld(s1, sp, 0x18);
    ld(s0, sp, 0x10);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00595010 sub_595010 -- 36 bytes; frame 0x10: ra sp+0x0
// sceMpeg callback: restarts the input DMA (sub_5946A8); 1.
void sub_595010(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595010
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a2, sfd::kVdecWork);
    a0 = addiu(a0, 4504);
    jal(ctx, 0x59501Cu, gen::fn_sub_5946A8_005946a8);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00595038 sub_595038 -- 36 bytes; frame 0x10: ra sp+0x0
// sceMpeg callback: stops the input DMA (sub_5947A8); 1.
void sub_595038(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595038
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a2, sfd::kVdecWork);
    a0 = addiu(a0, 4504);
    jal(ctx, 0x595044u, gen::fn_sub_5947A8_005947a8);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00595060 sub_595060 -- 640 bytes, 2 chunks; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Releases the sceMpeg path: stops the DMA (sub_594AC0); in recreate mode resets and saves the 72-byte sceMpeg record
//   into 0x9ACB70, else deletes it.
void sub_595060(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595060
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x595070u, gen::fn_sub_594B78_00594b78);
    ld(s0, sp, 0x0);
    if (v0 == 0) {
        // 0x005950d8
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00595080
    charge(ctx, 8);
    lw(s0, s1, sfd::kVdecWork);
    a0 = addiu(s0, 4504);
    jal(ctx, 0x595084u, gen::fn_sub_594AC0_00594ac0);
    jal(ctx, 0x59508Cu, gen::fn_sceInsockGetErrnoMode_1_00597438);
    v1 = 1;
    a0 = addiu(s0, 4432);
    if (v0 != v1) {
        // 0x005950a0
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        if (native::movies::MoviesService* nm = native::movies::service()) {  // layer 4: the native decoder goes
            nm->mpeg_delete(ctx.cycles, a0.u());
            v0 = 1;  // sceMpegDelete's result
            return;
        }
        gen::fn_sceMpegDelete_00500ad0(ctx);  // tail call
        return;
    }
    // 0x005950b8
    charge(ctx, 8);
    if (native::movies::MoviesService* nm = native::movies::service()) {  // layer 4: the native decoder resets
        link(ctx, 0x5950B8u);
        nm->mpeg_reset(ctx.cycles, a0.u());
    } else {
        jal(ctx, 0x5950B8u, gen::fn_sceMpegReset_00500bb8);
    }
    a0 = s1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    // 0x005950e8
    charge(ctx, 10);
    sp = addiu(sp, -0x10);
    a2 = 72;
    sd(ra, sp, 0x0);
    lw(a1, a0, sfd::kVdecWork);
    a0 = 0x9B0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, -13456);  // &0x9ACB70
    a1 = addiu(a1, 4432);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x005754d0
    charge(ctx, 3);
    v1 = a2 & 0x1F;
    if (v1 == 0) {
        a2 = srl(a2, 5);
    } else {
        // 0x005754dc
        charge(ctx, 1);
        for (;;) {
            // 0x005754e0
            charge(ctx, 7);
            lbu(v0, a1, 0);
            a1 = addiu(a1, 1);
            v1 = addiu(v1, -1);
            sb(v0, a0, 0);
            a0 = addiu(a0, 1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005754fc
        charge(ctx, 1);
        a2 = srl(a2, 5);
    }
    // 0x00575500
    charge(ctx, 2);
    if (a2 != 0) {
        for (;;) {
            // 0x00575508
            charge(ctx, 100);
            lb(t0, a1, 0);
            a1 = addiu(a1, 1);
            lb(a3, a1, 0);
            a1 = addiu(a1, 1);
            lb(v1, a1, 0);
            a1 = addiu(a1, 1);
            lb(v0, a1, 0);
            a1 = addiu(a1, 1);
            sb(t0, a0, 0);
            a2 = addiu(a2, -1);
            sb(a3, a0, 1);
            sb(v1, a0, 2);
            sb(v0, a0, 3);
            lb(t0, a1, 0);
            a1 = addiu(a1, 1);
            lb(a3, a1, 0);
            a1 = addiu(a1, 1);
            lb(v1, a1, 0);
            a1 = addiu(a1, 1);
            lb(v0, a1, 0);
            a1 = addiu(a1, 1);
            sb(t0, a0, 4);
            sb(a3, a0, 5);
            sb(v1, a0, 6);
            sb(v0, a0, 7);
            lb(t0, a1, 0);
            a1 = addiu(a1, 1);
            lb(a3, a1, 0);
            a1 = addiu(a1, 1);
            lb(v1, a1, 0);
            a1 = addiu(a1, 1);
            lb(v0, a1, 0);
            a1 = addiu(a1, 1);
            sb(t0, a0, 8);
            sb(a3, a0, 9);
            sb(v1, a0, 10);
            sb(v0, a0, 11);
            lb(t0, a1, 0);
            a1 = addiu(a1, 1);
            lb(a3, a1, 0);
            a1 = addiu(a1, 1);
            lb(v1, a1, 0);
            a1 = addiu(a1, 1);
            lb(v0, a1, 0);
            a1 = addiu(a1, 1);
            sb(t0, a0, 12);
            sb(a3, a0, 13);
            sb(v1, a0, 14);
            sb(v0, a0, 15);
            a0 = addiu(a0, 16);
            lb(t0, a1, 0);
            a1 = addiu(a1, 1);
            lb(a3, a1, 0);
            a1 = addiu(a1, 1);
            lb(v1, a1, 0);
            a1 = addiu(a1, 1);
            lb(v0, a1, 0);
            a1 = addiu(a1, 1);
            sb(t0, a0, 0);
            sb(a3, a0, 1);
            sb(v1, a0, 2);
            sb(v0, a0, 3);
            lb(t0, a1, 0);
            a1 = addiu(a1, 1);
            lb(a3, a1, 0);
            a1 = addiu(a1, 1);
            lb(v1, a1, 0);
            a1 = addiu(a1, 1);
            lb(v0, a1, 0);
            a1 = addiu(a1, 1);
            sb(t0, a0, 4);
            sb(a3, a0, 5);
            sb(v1, a0, 6);
            sb(v0, a0, 7);
            lb(t0, a1, 0);
            a1 = addiu(a1, 1);
            lb(a3, a1, 0);
            a1 = addiu(a1, 1);
            lb(v1, a1, 0);
            a1 = addiu(a1, 1);
            lb(v0, a1, 0);
            a1 = addiu(a1, 1);
            sb(t0, a0, 8);
            sb(a3, a0, 9);
            sb(v1, a0, 10);
            sb(v0, a0, 11);
            lb(t0, a1, 0);
            a1 = addiu(a1, 1);
            lb(a3, a1, 0);
            a1 = addiu(a1, 1);
            lb(v1, a1, 0);
            a1 = addiu(a1, 1);
            lb(v0, a1, 0);
            a1 = addiu(a1, 1);
            sb(t0, a0, 12);
            sb(a3, a0, 13);
            sb(v1, a0, 14);
            sb(v0, a0, 15);
            a0 = addiu(a0, 16);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00575698 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00595110 sub_595110 -- 504 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Restores the 72-byte sceMpeg record from 0x9ACB70.
void sub_595110(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595110
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0x9B0000;
    sd(ra, sp, 0x0);
    a1 = addiu(a1, -13456);  // &0x9ACB70
    a2 = 72;
    lw(a0, a0, sfd::kVdecWork);
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 4432);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x005754d0
    charge(ctx, 3);
    v1 = a2 & 0x1F;
    if (v1 == 0) {
        a2 = srl(a2, 5);
    } else {
        // 0x005754dc
        charge(ctx, 1);
        for (;;) {
            // 0x005754e0
            charge(ctx, 7);
            lbu(v0, a1, 0);
            a1 = addiu(a1, 1);
            v1 = addiu(v1, -1);
            sb(v0, a0, 0);
            a0 = addiu(a0, 1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005754fc
        charge(ctx, 1);
        a2 = srl(a2, 5);
    }
    // 0x00575500
    charge(ctx, 2);
    if (a2 != 0) {
        for (;;) {
            // 0x00575508
            charge(ctx, 100);
            lb(t0, a1, 0);
            a1 = addiu(a1, 1);
            lb(a3, a1, 0);
            a1 = addiu(a1, 1);
            lb(v1, a1, 0);
            a1 = addiu(a1, 1);
            lb(v0, a1, 0);
            a1 = addiu(a1, 1);
            sb(t0, a0, 0);
            a2 = addiu(a2, -1);
            sb(a3, a0, 1);
            sb(v1, a0, 2);
            sb(v0, a0, 3);
            lb(t0, a1, 0);
            a1 = addiu(a1, 1);
            lb(a3, a1, 0);
            a1 = addiu(a1, 1);
            lb(v1, a1, 0);
            a1 = addiu(a1, 1);
            lb(v0, a1, 0);
            a1 = addiu(a1, 1);
            sb(t0, a0, 4);
            sb(a3, a0, 5);
            sb(v1, a0, 6);
            sb(v0, a0, 7);
            lb(t0, a1, 0);
            a1 = addiu(a1, 1);
            lb(a3, a1, 0);
            a1 = addiu(a1, 1);
            lb(v1, a1, 0);
            a1 = addiu(a1, 1);
            lb(v0, a1, 0);
            a1 = addiu(a1, 1);
            sb(t0, a0, 8);
            sb(a3, a0, 9);
            sb(v1, a0, 10);
            sb(v0, a0, 11);
            lb(t0, a1, 0);
            a1 = addiu(a1, 1);
            lb(a3, a1, 0);
            a1 = addiu(a1, 1);
            lb(v1, a1, 0);
            a1 = addiu(a1, 1);
            lb(v0, a1, 0);
            a1 = addiu(a1, 1);
            sb(t0, a0, 12);
            sb(a3, a0, 13);
            sb(v1, a0, 14);
            sb(v0, a0, 15);
            a0 = addiu(a0, 16);
            lb(t0, a1, 0);
            a1 = addiu(a1, 1);
            lb(a3, a1, 0);
            a1 = addiu(a1, 1);
            lb(v1, a1, 0);
            a1 = addiu(a1, 1);
            lb(v0, a1, 0);
            a1 = addiu(a1, 1);
            sb(t0, a0, 0);
            sb(a3, a0, 1);
            sb(v1, a0, 2);
            sb(v0, a0, 3);
            lb(t0, a1, 0);
            a1 = addiu(a1, 1);
            lb(a3, a1, 0);
            a1 = addiu(a1, 1);
            lb(v1, a1, 0);
            a1 = addiu(a1, 1);
            lb(v0, a1, 0);
            a1 = addiu(a1, 1);
            sb(t0, a0, 4);
            sb(a3, a0, 5);
            sb(v1, a0, 6);
            sb(v0, a0, 7);
            lb(t0, a1, 0);
            a1 = addiu(a1, 1);
            lb(a3, a1, 0);
            a1 = addiu(a1, 1);
            lb(v1, a1, 0);
            a1 = addiu(a1, 1);
            lb(v0, a1, 0);
            a1 = addiu(a1, 1);
            sb(t0, a0, 8);
            sb(a3, a0, 9);
            sb(v1, a0, 10);
            sb(v0, a0, 11);
            lb(t0, a1, 0);
            a1 = addiu(a1, 1);
            lb(a3, a1, 0);
            a1 = addiu(a1, 1);
            lb(v1, a1, 0);
            a1 = addiu(a1, 1);
            lb(v0, a1, 0);
            a1 = addiu(a1, 1);
            sb(t0, a0, 12);
            sb(a3, a0, 13);
            sb(v1, a0, 14);
            sb(v0, a0, 15);
            a0 = addiu(a0, 16);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00575698 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00595138 sub_595138 -- 112 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// On the sceMpeg path, feeds the input chunk to the ring (sub_594EC8); otherwise returns a2.
void sub_595138(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595138
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a0;
    jal(ctx, 0x595154u, gen::fn_sub_594B78_00594b78);
    a1 = s0;
    a2 = s1;
    if (v0 == 0) {
        // 0x00595168
        charge(ctx, 7);
        v0 = s1;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00595188
    charge(ctx, 8);
    lw(a0, s2, sfd::kVdecWork);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a0 = addiu(a0, 4504);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_594EC8_00594ec8(ctx);  // tail call
}

// 0x005951A8 sub_5951A8 -- 92 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// On the sceMpeg path, takes n bytes from the ring (sub_594428); otherwise returns a1.
void sub_5951A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005951a8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x5951BCu, gen::fn_sub_594B78_00594b78);
    a1 = s0;
    if (v0 == 0) {
        // 0x005951cc
        charge(ctx, 6);
        v0 = s0;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x005951e8
    charge(ctx, 7);
    lw(a0, s1, sfd::kVdecWork);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a0 = addiu(a0, 4504);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_594428_00594428(ctx);  // tail call
}

// 0x00595260 sub_595260 -- 300 bytes; frame 0x50: s0 sp+0x0, s1 sp+0x8, s5 sp+0x28, fp sp+0x40, s2 sp+0x10, s4 sp+0x20, s6 sp+0x30, s7 sp+0x38, s3 sp+0x18, ra sp+0x48
// Copies two source pieces into the two destination pieces of a ring when they fit; the total, or 0.
void sub_595260(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00595260
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0;
    sd(s0, sp, 0x0);
    s0 = t1;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s5, sp, 0x28);
    s5 = t3;
    sd(fp, sp, 0x40);
    fp = addu(s0, s5);
    a3 = addu(s1, a3);
    sd(s2, sp, 0x10);
    a3 = slt(a3, fp);
    sd(s4, sp, 0x20);
    sd(s6, sp, 0x30);
    s6 = a2;
    sd(s7, sp, 0x38);
    s7 = a0;
    sd(s3, sp, 0x18);
    v1 = slt(s0, s1);
    sd(ra, sp, 0x48);
    s2 = t0;
    s4 = t2;
    if (a3 == 0) {
        // 0x005952c0
        charge(ctx, 2);
        if (v1 != 0) {
            s3 = subu(s1, s0);
            // 0x00595300
            charge(ctx, 3);
            v0 = slt(s5, s3);
            a1 = s2;
            if (v0 != 0) {
                // 0x00595340
                charge(ctx, 7);
                a2 = s0;
                jal(ctx, 0x595340u, gen::fn_memcpy_00521250);
                a2 = s5;
                a1 = s4;
                a0 = addu(s7, s0);
                jal(ctx, 0x595350u, gen::fn_memcpy_00521250);
                v0 = fp;
            } else {
                // 0x0059530c
                charge(ctx, 13);
                a2 = s0;
                jal(ctx, 0x59530Cu, gen::fn_memcpy_00521250);
                a2 = s3;
                a1 = s4;
                a0 = addu(s7, s0);
                jal(ctx, 0x59531Cu, gen::fn_memcpy_00521250);
                a1 = addu(s4, s1);
                a1 = subu(a1, s0);
                a2 = subu(s5, s3);
                a0 = s6;
                jal(ctx, 0x595330u, gen::fn_memcpy_00521250);
                v0 = fp;
            }
        } else {
            // 0x005952c8
            charge(ctx, 14);
            a1 = s2;
            a2 = s1;
            jal(ctx, 0x5952CCu, gen::fn_memcpy_00521250);
            a0 = s6;
            a1 = addu(s2, s1);
            a2 = subu(s0, s1);
            jal(ctx, 0x5952DCu, gen::fn_memcpy_00521250);
            a0 = addu(s6, s0);
            a0 = subu(a0, s1);
            a1 = s4;
            a2 = s5;
            jal(ctx, 0x5952F0u, gen::fn_memcpy_00521250);
            v0 = fp;
        }
    }
    // 0x0059535c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(fp, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x00595390 sub_595390 -- 328 bytes; frame 0x40: s5 sp+0x28, s1 sp+0x8, s0 sp+0x0, s4 sp+0x20, s2 sp+0x10, s3 sp+0x18, s6 sp+0x30, ra sp+0x38
// Decodes a picture: through MPV (sub_579078), or on the sceMpeg path the input DMA stop / restart around
//   sceMpegGetPicture (format 2) / sceMpegGetPictureRAW8, one pending picture less (sub_595700), -3 on a sceMpeg
//   error.
void sub_595390(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595390
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s5, sp, 0x28);
    s5 = a3;
    sd(s1, sp, 0x8);
    s1 = a0;
    a0 = s5;
    sd(s0, sp, 0x0);
    sd(s4, sp, 0x20);
    s4 = a2;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s6, sp, 0x30);
    sd(ra, sp, 0x38);
    s0 = a1;
    jal(ctx, 0x5953C4u, gen::fn_sub_594B78_00594b78);
    a1 = s0;
    a0 = s1;
    a2 = s4;
    if (v0 == 0) {
        // 0x005953dc
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
        gen::fn_sub_579078_00579078(ctx);  // tail call
        return;
    }
    // 0x00595408
    const u64 log_c0 = ctx.cycles;  // the movie log (movies_service.h g_log; read-only)
    charge(ctx, 27);
    link(ctx, 0x595408u);  // $ra first: the delay slot below depends on it
    lw(s2, s5, sfd::kVdecWork);
    call(ctx, gen::fn_sub_579080_00579080);
    s6 = v0;
    s0 = addiu(s2, 4504);
    s3 = addiu(s2, vdec::kIpu);
    a0 = s0;
    s1 = addiu(s2, 4);
    jal(ctx, 0x595420u, gen::fn_sub_5947A8_005947a8);
    a0 = s0;
    jal(ctx, 0x595428u, gen::fn_sub_5944A8_005944a8);
    a0 = addiu(s2, 4432);
    v0 = 1;
    lw(t2, s5, 56);
    sw(v0, s3, 20);
    t1 = 2;
    lw(v1, s1, 12);
    lw(v0, s1, 8);
    t0 = addiu(v1, 15);
    a3 = slti(v1, 0);
    a2 = addiu(v0, 15);
    a1 = slti(v0, 0);
    if (a1 != 0) v0 = a2;
    if (a3 != 0) v1 = t0;
    v0 = sra(v0, 4);
    v1 = sra(v1, 4);
    mult(a2, v0, v1);
    if (native::movies::MoviesService* nm = native::movies::service()) {
        // modernize layer 4 (movies_native.h): the native decoder instead of sceMpegGetPicture / RAW8
        charge(ctx, 4);
        link(ctx, 0x595474u);
        // the faithful call's guest time, charged with check points as its loops would (no host state is live here)
        for (u64 left = sfd_native_get_picture(ctx, *nm, s2.u(), s4.u(), s5.u()); left != 0;) {
            const u64 n = left < 4096u ? left : 4096u;
            charge(ctx, n);
            left -= n;
            backedge(ctx);
        }
        sw(zero, s3, 20);
    } else if (t2 != t1) {
        // 0x00595488
        charge(ctx, 3);
        link(ctx, 0x595488u);  // $ra first: the delay slot below depends on it
        lw(a1, s4, 32);
        call(ctx, gen::fn_sceMpegGetPictureRAW8_00500b60);
        sw(zero, s3, 20);
    } else {
        // 0x00595474
        charge(ctx, 4);
        link(ctx, 0x595474u);  // $ra first: the delay slot below depends on it
        lw(a1, s4, 32);
        call(ctx, gen::fn_sceMpegGetPicture_00500b18);
        sw(zero, s3, 20);
    }
    // 0x00595494
    charge(ctx, 17);
    a0 = addiu(s3, 112);
    jal(ctx, 0x595494u, gen::fn_sub_5946A8_005946a8);
    a0 = s5;
    jal(ctx, 0x59549Cu, gen::fn_sub_595700_00595700);
    lw(v1, s3, 24);
    v0 = si(-3);
    ld(s0, sp, 0x0);
    if (v1 == 0) v0 = s6;
    if (native::movies::MovieLogSink* lg = native::movies::g_log)
        lg->picture_call(log_c0, ctx.cycles, s2.u(), ctx.memory->read<u32>(s4.u() + 32u),
                         ctx.memory->read<u32>(s5.u() + 56u), v0.s());
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x005954D8 sub_5954D8 -- 12 bytes; leaf frame (no stack)
// work+4440.
void sub_5954D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x005954d8
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, sfd::kVdecWork);
    lw(v0, v1, 4440);
}

// 0x005954E8 sub_5954E8 -- 532 bytes; frame 0x50: s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, s0 sp+0x10, ra sp+0x40
// sceMpeg path: counts the picture start codes of an input chunk, carrying the last 3 bytes across chunks; a non-
//   picture code or the sequence end (0xB7) completes the stream (sub_589FD0, sub_58A038, sub_595208).
void sub_5954E8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005954e8
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    s2 = a2;
    sd(s3, sp, 0x28);
    s3 = a1;
    sd(s4, sp, 0x30);
    s4 = a0;
    sd(s5, sp, 0x38);
    s5 = 0;
    sd(s0, sp, 0x10);
    a2 = 0;
    sd(ra, sp, 0x40);
    lw(v1, s4, sfd::kVdecWork);
    s1 = addiu(v1, vdec::kIpu);
    lw(v1, s1, 4);
    lw(v0, s1, 12);
    lw(a0, s1, 8);
    lbu(a1, s1, 16);
    v0 = addu(v0, v1);
    sw(v0, s1, 12);
    sw(a0, s1, 4);
    sw(zero, s1, 8);
    sb(a1, sp, 0x0);
    lbu(v0, s1, 17);
    sb(v0, sp, 0x1);
    lbu(v1, s1, 18);
    sb(v1, sp, 0x2);
    lbu(v0, s3, 0);
    sb(v0, sp, 0x3);
    lbu(v1, s3, 1);
    sb(v1, sp, 0x4);
    lbu(v0, s3, 2);
    sb(v0, sp, 0x5);
    a3 = slti(s2, 4);
    for (;;) {
        // 0x005955cc
        charge(ctx, 5);
        v0 = 3;
        if (a3 != 0) v0 = s2;
        v0 = slt(a2, v0);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = addu(sp, a2);
        if (!cc) {
            break;
        }
        backedge(ctx);
        // 0x00595578
        charge(ctx, 3);
        lbu(v1, v0, 0);
        a1 = addiu(a2, 1);
        if (v1 != 0) {
            // 0x005955c8
            charge(ctx, 1);
            a2 = a1;
            continue;
        }
        // 0x00595584
        charge(ctx, 4);
        v0 = addu(sp, a1);
        lbu(v1, v0, 0);
        if (v1 != 0) {
            a2 = a1;
            continue;
        }
        // 0x00595594
        charge(ctx, 5);
        v0 = addu(a2, sp);
        a0 = 1;
        lbu(v1, v0, 2);
        if (v1 != a0) {
            a2 = a1;
            continue;
        }
        // 0x005955a8
        charge(ctx, 3);
        lbu(v1, v0, 3);
        v0 = 183;
        if (v1 == 0) {
            goto L_00595618;
        }
        // 0x005955b4
        charge(ctx, 2);
        if (v1 == v0) {
            goto L_005955bc_6;
        }
        a2 = a1;
    }
L_005955e0:
    charge(ctx, 3);
    v0 = slti(s2, 3);
    a0 = addu(s3, s2);
    if (v0 == 0) {
        // 0x00595628
        charge(ctx, 7);
        lbu(v0, a0, -3);
        sb(v0, s1, 16);
        lbu(v1, a0, -2);
        sb(v1, s1, 17);
        lbu(v0, a0, -1);
        sb(v0, s1, 18);
    } else {
        // 0x005955ec
        charge(ctx, 10);
        v0 = addu(sp, s2);
        a0 = addu(s2, sp);
        lbu(v1, v0, 0);
        a1 = a0;
        sb(v1, s1, 16);
        lbu(v0, a0, 1);
        sb(v0, s1, 17);
        lbu(v1, a1, 2);
        sb(v1, s1, 18);
    }
    for (;;) {
        // 0x0059567c
        charge(ctx, 2);
        v0 = 1;
        if (a3 != 0) {
            break;
        }
        // 0x00595684
        charge(ctx, 7);
        a0 = s3;
        a1 = s2;
        a2 = 132;
        jal(ctx, 0x59568Cu, gen::fn_sub_578160_00578160);
        s0 = v0;
        a0 = s0;
        if (s0 == 0) {
            goto L_005956a0_18;
        }
        backedge(ctx);
        // 0x00595648
        charge(ctx, 5);
        jal(ctx, 0x595648u, gen::fn_sub_577FC8_00577fc8);
        v0 = v0 & 0x4;
        if (v0 == 0) {
            s5 = 1;
        } else {
            // 0x0059565c
            charge(ctx, 3);
            lw(v0, s1, 8);
            v0 = addiu(v0, 1);
            sw(v0, s1, 8);
        }
        // 0x00595668
        charge(ctx, 5);
        s0 = addiu(s0, 4);
        v0 = subu(s0, s3);
        s3 = s0;
        s2 = subu(s2, v0);
        a3 = slti(s2, 4);
    }
L_005956a4:
    charge(ctx, 2);
    if (s5 != v0) {
        ld(s0, sp, 0x10);
    } else {
        // 0x005956ac
        charge(ctx, 4);
        a0 = s4;
        jal(ctx, 0x5956ACu, gen::fn_sub_589FD0_00589fd0);
        if (v0 != 0) {
            ld(s0, sp, 0x10);
        } else {
            // 0x005956bc
            charge(ctx, 4);
            a0 = s4;
            jal(ctx, 0x5956BCu, gen::fn_sub_58A038_0058a038);
            ld(s0, sp, 0x10);
            if (v0 == 0) {
                // 0x005956cc
                charge(ctx, 4);
                a0 = s4;
                a1 = 1;
                jal(ctx, 0x5956D0u, gen::fn_sub_595208_00595208);
                ld(s0, sp, 0x10);
            }
        }
    }
    // 0x005956dc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
    return;
L_005955bc_6:
    charge(ctx, 2);
    s5 = 1;
    goto L_005955e0;
L_00595618:
    charge(ctx, 4);
    lw(v0, s1, 8);
    v0 = addiu(v0, 1);
    sw(v0, s1, 8);
    backedge(ctx);
    goto L_005955e0;
L_005956a0_18:
    charge(ctx, 1);
    v0 = 1;
    goto L_005956a4;
}

// 0x00595700 sub_595700 -- 24 bytes; leaf frame (no stack)
// One pending picture less (work+4404).
void sub_595700(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00595700
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, a0, sfd::kVdecWork);
    v1 = addiu(v1, vdec::kIpu);
    lw(v0, v1, 12);
    v0 = addiu(v0, -1);
    sw(v0, v1, 12);
}

// 0x00595718 sub_595718 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Whether the sceMpeg path has input enough: always without it; else at the end (+4424 = 1) or with 3 pictures
//   pending.
void sub_595718(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595718
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x595724u, gen::fn_sub_594B78_00594b78);
    a1 = 1;
    if (v0 != 0) {
        // 0x00595740
        charge(ctx, 5);
        lw(a0, s0, sfd::kVdecWork);
        a0 = addiu(a0, vdec::kIpu);
        lw(v1, a0, 32);
        v0 = 1;
        if (v1 != a1) {
            // 0x00595754
            charge(ctx, 3);
            lw(v0, a0, 12);
            v0 = slti(v0, 3);
            v0 = sltiu(v0, 1);
        }
    } else {
        // 0x00595734
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x00595760 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005959D0 sub_5959D0 -- 16 bytes; leaf frame (no stack)
// Request (+76) = 3 (stop).
void sub_5959D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x005959d0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 3;
    v0 = 0;
    sw(v1, a0, 76);
}

// 0x00595B30 sub_595B30 -- 36 bytes; frame 0x10: ra sp+0x0
// Checks the work marker (sub_595B58) and clears the get-frame callback 0x7B47BC.
void sub_595B30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595b30
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x595B38u, gen::fn_sub_595B58_00595b58);
    ld(ra, sp, 0x0);
    v0 = 0x7B0000;
    sw(zero, v0, 18364);  // 0x7B47BC
    sp = addiu(sp, 0x10);
}

// 0x00595B58 sub_595B58 -- 68 bytes; frame 0x10: ra sp+0x0
// The marker 0x7CA280 must be 0x5A5A5A5A (error -16776703).
void sub_595B58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595b58
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0x7D0000;
    v1 = 0x5A5A0000;
    lw(a0, v0, -23936);  // 0x7CA280
    sp = addiu(sp, -0x10);
    v1 = v1 | 0x5A5A;
    sd(ra, sp, 0x0);
    if (a0 == v1) {
        // 0x00595b90
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00595b74
    charge(ctx, 6);
    a1 = lui(0xFF00);
    ld(ra, sp, 0x0);
    a0 = 0;
    a1 = a1 | 0x201;
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x00595D10 sub_595D10 -- 276 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// The status step of an SFD handle: when the time was updated (+68), runs the status's handler (1 sub_595E68, 2
//   sub_595E98, 3 sub_596230, 4 sub_5962D0, 6 sub_596340) between two clock reads (profile +14176).
void sub_595D10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595d10
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(s0, s1, 72);
    v0 = addiu(s0, -1);
    v0 = sltiu(v0, 4);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
        // 0x00595e10 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00595d3c
    charge(ctx, 3);
    lw(v0, s1, 68);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
        // 0x00595e10 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00595d48
    charge(ctx, 8);
    sw(zero, s1, 68);
    jal(ctx, 0x595D4Cu, gen::fn_sub_59B3A8_0059b3a8);
    s2 = v0;
    v0 = addiu(s0, -2);
    v0 = sltiu(v0, 3);
    if (v0 == 0) {
        lw(s0, s1, 72);
    } else {
        // 0x00595d68
        charge(ctx, 3);
        a0 = s1;
        jal(ctx, 0x595D68u, gen::fn_sub_595E28_00595e28);
        lw(s0, s1, 72);
    }
    // 0x00595d74
    charge(ctx, 3);
    v0 = sltiu(s0, 7);
    if (v0 == 0) {
        sw(s0, s1, 72);
    } else {
        // 0x00595d80
        charge(ctx, 6);
        v0 = sll(s0, 2);
        v1 = 0x7D0000;
        v1 = addu(v1, v0);
        lw(v1, v1, -23904);
        switch (v1.u()) {
        case 0x595D98u:  // table[1]
            // 0x00595d98
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x595D98u, gen::fn_sub_595E68_00595e68);
            s0 = v0;
            break;
        case 0x595DA8u:  // table[2]
            // 0x00595da8
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x595DA8u, gen::fn_sub_595E98_00595e98);
            s0 = v0;
            break;
        case 0x595DB8u:  // table[3]
            // 0x00595db8
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x595DB8u, gen::fn_sub_596230_00596230);
            s0 = v0;
            break;
        case 0x595DC8u:  // table[4]
            // 0x00595dc8
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x595DC8u, gen::fn_sub_5962D0_005962d0);
            s0 = v0;
            break;
        case 0x595DD8u:  // table[6]
            // 0x00595dd8
            charge(ctx, 3);
            a0 = s1;
            jal(ctx, 0x595DD8u, gen::fn_sub_596340_00596340);
            s0 = v0;
            break;
        case 0x595DE4u:  // table[0, 5]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
        // 0x00595de4
        charge(ctx, 1);
        sw(s0, s1, 72);
    }
    // 0x00595de8
    charge(ctx, 10);
    s0 = addiu(s1, 14176);
    jal(ctx, 0x595DE8u, gen::fn_sub_59B3A8_0059b3a8);
    a0 = s0;
    a1 = v0 - s2;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_59B4B0_0059b4b0(ctx);  // tail call
}

// 0x00595E28 sub_595E28 -- 40 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The pre-step of statuses 2..4: sub_595E50, then the header object's step (sub_598640).
void sub_595E28(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595e28
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x595E34u, gen::fn_sub_595E50_00595e50);
    ld(ra, sp, 0x8);
    a0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_598640_00598640(ctx);  // tail call
}

// 0x00595E50 sub_595E50 -- 24 bytes; frame 0x10: ra sp+0x0
// sub_59BB88(handle, 2).
void sub_595E50(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595e50
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 2;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59BB88_0059bb88(ctx);  // tail call
}

// 0x00595E68 sub_595E68 -- 48 bytes; leaf frame (no stack)
// Status 1: to status 2 when the request is 2..4 or 6.
void sub_595E68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00595e68
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, a0, 76);
    lw(a1, a0, 72);
    v0 = slti(v1, 2);
    a0 = slti(v1, 5);
    if (v0 == 0) {
        // 0x00595e7c
        charge(ctx, 2);
        if (a0 != 0) {
            a1 = 2;
        } else {
            // 0x00595e84
            charge(ctx, 3);
            v0 = 6;
            if (v1 == v0) {
                a1 = 2;
            }
        }
    }
    // 0x00595e90 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a1;
}

// 0x00595E98 sub_595E98 -- 192 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// Status 2 (preparing): when the inputs are ready (sub_595F58), the params (sub_596008); request 3 -> 3, 2 -> 2, 4 /
//   6 -> 4 when ready to start (sub_596348, sub_597340) else 3.
void sub_595E98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00595e98
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(s2, s1, 72);
    link(ctx, 0x595EB4u);  // $ra first: the delay slot below depends on it
    lw(s0, s1, 76);
    call(ctx, gen::fn_sub_595F58_00595f58);
    if (v0 == 0) {
        v0 = s2;
    } else {
        // 0x00595ec4
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x595EC4u, gen::fn_sub_596008_00596008);
        v0 = 3;
        cc = s0 == v0;  // the condition, before the delay slot changes it
        v0 = slti(s0, 4);
        if (!cc) {
            // 0x00595ed8
            charge(ctx, 2);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 4;
            if (cc) {
                // 0x00595ef8
                charge(ctx, 2);
                cc = s0 == v0;  // the condition, before the delay slot changes it
                v0 = 6;
                if (!cc) {
                    // 0x00595f00
                    charge(ctx, 2);
                    cc = s0 == v0;  // the condition, before the delay slot changes it
                    v0 = s2;
                    if (cc) {
                        goto L_00595f18;
                    }
                    // 0x00595f08
                    charge(ctx, 2);
                    ld(s0, sp, 0x0);
                    // 0x00595f44 (the shared epilogue, written out on this path)
                    charge(ctx, 5);
                    ld(s1, sp, 0x8);
                    ld(s2, sp, 0x10);
                    ld(ra, sp, 0x18);
                    sp = addiu(sp, 0x20);
                    return;
                }
            L_00595f18:
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x595F18u, gen::fn_sub_596348_00596348);
                a0 = s1;
                if (v0 == 0) {
                    goto L_00595f38;
                }
                // 0x00595f28
                charge(ctx, 4);
                s2 = 4;
                jal(ctx, 0x595F28u, gen::fn_sub_597340_00597340);
                v0 = s2;
                goto L_00595f40;
            }
            // 0x00595ee0
            charge(ctx, 3);
            v0 = 2;
            cc = s0 == v0;  // the condition, before the delay slot changes it
            v0 = s2;
            if (cc) {
                // 0x00595f10
                charge(ctx, 2);
                s2 = 2;
            L_00595f3c:
                charge(ctx, 1);
                v0 = s2;
                goto L_00595f40;
            }
            // 0x00595eec
            charge(ctx, 2);
            ld(s0, sp, 0x0);
            // 0x00595f44 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(ra, sp, 0x18);
            sp = addiu(sp, 0x20);
            return;
        }
    L_00595f38:
        charge(ctx, 1);
        s2 = 3;
        goto L_00595f3c;
    }
L_00595f40:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x00595f44 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00595F58 sub_595F58 -- 176 bytes; frame 0x20: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, ra sp+0x18
// Whether the audio (param 5) and video (param 6) inputs are ready (sub_59BC88 / sub_59BCB8).
void sub_595F58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595f58
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 5;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    s2 = 1;
    jal(ctx, 0x595F74u, gen::fn_sub_599408_00599408);
    a0 = s0;
    a1 = 6;
    if (v0 != 0) {
        // 0x00595f88
        charge(ctx, 8);
        jal(ctx, 0x595F88u, gen::fn_sub_59BC88_0059bc88);
        a0 = s0;
        a1 = 6;
        s2 = v0;
        jal(ctx, 0x595F98u, gen::fn_sub_59BCB8_0059bcb8);
        s2 = s2 | v0;
        a0 = s0;
    }
    // 0x00595fa8
    charge(ctx, 6);
    a1 = 6;
    jal(ctx, 0x595FA8u, gen::fn_sub_599408_00599408);
    a0 = s0;
    a1 = 7;
    s1 = 1;
    if (v0 != 0) {
        // 0x00595fc0
        charge(ctx, 7);
        jal(ctx, 0x595FC0u, gen::fn_sub_59BC88_0059bc88);
        a0 = s0;
        a1 = 7;
        s1 = v0;
        jal(ctx, 0x595FD0u, gen::fn_sub_59BCB8_0059bcb8);
        s1 = s1 | v0;
    }
    // 0x00595fdc
    charge(ctx, 2);
    v0 = 0;
    if (s2 != 0) {
        // 0x00595fe4
        charge(ctx, 2);
        v0 = 1;
        if (s1 == 0) {
            // 0x00595fec
            charge(ctx, 1);
            v0 = 0;
        }
    }
    // 0x00595ff0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00596008 sub_596008 -- 48 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The stream params: sub_596038, sub_5960E0, sub_596168.
void sub_596008(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00596008
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x596014u, gen::fn_sub_596038_00596038);
    a0 = s0;
    jal(ctx, 0x59601Cu, gen::fn_sub_5960E0_005960e0);
    a0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_596168_00596168(ctx);  // tail call
}

// 0x00596038 sub_596038 -- 212 bytes, 2 chunks; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// The audio / video presence params (sub_589550 / sub_589530) and their copy into the header object (+3512 / +3516).
void sub_596038(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00596038
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 1;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    s0 = addiu(s1, 2572);
    lw(v0, s0, 20);
    if (v0 != v1) {
        lw(a2, s0, 24);
    } else {
        // 0x00596060
        charge(ctx, 4);
        a1 = 1;
        jal(ctx, 0x596060u, gen::fn_sub_589550_00589550);
        if (v0 != 0) {
            lw(a2, s0, 24);
        } else {
            // 0x00596070
            charge(ctx, 5);
            a0 = s1;
            a1 = 1;
            jal(ctx, 0x596074u, gen::fn_sub_589530_00589530);
            if (v0 == 0) {
                sw(zero, s0, 20);
            }
            // 0x00596084
            charge(ctx, 1);
            lw(a2, s0, 24);
        }
    }
    // 0x00596088
    charge(ctx, 3);
    v0 = 1;
    if (a2 != v0) {
        lw(a1, s0, 20);
    } else {
        // 0x00596094
        charge(ctx, 5);
        a0 = s1;
        a1 = 2;
        jal(ctx, 0x596098u, gen::fn_sub_589550_00589550);
        if (v0 != 0) {
            lw(a2, s0, 24);
        } else {
            // 0x005960a8
            charge(ctx, 5);
            a0 = s1;
            a1 = 2;
            jal(ctx, 0x5960ACu, gen::fn_sub_589530_00589530);
            if (v0 != 0) {
                lw(a2, s0, 24);
            } else {
                // 0x005960bc
                charge(ctx, 2);
                sw(zero, s0, 24);
                a2 = 0;
            }
        }
        // 0x005960c4
        charge(ctx, 1);
        lw(a1, s0, 20);
    }
    // 0x005960c8
    charge(ctx, 6);
    a0 = s1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    // 0x00598610
    charge(ctx, 3);
    lw(v1, a0, sfd::kHdrObj);
    if (v1 != 0) {
        // 0x0059861c
        charge(ctx, 3);
        lw(v0, v1, 3512);
        if (i64(v0) < 0) {
            sw(a1, v1, 3512);
        }
        // 0x00598628
        charge(ctx, 3);
        lw(v0, v1, 3516);
        if (i64(v0) < 0) {
            sw(a2, v1, 3516);
        }
    }
    // 0x00598634 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005960E0 sub_5960E0 -- 136 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Adjusts the sync param 15 from the video / audio presence (sub_599240).
void sub_5960E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005960e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    s0 = addiu(s1, 2572);
    lw(v0, s0, 24);
    if (v0 != 0) {
        lw(v0, s0, 20);
    } else {
        // 0x00596104
        charge(ctx, 4);
        lw(v1, s0, 60);
        v0 = 2;
        if (v1 != v0) {
            lw(v0, s0, 20);
        } else {
            // 0x00596114
            charge(ctx, 4);
            a1 = 15;
            a2 = 1;
            jal(ctx, 0x596118u, gen::fn_sub_599240_00599240);
            lw(v0, s0, 20);
        }
    }
    // 0x00596124
    charge(ctx, 2);
    if (v0 != 0) {
        ld(s0, sp, 0x0);
        // 0x00596158 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059612c
    charge(ctx, 4);
    lw(v1, s0, 60);
    v0 = 1;
    ld(s0, sp, 0x0);
    if (v1 != v0) {
        // 0x00596158 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059613c
    charge(ctx, 7);
    a0 = s1;
    ld(s1, sp, 0x8);
    a1 = 15;
    ld(ra, sp, 0x10);
    a2 = 2;
    sp = addiu(sp, 0x20);
    gen::fn_sub_599240_00599240(ctx);  // tail call
}

// 0x00596168 sub_596168 -- 196 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// The sync-master param 25 from the video / audio presence (audio clock when there is one, sub_5A1B58, param 72).
void sub_596168(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00596168
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a3 = 1;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    a1 = addiu(s1, 2572);
    a2 = 2;
    lw(v0, a1, 24);
    lw(v1, a1, 20);
    v0 = v0 ^ a3;
    a1 = sltiu(v0, 1);
    v1 = v1 ^ a3;
    v0 = a1 | 0x2;
    if (v1 == 0) a1 = v0;
    s0 = 2;
    if (a1 != a2) {
        // 0x005961ac
        charge(ctx, 3);
        v0 = sltiu(a1, 3);
        if (v0 != 0) {
            // 0x005961b8
            charge(ctx, 2);
            s0 = 1;
            if (a1 != a3) {
                // 0x005961c0
                charge(ctx, 2);
                s0 = 3;
            }
            goto L_0059620c;
        }
        v0 = 3;
        // 0x005961c8
        charge(ctx, 2);
        s0 = 3;
        if (a1 != v0) {
            goto L_0059620c;
        }
        // 0x005961d0
        charge(ctx, 5);
        a1 = 25;
        jal(ctx, 0x5961D0u, gen::fn_sub_599408_00599408);
        s0 = v0;
        a0 = s1;
        if (s0 == 0) {
            // 0x005961e4
            charge(ctx, 4);
            jal(ctx, 0x5961E4u, gen::fn_sub_5A1B58_005a1b58);
            if (v0 != 0) {
                s0 = 3;
                goto L_0059620c;
            }
            // 0x005961f4
            charge(ctx, 5);
            a0 = s1;
            a1 = 72;
            jal(ctx, 0x5961F8u, gen::fn_sub_599408_00599408);
            a0 = s1;
            if (v0 == 0) {
                // 0x00596208
                charge(ctx, 1);
                s0 = 3;
                goto L_0059620c;
            }
        }
        goto L_00596210;
    }
L_0059620c:
    charge(ctx, 1);
    a0 = s1;
L_00596210:
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    a2 = s0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    a1 = 25;
    sp = addiu(sp, 0x20);
    gen::fn_sub_599240_00599240(ctx);  // tail call
}

// 0x00596230 sub_596230 -- 160 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Status 3 (ready): request 2 -> 2, 3 -> 3, 4 / 6 -> 4 when ready to start (sub_596348, sub_597340).
void sub_596230(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00596230
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 3;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    lw(v1, s0, 76);
    lw(s1, s0, 72);
    if (v1 == v0) {
        // 0x00596298
        charge(ctx, 2);
        s1 = 3;
    L_005962b8:
        charge(ctx, 2);
        v0 = s1;
        ld(s0, sp, 0x0);
    } else {
        // 0x00596254
        charge(ctx, 3);
        v0 = slti(v1, 4);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 4;
        if (cc) {
            // 0x00596278
            charge(ctx, 2);
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = 6;
            if (!cc) {
                // 0x00596280
                charge(ctx, 2);
                cc = v1 == v0;  // the condition, before the delay slot changes it
                v0 = s1;
                if (cc) {
                    goto L_005962a0;
                }
                // 0x00596288
                charge(ctx, 2);
                ld(s0, sp, 0x0);
                // 0x005962c0 (the shared epilogue, written out on this path)
                charge(ctx, 4);
                ld(s1, sp, 0x8);
                ld(ra, sp, 0x10);
                sp = addiu(sp, 0x20);
                return;
            }
        L_005962a0:
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x5962A0u, gen::fn_sub_596348_00596348);
            a0 = s0;
            if (v0 != 0) {
                // 0x005962b0
                charge(ctx, 2);
                s1 = 4;
                jal(ctx, 0x5962B0u, gen::fn_sub_597340_00597340);
            }
            goto L_005962b8;
        }
        // 0x00596260
        charge(ctx, 3);
        v0 = 2;
        cc = v1 == v0;  // the condition, before the delay slot changes it
        v0 = s1;
        if (cc) {
            // 0x00596290
            charge(ctx, 2);
            s1 = 2;
            goto L_005962b8;
        }
        // 0x0059626c
        charge(ctx, 2);
        ld(s0, sp, 0x0);
    }
    // 0x005962c0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005962D0 sub_5962D0 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Status 4 (playing): the end checks (sub_596898) and the frame step (sub_5963B0); request 6 -> 6.
void sub_5962D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005962d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5962DCu, gen::fn_sub_596898_00596898);
    a0 = s0;
    if (v0 == 0) {
        // 0x005962ec
        charge(ctx, 4);
        jal(ctx, 0x5962ECu, gen::fn_sub_5963B0_005963b0);
        if (v0 != 0) {
            goto L_005962fc;
        }
        lw(a1, s0, 76);
        // 0x00596308
        charge(ctx, 4);
        lw(a0, s0, 72);
        v0 = slti(a1, 2);
        v1 = slti(a1, 5);
        if (v0 == 0) {
            // 0x00596318
            charge(ctx, 2);
            v0 = a0;
            if (v1 == 0) {
                // 0x00596320
                charge(ctx, 3);
                v1 = 6;
                v0 = a1 ^ v1;
                if (v0 == 0) a0 = v1;
                goto L_0059632c;
            }
            // 0x00596330 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(s0, sp, 0x0);
            ld(ra, sp, 0x8);
            sp = addiu(sp, 0x10);
            return;
        }
    L_0059632c:
        charge(ctx, 1);
        v0 = a0;
        // 0x00596330 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_005962fc:
    charge(ctx, 2);
    lw(v0, s0, 72);
    // 0x00596330 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00596348 sub_596348 -- 100 bytes; frame 0x10: ra sp+0x0
// Whether playback may start: 1 unless params 14 and 5 are set, +4064 is clear and +4092 is below param 45 (+2752);
//   then the input end (sub_596978).
void sub_596348(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00596348
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a0;
    sd(ra, sp, 0x0);
    a2 = addiu(a1, 2572);
    v0 = 1;
    lw(v1, a2, 56);
    a1 = addiu(a1, 3376);
    if (v1 != 0) {
        // 0x00596368
        charge(ctx, 3);
        lw(v1, a2, 20);
        if (v1 == 0) {
            ld(ra, sp, 0x0);
        } else {
            // 0x00596374
            charge(ctx, 3);
            lw(v1, a1, 688);
            if (v1 != 0) {
                ld(ra, sp, 0x0);
            } else {
                // 0x00596380
                charge(ctx, 5);
                lw(v1, a1, 716);
                lw(a1, a2, 180);
                v1 = slt(v1, a1);
                if (v1 != 0) {
                    // 0x00596394
                    charge(ctx, 3);
                    jal(ctx, 0x596394u, gen::fn_sub_596978_00596978);
                    v0 = sltu(0, v0);
                    goto L_005963a0;
                }
                ld(ra, sp, 0x0);
            }
        }
        // 0x005963a4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_005963a0:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x005963a4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x005963B0 sub_5963B0 -- 172 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// Under the lock: the frame step: shows the next frame when due (sub_596460) or releases the shown one (sub_5965E0),
//   sub_595868.
void sub_5963B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005963b0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = addiu(s0, 2384);
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x28);
    a0 = sp;
    jal(ctx, 0x5963CCu, gen::fn_sub_58C100_0058c100);
    lw(v0, s1, 32);
    s2 = 0;
    a0 = s0;
    if (v0 != 0) {
        // 0x00596418
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x596418u, gen::fn_sub_5965E0_005965e0);
        a0 = s0;
        a1 = 0;
        if (v0 != 0) {
            // 0x0059642c
            charge(ctx, 3);
            link(ctx, 0x59642Cu);  // $ra first: the delay slot below depends on it
            sw(zero, s1, 32);
            call(ctx, gen::fn_sub_595868_00595868);
            s2 = v0;
        }
    } else {
        // 0x005963e4
        charge(ctx, 4);
        jal(ctx, 0x5963E4u, gen::fn_sub_596460_00596460);
        a1 = 1;
        if (v0 != 0) {
            // 0x005963f4
            charge(ctx, 9);
            lw(v1, s1, 36);
            v0 = 1;
            sw(v0, s1, 32);
            a0 = s0;
            v1 = addiu(v1, 1);
            link(ctx, 0x596408u);  // $ra first: the delay slot below depends on it
            sw(v1, s1, 36);
            call(ctx, gen::fn_sub_595868_00595868);
            s2 = v0;
        }
    }
    // 0x00596438
    charge(ctx, 9);
    a0 = sp;
    jal(ctx, 0x596438u, gen::fn_sub_58C118_0058c118);
    v0 = s2;
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00596460 sub_596460 -- 380 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// Whether the next frame is due: playing, not paused, the inputs flowing (sub_5966C0, sub_589D30, sub_59BCD0,
//   sub_596760), the time (sub_59A168) against the frame time (sub_59A560).
void sub_596460(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00596460
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a1 = 67;
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x20);
    s1 = addiu(s0, 2384);
    jal(ctx, 0x596478u, gen::fn_sub_599408_00599408);
    a0 = s0;
    if (v0 != 0) {
        // 0x00596488
        charge(ctx, 4);
        a1 = 15;
        jal(ctx, 0x596488u, gen::fn_sub_599408_00599408);
        if (v0 == 0) {
            ld(s0, sp, 0x10);
        } else {
            // 0x00596498
            charge(ctx, 3);
            lw(v1, s0, 80);
            v0 = 0;
            if (v1 != 0) {
                goto L_005965c8;
            }
            // 0x005964a4
            charge(ctx, 4);
            lw(a0, s0, 72);
            v1 = 4;
            if (a0 == v1) {
                // 0x005964b4
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x5964B4u, gen::fn_sub_5966C0_005966c0);
                if (v0 != 0) {
                    v0 = 0;
                } else {
                    // 0x005964c4
                    charge(ctx, 6);
                    a0 = s0;
                    a1 = 5;
                    jal(ctx, 0x5964C8u, gen::fn_sub_599408_00599408);
                    v1 = 1;
                    a0 = s0;
                    if (v0 == v1) {
                        // 0x005964dc
                        charge(ctx, 3);
                        lw(v1, s1, 40);
                        v0 = 0;
                        if (v1 != 0) {
                            // 0x005964e8
                            charge(ctx, 1);
                            a0 = s0;
                            goto L_005964ec;
                        }
                        goto L_005965c8;
                    }
                L_005964ec:
                    charge(ctx, 5);
                    a1 = 6;
                    jal(ctx, 0x5964ECu, gen::fn_sub_599408_00599408);
                    v1 = 1;
                    a0 = s0;
                    if (v0 == v1) {
                        // 0x00596500
                        charge(ctx, 4);
                        a1 = 2;
                        jal(ctx, 0x596500u, gen::fn_sub_589D30_00589d30);
                        cc = i64(v0) > 0;  // the condition, before the delay slot changes it
                        v0 = 0;
                        if (!cc) {
                            // 0x00596510
                            charge(ctx, 1);
                            a0 = s0;
                            goto L_00596514;
                        }
                        goto L_005965c8;
                    }
                L_00596514:
                    charge(ctx, 4);
                    a1 = 1;
                    jal(ctx, 0x596514u, gen::fn_sub_59BCD0_0059bcd0);
                    a0 = s0;
                    if (v0 != 0) {
                        // 0x00596524
                        charge(ctx, 4);
                        a1 = 0;
                        jal(ctx, 0x596524u, gen::fn_sub_589D30_00589d30);
                        cc = i64(v0) > 0;  // the condition, before the delay slot changes it
                        v0 = 0;
                        if (!cc) {
                            goto L_00596534;
                        }
                        goto L_005965c8;
                    }
                L_00596534:
                    charge(ctx, 6);
                    a0 = s0;
                    a1 = 5;
                    jal(ctx, 0x596538u, gen::fn_sub_599408_00599408);
                    v1 = 1;
                    if (v0 != v1) {
                        a1 = sp;
                    } else {
                        // 0x0059654c
                        charge(ctx, 4);
                        a0 = s0;
                        jal(ctx, 0x59654Cu, gen::fn_sub_596760_00596760);
                        cc = v0 != 0;  // the condition, before the delay slot changes it
                        v0 = 0;
                        if (!cc) {
                            // 0x0059655c
                            charge(ctx, 1);
                            a1 = sp;
                            goto L_00596560;
                        }
                        goto L_005965c8;
                    }
                L_00596560:
                    charge(ctx, 17);
                    a2 = addiu(sp, 0x4);
                    a0 = s0;
                    jal(ctx, 0x596564u, gen::fn_sub_59A168_0059a168);
                    v1 = addiu(s0, 3376);
                    lw(s1, v1, 648);
                    a0 = s0;
                    a1 = 68;
                    link(ctx, 0x59657Cu);  // $ra first: the delay slot below depends on it
                    lw(s0, v1, 644);
                    call(ctx, gen::fn_sub_599408_00599408);
                    a1 = s1;
                    a2 = 0xF0000;
                    a0 = v0;
                    a2 = a2 | 0x4240;
                    jal(ctx, 0x596590u, gen::fn_sub_57BAF0_0057baf0);
                    lw(a0, sp, 0x0);
                    s0 = subu(s0, v0);
                    if (i64(a0) > 0) {
                        // 0x005965a4
                        charge(ctx, 2);
                        lw(a1, sp, 0x4);
                        if (i64(s0) <= 0) {
                            goto L_005965ac;
                        }
                        // 0x005965b8
                        charge(ctx, 4);
                        a2 = s0;
                        a3 = s1;
                        jal(ctx, 0x5965BCu, gen::fn_sub_59A560_0059a560);
                        v0 = sltiu(v0, 1);
                        goto L_005965c8;
                    }
                L_005965ac:
                    charge(ctx, 2);
                    v0 = 0;
                }
                goto L_005965c8;
            }
            ld(s0, sp, 0x10);
        }
        // 0x005965cc (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_005965c8:
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    // 0x005965cc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005966C0 sub_5966C0 -- 156 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Whether an input has run dry: param 5 / 6 inputs (sub_59BCB8) or any of the 8 streams (sub_589D10).
void sub_5966C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005966c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 5;
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x5966D4u, gen::fn_sub_599408_00599408);
    a0 = s1;
    if (v0 != 0) {
        // 0x005966e4
        charge(ctx, 4);
        a1 = 6;
        jal(ctx, 0x5966E4u, gen::fn_sub_59BCB8_0059bcb8);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (!cc) {
            goto L_005966f4;
        }
        // 0x00596748 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_005966f4:
    charge(ctx, 5);
    a0 = s1;
    a1 = 6;
    jal(ctx, 0x5966F8u, gen::fn_sub_599408_00599408);
    s0 = 0;
    if (v0 != 0) {
        // 0x00596708
        charge(ctx, 5);
        a0 = s1;
        a1 = 7;
        jal(ctx, 0x59670Cu, gen::fn_sub_59BCB8_0059bcb8);
        s0 = 0;
        if (v0 == 0) {
            goto L_00596728;
        }
    L_0059671c:
        charge(ctx, 2);
        v0 = 1;
        // 0x00596748 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_00596728:
    charge(ctx, 1);
    a1 = s0;
    for (;;) {
        // 0x0059672c
        charge(ctx, 5);
        s0 = addiu(s0, 1);
        a0 = s1;
        jal(ctx, 0x596730u, gen::fn_sub_589D10_00589d10);
        v1 = sltiu(s0, 8);
        if (v0 != 0) {
            backedge(ctx);
            goto L_0059671c;
        }
        // 0x00596740
        charge(ctx, 2);
        a1 = s0;
        if (v1 != 0) {
            backedge(ctx);
            continue;
        }
        break;
    }
    // 0x00596748 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00596898 sub_596898 -- 108 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Play-end checks: the end time (sub_596908), the input end (sub_596978), the video end (sub_596A40), the audio end
//   (sub_596A98); any one ends it (sub_596B28).
void sub_596898(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00596898
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5968A4u, gen::fn_sub_596908_00596908);
    a0 = s0;
    if (v0 == 0) {
        // 0x005968b4
        charge(ctx, 4);
        jal(ctx, 0x5968B4u, gen::fn_sub_596978_00596978);
        a0 = s0;
        if (v0 != 0) {
            goto L_005968e4;
        }
        // 0x005968c4
        charge(ctx, 4);
        jal(ctx, 0x5968C4u, gen::fn_sub_596A40_00596a40);
        a0 = s0;
        if (v0 != 0) {
            goto L_005968e4;
        }
        // 0x005968d4
        charge(ctx, 4);
        jal(ctx, 0x5968D4u, gen::fn_sub_596A98_00596a98);
        if (v0 != 0) {
            goto L_005968e4;
        }
        ld(s0, sp, 0x0);
        // 0x005968f8
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_005968e4:
    charge(ctx, 5);
    a0 = s0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_596B28_00596b28(ctx);  // tail call
}

// 0x00596908 sub_596908 -- 108 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// Whether the end time (params 20 / 21) is reached (sub_59A168, sub_56F4B8).
void sub_596908(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00596908
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = addiu(a0, 2572);
    sd(s0, sp, 0x10);
    a1 = si(-4);
    sd(s1, sp, 0x18);
    v0 = 0;
    sd(ra, sp, 0x20);
    lw(s0, v1, 80);
    lw(s1, v1, 84);
    if (s0 != a1) {
        // 0x00596930
        charge(ctx, 9);
        a2 = addiu(sp, 0x4);
        a1 = sp;
        jal(ctx, 0x596934u, gen::fn_sub_59A168_0059a168);
        v0 = 0;
        lw(v1, sp, 0x0);
        a2 = s0;
        a3 = s1;
        a0 = v1;
        if (i64(v1) >= 0) {
            // 0x00596954
            charge(ctx, 3);
            link(ctx, 0x596954u);  // $ra first: the delay slot below depends on it
            lw(a1, sp, 0x4);
            call(ctx, gen::fn_sub_56F4B8_0056f4b8);
            v0 = sltiu(v0, 1);
        }
    }
    // 0x00596960 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00596978 sub_596978 -- 200 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// The input end by the sync master (param 25): video, audio, both or either.
void sub_596978(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00596978
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    v1 = addiu(s0, 2572);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v0, v1, 24);
    a1 = 6;
    if (v0 == 0) {
        // 0x005969a0
        charge(ctx, 3);
        lw(v1, v1, 20);
        v0 = 1;
        if (v1 != 0) {
            // 0x005969ac
            charge(ctx, 1);
            a1 = 6;
            goto L_005969b0;
        }
    L_00596a28:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
        // 0x00596a2c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_005969b0:
    charge(ctx, 14);
    a0 = s0;
    jal(ctx, 0x5969B0u, gen::fn_sub_59BCB8_0059bcb8);
    a0 = s0;
    a1 = 7;
    s2 = v0;
    jal(ctx, 0x5969C0u, gen::fn_sub_59BCB8_0059bcb8);
    a0 = s0;
    a1 = 25;
    s1 = v0;
    jal(ctx, 0x5969D0u, gen::fn_sub_599408_00599408);
    v1 = v0;
    v0 = 1;
    a0 = 0;
    if (v1 == v0) {
        // 0x00596a10
        charge(ctx, 2);
        a0 = s1;
    L_00596a24:
        charge(ctx, 1);
        v0 = a0;
        goto L_00596a28;
    }
    // 0x005969e8
    charge(ctx, 2);
    if (v1 == 0) {
        a0 = s1 & s2;
        goto L_00596a24;
    }
    // 0x005969f0
    charge(ctx, 3);
    v0 = 2;
    cc = v1 == v0;  // the condition, before the delay slot changes it
    v0 = 3;
    if (cc) {
        // 0x00596a18
        charge(ctx, 2);
        a0 = s2;
        goto L_00596a24;
    }
    // 0x005969fc
    charge(ctx, 2);
    cc = v1 == v0;  // the condition, before the delay slot changes it
    v0 = a0;
    if (cc) {
        // 0x00596a20
        charge(ctx, 1);
        a0 = s1 | s2;
        goto L_00596a24;
    }
    // 0x00596a04
    charge(ctx, 2);
    ld(s0, sp, 0x0);
    // 0x00596a2c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00596A40 sub_596A40 -- 88 bytes; frame 0x10: ra sp+0x0
// The video end while playing (sub_599E08).
void sub_596A40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00596a40
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a0;
    sd(ra, sp, 0x0);
    v1 = 4;
    lw(v0, a1, 72);
    a2 = addiu(a1, 2384);
    if (v0 == v1) {
        // 0x00596a5c
        charge(ctx, 4);
        lw(v0, a1, 80);
        v1 = 1;
        cc = v0 == v1;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x00596a6c
            charge(ctx, 3);
            lw(v0, a2, 32);
            if (v0 == v1) {
                goto L_00596a78;
            }
            // 0x00596a80
            charge(ctx, 3);
            jal(ctx, 0x596A80u, gen::fn_sub_599E08_00599e08);
            v0 = sltu(0, v0);
        }
        // 0x00596a8c (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_00596a78:
    charge(ctx, 2);
    v0 = 0;
    // 0x00596a8c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00596A98 sub_596A98 -- 144 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// The audio end while playing: the audio time (sub_59A028) against param 54 (sub_59A560).
void sub_596A98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00596a98
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 4;
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(ra, sp, 0x18);
    lw(v0, s0, 72);
    a1 = addiu(s0, 2384);
    if (v0 == v1) {
        // 0x00596ab8
        charge(ctx, 4);
        lw(v0, s0, 80);
        v1 = 1;
        cc = v0 == v1;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x00596ac8
            charge(ctx, 3);
            lw(v0, a1, 32);
            a1 = sp;
            if (v0 == v1) {
                goto L_00596ae4;
            }
            // 0x00596ad4
            charge(ctx, 4);
            a2 = addiu(sp, 0x4);
            jal(ctx, 0x596AD4u, gen::fn_sub_59A028_0059a028);
            lw(v1, sp, 0x0);
            if (v0 != 0) {
                goto L_00596ae4;
            }
            // 0x00596af0
            charge(ctx, 2);
            a0 = s0;
            if (i64(v1) >= 0) {
                // 0x00596af8
                charge(ctx, 8);
                a1 = 54;
                jal(ctx, 0x596AF8u, gen::fn_sub_599408_00599408);
                a1 = 1000;
                lw(a2, sp, 0x0);
                a0 = v0;
                link(ctx, 0x596B0Cu);  // $ra first: the delay slot below depends on it
                lw(a3, sp, 0x4);
                call(ctx, gen::fn_sub_59A560_0059a560);
                v0 = sltu(0, v0);
            }
        }
        // 0x00596b18 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_00596ae4:
    charge(ctx, 2);
    v0 = 0;
    // 0x00596b18 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00596C28 sub_596C28 -- 152 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// Creates an SFD handle: the creation params (sub_596CC0), a free table slot (sub_596D28; error -16776698), the
//   handle (sub_596D68), kept in the table 0x7B4774.
void sub_596C28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00596c28
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x7B0000;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    s3 = addiu(v0, 18292);  // &0x7B4774
    jal(ctx, 0x596C4Cu, gen::fn_sub_596CC0_00596cc0);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x00596c5c
        charge(ctx, 6);
        jal(ctx, 0x596C5Cu, gen::fn_sub_596D28_00596d28);
        s0 = v0;
        v0 = si(-1);
        a0 = s1;
        if (s0 != v0) {
            // 0x00596c90
            charge(ctx, 5);
            a1 = s2;
            jal(ctx, 0x596C90u, gen::fn_sub_596D68_00596d68);
            v1 = sll(s0, 2);
            v1 = addu(v1, s3);
            sw(v0, v1, 0);
        } else {
            // 0x00596c74
            charge(ctx, 6);
            a1 = lui(0xFF00);
            a0 = 0;
            a1 = a1 | 0x206;
            jal(ctx, 0x596C7Cu, gen::fn_sub_58BE40_0058be40);
            v0 = 0;
        }
    }
    // 0x00596ca4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00596CC0 sub_596CC0 -- 100 bytes; frame 0x10: ra sp+0x0
// Checks the creation params: a work buffer (+4; error -16776700) of at least 0x37D0 bytes (+64; error -16776699).
void sub_596CC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00596cc0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = a0;
    sd(ra, sp, 0x0);
    lw(v0, v1, 4);
    a0 = 0;
    if (v0 == 0) {
        // 0x00596cd8
        charge(ctx, 5);
        a1 = lui(0xFF00);
        ld(ra, sp, 0x0);
        a1 = a1 | 0x204;
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00596cf0
    charge(ctx, 4);
    lw(v0, v1, 64);
    v0 = sltiu(v0, 14288);
    ld(ra, sp, 0x0);
    if (v0 == 0) {
        // 0x00596d18
        charge(ctx, 3);
        v0 = 0;
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00596d00
    charge(ctx, 5);
    a1 = lui(0xFF00);
    a0 = 0;
    a1 = a1 | 0x205;
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x00596D28 sub_596D28 -- 64 bytes; leaf frame (no stack)
// The first free slot of the 8-handle table 0x7B4774; -1 when full.
void sub_596D28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00596d28
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    a1 = 0;
    a2 = addiu(v0, 18292);  // &0x7B4774
    lw(v1, a2, 0);  // 0x7B4774
    for (;;) {
        // 0x00596d38
        charge(ctx, 5);
        a2 = addiu(a2, 4);
        v0 = a1;
        a1 = addiu(a1, 1);
        a0 = slti(a1, 8);
        if (v1 == 0) {
            break;
        }
        // 0x00596d4c
        charge(ctx, 4);
        if (a0 == 0) {
            goto L_00596d5c_3;
        }
        lw(v1, a2, 0);
        backedge(ctx);
    }
    // 0x00596d60 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_00596d5c_3:
    charge(ctx, 1);
    v0 = si(-1);
    // 0x00596d60 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00596D68 sub_596D68 -- 556 bytes; frame 0x30: s2 sp+0x10, s4 sp+0x20, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, ra sp+0x28
// Builds an SFD handle in the 32-aligned work buffer: clears it, copies the 68-byte creation params, initialises its
//   parts (the header info, sub_596F98, sub_597000, sub_597088, the error record, the two 400-byte param tables from
//   0x7B4570, the time record, the streams sub_588740, the transfers sub_59B620, the header object, status 3); the
//   handle or 0.
void sub_596D68(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00596d68
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s4, sp, 0x20);
    s4 = a1;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x28);
    lw(a3, s2, 64);
    lw(s0, s2, 60);
    a2 = srl(a3, 2);
    if (s0 != 0) {
        // 0x00596da0
        charge(ctx, 4);
        v1 = addiu(a3, -1);
        v1 = sltiu(v1, 28576);
        if (v1 != 0) {
            // 0x00596db0
            charge(ctx, 4);
            t0 = 0x7B0000;
            lw(v1, t0, 18360);  // 0x7B47B8
            a0 = s0;
            if (v1 != 0) {
                // 0x00596dc0
                charge(ctx, 2);
                if (v1 == a3) {
                    // 0x00596dc8
                    charge(ctx, 1);
                    a0 = s0;
                    goto L_00596dcc;
                }
                ld(s0, sp, 0x0);
                // 0x00596f78 (the shared epilogue, written out on this path)
                charge(ctx, 7);
                ld(s1, sp, 0x8);
                ld(s2, sp, 0x10);
                ld(s3, sp, 0x18);
                ld(s4, sp, 0x20);
                ld(ra, sp, 0x28);
                sp = addiu(sp, 0x30);
                return;
            }
        L_00596dcc:
            charge(ctx, 16);
            a1 = 0;
            link(ctx, 0x596DD0u);  // $ra first: the delay slot below depends on it
            sw(a3, t0, 18360);
            call(ctx, gen::fn_sub_575880_00575880);
            lw(v0, s2, 4);
            v1 = addiu(s0, 31);
            a0 = si(-32);
            a1 = s2 & 0x7;
            v0 = addiu(v0, 31);
            s1 = v1 & a0;
            v0 = v0 & a0;
            sw(zero, s1, 76);
            sw(v0, s2, 4);
            v0 = s2;
            sw(zero, s1, 72);
            v1 = s1;
            if (a1 == 0) {
                // 0x00596e70
                charge(ctx, 1);
                a0 = addiu(s2, 64);
                for (;;) {
                    // 0x00596e74
                    charge(ctx, 13);
                    ld(a1, v0, 0);
                    ld(a2, v0, 8);
                    ld(a3, v0, 16);
                    ld(t0, v0, 24);
                    sd(a1, v1, 0);
                    sd(a2, v1, 8);
                    sd(a3, v1, 16);
                    sd(t0, v1, 24);
                    v0 = addiu(v0, 32);
                    v1 = addiu(v1, 32);
                    if (v0 == a0) {
                        break;
                    }
                    backedge(ctx);
                }
            } else {
                // 0x00596e0c
                charge(ctx, 1);
                a0 = addiu(s2, 64);
                for (;;) {
                    // 0x00596e10
                    charge(ctx, 21);
                    ldl(a1, v0, 7);
                    ldr(a1, v0, 0);
                    ldl(a2, v0, 15);
                    ldr(a2, v0, 8);
                    ldl(a3, v0, 23);
                    ldr(a3, v0, 16);
                    ldl(t0, v0, 31);
                    ldr(t0, v0, 24);
                    sdl(a1, v1, 7);
                    sdr(a1, v1, 0);
                    sdl(a2, v1, 15);
                    sdr(a2, v1, 8);
                    sdl(a3, v1, 23);
                    sdr(a3, v1, 16);
                    sdl(t0, v1, 31);
                    sdr(t0, v1, 24);
                    v0 = addiu(v0, 32);
                    v1 = addiu(v1, 32);
                    if (v0 == a0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00596e64
                charge(ctx, 2);
            }
            // 0x00596ea8
            charge(ctx, 37);
            lw(a0, v0, 0);
            s3 = 1;
            s0 = 0x7B0000;
            sw(a0, v1, 0);
            a0 = addiu(s1, 120);
            sw(zero, s1, 80);
            s0 = addiu(s0, 17776);  // &0x7B4570
            sw(s3, s1, 68);
            sw(zero, s1, 84);
            sw(zero, s1, 88);
            link(ctx, 0x596ED0u);  // $ra first: the delay slot below depends on it
            sw(zero, s1, 92);
            call(ctx, gen::fn_sub_58B140_0058b140);
            a0 = addiu(s1, 2316);
            jal(ctx, 0x596ED8u, gen::fn_sub_596F98_00596f98);
            a0 = addiu(s1, 2384);
            jal(ctx, 0x596EE0u, gen::fn_sub_597000_00597000);
            a0 = addiu(s1, 14016);
            jal(ctx, 0x596EE8u, gen::fn_sub_597088_00597088);
            a0 = addiu(s1, 2552);
            jal(ctx, 0x596EF0u, gen::fn_sub_58BE28_0058be28);
            a0 = addiu(s1, 2572);
            a1 = s0;
            a2 = 400;
            jal(ctx, 0x596F00u, gen::fn_sub_575410_00575410);
            a0 = addiu(s1, 2972);
            a2 = 400;
            a1 = s0;
            jal(ctx, 0x596F10u, gen::fn_sub_575410_00575410);
            a0 = s1;
            a1 = addiu(s1, 3376);
            jal(ctx, 0x596F1Cu, gen::fn_sub_599810_00599810);
            a0 = s1;
            a1 = addiu(s1, 4880);
            a2 = s2;
            jal(ctx, 0x596F2Cu, gen::fn_sub_588740_00588740);
            if (v0 != 0) {
                v0 = 0;
            } else {
                // 0x00596f3c
                charge(ctx, 11);
                a2 = s2;
                a3 = s4;
                a0 = s1;
                a1 = addiu(s1, 7984);
                jal(ctx, 0x596F48u, gen::fn_sub_59B620_0059b620);
                a0 = addiu(s1, sfd::kHdrObj);
                jal(ctx, 0x596F50u, gen::fn_sub_5982E0_005982e0);
                a0 = s1;
                jal(ctx, 0x596F58u, gen::fn_sub_5971D0_005971d0);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = 0;
                if (!cc) {
                    // 0x00596f68
                    charge(ctx, 3);
                    sw(s3, s1, 72);
                    v0 = s1;
                    sw(s3, s1, 76);
                }
            }
            goto L_00596f74;
        }
        ld(s0, sp, 0x0);
        // 0x00596f78 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
L_00596f74:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x00596f78 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00596F98 sub_596F98 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Resets the decode-info record (handle+2316).
void sub_596F98(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00596f98
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    a2 = 16;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x596FACu, gen::fn_sub_575880_00575880);
    v1 = si(-1);
    v0 = 1;
    sw(v1, s0, 44);
    sw(v0, s0, 28);
    sw(zero, s0, 0);
    sw(zero, s0, 4);
    sw(zero, s0, 8);
    sw(zero, s0, 12);
    sw(zero, s0, 16);
    sw(zero, s0, 20);
    sw(zero, s0, 24);
    sw(zero, s0, 32);
    sw(v1, s0, 36);
    sw(v1, s0, 40);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00597000 sub_597000 -- 120 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Resets the counters record (handle+2384) and its four 24-byte sub-records.
void sub_597000(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597000
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    a2 = 42;
    jal(ctx, 0x597014u, gen::fn_sub_575880_00575880);
    sw(zero, s0, 0);
    sw(zero, s0, 4);
    a0 = addiu(s0, 56);
    sw(zero, s0, 8);
    sw(zero, s0, 12);
    sw(zero, s0, 16);
    sw(zero, s0, 24);
    sw(zero, s0, 28);
    sw(zero, s0, 32);
    sw(zero, s0, 36);
    sw(zero, s0, 40);
    sw(zero, s0, 44);
    link(ctx, 0x59704Cu);  // $ra first: the delay slot below depends on it
    sw(zero, s0, 48);
    call(ctx, gen::fn_sub_597078_00597078);
    a0 = addiu(s0, 80);
    jal(ctx, 0x597054u, gen::fn_sub_597078_00597078);
    a0 = addiu(s0, 104);
    jal(ctx, 0x59705Cu, gen::fn_sub_597078_00597078);
    a0 = addiu(s0, 128);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_597078_00597078(ctx);  // tail call
}

// 0x00597078 sub_597078 -- 16 bytes; leaf frame (no stack)
// Clears 24 bytes (three 64-bit words).
void sub_597078(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x00597078
    enter(ctx, 4);  // entry check point + this block's cycles
    sd(zero, a0, 16);
    sd(zero, a0, 0);
    sd(zero, a0, 8);
}

// 0x00597088 sub_597088 -- 120 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// Resets the profile record (handle+14016): six timing slots (sub_59B490) and the totals.
void sub_597088(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597088
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 0;
    sd(s1, sp, 0x8);
    s1 = a0;
    a2 = 56;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = 4;
    jal(ctx, 0x5970A8u, gen::fn_sub_575880_00575880);
    s0 = s1;
    a0 = s0;
    for (;;) {
        // 0x005970b8
        charge(ctx, 5);
        s0 = addiu(s0, 32);
        s2 = addiu(s2, -1);
        jal(ctx, 0x5970BCu, gen::fn_sub_59B490_0059b490);
        if (i64(s2) < 0) {
            break;
        }
        a0 = s0;
        backedge(ctx);
    }
    // 0x005970cc
    charge(ctx, 13);
    a0 = addiu(s1, 160);
    jal(ctx, 0x5970CCu, gen::fn_sub_59B490_0059b490);
    sd(zero, s1, 192);
    sw(zero, s1, 220);
    sd(zero, s1, 200);
    sd(zero, s1, 208);
    sw(zero, s1, 216);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00597100 sub_597100 -- 100 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Adds a1 to the decoded-picture count (handle+2384) and calls the counter callback (param) with (handle, a2,
//   counters).
void sub_597100(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597100
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    s0 = addiu(s1, 2384);
    lw(v0, s0, 0);
    v0 = addu(v0, a1);
    a1 = 36;
    link(ctx, 0x59712Cu);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 0);
    call(ctx, gen::fn_sub_599408_00599408);
    a0 = s1;
    a1 = s2;
    a2 = s0;
    if (v0 != 0) {
        // 0x00597144
        charge(ctx, 2);
        jalr(ctx, 0x597144u, v0.u());
    }
    // 0x0059714c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005971D0 sub_5971D0 -- 24 bytes; frame 0x10: ra sp+0x0
// sub_59BB88(handle, 3).
void sub_5971D0(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005971d0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 3;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59BB88_0059bb88(ctx);  // tail call
}

// 0x005971E8 sub_5971E8 -- 160 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Destroys an SFD handle: handle check (error -16776911), stop (sub_5973C0), the header info (sub_58B158), the
//   streams (sub_588A10), reset (sub_597288), removed from the table 0x7B4774.
void sub_5971E8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005971e8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5971F4u, gen::fn_sub_58C060_0058c060);
    ld(ra, sp, 0x8);
    if (v0 != 0) {
        // 0x00597204
        charge(ctx, 6);
        a1 = lui(0xFF00);
        ld(s0, sp, 0x0);
        a0 = 0;
        a1 = a1 | 0x131;
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00597220
    charge(ctx, 12);
    a0 = s0;
    jal(ctx, 0x597220u, gen::fn_sub_5973C0_005973c0);
    a0 = addiu(s0, 120);
    jal(ctx, 0x597228u, gen::fn_sub_58B158_0058b158);
    a0 = s0;
    jal(ctx, 0x597230u, gen::fn_sub_588A10_00588a10);
    a0 = s0;
    jal(ctx, 0x597238u, gen::fn_sub_597288_00597288);
    a0 = 7;
    a1 = v0;
    v0 = 0x7B0000;
    v1 = addiu(v0, 18292);  // &0x7B4774
    for (;;) {
        // 0x00597250
        charge(ctx, 3);
        lw(v0, v1, 0);
        if (v0 == s0) {
            sw(zero, v1, 0);
        }
        // 0x0059725c
        charge(ctx, 6);
        a0 = addiu(a0, -1);
        v1 = addiu(v1, 4);
        if (i64(a0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00597274
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    v0 = a1;
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00597288 sub_597288 -- 36 bytes; frame 0x10: ra sp+0x0
// Status and request 0, then sub_59BB88.
void sub_597288(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597288
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    a1 = 4;
    sw(zero, v0, 76);
    ld(ra, sp, 0x0);
    sw(zero, v0, 72);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59BB88_0059bb88(ctx);  // tail call
}

// 0x00597330 sub_597330 -- 16 bytes; leaf frame (no stack)
// Request (+76) = 4 (start).
void sub_597330(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00597330
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 4;
    v0 = 0;
    sw(v1, a0, 76);
}

// 0x00597340 sub_597340 -- 40 bytes; frame 0x10: ra sp+0x0
// sub_59BC20(handle, 7, 6, 0, 0).
void sub_597340(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597340
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 7;
    a2 = 6;
    a3 = 0;
    sd(ra, sp, 0x0);
    t0 = 0;
    jal(ctx, 0x597354u, gen::fn_sub_59BC20_0059bc20);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005973C0 sub_5973C0 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Stops a handle: unless at status 1, stops the transfers (my_malloc_1) and rebuilds the handle in recreate mode
//   (0x7B476C, sub_5974A8).
void sub_5973C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005973c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v1, s0, 72);
    v0 = 0;
    if (v1 != a1) {
        // 0x005973e0
        charge(ctx, 4);
        jal(ctx, 0x5973E0u, gen::fn_my_malloc_1_00597448);
        a0 = 1;
        if (v0 == 0) {
            // 0x005973f0
            charge(ctx, 9);
            sw(zero, s0, 76);
            link(ctx, 0x5973F4u);  // $ra first: the delay slot below depends on it
            sw(zero, s0, 72);
            call(ctx, gen::fn_sceInsockSetErrnoMode_1_00597428);
            a0 = s0;
            jal(ctx, 0x5973FCu, gen::fn_sub_5974A8_005974a8);
            a0 = 0;
            s0 = v0;
            jal(ctx, 0x597408u, gen::fn_sceInsockSetErrnoMode_1_00597428);
            v0 = s0;
        }
    }
    // 0x00597414 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00597428 sceInsockSetErrnoMode_1 -- 12 bytes; leaf frame (no stack)
// Sets the recreate switch 0x7B476C.
void sceInsockSetErrnoMode_1(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00597428
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sw(a0, v0, 18284);  // 0x7B476C
}

// 0x00597448 my_malloc_1 -- 92 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Stops the transfers when playing (sub_59BC20); on success status and request 1.
void my_malloc_1(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597448
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 4;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, 72);
    if (v0 != v1) {
        v1 = 1;
    } else {
        // 0x00597468
        charge(ctx, 7);
        a1 = 7;
        a2 = 7;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x597474u, gen::fn_sub_59BC20_0059bc20);
        if (v0 == 0) {
            // 0x00597484
            charge(ctx, 1);
            v1 = 1;
            goto L_00597488;
        }
        ld(s0, sp, 0x0);
        // 0x00597498 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_00597488:
    charge(ctx, 4);
    v0 = 0;
    sw(v1, s0, 76);
    sw(v1, s0, 72);
    ld(s0, sp, 0x0);
    // 0x00597498 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005974A8 sub_5974A8 -- 972 bytes; frame 0x2E0: s0 sp+0x290, s1 sp+0x298, s2 sp+0x2A0, s3 sp+0x2A8, s4 sp+0x2B0, s5 sp+0x2B8, s6 sp+0x2C0, s7 sp+0x2C8, fp sp+0x2D0, ra sp+0x2D8
// Rebuilds a stopped handle in place: saves the creation params and its settings, resets, re-creates it (sub_596D68;
//   error -16776702) and restores the param tables and the settings (sub_58E670, sub_597878 ..).
void sub_5974A8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005974a8
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2E0);
    sd(s0, sp, 0x290);
    s0 = a0;
    v0 = s0 & 0x7;
    sd(s1, sp, 0x298);
    sd(s2, sp, 0x2A0);
    a0 = sp;
    sd(s3, sp, 0x2A8);
    v1 = s0;
    sd(s4, sp, 0x2B0);
    sd(s5, sp, 0x2B8);
    sd(s6, sp, 0x2C0);
    sd(s7, sp, 0x2C8);
    sd(fp, sp, 0x2D0);
    sd(ra, sp, 0x2D8);
    sw(zero, sp, 0x250);
    if (v0 == 0) {
        // 0x00597550
        charge(ctx, 1);
        v0 = addiu(s0, 64);
        for (;;) {
            // 0x00597554
            charge(ctx, 13);
            ld(a1, v1, 0);
            ld(a2, v1, 8);
            ld(a3, v1, 16);
            ld(t0, v1, 24);
            sd(a1, a0, 0);
            sd(a2, a0, 8);
            sd(a3, a0, 16);
            sd(t0, a0, 24);
            v1 = addiu(v1, 32);
            a0 = addiu(a0, 32);
            if (v1 == v0) {
                break;
            }
            backedge(ctx);
        }
    } else {
        // 0x005974ec
        charge(ctx, 1);
        v0 = addiu(s0, 64);
        for (;;) {
            // 0x005974f0
            charge(ctx, 21);
            ldl(a1, v1, 7);
            ldr(a1, v1, 0);
            ldl(a2, v1, 15);
            ldr(a2, v1, 8);
            ldl(a3, v1, 23);
            ldr(a3, v1, 16);
            ldl(t0, v1, 31);
            ldr(t0, v1, 24);
            sdl(a1, a0, 7);
            sdr(a1, a0, 0);
            sdl(a2, a0, 15);
            sdr(a2, a0, 8);
            sdl(a3, a0, 23);
            sdr(a3, a0, 16);
            sdl(t0, a0, 31);
            sdr(t0, a0, 24);
            v1 = addiu(v1, 32);
            a0 = addiu(a0, 32);
            if (v1 == v0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00597544
        charge(ctx, 2);
    }
    // 0x00597588
    charge(ctx, 5);
    lw(v0, v1, 0);
    sw(v0, a0, 0);
    lw(s5, s0, 2604);
    if (s5 != 0) {
        // 0x0059759c
        charge(ctx, 5);
        a0 = s0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x5975A0u, gen::fn_sub_597878_00597878);
        lw(t0, sp, 0x64);
        sw(t0, sp, 0x250);
    }
    // 0x005975b0
    charge(ctx, 25);
    a0 = addiu(s0, 120);
    jal(ctx, 0x5975B0u, gen::fn_sub_58B158_0058b158);
    a0 = s0;
    jal(ctx, 0x5975B8u, gen::fn_sub_588A10_00588a10);
    lw(s6, s0, 2552);
    lw(a2, s0, 2556);
    ldl(v0, s0, 4839);
    ldr(v0, s0, 4832);
    lw(v1, s0, 4840);
    sdl(v0, sp, 0x247);
    sdr(v0, sp, 0x240);
    sw(v1, sp, 0x248);
    lw(s2, s0, sfd::kHdrObj);
    sw(a2, sp, 0x254);
    lw(a3, s0, 4116);
    lw(s7, s0, 3392);
    lw(fp, s0, 4100);
    sw(a3, sp, 0x258);
    lw(t0, s0, 4120);
    sw(t0, sp, 0x25C);
    lw(v0, s0, 3400);
    sw(v0, sp, 0x260);
    lw(v1, s0, 4060);
    sw(v1, sp, 0x264);
    if (s2 == 0) {
        // 0x00597640
        charge(ctx, 5);
        sw(zero, sp, 0x278);
        sw(zero, sp, 0x274);
        sw(zero, sp, 0x270);
        sw(zero, sp, 0x26C);
        sw(zero, sp, 0x268);
    } else {
        // 0x00597614
        charge(ctx, 11);
        lw(a0, s2, 3536);
        sw(a0, sp, 0x268);
        lw(a1, s2, 3524);
        sw(a1, sp, 0x26C);
        lw(a2, s2, 3528);
        sw(a2, sp, 0x270);
        lw(a3, s2, 3532);
        sw(a3, sp, 0x274);
        lw(t0, s2, 3540);
        sw(t0, sp, 0x278);
    }
    // 0x00597654
    charge(ctx, 16);
    v1 = addiu(s0, 5052);
    s4 = addiu(sp, 0x200);
    lw(v0, v1, 4);
    a0 = s0;
    a1 = s4;
    a2 = 64;
    v0 = sll(v0, 4);
    sw(v0, sp, 0x280);
    lw(v1, v1, 0);
    link(ctx, 0x597678u);  // $ra first: the delay slot below depends on it
    sw(v1, sp, 0x27C);
    call(ctx, gen::fn_sub_58E5E8_0058e5e8);
    a0 = s0;
    s3 = v0;
    jal(ctx, 0x597684u, gen::fn_sub_597288_00597288);
    if (v0 != 0) {
        ld(s0, sp, 0x290);
    } else {
        // 0x00597694
        charge(ctx, 11);
        s1 = addiu(sp, 0x70);
        a1 = addiu(s0, 2972);
        a2 = 400;
        a0 = s1;
        jal(ctx, 0x5976A0u, gen::fn_sub_575410_00575410);
        a1 = 0;
        a0 = sp;
        jal(ctx, 0x5976ACu, gen::fn_sub_596D68_00596d68);
        s0 = v0;
        a0 = addiu(s0, 2572);
        if (s0 != 0) {
            // 0x005976d8
            charge(ctx, 13);
            a1 = s1;
            a2 = 400;
            jal(ctx, 0x5976DCu, gen::fn_sub_575410_00575410);
            a0 = addiu(s0, 2972);
            a1 = s1;
            a2 = 400;
            jal(ctx, 0x5976ECu, gen::fn_sub_575410_00575410);
            a0 = s0;
            a1 = s4;
            a2 = s3;
            jal(ctx, 0x5976FCu, gen::fn_sub_58E670_0058e670);
            if (s5 != 0) {
                // 0x0059770c
                charge(ctx, 5);
                a0 = s0;
                a1 = addiu(sp, 0x50);
                jal(ctx, 0x597710u, gen::fn_sub_597878_00597878);
                if (v0 != 0) {
                    ld(s0, sp, 0x290);
                } else {
                    // 0x00597720
                    charge(ctx, 6);
                    lw(a2, sp, 0x64);
                    a0 = s0;
                    link(ctx, 0x597728u);  // $ra first: the delay slot below depends on it
                    lw(a1, sp, 0x250);
                    call(ctx, gen::fn_sub_5978E8_005978e8);
                    if (v0 == 0) {
                        // 0x00597738
                        charge(ctx, 2);
                        a0 = s0;
                        jal(ctx, 0x597738u, gen::fn_sub_597968_00597968);
                        goto L_00597740;
                    }
                    ld(s0, sp, 0x290);
                }
                // 0x00597848 (the shared epilogue, written out on this path)
                charge(ctx, 11);
                ld(s1, sp, 0x298);
                ld(s2, sp, 0x2A0);
                ld(s3, sp, 0x2A8);
                ld(s4, sp, 0x2B0);
                ld(s5, sp, 0x2B8);
                ld(s6, sp, 0x2C0);
                ld(s7, sp, 0x2C8);
                ld(fp, sp, 0x2D0);
                ld(ra, sp, 0x2D8);
                sp = addiu(sp, 0x2E0);
                return;
            }
        L_00597740:
            charge(ctx, 2);
            lw(a2, sp, 0x254);
            if (s6 != 0) {
                // 0x00597748
                charge(ctx, 3);
                a1 = s6;
                a0 = s0;
                jal(ctx, 0x59774Cu, gen::fn_sub_58BEF0_0058bef0);
            }
            // 0x00597754
            charge(ctx, 2);
            a1 = s7;
            if (s7 != 0) {
                // 0x0059775c
                charge(ctx, 2);
                a0 = s0;
                jal(ctx, 0x59775Cu, gen::fn_sub_59A578_0059a578);
            }
            // 0x00597764
            charge(ctx, 2);
            lw(a2, sp, 0x258);
            if (fp != 0) {
                // 0x0059776c
                charge(ctx, 4);
                a1 = fp;
                lw(a3, sp, 0x25C);
                a0 = s0;
                jal(ctx, 0x597774u, gen::fn_sub_59A600_0059a600);
            }
            // 0x0059777c
            charge(ctx, 3);
            lw(v0, sp, 0x260);
            a1 = v0;
            if (v0 != 0) {
                // 0x00597788
                charge(ctx, 2);
                a0 = s0;
                jal(ctx, 0x597788u, gen::fn_sub_59A508_0059a508);
            }
            // 0x00597790
            charge(ctx, 4);
            lw(v1, sp, 0x264);
            v0 = 1000;
            a1 = v1;
            if (v1 != v0) {
                // 0x005977a0
                charge(ctx, 2);
                a0 = s0;
                jal(ctx, 0x5977A0u, gen::fn_sub_5959E0_005959e0);
            }
            // 0x005977a8
            charge(ctx, 3);
            lw(v0, sp, 0x240);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 0x7B0000;
            if (!cc) {
                // 0x005977b4
                charge(ctx, 9);
                ldl(a0, sp, 0x247);
                ldr(a0, sp, 0x240);
                lw(a1, sp, 0x248);
                sdl(a0, s0, 4839);
                sdr(a0, s0, 4832);
                sw(a1, s0, 4840);
                lw(v0, v0, 18352);
                t0 = addiu(sp, 0x240);
                if (v0 != 0) {
                    // 0x005977d8
                    charge(ctx, 2);
                    a0 = t0;
                    jalr(ctx, 0x5977D8u, v0.u());
                }
            }
            // 0x005977e0
            charge(ctx, 2);
            lw(v0, sp, 0x27C);
            if (s2 != 0) {
                // 0x005977e8
                charge(ctx, 17);
                a1 = s2;
                a0 = s0;
                jal(ctx, 0x5977ECu, gen::fn_sub_598470_00598470);
                a0 = s0;
                link(ctx, 0x5977F8u);  // $ra first: the delay slot below depends on it
                lw(a1, sp, 0x268);
                call(ctx, gen::fn_sub_598E18_00598e18);
                a0 = s0;
                link(ctx, 0x597804u);  // $ra first: the delay slot below depends on it
                lw(a1, sp, 0x26C);
                call(ctx, gen::fn_sub_598D20_00598d20);
                a0 = s0;
                lw(a1, sp, 0x270);
                link(ctx, 0x597814u);  // $ra first: the delay slot below depends on it
                lw(a2, sp, 0x274);
                call(ctx, gen::fn_sub_598D90_00598d90);
                a0 = s0;
                link(ctx, 0x597820u);  // $ra first: the delay slot below depends on it
                lw(a1, sp, 0x278);
                call(ctx, gen::fn_sub_598E88_00598e88);
                lw(v0, sp, 0x27C);
            }
            // 0x0059782c
            charge(ctx, 2);
            lw(a2, sp, 0x280);
            if (v0 != 0) {
                // 0x00597834
                charge(ctx, 3);
                a0 = s0;
                a1 = v0;
                jal(ctx, 0x597838u, gen::fn_sub_597E98_00597e98);
            }
            // 0x00597840
            charge(ctx, 2);
            v0 = 0;
            ld(s0, sp, 0x290);
        } else {
            // 0x005976c0
            charge(ctx, 6);
            a1 = lui(0xFF00);
            a0 = 0;
            a1 = a1 | 0x202;
            jal(ctx, 0x5976C8u, gen::fn_sub_58BE40_0058be40);
            ld(s0, sp, 0x290);
        }
    }
    // 0x00597848 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s1, sp, 0x298);
    ld(s2, sp, 0x2A0);
    ld(s3, sp, 0x2A8);
    ld(s4, sp, 0x2B0);
    ld(s5, sp, 0x2B8);
    ld(s6, sp, 0x2C0);
    ld(s7, sp, 0x2C8);
    ld(fp, sp, 0x2D0);
    ld(ra, sp, 0x2D8);
    sp = addiu(sp, 0x2E0);
}

// 0x00597C28 sub_597C28 -- 244 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// Get-frame (transfer 6, command 11): handle check (error -16776906), API mode 1 (sub_597DC8); first frame's clock;
//   the callback 0x7B47BC.
void sub_597C28(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00597c28
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    link(ctx, 0x597C44u);  // $ra first: the delay slot below depends on it
    sw(zero, s1, 0);
    call(ctx, gen::fn_sub_58C060_0058c060);
    a0 = 0;
    if (v0 != 0) {
        // 0x00597c54
        charge(ctx, 8);
        a1 = lui(0xFF00);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        a1 = a1 | 0x136;
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00597c78
    charge(ctx, 5);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x597C7Cu, gen::fn_sub_597DC8_00597dc8);
    if (v0 != 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00597c8c
        charge(ctx, 10);
        a0 = s0;
        a1 = 6;
        a2 = 11;
        a3 = s1;
        t0 = 0;
        jal(ctx, 0x597C9Cu, gen::fn_sub_59BC20_0059bc20);
        s2 = v0;
        lw(v0, s1, 0);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0x7B0000;
        if (!cc) {
            // 0x00597cb4
            charge(ctx, 4);
            lw(v1, s0, 2408);
            lw(v0, s0, 2412);
            if (v1 != v0) {
                v0 = 0x7B0000;
            } else {
                // 0x00597cc4
                charge(ctx, 2);
                if (v1 != 0) {
                    v0 = addiu(v1, 1);
                } else {
                    // 0x00597ccc
                    charge(ctx, 5);
                    jal(ctx, 0x597CCCu, gen::fn_sub_59B3A8_0059b3a8);
                    lw(v1, s0, 2408);
                    sd(v0, s0, 14208);
                    v0 = addiu(v1, 1);
                }
                // 0x00597ce0
                charge(ctx, 2);
                sw(v0, s0, 2408);
                v0 = 0x7B0000;
            }
        }
        // 0x00597ce8
        charge(ctx, 3);
        lw(v0, v0, 18364);
        if (v0 == 0) {
            v0 = s2;
        } else {
            // 0x00597cf4
            charge(ctx, 4);
            lw(a1, s1, 0);
            a0 = s0;
            jalr(ctx, 0x597CF8u, v0.u());
            v0 = s2;
        }
        // 0x00597d04
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x00597d08 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00597D20 sub_597D20 -- 164 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Release-frame (transfer 6, command 12): handle check (error -16776905), API mode 1, the released count.
void sub_597D20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597d20
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x597D34u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x00597d48
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x137;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00597d60
    charge(ctx, 9);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x597D64u, gen::fn_sub_597DC8_00597dc8);
    a0 = s0;
    a3 = s1;
    a1 = 6;
    a2 = 12;
    t0 = 0;
    if (v0 != 0) {
        // 0x00597db0
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00597d84
    charge(ctx, 6);
    lw(v0, s0, 2412);
    lw(v1, s0, 2408);
    t1 = addiu(v0, 1);
    v0 = slt(v0, v1);
    if (v0 != 0) {
        sw(t1, s0, 2412);
    }
    // 0x00597d9c
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_59BC20_0059bc20(ctx);  // tail call
}

// 0x00597DC8 sub_597DC8 -- 84 bytes; frame 0x10: ra sp+0x0
// Claims the handle's API mode (+88): sets it when free; another mode is an error.
void sub_597DC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597dc8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    lw(v1, v0, 88);
    if (v1 == 0) {
        // 0x00597de0
        charge(ctx, 3);
        sw(a1, v0, 88);
        v0 = 0;
        // 0x00597e10 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00597df0
    charge(ctx, 2);
    v0 = 0;
    if (v1 == a1) {
        // 0x00597e10 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00597df8
    charge(ctx, 5);
    a1 = lui(0xFF00);
    ld(ra, sp, 0x0);
    a1 = a1 | 0x207;
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x00597E20 sub_597E20 -- 92 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Handle check (error -16776903), then sub_588D38.
void sub_597E20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597e20
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x597E34u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x00597e48
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x139;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00597e60
    charge(ctx, 7);
    a0 = s0;
    ld(s0, sp, 0x0);
    a1 = s1;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_588D38_00588d38(ctx);  // tail call
}

// 0x00597E80 sub_597E80 -- 24 bytes; leaf frame (no stack)
// Clears a 20-byte record.
void sub_597E80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x00597e80
    enter(ctx, 6);  // entry check point + this block's cycles
    sw(zero, a0, 16);
    sw(zero, a0, 0);
    sw(zero, a0, 4);
    sw(zero, a0, 8);
    sw(zero, a0, 12);
}

// 0x00597FA0 sub_597FA0 -- 140 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The time of a stream position (stream record handle+4936 + 116 i, sub_598030; error -16776159).
void sub_597FA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597fa0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = a2;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    v1 = sll(a1, 3);
    v1 = subu(v1, a1);
    sw(zero, a3, 0);
    ld(a2, t0, 0);
    v1 = sll(v1, 2);
    v0 = 0;
    v1 = addu(v1, a1);
    if (i64(a2) < 0) {
        // 0x0059801c (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00597fd4
    charge(ctx, 6);
    a0 = sll(v1, 2);
    a0 = addu(s0, a0);
    a0 = addiu(a0, 4936);
    lw(v1, a0, 0);
    a1 = t0;
    if (v1 == 0) {
        // 0x0059801c (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00597fec
    charge(ctx, 7);
    a2 = a3;
    jal(ctx, 0x597FECu, gen::fn_sub_598030_00598030);
    a0 = s0;
    a1 = lui(0xFF00);
    v1 = si(-1);
    a1 = a1 | 0x421;
    if (v0 == v1) {
        // 0x00598008
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00598018
    charge(ctx, 1);
    v0 = 0;
    // 0x0059801c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005980C8 sub_5980C8 -- 116 bytes; frame 0x10: ra sp+0x0
// The time stamp of a stream address (sub_598140), relative to the stream's window.
void sub_5980C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005980c8
    enter(ctx, 20);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    v1 = addiu(a0, 4880);
    v0 = subu(v0, a1);
    sp = addiu(sp, -0x10);
    v0 = sll(v0, 2);
    sd(ra, sp, 0x0);
    v0 = addu(v0, a1);
    a0 = si(-1);
    v0 = sll(v0, 2);
    sd(a0, a3, 0);
    v1 = addu(v1, v0);
    v0 = 0;
    a0 = addiu(v1, 56);
    v1 = addiu(v1, 16);
    lw(a1, a0, 0);
    t1 = a2;
    lw(t0, v1, 12);
    a2 = a3;
    lw(a3, v1, 8);
    if (a1 != 0) {
        // 0x00598118
        charge(ctx, 6);
        v0 = addu(a3, t0);
        a1 = subu(t1, t0);
        v0 = sltu(t1, v0);
        if (v0 != 0) a1 = t1;
        jal(ctx, 0x598124u, gen::fn_sub_598140_00598140);
        v0 = 0;
    }
    // 0x00598130 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005982A0 sub_5982A0 -- 64 bytes; leaf frame (no stack)
// Whether a stream's time-stamp queue is full.
void sub_5982A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x005982a0
    enter(ctx, 10);  // entry check point + this block's cycles
    v1 = sll(a1, 3);
    v1 = subu(v1, a1);
    v1 = sll(v1, 2);
    v1 = addu(v1, a1);
    v1 = sll(v1, 2);
    a0 = addu(a0, v1);
    a0 = addiu(a0, 4936);
    lw(v1, a0, 0);
    v0 = 0;
    if (v1 != 0) {
        // 0x005982c8
        charge(ctx, 4);
        lw(v1, a0, 4);
        lw(v0, a0, 8);
        v0 = slt(v0, v1);
        v0 = v0 ^ 0x1;
    }
    // 0x005982d8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005982E0 sub_5982E0 -- 32 bytes; leaf frame (no stack)
// Resets the header-object record: +8 = -3, +12 = 1.
void sub_5982E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x005982e0
    enter(ctx, 8);  // entry check point + this block's cycles
    v1 = addiu(a0, 4);
    a1 = si(-3);
    v0 = 1;
    sw(a1, v1, 4);
    sw(v0, v1, 8);
    sw(zero, a0, 0);
    sw(zero, v1, 0);
}

// 0x00598640 sub_598640 -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// With a header object, its step (sub_598688, sub_598EE8).
void sub_598640(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598640
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, sfd::kHdrObj);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
        // 0x00598678
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0059865c
    charge(ctx, 7);
    jal(ctx, 0x59865Cu, gen::fn_sub_598688_00598688);
    a0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_598EE8_00598ee8(ctx);  // tail call
}

// 0x00599810 sub_599810 -- 540 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Resets the time record: the six time-source callbacks (0x59A298, 0x59A2E0, -, 0x59A340, -, 0x59A360), the time
//   windows (sub_599A30), counters and the defaults (1000, 100, -5, -1.0f ...).
void sub_599810(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00599810
    enter(ctx, 68);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x5A0000;
    sd(s1, sp, 0x8);
    s1 = a1;
    a2 = 0;
    a1 = addiu(v0, -23912);  // &sub_59A298
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x599830u, gen::fn_sub_59A860_0059a860);
    a1 = 0x5A0000;
    a2 = 1;
    a1 = addiu(a1, -23840);  // &sub_59A2E0
    a0 = s0;
    jal(ctx, 0x599844u, gen::fn_sub_59A860_0059a860);
    a0 = s0;
    a1 = 0;
    a2 = 2;
    jal(ctx, 0x599854u, gen::fn_sub_59A860_0059a860);
    a1 = 0x5A0000;
    a1 = addiu(a1, -23744);  // &sub_59A340
    a2 = 3;
    a0 = s0;
    jal(ctx, 0x599868u, gen::fn_sub_59A860_0059a860);
    a0 = s0;
    a1 = 0;
    a2 = 4;
    jal(ctx, 0x599878u, gen::fn_sub_59A860_0059a860);
    a1 = 0x5A0000;
    a2 = 5;
    a1 = addiu(a1, -23712);  // &sub_59A360
    a0 = s0;
    jal(ctx, 0x59988Cu, gen::fn_sub_59A860_0059a860);
    sw(zero, s1, 24);
    a0 = addiu(s1, 28);
    jal(ctx, 0x599898u, gen::fn_sub_599A78_00599a78);
    a0 = addiu(s1, 192);
    a1 = 0;
    jal(ctx, 0x5998A4u, gen::fn_sub_599A30_00599a30);
    a0 = addiu(s1, 60);
    a1 = 0x7FFF0000;
    a1 = a1 | 0xFFFF;
    jal(ctx, 0x5998B4u, gen::fn_sub_599A30_00599a30);
    a0 = addiu(s1, 104);
    a1 = si(-1);
    jal(ctx, 0x5998C0u, gen::fn_sub_599A30_00599a30);
    a0 = addiu(s1, 148);
    a1 = si(-1);
    jal(ctx, 0x5998CCu, gen::fn_sub_599A30_00599a30);
    a0 = addiu(s1, 236);
    a1 = si(-1);
    jal(ctx, 0x5998D8u, gen::fn_sub_599A30_00599a30);
    a0 = addiu(s1, 280);
    a1 = 0x7FFF0000;
    a1 = a1 | 0xFFFF;
    jal(ctx, 0x5998E8u, gen::fn_sub_599A30_00599a30);
    sw(zero, s1, 324);
    v0 = si(-1);
    sw(zero, s1, 328);
    sw(zero, s1, 352);
    a0 = addiu(s1, 12);
    sw(zero, s1, 356);
    v1 = 31;
    sw(zero, s1, 360);
    sd(v0, s1, 344);
    sd(v0, s1, 336);
    v0 = addiu(s1, 488);
    for (;;) {
        // 0x00599920
        charge(ctx, 7);
        v1 = addiu(v1, -1);
        sw(zero, v0, 0);
        v0 = addiu(v0, -4);
        if (i64(v1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0059993c
    charge(ctx, 7);
    v0 = 1;
    sw(zero, s1, 496);
    sw(zero, s1, 500);
    v1 = 31;
    sw(zero, s1, 504);
    sw(v0, s1, 492);
    v0 = addiu(a0, 620);
    for (;;) {
        // 0x00599958
        charge(ctx, 7);
        v1 = addiu(v1, -1);
        sw(zero, v0, 0);
        v0 = addiu(v0, -4);
        if (i64(v1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00599974
    charge(ctx, 46);
    a3 = si(-1);
    sw(zero, s1, 680);
    sw(a3, s1, 716);
    a2 = 0x7FFF0000;
    at = lui(0xBF80);
    mtc1(at, f0);
    a1 = 1;
    lw(t0, s1, 680);
    v0 = si(-5);
    a2 = a2 | 0xFFFF;
    v1 = 1000;
    a0 = 100;
    sw(v0, s1, 728);
    sw(a2, s1, 672);
    sw(zero, s1, 732);
    sw(v1, s1, 684);
    sw(a1, s1, 736);
    sw(a0, s1, 700);
    swc1(f0, s1, 712);
    sw(t0, s1, 720);
    sw(zero, s1, 1464);
    sw(a3, s1, 740);
    sw(v0, s1, 636);
    sw(a1, s1, 640);
    sw(v0, s1, 644);
    sw(a1, s1, 648);
    sw(a3, s1, 652);
    sw(a1, s1, 656);
    sw(v0, s1, 660);
    sw(a2, s1, 664);
    sw(zero, s1, 668);
    sw(zero, s1, 676);
    sw(zero, s1, 688);
    sw(zero, s1, 692);
    sw(a1, s1, 696);
    swc1(f0, s1, 704);
    sw(zero, s1, 708);
    sw(zero, s1, 724);
    sw(zero, s1, 744);
    sw(zero, s1, 1456);
    sw(zero, s1, 1460);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059A028 sub_59A028 -- 172 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// The audio time plus the pause offset (sub_59A150, sub_57BAF0).
void sub_59A028(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a028
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = a0;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = addiu(v0, 3656);
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    s3 = addiu(v0, 3376);
    jal(ctx, 0x59A054u, gen::fn_sub_59A150_0059a150);
    lw(a1, s0, 0);
    v1 = 1;
    s4 = v0;
    if (a1 != v1) {
        // 0x0059a06c
        charge(ctx, 3);
        lw(v0, s3, 328);
        if (a1 == v0) {
            // 0x0059a078
            charge(ctx, 5);
            lw(v1, s3, 324);
            lw(v0, s2, 0);
            v0 = addu(v0, v1);
            sw(v0, s2, 0);
            goto L_0059a0b0;
        }
        lw(v0, s1, 0);
        // 0x0059a090
        charge(ctx, 2);
        if (v0 == 0) {
            v0 = s4;
        } else {
            // 0x0059a098
            charge(ctx, 6);
            lw(a2, s1, 40);
            link(ctx, 0x59A09Cu);  // $ra first: the delay slot below depends on it
            lw(a0, s1, 36);
            call(ctx, gen::fn_sub_57BAF0_0057baf0);
            lw(v1, s2, 0);
            v1 = addu(v1, v0);
            sw(v1, s2, 0);
        L_0059a0b0:
            charge(ctx, 1);
            v0 = s4;
        }
    }
    // 0x0059a0b4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0059A910 sub_59A910 -- 140 bytes; leaf frame (no stack)
// Time code to time: (h x 3600 + m x 60 + s) x rate + 1,000 x (f + extra) + 500 x field; the unit is a1.
void sub_59A910(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13};
    // 0x0059a910
    enter(ctx, 35);  // entry check point + this block's cycles
    lw(t2, a1, 8);
    lw(t4, a1, 12);
    mult(t2, t2, a0);
    lw(v0, a1, 24);
    lw(t3, a1, 20);
    mult(t4, t4, a0);
    lh(t5, a1, 30);
    t3 = addu(t3, v0);
    lw(t1, a1, 16);
    v0 = sll(t2, 3);
    v1 = sll(t3, 5);
    a1 = sll(t5, 5);
    v0 = subu(v0, t2);
    mult(t1, t1, a0);
    a1 = subu(a1, t5);
    v0 = sll(v0, 5);
    v1 = subu(v1, t3);
    t0 = sll(t4, 4);
    v0 = addu(v0, t2);
    t0 = subu(t0, t4);
    a1 = sll(a1, 2);
    v1 = sll(v1, 2);
    a1 = addu(a1, t5);
    v1 = addu(v1, t3);
    v0 = sll(v0, 4);
    t0 = sll(t0, 2);
    a1 = sll(a1, 2);
    v0 = addu(v0, t0);
    v1 = sll(v1, 3);
    t1 = addu(t1, a1);
    v0 = addu(v0, v1);
    t1 = addu(t1, v0);
    sw(t1, a2, 0);
    sw(a0, a3, 0);
}

// 0x0059A9D8 sub_59A9D8 -- 56 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// sub_59A910 at rate 30,000; then the unit word = a0.
void sub_59A9D8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a9d8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    a0 = 30000;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a3;
    jal(ctx, 0x59A9F0u, gen::fn_sub_59A910_0059a910);
    sw(s1, s0, 0);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
}

// 0x0059AD80 sub_59AD80 -- 120 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// The frame rate of the handle's sequence (0x7CA2C0[code]); handle check (error -16776933).
void sub_59AD80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059ad80
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = si(-1);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x10);
    link(ctx, 0x59AD9Cu);  // $ra first: the delay slot below depends on it
    sw(v0, s1, 0);
    call(ctx, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x0059adb0
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x11B;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0059adc8
    charge(ctx, 3);
    lw(v1, s0, 2336);
    cc = v1 == 0;  // the condition, before the delay slot changes it
    v1 = sll(v1, 2);
    if (!cc) {
        // 0x0059add4
        charge(ctx, 4);
        a0 = 0x7D0000;
        a0 = addu(a0, v1);
        lw(a0, a0, -23872);
        sw(a0, s1, 0);
    }
    // 0x0059ade4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059AE88 sub_59AE88 -- 52 bytes; frame 0x10: ra sp+0x0
// With a frame: whether its time is due (sub_59AEC0).
void sub_59AE88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ae88
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0;
    sd(ra, sp, 0x0);
    if (a1 == 0) {
        // 0x0059aeb0
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0059ae98
    charge(ctx, 5);
    lw(a2, a1, 24);
    ld(ra, sp, 0x0);
    lw(a1, a1, 20);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59AEC0_0059aec0(ctx);  // tail call
}

// 0x0059AEC0 sub_59AEC0 -- 52 bytes; frame 0x20: ra sp+0x10
// Whether a time is due (sub_59B048), always unless param 14 is clear.
void sub_59AEC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059aec0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a3 = addiu(a0, 2572);
    sd(ra, sp, 0x10);
    lw(v1, a3, 56);
    v0 = 1;
    if (v1 == 0) {
        // 0x0059aed8
        charge(ctx, 4);
        lw(t0, a3, 176);
        a3 = sp;
        jal(ctx, 0x59AEDCu, gen::fn_sub_59B048_0059b048);
        lw(v0, sp, 0x0);
    }
    // 0x0059aee8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059B048 sub_59B048 -- 332 bytes; frame 0x50: s3 sp+0x28, s4 sp+0x30, s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s5 sp+0x38, ra sp+0x40
// Compares a time with the play clock (sub_59A168): at the stop clock -> due; otherwise scaled to 1/10000 units,
//   exact (param 15 = 1) or with tolerance (sub_59B210).
void sub_59B048(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13};
    // 0x0059b048
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x7B0000;
    sd(s3, sp, 0x28);
    s3 = a1;
    sd(s4, sp, 0x30);
    s4 = a2;
    a1 = sp;
    a2 = addiu(sp, 0x4);
    sd(s0, sp, 0x10);
    s0 = t0;
    sd(s1, sp, 0x18);
    s1 = a3;
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s5, sp, 0x38);
    sd(ra, sp, 0x40);
    s5 = addiu(v0, 18208);  // &0x7B4720
    jal(ctx, 0x59B088u, gen::fn_sub_59A168_0059a168);
    lw(v0, sp, 0x4);
    a2 = 1;
    at = 0x461C0000;
    at = at | 0x4000;
    mtc1(at, f3);
    v1 = si(-2);
    mult(a0, v0, s0);
    if (v0 != a2) {
        // 0x0059b0e0
        charge(ctx, 8);
        lw(v1, s5, 8);
        mtc1(s3, f0);
        cvt_s_w(f0, f0);
        mtc1(s4, f1);
        cvt_s_w(f1, f1);
        div(a0, v1);
        if (v1 == 0) {
            brk(ctx, 0x59B0FCu, 0x7u);
        }
        // 0x0059b100
        charge(ctx, 19);
        mtc1(v0, f2);
        cvt_s_w(f2, f2);
        lw(v0, sp, 0x0);
        mul_s(f0, f0, f3);
        lw(a1, s2, 2632);
        div_s(f1, f0, f1);
        mov_s(f12, f1);
        mflo(v1);
        v0 = addu(v0, v1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        mul_s(f0, f0, f3);
        div_s(f13, f0, f2);
        sw(v0, sp, 0x0);
        if (a1 == a2) {
            // 0x0059b160
            charge(ctx, 3);
            c_le_s(f1, f13);
            if (!cond(ctx)) {
                sw(zero, s1, 0);
            } else {
                // 0x0059b16c
                charge(ctx, 1);
                sw(a1, s1, 0);
            }
        L_0059b170:
            charge(ctx, 1);
            ld(s0, sp, 0x10);
        } else {
            // 0x0059b14c
            charge(ctx, 5);
            a0 = s2;
            a1 = s1;
            jal(ctx, 0x59B150u, gen::fn_sub_59B210_0059b210);
            ld(s0, sp, 0x10);
        }
    } else {
        // 0x0059b0b0
        charge(ctx, 3);
        lw(v0, sp, 0x0);
        if (v0 == v1) {
            // 0x0059b0bc
            charge(ctx, 2);
            sw(a2, s1, 0);
            goto L_0059b170;
        }
        a0 = s2;
        // 0x0059b0c8
        charge(ctx, 6);
        a1 = s3;
        a2 = s4;
        a3 = s1;
        jal(ctx, 0x59B0D0u, gen::fn_sub_59B198_0059b198);
        ld(s0, sp, 0x10);
    }
    // 0x0059b174 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0059B210 sub_59B210 -- 236 bytes; leaf frame (no stack)
// The due decision with a tolerance window (+2756) and the 59.94 Hz frame-repeat rule.
void sub_59B210(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13};
    // 0x0059b210
    enter(ctx, 7);  // entry check point + this block's cycles
    a3 = a0;
    lwc1(f1, a3, 2756);
    cvt_s_w(f1, f1);
    add_s(f0, f13, f1);
    c_lt_s(f0, f12);
    a2 = addiu(a3, 3376);
    if (cond(ctx)) {
        // 0x0059b22c
        charge(ctx, 2);
        sw(zero, a1, 0);
        return;
    }
    // 0x0059b238
    charge(ctx, 4);
    sub_s(f0, f13, f1);
    c_le_s(f12, f0);
    v0 = 0x7B0000;
    if (cond(ctx)) {
        // 0x0059b248
        charge(ctx, 5);
        lwc1(f0, a2, 712);
        v0 = 1;
        c_eq_s(f0, f12);
        sw(v0, a1, 0);
        if (cond(ctx)) {
            // 0x0059b2f4 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        // 0x0059b25c
        charge(ctx, 4);
        lwc1(f0, a2, 704);
        c_eq_s(f0, f12);
        if (cond(ctx)) {
            // 0x0059b2f4 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        // 0x0059b26c
        charge(ctx, 5);
        lw(v0, a2, 700);
        swc1(f12, a2, 704);
        v0 = addiu(v0, 1);
        sw(v0, a2, 700);
        return;
    }
    // 0x0059b280
    charge(ctx, 4);
    a0 = 0xEA24;
    lw(v1, v0, 18216);
    t0 = 0;
    if (v1 == a0) {
        // 0x0059b290
        charge(ctx, 4);
        lw(v0, a3, 2336);
        v0 = slti(v0, 3);
        if (v0 != 0) {
            // 0x0059b2a0
            charge(ctx, 3);
            lw(v0, a2, 684);
            v0 = v0 ^ 0x3E8;
            t0 = sltiu(v0, 1);
            goto L_0059b2ac;
        }
        lw(v0, a2, 700);
        goto L_0059b2b0;
    }
L_0059b2ac:
    charge(ctx, 1);
    lw(v0, a2, 700);
L_0059b2b0:
    charge(ctx, 3);
    v0 = slt(t0, v0);
    if (v0 == 0) {
        // 0x0059b2bc
        charge(ctx, 2);
        lw(v0, a2, 708);
        goto L_0059b2e0;
    }
    // 0x0059b2c8
    charge(ctx, 3);
    c_lt_s(f13, f12);
    v0 = 1;
    if (!cond(ctx)) {
    L_0059b2e0:
        charge(ctx, 1);
        sw(v0, a1, 0);
    } else {
        // 0x0059b2d4
        charge(ctx, 2);
        sw(zero, a1, 0);
    }
    // 0x0059b2e4
    charge(ctx, 4);
    sw(zero, a2, 700);
    swc1(f12, a2, 712);
    lw(v0, a1, 0);
    sw(v0, a2, 708);
    // 0x0059b2f4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0059B3A8 sub_59B3A8 -- 176 bytes; frame 0x20: ra sp+0x10
// The current clock: the last handle's time source (+4100) or the vsync count x 1,000 at rate 0x7B4728; or the timer
//   (sub_5A1B80 / sub_5A1A30).
void sub_59B3A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059b3a8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    jal(ctx, 0x59B3B0u, gen::fn_sub_5A1B58_005a1b58);
    v1 = 0x7B0000;
    v1 = addiu(v1, 17776);  // &0x7B4570
    if (v0 != 0) {
        // 0x0059b3e0
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(a0, v0, 17768);  // 0x7B4568
        if (a0 != 0) {
            // 0x0059b3f0
            charge(ctx, 3);
            lw(v0, a0, 72);
            if (v0 == 0) {
                goto L_0059b428;
            }
            // 0x0059b3fc
            charge(ctx, 3);
            lw(v0, a0, 4100);
            a1 = sp;
            if (v0 == 0) {
                goto L_0059b428;
            }
            // 0x0059b408
            charge(ctx, 8);
            lw(a0, a0, 4120);
            a2 = addiu(sp, 0x4);
            jalr(ctx, 0x59B40Cu, v0.u());
            a0 = 0x9B0000;
            lw(v1, sp, 0x4);
            lw(v0, sp, 0x0);
            sd(v1, a0, -13368);  // 0x9ACBC8
            goto L_0059b44c;
        }
    L_0059b428:
        charge(ctx, 9);
        lw(a0, v1, 432);
        lw(a1, v1, 440);
        v1 = 0x9B0000;
        v0 = sll(a0, 5);
        v0 = subu(v0, a0);
        sd(a1, v1, -13368);  // 0x9ACBC8
        v0 = sll(v0, 2);
        v0 = addu(v0, a0);
        v0 = sll(v0, 3);
    L_0059b44c:
        charge(ctx, 1);
        ld(ra, sp, 0x10);
    } else {
        // 0x0059b3c4
        charge(ctx, 7);
        jal(ctx, 0x59B3C4u, gen::fn_sub_5A1B80_005a1b80);
        v1 = 0x9B0000;
        link(ctx, 0x59B3D0u);  // $ra first: the delay slot below depends on it
        sd(v0, v1, -13368);
        call(ctx, gen::fn_sub_5A1A30_005a1a30);
        ld(ra, sp, 0x10);
    }
    // 0x0059b450 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x20);
}

// 0x0059B620 sub_59B620 -- 184 bytes; frame 0x30: s3 sp+0x18, ra sp+0x28, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s4 sp+0x20
// Initialises the 9 transfer slots (68 bytes) from the creation's table and connects them (sub_59B720; error
//   -16776446).
void sub_59B620(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059b620
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s3, sp, 0x18);
    lw(s3, a2, 0);
    sd(ra, sp, 0x28);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = s3;
    sd(s2, sp, 0x10);
    s2 = 8;
    sd(s4, sp, 0x20);
    s4 = a0;
    sw(zero, s0, 8);
    for (;;) {
        // 0x0059b658
        charge(ctx, 8);
        a0 = s0;
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 68);
        lw(a1, s1, 0);
        s1 = addiu(s1, 4);
        jal(ctx, 0x59B668u, gen::fn_sub_59B6D8_0059b6d8);
        if (i64(s2) < 0) {
            break;
        }
        sw(zero, s0, 8);
        backedge(ctx);
    }
    // 0x0059b678
    charge(ctx, 5);
    a1 = s3;
    a0 = s4;
    jal(ctx, 0x59B67Cu, gen::fn_sub_59B720_0059b720);
    a0 = s4;
    if (v0 == 0) {
        // 0x0059b6b8
        charge(ctx, 8);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x0059b68c
    charge(ctx, 10);
    ld(s4, sp, 0x20);
    a1 = lui(0xFF00);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a1 = a1 | 0x302;
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0059B6D8 sub_59B6D8 -- 72 bytes; leaf frame (no stack)
// Resets a transfer slot.
void sub_59B6D8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0059b6d8
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 8;
    sw(zero, a0, 4);
    sw(zero, a0, 0);
    v1 = 2;
    sw(a1, a0, 12);
    a1 = 8;
    sw(v0, a0, 16);
    v0 = addiu(a0, 28);
    for (;;) {
        // 0x0059b6f8
        charge(ctx, 7);
        v1 = addiu(v1, -1);
        sw(a1, v0, 0);
        v0 = addiu(v0, -4);
        if (i64(v1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0059b714
    charge(ctx, 3);
    v0 = si(-1);
    sw(v0, a0, 32);
}

// 0x0059B720 sub_59B720 -- 288 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Connects the transfer graph for the streams present: system, video only, audio only or user data.
void sub_59B720(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059b720
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    lw(v0, s0, 4);
    s1 = a0;
    if (v0 == 0) {
        // 0x0059b760
        charge(ctx, 3);
        lw(v0, s0, 8);
        a2 = 1;
        if (v0 != 0) {
            // 0x0059b76c
            charge(ctx, 11);
            a1 = 0;
            jal(ctx, 0x59B76Cu, gen::fn_sub_59BA90_0059ba90);
            a0 = s1;
            a1 = s0;
            jal(ctx, 0x59B778u, gen::fn_sub_59B930_0059b930);
            a0 = s1;
            a1 = 6;
            a2 = 0;
            jal(ctx, 0x59B788u, gen::fn_sub_599240_00599240);
            sw(zero, s1, 2996);
            goto L_0059b828;
        }
        // 0x0059b798
        charge(ctx, 3);
        lw(v0, s0, 12);
        a2 = 2;
        if (v0 != 0) {
            // 0x0059b7a4
            charge(ctx, 11);
            a1 = 0;
            jal(ctx, 0x59B7A4u, gen::fn_sub_59BA90_0059ba90);
            a0 = s1;
            a1 = s0;
            jal(ctx, 0x59B7B0u, gen::fn_sub_59B9D0_0059b9d0);
            a0 = s1;
            a1 = 5;
            a2 = 0;
            jal(ctx, 0x59B7C0u, gen::fn_sub_599240_00599240);
            sw(zero, s1, 2992);
            goto L_0059b828;
        }
        // 0x0059b7d0
        charge(ctx, 3);
        lw(v0, s0, 32);
        a2 = 7;
        if (v0 == 0) {
            // 0x0059b820
            charge(ctx, 2);
            v0 = si(-1);
        } else {
            // 0x0059b7dc
            charge(ctx, 16);
            a1 = 0;
            jal(ctx, 0x59B7DCu, gen::fn_sub_59BA90_0059ba90);
            a0 = s1;
            a1 = s0;
            jal(ctx, 0x59B7E8u, gen::fn_sub_59BA70_0059ba70);
            a0 = s1;
            a1 = 6;
            a2 = 0;
            jal(ctx, 0x59B7F8u, gen::fn_sub_599240_00599240);
            a0 = s1;
            a1 = 5;
            a2 = 0;
            jal(ctx, 0x59B808u, gen::fn_sub_599240_00599240);
            sw(zero, s1, 2996);
            sw(zero, s1, 2992);
        L_0059b828:
            charge(ctx, 1);
            v0 = 0;
        }
    } else {
        // 0x0059b740
        charge(ctx, 8);
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x59B744u, gen::fn_sub_59BA90_0059ba90);
        a0 = s1;
        a1 = s0;
        jal(ctx, 0x59B750u, gen::fn_sub_59B840_0059b840);
        v0 = 0;
    }
    // 0x0059b82c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059B840 sub_59B840 -- 236 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// The system-stream graph: the video and audio chains when present, the user-data link.
void sub_59B840(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059b840
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 1;
    sd(s1, sp, 0x8);
    s1 = a1;
    a1 = 0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x59B85Cu, gen::fn_sub_59BB50_0059bb50);
    a0 = s0;
    lw(v0, s1, 8);
    a1 = 5;
    a2 = 0;
    if (v0 == 0) {
        // 0x0059b898
        charge(ctx, 4);
        jal(ctx, 0x59B898u, gen::fn_sub_599240_00599240);
        sw(zero, s0, 2992);
        lw(v0, s1, 12);
    } else {
        // 0x0059b878
        charge(ctx, 8);
        a1 = 1;
        a2 = 1;
        jal(ctx, 0x59B87Cu, gen::fn_sub_59BAB0_0059bab0);
        a0 = s0;
        a1 = s1;
        jal(ctx, 0x59B888u, gen::fn_sub_59B930_0059b930);
        lw(v0, s1, 12);
    }
    // 0x0059b8a8
    charge(ctx, 2);
    a0 = s0;
    if (v0 == 0) {
        // 0x0059b8d0
        charge(ctx, 5);
        a1 = 6;
        a2 = 0;
        jal(ctx, 0x59B8D4u, gen::fn_sub_599240_00599240);
        sw(zero, s0, 2996);
        lw(v0, s1, 32);
    } else {
        // 0x0059b8b0
        charge(ctx, 8);
        a1 = 1;
        a2 = 2;
        jal(ctx, 0x59B8B4u, gen::fn_sub_59BAD0_0059bad0);
        a0 = s0;
        a1 = s1;
        jal(ctx, 0x59B8C0u, gen::fn_sub_59B9D0_0059b9d0);
        lw(v0, s1, 32);
    }
    // 0x0059b8e4
    charge(ctx, 2);
    a0 = s0;
    if (v0 == 0) {
        // 0x0059b918
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059b8ec
    charge(ctx, 10);
    a1 = 1;
    a2 = 7;
    jal(ctx, 0x59B8F0u, gen::fn_sub_59BAF0_0059baf0);
    a0 = s0;
    a1 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_59BA70_0059ba70(ctx);  // tail call
}

// 0x0059B930 sub_59B930 -- 156 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// The video chain: 1 -> 2 -> 3, then 3 -> 6 or 3 -> 4 -> 5 -> 6.
void sub_59B930(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059b930
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 2;
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    a1 = 1;
    jal(ctx, 0x59B94Cu, gen::fn_sub_59BB50_0059bb50);
    a0 = s1;
    a1 = 2;
    a2 = 3;
    jal(ctx, 0x59B95Cu, gen::fn_sub_59BA90_0059ba90);
    a0 = s1;
    lw(v0, s0, 16);
    a1 = 3;
    a2 = 4;
    if (v0 == 0) {
        // 0x0059b9b0
        charge(ctx, 7);
        ld(s1, sp, 0x8);
        ld(s0, sp, 0x0);
        a1 = 3;
        ld(ra, sp, 0x10);
        a2 = 6;
        sp = addiu(sp, 0x20);
        gen::fn_sub_59BB50_0059bb50(ctx);  // tail call
        return;
    }
    // 0x0059b978
    charge(ctx, 14);
    jal(ctx, 0x59B978u, gen::fn_sub_59BB50_0059bb50);
    a0 = s1;
    a1 = 4;
    a2 = 5;
    jal(ctx, 0x59B988u, gen::fn_sub_59BA90_0059ba90);
    a0 = s1;
    ld(s0, sp, 0x0);
    a1 = 5;
    ld(s1, sp, 0x8);
    a2 = 6;
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_59BB50_0059bb50(ctx);  // tail call
}

// 0x0059B9D0 sub_59B9D0 -- 156 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// The audio chain: 2 -> 3 -> 4, then 4 -> 7 or 4 -> 5 -> 6 -> 7.
void sub_59B9D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059b9d0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 3;
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    a1 = 2;
    jal(ctx, 0x59B9ECu, gen::fn_sub_59BB50_0059bb50);
    a0 = s1;
    a1 = 3;
    a2 = 4;
    jal(ctx, 0x59B9FCu, gen::fn_sub_59BA90_0059ba90);
    a0 = s1;
    lw(v0, s0, 20);
    a1 = 4;
    a2 = 5;
    if (v0 == 0) {
        // 0x0059ba50
        charge(ctx, 7);
        ld(s1, sp, 0x8);
        ld(s0, sp, 0x0);
        a1 = 4;
        ld(ra, sp, 0x10);
        a2 = 7;
        sp = addiu(sp, 0x20);
        gen::fn_sub_59BB50_0059bb50(ctx);  // tail call
        return;
    }
    // 0x0059ba18
    charge(ctx, 14);
    jal(ctx, 0x59BA18u, gen::fn_sub_59BB50_0059bb50);
    a0 = s1;
    a1 = 5;
    a2 = 6;
    jal(ctx, 0x59BA28u, gen::fn_sub_59BA90_0059ba90);
    a0 = s1;
    ld(s0, sp, 0x0);
    a1 = 6;
    ld(s1, sp, 0x8);
    a2 = 7;
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_59BB50_0059bb50(ctx);  // tail call
}

// 0x0059BA70 sub_59BA70 -- 28 bytes; frame 0x10: ra sp+0x0
// Link 7 -> 8 (sub_59BB50).
void sub_59BA70(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ba70
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 7;
    sd(ra, sp, 0x0);
    a2 = 8;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59BB50_0059bb50(ctx);  // tail call
}

// 0x0059BA90 sub_59BA90 -- 28 bytes; frame 0x10: ra sp+0x0
// A link variant (tail into the shared code at 0x59BB10).
void sub_59BA90(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ba90
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = a2;
    sd(ra, sp, 0x0);
    a2 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59BAF0_0059baf0_at_0059bb10(ctx);  // tail call
}

// 0x0059BAB0 sub_59BAB0 -- 28 bytes; frame 0x10: ra sp+0x0
// A link variant (tail into the shared code at 0x59BB10).
void sub_59BAB0(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059bab0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = a2;
    sd(ra, sp, 0x0);
    a2 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59BAF0_0059baf0_at_0059bb10(ctx);  // tail call
}

// 0x0059BAD0 sub_59BAD0 -- 28 bytes; frame 0x10: ra sp+0x0
// A link variant (tail into the shared code at 0x59BB10).
void sub_59BAD0(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059bad0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = a2;
    sd(ra, sp, 0x0);
    a2 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59BAF0_0059baf0_at_0059bb10(ctx);  // tail call
}

// 0x0059BB50 sub_59BB50 -- 52 bytes; leaf frame (no stack)
// Links slot a1 to slot a2: the slot's input (handle+8000 + 68 a2) = a1, the stream's output (handle+4960 + 116 a1) =
//   a2.
void sub_59BB50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0059bb50
    enter(ctx, 13);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    v1 = sll(a2, 4);
    v0 = subu(v0, a1);
    v1 = addu(v1, a2);
    v0 = sll(v0, 2);
    v1 = sll(v1, 2);
    v0 = addu(v0, a1);
    v1 = addu(a0, v1);
    v0 = sll(v0, 2);
    sw(a1, v1, 8000);
    a0 = addu(a0, v0);
    sw(a2, a0, 4960);
}

// 0x0059C358 sub_59C358 -- 96 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Pushes a sample into a ring-average record and stores the new average (+420, +424).
void sub_59C358(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059c358
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    a3 = addiu(s0, 20);
    lw(v1, s0, 16);
    lw(a2, a3, 0);
    if (v1 == 0) {
        brk(ctx, 0x59C378u, 0x7u);
    }
    // 0x0059c37c
    charge(ctx, 15);
    div(a2, v1);
    a2 = addiu(a2, 1);
    mfhi(v0);
    v0 = sll(v0, 2);
    v0 = addu(v0, s0);
    sw(a1, v0, 24);
    link(ctx, 0x59C394u);  // $ra first: the delay slot below depends on it
    sw(a2, a3, 0);
    call(ctx, gen::fn_sub_59C418_0059c418);
    v1 = v0;
    ld(ra, sp, 0x8);
    sw(v1, s0, 424);
    sw(v1, s0, 420);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0059C418 sub_59C418 -- 76 bytes; leaf frame (no stack)
// The average of a ring-average record's samples.
void sub_59C418(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0059c418
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a1, a0, 16);
    a2 = 0;
    if (i64(a1) > 0) {
        // 0x0059c424
        charge(ctx, 3);
        a0 = addiu(a0, 24);
        v1 = a1;
        for (;;) {
            // 0x0059c430
            charge(ctx, 7);
            lw(v0, a0, 0);
            a0 = addiu(a0, 4);
            v1 = addiu(v1, -1);
            a2 = addu(a2, v0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0059c44c
    charge(ctx, 3);
    div(a2, a1);
    if (a1 == 0) {
        brk(ctx, 0x59C454u, 0x7u);
    }
    // 0x0059c458
    charge(ctx, 3);
    mflo(v0);
}

// 0x0059C480 sub_59C480 -- 348 bytes; frame 0x140: s0 sp+0x120, s1 sp+0x128, ra sp+0x130
// Profiler log: copies the column titles (0x7CA330) into the log buffer 0x7B47DC.
void sub_59C480(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059c480
    enter(ctx, 9);  // entry check point + this block's cycles
    v1 = 0x7D0000;
    sp = addiu(sp, -0x140);
    v1 = addiu(v1, -23760);  // &0x7CA330
    sd(s0, sp, 0x120);
    v0 = v1 & 0x7;
    sd(s1, sp, 0x128);
    sd(ra, sp, 0x130);
    a0 = sp;
    if (v0 == 0) {
        // 0x0059c508
        charge(ctx, 1);
        v0 = addiu(v1, 256);
        for (;;) {
            // 0x0059c50c
            charge(ctx, 13);
            ld(a1, v1, 0);
            ld(a2, v1, 8);
            ld(a3, v1, 16);
            ld(t0, v1, 24);
            sd(a1, a0, 0);
            sd(a2, a0, 8);
            sd(a3, a0, 16);
            sd(t0, a0, 24);
            v1 = addiu(v1, 32);
            a0 = addiu(a0, 32);
            if (v1 == v0) {
                break;
            }
            backedge(ctx);
        }
    } else {
        // 0x0059c4a4
        charge(ctx, 1);
        v0 = addiu(v1, 256);
        for (;;) {
            // 0x0059c4a8
            charge(ctx, 21);
            ldl(a1, v1, 7);
            ldr(a1, v1, 0);
            ldl(a2, v1, 15);
            ldr(a2, v1, 8);
            ldl(a3, v1, 23);
            ldr(a3, v1, 16);
            ldl(t0, v1, 31);
            ldr(t0, v1, 24);
            sdl(a1, a0, 7);
            sdr(a1, a0, 0);
            sdl(a2, a0, 15);
            sdr(a2, a0, 8);
            sdl(a3, a0, 23);
            sdr(a3, a0, 16);
            sdl(t0, a0, 31);
            sdr(t0, a0, 24);
            v1 = addiu(v1, 32);
            a0 = addiu(a0, 32);
            if (v1 == v0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0059c4fc
        charge(ctx, 2);
    }
    // 0x0059c540
    charge(ctx, 17);
    ldl(a1, v1, 7);
    ldr(a1, v1, 0);
    ldl(a2, v1, 15);
    ldr(a2, v1, 8);
    lb(a3, v1, 16);
    lb(t0, v1, 17);
    sdl(a1, a0, 7);
    sdr(a1, a0, 0);
    sdl(a2, a0, 15);
    sdr(a2, a0, 8);
    sb(a3, a0, 16);
    v0 = 0x7B0000;
    s1 = addiu(v0, 18396);  // &0x7B47DC
    sb(t0, a0, 17);
    lw(a0, s1, 0);  // 0x7B47DC
    v0 = 0x7B0000;
    if (a0 != 0) {
        // 0x0059c584
        charge(ctx, 17);
        a1 = 0;
        lw(a2, v0, 18392);
        s0 = 0x7B0000;
        s0 = addiu(s0, 18404);  // &0x7B47E4
        jal(ctx, 0x59C590u, gen::fn_memset_00521408);
        lw(v0, s1, 0);
        a1 = sp;
        sw(v0, s0, 0);  // 0x7B47E4
        a0 = v0;
        jal(ctx, 0x59C5A4u, gen::fn_strcpy_00524270);
        a0 = sp;
        jal(ctx, 0x59C5ACu, gen::fn_strlen_00524388);
        lw(v1, s0, 0);  // 0x7B47E4
        a0 = 0x7B0000;
        v1 = addu(v1, v0);
        sw(v1, a0, 18408);  // 0x7B47E8
        sw(v1, s0, 0);  // 0x7B47E4
    }
    // 0x0059c5c8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x120);
    ld(s1, sp, 0x128);
    ld(ra, sp, 0x130);
    sp = addiu(sp, 0x140);
}

// 0x0059C5E0 sub_59C5E0 -- 472 bytes; frame 0x210: fp sp+0x200, s0 sp+0x1C0, s1 sp+0x1C8, s2 sp+0x1D0, s3 sp+0x1D8, s4 sp+0x1E0, s5 sp+0x1E8, s6 sp+0x1F0, s7 sp+0x1F8, ra sp+0x208
// Profiler log: one sprintf line of a handle's counters into the log buffer; wraps 1 KiB before its end.
void sub_59C5E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0059c5e0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x210);
    v1 = 0x7B0000;
    sd(fp, sp, 0x200);
    fp = a0;
    sd(s0, sp, 0x1C0);
    v1 = addiu(v1, 18396);  // &0x7B47DC
    sd(s1, sp, 0x1C8);
    sd(s2, sp, 0x1D0);
    sd(s3, sp, 0x1D8);
    sd(s4, sp, 0x1E0);
    sd(s5, sp, 0x1E8);
    sd(s6, sp, 0x1F0);
    sd(s7, sp, 0x1F8);
    sd(ra, sp, 0x208);
    lw(v0, v1, 0);  // 0x7B47DC
    a0 = 1000;
    if (v0 != 0) {
        // 0x0059c624
        charge(ctx, 86);
        lw(a2, fp, 0x120);
        s0 = 0x7D0000;
        lw(a1, fp, 0x118);
        s0 = addiu(s0, -23480);  // &0x7CA448
        jal(ctx, 0x59C630u, gen::fn_sub_57BAF0_0057baf0);
        ld(s1, fp, 0x118);
        ld(a1, fp, 0x120);
        s6 = v0;
        a0 = s1;
        jal(ctx, 0x59C644u, gen::fn___divdi3_0052eeb0);
        t3 = 0x7FFF0000;
        t3 = t3 | 0xFFFF;
        ld(a0, fp, 0x188);
        t2 = s1;
        ld(v1, fp, 0x128);
        a1 = s0;
        sd(a0, sp, 0x1A0);
        a3 = v0;
        t1 = dsra32(s1, 0);
        a2 = fp;
        ld(s2, fp, 0x108);
        t0 = s6;
        t3 = t2 & t3;
        sd(s2, sp, 0x1A8);
        ld(s2, sp, 0x1A0);
        lw(a0, fp, 0x1AC);
        s7 = s2 - v1;
        sd(a0, sp, 0x1B0);
        ld(a0, sp, 0x1A8);
        lw(t5, fp, 0x198);
        s2 = a0 - v1;
        a0 = addiu(sp, 0xA0);
        lw(t6, fp, 0x1A4);
        lw(t9, fp, 0x1B0);
        lw(t8, fp, 0x1B4);
        lw(t7, fp, 0x1A0);
        lw(t4, fp, 0x194);
        lw(s1, fp, 0x1A8);
        lw(s0, fp, 0x19C);
        lw(v0, fp, 0x190);
        lw(s5, fp, 0x1B8);
        lwu(s4, fp, 0x4);
        lwu(s3, fp, 0x8);
        sd(s2, sp, 0x18);
        ld(s2, sp, 0x1B0);
        sd(s0, sp, 0x58);
        sd(s2, sp, 0x28);
        sd(v0, sp, 0x68);
        sd(s7, sp, 0x20);
        sd(t9, sp, 0x30);
        sd(t8, sp, 0x38);
        sd(s5, sp, 0x40);
        sd(s4, sp, 0x48);
        sd(s3, sp, 0x50);
        sd(t7, sp, 0x60);
        sd(t4, sp, 0x70);
        ld(v0, sp, 0x1A0);
        sd(v1, sp, 0x10);
        v1 = 0x7B0000;
        ld(s2, sp, 0x1A8);
        sd(v0, sp, 0x0);
        lw(v0, v1, 17744);  // 0x7B4550
        sd(s2, sp, 0x8);
        s2 = 0x7B0000;
        sd(s1, sp, 0x88);
        s2 = addiu(s2, 18396);  // &0x7B47DC
        sd(t5, sp, 0x78);
        sd(t6, sp, 0x80);
        link(ctx, 0x59C734u);  // $ra first: the delay slot below depends on it
        sd(v0, sp, 0x90);
        call(ctx, gen::fn_sprintf_00523ac8);
        s0 = v0;
        v0 = 0x7B0000;
        s1 = addiu(v0, 18404);  // &0x7B47E4
        a1 = addiu(sp, 0xA0);
        link(ctx, 0x59C74Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 0);  // 0x7B47E4
        call(ctx, gen::fn_strcpy_00524270);
        a0 = 0x7B0000;
        lw(v0, s2, 0);  // 0x7B47DC
        lw(a1, a0, 18392);  // 0x7B47D8
        lw(v1, s1, 0);  // 0x7B47E4
        v0 = addu(v0, a1);
        v1 = addu(v1, s0);
        v0 = addiu(v0, -1024);
        v0 = sltu(v1, v0);
        sw(v1, s1, 0);  // 0x7B47E4
        if (v0 == 0) {
            // 0x0059c77c
            charge(ctx, 3);
            v0 = 0x7B0000;
            lw(v1, v0, 18408);  // 0x7B47E8
            sw(v1, s1, 0);
        }
    }
    // 0x0059c788 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x1C0);
    ld(s1, sp, 0x1C8);
    ld(s2, sp, 0x1D0);
    ld(s3, sp, 0x1D8);
    ld(s4, sp, 0x1E0);
    ld(s5, sp, 0x1E8);
    ld(s6, sp, 0x1F0);
    ld(s7, sp, 0x1F8);
    ld(fp, sp, 0x200);
    ld(ra, sp, 0x208);
    sp = addiu(sp, 0x210);
}

}  // namespace p3fes::game
