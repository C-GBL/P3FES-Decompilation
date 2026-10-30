// Phase 5 slice libs8: the CRI middleware library band 0x540048-0x54E568 (150 functions).
//   0x540048-0x5419F0  ADXM: the ADX thread manager (safe / vsync / fs / mwidle / user threads: create, suspend,
//                      resume, wake, shut down), the vblank handler, user callbacks, debug prints, thunks.
//   0x541AA8-0x541DA0  PS2RNA guards and small counters.
//   0x542F70-0x5433C0  ADXT forwarders to the ADX SJ decoder (handle at +4).
//   0x543430-0x544850  an ADX encoder: cipher keys, predictor / channel records, block coding, frame output.
//   0x545BF0-0x547668  ADXSTM: the ADX file streamer on CVFS (96-byte records at 0x792BD8) and ADXPS2_SetupDvdFs.
//   0x548278-0x54B8E0  ADXT handle pieces (E0208xxxx parameter checks).
//   0x54CFE8-0x54E568  AHX (MPEG audio) decoder pieces: bit reader, cipher keys, header.
// p3fes_handgen bodies (game/include/p3fes/game/hg_cpu.h): every statement, charge and check point is the
// generator's, equal to the recompiled body. Each function carries a role comment read from its instructions
// (status values are sceReferThreadStatus's: 4 WAIT, 8 SUSPEND, 12 WAITSUSPEND), and the address comments name the
// globals. Names are symbols/functions.json's (ADR-0009); proposals are in [brackets] and symbols/deltas/libs8.sym.
// Some map names are wrong for what the body does (__errno, expl_1, atan2l_2, cosl_2, coshl_2, the streambuf
// accessor): the role comment says so.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs8.h"

namespace p3fes::recomp_gen {
void fn_ADXM_SetupThrd_00540588(p3fes::EEContext&);
void fn_ADXPS2_ExecVint_00540d80(p3fes::EEContext&);
void fn_ADXPS2_SetupDvdFs_00547668(p3fes::EEContext&);
void fn_ADXSTMF_ExecHndl_00546bb0(p3fes::EEContext&);
void fn_ADXT_UpdateFsStat_0053e0b8(p3fes::EEContext&);
void fn_PS2RNA_Init_0055ff70(p3fes::EEContext&);
void fn_StartThread_005042a0(p3fes::EEContext&);
void fn__ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_2_005470e0(p3fes::EEContext&);
void fn___errno_00540550(p3fes::EEContext&);
void fn__sceChangeThreadPriority_00502ff0(p3fes::EEContext&);
void fn__sceCreateThread_00502f60(p3fes::EEContext&);
void fn__sceGetThreadId_00503050(p3fes::EEContext&);
void fn__sceReferThreadStatus_00503060(p3fes::EEContext&);
void fn__sceResumeThread_005030f0(p3fes::EEContext&);
void fn__sceSleepThread_00503080(p3fes::EEContext&);
void fn__sceSuspendThread_005030d0(p3fes::EEContext&);
void fn__sceWakeupThread_00503090(p3fes::EEContext&);
void fn_adxm_SetupFsThrd_00540360(p3fes::EEContext&);
void fn_adxm_SetupMwIdleThrd_005403e8(p3fes::EEContext&);
void fn_adxm_SetupSafeThrd_00540178(p3fes::EEContext&);
void fn_adxm_SetupUsrIdleThrd_00540480(p3fes::EEContext&);
void fn_adxm_SetupUsrVsyncThrd_00540220(p3fes::EEContext&);
void fn_adxm_SetupVsyncThrd_005402d8(p3fes::EEContext&);
void fn_adxstm_Create_00546010(p3fes::EEContext&);
void fn_adxstmf_ExecRead_00546788(p3fes::EEContext&);
void fn_adxstmf_ExecServer_00546e60(p3fes::EEContext&);
void fn_atan2l_2_00545c08(p3fes::EEContext&);
void fn_coshl_2_00545c38(p3fes::EEContext&);
void fn_cosl_2_00545c20(p3fes::EEContext&);
void fn_cvFsAddDev_00555b10(p3fes::EEContext&);
void fn_cvFsClose_00556398(p3fes::EEContext&);
void fn_cvFsExecServer_00556608(p3fes::EEContext&);
void fn_cvFsGetFileSize_005566d0(p3fes::EEContext&);
void fn_cvFsGetStat_00556668(p3fes::EEContext&);
void fn_cvFsOpen_00556048(p3fes::EEContext&);
void fn_cvFsReqRd_005564e0(p3fes::EEContext&);
void fn_cvFsSeek_00556478(p3fes::EEContext&);
void fn_cvFsTell_00556410(p3fes::EEContext&);
void fn_dpdiv_00531480(p3fes::EEContext&);
void fn_dpmul_00531230(p3fes::EEContext&);
void fn_dptoli_005317d0(p3fes::EEContext&);
void fn_dvCiSetRootDir_0055b610(p3fes::EEContext&);
void fn_expl_1_00541aa8(p3fes::EEContext&);
void fn_litodp_00531720(p3fes::EEContext&);
void fn_memcmp_005211b8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sceInsockGetErrnoMode_00537780(p3fes::EEContext&);
void fn_sceInsockSetsockopt_2_0054a928(p3fes::EEContext&);
void fn_scePrintf_00505e48(p3fes::EEContext&);
void fn_sub_534A88_00534a88(p3fes::EEContext&);
void fn_sub_535170_00535170(p3fes::EEContext&);
void fn_sub_537F70_00537f70(p3fes::EEContext&);
void fn_sub_538038_00538038(p3fes::EEContext&);
void fn_sub_538058_00538058(p3fes::EEContext&);
void fn_sub_5380A0_005380a0(p3fes::EEContext&);
void fn_sub_5380E0_005380e0(p3fes::EEContext&);
void fn_sub_538148_00538148(p3fes::EEContext&);
void fn_sub_539818_00539818(p3fes::EEContext&);
void fn_sub_539830_00539830(p3fes::EEContext&);
void fn_sub_539858_00539858(p3fes::EEContext&);
void fn_sub_53AE08_0053ae08(p3fes::EEContext&);
void fn_sub_53AE60_0053ae60(p3fes::EEContext&);
void fn_sub_53F6D0_0053f6d0(p3fes::EEContext&);
void fn_sub_53FFF8_0053fff8(p3fes::EEContext&);
void fn_sub_540048_00540048(p3fes::EEContext&);
void fn_sub_540098_00540098(p3fes::EEContext&);
void fn_sub_5400B0_005400b0(p3fes::EEContext&);
void fn_sub_540118_00540118(p3fes::EEContext&);
void fn_sub_540560_00540560(p3fes::EEContext&);
void fn_sub_540570_00540570(p3fes::EEContext&);
void fn_sub_540718_00540718(p3fes::EEContext&);
void fn_sub_540768_00540768(p3fes::EEContext&);
void fn_sub_540800_00540800(p3fes::EEContext&);
void fn_sub_5408D0_005408d0(p3fes::EEContext&);
void fn_sub_5409A0_005409a0(p3fes::EEContext&);
void fn_sub_540A70_00540a70(p3fes::EEContext&);
void fn_sub_540BA0_00540ba0(p3fes::EEContext&);
void fn_sub_540C70_00540c70(p3fes::EEContext&);
void fn_sub_540D40_00540d40(p3fes::EEContext&);
void fn_sub_540D58_00540d58(p3fes::EEContext&);
void fn_sub_540EA8_00540ea8(p3fes::EEContext&);
void fn_sub_540ED8_00540ed8(p3fes::EEContext&);
void fn_sub_540F60_00540f60(p3fes::EEContext&);
void fn_sub_540FE0_00540fe0(p3fes::EEContext&);
void fn_sub_5414E0_005414e0(p3fes::EEContext&);
void fn_sub_541510_00541510(p3fes::EEContext&);
void fn_sub_541610_00541610(p3fes::EEContext&);
void fn_sub_5416E8_005416e8(p3fes::EEContext&);
void fn_sub_541760_00541760(p3fes::EEContext&);
void fn_sub_5417E0_005417e0(p3fes::EEContext&);
void fn_sub_5419C0_005419c0(p3fes::EEContext&);
void fn_sub_5419D8_005419d8(p3fes::EEContext&);
void fn_sub_5419F0_005419f0(p3fes::EEContext&);
void fn_sub_541BB8_00541bb8(p3fes::EEContext&);
void fn_sub_541C60_00541c60(p3fes::EEContext&);
void fn_sub_541C88_00541c88(p3fes::EEContext&);
void fn_sub_541CA0_00541ca0(p3fes::EEContext&);
void fn_sub_541D00_00541d00(p3fes::EEContext&);
void fn_sub_541D18_00541d18(p3fes::EEContext&);
void fn_sub_541D30_00541d30(p3fes::EEContext&);
void fn_sub_541DA0_00541da0(p3fes::EEContext&);
void fn_sub_542F60_00542f60(p3fes::EEContext&);
void fn_sub_542F70_00542f70(p3fes::EEContext&);
void fn_sub_542FA8_00542fa8(p3fes::EEContext&);
void fn_sub_542FC0_00542fc0(p3fes::EEContext&);
void fn_sub_543020_00543020(p3fes::EEContext&);
void fn_sub_543038_00543038(p3fes::EEContext&);
void fn_sub_5430B8_005430b8(p3fes::EEContext&);
void fn_sub_543118_00543118(p3fes::EEContext&);
void fn_sub_5431F0_005431f0(p3fes::EEContext&);
void fn_sub_543328_00543328(p3fes::EEContext&);
void fn_sub_543380_00543380(p3fes::EEContext&);
void fn_sub_543388_00543388(p3fes::EEContext&);
void fn_sub_5433C0_005433c0(p3fes::EEContext&);
void fn_sub_543430_00543430(p3fes::EEContext&);
void fn_sub_543450_00543450(p3fes::EEContext&);
void fn_sub_543470_00543470(p3fes::EEContext&);
void fn_sub_5436D0_005436d0(p3fes::EEContext&);
void fn_sub_5438C0_005438c0(p3fes::EEContext&);
void fn_sub_543AA8_00543aa8(p3fes::EEContext&);
void fn_sub_543B40_00543b40(p3fes::EEContext&);
void fn_sub_543B50_00543b50(p3fes::EEContext&);
void fn_sub_543B60_00543b60(p3fes::EEContext&);
void fn_sub_543B78_00543b78(p3fes::EEContext&);
void fn_sub_543BF0_00543bf0(p3fes::EEContext&);
void fn_sub_543C90_00543c90(p3fes::EEContext&);
void fn_sub_543CC8_00543cc8(p3fes::EEContext&);
void fn_sub_543CD8_00543cd8(p3fes::EEContext&);
void fn_sub_543D30_00543d30(p3fes::EEContext&);
void fn_sub_543D40_00543d40(p3fes::EEContext&);
void fn_sub_543E28_00543e28(p3fes::EEContext&);
void fn_sub_543EC0_00543ec0(p3fes::EEContext&);
void fn_sub_543EF8_00543ef8(p3fes::EEContext&);
void fn_sub_543F08_00543f08(p3fes::EEContext&);
void fn_sub_544078_00544078(p3fes::EEContext&);
void fn_sub_5442D8_005442d8(p3fes::EEContext&);
void fn_sub_544560_00544560(p3fes::EEContext&);
void fn_sub_544720_00544720(p3fes::EEContext&);
void fn_sub_544850_00544850(p3fes::EEContext&);
void fn_sub_545BF0_00545bf0(p3fes::EEContext&);
void fn_sub_545C40_00545c40(p3fes::EEContext&);
void fn_sub_545C78_00545c78(p3fes::EEContext&);
void fn_sub_545D18_00545d18(p3fes::EEContext&);
void fn_sub_545E20_00545e20(p3fes::EEContext&);
void fn_sub_545EF8_00545ef8(p3fes::EEContext&);
void fn_sub_546088_00546088(p3fes::EEContext&);
void fn_sub_5460E0_005460e0(p3fes::EEContext&);
void fn_sub_546150_00546150(p3fes::EEContext&);
void fn_sub_5461C8_005461c8(p3fes::EEContext&);
void fn_sub_546238_00546238(p3fes::EEContext&);
void fn_sub_546270_00546270(p3fes::EEContext&);
void fn_sub_5462A0_005462a0(p3fes::EEContext&);
void fn_sub_5462E0_005462e0(p3fes::EEContext&);
void fn_sub_546310_00546310(p3fes::EEContext&);
void fn_sub_5463A0_005463a0(p3fes::EEContext&);
void fn_sub_5463A8_005463a8(p3fes::EEContext&);
void fn_sub_5463F0_005463f0(p3fes::EEContext&);
void fn_sub_546410_00546410(p3fes::EEContext&);
void fn_sub_546448_00546448(p3fes::EEContext&);
void fn_sub_546460_00546460(p3fes::EEContext&);
void fn_sub_5464D0_005464d0(p3fes::EEContext&);
void fn_sub_546510_00546510(p3fes::EEContext&);
void fn_sub_546558_00546558(p3fes::EEContext&);
void fn_sub_5465A0_005465a0(p3fes::EEContext&);
void fn_sub_5465D0_005465d0(p3fes::EEContext&);
void fn_sub_546638_00546638(p3fes::EEContext&);
void fn_sub_546668_00546668(p3fes::EEContext&);
void fn_sub_546708_00546708(p3fes::EEContext&);
void fn_sub_546718_00546718(p3fes::EEContext&);
void fn_sub_546758_00546758(p3fes::EEContext&);
void fn_sub_546770_00546770(p3fes::EEContext&);
void fn_sub_546D90_00546d90(p3fes::EEContext&);
void fn_sub_546DB8_00546db8(p3fes::EEContext&);
void fn_sub_546E38_00546e38(p3fes::EEContext&);
void fn_sub_546FF8_00546ff8(p3fes::EEContext&);
void fn_sub_547008_00547008(p3fes::EEContext&);
void fn_sub_547050_00547050(p3fes::EEContext&);
void fn_sub_547068_00547068(p3fes::EEContext&);
void fn_sub_5470A0_005470a0(p3fes::EEContext&);
void fn_sub_5470A8_005470a8(p3fes::EEContext&);
void fn_sub_547138_00547138(p3fes::EEContext&);
void fn_sub_547178_00547178(p3fes::EEContext&);
void fn_sub_547318_00547318(p3fes::EEContext&);
void fn_sub_547358_00547358(p3fes::EEContext&);
void fn_sub_547558_00547558(p3fes::EEContext&);
void fn_sub_547590_00547590(p3fes::EEContext&);
void fn_sub_548078_00548078(p3fes::EEContext&);
void fn_sub_548278_00548278(p3fes::EEContext&);
void fn_sub_548318_00548318(p3fes::EEContext&);
void fn_sub_548678_00548678(p3fes::EEContext&);
void fn_sub_549000_00549000(p3fes::EEContext&);
void fn_sub_549310_00549310(p3fes::EEContext&);
void fn_sub_549390_00549390(p3fes::EEContext&);
void fn_sub_549450_00549450(p3fes::EEContext&);
void fn_sub_54AC40_0054ac40(p3fes::EEContext&);
void fn_sub_54B3F0_0054b3f0(p3fes::EEContext&);
void fn_sub_54B8E0_0054b8e0(p3fes::EEContext&);
void fn_sub_54CFE8_0054cfe8(p3fes::EEContext&);
void fn_sub_54D528_0054d528(p3fes::EEContext&);
void fn_sub_54D6B8_0054d6b8(p3fes::EEContext&);
void fn_sub_54D7E8_0054d7e8(p3fes::EEContext&);
void fn_sub_54D898_0054d898(p3fes::EEContext&);
void fn_sub_54DAD8_0054dad8(p3fes::EEContext&);
void fn_sub_54DB38_0054db38(p3fes::EEContext&);
void fn_sub_54DBE8_0054dbe8(p3fes::EEContext&);
void fn_sub_54DBF0_0054dbf0(p3fes::EEContext&);
void fn_sub_54DD08_0054dd08(p3fes::EEContext&);
void fn_sub_54DE50_0054de50(p3fes::EEContext&);
void fn_sub_54DE90_0054de90(p3fes::EEContext&);
void fn_sub_54E2C0_0054e2c0(p3fes::EEContext&);
void fn_sub_54E568_0054e568(p3fes::EEContext&);
void fn_sub_54E9A0_0054e9a0(p3fes::EEContext&);
void fn_sub_54EAD8_0054ead8(p3fes::EEContext&);
void fn_sub_54EBC0_0054ebc0(p3fes::EEContext&);
void fn_sub_54ED48_0054ed48(p3fes::EEContext&);
void fn_sub_551AD8_00551ad8(p3fes::EEContext&);
void fn_sub_551BB0_00551bb0(p3fes::EEContext&);
void fn_sub_555E48_00555e48(p3fes::EEContext&);
void fn_sub_557198_00557198(p3fes::EEContext&);
void fn_sub_55B5F0_0055b5f0(p3fes::EEContext&);
void fn_sub_55F688_0055f688(p3fes::EEContext&);
void fn_sub_560698_00560698(p3fes::EEContext&);
void fn_sub_5615B0_005615b0(p3fes::EEContext&);
void fn_sub_561970_00561970(p3fes::EEContext&);
void fn_sub_563C28_00563c28(p3fes::EEContext&);
void fn_sub_564978_00564978(p3fes::EEContext&);
void fn_sub_564990_00564990(p3fes::EEContext&);
void fn_sub_565158_00565158(p3fes::EEContext&);
void fn_sub_5651F0_005651f0(p3fes::EEContext&);
void fn_sub_565230_00565230(p3fes::EEContext&);
void fn_sub_565248_00565248(p3fes::EEContext&);
void fn_sub_565550_00565550(p3fes::EEContext&);
void fn_sub_565590_00565590(p3fes::EEContext&);
void fn_sub_5655E8_005655e8(p3fes::EEContext&);
void fn_vsprintf_005288c8(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x00540048 sub_540048 -- 80 bytes; frame 0x40: s0 sp+0x30, ra sp+0x38
// [adxm_WakeupThrd] ADXM: wake thread a0 when sceReferThreadStatus says it waits (status 4 WAIT or 12 WAITSUSPEND); a0
// == 0 does nothing.
void sub_540048(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00540048
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x30);
    s0 = a0;
    sd(ra, sp, 0x38);
    if (s0 != 0) {
        // 0x0054005c
        charge(ctx, 7);
        a1 = sp;
        jal(ctx, 0x54005Cu, gen::fn__sceReferThreadStatus_00503060);
        a0 = s0;
        lw(v1, sp, 0x0);
        v0 = 4;
        a1 = 12;
        if (v1 != v0) {
            // 0x00540078
            charge(ctx, 2);
            ld(s0, sp, 0x30);
            if (v1 == a1) {
                goto L_00540080;
            }
            // 0x0054008c (the shared epilogue, written out on this path)
            charge(ctx, 3);
            ld(ra, sp, 0x38);
            sp = addiu(sp, 0x40);
            return;
        }
    L_00540080:
        charge(ctx, 2);
        jal(ctx, 0x540080u, gen::fn__sceWakeupThread_00503090);
    }
    // 0x00540088
    charge(ctx, 1);
    ld(s0, sp, 0x30);
    // 0x0054008c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x00540098 sub_540098 -- 20 bytes; frame 0x10: ra sp+0x0
// [adxm_SleepThrd] ADXM: tail call to sceSleepThread (the calling thread sleeps).
void sub_540098(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00540098
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn__sceSleepThread_00503080(ctx);  // tail call
}

// 0x005400B0 sub_5400B0 -- 100 bytes; frame 0x50: s0 sp+0x30, s1 sp+0x38, ra sp+0x40
// [adxm_ResumeThrd] ADXM: resume thread a0 when it is suspended (status 8 SUSPEND or 12 WAITSUSPEND); returns
// sceResumeThread's result, else 0.
void sub_5400B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005400b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x30);
    s0 = a0;
    sd(s1, sp, 0x38);
    s1 = 0;
    sd(ra, sp, 0x40);
    if (s0 != 0) {
        // 0x005400cc
        charge(ctx, 7);
        a1 = sp;
        jal(ctx, 0x5400CCu, gen::fn__sceReferThreadStatus_00503060);
        a0 = s0;
        lw(v1, sp, 0x0);
        v0 = 8;
        a1 = 12;
        if (v1 != v0) {
            // 0x005400e8
            charge(ctx, 2);
            v0 = s1;
            if (v1 == a1) {
                goto L_005400f0;
            }
            // 0x00540100 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(s0, sp, 0x30);
            ld(s1, sp, 0x38);
            ld(ra, sp, 0x40);
            sp = addiu(sp, 0x50);
            return;
        }
    L_005400f0:
        charge(ctx, 3);
        jal(ctx, 0x5400F0u, gen::fn__sceResumeThread_005030f0);
        s1 = v0;
    }
    // 0x005400fc
    charge(ctx, 1);
    v0 = s1;
    // 0x00540100 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00540118 sub_540118 -- 96 bytes; frame 0x50: s0 sp+0x30, s1 sp+0x38, ra sp+0x40
// [adxm_SuspendThrd] ADXM: suspend thread a0 unless it is already suspended (status 8 / 12); returns sceSuspendThread's
// result, else 0.
void sub_540118(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00540118
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x30);
    s0 = a0;
    sd(s1, sp, 0x38);
    s1 = 0;
    sd(ra, sp, 0x40);
    if (s0 != 0) {
        // 0x00540134
        charge(ctx, 6);
        a1 = sp;
        jal(ctx, 0x540134u, gen::fn__sceReferThreadStatus_00503060);
        lw(v1, sp, 0x0);
        v0 = 8;
        a0 = 12;
        if (v1 == v0) {
            goto L_00540160;
        }
        // 0x0054014c
        charge(ctx, 2);
        if (v1 != a0) {
            // 0x00540154
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x540154u, gen::fn__sceSuspendThread_005030d0);
            s1 = v0;
            goto L_00540160;
        }
        v0 = s1;
        // 0x00540164 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x30);
        ld(s1, sp, 0x38);
        ld(ra, sp, 0x40);
        sp = addiu(sp, 0x50);
        return;
    }
L_00540160:
    charge(ctx, 1);
    v0 = s1;
    // 0x00540164 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00540178 adxm_SetupSafeThrd -- 164 bytes; frame 0x40: s0 sp+0x30, ra sp+0x38
