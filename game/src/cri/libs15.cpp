// Slice libs15 (Phase 5): 100 CRI middleware functions of SLUS_216.21, hand-decompiled from p3fes_handgen bodies.
// Every body keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); on top of that each has its role, its proposed name where the binary's own
// strings give one, and the field offsets named in libs15.h (l15::). Groups, in address order: ADXT loop-play entry
// points and the ADXM threads (0x53F2D8..), the PS2RNA IOP commands (0x560240..), the ROFS / PFS front ends
// (0x566488..), the MPEG-2 video header parsers (0x570240..), MWSFD / MWPLY helpers (0x582BF0..), the WTLS hooks and the
// ADX stream input (0x584AB0..). Pair tests: tests/game/test_libs15.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs15.h"

namespace p3fes::recomp_gen {
void fn_DTX_CallUrpc_00559c10(p3fes::EEContext&);
void fn_PS2RNA_StartPcmTrans_00560558(p3fes::EEContext&);
void fn_PS2RNA_StopPcmTrans_005605e8(p3fes::EEContext&);
void fn_RFHN_StopTrG_00566180(p3fes::EEContext&);
void fn_ROFS_DelVolume_00566488(p3fes::EEContext&);
void fn_ROFS_LoadDir_00566a58(p3fes::EEContext&);
void fn_ROFS_StopTr_00566750(p3fes::EEContext&);
void fn_R_LOCK_DEF_w_lock_4_00586748(p3fes::EEContext&);
void fn_SVM_ExecSvrFs_00565420(p3fes::EEContext&);
void fn_WTLS_get_table_1_005851b0(p3fes::EEContext&);
void fn___env_lock_0_0054a630(p3fes::EEContext&);
void fn___gthread_get_ee_key_use_0057f740(p3fes::EEContext&);
void fn__get_peer_or_sock_name_0_005843e8(p3fes::EEContext&);
void fn__sceExitDeleteThread_00502fa0(p3fes::EEContext&);
void fn_adxm_goto_svr_border_0053f9b0(p3fes::EEContext&);
void fn_adxm_safe_proc_0053fb00(p3fes::EEContext&);
void fn_dcfReadBlk_0056a9e0(p3fes::EEContext&);
void fn_dcfReadCda_0056aac0(p3fes::EEContext&);
void fn_dcfReqRdBlk_0056a860(p3fes::EEContext&);
void fn_dcfReqRdCda_0056aa98(p3fes::EEContext&);
void fn_dcfStopTr_0056a660(p3fes::EEContext&);
void fn_dcfTell_0056a5a0(p3fes::EEContext&);
void fn_logf_0052ea30(p3fes::EEContext&);
void fn_memcmp_005211b8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_pfsCvfsStopTr_005657b8(p3fes::EEContext&);
void fn_rfpfs_waitRdComplete_0056ac28(p3fes::EEContext&);
void fn_sceInsockListen_2_00549160(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_19_005851a0(p3fes::EEContext&);
void fn_sinl_11_00585658(p3fes::EEContext&);
void fn_strncmp_00524670(p3fes::EEContext&);
void fn_sub_53AE08_0053ae08(p3fes::EEContext&);
void fn_sub_53DD10_0053dd10(p3fes::EEContext&);
void fn_sub_53DEF0_0053def0(p3fes::EEContext&);
void fn_sub_53EF40_0053ef40_at_0053efc0(p3fes::EEContext&);
void fn_sub_53F080_0053f080(p3fes::EEContext&);
void fn_sub_53F178_0053f178(p3fes::EEContext&);
void fn_sub_53F2D8_0053f2d8(p3fes::EEContext&);
void fn_sub_53F458_0053f458(p3fes::EEContext&);
void fn_sub_53F548_0053f548(p3fes::EEContext&);
void fn_sub_53F5B0_0053f5b0(p3fes::EEContext&);
void fn_sub_53F768_0053f768(p3fes::EEContext&);
void fn_sub_53FAC0_0053fac0(p3fes::EEContext&);
void fn_sub_53FAE8_0053fae8(p3fes::EEContext&);
void fn_sub_53FB58_0053fb58(p3fes::EEContext&);
void fn_sub_53FF20_0053ff20(p3fes::EEContext&);
void fn_sub_540098_00540098(p3fes::EEContext&);
void fn_sub_541760_00541760(p3fes::EEContext&);
void fn_sub_546EF0_00546ef0(p3fes::EEContext&);
void fn_sub_547008_00547008(p3fes::EEContext&);
void fn_sub_547068_00547068(p3fes::EEContext&);
void fn_sub_5492C8_005492c8(p3fes::EEContext&);
void fn_sub_549480_00549480(p3fes::EEContext&);
void fn_sub_549530_00549530(p3fes::EEContext&);
void fn_sub_54AC40_0054ac40(p3fes::EEContext&);
void fn_sub_54AC80_0054ac80(p3fes::EEContext&);
void fn_sub_5565B0_005565b0(p3fes::EEContext&);
void fn_sub_559B98_00559b98(p3fes::EEContext&);
void fn_sub_55D428_0055d428(p3fes::EEContext&);
void fn_sub_55D5C0_0055d5c0(p3fes::EEContext&);
void fn_sub_55D668_0055d668(p3fes::EEContext&);
void fn_sub_55D7C0_0055d7c0(p3fes::EEContext&);
void fn_sub_55D7F0_0055d7f0(p3fes::EEContext&);
void fn_sub_55D880_0055d880(p3fes::EEContext&);
void fn_sub_55DB58_0055db58(p3fes::EEContext&);
void fn_sub_560240_00560240(p3fes::EEContext&);
void fn_sub_560378_00560378(p3fes::EEContext&);
void fn_sub_5603D8_005603d8(p3fes::EEContext&);
void fn_sub_560448_00560448(p3fes::EEContext&);
void fn_sub_560BE0_00560be0(p3fes::EEContext&);
void fn_sub_560C28_00560c28(p3fes::EEContext&);
void fn_sub_560C88_00560c88(p3fes::EEContext&);
void fn_sub_560D20_00560d20(p3fes::EEContext&);
void fn_sub_5611E0_005611e0(p3fes::EEContext&);
void fn_sub_5615B0_005615b0(p3fes::EEContext&);
void fn_sub_561640_00561640(p3fes::EEContext&);
void fn_sub_561688_00561688(p3fes::EEContext&);
void fn_sub_5616C8_005616c8(p3fes::EEContext&);
void fn_sub_563D20_00563d20(p3fes::EEContext&);
void fn_sub_563E30_00563e30(p3fes::EEContext&);
void fn_sub_564038_00564038(p3fes::EEContext&);
void fn_sub_564320_00564320(p3fes::EEContext&);
void fn_sub_564830_00564830(p3fes::EEContext&);
void fn_sub_564B50_00564b50(p3fes::EEContext&);
void fn_sub_564EF8_00564ef8(p3fes::EEContext&);
void fn_sub_5653C0_005653c0(p3fes::EEContext&);
void fn_sub_5653D8_005653d8(p3fes::EEContext&);
void fn_sub_5653F0_005653f0(p3fes::EEContext&);
void fn_sub_565408_00565408(p3fes::EEContext&);
void fn_sub_565438_00565438(p3fes::EEContext&);
void fn_sub_565450_00565450(p3fes::EEContext&);
void fn_sub_565468_00565468(p3fes::EEContext&);
void fn_sub_565590_00565590(p3fes::EEContext&);
void fn_sub_565690_00565690(p3fes::EEContext&);
void fn_sub_5662C8_005662c8(p3fes::EEContext&);
void fn_sub_566848_00566848(p3fes::EEContext&);
void fn_sub_5668B8_005668b8(p3fes::EEContext&);
void fn_sub_566938_00566938(p3fes::EEContext&);
void fn_sub_566C20_00566c20(p3fes::EEContext&);
void fn_sub_566CB8_00566cb8(p3fes::EEContext&);
void fn_sub_566D28_00566d28(p3fes::EEContext&);
void fn_sub_569730_00569730(p3fes::EEContext&);
void fn_sub_569810_00569810(p3fes::EEContext&);
void fn_sub_56A538_0056a538(p3fes::EEContext&);
void fn_sub_56CA60_0056ca60(p3fes::EEContext&);
void fn_sub_56CA80_0056ca80(p3fes::EEContext&);
void fn_sub_56CA98_0056ca98(p3fes::EEContext&);
void fn_sub_570240_00570240(p3fes::EEContext&);
void fn_sub_570248_00570248(p3fes::EEContext&);
void fn_sub_5702F8_005702f8(p3fes::EEContext&);
void fn_sub_570348_00570348(p3fes::EEContext&);
void fn_sub_5703B8_005703b8(p3fes::EEContext&);
void fn_sub_5703C0_005703c0(p3fes::EEContext&);
void fn_sub_570B98_00570b98(p3fes::EEContext&);
void fn_sub_570CB8_00570cb8(p3fes::EEContext&);
void fn_sub_570ED0_00570ed0(p3fes::EEContext&);
void fn_sub_571048_00571048(p3fes::EEContext&);
void fn_sub_571088_00571088(p3fes::EEContext&);
void fn_sub_574068_00574068(p3fes::EEContext&);
void fn_sub_5745D0_005745d0(p3fes::EEContext&);
void fn_sub_577FC8_00577fc8(p3fes::EEContext&);
void fn_sub_578160_00578160(p3fes::EEContext&);
void fn_sub_578378_00578378(p3fes::EEContext&);
void fn_sub_578820_00578820(p3fes::EEContext&);
void fn_sub_57BAF0_0057baf0(p3fes::EEContext&);
void fn_sub_581798_00581798(p3fes::EEContext&);
void fn_sub_582BF0_00582bf0(p3fes::EEContext&);
void fn_sub_582C68_00582c68(p3fes::EEContext&);
void fn_sub_582CD8_00582cd8(p3fes::EEContext&);
void fn_sub_582D48_00582d48(p3fes::EEContext&);
void fn_sub_5833D8_005833d8(p3fes::EEContext&);
void fn_sub_583848_00583848(p3fes::EEContext&);
void fn_sub_584400_00584400(p3fes::EEContext&);
void fn_sub_584558_00584558(p3fes::EEContext&);
void fn_sub_584748_00584748(p3fes::EEContext&);
void fn_sub_584760_00584760(p3fes::EEContext&);
void fn_sub_5849D0_005849d0(p3fes::EEContext&);
void fn_sub_584AB0_00584ab0(p3fes::EEContext&);
void fn_sub_584B78_00584b78(p3fes::EEContext&);
void fn_sub_584BE0_00584be0(p3fes::EEContext&);
void fn_sub_584E68_00584e68(p3fes::EEContext&);
void fn_sub_584EC8_00584ec8(p3fes::EEContext&);
void fn_sub_5851D0_005851d0(p3fes::EEContext&);
void fn_sub_585250_00585250(p3fes::EEContext&);
void fn_sub_585340_00585340(p3fes::EEContext&);
void fn_sub_585398_00585398(p3fes::EEContext&);
void fn_sub_5853F0_005853f0(p3fes::EEContext&);
void fn_sub_585440_00585440(p3fes::EEContext&);
void fn_sub_585590_00585590(p3fes::EEContext&);
void fn_sub_586110_00586110(p3fes::EEContext&);
void fn_sub_586300_00586300(p3fes::EEContext&);
void fn_sub_586308_00586308(p3fes::EEContext&);
void fn_sub_586450_00586450(p3fes::EEContext&);
void fn_sub_586468_00586468(p3fes::EEContext&);
void fn_sub_586628_00586628(p3fes::EEContext&);
void fn_sub_5866C8_005866c8(p3fes::EEContext&);
void fn_sub_5866E8_005866e8(p3fes::EEContext&);
void fn_sub_586708_00586708(p3fes::EEContext&);
void fn_sub_586728_00586728(p3fes::EEContext&);
void fn_sub_586C10_00586c10(p3fes::EEContext&);
void fn_sub_586E78_00586e78(p3fes::EEContext&);
void fn_sub_586F00_00586f00(p3fes::EEContext&);
void fn_sub_587100_00587100(p3fes::EEContext&);
void fn_sub_587218_00587218(p3fes::EEContext&);
void fn_sub_587FD8_00587fd8(p3fes::EEContext&);
void fn_sub_588360_00588360(p3fes::EEContext&);
void fn_sub_588568_00588568(p3fes::EEContext&);
void fn_sub_588640_00588640(p3fes::EEContext&);
void fn_sub_588698_00588698(p3fes::EEContext&);
void fn_sub_58BBB0_0058bbb0(p3fes::EEContext&);
void fn_sub_58BE40_0058be40(p3fes::EEContext&);
void fn_sub_599240_00599240(p3fes::EEContext&);
void fn_sub_599408_00599408(p3fes::EEContext&);
void fn_sub_599EC8_00599ec8(p3fes::EEContext&);
void fn_sub_599F28_00599f28(p3fes::EEContext&);
void fn_sub_599FA0_00599fa0(p3fes::EEContext&);
void fn_sub_59AD40_0059ad40(p3fes::EEContext&);
void fn_sub_59BC20_0059bc20(p3fes::EEContext&);
void fn_sub_59C8E0_0059c8e0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
namespace L15 = ::p3fes::game::l15;

// 0x0053F2D8 sub_53F2D8 -- 300 bytes; frame 0x10: ra sp+0x0
// [proposed adxt_StartFnameLp] Loop-plays a whole file: $a2 = 0, $a3 = 0xFFFFF, then falls into the body of
// adxt_StartFnameRangeLp (0x53F358; named by its error text): a null handle or name reports "E02080852
// adxt_StartFnameRangeLp: parameter error" (sub_53AE08); else it locks the handle's stream (+adxt::kStm, sub_55D668),
// registers the range (sub_53EF40's entry 0x53EFC0), marks it (sub_55DB58(stm, 1)) and starts the handle (sub_53F178,
// tail call).
void sub_53F2D8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f2d8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = 0xF0000;
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = a3 | 0xFFFF;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0053f358
    charge(ctx, 12);
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(s4, sp, 0x20);
    s4 = a3;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x28);
    if (s1 != 0) {
        // 0x0053f388
        charge(ctx, 2);
        if (s2 == 0) {
            goto L_0053f390;
        }
        lw(s0, s1, L15::adxt::kStm);
        // 0x0053f3b8
        charge(ctx, 19);
        a0 = s0;
        jal(ctx, 0x53F3B8u, gen::fn_sub_55D668_0055d668);
        a0 = s1;
        a2 = s3;
        a3 = s4;
        a1 = s2;
        link(ctx, 0x53F3CCu);
        gen::fn_sub_53EF40_0053ef40_at_0053efc0(ctx);
        a0 = s0;
        a1 = 1;
        jal(ctx, 0x53F3D8u, gen::fn_sub_55DB58_0055db58);
        a0 = s1;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        gen::fn_sub_53F178_0053f178(ctx);  // tail call
        return;
    }
L_0053f390:
    charge(ctx, 10);
    a0 = 0x7C0000;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a0 = addiu(a0, 9208);  // "E02080852 adxt_StartFnameRangeLp: parameter error"
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
}

// 0x0053F458 sub_53F458 -- 172 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// [proposed adxt_StartAfsLp] Loop-plays an AFS partition / file: a null handle, a partition id > 0 or a file id >
// 0x10000 reports "E0405100 adxt_StartAfsLp: parameter error"; else lock the stream, register the entry (sub_53F080),
// mark it (sub_55DB58(stm, 1)) and start the handle (sub_53F178, tail call).
void sub_53F458(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f458
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    if (s1 != 0) {
        // 0x0053f480
        charge(ctx, 2);
        if (i64(s2) > 0) {
            a0 = 0x7C0000;
        L_0053f49c:
            charge(ctx, 8);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            a0 = addiu(a0, 9264);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
            return;
        }
        // 0x0053f488
        charge(ctx, 4);
        v0 = 0x10000;
        v0 = sltu(v0, s3);
        if (v0 != 0) {
            goto L_0053f498;
        }
        lw(s0, s1, L15::adxt::kStm);
        // 0x0053f4c0
        charge(ctx, 17);
        a0 = s0;
        jal(ctx, 0x53F4C0u, gen::fn_sub_55D668_0055d668);
        a0 = s1;
        a2 = s3;
        a1 = s2;
        jal(ctx, 0x53F4D0u, gen::fn_sub_53F080_0053f080);
        a0 = s0;
        a1 = 1;
        jal(ctx, 0x53F4DCu, gen::fn_sub_55DB58_0055db58);
        a0 = s1;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_53F178_0053f178(ctx);  // tail call
        return;
    }
L_0053f498:
    charge(ctx, 1);
    a0 = 0x7C0000;
    goto L_0053f49c;
}

// 0x0053F548 sub_53F548 -- 56 bytes; frame 0x10: ra sp+0x0
// [proposed adxt_GetNumFiles] The number of entries in the handle's loop list (sub_55D7C0 on +adxt::kStm, tail call);
// a null handle reports "E02080854 adxt_GetNumFiles: parameter error" and returns -1.
void sub_53F548(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f548
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0053f570
        charge(ctx, 4);
        lw(a0, a0, L15::adxt::kStm);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_sub_55D7C0_0055d7c0(ctx);  // tail call
        return;
    }
    // 0x0053f554
    charge(ctx, 7);
    a0 = 0x7C0000;
    a0 = addiu(a0, 9312);  // "E02080854 adxt_GetNumFiles: parameter error"
    jal(ctx, 0x53F558u, gen::fn_sub_53AE08_0053ae08);
    v0 = si(-1);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053F5B0 sub_53F5B0 -- 64 bytes; frame 0x10: ra sp+0x0
// [proposed adxt_ResetEntry] Clears the handle's loop list (sub_55D5C0 on +adxt::kStm) while the status byte +1 is 0;
// otherwise returns that byte. A null handle reports "E02080849 adxt_ResetEntry: parameter error".
void sub_53F5B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f5b0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0053f5bc
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 9360);  // "E02080849 adxt_ResetEntry: parameter error"
        sp = addiu(sp, 0x10);
        gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
        return;
    }
    // 0x0053f5d0
    charge(ctx, 3);
    lb(v0, a0, L15::adxt::kStat);
    ld(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0053f5e8
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0053f5dc
    charge(ctx, 3);
    lw(a0, a0, L15::adxt::kStm);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55D5C0_0055d5c0(ctx);  // tail call
}

// 0x0053F768 sub_53F768 -- 88 bytes; frame 0x10: ra sp+0x0
// The ADXM file-system server pass: runs the eight SVM server steps once (sub_5653C0, sub_5653D8, sub_5653F0,
// sub_565408, SVM_ExecSvrFs, sub_565438, sub_565450, sub_565468) and returns 0.
void sub_53F768(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f768
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x53F770u, gen::fn_sub_5653C0_005653c0);
    jal(ctx, 0x53F778u, gen::fn_sub_5653D8_005653d8);
    jal(ctx, 0x53F780u, gen::fn_sub_5653F0_005653f0);
    jal(ctx, 0x53F788u, gen::fn_sub_565408_00565408);
    jal(ctx, 0x53F790u, gen::fn_SVM_ExecSvrFs_00565420);
    jal(ctx, 0x53F798u, gen::fn_sub_565438_00565438);
    jal(ctx, 0x53F7A0u, gen::fn_sub_565450_00565450);
    jal(ctx, 0x53F7A8u, gen::fn_sub_565468_00565468);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053FAC0 sub_53FAC0 -- 40 bytes; frame 0x10: ra sp+0x0
// Thread entry: adxm_goto_svr_border(*0x7886F0, *0x78866C) (tail call).
void sub_53FAC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053fac0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(ra, sp, 0x0);
    v1 = 0x790000;
    v0 = addiu(v0, -30992);  // &0x7886F0
    lw(a1, v1, -31124);  // 0x78866C
    lw(a0, v0, 0);  // 0x7886F0
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_adxm_goto_svr_border_0053f9b0(ctx);  // tail call
}

// 0x0053FAE8 sub_53FAE8 -- 24 bytes; leaf frame (no stack)
// The safe thread's idle step: ++ the 64-bit counter 0x7886A0.
void sub_53FAE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x0053fae8
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x790000;
    v1 = addiu(v1, -31072);  // &0x7886A0
    ld(v0, v1, 0);  // 0x7886A0
    v0 = daddiu(v0, 1);
    sd(v0, v1, 0);  // 0x7886A0
}

// 0x0053FB00 adxm_safe_proc -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The ADXM safe thread: runs sub_53FAE8 until the stop word 0x7886F8 (64-bit) is set, then sets the done word 0x788700
// = 1 and ends the thread (_sceExitDeleteThread, tail call).
void adxm_safe_proc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0053fb00
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    v0 = addiu(v0, -30984);  // &0x7886F8
    sd(ra, sp, 0x8);
    ld(v1, v0, 0);  // 0x7886F8
    if (v1 != 0) {
        v0 = 0x790000;
    } else {
        // 0x0053fb20
        charge(ctx, 2);
        s0 = v0;
        for (;;) {
            // 0x0053fb28
            charge(ctx, 5);
            jal(ctx, 0x53FB28u, gen::fn_sub_53FAE8_0053fae8);
            ld(v0, s0, 0);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 0x790000;
            if (!cc) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0053fb3c
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    v1 = 1;
    v0 = addiu(v0, -30976);
    sd(v1, v0, 0);
    sp = addiu(sp, 0x10);
    gen::fn__sceExitDeleteThread_00502fa0(ctx);  // tail call
}

// 0x0053FB58 sub_53FB58 -- 152 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// An ADXM server thread: until the stop word 0x788708 is set: ++ the pass counter 0x7886A8, busy 0x78868C = 1, one
// server pass (sub_5653D8), busy = 0, sleep (sub_540098). Then done 0x788710 = 1 and _sceExitDeleteThread (tail call).
void sub_53FB58(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0053fb58
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    a0 = addiu(v0, -30968);  // &0x788708
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    ld(v1, a0, 0);  // 0x788708
    v0 = 0x790000;
    if (v1 == 0) {
        // 0x0053fb84
        charge(ctx, 7);
        v0 = 0x790000;
        v1 = 0x790000;
        s1 = addiu(v0, -31064);  // &0x7886A8
        s0 = addiu(v1, -31092);  // &0x78868C
        s3 = a0;
        s2 = 1;
        for (;;) {
            // 0x0053fba0
            charge(ctx, 10);
            ld(v0, s1, 0);
            v0 = daddiu(v0, 1);
            sd(v0, s1, 0);
            link(ctx, 0x53FBACu);  // $ra first: the delay slot below depends on it
            sw(s2, s0, 0);
            call(ctx, gen::fn_sub_5653D8_005653d8);
            link(ctx, 0x53FBB4u);  // $ra first: the delay slot below depends on it
            sw(zero, s0, 0);
            call(ctx, gen::fn_sub_540098_00540098);
            ld(v0, s3, 0);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 0x790000;
            if (!cc) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0053fbc8
    charge(ctx, 10);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v1 = 1;
    ld(s2, sp, 0x10);
    v0 = addiu(v0, -30960);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sd(v1, v0, 0);
    sp = addiu(sp, 0x30);
    gen::fn__sceExitDeleteThread_00502fa0(ctx);  // tail call
}

// 0x0053FF20 sub_53FF20 -- 212 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// The ADXM file-system thread: until the stop word 0x788748 is set: ++ 0x7886C8, busy 0x788698 = 1, r = sub_565468(),
// busy = 0; a pending wake request (0x788684 == 1) is cleared with one sleep (sub_540098), and r == 0 (nothing served)
// sleeps once more. Then done 0x788750 = 1 and _sceExitDeleteThread (tail call).
void sub_53FF20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0053ff20
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    a1 = addiu(v0, -30904);  // &0x788748
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x30);
    ld(v1, a1, 0);  // 0x788748
    v0 = 0x790000;
    if (v1 == 0) {
        // 0x0053ff54
        charge(ctx, 9);
        v0 = 0x790000;
        v1 = 0x790000;
        a0 = 0x790000;
        s4 = addiu(v0, -31032);  // &0x7886C8
        s3 = addiu(v1, -31080);  // &0x788698
        s2 = addiu(a0, -31100);  // &0x788684
        s5 = a1;
        s1 = 1;
        for (;;) {
            // 0x0053ff78
            charge(ctx, 10);
            ld(v0, s4, 0);
            v0 = daddiu(v0, 1);
            sd(v0, s4, 0);
            link(ctx, 0x53FF84u);  // $ra first: the delay slot below depends on it
            sw(s1, s3, 0);
            call(ctx, gen::fn_sub_565468_00565468);
            sw(zero, s3, 0);
            s0 = v0;
            lw(v0, s2, 0);
            if (v0 == s1) {
                // 0x0053ffa0
                charge(ctx, 2);
                link(ctx, 0x53FFA0u);  // $ra first: the delay slot below depends on it
                sw(zero, s2, 0);
                call(ctx, gen::fn_sub_540098_00540098);
            }
            // 0x0053ffa8
            charge(ctx, 2);
            if (s0 == 0) {
                // 0x0053ffb0
                charge(ctx, 2);
                jal(ctx, 0x53FFB0u, gen::fn_sub_540098_00540098);
            }
            // 0x0053ffb8
            charge(ctx, 3);
            ld(v0, s5, 0);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 0x790000;
            if (!cc) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0053ffc4
    charge(ctx, 12);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v1 = 1;
    ld(s2, sp, 0x10);
    v0 = addiu(v0, -30896);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sd(v1, v0, 0);
    sp = addiu(sp, 0x40);
    gen::fn__sceExitDeleteThread_00502fa0(ctx);  // tail call
}

// 0x00560240 sub_560240 -- 84 bytes; frame 0x20: ra sp+0x10
// PS2RNA: sends IOP command 11 with one word ($a0, staged at sp+0) through DTX_CallUrpc. The RNA guard first: with the
// mode word 0x7A93F8 == 1 and the count 0x7A93F0 <= 0 it returns at once ($v0 as the guard left it).
void sub_560240(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00560240
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x20);
    lw(v1, v0, -27656);  // 0x7A93F8
    a1 = 1;
    t1 = a0;
    a0 = 11;
    sd(ra, sp, 0x10);
    if (v1 == a1) {
        // 0x00560260
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        if (i64(v1) > 0) {
            goto L_00560270;
        }
        ld(ra, sp, 0x10);
        // 0x0056028c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x20);
        return;
    }
L_00560270:
    charge(ctx, 7);
    a1 = sp;
    a2 = 1;
    a3 = 0;
    t0 = 0;
    link(ctx, 0x560280u);  // $ra first: the delay slot below depends on it
    sw(t1, sp, 0x0);
    call(ctx, gen::fn_DTX_CallUrpc_00559c10);
    ld(ra, sp, 0x10);
    // 0x0056028c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x20);
}

// 0x00560378 sub_560378 -- 92 bytes; frame 0x10: ra sp+0x0
// PS2RNA: IOP command 13 without arguments, then clears both PCM-transfer flags 0x7A9430 / 0x7A9434. The RNA guard
// first: with the mode word 0x7A93F8 == 1 and the count 0x7A93F0 <= 0 it returns at once ($v0 as the guard left it).
void sub_560378(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00560378
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -27656);  // 0x7A93F8
    a0 = 1;
    sd(ra, sp, 0x0);
    if (v1 == a0) {
        // 0x00560390
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        if (i64(v1) > 0) {
            goto L_005603a0;
        }
        ld(ra, sp, 0x0);
        // 0x005603cc (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_005603a0:
    charge(ctx, 11);
    a0 = 13;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x5603B0u, gen::fn_DTX_CallUrpc_00559c10);
    v1 = 0x7B0000;
    v1 = addiu(v1, -27600);  // &0x7A9430
    sw(zero, v1, 4);  // 0x7A9434
    sw(zero, v1, 0);  // 0x7A9430
    ld(ra, sp, 0x0);
    // 0x005603cc (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x005603D8 sub_5603D8 -- 112 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// PS2RNA: IOP command 14 once: only when the flag 0x7A9420 is not 1, which it then sets. The RNA guard first: with the
// mode word 0x7A93F8 == 1 and the count 0x7A93F0 <= 0 it returns at once ($v0 as the guard left it).
void sub_5603D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005603d8
    enter(ctx, 8);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    sp = addiu(sp, -0x20);
    lw(v0, v1, -27656);  // 0x7A93F8
    sd(s0, sp, 0x0);
    s0 = 1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    if (v0 == s0) {
        // 0x005603f8
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        if (i64(v1) > 0) {
            goto L_00560408;
        }
        ld(s0, sp, 0x0);
        // 0x00560438 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_00560408:
    charge(ctx, 5);
    v0 = 0x7B0000;
    s1 = addiu(v0, -27616);  // &0x7A9420
    lw(v1, s1, 0);  // 0x7A9420
    a0 = 14;
    if (v1 != s0) {
        // 0x0056041c
        charge(ctx, 6);
        a1 = 0;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x560428u, gen::fn_DTX_CallUrpc_00559c10);
        sw(s0, s1, 0);
    }
    // 0x00560434
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x00560438 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00560448 sub_560448 -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// PS2RNA: IOP command 15 when the flag 0x7A9420 is set, which it then clears (the undo of sub_5603D8). The RNA guard
// first: with the mode word 0x7A93F8 == 1 and the count 0x7A93F0 <= 0 it returns at once ($v0 as the guard left it).
void sub_560448(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00560448
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -27656);  // 0x7A93F8
    a0 = 1;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    if (v1 == a0) {
        // 0x00560464
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        ld(s0, sp, 0x0);
        if (i64(v1) > 0) {
            goto L_00560474;
        }
        // 0x005604a4 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_00560474:
    charge(ctx, 5);
    v0 = 0x7B0000;
    s0 = addiu(v0, -27616);  // &0x7A9420
    lw(v1, s0, 0);  // 0x7A9420
    a0 = 15;
    if (v1 != 0) {
        // 0x00560488
        charge(ctx, 6);
        a1 = 0;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x560494u, gen::fn_DTX_CallUrpc_00559c10);
        sw(zero, s0, 0);
    }
    // 0x005604a0
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x005604a4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00560558 PS2RNA_StartPcmTrans -- 140 bytes; frame 0x30: s1 sp+0x18, s0 sp+0x10, ra sp+0x20
// Starts the PCM transfer of channel $a0 (0 or 1; others do nothing): IOP command 16 with the channel, then the
// channel's flag 0x7A9430[ch] = 1; skipped when the flag is already 1. The RNA guard first: with the mode word
// 0x7A93F8 == 1 and the count 0x7A93F0 <= 0 it returns at once ($v0 as the guard left it).
void PS2RNA_StartPcmTrans(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00560558
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x30);
    lw(v1, v0, -27656);  // 0x7A93F8
    t1 = a0;
    sd(s1, sp, 0x18);
    s1 = 1;
    sd(s0, sp, 0x10);
    a0 = sltiu(t1, 2);
    sd(ra, sp, 0x20);
    if (v1 == s1) {
        // 0x00560580
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        ld(s0, sp, 0x10);
        if (i64(v1) > 0) {
            goto L_00560590;
        }
        // 0x005605d4 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_00560590:
    charge(ctx, 2);
    ld(s0, sp, 0x10);
    if (a0 != 0) {
        // 0x00560598
        charge(ctx, 7);
        v0 = sll(t1, 2);
        s0 = 0x7B0000;
        s0 = addiu(s0, -27600);  // &0x7A9430
        s0 = addu(s0, v0);
        lw(v1, s0, 0);
        a0 = 16;
        if (v1 != s1) {
            // 0x005605b4
            charge(ctx, 7);
            a1 = sp;
            a2 = 1;
            a3 = 0;
            t0 = 0;
            link(ctx, 0x5605C4u);  // $ra first: the delay slot below depends on it
            sw(t1, sp, 0x0);
            call(ctx, gen::fn_DTX_CallUrpc_00559c10);
            sw(s1, s0, 0);
        }
        // 0x005605d0
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    }
    // 0x005605d4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005605E8 PS2RNA_StopPcmTrans -- 132 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// Stops the PCM transfer of channel $a0 (0 or 1): IOP command 17 with the channel, then the flag 0x7A9430[ch] = 0;
// skipped when the flag is already 0. The RNA guard first: with the mode word 0x7A93F8 == 1 and the count 0x7A93F0 <=
// 0 it returns at once ($v0 as the guard left it).
void PS2RNA_StopPcmTrans(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005605e8
    enter(ctx, 9);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x20);
    lw(v1, v0, -27656);  // 0x7A93F8
    t1 = a0;
    a1 = 1;
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x18);
    a0 = sltiu(t1, 2);
    if (v1 == a1) {
        // 0x0056060c
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        ld(s0, sp, 0x10);
        if (i64(v1) > 0) {
            goto L_0056061c;
        }
        // 0x00560660 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0056061c:
    charge(ctx, 2);
    ld(s0, sp, 0x10);
    if (a0 != 0) {
        // 0x00560624
        charge(ctx, 7);
        v0 = sll(t1, 2);
        s0 = 0x7B0000;
        s0 = addiu(s0, -27600);  // &0x7A9430
        s0 = addu(s0, v0);
        lw(v1, s0, 0);
        a0 = 17;
        if (v1 != 0) {
            // 0x00560640
            charge(ctx, 7);
            a1 = sp;
            a2 = 1;
            a3 = 0;
            t0 = 0;
            link(ctx, 0x560650u);  // $ra first: the delay slot below depends on it
            sw(t1, sp, 0x0);
            call(ctx, gen::fn_DTX_CallUrpc_00559c10);
            sw(zero, s0, 0);
        }
        // 0x0056065c
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    }
    // 0x00560660 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00560BE0 sub_560BE0 -- 72 bytes; frame 0x10: ra sp+0x0
// [proposed PS2RNA_Start] A stub: prints "PS2RNA_Start: not implemented" (sub_541760, tail call). The RNA guard first:
// with the mode word 0x7A93F8 == 1 and the count 0x7A93F0 <= 0 it returns at once ($v0 as the guard left it).
void sub_560BE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00560be0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -27656);  // 0x7A93F8
    a0 = 1;
    sd(ra, sp, 0x0);
    if (v1 == a0) {
        // 0x00560bf8
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        ld(ra, sp, 0x0);
        if (i64(v1) > 0) {
            goto L_00560c08;
        }
        // 0x00560c20
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_00560c08:
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 26096);  // "PS2RNA_Start: not implemented\n"
    sp = addiu(sp, 0x10);
    gen::fn_sub_541760_00541760(ctx);  // tail call
}

// 0x00560C28 sub_560C28 -- 92 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// PS2RNA: runs sub_560C88(h, 0) then sub_560D20(h, 0) (tail call) on the handle $a0. The RNA guard first: with the
// mode word 0x7A93F8 == 1 and the count 0x7A93F0 <= 0 it returns at once ($v0 as the guard left it).
void sub_560C28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00560c28
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -27656);  // 0x7A93F8
    a1 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (v1 == a1) {
        // 0x00560c48
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        if (i64(v1) > 0) {
            goto L_00560c58;
        }
        ld(s0, sp, 0x0);
        // 0x00560c78
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_00560c58:
    charge(ctx, 8);
    a1 = 0;
    jal(ctx, 0x560C58u, gen::fn_sub_560C88_00560c88);
    a0 = s0;
    ld(ra, sp, 0x8);
    a1 = 0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_560D20_00560d20(ctx);  // tail call
}

