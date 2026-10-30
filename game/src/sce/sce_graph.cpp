// Slice sce1 (sce_graph.cpp): libgraph's environment builders and libdma's pure helpers.
// p3fes_handgen bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): register for register, block for block the
// recompiled body (frame, spills, $ra links, cycle charges, check points). Each function carries its role and what the
// instructions do, from the binary and public PS2 hardware documentation only (the Sony SDK is proprietary: no SDK
// source or header was used; names are symbols/functions.json's, ADR-0009). Named layouts: game/include/p3fes/game/sce.h.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/sce.h"

namespace p3fes::recomp_gen {
void fn_AlarmHandler_0050f030(p3fes::EEContext&);
void fn_CheckAddress_004fa890(p3fes::EEContext&);
void fn_DPRINT_0051d588(p3fes::EEContext&);
void fn_Exit_0050da58(p3fes::EEContext&);
void fn_QueueInit_00504678(p3fes::EEContext&);
void fn_QueuePeekReadDone_005046e0(p3fes::EEContext&);
void fn_QueuePeekWriteDone_005046a0(p3fes::EEContext&);
void fn__InitAlarm_0050efe0(p3fes::EEContext&);
void fn___divdi3_0052eeb0(p3fes::EEContext&);
void fn___fixunsdfdi_0052ec28(p3fes::EEContext&);
void fn___fixunssfdi_0052eda0(p3fes::EEContext&);
void fn___floatdisf_0052eb60(p3fes::EEContext&);
void fn___moddi3_0052f6a0(p3fes::EEContext&);
void fn___sceKernlGetEhSemaId_0050d468(p3fes::EEContext&);
void fn___udivdi3_0052fe98(p3fes::EEContext&);
void fn___umoddi3_00530578(p3fes::EEContext&);
void fn__change_addr_00505f68(p3fes::EEContext&);
void fn__fs_version_00508378(p3fes::EEContext&);
void fn__get_dir_nest_005151d0(p3fes::EEContext&);
void fn__get_free_slot_0051c0f8(p3fes::EEContext&);
void fn__lf_version_0050bbe8(p3fes::EEContext&);
void fn__make_path_00515218(p3fes::EEContext&);
void fn__sceSnprintf_00504f48(p3fes::EEContext&);
void fn__sceSnprintf_pf_00505d08(p3fes::EEContext&);
void fn__sce_GetGsDxDyOffset_004f9158(p3fes::EEContext&);
void fn__set_sreg_00505f48(p3fes::EEContext&);
void fn__strtok_005150b0(p3fes::EEContext&);
void fn_atoi_0051e0f0(p3fes::EEContext&);
void fn_checkModelVersion_004f90b8(p3fes::EEContext&);
void fn_close_00503848(p3fes::EEContext&);
void fn_deci2Putchar_00504bf8(p3fes::EEContext&);
void fn_dpcmp_005316d0(p3fes::EEContext&);
void fn_dpdiv_00531480(p3fes::EEContext&);
void fn_dpmul_00531230(p3fes::EEContext&);
void fn_dpsub_005311c8(p3fes::EEContext&);
void fn_dptofp_005318a0(p3fes::EEContext&);
void fn_fptodp_00530da0(p3fes::EEContext&);
void fn_fstat_00503918(p3fes::EEContext&);
void fn_ftoi_00504ce0(p3fes::EEContext&);
void fn_getpid_00503930(p3fes::EEContext&);
void fn_instr_00514d50(p3fes::EEContext&);
void fn_ioctl_00503850(p3fes::EEContext&);
void fn_isCorrFname_00514e20(p3fes::EEContext&);
void fn_isCorrNameSize_00514db0(p3fes::EEContext&);
void fn_isPathCurParent_00514e78(p3fes::EEContext&);
void fn_isWildFit_00514f30(p3fes::EEContext&);
void fn_isatty_00503910(p3fes::EEContext&);
void fn_kill_00503938(p3fes::EEContext&);
void fn_kprintf_char_00505ce0(p3fes::EEContext&);
void fn_kputchar_00504bc0(p3fes::EEContext&);
void fn_kputs_00504650(p3fes::EEContext&);
void fn_lseek_00503858(p3fes::EEContext&);
void fn_memclr_004fa8b8(p3fes::EEContext&);
void fn_memcmp_005211b8(p3fes::EEContext&);
void fn_nullsub_131_0050dc78(p3fes::EEContext&);
void fn_open_00503820(p3fes::EEContext&);
void fn_printf_char_00505cb8(p3fes::EEContext&);
void fn_printfloat_00504d70(p3fes::EEContext&);
void fn_sceClose_00508900(p3fes::EEContext&);
void fn_sceDmaGetEnv_004fabd0(p3fes::EEContext&);
void fn_sceGsGetGParam_004f9040(p3fes::EEContext&);
void fn_sceGsSetDefDispEnv_004f9168(p3fes::EEContext&);
void fn_sceGsSetDefDrawEnv2_004fa558(p3fes::EEContext&);
void fn_sceGsSetDefDrawEnv_004f9668(p3fes::EEContext&);
void fn_sceGsSetDefStoreImage_004f9ce8(p3fes::EEContext&);
void fn_sceGszbufaddr_004f95a0(p3fes::EEContext&);
void fn_sceOpen_00508670(p3fes::EEContext&);
void fn_scePrintf_00505e48(p3fes::EEContext&);
void fn_sceRead_00508cb8(p3fes::EEContext&);
void fn_sceResetttyinit_005035e0(p3fes::EEContext&);
void fn_sceSifGetDataTable_00505fb0(p3fes::EEContext&);
void fn_sceSifGetSreg_00505f78(p3fes::EEContext&);
void fn_sceSifSetSreg_00505f90(p3fes::EEContext&);
void fn_sceSnprintf_00505d90(p3fes::EEContext&);
void fn_sceTtyRead_00504a30(p3fes::EEContext&);
void fn_sceVsnprintf_00505d58(p3fes::EEContext&);
void fn_serialPutchar_00504ca8(p3fes::EEContext&);
void fn_snprintf_char_00505c60(p3fes::EEContext&);
void fn_stat_00503960(p3fes::EEContext&);
void fn_strcat_00523e68(p3fes::EEContext&);
void fn_strchr_00523f98(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncmp_00524670(p3fes::EEContext&);
void fn_strrchr_005249e8(p3fes::EEContext&);
void fn_sub_506400_00506400(p3fes::EEContext&);
void fn_sub_506418_00506418(p3fes::EEContext&);
void fn_sub_506430_00506430(p3fes::EEContext&);
void fn_sub_50D840_0050d840(p3fes::EEContext&);
void fn_sub_50E190_0050e190(p3fes::EEContext&);
void fn_sub_50E218_0050e218(p3fes::EEContext&);
void fn_sub_50E5D8_0050e5d8(p3fes::EEContext&);
void fn_sub_50E690_0050e690(p3fes::EEContext&);
void fn_sub_50E7A0_0050e7a0(p3fes::EEContext&);
void fn_sub_50EB50_0050eb50(p3fes::EEContext&);
void fn_sub_50EE38_0050ee38(p3fes::EEContext&);
void fn_sub_50EEE0_0050eee0(p3fes::EEContext&);
void fn_sub_50EF50_0050ef50(p3fes::EEContext&);
void fn_sub_50EFA8_0050efa8(p3fes::EEContext&);
void fn_sub_51F690_0051f690(p3fes::EEContext&);
void fn_unlink_00503988(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x004F90B8 checkModelVersion -- 160 bytes; frame 0x140: s2 sp+0x120, ra sp+0x130, s1 sp+0x110, s0 sp+0x100
// [libgraph] Is the console's ROM newer than 2001-06-08? Opens "rom0:ROMVER" through sceOpen (an IOP file request; the
// pair tests stand sceOpen / sceRead / sceClose in), reads it byte by byte with sceRead into a 256-byte stack buffer
// (sp+0..0xFF) until a NUL or 256 bytes, closes it, and runs atoi on the 8 characters that end 9 bytes before the stop
// (ROMVER = "0230AC20080220..": the date field). Returns 1 when that number is > 20010608 (0x1315670), 0 when not, -1
// when the open failed. Only sceGsSetDefDispEnv asks: newer ROMs report a DX / DY display offset.
void checkModelVersion(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f90b8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    a0 = 0x7C0000;
    sd(s2, sp, 0x120);
    a1 = 1;
    sd(ra, sp, 0x130);
    a0 = addiu(a0, -12176);  // "rom0:ROMVER"
    sd(s1, sp, 0x110);
    link(ctx, 0x4F90D4u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x100);
    call(ctx, gen::fn_sceOpen_00508670);
    s2 = v0;
    s1 = 0;
    if (i64(s2) >= 0) {
        // 0x004f90f0
        charge(ctx, 2);
        s0 = sp;
        for (;;) {
            // 0x004f90fc
            charge(ctx, 3);
            v0 = sltiu(s1, 256);
            a1 = s0;
            if (v0 != 0) {
                // 0x004f9108
                charge(ctx, 6);
                a0 = s2;
                a2 = 1;
                jal(ctx, 0x4F910Cu, gen::fn_sceRead_00508cb8);
                lb(v1, s0, 0);
                s0 = addiu(s0, 1);
                if (v1 != 0) {
                    backedge(ctx);
                    // 0x004f90f8
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                    continue;
                }
            }
            break;
        }
        // 0x004f9120
        charge(ctx, 8);
        a0 = s2;
        jal(ctx, 0x4F9120u, gen::fn_sceClose_00508900);
        a0 = addiu(s1, -9);
        a0 = addu(sp, a0);
        jal(ctx, 0x4F912Cu, gen::fn_atoi_0051e0f0);
        v1 = 0x1310000;
        v1 = v1 | 0x5670;  // &0x1315670
        v0 = slt(v1, v0);
    } else {
        // 0x004f90e8
        charge(ctx, 2);
        v0 = si(-1);
    }
    // 0x004f9140 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x130);
    ld(s2, sp, 0x120);
    ld(s1, sp, 0x110);
    ld(s0, sp, 0x100);
    sp = addiu(sp, 0x140);
}

// 0x004F9168 sceGsSetDefDispEnv -- 884 bytes; frame 0x90: s6 sp+0x70, s5 sp+0x60, s4 sp+0x50, s3 sp+0x40, s2 sp+0x30, s0 sp+0x10, s1 sp+0x20, ra sp+0x80
// [libgraph] Fills a display environment (sce::disp::, 5 GS privileged-register images, 40 bytes) for the current video
// mode from sceGsGetGParam (sce::gparam:: at 0x77F280). Arguments (each taken as an s16): $a0 env, $a1 PSM, $a2 width,
// $a3 height, $t0 DX, $t1 DY (offsets added to the mode's own origin).
//   PMODE   = 0x66 (EN2 = 1: read circuit 2; CRTMD = 1; MMOD = 1, AMOD = 1: fixed alpha, ALP = 0);
//   SMODE2  = INT | FFMD << 1: 2 when gparam.interlace = 0, else 3 when gparam.ffmode != 0, else 1;
//   DISPFB  = FBW (width + 63) / 64 at bit 9, PSM (4 bits) at bit 15, FBP / DBX / DBY 0;
//   DISPLAY = DX bits 0-11, DY 12-22, MAGH 23-26, MAGV 27-28 (0), DW 32-43, DH 44-54. NTSC (omode 2) / PAL (3):
//             MAGH + 1 = (width + 2559) / width (div; 2560 VCK per line), DW = (MAGH + 1) * width - 1, DX = 636 / 656
//             + DX * (MAGH + 1) (mult1: the pipeline-1 multiplier), DY = DY + 50 / 72 interlaced (DH = 2 * height - 1
//             when ffmode != 0, height - 1 otherwise) or + 25 / 36 progressive (DH = height - 1). 480p (0x50): MAGH 1,
//             DW = 2 * width - 1, DH = height - 1, DX = 2 * ((720 - width) / 2) + 2 * DX + 232, DY = DY + 35;
//   BGCOLOR = 0.
// The four words at sp+0 are mode-specific origin corrections added to DX / DY: 0 for NTSC and PAL; for other modes
// _sce_GetGsDxDyOffset (a kernel call, kept recompiled) writes them when checkModelVersion says the ROM is newer than
// 2001-06-08. An unknown mode prints "sceGsDefDispEnv:Not support displaymode for 0x%x!!" through scePrintf and leaves
// DISPLAY as it was. width = 0 runs into the div's divide-by-zero break (brk 7), in both bodies alike.
void sceGsSetDefDispEnv(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004f9168
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    a1 = sll(a1, 16);
    sd(s6, sp, 0x70);
    a2 = sll(a2, 16);
    sd(s5, sp, 0x60);
    a3 = sll(a3, 16);
    sd(s4, sp, 0x50);
    t0 = sll(t0, 16);
    sd(s3, sp, 0x40);
    t1 = sll(t1, 16);
    sd(s2, sp, 0x30);
    s6 = sra(a1, 16);
    sd(s0, sp, 0x10);
    s2 = sra(a3, 16);
    sd(s1, sp, 0x20);
    s0 = sra(a2, 16);
    sd(ra, sp, 0x80);
    s5 = sra(t0, 16);
    s4 = sra(t1, 16);
    s3 = a0;
    jal(ctx, 0x4F91B4u, gen::fn_sceGsGetGParam_004f9040);
    s1 = v0;
    lhu(a0, s1, sce::gparam::kOmode);
    v0 = addiu(a0, -2);
    v0 = sltiu(v0, 2);
    if (v0 != 0) {
        sw(zero, sp, 0xC);
    } else {
        // 0x004f91d4
        charge(ctx, 4);
        jal(ctx, 0x4F91D4u, gen::fn_checkModelVersion_004f90b8);
        a1 = sp;
        if (v0 == 0) {
            // 0x004f9200
            charge(ctx, 2);
            lhu(a0, s1, sce::gparam::kOmode);
            sw(zero, sp, 0xC);
            goto L_004f9208;
        }
        // 0x004f91e4
        charge(ctx, 7);
        lh(a0, s1, sce::gparam::kOmode);
        a2 = sp | 0x4;
        a3 = sp | 0x8;
        t0 = sp | 0xC;
        jal(ctx, 0x4F91F0u, gen::fn__sce_GetGsDxDyOffset_004f9158);
        lhu(a0, s1, sce::gparam::kOmode);
        goto L_004f9214;
    }
L_004f9208:
    charge(ctx, 3);
    sw(zero, sp, 0x8);
    sw(zero, sp, 0x4);
    sw(zero, sp, 0x0);
L_004f9214:
    charge(ctx, 6);
    v1 = 102;
    lhu(a2, s1, sce::gparam::kInterlace);
    sd(v1, s3, sce::disp::kPmode);
    lh(v0, s1, sce::gparam::kInterlace);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 2;
    if (!cc) {
        // 0x004f922c
        charge(ctx, 3);
        lh(v0, s1, sce::gparam::kFfmode);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 3;
        if (!cc) {
            // 0x004f9238
            charge(ctx, 1);
            v0 = 1;
        }
    }
    // 0x004f923c
    charge(ctx, 13);
    sd(v0, s3, sce::disp::kSmode2);
    v0 = addiu(s0, 63);
    v1 = s6 & 0xF;
    v0 = sra(v0, 6);
    a0 = sll(a0, 16);
    v0 = v0 & 0x3F;
    v1 = dsll(v1, 15);
    v0 = dsll(v0, 9);
    a1 = sra(a0, 16);
    v1 = v1 | v0;
    a0 = 2;
    sd(v1, s3, sce::disp::kDispfb);
    if (a1 == a0) {
        // 0x004f9270
        charge(ctx, 5);
        v0 = sll(a2, 16);
        v1 = 1;
        v0 = sra(v0, 16);
        cc = v0 != v1;  // the condition, before the delay slot changes it
        v0 = addiu(s0, 2559);
        if (cc) {
            // 0x004f92ec
            charge(ctx, 2);
            if (s0 == 0) {
                brk(ctx, 0x4F92F0u, 0x7u);
            }
            // 0x004f92f4
            charge(ctx, 9);
            div(v0, s0);
            a3 = addiu(s2, -1);
            lw(a1, sp, 0x0);
            a3 = dsll32(a3, 12);
            lw(v1, sp, 0x4);
            a1 = daddiu(a1, 636);
            v1 = addu(s4, v1);
            v1 = addiu(v1, 25);
            goto L_004f93e8;
        }
        // 0x004f9284
        charge(ctx, 3);
        v1 = addiu(s0, 2559);
        if (s0 == 0) {
            brk(ctx, 0x4F928Cu, 0x7u);
        }
        // 0x004f9290
        charge(ctx, 19);
        div(v1, s0);
        lw(v0, sp, 0x4);
        lw(a1, sp, 0x0);
        v0 = addu(s4, v0);
        lh(a2, s1, sce::gparam::kFfmode);
        v0 = addiu(v0, 50);
        a1 = daddiu(a1, 636);
        v0 = v0 & 0xFFF;
        a3 = dsll(v0, 12);
        mflo(v1);
        mult(a0, v1, s0);
        mult1(v0, s5, v1);
        v1 = addiu(v1, -1);
        t2 = dsll(v1, 23);
        a0 = addiu(a0, -1);
        v1 = dsll32(a0, 0);
        a1 = v0 + a1;
        a1 = a1 & 0xFFF;
        if (a2 == 0) {
            goto L_004f93a0;
        }
        // 0x004f92dc
        charge(ctx, 4);
        v0 = sll(s2, 1);
        v1 = t2 | v1;
        v0 = addiu(v0, -1);
        goto L_004f93a8;
    }
    // 0x004f9318
    charge(ctx, 3);
    v0 = 3;
    cc = a1 != v0;  // the condition, before the delay slot changes it
    v0 = 80;
    if (cc) {
        // 0x004f942c
        charge(ctx, 2);
        a0 = 0x7C0000;
        if (a1 != v0) {
            // 0x004f94a8
            charge(ctx, 2);
            a0 = addiu(a0, -12160);
            jal(ctx, 0x4F94A8u, gen::fn_scePrintf_00505e48);
        } else {
            // 0x004f9434
            charge(ctx, 29);
            v0 = 720;
            lw(a1, sp, 0x0);
            v0 = subu(v0, s0);
            a2 = sll(s5, 1);
            v1 = srl(v0, 31);
            lw(a0, sp, 0x4);
            v0 = addu(v0, v1);
            a3 = daddiu(a2, 232);
            v0 = sra(v0, 1);
            a2 = sll(s0, 1);
            v0 = sll(v0, 1);
            a0 = addu(s4, a0);
            a1 = v0 + a1;
            v1 = addiu(s2, -1);
            a1 = a1 + a3;
            a2 = addiu(a2, -1);
            v1 = dsll32(v1, 12);
            a2 = dsll32(a2, 0);
            a1 = a1 & 0xFFF;
            a0 = addiu(a0, 35);
            v0 = 0x800000;
            v1 = v1 | a2;
            a1 = a1 | v0;
            a0 = a0 & 0xFFF;
            v1 = v1 | a1;
            a0 = dsll(a0, 12);
            v1 = v1 | a0;
            sd(v1, s3, sce::disp::kDisplay);
        }
    } else {
        // 0x004f9324
        charge(ctx, 5);
        v0 = sll(a2, 16);
        v1 = 1;
        v0 = sra(v0, 16);
        cc = v0 != v1;  // the condition, before the delay slot changes it
        v0 = addiu(s0, 2559);
        if (cc) {
            // 0x004f93c0
            charge(ctx, 2);
            if (s0 == 0) {
                brk(ctx, 0x4F93C4u, 0x7u);
            }
            // 0x004f93c8
            charge(ctx, 8);
            div(v0, s0);
            a3 = addiu(s2, -1);
            lw(a1, sp, 0x0);
            a3 = dsll32(a3, 12);
            lw(v1, sp, 0x4);
            a1 = daddiu(a1, 656);
            v1 = addu(s4, v1);
            v1 = addiu(v1, 36);
        L_004f93e8:
            charge(ctx, 17);
            v1 = v1 & 0xFFF;
            v1 = dsll(v1, 12);
            mflo(v0);
            mult(a2, s5, v0);
            mult1(a0, v0, s0);
            v0 = addiu(v0, -1);
            a1 = a2 + a1;
            v0 = dsll(v0, 23);
            a1 = a1 & 0xFFF;
            a0 = addiu(a0, -1);
            a1 = a1 | a3;
            a0 = dsll32(a0, 0);
            v0 = v0 | a0;
            v0 = v0 | a1;
            v0 = v0 | v1;
            sd(v0, s3, sce::disp::kDisplay);
        } else {
            // 0x004f9338
            charge(ctx, 3);
            v1 = addiu(s0, 2559);
            if (s0 == 0) {
                brk(ctx, 0x4F9340u, 0x7u);
            }
            // 0x004f9344
            charge(ctx, 19);
            div(v1, s0);
            lw(v0, sp, 0x4);
            lw(a1, sp, 0x0);
            v0 = addu(s4, v0);
            lh(a2, s1, sce::gparam::kFfmode);
            v0 = addiu(v0, 72);
            a1 = daddiu(a1, 656);
            v0 = v0 & 0xFFF;
            a3 = dsll(v0, 12);
            mflo(v1);
            mult(a0, v1, s0);
            mult1(v0, s5, v1);
            v1 = addiu(v1, -1);
            t2 = dsll(v1, 23);
            a0 = addiu(a0, -1);
            v1 = dsll32(a0, 0);
            a1 = v0 + a1;
            a1 = a1 & 0xFFF;
            if (a2 == 0) {
            L_004f93a0:
                charge(ctx, 2);
                v0 = addiu(s2, -1);
                v1 = t2 | v1;
            } else {
                // 0x004f9390
                charge(ctx, 4);
                v0 = sll(s2, 1);
                v1 = t2 | v1;
                v0 = addiu(v0, -1);
            }
        L_004f93a8:
            charge(ctx, 6);
            v0 = dsll32(v0, 12);
            v0 = a1 | v0;
            v1 = v1 | v0;
            v0 = v1 | a3;
            sd(v0, s3, sce::disp::kDisplay);
        }
    }
    // 0x004f94b0 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    sd(zero, s3, sce::disp::kBgcolor);
    ld(ra, sp, 0x80);
    ld(s6, sp, 0x70);
    ld(s5, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x90);
}

// 0x004F95A0 sceGszbufaddr -- 200 bytes; frame 0x40: s1 sp+0x10, s0 sp+0x0, s2 sp+0x20, ra sp+0x30
// [libgraph] The Z-buffer page right after a frame buffer: pages(width, height) = ((width + 63) / 64) * ((height +
// 31) / 32) for 32-bit pixels, or ((height + 63) / 64) when bit 1 of $a0 (the PSM argument: a 16-bit format) is set
// (a GS page is 64 x 32 pixels at 32 bpp, 64 x 64 at 16 bpp); doubled (the Z buffer after two frame buffers) unless gparam
// says interlaced field mode (interlace = 1, ffmode = 0). Signed rounding as the instructions do it
// (bltz on width + 63). Returns the page number as an s16 (sll 16 / sra 16) in $v0.
void sceGszbufaddr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004f95a0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a2 = sll(a2, 16);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    s1 = sll(a0, 16);
    sd(s2, sp, 0x20);
    s0 = sll(a1, 16);
    s0 = sra(s0, 16);
    s1 = sra(s1, 16);
    sd(ra, sp, 0x30);
    s2 = sra(a2, 16);
    jal(ctx, 0x4F95C8u, gen::fn_sceGsGetGParam_004f9040);
    v1 = addiu(s0, 63);
    a1 = v0;
    a0 = si(-1);
    s0 = addiu(s0, 126);
    v0 = slt(a0, v1);
    s1 = s1 & 0x2;
    if (v0 != 0) s0 = v1;
    s0 = sra(s0, 6);
    if (s1 == 0) {
        // 0x004f960c
        charge(ctx, 5);
        v0 = addiu(s2, 31);
        v1 = addiu(s2, 62);
        a0 = slt(a0, v0);
        if (a0 != 0) v1 = v0;
        a2 = sra(v1, 5);
    } else {
        // 0x004f95f4
        charge(ctx, 6);
        v0 = addiu(s2, 63);
        v1 = addiu(s2, 126);
        a0 = slt(a0, v0);
        if (a0 != 0) v1 = v0;
        a2 = sra(v1, 6);
    }
    // 0x004f9620
    charge(ctx, 8);
    ld(v0, a1, 0);
    v1 = 0xFFFF;
    v1 = dsll32(v1, 0);
    v1 = v1 | 0xFFFF;
    a0 = 1;
    v0 = v0 & v1;
    cc = v0 != a0;  // the condition, before the delay slot changes it
    mult(v0, s0, a2);
    if (cc) {
        // 0x004f9648
        charge(ctx, 1);
        v0 = sll(v0, 17);
    } else {
        // 0x004f9640
        charge(ctx, 2);
        v0 = sll(v0, 16);
    }
    // 0x004f964c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = sra(v0, 16);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004F9668 sceGsSetDefDrawEnv -- 484 bytes; frame 0x70: s2 sp+0x20, s4 sp+0x40, s0 sp+0x0, s5 sp+0x50, s3 sp+0x30, s1 sp+0x10, ra sp+0x60
// [libgraph] Fills draw environment 1 (sce::draw:: -- 8 A+D pairs {data, GS register address}, 128 bytes, the payload
// of a GIF A+D packet) for a width x height frame buffer at page 0: $a0 env, $a1 PSM, $a2 width, $a3 height, $t0 Z test
// (0 = Z off), $t1 Z PSM. Register images (GS manual, general-purpose registers):
//   FRAME_1 (0x4C)    = FBP 0, FBW (width + 63) / 64 << 16, PSM << 24;
//   ZBUF_1 (0x4E)     = ZBP sceGszbufaddr(psm, width, height), PSM (Z) << 24, ZMSK (bit 32) set when Z test is 0;
//   XYOFFSET_1 (0x18) = OFX (2048 - width / 2) << 4, OFY (2048 - height / 2) << 4 at bit 32 (12.4 fixed point);
//   SCISSOR_1 (0x40)  = X0 0, X1 width - 1, Y0 0, Y1 height - 1 at bit 48;
//   PRMODECONT (0x1A) = old | 1 (AC = 1: PRIM register attributes); COLCLAMP (0x46) = old | 1 (CLAMP);
//   DTHE (0x45)       = dither on (bit 0) for a 16-bit PSM (bit 1 of $a1), off otherwise -- the other bits are kept;
//   TEST_1 (0x47)     = ZTE 1 (bit 16) with ZTST = ztest & 3 (bits 17-18), or 0x30000 (ZTST 1, always) when ztest is 0.
// Returns 8 (the number of A+D pairs), after a sync.
void sceGsSetDefDrawEnv(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f9668
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    a2 = sll(a2, 16);
    sd(s2, sp, 0x20);
    a1 = sll(a1, 16);
    s2 = sra(a2, 16);
    sd(s4, sp, 0x40);
    v0 = addiu(s2, 63);
    s4 = sra(a1, 16);
    v0 = sra(v0, 6);
    v1 = s4 & 0xF;
    v0 = v0 & 0x3F;
    sd(s0, sp, 0x0);
    v1 = dsll(v1, 24);
    v0 = dsll(v0, 16);
    s0 = a0;
    v0 = v0 | v1;
    sd(s5, sp, 0x50);
    a3 = sll(a3, 16);
    sd(s3, sp, 0x30);
    t0 = sll(t0, 16);
    sd(s1, sp, 0x10);
    t1 = sll(t1, 16);
    sd(ra, sp, 0x60);
    v1 = 76;
    a0 = 78;
    s1 = sra(a3, 16);
    s5 = sra(t0, 16);
    s3 = sra(t1, 16);
    sd(v1, s0, sce::draw::kFrame + sce::draw::kAddrOff);
    sd(v0, s0, sce::draw::kFrame);
    sd(a0, s0, sce::draw::kZbuf + sce::draw::kAddrOff);
    if (s5 != 0) {
        // 0x004f971c
        charge(ctx, 9);
        a0 = s4;
        a1 = s2;
        a2 = s1;
        jal(ctx, 0x4F9724u, gen::fn_sceGszbufaddr_004f95a0);
        v0 = dsll32(v0, 16);
        v1 = s3 & 0xF;
        v0 = dsra32(v0, 16);
        v1 = dsll(v1, 24);
        v0 = v0 | v1;
    } else {
        // 0x004f96e8
        charge(ctx, 13);
        a0 = s4;
        a1 = s2;
        a2 = s1;
        jal(ctx, 0x4F96F0u, gen::fn_sceGszbufaddr_004f95a0);
        v0 = dsll32(v0, 16);
        v1 = s3 & 0xF;
        v0 = dsra32(v0, 16);
        v1 = dsll(v1, 24);
        v0 = v0 | v1;
        a0 = 0x8000;
        a0 = dsll(a0, 17);
        v0 = v0 | a0;
    }
    // 0x004f9740
    charge(ctx, 39);
    sd(v0, s0, sce::draw::kZbuf);
    v0 = sra(s1, 1);
    v1 = sra(s2, 1);
    v0 = dsll32(v0, 16);
    a0 = 2048;
    v1 = dsll32(v1, 16);
    v0 = dsra32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = a0 - v0;
    a0 = a0 - v1;
    v0 = dsll32(v0, 4);
    a2 = addiu(s2, -1);
    a1 = addiu(s1, -1);
    a0 = dsll(a0, 4);
    ld(v1, s0, sce::draw::kPrmodecont);
    ld(a3, s0, sce::draw::kColclamp);
    a1 = dsll32(a1, 16);
    a0 = a0 | v0;
    a2 = dsll(a2, 16);
    t3 = 1;
    a2 = a2 | a1;
    v0 = 24;
    v1 = v1 | t3;
    a3 = a3 | t3;
    a1 = 64;
    t0 = 26;
    t1 = 70;
    t2 = 69;
    sd(v0, s0, sce::draw::kXyoffset + sce::draw::kAddrOff);
    sd(a0, s0, sce::draw::kXyoffset);
    v0 = s4 & 0x2;
    sd(a1, s0, sce::draw::kScissor + sce::draw::kAddrOff);
    sd(a2, s0, sce::draw::kScissor);
    sd(t0, s0, sce::draw::kPrmodecont + sce::draw::kAddrOff);
    sd(v1, s0, sce::draw::kPrmodecont);
    sd(t1, s0, sce::draw::kColclamp + sce::draw::kAddrOff);
    sd(a3, s0, sce::draw::kColclamp);
    sd(t2, s0, sce::draw::kDthe + sce::draw::kAddrOff);
    if (v0 == 0) {
        // 0x004f97e8
        charge(ctx, 3);
        ld(v0, s0, sce::draw::kDthe);
        v1 = si(-2);
        v0 = v0 & v1;
    } else {
        // 0x004f97dc
        charge(ctx, 3);
        ld(v0, s0, sce::draw::kDthe);
        v0 = v0 | t3;
    }
    // 0x004f97f4
    charge(ctx, 4);
    sd(v0, s0, sce::draw::kDthe);
    v0 = 71;
    sd(v0, s0, sce::draw::kTest + sce::draw::kAddrOff);
    if (s5 == 0) {
        // 0x004f9818
        charge(ctx, 1);
        v0 = 0x30000;
    } else {
        // 0x004f9804
        charge(ctx, 5);
        v0 = s5 & 0x3;
        v1 = 0x10000;
        v0 = dsll(v0, 17);
        v0 = v0 | v1;
    }
    // 0x004f981c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    sd(v0, s0, sce::draw::kTest);
    sync(ctx, 0);
    ld(ra, sp, 0x60);
    v0 = 8;
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x004F9CE8 sceGsSetDefStoreImage -- 320 bytes; frame 0x10: s0 sp+0x0
// [libgraph] Builds the VIF1 / GIF packet that reads a GS rectangle back to memory (sce::store::, 112 bytes): $a0 packet,
// $a1 SBP (source base, 64-word units), $a2 SBW, $a3 SPSM, $t0 X, $t1 Y, $t2 width, $t3 height.
//   +0  VIF NOP; +4 MSKPATH3 (0x06008000: mask PATH3); +8 FLUSHA (0x13000000); +12 DIRECT 6 qwords (0x50000006);
//   +16 GIF tag: NLOOP 5, EOP 1, FLG PACKED, NREG 1 (the low 64 bits cleared by a 128-bit store first, then OR-ed),
//       REGS = 0xE (A+D);
//   +32 BITBLTBUF (0x50) = SBP | SBW << 16 | SPSM << 24 (the source half: GS -> host);
//   +48 TRXPOS (0x51)    = SSAX | SSAY << 16; +64 TRXREG (0x52) = RRW | RRH << 32;
//   +80 FINISH (0x61)    = 0; +96 TRXDIR (0x53) = 1 (local -> host).
// Returns 7, after a sync. sceGsExecStoreImage (kept recompiled: DMA channels and GS registers) sends it.
void sceGsSetDefStoreImage(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, sp{ctx, 29};
    // 0x004f9ce8
    enter(ctx, 80);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    por(v0, zero, zero);
    sd(s0, sp, 0x0);
    a1 = sll(a1, 16);
    sq(v0, a0, sce::store::kGifTag);
    a1 = sra(a1, 16);
    v0 = si(-32768);
    a3 = sll(a3, 16);
    ld(t4, a0, sce::store::kGifTag);
    t0 = sll(t0, 16);
    t2 = sll(t2, 16);
    t3 = sll(t3, 16);
    t4 = t4 & v0;
    ld(t5, a0, sce::store::kGifTag + 8);
    v0 = 5;
    a3 = sra(a3, 16);
    t4 = t4 | v0;
    t0 = sra(t0, 16);
    v0 = 0x8000;
    t2 = sra(t2, 16);
    t4 = t4 | v0;
    t3 = sra(t3, 16);
    v0 = si(-1);
    v0 = dsrl(v0, 4);
    a1 = dsll32(a1, 16);
    a2 = sll(a2, 16);
    v1 = si(-16);
    t4 = t4 & v0;
    a1 = dsra32(a1, 16);
    a3 = dsll32(a3, 16);
    t0 = dsll32(t0, 16);
    t2 = dsll32(t2, 16);
    t3 = dsll32(t3, 16);
    t5 = t5 & v1;
    a1 = a2 | a1;
    t1 = sll(t1, 16);
    a3 = dsra(a3, 24);
    t3 = dsra(t3, 16);
    v0 = 0x8000;
    v0 = dsll32(v0, 13);
    t6 = 14;
    t0 = dsra32(t0, 16);
    t2 = dsra32(t2, 16);
    a1 = a1 | a3;
    t0 = t1 | t0;
    t2 = t2 | t3;
    t4 = t4 | v0;
    t5 = t5 | t6;
    v1 = 0x6000000;
    a2 = 0x50000000;
    v1 = v1 | 0x8000;
    a3 = 0x13000000;
    a2 = a2 | 0x6;
    t1 = 80;
    t3 = 81;
    t6 = 82;
    t7 = 97;
    s0 = 1;
    v0 = 83;
    sw(v1, a0, sce::store::kVifMskpath3);
    sd(v0, a0, sce::store::kTrxdir + 8);
    sw(a3, a0, sce::store::kVifFlusha);
    sw(a2, a0, sce::store::kVifDirect);
    sd(t4, a0, sce::store::kGifTag);
    sd(t5, a0, sce::store::kGifTag + 8);
    sd(a1, a0, sce::store::kBitbltbuf);
    sd(t1, a0, sce::store::kBitbltbuf + 8);
    sd(t0, a0, sce::store::kTrxpos);
    sd(t3, a0, sce::store::kTrxpos + 8);
    sd(t2, a0, sce::store::kTrxreg);
    sd(t6, a0, sce::store::kTrxreg + 8);
    sd(t7, a0, sce::store::kFinish + 8);
    sd(s0, a0, sce::store::kTrxdir);
    sw(zero, a0, sce::store::kVifNop);
    sd(zero, a0, sce::store::kFinish);
    sync(ctx, 0);
    ld(s0, sp, 0x0);
    v0 = 7;
    sp = addiu(sp, 0x10);
}

// 0x004FA558 sceGsSetDefDrawEnv2 -- 480 bytes; frame 0x70: s2 sp+0x20, s4 sp+0x40, s0 sp+0x0, s5 sp+0x50, s3 sp+0x30, s1 sp+0x10, ra sp+0x60
// [libgraph] The context-2 twin of sceGsSetDefDrawEnv (same arguments and layout): FRAME_2 (0x4D), ZBUF_2 (0x4F),
// XYOFFSET_2 (0x19), SCISSOR_2 (0x41), PRMODECONT / COLCLAMP / DTHE as for context 1, TEST_2 (0x48). One instruction
// differs besides the addresses: FBW is (width >> 6) here (no + 63 rounding; sra 22 of the shifted width). Returns 8.
void sceGsSetDefDrawEnv2(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fa558
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    a2 = sll(a2, 16);
    sd(s2, sp, 0x20);
    a1 = sll(a1, 16);
    sd(s4, sp, 0x40);
    s2 = sra(a2, 16);
    s4 = sra(a1, 16);
    a2 = sra(a2, 22);
    v0 = s4 & 0xF;
    a2 = a2 & 0x3F;
    v0 = dsll(v0, 24);
    a2 = dsll(a2, 16);
    sd(s0, sp, 0x0);
    a2 = a2 | v0;
    sd(s5, sp, 0x50);
    s0 = a0;
    sd(s3, sp, 0x30);
    a3 = sll(a3, 16);
    sd(s1, sp, 0x10);
    t0 = sll(t0, 16);
    sd(ra, sp, 0x60);
    t1 = sll(t1, 16);
    v0 = 77;
    v1 = 79;
    s1 = sra(a3, 16);
    s5 = sra(t0, 16);
    s3 = sra(t1, 16);
    sd(v0, s0, sce::draw::kFrame + sce::draw::kAddrOff);
    sd(a2, s0, sce::draw::kFrame);
    sd(v1, s0, sce::draw::kZbuf + sce::draw::kAddrOff);
    if (s5 != 0) {
        // 0x004fa608
        charge(ctx, 9);
        a0 = s4;
        a1 = s2;
        a2 = s1;
        jal(ctx, 0x4FA610u, gen::fn_sceGszbufaddr_004f95a0);
        v0 = dsll32(v0, 16);
        v1 = s3 & 0xF;
        v0 = dsra32(v0, 16);
        v1 = dsll(v1, 24);
        v0 = v0 | v1;
    } else {
        // 0x004fa5d4
        charge(ctx, 13);
        a0 = s4;
        a1 = s2;
        a2 = s1;
        jal(ctx, 0x4FA5DCu, gen::fn_sceGszbufaddr_004f95a0);
        v0 = dsll32(v0, 16);
        v1 = s3 & 0xF;
        v0 = dsra32(v0, 16);
        v1 = dsll(v1, 24);
        v0 = v0 | v1;
        a0 = 0x8000;
        a0 = dsll(a0, 17);
        v0 = v0 | a0;
    }
    // 0x004fa62c
    charge(ctx, 39);
    sd(v0, s0, sce::draw::kZbuf);
    v0 = sra(s1, 1);
    v1 = sra(s2, 1);
    v0 = dsll32(v0, 16);
    a0 = 2048;
    v1 = dsll32(v1, 16);
    v0 = dsra32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = a0 - v0;
    a0 = a0 - v1;
    v0 = dsll32(v0, 4);
    a2 = addiu(s2, -1);
    a1 = addiu(s1, -1);
    a0 = dsll(a0, 4);
    ld(v1, s0, sce::draw::kPrmodecont);
    ld(a3, s0, sce::draw::kColclamp);
    a1 = dsll32(a1, 16);
    a0 = a0 | v0;
    a2 = dsll(a2, 16);
    t3 = 1;
    a2 = a2 | a1;
    v0 = 25;
    v1 = v1 | t3;
    a3 = a3 | t3;
    a1 = 65;
    t0 = 26;
    t1 = 70;
    t2 = 69;
    sd(v0, s0, sce::draw::kXyoffset + sce::draw::kAddrOff);
    sd(a0, s0, sce::draw::kXyoffset);
    v0 = s4 & 0x2;
    sd(a1, s0, sce::draw::kScissor + sce::draw::kAddrOff);
    sd(a2, s0, sce::draw::kScissor);
    sd(t0, s0, sce::draw::kPrmodecont + sce::draw::kAddrOff);
    sd(v1, s0, sce::draw::kPrmodecont);
    sd(t1, s0, sce::draw::kColclamp + sce::draw::kAddrOff);
    sd(a3, s0, sce::draw::kColclamp);
    sd(t2, s0, sce::draw::kDthe + sce::draw::kAddrOff);
    if (v0 == 0) {
        // 0x004fa6d4
        charge(ctx, 3);
        ld(v0, s0, sce::draw::kDthe);
        v1 = si(-2);
        v0 = v0 & v1;
    } else {
        // 0x004fa6c8
        charge(ctx, 3);
        ld(v0, s0, sce::draw::kDthe);
        v0 = v0 | t3;
    }
    // 0x004fa6e0
    charge(ctx, 4);
    sd(v0, s0, sce::draw::kDthe);
    v0 = 72;
    sd(v0, s0, sce::draw::kTest + sce::draw::kAddrOff);
    if (s5 == 0) {
        // 0x004fa704
        charge(ctx, 1);
        v0 = 0x30000;
    } else {
        // 0x004fa6f0
        charge(ctx, 5);
        v0 = s5 & 0x3;
        v1 = 0x10000;
        v0 = dsll(v0, 17);
        v0 = v0 | v1;
    }
    // 0x004fa708 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    sd(v0, s0, sce::draw::kTest);
    sync(ctx, 0);
    ld(ra, sp, 0x60);
    v0 = 8;
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x004FA890 CheckAddress -- 40 bytes; leaf frame (no stack)
// [libdma] Maps a scratchpad address for the DMA controller: an address in 0x70000000-0x7FFFFFFF becomes its offset with
// bit 31 set (0x80000000 | (addr & 0x0FFFFFFF): the SPR flag of the Dn_MADR / Dn_TADR registers, EE manual DMAC);
// anything else is returned unchanged (the whole 64-bit register: srl 28 tests the low word).
void CheckAddress(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fa890
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 7;
    v0 = srl(a0, 28);
    cc = v0 != v1;  // the condition, before the delay slot changes it
    v0 = 0xFFF0000;
    if (!cc) {
        // 0x004fa8a0
        charge(ctx, 4);
        v1 = lui(0x8000);
        v0 = v0 | 0xFFFF;
        a0 = a0 & v0;
        a0 = a0 | v1;
    }
    // 0x004fa8b0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
}

// 0x004FA8B8 memclr -- 52 bytes; leaf frame (no stack)
// [libdma] Clears $a1 bytes at $a0, one sb per byte (a counted loop on $v0 = n - 1 down to -1; n = 0 stores nothing).
// $v0 ends at -1 (or n - 1 for n = 0) -- callers do not read it, the register stays as the original leaves it.
void memclr(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004fa8b8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = addiu(a1, -1);
    if (a1 != 0) {
        // 0x004fa8c0
        charge(ctx, 2);
        v1 = si(-1);
        for (;;) {
            // 0x004fa8c8
            charge(ctx, 7);
            sb(zero, a0, 0);
            v0 = addiu(v0, -1);
            a0 = addiu(a0, 1);
            if (v0 == v1) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004fa8e4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004FABD0 sceDmaGetEnv -- 56 bytes; leaf frame (no stack)
// [libdma] Copies libdma's shadow of the DMAC environment (20 bytes at 0x965AC8: two doublewords and a word, last
// written by sceDmaPutEnv) to $a0 and returns $a0. Memory only: the hardware registers are not read.
void sceDmaGetEnv(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x004fabd0
    enter(ctx, 14);  // entry check point + this block's cycles
    v1 = 0x960000;
    t0 = addiu(v1, 23240);  // &0x965AC8
    ldl(a1, t0, 7);  // 0x965ACF
    ldr(a1, t0, 0);  // 0x965AC8
    ldl(a2, t0, 15);  // 0x965AD7
    ldr(a2, t0, 8);  // 0x965AD0
    lw(a3, t0, 16);  // 0x965AD8
    sdl(a1, a0, 7);
    sdr(a1, a0, 0);
    sdl(a2, a0, 15);
    sdr(a2, a0, 8);
    sw(a3, a0, 16);
    v0 = a0;
}

}  // namespace p3fes::game

// --- the recompiled entry points (dispatch, generated callers) run the bodies above ---