// ADXM: create the safe thread (adxm_safe_proc, stack 0x788770, 2 KiB, the main thread's priority), start it, suspend
// it and give it its priority (0x788654); the id goes to 0x7886D8.
void adxm_SetupSafeThrd(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00540178
    enter(ctx, 29);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x40);
    lw(a3, v0, -136);  // 0x78FF78 main thread prio
    v0 = 0x7D0000;
    a1 = 0x540000;
    v1 = 0x790000;
    a1 = addiu(a1, -1280);  // &adxm_safe_proc
    v1 = addiu(v1, -30864);  // &0x788770
    a0 = sp;
    a2 = 2048;
    v0 = addiu(v0, 11504);  // &gp_base
    sd(s0, sp, 0x30);
    sw(a1, sp, 0x4);
    sw(v1, sp, 0x8);
    sd(ra, sp, 0x38);
    sw(a2, sp, 0xC);
    sw(a3, sp, 0x14);
    link(ctx, 0x5401BCu);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x10);
    call(ctx, gen::fn__sceCreateThread_00502f60);
    v1 = 0x790000;
    a1 = 0;
    s0 = addiu(v1, -31016);  // &0x7886D8 safe tid
    sw(v0, s0, 0);  // 0x7886D8 safe tid
    lw(v0, s0, 0);  // 0x7886D8 safe tid
    link(ctx, 0x5401D8u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 0);  // 0x7886D8 safe tid
    call(ctx, gen::fn_StartThread_005042a0);
    lw(v1, s0, 0);  // 0x7886D8 safe tid
    v0 = 0x790000;
    if (v1 != 0) {
        // 0x005401ec
        charge(ctx, 5);
        lw(a0, s0, 0);
        jal(ctx, 0x5401F0u, gen::fn_sub_540118_00540118);
        lw(v1, s0, 0);
        v0 = 0x790000;
    }
    // 0x00540200
    charge(ctx, 7);
    lw(a0, s0, 0);
    link(ctx, 0x540204u);  // $ra first: the delay slot below depends on it
    lw(a1, v0, -31148);
    call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
    ld(s0, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x00540220 adxm_SetupUsrVsyncThrd -- 184 bytes; frame 0x40: s0 sp+0x30, ra sp+0x38
// ADXM: create the user vsync thread (sub_53FB58) on the caller's stack a0 / size a1 (logged) or the built-in one
// (0x788F70, 4 KiB), start it and set its priority (0x788658); id to 0x7886DC.
void adxm_SetupUsrVsyncThrd(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00540220
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = 0x540000;
    sp = addiu(sp, -0x40);
    a3 = a1;
    v1 = a0;
    v0 = addiu(v0, -1192);  // &sub_53FB58
    sd(s0, sp, 0x30);
    sd(ra, sp, 0x38);
    a2 = a3;
    a1 = v1;
    sw(v0, sp, 0x4);
    if (v1 != 0) {
        // 0x00540268
        charge(ctx, 5);
        a0 = 0x7C0000;
        sw(v1, sp, 0x8);
        a0 = addiu(a0, 9504);  // &0x7C2520
        link(ctx, 0x540274u);  // $ra first: the delay slot below depends on it
        sw(a3, sp, 0xC);
        call(ctx, gen::fn_sub_541760_00541760);
    } else {
        // 0x0054024c
        charge(ctx, 6);
        v0 = 0x790000;
        v1 = 4096;
        v0 = addiu(v0, -28816);  // &0x788F70
        sw(v1, sp, 0xC);
        sw(v0, sp, 0x8);
    }
    // 0x0054027c
    charge(ctx, 23);
    a1 = 0x790000;
    v0 = 0x7D0000;
    lw(v1, a1, -136);  // 0x78FF78 main thread prio
    a0 = sp;
    v0 = addiu(v0, 11504);  // &gp_base
    s0 = 0x790000;
    s0 = addiu(s0, -31012);  // &0x7886DC usr-vsync tid
    sw(v0, sp, 0x10);
    link(ctx, 0x54029Cu);  // $ra first: the delay slot below depends on it
    sw(v1, sp, 0x14);
    call(ctx, gen::fn__sceCreateThread_00502f60);
    sw(v0, s0, 0);  // 0x7886DC usr-vsync tid
    a1 = 0;
    lw(v0, s0, 0);  // 0x7886DC usr-vsync tid
    link(ctx, 0x5402B0u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 0);  // 0x7886DC usr-vsync tid
    call(ctx, gen::fn_StartThread_005042a0);
    lw(a0, s0, 0);  // 0x7886DC usr-vsync tid
    v0 = 0x790000;
    link(ctx, 0x5402C0u);  // $ra first: the delay slot below depends on it
    lw(a1, v0, -31144);
    call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
    ld(s0, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x005402D8 adxm_SetupVsyncThrd -- 136 bytes; frame 0x40: s0 sp+0x30, ra sp+0x38
// ADXM: create the vsync thread (adxm_vsync_proc, stack 0x789F70, 4 KiB), start it and set its priority (0x78865C); id
// to 0x7886E0.
void adxm_SetupVsyncThrd(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005402d8
    enter(ctx, 34);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x40);
    lw(a3, v0, -136);  // 0x78FF78 main thread prio
    v0 = 0x7D0000;
    a1 = 0x540000;
    v1 = 0x790000;
    sd(s0, sp, 0x30);
    s0 = 0x790000;
    v1 = addiu(v1, -24720);  // &0x789F70
    a0 = sp;
    a2 = 4096;
    a1 = addiu(a1, -1040);  // &adxm_vsync_proc
    v0 = addiu(v0, 11504);  // &gp_base
    sd(ra, sp, 0x38);
    sw(a1, sp, 0x4);
    s0 = addiu(s0, -31008);  // &0x7886E0 vsync tid
    sw(v1, sp, 0x8);
    sw(a2, sp, 0xC);
    sw(a3, sp, 0x14);
    link(ctx, 0x540324u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x10);
    call(ctx, gen::fn__sceCreateThread_00502f60);
    sw(v0, s0, 0);  // 0x7886E0 vsync tid
    a1 = 0;
    lw(v0, s0, 0);  // 0x7886E0 vsync tid
    link(ctx, 0x540338u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 0);  // 0x7886E0 vsync tid
    call(ctx, gen::fn_StartThread_005042a0);
    lw(a0, s0, 0);  // 0x7886E0 vsync tid
    v0 = 0x790000;
    link(ctx, 0x540348u);  // $ra first: the delay slot below depends on it
    lw(a1, v0, -31140);
    call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
    ld(s0, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x00540360 adxm_SetupFsThrd -- 136 bytes; frame 0x40: s0 sp+0x30, ra sp+0x38
// ADXM: create the file-system thread (adxm_fs_proc, stack 0x78AF70, 4 KiB), start it and set its priority (0x788660);
// id to 0x7886E4.
void adxm_SetupFsThrd(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00540360
    enter(ctx, 34);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x40);
    lw(a3, v0, -136);  // 0x78FF78 main thread prio
    v0 = 0x7D0000;
    a1 = 0x540000;
    v1 = 0x790000;
    sd(s0, sp, 0x30);
    s0 = 0x790000;
    v1 = addiu(v1, -20624);  // &adxm_stack_fs
    a0 = sp;
    a2 = 4096;
    a1 = addiu(a1, -776);  // &adxm_fs_proc
    v0 = addiu(v0, 11504);  // &gp_base
    sd(ra, sp, 0x38);
    sw(a1, sp, 0x4);
    s0 = addiu(s0, -31004);  // &0x7886E4 fs tid
    sw(v1, sp, 0x8);
    sw(a2, sp, 0xC);
    sw(a3, sp, 0x14);
    link(ctx, 0x5403ACu);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x10);
    call(ctx, gen::fn__sceCreateThread_00502f60);
    sw(v0, s0, 0);  // 0x7886E4 fs tid
    a1 = 0;
    lw(v0, s0, 0);  // 0x7886E4 fs tid
    link(ctx, 0x5403C0u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 0);  // 0x7886E4 fs tid
    call(ctx, gen::fn_StartThread_005042a0);
    lw(a0, s0, 0);  // 0x7886E4 fs tid
    v0 = 0x790000;
    link(ctx, 0x5403D0u);  // $ra first: the delay slot below depends on it
    lw(a1, v0, -31136);
    call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
    ld(s0, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x005403E8 adxm_SetupMwIdleThrd -- 152 bytes; frame 0x40: s0 sp+0x30, ra sp+0x38
// ADXM: create the middleware idle thread (adxm_mwidle_proc, stack 0x78BF70, 8 KiB), start it, set its priority
// (0x788668) and suspend it; id to 0x7886EC.
void adxm_SetupMwIdleThrd(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005403e8
    enter(ctx, 38);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x40);
    lw(a3, v0, -136);  // 0x78FF78 main thread prio
    v0 = 0x7D0000;
    a1 = 0x540000;
    v1 = 0x790000;
    sd(s0, sp, 0x30);
    s0 = 0x790000;
    v1 = addiu(v1, -16528);  // &0x78BF70
    a0 = sp;
    a2 = 8192;
    a1 = addiu(a1, -536);  // &adxm_mwidle_proc
    v0 = addiu(v0, 11504);  // &gp_base
    s0 = addiu(s0, -30996);  // &0x7886EC mwidle tid
    sd(ra, sp, 0x38);
    sw(a1, sp, 0x4);
    sw(v1, sp, 0x8);
    sw(a2, sp, 0xC);
    sw(a3, sp, 0x14);
    link(ctx, 0x540434u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x10);
    call(ctx, gen::fn__sceCreateThread_00502f60);
    sw(v0, s0, 0);  // 0x7886EC mwidle tid
    a1 = 0;
    lw(v0, s0, 0);  // 0x7886EC mwidle tid
    link(ctx, 0x540448u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 0);  // 0x7886EC mwidle tid
    call(ctx, gen::fn_StartThread_005042a0);
    lw(a0, s0, 0);  // 0x7886EC mwidle tid
    v0 = 0x790000;
    link(ctx, 0x540458u);  // $ra first: the delay slot below depends on it
    lw(a1, v0, -31128);
    call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
    lw(a0, s0, 0);  // 0x7886EC mwidle tid
    jal(ctx, 0x540464u, gen::fn_sub_540118_00540118);
    lw(v1, s0, 0);  // 0x7886EC mwidle tid
    ld(ra, sp, 0x38);
    ld(s0, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00540480 adxm_SetupUsrIdleThrd -- 208 bytes; frame 0x40: s0 sp+0x30, ra sp+0x38
// ADXM: create the user idle thread (sub_53FF20) on the caller's stack a0 / size a1 (logged) or the built-in one
// (0x78DF70, 8 KiB), start, prioritise (0x78866C) and suspend it; id to 0x7886F0; returns the mwidle id.
void adxm_SetupUsrIdleThrd(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00540480
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = 0x540000;
    sp = addiu(sp, -0x40);
    a3 = a1;
    v1 = a0;
    v0 = addiu(v0, -224);  // &sub_53FF20
    sd(s0, sp, 0x30);
    sd(ra, sp, 0x38);
    a2 = a3;
    a1 = v1;
    sw(v0, sp, 0x4);
    if (v1 != 0) {
        // 0x005404c8
        charge(ctx, 5);
        a0 = 0x7C0000;
        sw(v1, sp, 0x8);
        a0 = addiu(a0, 9568);  // &0x7C2560
        link(ctx, 0x5404D4u);  // $ra first: the delay slot below depends on it
        sw(a3, sp, 0xC);
        call(ctx, gen::fn_sub_541760_00541760);
    } else {
        // 0x005404ac
        charge(ctx, 6);
        v0 = 0x790000;
        v1 = 8192;
        v0 = addiu(v0, -8336);  // &0x78DF70
        sw(v1, sp, 0xC);
        sw(v0, sp, 0x8);
    }
    // 0x005404dc
    charge(ctx, 29);
    a1 = 0x790000;
    v0 = 0x7D0000;
    lw(v1, a1, -136);  // 0x78FF78 main thread prio
    a0 = sp;
    v0 = addiu(v0, 11504);  // &gp_base
    s0 = 0x790000;
    sw(v1, sp, 0x14);
    s0 = addiu(s0, -30992);  // &0x7886F0 usr-idle tid
    link(ctx, 0x5404FCu);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x10);
    call(ctx, gen::fn__sceCreateThread_00502f60);
    sw(v0, s0, 0);  // 0x7886F0 usr-idle tid
    a1 = 0;
    lw(v0, s0, 0);  // 0x7886F0 usr-idle tid
    link(ctx, 0x540510u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 0);  // 0x7886F0 usr-idle tid
    call(ctx, gen::fn_StartThread_005042a0);
    lw(a0, s0, 0);  // 0x7886F0 usr-idle tid
    v0 = 0x790000;
    link(ctx, 0x540520u);  // $ra first: the delay slot below depends on it
    lw(a1, v0, -31124);
    call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
    lw(a0, s0, 0);  // 0x7886F0 usr-idle tid
    jal(ctx, 0x54052Cu, gen::fn_sub_540118_00540118);
    v1 = 0x790000;
    v1 = addiu(v1, -30996);  // &0x7886EC mwidle tid
    ld(s0, sp, 0x30);
    lw(v0, v1, 0);  // 0x7886EC mwidle tid
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x00540550 __errno -- 12 bytes; leaf frame (no stack)
// [adxm_GetThrdMode] ADXM: returns the word at 0x788648 (1 when the user vsync / idle threads of ADXM_SetupThrdEx run).
// The symbol name __errno is the map's; the body is a plain getter.
void __errno(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00540550
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x790000;
    lw(v0, v1, -31160);  // 0x788648 ADXM thread mode
}

// 0x00540560 sub_540560 -- 16 bytes; leaf frame (no stack)
// [adxm_IsSetup] ADXM: 1 when the setup count 0x788644 is non-zero.
void sub_540560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00540560
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 0x790000;
    lw(v0, v1, -31164);  // 0x788644 ADXM setup count
    v0 = sltu(0, v0);
}

// 0x00540570 sub_540570 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: calls sub_5651F0 (tail position, $ra kept).
void sub_540570(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00540570
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5651F0_005651f0(ctx);  // tail call
}

// 0x00540588 ADXM_SetupThrd -- 400 bytes; frame 0x50: s2 sp+0x40, s0 sp+0x30, s1 sp+0x38, ra sp+0x48
// ADXM: first-call setup. Clears the sleep flag, then (setup count 0 only) runs sub_565550 (a0), installs the server
// callbacks, clears the user callbacks 0x997038-0x997044, takes the six priorities from the parameter record a0 or the
// defaults (1, safe 8, vsync 16, fs 18, main 24, mwidle 25), reads the main thread's current priority, creates the four
// threads, lowers the main thread and registers sub_53FA98 (sub_565158(6, ..)). Returns the incremented setup count.
void ADXM_SetupThrd(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00540588
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x790000;
    sd(s2, sp, 0x40);
    s2 = 0x790000;
    sd(s0, sp, 0x30);
    s0 = a0;
    sd(s1, sp, 0x38);
    v1 = 0x790000;
    sd(ra, sp, 0x48);
    v0 = addiu(v0, -31168);  // &0x788640
    lw(a1, s2, -31164);  // 0x788644 ADXM setup count
    v1 = addiu(v1, -31076);  // &0x78869C main asleep
    lw(a2, v0, 0);  // 0x788640
    sw(zero, v1, 0);  // 0x78869C main asleep
    if (a1 != 0) {
        v1 = addiu(s2, -31164);  // &0x788644 ADXM setup count
    } else {
        // 0x005405c8
        charge(ctx, 19);
        jal(ctx, 0x5405C8u, gen::fn_sub_565550_00565550);
        a0 = 0x540000;
        a1 = 0;
        a0 = addiu(a0, -1864);  // &sub_53F8B8
        jal(ctx, 0x5405D8u, gen::fn_sub_565230_00565230);
        a0 = 0x540000;
        a0 = addiu(a0, -1728);  // &sub_53F940
        a1 = 0;
        jal(ctx, 0x5405E8u, gen::fn_sub_565248_00565248);
        v0 = 0x990000;
        v1 = 0x990000;
        v0 = addiu(v0, 28728);  // &0x997038 user cb 1
        v1 = addiu(v1, 28736);  // &0x997040 user cb 2
        sw(zero, v0, 4);  // 0x99703C user cb 1 arg
        sw(zero, v0, 0);  // 0x997038 user cb 1
        sw(zero, v1, 4);  // 0x997044 user cb 2 arg
        sw(zero, v1, 0);  // 0x997040 user cb 2
        if (s0 != 0) {
            // 0x00540650
            charge(ctx, 14);
            lw(v1, s0, 16);
            s1 = 0x790000;
            a0 = addiu(s1, -31152);  // &0x788650 prm[0]
            sw(v1, a0, 20);  // 0x788664 main prio
            lw(v0, s0, 0);
            sw(v0, a0, 0);  // 0x788650 prm[0]
            lw(v1, s0, 4);
            sw(v1, a0, 4);  // 0x788654 safe prio
            lw(v0, s0, 8);
            sw(v0, a0, 12);  // 0x78865C vsync prio
            lw(v1, s0, 12);
            sw(v1, a0, 16);  // 0x788660 fs prio
            lw(v0, s0, 20);
            sw(v0, a0, 24);  // 0x788668 mwidle prio
        } else {
            // 0x00540614
            charge(ctx, 15);
            s1 = 0x790000;
            v0 = 25;
            a0 = addiu(s1, -31152);  // &0x788650 prm[0]
            v1 = 24;
            sw(v0, a0, 24);  // 0x788668 mwidle prio
            v0 = 1;
            sw(v1, a0, 20);  // 0x788664 main prio
            v1 = 8;
            sw(v0, a0, 0);  // 0x788650 prm[0]
            v0 = 16;
            sw(v1, a0, 4);  // 0x788654 safe prio
            v1 = 18;
            sw(v0, a0, 12);  // 0x78865C vsync prio
            sw(v1, a0, 16);  // 0x788660 fs prio
        }
        // 0x00540688
        charge(ctx, 27);
        s0 = 0x790000;
        jal(ctx, 0x540688u, gen::fn__sceGetThreadId_00503050);
        s0 = addiu(s0, -31000);  // &0x7886E8 main tid
        a1 = sp;
        sw(v0, s0, 0);  // 0x7886E8 main tid
        link(ctx, 0x54069Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);  // 0x7886E8 main tid
        call(ctx, gen::fn__sceReferThreadStatus_00503060);
        v1 = 0x790000;
        lw(v0, sp, 0x18);
        link(ctx, 0x5406ACu);  // $ra first: the delay slot below depends on it
        sw(v0, v1, -136);
        call(ctx, gen::fn_adxm_SetupSafeThrd_00540178);
        jal(ctx, 0x5406B4u, gen::fn_adxm_SetupVsyncThrd_005402d8);
        jal(ctx, 0x5406BCu, gen::fn_adxm_SetupFsThrd_00540360);
        jal(ctx, 0x5406C4u, gen::fn_adxm_SetupMwIdleThrd_005403e8);
        lw(a0, s0, 0);  // 0x7886E8 main tid
        v0 = addiu(s1, -31152);
        link(ctx, 0x5406D4u);  // $ra first: the delay slot below depends on it
        lw(a1, v0, 20);
        call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
        a1 = 0x540000;
        a1 = addiu(a1, -1384);  // &sub_53FA98
        a0 = 6;
        a2 = 0;
        jal(ctx, 0x5406E8u, gen::fn_sub_565158_00565158);
        v1 = addiu(s2, -31164);
    }
    // 0x005406f4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s2, sp, 0x40);
    lw(v0, v1, 0);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    v0 = addiu(v0, 1);
    ld(ra, sp, 0x48);
    sw(v0, v1, 0);
    sp = addiu(sp, 0x50);
}

// 0x00540718 sub_540718 -- 80 bytes; leaf frame (no stack)
// ADXM: raise the six thread exit requests (64-bit words 0x7886F8 .. 0x788748, stride 16) to 1; returns 1.
void sub_540718(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00540718
    enter(ctx, 20);  // entry check point + this block's cycles
    v1 = 0x790000;
    a0 = 0x790000;
    a1 = 0x790000;
    a2 = 0x790000;
    a3 = 0x790000;
    t0 = 0x790000;
    v0 = 1;
    v1 = addiu(v1, -30984);  // &0x7886F8 safe exit req
    a0 = addiu(a0, -30968);  // &0x788708 usr-vsync exit req
    a1 = addiu(a1, -30952);  // &0x788718 vsync exit req
    a2 = addiu(a2, -30936);  // &0x788728 fs exit req
    a3 = addiu(a3, -30920);  // &0x788738 mwidle exit req
    t0 = addiu(t0, -30904);  // &0x788748 usr-idle exit req
    sd(v0, v1, 0);  // 0x7886F8 safe exit req
    sd(v0, a0, 0);  // 0x788708 usr-vsync exit req
    sd(v0, a1, 0);  // 0x788718 vsync exit req
    sd(v0, a2, 0);  // 0x788728 fs exit req
    sd(v0, a3, 0);  // 0x788738 mwidle exit req
    sd(v0, t0, 0);  // 0x788748 usr-idle exit req
}

// 0x00540768 sub_540768 -- 148 bytes; frame 0x10: ra sp+0x0
// ADXM: shutdown. Decrements the setup count; at 0 raises the exit requests, ends the mwidle, fs, vsync and safe
// threads, restores the main thread's priority, clears the server callbacks and runs sub_565590.
void sub_540768(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00540768
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x790000;
    sd(ra, sp, 0x0);
    v1 = addiu(v1, -31164);  // &0x788644 ADXM setup count
    lw(v0, v1, 0);  // 0x788644 ADXM setup count
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x788644 ADXM setup count
    if (v0 != 0) {
        // 0x005407f0
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00540788
    charge(ctx, 25);
    jal(ctx, 0x540788u, gen::fn_sub_540718_00540718);
    jal(ctx, 0x540790u, gen::fn_sub_5408D0_005408d0);
    jal(ctx, 0x540798u, gen::fn_sub_540A70_00540a70);
    jal(ctx, 0x5407A0u, gen::fn_sub_5409A0_005409a0);
    jal(ctx, 0x5407A8u, gen::fn_sub_540C70_00540c70);
    v0 = 0x790000;
    v1 = 0x790000;
    v0 = addiu(v0, -31000);  // &0x7886E8 main tid
    lw(a1, v1, -136);  // 0x78FF78 main thread prio
    link(ctx, 0x5407C0u);  // $ra first: the delay slot below depends on it
    lw(a0, v0, 0);
    call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
    a0 = 0;
    a1 = 0;
    jal(ctx, 0x5407CCu, gen::fn_sub_565230_00565230);
    a0 = 0;
    a1 = 0;
    jal(ctx, 0x5407D8u, gen::fn_sub_565248_00565248);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_565590_00565590(ctx);  // tail call
}

// 0x00540800 sub_540800 -- 204 bytes; frame 0x40: s6 sp+0x30, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x38
// ADXM: end the user idle thread: until its exit ack (0x788750) is set, request exit (0x788748), raise it to priority
// 1, wake and resume it; then clear ack, request and id 0x7886F0.
void sub_540800(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00540800
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s6, sp, 0x30);
    s6 = 0x790000;
    sd(s0, sp, 0x0);
    v1 = addiu(s6, -30896);  // &0x788750 usr-idle exit ack
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x38);
    ld(v0, v1, 0);  // 0x788750 usr-idle exit ack
    s5 = 0x790000;
    if (v0 != 0) {
        // 0x00540888
        charge(ctx, 3);
        s4 = 0x790000;
        v0 = addiu(s6, -30896);
        ld(s6, sp, 0x30);
    } else {
        // 0x00540838
        charge(ctx, 6);
        s4 = 0x790000;
        s3 = v1;
        s2 = addiu(s5, -30904);
        s1 = 1;
        s0 = addiu(s4, -30992);  // &0x7886F0 usr-idle tid
        for (;;) {
            // 0x00540850
            charge(ctx, 11);
            sd(s1, s2, 0);
            a1 = 1;
            link(ctx, 0x540858u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
            link(ctx, 0x540860u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn__sceWakeupThread_00503090);
            link(ctx, 0x540868u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn_sub_5400B0_005400b0);
            ld(v1, s3, 0);
            v0 = addiu(s6, -30896);
            if (v1 != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0054087c
        charge(ctx, 2);
        ld(s6, sp, 0x30);
    }
    // 0x00540894 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    v1 = addiu(s5, -30904);
    ld(s5, sp, 0x28);
    a0 = addiu(s4, -30992);
    ld(s4, sp, 0x20);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x38);
    sd(zero, v0, 0);
    sd(zero, v1, 0);
    sw(zero, a0, 0);
    sp = addiu(sp, 0x40);
}

// 0x005408D0 sub_5408D0 -- 204 bytes; frame 0x40: s6 sp+0x30, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x38
// ADXM: end the mwidle thread (ack 0x788740, request 0x788738, id 0x7886EC); same shape as sub_540800.
void sub_5408D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005408d0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s6, sp, 0x30);
    s6 = 0x790000;
    sd(s0, sp, 0x0);
    v1 = addiu(s6, -30912);  // &0x788740 mwidle exit ack
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x38);
    ld(v0, v1, 0);  // 0x788740 mwidle exit ack
    s5 = 0x790000;
    if (v0 != 0) {
        // 0x00540958
        charge(ctx, 3);
        s4 = 0x790000;
        v0 = addiu(s6, -30912);
        ld(s6, sp, 0x30);
    } else {
        // 0x00540908
        charge(ctx, 6);
        s4 = 0x790000;
        s3 = v1;
        s2 = addiu(s5, -30920);
        s1 = 1;
        s0 = addiu(s4, -30996);  // &0x7886EC mwidle tid
        for (;;) {
            // 0x00540920
            charge(ctx, 11);
            sd(s1, s2, 0);
            a1 = 1;
            link(ctx, 0x540928u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
            link(ctx, 0x540930u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn__sceWakeupThread_00503090);
            link(ctx, 0x540938u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn_sub_5400B0_005400b0);
            ld(v1, s3, 0);
            v0 = addiu(s6, -30912);
            if (v1 != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0054094c
        charge(ctx, 2);
        ld(s6, sp, 0x30);
    }
    // 0x00540964 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    v1 = addiu(s5, -30920);
    ld(s5, sp, 0x28);
    a0 = addiu(s4, -30996);
    ld(s4, sp, 0x20);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x38);
    sd(zero, v0, 0);
    sd(zero, v1, 0);
    sw(zero, a0, 0);
    sp = addiu(sp, 0x40);
}

// 0x005409A0 sub_5409A0 -- 204 bytes; frame 0x40: s6 sp+0x30, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x38
// ADXM: end the vsync thread (ack 0x788720, request 0x788718, id 0x7886E0); same shape as sub_540800.
void sub_5409A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005409a0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s6, sp, 0x30);
    s6 = 0x790000;
    sd(s0, sp, 0x0);
    v1 = addiu(s6, -30944);  // &0x788720 vsync exit ack
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x38);
    ld(v0, v1, 0);  // 0x788720 vsync exit ack
    s5 = 0x790000;
    if (v0 != 0) {
        // 0x00540a28
        charge(ctx, 3);
        s4 = 0x790000;
        v0 = addiu(s6, -30944);
        ld(s6, sp, 0x30);
    } else {
        // 0x005409d8
        charge(ctx, 6);
        s4 = 0x790000;
        s3 = v1;
        s2 = addiu(s5, -30952);
        s1 = 1;
        s0 = addiu(s4, -31008);  // &0x7886E0 vsync tid
        for (;;) {
            // 0x005409f0
            charge(ctx, 11);
            sd(s1, s2, 0);
            a1 = 1;
            link(ctx, 0x5409F8u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
            link(ctx, 0x540A00u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn__sceWakeupThread_00503090);
            link(ctx, 0x540A08u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn_sub_5400B0_005400b0);
            ld(v1, s3, 0);
            v0 = addiu(s6, -30944);
            if (v1 != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00540a1c
        charge(ctx, 2);
        ld(s6, sp, 0x30);
    }
    // 0x00540a34 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    v1 = addiu(s5, -30952);
    ld(s5, sp, 0x28);
    a0 = addiu(s4, -31008);
    ld(s4, sp, 0x20);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x38);
    sd(zero, v0, 0);
    sd(zero, v1, 0);
    sw(zero, a0, 0);
    sp = addiu(sp, 0x40);
}

// 0x00540A70 sub_540A70 -- 304 bytes; frame 0x50: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s7 sp+0x38, ra sp+0x40
// ADXM: end the fs thread (ack 0x788730, request 0x788728, id 0x7886E4). With 0x788690 == 1 (fs thread not driven) it
// only spins on the ack; otherwise it counts its wake rounds in 0x78876C.
void sub_540A70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00540a70
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    v0 = addiu(v0, -31088);  // &0x788690
    sd(s1, sp, 0x8);
    a0 = 1;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(s6, sp, 0x30);
    sd(s7, sp, 0x38);
    sd(ra, sp, 0x40);
    lw(v1, v0, 0);  // 0x788690
    v0 = 0x790000;
    if (v1 == a0) {
        // 0x00540ab0
        charge(ctx, 2);
        s5 = 0x790000;
        v0 = addiu(s5, -30928);  // &0x788730 fs exit ack
        for (;;) {
            // 0x00540ab8
            charge(ctx, 7);
            ld(v1, v0, 0);
            s7 = 0x790000;
            if (v1 != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00540ad4
        charge(ctx, 2);
        s6 = 0x790000;
        goto L_00540b5c;
    }
    // 0x00540ae0
    charge(ctx, 7);
    s5 = 0x790000;
    v1 = addiu(v0, -30868);
    a0 = addiu(s5, -30928);  // &0x788730 fs exit ack
    sw(zero, v1, 0);
    ld(v0, a0, 0);  // 0x788730 fs exit ack
    s7 = 0x790000;
    if (v0 != 0) {
        // 0x00540b58
        charge(ctx, 1);
        s6 = 0x790000;
    L_00540b5c:
        charge(ctx, 2);
        v0 = addiu(s5, -30928);
        ld(s5, sp, 0x28);
    } else {
        // 0x00540afc
        charge(ctx, 7);
        s6 = 0x790000;
        s1 = v1;
        s4 = a0;
        s3 = addiu(s7, -30936);
        s2 = 1;
        s0 = addiu(s6, -31004);  // &0x7886E4 fs tid
        for (;;) {
            // 0x00540b18
            charge(ctx, 14);
            sd(s2, s3, 0);
            a1 = 1;
            link(ctx, 0x540B20u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
            link(ctx, 0x540B28u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn__sceWakeupThread_00503090);
            link(ctx, 0x540B30u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn_sub_5400B0_005400b0);
            lw(v1, s1, 0);
            v1 = addiu(v1, 1);
            sw(v1, s1, 0);
            ld(v0, s4, 0);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addiu(s5, -30928);
            if (!cc) {
                break;
            }
            backedge(ctx);
        }
        // 0x00540b50
        charge(ctx, 2);
        ld(s5, sp, 0x28);
    }
    // 0x00540b64 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    v1 = addiu(s7, -30936);
    ld(s7, sp, 0x38);
    a0 = addiu(s6, -31004);
    ld(s6, sp, 0x30);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x40);
    sd(zero, v0, 0);
    sd(zero, v1, 0);
    sw(zero, a0, 0);
    sp = addiu(sp, 0x50);
}

// 0x00540BA0 sub_540BA0 -- 204 bytes; frame 0x40: s6 sp+0x30, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x38
// ADXM: end the user vsync thread (ack 0x788710, request 0x788708, id 0x7886DC); same shape as sub_540800.
void sub_540BA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00540ba0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s6, sp, 0x30);
    s6 = 0x790000;
    sd(s0, sp, 0x0);
    v1 = addiu(s6, -30960);  // &0x788710 usr-vsync exit ack
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x38);
    ld(v0, v1, 0);  // 0x788710 usr-vsync exit ack
    s5 = 0x790000;
    if (v0 != 0) {
        // 0x00540c28
        charge(ctx, 3);
        s4 = 0x790000;
        v0 = addiu(s6, -30960);
        ld(s6, sp, 0x30);
    } else {
        // 0x00540bd8
        charge(ctx, 6);
        s4 = 0x790000;
        s3 = v1;
        s2 = addiu(s5, -30968);
        s1 = 1;
        s0 = addiu(s4, -31012);  // &0x7886DC usr-vsync tid
        for (;;) {
            // 0x00540bf0
            charge(ctx, 11);
            sd(s1, s2, 0);
            a1 = 1;
            link(ctx, 0x540BF8u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
            link(ctx, 0x540C00u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn__sceWakeupThread_00503090);
            link(ctx, 0x540C08u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn_sub_5400B0_005400b0);
            ld(v1, s3, 0);
            v0 = addiu(s6, -30960);
            if (v1 != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00540c1c
        charge(ctx, 2);
        ld(s6, sp, 0x30);
    }
    // 0x00540c34 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    v1 = addiu(s5, -30968);
    ld(s5, sp, 0x28);
    a0 = addiu(s4, -31012);
    ld(s4, sp, 0x20);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x38);
    sd(zero, v0, 0);
    sd(zero, v1, 0);
    sw(zero, a0, 0);
    sp = addiu(sp, 0x40);
}

// 0x00540C70 sub_540C70 -- 204 bytes; frame 0x40: s6 sp+0x30, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x38
// ADXM: end the safe thread (ack 0x788700, request 0x7886F8, id 0x7886D8); same shape as sub_540800.
void sub_540C70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00540c70
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s6, sp, 0x30);
    s6 = 0x790000;
    sd(s0, sp, 0x0);
    v1 = addiu(s6, -30976);  // &0x788700 safe exit ack
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x38);
    ld(v0, v1, 0);  // 0x788700 safe exit ack
    s5 = 0x790000;
    if (v0 != 0) {
        // 0x00540cf8
        charge(ctx, 3);
        s4 = 0x790000;
        v0 = addiu(s6, -30976);
        ld(s6, sp, 0x30);
    } else {
        // 0x00540ca8
        charge(ctx, 6);
        s4 = 0x790000;
        s3 = v1;
        s2 = addiu(s5, -30984);
        s1 = 1;
        s0 = addiu(s4, -31016);  // &0x7886D8 safe tid
        for (;;) {
            // 0x00540cc0
            charge(ctx, 11);
            sd(s1, s2, 0);
            a1 = 1;
            link(ctx, 0x540CC8u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
            link(ctx, 0x540CD0u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn__sceWakeupThread_00503090);
            link(ctx, 0x540CD8u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn_sub_5400B0_005400b0);
            ld(v1, s3, 0);
            v0 = addiu(s6, -30976);
            if (v1 != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00540cec
        charge(ctx, 2);
        ld(s6, sp, 0x30);
    }
    // 0x00540d04 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    v1 = addiu(s5, -30984);
    ld(s5, sp, 0x28);
    a0 = addiu(s4, -31016);
    ld(s4, sp, 0x20);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x38);
    sd(zero, v0, 0);
    sd(zero, v1, 0);
    sw(zero, a0, 0);
    sp = addiu(sp, 0x40);
}

// 0x00540D40 sub_540D40 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: calls sub_564978 (the lock that the ADX servers take).
void sub_540D40(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00540d40
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564978_00564978(ctx);  // tail call
}

// 0x00540D58 sub_540D58 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: calls sub_564990 (the matching unlock).
void sub_540D58(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00540d58
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564990_00564990(ctx);  // tail call
}

// 0x00540D80 ADXPS2_ExecVint -- 296 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// ADXM vblank handler: counts vblanks (0x787568); unless re-entered (0x78875C) and while ADXM is set up, wakes the
// vsync, fs and (thread mode 1) user vsync threads that are not marked off (0x788688 / 0x788690 / 0x78868C), counts the
// tick (0x7886D0), runs sub_53F6D0; then calls the user vblank callback 0x788760 (jalr) with a0 or returns 0.
void ADXPS2_ExecVint(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00540d80
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x780000;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 0x790000;
    sd(s0, sp, 0x0);
    v0 = addiu(v0, 30056);  // &0x787568 ADXM vblank count
    sd(ra, sp, 0x18);
    a1 = addiu(s2, -30884);  // &0x78875C ExecVint busy
    lw(v1, v0, 0);  // 0x787568 ADXM vblank count
    v1 = addiu(v1, 1);
    sw(v1, v0, 0);  // 0x787568 ADXM vblank count
    lw(a0, a1, 0);  // 0x78875C ExecVint busy
    v0 = 0x790000;
    if (a0 == 0) {
        // 0x00540dc0
        charge(ctx, 6);
        v0 = 0x790000;
        s0 = 1;
        lw(v1, v0, -31164);  // 0x788644 ADXM setup count
        sw(s0, a1, 0);
        v0 = 0x790000;
        if (i64(v1) > 0) {
            // 0x00540dd8
            charge(ctx, 4);
            v0 = addiu(v0, -31096);
            lw(v1, v0, 0);
            v0 = 0x790000;
            if (v1 != s0) {
                // 0x00540de8
                charge(ctx, 3);
                v0 = addiu(v0, -31008);
                link(ctx, 0x540DECu);  // $ra first: the delay slot below depends on it
                lw(a0, v0, 0);
                call(ctx, gen::fn_sub_53FFF8_0053fff8);
            }
            // 0x00540df4
            charge(ctx, 5);
            v0 = 0x790000;
            v0 = addiu(v0, -31088);  // &0x788690
            lw(v1, v0, 0);  // 0x788690
            v0 = 0x790000;
            if (v1 != s0) {
                // 0x00540e08
                charge(ctx, 3);
                v0 = addiu(v0, -31004);
                link(ctx, 0x540E0Cu);  // $ra first: the delay slot below depends on it
                lw(a0, v0, 0);
                call(ctx, gen::fn_sub_53FFF8_0053fff8);
            }
            // 0x00540e14
            charge(ctx, 5);
            jal(ctx, 0x540E14u, gen::fn___errno_00540550);
            a0 = v0;
            v1 = 0x790000;
            if (a0 == s0) {
                // 0x00540e28
                charge(ctx, 5);
                v0 = 0x790000;
                v0 = addiu(v0, -31092);  // &0x78868C
                lw(v1, v0, 0);  // 0x78868C
                v0 = 0x790000;
                if (v1 != a0) {
                    // 0x00540e3c
                    charge(ctx, 3);
                    v0 = addiu(v0, -31012);
                    link(ctx, 0x540E40u);  // $ra first: the delay slot below depends on it
                    lw(a0, v0, 0);
                    call(ctx, gen::fn_sub_53FFF8_0053fff8);
                }
                // 0x00540e48
                charge(ctx, 1);
                v1 = 0x790000;
            }
            // 0x00540e4c
            charge(ctx, 4);
            v1 = addiu(v1, -31024);
            ld(v0, v1, 0);
            v0 = daddiu(v0, 1);
            sd(v0, v1, 0);
        }
        // 0x00540e5c
        charge(ctx, 5);
        jal(ctx, 0x540E5Cu, gen::fn_sub_53F6D0_0053f6d0);
        v1 = addiu(s2, -30884);
        sw(zero, v1, 0);
        v0 = 0x790000;
    }
    // 0x00540e70
    charge(ctx, 3);
    lw(v0, v0, -30880);
    if (v0 == 0) {
        v0 = 0;
        // 0x00540e90
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    } else {
        // 0x00540e7c
        charge(ctx, 4);
        a0 = s1;
        jalr(ctx, 0x540E7Cu, v0.u());
        ld(s0, sp, 0x0);
    }
    // 0x00540e94 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00540EA8 sub_540EA8 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk to ADXPS2_ExecVint (the kwlnGsSyncVCallback hook).
void sub_540EA8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00540ea8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_ADXPS2_ExecVint_00540d80(ctx);  // tail call
}

// 0x00540ED8 sub_540ED8 -- 136 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXM: resume and wake the mwidle thread, and in thread mode 1 the user idle thread too.
void sub_540ED8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00540ed8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, -30996);  // &0x7886EC mwidle tid
    sd(ra, sp, 0x8);
    link(ctx, 0x540EECu);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 0);  // 0x7886EC mwidle tid
    call(ctx, gen::fn_sub_5400B0_005400b0);
    lw(v1, s0, 0);  // 0x7886EC mwidle tid
    if (v0 == v1) {
        // 0x00540f00
        charge(ctx, 2);
        link(ctx, 0x540F00u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_540048_00540048);
    }
    // 0x00540f08
    charge(ctx, 6);
    jal(ctx, 0x540F08u, gen::fn___errno_00540550);
    v1 = 0x790000;
    a0 = 1;
    s0 = addiu(v1, -30992);  // &0x7886F0 usr-idle tid
    if (v0 != a0) {
        // 0x00540f50
        charge(ctx, 1);
        ld(s0, sp, 0x0);
        // 0x00540f54 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00540f20
    charge(ctx, 6);
    lw(a0, s0, 0);
    jal(ctx, 0x540F24u, gen::fn_sub_5400B0_005400b0);
    lw(v1, s0, 0);
    if (v0 != v1) {
        ld(s0, sp, 0x0);
        // 0x00540f54 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00540f38
    charge(ctx, 5);
    lw(a0, s0, 0);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_540048_00540048(ctx);  // tail call
}

// 0x00540F60 sub_540F60 -- 124 bytes; frame 0x50: s1 sp+0x38, s0 sp+0x30, ra sp+0x40
// ADXM: when the main thread sleeps (0x78869C == 1) and waits (status 4 / 12), wake it and clear the flag on success.
void sub_540F60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00540f60
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x790000;
    sd(s1, sp, 0x38);
    s1 = addiu(v0, -31076);  // &0x78869C main asleep
    lw(v1, s1, 0);  // 0x78869C main asleep
    a0 = 1;
    sd(s0, sp, 0x30);
    sd(ra, sp, 0x40);
    if (v1 == a0) {
        // 0x00540f84
        charge(ctx, 9);
        v0 = 0x790000;
        a1 = sp;
        s0 = addiu(v0, -31000);  // &0x7886E8 main tid
        link(ctx, 0x540F90u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);  // 0x7886E8 main tid
        call(ctx, gen::fn__sceReferThreadStatus_00503060);
        lw(v1, sp, 0x0);
        v0 = 4;
        a0 = 12;
        if (v1 != v0) {
            // 0x00540fa8
            charge(ctx, 2);
            if (v1 == a0) {
                goto L_00540fb0;
            }
            ld(s0, sp, 0x30);
            // 0x00540fcc (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(s1, sp, 0x38);
            ld(ra, sp, 0x40);
            sp = addiu(sp, 0x50);
            return;
        }
    L_00540fb0:
        charge(ctx, 6);
        lw(a0, s0, 0);
        jal(ctx, 0x540FB4u, gen::fn__sceWakeupThread_00503090);
        lw(v1, s0, 0);
        if (v0 == v1) {
            sw(zero, s1, 0);
        }
    }
    // 0x00540fc8
    charge(ctx, 1);
    ld(s0, sp, 0x30);
    // 0x00540fcc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00540FE0 sub_540FE0 -- 36 bytes; frame 0x10: ra sp+0x0
// ADXM: mark the main thread asleep (0x78869C = 1) and sleep.
void sub_540FE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00540fe0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(ra, sp, 0x0);
    v1 = 1;
    v0 = addiu(v0, -31076);  // &0x78869C main asleep
    ld(ra, sp, 0x0);
    sw(v1, v0, 0);  // 0x78869C main asleep
    sp = addiu(sp, 0x10);
    gen::fn_sub_540098_00540098(ctx);  // tail call
}

