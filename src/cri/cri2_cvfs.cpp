// Phase 5 slice cri2: the cvFs request layer (0x555B10-0x557A28) -- the device table of 32 {interface, name} slots at
// 0x997658 (cri1::cvfs) and the 40 file handles {interface, device file} at 0x997518. A request splits "DEV:file"
// (cvfs_getDevName, cri1), finds the device by name (cvfs_getDevice: strncmp over the slots) or falls back to the
// default device, and calls the entry of the device's interface table (cri2::cvfs::kIf*); handle requests call the
// handle's interface with its device file. A missing entry reports "<request> #n:vtbl error" through the error
// callback (sub_555918, cri1). Note the "device not found" paths of the name requests: they report and then still
// read the entry from a null interface (address 8, 0x5C, 0x3C ... -- kernel RAM on the PS2); kept as is.
// p3fes_handgen bodies with a role comment per function and the interface entries named.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/cri2.h"

namespace p3fes::recomp_gen {
void fn_cvFsAddDev_00555b10(p3fes::EEContext&);
void fn_cvFsAddVolumeEx_00557358(p3fes::EEContext&);
void fn_cvFsClose_00556398(p3fes::EEContext&);
void fn_cvFsExecServer_00556608(p3fes::EEContext&);
void fn_cvFsGetFileSize_005566d0(p3fes::EEContext&);
void fn_cvFsGetStat_00556668(p3fes::EEContext&);
void fn_cvFsOpen_00556048(p3fes::EEContext&);
void fn_cvFsReqRd_005564e0(p3fes::EEContext&);
void fn_cvFsSeek_00556478(p3fes::EEContext&);
void fn_cvFsSetCurVolume_00557290(p3fes::EEContext&);
void fn_cvFsSetDefVol_005575f0(p3fes::EEContext&);
void fn_cvFsTell_00556410(p3fes::EEContext&);
void fn_cvfs_addDevName_00557700(p3fes::EEContext&);
void fn_cvfs_addDevice_00555ba0(p3fes::EEContext&);
void fn_cvfs_getDefDev_00556330(p3fes::EEContext&);
void fn_cvfs_getDevName_005561e8(p3fes::EEContext&);
void fn_cvfs_getDevice_00555c78(p3fes::EEContext&);
void fn_cvfs_isNeedDevName_005576b0(p3fes::EEContext&);
void fn_cvfs_variousProc_00555fa0(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_5_00555f90(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncmp_00524670(p3fes::EEContext&);
void fn_sub_555918_00555918(p3fes::EEContext&);
void fn_sub_555D10_00555d10(p3fes::EEContext&);
void fn_sub_555D70_00555d70(p3fes::EEContext&);
void fn_sub_555E48_00555e48(p3fes::EEContext&);
void fn_sub_555F10_00555f10(p3fes::EEContext&);
void fn_sub_556170_00556170(p3fes::EEContext&);
void fn_sub_5561D8_005561d8(p3fes::EEContext&);
void fn_sub_556548_00556548(p3fes::EEContext&);
void fn_sub_5565B0_005565b0(p3fes::EEContext&);
void fn_sub_556790_00556790(p3fes::EEContext&);
void fn_sub_556860_00556860(p3fes::EEContext&);
void fn_sub_5568C0_005568c0(p3fes::EEContext&);
void fn_sub_556A00_00556a00(p3fes::EEContext&);
void fn_sub_556A68_00556a68(p3fes::EEContext&);
void fn_sub_556AC0_00556ac0(p3fes::EEContext&);
void fn_sub_556B28_00556b28(p3fes::EEContext&);
void fn_sub_556BE8_00556be8(p3fes::EEContext&);
void fn_sub_556C90_00556c90(p3fes::EEContext&);
void fn_sub_556DA0_00556da0(p3fes::EEContext&);
void fn_sub_556E78_00556e78(p3fes::EEContext&);
void fn_sub_556ED0_00556ed0(p3fes::EEContext&);
void fn_sub_556F90_00556f90(p3fes::EEContext&);
void fn_sub_557050_00557050(p3fes::EEContext&);
void fn_sub_557110_00557110(p3fes::EEContext&);
void fn_sub_557198_00557198(p3fes::EEContext&);
void fn_sub_5571C0_005571c0(p3fes::EEContext&);
void fn_sub_557228_00557228(p3fes::EEContext&);
void fn_sub_557350_00557350(p3fes::EEContext&);
void fn_sub_557460_00557460(p3fes::EEContext&);
void fn_sub_557520_00557520(p3fes::EEContext&);
void fn_sub_557798_00557798(p3fes::EEContext&);
void fn_sub_5577B8_005577b8(p3fes::EEContext&);
void fn_sub_557850_00557850(p3fes::EEContext&);
void fn_sub_557908_00557908(p3fes::EEContext&);
void fn_sub_5579C8_005579c8(p3fes::EEContext&);
void fn_sub_557A28_00557a28(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace cri2;

// 0x00555B10 cvFsAddDev -- 144 bytes; frame 0x10: ra sp+0x0
// register a device (name, interface getter); give it the error callback. ["cvFsAddDev"]
void cvFsAddDev(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00555b10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7A0000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 2208);  // "X9|"
    a2 = a1;
    lw(v1, v0, 0);  // 0x7A08A0
    ld(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00555b30
        charge(ctx, 4);
        a0 = 0x7C0000;
        a0 = addiu(a0, 14736);  // "cvFsAddDev #1:illegal device name"
        sp = addiu(sp, 0x10);
        gen::fn_sub_555918_00555918(ctx);  // tail call
        return;
    }
    // 0x00555b40
    charge(ctx, 2);
    if (a2 == 0) {
        // 0x00555b48
        charge(ctx, 4);
        a0 = 0x7C0000;
        a0 = addiu(a0, 14776);  // "cvFsAddDev #2:illegal I/F func name"
        sp = addiu(sp, 0x10);
        gen::fn_sub_555918_00555918(ctx);  // tail call
        return;
    }
    // 0x00555b58
    charge(ctx, 4);
    jal(ctx, 0x555B58u, gen::fn_cvfs_addDevice_00555ba0);
    if (v0 == 0) {
        // 0x00555b68
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 14816);  // "cvFsAddDev #3:failed added a device"
        sp = addiu(sp, 0x10);
        gen::fn_sub_555918_00555918(ctx);  // tail call
        return;
    }
    lw(v0, v0, cvfs::kIfEntryErrFn);
    // 0x00555b80
    charge(ctx, 2);
    a1 = 0;
    if (v0 != 0) {
        // 0x00555b88
        charge(ctx, 3);
        a0 = 0x550000;
        a0 = addiu(a0, 22760);  // &sub_5558E8
        jalr(ctx, 0x555B8Cu, v0.u());
    }
    // 0x00555b94 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00555BA0 cvfs_addDevice -- 212 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// add a device to the first free slot unless the name is taken (upper-cased name). [cvfs_addDevice]
void cvfs_addDevice(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00555ba0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s1 = a0;
    jal(ctx, 0x555BB8u, gen::fn_sub_555D10_00555d10);
    jalr(ctx, 0x555BC0u, s0.u());
    a0 = s1;
    s2 = v0;
    s0 = 0;
    jal(ctx, 0x555BD0u, gen::fn_cvfs_getDevice_00555c78);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = s2;
    if (!cc) {
        // 0x00555be0
        charge(ctx, 5);
        a0 = 0x990000;
        v1 = addiu(a0, 30296);  // &0x997658
        lb(v0, v1, 4);  // 0x99765C
        v1 = addiu(v1, 4);  // &0x99765C
        if (v0 != 0) {
            // 0x00555bf4
            charge(ctx, 1);
            s0 = addiu(s0, 1);
            for (;;) {
                // 0x00555bf8
                charge(ctx, 3);
                v0 = slti(s0, 32);
                v1 = addiu(v1, 16);
                if (v0 != 0) {
                    // 0x00555c04
                    charge(ctx, 6);
                    lb(v0, v1, 0);
                    if (v0 != 0) {
                        s0 = addiu(s0, 1);
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
        }
        // 0x00555c1c
        charge(ctx, 3);
        v1 = 32;
        v0 = 0;
        if (s0 != v1) {
            // 0x00555c28
            charge(ctx, 13);
            v0 = addiu(a0, 30296);
            a0 = s1;
            s0 = sll(s0, 4);
            v1 = addiu(v0, 4);
            v0 = addu(s0, v0);
            s0 = addu(s0, v1);
            link(ctx, 0x555C40u);  // $ra first: the delay slot below depends on it
            sw(s2, v0, 0);
            call(ctx, gen::fn_strlen_00524388);
            a0 = s0;
            a1 = s1;
            a2 = addiu(v0, 1);
            jal(ctx, 0x555C50u, gen::fn_memcpy_00521250);
            v0 = s2;
        }
    }
    // 0x00555c5c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00555C78 cvfs_getDevice -- 152 bytes; frame 0x40: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s0 sp+0x0, ra sp+0x30
// the interface of the device whose name starts with the given one (strncmp over 32 slots), or 0. [cvfs_getDevice]
void cvfs_getDevice(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00555c78
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x8);
    s1 = 0;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x30);
    s4 = a0;
    jal(ctx, 0x555C9Cu, gen::fn_strlen_00524388);
    s3 = v0;
    v0 = 0x990000;
    s2 = addiu(v0, 30300);  // &0x99765C
    s5 = addiu(s2, -4);  // &0x997658
    s0 = sll(s1, 4);
    for (;;) {
        // 0x00555cb8
        charge(ctx, 7);
        s1 = addiu(s1, 1);
        a0 = s4;
        a1 = addu(s0, s2);
        a2 = s3;
        jal(ctx, 0x555CC4u, gen::fn_strncmp_00524670);
        v1 = sltiu(s1, 32);
        if (v0 == 0) {
            goto L_00555cd4_2;
        }
        // 0x00555ce0
        charge(ctx, 2);
        s0 = sll(s1, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00555ce8
    charge(ctx, 1);
    v0 = 0;
    // 0x00555cec (the shared epilogue, written out on this path)
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
L_00555cd4_2:
    charge(ctx, 3);
    v1 = addu(s0, s5);
    lw(v0, v1, 0);
    // 0x00555cec (the shared epilogue, written out on this path)
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

// 0x00555D70 sub_555D70 -- 212 bytes; frame 0x40: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// remove a device: clear the first byte of its name. [cvFsDelDev]
void sub_555D70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00555d70
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x30);
    if (s2 == 0) {
        // 0x00555d98
        charge(ctx, 11);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 14856);  // "cvFsDelDev #1:illegal device name"
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        gen::fn_sub_555918_00555918(ctx);  // tail call
        return;
    }
    // 0x00555dd8
    charge(ctx, 8);
    s0 = 0;
    jal(ctx, 0x555DD8u, gen::fn_strlen_00524388);
    s4 = v0;
    v0 = 0x990000;
    s1 = addiu(v0, 30300);  // &0x99765C
    s5 = s1;
    a1 = s1;
    for (;;) {
        // 0x00555df8
        charge(ctx, 8);
        s1 = addiu(s1, 16);
        a0 = s2;
        a2 = s4;
        s3 = sll(s0, 4);
        s0 = addiu(s0, 1);
        jal(ctx, 0x555E08u, gen::fn_strncmp_00524670);
        v1 = sltiu(s0, 32);
        if (v0 == 0) {
            backedge(ctx);
            goto L_00555dc8;
        }
        // 0x00555e18
        charge(ctx, 2);
        a1 = s1;
        if (v1 != 0) {
            backedge(ctx);
            continue;
        }
        break;
    }
    // 0x00555e20 (the shared epilogue, written out on this path)
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
L_00555dc8:
    charge(ctx, 4);
    v0 = addiu(s5, -4);
    v0 = addu(s3, v0);
    sb(zero, v0, 4);
    // 0x00555e20 (the shared epilogue, written out on this path)
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

// 0x00555E48 sub_555E48 -- 196 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// set the default device (upper-cased; must be registered; "" clears it). [cvFsSetDefDev]
void sub_555E48(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00555e48
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    if (s0 == 0) {
        // 0x00555e60
        charge(ctx, 7);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 14896);  // "cvFsSetDefDev #1:illegal device name"
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_555918_00555918(ctx);  // tail call
        return;
    }
    // 0x00555e80
    charge(ctx, 5);
    jal(ctx, 0x555E80u, gen::fn_strlen_00524388);
    s1 = v0;
    a0 = s0;
    if (s1 == 0) {
        // 0x00555e94
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        v0 = 0x990000;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sb(zero, v0, 30808);  // 0x997858
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00555eb0
    charge(ctx, 11);
    jal(ctx, 0x555EB0u, gen::fn_sub_555D10_00555d10);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x555EBCu, gen::fn_sub_555F10_00555f10);
    a0 = 0x990000;
    v1 = 1;
    a0 = addiu(a0, 30808);  // &0x997858
    a1 = s0;
    a2 = addiu(s1, 1);
    if (v0 == v1) {
        // 0x00555edc
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_memcpy_00521250(ctx);  // tail call
        return;
    }
    // 0x00555ef0
    charge(ctx, 7);
    a0 = 0x7C0000;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a0 = addiu(a0, 14936);  // "cvFsSetDefDev #2:unknown device name"
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_555918_00555918(ctx);  // tail call
}

// 0x00555F10 sub_555F10 -- 124 bytes; frame 0x30: ra sp+0x20, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18
// is a device of that name registered (1 / 0). [cvfs_isExistDev]
void sub_555F10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00555f10
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x990000;
    sd(ra, sp, 0x20);
    sd(s0, sp, 0x0);
    s0 = 0;
    sd(s1, sp, 0x8);
    s1 = addiu(v0, 30300);  // &0x99765C
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = a0;
    a1 = s1;
    for (;;) {
        // 0x00555f40
        charge(ctx, 6);
        s1 = addiu(s1, 16);
        a0 = s3;
        a2 = s2;
        jal(ctx, 0x555F48u, gen::fn_strncmp_00524670);
        s0 = addiu(s0, 1);
        if (v0 == 0) {
            goto L_00555f58_2;
        }
        // 0x00555f60
        charge(ctx, 3);
        v0 = slti(s0, 32);
        a1 = s1;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00555f6c
    charge(ctx, 1);
    v0 = 0;
    // 0x00555f70 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    return;
L_00555f58_2:
    charge(ctx, 2);
    v0 = 1;
    // 0x00555f70 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00555FA0 cvfs_variousProc -- 168 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// resolve a split path: the named device, else the default device (the path then keeps its "DEV:" part).
//   [cvfs_variousProc]
void cvfs_variousProc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00555fa0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    lb(v0, s1, 0);
    s3 = a2;
    if (v0 == 0) {
        // 0x00555fcc
        charge(ctx, 5);
        jal(ctx, 0x555FCCu, gen::fn_cvfs_getDefDev_00556330);
        lb(v1, s1, 0);
        v0 = 0;
        if (v1 != 0) {
            goto L_00555fe0;
        }
        // 0x0055602c (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_00555fe0:
    charge(ctx, 8);
    a1 = s2;
    a0 = s1;
    jal(ctx, 0x555FE4u, gen::fn_cvfs_addDevName_00557700);
    a0 = s1;
    jal(ctx, 0x555FECu, gen::fn_cvfs_getDevice_00555c78);
    s0 = v0;
    a0 = s1;
    if (s0 == 0) {
        // 0x00556000
        charge(ctx, 8);
        jal(ctx, 0x556000u, gen::fn_cvfs_getDefDev_00556330);
        a0 = s1;
        jal(ctx, 0x556008u, gen::fn_cvfs_getDevice_00555c78);
        a0 = s2;
        s0 = v0;
        a1 = s3;
        if (s0 != 0) {
            // 0x00556020
            charge(ctx, 2);
            jal(ctx, 0x556020u, gen::fn_strcpy_00524270);
            goto L_00556028;
        }
        // 0x0055602c (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_00556028:
    charge(ctx, 1);
    v0 = s0;
    // 0x0055602c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00556048 cvFsOpen -- 296 bytes; frame 0x290: s1 sp+0x268, s3 sp+0x278, s4 sp+0x280, s0 sp+0x260, s2 sp+0x270, ra sp+0x288
// open a file: split "DEV:file", take a handle, resolve the device, call its Open. ["cvFsOpen"]
void cvFsOpen(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00556048
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x290);
    sd(s1, sp, 0x268);
    s1 = a0;
    sd(s3, sp, 0x278);
    s3 = a1;
    sd(s4, sp, 0x280);
    s4 = a2;
    sd(s0, sp, 0x260);
    sd(s2, sp, 0x270);
    sd(ra, sp, 0x288);
    if (s1 == 0) {
        // 0x00556074
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 14976);  // "cvFsOpen #1:illegal file name"
        goto L_00556144;
    }
    // 0x00556080
    charge(ctx, 8);
    s2 = addiu(sp, 0x130);
    a0 = sp;
    a1 = s2;
    a2 = s1;
    jal(ctx, 0x55608Cu, gen::fn_cvfs_getDevName_005561e8);
    lb(v0, sp, 0x130);
    a0 = 0x7C0000;
    if (v0 == 0) {
        // 0x005560a0
        charge(ctx, 2);
        a0 = addiu(a0, 14976);
        goto L_00556144;
    }
    // 0x005560a8
    charge(ctx, 5);
    jal(ctx, 0x5560A8u, gen::fn_sub_556170_00556170);
    s0 = v0;
    a2 = s1;
    if (s0 == 0) {
        // 0x005560bc
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 15008);  // "cvFsOpen #3:failed handle alloced"
        goto L_00556144;
    }
    // 0x005560c8
    charge(ctx, 5);
    a0 = sp;
    a1 = s2;
    jal(ctx, 0x5560CCu, gen::fn_cvfs_variousProc_00555fa0);
    sw(v0, s0, cvfs::kHIf);
    if (v0 == 0) {
        // 0x005560dc
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x5560DCu, gen::fn_sub_5561D8_005561d8);
        a0 = 0x7C0000;
        a0 = addiu(a0, 15080);  // "cvFsOpen #4:device not found"
        goto L_00556144;
    }
    // 0x005560f0
    charge(ctx, 3);
    lw(v0, v0, cvfs::kIfOpen);
    a1 = s3;
    if (v0 == 0) {
        // 0x00556110
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x556110u, gen::fn_sub_5561D8_005561d8);
        a0 = 0x7C0000;
        a0 = addiu(a0, 15112);  // "cvFsOpen #5:vtbl error"
    L_00556144:
        charge(ctx, 3);
        jal(ctx, 0x556144u, gen::fn_sub_555918_00555918);
        v0 = 0;
    } else {
        // 0x005560fc
        charge(ctx, 5);
        a0 = s2;
        a2 = s4;
        jalr(ctx, 0x556100u, v0.u());
        sw(v0, s0, cvfs::kHFile);
        // 0x00556128
        charge(ctx, 3);
        lw(v0, s0, cvfs::kHFile);
        if (v0 == 0) {
            // 0x00556134
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x556134u, gen::fn_sub_5561D8_005561d8);
            a0 = 0x7C0000;
            a0 = addiu(a0, 15136);  // "cvFsOpen #6:open failed"
            goto L_00556144;
        }
        v0 = s0;
    }
    // 0x00556150 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x260);
    ld(s1, sp, 0x268);
    ld(s2, sp, 0x270);
    ld(s3, sp, 0x278);
    ld(s4, sp, 0x280);
    ld(ra, sp, 0x288);
    sp = addiu(sp, 0x290);
}

// 0x00556170 sub_556170 -- 100 bytes; leaf frame (no stack)
// the first free file handle of the 40. [cvfs_allocHandle]
void sub_556170(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00556170
    enter(ctx, 6);  // entry check point + this block's cycles
    a1 = 0x990000;
    v0 = addiu(a1, 29976);  // &cvFsHandleTable
    v0 = addiu(v0, 4);  // &0x99751C
    lw(v1, v0, 0);  // 0x99751C
    a0 = 0;
    if (v1 != 0) {
        // 0x00556188
        charge(ctx, 2);
        v1 = v0;
        a0 = addiu(a0, 1);
        for (;;) {
            // 0x00556190
            charge(ctx, 3);
            v0 = slti(a0, 40);
            v1 = addiu(v1, 8);
            if (v0 != 0) {
                // 0x0055619c
                charge(ctx, 6);
                lw(v0, v1, 0);
                if (v0 != 0) {
                    a0 = addiu(a0, 1);
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x005561b4
    charge(ctx, 3);
    v1 = 40;
    v0 = 0;
    if (a0 != v1) {
        // 0x005561c0
        charge(ctx, 3);
        v1 = sll(a0, 3);
        v0 = addiu(a1, 29976);
        v0 = addu(v1, v0);
    }
    // 0x005561cc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005561D8 sub_5561D8 -- 12 bytes; leaf frame (no stack)
// release a file handle. [cvfs_freeHandle]
void sub_5561D8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x005561d8
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(zero, a0, cvfs::kHIf);
    sw(zero, a0, cvfs::kHFile);
}

// 0x00556398 cvFsClose -- 116 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// close: the device's Close, release the handle. ["cvFsClose"]
void cvFsClose(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00556398
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x005563ac
        charge(ctx, 6);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        a0 = addiu(a0, 15160);  // "cvFsClose #1:handle error"
        sp = addiu(sp, 0x10);
        gen::fn_sub_555918_00555918(ctx);  // tail call
        return;
    }
    // 0x005563c8
    charge(ctx, 4);
    lw(v0, s0, cvfs::kHIf);
    lw(v0, v0, cvfs::kIfClose);
    if (v0 == 0) {
        a0 = 0x7C0000;
        // 0x005563f8
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        a0 = addiu(a0, 15192);
        sp = addiu(sp, 0x10);
        gen::fn_sub_555918_00555918(ctx);  // tail call
        return;
    }
    // 0x005563d8
    charge(ctx, 7);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x5563D8u);  // $ra = the return address
    lw(a0, s0, cvfs::kHFile);
    call_ptr(ctx, jt);
    a0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5561D8_005561d8(ctx);  // tail call
}

// 0x00556410 cvFsTell -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// the device's Tell. ["cvFsTell"]
void cvFsTell(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00556410
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    if (a0 != 0) {
        // 0x00556438
        charge(ctx, 4);
        lw(v0, a0, cvfs::kHIf);
        lw(v0, v0, cvfs::kIfTell);
        if (v0 == 0) {
            a0 = 0x7C0000;
            // 0x00556458
            charge(ctx, 3);
            s0 = 0;
            a0 = addiu(a0, 15248);
            jal(ctx, 0x55645Cu, gen::fn_sub_555918_00555918);
        } else {
            // 0x00556448
            charge(ctx, 4);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x556448u);  // $ra = the return address
            lw(a0, a0, cvfs::kHFile);
            call_ptr(ctx, jt);
            s0 = v0;
        }
        // 0x00556464
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x00556420
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 15216);  // "cvFsTell #1:handle error"
        jal(ctx, 0x556424u, gen::fn_sub_555918_00555918);
        v0 = 0;
    }
    // 0x00556468 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00556478 cvFsSeek -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// the device's Seek. ["cvFsSeek"]
void cvFsSeek(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00556478
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    if (a0 != 0) {
        // 0x005564a0
        charge(ctx, 4);
        lw(v0, a0, cvfs::kHIf);
        lw(v0, v0, cvfs::kIfSeek);
        if (v0 == 0) {
            a0 = 0x7C0000;
            // 0x005564c0
            charge(ctx, 3);
            s0 = 0;
            a0 = addiu(a0, 15304);
            jal(ctx, 0x5564C4u, gen::fn_sub_555918_00555918);
        } else {
            // 0x005564b0
            charge(ctx, 4);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x5564B0u);  // $ra = the return address
            lw(a0, a0, cvfs::kHFile);
            call_ptr(ctx, jt);
            s0 = v0;
        }
        // 0x005564cc
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x00556488
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 15272);  // "cvFsSeek #1:handle error"
        jal(ctx, 0x55648Cu, gen::fn_sub_555918_00555918);
        v0 = 0;
    }
    // 0x005564d0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005564E0 cvFsReqRd -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// the device's read request. ["cvFsReqRd"]
void cvFsReqRd(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005564e0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    if (a0 != 0) {
        // 0x00556508
        charge(ctx, 4);
        lw(v0, a0, cvfs::kHIf);
        lw(v0, v0, cvfs::kIfReqRd);
        if (v0 == 0) {
            a0 = 0x7C0000;
            // 0x00556528
            charge(ctx, 3);
            s0 = 0;
            a0 = addiu(a0, 15360);
            jal(ctx, 0x55652Cu, gen::fn_sub_555918_00555918);
        } else {
            // 0x00556518
            charge(ctx, 4);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x556518u);  // $ra = the return address
            lw(a0, a0, cvfs::kHFile);
            call_ptr(ctx, jt);
            s0 = v0;
        }
        // 0x00556534
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x005564f0
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 15328);  // "cvFsReqRd #1:handle error"
        jal(ctx, 0x5564F4u, gen::fn_sub_555918_00555918);
        v0 = 0;
    }
    // 0x00556538 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00556548 sub_556548 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// the device's write request. [cvFsReqWr]
void sub_556548(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00556548
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = 0;
    sd(ra, sp, 0x8);
    if (a0 != 0) {
        // 0x00556570
        charge(ctx, 4);
        lw(v0, a0, cvfs::kHIf);
        lw(v0, v0, cvfs::kIfReqWr);
        if (v0 == 0) {
            a0 = 0x7C0000;
            // 0x00556590
            charge(ctx, 2);
            a0 = addiu(a0, 15416);
            jal(ctx, 0x556590u, gen::fn_sub_555918_00555918);
        } else {
            // 0x00556580
            charge(ctx, 4);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x556580u);  // $ra = the return address
            lw(a0, a0, cvfs::kHFile);
            call_ptr(ctx, jt);
            s0 = v0;
        }
        // 0x00556598
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x0055655c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 15384);  // "cvFsReqWr #1:handle error"
        jal(ctx, 0x556560u, gen::fn_sub_555918_00555918);
        v0 = 0;
    }
    // 0x0055659c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005565B0 sub_5565B0 -- 88 bytes; frame 0x10: ra sp+0x0
