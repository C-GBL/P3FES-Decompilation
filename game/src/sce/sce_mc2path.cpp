// Slice sce1 (sce_mc2path.cpp): libmc2's path and file-name helpers (pure string code, no card access).
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

// 0x00514D50 instr -- 92 bytes; leaf frame (no stack)
// [libmc2] The index of the first $a1 in the string $a0, or -1 (a NUL ends the search; searching for 0 finds the NUL).
void instr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00514d50
    enter(ctx, 6);  // entry check point + this block's cycles
    a1 = sll(a1, 24);
    lb(v1, a0, 0);
    lbu(v0, a0, 0);
    a1 = sra(a1, 24);
    a2 = a0;
    if (v1 != 0) {
        // 0x00514d68
        charge(ctx, 2);
        if (v1 == a1) {
            // 0x00514d9c (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = subu(a2, a0);
            return;
        }
        // 0x00514d70
        charge(ctx, 2);
        a2 = addiu(a2, 1);
        for (;;) {
            // 0x00514d78
            charge(ctx, 3);
            lb(v1, a2, 0);
            lbu(v0, a2, 0);
            if (v1 != 0) {
                // 0x00514d84
                charge(ctx, 2);
                if (v1 != a1) {
                    a2 = addiu(a2, 1);
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
        goto L_00514d8c;
    }
L_00514d8c:
    charge(ctx, 4);
    v0 = sll(v0, 24);
    v0 = sra(v0, 24);
    if (v0 != a1) {
        // 0x00514da4
        charge(ctx, 2);
        v0 = si(-1);
        return;
    }
    // 0x00514d9c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = subu(a2, a0);
}

// 0x00514DB0 isCorrNameSize -- 108 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// [libmc2] Is the last path element (after the last '/', or the whole name) shorter than 32 characters? 1 / 0.
void isCorrNameSize(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00514db0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 47;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x514DC0u, gen::fn_strchr_00523f98);
    a0 = s0;
    if (v0 == 0) {
        // 0x00514df4
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x514DF4u, gen::fn_strlen_00524388);
        v1 = sltiu(v0, 32);
        v0 = 0;
        if (v1 != 0) {
            // 0x00514e08
            charge(ctx, 1);
            v0 = 1;
        }
    } else {
        // 0x00514dd0
        charge(ctx, 7);
        a1 = 47;
        jal(ctx, 0x514DD0u, gen::fn_strrchr_005249e8);
        a0 = addiu(v0, 1);
        jal(ctx, 0x514DD8u, gen::fn_strlen_00524388);
        v0 = sltiu(v0, 32);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (!cc) {
            // 0x00514dec
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x00514e0c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00514E20 isCorrFname -- 84 bytes; leaf frame (no stack)
// [libmc2] Is the name free of wildcards and control characters? 0 at the first '?', '*' or byte < 0x20, else 1.
void isCorrFname(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00514e20
    enter(ctx, 3);  // entry check point + this block's cycles
    lb(v0, a0, 0);
    lbu(v1, a0, 0);
    if (v0 == 0) {
        // 0x00514e6c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 1;
        return;
    }
    // 0x00514e2c
    charge(ctx, 3);
    a2 = 63;
    a1 = 42;
    for (;;) {
        // 0x00514e38
        charge(ctx, 4);
        v0 = sll(v1, 24);
        v0 = sra(v0, 24);
        if (v0 == a2) {
            // 0x00514e58 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = 0;
            return;
        }
        // 0x00514e48
        charge(ctx, 2);
        cc = v0 == a1;  // the condition, before the delay slot changes it
        v0 = slti(v0, 32);
        if (cc) {
            // 0x00514e58 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = 0;
            return;
        }
        // 0x00514e50
        charge(ctx, 2);
        a0 = addiu(a0, 1);
        if (v0 != 0) {
            // 0x00514e58 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = 0;
            return;
        }
        // 0x00514e60
        charge(ctx, 3);
        lb(v0, a0, 0);
        lbu(v1, a0, 0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00514e6c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = 1;
}

// 0x00514E78 isPathCurParent -- 180 bytes; frame 0x40: s0 sp+0x20, ra sp+0x30
// [libmc2] Is the last path element (copied to a 32-byte stack buffer) neither "." (0x7BE5F0) nor ".." (0x7BE5F8)? 1 /
// 0; 0 too when the element is 32 characters or longer.
void isPathCurParent(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00514e78
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a1 = 47;
    sd(s0, sp, 0x20);
    sd(ra, sp, 0x30);
    s0 = a0;
    jal(ctx, 0x514E88u, gen::fn_strchr_00523f98);
    a0 = s0;
    if (v0 != 0) {
        // 0x00514e98
        charge(ctx, 7);
        a1 = 47;
        jal(ctx, 0x514E98u, gen::fn_strrchr_005249e8);
        a0 = addiu(v0, 1);
        jal(ctx, 0x514EA0u, gen::fn_strlen_00524388);
        v0 = sltiu(v0, 32);
        a0 = s0;
        if (v0 == 0) {
            goto L_00514f18;
        }
        // 0x00514eb4
        charge(ctx, 7);
        a1 = 47;
        jal(ctx, 0x514EB4u, gen::fn_strrchr_005249e8);
        a1 = addiu(v0, 1);
        a0 = sp;
        jal(ctx, 0x514EC0u, gen::fn_strcpy_00524270);
        a1 = 0x7C0000;
        goto L_00514ef0;
    }
    // 0x00514ed0
    charge(ctx, 5);
    a0 = s0;
    jal(ctx, 0x514ED0u, gen::fn_strlen_00524388);
    v0 = sltiu(v0, 32);
    a1 = s0;
    if (v0 == 0) {
    L_00514f18:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00514ee4
        charge(ctx, 3);
        a0 = sp;
        jal(ctx, 0x514EE4u, gen::fn_strcpy_00524270);
        a1 = 0x7C0000;
    L_00514ef0:
        charge(ctx, 5);
        a0 = sp;
        a1 = addiu(a1, -6672);
        jal(ctx, 0x514EF4u, gen::fn_strcmp_00524128);
        a1 = 0x7C0000;
        if (v0 == 0) {
            goto L_00514f18;
        }
        // 0x00514f04
        charge(ctx, 5);
        a0 = sp;
        a1 = addiu(a1, -6664);
        jal(ctx, 0x514F08u, gen::fn_strcmp_00524128);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (!cc) {
            goto L_00514f18;
        }
    }
    // 0x00514f1c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x40);
}

// 0x00514F30 isWildFit -- 384 bytes; frame 0x50: s3 sp+0x30, s1 sp+0x10, ra sp+0x40, s2 sp+0x20, s0 sp+0x0
// [libmc2] Does the name $a0 match the pattern $a1 ('?' one character, '*' any run)? Literal runs with strncmp, '?'
// steps, and for '*' a recursive try at every occurrence of the next literal character (instr). 1 / 0.
void isWildFit(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00514f30
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s3, sp, 0x30);
    sd(s1, sp, 0x10);
    s3 = a0;
    sd(ra, sp, 0x40);
    s1 = a1;
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x0);
    // 0x0051505c
    charge(ctx, 1);
    a0 = s1;
    for (;;) {
        // 0x00515060
        charge(ctx, 8);
        a1 = 63;
        jal(ctx, 0x515060u, gen::fn_instr_00514d50);
        s2 = v0;
        a0 = s1;
        a1 = 42;
        jal(ctx, 0x515070u, gen::fn_instr_00514d50);
        v1 = v0;
        if (i64(s2) >= 0) {
            backedge(ctx);
        } else {
            // 0x00515080
            charge(ctx, 2);
            a0 = s1;
            if (i64(v1) < 0) {
                goto L_00515088_24;
            }
            backedge(ctx);
            goto L_00514f58;
        }
    L_00514f58:
        charge(ctx, 2);
        s0 = v1;
        if (i64(s2) >= 0) {
            // 0x00514f60
            charge(ctx, 2);
            s0 = s2;
            if (i64(v1) >= 0) {
                // 0x00514f68
                charge(ctx, 2);
                v0 = slt(s2, v1);
                if (v0 == 0) s0 = v1;
            }
        }
        // 0x00514f70
        charge(ctx, 6);
        a0 = s1;
        a1 = s3;
        a2 = s0;
        jal(ctx, 0x514F78u, gen::fn_strncmp_00524670);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (cc) {
            break;
        }
        // 0x00514f88
        charge(ctx, 6);
        s1 = addu(s1, s0);
        s3 = addu(s3, s0);
        lb(v1, s1, 0);
        v0 = 63;
        lbu(a1, s1, 0);
        if (v1 == v0) {
            // 0x00514fa0
            charge(ctx, 2);
            v1 = 63;
            for (;;) {
                // 0x00514fa8
                charge(ctx, 3);
                lb(v0, s3, 0);
                s1 = addiu(s1, 1);
                if (v0 == 0) {
                    goto L_0051502c;
                }
                // 0x00514fb4
                charge(ctx, 4);
                s3 = addiu(s3, 1);
                lb(v0, s1, 0);
                lbu(a1, s1, 0);
                if (v0 != v1) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00514fc4
        charge(ctx, 5);
        v0 = sll(a1, 24);
        v1 = 42;
        v0 = sra(v0, 24);
        a0 = s1;
        if (v0 != v1) {
            continue;
        }
        goto L_00514fd8_10;
    }
    // 0x00515094 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_00514fd8_10:
    charge(ctx, 2);
    a0 = 42;
    v1 = 63;
    for (;;) {
    L_00514fe0:
        charge(ctx, 1);
        s1 = addiu(s1, 1);
        for (;;) {
            // 0x00514fe4
            charge(ctx, 6);
            lb(v0, s1, 0);
            lbu(a1, s1, 0);
            if (v0 == a0) {
                backedge(ctx);
                goto L_00514fe0;
            }
            // 0x00514ffc
            charge(ctx, 2);
            if (v0 != v1) {
                break;
            }
            s1 = addiu(s1, 1);
            backedge(ctx);
        }
        break;
    }
    // 0x00515004
    charge(ctx, 2);
    s2 = 1;
    if (v0 == 0) {
    L_0051502c:
        charge(ctx, 2);
        v0 = 1;
    } else {
        // 0x0051500c
        charge(ctx, 2);
        a1 = sll(a1, 24);
        for (;;) {
            // 0x0051503c
            charge(ctx, 6);
            a0 = s3;
            a1 = sra(a1, 24);
            jal(ctx, 0x515040u, gen::fn_instr_00514d50);
            s0 = v0;
            s3 = addu(s3, s0);
            if (i64(s0) < 0) {
                break;
            }
            backedge(ctx);
            // 0x00515018
            charge(ctx, 5);
            a1 = s1;
            a0 = s3;
            jal(ctx, 0x51501Cu, gen::fn_isWildFit_00514f30);
            if (v0 == s2) {
                goto L_0051502c;
            }
            lbu(a1, s1, 0);
            // 0x00515034
            charge(ctx, 2);
            s3 = addiu(s3, 1);
            a1 = sll(a1, 24);
        }
        // 0x00515054
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00515094 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_00515088_24:
    charge(ctx, 3);
    a1 = s3;
    jal(ctx, 0x515088u, gen::fn_strcmp_00524128);
    v0 = sltiu(v0, 1);
    // 0x00515094 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x005150B0 _strtok -- 288 bytes; frame 0x50: s1 sp+0x10, s0 sp+0x0, ra sp+0x40, s3 sp+0x30, s2 sp+0x20
// [libmc2] strtok over a private copy: a non-NULL $a0 is first copied (strcpy) to the buffer at 0x97B688; skips
// leading separators ($a1), takes a token up to the next separator -- or, after a '"', up to the closing quote (the set
// at 0x7BE600) -- NUL-terminates it and keeps the position at 0x97B680 (0 at the end of the string). Returns the token or
// NULL.
void _strtok(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005150b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    s1 = a1;
    sd(ra, sp, 0x40);
    s0 = a0;
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    if (s0 != 0) {
        // 0x005150d4
        charge(ctx, 8);
        v0 = 0x980000;
        a1 = s0;
        v0 = addiu(v0, -18808);  // &0x97B688
        a0 = v0;
        s0 = v0;
        jal(ctx, 0x5150E4u, gen::fn_strcpy_00524270);
        if (s0 == 0) {
            goto L_005150f4;
        }
        lb(v0, s0, 0);  // 0x97B688
    L_00515108:
        charge(ctx, 2);
        lbu(a1, s0, 0);
        if (v0 != 0) {
            for (;;) {
                // 0x00515124
                charge(ctx, 7);
                a1 = sll(a1, 24);
                s0 = addiu(s0, 1);
                a1 = sra(a1, 24);
                a0 = s1;
                jal(ctx, 0x515130u, gen::fn_strchr_00523f98);
                if (v0 == 0) {
                    goto L_00515140_9;
                }
                lb(v0, s0, -1);
                backedge(ctx);
                // 0x00515118
                charge(ctx, 2);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = 0;
                if (!cc) {
                    // 0x00515120
                    charge(ctx, 1);
                    lbu(a1, s0, 0);
                    continue;
                }
                break;
            }
        } else {
            // 0x00515110
            charge(ctx, 2);
            v0 = 0;
        }
        // 0x005151b4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x40);
        ld(s3, sp, 0x30);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_005150f4:
    charge(ctx, 4);
    s3 = 0x980000;
    lw(s0, s3, -18816);  // 0x97B680
    v0 = 0;
    if (s0 != 0) {
        // 0x00515104
        charge(ctx, 1);
        lb(v0, s0, 0);
        goto L_00515108;
    }
    // 0x005151b4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_00515140_9:
    charge(ctx, 4);
    lb(v1, s0, -1);
    v0 = 34;
    s2 = addiu(s0, -1);
    if (v1 != v0) {
        // 0x0051517c
        charge(ctx, 3);
        s3 = 0x980000;
        lb(a1, s0, 0);
        for (;;) {
            // 0x00515188
            charge(ctx, 5);
            a0 = s1;
            s0 = addiu(s0, 1);
            jal(ctx, 0x51518Cu, gen::fn_strchr_00523f98);
            if (v0 != 0) {
                break;
            }
            lb(a1, s0, 0);
            backedge(ctx);
        }
        // 0x0051519c
        charge(ctx, 1);
        lb(v0, s0, -1);
    } else {
        // 0x00515150
        charge(ctx, 4);
        s2 = s0;
        s3 = 0x980000;
        s1 = 0x7C0000;
        lb(a1, s0, 0);
        for (;;) {
            // 0x00515160
            charge(ctx, 5);
            a0 = addiu(s1, -6656);
            s0 = addiu(s0, 1);
            jal(ctx, 0x515164u, gen::fn_strchr_00523f98);
            if (v0 != 0) {
                break;
            }
            lb(a1, s0, 0);
            backedge(ctx);
        }
        // 0x00515174
        charge(ctx, 2);
        lb(v0, s0, -1);
    }
    // 0x005151a0
    charge(ctx, 2);
    if (v0 == 0) {
        sw(zero, s3, -18816);
    } else {
        // 0x005151a8
        charge(ctx, 1);
        sw(s0, s3, -18816);
    }
    // 0x005151ac
    charge(ctx, 2);
    sb(zero, s0, -1);
    v0 = s2;
    // 0x005151b4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x005151D0 _get_dir_nest -- 68 bytes; leaf frame (no stack)
// [libmc2] The number of '/' in the path $a0.
void _get_dir_nest(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x005151d0
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = a0;
    a2 = 0;
    lb(v0, a1, 0);
    lbu(v1, a1, 0);
    if (v0 != 0) {
        // 0x005151e4
        charge(ctx, 1);
        for (;;) {
            // 0x005151e8
            charge(ctx, 9);
            v0 = sll(v1, 24);
            a1 = addiu(a1, 1);
            v0 = sra(v0, 24);
            v1 = addiu(a2, 1);
            v0 = v0 ^ 0x2F;
            lb(a0, a1, 0);
            if (v0 == 0) a2 = v1;
            lbu(v1, a1, 0);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0051520c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a2;
}

// 0x00515218 _make_path -- 388 bytes; frame 0x50: s2 sp+0x20, s0 sp+0x0, s1 sp+0x10, ra sp+0x40, s3 sp+0x30
// [libmc2] Resolves $a1 against the current directory of port $a0 (the 2,200-byte per-port records at 0x97BF90) into $a2:
// an absolute path starts from "/", "." elements are skipped, ".." drops the last element (0 if there is none), others
// are appended with a '/'; the trailing '/' is removed unless the result is "/". 0 for paths of 128 characters or more,
// else 1.
void _make_path(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00515218
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x0);
    s2 = a0;
    sd(s1, sp, 0x10);
    s0 = a1;
    sd(ra, sp, 0x40);
    s1 = a2;
    sd(s3, sp, 0x30);
    a0 = s0;
    jal(ctx, 0x51523Cu, gen::fn_strlen_00524388);
    v0 = sltiu(v0, 128);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 2200;
    if (cc) {
        // 0x00515258
        charge(ctx, 10);
        a1 = 0x980000;
        mult(v0, s2, v0);
        a1 = addiu(a1, -16496);  // &0x97BF90
        a0 = s1;
        a1 = addu(v0, a1);
        jal(ctx, 0x515268u, gen::fn_strcpy_00524270);
        lb(v1, s0, 0);
        v0 = 47;
        s2 = 0x7C0000;
        if (v1 != v0) {
            // 0x005152a8
            charge(ctx, 4);
            a0 = s0;
            a1 = addiu(s2, -6648);
            jal(ctx, 0x5152ACu, gen::fn__strtok_005150b0);
            s0 = v0;
        } else {
            // 0x00515280
            charge(ctx, 10);
            a0 = addiu(s0, 1);
            a2 = addiu(s2, -6648);
            lb(v0, a2, 0);
            lb(v1, a2, 1);
            sb(v0, s1, 0);
            sb(v1, s1, 1);
            a1 = addiu(s2, -6648);
            jal(ctx, 0x515298u, gen::fn__strtok_005150b0);
            s0 = v0;
        }
        // 0x005152b8
        charge(ctx, 2);
        s3 = 0x7C0000;
        if (s0 != 0) {
            // 0x005152c0
            charge(ctx, 2);
            a0 = s0;
            for (;;) {
                // 0x005152c8
                charge(ctx, 4);
                a1 = addiu(s3, -6672);
                jal(ctx, 0x5152C8u, gen::fn_strcmp_00524128);
                a1 = 0x7C0000;
                if (v0 == 0) {
                    // 0x005152d8
                    charge(ctx, 3);
                    a0 = 0;
                    a1 = addiu(s2, -6648);
                    goto L_00515348;
                }
                // 0x005152e4
                charge(ctx, 5);
                a0 = s0;
                a1 = addiu(a1, -6664);
                jal(ctx, 0x5152E8u, gen::fn_strcmp_00524128);
                a1 = s0;
                if (v0 == 0) {
                    // 0x005152f8
                    charge(ctx, 9);
                    a0 = s1;
                    jal(ctx, 0x5152F8u, gen::fn_strlen_00524388);
                    v0 = addu(v0, s1);
                    a0 = s1;
                    sb(zero, v0, -1);
                    a1 = 47;
                    jal(ctx, 0x51530Cu, gen::fn_strrchr_005249e8);
                    a0 = 0;
                    if (v0 == 0) {
                        backedge(ctx);
                        goto L_00515250;
                    }
                    // 0x0051531c
                    charge(ctx, 3);
                    sb(zero, v0, 1);
                    a1 = addiu(s2, -6648);
                    goto L_00515348;
                }
                // 0x00515328
                charge(ctx, 8);
                a0 = s1;
                jal(ctx, 0x515328u, gen::fn_strcat_00523e68);
                s0 = addiu(s2, -6648);
                a1 = s0;
                a0 = s1;
                jal(ctx, 0x515338u, gen::fn_strcat_00523e68);
                a1 = s0;
                a0 = 0;
            L_00515348:
                charge(ctx, 5);
                jal(ctx, 0x515348u, gen::fn__strtok_005150b0);
                s0 = v0;
                a0 = s0;
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0051535c
        charge(ctx, 5);
        a1 = addiu(s2, -6648);
        a0 = s1;
        jal(ctx, 0x515360u, gen::fn_strcmp_00524128);
        a0 = s1;
        if (v0 != 0) {
            // 0x00515370
            charge(ctx, 3);
            a1 = 47;
            jal(ctx, 0x515370u, gen::fn_strrchr_005249e8);
            sb(zero, v0, 0);
        }
        // 0x0051537c
        charge(ctx, 1);
        v0 = 1;
        // 0x00515380 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x40);
        ld(s3, sp, 0x30);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_00515250:
    charge(ctx, 2);
    v0 = 0;
    // 0x00515380 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

}  // namespace p3fes::game

// --- the recompiled entry points (dispatch, generated callers) run the bodies above ---