// 0x005414E0 sub_5414E0 -- 48 bytes; frame 0x10: ra sp+0x0
// ADXM: call the user callback 0x997038 (jalr) with its argument 0x99703C when one is set.
void sub_5414E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005414e0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x990000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 28728);  // &0x997038 user cb 1
    lw(v1, v0, 0);  // 0x997038 user cb 1
    if (v1 == 0) {
        ld(ra, sp, 0x0);
    } else {
        // 0x005414fc
        charge(ctx, 3);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x5414FCu);  // $ra = the return address
        lw(a0, v0, 4);
        call_ptr(ctx, jt);
        ld(ra, sp, 0x0);
    }
    // 0x00541508 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00541510 sub_541510 -- 48 bytes; frame 0x10: ra sp+0x0
// ADXM: call the user callback 0x997040 (jalr) with its argument 0x997044 when one is set.
void sub_541510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00541510
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x990000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 28736);  // &0x997040 user cb 2
    lw(v1, v0, 0);  // 0x997040 user cb 2
    if (v1 == 0) {
        ld(ra, sp, 0x0);
    } else {
        // 0x0054152c
        charge(ctx, 3);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x54152Cu);  // $ra = the return address
        lw(a0, v0, 4);
        call_ptr(ctx, jt);
        ld(ra, sp, 0x0);
    }
    // 0x00541538 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00541610 sub_541610 -- 20 bytes; leaf frame (no stack)
// Maps a0 == 1 to 1, anything else to 2.
void sub_541610(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00541610
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 1;
    v1 = 2;
    a0 = a0 ^ v0;
    if (a0 != 0) v0 = v1;
}

// 0x005416E8 sub_5416E8 -- 120 bytes; frame 0xF0: ra sp+0x80
// Debug print: vsprintf the variadic arguments (spilled to the frame) into a 128-byte buffer and scePrintf it when the
// print level 0x78FF80 is 0.
void sub_5416E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f18{ctx, 18}, f19{ctx, 19};
    // 0x005416e8
    enter(ctx, 23);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0xF0);
    lw(v1, v0, -128);  // 0x78FF80 print level
    sd(a1, sp, 0xB8);
    a1 = a0;
    sd(a2, sp, 0xC0);
    a2 = addiu(sp, 0xB8);
    sd(ra, sp, 0x80);
    a0 = sp;
    sd(a3, sp, 0xC8);
    sd(t0, sp, 0xD0);
    sd(t1, sp, 0xD8);
    sd(t2, sp, 0xE0);
    sd(t3, sp, 0xE8);
    swc1(f12, sp, 0x98);
    swc1(f13, sp, 0x9C);
    swc1(f14, sp, 0xA0);
    swc1(f15, sp, 0xA4);
    swc1(f16, sp, 0xA8);
    swc1(f17, sp, 0xAC);
    swc1(f18, sp, 0xB0);
    swc1(f19, sp, 0xB4);
    if (v1 == 0) {
        // 0x00541744
        charge(ctx, 4);
        jal(ctx, 0x541744u, gen::fn_vsprintf_005288c8);
        a0 = sp;
        jal(ctx, 0x54174Cu, gen::fn_scePrintf_00505e48);
    }
    // 0x00541754 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x80);
    sp = addiu(sp, 0xF0);
}

// 0x00541760 sub_541760 -- 128 bytes; frame 0xF0: ra sp+0x80
// Debug print: as sub_5416E8, printing unless the print level 0x78FF80 is 2.
void sub_541760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f18{ctx, 18}, f19{ctx, 19};
    // 0x00541760
    enter(ctx, 25);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0xF0);
    lw(t4, v0, -128);  // 0x78FF80 print level
    v1 = a0;
    t5 = 2;
    sd(a1, sp, 0xB8);
    sd(a2, sp, 0xC0);
    a2 = addiu(sp, 0xB8);
    sd(ra, sp, 0x80);
    a0 = sp;
    a1 = v1;
    sd(a3, sp, 0xC8);
    sd(t0, sp, 0xD0);
    sd(t1, sp, 0xD8);
    sd(t2, sp, 0xE0);
    sd(t3, sp, 0xE8);
    swc1(f12, sp, 0x98);
    swc1(f13, sp, 0x9C);
    swc1(f14, sp, 0xA0);
    swc1(f15, sp, 0xA4);
    swc1(f16, sp, 0xA8);
    swc1(f17, sp, 0xAC);
    swc1(f18, sp, 0xB0);
    swc1(f19, sp, 0xB4);
    if (t4 != t5) {
        // 0x005417c4
        charge(ctx, 4);
        jal(ctx, 0x5417C4u, gen::fn_vsprintf_005288c8);
        a0 = sp;
        jal(ctx, 0x5417CCu, gen::fn_scePrintf_00505e48);
    }
    // 0x005417d4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x80);
    sp = addiu(sp, 0xF0);
}

// 0x005417E0 sub_5417E0 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: calls sub_55F688.
void sub_5417E0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005417e0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55F688_0055f688(ctx);  // tail call
}

// 0x005419C0 sub_5419C0 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk to PS2RNA_Init.
void sub_5419C0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005419c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_PS2RNA_Init_0055ff70(ctx);  // tail call
}

// 0x005419D8 sub_5419D8 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: calls sub_560698.
void sub_5419D8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005419d8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_560698_00560698(ctx);  // tail call
}

// 0x005419F0 sub_5419F0 -- 8 bytes; leaf frame (no stack)
// Empty function (jr $ra / nop).
void sub_5419F0(EEContext& ctx) {
    using namespace hg;
    // 0x005419f0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00541AA8 expl_1 -- 72 bytes, 2 chunks; frame 0x10: ra sp+0x0
// PS2RNA: unless (mode 0x7A93F8 == 1 and count 0x7A93F0 <= 0), store 0 to *a1 and 48000 (the output rate) to *a2. The
// symbol name expl_1 is the map's.
void expl_1(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541aa8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00560e78
    charge(ctx, 5);
    v0 = 0x7B0000;
    a0 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8 PS2RNA mode
    v0 = 0xBB80;
    if (v1 == a0) {
        // 0x00560e8c
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0 PS2RNA count
        v0 = 0xBB80;
        if (i64(v1) > 0) {
            goto L_00560e9c;
        }
        // 0x00560ea4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00560e9c:
    charge(ctx, 2);
    sw(zero, a1, 0);
    sw(v0, a2, 0);
    // 0x00560ea4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00541BB8 sub_541BB8 -- 64 bytes, 2 chunks; frame 0x10: ra sp+0x0
// PS2RNA: store a1 to record a0 +92 unless (mode 0x7A93F8 == 1 and count 0x7A93F0 <= 0).
void sub_541BB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541bb8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00561360
    charge(ctx, 5);
    v0 = 0x7B0000;
    a2 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8 PS2RNA mode
    if (v1 != a2) {
        sw(a1, a0, 92);
    } else {
        // 0x00561374
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0 PS2RNA count
        if (i64(v1) > 0) {
            sw(a1, a0, 92);
        }
    }
    // 0x00561384 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00541C60 sub_541C60 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: calls sub_5615B0.
void sub_541C60(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541c60
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5615B0_005615b0(ctx);  // tail call
}

// 0x00541C88 sub_541C88 -- 68 bytes, 2 chunks; frame 0x10: ra sp+0x0
// PS2RNA: store a0 to 0x7A9424 unless (mode 0x7A93F8 == 1 and count 0x7A93F0 <= 0).
void sub_541C88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541c88
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00560d50
    charge(ctx, 5);
    v0 = 0x7B0000;
    a1 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8 PS2RNA mode
    v0 = 0x7B0000;
    if (v1 == a1) {
        // 0x00560d64
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0 PS2RNA count
        v0 = 0x7B0000;
        if (i64(v1) > 0) {
            goto L_00560d74;
        }
        // 0x00560d78 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00560d74:
    charge(ctx, 1);
    sw(a0, v0, -27612);
    // 0x00560d78 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00541CA0 sub_541CA0 -- 72 bytes, 2 chunks; frame 0x10: ra sp+0x0
// PS2RNA: return 0x7A9424, or 0 when mode 0x7A93F8 == 1 and count 0x7A93F0 <= 0.
void sub_541CA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00541ca0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00560d80
    charge(ctx, 5);
    v0 = 0x7B0000;
    a0 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8 PS2RNA mode
    cc = v1 != a0;  // the condition, before the delay slot changes it
    v1 = 0x7B0000;
    if (!cc) {
        // 0x00560d94
        charge(ctx, 4);
        a0 = 0x7B0000;
        lw(v1, a0, -27664);  // 0x7A93F0 PS2RNA count
        v0 = 0;
        if (i64(v1) > 0) {
            // 0x00560da4
            charge(ctx, 1);
            v1 = 0x7B0000;
            goto L_00560da8;
        }
        // 0x00560dac (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00560da8:
    charge(ctx, 1);
    lw(v0, v1, -27612);
    // 0x00560dac (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00541D00 sub_541D00 -- 24 bytes; leaf frame (no stack)
// Decrements the counter 0x78FF88 and returns the new value.
void sub_541D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00541d00
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x790000;
    v1 = addiu(v1, -120);  // &0x78FF88
    lw(v0, v1, 0);  // 0x78FF88
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x78FF88
}

// 0x00541D18 sub_541D18 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Stores a0 to 0x7838EC (body shares a chunk at 0x537770).
void sub_541D18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541d18
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00537770
    charge(ctx, 3);
    v0 = 0x780000;
    sw(a0, v0, 14572);  // 0x7838EC
}

// 0x00541D30 sub_541D30 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk to sceInsockGetErrnoMode (the map's name for 0x537780).
void sub_541D30(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541d30
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sceInsockGetErrnoMode_00537780(ctx);  // tail call
}

// 0x00541DA0 sub_541DA0 -- 72 bytes; frame 0x10: ra sp+0x0
// Finish: decrement the init count 0x78FF90; at 0 clear the 2688-byte table at 0x78FF98.
void sub_541DA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541da0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, -112);  // &0x78FF90
    lw(v1, v0, 0);  // 0x78FF90
    v1 = addiu(v1, -1);
    sw(v1, v0, 0);  // 0x78FF90
    lw(a0, v0, 0);  // 0x78FF90
    ld(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00541de0
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00541dc8
    charge(ctx, 6);
    a0 = 0x790000;
    a1 = 0;
    a0 = addiu(a0, -104);  // &0x78FF98
    a2 = 2688;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x00542F70 sub_542F70 -- 36 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Store a1 / a2 to the decoder record (a0 +4) +252 / +256.
void sub_542F70(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00542f70
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x005383f8
    charge(ctx, 3);
    sw(a2, a0, 256);
    sw(a1, a0, 252);
}

// 0x00542FA8 sub_542FA8 -- 24 bytes; frame 0x10: ra sp+0x0
// Tail call sub_5380E0 on the decoder handle a0 +4.
void sub_542FA8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00542fa8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5380E0_005380e0(ctx);  // tail call
}

// 0x00542FC0 sub_542FC0 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: calls sub_538148.
void sub_542FC0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00542fc0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_538148_00538148(ctx);  // tail call
}

// 0x00543020 sub_543020 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Clear the halfword +154 of the decoder record (a0 +4).
void sub_543020(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543020
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00537ce8
    charge(ctx, 2);
    sh(zero, a0, 154);
}

// 0x00543038 sub_543038 -- 96 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Under the lock pair sub_539818 / sub_539830: add a positive a1 to a0 +160, subtract a non-positive one from a0 +164;
// returns a1.
void sub_543038(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543038
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x54304Cu, gen::fn_sub_539818_00539818);
    if (i64(s1) <= 0) {
        lw(v0, s0, 164);
        // 0x00543070
        charge(ctx, 2);
        v0 = subu(v0, s1);
        sw(v0, s0, 164);
    } else {
        // 0x0054305c
        charge(ctx, 4);
        lw(v0, s0, 160);
        v0 = addu(v0, s1);
        sw(v0, s0, 160);
    }
    // 0x00543078
    charge(ctx, 8);
    jal(ctx, 0x543078u, gen::fn_sub_539830_00539830);
    v0 = s1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00543328 sub_543328 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// When sub_538038(handle) > 0 and the state byte a0 +1 is 2 or 3, return sub_538058(handle), else 0.
void sub_543328(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543328
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    link(ctx, 0x543338u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 4);
    call(ctx, gen::fn_sub_538038_00538038);
    if (i64(v0) <= 0) {
        ld(s0, sp, 0x0);
        // 0x00543370 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        v0 = 0;
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00543348
    charge(ctx, 5);
    lbu(v0, s0, 1);
    v0 = addiu(v0, -2);
    v0 = sltiu(v0, 2);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
        // 0x00543370 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        v0 = 0;
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0054335c
    charge(ctx, 5);
    lw(a0, s0, 4);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_538058_00538058(ctx);  // tail call
}

// 0x00543380 sub_543380 -- 8 bytes; leaf frame (no stack)
// Returns the word a0 +152.
void sub_543380(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00543380
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 152);
}

// 0x00543388 sub_543388 -- 24 bytes; frame 0x10: ra sp+0x0
// Tail call sub_537F70 on the decoder handle a0 +4.
void sub_543388(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543388
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_537F70_00537f70(ctx);  // tail call
}

// 0x005433C0 sub_5433C0 -- 24 bytes; frame 0x10: ra sp+0x0
// Tail call sub_5380A0 on the decoder handle a0 +4.
void sub_5433C0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005433c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5380A0_005380a0(ctx);  // tail call
}