// the device's transfer stop. [cvFsStopTr]
void sub_5565B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005565b0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x005565bc
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 15440);  // "cvFsStopTr #1:handle error"
        sp = addiu(sp, 0x10);
        gen::fn_sub_555918_00555918(ctx);  // tail call
        return;
    }
    // 0x005565d0
    charge(ctx, 4);
    lw(v0, a0, cvfs::kHIf);
    lw(v0, v0, cvfs::kIfStopTr);
    if (v0 == 0) {
        a0 = 0x7C0000;
        // 0x005565f8
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 15472);
        sp = addiu(sp, 0x10);
        gen::fn_sub_555918_00555918(ctx);  // tail call
        return;
    }
    // 0x005565e0
    charge(ctx, 5);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x5565E0u);  // $ra = the return address
    lw(a0, a0, cvfs::kHFile);
    call_ptr(ctx, jt);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00556608 cvFsExecServer -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0, s1 sp+0x8
// every registered device's server. ["cvFsExecServer"]
void cvFsExecServer(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00556608
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x990000;
    sd(ra, sp, 0x10);
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 30296);  // &0x997658
    sd(s1, sp, 0x8);
    s1 = 31;
    lw(v0, s0, 0);  // 0x997658
    for (;;) {
        // 0x00556628
        charge(ctx, 2);
        s0 = addiu(s0, 16);
        if (v0 != 0) {
            // 0x00556630
            charge(ctx, 3);
            lw(v0, v0, cvfs::kIfExecServer);
            if (v0 != 0) {
                // 0x0055663c
                charge(ctx, 2);
                jalr(ctx, 0x55663Cu, v0.u());
                goto L_00556644;
            }
            s1 = addiu(s1, -1);
            goto L_00556648;
        }
    L_00556644:
        charge(ctx, 1);
        s1 = addiu(s1, -1);
    L_00556648:
        charge(ctx, 2);
        if (i64(s1) < 0) {
            break;
        }
        lw(v0, s0, 0);
        backedge(ctx);
    }
    // 0x00556650
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00556668 cvFsGetStat -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// the device's status (3 = error for a bad handle). ["cvFsGetStat"]
void cvFsGetStat(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00556668
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = 3;
    sd(ra, sp, 0x8);
    if (a0 != 0) {
        // 0x00556690
        charge(ctx, 4);
        lw(v0, a0, cvfs::kHIf);
        lw(v0, v0, cvfs::kIfGetStat);
        if (v0 == 0) {
            a0 = 0x7C0000;
            // 0x005566b0
            charge(ctx, 2);
            a0 = addiu(a0, 15536);
            jal(ctx, 0x5566B0u, gen::fn_sub_555918_00555918);
        } else {
            // 0x005566a0
            charge(ctx, 4);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x5566A0u);  // $ra = the return address
            lw(a0, a0, cvfs::kHFile);
            call_ptr(ctx, jt);
            s0 = v0;
        }
        // 0x005566b8
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x0055667c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 15504);  // "cvFsGetStat #1:handle error"
        jal(ctx, 0x556680u, gen::fn_sub_555918_00555918);
        v0 = 3;
    }
    // 0x005566bc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005566D0 cvFsGetFileSize -- 188 bytes; frame 0x280: s0 sp+0x260, s1 sp+0x268, ra sp+0x270
