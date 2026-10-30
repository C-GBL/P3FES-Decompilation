// Slice sce1 (sce_kernel.cpp): libkernel's newlib glue, SIF bookkeeping tables, the alarm pool and the module-version checks.
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

// 0x00503820 open -- 40 bytes; frame 0x10: ra sp+0x0
// [libkernel newlib glue] open(): not supported on this target -- errno (through sub_51F690 [__errno]) = 5 (EIO), returns -1.
void open(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00503820
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x503828u, gen::fn_sub_51F690_0051f690);
    v1 = 5;
    ld(ra, sp, 0x0);
    sw(v1, v0, 0);
    v0 = si(-1);
    sp = addiu(sp, 0x10);
}

// 0x00503848 close -- 8 bytes; leaf frame (no stack)
// [libkernel newlib glue] close(): returns -1 (no file system behind newlib's file descriptors).
void close(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00503848
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = si(-1);
}

// 0x00503850 ioctl -- 8 bytes; leaf frame (no stack)
// [libkernel newlib glue] ioctl(): returns -1.
void ioctl(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00503850
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = si(-1);
}

// 0x00503858 lseek -- 8 bytes; leaf frame (no stack)
// [libkernel newlib glue] lseek(): returns -1.
void lseek(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00503858
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = si(-1);
}

// 0x00503910 isatty -- 8 bytes; leaf frame (no stack)
// [libkernel newlib glue] isatty(): every descriptor is a terminal (returns 1), so stdio line-buffers stdout.
void isatty(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00503910
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}

// 0x00503918 fstat -- 20 bytes; leaf frame (no stack)
// [libkernel newlib glue] fstat(fd, st): st->st_mode (+4) = 0x2000 (S_IFCHR, a character device), the doubleword at +72
// (st_blksize / st_blocks, 0) cleared; returns 0.
void fstat(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a1{ctx, 5};
    // 0x00503918
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 8192;
    sd(zero, a1, 72);
    sw(v0, a1, 4);
    v0 = 0;
}

// 0x00503930 getpid -- 8 bytes; leaf frame (no stack)
// [libkernel newlib glue] getpid(): always 1.
void getpid(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00503930
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}

// 0x00503938 kill -- 40 bytes; frame 0x10: ra sp+0x0
// [libkernel newlib glue] kill(pid, sig): pid 1 (the program itself, see getpid) calls Exit(sig) -- the kernel call,
// which does not return (stood in by the pair tests); any other pid returns 0.
void kill(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00503938
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    if (a0 == v0) {
        // 0x00503948
        charge(ctx, 2);
        a0 = a1;
        jal(ctx, 0x503948u, gen::fn_Exit_0050da58);
    }
    // 0x00503950 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x00503960 stat -- 40 bytes; frame 0x10: ra sp+0x0
// [libkernel newlib glue] stat(): errno = 5 (EIO) through sub_51F690 [__errno], returns -1.
void stat(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00503960
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x503968u, gen::fn_sub_51F690_0051f690);
    v1 = 5;
    ld(ra, sp, 0x0);
    sw(v1, v0, 0);
    v0 = si(-1);
    sp = addiu(sp, 0x10);
}

// 0x00503988 unlink -- 40 bytes; frame 0x10: ra sp+0x0
// [libkernel newlib glue] unlink(): errno = 5 (EIO) through sub_51F690 [__errno], returns -1.
void unlink(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00503988
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x503990u, gen::fn_sub_51F690_0051f690);
    v1 = 5;
    ld(ra, sp, 0x0);
    sw(v1, v0, 0);
    v0 = si(-1);
    sp = addiu(sp, 0x10);
}

// 0x005035E0 sceResetttyinit -- 12 bytes; leaf frame (no stack)
// [libkernel] Forgets that the tty layer was set up (the init flag at 0x77F490 = 0), so the next read / write runs
// sceTtyInit again; called by sceSifSyncIop after an IOP reboot. $v0 is left at the flag's page (0x780000) by lui.
void sceResetttyinit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2};
    // 0x005035e0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x780000;
    sw(zero, v0, -2928);  // 0x77F490
}