// 0x00543430 sub_543430 -- 28 bytes; leaf frame (no stack)
// ADX encoder: count an init (0x790A18); returns 0.
void sub_543430(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00543430
    enter(ctx, 7);  // entry check point + this block's cycles
    a0 = 0x790000;
    v0 = 0;
    a0 = addiu(a0, 2584);  // &0x790A18 ADX enc init count
    lw(v1, a0, 0);  // 0x790A18 ADX enc init count
    v1 = addiu(v1, 1);
    sw(v1, a0, 0);  // 0x790A18 ADX enc init count
}

// 0x00543450 sub_543450 -- 28 bytes; leaf frame (no stack)
// ADX encoder: count a finish (0x790A18); returns 0.
void sub_543450(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00543450
    enter(ctx, 7);  // entry check point + this block's cycles
    a0 = 0x790000;
    v0 = 0;
    a0 = addiu(a0, 2584);  // &0x790A18 ADX enc init count
    lw(v1, a0, 0);  // 0x790A18 ADX enc init count
    v1 = addiu(v1, -1);
    sw(v1, a0, 0);  // 0x790A18 ADX enc init count
}

// 0x00543470 sub_543470 -- 436 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// [adxenc_CalcKey] ADX encoder: the three 15-bit cipher keys of a key string (a0, length a1): three chained table walks
// (the 0x7C11B8 tables, seeds 0x7C13B8 / 0x7C15B8 / 0x7C17B8) written to *a2 / *a3 / *a4. Inits the encoder first when
// the count is 0.
void sub_543470(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543470
    enter(ctx, 15);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x30);
    lw(v1, v0, 2584);  // 0x790A18 ADX enc init count
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
        // 0x005434ac
        charge(ctx, 2);
        jal(ctx, 0x5434ACu, gen::fn_sub_543430_00543430);
    }
    // 0x005434b4
    charge(ctx, 4);
    sh(zero, s2, 0);
    sh(zero, s3, 0);
    sh(zero, s4, 0);
    if (s1 == 0) {
        // 0x005434c4
        charge(ctx, 2);
        v0 = 0;
        if (i64(s0) > 0) {
            goto L_005434cc;
        }
        // 0x00543604 (the shared epilogue, written out on this path)
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
L_005434cc:
    charge(ctx, 5);
    t3 = 0x7C0000;
    a3 = 0;
    v0 = addiu(t3, 4536);  // &0x7C11B8
    lh(t2, v0, 512);  // 0x7C13B8
    if (i64(s0) > 0) {
        // 0x005434e0
        charge(ctx, 2);
        t0 = v0;
        for (;;) {
            // 0x005434e8
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
        // 0x00543534
        charge(ctx, 2);
        v0 = addiu(t3, 4536);
        a3 = 0;
    }
    // 0x0054353c
    charge(ctx, 2);
    lh(t0, v0, 1024);
    if (i64(s0) > 0) {
        // 0x00543544
        charge(ctx, 1);
        t1 = v0;
        for (;;) {
            // 0x00543548
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
    // 0x00543594
    charge(ctx, 4);
    v0 = addiu(t3, 4536);
    a3 = 0;
    lh(a0, v0, 1536);
    if (i64(s0) > 0) {
        // 0x005435a4
        charge(ctx, 1);
        t1 = v0;
        for (;;) {
            // 0x005435a8
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
    // 0x005435f4
    charge(ctx, 4);
    sh(t2, s2, 0);
    v0 = 0;
    sh(t0, s3, 0);
    sh(a0, s4, 0);
    // 0x00543604 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x005436D0 sub_5436D0 -- 48 bytes; leaf frame (no stack)
// ADX encoder: stream size = 18 * ceil(a2 / 32) * a0 + a1 + 4 (frames of 32 samples per channel, plus header and
// footer).
void sub_5436D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x005436d0
    enter(ctx, 12);  // entry check point + this block's cycles
    v1 = addiu(a2, 31);
    a2 = addiu(a2, 62);
    v0 = slti(v1, 0);
    if (v0 != 0) v1 = a2;
    v1 = sra(v1, 5);
    mult(v1, v1, a0);
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, a1);
    v0 = addiu(v0, 4);
}

// 0x005438C0 sub_5438C0 -- 444 bytes; frame 0x40: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, ra sp+0x38
// ADX encoder: write a2 elements of a1 bytes (4, 2 or 1) from a0 to the stream joint a3 big-endian (GetChunk / PutChunk
// through its vtable, jalr). A short chunk is ungot and 0 returned; other sizes spin forever, as the original.
void sub_5438C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005438c0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    s1 = a1;
    sd(s2, sp, 0x20);
    s2 = a2;
    sd(s3, sp, 0x28);
    s3 = a0;
    sd(s4, sp, 0x30);
    s4 = a3;
    sd(ra, sp, 0x38);
    mult(s0, s1, s2);
    a1 = 0;
    a0 = s4;
    lw(v0, s4, 0);
    a3 = sp;
    lw(v1, v0, 24);
    a2 = s0;
    jalr(ctx, 0x543904u, v1.u());
    lw(v0, sp, 0x4);
    v0 = slt(v0, s0);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 4;
    if (cc) {
        // 0x00543940
        charge(ctx, 2);
        cc = s1 != v0;  // the condition, before the delay slot changes it
        v0 = 2;
        if (cc) {
            // 0x005439a8
            charge(ctx, 2);
            cc = s1 != v0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (cc) {
                // 0x00543a00
                charge(ctx, 2);
                lw(a0, sp, 0x0);
                if (s1 != v0) {
                    for (;;) {
                        // 0x00543a20
                        charge(ctx, 7);
                        backedge(ctx);
                    }
                }
                // 0x00543a08
                charge(ctx, 5);
                a1 = s3;
                a2 = s2 & 0xFFFF;
                jal(ctx, 0x543A0Cu, gen::fn_memcpy_00521250);
                lw(v1, s4, 0);
            } else {
                // 0x005439b0
                charge(ctx, 4);
                a1 = s3;
                lw(a2, sp, 0x0);
                t0 = 0;
                if (i64(s2) <= 0) {
                L_00543a40:
                    charge(ctx, 1);
                    lw(v1, s4, 0);
                } else {
                    // 0x005439c0
                    charge(ctx, 2);
                    a3 = si(-256);
                    for (;;) {
                        // 0x005439c8
                        charge(ctx, 11);
                        lhu(v0, a1, 0);
                        t0 = addiu(t0, 1);
                        lbu(v1, a1, 1);
                        a1 = addiu(a1, 2);
                        v0 = sll(v0, 8);
                        a0 = slt(t0, s2);
                        v0 = v0 & a3;
                        v1 = v1 | v0;
                        sh(v1, a2, 0);
                        a2 = addiu(a2, 2);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x005439f4
                    charge(ctx, 2);
                    lw(v1, s4, 0);
                }
            }
        } else {
            // 0x00543948
            charge(ctx, 4);
            a3 = s3;
            lw(a2, sp, 0x0);
            t0 = 0;
            if (i64(s2) <= 0) {
                goto L_00543a40;
            }
            // 0x00543958
            charge(ctx, 2);
            t1 = 0xFF0000;
            for (;;) {
                // 0x00543960
                charge(ctx, 16);
                lw(a0, a3, 0);
                a3 = addiu(a3, 4);
                t0 = addiu(t0, 1);
                a1 = sra(a0, 8);
                v1 = sll(a0, 8);
                v0 = srl(a0, 24);
                a0 = sll(a0, 24);
                v1 = v1 & t1;
                a1 = a1 & 0xFF00;
                v0 = v0 | a0;
                a0 = slt(t0, s2);
                v1 = v1 | a1;
                v0 = v0 | v1;
                sw(v0, a2, 0);
                a2 = addiu(a2, 4);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x005439a0
            charge(ctx, 2);
            lw(v1, s4, 0);
        }
        // 0x00543a44
        charge(ctx, 6);
        a0 = s4;
        a1 = 1;
        lw(v0, v1, 32);
        a2 = sp;
        jalr(ctx, 0x543A50u, v0.u());
        v0 = s2;
    } else {
        // 0x0054391c
        charge(ctx, 8);
        lw(v1, s4, 0);
        a0 = s4;
        a1 = 0;
        lw(v0, v1, 28);
        a2 = sp;
        jalr(ctx, 0x54392Cu, v0.u());
        v0 = 0;
    }
    // 0x00543a5c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x00543AA8 sub_543AA8 -- 96 bytes; leaf frame (no stack)
// ADX encoder: first free 12-byte predictor record of the 16 at 0x7921F8 (0 when all are used).
void sub_543AA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00543aa8
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = 0x790000;
    v1 = addiu(v1, 8696);  // &0x7921F8
    lb(v0, v1, 0);  // 0x7921F8
    a3 = 0;
    if (v0 == 0) {
        // 0x00543af8
        charge(ctx, 1);
        a0 = 1;
    L_00543afc:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00543abc
        charge(ctx, 3);
        a2 = v1;
        a1 = v1;
        for (;;) {
            // 0x00543ac8
            charge(ctx, 5);
            a3 = addiu(a3, 1);
            a2 = addiu(a2, 12);
            a0 = slti(a3, 16);
            a1 = addiu(a1, 12);
            if (a0 == 0) {
                goto L_00543afc;
            }
            // 0x00543adc
            charge(ctx, 4);
            lb(v0, a2, 0);
            v1 = a1;
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00543aec
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00543b00 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    if (a0 != 0) v0 = v1;
}

// 0x00543B40 sub_543B40 -- 12 bytes; leaf frame (no stack)
// Predictor record: store the coefficients a1 / a2 to +4 / +6.
void sub_543B40(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00543b40
    enter(ctx, 3);  // entry check point + this block's cycles
    sh(a2, a0, 6);
    sh(a1, a0, 4);
}

// 0x00543B50 sub_543B50 -- 12 bytes; leaf frame (no stack)
// Predictor record: store the history a1 / a2 to +8 / +10.
void sub_543B50(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00543b50
    enter(ctx, 3);  // entry check point + this block's cycles
    sh(a2, a0, 10);
    sh(a1, a0, 8);
}

// 0x00543B60 sub_543B60 -- 20 bytes; leaf frame (no stack)
// Predictor record: load the history +8 / +10 to *a1 / *a2.
void sub_543B60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00543b60
    enter(ctx, 5);  // entry check point + this block's cycles
    lhu(v0, a0, 8);
    sh(v0, a1, 0);
    lhu(v1, a0, 10);
    sh(v1, a2, 0);
}

// 0x00543B78 sub_543B78 -- 120 bytes; leaf frame (no stack)
// Predictor step: (c0 * h0 + c1 * h1) >> 12 plus the residual a1, saturated to 16 bits; shifts the history and returns
// the sample.
void sub_543B78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00543b78
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = sll(a1, 16);
    a2 = a0;
    a3 = sra(a1, 16);
    if (a2 == 0) {
        // 0x00543be8
        charge(ctx, 2);
        v0 = a3;
        return;
    }
    // 0x00543b88
    charge(ctx, 13);
    lh(a0, a2, 8);
    lh(a1, a2, 10);
    lh(v0, a2, 4);
    lh(v1, a2, 6);
    mult(v0, v0, a0);
    lhu(a0, a2, 8);
    mult(v1, v1, a1);
    v0 = addu(v0, v1);
    v0 = sra(v0, 12);
    a1 = addu(v0, a3);
    v0 = slti(a1, 32767);
    v1 = slti(a1, -32768);
    if (v0 == 0) {
        // 0x00543bd0
        charge(ctx, 1);
        v1 = 32767;
    } else {
        // 0x00543bbc
        charge(ctx, 5);
        v0 = si(-32768);
        if (v1 == 0) v0 = a1;
        v0 = sll(v0, 16);
        v1 = sra(v0, 16);
    }
    // 0x00543bd4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    sh(a0, a2, 10);
    v0 = v1;
    sh(v1, a2, 8);
}

// 0x00543BF0 sub_543BF0 -- 156 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADX encoder: take a predictor record and the first free 144-byte channel record of the 16 at 0x7922B8; store a0 at
// +20 and the predictor at +136, mark it used.
void sub_543BF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543bf0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x543BFCu, gen::fn_sub_543AA8_00543aa8);
    t0 = v0;
    v1 = 0x790000;
    if (t0 != 0) {
        // 0x00543c10
        charge(ctx, 4);
        a0 = addiu(v1, 8888);
        lb(v0, a0, 0);
        a3 = 0;
        if (v0 == 0) {
            // 0x00543c58
            charge(ctx, 1);
            v1 = 1;
        L_00543c5c:
            charge(ctx, 1);
            sw(s0, a0, 20);
        } else {
            // 0x00543c20
            charge(ctx, 2);
            a2 = a0;
            a1 = a0;
            for (;;) {
                // 0x00543c28
                charge(ctx, 5);
                a3 = addiu(a3, 1);
                a2 = addiu(a2, 144);
                v1 = slti(a3, 16);
                a1 = addiu(a1, 144);
                if (v1 == 0) {
                    goto L_00543c5c;
                }
                // 0x00543c3c
                charge(ctx, 4);
                lb(v0, a2, 0);
                a0 = a1;
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00543c4c
            charge(ctx, 2);
            sw(s0, a0, 20);
        }
        // 0x00543c60
        charge(ctx, 2);
        sw(t0, a0, 136);
        if (v1 == 0) {
            // 0x00543c78
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x00543c68
            charge(ctx, 4);
            v1 = 1;
            v0 = a0;
            sb(v1, a0, 0);
        }
    }
    // 0x00543c7c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00543C90 sub_543C90 -- 52 bytes; frame 0x10: ra sp+0x0
// ADX encoder: release a 144-byte channel record (clear it).
void sub_543C90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543c90
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    if (v0 == 0) {
        // 0x00543cb8
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00543ca0
    charge(ctx, 6);
    ld(ra, sp, 0x0);
    a1 = 0;
    a2 = 144;
    sb(zero, v0, 0);
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x00543CC8 sub_543CC8 -- 12 bytes; leaf frame (no stack)
// Channel record: store the coefficients a1 / a2 to +4 / +6.
void sub_543CC8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00543cc8
    enter(ctx, 3);  // entry check point + this block's cycles
    sh(a2, a0, 6);
    sh(a1, a0, 4);
}

// 0x00543CD8 sub_543CD8 -- 88 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// Channel record: derive the two predictor coefficients from a1 / a2 (sub_539858) and store them to the record and its
// predictor.
void sub_543CD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543cd8
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = sll(a1, 16);
    sd(s0, sp, 0x10);
    s0 = a0;
    a3 = addiu(sp, 0x2);
    a1 = a2;
    a0 = sra(v0, 16);
    sd(ra, sp, 0x18);
    a2 = sp;
    jal(ctx, 0x543CF8u, gen::fn_sub_539858_00539858);
    lh(a1, sp, 0x0);
    a0 = s0;
    link(ctx, 0x543D08u);  // $ra first: the delay slot below depends on it
    lh(a2, sp, 0x2);
    call(ctx, gen::fn_sub_543CC8_00543cc8);
    lw(a0, s0, 136);
    lh(a1, sp, 0x0);
    link(ctx, 0x543D18u);  // $ra first: the delay slot below depends on it
    lh(a2, sp, 0x2);
    call(ctx, gen::fn_sub_543B40_00543b40);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00543D30 sub_543D30 -- 12 bytes; leaf frame (no stack)
// Channel record: store the history a1 / a2 to +8 / +10.
void sub_543D30(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00543d30
    enter(ctx, 3);  // entry check point + this block's cycles
    sh(a2, a0, 10);
    sh(a1, a0, 8);
}

// 0x00543D40 sub_543D40 -- 228 bytes; leaf frame (no stack)
// Channel record: residual of sample a2 against the prediction, saturated, stored as entry a1 of the block (+24);
// tracks the block's largest magnitude (+120). Entry 0 clears the block first.
void sub_543D40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00543d40
    enter(ctx, 4);  // entry check point + this block's cycles
    a2 = sll(a2, 16);
    t0 = a0;
    t1 = sra(a2, 16);
    if (a1 == 0) {
        // 0x00543d50
        charge(ctx, 4);
        lw(v1, t0, 20);
        v0 = slt(a1, v1);
        if (v0 == 0) {
            sw(zero, t0, 120);
        } else {
            // 0x00543d60
            charge(ctx, 2);
            v0 = addiu(t0, 24);
            for (;;) {
                // 0x00543d68
                charge(ctx, 7);
                v1 = addiu(v1, -1);
                sh(zero, v0, 0);
                v0 = addiu(v0, 2);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00543d84
            charge(ctx, 1);
            sw(zero, t0, 120);
        }
    }
    // 0x00543d88
    charge(ctx, 2);
    if (t0 != 0) {
        // 0x00543d90
        charge(ctx, 16);
        lh(v0, t0, 4);
        a0 = sll(a1, 1);
        lh(a3, t0, 8);
        a1 = 32767;
        lh(a2, t0, 10);
        a0 = addu(a0, t0);
        lh(v1, t0, 6);
        mult(v0, v0, a3);
        mult(v1, v1, a2);
        v0 = sra(v0, 12);
        v0 = subu(t1, v0);
        v1 = sra(v1, 12);
        a2 = subu(v0, v1);
        a1 = slt(a1, a2);
        a0 = addiu(a0, 24);
        if (a1 != 0) {
            // 0x00543de8
            charge(ctx, 1);
            a1 = 32767;
        } else {
            // 0x00543dd0
            charge(ctx, 5);
            v0 = si(-32768);
            v1 = slti(a2, -32768);
            a1 = v0;
            if (v1 == 0) a1 = a2;
        }
        // 0x00543dec
        charge(ctx, 5);
        v0 = sll(a1, 16);
        lw(v1, t0, 120);
        v0 = sra(v0, 16);
        if (i64(v0) < 0) {
            v0 = subu(0, v0);
        }
        // 0x00543e00
        charge(ctx, 3);
        v1 = slt(v1, v0);
        sh(a1, a0, 0);
        if (v1 != 0) {
            // 0x00543e0c
            charge(ctx, 1);
            sw(v0, t0, 120);
        }
        // 0x00543e10
        charge(ctx, 3);
        lhu(v0, t0, 8);
        sh(t1, t0, 8);
        sh(v0, t0, 10);
    }
    // 0x00543e1c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00543E28 sub_543E28 -- 148 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Channel record: the block scale ((max - 1) / 7 + 1, clamped to 1 .. 0x790A2C) to +124 and its reciprocal (double,
// soft-float) to +128.
void sub_543E28(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543e28
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 7;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (a1 == 0) {
        brk(ctx, 0x543E40u, 0x7u);
    }
    // 0x00543e44
    charge(ctx, 15);
    a0 = 0x790000;
    t0 = 1;
    lw(a3, s0, 120);
    lw(v1, a0, 2604);  // 0x790A2C
    v0 = addiu(a3, -1);
    a0 = a3;
    div(v0, a1);
    mflo(v0);
    v0 = addiu(v0, 1);
    a1 = slt(v0, v1);
    if (a1 != 0) v1 = v0;
    a2 = slti(v1, 1);
    if (a2 != 0) v1 = t0;
    sh(v1, s0, 124);
    if (a3 != 0) {
        // 0x00543e90
        charge(ctx, 6);
        jal(ctx, 0x543E90u, gen::fn_litodp_00531720);
        at = 0x7C0000;
        ld(a0, at, 9904);  // 0x7C26B0
        a1 = v0;
        jal(ctx, 0x543EA0u, gen::fn_dpdiv_00531480);
    } else {
        // 0x00543e80
        charge(ctx, 3);
        at = 0x7C0000;
        ld(v0, at, 9896);  // 0x7C26A8
    }
    // 0x00543ea8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sd(v0, s0, 128);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00543EC0 sub_543EC0 -- 28 bytes; leaf frame (no stack)
// Channel record: residual entry a1 (0 for a null record).
void sub_543EC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00543ec0
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = sll(a1, 1);
    v0 = 0;
    a1 = addu(a1, a0);
    if (a0 != 0) {
        // 0x00543ed0
        charge(ctx, 1);
        lh(v0, a1, 24);
    }
    // 0x00543ed4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00543EF8 sub_543EF8 -- 12 bytes; leaf frame (no stack)
// Channel record: store the 4-bit code a2 as byte a1 of +88.
void sub_543EF8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00543ef8
    enter(ctx, 3);  // entry check point + this block's cycles
    a0 = addu(a1, a0);
    sb(a2, a0, 88);
}

// 0x00543F08 sub_543F08 -- 364 bytes; frame 0x70: s1 sp+0x28, s2 sp+0x30, s4 sp+0x40, s7 sp+0x58, fp sp+0x60, s0 sp+0x20, s3 sp+0x38, s5 sp+0x48, s6 sp+0x50, ra sp+0x68
// ADX encoder: read a2 samples per channel from each input stream joint (+4..) into the caller's buffers (a3), checking
// first that each holds enough data (jalr through the vtables).
void sub_543F08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00543f08
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s1, sp, 0x28);
    s1 = 0;
    sd(s2, sp, 0x30);
    s2 = a2;
    sd(s4, sp, 0x40);
    s4 = 0;
    sd(s7, sp, 0x58);
    s7 = a0;
    sd(fp, sp, 0x60);
    fp = addiu(s7, 0x4);
    sd(s0, sp, 0x20);
    sd(s3, sp, 0x38);
    sd(s5, sp, 0x48);
    sd(s6, sp, 0x50);
    sd(ra, sp, 0x68);
    lw(v1, s7, 88);
    sw(a3, sp, 0x10);
    if (i64(v1) > 0) {
        // 0x00543f54
        charge(ctx, 3);
        s0 = fp;
        lw(a0, s0, 0);
        for (;;) {
            // 0x00543f60
            charge(ctx, 9);
            s0 = addiu(s0, 4);
            lw(v1, a0, 0);
            lw(v0, v1, 36);
            a1 = 1;
            jalr(ctx, 0x543F6Cu, v0.u());
            s1 = srl(v0, 1);
            v1 = slt(s1, s2);
            v0 = 0;
            if (v1 != 0) {
                break;
            }
            // 0x00543f84
            charge(ctx, 5);
            lw(v1, s7, 88);
            s4 = addiu(s4, 1);
            v0 = slt(s4, v1);
            if (v0 == 0) {
                goto L_00543f98;
            }
            lw(a0, s0, 0);
            backedge(ctx);
        }
        // 0x00544044 (the shared epilogue, written out on this path)
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
L_00543f98:
    charge(ctx, 2);
    s4 = 0;
    if (i64(v1) > 0) {
        // 0x00543fa0
        charge(ctx, 2);
        s5 = 0;
        for (;;) {
            // 0x00543fa8
            charge(ctx, 2);
            s1 = 0;
            if (i64(s2) > 0) {
                // 0x00543fb0
                charge(ctx, 6);
                lw(v0, sp, 0x10);
                s6 = sll(s2, 1);
                s0 = addu(s5, fp);
                s3 = addu(s5, v0);
                lw(a0, s0, 0);
                for (;;) {
                    // 0x00543fc8
                    charge(ctx, 25);
                    a3 = sp;
                    a1 = 1;
                    lw(v1, a0, 0);
                    lw(v0, v1, 24);
                    a2 = s6;
                    jalr(ctx, 0x543FD8u, v0.u());
                    lw(v1, s3, 0);
                    lw(a1, sp, 0x0);
                    a0 = sll(s1, 1);
                    lw(a2, sp, 0x4);
                    a0 = addu(a0, v1);
                    jal(ctx, 0x543FF0u, gen::fn_memcpy_00521250);
                    lw(a0, s0, 0);
                    lw(v0, sp, 0x4);
                    a1 = 0;
                    lw(a3, a0, 0);
                    a2 = sp;
                    v0 = sll(v0, 15);
                    v0 = sra(v0, 16);
                    lw(v1, a3, 32);
                    s1 = addu(s1, v0);
                    jalr(ctx, 0x544018u, v1.u());
                    v0 = slt(s1, s2);
                    if (v0 == 0) {
                        break;
                    }
                    lw(a0, s0, 0);
                    backedge(ctx);
                }
                // 0x0054402c
                charge(ctx, 1);
                lw(v1, s7, 88);
            }
            // 0x00544030
            charge(ctx, 4);
            s4 = addiu(s4, 1);
            v0 = slt(s4, v1);
            s5 = addiu(s5, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00544040
    charge(ctx, 1);
    v0 = s1;
    // 0x00544044 (the shared epilogue, written out on this path)
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
}

// 0x00544078 sub_544078 -- 608 bytes; frame 0x60: s4 sp+0x30, s2 sp+0x20, s3 sp+0x28, s6 sp+0x40, s7 sp+0x48, fp sp+0x50, s0 sp+0x10, s1 sp+0x18, s5 sp+0x38, ra sp+0x58
// ADX encoder: code one channel's block: residuals, scale, then per sample the 4-bit code (rounded divide by 4681,
// clamped -8..7) and the decoder-side reconstruction.
void sub_544078(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00544078
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s4, sp, 0x30);
    s4 = a1;
    sd(s2, sp, 0x20);
    s2 = 0;
    sd(s3, sp, 0x28);
    s3 = a0;
    sd(s6, sp, 0x40);
    s6 = addiu(s3, 12);
    sd(s7, sp, 0x48);
    s7 = addiu(s3, 8);
    sd(fp, sp, 0x50);
    fp = sll(s4, 1);
    sd(s0, sp, 0x10);
    v1 = sll(s4, 2);
    sd(s1, sp, 0x18);
    v1 = addu(v1, s3);
    sd(s5, sp, 0x38);
    v0 = addiu(fp, 0x80);
    sd(ra, sp, 0x58);
    a0 = addu(s6, v0);
    v0 = addu(s7, v0);
    lw(s1, v1, 128);
    lh(a2, a0, 0);
    lh(a1, v0, 0);
    a0 = s1;
    lw(v0, s1, 136);
    link(ctx, 0x5440E4u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x4);
    call(ctx, gen::fn_sub_543D30_00543d30);
    lw(v0, s3, 68);
    a0 = s1;
    if (i64(v0) > 0) {
        // 0x005440f8
        charge(ctx, 4);
        s5 = sll(s4, 6);
        v0 = addu(s5, s3);
        s0 = addiu(v0, 144);
        lh(a2, s0, 0);
        for (;;) {
            // 0x00544108
            charge(ctx, 9);
            s0 = addiu(s0, 2);
            a1 = s2;
            s2 = addiu(s2, 1);
            a0 = s1;
            jal(ctx, 0x544114u, gen::fn_sub_543D40_00543d40);
            lw(v0, s3, 68);
            v0 = slt(s2, v0);
            if (v0 == 0) {
                break;
            }
            lh(a2, s0, 0);
            backedge(ctx);
        }
        // 0x0054412c
        charge(ctx, 1);
        a0 = s1;
    }
    // 0x00544130
    charge(ctx, 12);
    s2 = 0;
    jal(ctx, 0x544130u, gen::fn_sub_543E28_00543e28);
    v0 = addiu(fp, 0x80);
    v1 = addu(s6, v0);
    v0 = addu(s7, v0);
    lh(a1, v0, 0);
    lh(a2, v1, 0);
    link(ctx, 0x54414Cu);  // $ra first: the delay slot below depends on it
    lw(a0, s1, 136);
    call(ctx, gen::fn_sub_543B50_00543b50);
    lw(v0, s3, 68);
    ld(s0, sp, 0x10);
    if (i64(v0) > 0) {
        // 0x00544160
        charge(ctx, 6);
        s5 = sll(s4, 6);
        s4 = 4681;
        fp = addiu(sp, 0x2);
        s7 = 32767;
        s6 = si(-32768);
        lw(a0, sp, 0x4);
        for (;;) {
            // 0x00544178
            charge(ctx, 29);
            v0 = addu(s5, s3);
            v1 = sll(s2, 1);
            a1 = sp;
            v1 = addu(v1, v0);
            a2 = fp;
            link(ctx, 0x54418Cu);  // $ra first: the delay slot below depends on it
            lh(s0, v1, 144);
            call(ctx, gen::fn_sub_543B60_00543b60);
            lh(a1, sp, 0x0);
            a0 = s1;
            link(ctx, 0x54419Cu);  // $ra first: the delay slot below depends on it
            lh(a2, sp, 0x2);
            call(ctx, gen::fn_sub_543D30_00543d30);
            a0 = s1;
            a2 = s0;
            a1 = s2;
            jal(ctx, 0x5441ACu, gen::fn_sub_543D40_00543d40);
            a0 = s1;
            a1 = s2;
            jal(ctx, 0x5441B8u, gen::fn_sub_543EC0_00543ec0);
            a0 = v0;
            jal(ctx, 0x5441C0u, gen::fn_litodp_00531720);
            ld(a1, s1, 128);
            a0 = v0;
            jal(ctx, 0x5441CCu, gen::fn_dpmul_00531230);
            a0 = v0;
            jal(ctx, 0x5441D4u, gen::fn_dptoli_005317d0);
            s0 = v0;
            v0 = slt(s7, s0);
            if (v0 != 0) {
                v0 = 32767;
            } else {
                // 0x005441ec
                charge(ctx, 5);
                v1 = slti(s0, -32768);
                v0 = s6;
                if (v1 == 0) v0 = s0;
                v0 = sll(v0, 16);
                v0 = sra(v0, 16);
            }
            // 0x00544200
            charge(ctx, 3);
            s0 = v0;
            if (i64(s0) >= 0) {
                v0 = addiu(s0, 2340);
            } else {
                // 0x0054420c
                charge(ctx, 1);
                v0 = addiu(s0, -2340);
            }
            // 0x00544210
            charge(ctx, 2);
            if (s4 == 0) {
                brk(ctx, 0x544214u, 0x7u);
            }
            // 0x00544218
            charge(ctx, 6);
            div(v0, s4);
            mflo(v0);
            s0 = v0;
            v0 = slti(s0, 7);
            v1 = 7;
            if (v0 != 0) {
                // 0x00544230
                charge(ctx, 4);
                v1 = s0;
                v0 = slti(v1, -8);
                if (v0 != 0) {
                    v1 = si(-8);
                    goto L_00544248;
                }
                // 0x00544240
                charge(ctx, 2);
                s0 = v1;
                goto L_0054424c;
            }
        L_00544248:
            charge(ctx, 1);
            s0 = v1;
        L_0054424c:
            charge(ctx, 10);
            a0 = s1;
            a2 = sll(s0, 24);
            a1 = s2;
            a2 = sra(a2, 24);
            jal(ctx, 0x544258u, gen::fn_sub_543EF8_00543ef8);
            lh(v0, s1, 124);
            mult(s0, s0, v0);
            v1 = slt(s7, s0);
            if (v1 != 0) {
                a1 = 32767;
            } else {
                // 0x00544274
                charge(ctx, 5);
                v1 = slti(s0, -32768);
                v0 = s6;
                if (v1 == 0) v0 = s0;
                v0 = sll(v0, 16);
                a1 = sra(v0, 16);
            }
            // 0x00544288
            charge(ctx, 7);
            lw(a0, s1, 136);
            s2 = addiu(s2, 1);
            jal(ctx, 0x54428Cu, gen::fn_sub_543B78_00543b78);
            lw(v1, s3, 68);
            v1 = slt(s2, v1);
            lw(a0, sp, 0x4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005442a4
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    }
    // 0x005442a8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    v0 = 0;
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
}

// 0x005442D8 sub_5442D8 -- 644 bytes; frame 0x70: s3 sp+0x38, s4 sp+0x40, s6 sp+0x50, s7 sp+0x58, fp sp+0x60, s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, s5 sp+0x48, ra sp+0x68
// ADX encoder: requantise a channel's block and pack the codes (bits per sample +84) into its 16-byte frame at +680.
void sub_5442D8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005442d8
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    a2 = 8;
    sd(s3, sp, 0x38);
    s3 = a0;
    sd(s4, sp, 0x40);
    s4 = 0;
    sd(s6, sp, 0x50);
    a0 = sll(a1, 2);
    sd(s7, sp, 0x58);
    v1 = sll(a1, 6);
    sd(fp, sp, 0x60);
    fp = si(-0x1);
    sd(s0, sp, 0x20);
    a1 = sll(a1, 4);
    sd(s1, sp, 0x28);
    v1 = addu(s3, v1);
    sd(s2, sp, 0x30);
    a1 = addu(s3, a1);
    sd(s5, sp, 0x48);
    a1 = addiu(a1, 680);
    sd(ra, sp, 0x68);
    a0 = addu(a0, s3);
    lw(v0, s3, 84);
    div(a2, v0);
    a2 = addiu(v1, 528);
    mflo(a3);
    sw(a3, sp, 0x14);
    if (v0 == 0) {
        brk(ctx, 0x544348u, 0x7u);
    }
    // 0x0054434c
    charge(ctx, 11);
    lw(v0, s3, 68);
    a3 = addiu(v1, 272);
    sw(a2, sp, 0xC);
    v1 = addiu(v1, 400);
    sw(a1, sp, 0x10);
    lw(s6, sp, 0x14);
    lw(s7, a0, 128);
    sw(zero, sp, 0x0);
    sw(a3, sp, 0x4);
    sw(v1, sp, 0x8);
    if (i64(v0) > 0) {
        // 0x00544378
        charge(ctx, 2);
        s5 = 4681;
        a1 = s4;
        for (;;) {
            // 0x00544380
            charge(ctx, 20);
            a0 = s7;
            jal(ctx, 0x544380u, gen::fn_sub_543EC0_00543ec0);
            s1 = sll(s4, 1);
            lw(a0, sp, 0x4);
            v1 = addu(s1, a0);
            a0 = sll(v0, 16);
            sh(v0, v1, 0);
            a0 = sra(a0, 16);
            jal(ctx, 0x54439Cu, gen::fn_litodp_00531720);
            ld(s2, s7, 128);
            a0 = v0;
            a1 = s2;
            jal(ctx, 0x5443ACu, gen::fn_dpmul_00531230);
            a0 = v0;
            jal(ctx, 0x5443B4u, gen::fn_dptoli_005317d0);
            a1 = 32767;
            a0 = v0;
            v0 = slt(a1, a0);
            v1 = 32767;
            if (v0 == 0) {
                // 0x005443d0
                charge(ctx, 4);
                v1 = a0;
                v0 = slti(v1, -32768);
                if (v0 != 0) {
                    v1 = si(-32768);
                    goto L_005443e8;
                }
                // 0x005443e0
                charge(ctx, 2);
                lw(a2, sp, 0x8);
                goto L_005443ec;
            }
        L_005443e8:
            charge(ctx, 1);
            lw(a2, sp, 0x8);
        L_005443ec:
            charge(ctx, 5);
            a0 = v1;
            v1 = sll(a0, 16);
            v0 = addu(s1, a2);
            sh(a0, v0, 0);
            if (i64(v1) >= 0) {
                // 0x00544408
                charge(ctx, 1);
                v0 = addiu(a0, 2340);
            } else {
                // 0x00544400
                charge(ctx, 2);
                v0 = addiu(a0, -2340);
            }
            // 0x0054440c
            charge(ctx, 2);
            if (s5 == 0) {
                brk(ctx, 0x544410u, 0x7u);
            }
            // 0x00544414
            charge(ctx, 6);
            div(v0, s5);
            mflo(v0);
            a0 = v0;
            v0 = slti(a0, 7);
            s0 = 7;
            if (v0 != 0) {
                // 0x0054442c
                charge(ctx, 4);
                s0 = a0;
                v0 = slti(s0, -8);
                if (v0 != 0) {
                    s0 = si(-8);
                    goto L_00544448;
                }
                // 0x0054443c
                charge(ctx, 2);
                lh(a0, s7, 124);
                goto L_0054444c;
            }
        L_00544448:
            charge(ctx, 1);
            lh(a0, s7, 124);
        L_0054444c:
            charge(ctx, 12);
            mult(a0, s0, a0);
            jal(ctx, 0x54444Cu, gen::fn_litodp_00531720);
            a1 = s2;
            a0 = v0;
            jal(ctx, 0x544458u, gen::fn_dpmul_00531230);
            a0 = v0;
            jal(ctx, 0x544460u, gen::fn_dptoli_005317d0);
            v1 = 32767;
            a0 = v0;
            v0 = slt(v1, a0);
            if (v0 != 0) {
                a0 = 32767;
            } else {
                // 0x0054447c
                charge(ctx, 3);
                v0 = slti(a0, -32768);
                if (v0 != 0) {
                    a0 = si(-32768);
                    goto L_00544490;
                }
                // 0x00544488
                charge(ctx, 2);
                div(s4, s6);
                goto L_00544494;
            }
        L_00544490:
            charge(ctx, 1);
            div(s4, s6);
        L_00544494:
            charge(ctx, 5);
            lw(a1, sp, 0xC);
            v0 = addu(s1, a1);
            sh(a0, v0, 0);
            if (s6 == 0) {
                brk(ctx, 0x5444A4u, 0x7u);
            }
            // 0x005444a8
            charge(ctx, 3);
            mfhi(v1);
            cc = v1 != 0;  // the condition, before the delay slot changes it
            lw(v1, sp, 0x10);
            if (cc) {
                // 0x005444d0
                charge(ctx, 1);
                a3 = addu(v1, fp);
            } else {
                // 0x005444b4
                charge(ctx, 7);
                lw(v0, sp, 0x10);
                fp = addiu(fp, 0x1);
                a2 = 1;
                a3 = addu(v0, fp);
                sw(a2, sp, 0x0);
                sb(zero, a3, 0);
            }
            // 0x005444d4
            charge(ctx, 22);
            lw(v0, sp, 0x0);
            v1 = 8;
            lw(a2, sp, 0x14);
            s4 = addiu(s4, 1);
            lw(a1, s3, 84);
            a0 = subu(a2, v0);
            lbu(a2, a3, 0);
            v1 = subu(v1, a1);
            mult(a0, a0, a1);
            v0 = sllv(s0, v1);
            lw(a1, sp, 0x0);
            v0 = v0 & 0xFF;
            s0 = srav(v0, v1);
            a1 = addiu(a1, 1);
            a0 = sllv(s0, a0);
            sw(a1, sp, 0x0);
            a2 = a2 | a0;
            sb(a2, a3, 0);
            lw(v0, s3, 68);
            v0 = slt(s4, v0);
            a1 = s4;
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0054452c (the shared epilogue, written out on this path)
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
}

// 0x00544560 sub_544560 -- 448 bytes; frame 0x70: s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, s3 sp+0x38, s4 sp+0x40, s5 sp+0x48, s6 sp+0x50, s7 sp+0x58, fp sp+0x60, ra sp+0x68
// ADX encoder: read one block of input, zero-pad a short tail, then code and pack every channel; returns the samples
// taken.
void sub_544560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00544560
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s0, sp, 0x20);
    s0 = a0;
    sd(s1, sp, 0x28);
    t0 = addiu(s0, 144);
    sd(s2, sp, 0x30);
    t1 = addiu(s0, 208);
    sd(s3, sp, 0x38);
    a3 = sp;
    sd(s4, sp, 0x40);
    sd(s5, sp, 0x48);
    sd(s6, sp, 0x50);
    sd(s7, sp, 0x58);
    sd(fp, sp, 0x60);
    sd(ra, sp, 0x68);
    sw(t0, sp, 0x0);
    lw(v0, s0, 48);
    lw(v1, s0, 60);
    lw(a2, s0, 68);
    a1 = v0;
    s1 = subu(v1, v0);
    sw(t1, sp, 0x4);
    v0 = slt(a2, s1);
    if (v0 != 0) s1 = a2;
    a2 = s1;
    jal(ctx, 0x5445C0u, gen::fn_sub_543F08_00543f08);
    if (v0 == 0) {
        ld(s0, sp, 0x20);
    } else {
        // 0x005445d0
        charge(ctx, 4);
        lw(a2, s0, 68);
        v0 = slt(s1, a2);
        lw(v1, s0, 88);
        if (v0 != 0) {
            // 0x005445e0
            charge(ctx, 2);
            s3 = 0;
            if (i64(v1) <= 0) {
                goto L_00544638;
            }
            // 0x005445e8
            charge(ctx, 4);
            s4 = sll(s1, 1);
            s2 = sp;
            lw(v0, s2, 0);
            for (;;) {
                // 0x005445f8
                charge(ctx, 3);
                s2 = addiu(s2, 4);
                a0 = addu(s4, v0);
                if (v0 != 0) {
                    // 0x00544604
                    charge(ctx, 6);
                    a2 = subu(a2, s1);
                    a1 = 0;
                    a2 = sll(a2, 1);
                    jal(ctx, 0x54460Cu, gen::fn_memset_00521408);
                    lw(a2, s0, 68);
                    lw(v1, s0, 88);
                }
                // 0x0054461c
                charge(ctx, 4);
                s3 = addiu(s3, 1);
                v0 = slt(s3, v1);
                if (v0 == 0) {
                    break;
                }
                lw(v0, s2, 0);
                backedge(ctx);
            }
            // 0x0054462c
            charge(ctx, 2);
            lw(v0, s0, 48);
            goto L_0054463c;
        }
    L_00544638:
        charge(ctx, 1);
        lw(v0, s0, 48);
    L_0054463c:
        charge(ctx, 4);
        s5 = 0;
        v0 = addu(v0, a2);
        sw(v0, s0, 48);
        if (i64(v1) > 0) {
            // 0x0054464c
            charge(ctx, 9);
            fp = addiu(sp, 0x12);
            s7 = addiu(s0, 12);
            s6 = addiu(s0, 8);
            s4 = addiu(s0, 664);
            s3 = addiu(s0, 656);
            s1 = addiu(s0, 128);
            s2 = 128;
            a1 = s5;
            for (;;) {
                // 0x00544670
                charge(ctx, 30);
                a0 = s0;
                jal(ctx, 0x544670u, gen::fn_sub_544078_00544078);
                lw(v1, s1, 0);
                v0 = addiu(sp, 0x10);
                a2 = fp;
                ld(a3, v1, 128);
                a1 = v0;
                lhu(v0, v1, 124);
                s1 = addiu(s1, 4);
                lw(a0, v1, 136);
                sh(v0, s3, 0);
                s3 = addiu(s3, 2);
                sd(a3, s4, 0);
                s4 = addiu(s4, 8);
                jal(ctx, 0x5446A4u, gen::fn_sub_543B60_00543b60);
                a0 = addu(s6, s2);
                lhu(v0, sp, 0x10);
                a2 = addu(s7, s2);
                lhu(v1, sp, 0x12);
                a1 = s5;
                sh(v0, a0, 0);
                a0 = s0;
                sh(v1, a2, 0);
                s5 = addiu(s5, 1);
                s2 = addiu(s2, 2);
                jal(ctx, 0x5446D0u, gen::fn_sub_5442D8_005442d8);
                lw(v0, s0, 88);
                v0 = slt(s5, v0);
                a1 = s5;
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x005446e8
            charge(ctx, 1);
            lw(a2, s0, 68);
        }
        // 0x005446ec
        charge(ctx, 2);
        v0 = a2;
        ld(s0, sp, 0x20);
    }
    // 0x005446f4 (the shared epilogue, written out on this path)
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

// 0x00544720 sub_544720 -- 304 bytes; frame 0x50: s2 sp+0x20, s5 sp+0x38, s6 sp+0x40, s0 sp+0x10, s1 sp+0x18, s3 sp+0x28, s4 sp+0x30, ra sp+0x48
// ADX encoder: write each channel's frame: the (XOR-ciphered) scale big-endian, then 16 data bytes, advancing the
// cipher state (+720 = (+720 * +722 + +724) & 0x7FFF).
void sub_544720(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00544720
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s5, sp, 0x38);
    s5 = 0;
    sd(s6, sp, 0x40);
    s6 = 0;
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    sd(s3, sp, 0x28);
    sd(s4, sp, 0x30);
    sd(ra, sp, 0x48);
    lw(v0, s2, 88);
    lw(s4, s2, 12);
    if (i64(v0) > 0) {
        // 0x0054475c
        charge(ctx, 3);
        s1 = addiu(s2, 680);
        s3 = addiu(s2, 656);
        lhu(a0, s2, 720);
        for (;;) {
        L_00544768:
            charge(ctx, 14);
            lhu(a1, s2, 722);
            lhu(v1, s3, 0);
            s3 = addiu(s3, 2);
            mult(a1, a0, a1);
            lhu(v0, s2, 724);
            v1 = addiu(v1, -1);
            lw(a2, s1, 0);
            a0 = a0 ^ v1;
            a0 = sll(a0, 16);
            v0 = addu(v0, a1);
            s0 = sra(a0, 16);
            v0 = v0 & 0x7FFF;
            sh(v0, s2, 720);
            if (a2 == 0) {
                // 0x005447a0
                charge(ctx, 3);
                lw(v0, s1, 4);
                a0 = sp;
                if (v0 != 0) {
                L_005447c4:
                    charge(ctx, 1);
                    a1 = 1;
                } else {
                    // 0x005447ac
                    charge(ctx, 3);
                    lw(v0, s1, 8);
                    a1 = 1;
                    if (v0 == 0) {
                        // 0x005447b8
                        charge(ctx, 2);
                        lw(v0, s1, 12);
                        if (v0 == 0) s0 = 0;
                        goto L_005447c0;
                    }
                }
                goto L_005447c8;
            }
        L_005447c0:
            charge(ctx, 1);
            a0 = sp;
            goto L_005447c4;
        }
    }
    // 0x00544824 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = s6;
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
    return;
L_005447c8:
    charge(ctx, 23);
    a2 = 1;
    a3 = s4;
    v0 = sra(s0, 8);
    s5 = addiu(s5, 1);
    link(ctx, 0x5447D8u);  // $ra first: the delay slot below depends on it
    sb(v0, sp, 0x0);
    call(ctx, gen::fn_sub_5438C0_005438c0);
    a0 = sp;
    a1 = 1;
    a2 = 1;
    a3 = s4;
    link(ctx, 0x5447F0u);  // $ra first: the delay slot below depends on it
    sb(s0, sp, 0x0);
    call(ctx, gen::fn_sub_5438C0_005438c0);
    a0 = s1;
    s1 = addiu(s1, 16);
    a1 = 1;
    a2 = 16;
    a3 = s4;
    s6 = addiu(s6, 18);
    jal(ctx, 0x54480Cu, gen::fn_sub_5438C0_005438c0);
    lw(v1, s2, 88);
    v1 = slt(s5, v1);
    if (v1 != 0) {
        lhu(a0, s2, 720);
        backedge(ctx);
        goto L_00544768;
    }
    // 0x00544824 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = s6;
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

// 0x00544850 sub_544850 -- 176 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s1 sp+0x8, ra sp+0x20
// ADX encoder: encode frames while the output stream joint has room for one per channel and input remains; returns the
// bytes written.
void sub_544850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00544850
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = 18;
    sd(s3, sp, 0x18);
    s3 = 0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x20);
    lw(s1, s0, 12);
    for (;;) {
        // 0x00544878
        charge(ctx, 9);
        lw(v1, s1, 0);
        a0 = s1;
        lw(v0, v1, 36);
        a1 = 0;
        jalr(ctx, 0x544884u, v0.u());
        a0 = s0;
        div(v0, s2);
        if (s2 == 0) {
            brk(ctx, 0x544898u, 0x7u);
        }
        // 0x0054489c
        charge(ctx, 6);
        lw(v1, s0, 88);
        mflo(v0);
        div(v0, v1);
        mflo(v0);
        cc = i64(v0) <= 0;  // the condition, before the delay slot changes it
        v0 = s3;
        if (cc) {
            // 0x005448e4 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            return;
        }
        // 0x005448b4
        charge(ctx, 4);
        jal(ctx, 0x5448B4u, gen::fn_sub_544560_00544560);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = s3;
        if (cc) {
            // 0x005448e4 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            return;
        }
        // 0x005448c4
        charge(ctx, 7);
        a0 = s0;
        jal(ctx, 0x5448C4u, gen::fn_sub_544720_00544720);
        lw(v1, s0, 48);
        lw(a0, s0, 60);
        v1 = slt(v1, a0);
        s3 = addu(s3, v0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005448e0
    charge(ctx, 1);
    v0 = s3;
    // 0x005448e4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00545BF0 sub_545BF0 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: calls sub_564978 (lock).
void sub_545BF0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00545bf0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564978_00564978(ctx);  // tail call
}

// 0x00545C08 atan2l_2 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: calls sub_564990 (unlock). The symbol name atan2l_2 is the map's.
void atan2l_2(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00545c08
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564990_00564990(ctx);  // tail call
}

// 0x00545C20 cosl_2 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: calls sub_5655E8. The symbol name cosl_2 is the map's.
void cosl_2(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00545c20
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5655E8_005655e8(ctx);  // tail call
}

// 0x00545C38 coshl_2 -- 8 bytes; leaf frame (no stack)
// Empty (jr $ra / nop): the ADXSTM enter-critical hook. The symbol name coshl_2 is the map's.
void coshl_2(EEContext& ctx) {
    using namespace hg;
    // 0x00545c38
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00545C40 sub_545C40 -- 8 bytes; leaf frame (no stack)
// Empty (jr $ra / nop): the ADXSTM leave-critical hook.
void sub_545C40(EEContext& ctx) {
    using namespace hg;
    // 0x00545c40
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00545C78 sub_545C78 -- 72 bytes; frame 0x10: ra sp+0x0
// ADXSTM init: count it (0x792BB8); the first call clears the 3840-byte record pool at 0x792BD8. Returns 1.
void sub_545C78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00545c78
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 11192);  // &0x792BB8 ADXSTM init count
    a0 = 1;
    lw(v1, v0, 0);  // 0x792BB8 ADXSTM init count
    v1 = addiu(v1, 1);
    sw(v1, v0, 0);  // 0x792BB8 ADXSTM init count
    if (v1 == a0) {
        // 0x00545c9c
        charge(ctx, 5);
        a0 = 0x790000;
        a1 = 0;
        a0 = addiu(a0, 11224);  // &0x792BD8
        a2 = 3840;
        jal(ctx, 0x545CA8u, gen::fn_memset_00521408);
    }
    // 0x00545cb0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// 0x00545D18 sub_545D18 -- 264 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// ADXSTM: initialise stream record a0 under the lock: file handle a1, start sector a2, byte size a3 (sectors rounded
// up), max request 512 sectors, end 0xFFFFF, the stream joint a4 and its buffer size (GetNumData of both lines, jalr);
// marks it used.
void sub_545D18(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00545d18
    enter(ctx, 41);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a3;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a0;
    sd(s4, sp, 0x20);
    s4 = t0;
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x30);
    s5 = 1;
    jal(ctx, 0x545D4Cu, gen::fn_sub_539818_00539818);
    a3 = addiu(s0, 2047);
    v0 = slti(s0, 0);
    v1 = s0;
    a2 = 0xF0000;
    if (v0 != 0) v1 = a3;
    a3 = 512;
    v1 = sra(v1, 11);
    a2 = a2 | 0xFFFF;
    v0 = sll(v1, 11);
    a0 = s4;
    v0 = subu(s0, v0);
    a1 = 0;
    v0 = slt(0, v0);
    sw(s1, s3, 8);
    v1 = addu(v1, v0);
    sw(s2, s3, 12);
    sw(a3, s3, 44);
    sw(a2, s3, 92);
    sw(v1, s3, 48);
    sb(s5, s3, 1);
    sb(zero, s3, 2);
    sw(s4, s3, 4);
    sw(s0, s3, 16);
    sw(v1, s3, 20);
    sw(zero, s3, 88);
    if (s4 != 0) {
        // 0x00545dbc
        charge(ctx, 14);
        lw(v1, s4, 0);
        lw(v0, v1, 36);
        jalr(ctx, 0x545DC4u, v0.u());
        lw(v1, s4, 0);
        s0 = v0;
        a0 = s4;
        lw(v0, v1, 36);
        a1 = 1;
        jalr(ctx, 0x545DDCu, v0.u());
        s0 = addu(s0, v0);
        sw(s0, s3, 28);
        sw(s0, s3, 64);
        sw(s0, s3, 24);
    }
    // 0x00545df4
    charge(ctx, 11);
    sb(s5, s3, 0);
    sb(zero, s3, 68);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
    gen::fn_sub_539830_00539830(ctx);  // tail call
}

// 0x00545E20 sub_545E20 -- 212 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXSTM: find a free record in the first pool range (0x792BBC, count 0x792BC0), initialise it and mark it as a small
// stream (+3 = 1).
void sub_545E20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00545e20
    enter(ctx, 12);  // entry check point + this block's cycles
    t5 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(t1, t5, 11200);  // 0x792BC0
    t2 = a1;
    sd(s0, sp, 0x0);
    s0 = 0;
    sd(ra, sp, 0x8);
    t4 = a0;
    t3 = a2;
    t0 = a3;
    a1 = 0;
    if (i64(t1) > 0) {
        // 0x00545e50
        charge(ctx, 12);
        v0 = 0x790000;
        a0 = 0x790000;
        a3 = addiu(v0, 11196);  // &0x792BBC
        a0 = addiu(a0, 11224);  // &0x792BD8
        lw(v1, a3, 0);  // 0x792BBC
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 5);
        s0 = addu(v0, a0);
        lb(v1, s0, 0);
        cc = v1 == 0;  // the condition, before the delay slot changes it
        lw(v1, t5, 11200);
        if (!cc) {
            // 0x00545e80
            charge(ctx, 2);
            a2 = t1;
            a1 = addiu(a1, 1);
            for (;;) {
                // 0x00545e88
                charge(ctx, 3);
                v0 = slt(a1, a2);
                lw(v1, t5, 11200);
                if (v0 == 0) {
                    break;
                }
                // 0x00545e94
                charge(ctx, 9);
                lw(v0, a3, 0);
                v0 = addu(v0, a1);
                v1 = sll(v0, 1);
                v1 = addu(v1, v0);
                v1 = sll(v1, 5);
                s0 = addu(v1, a0);
                lb(v0, s0, 0);
                if (v0 == 0) {
                    goto L_00545eb8;
                }
                a1 = addiu(a1, 1);
                backedge(ctx);
            }
        }
        goto L_00545ebc;
    }
L_00545eb8:
    charge(ctx, 1);
    lw(v1, t5, 11200);
L_00545ebc:
    charge(ctx, 2);
    v0 = 0;
    if (a1 != v1) {
        // 0x00545ec4
        charge(ctx, 8);
        a1 = t4;
        a2 = t2;
        a3 = t3;
        a0 = s0;
        jal(ctx, 0x545ED0u, gen::fn_sub_545D18_00545d18);
        v0 = 1;
        sb(v0, s0, 3);
        v0 = s0;
    }
    // 0x00545ee4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00545EF8 sub_545EF8 -- 208 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXSTM: as sub_545E20 in the second range (0x792BC4, count 0x792BC8), +3 = 0.
void sub_545EF8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00545ef8
    enter(ctx, 12);  // entry check point + this block's cycles
    t5 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(t1, t5, 11208);  // 0x792BC8
    t2 = a1;
    sd(s0, sp, 0x0);
    s0 = 0;
    sd(ra, sp, 0x8);
    t4 = a0;
    t3 = a2;
    t0 = a3;
    a1 = 0;
    if (i64(t1) > 0) {
        // 0x00545f28
        charge(ctx, 12);
        v0 = 0x790000;
        a0 = 0x790000;
        a3 = addiu(v0, 11204);  // &0x792BC4
        a0 = addiu(a0, 11224);  // &0x792BD8
        lw(v1, a3, 0);  // 0x792BC4
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 5);
        s0 = addu(v0, a0);
        lb(v1, s0, 0);
        cc = v1 == 0;  // the condition, before the delay slot changes it
        lw(v1, t5, 11208);
        if (!cc) {
            // 0x00545f58
            charge(ctx, 2);
            a2 = t1;
            a1 = addiu(a1, 1);
            for (;;) {
                // 0x00545f60
                charge(ctx, 3);
                v0 = slt(a1, a2);
                lw(v1, t5, 11208);
                if (v0 == 0) {
                    break;
                }
                // 0x00545f6c
                charge(ctx, 9);
                lw(v0, a3, 0);
                v0 = addu(v0, a1);
                v1 = sll(v0, 1);
                v1 = addu(v1, v0);
                v1 = sll(v1, 5);
                s0 = addu(v1, a0);
                lb(v0, s0, 0);
                if (v0 == 0) {
                    goto L_00545f90;
                }
                a1 = addiu(a1, 1);
                backedge(ctx);
            }
        }
        goto L_00545f94;
    }
L_00545f90:
    charge(ctx, 1);
    lw(v1, t5, 11208);
L_00545f94:
    charge(ctx, 2);
    v0 = 0;
    if (a1 != v1) {
        // 0x00545f9c
        charge(ctx, 7);
        a1 = t4;
        a2 = t2;
        a3 = t3;
        a0 = s0;
        jal(ctx, 0x545FA8u, gen::fn_sub_545D18_00545d18);
        sb(zero, s0, 3);
        v0 = s0;
    }
    // 0x00545fb8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00546010 adxstm_Create -- 68 bytes; frame 0x10: ra sp+0x0
// ADXSTM: create a stream on the stream joint a0, from the second range when a1 >= 256, else from the first.
void adxstm_Create(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00546010
    enter(ctx, 8);  // entry check point + this block's cycles
    v1 = a0;
    a0 = 0;
    sp = addiu(sp, -0x10);
    v0 = slti(a1, 256);
    sd(ra, sp, 0x0);
    a3 = v1;
    a1 = 0;
    if (v0 == 0) {
        // 0x00546040
        charge(ctx, 3);
        a2 = 0;
        jal(ctx, 0x546040u, gen::fn_sub_545EF8_00545ef8);
        ld(ra, sp, 0x0);
    } else {
        // 0x00546030
        charge(ctx, 4);
        a2 = 0;
        jal(ctx, 0x546030u, gen::fn_sub_545E20_00545e20);
        ld(ra, sp, 0x0);
    }
    // 0x0054604c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00546088 sub_546088 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXSTM: destroy a stream: stop it, release it, clear the 96-byte record.
void sub_546088(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00546088
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x005460d0
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0054609c
    charge(ctx, 12);
    jal(ctx, 0x54609Cu, gen::fn_sub_546638_00546638);
    a0 = s0;
    jal(ctx, 0x5460A4u, gen::fn_sub_5462E0_005462e0);
    sb(zero, s0, 0);
    a0 = s0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    a1 = 0;
    a2 = 96;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x00546150 sub_546150 -- 116 bytes; frame 0x30: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// ADXSTM: under the lock store the file name a1 / directory a2, start a3 and sector count a4 (bytes a4 << 11) and
// request an open (+69 = 1).
void sub_546150(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00546150
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    s2 = t0;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a3;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    s4 = a2;
    jal(ctx, 0x54617Cu, gen::fn_sub_545BF0_00545bf0);
    v1 = sll(s2, 11);
    v0 = 1;
    sw(s1, s0, 12);
    sw(s2, s0, 20);
    sw(s3, s0, 80);
    sw(s4, s0, 84);
    sb(v0, s0, 69);
    sw(v1, s0, 16);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    gen::fn_atan2l_2_00545c08(ctx);  // tail call
}

// 0x005461C8 sub_5461C8 -- 108 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// ADXSTM: open (sub_546238) between the critical hooks.
void sub_5461C8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005461c8
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    s4 = t0;
    jal(ctx, 0x5461F4u, gen::fn_coshl_2_00545c38);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    t0 = s4;
    jal(ctx, 0x54620Cu, gen::fn_sub_546238_00546238);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    gen::fn_sub_545C40_00545c40(ctx);  // tail call
}

// 0x00546238 sub_546238 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXSTM: request an open and run the fs status server until the request clears (+69).
void sub_546238(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00546238
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x546244u, gen::fn_sub_5460E0_005460e0);
    for (;;) {
        // 0x00546250
        charge(ctx, 5);
        jal(ctx, 0x546250u, gen::fn_ADXT_UpdateFsStat_0053e0b8);
        lb(v0, s0, 69);
        ld(ra, sp, 0x8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00546264
    charge(ctx, 3);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005462A0 sub_5462A0 -- 64 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXSTM: stop, then under the lock request a close (+70) when the file is open (+73) and drop any open request.
void sub_5462A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005462a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5462ACu, gen::fn_sub_5465A0_005465a0);
    jal(ctx, 0x5462B4u, gen::fn_sub_545BF0_00545bf0);
    lb(v1, s0, 73);
    v0 = 1;
    if (v1 == v0) {
        sb(v1, s0, 70);
    }
    // 0x005462cc
    charge(ctx, 5);
    sb(zero, s0, 69);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_atan2l_2_00545c08(ctx);  // tail call
}

// 0x005462E0 sub_5462E0 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXSTM: close (sub_546310) between the critical hooks.
void sub_5462E0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005462e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5462ECu, gen::fn_coshl_2_00545c38);
    a0 = s0;
    jal(ctx, 0x5462F4u, gen::fn_sub_546310_00546310);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_545C40_00545c40(ctx);  // tail call
}

// 0x00546310 sub_546310 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXSTM: stop, request a close and run the fs status server until the file is shut (+73).
void sub_546310(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00546310
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x54631Cu, gen::fn_sub_546638_00546638);
    a0 = s0;
    jal(ctx, 0x546324u, gen::fn_sub_546270_00546270);
    lb(v0, s0, 73);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        for (;;) {
            // 0x00546338
            charge(ctx, 5);
            jal(ctx, 0x546338u, gen::fn_ADXT_UpdateFsStat_0053e0b8);
            lb(v0, s0, 73);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0054634c
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x00546350 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005463A0 sub_5463A0 -- 8 bytes; leaf frame (no stack)
// ADXSTM: returns the status byte +1.
void sub_5463A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005463a0
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, 1);
}

// 0x005463F0 sub_5463F0 -- 28 bytes; leaf frame (no stack)
// ADXSTM: set the read position +88 to a1 clamped to the sector count +20; returns it.
void sub_5463F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x005463f0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, 20);
    sw(a1, a0, 88);
    a1 = slt(v0, a1);
    if (a1 != 0) {
        sw(v0, a0, 88);
    }
    // 0x00546404
    charge(ctx, 2);
    lw(v0, a0, 88);
}

// 0x00546410 sub_546410 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXSTM: read position (sub_546448) between the critical hooks.
void sub_546410(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00546410
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x54641Cu, gen::fn_coshl_2_00545c38);
    a0 = s0;
    jal(ctx, 0x546424u, gen::fn_sub_546448_00546448);
    s0 = v0;
    jal(ctx, 0x54642Cu, gen::fn_sub_545C40_00545c40);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00546448 sub_546448 -- 24 bytes; leaf frame (no stack)
// ADXSTM: read position +88 when a file is set (+8), else 0.
void sub_546448(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00546448
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, 8);
    v0 = 0;
    if (v1 != 0) {
        // 0x00546454
        charge(ctx, 1);
        lw(v0, a0, 88);
    }
    // 0x00546458 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00546460 sub_546460 -- 56 bytes; leaf frame (no stack)
// ADXSTM: reset the transfer state: counters +52 / +76 cleared, status 2 (prepared) or 3 (empty file), no read in
// flight, request +36 / +40 cleared, start flag +71. Returns 1.
void sub_546460(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4};
    // 0x00546460
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 20);
    sw(zero, a0, 52);
    sw(zero, a0, 76);
    if (v0 != 0) {
        // 0x00546478
        charge(ctx, 1);
        v0 = 2;
    } else {
        // 0x00546470
        charge(ctx, 2);
        v0 = 3;
    }
    // 0x0054647c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sb(v0, a0, 1);
    v0 = 1;
    sb(zero, a0, 2);
    sw(zero, a0, 36);
    sw(zero, a0, 40);
    sb(v0, a0, 71);
}

// 0x005464D0 sub_5464D0 -- 64 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXSTM: start under the lock with no end sector (+92 = 0xFFFFF).
void sub_5464D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005464d0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5464DCu, gen::fn_sub_539818_00539818);
    a0 = s0;
    jal(ctx, 0x5464E4u, gen::fn_sub_546460_00546460);
    v0 = 0xF0000;
    v0 = v0 | 0xFFFF;
    link(ctx, 0x5464F4u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 92);
    call(ctx, gen::fn_sub_539830_00539830);
    v0 = 1;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00546510 sub_546510 -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXSTM: start with an end sector (sub_546558) between the critical hooks.
void sub_546510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00546510
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x546524u, gen::fn_coshl_2_00545c38);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x546530u, gen::fn_sub_546558_00546558);
    s0 = v0;
    jal(ctx, 0x546538u, gen::fn_sub_545C40_00545c40);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00546558 sub_546558 -- 68 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXSTM: start under the lock with end sector a1 (+92).