// a file's size through its device. ["cvFsGetFileSize"]
void cvFsGetFileSize(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005566d0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x280);
    sd(s0, sp, 0x260);
    s0 = a0;
    sd(s1, sp, 0x268);
    sd(ra, sp, 0x270);
    if (s0 == 0) {
        // 0x005566e8
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 15568);  // "cvFsGetFileSize #1:illegal file name"
        goto L_0055676c;
    }
    // 0x005566f8
    charge(ctx, 8);
    s1 = addiu(sp, 0x130);
    a0 = sp;
    a1 = s1;
    a2 = s0;
    jal(ctx, 0x556704u, gen::fn_cvfs_getDevName_005561e8);
    lb(v0, sp, 0x130);
    a2 = s0;
    if (v0 == 0) {
        // 0x00556718
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 15568);  // "cvFsGetFileSize #1:illegal file name"
        goto L_0055676c;
    }
    // 0x00556728
    charge(ctx, 6);
    a0 = sp;
    a1 = s1;
    jal(ctx, 0x55672Cu, gen::fn_cvfs_variousProc_00555fa0);
    s0 = v0;
    if (s0 != 0) {
        lw(v0, s0, cvfs::kIfGetFileSize);
    } else {
        // 0x00556740
        charge(ctx, 4);
        a0 = 0x7C0000;
        a0 = addiu(a0, 15648);  // "cvFsGetFileSize #3:device not found"
        jal(ctx, 0x556744u, gen::fn_sub_555918_00555918);
        lw(v0, s0, cvfs::kIfGetFileSize);
    }
    // 0x00556750
    charge(ctx, 2);
    if (v0 == 0) {
        a0 = 0x7C0000;
        // 0x00556768
        charge(ctx, 1);
        a0 = addiu(a0, 15688);
    L_0055676c:
        charge(ctx, 4);
        jal(ctx, 0x55676Cu, gen::fn_sub_555918_00555918);
        v0 = 0;
        ld(s0, sp, 0x260);
    } else {
        // 0x00556758
        charge(ctx, 4);
        a0 = s1;
        jalr(ctx, 0x556758u, v0.u());
        ld(s0, sp, 0x260);
    }
    // 0x0055677c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x268);
    ld(ra, sp, 0x270);
    sp = addiu(sp, 0x280);
}