// 0x00505F48 _set_sreg -- 28 bytes; leaf frame (no stack)
// [libkernel SIF] The SIF "set software register" command handler: table (the word at +28 of $a1, the handler data)
// [packet+16] = packet+20. Memory only: called by the SIF command dispatcher with the received packet.
void _set_sreg(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00505f48
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v0, a0, 16);
    lw(a2, a1, 28);
    lw(v1, a0, 20);
    v0 = sll(v0, 2);
    v0 = addu(v0, a2);
    sw(v1, v0, 0);
}

// 0x00505F68 _change_addr -- 12 bytes; leaf frame (no stack)
// [libkernel SIF] The SIF "change address" command handler: stores the packet's word at +16 into +8 of the handler data
// ($a1) and returns it.
void _change_addr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00505f68
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 16);
    sw(v0, a1, 8);
}

// 0x00505F78 sceSifGetSreg -- 24 bytes; leaf frame (no stack)
// [libkernel SIF] Software register $a0 (the word table at 0x966C00).
void sceSifGetSreg(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00505f78
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x960000;
    a0 = sll(a0, 2);
    v0 = addiu(v0, 27648);  // &0x966C00
    a0 = addu(a0, v0);
    lw(v0, a0, 0);
}

// 0x00505F90 sceSifSetSreg -- 28 bytes; leaf frame (no stack)
// [libkernel SIF] Software register $a0 = $a1 (the table at 0x966C00); returns $a1.
void sceSifSetSreg(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00505f90
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0x960000;
    a0 = sll(a0, 2);
    v0 = addiu(v0, 27648);  // &0x966C00
    a0 = addu(a0, v0);
    v0 = a1;
    sw(a1, a0, 0);
}

// 0x00505FB0 sceSifGetDataTable -- 12 bytes; leaf frame (no stack)
// [libkernel SIF] The address of the SIF command data block (0x966A58).
void sceSifGetDataTable(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00505fb0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x960000;
    v0 = addiu(v0, 27224);  // &0x966A58
}

// 0x00506400 sub_506400 -- 24 bytes; leaf frame (no stack)
// [libkernel SIF] [proposed: set the user command handler table] The SIF data block's user table: pointer (0x966A6C) =
// $a0, size (0x966A70) = $a1; returns the old pointer.
void sub_506400(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00506400
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x960000;
    v1 = addiu(v1, 27224);  // &0x966A58
    lw(v0, v1, 20);  // 0x966A6C
    sw(a1, v1, 24);  // 0x966A70
    sw(a0, v1, 20);  // 0x966A6C
}

// 0x00506418 sub_506418 -- 24 bytes; leaf frame (no stack)
// [libkernel SIF] [proposed: set the system command handler table] The system table: pointer (0x966A64) = $a0, size
// (0x966A68) = $a1; returns the old pointer.
void sub_506418(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00506418
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x960000;
    v1 = addiu(v1, 27224);  // &0x966A58
    lw(v0, v1, 12);  // 0x966A64
    sw(a1, v1, 16);  // 0x966A68
    sw(a0, v1, 12);  // 0x966A64
}