void sub_546558(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00546558
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x54656Cu, gen::fn_sub_539818_00539818);
    a0 = s0;
    jal(ctx, 0x546574u, gen::fn_sub_546460_00546460);
    link(ctx, 0x54657Cu);  // $ra first: the delay slot below depends on it
    sw(s1, s0, 92);
    call(ctx, gen::fn_sub_539830_00539830);
    v0 = 1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005465D0 sub_5465D0 -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXSTM: stop under the lock: a busy record (word & 0xFFFF00 == 0x10200) gets a stop request (+72) and loses a pending
// start; any other goes to status 1 (stopped).
void sub_5465D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005465d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5465DCu, gen::fn_sub_545BF0_00545bf0);
    lw(v0, s0, 0);
    v1 = 0xFF0000;
    v1 = v1 | 0xFF00;  // &0xFFFF00
    a0 = 0x10000;
    v0 = v0 & v1;
    a0 = a0 | 0x200;
    a1 = 1;
    if (v0 != a0) {
        // 0x00546620
        charge(ctx, 2);
        v0 = 1;
        sb(v0, s0, 1);
    } else {
        // 0x00546604
        charge(ctx, 4);
        lb(v1, s0, 71);
        v0 = 1;
        sb(v0, s0, 72);
        if (v1 == a1) {
            // 0x00546614
            charge(ctx, 2);
            sb(zero, s0, 71);
        }
    }
    // 0x00546628
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_atan2l_2_00545c08(ctx);  // tail call
}