// 0x00556790 sub_556790 -- 204 bytes; frame 0x280: s0 sp+0x260, s2 sp+0x270, s1 sp+0x268, ra sp+0x278
// a file's size, second form (interface +92). [cvFsGetFileSizeEx]
void sub_556790(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00556790
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x280);
    sd(s0, sp, 0x260);
    s0 = a0;
    sd(s2, sp, 0x270);
    s2 = a1;
    sd(s1, sp, 0x268);
    sd(ra, sp, 0x278);
    if (s0 == 0) {
        // 0x005567b0
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 15720);  // "cvFsGetFileSizeEx #1:illegal file name"
        goto L_00556838;
    }
    // 0x005567c0
    charge(ctx, 8);
    s1 = addiu(sp, 0x130);
    a0 = sp;
    a1 = s1;
    a2 = s0;
    jal(ctx, 0x5567CCu, gen::fn_cvfs_getDevName_005561e8);
    lb(v0, sp, 0x130);
    a2 = s0;
    if (v0 == 0) {
        // 0x005567e0
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 15720);  // "cvFsGetFileSizeEx #1:illegal file name"
        goto L_00556838;
    }
    // 0x005567f0
    charge(ctx, 6);
    a0 = sp;
    a1 = s1;
    jal(ctx, 0x5567F4u, gen::fn_cvfs_variousProc_00555fa0);
    s0 = v0;
    if (s0 != 0) {
        lw(v0, s0, cvfs::kIfGetFileSizeEx);
    } else {
        // 0x00556808
        charge(ctx, 4);
        a0 = 0x7C0000;
        a0 = addiu(a0, 15808);  // "cvFsGetFileSizeEx #3:device not found"
        jal(ctx, 0x55680Cu, gen::fn_sub_555918_00555918);
        lw(v0, s0, cvfs::kIfGetFileSizeEx);
    }
    // 0x00556818
    charge(ctx, 2);
    a0 = s1;
    if (v0 == 0) {
        // 0x00556830
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 15848);  // "cvFsGetFileSizeEx #4:vtbl error"
    L_00556838:
        charge(ctx, 4);
        jal(ctx, 0x556838u, gen::fn_sub_555918_00555918);
        v0 = 0;
        ld(s0, sp, 0x260);
    } else {
        // 0x00556820
        charge(ctx, 4);
        a1 = s2;
        jalr(ctx, 0x556820u, v0.u());
        ld(s0, sp, 0x260);
    }
    // 0x00556848 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x268);
    ld(s2, sp, 0x270);
    ld(ra, sp, 0x278);
    sp = addiu(sp, 0x280);
}

// 0x00556860 sub_556860 -- 92 bytes; frame 0x10: ra sp+0x0
// a file's size by handle (OptFn1 code 300; 0x7FFFFFFF without OptFn1). [cvFsGetFileSizeByHndl]
void sub_556860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00556860
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00556880
        charge(ctx, 5);
        lw(v0, a0, cvfs::kHIf);
        v1 = 0x7FFF0000;
        lw(v0, v0, cvfs::kIfOptFn1);
        v1 = v1 | 0xFFFF;
        if (v0 != 0) {
            // 0x00556894
            charge(ctx, 6);
            lw(a0, a0, cvfs::kHFile);
            a1 = 300;
            a2 = 0;
            a3 = 0;
            jalr(ctx, 0x5568A0u, v0.u());
            v1 = v0;
        }
        // 0x005568ac
        charge(ctx, 1);
        v0 = v1;
    } else {
        // 0x0055686c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 15880);  // "cvFsGetFileSizeByHndl #1:illegal file handle"
        jal(ctx, 0x556870u, gen::fn_sub_555918_00555918);
        v0 = si(-1);
    }
    // 0x005568b0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005568C0 sub_5568C0 -- 320 bytes; frame 0x170: s0 sp+0x130, s4 sp+0x150, s1 sp+0x138, s2 sp+0x140, s3 sp+0x148, s5 sp+0x158, s6 sp+0x160, ra sp+0x168
// a device's free size (the default device when none named). [cvFsGetFreeSize]
void sub_5568C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005568c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x170);
    sd(s0, sp, 0x130);
    s0 = a0;
    sd(s4, sp, 0x150);
    s4 = 0;
    sd(s1, sp, 0x138);
    sd(s2, sp, 0x140);
    sd(s3, sp, 0x148);
    sd(s5, sp, 0x158);
    sd(s6, sp, 0x160);
    sd(ra, sp, 0x168);
    if (s0 != 0) {
        // 0x005568f0
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 == 0) {
            goto L_005568fc;
        }
        // 0x00556920
        charge(ctx, 6);
        jal(ctx, 0x556920u, gen::fn_strlen_00524388);
        a1 = s0;
        a0 = sp;
        a2 = addiu(v0, 1);
        jal(ctx, 0x556930u, gen::fn_memcpy_00521250);
    L_00556938:
        charge(ctx, 5);
        a0 = sp;
        jal(ctx, 0x556938u, gen::fn_strlen_00524388);
        s2 = v0;
        if (i64(s2) > 0) {
            v0 = 0x990000;
            // 0x00556958
            charge(ctx, 6);
            s1 = 0;
            s3 = addiu(v0, 30300);
            s6 = 0x7C0000;
            s5 = addiu(s3, -4);
            s0 = sll(s1, 4);
            for (;;) {
                // 0x00556970
                charge(ctx, 8);
                s1 = addiu(s1, 1);
                a1 = addu(s0, s3);
                s0 = addu(s0, s5);
                a0 = sp;
                a2 = s2;
                jal(ctx, 0x556980u, gen::fn_strncmp_00524670);
                if (v0 != 0) {
                    v0 = slti(s1, 32);
                } else {
                    // 0x00556990
                    charge(ctx, 3);
                    lw(s0, s0, 0);
                    a0 = addiu(s6, 15968);
                    if (s0 == 0) {
                        goto L_005569b8;
                    }
                    // 0x0055699c
                    charge(ctx, 3);
                    lw(s0, s0, cvfs::kIfGetFreeSize);
                    if (s0 == 0) {
                        v0 = slti(s1, 32);
                    } else {
                        // 0x005569a8
                        charge(ctx, 4);
                        jalr(ctx, 0x5569A8u, s0.u());
                        s4 = v0;
                        // 0x005569c8
                        charge(ctx, 1);
                        v0 = slti(s1, 32);
                    }
                    goto L_005569cc;
                }
            L_005569cc:
                charge(ctx, 2);
                s0 = sll(s1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x005569d4
            charge(ctx, 1);
            v0 = s4;
        } else {
            // 0x0055694c
            charge(ctx, 3);
            a0 = 0x7C0000;
            a0 = addiu(a0, 15928);  // "cvFsGetFreeSize #5:device not found"
        L_005569b8:
            charge(ctx, 4);
            jal(ctx, 0x5569B8u, gen::fn_sub_555918_00555918);
            v0 = 0;
        }
        // 0x005569d8 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(s0, sp, 0x130);
        ld(s1, sp, 0x138);
        ld(s2, sp, 0x140);
        ld(s3, sp, 0x148);
        ld(s4, sp, 0x150);
        ld(s5, sp, 0x158);
        ld(s6, sp, 0x160);
        ld(ra, sp, 0x168);
        sp = addiu(sp, 0x170);
        return;
    }
L_005568fc:
    charge(ctx, 5);
    a0 = sp;
    jal(ctx, 0x5568FCu, gen::fn_cvfs_getDefDev_00556330);
    lb(v0, sp, 0x0);
    if (v0 != 0) {
        goto L_00556938;
    }
    // 0x00556910
    charge(ctx, 3);
    a0 = 0x7C0000;
    a0 = addiu(a0, 15928);  // "cvFsGetFreeSize #5:device not found"
    goto L_005569b8;
}

// 0x00556A00 sub_556A00 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// the device's sector length. [cvFsGetSctLen]
void sub_556A00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00556a00
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = 0;
    sd(ra, sp, 0x8);
    if (a0 != 0) {
        // 0x00556a28
        charge(ctx, 4);
        lw(v0, a0, cvfs::kHIf);
        lw(v0, v0, cvfs::kIfGetSctLen);
        if (v0 == 0) {
            a0 = 0x7C0000;
            // 0x00556a48
            charge(ctx, 2);
            a0 = addiu(a0, 16032);
            jal(ctx, 0x556A48u, gen::fn_sub_555918_00555918);
        } else {
            // 0x00556a38
            charge(ctx, 4);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x556A38u);  // $ra = the return address
            lw(a0, a0, cvfs::kHFile);
            call_ptr(ctx, jt);
            s0 = v0;
        }
        // 0x00556a50
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x00556a14
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 16000);  // "cvFsGetSctLen #1:handle error"
        jal(ctx, 0x556A18u, gen::fn_sub_555918_00555918);
        v0 = 0;
    }
    // 0x00556a54 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00556A68 sub_556A68 -- 88 bytes; frame 0x10: ra sp+0x0
// set the device's sector length. [cvFsSetSctLen]
void sub_556A68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00556a68
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00556a74
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 16064);  // "cvFsSetSctLen #3:handle error"
        sp = addiu(sp, 0x10);
        gen::fn_sub_555918_00555918(ctx);  // tail call
        return;
    }
    // 0x00556a88
    charge(ctx, 4);
    lw(v0, a0, cvfs::kHIf);
    lw(v0, v0, cvfs::kIfSetSctLen);
    if (v0 == 0) {
        a0 = 0x7C0000;
        // 0x00556ab0
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 16096);
        sp = addiu(sp, 0x10);
        gen::fn_sub_555918_00555918(ctx);  // tail call
        return;
    }
    // 0x00556a98
    charge(ctx, 5);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x556A98u);  // $ra = the return address
    lw(a0, a0, cvfs::kHFile);
    call_ptr(ctx, jt);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00556AC0 sub_556AC0 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// the device's transferred count. [cvFsGetNumTr]
void sub_556AC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00556ac0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = 0;
    sd(ra, sp, 0x8);
    if (a0 != 0) {
        // 0x00556ae8
        charge(ctx, 4);
        lw(v0, a0, cvfs::kHIf);
        lw(v0, v0, cvfs::kIfGetNumTr);
        if (v0 == 0) {
            a0 = 0x7C0000;
            // 0x00556b08
            charge(ctx, 2);
            a0 = addiu(a0, 16160);
            jal(ctx, 0x556B08u, gen::fn_sub_555918_00555918);
        } else {
            // 0x00556af8
            charge(ctx, 4);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x556AF8u);  // $ra = the return address
            lw(a0, a0, cvfs::kHFile);
            call_ptr(ctx, jt);
            s0 = v0;
        }
        // 0x00556b10
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x00556ad4
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 16128);  // "cvFsGetNumTr #1:handle error"
        jal(ctx, 0x556AD8u, gen::fn_sub_555918_00555918);
        v0 = 0;
    }
    // 0x00556b14 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00556B28 sub_556B28 -- 188 bytes; frame 0x280: s0 sp+0x260, s1 sp+0x268, ra sp+0x270
