// Slice libs7: 140 functions of the CRI ADX middleware (0x535A88..0x53FFF8), in six groups (the banners below):
// ADXB's PCM-container decoders, the ADX keys and decode steps, the error callback, ADXF (the ADX file layer), the
// ADX header encode / decode, and the ADXT file entry with the ADXM server threads.
// Made by p3fes_handgen from SLUS_216.21 and symbols/: every body keeps the recompiled body's registers, frame, spills,
// $ra links, cycle charges and check points (game/include/p3fes/game/hg_cpu.h). On top: a role comment per function,
// proposed names from the binary's own error texts, and the ADXF handle's named offsets (libs7.h, adxf::). The pair
// tests are tests/game/test_libs7.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs7.h"

namespace p3fes::recomp_gen {
void fn_ADXT_UpdateFsStat_0053e0b8(p3fes::EEContext&);
void fn_InvalidDCache_00503b98(p3fes::EEContext&);
void fn___env_lock_0053b598(p3fes::EEContext&);
void fn___env_unlock_0053b5a0(p3fes::EEContext&);
void fn___errno_00540550(p3fes::EEContext&);
void fn__sceChangeThreadPriority_00502ff0(p3fes::EEContext&);
void fn__sceExitDeleteThread_00502fa0(p3fes::EEContext&);
void fn__sceiReferThreadStatus_00503070(p3fes::EEContext&);
void fn_adxf_AddRofsVol_0053b318(p3fes::EEContext&);
void fn_adxf_ExecOne_0053d640(p3fes::EEContext&);
void fn_adxf_GetFsizeSct_0053d9a0(p3fes::EEContext&);
void fn_adxf_GetStat_0053dbc8(p3fes::EEContext&);
void fn_adxf_LoadPartitionNw_0053b8d0(p3fes::EEContext&);
void fn_adxf_ReadNw32_0053d1f0(p3fes::EEContext&);
void fn_adxf_SetDefDev_0053b528(p3fes::EEContext&);
void fn_adxf_SetFileInfoEx_0053c860(p3fes::EEContext&);
void fn_adxf_SetReqRdSct_0053df90(p3fes::EEContext&);
void fn_adxf_SetupRofs_0053b250(p3fes::EEContext&);
void fn_adxm_goto_svr_border_0053f9b0(p3fes::EEContext&);
void fn_adxm_mwidle_proc_0053fde8(p3fes::EEContext&);
void fn_adxm_vsync_proc_0053fbf0(p3fes::EEContext&);
void fn_adxt_ExecFsSvr_0053e0e0(p3fes::EEContext&);
void fn_cvFsAddDev_00555b10(p3fes::EEContext&);
void fn_cvFsAddVolumeEx_00557358(p3fes::EEContext&);
void fn_cvFsClose_00556398(p3fes::EEContext&);
void fn_cvFsOpen_00556048(p3fes::EEContext&);
void fn_cvFsSetDefVol_005575f0(p3fes::EEContext&);
void fn_iWakeupThread_00504028(p3fes::EEContext&);
void fn_memcmp_005211b8(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sceInsockSetsockopt_2_0054a928(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncpy_00524828(p3fes::EEContext&);
void fn_sub_535A88_00535a88(p3fes::EEContext&);
void fn_sub_535D18_00535d18(p3fes::EEContext&);
void fn_sub_535E58_00535e58(p3fes::EEContext&);
void fn_sub_535F38_00535f38(p3fes::EEContext&);
void fn_sub_536058_00536058(p3fes::EEContext&);
void fn_sub_5360B0_005360b0(p3fes::EEContext&);
void fn_sub_536440_00536440(p3fes::EEContext&);
void fn_sub_5364A8_005364a8(p3fes::EEContext&);
void fn_sub_5365B8_005365b8(p3fes::EEContext&);
void fn_sub_5366D0_005366d0(p3fes::EEContext&);
void fn_sub_536868_00536868(p3fes::EEContext&);
void fn_sub_5369E8_005369e8(p3fes::EEContext&);
void fn_sub_536A10_00536a10(p3fes::EEContext&);
void fn_sub_536D28_00536d28(p3fes::EEContext&);
void fn_sub_536D80_00536d80(p3fes::EEContext&);
void fn_sub_536E90_00536e90(p3fes::EEContext&);
void fn_sub_536F90_00536f90(p3fes::EEContext&);
void fn_sub_537128_00537128(p3fes::EEContext&);
void fn_sub_5372A8_005372a8(p3fes::EEContext&);
void fn_sub_537450_00537450(p3fes::EEContext&);
void fn_sub_5374E8_005374e8(p3fes::EEContext&);
void fn_sub_537508_00537508(p3fes::EEContext&);
void fn_sub_537528_00537528(p3fes::EEContext&);
void fn_sub_537808_00537808(p3fes::EEContext&);
void fn_sub_537838_00537838(p3fes::EEContext&);
void fn_sub_537858_00537858(p3fes::EEContext&);
void fn_sub_5379F8_005379f8(p3fes::EEContext&);
void fn_sub_537F70_00537f70(p3fes::EEContext&);
void fn_sub_537FE0_00537fe0(p3fes::EEContext&);
void fn_sub_537FF0_00537ff0(p3fes::EEContext&);
void fn_sub_537FF8_00537ff8(p3fes::EEContext&);
void fn_sub_538058_00538058(p3fes::EEContext&);
void fn_sub_5380A0_005380a0(p3fes::EEContext&);
void fn_sub_5380E0_005380e0(p3fes::EEContext&);
void fn_sub_538148_00538148(p3fes::EEContext&);
void fn_sub_5381C0_005381c0(p3fes::EEContext&);
void fn_sub_538410_00538410(p3fes::EEContext&);
void fn_sub_538460_00538460(p3fes::EEContext&);
void fn_sub_5384B8_005384b8(p3fes::EEContext&);
void fn_sub_538510_00538510(p3fes::EEContext&);
void fn_sub_538618_00538618(p3fes::EEContext&);
void fn_sub_538648_00538648(p3fes::EEContext&);
void fn_sub_5386B8_005386b8(p3fes::EEContext&);
void fn_sub_5386D8_005386d8(p3fes::EEContext&);
void fn_sub_538860_00538860(p3fes::EEContext&);
void fn_sub_538B60_00538b60(p3fes::EEContext&);
void fn_sub_538C80_00538c80(p3fes::EEContext&);
void fn_sub_538D78_00538d78(p3fes::EEContext&);
void fn_sub_539248_00539248(p3fes::EEContext&);
void fn_sub_5393C0_005393c0(p3fes::EEContext&);
void fn_sub_539558_00539558(p3fes::EEContext&);
void fn_sub_539760_00539760(p3fes::EEContext&);
void fn_sub_539818_00539818(p3fes::EEContext&);
void fn_sub_539830_00539830(p3fes::EEContext&);
void fn_sub_539848_00539848(p3fes::EEContext&);
void fn_sub_539850_00539850(p3fes::EEContext&);
void fn_sub_539AE0_00539ae0(p3fes::EEContext&);
void fn_sub_539BE0_00539be0(p3fes::EEContext&);
void fn_sub_539C60_00539c60(p3fes::EEContext&);
void fn_sub_539CD8_00539cd8(p3fes::EEContext&);
void fn_sub_539ED8_00539ed8(p3fes::EEContext&);
void fn_sub_53A138_0053a138(p3fes::EEContext&);
void fn_sub_53AD70_0053ad70(p3fes::EEContext&);
void fn_sub_53ADA8_0053ada8(p3fes::EEContext&);
void fn_sub_53ADE0_0053ade0(p3fes::EEContext&);
void fn_sub_53AE08_0053ae08(p3fes::EEContext&);
void fn_sub_53AE60_0053ae60(p3fes::EEContext&);
void fn_sub_53AED0_0053aed0(p3fes::EEContext&);
void fn_sub_53AFD8_0053afd8(p3fes::EEContext&);
void fn_sub_53B060_0053b060(p3fes::EEContext&);
void fn_sub_53B080_0053b080(p3fes::EEContext&);
void fn_sub_53B158_0053b158(p3fes::EEContext&);
void fn_sub_53B2A0_0053b2a0(p3fes::EEContext&);
void fn_sub_53B408_0053b408(p3fes::EEContext&);
void fn_sub_53B4A0_0053b4a0(p3fes::EEContext&);
void fn_sub_53B5A8_0053b5a8(p3fes::EEContext&);
void fn_sub_53B5D0_0053b5d0(p3fes::EEContext&);
void fn_sub_53B680_0053b680(p3fes::EEContext&);
void fn_sub_53B6B0_0053b6b0(p3fes::EEContext&);
void fn_sub_53BD10_0053bd10(p3fes::EEContext&);
void fn_sub_53BDD8_0053bdd8(p3fes::EEContext&);
void fn_sub_53BEB0_0053beb0(p3fes::EEContext&);
void fn_sub_53BEF0_0053bef0(p3fes::EEContext&);
void fn_sub_53C198_0053c198(p3fes::EEContext&);
void fn_sub_53C268_0053c268(p3fes::EEContext&);
void fn_sub_53C2A0_0053c2a0(p3fes::EEContext&);
void fn_sub_53C758_0053c758(p3fes::EEContext&);
void fn_sub_53C770_0053c770(p3fes::EEContext&);
void fn_sub_53C7C8_0053c7c8(p3fes::EEContext&);
void fn_sub_53C9F8_0053c9f8(p3fes::EEContext&);
void fn_sub_53CAE0_0053cae0(p3fes::EEContext&);
void fn_sub_53CBA0_0053cba0(p3fes::EEContext&);
void fn_sub_53CCC0_0053ccc0(p3fes::EEContext&);
void fn_sub_53CD60_0053cd60(p3fes::EEContext&);
void fn_sub_53CDD0_0053cdd0(p3fes::EEContext&);
void fn_sub_53CE00_0053ce00(p3fes::EEContext&);
void fn_sub_53CEB8_0053ceb8(p3fes::EEContext&);
void fn_sub_53CEE0_0053cee0(p3fes::EEContext&);
void fn_sub_53CF40_0053cf40(p3fes::EEContext&);
void fn_sub_53D098_0053d098(p3fes::EEContext&);
void fn_sub_53D180_0053d180(p3fes::EEContext&);
void fn_sub_53D450_0053d450(p3fes::EEContext&);
void fn_sub_53D578_0053d578(p3fes::EEContext&);
void fn_sub_53D7E8_0053d7e8(p3fes::EEContext&);
void fn_sub_53D938_0053d938(p3fes::EEContext&);
void fn_sub_53DA18_0053da18(p3fes::EEContext&);
void fn_sub_53DAD8_0053dad8(p3fes::EEContext&);
void fn_sub_53DB60_0053db60(p3fes::EEContext&);
void fn_sub_53DBF8_0053dbf8(p3fes::EEContext&);
void fn_sub_53DCE8_0053dce8(p3fes::EEContext&);
void fn_sub_53DD10_0053dd10(p3fes::EEContext&);
void fn_sub_53DD98_0053dd98(p3fes::EEContext&);
void fn_sub_53DEF0_0053def0(p3fes::EEContext&);
void fn_sub_53DF28_0053df28(p3fes::EEContext&);
void fn_sub_53E000_0053e000(p3fes::EEContext&);
void fn_sub_53E070_0053e070(p3fes::EEContext&);
void fn_sub_53E088_0053e088(p3fes::EEContext&);
void fn_sub_53E0A0_0053e0a0(p3fes::EEContext&);
void fn_sub_53E1B8_0053e1b8(p3fes::EEContext&);
void fn_sub_53E208_0053e208(p3fes::EEContext&);
void fn_sub_53E220_0053e220(p3fes::EEContext&);
void fn_sub_53E250_0053e250(p3fes::EEContext&);
void fn_sub_53E290_0053e290(p3fes::EEContext&);
void fn_sub_53E350_0053e350(p3fes::EEContext&);
void fn_sub_53E370_0053e370(p3fes::EEContext&);
void fn_sub_53E460_0053e460(p3fes::EEContext&);
void fn_sub_53E520_0053e520(p3fes::EEContext&);
void fn_sub_53E6D8_0053e6d8(p3fes::EEContext&);
void fn_sub_53E9D8_0053e9d8(p3fes::EEContext&);
void fn_sub_53E9F0_0053e9f0(p3fes::EEContext&);
void fn_sub_53F080_0053f080(p3fes::EEContext&);
void fn_sub_53F178_0053f178(p3fes::EEContext&);
void fn_sub_53F5F0_0053f5f0(p3fes::EEContext&);
void fn_sub_53F618_0053f618(p3fes::EEContext&);
void fn_sub_53F630_0053f630(p3fes::EEContext&);
void fn_sub_53F640_0053f640(p3fes::EEContext&);
void fn_sub_53F6D0_0053f6d0(p3fes::EEContext&);
void fn_sub_53F768_0053f768(p3fes::EEContext&);
void fn_sub_53F880_0053f880(p3fes::EEContext&);
void fn_sub_53FA98_0053fa98(p3fes::EEContext&);
void fn_sub_53FFF8_0053fff8(p3fes::EEContext&);
void fn_sub_540048_00540048(p3fes::EEContext&);
void fn_sub_540098_00540098(p3fes::EEContext&);
void fn_sub_5400B0_005400b0(p3fes::EEContext&);
void fn_sub_540118_00540118(p3fes::EEContext&);
void fn_sub_540560_00540560(p3fes::EEContext&);
void fn_sub_540F60_00540f60(p3fes::EEContext&);
void fn_sub_541510_00541510(p3fes::EEContext&);
void fn_sub_545FC8_00545fc8(p3fes::EEContext&);
void fn_sub_546058_00546058(p3fes::EEContext&);
void fn_sub_5461C8_005461c8(p3fes::EEContext&);
void fn_sub_5462E0_005462e0(p3fes::EEContext&);
void fn_sub_546368_00546368(p3fes::EEContext&);
void fn_sub_5463A8_005463a8(p3fes::EEContext&);
void fn_sub_546410_00546410(p3fes::EEContext&);
void fn_sub_546510_00546510(p3fes::EEContext&);
void fn_sub_5465A0_005465a0(p3fes::EEContext&);
void fn_sub_546638_00546638(p3fes::EEContext&);
void fn_sub_546718_00546718(p3fes::EEContext&);
void fn_sub_547008_00547008(p3fes::EEContext&);
void fn_sub_547068_00547068(p3fes::EEContext&);
void fn_sub_5470A8_005470a8(p3fes::EEContext&);
void fn_sub_5470E8_005470e8(p3fes::EEContext&);
void fn_sub_547138_00547138(p3fes::EEContext&);
void fn_sub_547318_00547318(p3fes::EEContext&);
void fn_sub_547558_00547558(p3fes::EEContext&);
void fn_sub_547598_00547598(p3fes::EEContext&);
void fn_sub_548318_00548318(p3fes::EEContext&);
void fn_sub_5485A8_005485a8(p3fes::EEContext&);
void fn_sub_54CC98_0054cc98(p3fes::EEContext&);
void fn_sub_54CCC0_0054ccc0(p3fes::EEContext&);
void fn_sub_54CD10_0054cd10(p3fes::EEContext&);
void fn_sub_54CD80_0054cd80(p3fes::EEContext&);
void fn_sub_54CD88_0054cd88(p3fes::EEContext&);
void fn_sub_54CDB8_0054cdb8(p3fes::EEContext&);
void fn_sub_54CDE8_0054cde8(p3fes::EEContext&);
void fn_sub_54CE60_0054ce60(p3fes::EEContext&);
void fn_sub_54CE78_0054ce78(p3fes::EEContext&);
void fn_sub_54CE90_0054ce90(p3fes::EEContext&);
void fn_sub_555D70_00555d70(p3fes::EEContext&);
void fn_sub_555E48_00555e48(p3fes::EEContext&);
void fn_sub_557460_00557460(p3fes::EEContext&);
void fn_sub_557520_00557520(p3fes::EEContext&);
void fn_sub_55D428_0055d428(p3fes::EEContext&);
void fn_sub_55D600_0055d600(p3fes::EEContext&);
void fn_sub_55D730_0055d730(p3fes::EEContext&);
void fn_sub_55DA48_0055da48(p3fes::EEContext&);
void fn_sub_562388_00562388(p3fes::EEContext&);
void fn_sub_564B50_00564b50(p3fes::EEContext&);
void fn_sub_5651F0_005651f0(p3fes::EEContext&);
void fn_sub_5653C0_005653c0(p3fes::EEContext&);
void fn_sub_5653D8_005653d8(p3fes::EEContext&);
void fn_sub_5653F0_005653f0(p3fes::EEContext&);
void fn_sub_565408_00565408(p3fes::EEContext&);
void fn_sub_565438_00565438(p3fes::EEContext&);
void fn_sub_565450_00565450(p3fes::EEContext&);
void fn_sub_565468_00565468(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// =====================================================================================================================
// ADXB: PCM-container decoders (AIFF, Sun .snd, a third little-endian form), the level scan, the AC-3 sync test
// =====================================================================================================================

// 0x00535A88 sub_535A88 -- 652 bytes; frame 0x80: s2 sp+0x40, s4 sp+0x50, s0 sp+0x30, s1 sp+0x38, s3 sp+0x48, s5 sp+0x58, s6 sp+0x60, s7 sp+0x68, fp sp+0x70, ra sp+0x78
// Per-channel peak scan: for each channel, pull 16-bit samples from the input stream joint (vtable +36 GetNumData, +24
// GetChunk, +32 PutChunk), keep the largest |sample| per block of (rate * scale) samples and append a 16-byte peak
// record {peak, position, rate, block} to the output joint; counts records at +44. [proposed: adxb level-meter exec]
void sub_535A88(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00535a88
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s2, sp, 0x40);
    sd(s4, sp, 0x50);
    s4 = a0;
    sd(s0, sp, 0x30);
    sd(s1, sp, 0x38);
    sd(s3, sp, 0x48);
    sd(s5, sp, 0x58);
    sd(s6, sp, 0x60);
    sd(s7, sp, 0x68);
    sd(fp, sp, 0x70);
    sd(ra, sp, 0x78);
    sw(zero, sp, 0x20);
    lwc1(f0, s4, 32);
    cvt_s_w(f0, f0);
    lwc1(f1, s4, 36);
    lw(v0, s4, 28);
    mul_s(f0, f0, f1);
    cvt_w_s(f1, f0);
    mfc1(s2, f1);
    ld(s0, sp, 0x30);
    if (i64(v0) > 0) {
        // 0x00535ae0
        charge(ctx, 6);
        s7 = addiu(s4, 12);
        v0 = addiu(s4, 20);
        sw(s7, sp, 0x28);
        fp = addiu(s4, 0x4);
        sw(v0, sp, 0x2C);
        for (;;) {
            // 0x00535af8
            charge(ctx, 9);
            lw(v1, sp, 0x20);
            lw(a0, fp, 0x0);
            s1 = sll(v1, 2);
            lw(v1, a0, 0);
            lw(v0, v1, 36);
            a1 = 1;
            jalr(ctx, 0x535B0Cu, v0.u());
            if (s2 == 0) {
                brk(ctx, 0x535B18u, 0x7u);
            }
            // 0x00535b1c
            charge(ctx, 18);
            s0 = srl(v0, 31);
            lw(a0, s7, 0);
            s0 = addu(s0, v0);
            s0 = sra(s0, 1);
            lw(v1, a0, 0);
            div(s0, s2);
            lw(v0, v1, 36);
            mflo(s0);
            a1 = 0;
            jalr(ctx, 0x535B3Cu, v0.u());
            v1 = slti(v0, 0);
            a0 = addiu(v0, 15);
            if (v1 != 0) v0 = a0;
            v1 = sra(v0, 4);
            v0 = slt(s0, v1);
            if (v0 != 0) v1 = s0;
            if (i64(v1) <= 0) {
                lw(v1, sp, 0x20);
            } else {
                // 0x00535b64
                charge(ctx, 5);
                lw(v0, sp, 0x28);
                s6 = v1;
                lw(s5, sp, 0x2C);
                s1 = addu(v0, s1);
                sw(s1, sp, 0x24);
                for (;;) {
                    // 0x00535b78
                    charge(ctx, 3);
                    s0 = 0;
                    s3 = 0;
                    if (i64(s2) > 0) {
                        // 0x00535b84
                        charge(ctx, 3);
                        s1 = fp;
                        lw(a0, s1, 0);
                        for (;;) {
                            // 0x00535b90
                            charge(ctx, 13);
                            a2 = subu(s2, s0);
                            a3 = sp;
                            a2 = sll(a2, 1);
                            lw(v1, a0, 0);
                            lw(v0, v1, 24);
                            a1 = 1;
                            jalr(ctx, 0x535BA4u, v0.u());
                            lw(v1, sp, 0x4);
                            v0 = srl(v1, 31);
                            v1 = addu(v1, v0);
                            t0 = sra(v1, 1);
                            lw(a3, sp, 0x0);
                            if (i64(t0) > 0) {
                                // 0x00535bc4
                                charge(ctx, 1);
                                a2 = t0;
                                for (;;) {
                                    // 0x00535bc8
                                    charge(ctx, 9);
                                    lh(a0, a3, 0);
                                    a3 = addiu(a3, 2);
                                    a2 = addiu(a2, -1);
                                    a1 = subu(0, a0);
                                    v0 = slti(a0, 0);
                                    if (v0 != 0) a0 = a1;
                                    v1 = slt(s3, a0);
                                    if (v1 != 0) s3 = a0;
                                    if (a2 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                            // 0x00535bec
                            charge(ctx, 10);
                            lw(a0, s1, 0);
                            s0 = addu(s0, t0);
                            a1 = 0;
                            lw(v1, a0, 0);
                            lw(v0, v1, 32);
                            a2 = sp;
                            jalr(ctx, 0x535C00u, v0.u());
                            v1 = slt(s0, s2);
                            if (v1 == 0) {
                                break;
                            }
                            lw(a0, s1, 0);
                            backedge(ctx);
                        }
                    }
                    // 0x00535c14
                    charge(ctx, 11);
                    lw(a0, s7, 0);
                    v1 = addiu(sp, 0x10);
                    a3 = v1;
                    a1 = 0;
                    lw(v1, a0, 0);
                    lw(v0, v1, 24);
                    a2 = 16;
                    jalr(ctx, 0x535C2Cu, v0.u());
                    lw(v1, sp, 0x14);
                    lw(a3, sp, 0x10);
                    if (v1 == 0) {
                        goto L_00535c40;
                    }
                    // 0x00535c60
                    charge(ctx, 22);
                    v1 = addiu(sp, 0x10);
                    lw(v0, sp, 0x24);
                    a2 = v1;
                    sw(s3, a3, 0);
                    a1 = 1;
                    lw(a0, v0, 0);
                    s6 = addiu(s6, -1);
                    lw(v0, s5, 0);
                    lw(v1, a0, 0);
                    sw(v0, a3, 4);
                    lw(t0, v1, 32);
                    lw(v1, s4, 32);
                    sw(s2, a3, 12);
                    jt = t0.u();  // the target, read before the delay slot
                    link(ctx, 0x535C94u);  // $ra = the return address
                    sw(v1, a3, 8);
                    call_ptr(ctx, jt);
                    lw(v0, s5, 0);
                    v0 = addu(v0, s2);
                    sw(v0, s5, 0);
                    lw(v1, s4, 44);
                    v1 = addiu(v1, 1);
                    sw(v1, s4, 44);
                    if (s6 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00535cb8
                charge(ctx, 1);
                lw(v1, sp, 0x20);
            }
            // 0x00535cbc
            charge(ctx, 10);
            s7 = addiu(s7, 4);
            lw(v0, s4, 28);
            fp = addiu(fp, 0x4);
            v1 = addiu(v1, 1);
            sw(v1, sp, 0x20);
            v0 = slt(v1, v0);
            lw(v1, sp, 0x2C);
            v1 = addiu(v1, 4);
            sw(v1, sp, 0x2C);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00535ce4
        charge(ctx, 1);
        ld(s0, sp, 0x30);
    }
    // 0x00535ce8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(s4, sp, 0x50);
    ld(s5, sp, 0x58);
    ld(s6, sp, 0x60);
    ld(s7, sp, 0x68);
    ld(fp, sp, 0x70);
    ld(ra, sp, 0x78);
    sp = addiu(sp, 0x80);
    return;
L_00535c40:
    charge(ctx, 7);
    backedge(ctx);
    goto L_00535c40;
}

// 0x00535D18 sub_535D18 -- 40 bytes; frame 0x10: ra sp+0x0
// Runs the peak scan (sub_535A88) when the handle's state byte +1 is 2 (executing); else returns 2.
void sub_535D18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00535d18
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 2;
    sd(ra, sp, 0x0);
    lb(v1, a0, 1);
    ld(ra, sp, 0x0);
    if (v1 != v0) {
        // 0x00535d38
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00535d30
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
    gen::fn_sub_535A88_00535a88(ctx);  // tail call
}

// 0x00535E58 sub_535E58 -- 44 bytes; frame 0x10: ra sp+0x0
// Calls the global hook at 0x7836B0 when the handle's word +192 is set (a decode-end callback).
void sub_535E58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00535e58
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 192);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x780000;
    if (!cc) {
        // 0x00535e6c
        charge(ctx, 3);
        lw(v1, v0, 14000);
        jalr(ctx, 0x535E70u, v1.u());
    }
    // 0x00535e78 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00535F38 sub_535F38 -- 136 bytes; leaf frame (no stack)
// AC-3 sync-word test: 1 when bytes 0..1 or 16..17 hold 0x0B 0x77 in either byte order, else 0.
void sub_535F38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00535f38
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = a0;
    v0 = 11;
    lbu(a2, a1, 0);
    cc = a2 != v0;  // the condition, before the delay slot changes it
    v0 = 119;
    if (!cc) {
        // 0x00535f4c
        charge(ctx, 4);
        lbu(a0, a1, 1);
        v1 = 119;
        v0 = 1;
        if (a0 != v1) {
            // 0x00535f5c
            charge(ctx, 1);
            v0 = 119;
            goto L_00535f60;
        }
        // 0x00535fb8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00535f60:
    charge(ctx, 2);
    if (a2 != v0) {
        lbu(a2, a1, 16);
    } else {
        // 0x00535f68
        charge(ctx, 4);
        lbu(a0, a1, 1);
        v1 = 11;
        v0 = 1;
        if (a0 != v1) {
            // 0x00535f78
            charge(ctx, 1);
            lbu(a2, a1, 16);
            goto L_00535f7c;
        }
        // 0x00535fb8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00535f7c:
    charge(ctx, 3);
    v0 = 11;
    cc = a2 != v0;  // the condition, before the delay slot changes it
    v0 = 119;
    if (!cc) {
        // 0x00535f88
        charge(ctx, 4);
        lbu(a0, a1, 17);
        v1 = 119;
        v0 = 1;
        if (a0 != v1) {
            // 0x00535f98
            charge(ctx, 1);
            v0 = 119;
            goto L_00535f9c;
        }
        // 0x00535fb8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00535f9c:
    charge(ctx, 2);
    cc = a2 != v0;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x00535fa4
        charge(ctx, 4);
        lbu(a0, a1, 17);
        v1 = 11;
        v0 = 1;
        if (a0 != v1) {
            // 0x00535fb4
            charge(ctx, 1);
            v0 = 0;
        }
    }
    // 0x00535fb8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00536058 sub_536058 -- 36 bytes; frame 0x10: ra sp+0x0
// Calls the global hook at 0x7836C4 (tail call through a function pointer).
void sub_536058(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00536058
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x780000;
    sd(ra, sp, 0x0);
    lw(v1, v0, 14020);  // 0x7836C4
    jalr(ctx, 0x536068u, v1.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005360B0 sub_5360B0 -- 908 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28
// AIFF header parser: checks FORM / AIFF, walks the big-endian chunks to COMM (channels, frames, bits, sample-rate
// exponent) and SSND; returns the address of the sample data, 0 when malformed.
void sub_5360B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005360b0
    enter(ctx, 62);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t8 = a0;
    sd(s0, sp, 0x0);
    s0 = 0x4D520000;
    sd(s1, sp, 0x8);
    s1 = 0xFF0000;
    sd(s2, sp, 0x10);
    s2 = t0;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    s4 = a2;
    sd(s5, sp, 0x28);
    s5 = a1;
    s0 = s0 | 0x4F46;
    lbu(t7, t8, 0);
    lbu(t6, t8, 3);
    lbu(t4, t8, 2);
    lbu(t5, t8, 1);
    t8 = addiu(t8, 4);
    lbu(a1, t8, 3);
    t6 = sll(t6, 24);
    lbu(v1, t8, 2);
    t5 = sll(t5, 8);
    lbu(a0, t8, 1);
    a1 = sll(a1, 24);
    lbu(v0, t8, 0);
    t8 = addiu(t8, 4);
    a0 = sll(a0, 8);
    v1 = sll(v1, 16);
    v0 = v0 | a1;
    lbu(a1, t8, 2);
    v1 = v1 | a0;
    lbu(t3, t8, 3);
    t9 = v0 | v1;
    lbu(t2, t8, 1);
    v1 = sra(t9, 8);
    a0 = srl(t9, 24);
    v0 = sll(t9, 8);
    lbu(t1, t8, 0);
    t4 = sll(t4, 16);
    v1 = v1 & 0xFF00;
    v0 = v0 & s1;
    s1 = 0;
    t7 = t7 | t6;
    t6 = 0;
    t4 = t4 | t5;
    t5 = 0;
    a0 = a0 | v1;
    t3 = sll(t3, 24);
    a1 = sll(a1, 16);
    t2 = sll(t2, 8);
    a0 = a0 | v0;
    v0 = sll(t9, 24);
    t1 = t1 | t3;
    a1 = a1 | t2;
    t7 = t7 | t4;
    t9 = a0 | v0;
    t1 = t1 | a1;
    t8 = addiu(t8, 4);
    v0 = 0;
    if (t7 == s0) {
        // 0x005361a8
        charge(ctx, 4);
        v0 = 0x46460000;
        v0 = v0 | 0x4941;
        if (t1 == v0) {
            v0 = addu(t8, t9);
            // 0x005361c0
            charge(ctx, 4);
            t3 = addiu(v0, -4);
            v1 = sltu(t8, t3);
            v0 = s1;
            if (v1 != 0) {
                // 0x005361d0
                charge(ctx, 4);
                t4 = 0xFF0000;
                s0 = si(-256);
                lbu(t1, t8, 0);
                for (;;) {
                    // 0x005361e0
                    charge(ctx, 33);
                    t2 = 0x444E0000;
                    lbu(t0, t8, 3);
                    t2 = t2 | 0x5353;
                    lbu(a2, t8, 2);
                    lbu(a3, t8, 1);
                    t8 = addiu(t8, 4);
                    lbu(a1, t8, 3);
                    t0 = sll(t0, 24);
                    lbu(v1, t8, 2);
                    a2 = sll(a2, 16);
                    lbu(a0, t8, 1);
                    a1 = sll(a1, 24);
                    lbu(v0, t8, 0);
                    t8 = addiu(t8, 4);
                    a0 = sll(a0, 8);
                    v1 = sll(v1, 16);
                    v1 = v1 | a0;
                    v0 = v0 | a1;
                    t9 = v0 | v1;
                    a3 = sll(a3, 8);
                    v1 = sra(t9, 8);
                    a0 = srl(t9, 24);
                    v0 = sll(t9, 8);
                    v1 = v1 & 0xFF00;
                    v0 = v0 & t4;
                    t1 = t1 | t0;
                    a2 = a2 | a3;
                    a0 = a0 | v1;
                    a0 = a0 | v0;
                    v0 = sll(t9, 24);
                    t7 = t1 | a2;
                    t9 = a0 | v0;
                    if (t7 == t2) {
                        // 0x00536390
                        charge(ctx, 2);
                        v0 = sltu(t8, t3);
                        if (t6 != 0) {
                        L_00536410:
                            charge(ctx, 2);
                            if (v0 == 0) {
                                goto L_00536418_17;
                            }
                            lbu(t1, t8, 0);
                            backedge(ctx);
                            continue;
                        }
                        // 0x00536398
                        charge(ctx, 23);
                        lbu(a1, t8, 3);
                        t6 = 1;
                        lbu(v0, t8, 2);
                        lbu(a0, t8, 1);
                        a1 = sll(a1, 24);
                        lbu(v1, t8, 0);
                        t8 = addiu(t8, 4);
                        a0 = sll(a0, 8);
                        v0 = sll(v0, 16);
                        v1 = v1 | a1;
                        v0 = v0 | a0;
                        v0 = v1 | v0;
                        a1 = srl(v0, 8);
                        a0 = sll(v0, 8);
                        v1 = srl(v0, 24);
                        v0 = sll(v0, 24);
                        a0 = a0 & t4;
                        a1 = a1 & 0xFF00;
                        v1 = v1 | v0;
                        a0 = a0 | a1;
                        v0 = v1 | a0;
                        s1 = addu(t8, v0);
                        if (t5 != 0) {
                            goto L_005363f4_13;
                        }
                    L_0053640c:
                        charge(ctx, 1);
                        v0 = sltu(t8, t3);
                        goto L_00536410;
                    }
                    // 0x00536264
                    charge(ctx, 4);
                    v0 = 0x4D4D0000;
                    v0 = v0 | 0x4F43;
                    cc = t7 != v0;  // the condition, before the delay slot changes it
                    v0 = addiu(t9, 1);
                    if (cc) {
                        // 0x00536400
                        charge(ctx, 3);
                        v1 = si(-2);
                        v0 = v0 & v1;
                        t8 = addu(t8, v0);
                        goto L_0053640c;
                    }
                    // 0x00536274
                    charge(ctx, 2);
                    v0 = sltu(t8, t3);
                    if (t5 != 0) {
                        goto L_00536410;
                    }
                    // 0x0053627c
                    charge(ctx, 3);
                    v0 = slti(t9, 18);
                    cc = v0 != 0;  // the condition, before the delay slot changes it
                    v0 = 0;
                    if (!cc) {
                        // 0x00536288
                        charge(ctx, 63);
                        lbu(a0, t8, 1);
                        a2 = 16398;
                        lbu(v0, t8, 0);
                        t8 = addiu(t8, 2);
                        a0 = sll(a0, 8);
                        t5 = 1;
                        v0 = v0 | a0;
                        v1 = sll(v0, 8);
                        v0 = srl(v0, 8);
                        v1 = v1 & 0xFF00;
                        v0 = v0 | v1;
                        sw(v0, s4, 0);
                        lbu(a1, t8, 3);
                        lbu(v0, t8, 2);
                        lbu(a0, t8, 1);
                        a1 = sll(a1, 24);
                        lbu(v1, t8, 0);
                        t8 = addiu(t8, 4);
                        a0 = sll(a0, 8);
                        v0 = sll(v0, 16);
                        v0 = v0 | a0;
                        v1 = v1 | a1;
                        v1 = v1 | v0;
                        a1 = sra(v1, 8);
                        a0 = sll(v1, 8);
                        a1 = a1 & 0xFF00;
                        v0 = srl(v1, 24);
                        a0 = a0 & t4;
                        v1 = sll(v1, 24);
                        a0 = a0 | a1;
                        v0 = v0 | v1;
                        v0 = v0 | a0;
                        sw(v0, s2, 0);
                        lbu(a0, t8, 1);
                        lbu(v0, t8, 0);
                        t8 = addiu(t8, 2);
                        a0 = sll(a0, 8);
                        v0 = v0 | a0;
                        v1 = sll(v0, 8);
                        v0 = srl(v0, 8);
                        v1 = v1 & 0xFF00;
                        v0 = v0 | v1;
                        sw(v0, s3, 0);
                        lbu(a1, t8, 0);
                        lbu(a0, t8, 1);
                        t8 = addiu(t8, 2);
                        lbu(v1, t8, 1);
                        lbu(v0, t8, 0);
                        t8 = addiu(t8, 8);
                        v1 = sll(v1, 8);
                        a0 = sll(a0, 8);
                        v0 = v0 | v1;
                        a1 = a1 | a0;
                        v1 = sll(v0, 8);
                        v0 = srl(v0, 8);
                        v1 = v1 & s0;
                        a1 = srl(a1, 8);
                        v0 = v0 | v1;
                        a2 = subu(a2, a1);
                        v0 = v0 & 0xFFFF;
                        v0 = srav(v0, a2);
                        sw(v0, s5, 0);
                        if (t6 == 0) {
                            goto L_0053640c;
                        }
                        goto L_00536384_10;
                    }
                    break;
                }
            }
        } else {
            // 0x005361b8
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x0053641c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    sp = addiu(sp, 0x30);
    return;
L_00536384_10:
    charge(ctx, 2);
    v0 = s1;
    // 0x0053641c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    sp = addiu(sp, 0x30);
    return;
L_005363f4_13:
    charge(ctx, 2);
    v0 = s1;
    // 0x0053641c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    sp = addiu(sp, 0x30);
    return;
L_00536418_17:
    charge(ctx, 1);
    v0 = s1;
    // 0x0053641c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00536440 sub_536440 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// AIFF magic test: memcmp(p, "FORM", 4) == 0 && memcmp(p + 8, "AIFF", 4) == 0.
void sub_536440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00536440
    enter(ctx, 13);  // entry check point + this block's cycles
    a1 = 0x7C0000;
    sp = addiu(sp, -0x10);
    a2 = 4;
    a1 = addiu(a1, 4456);  // "FORM"
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x536458u, gen::fn_memcmp_005211b8);
    a1 = 0x7C0000;
    a0 = addiu(s0, 8);
    a1 = addiu(a1, 4464);  // "AIFF"
    a2 = 4;
    if (v0 != 0) {
        // 0x00536490
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00536474
        charge(ctx, 4);
        jal(ctx, 0x536474u, gen::fn_memcmp_005211b8);
        if (v0 != 0) {
            v0 = 0;
        } else {
            // 0x00536484
            charge(ctx, 2);
            v0 = 1;
        }
    }
    // 0x00536494 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005364A8 sub_5364A8 -- 272 bytes; frame 0x50: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, s6 sp+0x40, ra sp+0x48
// AIFF header decode into the caller's fields (header size, block bytes, bits, channels, rate, frames); -1 below 4096
// bytes or when sub_5360B0 refuses.
void sub_5364A8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005364a8
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = slti(a1, 4096);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a2;
    sd(s2, sp, 0x20);
    s2 = t2;
    sd(s3, sp, 0x28);
    s3 = t3;
    sd(s4, sp, 0x30);
    s4 = t0;
    sd(s5, sp, 0x38);
    s5 = a3;
    sd(s6, sp, 0x40);
    s6 = t1;
    sd(ra, sp, 0x48);
    a1 = sp;
    a2 = addiu(sp, 0x4);
    t0 = addiu(sp, 0xC);
    a3 = addiu(sp, 0x8);
    if (v0 == 0) {
        // 0x00536510
        charge(ctx, 5);
        jal(ctx, 0x536510u, gen::fn_sub_5360B0_005360b0);
        v1 = v0;
        v0 = si(-1);
        if (v1 != 0) {
            // 0x00536524
            charge(ctx, 4);
            v1 = subu(v1, s0);
            a0 = sll(v1, 16);
            sh(v1, s1, 0);
            if (i64(a0) > 0) {
                // 0x00536534
                charge(ctx, 23);
                lbu(v1, sp, 0x4);
                a3 = si(-1);
                lw(a2, sp, 0x0);
                t0 = 1;
                lbu(a0, sp, 0x8);
                v0 = 0;
                sw(a2, s3, 0);
                lw(a1, sp, 0xC);
                sb(v1, s2, 0);
                sb(a0, s4, 0);
                lw(v1, sp, 0x50);
                sw(a1, v1, 0);
                sb(a3, s5, 0);
                lb(a0, s4, 0);
                lb(v1, s2, 0);
                mult(v1, v1, a0);
                a0 = slti(v1, 0);
                a1 = addiu(v1, 7);
                if (a0 != 0) v1 = a1;
                lw(a0, sp, 0x58);
                v1 = sra(v1, 3);
                sb(v1, s6, 0);
                sw(t0, a0, 0);
            }
        }
    } else {
        // 0x00536500
        charge(ctx, 3);
        sh(zero, s1, 0);
        v0 = si(-1);
    }
    // 0x00536590 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x005365B8 sub_5365B8 -- 280 bytes; frame 0x60: s0 sp+0x20, s5 sp+0x48, s1 sp+0x28, s2 sp+0x30, s3 sp+0x38, s4 sp+0x40, ra sp+0x50, s3 sp+0x8
// ADXB handle set-up for an AIFF stream: decodes the header (sub_5364A8) into +12..+24, clears the decode counters and
// copies the output buffer layout; returns the header size.
void sub_5365B8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005365b8
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s0, sp, 0x20);
    s0 = a0;
    sd(s5, sp, 0x48);
    s5 = 1;
    sd(s1, sp, 0x28);
    s1 = addiu(s0, 14);
    sd(s2, sp, 0x30);
    s2 = addiu(s0, 15);
    sd(s3, sp, 0x38);
    s3 = addiu(s0, 16);
    sd(s4, sp, 0x40);
    s4 = addiu(s0, 13);
    sd(ra, sp, 0x50);
    a0 = a1;
    sh(s5, s0, 2);
    v0 = addiu(s0, 24);
    a1 = a2;
    a2 = addiu(sp, 0x10);
    a3 = addiu(s0, 12);
    t0 = s4;
    t1 = s2;
    t2 = s1;
    t3 = addiu(s0, 20);
    sw(v0, sp, 0x0);
    link(ctx, 0x53661Cu);  // $ra first: the delay slot below depends on it
    sw(s3, sp, 0x8);
    call(ctx, gen::fn_sub_5364A8_005364a8);
    a3 = 8;
    if (i64(v0) >= 0) {
        // 0x00536638
        charge(ctx, 27);
        sw(zero, s0, 52);
        sw(zero, s0, 48);
        sw(zero, s0, 44);
        sw(zero, s0, 40);
        sw(zero, s0, 32);
        sh(zero, s0, 28);
        sh(zero, s0, 38);
        sh(zero, s0, 36);
        lw(a0, s0, 60);
        lb(v0, s1, 0);
        lw(a1, s0, 64);
        sw(v0, s0, 80);
        v0 = 3;
        lw(a2, s0, 68);
        lb(v1, s2, 0);
        sw(a0, s0, 92);
        sw(v1, s0, 84);
        sh(v0, s0, 152);
        lw(v1, s3, 0);
        sw(a1, s0, 96);
        sw(v1, s0, 88);
        sw(a2, s0, 100);
        sw(zero, s0, 140);
        sw(zero, s0, 136);
        lb(v0, s4, 0);
        if (v0 != a3) {
            sh(zero, s0, 156);
        } else {
            // 0x005366a4
            charge(ctx, 1);
            sh(s5, s0, 156);
        }
        // 0x005366a8
        charge(ctx, 1);
        lh(v0, sp, 0x10);
    } else {
        // 0x0053662c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x005366ac (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(ra, sp, 0x50);
    sp = addiu(sp, 0x60);
}

// 0x005366D0 sub_5366D0 -- 408 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// AIFF decode step, 16-bit big-endian samples: byte-swaps the available input into the output channels and advances
// the counters.
void sub_5366D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005366d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = addiu(s0, 72);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v1, s0, 4);
    lw(s2, s1, 0);
    if (v1 == v0) {
        // 0x005366fc
        charge(ctx, 4);
        link(ctx, 0x5366FCu);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 8);
        call(ctx, gen::fn_sub_54CD80_0054cd80);
        if (v0 != 0) {
            lw(v1, s0, 4);
        } else {
            // 0x0053670c
            charge(ctx, 22);
            lw(a0, s0, 124);
            a1 = addiu(s0, 104);
            lw(v0, s0, 120);
            a2 = addiu(s0, 108);
            a3 = addiu(s0, 112);
            jalr(ctx, 0x53671Cu, v0.u());
            lw(a0, s1, 24);
            lw(a3, s1, 32);
            a2 = 2;
            lw(v1, s1, 36);
            t1 = subu(a0, a3);
            lb(a0, s0, 14);
            v0 = slt(v1, t1);
            lw(a1, s1, 4);
            if (v0 != 0) t1 = v1;
            v1 = sll(a3, 1);
            lw(t3, s1, 20);
            v0 = slt(a1, t1);
            if (v0 != 0) t1 = a1;
            t2 = addu(t3, v1);
            lbu(v1, s0, 14);
            if (a0 != a2) {
                // 0x005367d0
                charge(ctx, 2);
                t0 = 0;
                if (i64(t1) > 0) {
                    for (;;) {
                        // 0x005367d8
                        charge(ctx, 11);
                        a0 = sll(t0, 1);
                        t0 = addiu(t0, 1);
                        v0 = addu(a0, s2);
                        a0 = addu(a0, t2);
                        lhu(v0, v0, 0);
                        a1 = slt(t0, t1);
                        v1 = sll(v0, 8);
                        v0 = srl(v0, 8);
                        v0 = v0 | v1;
                        sh(v0, a0, 0);
                        if (a1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00536804
                    charge(ctx, 1);
                    lbu(v1, s0, 14);
                }
            } else {
                // 0x00536764
                charge(ctx, 6);
                lw(v0, s1, 28);
                t0 = 0;
                v0 = addu(v0, a3);
                v0 = sll(v0, 1);
                t3 = addu(t3, v0);
                if (i64(t1) > 0) {
                    // 0x0053677c
                    charge(ctx, 1);
                    a3 = s2;
                    for (;;) {
                        // 0x00536780
                        charge(ctx, 17);
                        lhu(v0, a3, 0);
                        a0 = sll(t0, 1);
                        a1 = addu(a0, t2);
                        a0 = addu(a0, t3);
                        v1 = sll(v0, 8);
                        v0 = srl(v0, 8);
                        v0 = v0 | v1;
                        t0 = addiu(t0, 1);
                        sh(v0, a1, 0);
                        a2 = slt(t0, t1);
                        lhu(v0, a3, 2);
                        a3 = addiu(a3, 4);
                        v1 = sll(v0, 8);
                        v0 = srl(v0, 8);
                        v0 = v0 | v1;
                        sh(v0, a0, 0);
                        if (a2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x005367c4
                    charge(ctx, 2);
                    lbu(v1, s0, 14);
                }
            }
            // 0x00536808
            charge(ctx, 8);
            v0 = sll(v1, 24);
            v1 = 2;
            v0 = sra(v0, 24);
            sw(v1, s0, 4);
            mult(v0, t1, v0);
            sw(t1, s0, 144);
            v0 = sll(v0, 1);
            sw(v0, s0, 148);
        }
    }
    // 0x00536828
    charge(ctx, 3);
    v0 = 2;
    if (v1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00536834
        charge(ctx, 8);
        lw(v1, s0, 128);
        lw(a0, s0, 132);
        lw(a1, s0, 148);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x536840u);  // $ra = the return address
        lw(a2, s0, 144);
        call_ptr(ctx, jt);
        v0 = 3;
        sw(v0, s0, 4);
        ld(s0, sp, 0x0);
    }
    // 0x00536854 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00536868 sub_536868 -- 384 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// AIFF decode step, 8-bit signed samples: widens the available input into the output channels.
void sub_536868(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00536868
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = addiu(s0, 72);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v1, s0, 4);
    lw(s2, s1, 0);
    if (v1 == v0) {
        // 0x00536894
        charge(ctx, 4);
        link(ctx, 0x536894u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 8);
        call(ctx, gen::fn_sub_54CD80_0054cd80);
        if (v0 != 0) {
            lw(v1, s0, 4);
        } else {
            // 0x005368a4
            charge(ctx, 22);
            lw(a0, s0, 124);
            a1 = addiu(s0, 104);
            lw(v0, s0, 120);
            a2 = addiu(s0, 108);
            a3 = addiu(s0, 112);
            jalr(ctx, 0x5368B4u, v0.u());
            lw(a0, s1, 24);
            lw(t1, s1, 32);
            a2 = 2;
            lw(v1, s1, 36);
            t0 = subu(a0, t1);
            lb(a0, s0, 14);
            v0 = slt(v1, t0);
            lw(a1, s1, 4);
            if (v0 != 0) t0 = v1;
            v1 = sll(t1, 1);
            lw(t3, s1, 20);
            v0 = slt(a1, t0);
            if (v0 != 0) t0 = a1;
            t2 = addu(t3, v1);
            lbu(v1, s0, 14);
            if (a0 != a2) {
                // 0x00536958
                charge(ctx, 2);
                a3 = 0;
                if (i64(t0) > 0) {
                    // 0x00536960
                    charge(ctx, 2);
                    a1 = t2;
                    for (;;) {
                        // 0x00536968
                        charge(ctx, 8);
                        v0 = addu(s2, a3);
                        a3 = addiu(a3, 1);
                        lbu(v1, v0, 0);
                        a0 = slt(a3, t0);
                        v1 = sll(v1, 8);
                        sh(v1, a1, 0);
                        a1 = addiu(a1, 2);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00536988
                    charge(ctx, 1);
                    lbu(v1, s0, 14);
                }
            } else {
                // 0x005368fc
                charge(ctx, 6);
                lw(v0, s1, 28);
                a3 = 0;
                v0 = addu(v0, t1);
                v0 = sll(v0, 1);
                t1 = addu(t3, v0);
                if (i64(t0) > 0) {
                    // 0x00536914
                    charge(ctx, 1);
                    a2 = s2;
                    for (;;) {
                        // 0x00536918
                        charge(ctx, 13);
                        lbu(v0, a2, 0);
                        v1 = sll(a3, 1);
                        a0 = addu(v1, t2);
                        v1 = addu(v1, t1);
                        v0 = sll(v0, 8);
                        a3 = addiu(a3, 1);
                        sh(v0, a0, 0);
                        a1 = slt(a3, t0);
                        lbu(v0, a2, 1);
                        a2 = addiu(a2, 2);
                        v0 = sll(v0, 8);
                        sh(v0, v1, 0);
                        if (a1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0053694c
                    charge(ctx, 2);
                    lbu(v1, s0, 14);
                }
            }
            // 0x0053698c
            charge(ctx, 7);
            v0 = sll(v1, 24);
            v1 = 2;
            v0 = sra(v0, 24);
            sw(v1, s0, 4);
            mult(v0, t0, v0);
            sw(t0, s0, 144);
            sw(v0, s0, 148);
        }
    }
    // 0x005369a8
    charge(ctx, 3);
    v0 = 2;
    if (v1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005369b4
        charge(ctx, 8);
        lw(v1, s0, 128);
        lw(a0, s0, 132);
        lw(a1, s0, 148);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x5369C0u);  // $ra = the return address
        lw(a2, s0, 144);
        call_ptr(ctx, jt);
        v0 = 3;
        sw(v0, s0, 4);
        ld(s0, sp, 0x0);
    }
    // 0x005369d4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005369E8 sub_5369E8 -- 40 bytes; frame 0x10: ra sp+0x0
// AIFF decode dispatch on the handle's sample width (+156): 8-bit (sub_536868) or 16-bit (sub_5366D0).
void sub_5369E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005369e8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    lh(v1, a0, 156);
    ld(ra, sp, 0x0);
    if (v1 != v0) {
        // 0x00536a08
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        gen::fn_sub_5366D0_005366d0(ctx);  // tail call
        return;
    }
    // 0x00536a00
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
    gen::fn_sub_536868_00536868(ctx);  // tail call
}

// 0x00536A10 sub_536A10 -- 792 bytes; frame 0x10: s0 sp+0x0, s1 sp+0x8
// Sun / NeXT .snd (AU) header parser: magic '.snd' (or its DEC twin), big-endian data offset, size, encoding, rate,
// channels.
void sub_536A10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00536a10
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t6 = a0;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a3;
    t4 = 0x640000;
    t9 = a1;
    lbu(t3, t6, 3);
    t4 = t4 | 0x732E;  // &0x64732E
    lbu(v1, t6, 2);
    t5 = t0;
    lbu(a0, t6, 1);
    t3 = sll(t3, 24);
    lbu(v0, t6, 0);
    v1 = sll(v1, 16);
    a0 = sll(a0, 8);
    t8 = t1;
    v0 = v0 | t3;
    v1 = v1 | a0;
    a0 = v0 | v1;
    t3 = addiu(t6, 4);
    if (a0 != t4) {
        // 0x00536a6c
        charge(ctx, 4);
        v1 = 0x646E0000;
        v1 = v1 | 0x732E;
        v0 = 0;
        if (a0 == v1) {
            goto L_00536a7c;
        }
    L_00536d18:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
        // 0x00536d1c (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(s1, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_00536a7c:
    charge(ctx, 24);
    lbu(a2, t3, 3);
    t7 = 0xFF0000;
    lbu(a0, t3, 2);
    v0 = 0;
    lbu(a1, t3, 1);
    a2 = sll(a2, 24);
    lbu(v1, t3, 0);
    a1 = sll(a1, 8);
    a0 = sll(a0, 16);
    v1 = v1 | a2;
    a0 = a0 | a1;
    t4 = v1 | a0;
    a2 = srl(t4, 8);
    a1 = sll(t4, 8);
    a0 = sll(t4, 24);
    v1 = srl(t4, 24);
    a1 = a1 & t7;
    a2 = a2 & 0xFF00;
    v1 = v1 | a0;
    a1 = a1 | a2;
    t4 = v1 | a1;
    a0 = slt(t9, t4);
    t3 = addiu(t3, 4);
    if (a0 != 0) {
        goto L_00536d18;
    }
    // 0x00536adc
    charge(ctx, 42);
    lbu(t1, t3, 0);
    t9 = 2;
    lbu(t0, t3, 3);
    lbu(a2, t3, 2);
    lbu(a3, t3, 1);
    t3 = addiu(t3, 4);
    lbu(a1, t3, 3);
    t0 = sll(t0, 24);
    lbu(a0, t3, 2);
    a3 = sll(a3, 8);
    lbu(v0, t3, 1);
    a1 = sll(a1, 24);
    lbu(v1, t3, 0);
    t3 = addiu(t3, 4);
    v0 = sll(v0, 8);
    a0 = sll(a0, 16);
    v1 = v1 | a1;
    a0 = a0 | v0;
    a2 = sll(a2, 16);
    a0 = v1 | a0;
    a2 = a2 | a3;
    t1 = t1 | t0;
    t1 = t1 | a2;
    a2 = srl(a0, 24);
    v0 = srl(a0, 8);
    a1 = sll(a0, 8);
    a3 = srl(t1, 8);
    v0 = v0 & 0xFF00;
    v1 = sll(t1, 8);
    a0 = sll(a0, 24);
    a1 = a1 & t7;
    a2 = a2 | a0;
    a1 = a1 | v0;
    v0 = srl(t1, 24);
    a0 = sll(t1, 24);
    v1 = v1 & t7;
    a3 = a3 & 0xFF00;
    v0 = v0 | a0;
    v1 = v1 | a3;
    a0 = a2 | a1;
    t1 = v0 | v1;
    if (a0 == t9) {
        // 0x00536bc8
        charge(ctx, 5);
        v0 = 1;
        v1 = 8;
        sw(v0, t2, 0);
        sw(v1, t5, 0);
    L_00536bec:
        charge(ctx, 46);
        lbu(a1, t3, 3);
        a2 = 0xFF0000;
        lbu(v1, t3, 2);
        a3 = 2;
        lbu(a0, t3, 1);
        a1 = sll(a1, 24);
        lbu(v0, t3, 0);
        t3 = addiu(t3, 4);
        a0 = sll(a0, 8);
        v1 = sll(v1, 16);
        v1 = v1 | a0;
        v0 = v0 | a1;
        v0 = v0 | v1;
        a1 = sra(v0, 8);
        a0 = sll(v0, 8);
        a1 = a1 & 0xFF00;
        v1 = srl(v0, 24);
        a0 = a0 & a2;
        v0 = sll(v0, 24);
        a0 = a0 | a1;
        v1 = v1 | v0;
        v1 = v1 | a0;
        sw(v1, s0, 0);
        lbu(a1, t3, 1);
        lbu(a0, t3, 3);
        lbu(v1, t3, 2);
        a1 = sll(a1, 8);
        lbu(v0, t3, 0);
        a0 = sll(a0, 24);
        v1 = sll(v1, 16);
        v1 = v1 | a1;
        v0 = v0 | a0;
        v0 = v0 | v1;
        a1 = sra(v0, 8);
        a0 = sll(v0, 8);
        v1 = srl(v0, 24);
        v0 = sll(v0, 24);
        a0 = a0 & a2;
        a1 = a1 & 0xFF00;
        v1 = v1 | v0;
        a0 = a0 | a1;
        v1 = v1 | a0;
        sw(v1, s1, 0);
        lw(t2, t2, 0);
        v0 = 1;
        if (t2 != a3) {
            // 0x00536cc0
            charge(ctx, 2);
            if (t2 != v0) {
                // 0x00536ce0
                charge(ctx, 2);
                v0 = 0x7FFF0000;
                if (t2 != 0) {
                    // 0x00536d10
                    charge(ctx, 1);
                    sw(v0, t8, 0);
                } else {
                    // 0x00536ce8
                    charge(ctx, 3);
                    v0 = srl(t1, 31);
                    if (v1 == 0) {
                        brk(ctx, 0x536CF0u, 0x7u);
                    }
                    // 0x00536cf4
                    charge(ctx, 6);
                    v0 = addu(t1, v0);
                    v0 = sra(v0, 1);
                    div(v0, v1);
                    mflo(v0);
                    sw(v0, t8, 0);
                }
            } else {
                // 0x00536cc8
                charge(ctx, 3);
                div(t1, v1);
                if (v1 == 0) {
                    brk(ctx, 0x536CD0u, 0x7u);
                }
                // 0x00536cd4
                charge(ctx, 3);
                mflo(v0);
                sw(v0, t8, 0);
            }
        } else {
            // 0x00536ca4
            charge(ctx, 3);
            div(t1, v1);
            if (v1 == 0) {
                brk(ctx, 0x536CACu, 0x7u);
            }
            // 0x00536cb0
            charge(ctx, 3);
            mflo(v0);
            sw(v0, t8, 0);
        }
        // 0x00536d14
        charge(ctx, 1);
        v0 = addu(t6, t4);
        goto L_00536d18;
    }
    // 0x00536b84
    charge(ctx, 3);
    v0 = sltiu(a0, 3);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 3;
    if (cc) {
        // 0x00536ba8
        charge(ctx, 2);
        cc = a0 == v0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (cc) {
            // 0x00536be0
            charge(ctx, 3);
            v0 = 16;
            sw(zero, t2, 0);
            sw(v0, t5, 0);
            goto L_00536bec;
        }
        // 0x00536bb0
        charge(ctx, 2);
        ld(s0, sp, 0x0);
    } else {
        // 0x00536b90
        charge(ctx, 3);
        v0 = 1;
        cc = a0 == v0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (cc) {
            // 0x00536bb8
            charge(ctx, 4);
            v0 = 8;
            sw(t9, t2, 0);
            sw(v0, t5, 0);
            goto L_00536bec;
        }
        // 0x00536b9c
        charge(ctx, 2);
        ld(s0, sp, 0x0);
    }
    // 0x00536d1c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00536D28 sub_536D28 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// AU magic test: ".snd" or the second accepted magic at 0x7C1180.
void sub_536D28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00536d28
    enter(ctx, 13);  // entry check point + this block's cycles
    a1 = 0x7C0000;
    sp = addiu(sp, -0x10);
    a2 = 4;
    a1 = addiu(a1, 4472);  // ".snd"
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x536D40u, gen::fn_memcmp_005211b8);
    a1 = 0x7C0000;
    a0 = s0;
    a1 = addiu(a1, 4480);  // ".sd"
    a2 = 4;
    if (v0 != 0) {
        // 0x00536d5c
        charge(ctx, 4);
        jal(ctx, 0x536D5Cu, gen::fn_memcmp_005211b8);
        if (v0 == 0) {
            goto L_00536d6c;
        }
        v0 = 0;
        // 0x00536d70 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_00536d6c:
    charge(ctx, 1);
    v0 = 1;
    // 0x00536d70 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00536D80 sub_536D80 -- 272 bytes; frame 0x50: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, s6 sp+0x40, ra sp+0x48
// AU header decode into the caller's fields; -1 below 8 bytes or when sub_536A10 refuses.
void sub_536D80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00536d80
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = slti(a1, 8);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a2;
    sd(s2, sp, 0x20);
    s2 = t2;
    sd(s3, sp, 0x28);
    s3 = t3;
    sd(s4, sp, 0x30);
    s4 = t0;
    sd(s5, sp, 0x38);
    s5 = a3;
    sd(s6, sp, 0x40);
    s6 = t1;
    sd(ra, sp, 0x48);
    a2 = sp;
    t0 = addiu(sp, 0x8);
    a3 = addiu(sp, 0x4);
    t1 = addiu(sp, 0xC);
    lw(t2, sp, 0x60);
    if (v0 == 0) {
        // 0x00536de8
        charge(ctx, 6);
        jal(ctx, 0x536DE8u, gen::fn_sub_536A10_00536a10);
        v1 = v0;
        v0 = si(-1);
        a0 = subu(v1, s0);
        if (v1 != 0) {
            // 0x00536e00
            charge(ctx, 3);
            v1 = sll(a0, 16);
            sh(a0, s1, 0);
            if (i64(v1) > 0) {
                // 0x00536e0c
                charge(ctx, 23);
                lw(a2, sp, 0x0);
                a3 = si(-1);
                lbu(v1, sp, 0x4);
                t0 = 1;
                lbu(a0, sp, 0x8);
                v0 = 0;
                sw(a2, s3, 0);
                lw(a1, sp, 0xC);
                sb(v1, s2, 0);
                sb(a0, s4, 0);
                lw(v1, sp, 0x50);
                sw(a1, v1, 0);
                sb(a3, s5, 0);
                lb(a0, s4, 0);
                lb(v1, s2, 0);
                mult(v1, v1, a0);
                a0 = slti(v1, 0);
                a1 = addiu(v1, 7);
                if (a0 != 0) v1 = a1;
                v1 = sra(v1, 3);
                sb(v1, s6, 0);
                lw(a0, sp, 0x58);
                sw(t0, a0, 0);
            }
        }
    } else {
        // 0x00536ddc
        charge(ctx, 3);
        sh(zero, s1, 0);
        v0 = si(-1);
    }
    // 0x00536e68 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x00536E90 sub_536E90 -- 252 bytes; frame 0x60: s0 sp+0x30, s1 sp+0x38, s2 sp+0x40, s3 sp+0x48, ra sp+0x50, s2 sp+0x8
// ADXB handle set-up for an AU stream (as sub_5365B8 for AIFF).
void sub_536E90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00536e90
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 1;
    sd(s0, sp, 0x30);
    s0 = a0;
    sd(s1, sp, 0x38);
    s1 = addiu(s0, 14);
    sd(s2, sp, 0x40);
    s2 = addiu(s0, 16);
    sd(s3, sp, 0x48);
    s3 = addiu(s0, 15);
    sd(ra, sp, 0x50);
    a0 = a1;
    sh(v0, s0, 2);
    v0 = addiu(s0, 24);
    a1 = a2;
    a2 = addiu(sp, 0x20);
    v1 = addiu(sp, 0x24);
    a3 = addiu(s0, 12);
    t0 = addiu(s0, 13);
    t1 = s3;
    t2 = s1;
    t3 = addiu(s0, 20);
    sw(v0, sp, 0x0);
    sw(v1, sp, 0x10);
    link(ctx, 0x536EF0u);  // $ra first: the delay slot below depends on it
    sw(s2, sp, 0x8);
    call(ctx, gen::fn_sub_536D80_00536d80);
    if (i64(v0) >= 0) {
        sw(zero, s0, 52);
        // 0x00536f08
        charge(ctx, 26);
        sw(zero, s0, 48);
        sw(zero, s0, 44);
        sw(zero, s0, 40);
        sw(zero, s0, 32);
        sh(zero, s0, 28);
        sh(zero, s0, 38);
        sh(zero, s0, 36);
        lw(a1, s0, 60);
        lb(v0, s1, 0);
        lhu(a0, sp, 0x24);
        sw(v0, s0, 80);
        lw(a2, s0, 64);
        lb(v1, s3, 0);
        lh(v0, sp, 0x20);
        sw(v1, s0, 84);
        v1 = 4;
        lw(a3, s0, 68);
        sh(a0, s0, 156);
        lw(a0, s2, 0);
        sw(a1, s0, 92);
        sh(v1, s0, 152);
        sw(a0, s0, 88);
        sw(a2, s0, 96);
        sw(a3, s0, 100);
        sw(zero, s0, 140);
        sw(zero, s0, 136);
    } else {
        // 0x00536f00
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00536f70 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(ra, sp, 0x50);
    sp = addiu(sp, 0x60);
}

// 0x00536F90 sub_536F90 -- 408 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// AU decode step, 16-bit big-endian linear PCM.
void sub_536F90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00536f90
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = addiu(s0, 72);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v1, s0, 4);
    lw(s2, s1, 0);
    if (v1 == v0) {
        // 0x00536fbc
        charge(ctx, 4);
        link(ctx, 0x536FBCu);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 8);
        call(ctx, gen::fn_sub_54CD80_0054cd80);
        if (v0 != 0) {
            lw(v1, s0, 4);
        } else {
            // 0x00536fcc
            charge(ctx, 22);
            lw(a0, s0, 124);
            a1 = addiu(s0, 104);
            lw(v0, s0, 120);
            a2 = addiu(s0, 108);
            a3 = addiu(s0, 112);
            jalr(ctx, 0x536FDCu, v0.u());
            lw(a0, s1, 24);
            lw(a3, s1, 32);
            a2 = 2;
            lw(v1, s1, 36);
            t1 = subu(a0, a3);
            lb(a0, s0, 14);
            v0 = slt(v1, t1);
            lw(a1, s1, 4);
            if (v0 != 0) t1 = v1;
            v1 = sll(a3, 1);
            lw(t3, s1, 20);
            v0 = slt(a1, t1);
            if (v0 != 0) t1 = a1;
            t2 = addu(t3, v1);
            lbu(v1, s0, 14);
            if (a0 != a2) {
                // 0x00537090
                charge(ctx, 2);
                t0 = 0;
                if (i64(t1) > 0) {
                    for (;;) {
                        // 0x00537098
                        charge(ctx, 11);
                        a0 = sll(t0, 1);
                        t0 = addiu(t0, 1);
                        v0 = addu(a0, s2);
                        a0 = addu(a0, t2);
                        lhu(v0, v0, 0);
                        a1 = slt(t0, t1);
                        v1 = sll(v0, 8);
                        v0 = srl(v0, 8);
                        v0 = v0 | v1;
                        sh(v0, a0, 0);
                        if (a1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x005370c4
                    charge(ctx, 1);
                    lbu(v1, s0, 14);
                }
            } else {
                // 0x00537024
                charge(ctx, 6);
                lw(v0, s1, 28);
                t0 = 0;
                v0 = addu(v0, a3);
                v0 = sll(v0, 1);
                t3 = addu(t3, v0);
                if (i64(t1) > 0) {
                    // 0x0053703c
                    charge(ctx, 1);
                    a3 = s2;
                    for (;;) {
                        // 0x00537040
                        charge(ctx, 17);
                        lhu(v0, a3, 0);
                        a0 = sll(t0, 1);
                        a1 = addu(a0, t2);
                        a0 = addu(a0, t3);
                        v1 = sll(v0, 8);
                        v0 = srl(v0, 8);
                        v0 = v0 | v1;
                        t0 = addiu(t0, 1);
                        sh(v0, a1, 0);
                        a2 = slt(t0, t1);
                        lhu(v0, a3, 2);
                        a3 = addiu(a3, 4);
                        v1 = sll(v0, 8);
                        v0 = srl(v0, 8);
                        v0 = v0 | v1;
                        sh(v0, a0, 0);
                        if (a2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00537084
                    charge(ctx, 2);
                    lbu(v1, s0, 14);
                }
            }
            // 0x005370c8
            charge(ctx, 8);
            v0 = sll(v1, 24);
            v1 = 2;
            v0 = sra(v0, 24);
            sw(v1, s0, 4);
            mult(v0, t1, v0);
            sw(t1, s0, 144);
            v0 = sll(v0, 1);
            sw(v0, s0, 148);
        }
    }
    // 0x005370e8
    charge(ctx, 3);
    v0 = 2;
    if (v1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005370f4
        charge(ctx, 8);
        lw(v1, s0, 128);
        lw(a0, s0, 132);
        lw(a1, s0, 148);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x537100u);  // $ra = the return address
        lw(a2, s0, 144);
        call_ptr(ctx, jt);
        v0 = 3;
        sw(v0, s0, 4);
        ld(s0, sp, 0x0);
    }
    // 0x00537114 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00537128 sub_537128 -- 384 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// AU decode step, 8-bit linear PCM.
void sub_537128(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00537128
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = addiu(s0, 72);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v1, s0, 4);
    lw(s2, s1, 0);
    if (v1 == v0) {
        // 0x00537154
        charge(ctx, 4);
        link(ctx, 0x537154u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 8);
        call(ctx, gen::fn_sub_54CD80_0054cd80);
        if (v0 != 0) {
            lw(v1, s0, 4);
        } else {
            // 0x00537164
            charge(ctx, 22);
            lw(a0, s0, 124);
            a1 = addiu(s0, 104);
            lw(v0, s0, 120);
            a2 = addiu(s0, 108);
            a3 = addiu(s0, 112);
            jalr(ctx, 0x537174u, v0.u());
            lw(a0, s1, 24);
            lw(t1, s1, 32);
            a2 = 2;
            lw(v1, s1, 36);
            t0 = subu(a0, t1);
            lb(a0, s0, 14);
            v0 = slt(v1, t0);
            lw(a1, s1, 4);
            if (v0 != 0) t0 = v1;
            v1 = sll(t1, 1);
            lw(t3, s1, 20);
            v0 = slt(a1, t0);
            if (v0 != 0) t0 = a1;
            t2 = addu(t3, v1);
            lbu(v1, s0, 14);
            if (a0 != a2) {
                // 0x00537218
                charge(ctx, 2);
                a3 = 0;
                if (i64(t0) > 0) {
                    // 0x00537220
                    charge(ctx, 2);
                    a1 = t2;
                    for (;;) {
                        // 0x00537228
                        charge(ctx, 8);
                        v0 = addu(s2, a3);
                        a3 = addiu(a3, 1);
                        lbu(v1, v0, 0);
                        a0 = slt(a3, t0);
                        v1 = sll(v1, 8);
                        sh(v1, a1, 0);
                        a1 = addiu(a1, 2);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00537248
                    charge(ctx, 1);
                    lbu(v1, s0, 14);
                }
            } else {
                // 0x005371bc
                charge(ctx, 6);
                lw(v0, s1, 28);
                a3 = 0;
                v0 = addu(v0, t1);
                v0 = sll(v0, 1);
                t1 = addu(t3, v0);
                if (i64(t0) > 0) {
                    // 0x005371d4
                    charge(ctx, 1);
                    a2 = s2;
                    for (;;) {
                        // 0x005371d8
                        charge(ctx, 13);
                        lbu(v0, a2, 0);
                        v1 = sll(a3, 1);
                        a0 = addu(v1, t2);
                        v1 = addu(v1, t1);
                        v0 = sll(v0, 8);
                        a3 = addiu(a3, 1);
                        sh(v0, a0, 0);
                        a1 = slt(a3, t0);
                        lbu(v0, a2, 1);
                        a2 = addiu(a2, 2);
                        v0 = sll(v0, 8);
                        sh(v0, v1, 0);
                        if (a1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0053720c
                    charge(ctx, 2);
                    lbu(v1, s0, 14);
                }
            }
            // 0x0053724c
            charge(ctx, 7);
            v0 = sll(v1, 24);
            v1 = 2;
            v0 = sra(v0, 24);
            sw(v1, s0, 4);
            mult(v0, t0, v0);
            sw(t0, s0, 144);
            sw(v0, s0, 148);
        }
    }
    // 0x00537268
    charge(ctx, 3);
    v0 = 2;
    if (v1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00537274
        charge(ctx, 8);
        lw(v1, s0, 128);
        lw(a0, s0, 132);
        lw(a1, s0, 148);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x537280u);  // $ra = the return address
        lw(a2, s0, 144);
        call_ptr(ctx, jt);
        v0 = 3;
        sw(v0, s0, 4);
        ld(s0, sp, 0x0);
    }
    // 0x00537294 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005372A8 sub_5372A8 -- 424 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// AU decode step, 8-bit mu-law through the table at 0x7836C8.
void sub_5372A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005372a8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = addiu(s0, 72);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v1, s0, 4);
    lw(s2, s1, 0);
    if (v1 == v0) {
        // 0x005372d4
        charge(ctx, 4);
        link(ctx, 0x5372D4u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 8);
        call(ctx, gen::fn_sub_54CD80_0054cd80);
        if (v0 != 0) {
            lw(v1, s0, 4);
        } else {
            // 0x005372e4
            charge(ctx, 22);
            lw(a0, s0, 124);
            a1 = addiu(s0, 104);
            lw(v0, s0, 120);
            a2 = addiu(s0, 108);
            a3 = addiu(s0, 112);
            jalr(ctx, 0x5372F4u, v0.u());
            lw(a0, s1, 24);
            lw(a3, s1, 32);
            a2 = 2;
            lw(v1, s1, 36);
            t1 = subu(a0, a3);
            lb(a0, s0, 14);
            v0 = slt(v1, t1);
            lw(a1, s1, 4);
            if (v0 != 0) t1 = v1;
            v1 = sll(a3, 1);
            lw(t2, s1, 20);
            v0 = slt(a1, t1);
            if (v0 != 0) t1 = a1;
            t3 = addu(t2, v1);
            lbu(v1, s0, 14);
            if (a0 != a2) {
                // 0x005373b0
                charge(ctx, 2);
                t0 = 0;
                if (i64(t1) > 0) {
                    // 0x005373b8
                    charge(ctx, 4);
                    v0 = 0x780000;
                    a1 = t3;
                    a2 = addiu(v0, 14024);  // &0x7836C8
                    for (;;) {
                        // 0x005373c8
                        charge(ctx, 10);
                        v1 = addu(s2, t0);
                        t0 = addiu(t0, 1);
                        lbu(v0, v1, 0);
                        a0 = slt(t0, t1);
                        v0 = sll(v0, 1);
                        v0 = addu(v0, a2);
                        lhu(v1, v0, 0);
                        sh(v1, a1, 0);
                        a1 = addiu(a1, 2);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x005373f0
                    charge(ctx, 1);
                    lbu(v1, s0, 14);
                }
            } else {
                // 0x0053733c
                charge(ctx, 6);
                lw(v0, s1, 28);
                t0 = 0;
                v0 = addu(v0, a3);
                v0 = sll(v0, 1);
                t4 = addu(t2, v0);
                if (i64(t1) > 0) {
                    // 0x00537354
                    charge(ctx, 3);
                    v0 = 0x780000;
                    a3 = s2;
                    t2 = addiu(v0, 14024);  // &0x7836C8
                    for (;;) {
                        // 0x00537360
                        charge(ctx, 17);
                        lbu(v0, a3, 0);
                        a0 = sll(t0, 1);
                        a1 = addu(a0, t3);
                        a0 = addu(a0, t4);
                        v0 = sll(v0, 1);
                        t0 = addiu(t0, 1);
                        v0 = addu(v0, t2);
                        a2 = slt(t0, t1);
                        lhu(v1, v0, 0);
                        sh(v1, a1, 0);
                        lbu(v0, a3, 1);
                        a3 = addiu(a3, 2);
                        v0 = sll(v0, 1);
                        v0 = addu(v0, t2);
                        lhu(v1, v0, 0);
                        sh(v1, a0, 0);
                        if (a2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x005373a4
                    charge(ctx, 2);
                    lbu(v1, s0, 14);
                }
            }
            // 0x005373f4
            charge(ctx, 7);
            v0 = sll(v1, 24);
            v1 = 2;
            v0 = sra(v0, 24);
            sw(v1, s0, 4);
            mult(v0, t1, v0);
            sw(t1, s0, 144);
            sw(v0, s0, 148);
        }
    }
    // 0x00537410
    charge(ctx, 3);
    v0 = 2;
    if (v1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0053741c
        charge(ctx, 8);
        lw(v1, s0, 128);
        lw(a0, s0, 132);
        lw(a1, s0, 148);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x537428u);  // $ra = the return address
        lw(a2, s0, 144);
        call_ptr(ctx, jt);
        v0 = 3;
        sw(v0, s0, 4);
        ld(s0, sp, 0x0);
    }
    // 0x0053743c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00537450 sub_537450 -- 64 bytes; frame 0x10: ra sp+0x0
// AU decode dispatch on the encoding kind (+156): 2 mu-law, 1 8-bit, else 16-bit.
void sub_537450(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00537450
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 2;
    sd(ra, sp, 0x0);
    lh(v1, a0, 156);
    cc = v1 != v0;  // the condition, before the delay slot changes it
    v0 = 1;
    if (!cc) {
        // 0x00537468
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_sub_5372A8_005372a8(ctx);  // tail call
        return;
    }
    // 0x00537478
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    if (v1 != v0) {
        // 0x00537488
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        gen::fn_sub_536F90_00536f90(ctx);  // tail call
        return;
    }
    // 0x00537480
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
    gen::fn_sub_537128_00537128(ctx);  // tail call
}

// =====================================================================================================================
// ADXB: the ADX key derivation, handle getters, the ADX decode steps
// =====================================================================================================================

// 0x005374E8 sub_5374E8 -- 28 bytes; leaf frame (no stack)
// Increments the key-table init count (0x7838CC); returns 0.
void sub_5374E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x005374e8
    enter(ctx, 7);  // entry check point + this block's cycles
    a0 = 0x780000;
    v0 = 0;
    a0 = addiu(a0, 14540);  // &0x7838CC
    lw(v1, a0, 0);  // 0x7838CC
    v1 = addiu(v1, 1);
    sw(v1, a0, 0);  // 0x7838CC
}

// 0x00537508 sub_537508 -- 28 bytes; leaf frame (no stack)
// Decrements the key-table init count (0x7838CC); returns 0.
void sub_537508(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00537508
    enter(ctx, 7);  // entry check point + this block's cycles
    a0 = 0x780000;
    v0 = 0;
    a0 = addiu(a0, 14540);  // &0x7838CC
    lw(v1, a0, 0);  // 0x7838CC
    v1 = addiu(v1, -1);
    sw(v1, a0, 0);  // 0x7838CC
}

// 0x00537528 sub_537528 -- 436 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// ADX key derivation from a pass phrase: hashes the bytes through the prime tables at 0x7C11B8.. into three 16-bit
// keys (k0, km, ka); all zero for an empty phrase.
void sub_537528(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00537528
    enter(ctx, 15);  // entry check point + this block's cycles
    v0 = 0x780000;
    sp = addiu(sp, -0x30);
    lw(v1, v0, 14540);  // 0x7838CC
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    s4 = t0;
    sd(ra, sp, 0x28);
    if (v1 == 0) {
        // 0x00537564
        charge(ctx, 2);
        jal(ctx, 0x537564u, gen::fn_sub_5374E8_005374e8);
    }
    // 0x0053756c
    charge(ctx, 4);
    sh(zero, s2, 0);
    sh(zero, s3, 0);
    sh(zero, s4, 0);
    if (s1 == 0) {
        // 0x0053757c
        charge(ctx, 2);
        v0 = 0;
        if (i64(s0) > 0) {
            goto L_00537584;
        }
        // 0x005376bc (the shared epilogue, written out on this path)
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
L_00537584:
    charge(ctx, 5);
    t3 = 0x7C0000;
    a3 = 0;
    v0 = addiu(t3, 4536);  // &0x7C11B8
    lh(t2, v0, 512);  // 0x7C13B8
    if (i64(s0) > 0) {
        // 0x00537598
        charge(ctx, 2);
        t0 = v0;
        for (;;) {
            // 0x005375a0
            charge(ctx, 19);
            v1 = addu(s1, a3);
            a3 = addiu(a3, 1);
            lb(v0, v1, 0);
            a2 = slt(a3, s0);
            v0 = sll(v0, 1);
            v0 = addu(v0, t0);
            lh(v1, v0, 256);
            mult(v1, t2, v1);
            a1 = addiu(v1, 1023);
            a0 = slti(v1, 0);
            v0 = v1;
            if (a0 != 0) v0 = a1;
            v0 = sra(v0, 10);
            v0 = sll(v0, 10);
            v1 = subu(v1, v0);
            v1 = sll(v1, 1);
            v1 = addu(v1, t0);
            lh(t2, v1, 0);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005375ec
        charge(ctx, 2);
        v0 = addiu(t3, 4536);
        a3 = 0;
    }
    // 0x005375f4
    charge(ctx, 2);
    lh(t0, v0, 1024);
    if (i64(s0) > 0) {
        // 0x005375fc
        charge(ctx, 1);
        t1 = v0;
        for (;;) {
            // 0x00537600
            charge(ctx, 19);
            v1 = addu(s1, a3);
            a3 = addiu(a3, 1);
            lb(v0, v1, 0);
            a2 = slt(a3, s0);
            v0 = sll(v0, 1);
            v0 = addu(v0, t1);
            lh(v1, v0, 256);
            mult(v1, t0, v1);
            a1 = addiu(v1, 1023);
            a0 = slti(v1, 0);
            v0 = v1;
            if (a0 != 0) v0 = a1;
            v0 = sra(v0, 10);
            v0 = sll(v0, 10);
            v1 = subu(v1, v0);
            v1 = sll(v1, 1);
            v1 = addu(v1, t1);
            lh(t0, v1, 0);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0053764c
    charge(ctx, 4);
    v0 = addiu(t3, 4536);
    a3 = 0;
    lh(a0, v0, 1536);
    if (i64(s0) > 0) {
        // 0x0053765c
        charge(ctx, 1);
        t1 = v0;
        for (;;) {
            // 0x00537660
            charge(ctx, 19);
            v1 = addu(s1, a3);
            a3 = addiu(a3, 1);
            lb(v0, v1, 0);
            a2 = slt(a3, s0);
            v0 = sll(v0, 1);
            v0 = addu(v0, t1);
            lh(v1, v0, 256);
            mult(v1, a0, v1);
            a0 = slti(v1, 0);
            a1 = addiu(v1, 1023);
            v0 = v1;
            if (a0 != 0) v0 = a1;
            v0 = sra(v0, 10);
            v0 = sll(v0, 10);
            v1 = subu(v1, v0);
            v1 = sll(v1, 1);
            v1 = addu(v1, t1);
            lh(a0, v1, 0);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x005376ac
    charge(ctx, 4);
    sh(t2, s2, 0);
    v0 = 0;
    sh(t0, s3, 0);
    sh(a0, s4, 0);
    // 0x005376bc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00537808 sub_537808 -- 48 bytes; leaf frame (no stack)
// Decoder method (data ref): the output position, the space before the wrap, the remaining samples.
void sub_537808(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00537808
    enter(ctx, 12);  // entry check point + this block's cycles
    lw(t0, a0, 140);
    lw(v0, a0, 60);
    sw(t0, a1, 0);
    lw(a1, a0, 140);
    lw(v1, a0, 64);
    v1 = subu(v1, a1);
    sw(v1, a2, 0);
    lw(a1, a0, 24);
    lw(v1, a0, 136);
    a1 = subu(a1, v1);
    sw(a1, a3, 0);
}

// 0x00537838 sub_537838 -- 28 bytes; leaf frame (no stack)
// Decoder method (data ref): advances the written / total sample counters (+140, +136) by a2.
void sub_537838(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6};
    // 0x00537838
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v0, a0, 140);
    lw(v1, a0, 136);
    v0 = addu(v0, a2);
    v1 = addu(v1, a2);
    sw(v0, a0, 140);
    sw(v1, a0, 136);
}

// 0x00537858 sub_537858 -- 56 bytes; frame 0x10: ra sp+0x0
// Resets the handle's AHX / filter state: +228 = -128, +226 = -128, +224 = 0, +204 = 0, and 16 bytes at +208.
void sub_537858(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00537858
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    v1 = si(-128);
    a0 = addiu(v0, 208);
    a1 = 0;
    ld(ra, sp, 0x0);
    a2 = 16;
    sh(v1, v0, 228);
    sw(zero, v0, 204);
    sh(zero, v0, 224);
    sh(v1, v0, 226);
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x005379F8 sub_5379F8 -- 748 bytes; frame 0xA0: s0 sp+0x50, s1 sp+0x58, s2 sp+0x60, s3 sp+0x68, s4 sp+0x70, s5 sp+0x78, s6 sp+0x80, s7 sp+0x88, fp sp+0x90, ra sp+0x98, s4 sp+0x0, s7 sp+0x8
// ADX header decode into an ADXB handle: format, block size, bits, channels, rate, frames, loop info, the encryption
// keys (sub_5381C0); refuses AHX data on a handle without AHX ('E1060101').
// [proposed name] ADXB_DecodeHeaderAdx: the function's own error text names it.
void sub_5379F8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005379f8
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    v0 = 1;
    sd(s0, sp, 0x50);
    s0 = a0;
    sd(s1, sp, 0x58);
    s1 = a1;
    sd(s2, sp, 0x60);
    s2 = a2;
    sd(s3, sp, 0x68);
    s3 = addiu(s0, 12);
    sd(s4, sp, 0x70);
    s4 = addiu(s0, 24);
    sd(s5, sp, 0x78);
    s5 = addiu(s0, 13);
    sd(s6, sp, 0x80);
    s6 = addiu(s0, 14);
    sd(s7, sp, 0x88);
    s7 = addiu(s0, 16);
    sd(fp, sp, 0x90);
    fp = addiu(s0, 0xF);
    sd(ra, sp, 0x98);
    a2 = addiu(sp, 0x40);
    sh(v0, s0, 2);
    v0 = addiu(s0, 20);
    a0 = s1;
    a1 = s2;
    a3 = s3;
    t0 = s5;
    t1 = fp;
    t2 = s6;
    t3 = v0;
    sw(v0, sp, 0x4C);
    sw(s4, sp, 0x0);
    link(ctx, 0x537A7Cu);  // $ra first: the delay slot below depends on it
    sw(s7, sp, 0x8);
    call(ctx, gen::fn_sub_539AE0_00539ae0);
    cc = i64(v0) < 0;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x00537a8c
        charge(ctx, 4);
        lb(v0, s3, 0);
        v0 = slti(v0, 5);
        a0 = s1;
        if (v0 != 0) {
            // 0x00537b80
            charge(ctx, 6);
            a1 = s2;
            a2 = addiu(sp, 0x42);
            a3 = addiu(sp, 0x43);
            jal(ctx, 0x537B88u, gen::fn_sub_539C60_00539c60);
            a0 = s0;
            if (i64(v0) < 0) {
            L_00537c04:
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x00537b98
                charge(ctx, 9);
                lw(a3, s4, 0);
                lbu(a1, sp, 0x42);
                t0 = addiu(sp, 0x44);
                lbu(a2, sp, 0x43);
                t1 = addiu(sp, 0x46);
                t2 = addiu(sp, 0x48);
                jal(ctx, 0x537BACu, gen::fn_sub_5381C0_005381c0);
                s3 = addiu(s0, 28);
                if (i64(v0) < 0) {
                    backedge(ctx);
                L_00537abc:
                    charge(ctx, 2);
                    v0 = si(-1);
                } else {
                    // 0x00537bbc
                    charge(ctx, 11);
                    lw(a0, s0, 8);
                    lh(a1, sp, 0x44);
                    lh(a2, sp, 0x46);
                    link(ctx, 0x537BC8u);  // $ra first: the delay slot below depends on it
                    lh(a3, sp, 0x48);
                    call(ctx, gen::fn_sub_54CD10_0054cd10);
                    a0 = s1;
                    a1 = s2;
                    a2 = s3;
                    jal(ctx, 0x537BD8u, gen::fn_sub_539BE0_00539be0);
                    s4 = addiu(sp, 0x20);
                    if (i64(v0) < 0) {
                        goto L_00537c04;
                    }
                    // 0x00537be8
                    charge(ctx, 7);
                    a0 = s1;
                    a1 = s2;
                    a2 = addiu(sp, 0x10);
                    a3 = s4;
                    jal(ctx, 0x537BF4u, gen::fn_sub_539CD8_00539cd8);
                    if (i64(v0) < 0) {
                        goto L_00537c04;
                    }
                    lw(v0, sp, 0x4C);
                    // 0x00537c10
                    charge(ctx, 28);
                    lh(a2, s3, 0);
                    lw(a1, v0, 0);
                    link(ctx, 0x537C18u);  // $ra first: the delay slot below depends on it
                    lw(a0, s0, 8);
                    call(ctx, gen::fn_sub_54CC98_0054cc98);
                    lw(a0, s0, 8);
                    a1 = addiu(sp, 0x10);
                    a2 = s4;
                    jal(ctx, 0x537C28u, gen::fn_sub_54CCC0_0054ccc0);
                    v0 = addiu(s0, 52);
                    a2 = addiu(s0, 32);
                    a3 = addiu(s0, 36);
                    t0 = addiu(s0, 38);
                    t1 = addiu(s0, 40);
                    t2 = addiu(s0, 44);
                    t3 = addiu(s0, 48);
                    a0 = s1;
                    a1 = s2;
                    link(ctx, 0x537C54u);  // $ra first: the delay slot below depends on it
                    sw(v0, sp, 0x0);
                    call(ctx, gen::fn_sub_539ED8_00539ed8);
                    a0 = s1;
                    a1 = s2;
                    a2 = addiu(s0, 204);
                    a3 = addiu(s0, 208);
                    t0 = addiu(s0, 224);
                    t1 = addiu(s0, 226);
                    jal(ctx, 0x537C70u, gen::fn_sub_53A138_0053a138);
                    sh(zero, s0, 152);
                    lb(v0, s0, 14);
                L_00537c80:
                    charge(ctx, 13);
                    lb(v1, s0, 15);
                    lw(a0, s0, 16);
                    lw(a1, s0, 60);
                    lw(a2, s0, 64);
                    lw(a3, s0, 68);
                    sw(v0, s0, 80);
                    sw(v1, s0, 84);
                    sw(a0, s0, 88);
                    sw(a1, s0, 92);
                    sw(a2, s0, 96);
                    sw(a3, s0, 100);
                    sw(zero, s0, 140);
                    lh(v0, sp, 0x40);
                }
            }
        } else {
            // 0x00537a9c
            charge(ctx, 3);
            lw(v0, s0, 180);
            if (v0 == 0) {
                // 0x00537aa8
                charge(ctx, 5);
                a0 = 0x7C0000;
                a1 = 0x7C0000;
                a0 = addiu(a0, 6592);  // "E1060101 ADXB_DecodeHeaderAdx: "
                a1 = addiu(a1, 6624);  // "can't play AHX data by this handle"
                jal(ctx, 0x537AB4u, gen::fn_sub_53AE60_0053ae60);
                goto L_00537abc;
            }
            v0 = 8;
            // 0x00537ac8
            charge(ctx, 26);
            t1 = 96;
            sb(v0, s5, 0);
            t0 = 10;
            a0 = s1;
            a1 = s2;
            lb(v1, s6, 0);
            a2 = addiu(sp, 0x42);
            a3 = addiu(sp, 0x43);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 6);
            sb(v0, fp, 0x0);
            sw(t1, s7, 0);
            sh(t0, s0, 152);
            sh(zero, s0, 28);
            sh(zero, s0, 36);
            sh(zero, s0, 38);
            sw(zero, s0, 32);
            sw(zero, s0, 40);
            sw(zero, s0, 44);
            sw(zero, s0, 48);
            sw(zero, s0, 52);
            link(ctx, 0x537B20u);  // $ra first: the delay slot below depends on it
            sw(zero, s0, 136);
            call(ctx, gen::fn_sub_539C60_00539c60);
            a0 = s0;
            if (i64(v0) < 0) {
                goto L_00537c04;
            }
            // 0x00537b30
            charge(ctx, 10);
            lw(a3, s4, 0);
            lbu(a1, sp, 0x42);
            t0 = addiu(sp, 0x32);
            lbu(a2, sp, 0x43);
            t1 = addiu(sp, 0x34);
            t2 = addiu(sp, 0x36);
            link(ctx, 0x537B48u);  // $ra first: the delay slot below depends on it
            sh(zero, sp, 0x30);
            call(ctx, gen::fn_sub_5381C0_005381c0);
            cc = i64(v0) < 0;  // the condition, before the delay slot changes it
            v0 = si(-1);
            if (!cc) {
                // 0x00537b58
                charge(ctx, 4);
                v0 = 0x780000;
                lw(v0, v0, 14552);  // 0x7838D8
                if (v0 == 0) {
                    lb(v0, s0, 14);
                } else {
                    // 0x00537b68
                    charge(ctx, 5);
                    lw(a0, s0, 180);
                    a1 = addiu(sp, 0x30);
                    jalr(ctx, 0x537B6Cu, v0.u());
                    lb(v0, s0, 14);
                }
                goto L_00537c80;
            }
        }
    }
    // 0x00537cb4 (the shared epilogue, written out on this path)
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

// 0x00537F70 sub_537F70 -- 8 bytes; leaf frame (no stack)
// Getter: the channel count (s8 at +13).
void sub_537F70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00537f70
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, 13);
}

// 0x00537FE0 sub_537FE0 -- 8 bytes; leaf frame (no stack)
// Getter: the s8 at +15 (bits per sample).
void sub_537FE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00537fe0
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, 15);
}

// 0x00537FF0 sub_537FF0 -- 8 bytes; leaf frame (no stack)
// Getter: the s16 at +28.
void sub_537FF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00537ff0
    enter(ctx, 2);  // entry check point + this block's cycles
    lh(v0, a0, 28);
}

// 0x00537FF8 sub_537FF8 -- 8 bytes; leaf frame (no stack)
// Getter: the s32 at +32 (decoded samples).
void sub_537FF8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00537ff8
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 32);
}

// 0x00538058 sub_538058 -- 8 bytes; leaf frame (no stack)
// Getter: the address of the 16-byte block at +208.
void sub_538058(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00538058
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = addiu(a0, 208);
}

// 0x005380A0 sub_5380A0 -- 64 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Pushes the handle's key words (+166..+170) and positions into the ADX decoder (sub_54CCC0, sub_54CD10).
void sub_5380A0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005380a0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    a1 = addiu(s0, 172);
    a2 = addiu(s0, 176);
    link(ctx, 0x5380B8u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 8);
    call(ctx, gen::fn_sub_54CCC0_0054ccc0);
    lw(a0, s0, 8);
    lh(a3, s0, 170);
    lh(a1, s0, 166);
    lh(a2, s0, 168);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_54CD10_0054cd10(ctx);  // tail call
}

// 0x005380E0 sub_5380E0 -- 100 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// Sets the handle's keys (+160..+164) from a pass phrase (strlen + sub_537528).
void sub_5380E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005380e0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(ra, sp, 0x20);
    a0 = s0;
    jal(ctx, 0x5380F8u, gen::fn_strlen_00524388);
    a0 = s0;
    a1 = v0;
    a2 = sp;
    a3 = addiu(sp, 0x2);
    t0 = addiu(sp, 0x4);
    jal(ctx, 0x538110u, gen::fn_sub_537528_00537528);
    lhu(v1, sp, 0x0);
    lhu(a0, sp, 0x2);
    lhu(v0, sp, 0x4);
    ld(s0, sp, 0x10);
    sh(v1, s1, 160);
    sh(v0, s1, 164);
    sh(a0, s1, 162);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x18);
    sp = addiu(sp, 0x30);
}

// 0x00538148 sub_538148 -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Sets the default keys (0x7838E4..E8) from a pass phrase.
void sub_538148(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00538148
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x538154u, gen::fn_strlen_00524388);
    ld(ra, sp, 0x8);
    a0 = s0;
    a2 = 0x780000;
    a3 = 0x780000;
    t0 = 0x780000;
    ld(s0, sp, 0x0);
    a1 = v0;
    a2 = addiu(a2, 14564);  // &0x7838E4
    a3 = addiu(a3, 14566);  // &0x7838E6
    t0 = addiu(t0, 14568);  // &0x7838E8
    sp = addiu(sp, 0x10);
    gen::fn_sub_537528_00537528(ctx);  // tail call
}

// 0x005381C0 sub_5381C0 -- 256 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// Keys from the header's key code: below version 4 none; from 16 on, the code as "%08X" through sub_537528; else the
// default keys.
void sub_5381C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005381c0
    enter(ctx, 13);  // entry check point + this block's cycles
    a1 = a1 & 0xFF;
    sp = addiu(sp, -0x30);
    a1 = sltiu(a1, 4);
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    s1 = t1;
    sd(s2, sp, 0x20);
    s2 = t2;
    sd(ra, sp, 0x28);
    t3 = a0;
    s0 = t0;
    a2 = a2 & 0xFF;
    if (a1 != 0) {
        // 0x00538298
        charge(ctx, 1);
        sh(zero, s0, 0);
    L_0053829c:
        charge(ctx, 2);
        sh(zero, s1, 0);
        sh(zero, s2, 0);
    L_005382a4:
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    } else {
        // 0x005381f4
        charge(ctx, 3);
        v0 = sltiu(a2, 16);
        if (v0 != 0) {
            v0 = sltiu(a2, 8);
            // 0x00538238
            charge(ctx, 2);
            if (v0 != 0) {
                sh(zero, s0, 0);
                goto L_0053829c;
            }
            // 0x00538240
            charge(ctx, 3);
            lw(v0, t3, 160);
            if (v0 != 0) {
                lhu(v0, t3, 160);
            } else {
                // 0x0053824c
                charge(ctx, 3);
                lh(v0, t3, 164);
                if (v0 != 0) {
                    lhu(v0, t3, 160);
                } else {
                    // 0x00538258
                    charge(ctx, 10);
                    v0 = 0x780000;
                    a0 = 0x780000;
                    lhu(v1, v0, 14564);  // 0x7838E4
                    a1 = 0x780000;
                    sh(v1, t3, 160);
                    lhu(v0, a0, 14566);  // 0x7838E6
                    sh(v0, t3, 162);
                    lhu(v1, a1, 14568);  // 0x7838E8
                    sh(v1, t3, 164);
                    lhu(v0, t3, 160);
                }
            }
            // 0x00538280
            charge(ctx, 6);
            sh(v0, s0, 0);
            lhu(v1, t3, 162);
            sh(v1, s1, 0);
            lhu(v0, t3, 164);
            sh(v0, s2, 0);
            goto L_005382a4;
        }
        // 0x00538200
        charge(ctx, 13);
        a1 = 0x7C0000;
        a2 = a3;
        a1 = addiu(a1, 6664);  // "%08X"
        a0 = sp;
        jal(ctx, 0x53820Cu, gen::fn_sprintf_00523ac8);
        a1 = 8;
        a0 = sp;
        a2 = s0;
        a3 = s1;
        t0 = s2;
        jal(ctx, 0x538224u, gen::fn_sub_537528_00537528);
        ld(s0, sp, 0x10);
    }
    // 0x005382a8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 0;
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00538410 sub_538410 -- 104 bytes, 2 chunks; frame 0x10: ra sp+0x8, s0 sp+0x0
// ADX decode, mono: one channel into the output ring (sub_54CD88); marks the decoder started.
void sub_538410(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00538410
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = addiu(a0, 72);
    sd(ra, sp, 0x8);
    a2 = a1;
    sd(s0, sp, 0x0);
    t0 = 0;
    lw(a3, v0, 32);
    lw(s0, a0, 8);
    lw(v1, v0, 20);
    a3 = sll(a3, 1);
    lw(a1, v0, 0);
    a0 = s0;
    a3 = addu(v1, a3);
    jal(ctx, 0x538440u, gen::fn_sub_54CD88_0054cd88);
    a0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0054ce18
    charge(ctx, 3);
    lw(v0, a0, 12);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 1;
    if (!cc) {
        // 0x0054ce24
        charge(ctx, 2);
        sw(zero, a0, 16);
        sw(v0, a0, 12);
    }
    // 0x0054ce2c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00538460 sub_538460 -- 116 bytes, 2 chunks; frame 0x10: ra sp+0x8, s0 sp+0x0
// ADX decode, stereo interleaved (sub_54CDB8).
void sub_538460(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00538460
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = addiu(a0, 72);
    sd(ra, sp, 0x8);
    a1 = sll(a1, 1);
    sd(s0, sp, 0x0);
    a2 = a1;
    lw(v0, v1, 32);
    lw(a3, v1, 20);
    lw(t0, v1, 28);
    v0 = sll(v0, 1);
    lw(s0, a0, 8);
    a3 = addu(a3, v0);
    lw(a1, v1, 0);
    t0 = sll(t0, 1);
    a0 = s0;
    t0 = addu(a3, t0);
    jal(ctx, 0x53849Cu, gen::fn_sub_54CDB8_0054cdb8);
    a0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0054ce18
    charge(ctx, 3);
    lw(v0, a0, 12);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 1;
    if (!cc) {
        // 0x0054ce24
        charge(ctx, 2);
        sw(zero, a0, 16);
        sw(v0, a0, 12);
    }
    // 0x0054ce2c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005384B8 sub_5384B8 -- 112 bytes, 2 chunks; frame 0x10: ra sp+0x8, s0 sp+0x0
// ADX decode, stereo split (sub_54CDE8).
void sub_5384B8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005384b8
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = addiu(a0, 72);
    sd(ra, sp, 0x8);
    a2 = a1;
    sd(s0, sp, 0x0);
    lw(v0, v1, 32);
    lw(a3, v1, 20);
    lw(t0, v1, 28);
    v0 = sll(v0, 1);
    lw(s0, a0, 8);
    a3 = addu(a3, v0);
    lw(a1, v1, 0);
    t0 = sll(t0, 1);
    a0 = s0;
    t0 = addu(a3, t0);
    jal(ctx, 0x5384F0u, gen::fn_sub_54CDE8_0054cde8);
    a0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0054ce18
    charge(ctx, 3);
    lw(v0, a0, 12);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 1;
    if (!cc) {
        // 0x0054ce24
        charge(ctx, 2);
        sw(zero, a0, 16);
        sw(v0, a0, 12);
    }
    // 0x0054ce2c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00538510 sub_538510 -- 260 bytes; frame 0x10: ra sp+0x0
// ADX decode dispatch: stereo (+80 == 2) or the split flag (+232), else mono; traps on a zero channel count or block
// size.
void sub_538510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00538510
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t8 = a0;
    sd(ra, sp, 0x0);
    a1 = addiu(t8, 72);
    lw(t6, a1, 8);
    lw(a2, a1, 4);
    if (t6 == 0) {
        brk(ctx, 0x53852Cu, 0x7u);
    }
    // 0x00538530
    charge(ctx, 26);
    lw(t7, a1, 24);
    div(a2, t6);
    lw(t0, a1, 32);
    lw(t1, a1, 16);
    v0 = subu(t7, t0);
    lw(a3, a1, 40);
    v0 = addu(v0, t1);
    v0 = addiu(v0, -1);
    v1 = addu(a3, t1);
    v1 = addiu(v1, -1);
    lw(t4, a1, 36);
    a3 = slt(a3, t4);
    mflo(a2);
    div(v0, t1);
    t2 = a2;
    mflo(v0);
    div(v1, t1);
    t3 = v0;
    mflo(t5);
    mfhi(a1);
    mult(v1, t3, t1);
    a1 = subu(t1, a1);
    v0 = slt(t5, t3);
    a1 = addiu(a1, -1);
    t0 = addu(t0, v1);
    if (v0 != 0) {
        // 0x00538598
        charge(ctx, 3);
        v0 = subu(t0, a1);
        v0 = slt(v0, t7);
        t3 = addu(t3, v0);
    }
    // 0x005385a4
    charge(ctx, 4);
    mult(v0, a3, a1);
    a2 = 2;
    if (t1 == 0) {
        brk(ctx, 0x5385B0u, 0x7u);
    }
    // 0x005385b4
    charge(ctx, 10);
    t4 = addu(v0, t4);
    div(t4, t1);
    mflo(a1);
    v0 = slt(a1, t2);
    if (v0 != 0) t2 = a1;
    v1 = slt(t5, t2);
    if (v1 != 0) t2 = t5;
    v0 = slt(t3, t2);
    if (v0 != 0) t2 = t3;
    if (t6 == a2) {
        // 0x005385dc
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        a1 = t2;
        sp = addiu(sp, 0x10);
        gen::fn_sub_538460_00538460(ctx);  // tail call
        return;
    }
    // 0x005385f0
    charge(ctx, 3);
    lw(v0, t8, 232);
    ld(ra, sp, 0x0);
    if (v0 == 0) {
        // 0x00538608
        charge(ctx, 3);
        a1 = t2;
        sp = addiu(sp, 0x10);
        gen::fn_sub_538410_00538410(ctx);  // tail call
        return;
    }
    // 0x005385fc
    charge(ctx, 3);
    a1 = t2;
    sp = addiu(sp, 0x10);
    gen::fn_sub_5384B8_005384b8(ctx);  // tail call
}

// 0x00538618 sub_538618 -- 44 bytes; leaf frame (no stack)
// Copies n halfwords from src to dst (n <= 0: nothing).
void sub_538618(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00538618
    enter(ctx, 2);  // entry check point + this block's cycles
    if (i64(a2) > 0) {
        for (;;) {
            // 0x00538620
            charge(ctx, 7);
            lhu(v0, a1, 0);
            a1 = addiu(a1, 2);
            a2 = addiu(a2, -1);
            sh(v0, a0, 0);
            a0 = addiu(a0, 2);
            if (i64(a2) <= 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0053863c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00538648 sub_538648 -- 108 bytes; frame 0x30: s2 sp+0x10, s1 sp+0x8, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// Moves two channel runs back to the start of the ring (two sub_538618 copies).
void sub_538648(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00538648
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    s3 = a3;
    a1 = sll(s2, 1);
    sd(s0, sp, 0x0);
    a1 = addu(s1, a1);
    s0 = a2;
    sd(ra, sp, 0x20);
    a2 = s3;
    jal(ctx, 0x538678u, gen::fn_sub_538618_00538618);
    a0 = sll(s0, 1);
    s0 = addu(s0, s2);
    ld(s2, sp, 0x10);
    s0 = sll(s0, 1);
    a0 = addu(s1, a0);
    a1 = addu(s1, s0);
    ld(s0, sp, 0x0);
    a2 = s3;
    ld(s3, sp, 0x18);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_538618_00538618(ctx);  // tail call
}

// 0x005386B8 sub_5386B8 -- 32 bytes; frame 0x10: ra sp+0x0
// Moves one channel run back to the start of the ring (sub_538618).
void sub_5386B8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005386b8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = sll(a1, 1);
    sd(ra, sp, 0x0);
    a2 = a3;
    a1 = addu(a0, a1);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_538618_00538618(ctx);  // tail call
}

// 0x005386D8 sub_5386D8 -- 392 bytes; frame 0x60: s0 sp+0x10, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, s6 sp+0x40, fp sp+0x50, s1 sp+0x18, s2 sp+0x20, s7 sp+0x48, ra sp+0x58
// ADX decode completion: converts the decoded blocks into samples, folds the wrapped tail back (sub_538648 /
// sub_5386B8) and updates the counters.
void sub_5386D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005386d8
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s0, sp, 0x10);
    sd(s3, sp, 0x28);
    sd(s4, sp, 0x30);
    sd(s5, sp, 0x38);
    sd(s6, sp, 0x40);
    s6 = a0;
    sd(fp, sp, 0x50);
    s4 = addiu(s6, 72);
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    sd(s7, sp, 0x48);
    sd(ra, sp, 0x58);
    lw(s1, s4, 16);
    lw(s2, s4, 40);
    if (s1 == 0) {
        brk(ctx, 0x538718u, 0x7u);
    }
    // 0x0053871c
    charge(ctx, 21);
    s2 = addu(s2, s1);
    lw(v0, s6, 68);
    s2 = addiu(s2, -1);
    lw(s7, s6, 64);
    div(s2, s1);
    lw(a0, s6, 8);
    lw(fp, s4, 20);
    sw(v0, sp, 0x0);
    lw(s3, s4, 12);
    mfhi(s0);
    mflo(s2);
    link(ctx, 0x538748u);  // $ra first: the delay slot below depends on it
    lw(s5, s4, 32);
    call(ctx, gen::fn_sub_54CE78_0054ce78);
    lw(v1, s4, 8);
    s0 = subu(s1, s0);
    mult(s1, v0, s1);
    mult(s2, s2, v1);
    s0 = addiu(s0, -1);
    mult1(s3, v0, s3);
    if (v1 == 0) {
        brk(ctx, 0x53876Cu, 0x7u);
    }
    // 0x00538770
    charge(ctx, 12);
    a0 = 2;
    div(s1, v1);
    v0 = slt(v0, s2);
    sw(s3, s6, 148);
    mflo(s1);
    s0 = subu(s1, s0);
    if (v0 != 0) s0 = s1;
    s5 = addu(s5, s0);
    sw(s0, s6, 144);
    v0 = slt(s5, s7);
    s5 = subu(s5, s7);
    if (v0 != 0) {
        // 0x00538830
        charge(ctx, 12);
        ld(s0, sp, 0x10);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(s3, sp, 0x28);
        ld(s4, sp, 0x30);
        ld(s5, sp, 0x38);
        ld(s6, sp, 0x40);
        ld(s7, sp, 0x48);
        ld(fp, sp, 0x50);
        ld(ra, sp, 0x58);
        sp = addiu(sp, 0x60);
        return;
    }
    // 0x005387a0
    charge(ctx, 3);
    v0 = v1;
    cc = v0 == a0;  // the condition, before the delay slot changes it
    a0 = fp;
    if (!cc) {
        // 0x005387ac
        charge(ctx, 3);
        lw(v0, s6, 232);
        ld(fp, sp, 0x50);
        if (v0 != 0) {
            goto L_005387b8;
        }
        // 0x005387f8
        charge(ctx, 14);
        a1 = s7;
        ld(s7, sp, 0x48);
        a3 = s5;
        ld(s5, sp, 0x38);
        lw(a2, sp, 0x0);
        ld(s0, sp, 0x10);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(s3, sp, 0x28);
        ld(s4, sp, 0x30);
        ld(s6, sp, 0x40);
        ld(ra, sp, 0x58);
        sp = addiu(sp, 0x60);
        gen::fn_sub_5386B8_005386b8(ctx);  // tail call
        return;
    }
L_005387b8:
    charge(ctx, 15);
    ld(fp, sp, 0x50);
    a1 = s7;
    ld(s7, sp, 0x48);
    a3 = s5;
    ld(s5, sp, 0x38);
    lw(a2, sp, 0x0);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s6, sp, 0x40);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
    gen::fn_sub_538648_00538648(ctx);  // tail call
}

// 0x00538860 sub_538860 -- 336 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// ADX decode step: when the decoder is idle, fetches input (+120 callback), starts a decode (sub_538510); when done,
// completes it (sub_5386D8).
void sub_538860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00538860
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    lw(v1, s0, 4);
    if (v1 != v0) {
        v0 = 2;
    } else {
        // 0x0053888c
        charge(ctx, 4);
        link(ctx, 0x53888Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 8);
        call(ctx, gen::fn_sub_54CD80_0054cd80);
        if (v0 != 0) {
            lw(v1, s0, 4);
            // 0x005388d0
            charge(ctx, 1);
            v0 = 2;
        } else {
            // 0x0053889c
            charge(ctx, 12);
            lw(a0, s0, 124);
            a1 = addiu(s0, 104);
            lw(v0, s0, 120);
            a2 = addiu(s0, 108);
            a3 = addiu(s0, 112);
            jalr(ctx, 0x5388ACu, v0.u());
            a0 = s0;
            jal(ctx, 0x5388B4u, gen::fn_sub_538510_00538510);
            v0 = 2;
            sw(v0, s0, 4);
            v1 = 2;
        }
    }
    // 0x005388d4
    charge(ctx, 2);
    if (v1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005388dc
        charge(ctx, 7);
        link(ctx, 0x5388DCu);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 8);
        call(ctx, gen::fn_sub_54CE90_0054ce90);
        link(ctx, 0x5388E4u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 8);
        call(ctx, gen::fn_sub_54CD80_0054cd80);
        v1 = 3;
        if (v0 != v1) {
            ld(s0, sp, 0x0);
        } else {
            // 0x005388f8
            charge(ctx, 3);
            lw(v0, s0, 232);
            if (v0 != 0) {
                // 0x00538904
                charge(ctx, 6);
                link(ctx, 0x538904u);  // $ra first: the delay slot below depends on it
                lw(s1, s0, 8);
                call(ctx, gen::fn_sub_539818_00539818);
                lw(v0, s1, 16);
                v0 = sll(v0, 5);
                s2 = 0;
                if (i64(v0) > 0) {
                    // 0x0053891c
                    charge(ctx, 3);
                    s3 = 0x780000;
                    lw(a2, s1, 32);
                    for (;;) {
                        // 0x00538928
                        charge(ctx, 14);
                        a3 = sll(s2, 1);
                        lw(v0, s1, 36);
                        a0 = s0;
                        a2 = addu(a3, a2);
                        lw(v1, s3, 14556);
                        lh(a1, a2, 0);
                        a3 = addu(v0, a3);
                        s2 = addiu(s2, 1);
                        jalr(ctx, 0x538944u, v1.u());
                        lw(v0, s1, 16);
                        v0 = sll(v0, 5);
                        v0 = slt(s2, v0);
                        if (v0 == 0) {
                            break;
                        }
                        lw(a2, s1, 32);
                        backedge(ctx);
                    }
                }
                // 0x00538960
                charge(ctx, 2);
                jal(ctx, 0x538960u, gen::fn_sub_539830_00539830);
            }
            // 0x00538968
            charge(ctx, 12);
            a0 = s0;
            jal(ctx, 0x538968u, gen::fn_sub_5386D8_005386d8);
            link(ctx, 0x538970u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 8);
            call(ctx, gen::fn_sub_54CE60_0054ce60);
            lw(v1, s0, 128);
            lw(a0, s0, 132);
            lw(a1, s0, 148);
            jt = v1.u();  // the target, read before the delay slot
            link(ctx, 0x538984u);  // $ra = the return address
            lw(a2, s0, 144);
            call_ptr(ctx, jt);
            v0 = 3;
            sw(v0, s0, 4);
            ld(s0, sp, 0x0);
        }
    }
    // 0x00538998 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00538B60 sub_538B60 -- 288 bytes; leaf frame (no stack)
// Third header form parse: header size = 16 * byte 7, channels = (byte 9 & 3) + 1, rate = u16 at +42; byte 8 picks the
// sample kind (0: 16-bit, 1: 8-bit, 2..3: 4-bit) and the kind code (+156: 0, 1, 2).
void sub_538B60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29};
    // 0x00538b60
    enter(ctx, 17);  // entry check point + this block's cycles
    t4 = a0;
    t7 = 1;
    lbu(v0, t4, 7);
    lw(a1, sp, 0x10);
    v0 = sll(v0, 4);
    lw(t5, sp, 0x8);
    sh(v0, a2, 0);
    lw(t6, sp, 0x0);
    lbu(v0, t4, 9);
    v0 = v0 & 0x3;
    v0 = addiu(v0, 1);
    sb(v0, t2, 0);
    lhu(v1, t4, 42);
    sw(v1, t3, 0);
    lbu(a0, t4, 8);
    v0 = slti(a0, 2);
    if (a0 == t7) {
        // 0x00538c00
        charge(ctx, 8);
        v0 = 8;
        sb(v0, t0, 0);
        lb(v1, t2, 0);
        sb(v1, t1, 0);
        sw(a0, t5, 0);
        sh(a0, a1, 0);
        lw(v0, t4, 12);
    L_00538c40:
        charge(ctx, 2);
        sw(v0, t6, 0);
        v1 = 2;
    } else {
        // 0x00538ba4
        charge(ctx, 2);
        if (v0 == 0) {
            v0 = slti(a0, 4);
            // 0x00538bc0
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x00538bc8
                charge(ctx, 2);
                v1 = 4;
                // 0x00538c20
                charge(ctx, 8);
                a0 = 2;
                sb(v1, t0, 0);
                lb(v0, t2, 0);
                sb(v0, t1, 0);
                sw(a0, t5, 0);
                sh(a0, a1, 0);
                lw(v0, t4, 12);
                v0 = sll(v0, 1);
                goto L_00538c40;
            }
            v1 = 2;
        } else {
            // 0x00538bac
            charge(ctx, 2);
            if (a0 == 0) {
                v1 = 16;
                // 0x00538bd0
                charge(ctx, 11);
                sb(v1, t0, 0);
                lb(v0, t2, 0);
                v0 = sll(v0, 1);
                sb(v0, t1, 0);
                sw(t7, t5, 0);
                sh(zero, a1, 0);
                lw(v0, t4, 12);
                v1 = srl(v0, 31);
                v0 = addu(v0, v1);
                v0 = sra(v0, 1);
                goto L_00538c40;
            }
            // 0x00538bb4
            charge(ctx, 2);
            v1 = 2;
        }
    }
    // 0x00538c48 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    a0 = 1;
    sb(v1, t1, 0);
    a1 = 16;
    sw(a0, t5, 0);
    a2 = si(-1);
    v0 = 0;
    lw(v1, t4, 12);
    a0 = srl(v1, 31);
    v1 = addu(v1, a0);
    v1 = sra(v1, 1);
    sw(v1, t6, 0);
    sb(a1, t0, 0);
    sb(a2, a3, 0);
}

// 0x00538C80 sub_538C80 -- 244 bytes; frame 0x60: s0 sp+0x30, s1 sp+0x38, s2 sp+0x40, s3 sp+0x48, ra sp+0x50, s2 sp+0x8
// ADXB handle set-up for the third header form (sub_538B60), as sub_5365B8.
void sub_538C80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00538c80
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 1;
    sd(s0, sp, 0x30);
    s0 = a0;
    sd(s1, sp, 0x38);
    s1 = addiu(s0, 14);
    sd(s2, sp, 0x40);
    s2 = addiu(s0, 16);
    sd(s3, sp, 0x48);
    s3 = addiu(s0, 15);
    sd(ra, sp, 0x50);
    a0 = a1;
    sh(v0, s0, 2);
    v0 = addiu(s0, 24);
    a1 = a2;
    a2 = addiu(sp, 0x20);
    v1 = addiu(s0, 156);
    a3 = addiu(s0, 12);
    t0 = addiu(s0, 13);
    t1 = s3;
    t2 = s1;
    t3 = addiu(s0, 20);
    sw(v0, sp, 0x0);
    sw(v1, sp, 0x10);
    link(ctx, 0x538CE0u);  // $ra first: the delay slot below depends on it
    sw(s2, sp, 0x8);
    call(ctx, gen::fn_sub_538B60_00538b60);
    if (i64(v0) >= 0) {
        sw(zero, s0, 52);
        // 0x00538cf8
        charge(ctx, 24);
        sw(zero, s0, 48);
        sw(zero, s0, 44);
        sw(zero, s0, 40);
        sw(zero, s0, 32);
        sh(zero, s0, 28);
        sh(zero, s0, 38);
        sh(zero, s0, 36);
        lw(a1, s0, 60);
        lb(v1, s1, 0);
        lw(a2, s0, 64);
        sw(v1, s0, 80);
        v1 = 2;
        lw(a3, s0, 68);
        lb(a0, s3, 0);
        lh(v0, sp, 0x20);
        sw(a0, s0, 84);
        sh(v1, s0, 152);
        lw(v1, s2, 0);
        sw(a1, s0, 92);
        sw(a2, s0, 96);
        sw(v1, s0, 88);
        sw(a3, s0, 100);
        sw(zero, s0, 140);
        sw(zero, s0, 136);
    } else {
        // 0x00538cf0
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00538d58 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(ra, sp, 0x50);
    sp = addiu(sp, 0x60);
}

// 0x00538D78 sub_538D78 -- 372 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Decode step of the same input-callback / copy pattern (16-bit samples), called directly by the decode server.
void sub_538D78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00538d78
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = addiu(s0, 72);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v1, s0, 4);
    lw(s2, s1, 0);
    if (v1 == v0) {
        // 0x00538da4
        charge(ctx, 4);
        link(ctx, 0x538DA4u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 8);
        call(ctx, gen::fn_sub_54CD80_0054cd80);
        if (v0 != 0) {
            lw(v1, s0, 4);
        } else {
            // 0x00538db4
            charge(ctx, 22);
            lw(a0, s0, 124);
            a1 = addiu(s0, 104);
            lw(v0, s0, 120);
            a2 = addiu(s0, 108);
            a3 = addiu(s0, 112);
            jalr(ctx, 0x538DC4u, v0.u());
            lw(a0, s1, 24);
            lw(a3, s1, 32);
            a2 = 2;
            lw(v1, s1, 36);
            t1 = subu(a0, a3);
            lb(a0, s0, 14);
            v0 = slt(v1, t1);
            lw(a1, s1, 4);
            if (v0 != 0) t1 = v1;
            v1 = sll(a3, 1);
            lw(t3, s1, 20);
            v0 = slt(a1, t1);
            if (v0 != 0) t1 = a1;
            t2 = addu(t3, v1);
            lbu(v1, s0, 14);
            if (a0 != a2) {
                // 0x00538e60
                charge(ctx, 2);
                t0 = 0;
                if (i64(t1) > 0) {
                    for (;;) {
                        // 0x00538e68
                        charge(ctx, 8);
                        v0 = sll(t0, 1);
                        t0 = addiu(t0, 1);
                        v1 = addu(v0, s2);
                        v0 = addu(v0, t2);
                        lhu(a0, v1, 0);
                        a1 = slt(t0, t1);
                        sh(a0, v0, 0);
                        if (a1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00538e88
                    charge(ctx, 1);
                    lbu(v1, s0, 14);
                }
            } else {
                // 0x00538e0c
                charge(ctx, 6);
                lw(v0, s1, 28);
                t0 = 0;
                v0 = addu(v0, a3);
                v0 = sll(v0, 1);
                t3 = addu(t3, v0);
                if (i64(t1) > 0) {
                    // 0x00538e24
                    charge(ctx, 1);
                    a3 = s2;
                    for (;;) {
                        // 0x00538e28
                        charge(ctx, 11);
                        v1 = sll(t0, 1);
                        t0 = addiu(t0, 1);
                        lhu(a1, a3, 0);
                        a0 = addu(v1, t2);
                        a2 = slt(t0, t1);
                        v1 = addu(v1, t3);
                        sh(a1, a0, 0);
                        lhu(v0, a3, 2);
                        a3 = addiu(a3, 4);
                        sh(v0, v1, 0);
                        if (a2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00538e54
                    charge(ctx, 2);
                    lbu(v1, s0, 14);
                }
            }
            // 0x00538e8c
            charge(ctx, 8);
            v0 = sll(v1, 24);
            v1 = 2;
            v0 = sra(v0, 24);
            sw(v1, s0, 4);
            mult(v0, t1, v0);
            sw(t1, s0, 144);
            v0 = sll(v0, 1);
            sw(v0, s0, 148);
        }
    }
    // 0x00538eac
    charge(ctx, 3);
    v0 = 2;
    if (v1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00538eb8
        charge(ctx, 8);
        lw(v1, s0, 128);
        lw(a0, s0, 132);
        lw(a1, s0, 148);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x538EC4u);  // $ra = the return address
        lw(a2, s0, 144);
        call_ptr(ctx, jt);
        v0 = 3;
        sw(v0, s0, 4);
        ld(s0, sp, 0x0);
    }
    // 0x00538ed8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00539248 sub_539248 -- 372 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Decode step for kind 0 of sub_539760 (16-bit samples).
void sub_539248(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00539248
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = addiu(s0, 72);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v1, s0, 4);
    lw(s2, s1, 0);
    if (v1 == v0) {
        // 0x00539274
        charge(ctx, 4);
        link(ctx, 0x539274u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 8);
        call(ctx, gen::fn_sub_54CD80_0054cd80);
        if (v0 != 0) {
            lw(v1, s0, 4);
        } else {
            // 0x00539284
            charge(ctx, 22);
            lw(a0, s0, 124);
            a1 = addiu(s0, 104);
            lw(v0, s0, 120);
            a2 = addiu(s0, 108);
            a3 = addiu(s0, 112);
            jalr(ctx, 0x539294u, v0.u());
            lw(a0, s1, 24);
            lw(a3, s1, 32);
            a2 = 2;
            lw(v1, s1, 36);
            t1 = subu(a0, a3);
            lb(a0, s0, 14);
            v0 = slt(v1, t1);
            lw(a1, s1, 4);
            if (v0 != 0) t1 = v1;
            v1 = sll(a3, 1);
            lw(t3, s1, 20);
            v0 = slt(a1, t1);
            if (v0 != 0) t1 = a1;
            t2 = addu(t3, v1);
            lbu(v1, s0, 14);
            if (a0 != a2) {
                // 0x00539330
                charge(ctx, 2);
                t0 = 0;
                if (i64(t1) > 0) {
                    for (;;) {
                        // 0x00539338
                        charge(ctx, 8);
                        v0 = sll(t0, 1);
                        t0 = addiu(t0, 1);
                        v1 = addu(v0, s2);
                        v0 = addu(v0, t2);
                        lhu(a0, v1, 0);
                        a1 = slt(t0, t1);
                        sh(a0, v0, 0);
                        if (a1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00539358
                    charge(ctx, 1);
                    lbu(v1, s0, 14);
                }
            } else {
                // 0x005392dc
                charge(ctx, 6);
                lw(v0, s1, 28);
                t0 = 0;
                v0 = addu(v0, a3);
                v0 = sll(v0, 1);
                t3 = addu(t3, v0);
                if (i64(t1) > 0) {
                    // 0x005392f4
                    charge(ctx, 1);
                    a3 = s2;
                    for (;;) {
                        // 0x005392f8
                        charge(ctx, 11);
                        v1 = sll(t0, 1);
                        t0 = addiu(t0, 1);
                        lhu(a1, a3, 0);
                        a0 = addu(v1, t2);
                        a2 = slt(t0, t1);
                        v1 = addu(v1, t3);
                        sh(a1, a0, 0);
                        lhu(v0, a3, 2);
                        a3 = addiu(a3, 4);
                        sh(v0, v1, 0);
                        if (a2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00539324
                    charge(ctx, 2);
                    lbu(v1, s0, 14);
                }
            }
            // 0x0053935c
            charge(ctx, 8);
            v0 = sll(v1, 24);
            v1 = 2;
            v0 = sra(v0, 24);
            sw(v1, s0, 4);
            mult(v0, t1, v0);
            sw(t1, s0, 144);
            v0 = sll(v0, 1);
            sw(v0, s0, 148);
        }
    }
    // 0x0053937c
    charge(ctx, 3);
    v0 = 2;
    if (v1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00539388
        charge(ctx, 8);
        lw(v1, s0, 128);
        lw(a0, s0, 132);
        lw(a1, s0, 148);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x539394u);  // $ra = the return address
        lw(a2, s0, 144);
        call_ptr(ctx, jt);
        v0 = 3;
        sw(v0, s0, 4);
        ld(s0, sp, 0x0);
    }
    // 0x005393a8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005393C0 sub_5393C0 -- 404 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Decode step for kind 1 of sub_539760 (8-bit samples).
void sub_5393C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005393c0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = addiu(s0, 72);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v1, s0, 4);
    lw(s2, s1, 0);
    if (v1 == v0) {
        // 0x005393ec
        charge(ctx, 4);
        link(ctx, 0x5393ECu);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 8);
        call(ctx, gen::fn_sub_54CD80_0054cd80);
        if (v0 != 0) {
            lw(v1, s0, 4);
        } else {
            // 0x005393fc
            charge(ctx, 22);
            lw(a0, s0, 124);
            a1 = addiu(s0, 104);
            lw(v0, s0, 120);
            a2 = addiu(s0, 108);
            a3 = addiu(s0, 112);
            jalr(ctx, 0x53940Cu, v0.u());
            lw(a0, s1, 24);
            lw(a3, s1, 32);
            a2 = 2;
            lw(v1, s1, 36);
            t1 = subu(a0, a3);
            lb(a0, s0, 14);
            v0 = slt(v1, t1);
            lw(a1, s1, 4);
            if (v0 != 0) t1 = v1;
            v1 = sll(a3, 1);
            lw(t2, s1, 20);
            v0 = slt(a1, t1);
            if (v0 != 0) t1 = a1;
            t3 = addu(t2, v1);
            lbu(v1, s0, 14);
            if (a0 != a2) {
                // 0x005394c0
                charge(ctx, 2);
                t0 = 0;
                if (i64(t1) > 0) {
                    // 0x005394c8
                    charge(ctx, 2);
                    a1 = t3;
                    a2 = 0xFF80;
                    for (;;) {
                        // 0x005394d0
                        charge(ctx, 9);
                        v0 = addu(s2, t0);
                        t0 = addiu(t0, 1);
                        lbu(v1, v0, 0);
                        a0 = slt(t0, t1);
                        v1 = addu(v1, a2);
                        v1 = sll(v1, 8);
                        sh(v1, a1, 0);
                        a1 = addiu(a1, 2);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x005394f4
                    charge(ctx, 1);
                    lbu(v1, s0, 14);
                }
            } else {
                // 0x00539454
                charge(ctx, 6);
                lw(v0, s1, 28);
                t0 = 0;
                v0 = addu(v0, a3);
                v0 = sll(v0, 1);
                t4 = addu(t2, v0);
                if (i64(t1) > 0) {
                    // 0x0053946c
                    charge(ctx, 3);
                    a3 = s2;
                    t2 = 0xFF80;
                    for (;;) {
                        // 0x00539478
                        charge(ctx, 15);
                        lbu(v1, a3, 0);
                        a0 = sll(t0, 1);
                        a1 = addu(a0, t3);
                        a0 = addu(a0, t4);
                        v1 = addu(v1, t2);
                        t0 = addiu(t0, 1);
                        v1 = sll(v1, 8);
                        a2 = slt(t0, t1);
                        sh(v1, a1, 0);
                        lbu(v0, a3, 1);
                        a3 = addiu(a3, 2);
                        v0 = addu(v0, t2);
                        v0 = sll(v0, 8);
                        sh(v0, a0, 0);
                        if (a2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x005394b4
                    charge(ctx, 2);
                    lbu(v1, s0, 14);
                }
            }
            // 0x005394f8
            charge(ctx, 7);
            v0 = sll(v1, 24);
            v1 = 2;
            v0 = sra(v0, 24);
            sw(v1, s0, 4);
            mult(v0, t1, v0);
            sw(t1, s0, 144);
            sw(v0, s0, 148);
        }
    }
    // 0x00539514
    charge(ctx, 3);
    v0 = 2;
    if (v1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00539520
        charge(ctx, 8);
        lw(v1, s0, 128);
        lw(a0, s0, 132);
        lw(a1, s0, 148);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x53952Cu);  // $ra = the return address
        lw(a2, s0, 144);
        call_ptr(ctx, jt);
        v0 = 3;
        sw(v0, s0, 4);
        ld(s0, sp, 0x0);
    }
    // 0x00539540 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00539558 sub_539558 -- 412 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Decode step for kind 2 of sub_539760 (byte pairs, split per channel when +14 is 2).
void sub_539558(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00539558
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = addiu(s0, 72);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v1, s0, 4);
    lw(s2, s1, 0);
    if (v1 == v0) {
        // 0x00539584
        charge(ctx, 4);
        link(ctx, 0x539584u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 8);
        call(ctx, gen::fn_sub_54CD80_0054cd80);
        if (v0 != 0) {
            lw(v1, s0, 4);
        } else {
            // 0x00539594
            charge(ctx, 22);
            lw(a0, s0, 124);
            a1 = addiu(s0, 104);
            lw(v0, s0, 120);
            a2 = addiu(s0, 108);
            a3 = addiu(s0, 112);
            jalr(ctx, 0x5395A4u, v0.u());
            lw(a0, s1, 24);
            lw(a3, s1, 32);
            a2 = 2;
            lw(v1, s1, 36);
            t1 = subu(a0, a3);
            lb(a0, s0, 14);
            v0 = slt(v1, t1);
            lw(a1, s1, 4);
            if (v0 != 0) t1 = v1;
            v1 = sll(a3, 1);
            lw(t3, s1, 20);
            v0 = slt(a1, t1);
            if (v0 != 0) t1 = a1;
            t2 = addu(t3, v1);
            lbu(v1, s0, 14);
            if (a0 != a2) {
                // 0x00539658
                charge(ctx, 2);
                t0 = 0;
                if (i64(t1) > 0) {
                    // 0x00539660
                    charge(ctx, 2);
                    a1 = s2;
                    a2 = t2;
                    for (;;) {
                        // 0x00539668
                        charge(ctx, 10);
                        lbu(v0, a1, 1);
                        t0 = addiu(t0, 1);
                        lbu(v1, a1, 0);
                        a1 = addiu(a1, 2);
                        v0 = sll(v0, 8);
                        a0 = slt(t0, t1);
                        v1 = v1 | v0;
                        sh(v1, a2, 0);
                        a2 = addiu(a2, 2);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00539690
                    charge(ctx, 1);
                    lbu(v1, s0, 14);
                }
            } else {
                // 0x005395ec
                charge(ctx, 6);
                lw(v0, s1, 28);
                t0 = 0;
                v0 = addu(v0, a3);
                v0 = sll(v0, 1);
                t3 = addu(t3, v0);
                if (i64(t1) > 0) {
                    // 0x00539604
                    charge(ctx, 1);
                    a3 = s2;
                    for (;;) {
                        // 0x00539608
                        charge(ctx, 17);
                        lbu(v0, a3, 2);
                        a0 = sll(t0, 1);
                        lbu(v1, a3, 0);
                        a1 = addu(a0, t2);
                        v0 = sll(v0, 8);
                        t0 = addiu(t0, 1);
                        v1 = v1 | v0;
                        a0 = addu(a0, t3);
                        sh(v1, a1, 0);
                        a2 = slt(t0, t1);
                        lbu(v0, a3, 3);
                        lbu(v1, a3, 1);
                        a3 = addiu(a3, 4);
                        v0 = sll(v0, 8);
                        v1 = v1 | v0;
                        sh(v1, a0, 0);
                        if (a2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0053964c
                    charge(ctx, 2);
                    lbu(v1, s0, 14);
                }
            }
            // 0x00539694
            charge(ctx, 8);
            v0 = sll(v1, 24);
            v1 = 2;
            v0 = sra(v0, 24);
            sw(v1, s0, 4);
            mult(v0, t1, v0);
            sw(t1, s0, 144);
            v0 = sll(v0, 1);
            sw(v0, s0, 148);
        }
    }
    // 0x005396b4
    charge(ctx, 3);
    v0 = 2;
    if (v1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005396c0
        charge(ctx, 8);
        lw(v1, s0, 128);
        lw(a0, s0, 132);
        lw(a1, s0, 148);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x5396CCu);  // $ra = the return address
        lw(a2, s0, 144);
        call_ptr(ctx, jt);
        v0 = 3;
        sw(v0, s0, 4);
        ld(s0, sp, 0x0);
    }
    // 0x005396e0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00539760 sub_539760 -- 88 bytes; frame 0x10: ra sp+0x0
// Decode dispatch on the kind at +156: 2, 1 or 0 (other kinds: return 1).
void sub_539760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00539760
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 2;
    sd(ra, sp, 0x0);
    lh(v1, a0, 156);
    cc = v1 != v0;  // the condition, before the delay slot changes it
    v0 = 1;
    if (!cc) {
        // 0x00539778
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_sub_539558_00539558(ctx);  // tail call
        return;
    }
    // 0x00539788
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    if (v1 == v0) {
        // 0x00539790
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        gen::fn_sub_5393C0_005393c0(ctx);  // tail call
        return;
    }
    // 0x00539798
    charge(ctx, 2);
    if (v1 != 0) {
        // 0x005397b0
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005397a0
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539248_00539248(ctx);  // tail call
}

// =====================================================================================================================
// ADX error reporting: the callback, the message buffer, number to text
// =====================================================================================================================

// 0x0053AD70 sub_53AD70 -- 56 bytes; frame 0x10: ra sp+0x0
// Error state init: clears the message buffer at 0x784958 and the callback (0x784950 / 0x784954).
void sub_53AD70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053ad70
    enter(ctx, 14);  // entry check point + this block's cycles
    a0 = 0x780000;
    sp = addiu(sp, -0x10);
    a1 = 0;
    a0 = addiu(a0, 18776);  // &0x784958
    sd(ra, sp, 0x0);
    a2 = 256;
    jal(ctx, 0x53AD84u, gen::fn_memset_00521408);
    v1 = 0x780000;
    ld(ra, sp, 0x0);
    v0 = 0x780000;
    sw(zero, v1, 18768);  // 0x784950
    sw(zero, v0, 18772);  // 0x784954
    sp = addiu(sp, 0x10);
}

// 0x0053ADA8 sub_53ADA8 -- 56 bytes; frame 0x10: ra sp+0x0
// Error state finish: the same clear as sub_53AD70.
void sub_53ADA8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053ada8
    enter(ctx, 14);  // entry check point + this block's cycles
    a0 = 0x780000;
    sp = addiu(sp, -0x10);
    a1 = 0;
    a0 = addiu(a0, 18776);  // &0x784958
    sd(ra, sp, 0x0);
    a2 = 256;
    jal(ctx, 0x53ADBCu, gen::fn_memset_00521408);
    v1 = 0x780000;
    ld(ra, sp, 0x0);
    v0 = 0x780000;
    sw(zero, v1, 18768);  // 0x784950
    sw(zero, v0, 18772);  // 0x784954
    sp = addiu(sp, 0x10);
}

// 0x0053ADE0 sub_53ADE0 -- 36 bytes; frame 0x10: ra sp+0x0
// Sets the error callback (function, object) and forwards it to SVM (sub_5651F0).
void sub_53ADE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053ade0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x780000;
    sd(ra, sp, 0x0);
    v1 = 0x780000;
    sw(a0, v0, 18768);  // 0x784950
    ld(ra, sp, 0x0);
    sw(a1, v1, 18772);  // 0x784954
    sp = addiu(sp, 0x10);
    gen::fn_sub_5651F0_005651f0(ctx);  // tail call
}

// 0x0053AED0 sub_53AED0 -- 260 bytes; frame 0x20: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, ra sp+0x18
// Integer to decimal text into a caller buffer (at most 32 digits), via a reversed digit scratch.
void sub_53AED0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053aed0
    enter(ctx, 13);  // entry check point + this block's cycles
    v0 = 10;
    sp = addiu(sp, -0x20);
    div(a0, v0);
    sd(s0, sp, 0x0);
    v1 = 10;
    s0 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s1, sp, 0x8);
    a1 = 0;
    sd(ra, sp, 0x18);
    if (v0 == 0) {
        brk(ctx, 0x53AF00u, 0x7u);
    }
    // 0x0053af04
    charge(ctx, 6);
    mflo(t0);
    mfhi(a3);
    a0 = t0;
    sb(a3, s0, 0);
    if (a0 != 0) {
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x0053af28
            charge(ctx, 3);
            v0 = slti(a1, 32);
            a2 = addu(s0, a1);
            if (v0 == 0) {
                break;
            }
            // 0x0053af34
            charge(ctx, 5);
            v0 = 10;
            v1 = 10;
            div(a0, v0);
            if (v0 == 0) {
                brk(ctx, 0x53AF44u, 0x7u);
            }
            // 0x0053af48
            charge(ctx, 6);
            mflo(t0);
            mfhi(a3);
            a0 = t0;
            sb(a3, a2, 0);
            if (a0 == 0) {
                goto L_0053af60_6;
            }
            a1 = addiu(a1, 1);
            backedge(ctx);
        }
    } else {
        // 0x0053af1c
        charge(ctx, 2);
        sb(zero, s0, 0);
    }
L_0053af64:
    charge(ctx, 10);
    v0 = 0x990000;
    s1 = addiu(v0, 28680);  // &0x997008
    a0 = s1;
    jal(ctx, 0x53AF6Cu, gen::fn_strlen_00524388);
    a3 = v0;
    v0 = addiu(s2, -1);
    v1 = slt(a3, v0);
    if (v1 == 0) a3 = v0;
    a1 = 0;
    if (i64(a3) > 0) {
        // 0x0053af8c
        charge(ctx, 3);
        v0 = addu(a3, s1);
        a2 = addiu(v0, -1);
        for (;;) {
            // 0x0053af98
            charge(ctx, 7);
            a0 = addu(s0, a1);
            a1 = addiu(a1, 1);
            lbu(v1, a2, 0);
            a2 = addiu(a2, -1);
            v0 = slt(a1, a3);
            sb(v1, a0, 0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0053afb4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = addu(s0, a1);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sb(zero, v0, 0);
    sp = addiu(sp, 0x20);
    return;
L_0053af60_6:
    charge(ctx, 1);
    sb(zero, a2, 0);
    goto L_0053af64;
}

// =====================================================================================================================
// ADXF: the file layer (handles 0x784A60, partitions 0x784EA0, the call log, ROFS volumes, read / seek / stop)
// =====================================================================================================================

// 0x0053B060 sub_53B060 -- 28 bytes; frame 0x10: ra sp+0x0
// InvalidDCache over [buf, buf + size).
void sub_53B060(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b060
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = addu(a0, a1);
    sd(ra, sp, 0x0);
    a1 = addiu(a1, -1);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_InvalidDCache_00503b98(ctx);  // tail call
}

// 0x0053B080 sub_53B080 -- 216 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXF_Init: on the first call clears the handle table (0x784A60, 16 x 68), the partition table (0x784EA0), the call
// log and its counters; counts the init.
void sub_53B080(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b080
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x780000;
    sd(s0, sp, 0x0);
    s0 = addiu(a0, 19032);  // &0x784A58
    v1 = 0x990000;
    v0 = 0x7C0000;
    lw(a0, s0, 0);  // 0x784A58
    v1 = addiu(v1, 28712);  // &0x997028
    v0 = addiu(v0, 6792);  // "\nADXF/PS2EE Ver.7.30 Build:Feb 28 2005 19:25:12\n"
    sd(ra, sp, 0x8);
    sw(v0, v1, 0);  // 0x997028
    if (a0 != 0) {
        v0 = addiu(a0, 1);
    } else {
        // 0x0053b0b4
        charge(ctx, 36);
        a0 = 0x780000;
        a1 = 0;
        a0 = addiu(a0, 19040);  // &0x784A60
        a2 = 1088;
        jal(ctx, 0x53B0C0u, gen::fn_memset_00521408);
        a0 = 0x780000;
        a0 = addiu(a0, 20128);  // &0x784EA0
        a1 = 0;
        a2 = 1024;
        jal(ctx, 0x53B0D4u, gen::fn_memset_00521408);
        a0 = 0x780000;
        a0 = addiu(a0, 21160);  // &0x7852A8
        a1 = 255;
        a2 = 256;
        jal(ctx, 0x53B0E8u, gen::fn_memset_00521408);
        a0 = 0x780000;
        a0 = addiu(a0, 21416);  // &0x7853A8
        a1 = 0;
        a2 = 32;
        jal(ctx, 0x53B0FCu, gen::fn_memset_00521408);
        a2 = 0x780000;
        a0 = 0x780000;
        a3 = 0x780000;
        t0 = 0x780000;
        t1 = 0x780000;
        a1 = 0x780000;
        v1 = si(-1);
        v0 = 1;
        sw(v1, a1, 21460);  // 0x7853D4
        sw(v0, a0, 21464);  // 0x7853D8
        sw(zero, a2, 21448);  // 0x7853C8
        sw(zero, a3, 21152);  // 0x7852A0
        sw(zero, t0, 21452);  // 0x7853CC
        sw(zero, t1, 21456);  // 0x7853D0
        lw(a0, s0, 0);
        v0 = addiu(a0, 1);
    }
    // 0x0053b144 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x8);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053B158 sub_53B158 -- 196 bytes; frame 0x10: ra sp+0x0
// ADXF_Finish: on the last call closes every handle (sub_53CEB8) and clears what ADXF_Init set.
void sub_53B158(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b158
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x780000;
    sd(ra, sp, 0x0);
    v1 = addiu(v1, 19032);  // &0x784A58
    lw(v0, v1, 0);  // 0x784A58
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x784A58
    if (v0 != 0) {
        // 0x0053b210
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0053b178
    charge(ctx, 38);
    jal(ctx, 0x53B178u, gen::fn_sub_53CEB8_0053ceb8);
    t4 = 0x780000;
    a0 = 0x780000;
    t2 = 1;
    t3 = 0x780000;
    v1 = 0x780000;
    a3 = 0x780000;
    t0 = 0x780000;
    t1 = 0x780000;
    a1 = 0;
    a0 = addiu(a0, 21416);  // &0x7853A8
    a2 = 32;
    v0 = si(-1);
    sw(t2, t4, 21464);  // 0x7853D8
    sw(v0, t3, 21460);  // 0x7853D4
    sw(zero, v1, 21456);  // 0x7853D0
    sw(zero, a3, 21452);  // 0x7853CC
    sw(zero, t0, 21152);  // 0x7852A0
    link(ctx, 0x53B1C4u);  // $ra first: the delay slot below depends on it
    sw(zero, t1, 21448);
    call(ctx, gen::fn_memset_00521408);
    a0 = 0x780000;
    a1 = 255;
    a0 = addiu(a0, 21160);  // &0x7852A8
    a2 = 256;
    jal(ctx, 0x53B1D8u, gen::fn_memset_00521408);
    a0 = 0x780000;
    a0 = addiu(a0, 20128);  // &0x784EA0
    a1 = 0;
    a2 = 1024;
    jal(ctx, 0x53B1ECu, gen::fn_memset_00521408);
    a0 = 0x780000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 19040);  // &0x784A60
    a1 = 0;
    a2 = 1088;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0053B250 adxf_SetupRofs -- 40 bytes; frame 0x10: ra sp+0x0
// cvFsAddDev("ROFS", ROCI_GetInterface, 0).
void adxf_SetupRofs(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b250
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x7C0000;
    sd(ra, sp, 0x0);
    a1 = 0x570000;
    a0 = addiu(a0, 6872);  // "ROFS"
    a1 = addiu(a1, -14200);  // &ROCI_GetInterface
    ld(ra, sp, 0x0);
    a2 = 0;
    sp = addiu(sp, 0x10);
    gen::fn_cvFsAddDev_00555b10(ctx);  // tail call
}

// 0x0053B2A0 sub_53B2A0 -- 28 bytes; frame 0x10: ra sp+0x0
// Removes the ROFS device (sub_555D70("ROFS")).
void sub_53B2A0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b2a0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x7C0000;
    sd(ra, sp, 0x0);
    a0 = addiu(a0, 6872);  // "ROFS"
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_555D70_00555d70(ctx);  // tail call
}

// 0x0053B318 adxf_AddRofsVol -- 188 bytes; frame 0x30: s1 sp+0x8, s0 sp+0x0, s3 sp+0x18, s2 sp+0x10, ra sp+0x20
// Opens the volume image and registers it as a ROFS volume (cvFsOpen, cvFsAddVolumeEx); -3 for a null / "ROFS" name,
// -1 when the open or the add fails (the file is closed again).
void adxf_AddRofsVol(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b318
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = si(-3);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    if (s1 != 0) {
        // 0x0053b344
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x0053b34c
            charge(ctx, 8);
            v0 = 0x7C0000;
            s2 = addiu(v0, 6872);  // "ROFS"
            a1 = s2;
            jal(ctx, 0x53B354u, gen::fn_strcmp_00524128);
            a0 = s0;
            a1 = 0;
            a2 = 0;
            if (v0 != 0) {
                // 0x0053b378
                charge(ctx, 9);
                jal(ctx, 0x53B378u, gen::fn_cvFsOpen_00556048);
                a0 = s2;
                s0 = v0;
                v0 = si(-1);
                a3 = s3;
                a1 = s1;
                a2 = s0;
                if (s0 != 0) {
                    // 0x0053b39c
                    charge(ctx, 4);
                    jal(ctx, 0x53B39Cu, gen::fn_cvFsAddVolumeEx_00557358);
                    if (i64(v0) >= 0) {
                        v0 = 0;
                    } else {
                        // 0x0053b3ac
                        charge(ctx, 3);
                        a0 = s0;
                        jal(ctx, 0x53B3ACu, gen::fn_cvFsClose_00556398);
                        v0 = si(-1);
                    }
                }
            } else {
                // 0x0053b36c
                charge(ctx, 2);
                v0 = si(-3);
            }
            goto L_0053b3b8;
        }
        ld(s0, sp, 0x0);
        // 0x0053b3bc (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_0053b3b8:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0053b3bc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0053B408 sub_53B408 -- 96 bytes; frame 0x30: s1 sp+0x18, s0 sp+0x10, ra sp+0x20
// Removes a ROFS volume and closes its image.
void sub_53B408(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b408
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s0, sp, 0x10);
    a1 = s1;
    sd(ra, sp, 0x20);
    if (s1 != 0) {
        // 0x0053b424
        charge(ctx, 8);
        s0 = 0x7C0000;
        a2 = sp;
        s0 = addiu(s0, 6872);  // "ROFS"
        a0 = s0;
        jal(ctx, 0x53B430u, gen::fn_sub_557520_00557520);
        a0 = s0;
        a1 = s1;
        if (i64(v0) >= 0) {
            // 0x0053b444
            charge(ctx, 4);
            jal(ctx, 0x53B444u, gen::fn_sub_557460_00557460);
            link(ctx, 0x53B44Cu);  // $ra first: the delay slot below depends on it
            lw(a0, sp, 0x4);
            call(ctx, gen::fn_cvFsClose_00556398);
        }
    }
    // 0x0053b454 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0053B4A0 sub_53B4A0 -- 84 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// 1 when the ROFS volume `name` is registered under that name.
void sub_53B4A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b4a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x10);
    s0 = a0;
    a0 = 0x7C0000;
    a1 = s0;
    a0 = addiu(a0, 6872);  // "ROFS"
    sd(ra, sp, 0x18);
    a2 = sp;
    jal(ctx, 0x53B4BCu, gen::fn_sub_557520_00557520);
    a1 = s0;
    if (i64(v0) >= 0) {
        // 0x0053b4d8
        charge(ctx, 3);
        link(ctx, 0x53B4D8u);  // $ra first: the delay slot below depends on it
        lw(a0, sp, 0x0);
        call(ctx, gen::fn_strcmp_00524128);
        v0 = sltiu(v0, 1);
    } else {
        // 0x0053b4cc
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0053b4e4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0053B528 adxf_SetDefDev -- 112 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// Makes a ROFS volume the default (cvFsSetDefVol) when it is registered.
void adxf_SetDefDev(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b528
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x20);
    if (s0 != 0) {
        // 0x0053b540
        charge(ctx, 6);
        v0 = 0x7C0000;
        s1 = addiu(v0, 6872);  // "ROFS"
        a1 = s1;
        jal(ctx, 0x53B548u, gen::fn_strcmp_00524128);
        a0 = s0;
        if (v0 != 0) {
            // 0x0053b558
            charge(ctx, 9);
            jal(ctx, 0x53B558u, gen::fn_sub_555E48_00555e48);
            a0 = s1;
            a1 = s0;
            a2 = sp;
            jal(ctx, 0x53B568u, gen::fn_sub_557520_00557520);
            a0 = s1;
            a1 = s0;
            if (i64(v0) >= 0) {
                // 0x0053b57c
                charge(ctx, 2);
                jal(ctx, 0x53B57Cu, gen::fn_cvFsSetDefVol_005575f0);
            }
        }
    }
    // 0x0053b584 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0053B598 __env_lock -- 8 bytes; leaf frame (no stack)
// Empty lock hook.
void __env_lock(EEContext& ctx) {
    using namespace hg;
    // 0x0053b598
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0053B5A0 __env_unlock -- 8 bytes; leaf frame (no stack)
// Empty unlock hook.
void __env_unlock(EEContext& ctx) {
    using namespace hg;
    // 0x0053b5a0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0053B5A8 sub_53B5A8 -- 40 bytes; leaf frame (no stack)
// Bytes to 2048-byte sectors, rounded up.
void sub_53B5A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0053b5a8
    enter(ctx, 10);  // entry check point + this block's cycles
    v1 = slti(a0, 0);
    a1 = addiu(a0, 2047);
    v0 = a0;
    if (v1 != 0) v0 = a1;
    v0 = sra(v0, 11);
    v1 = sll(v0, 11);
    a0 = subu(a0, v1);
    a0 = slt(0, a0);
    v0 = addu(v0, a0);
}

// 0x0053B5D0 sub_53B5D0 -- 172 bytes; leaf frame (no stack)
// ADXF call log: a 16-entry ring at 0x7852A8 of {id, leave flag, count, a, b, c}; on entry counts the call per id
// (0x7853A8).
void sub_53B5D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13};
    // 0x0053b5d0
    enter(ctx, 22);  // entry check point + this block's cycles
    v0 = 0x780000;
    t2 = a0;
    t4 = addiu(v0, 21448);  // &0x7853C8
    t5 = a1;
    lw(v1, t4, 0);  // 0x7853C8
    t1 = sll(t2, 1);
    t3 = 0x780000;
    t3 = addiu(t3, 21416);  // &0x7853A8
    t3 = addu(t3, t1);
    a1 = addiu(v1, 15);
    a0 = slti(v1, 0);
    v0 = v1;
    if (a0 != 0) v0 = a1;
    v0 = sra(v0, 4);
    v0 = sll(v0, 4);
    v1 = subu(v1, v0);
    a0 = sll(v1, 4);
    a1 = 0x780000;
    a1 = addiu(a1, 21160);  // &0x7852A8
    a1 = addu(a1, a0);
    sw(v1, t4, 0);  // 0x7853C8
    if (t5 != 0) {
        // 0x0053b640
        charge(ctx, 2);
        a0 = 0x780000;
        t1 = sll(t2, 1);
    } else {
        // 0x0053b628
        charge(ctx, 5);
        lhu(v0, t3, 0);
        a0 = 0x780000;
        v0 = addiu(v0, 1);
        sh(v0, t3, 0);
    }
    // 0x0053b648 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    lw(v1, t4, 0);
    a0 = addiu(a0, 21416);
    sb(t2, a1, 0);
    a0 = addu(t1, a0);
    v1 = addiu(v1, 1);
    sb(t5, a1, 1);
    sw(t0, a1, 12);
    sw(a2, a1, 4);
    sw(a3, a1, 8);
    sw(v1, t4, 0);
    lhu(v0, a0, 0);
    sh(v0, a1, 2);
}

// 0x0053B680 sub_53B680 -- 44 bytes; leaf frame (no stack)
// Busy wait: 49999 loop turns.
void sub_53B680(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0053b680
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0xC350;
    v0 = addiu(v0, -1);
    for (;;) {
        // 0x0053b688
        charge(ctx, 7);
        if (v0 == 0) {
            break;
        }
        v0 = addiu(v0, -1);
        backedge(ctx);
    }
    // 0x0053b6a4
    charge(ctx, 2);
}

// 0x0053B6B0 sub_53B6B0 -- 72 bytes; frame 0x10: ra sp+0x0
// Partition argument check: 'E9040801' for an id >= 256, 'E9040802' for a null info; -3, else 0.
// [proposed name] adxf_ChkPrmPt: the function's own error text names it.
void sub_53B6B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b6b0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = sltiu(a0, 256);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0053b6c0
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 6880);  // "E9040801:partition ID is range outside.(adxf_ChkPrmPt)"
        goto L_0053b6e0;
    }
    // 0x0053b6d0
    charge(ctx, 2);
    v0 = 0;
    if (a1 == 0) {
        // 0x0053b6d8
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 6936);  // "E9040802:'ptinfo' is NULL.(adxf_ChkPrmPt)"
    L_0053b6e0:
        charge(ctx, 3);
        jal(ctx, 0x53B6E0u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-3);
    }
    // 0x0053b6ec (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053B8D0 adxf_LoadPartitionNw -- 948 bytes; frame 0x10: ra sp+0x0
// Loads a partition by file name, no wait (sub_53BEF0 with the work buffer at 0x785478).
void adxf_LoadPartitionNw(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b8d0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = 0x780000;
    sd(ra, sp, 0x0);
    v0 = si(-64);
    t0 = addiu(t0, 21624);  // &0x785478
    t1 = 2048;
    ld(ra, sp, 0x0);
    t0 = t0 & v0;
    sp = addiu(sp, 0x10);
    // 0x0053bc38
    charge(ctx, 19);
    sp = addiu(sp, -0x30);
    v1 = a2;
    v0 = a1;
    a1 = 0;
    t2 = 0xF0000;
    t3 = a3;
    sw(t0, sp, 0x0);
    t0 = v1;
    sw(t1, sp, 0x8);
    t1 = 0;
    a2 = 0;
    a3 = v0;
    t2 = t2 | 0xFFFF;
    sd(ra, sp, 0x20);
    link(ctx, 0x53BC70u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x10);
    call(ctx, gen::fn_sub_53BEF0_0053bef0);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0053BD10 sub_53BD10 -- 60 bytes; frame 0x30: ra sp+0x20
// Loads a partition by range, no wait (sub_53BEF0).
void sub_53BD10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053bd10
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t2 = 0xF0000;
    t3 = a3;
    a3 = 0;
    sw(t0, sp, 0x0);
    t0 = 0;
    sw(t1, sp, 0x8);
    t1 = 0;
    t2 = t2 | 0xFFFF;
    sd(ra, sp, 0x20);
    link(ctx, 0x53BD38u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x10);
    call(ctx, gen::fn_sub_53BEF0_0053bef0);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0053BDD8 sub_53BDD8 -- 80 bytes; frame 0x30: ra sp+0x20
// Loads a partition by file name, extended form (sub_53BEF0, last flag 1).
void sub_53BDD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053bdd8
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = a2;
    v0 = a1;
    a1 = 0;
    t2 = 0xF0000;
    t3 = a3;
    sw(t0, sp, 0x0);
    t0 = v1;
    a3 = v0;
    v0 = 1;
    sw(t1, sp, 0x8);
    t1 = 0;
    a2 = 0;
    t2 = t2 | 0xFFFF;
    sd(ra, sp, 0x20);
    link(ctx, 0x53BE14u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x10);
    call(ctx, gen::fn_sub_53BEF0_0053bef0);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0053BEB0 sub_53BEB0 -- 64 bytes; frame 0x30: ra sp+0x20
// Loads a partition by range, extended form (sub_53BEF0, last flag 1).
void sub_53BEB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053beb0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t2 = 0xF0000;
    t3 = a3;
    a3 = 0;
    sw(t0, sp, 0x0);
    t0 = 0;
    sw(t1, sp, 0x8);
    t1 = 0;
    v0 = 1;
    t2 = t2 | 0xFFFF;
    sd(ra, sp, 0x20);
    link(ctx, 0x53BEDCu);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x10);
    call(ctx, gen::fn_sub_53BEF0_0053bef0);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0053C198 sub_53C198 -- 64 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Closes the partition loader's handle (0x7853D0) and clears its state.
void sub_53C198(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053c198
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = 0x780000;
    sd(ra, sp, 0x8);
    s0 = addiu(s0, 21456);  // &0x7853D0
    link(ctx, 0x53C1ACu);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 0);  // 0x7853D0
    call(ctx, gen::fn_sub_53CE00_0053ce00);
    sw(zero, s0, 0);  // 0x7853D0
    ld(ra, sp, 0x8);
    v0 = 0x780000;
    ld(s0, sp, 0x0);
    v1 = 0x780000;
    sw(zero, v0, 21452);  // 0x7853CC
    sw(zero, v1, 21476);  // 0x7853E4
    sp = addiu(sp, 0x10);
}

// 0x0053C268 sub_53C268 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Locked wrapper of sub_53C2A0 (ADXCRS lock / unlock).
void sub_53C268(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053c268
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53C274u, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    jal(ctx, 0x53C27Cu, gen::fn_sub_53C2A0_0053c2a0);
    s0 = v0;
    jal(ctx, 0x53C284u, gen::fn_sub_53E0A0_0053e0a0);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053C758 sub_53C758 -- 24 bytes; leaf frame (no stack)
// The partition record's word +4 (the file count).
void sub_53C758(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0053c758
    enter(ctx, 6);  // entry check point + this block's cycles
    a0 = sll(a0, 2);
    v1 = 0x780000;
    v1 = addu(v1, a0);
    lw(v1, v1, 20128);
    lw(v0, v1, 4);
}

// 0x0053C770 sub_53C770 -- 88 bytes; leaf frame (no stack)
// First free ADXF handle in the table at 0x784A60 (16 x 68 bytes), or 0.
void sub_53C770(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0053c770
    enter(ctx, 6);  // entry check point + this block's cycles
    a2 = 0x780000;
    a3 = 0;
    v1 = addiu(a2, 19040);  // &0x784A60
    lb(v0, v1, 0);  // 0x784A60
    a1 = 0;
    if (v0 != 0) {
        // 0x0053c790
        charge(ctx, 1);
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x0053c794
            charge(ctx, 4);
            v0 = sll(a1, 4);
            v1 = slti(a1, 16);
            v0 = addu(v0, a1);
            if (v1 == 0) {
                break;
            }
            // 0x0053c7a4
            charge(ctx, 6);
            v0 = sll(v0, 2);
            v1 = addiu(a2, 19040);
            v0 = addu(v0, v1);
            lb(a0, v0, 0);
            if (a0 == 0) {
                goto L_0053c7bc_5;
            }
            a1 = addiu(a1, 1);
            backedge(ctx);
        }
    } else {
        // 0x0053c788
        charge(ctx, 2);
        a3 = v1;
    }
    // 0x0053c7c0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a3;
    return;
L_0053c7bc_5:
    charge(ctx, 1);
    a3 = v0;
    // 0x0053c7c0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a3;
}

// 0x0053C7C8 sub_53C7C8 -- 148 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Allocates an ADXF handle: a free slot plus an ADXSTM handle (sub_545FC8); sets used, stat 1, the request size 512
// sectors; 'E04041201' / 'E02111001' and 0 on failure.
// [proposed name] adxf_CreateAdxFs: the function's own error text names it.
void sub_53C7C8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053c7c8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    jal(ctx, 0x53C7D4u, gen::fn_sub_53C770_0053c770);
    s0 = v0;
    a0 = 0x7C0000;
    a0 = addiu(a0, 7480);  // "E04041201:not enough ADXF handle (adxf_CreateAdxFs)"
    a1 = 256;
    if (s0 != 0) {
        // 0x0053c7f0
        charge(ctx, 7);
        a0 = 0;
        jal(ctx, 0x53C7F0u, gen::fn_sub_545FC8_00545fc8);
        v1 = 1;
        a0 = 0x7C0000;
        sw(v0, s0, adxf::kStm);
        a0 = addiu(a0, 7536);  // "E02111001:can't create stm handle (adxf_CreateAdxFs)"
        if (v0 == 0) {
            goto L_0053c80c;
        }
        // 0x0053c820
        charge(ctx, 11);
        v0 = 512;
        sb(v1, s0, adxf::kUsed);
        sb(v1, s0, adxf::kStat);
        sw(zero, s0, adxf::kReqStart);
        sw(zero, s0, adxf::kReqNsct);
        sw(zero, s0, adxf::kReadNsct);
        sb(zero, s0, adxf::kSjFlag);
        sw(zero, s0, adxf::kSj);
        sb(zero, s0, 3);
        sw(v0, s0, adxf::kMaxReqSct);
        v0 = s0;
        // 0x0053c84c (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_0053c80c:
    charge(ctx, 4);
    jal(ctx, 0x53C80Cu, gen::fn_sub_53AE08_0053ae08);
    v0 = 0;
    // 0x0053c84c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0053C860 adxf_SetFileInfoEx -- 176 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Sets a handle's file by name: the stream's file info (sub_5461C8), -1 when the stream reports an error, else the
// size in bytes and sectors.
void adxf_SetFileInfoEx(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053c860
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    v0 = a2;
    if (v1 != 0) {
        // 0x0053c890
        charge(ctx, 13);
        sw(v1, s0, adxf::kName);
        t0 = 0xF0000;
        sw(v0, s0, adxf::kDir);
        a3 = 0;
        lw(a0, s0, adxf::kStm);
        t0 = t0 | 0xFFFF;
        link(ctx, 0x53C8A8u);  // $ra first: the delay slot below depends on it
        sw(zero, s0, adxf::kOfst);
        call(ctx, gen::fn_sub_5461C8_005461c8);
        link(ctx, 0x53C8B0u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, adxf::kStm);
        call(ctx, gen::fn_sub_546368_00546368);
        v1 = 4;
        if (v0 != v1) {
            // 0x0053c8d8
            charge(ctx, 10);
            link(ctx, 0x53C8D8u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, adxf::kStm);
            call(ctx, gen::fn_sub_547068_00547068);
            lw(a0, s0, adxf::kStm);
            link(ctx, 0x53C8E4u);  // $ra first: the delay slot below depends on it
            sw(v0, s0, adxf::kFsizeByte);
            call(ctx, gen::fn_sub_5470A8_005470a8);
            sw(zero, s0, adxf::kRangeOfst);
            v1 = v0;
            v0 = 0;
            sw(v1, s0, adxf::kRangeNsct);
            sw(v1, s0, adxf::kFsizeSct);
        } else {
            // 0x0053c8c4
            charge(ctx, 4);
            link(ctx, 0x53C8C4u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, adxf::kStm);
            call(ctx, gen::fn_sub_5462E0_005462e0);
            v0 = si(-1);
        }
    } else {
        // 0x0053c87c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 7592);  // "E9081901:illigal parameter fname=null.(adxf_SetFileInfoEx)"
        jal(ctx, 0x53C880u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-1);
    }
    // 0x0053c900 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0053C9F8 sub_53C9F8 -- 128 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Sets a handle's file by range (name, dir, start sector, sectors): no size query, size = sectors * 2048.
void sub_53C9F8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053c9f8
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a3;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = t0;
    sd(ra, sp, 0x10);
    sw(a2, s0, 52);
    sw(v0, s0, 60);
    sw(a1, s0, 56);
    sw(v0, s0, 48);
    lw(a0, s0, 4);
    sw(s1, s0, 64);
    link(ctx, 0x53CA2Cu);  // $ra first: the delay slot below depends on it
    sw(zero, s0, 20);
    call(ctx, gen::fn_sub_5461C8_005461c8);
    link(ctx, 0x53CA34u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 4);
    call(ctx, gen::fn_sub_546368_00546368);
    v1 = 4;
    a0 = sll(s1, 11);
    if (v0 != v1) {
        // 0x0053ca58
        charge(ctx, 3);
        sw(a0, s0, 16);
        v0 = 0;
        sw(s1, s0, 12);
    } else {
        // 0x0053ca48
        charge(ctx, 4);
        link(ctx, 0x53CA48u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 4);
        call(ctx, gen::fn_sub_5462E0_005462e0);
        v0 = si(-1);
    }
    // 0x0053ca64 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0053CAE0 sub_53CAE0 -- 192 bytes; frame 0x30: s3 sp+0x18, s4 sp+0x20, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x28
// Opens an ADXF handle on a sector range (log id 1).
void sub_53CAE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053cae0
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t0 = si(-1);
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    s4 = a0;
    sd(s0, sp, 0x0);
    s0 = a3;
    sd(s1, sp, 0x8);
    s1 = a2;
    a0 = 1;
    a1 = 0;
    a2 = s4;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x28);
    a3 = s3;
    jal(ctx, 0x53CB1Cu, gen::fn_sub_53B5D0_0053b5d0);
    jal(ctx, 0x53CB24u, gen::fn_sub_53C7C8_0053c7c8);
    a3 = s1;
    s2 = v0;
    t0 = s0;
    a0 = s2;
    a1 = s4;
    a2 = s3;
    if (s2 != 0) {
        // 0x0053cb48
        charge(ctx, 4);
        jal(ctx, 0x53CB48u, gen::fn_sub_53C9F8_0053c9f8);
        a2 = s4;
        if (i64(v0) < 0) {
            // 0x0053cb58
            charge(ctx, 3);
            a0 = s2;
            s2 = 0;
            jal(ctx, 0x53CB5Cu, gen::fn_sub_53CE00_0053ce00);
            goto L_0053cb64;
        }
        goto L_0053cb68;
    }
L_0053cb64:
    charge(ctx, 1);
    a2 = s4;
L_0053cb68:
    charge(ctx, 14);
    a3 = s3;
    a0 = 1;
    a1 = 1;
    t0 = si(-1);
    jal(ctx, 0x53CB74u, gen::fn_sub_53B5D0_0053b5d0);
    v0 = s2;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0053CBA0 sub_53CBA0 -- 212 bytes; frame 0x130: s0 sp+0x110, s1 sp+0x118, ra sp+0x120
// Sets a handle's file from a partition entry (sub_53DD98 for the range, sub_53DF28 for the name); -3 for a bad id.
void sub_53CBA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053cba0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    sd(s0, sp, 0x110);
    s0 = a1;
    sd(s1, sp, 0x118);
    s1 = a0;
    a1 = a2;
    a2 = sp;
    a0 = s0;
    a3 = addiu(sp, 0x100);
    t0 = addiu(sp, 0x104);
    sd(ra, sp, 0x120);
    t1 = addiu(sp, 0x108);
    jal(ctx, 0x53CBCCu, gen::fn_sub_53DD98_0053dd98);
    a0 = s0;
    if (i64(v0) >= 0) {
        // 0x0053cbe8
        charge(ctx, 22);
        lw(v1, sp, 0x100);
        lw(v0, sp, 0x104);
        sw(v1, s1, 52);
        link(ctx, 0x53CBF4u);  // $ra first: the delay slot below depends on it
        sw(v0, s1, 48);
        call(ctx, gen::fn_sub_53DF28_0053df28);
        sw(zero, s1, 20);
        lw(a2, s1, 52);
        a1 = v0;
        lw(v1, sp, 0x108);
        lw(a0, sp, 0x104);
        sw(v1, s1, 64);
        t0 = v1;
        a3 = a0;
        sw(v0, s1, 56);
        sw(a0, s1, 60);
        link(ctx, 0x53CC24u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 4);
        call(ctx, gen::fn_sub_5461C8_005461c8);
        link(ctx, 0x53CC2Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 4);
        call(ctx, gen::fn_sub_546368_00546368);
        v1 = 4;
        if (v0 != v1) {
            lw(a0, sp, 0x108);
            // 0x0053cc50
            charge(ctx, 4);
            v0 = 0;
            v1 = sll(a0, 11);
            sw(a0, s1, 12);
            sw(v1, s1, 16);
        } else {
            // 0x0053cc40
            charge(ctx, 4);
            link(ctx, 0x53CC40u);  // $ra first: the delay slot below depends on it
            lw(a0, s1, 4);
            call(ctx, gen::fn_sub_5462E0_005462e0);
            v0 = si(-1);
        }
    } else {
        // 0x0053cbdc
        charge(ctx, 2);
        v0 = si(-3);
    }
    // 0x0053cc60 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x110);
    ld(s1, sp, 0x118);
    ld(ra, sp, 0x120);
    sp = addiu(sp, 0x130);
}

// 0x0053CCC0 sub_53CCC0 -- 160 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// Opens an ADXF handle on a partition entry (log id 2).
void sub_53CCC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053ccc0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = si(-1);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a0;
    a1 = 0;
    a2 = s2;
    a0 = 2;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    a3 = s1;
    jal(ctx, 0x53CCECu, gen::fn_sub_53B5D0_0053b5d0);
    jal(ctx, 0x53CCF4u, gen::fn_sub_53C7C8_0053c7c8);
    a1 = s2;
    s0 = v0;
    a2 = s1;
    a0 = s0;
    if (s0 != 0) {
        // 0x0053cd10
        charge(ctx, 4);
        jal(ctx, 0x53CD10u, gen::fn_sub_53CBA0_0053cba0);
        a2 = s2;
        if (i64(v0) < 0) {
            // 0x0053cd20
            charge(ctx, 3);
            a0 = s0;
            s0 = 0;
            jal(ctx, 0x53CD24u, gen::fn_sub_53CE00_0053ce00);
            goto L_0053cd2c;
        }
        goto L_0053cd30;
    }
L_0053cd2c:
    charge(ctx, 1);
    a2 = s2;
L_0053cd30:
    charge(ctx, 12);
    a3 = s1;
    a0 = 2;
    a1 = 1;
    t0 = si(-1);
    jal(ctx, 0x53CD3Cu, gen::fn_sub_53B5D0_0053b5d0);
    v0 = s0;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0053CD60 sub_53CD60 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Read completion: when the transfer is done and a joint is set, invalidates the cache over the buffer (flag 0x7852A0)
// and hands the data to the joint (vtable call).
void sub_53CD60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053cd60
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(a1, s0, 8);
    if (a1 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0053cd7c
        charge(ctx, 3);
        lb(v0, s0, 2);
        if (v0 != 0) {
            ld(s0, sp, 0x0);
        } else {
            // 0x0053cd88
            charge(ctx, 5);
            v0 = 0x780000;
            a0 = 1;
            lw(v1, v0, 21152);  // 0x7852A0
            if (v1 != a0) {
                lw(v1, a1, 0);
            } else {
                // 0x0053cd9c
                charge(ctx, 5);
                lw(a1, s0, 40);
                link(ctx, 0x53CDA0u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 36);
                call(ctx, gen::fn_sub_53B060_0053b060);
                lw(a1, s0, 8);
                lw(v1, a1, 0);
            }
            // 0x0053cdb0
            charge(ctx, 5);
            sw(zero, s0, 8);
            lw(v0, v1, 12);
            a0 = a1;
            jalr(ctx, 0x53CDB8u, v0.u());
            ld(s0, sp, 0x0);
        }
    }
    // 0x0053cdc4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0053CDD0 sub_53CDD0 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXF_Close: the locked sub_53CE00.
void sub_53CDD0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053cdd0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53CDDCu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    jal(ctx, 0x53CDE4u, gen::fn_sub_53CE00_0053ce00);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_53E0A0_0053e0a0(ctx);  // tail call
}

// 0x0053CE00 sub_53CE00 -- 180 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Closes an ADXF handle: stops a running read, releases the stream (sub_5462E0, sub_546058), clears the 68 bytes (log
// id 3).
void sub_53CE00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053ce00
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 0;
    sd(s1, sp, 0x8);
    s1 = a0;
    a2 = s1;
    a3 = si(-1);
    a0 = 3;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    t0 = si(-1);
    jal(ctx, 0x53CE24u, gen::fn_sub_53B5D0_0053b5d0);
    v1 = 2;
    if (s1 == 0) {
        // 0x0053cea0
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0053ce34
    charge(ctx, 3);
    lb(v0, s1, 1);
    if (v0 != v1) {
        lw(s0, s1, 4);
    } else {
        // 0x0053ce40
        charge(ctx, 3);
        a0 = s1;
        jal(ctx, 0x53CE40u, gen::fn_sub_53D450_0053d450);
        lw(s0, s1, 4);
    }
    // 0x0053ce4c
    charge(ctx, 2);
    a0 = s0;
    if (s0 != 0) {
        // 0x0053ce54
        charge(ctx, 5);
        sb(zero, s1, 0);
        link(ctx, 0x53CE58u);  // $ra first: the delay slot below depends on it
        sw(zero, s1, 4);
        call(ctx, gen::fn_sub_5462E0_005462e0);
        a0 = s0;
        jal(ctx, 0x53CE60u, gen::fn_sub_546058_00546058);
    }
    // 0x0053ce68
    charge(ctx, 14);
    a0 = s1;
    a1 = 0;
    a2 = 68;
    jal(ctx, 0x53CE70u, gen::fn_memset_00521408);
    a0 = 3;
    a2 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    a1 = 1;
    ld(ra, sp, 0x10);
    a3 = si(-1);
    t0 = si(-1);
    sp = addiu(sp, 0x20);
    gen::fn_sub_53B5D0_0053b5d0(ctx);  // tail call
}

// 0x0053CEB8 sub_53CEB8 -- 36 bytes; frame 0x10: ra sp+0x0
// ADXF_CloseAll: the locked sub_53CEE0.
void sub_53CEB8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053ceb8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x53CEC0u, gen::fn_sub_53E088_0053e088);
    jal(ctx, 0x53CEC8u, gen::fn_sub_53CEE0_0053cee0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_53E0A0_0053e0a0(ctx);  // tail call
}

// 0x0053CEE0 sub_53CEE0 -- 96 bytes; frame 0x20: ra sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// Closes every used handle of the table.
void sub_53CEE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053cee0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x780000;
    sd(ra, sp, 0x18);
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 19040);  // &0x784A60
    sd(s1, sp, 0x8);
    s1 = 15;
    sd(s2, sp, 0x10);
    s2 = 1;
    for (;;) {
        // 0x0053cf08
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x0053cf14
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x53CF14u, gen::fn_sub_53CE00_0053ce00);
            s1 = addiu(s1, -1);
        }
        // 0x0053cf20
        charge(ctx, 2);
        s0 = addiu(s0, 68);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0053cf28
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0053CF40 sub_53CF40 -- 256 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Starts a read of up to n sectors into a joint: clamps to the file end, stores the request (+24, +28), sets up and
// starts the stream.
void sub_53CF40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053cf40
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    link(ctx, 0x53CF60u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 4);
    call(ctx, gen::fn_sub_546368_00546368);
    v1 = 1;
    if (v0 != v1) {
        // 0x0053cf74
        charge(ctx, 2);
        link(ctx, 0x53CF74u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 4);
        call(ctx, gen::fn_sub_546638_00546638);
    }
    // 0x0053cf7c
    charge(ctx, 14);
    jal(ctx, 0x53CF7Cu, gen::fn_sub_539818_00539818);
    lw(a2, s0, 20);
    lw(v0, s0, 12);
    a1 = si(-1);
    lw(v1, s0, 48);
    v0 = subu(v0, a2);
    sw(zero, s0, 32);
    a0 = slt(s1, v0);
    v1 = addu(v1, a2);
    if (a0 != 0) v0 = s1;
    sw(v1, s0, 24);
    sw(v0, s0, 28);
    if (v0 != 0) {
        // 0x0053cfc8
        charge(ctx, 21);
        link(ctx, 0x53CFC8u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 4);
        call(ctx, gen::fn_sub_546718_00546718);
        lw(a0, s0, 4);
        a1 = s2;
        jal(ctx, 0x53CFD4u, gen::fn_sub_547318_00547318);
        lw(a0, s0, 4);
        link(ctx, 0x53CFE0u);  // $ra first: the delay slot below depends on it
        lw(a1, s0, 44);
        call(ctx, gen::fn_sub_547008_00547008);
        v1 = 2;
        sb(v1, s0, 1);
        a1 = 0;
        lw(a0, s0, 4);
        link(ctx, 0x53CFF8u);  // $ra first: the delay slot below depends on it
        sb(zero, s0, 3);
        call(ctx, gen::fn_sub_547138_00547138);
        lw(a0, s0, 4);
        link(ctx, 0x53D004u);  // $ra first: the delay slot below depends on it
        lw(a1, s0, 20);
        call(ctx, gen::fn_sub_5463A8_005463a8);
        lw(a0, s0, 4);
        link(ctx, 0x53D010u);  // $ra first: the delay slot below depends on it
        lw(a1, s0, 28);
        call(ctx, gen::fn_sub_546510_00546510);
        lw(s0, s0, 28);
    } else {
        // 0x0053cfb4
        charge(ctx, 4);
        v0 = 3;
        sb(v0, s0, 1);
        s0 = 0;
    }
    // 0x0053d01c
    charge(ctx, 9);
    jal(ctx, 0x53D01Cu, gen::fn_sub_539830_00539830);
    v0 = s0;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0053D098 sub_53D098 -- 140 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXF_ReadSj32 checks: 'E9040811' null handle, 'E9040812' negative count, 'E9040813' null joint; -3, else sub_53CF40.
// [proposed name] adxf_ReadSj32: the function's own error text names it.
void sub_53D098(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d098
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    v1 = a2;
    if (s0 == 0) {
        // 0x0053d0b4
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 7656);  // "E9040811:'adxf' is NULL.(adxf_ReadSj32)"
        goto L_0053d0e8;
    }
    // 0x0053d0c0
    charge(ctx, 2);
    if (i64(v0) < 0) {
        // 0x0053d0c8
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 7696);  // "E9040812:'nsct'is negative.(adxf_ReadSj32)"
        goto L_0053d0e8;
    }
    // 0x0053d0d8
    charge(ctx, 2);
    if (v1 != 0) {
        lb(a3, s0, 1);
        // 0x0053d0f8
        charge(ctx, 3);
        v1 = 2;
        v0 = 0;
        if (a3 != v1) {
            // 0x0053d104
            charge(ctx, 4);
            jal(ctx, 0x53D104u, gen::fn_sub_53CF40_0053cf40);
            v1 = 1;
            sb(v1, s0, 2);
        }
    } else {
        // 0x0053d0e0
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 7744);  // "E9040813:'sj'is NULL.(adxf_ReadSj32)"
    L_0053d0e8:
        charge(ctx, 4);
        jal(ctx, 0x53D0E8u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-3);
    }
    // 0x0053d114 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0053D180 sub_53D180 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk to sub_53D098.
void sub_53D180(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d180
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_53D098_0053d098(ctx);  // tail call
}

// 0x0053D1F0 adxf_ReadNw32 -- 396 bytes; frame 0x30: s0 sp+0x0, s3 sp+0x18, s4 sp+0x20, s1 sp+0x8, s2 sp+0x10, ra sp+0x28
// Reads n sectors into a buffer through a ring joint over it (no wait); checks the handle, the count, the buffer and
// that no joint is set.
void adxf_ReadNw32(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d1f0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(s4, sp, 0x20);
    s4 = a1;
    a0 = 4;
    a2 = s0;
    a1 = 0;
    a3 = s4;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x28);
    t0 = s3;
    jal(ctx, 0x53D228u, gen::fn_sub_53B5D0_0053b5d0);
    a0 = 0x7C0000;
    if (s0 == 0) {
        // 0x0053d238
        charge(ctx, 2);
        a0 = addiu(a0, 7784);
        goto L_0053d260;
    }
    // 0x0053d240
    charge(ctx, 2);
    a0 = 0x7C0000;
    if (i64(s4) < 0) {
        // 0x0053d248
        charge(ctx, 2);
        a0 = addiu(a0, 7824);
        goto L_0053d260;
    }
    // 0x0053d250
    charge(ctx, 2);
    if (s3 != 0) {
        lb(a0, s0, 1);
        // 0x0053d270
        charge(ctx, 3);
        v1 = 2;
        v0 = 0;
        if (a0 != v1) {
            // 0x0053d27c
            charge(ctx, 3);
            lw(v0, s0, 8);
            a0 = 0x7C0000;
            if (v0 == 0) {
                // 0x0053d298
                charge(ctx, 8);
                s2 = sll(s4, 11);
                a0 = s3;
                a1 = s2;
                a2 = 0;
                jal(ctx, 0x53D2A4u, gen::fn_sub_562388_00562388);
                s1 = v0;
                v0 = si(-2);
                if (s1 != 0) {
                    // 0x0053d2b8
                    charge(ctx, 10);
                    jal(ctx, 0x53D2B8u, gen::fn_sub_539818_00539818);
                    sw(s3, s0, 36);
                    sw(s1, s0, 8);
                    a0 = 0x780000;
                    sw(s2, s0, 40);
                    v1 = 1;
                    lw(v0, a0, 21152);  // 0x7852A0
                    a1 = s2;
                    if (v0 == v1) {
                        // 0x0053d2e0
                        charge(ctx, 2);
                        a0 = s3;
                        jal(ctx, 0x53D2E0u, gen::fn_sub_53B060_0053b060);
                    }
                    // 0x0053d2e8
                    charge(ctx, 9);
                    jal(ctx, 0x53D2E8u, gen::fn_sub_539830_00539830);
                    a0 = s0;
                    lw(a2, s0, 8);
                    a1 = s4;
                    jal(ctx, 0x53D2F8u, gen::fn_sub_53CF40_0053cf40);
                    s1 = v0;
                    if (i64(s1) > 0) {
                        sb(zero, s0, 2);
                    } else {
                        // 0x0053d30c
                        charge(ctx, 5);
                        jal(ctx, 0x53D30Cu, gen::fn_sub_539818_00539818);
                        lw(a0, s0, 8);
                        if (a0 != 0) {
                            // 0x0053d320
                            charge(ctx, 5);
                            lw(v1, a0, 0);
                            lw(v0, v1, 12);
                            jalr(ctx, 0x53D328u, v0.u());
                            sw(zero, s0, 8);
                        }
                        // 0x0053d334
                        charge(ctx, 3);
                        jal(ctx, 0x53D334u, gen::fn_sub_539830_00539830);
                        sb(zero, s0, 2);
                    }
                    // 0x0053d340
                    charge(ctx, 7);
                    a2 = s0;
                    a3 = s4;
                    t0 = s3;
                    a0 = 4;
                    a1 = 1;
                    jal(ctx, 0x53D350u, gen::fn_sub_53B5D0_0053b5d0);
                    v0 = s1;
                }
            } else {
                // 0x0053d288
                charge(ctx, 4);
                a0 = addiu(a0, 7912);
                jal(ctx, 0x53D288u, gen::fn_sub_53AE08_0053ae08);
                v0 = si(-1);
            }
        }
    } else {
        // 0x0053d258
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 7872);  // "E9040818:'buf' is NULL.(adxf_ReadNw32)"
    L_0053d260:
        charge(ctx, 4);
        jal(ctx, 0x53D260u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-3);
    }
    // 0x0053d35c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0053D450 sub_53D450 -- 236 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Stops a read: stops the stream (sub_546638), takes the read count, completes it (sub_53CD60); 'E9040822' /
// 'E9040823'.
// [proposed name] adxf_Stop: the function's own error text names it.
void sub_53D450(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d450
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 0;
    sd(s0, sp, 0x0);
    s0 = a0;
    a2 = s0;
    a3 = si(-1);
    a0 = 5;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    t0 = si(-1);
    jal(ctx, 0x53D474u, gen::fn_sub_53B5D0_0053b5d0);
    a0 = 0x7C0000;
    a0 = addiu(a0, 8016);  // "E9040822:'adxf' is NULL.(adxf_Stop)"
    if (s0 != 0) {
        // 0x0053d498
        charge(ctx, 4);
        lb(v1, s0, 1);
        s1 = 1;
        v0 = 3;
        if (v1 != s1) {
            // 0x0053d4a8
            charge(ctx, 2);
            if (v1 == v0) {
                // 0x0053d4b0
                charge(ctx, 2);
                sb(s1, s0, 1);
                goto L_0053d524;
            }
            lw(a0, s0, 4);
            // 0x0053d4b8
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x0053d4d8
                charge(ctx, 19);
                jal(ctx, 0x53D4D8u, gen::fn_sub_546638_00546638);
                jal(ctx, 0x53D4E0u, gen::fn_sub_539818_00539818);
                link(ctx, 0x53D4E8u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 4);
                call(ctx, gen::fn_sub_546410_00546410);
                lw(v1, s0, 20);
                a0 = s0;
                v0 = subu(v0, v1);
                link(ctx, 0x53D4FCu);  // $ra first: the delay slot below depends on it
                sw(v0, s0, 32);
                call(ctx, gen::fn_sub_53CD60_0053cd60);
                link(ctx, 0x53D504u);  // $ra first: the delay slot below depends on it
                sb(s1, s0, 1);
                call(ctx, gen::fn_sub_539830_00539830);
                a0 = 5;
                a1 = 1;
                a2 = s0;
                a3 = si(-1);
                t0 = si(-1);
                jal(ctx, 0x53D51Cu, gen::fn_sub_53B5D0_0053b5d0);
                goto L_0053d524;
            }
            // 0x0053d4c0
            charge(ctx, 5);
            a0 = 0x7C0000;
            a0 = addiu(a0, 8056);  // "E9040823:'adxf->stm' is NULL.(adxf_Stop)"
            jal(ctx, 0x53D4C4u, gen::fn_sub_53AE08_0053ae08);
            v0 = si(-1);
            // 0x0053d528 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x10);
            sp = addiu(sp, 0x20);
            return;
        }
    L_0053d524:
        charge(ctx, 1);
        lw(v0, s0, 20);
    } else {
        // 0x0053d488
        charge(ctx, 4);
        jal(ctx, 0x53D488u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-3);
    }
    // 0x0053d528 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0053D578 sub_53D578 -- 196 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Stops a read without completion (sub_5465A0); 'E2092301' / 'E2092302'.
// [proposed name] adxf_StopNw: the function's own error text names it.
void sub_53D578(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d578
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 0;
    sd(s0, sp, 0x0);
    s0 = a0;
    a2 = s0;
    a3 = si(-1);
    a0 = 7;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    t0 = si(-1);
    jal(ctx, 0x53D59Cu, gen::fn_sub_53B5D0_0053b5d0);
    a0 = 0x7C0000;
    a0 = addiu(a0, 8104);  // "E2092301:'adxf' is NULL.(adxf_StopNw)"
    if (s0 != 0) {
        // 0x0053d5c0
        charge(ctx, 4);
        lb(v1, s0, 1);
        s1 = 1;
        v0 = 3;
        if (v1 != s1) {
            // 0x0053d5d0
            charge(ctx, 2);
            if (v1 == v0) {
                // 0x0053d5d8
                charge(ctx, 2);
                sb(s1, s0, 1);
                goto L_0053d624;
            }
            lw(a0, s0, 4);
            // 0x0053d5e0
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x0053d600
                charge(ctx, 9);
                jal(ctx, 0x53D600u, gen::fn_sub_5465A0_005465a0);
                sb(s1, s0, 3);
                a0 = 7;
                a1 = 1;
                a2 = s0;
                a3 = si(-1);
                t0 = si(-1);
                jal(ctx, 0x53D61Cu, gen::fn_sub_53B5D0_0053b5d0);
                goto L_0053d624;
            }
            // 0x0053d5e8
            charge(ctx, 5);
            a0 = 0x7C0000;
            a0 = addiu(a0, 8144);  // "E2092302:'adxf->stm' is NULL.(adxf_StopNw)"
            jal(ctx, 0x53D5ECu, gen::fn_sub_53AE08_0053ae08);
            v0 = si(-1);
            // 0x0053d628 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x10);
            sp = addiu(sp, 0x20);
            return;
        }
    L_0053d624:
        charge(ctx, 1);
        lw(v0, s0, 20);
    } else {
        // 0x0053d5b0
        charge(ctx, 4);
        jal(ctx, 0x53D5B0u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-3);
    }
    // 0x0053d628 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0053D640 adxf_ExecOne -- 200 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// One server step of a reading handle: the stream's state into +1, the sectors read into +32, the position advanced
// and the completion run when the read ended.
void adxf_ExecOne(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d640
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 2;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lb(v0, s0, 1);
    if (v0 != v1) {
        lb(s1, s0, 3);
    } else {
        // 0x0053d668
        charge(ctx, 14);
        link(ctx, 0x53D668u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 4);
        call(ctx, gen::fn_sub_546368_00546368);
        lw(a0, s0, 4);
        link(ctx, 0x53D674u);  // $ra first: the delay slot below depends on it
        sb(v0, s0, 1);
        call(ctx, gen::fn_sub_546410_00546410);
        a0 = s0;
        lbu(v1, s0, 1);
        lw(a1, s0, 20);
        v1 = addiu(v1, -3);
        v0 = subu(v0, a1);
        v1 = sltiu(v1, 2);
        a1 = addu(a1, v0);
        sw(v0, s0, 32);
        if (v1 != 0) {
            // 0x0053d6a0
            charge(ctx, 2);
            link(ctx, 0x53D6A0u);  // $ra first: the delay slot below depends on it
            sw(a1, s0, 20);
            call(ctx, gen::fn_sub_53CD60_0053cd60);
        }
        // 0x0053d6a8
        charge(ctx, 1);
        lb(s1, s0, 3);
    }
    // 0x0053d6ac
    charge(ctx, 3);
    v0 = 1;
    if (s1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0053d6b8
        charge(ctx, 5);
        link(ctx, 0x53D6B8u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 4);
        call(ctx, gen::fn_sub_546368_00546368);
        s2 = v0;
        if (s2 != s1) {
            ld(s0, sp, 0x0);
        } else {
            // 0x0053d6cc
            charge(ctx, 10);
            link(ctx, 0x53D6CCu);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 4);
            call(ctx, gen::fn_sub_546410_00546410);
            lw(v1, s0, 20);
            a0 = s0;
            v0 = subu(v0, v1);
            link(ctx, 0x53D6E0u);  // $ra first: the delay slot below depends on it
            sw(v0, s0, 32);
            call(ctx, gen::fn_sub_53CD60_0053cd60);
            sb(s2, s0, 1);
            sb(zero, s0, 3);
            ld(s0, sp, 0x0);
        }
    }
    // 0x0053d6f4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0053D7E8 sub_53D7E8 -- 276 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Seek: type 0 from the start, 1 from the current, 2 from the end; clamped to [0, size]; stops a running read first;
// 'E9040825' / 'E9040826'.
// [proposed name] adxf_Seek: the function's own error text names it.
void sub_53D7E8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d7e8
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a1;
    a0 = 6;
    a2 = s0;
    a1 = 0;
    a3 = s2;
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    t0 = s1;
    jal(ctx, 0x53D81Cu, gen::fn_sub_53B5D0_0053b5d0);
    if (s0 == 0) {
        // 0x0053d82c
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 8192);  // "E9040825:'adxf' is NULL.(adxf_Seek)"
        goto L_0053d88c;
    }
    lb(v0, s0, 1);
    // 0x0053d838
    charge(ctx, 3);
    s3 = 2;
    if (v0 == s3) {
        // 0x0053d844
        charge(ctx, 2);
        a0 = s0;
        jal(ctx, 0x53D844u, gen::fn_sub_53D450_0053d450);
    }
    // 0x0053d84c
    charge(ctx, 2);
    v0 = 1;
    if (s1 == 0) {
        // 0x0053d854
        charge(ctx, 2);
        sw(s2, s0, 20);
        goto L_0053d8a0;
    }
    // 0x0053d860
    charge(ctx, 2);
    if (s1 == v0) {
        // 0x0053d868
        charge(ctx, 2);
        lw(v0, s0, 20);
        goto L_0053d87c;
    }
    // 0x0053d870
    charge(ctx, 2);
    a0 = 0x7C0000;
    if (s1 != s3) {
        // 0x0053d888
        charge(ctx, 1);
        a0 = addiu(a0, 8232);
    L_0053d88c:
        charge(ctx, 4);
        jal(ctx, 0x53D88Cu, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-3);
    } else {
        // 0x0053d878
        charge(ctx, 1);
        lw(v0, s0, 12);
    L_0053d87c:
        charge(ctx, 3);
        v0 = addu(v0, s2);
        sw(v0, s0, 20);
    L_0053d8a0:
        charge(ctx, 3);
        lw(v0, s0, 20);
        if (i64(v0) >= 0) {
            lw(v1, s0, 12);
            // 0x0053d8b8
            charge(ctx, 3);
            v0 = slt(v1, v0);
            if (v0 != 0) {
                sw(v1, s0, 20);
            }
        } else {
            // 0x0053d8ac
            charge(ctx, 2);
            sw(zero, s0, 20);
        }
        // 0x0053d8c4
        charge(ctx, 7);
        a3 = s2;
        t0 = s1;
        a0 = 6;
        a1 = 1;
        a2 = s0;
        jal(ctx, 0x53D8D4u, gen::fn_sub_53B5D0_0053b5d0);
        lw(v0, s0, 20);
    }
    // 0x0053d8e0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0053D938 sub_53D938 -- 48 bytes; frame 0x10: ra sp+0x0
// Tell: the current sector (+20); -3 for a null handle.
// [proposed name] adxf_Tell: the function's own error text names it.
void sub_53D938(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d938
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0053d958
        charge(ctx, 1);
        lw(v0, a0, adxf::kOfst);
    } else {
        // 0x0053d944
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 8272);  // "E9040827:'adxf' is NULL.(ADXF_Tell)"
        jal(ctx, 0x53D948u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-3);
    }
    // 0x0053d95c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053D9A0 adxf_GetFsizeSct -- 64 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// File size in sectors (bytes rounded up), also stored at +12.