// 0x005611E0 sub_5611E0 -- 72 bytes; frame 0x10: ra sp+0x0
// [proposed PS2RNA_SetStartSmpl] A stub: prints "PS2RNA_SetStartSmpl: not implemented" (tail call). The RNA guard
// first: with the mode word 0x7A93F8 == 1 and the count 0x7A93F0 <= 0 it returns at once ($v0 as the guard left it).
void sub_5611E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005611e0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -27656);  // 0x7A93F8
    a0 = 1;
    sd(ra, sp, 0x0);
    if (v1 == a0) {
        // 0x005611f8
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        ld(ra, sp, 0x0);
        if (i64(v1) > 0) {
            goto L_00561208;
        }
        // 0x00561220
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_00561208:
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 26208);  // "PS2RNA_SetStartSmpl: not implemented\n"
    sp = addiu(sp, 0x10);
    gen::fn_sub_541760_00541760(ctx);  // tail call
}

// 0x005615B0 sub_5615B0 -- 68 bytes; frame 0x10: ra sp+0x0
// [proposed PS2RNA_DiscardData] A stub: prints "PS2RNA_DiscardData: not implemented" and returns 0. The RNA guard
// first: with the mode word 0x7A93F8 == 1 and the count 0x7A93F0 <= 0 it returns at once ($v0 as the guard left it).
void sub_5615B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005615b0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -27656);  // 0x7A93F8
    a0 = 1;
    sd(ra, sp, 0x0);
    if (v1 == a0) {
        // 0x005615c8
        charge(ctx, 4);
        a0 = 0x7B0000;
        lw(v1, a0, -27664);  // 0x7A93F0
        v0 = 0;
        if (i64(v1) > 0) {
            goto L_005615d8;
        }
        // 0x005615e8 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_005615d8:
    charge(ctx, 4);
    a0 = 0x7C0000;
    a0 = addiu(a0, 26480);  // "PS2RNA_DiscardData: not implemented\n"
    jal(ctx, 0x5615DCu, gen::fn_sub_541760_00541760);
    v0 = 0;
    // 0x005615e8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00561640 sub_561640 -- 68 bytes; frame 0x10: ra sp+0x0
// [proposed PS2RNA_SetStmHdInfo] A stub: prints "PS2RNA_SetStmHdInfo: not implemented" and returns 0. The RNA guard
// first: with the mode word 0x7A93F8 == 1 and the count 0x7A93F0 <= 0 it returns at once ($v0 as the guard left it).
void sub_561640(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561640
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -27656);  // 0x7A93F8
    a0 = 1;
    sd(ra, sp, 0x0);
    if (v1 == a0) {
        // 0x00561658
        charge(ctx, 4);
        a0 = 0x7B0000;
        lw(v1, a0, -27664);  // 0x7A93F0
        v0 = 0;
        if (i64(v1) > 0) {
            goto L_00561668;
        }
        // 0x00561678 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_00561668:
    charge(ctx, 4);
    a0 = 0x7C0000;
    a0 = addiu(a0, 26568);  // "PS2RNA_SetStmHdInfo: not implemented\n"
    jal(ctx, 0x56166Cu, gen::fn_sub_541760_00541760);
    v0 = 0;
    // 0x00561678 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00561688 sub_561688 -- 60 bytes; leaf frame (no stack)
// PS2RNA: channel $a1's record (*(h + 8 + 4 * ch)) word +8. The RNA guard first: with the mode word 0x7A93F8 == 1 and
// the count 0x7A93F0 <= 0 it returns at once ($v0 as the guard left it). (Then $v0 = 0.)
void sub_561688(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00561688
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    a2 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8
    a3 = a0;
    a1 = sll(a1, 2);
    if (v1 == a2) {
        // 0x005616a0
        charge(ctx, 4);
        a0 = 0x7B0000;
        lw(v1, a0, -27664);  // 0x7A93F0
        v0 = 0;
        if (i64(v1) > 0) {
            goto L_005616b0;
        }
        // 0x005616bc (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_005616b0:
    charge(ctx, 3);
    v0 = addu(a3, a1);
    lw(v1, v0, 8);
    lw(v0, v1, 8);
    // 0x005616bc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005616C8 sub_5616C8 -- 60 bytes; leaf frame (no stack)
// PS2RNA: channel $a1's record (*(h + 8 + 4 * ch)) word +4. The RNA guard first: with the mode word 0x7A93F8 == 1 and
// the count 0x7A93F0 <= 0 it returns at once ($v0 as the guard left it). (Then $v0 = 0.)
void sub_5616C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x005616c8
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    a2 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8
    a3 = a0;
    a1 = sll(a1, 2);
    if (v1 == a2) {
        // 0x005616e0
        charge(ctx, 4);
        a0 = 0x7B0000;
        lw(v1, a0, -27664);  // 0x7A93F0
        v0 = 0;
        if (i64(v1) > 0) {
            goto L_005616f0;
        }
        // 0x005616fc (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_005616f0:
    charge(ctx, 3);
    v0 = addu(a3, a1);
    lw(v1, v0, 8);
    lw(v0, v1, 4);
    // 0x005616fc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00563E30 sub_563E30 -- 52 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Fills a two-word view of the object $a0: out[0] = $a0 + 16, out[1] = sub_563D20($a0 + 8).
void sub_563E30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00563e30
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = addiu(a0, 16);
    sd(s0, sp, 0x0);
    s0 = a1;
    sw(v0, s0, 0);
    sd(ra, sp, 0x8);
    a0 = addiu(a0, 8);
    jal(ctx, 0x563E48u, gen::fn_sub_563D20_00563d20);
    sw(v0, s0, 4);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00564038 sub_564038 -- 48 bytes; frame 0x10: ra sp+0x0
// Stores $a0 in the RPC word 0x999C00 and sends IOP command 35 with it (DTX_CallUrpc, tail call).
void sub_564038(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564038
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0x9A0000;
    sd(ra, sp, 0x0);
    a1 = addiu(a1, -25600);  // &0x999C00
    sw(a0, a1, 0);  // 0x999C00
    a0 = 35;
    ld(ra, sp, 0x0);
    a2 = 1;
    a3 = 0;
    t0 = 0;
    sp = addiu(sp, 0x10);
    gen::fn_DTX_CallUrpc_00559c10(ctx);  // tail call
}

// 0x00564320 sub_564320 -- 60 bytes; frame 0x10: ra sp+0x0
// Drops one reference from the counter 0x7B1AB4; the last one runs sub_559B98 (tail call).
void sub_564320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564320
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x7B0000;
    sd(ra, sp, 0x0);
    v1 = addiu(v1, 6836);  // &0x7B1AB4
    lw(v0, v1, 0);  // 0x7B1AB4
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x7B1AB4
    if (v0 != 0) {
        // 0x00564350
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00564340
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_559B98_00559b98(ctx);  // tail call
}

// 0x00564830 sub_564830 -- 68 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// Closes an IOP-side object: IOP command 1 with its id (+16, staged at sp+0), then its used byte +0 = 0.
void sub_564830(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564830
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 1;
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(ra, sp, 0x18);
    a1 = sp;
    a0 = 1;
    a3 = 0;
    lw(v0, s0, 16);
    t0 = 0;
    link(ctx, 0x564858u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x0);
    call(ctx, gen::fn_DTX_CallUrpc_00559c10);
    ld(ra, sp, 0x18);
    sb(zero, s0, 0);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005657B8 pfsCvfsStopTr -- 20 bytes; frame 0x10: ra sp+0x0
// Tail call to sub_5565B0.
void pfsCvfsStopTr(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005657b8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5565B0_005565b0(ctx);  // tail call
}

// 0x00566488 ROFS_DelVolume -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The ROFS front end (rofs_if.c line 178): sub_569810, then the volume interface's DelVolume slot (*0x7B26F8 +
// rofs_if::kDelVolume) with ($a0, 178, "ROFS_DelVolume", 0, -203); without an interface it reports error -203 through
// sub_569730 (tail call).
void ROFS_DelVolume(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00566488
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x566494u, gen::fn_sub_569810_00569810);
    v0 = 0x7B0000;
    a2 = 0x7C0000;
    lw(v0, v0, 9976);  // 0x7B26F8
    a0 = s0;
    a2 = addiu(a2, 28832);  // "ROFS_DelVolume"
    a1 = 178;
    a3 = 0;
    t0 = si(-203);
    if (v0 != 0) {
        // 0x005664c0
        charge(ctx, 7);
        lw(v0, v0, L15::rofs_if::kDelVolume);
        jalr(ctx, 0x5664C4u, v0.u());
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005664e0
    charge(ctx, 6);
    a0 = 0x7C0000;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    a0 = addiu(a0, 28776);  // "../../rofs_if.c"
    sp = addiu(sp, 0x10);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x00566750 ROFS_StopTr -- 40 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// sub_569810, then RFHN_StopTrG($a0) (tail call).
void ROFS_StopTr(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00566750
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x56675Cu, gen::fn_sub_569810_00569810);
    ld(ra, sp, 0x8);
    a0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_RFHN_StopTrG_00566180(ctx);  // tail call
}

// 0x00566848 sub_566848 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ROFS front end, line 327: sub_569810, then the GetFileSiz64 slot (rofs_if::kGetFileSiz64) with $a1 = 0; without an
// interface it reports -203 ("ROFS_GetFileSiz64") through sub_569730.
void sub_566848(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00566848
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x566854u, gen::fn_sub_569810_00569810);
    v0 = 0x7B0000;
    a2 = 0x7C0000;
    lw(v0, v0, 9976);  // 0x7B26F8
    a0 = s0;
    a2 = addiu(a2, 28944);  // "ROFS_GetFileSiz64"
    a1 = 0;
    a3 = 0;
    t0 = si(-203);
    if (v0 == 0) {
        // 0x00566898
        charge(ctx, 5);
        a0 = 0x7C0000;
        a1 = 327;
        a0 = addiu(a0, 28776);  // "../../rofs_if.c"
        jal(ctx, 0x5668A0u, gen::fn_sub_569730_00569730);
        ld(s0, sp, 0x0);
    } else {
        // 0x00566880
        charge(ctx, 5);
        lw(v0, v0, L15::rofs_if::kGetFileSiz64);
        jalr(ctx, 0x566884u, v0.u());
        ld(s0, sp, 0x0);
    }
    // 0x005668ac (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005668B8 sub_5668B8 -- 128 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [proposed ROFS_GetFileSiz] ROFS front end, line 346: sub_569810, then the GetFileSiz slot (rofs_if::kGetFileSiz)
// with ($a0, $a1); else -203 through sub_569730.
void sub_5668B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005668b8
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x5668CCu, gen::fn_sub_569810_00569810);
    v0 = 0x7B0000;
    a2 = 0x7C0000;
    lw(v0, v0, 9976);  // 0x7B26F8
    a0 = s0;
    a1 = s1;
    a2 = addiu(a2, 28928);  // "ROFS_GetFileSiz"
    a3 = 0;
    t0 = si(-203);
    if (v0 != 0) {
        // 0x005668f8
        charge(ctx, 8);
        lw(v0, v0, L15::rofs_if::kGetFileSiz);
        jalr(ctx, 0x5668FCu, v0.u());
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00566918
    charge(ctx, 8);
    a0 = 0x7C0000;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a0 = addiu(a0, 28776);  // "../../rofs_if.c"
    ld(ra, sp, 0x10);
    a1 = 346;
    sp = addiu(sp, 0x20);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x00566938 sub_566938 -- 124 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ROFS front end, line 360: sub_569810, then the GetFileSiz64 slot (rofs_if::kGetFileSiz64) with ($a0, $a1); else -203
// ("ROFS_GetFileSiz64") through sub_569730.
void sub_566938(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00566938
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x56694Cu, gen::fn_sub_569810_00569810);
    v0 = 0x7B0000;
    a2 = 0x7C0000;
    lw(v0, v0, 9976);  // 0x7B26F8
    a0 = s0;
    a1 = s1;
    a2 = addiu(a2, 28944);  // "ROFS_GetFileSiz64"
    a3 = 0;
    t0 = si(-203);
    if (v0 == 0) {
        // 0x00566990
        charge(ctx, 5);
        a0 = 0x7C0000;
        a1 = 360;
        a0 = addiu(a0, 28776);  // "../../rofs_if.c"
        jal(ctx, 0x566998u, gen::fn_sub_569730_00569730);
        ld(s0, sp, 0x0);
    } else {
        // 0x00566978
        charge(ctx, 5);
        lw(v0, v0, L15::rofs_if::kGetFileSiz64);
        jalr(ctx, 0x56697Cu, v0.u());
        ld(s0, sp, 0x0);
    }
    // 0x005669a4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00566A58 ROFS_LoadDir -- 172 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// ROFS front end, line 409: sub_569810, then the LoadDir slot (rofs_if::kLoadDir) with ($a0, $a1, $a2); a nonzero
// result runs sub_5662C8 and is returned. Without an interface: -203 through sub_569730.
void ROFS_LoadDir(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00566a58
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x566A74u, gen::fn_sub_569810_00569810);
    v0 = 0x7B0000;
    a0 = s0;
    lw(v0, v0, 9976);  // 0x7B26F8
    a1 = s1;
    a2 = s2;
    a3 = 0;
    t0 = si(-203);
    if (v0 == 0) {
        // 0x00566ad8
        charge(ctx, 11);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 28776);  // "../../rofs_if.c"
        ld(s1, sp, 0x8);
        a2 = addiu(a2, 28992);  // "ROFS_LoadDir"
        ld(s2, sp, 0x10);
        a1 = 409;
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x00566a9c
    charge(ctx, 6);
    lw(v0, v0, L15::rofs_if::kLoadDir);
    jalr(ctx, 0x566AA0u, v0.u());
    s0 = v0;
    v0 = s0;
    if (s0 != 0) {
        // 0x00566ab4
        charge(ctx, 3);
        jal(ctx, 0x566AB4u, gen::fn_sub_5662C8_005662c8);
        v0 = s0;
    }
    // 0x00566ac0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00566C20 sub_566C20 -- 148 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [proposed ROFS_GetDirInf] ROFS front end, line 455: sub_569810, then the GetDirInf slot (rofs_if::kGetDirInf) with
// ($a0, $a1, $a2); else -203 through sub_569730.
void sub_566C20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00566c20
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x566C3Cu, gen::fn_sub_569810_00569810);
    v0 = 0x7B0000;
    a0 = s0;
    lw(v0, v0, 9976);  // 0x7B26F8
    a1 = s1;
    a2 = s2;
    a3 = 0;
    t0 = si(-203);
    if (v0 != 0) {
        // 0x00566c64
        charge(ctx, 9);
        lw(v0, v0, L15::rofs_if::kGetDirInf);
        jalr(ctx, 0x566C68u, v0.u());
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00566c88
    charge(ctx, 11);
    a0 = 0x7C0000;
    a2 = 0x7C0000;
    ld(s0, sp, 0x0);
    a0 = addiu(a0, 28776);  // "../../rofs_if.c"
    ld(s1, sp, 0x8);
    a2 = addiu(a2, 29040);  // "ROFS_GetDirInf"
    ld(s2, sp, 0x10);
    a1 = 455;
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x00566CB8 sub_566CB8 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [proposed ROFS_IsExistFile] ROFS front end, line 470: sub_569810, then the IsExistFile slot (rofs_if::kIsExistFile);
// without an interface it reports -203 and returns 0.
void sub_566CB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00566cb8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x566CC4u, gen::fn_sub_569810_00569810);
    v0 = 0x7B0000;
    a2 = 0x7C0000;
    lw(v0, v0, 9976);  // 0x7B26F8
    a0 = s0;
    a1 = 470;
    a2 = addiu(a2, 29056);  // "ROFS_IsExistFile"
    a3 = 0;
    t0 = si(-203);
    if (v0 == 0) {
        // 0x00566d08
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 28776);  // "../../rofs_if.c"
        jal(ctx, 0x566D0Cu, gen::fn_sub_569730_00569730);
        v0 = 0;
        ld(s0, sp, 0x0);
    } else {
        // 0x00566cf0
        charge(ctx, 5);
        lw(v0, v0, L15::rofs_if::kIsExistFile);
        jalr(ctx, 0x566CF4u, v0.u());
        ld(s0, sp, 0x0);
    }
    // 0x00566d1c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00566D28 sub_566D28 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [proposed ROFS_GetNumFiles] ROFS front end, line 486: sub_569810, then the GetNumFiles slot (rofs_if::kGetNumFiles);
// else -203 through sub_569730.
void sub_566D28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00566d28
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x566D34u, gen::fn_sub_569810_00569810);
    v0 = 0x7B0000;
    a2 = 0x7C0000;
    lw(v0, v0, 9976);  // 0x7B26F8
    a0 = s0;
    a2 = addiu(a2, 29080);  // "ROFS_GetNumFiles"
    a1 = 486;
    a3 = 0;
    t0 = si(-203);
    if (v0 != 0) {
        // 0x00566d60
        charge(ctx, 7);
        lw(v0, v0, L15::rofs_if::kGetNumFiles);
        jalr(ctx, 0x566D64u, v0.u());
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00566d80
    charge(ctx, 6);
    a0 = 0x7C0000;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    a0 = addiu(a0, 28776);  // "../../rofs_if.c"
    sp = addiu(sp, 0x10);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x0056A538 sub_56A538 -- 8 bytes; leaf frame (no stack)
// An empty function (jr $ra): a no-op slot of a function table.
void sub_56A538(EEContext& ctx) {
    using namespace hg;
    // 0x0056a538
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0056A5A0 dcfTell -- 96 bytes; frame 0x10: ra sp+0x0
// The PFS device table's Tell: g_rofs_pfs_tbl's slot pfs::kTell when the table and the slot are set; otherwise error
// -203 (rofs_pfs.c line 170, "dcfTell") through sub_569730.
void dcfTell(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056a5a0
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10248);  // g_rofs_pfs_tbl
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056a5b4
        charge(ctx, 3);
        lw(v0, v0, L15::pfs::kTell);
        if (v0 == 0) {
            a0 = 0x7C0000;
            goto L_0056a5dc;
        }
        // 0x0056a5c0
        charge(ctx, 5);
        jalr(ctx, 0x56A5C0u, v0.u());
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0056a5d8
    charge(ctx, 1);
    a0 = 0x7C0000;
L_0056a5dc:
    charge(ctx, 9);
    a2 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 30216);
    a2 = addiu(a2, 30248);  // "dcfTell"
    a1 = 170;
    a3 = 0;
    t0 = si(-203);
    sp = addiu(sp, 0x10);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x0056A660 dcfStopTr -- 52 bytes; frame 0x10: ra sp+0x0
// The PFS device table's StopTr: calls g_rofs_pfs_tbl's slot pfs::kStopTr when the table and the slot are set; else
// returns the value it tested.
void dcfStopTr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056a660
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10248);  // g_rofs_pfs_tbl
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056a674
        charge(ctx, 3);
        lw(v0, v0, L15::pfs::kStopTr);
        if (v0 != 0) {
            // 0x0056a680
            charge(ctx, 2);
            jalr(ctx, 0x56A680u, v0.u());
            goto L_0056a688;
        }
        ld(ra, sp, 0x0);
        // 0x0056a68c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_0056a688:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x0056a68c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x0056A9E0 dcfReadBlk -- 184 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Reads $a2 sectors (> 0, else returns 0): dcfReqRdBlk, then rfpfs_waitRdComplete; returns the sector count << 11
// (bytes). A failed request reports its code (line 338, "dcfReqRdBlk"), a failed wait -207 (line 342,
// "waitRdComplete"), both through sub_569730.
void dcfReadBlk(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056a9e0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    if (i64(a2) <= 0) {
        // 0x0056aa84 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0056a9fc
    charge(ctx, 10);
    jal(ctx, 0x56A9FCu, gen::fn_dcfReqRdBlk_0056a860);
    a2 = 0x7C0000;
    s0 = v0;
    a0 = s1;
    a2 = addiu(a2, 30336);  // "dcfReqRdBlk"
    t0 = s0;
    a1 = 338;
    a3 = 0;
    if (i64(s0) < 0) {
        // 0x0056aa24
        charge(ctx, 7);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 30216);  // "../../rofs_pfs.c"
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x0056aa40
    charge(ctx, 11);
    jal(ctx, 0x56AA40u, gen::fn_rfpfs_waitRdComplete_0056ac28);
    a0 = 0x7C0000;
    a2 = 0x7C0000;
    v1 = 1;
    a0 = addiu(a0, 30216);  // "../../rofs_pfs.c"
    a2 = addiu(a2, 30368);  // "waitRdComplete"
    a1 = 342;
    a3 = 0;
    t0 = si(-207);
    if (v0 != v1) {
        // 0x0056aa6c
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x0056aa80
    charge(ctx, 1);
    v0 = sll(s0, 11);
    // 0x0056aa84 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0056AAC0 dcfReadCda -- 184 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// As dcfReadBlk for the CD-DA path ($a3 sectors): dcfReqRdCda, rfpfs_waitRdComplete, the count << 11; errors at lines
// 382 / 387.
void dcfReadCda(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056aac0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    if (i64(a3) <= 0) {
        // 0x0056ab64 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0056aadc
    charge(ctx, 10);
    jal(ctx, 0x56AADCu, gen::fn_dcfReqRdCda_0056aa98);
    a2 = 0x7C0000;
    s0 = v0;
    a0 = s1;
    a2 = addiu(a2, 30384);  // "dcfReqRdCda"
    t0 = s0;
    a1 = 382;
    a3 = 0;
    if (i64(s0) < 0) {
        // 0x0056ab04
        charge(ctx, 7);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 30216);  // "../../rofs_pfs.c"
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x0056ab20
    charge(ctx, 11);
    jal(ctx, 0x56AB20u, gen::fn_rfpfs_waitRdComplete_0056ac28);
    a0 = 0x7C0000;
    a2 = 0x7C0000;
    v1 = 1;
    a0 = addiu(a0, 30216);  // "../../rofs_pfs.c"
    a2 = addiu(a2, 30368);  // "waitRdComplete"
    a1 = 387;
    a3 = 0;
    t0 = si(-207);
    if (v0 != v1) {
        // 0x0056ab4c
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x0056ab60
    charge(ctx, 1);
    v0 = sll(s0, 11);
    // 0x0056ab64 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0056CA60 sub_56CA60 -- 20 bytes; frame 0x10: ra sp+0x0
// ROCI option thunk: tail call to sub_566CB8 (ROFS IsExistFile).
void sub_56CA60(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056ca60
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_566CB8_00566cb8(ctx);  // tail call
}

// 0x0056CA80 sub_56CA80 -- 20 bytes; frame 0x10: ra sp+0x0
// ROCI option thunk: tail call to sub_566C20 (ROFS GetDirInf).
void sub_56CA80(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056ca80
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_566C20_00566c20(ctx);  // tail call
}

// 0x0056CA98 sub_56CA98 -- 20 bytes; frame 0x10: ra sp+0x0
// ROCI option thunk: tail call to sub_5668B8 (ROFS GetFileSiz).
void sub_56CA98(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056ca98
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5668B8_005668b8(ctx);  // tail call
}

// 0x00570240 sub_570240 -- 8 bytes; leaf frame (no stack)
// An empty function (jr $ra) the sequence-header parser calls (sub_5703C0).
void sub_570240(EEContext& ctx) {
    using namespace hg;
    // 0x00570240
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x005702F8 sub_5702F8 -- 80 bytes; leaf frame (no stack)
// MPEG-2 video: chooses the decode mode m2v::kDecMode from the picture: 1 when the word m2v::kMode1 is
// 1 or the picture structure (m2v::kPicStruct) is 1 or 2 (a field); else 3 when +308 is 1, 2 otherwise. Returns 1 or
// 3.
void sub_5702F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005702f8
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, L15::m2v::kMode1);
    v1 = 1;
    cc = v0 == v1;  // the condition, before the delay slot changes it
    v0 = 1;
    if (cc) {
        // 0x00570324 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sw(v0, a0, L15::m2v::kDecMode);
        return;
    }
    // 0x00570308
    charge(ctx, 3);
    lw(v0, a0, L15::m2v::kPicStruct);
    if (v0 == v1) {
        v0 = 1;
        // 0x00570324 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sw(v0, a0, L15::m2v::kDecMode);
        return;
    }
    // 0x00570314
    charge(ctx, 3);
    a1 = 2;
    if (v0 == a1) {
        // 0x00570320
        charge(ctx, 1);
        v0 = 1;
        // 0x00570324 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sw(v0, a0, L15::m2v::kDecMode);
        return;
    }
    lw(v0, a0, 308);
    // 0x00570330
    charge(ctx, 2);
    cc = v0 != v1;  // the condition, before the delay slot changes it
    v0 = 3;
    if (cc) {
        // 0x00570340
        charge(ctx, 2);
        sw(a1, a0, L15::m2v::kDecMode);
        return;
    }
    // 0x00570338
    charge(ctx, 2);
    sw(v0, a0, L15::m2v::kDecMode);
}

// 0x00570348 sub_570348 -- 108 bytes; leaf frame (no stack)
// MPEG-2 video: the field-parity toggle and the intra-DC setup: a frame picture (m2v::kPicStruct == 3) clears the
// parity pair +964 / +968; else +964 = (+968)++ % 2. Then the DC predictor reset m2v::kDcReset = {128, 256, 512,
// 1024}[precision] and the DC multiplier m2v::kDcMult = {8, 4, 2, 1}[precision] (tables 0x7C78D0 / 0x7C78E0; precision
// = m2v::kIntraDcPrec). Returns precision * 4.
void sub_570348(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00570348
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = a0;
    v1 = 3;
    lw(v0, a1, L15::m2v::kPicStruct);
    if (v0 != v1) {
        lw(v0, a1, 968);
        // 0x00570368
        charge(ctx, 8);
        v1 = srl(v0, 31);
        a0 = addiu(v0, 1);
        v1 = addu(v0, v1);
        sw(a0, a1, 968);
        v1 = sra(v1, 1);
        v1 = sll(v1, 1);
        v0 = subu(v0, v1);
        sw(v0, a1, 964);
    } else {
        // 0x0057035c
        charge(ctx, 3);
        sw(zero, a1, 968);
        sw(zero, a1, 964);
    }
    // 0x00570388 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lw(v0, a1, L15::m2v::kIntraDcPrec);
    v0 = sll(v0, 2);
    v1 = 0x7C0000;
    v1 = addu(v1, v0);
    lw(v1, v1, 30928);
    sw(v1, a1, L15::m2v::kDcReset);
    a0 = 0x7C0000;
    a0 = addu(a0, v0);
    lw(a0, a0, 30944);
    sw(a0, a1, L15::m2v::kDcMult);
}

// 0x005703C0 sub_5703C0 -- 2008 bytes; frame 0x30: s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, ra sp+0x20
// MPEG-2 video: the sequence-header parser (start code 0x1B3). The header kind m2v::kHdrKind = 1, +1640.. +1648
// cleared, +1520 counted (and +1624 by the stream type +1128), sub_570240 runs, then the bit reader (a big-endian
// 64-bit window over the aligned words at $a1 & ~3) takes the 12-bit sizes, aspect / rate codes, the bit rate, the VBV
// size and the two optional 64-entry quantiser matrices into the record at $a0 + 352. Returns the byte address after
// the header.
void sub_5703C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005703c0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 1;
    sd(s2, sp, 0x10);
    s2 = addiu(a0, 352);
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x20);
    sw(v1, s2, 1156);
    lw(v0, s2, 1168);
    lw(a0, s2, 776);
    v0 = addiu(v0, 1);
    sw(zero, s2, 1288);
    sw(v0, s2, 1168);
    sw(zero, s2, 1292);
    sw(zero, s2, 1296);
    if (a0 != 0) {
        // 0x00570408
        charge(ctx, 3);
        v0 = 64;
        if (a0 == v0) {
            goto L_00570414;
        }
        lw(v0, s2, 1272);
    L_00570424:
        charge(ctx, 2);
        v0 = addiu(v0, 1);
        sw(v0, s2, 1272);
        goto L_0057042c;
    }
L_00570414:
    charge(ctx, 3);
    lw(v0, s2, 780);
    if (v0 != 0) {
        // 0x00570420
        charge(ctx, 1);
        lw(v0, s2, 1272);
        goto L_00570424;
    }
L_0057042c:
    charge(ctx, 36);
    a0 = s2;
    jal(ctx, 0x57042Cu, gen::fn_sub_570240_00570240);
    v0 = si(-4);
    s0 = s3 & v0;
    v1 = subu(s3, s0);
    lb(t0, s0, 0);
    s0 = addiu(s0, 1);
    s1 = sll(v1, 3);
    lbu(a0, s0, 0);
    s0 = addiu(s0, 1);
    lbu(a1, s0, 0);
    s0 = addiu(s0, 1);
    lbu(a2, s0, 0);
    s0 = addiu(s0, 1);
    lb(a3, s0, 0);
    s0 = addiu(s0, 1);
    lbu(v0, s0, 0);
    s0 = addiu(s0, 1);
    t0 = sll(t0, 8);
    a3 = sll(a3, 8);
    t0 = t0 | a0;
    a3 = a3 | v0;
    lbu(v1, s0, 0);
    s0 = addiu(s0, 1);
    t0 = sll(t0, 8);
    a3 = sll(a3, 8);
    t0 = t0 | a1;
    lbu(v0, s0, 0);
    a3 = a3 | v1;
    t0 = sll(t0, 8);
    a3 = sll(a3, 8);
    t0 = t0 | a2;
    s0 = addiu(s0, 1);
    a3 = a3 | v0;
    t0 = sllv(t0, s1);
    if (s1 == 0) {
        // 0x005704d8
        charge(ctx, 2);
        sw(t0, s2, 0);
        t0 = a3;
    } else {
        // 0x005704bc
        charge(ctx, 6);
        v0 = subu(0, s1);
        v0 = srlv(a3, v0);
        v0 = t0 | v0;
        t0 = sllv(a3, s1);
        sw(v0, s2, 0);
    }
    // 0x005704e0
    charge(ctx, 16);
    lb(a3, s0, 0);
    s0 = addiu(s0, 1);
    lbu(v0, s0, 0);
    s0 = addiu(s0, 1);
    a3 = sll(a3, 8);
    lbu(v1, s0, 0);
    a3 = a3 | v0;
    v0 = slti(s1, 20);
    s0 = addiu(s0, 1);
    a3 = sll(a3, 8);
    lbu(a0, s0, 0);
    s0 = addiu(s0, 1);
    a3 = a3 | v1;
    a3 = sll(a3, 8);
    a3 = a3 | a0;
    if (v0 != 0) {
        // 0x00570590
        charge(ctx, 4);
        v0 = srl(t0, 20);
        t0 = sll(t0, 12);
        sw(v0, s2, 4);
        s1 = addiu(s1, 12);
    } else {
        // 0x00570520
        charge(ctx, 3);
        s1 = addiu(s1, -20);
        v0 = 12;
        if (s1 == 0) {
            // 0x00570548
            charge(ctx, 3);
            v0 = srl(t0, 20);
            t0 = a3;
            sw(v0, s2, 4);
        } else {
            // 0x0057052c
            charge(ctx, 7);
            v0 = subu(v0, s1);
            v0 = srlv(a3, v0);
            t0 = t0 | v0;
            v1 = srl(t0, 20);
            t0 = sllv(a3, s1);
            sw(v1, s2, 4);
        }
        // 0x00570554
        charge(ctx, 15);
        lb(a3, s0, 0);
        s0 = addiu(s0, 1);
        lbu(v0, s0, 0);
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v1, s0, 0);
        a3 = a3 | v0;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v0, s0, 0);
        a3 = a3 | v1;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x005705a0
    charge(ctx, 3);
    v0 = slti(s1, 20);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t0, 20);
    if (cc) {
        // 0x00570620
        charge(ctx, 3);
        t0 = sll(t0, 12);
        sw(v0, s2, 8);
        s1 = addiu(s1, 12);
    } else {
        // 0x005705ac
        charge(ctx, 3);
        s1 = addiu(s1, -20);
        v0 = 12;
        if (s1 == 0) {
            // 0x005705d8
            charge(ctx, 3);
            v0 = srl(t0, 20);
            t0 = a3;
            sw(v0, s2, 8);
        } else {
            // 0x005705b8
            charge(ctx, 7);
            v0 = subu(v0, s1);
            v0 = srlv(a3, v0);
            t0 = t0 | v0;
            v1 = srl(t0, 20);
            t0 = sllv(a3, s1);
            sw(v1, s2, 8);
        }
        // 0x005705e4
        charge(ctx, 15);
        lb(a3, s0, 0);
        s0 = addiu(s0, 1);
        lbu(v0, s0, 0);
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v1, s0, 0);
        a3 = a3 | v0;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v0, s0, 0);
        a3 = a3 | v1;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x0057062c
    charge(ctx, 3);
    v0 = slti(s1, 28);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t0, 28);
    if (cc) {
        // 0x005706a8
        charge(ctx, 3);
        t0 = sll(t0, 4);
        sw(v0, s2, 12);
        s1 = addiu(s1, 4);
    } else {
        // 0x00570638
        charge(ctx, 3);
        s1 = addiu(s1, -28);
        v0 = 4;
        if (s1 == 0) {
            // 0x00570660
            charge(ctx, 3);
            v0 = srl(t0, 28);
            t0 = a3;
            sw(v0, s2, 12);
        } else {
            // 0x00570644
            charge(ctx, 7);
            v0 = subu(v0, s1);
            v0 = srlv(a3, v0);
            t0 = t0 | v0;
            v1 = srl(t0, 28);
            t0 = sllv(a3, s1);
            sw(v1, s2, 12);
        }
        // 0x0057066c
        charge(ctx, 15);
        lb(a3, s0, 0);
        s0 = addiu(s0, 1);
        lbu(v0, s0, 0);
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v1, s0, 0);
        a3 = a3 | v0;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v0, s0, 0);
        a3 = a3 | v1;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x005706b4
    charge(ctx, 3);
    v0 = slti(s1, 28);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t0, 28);
    if (cc) {
        // 0x00570730
        charge(ctx, 3);
        t0 = sll(t0, 4);
        sw(v0, s2, 16);
        s1 = addiu(s1, 4);
    } else {
        // 0x005706c0
        charge(ctx, 3);
        s1 = addiu(s1, -28);
        v0 = 4;
        if (s1 == 0) {
            // 0x005706e8
            charge(ctx, 3);
            v0 = srl(t0, 28);
            t0 = a3;
            sw(v0, s2, 16);
        } else {
            // 0x005706cc
            charge(ctx, 7);
            v0 = subu(v0, s1);
            v0 = srlv(a3, v0);
            t0 = t0 | v0;
            v1 = srl(t0, 28);
            t0 = sllv(a3, s1);
            sw(v1, s2, 16);
        }
        // 0x005706f4
        charge(ctx, 15);
        lb(a3, s0, 0);
        s0 = addiu(s0, 1);
        lbu(v0, s0, 0);
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v1, s0, 0);
        a3 = a3 | v0;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v0, s0, 0);
        a3 = a3 | v1;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x0057073c
    charge(ctx, 3);
    v0 = slti(s1, 14);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t0, 14);
    if (cc) {
        // 0x005707b8
        charge(ctx, 3);
        t0 = sll(t0, 18);
        sw(v0, s2, 20);
        s1 = addiu(s1, 18);
    } else {
        // 0x00570748
        charge(ctx, 3);
        s1 = addiu(s1, -14);
        v0 = 18;
        if (s1 == 0) {
            // 0x00570770
            charge(ctx, 3);
            v0 = srl(t0, 14);
            t0 = a3;
            sw(v0, s2, 20);
        } else {
            // 0x00570754
            charge(ctx, 7);
            v0 = subu(v0, s1);
            v0 = srlv(a3, v0);
            t0 = t0 | v0;
            v1 = srl(t0, 14);
            t0 = sllv(a3, s1);
            sw(v1, s2, 20);
        }
        // 0x0057077c
        charge(ctx, 15);
        lb(a3, s0, 0);
        s0 = addiu(s0, 1);
        lbu(v0, s0, 0);
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v1, s0, 0);
        a3 = a3 | v0;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v0, s0, 0);
        a3 = a3 | v1;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x005707c4
    charge(ctx, 3);
    v0 = slti(s1, 31);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t0, 31);
    if (cc) {
        // 0x00570840
        charge(ctx, 3);
        t0 = sll(t0, 1);
        sw(v0, s2, 24);
        s1 = addiu(s1, 1);
    } else {
        // 0x005707d0
        charge(ctx, 3);
        s1 = addiu(s1, -31);
        v0 = 1;
        if (s1 == 0) {
            // 0x005707f8
            charge(ctx, 3);
            v0 = srl(t0, 31);
            t0 = a3;
            sw(v0, s2, 24);
        } else {
            // 0x005707dc
            charge(ctx, 7);
            v0 = subu(v0, s1);
            v0 = srlv(a3, v0);
            t0 = t0 | v0;
            v1 = srl(t0, 31);
            t0 = sllv(a3, s1);
            sw(v1, s2, 24);
        }
        // 0x00570804
        charge(ctx, 15);
        lb(a3, s0, 0);
        s0 = addiu(s0, 1);
        lbu(v0, s0, 0);
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v1, s0, 0);
        a3 = a3 | v0;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v0, s0, 0);
        a3 = a3 | v1;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x0057084c
    charge(ctx, 3);
    v0 = slti(s1, 22);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t0, 22);
    if (cc) {
        // 0x005708c8
        charge(ctx, 3);
        t0 = sll(t0, 10);
        sw(v0, s2, 28);
        s1 = addiu(s1, 10);
    } else {
        // 0x00570858
        charge(ctx, 3);
        s1 = addiu(s1, -22);
        v0 = 10;
        if (s1 == 0) {
            // 0x00570880
            charge(ctx, 3);
            v0 = srl(t0, 22);
            t0 = a3;
            sw(v0, s2, 28);
        } else {
            // 0x00570864
            charge(ctx, 7);
            v0 = subu(v0, s1);
            v0 = srlv(a3, v0);
            t0 = t0 | v0;
            v1 = srl(t0, 22);
            t0 = sllv(a3, s1);
            sw(v1, s2, 28);
        }
        // 0x0057088c
        charge(ctx, 15);
        lb(a3, s0, 0);
        s0 = addiu(s0, 1);
        lbu(v0, s0, 0);
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v1, s0, 0);
        a3 = a3 | v0;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v0, s0, 0);
        a3 = a3 | v1;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x005708d4
    charge(ctx, 3);
    v0 = slti(s1, 31);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t0, 31);
    if (cc) {
        // 0x00570950
        charge(ctx, 3);
        t0 = sll(t0, 1);
        sw(v0, s2, 32);
        s1 = addiu(s1, 1);
    } else {
        // 0x005708e0
        charge(ctx, 3);
        s1 = addiu(s1, -31);
        v0 = 1;
        if (s1 == 0) {
            // 0x00570908
            charge(ctx, 3);
            v0 = srl(t0, 31);
            t0 = a3;
            sw(v0, s2, 32);
        } else {
            // 0x005708ec
            charge(ctx, 7);
            v0 = subu(v0, s1);
            v0 = srlv(a3, v0);
            t0 = t0 | v0;
            v1 = srl(t0, 31);
            t0 = sllv(a3, s1);
            sw(v1, s2, 32);
        }
        // 0x00570914
        charge(ctx, 15);
        lb(a3, s0, 0);
        s0 = addiu(s0, 1);
        lbu(v0, s0, 0);
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v1, s0, 0);
        a3 = a3 | v0;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v0, s0, 0);
        a3 = a3 | v1;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x0057095c
    charge(ctx, 3);
    v0 = slti(s1, 31);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t0, 31);
    if (cc) {
        // 0x005709d8
        charge(ctx, 3);
        t0 = sll(t0, 1);
        sw(v0, s2, 36);
        s1 = addiu(s1, 1);
    } else {
        // 0x00570968
        charge(ctx, 3);
        s1 = addiu(s1, -31);
        v0 = 1;
        if (s1 == 0) {
            // 0x00570990
            charge(ctx, 3);
            v0 = srl(t0, 31);
            t0 = a3;
            sw(v0, s2, 36);
        } else {
            // 0x00570974
            charge(ctx, 7);
            v0 = subu(v0, s1);
            v0 = srlv(a3, v0);
            t0 = t0 | v0;
            v1 = srl(t0, 31);
            t0 = sllv(a3, s1);
            sw(v1, s2, 36);
        }
        // 0x0057099c
        charge(ctx, 15);
        lb(a3, s0, 0);
        s0 = addiu(s0, 1);
        lbu(v0, s0, 0);
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v1, s0, 0);
        a3 = a3 | v0;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        lbu(v0, s0, 0);
        a3 = a3 | v1;
        s0 = addiu(s0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x005709e4
    charge(ctx, 3);
    lw(v0, s2, 36);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = slti(s1, 31);
    if (!cc) {
        // 0x005709f0
        charge(ctx, 2);
        a0 = 63;
        s1 = addiu(s1, 8);
        for (;;) {
            // 0x005709f8
            charge(ctx, 3);
            v0 = slti(s1, 32);
            if (v0 != 0) {
                t0 = sll(t0, 8);
            } else {
                // 0x00570a04
                charge(ctx, 16);
                s1 = addiu(s1, -32);
                t0 = sllv(a3, s1);
                lb(a3, s0, 0);
                s0 = addiu(s0, 1);
                lbu(v0, s0, 0);
                s0 = addiu(s0, 1);
                a3 = sll(a3, 8);
                lbu(v1, s0, 0);
                a3 = a3 | v0;
                s0 = addiu(s0, 1);
                a3 = sll(a3, 8);
                lbu(v0, s0, 0);
                a3 = a3 | v1;
                s0 = addiu(s0, 1);
                a3 = sll(a3, 8);
                a3 = a3 | v0;
            }
            // 0x00570a44
            charge(ctx, 3);
            a0 = addiu(a0, -1);
            if (i64(a0) < 0) {
                break;
            }
            s1 = addiu(s1, 8);
            backedge(ctx);
        }
        // 0x00570a50
        charge(ctx, 1);
        v0 = slti(s1, 31);
    }
    // 0x00570a54
    charge(ctx, 2);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t0, 31);
    if (cc) {
        // 0x00570a90
        charge(ctx, 2);
        s1 = addiu(s1, 1);
        sw(v0, s2, 40);
    } else {
        // 0x00570a5c
        charge(ctx, 3);
        s1 = addiu(s1, -31);
        v0 = 1;
        if (s1 == 0) {
            // 0x00570a80
            charge(ctx, 2);
            v0 = srl(t0, 31);
            sw(v0, s2, 40);
        } else {
            // 0x00570a68
            charge(ctx, 6);
            v0 = subu(v0, s1);
            v0 = srlv(a3, v0);
            t0 = t0 | v0;
            v1 = srl(t0, 31);
            sw(v1, s2, 40);
        }
        // 0x00570a88
        charge(ctx, 2);
        s0 = addiu(s0, 4);
    }
    // 0x00570a98
    charge(ctx, 3);
    lw(v0, s2, 40);
    v1 = 63;
    if (v0 != 0) {
        // 0x00570aa4
        charge(ctx, 1);
        s1 = addiu(s1, 8);
        for (;;) {
            // 0x00570aa8
            charge(ctx, 3);
            v0 = slti(s1, 32);
            v1 = addiu(v1, -1);
            if (v0 == 0) {
                // 0x00570ab4
                charge(ctx, 2);
                s1 = addiu(s1, -32);
                s0 = addiu(s0, 4);
            }
            // 0x00570abc
            charge(ctx, 4);
            if (i64(v1) < 0) {
                break;
            }
            s1 = addiu(s1, 8);
            backedge(ctx);
        }
    }
    // 0x00570acc
    charge(ctx, 7);
    a0 = s2;
    jal(ctx, 0x570ACCu, gen::fn_sub_570248_00570248);
    a0 = s2;
    jal(ctx, 0x570AD4u, gen::fn_sub_5703B8_005703b8);
    lw(v0, s2, 708);
    if (v0 != 0) {
        lw(v0, s2, 712);
    } else {
        // 0x00570ae8
        charge(ctx, 4);
        lw(v0, s2, 1272);
        v0 = addiu(v0, 1);
        sw(v0, s2, 1272);
        lw(v0, s2, 712);
    }
    // 0x00570af8
    charge(ctx, 2);
    if (v0 != 0) {
        lw(v0, s2, 12);
    } else {
        // 0x00570b00
        charge(ctx, 4);
        lw(v0, s2, 1272);
        v0 = addiu(v0, 1);
        sw(v0, s2, 1272);
        lw(v0, s2, 12);
    }
    // 0x00570b10
    charge(ctx, 4);
    v0 = addiu(v0, -1);
    v0 = sltiu(v0, 4);
    if (v0 != 0) {
        lw(v0, s2, 16);
    } else {
        // 0x00570b20
        charge(ctx, 4);
        lw(v0, s2, 1272);
        v0 = addiu(v0, 1);
        sw(v0, s2, 1272);
        lw(v0, s2, 16);
    }
    // 0x00570b30
    charge(ctx, 4);
    v0 = addiu(v0, -1);
    v0 = sltiu(v0, 8);
    v1 = subu(s0, s3);
    if (v0 == 0) {
        // 0x00570b40
        charge(ctx, 3);
        lw(v0, s2, 1272);
        v0 = addiu(v0, 1);
        sw(v0, s2, 1272);
    }
    // 0x00570b4c (the shared epilogue, written out on this path)
    charge(ctx, 19);
    ld(s0, sp, 0x0);
    v1 = sll(v1, 3);
    v0 = 1;
    v1 = addu(s1, v1);
    ld(s1, sp, 0x8);
    sw(v0, s2, 780);
    v0 = addiu(v1, -57);
    a0 = slti(v0, 0);
    v1 = addiu(v1, -50);
    if (a0 != 0) v0 = v1;
    a1 = 16;
    v0 = sra(v0, 3);
    sw(a1, s2, 776);
    v0 = addu(s3, v0);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00570B98 sub_570B98 -- 288 bytes; leaf frame (no stack)