// 0x00506430 sub_506430 -- 120 bytes; leaf frame (no stack)
// [libkernel SIF] [proposed: add a command handler] Command $a0 gets handler $a1 with data $a2: 12-byte entries {handler,
// data, -}, in the system table for a command with bit 31 set (index $a0 & 0x7FFFFFFF), the user table otherwise; the
// third word gets $v1's value as the instructions leave it (Hex-Rays: undefined). Returns the table.
void sub_506430(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x00506430
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = a0;
    a3 = a1;
    if (i64(v0) >= 0) {
        // 0x00506474
        charge(ctx, 10);
        v1 = 12;
        a0 = 0x960000;
        mult(v1, v0, v1);
        a0 = addiu(a0, 27224);  // &0x966A58
        lw(v0, a0, 20);  // 0x966A6C
        v0 = addu(v1, v0);
        sw(a2, v0, 4);
        sw(a3, v0, 0);
        a1 = gp;
        lw(v0, a0, 20);  // 0x966A6C
    } else {
        // 0x0050643c
        charge(ctx, 14);
        v1 = 0x7FFF0000;
        a1 = 12;
        v1 = v1 | 0xFFFF;
        a0 = 0x960000;
        v1 = v0 & v1;
        a0 = addiu(a0, 27224);  // &0x966A58
        mult(v1, v1, a1);
        lw(v0, a0, 12);  // 0x966A64
        v0 = addu(v1, v0);
        sw(a2, v0, 4);
        sw(a3, v0, 0);
        a1 = gp;
        lw(v0, a0, 12);  // 0x966A64
    }
    // 0x0050649c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v1 = addu(v1, v0);
    sw(a1, v1, 8);
}

// 0x0050D468 __sceKernlGetEhSemaId -- 12 bytes; leaf frame (no stack)
// [libkernel] The id of the kernel exception-handler semaphore (the word at 0x77FBD4).
void __sceKernlGetEhSemaId(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x0050d468
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x780000;
    lw(v0, v1, -1068);  // 0x77FBD4
}