void adxf_GetFsizeSct(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d9a0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53D9ACu, gen::fn_sub_53DA18_0053da18);
    v1 = v0;
    ld(ra, sp, 0x8);
    v0 = addiu(v1, 2047);
    v1 = addiu(v1, 4094);
    a0 = slti(v0, 0);
    if (a0 != 0) v0 = v1;
    v0 = sra(v0, 11);
    sw(v0, s0, adxf::kFsizeSct);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053DA18 sub_53DA18 -- 120 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// File size in bytes: queries the stream when the cached size is unknown (> 0x7FFFF7FF); -5 on a stream error.
void sub_53DA18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0053da18
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 != 0) {
        // 0x0053da40
        charge(ctx, 6);
        lw(v1, s0, adxf::kFsizeByte);
        v0 = 0x7FFF0000;
        v0 = v0 | 0xF7FF;
        v0 = slt(v0, v1);
        if (v0 != 0) {
            // 0x0053da58
            charge(ctx, 7);
            link(ctx, 0x53DA58u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, adxf::kStm);
            call(ctx, gen::fn_sub_547598_00547598);
            link(ctx, 0x53DA60u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, adxf::kStm);
            call(ctx, gen::fn_sub_546368_00546368);
            v1 = 4;
            cc = v0 == v1;  // the condition, before the delay slot changes it
            v0 = si(-5);
            if (!cc) {
                goto L_0053da74;
            }
            // 0x0053da80 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(s0, sp, 0x0);
            ld(ra, sp, 0x8);
            sp = addiu(sp, 0x10);
            return;
        }
    L_0053da74:
        charge(ctx, 3);
        link(ctx, 0x53DA74u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, adxf::kStm);
        call(ctx, gen::fn_sub_547068_00547068);
        sw(v0, s0, adxf::kFsizeByte);
    } else {
        // 0x0053da2c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 8312);  // "E9040828:'adxf' is NULL.(adxf_GetFsizeSct)"
        jal(ctx, 0x53DA30u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-3);
    }
    // 0x0053da80 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0053DAD8 sub_53DAD8 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The requested range: start into *out (+24), returns the count (+28).