// change directory through the device. [cvFsChangeDir]
void sub_556B28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00556b28
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x280);
    sd(s0, sp, 0x260);
    s0 = a0;
    sd(s1, sp, 0x268);
    sd(ra, sp, 0x270);
    if (s0 == 0) {
        // 0x00556b40
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 16192);  // "cvFsChangeDir #1:illegal directory name"
        goto L_00556bc4;
    }
    // 0x00556b50
    charge(ctx, 8);
    s1 = addiu(sp, 0x130);
    a0 = sp;
    a1 = s1;
    a2 = s0;
    jal(ctx, 0x556B5Cu, gen::fn_cvfs_getDevName_005561e8);
    lb(v0, sp, 0x130);
    a2 = s0;
    if (v0 == 0) {
        // 0x00556b70
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 16192);  // "cvFsChangeDir #1:illegal directory name"
        goto L_00556bc4;
    }
    // 0x00556b80
    charge(ctx, 6);
    a0 = sp;
    a1 = s1;
    jal(ctx, 0x556B84u, gen::fn_cvfs_variousProc_00555fa0);
    s0 = v0;
    if (s0 != 0) {
        lw(v0, s0, cvfs::kIfChangeDir);
    } else {
        // 0x00556b98
        charge(ctx, 4);
        a0 = 0x7C0000;
        a0 = addiu(a0, 16272);  // "cvFsChangeDir #3:device not found"
        jal(ctx, 0x556B9Cu, gen::fn_sub_555918_00555918);
        lw(v0, s0, cvfs::kIfChangeDir);
    }
    // 0x00556ba8
    charge(ctx, 2);
    if (v0 == 0) {
        a0 = 0x7C0000;
        // 0x00556bc0
        charge(ctx, 1);
        a0 = addiu(a0, 16312);
    L_00556bc4:
        charge(ctx, 4);
        jal(ctx, 0x556BC4u, gen::fn_sub_555918_00555918);
        v0 = si(-1);
        ld(s0, sp, 0x260);
    } else {
        // 0x00556bb0
        charge(ctx, 4);
        a0 = s1;
        jalr(ctx, 0x556BB0u, v0.u());
        ld(s0, sp, 0x260);
    }
    // 0x00556bd4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x268);
    ld(ra, sp, 0x270);
    sp = addiu(sp, 0x280);
}

// 0x00556BE8 sub_556BE8 -- 164 bytes; frame 0x280: s0 sp+0x260, s1 sp+0x268, ra sp+0x270
// does a file exist (through the device). [cvFsIsExistFile]
void sub_556BE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00556be8
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x280);
    sd(s0, sp, 0x260);
    s0 = a0;
    sd(s1, sp, 0x268);
    s1 = addiu(sp, 0x130);
    a0 = sp;
    a2 = s0;
    sd(ra, sp, 0x270);
    a1 = s1;
    jal(ctx, 0x556C08u, gen::fn_cvfs_getDevName_005561e8);
    a0 = 0x7C0000;
    lb(v0, sp, 0x130);
    a0 = addiu(a0, 16344);  // "cvFsIsExistFile #1:illegal file name"
    a2 = s0;
    a1 = s1;
    if (v0 != 0) {
        // 0x00556c28
        charge(ctx, 6);
        a0 = sp;
        jal(ctx, 0x556C28u, gen::fn_cvfs_variousProc_00555fa0);
        a0 = 0x7C0000;
        s0 = v0;
        a0 = addiu(a0, 16424);  // "cvFsIsExistFile #3:device not found"
        if (s0 == 0) {
            // 0x00556c40
            charge(ctx, 2);
            jal(ctx, 0x556C40u, gen::fn_sub_555918_00555918);
        }
        // 0x00556c48
        charge(ctx, 3);
        lw(v0, s0, cvfs::kIfIsExistFile);
        if (v0 == 0) {
            a0 = 0x7C0000;
            // 0x00556c68
            charge(ctx, 1);
            a0 = addiu(a0, 16464);
            goto L_00556c6c;
        }
        // 0x00556c54
        charge(ctx, 4);
        a0 = s1;
        jalr(ctx, 0x556C54u, v0.u());
        ld(s0, sp, 0x260);
        // 0x00556c7c (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x268);
        ld(ra, sp, 0x270);
        sp = addiu(sp, 0x280);
        return;
    }
L_00556c6c:
    charge(ctx, 4);
    jal(ctx, 0x556C6Cu, gen::fn_sub_555918_00555918);
    v0 = 0;
    ld(s0, sp, 0x260);
    // 0x00556c7c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x268);
    ld(ra, sp, 0x270);
    sp = addiu(sp, 0x280);
}

// 0x00556C90 sub_556C90 -- 272 bytes; frame 0x60: s1 sp+0x28, s2 sp+0x30, s3 sp+0x38, s4 sp+0x40, s5 sp+0x48, s6 sp+0x50, s0 sp+0x20, ra sp+0x58
// the number of files on a device (its GetNumFiles, or OptFn1 code 4 for a device that wants its name).
//   [cvFsGetNumFiles]
void sub_556C90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00556c90
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s1, sp, 0x28);
    s1 = 0;
    sd(s2, sp, 0x30);
    s2 = a0;
    sd(s3, sp, 0x38);
    sd(s4, sp, 0x40);
    sd(s5, sp, 0x48);
    sd(s6, sp, 0x50);
    sd(s0, sp, 0x20);
    sd(ra, sp, 0x58);
    s4 = 0;
    jal(ctx, 0x556CBCu, gen::fn_strlen_00524388);
    s5 = v0;
    v0 = 0x990000;
    s3 = addiu(v0, 30300);  // &0x99765C
    s6 = addiu(s3, -4);  // &0x997658
    s0 = sll(s1, 4);
    for (;;) {
        // 0x00556cd8
        charge(ctx, 8);
        s1 = addiu(s1, 1);
        a0 = s2;
        a1 = addu(s0, s3);
        a2 = s5;
        s0 = addu(s0, s6);
        jal(ctx, 0x556CE8u, gen::fn_strncmp_00524670);
        a0 = s2;
        if (v0 == 0) {
            // 0x00556cf8
            charge(ctx, 4);
            link(ctx, 0x556CF8u);  // $ra first: the delay slot below depends on it
            lw(s0, s0, 0);
            call(ctx, gen::fn_cvfs_isNeedDevName_005576b0);
            if (v0 == 0) {
                // 0x00556d40
                charge(ctx, 2);
                v0 = slti(s1, 32);
                if (s0 == 0) {
                    goto L_00556d6c;
                }
                // 0x00556d48
                charge(ctx, 3);
                lw(s0, s0, cvfs::kIfGetNumFiles);
                if (s0 == 0) {
                    goto L_00556d6c;
                }
                goto L_00556d54_8;
            }
            // 0x00556d08
            charge(ctx, 2);
            v0 = slti(s1, 32);
            if (s0 == 0) {
                goto L_00556d6c;
            }
            // 0x00556d10
            charge(ctx, 3);
            lw(v0, s0, cvfs::kIfOptFn1);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = slti(s1, 32);
            if (cc) {
                goto L_00556d6c;
            }
            goto L_00556d1c_5;
        }
        // 0x00556d68
        charge(ctx, 1);
        v0 = slti(s1, 32);
    L_00556d6c:
        charge(ctx, 2);
        s0 = sll(s1, 4);
        if (v0 != 0) {
            backedge(ctx);
            continue;
        }
        break;
    }
    // 0x00556d74 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = s4;
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
    return;
L_00556d1c_5:
    charge(ctx, 9);
    sw(s2, sp, 0x4);
    a0 = sp;
    a1 = 4;
    a2 = 0;
    lw(v0, s0, cvfs::kIfOptFn1);
    a3 = 0;
    jalr(ctx, 0x556D30u, v0.u());
    s4 = v0;
    // 0x00556d74 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = s4;
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
    return;
L_00556d54_8:
    charge(ctx, 4);
    jalr(ctx, 0x556D54u, s0.u());
    s4 = v0;
    // 0x00556d74 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = s4;
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x00556DA0 sub_556DA0 -- 212 bytes; frame 0x290: s0 sp+0x260, s1 sp+0x268, s2 sp+0x270, s3 sp+0x278, s4 sp+0x280, ra sp+0x288
// load directory information through the device. [cvFsLoadDirInfo]
void sub_556DA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00556da0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x290);
    sd(s0, sp, 0x260);
    s0 = a0;
    sd(s1, sp, 0x268);
    s1 = addiu(sp, 0x130);
    sd(s2, sp, 0x270);
    s2 = a1;
    sd(s3, sp, 0x278);
    s3 = a2;
    a0 = sp;
    a1 = s1;
    sd(s4, sp, 0x280);
    sd(ra, sp, 0x288);
    a2 = s0;
    jal(ctx, 0x556DD4u, gen::fn_cvfs_getDevName_005561e8);
    lb(v0, sp, 0x0);
    s4 = 0;
    a0 = sp;
    if (v0 == 0) {
        // 0x00556dec
        charge(ctx, 6);
        jal(ctx, 0x556DECu, gen::fn_cvfs_getDefDev_00556330);
        a0 = 0x7C0000;
        lb(v0, sp, 0x0);
        a0 = addiu(a0, 16384);  // "cvFsIsExistFile #2:illegal device name"
        if (v0 != 0) {
            goto L_00556e18;
        }
        // 0x00556e04
        charge(ctx, 4);
        jal(ctx, 0x556E04u, gen::fn_sub_555918_00555918);
        v0 = 0;
        // 0x00556e54 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(s0, sp, 0x260);
        ld(s1, sp, 0x268);
        ld(s2, sp, 0x270);
        ld(s3, sp, 0x278);
        ld(s4, sp, 0x280);
        ld(ra, sp, 0x288);
        sp = addiu(sp, 0x290);
        return;
    }
L_00556e18:
    charge(ctx, 7);
    a0 = sp;
    a1 = s1;
    jal(ctx, 0x556E1Cu, gen::fn_cvfs_addDevName_00557700);
    a0 = sp;
    jal(ctx, 0x556E24u, gen::fn_cvfs_getDevice_00555c78);
    if (v0 == 0) {
        v0 = s4;
    } else {
        // 0x00556e34
        charge(ctx, 3);
        lw(v0, v0, cvfs::kIfLoadDirInfo);
        a0 = s0;
        if (v0 != 0) {
            // 0x00556e40
            charge(ctx, 4);
            a1 = s2;
            a2 = s3;
            jalr(ctx, 0x556E44u, v0.u());
            s4 = v0;
        }
        // 0x00556e50
        charge(ctx, 1);
        v0 = s4;
    }
    // 0x00556e54 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x260);
    ld(s1, sp, 0x268);
    ld(s2, sp, 0x270);
    ld(s3, sp, 0x278);
    ld(s4, sp, 0x280);
    ld(ra, sp, 0x288);
    sp = addiu(sp, 0x290);
}