// 0x0050D840 sub_50D840 -- 48 bytes; leaf frame (no stack)
// [libkernel] [proposed: byte copy] Copies $a2 bytes from $a1 to $a0 (an unsigned count; nothing for 0); returns 0.
void sub_50D840(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0050d840
    enter(ctx, 2);  // entry check point + this block's cycles
    a3 = 0;
    if (a2 != 0) {
        for (;;) {
            // 0x0050d848
            charge(ctx, 8);
            lbu(v1, a1, 0);
            a3 = addiu(a3, 1);
            a1 = addiu(a1, 1);
            v0 = sltu(a3, a2);
            sb(v1, a0, 0);
            a0 = addiu(a0, 1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0050d868 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = 0;
}

// 0x0050DC78 nullsub_131 -- 8 bytes; leaf frame (no stack)
// [libkernel] An empty handler (jr $ra).
void nullsub_131(EEContext& ctx) {
    using namespace hg;
    // 0x0050dc78
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0050E190 sub_50E190 -- 132 bytes; leaf frame (no stack)
// [libkernel alarms] [proposed: insert an alarm] Links the alarm $a0 (sce::alarm::) into the pending list (head at
// 0x780B60) before the first entry whose key ([+32] + [+16] - [+24], three u64 fields, compared unsigned) is larger; updates
// the neighbours' next / prev and the head. $v0 = the timer block (0x780B48).
void sub_50E190(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x0050e190
    enter(ctx, 11);  // entry check point + this block's cycles
    a2 = a0;
    t1 = 0x780000;
    ld(v0, a2, 32);
    a1 = addiu(t1, 2888);  // &0x780B48
    ld(v1, a2, 16);
    t0 = 0;
    ld(a0, a2, 24);
    v0 = v0 + v1;
    lw(a1, a1, 24);  // 0x780B60
    a3 = v0 - a0;
    for (;;) {
        // 0x0050e1c4
        charge(ctx, 2);
        if (a1 != 0) {
            // 0x0050e1cc
            charge(ctx, 8);
            ld(v0, a1, 32);
            ld(v1, a1, 16);
            ld(a0, a1, 24);
            v0 = v0 + v1;
            v0 = v0 - a0;
            v0 = sltu(a3, v0);
            if (v0 != 0) {
                goto L_0050e1ec_4;
            }
            t0 = a1;
            backedge(ctx);
            // 0x0050e1c0
            charge(ctx, 1);
            lw(a1, t0, 0);
            continue;
        }
        sw(t0, a2, 4);
        break;
    }
L_0050e1f0:
    charge(ctx, 2);
    sw(a1, a2, 0);
    if (a1 != 0) {
        // 0x0050e1f8
        charge(ctx, 1);
        sw(a2, a1, 4);
    }
    // 0x0050e1fc
    charge(ctx, 2);
    v0 = addiu(t1, 2888);
    if (t0 == 0) {
        // 0x0050e20c
        charge(ctx, 2);
        sw(a2, v0, 24);
        return;
    }
    // 0x0050e204
    charge(ctx, 2);
    sw(a2, t0, 0);
    return;
L_0050e1ec_4:
    charge(ctx, 1);
    sw(t0, a2, 4);
    goto L_0050e1f0;
}

// 0x0050E218 sub_50E218 -- 56 bytes; leaf frame (no stack)
// [libkernel alarms] [proposed: unlink an alarm] Removes $a0 from the pending list (the head 0x780B60 when it has no
// prev), clears its prev; returns its old next.
void sub_50E218(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0050e218
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 4);
    lw(v1, a0, 0);
    if (v0 == 0) {
        // 0x0050e22c
        charge(ctx, 2);
        v0 = 0x780000;
        sw(v1, v0, 2912);  // 0x780B60
    } else {
        // 0x0050e224
        charge(ctx, 2);
        sw(v1, v0, 0);
    }
    // 0x0050e234
    charge(ctx, 2);
    if (v1 == 0) {
        sw(zero, a0, 4);
    } else {
        // 0x0050e23c
        charge(ctx, 3);
        lw(v0, a0, 4);
        sw(v0, v1, 4);
        sw(zero, a0, 4);
    }
    // 0x0050e248 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = v1;
}

// 0x0050E5D8 sub_50E5D8 -- 112 bytes; leaf frame (no stack)
// [libkernel alarms] [proposed: allocate an alarm] Takes the first record of the free list (0x780B5C), counts it in use
// (0x780B58 + 1), clears its flags (+12), the u64 at +24 and the word at +40, gives it the next sequence tag ((++0x780B54 * 2) & 0x3FE
// | 1) and returns the id (record << 4 | tag; record addresses are 64-byte aligned so id >> 10 << 6 recovers them);
// 0x80008005 when the pool is empty (the KE_ error code as the instructions build it).
void sub_50E5D8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0050e5d8
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x780000;
    a3 = addiu(v0, 2888);  // &0x780B48
    lw(a2, a3, 20);  // 0x780B5C
    if (a2 == 0) {
        // 0x0050e5ec
        charge(ctx, 3);
        v0 = lui(0x8000);
        v0 = v0 | 0x8005;
        return;
    }
    // 0x0050e5f8
    charge(ctx, 20);
    lw(v0, a3, 16);
    a1 = sll(a2, 4);
    lw(a0, a2, 0);
    v0 = addiu(v0, 1);
    sw(zero, a2, 40);
    sw(v0, a3, 16);
    sw(zero, a2, 12);
    sw(a0, a3, 20);
    lw(v1, a3, 12);
    sd(zero, a2, 24);
    v1 = addiu(v1, 1);
    sw(v1, a3, 12);
    lw(v0, a3, 12);
    v0 = sll(v0, 1);
    v0 = v0 & 0x3FE;
    v0 = v0 | 0x1;
    sw(v0, a2, 8);
    lw(v0, a2, 8);
    v0 = a1 | v0;
}

// 0x0050E690 sub_50E690 -- 188 bytes; frame 0x40: s0 sp+0x0, ra sp+0x30, s2 sp+0x20, s1 sp+0x10
// [libkernel alarms] [proposed: free an alarm] Checks the id $a0 (non-negative, its tag = the record's), refuses the
// alarm being handled now (0x780B64: 0x80000010); a pending one (flag bit 1) is unlinked, with the list cursor 0x780B68
// moved on when it pointed at it; then clears tag and flags, pushes it on the free list, in use - 1. 0 on success,
// 0x80008002 for a bad id.
void sub_50E690(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050e690
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = srl(a0, 10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x30);
    s0 = sll(v0, 6);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    if (i64(a0) >= 0) {
        // 0x0050e6b0
        charge(ctx, 4);
        lw(v1, s0, 8);
        v0 = a0 & 0x3FF;
        s2 = 0x780000;
        if (v0 != v1) {
            goto L_0050e6c0;
        }
        // 0x0050e6cc
        charge(ctx, 4);
        s1 = addiu(s2, 2888);
        lw(v0, s1, 28);
        if (v0 != a0) {
            lw(v0, s0, 12);
            // 0x0050e6e8
            charge(ctx, 3);
            v0 = v0 & 0x2;
            if (v0 != 0) {
                // 0x0050e6f4
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x50E6F4u, gen::fn_sub_50E218_0050e218);
                v1 = v0;
                lw(v0, s1, 32);
                if (v0 == s0) {
                    sw(v1, s1, 32);
                }
            }
            // 0x0050e70c
            charge(ctx, 10);
            sw(zero, s0, 8);
            v1 = addiu(s2, 2888);
            sw(zero, s0, 12);
            v0 = 0;
            lw(a1, v1, 20);
            lw(a0, v1, 16);
            sw(a1, s0, 0);
            a0 = addiu(a0, -1);
            sw(s0, v1, 20);
            sw(a0, v1, 16);
        } else {
            // 0x0050e6dc
            charge(ctx, 3);
            v0 = lui(0x8000);
            v0 = v0 | 0x10;
        }
        // 0x0050e734 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x30);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_0050e6c0:
    charge(ctx, 3);
    v0 = lui(0x8000);
    v0 = v0 | 0x8002;
    // 0x0050e734 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0050E7A0 sub_50E7A0 -- 80 bytes; leaf frame (no stack)
// [libkernel alarms] [proposed: alarm pool status] Unless the timer is not set up (0x780B50 < 0: 0x80008001), writes the
// alarms in use (0x780B58) to *$a0 and the free ones (128 - in use) to *$a1 (each when the pointer is not NULL); 0.
void sub_50E7A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0050e7a0
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x780000;
    v1 = addiu(v0, 2888);  // &0x780B48
    lw(v0, v1, 8);  // 0x780B50
    if (i64(v0) < 0) {
        // 0x0050e7b4
        charge(ctx, 3);
        v0 = lui(0x8000);
        v0 = v0 | 0x8001;
        return;
    }
    // 0x0050e7c0
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x0050e7c8
        charge(ctx, 2);
        lw(v0, v1, 16);
        sw(v0, a0, 0);
    }
    // 0x0050e7d0
    charge(ctx, 2);
    if (a1 != 0) {
        // 0x0050e7d8
        charge(ctx, 4);
        lw(v1, v1, 16);
        v0 = 128;
        v0 = subu(v0, v1);
        sw(v0, a1, 0);
    }
    // 0x0050e7e8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = 0;
}

// 0x0050EB50 sub_50EB50 -- 72 bytes; leaf frame (no stack)
// [libkernel alarms] [proposed: alarm time left] For a valid id $a0 with flag bit 0 set: [+16] - [+24] (u64); 0 when
// the flag is clear; -1 for a bad id.
void sub_50EB50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0050eb50
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = srl(a0, 10);
    a1 = sll(v0, 6);
    if (i64(a0) < 0) {
        // 0x0050eb6c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = si(-1);
        return;
    }
    // 0x0050eb5c
    charge(ctx, 4);
    lw(v1, a1, 8);
    v0 = a0 & 0x3FF;
    if (v0 != v1) {
        // 0x0050eb6c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = si(-1);
        return;
    }
    lw(v0, a1, 12);
    // 0x0050eb74
    charge(ctx, 3);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0050eb90
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x0050eb80
    charge(ctx, 4);
    ld(v1, a1, 24);
    ld(v0, a1, 16);
    v0 = v0 - v1;
}