// [proposed name] adxf_GetNumReqSct: the function's own error text names it.
void sub_53DAD8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053dad8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(ra, sp, 0x8);
    if (a0 != 0) {
        // 0x0053db08
        charge(ctx, 3);
        lw(v0, a0, adxf::kReqStart);
        sw(v0, s0, 0);
        lw(v0, a0, adxf::kReqNsct);
    } else {
        // 0x0053daec
        charge(ctx, 6);
        a0 = 0x7C0000;
        a0 = addiu(a0, 8360);  // "E9040830:'adxf' is NULL.(adxf_GetNumReqSct)"
        jal(ctx, 0x53DAF0u, gen::fn_sub_53AE08_0053ae08);
        sw(zero, s0, 0);
        v0 = si(-3);
    }
    // 0x0053db14 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0053DB60 sub_53DB60 -- 48 bytes; frame 0x10: ra sp+0x0
// Sectors read by the last request (+32).
// [proposed name] adxf_GetNumReadSct: the function's own error text names it.
void sub_53DB60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053db60
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0053db80
        charge(ctx, 1);
        lw(v0, a0, adxf::kReadNsct);
    } else {
        // 0x0053db6c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 8408);  // "E9040831:'adxf' is NULL.(adxf_GetNumReadSct)"
        jal(ctx, 0x53DB70u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-3);
    }
    // 0x0053db84 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053DBC8 adxf_GetStat -- 48 bytes; frame 0x10: ra sp+0x0