// 0x00546638 sub_546638 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXSTM: stop and wait (sub_546668) between the critical hooks.
void sub_546638(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00546638
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x546644u, gen::fn_coshl_2_00545c38);
    a0 = s0;
    jal(ctx, 0x54664Cu, gen::fn_sub_546668_00546668);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_545C40_00545c40(ctx);  // tail call
}

// 0x00546668 sub_546668 -- 80 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXSTM: stop, then run the fs status server until the status is 1 and no request is in flight (+36).
void sub_546668(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00546668
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = 1;
    jal(ctx, 0x54667Cu, gen::fn_sub_5465A0_005465a0);
    for (;;) {
        // 0x00546688
        charge(ctx, 5);
        jal(ctx, 0x546688u, gen::fn_ADXT_UpdateFsStat_0053e0b8);
        lb(v0, s0, 1);
        if (v0 != s1) {
            backedge(ctx);
            continue;
        }
        // 0x0054669c
        charge(ctx, 3);
        lw(v0, s0, 36);
        ld(ra, sp, 0x10);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005466a8
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
}

// 0x00546708 sub_546708 -- 12 bytes; leaf frame (no stack)
// ADXSTM: store the end callback a1 and its argument a2 (+56 / +60).
void sub_546708(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00546708
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a2, a0, 60);
    sw(a1, a0, 56);
}

// 0x00546758 sub_546758 -- 24 bytes; leaf frame (no stack)
// ADXSTM: set the read end +48 to a1, or to the sector count +20 when a1 is negative.
void sub_546758(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00546758
    enter(ctx, 2);  // entry check point + this block's cycles
    if (i64(a1) >= 0) {
        // 0x00546760
        charge(ctx, 2);
        sw(a1, a0, 48);
        return;
    }
    lw(v0, a0, 20);
    // 0x00546768
    charge(ctx, 2);
    sw(v0, a0, 48);
}

// 0x00546788 adxstmf_ExecRead -- 1060 bytes; frame 0x50: s0 sp+0x20, s3 sp+0x38, s1 sp+0x28, s2 sp+0x30, s4 sp+0x40, ra sp+0x48
// ADXSTM read server for one record: completes a finished read (puts the sectors into the stream joint, advances the
// position, calls the end callback, ends at the limit), retries errors up to 0x792BD0 times, then issues the next
// cvFsSeek + cvFsReqRd sized by the joint's free room, the end and the 512-sector cap (jalr through the joint's
// vtable).
void adxstmf_ExecRead(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00546788
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x20);
    sd(s3, sp, 0x38);
    s3 = a0;
    sd(s1, sp, 0x28);
    sd(s2, sp, 0x30);
    sd(s4, sp, 0x40);
    sd(ra, sp, 0x48);
    lw(a0, s3, 8);
    link(ctx, 0x5467ACu);  // $ra first: the delay slot below depends on it
    lw(s4, s3, 4);
    call(ctx, gen::fn_cvFsGetStat_00556668);
    s0 = v0;
    jal(ctx, 0x5467B4u, gen::fn_sub_545BF0_00545bf0);
    lb(v1, s3, 2);
    v0 = 1;
    if (v1 != v0) {
        lb(v1, s3, 1);
    } else {
        // 0x005467cc
        charge(ctx, 2);
        v0 = 3;
        if (s0 == v1) {
            // 0x005467d4
            charge(ctx, 35);
            sb(zero, s3, 2);
            s2 = addiu(s3, 36);
            jal(ctx, 0x5467D8u, gen::fn_atan2l_2_00545c08);
            lw(s0, s3, 32);
            s1 = addiu(sp, 0x10);
            a2 = sp;
            s0 = sll(s0, 11);
            a3 = s1;
            a1 = s0;
            a0 = s2;
            jal(ctx, 0x5467F8u, gen::fn_sub_563C28_00563c28);
            lw(v1, s4, 0);
            a2 = sp;
            a0 = s4;
            lw(v0, v1, 32);
            a1 = 1;
            jalr(ctx, 0x546810u, v0.u());
            lw(v1, s4, 0);
            a0 = s4;
            a1 = 0;
            lw(v0, v1, 28);
            a2 = s1;
            jalr(ctx, 0x546828u, v0.u());
            lw(v1, s3, 88);
            lw(v0, s3, 52);
            lw(a0, s3, 32);
            lw(a1, s3, 48);
            v0 = addu(v0, s0);
            v1 = addu(v1, a0);
            sw(v0, s3, 52);
            sw(zero, s2, 0);
            sw(v1, s3, 88);
            sw(zero, s3, 40);
            lw(s0, s3, 20);
            if (v1 == a1) {
                // 0x00546860
                charge(ctx, 3);
                lw(v0, s3, 56);
                if (v0 != 0) {
                    // 0x0054686c
                    charge(ctx, 2);
                    jt = v0.u();  // the target, read before the delay slot
                    link(ctx, 0x54686Cu);  // $ra = the return address
                    lw(a0, s3, 60);
                    call_ptr(ctx, jt);
                    goto L_00546874;
                }
                lw(v0, s3, 88);
                goto L_00546878;
            }
        L_00546874:
            charge(ctx, 1);
            lw(v0, s3, 88);
        L_00546878:
            charge(ctx, 3);
            v0 = slt(v0, s0);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 3;
            if (!cc) {
                // 0x00546884
                charge(ctx, 6);
                lw(v0, s3, 52);
                lw(v1, s3, 92);
                v0 = srl(v0, 11);
                v0 = sltu(v0, v1);
                if (v0 != 0) {
                    sw(zero, s3, 76);
                } else {
                    // 0x0054689c
                    charge(ctx, 5);
                    v0 = 0xF0000;
                    v0 = v0 | 0xFFFE;
                    v0 = sltu(v0, v1);
                    if (v0 == 0) {
                        // 0x005468b0
                        charge(ctx, 1);
                        v0 = 3;
                        goto L_005468b4;
                    }
                    sw(zero, s3, 76);
                }
                goto L_00546948;
            }
        L_005468b4:
            charge(ctx, 3);
            sb(v0, s3, 1);
            sw(zero, s3, 76);
            goto L_00546948;
        }
        // 0x005468c0
        charge(ctx, 2);
        if (s0 != v0) {
            // 0x00546940
            charge(ctx, 2);
            jal(ctx, 0x546940u, gen::fn_atan2l_2_00545c08);
        L_00546948:
            charge(ctx, 1);
            lb(v1, s3, 1);
        } else {
            // 0x005468c8
            charge(ctx, 15);
            sb(zero, s3, 2);
            s0 = addiu(s3, 36);
            jal(ctx, 0x5468CCu, gen::fn_atan2l_2_00545c08);
            lw(v1, s4, 0);
            a0 = s4;
            a1 = 0;
            lw(v0, v1, 28);
            a2 = s0;
            jalr(ctx, 0x5468E4u, v0.u());
            sw(zero, s0, 0);
            sw(zero, s3, 40);
            v0 = 0x790000;
            lw(v0, v0, 11216);  // 0x792BD0 ADXSTM retry limit
            lw(v1, s3, 76);
            if (i64(v0) >= 0) {
                // 0x00546904
                charge(ctx, 3);
                v0 = slt(v0, v1);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = 0x7FFF0000;
                if (cc) {
                    goto L_00546924;
                }
                // 0x00546910
                charge(ctx, 3);
                v0 = 4;
                sb(v0, s3, 1);
                goto L_00546948;
            }
            // 0x00546920
            charge(ctx, 1);
            v0 = 0x7FFF0000;
        L_00546924:
            charge(ctx, 4);
            v0 = v0 | 0xFFFE;
            v0 = slt(v0, v1);
            if (v0 == 0) {
                // 0x00546934
                charge(ctx, 3);
                v0 = addiu(v1, 1);
                sw(v0, s3, 76);
                goto L_00546948;
            }
            lb(v1, s3, 1);
        }
    }
    // 0x0054694c
    charge(ctx, 3);
    v0 = 4;
    ld(s0, sp, 0x20);
    if (v1 != v0) {
        // 0x00546958
        charge(ctx, 3);
        lb(v0, s3, 2);
        ld(s1, sp, 0x28);
        if (v0 == 0) {
            // 0x00546964
            charge(ctx, 9);
            v0 = 1;
            sw(zero, s3, 36);
            sb(v0, s3, 2);
            s1 = 1;
            link(ctx, 0x546974u);  // $ra first: the delay slot below depends on it
            sw(zero, s3, 40);
            call(ctx, gen::fn_atan2l_2_00545c08);
            lb(v0, s3, 68);
            if (v0 == s1) {
                sb(zero, s3, 2);
            } else {
                // 0x00546988
                charge(ctx, 3);
                lb(v0, s3, 72);
                if (v0 == s1) {
                    sb(zero, s3, 2);
                    goto L_00546b8c;
                }
                // 0x00546994
                charge(ctx, 3);
                lw(v0, s3, 20);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = 3;
                if (!cc) {
                    // 0x005469a0
                    charge(ctx, 4);
                    sb(zero, s3, 2);
                    sb(v0, s3, 1);
                    sw(zero, s3, 32);
                    goto L_00546b8c;
                }
                // 0x005469b0
                charge(ctx, 2);
                if (s4 != 0) {
                    // 0x005469b8
                    charge(ctx, 3);
                    lw(v0, s4, 0);
                    if (v0 == 0) {
                        goto L_005469c4;
                    }
                    lw(v0, v0, 36);
                    // 0x005469d8
                    charge(ctx, 9);
                    a0 = s4;
                    a1 = 0;
                    jalr(ctx, 0x5469DCu, v0.u());
                    lw(v1, s3, 64);
                    lw(a0, s3, 28);
                    v1 = subu(v1, v0);
                    v1 = slt(v1, a0);
                    if (v1 == 0) {
                        // 0x005469fc
                        charge(ctx, 2);
                        sb(zero, s3, 2);
                        goto L_00546b8c;
                    }
                    lw(v1, s4, 0);
                    // 0x00546a08
                    charge(ctx, 32);
                    a3 = addiu(sp, 0x10);
                    lw(a2, s3, 24);
                    a0 = s4;
                    lw(v0, v1, 24);
                    a1 = 0;
                    jalr(ctx, 0x546A18u, v0.u());
                    lw(a1, s3, 48);
                    lw(v1, sp, 0x14);
                    a2 = 0;
                    lw(a3, s3, 88);
                    a0 = addiu(v1, 2047);
                    v0 = slti(v1, 0);
                    if (v0 != 0) v1 = a0;
                    lw(v0, s3, 20);
                    a1 = subu(a1, a3);
                    s0 = sra(v1, 11);
                    v1 = slt(s0, a1);
                    v0 = subu(v0, a3);
                    if (v1 == 0) s0 = a1;
                    lw(a1, s3, 12);
                    v1 = slt(s0, v0);
                    lw(t0, s3, 44);
                    if (v1 == 0) s0 = v0;
                    lw(a0, s3, 8);
                    v0 = slt(s0, t0);
                    a1 = addu(a1, a3);
                    if (v0 == 0) s0 = t0;
                    jal(ctx, 0x546A70u, gen::fn_cvFsSeek_00556478);
                    v1 = 0x790000;
                    lw(a0, v1, 15112);  // 0x793B08
                    v0 = 0xF0000;
                    if (a0 == s1) {
                        // 0x00546a88
                        charge(ctx, 5);
                        v0 = 0x7A0000;
                        sw(a0, v0, 2344);  // 0x7A0928
                        lb(v1, s3, 3);
                        v0 = 0x7A0000;
                        if (v1 != a0) {
                            // 0x00546aa8
                            charge(ctx, 1);
                            sb(a0, v0, 2348);
                        } else {
                            // 0x00546a9c
                            charge(ctx, 2);
                            sb(zero, v0, 2348);
                        }
                        // 0x00546aac
                        charge(ctx, 1);
                        v0 = 0xF0000;
                    }
                    // 0x00546ab0
                    charge(ctx, 4);
                    lw(a1, s3, 92);
                    v0 = v0 | 0xFFFF;
                    if (a1 == v0) {
                        lw(a0, s3, 8);
                    } else {
                        // 0x00546ac0
                        charge(ctx, 9);
                        lw(v0, s3, 52);
                        v1 = slti(v0, 0);
                        a0 = addiu(v0, 2047);
                        if (v1 != 0) v0 = a0;
                        v0 = sra(v0, 11);
                        v0 = subu(a1, v0);
                        v1 = slt(s0, v0);
                        if (v1 == 0) s0 = v0;
                        lw(a0, s3, 8);
                    }
                    // 0x00546ae4
                    charge(ctx, 9);
                    a1 = s0;
                    link(ctx, 0x546AE8u);  // $ra first: the delay slot below depends on it
                    lw(a2, sp, 0x10);
                    call(ctx, gen::fn_cvFsReqRd_005564e0);
                    lw(a0, sp, 0x14);
                    lw(v1, sp, 0x10);
                    sw(a0, s3, 40);
                    sw(v1, s3, 36);
                    sw(v0, s3, 32);
                    if (i64(v0) > 0) {
                        goto L_00546b8c;
                    }
                    // 0x00546b08
                    charge(ctx, 15);
                    lw(v1, s4, 0);
                    s0 = addiu(s3, 36);
                    a0 = s4;
                    a1 = 0;
                    lw(v0, v1, 28);
                    a2 = s0;
                    jalr(ctx, 0x546B1Cu, v0.u());
                    sw(zero, s0, 0);
                    sw(zero, s3, 40);
                    sb(zero, s3, 2);
                    link(ctx, 0x546B30u);  // $ra first: the delay slot below depends on it
                    lw(a0, s3, 8);
                    call(ctx, gen::fn_cvFsGetStat_00556668);
                    v1 = 3;
                    if (v0 != v1) {
                        ld(s0, sp, 0x20);
                    } else {
                        // 0x00546b44
                        charge(ctx, 4);
                        v0 = 0x790000;
                        lw(v0, v0, 11216);  // 0x792BD0 ADXSTM retry limit
                        lw(v1, s3, 76);
                        if (i64(v0) >= 0) {
                            // 0x00546b54
                            charge(ctx, 3);
                            v0 = slt(v0, v1);
                            cc = v0 == 0;  // the condition, before the delay slot changes it
                            v0 = 0x7FFF0000;
                            if (cc) {
                                goto L_00546b74;
                            }
                            // 0x00546b60
                            charge(ctx, 3);
                            v0 = 4;
                            sb(v0, s3, 1);
                            goto L_00546b8c;
                        }
                        // 0x00546b70
                        charge(ctx, 1);
                        v0 = 0x7FFF0000;
                    L_00546b74:
                        charge(ctx, 4);
                        v0 = v0 | 0xFFFE;
                        v0 = slt(v0, v1);
                        ld(s0, sp, 0x20);
                        if (v0 == 0) {
                            // 0x00546b84
                            charge(ctx, 2);
                            v0 = addiu(v1, 1);
                            sw(v0, s3, 76);
                            goto L_00546b8c;
                        }
                    }
                    goto L_00546b90;
                }
            L_005469c4:
                charge(ctx, 4);
                link(ctx, 0x5469C4u);  // $ra first: the delay slot below depends on it
                sb(zero, s3, 2);
                call(ctx, gen::fn_sub_546770_00546770);
                ld(s0, sp, 0x20);
                goto L_00546b90;
            }
        L_00546b8c:
            charge(ctx, 1);
            ld(s0, sp, 0x20);
            goto L_00546b90;
        }
        // 0x00546b94 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s2, sp, 0x30);
        ld(s3, sp, 0x38);
        ld(s4, sp, 0x40);
        ld(ra, sp, 0x48);
        sp = addiu(sp, 0x50);
        return;
    }