// 0x00556E78 sub_556E78 -- 88 bytes; frame 0x10: ra sp+0x0
// the device's maximum byte rate. [cvFsGetMaxByteRate]
void sub_556E78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00556e78
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00556e84
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 16496);  // "cvFsGetMaxByteRate #1:handle error"
        jal(ctx, 0x556E88u, gen::fn_sub_555918_00555918);
        v0 = 0;
        goto L_00556ec4;
    }
    // 0x00556e98
    charge(ctx, 4);
    lw(v0, a0, cvfs::kHIf);
    lw(v0, v0, cvfs::kIfGetMaxByteRate);
    if (v0 == 0) {
        a0 = 0x7C0000;
        // 0x00556eb8
        charge(ctx, 3);
        a0 = addiu(a0, 16536);
        jal(ctx, 0x556EB8u, gen::fn_sub_555918_00555918);
        v0 = 0;
    L_00556ec4:
        charge(ctx, 1);
        ld(ra, sp, 0x0);
    } else {
        // 0x00556ea8
        charge(ctx, 4);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x556EA8u);  // $ra = the return address
        lw(a0, a0, cvfs::kHFile);
        call_ptr(ctx, jt);
        ld(ra, sp, 0x0);
    }
    // 0x00556ec8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00556ED0 sub_556ED0 -- 188 bytes; frame 0x80: s0 sp+0x60, s1 sp+0x68, ra sp+0x70
// make a directory through the device. [cvFsMakeDir]
void sub_556ED0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00556ed0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s0, sp, 0x60);
    s0 = a0;
    sd(s1, sp, 0x68);
    sd(ra, sp, 0x70);
    if (s0 == 0) {
        // 0x00556ee8
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 16576);  // "cvFsMakeDir #1:illegal directory name"
        goto L_00556f6c;
    }
    // 0x00556ef8
    charge(ctx, 8);
    s1 = addiu(sp, 0x30);
    a0 = sp;
    a1 = s1;
    a2 = s0;
    jal(ctx, 0x556F04u, gen::fn_cvfs_getDevName_005561e8);
    lb(v0, sp, 0x30);
    a2 = s0;
    if (v0 == 0) {
        // 0x00556f18
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 16576);  // "cvFsMakeDir #1:illegal directory name"
        goto L_00556f6c;
    }
    // 0x00556f28
    charge(ctx, 6);
    a0 = sp;
    a1 = s1;
    jal(ctx, 0x556F2Cu, gen::fn_cvfs_variousProc_00555fa0);
    s0 = v0;
    if (s0 != 0) {
        lw(v0, s0, cvfs::kIfMakeDir);
    } else {
        // 0x00556f40
        charge(ctx, 4);
        a0 = 0x7C0000;
        a0 = addiu(a0, 16656);  // "cvFsMakeDir #3:device not found"
        jal(ctx, 0x556F44u, gen::fn_sub_555918_00555918);
        lw(v0, s0, cvfs::kIfMakeDir);
    }
    // 0x00556f50
    charge(ctx, 2);
    if (v0 == 0) {
        a0 = 0x7C0000;
        // 0x00556f68
        charge(ctx, 1);
        a0 = addiu(a0, 16688);
    L_00556f6c:
        charge(ctx, 4);
        jal(ctx, 0x556F6Cu, gen::fn_sub_555918_00555918);
        v0 = si(-1);
        ld(s0, sp, 0x60);
    } else {
        // 0x00556f58
        charge(ctx, 4);
        a0 = s1;
        jalr(ctx, 0x556F58u, v0.u());
        ld(s0, sp, 0x60);
    }
    // 0x00556f7c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x68);
    ld(ra, sp, 0x70);
    sp = addiu(sp, 0x80);
}

// 0x00556F90 sub_556F90 -- 188 bytes; frame 0x280: s0 sp+0x260, s1 sp+0x268, ra sp+0x270
// remove a directory through the device. [cvFsRemoveDir]
void sub_556F90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00556f90
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x280);
    sd(s0, sp, 0x260);
    s0 = a0;
    sd(s1, sp, 0x268);
    sd(ra, sp, 0x270);
    if (s0 == 0) {
        // 0x00556fa8
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 16720);  // "cvFsRemoveDir #1:illegal directory name"
        goto L_0055702c;
    }
    // 0x00556fb8
    charge(ctx, 8);
    s1 = addiu(sp, 0x130);
    a0 = sp;
    a1 = s1;
    a2 = s0;
    jal(ctx, 0x556FC4u, gen::fn_cvfs_getDevName_005561e8);
    lb(v0, sp, 0x130);
    a2 = s0;
    if (v0 == 0) {
        // 0x00556fd8
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 16720);  // "cvFsRemoveDir #1:illegal directory name"
        goto L_0055702c;
    }
    // 0x00556fe8
    charge(ctx, 6);
    a0 = sp;
    a1 = s1;
    jal(ctx, 0x556FECu, gen::fn_cvfs_variousProc_00555fa0);
    s0 = v0;
    if (s0 != 0) {
        lw(v0, s0, cvfs::kIfRemoveDir);
    } else {
        // 0x00557000
        charge(ctx, 4);
        a0 = 0x7C0000;
        a0 = addiu(a0, 16800);  // "cvFsRemoveDir #3:device not found"
        jal(ctx, 0x557004u, gen::fn_sub_555918_00555918);
        lw(v0, s0, cvfs::kIfRemoveDir);
    }
    // 0x00557010
    charge(ctx, 2);
    if (v0 == 0) {
        a0 = 0x7C0000;
        // 0x00557028
        charge(ctx, 1);
        a0 = addiu(a0, 16840);
    L_0055702c:
        charge(ctx, 4);
        jal(ctx, 0x55702Cu, gen::fn_sub_555918_00555918);
        v0 = si(-1);
        ld(s0, sp, 0x260);
    } else {
        // 0x00557018
        charge(ctx, 4);
        a0 = s1;
        jalr(ctx, 0x557018u, v0.u());
        ld(s0, sp, 0x260);
    }
    // 0x0055703c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x268);
    ld(ra, sp, 0x270);
    sp = addiu(sp, 0x280);
}

// 0x00557050 sub_557050 -- 188 bytes; frame 0x280: s0 sp+0x260, s1 sp+0x268, ra sp+0x270
// delete a file through the device. [cvFsDeleteFile]
void sub_557050(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00557050
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x280);
    sd(s0, sp, 0x260);
    s0 = a0;
    sd(s1, sp, 0x268);
    sd(ra, sp, 0x270);
    if (s0 == 0) {
        // 0x00557068
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 16872);  // "cvFsDeleteFile #1:illegal file name"
        goto L_005570ec;
    }
    // 0x00557078
    charge(ctx, 8);
    s1 = addiu(sp, 0x130);
    a0 = sp;
    a1 = s1;
    a2 = s0;
    jal(ctx, 0x557084u, gen::fn_cvfs_getDevName_005561e8);
    lb(v0, sp, 0x130);
    a2 = s0;
    if (v0 == 0) {
        // 0x00557098
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 16872);  // "cvFsDeleteFile #1:illegal file name"
        goto L_005570ec;
    }
    // 0x005570a8
    charge(ctx, 6);
    a0 = sp;
    a1 = s1;
    jal(ctx, 0x5570ACu, gen::fn_cvfs_variousProc_00555fa0);
    s0 = v0;
    if (s0 != 0) {
        lw(v0, s0, cvfs::kIfDeleteFile);
    } else {
        // 0x005570c0
        charge(ctx, 4);
        a0 = 0x7C0000;
        a0 = addiu(a0, 16952);  // "cvFsDeleteFile #3:device not found"
        jal(ctx, 0x5570C4u, gen::fn_sub_555918_00555918);
        lw(v0, s0, cvfs::kIfDeleteFile);
    }
    // 0x005570d0
    charge(ctx, 2);
    if (v0 == 0) {
        a0 = 0x7C0000;
        // 0x005570e8
        charge(ctx, 1);
        a0 = addiu(a0, 16992);
    L_005570ec:
        charge(ctx, 4);
        jal(ctx, 0x5570ECu, gen::fn_sub_555918_00555918);
        v0 = si(-1);
        ld(s0, sp, 0x260);
    } else {
        // 0x005570d8
        charge(ctx, 4);
        a0 = s1;
        jalr(ctx, 0x5570D8u, v0.u());
        ld(s0, sp, 0x260);
    }
    // 0x005570fc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x268);
    ld(ra, sp, 0x270);
    sp = addiu(sp, 0x280);
}

// 0x00557110 sub_557110 -- 132 bytes; frame 0x10: ra sp+0x0
// the device name of a file handle (the slot whose interface matches). [cvFsGetDevName]
void sub_557110(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00557110
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00557130
        charge(ctx, 7);
        v0 = 0x990000;
        lw(a0, a0, cvfs::kHIf);
        v1 = addiu(v0, 30296);  // &0x997658
        a2 = 0;
        lw(v0, v1, 0);  // 0x997658
        a1 = 0;
        if (v0 != a0) {
            // 0x0055714c
            charge(ctx, 3);
            a3 = v1;
            a2 = addiu(a2, 1);
            for (;;) {
                // 0x00557158
                charge(ctx, 4);
                a1 = sll(a2, 4);
                v0 = slti(a2, 32);
                v1 = addu(a1, a3);
                if (v0 != 0) {
                    // 0x00557168
                    charge(ctx, 5);
                    lw(v0, v1, 0);
                    if (v0 != a0) {
                        a2 = addiu(a2, 1);
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
        }
        // 0x0055717c
        charge(ctx, 3);
        v0 = 0x990000;
        v0 = addiu(v0, 30300);  // &0x99765C
        v0 = addu(v0, a1);
    } else {
        // 0x0055711c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17024);  // "cvFsGetDevName #1:vtbl error"
        jal(ctx, 0x557120u, gen::fn_sub_555918_00555918);
        v0 = 0;
    }
    // 0x00557188 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00557198 sub_557198 -- 40 bytes; leaf frame (no stack)
// set the cvFs error callback and its object (0 clears both). [cvFsEntryErrFunc]
void sub_557198(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00557198
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    if (a0 != 0) {
        // 0x005571b0
        charge(ctx, 4);
        v1 = 0x7A0000;
        sw(a0, v0, 2212);
        sw(a1, v1, 2216);  // 0x7A08A8
        return;
    }
    // 0x005571a0
    charge(ctx, 4);
    v1 = 0x7A0000;
    sw(zero, v0, 2212);
    sw(zero, v1, 2216);  // 0x7A08A8
}

// 0x005571C0 sub_5571C0 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// the device's OptFn1 with the handle's file. [cvFsOptFn1]
void sub_5571C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005571c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = 0;
    sd(ra, sp, 0x8);
    if (a0 != 0) {
        // 0x005571e8
        charge(ctx, 4);
        lw(v0, a0, cvfs::kHIf);
        lw(v0, v0, cvfs::kIfOptFn1);
        if (v0 == 0) {
            a0 = 0x7C0000;
            // 0x00557208
            charge(ctx, 2);
            a0 = addiu(a0, 17088);
            jal(ctx, 0x557208u, gen::fn_sub_555918_00555918);
        } else {
            // 0x005571f8
            charge(ctx, 4);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x5571F8u);  // $ra = the return address
            lw(a0, a0, cvfs::kHFile);
            call_ptr(ctx, jt);
            s0 = v0;
        }
        // 0x00557210
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x005571d4
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17056);  // "cvFsOptFn1 #1:handle error"
        jal(ctx, 0x5571D8u, gen::fn_sub_555918_00555918);
        v0 = 0;
    }
    // 0x00557214 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00557228 sub_557228 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// the device's OptFn2 with the handle's file. [cvFsOptFn2]
void sub_557228(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00557228
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = 0;
    sd(ra, sp, 0x8);
    if (a0 != 0) {
        // 0x00557250
        charge(ctx, 4);
        lw(v0, a0, cvfs::kHIf);
        lw(v0, v0, cvfs::kIfOptFn2);
        if (v0 == 0) {
            a0 = 0x7C0000;
            // 0x00557270
            charge(ctx, 2);
            a0 = addiu(a0, 17152);
            jal(ctx, 0x557270u, gen::fn_sub_555918_00555918);
        } else {
            // 0x00557260
            charge(ctx, 4);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x557260u);  // $ra = the return address
            lw(a0, a0, cvfs::kHFile);
            call_ptr(ctx, jt);
            s0 = v0;
        }
        // 0x00557278
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x0055723c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17120);  // "cvFsOptFn2 #1:handle error"
        jal(ctx, 0x557240u, gen::fn_sub_555918_00555918);
        v0 = 0;
    }
    // 0x0055727c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00557290 cvFsSetCurVolume -- 188 bytes; frame 0x40: s0 sp+0x20, s1 sp+0x28, ra sp+0x30
