// Phase 5 slice libs10: the CRI middleware layer between ADX and the IOP (150 functions, 0x550048..0x55FC00).
//   0x550048..0x5526xx  AHX (MPEG audio layer II) decoder: the synthesis windows, the synthesis / decoder pools and
//                       the per-decoder server;
//   0x552630..0x555898  AIX: the AIXP player (4 x 620 bytes at 0x799978) over per-track ADXT players, and the AIX
//                       demuxer (4 x 6492 bytes at 0x79A330) with its "AIXF" header parser;
//   0x557A58..0x558D58  SRD, the single DVD / host read request (0x7A08B0) and its locked sce* file wrappers;
//   0x559138..0x559D18  DTR / DTX, the EE <-> IOP transfer objects (the IOP side stays recompiled);
//   0x559D78..0x55CF08  the DVD CI (dvCi*) and host CI file systems: handles, file cache, paths;
//   0x55D240..0x55DD08  LSC, the queued file streamer (32 x 568 bytes at 0x7A32A0);
//   0x55E190..0x55FC00  the hex-named file handles and PS2RNA's channel records / IOP command list.
// Made by p3fes_handgen from SLUS_216.21: every body keeps the recompiled body's registers, frame, spills, $ra links,
// cycle charges and check points (game/include/p3fes/game/hg_cpu.h). The readability pass adds a role comment per
// function (from the instructions; proposed names in brackets, also in symbols/deltas/libs10.sym); the code is the
// faithful generated body. Pair tests: tests/game/test_libs10.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs10.h"