// The handle's state (s8 at +1); -3 and 'E9040832' for a null handle.
void adxf_GetStat(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053dbc8
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0053dbe8
        charge(ctx, 1);
        lb(v0, a0, adxf::kStat);
    } else {
        // 0x0053dbd4
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 8456);  // "E9040832:'adxf' is NULL.(adxf_GetStat)"
        jal(ctx, 0x53DBD8u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-3);
    }
    // 0x0053dbec (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053DBF8 sub_53DBF8 -- 120 bytes; frame 0x10: ra sp+0x0
// Partition / file id check against the partition table: 'E9040828' for a bad ptid or flid; -3, else 0.
void sub_53DBF8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0053dbf8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = sll(a0, 2);
    a0 = sltiu(a0, 256);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0053dc0c
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 8496);  // "E9040828:'ptid' is range outside."
        goto L_0053dc58;
    }
    // 0x0053dc18
    charge(ctx, 5);
    a0 = 0x780000;
    a0 = addu(a0, v0);
    lw(a0, a0, 20128);
    if (a0 == 0) {
        // 0x0053dc2c
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 8496);  // "E9040828:'ptid' is range outside."
        goto L_0053dc58;
    }
    // 0x0053dc38
    charge(ctx, 2);
    if (i64(a1) < 0) {
        a0 = 0x7C0000;
    } else {
        // 0x0053dc40
        charge(ctx, 4);
        lw(v0, a0, 8);
        v0 = slt(a1, v0);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x0053dc50
            charge(ctx, 1);
            a0 = 0x7C0000;
            goto L_0053dc54;
        }
        // 0x0053dc64 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_0053dc54:
    charge(ctx, 1);
    a0 = addiu(a0, 8536);