// select a device's current volume (OptFn1 code 1). ["cvFsSetCurVolume"]
void cvFsSetCurVolume(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00557290
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x20);
    s0 = a1;
    sd(s1, sp, 0x28);
    sd(ra, sp, 0x30);
    if (a0 == 0) {
        // 0x005572a8
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17184);  // "cvFsSetCurVolume #1:illegal device name"
        goto L_005572f4;
    }
    // 0x005572b8
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x005572c0
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17224);  // "cvFsSetCurVolume #2:illegal image handle"
        goto L_005572f4;
    }
    // 0x005572d0
    charge(ctx, 7);
    jal(ctx, 0x5572D0u, gen::fn_cvfs_getDevice_00555c78);
    a1 = 0;
    s1 = v0;
    a0 = sp;
    a2 = 20;
    if (s1 != 0) {
        // 0x00557308
        charge(ctx, 10);
        jal(ctx, 0x557308u, gen::fn_memset_00521408);
        v0 = si(-1);
        sw(s0, sp, 0x0);
        a0 = sp;
        a1 = 1;
        a2 = 0;
        lw(v1, s1, cvfs::kIfOptFn1);
        a3 = 0;
        if (v1 != 0) {
            // 0x00557330
            charge(ctx, 2);
            jalr(ctx, 0x557330u, v1.u());
        }
    } else {
        // 0x005572ec
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17272);  // "cvFsSetCurVolume #3:device not found"
    L_005572f4:
        charge(ctx, 4);
        jal(ctx, 0x5572F4u, gen::fn_sub_555918_00555918);
        v0 = si(-1);
    }
    // 0x00557338 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00557350 sub_557350 -- 8 bytes; leaf frame (no stack)
// returns 0 (`jr $ra` + clear). [cvfs_nop]
void sub_557350(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00557350
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00557358 cvFsAddVolumeEx -- 264 bytes; frame 0x50: s1 sp+0x28, s2 sp+0x30, s3 sp+0x38, s0 sp+0x20, ra sp+0x40
// add a volume to a device (OptFn1 code 2: image handle, name, mode). ["cvFsAddVolumeEx"]
void cvFsAddVolumeEx(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00557358
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s1, sp, 0x28);
    s1 = a2;
    sd(s2, sp, 0x30);
    s2 = a1;
    sd(s3, sp, 0x38);
    s3 = a3;
    sd(s0, sp, 0x20);
    sd(ra, sp, 0x40);
    if (a0 == 0) {
        // 0x00557380
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17312);  // "cvFsAddVolumeEx #1:illegal device name"
        jal(ctx, 0x557384u, gen::fn_sub_555918_00555918);
        v0 = si(-1);
        goto L_00557444;
    }
    // 0x00557398
    charge(ctx, 2);
    if (s2 == 0) {
        // 0x005573a0
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17352);  // "cvFsAddVolumeEx #2:illegal volume name"
        jal(ctx, 0x5573A4u, gen::fn_sub_555918_00555918);
        v0 = si(-1);
        goto L_00557444;
    }
    // 0x005573b8
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x005573c0
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17392);  // "cvFsAddVolumeEx #3:illegal image handle"
        jal(ctx, 0x5573C4u, gen::fn_sub_555918_00555918);
        v0 = si(-1);
        goto L_00557444;
    }
    // 0x005573d8
    charge(ctx, 5);
    jal(ctx, 0x5573D8u, gen::fn_cvfs_getDevice_00555c78);
    s0 = v0;
    if (s0 == 0) {
        // 0x005573ec
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17432);  // "cvFsAddVolumeEx #3:device not found"
        jal(ctx, 0x5573F0u, gen::fn_sub_555918_00555918);
        v0 = si(-1);
        goto L_00557444;
    }
    a0 = sp;
    // 0x00557400
    charge(ctx, 9);
    a1 = 0;
    a2 = 20;
    jal(ctx, 0x557404u, gen::fn_memset_00521408);
    sw(s1, sp, 0x0);
    sw(s2, sp, 0x4);
    sw(s3, sp, 0x8);
    lw(v0, s0, cvfs::kIfOptFn1);
    a0 = sp;
    if (v0 == 0) {
        // 0x00557440
        charge(ctx, 1);
        v0 = si(-1);
    L_00557444:
        charge(ctx, 1);
        ld(s0, sp, 0x20);
    } else {
        // 0x00557424
        charge(ctx, 6);
        a1 = 2;
        a2 = 0;
        a3 = 0;
        jalr(ctx, 0x55742Cu, v0.u());
        ld(s0, sp, 0x20);
    }
    // 0x00557448 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00557460 sub_557460 -- 188 bytes; frame 0x40: s0 sp+0x20, s1 sp+0x28, ra sp+0x30
// remove a volume (OptFn1 code 3). [cvFsDelVolume]
void sub_557460(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00557460
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x20);
    s0 = a1;
    sd(s1, sp, 0x28);
    sd(ra, sp, 0x30);
    if (a0 == 0) {
        // 0x00557478
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17472);  // "cvFsDelVolume #1:illegal device name"
        goto L_005574c4;
    }
    // 0x00557488
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x00557490
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17512);  // "cvFsDelVolume #2:illegal volume name"
        goto L_005574c4;
    }
    // 0x005574a0
    charge(ctx, 7);
    jal(ctx, 0x5574A0u, gen::fn_cvfs_getDevice_00555c78);
    a1 = 0;
    s1 = v0;
    a0 = sp;
    a2 = 20;
    if (s1 != 0) {
        // 0x005574d8
        charge(ctx, 10);
        jal(ctx, 0x5574D8u, gen::fn_memset_00521408);
        v0 = si(-1);
        sw(s0, sp, 0x4);
        a0 = sp;
        a1 = 3;
        a2 = 0;
        lw(v1, s1, cvfs::kIfOptFn1);
        a3 = 0;
        if (v1 != 0) {
            // 0x00557500
            charge(ctx, 2);
            jalr(ctx, 0x557500u, v1.u());
        }
    } else {
        // 0x005574bc
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17552);  // "cvFsDelVolume #3:device not found"
    L_005574c4:
        charge(ctx, 4);
        jal(ctx, 0x5574C4u, gen::fn_sub_555918_00555918);
        v0 = si(-1);
    }
    // 0x00557508 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00557520 sub_557520 -- 204 bytes; frame 0x40: s0 sp+0x20, s2 sp+0x30, s1 sp+0x28, ra sp+0x38
// volume information (OptFn1 code 5). [cvFsGetVolumeInfo]
void sub_557520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00557520
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x20);
    s0 = a1;
    sd(s2, sp, 0x30);
    s2 = a2;
    sd(s1, sp, 0x28);
    sd(ra, sp, 0x38);
    if (a0 == 0) {
        // 0x00557540
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17592);  // "cvFsGetVolumeInfo #1:illegal device name"
        goto L_0055758c;
    }
    // 0x00557550
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x00557558
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17640);  // "cvFsGetVolumeInfo #2:illegal volume name"
        goto L_0055758c;
    }
    // 0x00557568
    charge(ctx, 7);
    jal(ctx, 0x557568u, gen::fn_cvfs_getDevice_00555c78);
    a1 = 0;
    s1 = v0;
    a0 = sp;
    a2 = 20;
    if (s1 != 0) {
        // 0x005575a0
        charge(ctx, 11);
        jal(ctx, 0x5575A0u, gen::fn_memset_00521408);
        v0 = si(-1);
        sw(s0, sp, 0x4);
        a0 = sp;
        sw(s2, sp, 0x8);
        a1 = 5;
        a2 = 0;
        lw(v1, s1, cvfs::kIfOptFn1);
        a3 = 0;
        if (v1 != 0) {
            // 0x005575cc
            charge(ctx, 2);
            jalr(ctx, 0x5575CCu, v1.u());
        }
    } else {
        // 0x00557584
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17688);  // "cvFsGetVolumeInfo #3:device not found"
    L_0055758c:
        charge(ctx, 4);
        jal(ctx, 0x55758Cu, gen::fn_sub_555918_00555918);
        v0 = si(-1);
    }
    // 0x005575d4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x005575F0 cvFsSetDefVol -- 192 bytes; frame 0x40: s0 sp+0x20, s1 sp+0x28, ra sp+0x30