namespace p3fes::recomp_gen {
void fn_InvalidDCache_00503b98(p3fes::EEContext&);
void fn_SRD_Create_00557a58(p3fes::EEContext&);
void fn_SRD_ExecServer_00558500(p3fes::EEContext&);
void fn_SRD_WaitComplete_00557e50(p3fes::EEContext&);
void fn_SyncDCache_00503a58(p3fes::EEContext&);
void fn___env_lock_8_0055dc78(p3fes::EEContext&);
void fn___env_unlock_7_0055dc80(p3fes::EEContext&);
void fn_dtx_create_rmt_00559588(p3fes::EEContext&);
void fn_dtx_destroy_rmt_005595f8(p3fes::EEContext&);
void fn_dvCiExecHndl_00559e80(p3fes::EEContext&);
void fn_dvCiExecServer_00559f48(p3fes::EEContext&);
void fn_dvCiGetInterface_00559d78(p3fes::EEContext&);
void fn_dvCiLoadFcache_0055b300(p3fes::EEContext&);
void fn_dvCiSetRootDir_0055b610(p3fes::EEContext&);
void fn_dvci_analysis_flist_0055ab80(p3fes::EEContext&);
void fn_dvci_get_adr_size_0055b160(p3fes::EEContext&);
void fn_dvci_get_fp_from_fname_0055b030(p3fes::EEContext&);
void fn_dvci_get_fstate_0055b220(p3fes::EEContext&);
void fn_dvci_is_lsn_access_fname_0055b120(p3fes::EEContext&);
void fn_dvci_load_flist_0055ad18(p3fes::EEContext&);
void fn_dvci_search_fstate_0055aea0(p3fes::EEContext&);
void fn_memcmp_005211b8(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sceClose_00508900(p3fes::EEContext&);
void fn_sceInsockSetsockopt_2_0054a928(p3fes::EEContext&);
void fn_sceIoctl_005091e8(p3fes::EEContext&);
void fn_sceLseek64_0050acd8(p3fes::EEContext&);
void fn_sceLseek_00508a78(p3fes::EEContext&);
void fn_sceOpen_00508670(p3fes::EEContext&);
void fn_scePrintf_00505e48(p3fes::EEContext&);
void fn_sceRead_00508cb8(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_srd_exec_dvd_00558138(p3fes::EEContext&);
void fn_srd_wait_dvd_00557d58(p3fes::EEContext&);
void fn_strcat_00523e68(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_sub_53AE08_0053ae08(p3fes::EEContext&);
void fn_sub_5416E8_005416e8(p3fes::EEContext&);
void fn_sub_541760_00541760(p3fes::EEContext&);
void fn_sub_545FC8_00545fc8(p3fes::EEContext&);
void fn_sub_5460E0_005460e0(p3fes::EEContext&);
void fn_sub_546270_00546270(p3fes::EEContext&);
void fn_sub_546368_00546368(p3fes::EEContext&);
void fn_sub_5463A8_005463a8(p3fes::EEContext&);
void fn_sub_546498_00546498(p3fes::EEContext&);
void fn_sub_5466B8_005466b8(p3fes::EEContext&);
void fn_sub_546718_00546718(p3fes::EEContext&);
void fn_sub_546FA0_00546fa0(p3fes::EEContext&);
void fn_sub_547BC0_00547bc0(p3fes::EEContext&);
void fn_sub_547F30_00547f30(p3fes::EEContext&);
void fn_sub_548048_00548048(p3fes::EEContext&);
void fn_sub_5484E0_005484e0(p3fes::EEContext&);
void fn_sub_548678_00548678(p3fes::EEContext&);
void fn_sub_548768_00548768(p3fes::EEContext&);
void fn_sub_54A3C0_0054a3c0(p3fes::EEContext&);
void fn_sub_54D6B8_0054d6b8(p3fes::EEContext&);
void fn_sub_54D7E8_0054d7e8(p3fes::EEContext&);
void fn_sub_54DBE8_0054dbe8(p3fes::EEContext&);
void fn_sub_54DBF0_0054dbf0(p3fes::EEContext&);
void fn_sub_54E0D8_0054e0d8(p3fes::EEContext&);
void fn_sub_54E130_0054e130(p3fes::EEContext&);
void fn_sub_54E180_0054e180(p3fes::EEContext&);
void fn_sub_54E260_0054e260(p3fes::EEContext&);
void fn_sub_54E2C0_0054e2c0(p3fes::EEContext&);
void fn_sub_54E388_0054e388(p3fes::EEContext&);
void fn_sub_54E3C0_0054e3c0(p3fes::EEContext&);
void fn_sub_54E568_0054e568(p3fes::EEContext&);
void fn_sub_54E648_0054e648(p3fes::EEContext&);
void fn_sub_54E658_0054e658(p3fes::EEContext&);
void fn_sub_54E7D8_0054e7d8(p3fes::EEContext&);
void fn_sub_54F8C8_0054f8c8(p3fes::EEContext&);
void fn_sub_550048_00550048(p3fes::EEContext&);
void fn_sub_550238_00550238(p3fes::EEContext&);
void fn_sub_550428_00550428(p3fes::EEContext&);
void fn_sub_550618_00550618(p3fes::EEContext&);
void fn_sub_5513A8_005513a8(p3fes::EEContext&);
void fn_sub_551598_00551598(p3fes::EEContext&);
void fn_sub_551788_00551788(p3fes::EEContext&);
void fn_sub_551978_00551978(p3fes::EEContext&);
void fn_sub_551990_00551990(p3fes::EEContext&);
void fn_sub_5519E8_005519e8(p3fes::EEContext&);
void fn_sub_551A88_00551a88(p3fes::EEContext&);
void fn_sub_551AD8_00551ad8(p3fes::EEContext&);
void fn_sub_551BB0_00551bb0(p3fes::EEContext&);
void fn_sub_551BF0_00551bf0(p3fes::EEContext&);
void fn_sub_551D38_00551d38(p3fes::EEContext&);
void fn_sub_551DA0_00551da0(p3fes::EEContext&);
void fn_sub_551DF8_00551df8(p3fes::EEContext&);
void fn_sub_551E30_00551e30(p3fes::EEContext&);
void fn_sub_551F80_00551f80(p3fes::EEContext&);
void fn_sub_551FF8_00551ff8(p3fes::EEContext&);
void fn_sub_552008_00552008(p3fes::EEContext&);
void fn_sub_552028_00552028(p3fes::EEContext&);
void fn_sub_552080_00552080(p3fes::EEContext&);
void fn_sub_5520B0_005520b0(p3fes::EEContext&);
void fn_sub_552110_00552110(p3fes::EEContext&);
void fn_sub_5523B8_005523b8(p3fes::EEContext&);
void fn_sub_552460_00552460(p3fes::EEContext&);
void fn_sub_552468_00552468(p3fes::EEContext&);
void fn_sub_552480_00552480(p3fes::EEContext&);
void fn_sub_552508_00552508(p3fes::EEContext&);
void fn_sub_552520_00552520(p3fes::EEContext&);
void fn_sub_552600_00552600(p3fes::EEContext&);
void fn_sub_552630_00552630(p3fes::EEContext&);
void fn_sub_552930_00552930(p3fes::EEContext&);
void fn_sub_552BD0_00552bd0(p3fes::EEContext&);
void fn_sub_552D68_00552d68(p3fes::EEContext&);
void fn_sub_5530D0_005530d0(p3fes::EEContext&);
void fn_sub_553188_00553188(p3fes::EEContext&);
void fn_sub_553288_00553288(p3fes::EEContext&);
void fn_sub_5535D0_005535d0(p3fes::EEContext&);
void fn_sub_553838_00553838(p3fes::EEContext&);
void fn_sub_553920_00553920(p3fes::EEContext&);
void fn_sub_553A78_00553a78(p3fes::EEContext&);
void fn_sub_553B70_00553b70(p3fes::EEContext&);
void fn_sub_553BC0_00553bc0(p3fes::EEContext&);
void fn_sub_553FA8_00553fa8(p3fes::EEContext&);
void fn_sub_554048_00554048(p3fes::EEContext&);
void fn_sub_554138_00554138_at_005541a8(p3fes::EEContext&);
void fn_sub_5541D0_005541d0(p3fes::EEContext&);
void fn_sub_5542E8_005542e8(p3fes::EEContext&);
void fn_sub_554360_00554360(p3fes::EEContext&);
void fn_sub_5543C8_005543c8(p3fes::EEContext&);
void fn_sub_554448_00554448(p3fes::EEContext&);
void fn_sub_5544C8_005544c8(p3fes::EEContext&);
void fn_sub_554530_00554530(p3fes::EEContext&);
void fn_sub_5545D8_005545d8(p3fes::EEContext&);
void fn_sub_5546F0_005546f0(p3fes::EEContext&);
void fn_sub_554708_00554708(p3fes::EEContext&);
void fn_sub_554720_00554720(p3fes::EEContext&);
void fn_sub_5547C8_005547c8(p3fes::EEContext&);
void fn_sub_554900_00554900(p3fes::EEContext&);
void fn_sub_554908_00554908(p3fes::EEContext&);
void fn_sub_554948_00554948(p3fes::EEContext&);
void fn_sub_554958_00554958(p3fes::EEContext&);
void fn_sub_554960_00554960(p3fes::EEContext&);
void fn_sub_554968_00554968(p3fes::EEContext&);
void fn_sub_554970_00554970(p3fes::EEContext&);
void fn_sub_554980_00554980(p3fes::EEContext&);
void fn_sub_554990_00554990(p3fes::EEContext&);
void fn_sub_5549C8_005549c8(p3fes::EEContext&);
void fn_sub_554A98_00554a98(p3fes::EEContext&);
void fn_sub_554AE8_00554ae8(p3fes::EEContext&);
void fn_sub_554EA0_00554ea0(p3fes::EEContext&);
void fn_sub_554FD0_00554fd0(p3fes::EEContext&);
void fn_sub_555120_00555120(p3fes::EEContext&);
void fn_sub_555470_00555470(p3fes::EEContext&);
void fn_sub_555570_00555570(p3fes::EEContext&);
void fn_sub_5555A0_005555a0(p3fes::EEContext&);
void fn_sub_555658_00555658(p3fes::EEContext&);
void fn_sub_555788_00555788(p3fes::EEContext&);
void fn_sub_555898_00555898(p3fes::EEContext&);
void fn_sub_557A28_00557a28(p3fes::EEContext&);
void fn_sub_557AE0_00557ae0(p3fes::EEContext&);
void fn_sub_557D20_00557d20(p3fes::EEContext&);
void fn_sub_557D28_00557d28(p3fes::EEContext&);
void fn_sub_557D80_00557d80(p3fes::EEContext&);
void fn_sub_557F80_00557f80(p3fes::EEContext&);
void fn_sub_558320_00558320(p3fes::EEContext&);
void fn_sub_558610_00558610(p3fes::EEContext&);
void fn_sub_558988_00558988(p3fes::EEContext&);
void fn_sub_558A70_00558a70(p3fes::EEContext&);
void fn_sub_558AA8_00558aa8(p3fes::EEContext&);
void fn_sub_558B68_00558b68(p3fes::EEContext&);
void fn_sub_558C20_00558c20(p3fes::EEContext&);
void fn_sub_558C98_00558c98(p3fes::EEContext&);
void fn_sub_558D00_00558d00(p3fes::EEContext&);
void fn_sub_558D58_00558d58(p3fes::EEContext&);
void fn_sub_559138_00559138(p3fes::EEContext&);
void fn_sub_559280_00559280(p3fes::EEContext&);
void fn_sub_559370_00559370(p3fes::EEContext&);
void fn_sub_559398_00559398(p3fes::EEContext&);
void fn_sub_559718_00559718(p3fes::EEContext&);
void fn_sub_5598B0_005598b0(p3fes::EEContext&);
void fn_sub_559918_00559918(p3fes::EEContext&);
void fn_sub_559928_00559928(p3fes::EEContext&);
void fn_sub_559938_00559938(p3fes::EEContext&);
void fn_sub_559B98_00559b98(p3fes::EEContext&);
void fn_sub_559D18_00559d18(p3fes::EEContext&);
void fn_sub_559DA8_00559da8(p3fes::EEContext&);
void fn_sub_559FC0_00559fc0(p3fes::EEContext&);
void fn_sub_559FD8_00559fd8(p3fes::EEContext&);
void fn_sub_55B0F8_0055b0f8(p3fes::EEContext&);
void fn_sub_55B5F0_0055b5f0(p3fes::EEContext&);
void fn_sub_55B798_0055b798(p3fes::EEContext&);
void fn_sub_55B7C8_0055b7c8(p3fes::EEContext&);
void fn_sub_55B910_0055b910(p3fes::EEContext&);
void fn_sub_55B9D8_0055b9d8(p3fes::EEContext&);
void fn_sub_55BB30_0055bb30(p3fes::EEContext&);
void fn_sub_55BDA8_0055bda8(p3fes::EEContext&);
void fn_sub_55C240_0055c240(p3fes::EEContext&);
void fn_sub_55C338_0055c338(p3fes::EEContext&);
void fn_sub_55C3C8_0055c3c8(p3fes::EEContext&);
void fn_sub_55C548_0055c548(p3fes::EEContext&);
void fn_sub_55C5B8_0055c5b8(p3fes::EEContext&);
void fn_sub_55C610_0055c610(p3fes::EEContext&);
void fn_sub_55C9D0_0055c9d0(p3fes::EEContext&);
void fn_sub_55CE18_0055ce18(p3fes::EEContext&);
void fn_sub_55CEE0_0055cee0(p3fes::EEContext&);
void fn_sub_55CF08_0055cf08(p3fes::EEContext&);
void fn_sub_55D240_0055d240(p3fes::EEContext&);
void fn_sub_55D3A8_0055d3a8(p3fes::EEContext&);
void fn_sub_55D428_0055d428(p3fes::EEContext&);
void fn_sub_55D5C0_0055d5c0(p3fes::EEContext&);
void fn_sub_55D600_0055d600(p3fes::EEContext&);
void fn_sub_55D668_0055d668(p3fes::EEContext&);
void fn_sub_55D730_0055d730(p3fes::EEContext&);
void fn_sub_55DB58_0055db58(p3fes::EEContext&);
void fn_sub_55DB88_0055db88(p3fes::EEContext&);
void fn_sub_55DBA8_0055dba8(p3fes::EEContext&);
void fn_sub_55DBC0_0055dbc0(p3fes::EEContext&);
void fn_sub_55DBE8_0055dbe8(p3fes::EEContext&);
void fn_sub_55DC88_0055dc88(p3fes::EEContext&);
void fn_sub_55DD08_0055dd08(p3fes::EEContext&);
void fn_sub_55DDC8_0055ddc8(p3fes::EEContext&);
void fn_sub_55DEF0_0055def0(p3fes::EEContext&);
void fn_sub_55DFB8_0055dfb8(p3fes::EEContext&);
void fn_sub_55E0C0_0055e0c0(p3fes::EEContext&);
void fn_sub_55E190_0055e190(p3fes::EEContext&);
void fn_sub_55E1A8_0055e1a8(p3fes::EEContext&);
void fn_sub_55E1C0_0055e1c0(p3fes::EEContext&);
void fn_sub_55E1D8_0055e1d8(p3fes::EEContext&);
void fn_sub_55E208_0055e208(p3fes::EEContext&);
void fn_sub_55E220_0055e220(p3fes::EEContext&);
void fn_sub_55E318_0055e318(p3fes::EEContext&);
void fn_sub_55E320_0055e320(p3fes::EEContext&);
void fn_sub_55E378_0055e378(p3fes::EEContext&);
void fn_sub_55E390_0055e390(p3fes::EEContext&);
void fn_sub_55E3B0_0055e3b0(p3fes::EEContext&);
void fn_sub_55E428_0055e428(p3fes::EEContext&);
void fn_sub_55E940_0055e940(p3fes::EEContext&);
void fn_sub_55EA80_0055ea80(p3fes::EEContext&);
void fn_sub_55EA98_0055ea98(p3fes::EEContext&);
void fn_sub_55EB08_0055eb08(p3fes::EEContext&);
void fn_sub_55EDB8_0055edb8(p3fes::EEContext&);
void fn_sub_55F1C8_0055f1c8(p3fes::EEContext&);
void fn_sub_55F218_0055f218(p3fes::EEContext&);
void fn_sub_55F688_0055f688(p3fes::EEContext&);
void fn_sub_55FB20_0055fb20(p3fes::EEContext&);
void fn_sub_55FB98_0055fb98(p3fes::EEContext&);
void fn_sub_55FBA0_0055fba0(p3fes::EEContext&);
void fn_sub_55FC00_0055fc00(p3fes::EEContext&);
void fn_sub_5617C0_005617c0(p3fes::EEContext&);
void fn_sub_5617D8_005617d8(p3fes::EEContext&);
void fn_sub_562388_00562388(p3fes::EEContext&);
void fn_sub_563C28_00563c28(p3fes::EEContext&);
void fn_sub_564978_00564978(p3fes::EEContext&);
void fn_sub_564990_00564990(p3fes::EEContext&);
void fn_sub_5649A8_005649a8(p3fes::EEContext&);
void fn_sub_5649D8_005649d8(p3fes::EEContext&);
void fn_sub_564A20_00564a20(p3fes::EEContext&);
void fn_sub_564A50_00564a50(p3fes::EEContext&);
void fn_sub_5655E8_005655e8(p3fes::EEContext&);
void fn_vsprintf_005288c8(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x00550048 sub_550048 -- 496 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// AHX (CRI's MPEG audio layer II) polyphase synthesis window, one of the V-buffer phase variants the table at 0x798690
// selects ($a0 V buffer, $a1 the s16 window, $a2 out): 32 samples, each a 16-tap s16 x s16 dot product (taps 32 / 96
// halfwords apart), clamped to s16 after >> 11 (the MMI mult1 pairs the products).
void sub_550048(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x00550048
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t8 = a1;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 32;
    for (;;) {
        // 0x00550068
        charge(ctx, 99);
        v0 = s1;
        lh(a3, t8, 0);
        lh(a0, v0, 0);
        s1 = addiu(v0, 2);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        mult(t9, a3, a0);
        lh(a0, v0, 0);
        lh(a2, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult1(a1, a1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(a2, a2, a0);
        lh(a0, v0, 0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(a3, a3, v1);
        lh(t3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(t0, t0, a0);
        lh(a0, v0, 0);
        lh(t5, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(t3, t3, v1);
        t9 = addu(t9, a1);
        lh(t6, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t5, t5, a0);
        t9 = addu(t9, a2);
        lh(t7, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t6, t6, v1);
        t9 = addu(t9, a3);
        lh(t4, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t7, t7, a0);
        t9 = addu(t9, t0);
        lh(t2, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t4, t4, v1);
        lh(t1, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t3);
        mult(t2, t2, a0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        v0 = addiu(v0, -1856);
        t9 = addu(t9, t5);
        mult(t1, t1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t6);
        mult(t0, t0, a0);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        t9 = addu(t9, t7);
        mult(a3, a3, v1);
        lh(v1, t8, 0);
        lh(a2, v0, 192);
        v0 = 0x3FF0000;
        t9 = addu(t9, t4);
        mult(a1, a1, a0);
        t9 = addu(t9, t2);
        mult(v1, v1, a2);
        t9 = addu(t9, t1);
        v0 = v0 | 0xF800;
        t9 = addu(t9, t0);
        t9 = addu(t9, a3);
        t9 = addu(t9, a1);
        t9 = addu(t9, v1);
        v0 = slt(v0, t9);
        t8 = addiu(t8, 2);
        if (v0 == 0) {
            // 0x00550200
            charge(ctx, 4);
            v0 = lui(0xFC00);
            v0 = slt(t9, v0);
            if (v0 == 0) {
                v0 = sra(t9, 11);
            } else {
                // 0x00550210
                charge(ctx, 1);
                v0 = si(-32768);
            }
        } else {
            // 0x005501f4
            charge(ctx, 2);
            v0 = 32767;
        }
        // 0x00550214
        charge(ctx, 4);
        sh(v0, s0, 0);
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00550224
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00550238 sub_550238 -- 496 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// AHX (CRI's MPEG audio layer II) polyphase synthesis window, one of the V-buffer phase variants the table at 0x798690
// selects ($a0 V buffer, $a1 the s16 window, $a2 out): 32 samples, each a 16-tap s16 x s16 dot product (taps 32 / 96
// halfwords apart), clamped to s16 after >> 11 (the MMI mult1 pairs the products).
void sub_550238(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x00550238
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t8 = a1;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 32;
    for (;;) {
        // 0x00550258
        charge(ctx, 99);
        v0 = s1;
        lh(a3, t8, 0);
        lh(a0, v0, 0);
        s1 = addiu(v0, 2);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        mult(t9, a3, a0);
        lh(a0, v0, 0);
        lh(a2, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult1(a1, a1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(a2, a2, a0);
        lh(a0, v0, 0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(a3, a3, v1);
        lh(t3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(t0, t0, a0);
        lh(a0, v0, 0);
        lh(t5, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(t3, t3, v1);
        t9 = addu(t9, a1);
        lh(t6, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t5, t5, a0);
        t9 = addu(t9, a2);
        lh(t7, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t6, t6, v1);
        t9 = addu(t9, a3);
        lh(t4, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t7, t7, a0);
        t9 = addu(t9, t0);
        lh(t2, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t4, t4, v1);
        lh(t1, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, -1984);
        t9 = addu(t9, t3);
        mult(t2, t2, a0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t9 = addu(t9, t5);
        mult(t1, t1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t6);
        mult(t0, t0, a0);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        t9 = addu(t9, t7);
        mult(a3, a3, v1);
        lh(v1, t8, 0);
        lh(a2, v0, 192);
        v0 = 0x3FF0000;
        t9 = addu(t9, t4);
        mult(a1, a1, a0);
        t9 = addu(t9, t2);
        mult(v1, v1, a2);
        t9 = addu(t9, t1);
        v0 = v0 | 0xF800;
        t9 = addu(t9, t0);
        t9 = addu(t9, a3);
        t9 = addu(t9, a1);
        t9 = addu(t9, v1);
        v0 = slt(v0, t9);
        t8 = addiu(t8, 2);
        if (v0 == 0) {
            // 0x005503f0
            charge(ctx, 4);
            v0 = lui(0xFC00);
            v0 = slt(t9, v0);
            if (v0 == 0) {
                v0 = sra(t9, 11);
            } else {
                // 0x00550400
                charge(ctx, 1);
                v0 = si(-32768);
            }
        } else {
            // 0x005503e4
            charge(ctx, 2);
            v0 = 32767;
        }
        // 0x00550404
        charge(ctx, 4);
        sh(v0, s0, 0);
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00550414
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00550428 sub_550428 -- 496 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// AHX (CRI's MPEG audio layer II) polyphase synthesis window, one of the V-buffer phase variants the table at 0x798690
// selects ($a0 V buffer, $a1 the s16 window, $a2 out): 32 samples, each a 16-tap s16 x s16 dot product (taps 32 / 96
// halfwords apart), clamped to s16 after >> 11 (the MMI mult1 pairs the products).
void sub_550428(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x00550428
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t8 = a1;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 32;
    for (;;) {
        // 0x00550448
        charge(ctx, 99);
        v0 = s1;
        lh(a3, t8, 0);
        lh(a0, v0, 0);
        s1 = addiu(v0, 2);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        mult(t9, a3, a0);
        lh(a0, v0, 0);
        lh(a2, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult1(a1, a1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(a2, a2, a0);
        lh(a0, v0, 0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(a3, a3, v1);
        lh(t3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(t0, t0, a0);
        lh(a0, v0, 0);
        lh(t5, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(t3, t3, v1);
        t9 = addu(t9, a1);
        lh(t6, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t5, t5, a0);
        t9 = addu(t9, a2);
        lh(t7, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t6, t6, v1);
        t9 = addu(t9, a3);
        lh(t4, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t7, t7, a0);
        t9 = addu(t9, t0);
        lh(t2, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, -1856);
        t8 = addiu(t8, 2);
        mult(t4, t4, v1);
        lh(t1, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t3);
        mult(t2, t2, a0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t9 = addu(t9, t5);
        mult(t1, t1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t6);
        mult(t0, t0, a0);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        t9 = addu(t9, t7);
        mult(a3, a3, v1);
        lh(v1, t8, 0);
        lh(a2, v0, 192);
        v0 = 0x3FF0000;
        t9 = addu(t9, t4);
        mult(a1, a1, a0);
        t9 = addu(t9, t2);
        mult(v1, v1, a2);
        t9 = addu(t9, t1);
        v0 = v0 | 0xF800;
        t9 = addu(t9, t0);
        t9 = addu(t9, a3);
        t9 = addu(t9, a1);
        t9 = addu(t9, v1);
        v0 = slt(v0, t9);
        t8 = addiu(t8, 2);
        if (v0 == 0) {
            // 0x005505e0
            charge(ctx, 4);
            v0 = lui(0xFC00);
            v0 = slt(t9, v0);
            if (v0 == 0) {
                v0 = sra(t9, 11);
            } else {
                // 0x005505f0
                charge(ctx, 1);
                v0 = si(-32768);
            }
        } else {
            // 0x005505d4
            charge(ctx, 2);
            v0 = 32767;
        }
        // 0x005505f4
        charge(ctx, 4);
        sh(v0, s0, 0);
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00550604
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00550618 sub_550618 -- 496 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// AHX (CRI's MPEG audio layer II) polyphase synthesis window, one of the V-buffer phase variants the table at 0x798690
// selects ($a0 V buffer, $a1 the s16 window, $a2 out): 32 samples, each a 16-tap s16 x s16 dot product (taps 32 / 96
// halfwords apart), clamped to s16 after >> 11 (the MMI mult1 pairs the products).
void sub_550618(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x00550618
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t8 = a1;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 32;
    for (;;) {
        // 0x00550638
        charge(ctx, 99);
        v0 = s1;
        lh(a3, t8, 0);
        lh(a0, v0, 0);
        s1 = addiu(v0, 2);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        mult(t9, a3, a0);
        lh(a0, v0, 0);
        lh(a2, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult1(a1, a1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(a2, a2, a0);
        lh(a0, v0, 0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(a3, a3, v1);
        lh(t3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(t0, t0, a0);
        lh(a0, v0, 0);
        lh(t5, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(t3, t3, v1);
        t9 = addu(t9, a1);
        lh(t6, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t5, t5, a0);
        t9 = addu(t9, a2);
        lh(t7, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t6, t6, v1);
        t9 = addu(t9, a3);
        lh(t4, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, -1984);
        t8 = addiu(t8, 2);
        mult(t7, t7, a0);
        t9 = addu(t9, t0);
        lh(t2, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t4, t4, v1);
        lh(t1, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t3);
        mult(t2, t2, a0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t9 = addu(t9, t5);
        mult(t1, t1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t6);
        mult(t0, t0, a0);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        t9 = addu(t9, t7);
        mult(a3, a3, v1);
        lh(v1, t8, 0);
        lh(a2, v0, 192);
        v0 = 0x3FF0000;
        t9 = addu(t9, t4);
        mult(a1, a1, a0);
        t9 = addu(t9, t2);
        mult(v1, v1, a2);
        t9 = addu(t9, t1);
        v0 = v0 | 0xF800;
        t9 = addu(t9, t0);
        t9 = addu(t9, a3);
        t9 = addu(t9, a1);
        t9 = addu(t9, v1);
        v0 = slt(v0, t9);
        t8 = addiu(t8, 2);
        if (v0 == 0) {
            // 0x005507d0
            charge(ctx, 4);
            v0 = lui(0xFC00);
            v0 = slt(t9, v0);
            if (v0 == 0) {
                v0 = sra(t9, 11);
            } else {
                // 0x005507e0
                charge(ctx, 1);
                v0 = si(-32768);
            }
        } else {
            // 0x005507c4
            charge(ctx, 2);
            v0 = 32767;
        }
        // 0x005507e4
        charge(ctx, 4);
        sh(v0, s0, 0);
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005507f4
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005513A8 sub_5513A8 -- 496 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// AHX (CRI's MPEG audio layer II) polyphase synthesis window, one of the V-buffer phase variants the table at 0x798690
// selects ($a0 V buffer, $a1 the s16 window, $a2 out): 32 samples, each a 16-tap s16 x s16 dot product (taps 32 / 96
// halfwords apart), clamped to s16 after >> 11 (the MMI mult1 pairs the products).
void sub_5513A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x005513a8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t8 = a1;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 32;
    for (;;) {
        // 0x005513c8
        charge(ctx, 99);
        v0 = s1;
        lh(a3, t8, 0);
        lh(a0, v0, 0);
        s1 = addiu(v0, 2);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        mult(t9, a3, a0);
        lh(a0, v0, 0);
        lh(a2, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, -1856);
        mult1(a1, a1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(a2, a2, a0);
        lh(a0, v0, 0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(a3, a3, v1);
        lh(t3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(t0, t0, a0);
        lh(a0, v0, 0);
        lh(t5, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(t3, t3, v1);
        t9 = addu(t9, a1);
        lh(t6, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t5, t5, a0);
        t9 = addu(t9, a2);
        lh(t7, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t6, t6, v1);
        t9 = addu(t9, a3);
        lh(t4, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t7, t7, a0);
        t9 = addu(t9, t0);
        lh(t2, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t4, t4, v1);
        lh(t1, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t3);
        mult(t2, t2, a0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t9 = addu(t9, t5);
        mult(t1, t1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t6);
        mult(t0, t0, a0);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        t9 = addu(t9, t7);
        mult(a3, a3, v1);
        lh(v1, t8, 0);
        lh(a2, v0, 192);
        v0 = 0x3FF0000;
        t9 = addu(t9, t4);
        mult(a1, a1, a0);
        t9 = addu(t9, t2);
        mult(v1, v1, a2);
        t9 = addu(t9, t1);
        v0 = v0 | 0xF800;
        t9 = addu(t9, t0);
        t9 = addu(t9, a3);
        t9 = addu(t9, a1);
        t9 = addu(t9, v1);
        v0 = slt(v0, t9);
        t8 = addiu(t8, 2);
        if (v0 == 0) {
            // 0x00551560
            charge(ctx, 4);
            v0 = lui(0xFC00);
            v0 = slt(t9, v0);
            if (v0 == 0) {
                v0 = sra(t9, 11);
            } else {
                // 0x00551570
                charge(ctx, 1);
                v0 = si(-32768);
            }
        } else {
            // 0x00551554
            charge(ctx, 2);
            v0 = 32767;
        }
        // 0x00551574
        charge(ctx, 4);
        sh(v0, s0, 0);
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00551584
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00551598 sub_551598 -- 496 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// AHX (CRI's MPEG audio layer II) polyphase synthesis window, one of the V-buffer phase variants the table at 0x798690
// selects ($a0 V buffer, $a1 the s16 window, $a2 out): 32 samples, each a 16-tap s16 x s16 dot product (taps 32 / 96
// halfwords apart), clamped to s16 after >> 11 (the MMI mult1 pairs the products).
void sub_551598(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x00551598
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t8 = a1;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 32;
    for (;;) {
        // 0x005515b8
        charge(ctx, 99);
        v0 = s1;
        lh(a3, t8, 0);
        lh(a0, v0, 0);
        s1 = addiu(v0, 2);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        lh(v1, v0, 0);
        v0 = addiu(v0, -1984);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        mult(t9, a3, a0);
        lh(a0, v0, 0);
        lh(a2, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult1(a1, a1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(a2, a2, a0);
        lh(a0, v0, 0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(a3, a3, v1);
        lh(t3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(t0, t0, a0);
        lh(a0, v0, 0);
        lh(t5, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(t3, t3, v1);
        t9 = addu(t9, a1);
        lh(t6, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t5, t5, a0);
        t9 = addu(t9, a2);
        lh(t7, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t6, t6, v1);
        t9 = addu(t9, a3);
        lh(t4, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t7, t7, a0);
        t9 = addu(t9, t0);
        lh(t2, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t4, t4, v1);
        lh(t1, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t3);
        mult(t2, t2, a0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t9 = addu(t9, t5);
        mult(t1, t1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t6);
        mult(t0, t0, a0);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        t9 = addu(t9, t7);
        mult(a3, a3, v1);
        lh(v1, t8, 0);
        lh(a2, v0, 192);
        v0 = 0x3FF0000;
        t9 = addu(t9, t4);
        mult(a1, a1, a0);
        t9 = addu(t9, t2);
        mult(v1, v1, a2);
        t9 = addu(t9, t1);
        v0 = v0 | 0xF800;
        t9 = addu(t9, t0);
        t9 = addu(t9, a3);
        t9 = addu(t9, a1);
        t9 = addu(t9, v1);
        v0 = slt(v0, t9);
        t8 = addiu(t8, 2);
        if (v0 == 0) {
            // 0x00551750
            charge(ctx, 4);
            v0 = lui(0xFC00);
            v0 = slt(t9, v0);
            if (v0 == 0) {
                v0 = sra(t9, 11);
            } else {
                // 0x00551760
                charge(ctx, 1);
                v0 = si(-32768);
            }
        } else {
            // 0x00551744
            charge(ctx, 2);
            v0 = 32767;
        }
        // 0x00551764
        charge(ctx, 4);
        sh(v0, s0, 0);
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00551774
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00551788 sub_551788 -- 496 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// AHX (CRI's MPEG audio layer II) polyphase synthesis window, one of the V-buffer phase variants the table at 0x798690
// selects ($a0 V buffer, $a1 the s16 window, $a2 out): 32 samples, each a 16-tap s16 x s16 dot product (taps 32 / 96
// halfwords apart), clamped to s16 after >> 11 (the MMI mult1 pairs the products).
void sub_551788(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x00551788
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t8 = a1;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 32;
    for (;;) {
        // 0x005517a8
        charge(ctx, 99);
        v0 = s1;
        lh(a3, t8, 0);
        lh(a0, v0, 0);
        s1 = addiu(v0, 2);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, -1856);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        mult(t9, a3, a0);
        lh(a0, v0, 0);
        lh(a2, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult1(a1, a1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(a2, a2, a0);
        lh(a0, v0, 0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(a3, a3, v1);
        lh(t3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(t0, t0, a0);
        lh(a0, v0, 0);
        lh(t5, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(t3, t3, v1);
        t9 = addu(t9, a1);
        lh(t6, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t5, t5, a0);
        t9 = addu(t9, a2);
        lh(t7, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t6, t6, v1);
        t9 = addu(t9, a3);
        lh(t4, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t7, t7, a0);
        t9 = addu(t9, t0);
        lh(t2, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t4, t4, v1);
        lh(t1, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t3);
        mult(t2, t2, a0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t9 = addu(t9, t5);
        mult(t1, t1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t6);
        mult(t0, t0, a0);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        t9 = addu(t9, t7);
        mult(a3, a3, v1);
        lh(v1, t8, 0);
        lh(a2, v0, 192);
        v0 = 0x3FF0000;
        t9 = addu(t9, t4);
        mult(a1, a1, a0);
        t9 = addu(t9, t2);
        mult(v1, v1, a2);
        t9 = addu(t9, t1);
        v0 = v0 | 0xF800;
        t9 = addu(t9, t0);
        t9 = addu(t9, a3);
        t9 = addu(t9, a1);
        t9 = addu(t9, v1);
        v0 = slt(v0, t9);
        t8 = addiu(t8, 2);
        if (v0 == 0) {
            // 0x00551940
            charge(ctx, 4);
            v0 = lui(0xFC00);
            v0 = slt(t9, v0);
            if (v0 == 0) {
                v0 = sra(t9, 11);
            } else {
                // 0x00551950
                charge(ctx, 1);
                v0 = si(-32768);
            }
        } else {
            // 0x00551934
            charge(ctx, 2);
            v0 = 32767;
        }
        // 0x00551954
        charge(ctx, 4);
        sh(v0, s0, 0);
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00551964
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00551978 sub_551978 -- 8 bytes; leaf frame (no stack)
// The AHX profiling clock: returns 0 (the timing stores around the decoder's steps read it).
void sub_551978(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00551978
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00551990 sub_551990 -- 84 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// AHX synthesis init (reference counted, 0x798640): on the first call clears the 16 object slots (0x798648) and builds
// the aligned tables.
void sub_551990(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00551990
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7A0000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, -31168);  // &0x798640
    lw(v0, s0, 0);  // 0x798640
    sd(ra, sp, 0x8);
    if (v0 == 0) {
        // 0x005519ac
        charge(ctx, 8);
        a0 = 0x7A0000;
        a1 = 0;
        a0 = addiu(a0, -31160);  // &0x798648
        a2 = 64;
        jal(ctx, 0x5519B8u, gen::fn_memset_00521408);
        jal(ctx, 0x5519C0u, gen::fn_sub_5519E8_005519e8);
        lw(v0, s0, 0);
    }
    // 0x005519cc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = addiu(v0, 1);
    ld(ra, sp, 0x8);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005519E8 sub_5519E8 -- 156 bytes; leaf frame (no stack)
// Copies the synthesis tables once (flag 0x798644): 1025 bytes to a 32-aligned buffer (ptr 0x79868C) and 4097 bytes to
// another (ptr 0x798688).
void sub_5519E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005519e8
    enter(ctx, 4);  // entry check point + this block's cycles
    t0 = 0x7A0000;
    lw(v0, t0, -31164);  // 0x798644
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 0x7A0000;
    if (!cc) {
        // 0x005519f8
        charge(ctx, 8);
        v1 = si(-32);
        v0 = addiu(v0, -27329);
        a0 = 0x7A0000;
        a2 = v0 & v1;
        a3 = addiu(v0, -31);
        sw(a2, a0, -31092);  // 0x79868C
        a1 = 1024;
        for (;;) {
            // 0x00551a18
            charge(ctx, 7);
            v0 = addu(a3, a1);
            a0 = addu(a2, a1);
            lbu(v1, v0, 0);
            a1 = addiu(a1, -1);
            sb(v1, a0, 0);
            if (i64(a1) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00551a34
        charge(ctx, 9);
        v0 = 0x790000;
        v1 = si(-32);
        v0 = addiu(v0, 30239);  // &0x79761F
        a0 = 0x7A0000;
        a2 = v0 & v1;
        a3 = addiu(v0, -31);  // &0x797600
        sw(a2, a0, -31096);  // 0x798688
        a1 = 4096;
        for (;;) {
            // 0x00551a58
            charge(ctx, 7);
            v0 = addu(a3, a1);
            a0 = addu(a2, a1);
            lbu(v1, v0, 0);
            a1 = addiu(a1, -1);
            sb(v1, a0, 0);
            if (i64(a1) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00551a74
        charge(ctx, 2);
        v0 = 1;
        sw(v0, t0, -31164);
    }
    // 0x00551a7c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00551A88 sub_551A88 -- 76 bytes; frame 0x10: ra sp+0x0
// AHX synthesis finish: drops the reference count (0x798640); at zero clears the 16 object slots.
void sub_551A88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00551a88
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x7A0000;
    sd(ra, sp, 0x0);
    v1 = addiu(v1, -31168);  // &0x798640
    lw(v0, v1, 0);  // 0x798640
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x798640
    if (v0 != 0) {
        // 0x00551ac8
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00551aa8
    charge(ctx, 7);
    a0 = 0x7A0000;
    ld(ra, sp, 0x0);
    a1 = 0;
    a0 = addiu(a0, -31160);  // &0x798648
    a2 = 64;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x00551AD8 sub_551AD8 -- 216 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// AHX synthesis create: takes a free slot of 16 (0x798648), clears the work ($a0, $a1 bytes), sets id, offsets 64 / 64
// and the two table pointers; returns it or 0.
void sub_551AD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00551ad8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = 0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s2 = 0x7A0000;
    sd(ra, sp, 0x18);
    v0 = addiu(s2, -31160);  // &0x798648
    lw(t0, v0, 0);  // 0x798648
    s1 = a0;
    if (t0 != 0) {
        // 0x00551b04
        charge(ctx, 3);
        v1 = v0;
        s0 = addiu(s0, 1);
        for (;;) {
            // 0x00551b10
            charge(ctx, 3);
            v0 = slti(s0, 16);
            v1 = addiu(v1, 4);
            if (v0 != 0) {
                // 0x00551b1c
                charge(ctx, 6);
                lw(t0, v1, 0);
                if (t0 != 0) {
                    s0 = addiu(s0, 1);
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x00551b34
    charge(ctx, 3);
    v1 = 16;
    v0 = 0;
    if (s0 != v1) {
        // 0x00551b40
        charge(ctx, 22);
        a2 = a1;
        a1 = 0;
        a0 = s1;
        jal(ctx, 0x551B48u, gen::fn_memset_00521408);
        v1 = addiu(s2, -31160);
        v0 = sll(s0, 2);
        t0 = s1;
        v0 = addu(v0, v1);
        a0 = 64;
        sw(s1, v0, 0);
        v0 = t0;
        sb(s0, t0, 1);
        a2 = 0x7A0000;
        sw(a0, t0, 4);
        a3 = 0x7A0000;
        sw(a0, t0, 8);
        a1 = 1;
        lw(v1, a2, -31092);  // 0x79868C
        sw(v1, t0, 16);
        lw(a0, a3, -31096);  // 0x798688
        sb(a1, t0, 0);
        sw(a0, t0, 12);
    }
    // 0x00551b98 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00551BB0 sub_551BB0 -- 60 bytes; frame 0x10: ra sp+0x8, s0 sp+0x0
// AHX synthesis destroy: clears the object ($a0) and its slot in the 16-entry table.
void sub_551BB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00551bb0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(ra, sp, 0x8);
    a2 = 4116;
    sd(s0, sp, 0x0);
    link(ctx, 0x551BC4u);  // $ra first: the delay slot below depends on it
    lb(s0, a0, 1);
    call(ctx, gen::fn_memset_00521408);
    ld(ra, sp, 0x8);
    s0 = sll(s0, 2);
    at = 0x7A0000;
    at = addu(at, s0);
    sw(zero, at, -31160);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00551BF0 sub_551BF0 -- 324 bytes; frame 0x50: s3 sp+0x18, s1 sp+0x8, s2 sp+0x10, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s7 sp+0x38, fp sp+0x40, s0 sp+0x0, ra sp+0x48
// One AHX synthesis step for channel $a2: steps the channel's V offset back by 64 (mod 1024), runs the DCT (0x54F8C8)
// into the V buffer, then the window variant of the table 0x798690 (jalr) into $a3. Spins forever on a misaligned
// buffer.
void sub_551BF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00551bf0
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s3, sp, 0x18);
    s3 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s4, sp, 0x20);
    s4 = sll(a2, 11);
    sd(s5, sp, 0x28);
    s5 = addiu(s3, 4);
    sd(s6, sp, 0x30);
    s6 = sll(a2, 2);
    sd(s7, sp, 0x38);
    s7 = 0x7A0000;
    sd(fp, sp, 0x40);
    fp = a3;
    sd(s0, sp, 0x0);
    a0 = addu(s5, s6);
    sd(ra, sp, 0x48);
    v1 = addu(s3, s4);
    lw(v0, a0, 0);
    lw(s0, s3, 12);
    v0 = addiu(v0, -64);
    v0 = v0 & 0x3FF;
    sw(v0, a0, 0);
    v0 = sll(v0, 1);
    v1 = addu(v1, v0);
    s1 = addiu(v1, 20);
    jal(ctx, 0x551C5Cu, gen::fn_sub_551978_00551978);
    v1 = s2 & 0x1F;
    sw(v0, s7, -31024);  // 0x7986D0
    if (v1 == 0) {
        goto L_00551c70_1;
    }
    for (;;) {
    L_00551c80:
        charge(ctx, 7);
        backedge(ctx);
    }
L_00551c70_1:
    charge(ctx, 3);
    v0 = s0 & 0x1F;
    a0 = s2;
    if (v0 != 0) {
        // 0x00551c7c
        charge(ctx, 1);
        goto L_00551c80;
    }
    // 0x00551ca0
    charge(ctx, 37);
    s2 = addiu(s7, -31024);
    a1 = s0;
    a2 = s1;
    jal(ctx, 0x551CA8u, gen::fn_sub_54F8C8_0054f8c8);
    s1 = addu(s3, s4);
    jal(ctx, 0x551CB0u, gen::fn_sub_551978_00551978);
    sw(v0, s2, 16);
    v0 = addu(s5, s6);
    link(ctx, 0x551CC0u);  // $ra first: the delay slot below depends on it
    lw(s0, v0, 0);
    call(ctx, gen::fn_sub_551978_00551978);
    sw(v0, s2, 0);
    s1 = addiu(s1, 20);
    v1 = sra(s0, 6);
    s0 = sll(s0, 1);
    v1 = sll(v1, 2);
    lw(a1, s3, 16);
    v0 = 0x7A0000;
    v0 = addu(v0, v1);
    lw(v0, v0, -31088);
    a0 = addu(s1, s0);
    a2 = fp;
    jalr(ctx, 0x551CF0u, v0.u());
    jal(ctx, 0x551CF8u, gen::fn_sub_551978_00551978);
    sw(v0, s2, 16);
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

// 0x00551D38 sub_551D38 -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// AHX decoder init (reference counted, 0x7986E8): first call inits the synthesis (0x54E0D8) and clears the 16 decoder
// slots (0x7986F0).
void sub_551D38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00551d38
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x7A0000;
    sd(s0, sp, 0x0);
    s0 = addiu(v1, -31000);  // &0x7986E8
    sd(ra, sp, 0x8);
    v0 = 0x7A0000;
    lw(a1, s0, 0);  // 0x7986E8
    v0 = addiu(v0, -30996);  // "p1|"
    lw(v1, v0, 0);  // 0x7986EC
    lw(a0, v0, 0);  // 0x7986EC
    if (a1 != 0) {
        v0 = addiu(a1, 1);
    } else {
        // 0x00551d68
        charge(ctx, 9);
        jal(ctx, 0x551D68u, gen::fn_sub_54E0D8_0054e0d8);
        a0 = 0x7A0000;
        a1 = 0;
        a0 = addiu(a0, -30992);  // &0x7986F0
        a2 = 64;
        jal(ctx, 0x551D7Cu, gen::fn_memset_00521408);
        lw(a1, s0, 0);
        v0 = addiu(a1, 1);
    }
    // 0x00551d8c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x8);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00551DA0 sub_551DA0 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// AHX decoder finish: the last reference clears the 16 decoder slots and finishes the synthesis (0x54E130).
void sub_551DA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00551da0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7A0000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, -31000);  // &0x7986E8
    lw(v0, s0, 0);  // 0x7986E8
    v1 = 1;
    sd(ra, sp, 0x8);
    if (v0 == v1) {
        // 0x00551dc0
        charge(ctx, 8);
        a0 = 0x7A0000;
        a1 = 0;
        a0 = addiu(a0, -30992);  // &0x7986F0
        a2 = 64;
        jal(ctx, 0x551DCCu, gen::fn_memset_00521408);
        jal(ctx, 0x551DD4u, gen::fn_sub_54E130_0054e130);
        lw(v0, s0, 0);
    }
    // 0x00551de0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = addiu(v0, -1);
    ld(ra, sp, 0x8);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00551DF8 sub_551DF8 -- 56 bytes; leaf frame (no stack)
// Resets a decoder's ($a0) play counters: end sample 0x7FFFFFFF, limit -1, the counters and flag +7 zero; returns
// 0x7FFFFFFF.
void sub_551DF8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00551df8
    enter(ctx, 14);  // entry check point + this block's cycles
    v0 = 0x7FFF0000;
    v1 = si(-1);
    v0 = v0 | 0xFFFF;
    sw(v1, a0, 48);
    sw(v0, a0, 44);
    sb(zero, a0, 7);
    sw(zero, a0, 8);
    sw(zero, a0, 28);
    sw(zero, a0, 32);
    sw(zero, a0, 36);
    sw(zero, a0, 40);
    sw(zero, a0, 52);
    sw(zero, a0, 56);
}

// 0x00551E30 sub_551E30 -- 336 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// AHX decoder create: free slot of 16, clears the work, opens the bit reader (0x54D6B8) and the MPEG decoder
// (0x54E180, work +80, 6716 bytes), copies $a1 stream handles, resets the counters.
void sub_551E30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00551e30
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a3;
    sd(s1, sp, 0x8);
    s1 = 0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = a0;
    sd(s4, sp, 0x20);
    s4 = 0x7A0000;
    sd(s5, sp, 0x28);
    s5 = a2;
    sd(ra, sp, 0x30);
    v1 = addiu(s4, -30992);  // &0x7986F0
    lw(v0, v1, 0);  // 0x7986F0
    a2 = t0;
    if (v0 != 0) {
        // 0x00551e78
        charge(ctx, 2);
        s1 = addiu(s1, 1);
        for (;;) {
            // 0x00551e80
            charge(ctx, 3);
            v0 = slti(s1, 16);
            v1 = addiu(v1, 4);
            if (v0 != 0) {
                // 0x00551e8c
                charge(ctx, 6);
                lw(v0, v1, 0);
                if (v0 != 0) {
                    s1 = addiu(s1, 1);
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x00551ea4
    charge(ctx, 3);
    v1 = 16;
    v0 = 0;
    if (s1 != v1) {
        // 0x00551eb0
        charge(ctx, 13);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x551EB4u, gen::fn_memset_00521408);
        v1 = addiu(s4, -30992);
        v0 = sll(s1, 2);
        sw(s1, s0, 60);
        v0 = addu(v0, v1);
        a0 = s3;
        link(ctx, 0x551ED0u);  // $ra first: the delay slot below depends on it
        sw(s0, v0, 0);
        call(ctx, gen::fn_sub_54D6B8_0054d6b8);
        v1 = v0;
        sw(v1, s0, 12);
        if (v1 != 0) {
            // 0x00551ee4
            charge(ctx, 6);
            a0 = addiu(s0, 80);
            a1 = 6716;
            jal(ctx, 0x551EE8u, gen::fn_sub_54E180_0054e180);
            v1 = v0;
            sw(v1, s0, 0);
            if (v1 != 0) {
                // 0x00551efc
                charge(ctx, 4);
                sw(s3, s0, 16);
                a1 = 0;
                sb(s2, s0, 6);
                if (i64(s2) > 0) {
                    // 0x00551f0c
                    charge(ctx, 3);
                    a2 = s5;
                    a0 = addiu(s0, 20);
                    for (;;) {
                        // 0x00551f18
                        charge(ctx, 7);
                        lw(v1, a2, 0);
                        a2 = addiu(a2, 4);
                        a1 = addiu(a1, 1);
                        v0 = slt(a1, s2);
                        sw(v1, a0, 0);
                        a0 = addiu(a0, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x00551f34
                charge(ctx, 10);
                sb(zero, s0, 5);
                a0 = s0;
                jal(ctx, 0x551F38u, gen::fn_sub_551DF8_00551df8);
                sw(zero, s0, 64);
                v0 = 1;
                sw(zero, s0, 68);
                sw(zero, s0, 72);
                sw(zero, s0, 76);
                sb(v0, s0, 4);
                v0 = s0;
            }
        }
    }
    // 0x00551f5c (the shared epilogue, written out on this path)
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

// 0x00551F80 sub_551F80 -- 120 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// AHX decoder destroy: closes the bit reader and MPEG decoder it holds, clears 80 bytes and its slot.
void sub_551F80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00551f80
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    if (s0 != 0) {
        // 0x00551f98
        charge(ctx, 4);
        lw(v0, s0, 12);
        lw(s1, s0, 60);
        a0 = v0;
        if (v0 != 0) {
            // 0x00551fa8
            charge(ctx, 2);
            link(ctx, 0x551FA8u);  // $ra first: the delay slot below depends on it
            sw(zero, s0, 12);
            call(ctx, gen::fn_sub_54D7E8_0054d7e8);
        }
        // 0x00551fb0
        charge(ctx, 3);
        lw(a0, s0, 0);
        if (a0 == 0) {
            a0 = s0;
        } else {
            // 0x00551fbc
            charge(ctx, 3);
            link(ctx, 0x551FBCu);  // $ra first: the delay slot below depends on it
            sw(zero, s0, 0);
            call(ctx, gen::fn_sub_54E260_0054e260);
            a0 = s0;
        }
        // 0x00551fc8
        charge(ctx, 7);
        a1 = 0;
        a2 = 80;
        jal(ctx, 0x551FCCu, gen::fn_memset_00521408);
        v1 = sll(s1, 2);
        at = 0x7A0000;
        at = addu(at, v1);
        sw(zero, at, -30992);
    }
    // 0x00551fe4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00551FF8 sub_551FF8 -- 8 bytes; leaf frame (no stack)
// Returns a decoder's state byte (+5).
void sub_551FF8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00551ff8
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, 5);
}

// 0x00552008 sub_552008 -- 8 bytes; leaf frame (no stack)
// Sets a decoder's input stream (+16).
void sub_552008(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00552008
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, 16);
}

// 0x00552028 sub_552028 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// AHX decoder start: resets the counters, reopens the bit reader on the input stream and binds it to the MPEG decoder
// (0x54E388); state 1 (header wait).
void sub_552028(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552028
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x552034u, gen::fn_sub_551DF8_00551df8);
    lw(v0, s0, 12);
    a0 = v0;
    if (v0 != 0) {
        // 0x00552048
        charge(ctx, 2);
        link(ctx, 0x552048u);  // $ra first: the delay slot below depends on it
        sw(zero, s0, 12);
        call(ctx, gen::fn_sub_54D7E8_0054d7e8);
    }
    // 0x00552050
    charge(ctx, 12);
    link(ctx, 0x552050u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 16);
    call(ctx, gen::fn_sub_54D6B8_0054d6b8);
    lw(a0, s0, 0);
    sw(v0, s0, 12);
    a1 = v0;
    jal(ctx, 0x552060u, gen::fn_sub_54E388_0054e388);
    v0 = 1;
    sb(v0, s0, 5);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00552080 sub_552080 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// AHX decoder stop: stops the MPEG decoder (0x54E2C0) and sets state 0.
void sub_552080(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552080
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    link(ctx, 0x552090u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 0);
    call(ctx, gen::fn_sub_54E2C0_0054e2c0);
    sb(zero, s0, 5);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005520B0 sub_5520B0 -- 96 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Header wait: once the input stream (vtable +36) holds 36 bytes, parses the header (0x54E3C0, 0x54E568), state 2
// (decoding).
void sub_5520B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005520b0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(a0, s0, 16);
    lw(v1, a0, 0);
    lw(v0, v1, 36);
    a1 = 1;
    jalr(ctx, 0x5520CCu, v0.u());
    v0 = slti(v0, 36);
    if (v0 != 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005520e0
        charge(ctx, 9);
        link(ctx, 0x5520E0u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_54E3C0_0054e3c0);
        link(ctx, 0x5520E8u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_54E568_0054e568);
        v1 = 1;
        v0 = 2;
        sb(v1, s0, 7);
        sb(v0, s0, 5);
        ld(s0, sp, 0x0);
    }
    // 0x00552104 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00552110 sub_552110 -- 676 bytes; frame 0x60: s1 sp+0x28, s6 sp+0x50, s0 sp+0x20, s2 sp+0x30, s3 sp+0x38, s4 sp+0x40, s5 sp+0x48, ra sp+0x58
// One AHX decode step: checks end of stream, sizes the frame against the output stream's room, decodes (0x54E658) into
// it, interleaves (0x563C28), calls the per-frame callback (+72) and the end-sample callback (+64); state 3 at the
// end.
void sub_552110(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00552110
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 1;
    sd(s1, sp, 0x28);
    s1 = a0;
    sd(s6, sp, 0x50);
    s6 = addiu(s1, 20);
    sd(s0, sp, 0x20);
    sd(s2, sp, 0x30);
    sd(s3, sp, 0x38);
    sd(s4, sp, 0x40);
    sd(s5, sp, 0x48);
    sd(ra, sp, 0x58);
    lb(s0, s1, 7);
    lw(s5, s1, 0);
    lw(a0, s1, 16);
    if (s0 == v0) {
        // 0x00552150
        charge(ctx, 6);
        lw(v1, a0, 0);
        lw(v0, v1, 36);
        a1 = 1;
        jalr(ctx, 0x552158u, v0.u());
        if (v0 != 0) {
            goto L_00552178;
        }
        // 0x00552168
        charge(ctx, 4);
        link(ctx, 0x552168u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 12);
        call(ctx, gen::fn_sub_54DBF0_0054dbf0);
        if (v0 != s0) {
            goto L_00552178;
        }
        lw(v1, s1, 44);
    L_0055220c:
        charge(ctx, 4);
        v0 = 3;
        sb(v0, s1, 5);
        sw(v1, s1, 32);
    L_0055238c:
        charge(ctx, 1);
        ld(s0, sp, 0x20);
    L_00552390:
        charge(ctx, 1);
        ld(s1, sp, 0x28);
        // 0x00552394 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(s2, sp, 0x30);
        ld(s3, sp, 0x38);
        ld(s4, sp, 0x40);
        ld(s5, sp, 0x48);
        ld(s6, sp, 0x50);
        ld(ra, sp, 0x58);
        sp = addiu(sp, 0x60);
        return;
    }
L_00552178:
    charge(ctx, 16);
    a0 = s1;
    jal(ctx, 0x552178u, gen::fn_sub_552520_00552520);
    a0 = s1;
    s4 = v0;
    jal(ctx, 0x552184u, gen::fn_sub_552508_00552508);
    lw(a0, s1, 20);
    a1 = addiu(v0, 7);
    v1 = slti(v0, 0);
    lw(a2, a0, 0);
    if (v1 != 0) v0 = a1;
    a1 = 0;
    lw(v1, a2, 36);
    s2 = sra(v0, 3);
    jalr(ctx, 0x5521A8u, v1.u());
    if (s2 == 0) {
        brk(ctx, 0x5521B4u, 0x7u);
    }
    // 0x005521b8
    charge(ctx, 5);
    div(v0, s2);
    mflo(v0);
    v0 = slt(v0, s4);
    ld(s0, sp, 0x20);
    if (v0 != 0) {
        goto L_00552390;
    }
    // 0x005521cc
    charge(ctx, 4);
    a0 = s5;
    jal(ctx, 0x5521CCu, gen::fn_sub_54E648_0054e648);
    if (v0 == 0) {
        lw(a0, s6, 0);
    } else {
        // 0x005521dc
        charge(ctx, 11);
        jal(ctx, 0x5521DCu, gen::fn_sub_551978_00551978);
        v1 = 0x7A0000;
        s0 = addiu(v1, -30928);  // &0x798730
        a0 = s5;
        link(ctx, 0x5521F0u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, 8);  // 0x798738
        call(ctx, gen::fn_sub_54E568_0054e568);
        v1 = v0;
        v0 = 1;
        cc = v1 != v0;  // the condition, before the delay slot changes it
        v0 = si(-1);
        if (!cc) {
            // 0x00552208
            charge(ctx, 1);
            lw(v1, s1, 44);
            goto L_0055220c;
        }
        // 0x00552220
        charge(ctx, 2);
        if (v1 == v0) {
            ld(s0, sp, 0x20);
            goto L_00552390;
        }
        // 0x00552228
        charge(ctx, 4);
        jal(ctx, 0x552228u, gen::fn_sub_551978_00551978);
        sw(v0, s0, 12);
        lw(a0, s6, 0);
        goto L_00552238;
    }
L_00552238:
    charge(ctx, 11);
    mult(zero, s4, s2);
    a1 = 0;
    lw(v0, a0, 0);
    lw(v1, v0, 24);
    mflo(a2);
    a3 = sp;
    jalr(ctx, 0x55224Cu, v1.u());
    lw(v0, sp, 0x4);
    v0 = srl(v0, 1);
    lw(s3, sp, 0x0);
    if (v0 != s4) {
        // 0x00552264
        charge(ctx, 8);
        lw(a0, s6, 0);
        a1 = 0;
        lw(v1, a0, 0);
        lw(v0, v1, 28);
        a2 = sp;
        jalr(ctx, 0x552274u, v0.u());
        ld(s0, sp, 0x20);
        goto L_00552390;
    }
    // 0x00552288
    charge(ctx, 22);
    s0 = 0x7A0000;
    jal(ctx, 0x552288u, gen::fn_sub_551978_00551978);
    s0 = addiu(s0, -30928);  // &0x798730
    a1 = s3;
    sw(v0, s0, 0);  // 0x798730
    a0 = s5;
    a3 = s4;
    a2 = 0;
    jal(ctx, 0x5522A4u, gen::fn_sub_54E658_0054e658);
    s3 = v0;
    jal(ctx, 0x5522ACu, gen::fn_sub_551978_00551978);
    mult(zero, s3, s2);
    s2 = addiu(sp, 0x10);
    sw(v0, s0, 4);  // 0x798734
    a0 = sp;
    a2 = sp;
    mflo(a1);
    a3 = s2;
    jal(ctx, 0x5522CCu, gen::fn_sub_563C28_00563c28);
    lw(v0, s1, 72);
    lw(a2, sp, 0x0);
    if (v0 != 0) {
        // 0x005522e0
        charge(ctx, 4);
        lw(a0, s1, 76);
        a1 = 0;
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x5522E8u);  // $ra = the return address
        lw(a3, sp, 0x4);
        call_ptr(ctx, jt);
    }
    // 0x005522f0
    charge(ctx, 31);
    lw(a0, s6, 0);
    a2 = sp;
    lw(v1, a0, 0);
    lw(v0, v1, 32);
    a1 = 1;
    jalr(ctx, 0x552300u, v0.u());
    lw(a0, s6, 0);
    a2 = s2;
    lw(v0, a0, 0);
    lw(v1, v0, 28);
    a1 = 0;
    jalr(ctx, 0x552318u, v1.u());
    lw(v0, s1, 32);
    lw(a0, s1, 12);
    v0 = addu(v0, s3);
    link(ctx, 0x55232Cu);  // $ra first: the delay slot below depends on it
    sw(v0, s1, 32);
    call(ctx, gen::fn_sub_54DBE8_0054dbe8);
    lw(a1, s1, 40);
    a0 = addiu(v0, 7);
    v0 = addiu(v0, 14);
    lw(a2, s1, 52);
    v1 = slti(a0, 0);
    if (v1 != 0) a0 = v0;
    lw(v1, s1, 48);
    v0 = addu(a2, s3);
    a0 = sra(a0, 3);
    a1 = addu(a1, s3);
    sw(a0, s1, 36);
    sw(a1, s1, 40);
    sw(v0, s1, 52);
    if (i64(v1) < 0) {
        goto L_0055238c;
    }
    // 0x0055236c
    charge(ctx, 3);
    v0 = slt(v0, v1);
    ld(s0, sp, 0x20);
    if (v0 != 0) {
        goto L_00552390;
    }
    // 0x00552378
    charge(ctx, 3);
    lw(v0, s1, 64);
    if (v0 != 0) {
        // 0x00552384
        charge(ctx, 2);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x552384u);  // $ra = the return address
        lw(a0, s1, 68);
        call_ptr(ctx, jt);
        goto L_0055238c;
    }
    ld(s1, sp, 0x28);
    // 0x00552394 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x005523B8 sub_5523B8 -- 64 bytes; frame 0x10: ra sp+0x0
// AHX decoder server for one decoder: state 1 header wait, state 2 decode step.
void sub_5523B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005523b8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 2;
    sd(ra, sp, 0x0);
    lb(v1, a0, 5);
    cc = v1 != v0;  // the condition, before the delay slot changes it
    v0 = 1;
    if (!cc) {
        // 0x005523d0
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_sub_552110_00552110(ctx);  // tail call
        return;
    }
    // 0x005523e0
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    if (v1 != v0) {
        // 0x005523f0
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005523e8
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5520B0_005520b0(ctx);  // tail call
}

// 0x00552460 sub_552460 -- 8 bytes; leaf frame (no stack)
// Returns a decoder's input bytes consumed (+36, the bit reader's position rounded up to bytes).
void sub_552460(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00552460
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 36);
}

// 0x00552468 sub_552468 -- 8 bytes; leaf frame (no stack)
// Returns a decoder's decoded-sample count (+32).
void sub_552468(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00552468
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 32);
}

// 0x00552480 sub_552480 -- 12 bytes; leaf frame (no stack)
// Sets a decoder's per-frame callback (+72) and its argument (+76).
void sub_552480(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00552480
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a2, a0, 76);
    sw(a1, a0, 72);
}

// 0x00552508 sub_552508 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Returns 16 (bits per output sample).
void sub_552508(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552508
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x0054e7d0
    charge(ctx, 2);
    v0 = 16;
}

// 0x00552520 sub_552520 -- 24 bytes; frame 0x10: ra sp+0x0
// Returns the MPEG decoder's output samples per frame (0x54E7D8 on +0).
void sub_552520(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552520
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_54E7D8_0054e7d8(ctx);  // tail call
}

// 0x00552600 sub_552600 -- 44 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Stores a 64-bit value ($a1 points at it) twice at the MPEG decoder's +2592.
void sub_552600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552600
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x0054e888
    charge(ctx, 5);
    ldl(v0, a1, 7);
    ldr(v0, a1, 0);
    sdl(v0, a0, 2599);
    sdr(v0, a0, 2592);
}

// 0x00552630 sub_552630 -- 20 bytes; frame 0x10: ra sp+0x0
// The AIX/ADXT error reporter: forwards the text to the ADX error callback (0x53AE08).
void sub_552630(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00552630
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
}

// 0x00552930 sub_552930 -- 672 bytes; frame 0x40: s3 sp+0x18, s2 sp+0x10, s5 sp+0x28, s0 sp+0x0, s1 sp+0x8, s4 sp+0x20, ra sp+0x30
// AIXP create (pool of 4 x 620 bytes at 0x799978): lays out the work ($a1, $a2 bytes, 64-aligned) for the demuxer, the
// per-track ADXT players, the SJ ring buffers; registers the demux callback 0x553920. [proposed: AIXP_Create]
void sub_552930(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552930
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a3 = si(-64);
    v1 = addiu(a1, 63);
    sd(s3, sp, 0x18);
    s3 = v1 & a3;
    sd(s2, sp, 0x10);
    v0 = subu(s3, a1);
    sd(s5, sp, 0x28);
    sd(s0, sp, 0x0);
    s2 = subu(a2, v0);
    sd(s1, sp, 0x8);
    s5 = a0;
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x30);
    if (a1 != 0) {
        // 0x00552980
        charge(ctx, 5);
        a0 = 0x7A0000;
        v1 = addiu(a0, -26248);  // &0x799978
        lb(v0, v1, 0);  // 0x799978
        a1 = 0;
        if (v0 != 0) {
            // 0x00552994
            charge(ctx, 1);
            a1 = addiu(a1, 1);
            for (;;) {
                // 0x00552998
                charge(ctx, 3);
                v0 = slti(a1, 4);
                v1 = addiu(v1, 620);
                if (v0 != 0) {
                    // 0x005529a4
                    charge(ctx, 6);
                    lb(v0, v1, 0);
                    if (v0 != 0) {
                        a1 = addiu(a1, 1);
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
        }
        // 0x005529bc
        charge(ctx, 3);
        v1 = 4;
        v0 = 0;
        if (a1 != v1) {
            // 0x005529c8
            charge(ctx, 25);
            v1 = sll(a1, 2);
            a0 = addiu(a0, -26248);
            v1 = addu(v1, a1);
            a1 = 0;
            v0 = sll(v1, 5);
            a2 = 620;
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            s0 = addu(v0, a0);
            a0 = s0;
            jal(ctx, 0x5529ECu, gen::fn_memset_00521408);
            lbu(v1, s5, 0);
            a0 = 1;
            sb(v1, s0, 3);
            lbu(v0, s5, 4);
            sb(v0, s0, 2);
            v0 = 8192;
            lw(v1, s5, 8);
            sw(v0, s0, 416);
            v0 = 64;
            sw(v1, s0, 616);
            sw(v0, s0, 420);
            lw(v1, s5, 8);
            if (v1 != a0) {
                lw(v1, s5, 4);
                // 0x00552a40
                charge(ctx, 8);
                lw(a0, s5, 0);
                v0 = sll(v1, 6);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                v0 = subu(v0, v1);
                v0 = sll(v0, 6);
                v0 = addiu(v0, 64);
                mult(s1, v0, a0);
            } else {
                // 0x00552a2c
                charge(ctx, 4);
                lw(v1, s5, 0);
                v0 = 0x85C0;
                mult(s1, v1, v0);
            }
            // 0x00552a60
            charge(ctx, 6);
            a0 = s0;
            a1 = s3;
            a2 = s1;
            jal(ctx, 0x552A68u, gen::fn_sub_5541D0_005541d0);
            s2 = subu(s2, s1);
            if (i64(v0) >= 0) {
                // 0x00552a78
                charge(ctx, 2);
                s3 = addu(s3, s1);
                if (i64(s2) < 0) {
                    goto L_00552ba0;
                }
                // 0x00552a80
                charge(ctx, 3);
                lb(v0, s0, 3);
                s4 = 0;
                if (i64(v0) > 0) {
                    // 0x00552a8c
                    charge(ctx, 3);
                    s1 = addiu(s0, 288);
                    lw(v0, s0, 416);
                    for (;;) {
                        // 0x00552a98
                        charge(ctx, 8);
                        lw(v1, s0, 420);
                        a1 = v0;
                        sw(s3, s1, 0);
                        v0 = addu(v0, v1);
                        a2 = v1;
                        s2 = subu(s2, v0);
                        s3 = addu(s3, v0);
                        if (i64(s2) < 0) {
                            goto L_00552ba0;
                        }
                        // 0x00552ab8
                        charge(ctx, 5);
                        link(ctx, 0x552AB8u);  // $ra first: the delay slot below depends on it
                        lw(a0, s1, 0);
                        call(ctx, gen::fn_sub_562388_00562388);
                        sw(v0, s1, -140);
                        s1 = addiu(s1, 4);
                        if (v0 == 0) {
                            goto L_00552ba0;
                        }
                        // 0x00552acc
                        charge(ctx, 5);
                        lb(v0, s0, 3);
                        s4 = addiu(s4, 1);
                        v0 = slt(s4, v0);
                        if (v0 == 0) {
                            break;
                        }
                        lw(v0, s0, 416);
                        backedge(ctx);
                    }
                }
                // 0x00552ae0
                charge(ctx, 17);
                v0 = addiu(s2, -8192);
                a1 = addiu(s2, -6145);
                v1 = slti(v0, 0);
                sw(s3, s0, 276);
                if (v1 != 0) v0 = a1;
                v1 = 8192;
                v0 = sra(v0, 11);
                sw(v1, s0, 284);
                v0 = sll(v0, 11);
                sw(zero, s0, 144);
                sw(v0, s0, 280);
                a0 = s3;
                a2 = 8192;
                a1 = v0;
                jal(ctx, 0x552B14u, gen::fn_sub_562388_00562388);
                sw(v0, s0, 140);
                if (v0 == 0) {
                    goto L_00552ba0;
                }
                // 0x00552b24
                charge(ctx, 6);
                lw(a0, s5, 0);
                a2 = addiu(s0, 148);
                link(ctx, 0x552B2Cu);  // $ra first: the delay slot below depends on it
                lw(a1, s0, 144);
                call(ctx, gen::fn_sub_5547C8_005547c8);
                sw(v0, s0, 4);
                if (v0 == 0) {
                    goto L_00552ba0;
                }
                // 0x00552b3c
                charge(ctx, 5);
                lw(a0, s0, 140);
                a1 = 0;
                jal(ctx, 0x552B40u, gen::fn_sub_545FC8_00545fc8);
                sw(v0, s0, 8);
                if (v0 == 0) {
                    goto L_00552ba0;
                }
                // 0x00552b50
                charge(ctx, 19);
                a1 = 0x550000;
                a0 = v0;
                a1 = addiu(a1, 14624);  // &sub_553920
                a2 = s0;
                jal(ctx, 0x552B5Cu, gen::fn_sub_5466B8_005466b8);
                sw(zero, s0, 424);
                v1 = 1;
                v0 = 1;
                sb(v0, s0, 433);
                v0 = s0;
                sb(v1, s0, 0);
                sb(zero, s0, 432);
                sw(zero, s0, 440);
                sw(zero, s0, 448);
                sw(zero, s0, 444);
                sw(zero, s0, 452);
                sw(v1, s0, 456);
                sw(zero, s0, 480);
                // 0x00552bac (the shared epilogue, written out on this path)
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
        L_00552ba0:
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x552BA0u, gen::fn_sub_552BD0_00552bd0);
            v0 = 0;
        }
    } else {
        // 0x0055296c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 12792);  // "E2003050201 : NULL pointer is specified."
        jal(ctx, 0x552970u, gen::fn_sub_552630_00552630);
        v0 = 0;
    }
    // 0x00552bac (the shared epilogue, written out on this path)
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

// 0x00552D68 sub_552D68 -- 316 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// AIXP start on a file area ($a0 player, $a1 / $a2 the source -> +460 / +464, $a3 ofst >= 0 -> +468, $t0 nsct > 0
// -> +472): checks the arguments (error texts), stops, binds the input SJ to the demuxer and arms the start.
void sub_552D68(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552d68
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x7C0000;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a3;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = t0;
    sd(s4, sp, 0x20);
    s4 = a2;
    sd(ra, sp, 0x28);
    v0 = addiu(v0, 8808);  // "\nADXT/PS2EE Ver.9.44 Build:Feb 28 2005 19:25:20\n"
    lw(v1, v0, 0);  // 0x7C2268
    if (s0 == 0) {
        a0 = 0x7C0000;
    } else {
        // 0x00552dac
        charge(ctx, 2);
        if (s2 == 0) {
            // 0x00552db4
            charge(ctx, 1);
            a0 = 0x7C0000;
            goto L_00552db8;
        }
        // 0x00552de0
        charge(ctx, 2);
        ld(ra, sp, 0x28);
        if (i64(s1) < 0) {
            // 0x00552de8
            charge(ctx, 9);
            a0 = 0x7C0000;
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            a0 = addiu(a0, 12936);  // "E2004111001 : Illigal parameter 'ofst<0'."
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(s4, sp, 0x20);
            sp = addiu(sp, 0x30);
            gen::fn_sub_552630_00552630(ctx);  // tail call
            return;
        }
        // 0x00552e10
        charge(ctx, 2);
        if (i64(s3) <= 0) {
            // 0x00552e18
            charge(ctx, 9);
            a0 = 0x7C0000;
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            a0 = addiu(a0, 12984);  // "E2004111002 : Illigal parameter 'nsct<=0'."
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(s4, sp, 0x20);
            sp = addiu(sp, 0x30);
            gen::fn_sub_552630_00552630(ctx);  // tail call
            return;
        }
        // 0x00552e40
        charge(ctx, 25);
        jal(ctx, 0x552E40u, gen::fn_sub_5530D0_005530d0);
        jal(ctx, 0x552E48u, gen::fn_sub_5546F0_005546f0);
        lw(v0, s0, 140);
        sw(s2, s0, 460);
        sw(s1, s0, 468);
        a1 = v0;
        sw(s4, s0, 464);
        sw(s3, s0, 472);
        sw(v0, s0, 144);
        link(ctx, 0x552E6Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 4);
        call(ctx, gen::fn_sub_554948_00554948);
        sw(zero, s0, 476);
        v0 = 1;
        ld(s1, sp, 0x8);
        sb(v0, s0, 1);
        sb(v0, s0, 434);
        ld(s2, sp, 0x10);
        ld(s0, sp, 0x0);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        gen::fn_sub_554708_00554708(ctx);  // tail call
        return;
    }
L_00552db8:
    charge(ctx, 9);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a0 = addiu(a0, 12888);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    gen::fn_sub_552630_00552630(ctx);  // tail call
}

// 0x00553288 sub_553288 -- 132 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Sets the AIX input SJ trigger: half the buffer, or the byte rate x the configured float (+480).
void sub_553288(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00553288
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    mtc1(zero, f1);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lwc1(f0, s0, 480);
    c_eq_s(f0, f1);
    if (cond(ctx)) {
        lw(a1, s0, 280);
        // 0x005532e8
        charge(ctx, 9);
        lw(a0, s0, 8);
        v0 = srl(a1, 31);
        a2 = a1;
        ld(s0, sp, 0x0);
        a1 = addu(a1, v0);
        ld(ra, sp, 0x8);
        a1 = sra(a1, 1);
        sp = addiu(sp, 0x10);
        gen::fn_sub_546FA0_00546fa0(ctx);  // tail call
        return;
    }
    // 0x005532ac
    charge(ctx, 14);
    jal(ctx, 0x5532ACu, gen::fn_sub_553838_00553838);
    lwc1(f1, s0, 480);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    lw(a2, s0, 280);
    lw(a0, s0, 8);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    mul_s(f0, f0, f1);
    cvt_w_s(f1, f0);
    mfc1(a1, f1);
    sp = addiu(sp, 0x10);
    gen::fn_sub_546FA0_00546fa0(ctx);  // tail call
}

// 0x005535D0 sub_5535D0 -- 132 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// AIXP pause on / off ($a1): records it (+424) and pauses each track's player unless stopped.
void sub_5535D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005535d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    if (s0 == 0) {
        // 0x005535ec
        charge(ctx, 7);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 13760);  // "E2003050222 : NULL pointer is specified."
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_552630_00552630(ctx);  // tail call
        return;
    }
    // 0x00553608
    charge(ctx, 8);
    jal(ctx, 0x553608u, gen::fn_sub_553188_00553188);
    v1 = 1;
    lb(v0, s0, 1);
    a0 = s0;
    a1 = s1;
    sw(s1, s0, 424);
    if (v0 == v1) {
        // 0x00553640
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00553628
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5543C8_005543c8(ctx);  // tail call
}

// 0x00553838 sub_553838 -- 228 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// AIXP_GetByteRate (by its error text): sums the tracks' rate x channels x 18 / 32; -1 on NULL.
void sub_553838(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553838
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    if (a0 != 0) {
        // 0x00553870
        charge(ctx, 5);
        lbu(v0, a0, 1);
        v0 = addiu(v0, -1);
        v0 = sltiu(v0, 3);
        if (v0 == 0) {
            v0 = 0;
        } else {
            // 0x00553884
            charge(ctx, 8);
            lw(s2, a0, 4);
            s1 = 0;
            s4 = 0;
            a0 = s2;
            jal(ctx, 0x553890u, gen::fn_sub_554968_00554968);
            s3 = v0;
            v0 = s4;
            if (i64(s3) > 0) {
                // 0x005538a4
                charge(ctx, 1);
                for (;;) {
                    // 0x005538a8
                    charge(ctx, 20);
                    a1 = s1;
                    a0 = s2;
                    jal(ctx, 0x5538ACu, gen::fn_sub_554970_00554970);
                    a0 = s2;
                    a1 = s1;
                    s1 = addiu(s1, 1);
                    s0 = v0;
                    jal(ctx, 0x5538C0u, gen::fn_sub_554980_00554980);
                    mult(s0, s0, v0);
                    a1 = slt(s1, s3);
                    v0 = sll(s0, 3);
                    v0 = addu(v0, s0);
                    v0 = sll(v0, 1);
                    v1 = v0;
                    a0 = addiu(v0, 31);
                    v0 = slti(v0, 0);
                    if (v0 != 0) v1 = a0;
                    v1 = sra(v1, 5);
                    s4 = addu(s4, v1);
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x005538f8
                charge(ctx, 1);
                v0 = s4;
            }
        }
    } else {
        // 0x00553858
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 14112);  // "E2004051901 AIXP_GetByteRate: NULL pointer is specified."
        jal(ctx, 0x55385Cu, gen::fn_sub_552630_00552630);
        v0 = si(-1);
    }
    // 0x005538fc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00553920 sub_553920 -- 340 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// The AIX demux callback: counts the played segments and loops back to the loop start when looping; reprograms the
// input range (0x5463A8 / 0x546718) for the next segment.
void sub_553920(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00553920
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a1 = 1;
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x28);
    lw(v0, s0, 428);
    cc = v0 == a1;  // the condition, before the delay slot changes it
    v0 = 2;
    if (!cc) {
        // 0x00553948
        charge(ctx, 3);
        lb(v1, s0, 1);
        if (v1 == v0) {
            goto L_00553954;
        }
        ld(s0, sp, 0x10);
        // 0x00553a60 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
L_00553954:
    charge(ctx, 5);
    lw(v0, s0, 444);
    lb(v1, s0, 432);
    a0 = addiu(v0, 1);
    sw(a0, s0, 444);
    if (v1 == a1) {
        // 0x00553968
        charge(ctx, 4);
        lw(v0, s0, 456);
        v0 = slt(a0, v0);
        if (v0 == 0) {
            // 0x00553978
            charge(ctx, 2);
            lw(v0, s0, 452);
            sw(v0, s0, 444);
            goto L_00553980;
        }
        lb(s2, s0, 433);
        goto L_00553984;
    }
L_00553980:
    charge(ctx, 1);
    lb(s2, s0, 433);
L_00553984:
    charge(ctx, 3);
    v0 = 1;
    if (s2 != v0) {
        ld(s0, sp, 0x10);
    } else {
        // 0x00553990
        charge(ctx, 6);
        link(ctx, 0x553990u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 4);
        call(ctx, gen::fn_sub_554990_00554990);
        lw(v1, s0, 444);
        v1 = slt(v1, v0);
        if (v1 == 0) {
            ld(s0, sp, 0x10);
        } else {
            // 0x005539a8
            charge(ctx, 7);
            jal(ctx, 0x5539A8u, gen::fn_sub_5546F0_005546f0);
            lw(s1, s0, 444);
            link(ctx, 0x5539B4u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 4);
            call(ctx, gen::fn_sub_554A98_00554a98);
            if (v0 == 0) {
                lw(a0, s0, 4);
                // 0x005539d8
                charge(ctx, 24);
                a2 = sp;
                a3 = addiu(sp, 0x4);
                a1 = s1;
                jal(ctx, 0x5539E0u, gen::fn_sub_5549C8_005549c8);
                lw(a0, s0, 8);
                lw(a1, sp, 0x0);
                v1 = addiu(a1, 2047);
                v0 = slti(a1, 0);
                if (v0 != 0) a1 = v1;
                a1 = sra(a1, 11);
                jal(ctx, 0x5539FCu, gen::fn_sub_5463A8_005463a8);
                lw(a0, s0, 8);
                lw(v0, sp, 0x4);
                lw(a1, sp, 0x0);
                a1 = addu(a1, v0);
                v1 = addiu(a1, 2047);
                v0 = slti(a1, 0);
                if (v0 != 0) a1 = v1;
                a1 = sra(a1, 11);
                jal(ctx, 0x553A20u, gen::fn_sub_546718_00546718);
                link(ctx, 0x553A28u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 8);
                call(ctx, gen::fn_sub_546498_00546498);
            } else {
                // 0x005539c4
                charge(ctx, 2);
                if (v0 == s2) {
                    lw(a0, s0, 8);
                    // 0x00553a38
                    charge(ctx, 7);
                    a1 = 0;
                    jal(ctx, 0x553A38u, gen::fn_sub_5463A8_005463a8);
                    lw(a0, s0, 8);
                    a1 = si(-1);
                    jal(ctx, 0x553A44u, gen::fn_sub_546718_00546718);
                    link(ctx, 0x553A4Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, s0, 8);
                    call(ctx, gen::fn_sub_546498_00546498);
                } else {
                    // 0x005539cc
                    charge(ctx, 2);
                }
            }
            // 0x00553a54
            charge(ctx, 3);
            jal(ctx, 0x553A54u, gen::fn_sub_554708_00554708);
            ld(s0, sp, 0x10);
        }
    }
    // 0x00553a60 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00553A78 sub_553A78 -- 244 bytes; frame 0x20: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, ra sp+0x18
// AIXP start of playback: resets the input, the tracks' SJ, sets the file range and trigger, starts the demuxer.
void sub_553A78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553a78
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = 0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    link(ctx, 0x553A94u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 8);
    call(ctx, gen::fn_sub_546270_00546270);
    lw(a0, s0, 144);
    lw(v1, a0, 0);
    lw(v0, v1, 20);
    jalr(ctx, 0x553AA8u, v0.u());
    lb(v1, s0, 3);
    if (i64(v1) <= 0) {
        lw(a3, s0, 468);
    } else {
        // 0x00553abc
        charge(ctx, 3);
        s1 = addiu(s0, 148);
        lw(a0, s1, 0);
        for (;;) {
            // 0x00553ac8
            charge(ctx, 9);
            s1 = addiu(s1, 4);
            lw(v0, a0, 0);
            lw(v1, v0, 20);
            s2 = addiu(s2, 1);
            jalr(ctx, 0x553AD4u, v1.u());
            lb(v0, s0, 3);
            v0 = slt(s2, v0);
            if (v0 == 0) {
                break;
            }
            lw(a0, s1, 0);
            backedge(ctx);
        }
        // 0x00553aec
        charge(ctx, 1);
        lw(a3, s0, 468);
    }
    // 0x00553af0
    charge(ctx, 31);
    lw(t0, s0, 472);
    lw(a0, s0, 8);
    lw(a1, s0, 460);
    link(ctx, 0x553AFCu);  // $ra first: the delay slot below depends on it
    lw(a2, s0, 464);
    call(ctx, gen::fn_sub_5460E0_005460e0);
    lw(a1, s0, 280);
    lw(a0, s0, 8);
    a2 = 0x7FFF0000;
    v0 = srl(a1, 31);
    a2 = a2 | 0xFFFF;
    a1 = addu(a1, v0);
    a1 = sra(a1, 1);
    jal(ctx, 0x553B1Cu, gen::fn_sub_546FA0_00546fa0);
    lw(a0, s0, 8);
    a1 = 0;
    jal(ctx, 0x553B28u, gen::fn_sub_5463A8_005463a8);
    lw(a0, s0, 8);
    a1 = 3;
    jal(ctx, 0x553B34u, gen::fn_sub_546718_00546718);
    link(ctx, 0x553B3Cu);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 8);
    call(ctx, gen::fn_sub_546498_00546498);
    lw(a0, s0, 4);
    a1 = 1;
    jal(ctx, 0x553B48u, gen::fn_sub_554958_00554958);
    lw(a0, s0, 4);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_554908_00554908(ctx);  // tail call
}

// 0x00553B70 sub_553B70 -- 76 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// One AIXP server step under the 0x79996C busy flag (0x5655E8 test-and-set).
void sub_553B70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553b70
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7A0000;
    sd(s1, sp, 0x8);
    s1 = addiu(v0, -26260);  // &0x79996C
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x10);
    a0 = s1;
    jal(ctx, 0x553B8Cu, gen::fn_sub_5655E8_005655e8);
    a0 = s0;
    if (v0 != 0) {
        // 0x00553b9c
        charge(ctx, 3);
        jal(ctx, 0x553B9Cu, gen::fn_sub_553BC0_00553bc0);
        sw(zero, s1, 0);
    }
    // 0x00553ba8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00553BC0 sub_553BC0 -- 1000 bytes; frame 0x40: s0 sp+0x10, s4 sp+0x30, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, ra sp+0x38
// The AIXP state machine for one player: prepare, start the tracks, loop handling, the end and error states.
void sub_553BC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00553bc0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s4, sp, 0x30);
    s4 = addiu(s0, 12);
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    sd(s3, sp, 0x28);
    sd(ra, sp, 0x38);
    lw(s3, s0, 4);
    if (s0 != 0) {
        // 0x00553c00
        charge(ctx, 4);
        lb(s1, s0, 1);
        v0 = 1;
        lbu(v1, s0, 1);
        if (s1 == v0) {
            // 0x00553c10
            charge(ctx, 5);
            a1 = 1;
            jal(ctx, 0x553C10u, gen::fn_sub_5543C8_005543c8);
            lw(v0, s0, 428);
            if (v0 != 0) {
                // 0x00553e68
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x553E68u, gen::fn_sub_554530_00554530);
                if (v0 != s1) {
                    lbu(v1, s0, 1);
                } else {
                    // 0x00553e78
                    charge(ctx, 5);
                    jal(ctx, 0x553E78u, gen::fn_sub_5546F0_005546f0);
                    lw(v0, s0, 424);
                    a0 = s0;
                    if (v0 == 0) {
                        // 0x00553e8c
                        charge(ctx, 2);
                        a1 = 0;
                        jal(ctx, 0x553E8Cu, gen::fn_sub_5543C8_005543c8);
                    }
                    // 0x00553e94
                    charge(ctx, 6);
                    a0 = s0;
                    jal(ctx, 0x553E94u, gen::fn_sub_553288_00553288);
                    v0 = 2;
                    sb(v0, s0, 1);
                    link(ctx, 0x553EA4u);  // $ra first: the delay slot below depends on it
                    sw(zero, s0, 428);
                    call(ctx, gen::fn_sub_554708_00554708);
                L_00553eac:
                    charge(ctx, 1);
                    lbu(v1, s0, 1);
                }
                goto L_00553eb0;
            }
            // 0x00553c24
            charge(ctx, 4);
            lw(v0, s0, 476);
            v0 = sltiu(v0, 2);
            if (v0 == 0) {
                // 0x00553de8
                charge(ctx, 5);
                a0 = s3;
                jal(ctx, 0x553DE8u, gen::fn_sub_554900_00554900);
                v1 = v0;
                v0 = 2;
                if (v1 != 0) {
                    // 0x00553e50
                    charge(ctx, 2);
                    if (v1 == v0) {
                        // 0x00553e58
                        charge(ctx, 4);
                        a0 = s0;
                        jal(ctx, 0x553E58u, gen::fn_sub_554448_00554448);
                        sw(s1, s0, 428);
                        goto L_00553eac;
                    }
                    lbu(v1, s0, 1);
                } else {
                    // 0x00553dfc
                    charge(ctx, 4);
                    lb(v0, s0, 3);
                    v0 = slt(v1, v0);
                    s2 = 0;
                    if (v0 != 0) {
                        // 0x00553e0c
                        charge(ctx, 3);
                        s1 = addiu(s0, 148);
                        lw(a0, s1, 0);
                        for (;;) {
                            // 0x00553e18
                            charge(ctx, 9);
                            s1 = addiu(s1, 4);
                            lw(v0, a0, 0);
                            lw(v1, v0, 20);
                            s2 = addiu(s2, 1);
                            jalr(ctx, 0x553E24u, v1.u());
                            lb(v0, s0, 3);
                            v0 = slt(s2, v0);
                            if (v0 == 0) {
                                break;
                            }
                            lw(a0, s1, 0);
                            backedge(ctx);
                        }
                    }
                    // 0x00553e3c
                    charge(ctx, 4);
                    a0 = s3;
                    jal(ctx, 0x553E3Cu, gen::fn_sub_554908_00554908);
                    lbu(v1, s0, 1);
                }
                goto L_00553eb0;
            }
            // 0x00553c34
            charge(ctx, 7);
            link(ctx, 0x553C34u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 8);
            call(ctx, gen::fn_sub_546368_00546368);
            s2 = v0;
            jal(ctx, 0x553C3Cu, gen::fn_sub_5546F0_005546f0);
            lb(v0, s0, 434);
            cc = v0 != s1;  // the condition, before the delay slot changes it
            v0 = 2;
            if (!cc) {
                // 0x00553c50
                charge(ctx, 2);
                if (s2 == v0) {
                    goto L_00553c70;
                }
                // 0x00553c58
                charge(ctx, 6);
                link(ctx, 0x553C58u);  // $ra first: the delay slot below depends on it
                sb(zero, s0, 434);
                call(ctx, gen::fn_sub_554708_00554708);
                a0 = s0;
                jal(ctx, 0x553C60u, gen::fn_sub_553A78_00553a78);
                goto L_00553c78;
            }
        L_00553c70:
            charge(ctx, 2);
            jal(ctx, 0x553C70u, gen::fn_sub_554708_00554708);
        L_00553c78:
            charge(ctx, 5);
            a0 = s3;
            jal(ctx, 0x553C78u, gen::fn_sub_554900_00554900);
            v1 = 2;
            if (v0 != v1) {
                lbu(v1, s0, 1);
                goto L_00553eb0;
            }
            // 0x00553c8c
            charge(ctx, 7);
            a0 = s3;
            jal(ctx, 0x553C8Cu, gen::fn_sub_554968_00554968);
            a0 = s3;
            jal(ctx, 0x553C94u, gen::fn_sub_554A98_00554a98);
            s1 = v0;
            v0 = 1;
            if (s1 != 0) {
                // 0x00553ca8
                charge(ctx, 2);
                if (s1 == v0) {
                    lw(a0, s0, 8);
                    // 0x00553d88
                    charge(ctx, 8);
                    a1 = si(-1);
                    jal(ctx, 0x553D88u, gen::fn_sub_546718_00546718);
                    a0 = s3;
                    a1 = 0;
                    jal(ctx, 0x553D94u, gen::fn_sub_554958_00554958);
                    lb(v0, s0, 432);
                    a0 = s3;
                    if (v0 != s1) {
                        // 0x00553da8
                        charge(ctx, 3);
                        lb(v0, s0, 433);
                        if (v0 == s1) {
                            // 0x00553db4
                            charge(ctx, 1);
                            a0 = s3;
                            goto L_00553db8;
                        }
                        lw(a0, s0, 12);
                        goto L_00553dc4;
                    }
                L_00553db8:
                    charge(ctx, 3);
                    a1 = 1;
                    jal(ctx, 0x553DB8u, gen::fn_sub_554960_00554960);
                    lw(a0, s0, 12);
                L_00553dc4:
                    charge(ctx, 6);
                    a1 = 1;
                    jal(ctx, 0x553DC4u, gen::fn_sceInsockSetsockopt_2_0054a928);
                    lw(a0, s4, 0);
                    link(ctx, 0x553DD0u);  // $ra first: the delay slot below depends on it
                    lw(a1, s0, 148);
                    call(ctx, gen::fn_sub_5484E0_005484e0);
                    v0 = 1;
                    goto L_00553ddc;
                }
                // 0x00553cb0
                charge(ctx, 2);
                lbu(v1, s0, 1);
                goto L_00553de0;
            }
            // 0x00553cb8
            charge(ctx, 3);
            lw(s1, s0, 448);
            sw(s1, s0, 444);
            if (i64(s1) >= 0) {
                // 0x00553cc4
                charge(ctx, 5);
                link(ctx, 0x553CC4u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 4);
                call(ctx, gen::fn_sub_554990_00554990);
                v0 = slt(s1, v0);
                a2 = sp;
                if (v0 == 0) {
                    goto L_00553cd8;
                }
                // 0x00553ce8
                charge(ctx, 27);
                a3 = addiu(sp, 0x4);
                a1 = s1;
                a0 = s3;
                jal(ctx, 0x553CF0u, gen::fn_sub_5549C8_005549c8);
                lw(a0, s0, 8);
                lw(a1, sp, 0x0);
                v1 = addiu(a1, 2047);
                v0 = slti(a1, 0);
                if (v0 != 0) a1 = v1;
                a1 = sra(a1, 11);
                jal(ctx, 0x553D0Cu, gen::fn_sub_5463A8_005463a8);
                lw(a0, s0, 8);
                lw(v0, sp, 0x4);
                lw(a1, sp, 0x0);
                a1 = addu(a1, v0);
                v1 = addiu(a1, 2047);
                v0 = slti(a1, 0);
                if (v0 != 0) a1 = v1;
                a1 = sra(a1, 11);
                jal(ctx, 0x553D30u, gen::fn_sub_546718_00546718);
                a0 = s3;
                a1 = 0;
                jal(ctx, 0x553D3Cu, gen::fn_sub_554958_00554958);
                lb(v0, s0, 432);
                v1 = 1;
                a0 = s3;
                if (v0 != v1) {
                    // 0x00553d54
                    charge(ctx, 3);
                    lb(v0, s0, 433);
                    a0 = s0;
                    if (v0 == v1) {
                        // 0x00553d60
                        charge(ctx, 1);
                        a0 = s3;
                        goto L_00553d64;
                    }
                    goto L_00553d70;
                }
            L_00553d64:
                charge(ctx, 3);
                a1 = 1;
                jal(ctx, 0x553D64u, gen::fn_sub_554960_00554960);
                a0 = s0;
            L_00553d70:
                charge(ctx, 6);
                a1 = 1;
                jal(ctx, 0x553D70u, gen::fn_sub_5544C8_005544c8);
                a0 = s0;
                jal(ctx, 0x553D78u, gen::fn_sub_554448_00554448);
                v0 = 1;
            L_00553ddc:
                charge(ctx, 1);
                lbu(v1, s0, 1);
            L_00553de0:
                charge(ctx, 2);
                sw(v0, s0, 428);
                goto L_00553eb0;
            }
        L_00553cd8:
            charge(ctx, 3);
            v0 = 3;
            sb(v0, s0, 1);
            goto L_00553f88;
        }
    L_00553eb0:
        charge(ctx, 5);
        v0 = sll(v1, 24);
        v1 = 2;
        s1 = sra(v0, 24);
        if (s1 == v1) {
            // 0x00553ec4
            charge(ctx, 5);
            a0 = s3;
            jal(ctx, 0x553EC4u, gen::fn_sub_554A98_00554a98);
            v1 = v0;
            v0 = 1;
            if (v1 == 0) {
                // 0x00553ee8
                charge(ctx, 6);
                a0 = s3;
                jal(ctx, 0x553EE8u, gen::fn_sub_554900_00554900);
                s1 = v0;
                v0 = 3;
                if (s1 == v0) {
                    // 0x00553f00
                    charge(ctx, 5);
                    a0 = s0;
                    jal(ctx, 0x553F00u, gen::fn_sub_5545D8_005545d8);
                    v1 = 1;
                    if (v0 == v1) {
                        sb(s1, s0, 1);
                    } else {
                        // 0x00553f14
                        charge(ctx, 2);
                    }
                }
            } else {
                // 0x00553ed8
                charge(ctx, 2);
                if (v1 == v0) {
                    // 0x00553f20
                    charge(ctx, 4);
                    link(ctx, 0x553F20u);  // $ra first: the delay slot below depends on it
                    lw(a0, s0, 8);
                    call(ctx, gen::fn_sub_546368_00546368);
                    if (v0 != s1) {
                        // 0x00553f30
                        charge(ctx, 6);
                        link(ctx, 0x553F30u);  // $ra first: the delay slot below depends on it
                        lw(a0, s0, 12);
                        call(ctx, gen::fn_sub_548768_00548768);
                        v1 = v0;
                        v0 = 5;
                        cc = v1 == v0;  // the condition, before the delay slot changes it
                        v0 = 3;
                        if (!cc) {
                            // 0x00553f48
                            charge(ctx, 2);
                            if (v1 == 0) {
                                goto L_00553f50;
                            }
                            goto L_00553f54;
                        }
                    L_00553f50:
                        charge(ctx, 1);
                        sb(v0, s0, 1);
                    }
                } else {
                    // 0x00553ee0
                    charge(ctx, 2);
                }
            }
        }
    L_00553f54:
        charge(ctx, 5);
        jal(ctx, 0x553F54u, gen::fn_sub_5546F0_005546f0);
        lw(a0, s0, 8);
        if (a0 != 0) {
            // 0x00553f68
            charge(ctx, 6);
            jal(ctx, 0x553F68u, gen::fn_sub_546368_00546368);
            v1 = v0;
            v0 = 4;
            if (v1 == v0) {
                sb(v1, s0, 1);
            }
        }
        // 0x00553f80
        charge(ctx, 2);
        jal(ctx, 0x553F80u, gen::fn_sub_554708_00554708);
    L_00553f88:
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    } else {
        // 0x00553bec
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 14176);  // "E2003050223 : NULL pointer is specified."
        jal(ctx, 0x553BF0u, gen::fn_sub_552630_00552630);
        ld(s0, sp, 0x10);
    }
    // 0x00553f8c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x00553FA8 sub_553FA8 -- 96 bytes; frame 0x20: ra sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// AIXP server: runs the step of each of the 4 live players. [proposed: AIXP_ExecServer]
void sub_553FA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553fa8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7A0000;
    sd(ra, sp, 0x18);
    sd(s0, sp, 0x0);
    s0 = addiu(v0, -26248);  // &0x799978
    sd(s1, sp, 0x8);
    s1 = 3;
    sd(s2, sp, 0x10);
    s2 = 1;
    for (;;) {
        // 0x00553fd0
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x00553fdc
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x553FDCu, gen::fn_sub_553B70_00553b70);
            s1 = addiu(s1, -1);
        }
        // 0x00553fe8
        charge(ctx, 2);
        s0 = addiu(s0, 620);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00553ff0
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00554048 sub_554048 -- 156 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Sets the AIX output volume (+484) and applies it with each track's offset.
void sub_554048(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00554048
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    if (s0 == 0) {
        // 0x00554064
        charge(ctx, 8);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 14224);  // "E2003102010 : NULL pointer is specified."
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_552630_00552630(ctx);  // tail call
        return;
    }
    // 0x00554088
    charge(ctx, 4);
    lb(v0, s0, 3);
    s2 = 0;
    sw(a1, s0, 484);
    if (i64(v0) > 0) {
        // 0x00554098
        charge(ctx, 2);
        s1 = addiu(s0, 488);
        lw(v0, s1, 0);
        for (;;) {
            // 0x005540a0
            charge(ctx, 11);
            s1 = addiu(s1, 4);
            lw(a2, s0, 484);
            a1 = s2;
            a0 = s0;
            s2 = addiu(s2, 1);
            a2 = addu(a2, v0);
            link(ctx, 0x5540B4u);
            gen::fn_sub_554138_00554138_at_005541a8(ctx);
            lb(v0, s0, 3);
            v0 = slt(s2, v0);
            if (v0 == 0) {
                break;
            }
            lw(v0, s1, 0);
            backedge(ctx);
        }
    }
    // 0x005540cc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005541D0 sub_5541D0 -- 280 bytes; frame 0x40: s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, s0 sp+0x0, s2 sp+0x10, s5 sp+0x28, s6 sp+0x30, ra sp+0x38
// Creates the per-track ADXT players inside the work area (AHX or ADX per +616).
void sub_5541D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005541d0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = addiu(a1, 63);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    a0 = si(-64);
    sd(s4, sp, 0x20);
    s4 = v0 & a0;
    sd(s0, sp, 0x0);
    a1 = subu(s4, a1);
    sd(s2, sp, 0x10);
    v0 = 1;
    sd(s5, sp, 0x28);
    sd(s6, sp, 0x30);
    sd(ra, sp, 0x38);
    lw(v1, s1, 616);
    s3 = subu(a2, a1);
    if (v1 != v0) {
        // 0x00554220
        charge(ctx, 8);
        lb(v1, s1, 2);
        v0 = sll(v1, 6);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = subu(v0, v1);
        v0 = sll(v0, 6);
        v0 = addiu(v0, 127);
        s2 = v0 & a0;
    } else {
        // 0x00554218
        charge(ctx, 2);
        s2 = 0x85C0;
    }
    // 0x00554240
    charge(ctx, 3);
    lb(v0, s1, 3);
    s5 = 0;
    if (i64(v0) > 0) {
        // 0x0055424c
        charge(ctx, 3);
        s6 = 1;
        s0 = addiu(s1, 12);
        for (;;) {
            // 0x00554258
            charge(ctx, 7);
            v0 = s4;
            s3 = subu(s3, s2);
            a0 = v0;
            a1 = v0;
            s4 = addu(v0, s2);
            v0 = si(-1);
            if (i64(s3) < 0) {
                break;
            }
            // 0x00554274
            charge(ctx, 3);
            lw(v0, s1, 616);
            if (v0 == s6) {
                // 0x00554280
                charge(ctx, 4);
                a1 = s2;
                jal(ctx, 0x554280u, gen::fn_sub_547F30_00547f30);
                sw(v0, s0, 0);
                if (v0 != 0) {
                    goto L_005542a8;
                }
                goto L_00554290;
            }
            lb(a0, s1, 2);
            // 0x00554298
            charge(ctx, 4);
            a2 = s2;
            jal(ctx, 0x554298u, gen::fn_sub_547BC0_00547bc0);
            sw(v0, s0, 0);
            if (v0 == 0) {
                backedge(ctx);
                goto L_00554290;
            }
        L_005542a8:
            charge(ctx, 5);
            lb(v0, s1, 3);
            s5 = addiu(s5, 1);
            v0 = slt(s5, v0);
            s0 = addiu(s0, 4);
            if (v0 == 0) {
                goto L_005542bc;
            }
            backedge(ctx);
        }
        // 0x005542c0 (the shared epilogue, written out on this path)
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
    }
L_005542bc:
    charge(ctx, 1);
    v0 = 0;
    // 0x005542c0 (the shared epilogue, written out on this path)
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
L_00554290:
    charge(ctx, 2);
    v0 = si(-1);
    // 0x005542c0 (the shared epilogue, written out on this path)
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
}

// 0x005542E8 sub_5542E8 -- 120 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// Destroys each track's ADXT player.
void sub_5542E8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005542e8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    lb(v0, s1, 3);
    lbu(v1, s1, 3);
    if (i64(v0) > 0) {
        // 0x00554310
        charge(ctx, 2);
        s0 = addiu(s1, 12);
        for (;;) {
            // 0x00554318
            charge(ctx, 3);
            lw(v0, s0, 0);
            a0 = v0;
            if (v0 != 0) {
                // 0x00554324
                charge(ctx, 3);
                link(ctx, 0x554324u);  // $ra first: the delay slot below depends on it
                sw(zero, s0, 0);
                call(ctx, gen::fn_sub_548048_00548048);
                lbu(v1, s1, 3);
            }
            // 0x00554330
            charge(ctx, 6);
            v0 = sll(v1, 24);
            s2 = addiu(s2, 1);
            v0 = sra(v0, 24);
            v0 = slt(s2, v0);
            s0 = addiu(s0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00554348 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00554360 sub_554360 -- 100 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// Stops each track's ADXT player.
void sub_554360(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00554360
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    lb(v0, s1, 3);
    s2 = 0;
    if (i64(v0) > 0) {
        // 0x00554384
        charge(ctx, 3);
        s0 = addiu(s1, 12);
        lw(a0, s0, 0);
        for (;;) {
            // 0x00554390
            charge(ctx, 7);
            s0 = addiu(s0, 4);
            s2 = addiu(s2, 1);
            jal(ctx, 0x554394u, gen::fn_sub_548678_00548678);
            lb(v0, s1, 3);
            v0 = slt(s2, v0);
            if (v0 == 0) {
                break;
            }
            lw(a0, s0, 0);
            backedge(ctx);
        }
    }
    // 0x005543ac (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005543C8 sub_5543C8 -- 128 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// Pauses / resumes ($a1) each track's ADXT player.
void sub_5543C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005543c8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 0;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    lb(v0, s1, 3);
    lbu(v1, s1, 3);
    if (i64(v0) > 0) {
        // 0x005543f8
        charge(ctx, 2);
        s0 = addiu(s1, 12);
        lw(a0, s0, 0);
        for (;;) {
            // 0x00554400
            charge(ctx, 2);
            s0 = addiu(s0, 4);
            if (a0 != 0) {
                // 0x00554408
                charge(ctx, 3);
                a1 = s3;
                jal(ctx, 0x554408u, gen::fn_sub_54A3C0_0054a3c0);
                lbu(v1, s1, 3);
            }
            // 0x00554414
            charge(ctx, 6);
            v0 = sll(v1, 24);
            s2 = addiu(s2, 1);
            v0 = sra(v0, 24);
            v0 = slt(s2, v0);
            if (v0 == 0) {
                break;
            }
            lw(a0, s0, 0);
            backedge(ctx);
        }
    }
    // 0x0055442c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00554448 sub_554448 -- 124 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s1 sp+0x8, ra sp+0x20
// Starts each track's player on its SJ (0x5484E0).
void sub_554448(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00554448
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    s3 = 0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x20);
    link(ctx, 0x554468u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 4);
    call(ctx, gen::fn_sub_554968_00554968);
    s2 = v0;
    if (i64(s2) <= 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0055447c
        charge(ctx, 3);
        s1 = addiu(s0, 12);
        s0 = addiu(s0, 148);
        lw(a0, s1, 0);
        for (;;) {
            // 0x00554488
            charge(ctx, 8);
            s1 = addiu(s1, 4);
            lw(a1, s0, 0);
            s0 = addiu(s0, 4);
            s3 = addiu(s3, 1);
            jal(ctx, 0x554494u, gen::fn_sub_5484E0_005484e0);
            v0 = slt(s3, s2);
            if (v0 == 0) {
                break;
            }
            lw(a0, s1, 0);
            backedge(ctx);
        }
        // 0x005544a8
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x005544ac (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005544C8 sub_5544C8 -- 104 bytes; frame 0x20: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, ra sp+0x18
// Sets each track player's flag ($a1) through 0x54A928.
void sub_5544C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005544c8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    link(ctx, 0x5544E4u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 4);
    call(ctx, gen::fn_sub_554968_00554968);
    if (i64(v0) <= 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005544f4
        charge(ctx, 3);
        s1 = addiu(s0, 12);
        s0 = v0;
        lw(a0, s1, 0);
        for (;;) {
            // 0x00554500
            charge(ctx, 6);
            s1 = addiu(s1, 4);
            s0 = addiu(s0, -1);
            a1 = s2;
            jal(ctx, 0x554508u, gen::fn_sceInsockSetsockopt_2_0054a928);
            if (s0 == 0) {
                break;
            }
            lw(a0, s1, 0);
            backedge(ctx);
        }
        // 0x00554518
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x0055451c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00554530 sub_554530 -- 168 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, ra sp+0x38
// True when every track player is in state 3 (playing); a state 6 track sets the AIXP error state.
void sub_554530(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00554530
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = 0;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    s3 = a0;
    sd(s4, sp, 0x20);
    s4 = 3;
    sd(s5, sp, 0x28);
    s5 = 4;
    sd(s6, sp, 0x30);
    s6 = 6;
    sd(ra, sp, 0x38);
    s0 = addiu(s3, 12);
    link(ctx, 0x55456Cu);  // $ra first: the delay slot below depends on it
    lw(a0, s3, 4);
    call(ctx, gen::fn_sub_554968_00554968);
    s2 = v0;
    for (;;) {
        // 0x00554584
        charge(ctx, 3);
        v0 = slt(s1, s2);
        if (v0 == 0) {
            v0 = s1 ^ s2;
        } else {
            // 0x00554590
            charge(ctx, 5);
            lw(a0, s0, 0);
            s0 = addiu(s0, 4);
            jal(ctx, 0x554594u, gen::fn_sub_548768_00548768);
            if (v0 == s6) {
                sb(s5, s3, 1);
            }
            // 0x005545a4
            charge(ctx, 2);
            cc = v0 == s4;  // the condition, before the delay slot changes it
            v0 = s1 ^ s2;
            if (cc) {
                backedge(ctx);
                // 0x00554580
                charge(ctx, 1);
                s1 = addiu(s1, 1);
                continue;
            }
        }
        break;
    }
    // 0x005545ac (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    v0 = sltiu(v0, 1);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x005546F0 sub_5546F0 -- 20 bytes; frame 0x10: ra sp+0x0
// Enter the CRI critical section (0x564978).
void sub_5546F0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005546f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564978_00564978(ctx);  // tail call
}

// 0x00554708 sub_554708 -- 20 bytes; frame 0x10: ra sp+0x0
// Leave the CRI critical section (0x564990).
void sub_554708(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00554708
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564990_00564990(ctx);  // tail call
}

// 0x00554720 sub_554720 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// AIX demuxer init (reference counted, 0x79A328): first call clears the pool (4 x 6492 bytes at 0x79A330).
void sub_554720(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00554720
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    jal(ctx, 0x55472Cu, gen::fn_sub_5546F0_005546f0);
    v0 = 0x7A0000;
    a0 = 0x7A0000;
    s0 = addiu(v0, -23768);  // &0x79A328
    a0 = addiu(a0, -23760);  // &0x79A330
    lw(v0, s0, 0);  // 0x79A328
    a1 = 0;
    a2 = 25968;
    if (v0 == 0) {
        // 0x00554754
        charge(ctx, 3);
        jal(ctx, 0x554754u, gen::fn_memset_00521408);
        lw(v0, s0, 0);
    }
    // 0x00554760
    charge(ctx, 6);
    v0 = addiu(v0, 1);
    ld(ra, sp, 0x8);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_554708_00554708(ctx);  // tail call
}

// 0x00554900 sub_554900 -- 8 bytes; leaf frame (no stack)
// Returns the demuxer's state byte (+1).
void sub_554900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00554900
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, 1);
}

// 0x00554908 sub_554908 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Demuxer stop: state 1, counters cleared (in the critical section).
void sub_554908(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00554908
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x554914u, gen::fn_sub_5546F0_005546f0);
    v0 = 1;
    ld(ra, sp, 0x8);
    sw(zero, s0, 16);
    sb(v0, s0, 1);
    sw(zero, s0, 8);
    sw(zero, s0, 12);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_554708_00554708(ctx);  // tail call
}

// 0x00554948 sub_554948 -- 8 bytes; leaf frame (no stack)
// Sets the demuxer's input SJ (+28).
void sub_554948(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00554948
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, 28);
}

// 0x00554958 sub_554958 -- 8 bytes; leaf frame (no stack)
// Sets the demuxer's pause byte (+3).
void sub_554958(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00554958
    enter(ctx, 2);  // entry check point + this block's cycles
    sb(a1, a0, 3);
}

// 0x00554968 sub_554968 -- 8 bytes; leaf frame (no stack)
// Returns the demuxer's track count (+172).
void sub_554968(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00554968
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, 172);
}

// 0x00554990 sub_554990 -- 8 bytes; leaf frame (no stack)
// Returns the demuxer's segment count (+688).
void sub_554990(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00554990
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 688);
}

// 0x005549C8 sub_5549C8 -- 48 bytes; leaf frame (no stack)
// Reads segment $a1's offset / size (16-byte entries from +692) into $a2 / $a3 when non-NULL.
void sub_5549C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x005549c8
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = sll(a1, 4);
    v1 = addu(v0, a0);
    a1 = v1;
    if (a2 != 0) {
        // 0x005549d8
        charge(ctx, 2);
        lw(v0, a1, 692);
        sw(v0, a2, 0);
    }
    // 0x005549e0
    charge(ctx, 2);
    if (a3 != 0) {
        // 0x005549e8
        charge(ctx, 2);
        lw(v0, v1, 696);
        sw(v0, a3, 0);
    }
    // 0x005549f0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00554A98 sub_554A98 -- 8 bytes; leaf frame (no stack)
// Returns the demuxer's stream-type word (+6488).
void sub_554A98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00554a98
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 6488);
}

// 0x00554AE8 sub_554AE8 -- 948 bytes; frame 0x30: s4 sp+0x20, s0 sp+0x0, s3 sp+0x18, s1 sp+0x8, s2 sp+0x10, ra sp+0x28
// Parses the AIX header ("AIXF", checked by the "(c)CRI" tail): rate, tracks, the segment table, the layer table;
// returns the data offset, 0 when not AIXF, -1 when short.
void sub_554AE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00554ae8
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x7C0000;
    sd(s4, sp, 0x20);
    s4 = addiu(v0, 14376);  // "(c)CRI"
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s3, sp, 0x18);
    s3 = a0;
    a0 = s4;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x28);
    s2 = a2;
    jal(ctx, 0x554B18u, gen::fn_strlen_00524388);
    s0 = slti(s0, 6144);
    t0 = v0;
    s1 = s3;
    v0 = si(-1);
    if (s0 == 0) {
        // 0x00554b34
        charge(ctx, 14);
        lbu(v0, s1, 0);
        a1 = 0x41490000;
        lbu(v1, s1, 2);
        a1 = a1 | 0x5846;
        lbu(a0, s1, 1);
        v0 = sll(v0, 24);
        lbu(a2, s1, 3);
        v1 = sll(v1, 8);
        a0 = sll(a0, 16);
        v0 = v0 | a2;
        v1 = v1 | a0;
        v0 = v0 | v1;
        if (v0 == a1) {
            s1 = addiu(s1, 4);
            // 0x00554b80
            charge(ctx, 19);
            a1 = s4;
            lbu(a0, s1, 0);
            a2 = t0;
            lbu(v0, s1, 2);
            lbu(v1, s1, 1);
            a0 = sll(a0, 24);
            lbu(a3, s1, 3);
            s1 = addiu(s1, 4);
            v0 = sll(v0, 8);
            v1 = sll(v1, 16);
            a0 = a0 | a3;
            v0 = v0 | v1;
            s0 = a0 | v0;
            a0 = subu(s0, t0);
            a0 = addu(s3, a0);
            a0 = addiu(a0, 8);
            jal(ctx, 0x554BBCu, gen::fn_memcmp_005211b8);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = si(-1);
            if (!cc) {
                // 0x00554bcc
                charge(ctx, 35);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                t3 = 0;
                sb(v0, s2, 0);
                lbu(v1, s1, 0);
                s1 = addiu(s1, 1);
                sb(v1, s2, 1);
                lbu(v0, s1, 0);
                lbu(v1, s1, 1);
                s1 = addiu(s1, 2);
                v0 = sll(v0, 8);
                a2 = addiu(s1, 4);
                v0 = v0 | v1;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, s2, 8);
                lbu(v1, s1, 0);
                lbu(v0, s1, 2);
                lbu(a0, s1, 1);
                v1 = sll(v1, 24);
                lbu(a1, s1, 3);
                s1 = addiu(a2, 8);
                v0 = sll(v0, 8);
                a0 = sll(a0, 16);
                v0 = v0 | a0;
                v1 = v1 | a1;
                v1 = v1 | v0;
                sw(v1, s2, 4);
                lbu(v0, s1, 0);
                lbu(v1, s1, 1);
                s1 = addiu(a2, 16);
                v0 = sll(v0, 8);
                v0 = v0 | v1;
                sw(v0, s2, 528);
                if (v0 != 0) {
                    // 0x00554c58
                    charge(ctx, 6);
                    t7 = addiu(s2, 4);
                    t6 = addiu(s2, 8);
                    t5 = addiu(s2, 12);
                    t4 = addiu(s2, 16);
                    t2 = 528;
                    for (;;) {
                        // 0x00554c70
                        charge(ctx, 57);
                        lbu(v0, s1, 0);
                        a2 = addu(t7, t2);
                        lbu(v1, s1, 2);
                        a3 = addu(t6, t2);
                        lbu(a0, s1, 1);
                        v0 = sll(v0, 24);
                        lbu(a1, s1, 3);
                        s1 = addiu(s1, 4);
                        a0 = sll(a0, 16);
                        v1 = sll(v1, 8);
                        v1 = v1 | a0;
                        v0 = v0 | a1;
                        v0 = v0 | v1;
                        t0 = addu(t5, t2);
                        sw(v0, a2, 0);
                        t1 = addu(t4, t2);
                        t3 = addiu(t3, 1);
                        t2 = addiu(t2, 16);
                        lbu(v0, s1, 0);
                        lbu(v1, s1, 2);
                        lbu(a0, s1, 1);
                        v0 = sll(v0, 24);
                        lbu(a1, s1, 3);
                        s1 = addiu(s1, 4);
                        a0 = sll(a0, 16);
                        v1 = sll(v1, 8);
                        v1 = v1 | a0;
                        v0 = v0 | a1;
                        v0 = v0 | v1;
                        sw(v0, a3, 0);
                        lbu(v1, s1, 0);
                        lbu(v0, s1, 2);
                        lbu(a0, s1, 1);
                        v1 = sll(v1, 24);
                        lbu(a1, s1, 3);
                        s1 = addiu(s1, 4);
                        a0 = sll(a0, 16);
                        v0 = sll(v0, 8);
                        v0 = v0 | a0;
                        v1 = v1 | a1;
                        v1 = v1 | v0;
                        sw(v1, t0, 0);
                        lbu(a0, s1, 0);
                        lbu(v0, s1, 2);
                        lbu(v1, s1, 1);
                        a0 = sll(a0, 24);
                        lbu(a1, s1, 3);
                        v0 = sll(v0, 8);
                        v1 = sll(v1, 16);
                        v0 = v0 | v1;
                        a0 = a0 | a1;
                        a0 = a0 | v0;
                        sw(a0, t1, 0);
                        lw(v0, s2, 528);
                        v0 = slt(t3, v0);
                        s1 = addiu(s1, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x00554d54
                charge(ctx, 4);
                lb(v0, s1, 0);
                s1 = addiu(s1, 8);
                sw(v0, s2, 6292);
                if (i64(v0) > 0) {
                    // 0x00554d64
                    charge(ctx, 7);
                    t3 = v0;
                    t5 = addiu(s2, 8);
                    t4 = addiu(s2, 10);
                    t2 = addiu(s2, 12);
                    t1 = addiu(s2, 14);
                    t0 = 6288;
                    for (;;) {
                        // 0x00554d80
                        charge(ctx, 31);
                        lbu(v0, s1, 0);
                        a0 = addu(t5, t0);
                        lbu(v1, s1, 1);
                        s1 = addiu(s1, 2);
                        v0 = sll(v0, 8);
                        a1 = addu(t4, t0);
                        v1 = v1 | v0;
                        a2 = addu(t2, t0);
                        sh(v1, a0, 0);
                        a3 = addu(t1, t0);
                        t3 = addiu(t3, -1);
                        t0 = addiu(t0, 8);
                        lbu(v0, s1, 0);
                        lbu(v1, s1, 1);
                        s1 = addiu(s1, 2);
                        v0 = sll(v0, 8);
                        v1 = v1 | v0;
                        sh(v1, a1, 0);
                        lbu(v0, s1, 0);
                        lbu(v1, s1, 1);
                        s1 = addiu(s1, 2);
                        v0 = sll(v0, 8);
                        v1 = v1 | v0;
                        sh(v1, a2, 0);
                        lbu(v0, s1, 0);
                        lbu(v1, s1, 1);
                        s1 = addiu(s1, 2);
                        v0 = sll(v0, 8);
                        v1 = v1 | v0;
                        sh(v1, a3, 0);
                        if (t3 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x00554dfc
                charge(ctx, 6);
                lbu(v1, s1, 0);
                s1 = addiu(s1, 8);
                t3 = 0;
                v0 = sll(v1, 24);
                sb(v1, s2, 12);
                if (i64(v0) > 0) {
                    // 0x00554e14
                    charge(ctx, 3);
                    t1 = addiu(s2, 4);
                    t0 = 16;
                    for (;;) {
                        // 0x00554e20
                        charge(ctx, 22);
                        lbu(v0, s1, 0);
                        a2 = addu(t1, t0);
                        lbu(v1, s1, 2);
                        a3 = addu(s2, t0);
                        lbu(a0, s1, 1);
                        v0 = sll(v0, 24);
                        lbu(a1, s1, 3);
                        s1 = addiu(s1, 4);
                        v1 = sll(v1, 8);
                        a0 = sll(a0, 16);
                        v1 = v1 | a0;
                        v0 = v0 | a1;
                        v0 = v0 | v1;
                        t3 = addiu(t3, 1);
                        sw(v0, a2, 0);
                        t0 = addiu(t0, 16);
                        lbu(v1, s1, 0);
                        sb(v1, a3, 0);
                        lb(v0, s2, 12);
                        v0 = slt(t3, v0);
                        s1 = addiu(s1, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x00554e78
                charge(ctx, 1);
                v0 = addiu(s0, 8);
            }
        } else {
            // 0x00554b6c
            charge(ctx, 4);
            a0 = s2;
            jal(ctx, 0x554B6Cu, gen::fn_sub_554EA0_00554ea0);
            v0 = 0;
        }
    }
    // 0x00554e7c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00555570 sub_555570 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// One demuxer step in the critical section.
void sub_555570(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00555570
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x55557Cu, gen::fn_sub_5546F0_005546f0);
    a0 = s0;
    jal(ctx, 0x555584u, gen::fn_sub_5555A0_005555a0);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_554708_00554708(ctx);  // tail call
}

// 0x005555A0 sub_5555A0 -- 180 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The demuxer state machine: header (0x554FD0), then the segment reader (0x555120 / 0x555470).
void sub_5555A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005555a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lb(a1, s0, 0);
    if (a1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005555c0
        charge(ctx, 3);
        lb(v1, s0, 1);
        v0 = 2;
        if (v1 == a1) {
            // 0x005555cc
            charge(ctx, 4);
            ld(s0, sp, 0x0);
            ld(ra, sp, 0x8);
            sp = addiu(sp, 0x10);
            gen::fn_sub_554FD0_00554fd0(ctx);  // tail call
            return;
        }
        // 0x005555e0
        charge(ctx, 2);
        if (v1 != v0) {
            ld(s0, sp, 0x0);
            goto L_00555648;
        }
        // 0x005555e8
        charge(ctx, 3);
        lb(v0, s0, 3);
        if (v0 != 0) {
            ld(s0, sp, 0x0);
            goto L_00555648;
        }
        // 0x005555f4
        charge(ctx, 3);
        lw(v0, s0, 6488);
        if (v0 == 0) {
            // 0x00555610
            charge(ctx, 5);
            jal(ctx, 0x555610u, gen::fn_sub_555120_00555120);
            v1 = si(-1);
            if (v0 != v1) {
                ld(s0, sp, 0x0);
                goto L_00555648;
            }
            // 0x00555624
            charge(ctx, 5);
            a0 = s0;
            ld(s0, sp, 0x0);
            ld(ra, sp, 0x8);
            sp = addiu(sp, 0x10);
            gen::fn_sub_555120_00555120(ctx);  // tail call
            return;
        }
        // 0x00555600
        charge(ctx, 2);
        ld(s0, sp, 0x0);
        if (v0 == a1) {
            // 0x00555638
            charge(ctx, 3);
            ld(ra, sp, 0x8);
            sp = addiu(sp, 0x10);
            gen::fn_sub_555470_00555470(ctx);  // tail call
            return;
        }
        // 0x00555608
        charge(ctx, 2);
        ld(ra, sp, 0x8);
        // 0x0055564c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_00555648:
    charge(ctx, 1);
    ld(ra, sp, 0x8);
    // 0x0055564c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00555658 sub_555658 -- 72 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10, s1 sp+0x8
// AIX demuxer server: steps each of the 4 demuxers.
void sub_555658(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00555658
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7A0000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, -23760);  // &0x79A330
    sd(ra, sp, 0x10);
    sd(s1, sp, 0x8);
    s1 = addiu(s0, 25968);  // "X9|"
    a0 = s0;
    for (;;) {
        // 0x00555678
        charge(ctx, 5);
        s0 = addiu(s0, 6492);
        jal(ctx, 0x555678u, gen::fn_sub_555570_00555570);
        v0 = slt(s0, s1);
        a0 = s0;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0055568c
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00555898 sub_555898 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// PS2RNA voice query: -1 when uninitialised, -3 when the lookup (0x555788) fails, else stores its +12 into *$a1 and
// returns 0.
void sub_555898(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00555898
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 0x990000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, 29708);  // 0x99740C
    v0 = si(-1);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(ra, sp, 0x8);
    if (v1 != 0) {
        // 0x005558b8
        charge(ctx, 5);
        jal(ctx, 0x5558B8u, gen::fn_sub_555788_00555788);
        v1 = v0;
        v0 = si(-3);
        if (v1 != 0) {
            // 0x005558cc
            charge(ctx, 3);
            lw(v1, v1, 12);
            v0 = 0;
            sw(v1, s0, 0);
        }
    }
    // 0x005558d8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00557A58 SRD_Create -- 132 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// SRD_Create: claims the single SRD object (0x7A08B0) in the critical section; 0 when busy.
void SRD_Create(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00557a58
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = 0;
    jal(ctx, 0x557A68u, gen::fn_sub_5649A8_005649a8);
    v0 = 0x7A0000;
    s0 = addiu(v0, 2224);  // &srd_obj
    lb(v0, s0, 0);  // srd_obj
    if (v0 == 0) {
        // 0x00557a84
        charge(ctx, 14);
        jal(ctx, 0x557A84u, gen::fn_sub_557A28_00557a28);
        a0 = 1;
        sb(a0, s0, 0);
        v1 = 0x7A0000;
        v1 = addiu(v1, 2320);  // &0x7A0910
        a1 = si(-1);
        lw(v0, v1, 0);  // 0x7A0910
        s1 = s0;
        sb(a1, s0, 3);
        v0 = addiu(v0, 1);
        sb(zero, s0, 2);
        sw(v0, v1, 0);  // 0x7A0910
        sw(zero, s0, 4);
    }
    // 0x00557abc
    charge(ctx, 8);
    jal(ctx, 0x557ABCu, gen::fn_sub_564A20_00564a20);
    v0 = s1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00557AE0 sub_557AE0 -- 160 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Destroys the SRD handle (by its "invalid SRD_Destroy" text): clears the object, counts the releases. [proposed:
// SRD_Destroy]
void sub_557AE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00557ae0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = 0x7A0000;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x557AF4u, gen::fn_sub_5649A8_005649a8);
    a0 = 0x7C0000;
    v0 = addiu(s1, 2224);  // &srd_obj
    a0 = addiu(a0, 17984);  // &0x7C4640
    a1 = s0;
    a2 = v0;
    if (s0 == v0) {
        // 0x00557b28
        charge(ctx, 3);
        lb(a0, s0, 2);
        v0 = 3;
        if (a0 != 0) {
            // 0x00557b34
            charge(ctx, 2);
            cc = a0 == v0;  // the condition, before the delay slot changes it
            v0 = 9;
            if (!cc) {
                // 0x00557b3c
                charge(ctx, 2);
                cc = a0 == v0;  // the condition, before the delay slot changes it
                a0 = 0x7C0000;
                if (!cc) {
                    // 0x00557b44
                    charge(ctx, 2);
                    a0 = addiu(a0, 18048);
                    jal(ctx, 0x557B44u, gen::fn_scePrintf_00505e48);
                }
            }
        }
        // 0x00557b4c
        charge(ctx, 9);
        jal(ctx, 0x557B4Cu, gen::fn_sub_557A28_00557a28);
        v1 = 0x7A0000;
        sb(zero, s1, 2224);
        v1 = addiu(v1, 2324);  // &0x7A0914
        lw(v0, v1, 0);  // 0x7A0914
        v0 = addiu(v0, 1);
        sw(v0, v1, 0);  // 0x7A0914
        ld(s0, sp, 0x0);
    } else {
        // 0x00557b14
        charge(ctx, 4);
        jal(ctx, 0x557B14u, gen::fn_scePrintf_00505e48);
        ld(s0, sp, 0x0);
    }
    // 0x00557b70
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_564A20_00564a20(ctx);  // tail call
}

// 0x00557D20 sub_557D20 -- 8 bytes; leaf frame (no stack)
// Returns an SRD handle's status byte (+2).
void sub_557D20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00557d20
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, 2);
}

// 0x00557D28 sub_557D28 -- 44 bytes; leaf frame (no stack)
// A short busy wait (512 iterations).
void sub_557D28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00557d28
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 16383;
    v0 = addiu(v0, -32);
    for (;;) {
        // 0x00557d30
        charge(ctx, 7);
        if (i64(v0) < 0) {
            break;
        }
        v0 = addiu(v0, -32);
        backedge(ctx);
    }
    // 0x00557d4c
    charge(ctx, 2);
}

// 0x00557D80 sub_557D80 -- 204 bytes; frame 0x50: s0 sp+0x10, ra sp+0x48, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, s6 sp+0x40
// Waits for the host-file read to finish (sceIoctl poll), 36864 tries; error -> status 9. [proposed: srd_wait_hst]
void sub_557D80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00557d80
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 1;
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x48);
    sw(v0, sp, 0x0);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s2, sp, 0x20);
    s2 = 0;
    sd(s3, sp, 0x28);
    s3 = 0x9000;
    sd(s4, sp, 0x30);
    s4 = 1;
    sd(s5, sp, 0x38);
    s5 = 0x7C0000;
    sd(s6, sp, 0x40);
    s6 = 9;
    lw(v0, sp, 0x0);
    for (;;) {
        // 0x00557dc8
        charge(ctx, 2);
        ld(s0, sp, 0x10);
        if (v0 != s4) {
            break;
        }
        // 0x00557dd0
        charge(ctx, 11);
        a0 = 4352;
        jal(ctx, 0x557DD0u, gen::fn_sub_558988_00558988);
        lw(a0, s1, 48);
        a1 = 1;
        a2 = sp;
        jal(ctx, 0x557DE0u, gen::fn_sub_558C20_00558c20);
        a0 = 4353;
        s0 = v0;
        jal(ctx, 0x557DECu, gen::fn_sub_558988_00558988);
        if (i64(s0) < 0) {
            goto L_00557dfc_3;
        }
        // 0x00557e08
        charge(ctx, 5);
        s2 = addiu(s2, 1);
        jal(ctx, 0x557E08u, gen::fn_sub_557D28_00557d28);
        v0 = slt(s3, s2);
        if (v0 != 0) {
            goto L_00557e1c_5;
        }
        lw(v0, sp, 0x0);
        backedge(ctx);
    }
    // 0x00557e28 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
    return;
L_00557dfc_3:
    charge(ctx, 3);
    sw(s0, s1, 52);
    sb(s6, s1, 2);
L_00557e24:
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    // 0x00557e28 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
    return;
L_00557e1c_5:
    charge(ctx, 2);
    a0 = addiu(s5, 18080);
    jal(ctx, 0x557E1Cu, gen::fn_scePrintf_00505e48);
    goto L_00557e24;
}

// 0x00557E50 SRD_WaitComplete -- 268 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// SRD_WaitComplete: takes the server lock, waits on the DVD or host read, marks the handle complete.
void SRD_WaitComplete(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00557e50
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = 0;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    s3 = 0x7A0000;
    for (;;) {
        // 0x00557e80
        charge(ctx, 3);
        v0 = slti(s0, 1000);
        if (v0 != 0) {
            // 0x00557e8c
            charge(ctx, 7);
            jal(ctx, 0x557E8Cu, gen::fn_sub_564978_00564978);
            a0 = addiu(s3, 2284);
            lw(v0, a0, 0);
            v1 = 1;
            if (v0 != v1) {
                goto L_00557ec0;
            }
            // 0x00557ea8
            charge(ctx, 6);
            jal(ctx, 0x557EA8u, gen::fn_sub_564990_00564990);
            jal(ctx, 0x557EB0u, gen::fn_sub_557D28_00557d28);
            v0 = addiu(s0, 1);
            backedge(ctx);
            // 0x00557e78
            charge(ctx, 2);
            v0 = sll(v0, 16);
            s0 = sra(v0, 16);
            continue;
        }
        lb(s2, s1, 2);
        break;
    }
L_00557ecc:
    charge(ctx, 3);
    v0 = 2;
    if (s2 != v0) {
        sw(zero, s3, 2284);
    } else {
        // 0x00557ed8
        charge(ctx, 6);
        v0 = 0x7A0000;
        a0 = 1;
        s0 = addiu(v0, 2224);  // &srd_obj
        lb(v1, s0, 1);  // 0x7A08B1
        lbu(v0, s0, 1);  // 0x7A08B1
        if (v1 == a0) {
            // 0x00557ef0
            charge(ctx, 3);
            a0 = s1;
            jal(ctx, 0x557EF0u, gen::fn_srd_wait_dvd_00557d58);
            lbu(v0, s0, 1);
        }
        // 0x00557efc
        charge(ctx, 4);
        v0 = sll(v0, 24);
        v0 = sra(v0, 24);
        if (v0 != s2) {
            lb(v1, s1, 2);
        } else {
            // 0x00557f0c
            charge(ctx, 3);
            a0 = s1;
            jal(ctx, 0x557F0Cu, gen::fn_sub_557D80_00557d80);
            lb(v1, s1, 2);
        }
        // 0x00557f18
        charge(ctx, 3);
        v0 = 9;
        cc = v1 == v0;  // the condition, before the delay slot changes it
        v0 = 3;
        if (!cc) {
            // 0x00557f24
            charge(ctx, 6);
            v1 = 0x7A0000;
            sb(v0, s1, 2);
            v1 = addiu(v1, 2316);  // &0x7A090C
            lw(v0, v1, 0);  // 0x7A090C
            v0 = addiu(v0, 1);
            sw(v0, v1, 0);  // 0x7A090C
        }
        // 0x00557f3c
        charge(ctx, 1);
        sw(zero, s3, 2284);
    }
    // 0x00557f40 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    return;
L_00557ec0:
    charge(ctx, 3);
    link(ctx, 0x557EC0u);  // $ra first: the delay slot below depends on it
    sw(v1, a0, 0);
    call(ctx, gen::fn_sub_564990_00564990);
    lb(s2, s1, 2);
    goto L_00557ecc;
}

// 0x00557F80 sub_557F80 -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Sets an SRD handle's break flag. [proposed: SRD_Break]
void sub_557F80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00557f80
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x557F8Cu, gen::fn_sub_5649A8_005649a8);
    a0 = 0x7C0000;
    v1 = 1;
    a0 = addiu(a0, 18112);  // &0x7C46C0
    if (s0 != 0) {
        // 0x00557fb8
        charge(ctx, 3);
        lw(v0, s0, 4);
        if (v0 != v1) {
            sw(v1, s0, 4);
            // 0x00557fd8
            charge(ctx, 1);
            ld(s0, sp, 0x0);
        } else {
            // 0x00557fc4
            charge(ctx, 5);
            a0 = 0x7C0000;
            a0 = addiu(a0, 18144);  // &0x7C46E0
            jal(ctx, 0x557FC8u, gen::fn_scePrintf_00505e48);
            ld(s0, sp, 0x0);
        }
    } else {
        // 0x00557fa4
        charge(ctx, 4);
        jal(ctx, 0x557FA4u, gen::fn_scePrintf_00505e48);
        ld(s0, sp, 0x0);
    }
    // 0x00557fdc
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564A20_00564a20(ctx);  // tail call
}

// 0x00558500 SRD_ExecServer -- 236 bytes; frame 0x30: s3 sp+0x18, s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x20
// SRD_ExecServer: under the busy flag, runs the DVD or the host-file request step.
void SRD_ExecServer(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00558500
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x7A0000;
    sd(s3, sp, 0x18);
    s3 = 0x7A0000;
    a0 = addiu(s3, 2284);  // &0x7A08EC
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    s1 = addiu(v0, 2224);  // &srd_obj
    jal(ctx, 0x558524u, gen::fn_sub_5655E8_005655e8);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 1;
    if (!cc) {
        // 0x00558534
        charge(ctx, 3);
        lb(s0, s1, 1);
        lbu(v1, s1, 1);
        if (s0 == v0) {
            // 0x00558540
            charge(ctx, 5);
            v0 = 0x7A0000;
            s2 = addiu(v0, 2288);  // &0x7A08F0
            lw(v1, s2, 0);  // 0x7A08F0
            if (v1 == s0) {
                // 0x00558554
                charge(ctx, 2);
                jal(ctx, 0x558554u, gen::fn_sub_5649D8_005649d8);
            }
            // 0x0055855c
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x55855Cu, gen::fn_srd_exec_dvd_00558138);
            lw(v0, s2, 0);
            if (v0 != s0) {
                lbu(v1, s1, 1);
            } else {
                // 0x00558570
                charge(ctx, 3);
                jal(ctx, 0x558570u, gen::fn_sub_564A50_00564a50);
                lbu(v1, s1, 1);
            }
        }
        // 0x0055857c
        charge(ctx, 5);
        v0 = sll(v1, 24);
        v1 = 2;
        v0 = sra(v0, 24);
        if (v0 != v1) {
            sw(zero, s3, 2284);
        } else {
            // 0x00558590
            charge(ctx, 6);
            v1 = 0x7A0000;
            s2 = 1;
            s0 = addiu(v1, 2292);  // &0x7A08F4
            lw(v0, s0, 0);  // 0x7A08F4
            if (v0 == s2) {
                // 0x005585a8
                charge(ctx, 2);
                jal(ctx, 0x5585A8u, gen::fn_sub_5649D8_005649d8);
            }
            // 0x005585b0
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x5585B0u, gen::fn_sub_558320_00558320);
            lw(v0, s0, 0);
            if (v0 != s2) {
                sw(zero, s3, 2284);
            } else {
                // 0x005585c4
                charge(ctx, 3);
                jal(ctx, 0x5585C4u, gen::fn_sub_564A50_00564a50);
                sw(zero, s3, 2284);
            }
        }
    }
    // 0x005585d0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00558610 sub_558610 -- 104 bytes; frame 0x10: ra sp+0x0
// Spins while the SRD server is busy (timeout message after 0x19640000 loops). [proposed: SRD_WaitForExecServer]
void sub_558610(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558610
    enter(ctx, 12);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    sp = addiu(sp, -0x10);
    v0 = addiu(v0, 2304);  // &0x7A0900
    sd(ra, sp, 0x0);
    sw(zero, v0, 0);  // 0x7A0900
    t0 = 0x7A0000;
    a3 = 1;
    a1 = v0;
    a2 = 0x19640000;
    a0 = 0x7C0000;
    lw(v0, t0, 2284);  // 0x7A08EC
    for (;;) {
        // 0x00558640
        charge(ctx, 2);
        ld(ra, sp, 0x0);
        if (v0 != a3) {
            break;
        }
        // 0x00558648
        charge(ctx, 7);
        lw(v0, a1, 0);
        v0 = addiu(v0, 1);
        sw(v0, a1, 0);
        lw(v1, a1, 0);
        v1 = sltu(a2, v1);
        if (v1 != 0) {
            goto L_00558664_3;
        }
        lw(v0, t0, 2284);
        backedge(ctx);
    }
    // 0x00558670 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
    return;
L_00558664_3:
    charge(ctx, 3);
    a0 = addiu(a0, 18344);
    jal(ctx, 0x558664u, gen::fn_scePrintf_00505e48);
    ld(ra, sp, 0x0);
    // 0x00558670 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00558988 sub_558988 -- 32 bytes; leaf frame (no stack)
// Records an SRD trace code: previous <- current, current <- $a0; returns the pair's address.
void sub_558988(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00558988
    enter(ctx, 8);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    v0 = 0x7A0000;
    v1 = addiu(v1, 2332);  // &0x7A091C
    v0 = addiu(v0, 2328);  // &0x7A0918
    lw(a1, v1, 0);  // 0x7A091C
    sw(a1, v0, 0);  // 0x7A0918
    sw(a0, v1, 0);  // 0x7A091C
}

// 0x00558A70 sub_558A70 -- 52 bytes; frame 0x10: ra sp+0x0
// Enter the SRD I/O lock when enabled (0x7A0924).
void sub_558A70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558a70
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, 2340);  // 0x7A0924
    a0 = 1;
    sd(ra, sp, 0x0);
    if (v1 != a0) {
        // 0x00558a98
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00558a88
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5649D8_005649d8(ctx);  // tail call
}

// 0x00558AA8 sub_558AA8 -- 52 bytes; frame 0x10: ra sp+0x0
// Leave the SRD I/O lock when enabled.
void sub_558AA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558aa8
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, 2340);  // 0x7A0924
    a0 = 1;
    sd(ra, sp, 0x0);
    if (v1 != a0) {
        // 0x00558ad0
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00558ac0
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564A50_00564a50(ctx);  // tail call
}

// 0x00558B68 sub_558B68 -- 184 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// sceLseek64 or sceLseek (per 0x7A0920) under the lock, error text on failure.
void sub_558B68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558b68
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x558B84u, gen::fn_sub_558A70_00558a70);
    v0 = 0x7A0000;
    v1 = 1;
    lw(a3, v0, 2336);  // 0x7A0920
    a0 = s0;
    a1 = dsll32(s1, 0);
    a1 = dsra32(a1, 0);
    a2 = s2;
    if (a3 != v1) {
        // 0x00558bd8
        charge(ctx, 7);
        jal(ctx, 0x558BD8u, gen::fn_sceLseek_00508a78);
        a0 = 0x7C0000;
        s0 = v0;
        a0 = addiu(a0, 18688);  // &0x7C4900
        a1 = s0;
        if (i64(s0) < 0) {
            // 0x00558bf4
            charge(ctx, 2);
            jal(ctx, 0x558BF4u, gen::fn_scePrintf_00505e48);
        }
    } else {
        // 0x00558bac
        charge(ctx, 7);
        a1 = s1;
        jal(ctx, 0x558BACu, gen::fn_sceLseek64_0050acd8);
        a0 = 0x7C0000;
        s0 = v0;
        a0 = addiu(a0, 18656);  // &0x7C48E0
        a1 = s0;
        if (i64(s0) < 0) {
            // 0x00558bc8
            charge(ctx, 4);
            jal(ctx, 0x558BC8u, gen::fn_scePrintf_00505e48);
        }
    }
    // 0x00558bfc
    charge(ctx, 9);
    jal(ctx, 0x558BFCu, gen::fn_sub_558AA8_00558aa8);
    v0 = s0;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00558C20 sub_558C20 -- 116 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// sceIoctl under the lock, error text on failure.
void sub_558C20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558c20
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x558C3Cu, gen::fn_sub_558A70_00558a70);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x558C4Cu, gen::fn_sceIoctl_005091e8);
    a0 = 0x7C0000;
    s0 = v0;
    a0 = addiu(a0, 18720);  // &0x7C4920
    a1 = s0;
    if (i64(s0) < 0) {
        // 0x00558c68
        charge(ctx, 2);
        jal(ctx, 0x558C68u, gen::fn_scePrintf_00505e48);
    }
    // 0x00558c70
    charge(ctx, 9);
    jal(ctx, 0x558C70u, gen::fn_sub_558AA8_00558aa8);
    v0 = s0;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00558C98 sub_558C98 -- 100 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// sceOpen under the lock, error text on failure.
void sub_558C98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558c98
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x558CACu, gen::fn_sub_558A70_00558a70);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x558CB8u, gen::fn_sceOpen_00508670);
    a0 = 0x7C0000;
    s0 = v0;
    a0 = addiu(a0, 18752);  // &0x7C4940
    a1 = s0;
    if (i64(s0) < 0) {
        // 0x00558cd4
        charge(ctx, 2);
        jal(ctx, 0x558CD4u, gen::fn_scePrintf_00505e48);
    }
    // 0x00558cdc
    charge(ctx, 8);
    jal(ctx, 0x558CDCu, gen::fn_sub_558AA8_00558aa8);
    v0 = s0;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00558D00 sub_558D00 -- 84 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// sceClose under the lock, error text on failure.
void sub_558D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558d00
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x558D0Cu, gen::fn_sub_558A70_00558a70);
    a0 = s0;
    jal(ctx, 0x558D14u, gen::fn_sceClose_00508900);
    a0 = 0x7C0000;
    s0 = v0;
    a0 = addiu(a0, 18784);  // &0x7C4960
    a1 = s0;
    if (i64(s0) < 0) {
        // 0x00558d30
        charge(ctx, 2);
        jal(ctx, 0x558D30u, gen::fn_scePrintf_00505e48);
    }
    // 0x00558d38
    charge(ctx, 7);
    jal(ctx, 0x558D38u, gen::fn_sub_558AA8_00558aa8);
    v0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00558D58 sub_558D58 -- 116 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// sceRead under the lock, error text on failure.
void sub_558D58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558d58
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x558D74u, gen::fn_sub_558A70_00558a70);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x558D84u, gen::fn_sceRead_00508cb8);
    a0 = 0x7C0000;
    s0 = v0;
    a0 = addiu(a0, 18816);  // &0x7C4980
    a1 = s0;
    if (i64(s0) < 0) {
        // 0x00558da0
        charge(ctx, 2);
        jal(ctx, 0x558DA0u, gen::fn_scePrintf_00505e48);
    }
    // 0x00558da8
    charge(ctx, 9);
    jal(ctx, 0x558DA8u, gen::fn_sub_558AA8_00558aa8);
    v0 = s0;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00559138 sub_559138 -- 8 bytes; leaf frame (no stack)
// Returns a DTR object's state byte (+1).
void sub_559138(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00559138
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, 1);
}

// 0x00559280 sub_559280 -- 236 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// DTR create: a free object of 32 (64 bytes at 0x7A0938) with its two parameters; a message and 0 when full.
void sub_559280(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00559280
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    s3 = a1;
    jal(ctx, 0x55929Cu, gen::fn_sub_5617C0_005617c0);
    v0 = 0x7A0000;
    s1 = addiu(v0, 2360);  // &0x7A0938
    lb(v1, s1, 0);  // 0x7A0938
    a1 = 0;
    if (v1 != 0) {
        // 0x005592b8
        charge(ctx, 2);
        a2 = s1;
        a0 = s1;
        for (;;) {
            // 0x005592c0
            charge(ctx, 5);
            a1 = addiu(a1, 1);
            a0 = addiu(a0, 64);
            v0 = slti(a1, 32);
            v1 = sll(a1, 6);
            if (v0 != 0) {
                // 0x005592d4
                charge(ctx, 4);
                lb(v0, a0, 0);
                s1 = addu(v1, a2);
                if (v0 != 0) {
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x005592e4
    charge(ctx, 3);
    v0 = 32;
    a0 = s1;
    if (a1 != v0) {
        // 0x00559310
        charge(ctx, 13);
        a1 = 0;
        a2 = 64;
        s0 = 64;
        jal(ctx, 0x559318u, gen::fn_memset_00521408);
        sb(zero, s1, 1);
        v0 = 1;
        sw(s0, s1, 56);
        sw(s2, s1, 4);
        sw(s3, s1, 8);
        sb(v0, s1, 0);
        sb(zero, s1, 2);
        sw(v0, s1, 48);
        sw(zero, s1, 52);
    } else {
        // 0x005592f0
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 32;
        a0 = addiu(a0, 19136);  // "i:%d DTR_MAX_OBJ:%d\n"
        a2 = 32;
        jal(ctx, 0x5592FCu, gen::fn_sub_541760_00541760);
        s1 = 0;
    }
    // 0x00559344
    charge(ctx, 10);
    jal(ctx, 0x559344u, gen::fn_sub_5617D8_005617d8);
    v0 = s1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00559370 sub_559370 -- 40 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// DTR destroy: frees the object (byte 0) under the lock.
void sub_559370(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00559370
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x55937Cu, gen::fn_sub_5617C0_005617c0);
    ld(ra, sp, 0x8);
    sb(zero, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x00559398 sub_559398 -- 16 bytes; leaf frame (no stack)
// DTR start: count +60 cleared, state 1.
void sub_559398(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4};
    // 0x00559398
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 1;
    sw(zero, a0, 60);
    sb(v0, a0, 1);
}

// 0x00559718 sub_559718 -- 408 bytes; frame 0x30: s2 sp+0x10, s1 sp+0x8, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// DTX create for id $a0 (16 x 68 bytes at 0x7A1160): checks alignments, opens the IOP side, clears and flushes the EE
// work. [proposed: DTX_Create]
void sub_559718(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00559718
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t0 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    v0 = s2 & 0x3F;
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(s0, sp, 0x0);
    s1 = a3;
    sd(ra, sp, 0x20);
    if (v0 != 0) {
        // 0x00559748
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 19232);  // "eewk is not alignment 64 byte\n"
        goto L_005597e8;
    }
    // 0x00559758
    charge(ctx, 3);
    v0 = s3 & 0x1F;
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = s1 & 0x3F;
    if (!cc) {
        // 0x00559764
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 19264);  // "iopwk is not alignment 32 byte\n"
        goto L_005597e8;
    }
    // 0x00559770
    charge(ctx, 2);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = sltiu(t0, 16);
    if (!cc) {
        // 0x00559778
        charge(ctx, 4);
        a0 = 0x7C0000;
        a1 = s1;
        a0 = addiu(a0, 19296);  // "wklen=%d is not 64*N\n"
        goto L_0055979c;
    }
    // 0x00559788
    charge(ctx, 2);
    v1 = sll(t0, 4);
    if (v0 != 0) {
        // 0x005597b0
        charge(ctx, 8);
        v1 = addu(v1, t0);
        v1 = sll(v1, 2);
        s0 = 0x7A0000;
        s0 = addiu(s0, 4448);  // &0x7A1160
        s0 = addu(s0, v1);
        lb(t0, s0, 0);
        v0 = 0;
        if (t0 == 0) {
            // 0x005597d0
            charge(ctx, 4);
            jal(ctx, 0x5597D0u, gen::fn_dtx_create_rmt_00559588);
            sw(v0, s0, 4);
            if (v0 != 0) {
                // 0x005597f8
                charge(ctx, 39);
                v1 = addiu(s1, -64);
                a0 = 0x20000000;
                v0 = addu(s2, v1);
                a2 = v1;
                v0 = v0 | a0;
                a0 = s2;
                a1 = 0;
                sw(v1, s0, 16);
                sw(s1, s0, 28);
                sw(s3, s0, 24);
                sw(v0, s0, 20);
                sw(zero, s0, 8);
                sw(s2, s0, 12);
                link(ctx, 0x55982Cu);  // $ra first: the delay slot below depends on it
                sb(zero, s0, 1);
                call(ctx, gen::fn_memset_00521408);
                lw(a1, s0, 12);
                lw(v0, s0, 16);
                a0 = a1;
                a1 = addu(a1, v0);
                a1 = addiu(a1, 63);
                jal(ctx, 0x559844u, gen::fn_SyncDCache_00503a58);
                lw(a1, s0, 12);
                lw(v0, s0, 16);
                a0 = a1;
                a1 = addu(a1, v0);
                a1 = addiu(a1, 63);
                jal(ctx, 0x55985Cu, gen::fn_InvalidDCache_00503b98);
                v0 = 0x560000;
                v1 = 0x560000;
                a0 = 1;
                v1 = addiu(v1, -27040);  // &sub_559660
                v0 = addiu(v0, -27064);  // &sub_559648
                sw(v1, s0, 40);
                sb(a0, s0, 0);
                sw(zero, s0, 36);
                sw(zero, s0, 44);
                sb(a0, s0, 2);
                sw(v0, s0, 32);
                v0 = s0;
            } else {
                // 0x005597e0
                charge(ctx, 2);
                a0 = 0x7C0000;
                a0 = addiu(a0, 19344);  // "DTX_Create: can't create DTX of server\n"
            L_005597e8:
                charge(ctx, 4);
                jal(ctx, 0x5597E8u, gen::fn_sub_541760_00541760);
                v0 = 0;
            }
        }
    } else {
        // 0x00559790
        charge(ctx, 3);
        a0 = 0x7C0000;
        a1 = t0;
        a0 = addiu(a0, 19320);  // "illeagal ID (%d) \n"
    L_0055979c:
        charge(ctx, 4);
        jal(ctx, 0x55979Cu, gen::fn_sub_541760_00541760);
        v0 = 0;
    }
    // 0x00559894 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005598B0 sub_5598B0 -- 100 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// DTX destroy: waits while it runs, closes the IOP side, clears the record.
void sub_5598B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005598b0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    sb(zero, s0, 2);
    lb(v0, s0, 1);
    s1 = 1;
    if (v0 == v1) {
        for (;;) {
            // 0x005598d8
            charge(ctx, 5);
            jal(ctx, 0x5598D8u, gen::fn_sub_559D18_00559d18);
            lb(v0, s0, 1);
            if (v0 != s1) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x005598ec
    charge(ctx, 10);
    link(ctx, 0x5598ECu);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 4);
    call(ctx, gen::fn_dtx_destroy_rmt_005595f8);
    a0 = s0;
    ld(s1, sp, 0x8);
    a1 = 0;
    ld(s0, sp, 0x0);
    a2 = 68;
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x00559918 sub_559918 -- 12 bytes; leaf frame (no stack)
// Sets a DTX's send callback (+32) and argument (+36).
void sub_559918(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00559918
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a2, a0, 36);
    sw(a1, a0, 32);
}

// 0x00559928 sub_559928 -- 12 bytes; leaf frame (no stack)
// Sets a DTX's receive callback (+40) and argument (+44).
void sub_559928(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00559928
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a2, a0, 44);
    sw(a1, a0, 40);
}

// 0x00559B98 sub_559B98 -- 120 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// DTX finish (reference counted, 0x7A115C): the last one destroys every live DTX.
void sub_559B98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00559b98
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x7A0000;
    sd(s0, sp, 0x0);
    v1 = addiu(v1, 4444);  // &0x7A115C
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v0, v1, 0);  // 0x7A115C
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x7A115C
    if (v0 == 0) {
        // 0x00559bc4
        charge(ctx, 5);
        v0 = 0x7A0000;
        s2 = 1;
        s0 = addiu(v0, 4448);  // &0x7A1160
        s1 = 15;
        for (;;) {
            // 0x00559bd8
            charge(ctx, 3);
            lb(v0, s0, 0);
            if (v0 != s2) {
                s1 = addiu(s1, -1);
            } else {
                // 0x00559be4
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x559BE4u, gen::fn_sub_5598B0_005598b0);
                s1 = addiu(s1, -1);
            }
            // 0x00559bf0
            charge(ctx, 2);
            s0 = addiu(s0, 68);
            if (i64(s1) < 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00559bf8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00559D18 sub_559D18 -- 96 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// DTX server: steps every live DTX under the lock.
void sub_559D18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00559d18
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = 15;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = 1;
    jal(ctx, 0x559D30u, gen::fn_sub_5617C0_005617c0);
    v0 = 0x7A0000;
    s0 = addiu(v0, 4448);  // &0x7A1160
    for (;;) {
        // 0x00559d40
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x00559d4c
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x559D4Cu, gen::fn_sub_559938_00559938);
            s1 = addiu(s1, -1);
        }
        // 0x00559d58
        charge(ctx, 2);
        s0 = addiu(s0, 68);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00559d60
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x00559D78 dvCiGetInterface -- 48 bytes; frame 0x10: ra sp+0x0
// dvCiGetInterface: clears the root directory, returns the DVD CI function table.
void dvCiGetInterface(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00559d78
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7A0000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 7536);  // &0x7A1D70
    a0 = 0;
    link(ctx, 0x559D8Cu);  // $ra first: the delay slot below depends on it
    lw(v1, v0, 0);
    call(ctx, gen::fn_dvCiSetRootDir_0055b610);
    ld(ra, sp, 0x0);
    v0 = 0x7A0000;
    v0 = addiu(v0, 7560);  // &dvg_ci_vtbl
    sp = addiu(sp, 0x10);
}

// 0x00559DA8 sub_559DA8 -- 48 bytes; frame 0x10: ra sp+0x0
// The DVD CI error callback: calls the registered function (0x7A1D74) with its object and the text.
void sub_559DA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00559da8
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, 7540);  // 0x7A1D74
    a2 = a0;
    sd(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x00559dc0
        charge(ctx, 3);
        v0 = 0x7A0000;
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x559DC4u);  // $ra = the return address
        lw(a0, v0, 7544);
        call_ptr(ctx, jt);
    }
    // 0x00559dcc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00559E80 dvCiExecHndl -- 196 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// dvCiExecHndl: maps its SRD request's status into the handle (3 -> complete, pos += n; 9 -> error) and destroys the
// SRD.
void dvCiExecHndl(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00559e80
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, 28);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
        // 0x00559f38
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00559e9c
    charge(ctx, 8);
    jal(ctx, 0x559E9Cu, gen::fn_sub_5649A8_005649a8);
    link(ctx, 0x559EA4u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 28);
    call(ctx, gen::fn_sub_557D20_00557d20);
    v1 = v0;
    v0 = sltiu(v1, 10);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00559ebc
        charge(ctx, 6);
        v0 = sll(v1, 2);
        v1 = 0x7C0000;
        v1 = addu(v1, v0);
        lw(v1, v1, 19488);
        switch (v1.u()) {
        case 0x559ED8u:  // table[9]
            // 0x00559ed8
            charge(ctx, 4);
            v0 = 3;
            lw(a0, s0, 28);
            sb(v0, s0, 2);
        L_00559f18:
            charge(ctx, 3);
            jal(ctx, 0x559F18u, gen::fn_sub_557AE0_00557ae0);
            sw(zero, s0, 28);
            break;
        case 0x559EE8u:  // table[3]
            // 0x00559ee8
            charge(ctx, 9);
            lw(a0, s0, 16);
            v1 = 1;
            lw(v0, s0, 12);
            sw(a0, s0, 20);
            v0 = addu(v0, a0);
            lw(a0, s0, 28);
            sb(v1, s0, 2);
            sw(v0, s0, 12);
            goto L_00559f18;
        case 0x559F10u:  // table[0]
            // 0x00559f10
            charge(ctx, 2);
            sb(zero, s0, 2);
            lw(a0, s0, 28);
            goto L_00559f18;
        case 0x559F24u:  // table[1, 2, 4, 5, 6, 7, 8]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
        // 0x00559f24
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x00559f28
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564A20_00564a20(ctx);  // tail call
}

// 0x00559F48 dvCiExecServer -- 120 bytes; frame 0x30: s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x20
// dvCiExecServer: under the busy flag, runs every live handle (40 x 72 bytes at 0x7A1DF0).
void dvCiExecServer(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00559f48
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s3, sp, 0x18);
    s3 = 0x7A0000;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    a0 = addiu(s3, 7552);  // &0x7A1D80
    jal(ctx, 0x559F64u, gen::fn_sub_5655E8_005655e8);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x7A0000;
    if (!cc) {
        // 0x00559f74
        charge(ctx, 3);
        s2 = 1;
        s0 = addiu(v0, 7664);
        s1 = 39;
        for (;;) {
            // 0x00559f80
            charge(ctx, 3);
            lb(v0, s0, 0);
            if (v0 != s2) {
                s1 = addiu(s1, -1);
            } else {
                // 0x00559f8c
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x559F8Cu, gen::fn_dvCiExecHndl_00559e80);
                s1 = addiu(s1, -1);
            }
            // 0x00559f98
            charge(ctx, 2);
            s0 = addiu(s0, 72);
            if (i64(s1) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00559fa0
        charge(ctx, 1);
        sw(zero, s3, 7552);
    }
    // 0x00559fa4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00559FC0 sub_559FC0 -- 20 bytes; leaf frame (no stack)
// Registers the DVD CI error callback and its object.
void sub_559FC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00559fc0
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    v1 = 0x7A0000;
    sw(a0, v0, 7540);  // 0x7A1D74
    sw(a1, v1, 7544);  // 0x7A1D78
}

// 0x00559FD8 sub_559FD8 -- 120 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Normalises a file name in place: '/' -> '\\', lower case -> upper case.
void sub_559FD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00559fd8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x559FE4u, gen::fn_strlen_00524388);
    a3 = v0;
    a2 = 0;
    if (a3 != 0) {
        // 0x00559ff8
        charge(ctx, 4);
        t1 = 47;
        t0 = 92;
        a0 = addu(s0, a2);
        for (;;) {
            // 0x0055a008
            charge(ctx, 5);
            a2 = addiu(a2, 1);
            lb(v0, a0, 0);
            a1 = sltu(a2, a3);
            lbu(v1, a0, 0);
            if (v0 == t1) {
                // 0x0055a01c
                charge(ctx, 2);
                sb(t0, a0, 0);
                v1 = t0;
            }
            // 0x0055a024
            charge(ctx, 4);
            v0 = addiu(v1, -97);
            v0 = sltiu(v0, 26);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addiu(v1, -32);
            if (!cc) {
                // 0x0055a034
                charge(ctx, 1);
                sb(v0, a0, 0);
            }
            // 0x0055a038
            charge(ctx, 2);
            a0 = addu(s0, a2);
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0055a040 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0055B220 dvci_get_fstate -- 220 bytes; frame 0x30: s1 sp+0x18, s0 sp+0x10, ra sp+0x20
// dvci_get_fstate: the "DVD-ROM" image, a LSN-addressed name, or a lookup in the file cache.
void dvci_get_fstate(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055b220
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x18);
    s1 = a0;
    a0 = 0x7C0000;
    sd(s0, sp, 0x10);
    a0 = addiu(a0, 20224);  // "DVD-ROM"
    s0 = a1;
    sd(ra, sp, 0x20);
    a1 = s1;
    jal(ctx, 0x55B240u, gen::fn_strcmp_00524128);
    a0 = s1;
    a1 = 46;
    if (v0 != 0) {
        // 0x0055b278
        charge(ctx, 9);
        jal(ctx, 0x55B278u, gen::fn_dvci_is_lsn_access_fname_0055b120);
        v1 = 0x7A0000;
        a3 = 1;
        v1 = addiu(v1, 10848);  // &0x7A2A60
        a0 = s1;
        a1 = sp;
        a2 = addiu(sp, 0x4);
        if (v0 != a3) {
            // 0x0055b2c0
            charge(ctx, 5);
            sw(zero, s0, 0);
            sw(zero, s0, 4);
            lw(v0, v1, 0);
            a2 = v0;
            if (v0 != 0) {
                // 0x0055b2d4
                charge(ctx, 4);
                lw(a3, v1, 4);
                a0 = s0;
                a1 = s1;
                jal(ctx, 0x55B2DCu, gen::fn_dvci_get_fp_from_fname_0055b030);
            }
            // 0x0055b2e4
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0055b29c
            charge(ctx, 9);
            jal(ctx, 0x55B29Cu, gen::fn_dvci_get_adr_size_0055b160);
            v0 = 0;
            lw(v1, sp, 0x4);
            lw(a0, sp, 0x0);
            v1 = sll(v1, 11);
            sw(v1, s0, 4);
            sw(a0, s0, 0);
        }
    } else {
        // 0x0055b254
        charge(ctx, 8);
        v0 = si(-1);
        a0 = 0x7C0000;
        sw(v0, s0, 4);
        a0 = addiu(a0, 20232);  // "DVCI: CD/DVD-ROM Image opened%c\n"
        link(ctx, 0x55B264u);  // $ra first: the delay slot below depends on it
        sw(zero, s0, 0);
        call(ctx, gen::fn_sub_541760_00541760);
        v0 = 1;
    }
    // 0x0055b2e8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0055B300 dvCiLoadFcache -- 380 bytes; frame 0x30: s4 sp+0x20, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x28
// dvCiLoadFcache: reads the file list file and builds the file cache in $a1 ($a2 bytes, $a3 name length).
void dvCiLoadFcache(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055b300
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s4, sp, 0x20);
    s4 = 0x990000;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a1;
    a2 = 4096;
    a0 = addiu(s4, 31680);  // &0x997BC0
    a1 = 0;
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x28);
    s3 = a3;
    jal(ctx, 0x55B338u, gen::fn_memset_00521408);
    v1 = 0x7A0000;
    lw(v0, v1, 10848);  // 0x7A2A60
    if (v0 != 0) {
        // 0x0055b350
        charge(ctx, 2);
        jal(ctx, 0x55B350u, gen::fn_sub_55B0F8_0055b0f8);
    }
    // 0x0055b358
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x0055b360
        charge(ctx, 2);
        if (s2 == 0) {
            goto L_0055b370;
        }
        // 0x0055b368
        charge(ctx, 2);
        if (s1 == 0) {
            goto L_0055b370;
        }
        goto L_0055b378;
    }
L_0055b370:
    charge(ctx, 2);
    jal(ctx, 0x55B370u, gen::fn_sub_55B0F8_0055b0f8);
L_0055b378:
    charge(ctx, 2);
    v0 = 0;
    if (s0 != 0) {
        // 0x0055b380
        charge(ctx, 2);
        a0 = 0x7C0000;
        if (s2 == 0) {
            // 0x0055b388
            charge(ctx, 3);
            a1 = 0;
            a0 = addiu(a0, 20272);
            goto L_0055b3ac;
        }
        // 0x0055b398
        charge(ctx, 2);
        a0 = s2;
        if (s1 != 0) {
            // 0x0055b3c0
            charge(ctx, 9);
            a1 = 0;
            s4 = addiu(s4, 31680);
            a2 = s1;
            jal(ctx, 0x55B3C8u, gen::fn_memset_00521408);
            a0 = s0;
            a1 = s4;
            jal(ctx, 0x55B3D4u, gen::fn_dvci_load_flist_0055ad18);
            if (v0 != 0) {
                s0 = addiu(s3, 9);
                // 0x0055b410
                charge(ctx, 7);
                a1 = s4;
                divu(s1, s0);
                a2 = 4096;
                t0 = s3;
                a0 = s2;
                if (s0 == 0) {
                    brk(ctx, 0x55B428u, 0x7u);
                }
                // 0x0055b42c
                charge(ctx, 9);
                mflo(s1);
                a3 = s1;
                s1 = sll(s1, 3);
                jal(ctx, 0x55B434u, gen::fn_dvci_analysis_flist_0055ab80);
                a0 = s2;
                a1 = v0;
                jal(ctx, 0x55B440u, gen::fn_dvci_search_fstate_0055aea0);
                if (s0 == 0) {
                    brk(ctx, 0x55B44Cu, 0x7u);
                }
                // 0x0055b450
                charge(ctx, 3);
                v1 = addiu(s3, 1);
                mult(v0, v0, v1);
                v0 = addu(s1, v0);
            } else {
                // 0x0055b3e4
                charge(ctx, 10);
                a0 = 0x7C0000;
                a1 = s0;
                a0 = addiu(a0, 20368);  // "DVCI: Can't read filelist file.(%s)\n"
                jal(ctx, 0x55B3ECu, gen::fn_sub_5416E8_005416e8);
                a1 = 0x7C0000;
                a1 = addiu(a1, 20408);  // "E0111501:can't read filelist.(dvCiLoadDirInfo)"
                a0 = 0;
                jal(ctx, 0x55B3FCu, gen::fn_sub_559DA8_00559da8);
                v0 = 0;
            }
        } else {
            // 0x0055b3a0
            charge(ctx, 3);
            a0 = 0x7C0000;
            a1 = 0;
            a0 = addiu(a0, 20320);  // &0x7C4F60
        L_0055b3ac:
            charge(ctx, 4);
            jal(ctx, 0x55B3ACu, gen::fn_sub_5416E8_005416e8);
            v0 = 0;
        }
    }
    // 0x0055b45c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0055B5F0 sub_55B5F0 -- 32 bytes; leaf frame (no stack)
// Sets the DVD CI read modes (cdrmode bytes, rdmode word).
void sub_55B5F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0055b5f0
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    v1 = 0x7A0000;
    v0 = addiu(v0, 10864);  // &dvg_ci_cdrmode
    sw(a3, v1, 10868);  // dvg_ci_rdmode
    sb(a2, v0, 2);  // 0x7A2A72
    sb(a0, v0, 0);  // dvg_ci_cdrmode
    sb(a1, v0, 1);  // 0x7A2A71
}

// 0x0055B610 dvCiSetRootDir -- 200 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// dvCiSetRootDir: copies the root directory (adds the leading separator, drops the trailing one).
void dvCiSetRootDir(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055b610
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    a1 = s0;
    sd(ra, sp, 0x10);
    if (s0 == 0) {
        // 0x0055b62c
        charge(ctx, 3);
        v0 = 0x7A0000;
        sb(zero, v0, 10880);  // dvg_ci_root_dir
        goto L_0055b6c4;
    }
    // 0x0055b638
    charge(ctx, 4);
    lb(v1, s0, 0);
    v0 = 47;
    cc = v1 == v0;  // the condition, before the delay slot changes it
    v0 = 92;
    if (!cc) {
        // 0x0055b648
        charge(ctx, 2);
        cc = v1 == v0;  // the condition, before the delay slot changes it
        v0 = 0x7C0000;
        if (cc) {
            goto L_0055b678;
        }
        // 0x0055b650
        charge(ctx, 9);
        a0 = 0x7A0000;
        t0 = addiu(v0, 20016);
        a3 = addiu(a0, 10880);  // &dvg_ci_root_dir
        lb(v1, t0, 0);
        lb(a2, t0, 1);
        sb(v1, a3, 0);  // dvg_ci_root_dir
        sb(a2, a3, 1);  // 0x7A2A81
        s1 = addiu(a0, 10880);  // &dvg_ci_root_dir
        goto L_0055b684;
    }
L_0055b678:
    charge(ctx, 3);
    a0 = 0x7A0000;
    sb(zero, a0, 10880);  // dvg_ci_root_dir
    s1 = addiu(a0, 10880);  // &dvg_ci_root_dir
L_0055b684:
    charge(ctx, 10);
    a0 = s1;
    jal(ctx, 0x55B684u, gen::fn_strcat_00523e68);
    a0 = s0;
    jal(ctx, 0x55B68Cu, gen::fn_strlen_00524388);
    a0 = s1;
    v0 = addu(s0, v0);
    v1 = 47;
    lb(v0, v0, -1);
    a1 = 92;
    if (v0 != v1) {
        // 0x0055b6ac
        charge(ctx, 2);
        ld(s0, sp, 0x0);
        if (v0 == a1) {
            goto L_0055b6b4;
        }
        // 0x0055b6c8 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_0055b6b4:
    charge(ctx, 4);
    jal(ctx, 0x55B6B4u, gen::fn_strlen_00524388);
    v0 = addu(v0, s1);
    sb(zero, v0, -1);
L_0055b6c4:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0055b6c8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0055B7C8 sub_55B7C8 -- 48 bytes; frame 0x10: ra sp+0x0
// The host CI error callback: calls the registered function (0x7A2C0C) with its object and the text.
void sub_55B7C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0055b7c8
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, 11276);  // 0x7A2C0C
    a2 = a0;
    sd(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x0055b7e0
        charge(ctx, 3);
        v0 = 0x7A0000;
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x55B7E4u);  // $ra = the return address
        lw(a0, v0, 11280);
        call_ptr(ctx, jt);
    }
    // 0x0055b7ec (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055B9D8 sub_55B9D8 -- 120 bytes; frame 0x30: s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x20
// Host CI server: under the busy flag, steps each of the 13 handles (48 bytes at 0x7A2C80).
void sub_55B9D8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055b9d8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s3, sp, 0x18);
    s3 = 0x7A0000;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    a0 = addiu(s3, 11284);  // &0x7A2C14
    jal(ctx, 0x55B9F4u, gen::fn_sub_5655E8_005655e8);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x7A0000;
    if (!cc) {
        // 0x0055ba04
        charge(ctx, 3);
        s2 = 1;
        s0 = addiu(v0, 11392);
        s1 = 12;
        for (;;) {
            // 0x0055ba10
            charge(ctx, 3);
            lb(v0, s0, 0);
            if (v0 != s2) {
                s1 = addiu(s1, -1);
            } else {
                // 0x0055ba1c
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x55BA1Cu, gen::fn_sub_55B910_0055b910);
                s1 = addiu(s1, -1);
            }
            // 0x0055ba28
            charge(ctx, 2);
            s0 = addiu(s0, 48);
            if (i64(s1) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0055ba30
        charge(ctx, 1);
        sw(zero, s3, 11284);
    }
    // 0x0055ba34 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0055BB30 sub_55BB30 -- 440 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// Host CI file size: the cache first, else open / lseek(end) / close with the error codes.
void sub_55BB30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055bb30
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x20);
    if (s0 == 0) {
        // 0x0055bb48
        charge(ctx, 3);
        a1 = 0x7C0000;
        a1 = addiu(a1, 20568);  // "E0092704:fname is null.(htCiGetFileSize)"
        goto L_0055bcc0;
    }
    // 0x0055bb58
    charge(ctx, 5);
    a1 = sp;
    jal(ctx, 0x55BB58u, gen::fn_sub_55CF08_0055cf08);
    lw(v0, sp, 0x4);
    lw(s1, sp, 0x4);
    if (v0 != 0) {
        // 0x0055bcd0
        charge(ctx, 1);
        v0 = s1;
    } else {
        // 0x0055bb6c
        charge(ctx, 15);
        v0 = 0x7A0000;
        a0 = s0;
        s1 = addiu(v0, 12016);  // &0x7A2EF0
        a1 = s1;
        jal(ctx, 0x55BB78u, gen::fn_sub_55C610_0055c610);
        a0 = 17408;
        jal(ctx, 0x55BB80u, gen::fn_sub_558988_00558988);
        a0 = s1;
        a1 = 1;
        jal(ctx, 0x55BB8Cu, gen::fn_sub_558C98_00558c98);
        a0 = 17409;
        s0 = v0;
        jal(ctx, 0x55BB98u, gen::fn_sub_558988_00558988);
        v0 = 0x10000;
        if (i64(s0) < 0) {
            // 0x0055bba8
            charge(ctx, 8);
            a0 = 0x7C0000;
            a1 = s1;
            a0 = addiu(a0, 20616);  // "HTCI: sceOpen failed. \"%s\"\n"
            jal(ctx, 0x55BBB0u, gen::fn_sub_541760_00541760);
            a1 = 0x7C0000;
            a1 = addiu(a1, 20648);  // "E0092705:sceOpen fail.(htCiGetFileSize)"
            a0 = 0;
            goto L_0055bcc0;
        }
        // 0x0055bbc8
        charge(ctx, 3);
        v0 = v0 | 0x4;
        if (s0 == v0) {
            // 0x0055bbd4
            charge(ctx, 7);
            a0 = 0x7C0000;
            a0 = addiu(a0, 20688);  // "HTCI: sceOpen failed. IOP Module version is invalid.\n"
            jal(ctx, 0x55BBD8u, gen::fn_sub_541760_00541760);
            a1 = 0x7C0000;
            a1 = addiu(a1, 20744);  // "E0082101:sceOpen fail.(htCiGetFileSize)"
            a0 = 0;
            goto L_0055bcc0;
        }
        v0 = 19;
        // 0x0055bbf0
        charge(ctx, 2);
        if (s0 == v0) {
            // 0x0055bbf8
            charge(ctx, 7);
            a0 = 0x7C0000;
            a0 = addiu(a0, 20784);  // "HTCI: sceOpen failed. file desc is insufficient.\n"
            jal(ctx, 0x55BBFCu, gen::fn_sub_541760_00541760);
            a1 = 0x7C0000;
            a1 = addiu(a1, 20744);  // "E0082101:sceOpen fail.(htCiGetFileSize)"
            a0 = 0;
            goto L_0055bcc0;
        }
        // 0x0055bc18
        charge(ctx, 19);
        a0 = 17920;
        jal(ctx, 0x55BC18u, gen::fn_sub_558988_00558988);
        a0 = s0;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x55BC28u, gen::fn_sub_558B68_00558b68);
        a0 = 17921;
        jal(ctx, 0x55BC30u, gen::fn_sub_558988_00558988);
        a0 = 17920;
        jal(ctx, 0x55BC38u, gen::fn_sub_558988_00558988);
        a0 = s0;
        a1 = 0;
        a2 = 2;
        jal(ctx, 0x55BC48u, gen::fn_sub_558B68_00558b68);
        a0 = 17921;
        s1 = v0;
        jal(ctx, 0x55BC54u, gen::fn_sub_558988_00558988);
        a1 = 0x7C0000;
        if (i64(s1) >= 0) {
            // 0x0055bc90
            charge(ctx, 9);
            a0 = 20480;
            jal(ctx, 0x55BC90u, gen::fn_sub_558988_00558988);
            a0 = s0;
            jal(ctx, 0x55BC98u, gen::fn_sub_558D00_00558d00);
            a0 = 20481;
            s0 = v0;
            jal(ctx, 0x55BCA4u, gen::fn_sub_558988_00558988);
            if (i64(s0) >= 0) {
                v0 = s1;
            } else {
                // 0x0055bcb4
                charge(ctx, 3);
                a1 = 0x7C0000;
                a0 = 0;
                a1 = addiu(a1, 20888);  // "E0092707:sceClose fail.(htCiGetFileSize)"
            L_0055bcc0:
                charge(ctx, 4);
                jal(ctx, 0x55BCC0u, gen::fn_sub_55B7C8_0055b7c8);
                v0 = 0;
            }
        } else {
            // 0x0055bc64
            charge(ctx, 11);
            a0 = 0;
            a1 = addiu(a1, 20840);
            jal(ctx, 0x55BC68u, gen::fn_sub_55B7C8_0055b7c8);
            a0 = 17664;
            jal(ctx, 0x55BC70u, gen::fn_sub_558988_00558988);
            a0 = s0;
            jal(ctx, 0x55BC78u, gen::fn_sub_558D00_00558d00);
            a0 = 17665;
            jal(ctx, 0x55BC80u, gen::fn_sub_558988_00558988);
            v0 = 0;
        }
    }
    // 0x0055bcd4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0055BDA8 sub_55BDA8 -- 28 bytes; frame 0x10: ra sp+0x0
// Clears a host CI handle (48 bytes).
void sub_55BDA8(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055bda8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(ra, sp, 0x0);
    a2 = 48;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0055C240 sub_55C240 -- 244 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// Host CI stop transfer: breaks the SRD read and runs the servers until the handle leaves state 2. [proposed:
// htCiStopTr]
void sub_55C240(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055c240
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = 0;
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    if (s0 == 0) {
        // 0x0055c268
        charge(ctx, 10);
        a1 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a1 = addiu(a1, 21264);  // "E0082401:handl is null."
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        gen::fn_sub_55B7C8_0055b7c8(ctx);  // tail call
        return;
    }
    // 0x0055c290
    charge(ctx, 4);
    lbu(v0, s0, 2);
    v0 = sltiu(v0, 2);
    if (v0 != 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0055c2a0
        charge(ctx, 3);
        lw(a0, s0, 44);
        s1 = 0x630000;
        if (a0 != 0) {
            // 0x0055c2ac
            charge(ctx, 2);
            jal(ctx, 0x55C2ACu, gen::fn_sub_557F80_00557f80);
        }
        // 0x0055c2b4
        charge(ctx, 4);
        s3 = 2;
        s1 = s1 | 0xFFF6;
        s4 = 0x7C0000;
        for (;;) {
            // 0x0055c2d0
            charge(ctx, 9);
            jal(ctx, 0x55C2D0u, gen::fn_SRD_ExecServer_00558500);
            jal(ctx, 0x55C2D8u, gen::fn_sub_55B9D8_0055b9d8);
            a0 = s0;
            jal(ctx, 0x55C2E0u, gen::fn_sub_55C338_0055c338);
            lb(v1, s0, 2);
            if (v1 == s3) {
                // 0x0055c2f4
                charge(ctx, 4);
                s2 = addiu(s2, 1);
                v0 = slt(s1, s2);
                if (v0 != 0) {
                    goto L_0055c304_9;
                }
                backedge(ctx);
                // 0x0055c2c8
                charge(ctx, 2);
                jal(ctx, 0x55C2C8u, gen::fn_sub_55B798_0055b798);
                continue;
            }
            sw(zero, s0, 40);
            break;
        }
    L_0055c310:
        charge(ctx, 2);
        sb(zero, s0, 2);
        ld(s0, sp, 0x0);
    }
    // 0x0055c318 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    return;
L_0055c304_9:
    charge(ctx, 3);
    a0 = addiu(s4, 21288);
    jal(ctx, 0x55C304u, gen::fn_sub_541760_00541760);
    sw(zero, s0, 40);
    goto L_0055c310;
}

// 0x0055C338 sub_55C338 -- 56 bytes; frame 0x10: ra sp+0x0
// Returns a host CI handle's status byte (+2); NULL -> error text and 0.
void sub_55C338(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055c338
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0055c360
        charge(ctx, 1);
        lb(v0, v0, 2);
    } else {
        // 0x0055c348
        charge(ctx, 5);
        a1 = 0x7C0000;
        a1 = addiu(a1, 21168);  // "E0092712:handl is null."
        jal(ctx, 0x55C34Cu, gen::fn_sub_55B7C8_0055b7c8);
        v0 = 0;
    }
    // 0x0055c364 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055C3C8 sub_55C3C8 -- 20 bytes; frame 0x10: ra sp+0x0
// Host CI get file size (forwards to 0x55BB30).
void sub_55C3C8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0055c3c8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55BB30_0055bb30(ctx);  // tail call
}

// 0x0055C610 sub_55C610 -- 276 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// Builds the full host path: device prefix, root directory, the name; '\\' -> '/'.
void sub_55C610(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055c610
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    link(ctx, 0x55C62Cu);  // $ra first: the delay slot below depends on it
    sb(zero, s1, 0);
    call(ctx, gen::fn_sub_55C548_0055c548);
    a1 = 0x7A0000;
    if (v0 == 0) {
        // 0x0055c63c
        charge(ctx, 3);
        a0 = s1;
        a1 = addiu(a1, 12608);
        jal(ctx, 0x55C640u, gen::fn_strcpy_00524270);
    }
    // 0x0055c648
    charge(ctx, 5);
    a0 = s1;
    jal(ctx, 0x55C648u, gen::fn_sub_55C5B8_0055c5b8);
    v1 = 1;
    if (v0 != v1) {
        a1 = s2;
    } else {
        // 0x0055c65c
        charge(ctx, 12);
        s0 = 0x7A0000;
        a0 = s1;
        s0 = addiu(s0, 12344);  // &0x7A3038
        a1 = s0;
        jal(ctx, 0x55C668u, gen::fn_strcat_00523e68);
        a0 = s0;
        jal(ctx, 0x55C670u, gen::fn_strlen_00524388);
        a0 = 92;
        v0 = addu(v0, s0);
        lb(v0, v0, -1);
        v1 = 47;
        if (v0 != a0) {
            // 0x0055c68c
            charge(ctx, 2);
            a1 = s2;
            if (v0 != v1) {
                // 0x0055c694
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x0055c69c
                    charge(ctx, 3);
                    lb(v0, s2, 0);
                    if (v0 != a0) {
                        // 0x0055c6a8
                        charge(ctx, 2);
                        a1 = 0x7C0000;
                        if (v0 != v1) {
                            // 0x0055c6b0
                            charge(ctx, 3);
                            a0 = s1;
                            a1 = addiu(a1, 21328);
                            jal(ctx, 0x55C6B4u, gen::fn_strcat_00523e68);
                        }
                        goto L_0055c6bc;
                    }
                }
            }
            goto L_0055c6c0;
        }
    L_0055c6bc:
        charge(ctx, 1);
        a1 = s2;
    }
L_0055c6c0:
    charge(ctx, 7);
    a0 = s1;
    jal(ctx, 0x55C6C0u, gen::fn_strcat_00523e68);
    a0 = s1;
    jal(ctx, 0x55C6C8u, gen::fn_strlen_00524388);
    a2 = v0;
    a1 = 0;
    if (i64(a2) > 0) {
        // 0x0055c6dc
        charge(ctx, 3);
        t0 = 92;
        a3 = 47;
        a0 = addu(s1, a1);
        for (;;) {
            // 0x0055c6e8
            charge(ctx, 4);
            a1 = addiu(a1, 1);
            lb(v0, a0, 0);
            v1 = slt(a1, a2);
            if (v0 == t0) {
                // 0x0055c6f8
                charge(ctx, 1);
                sb(a3, a0, 0);
            }
            // 0x0055c6fc
            charge(ctx, 4);
            a0 = addu(s1, a1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0055c70c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0055C9D0 sub_55C9D0 -- 352 bytes; frame 0x130: s0 sp+0x100, s3 sp+0x118, s2 sp+0x110, s1 sp+0x108, ra sp+0x120
// Reads a whole host file (up to 4096 bytes) into $a1 with open / lseek / read / close.
void sub_55C9D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055c9d0
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    a2 = 256;
    sd(s0, sp, 0x100);
    s0 = a0;
    sd(s3, sp, 0x118);
    s3 = a1;
    a0 = sp;
    sd(s2, sp, 0x110);
    sd(s1, sp, 0x108);
    sd(ra, sp, 0x120);
    a1 = 0;
    jal(ctx, 0x55C9F8u, gen::fn_memset_00521408);
    a1 = sp;
    a0 = s0;
    jal(ctx, 0x55CA04u, gen::fn_sub_55C610_0055c610);
    a0 = 24576;
    jal(ctx, 0x55CA0Cu, gen::fn_sub_558988_00558988);
    a1 = 1;
    a0 = sp;
    jal(ctx, 0x55CA18u, gen::fn_sub_558C98_00558c98);
    a0 = 24577;
    s2 = v0;
    jal(ctx, 0x55CA24u, gen::fn_sub_558988_00558988);
    a0 = 24832;
    v0 = 0;
    if (i64(s2) >= 0) {
        // 0x0055ca38
        charge(ctx, 12);
        jal(ctx, 0x55CA38u, gen::fn_sub_558988_00558988);
        a0 = s2;
        a1 = 0;
        a2 = 2;
        jal(ctx, 0x55CA48u, gen::fn_sub_558B68_00558b68);
        a0 = 24833;
        s1 = v0;
        jal(ctx, 0x55CA54u, gen::fn_sub_558988_00558988);
        a0 = 25088;
        v0 = 0;
        if (i64(s1) >= 0) {
            // 0x0055ca68
            charge(ctx, 16);
            jal(ctx, 0x55CA68u, gen::fn_sub_558988_00558988);
            a0 = s2;
            a1 = 0;
            a2 = 0;
            jal(ctx, 0x55CA78u, gen::fn_sub_558B68_00558b68);
            s0 = dsll32(v0, 0);
            s0 = dsra32(s0, 0);
            a0 = 25089;
            jal(ctx, 0x55CA88u, gen::fn_sub_558988_00558988);
            v0 = 4096;
            v1 = slti(s1, 4097);
            if (v1 == 0) s1 = v0;
            v0 = 0;
            a0 = 25344;
            if (i64(s0) >= 0) {
                // 0x0055caa8
                charge(ctx, 12);
                jal(ctx, 0x55CAA8u, gen::fn_sub_558988_00558988);
                a0 = s2;
                a2 = dsll32(s1, 0);
                a2 = dsra32(a2, 0);
                a1 = s3;
                jal(ctx, 0x55CABCu, gen::fn_sub_558D58_00558d58);
                a0 = 25345;
                s0 = v0;
                jal(ctx, 0x55CAC8u, gen::fn_sub_558988_00558988);
                a0 = 25856;
                if (i64(s0) >= 0) {
                    // 0x0055caf8
                    charge(ctx, 7);
                    a0 = 25600;
                    jal(ctx, 0x55CAF8u, gen::fn_sub_558988_00558988);
                    a0 = s2;
                    jal(ctx, 0x55CB00u, gen::fn_sub_558D00_00558d00);
                    a0 = 25601;
                    jal(ctx, 0x55CB08u, gen::fn_sub_558988_00558988);
                    v0 = 1;
                } else {
                    // 0x0055cad8
                    charge(ctx, 8);
                    jal(ctx, 0x55CAD8u, gen::fn_sub_558988_00558988);
                    a0 = s2;
                    jal(ctx, 0x55CAE0u, gen::fn_sub_558D00_00558d00);
                    a0 = 25857;
                    jal(ctx, 0x55CAE8u, gen::fn_sub_558988_00558988);
                    v0 = 0;
                }
            }
        }
    }
    // 0x0055cb14 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x100);
    ld(s1, sp, 0x108);
    ld(s2, sp, 0x110);
    ld(s3, sp, 0x118);
    ld(ra, sp, 0x120);
    sp = addiu(sp, 0x130);
}

// 0x0055CEE0 sub_55CEE0 -- 36 bytes; frame 0x10: ra sp+0x0
// Clears the host file cache descriptor (16 bytes at 0x7A3020).
void sub_55CEE0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055cee0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x7A0000;
    sd(ra, sp, 0x0);
    a1 = 0;
    a0 = addiu(a0, 12320);  // &0x7A3020
    a2 = 16;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0055CF08 sub_55CF08 -- 76 bytes; frame 0x10: ra sp+0x0
// Host file cache lookup: clears the result and searches when a cache is set.
void sub_55CF08(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055cf08
    enter(ctx, 12);  // entry check point + this block's cycles
    v1 = a1;
    a1 = a0;
    sp = addiu(sp, -0x10);
    v0 = 0x7A0000;
    sd(ra, sp, 0x0);
    a3 = addiu(v0, 12320);  // &0x7A3020
    sw(zero, v1, 0);
    a0 = v1;
    sw(zero, v1, 4);
    lw(v0, a3, 0);  // 0x7A3020
    a2 = v0;
    if (v0 == 0) {
        // 0x0055cf48
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0055cf38
    charge(ctx, 4);
    lw(a3, a3, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55CE18_0055ce18(ctx);  // tail call
}

// 0x0055D240 sub_55D240 -- 96 bytes; leaf frame (no stack)
// LSC: returns a free object of 32 (568 bytes at 0x7A32A0), or 0.
void sub_55D240(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0055d240
    enter(ctx, 6);  // entry check point + this block's cycles
    a2 = 0x7A0000;
    a3 = 0;
    v1 = addiu(a2, 12960);  // &0x7A32A0
    lb(v0, v1, 0);  // 0x7A32A0
    a1 = 0;
    if (v0 != 0) {
        // 0x0055d260
        charge(ctx, 1);
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x0055d264
            charge(ctx, 4);
            v0 = sll(a1, 3);
            v1 = slti(a1, 32);
            v0 = addu(v0, a1);
            if (v1 == 0) {
                break;
            }
            // 0x0055d274
            charge(ctx, 8);
            v0 = sll(v0, 3);
            a0 = addiu(a2, 12960);
            v0 = subu(v0, a1);
            v0 = sll(v0, 3);
            v0 = addu(v0, a0);
            lb(v1, v0, 0);
            if (v1 == 0) {
                goto L_0055d294_5;
            }
            a1 = addiu(a1, 1);
            backedge(ctx);
        }
    } else {
        // 0x0055d258
        charge(ctx, 2);
        a3 = v1;
    }
    // 0x0055d298 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a3;
    return;
L_0055d294_5:
    charge(ctx, 1);
    a3 = v0;
    // 0x0055d298 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a3;
}

// 0x0055D428 sub_55D428 -- 408 bytes; frame 0x40: s1 sp+0x8, s2 sp+0x10, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s0 sp+0x0, s3 sp+0x18, ra sp+0x38
// LSC entry: queues file $a1 (ring of 16 x 32 bytes: id, name, checksum, offset / size), returns its id or -1.
void sub_55D428(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055d428
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s4, sp, 0x20);
    s4 = a3;
    sd(s5, sp, 0x28);
    s5 = t0;
    sd(s6, sp, 0x30);
    s6 = a2;
    sd(s0, sp, 0x0);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x38);
    if (s1 != 0) {
        // 0x0055d478
        charge(ctx, 4);
        lw(v1, s1, 36);
        v1 = slti(v1, 16);
        v0 = si(-1);
        if (v1 != 0) {
            // 0x0055d488
            charge(ctx, 2);
            if (s2 != 0) {
                lw(v1, s1, 28);
                // 0x0055d4a8
                charge(ctx, 28);
                t0 = 0x7FFF0000;
                t0 = t0 | 0xFFFF;
                s3 = 0;
                a2 = addiu(v1, 15);
                a3 = addiu(v1, 30);
                a1 = slti(a2, 0);
                v0 = a2;
                if (a1 != 0) v0 = a3;
                v1 = sll(v1, 5);
                v0 = sra(v0, 4);
                v1 = addu(s1, v1);
                v0 = sll(v0, 4);
                s0 = addiu(v1, 56);
                v0 = subu(a2, v0);
                sw(s2, s0, 4);
                v0 = sll(v0, 5);
                a0 = s2;
                v0 = addu(v0, s1);
                lw(v1, v0, 56);
                t0 = v1 ^ t0;
                v1 = addiu(v1, 1);
                if (t0 != 0) s3 = v1;
                link(ctx, 0x55D500u);  // $ra first: the delay slot below depends on it
                sw(s3, s0, 0);
                call(ctx, gen::fn_strlen_00524388);
                sw(zero, s0, 8);
                a2 = v0;
                a1 = 0;
                if (a2 != 0) {
                    for (;;) {
                        // 0x0055d518
                        charge(ctx, 8);
                        v0 = addu(s2, a1);
                        a1 = addiu(a1, 1);
                        lbu(v1, v0, 0);
                        a0 = sltu(a1, a2);
                        lw(v0, s0, 8);
                        v0 = addu(v0, v1);
                        sw(v0, s0, 8);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x0055d538
                charge(ctx, 21);
                sw(s4, s0, 16);
                t0 = 1;
                sw(s5, s0, 20);
                sw(zero, s0, 28);
                sw(zero, s0, 24);
                sw(s6, s0, 12);
                lw(v1, s1, 28);
                lw(a2, s1, 36);
                a0 = addiu(v1, 1);
                v1 = addiu(v1, 16);
                a1 = slti(a0, 0);
                v0 = a0;
                if (a1 != 0) v0 = v1;
                lb(a3, s1, 1);
                v0 = sra(v0, 4);
                a2 = addiu(a2, 1);
                v0 = sll(v0, 4);
                sw(a2, s1, 36);
                a0 = subu(a0, v0);
                sw(a0, s1, 28);
                if (a3 == t0) {
                    // 0x0055d58c
                    charge(ctx, 2);
                    v0 = 2;
                    sb(v0, s1, 1);
                }
                // 0x0055d594
                charge(ctx, 1);
                v0 = s3;
            } else {
                // 0x0055d490
                charge(ctx, 5);
                a0 = 0x7C0000;
                a0 = addiu(a0, 21912);  // "E2005012804: Illigal parameter fname=%s\n"
                jal(ctx, 0x55D494u, gen::fn_sub_55DBE8_0055dbe8);
                v0 = si(-1);
            }
        }
    } else {
        // 0x0055d464
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 21864);  // "E2005012803: Illigal parameter lsc=NULL\n"
        jal(ctx, 0x55D468u, gen::fn_sub_55DBE8_0055dbe8);
        v0 = si(-1);
    }
    // 0x0055d598 (the shared epilogue, written out on this path)
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
}

// 0x0055D5C0 sub_55D5C0 -- 64 bytes; frame 0x10: ra sp+0x0
// LSC reset of the queue when stopped.
void sub_55D5C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055d5c0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0055d5cc
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 21960);  // "E2005012805: Illigal parameter lsc=NULL\n"
        sp = addiu(sp, 0x10);
        gen::fn_sub_55DBE8_0055dbe8(ctx);  // tail call
        return;
    }
    // 0x0055d5e0
    charge(ctx, 3);
    lb(v0, a0, 1);
    ld(ra, sp, 0x0);
    if (v0 == 0) {
        // 0x0055d5ec
        charge(ctx, 3);
        sw(zero, a0, 36);
        sw(zero, a0, 28);
        sw(zero, a0, 32);
    }
    // 0x0055d5f8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x0055D600 sub_55D600 -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// LSC start: stops first if running, state 2 with entries else 1.
void sub_55D600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055d600
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x0055d614
        charge(ctx, 6);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        a0 = addiu(a0, 22008);  // "E2005012806: Illigal parameter lsc=NULL\n"
        sp = addiu(sp, 0x10);
        gen::fn_sub_55DBE8_0055dbe8(ctx);  // tail call
        return;
    }
    // 0x0055d630
    charge(ctx, 3);
    lb(v0, s0, 1);
    if (v0 == 0) {
        lw(v0, s0, 36);
    } else {
        // 0x0055d63c
        charge(ctx, 3);
        jal(ctx, 0x55D63Cu, gen::fn_sub_55D668_0055d668);
        lw(v0, s0, 36);
    }
    // 0x0055d648
    charge(ctx, 2);
    if (i64(v0) <= 0) {
        v0 = 1;
    } else {
        // 0x0055d650
        charge(ctx, 1);
        v0 = 2;
    }
    // 0x0055d654 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sb(v0, s0, 1);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0055D730 sub_55D730 -- 96 bytes; frame 0x20: ra sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// LSC server: steps each of the 32 objects.
void sub_55D730(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055d730
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7A0000;
    sd(ra, sp, 0x18);
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 12960);  // &0x7A32A0
    sd(s1, sp, 0x8);
    s1 = 31;
    sd(s2, sp, 0x10);
    s2 = 1;
    for (;;) {
        // 0x0055d758
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x0055d764
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x55D764u, gen::fn_sub_55E0C0_0055e0c0);
            s1 = addiu(s1, -1);
        }
        // 0x0055d770
        charge(ctx, 2);
        s0 = addiu(s0, 568);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0055d778
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0055DB58 sub_55DB58 -- 48 bytes; frame 0x10: ra sp+0x0
// LSC set the flag byte (+3).
void sub_55DB58(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055db58
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0055db78
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sb(a1, a0, 3);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0055db64
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 22768);  // "E2005012822: Illigal parameter lsc=NULL\n"
    sp = addiu(sp, 0x10);
    gen::fn_sub_55DBE8_0055dbe8(ctx);  // tail call
}

// 0x0055DB88 sub_55DB88 -- 28 bytes; frame 0x10: ra sp+0x0
// LSC lock.
void sub_55DB88(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0055db88
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x55DB90u, gen::fn_sub_5617C0_005617c0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055DBA8 sub_55DBA8 -- 20 bytes; frame 0x10: ra sp+0x0
// LSC unlock.
void sub_55DBA8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0055dba8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x0055DBC0 sub_55DBC0 -- 40 bytes; leaf frame (no stack)
// Registers the LSC error callback and its object (both 0 when $a0 is 0).
void sub_55DBC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0055dbc0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    if (a0 != 0) {
        // 0x0055dbd8
        charge(ctx, 4);
        v1 = 0x7A0000;
        sw(a0, v0, 12664);
        sw(a1, v1, 12668);  // 0x7A317C
        return;
    }
    // 0x0055dbc8
    charge(ctx, 4);
    v1 = 0x7A0000;
    sw(zero, v0, 12664);
    sw(zero, v1, 12668);  // 0x7A317C
}

// 0x0055DBE8 sub_55DBE8 -- 140 bytes; frame 0x70: s0 sp+0x0, ra sp+0x8
// LSC error: vsprintf into 0x7A3180 and calls the error callback.
void sub_55DBE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f18{ctx, 18}, f19{ctx, 19};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0055dbe8
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s0, sp, 0x0);
    s0 = 0x7A0000;
    s0 = addiu(s0, 12672);  // &0x7A3180
    sd(a1, sp, 0x38);
    sd(a2, sp, 0x40);
    a2 = addiu(sp, 0x38);
    a1 = a0;
    a0 = s0;
    sd(ra, sp, 0x8);
    sd(a3, sp, 0x48);
    sd(t0, sp, 0x50);
    sd(t1, sp, 0x58);
    sd(t2, sp, 0x60);
    sd(t3, sp, 0x68);
    swc1(f12, sp, 0x18);
    swc1(f13, sp, 0x1C);
    swc1(f14, sp, 0x20);
    swc1(f15, sp, 0x24);
    swc1(f16, sp, 0x28);
    swc1(f17, sp, 0x2C);
    swc1(f18, sp, 0x30);
    link(ctx, 0x55DC40u);  // $ra first: the delay slot below depends on it
    swc1(f19, sp, 0x34);
    call(ctx, gen::fn_vsprintf_005288c8);
    v1 = 0x7A0000;
    lw(v1, v1, 12664);  // 0x7A3178
    a1 = s0;
    if (v1 != 0) {
        // 0x0055dc58
        charge(ctx, 3);
        v0 = 0x7A0000;
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x55DC5Cu);  // $ra = the return address
        lw(a0, v0, 12668);
        call_ptr(ctx, jt);
    }
    // 0x0055dc64 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x70);
}

// 0x0055DC78 __env_lock_8 -- 8 bytes; leaf frame (no stack)
// An empty stub (environment lock).
void __env_lock_8(EEContext& ctx) {
    using namespace hg;
    // 0x0055dc78
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0055DC88 sub_55DC88 -- 128 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// LSC init (reference counted, 0x7A3298): first call clears the pool and the callback.
void sub_55DC88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055dc88
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7A0000;
    sd(s0, sp, 0x10);
    v0 = addiu(v0, 12928);  // " Y|"
    sd(ra, sp, 0x18);
    a0 = sp;
    link(ctx, 0x55DCA0u);  // $ra first: the delay slot below depends on it
    lw(v1, v0, 0);
    call(ctx, gen::fn_sub_55DB88_0055db88);
    v0 = 0x7A0000;
    a0 = 0x7A0000;
    s0 = addiu(v0, 12952);  // &0x7A3298
    a0 = addiu(a0, 12960);  // &0x7A32A0
    lw(v0, s0, 0);  // 0x7A3298
    a1 = 0;
    a2 = 18176;
    if (v0 == 0) {
        // 0x0055dcc8
        charge(ctx, 8);
        jal(ctx, 0x55DCC8u, gen::fn_memset_00521408);
        jal(ctx, 0x55DCD0u, gen::fn___env_lock_8_0055dc78);
        a0 = 0;
        a1 = 0;
        jal(ctx, 0x55DCDCu, gen::fn_sub_55DBC0_0055dbc0);
        lw(v0, s0, 0);
    }
    // 0x0055dce8
    charge(ctx, 8);
    v0 = addiu(v0, 1);
    a0 = sp;
    link(ctx, 0x55DCF0u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 0);
    call(ctx, gen::fn_sub_55DBA8_0055dba8);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0055DD08 sub_55DD08 -- 188 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// LSC finish: the last reference destroys the live objects and clears the pool.
void sub_55DD08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055dd08
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 0x7A0000;
    sd(s0, sp, 0x0);
    v1 = addiu(v1, 12952);  // &0x7A3298
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    lw(v0, v1, 0);  // 0x7A3298
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x7A3298
    if (v0 != 0) {
        // 0x0055dda8
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x0055dd38
    charge(ctx, 4);
    s3 = 0x7A0000;
    s2 = 1;
    s0 = addiu(s3, 12960);  // &0x7A32A0
    s1 = 31;
    for (;;) {
        // 0x0055dd48
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x0055dd54
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x55DD54u, gen::fn_sub_55D3A8_0055d3a8);
            s1 = addiu(s1, -1);
        }
        // 0x0055dd60
        charge(ctx, 2);
        s0 = addiu(s0, 568);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0055dd68
    charge(ctx, 15);
    a0 = addiu(s3, 12960);
    a1 = 0;
    a2 = 18176;
    jal(ctx, 0x55DD70u, gen::fn_memset_00521408);
    jal(ctx, 0x55DD78u, gen::fn___env_unlock_7_0055dc80);
    ld(s0, sp, 0x0);
    a0 = 0;
    ld(s1, sp, 0x8);
    a1 = 0;
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_55DBC0_0055dbc0(ctx);  // tail call
}

// 0x0055E0C0 sub_55E0C0 -- 208 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// One LSC step: the current entry's state 1 start / 2 read / 0 next.
void sub_55E0C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055e0c0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lb(v0, s0, 4);
    cc = v0 == a2;  // the condition, before the delay slot changes it
    v0 = 2;
    if (cc) {
        // 0x0055e178
        charge(ctx, 1);
        ld(s0, sp, 0x0);
        // 0x0055e17c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0055e0e8
    charge(ctx, 3);
    lb(s2, s0, 1);
    if (s2 != v0) {
        ld(s0, sp, 0x0);
        // 0x0055e17c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0055e0f4
    charge(ctx, 3);
    lw(v0, s0, 36);
    if (i64(v0) <= 0) {
        ld(s0, sp, 0x0);
        // 0x0055e17c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0055e100
    charge(ctx, 7);
    lw(a1, s0, 32);
    s1 = addiu(s0, 16);
    v0 = sll(a1, 5);
    v0 = addu(v0, s1);
    lw(v1, v0, 64);
    v0 = sll(a1, 5);
    if (v1 == a2) {
        // 0x0055e11c
        charge(ctx, 4);
        jal(ctx, 0x55E11Cu, gen::fn_sub_55DEF0_0055def0);
        lw(a1, s0, 32);
        v0 = sll(a1, 5);
    }
    // 0x0055e12c
    charge(ctx, 4);
    v0 = addu(v0, s1);
    lw(v1, v0, 64);
    v0 = sll(a1, 5);
    if (v1 == s2) {
        // 0x0055e13c
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x55E13Cu, gen::fn_sub_55DFB8_0055dfb8);
        lw(a1, s0, 32);
        v0 = sll(a1, 5);
    }
    // 0x0055e14c
    charge(ctx, 4);
    v0 = addu(v0, s1);
    lw(v1, v0, 64);
    if (v1 != 0) {
        ld(s0, sp, 0x0);
        // 0x0055e17c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0055e15c
    charge(ctx, 7);
    a0 = s0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_55DDC8_0055ddc8(ctx);  // tail call
}

// 0x0055E190 sub_55E190 -- 20 bytes; frame 0x10: ra sp+0x0
// Enter the CRI critical section.
void sub_55E190(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e190
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564978_00564978(ctx);  // tail call
}

// 0x0055E1A8 sub_55E1A8 -- 20 bytes; frame 0x10: ra sp+0x0
// Leave the CRI critical section.
void sub_55E1A8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e1a8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564990_00564990(ctx);  // tail call
}

// 0x0055E1C0 sub_55E1C0 -- 24 bytes; leaf frame (no stack)
// Returns the CVFS-style interface table 0x7A79B0.
void sub_55E1C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0055e1c0
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    v0 = 0x7A0000;
    v1 = addiu(v1, 31136);  // &0x7A79A0
    v0 = addiu(v0, 31152);  // &0x7A79B0
    lw(a0, v1, 0);  // 0x7A79A0
}

// 0x0055E1D8 sub_55E1D8 -- 48 bytes; frame 0x10: ra sp+0x0
// The file-system error callback (0x7A79A4) with its object and the text.
void sub_55E1D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0055e1d8
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, 31140);  // 0x7A79A4
    a2 = a0;
    sd(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x0055e1f0
        charge(ctx, 3);
        v0 = 0x7A0000;
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x55E1F4u);  // $ra = the return address
        lw(a0, v0, 31144);
        call_ptr(ctx, jt);
    }
    // 0x0055e1fc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055E220 sub_55E220 -- 248 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// Parses a 17-byte "XXXXXXXX.YYYYYYYY" name into two hex numbers (strtol base 16): the first returned, the second in
// *$a1.
void sub_55E220(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e220
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x28);
    s2 = a1;
    jal(ctx, 0x55E238u, gen::fn_strlen_00524388);
    v1 = 0x7B0000;
    a1 = 0x7C0000;
    s0 = addiu(v1, -32040);  // &0x7A82D8
    v1 = 17;
    a1 = addiu(a1, 23008);  // "E01100308:length of '%s' is not 17 bytes.(mfci_get_adr_size)"
    a2 = s1;
    a0 = s0;
    if (v0 != v1) {
        // 0x0055e260
        charge(ctx, 5);
        jal(ctx, 0x55E260u, gen::fn_sprintf_00523ac8);
        a1 = s0;
        a0 = 0;
        jal(ctx, 0x55E26Cu, gen::fn_sub_55E1D8_0055e1d8);
    }
    // 0x0055e274
    charge(ctx, 4);
    lb(v1, s1, 8);
    v0 = 46;
    s0 = 0x7B0000;
    if (v1 != v0) {
        // 0x0055e284
        charge(ctx, 9);
        a1 = 0x7C0000;
        s0 = addiu(s0, -32040);
        a1 = addiu(a1, 23072);  // "E01100309:illegal file name format '%s'(mfci_get_adr_size)"
        a0 = s0;
        a2 = s1;
        jal(ctx, 0x55E294u, gen::fn_sprintf_00523ac8);
        a0 = 0;
        a1 = s0;
        jal(ctx, 0x55E2A0u, gen::fn_sub_55E1D8_0055e1d8);
    }
    // 0x0055e2a8
    charge(ctx, 13);
    a1 = sp;
    a2 = 16;
    a0 = s1;
    link(ctx, 0x55E2B4u);  // $ra first: the delay slot below depends on it
    sw(s1, sp, 0x0);
    call(ctx, gen::fn_sub_55E208_0055e208);
    a2 = 16;
    s0 = dsll32(v0, 0);
    s0 = dsra32(s0, 0);
    lw(v0, sp, 0x0);
    a1 = sp;
    lb(v1, v0, 0);
    v0 = addiu(v0, 1);
    if (v1 != 0) {
        // 0x0055e2dc
        charge(ctx, 1);
        sw(v0, sp, 0x0);
    }
    // 0x0055e2e0
    charge(ctx, 2);
    v0 = s0;
    if (s2 != 0) {
        // 0x0055e2e8
        charge(ctx, 6);
        link(ctx, 0x55E2E8u);  // $ra first: the delay slot below depends on it
        lw(a0, sp, 0x0);
        call(ctx, gen::fn_sub_55E208_0055e208);
        v0 = dsll32(v0, 0);
        v0 = dsra32(v0, 0);
        sw(v0, s2, 0);
        v0 = s0;
    }
    // 0x0055e300 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0055E320 sub_55E320 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0, s1 sp+0x8
// Server step for each of the 40 handles (56 bytes at 0x7A7A18).
void sub_55E320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e320
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7A0000;
    sd(ra, sp, 0x10);
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 31256);  // &0x7A7A18
    sd(s1, sp, 0x8);
    s1 = 39;
    for (;;) {
        // 0x0055e340
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 == 0) {
            s1 = addiu(s1, -1);
        } else {
            // 0x0055e34c
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x55E34Cu, gen::fn_sub_55E318_0055e318);
            s1 = addiu(s1, -1);
        }
        // 0x0055e358
        charge(ctx, 2);
        s0 = addiu(s0, 56);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0055e360
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0055E378 sub_55E378 -- 20 bytes; leaf frame (no stack)
// Registers the file-system error callback and its object.
void sub_55E378(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0055e378
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    v1 = 0x7A0000;
    sw(a0, v0, 31140);  // 0x7A79A4
    sw(a1, v1, 31144);  // 0x7A79A8
}

// 0x0055E390 sub_55E390 -- 32 bytes; frame 0x20: ra sp+0x10
// The second number of a 17-byte hex name.
void sub_55E390(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e390
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    a1 = sp;
    jal(ctx, 0x55E398u, gen::fn_sub_55E220_0055e220);
    lw(v0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0055E3B0 sub_55E3B0 -- 88 bytes; leaf frame (no stack)
// Returns a free handle of 40 (56 bytes at 0x7A7A18), or 0.
void sub_55E3B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0055e3b0
    enter(ctx, 6);  // entry check point + this block's cycles
    a2 = 0x7A0000;
    a3 = 0;
    v1 = addiu(a2, 31256);  // &0x7A7A18
    lb(v0, v1, 0);  // 0x7A7A18
    a1 = 0;
    if (v0 != 0) {
        // 0x0055e3d0
        charge(ctx, 1);
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x0055e3d4
            charge(ctx, 4);
            v0 = sll(a1, 3);
            v1 = slti(a1, 40);
            v0 = subu(v0, a1);
            if (v1 == 0) {
                break;
            }
            // 0x0055e3e4
            charge(ctx, 6);
            v0 = sll(v0, 3);
            v1 = addiu(a2, 31256);
            v0 = addu(v0, v1);
            lb(a0, v0, 0);
            if (a0 == 0) {
                goto L_0055e3fc_5;
            }
            a1 = addiu(a1, 1);
            backedge(ctx);
        }
    } else {
        // 0x0055e3c8
        charge(ctx, 2);
        a3 = v1;
    }
    // 0x0055e400 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a3;
    return;
L_0055e3fc_5:
    charge(ctx, 1);
    a3 = v0;
    // 0x0055e400 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a3;
}

// 0x0055E428 sub_55E428 -- 108 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Opens a handle on its hex name: sector 2048, size, sector count, open state.
void sub_55E428(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e428
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 2048;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    a0 = addiu(s0, 28);
    link(ctx, 0x55E440u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 4);
    call(ctx, gen::fn_sub_55E390_0055e390);
    lw(v1, s0, 4);
    sw(v0, s0, 8);
    a0 = 1;
    v0 = addu(v0, v1);
    if (v1 == 0) {
        brk(ctx, 0x55E45Cu, 0x7u);
    }
    // 0x0055e460
    charge(ctx, 13);
    v0 = addiu(v0, -1);
    sb(a0, s0, 0);
    div(v0, v1);
    sw(zero, s0, 16);
    sw(zero, s0, 24);
    sw(zero, s0, 20);
    sb(zero, s0, 1);
    ld(ra, sp, 0x8);
    mflo(v0);
    sw(v0, s0, 12);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055E940 sub_55E940 -- 56 bytes; frame 0x10: ra sp+0x0
// Returns a handle's +20; NULL -> error text and 0.
void sub_55E940(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e940
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0055e968
        charge(ctx, 1);
        lw(v0, v0, 20);
    } else {
        // 0x0055e950
        charge(ctx, 5);
        a1 = 0x7C0000;
        a1 = addiu(a1, 23432);  // "E0092912:handl is null."
        jal(ctx, 0x55E954u, gen::fn_sub_55E1D8_0055e1d8);
        v0 = 0;
    }
    // 0x0055e96c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055EA80 sub_55EA80 -- 20 bytes; frame 0x10: ra sp+0x0
// Enter the CRI critical section.
void sub_55EA80(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0055ea80
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564978_00564978(ctx);  // tail call
}

// 0x0055EA98 sub_55EA98 -- 20 bytes; frame 0x10: ra sp+0x0
// Leave the CRI critical section.
void sub_55EA98(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0055ea98
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564990_00564990(ctx);  // tail call
}

// 0x0055EB08 sub_55EB08 -- 48 bytes; frame 0x10: ra sp+0x0
// The error callback (0x7A843C) with its object.
void sub_55EB08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0055eb08
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -31684);  // 0x7A843C
    a1 = a0;
    sd(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x0055eb20
        charge(ctx, 3);
        v0 = 0x7B0000;
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x55EB24u);  // $ra = the return address
        lw(a0, v0, -31680);
        call_ptr(ctx, jt);
    }
    // 0x0055eb2c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055EDB8 sub_55EDB8 -- 64 bytes; leaf frame (no stack)
// Clears two 96-word tables and sets the counters (0, 64).
void sub_55EDB8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x0055edb8
    enter(ctx, 4);  // entry check point + this block's cycles
    a2 = a0;
    a1 = 0;
    lw(t0, a2, 8);
    lw(a3, a2, 12);
    for (;;) {
        // 0x0055edc8
        charge(ctx, 8);
        v0 = sll(a1, 2);
        a1 = addiu(a1, 1);
        a0 = addu(v0, a3);
        v0 = addu(v0, t0);
        v1 = slti(a1, 96);
        sw(zero, v0, 0);
        sw(zero, a0, 0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0055ede8
    charge(ctx, 4);
    v0 = 64;
    sw(zero, a2, 20);
    sw(v0, a2, 24);
}

// 0x0055F1C8 sub_55F1C8 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Runs 0x55F218 inside the critical section.
void sub_55F1C8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055f1c8
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x55F1E4u, gen::fn_sub_55EA80_0055ea80);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x55F1F4u, gen::fn_sub_55F218_0055f218);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_55EA98_0055ea98(ctx);  // tail call
}

// 0x0055F688 sub_55F688 -- 188 bytes; frame 0x10: ra sp+0x0
// Sets the PS2RNA voice configuration: nste stereo + nmono mono channels (2 x nste + nmono <= 32), work size 16640 per
// channel.
void sub_55F688(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055f688
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t2 = a0;
    sd(ra, sp, 0x0);
    t3 = a1;
    if (i64(t2) < 0) {
        // 0x0055f69c
        charge(ctx, 6);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a1 = t2;
        a0 = addiu(a0, 25240);  // "PS2RNA_SetupVoice:Illigal parameter(nste=%d)."
        sp = addiu(sp, 0x10);
        gen::fn_sub_541760_00541760(ctx);  // tail call
        return;
    }
    // 0x0055f6b8
    charge(ctx, 2);
    v0 = sll(t2, 1);
    if (i64(t3) < 0) {
        // 0x0055f6c0
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 25288);  // "PS2RNA_SetupVoice:Illigal parameter(nmono=%d)."
        sp = addiu(sp, 0x10);
        gen::fn_sub_541760_00541760(ctx);  // tail call
        return;
    }
    // 0x0055f6d8
    charge(ctx, 5);
    t1 = addu(v0, t3);
    v1 = sll(t1, 6);
    v0 = slti(t1, 33);
    v1 = addu(v1, t1);
    if (v0 == 0) {
        // 0x0055f6ec
        charge(ctx, 6);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a1 = 32;
        a0 = addiu(a0, 25336);  // "PS2RNA_SetupVoice:The set-up value exceeded maximum(MAX=%d)."
        sp = addiu(sp, 0x10);
        gen::fn_sub_541760_00541760(ctx);  // tail call
        return;
    }
    // 0x0055f708
    charge(ctx, 15);
    ld(ra, sp, 0x0);
    a3 = sll(v1, 8);
    t0 = 0x7B0000;
    a0 = 0x7B0000;
    v1 = 0x7B0000;
    a1 = 0x7B0000;
    a2 = 0x7B0000;
    v0 = 1;
    sw(t2, v1, -27624);  // 0x7A9418
    sw(t3, a0, -27620);  // 0x7A941C
    sw(a3, a1, -27660);  // 0x7A93F4
    sw(v0, a2, -27656);  // 0x7A93F8
    sw(t1, t0, -27664);  // 0x7A93F0
    sp = addiu(sp, 0x10);
}

// 0x0055FB20 sub_55FB20 -- 116 bytes; leaf frame (no stack)
// PS2RNA: claims a free channel record (24 bytes at 0x7A9450) among the configured count; 0 when full.
void sub_55FB20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055fb20
    enter(ctx, 5);  // entry check point + this block's cycles
    t0 = 0x7B0000;
    a2 = 0;
    lw(a1, t0, -27664);  // 0x7A93F0
    a0 = 0;
    if (i64(a1) > 0) {
        // 0x0055fb34
        charge(ctx, 5);
        v0 = 0x7B0000;
        a0 = addiu(v0, -27568);  // &0x7A9450
        lb(v1, a0, 0);  // 0x7A9450
        cc = v1 == 0;  // the condition, before the delay slot changes it
        v1 = a0;
        if (!cc) {
            // 0x0055fb48
            charge(ctx, 2);
            a3 = a1;
            a1 = a0;
            for (;;) {
                // 0x0055fb50
                charge(ctx, 5);
                a2 = addiu(a2, 1);
                a1 = addiu(a1, 24);
                v0 = slt(a2, a3);
                v1 = addiu(v1, 24);
                if (v0 != 0) {
                    // 0x0055fb64
                    charge(ctx, 4);
                    lb(v0, a1, 0);
                    a0 = v1;
                    if (v0 != 0) {
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
        }
    }
    // 0x0055fb74
    charge(ctx, 3);
    lw(v1, t0, -27664);
    v0 = 0;
    if (a2 != v1) {
        // 0x0055fb80
        charge(ctx, 3);
        v1 = 1;
        v0 = a0;
        sb(v1, a0, 0);
    }
    // 0x0055fb8c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0055FB98 sub_55FB98 -- 8 bytes; leaf frame (no stack)
// PS2RNA: frees a channel record (byte 0).
void sub_55FB98(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x0055fb98
    enter(ctx, 2);  // entry check point + this block's cycles
    sb(zero, a0, 0);
}

// 0x0055FBA0 sub_55FBA0 -- 92 bytes; leaf frame (no stack)
// A delay loop of *$a1 - 1 iterations (spins forever on NULL).
void sub_55FBA0(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5};
    // 0x0055fba0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a1 == 0) {
        for (;;) {
            // 0x0055fba8
            charge(ctx, 7);
            backedge(ctx);
        }
    }
    lw(a1, a1, 0);
    // 0x0055fbc8
    charge(ctx, 2);
    if (i64(a1) > 0) {
        // 0x0055fbd0
        charge(ctx, 2);
        a1 = addiu(a1, -1);
        for (;;) {
            // 0x0055fbd8
            charge(ctx, 7);
            if (a1 == 0) {
                break;
            }
            a1 = addiu(a1, -1);
            backedge(ctx);
        }
    }
    // 0x0055fbf4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0055FC00 sub_55FC00 -- 876 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18
// PS2RNA: builds the IOP command list (16-byte commands, at most 128) from the changed parameters of each of the 16
// live channels.
void sub_55FC00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055fc00
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7B0000;
    sd(s1, sp, 0x8);
    s1 = a1;
    t7 = addiu(s1, 16);
    v1 = 0x7B0000;
    a0 = 0x7B0000;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    s2 = addiu(a0, -31664);  // &0x7A8450
    sd(s3, sp, 0x18);
    s3 = addiu(v1, -27612);  // &0x7A9424
    a3 = addiu(v0, -18352);  // &0x7AB850
    t2 = 0;
    t8 = 0;
    s0 = 1;
    t9 = 2;
    a2 = t7;
    for (;;) {
        // 0x0055fc48
        charge(ctx, 3);
        lb(v0, a3, 0);
        if (v0 != s0) {
            t8 = addiu(t8, 1);
        } else {
            // 0x0055fc54
            charge(ctx, 3);
            t0 = 128;
            v1 = 0x7B0000;
            if (t2 == t0) {
                goto L_0055ff50;
            }
            // 0x0055fc60
            charge(ctx, 5);
            lw(a0, s3, 0);
            v1 = addiu(v1, -27608);
            lw(v0, v1, 0);
            cc = a0 == v0;  // the condition, before the delay slot changes it
            v0 = 11;
            if (!cc) {
                // 0x0055fc74
                charge(ctx, 6);
                sw(zero, a2, 4);
                sh(v0, a2, 0);
                t2 = addiu(t2, 1);
                sw(a0, a2, 8);
                a2 = addiu(a2, 16);
                sw(a0, v1, 0);
            }
            // 0x0055fc8c
            charge(ctx, 2);
            if (t2 == t0) {
                sw(t2, s1, 0);
            } else {
                // 0x0055fc94
                charge(ctx, 4);
                lb(v1, a3, 91);
                lb(v0, a3, 90);
                cc = v1 == v0;  // the condition, before the delay slot changes it
                v0 = 8;
                if (!cc) {
                    // 0x0055fca4
                    charge(ctx, 9);
                    lw(v1, a3, 32);
                    sh(v0, a2, 0);
                    t2 = addiu(t2, 1);
                    sw(v1, a2, 4);
                    lb(v0, a3, 91);
                    sw(v0, a2, 8);
                    a2 = addiu(a2, 16);
                    lbu(v0, a3, 91);
                    sb(v0, a3, 90);
                }
                // 0x0055fcc8
                charge(ctx, 2);
                v0 = 256;
                if (t2 == t0) {
                    goto L_0055ff50;
                }
                // 0x0055fcd0
                charge(ctx, 3);
                lhu(v1, a3, 80);
                if (v1 == v0) {
                    // 0x0055fcdc
                    charge(ctx, 9);
                    lw(v0, a3, 32);
                    t2 = addiu(t2, 1);
                    sh(t9, a2, 0);
                    sw(v0, a2, 4);
                    lb(v1, a3, 80);
                    sw(v1, a2, 8);
                    a2 = addiu(a2, 16);
                    lbu(v0, a3, 80);
                    sb(v0, a3, 81);
                }
                // 0x0055fd00
                charge(ctx, 2);
                if (t2 == t0) {
                    sw(t2, s1, 0);
                } else {
                    // 0x0055fd08
                    charge(ctx, 4);
                    lb(v1, a3, 84);
                    lb(v0, a3, 85);
                    cc = v1 == v0;  // the condition, before the delay slot changes it
                    v0 = 10;
                    if (!cc) {
                        // 0x0055fd18
                        charge(ctx, 9);
                        lw(v1, a3, 32);
                        sh(v0, a2, 0);
                        t2 = addiu(t2, 1);
                        sw(v1, a2, 4);
                        lb(v0, a3, 84);
                        sw(v0, a2, 8);
                        a2 = addiu(a2, 16);
                        lbu(v0, a3, 84);
                        sb(v0, a3, 85);
                    }
                    // 0x0055fd3c
                    charge(ctx, 2);
                    if (t2 == t0) {
                        sw(t2, s1, 0);
                    } else {
                        // 0x0055fd44
                        charge(ctx, 4);
                        lb(v1, a3, 86);
                        lb(v0, a3, 87);
                        cc = v1 == v0;  // the condition, before the delay slot changes it
                        v0 = 12;
                        if (!cc) {
                            // 0x0055fd54
                            charge(ctx, 9);
                            lw(v1, a3, 32);
                            sh(v0, a2, 0);
                            t2 = addiu(t2, 1);
                            sw(v1, a2, 4);
                            lb(v0, a3, 86);
                            sw(v0, a2, 8);
                            a2 = addiu(a2, 16);
                            lbu(v0, a3, 86);
                            sb(v0, a3, 87);
                        }
                        // 0x0055fd78
                        charge(ctx, 2);
                        if (t2 == t0) {
                            sw(t2, s1, 0);
                        } else {
                            // 0x0055fd80
                            charge(ctx, 4);
                            lb(v1, a3, 82);
                            lb(v0, a3, 83);
                            cc = v1 == v0;  // the condition, before the delay slot changes it
                            v0 = 3;
                            if (!cc) {
                                // 0x0055fd90
                                charge(ctx, 9);
                                lw(v1, a3, 32);
                                sh(v0, a2, 0);
                                t2 = addiu(t2, 1);
                                sw(v1, a2, 4);
                                lb(v0, a3, 82);
                                sw(v0, a2, 8);
                                a2 = addiu(a2, 16);
                                lbu(v0, a3, 82);
                                sb(v0, a3, 83);
                            }
                            // 0x0055fdb4
                            charge(ctx, 2);
                            if (t2 == t0) {
                                sw(t2, s1, 0);
                            } else {
                                // 0x0055fdbc
                                charge(ctx, 4);
                                lw(v1, a3, 48);
                                lw(v0, a3, 52);
                                cc = v1 == v0;  // the condition, before the delay slot changes it
                                v0 = 4;
                                if (!cc) {
                                    // 0x0055fdcc
                                    charge(ctx, 8);
                                    sw(v1, a2, 8);
                                    lw(a0, a3, 32);
                                    t2 = addiu(t2, 1);
                                    lw(v1, a3, 48);
                                    sh(v0, a2, 0);
                                    sw(v1, a3, 52);
                                    sw(a0, a2, 4);
                                    a2 = addiu(a2, 16);
                                }
                                // 0x0055fdec
                                charge(ctx, 2);
                                if (t2 == t0) {
                                    sw(t2, s1, 0);
                                } else {
                                    // 0x0055fdf4
                                    charge(ctx, 4);
                                    lw(v1, a3, 56);
                                    lw(v0, a3, 60);
                                    cc = v1 == v0;  // the condition, before the delay slot changes it
                                    v0 = sll(v1, 2);
                                    if (!cc) {
                                        // 0x0055fe04
                                        charge(ctx, 12);
                                        lw(a1, a3, 32);
                                        v0 = subu(s2, v0);
                                        a0 = 5;
                                        lw(v1, v0, 0);
                                        t2 = addiu(t2, 1);
                                        sw(zero, a2, 8);
                                        sw(v1, a2, 12);
                                        sh(a0, a2, 0);
                                        lw(v0, a3, 56);
                                        sw(a1, a2, 4);
                                        a2 = addiu(a2, 16);
                                        sw(v0, a3, 60);
                                    }
                                    // 0x0055fe34
                                    charge(ctx, 2);
                                    v0 = 127;
                                    if (t2 == t0) {
                                        goto L_0055ff50;
                                    }
                                    // 0x0055fe3c
                                    charge(ctx, 2);
                                    if (t2 == v0) {
                                        sw(t2, s1, 0);
                                    } else {
                                        // 0x0055fe44
                                        charge(ctx, 4);
                                        lb(v0, a3, 82);
                                        t4 = 0;
                                        lbu(t1, a3, 82);
                                        if (i64(v0) > 0) {
                                            // 0x0055fe54
                                            charge(ctx, 7);
                                            v0 = sll(t2, 4);
                                            t5 = addiu(a3, 8);
                                            a0 = addu(v0, t7);
                                            t6 = 9;
                                            t3 = 64;
                                            a1 = addu(a3, t3);
                                            for (;;) {
                                                // 0x0055fe70
                                                charge(ctx, 5);
                                                t0 = addu(t5, t3);
                                                lw(v1, a1, 0);
                                                lw(v0, t0, 0);
                                                t3 = addiu(t3, 4);
                                                if (v1 != v0) {
                                                    // 0x0055fe84
                                                    charge(ctx, 12);
                                                    sw(t4, a0, 8);
                                                    a2 = addiu(a2, 16);
                                                    lw(v1, a3, 32);
                                                    t2 = addiu(t2, 1);
                                                    lw(v0, a1, 0);
                                                    sh(t6, a0, 0);
                                                    sw(v0, a0, 12);
                                                    sw(v1, a0, 4);
                                                    a0 = addiu(a0, 16);
                                                    lw(v0, a1, 0);
                                                    sw(v0, t0, 0);
                                                    lbu(t1, a3, 82);
                                                }
                                                // 0x0055feb4
                                                charge(ctx, 6);
                                                v0 = sll(t1, 24);
                                                t4 = addiu(t4, 1);
                                                v0 = sra(v0, 24);
                                                v0 = slt(t4, v0);
                                                a1 = addu(a3, t3);
                                                if (v0 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                        }
                                        // 0x0055fecc
                                        charge(ctx, 4);
                                        lw(v1, a3, 92);
                                        lw(v0, a3, 96);
                                        cc = v1 == v0;  // the condition, before the delay slot changes it
                                        v0 = 13;
                                        if (!cc) {
                                            // 0x0055fedc
                                            charge(ctx, 8);
                                            sw(v1, a2, 8);
                                            lw(a0, a3, 32);
                                            t2 = addiu(t2, 1);
                                            lw(v1, a3, 92);
                                            sh(v0, a2, 0);
                                            sw(v1, a3, 96);
                                            sw(a0, a2, 4);
                                            a2 = addiu(a2, 16);
                                        }
                                        // 0x0055fefc
                                        charge(ctx, 3);
                                        a0 = 128;
                                        if (t2 == a0) {
                                            sw(t2, s1, 0);
                                        } else {
                                            // 0x0055ff08
                                            charge(ctx, 3);
                                            lhu(v0, a3, 80);
                                            if (v0 == s0) {
                                                // 0x0055ff14
                                                charge(ctx, 9);
                                                lw(v0, a3, 32);
                                                t2 = addiu(t2, 1);
                                                sh(t9, a2, 0);
                                                sw(v0, a2, 4);
                                                lb(v1, a3, 80);
                                                sw(v1, a2, 8);
                                                a2 = addiu(a2, 16);
                                                lbu(v0, a3, 80);
                                                sb(v0, a3, 81);
                                            }
                                            // 0x0055ff38
                                            charge(ctx, 2);
                                            if (t2 != a0) {
                                                // 0x0055ff40
                                                charge(ctx, 1);
                                                t8 = addiu(t8, 1);
                                                goto L_0055ff44;
                                            }
                                            sw(t2, s1, 0);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
        }
    L_0055ff44:
        charge(ctx, 3);
        v0 = slti(t8, 16);
        a3 = addiu(a3, 100);
        if (v0 == 0) {
            goto L_0055ff50;
        }
        backedge(ctx);
    }
    // 0x0055ff54 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    sp = addiu(sp, 0x20);
    return;
L_0055ff50:
    charge(ctx, 1);
    sw(t2, s1, 0);
    // 0x0055ff54 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