// 0x0050EE38 sub_50EE38 -- 168 bytes; frame 0x40: s1 sp+0x10, s0 sp+0x0, s2 sp+0x20, ra sp+0x30
// [libkernel time] [proposed: bus cycles -> seconds + microseconds] With the bus clock 147,456,000 Hz: *$a1 = cycles /
// 147456000, *$a2 = (cycles - seconds * 147456000) * 1000000 / 147456000 (each when not NULL; __udivdi3).
void sub_50EE38(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050ee38
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    s1 = a0;
    sd(s2, sp, 0x20);
    s0 = a1;
    sd(ra, sp, 0x30);
    s2 = a2;
    a1 = 0x8CA0000;
    jal(ctx, 0x50EE58u, gen::fn___udivdi3_0052fe98);
    v0 = dsll32(v0, 0);
    v0 = dsra32(v0, 0);
    if (s0 != 0) {
        sw(v0, s0, 0);
    }
    // 0x0050ee70
    charge(ctx, 2);
    v1 = 0x8CA0000;
    if (s2 != 0) {
        // 0x0050ee78
        charge(ctx, 20);
        a1 = 0x8CA0000;
        multu(zero, v0, v1);
        mflo(a2);
        mfhi(v1);
        a2 = dsll32(a2, 0);
        v1 = dsll32(v1, 0);
        a2 = dsrl32(a2, 0);
        v1 = v1 | a2;
        v1 = s1 - v1;
        v0 = dsll(v1, 5);
        v0 = v0 - v1;
        a0 = dsll(v0, 6);
        a0 = a0 - v0;
        a0 = dsll(a0, 3);
        a0 = a0 + v1;
        a0 = dsll(a0, 6);
        jal(ctx, 0x50EEB4u, gen::fn___udivdi3_0052fe98);
        v0 = dsll32(v0, 0);
        v0 = dsra32(v0, 0);
        sw(v0, s2, 0);
    }
    // 0x0050eec8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0050EEE0 sub_50EEE0 -- 112 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// [libkernel time] [proposed: seconds + microseconds -> bus cycles] $a0 * 147456000 (the 64-bit product through the
// pipeline-1 multu1 / mfhi1 / mflo1) + $a1 * 147456000 / 1000000 (__udivdi3). Used by DelayThread.
void sub_50EEE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050eee0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x8CA0000;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x10);
    a0 = a1;
    multu1(zero, s0, v0);
    multu(zero, a0, v0);
    a1 = 0xF0000;
    a1 = a1 | 0x4240;
    mfhi1(s0);
    mflo(a2);
    s0 = dsll32(s0, 0);
    a2 = dsll32(a2, 0);
    mfhi(a0);
    a2 = dsrl32(a2, 0);
    a0 = dsll32(a0, 0);
    a0 = a0 | a2;
    mflo1(a2);
    a2 = dsll32(a2, 0);
    a2 = dsrl32(a2, 0);
    s0 = s0 | a2;
    jal(ctx, 0x50EF34u, gen::fn___udivdi3_0052fe98);
    v0 = s0 + v0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0050EF50 sub_50EF50 -- 84 bytes; frame 0x10: ra sp+0x0