L_00546b90:
    charge(ctx, 1);
    ld(s1, sp, 0x28);
    // 0x00546b94 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x00546BB0 ADXSTMF_ExecHndl -- 480 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// ADXSTM handle server: applies stop and close requests, opens a requested file (cvFsOpen, size by seek / tell or
// cvFsGetFileSize, clamps the range), then runs adxstmf_ExecRead while the stream is active.
void ADXSTMF_ExecHndl(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00546bb0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lb(v0, s0, 2);
    if (v0 != 0) {
        lb(v1, s0, 1);
    } else {
        // 0x00546bd4
        charge(ctx, 4);
        lb(v1, s0, 72);
        v0 = 1;
        if (v1 != v0) {
            lb(v1, s0, 70);
        } else {
            // 0x00546be4
            charge(ctx, 3);
            lb(v0, s0, 71);
            sb(zero, s0, 72);
            if (v0 == 0) {
                // 0x00546bf0
                charge(ctx, 1);
                sb(v1, s0, 1);
            }
            // 0x00546bf4
            charge(ctx, 2);
            lb(v1, s0, 70);
            v0 = 1;
        }
        // 0x00546bfc
        charge(ctx, 2);
        if (v1 == v0) {
            // 0x00546c04
            charge(ctx, 3);
            lw(a0, s0, 8);
            if (a0 == 0) {
                sb(zero, s0, 70);
            } else {
                // 0x00546c10
                charge(ctx, 3);
                link(ctx, 0x546C10u);  // $ra first: the delay slot below depends on it
                sw(zero, s0, 8);
                call(ctx, gen::fn_cvFsClose_00556398);
                sb(zero, s0, 70);
            }
            // 0x00546c1c
            charge(ctx, 1);
            sb(zero, s0, 73);
        }
        // 0x00546c20
        charge(ctx, 6);
        jal(ctx, 0x546C20u, gen::fn_sub_545BF0_00545bf0);
        lb(v1, s0, 69);
        v0 = 1;
        if (v1 != v0) {
            // 0x00546d38
            charge(ctx, 2);
            jal(ctx, 0x546D38u, gen::fn_atan2l_2_00545c08);
        L_00546d40:
            charge(ctx, 1);
            lb(v1, s0, 71);
        L_00546d44:
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                sb(zero, s0, 71);
            }
            // 0x00546d50
            charge(ctx, 1);
            lb(v1, s0, 1);
            goto L_00546d54;
        }
        // 0x00546c38
        charge(ctx, 5);
        link(ctx, 0x546C38u);  // $ra first: the delay slot below depends on it
        sb(v1, s0, 73);
        call(ctx, gen::fn_atan2l_2_00545c08);
        lw(v0, s0, 8);
        if (v0 != 0) {
            lb(v1, s0, 71);
            goto L_00546d44;
        }
        // 0x00546c4c
        charge(ctx, 6);
        lw(a0, s0, 80);
        a2 = 0;
        link(ctx, 0x546C54u);  // $ra first: the delay slot below depends on it
        lw(a1, s0, 84);
        call(ctx, gen::fn_cvFsOpen_00556048);
        sw(v0, s0, 8);
        if (v0 != 0) {
            // 0x00546c88
            charge(ctx, 10);
            a0 = v0;
            a1 = 0;
            a2 = 2;
            jal(ctx, 0x546C90u, gen::fn_cvFsSeek_00556478);
            link(ctx, 0x546C98u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 8);
            call(ctx, gen::fn_cvFsTell_00556410);
            s1 = v0;
            lw(v0, s0, 84);
            s2 = sll(s1, 11);
            if (v0 == 0) {
                // 0x00546cb0
                charge(ctx, 3);
                link(ctx, 0x546CB0u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 80);
                call(ctx, gen::fn_cvFsGetFileSize_005566d0);
                s2 = v0;
            }
            // 0x00546cbc
            charge(ctx, 9);
            lw(a0, s0, 8);
            a1 = 0;
            a2 = 0;
            jal(ctx, 0x546CC4u, gen::fn_cvFsSeek_00556478);
            lw(v1, s0, 16);
            v0 = 0x7FFF0000;
            v0 = v0 | 0xF800;
            if (v1 != v0) {
                lw(v1, s0, 12);
            } else {
                // 0x00546ce0
                charge(ctx, 3);
                sw(s2, s0, 16);
                sw(s1, s0, 20);
                lw(v1, s0, 12);
            }
            // 0x00546cec
            charge(ctx, 3);
            v0 = slt(s1, v1);
            if (v0 == 0) {
                lw(v0, s0, 20);
            } else {
                // 0x00546cf8
                charge(ctx, 3);
                sw(s1, s0, 12);
                v1 = s1;
                lw(v0, s0, 20);
            }
            // 0x00546d04
            charge(ctx, 4);
            v0 = addu(v0, v1);
            v0 = slt(s1, v0);
            a0 = s0;
            if (v0 != 0) {
                // 0x00546d14
                charge(ctx, 4);
                v0 = subu(s1, v1);
                v1 = sll(v0, 11);
                sw(v0, s0, 20);
                sw(v1, s0, 16);
            }
            // 0x00546d24
            charge(ctx, 4);
            a1 = 0;
            jal(ctx, 0x546D24u, gen::fn_sub_5463A8_005463a8);
            sb(zero, s0, 69);
            goto L_00546d40;
        }
        // 0x00546c64
        charge(ctx, 9);
        a0 = 0x7C0000;
        lw(a1, s0, 80);
        a0 = addiu(a0, 9920);  // "E02110501 adxstmf_stat_exec: can't open "
        jal(ctx, 0x546C6Cu, gen::fn_sub_53AE60_0053ae60);
        v0 = 4;
        sb(v0, s0, 1);
        sb(zero, s0, 69);
        sb(zero, s0, 73);
    L_00546d78:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
        // 0x00546d7c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_00546d54:
    charge(ctx, 3);
    v0 = 2;
    if (v1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00546d60
        charge(ctx, 4);
        lb(v1, s0, 73);
        v0 = 1;
        if (v1 == v0) {
            // 0x00546d70
            charge(ctx, 2);
            a0 = s0;
            jal(ctx, 0x546D70u, gen::fn_adxstmf_ExecRead_00546788);
            goto L_00546d78;
        }
        ld(s0, sp, 0x0);
    }
    // 0x00546d7c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00546D90 sub_546D90 -- 36 bytes; frame 0x10: ra sp+0x0
// ADXSTM: run the record servers (sub_546DB8) between the critical hooks.
void sub_546D90(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00546d90
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x546D98u, gen::fn_coshl_2_00545c38);
    jal(ctx, 0x546DA0u, gen::fn_sub_546DB8_00546db8);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_545C40_00545c40(ctx);  // tail call
}

// 0x00546DB8 sub_546DB8 -- 124 bytes; frame 0x30: s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x20
// ADXSTM: unless re-entered (sub_5655E8 on 0x792BCC), run ADXSTMF_ExecHndl on every used record of the 40, then clear
// the guard.
void sub_546DB8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00546db8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s3, sp, 0x18);
    s3 = 0x790000;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    a0 = addiu(s3, 11212);  // &0x792BCC ADXSTM server busy
    jal(ctx, 0x546DD4u, gen::fn_cosl_2_00545c20);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x790000;
    if (!cc) {
        // 0x00546de4
        charge(ctx, 3);
        s2 = 1;
        s0 = addiu(v0, 11224);
        s1 = 39;
        for (;;) {
            // 0x00546df0
            charge(ctx, 3);
            lb(v0, s0, 0);
            if (v0 != s2) {
                s1 = addiu(s1, -1);
            } else {
                // 0x00546dfc
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x546DFCu, gen::fn_ADXSTMF_ExecHndl_00546bb0);
                s1 = addiu(s1, -1);
            }
            // 0x00546e08
            charge(ctx, 2);
            s0 = addiu(s0, 96);
            if (i64(s1) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00546e10
        charge(ctx, 2);
        v0 = addiu(s3, 11212);
        sw(zero, v0, 0);
    }
    // 0x00546e18 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00546E38 sub_546E38 -- 36 bytes; frame 0x10: ra sp+0x0
// ADXSTM: run the CVFS server between the critical hooks.
void sub_546E38(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00546e38
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x546E40u, gen::fn_coshl_2_00545c38);
    jal(ctx, 0x546E48u, gen::fn_adxstmf_ExecServer_00546e60);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_545C40_00545c40(ctx);  // tail call
}

// 0x00546E60 adxstmf_ExecServer -- 20 bytes; frame 0x10: ra sp+0x0
// ADXSTM: tail call cvFsExecServer.
void adxstmf_ExecServer(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00546e60
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_cvFsExecServer_00556608(ctx);  // tail call
}

// 0x00546FF8 sub_546FF8 -- 16 bytes; leaf frame (no stack)
// ADXSTM: store a2 / a1 to +24 / +28; returns 1.
void sub_546FF8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00546ff8
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 1;
    sw(a2, a0, 24);
    sw(a1, a0, 28);
}

// 0x00547008 sub_547008 -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXSTM: set the request cap (sub_547050) between the critical hooks.
void sub_547008(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00547008
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x54701Cu, gen::fn_coshl_2_00545c38);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x547028u, gen::fn_sub_547050_00547050);
    s0 = v0;
    jal(ctx, 0x547030u, gen::fn_sub_545C40_00545c40);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00547050 sub_547050 -- 12 bytes; leaf frame (no stack)
// ADXSTM: request cap +44 = a1; returns 1.
void sub_547050(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00547050
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a1, a0, 44);
    v0 = 1;
}

// 0x00547068 sub_547068 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXSTM: byte size (sub_5470A0) between the critical hooks.
void sub_547068(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00547068
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x547074u, gen::fn_coshl_2_00545c38);
    a0 = s0;
    jal(ctx, 0x54707Cu, gen::fn_sub_5470A0_005470a0);
    s0 = v0;
    jal(ctx, 0x547084u, gen::fn_sub_545C40_00545c40);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005470A0 sub_5470A0 -- 8 bytes; leaf frame (no stack)
// ADXSTM: returns the byte size +16.
void sub_5470A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005470a0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 16);
}

// 0x005470A8 sub_5470A8 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXSTM: sector count (0x5470E0) between the critical hooks.
void sub_5470A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005470a8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5470B4u, gen::fn_coshl_2_00545c38);
    a0 = s0;
    jal(ctx, 0x5470BCu, gen::fn__ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_2_005470e0);
    s0 = v0;
    jal(ctx, 0x5470C4u, gen::fn_sub_545C40_00545c40);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005470E0 _ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_2 -- 8 bytes; leaf frame (no stack)
// ADXSTM: returns the sector count +20. The symbol name (a streambuf::eback) is the map's.
void _ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_2(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005470e0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 20);
}

// 0x00547138 sub_547138 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXSTM: set the pause flag (sub_547178) between the critical hooks.
void sub_547138(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00547138
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x54714Cu, gen::fn_coshl_2_00545c38);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x547158u, gen::fn_sub_547178_00547178);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_545C40_00545c40(ctx);  // tail call
}

// 0x00547178 sub_547178 -- 8 bytes; leaf frame (no stack)
// ADXSTM: store the byte a1 to +68 (reads pause while it is 1).
void sub_547178(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00547178
    enter(ctx, 2);  // entry check point + this block's cycles
    sb(a1, a0, 68);
}

// 0x00547318 sub_547318 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXSTM: attach a stream joint (sub_547358) between the critical hooks.
void sub_547318(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00547318
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x54732Cu, gen::fn_coshl_2_00545c38);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x547338u, gen::fn_sub_547358_00547358);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_545C40_00545c40(ctx);  // tail call
}

// 0x00547358 sub_547358 -- 128 bytes; frame 0x20: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, ra sp+0x18
// ADXSTM: attach the stream joint a1 (+4) and, under the lock, take its buffer size (GetNumData of both lines, jalr)
// into +64 / +28 / +24.
void sub_547358(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00547358
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    link(ctx, 0x547374u);  // $ra first: the delay slot below depends on it
    sw(s0, s2, 4);
    call(ctx, gen::fn_sub_539818_00539818);
    lw(v1, s0, 0);
    a0 = s0;
    lw(v0, v1, 36);
    a1 = 0;
    jalr(ctx, 0x547388u, v0.u());
    lw(v1, s0, 0);
    s1 = v0;
    a0 = s0;
    lw(v0, v1, 36);
    a1 = 1;
    jalr(ctx, 0x5473A0u, v0.u());
    s1 = addu(s1, v0);
    link(ctx, 0x5473ACu);  // $ra first: the delay slot below depends on it
    sw(s1, s2, 64);
    call(ctx, gen::fn_sub_539830_00539830);
    lw(v0, s2, 64);
    ld(s0, sp, 0x0);
    sw(v0, s2, 28);
    sw(v0, s2, 24);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00547558 sub_547558 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXSTM: sub_547590 between the critical hooks.
void sub_547558(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00547558
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x547564u, gen::fn_coshl_2_00545c38);
    a0 = s0;
    jal(ctx, 0x54756Cu, gen::fn_sub_547590_00547590);
    s0 = v0;
    jal(ctx, 0x547574u, gen::fn_sub_545C40_00545c40);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00547668 ADXPS2_SetupDvdFs -- 256 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXPS2: file-system setup. Touches the version strings (memcmp of each with itself), registers the two CVFS devices
// (0x7C26F0 with sub_55E1C0, 0x7C26F8 with dvCiGetInterface), makes the second the default, then sets the DVD layer's
// parameters and root directory from the record a0 (or zeros).
void ADXPS2_SetupDvdFs(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00547668
    enter(ctx, 44);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x20);
    v0 = addiu(v0, 15064);  // "\nADXRT  Ver.3020 Build:Feb 28 2005 19:25:21\n"
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    a0 = v0;
    a1 = a0;
    a2 = 128;
    jal(ctx, 0x54768Cu, gen::fn_memcmp_005211b8);
    a0 = 0x790000;
    a0 = addiu(a0, 15080);  // " Build:Feb 28 2005 19:25:21\n"
    s0 = 0x540000;
    a2 = 232;
    a1 = a0;
    s0 = addiu(s0, 30288);  // &sub_547650
    jal(ctx, 0x5476A8u, gen::fn_memcmp_005211b8);
    a0 = s0;
    a1 = 0;
    jal(ctx, 0x5476B4u, gen::fn_sub_557198_00557198);
    a0 = 0x7C0000;
    a1 = 0x560000;
    a2 = 0;
    a0 = addiu(a0, 9968);  // "MFS"
    a1 = addiu(a1, -7744);  // &sub_55E1C0
    jal(ctx, 0x5476CCu, gen::fn_cvFsAddDev_00555b10);
    a0 = s0;
    a1 = 0;
    s0 = 0x7C0000;
    jal(ctx, 0x5476DCu, gen::fn_sub_557198_00557198);
    a1 = 0x560000;
    s0 = addiu(s0, 9976);  // "CDV"
    a1 = addiu(a1, -25224);  // &dvCiGetInterface
    a2 = 0;
    a0 = s0;
    jal(ctx, 0x5476F4u, gen::fn_cvFsAddDev_00555b10);
    a0 = s0;
    jal(ctx, 0x5476FCu, gen::fn_sub_555E48_00555e48);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    if (s1 == 0) {
        // 0x00547748
        charge(ctx, 8);
        jal(ctx, 0x547748u, gen::fn_sub_55B5F0_0055b5f0);
        a0 = 0;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_dvCiSetRootDir_0055b610(ctx);  // tail call
        return;
    }
    // 0x00547718
    charge(ctx, 11);
    lw(a0, s1, 8);
    lw(a1, s1, 12);
    lw(a2, s1, 16);
    link(ctx, 0x547724u);  // $ra first: the delay slot below depends on it
    lw(a3, s1, 4);
    call(ctx, gen::fn_sub_55B5F0_0055b5f0);
    lw(a0, s1, 0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_dvCiSetRootDir_0055b610(ctx);  // tail call
}

// 0x00548278 sub_548278 -- 96 bytes; frame 0x20: ra sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// Runs sub_548078 on each used 200-byte record of the 16 at 0x787570.
void sub_548278(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00548278
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x780000;
    sd(ra, sp, 0x18);
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 30064);  // &0x787570
    sd(s1, sp, 0x8);
    s1 = 15;
    sd(s2, sp, 0x10);
    s2 = 1;
    for (;;) {
        // 0x005482a0
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x005482ac
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x5482ACu, gen::fn_sub_548078_00548078);
            s1 = addiu(s1, -1);
        }
        // 0x005482b8
        charge(ctx, 2);
        s0 = addiu(s0, 200);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005482c0
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00549000 sub_549000 -- 76 bytes; frame 0x10: ra sp+0x0
// ADXT: for handle a0 with state >= 2, return sub_543118 of its decoder (+4); 0 before; a null handle logs E02080820
// and returns -1.
void sub_549000(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549000
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0054900c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 10472);  // "E02080820 adxt_GetNumChan: parameter error"
        jal(ctx, 0x549010u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-1);
        // 0x00549040 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00549020
    charge(ctx, 4);
    lb(v0, a0, 1);
    v0 = slti(v0, 2);
    if (v0 != 0) {
        v0 = 0;
        // 0x00549040 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00549030
    charge(ctx, 4);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_543118_00543118(ctx);  // tail call
}

// 0x00549310 sub_549310 -- 60 bytes; frame 0x10: ra sp+0x0
// ADXT: halfword a1 of the table at a0 +66; a null handle logs E02080826 and returns 0.
void sub_549310(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549310
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = sll(a1, 1);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00549338
        charge(ctx, 2);
        v1 = addu(v1, a0);
        lh(v0, v1, 66);
    } else {
        // 0x00549320
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 10712);  // "E02080826 adxt_GetOutPan: parameter error"
        jal(ctx, 0x549324u, gen::fn_sub_53AE08_0053ae08);
        v0 = 0;
    }
    // 0x00549340 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00549390 sub_549390 -- 132 bytes; frame 0x10: ra sp+0x0
// ADXT: store the value a1 clamped to -15..15 at +70 and pass it (or -128 while 0x787560 is set) to sub_541BB8 on the
// output record +12; a null handle logs E02080870.
void sub_549390(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00549390
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0054939c
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 10760);  // "E02080870 adxt_SetOutBalance: parameter error"
        sp = addiu(sp, 0x10);
        gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
        return;
    }
    // 0x005493b0
    charge(ctx, 3);
    v0 = slti(a1, -15);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = slti(a1, 16);
    if (cc) {
        // 0x005493c8
        charge(ctx, 2);
        if (v0 != 0) {
            sh(a1, a0, 70);
        } else {
            // 0x005493d0
            charge(ctx, 2);
            v0 = 15;
            sh(v0, a0, 70);
        }
    } else {
        // 0x005493bc
        charge(ctx, 3);
        v0 = si(-15);
        sh(v0, a0, 70);
    }
    // 0x005493d8
    charge(ctx, 4);
    v0 = 0x780000;
    lw(v1, v0, 30048);  // 0x787560
    if (v1 != 0) {
        lw(a0, a0, 12);
        // 0x00549400
        charge(ctx, 3);
        a1 = si(-128);
        jal(ctx, 0x549400u, gen::fn_sub_541BB8_00541bb8);
        ld(ra, sp, 0x0);
    } else {
        // 0x005493e8
        charge(ctx, 5);
        lh(a1, a0, 70);
        link(ctx, 0x5493ECu);  // $ra first: the delay slot below depends on it
        lw(a0, a0, 12);
        call(ctx, gen::fn_sub_541BB8_00541bb8);
        ld(ra, sp, 0x0);
    }
    // 0x0054940c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00549450 sub_549450 -- 48 bytes; frame 0x10: ra sp+0x0