// MPEG-2 video: a 32-bit header record (header kind 1): bumps its counters, takes the 32 bits after the start code
// into +396 (the record at $a0 + 352, word 11) and clears +1132 / +1128. Returns the next byte.
void sub_570B98(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12};
    // 0x00570b98
    enter(ctx, 9);  // entry check point + this block's cycles
    t3 = addiu(a0, 352);
    v1 = 1;
    lw(v0, t3, 1172);
    t4 = a1;
    lw(a0, t3, 776);
    v0 = addiu(v0, 1);
    sw(v1, t3, 1156);
    sw(v0, t3, 1172);
    if (a0 != 0) {
        // 0x00570bbc
        charge(ctx, 3);
        v0 = 128;
        if (a0 == v0) {
            goto L_00570bc8;
        }
        lw(v0, t3, 1272);
    L_00570bd8:
        charge(ctx, 3);
        v0 = addiu(v0, 1);
        sw(v0, t3, 1272);
        v1 = si(-4);
        goto L_00570be4;
    }
L_00570bc8:
    charge(ctx, 3);
    lw(v0, t3, 780);
    v1 = si(-4);
    if (v0 != 0) {
        // 0x00570bd4
        charge(ctx, 1);
        lw(v0, t3, 1272);
        goto L_00570bd8;
    }
L_00570be4:
    charge(ctx, 46);
    v1 = t4 & v1;
    a2 = subu(t4, v1);
    lb(t2, v1, 0);
    v1 = addiu(v1, 1);
    a2 = sll(a2, 3);
    lbu(a1, v1, 0);
    v1 = addiu(v1, 1);
    lbu(a3, v1, 0);
    v1 = addiu(v1, 1);
    lbu(t0, v1, 0);
    v1 = addiu(v1, 1);
    lb(a0, v1, 0);
    v1 = addiu(v1, 1);
    lbu(v0, v1, 0);
    v1 = addiu(v1, 1);
    t2 = sll(t2, 8);
    a0 = sll(a0, 8);
    t2 = t2 | a1;
    lbu(a1, v1, 0);
    v1 = addiu(v1, 1);
    a0 = a0 | v0;
    lbu(v0, v1, 0);
    v1 = addiu(v1, 1);
    v1 = addiu(v1, 4);
    a0 = sll(a0, 8);
    v1 = subu(v1, t4);
    a0 = a0 | a1;
    v1 = sll(v1, 3);
    t2 = sll(t2, 8);
    v1 = addu(a2, v1);
    a0 = sll(a0, 8);
    a0 = a0 | v0;
    v0 = addiu(v1, -57);
    t2 = t2 | a3;
    a1 = slti(v0, 0);
    v1 = addiu(v1, -50);
    t2 = sll(t2, 8);
    if (a1 != 0) v0 = v1;
    t1 = subu(0, a2);
    t2 = t2 | t0;
    a0 = srlv(a0, t1);
    t2 = sllv(t2, a2);
    v0 = sra(v0, 3);
    v1 = t2 | a0;
    v0 = addu(t4, v0);
    if (a2 == 0) {
        // 0x00570ca8
        charge(ctx, 1);
        sw(t2, t3, 44);
    } else {
        // 0x00570c9c
        charge(ctx, 2);
        sw(v1, t3, 44);
    }
    // 0x00570cac (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sw(zero, t3, 780);
    sw(zero, t3, 776);
}

// 0x00570CB8 sub_570CB8 -- 536 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// MPEG-2 video: user data (start code 0x1B2): counts it (+1528), scans the bytes up to the next 0x000001 prefix (at
// most 0x100000 bytes) and hands them to sub_570ED0. Returns the byte after the data.
void sub_570CB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00570cb8
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t2 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s0, sp, 0x0);
    t1 = addiu(t2, 352);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    lw(v0, t1, 1176);
    lw(v1, t1, 776);
    v0 = addiu(v0, 1);
    sw(v0, t1, 1176);
    if (v1 != 0) {
        // 0x00570cec
        charge(ctx, 3);
        v0 = 32;
        if (v1 == v0) {
            goto L_00570cf8;
        }
        lw(v0, t1, 1272);
    L_00570d08:
        charge(ctx, 3);
        v0 = addiu(v0, 1);
        sw(v0, t1, 1272);
        v0 = si(-4);
        goto L_00570d14;
    }
L_00570cf8:
    charge(ctx, 3);
    lw(v0, t1, 780);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = si(-4);
    if (!cc) {
        // 0x00570d04
        charge(ctx, 1);
        lw(v0, t1, 1272);
        goto L_00570d08;
    }
L_00570d14:
    charge(ctx, 33);
    s0 = s2 & v0;
    v1 = subu(s2, s0);
    lb(t0, s0, 0);
    s0 = addiu(s0, 1);
    s1 = sll(v1, 3);
    lbu(a0, s0, 0);
    s0 = addiu(s0, 1);
    lbu(a1, s0, 0);
    s0 = addiu(s0, 1);
    lbu(a2, s0, 0);
    s0 = addiu(s0, 1);
    lb(a3, s0, 0);
    s0 = addiu(s0, 1);
    lbu(v0, s0, 0);
    s0 = addiu(s0, 1);
    t0 = sll(t0, 8);
    a3 = sll(a3, 8);
    t0 = t0 | a0;
    a3 = a3 | v0;
    lbu(v1, s0, 0);
    s0 = addiu(s0, 1);
    t0 = sll(t0, 8);
    a3 = sll(a3, 8);
    t0 = t0 | a1;
    lbu(v0, s0, 0);
    a3 = a3 | v1;
    t0 = sll(t0, 8);
    a3 = sll(a3, 8);
    t0 = t0 | a2;
    s0 = addiu(s0, 1);
    a3 = a3 | v0;
    t0 = sllv(t0, s1);
    if (s1 == 0) {
        // 0x00570db0
        charge(ctx, 2);
        sw(t0, t1, 48);
        t0 = a3;
    } else {
        // 0x00570d98
        charge(ctx, 6);
        v0 = subu(0, s1);
        v0 = srlv(a3, v0);
        v0 = t0 | v0;
        t0 = sllv(a3, s1);
        sw(v0, t1, 48);
    }
    // 0x00570db8
    charge(ctx, 20);
    lb(a3, s0, 0);
    s0 = addiu(s0, 1);
    lbu(v0, s0, 0);
    s0 = addiu(s0, 1);
    a3 = sll(a3, 8);
    lbu(v1, s0, 0);
    a3 = a3 | v0;
    s0 = addiu(s0, 1);
    a3 = sll(a3, 8);
    lbu(v0, s0, 0);
    a3 = a3 | v1;
    a0 = 0xF0000;
    a3 = sll(a3, 8);
    s0 = addiu(s0, 1);
    a3 = a3 | v0;
    a2 = 0;
    a0 = a0 | 0xFFFF;
    t1 = 40;
    a1 = 1;
    for (;;) {
        // 0x00570e54
        charge(ctx, 3);
        v0 = slt(a0, a2);
        if (v0 == 0) {
            // 0x00570e60
            charge(ctx, 4);
            v0 = slti(s1, 9);
            v1 = srl(t0, 8);
            t0 = sll(t0, 8);
            if (v0 == 0) {
                // 0x00570e70
                charge(ctx, 3);
                v0 = subu(t1, s1);
                v0 = srlv(a3, v0);
                v1 = v1 | v0;
            }
            // 0x00570e7c
            charge(ctx, 2);
            if (v1 == a1) {
                goto L_00570e84_15;
            }
            s1 = addiu(s1, 8);
            backedge(ctx);
            // 0x00570e08
            charge(ctx, 3);
            v0 = slti(s1, 32);
            a2 = addiu(a2, 1);
            if (v0 == 0) {
                // 0x00570e14
                charge(ctx, 16);
                s1 = addiu(s1, -32);
                t0 = sllv(a3, s1);
                lb(a3, s0, 0);
                s0 = addiu(s0, 1);
                lbu(v0, s0, 0);
                s0 = addiu(s0, 1);
                a3 = sll(a3, 8);
                lbu(v1, s0, 0);
                a3 = a3 | v0;
                s0 = addiu(s0, 1);
                a3 = sll(a3, 8);
                lbu(v0, s0, 0);
                a3 = a3 | v1;
                s0 = addiu(s0, 1);
                a3 = sll(a3, 8);
                a3 = a3 | v0;
            }
            continue;
        }
        a0 = t2;
        break;
    }
L_00570e88:
    charge(ctx, 18);
    a1 = s2;
    a2 = addiu(a2, 4);
    jal(ctx, 0x570E8Cu, gen::fn_sub_570ED0_00570ed0);
    v1 = subu(s0, s2);
    v1 = sll(v1, 3);
    ld(ra, sp, 0x18);
    v1 = addu(s1, v1);
    ld(s1, sp, 0x8);
    v0 = addiu(v1, -57);
    v1 = addiu(v1, -50);
    a0 = slti(v0, 0);
    ld(s0, sp, 0x0);
    if (a0 != 0) v0 = v1;
    v0 = sra(v0, 3);
    v0 = addu(s2, v0);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
    return;
L_00570e84_15:
    charge(ctx, 1);
    a0 = t2;
    goto L_00570e88;
}

// 0x00570ED0 sub_570ED0 -- 372 bytes; frame 0x60: s2 sp+0x30, s4 sp+0x40, s5 sp+0x48, s6 sp+0x50, s0 sp+0x20, s1 sp+0x28, s3 sp+0x38, ra sp+0x58
// MPEG-2 video: delivers user data to the consumer of the current header kind (record +272 + 12 * kind): puts the
// bytes into its stream joint (vtable +24 GetChunk, memcpy, +32 PutChunk; twice when the chunk wraps) and calls its
// callback (+12, with +16 and the kind). Kind 3 (picture) also appends them to the user-data buffer (sub_571048),
// after the 8-byte "\0\0\1\xB2" + "2nd" marker at 0x7C78C8 when +1316 is set.
void sub_570ED0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00570ed0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s2, sp, 0x30);
    s2 = a0;
    sd(s4, sp, 0x40);
    sd(s5, sp, 0x48);
    s5 = a2;
    sd(s6, sp, 0x50);
    sd(s0, sp, 0x20);
    sd(s1, sp, 0x28);
    sd(s3, sp, 0x38);
    sd(ra, sp, 0x58);
    lw(s3, s2, L15::m2v::kHdrKind);
    v0 = sll(s3, 1);
    v0 = addu(v0, s3);
    v0 = sll(v0, 2);
    s4 = addiu(v0, 272);
    v1 = addu(s2, s4);
    lw(s1, v1, 8);
    s6 = a1;
    if (s1 != 0) {
        // 0x00570f20
        charge(ctx, 20);
        lw(v1, s1, 0);
        a3 = sp;
        a0 = s1;
        lw(v0, v1, 24);
        a1 = 0;
        jalr(ctx, 0x570F30u, v0.u());
        a1 = s6;
        lw(a0, sp, 0x0);
        link(ctx, 0x570F40u);  // $ra first: the delay slot below depends on it
        lw(a2, sp, 0x4);
        call(ctx, gen::fn_memcpy_00521250);
        lw(v1, s1, 0);
        a0 = s1;
        a1 = 1;
        lw(v0, v1, 32);
        a2 = sp;
        jalr(ctx, 0x570F58u, v0.u());
        lw(a0, sp, 0x4);
        v0 = slt(a0, s5);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = addu(s2, s4);
        if (!cc) {
            // 0x00570f70
            charge(ctx, 20);
            lw(v1, s1, 0);
            s0 = addiu(sp, 0x10);
            a2 = subu(s5, a0);
            a0 = s1;
            lw(v0, v1, 24);
            a1 = 0;
            a3 = s0;
            jalr(ctx, 0x570F88u, v0.u());
            lw(a1, sp, 0x4);
            lw(a0, sp, 0x10);
            lw(a2, sp, 0x14);
            a1 = addu(s6, a1);
            jal(ctx, 0x570F9Cu, gen::fn_memcpy_00521250);
            lw(v1, s1, 0);
            a0 = s1;
            a2 = s0;
            lw(v0, v1, 32);
            a1 = 1;
            jalr(ctx, 0x570FB4u, v0.u());
            v0 = addu(s2, s4);
        }
        // 0x00570fc0
        charge(ctx, 3);
        lw(v1, v0, 12);
        if (v1 != 0) {
            // 0x00570fcc
            charge(ctx, 3);
            lw(a0, v0, 16);
            a1 = s3;
            jalr(ctx, 0x570FD0u, v1.u());
            goto L_00570fd8;
        }
        v0 = 3;
        goto L_00570fdc;
    }
L_00570fd8:
    charge(ctx, 1);
    v0 = 3;