L_0053dc58:
    charge(ctx, 3);
    jal(ctx, 0x53DC58u, gen::fn_sub_53AE08_0053ae08);
    v0 = si(-3);
    // 0x0053dc64 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053DCE8 sub_53DCE8 -- 40 bytes; frame 0x20: ra sp+0x10
// Partition entry range without the name (sub_53DD98 with a local).
void sub_53DCE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053dce8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a3;
    t1 = t0;
    t0 = v0;
    sd(ra, sp, 0x10);
    a3 = sp;
    jal(ctx, 0x53DCFCu, gen::fn_sub_53DD98_0053dd98);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0053DD98 sub_53DD98 -- 344 bytes; frame 0x50: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s7 sp+0x38, s1 sp+0x8, ra sp+0x40
// Partition entry: walks the size table to the file's start sector, returns the sector count, offset and the name
// (strncpy) for partition form 1.
void sub_53DD98(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053dd98
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = t1;
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    s5 = a3;
    sd(s6, sp, 0x30);
    s6 = t0;
    sd(s7, sp, 0x38);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x40);
    s7 = a2;
    jal(ctx, 0x53DDD4u, gen::fn_sub_53DBF8_0053dbf8);
    s4 = v0;
    if (i64(s4) >= 0) {
        v0 = sll(s0, 2);
        // 0x0053de00
        charge(ctx, 7);
        a0 = 1;
        s1 = 0x780000;
        s1 = addu(s1, v0);
        lw(s1, s1, 20128);
        lb(v1, s1, 15);
        if (v1 != a0) {
            lhu(s0, s1, 280);
            // 0x0053de60
            charge(ctx, 2);
            a1 = addiu(s1, 282);
            if (i64(s2) > 0) {
                // 0x0053de68
                charge(ctx, 2);
                a0 = a1;
                v1 = s2;
                for (;;) {
                    // 0x0053de70
                    charge(ctx, 7);
                    lhu(v0, a0, 0);
                    a0 = addiu(a0, 2);
                    v1 = addiu(v1, -1);
                    s0 = addu(s0, v0);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0053de8c
            charge(ctx, 3);
            v0 = sll(s2, 1);
            v0 = addu(v0, a1);
            lhu(v1, v0, 0);
        } else {
            // 0x0053de1c
            charge(ctx, 3);
            lw(s0, s1, 280);
            a1 = addiu(s1, 284);
            if (i64(s2) > 0) {
                // 0x0053de28
                charge(ctx, 2);
                a0 = a1;
                v1 = s2;
                for (;;) {
                    // 0x0053de30
                    charge(ctx, 7);
                    lw(v0, a0, 0);
                    a0 = addiu(a0, 4);
                    v1 = addiu(v1, -1);
                    s0 = addu(s0, v0);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0053de4c
            charge(ctx, 4);
            v0 = sll(s2, 2);
            v0 = addu(v0, a1);
            lw(v1, v0, 0);
        }
        // 0x0053de98
        charge(ctx, 11);
        sw(v1, s3, 0);
        a0 = s7;
        a1 = addiu(s1, 16);
        a2 = 256;
        jal(ctx, 0x53DEA4u, gen::fn_strncpy_00524828);
        lw(a0, s1, 272);
        lw(v1, s1, 276);
        v0 = s4;
        sw(a0, s5, 0);
        v1 = addu(v1, s0);
        sw(v1, s6, 0);
    } else {
        // 0x0053dde8
        charge(ctx, 5);
        v1 = si(-1);
        sw(zero, s5, 0);
        sw(v1, s6, 0);
        sw(v1, s3, 0);
    }
    // 0x0053dec4 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s0, sp, 0x0);
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

// 0x0053DEF0 sub_53DEF0 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Locked sub_53DF28.
void sub_53DEF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053def0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53DEFCu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    jal(ctx, 0x53DF04u, gen::fn_sub_53DF28_0053df28);
    s0 = v0;
    jal(ctx, 0x53DF0Cu, gen::fn_sub_53E0A0_0053e0a0);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053DF28 sub_53DF28 -- 24 bytes; leaf frame (no stack)
// The partition record's file name (+16).
void sub_53DF28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0053df28
    enter(ctx, 6);  // entry check point + this block's cycles
    a0 = sll(a0, 2);
    v0 = 0x780000;
    v0 = addu(v0, a0);
    lw(v0, v0, 20128);
    v0 = addiu(v0, 16);
}

// 0x0053DF90 adxf_SetReqRdSct -- 52 bytes; frame 0x10: ra sp+0x0
// Sets the per-request sector limit (+44); refused while reading ('E0041201').
void adxf_SetReqRdSct(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053df90
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 2;
    sd(ra, sp, 0x0);
    lb(v0, a0, adxf::kStat);
    ld(ra, sp, 0x0);
    if (v0 != v1) {
        // 0x0053dfb8
        charge(ctx, 3);
        sw(a1, a0, adxf::kMaxReqSct);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0053dfa8
    charge(ctx, 4);
    a0 = 0x7C0000;
    a0 = addiu(a0, 8576);  // "E0041201:state is reading(ADXF_SetReqRdSct)"
    sp = addiu(sp, 0x10);
    gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
}

// 0x0053E000 sub_53E000 -- 52 bytes; frame 0x10: ra sp+0x0
// The stream's status (sub_547558) of a handle, 0 without one.
void sub_53E000(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053e000
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0;
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0053e028 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0053e010
    charge(ctx, 3);
    lw(v1, a0, adxf::kStm);
    a0 = v1;
    if (v1 == 0) {
        // 0x0053e028 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0053e01c
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_547558_00547558(ctx);  // tail call
}

// 0x0053E070 sub_53E070 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk to sub_5470E8.
void sub_53E070(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053e070
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5470E8_005470e8(ctx);  // tail call
}

// 0x0053E088 sub_53E088 -- 20 bytes; frame 0x10: ra sp+0x0
// ADXF lock (sub_539848).
void sub_53E088(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053e088
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539848_00539848(ctx);  // tail call
}

// 0x0053E0A0 sub_53E0A0 -- 20 bytes; frame 0x10: ra sp+0x0
// ADXF unlock (sub_539850).
void sub_53E0A0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053e0a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0053E0B8 ADXT_UpdateFsStat -- 36 bytes; frame 0x10: ra sp+0x0
// ADXT_UpdateFsStat: the file server step (adxt_ExecFsSvr) under the lock.
void ADXT_UpdateFsStat(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053e0b8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x53E0C0u, gen::fn_sub_539848_00539848);
    jal(ctx, 0x53E0C8u, gen::fn_adxt_ExecFsSvr_0053e0e0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0053E1B8 sub_53E1B8 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk to ADXT_UpdateFsStat.
void sub_53E1B8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053e1b8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_ADXT_UpdateFsStat_0053e0b8(ctx);  // tail call
}

// 0x0053E208 sub_53E208 -- 20 bytes; leaf frame (no stack)
// 1 when the word at 0x787538 is set.
void sub_53E208(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x0053e208
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = 0x780000;
    v1 = addiu(v1, 30008);  // &0x787538
    lw(v0, v1, 0);  // 0x787538
    v0 = sltu(0, v0);
}

// =====================================================================================================================
// ADX header encode / decode (big-endian fields, the 0x8000 magic, the "(c)CRI" signature)
// =====================================================================================================================

// 0x0053E220 sub_53E220 -- 24 bytes; leaf frame (no stack)
// Stores a 16-bit value big-endian.
void sub_53E220(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0053e220
    enter(ctx, 6);  // entry check point + this block's cycles
    a1 = sll(a1, 16);
    a1 = sra(a1, 16);
    v0 = srl(a1, 8);
    sb(a1, a0, 1);
    sb(v0, a0, 0);
}

// 0x0053E250 sub_53E250 -- 32 bytes; leaf frame (no stack)
// Stores a 32-bit value big-endian.
void sub_53E250(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0053e250
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = srl(a1, 24);
    v1 = srl(a1, 16);
    a2 = srl(a1, 8);
    sb(a1, a0, 3);
    sb(v0, a0, 0);
    sb(v1, a0, 1);
    sb(a2, a0, 2);
}

// 0x0053E290 sub_53E290 -- 188 bytes; leaf frame (no stack)
// ADX header body decode: the format bytes, then the big-endian rate and frame count into the info record.
void sub_53E290(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0053e290
    enter(ctx, 47);  // entry check point + this block's cycles
    lbu(v0, a0, 0);
    a0 = addiu(a0, 1);
    sb(v0, a1, 0);
    lbu(v1, a0, 0);
    a0 = addiu(a0, 1);
    sb(v1, a1, 1);
    lbu(v0, a0, 0);
    a0 = addiu(a0, 1);
    sb(v0, a1, 2);
    lbu(v1, a0, 0);
    a0 = addiu(a0, 1);
    sb(v1, a1, 3);
    lbu(v0, a0, 0);
    lbu(v1, a0, 2);
    lbu(a2, a0, 1);
    v0 = sll(v0, 24);
    lbu(a3, a0, 3);
    a0 = addiu(a0, 4);
    a2 = sll(a2, 16);
    v1 = sll(v1, 8);
    v1 = v1 | a2;
    v0 = v0 | a3;
    v0 = v0 | v1;
    sw(v0, a1, 4);
    lbu(v1, a0, 0);
    lbu(v0, a0, 2);
    lbu(a2, a0, 1);
    v1 = sll(v1, 24);
    lbu(a3, a0, 3);
    a0 = addiu(a0, 4);
    v0 = sll(v0, 8);
    a2 = sll(a2, 16);
    v0 = v0 | a2;
    v1 = v1 | a3;
    v1 = v1 | v0;
    sw(v1, a1, 8);
    lbu(v0, a0, 0);
    lbu(v1, a0, 1);
    a0 = addiu(a0, 2);
    v0 = sll(v0, 8);
    v1 = v1 | v0;
    sh(v1, a1, 12);
    lbu(v0, a0, 0);
    sb(v0, a1, 60);
    lbu(v1, a0, 1);
    sb(v1, a1, 61);
}

// 0x0053E350 sub_53E350 -- 28 bytes; leaf frame (no stack)
// The big-endian u16 at +2 into the info's +14.
void sub_53E350(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0053e350
    enter(ctx, 7);  // entry check point + this block's cycles
    a0 = addiu(a0, 2);
    lbu(v0, a0, 0);
    lbu(v1, a0, 1);
    v0 = sll(v0, 8);
    v1 = v1 | v0;
    sh(v1, a1, 14);
}

// 0x0053E370 sub_53E370 -- 240 bytes; leaf frame (no stack)
// ADX header loop section decode (version 3).
void sub_53E370(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0053e370
    enter(ctx, 60);  // entry check point + this block's cycles
    lbu(v0, a0, 0);
    lbu(v1, a0, 1);
    a0 = addiu(a0, 2);
    v0 = sll(v0, 8);
    v1 = v1 | v0;
    sh(v1, a1, 0);
    lbu(v0, a0, 0);
    lbu(v1, a0, 1);
    a0 = addiu(a0, 2);
    v0 = sll(v0, 8);
    v1 = v1 | v0;
    sh(v1, a1, 2);
    lbu(v0, a0, 0);
    lbu(v1, a0, 2);
    lbu(a2, a0, 1);
    v0 = sll(v0, 24);
    lbu(a3, a0, 3);
    a0 = addiu(a0, 4);
    a2 = sll(a2, 16);
    v1 = sll(v1, 8);
    v1 = v1 | a2;
    v0 = v0 | a3;
    v0 = v0 | v1;
    sw(v0, a1, 4);
    lbu(v1, a0, 0);
    lbu(v0, a0, 2);
    lbu(a2, a0, 1);
    v1 = sll(v1, 24);
    lbu(a3, a0, 3);
    a0 = addiu(a0, 4);
    a2 = sll(a2, 16);
    v0 = sll(v0, 8);
    v0 = v0 | a2;
    v1 = v1 | a3;
    v1 = v1 | v0;
    sw(v1, a1, 8);
    lbu(v0, a0, 0);
    lbu(v1, a0, 2);
    lbu(a2, a0, 1);
    v0 = sll(v0, 24);
    lbu(a3, a0, 3);
    a0 = addiu(a0, 4);
    a2 = sll(a2, 16);
    v1 = sll(v1, 8);
    v1 = v1 | a2;
    v0 = v0 | a3;
    v0 = v0 | v1;
    sw(v0, a1, 12);
    lbu(a2, a0, 1);
    lbu(v0, a0, 0);
    lbu(v1, a0, 2);
    a2 = sll(a2, 16);
    lbu(a3, a0, 3);
    v0 = sll(v0, 24);
    v1 = sll(v1, 8);
    v0 = v0 | a3;
    v1 = v1 | a2;
    v0 = v0 | v1;
    sw(v0, a1, 16);
}

// 0x0053E460 sub_53E460 -- 192 bytes; leaf frame (no stack)
// ADX header loop section decode (version 4 layout).
void sub_53E460(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0053e460
    enter(ctx, 9);  // entry check point + this block's cycles
    a2 = a0;
    lbu(v0, a2, 0);
    lbu(v1, a2, 1);
    a2 = addiu(a2, 2);
    v0 = sll(v0, 8);
    v1 = v1 | v0;
    a0 = sll(v1, 16);
    sh(v1, a1, 0);
    if (i64(a0) > 0) {
        // 0x0053e484
        charge(ctx, 5);
        lbu(v0, a2, 0);
        lbu(v1, a2, 1);
        v0 = sll(v0, 8);
        v1 = v1 | v0;
        sh(v1, a1, 2);
    }
    // 0x0053e498
    charge(ctx, 6);
    a2 = addiu(a2, 2);
    lbu(v0, a2, 0);
    a2 = addiu(a2, 1);
    v1 = sll(v0, 24);
    sb(v0, a1, 4);
    if (i64(v1) > 0) {
        // 0x0053e4b0
        charge(ctx, 2);
        lbu(v0, a2, 0);
        sb(v0, a1, 5);
    }
    // 0x0053e4b8
    charge(ctx, 6);
    a2 = addiu(a2, 1);
    lbu(v0, a2, 0);
    a2 = addiu(a2, 1);
    v1 = sll(v0, 24);
    sb(v0, a1, 6);
    if (i64(v1) > 0) {
        // 0x0053e4d0
        charge(ctx, 2);
        lbu(v0, a2, 0);
        sb(v0, a1, 7);
    }
    // 0x0053e4d8
    charge(ctx, 6);
    a2 = addiu(a2, 1);
    lbu(v0, a2, 0);
    a2 = addiu(a2, 1);
    v1 = sll(v0, 24);
    sb(v0, a1, 8);
    if (i64(v1) > 0) {
        // 0x0053e4f0
        charge(ctx, 2);
        lbu(v0, a2, 0);
        sb(v0, a1, 9);
    }
    // 0x0053e4f8
    charge(ctx, 6);
    a2 = addiu(a2, 1);
    lbu(v0, a2, 0);
    a2 = addiu(a2, 1);
    v1 = sll(v0, 24);
    sb(v0, a1, 10);
    if (i64(v1) > 0) {
        // 0x0053e510
        charge(ctx, 2);
        lbu(v0, a2, 0);
        sb(v0, a1, 11);
    }
    // 0x0053e518 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0053E520 sub_53E520 -- 436 bytes; frame 0x30: s1 sp+0x8, s3 sp+0x18, s0 sp+0x0, s2 sp+0x10, s4 sp+0x20, ra sp+0x28
// ADX header decode: 0x8000 magic, the header size into *size, then the body and loop sections by version; -1 short,
// -4 bad magic, -2 truncated.
void sub_53E520(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0053e520
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    if (a2 != 0) {
        // 0x0053e54c
        charge(ctx, 1);
        sw(zero, a2, 0);
    }
    // 0x0053e550
    charge(ctx, 3);
    v1 = slti(t0, 4);
    v0 = si(-1);
    if (v1 == 0) {
        // 0x0053e55c
        charge(ctx, 8);
        lbu(v1, s1, 0);
        a1 = 0x8000;
        lbu(a0, s1, 1);
        s1 = addiu(s1, 2);
        v1 = sll(v1, 8);
        a0 = a0 | v1;
        v0 = si(-4);
        if (a0 != a1) {
            goto L_0053e6b4;
        }
        // 0x0053e57c
        charge(ctx, 6);
        lbu(v0, s1, 0);
        lbu(v1, s1, 1);
        s1 = addiu(s1, 2);
        v0 = sll(v0, 8);
        s2 = v0 | v1;
        if (a2 != 0) {
            // 0x0053e594
            charge(ctx, 1);
            sw(s2, a2, 0);
        }
        // 0x0053e598
        charge(ctx, 2);
        v0 = 0;
        if (s3 == 0) {
            goto L_0053e6b4;
        }
        // 0x0053e5a0
        charge(ctx, 4);
        v1 = addiu(s2, 4);
        v1 = slt(t0, v1);
        v0 = si(-2);
        if (v1 != 0) {
            goto L_0053e6b4;
        }
        // 0x0053e5b0
        charge(ctx, 4);
        s2 = addiu(s2, -6);
        v1 = slti(s2, 16);
        ld(s0, sp, 0x0);
        if (v1 == 0) {
            // 0x0053e5c0
            charge(ctx, 9);
            a0 = s1;
            s1 = addiu(s1, 16);
            a1 = s3;
            s2 = addiu(s2, -16);
            jal(ctx, 0x53E5CCu, gen::fn_sub_53E290_0053e290);
            lb(v1, s3, 60);
            v0 = 4;
            cc = v1 != v0;  // the condition, before the delay slot changes it
            v1 = slti(s2, 4);
            if (!cc) {
                // 0x0053e5e4
                charge(ctx, 3);
                s1 = addiu(s1, 12);
                s2 = addiu(s2, -12);
                v1 = slti(s2, 4);
            }
            // 0x0053e5f0
            charge(ctx, 2);
            v0 = 0;
            if (v1 == 0) {
                // 0x0053e5f8
                charge(ctx, 11);
                a0 = s1;
                s1 = addiu(s1, 4);
                a1 = s3;
                jal(ctx, 0x53E600u, gen::fn_sub_53E350_0053e350);
                lh(v1, s3, 14);
                v0 = sll(v1, 2);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                v0 = slt(s2, v0);
                lhu(a0, s3, 14);
                if (v0 == 0) {
                    // 0x0053e624
                    charge(ctx, 2);
                    s4 = 0;
                    if (i64(v1) > 0) {
                        // 0x0053e62c
                        charge(ctx, 1);
                        s0 = addiu(s3, 16);
                        for (;;) {
                            // 0x0053e630
                            charge(ctx, 9);
                            a1 = s0;
                            s0 = addiu(s0, 20);
                            a0 = s1;
                            s4 = addiu(s4, 1);
                            jal(ctx, 0x53E63Cu, gen::fn_sub_53E370_0053e370);
                            lh(v0, s3, 14);
                            v0 = slt(s4, v0);
                            lhu(a0, s3, 14);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                    // 0x0053e654
                    charge(ctx, 9);
                    v0 = sll(a0, 16);
                    lb(a0, s3, 3);
                    v0 = sra(v0, 16);
                    s4 = 0;
                    v1 = sll(v0, 2);
                    v1 = addu(v1, v0);
                    v1 = sll(v1, 2);
                    s2 = subu(s2, v1);
                    if (i64(a0) > 0) {
                        // 0x0053e678
                        charge(ctx, 2);
                        s0 = addiu(s3, 36);
                        v0 = slti(s2, 12);
                        for (;;) {
                            // 0x0053e680
                            charge(ctx, 2);
                            s2 = addiu(s2, -12);
                            if (v0 == 0) {
                                // 0x0053e688
                                charge(ctx, 10);
                                a0 = s1;
                                s1 = addiu(s1, 12);
                                a1 = s0;
                                s0 = addiu(s0, 12);
                                jal(ctx, 0x53E694u, gen::fn_sub_53E460_0053e460);
                                lb(v0, s3, 3);
                                s4 = addiu(s4, 1);
                                v0 = slt(s4, v0);
                                cc = v0 != 0;  // the condition, before the delay slot changes it
                                v0 = slti(s2, 12);
                                if (cc) {
                                    backedge(ctx);
                                    continue;
                                }
                            }
                            break;
                        }
                    }
                }
                // 0x0053e6b0
                charge(ctx, 1);
                v0 = 0;
            }
            goto L_0053e6b4;
        }
        // 0x0053e6b8 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
L_0053e6b4:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0053e6b8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0053E6D8 sub_53E6D8 -- 244 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// ADX header encode: the format bytes, big-endian rate / frames / sizes and the "(c)CRI" signature.
void sub_53E6D8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053e6d8
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7C0000;
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = addiu(v0, 8624);  // "(c)CRI"
    sd(ra, sp, 0x18);
    lbu(v1, s0, 0);
    sb(v1, s1, 0);
    s1 = addiu(s1, 1);
    lbu(v0, s0, 1);
    sb(v0, s1, 0);
    s1 = addiu(s1, 1);
    lbu(v0, s0, 2);
    sb(v0, s1, 0);
    s1 = addiu(s1, 1);
    lbu(v0, s0, 3);
    sb(v0, s1, 0);
    s1 = addiu(s1, 1);
    a0 = s1;
    s1 = addiu(s1, 4);
    link(ctx, 0x53E734u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, 4);
    call(ctx, gen::fn_sub_53E250_0053e250);
    a0 = s1;
    lw(a1, s0, 8);
    s1 = addiu(s1, 4);
    jal(ctx, 0x53E744u, gen::fn_sub_53E250_0053e250);
    a0 = s1;
    lh(a1, s0, 12);
    s1 = addiu(s1, 2);
    jal(ctx, 0x53E754u, gen::fn_sub_53E220_0053e220);
    lbu(v0, s0, 60);
    v1 = 9;
    sb(v0, s1, 0);
    s1 = addiu(s1, 1);
    lbu(v0, s0, 61);
    sb(v0, s1, 0);
    s1 = addiu(s1, 1);
    for (;;) {
        // 0x0053e778
        charge(ctx, 7);
        v1 = addiu(v1, -1);
        sb(zero, s1, 0);
        s1 = addiu(s1, 1);
        if (i64(v1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0053e794
    charge(ctx, 1);
    v1 = 6;
    for (;;) {
        // 0x0053e798
        charge(ctx, 7);
        lbu(v0, s2, 0);
        s2 = addiu(s2, 1);
        v1 = addiu(v1, -1);
        sb(v0, s1, 0);
        s1 = addiu(s1, 1);
        if (i64(v1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0053e7b4
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0053E9D8 sub_53E9D8 -- 24 bytes; frame 0x10: ra sp+0x0
// Error forwarder (data ref): reports its second argument (sub_53AE08).
void sub_53E9D8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053e9d8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = a1;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
}

// 0x0053E9F0 sub_53E9F0 -- 24 bytes; frame 0x10: ra sp+0x0
// Error forwarder (data ref): reports its second argument (sub_53AE08).
void sub_53E9F0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053e9f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = a1;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
}

// =====================================================================================================================
// ADXT / ADXM: the player's file entry, the sync modes, the server threads
// =====================================================================================================================

// 0x0053F080 sub_53F080 -- 200 bytes; frame 0x40: s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, ra sp+0x38
// ADXT: enters a partition file into the play list (sub_53DD10, sub_55D428); 'E02080855' null handle, 'E0071301' when
// the entry fails.
// [proposed name] adxt_EntryAfs: the function's own error text names it.
void sub_53F080(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f080
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = a0;
    sd(s0, sp, 0x20);
    s0 = a1;
    sd(s1, sp, 0x28);
    s1 = a2;
    sd(s2, sp, 0x30);
    a0 = s0;
    sd(ra, sp, 0x38);
    a1 = s1;
    lw(s2, v0, 148);
    if (v0 != 0) {
        // 0x0053f0c8
        charge(ctx, 10);
        lw(a2, v0, 176);
        a3 = addiu(sp, 0x10);
        t0 = addiu(sp, 0x14);
        t1 = addiu(sp, 0x18);
        jal(ctx, 0x53F0D4u, gen::fn_sub_53DD10_0053dd10);
        a0 = s0;
        a1 = s1;
        a2 = sp;
        a3 = 16;
        if (v0 != 0) {
            // 0x0053f118
            charge(ctx, 7);
            jal(ctx, 0x53F118u, gen::fn_sub_53AFD8_0053afd8);
            a0 = 0x7C0000;
            a0 = addiu(a0, 9072);  // "E0071301 adxt_EntryAfs: can't entry "
            a1 = sp;
            jal(ctx, 0x53F128u, gen::fn_sub_53AE60_0053ae60);
            ld(s0, sp, 0x20);
        } else {
            // 0x0053f0f0
            charge(ctx, 10);
            jal(ctx, 0x53F0F0u, gen::fn_sub_53DEF0_0053def0);
            a0 = s2;
            lw(a2, sp, 0x10);
            a1 = v0;
            lw(a3, sp, 0x14);
            link(ctx, 0x53F108u);  // $ra first: the delay slot below depends on it
            lw(t0, sp, 0x18);
            call(ctx, gen::fn_sub_55D428_0055d428);
            ld(s0, sp, 0x20);
        }
    } else {
        // 0x0053f0b0
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 9024);  // "E02080855 adxt_EntryAfs: parameter error"
        jal(ctx, 0x53F0B4u, gen::fn_sub_53AE08_0053ae08);
        ld(s0, sp, 0x20);
    }
    // 0x0053f134 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0053F178 sub_53F178 -- 172 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXT: restarts the stream: stops it, resets the joints and the input buffer (sub_55DA48), restarts the decoder;
// 'E02080850' for a null handle.
// [proposed name] adxt_StartSeamless: the function's own error text names it.
void sub_53F178(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f178
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    lw(s1, s0, 148);
    if (s0 == 0) {
        // 0x0053f194
        charge(ctx, 7);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 9112);  // "E02080850 adxt_StartSeamless: parameter error"
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
        return;
    }
    // 0x0053f1b0
    charge(ctx, 29);
    jal(ctx, 0x53F1B0u, gen::fn_sub_5485A8_005485a8);
    jal(ctx, 0x53F1B8u, gen::fn_sub_539818_00539818);
    lw(a1, s0, 16);
    a0 = s0;
    jal(ctx, 0x53F1C4u, gen::fn_sub_548318_00548318);
    lw(a0, s0, 20);
    lw(v1, a0, 0);
    lw(v0, v1, 20);
    jalr(ctx, 0x53F1D8u, v0.u());
    v1 = 4;
    lh(a1, s0, 62);
    a0 = s1;
    sb(v1, s0, 2);
    a1 = sll(a1, 11);
    jal(ctx, 0x53F1F0u, gen::fn_sub_55DA48_0055da48);
    jal(ctx, 0x53F1F8u, gen::fn_sub_539830_00539830);
    a0 = s1;
    jal(ctx, 0x53F200u, gen::fn_sub_55D600_0055d600);
    a0 = s0;
    ld(s1, sp, 0x8);
    a1 = 1;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sceInsockSetsockopt_2_0054a928(ctx);  // tail call
}

// 0x0053F5F0 sub_53F5F0 -- 36 bytes; frame 0x10: ra sp+0x0
// Locked sub_53F618.
void sub_53F5F0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f5f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x53F5F8u, gen::fn_sub_539848_00539848);
    jal(ctx, 0x53F600u, gen::fn_sub_53F618_0053f618);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0053F618 sub_53F618 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk to sub_55D730.
void sub_53F618(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f618
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55D730_0055d730(ctx);  // tail call
}

// 0x0053F630 sub_53F630 -- 12 bytes; leaf frame (no stack)
// Sets the ADXM sync mode (0x788630).
void sub_53F630(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0053f630
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x790000;
    sw(a0, v0, -31184);  // 0x788630
}

// 0x0053F640 sub_53F640 -- 144 bytes; frame 0x10: ra sp+0x0
// ADXM main-loop step by the sync mode: 1 wakes the server thread, 2 runs the main server, 3 all of them.
void sub_53F640(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0053f640
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(a0, v0, -31184);  // 0x788630
    sd(ra, sp, 0x0);
    jal(ctx, 0x53F650u, gen::fn_sub_53F880_0053f880);
    v1 = v0;
    v0 = 1;
    a0 = slti(v1, 2);
    if (v1 == v0) {
        // 0x0053f690
        charge(ctx, 4);
        jal(ctx, 0x53F690u, gen::fn_sub_53F768_0053f768);
        ld(ra, sp, 0x0);
    L_0053f6c4:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0053f668
        charge(ctx, 2);
        ld(ra, sp, 0x0);
        if (a0 != 0) {
            goto L_0053f6c4;
        }
        // 0x0053f670
        charge(ctx, 3);
        v0 = 2;
        cc = v1 == v0;  // the condition, before the delay slot changes it
        v0 = 3;
        if (cc) {
            // 0x0053f6a0
            charge(ctx, 4);
            jal(ctx, 0x53F6A0u, gen::fn_sub_565438_00565438);
            ld(ra, sp, 0x0);
            goto L_0053f6c4;
        }
        // 0x0053f67c
        charge(ctx, 2);
        cc = v1 == v0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (cc) {
            // 0x0053f6b0
            charge(ctx, 5);
            jal(ctx, 0x53F6B0u, gen::fn_sub_565450_00565450);
            jal(ctx, 0x53F6B8u, gen::fn_sub_565468_00565468);
            ld(ra, sp, 0x0);
            goto L_0053f6c4;
        }
        // 0x0053f684
        charge(ctx, 2);
    }
    // 0x0053f6c8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x0053F6D0 sub_53F6D0 -- 152 bytes; frame 0x10: ra sp+0x0
// ADXPS2 v-interrupt step by the sync mode: 2 runs the v-sync server, 3 every server.
void sub_53F6D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0053f6d0
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(a0, v0, -31184);  // 0x788630
    sd(ra, sp, 0x0);
    jal(ctx, 0x53F6E0u, gen::fn_sub_53F880_0053f880);
    v1 = v0;
    v0 = 1;
    a0 = slti(v1, 2);
    if (v1 != v0) {
        // 0x0053f6f8
        charge(ctx, 2);
        ld(ra, sp, 0x0);
        if (a0 != 0) {
        L_0053f75c:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0053f700
            charge(ctx, 3);
            v0 = 2;
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = 3;
            if (cc) {
                // 0x0053f720
                charge(ctx, 4);
                jal(ctx, 0x53F720u, gen::fn_sub_5653C0_005653c0);
                ld(ra, sp, 0x0);
                goto L_0053f75c;
            }
            // 0x0053f70c
            charge(ctx, 2);
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (cc) {
                // 0x0053f730
                charge(ctx, 10);
                jal(ctx, 0x53F730u, gen::fn_sub_5653C0_005653c0);
                jal(ctx, 0x53F738u, gen::fn_sub_5653D8_005653d8);
                jal(ctx, 0x53F740u, gen::fn_sub_5653F0_005653f0);
                jal(ctx, 0x53F748u, gen::fn_sub_565408_00565408);
                jal(ctx, 0x53F750u, gen::fn_sub_565438_00565438);
                goto L_0053f758;
            }
            // 0x0053f714
            charge(ctx, 2);
        }
        // 0x0053f760 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_0053f758:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    goto L_0053f75c;
}

// 0x0053F880 sub_53F880 -- 56 bytes; frame 0x10: ra sp+0x0
// Resolves the sync mode -1: 2 when sub_540560 says 1, else 1.
void sub_53F880(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f880
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = si(-1);
    sd(ra, sp, 0x0);
    if (a0 == v0) {
        // 0x0053f890
        charge(ctx, 6);
        jal(ctx, 0x53F890u, gen::fn_sub_540560_00540560);
        v1 = 1;
        v0 = v0 ^ v1;
        a0 = 2;
        if (v0 != 0) a0 = v1;
    }
    // 0x0053f8a8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    v0 = a0;
    sp = addiu(sp, 0x10);
}

// 0x0053F9B0 adxm_goto_svr_border -- 228 bytes; frame 0x40: s1 sp+0x8, s5 sp+0x28, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x30
// Hands the server work to the ADXM thread: raises it, waits (at most 200,000,000 polls) for the border flag 0x788684
// to clear; 'Internal Error' on time-out.
void adxm_goto_svr_border(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f9b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s5, sp, 0x28);
    s5 = a1;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x30);
    if (s1 == 0) {
        // 0x0053fa70
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
    // 0x0053f9dc
    charge(ctx, 13);
    v0 = 0x790000;
    s0 = 0x790000;
    lw(a1, v0, -31152);  // 0x788650
    v0 = 1;
    s0 = addiu(s0, -31100);  // &0x788684
    s2 = 0xBEB0000;
    sw(v0, s0, 0);  // 0x788684
    s3 = s0;
    s2 = s2 | 0xC1FF;
    s4 = 0x7C0000;
    jal(ctx, 0x53FA00u, gen::fn__sceChangeThreadPriority_00502ff0);
    s0 = 0;
    for (;;) {
        // 0x0053fa10
        charge(ctx, 8);
        a0 = s1;
        jal(ctx, 0x53FA10u, gen::fn_sub_540048_00540048);
        a0 = s1;
        jal(ctx, 0x53FA18u, gen::fn_sub_5400B0_005400b0);
        v1 = slt(s2, s0);
        lw(v0, s3, 0);
        s0 = addiu(s0, 1);
        if (v0 == 0) {
            break;
        }
        // 0x0053fa30
        charge(ctx, 2);
        if (v1 != 0) {
            goto L_0053fa38_4;
        }
        backedge(ctx);
    }
L_0053fa40:
    charge(ctx, 11);
    a0 = s1;
    ld(s1, sp, 0x8);
    a1 = s5;
    ld(s5, sp, 0x28);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
    gen::fn__sceChangeThreadPriority_00502ff0(ctx);  // tail call
    return;
L_0053fa38_4:
    charge(ctx, 2);
    a0 = addiu(s4, 9456);
    jal(ctx, 0x53FA38u, gen::fn_sub_564B50_00564b50);
    goto L_0053fa40;
}

// 0x0053FA98 sub_53FA98 -- 40 bytes; frame 0x10: ra sp+0x0
// sub_53F9B0 with the server thread and its priority (0x7886EC, 0x788668).
void sub_53FA98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053fa98
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(ra, sp, 0x0);
    v1 = 0x790000;
    v0 = addiu(v0, -30996);  // &0x7886EC
    lw(a1, v1, -31128);  // 0x788668
    lw(a0, v0, 0);  // 0x7886EC
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_adxm_goto_svr_border_0053f9b0(ctx);  // tail call
}

// 0x0053FBF0 adxm_vsync_proc -- 260 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, ra sp+0x38
// The ADXM v-sync thread: until told to stop, counts, sleeps, runs the v-sync server; then marks itself ended and
// exits.
void adxm_vsync_proc(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0053fbf0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    a3 = addiu(v0, -30952);  // &0x788718
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(s6, sp, 0x30);
    sd(ra, sp, 0x38);
    ld(v1, a3, 0);  // 0x788718
    v0 = 0x790000;
    if (v1 == 0) {
        // 0x0053fc28
        charge(ctx, 12);
        v0 = 0x790000;
        v1 = 0x790000;
        a0 = 0x790000;
        a1 = 0x790000;
        a2 = 0x790000;
        s3 = addiu(v0, -31056);  // &0x7886B0
        s6 = addiu(v1, -30996);  // &0x7886EC
        s2 = addiu(a0, -30872);  // &0x788768
        s5 = addiu(a1, -30992);  // &0x7886F0
        s1 = addiu(a2, -31096);  // &0x788688
        s4 = a3;
        for (;;) {
            // 0x0053fc58
            charge(ctx, 8);
            ld(v0, s3, 0);
            v0 = daddiu(v0, 1);
            sd(v0, s3, 0);
            link(ctx, 0x53FC64u);  // $ra first: the delay slot below depends on it
            lw(a0, s6, 0);
            call(ctx, gen::fn_sub_540118_00540118);
            lw(v1, s2, 0);
            if (v1 == 0) {
                // 0x0053fc78
                charge(ctx, 2);
                jal(ctx, 0x53FC78u, gen::fn_sub_541510_00541510);
            }
            // 0x0053fc80
            charge(ctx, 5);
            sw(zero, s2, 0);
            s0 = 1;
            jal(ctx, 0x53FC84u, gen::fn___errno_00540550);
            if (v0 == s0) {
                // 0x0053fc94
                charge(ctx, 2);
                link(ctx, 0x53FC94u);  // $ra first: the delay slot below depends on it
                lw(a0, s5, 0);
                call(ctx, gen::fn_sub_540118_00540118);
            }
            // 0x0053fc9c
            charge(ctx, 9);
            jal(ctx, 0x53FC9Cu, gen::fn_sub_540F60_00540f60);
            link(ctx, 0x53FCA4u);  // $ra first: the delay slot below depends on it
            sw(s0, s1, 0);
            call(ctx, gen::fn_sub_5653F0_005653f0);
            link(ctx, 0x53FCACu);  // $ra first: the delay slot below depends on it
            sw(zero, s1, 0);
            call(ctx, gen::fn_sub_540098_00540098);
            ld(v0, s4, 0);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 0x790000;
            if (!cc) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0053fcc0
    charge(ctx, 13);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v1 = 1;
    ld(s2, sp, 0x10);
    v0 = addiu(v0, -30944);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x38);
    sd(v1, v0, 0);
    sp = addiu(sp, 0x40);
    gen::fn__sceExitDeleteThread_00502fa0(ctx);  // tail call
}

// 0x0053FDE8 adxm_mwidle_proc -- 312 bytes; frame 0x50: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s7 sp+0x38, ra sp+0x40
// The ADXM idle thread: until told to stop, runs the idle server and hands control back; then exits.
void adxm_mwidle_proc(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0053fde8
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    a2 = addiu(v0, -30920);  // &0x788738
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(s6, sp, 0x30);
    sd(s7, sp, 0x38);
    sd(ra, sp, 0x40);
    ld(v1, a2, 0);  // 0x788738
    v0 = 0x790000;
    if (v1 == 0) {
        // 0x0053fe24
        charge(ctx, 11);
        v0 = 0x790000;
        v1 = 0x790000;
        a0 = 0x790000;
        a1 = 0x790000;
        s4 = addiu(v0, -31040);  // &0x7886C0
        s3 = addiu(v1, -31084);  // &0x788694
        s2 = addiu(a0, -31100);  // &0x788684
        s7 = addiu(a1, -30872);  // &0x788768
        s6 = a2;
        s1 = 1;
        s5 = 0x790000;
        for (;;) {
            // 0x0053fe50
            charge(ctx, 10);
            ld(v0, s4, 0);
            v0 = daddiu(v0, 1);
            sd(v0, s4, 0);
            link(ctx, 0x53FE5Cu);  // $ra first: the delay slot below depends on it
            sw(s1, s3, 0);
            call(ctx, gen::fn_sub_565450_00565450);
            sw(zero, s3, 0);
            s0 = v0;
            lw(v0, s2, 0);
            if (v0 == s1) {
                // 0x0053fe78
                charge(ctx, 2);
                link(ctx, 0x53FE78u);  // $ra first: the delay slot below depends on it
                sw(zero, s2, 0);
                call(ctx, gen::fn_sub_540098_00540098);
            }
            // 0x0053fe80
            charge(ctx, 2);
            if (s0 == 0) {
                // 0x0053fe88
                charge(ctx, 4);
                jal(ctx, 0x53FE88u, gen::fn___errno_00540550);
                s0 = addiu(s5, -30992);
                if (v0 == s1) {
                    // 0x0053fe98
                    charge(ctx, 6);
                    lw(a0, s0, 0);
                    jal(ctx, 0x53FE9Cu, gen::fn_sub_5400B0_005400b0);
                    lw(v1, s0, 0);
                    if (v0 == v1) {
                        // 0x0053feb0
                        charge(ctx, 2);
                        link(ctx, 0x53FEB0u);  // $ra first: the delay slot below depends on it
                        lw(a0, s0, 0);
                        call(ctx, gen::fn_sub_540048_00540048);
                    }
                }
                // 0x0053feb8
                charge(ctx, 4);
                lw(v0, s2, 0);
                s0 = 1;
                if (v0 != s0) {
                    // 0x0053fec8
                    charge(ctx, 3);
                    jal(ctx, 0x53FEC8u, gen::fn_sub_541510_00541510);
                    sw(s0, s7, 0);
                }
                // 0x0053fed4
                charge(ctx, 2);
                jal(ctx, 0x53FED4u, gen::fn_sub_540098_00540098);
            }
            // 0x0053fedc
            charge(ctx, 3);
            ld(v0, s6, 0);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 0x790000;
            if (!cc) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0053fee8
    charge(ctx, 14);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v1 = 1;
    ld(s2, sp, 0x10);
    v0 = addiu(v0, -30912);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(ra, sp, 0x40);
    sd(v1, v0, 0);
    sp = addiu(sp, 0x50);
    gen::fn__sceExitDeleteThread_00502fa0(ctx);  // tail call
}

// 0x0053FFF8 sub_53FFF8 -- 80 bytes; frame 0x40: s0 sp+0x30, ra sp+0x38
// Wakes a thread (iWakeupThread) when it is in WAIT (4) or WAITSUSPEND (12).
void sub_53FFF8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053fff8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x30);
    s0 = a0;
    sd(ra, sp, 0x38);
    if (s0 != 0) {
        // 0x0054000c
        charge(ctx, 7);
        a1 = sp;
        jal(ctx, 0x54000Cu, gen::fn__sceiReferThreadStatus_00503070);
        a0 = s0;
        lw(v1, sp, 0x0);
        v0 = 4;
        a1 = 12;
        if (v1 != v0) {
            // 0x00540028
            charge(ctx, 2);
            ld(s0, sp, 0x30);
            if (v1 == a1) {
                goto L_00540030;
            }
            // 0x0054003c (the shared epilogue, written out on this path)
            charge(ctx, 3);
            ld(ra, sp, 0x38);
            sp = addiu(sp, 0x40);
            return;
        }
    L_00540030:
        charge(ctx, 2);
        jal(ctx, 0x540030u, gen::fn_iWakeupThread_00504028);
    }
    // 0x00540038
    charge(ctx, 1);
    ld(s0, sp, 0x30);
    // 0x0054003c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

}  // namespace p3fes::game