// set a device's default volume (OptFn1 code 6). ["cvFsSetDefVol"]
void cvFsSetDefVol(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005575f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x20);
    s0 = a1;
    sd(s1, sp, 0x28);
    sd(ra, sp, 0x30);
    if (a0 != 0) {
        // 0x00557620
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x00557640
            charge(ctx, 7);
            jal(ctx, 0x557640u, gen::fn_cvfs_getDevice_00555c78);
            a1 = 0;
            s1 = v0;
            a0 = sp;
            a2 = 20;
            if (s1 != 0) {
                // 0x00557670
                charge(ctx, 9);
                jal(ctx, 0x557670u, gen::fn_memset_00521408);
                a1 = 6;
                sw(s0, sp, 0x4);
                a0 = sp;
                a2 = 0;
                lw(v0, s1, cvfs::kIfOptFn1);
                a3 = 0;
                if (v0 != 0) {
                    // 0x00557694
                    charge(ctx, 2);
                    jalr(ctx, 0x557694u, v0.u());
                }
                // 0x0055769c
                charge(ctx, 1);
                ld(s0, sp, 0x20);
            } else {
                // 0x0055765c
                charge(ctx, 5);
                a0 = 0x7C0000;
                a0 = addiu(a0, 17808);  // "cvFsSetDefVol #3:device not found"
                jal(ctx, 0x557660u, gen::fn_sub_555918_00555918);
                ld(s0, sp, 0x20);
            }
        } else {
            // 0x00557628
            charge(ctx, 5);
            a0 = 0x7C0000;
            a0 = addiu(a0, 17768);  // "cvFsSetDefVol #2:illegal volume name"
            jal(ctx, 0x55762Cu, gen::fn_sub_555918_00555918);
            ld(s0, sp, 0x20);
        }
    } else {
        // 0x00557608
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17728);  // "cvFsSetDefVol #1:illegal device name"
        jal(ctx, 0x55760Cu, gen::fn_sub_555918_00555918);
        ld(s0, sp, 0x20);
    }
    // 0x005576a0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x005576B0 cvfs_isNeedDevName -- 80 bytes; frame 0x10: ra sp+0x0
// does the device want "DEV:" in its paths (OptFn1 code 100). [cvfs_isNeedDevName]
void cvfs_isNeedDevName(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005576b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5576B8u, gen::fn_cvfs_getDevice_00555c78);
    v1 = v0;
    ld(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x005576cc
        charge(ctx, 3);
        lw(v0, v1, cvfs::kIfOptFn1);
        a0 = 0;
        if (v0 == 0) {
            // 0x005576f0
            charge(ctx, 2);
            v0 = 0;
            ld(ra, sp, 0x0);
        } else {
            // 0x005576d8
            charge(ctx, 6);
            a1 = 100;
            a2 = 0;
            a3 = 0;
            jalr(ctx, 0x5576E0u, v0.u());
            ld(ra, sp, 0x0);
        }
    }
    // 0x005576f8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00557700 cvfs_addDevName -- 152 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// prefix "DEV:" (sprintf "%s:%s") when the device wants it. [cvfs_addDevName]
void cvfs_addDevName(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00557700
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    if (s0 == 0) {
        // 0x00557720
        charge(ctx, 3);
        jal(ctx, 0x557720u, gen::fn_sceLibgcc32GetErxEntries_5_00555f90);
        s0 = v0;
    }
    // 0x0055772c
    charge(ctx, 8);
    a0 = s0;
    jal(ctx, 0x55772Cu, gen::fn_cvfs_isNeedDevName_005576b0);
    v1 = 0x990000;
    s2 = addiu(v1, 30824);  // &0x997868
    v1 = 1;
    a1 = s1;
    a0 = s2;
    if (v0 != v1) {
        // 0x00557780
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0055774c
    charge(ctx, 13);
    jal(ctx, 0x55774Cu, gen::fn_strcpy_00524270);
    a1 = 0x7C0000;
    a2 = s0;
    ld(s0, sp, 0x0);
    a0 = s1;
    ld(s1, sp, 0x8);
    a3 = s2;
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    a1 = addiu(a1, 17848);  // "%s:%s"
    sp = addiu(sp, 0x20);
    gen::fn_sprintf_00523ac8(ctx);  // tail call
}

// 0x00557798 sub_557798 -- 32 bytes; frame 0x10: ra sp+0x0
// is the device registered (1 / 0). [cvFsIsAvailableDev]
void sub_557798(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00557798
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5577A0u, gen::fn_cvfs_getDevice_00555c78);
    ld(ra, sp, 0x0);
    v0 = sltu(0, v0);
    sp = addiu(sp, 0x10);
}

// 0x005577B8 sub_5577B8 -- 152 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// the 64-bit transferred count (OptFn1 codes 200 / 201). [cvFsGetNumTr64]
void sub_5577B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005577b8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    s0 = 0;
    sd(ra, sp, 0x10);
    if (s1 != 0) {
        // 0x005577e8
        charge(ctx, 4);
        lw(v0, s1, cvfs::kHIf);
        lw(v0, v0, cvfs::kIfOptFn1);
        a1 = 200;
        if (v0 != 0) {
            // 0x005577f8
            charge(ctx, 16);
            lw(a0, s1, cvfs::kHFile);
            a2 = 0;
            a3 = 0;
            jalr(ctx, 0x557800u, v0.u());
            lw(v1, s1, cvfs::kHIf);
            s0 = v0;
            lw(a0, s1, cvfs::kHFile);
            lw(v0, v1, cvfs::kIfOptFn1);
            a1 = 201;
            a2 = 0;
            a3 = 0;
            jalr(ctx, 0x557820u, v0.u());
            s0 = dsll32(s0, 0);
            v0 = dsll32(v0, 0);
            v0 = dsrl32(v0, 0);
            s0 = s0 + v0;
        }
        // 0x00557838
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x005577d4
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17856);  // "cvFsGetNumTr64 #1:handle error"
        jal(ctx, 0x5577D8u, gen::fn_sub_555918_00555918);
        v0 = 0;
    }
    // 0x0055783c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00557850 sub_557850 -- 180 bytes; frame 0x290: s1 sp+0x268, s3 sp+0x278, s0 sp+0x260, s2 sp+0x270, ra sp+0x280
// the 64-bit file size (OptFn1 codes 202 / 203). [cvFsGetFileSize64]
void sub_557850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00557850
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x290);
    sd(s1, sp, 0x268);
    s1 = a0;
    sd(s3, sp, 0x278);
    s3 = addiu(sp, 0x130);
    a0 = sp;
    a2 = s1;
    a1 = s3;
    sd(s0, sp, 0x260);
    sd(s2, sp, 0x270);
    sd(ra, sp, 0x280);
    s0 = 0;
    jal(ctx, 0x55787Cu, gen::fn_cvfs_getDevName_005561e8);
    a0 = sp;
    a1 = s3;
    a2 = s1;
    jal(ctx, 0x55788Cu, gen::fn_cvfs_variousProc_00555fa0);
    a0 = s1;
    s2 = v0;
    a1 = 202;
    lw(v0, s2, cvfs::kIfOptFn1);
    a2 = s3;
    a3 = 0;
    if (v0 != 0) {
        // 0x005578b0
        charge(ctx, 13);
        jalr(ctx, 0x5578B0u, v0.u());
        a0 = s1;
        s0 = v0;
        lw(v0, s2, cvfs::kIfOptFn1);
        a2 = s3;
        a1 = 203;
        a3 = 0;
        s0 = dsll32(s0, 0);
        jalr(ctx, 0x5578D0u, v0.u());
        v0 = dsll32(v0, 0);
        v0 = dsrl32(v0, 0);
        s0 = s0 + v0;
    }
    // 0x005578e4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s0;
    ld(s0, sp, 0x260);
    ld(s1, sp, 0x268);
    ld(s2, sp, 0x270);
    ld(s3, sp, 0x278);
    ld(ra, sp, 0x280);
    sp = addiu(sp, 0x290);
}

// 0x00557908 sub_557908 -- 192 bytes; frame 0x290: s2 sp+0x270, s1 sp+0x268, s3 sp+0x278, s4 sp+0x280, s0 sp+0x260, ra sp+0x288
// the 64-bit free size (OptFn1 codes 204 / 205). [cvFsGetFreeSize64]
void sub_557908(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00557908
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x290);
    sd(s2, sp, 0x270);
    s2 = a0;
    a0 = sp;
    sd(s1, sp, 0x268);
    sd(s3, sp, 0x278);
    sd(s4, sp, 0x280);
    sd(s0, sp, 0x260);
    sd(ra, sp, 0x288);
    s4 = a1;
    jal(ctx, 0x55792Cu, gen::fn_cvfs_getDevice_00555c78);
    s1 = v0;
    v0 = 0;
    s3 = addiu(sp, 0x130);
    a0 = sp;
    a1 = s3;
    a2 = s2;
    if (s1 != 0) {
        // 0x00557950
        charge(ctx, 9);
        jal(ctx, 0x557950u, gen::fn_cvfs_getDevName_005561e8);
        v0 = 0;
        lw(v1, s1, cvfs::kIfOptFn1);
        a0 = s2;
        a3 = s4;
        a1 = 204;
        a2 = s3;
        if (v1 != 0) {
            // 0x00557974
            charge(ctx, 13);
            jalr(ctx, 0x557974u, v1.u());
            a0 = s2;
            s0 = v0;
            lw(v0, s1, cvfs::kIfOptFn1);
            a2 = s3;
            a3 = s4;
            a1 = 205;
            s0 = dsll32(s0, 0);
            jalr(ctx, 0x557994u, v0.u());
            v0 = dsll32(v0, 0);
            v0 = dsrl32(v0, 0);
            v0 = s0 + v0;
        }
    }
    // 0x005579a8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x260);
    ld(s1, sp, 0x268);
    ld(s2, sp, 0x270);
    ld(s3, sp, 0x278);
    ld(s4, sp, 0x280);
    ld(ra, sp, 0x288);
    sp = addiu(sp, 0x290);
}

// 0x005579C8 sub_5579C8 -- 92 bytes; frame 0x10: ra sp+0x0
// the file system's 64-bit flag (OptFn1 code 299). [cvFsGetFsys64Info]
void sub_5579C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005579c8
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0;
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x005579f0
        charge(ctx, 4);
        lw(v0, a0, cvfs::kHIf);
        lw(v0, v0, cvfs::kIfOptFn1);
        a1 = 299;
        if (v0 != 0) {
            // 0x00557a00
            charge(ctx, 5);
            lw(a0, a0, cvfs::kHFile);
            a2 = 0;
            a3 = 0;
            jalr(ctx, 0x557A08u, v0.u());
            v1 = v0;
        }
        // 0x00557a14
        charge(ctx, 1);
        v0 = v1;
    } else {
        // 0x005579d8
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 17888);  // "cvFsGetFsys64Info #1:handle error"
        jal(ctx, 0x5579DCu, gen::fn_sub_555918_00555918);
        v0 = 0;
    }
    // 0x00557a18 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00557A28 sub_557A28 -- 48 bytes; frame 0x10: ra sp+0x0
// clear the SRD object (56 bytes at 0x7A08B0). [srd_Clear]
void sub_557A28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00557a28
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7A0000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 2280);  // &0x7A08E8
    a0 = 0x7A0000;
    a1 = 0;
    lw(v1, v0, 0);  // 0x7A08E8
    a0 = addiu(a0, 2224);  // &srd_obj
    ld(ra, sp, 0x0);
    a2 = 56;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

}  // namespace p3fes::game