L_00570fdc:
    charge(ctx, 2);
    ld(s0, sp, 0x20);
    if (s3 == v0) {
        // 0x00570fe4
        charge(ctx, 3);
        lw(v0, s2, 328);
        ld(s1, sp, 0x28);
        if (v0 != 0) {
            // 0x00570ff0
            charge(ctx, 3);
            lw(v0, s2, 1316);
            a1 = 0x7C0000;
            if (v0 != 0) {
                // 0x00570ffc
                charge(ctx, 4);
                a0 = s2;
                a1 = addiu(a1, 30920);
                a2 = 8;
                jal(ctx, 0x571004u, gen::fn_sub_571048_00571048);
            }
            // 0x0057100c
            charge(ctx, 5);
            a0 = s2;
            a1 = s6;
            a2 = s5;
            jal(ctx, 0x571014u, gen::fn_sub_571048_00571048);
            ld(s0, sp, 0x20);
            goto L_00571020;
        }
        // 0x00571024 (the shared epilogue, written out on this path)
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
L_00571020:
    charge(ctx, 1);
    ld(s1, sp, 0x28);
    // 0x00571024 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x00571048 sub_571048 -- 64 bytes; frame 0x10: ra sp+0x0
// Appends up to $a2 bytes to the bounded buffer at $a0 + 328 (base, capacity +332, used +336): copies min(n, cap -
// used) bytes with memcpy (tail call) and advances the used count.
void sub_571048(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00571048
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = addiu(a0, 328);
    sd(ra, sp, 0x0);
    t0 = a2;
    lw(v0, a3, 8);
    lw(a2, a3, 4);
    lw(a0, a3, 0);
    a2 = subu(a2, v0);
    ld(ra, sp, 0x0);
    v1 = slt(t0, a2);
    a0 = addu(a0, v0);
    if (v1 != 0) a2 = t0;
    v0 = addu(v0, a2);
    sw(v0, a3, 8);
    sp = addiu(sp, 0x10);
    gen::fn_memcpy_00521250(ctx);  // tail call
}

// 0x00571088 sub_571088 -- 12256 bytes; frame 0x40: s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s0 sp+0x0, s2 sp+0x10, ra sp+0x38
// MPEG-2 video: the extension parser (start code 0x1B5): bumps +1532, takes the 4-bit extension id into +416, counts
// unexpected ids, then a switch (jump table 0x7C78F0) on id - 1 parses the extension (MPEG-2 ids: 1 sequence, 2
// sequence display, 3 quant matrix, 7 picture display, 8 picture coding, ...) field by field into the record at $a0 +
// 352. Returns the byte after the extension.
void sub_571088(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00571088
    enter(ctx, 49);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = si(-4);
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    s5 = a0;
    sd(s6, sp, 0x30);
    s6 = a1;
    sd(s0, sp, 0x0);
    s4 = addiu(s5, 352);
    sd(s2, sp, 0x10);
    s1 = s6 & v1;
    sd(ra, sp, 0x38);
    a0 = subu(s6, s1);
    s3 = sll(a0, 3);
    lw(v0, s4, 1180);
    v0 = addiu(v0, 1);
    sw(v0, s4, 1180);
    lb(s2, s1, 0);
    s1 = addiu(s1, 1);
    lbu(v1, s1, 0);
    s1 = addiu(s1, 1);
    lbu(a0, s1, 0);
    s1 = addiu(s1, 1);
    lbu(a1, s1, 0);
    s1 = addiu(s1, 1);
    lb(s0, s1, 0);
    s1 = addiu(s1, 1);
    lbu(v0, s1, 0);
    s1 = addiu(s1, 1);
    s2 = sll(s2, 8);
    s0 = sll(s0, 8);
    s2 = s2 | v1;
    lbu(v1, s1, 0);
    s0 = s0 | v0;
    s2 = sll(s2, 8);
    s1 = addiu(s1, 1);
    s0 = sll(s0, 8);
    s2 = s2 | a0;
    lbu(v0, s1, 0);
    s0 = s0 | v1;
    s2 = sll(s2, 8);
    s0 = sll(s0, 8);
    s2 = s2 | a1;
    s1 = addiu(s1, 1);
    s0 = s0 | v0;
    s2 = sllv(s2, s3);
    if (s3 == 0) {
        // 0x00571168
        charge(ctx, 2);
        sw(s2, s4, 52);
        s2 = s0;
    } else {
        // 0x0057114c
        charge(ctx, 6);
        v0 = subu(0, s3);
        v0 = srlv(s0, v0);
        v0 = s2 | v0;
        s2 = sllv(s0, s3);
        sw(v0, s4, 52);
    }
    // 0x00571170
    charge(ctx, 16);
    lb(s0, s1, 0);
    s1 = addiu(s1, 1);
    lbu(v0, s1, 0);
    s1 = addiu(s1, 1);
    s0 = sll(s0, 8);
    lbu(v1, s1, 0);
    s0 = s0 | v0;
    v0 = slti(s3, 28);
    s1 = addiu(s1, 1);
    s0 = sll(s0, 8);
    lbu(a0, s1, 0);
    s1 = addiu(s1, 1);
    s0 = s0 | v1;
    s0 = sll(s0, 8);
    s0 = s0 | a0;
    if (v0 != 0) {
        // 0x00571220
        charge(ctx, 4);
        v0 = srl(s2, 28);
        s2 = sll(s2, 4);
        sw(v0, s4, 64);
        s3 = addiu(s3, 4);
    } else {
        // 0x005711b0
        charge(ctx, 3);
        s3 = addiu(s3, -28);
        v0 = 4;
        if (s3 == 0) {
            // 0x005711d8
            charge(ctx, 3);
            v0 = srl(s2, 28);
            s2 = s0;
            sw(v0, s4, 64);
        } else {
            // 0x005711bc
            charge(ctx, 7);
            v0 = subu(v0, s3);
            v0 = srlv(s0, v0);
            s2 = s2 | v0;
            v1 = srl(s2, 28);
            s2 = sllv(s0, s3);
            sw(v1, s4, 64);
        }
        // 0x005711e4
        charge(ctx, 15);
        lb(s0, s1, 0);
        s1 = addiu(s1, 1);
        lbu(v0, s1, 0);
        s1 = addiu(s1, 1);
        s0 = sll(s0, 8);
        lbu(v1, s1, 0);
        s0 = s0 | v0;
        s1 = addiu(s1, 1);
        s0 = sll(s0, 8);
        lbu(v0, s1, 0);
        s0 = s0 | v1;
        s1 = addiu(s1, 1);
        s0 = sll(s0, 8);
        s0 = s0 | v0;
    }
    // 0x00571230
    charge(ctx, 3);
    lw(v1, s4, 776);
    v0 = 16;
    if (v1 != 0) {
        // 0x0057123c
        charge(ctx, 2);
        if (v1 == v0) {
            goto L_00571244;
        }
        lw(v1, s4, 64);
        // 0x00571260
        charge(ctx, 1);
        lw(v0, s4, 1272);
    L_00571264:
        charge(ctx, 2);
        v0 = addiu(v0, 1);
        sw(v0, s4, 1272);
    L_0057126c:
        charge(ctx, 1);
        lw(a0, s4, 1156);
        goto L_00571270;
    }
L_00571244:
    charge(ctx, 3);
    lw(v0, s4, 780);
    lw(v1, s4, 64);
    if (v0 == 0) {
        goto L_0057126c;
    }
    // 0x00571250
    charge(ctx, 2);
    if (v0 != v1) {
        // 0x00571258
        charge(ctx, 2);
        lw(v0, s4, 1272);
        goto L_00571264;
    }
    lw(a0, s4, 1156);
L_00571270:
    charge(ctx, 3);
    v0 = 1;
    cc = a0 == v0;  // the condition, before the delay slot changes it
    v0 = addiu(v1, -1);
    if (!cc) {
        // 0x0057127c
        charge(ctx, 3);
        v0 = sltiu(v0, 2);
        if (v0 == 0) {
            // 0x00571288
            charge(ctx, 3);
            v0 = 5;
            if (v1 != v0) {
                goto L_00571294;
            }
            lw(v0, s4, 1272);
            goto L_005712d4;
        }
        lw(v0, s4, 1272);
    L_005712d4:
        charge(ctx, 3);
        v0 = addiu(v0, 1);
        sw(v0, s4, 1272);
        v1 = addiu(v1, -1);
        goto L_005712e0;
    }
L_00571294:
    charge(ctx, 3);
    v0 = 3;
    if (a0 != v0) {
        // 0x005712a0
        charge(ctx, 2);
        cc = v1 == v0;  // the condition, before the delay slot changes it
        v0 = 4;
        if (!cc) {
            // 0x005712a8
            charge(ctx, 2);
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = 7;
            if (cc) {
                goto L_005712d0;
            }
            // 0x005712b0
            charge(ctx, 2);
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = 8;
            if (cc) {
                goto L_005712d0;
            }
            // 0x005712b8
            charge(ctx, 2);
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = 9;
            if (cc) {
                goto L_005712d0;
            }
            // 0x005712c0
            charge(ctx, 2);
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = 10;
            if (cc) {
                goto L_005712d0;
            }
            // 0x005712c8
            charge(ctx, 2);
            if (v1 == v0) {
                goto L_005712d0;
            }
            v1 = addiu(v1, -1);
            goto L_005712e0;
        }
    L_005712d0:
        charge(ctx, 1);
        lw(v0, s4, 1272);
        goto L_005712d4;
    }
    v1 = addiu(v1, -1);
L_005712e0:
    charge(ctx, 3);
    v0 = sltiu(v1, 10);
    if (v0 == 0) {
        lw(v0, s4, 1272);
    } else {
        // 0x005712ec
        charge(ctx, 6);
        v0 = sll(v1, 2);
        v1 = 0x7C0000;
        v1 = addu(v1, v0);
        lw(v1, v1, 30960);
        switch (v1.u()) {
        case 0x571308u:  // table[0]
            // 0x00571308
            charge(ctx, 3);
            v0 = slti(s3, 24);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 24);
            if (cc) {
                // 0x00571388
                charge(ctx, 3);
                s2 = sll(s2, 8);
                sw(v0, s4, 68);
                s3 = addiu(s3, 8);
            } else {
                // 0x00571314
                charge(ctx, 3);
                s3 = addiu(s3, -24);
                v0 = 8;
                if (s3 == 0) {
                    // 0x00571340
                    charge(ctx, 3);
                    v0 = srl(s2, 24);
                    s2 = s0;
                    sw(v0, s4, 68);
                } else {
                    // 0x00571320
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 24);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 68);
                }
                // 0x0057134c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00571394
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00571410
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 72);
                s3 = addiu(s3, 1);
            } else {
                // 0x005713a0
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x005713c8
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 72);
                } else {
                    // 0x005713ac
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 72);
                }
                // 0x005713d4
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x0057141c
            charge(ctx, 3);
            v0 = slti(s3, 30);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 30);
            if (cc) {
                // 0x00571498
                charge(ctx, 3);
                s2 = sll(s2, 2);
                sw(v0, s4, 76);
                s3 = addiu(s3, 2);
            } else {
                // 0x00571428
                charge(ctx, 3);
                s3 = addiu(s3, -30);
                v0 = 2;
                if (s3 == 0) {
                    // 0x00571450
                    charge(ctx, 3);
                    v0 = srl(s2, 30);
                    s2 = s0;
                    sw(v0, s4, 76);
                } else {
                    // 0x00571434
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 30);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 76);
                }
                // 0x0057145c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x005714a4
            charge(ctx, 3);
            v0 = slti(s3, 30);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 30);
            if (cc) {
                // 0x00571520
                charge(ctx, 3);
                s2 = sll(s2, 2);
                sw(v0, s4, 80);
                s3 = addiu(s3, 2);
            } else {
                // 0x005714b0
                charge(ctx, 3);
                s3 = addiu(s3, -30);
                v0 = 2;
                if (s3 == 0) {
                    // 0x005714d8
                    charge(ctx, 3);
                    v0 = srl(s2, 30);
                    s2 = s0;
                    sw(v0, s4, 80);
                } else {
                    // 0x005714bc
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 30);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 80);
                }
                // 0x005714e4
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x0057152c
            charge(ctx, 3);
            v0 = slti(s3, 30);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 30);
            if (cc) {
                // 0x005715a8
                charge(ctx, 3);
                s2 = sll(s2, 2);
                sw(v0, s4, 84);
                s3 = addiu(s3, 2);
            } else {
                // 0x00571538
                charge(ctx, 3);
                s3 = addiu(s3, -30);
                v0 = 2;
                if (s3 == 0) {
                    // 0x00571560
                    charge(ctx, 3);
                    v0 = srl(s2, 30);
                    s2 = s0;
                    sw(v0, s4, 84);
                } else {
                    // 0x00571544
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 30);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 84);
                }
                // 0x0057156c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x005715b4
            charge(ctx, 3);
            v0 = slti(s3, 20);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 20);
            if (cc) {
                // 0x00571630
                charge(ctx, 3);
                s2 = sll(s2, 12);
                sw(v0, s4, 88);
                s3 = addiu(s3, 12);
            } else {
                // 0x005715c0
                charge(ctx, 3);
                s3 = addiu(s3, -20);
                v0 = 12;
                if (s3 == 0) {
                    // 0x005715e8
                    charge(ctx, 3);
                    v0 = srl(s2, 20);
                    s2 = s0;
                    sw(v0, s4, 88);
                } else {
                    // 0x005715cc
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 20);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 88);
                }
                // 0x005715f4
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x0057163c
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x005716b8
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 24);
                s3 = addiu(s3, 1);
            } else {
                // 0x00571648
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00571670
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 24);
                } else {
                    // 0x00571654
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 24);
                }
                // 0x0057167c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x005716c4
            charge(ctx, 3);
            v0 = slti(s3, 24);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 24);
            if (cc) {
                // 0x00571740
                charge(ctx, 3);
                s2 = sll(s2, 8);
                sw(v0, s4, 92);
                s3 = addiu(s3, 8);
            } else {
                // 0x005716d0
                charge(ctx, 3);
                s3 = addiu(s3, -24);
                v0 = 8;
                if (s3 == 0) {
                    // 0x005716f8
                    charge(ctx, 3);
                    v0 = srl(s2, 24);
                    s2 = s0;
                    sw(v0, s4, 92);
                } else {
                    // 0x005716dc
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 24);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 92);
                }
                // 0x00571704
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x0057174c
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x005717c8
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 96);
                s3 = addiu(s3, 1);
            } else {
                // 0x00571758
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00571780
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 96);
                } else {
                    // 0x00571764
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 96);
                }
                // 0x0057178c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x005717d4
            charge(ctx, 3);
            v0 = slti(s3, 30);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 30);
            if (cc) {
                // 0x00571850
                charge(ctx, 3);
                s2 = sll(s2, 2);
                sw(v0, s4, 100);
                s3 = addiu(s3, 2);
            } else {
                // 0x005717e0
                charge(ctx, 3);
                s3 = addiu(s3, -30);
                v0 = 2;
                if (s3 == 0) {
                    // 0x00571808
                    charge(ctx, 3);
                    v0 = srl(s2, 30);
                    s2 = s0;
                    sw(v0, s4, 100);
                } else {
                    // 0x005717ec
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 30);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 100);
                }
                // 0x00571814
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x0057185c
            charge(ctx, 3);
            v0 = slti(s3, 27);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 27);
            if (cc) {
                // 0x005718a0
                charge(ctx, 2);
                s3 = addiu(s3, 5);
                sw(v0, s4, 104);
            } else {
                // 0x00571868
                charge(ctx, 3);
                s3 = addiu(s3, -27);
                v0 = 5;
                if (s3 == 0) {
                    // 0x00571890
                    charge(ctx, 2);
                    v0 = srl(s2, 27);
                    sw(v0, s4, 104);
                } else {
                    // 0x00571874
                    charge(ctx, 6);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 27);
                    sw(v1, s4, 104);
                }
                // 0x00571898
                charge(ctx, 2);
                s1 = addiu(s1, 4);
            }
            // 0x005718a8
            charge(ctx, 4);
            lw(v1, s4, 76);
            a0 = 1;
            cc = v1 == a0;  // the condition, before the delay slot changes it
            v1 = sll(v1, 2);
            if (!cc) {
                // 0x005718b8
                charge(ctx, 6);
                lw(v0, s4, 1272);
                v1 = 1;
                sw(a0, s4, 76);
                v0 = addiu(v0, 1);
                sw(v0, s4, 1272);
                v1 = sll(v1, 2);
            }
            // 0x005718d0
            charge(ctx, 17);
            a0 = s4;
            v0 = 0x7C0000;
            v0 = addu(v0, v1);
            lw(v0, v0, 30896);
            link(ctx, 0x5718E0u);  // $ra first: the delay slot below depends on it
            sw(v0, s4, 792);
            call(ctx, gen::fn_sub_570248_00570248);
            lw(v0, s4, 88);
            lw(v1, s4, 92);
            lw(a1, s4, 20);
            v0 = sll(v0, 18);
            lw(a0, s4, 28);
            v1 = sll(v1, 10);
            v0 = v0 | a1;
            v1 = v1 | a0;
            sw(v0, s4, 724);
            sw(v1, s4, 728);
        L_00574014:
            charge(ctx, 1);
            v1 = subu(s1, s6);
            break;
        case 0x571918u:  // table[1]
            // 0x00571918
            charge(ctx, 3);
            v0 = slti(s3, 29);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 29);
            if (cc) {
                // 0x00571998
                charge(ctx, 3);
                s2 = sll(s2, 3);
                sw(v0, s4, 108);
                s3 = addiu(s3, 3);
            } else {
                // 0x00571924
                charge(ctx, 3);
                s3 = addiu(s3, -29);
                v0 = 3;
                if (s3 == 0) {
                    // 0x00571950
                    charge(ctx, 3);
                    v0 = srl(s2, 29);
                    s2 = s0;
                    sw(v0, s4, 108);
                } else {
                    // 0x00571930
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 29);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 108);
                }
                // 0x0057195c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x005719a4
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00571a20
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 112);
                s3 = addiu(s3, 1);
            } else {
                // 0x005719b0
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x005719d8
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 112);
                } else {
                    // 0x005719bc
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 112);
                }
                // 0x005719e4
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00571a2c
            charge(ctx, 3);
            lw(v0, s4, 112);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = slti(s3, 24);
            if (!cc) {
                // 0x00571a38
                charge(ctx, 2);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 24);
                if (cc) {
                    // 0x00571ab0
                    charge(ctx, 3);
                    s2 = sll(s2, 8);
                    sw(v0, s4, 116);
                    s3 = addiu(s3, 8);
                } else {
                    // 0x00571a40
                    charge(ctx, 3);
                    s3 = addiu(s3, -24);
                    v0 = 8;
                    if (s3 == 0) {
                        // 0x00571a68
                        charge(ctx, 3);
                        v0 = srl(s2, 24);
                        s2 = s0;
                        sw(v0, s4, 116);
                    } else {
                        // 0x00571a4c
                        charge(ctx, 7);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 24);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 116);
                    }
                    // 0x00571a74
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x00571abc
                charge(ctx, 3);
                v0 = slti(s3, 24);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 24);
                if (cc) {
                    // 0x00571b38
                    charge(ctx, 3);
                    s2 = sll(s2, 8);
                    sw(v0, s4, 120);
                    s3 = addiu(s3, 8);
                } else {
                    // 0x00571ac8
                    charge(ctx, 3);
                    s3 = addiu(s3, -24);
                    v0 = 8;
                    if (s3 == 0) {
                        // 0x00571af0
                        charge(ctx, 3);
                        v0 = srl(s2, 24);
                        s2 = s0;
                        sw(v0, s4, 120);
                    } else {
                        // 0x00571ad4
                        charge(ctx, 7);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 24);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 120);
                    }
                    // 0x00571afc
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x00571b44
                charge(ctx, 3);
                v0 = slti(s3, 24);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 24);
                if (cc) {
                    // 0x00571bc0
                    charge(ctx, 3);
                    s2 = sll(s2, 8);
                    sw(v0, s4, 124);
                    s3 = addiu(s3, 8);
                } else {
                    // 0x00571b50
                    charge(ctx, 3);
                    s3 = addiu(s3, -24);
                    v0 = 8;
                    if (s3 == 0) {
                        // 0x00571b78
                        charge(ctx, 3);
                        v0 = srl(s2, 24);
                        s2 = s0;
                        sw(v0, s4, 124);
                    } else {
                        // 0x00571b5c
                        charge(ctx, 7);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 24);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 124);
                    }
                    // 0x00571b84
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
            }
            // 0x00571bcc
            charge(ctx, 3);
            v0 = slti(s3, 18);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 18);
            if (cc) {
                // 0x00571c48
                charge(ctx, 3);
                s2 = sll(s2, 14);
                sw(v0, s4, 128);
                s3 = addiu(s3, 14);
            } else {
                // 0x00571bd8
                charge(ctx, 3);
                s3 = addiu(s3, -18);
                v0 = 14;
                if (s3 == 0) {
                    // 0x00571c00
                    charge(ctx, 3);
                    v0 = srl(s2, 18);
                    s2 = s0;
                    sw(v0, s4, 128);
                } else {
                    // 0x00571be4
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 18);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 128);
                }
                // 0x00571c0c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00571c54
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00571cd0
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 24);
                s3 = addiu(s3, 1);
            } else {
                // 0x00571c60
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00571c88
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 24);
                } else {
                    // 0x00571c6c
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 24);
                }
                // 0x00571c94
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00571cdc
            charge(ctx, 3);
            v0 = slti(s3, 18);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 18);
            if (cc) {
                // 0x00571d20
                charge(ctx, 3);
                s3 = addiu(s3, 14);
                sw(v0, s4, 132);
            } else {
                // 0x00571ce8
                charge(ctx, 3);
                s3 = addiu(s3, -18);
                v0 = 14;
                if (s3 == 0) {
                    // 0x00571d10
                    charge(ctx, 3);
                    v0 = srl(s2, 18);
                    sw(v0, s4, 132);
                } else {
                    // 0x00571cf4
                    charge(ctx, 6);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 18);
                    sw(v1, s4, 132);
                }
            L_00573ff0:
                charge(ctx, 2);
                s1 = addiu(s1, 4);
            }
            goto L_00574014;
        case 0x571D30u:  // table[2]
            // 0x00571d30
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00571db0
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 36);
                s3 = addiu(s3, 1);
            } else {
                // 0x00571d3c
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00571d68
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 36);
                } else {
                    // 0x00571d48
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 36);
                }
                // 0x00571d74
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00571dbc
            charge(ctx, 3);
            lw(v0, s4, 36);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = slti(s3, 31);
            if (!cc) {
                // 0x00571dc8
                charge(ctx, 2);
                a0 = 63;
                s3 = addiu(s3, 8);
                for (;;) {
                    // 0x00571dd0
                    charge(ctx, 3);
                    v0 = slti(s3, 32);
                    if (v0 != 0) {
                        s2 = sll(s2, 8);
                    } else {
                        // 0x00571ddc
                        charge(ctx, 16);
                        s3 = addiu(s3, -32);
                        s2 = sllv(s0, s3);
                        lb(s0, s1, 0);
                        s1 = addiu(s1, 1);
                        lbu(v0, s1, 0);
                        s1 = addiu(s1, 1);
                        s0 = sll(s0, 8);
                        lbu(v1, s1, 0);
                        s0 = s0 | v0;
                        s1 = addiu(s1, 1);
                        s0 = sll(s0, 8);
                        lbu(v0, s1, 0);
                        s0 = s0 | v1;
                        s1 = addiu(s1, 1);
                        s0 = sll(s0, 8);
                        s0 = s0 | v0;
                    }
                    // 0x00571e1c
                    charge(ctx, 3);
                    a0 = addiu(a0, -1);
                    if (i64(a0) < 0) {
                        break;
                    }
                    s3 = addiu(s3, 8);
                    backedge(ctx);
                }
                // 0x00571e28
                charge(ctx, 1);
                v0 = slti(s3, 31);
            }
            // 0x00571e2c
            charge(ctx, 2);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00571ea8
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 40);
                s3 = addiu(s3, 1);
            } else {
                // 0x00571e34
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00571e60
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 40);
                } else {
                    // 0x00571e40
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 40);
                }
                // 0x00571e6c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00571eb4
            charge(ctx, 3);
            lw(v0, s4, 40);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = slti(s3, 31);
            if (!cc) {
                // 0x00571ec0
                charge(ctx, 2);
                a0 = 63;
                s3 = addiu(s3, 8);
                for (;;) {
                    // 0x00571ec8
                    charge(ctx, 3);
                    v0 = slti(s3, 32);
                    if (v0 != 0) {
                        s2 = sll(s2, 8);
                    } else {
                        // 0x00571ed4
                        charge(ctx, 16);
                        s3 = addiu(s3, -32);
                        s2 = sllv(s0, s3);
                        lb(s0, s1, 0);
                        s1 = addiu(s1, 1);
                        lbu(v0, s1, 0);
                        s1 = addiu(s1, 1);
                        s0 = sll(s0, 8);
                        lbu(v1, s1, 0);
                        s0 = s0 | v0;
                        s1 = addiu(s1, 1);
                        s0 = sll(s0, 8);
                        lbu(v0, s1, 0);
                        s0 = s0 | v1;
                        s1 = addiu(s1, 1);
                        s0 = sll(s0, 8);
                        s0 = s0 | v0;
                    }
                    // 0x00571f14
                    charge(ctx, 3);
                    a0 = addiu(a0, -1);
                    if (i64(a0) < 0) {
                        break;
                    }
                    s3 = addiu(s3, 8);
                    backedge(ctx);
                }
                // 0x00571f20
                charge(ctx, 1);
                v0 = slti(s3, 31);
            }
            // 0x00571f24
            charge(ctx, 2);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00571fa0
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 344);
                s3 = addiu(s3, 1);
            } else {
                // 0x00571f2c
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00571f58
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 344);
                } else {
                    // 0x00571f38
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 344);
                }
                // 0x00571f64
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00571fac
            charge(ctx, 3);
            lw(v0, s4, 344);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = slti(s3, 31);
            if (!cc) {
                // 0x00571fb8
                charge(ctx, 2);
                a0 = 63;
                s3 = addiu(s3, 8);
                for (;;) {
                    // 0x00571fc0
                    charge(ctx, 3);
                    v0 = slti(s3, 32);
                    if (v0 != 0) {
                        s2 = sll(s2, 8);
                    } else {
                        // 0x00571fcc
                        charge(ctx, 16);
                        s3 = addiu(s3, -32);
                        s2 = sllv(s0, s3);
                        lb(s0, s1, 0);
                        s1 = addiu(s1, 1);
                        lbu(v0, s1, 0);
                        s1 = addiu(s1, 1);
                        s0 = sll(s0, 8);
                        lbu(v1, s1, 0);
                        s0 = s0 | v0;
                        s1 = addiu(s1, 1);
                        s0 = sll(s0, 8);
                        lbu(v0, s1, 0);
                        s0 = s0 | v1;
                        s1 = addiu(s1, 1);
                        s0 = sll(s0, 8);
                        s0 = s0 | v0;
                    }
                    // 0x0057200c
                    charge(ctx, 3);
                    a0 = addiu(a0, -1);
                    if (i64(a0) < 0) {
                        break;
                    }
                    s3 = addiu(s3, 8);
                    backedge(ctx);
                }
                // 0x00572018
                charge(ctx, 1);
                v0 = slti(s3, 31);
            }
            // 0x0057201c
            charge(ctx, 2);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00572058
                charge(ctx, 2);
                s3 = addiu(s3, 1);
                sw(v0, s4, 348);
            } else {
                // 0x00572024
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00572048
                    charge(ctx, 2);
                    v0 = srl(s2, 31);
                    sw(v0, s4, 348);
                } else {
                    // 0x00572030
                    charge(ctx, 6);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    sw(v1, s4, 348);
                }
                // 0x00572050
                charge(ctx, 2);
                s1 = addiu(s1, 4);
            }
            // 0x00572060
            charge(ctx, 3);
            lw(v0, s4, 348);
            if (v0 != 0) {
                // 0x0057206c
                charge(ctx, 3);
                v1 = 63;
                s3 = addiu(s3, 8);
                for (;;) {
                    // 0x00572078
                    charge(ctx, 3);
                    v0 = slti(s3, 32);
                    v1 = addiu(v1, -1);
                    if (v0 == 0) {
                        // 0x00572084
                        charge(ctx, 2);
                        s3 = addiu(s3, -32);
                        s1 = addiu(s1, 4);
                    }
                    // 0x0057208c
                    charge(ctx, 4);
                    if (i64(v1) < 0) {
                        break;
                    }
                    s3 = addiu(s3, 8);
                    backedge(ctx);
                }
            }
            // 0x0057209c
            charge(ctx, 4);
            a0 = s4;
            jal(ctx, 0x57209Cu, gen::fn_sub_5703B8_005703b8);
            v1 = subu(s1, s6);
            break;
        case 0x5720B0u:  // table[3]
            // 0x005720b0
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00572130
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 412);
                s3 = addiu(s3, 1);
            } else {
                // 0x005720bc
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x005720e8
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 412);
                } else {
                    // 0x005720c8
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 412);
                }
                // 0x005720f4
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x0057213c
            charge(ctx, 3);
            v0 = slti(s3, 24);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 24);
            if (cc) {
                // 0x005721b8
                charge(ctx, 3);
                s2 = sll(s2, 8);
                sw(v0, s4, 416);
                s3 = addiu(s3, 8);
            } else {
                // 0x00572148
                charge(ctx, 3);
                s3 = addiu(s3, -24);
                v0 = 8;
                if (s3 == 0) {
                    // 0x00572170
                    charge(ctx, 3);
                    v0 = srl(s2, 24);
                    s2 = s0;
                    sw(v0, s4, 416);
                } else {
                    // 0x00572154
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 24);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 416);
                }
                // 0x0057217c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x005721c4
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00572240
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 420);
                s3 = addiu(s3, 1);
            } else {
                // 0x005721d0
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x005721f8
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 420);
                } else {
                    // 0x005721dc
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 420);
                }
                // 0x00572204
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x0057224c
            charge(ctx, 3);
            v0 = slti(s3, 25);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 25);
            if (cc) {
                // 0x005722c8
                charge(ctx, 3);
                s2 = sll(s2, 7);
                sw(v0, s4, 424);
                s3 = addiu(s3, 7);
            } else {
                // 0x00572258
                charge(ctx, 3);
                s3 = addiu(s3, -25);
                v0 = 7;
                if (s3 == 0) {
                    // 0x00572280
                    charge(ctx, 3);
                    v0 = srl(s2, 25);
                    s2 = s0;
                    sw(v0, s4, 424);
                } else {
                    // 0x00572264
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 25);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 424);
                }
                // 0x0057228c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x005722d4
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00572350
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 24);
                s3 = addiu(s3, 1);
            } else {
                // 0x005722e0
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00572308
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 24);
                } else {
                    // 0x005722ec
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 24);
                }
                // 0x00572314
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x0057235c
            charge(ctx, 3);
            v0 = slti(s3, 12);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 12);
            if (cc) {
                // 0x005723d8
                charge(ctx, 3);
                s2 = sll(s2, 20);
                sw(v0, s4, 428);
                s3 = addiu(s3, 20);
            } else {
                // 0x00572368
                charge(ctx, 3);
                s3 = addiu(s3, -12);
                v0 = 20;
                if (s3 == 0) {
                    // 0x00572390
                    charge(ctx, 3);
                    v0 = srl(s2, 12);
                    s2 = s0;
                    sw(v0, s4, 428);
                } else {
                    // 0x00572374
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 12);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 428);
                }
                // 0x0057239c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x005723e4
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00572460
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 24);
                s3 = addiu(s3, 1);
            } else {
                // 0x005723f0
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00572418
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 24);
                } else {
                    // 0x005723fc
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 24);
                }
                // 0x00572424
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x0057246c
            charge(ctx, 3);
            v0 = slti(s3, 10);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 10);
            if (cc) {
                // 0x005724e8
                charge(ctx, 3);
                s2 = sll(s2, 22);
                sw(v0, s4, 432);
                s3 = addiu(s3, 22);
            } else {
                // 0x00572478
                charge(ctx, 3);
                s3 = addiu(s3, -10);
                v0 = 22;
                if (s3 == 0) {
                    // 0x005724a0
                    charge(ctx, 3);
                    v0 = srl(s2, 10);
                    s2 = s0;
                    sw(v0, s4, 432);
                } else {
                    // 0x00572484
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 10);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 432);
                }
                // 0x005724ac
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x005724f4
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00572570
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 24);
                s3 = addiu(s3, 1);
            } else {
                // 0x00572500
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00572528
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 24);
                } else {
                    // 0x0057250c
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 24);
                }
                // 0x00572534
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x0057257c
            charge(ctx, 3);
            v0 = slti(s3, 10);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 10);
            if (!cc) {
                // 0x00572588
                charge(ctx, 3);
                s3 = addiu(s3, -10);
                v0 = 22;
                if (s3 == 0) {
                    // 0x005725b0
                    charge(ctx, 3);
                    v0 = srl(s2, 10);
                    sw(v0, s4, 436);
                } else {
                    // 0x00572594
                    charge(ctx, 6);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 10);
                    sw(v1, s4, 436);
                }
                goto L_00573ff0;
            }
            // 0x005725c0
            charge(ctx, 3);
            s3 = addiu(s3, 22);
            sw(v0, s4, 436);
            goto L_00574014;
        case 0x5725D0u:  // table[4]
            // 0x005725d0
            charge(ctx, 4);
            v0 = 1;
            v1 = slti(s3, 30);
            sw(v0, s4, 784);
            if (v1 != 0) {
                // 0x00572650
                charge(ctx, 4);
                v0 = srl(s2, 30);
                s2 = sll(s2, 2);
                sw(v0, s4, 136);
                s3 = addiu(s3, 2);
            } else {
                // 0x005725e0
                charge(ctx, 3);
                s3 = addiu(s3, -30);
                v0 = 2;
                if (s3 == 0) {
                    // 0x00572608
                    charge(ctx, 3);
                    v0 = srl(s2, 30);
                    s2 = s0;
                    sw(v0, s4, 136);
                } else {
                    // 0x005725ec
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 30);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 136);
                }
                // 0x00572614
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00572660
            charge(ctx, 3);
            v0 = slti(s3, 28);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 28);
            if (cc) {
                // 0x005726e0
                charge(ctx, 3);
                s2 = sll(s2, 4);
                sw(v0, s4, 140);
                s3 = addiu(s3, 4);
            } else {
                // 0x0057266c
                charge(ctx, 3);
                s3 = addiu(s3, -28);
                v0 = 4;
                if (s3 == 0) {
                    // 0x00572698
                    charge(ctx, 3);
                    v0 = srl(s2, 28);
                    s2 = s0;
                    sw(v0, s4, 140);
                } else {
                    // 0x00572678
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 28);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 140);
                }
                // 0x005726a4
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x005726ec
            charge(ctx, 4);
            lw(v1, s4, 136);
            a0 = 1;
            v0 = 3;
            if (v1 == a0) {
                // 0x005726fc
                charge(ctx, 3);
                v0 = slti(s3, 18);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 18);
                if (cc) {
                    // 0x00572778
                    charge(ctx, 3);
                    s2 = sll(s2, 14);
                    sw(v0, s4, 144);
                    s3 = addiu(s3, 14);
                } else {
                    // 0x00572708
                    charge(ctx, 3);
                    s3 = addiu(s3, -18);
                    v0 = 14;
                    if (s3 == 0) {
                        // 0x00572730
                        charge(ctx, 3);
                        v0 = srl(s2, 18);
                        s2 = s0;
                        sw(v0, s4, 144);
                    } else {
                        // 0x00572714
                        charge(ctx, 7);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 18);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 144);
                    }
                    // 0x0057273c
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x00572784
                charge(ctx, 3);
                v0 = slti(s3, 31);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 31);
                if (cc) {
                    // 0x00572800
                    charge(ctx, 3);
                    s2 = sll(s2, 1);
                    sw(v0, s4, 24);
                    s3 = addiu(s3, 1);
                } else {
                    // 0x00572790
                    charge(ctx, 3);
                    s3 = addiu(s3, -31);
                    v0 = 1;
                    if (s3 == 0) {
                        // 0x005727b8
                        charge(ctx, 3);
                        v0 = srl(s2, 31);
                        s2 = s0;
                        sw(v0, s4, 24);
                    } else {
                        // 0x0057279c
                        charge(ctx, 7);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 31);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 24);
                    }
                    // 0x005727c4
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x0057280c
                charge(ctx, 3);
                v0 = slti(s3, 18);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 18);
                if (cc) {
                    // 0x00572888
                    charge(ctx, 3);
                    s2 = sll(s2, 14);
                    sw(v0, s4, 148);
                    s3 = addiu(s3, 14);
                } else {
                    // 0x00572818
                    charge(ctx, 3);
                    s3 = addiu(s3, -18);
                    v0 = 14;
                    if (s3 == 0) {
                        // 0x00572840
                        charge(ctx, 3);
                        v0 = srl(s2, 18);
                        s2 = s0;
                        sw(v0, s4, 148);
                    } else {
                        // 0x00572824
                        charge(ctx, 7);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 18);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 148);
                    }
                    // 0x0057284c
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x00572894
                charge(ctx, 3);
                v0 = slti(s3, 27);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 27);
                if (cc) {
                    // 0x00572910
                    charge(ctx, 3);
                    s2 = sll(s2, 5);
                    sw(v0, s4, 152);
                    s3 = addiu(s3, 5);
                } else {
                    // 0x005728a0
                    charge(ctx, 3);
                    s3 = addiu(s3, -27);
                    v0 = 5;
                    if (s3 == 0) {
                        // 0x005728c8
                        charge(ctx, 3);
                        v0 = srl(s2, 27);
                        s2 = s0;
                        sw(v0, s4, 152);
                    } else {
                        // 0x005728ac
                        charge(ctx, 7);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 27);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 152);
                    }
                    // 0x005728d4
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x0057291c
                charge(ctx, 3);
                v0 = slti(s3, 27);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 27);
                if (cc) {
                    // 0x00572998
                    charge(ctx, 3);
                    s2 = sll(s2, 5);
                    sw(v0, s4, 156);
                    s3 = addiu(s3, 5);
                } else {
                    // 0x00572928
                    charge(ctx, 3);
                    s3 = addiu(s3, -27);
                    v0 = 5;
                    if (s3 == 0) {
                        // 0x00572950
                        charge(ctx, 3);
                        v0 = srl(s2, 27);
                        s2 = s0;
                        sw(v0, s4, 156);
                    } else {
                        // 0x00572934
                        charge(ctx, 7);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 27);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 156);
                    }
                    // 0x0057295c
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x005729a4
                charge(ctx, 3);
                v0 = slti(s3, 27);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 27);
                if (cc) {
                    // 0x00572a20
                    charge(ctx, 3);
                    s2 = sll(s2, 5);
                    sw(v0, s4, 160);
                    s3 = addiu(s3, 5);
                } else {
                    // 0x005729b0
                    charge(ctx, 3);
                    s3 = addiu(s3, -27);
                    v0 = 5;
                    if (s3 == 0) {
                        // 0x005729d8
                        charge(ctx, 3);
                        v0 = srl(s2, 27);
                        s2 = s0;
                        sw(v0, s4, 160);
                    } else {
                        // 0x005729bc
                        charge(ctx, 7);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 27);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 160);
                    }
                    // 0x005729e4
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x00572a2c
                charge(ctx, 3);
                v0 = slti(s3, 27);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 27);
                if (!cc) {
                    // 0x00572a38
                    charge(ctx, 3);
                    s3 = addiu(s3, -27);
                    v0 = 5;
                    if (s3 == 0) {
                        // 0x00572a60
                        charge(ctx, 3);
                        v0 = srl(s2, 27);
                        sw(v0, s4, 164);
                    } else {
                        // 0x00572a44
                        charge(ctx, 6);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 27);
                        sw(v1, s4, 164);
                    }
                    goto L_00573ff0;
                }
                // 0x00572a70
                charge(ctx, 3);
                s3 = addiu(s3, 5);
                sw(v0, s4, 164);
                goto L_00574014;
            }
            // 0x00572a80
            charge(ctx, 2);
            if (v1 == v0) {
                // 0x00572a88
                charge(ctx, 3);
                v0 = slti(s3, 31);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 31);
                if (cc) {
                    // 0x00572b00
                    charge(ctx, 3);
                    s2 = sll(s2, 1);
                    sw(v0, s4, 168);
                    s3 = addiu(s3, 1);
                } else {
                    // 0x00572a94
                    charge(ctx, 3);
                    s3 = addiu(s3, -31);
                    v0 = subu(a0, s3);
                    if (s3 == 0) {
                        // 0x00572ab8
                        charge(ctx, 3);
                        v0 = srl(s2, 31);
                        s2 = s0;
                        sw(v0, s4, 168);
                    } else {
                        // 0x00572aa0
                        charge(ctx, 6);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 31);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 168);
                    }
                    // 0x00572ac4
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x00572b0c
                charge(ctx, 3);
                lw(v0, s4, 168);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = slti(s3, 31);
                if (!cc) {
                    // 0x00572b18
                    charge(ctx, 2);
                    cc = v0 != 0;  // the condition, before the delay slot changes it
                    v0 = srl(s2, 31);
                    if (cc) {
                        // 0x00572b90
                        charge(ctx, 3);
                        s2 = sll(s2, 1);
                        sw(v0, s4, 172);
                        s3 = addiu(s3, 1);
                    } else {
                        // 0x00572b20
                        charge(ctx, 3);
                        s3 = addiu(s3, -31);
                        v0 = 1;
                        if (s3 == 0) {
                            // 0x00572b48
                            charge(ctx, 3);
                            v0 = srl(s2, 31);
                            s2 = s0;
                            sw(v0, s4, 172);
                        } else {
                            // 0x00572b2c
                            charge(ctx, 7);
                            v0 = subu(v0, s3);
                            v0 = srlv(s0, v0);
                            s2 = s2 | v0;
                            v1 = srl(s2, 31);
                            s2 = sllv(s0, s3);
                            sw(v1, s4, 172);
                        }
                        // 0x00572b54
                        charge(ctx, 15);
                        lb(s0, s1, 0);
                        s1 = addiu(s1, 1);
                        lbu(v0, s1, 0);
                        s1 = addiu(s1, 1);
                        s0 = sll(s0, 8);
                        lbu(v1, s1, 0);
                        s0 = s0 | v0;
                        s1 = addiu(s1, 1);
                        s0 = sll(s0, 8);
                        lbu(v0, s1, 0);
                        s0 = s0 | v1;
                        s1 = addiu(s1, 1);
                        s0 = sll(s0, 8);
                        s0 = s0 | v0;
                    }
                }
                // 0x00572b9c
                charge(ctx, 3);
                v0 = slti(s3, 29);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 29);
                if (cc) {
                    // 0x00572c18
                    charge(ctx, 3);
                    s2 = sll(s2, 3);
                    sw(v0, s4, 176);
                    s3 = addiu(s3, 3);
                } else {
                    // 0x00572ba8
                    charge(ctx, 3);
                    s3 = addiu(s3, -29);
                    v0 = 3;
                    if (s3 == 0) {
                        // 0x00572bd0
                        charge(ctx, 3);
                        v0 = srl(s2, 29);
                        s2 = s0;
                        sw(v0, s4, 176);
                    } else {
                        // 0x00572bb4
                        charge(ctx, 7);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 29);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 176);
                    }
                    // 0x00572bdc
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x00572c24
                charge(ctx, 3);
                v0 = slti(s3, 29);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 29);
                if (!cc) {
                    // 0x00572c30
                    charge(ctx, 3);
                    s3 = addiu(s3, -29);
                    v0 = 3;
                    if (s3 == 0) {
                        // 0x00572c58
                        charge(ctx, 3);
                        v0 = srl(s2, 29);
                        sw(v0, s4, 180);
                    } else {
                        // 0x00572c3c
                        charge(ctx, 6);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 29);
                        sw(v1, s4, 180);
                    }
                    goto L_00573ff0;
                }
                // 0x00572c68
                charge(ctx, 3);
                s3 = addiu(s3, 3);
                sw(v0, s4, 180);
                goto L_00574014;
            }
            v1 = subu(s1, s6);
            break;
        case 0x572C78u:  // table[6]
            // 0x00572c78
            charge(ctx, 5);
            a0 = s4;
            jal(ctx, 0x572C78u, gen::fn_sub_5702F8_005702f8);
            lw(v0, s4, 56);
            a2 = 0;
            if (i64(v0) <= 0) {
                goto L_00574014;
            }
            // 0x00572c8c
            charge(ctx, 5);
            t0 = 16;
            a3 = 1;
            a1 = addiu(s4, 364);
            a0 = addiu(s4, 352);
            for (;;) {
                // 0x00572ca0
                charge(ctx, 3);
                v0 = slti(s3, 16);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 16);
                if (cc) {
                    // 0x00572d18
                    charge(ctx, 3);
                    s2 = sll(s2, 16);
                    sw(v0, a0, 0);
                    s3 = addiu(s3, 16);
                } else {
                    // 0x00572cac
                    charge(ctx, 3);
                    s3 = addiu(s3, -16);
                    v0 = subu(t0, s3);
                    if (s3 == 0) {
                        // 0x00572cd0
                        charge(ctx, 3);
                        v0 = srl(s2, 16);
                        s2 = s0;
                        sw(v0, a0, 0);
                    } else {
                        // 0x00572cb8
                        charge(ctx, 6);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 16);
                        s2 = sllv(s0, s3);
                        sw(v1, a0, 0);
                    }
                    // 0x00572cdc
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x00572d24
                charge(ctx, 3);
                v0 = slti(s3, 31);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 31);
                if (cc) {
                    // 0x00572da0
                    charge(ctx, 3);
                    s2 = sll(s2, 1);
                    sw(v0, s4, 24);
                    s3 = addiu(s3, 1);
                } else {
                    // 0x00572d30
                    charge(ctx, 3);
                    s3 = addiu(s3, -31);
                    v0 = subu(a3, s3);
                    if (s3 == 0) {
                        // 0x00572d58
                        charge(ctx, 3);
                        v0 = srl(s2, 31);
                        s2 = s0;
                        sw(v0, s4, 24);
                    } else {
                        // 0x00572d3c
                        charge(ctx, 6);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 31);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 24);
                    }
                    // 0x00572d64
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x00572dac
                charge(ctx, 3);
                v0 = slti(s3, 16);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 16);
                if (cc) {
                    // 0x00572e28
                    charge(ctx, 3);
                    s2 = sll(s2, 16);
                    sw(v0, a1, 0);
                    s3 = addiu(s3, 16);
                } else {
                    // 0x00572db8
                    charge(ctx, 3);
                    s3 = addiu(s3, -16);
                    v0 = subu(t0, s3);
                    if (s3 == 0) {
                        // 0x00572de0
                        charge(ctx, 3);
                        v0 = srl(s2, 16);
                        s2 = s0;
                        sw(v0, a1, 0);
                    } else {
                        // 0x00572dc4
                        charge(ctx, 6);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 16);
                        s2 = sllv(s0, s3);
                        sw(v1, a1, 0);
                    }
                    // 0x00572dec
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x00572e34
                charge(ctx, 3);
                v0 = slti(s3, 31);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 31);
                if (cc) {
                    // 0x00572eb0
                    charge(ctx, 3);
                    s2 = sll(s2, 1);
                    sw(v0, s4, 24);
                    s3 = addiu(s3, 1);
                } else {
                    // 0x00572e40
                    charge(ctx, 3);
                    s3 = addiu(s3, -31);
                    v0 = subu(a3, s3);
                    if (s3 == 0) {
                        // 0x00572e68
                        charge(ctx, 3);
                        v0 = srl(s2, 31);
                        s2 = s0;
                        sw(v0, s4, 24);
                    } else {
                        // 0x00572e4c
                        charge(ctx, 6);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 31);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 24);
                    }
                    // 0x00572e74
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x00572ebc
                charge(ctx, 6);
                lw(v0, s4, 56);
                a2 = addiu(a2, 1);
                a1 = addiu(a1, 4);
                v0 = slt(a2, v0);
                a0 = addiu(a0, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00572ed4
            charge(ctx, 2);
            v1 = subu(s1, s6);
            break;
        case 0x572EE0u:  // table[7]
            // 0x00572ee0
            charge(ctx, 3);
            v0 = slti(s3, 28);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 28);
            if (cc) {
                // 0x00572f60
                charge(ctx, 3);
                s2 = sll(s2, 4);
                sw(v0, s4, 260);
                s3 = addiu(s3, 4);
            } else {
                // 0x00572eec
                charge(ctx, 3);
                s3 = addiu(s3, -28);
                v0 = 4;
                if (s3 == 0) {
                    // 0x00572f18
                    charge(ctx, 3);
                    v0 = srl(s2, 28);
                    s2 = s0;
                    sw(v0, s4, 260);
                } else {
                    // 0x00572ef8
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 28);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 260);
                }
                // 0x00572f24
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00572f6c
            charge(ctx, 3);
            v0 = slti(s3, 28);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 28);
            if (cc) {
                // 0x00572fe8
                charge(ctx, 3);
                s2 = sll(s2, 4);
                sw(v0, s4, 264);
                s3 = addiu(s3, 4);
            } else {
                // 0x00572f78
                charge(ctx, 3);
                s3 = addiu(s3, -28);
                v0 = 4;
                if (s3 == 0) {
                    // 0x00572fa0
                    charge(ctx, 3);
                    v0 = srl(s2, 28);
                    s2 = s0;
                    sw(v0, s4, 264);
                } else {
                    // 0x00572f84
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 28);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 264);
                }
                // 0x00572fac
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00572ff4
            charge(ctx, 3);
            v0 = slti(s3, 28);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 28);
            if (cc) {
                // 0x00573070
                charge(ctx, 3);
                s2 = sll(s2, 4);
                sw(v0, s4, 268);
                s3 = addiu(s3, 4);
            } else {
                // 0x00573000
                charge(ctx, 3);
                s3 = addiu(s3, -28);
                v0 = 4;
                if (s3 == 0) {
                    // 0x00573028
                    charge(ctx, 3);
                    v0 = srl(s2, 28);
                    s2 = s0;
                    sw(v0, s4, 268);
                } else {
                    // 0x0057300c
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 28);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 268);
                }
                // 0x00573034
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x0057307c
            charge(ctx, 3);
            v0 = slti(s3, 28);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 28);
            if (cc) {
                // 0x005730f8
                charge(ctx, 3);
                s2 = sll(s2, 4);
                sw(v0, s4, 272);
                s3 = addiu(s3, 4);
            } else {
                // 0x00573088
                charge(ctx, 3);
                s3 = addiu(s3, -28);
                v0 = 4;
                if (s3 == 0) {
                    // 0x005730b0
                    charge(ctx, 3);
                    v0 = srl(s2, 28);
                    s2 = s0;
                    sw(v0, s4, 272);
                } else {
                    // 0x00573094
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 28);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 272);
                }
                // 0x005730bc
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573104
            charge(ctx, 3);
            v0 = slti(s3, 30);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 30);
            if (cc) {
                // 0x00573180
                charge(ctx, 3);
                s2 = sll(s2, 2);
                sw(v0, s4, 276);
                s3 = addiu(s3, 2);
            } else {
                // 0x00573110
                charge(ctx, 3);
                s3 = addiu(s3, -30);
                v0 = 2;
                if (s3 == 0) {
                    // 0x00573138
                    charge(ctx, 3);
                    v0 = srl(s2, 30);
                    s2 = s0;
                    sw(v0, s4, 276);
                } else {
                    // 0x0057311c
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 30);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 276);
                }
                // 0x00573144
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x0057318c
            charge(ctx, 3);
            v0 = slti(s3, 30);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 30);
            if (cc) {
                // 0x00573208
                charge(ctx, 3);
                s2 = sll(s2, 2);
                sw(v0, s4, 280);
                s3 = addiu(s3, 2);
            } else {
                // 0x00573198
                charge(ctx, 3);
                s3 = addiu(s3, -30);
                v0 = 2;
                if (s3 == 0) {
                    // 0x005731c0
                    charge(ctx, 3);
                    v0 = srl(s2, 30);
                    s2 = s0;
                    sw(v0, s4, 280);
                } else {
                    // 0x005731a4
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 30);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 280);
                }
                // 0x005731cc
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573214
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00573290
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 284);
                s3 = addiu(s3, 1);
            } else {
                // 0x00573220
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00573248
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 284);
                } else {
                    // 0x0057322c
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 284);
                }
                // 0x00573254
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x0057329c
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00573318
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 288);
                s3 = addiu(s3, 1);
            } else {
                // 0x005732a8
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x005732d0
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 288);
                } else {
                    // 0x005732b4
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 288);
                }
                // 0x005732dc
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573324
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x005733a0
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 292);
                s3 = addiu(s3, 1);
            } else {
                // 0x00573330
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00573358
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 292);
                } else {
                    // 0x0057333c
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 292);
                }
                // 0x00573364
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x005733ac
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00573428
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 296);
                s3 = addiu(s3, 1);
            } else {
                // 0x005733b8
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x005733e0
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 296);
                } else {
                    // 0x005733c4
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 296);
                }
                // 0x005733ec
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573434
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x005734b0
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 300);
                s3 = addiu(s3, 1);
            } else {
                // 0x00573440
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00573468
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 300);
                } else {
                    // 0x0057344c
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 300);
                }
                // 0x00573474
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x005734bc
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00573538
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 304);
                s3 = addiu(s3, 1);
            } else {
                // 0x005734c8
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x005734f0
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 304);
                } else {
                    // 0x005734d4
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 304);
                }
                // 0x005734fc
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573544
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x005735c0
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 308);
                s3 = addiu(s3, 1);
            } else {
                // 0x00573550
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00573578
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 308);
                } else {
                    // 0x0057355c
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 308);
                }
                // 0x00573584
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x005735cc
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00573648
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 312);
                s3 = addiu(s3, 1);
            } else {
                // 0x005735d8
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00573600
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 312);
                } else {
                    // 0x005735e4
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 312);
                }
                // 0x0057360c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573654
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x005736d0
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 316);
                s3 = addiu(s3, 1);
            } else {
                // 0x00573660
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00573688
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 316);
                } else {
                    // 0x0057366c
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 316);
                }
                // 0x00573694
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x005736dc
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00573758
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 320);
                s3 = addiu(s3, 1);
            } else {
                // 0x005736e8
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00573710
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 320);
                } else {
                    // 0x005736f4
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 320);
                }
                // 0x0057371c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573764
            charge(ctx, 3);
            lw(v0, s4, 320);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = slti(s3, 31);
            if (!cc) {
                // 0x00573770
                charge(ctx, 2);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 31);
                if (cc) {
                    // 0x005737e8
                    charge(ctx, 3);
                    s2 = sll(s2, 1);
                    sw(v0, s4, 324);
                    s3 = addiu(s3, 1);
                } else {
                    // 0x00573778
                    charge(ctx, 3);
                    s3 = addiu(s3, -31);
                    v0 = 1;
                    if (s3 == 0) {
                        // 0x005737a0
                        charge(ctx, 3);
                        v0 = srl(s2, 31);
                        s2 = s0;
                        sw(v0, s4, 324);
                    } else {
                        // 0x00573784
                        charge(ctx, 7);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 31);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 324);
                    }
                    // 0x005737ac
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x005737f4
                charge(ctx, 3);
                v0 = slti(s3, 29);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 29);
                if (cc) {
                    // 0x00573870
                    charge(ctx, 3);
                    s2 = sll(s2, 3);
                    sw(v0, s4, 328);
                    s3 = addiu(s3, 3);
                } else {
                    // 0x00573800
                    charge(ctx, 3);
                    s3 = addiu(s3, -29);
                    v0 = 3;
                    if (s3 == 0) {
                        // 0x00573828
                        charge(ctx, 3);
                        v0 = srl(s2, 29);
                        s2 = s0;
                        sw(v0, s4, 328);
                    } else {
                        // 0x0057380c
                        charge(ctx, 7);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 29);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 328);
                    }
                    // 0x00573834
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x0057387c
                charge(ctx, 3);
                v0 = slti(s3, 31);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 31);
                if (cc) {
                    // 0x005738f8
                    charge(ctx, 3);
                    s2 = sll(s2, 1);
                    sw(v0, s4, 332);
                    s3 = addiu(s3, 1);
                } else {
                    // 0x00573888
                    charge(ctx, 3);
                    s3 = addiu(s3, -31);
                    v0 = 1;
                    if (s3 == 0) {
                        // 0x005738b0
                        charge(ctx, 3);
                        v0 = srl(s2, 31);
                        s2 = s0;
                        sw(v0, s4, 332);
                    } else {
                        // 0x00573894
                        charge(ctx, 7);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 31);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 332);
                    }
                    // 0x005738bc
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x00573904
                charge(ctx, 3);
                v0 = slti(s3, 25);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 25);
                if (cc) {
                    // 0x00573980
                    charge(ctx, 3);
                    s2 = sll(s2, 7);
                    sw(v0, s4, 336);
                    s3 = addiu(s3, 7);
                } else {
                    // 0x00573910
                    charge(ctx, 3);
                    s3 = addiu(s3, -25);
                    v0 = 7;
                    if (s3 == 0) {
                        // 0x00573938
                        charge(ctx, 3);
                        v0 = srl(s2, 25);
                        s2 = s0;
                        sw(v0, s4, 336);
                    } else {
                        // 0x0057391c
                        charge(ctx, 7);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 25);
                        s2 = sllv(s0, s3);
                        sw(v1, s4, 336);
                    }
                    // 0x00573944
                    charge(ctx, 15);
                    lb(s0, s1, 0);
                    s1 = addiu(s1, 1);
                    lbu(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v1, s1, 0);
                    s0 = s0 | v0;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    lbu(v0, s1, 0);
                    s0 = s0 | v1;
                    s1 = addiu(s1, 1);
                    s0 = sll(s0, 8);
                    s0 = s0 | v0;
                }
                // 0x0057398c
                charge(ctx, 3);
                v0 = slti(s3, 24);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = srl(s2, 24);
                if (cc) {
                    // 0x005739d0
                    charge(ctx, 2);
                    s3 = addiu(s3, 8);
                    sw(v0, s4, 340);
                } else {
                    // 0x00573998
                    charge(ctx, 3);
                    s3 = addiu(s3, -24);
                    v0 = 8;
                    if (s3 == 0) {
                        // 0x005739c0
                        charge(ctx, 2);
                        v0 = srl(s2, 24);
                        sw(v0, s4, 340);
                    } else {
                        // 0x005739a4
                        charge(ctx, 6);
                        v0 = subu(v0, s3);
                        v0 = srlv(s0, v0);
                        s2 = s2 | v0;
                        v1 = srl(s2, 24);
                        sw(v1, s4, 340);
                    }
                    // 0x005739c8
                    charge(ctx, 2);
                    s1 = addiu(s1, 4);
                }
            }
            // 0x005739d8
            charge(ctx, 7);
            a0 = s4;
            jal(ctx, 0x5739D8u, gen::fn_sub_570248_00570248);
            a0 = s4;
            jal(ctx, 0x5739E0u, gen::fn_sub_570348_00570348);
            lw(v0, s4, 964);
            if (v0 == 0) {
                sw(zero, s5, 336);
                goto L_00574014;
            }
            // 0x005739f4
            charge(ctx, 2);
            v1 = subu(s1, s6);
            break;
        case 0x573A00u:  // table[8]
            // 0x00573a00
            charge(ctx, 4);
            v0 = 1;
            v1 = slti(s3, 22);
            sw(v0, s4, 788);
            if (v1 != 0) {
                // 0x00573a80
                charge(ctx, 4);
                v0 = srl(s2, 22);
                s2 = sll(s2, 10);
                sw(v0, s4, 388);
                s3 = addiu(s3, 10);
            } else {
                // 0x00573a10
                charge(ctx, 3);
                s3 = addiu(s3, -22);
                v0 = 10;
                if (s3 == 0) {
                    // 0x00573a38
                    charge(ctx, 3);
                    v0 = srl(s2, 22);
                    s2 = s0;
                    sw(v0, s4, 388);
                } else {
                    // 0x00573a1c
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 22);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 388);
                }
                // 0x00573a44
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573a90
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00573b10
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 24);
                s3 = addiu(s3, 1);
            } else {
                // 0x00573a9c
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00573ac8
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 24);
                } else {
                    // 0x00573aa8
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 24);
                }
                // 0x00573ad4
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573b1c
            charge(ctx, 3);
            v0 = slti(s3, 17);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 17);
            if (cc) {
                // 0x00573b98
                charge(ctx, 3);
                s2 = sll(s2, 15);
                sw(v0, s4, 392);
                s3 = addiu(s3, 15);
            } else {
                // 0x00573b28
                charge(ctx, 3);
                s3 = addiu(s3, -17);
                v0 = 15;
                if (s3 == 0) {
                    // 0x00573b50
                    charge(ctx, 3);
                    v0 = srl(s2, 17);
                    s2 = s0;
                    sw(v0, s4, 392);
                } else {
                    // 0x00573b34
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 17);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 392);
                }
                // 0x00573b5c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573ba4
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00573c20
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 24);
                s3 = addiu(s3, 1);
            } else {
                // 0x00573bb0
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00573bd8
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 24);
                } else {
                    // 0x00573bbc
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 24);
                }
                // 0x00573be4
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573c2c
            charge(ctx, 3);
            v0 = slti(s3, 17);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 17);
            if (cc) {
                // 0x00573ca8
                charge(ctx, 3);
                s2 = sll(s2, 15);
                sw(v0, s4, 396);
                s3 = addiu(s3, 15);
            } else {
                // 0x00573c38
                charge(ctx, 3);
                s3 = addiu(s3, -17);
                v0 = 15;
                if (s3 == 0) {
                    // 0x00573c60
                    charge(ctx, 3);
                    v0 = srl(s2, 17);
                    s2 = s0;
                    sw(v0, s4, 396);
                } else {
                    // 0x00573c44
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 17);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 396);
                }
                // 0x00573c6c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573cb4
            charge(ctx, 3);
            v0 = slti(s3, 30);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 30);
            if (cc) {
                // 0x00573d30
                charge(ctx, 3);
                s2 = sll(s2, 2);
                sw(v0, s4, 400);
                s3 = addiu(s3, 2);
            } else {
                // 0x00573cc0
                charge(ctx, 3);
                s3 = addiu(s3, -30);
                v0 = 2;
                if (s3 == 0) {
                    // 0x00573ce8
                    charge(ctx, 3);
                    v0 = srl(s2, 30);
                    s2 = s0;
                    sw(v0, s4, 400);
                } else {
                    // 0x00573ccc
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 30);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 400);
                }
                // 0x00573cf4
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573d3c
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00573db8
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 404);
                s3 = addiu(s3, 1);
            } else {
                // 0x00573d48
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00573d70
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 404);
                } else {
                    // 0x00573d54
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 404);
                }
                // 0x00573d7c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573dc4
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (!cc) {
                // 0x00573dd0
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00573df8
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    sw(v0, s4, 408);
                } else {
                    // 0x00573ddc
                    charge(ctx, 6);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    sw(v1, s4, 408);
                }
                goto L_00573ff0;
            }
            // 0x00573e08
            charge(ctx, 3);
            s3 = addiu(s3, 1);
            sw(v0, s4, 408);
            goto L_00574014;
        case 0x573E18u:  // table[9]
            // 0x00573e18
            charge(ctx, 3);
            v0 = slti(s3, 30);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 30);
            if (cc) {
                // 0x00573e98
                charge(ctx, 3);
                s2 = sll(s2, 2);
                sw(v0, s4, 376);
                s3 = addiu(s3, 2);
            } else {
                // 0x00573e24
                charge(ctx, 3);
                s3 = addiu(s3, -30);
                v0 = 2;
                if (s3 == 0) {
                    // 0x00573e50
                    charge(ctx, 3);
                    v0 = srl(s2, 30);
                    s2 = s0;
                    sw(v0, s4, 376);
                } else {
                    // 0x00573e30
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 30);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 376);
                }
                // 0x00573e5c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573ea4
            charge(ctx, 3);
            v0 = slti(s3, 22);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 22);
            if (cc) {
                // 0x00573f20
                charge(ctx, 3);
                s2 = sll(s2, 10);
                sw(v0, s4, 380);
                s3 = addiu(s3, 10);
            } else {
                // 0x00573eb0
                charge(ctx, 3);
                s3 = addiu(s3, -22);
                v0 = 10;
                if (s3 == 0) {
                    // 0x00573ed8
                    charge(ctx, 3);
                    v0 = srl(s2, 22);
                    s2 = s0;
                    sw(v0, s4, 380);
                } else {
                    // 0x00573ebc
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 22);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 380);
                }
                // 0x00573ee4
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573f2c
            charge(ctx, 3);
            v0 = slti(s3, 31);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 31);
            if (cc) {
                // 0x00573fa8
                charge(ctx, 3);
                s2 = sll(s2, 1);
                sw(v0, s4, 24);
                s3 = addiu(s3, 1);
            } else {
                // 0x00573f38
                charge(ctx, 3);
                s3 = addiu(s3, -31);
                v0 = 1;
                if (s3 == 0) {
                    // 0x00573f60
                    charge(ctx, 3);
                    v0 = srl(s2, 31);
                    s2 = s0;
                    sw(v0, s4, 24);
                } else {
                    // 0x00573f44
                    charge(ctx, 7);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 31);
                    s2 = sllv(s0, s3);
                    sw(v1, s4, 24);
                }
                // 0x00573f6c
                charge(ctx, 15);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                lbu(v0, s1, 0);
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v1, s1, 0);
                s0 = s0 | v0;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                lbu(v0, s1, 0);
                s0 = s0 | v1;
                s1 = addiu(s1, 1);
                s0 = sll(s0, 8);
                s0 = s0 | v0;
            }
            // 0x00573fb4
            charge(ctx, 3);
            v0 = slti(s3, 22);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = srl(s2, 22);
            if (!cc) {
                // 0x00573fc0
                charge(ctx, 3);
                s3 = addiu(s3, -22);
                v0 = 10;
                if (s3 == 0) {
                    // 0x00573fe8
                    charge(ctx, 2);
                    v0 = srl(s2, 22);
                    sw(v0, s4, 384);
                } else {
                    // 0x00573fcc
                    charge(ctx, 6);
                    v0 = subu(v0, s3);
                    v0 = srlv(s0, v0);
                    s2 = s2 | v0;
                    v1 = srl(s2, 22);
                    sw(v1, s4, 384);
                }
                goto L_00573ff0;
            }
            // 0x00573ff8
            charge(ctx, 3);
            s3 = addiu(s3, 10);
            sw(v0, s4, 384);
            goto L_00574014;
        case 0x574008u:  // table[5]
            // 0x00574008
            charge(ctx, 1);
            lw(v0, s4, 1272);
        L_0057400c:
            charge(ctx, 2);
            v0 = addiu(v0, 1);
            sw(v0, s4, 1272);
            goto L_00574014;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
        // 0x00574018 (the shared epilogue, written out on this path)
        charge(ctx, 20);
        ld(s1, sp, 0x8);
        v1 = sll(v1, 3);
        sw(zero, s4, 780);
        v1 = addu(s3, v1);
        ld(s3, sp, 0x18);
        v0 = addiu(v1, -57);
        v1 = addiu(v1, -50);
        a0 = slti(v0, 0);
        sw(zero, s4, 776);
        if (a0 != 0) v0 = v1;
        ld(s0, sp, 0x0);
        v0 = sra(v0, 3);
        ld(s2, sp, 0x10);
        v0 = addu(s6, v0);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(s6, sp, 0x30);
        ld(ra, sp, 0x38);
        sp = addiu(sp, 0x40);
        return;
    }
    goto L_0057400c;
}

