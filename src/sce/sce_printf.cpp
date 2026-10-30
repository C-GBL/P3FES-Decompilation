// Slice sce1 (sce_printf.cpp): the libkernel tty queue, the character sinks and the sceSnprintf formatting engine.
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

// 0x00504678 QueueInit -- 36 bytes; leaf frame (no stack)
// [libkernel tty] Resets the tty input ring (sce::ttyq:: at 0x966540): capacity = $a0, count 0, read and write pointers
// at the start of the data (+16, 0x966550). Returns the queue's address.
void QueueInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00504678
    enter(ctx, 9);  // entry check point + this block's cycles
    v0 = 0x960000;
    v1 = addiu(v0, 25920);  // &0x966540
    sw(a0, v0, 25920);  // 0x966540
    a0 = addiu(v1, 16);  // &0x966550
    v0 = v1;
    sw(a0, v1, 8);  // 0x966548
    sw(zero, v1, 4);  // 0x966544
    sw(a0, v1, 12);  // 0x96654C
}

// 0x005046A0 QueuePeekWriteDone -- 60 bytes; leaf frame (no stack)
// [libkernel tty] One byte was written at the write pointer: count + 1, write pointer + 1, wrapped back to the data
// start when it reaches data + capacity. $v0 = the new count (or the data start on a wrap).
void QueuePeekWriteDone(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x005046a0
    enter(ctx, 11);  // entry check point + this block's cycles
    a1 = a0;
    lw(v0, a1, 4);
    lw(a0, a1, 12);
    lw(v1, a1, 0);
    v0 = addiu(v0, 1);
    a0 = addiu(a0, 1);
    sw(v0, a1, 4);
    v1 = addiu(v1, 16);
    v1 = addu(a1, v1);
    sw(a0, a1, 12);
    if (a0 == v1) {
        // 0x005046cc
        charge(ctx, 2);
        v0 = addiu(a1, 16);
        sw(v0, a1, 12);
    }
    // 0x005046d4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005046E0 QueuePeekReadDone -- 60 bytes; leaf frame (no stack)
// [libkernel tty] One byte was taken at the read pointer: count - 1, read pointer + 1 with the same wrap. $v0 = the new
// count (or the data start on a wrap).
void QueuePeekReadDone(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x005046e0
    enter(ctx, 11);  // entry check point + this block's cycles
    a1 = a0;
    lw(v0, a1, 4);
    lw(a0, a1, 8);
    lw(v1, a1, 0);
    v0 = addiu(v0, -1);
    a0 = addiu(a0, 1);
    sw(v0, a1, 4);
    v1 = addiu(v1, 16);
    v1 = addu(a1, v1);
    sw(a0, a1, 8);
    if (a0 == v1) {
        // 0x0050470c
        charge(ctx, 2);
        v0 = addiu(a1, 16);
        sw(v0, a1, 8);
    }
    // 0x00504714 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00504A30 sceTtyRead -- 208 bytes; frame 0x60: s4 sp+0x40, s2 sp+0x20, ra sp+0x50, s3 sp+0x30, s1 sp+0x10, s0 sp+0x0
// [libkernel tty] read() on the tty: copies up to $a1 bytes from the input ring (the queue pointer at 0x966668) to $a0,
// spinning while the ring is empty (the deci2 handler fills it; the spin is a loop of loads with its back-edge check
// point), and stops after a '\n' or '\r' (which is copied and counted). Returns the bytes copied; 0 for n <= 0.
void sceTtyRead(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00504a30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v1 = 0;
    sd(s4, sp, 0x40);
    sd(s2, sp, 0x20);
    s4 = a0;
    sd(ra, sp, 0x50);
    s2 = a1;
    sd(s3, sp, 0x30);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    if (i64(s2) > 0) {
        // 0x00504a5c
        charge(ctx, 3);
        s3 = 0x960000;
        v0 = 0x960000;
        for (;;) {
            // 0x00504a68
            charge(ctx, 4);
            s1 = addiu(v1, 1);
            lw(a0, v0, 26216);
            s0 = addu(s4, v1);
            for (;;) {
                // 0x00504a78
                charge(ctx, 7);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00504a94
            charge(ctx, 11);
            a1 = addiu(s3, 26192);
            lw(v0, a1, 24);
            lw(v1, v0, 8);
            lbu(a0, v1, 0);
            sb(a0, s0, 0);
            link(ctx, 0x504AA8u);  // $ra first: the delay slot below depends on it
            lw(a0, a1, 24);
            call(ctx, gen::fn_QueuePeekReadDone_005046e0);
            lb(v1, s0, 0);
            v0 = 10;
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = 13;
            if (cc) {
                goto L_00504ac8;
            }
            // 0x00504ac0
            charge(ctx, 2);
            cc = v1 != v0;  // the condition, before the delay slot changes it
            v1 = s1;
            if (!cc) {
                goto L_00504ac8;
            }
            // 0x00504ad0
            charge(ctx, 3);
            v0 = slt(v1, s2);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 0x960000;
            if (!cc) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00504adc
    charge(ctx, 1);
    v0 = v1;
    // 0x00504ae0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_00504ac8:
    charge(ctx, 2);
    v0 = s1;
    // 0x00504ae0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00504BF8 deci2Putchar -- 176 bytes; frame 0x40: s1 sp+0x10, s0 sp+0x0, ra sp+0x30, s2 sp+0x20
// [libkernel tty] printf's DECI2 sink: appends a character to the 128-byte line buffer at 0x966900 (fill count at
// 0x77F4A0); a full buffer (>= 126) is NUL-terminated at +127 and flushed with kputs first (the DECI2 kernel call,
// stood in by the pair tests); '\n' is stored with a NUL after it and flushes the line.
void deci2Putchar(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00504bf8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x10);
    s1 = 0x780000;
    sd(s0, sp, 0x0);
    lw(a1, s1, -2912);  // 0x77F4A0
    s0 = a0;
    sd(ra, sp, 0x30);
    v0 = slti(a1, 126);
    sd(s2, sp, 0x20);
    if (v0 != 0) {
        // 0x00504c40
        charge(ctx, 1);
        s2 = 0x960000;
    } else {
        // 0x00504c20
        charge(ctx, 8);
        s2 = 0x960000;
        sw(zero, s1, -2912);
        v0 = addiu(s2, 26880);  // &0x966900
        a0 = v0;
        link(ctx, 0x504C30u);  // $ra first: the delay slot below depends on it
        sb(zero, v0, 127);
        call(ctx, gen::fn_kputs_00504650);
        lw(a1, s1, -2912);
    }
    // 0x00504c44
    charge(ctx, 3);
    v0 = 10;
    cc = s0 != v0;  // the condition, before the delay slot changes it
    v0 = addiu(s2, 26880);
    if (cc) {
        // 0x00504c80
        charge(ctx, 10);
        v1 = addiu(a1, 1);
        sw(v1, s1, -2912);
        v0 = addu(a1, v0);
        sb(s0, v0, 0);
        ld(ra, sp, 0x30);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
    // 0x00504c50
    charge(ctx, 12);
    a0 = addiu(s2, 26880);
    sw(zero, s1, -2912);
    v0 = addu(a1, a0);
    ld(ra, sp, 0x30);
    sb(s0, v0, 0);
    v1 = v0;
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sb(zero, v1, 1);
    sp = addiu(sp, 0x40);
    gen::fn_kputs_00504650(ctx);  // tail call
}

// 0x00504CA8 serialPutchar -- 52 bytes; frame 0x10: ra sp+0x0
// [libkernel tty] kprintf's serial sink: '\n' becomes "\r\n" (kputchar('\r') first), then kputchar(c) -- kputchar
// writes the SIO transmit register and stays recompiled.
void serialPutchar(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00504ca8
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 10;
    sd(ra, sp, 0x0);
    if (a0 != v0) {
        // 0x00504cd0
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_kputchar_00504bc0(ctx);  // tail call
        return;
    }
    // 0x00504cb8
    charge(ctx, 6);
    a0 = 13;
    jal(ctx, 0x504CB8u, gen::fn_kputchar_00504bc0);
    ld(ra, sp, 0x0);
    a0 = 10;
    sp = addiu(sp, 0x10);
    gen::fn_kputchar_00504bc0(ctx);  // tail call
}

// 0x00504CE0 ftoi -- 144 bytes; leaf frame (no stack)
// [libkernel printf] printfloat's double -> int on the raw IEEE bits ($a0 = the 64-bit pattern, sign ignored): 0 below
// 0.5 (biased exponent - 1075 < -53), 9999 from 2^65 up (>= 13), else the 53-bit mantissa shifted into place (truncated to
// 32 bits), rounded up when the two bits below the integer are both set.
void ftoi(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00504ce0
    enter(ctx, 7);  // entry check point + this block's cycles
    a1 = a0;
    v0 = dsll(a1, 1);
    a2 = dsrl32(v0, 21);
    a2 = daddiu(a2, -1075);
    v0 = slti(a2, -53);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = slti(a2, 13);
    if (!cc) {
        // 0x00504cfc
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x00504d04
    charge(ctx, 2);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = dsll(a1, 12);
    if (!cc) {
        // 0x00504d0c
        charge(ctx, 2);
        v0 = 9999;
        return;
    }
    // 0x00504d14
    charge(ctx, 5);
    v1 = 0x8000;
    v1 = dsll32(v1, 5);
    a1 = dsrl(v0, 12);
    a1 = a1 | v1;
    if (i64(a2) >= 0) {
        // 0x00504d58
        charge(ctx, 3);
        v0 = dsll32(a2, 0);
        v0 = dsra32(v0, 0);
        a1 = dsllv(a1, v0);
    } else {
        // 0x00504d28
        charge(ctx, 9);
        a2 = 0 - a2;
        v0 = 3;
        v1 = daddiu(a2, -2);
        v1 = dsll32(v1, 0);
        v1 = dsra32(v1, 0);
        a1 = dsrlv(a1, v1);
        a0 = a1 & 0x3;
        if (a0 != v0) {
            a1 = dsrl(a1, 2);
        } else {
            // 0x00504d4c
            charge(ctx, 3);
            v0 = dsrl(a1, 2);
            a1 = daddiu(v0, 1);
        }
    }
    // 0x00504d64 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = dsll32(a1, 0);
    v0 = dsra32(v0, 0);
}

// 0x00504D70 printfloat -- 472 bytes; frame 0x80: s6 sp+0x60, s5 sp+0x50, s4 sp+0x40, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0, ra sp+0x70, s3 sp+0x30
// [libkernel printf] %e / %f of the small printf: prints a double ($a3, the bit pattern) through the output callback
// ($a0 sink, $a1 its state, $a2 the remaining-space counter, which it decrements): a '-' for negative values, then
// scales by 10 with the soft-float dpcmp / dpdiv / dpmul (into [0.1, 1) above the constant at 0x7BDB48 / below
// 0x7BDB50), prints "0.%d" of the value times the constant at 0x7BDB58 (through ftoi) and the decimal exponent with
// "e%d" / "e+%d". Returns the characters printed; 0 when no space is left.
void printfloat(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00504d70
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s6, sp, 0x60);
    sd(s5, sp, 0x50);
    s6 = a1;
    sd(s4, sp, 0x40);
    s5 = a0;
    sd(s2, sp, 0x20);
    s4 = 0;
    sd(s1, sp, 0x10);
    s2 = 0;
    sd(s0, sp, 0x0);
    s1 = a2;
    sd(ra, sp, 0x70);
    sd(s3, sp, 0x30);
    lw(v0, s1, 0);
    s0 = a3;
    if (v0 != 0) {
        // 0x00504dbc
        charge(ctx, 6);
        s3 = 0;
        a0 = s0;
        a1 = s3;
        jal(ctx, 0x504DC4u, gen::fn_dpcmp_005316d0);
        a1 = s0;
        if (i64(v0) < 0) {
            // 0x00504dd4
            charge(ctx, 11);
            a0 = s3;
            jal(ctx, 0x504DD4u, gen::fn_dpsub_005311c8);
            s4 = 1;
            s0 = v0;
            a0 = s6;
            a1 = s1;
            a2 = 45;
            jalr(ctx, 0x504DECu, s5.u());
            lw(v1, s1, 0);
            v1 = addiu(v1, -1);
            sw(v1, s1, 0);
        }
        // 0x00504e00
        charge(ctx, 6);
        at = 0x7C0000;
        ld(a1, at, -9400);  // 0x7BDB48
        a0 = s0;
        jal(ctx, 0x504E08u, gen::fn_dpcmp_005316d0);
        s3 = 0x7C0000;
        if (i64(v0) >= 0) {
            // 0x00504e54
            charge(ctx, 6);
            a1 = 0xFFC0;
            a1 = dsll32(a1, 14);
            a0 = s0;
            jal(ctx, 0x504E5Cu, gen::fn_dpcmp_005316d0);
            s3 = 0x7C0000;
            if (i64(v0) >= 0) {
                // 0x00504e6c
                charge(ctx, 2);
                for (;;) {
                    // 0x00504e8c
                    charge(ctx, 6);
                    a1 = 0xFFC0;
                    a1 = dsll32(a1, 14);
                    a0 = s0;
                    jal(ctx, 0x504E94u, gen::fn_dpcmp_005316d0);
                    a0 = s0;
                    if (i64(v0) < 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00504e78
                    charge(ctx, 5);
                    a1 = 0x8048;
                    a1 = dsll32(a1, 15);
                    s2 = addiu(s2, 1);
                    jal(ctx, 0x504E80u, gen::fn_dpdiv_00531480);
                    s0 = v0;
                }
            }
        } else {
            // 0x00504e18
            charge(ctx, 2);
            for (;;) {
                // 0x00504e34
                charge(ctx, 6);
                at = 0x7C0000;
                ld(a1, at, -9392);  // 0x7BDB50
                a0 = s0;
                jal(ctx, 0x504E3Cu, gen::fn_dpcmp_005316d0);
                a0 = s0;
                if (i64(v0) >= 0) {
                    break;
                }
                backedge(ctx);
                // 0x00504e20
                charge(ctx, 5);
                a1 = 0x8048;
                a1 = dsll32(a1, 15);
                s2 = addiu(s2, -1);
                jal(ctx, 0x504E28u, gen::fn_dpmul_00531230);
                s0 = v0;
            }
            // 0x00504e4c
            charge(ctx, 2);
        }
        // 0x00504ea4
        charge(ctx, 16);
        at = 0x7C0000;
        ld(a1, at, -9384);  // 0x7BDB58
        a0 = s0;
        jal(ctx, 0x504EACu, gen::fn_dpmul_00531230);
        a0 = v0;
        jal(ctx, 0x504EB4u, gen::fn___fixunsdfdi_0052ec28);
        a0 = v0;
        jal(ctx, 0x504EBCu, gen::fn_ftoi_00504ce0);
        a3 = addiu(s3, -9424);
        t0 = v0;
        a0 = s5;
        a1 = s6;
        a2 = s1;
        jal(ctx, 0x504ED4u, gen::fn__sceSnprintf_pf_00505d08);
        s4 = addu(s4, v0);
        if (i64(s2) < 0) {
            // 0x00504efc
            charge(ctx, 5);
            a3 = 0x7C0000;
            a0 = s5;
            a1 = s6;
            a2 = s1;
            a3 = addiu(a3, -9408);  // "e%d"
        } else {
            // 0x00504ee4
            charge(ctx, 6);
            a3 = 0x7C0000;
            a0 = s5;
            a1 = s6;
            a2 = s1;
            a3 = addiu(a3, -9416);  // "e+%d"
        }
        // 0x00504f10
        charge(ctx, 4);
        t0 = s2;
        jal(ctx, 0x504F10u, gen::fn__sceSnprintf_pf_00505d08);
        s4 = addu(s4, v0);
        v0 = s4;
    } else {
        // 0x00504db4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00504f20 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00504F48 _sceSnprintf -- 3348 bytes; frame 0x120: fp sp+0x100, s6 sp+0xE0, ra sp+0x110, s7 sp+0xF0, s5 sp+0xD0, s4 sp+0xC0, s3 sp+0xB0, s2 sp+0xA0, s1 sp+0x90, s0 sp+0x80
// [libkernel printf] The formatting engine behind sceSnprintf / sceVsnprintf / scePrintf / kprintf: walks the format
// ($a3) and emits characters through the sink callback ($a0, called by jalr with $a1 = its state) while the space
// counter ($a2) lasts. Flags '-' '+' ' ' '#' '0', width and precision (digits or '*'), length 'h' / 'l' (l = 64-bit),
// conversions d i o u x X p c s e f % (e / f through dptofp / fptodp and printfloat), digits built backwards in a stack
// buffer with __divdi3 / __moddi3 / __udivdi3 / __umoddi3, the jump table at 0x7BDB90 over the conversion character.
// Returns the number of characters produced. The varargs are 8-byte slots ($t0 = their address).
void _sceSnprintf(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00504f48
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    sd(fp, sp, 0x100);
    v0 = addiu(sp, 0x1F);
    sd(s6, sp, 0xE0);
    fp = t0;
    sd(ra, sp, 0x110);
    s6 = a3;
    sd(s7, sp, 0xF0);
    sd(s5, sp, 0xD0);
    sd(s4, sp, 0xC0);
    sd(s3, sp, 0xB0);
    sd(s2, sp, 0xA0);
    sd(s1, sp, 0x90);
    sd(s0, sp, 0x80);
    sw(a2, sp, 0x40);
    sw(a0, sp, 0x44);
    sw(a1, sp, 0x48);
    lbu(a1, s6, 0);
    sw(v0, sp, 0x4C);
    v0 = a1;
    sw(zero, sp, 0x58);
    if (v0 == 0) {
        // 0x00505c0c
        charge(ctx, 3);
        a1 = addiu(sp, 0x40);
        sw(a1, sp, 0x5C);
        lw(a0, sp, 0x48);
    } else {
        // 0x00504fa0
        charge(ctx, 2);
        v1 = addiu(sp, 0x40);
        sw(v1, sp, 0x5C);
        for (;;) {
            // 0x00504fa8
            charge(ctx, 8);
            v0 = sll(v0, 24);
            s5 = 0;
            a2 = sra(v0, 24);
            sw(zero, sp, 0x50);
            t0 = 0;
            v0 = 37;
            sw(zero, sp, 0x54);
            if (a2 != v0) {
                // 0x00505bc4
                charge(ctx, 2);
                lw(a0, sp, 0x48);
                if (a2 == 0) {
                L_00505bf0:
                    charge(ctx, 1);
                    s7 = addiu(s6, 1);
                } else {
                    // 0x00505bcc
                    charge(ctx, 2);
                    s7 = addiu(s6, 1);
                    lw(a1, sp, 0x5C);
                L_00505bd4:
                    charge(ctx, 7);
                    lw(v1, sp, 0x44);
                    jalr(ctx, 0x505BD8u, v1.u());
                    lw(a0, sp, 0x58);
                    a0 = addu(a0, v0);
                    sw(a0, sp, 0x58);
                    backedge(ctx);
                L_005054e4:
                    charge(ctx, 2);
                    lbu(a1, s6, 0);
                }
            } else {
                for (;;) {
                    // 0x00504fc8
                    charge(ctx, 8);
                    s6 = addiu(s6, 1);
                    lbu(a1, s6, 0);
                    v0 = addiu(a1, -32);
                    v0 = sll(v0, 24);
                    a0 = sra(v0, 24);
                    v1 = sltiu(a0, 89);
                    a2 = a1;
                    if (v1 == 0) {
                        goto L_00505714;
                    }
                    // 0x00504fe8
                    charge(ctx, 7);
                    v0 = 0x7C0000;
                    v1 = sll(a0, 2);
                    v0 = addiu(v0, -9328);  // &0x7BDB90
                    v1 = addu(v1, v0);
                    lw(a0, v1, 0);
                    switch (a0.u()) {
                    case 0x505004u:  // table[13]
                        // 0x00505004
                        charge(ctx, 2);
                        s5 = s5 | 0x1;
                        backedge(ctx);
                        continue;
                    case 0x50500Cu:  // table[11]
                        // 0x0050500c
                        charge(ctx, 2);
                        s5 = s5 | 0x2;
                        backedge(ctx);
                        continue;
                    case 0x505014u:  // table[16]
                        // 0x00505014
                        charge(ctx, 2);
                        s5 = s5 | 0x4;
                        backedge(ctx);
                        continue;
                    case 0x50501Cu:  // table[17, 18, 19, 20, 21, 22, 23, 24, 25]
                        // 0x0050501c
                        charge(ctx, 3);
                        s0 = 0;
                        a2 = 10;
                        for (;;) {
                            // 0x00505028
                            charge(ctx, 10);
                            mult(a0, s0, a2);
                            v1 = sll(a1, 24);
                            s6 = addiu(s6, 1);
                            v1 = sra(v1, 24);
                            lbu(a1, s6, 0);
                            a0 = addiu(a0, -48);
                            v0 = addiu(a1, -48);
                            v0 = sltiu(v0, 10);
                            s0 = addu(a0, v1);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x00505050
                        charge(ctx, 1);
                        sw(s0, sp, 0x50);
                    L_00505054:
                        charge(ctx, 2);
                        s7 = addiu(s6, 1);
                        if (a1 != 0) {
                            // 0x0050505c
                            charge(ctx, 2);
                            s6 = addiu(s6, -1);
                            backedge(ctx);
                            continue;
                        }
                        break;
                    case 0x505064u:  // table[14]
                        // 0x00505064
                        charge(ctx, 6);
                        s6 = addiu(s6, 1);
                        s5 = s5 | 0x20;
                        lb(v1, s6, 0);
                        v0 = 42;
                        lbu(a1, s6, 0);
                        if (v1 == v0) {
                            // 0x0050507c
                            charge(ctx, 7);
                            fp = addiu(fp, 0x8);
                            v0 = si(-2);
                            lw(s0, fp, -0x8);
                            t0 = si(-1);
                            v0 = slt(v0, s0);
                            if (v0 != 0) t0 = s0;
                            backedge(ctx);
                            continue;
                        }
                        // 0x00505098
                        charge(ctx, 4);
                        v0 = addiu(a1, -48);
                        v0 = sltiu(v0, 10);
                        s0 = 0;
                        if (v0 != 0) {
                            // 0x005050a8
                            charge(ctx, 2);
                            a2 = 10;
                            for (;;) {
                                // 0x005050b0
                                charge(ctx, 10);
                                mult(a0, s0, a2);
                                v1 = sll(a1, 24);
                                s6 = addiu(s6, 1);
                                v1 = sra(v1, 24);
                                lbu(a1, s6, 0);
                                a0 = addiu(a0, -48);
                                v0 = addiu(a1, -48);
                                v0 = sltiu(v0, 10);
                                s0 = addu(a0, v1);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                        }
                        // 0x005050d8
                        charge(ctx, 5);
                        v0 = si(-2);
                        t0 = si(-1);
                        v0 = slt(v0, s0);
                        if (v0 != 0) t0 = s0;
                        backedge(ctx);
                        goto L_00505054;
                    case 0x5050ECu:  // table[0]
                        // 0x005050ec
                        charge(ctx, 2);
                        s5 = s5 | 0x8;
                        backedge(ctx);
                        continue;
                    case 0x5050F4u:  // table[3]
                        // 0x005050f4
                        charge(ctx, 2);
                        s5 = s5 | 0x10;
                        backedge(ctx);
                        continue;
                    case 0x5050FCu:  // table[76]
                        // 0x005050fc
                        charge(ctx, 2);
                        s5 = s5 | 0x40;
                        backedge(ctx);
                        continue;
                    case 0x505104u:  // table[72]
                        // 0x00505104
                        charge(ctx, 2);
                        s5 = s5 | 0x80;
                        backedge(ctx);
                        continue;
                    case 0x50510Cu:  // table[79]
                        goto L_0050510c;
                    case 0x5051C0u:  // table[88]
                        goto L_005051c0;
                    case 0x5051ECu:  // table[56]
                        goto L_005051ec;
                    case 0x5052ACu:  // table[68, 73]
                        goto L_005052ac;
                    case 0x5053C4u:  // table[85]
                        goto L_005053c4;
                    case 0x505488u:  // table[69, 70]
                        goto L_00505488;
                    case 0x5054ECu:  // table[83]
                        goto L_005054ec;
                    case 0x505630u:  // table[67]
                        goto L_00505630;
                    case 0x505668u:  // table[80]
                        goto L_00505668;
                    case 0x505714u:  // table[1, 2, 4, 5, 6, 7, 8, 9, 10, 12, 15, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 71, 74, 75, 77, 78, 81, 82, 84, 86, 87]
                        goto L_00505714;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, a0.u());
                        return;
                    }
                    break;
                }
            }
        L_00505bf4:
            charge(ctx, 4);
            if (a1 != 0) s6 = s7;
            lbu(v0, s6, 0);
            a1 = v0;
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00505c04
        charge(ctx, 2);
        lw(a0, sp, 0x48);
    }
    // 0x00505c18
    charge(ctx, 17);
    a2 = 0;
    lw(v1, sp, 0x44);
    jt = v1.u();  // the target, read before the delay slot
    link(ctx, 0x505C20u);  // $ra = the return address
    lw(a1, sp, 0x5C);
    call_ptr(ctx, jt);
    lw(v0, sp, 0x58);
    ld(ra, sp, 0x110);
    ld(fp, sp, 0x100);
    ld(s7, sp, 0xF0);
    ld(s6, sp, 0xE0);
    ld(s5, sp, 0xD0);
    ld(s4, sp, 0xC0);
    ld(s3, sp, 0xB0);
    ld(s2, sp, 0xA0);
    ld(s1, sp, 0x90);
    ld(s0, sp, 0x80);
    sp = addiu(sp, 0x120);
    return;
L_0050510c:
    charge(ctx, 3);
    v0 = s5 & 0x40;
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = s5 & 0x80;
    if (cc) {
        // 0x00505124
        charge(ctx, 2);
        fp = addiu(fp, 0x8);
        if (v0 == 0) {
            // 0x00505134
            charge(ctx, 1);
            lwu(s0, fp, -0x8);
        } else {
            // 0x0050512c
            charge(ctx, 2);
            lhu(s0, fp, -0x8);
        }
    } else {
        // 0x00505118
        charge(ctx, 3);
        fp = addiu(fp, 0x8);
        ld(s0, fp, -0x8);
    }
    // 0x00505138
    charge(ctx, 2);
    lw(s1, sp, 0x4C);
    if (s0 != 0) {
        // 0x00505168
        charge(ctx, 4);
        s7 = addiu(s6, 1);
        v1 = s5 & 0x10;
        s4 = s5 & 0x100;
        s3 = s5 & 0x1;
        for (;;) {
            // 0x00505178
            charge(ctx, 8);
            v0 = s0 & 0x7;
            v0 = daddiu(v0, 48);
            s0 = dsrl(s0, 3);
            v0 = v0 & 0xFF;
            sb(v0, s1, 0);
            s1 = addiu(s1, -1);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00505198
        charge(ctx, 2);
        v0 = 48;
        if (v1 != 0) {
            // 0x005051a0
            charge(ctx, 3);
            sb(v0, s1, 0);
            s1 = addiu(s1, -1);
        }
    } else {
        // 0x00505140
        charge(ctx, 3);
        v0 = s5 & 0x20;
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 48;
        if (!cc) {
            // 0x0050514c
            charge(ctx, 2);
            s7 = addiu(s6, 1);
            if (t0 != 0) {
                goto L_00505154;
            }
            // 0x005051ac
            charge(ctx, 1);
            s4 = s5 & 0x100;
            goto L_005051b0;
        }
    L_00505154:
        charge(ctx, 5);
        s7 = addiu(s6, 1);
        sb(v0, s1, 0);
        s4 = s5 & 0x100;
        s1 = addiu(s1, -1);
    L_005051b0:
        charge(ctx, 1);
        s3 = s5 & 0x1;
    }
    // 0x005051b4
    charge(ctx, 3);
    lw(a1, sp, 0x4C);
    s2 = addiu(s1, 1);
L_00505744:
    charge(ctx, 1);
    a0 = subu(a1, s1);
L_00505748:
    charge(ctx, 12);
    v0 = t0;
    lw(a1, sp, 0x50);
    v0 = slt(a0, v0);
    t0 = subu(t0, a0);
    if (v0 == 0) t0 = 0;
    v1 = subu(a1, a0);
    lw(v0, sp, 0x54);
    s1 = addu(s2, a0);
    v1 = subu(v1, v0);
    v1 = subu(v1, t0);
    sw(v1, sp, 0x50);
    if (s4 == 0) {
        // 0x00505794
        charge(ctx, 4);
        v1 = s5 & 0x24;
        v0 = 4;
        a3 = 32;
        if (v1 == v0) {
            // 0x005057a4
            charge(ctx, 3);
            lw(a1, sp, 0x50);
            v1 = 48;
            v0 = slti(a1, 1);
        L_005057b0:
            charge(ctx, 1);
            if (v0 == 0) a3 = v1;
        }
    } else {
        // 0x00505778
        charge(ctx, 3);
        v0 = s5 & 0x4;
        a3 = 32;
        if (v0 != 0) {
            // 0x00505784
            charge(ctx, 4);
            lw(a0, sp, 0x50);
            v1 = 48;
            v0 = slti(a0, 1);
            goto L_005057b0;
        }
    }
    // 0x005057b4
    charge(ctx, 2);
    lw(v0, sp, 0x54);
    if (s3 == 0) {
        // 0x005058c0
        charge(ctx, 3);
        v0 = s5 & 0x4;
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 48;
        if (cc) {
            // 0x00505aa4
            charge(ctx, 3);
            lw(a1, sp, 0x50);
            s0 = 0;
            if (i64(a1) <= 0) {
                // 0x00505b00
                charge(ctx, 2);
                s4 = sltu(s2, s1);
                lw(v0, sp, 0x54);
            } else {
                // 0x00505ab0
                charge(ctx, 2);
                s4 = sltu(s2, s1);
                for (;;) {
                    // 0x00505ab8
                    charge(ctx, 16);
                    lw(a0, sp, 0x48);
                    a2 = a3;
                    lw(a1, sp, 0x5C);
                    s0 = addiu(s0, 1);
                    lw(v1, sp, 0x44);
                    sq(a3, sp, 0x60);
                    jt = v1.u();  // the target, read before the delay slot
                    link(ctx, 0x505AD0u);  // $ra = the return address
                    sq(t0, sp, 0x70);
                    call_ptr(ctx, jt);
                    lw(a0, sp, 0x58);
                    lw(a1, sp, 0x50);
                    a0 = addu(a0, v0);
                    lq(a3, sp, 0x60);
                    sw(a0, sp, 0x58);
                    v0 = slt(s0, a1);
                    lq(t0, sp, 0x70);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00505af8
                charge(ctx, 2);
                lw(v0, sp, 0x54);
            }
            // 0x00505b08
            charge(ctx, 2);
            s0 = 0;
            if (v0 != 0) {
                // 0x00505b10
                charge(ctx, 2);
                s3 = addiu(sp, 0x20);
                for (;;) {
                    // 0x00505b18
                    charge(ctx, 15);
                    v0 = addu(s3, s0);
                    lw(a0, sp, 0x48);
                    lb(a2, v0, 0);
                    s0 = addiu(s0, 1);
                    lw(a1, sp, 0x5C);
                    lw(v1, sp, 0x44);
                    jt = v1.u();  // the target, read before the delay slot
                    link(ctx, 0x505B30u);  // $ra = the return address
                    sq(t0, sp, 0x70);
                    call_ptr(ctx, jt);
                    lw(a0, sp, 0x58);
                    lw(a1, sp, 0x54);
                    a0 = addu(a0, v0);
                    lq(t0, sp, 0x70);
                    v0 = slt(s0, a1);
                    sw(a0, sp, 0x58);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00505b54
            charge(ctx, 2);
            if (i64(t0) > 0) {
                // 0x00505b5c
                charge(ctx, 1);
                s0 = t0;
                for (;;) {
                    // 0x00505b60
                    charge(ctx, 10);
                    lw(a0, sp, 0x48);
                    a2 = 48;
                    lw(a1, sp, 0x5C);
                    lw(v1, sp, 0x44);
                    s0 = addiu(s0, -1);
                    jalr(ctx, 0x505B70u, v1.u());
                    lw(a0, sp, 0x58);
                    a0 = addu(a0, v0);
                    sw(a0, sp, 0x58);
                    if (s0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00505b88
            charge(ctx, 2);
            if (s4 == 0) {
                lbu(a1, s6, 0);
            } else {
                for (;;) {
                    // 0x00505b90
                    charge(ctx, 11);
                    lb(a2, s2, 0);
                    lw(a0, sp, 0x48);
                    s2 = addiu(s2, 1);
                    lw(v1, sp, 0x44);
                    jt = v1.u();  // the target, read before the delay slot
                    link(ctx, 0x505BA0u);  // $ra = the return address
                    lw(a1, sp, 0x5C);
                    call_ptr(ctx, jt);
                    lw(a0, sp, 0x58);
                    a0 = addu(a0, v0);
                    v0 = sltu(s2, s1);
                    sw(a0, sp, 0x58);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00505bbc
                charge(ctx, 2);
                lbu(a1, s6, 0);
            }
        } else {
            // 0x005058cc
            charge(ctx, 2);
            lw(a1, sp, 0x50);
            if (a3 != v0) {
                // 0x00505988
                charge(ctx, 2);
                s0 = 0;
                if (i64(a1) <= 0) {
                    // 0x005059e0
                    charge(ctx, 2);
                    s4 = sltu(s2, s1);
                    lw(v0, sp, 0x54);
                } else {
                    // 0x00505990
                    charge(ctx, 2);
                    s4 = sltu(s2, s1);
                    for (;;) {
                        // 0x00505998
                        charge(ctx, 16);
                        lw(a0, sp, 0x48);
                        a2 = a3;
                        lw(a1, sp, 0x5C);
                        s0 = addiu(s0, 1);
                        lw(v1, sp, 0x44);
                        sq(a3, sp, 0x60);
                        jt = v1.u();  // the target, read before the delay slot
                        link(ctx, 0x5059B0u);  // $ra = the return address
                        sq(t0, sp, 0x70);
                        call_ptr(ctx, jt);
                        lw(a0, sp, 0x58);
                        lw(a1, sp, 0x50);
                        a0 = addu(a0, v0);
                        lq(a3, sp, 0x60);
                        sw(a0, sp, 0x58);
                        v0 = slt(s0, a1);
                        lq(t0, sp, 0x70);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x005059d8
                    charge(ctx, 2);
                    lw(v0, sp, 0x54);
                }
                // 0x005059e8
                charge(ctx, 2);
                s0 = 0;
                if (v0 != 0) {
                    // 0x005059f0
                    charge(ctx, 2);
                    s3 = addiu(sp, 0x20);
                    for (;;) {
                        // 0x005059f8
                        charge(ctx, 15);
                        v0 = addu(s3, s0);
                        lw(a0, sp, 0x48);
                        lb(a2, v0, 0);
                        s0 = addiu(s0, 1);
                        lw(a1, sp, 0x5C);
                        lw(v1, sp, 0x44);
                        jt = v1.u();  // the target, read before the delay slot
                        link(ctx, 0x505A10u);  // $ra = the return address
                        sq(t0, sp, 0x70);
                        call_ptr(ctx, jt);
                        lw(a0, sp, 0x58);
                        lw(a1, sp, 0x54);
                        a0 = addu(a0, v0);
                        lq(t0, sp, 0x70);
                        v0 = slt(s0, a1);
                        sw(a0, sp, 0x58);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            } else {
                // 0x005058d4
                charge(ctx, 3);
                lw(a1, sp, 0x54);
                s0 = 0;
                if (a1 == 0) {
                    // 0x00505934
                    charge(ctx, 2);
                    s4 = sltu(s2, s1);
                    lw(v0, sp, 0x50);
                } else {
                    // 0x005058e0
                    charge(ctx, 2);
                    s3 = addiu(sp, 0x20);
                    s4 = sltu(s2, s1);
                    for (;;) {
                        // 0x005058e8
                        charge(ctx, 17);
                        v0 = addu(s3, s0);
                        lw(a0, sp, 0x48);
                        lb(a2, v0, 0);
                        s0 = addiu(s0, 1);
                        lw(a1, sp, 0x5C);
                        lw(v1, sp, 0x44);
                        sq(a3, sp, 0x60);
                        jt = v1.u();  // the target, read before the delay slot
                        link(ctx, 0x505904u);  // $ra = the return address
                        sq(t0, sp, 0x70);
                        call_ptr(ctx, jt);
                        lw(a0, sp, 0x58);
                        lw(a1, sp, 0x54);
                        a0 = addu(a0, v0);
                        lq(a3, sp, 0x60);
                        sw(a0, sp, 0x58);
                        v0 = slt(s0, a1);
                        lq(t0, sp, 0x70);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0050592c
                    charge(ctx, 2);
                    lw(v0, sp, 0x50);
                }
                // 0x0050593c
                charge(ctx, 2);
                if (i64(v0) > 0) {
                    // 0x00505944
                    charge(ctx, 1);
                    s0 = v0;
                    for (;;) {
                        // 0x00505948
                        charge(ctx, 14);
                        lw(a0, sp, 0x48);
                        a2 = a3;
                        lw(a1, sp, 0x5C);
                        s0 = addiu(s0, -1);
                        lw(v1, sp, 0x44);
                        sq(a3, sp, 0x60);
                        jt = v1.u();  // the target, read before the delay slot
                        link(ctx, 0x505960u);  // $ra = the return address
                        sq(t0, sp, 0x70);
                        call_ptr(ctx, jt);
                        lw(a0, sp, 0x58);
                        lq(a3, sp, 0x60);
                        a0 = addu(a0, v0);
                        lq(t0, sp, 0x70);
                        sw(a0, sp, 0x58);
                        if (s0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00505980
                    charge(ctx, 2);
                }
            }
            // 0x00505a34
            charge(ctx, 2);
            if (i64(t0) > 0) {
                // 0x00505a3c
                charge(ctx, 1);
                s0 = t0;
                for (;;) {
                    // 0x00505a40
                    charge(ctx, 10);
                    lw(a0, sp, 0x48);
                    a2 = 48;
                    lw(a1, sp, 0x5C);
                    lw(v1, sp, 0x44);
                    s0 = addiu(s0, -1);
                    jalr(ctx, 0x505A50u, v1.u());
                    lw(a0, sp, 0x58);
                    a0 = addu(a0, v0);
                    sw(a0, sp, 0x58);
                    if (s0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00505a68
            charge(ctx, 2);
            if (s4 == 0) {
                lbu(a1, s6, 0);
            } else {
                for (;;) {
                    // 0x00505a70
                    charge(ctx, 11);
                    lb(a2, s2, 0);
                    lw(a0, sp, 0x48);
                    s2 = addiu(s2, 1);
                    lw(v1, sp, 0x44);
                    jt = v1.u();  // the target, read before the delay slot
                    link(ctx, 0x505A80u);  // $ra = the return address
                    lw(a1, sp, 0x5C);
                    call_ptr(ctx, jt);
                    lw(a0, sp, 0x58);
                    a0 = addu(a0, v0);
                    v0 = sltu(s2, s1);
                    sw(a0, sp, 0x58);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00505a9c
                charge(ctx, 2);
                lbu(a1, s6, 0);
            }
        }
    } else {
        // 0x005057bc
        charge(ctx, 2);
        s0 = 0;
        if (v0 == 0) {
            // 0x00505814
            charge(ctx, 1);
            s4 = sltu(s2, s1);
        } else {
            // 0x005057c4
            charge(ctx, 3);
            s3 = addiu(sp, 0x20);
            s4 = sltu(s2, s1);
            for (;;) {
                // 0x005057d0
                charge(ctx, 15);
                v0 = addu(s3, s0);
                lw(a0, sp, 0x48);
                lb(a2, v0, 0);
                s0 = addiu(s0, 1);
                lw(a1, sp, 0x5C);
                lw(v1, sp, 0x44);
                jt = v1.u();  // the target, read before the delay slot
                link(ctx, 0x5057E8u);  // $ra = the return address
                sq(t0, sp, 0x70);
                call_ptr(ctx, jt);
                lw(a0, sp, 0x58);
                lw(a1, sp, 0x54);
                a0 = addu(a0, v0);
                lq(t0, sp, 0x70);
                v0 = slt(s0, a1);
                sw(a0, sp, 0x58);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0050580c
            charge(ctx, 2);
        }
        // 0x00505818
        charge(ctx, 2);
        if (i64(t0) > 0) {
            // 0x00505820
            charge(ctx, 2);
            s0 = t0;
            for (;;) {
                // 0x00505828
                charge(ctx, 10);
                lw(a0, sp, 0x48);
                a2 = 48;
                lw(a1, sp, 0x5C);
                lw(v1, sp, 0x44);
                s0 = addiu(s0, -1);
                jalr(ctx, 0x505838u, v1.u());
                lw(a0, sp, 0x58);
                a0 = addu(a0, v0);
                sw(a0, sp, 0x58);
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00505850
        charge(ctx, 2);
        lw(a1, sp, 0x50);
        if (s4 != 0) {
            for (;;) {
                // 0x00505858
                charge(ctx, 11);
                lb(a2, s2, 0);
                lw(a0, sp, 0x48);
                s2 = addiu(s2, 1);
                lw(v1, sp, 0x44);
                jt = v1.u();  // the target, read before the delay slot
                link(ctx, 0x505868u);  // $ra = the return address
                lw(a1, sp, 0x5C);
                call_ptr(ctx, jt);
                lw(a0, sp, 0x58);
                a0 = addu(a0, v0);
                v0 = sltu(s2, s1);
                sw(a0, sp, 0x58);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00505884
            charge(ctx, 1);
            lw(a1, sp, 0x50);
        }
        // 0x00505888
        charge(ctx, 2);
        s0 = a1;
        if (i64(a1) <= 0) {
            backedge(ctx);
            goto L_005054e4;
        }
        for (;;) {
            // 0x00505890
            charge(ctx, 10);
            lw(a0, sp, 0x48);
            a2 = 32;
            lw(a1, sp, 0x5C);
            lw(v1, sp, 0x44);
            s0 = addiu(s0, -1);
            jalr(ctx, 0x5058A0u, v1.u());
            lw(a0, sp, 0x58);
            a0 = addu(a0, v0);
            sw(a0, sp, 0x58);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005058b8
        charge(ctx, 2);
        lbu(a1, s6, 0);
    }
    goto L_00505bf4;
L_005051c0:
    charge(ctx, 4);
    v0 = 0x7C0000;
    v1 = s5 & 0x10;
    a0 = addiu(v0, -9376);  // "0123456789abcdef"
    if (v1 != 0) {
        // 0x005051d0
        charge(ctx, 7);
        v0 = 48;
        v1 = 120;
        sb(v0, sp, 0x20);
        v0 = 2;
        sb(v1, sp, 0x21);
        sw(v0, sp, 0x54);
    }
L_00505214:
    charge(ctx, 3);
    v0 = s5 & 0x40;
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = s5 & 0x80;
    if (cc) {
        // 0x0050522c
        charge(ctx, 2);
        fp = addiu(fp, 0x8);
        if (v0 == 0) {
            // 0x0050523c
            charge(ctx, 1);
            lwu(s0, fp, -0x8);
        } else {
            // 0x00505234
            charge(ctx, 2);
            lhu(s0, fp, -0x8);
        }
    } else {
        // 0x00505220
        charge(ctx, 3);
        fp = addiu(fp, 0x8);
        ld(s0, fp, -0x8);
    }
    // 0x00505240
    charge(ctx, 2);
    lw(s1, sp, 0x4C);
    if (s0 != 0) {
        // 0x00505274
        charge(ctx, 3);
        s7 = addiu(s6, 1);
        s4 = s5 & 0x100;
        s3 = s5 & 0x1;
        for (;;) {
            // 0x00505280
            charge(ctx, 9);
            v0 = s0 & 0xF;
            v0 = dsll32(v0, 0);
            v0 = dsra32(v0, 0);
            s0 = dsrl(s0, 4);
            v0 = addu(a0, v0);
            lbu(v1, v0, 0);
            sb(v1, s1, 0);
            s1 = addiu(s1, -1);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005052a4
        charge(ctx, 2);
        lw(v0, sp, 0x4C);
    } else {
        // 0x00505248
        charge(ctx, 3);
        v0 = s5 & 0x20;
        sw(zero, sp, 0x54);
        if (v0 != 0) {
            // 0x00505254
            charge(ctx, 2);
            s7 = addiu(s6, 1);
            if (t0 != 0) {
                goto L_0050525c;
            }
        L_00505470:
            charge(ctx, 1);
            s4 = s5 & 0x100;
            goto L_00505474;
        }
    L_0050525c:
        charge(ctx, 6);
        v0 = 48;
        s7 = addiu(s6, 1);
        sb(v0, s1, 0);
        s4 = s5 & 0x100;
        s1 = addiu(s1, -1);
    L_00505474:
        charge(ctx, 2);
        s3 = s5 & 0x1;
        lw(v0, sp, 0x4C);
    }
L_0050547c:
    charge(ctx, 3);
    s2 = addiu(s1, 1);
    a0 = subu(v0, s1);
    goto L_00505748;
L_005051ec:
    charge(ctx, 4);
    v0 = 0x7C0000;
    v1 = s5 & 0x10;
    a0 = addiu(v0, -9352);  // "0123456789ABCDEF"
    if (v1 != 0) {
        // 0x005051fc
        charge(ctx, 6);
        v0 = 48;
        v1 = 88;
        a1 = 2;
        sb(v0, sp, 0x20);
        sw(a1, sp, 0x54);
        sb(v1, sp, 0x21);
    }
    goto L_00505214;
L_005052ac:
    charge(ctx, 3);
    v0 = s5 & 0x40;
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = s5 & 0x80;
    if (cc) {
        // 0x005052c4
        charge(ctx, 2);
        fp = addiu(fp, 0x8);
        if (v0 == 0) {
            // 0x005052d4
            charge(ctx, 1);
            lw(s0, fp, -0x8);
        } else {
            // 0x005052cc
            charge(ctx, 2);
            lh(s0, fp, -0x8);
        }
    } else {
        // 0x005052b8
        charge(ctx, 3);
        fp = addiu(fp, 0x8);
        ld(s0, fp, -0x8);
    }
    // 0x005052d8
    charge(ctx, 2);
    lw(s1, sp, 0x4C);
    if (i64(s0) < 0) {
        // 0x00505310
        charge(ctx, 3);
        v0 = 45;
        a1 = 1;
        sw(a1, sp, 0x54);
    L_0050531c:
        charge(ctx, 1);
        sb(v0, sp, 0x20);
    } else {
        // 0x005052e0
        charge(ctx, 3);
        v0 = s5 & 0x2;
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 43;
        if (!cc) {
            // 0x005052ec
            charge(ctx, 3);
            v1 = 1;
            sw(v1, sp, 0x54);
            goto L_0050531c;
        }
        // 0x005052f8
        charge(ctx, 3);
        v0 = s5 & 0x8;
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 32;
        if (!cc) {
            // 0x00505304
            charge(ctx, 3);
            a0 = 1;
            sw(a0, sp, 0x54);
            goto L_0050531c;
        }
    }
    // 0x00505320
    charge(ctx, 2);
    v0 = si(-1);
    if (s0 == 0) {
        // 0x00505328
        charge(ctx, 3);
        v0 = s5 & 0x20;
        lw(v1, sp, 0x4C);
        if (v0 != 0) {
            // 0x00505334
            charge(ctx, 2);
            s7 = addiu(s6, 1);
            if (t0 == 0) {
                goto L_005053b0;
            }
            goto L_0050533c;
        }
    L_0050533c:
        charge(ctx, 6);
        v0 = 48;
        s7 = addiu(s6, 1);
        s4 = s5 & 0x100;
        s1 = addiu(v1, -1);
        sb(v0, v1, 0);
        goto L_005053b4;
    }
    // 0x00505354
    charge(ctx, 5);
    v1 = 0 - s0;
    v0 = slt(v0, s0);
    if (v0 == 0) s0 = v1;
    s7 = addiu(s6, 1);
    if (s0 == 0) {
    L_005053b0:
        charge(ctx, 1);
        s4 = s5 & 0x100;
    L_005053b4:
        charge(ctx, 2);
        s3 = s5 & 0x1;
        lw(a1, sp, 0x4C);
    } else {
        // 0x00505368
        charge(ctx, 2);
        s4 = s5 & 0x100;
        s3 = s5 & 0x1;
        for (;;) {
            // 0x00505370
            charge(ctx, 14);
            a0 = s0;
            a1 = 10;
            link(ctx, 0x505378u);  // $ra first: the delay slot below depends on it
            sq(t0, sp, 0x70);
            call(ctx, gen::fn___moddi3_0052f6a0);
            v0 = daddiu(v0, 48);
            a0 = s0;
            v0 = v0 & 0xFF;
            a1 = 10;
            link(ctx, 0x505390u);  // $ra first: the delay slot below depends on it
            sb(v0, s1, 0);
            call(ctx, gen::fn___divdi3_0052eeb0);
            s1 = addiu(s1, -1);
            s0 = v0;
            lq(t0, sp, 0x70);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005053a8
        charge(ctx, 2);
        lw(a1, sp, 0x4C);
    }
    // 0x005053bc
    charge(ctx, 2);
    s2 = addiu(s1, 1);
    goto L_00505744;
L_005053c4:
    charge(ctx, 3);
    v0 = s5 & 0x40;
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = s5 & 0x80;
    if (cc) {
        // 0x005053dc
        charge(ctx, 2);
        fp = addiu(fp, 0x8);
        if (v0 == 0) {
            // 0x005053ec
            charge(ctx, 1);
            lwu(s0, fp, -0x8);
        } else {
            // 0x005053e4
            charge(ctx, 2);
            lhu(s0, fp, -0x8);
        }
    } else {
        // 0x005053d0
        charge(ctx, 3);
        fp = addiu(fp, 0x8);
        ld(s0, fp, -0x8);
    }
    // 0x005053f0
    charge(ctx, 2);
    lw(s1, sp, 0x4C);
    if (s0 == 0) {
        // 0x005053f8
        charge(ctx, 3);
        v0 = s5 & 0x20;
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 48;
        if (!cc) {
            // 0x00505404
            charge(ctx, 2);
            s7 = addiu(s6, 1);
            if (t0 == 0) {
                goto L_00505470;
            }
            goto L_0050540c;
        }
    L_0050540c:
        charge(ctx, 5);
        s7 = addiu(s6, 1);
        sb(v0, s1, 0);
        s4 = s5 & 0x100;
        s1 = addiu(s1, -1);
        goto L_00505474;
    }
    // 0x00505420
    charge(ctx, 4);
    s7 = addiu(s6, 1);
    s4 = s5 & 0x100;
    s3 = s5 & 0x1;
    for (;;) {
        // 0x00505430
        charge(ctx, 14);
        a0 = s0;
        a1 = 10;
        link(ctx, 0x505438u);  // $ra first: the delay slot below depends on it
        sq(t0, sp, 0x70);
        call(ctx, gen::fn___umoddi3_00530578);
        v0 = daddiu(v0, 48);
        a0 = s0;
        v0 = v0 & 0xFF;
        a1 = 10;
        link(ctx, 0x505450u);  // $ra first: the delay slot below depends on it
        sb(v0, s1, 0);
        call(ctx, gen::fn___udivdi3_0052fe98);
        s1 = addiu(s1, -1);
        s0 = v0;
        lq(t0, sp, 0x70);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00505468
    charge(ctx, 2);
    lw(v0, sp, 0x4C);
    goto L_0050547c;
L_00505488:
    charge(ctx, 9);
    fp = addiu(fp, 0x8);
    link(ctx, 0x50548Cu);  // $ra first: the delay slot below depends on it
    ld(a0, fp, -0x8);
    call(ctx, gen::fn_dptofp_005318a0);
    mov_s(f12, f0);
    mtc1(zero, f0);
    c_eq_s(f12, f0);
    lw(a0, sp, 0x48);
    if (cond(ctx)) {
        // 0x005054ac
        charge(ctx, 4);
        a2 = 48;
        lw(a1, sp, 0x5C);
        s7 = addiu(s6, 1);
        goto L_00505bd4;
    }
    // 0x005054bc
    charge(ctx, 10);
    s7 = addiu(s6, 1);
    jal(ctx, 0x5054BCu, gen::fn_fptodp_00530da0);
    lw(a0, sp, 0x44);
    a3 = v0;
    lw(a1, sp, 0x48);
    link(ctx, 0x5054D0u);  // $ra first: the delay slot below depends on it
    lw(a2, sp, 0x5C);
    call(ctx, gen::fn_printfloat_00504d70);
    lw(a1, sp, 0x58);
    a1 = addu(a1, v0);
    sw(a1, sp, 0x58);
    goto L_005054e4;
L_005054ec:
    charge(ctx, 4);
    fp = addiu(fp, 0x8);
    lw(v1, fp, -0x8);
    v0 = s5 & 0x20;
    if (v1 != 0) {
        // 0x00505580
        charge(ctx, 2);
        s1 = v1;
        if (v0 != 0) {
            // 0x00505588
            charge(ctx, 2);
            s0 = 0;
            if (i64(t0) > 0) {
                // 0x00505590
                charge(ctx, 3);
                lb(v0, s1, 0);
                s1 = addiu(s1, 1);
                if (v0 == 0) {
                    goto L_005055cc;
                }
                // 0x0050559c
                charge(ctx, 3);
                s7 = addiu(s6, 1);
                s4 = s5 & 0x100;
                s3 = s5 & 0x1;
                for (;;) {
                    // 0x005055a8
                    charge(ctx, 4);
                    s0 = addiu(s0, 1);
                    v0 = slt(s0, t0);
                    a0 = s0;
                    if (v0 == 0) {
                        goto L_00505628;
                    }
                    // 0x005055b8
                    charge(ctx, 3);
                    lb(v0, s1, 0);
                    s1 = addiu(s1, 1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x005055c4
                charge(ctx, 2);
                s2 = v1;
                goto L_00505748;
            }
        L_005055cc:
            charge(ctx, 5);
            s7 = addiu(s6, 1);
            s4 = s5 & 0x100;
            s3 = s5 & 0x1;
            a0 = s0;
            goto L_00505628;
        }
        // 0x005055e0
        charge(ctx, 3);
        lb(v0, s1, 0);
        a0 = 0;
        if (v0 == 0) {
            // 0x0050561c
            charge(ctx, 3);
            s7 = addiu(s6, 1);
            s4 = s5 & 0x100;
            s3 = s5 & 0x1;
        L_00505628:
            charge(ctx, 2);
            s2 = v1;
        } else {
            // 0x005055ec
            charge(ctx, 3);
            s7 = addiu(s6, 1);
            s4 = s5 & 0x100;
            s3 = s5 & 0x1;
            for (;;) {
                // 0x005055f8
                charge(ctx, 7);
                s1 = addiu(s1, 1);
                a0 = addiu(a0, 1);
                lb(v0, s1, 0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00505614
            charge(ctx, 2);
            s2 = v1;
        }
        goto L_00505748;
    }
    // 0x005054fc
    charge(ctx, 33);
    lw(a0, sp, 0x48);
    a2 = 40;
    lw(a1, sp, 0x5C);
    lw(v1, sp, 0x44);
    s7 = addiu(s6, 1);
    jalr(ctx, 0x50550Cu, v1.u());
    lw(a0, sp, 0x48);
    a2 = 110;
    lw(v1, sp, 0x44);
    jt = v1.u();  // the target, read before the delay slot
    link(ctx, 0x505520u);  // $ra = the return address
    lw(a1, sp, 0x5C);
    call_ptr(ctx, jt);
    lw(a0, sp, 0x48);
    a2 = 117;
    lw(v1, sp, 0x44);
    jt = v1.u();  // the target, read before the delay slot
    link(ctx, 0x505534u);  // $ra = the return address
    lw(a1, sp, 0x5C);
    call_ptr(ctx, jt);
    lw(a0, sp, 0x48);
    a2 = 108;
    lw(v1, sp, 0x44);
    jt = v1.u();  // the target, read before the delay slot
    link(ctx, 0x505548u);  // $ra = the return address
    lw(a1, sp, 0x5C);
    call_ptr(ctx, jt);
    lw(a0, sp, 0x48);
    a2 = 108;
    lw(v1, sp, 0x44);
    jt = v1.u();  // the target, read before the delay slot
    link(ctx, 0x50555Cu);  // $ra = the return address
    lw(a1, sp, 0x5C);
    call_ptr(ctx, jt);
    lw(a0, sp, 0x48);
    a2 = 41;
    lw(v1, sp, 0x44);
    jt = v1.u();  // the target, read before the delay slot
    link(ctx, 0x505570u);  // $ra = the return address
    lw(a1, sp, 0x5C);
    call_ptr(ctx, jt);
    lbu(a1, s6, 0);
    goto L_00505bf4;
L_00505630:
    charge(ctx, 14);
    fp = addiu(fp, 0x8);
    lw(s1, sp, 0x4C);
    lb(s0, fp, -0x8);
    s5 = s5 | 0x100;
    t0 = 1;
    s7 = addiu(s6, 1);
    v0 = s0 & 0xFF;
    s4 = s5 & 0x100;
    sb(v0, s1, 0);
    s3 = s5 & 0x1;
    s1 = addiu(s1, -1);
    lw(a1, sp, 0x4C);
    s2 = addiu(s1, 1);
    goto L_00505744;
L_00505668:
    charge(ctx, 6);
    fp = addiu(fp, 0x8);
    v0 = 0x7C0000;
    lwu(s0, fp, -0x8);
    a0 = addiu(v0, -9376);  // "0123456789abcdef"
    lw(s1, sp, 0x4C);
    if (s0 != 0) {
        // 0x005056a8
        charge(ctx, 4);
        s7 = addiu(s6, 1);
        s4 = s5 & 0x100;
        s3 = s5 & 0x1;
        for (;;) {
            // 0x005056b8
            charge(ctx, 9);
            v0 = s0 & 0xF;
            v0 = dsll32(v0, 0);
            v0 = dsra32(v0, 0);
            s0 = dsrl(s0, 4);
            v0 = addu(a0, v0);
            lbu(v1, v0, 0);
            sb(v1, s1, 0);
            s1 = addiu(s1, -1);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005056dc
        charge(ctx, 2);
        v0 = 48;
    } else {
        // 0x00505680
        charge(ctx, 3);
        v0 = s5 & 0x20;
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 48;
        if (!cc) {
            // 0x0050568c
            charge(ctx, 2);
            s7 = addiu(s6, 1);
            if (t0 != 0) {
                goto L_00505694;
            }
            // 0x005056e4
            charge(ctx, 1);
            s4 = s5 & 0x100;
            goto L_005056e8;
        }
    L_00505694:
        charge(ctx, 5);
        s7 = addiu(s6, 1);
        sb(v0, s1, 0);
        s4 = s5 & 0x100;
        s1 = addiu(s1, -1);
    L_005056e8:
        charge(ctx, 2);
        s3 = s5 & 0x1;
        v0 = 48;
    }
    // 0x005056f0
    charge(ctx, 9);
    v1 = 120;
    sb(v0, sp, 0x20);
    s2 = addiu(s1, 1);
    lw(v0, sp, 0x4C);
    sb(v1, sp, 0x21);
    v1 = 2;
    a0 = subu(v0, s1);
    sw(v1, sp, 0x54);
    goto L_00505748;
L_00505714:
    charge(ctx, 3);
    v0 = sll(a2, 24);
    lw(s1, sp, 0x4C);
    if (v0 == 0) {
        goto L_00505bf0;
    }
    // 0x00505720
    charge(ctx, 9);
    s5 = s5 | 0x100;
    t0 = 1;
    s7 = addiu(s6, 1);
    sb(a1, s1, 0);
    s4 = s5 & 0x100;
    lw(a1, sp, 0x4C);
    s1 = addiu(s1, -1);
    s2 = addiu(s1, 1);
    s3 = s5 & 0x1;
    goto L_00505744;
}

// 0x00505C60 snprintf_char -- 88 bytes; leaf frame (no stack)
// [libkernel printf] sceSnprintf's sink: $a0 = &cursor, $a1 = &space, $a2 = the character. With space left, stores the character (a NUL in
// the last byte instead), advances the cursor, space - 1, returns 1; a value >= 256 (the end marker) stores a NUL and
// returns 0; no space returns 1 without storing.
void snprintf_char(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00505c60
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a1, 0);
    a3 = a0;
    if (v1 == 0) {
        // 0x00505c6c
        charge(ctx, 2);
        v0 = 1;
        return;
    }
    // 0x00505c74
    charge(ctx, 3);
    v0 = slti(a2, 256);
    if (v0 == 0) {
        lw(v1, a3, 0);
        // 0x00505cac
        charge(ctx, 3);
        v0 = 0;
        sb(zero, v1, 0);
        return;
    }
    // 0x00505c80
    charge(ctx, 11);
    v0 = v1 ^ 0x1;
    lw(a0, a3, 0);
    if (v0 == 0) a2 = 0;
    sb(a2, a0, 0);
    v0 = 1;
    a0 = addiu(a0, 1);
    lw(v1, a1, 0);
    sw(a0, a3, 0);
    v1 = addiu(v1, -1);
    sw(v1, a1, 0);
}

// 0x00505CB8 printf_char -- 40 bytes; frame 0x10: ra sp+0x0
// [libkernel printf] scePrintf's sink (the character in $a2, as for every sink): deci2Putchar(c) unless c is NUL; returns 1.
void printf_char(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00505cb8
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = a2;
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00505cc8
        charge(ctx, 2);
        jal(ctx, 0x505CC8u, gen::fn_deci2Putchar_00504bf8);
    }
    // 0x00505cd0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// 0x00505CE0 kprintf_char -- 40 bytes; frame 0x10: ra sp+0x0
// [libkernel printf] kprintf's sink (the character in $a2): serialPutchar(c) unless c is NUL; returns 1.
void kprintf_char(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00505ce0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = a2;
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00505cf0
        charge(ctx, 2);
        jal(ctx, 0x505CF0u, gen::fn_serialPutchar_00504ca8);
    }
    // 0x00505cf8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// 0x00505D08 _sceSnprintf_pf -- 76 bytes; frame 0x80: s0 sp+0x0, ra sp+0x10
// [libkernel printf] printf from inside the engine (printfloat's "0.%d" / "e%d"): spills $a3.. to the varargs area of its
// frame, runs _sceSnprintf with the caller's sink and *space, subtracts the count from *space, returns it.
void _sceSnprintf_pf(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00505d08
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s0, sp, 0x0);
    sd(t0, sp, 0x60);
    s0 = a2;
    sd(ra, sp, 0x10);
    t0 = addiu(sp, 0x60);
    lw(a2, s0, 0);
    sd(t1, sp, 0x68);
    sd(t2, sp, 0x70);
    link(ctx, 0x505D2Cu);  // $ra first: the delay slot below depends on it
    sd(t3, sp, 0x78);
    call(ctx, gen::fn__sceSnprintf_00504f48);
    lw(v1, s0, 0);
    a0 = v0;
    ld(ra, sp, 0x10);
    v1 = subu(v1, a0);
    sw(v1, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00505D58 sceVsnprintf -- 56 bytes; frame 0x20: ra sp+0x10
// [libkernel printf] vsnprintf(buf, size, fmt, ap): a cursor word on the stack = buf, then _sceSnprintf(snprintf_char,
// &cursor, size, fmt, ap).
void sceVsnprintf(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00505d58
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a2;
    sw(a0, sp, 0x0);
    t0 = a3;
    a2 = a1;
    a0 = 0x500000;
    sd(ra, sp, 0x10);
    a0 = addiu(a0, 23648);  // &snprintf_char
    a3 = v0;
    a1 = sp;
    jal(ctx, 0x505D7Cu, gen::fn__sceSnprintf_00504f48);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00505D90 sceSnprintf -- 72 bytes; frame 0x90: ra sp+0x10
// [libkernel printf] snprintf(buf, size, fmt, ...): spills the variable arguments to its frame, cursor = buf, then
// _sceSnprintf(snprintf_char, &cursor, size, fmt, &args). Callers: libmpeg's error messages.
void sceSnprintf(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00505d90
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(a3, sp, 0x68);
    sw(a0, sp, 0x0);
    a3 = a2;
    sd(t0, sp, 0x70);
    a2 = a1;
    a0 = 0x500000;
    sd(ra, sp, 0x10);
    sd(t1, sp, 0x78);
    a0 = addiu(a0, 23648);  // &snprintf_char
    sd(t2, sp, 0x80);
    a1 = sp;
    sd(t3, sp, 0x88);
    t0 = addiu(sp, 0x68);
    jal(ctx, 0x505DC4u, gen::fn__sceSnprintf_00504f48);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x90);
}

}  // namespace p3fes::game

// --- the recompiled entry points (dispatch, generated callers) run the bodies above ---