// [libkernel time] [proposed: cycles per second for a period] 147456000.0f / (float)$a0 (an unsigned 64-bit count:
// __floatdisf, with the halve-and-double fix for values >= 2^63) in $f0.
void sub_50EF50(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0050ef50
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (i64(a0) < 0) {
        // 0x0050ef6c
        charge(ctx, 5);
        v0 = dsrl(a0, 1);
        a0 = a0 & 0x1;
        a0 = a0 | v0;
        jal(ctx, 0x50EF74u, gen::fn___floatdisf_0052eb60);
        add_s(f1, f0, f0);
    } else {
        // 0x0050ef5c
        charge(ctx, 4);
        jal(ctx, 0x50EF5Cu, gen::fn___floatdisf_0052eb60);
        mov_s(f1, f0);
    }
    // 0x0050ef80 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    at = 0x4D0C0000;
    at = at | 0xA000;
    mtc1(at, f0);
    ld(ra, sp, 0x0);
    div_s(f0, f0, f1);
    sp = addiu(sp, 0x10);
}

// 0x0050EFA8 sub_50EFA8 -- 52 bytes; frame 0x10: ra sp+0x0
// [libkernel time] [proposed: period for a rate] (u64)(147456000.0f / $f12) through __fixunssfdi.
void sub_50EFA8(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x0050efa8
    enter(ctx, 13);  // entry check point + this block's cycles
    at = 0x4D0C0000;
    at = at | 0xA000;
    mtc1(at, f0);
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    div_s(f12, f0, f12);
    jal(ctx, 0x50EFC8u, gen::fn___fixunssfdi_0052eda0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0050EFE0 _InitAlarm -- 76 bytes; leaf frame (no stack)
// [libkernel alarms] Builds the free list of the 64 user-alarm records (16 bytes each, 0x96D3C0..0x96D7B0): each record's
// first word points to the record 16 bytes above it, the head (0x96D7C0) to the lowest one, the highest record's link
// 0. Returns 0.
void _InitAlarm(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0050efe0
    enter(ctx, 8);  // entry check point + this block's cycles
    a1 = 0x970000;
    v1 = 0x970000;
    v0 = addiu(a1, -11328);  // &0x96D3C0
    a0 = 63;
    sw(v0, v1, -10304);  // 0x96D7C0
    v1 = addiu(v0, 1024);  // &0x96D7C0
    v0 = addiu(v0, 1008);  // &0x96D7B0
    for (;;) {
        // 0x0050f000
        charge(ctx, 7);
        sw(v1, v0, 0);
        a0 = addiu(a0, -1);
        v0 = addiu(v0, -16);
        v1 = addiu(v1, -16);
        if (i64(a0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0050f01c
    charge(ctx, 4);
    v1 = addiu(a1, -11328);
    v0 = 0;
    sw(zero, v1, 1008);
}

// 0x0050F030 AlarmHandler -- 92 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// [libkernel alarms] The kernel-alarm trampoline for SetAlarm-style callbacks: calls the user handler (record +8, by
// jalr) with (record << 4 | (id & 0xFE) | 1, $a1, $a2, the user argument at +12); a 0 result puts the record back on the
// free list (head 0x96D7C0) and returns -1 (the alarm ends), otherwise the handler's value (the next interval).
void AlarmHandler(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050f030
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a0 = a0 & 0xFE;
    sd(s0, sp, 0x0);
    s0 = a3;
    sd(ra, sp, 0x10);
    v1 = sll(s0, 4);
    v1 = v1 | a0;
    lw(v0, s0, 8);
    lw(a3, s0, 12);
    a0 = v1 | 0x1;
    jalr(ctx, 0x50F054u, v0.u());
    ld(ra, sp, 0x10);
    if (v0 == 0) {
        // 0x0050f064
        charge(ctx, 7);
        v1 = 0x970000;
        v0 = si(-1);
        lw(a0, v1, -10304);  // 0x96D7C0
        sw(s0, v1, -10304);  // 0x96D7C0
        sw(a0, s0, 0);
        sw(zero, s0, 4);
        ld(ra, sp, 0x10);
    }
    // 0x0050f080 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00508378 _fs_version -- 140 bytes; frame 0x50: s3 sp+0x30, s1 sp+0x10, s2 sp+0x20, ra sp+0x40, s0 sp+0x0
// [libkernel file I/O] Which protocol the IOP file server speaks: 0 when the server's 4-byte version tag (0x969C28)
// equals the library's own (0x77F48C) or the alternate tag (*0x77F550); otherwise 1 unless the library's tag equals the
// alternate one (memcmp three times).
void _fs_version(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00508378
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x780000;
    sd(s3, sp, 0x30);
    v1 = 0x970000;
    sd(s1, sp, 0x10);
    s3 = addiu(v0, -2932);  // "3100"
    sd(s2, sp, 0x20);
    s1 = addiu(v1, -25560);  // &0x969C28
    sd(ra, sp, 0x40);
    s2 = 0;
    sd(s0, sp, 0x0);
    a0 = s1;
    a1 = s3;
    a2 = 4;
    jal(ctx, 0x5083ACu, gen::fn_memcmp_005211b8);
    s0 = 0x780000;
    if (v0 != 0) {
        // 0x005083bc
        charge(ctx, 6);
        a0 = s1;
        lw(a1, s0, -2736);
        a2 = 4;
        jal(ctx, 0x5083C4u, gen::fn_memcmp_005211b8);
        lw(a1, s0, -2736);
        if (v0 != 0) {
            // 0x005083d4
            charge(ctx, 4);
            a0 = s3;
            a2 = 4;
            jal(ctx, 0x5083D8u, gen::fn_memcmp_005211b8);
            s2 = sltu(0, v0);
        }
    }
    // 0x005083e4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s2;
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0050BBE8 _lf_version -- 140 bytes; frame 0x50: s3 sp+0x30, s1 sp+0x10, s2 sp+0x20, ra sp+0x40, s0 sp+0x0
// [libkernel module loader] The same check for the IOP module loader's tag (0x96A0E8 against 0x77F48C and *0x77F564).
void _lf_version(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050bbe8
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x780000;
    sd(s3, sp, 0x30);
    v1 = 0x970000;
    sd(s1, sp, 0x10);
    s3 = addiu(v0, -2932);  // "3100"
    sd(s2, sp, 0x20);
    s1 = addiu(v1, -24344);  // &0x96A0E8
    sd(ra, sp, 0x40);
    s2 = 0;
    sd(s0, sp, 0x0);
    a0 = s1;
    a1 = s3;
    a2 = 4;
    jal(ctx, 0x50BC1Cu, gen::fn_memcmp_005211b8);
    s0 = 0x780000;
    if (v0 != 0) {
        // 0x0050bc2c
        charge(ctx, 6);
        a0 = s1;
        lw(a1, s0, -2716);
        a2 = 4;
        jal(ctx, 0x50BC34u, gen::fn_memcmp_005211b8);
        lw(a1, s0, -2716);
        if (v0 != 0) {
            // 0x0050bc44
            charge(ctx, 4);
            a0 = s3;
            a2 = 4;
            jal(ctx, 0x50BC48u, gen::fn_memcmp_005211b8);
            s2 = sltu(0, v0);
        }
    }
    // 0x0050bc54 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s2;
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0051C0F8 _get_free_slot -- 56 bytes; leaf frame (no stack)
// [libdbc] The first of the two socket slots (36-byte records at 0x985508) whose first word is 0, or -1.
void _get_free_slot(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0051c0f8
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x980000;
    v1 = 0;
    a0 = addiu(v0, 21768);  // &0x985508
    for (;;) {
        // 0x0051c108
        charge(ctx, 3);
        lw(v0, a0, 0);
        if (v0 == 0) {
            goto L_0051c114_2;
        }
        v1 = addiu(v1, 1);
        // 0x0051c11c
        charge(ctx, 3);
        v0 = slti(v1, 2);
        a0 = addiu(a0, 36);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0051c128
    charge(ctx, 2);
    v0 = si(-1);
    return;
L_0051c114_2:
    charge(ctx, 2);
    v0 = v1;
}

// 0x0051D588 DPRINT -- 40 bytes; frame 0x80
// [libdbc] The debug print of the release library: empty (jr $ra).
void DPRINT(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29};
    // 0x0051d588
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(a1, sp, 0x48);
    sd(a2, sp, 0x50);
    sd(a3, sp, 0x58);
    sd(t0, sp, 0x60);
    sd(t1, sp, 0x68);
    sd(t2, sp, 0x70);
    sd(t3, sp, 0x78);
    sp = addiu(sp, 0x80);
}

}  // namespace p3fes::game

// --- the recompiled entry points (dispatch, generated callers) run the bodies above ---