// 0x00574068 sub_574068 -- 1384 bytes; leaf frame (no stack)
// MPEG-2 video: the GOP-header parser (start code 0x1B8; header kind 2): the 25-bit time code (drop flag, hours,
// minutes, marker, seconds, pictures), closed_gop and broken_link into the record. Returns the next byte.
void sub_574068(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00574068
    enter(ctx, 12);  // entry check point + this block's cycles
    t3 = addiu(a0, 352);
    v1 = 2;
    lw(v0, t3, 1184);
    t4 = a1;
    lw(a0, t3, 776);
    v0 = addiu(v0, 1);
    sw(v1, t3, 1156);
    sw(v0, t3, 1184);
    sw(zero, t3, 1288);
    sw(zero, t3, 1292);
    sw(zero, t3, 1296);
    if (a0 != 0) {
        // 0x00574098
        charge(ctx, 3);
        v0 = 8;
        if (a0 == v0) {
            goto L_005740a4;
        }
        lw(v0, t3, 1272);
    L_005740b4:
        charge(ctx, 3);
        v0 = addiu(v0, 1);
        sw(v0, t3, 1272);
        v0 = si(-4);
        goto L_005740c0;
    }
L_005740a4:
    charge(ctx, 3);
    lw(v0, t3, 780);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = si(-4);
    if (!cc) {
        // 0x005740b0
        charge(ctx, 1);
        lw(v0, t3, 1272);
        goto L_005740b4;
    }
L_005740c0:
    charge(ctx, 33);
    t0 = t4 & v0;
    v1 = subu(t4, t0);
    lb(t1, t0, 0);
    t0 = addiu(t0, 1);
    t2 = sll(v1, 3);
    lbu(a0, t0, 0);
    t0 = addiu(t0, 1);
    lbu(a1, t0, 0);
    t0 = addiu(t0, 1);
    lbu(a2, t0, 0);
    t0 = addiu(t0, 1);
    lb(a3, t0, 0);
    t0 = addiu(t0, 1);
    lbu(v0, t0, 0);
    t0 = addiu(t0, 1);
    t1 = sll(t1, 8);
    a3 = sll(a3, 8);
    t1 = t1 | a0;
    a3 = a3 | v0;
    lbu(v1, t0, 0);
    t0 = addiu(t0, 1);
    t1 = sll(t1, 8);
    a3 = sll(a3, 8);
    t1 = t1 | a1;
    lbu(v0, t0, 0);
    a3 = a3 | v1;
    t1 = sll(t1, 8);
    a3 = sll(a3, 8);
    t1 = t1 | a2;
    t0 = addiu(t0, 1);
    a3 = a3 | v0;
    t1 = sllv(t1, t2);
    if (t2 == 0) {
        // 0x00574160
        charge(ctx, 2);
        sw(t1, t3, 184);
        t1 = a3;
    } else {
        // 0x00574144
        charge(ctx, 6);
        v0 = subu(0, t2);
        v0 = srlv(a3, v0);
        v0 = t1 | v0;
        t1 = sllv(a3, t2);
        sw(v0, t3, 184);
    }
    // 0x00574168
    charge(ctx, 16);
    lb(a3, t0, 0);
    t0 = addiu(t0, 1);
    lbu(v0, t0, 0);
    t0 = addiu(t0, 1);
    a3 = sll(a3, 8);
    lbu(v1, t0, 0);
    a3 = a3 | v0;
    v0 = slti(t2, 31);
    t0 = addiu(t0, 1);
    a3 = sll(a3, 8);
    lbu(a0, t0, 0);
    t0 = addiu(t0, 1);
    a3 = a3 | v1;
    a3 = sll(a3, 8);
    a3 = a3 | a0;
    if (v0 != 0) {
        // 0x00574218
        charge(ctx, 4);
        v0 = srl(t1, 31);
        t1 = sll(t1, 1);
        sw(v0, t3, 188);
        t2 = addiu(t2, 1);
    } else {
        // 0x005741a8
        charge(ctx, 3);
        t2 = addiu(t2, -31);
        v0 = 1;
        if (t2 == 0) {
            // 0x005741d0
            charge(ctx, 3);
            v0 = srl(t1, 31);
            t1 = a3;
            sw(v0, t3, 188);
        } else {
            // 0x005741b4
            charge(ctx, 7);
            v0 = subu(v0, t2);
            v0 = srlv(a3, v0);
            t1 = t1 | v0;
            v1 = srl(t1, 31);
            t1 = sllv(a3, t2);
            sw(v1, t3, 188);
        }
        // 0x005741dc
        charge(ctx, 15);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x00574228
    charge(ctx, 3);
    v0 = slti(t2, 27);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t1, 27);
    if (cc) {
        // 0x005742a8
        charge(ctx, 3);
        t1 = sll(t1, 5);
        sw(v0, t3, 192);
        t2 = addiu(t2, 5);
    } else {
        // 0x00574234
        charge(ctx, 3);
        t2 = addiu(t2, -27);
        v0 = 5;
        if (t2 == 0) {
            // 0x00574260
            charge(ctx, 3);
            v0 = srl(t1, 27);
            t1 = a3;
            sw(v0, t3, 192);
        } else {
            // 0x00574240
            charge(ctx, 7);
            v0 = subu(v0, t2);
            v0 = srlv(a3, v0);
            t1 = t1 | v0;
            v1 = srl(t1, 27);
            t1 = sllv(a3, t2);
            sw(v1, t3, 192);
        }
        // 0x0057426c
        charge(ctx, 15);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x005742b4
    charge(ctx, 3);
    v0 = slti(t2, 26);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t1, 26);
    if (cc) {
        // 0x00574330
        charge(ctx, 3);
        t1 = sll(t1, 6);
        sw(v0, t3, 196);
        t2 = addiu(t2, 6);
    } else {
        // 0x005742c0
        charge(ctx, 3);
        t2 = addiu(t2, -26);
        v0 = 6;
        if (t2 == 0) {
            // 0x005742e8
            charge(ctx, 3);
            v0 = srl(t1, 26);
            t1 = a3;
            sw(v0, t3, 196);
        } else {
            // 0x005742cc
            charge(ctx, 7);
            v0 = subu(v0, t2);
            v0 = srlv(a3, v0);
            t1 = t1 | v0;
            v1 = srl(t1, 26);
            t1 = sllv(a3, t2);
            sw(v1, t3, 196);
        }
        // 0x005742f4
        charge(ctx, 15);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x0057433c
    charge(ctx, 3);
    v0 = slti(t2, 31);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t1, 31);
    if (cc) {
        // 0x005743b8
        charge(ctx, 3);
        t1 = sll(t1, 1);
        sw(v0, t3, 24);
        t2 = addiu(t2, 1);
    } else {
        // 0x00574348
        charge(ctx, 3);
        t2 = addiu(t2, -31);
        v0 = 1;
        if (t2 == 0) {
            // 0x00574370
            charge(ctx, 3);
            v0 = srl(t1, 31);
            t1 = a3;
            sw(v0, t3, 24);
        } else {
            // 0x00574354
            charge(ctx, 7);
            v0 = subu(v0, t2);
            v0 = srlv(a3, v0);
            t1 = t1 | v0;
            v1 = srl(t1, 31);
            t1 = sllv(a3, t2);
            sw(v1, t3, 24);
        }
        // 0x0057437c
        charge(ctx, 15);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x005743c4
    charge(ctx, 3);
    v0 = slti(t2, 26);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t1, 26);
    if (cc) {
        // 0x00574440
        charge(ctx, 3);
        t1 = sll(t1, 6);
        sw(v0, t3, 200);
        t2 = addiu(t2, 6);
    } else {
        // 0x005743d0
        charge(ctx, 3);
        t2 = addiu(t2, -26);
        v0 = 6;
        if (t2 == 0) {
            // 0x005743f8
            charge(ctx, 3);
            v0 = srl(t1, 26);
            t1 = a3;
            sw(v0, t3, 200);
        } else {
            // 0x005743dc
            charge(ctx, 7);
            v0 = subu(v0, t2);
            v0 = srlv(a3, v0);
            t1 = t1 | v0;
            v1 = srl(t1, 26);
            t1 = sllv(a3, t2);
            sw(v1, t3, 200);
        }
        // 0x00574404
        charge(ctx, 15);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x0057444c
    charge(ctx, 3);
    v0 = slti(t2, 26);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t1, 26);
    if (cc) {
        // 0x005744c8
        charge(ctx, 3);
        t1 = sll(t1, 6);
        sw(v0, t3, 204);
        t2 = addiu(t2, 6);
    } else {
        // 0x00574458
        charge(ctx, 3);
        t2 = addiu(t2, -26);
        v0 = 6;
        if (t2 == 0) {
            // 0x00574480
            charge(ctx, 3);
            v0 = srl(t1, 26);
            t1 = a3;
            sw(v0, t3, 204);
        } else {
            // 0x00574464
            charge(ctx, 7);
            v0 = subu(v0, t2);
            v0 = srlv(a3, v0);
            t1 = t1 | v0;
            v1 = srl(t1, 26);
            t1 = sllv(a3, t2);
            sw(v1, t3, 204);
        }
        // 0x0057448c
        charge(ctx, 15);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x005744d4
    charge(ctx, 3);
    v0 = slti(t2, 31);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t1, 31);
    if (cc) {
        // 0x00574550
        charge(ctx, 3);
        t1 = sll(t1, 1);
        sw(v0, t3, 208);
        t2 = addiu(t2, 1);
    } else {
        // 0x005744e0
        charge(ctx, 3);
        t2 = addiu(t2, -31);
        v0 = 1;
        if (t2 == 0) {
            // 0x00574508
            charge(ctx, 3);
            v0 = srl(t1, 31);
            t1 = a3;
            sw(v0, t3, 208);
        } else {
            // 0x005744ec
            charge(ctx, 7);
            v0 = subu(v0, t2);
            v0 = srlv(a3, v0);
            t1 = t1 | v0;
            v1 = srl(t1, 31);
            t1 = sllv(a3, t2);
            sw(v1, t3, 208);
        }
        // 0x00574514
        charge(ctx, 15);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x0057455c
    charge(ctx, 3);
    v0 = slti(t2, 31);
    if (v0 != 0) {
        v0 = srl(t1, 31);
        // 0x005745a0
        charge(ctx, 2);
        t2 = addiu(t2, 1);
        sw(v0, t3, 212);
    } else {
        // 0x00574568
        charge(ctx, 3);
        t2 = addiu(t2, -31);
        if (t2 == 0) {
            v0 = srl(t1, 31);
            // 0x00574590
            charge(ctx, 1);
            sw(v0, t3, 212);
        } else {
            // 0x00574574
            charge(ctx, 7);
            v0 = 1;
            v0 = subu(v0, t2);
            v0 = srlv(a3, v0);
            t1 = t1 | v0;
            v1 = srl(t1, 31);
            sw(v1, t3, 212);
        }
        // 0x00574594
        charge(ctx, 2);
        t0 = addiu(t0, 4);
    }
    // 0x005745a8 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v1 = subu(t0, t4);
    v1 = sll(v1, 3);
    v1 = addu(t2, v1);
    v0 = addiu(v1, -57);
    v1 = addiu(v1, -50);
    a0 = slti(v0, 0);
    if (a0 != 0) v0 = v1;
    v0 = sra(v0, 3);
    v0 = addu(t4, v0);
}

// 0x005745D0 sub_5745D0 -- 1752 bytes; leaf frame (no stack)
// MPEG-2 video: the picture-header parser (start code 0x100; header kind 3): temporal reference, picture coding type
// (3 bits), VBV delay (16 bits) and the motion codes that follow by type; sets +1132 = 8 and +1128 = 16. Returns the
// next byte.
void sub_5745D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005745d0
    enter(ctx, 9);  // entry check point + this block's cycles
    t3 = addiu(a0, 352);
    v1 = 3;
    lw(v0, t3, 1188);
    t4 = a1;
    lw(a0, t3, 776);
    v0 = addiu(v0, 1);
    sw(v1, t3, 1156);
    sw(v0, t3, 1188);
    if (a0 != 0) {
        // 0x005745f4
        charge(ctx, 3);
        v0 = 4;
        if (a0 == v0) {
            goto L_00574600;
        }
        lw(v0, t3, 1272);
    L_00574610:
        charge(ctx, 3);
        v0 = addiu(v0, 1);
        sw(v0, t3, 1272);
        v0 = si(-4);
        goto L_0057461c;
    }
L_00574600:
    charge(ctx, 3);
    lw(v0, t3, 780);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = si(-4);
    if (!cc) {
        // 0x0057460c
        charge(ctx, 1);
        lw(v0, t3, 1272);
        goto L_00574610;
    }
L_0057461c:
    charge(ctx, 33);
    t0 = t4 & v0;
    v1 = subu(t4, t0);
    lb(t1, t0, 0);
    t0 = addiu(t0, 1);
    t2 = sll(v1, 3);
    lbu(a0, t0, 0);
    t0 = addiu(t0, 1);
    lbu(a1, t0, 0);
    t0 = addiu(t0, 1);
    lbu(a2, t0, 0);
    t0 = addiu(t0, 1);
    lb(a3, t0, 0);
    t0 = addiu(t0, 1);
    lbu(v0, t0, 0);
    t0 = addiu(t0, 1);
    t1 = sll(t1, 8);
    a3 = sll(a3, 8);
    t1 = t1 | a0;
    a3 = a3 | v0;
    lbu(v1, t0, 0);
    t0 = addiu(t0, 1);
    t1 = sll(t1, 8);
    a3 = sll(a3, 8);
    t1 = t1 | a1;
    lbu(v0, t0, 0);
    a3 = a3 | v1;
    t1 = sll(t1, 8);
    a3 = sll(a3, 8);
    t1 = t1 | a2;
    t0 = addiu(t0, 1);
    a3 = a3 | v0;
    t1 = sllv(t1, t2);
    if (t2 == 0) {
        // 0x005746b8
        charge(ctx, 2);
        sw(t1, t3, 216);
        t1 = a3;
    } else {
        // 0x005746a0
        charge(ctx, 6);
        v0 = subu(0, t2);
        v0 = srlv(a3, v0);
        v0 = t1 | v0;
        t1 = sllv(a3, t2);
        sw(v0, t3, 216);
    }
    // 0x005746c0
    charge(ctx, 16);
    lb(a3, t0, 0);
    t0 = addiu(t0, 1);
    lbu(v0, t0, 0);
    t0 = addiu(t0, 1);
    a3 = sll(a3, 8);
    lbu(v1, t0, 0);
    a3 = a3 | v0;
    v0 = slti(t2, 22);
    t0 = addiu(t0, 1);
    a3 = sll(a3, 8);
    lbu(a0, t0, 0);
    t0 = addiu(t0, 1);
    a3 = a3 | v1;
    a3 = sll(a3, 8);
    a3 = a3 | a0;
    if (v0 != 0) {
        // 0x00574770
        charge(ctx, 4);
        v0 = srl(t1, 22);
        t1 = sll(t1, 10);
        sw(v0, t3, 220);
        t2 = addiu(t2, 10);
    } else {
        // 0x00574700
        charge(ctx, 3);
        t2 = addiu(t2, -22);
        v0 = 10;
        if (t2 == 0) {
            // 0x00574728
            charge(ctx, 3);
            v0 = srl(t1, 22);
            t1 = a3;
            sw(v0, t3, 220);
        } else {
            // 0x0057470c
            charge(ctx, 7);
            v0 = subu(v0, t2);
            v0 = srlv(a3, v0);
            t1 = t1 | v0;
            v1 = srl(t1, 22);
            t1 = sllv(a3, t2);
            sw(v1, t3, 220);
        }
        // 0x00574734
        charge(ctx, 15);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x00574780
    charge(ctx, 3);
    v0 = slti(t2, 29);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t1, 29);
    if (cc) {
        // 0x00574800
        charge(ctx, 3);
        t1 = sll(t1, 3);
        sw(v0, t3, 224);
        t2 = addiu(t2, 3);
    } else {
        // 0x0057478c
        charge(ctx, 3);
        t2 = addiu(t2, -29);
        v0 = 3;
        if (t2 == 0) {
            // 0x005747b8
            charge(ctx, 3);
            v0 = srl(t1, 29);
            t1 = a3;
            sw(v0, t3, 224);
        } else {
            // 0x00574798
            charge(ctx, 7);
            v0 = subu(v0, t2);
            v0 = srlv(a3, v0);
            t1 = t1 | v0;
            v1 = srl(t1, 29);
            t1 = sllv(a3, t2);
            sw(v1, t3, 224);
        }
        // 0x005747c4
        charge(ctx, 15);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x0057480c
    charge(ctx, 3);
    v0 = slti(t2, 16);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t1, 16);
    if (cc) {
        // 0x00574888
        charge(ctx, 3);
        t1 = sll(t1, 16);
        sw(v0, t3, 228);
        t2 = addiu(t2, 16);
    } else {
        // 0x00574818
        charge(ctx, 3);
        t2 = addiu(t2, -16);
        v0 = 16;
        if (t2 == 0) {
            // 0x00574840
            charge(ctx, 3);
            v0 = srl(t1, 16);
            t1 = a3;
            sw(v0, t3, 228);
        } else {
            // 0x00574824
            charge(ctx, 7);
            v0 = subu(v0, t2);
            v0 = srlv(a3, v0);
            t1 = t1 | v0;
            v1 = srl(t1, 16);
            t1 = sllv(a3, t2);
            sw(v1, t3, 228);
        }
        // 0x0057484c
        charge(ctx, 15);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x00574894
    charge(ctx, 5);
    lw(a2, t3, 224);
    v1 = addiu(a2, -1);
    v0 = sltiu(v1, 3);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = sltiu(v1, 2);
    if (!cc) {
        // 0x005748a8
        charge(ctx, 4);
        lw(v0, t3, 1272);
        v0 = addiu(v0, 1);
        sw(v0, t3, 1272);
        v0 = sltiu(v1, 2);
    }
    // 0x005748b8
    charge(ctx, 2);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    lw(v0, t3, 1288);
    if (cc) {
        // 0x005748d8
        charge(ctx, 7);
        lw(v1, t3, 1292);
        v0 = addiu(v0, -1);
        v1 = addiu(v1, 1);
        v0 = sll(v0, 16);
        v0 = v0 | v1;
        sw(v1, t3, 1292);
        sw(v0, t3, 1296);
    } else {
        // 0x005748c0
        charge(ctx, 6);
        sw(zero, t3, 1292);
        v0 = addiu(v0, 1);
        v1 = sll(v0, 16);
        sw(v0, t3, 1288);
        sw(v1, t3, 1296);
    }
    // 0x005748f4
    charge(ctx, 4);
    v0 = addiu(a2, -2);
    v0 = sltiu(v0, 2);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 3;
    if (!cc) {
        // 0x00574904
        charge(ctx, 3);
        v0 = slti(t2, 31);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = srl(t1, 31);
        if (cc) {
            // 0x00574980
            charge(ctx, 3);
            t1 = sll(t1, 1);
            sw(v0, t3, 232);
            t2 = addiu(t2, 1);
        } else {
            // 0x00574910
            charge(ctx, 3);
            t2 = addiu(t2, -31);
            v0 = 1;
            if (t2 == 0) {
                // 0x00574938
                charge(ctx, 3);
                v0 = srl(t1, 31);
                t1 = a3;
                sw(v0, t3, 232);
            } else {
                // 0x0057491c
                charge(ctx, 7);
                v0 = subu(v0, t2);
                v0 = srlv(a3, v0);
                t1 = t1 | v0;
                v1 = srl(t1, 31);
                t1 = sllv(a3, t2);
                sw(v1, t3, 232);
            }
            // 0x00574944
            charge(ctx, 15);
            lb(a3, t0, 0);
            t0 = addiu(t0, 1);
            lbu(v0, t0, 0);
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            lbu(v1, t0, 0);
            a3 = a3 | v0;
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            lbu(v0, t0, 0);
            a3 = a3 | v1;
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            a3 = a3 | v0;
        }
        // 0x0057498c
        charge(ctx, 3);
        v0 = slti(t2, 29);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = srl(t1, 29);
        if (cc) {
            // 0x00574a08
            charge(ctx, 3);
            t1 = sll(t1, 3);
            sw(v0, t3, 236);
            t2 = addiu(t2, 3);
        } else {
            // 0x00574998
            charge(ctx, 3);
            t2 = addiu(t2, -29);
            v0 = 3;
            if (t2 == 0) {
                // 0x005749c0
                charge(ctx, 3);
                v0 = srl(t1, 29);
                t1 = a3;
                sw(v0, t3, 236);
            } else {
                // 0x005749a4
                charge(ctx, 7);
                v0 = subu(v0, t2);
                v0 = srlv(a3, v0);
                t1 = t1 | v0;
                v1 = srl(t1, 29);
                t1 = sllv(a3, t2);
                sw(v1, t3, 236);
            }
            // 0x005749cc
            charge(ctx, 15);
            lb(a3, t0, 0);
            t0 = addiu(t0, 1);
            lbu(v0, t0, 0);
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            lbu(v1, t0, 0);
            a3 = a3 | v0;
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            lbu(v0, t0, 0);
            a3 = a3 | v1;
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            a3 = a3 | v0;
        }
        // 0x00574a14
        charge(ctx, 1);
        v0 = 3;
    }
    // 0x00574a18
    charge(ctx, 2);
    a0 = 1;
    if (a2 == v0) {
        // 0x00574a20
        charge(ctx, 3);
        v0 = slti(t2, 31);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = srl(t1, 31);
        if (cc) {
            // 0x00574aa0
            charge(ctx, 3);
            t1 = sll(t1, 1);
            sw(v0, t3, 240);
            t2 = addiu(t2, 1);
        } else {
            // 0x00574a2c
            charge(ctx, 3);
            t2 = addiu(t2, -31);
            v0 = 1;
            if (t2 == 0) {
                // 0x00574a58
                charge(ctx, 3);
                v0 = srl(t1, 31);
                t1 = a3;
                sw(v0, t3, 240);
            } else {
                // 0x00574a38
                charge(ctx, 7);
                v0 = subu(v0, t2);
                v0 = srlv(a3, v0);
                t1 = t1 | v0;
                v1 = srl(t1, 31);
                t1 = sllv(a3, t2);
                sw(v1, t3, 240);
            }
            // 0x00574a64
            charge(ctx, 15);
            lb(a3, t0, 0);
            t0 = addiu(t0, 1);
            lbu(v0, t0, 0);
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            lbu(v1, t0, 0);
            a3 = a3 | v0;
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            lbu(v0, t0, 0);
            a3 = a3 | v1;
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            a3 = a3 | v0;
        }
        // 0x00574aac
        charge(ctx, 3);
        v0 = slti(t2, 29);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = srl(t1, 29);
        if (cc) {
            // 0x00574b28
            charge(ctx, 3);
            t1 = sll(t1, 3);
            sw(v0, t3, 244);
            t2 = addiu(t2, 3);
        } else {
            // 0x00574ab8
            charge(ctx, 3);
            t2 = addiu(t2, -29);
            v0 = 3;
            if (t2 == 0) {
                // 0x00574ae0
                charge(ctx, 3);
                v0 = srl(t1, 29);
                t1 = a3;
                sw(v0, t3, 244);
            } else {
                // 0x00574ac4
                charge(ctx, 7);
                v0 = subu(v0, t2);
                v0 = srlv(a3, v0);
                t1 = t1 | v0;
                v1 = srl(t1, 29);
                t1 = sllv(a3, t2);
                sw(v1, t3, 244);
            }
            // 0x00574aec
            charge(ctx, 15);
            lb(a3, t0, 0);
            t0 = addiu(t0, 1);
            lbu(v0, t0, 0);
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            lbu(v1, t0, 0);
            a3 = a3 | v0;
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            lbu(v0, t0, 0);
            a3 = a3 | v1;
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            a3 = a3 | v0;
        }
        // 0x00574b34
        charge(ctx, 1);
        a0 = 1;
    }
    // 0x00574b38
    charge(ctx, 2);
    a1 = 8;
    for (;;) {
        // 0x00574bc4
        charge(ctx, 3);
        v0 = slti(t2, 31);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = srl(t1, 31);
        if (cc) {
            // 0x00574c40
            charge(ctx, 3);
            t1 = sll(t1, 1);
            sw(v0, t3, 248);
            t2 = addiu(t2, 1);
        } else {
            // 0x00574bd0
            charge(ctx, 3);
            t2 = addiu(t2, -31);
            v0 = subu(a0, t2);
            if (t2 == 0) {
                // 0x00574bf8
                charge(ctx, 3);
                v0 = srl(t1, 31);
                t1 = a3;
                sw(v0, t3, 248);
            } else {
                // 0x00574bdc
                charge(ctx, 6);
                v0 = srlv(a3, v0);
                t1 = t1 | v0;
                v1 = srl(t1, 31);
                t1 = sllv(a3, t2);
                sw(v1, t3, 248);
            }
            // 0x00574c04
            charge(ctx, 15);
            lb(a3, t0, 0);
            t0 = addiu(t0, 1);
            lbu(v0, t0, 0);
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            lbu(v1, t0, 0);
            a3 = a3 | v0;
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            lbu(v0, t0, 0);
            a3 = a3 | v1;
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            a3 = a3 | v0;
        }
        // 0x00574c4c
        charge(ctx, 3);
        lw(v0, t3, 248);
        if (v0 == 0) {
            break;
        }
        v0 = slti(t2, 24);
        backedge(ctx);
        // 0x00574b40
        charge(ctx, 2);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = srl(t1, 24);
        if (cc) {
            // 0x00574bb8
            charge(ctx, 3);
            t1 = sll(t1, 8);
            sw(v0, t3, 252);
            t2 = addiu(t2, 8);
        } else {
            // 0x00574b48
            charge(ctx, 3);
            t2 = addiu(t2, -24);
            v0 = subu(a1, t2);
            if (t2 == 0) {
                // 0x00574b70
                charge(ctx, 3);
                v0 = srl(t1, 24);
                t1 = a3;
                sw(v0, t3, 252);
            } else {
                // 0x00574b54
                charge(ctx, 6);
                v0 = srlv(a3, v0);
                t1 = t1 | v0;
                v1 = srl(t1, 24);
                t1 = sllv(a3, t2);
                sw(v1, t3, 252);
            }
            // 0x00574b7c
            charge(ctx, 15);
            lb(a3, t0, 0);
            t0 = addiu(t0, 1);
            lbu(v0, t0, 0);
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            lbu(v1, t0, 0);
            a3 = a3 | v0;
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            lbu(v0, t0, 0);
            a3 = a3 | v1;
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            a3 = a3 | v0;
        }
    }
    // 0x00574c58
    charge(ctx, 20);
    v1 = subu(t0, t4);
    a2 = sll(a2, 2);
    v1 = sll(v1, 3);
    a2 = addu(a2, t3);
    v1 = addu(t2, v1);
    a2 = addiu(a2, 1192);
    v0 = addiu(v1, -57);
    v1 = addiu(v1, -50);
    lw(a1, a2, 0);
    a0 = slti(v0, 0);
    if (a0 != 0) v0 = v1;
    v1 = 8;
    a3 = 16;
    a1 = addiu(a1, 1);
    v0 = sra(v0, 3);
    sw(a1, a2, 0);
    v0 = addu(t4, v0);
    sw(v1, t3, 780);
    sw(a3, t3, 776);
}

// 0x00578378 sub_578378 -- 1188 bytes; leaf frame (no stack)
// MPEG-2 video: probes the first slice at $a0 (start code 0x101; else returns 0) and reads its header fields with the
// bit reader and the VLC table 0x7B29A0.
void sub_578378(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00578378
    enter(ctx, 36);  // entry check point + this block's cycles
    t4 = a0;
    v0 = si(-4);
    t0 = t4 & v0;
    t5 = a1;
    v0 = subu(t4, t0);
    lb(t2, t0, 0);
    t0 = addiu(t0, 1);
    t1 = sll(v0, 3);
    lbu(v1, t0, 0);
    t0 = addiu(t0, 1);
    lbu(a0, t0, 0);
    t0 = addiu(t0, 1);
    lbu(a1, t0, 0);
    t0 = addiu(t0, 1);
    lb(a3, t0, 0);
    t0 = addiu(t0, 1);
    lbu(v0, t0, 0);
    t0 = addiu(t0, 1);
    t2 = sll(t2, 8);
    a3 = sll(a3, 8);
    t2 = t2 | v1;
    lbu(v1, t0, 0);
    a3 = a3 | v0;
    t2 = sll(t2, 8);
    t0 = addiu(t0, 1);
    a3 = sll(a3, 8);
    t2 = t2 | a0;
    lbu(v0, t0, 0);
    a3 = a3 | v1;
    t2 = sll(t2, 8);
    a3 = sll(a3, 8);
    t2 = t2 | a1;
    t0 = addiu(t0, 1);
    a3 = a3 | v0;
    t2 = sllv(t2, t1);
    if (t1 == 0) {
        // 0x00578420
        charge(ctx, 2);
        a1 = t2;
        t2 = a3;
    } else {
        // 0x00578408
        charge(ctx, 5);
        v0 = subu(0, t1);
        v0 = srlv(a3, v0);
        a1 = t2 | v0;
        t2 = sllv(a3, t1);
    }
    // 0x00578428
    charge(ctx, 17);
    lb(a3, t0, 0);
    t0 = addiu(t0, 1);
    lbu(v0, t0, 0);
    t0 = addiu(t0, 1);
    a3 = sll(a3, 8);
    lbu(v1, t0, 0);
    a3 = a3 | v0;
    t0 = addiu(t0, 1);
    a3 = sll(a3, 8);
    lbu(v0, t0, 0);
    a3 = a3 | v1;
    a0 = 257;
    a3 = sll(a3, 8);
    t0 = addiu(t0, 1);
    a3 = a3 | v0;
    v0 = 0;
    if (a1 != a0) {
        // 0x00578814 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x0057846c
    charge(ctx, 3);
    v0 = slti(t1, 27);
    if (v0 != 0) {
        t1 = addiu(t1, 5);
        // 0x005784c8
        charge(ctx, 1);
        t2 = sll(t2, 5);
    } else {
        // 0x00578478
        charge(ctx, 20);
        t1 = addiu(t1, -27);
        t2 = a3;
        v1 = sllv(a3, t1);
        lb(a3, t0, 0);
        v0 = t1 ^ 0x0;
        t0 = addiu(t0, 1);
        if (v0 != 0) t2 = v1;
        lbu(v0, t0, 0);
        a3 = sll(a3, 8);
        t0 = addiu(t0, 1);
        lbu(v1, t0, 0);
        t0 = addiu(t0, 1);
        a3 = a3 | v0;
        lbu(v0, t0, 0);
        a3 = sll(a3, 8);
        t0 = addiu(t0, 1);
        a3 = a3 | v1;
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x005784cc
    charge(ctx, 3);
    v0 = 31;
    a1 = srl(t2, 31);
    if (t1 != v0) {
        // 0x00578520
        charge(ctx, 2);
        t1 = addiu(t1, 1);
        t2 = sll(t2, 1);
    } else {
        // 0x005784d8
        charge(ctx, 17);
        t2 = a3;
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        t1 = 0;
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x00578528
    charge(ctx, 2);
    v0 = 0;
    if (a1 != 0) {
        // 0x00578814 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x00578530
    charge(ctx, 3);
    v0 = 31;
    a1 = srl(t2, 31);
    if (t1 != v0) {
        // 0x00578580
        charge(ctx, 2);
        t1 = addiu(t1, 1);
        t2 = sll(t2, 1);
    } else {
        // 0x0057853c
        charge(ctx, 17);
        t2 = a3;
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        t1 = 0;
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x00578588
    charge(ctx, 2);
    v0 = 0;
    if (a1 == 0) {
        // 0x00578814 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x00578590
    charge(ctx, 3);
    v0 = slti(t1, 27);
    a1 = srl(t2, 26);
    if (v0 == 0) {
        // 0x0057859c
        charge(ctx, 4);
        v0 = 58;
        v0 = subu(v0, t1);
        v0 = srlv(a3, v0);
        a1 = a1 | v0;
    }
    // 0x005785ac
    charge(ctx, 3);
    v0 = 11;
    cc = a1 == v0;  // the condition, before the delay slot changes it
    v0 = sltiu(a1, 11);
    if (!cc) {
        // 0x005785b8
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x005787f0 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = 0;
            return;
        }
        // 0x005785c0
        charge(ctx, 3);
        v0 = sltiu(a1, 24);
        if (v0 == 0) {
            // 0x005787f0 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = 0;
            return;
        }
        // 0x005785cc
        charge(ctx, 3);
        v0 = sltiu(a1, 22);
        t1 = addiu(t1, 5);
        if (v0 != 0) {
            // 0x005787f0 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = 0;
            return;
        }
        // 0x005785d8
        charge(ctx, 3);
        v0 = slti(t1, 32);
        if (v0 == 0) {
            t1 = addiu(t1, -32);
            goto L_00578604;
        }
        // 0x005785e4
        charge(ctx, 2);
        t2 = sll(t2, 5);
        goto L_00578640;
    }
    // 0x005785f0
    charge(ctx, 4);
    t1 = addiu(t1, 6);
    v0 = slti(t1, 32);
    if (v0 != 0) {
        t2 = sll(t2, 6);
    } else {
        // 0x00578600
        charge(ctx, 1);
        t1 = addiu(t1, -32);
    L_00578604:
        charge(ctx, 15);
        t2 = sllv(a3, t1);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
L_00578640:
    charge(ctx, 4);
    a2 = addiu(a2, -1);
    t3 = 53;
    a0 = 8;
    v0 = slti(t1, 22);
    for (;;) {
        // 0x00578650
        charge(ctx, 2);
        a1 = srl(t2, 21);
        if (v0 == 0) {
            // 0x00578658
            charge(ctx, 3);
            v0 = subu(t3, t1);
            v0 = srlv(a3, v0);
            a1 = a1 | v0;
        }
        // 0x00578664
        charge(ctx, 2);
        v1 = addiu(a2, -1);
        if (a1 != a0) {
            goto L_005786d0;
        }
        // 0x0057866c
        charge(ctx, 4);
        t1 = addiu(t1, 11);
        v0 = slti(t1, 32);
        if (v0 != 0) {
            t2 = sll(t2, 11);
        } else {
            // 0x0057867c
            charge(ctx, 16);
            t1 = addiu(t1, -32);
            t2 = sllv(a3, t1);
            lb(a3, t0, 0);
            t0 = addiu(t0, 1);
            lbu(v0, t0, 0);
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            lbu(v1, t0, 0);
            a3 = a3 | v0;
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            lbu(v0, t0, 0);
            a3 = a3 | v1;
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            a3 = a3 | v0;
        }
        // 0x005786bc
        charge(ctx, 4);
        a2 = addiu(a2, -33);
        v0 = slti(a2, 34);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = slti(t1, 22);
        if (!cc) {
            break;
        }
        backedge(ctx);
    }
    // 0x005786cc
    charge(ctx, 1);
    v1 = addiu(a2, -1);
L_005786d0:
    charge(ctx, 3);
    v1 = sltiu(v1, 33);
    v0 = 0;
    if (v1 == 0) {
        // 0x00578814 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x005786dc
    charge(ctx, 10);
    v0 = sll(a2, 1);
    v1 = 32;
    a2 = 0x7B0000;
    a2 = addu(a2, v0);
    lh(a2, a2, 10656);
    a0 = a2 & 0xFF;
    v1 = subu(v1, a0);
    v0 = slt(t1, v1);
    a1 = srlv(t2, v1);
    if (v0 != 0) {
        // 0x00578768
        charge(ctx, 2);
        t2 = sllv(t2, a0);
        t1 = addu(t1, a0);
    } else {
        // 0x00578704
        charge(ctx, 4);
        v0 = addu(t1, a0);
        t1 = addiu(v0, -32);
        if (t1 == 0) {
            t2 = a3;
        } else {
            // 0x00578714
            charge(ctx, 5);
            v0 = subu(a0, t1);
            v0 = srlv(a3, v0);
            t2 = t2 | v0;
            a1 = srlv(t2, v1);
            t2 = sllv(a3, t1);
        }
        // 0x00578728
        charge(ctx, 15);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x00578770
    charge(ctx, 3);
    v1 = sra(a2, 8);
    v0 = 0;
    if (a1 != v1) {
        // 0x00578814 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x0057877c
    charge(ctx, 3);
    v0 = slti(t1, 27);
    a1 = srl(t2, 26);
    if (v0 == 0) {
        // 0x00578788
        charge(ctx, 4);
        v0 = 58;
        v0 = subu(v0, t1);
        v0 = srlv(a3, v0);
        a1 = a1 | v0;
    }
    // 0x00578798
    charge(ctx, 3);
    v0 = 11;
    cc = a1 == v0;  // the condition, before the delay slot changes it
    v0 = sltiu(a1, 11);
    if (cc) {
        // 0x005787d0
        charge(ctx, 2);
        t1 = addiu(t1, 6);
        v0 = slti(t1, 32);
    L_005787d8:
        charge(ctx, 2);
        if (v0 != 0) {
            v0 = addiu(t1, 7);
        } else {
            // 0x005787e0
            charge(ctx, 3);
            t1 = addiu(t1, -32);
            t0 = addiu(t0, 4);
            // 0x005787f8
            charge(ctx, 1);
            v0 = addiu(t1, 7);
        }
        // 0x005787fc
        charge(ctx, 6);
        v0 = sra(v0, 3);
        v0 = addu(t0, v0);
        v0 = addiu(v0, -8);
        v0 = subu(v0, t4);
        v0 = slt(t5, v0);
        v0 = sltiu(v0, 1);
        // 0x00578814 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x005787a4
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x005787f0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x005787ac
    charge(ctx, 3);
    v0 = sltiu(a1, 24);
    if (v0 == 0) {
        // 0x005787f0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x005787b8
    charge(ctx, 3);
    v0 = sltiu(a1, 22);
    t1 = addiu(t1, 5);
    if (v0 != 0) {
        // 0x005787f0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x005787c4
    charge(ctx, 2);
    v0 = slti(t1, 32);
    goto L_005787d8;
}

// 0x00578820 sub_578820 -- 1340 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, s3 sp+0x18, ra sp+0x20
// MPEG-2 video: the second slice reader beside sub_578378 (both called by sub_5918A8): the same start-code check
// (0x101), bit reader and VLC table 0x7B29A0.
void sub_578820(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00578820
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = si(-4);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s0, sp, 0x0);
    t0 = s1 & v0;
    sd(s3, sp, 0x18);
    v0 = subu(s1, t0);
    sd(ra, sp, 0x20);
    t1 = sll(v0, 3);
    lb(t2, t0, 0);
    t0 = addiu(t0, 1);
    lbu(v1, t0, 0);
    t0 = addiu(t0, 1);
    lbu(a0, t0, 0);
    t0 = addiu(t0, 1);
    lbu(a1, t0, 0);
    t0 = addiu(t0, 1);
    lb(a3, t0, 0);
    t0 = addiu(t0, 1);
    lbu(v0, t0, 0);
    t0 = addiu(t0, 1);
    t2 = sll(t2, 8);
    a3 = sll(a3, 8);
    t2 = t2 | v1;
    lbu(v1, t0, 0);
    a3 = a3 | v0;
    t2 = sll(t2, 8);
    t0 = addiu(t0, 1);
    a3 = sll(a3, 8);
    t2 = t2 | a0;
    lbu(v0, t0, 0);
    a3 = a3 | v1;
    t2 = sll(t2, 8);
    a3 = sll(a3, 8);
    t2 = t2 | a1;
    t0 = addiu(t0, 1);
    a3 = a3 | v0;
    t2 = sllv(t2, t1);
    if (t1 == 0) {
        // 0x005788e0
        charge(ctx, 2);
        a1 = t2;
        t2 = a3;
    } else {
        // 0x005788c8
        charge(ctx, 5);
        v0 = subu(0, t1);
        v0 = srlv(a3, v0);
        a1 = t2 | v0;
        t2 = sllv(a3, t1);
    }
    // 0x005788e8
    charge(ctx, 17);
    lb(a3, t0, 0);
    t0 = addiu(t0, 1);
    lbu(v0, t0, 0);
    t0 = addiu(t0, 1);
    a3 = sll(a3, 8);
    lbu(v1, t0, 0);
    a3 = a3 | v0;
    t0 = addiu(t0, 1);
    a3 = sll(a3, 8);
    lbu(v0, t0, 0);
    a3 = a3 | v1;
    a0 = 257;
    a3 = sll(a3, 8);
    t0 = addiu(t0, 1);
    a3 = a3 | v0;
    v0 = 0;
    if (a1 == a0) {
        // 0x0057892c
        charge(ctx, 3);
        v0 = slti(t1, 27);
        if (v0 != 0) {
            t1 = addiu(t1, 5);
            // 0x00578988
            charge(ctx, 1);
            t2 = sll(t2, 5);
        } else {
            // 0x00578938
            charge(ctx, 20);
            t1 = addiu(t1, -27);
            t2 = a3;
            v1 = sllv(a3, t1);
            lb(a3, t0, 0);
            v0 = t1 ^ 0x0;
            t0 = addiu(t0, 1);
            if (v0 != 0) t2 = v1;
            lbu(v0, t0, 0);
            a3 = sll(a3, 8);
            t0 = addiu(t0, 1);
            lbu(v1, t0, 0);
            t0 = addiu(t0, 1);
            a3 = a3 | v0;
            lbu(v0, t0, 0);
            a3 = sll(a3, 8);
            t0 = addiu(t0, 1);
            a3 = a3 | v1;
            a3 = sll(a3, 8);
            a3 = a3 | v0;
        }
        // 0x0057898c
        charge(ctx, 3);
        v0 = 31;
        a1 = srl(t2, 31);
        if (t1 != v0) {
            // 0x005789e0
            charge(ctx, 2);
            t1 = addiu(t1, 1);
            t2 = sll(t2, 1);
        } else {
            // 0x00578998
            charge(ctx, 17);
            t2 = a3;
            lb(a3, t0, 0);
            t0 = addiu(t0, 1);
            t1 = 0;
            lbu(v0, t0, 0);
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            lbu(v1, t0, 0);
            a3 = a3 | v0;
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            lbu(v0, t0, 0);
            a3 = a3 | v1;
            t0 = addiu(t0, 1);
            a3 = sll(a3, 8);
            a3 = a3 | v0;
        }
        // 0x005789e8
        charge(ctx, 2);
        v0 = 0;
        if (a1 == 0) {
            // 0x005789f0
            charge(ctx, 3);
            v0 = 31;
            a1 = srl(t2, 31);
            if (t1 != v0) {
                // 0x00578a40
                charge(ctx, 2);
                t1 = addiu(t1, 1);
                t2 = sll(t2, 1);
            } else {
                // 0x005789fc
                charge(ctx, 17);
                t2 = a3;
                lb(a3, t0, 0);
                t0 = addiu(t0, 1);
                t1 = 0;
                lbu(v0, t0, 0);
                t0 = addiu(t0, 1);
                a3 = sll(a3, 8);
                lbu(v1, t0, 0);
                a3 = a3 | v0;
                t0 = addiu(t0, 1);
                a3 = sll(a3, 8);
                lbu(v0, t0, 0);
                a3 = a3 | v1;
                t0 = addiu(t0, 1);
                a3 = sll(a3, 8);
                a3 = a3 | v0;
            }
            // 0x00578a48
            charge(ctx, 2);
            v0 = 0;
            if (a1 != 0) {
                // 0x00578a50
                charge(ctx, 3);
                v0 = slti(t1, 28);
                a1 = srl(t2, 27);
                if (v0 == 0) {
                    // 0x00578a5c
                    charge(ctx, 4);
                    v0 = 59;
                    v0 = subu(v0, t1);
                    v0 = srlv(a3, v0);
                    a1 = a1 | v0;
                }
                // 0x00578a6c
                charge(ctx, 3);
                v1 = 7;
                v0 = 0;
                if (a1 == v1) {
                    // 0x00578a78
                    charge(ctx, 4);
                    t1 = addiu(t1, 5);
                    v0 = slti(t1, 32);
                    if (v0 != 0) {
                        t2 = sll(t2, 5);
                    } else {
                        // 0x00578a88
                        charge(ctx, 16);
                        t1 = addiu(t1, -32);
                        t2 = sllv(a3, t1);
                        lb(a3, t0, 0);
                        t0 = addiu(t0, 1);
                        lbu(v0, t0, 0);
                        t0 = addiu(t0, 1);
                        a3 = sll(a3, 8);
                        lbu(v1, t0, 0);
                        a3 = a3 | v0;
                        t0 = addiu(t0, 1);
                        a3 = sll(a3, 8);
                        lbu(v0, t0, 0);
                        a3 = a3 | v1;
                        t0 = addiu(t0, 1);
                        a3 = sll(a3, 8);
                        a3 = a3 | v0;
                    }
                    // 0x00578ac8
                    charge(ctx, 4);
                    a2 = addiu(a2, -1);
                    t3 = 53;
                    a0 = 8;
                    v0 = slti(t1, 22);
                    for (;;) {
                        // 0x00578ad8
                        charge(ctx, 2);
                        a1 = srl(t2, 21);
                        if (v0 == 0) {
                            // 0x00578ae0
                            charge(ctx, 3);
                            v0 = subu(t3, t1);
                            v0 = srlv(a3, v0);
                            a1 = a1 | v0;
                        }
                        // 0x00578aec
                        charge(ctx, 2);
                        v1 = addiu(a2, -1);
                        if (a1 != a0) {
                            goto L_00578b58;
                        }
                        // 0x00578af4
                        charge(ctx, 4);
                        t1 = addiu(t1, 11);
                        v0 = slti(t1, 32);
                        if (v0 != 0) {
                            t2 = sll(t2, 11);
                        } else {
                            // 0x00578b04
                            charge(ctx, 16);
                            t1 = addiu(t1, -32);
                            t2 = sllv(a3, t1);
                            lb(a3, t0, 0);
                            t0 = addiu(t0, 1);
                            lbu(v0, t0, 0);
                            t0 = addiu(t0, 1);
                            a3 = sll(a3, 8);
                            lbu(v1, t0, 0);
                            a3 = a3 | v0;
                            t0 = addiu(t0, 1);
                            a3 = sll(a3, 8);
                            lbu(v0, t0, 0);
                            a3 = a3 | v1;
                            t0 = addiu(t0, 1);
                            a3 = sll(a3, 8);
                            a3 = a3 | v0;
                        }
                        // 0x00578b44
                        charge(ctx, 4);
                        a2 = addiu(a2, -33);
                        v0 = slti(a2, 34);
                        cc = v0 == 0;  // the condition, before the delay slot changes it
                        v0 = slti(t1, 22);
                        if (!cc) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00578b54
                    charge(ctx, 1);
                    v1 = addiu(a2, -1);
                L_00578b58:
                    charge(ctx, 3);
                    v1 = sltiu(v1, 33);
                    v0 = 0;
                    if (v1 != 0) {
                        // 0x00578b64
                        charge(ctx, 10);
                        v0 = sll(a2, 1);
                        v1 = 32;
                        a2 = 0x7B0000;
                        a2 = addu(a2, v0);
                        lh(a2, a2, 10656);
                        a0 = a2 & 0xFF;
                        v1 = subu(v1, a0);
                        v0 = slt(t1, v1);
                        a1 = srlv(t2, v1);
                        if (v0 != 0) {
                            // 0x00578bf0
                            charge(ctx, 2);
                            t2 = sllv(t2, a0);
                            t1 = addu(t1, a0);
                        } else {
                            // 0x00578b8c
                            charge(ctx, 4);
                            v0 = addu(t1, a0);
                            t1 = addiu(v0, -32);
                            if (t1 == 0) {
                                t2 = a3;
                            } else {
                                // 0x00578b9c
                                charge(ctx, 5);
                                v0 = subu(a0, t1);
                                v0 = srlv(a3, v0);
                                t2 = t2 | v0;
                                a1 = srlv(t2, v1);
                                t2 = sllv(a3, t1);
                            }
                            // 0x00578bb0
                            charge(ctx, 15);
                            lb(a3, t0, 0);
                            t0 = addiu(t0, 1);
                            lbu(v0, t0, 0);
                            t0 = addiu(t0, 1);
                            a3 = sll(a3, 8);
                            lbu(v1, t0, 0);
                            a3 = a3 | v0;
                            t0 = addiu(t0, 1);
                            a3 = sll(a3, 8);
                            lbu(v0, t0, 0);
                            a3 = a3 | v1;
                            t0 = addiu(t0, 1);
                            a3 = sll(a3, 8);
                            a3 = a3 | v0;
                        }
                        // 0x00578bf8
                        charge(ctx, 3);
                        v1 = sra(a2, 8);
                        v0 = 0;
                        if (a1 == v1) {
                            // 0x00578c04
                            charge(ctx, 3);
                            v0 = slti(t1, 28);
                            a1 = srl(t2, 27);
                            if (v0 == 0) {
                                // 0x00578c10
                                charge(ctx, 4);
                                v0 = 59;
                                v0 = subu(v0, t1);
                                v0 = srlv(a3, v0);
                                a1 = a1 | v0;
                            }
                            // 0x00578c20
                            charge(ctx, 3);
                            v1 = 7;
                            v0 = 0;
                            if (a1 == v1) {
                                // 0x00578c2c
                                charge(ctx, 4);
                                t1 = addiu(t1, 5);
                                v0 = slti(t1, 32);
                                cc = v0 != 0;  // the condition, before the delay slot changes it
                                v0 = addiu(t1, 7);
                                if (!cc) {
                                    // 0x00578c3c
                                    charge(ctx, 3);
                                    t1 = addiu(t1, -32);
                                    t0 = addiu(t0, 4);
                                    v0 = addiu(t1, 7);
                                }
                                // 0x00578c48
                                charge(ctx, 7);
                                v0 = sra(v0, 3);
                                v0 = addu(t0, v0);
                                a0 = addiu(v0, -8);
                                a1 = subu(a0, s1);
                                v0 = slt(s2, a1);
                                s3 = 3;
                                if (v0 == 0) {
                                    for (;;) {
                                    L_00578ca8:
                                        charge(ctx, 1);
                                        a1 = subu(s2, a1);
                                        for (;;) {
                                            // 0x00578cac
                                            charge(ctx, 5);
                                            a2 = 204;
                                            jal(ctx, 0x578CACu, gen::fn_sub_578160_00578160);
                                            s0 = v0;
                                            a0 = s0;
                                            if (s0 != 0) {
                                                // 0x00578cc0
                                                charge(ctx, 10);
                                                jal(ctx, 0x578CC0u, gen::fn_sub_577FC8_00577fc8);
                                                a0 = addiu(s0, 1);
                                                a2 = v0;
                                                v0 = subu(s0, s1);
                                                v1 = a2 & 0x4;
                                                t0 = a2 & 0x40;
                                                a3 = v0;
                                                a1 = addiu(v0, 1);
                                                if (v1 == 0) {
                                                    goto L_00578d10;
                                                }
                                                // 0x00578ce8
                                                charge(ctx, 8);
                                                lbu(v0, s0, 5);
                                                lb(v1, s0, 6);
                                                v0 = v0 & 0x3;
                                                v0 = sll(v0, 1);
                                                v1 = srl(v1, 31);
                                                v0 = v0 | v1;
                                                cc = v0 != s3;  // the condition, before the delay slot changes it
                                                v0 = 0;
                                                if (!cc) {
                                                    // 0x00578d08
                                                    charge(ctx, 2);
                                                    a1 = subu(s2, a1);
                                                    backedge(ctx);
                                                    continue;
                                                }
                                            }
                                            break;
                                        }
                                        // 0x00578d40 (the shared epilogue, written out on this path)
                                        charge(ctx, 7);
                                        ld(s0, sp, 0x0);
                                        ld(s1, sp, 0x8);
                                        ld(s2, sp, 0x10);
                                        ld(s3, sp, 0x18);
                                        ld(ra, sp, 0x20);
                                        sp = addiu(sp, 0x30);
                                        return;
                                    }
                                L_00578d20:
                                    charge(ctx, 3);
                                    v0 = a2 & 0x80;
                                    a0 = subu(s0, s1);
                                    if (v0 == 0) {
                                        backedge(ctx);
                                        // 0x00578c70
                                        charge(ctx, 3);
                                        v0 = a2 & 0x8;
                                        cc = v0 == 0;  // the condition, before the delay slot changes it
                                        v0 = 0;
                                        if (!cc) {
                                            // 0x00578c7c
                                            charge(ctx, 4);
                                            lbu(v0, s0, 7);
                                            v0 = v0 & 0x40;
                                            cc = v0 == 0;  // the condition, before the delay slot changes it
                                            v0 = 0;
                                            if (!cc) {
                                                // 0x00578c8c
                                                charge(ctx, 5);
                                                v0 = subu(s0, s1);
                                                a1 = addiu(v0, 7);
                                                v1 = slt(s2, a1);
                                                if (v1 == 0) {
                                                    v0 = 1;
                                                } else {
                                                    // 0x00578ca0
                                                    charge(ctx, 2);
                                                    v0 = 0;
                                                }
                                            }
                                        }
                                    } else {
                                        // 0x00578d2c
                                        charge(ctx, 4);
                                        a1 = addiu(a0, 4);
                                        v1 = slt(s2, a1);
                                        v0 = 0;
                                        if (v1 == 0) {
                                            // 0x00578d3c
                                            charge(ctx, 1);
                                            v0 = 1;
                                        }
                                    }
                                } else {
                                    // 0x00578c64
                                    charge(ctx, 2);
                                    v0 = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x00578d40 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    return;
L_00578d10:
    charge(ctx, 2);
    a1 = addiu(a3, 1);
    if (t0 == 0) {
        goto L_00578d20;
    }
    // 0x00578d18
    charge(ctx, 2);
    a0 = addiu(s0, 1);
    backedge(ctx);
    goto L_00578ca8;
}

// 0x00582BF0 sub_582BF0 -- 116 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// MWSFD: copies a picture's attributes to the output record $a1 + 96: picture structure (sub_582C68), chroma format
// (sub_582CD8), the words +144 / +148 / +152 and the two chroma positions (sub_582D48).
void sub_582BF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00582bf0
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = addiu(a1, 96);
    jal(ctx, 0x582C04u, gen::fn_sub_582C68_00582c68);
    sw(v0, s1, 0);
    a0 = s0;
    s0 = addiu(s0, 136);
    jal(ctx, 0x582C14u, gen::fn_sub_582CD8_00582cd8);
    lw(v1, s0, 8);
    sw(v0, s1, 4);
    sw(v1, s1, 8);
    lw(a0, s0, 20);
    lw(v0, s0, 12);
    sw(v0, s1, 12);
    lw(v1, s0, 16);
    link(ctx, 0x582C38u);  // $ra first: the delay slot below depends on it
    sw(v1, s1, 16);
    call(ctx, gen::fn_sub_582D48_00582d48);
    lw(a0, s0, 24);
    link(ctx, 0x582C44u);  // $ra first: the delay slot below depends on it
    sw(v0, s1, 20);
    call(ctx, gen::fn_sub_582D48_00582d48);
    sw(v0, s1, 24);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00582C68 sub_582C68 -- 108 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Maps the picture structure (+136): 1, 2 and 3 map to themselves; others report "E301272 : picture_structure is
// invalid." (sub_585590) and give 3.
void sub_582C68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00582c68
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 2;
    sd(s0, sp, 0x0);
    s0 = 3;
    sd(ra, sp, 0x8);
    lw(v1, a0, 136);
    a0 = sltiu(v1, 3);
    if (v1 == v0) {
        // 0x00582cb0
        charge(ctx, 2);
        s0 = 2;
    L_00582cc0:
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x00582c88
        charge(ctx, 2);
        v0 = 1;
        if (a0 != 0) {
            // 0x00582c90
            charge(ctx, 2);
            if (v1 != v0) {
                // 0x00582c98
                charge(ctx, 2);
                a0 = 0x7D0000;
                goto L_00582cb8;
            }
            s0 = 1;
            goto L_00582cc0;
        }
        // 0x00582ca0
        charge(ctx, 2);
        v0 = s0;
        if (v1 != s0) {
            // 0x00582ca8
            charge(ctx, 2);
            a0 = 0x7D0000;
        L_00582cb8:
            charge(ctx, 2);
            a0 = addiu(a0, -27984);
            jal(ctx, 0x582CB8u, gen::fn_sub_585590_00585590);
            goto L_00582cc0;
        }
    }
    // 0x00582cc4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00582CD8 sub_582CD8 -- 108 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Maps the chroma format (+140): 1, 2 and 3 map to themselves; others report "E301273 : chroma_format is invalid." and
// give 1.
void sub_582CD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00582cd8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 2;
    sd(s0, sp, 0x0);
    s0 = 1;
    sd(ra, sp, 0x8);
    lw(v1, a0, 140);
    a0 = sltiu(v1, 3);
    if (v1 == v0) {
        // 0x00582d20
        charge(ctx, 2);
        s0 = 2;
    L_00582d30:
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x00582cf8
        charge(ctx, 2);
        if (a0 == 0) {
            v0 = 3;
            // 0x00582d10
            charge(ctx, 2);
            if (v1 == v0) {
                s0 = 3;
            } else {
                // 0x00582d18
                charge(ctx, 2);
                a0 = 0x7D0000;
            L_00582d28:
                charge(ctx, 2);
                a0 = addiu(a0, -27944);
                jal(ctx, 0x582D28u, gen::fn_sub_585590_00585590);
            }
            goto L_00582d30;
        }
        // 0x00582d00
        charge(ctx, 2);
        v0 = s0;
        if (v1 != s0) {
            // 0x00582d08
            charge(ctx, 2);
            a0 = 0x7D0000;
            goto L_00582d28;
        }
    }
    // 0x00582d34 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00582D48 sub_582D48 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Maps a chroma position: 0 and 1 map to themselves; others report "E301274 : chromapos is invalid." and give 1.
void sub_582D48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00582d48
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = 1;
    sd(ra, sp, 0x8);
    if (a0 == 0) {
        // 0x00582d70
        charge(ctx, 2);
        s0 = 0;
    L_00582d80:
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x00582d5c
        charge(ctx, 2);
        v0 = s0;
        if (a0 != s0) {
            // 0x00582d64
            charge(ctx, 2);
            a0 = 0x7D0000;
            // 0x00582d78
            charge(ctx, 2);
            a0 = addiu(a0, -27904);
            jal(ctx, 0x582D78u, gen::fn_sub_585590_00585590);
            goto L_00582d80;
        }
    }
    // 0x00582d84 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00583848 sub_583848 -- 96 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// MWPLY: 0 when sub_5833D8() == 1 or the seek word mwply::kSeekReq is 0; else sub_59C8E0(+60, 2, 0, 0) and 0 on
// success, -1 otherwise.
void sub_583848(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583848
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x583854u, gen::fn_sub_5833D8_005833d8);
    v1 = 1;
    if (v0 != v1) {
        lw(v1, s0, L15::mwply::kSeekReq);
        // 0x00583870
        charge(ctx, 2);
        v0 = 0;
        if (v1 != 0) {
            // 0x00583878
            charge(ctx, 8);
            lw(a0, s0, 60);
            a1 = 2;
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x583884u, gen::fn_sub_59C8E0_0059c8e0);
            v1 = si(-1);
            if (v0 == 0) v1 = 0;
            v0 = v1;
        }
    } else {
        // 0x00583868
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00583898 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005843E8 _get_peer_or_sock_name_0 -- 24 bytes; frame 0x10: ra sp+0x0
// MWPLY: the number of entries in the play list (sub_55D7C0 on mwply::kList, tail call).
void _get_peer_or_sock_name_0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005843e8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, L15::mwply::kList);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55D7C0_0055d7c0(ctx);  // tail call
}

// 0x00584400 sub_584400 -- 196 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// [proposed mwPlyEntryAfs] Adds AFS partition $a1, file $a2 to the play list: an invalid handle (sub_581798 != 1)
// reports "E1122636: mwPlyEntryAfs: handle is invalid."; an entry the AFS table (mwply::kAfs) cannot resolve
// (sub_53DD10) reports "E008311 mwPlyEntryAfs: can't entry pid=%d fid=%d"; else sub_55D428(list, sub_53DEF0(..),
// offset, size, extra) (tail call).
void sub_584400(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584400
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x28);
    s2 = a2;
    jal(ctx, 0x58441Cu, gen::fn_sub_581798_00581798);
    v1 = 1;
    a3 = sp;
    t0 = addiu(sp, 0x4);
    a0 = s0;
    a1 = s2;
    t1 = addiu(sp, 0x8);
    if (v0 == v1) {
        // 0x00584458
        charge(ctx, 7);
        lw(a2, s1, L15::mwply::kAfs);
        link(ctx, 0x58445Cu);  // $ra first: the delay slot below depends on it
        lw(s1, s1, L15::mwply::kList);
        call(ctx, gen::fn_sub_53DD10_0053dd10);
        a0 = s0;
        a1 = s0;
        a2 = s2;
        if (v0 != 0) {
            // 0x005844a0
            charge(ctx, 4);
            a0 = 0x7D0000;
            a0 = addiu(a0, -26040);  // "E008311 mwPlyEntryAfs: can't entry pid=%d fid=%d"
            jal(ctx, 0x5844A4u, gen::fn_sub_585590_00585590);
            ld(s0, sp, 0x10);
        } else {
            // 0x00584474
            charge(ctx, 10);
            jal(ctx, 0x584474u, gen::fn_sub_53DEF0_0053def0);
            a0 = s1;
            lw(a2, sp, 0x0);
            a1 = v0;
            lw(a3, sp, 0x4);
            link(ctx, 0x58448Cu);  // $ra first: the delay slot below depends on it
            lw(t0, sp, 0x8);
            call(ctx, gen::fn_sub_55D428_0055d428);
            ld(s0, sp, 0x10);
        }
    } else {
        // 0x00584440
        charge(ctx, 5);
        a0 = 0x7D0000;
        a0 = addiu(a0, -26088);  // "E1122636: mwPlyEntryAfs: handle is invalid."
        jal(ctx, 0x584444u, gen::fn_sub_585590_00585590);
        ld(s0, sp, 0x10);
    }
    // 0x005844b0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00584558 sub_584558 -- 136 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// [proposed mwPlyEntryFnameRange] Adds a file range (name $a1, start $a2, count $a3) to the play list (sub_55D428,
// tail call); an invalid handle reports "E407023: mwPlyEntryFnameRange: handle is invalid.".
void sub_584558(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584558
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a3;
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    s3 = a0;
    jal(ctx, 0x58457Cu, gen::fn_sub_581798_00581798);
    a0 = 0x7D0000;
    v1 = 1;
    a0 = addiu(a0, -25936);  // "E407023: mwPlyEntryFnameRange: handle is invalid."
    a1 = s0;
    a3 = s1;
    t0 = s2;
    a2 = 0;
    if (v0 != v1) {
        // 0x005845a4
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x005845c0
    charge(ctx, 8);
    lw(a0, s3, L15::mwply::kList);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_55D428_0055d428(ctx);  // tail call
}

// 0x00584748 sub_584748 -- 24 bytes; frame 0x10: ra sp+0x0
// MWPLY: sub_55D7F0 on the play list (mwply::kList), tail call.
void sub_584748(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584748
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, L15::mwply::kList);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55D7F0_0055d7f0(ctx);  // tail call
}

// 0x00584760 sub_584760 -- 24 bytes; frame 0x10: ra sp+0x0
// MWPLY: sub_55D880 on the play list (mwply::kList), tail call.
void sub_584760(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584760
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, L15::mwply::kList);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55D880_0055d880(ctx);  // tail call
}

// 0x005849D0 sub_5849D0 -- 52 bytes; leaf frame (no stack)
// Returns the work sizes: *$a0 = 431404, *$a1 = 81000, *$a2 = 0x2000, and their sum.
void sub_5849D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x005849d0
    enter(ctx, 13);  // entry check point + this block's cycles
    v0 = 0x60000;
    v1 = 0x10000;
    a3 = 8192;
    v0 = v0 | 0x952C;
    v1 = v1 | 0x3C68;
    sw(v0, a0, 0);
    sw(v1, a1, 0);
    sw(a3, a2, 0);
    lw(v0, a0, 0);
    lw(v1, a1, 0);
    v0 = addu(v0, v1);
    v0 = addu(v0, a3);
}

// 0x00584AB0 sub_584AB0 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Runs the WTLS table's init hook (word 0) once: when the table is set and the done count (+4 of the record
// sceLibgcc32GetErxEntries_19 returns) is 0; the count is then 1 (or the table + 1 without a hook).
void sub_584AB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584ab0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    jal(ctx, 0x584ABCu, gen::fn_sceLibgcc32GetErxEntries_19_005851a0);
    s0 = v0;
    jal(ctx, 0x584AC4u, gen::fn_WTLS_get_table_1_005851b0);
    v1 = v0;
    if (v1 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00584ad8
        charge(ctx, 3);
        lw(v0, s0, 4);
        if (v0 != 0) {
            ld(s0, sp, 0x0);
        } else {
            // 0x00584ae4
            charge(ctx, 3);
            lw(v1, v1, 0);
            if (v1 == 0) {
                v0 = addiu(v0, 1);
            } else {
                // 0x00584af0
                charge(ctx, 4);
                jalr(ctx, 0x584AF0u, v1.u());
                lw(v0, s0, 4);
                v0 = addiu(v0, 1);
            }
            // 0x00584b00
            charge(ctx, 2);
            sw(v0, s0, 4);
            ld(s0, sp, 0x0);
        }
    }
    // 0x00584b08 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00584B78 sub_584B78 -- 100 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Calls the WTLS table's hook +8 with ($a0, $a1, $a2) when the table and the hook are set; else 0.
void sub_584B78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584b78
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x584B94u, gen::fn_WTLS_get_table_1_005851b0);
    v1 = 0;
    if (v0 != 0) {
        // 0x00584ba4
        charge(ctx, 3);
        lw(v0, v0, 8);
        a0 = s0;
        if (v0 != 0) {
            // 0x00584bb0
            charge(ctx, 4);
            a1 = s1;
            a2 = s2;
            jalr(ctx, 0x584BB4u, v0.u());
            v1 = v0;
        }
    }
    // 0x00584bc0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    v0 = v1;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00584BE0 sub_584BE0 -- 84 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Calls the WTLS table's hook +12 with ($a0, $a1) when the table and the hook are set; else 0.
void sub_584BE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584be0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x584BF4u, gen::fn_WTLS_get_table_1_005851b0);
    v1 = 0;
    if (v0 != 0) {
        // 0x00584c04
        charge(ctx, 3);
        lw(v0, v0, 12);
        a0 = s0;
        if (v0 != 0) {
            // 0x00584c10
            charge(ctx, 3);
            a1 = s1;
            jalr(ctx, 0x584C10u, v0.u());
            v1 = v0;
        }
    }
    // 0x00584c1c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    v0 = v1;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00584E68 sub_584E68 -- 96 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// When sub_5851D0() == 1: calls the WTLS hook +40 with (the object's +20, $a1).
void sub_584E68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584e68
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x584E7Cu, gen::fn_sub_5851D0_005851d0);
    v1 = 1;
    if (v0 != v1) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00584e90
        charge(ctx, 4);
        jal(ctx, 0x584E90u, gen::fn_WTLS_get_table_1_005851b0);
        lw(a0, s0, 20);
        if (v0 != 0) {
            // 0x00584ea0
            charge(ctx, 3);
            lw(v0, v0, 40);
            if (v0 != 0) {
                // 0x00584eac
                charge(ctx, 2);
                a1 = s1;
                jalr(ctx, 0x584EACu, v0.u());
                goto L_00584eb4;
            }
            ld(s0, sp, 0x0);
            // 0x00584eb8 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x10);
            sp = addiu(sp, 0x20);
            return;
        }
    L_00584eb4:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x00584eb8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00584EC8 sub_584EC8 -- 104 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// When sub_5851D0() == 1: calls the WTLS hook +44 with the object's +20 and returns its result; else 0.
void sub_584EC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00584ec8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = 0;
    jal(ctx, 0x584EDCu, gen::fn_sub_5851D0_005851d0);
    v1 = 1;
    cc = v0 != v1;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x00584ef0
        charge(ctx, 4);
        jal(ctx, 0x584EF0u, gen::fn_WTLS_get_table_1_005851b0);
        lw(a0, s0, 20);
        if (v0 != 0) {
            // 0x00584f00
            charge(ctx, 3);
            lw(v0, v0, 44);
            if (v0 != 0) {
                // 0x00584f0c
                charge(ctx, 3);
                jalr(ctx, 0x584F0Cu, v0.u());
                s1 = v0;
                goto L_00584f18;
            }
            v0 = s1;
            // 0x00584f1c (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x10);
            sp = addiu(sp, 0x20);
            return;
        }
    L_00584f18:
        charge(ctx, 1);
        v0 = s1;
    }
    // 0x00584f1c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00585250 sub_585250 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail call to sub_565590.
void sub_585250(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00585250
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_565590_00565590(ctx);  // tail call
}

// 0x00585340 sub_585340 -- 32 bytes; frame 0x10: ra sp+0x0
// sub_564EF8(2, *0x9A6EC4) (tail call).
void sub_585340(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585340
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x9A0000;
    sd(ra, sp, 0x0);
    a0 = 2;
    lw(a1, v0, 28356);  // 0x9A6EC4
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564EF8_00564ef8(ctx);  // tail call
}

// 0x00585398 sub_585398 -- 32 bytes; frame 0x10: ra sp+0x0
// sub_564EF8(6, *0x9A6EC8) (tail call).
void sub_585398(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585398
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x9A0000;
    sd(ra, sp, 0x0);
    a0 = 6;
    lw(a1, v0, 28360);  // 0x9A6EC8
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564EF8_00564ef8(ctx);  // tail call
}

// 0x005853F0 sub_5853F0 -- 32 bytes; frame 0x10: ra sp+0x0
// sub_564EF8(5, *0x9A6ECC) (tail call).
void sub_5853F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005853f0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x9A0000;
    sd(ra, sp, 0x0);
    a0 = 5;
    lw(a1, v0, 28364);  // 0x9A6ECC
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564EF8_00564ef8(ctx);  // tail call
}

// 0x00585440 sub_585440 -- 60 bytes, 2 chunks; frame 0x10: ra sp+0x0
// sub_565690(0, 0), then clears the pair 0x99A0C8 / 0x99A0CC and returns its address (the function starts in a chunk
// at 0x5656A8).
void sub_585440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585440
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0;
    sd(ra, sp, 0x0);
    a1 = 0;
    jal(ctx, 0x58544Cu, gen::fn_sub_565690_00565690);
    a0 = 0;
    ld(ra, sp, 0x0);
    a1 = 0;
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x005656a8
    charge(ctx, 5);
    v0 = 0x9A0000;
    v0 = addiu(v0, -24376);  // &0x99A0C8
    sw(a1, v0, 4);  // 0x99A0CC
    sw(a0, v0, 0);  // 0x99A0C8
}

// 0x00585658 sinl_11 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail call to sub_564B50.
void sinl_11(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00585658
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564B50_00564b50(ctx);  // tail call
}

// 0x00586110 sub_586110 -- 32 bytes; frame 0x10: ra sp+0x0
// The current thread's word +88 (the record __gthread_get_ee_key_use returns).
void sub_586110(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586110
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x586118u, gen::fn___gthread_get_ee_key_use_0057f740);
    lw(v0, v0, 88);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00586300 sub_586300 -- 8 bytes; leaf frame (no stack)
// Returns 0.
void sub_586300(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00586300
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00586308 sub_586308 -- 40 bytes; frame 0x10: ra sp+0x0
// When $a0 is nonzero: sub_547008; returns 0.
void sub_586308(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586308
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0;
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00586318
        charge(ctx, 3);
        jal(ctx, 0x586318u, gen::fn_sub_547008_00547008);
        v0 = 0;
    }
    // 0x00586324 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00586450 sub_586450 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail call to sub_546EF0.
void sub_586450(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00586450
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_546EF0_00546ef0(ctx);  // tail call
}

// 0x00586468 sub_586468 -- 40 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// *$a1 = sub_547068().
void sub_586468(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586468
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a1;
    jal(ctx, 0x586474u, gen::fn_sub_547068_00547068);
    sw(v0, s0, 0);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00586628 sub_586628 -- 96 bytes; frame 0x10: ra sp+0x0
// The ADX header probe: *$a2 = 288 (the bytes it needs); true when at least 288 bytes ($a1) are there, the header
// starts 0x80 0x00 and the copyright "(c)CRI" stands at +282 (strncmp, 6 bytes).
void sub_586628(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586628
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 288;
    sp = addiu(sp, -0x10);
    a1 = slti(a1, 288);
    sd(ra, sp, 0x0);
    sw(v0, a2, 0);
    a2 = a0;
    v0 = 0;
    if (a1 == 0) {
        // 0x00586648
        charge(ctx, 4);
        lbu(a0, a2, 0);
        v1 = 128;
        if (a0 != v1) {
            ld(ra, sp, 0x0);
        } else {
            // 0x00586658
            charge(ctx, 3);
            lbu(v1, a2, 1);
            if (v1 == 0) {
                // 0x00586664
                charge(ctx, 6);
                a1 = 0x7D0000;
                a0 = addiu(a2, 282);
                a1 = addiu(a1, -25144);  // "(c)CRI"
                a2 = 6;
                jal(ctx, 0x586670u, gen::fn_strncmp_00524670);
                v0 = sltiu(v0, 1);
                goto L_0058667c;
            }
            ld(ra, sp, 0x0);
        }
        // 0x00586680 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_0058667c:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x00586680 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x005866C8 sub_5866C8 -- 28 bytes; frame 0x10: ra sp+0x0
// sceInsockListen_2 on the stream's first word (**(h + adxs::kWork)), tail call.
void sub_5866C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005866c8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, L15::adxs::kWork);
    ld(ra, sp, 0x0);
    lw(a0, v0, 0);
    sp = addiu(sp, 0x10);
    gen::fn_sceInsockListen_2_00549160(ctx);  // tail call
}

// 0x005866E8 sub_5866E8 -- 28 bytes; frame 0x10: ra sp+0x0
// sub_5492C8 on the stream's first word (**(h + adxs::kWork)), tail call.
void sub_5866E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005866e8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, L15::adxs::kWork);
    ld(ra, sp, 0x0);
    lw(a0, v0, 0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5492C8_005492c8(ctx);  // tail call
}

// 0x00586708 sub_586708 -- 28 bytes; frame 0x10: ra sp+0x0
// sub_549480 on the stream's first word (**(h + adxs::kWork)), tail call.
void sub_586708(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586708
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, L15::adxs::kWork);
    ld(ra, sp, 0x0);
    lw(a0, v0, 0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_549480_00549480(ctx);  // tail call
}

// 0x00586728 sub_586728 -- 28 bytes; frame 0x10: ra sp+0x0
// sub_549530 on the stream's first word (**(h + adxs::kWork)), tail call.
void sub_586728(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586728
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, L15::adxs::kWork);
    ld(ra, sp, 0x0);
    lw(a0, v0, 0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_549530_00549530(ctx);  // tail call
}

// 0x00586748 R_LOCK_DEF_w_lock_4 -- 184 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Sets the playback speed $a1 (1000 = normal) as a pitch: cents = (logf(speed) - ln 1000) * 1731.234 (= 1200 / ln 2),
// passed as (cents / 100, cents % 100) to __env_lock_0 on the stream's first word; 1000 gives (0, 0). Without a stream
// it returns 1000.
void R_LOCK_DEF_w_lock_4(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x00586748
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    lw(v0, a0, L15::adxs::kWork);
    lw(s0, v0, 0);
    v0 = 1000;
    if (s0 == 0) {
        // 0x005867f0
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00586764
    charge(ctx, 2);
    a2 = 0;
    if (a1 != v0) {
        // 0x00586778
        charge(ctx, 25);
        mtc1(a1, f12);
        cvt_s_w(f12, f12);
        jal(ctx, 0x58677Cu, gen::fn_logf_0052ea30);
        at = 0x40DD0000;
        at = at | 0xC54;
        mtc1(at, f2);
        at = 0x44D80000;
        at = at | 0x677D;
        mtc1(at, f3);
        sub_s(f0, f0, f2);
        at = 0x3C230000;
        at = at | 0xD70A;
        mtc1(at, f1);
        mul_s(f0, f0, f3);
        mul_s(f1, f0, f1);
        cvt_w_s(f2, f0);
        mfc1(v1, f2);
        cvt_w_s(f0, f1);
        mfc1(a1, f0);
        v0 = sll(a1, 1);
        v0 = addu(v0, a1);
        v0 = sll(v0, 3);
        v0 = addu(v0, a1);
        v0 = sll(v0, 2);
        a2 = subu(v1, v0);
    } else {
        // 0x0058676c
        charge(ctx, 2);
        a1 = 0;
    }
    // 0x005867dc
    charge(ctx, 5);
    a0 = s0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn___env_lock_0_0054a630(ctx);  // tail call
}

// 0x00586C10 sub_586C10 -- 616 bytes; frame 0x70: fp sp+0x60, s1 sp+0x28, s4 sp+0x40, s5 sp+0x48, s7 sp+0x58, s0 sp+0x20, s2 sp+0x30, s3 sp+0x38, s6 sp+0x50, ra sp+0x68
// ADX stream: one decode step over the input ($a1, $a2 bytes): with the header not yet parsed (sub_587218) it switches
// the step to sub_586B58; else it takes the decoder's block window (sub_599EC8 / sub_599F28 / sub_599FA0 on h + 3376),
// decodes whole 18-byte blocks (sub_586E78, the block count adxs::kBlocks += 32 per block row) or skips the excess
// (sub_586F00), marks the end (sub_599240(h, 6, 0)) and adds the bytes taken to the 64-bit position adxs::kPos; *$a3 =
// the bytes.
void sub_586C10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00586c10
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(fp, sp, 0x60);
    fp = a3;
    sd(s1, sp, 0x28);
    sd(s4, sp, 0x40);
    s4 = a0;
    sd(s5, sp, 0x48);
    s5 = a2;
    sd(s7, sp, 0x58);
    s7 = a1;
    sd(s0, sp, 0x20);
    a2 = addiu(sp, 0x4);
    sd(s2, sp, 0x30);
    a1 = sp;
    sd(s3, sp, 0x38);
    s1 = addiu(s4, 3376);
    sd(s6, sp, 0x50);
    sd(ra, sp, 0x68);
    sw(zero, fp, 0x0);
    link(ctx, 0x586C5Cu);  // $ra first: the delay slot below depends on it
    lw(s3, s4, L15::adxs::kWork);
    call(ctx, gen::fn_sub_587218_00587218);
    if (v0 != 0) {
        v0 = 0x580000;
    } else {
        // 0x00586c6c
        charge(ctx, 6);
        lw(a1, sp, 0x4);
        a0 = s1;
        jal(ctx, 0x586C70u, gen::fn_sub_599EC8_00599ec8);
        s2 = v0;
        a0 = s4;
        if (i64(s2) >= 0) {
            // 0x00586c84
            charge(ctx, 4);
            a1 = 5;
            jal(ctx, 0x586C84u, gen::fn_sub_599408_00599408);
            if (v0 == 0) {
                // 0x00586c94
                charge(ctx, 5);
                lw(a2, sp, 0x4);
                a0 = s1;
                a1 = s2;
                jal(ctx, 0x586C9Cu, gen::fn_sub_599FA0_00599fa0);
                v0 = 0x580000;
                goto L_00586ca8;
            }
            lw(a1, sp, 0x4);
            // 0x00586cb8
            charge(ctx, 6);
            a0 = s1;
            a2 = addiu(sp, 0x8);
            jal(ctx, 0x586CBCu, gen::fn_sub_599F28_00599f28);
            s0 = v0;
            a0 = s1;
            if (i64(s0) >= 0) {
                // 0x00586cd0
                charge(ctx, 9);
                lw(a2, sp, 0x4);
                a1 = s0;
                s6 = 0;
                jal(ctx, 0x586CD8u, gen::fn_sub_599FA0_00599fa0);
                v1 = subu(s0, s2);
                lw(v0, s3, L15::adxs::kBlocks);
                v1 = subu(v1, v0);
                lw(a1, sp, 0x0);
                if (i64(v1) < 0) {
                    // 0x00586de0
                    charge(ctx, 3);
                    lw(v0, sp, 0x8);
                    a0 = subu(0, v1);
                    if (v0 != 0) {
                        // 0x00586dec
                        charge(ctx, 7);
                        v0 = addiu(a0, 31);
                        v1 = slti(a0, 0);
                        if (v1 != 0) a0 = v0;
                        a0 = sra(a0, 5);
                        s0 = sll(a0, 5);
                        if (i64(s0) <= 0) {
                            v0 = 0x580000;
                        } else {
                            // 0x00586e08
                            charge(ctx, 9);
                            lw(a1, sp, 0x0);
                            a0 = s4;
                            a2 = s0;
                            jal(ctx, 0x586E10u, gen::fn_sub_586F00_00586f00);
                            lw(v1, s3, L15::adxs::kBlocks);
                            a0 = subu(s0, v0);
                            v1 = subu(v1, v0);
                            sw(v1, s3, L15::adxs::kBlocks);
                            if (i64(a0) <= 0) {
                                // 0x00586e2c
                                charge(ctx, 1);
                                v0 = 0x580000;
                                goto L_00586e30;
                            }
                            goto L_00586e38;
                        }
                    L_00586e30:
                        charge(ctx, 2);
                        v0 = addiu(v0, 27480);
                        sw(v0, s3, L15::adxs::kStep);
                    }
                L_00586e38:
                    charge(ctx, 1);
                    ld(v0, s4, 2504);
                } else {
                    // 0x00586cf4
                    charge(ctx, 7);
                    v1 = sra(v1, 5);
                    mult(v1, v1, a1);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    s1 = sll(v0, 1);
                    sw(zero, sp, 0xC);
                    if (i64(s1) > 0) {
                        // 0x00586d10
                        charge(ctx, 8);
                        v0 = sll(a1, 3);
                        a0 = s7;
                        v0 = addu(v0, a1);
                        a2 = addiu(sp, 0xC);
                        v0 = sll(v0, 1);
                        div(s5, v0);
                        if (v0 == 0) {
                            brk(ctx, 0x586D2Cu, 0x7u);
                        }
                        // 0x00586d30
                        charge(ctx, 19);
                        mflo(v1);
                        mult(v1, v1, a1);
                        v0 = sll(v1, 3);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 1);
                        s0 = v0;
                        v0 = slt(v0, s1);
                        if (v0 == 0) s0 = s1;
                        a1 = s0;
                        s0 = subu(s1, s0);
                        jal(ctx, 0x586D54u, gen::fn_sub_586E78_00586e78);
                        lw(v1, sp, 0x0);
                        s6 = v0;
                        v0 = sll(v1, 3);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 1);
                        div(s6, v0);
                        if (v0 == 0) {
                            brk(ctx, 0x586D78u, 0x7u);
                        }
                        // 0x00586d7c
                        charge(ctx, 6);
                        lw(v1, s3, L15::adxs::kBlocks);
                        mflo(a0);
                        a0 = sll(a0, 5);
                        v1 = addu(v1, a0);
                        sw(v1, s3, L15::adxs::kBlocks);
                        if (i64(s0) <= 0) {
                            goto L_00586d94;
                        }
                        goto L_00586dbc;
                    }
                L_00586d94:
                    charge(ctx, 3);
                    lw(v0, sp, 0x8);
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = 0x580000;
                    if (!cc) {
                        // 0x00586da0
                        charge(ctx, 7);
                        a0 = s7;
                        v0 = addiu(v0, 27480);
                        a1 = s5;
                        sw(v0, s3, L15::adxs::kStep);
                        a2 = addiu(sp, 0x10);
                        jal(ctx, 0x586DB0u, gen::fn_sub_54AC40_0054ac40);
                        sw(v0, sp, 0xC);
                    }
                L_00586dbc:
                    charge(ctx, 3);
                    lw(v0, sp, 0xC);
                    a0 = s4;
                    if (v0 == 0) {
                        goto L_00586e38;
                    }
                    // 0x00586dc8
                    charge(ctx, 5);
                    a1 = 6;
                    a2 = 0;
                    jal(ctx, 0x586DCCu, gen::fn_sub_599240_00599240);
                    ld(v0, s4, 2504);
                }
                // 0x00586e3c
                charge(ctx, 3);
                sw(s6, fp, 0x0);
                v0 = s6 + v0;
                sd(v0, s4, 2504);
            }
        }
        // 0x00586e48 (the shared epilogue, written out on this path)
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
L_00586ca8:
    charge(ctx, 3);
    v0 = addiu(v0, 27480);
    sw(v0, s3, L15::adxs::kStep);
    // 0x00586e48 (the shared epilogue, written out on this path)
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

// 0x00586E78 sub_586E78 -- 136 bytes; frame 0x40: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, ra sp+0x38
// Feeds 18-byte ADX blocks from $a0 to sub_54AC40 until $a1 bytes or a nonzero result (then *$a2 = 1); returns the
// bytes fed.
void sub_586E78(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00586e78
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = 0;
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(s3, sp, 0x28);
    s3 = a2;
    sd(s4, sp, 0x30);
    s4 = 1;
    sd(ra, sp, 0x38);
    sw(zero, s3, 0);
    for (;;) {
        // 0x00586eb4
        charge(ctx, 3);
        v0 = slt(s1, s2);
        if (v0 != 0) {
            // 0x00586ec0
            charge(ctx, 7);
            a0 = s0;
            s0 = addiu(s0, 18);
            a1 = 18;
            a2 = sp;
            jal(ctx, 0x586ECCu, gen::fn_sub_54AC40_0054ac40);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = s1;
            if (!cc) {
                goto L_00586edc_4;
            }
            backedge(ctx);
            // 0x00586eb0
            charge(ctx, 1);
            s1 = addiu(s1, 18);
            continue;
        }
        v0 = s1;
        break;
    }
    // 0x00586ee0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
    return;
L_00586edc_4:
    charge(ctx, 1);
    sw(s4, s3, 0);
    // 0x00586ee0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x00586F00 sub_586F00 -- 28 bytes; frame 0x10: ra sp+0x0
// sub_54AC80 on the stream's first word (**(h + adxs::kWork)), tail call.
void sub_586F00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586f00
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, L15::adxs::kWork);
    ld(ra, sp, 0x0);
    lw(a0, v0, 0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_54AC80_0054ac80(ctx);  // tail call
}

// 0x00587100 sub_587100 -- 276 bytes; frame 0x50: s5 sp+0x38, s0 sp+0x10, s2 sp+0x20, s3 sp+0x28, s1 sp+0x18, s4 sp+0x30, ra sp+0x40
// ADX stream: skips leading silent blocks (18 zero bytes, memcmp with 0x7C9DB0) of the input; at the first non-silent
// one, or when sub_58BBB0() >= 108, the step becomes sub_586F20. Adds the bytes skipped to the position adxs::kPos
// (*$a3 = them) and, when the header is known (sub_587218 == 0), 32 per channel row to adxs::kBlocks.
void sub_587100(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587100
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s5, sp, 0x38);
    s5 = a3;
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s3, sp, 0x28);
    s3 = a2;
    sd(s1, sp, 0x18);
    sd(s4, sp, 0x30);
    sd(ra, sp, 0x40);
    sw(zero, s5, 0);
    link(ctx, 0x587134u);  // $ra first: the delay slot below depends on it
    lw(s4, s2, L15::adxs::kWork);
    call(ctx, gen::fn_sub_58BBB0_0058bbb0);
    v0 = slti(v0, 108);
    s1 = 0;
    if (v0 == 0) {
        // 0x00587148
        charge(ctx, 4);
        v0 = 0x580000;
        v0 = addiu(v0, 28448);  // &sub_586F20
        sw(v0, s4, L15::adxs::kStep);
        goto L_005871f0;
    }
    // 0x00587158
    charge(ctx, 2);
    s3 = addiu(s3, -18);
    for (;;) {
        // 0x00587164
        charge(ctx, 3);
        v0 = slt(s1, s3);
        if (v0 != 0) {
            // 0x00587170
            charge(ctx, 7);
            a1 = 0x7D0000;
            a0 = s0;
            a1 = addiu(a1, -25168);  // &0x7C9DB0
            a2 = 18;
            jal(ctx, 0x58717Cu, gen::fn_memcmp_005211b8);
            s0 = addiu(s0, 18);
            if (v0 != 0) {
                goto L_0058718c_6;
            }
            backedge(ctx);
            // 0x00587160
            charge(ctx, 1);
            s1 = addiu(s1, 18);
            continue;
        }
        ld(v0, s2, 2504);
        break;
    }
L_0058719c:
    charge(ctx, 9);
    a0 = s2;
    sw(s1, s5, 0);
    a1 = sp;
    v0 = s1 + v0;
    a2 = addiu(sp, 0x4);
    link(ctx, 0x5871B0u);  // $ra first: the delay slot below depends on it
    sd(v0, s2, 2504);
    call(ctx, gen::fn_sub_587218_00587218);
    ld(s0, sp, 0x10);
    if (v0 == 0) {
        // 0x005871c0
        charge(ctx, 7);
        lw(v1, sp, 0x0);
        v0 = sll(v1, 3);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        div(s1, v0);
        if (v0 == 0) {
            brk(ctx, 0x5871D8u, 0x7u);
        }
        // 0x005871dc
        charge(ctx, 5);
        lw(v1, s4, L15::adxs::kBlocks);
        mflo(a0);
        a0 = sll(a0, 5);
        v1 = addu(v1, a0);
        sw(v1, s4, L15::adxs::kBlocks);
    L_005871f0:
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    }
    // 0x005871f4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
    return;
L_0058718c_6:
    charge(ctx, 4);
    v0 = 0x580000;
    v0 = addiu(v0, 28448);  // &sub_586F20
    sw(v0, s4, L15::adxs::kStep);
    ld(v0, s2, 2504);
    goto L_0058719c;
}

// 0x00587FD8 sub_587FD8 -- 76 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// *$a1 = sub_57BAF0($a2, the two words sub_59AD40($a0) returns).
void sub_587FD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587fd8
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a2;
    sd(s1, sp, 0x18);
    s1 = a1;
    a2 = addiu(sp, 0x4);
    sd(ra, sp, 0x20);
    a1 = sp;
    jal(ctx, 0x587FF4u, gen::fn_sub_59AD40_0059ad40);
    lw(a1, sp, 0x0);
    a0 = s0;
    link(ctx, 0x588004u);  // $ra first: the delay slot below depends on it
    lw(a2, sp, 0x4);
    call(ctx, gen::fn_sub_57BAF0_0057baf0);
    sw(v0, s1, 0);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00588360 sub_588360 -- 84 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// When sub_599408(h, 6): calls the callback +20 of the record at h + 8468 with (h, $a1).
void sub_588360(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588360
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a1;
    a1 = 6;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x588378u, gen::fn_sub_599408_00599408);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00588388
        charge(ctx, 4);
        lw(v0, s0, L15::adxs::kCbRec);
        lw(v0, v0, 20);
        a0 = s0;
        if (v0 != 0) {
            // 0x00588398
            charge(ctx, 2);
            a1 = s1;
            jalr(ctx, 0x588398u, v0.u());
        }
        // 0x005883a0
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x005883a4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00588568 sub_588568 -- 72 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// When sub_599408(h, 6): sub_59BC20(h, 3, 5, 0, 0) (tail call).
void sub_588568(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588568
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 6;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x588578u, gen::fn_sub_599408_00599408);
    a0 = s0;
    a1 = 3;
    a2 = 5;
    a3 = 0;
    t0 = 0;
    if (v0 != 0) {
        // 0x00588598
        charge(ctx, 2);
        jal(ctx, 0x588598u, gen::fn_sub_59BC20_0059bc20);
    }
    // 0x005885a0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00588640 sub_588640 -- 84 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// When sub_599408(h, 6): sub_59BC20(h, 3, 8, $a1, 0) (tail call).
void sub_588640(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588640
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a1;
    a1 = 6;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x588658u, gen::fn_sub_599408_00599408);
    a0 = s0;
    a3 = s1;
    a1 = 3;
    a2 = 8;
    t0 = 0;
    if (v0 != 0) {
        // 0x00588678
        charge(ctx, 2);
        jal(ctx, 0x588678u, gen::fn_sub_59BC20_0059bc20);
    }
    // 0x00588680 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00588698 sub_588698 -- 28 bytes; frame 0x10: ra sp+0x0
// sub_58BE40(h, 0xFF000A01) (tail call).
void sub_588698(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588698
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0xA01;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

}  // namespace p3fes::game