// ADXT: returns the halfword +70; a null handle logs E02080871 and returns 0.
void sub_549450(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549450
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00549470
        charge(ctx, 1);
        lh(v0, a0, 70);
    } else {
        // 0x0054945c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 10808);  // "E02080871 adxt_GetOutBalance: parameter error"
        jal(ctx, 0x549460u, gen::fn_sub_53AE08_0053ae08);
        v0 = 0;
    }
    // 0x00549474 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054AC40 sub_54AC40 -- 64 bytes; leaf frame (no stack)
// Header check: at least 2 bytes starting with the big-endian 0x8001 mark store the length a1 to *a2 and return 1, else
// 0.
void sub_54AC40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0054ac40
    enter(ctx, 4);  // entry check point + this block's cycles
    a3 = a1;
    v1 = slti(a3, 2);
    v0 = 0;
    if (v1 == 0) {
        // 0x0054ac50
        charge(ctx, 8);
        lhu(v1, a0, 0);
        a1 = 0x8001;
        a0 = sll(v1, 8);
        v1 = srl(v1, 8);
        v1 = v1 | a0;
        v1 = v1 & 0xFFFF;
        if (v1 == a1) {
            // 0x0054ac70
            charge(ctx, 2);
            sw(a3, a2, 0);
            v0 = 1;
        }
    }
    // 0x0054ac78 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0054B3F0 sub_54B3F0 -- 220 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// ADXT: start on stream joint a1 / channel a2: checks the arguments (E02080809), stops, then under the lock creates the
// joint reader (sub_561970) and starts it (state 2), or logs E8101207.
void sub_54B3F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b3f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    if (s0 != 0) {
        // 0x0054b414
        charge(ctx, 2);
        if (s1 == 0) {
            a0 = 0x7C0000;
        L_0054b428:
            charge(ctx, 7);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            a0 = addiu(a0, 12160);
            ld(s2, sp, 0x10);
            ld(ra, sp, 0x18);
            sp = addiu(sp, 0x20);
            gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
            return;
        }
        // 0x0054b41c
        charge(ctx, 2);
        if (i64(s2) < 0) {
            goto L_0054b424;
        }
        // 0x0054b448
        charge(ctx, 10);
        jal(ctx, 0x54B448u, gen::fn_sub_548678_00548678);
        jal(ctx, 0x54B450u, gen::fn_sub_539818_00539818);
        a0 = s1;
        a1 = s2;
        jal(ctx, 0x54B45Cu, gen::fn_sub_561970_00561970);
        a0 = s0;
        a1 = v0;
        if (v0 == 0) {
            // 0x0054b470
            charge(ctx, 10);
            jal(ctx, 0x54B470u, gen::fn_sub_539830_00539830);
            a0 = 0x7C0000;
            ld(s0, sp, 0x0);
            a0 = addiu(a0, 12208);  // "E8101207: can't create sj (adxt_StartMem)\n"
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(ra, sp, 0x18);
            sp = addiu(sp, 0x20);
            gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
            return;
        }
        // 0x0054b498
        charge(ctx, 13);
        jal(ctx, 0x54B498u, gen::fn_sub_548318_00548318);
        v0 = 2;
        sb(v0, s0, 2);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x54B4ACu, gen::fn_sceInsockSetsockopt_2_0054a928);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_539830_00539830(ctx);  // tail call
        return;
    }
L_0054b424:
    charge(ctx, 1);
    a0 = 0x7C0000;
    goto L_0054b428;
}

// 0x0054B8E0 sub_54B8E0 -- 164 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXT: per-step stream end check (a data-referenced callback): from the decoded byte count (sectors), set the
// streamer's end or, past the loop limit +196, stop the decoder and lift the read end (0x7FFFFFFF).
void sub_54B8E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b8e0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    lw(s1, s0, 8);
    lw(a0, s0, 4);
    if (s1 != 0) {
        // 0x0054b900
        charge(ctx, 2);
        if (a0 == 0) {
            ld(s0, sp, 0x0);
        } else {
            // 0x0054b908
            charge(ctx, 9);
            jal(ctx, 0x54B908u, gen::fn_sub_5431F0_005431f0);
            lb(a2, s0, 108);
            a0 = addiu(v0, 2047);
            v1 = slti(v0, 0);
            if (v1 != 0) v0 = a0;
            a0 = s1;
            a1 = sra(v0, 11);
            if (a2 != 0) {
                // 0x0054b968
                charge(ctx, 2);
                jal(ctx, 0x54B968u, gen::fn_sub_5463A8_005463a8);
                goto L_0054b970;
            }
            // 0x0054b92c
            charge(ctx, 6);
            link(ctx, 0x54B92Cu);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 4);
            call(ctx, gen::fn_sub_542F60_00542f60);
            lw(v1, s0, 196);
            v0 = slt(v0, v1);
            a1 = si(-1);
            if (v0 == 0) {
                // 0x0054b944
                charge(ctx, 2);
                link(ctx, 0x54B944u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 4);
                call(ctx, gen::fn_sub_5430B8_005430b8);
            }
            // 0x0054b94c
            charge(ctx, 6);
            a1 = 0x7FFF0000;
            lw(a0, s0, 8);
            a1 = a1 | 0xFFFF;
            jal(ctx, 0x54B954u, gen::fn_sub_546718_00546718);
            ld(s0, sp, 0x0);
        }
        // 0x0054b974 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_0054b970:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0054b974 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0054CFE8 sub_54CFE8 -- 40 bytes; frame 0x10: ra sp+0x0
// Tail call sub_534A88 on the record pointer 0x793F44.
void sub_54CFE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054cfe8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x790000;
    sd(ra, sp, 0x0);
    v0 = 0x790000;
    v1 = addiu(v1, 16192);  // &0x793F40
    lw(a0, v0, 16196);  // 0x793F44
    ld(ra, sp, 0x0);
    lw(v0, v1, 0);  // 0x793F40
    sp = addiu(sp, 0x10);
    gen::fn_sub_534A88_00534a88(ctx);  // tail call
}

// 0x0054D528 sub_54D528 -- 64 bytes, 2 chunks; frame 0x10: s0 sp+0x0, ra sp+0x8
// sub_535170 on the record pointer 0x793F44, then store a0 to its +92.
void sub_54D528(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d528
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    s0 = a0;
    lw(a0, v0, 16196);  // 0x793F44
    sd(ra, sp, 0x8);
    jal(ctx, 0x54D540u, gen::fn_sub_535170_00535170);
    a1 = s0;
    ld(ra, sp, 0x8);
    a0 = v0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00535380
    charge(ctx, 2);
    sw(a1, a0, 92);
}

// 0x0054D6B8 sub_54D6B8 -- 300 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// AHX: take a free 44-byte bit-reader record of the 16 at 0x796FE0 for stream joint a0: buffer size from GetNumData
// (jalr), words = size / 4, marked used.
void sub_54D6B8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d6b8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 0x790000;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s0, sp, 0x0);
    v1 = addiu(a1, 28640);  // &0x796FE0
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    lw(v0, v1, 0);  // 0x796FE0
    a3 = 0;
    if (v0 != 0) {
        // 0x0054d6e4
        charge(ctx, 3);
        a0 = v1;
        a3 = addiu(a3, 1);
        for (;;) {
            // 0x0054d6f0
            charge(ctx, 3);
            v1 = slti(a3, 16);
            a0 = addiu(a0, 44);
            if (v1 == 0) {
                goto L_0054d72c;
            }
            // 0x0054d6fc
            charge(ctx, 6);
            lw(v0, a0, 0);
            if (v0 == 0) {
                break;
            }
            a3 = addiu(a3, 1);
            backedge(ctx);
        }
        // 0x0054d714
        charge(ctx, 2);
        goto L_0054d724;
    }
    // 0x0054d720
    charge(ctx, 1);
    v1 = 1;
L_0054d724:
    charge(ctx, 2);
    s0 = sll(a3, 1);
    if (v1 != 0) {
        // 0x0054d738
        charge(ctx, 37);
        v0 = addiu(a1, 28640);
        s0 = addu(s0, a3);
        a2 = 44;
        s0 = sll(s0, 2);
        a1 = 0;
        s0 = subu(s0, a3);
        s0 = sll(s0, 2);
        s0 = addu(s0, v0);
        a0 = s0;
        jal(ctx, 0x54D758u, gen::fn_memset_00521408);
        sw(s2, s0, 4);
        lw(v1, s2, 0);
        a0 = s2;
        sw(zero, s0, 16);
        lw(v0, v1, 36);
        a1 = 1;
        jalr(ctx, 0x54D774u, v0.u());
        lw(v1, s2, 0);
        s1 = v0;
        a0 = s2;
        lw(v0, v1, 36);
        a1 = 0;
        jalr(ctx, 0x54D78Cu, v0.u());
        sw(zero, s0, 36);
        s1 = addu(s1, v0);
        v0 = s0;
        v1 = slti(s1, 0);
        a0 = addiu(s1, 3);
        sw(s1, s0, 20);
        if (v1 != 0) s1 = a0;
        s1 = sra(s1, 2);
        v1 = 1;
        sw(s1, s0, 24);
        sw(v1, s0, 0);
        sw(zero, s0, 28);
        sw(zero, s0, 32);
        sw(zero, s0, 40);
    } else {
    L_0054d72c:
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0054d7cc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0054D7E8 sub_54D7E8 -- 44 bytes; frame 0x10: ra sp+0x0
// AHX: release a bit-reader record (clear its 44 bytes).
void sub_54D7E8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d7e8
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0054d808
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0054d7f4
    charge(ctx, 5);
    ld(ra, sp, 0x0);
    a1 = 0;
    a2 = 44;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0054D898 sub_54D898 -- 576 bytes; frame 0x50: s1 sp+0x28, s2 sp+0x30, s0 sp+0x20, s3 sp+0x38, ra sp+0x40
// AHX bit reader: refill the 32-bit window (+8 / bit count +12) from the joint's chunk, one to four bytes, fetching a
// new chunk when fewer than 4 bytes remain (jalr through the joint's vtable).
void sub_54D898(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d898
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 32;
    sd(s1, sp, 0x28);
    s1 = a0;
    sd(s2, sp, 0x30);
    sd(s0, sp, 0x20);
    sd(s3, sp, 0x38);
    sd(ra, sp, 0x40);
    lw(v1, s1, 12);
    lw(a2, s1, 36);
    v0 = subu(v0, v1);
    a0 = addiu(v0, 7);
    v1 = slti(v0, 0);
    if (v1 != 0) v0 = a0;
    a1 = slti(a2, 4);
    s2 = sra(v0, 3);
    if (a1 != 0) {
        // 0x0054d8dc
        charge(ctx, 8);
        s3 = addiu(s1, 28);
        ldl(v0, s3, 7);
        ldr(v0, s3, 0);
        sdl(v0, sp, 0x7);
        sdr(v0, sp, 0x0);
        lw(a1, sp, 0x4);
        s0 = addiu(sp, 0x10);
        if (a1 != 0) {
            // 0x0054d8fc
            charge(ctx, 17);
            a1 = subu(a1, a2);
            a0 = sp;
            a3 = s0;
            a2 = sp;
            jal(ctx, 0x54D908u, gen::fn_sub_563C28_00563c28);
            lw(a0, s1, 4);
            a1 = 0;
            lw(v1, a0, 0);
            lw(v0, v1, 32);
            a2 = sp;
            jalr(ctx, 0x54D920u, v0.u());
            lw(a0, s1, 4);
            a2 = s0;
            lw(v1, a0, 0);
            lw(v0, v1, 28);
            a1 = 1;
            jalr(ctx, 0x54D938u, v0.u());
        }
        // 0x0054d940
        charge(ctx, 12);
        lw(a0, s1, 4);
        a1 = 1;
        lw(a2, s1, 24);
        lw(v1, a0, 0);
        lw(v0, v1, 24);
        a3 = s3;
        jalr(ctx, 0x54D954u, v0.u());
        lw(v1, s3, 0);
        lw(v0, s1, 32);
        sw(v1, s1, 40);
        sw(v0, s1, 36);
        a2 = v0;
    }
    // 0x0054d970
    charge(ctx, 5);
    v0 = slt(s2, a2);
    v1 = 3;
    if (v0 == 0) s2 = a2;
    if (s2 == v1) {
        // 0x0054d984
        charge(ctx, 19);
        lw(a3, s1, 40);
        a2 = addiu(a2, -3);
        lw(v0, s1, 8);
        lbu(v1, a3, 0);
        a3 = addiu(a3, 1);
        v0 = sll(v0, 8);
        lbu(a0, a3, 0);
        v0 = v0 | v1;
        lw(v1, s1, 12);
        a3 = addiu(a3, 1);
        v0 = sll(v0, 8);
        lbu(a1, a3, 0);
        a3 = addiu(a3, 1);
        v0 = v0 | a0;
        v1 = addiu(v1, 24);
        v0 = sll(v0, 8);
        sw(a2, s1, 36);
        v0 = v0 | a1;
        goto L_0054dab0;
    }
    v0 = 2;
    // 0x0054d9d0
    charge(ctx, 2);
    if (s2 == v0) {
        // 0x0054d9d8
        charge(ctx, 15);
        lw(a3, s1, 40);
        a2 = addiu(a2, -2);
        lw(v0, s1, 8);
        lbu(a0, a3, 0);
        a3 = addiu(a3, 1);
        v0 = sll(v0, 8);
        lbu(a1, a3, 0);
        lw(v1, s1, 12);
        v0 = v0 | a0;
        v0 = sll(v0, 8);
        a3 = addiu(a3, 1);
        v0 = v0 | a1;
        v1 = addiu(v1, 16);
        sw(a2, s1, 36);
        goto L_0054dab0;
    }
    v0 = 1;
    // 0x0054da18
    charge(ctx, 2);
    if (s2 == v0) {
        // 0x0054da20
        charge(ctx, 11);
        lw(a3, s1, 40);
        a1 = addiu(a2, -1);
        lw(v0, s1, 8);
        lbu(a0, a3, 0);
        a3 = addiu(a3, 1);
        lw(v1, s1, 12);
        v0 = sll(v0, 8);
        v0 = v0 | a0;
        sw(a1, s1, 36);
        v1 = addiu(v1, 8);
        goto L_0054dab0;
    }
    v0 = 4;
    // 0x0054da50
    charge(ctx, 2);
    ld(s0, sp, 0x20);
    if (s2 == v0) {
        // 0x0054da58
        charge(ctx, 22);
        lw(a3, s1, 40);
        a2 = addiu(a2, -4);
        lw(v0, s1, 8);
        lbu(v1, a3, 0);
        a3 = addiu(a3, 1);
        v0 = sll(v0, 8);
        lbu(a0, a3, 0);
        v0 = v0 | v1;
        lw(v1, s1, 12);
        a3 = addiu(a3, 1);
        v0 = sll(v0, 8);
        lbu(a1, a3, 0);
        a3 = addiu(a3, 1);
        v0 = v0 | a0;
        lbu(a0, a3, 0);
        v0 = sll(v0, 8);
        v1 = addiu(v1, 32);
        v0 = v0 | a1;
        a3 = addiu(a3, 1);
        v0 = sll(v0, 8);
        sw(a2, s1, 36);
        v0 = v0 | a0;
    L_0054dab0:
        charge(ctx, 4);
        sw(a3, s1, 40);
        sw(v0, s1, 8);
        sw(v1, s1, 12);
        ld(s0, sp, 0x20);
    }
    // 0x0054dac0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0054DB38 sub_54DB38 -- 172 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// AHX bit reader: take a1 bits (refilling as needed), masked by the table 0x796F58; counts calls (0x796F54); returns 0
// when the stream runs dry.
void sub_54DB38(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054db38
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 28500);  // &0x796F54
    lw(a2, s0, 12);
    lw(v1, v0, 0);  // 0x796F54
    a1 = slt(a2, s1);
    v1 = addiu(v1, 1);
    sw(v1, v0, 0);  // 0x796F54
    if (a1 != 0) {
        // 0x0054db70
        charge(ctx, 6);
        jal(ctx, 0x54DB70u, gen::fn_sub_54D898_0054d898);
        lw(a2, s0, 12);
        v1 = slt(a2, s1);
        v0 = 0;
        if (v1 == 0) {
            goto L_0054dba0;
        }
        // 0x0054db88
        charge(ctx, 5);
        lw(v1, s0, 16);
        sw(zero, s0, 12);
        v1 = addu(v1, a2);
        sw(v1, s0, 16);
        // 0x0054dbd0 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_0054dba0:
    charge(ctx, 12);
    lw(v1, s0, 16);
    a1 = sll(s1, 2);
    lw(v0, s0, 8);
    a2 = subu(a2, s1);
    a0 = 0x790000;
    a0 = addu(a0, a1);
    lw(a0, a0, 28504);
    v1 = addu(v1, s1);
    v0 = srav(v0, a2);
    sw(v1, s0, 16);
    sw(a2, s0, 12);
    v0 = v0 & a0;
    // 0x0054dbd0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0054DBE8 sub_54DBE8 -- 8 bytes; leaf frame (no stack)
// AHX bit reader: returns the bits consumed (+16).
void sub_54DBE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0054dbe8
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 16);
}

// 0x0054DBF0 sub_54DBF0 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// AHX bit reader: 1 when the joint holds no data (jalr) and neither the window nor the chunk has any left.
void sub_54DBF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0054dbf0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(a0, s0, 4);
    lw(v1, a0, 0);
    lw(v0, v1, 36);
    a1 = 1;
    jalr(ctx, 0x54DC0Cu, v0.u());
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x0054dc1c
        charge(ctx, 3);
        lw(v0, s0, 12);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x0054dc28
            charge(ctx, 3);
            lw(v1, s0, 36);
            v0 = 1;
            if (v1 != 0) {
                // 0x0054dc34
                charge(ctx, 1);
                v0 = 0;
            }
        }
    }
    // 0x0054dc38 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0054DE50 sub_54DE50 -- 28 bytes; leaf frame (no stack)
// AHX: count an init (0x7973A0); returns 0.
void sub_54DE50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0054de50
    enter(ctx, 7);  // entry check point + this block's cycles
    a0 = 0x790000;
    v0 = 0;
    a0 = addiu(a0, 29600);  // &0x7973A0 AHX init count
    lw(v1, a0, 0);  // 0x7973A0 AHX init count
    v1 = addiu(v1, 1);
    sw(v1, a0, 0);  // 0x7973A0 AHX init count
}

// 0x0054DE90 sub_54DE90 -- 436 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// [ahx_CalcKey] AHX: the three cipher keys of a key string, as sub_543470 (same tables), counting the init at 0x7973A0.
void sub_54DE90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054de90
    enter(ctx, 15);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x30);
    lw(v1, v0, 29600);  // 0x7973A0 AHX init count
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
        // 0x0054decc
        charge(ctx, 2);
        jal(ctx, 0x54DECCu, gen::fn_sub_54DE50_0054de50);
    }
    // 0x0054ded4
    charge(ctx, 4);
    sh(zero, s2, 0);
    sh(zero, s3, 0);
    sh(zero, s4, 0);
    if (s1 == 0) {
        // 0x0054dee4
        charge(ctx, 2);
        v0 = 0;
        if (i64(s0) > 0) {
            goto L_0054deec;
        }
        // 0x0054e024 (the shared epilogue, written out on this path)
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
L_0054deec:
    charge(ctx, 5);
    t3 = 0x7C0000;
    a3 = 0;
    v0 = addiu(t3, 4536);  // &0x7C11B8
    lh(t2, v0, 512);  // 0x7C13B8
    if (i64(s0) > 0) {
        // 0x0054df00
        charge(ctx, 2);
        t0 = v0;
        for (;;) {
            // 0x0054df08
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
        // 0x0054df54
        charge(ctx, 2);
        v0 = addiu(t3, 4536);
        a3 = 0;
    }
    // 0x0054df5c
    charge(ctx, 2);
    lh(t0, v0, 1024);
    if (i64(s0) > 0) {
        // 0x0054df64
        charge(ctx, 1);
        t1 = v0;
        for (;;) {
            // 0x0054df68
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
    // 0x0054dfb4
    charge(ctx, 4);
    v0 = addiu(t3, 4536);
    a3 = 0;
    lh(a0, v0, 1536);
    if (i64(s0) > 0) {
        // 0x0054dfc4
        charge(ctx, 1);
        t1 = v0;
        for (;;) {
            // 0x0054dfc8
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
    // 0x0054e014
    charge(ctx, 4);
    sh(t2, s2, 0);
    v0 = 0;
    sh(t0, s3, 0);
    sh(a0, s4, 0);
    // 0x0054e024 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0054E2C0 sub_54E2C0 -- 200 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// AHX: reset a decoder: clear its state tables, drop the header flag, and recreate the bit reader on the same joint
// (sub_551BB0 / sub_551AD8, 4116).
void sub_54E2C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054e2c0
    enter(ctx, 39);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 0;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    a0 = addiu(s0, 436);
    sd(ra, sp, 0x10);
    a2 = 48;
    link(ctx, 0x54E2E0u);  // $ra first: the delay slot below depends on it
    lw(s1, s0, 432);
    call(ctx, gen::fn_memset_00521408);
    a0 = addiu(s0, 484);
    a1 = 0;
    a2 = 60;
    jal(ctx, 0x54E2F0u, gen::fn_memset_00521408);
    a0 = addiu(s0, 544);
    a1 = 0;
    a2 = 256;
    jal(ctx, 0x54E300u, gen::fn_memset_00521408);
    a0 = addiu(s0, 800);
    a1 = 0;
    a2 = 256;
    jal(ctx, 0x54E310u, gen::fn_memset_00521408);
    a0 = addiu(s0, 1056);
    a1 = 0;
    a2 = 768;
    jal(ctx, 0x54E320u, gen::fn_memset_00521408);
    lw(a0, s0, 0);
    a1 = 0;
    a2 = 384;
    jal(ctx, 0x54E330u, gen::fn_memset_00521408);
    a0 = addiu(s0, 1824);
    a1 = 0;
    a2 = 768;
    jal(ctx, 0x54E340u, gen::fn_memset_00521408);
    sb(zero, s0, 421);
    lw(v0, s0, 432);
    sw(zero, s0, 424);
    a0 = v0;
    if (v0 != 0) {
        // 0x0054e35c
        charge(ctx, 6);
        link(ctx, 0x54E35Cu);  // $ra first: the delay slot below depends on it
        sw(zero, s0, 432);
        call(ctx, gen::fn_sub_551BB0_00551bb0);
        a0 = s1;
        a1 = 4116;
        jal(ctx, 0x54E368u, gen::fn_sub_551AD8_00551ad8);
        sw(v0, s0, 432);
    }
    // 0x0054e374 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0054E568 sub_54E568 -- 224 bytes; frame 0x30: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, ra sp+0x20
// AHX: read a frame header on the decoder's bit reader (+428): find the sync (sub_54DD08), check 20 bits (sub_54DAD8),
// then the header and the frame tables (sub_54E9A0 / sub_54EAD8 / sub_54EBC0 / sub_54ED48) into the record, set the
// header flag +421; returns 0, the sync result when it is not 1, or -1.
void sub_54E568(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054e568
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = si(-1);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    lw(v1, s2, 428);
    a0 = v1;
    if (v1 != 0) {
        // 0x0054e594
        charge(ctx, 6);
        jal(ctx, 0x54E594u, gen::fn_sub_54DD08_0054dd08);
        v1 = si(-1);
        a0 = v0;
        s3 = 1;
        if (a0 != v1) {
            // 0x0054e5ac
            charge(ctx, 2);
            v0 = 1;
            if (a0 == s3) {
                // 0x0054e5b4
                charge(ctx, 5);
                lw(a0, s2, 428);
                a1 = 20;
                jal(ctx, 0x54E5B8u, gen::fn_sub_54DAD8_0054dad8);
                s0 = addiu(s2, 436);
                if (v0 != 0) {
                    // 0x0054e5c8
                    charge(ctx, 5);
                    lw(a0, s2, 428);
                    a1 = s0;
                    jal(ctx, 0x54E5CCu, gen::fn_sub_54E9A0_0054e9a0);
                    a0 = s0;
                    if (i64(v0) < 0) {
                        goto L_0054e5dc;
                    }
                    // 0x0054e5e8
                    charge(ctx, 17);
                    s0 = addiu(s2, 484);
                    s1 = addiu(s2, 544);
                    a1 = s0;
                    jal(ctx, 0x54E5F0u, gen::fn_sub_54EAD8_0054ead8);
                    lw(a0, s2, 428);
                    a1 = s0;
                    a2 = s1;
                    jal(ctx, 0x54E600u, gen::fn_sub_54EBC0_0054ebc0);
                    lw(a0, s2, 428);
                    a1 = s0;
                    a2 = s1;
                    a3 = addiu(s2, 800);
                    t0 = addiu(s2, 1056);
                    jal(ctx, 0x54E618u, gen::fn_sub_54ED48_0054ed48);
                    sb(s3, s2, 421);
                    sw(zero, s2, 424);
                    v0 = 0;
                    // 0x0054e62c (the shared epilogue, written out on this path)
                    charge(ctx, 7);
                    ld(s0, sp, 0x0);
                    ld(s1, sp, 0x8);
                    ld(s2, sp, 0x10);
                    ld(s3, sp, 0x18);
                    ld(ra, sp, 0x20);
                    sp = addiu(sp, 0x30);
                    return;
                }
            L_0054e5dc:
                charge(ctx, 2);
                v0 = si(-1);
            }
        }
    }
    // 0x0054e62c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

}  // namespace p3fes::game
