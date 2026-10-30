// libmc2's FAT layer (0x5153A0-0x51A078): the PS2 memory card file system on the EE (public format: the
// superblock, the indirect FAT, 1,024-byte clusters, 512-byte directory entries). Per port it keeps a copy of the
// superblock (libs1::mc2::kSuperblock), a FAT / indirect-FAT cluster cache and the current directory
// (libs1::mc2::kFatState); clusters go through the write-cluster cache of libs1_mc2.cpp and pages through the core
// layer (_sceMcCore*, still recompiled: the DBC driver on the IOP). The file operations run in libmc2's basic_thread.
//
// Every body is p3fes_handgen's (register for register and block for block as the recompiled body: frame, spills,
// $ra links, cycle charges, check points); the readability pass (scratch spec.py, checked by check.py) adds the
// role comments and the named offsets of game/include/p3fes/game/libs1_mc2fat.h, each equal to the literal it replaces.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs1_mc2fat.h"

namespace p3fes::recomp_gen {
void fn__CheckFileDescript_00516be8(p3fes::EEContext&);
void fn__ConfInsert_00516b48(p3fes::EEContext&);
void fn__CreateEntry_005175e8(p3fes::EEContext&);
void fn__GetEntryByPos_00515b18(p3fes::EEContext&);
void fn__GetFreeEntrySize_005174b8(p3fes::EEContext&);
void fn__ParentDirUpdate_00517ab8(p3fes::EEContext&);
void fn__SearchEntry_00516c48(p3fes::EEContext&);
void fn__SearchFile_00516ec0(p3fes::EEContext&);
void fn__SetEntryByPos_00517310(p3fes::EEContext&);
void fn__fat_chain_trace_00515c98(p3fes::EEContext&);
void fn__get_dir_nest_005151d0(p3fes::EEContext&);
void fn__make_path_00515218(p3fes::EEContext&);
void fn__reset_problem_patch_00515d28(p3fes::EEContext&);
void fn__sceMcCoreBlockErase_0051bbd8(p3fes::EEContext&);
void fn__sceMcCoreClearNewCardFlag_0051b2c0(p3fes::EEContext&);
void fn__sceMcCoreGetConnection_0051c0c0(p3fes::EEContext&);
void fn__sceMcCoreReadClock_0051b5f0(p3fes::EEContext&);
void fn__sceMcCoreSetCardSpec_0051af98(p3fes::EEContext&);
void fn__sceMcCoreSetWriteBackHole_0051af70(p3fes::EEContext&);
void fn__sceMcCoreWriteBack_0051b4a0(p3fes::EEContext&);
void fn__sceMcFatChDir_00519728(p3fes::EEContext&);
void fn__sceMcFatCreateFile_00517cd8(p3fes::EEContext&);
void fn__sceMcFatDeleteFile_005194f8(p3fes::EEContext&);
void fn__sceMcFatFlushFatCache_00515588(p3fes::EEContext&);
void fn__sceMcFatGetDir_00519850(p3fes::EEContext&);
void fn__sceMcFatGetEntSpace_0051a078(p3fes::EEContext&);
void fn__sceMcFatGetFatClustNum_00515468(p3fes::EEContext&);
void fn__sceMcFatGetFreeClustSize_00515a40(p3fes::EEContext&);
void fn__sceMcFatGetFreeClust_00515910(p3fes::EEContext&);
void fn__sceMcFatGetInfo_00515d80(p3fes::EEContext&);
void fn__sceMcFatGetNextClustAlloc_00518da0(p3fes::EEContext&);
void fn__sceMcFatGetNextClustSelf_00515778(p3fes::EEContext&);
void fn__sceMcFatGetNextClust_00515730(p3fes::EEContext&);
void fn__sceMcFatInit2_00515400(p3fes::EEContext&);
void fn__sceMcFatInit_005153a0(p3fes::EEContext&);
void fn__sceMcFatReadFastFile_00518470(p3fes::EEContext&);
void fn__sceMcFatReadFatData_00515618(p3fes::EEContext&);
void fn__sceMcFatReadFile_00518268(p3fes::EEContext&);
void fn__sceMcFatRename_00519ef8(p3fes::EEContext&);
void fn__sceMcFatSearchFile_00517be8(p3fes::EEContext&);
void fn__sceMcFatSetAttr_00519d70(p3fes::EEContext&);
void fn__sceMcFatUnFormat_00516a48(p3fes::EEContext&);
void fn__sceMcFatWriteFastFile_00518e70(p3fes::EEContext&);
void fn__sceMcFatWriteFatData_005157e0(p3fes::EEContext&);
void fn__sceMcFatWriteFile_005187c0(p3fes::EEContext&);
void fn__sceMcpAuthentication_0051a1c0(p3fes::EEContext&);
void fn__sceMcpCheckNewCard_0051a1a0(p3fes::EEContext&);
void fn__sceMcpFlushCache_0051a498(p3fes::EEContext&);
void fn__sceMcpGetCardSpec_0051a180(p3fes::EEContext&);
void fn__sceMcpIsSpeckOutClust_0051ab50(p3fes::EEContext&);
void fn__sceMcpReadClust_0051a418(p3fes::EEContext&);
void fn__sceMcpReadSysInfo_0051a1e0(p3fes::EEContext&);
void fn__sceMcpReadUserClustFast_0051aa00(p3fes::EEContext&);
void fn__sceMcpReadUserClust_0051a9e0(p3fes::EEContext&);
void fn__sceMcpWriteClust_0051a458(p3fes::EEContext&);
void fn__sceMcpWriteUserClustFast_0051aa48(p3fes::EEContext&);
void fn__sceMcpWriteUserClust_0051aa90(p3fes::EEContext&);
void fn__strtok_005150b0(p3fes::EEContext&);
void fn_isCorrFname_00514e20(p3fes::EEContext&);
void fn_isCorrNameSize_00514db0(p3fes::EEContext&);
void fn_isWildFit_00514f30(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_strcat_00523e68(p3fes::EEContext&);
void fn_strchr_00523f98(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncmp_00524670(p3fes::EEContext&);
void fn_strrchr_005249e8(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x005153A0 _sceMcFatInit -- 96 bytes; leaf frame (no stack)
// Reset the FAT state of both ports: no cached FAT / indirect cluster (-1), not dirty, free search from 0, the
// new-card flag set (so the next GetInfo re-reads the card), the current directory "/".
void _sceMcFatInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t2{ctx, 10};
    // 0x005153a0
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 0x980000;
    a0 = si(-1);
    v0 = addiu(v0, -18552);  // &0x97B788
    a2 = 1;
    v0 = addiu(v0, 2056);  // &0x97BF90
    a1 = 0x7C0000;
    v1 = 1;
    for (;;) {
        // 0x005153c0
        charge(ctx, 14);
        sw(a0, v0, -8);
        v1 = addiu(v1, -1);
        sw(a0, v0, -4);
        sw(zero, v0, 140);
        sw(a2, v0, 128);
        sw(zero, v0, 132);
        sw(zero, v0, 136);
        t2 = addiu(a1, -6648);
        lb(a3, t2, 0);
        lb(t0, t2, 1);
        sb(a3, v0, 0);
        sb(t0, v0, 1);
        v0 = addiu(v0, 2200);
        if (i64(v1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005153f8
    charge(ctx, 2);
    v0 = 1;
}

// 0x00515400 _sceMcFatInit2 -- 104 bytes; leaf frame (no stack)
// Reset one port's FAT state as _sceMcFatInit does for both.
void _sceMcFatInit2(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x00515400
    enter(ctx, 26);  // entry check point + this block's cycles
    v0 = 2200;
    v1 = 0x980000;
    mult(a0, a0, v0);
    v1 = addiu(v1, -18552);  // &0x97B788
    t0 = si(-1);
    t1 = 1;
    t2 = addiu(v1, 2056);  // &0x97BF90
    t3 = 0x7C0000;
    a1 = addu(v1, a0);
    sw(t0, a1, 2048);
    a2 = a1;
    sw(t0, a2, 2052);
    a3 = a1;
    sw(zero, a3, 2196);
    v1 = a1;
    sw(t1, a1, 2184);
    a0 = addu(a0, t2);
    sw(zero, a2, 2188);
    sw(zero, v1, 2192);
    a3 = addiu(t3, -6648);  // &0x7BE608
    lb(v1, a3, 0);  // 0x7BE608
    lb(a1, a3, 1);  // 0x7BE609
    sb(v1, a0, 0);
    sb(a1, a0, 1);
    v0 = 1;
}

// 0x00515468 _sceMcFatGetFatClustNum -- 284 bytes; frame 0x70: s1 sp+0x10, s3 sp+0x30, ra sp+0x60, s5 sp+0x50, s4 sp+0x40, s2 sp+0x20, s0 sp+0x0
// The card cluster holding the FAT entry of a cluster: reads the indirect-FAT cluster (ifc_list[n / 65536]) into the
// port's indirect cache when it is not cached, then returns its word for (n / 256) % 256; *err = 0x8101006F on a read
// failure, 0x81019001 for an unused (negative) word.
void _sceMcFatGetFatClustNum(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00515468
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v1 = 388;
    sd(s1, sp, 0x10);
    v0 = 0x780000;
    s1 = a0;
    sd(s3, sp, 0x30);
    mult(v1, s1, v1);
    v0 = addiu(v0, 10208);  // &0x7827E0
    s3 = a2;
    sd(ra, sp, 0x60);
    sd(s5, sp, 0x50);
    a2 = a1;
    sd(s4, sp, 0x40);
    sd(s2, sp, 0x20);
    t1 = addu(v1, v0);
    sd(s0, sp, 0x0);
    if (i64(a1) < 0) {
        // 0x005154ac
        charge(ctx, 2);
        v0 = 0xFFFF;
        a2 = addu(a1, v0);
    }
    // 0x005154b4
    charge(ctx, 16);
    v0 = 2200;
    s5 = 0x980000;
    mult(a3, s1, v0);
    t0 = addiu(s5, -18552);  // &0x97B788
    v0 = si(-1);
    a0 = addiu(t0, 2052);  // &0x97BF8C
    v0 = slt(v0, a1);
    v1 = addiu(a1, 255);
    if (v0 != 0) v1 = a1;
    s0 = sra(a2, 16);
    s2 = addu(a3, a0);
    v1 = sra(v1, 8);
    v0 = sll(s0, 8);
    lw(a0, s2, 0);
    s4 = subu(v1, v0);
    if (a0 != s0) {
        // 0x005154f4
        charge(ctx, 9);
        v0 = sll(s0, 2);
        a1 = addu(a3, t0);
        v0 = addu(t1, v0);
        a0 = s1;
        lw(a2, v0, 80);
        a3 = 1;
        jal(ctx, 0x515508u, gen::fn__sceMcpReadClust_0051a418);
        if (v0 != 0) {
            sw(s0, s2, 0);
            goto L_0051552c;
        }
        // 0x00515518
        charge(ctx, 5);
        v1 = lui(0x8101);
        v0 = 0;
        v1 = v1 | 0x6F;
        sw(v1, s3, 0);
        // 0x00515560 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(ra, sp, 0x60);
        ld(s5, sp, 0x50);
        ld(s4, sp, 0x40);
        ld(s3, sp, 0x30);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x70);
        return;
    }
L_0051552c:
    charge(ctx, 9);
    v1 = 2200;
    v0 = sll(s4, 2);
    mult(v1, s1, v1);
    a0 = addiu(s5, -18552);
    v0 = addu(v0, v1);
    v0 = addu(v0, a0);
    lw(v0, v0, 0);
    if (i64(v0) >= 0) {
        sw(zero, s3, 0);
    } else {
        // 0x00515550
        charge(ctx, 4);
        v1 = lui(0x8101);
        v0 = 0;
        v1 = v1 | 0x9001;
        sw(v1, s3, 0);
    }
    // 0x00515560 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00515588 _sceMcFatFlushFatCache -- 144 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x10, ra sp+0x20
// Write the cached FAT cluster back when it is dirty (_sceMcpWriteClust); clears the dirty flag; 0 on a write
// failure, else 1.
void _sceMcFatFlushFatCache(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00515588
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 2200;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x10);
    mult(a3, s0, v0);
    s1 = 0x980000;
    sd(ra, sp, 0x20);
    a1 = addiu(s1, -18552);  // &0x97B788
    v0 = addu(a1, a3);
    lw(a2, v0, 2048);
    a0 = 1;
    if (i64(a2) <= 0) {
        // 0x005155ec
        charge(ctx, 1);
        v1 = 2200;
    L_005155f0:
        charge(ctx, 5);
        a0 = addiu(s1, -18552);
        mult(v1, s0, v1);
        v0 = 1;
        a0 = addu(a0, v1);
        sw(zero, a0, 2196);
    } else {
        // 0x005155bc
        charge(ctx, 3);
        lw(v1, v0, 2196);
        cc = v1 != a0;  // the condition, before the delay slot changes it
        v1 = 2200;
        if (cc) {
            goto L_005155f0;
        }
        // 0x005155c8
        charge(ctx, 7);
        a1 = addiu(a1, 1024);
        a0 = s0;
        a1 = addu(a3, a1);
        a3 = 1;
        jal(ctx, 0x5155D4u, gen::fn__sceMcpWriteClust_0051a458);
        v1 = 2200;
        if (v0 != 0) {
            goto L_005155f0;
        }
        // 0x005155e4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00515604 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00515618 _sceMcFatReadFatData -- 280 bytes; frame 0x90: s2 sp+0x20, s3 sp+0x30, s1 sp+0x10, s0 sp+0x0, ra sp+0x80, s7 sp+0x70, s6 sp+0x60, s5 sp+0x50, s4 sp+0x40
// The FAT entry of a cluster: finds its FAT cluster, swaps it into the FAT cache (flushing the old one first) and
// returns entry n % 256; *err as _sceMcFatGetFatClustNum.
void _sceMcFatReadFatData(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00515618
    enter(ctx, 25);  // entry check point + this block's cycles
    a3 = a1;
    v0 = si(-1);
    sp = addiu(sp, -0x90);
    v0 = slt(v0, a3);
    v1 = addiu(a3, 255);
    sd(s2, sp, 0x20);
    if (v0 != 0) v1 = a3;
    sd(s3, sp, 0x30);
    s2 = sra(v1, 8);
    sd(s1, sp, 0x10);
    s3 = a2;
    v0 = sll(s2, 8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x80);
    sd(s7, sp, 0x70);
    s2 = subu(a3, v0);
    sd(s6, sp, 0x60);
    sd(s5, sp, 0x50);
    link(ctx, 0x515664u);  // $ra first: the delay slot below depends on it
    sd(s4, sp, 0x40);
    call(ctx, gen::fn__sceMcFatGetFatClustNum_00515468);
    lw(v1, s3, 0);
    s0 = v0;
    v0 = 0;
    if (v1 == 0) {
        // 0x0051567c
        charge(ctx, 9);
        v0 = 2200;
        s7 = 0x980000;
        mult(s4, s1, v0);
        s6 = addiu(s7, -18552);  // &0x97B788
        v0 = addiu(s6, 2048);  // &0x97BF88
        s5 = addu(s4, v0);
        lw(v1, s5, 0);
        cc = v1 == s0;  // the condition, before the delay slot changes it
        v1 = 2200;
        if (!cc) {
            // 0x005156a0
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x5156A0u, gen::fn__sceMcFatFlushFatCache_00515588);
            a1 = addiu(s6, 1024);
            if (v0 != 0) {
                // 0x005156b0
                charge(ctx, 7);
                a0 = s1;
                a1 = addu(s4, a1);
                a2 = s0;
                a3 = 1;
                jal(ctx, 0x5156BCu, gen::fn__sceMcpReadClust_0051a418);
                if (v0 == 0) {
                    goto L_005156cc;
                }
                sw(s0, s5, 0);
                // 0x005156e0
                charge(ctx, 1);
                v1 = 2200;
                goto L_005156e4;
            }
        L_005156cc:
            charge(ctx, 5);
            v1 = lui(0x8101);
            v0 = 0;
            v1 = v1 | 0x6F;
            sw(v1, s3, 0);
            // 0x00515704 (the shared epilogue, written out on this path)
            charge(ctx, 11);
            ld(ra, sp, 0x80);
            ld(s7, sp, 0x70);
            ld(s6, sp, 0x60);
            ld(s5, sp, 0x50);
            ld(s4, sp, 0x40);
            ld(s3, sp, 0x30);
            ld(s2, sp, 0x20);
            ld(s1, sp, 0x10);
            ld(s0, sp, 0x0);
            sp = addiu(sp, 0x90);
            return;
        }
    L_005156e4:
        charge(ctx, 8);
        a0 = sll(s2, 2);
        mult(v1, s1, v1);
        v0 = addiu(s7, -18552);
        a0 = addu(a0, v1);
        v0 = addu(v0, a0);
        lw(s0, v0, 1024);
        sw(zero, s3, 0);
        v0 = s0;
    }
    // 0x00515704 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    ld(s7, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00515730 _sceMcFatGetNextClust -- 68 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// The FAT entry of a cluster, with *err = 0x81019002 for an unformatted entry (0x7FFFFFFF).
void _sceMcFatGetNextClust(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00515730
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a2;
    jal(ctx, 0x51573Cu, gen::fn__sceMcFatReadFatData_00515618);
    v1 = v0;
    v0 = 0x7FFF0000;
    v0 = v0 | 0xFFFF;
    ld(ra, sp, 0x10);
    if (v1 == v0) {
        // 0x00515758
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x9002;
        sw(v0, s0, 0);
    }
    // 0x00515764 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    v0 = v1;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00515778 _sceMcFatGetNextClustSelf -- 100 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// The next cluster of a chain: the entry without its in-use bit; -1 with *err = 0x81010059 at the chain's end.
void _sceMcFatGetNextClustSelf(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00515778
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a2;
    jal(ctx, 0x515784u, gen::fn__sceMcFatGetNextClust_00515730);
    lw(v1, s0, 0);
    a0 = v0;
    v0 = 0;
    if (v1 == 0) {
        // 0x0051579c
        charge(ctx, 4);
        v0 = lui(0xFFFF);
        v0 = v0 | 0xFFFF;
        cc = a0 != v0;  // the condition, before the delay slot changes it
        v0 = 0x7FFF0000;
        if (cc) {
            // 0x005157c4
            charge(ctx, 2);
            v0 = v0 | 0xFFFF;
            v0 = a0 & v0;
        } else {
            // 0x005157ac
            charge(ctx, 6);
            v1 = lui(0x8101);
            v0 = lui(0xFFFF);
            v1 = v1 | 0x59;
            v0 = v0 | 0xFFFF;
            sw(v1, s0, 0);
        }
    }
    // 0x005157cc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x005157E0 _sceMcFatWriteFatData -- 304 bytes; frame 0xA0: s3 sp+0x30, fp sp+0x80, s4 sp+0x40, s0 sp+0x0, s1 sp+0x10, ra sp+0x90, s7 sp+0x70, s6 sp+0x60, s5 sp+0x50, s2 sp+0x20
// Store a FAT entry: swaps its FAT cluster into the cache and marks it dirty; 1, or 0 with *err set.
void _sceMcFatWriteFatData(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005157e0
    enter(ctx, 27);  // entry check point + this block's cycles
    v0 = si(-1);
    sp = addiu(sp, -0xA0);
    v0 = slt(v0, a1);
    v1 = addiu(a1, 255);
    if (v0 != 0) v1 = a1;
    sd(s3, sp, 0x30);
    s3 = sra(v1, 8);
    sd(fp, sp, 0x80);
    sd(s4, sp, 0x40);
    v0 = sll(s3, 8);
    sd(s0, sp, 0x0);
    s4 = a3;
    s0 = a0;
    fp = a2;
    sd(s1, sp, 0x10);
    s3 = subu(a1, v0);
    sd(ra, sp, 0x90);
    sd(s7, sp, 0x70);
    a2 = s4;
    sd(s6, sp, 0x60);
    sd(s5, sp, 0x50);
    link(ctx, 0x515834u);  // $ra first: the delay slot below depends on it
    sd(s2, sp, 0x20);
    call(ctx, gen::fn__sceMcFatGetFatClustNum_00515468);
    s1 = v0;
    lw(v0, s4, 0);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x0051584c
        charge(ctx, 9);
        v0 = 2200;
        s7 = 0x980000;
        mult(s2, s0, v0);
        s6 = addiu(s7, -18552);  // &0x97B788
        v0 = addiu(s6, 2048);  // &0x97BF88
        s5 = addu(s2, v0);
        lw(v1, s5, 0);
        a0 = 2200;
        if (v1 != s1) {
            // 0x00515870
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x515870u, gen::fn__sceMcFatFlushFatCache_00515588);
            a1 = addiu(s6, 1024);
            if (v0 != 0) {
                // 0x00515880
                charge(ctx, 7);
                a0 = s0;
                a1 = addu(s2, a1);
                a2 = s1;
                a3 = 1;
                jal(ctx, 0x51588Cu, gen::fn__sceMcpReadClust_0051a418);
                if (v0 == 0) {
                    goto L_0051589c;
                }
                sw(s1, s5, 0);
                // 0x005158b0
                charge(ctx, 1);
                a0 = 2200;
                goto L_005158b4;
            }
        L_0051589c:
            charge(ctx, 5);
            v1 = lui(0x8101);
            v0 = 0;
            v1 = v1 | 0x6F;
            sw(v1, s4, 0);
            // 0x005158e0 (the shared epilogue, written out on this path)
            charge(ctx, 12);
            ld(ra, sp, 0x90);
            ld(fp, sp, 0x80);
            ld(s7, sp, 0x70);
            ld(s6, sp, 0x60);
            ld(s5, sp, 0x50);
            ld(s4, sp, 0x40);
            ld(s3, sp, 0x30);
            ld(s2, sp, 0x20);
            ld(s1, sp, 0x10);
            ld(s0, sp, 0x0);
            sp = addiu(sp, 0xA0);
            return;
        }
    L_005158b4:
        charge(ctx, 11);
        a1 = sll(s3, 2);
        mult(a0, s0, a0);
        v1 = addiu(s7, -18552);
        a2 = 1;
        v0 = 1;
        a1 = addu(a1, a0);
        a0 = addu(v1, a0);
        v1 = addu(v1, a1);
        sw(fp, v1, 1024);
        sw(a2, a0, 2196);
        sw(zero, s4, 0);
    }
    // 0x005158e0 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x90);
    ld(fp, sp, 0x80);
    ld(s7, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x00515910 _sceMcFatGetFreeClust -- 300 bytes; frame 0xB0: s5 sp+0x60, s6 sp+0x70, s1 sp+0x20, fp sp+0x90, s7 sp+0x80, s3 sp+0x40, ra sp+0xA0, s4 sp+0x50, s2 sp+0x30, s0 sp+0x10, s6 sp+0x0
// Find a free cluster (in-use bit clear) from the port's search start; restarts once from 0 when it reaches the
// usable-cluster count; *err = 0x8101001C when the card is full.
void _sceMcFatGetFreeClust(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00515910
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v0 = 2200;
    sd(s5, sp, 0x60);
    v1 = 0x980000;
    sd(s6, sp, 0x70);
    s5 = a0;
    mult(s6, s5, v0);
    a0 = 388;
    sd(s1, sp, 0x20);
    mult(a0, s5, a0);
    sd(fp, sp, 0x90);
    s1 = a1;
    sd(s7, sp, 0x80);
    v0 = 0x780000;
    sd(s3, sp, 0x40);
    v0 = addiu(v0, 10208);  // &0x7827E0
    sd(ra, sp, 0xA0);
    s7 = addiu(v1, -16360);  // &0x97C018
    sd(s4, sp, 0x50);
    s3 = addu(a0, v0);
    sd(s2, sp, 0x30);
    fp = addu(s6, s7);
    sd(s0, sp, 0x10);
    sw(zero, s1, 0);
    sw(s6, sp, 0x0);
    lw(v1, s3, 368);
    for (;;) {
        // 0x00515978
        charge(ctx, 4);
        lw(s0, fp, 0x0);
        v0 = slt(s0, v1);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        lw(v0, sp, 0x0);
        if (!cc) {
            // 0x00515988
            charge(ctx, 6);
            v1 = 0x980000;
            v1 = addiu(v1, -16360);  // &0x97C018
            s4 = lui(0x8000);
            s2 = addu(v0, v1);
            a0 = s5;
            for (;;) {
                // 0x005159a0
                charge(ctx, 7);
                a1 = s0;
                a2 = s1;
                jal(ctx, 0x5159A4u, gen::fn__sceMcFatReadFatData_00515618);
                v1 = v0;
                lw(v0, s1, 0);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = 0;
                if (cc) {
                    break;
                }
                // 0x005159bc
                charge(ctx, 3);
                v0 = v1 & s4;
                if (v0 == 0) {
                    goto L_005159c8_5;
                }
                lw(v1, s3, 368);
                // 0x005159d8
                charge(ctx, 4);
                s0 = addiu(s0, 1);
                v0 = slt(s0, v1);
                a0 = s5;
                if (v0 == 0) {
                    goto L_005159e8;
                }
                backedge(ctx);
            }
            break;
        }
    L_005159e8:
        charge(ctx, 4);
        a0 = addu(s6, s7);
        lw(v0, a0, 0);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (cc) {
            goto L_00515a00;
        }
        // 0x005159f8
        charge(ctx, 2);
        sw(zero, a0, 0);
        backedge(ctx);
    }
    // 0x00515a0c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0xA0);
    ld(fp, sp, 0x90);
    ld(s7, sp, 0x80);
    ld(s6, sp, 0x70);
    ld(s5, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0xB0);
    return;
L_005159c8_5:
    charge(ctx, 4);
    sw(zero, s1, 0);
    v0 = s0;
    sw(s0, s2, 0);
    // 0x00515a0c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0xA0);
    ld(fp, sp, 0x90);
    ld(s7, sp, 0x80);
    ld(s6, sp, 0x70);
    ld(s5, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0xB0);
    return;
L_00515a00:
    charge(ctx, 3);
    v1 = lui(0x8101);
    v1 = v1 | 0x1C;
    sw(v1, s1, 0);
    // 0x00515a0c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0xA0);
    ld(fp, sp, 0x90);
    ld(s7, sp, 0x80);
    ld(s6, sp, 0x70);
    ld(s5, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0xB0);
}

// 0x00515A40 _sceMcFatGetFreeClustSize -- 212 bytes; frame 0x70: s4 sp+0x40, s2 sp+0x20, s3 sp+0x30, s1 sp+0x10, ra sp+0x60, s5 sp+0x50, s0 sp+0x0
// Count the free clusters from the search start to the usable-cluster count (superblock +368).
void _sceMcFatGetFreeClustSize(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00515a40
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    a2 = 2200;
    sd(s4, sp, 0x40);
    v0 = 0x780000;
    s4 = a0;
    sd(s2, sp, 0x20);
    a0 = 388;
    mult1(a2, s4, a2);
    mult(a0, s4, a0);
    sd(s3, sp, 0x30);
    sd(s1, sp, 0x10);
    s2 = a1;
    sd(ra, sp, 0x60);
    v1 = 0x980000;
    sd(s5, sp, 0x50);
    v0 = addiu(v0, 10208);  // &0x7827E0
    sd(s0, sp, 0x0);
    v1 = addiu(v1, -18552);  // &0x97B788
    sw(zero, s2, 0);
    s3 = addu(a0, v0);
    v1 = addu(v1, a2);
    lw(s0, v1, 2192);
    lw(v0, s3, 368);
    v0 = slt(s0, v0);
    s1 = 0;
    if (v0 != 0) {
        // 0x00515aa8
        charge(ctx, 2);
        s5 = lui(0x8000);
        for (;;) {
            // 0x00515ab0
            charge(ctx, 8);
            a0 = s4;
            a1 = s0;
            a2 = s2;
            jal(ctx, 0x515AB8u, gen::fn__sceMcFatReadFatData_00515618);
            a0 = v0;
            lw(v0, s2, 0);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (cc) {
                break;
            }
            // 0x00515ad0
            charge(ctx, 7);
            lw(v0, s3, 368);
            a0 = a0 & s5;
            v1 = addiu(s1, 1);
            s0 = addiu(s0, 1);
            v0 = slt(s0, v0);
            if (a0 == 0) s1 = v1;
            if (v0 == 0) {
                goto L_00515aec;
            }
            backedge(ctx);
        }
        // 0x00515af0 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(ra, sp, 0x60);
        ld(s5, sp, 0x50);
        ld(s4, sp, 0x40);
        ld(s3, sp, 0x30);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x70);
        return;
    }
L_00515aec:
    charge(ctx, 1);
    v0 = s1;
    // 0x00515af0 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00515B18 _GetEntryByPos -- 384 bytes; frame 0x70: s3 sp+0x40, s1 sp+0x20, s4 sp+0x50, s2 sp+0x30, s0 sp+0x10, ra sp+0x60
// Read directory entry N of a directory cluster chain: follows the chain two entries per cluster, reads the cluster
// into the entry buffer 0x97C8C0 and copies the 512-byte entry out (its name's 32nd byte cleared); 0x81010002 past
// the end, 0x8101006F on a read failure.
void _GetEntryByPos(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00515b18
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s3, sp, 0x40);
    sd(s1, sp, 0x20);
    s3 = a1;
    sd(s4, sp, 0x50);
    s1 = lui(0x8101);
    sd(s2, sp, 0x30);
    a1 = a2;
    sd(s0, sp, 0x10);
    s2 = a0;
    sd(ra, sp, 0x60);
    s0 = a3;
    sw(zero, sp, 0x0);
    s4 = 0x980000;
    s1 = s1 | 0x59;
    for (;;) {
        // 0x00515b58
        charge(ctx, 3);
        v0 = slti(s0, 2);
        a2 = a1;
        if (v0 != 0) {
            goto L_00515b64_2;
        }
        // 0x00515c44
        charge(ctx, 6);
        a0 = s2;
        a2 = sp;
        jal(ctx, 0x515C48u, gen::fn__sceMcFatGetNextClustSelf_00515778);
        lw(v1, sp, 0x0);
        a1 = v0;
        if (v1 == s1) {
            goto L_00515c5c_13;
        }
        // 0x00515c68
        charge(ctx, 2);
        v0 = v1;
        if (v1 == 0) {
            // 0x00515c70
            charge(ctx, 2);
            s0 = addiu(s0, -2);
            backedge(ctx);
            continue;
        }
        break;
    }
    // 0x00515c78 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x70);
    return;
L_00515b64_2:
    charge(ctx, 7);
    s1 = addiu(s4, -14144);
    a0 = s2;
    a1 = s1;
    a3 = 1;
    jal(ctx, 0x515B70u, gen::fn__sceMcpReadUserClust_0051a9e0);
    v1 = sll(s0, 9);
    if (v0 != 0) {
        // 0x00515b8c
        charge(ctx, 5);
        v1 = addu(v1, s1);
        v0 = v1 | s3;
        v0 = v0 & 0x7;
        a0 = s3;
        if (v0 == 0) {
            // 0x00515c00
            charge(ctx, 1);
            v0 = addiu(v1, 512);
            for (;;) {
                // 0x00515c04
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
            // 0x00515c38
            charge(ctx, 1);
            sb(zero, s3, 95);
        } else {
            // 0x00515ba0
            charge(ctx, 1);
            v0 = addiu(v1, 512);
            for (;;) {
                // 0x00515ba4
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
            // 0x00515bf8
            charge(ctx, 2);
            sb(zero, s3, 95);
        }
        // 0x00515c3c
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x00515b80
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x6F;
    }
    // 0x00515c78 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x70);
    return;
L_00515c5c_13:
    charge(ctx, 3);
    v0 = lui(0x8101);
    v0 = v0 | 0x2;
    // 0x00515c78 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x70);
}

// 0x00515C98 _fat_chain_trace -- 144 bytes; frame 0x40: s1 sp+0x20, ra sp+0x30, s0 sp+0x10
// The length of a cluster chain in clusters (0 for an empty chain -1); 0x81019002 for a broken chain (an entry
// without its in-use bit).
void _fat_chain_trace(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00515c98
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = lui(0xFFFF);
    sd(s1, sp, 0x20);
    v0 = v0 | 0xFFFF;
    sd(ra, sp, 0x30);
    s1 = a0;
    sd(s0, sp, 0x10);
    if (a1 != v0) {
        // 0x00515cc0
        charge(ctx, 2);
        s0 = 1;
        for (;;) {
            // 0x00515cd4
            charge(ctx, 6);
            a0 = s1;
            a2 = sp;
            jal(ctx, 0x515CD8u, gen::fn__sceMcFatGetNextClust_00515730);
            lw(v1, sp, 0x0);
            a1 = v0;
            if (v1 != 0) {
                goto L_00515cec_5;
            }
            // 0x00515cf4
            charge(ctx, 4);
            v0 = lui(0xFFFF);
            v0 = v0 | 0xFFFF;
            cc = a1 == v0;  // the condition, before the delay slot changes it
            v0 = s0;
            if (!cc) {
                // 0x00515d04
                charge(ctx, 2);
                v0 = 0x7FFF0000;
                if (i64(a1) >= 0) {
                    goto L_00515d0c_8;
                }
                backedge(ctx);
                // 0x00515cc8
                charge(ctx, 3);
                s0 = addiu(s0, 1);
                v0 = v0 | 0xFFFF;
                a1 = a1 & v0;
                continue;
            }
            break;
        }
    } else {
        // 0x00515cb8
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00515d14 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x40);
    return;
L_00515cec_5:
    charge(ctx, 2);
    v0 = v1;
    // 0x00515d14 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x40);
    return;
L_00515d0c_8:
    charge(ctx, 2);
    v0 = lui(0x8101);
    v0 = v0 | 0x9002;
    // 0x00515d14 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x40);
}

// 0x00515D28 _reset_problem_patch -- 88 bytes; frame 0x20: ra sp+0x10
// Give the core layer the card geometry from the superblock: page length, pages per block, pages per card (clusters x
// 1024 / page length), ECC on.
void _reset_problem_patch(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00515d28
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = a1;
    sd(ra, sp, 0x10);
    t1 = 1;
    a1 = sp;
    lw(v0, v1, 48);
    lhu(a2, v1, 40);
    v0 = sll(v0, 10);
    lhu(a3, v1, 44);
    div(v0, a2);
    t0 = a2;
    sw(t0, sp, 0x0);
    sw(a3, sp, 0x4);
    if (a2 == 0) {
        brk(ctx, 0x515D60u, 0x7u);
    }
    // 0x00515d64
    charge(ctx, 7);
    sw(t1, sp, 0xC);
    mflo(v0);
    link(ctx, 0x515D6Cu);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x8);
    call(ctx, gen::fn__sceMcCoreSetCardSpec_0051af98);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00515D80 _sceMcFatGetInfo -- 920 bytes; frame 0x2C0: s3 sp+0x250, s6 sp+0x280, s1 sp+0x230, ra sp+0x2B0, fp sp+0x2A0, s7 sp+0x290, s5 sp+0x270, s4 sp+0x260, s2 sp+0x240, s0 sp+0x220
// Card information (type 2, formatted flag, free clusters): on a new card re-reads the superblock (magic "Sony PS2
// Memory Card Format", version >= 1.1), sets the core geometry and write-back hole, counts the usable clusters,
// checks the root's "." and ".." entries; 0x81019003 once after a card change.
void _sceMcFatGetInfo(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00515d80
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2C0);
    v1 = 388;
    sd(s3, sp, 0x250);
    v0 = 0x780000;
    s3 = a0;
    sd(s6, sp, 0x280);
    mult(v1, s3, v1);
    sd(s1, sp, 0x230);
    v0 = addiu(v0, 10208);  // &0x7827E0
    sd(ra, sp, 0x2B0);
    sd(fp, sp, 0x2A0);
    s6 = a1;
    sd(s7, sp, 0x290);
    sd(s5, sp, 0x270);
    s1 = addu(v1, v0);
    sd(s4, sp, 0x260);
    sd(s2, sp, 0x240);
    link(ctx, 0x515DC4u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x220);
    call(ctx, gen::fn__sceMcCoreGetConnection_0051c0c0);
    if (v0 != 0) {
        // 0x00515dd4
        charge(ctx, 2);
        if (s6 != 0) {
            // 0x00515ddc
            charge(ctx, 3);
            sw(zero, s6, 4);
            sw(zero, s6, 0);
            sw(zero, s6, 8);
        }
        // 0x00515de8
        charge(ctx, 4);
        a0 = s3;
        jal(ctx, 0x515DE8u, gen::fn__sceMcpCheckNewCard_0051a1a0);
        s4 = 2;
        if (v0 == 0) {
            goto L_00515df8;
        }
        // 0x00515e04
        charge(ctx, 2);
        fp = 0x980000;
        if (v0 == s4) {
            // 0x00515e0c
            charge(ctx, 8);
            a0 = s3;
            jal(ctx, 0x515E0Cu, gen::fn__sceMcCoreClearNewCardFlag_0051b2c0);
            v1 = 2200;
            v0 = addiu(fp, -0x4878);
            mult(v1, s3, v1);
            a0 = 1;
            v0 = addu(v0, v1);
            sw(a0, v0, 2184);
        }
        // 0x00515e2c
        charge(ctx, 7);
        v1 = 2200;
        s2 = addiu(fp, -0x4878);
        mult(s0, s3, v1);
        v0 = addu(s2, s0);
        lw(v1, v0, 2184);
        a0 = s3;
        if (v1 != 0) {
            // 0x00515e48
            charge(ctx, 4);
            a1 = sp;
            jal(ctx, 0x515E48u, gen::fn__sceMcpGetCardSpec_0051a180);
            if (v0 != 0) {
                // 0x00515e58
                charge(ctx, 3);
                lw(v0, sp, 0x0);
                v1 = addu(s2, s0);
                if (v0 == 0) {
                    goto L_00515eac;
                }
                // 0x00515e64
                charge(ctx, 18);
                a0 = si(-1);
                sw(zero, v1, 2196);
                v0 = v1;
                sw(a0, v0, 2048);
                a1 = 0x7C0000;
                sw(a0, v1, 2052);
                v0 = addiu(s2, 2056);
                v0 = addu(s0, v0);
                sw(zero, v1, 2192);
                t0 = addiu(a1, -6648);  // &0x7BE608
                lb(v1, t0, 0);  // 0x7BE608
                lb(a2, t0, 1);  // 0x7BE609
                sb(v1, v0, 0);
                sb(a2, v0, 1);
                a0 = s3;
                jal(ctx, 0x515E9Cu, gen::fn__sceMcpReadSysInfo_0051a1e0);
                if (v0 == 0) {
                    goto L_00515eac;
                }
                // 0x00515eb8
                charge(ctx, 2);
                if (s6 != 0) {
                    sw(s4, s6, 0);
                }
                // 0x00515ec0
                charge(ctx, 7);
                a1 = 0x7C0000;
                a0 = s1;
                a1 = addiu(a1, -6640);  // "Sony PS2 Memory Card Format"
                a2 = 27;
                jal(ctx, 0x515ECCu, gen::fn_strncmp_00524670);
                if (v0 != 0) {
                    // 0x00515edc
                    charge(ctx, 2);
                    if (s6 != 0) {
                        sw(zero, s6, 4);
                    } else {
                        // 0x00515ee4
                        charge(ctx, 2);
                    }
                    goto L_00516078;
                }
                lb(v0, s1, 28);
                // 0x00515eec
                charge(ctx, 9);
                a0 = 10;
                lb(a1, s1, 30);
                v0 = addiu(v0, -48);
                mult(a2, v0, a0);
                v1 = addiu(a2, -48);
                a2 = addu(v1, a1);
                v0 = slti(a2, 11);
                a0 = s3;
                if (v0 == 0) {
                    // 0x00515f1c
                    charge(ctx, 14);
                    a1 = s1;
                    jal(ctx, 0x515F1Cu, gen::fn__reset_problem_patch_00515d28);
                    s4 = 0;
                    lw(a1, s1, 68);
                    a0 = s3;
                    lw(a2, s1, 64);
                    s2 = 0;
                    jal(ctx, 0x515F34u, gen::fn__sceMcCoreSetWriteBackHole_0051af70);
                    a0 = s3;
                    jal(ctx, 0x515F3Cu, gen::fn__sceMcCoreWriteBack_0051b4a0);
                    lw(v1, s1, 48);
                    v0 = 1000;
                    if (v0 == 0) {
                        brk(ctx, 0x515F50u, 0x7u);
                    }
                    // 0x00515f54
                    charge(ctx, 7);
                    div(v1, v0);
                    lw(a0, s1, 56);
                    lw(s0, s1, 52);
                    mflo(v1);
                    mult(v1, v1, v0);
                    s7 = addiu(v1, 1);
                    if (i64(a0) <= 0) {
                        // 0x00515fb8
                        charge(ctx, 2);
                        s5 = addiu(sp, 0x10);
                        lw(a2, s1, 60);
                    } else {
                        // 0x00515f70
                        charge(ctx, 2);
                        s5 = addiu(sp, 0x10);
                        for (;;) {
                            // 0x00515f78
                            charge(ctx, 2);
                            a1 = s0;
                            if (s4 == s7) {
                                // 0x00515f80
                                charge(ctx, 3);
                                lw(v0, s1, 52);
                                v0 = subu(s0, v0);
                                sw(v0, s1, 368);
                            }
                            // 0x00515f8c
                            charge(ctx, 9);
                            a0 = s3;
                            jal(ctx, 0x515F8Cu, gen::fn__sceMcpIsSpeckOutClust_0051ab50);
                            s2 = addiu(s2, 1);
                            lw(a0, s1, 56);
                            v1 = addiu(s4, 1);
                            if (v0 == 0) s4 = v1;
                            a0 = slt(s2, a0);
                            s0 = addiu(s0, 1);
                            if (a0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x00515fb0
                        charge(ctx, 2);
                        lw(a2, s1, 60);
                    }
                    // 0x00515fc0
                    charge(ctx, 7);
                    a0 = s3;
                    a1 = s5;
                    a3 = 0;
                    jal(ctx, 0x515FC8u, gen::fn__GetEntryByPos_00515b18);
                    v1 = v0;
                    sw(v0, sp, 0x210);
                    if (v1 == 0) {
                        // 0x00515fdc
                        charge(ctx, 4);
                        lhu(v0, sp, 0x10);
                        v0 = v0 & 0x8000;
                        s0 = addiu(sp, 0x50);
                        if (v0 == 0) {
                        L_00516078:
                            charge(ctx, 3);
                            v0 = lui(0x8101);
                            v0 = v0 | 0x2F;
                        } else {
                            // 0x00515fec
                            charge(ctx, 6);
                            a1 = 0x7C0000;
                            a1 = addiu(a1, -6672);  // &0x7BE5F0
                            a0 = s0;
                            jal(ctx, 0x515FF4u, gen::fn_strcmp_00524128);
                            a1 = s5;
                            if (v0 != 0) {
                                goto L_00516078;
                            }
                            // 0x00516004
                            charge(ctx, 7);
                            lw(a2, s1, 60);
                            a0 = s3;
                            a3 = 1;
                            jal(ctx, 0x51600Cu, gen::fn__GetEntryByPos_00515b18);
                            v1 = v0;
                            sw(v0, sp, 0x210);
                            if (v1 == 0) {
                                // 0x00516020
                                charge(ctx, 4);
                                lhu(v0, sp, 0x10);
                                v0 = v0 & 0x8000;
                                a1 = 0x7C0000;
                                if (v0 == 0) {
                                    goto L_00516078;
                                }
                                // 0x00516030
                                charge(ctx, 5);
                                a0 = s0;
                                a1 = addiu(a1, -6664);
                                jal(ctx, 0x516034u, gen::fn_strcmp_00524128);
                                v1 = addiu(fp, -0x4878);
                                if (v0 != 0) {
                                    goto L_00516078;
                                }
                                // 0x00516044
                                charge(ctx, 5);
                                v0 = 2200;
                                mult(v0, s3, v0);
                                a0 = 1;
                                v1 = addu(v1, v0);
                                sw(a0, v1, 2188);
                                goto L_00516058;
                            }
                        }
                    }
                } else {
                    // 0x00515f10
                    charge(ctx, 3);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x86;
                }
                // 0x005160e8 (the shared epilogue, written out on this path)
                charge(ctx, 12);
                ld(ra, sp, 0x2B0);
                ld(fp, sp, 0x2A0);
                ld(s7, sp, 0x290);
                ld(s6, sp, 0x280);
                ld(s5, sp, 0x270);
                ld(s4, sp, 0x260);
                ld(s3, sp, 0x250);
                ld(s2, sp, 0x240);
                ld(s1, sp, 0x230);
                ld(s0, sp, 0x220);
                sp = addiu(sp, 0x2C0);
                return;
            }
        L_00515eac:
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x6F;
            // 0x005160e8 (the shared epilogue, written out on this path)
            charge(ctx, 12);
            ld(ra, sp, 0x2B0);
            ld(fp, sp, 0x2A0);
            ld(s7, sp, 0x290);
            ld(s6, sp, 0x280);
            ld(s5, sp, 0x270);
            ld(s4, sp, 0x260);
            ld(s3, sp, 0x250);
            ld(s2, sp, 0x240);
            ld(s1, sp, 0x230);
            ld(s0, sp, 0x220);
            sp = addiu(sp, 0x2C0);
            return;
        }
    L_00516058:
        charge(ctx, 8);
        v1 = 2200;
        v0 = addiu(fp, -0x4878);
        mult(v1, s3, v1);
        v0 = addiu(v0, 2188);
        s0 = addu(v1, v0);
        lw(a0, s0, 0);
        if (a0 == 0) {
            goto L_00516078;
        }
        // 0x00516084
        charge(ctx, 2);
        a0 = s3;
        if (s6 != 0) {
            // 0x0051608c
            charge(ctx, 5);
            a1 = addiu(sp, 0x210);
            jal(ctx, 0x51608Cu, gen::fn__sceMcFatGetFreeClustSize_00515a40);
            lw(v1, sp, 0x210);
            a2 = v0;
            if (v1 == 0) {
                // 0x005160a8
                charge(ctx, 5);
                lw(v1, s0, 0);
                v0 = 2;
                sw(v0, s6, 0);
                sw(v1, s6, 4);
                sw(a2, s6, 8);
                goto L_005160bc;
            }
            // 0x005160a0
            charge(ctx, 2);
            v0 = v1;
            // 0x005160e8 (the shared epilogue, written out on this path)
            charge(ctx, 12);
            ld(ra, sp, 0x2B0);
            ld(fp, sp, 0x2A0);
            ld(s7, sp, 0x290);
            ld(s6, sp, 0x280);
            ld(s5, sp, 0x270);
            ld(s4, sp, 0x260);
            ld(s3, sp, 0x250);
            ld(s2, sp, 0x240);
            ld(s1, sp, 0x230);
            ld(s0, sp, 0x220);
            sp = addiu(sp, 0x2C0);
            return;
        }
    L_005160bc:
        charge(ctx, 8);
        v1 = 2200;
        v0 = addiu(fp, -0x4878);
        mult(v1, s3, v1);
        v0 = addiu(v0, 2184);
        v1 = addu(v1, v0);
        lw(a0, v1, 0);
        if (a0 == 0) {
            v0 = 0;
        } else {
            // 0x005160dc
            charge(ctx, 3);
            v0 = lui(0x8101);
            sw(zero, v1, 0);
            v0 = v0 | 0x9003;
        }
        // 0x005160e8 (the shared epilogue, written out on this path)
        charge(ctx, 12);
        ld(ra, sp, 0x2B0);
        ld(fp, sp, 0x2A0);
        ld(s7, sp, 0x290);
        ld(s6, sp, 0x280);
        ld(s5, sp, 0x270);
        ld(s4, sp, 0x260);
        ld(s3, sp, 0x250);
        ld(s2, sp, 0x240);
        ld(s1, sp, 0x230);
        ld(s0, sp, 0x220);
        sp = addiu(sp, 0x2C0);
        return;
    }
L_00515df8:
    charge(ctx, 3);
    v0 = lui(0x8101);
    v0 = v0 | 0x13;
    // 0x005160e8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x2B0);
    ld(fp, sp, 0x2A0);
    ld(s7, sp, 0x290);
    ld(s6, sp, 0x280);
    ld(s5, sp, 0x270);
    ld(s4, sp, 0x260);
    ld(s3, sp, 0x250);
    ld(s2, sp, 0x240);
    ld(s1, sp, 0x230);
    ld(s0, sp, 0x220);
    sp = addiu(sp, 0x2C0);
}

// 0x00516A48 _sceMcFatUnFormat -- 256 bytes; frame 0x50: s2 sp+0x30, ra sp+0x40, s1 sp+0x20, s0 sp+0x10
// Erase every block of the card and reset the port's FAT state.
void _sceMcFatUnFormat(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00516a48
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s2, sp, 0x30);
    s2 = a0;
    sd(ra, sp, 0x40);
    sd(s1, sp, 0x20);
    link(ctx, 0x516A5Cu);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x10);
    call(ctx, gen::fn__sceMcCoreGetConnection_0051c0c0);
    a0 = s2;
    if (v0 != 0) {
        // 0x00516a78
        charge(ctx, 4);
        a1 = sp;
        jal(ctx, 0x516A78u, gen::fn__sceMcpGetCardSpec_0051a180);
        lw(a3, sp, 0x4);
        if (v0 != 0) {
            // 0x00516a94
            charge(ctx, 26);
            v1 = 2200;
            lw(a0, sp, 0x8);
            mult(v1, s2, v1);
            v0 = 0x980000;
            t0 = si(-1);
            div(a0, a3);
            v0 = addiu(v0, -18552);  // &0x97B788
            t1 = addiu(v0, 2056);  // &0x97BF90
            t2 = 0x7C0000;
            a0 = addu(v0, v1);
            sw(zero, a0, 2196);
            a1 = a0;
            sw(t0, a1, 2048);
            a2 = a0;
            sw(t0, a2, 2052);
            v0 = a0;
            sw(zero, a0, 2192);
            v1 = addu(v1, t1);
            sw(zero, v0, 2188);
            a2 = addiu(t2, -6648);  // &0x7BE608
            lb(v0, a2, 0);  // 0x7BE608
            lb(a0, a2, 1);  // 0x7BE609
            sb(v0, v1, 0);
            sb(a0, v1, 1);
            if (a3 == 0) {
                brk(ctx, 0x516AF8u, 0x7u);
            }
            // 0x00516afc
            charge(ctx, 3);
            mflo(s1);
            s0 = 0;
            if (i64(s1) > 0) {
                // 0x00516b08
                charge(ctx, 2);
                a0 = s2;
                for (;;) {
                    // 0x00516b10
                    charge(ctx, 4);
                    a1 = s0;
                    jal(ctx, 0x516B10u, gen::fn__sceMcCoreBlockErase_0051bbd8);
                    s0 = addiu(s0, 1);
                    if (v0 == 0) {
                        backedge(ctx);
                        goto L_00516a88;
                    }
                    // 0x00516b20
                    charge(ctx, 3);
                    v0 = slt(s0, s1);
                    a0 = s2;
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00516b2c
            charge(ctx, 1);
            v0 = 0;
            // 0x00516b30 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x40);
            ld(s2, sp, 0x30);
            ld(s1, sp, 0x20);
            ld(s0, sp, 0x10);
            sp = addiu(sp, 0x50);
            return;
        }
    L_00516a88:
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x6F;
    } else {
        // 0x00516a6c
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x13;
    }
    // 0x00516b30 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x50);
}

// 0x00516B48 _ConfInsert -- 160 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// The checks before every file operation: card connected and not changed, formatted, authenticated; then the core
// write-back; 0 or the error code.
void _ConfInsert(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00516b48
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x516B54u, gen::fn__sceMcCoreGetConnection_0051c0c0);
    if (v0 != 0) {
        // 0x00516b64
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x516B64u, gen::fn__sceMcpCheckNewCard_0051a1a0);
        v1 = 2;
        cc = v0 == v1;  // the condition, before the delay slot changes it
        v1 = 0x980000;
        if (cc) {
            goto L_00516bc0;
        }
        // 0x00516b78
        charge(ctx, 8);
        v0 = 2200;
        mult(a1, s0, v0);
        a2 = addiu(v1, -18552);
        a0 = 1;
        v0 = addu(a2, a1);
        lw(v1, v0, 2184);
        if (v1 == a0) {
            goto L_00516bc0;
        }
        // 0x00516b98
        charge(ctx, 3);
        lw(v1, v0, 2188);
        if (v1 != 0) {
            // 0x00516bb0
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x516BB0u, gen::fn__sceMcpAuthentication_0051a1c0);
            if (v0 == 0) {
                goto L_00516bc0;
            }
            // 0x00516bcc
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x516BCCu, gen::fn__sceMcCoreWriteBack_0051b4a0);
            v0 = 0;
        } else {
            // 0x00516ba4
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x2F;
        }
        // 0x00516bd8 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_00516bc0:
    charge(ctx, 3);
    v0 = lui(0x8101);
    v0 = v0 | 0x13;
    // 0x00516bd8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00516BE8 _CheckFileDescript -- 96 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// Build the absolute path of a name (_make_path) and check its characters and component lengths; 0x81010016 /
// 0x8101005B on a bad name.
void _CheckFileDescript(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00516be8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a2;
    jal(ctx, 0x516BF4u, gen::fn__make_path_00515218);
    if (v0 != 0) {
        // 0x00516c04
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x516C04u, gen::fn_isCorrFname_00514e20);
        if (v0 == 0) {
            goto L_00516c14;
        }
        // 0x00516c20
        charge(ctx, 6);
        a0 = s0;
        jal(ctx, 0x516C20u, gen::fn_isCorrNameSize_00514db0);
        v1 = lui(0x8101);
        v1 = v1 | 0x5B;
        if (v0 != 0) v1 = 0;
        v0 = v1;
        // 0x00516c38 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_00516c14:
    charge(ctx, 3);
    v0 = lui(0x8101);
    v0 = v0 | 0x16;
    // 0x00516c38 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00516C48 _SearchEntry -- 628 bytes; frame 0x4B0: fp sp+0x490, s7 sp+0x480, s6 sp+0x470, s5 sp+0x460, s4 sp+0x450, s3 sp+0x440, s2 sp+0x430, ra sp+0x4A0, s1 sp+0x420, s0 sp+0x410
// Find a name in a directory chain (checks the "." / ".." entries of its first cluster), copying the 512-byte entry
// out and its index; 0x81010002 when absent.
void _SearchEntry(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00516c48
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x4B0);
    v0 = 1;
    sd(fp, sp, 0x490);
    sd(s7, sp, 0x480);
    fp = a3;
    sd(s6, sp, 0x470);
    s7 = a0;
    sd(s5, sp, 0x460);
    s6 = a2;
    sd(s4, sp, 0x450);
    s5 = 0;
    sd(s3, sp, 0x440);
    s4 = a1;
    sd(s2, sp, 0x430);
    s3 = t0;
    sd(ra, sp, 0x4A0);
    s2 = t1;
    sd(s1, sp, 0x420);
    sd(s0, sp, 0x410);
    sw(zero, sp, 0x400);
    sw(v0, sp, 0x404);
    for (;;) {
        // 0x00516e2c
        charge(ctx, 7);
        a0 = s7;
        a1 = sp;
        a2 = s3;
        a3 = 1;
        jal(ctx, 0x516E38u, gen::fn__sceMcpReadUserClust_0051a9e0);
        lw(t0, sp, 0x404);
        if (v0 == 0) {
            goto L_00516e48_25;
        }
        // 0x00516e54
        charge(ctx, 2);
        s0 = sp;
        if (t0 == 0) {
            backedge(ctx);
        } else {
            // 0x00516e5c
            charge(ctx, 7);
            s0 = addiu(sp, 0x40);
            sw(zero, sp, 0x404);
            a0 = s0;
            jal(ctx, 0x516E64u, gen::fn_strlen_00524388);
            v0 = sltiu(v0, 32);
            a2 = 0x7C0000;
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00516ca0
            charge(ctx, 5);
            a0 = s0;
            a1 = addiu(a2, -6672);
            jal(ctx, 0x516CA4u, gen::fn_strcmp_00524128);
            s0 = addiu(sp, 0x240);
            if (v0 != 0) {
                break;
            }
            // 0x00516cb4
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x516CB4u, gen::fn_strlen_00524388);
            v0 = sltiu(v0, 32);
            a3 = 0x7C0000;
            if (v0 == 0) {
                break;
            }
            // 0x00516cc8
            charge(ctx, 5);
            a0 = s0;
            a1 = addiu(a3, -6664);
            jal(ctx, 0x516CCCu, gen::fn_strcmp_00524128);
            s0 = sp;
            if (v0 != 0) {
                break;
            }
            goto L_00516cdc;
        }
    L_00516cdc:
        charge(ctx, 2);
        s1 = 0;
        if (s2 != 0) {
            // 0x00516ce4
            charge(ctx, 1);
            lhu(v0, s0, 0);
            for (;;) {
                // 0x00516ce8
                charge(ctx, 3);
                v0 = v0 & 0x8000;
                a0 = fp;
                if (v0 != 0) {
                    // 0x00516cf4
                    charge(ctx, 5);
                    sb(zero, s0, 95);
                    a1 = addiu(s0, 64);
                    jal(ctx, 0x516CF8u, gen::fn_strcmp_00524128);
                    cc = v0 != 0;  // the condition, before the delay slot changes it
                    v0 = slt(0, s2);
                    if (cc) {
                        goto L_00516dd0;
                    }
                    goto L_00516d08_8;
                }
                // 0x00516dcc
                charge(ctx, 1);
                v0 = slt(0, s2);
            L_00516dd0:
                charge(ctx, 6);
                s1 = addiu(s1, 1);
                s2 = subu(s2, v0);
                s0 = addiu(s0, 512);
                v0 = slti(s1, 2);
                s5 = addiu(s5, 1);
                if (v0 == 0) {
                    break;
                }
                // 0x00516de8
                charge(ctx, 2);
                if (s2 == 0) {
                    break;
                }
                lhu(v0, s0, 0);
                backedge(ctx);
            }
        }
        // 0x00516df0
        charge(ctx, 7);
        a1 = s3;
        a0 = s7;
        a2 = addiu(sp, 0x400);
        jal(ctx, 0x516DF8u, gen::fn__sceMcFatGetNextClust_00515730);
        lw(v1, sp, 0x400);
        s3 = v0;
        if (v1 != 0) {
            goto L_00516e0c_21;
        }
        // 0x00516e14
        charge(ctx, 4);
        v0 = lui(0xFFFF);
        v0 = v0 | 0xFFFF;
        cc = s3 == v0;  // the condition, before the delay slot changes it
        v0 = 0x7FFF0000;
        if (cc) {
            goto L_00516e84;
        }
        // 0x00516e24
        charge(ctx, 2);
        v0 = v0 | 0xFFFF;
        s3 = s3 & v0;
    }
    // 0x00516e78
    charge(ctx, 3);
    v0 = lui(0x8101);
    v0 = v0 | 0x9002;
    // 0x00516e8c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x4A0);
    ld(fp, sp, 0x490);
    ld(s7, sp, 0x480);
    ld(s6, sp, 0x470);
    ld(s5, sp, 0x460);
    ld(s4, sp, 0x450);
    ld(s3, sp, 0x440);
    ld(s2, sp, 0x430);
    ld(s1, sp, 0x420);
    ld(s0, sp, 0x410);
    sp = addiu(sp, 0x4B0);
    return;
L_00516d08_8:
    charge(ctx, 2);
    if (s4 != 0) {
        // 0x00516d10
        charge(ctx, 5);
        a1 = s4;
        v0 = s0 | a1;
        v0 = v0 & 0x7;
        v1 = s0;
        if (v0 == 0) {
            // 0x00516d84
            charge(ctx, 1);
            v0 = addiu(s0, 512);
            for (;;) {
                // 0x00516d88
                charge(ctx, 13);
                ld(t0, v1, 0);
                ld(a0, v1, 8);
                ld(a2, v1, 16);
                ld(a3, v1, 24);
                sd(t0, a1, 0);
                sd(a0, a1, 8);
                sd(a2, a1, 16);
                sd(a3, a1, 24);
                v1 = addiu(v1, 32);
                a1 = addiu(a1, 32);
                if (v1 == v0) {
                    break;
                }
                backedge(ctx);
            }
        } else {
            // 0x00516d24
            charge(ctx, 1);
            v0 = addiu(s0, 512);
            for (;;) {
                // 0x00516d28
                charge(ctx, 21);
                ldl(t0, v1, 7);
                ldr(t0, v1, 0);
                ldl(a0, v1, 15);
                ldr(a0, v1, 8);
                ldl(a2, v1, 23);
                ldr(a2, v1, 16);
                ldl(a3, v1, 31);
                ldr(a3, v1, 24);
                sdl(t0, a1, 7);
                sdr(t0, a1, 0);
                sdl(a0, a1, 15);
                sdr(a0, a1, 8);
                sdl(a2, a1, 23);
                sdr(a2, a1, 16);
                sdl(a3, a1, 31);
                sdr(a3, a1, 24);
                v1 = addiu(v1, 32);
                a1 = addiu(a1, 32);
                if (v1 == v0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00516d7c
            charge(ctx, 2);
        }
    }
    // 0x00516dbc
    charge(ctx, 2);
    if (s6 != 0) {
        sw(s5, s6, 0);
    }
    // 0x00516dc4
    charge(ctx, 2);
    v0 = 0;
    // 0x00516e8c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x4A0);
    ld(fp, sp, 0x490);
    ld(s7, sp, 0x480);
    ld(s6, sp, 0x470);
    ld(s5, sp, 0x460);
    ld(s4, sp, 0x450);
    ld(s3, sp, 0x440);
    ld(s2, sp, 0x430);
    ld(s1, sp, 0x420);
    ld(s0, sp, 0x410);
    sp = addiu(sp, 0x4B0);
    return;
L_00516e0c_21:
    charge(ctx, 2);
    v0 = v1;
    // 0x00516e8c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x4A0);
    ld(fp, sp, 0x490);
    ld(s7, sp, 0x480);
    ld(s6, sp, 0x470);
    ld(s5, sp, 0x460);
    ld(s4, sp, 0x450);
    ld(s3, sp, 0x440);
    ld(s2, sp, 0x430);
    ld(s1, sp, 0x420);
    ld(s0, sp, 0x410);
    sp = addiu(sp, 0x4B0);
    return;
L_00516e48_25:
    charge(ctx, 3);
    v0 = lui(0x8101);
    v0 = v0 | 0x6F;
    // 0x00516e8c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x4A0);
    ld(fp, sp, 0x490);
    ld(s7, sp, 0x480);
    ld(s6, sp, 0x470);
    ld(s5, sp, 0x460);
    ld(s4, sp, 0x450);
    ld(s3, sp, 0x440);
    ld(s2, sp, 0x430);
    ld(s1, sp, 0x420);
    ld(s0, sp, 0x410);
    sp = addiu(sp, 0x4B0);
    return;
L_00516e84:
    charge(ctx, 2);
    v0 = lui(0x8101);
    v0 = v0 | 0x2;
    // 0x00516e8c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x4A0);
    ld(fp, sp, 0x490);
    ld(s7, sp, 0x480);
    ld(s6, sp, 0x470);
    ld(s5, sp, 0x460);
    ld(s4, sp, 0x450);
    ld(s3, sp, 0x440);
    ld(s2, sp, 0x430);
    ld(s1, sp, 0x420);
    ld(s0, sp, 0x410);
    sp = addiu(sp, 0x4B0);
}

// 0x00516EC0 _SearchFile -- 1104 bytes; frame 0x4D0: s7 sp+0x4A0, fp sp+0x4B0, s5 sp+0x480, s1 sp+0x440, ra sp+0x4C0, s6 sp+0x490, s4 sp+0x470, s3 sp+0x460, s2 sp+0x450, s0 sp+0x430
// Walk an absolute path component by component from the root; returns 0x81010011 with the entry (and its parent /
// index) when found, 0x81010002 with the parent when the last component is missing.
void _SearchFile(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00516ec0
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x4D0);
    v1 = 388;
    sd(s7, sp, 0x4A0);
    v0 = 0x780000;
    s7 = a0;
    sd(fp, sp, 0x4B0);
    mult(v1, s7, v1);
    sd(s5, sp, 0x480);
    sd(s1, sp, 0x440);
    v0 = addiu(v0, 10208);  // &0x7827E0
    sw(a3, sp, 0x424);
    s5 = a2;
    sd(ra, sp, 0x4C0);
    s1 = a1;
    sd(s6, sp, 0x490);
    v1 = addu(v1, v0);
    sd(s4, sp, 0x470);
    sd(s3, sp, 0x460);
    a1 = sp;
    sd(s2, sp, 0x450);
    a3 = 0;
    sd(s0, sp, 0x430);
    fp = 0;
    sw(t0, sp, 0x428);
    link(ctx, 0x516F20u);  // $ra first: the delay slot below depends on it
    lw(a2, v1, 60);
    call(ctx, gen::fn__GetEntryByPos_00515b18);
    a0 = v0;
    ld(ra, sp, 0x4C0);
    if (a0 == 0) {
        // 0x00516f34
        charge(ctx, 6);
        s0 = addiu(sp, 0x40);
        a0 = s0;
        jal(ctx, 0x516F38u, gen::fn_strlen_00524388);
        v0 = sltiu(v0, 32);
        a1 = 0x7C0000;
        if (v0 != 0) {
            // 0x00516f4c
            charge(ctx, 5);
            a0 = s0;
            a1 = addiu(a1, -6672);
            jal(ctx, 0x516F50u, gen::fn_strcmp_00524128);
            if (v0 != 0) {
                goto L_00516f60;
            }
            v0 = 0x7C0000;
            // 0x00516f6c
            charge(ctx, 6);
            a0 = s1;
            s0 = addiu(v0, -6648);
            a1 = s0;
            jal(ctx, 0x516F74u, gen::fn_strcmp_00524128);
            a0 = s1;
            if (v0 != 0) {
                // 0x00517034
                charge(ctx, 13);
                a1 = s0;
                jal(ctx, 0x517034u, gen::fn__strtok_005150b0);
                s3 = lui(0x8101);
                v1 = addiu(sp, 0x420);
                s4 = lui(0x8101);
                sw(v1, sp, 0x42C);
                s0 = addiu(sp, 0x200);
                s2 = addiu(sp, 0x400);
                s1 = v0;
                s6 = 1;
                s3 = s3 | 0x2;
                s4 = s4 | 0x9FFF;
                a1 = s1;
                for (;;) {
                    // 0x00517068
                    charge(ctx, 11);
                    a0 = s2;
                    jal(ctx, 0x517068u, gen::fn_strcpy_00524270);
                    a2 = 0x7C0000;
                    a0 = 0;
                    a1 = addiu(a2, -6648);  // &0x7BE608
                    jal(ctx, 0x517078u, gen::fn__strtok_005150b0);
                    s1 = v0;
                    v1 = s0;
                    if (s1 == 0) fp = s6;
                    v0 = sp;
                    a0 = s0;
                    for (;;) {
                        // 0x00517094
                        charge(ctx, 13);
                        ld(a3, v0, 0);
                        ld(t0, v0, 8);
                        ld(a1, v0, 16);
                        ld(a2, v0, 24);
                        sd(a3, v1, 0);
                        sd(t0, v1, 8);
                        sd(a1, v1, 16);
                        sd(a2, v1, 24);
                        v0 = addiu(v0, 32);
                        v1 = addiu(v1, 32);
                        if (v0 == a0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x005170c8
                    charge(ctx, 11);
                    lw(t0, sp, 0x210);
                    a0 = s7;
                    lw(t1, sp, 0x204);
                    a1 = sp;
                    lw(a2, sp, 0x42C);
                    a3 = s2;
                    jal(ctx, 0x5170DCu, gen::fn__SearchEntry_00516c48);
                    lhu(v1, sp, 0x0);
                    v1 = v1 & 0x2000;
                    a0 = v0;
                    if (v1 != 0) {
                        goto L_005172d8;
                    }
                    // 0x005170f4
                    charge(ctx, 2);
                    if (fp == s6) {
                        goto L_00517114;
                    }
                    // 0x005170fc
                    charge(ctx, 2);
                    a1 = s1;
                    if (a0 != 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00517104
                charge(ctx, 4);
                v1 = a0 ^ s3;
                v0 = s4;
                if (v1 != 0) v0 = a0;
            } else {
                // 0x00516f84
                charge(ctx, 4);
                a2 = s5;
                v0 = a2 & 0x7;
                v1 = sp;
                if (v0 == 0) {
                    // 0x00516ff4
                    charge(ctx, 1);
                    v0 = addiu(sp, 0x200);
                    for (;;) {
                        // 0x00516ff8
                        charge(ctx, 13);
                        ld(a0, v1, 0);
                        ld(a1, v1, 8);
                        ld(a3, v1, 16);
                        ld(t0, v1, 24);
                        sd(a0, a2, 0);
                        sd(a1, a2, 8);
                        sd(a3, a2, 16);
                        sd(t0, a2, 24);
                        v1 = addiu(v1, 32);
                        a2 = addiu(a2, 32);
                        if (v1 == v0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0051702c
                    charge(ctx, 2);
                } else {
                    // 0x00516f94
                    charge(ctx, 1);
                    v0 = addiu(sp, 0x200);
                    for (;;) {
                        // 0x00516f98
                        charge(ctx, 21);
                        ldl(a0, v1, 7);
                        ldr(a0, v1, 0);
                        ldl(a1, v1, 15);
                        ldr(a1, v1, 8);
                        ldl(a3, v1, 23);
                        ldr(a3, v1, 16);
                        ldl(t0, v1, 31);
                        ldr(t0, v1, 24);
                        sdl(a0, a2, 7);
                        sdr(a0, a2, 0);
                        sdl(a1, a2, 15);
                        sdr(a1, a2, 8);
                        sdl(a3, a2, 23);
                        sdr(a3, a2, 16);
                        sdl(t0, a2, 31);
                        sdr(t0, a2, 24);
                        v1 = addiu(v1, 32);
                        a2 = addiu(a2, 32);
                        if (v1 == v0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00516fec
                    charge(ctx, 2);
                }
            L_005171e8:
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x11;
            }
            goto L_005172e0;
        }
    L_00516f60:
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x9002;
    L_005172e0:
        charge(ctx, 1);
        ld(ra, sp, 0x4C0);
    }
    // 0x005172e4 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(fp, sp, 0x4B0);
    ld(s7, sp, 0x4A0);
    ld(s6, sp, 0x490);
    ld(s5, sp, 0x480);
    ld(s4, sp, 0x470);
    ld(s3, sp, 0x460);
    ld(s2, sp, 0x450);
    ld(s1, sp, 0x440);
    ld(s0, sp, 0x430);
    sp = addiu(sp, 0x4D0);
    return;
L_00517114:
    charge(ctx, 2);
    if (a0 == 0) {
        // 0x0051711c
        charge(ctx, 2);
        lw(v1, sp, 0x428);
        if (s5 != 0) {
            // 0x00517124
            charge(ctx, 4);
            a2 = s5;
            v0 = a2 & 0x7;
            v1 = sp;
            if (v0 == 0) {
                for (;;) {
                    // 0x00517190
                    charge(ctx, 13);
                    ld(a1, v1, 0);
                    ld(a3, v1, 8);
                    ld(t0, v1, 16);
                    ld(v0, v1, 24);
                    sd(a1, a2, 0);
                    sd(a3, a2, 8);
                    sd(t0, a2, 16);
                    sd(v0, a2, 24);
                    v1 = addiu(v1, 32);
                    a2 = addiu(a2, 32);
                    if (v1 == s0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x005171c4
                charge(ctx, 1);
                lw(v1, sp, 0x428);
            } else {
                for (;;) {
                    // 0x00517134
                    charge(ctx, 21);
                    ldl(a3, v1, 7);
                    ldr(a3, v1, 0);
                    ldl(t0, v1, 15);
                    ldr(t0, v1, 8);
                    ldl(v0, v1, 23);
                    ldr(v0, v1, 16);
                    ldl(a0, v1, 31);
                    ldr(a0, v1, 24);
                    sdl(a3, a2, 7);
                    sdr(a3, a2, 0);
                    sdl(t0, a2, 15);
                    sdr(t0, a2, 8);
                    sdl(v0, a2, 23);
                    sdr(v0, a2, 16);
                    sdl(a0, a2, 31);
                    sdr(a0, a2, 24);
                    v1 = addiu(v1, 32);
                    a2 = addiu(a2, 32);
                    if (v1 == s0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00517188
                charge(ctx, 2);
                lw(v1, sp, 0x428);
            }
        }
        // 0x005171c8
        charge(ctx, 2);
        lw(v0, sp, 0x420);
        if (v1 != 0) {
            // 0x005171d0
            charge(ctx, 1);
            sw(v0, v1, 0);
        }
        // 0x005171d4
        charge(ctx, 3);
        lw(a0, sp, 0x424);
        if (a0 != 0) {
            // 0x005171e0
            charge(ctx, 2);
            lw(v0, sp, 0x210);
            sw(v0, a0, 0);
        }
        goto L_005171e8;
    }
    // 0x005171f4
    charge(ctx, 4);
    v0 = lui(0x8101);
    v0 = v0 | 0x2;
    cc = a0 != v0;  // the condition, before the delay slot changes it
    v0 = a0;
    if (!cc) {
        // 0x00517204
        charge(ctx, 2);
        lw(v0, sp, 0x428);
        if (s5 != 0) {
            // 0x0051720c
            charge(ctx, 4);
            a2 = s5;
            v0 = a2 & 0x7;
            v1 = s0;
            if (v0 == 0) {
                for (;;) {
                    // 0x00517278
                    charge(ctx, 13);
                    ld(a0, v1, 0);
                    ld(a1, v1, 8);
                    ld(a3, v1, 16);
                    ld(t0, v1, 24);
                    sd(a0, a2, 0);
                    sd(a1, a2, 8);
                    sd(a3, a2, 16);
                    sd(t0, a2, 24);
                    v1 = addiu(v1, 32);
                    a2 = addiu(a2, 32);
                    if (v1 == s2) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x005172ac
                charge(ctx, 1);
                lw(v0, sp, 0x428);
            } else {
                for (;;) {
                    // 0x0051721c
                    charge(ctx, 21);
                    ldl(a1, v1, 7);
                    ldr(a1, v1, 0);
                    ldl(a3, v1, 15);
                    ldr(a3, v1, 8);
                    ldl(t0, v1, 23);
                    ldr(t0, v1, 16);
                    ldl(v0, v1, 31);
                    ldr(v0, v1, 24);
                    sdl(a1, a2, 7);
                    sdr(a1, a2, 0);
                    sdl(a3, a2, 15);
                    sdr(a3, a2, 8);
                    sdl(t0, a2, 23);
                    sdr(t0, a2, 16);
                    sdl(v0, a2, 31);
                    sdr(v0, a2, 24);
                    v1 = addiu(v1, 32);
                    a2 = addiu(a2, 32);
                    if (v1 == s2) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00517270
                charge(ctx, 2);
                lw(v0, sp, 0x428);
            }
        }
        // 0x005172b0
        charge(ctx, 2);
        if (v0 != 0) {
            sw(zero, v0, 0);
        }
        // 0x005172b8
        charge(ctx, 3);
        lw(v1, sp, 0x424);
        if (v1 != 0) {
            // 0x005172c4
            charge(ctx, 2);
            lw(v0, sp, 0x210);
            sw(v0, v1, 0);
        }
        // 0x005172cc
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x2;
    }
    goto L_005172e0;
L_005172d8:
    charge(ctx, 2);
    v0 = lui(0x8101);
    v0 = v0 | 0xD;
    goto L_005172e0;
}

// 0x00517310 _SetEntryByPos -- 420 bytes; frame 0x90: s5 sp+0x60, s3 sp+0x40, s2 sp+0x30, s6 sp+0x70, s4 sp+0x50, s1 sp+0x20, s0 sp+0x10, ra sp+0x80
// Write directory entry N of a directory chain (read-modify-write of its cluster through the cluster cache).
void _SetEntryByPos(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00517310
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(s5, sp, 0x60);
    sd(s3, sp, 0x40);
    s5 = lui(0x8101);
    sd(s2, sp, 0x30);
    s3 = lui(0xFFFF);
    sd(s6, sp, 0x70);
    s2 = 0x7FFF0000;
    sd(s4, sp, 0x50);
    s6 = a1;
    sd(s1, sp, 0x20);
    s4 = a0;
    sd(s0, sp, 0x10);
    s1 = a3;
    sd(ra, sp, 0x80);
    s0 = a2;
    sw(zero, sp, 0x0);
    s5 = s5 | 0x6F;
    s3 = s3 | 0xFFFF;
    s2 = s2 | 0xFFFF;
    for (;;) {
        // 0x00517360
        charge(ctx, 3);
        v0 = slti(s1, 2);
        a0 = s4;
        if (v0 != 0) {
            goto L_0051736c_2;
        }
        // 0x00517454
        charge(ctx, 6);
        a1 = s0;
        a2 = sp;
        jal(ctx, 0x517458u, gen::fn__sceMcFatGetNextClust_00515730);
        lw(v1, sp, 0x0);
        s0 = v0;
        if (v1 != 0) {
            goto L_0051746c_10;
        }
        // 0x00517474
        charge(ctx, 2);
        cc = s0 == s3;  // the condition, before the delay slot changes it
        s0 = s0 & s2;
        if (cc) {
            break;
        }
        // 0x0051747c
        charge(ctx, 2);
        s1 = addiu(s1, -2);
        backedge(ctx);
    }
L_00517484:
    charge(ctx, 2);
    v0 = lui(0x8101);
    v0 = v0 | 0x6F;
    // 0x0051748c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x80);
    ld(s6, sp, 0x70);
    ld(s5, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x90);
    return;
L_0051736c_2:
    charge(ctx, 8);
    s3 = 0x980000;
    s2 = addiu(s3, -14144);  // &0x97C8C0
    a2 = s0;
    a1 = s2;
    a3 = 1;
    jal(ctx, 0x51737Cu, gen::fn__sceMcpReadUserClust_0051a9e0);
    v1 = sll(s1, 9);
    if (v0 == 0) {
        goto L_00517484;
    }
    // 0x0051738c
    charge(ctx, 6);
    a1 = s6;
    v1 = addu(v1, s2);
    v0 = a1 | v1;
    v0 = v0 & 0x7;
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = addiu(a1, 512);
    if (cc) {
        for (;;) {
            // 0x00517400
            charge(ctx, 13);
            ld(a0, a1, 0);
            ld(a2, a1, 8);
            ld(a3, a1, 16);
            ld(t0, a1, 24);
            sd(a0, v1, 0);
            sd(a2, v1, 8);
            sd(a3, v1, 16);
            sd(t0, v1, 24);
            a1 = addiu(a1, 32);
            v1 = addiu(v1, 32);
            if (a1 == v0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00517434
        charge(ctx, 1);
        a0 = s4;
    } else {
        for (;;) {
            // 0x005173a4
            charge(ctx, 21);
            ldl(a0, a1, 7);
            ldr(a0, a1, 0);
            ldl(a2, a1, 15);
            ldr(a2, a1, 8);
            ldl(a3, a1, 23);
            ldr(a3, a1, 16);
            ldl(t0, a1, 31);
            ldr(t0, a1, 24);
            sdl(a0, v1, 7);
            sdr(a0, v1, 0);
            sdl(a2, v1, 15);
            sdr(a2, v1, 8);
            sdl(a3, v1, 23);
            sdr(a3, v1, 16);
            sdl(t0, v1, 31);
            sdr(t0, v1, 24);
            a1 = addiu(a1, 32);
            v1 = addiu(v1, 32);
            if (a1 == v0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005173f8
        charge(ctx, 2);
        a0 = s4;
    }
    // 0x00517438
    charge(ctx, 7);
    a1 = addiu(s3, -14144);
    a2 = s0;
    a3 = 1;
    jal(ctx, 0x517440u, gen::fn__sceMcpWriteUserClust_0051aa90);
    if (v0 != 0) s5 = 0;
    v0 = s5;
    // 0x0051748c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x80);
    ld(s6, sp, 0x70);
    ld(s5, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x90);
    return;
L_0051746c_10:
    charge(ctx, 2);
    v0 = v1;
    // 0x0051748c (the shared epilogue, written out on this path)
    charge(ctx, 10);
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

// 0x005174B8 _GetFreeEntrySize -- 300 bytes; frame 0xA0: s3 sp+0x30, fp sp+0x80, s7 sp+0x70, s6 sp+0x60, s5 sp+0x50, s4 sp+0x40, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0, ra sp+0x90
// Count the free entries of a directory chain (for the space checks of create).
void _GetFreeEntrySize(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005174b8
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    v0 = 0x980000;
    sd(s3, sp, 0x30);
    sd(fp, sp, 0x80);
    s3 = a3;
    sd(s7, sp, 0x70);
    fp = addiu(v0, -0x3740);  // &0x97C8C0
    sd(s6, sp, 0x60);
    s7 = lui(0x8101);
    sd(s5, sp, 0x50);
    s6 = lui(0xFFFF);
    sd(s4, sp, 0x40);
    s5 = 0x7FFF0000;
    sd(s2, sp, 0x20);
    s4 = a0;
    sd(s1, sp, 0x10);
    s2 = a2;
    sd(s0, sp, 0x0);
    s1 = 0;
    sd(ra, sp, 0x90);
    s0 = a1;
    sw(zero, s3, 0);
    s7 = s7 | 0x6F;
    s6 = s6 | 0xFFFF;
    s5 = s5 | 0xFFFF;
    a0 = s4;
    for (;;) {
        // 0x00517520
        charge(ctx, 6);
        a1 = fp;
        a2 = s0;
        a3 = 1;
        jal(ctx, 0x517528u, gen::fn__sceMcpReadUserClust_0051a9e0);
        a1 = 0;
        if (v0 == 0) {
            goto L_00517538_2;
        }
        // 0x00517544
        charge(ctx, 1);
        a0 = fp;
        for (;;) {
            // 0x00517548
            charge(ctx, 6);
            lhu(v0, a0, 0);
            v1 = addiu(s1, 1);
            s2 = addiu(s2, -1);
            v0 = v0 & 0x8000;
            if (v0 == 0) s1 = v1;
            if (s2 == 0) {
                goto L_005175a4;
            }
            // 0x00517560
            charge(ctx, 4);
            a1 = addiu(a1, 1);
            v0 = slti(a1, 2);
            a0 = addiu(a0, 512);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00517570
        charge(ctx, 7);
        a1 = s0;
        a0 = s4;
        a2 = s3;
        jal(ctx, 0x517578u, gen::fn__sceMcFatGetNextClust_00515730);
        lw(v1, s3, 0);
        s0 = v0;
        if (v1 != 0) {
            goto L_0051758c_7;
        }
        // 0x00517594
        charge(ctx, 2);
        cc = s0 == s6;  // the condition, before the delay slot changes it
        s0 = s0 & s5;
        if (cc) {
            goto L_005175b0;
        }
        // 0x0051759c
        charge(ctx, 2);
        a0 = s4;
        backedge(ctx);
    }
L_005175a4:
    charge(ctx, 3);
    v0 = addiu(s1, 1);
    if (a1 != 0) v0 = s1;
    // 0x005175b4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x90);
    ld(fp, sp, 0x80);
    ld(s7, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_00517538_2:
    charge(ctx, 3);
    sw(s7, s3, 0);
    v0 = si(-1);
    // 0x005175b4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x90);
    ld(fp, sp, 0x80);
    ld(s7, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_0051758c_7:
    charge(ctx, 2);
    v0 = si(-1);
    // 0x005175b4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x90);
    ld(fp, sp, 0x80);
    ld(s7, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_005175b0:
    charge(ctx, 1);
    v0 = s1;
    // 0x005175b4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x90);
    ld(fp, sp, 0x80);
    ld(s7, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x005175E8 _CreateEntry -- 1228 bytes; frame 0x4B0: s2 sp+0x430, s7 sp+0x480, s5 sp+0x460, s4 sp+0x450, s3 sp+0x440, s1 sp+0x420, ra sp+0x4A0, fp sp+0x490, s6 sp+0x470, s0 sp+0x410
// Create a directory entry in a parent: takes a free slot (or appends a cluster to the parent chain), writes the
// entry, and for a directory its first cluster with "." and "..".
void _CreateEntry(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005175e8
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x4B0);
    v0 = si(-1);
    sd(s2, sp, 0x430);
    s2 = a2;
    sw(v0, sp, 0x210);
    sd(s7, sp, 0x480);
    v0 = sltiu(s2, 1);
    sd(s5, sp, 0x460);
    s7 = lui(0x8101);
    sd(s4, sp, 0x450);
    s5 = a1;
    sd(s3, sp, 0x440);
    s4 = a0;
    sd(s1, sp, 0x420);
    s3 = a3;
    sd(ra, sp, 0x4A0);
    s1 = t0;
    sd(fp, sp, 0x490);
    s7 = s7 | 0x6F;
    sd(s6, sp, 0x470);
    sd(s0, sp, 0x410);
    sw(v0, sp, 0x404);
    sw(zero, sp, 0x400);
    for (;;) {
        // 0x00517648
        charge(ctx, 8);
        a0 = s4;
        a1 = 0x980000;
        a1 = addiu(a1, -14144);  // &0x97C8C0
        a2 = s2;
        a3 = 1;
        jal(ctx, 0x517658u, gen::fn__sceMcpReadUserClust_0051a9e0);
        s6 = 0;
        if (v0 == 0) {
            goto L_00517a7c;
        }
        // 0x00517668
        charge(ctx, 4);
        s0 = 0x980000;
        s0 = addiu(s0, -14144);  // &0x97C8C0
        fp = 0x7C0000;
        for (;;) {
            // 0x00517678
            charge(ctx, 4);
            lhu(v0, s0, 0);
            v0 = v0 & 0x8000;
            a0 = addiu(s0, 64);
            if (v0 == 0) {
                goto L_00517758;
            }
            // 0x00517688
            charge(ctx, 4);
            a1 = addiu(fp, -0x1A10);
            jal(ctx, 0x517688u, gen::fn_strcmp_00524128);
            if (v0 != 0) {
                lhu(v0, s0, 0);
            } else {
                // 0x00517698
                charge(ctx, 4);
                a0 = addiu(sp, 0x200);
                v0 = s0 & 0x7;
                v1 = s0;
                if (v0 == 0) {
                    // 0x00517708
                    charge(ctx, 1);
                    v0 = addiu(s0, 512);
                    for (;;) {
                        // 0x0051770c
                        charge(ctx, 13);
                        ld(t1, v1, 0);
                        ld(a1, v1, 8);
                        ld(a2, v1, 16);
                        ld(a3, v1, 24);
                        sd(t1, a0, 0);
                        sd(a1, a0, 8);
                        sd(a2, a0, 16);
                        sd(a3, a0, 24);
                        v1 = addiu(v1, 32);
                        a0 = addiu(a0, 32);
                        if (v1 == v0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00517740
                    charge(ctx, 1);
                    lhu(v0, s0, 0);
                } else {
                    // 0x005176a8
                    charge(ctx, 1);
                    v0 = addiu(s0, 512);
                    for (;;) {
                        // 0x005176ac
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
                    // 0x00517700
                    charge(ctx, 2);
                    lhu(v0, s0, 0);
                }
            }
            // 0x00517744
            charge(ctx, 3);
            v0 = v0 & 0x8000;
            if (v0 == 0) {
                a0 = s0;
                goto L_0051775c;
            }
            // 0x00517750
            charge(ctx, 2);
            lw(t0, sp, 0x400);
            if (s3 == 0) {
                goto L_00517758;
            }
            // 0x00517844
            charge(ctx, 8);
            v0 = slt(0, s3);
            s6 = addiu(s6, 1);
            s3 = subu(s3, v0);
            t0 = addiu(t0, 1);
            s0 = addiu(s0, 512);
            v0 = slti(s6, 2);
            sw(t0, sp, 0x400);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00517864
        charge(ctx, 3);
        lw(t1, sp, 0x404);
        s0 = s2;
        if (t1 == 0) {
            // 0x00517870
            charge(ctx, 3);
            v0 = slti(t0, 20);
            a0 = s4;
            if (v0 != 0) {
                goto L_00517894;
            }
            goto L_0051787c_29;
        }
        // 0x00517890
        charge(ctx, 1);
        a0 = s4;
    L_00517894:
        charge(ctx, 7);
        a1 = s0;
        a2 = s1;
        jal(ctx, 0x517898u, gen::fn__sceMcFatGetNextClust_00515730);
        lw(v1, s1, 0);
        s2 = v0;
        v0 = si(-1);
        if (v1 == 0) {
            // 0x005178b0
            charge(ctx, 4);
            v0 = lui(0xFFFF);
            v0 = v0 | 0xFFFF;
            cc = s2 != v0;  // the condition, before the delay slot changes it
            v0 = 0x7FFF0000;
            if (!cc) {
                goto L_005178c0_33;
            }
            // 0x00517a5c
            charge(ctx, 3);
            v0 = v0 | 0xFFFF;
            s2 = s2 & v0;
            backedge(ctx);
            continue;
        }
        break;
    }
    // 0x00517a84 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x4A0);
    ld(fp, sp, 0x490);
    ld(s7, sp, 0x480);
    ld(s6, sp, 0x470);
    ld(s5, sp, 0x460);
    ld(s4, sp, 0x450);
    ld(s3, sp, 0x440);
    ld(s2, sp, 0x430);
    ld(s1, sp, 0x420);
    ld(s0, sp, 0x410);
    sp = addiu(sp, 0x4B0);
    return;
L_00517758:
    charge(ctx, 1);
    a0 = s0;
L_0051775c:
    charge(ctx, 4);
    v0 = s5 | a0;
    v0 = v0 & 0x7;
    v1 = s5;
    if (v0 == 0) {
        // 0x005177cc
        charge(ctx, 1);
        v0 = addiu(s5, 512);
        for (;;) {
            // 0x005177d0
            charge(ctx, 13);
            ld(a3, v1, 0);
            ld(t0, v1, 8);
            ld(t1, v1, 16);
            ld(a1, v1, 24);
            sd(a3, a0, 0);
            sd(t0, a0, 8);
            sd(t1, a0, 16);
            sd(a1, a0, 24);
            v1 = addiu(v1, 32);
            a0 = addiu(a0, 32);
            if (v1 == v0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00517804
        charge(ctx, 1);
        a2 = 0x980000;
    } else {
        // 0x0051776c
        charge(ctx, 1);
        v0 = addiu(s5, 512);
        for (;;) {
            // 0x00517770
            charge(ctx, 21);
            ldl(t0, v1, 7);
            ldr(t0, v1, 0);
            ldl(t1, v1, 15);
            ldr(t1, v1, 8);
            ldl(a1, v1, 23);
            ldr(a1, v1, 16);
            ldl(a2, v1, 31);
            ldr(a2, v1, 24);
            sdl(t0, a0, 7);
            sdr(t0, a0, 0);
            sdl(t1, a0, 15);
            sdr(t1, a0, 8);
            sdl(a1, a0, 23);
            sdr(a1, a0, 16);
            sdl(a2, a0, 31);
            sdr(a2, a0, 24);
            v1 = addiu(v1, 32);
            a0 = addiu(a0, 32);
            if (v1 == v0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005177c4
        charge(ctx, 2);
        a2 = 0x980000;
    }
    // 0x00517808
    charge(ctx, 7);
    a0 = s4;
    a1 = addiu(a2, -14144);
    a3 = 1;
    a2 = s2;
    jal(ctx, 0x517814u, gen::fn__sceMcpWriteUserClust_0051aa90);
    if (v0 == 0) {
        sw(s7, s1, 0);
    L_00517a80:
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x00517824
        charge(ctx, 2);
        if (s3 != 0) {
            sw(zero, s1, 0);
        L_00517a54:
            charge(ctx, 2);
            lw(v0, sp, 0x400);
        } else {
            // 0x0051782c
            charge(ctx, 4);
            lw(a2, sp, 0x210);
            a3 = si(-1);
            cc = a2 == a3;  // the condition, before the delay slot changes it
            lw(a3, sp, 0x214);
            if (!cc) {
                // 0x0051783c
                charge(ctx, 2);
                a0 = s4;
            L_00517a18:
                charge(ctx, 4);
                a1 = sp;
                jal(ctx, 0x517A18u, gen::fn__GetEntryByPos_00515b18);
                sw(v0, s1, 0);
                if (v0 != 0) {
                    goto L_00517a80;
                }
                // 0x00517a28
                charge(ctx, 10);
                lw(v0, sp, 0x4);
                a0 = s4;
                lw(a2, sp, 0x210);
                a1 = sp;
                v0 = addiu(v0, 1);
                lw(a3, sp, 0x214);
                link(ctx, 0x517A40u);  // $ra first: the delay slot below depends on it
                sw(v0, sp, 0x4);
                call(ctx, gen::fn__SetEntryByPos_00517310);
                sw(v0, s1, 0);
                if (v0 != 0) {
                    goto L_00517a80;
                }
                // 0x00517a50
                charge(ctx, 1);
                sw(zero, s1, 0);
                goto L_00517a54;
            }
            // 0x00517a68
            charge(ctx, 5);
            v1 = lui(0x8101);
            v0 = si(-1);
            v1 = v1 | 0x9002;
            sw(v1, s1, 0);
        }
    }
    // 0x00517a84 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x4A0);
    ld(fp, sp, 0x490);
    ld(s7, sp, 0x480);
    ld(s6, sp, 0x470);
    ld(s5, sp, 0x460);
    ld(s4, sp, 0x450);
    ld(s3, sp, 0x440);
    ld(s2, sp, 0x430);
    ld(s1, sp, 0x420);
    ld(s0, sp, 0x410);
    sp = addiu(sp, 0x4B0);
    return;
L_0051787c_29:
    charge(ctx, 5);
    v1 = lui(0x8101);
    v0 = si(-1);
    v1 = v1 | 0x17;
    sw(v1, s1, 0);
    // 0x00517a84 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x4A0);
    ld(fp, sp, 0x490);
    ld(s7, sp, 0x480);
    ld(s6, sp, 0x470);
    ld(s5, sp, 0x460);
    ld(s4, sp, 0x450);
    ld(s3, sp, 0x440);
    ld(s2, sp, 0x430);
    ld(s1, sp, 0x420);
    ld(s0, sp, 0x410);
    sp = addiu(sp, 0x4B0);
    return;
L_005178c0_33:
    charge(ctx, 6);
    a0 = s4;
    a1 = s1;
    jal(ctx, 0x5178C4u, gen::fn__sceMcFatGetFreeClust_00515910);
    lw(v1, s1, 0);
    s2 = v0;
    if (v1 != 0) {
        goto L_00517a80;
    }
    // 0x005178d8
    charge(ctx, 9);
    a2 = lui(0x8000);
    a1 = s0;
    a2 = s2 | a2;
    a0 = s4;
    a3 = s1;
    jal(ctx, 0x5178E8u, gen::fn__sceMcFatWriteFatData_005157e0);
    lw(v1, s1, 0);
    v0 = si(-1);
    if (v1 == 0) {
        // 0x005178fc
        charge(ctx, 8);
        a0 = s4;
        a1 = s2;
        a2 = si(-1);
        a3 = s1;
        jal(ctx, 0x517908u, gen::fn__sceMcFatWriteFatData_005157e0);
        lw(v1, s1, 0);
        v0 = si(-1);
        if (v1 == 0) {
            // 0x0051791c
            charge(ctx, 7);
            v0 = 0x980000;
            a1 = s5;
            s0 = addiu(v0, -14144);  // &0x97C8C0
            v0 = a1 | s0;
            v0 = v0 & 0x7;
            a2 = s0;
            if (v0 == 0) {
                // 0x0051799c
                charge(ctx, 2);
                v0 = addiu(s0, 512);
                v1 = addiu(a1, 512);
                for (;;) {
                    // 0x005179a4
                    charge(ctx, 13);
                    ld(a0, a1, 0);
                    ld(a3, a1, 8);
                    ld(t0, a1, 16);
                    ld(t1, a1, 24);
                    sd(a0, a2, 0);
                    sd(a3, a2, 8);
                    sd(t0, a2, 16);
                    sd(t1, a2, 24);
                    a1 = addiu(a1, 32);
                    a2 = addiu(a2, 32);
                    if (a1 == v1) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x005179d8
                charge(ctx, 1);
                sh(zero, v0, 0);
            } else {
                // 0x00517938
                charge(ctx, 2);
                v0 = addiu(s0, 512);
                v1 = addiu(a1, 512);
                for (;;) {
                    // 0x00517940
                    charge(ctx, 21);
                    ldl(a0, a1, 7);
                    ldr(a0, a1, 0);
                    ldl(a3, a1, 15);
                    ldr(a3, a1, 8);
                    ldl(t0, a1, 23);
                    ldr(t0, a1, 16);
                    ldl(t1, a1, 31);
                    ldr(t1, a1, 24);
                    sdl(a0, a2, 7);
                    sdr(a0, a2, 0);
                    sdl(a3, a2, 15);
                    sdr(a3, a2, 8);
                    sdl(t0, a2, 23);
                    sdr(t0, a2, 16);
                    sdl(t1, a2, 31);
                    sdr(t1, a2, 24);
                    a1 = addiu(a1, 32);
                    a2 = addiu(a2, 32);
                    if (a1 == v1) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00517994
                charge(ctx, 2);
                sh(zero, v0, 0);
            }
            // 0x005179dc
            charge(ctx, 8);
            a2 = s2;
            v0 = 0x980000;
            a0 = s4;
            a1 = addiu(v0, -14144);  // &0x97C8C0
            a3 = 1;
            jal(ctx, 0x5179ECu, gen::fn__sceMcpWriteUserClust_0051aa90);
            lw(a2, sp, 0x210);
            if (v0 == 0) {
            L_00517a7c:
                charge(ctx, 1);
                sw(s7, s1, 0);
                goto L_00517a80;
            }
            // 0x005179fc
            charge(ctx, 3);
            v1 = si(-1);
            lw(a3, sp, 0x214);
            if (a2 != v1) {
                // 0x00517a14
                charge(ctx, 1);
                a0 = s4;
                goto L_00517a18;
            }
            // 0x00517a08
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x9002;
        }
    }
    // 0x00517a84 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x4A0);
    ld(fp, sp, 0x490);
    ld(s7, sp, 0x480);
    ld(s6, sp, 0x470);
    ld(s5, sp, 0x460);
    ld(s4, sp, 0x450);
    ld(s3, sp, 0x440);
    ld(s2, sp, 0x430);
    ld(s1, sp, 0x420);
    ld(s0, sp, 0x410);
    sp = addiu(sp, 0x4B0);
}

// 0x00517AB8 _ParentDirUpdate -- 300 bytes; frame 0x430: s0 sp+0x400, s1 sp+0x410, ra sp+0x420
// Update the parent directory's entry after a change (its length / modification time).
void _ParentDirUpdate(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00517ab8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x430);
    a3 = 0;
    sd(s0, sp, 0x400);
    s0 = a2;
    sd(s1, sp, 0x410);
    s1 = a0;
    a2 = a1;
    sd(ra, sp, 0x420);
    a1 = addiu(sp, 0x200);
    jal(ctx, 0x517AD8u, gen::fn__GetEntryByPos_00515b18);
    ld(ra, sp, 0x420);
    if (v0 == 0) {
        // 0x00517ae8
        charge(ctx, 6);
        a1 = 0x7C0000;
        a0 = addiu(sp, 0x240);
        a1 = addiu(a1, -6672);  // &0x7BE5F0
        jal(ctx, 0x517AF0u, gen::fn_strcmp_00524128);
        lw(a2, sp, 0x210);
        if (v0 != 0) {
            // 0x00517b00
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x9002;
            goto L_00517bd0;
        }
        // 0x00517b0c
        charge(ctx, 6);
        a0 = s1;
        lw(a3, sp, 0x214);
        a1 = sp;
        jal(ctx, 0x517B14u, gen::fn__GetEntryByPos_00515b18);
        ld(ra, sp, 0x420);
        if (v0 == 0) {
            // 0x00517b24
            charge(ctx, 43);
            lbu(a1, s0, 7);
            v1 = 10;
            lbu(a3, s0, 3);
            a0 = s1;
            lbu(a2, s0, 2);
            v0 = srl(a1, 4);
            lbu(t7, s0, 1);
            t3 = srl(a3, 4);
            lbu(t4, s0, 6);
            t0 = srl(a2, 4);
            lbu(t1, s0, 5);
            t6 = srl(t7, 4);
            t5 = srl(t4, 4);
            mult(v0, v0, v1);
            t2 = srl(t1, 4);
            mult1(t3, t3, v1);
            mult(t0, t0, v1);
            a1 = a1 & 0xF;
            mult(t6, t6, v1);
            a3 = a3 & 0xF;
            mult1(t5, t5, v1);
            a2 = a2 & 0xF;
            mult(t2, t2, v1);
            v0 = addu(v0, a1);
            t3 = addu(t3, a3);
            t0 = addu(t0, a2);
            t4 = t4 & 0xF;
            t1 = t1 & 0xF;
            t7 = t7 & 0xF;
            t5 = addu(t5, t4);
            t2 = addu(t2, t1);
            t6 = addu(t6, t7);
            v0 = addiu(v0, 2000);
            lw(a2, sp, 0x210);
            lw(a3, sp, 0x214);
            a1 = sp;
            sh(v0, sp, 0x1E);
            sb(t5, sp, 0x1D);
            sb(t2, sp, 0x1C);
            sb(t3, sp, 0x1B);
            sb(t0, sp, 0x1A);
            link(ctx, 0x517BC8u);  // $ra first: the delay slot below depends on it
            sb(t6, sp, 0x19);
            call(ctx, gen::fn__SetEntryByPos_00517310);
        L_00517bd0:
            charge(ctx, 1);
            ld(ra, sp, 0x420);
        }
    }
    // 0x00517bd4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x410);
    ld(s0, sp, 0x400);
    sp = addiu(sp, 0x430);
}

// 0x00517BE8 _sceMcFatSearchFile -- 240 bytes; frame 0x300: s1 sp+0x2B0, s4 sp+0x2E0, s2 sp+0x2C0, s0 sp+0x2A0, ra sp+0x2F0, s3 sp+0x2D0
// Look a path up and return its {created, modified, length, mode, name} record.
void _sceMcFatSearchFile(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00517be8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x300);
    sd(s1, sp, 0x2B0);
    sd(s4, sp, 0x2E0);
    s1 = a0;
    sd(s2, sp, 0x2C0);
    s4 = a1;
    sd(s0, sp, 0x2A0);
    s2 = a2;
    sd(ra, sp, 0x2F0);
    link(ctx, 0x517C0Cu);  // $ra first: the delay slot below depends on it
    sd(s3, sp, 0x2D0);
    call(ctx, gen::fn__ConfInsert_00516b48);
    s0 = v0;
    ld(ra, sp, 0x2F0);
    if (s0 == 0) {
        // 0x00517c20
        charge(ctx, 8);
        s3 = addiu(sp, 0x220);
        a1 = s4;
        a0 = s1;
        a2 = s3;
        jal(ctx, 0x517C2Cu, gen::fn__CheckFileDescript_00516be8);
        s0 = v0;
        ld(ra, sp, 0x2F0);
        if (s0 == 0) {
            // 0x00517c40
            charge(ctx, 12);
            a0 = s1;
            a1 = s3;
            a2 = sp;
            a3 = 0;
            t0 = 0;
            s0 = 0;
            jal(ctx, 0x517C54u, gen::fn__SearchFile_00516ec0);
            v1 = lui(0x8101);
            v1 = v1 | 0x11;
            a0 = v0 ^ v1;
            if (a0 != 0) s0 = v0;
            if (s2 != 0) {
                // 0x00517c70
                charge(ctx, 2);
                v0 = s0;
                if (s0 == 0) {
                    // 0x00517c78
                    charge(ctx, 15);
                    a0 = addiu(s2, 24);
                    a1 = addiu(sp, 0x40);
                    jal(ctx, 0x517C7Cu, gen::fn_strcpy_00524270);
                    lw(v1, sp, 0x4);
                    lhu(v0, sp, 0x0);
                    ldl(a0, sp, 0xF);
                    ldr(a0, sp, 0x8);
                    sdl(a0, s2, 7);
                    sdr(a0, s2, 0);
                    ldl(a0, sp, 0x1F);
                    ldr(a0, sp, 0x18);
                    sdl(a0, s2, 15);
                    sdr(a0, s2, 8);
                    sh(v0, s2, 20);
                    sw(v1, s2, 16);
                    goto L_00517cb4;
                }
                goto L_00517cb8;
            }
        L_00517cb4:
            charge(ctx, 1);
            v0 = s0;
        L_00517cb8:
            charge(ctx, 1);
            ld(ra, sp, 0x2F0);
        }
    }
    // 0x00517cbc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s4, sp, 0x2E0);
    ld(s3, sp, 0x2D0);
    ld(s2, sp, 0x2C0);
    ld(s1, sp, 0x2B0);
    ld(s0, sp, 0x2A0);
    sp = addiu(sp, 0x300);
}

// 0x00517CD8 _sceMcFatCreateFile -- 1420 bytes; frame 0x540: s4 sp+0x4E0, s5 sp+0x4F0, s0 sp+0x4A0, ra sp+0x530, fp sp+0x520, s7 sp+0x510, s6 sp+0x500, s3 sp+0x4D0, s2 sp+0x4C0, s1 sp+0x4B0
// Create a file or directory: checks the name, the parent, free clusters and entries, allocates the first cluster,
// writes the entry with the card clock, updates the parent, flushes the caches.
void _sceMcFatCreateFile(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00517cd8
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x540);
    sd(s4, sp, 0x4E0);
    sd(s5, sp, 0x4F0);
    s4 = a0;
    sd(s0, sp, 0x4A0);
    s5 = a2;
    sd(ra, sp, 0x530);
    s0 = a1;
    sd(fp, sp, 0x520);
    sd(s7, sp, 0x510);
    sd(s6, sp, 0x500);
    sd(s3, sp, 0x4D0);
    sd(s2, sp, 0x4C0);
    link(ctx, 0x517D0Cu);  // $ra first: the delay slot below depends on it
    sd(s1, sp, 0x4B0);
    call(ctx, gen::fn__ConfInsert_00516b48);
    v1 = v0;
    sw(v0, sp, 0x490);
    if (v1 == 0) {
        // 0x00517d20
        charge(ctx, 8);
        s2 = addiu(sp, 0x400);
        a1 = s0;
        a0 = s4;
        a2 = s2;
        jal(ctx, 0x517D2Cu, gen::fn__CheckFileDescript_00516be8);
        v1 = v0;
        sw(v0, sp, 0x490);
        if (v1 != 0) {
            goto L_00518234;
        }
        // 0x00517d40
        charge(ctx, 5);
        v0 = 0x8417;
        if (s5 == 0) s5 = v0;
        s7 = s5 & 0x20;
        s6 = s7;
        if (s7 != 0) {
            // 0x00517d54
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x517D54u, gen::fn__get_dir_nest_005151d0);
            v0 = slti(v0, 2);
            if (v0 != 0) {
                goto L_00517d74;
            }
            // 0x00517d68
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x9004;
            goto L_00518234;
        }
    L_00517d74:
        charge(ctx, 15);
        a0 = s2;
        jal(ctx, 0x517D74u, gen::fn__get_dir_nest_005151d0);
        v0 = v0 ^ 0x1;
        a0 = s4;
        s0 = sltiu(v0, 1);
        a1 = s2;
        a2 = sp;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x517D94u, gen::fn__SearchFile_00516ec0);
        v1 = lui(0x8101);
        a0 = v0;
        v1 = v1 | 0x2;
        sw(v0, sp, 0x490);
        if (a0 != v1) {
            goto L_00518234;
        }
        // 0x00517db0
        charge(ctx, 2);
        s1 = addiu(sp, 0x490);
        if (s0 == 0) {
            // 0x00517db8
            charge(ctx, 5);
            lw(v0, sp, 0x4);
            v0 = subu(v0, s3);
            v0 = slti(v0, 20);
            a0 = s4;
            if (v0 != 0) {
                goto L_00517ddc;
            }
            // 0x00517dcc
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x17;
            goto L_00518234;
        }
        // 0x00517dd8
        charge(ctx, 1);
        a0 = s4;
    L_00517ddc:
        charge(ctx, 5);
        a1 = s1;
        jal(ctx, 0x517DDCu, gen::fn__sceMcFatGetFreeClustSize_00515a40);
        lw(v1, sp, 0x490);
        s0 = v0;
        if (v1 != 0) {
            // 0x00517df0
            charge(ctx, 2);
            v0 = v1;
            goto L_00518234;
        }
        // 0x00517df8
        charge(ctx, 9);
        lw(a1, sp, 0x10);
        a0 = s4;
        lw(a2, sp, 0x4);
        a3 = s1;
        jal(ctx, 0x517E04u, gen::fn__GetFreeEntrySize_005174b8);
        s3 = v0;
        lw(v0, sp, 0x490);
        ld(ra, sp, 0x530);
        if (v0 == 0) {
            // 0x00517e1c
            charge(ctx, 8);
            v0 = slt(0, s3);
            v1 = 1;
            a0 = 2;
            s0 = addu(v0, s0);
            if (s6 != 0) v1 = a0;
            v1 = slt(s0, v1);
            if (v1 == 0) {
                // 0x00517e48
                charge(ctx, 2);
                a0 = s4;
                if (s7 != 0) {
                    // 0x00517e50
                    charge(ctx, 6);
                    a1 = s1;
                    jal(ctx, 0x517E50u, gen::fn__sceMcFatGetFreeClust_00515910);
                    fp = v0;
                    lw(v0, sp, 0x490);
                    ld(ra, sp, 0x530);
                    if (v0 == 0) {
                        // 0x00517e68
                        charge(ctx, 8);
                        a0 = s4;
                        a1 = fp;
                        a2 = si(-1);
                        a3 = s1;
                        jal(ctx, 0x517E74u, gen::fn__sceMcFatWriteFatData_005157e0);
                        lw(v0, sp, 0x490);
                        ld(ra, sp, 0x530);
                        if (v0 == 0) {
                            goto L_00517e88;
                        }
                    }
                    // 0x00518238 (the shared epilogue, written out on this path)
                    charge(ctx, 11);
                    ld(fp, sp, 0x520);
                    ld(s7, sp, 0x510);
                    ld(s6, sp, 0x500);
                    ld(s5, sp, 0x4F0);
                    ld(s4, sp, 0x4E0);
                    ld(s3, sp, 0x4D0);
                    ld(s2, sp, 0x4C0);
                    ld(s1, sp, 0x4B0);
                    ld(s0, sp, 0x4A0);
                    sp = addiu(sp, 0x540);
                    return;
                }
            L_00517e88:
                charge(ctx, 91);
                v0 = addiu(sp, 0x480);
                a0 = s4;
                sw(v0, sp, 0x494);
                a1 = v0;
                jal(ctx, 0x517E94u, gen::fn__sceMcCoreReadClock_0051b5f0);
                s3 = 10;
                s0 = addiu(sp, 0x200);
                a1 = 0;
                a0 = s0;
                a2 = 512;
                jal(ctx, 0x517EACu, gen::fn_memset_00521408);
                lbu(v1, sp, 0x487);
                t6 = si(-1);
                lbu(t1, sp, 0x486);
                t7 = 2;
                lbu(a3, sp, 0x485);
                v0 = srl(v1, 4);
                lbu(a2, sp, 0x483);
                t5 = srl(t1, 4);
                lbu(a1, sp, 0x482);
                t2 = srl(a3, 4);
                lbu(a0, sp, 0x481);
                t3 = srl(a2, 4);
                t4 = srl(a1, 4);
                mult(v0, v0, s3);
                t0 = srl(a0, 4);
                mult(t5, t5, s3);
                mult1(t2, t2, s3);
                v1 = v1 & 0xF;
                mult(t3, t3, s3);
                a3 = a3 & 0xF;
                mult1(t4, t4, s3);
                v0 = addu(v0, v1);
                mult(t0, t0, s3);
                a2 = a2 & 0xF;
                a1 = a1 & 0xF;
                a0 = a0 & 0xF;
                t1 = t1 & 0xF;
                t2 = addu(t2, a3);
                t3 = addu(t3, a2);
                t4 = addu(t4, a1);
                t0 = addu(t0, a0);
                t5 = addu(t5, t1);
                if (s6 != 0) t6 = fp;
                if (s6 == 0) t7 = 0;
                v0 = addiu(v0, 2000);
                sh(s5, sp, 0x200);
                sw(t6, sp, 0x210);
                a0 = s2;
                sw(t7, sp, 0x204);
                a1 = 47;
                sh(v0, sp, 0x20E);
                sb(t5, sp, 0x20D);
                sb(t2, sp, 0x20C);
                sb(t3, sp, 0x20B);
                sb(t4, sp, 0x20A);
                sb(t0, sp, 0x209);
                sh(zero, sp, 0x202);
                sb(zero, sp, 0x208);
                sw(zero, sp, 0x214);
                ldl(v1, sp, 0x20F);
                ldr(v1, sp, 0x208);
                sdl(v1, sp, 0x21F);
                sdr(v1, sp, 0x218);
                link(ctx, 0x517F88u);  // $ra first: the delay slot below depends on it
                sw(zero, sp, 0x220);
                call(ctx, gen::fn_strrchr_005249e8);
                ldl(t1, v0, 8);
                ldr(t1, v0, 1);
                ldl(v1, v0, 16);
                ldr(v1, v0, 9);
                ldl(a0, v0, 24);
                ldr(a0, v0, 17);
                ldl(a1, v0, 32);
                ldr(a1, v0, 25);
                sdl(t1, sp, 0x247);
                sdr(t1, sp, 0x240);
                sdl(v1, sp, 0x24F);
                sdr(v1, sp, 0x248);
                sdl(a0, sp, 0x257);
                sdr(a0, sp, 0x250);
                sdl(a1, sp, 0x25F);
                sdr(a1, sp, 0x258);
                t0 = s1;
                a1 = s0;
                a0 = s4;
                lw(a2, sp, 0x10);
                link(ctx, 0x517FE0u);  // $ra first: the delay slot below depends on it
                lw(a3, sp, 0x4);
                call(ctx, gen::fn__CreateEntry_005175e8);
                s5 = v0;
                lw(v0, sp, 0x490);
                if (i64(s5) >= 0) {
                    // 0x00517ff4
                    charge(ctx, 2);
                    s1 = 0x980000;
                    if (s7 != 0) {
                        // 0x00517ffc
                        charge(ctx, 126);
                        a1 = 0;
                        s0 = addiu(s1, -14144);
                        a2 = 512;
                        a0 = s0;
                        s2 = 0x8427;
                        jal(ctx, 0x51800Cu, gen::fn_memset_00521408);
                        lbu(v1, sp, 0x487);
                        t7 = 0x7C0000;
                        lbu(t6, sp, 0x486);
                        a1 = 0;
                        lbu(t5, sp, 0x485);
                        v0 = srl(v1, 4);
                        lbu(t4, sp, 0x483);
                        t3 = srl(t6, 4);
                        lbu(t2, sp, 0x482);
                        a3 = srl(t5, 4);
                        lbu(a2, sp, 0x481);
                        t0 = srl(t4, 4);
                        t1 = srl(t2, 4);
                        mult(v0, v0, s3);
                        a0 = srl(a2, 4);
                        mult(t3, t3, s3);
                        mult1(a3, a3, s3);
                        v1 = v1 & 0xF;
                        mult(t0, t0, s3);
                        a2 = a2 & 0xF;
                        mult1(t1, t1, s3);
                        v0 = addu(v0, v1);
                        mult(a0, a0, s3);
                        t6 = t6 & 0xF;
                        t5 = t5 & 0xF;
                        t4 = t4 & 0xF;
                        t2 = t2 & 0xF;
                        sh(s2, s1, -14144);
                        a3 = addu(a3, t5);
                        t0 = addu(t0, t4);
                        a0 = addu(a0, a2);
                        t1 = addu(t1, t2);
                        v0 = addiu(v0, 2000);
                        t3 = addu(t3, t6);
                        sb(a0, s0, 9);
                        a2 = 512;
                        sh(v0, s0, 14);
                        sb(t3, s0, 13);
                        sb(a3, s0, 12);
                        sb(t0, s0, 11);
                        sb(t1, s0, 10);
                        sw(s5, s0, 20);
                        sw(zero, s0, 4);
                        sh(zero, s0, 2);
                        sw(zero, s0, 16);
                        ldl(a3, s0, 15);
                        ldr(a3, s0, 8);
                        sdl(a3, s0, 31);
                        sdr(a3, s0, 24);
                        t0 = addiu(t7, -6672);  // &0x7BE5F0
                        lb(v1, t0, 0);  // 0x7BE5F0
                        lb(a0, t0, 1);  // 0x7BE5F1
                        sb(v1, s0, 64);
                        sb(a0, s0, 65);
                        s0 = addiu(s0, 512);
                        a0 = s0;
                        jal(ctx, 0x5180F0u, gen::fn_memset_00521408);
                        lbu(v1, sp, 0x487);
                        t7 = 0x7C0000;
                        lbu(t6, sp, 0x486);
                        a1 = addiu(s1, -14144);
                        lbu(t5, sp, 0x485);
                        v0 = srl(v1, 4);
                        lbu(t4, sp, 0x483);
                        t0 = srl(t6, 4);
                        lbu(a3, sp, 0x482);
                        t1 = srl(t5, 4);
                        lbu(a0, sp, 0x481);
                        t2 = srl(t4, 4);
                        t3 = srl(a3, 4);
                        mult(v0, v0, s3);
                        a2 = srl(a0, 4);
                        mult(t0, t0, s3);
                        mult1(t1, t1, s3);
                        v1 = v1 & 0xF;
                        mult(a2, a2, s3);
                        a3 = a3 & 0xF;
                        mult1(t2, t2, s3);
                        v0 = addu(v0, v1);
                        mult(t3, t3, s3);
                        a0 = a0 & 0xF;
                        t6 = t6 & 0xF;
                        t5 = t5 & 0xF;
                        t4 = t4 & 0xF;
                        a2 = addu(a2, a0);
                        t1 = addu(t1, t5);
                        v0 = addiu(v0, 2000);
                        t0 = addu(t0, t6);
                        t3 = addu(t3, a3);
                        t2 = addu(t2, t4);
                        sh(s2, s0, 0);
                        sh(v0, s0, 14);
                        a0 = s4;
                        sb(t0, s0, 13);
                        sb(t1, s0, 12);
                        sb(t2, s0, 11);
                        sb(t3, s0, 10);
                        sb(a2, s0, 9);
                        sw(zero, s0, 4);
                        sh(zero, s0, 2);
                        sb(zero, s0, 8);
                        sw(zero, s0, 16);
                        sw(zero, s0, 20);
                        ldl(t1, s0, 15);
                        ldr(t1, s0, 8);
                        sdl(t1, s0, 31);
                        sdr(t1, s0, 24);
                        sw(zero, s0, 32);
                        lw(a2, sp, 0x210);
                        v1 = addiu(t7, -6664);  // ".."
                        lb(t0, v1, 0);  // 0x7BE5F8
                        lb(t1, v1, 1);  // 0x7BE5F9
                        lb(v0, v1, 2);  // 0x7BE5FA
                        sb(t0, s0, 64);
                        sb(t1, s0, 65);
                        sb(v0, s0, 66);
                        a3 = 1;
                        jal(ctx, 0x5181E4u, gen::fn__sceMcpWriteUserClust_0051aa90);
                        if (v0 != 0) {
                            goto L_005181f4;
                        }
                    L_0051822c:
                        charge(ctx, 2);
                        v0 = lui(0x8101);
                        v0 = v0 | 0x6F;
                        goto L_00518234;
                    }
                L_005181f4:
                    charge(ctx, 6);
                    lw(a1, sp, 0x10);
                    a0 = s4;
                    link(ctx, 0x5181FCu);  // $ra first: the delay slot below depends on it
                    lw(a2, sp, 0x494);
                    call(ctx, gen::fn__ParentDirUpdate_00517ab8);
                    sw(v0, sp, 0x490);
                    if (v0 == 0) {
                        // 0x0051820c
                        charge(ctx, 4);
                        a0 = s4;
                        jal(ctx, 0x51820Cu, gen::fn__sceMcFatFlushFatCache_00515588);
                        if (v0 == 0) {
                            goto L_0051822c;
                        }
                        // 0x0051821c
                        charge(ctx, 4);
                        a0 = s4;
                        jal(ctx, 0x51821Cu, gen::fn__sceMcpFlushCache_0051a498);
                        if (v0 == 0) {
                            goto L_0051822c;
                        }
                        lw(v0, sp, 0x490);
                    }
                }
                goto L_00518234;
            }
            // 0x00517e3c
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x1C;
        }
        // 0x00518238 (the shared epilogue, written out on this path)
        charge(ctx, 11);
        ld(fp, sp, 0x520);
        ld(s7, sp, 0x510);
        ld(s6, sp, 0x500);
        ld(s5, sp, 0x4F0);
        ld(s4, sp, 0x4E0);
        ld(s3, sp, 0x4D0);
        ld(s2, sp, 0x4C0);
        ld(s1, sp, 0x4B0);
        ld(s0, sp, 0x4A0);
        sp = addiu(sp, 0x540);
        return;
    }
L_00518234:
    charge(ctx, 1);
    ld(ra, sp, 0x530);
    // 0x00518238 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(fp, sp, 0x520);
    ld(s7, sp, 0x510);
    ld(s6, sp, 0x500);
    ld(s5, sp, 0x4F0);
    ld(s4, sp, 0x4E0);
    ld(s3, sp, 0x4D0);
    ld(s2, sp, 0x4C0);
    ld(s1, sp, 0x4B0);
    ld(s0, sp, 0x4A0);
    sp = addiu(sp, 0x540);
}

// 0x00518268 _sceMcFatReadFile -- 520 bytes; frame 0x330: s5 sp+0x2E0, s4 sp+0x2D0, s3 sp+0x2C0, s2 sp+0x2B0, s0 sp+0x290, ra sp+0x320, fp sp+0x310, s7 sp+0x300, s6 sp+0x2F0, s1 sp+0x2A0
// Read from a file at an offset: walks the chain cluster by cluster through the entry buffer; returns the bytes read.
void _sceMcFatReadFile(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00518268
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x330);
    sd(s5, sp, 0x2E0);
    s5 = a0;
    sd(s4, sp, 0x2D0);
    sd(s3, sp, 0x2C0);
    s4 = a2;
    sd(s2, sp, 0x2B0);
    s3 = a1;
    sd(s0, sp, 0x290);
    s2 = t0;
    s0 = a3;
    sd(ra, sp, 0x320);
    sd(fp, sp, 0x310);
    sd(s7, sp, 0x300);
    sd(s6, sp, 0x2F0);
    link(ctx, 0x5182A4u);  // $ra first: the delay slot below depends on it
    sd(s1, sp, 0x2A0);
    call(ctx, gen::fn__ConfInsert_00516b48);
    ld(ra, sp, 0x320);
    if (v0 == 0) {
        // 0x005182b4
        charge(ctx, 7);
        s1 = addiu(sp, 0x200);
        a1 = s3;
        a0 = s5;
        a2 = s1;
        jal(ctx, 0x5182C0u, gen::fn__CheckFileDescript_00516be8);
        ld(ra, sp, 0x320);
        if (v0 == 0) {
            // 0x005182d0
            charge(ctx, 10);
            a1 = s1;
            a0 = s5;
            a2 = sp;
            a3 = 0;
            t0 = 0;
            jal(ctx, 0x5182E0u, gen::fn__SearchFile_00516ec0);
            v1 = lui(0x8101);
            v1 = v1 | 0x11;
            ld(ra, sp, 0x320);
            if (v0 == v1) {
                // 0x005182f8
                charge(ctx, 4);
                lhu(v1, sp, 0x0);
                v0 = v1 & 0x1;
                if (v0 != 0) {
                    // 0x00518308
                    charge(ctx, 3);
                    v0 = v1 & 0x2000;
                    if (v0 != 0) {
                        goto L_00518314;
                    }
                    v0 = v1 & 0x20;
                    // 0x00518320
                    charge(ctx, 2);
                    lw(a0, sp, 0x4);
                    if (v0 == 0) {
                        // 0x00518334
                        charge(ctx, 3);
                        v0 = slt(a0, s0);
                        v1 = subu(a0, s0);
                        if (v0 == 0) {
                            // 0x00518380
                            charge(ctx, 7);
                            if (s2 == 0) s2 = v1;
                            v0 = addu(s2, s0);
                            v0 = slt(a0, v0);
                            if (v0 != 0) s2 = v1;
                            fp = s2;
                            lw(s1, sp, 0x10);
                            if (fp != 0) {
                                // 0x0051839c
                                charge(ctx, 5);
                                s7 = lui(0xFFFF);
                                s6 = 0x7FFF0000;
                                s7 = s7 | 0xFFFF;
                                s6 = s6 | 0xFFFF;
                                for (;;) {
                                    // 0x005183b0
                                    charge(ctx, 3);
                                    v0 = slti(s0, 1024);
                                    cc = v0 == 0;  // the condition, before the delay slot changes it
                                    v0 = 0x980000;
                                    if (!cc) {
                                        // 0x005183bc
                                        charge(ctx, 8);
                                        a0 = s5;
                                        s3 = addiu(v0, -14144);
                                        a2 = s1;
                                        a1 = s3;
                                        a3 = 1;
                                        jal(ctx, 0x5183CCu, gen::fn__sceMcpReadUserClust_0051a9e0);
                                        sw(v0, sp, 0x280);
                                        if (v0 == 0) {
                                            backedge(ctx);
                                            goto L_0051834c;
                                        }
                                        // 0x005183dc
                                        charge(ctx, 5);
                                        v0 = 1024;
                                        a2 = subu(v0, s0);
                                        v0 = slt(a2, s2);
                                        a1 = addu(s0, s3);
                                        if (v0 == 0) {
                                            backedge(ctx);
                                            goto L_00518358;
                                        }
                                        // 0x005183f0
                                        charge(ctx, 7);
                                        a0 = s4;
                                        jal(ctx, 0x5183F0u, gen::fn_memcpy_00521250);
                                        v1 = addiu(s4, 1024);
                                        v0 = addiu(s2, -1024);
                                        s2 = addu(v0, s0);
                                        s4 = subu(v1, s0);
                                        s0 = 0;
                                        goto L_0051840c;
                                    }
                                L_0051840c:
                                    charge(ctx, 7);
                                    a1 = s1;
                                    a0 = s5;
                                    a2 = addiu(sp, 0x280);
                                    jal(ctx, 0x518414u, gen::fn__sceMcFatGetNextClust_00515730);
                                    lw(v1, sp, 0x280);
                                    s1 = v0;
                                    if (v1 != 0) {
                                        backedge(ctx);
                                        goto L_0051836c;
                                    }
                                    // 0x00518428
                                    charge(ctx, 2);
                                    cc = s1 == s7;  // the condition, before the delay slot changes it
                                    s1 = s1 & s6;
                                    if (cc) {
                                        backedge(ctx);
                                        goto L_00518374;
                                    }
                                    // 0x00518430
                                    charge(ctx, 3);
                                    v0 = addiu(s0, -1024);
                                    if (s0 != 0) s0 = v0;
                                    if (s2 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                            // 0x0051843c
                            charge(ctx, 1);
                            v0 = fp;
                        } else {
                            // 0x00518340
                            charge(ctx, 3);
                            v0 = lui(0x8101);
                            v0 = v0 | 0x16;
                        }
                    } else {
                        // 0x00518328
                        charge(ctx, 3);
                        v0 = lui(0x8101);
                        v0 = v0 | 0x2;
                    }
                    goto L_00518440;
                }
            L_00518314:
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0xD;
            L_00518440:
                charge(ctx, 1);
                ld(ra, sp, 0x320);
            }
        }
    }
    // 0x00518444 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(fp, sp, 0x310);
    ld(s7, sp, 0x300);
    ld(s6, sp, 0x2F0);
    ld(s5, sp, 0x2E0);
    ld(s4, sp, 0x2D0);
    ld(s3, sp, 0x2C0);
    ld(s2, sp, 0x2B0);
    ld(s1, sp, 0x2A0);
    ld(s0, sp, 0x290);
    sp = addiu(sp, 0x330);
    return;
L_0051834c:
    charge(ctx, 3);
    v0 = lui(0x8101);
    v0 = v0 | 0x6F;
    goto L_00518440;
L_00518358:
    charge(ctx, 5);
    a0 = s4;
    a2 = s2;
    jal(ctx, 0x51835Cu, gen::fn_memcpy_00521250);
    v0 = fp;
    goto L_00518440;
L_0051836c:
    charge(ctx, 2);
    v0 = v1;
    goto L_00518440;
L_00518374:
    charge(ctx, 3);
    v0 = lui(0x8101);
    v0 = v0 | 0x9002;
    goto L_00518440;
}

// 0x00518470 _sceMcFatReadFastFile -- 848 bytes; frame 0x320: s6 sp+0x2F0, s5 sp+0x2E0, s3 sp+0x2C0, s2 sp+0x2B0, s0 sp+0x290, ra sp+0x310, s7 sp+0x300, s4 sp+0x2D0, s1 sp+0x2A0
// Read from a file with whole clusters straight into the caller's buffer (_sceMcpReadUserClustFast) where the offset
// allows; returns the bytes read.
void _sceMcFatReadFastFile(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00518470
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x320);
    sd(s6, sp, 0x2F0);
    sd(s5, sp, 0x2E0);
    s6 = a0;
    sd(s3, sp, 0x2C0);
    s5 = a2;
    sd(s2, sp, 0x2B0);
    s3 = t0;
    sd(s0, sp, 0x290);
    s2 = a1;
    sd(ra, sp, 0x310);
    s0 = a3;
    sd(s7, sp, 0x300);
    sd(s4, sp, 0x2D0);
    link(ctx, 0x5184A8u);  // $ra first: the delay slot below depends on it
    sd(s1, sp, 0x2A0);
    call(ctx, gen::fn__ConfInsert_00516b48);
    v1 = v0;
    sw(v0, sp, 0x280);
    if (v1 == 0) {
        // 0x005184bc
        charge(ctx, 8);
        s1 = addiu(sp, 0x200);
        a1 = s2;
        a0 = s6;
        a2 = s1;
        jal(ctx, 0x5184C8u, gen::fn__CheckFileDescript_00516be8);
        v1 = v0;
        sw(v0, sp, 0x280);
        if (v1 == 0) {
            // 0x005184dc
            charge(ctx, 11);
            a1 = s1;
            a0 = s6;
            a2 = sp;
            a3 = 0;
            t0 = 0;
            jal(ctx, 0x5184ECu, gen::fn__SearchFile_00516ec0);
            v1 = lui(0x8101);
            a0 = v0;
            v1 = v1 | 0x11;
            sw(v0, sp, 0x280);
            if (a0 == v1) {
                // 0x00518508
                charge(ctx, 4);
                lhu(v1, sp, 0x0);
                v0 = v1 & 0x1;
                if (v0 != 0) {
                    // 0x00518518
                    charge(ctx, 3);
                    v0 = v1 & 0x2000;
                    if (v0 != 0) {
                        goto L_00518524;
                    }
                    v0 = v1 & 0x20;
                    // 0x00518530
                    charge(ctx, 2);
                    lw(a1, sp, 0x4);
                    if (v0 == 0) {
                        // 0x00518544
                        charge(ctx, 3);
                        v0 = slt(a1, s0);
                        if (v0 == 0) {
                            v0 = subu(a1, s0);
                            // 0x0051855c
                            charge(ctx, 9);
                            s4 = s5;
                            if (s3 == 0) s3 = v0;
                            lw(s1, sp, 0x10);
                            v1 = addu(s3, s0);
                            a0 = slti(s0, 1024);
                            v1 = slt(a1, v1);
                            if (v1 != 0) s3 = v0;
                            s7 = s3;
                            if (a0 == 0) {
                                // 0x00518580
                                charge(ctx, 2);
                                s2 = addiu(sp, 0x280);
                                a1 = s1;
                                for (;;) {
                                    // 0x00518588
                                    charge(ctx, 8);
                                    a0 = s6;
                                    a2 = s2;
                                    jal(ctx, 0x51858Cu, gen::fn__sceMcFatGetNextClustSelf_00515778);
                                    v1 = lui(0x8101);
                                    lw(a0, sp, 0x280);
                                    v1 = v1 | 0x59;
                                    s1 = v0;
                                    if (a0 == v1) {
                                        goto L_00518764;
                                    }
                                    // 0x005185a8
                                    charge(ctx, 2);
                                    s0 = addiu(s0, -1024);
                                    if (a0 != 0) {
                                        goto L_00518650;
                                    }
                                    // 0x005185b0
                                    charge(ctx, 3);
                                    v0 = slti(s0, 1024);
                                    a1 = s1;
                                    if (v0 != 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                            // 0x005185bc
                            charge(ctx, 2);
                            v0 = 0x980000;
                            if (i64(s0) <= 0) {
                                // 0x00518658
                                charge(ctx, 1);
                                s2 = 0;
                            L_0051865c:
                                charge(ctx, 3);
                                v0 = slti(s3, 1024);
                                s0 = 0;
                                if (v0 == 0) {
                                    // 0x00518668
                                    charge(ctx, 2);
                                    s5 = lui(0x8101);
                                    s5 = s5 | 0x59;
                                    for (;;) {
                                        // 0x00518670
                                        charge(ctx, 2);
                                        a1 = s1;
                                        if (s2 == 0) {
                                            // 0x00518678
                                            charge(ctx, 3);
                                            s2 = s1;
                                            s0 = 1;
                                            goto L_005186d8;
                                        }
                                        // 0x00518684
                                        charge(ctx, 6);
                                        a0 = s6;
                                        a2 = addiu(sp, 0x280);
                                        jal(ctx, 0x518688u, gen::fn__sceMcFatGetNextClustSelf_00515778);
                                        lw(v1, sp, 0x280);
                                        s1 = v0;
                                        if (v1 == s5) {
                                            goto L_00518764;
                                        }
                                        // 0x0051869c
                                        charge(ctx, 2);
                                        v0 = addu(s2, s0);
                                        if (v1 != 0) {
                                            goto L_00518770;
                                        }
                                        // 0x005186a4
                                        charge(ctx, 2);
                                        a2 = s2;
                                        if (v0 == s1) {
                                            // 0x005186d4
                                            charge(ctx, 1);
                                            s0 = addiu(s0, 1);
                                        L_005186d8:
                                            charge(ctx, 4);
                                            s3 = addiu(s3, -1024);
                                            v0 = slti(s3, 1024);
                                            if (v0 != 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                            continue;
                                        }
                                        // 0x005186ac
                                        charge(ctx, 6);
                                        a0 = s6;
                                        a1 = s4;
                                        a3 = s0;
                                        jal(ctx, 0x5186B4u, gen::fn__sceMcpReadUserClustFast_0051aa00);
                                        s2 = s1;
                                        if (v0 == 0) {
                                            goto L_00518778;
                                        }
                                        // 0x005186c4
                                        charge(ctx, 4);
                                        v0 = sll(s0, 10);
                                        s4 = addu(s4, v0);
                                        s0 = 1;
                                        goto L_005186d8;
                                    }
                                }
                                // 0x005186e8
                                charge(ctx, 2);
                                a1 = s4;
                                if (i64(s0) > 0) {
                                    // 0x005186f0
                                    charge(ctx, 7);
                                    a2 = s2;
                                    a0 = s6;
                                    a3 = s0;
                                    jal(ctx, 0x5186F8u, gen::fn__sceMcpReadUserClustFast_0051aa00);
                                    v1 = sll(s0, 10);
                                    s4 = addu(s4, v1);
                                    if (v0 == 0) {
                                    L_00518778:
                                        charge(ctx, 3);
                                        v0 = lui(0x8101);
                                        v0 = v0 | 0x6F;
                                    } else {
                                        // 0x0051870c
                                        charge(ctx, 2);
                                        a1 = s1;
                                        if (i64(s3) <= 0) {
                                        L_00518790:
                                            charge(ctx, 1);
                                            v0 = s7;
                                        } else {
                                            // 0x00518714
                                            charge(ctx, 8);
                                            a0 = s6;
                                            a2 = addiu(sp, 0x280);
                                            jal(ctx, 0x518718u, gen::fn__sceMcFatGetNextClustSelf_00515778);
                                            v1 = lui(0x8101);
                                            lw(a0, sp, 0x280);
                                            v1 = v1 | 0x59;
                                            s1 = v0;
                                            if (a0 != v1) {
                                                goto L_00518734;
                                            }
                                        L_00518764:
                                            charge(ctx, 3);
                                            v0 = lui(0x8101);
                                            v0 = v0 | 0x9002;
                                        }
                                    }
                                    // 0x00518794 (the shared epilogue, written out on this path)
                                    charge(ctx, 11);
                                    ld(ra, sp, 0x310);
                                    ld(s7, sp, 0x300);
                                    ld(s6, sp, 0x2F0);
                                    ld(s5, sp, 0x2E0);
                                    ld(s4, sp, 0x2D0);
                                    ld(s3, sp, 0x2C0);
                                    ld(s2, sp, 0x2B0);
                                    ld(s1, sp, 0x2A0);
                                    ld(s0, sp, 0x290);
                                    sp = addiu(sp, 0x320);
                                    return;
                                }
                            L_00518734:
                                charge(ctx, 2);
                                v0 = 0x980000;
                                if (i64(s3) <= 0) {
                                    goto L_00518790;
                                }
                                // 0x0051873c
                                charge(ctx, 8);
                                a0 = s6;
                                s0 = addiu(v0, -14144);
                                a2 = s1;
                                a1 = s0;
                                a3 = 1;
                                jal(ctx, 0x51874Cu, gen::fn__sceMcpReadUserClust_0051a9e0);
                                a0 = s4;
                                if (v0 == 0) {
                                    // 0x0051875c
                                    charge(ctx, 2);
                                    goto L_00518778;
                                }
                                // 0x00518784
                                charge(ctx, 3);
                                a1 = s0;
                                a2 = s3;
                                jal(ctx, 0x518788u, gen::fn_memcpy_00521250);
                                goto L_00518790;
                            }
                            // 0x005185c4
                            charge(ctx, 8);
                            a0 = s6;
                            s2 = addiu(v0, -14144);
                            a2 = s1;
                            a1 = s2;
                            a3 = 1;
                            jal(ctx, 0x5185D4u, gen::fn__sceMcpReadUserClust_0051a9e0);
                            if (v0 == 0) {
                                goto L_00518778;
                            }
                            // 0x005185e4
                            charge(ctx, 5);
                            v0 = 1024;
                            a2 = subu(v0, s0);
                            v1 = slt(a2, s3);
                            a1 = addu(s0, s2);
                            if (v1 != 0) {
                                // 0x0051860c
                                charge(ctx, 15);
                                a0 = s5;
                                jal(ctx, 0x51860Cu, gen::fn_memcpy_00521250);
                                v1 = addiu(s5, 1024);
                                v0 = addiu(s3, -1024);
                                a1 = s1;
                                s3 = addu(v0, s0);
                                s4 = subu(v1, s0);
                                a0 = s6;
                                a2 = addiu(sp, 0x280);
                                jal(ctx, 0x51862Cu, gen::fn__sceMcFatGetNextClustSelf_00515778);
                                v1 = lui(0x8101);
                                lw(a0, sp, 0x280);
                                v1 = v1 | 0x59;
                                s1 = v0;
                                if (a0 == v1) {
                                    goto L_00518764;
                                }
                                // 0x00518648
                                charge(ctx, 2);
                                s2 = 0;
                                if (a0 == 0) {
                                    goto L_0051865c;
                                }
                            L_00518650:
                                charge(ctx, 2);
                                v0 = a0;
                            } else {
                                // 0x005185f8
                                charge(ctx, 5);
                                a0 = s5;
                                a2 = s3;
                                jal(ctx, 0x5185FCu, gen::fn_memcpy_00521250);
                                v0 = s7;
                            }
                        } else {
                            // 0x00518550
                            charge(ctx, 3);
                            v0 = lui(0x8101);
                            v0 = v0 | 0x16;
                        }
                    } else {
                        // 0x00518538
                        charge(ctx, 3);
                        v0 = lui(0x8101);
                        v0 = v0 | 0x2;
                    }
                    // 0x00518794 (the shared epilogue, written out on this path)
                    charge(ctx, 11);
                    ld(ra, sp, 0x310);
                    ld(s7, sp, 0x300);
                    ld(s6, sp, 0x2F0);
                    ld(s5, sp, 0x2E0);
                    ld(s4, sp, 0x2D0);
                    ld(s3, sp, 0x2C0);
                    ld(s2, sp, 0x2B0);
                    ld(s1, sp, 0x2A0);
                    ld(s0, sp, 0x290);
                    sp = addiu(sp, 0x320);
                    return;
                }
            L_00518524:
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0xD;
            }
        }
    }
    // 0x00518794 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x310);
    ld(s7, sp, 0x300);
    ld(s6, sp, 0x2F0);
    ld(s5, sp, 0x2E0);
    ld(s4, sp, 0x2D0);
    ld(s3, sp, 0x2C0);
    ld(s2, sp, 0x2B0);
    ld(s1, sp, 0x2A0);
    ld(s0, sp, 0x290);
    sp = addiu(sp, 0x320);
    return;
L_00518770:
    charge(ctx, 2);
    v0 = v1;
    // 0x00518794 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x310);
    ld(s7, sp, 0x300);
    ld(s6, sp, 0x2F0);
    ld(s5, sp, 0x2E0);
    ld(s4, sp, 0x2D0);
    ld(s3, sp, 0x2C0);
    ld(s2, sp, 0x2B0);
    ld(s1, sp, 0x2A0);
    ld(s0, sp, 0x290);
    sp = addiu(sp, 0x320);
}

// 0x005187C0 _sceMcFatWriteFile -- 1500 bytes; frame 0x350: s3 sp+0x2E0, s7 sp+0x320, s4 sp+0x2F0, s2 sp+0x2D0, s1 sp+0x2C0, ra sp+0x340, fp sp+0x330, s6 sp+0x310, s5 sp+0x300, s0 sp+0x2B0
// Write to a file at an offset: extends the chain as needed, writes through the cluster cache, updates the entry and
// the parent.
void _sceMcFatWriteFile(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005187c0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x350);
    sd(s3, sp, 0x2E0);
    sd(s7, sp, 0x320);
    s3 = a0;
    sd(s4, sp, 0x2F0);
    s7 = t0;
    sd(s2, sp, 0x2D0);
    s4 = a2;
    sd(s1, sp, 0x2C0);
    s2 = a3;
    sd(ra, sp, 0x340);
    s1 = a1;
    sd(fp, sp, 0x330);
    sd(s6, sp, 0x310);
    sd(s5, sp, 0x300);
    link(ctx, 0x5187FCu);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x2B0);
    call(ctx, gen::fn__ConfInsert_00516b48);
    v1 = v0;
    sw(v0, sp, 0x298);
    if (v1 == 0) {
        // 0x00518810
        charge(ctx, 8);
        s0 = addiu(sp, 0x200);
        a1 = s1;
        a0 = s3;
        a2 = s0;
        jal(ctx, 0x51881Cu, gen::fn__CheckFileDescript_00516be8);
        v1 = v0;
        sw(v0, sp, 0x298);
        if (v1 != 0) {
            goto L_00518d6c;
        }
        // 0x00518830
        charge(ctx, 11);
        a1 = s0;
        a0 = s3;
        a2 = sp;
        a3 = addiu(sp, 0x290);
        t0 = addiu(sp, 0x294);
        jal(ctx, 0x518840u, gen::fn__SearchFile_00516ec0);
        v1 = lui(0x8101);
        a0 = v0;
        v1 = v1 | 0x11;
        sw(v0, sp, 0x298);
        if (a0 != v1) {
            goto L_00518d6c;
        }
        // 0x0051885c
        charge(ctx, 3);
        lbu(v0, sp, 0x60);
        lhu(a0, sp, 0x0);
        if (v0 == 0) {
            // 0x00518868
            charge(ctx, 4);
            v0 = 0x8000;
            v1 = a0 & 0xF000;
            a1 = a0;
            if (v1 != v0) {
                // 0x00518878
                charge(ctx, 3);
                v0 = 0xA000;
                if (v1 != v0) {
                    goto L_0051889c;
                }
                goto L_00518884;
            }
        L_00518884:
            charge(ctx, 4);
            v1 = a1 & 0xF00;
            v0 = 1024;
            if (v1 == v0) {
                v0 = a1 & 0x2;
            } else {
                // 0x00518894
                charge(ctx, 2);
                if (v1 != 0) {
                    goto L_0051889c;
                }
                v0 = a1 & 0x2;
                goto L_005188a8;
            }
        L_005188a8:
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x005188b0
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0xD;
                goto L_00518d6c;
            }
            v0 = a0 & 0x20;
            // 0x005188bc
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x005188c4
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x2;
                goto L_00518d6c;
            }
            lw(v0, sp, 0x4);
            // 0x005188d0
            charge(ctx, 3);
            v0 = slt(v0, s2);
            if (v0 != 0) {
                // 0x005188dc
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x16;
                goto L_00518d6c;
            }
            v0 = addu(s2, s7);
            // 0x005188e8
            charge(ctx, 12);
            v1 = si(-1);
            a0 = addiu(v0, 1023);
            lw(a1, sp, 0x10);
            v1 = slt(v1, a0);
            v0 = addiu(v0, 2046);
            if (v1 != 0) v0 = a0;
            a0 = s3;
            s1 = sra(v0, 10);
            jal(ctx, 0x518904u, gen::fn__fat_chain_trace_00515c98);
            s0 = v0;
            ld(ra, sp, 0x340);
            if (i64(s0) >= 0) {
                // 0x00518918
                charge(ctx, 3);
                v0 = slt(s0, s1);
                a0 = s3;
                if (v0 != 0) {
                    // 0x00518924
                    charge(ctx, 6);
                    a1 = addiu(sp, 0x298);
                    jal(ctx, 0x518924u, gen::fn__sceMcFatGetFreeClustSize_00515a40);
                    v1 = v0;
                    lw(v0, sp, 0x298);
                    ld(ra, sp, 0x340);
                    if (v0 == 0) {
                        // 0x0051893c
                        charge(ctx, 4);
                        v0 = subu(s1, s0);
                        v0 = slt(v1, v0);
                        if (v0 == 0) {
                            goto L_00518958;
                        }
                        // 0x0051894c
                        charge(ctx, 3);
                        v0 = lui(0x8101);
                        v0 = v0 | 0x1C;
                    }
                    // 0x00518d70 (the shared epilogue, written out on this path)
                    charge(ctx, 11);
                    ld(fp, sp, 0x330);
                    ld(s7, sp, 0x320);
                    ld(s6, sp, 0x310);
                    ld(s5, sp, 0x300);
                    ld(s4, sp, 0x2F0);
                    ld(s3, sp, 0x2E0);
                    ld(s2, sp, 0x2D0);
                    ld(s1, sp, 0x2C0);
                    ld(s0, sp, 0x2B0);
                    sp = addiu(sp, 0x350);
                    return;
                }
            L_00518958:
                charge(ctx, 5);
                v0 = lui(0xFFFF);
                lw(a1, sp, 0x10);
                v0 = v0 | 0xFFFF;
                cc = a1 != v0;  // the condition, before the delay slot changes it
                v0 = 0x980000;
                if (!cc) {
                    // 0x0051896c
                    charge(ctx, 7);
                    s0 = addiu(sp, 0x298);
                    a0 = s3;
                    a1 = s0;
                    jal(ctx, 0x518974u, gen::fn__sceMcFatGetFreeClust_00515910);
                    lw(v1, sp, 0x298);
                    s1 = v0;
                    if (v1 != 0) {
                    L_00518988:
                        charge(ctx, 2);
                        v0 = v1;
                        goto L_00518d6c;
                    }
                    // 0x00518990
                    charge(ctx, 8);
                    a3 = s0;
                    a0 = s3;
                    a1 = s1;
                    a2 = si(-1);
                    jal(ctx, 0x51899Cu, gen::fn__sceMcFatWriteFatData_005157e0);
                    lw(v0, sp, 0x298);
                    ld(ra, sp, 0x340);
                    if (v0 == 0) {
                        // 0x005189b0
                        charge(ctx, 7);
                        a0 = s3;
                        a1 = addiu(sp, 0x280);
                        jal(ctx, 0x5189B4u, gen::fn__sceMcCoreReadClock_0051b5f0);
                        lw(v1, sp, 0x4);
                        v1 = slt(v1, s5);
                        sw(s1, sp, 0x10);
                        if (v1 != 0) {
                            // 0x005189cc
                            charge(ctx, 1);
                            sw(s5, sp, 0x4);
                        }
                        // 0x005189d0
                        charge(ctx, 45);
                        lbu(a1, sp, 0x287);
                        v1 = 10;
                        lbu(a3, sp, 0x282);
                        a0 = s3;
                        lbu(a2, sp, 0x281);
                        v0 = srl(a1, 4);
                        lbu(t7, sp, 0x286);
                        t3 = srl(a3, 4);
                        lbu(t6, sp, 0x285);
                        t0 = srl(a2, 4);
                        lbu(t4, sp, 0x283);
                        t5 = srl(t7, 4);
                        t1 = srl(t6, 4);
                        mult(v0, v0, v1);
                        t2 = srl(t4, 4);
                        mult(t0, t0, v1);
                        mult(t3, t3, v1);
                        a1 = a1 & 0xF;
                        mult(t5, t5, v1);
                        a3 = a3 & 0xF;
                        mult1(t1, t1, v1);
                        a2 = a2 & 0xF;
                        mult1(t2, t2, v1);
                        v0 = addu(v0, a1);
                        t3 = addu(t3, a3);
                        t0 = addu(t0, a2);
                        t7 = t7 & 0xF;
                        t6 = t6 & 0xF;
                        t4 = t4 & 0xF;
                        t5 = addu(t5, t7);
                        t1 = addu(t1, t6);
                        t2 = addu(t2, t4);
                        v0 = addiu(v0, 2000);
                        lw(a2, sp, 0x290);
                        lw(a3, sp, 0x294);
                        a1 = sp;
                        sh(v0, sp, 0x1E);
                        sb(t5, sp, 0x1D);
                        sb(t1, sp, 0x1C);
                        sb(t2, sp, 0x1B);
                        sb(t3, sp, 0x1A);
                        link(ctx, 0x518A74u);  // $ra first: the delay slot below depends on it
                        sb(t0, sp, 0x19);
                        call(ctx, gen::fn__SetEntryByPos_00517310);
                        sw(v0, sp, 0x298);
                        if (v0 != 0) {
                            goto L_00518d6c;
                        }
                        // 0x00518a84
                        charge(ctx, 4);
                        a0 = s3;
                        jal(ctx, 0x518A84u, gen::fn__sceMcFatFlushFatCache_00515588);
                        sw(v0, sp, 0x29C);
                        if (v0 == 0) {
                        L_00518d40:
                            charge(ctx, 3);
                            v0 = lui(0x8101);
                            v0 = v0 | 0x6F;
                            goto L_00518d6c;
                        }
                        // 0x00518a94
                        charge(ctx, 4);
                        a0 = s3;
                        jal(ctx, 0x518A94u, gen::fn__sceMcpFlushCache_0051a498);
                        sw(v0, sp, 0x29C);
                        if (v0 == 0) {
                            goto L_00518d40;
                        }
                        // 0x00518aa4
                        charge(ctx, 2);
                        lw(a1, sp, 0x10);
                        v0 = 0x980000;
                        goto L_00518aac;
                    }
                    // 0x00518d70 (the shared epilogue, written out on this path)
                    charge(ctx, 11);
                    ld(fp, sp, 0x330);
                    ld(s7, sp, 0x320);
                    ld(s6, sp, 0x310);
                    ld(s5, sp, 0x300);
                    ld(s4, sp, 0x2F0);
                    ld(s3, sp, 0x2E0);
                    ld(s2, sp, 0x2D0);
                    ld(s1, sp, 0x2C0);
                    ld(s0, sp, 0x2B0);
                    sp = addiu(sp, 0x350);
                    return;
                }
            L_00518aac:
                charge(ctx, 5);
                sw(s7, sp, 0x2A0);
                s1 = a1;
                fp = addiu(v0, -0x3740);
                s6 = s4;
                s5 = s2;
                for (;;) {
                    // 0x00518ac0
                    charge(ctx, 3);
                    v0 = slti(s2, 1024);
                    s4 = s1;
                    if (v0 != 0) {
                        // 0x00518acc
                        charge(ctx, 2);
                        v0 = 0x980000;
                        if (i64(s2) <= 0) {
                            // 0x00518ad4
                            charge(ctx, 4);
                            v0 = addu(s2, s7);
                            v0 = slti(v0, 1024);
                            cc = v0 == 0;  // the condition, before the delay slot changes it
                            lw(v0, sp, 0x4);
                            if (!cc) {
                                // 0x00518ae4
                                charge(ctx, 3);
                                v0 = slt(s5, v0);
                                cc = v0 == 0;  // the condition, before the delay slot changes it
                                v0 = 0x980000;
                                if (cc) {
                                    goto L_00518b0c;
                                }
                                goto L_00518af0;
                            }
                        L_00518b0c:
                            charge(ctx, 5);
                            v0 = 1024;
                            a2 = subu(v0, s2);
                            v1 = slt(a2, s7);
                            a0 = addu(s2, fp);
                            if (v1 == 0) {
                                goto L_00518b20_37;
                            }
                            // 0x00518b74
                            charge(ctx, 9);
                            a1 = s6;
                            jal(ctx, 0x518B74u, gen::fn_memcpy_00521250);
                            a0 = s3;
                            a1 = fp;
                            a2 = s1;
                            a3 = 1;
                            jal(ctx, 0x518B88u, gen::fn__sceMcpWriteUserClust_0051aa90);
                            sw(v0, sp, 0x29C);
                            if (v0 == 0) {
                                goto L_00518d40;
                            }
                            // 0x00518b98
                            charge(ctx, 8);
                            v0 = addiu(s5, 1024);
                            a0 = addiu(s6, 1024);
                            v1 = addiu(s7, -1024);
                            s5 = subu(v0, s2);
                            s7 = addu(v1, s2);
                            s6 = subu(a0, s2);
                            s2 = 0;
                            s4 = s1;
                            goto L_00518bb8;
                        }
                    L_00518af0:
                        charge(ctx, 7);
                        a0 = s3;
                        a1 = addiu(v0, -14144);
                        a2 = s1;
                        a3 = 1;
                        jal(ctx, 0x518AFCu, gen::fn__sceMcpReadUserClust_0051a9e0);
                        sw(v0, sp, 0x29C);
                        if (v0 == 0) {
                            goto L_00518d40;
                        }
                        goto L_00518b0c;
                    }
                L_00518bb8:
                    charge(ctx, 7);
                    a0 = s3;
                    a1 = s4;
                    a2 = addiu(sp, 0x29C);
                    jal(ctx, 0x518BC0u, gen::fn__sceMcFatGetNextClust_00515730);
                    lw(v1, sp, 0x29C);
                    s1 = v0;
                    if (v1 != 0) {
                        backedge(ctx);
                        goto L_00518988;
                    }
                    // 0x00518bd4
                    charge(ctx, 4);
                    v0 = lui(0xFFFF);
                    v0 = v0 | 0xFFFF;
                    cc = s1 != v0;  // the condition, before the delay slot changes it
                    v0 = 0x7FFF0000;
                    if (!cc) {
                        // 0x00518be4
                        charge(ctx, 7);
                        s0 = addiu(sp, 0x298);
                        a0 = s3;
                        a1 = s0;
                        jal(ctx, 0x518BECu, gen::fn__sceMcFatGetFreeClust_00515910);
                        lw(v1, sp, 0x298);
                        s1 = v0;
                        if (v1 != 0) {
                            backedge(ctx);
                            goto L_00518988;
                        }
                        // 0x00518c00
                        charge(ctx, 8);
                        a0 = s3;
                        a1 = s1;
                        a2 = si(-1);
                        a3 = s0;
                        jal(ctx, 0x518C0Cu, gen::fn__sceMcFatWriteFatData_005157e0);
                        lw(v0, sp, 0x298);
                        a1 = s4;
                        if (v0 != 0) {
                            goto L_00518d6c;
                        }
                        // 0x00518c20
                        charge(ctx, 8);
                        a2 = lui(0x8000);
                        a2 = s1 | a2;
                        a3 = s0;
                        a0 = s3;
                        jal(ctx, 0x518C2Cu, gen::fn__sceMcFatWriteFatData_005157e0);
                        lw(v0, sp, 0x298);
                        ld(ra, sp, 0x340);
                        if (v0 == 0) {
                            // 0x00518c40
                            charge(ctx, 1);
                            v0 = 0x7FFF0000;
                            goto L_00518c44;
                        }
                        break;
                    }
                L_00518c44:
                    charge(ctx, 5);
                    v1 = addiu(s2, -1024);
                    v0 = v0 | 0xFFFF;
                    if (s2 != 0) s2 = v1;
                    s1 = s1 & v0;
                    backedge(ctx);
                }
            }
            // 0x00518d70 (the shared epilogue, written out on this path)
            charge(ctx, 11);
            ld(fp, sp, 0x330);
            ld(s7, sp, 0x320);
            ld(s6, sp, 0x310);
            ld(s5, sp, 0x300);
            ld(s4, sp, 0x2F0);
            ld(s3, sp, 0x2E0);
            ld(s2, sp, 0x2D0);
            ld(s1, sp, 0x2C0);
            ld(s0, sp, 0x2B0);
            sp = addiu(sp, 0x350);
            return;
        }
    L_0051889c:
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x9002;
        goto L_00518d6c;
    }
L_00518d6c:
    charge(ctx, 1);
    ld(ra, sp, 0x340);
    // 0x00518d70 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(fp, sp, 0x330);
    ld(s7, sp, 0x320);
    ld(s6, sp, 0x310);
    ld(s5, sp, 0x300);
    ld(s4, sp, 0x2F0);
    ld(s3, sp, 0x2E0);
    ld(s2, sp, 0x2D0);
    ld(s1, sp, 0x2C0);
    ld(s0, sp, 0x2B0);
    sp = addiu(sp, 0x350);
    return;
L_00518b20_37:
    charge(ctx, 10);
    a1 = s6;
    a2 = s7;
    jal(ctx, 0x518B24u, gen::fn_memcpy_00521250);
    a1 = fp;
    a2 = s1;
    a0 = s3;
    a3 = 1;
    jal(ctx, 0x518B38u, gen::fn__sceMcpWriteUserClust_0051aa90);
    sw(v0, sp, 0x29C);
    if (v0 == 0) {
        goto L_00518d40;
    }
    // 0x00518b48
    charge(ctx, 9);
    s1 = addiu(sp, 0x280);
    a0 = s3;
    a1 = s1;
    s5 = addu(s5, s7);
    jal(ctx, 0x518B54u, gen::fn__sceMcCoreReadClock_0051b5f0);
    lw(v1, sp, 0x4);
    v1 = slt(v1, s5);
    if (v1 != 0) {
        sw(s5, sp, 0x4);
        // 0x00518c58
        charge(ctx, 1);
        lbu(a1, sp, 0x287);
    } else {
        // 0x00518b6c
        charge(ctx, 2);
        lbu(a1, sp, 0x287);
    }
    // 0x00518c5c
    charge(ctx, 47);
    v1 = 10;
    lbu(a3, sp, 0x282);
    a0 = s3;
    lbu(a2, sp, 0x281);
    v0 = srl(a1, 4);
    lbu(s0, sp, 0x286);
    t6 = srl(a3, 4);
    lbu(t3, sp, 0x285);
    t1 = srl(a2, 4);
    lbu(t2, sp, 0x283);
    t7 = srl(s0, 4);
    t4 = srl(t3, 4);
    mult(v0, v0, v1);
    t5 = srl(t2, 4);
    mult(t1, t1, v1);
    mult(t6, t6, v1);
    a1 = a1 & 0xF;
    mult(t7, t7, v1);
    lhu(t0, sp, 0x0);
    mult1(t4, t4, v1);
    a3 = a3 & 0xF;
    mult1(t5, t5, v1);
    a2 = a2 & 0xF;
    v0 = addu(v0, a1);
    t6 = addu(t6, a3);
    t1 = addu(t1, a2);
    s0 = s0 & 0xF;
    t3 = t3 & 0xF;
    t2 = t2 & 0xF;
    t7 = addu(t7, s0);
    t4 = addu(t4, t3);
    t5 = addu(t5, t2);
    t0 = t0 | 0x80;
    v0 = addiu(v0, 2000);
    lw(a2, sp, 0x290);
    lw(a3, sp, 0x294);
    a1 = sp;
    sh(t0, sp, 0x0);
    sh(v0, sp, 0x1E);
    sb(t7, sp, 0x1D);
    sb(t4, sp, 0x1C);
    sb(t5, sp, 0x1B);
    sb(t6, sp, 0x1A);
    link(ctx, 0x518D08u);  // $ra first: the delay slot below depends on it
    sb(t1, sp, 0x19);
    call(ctx, gen::fn__SetEntryByPos_00517310);
    sw(v0, sp, 0x298);
    if (v0 == 0) {
        // 0x00518d18
        charge(ctx, 6);
        lw(a1, sp, 0x290);
        a2 = s1;
        a0 = s3;
        jal(ctx, 0x518D20u, gen::fn__ParentDirUpdate_00517ab8);
        sw(v0, sp, 0x298);
        if (v0 == 0) {
            // 0x00518d30
            charge(ctx, 4);
            a0 = s3;
            jal(ctx, 0x518D30u, gen::fn__sceMcFatFlushFatCache_00515588);
            sw(v0, sp, 0x29C);
            if (v0 == 0) {
                goto L_00518d40;
            }
            // 0x00518d4c
            charge(ctx, 8);
            a0 = s3;
            jal(ctx, 0x518D4Cu, gen::fn__sceMcpFlushCache_0051a498);
            v1 = lui(0x8101);
            lw(a0, sp, 0x2A0);
            v1 = v1 | 0x6F;
            sw(v0, sp, 0x29C);
            if (v0 == 0) a0 = v1;
            v0 = a0;
        }
    }
    goto L_00518d6c;
}

// 0x00518DA0 _sceMcFatGetNextClustAlloc -- 204 bytes; frame 0x50: s1 sp+0x10, s3 sp+0x30, s2 sp+0x20, s0 sp+0x0, ra sp+0x40
// The next cluster of a chain, allocating and linking a free one at the chain's end.
void _sceMcFatGetNextClustAlloc(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00518da0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s1, sp, 0x10);
    s1 = a1;
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    s3 = s1;
    sd(s0, sp, 0x0);
    s2 = a0;
    s0 = a2;
    sd(ra, sp, 0x40);
    a1 = s3;
    jal(ctx, 0x518DC8u, gen::fn__sceMcFatGetNextClustSelf_00515778);
    v1 = lui(0x8101);
    lw(a0, s0, 0);
    v1 = v1 | 0x59;
    s1 = v0;
    if (a0 != v1) {
        // 0x00518e48
        charge(ctx, 1);
        sw(zero, s0, 0);
    L_00518e4c:
        charge(ctx, 1);
        v0 = s1;
    } else {
        // 0x00518de4
        charge(ctx, 6);
        a0 = s2;
        a1 = s0;
        jal(ctx, 0x518DE8u, gen::fn__sceMcFatGetFreeClust_00515910);
        lw(v1, s0, 0);
        s1 = v0;
        if (v1 == 0) {
            // 0x00518dfc
            charge(ctx, 8);
            a0 = s2;
            a1 = s1;
            a2 = si(-1);
            a3 = s0;
            jal(ctx, 0x518E08u, gen::fn__sceMcFatWriteFatData_005157e0);
            lw(v1, s0, 0);
            v0 = si(-1);
            if (v1 == 0) {
                // 0x00518e1c
                charge(ctx, 9);
                a2 = lui(0x8000);
                a0 = s2;
                a1 = s3;
                a2 = s1 | a2;
                a3 = s0;
                jal(ctx, 0x518E2Cu, gen::fn__sceMcFatWriteFatData_005157e0);
                lw(v1, s0, 0);
                if (v1 != 0) {
                    goto L_00518e40;
                }
                sw(zero, s0, 0);
                goto L_00518e4c;
            }
            // 0x00518e50 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x40);
            ld(s3, sp, 0x30);
            ld(s2, sp, 0x20);
            ld(s1, sp, 0x10);
            ld(s0, sp, 0x0);
            sp = addiu(sp, 0x50);
            return;
        }
    L_00518e40:
        charge(ctx, 2);
        v0 = si(-1);
    }
    // 0x00518e50 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00518E70 _sceMcFatWriteFastFile -- 1672 bytes; frame 0x340: s3 sp+0x2D0, s7 sp+0x310, s6 sp+0x300, s2 sp+0x2C0, s1 sp+0x2B0, ra sp+0x330, fp sp+0x320, s5 sp+0x2F0, s4 sp+0x2E0, s0 sp+0x2A0
// Write to a file with whole clusters straight from the caller's buffer where possible.
void _sceMcFatWriteFastFile(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00518e70
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x340);
    sd(s3, sp, 0x2D0);
    sd(s7, sp, 0x310);
    s3 = a0;
    sd(s6, sp, 0x300);
    s7 = a2;
    sd(s2, sp, 0x2C0);
    s6 = t0;
    sd(s1, sp, 0x2B0);
    s2 = a3;
    sd(ra, sp, 0x330);
    s1 = a1;
    sd(fp, sp, 0x320);
    sd(s5, sp, 0x2F0);
    sd(s4, sp, 0x2E0);
    link(ctx, 0x518EACu);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x2A0);
    call(ctx, gen::fn__ConfInsert_00516b48);
    v1 = v0;
    sw(v0, sp, 0x298);
    if (v1 == 0) {
        // 0x00518ec0
        charge(ctx, 8);
        s0 = addiu(sp, 0x200);
        a1 = s1;
        a0 = s3;
        a2 = s0;
        jal(ctx, 0x518ECCu, gen::fn__CheckFileDescript_00516be8);
        v1 = v0;
        sw(v0, sp, 0x298);
        if (v1 != 0) {
            goto L_005194c8;
        }
        // 0x00518ee0
        charge(ctx, 11);
        a1 = s0;
        a0 = s3;
        a2 = sp;
        a3 = addiu(sp, 0x290);
        t0 = addiu(sp, 0x294);
        jal(ctx, 0x518EF0u, gen::fn__SearchFile_00516ec0);
        v1 = lui(0x8101);
        a0 = v0;
        v1 = v1 | 0x11;
        sw(v0, sp, 0x298);
        if (a0 != v1) {
            goto L_005194c8;
        }
        // 0x00518f0c
        charge(ctx, 3);
        lbu(v0, sp, 0x60);
        lhu(a0, sp, 0x0);
        if (v0 == 0) {
            // 0x00518f18
            charge(ctx, 4);
            v0 = 0x8000;
            v1 = a0 & 0xF000;
            a1 = a0;
            if (v1 != v0) {
                // 0x00518f28
                charge(ctx, 3);
                v0 = 0xA000;
                if (v1 != v0) {
                    goto L_005191ac;
                }
                goto L_00518f34;
            }
        L_00518f34:
            charge(ctx, 4);
            v1 = a1 & 0xF00;
            v0 = 1024;
            if (v1 == v0) {
                v0 = a1 & 0x2;
            } else {
                // 0x00518f44
                charge(ctx, 2);
                if (v1 != 0) {
                    goto L_005191ac;
                }
                // 0x00518f4c
                charge(ctx, 1);
                v0 = a1 & 0x2;
                goto L_00518f50;
            }
        L_00518f50:
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x00518f58
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0xD;
                goto L_005194c8;
            }
            v0 = a0 & 0x20;
            // 0x00518f64
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x00518f6c
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x2;
                goto L_005194c8;
            }
            lw(v0, sp, 0x4);
            // 0x00518f78
            charge(ctx, 3);
            v0 = slt(v0, s2);
            if (v0 != 0) {
                // 0x00518f84
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x16;
                goto L_005194c8;
            }
            v0 = addu(s2, s6);
            // 0x00518f90
            charge(ctx, 12);
            v1 = si(-1);
            a0 = addiu(v0, 1023);
            lw(a1, sp, 0x10);
            v1 = slt(v1, a0);
            v0 = addiu(v0, 2046);
            if (v1 != 0) v0 = a0;
            a0 = s3;
            s1 = sra(v0, 10);
            jal(ctx, 0x518FACu, gen::fn__fat_chain_trace_00515c98);
            s0 = v0;
            ld(ra, sp, 0x330);
            if (i64(s0) >= 0) {
                // 0x00518fc0
                charge(ctx, 3);
                v0 = slt(s0, s1);
                a0 = s3;
                if (v0 != 0) {
                    // 0x00518fcc
                    charge(ctx, 6);
                    a1 = addiu(sp, 0x298);
                    jal(ctx, 0x518FCCu, gen::fn__sceMcFatGetFreeClustSize_00515a40);
                    v1 = v0;
                    lw(v0, sp, 0x298);
                    ld(ra, sp, 0x330);
                    if (v0 == 0) {
                        // 0x00518fe4
                        charge(ctx, 4);
                        v0 = subu(s1, s0);
                        v0 = slt(v1, v0);
                        if (v0 == 0) {
                            goto L_00519000;
                        }
                        // 0x00518ff4
                        charge(ctx, 3);
                        v0 = lui(0x8101);
                        v0 = v0 | 0x1C;
                    }
                    // 0x005194cc (the shared epilogue, written out on this path)
                    charge(ctx, 11);
                    ld(fp, sp, 0x320);
                    ld(s7, sp, 0x310);
                    ld(s6, sp, 0x300);
                    ld(s5, sp, 0x2F0);
                    ld(s4, sp, 0x2E0);
                    ld(s3, sp, 0x2D0);
                    ld(s2, sp, 0x2C0);
                    ld(s1, sp, 0x2B0);
                    ld(s0, sp, 0x2A0);
                    sp = addiu(sp, 0x340);
                    return;
                }
            L_00519000:
                charge(ctx, 5);
                v0 = lui(0xFFFF);
                lw(a1, sp, 0x10);
                v0 = v0 | 0xFFFF;
                if (a1 != v0) {
                    s5 = s2;
                } else {
                    // 0x00519014
                    charge(ctx, 7);
                    s0 = addiu(sp, 0x298);
                    a0 = s3;
                    a1 = s0;
                    jal(ctx, 0x51901Cu, gen::fn__sceMcFatGetFreeClust_00515910);
                    lw(v1, sp, 0x298);
                    s1 = v0;
                    if (v1 != 0) {
                    L_005194c4:
                        charge(ctx, 1);
                        v0 = v1;
                        goto L_005194c8;
                    }
                    // 0x00519030
                    charge(ctx, 8);
                    a3 = s0;
                    a0 = s3;
                    a1 = s1;
                    a2 = si(-1);
                    jal(ctx, 0x51903Cu, gen::fn__sceMcFatWriteFatData_005157e0);
                    lw(v0, sp, 0x298);
                    ld(ra, sp, 0x330);
                    if (v0 == 0) {
                        // 0x00519050
                        charge(ctx, 7);
                        a0 = s3;
                        a1 = addiu(sp, 0x280);
                        jal(ctx, 0x519054u, gen::fn__sceMcCoreReadClock_0051b5f0);
                        lw(v1, sp, 0x4);
                        v1 = slt(v1, s5);
                        sw(s1, sp, 0x10);
                        if (v1 != 0) {
                            // 0x0051906c
                            charge(ctx, 1);
                            sw(s5, sp, 0x4);
                        }
                        // 0x00519070
                        charge(ctx, 45);
                        lbu(a1, sp, 0x287);
                        v1 = 10;
                        lbu(a3, sp, 0x282);
                        a0 = s3;
                        lbu(a2, sp, 0x281);
                        v0 = srl(a1, 4);
                        lbu(t7, sp, 0x286);
                        t3 = srl(a3, 4);
                        lbu(t6, sp, 0x285);
                        t0 = srl(a2, 4);
                        lbu(t4, sp, 0x283);
                        t5 = srl(t7, 4);
                        t1 = srl(t6, 4);
                        mult(v0, v0, v1);
                        t2 = srl(t4, 4);
                        mult(t0, t0, v1);
                        mult(t3, t3, v1);
                        a1 = a1 & 0xF;
                        mult(t5, t5, v1);
                        a3 = a3 & 0xF;
                        mult1(t1, t1, v1);
                        a2 = a2 & 0xF;
                        mult1(t2, t2, v1);
                        v0 = addu(v0, a1);
                        t3 = addu(t3, a3);
                        t0 = addu(t0, a2);
                        t7 = t7 & 0xF;
                        t6 = t6 & 0xF;
                        t4 = t4 & 0xF;
                        t5 = addu(t5, t7);
                        t1 = addu(t1, t6);
                        t2 = addu(t2, t4);
                        v0 = addiu(v0, 2000);
                        lw(a2, sp, 0x290);
                        lw(a3, sp, 0x294);
                        a1 = sp;
                        sh(v0, sp, 0x1E);
                        sb(t5, sp, 0x1D);
                        sb(t1, sp, 0x1C);
                        sb(t2, sp, 0x1B);
                        sb(t3, sp, 0x1A);
                        link(ctx, 0x519114u);  // $ra first: the delay slot below depends on it
                        sb(t0, sp, 0x19);
                        call(ctx, gen::fn__SetEntryByPos_00517310);
                        sw(v0, sp, 0x298);
                        if (v0 == 0) {
                            // 0x00519124
                            charge(ctx, 4);
                            a0 = s3;
                            jal(ctx, 0x519124u, gen::fn__sceMcFatFlushFatCache_00515588);
                            if (v0 != 0) {
                                // 0x00519134
                                charge(ctx, 4);
                                a0 = s3;
                                jal(ctx, 0x519134u, gen::fn__sceMcpFlushCache_0051a498);
                                lw(a1, sp, 0x10);
                                if (v0 == 0) {
                                    goto L_005194a4;
                                }
                                // 0x00519144
                                charge(ctx, 1);
                                s5 = s2;
                                goto L_00519148;
                            }
                        L_005194a4:
                            charge(ctx, 3);
                            v0 = lui(0x8101);
                            v0 = v0 | 0x6F;
                        }
                        goto L_005194c8;
                    }
                    // 0x005194cc (the shared epilogue, written out on this path)
                    charge(ctx, 11);
                    ld(fp, sp, 0x320);
                    ld(s7, sp, 0x310);
                    ld(s6, sp, 0x300);
                    ld(s5, sp, 0x2F0);
                    ld(s4, sp, 0x2E0);
                    ld(s3, sp, 0x2D0);
                    ld(s2, sp, 0x2C0);
                    ld(s1, sp, 0x2B0);
                    ld(s0, sp, 0x2A0);
                    sp = addiu(sp, 0x340);
                    return;
                }
            L_00519148:
                charge(ctx, 5);
                s1 = a1;
                fp = s6;
                v0 = slti(s5, 1024);
                s4 = s7;
                if (v0 == 0) {
                    // 0x0051915c
                    charge(ctx, 3);
                    s0 = addiu(sp, 0x298);
                    a1 = s1;
                    for (;;) {
                        // 0x00519168
                        charge(ctx, 6);
                        a0 = s3;
                        a2 = s0;
                        jal(ctx, 0x51916Cu, gen::fn__sceMcFatGetNextClustAlloc_00518da0);
                        lw(v1, sp, 0x298);
                        s1 = v0;
                        if (v1 != 0) {
                            goto L_005194c4;
                        }
                        // 0x00519180
                        charge(ctx, 4);
                        s2 = addiu(s2, -1024);
                        v0 = slti(s2, 1024);
                        a1 = s1;
                        if (v0 != 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x00519190
                charge(ctx, 2);
                if (i64(s2) > 0) {
                    // 0x00519198
                    charge(ctx, 5);
                    v0 = lui(0x8101);
                    lw(v1, sp, 0x298);
                    v0 = v0 | 0x59;
                    if (v1 == v0) {
                        goto L_005191ac;
                    }
                    v0 = 0x980000;
                    // 0x005191b8
                    charge(ctx, 8);
                    a0 = s3;
                    s0 = addiu(v0, -14144);
                    a2 = s1;
                    a1 = s0;
                    a3 = 1;
                    jal(ctx, 0x5191C8u, gen::fn__sceMcpReadUserClust_0051a9e0);
                    if (v0 == 0) {
                        goto L_005194a4;
                    }
                    // 0x005191d8
                    charge(ctx, 5);
                    v0 = 1024;
                    a2 = subu(v0, s2);
                    v1 = slt(a2, s6);
                    a0 = addu(s2, s0);
                    if (v1 != 0) {
                        // 0x005191ec
                        charge(ctx, 9);
                        a1 = s7;
                        jal(ctx, 0x5191ECu, gen::fn_memcpy_00521250);
                        a1 = s0;
                        a0 = s3;
                        a2 = s1;
                        a3 = 1;
                        jal(ctx, 0x519200u, gen::fn__sceMcpWriteUserClust_0051aa90);
                        v1 = addiu(s6, -1024);
                        if (v0 == 0) {
                            goto L_005194a4;
                        }
                        // 0x00519210
                        charge(ctx, 6);
                        v0 = addiu(s5, 1024);
                        a0 = addiu(s7, 1024);
                        s5 = subu(v0, s2);
                        s6 = addu(v1, s2);
                        s4 = subu(a0, s2);
                        goto L_00519254;
                    }
                    // 0x00519228
                    charge(ctx, 10);
                    a1 = s7;
                    a2 = s6;
                    jal(ctx, 0x51922Cu, gen::fn_memcpy_00521250);
                    a1 = s0;
                    a0 = s3;
                    a2 = s1;
                    a3 = 1;
                    jal(ctx, 0x519240u, gen::fn__sceMcpWriteUserClust_0051aa90);
                    s5 = addu(s5, s6);
                    if (v0 == 0) {
                        goto L_005194a4;
                    }
                    // 0x00519250
                    charge(ctx, 1);
                    s6 = 0;
                L_00519254:
                    charge(ctx, 7);
                    a1 = s1;
                    a0 = s3;
                    a2 = addiu(sp, 0x298);
                    jal(ctx, 0x51925Cu, gen::fn__sceMcFatGetNextClustAlloc_00518da0);
                    lw(v1, sp, 0x298);
                    s1 = v0;
                    if (v1 != 0) {
                        goto L_005194c4;
                    }
                    goto L_00519270;
                }
            L_00519270:
                charge(ctx, 2);
                s2 = 0;
                if (i64(s6) > 0) {
                    // 0x00519278
                    charge(ctx, 3);
                    v0 = slti(s6, 1024);
                    s0 = 0;
                    if (v0 == 0) {
                        // 0x00519284
                        charge(ctx, 1);
                        for (;;) {
                            // 0x00519288
                            charge(ctx, 2);
                            a1 = s1;
                            if (s2 == 0) {
                                // 0x00519290
                                charge(ctx, 3);
                                s2 = s1;
                                s0 = 1;
                                goto L_005192f0;
                            }
                            // 0x0051929c
                            charge(ctx, 6);
                            a0 = s3;
                            a2 = addiu(sp, 0x298);
                            jal(ctx, 0x5192A0u, gen::fn__sceMcFatGetNextClustAlloc_00518da0);
                            lw(v1, sp, 0x298);
                            s1 = v0;
                            if (v1 != 0) {
                                goto L_005194c4;
                            }
                            // 0x005192b4
                            charge(ctx, 3);
                            v0 = addu(s2, s0);
                            a2 = s2;
                            if (v0 == s1) {
                                // 0x005192ec
                                charge(ctx, 1);
                                s0 = addiu(s0, 1);
                            L_005192f0:
                                charge(ctx, 4);
                                s6 = addiu(s6, -1024);
                                v0 = slti(s6, 1024);
                                if (v0 != 0) {
                                    break;
                                }
                                backedge(ctx);
                                continue;
                            }
                            // 0x005192c0
                            charge(ctx, 6);
                            a0 = s3;
                            a1 = s4;
                            a3 = s0;
                            jal(ctx, 0x5192C8u, gen::fn__sceMcpWriteUserClustFast_0051aa48);
                            s2 = s1;
                            if (v0 == 0) {
                                goto L_005194a4;
                            }
                            // 0x005192d8
                            charge(ctx, 5);
                            v0 = sll(s0, 10);
                            s5 = addu(s5, v0);
                            s4 = addu(s4, v0);
                            s0 = 1;
                            goto L_005192f0;
                        }
                    }
                    // 0x00519300
                    charge(ctx, 2);
                    a2 = s2;
                    if (i64(s0) > 0) {
                        // 0x00519308
                        charge(ctx, 6);
                        a0 = s3;
                        a1 = s4;
                        a3 = s0;
                        jal(ctx, 0x519310u, gen::fn__sceMcpWriteUserClustFast_0051aa48);
                        if (v0 == 0) {
                            goto L_005194a4;
                        }
                        // 0x00519320
                        charge(ctx, 4);
                        v0 = sll(s0, 10);
                        s5 = addu(s5, v0);
                        s4 = addu(s4, v0);
                        if (i64(s6) <= 0) {
                            goto L_0051939c;
                        }
                        // 0x00519330
                        charge(ctx, 7);
                        a1 = s1;
                        a0 = s3;
                        a2 = addiu(sp, 0x298);
                        jal(ctx, 0x519338u, gen::fn__sceMcFatGetNextClustAlloc_00518da0);
                        lw(v1, sp, 0x298);
                        s1 = v0;
                        if (v1 != 0) {
                            goto L_005194c4;
                        }
                        goto L_0051934c;
                    }
                L_0051934c:
                    charge(ctx, 2);
                    v0 = 0x980000;
                    if (i64(s6) <= 0) {
                        goto L_0051939c;
                    }
                    // 0x00519354
                    charge(ctx, 8);
                    a0 = s3;
                    s0 = addiu(v0, -14144);
                    a2 = s1;
                    a1 = s0;
                    a3 = 1;
                    jal(ctx, 0x519364u, gen::fn__sceMcpReadUserClust_0051a9e0);
                    a1 = s4;
                    if (v0 == 0) {
                        goto L_005194a4;
                    }
                    // 0x00519374
                    charge(ctx, 10);
                    a0 = s0;
                    a2 = s6;
                    jal(ctx, 0x519378u, gen::fn_memcpy_00521250);
                    a1 = s0;
                    a2 = s1;
                    a0 = s3;
                    a3 = 1;
                    jal(ctx, 0x51938Cu, gen::fn__sceMcpWriteUserClust_0051aa90);
                    s5 = addu(s5, s6);
                    if (v0 == 0) {
                        goto L_005194a4;
                    }
                    goto L_0051939c;
                }
            L_0051939c:
                charge(ctx, 8);
                s1 = addiu(sp, 0x280);
                a0 = s3;
                a1 = s1;
                jal(ctx, 0x5193A4u, gen::fn__sceMcCoreReadClock_0051b5f0);
                lw(v1, sp, 0x4);
                v1 = slt(v1, s5);
                if (v1 != 0) {
                    sw(s5, sp, 0x4);
                }
                // 0x005193bc
                charge(ctx, 48);
                lbu(a1, sp, 0x287);
                v1 = 10;
                lbu(a3, sp, 0x282);
                a0 = s3;
                lbu(a2, sp, 0x281);
                v0 = srl(a1, 4);
                lbu(s0, sp, 0x286);
                t6 = srl(a3, 4);
                lbu(t3, sp, 0x285);
                t1 = srl(a2, 4);
                lbu(t2, sp, 0x283);
                t7 = srl(s0, 4);
                t4 = srl(t3, 4);
                mult(v0, v0, v1);
                t5 = srl(t2, 4);
                mult(t1, t1, v1);
                mult(t6, t6, v1);
                a1 = a1 & 0xF;
                mult(t7, t7, v1);
                lhu(t0, sp, 0x0);
                mult1(t4, t4, v1);
                a3 = a3 & 0xF;
                mult1(t5, t5, v1);
                a2 = a2 & 0xF;
                v0 = addu(v0, a1);
                t6 = addu(t6, a3);
                t1 = addu(t1, a2);
                s0 = s0 & 0xF;
                t3 = t3 & 0xF;
                t2 = t2 & 0xF;
                t7 = addu(t7, s0);
                t4 = addu(t4, t3);
                t5 = addu(t5, t2);
                t0 = t0 | 0x80;
                v0 = addiu(v0, 2000);
                lw(a2, sp, 0x290);
                lw(a3, sp, 0x294);
                a1 = sp;
                sh(t0, sp, 0x0);
                sh(v0, sp, 0x1E);
                sb(t7, sp, 0x1D);
                sb(t4, sp, 0x1C);
                sb(t5, sp, 0x1B);
                sb(t6, sp, 0x1A);
                link(ctx, 0x51946Cu);  // $ra first: the delay slot below depends on it
                sb(t1, sp, 0x19);
                call(ctx, gen::fn__SetEntryByPos_00517310);
                sw(v0, sp, 0x298);
                if (v0 == 0) {
                    // 0x0051947c
                    charge(ctx, 6);
                    lw(a1, sp, 0x290);
                    a2 = s1;
                    a0 = s3;
                    jal(ctx, 0x519484u, gen::fn__ParentDirUpdate_00517ab8);
                    sw(v0, sp, 0x298);
                    if (v0 == 0) {
                        // 0x00519494
                        charge(ctx, 4);
                        a0 = s3;
                        jal(ctx, 0x519494u, gen::fn__sceMcFatFlushFatCache_00515588);
                        if (v0 == 0) {
                            goto L_005194a4;
                        }
                        // 0x005194b0
                        charge(ctx, 5);
                        a0 = s3;
                        jal(ctx, 0x5194B0u, gen::fn__sceMcpFlushCache_0051a498);
                        v1 = lui(0x8101);
                        v1 = v1 | 0x6F;
                        if (v0 != 0) v1 = fp;
                        goto L_005194c4;
                    }
                }
                goto L_005194c8;
            }
            // 0x005194cc (the shared epilogue, written out on this path)
            charge(ctx, 11);
            ld(fp, sp, 0x320);
            ld(s7, sp, 0x310);
            ld(s6, sp, 0x300);
            ld(s5, sp, 0x2F0);
            ld(s4, sp, 0x2E0);
            ld(s3, sp, 0x2D0);
            ld(s2, sp, 0x2C0);
            ld(s1, sp, 0x2B0);
            ld(s0, sp, 0x2A0);
            sp = addiu(sp, 0x340);
            return;
        }
    L_005191ac:
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x9002;
        goto L_005194c8;
    }
L_005194c8:
    charge(ctx, 1);
    ld(ra, sp, 0x330);
    // 0x005194cc (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(fp, sp, 0x320);
    ld(s7, sp, 0x310);
    ld(s6, sp, 0x300);
    ld(s5, sp, 0x2F0);
    ld(s4, sp, 0x2E0);
    ld(s3, sp, 0x2D0);
    ld(s2, sp, 0x2C0);
    ld(s1, sp, 0x2B0);
    ld(s0, sp, 0x2A0);
    sp = addiu(sp, 0x340);
}

// 0x005194F8 _sceMcFatDeleteFile -- 560 bytes; frame 0x370: s3 sp+0x350, s0 sp+0x320, ra sp+0x360, s2 sp+0x340, s1 sp+0x330
// Delete a file or an empty directory: frees its chain in the FAT and clears its entry.
void _sceMcFatDeleteFile(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005194f8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x370);
    sd(s3, sp, 0x350);
    sd(s0, sp, 0x320);
    s3 = a0;
    sd(ra, sp, 0x360);
    s0 = a1;
    sd(s2, sp, 0x340);
    link(ctx, 0x519514u);  // $ra first: the delay slot below depends on it
    sd(s1, sp, 0x330);
    call(ctx, gen::fn__ConfInsert_00516b48);
    v1 = v0;
    sw(v0, sp, 0x31C);
    if (v1 == 0) {
        // 0x00519528
        charge(ctx, 8);
        s1 = addiu(sp, 0x210);
        a1 = s0;
        a0 = s3;
        a2 = s1;
        jal(ctx, 0x519534u, gen::fn__CheckFileDescript_00516be8);
        v1 = v0;
        sw(v0, sp, 0x31C);
        if (v1 != 0) {
            goto L_0051970c;
        }
        // 0x00519548
        charge(ctx, 11);
        a0 = s3;
        a1 = s1;
        a2 = sp;
        a3 = addiu(sp, 0x310);
        t0 = addiu(sp, 0x314);
        jal(ctx, 0x519558u, gen::fn__SearchFile_00516ec0);
        v1 = lui(0x8101);
        a0 = v0;
        v1 = v1 | 0x11;
        sw(v0, sp, 0x31C);
        if (a0 != v1) {
            goto L_0051970c;
        }
        // 0x00519574
        charge(ctx, 4);
        lhu(v1, sp, 0x0);
        v0 = v1 & 0x2;
        if (v0 == 0) {
            // 0x00519584
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0xD;
            goto L_0051970c;
        }
        v0 = v1 & 0x20;
        // 0x00519590
        charge(ctx, 2);
        s0 = addiu(sp, 0x290);
        if (v0 != 0) {
            // 0x00519598
            charge(ctx, 17);
            a1 = s1;
            a0 = s0;
            jal(ctx, 0x51959Cu, gen::fn_strcpy_00524270);
            a1 = 0x7C0000;
            a0 = s0;
            a1 = addiu(a1, -6560);  // "/*"
            jal(ctx, 0x5195ACu, gen::fn_strcat_00523e68);
            a1 = s0;
            a0 = s3;
            a2 = 0;
            a3 = si(-1);
            t0 = 0;
            t1 = addiu(sp, 0x318);
            jal(ctx, 0x5195C8u, gen::fn__sceMcFatGetDir_00519850);
            v1 = v0;
            sw(v0, sp, 0x31C);
            if (v1 != 0) {
                goto L_0051970c;
            }
            // 0x005195dc
            charge(ctx, 4);
            lw(v0, sp, 0x318);
            v0 = slti(v0, 3);
            lhu(v1, sp, 0x0);
            if (v0 != 0) {
                goto L_005195f8;
            }
            // 0x005195ec
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x5A;
            goto L_0051970c;
        }
    L_005195f8:
        charge(ctx, 10);
        v0 = v1 ^ 0x8000;
        lw(a2, sp, 0x310);
        lw(a3, sp, 0x314);
        a0 = s3;
        sh(v0, sp, 0x0);
        a1 = sp;
        jal(ctx, 0x51960Cu, gen::fn__SetEntryByPos_00517310);
        v1 = v0;
        sw(v0, sp, 0x31C);
        if (v1 != 0) {
            goto L_0051970c;
        }
        // 0x00519620
        charge(ctx, 4);
        a0 = s3;
        jal(ctx, 0x519620u, gen::fn__sceMcpFlushCache_0051a498);
        lw(a2, sp, 0x10);
        if (v0 != 0) {
            // 0x00519630
            charge(ctx, 4);
            v0 = lui(0xFFFF);
            v0 = v0 | 0xFFFF;
            s0 = a2;
            if (a2 == v0) {
                // 0x00519640
                charge(ctx, 2);
                v0 = 0;
                goto L_0051970c;
            }
            // 0x00519648
            charge(ctx, 2);
            s2 = addiu(sp, 0x31C);
            for (;;) {
                // 0x00519684
                charge(ctx, 8);
                s1 = s0;
                a0 = s3;
                a1 = s1;
                a2 = s2;
                jal(ctx, 0x519690u, gen::fn__sceMcFatGetNextClust_00515730);
                lw(v1, sp, 0x31C);
                s0 = v0;
                if (v1 != 0) {
                    goto L_005196ec;
                }
                // 0x005196a4
                charge(ctx, 4);
                v0 = lui(0xFFFF);
                v0 = v0 | 0xFFFD;
                if (s0 == v0) {
                    goto L_005196c0;
                }
                // 0x005196b4
                charge(ctx, 3);
                v0 = lui(0x8000);
                a1 = s1;
                if (i64(s0) >= 0) {
                    goto L_005196c0;
                }
                backedge(ctx);
                // 0x00519650
                charge(ctx, 7);
                a2 = s0 ^ v0;
                a0 = s3;
                a3 = s2;
                jal(ctx, 0x519658u, gen::fn__sceMcFatWriteFatData_005157e0);
                lw(v0, sp, 0x31C);
                ld(ra, sp, 0x360);
                if (v0 == 0) {
                    // 0x0051966c
                    charge(ctx, 4);
                    v0 = lui(0xFFFF);
                    v0 = v0 | 0xFFFF;
                    cc = s0 == v0;  // the condition, before the delay slot changes it
                    v0 = 0x7FFF0000;
                    if (cc) {
                        goto L_005196c0;
                    }
                    // 0x0051967c
                    charge(ctx, 2);
                    v0 = v0 | 0xFFFF;
                    s0 = s0 & v0;
                    continue;
                }
                break;
            }
            // 0x00519710 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(s3, sp, 0x350);
            ld(s2, sp, 0x340);
            ld(s1, sp, 0x330);
            ld(s0, sp, 0x320);
            sp = addiu(sp, 0x370);
            return;
        }
    L_005196e0:
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x6F;
        goto L_0051970c;
    }
L_0051970c:
    charge(ctx, 1);
    ld(ra, sp, 0x360);
    // 0x00519710 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s3, sp, 0x350);
    ld(s2, sp, 0x340);
    ld(s1, sp, 0x330);
    ld(s0, sp, 0x320);
    sp = addiu(sp, 0x370);
    return;
L_005196c0:
    charge(ctx, 4);
    a0 = s3;
    jal(ctx, 0x5196C0u, gen::fn__sceMcFatFlushFatCache_00515588);
    if (v0 == 0) {
        goto L_005196e0;
    }
    // 0x005196d0
    charge(ctx, 4);
    a0 = s3;
    jal(ctx, 0x5196D0u, gen::fn__sceMcpFlushCache_0051a498);
    a0 = 2200;
    if (v0 == 0) {
        goto L_005196e0;
    }
    // 0x005196f4
    charge(ctx, 6);
    v1 = 0x980000;
    mult(a0, s3, a0);
    v1 = addiu(v1, -18552);  // &0x97B788
    v0 = 0;
    v1 = addu(v1, a0);
    sw(zero, v1, 2192);
    goto L_0051970c;
L_005196ec:
    charge(ctx, 2);
    v0 = v1;
    goto L_0051970c;
}

// 0x00519728 _sceMcFatChDir -- 292 bytes; frame 0x2E0: s3 sp+0x2B0, s2 sp+0x2A0, s1 sp+0x290, ra sp+0x2D0, s4 sp+0x2C0, s0 sp+0x280
// Change the port's current directory (checked to exist and be a directory).
void _sceMcFatChDir(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00519728
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2E0);
    sd(s3, sp, 0x2B0);
    sd(s2, sp, 0x2A0);
    s3 = a2;
    sd(s1, sp, 0x290);
    s2 = a0;
    s1 = addiu(sp, 0x200);
    a2 = s1;
    sd(ra, sp, 0x2D0);
    sd(s4, sp, 0x2C0);
    link(ctx, 0x519750u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x280);
    call(ctx, gen::fn__CheckFileDescript_00516be8);
    ld(ra, sp, 0x2D0);
    if (v0 == 0) {
        // 0x00519760
        charge(ctx, 7);
        v0 = 0x7C0000;
        a0 = s1;
        s4 = addiu(v0, -6648);  // &0x7BE608
        a1 = s4;
        jal(ctx, 0x51976Cu, gen::fn_strcmp_00524128);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 2200;
        if (!cc) {
            // 0x0051977c
            charge(ctx, 8);
            a0 = 0x980000;
            mult(v0, s2, v0);
            a0 = addiu(a0, -16496);  // &0x97BF90
            a1 = s1;
            a0 = addu(v0, a0);
            jal(ctx, 0x51978Cu, gen::fn_strcpy_00524270);
            goto L_00519818;
        }
        // 0x0051979c
        charge(ctx, 4);
        a0 = s2;
        jal(ctx, 0x51979Cu, gen::fn__ConfInsert_00516b48);
        ld(ra, sp, 0x2D0);
        if (v0 == 0) {
            // 0x005197ac
            charge(ctx, 10);
            a0 = s2;
            a1 = s1;
            a2 = sp;
            a3 = 0;
            t0 = 0;
            jal(ctx, 0x5197BCu, gen::fn__SearchFile_00516ec0);
            v1 = lui(0x8101);
            v1 = v1 | 0x11;
            ld(ra, sp, 0x2D0);
            if (v0 == v1) {
                // 0x005197d4
                charge(ctx, 4);
                lhu(v0, sp, 0x0);
                v0 = v0 & 0x20;
                s0 = 2200;
                if (v0 != 0) {
                    // 0x005197f0
                    charge(ctx, 10);
                    v0 = 0x980000;
                    mult(s0, s2, s0);
                    v0 = addiu(v0, -16496);  // &0x97BF90
                    a1 = s1;
                    s0 = addu(s0, v0);
                    a0 = s0;
                    jal(ctx, 0x519804u, gen::fn_strcpy_00524270);
                    a0 = s0;
                    a1 = s4;
                    jal(ctx, 0x519810u, gen::fn_strcat_00523e68);
                L_00519818:
                    charge(ctx, 2);
                    a0 = s3;
                    if (s3 != 0) {
                        // 0x00519820
                        charge(ctx, 2);
                        a1 = s1;
                        jal(ctx, 0x519820u, gen::fn_strcpy_00524270);
                    }
                    // 0x00519828
                    charge(ctx, 2);
                    v0 = 0;
                    ld(ra, sp, 0x2D0);
                } else {
                    // 0x005197e4
                    charge(ctx, 3);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x14;
                }
            }
        }
    }
    // 0x00519830 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s4, sp, 0x2C0);
    ld(s3, sp, 0x2B0);
    ld(s2, sp, 0x2A0);
    ld(s1, sp, 0x290);
    ld(s0, sp, 0x280);
    sp = addiu(sp, 0x2E0);
}

// 0x00519850 _sceMcFatGetDir -- 1308 bytes; frame 0x600: s6 sp+0x5C0, s7 sp+0x5D0, s1 sp+0x570, s0 sp+0x560, ra sp+0x5F0, fp sp+0x5E0, s5 sp+0x5B0, s4 sp+0x5A0, s3 sp+0x590, s2 sp+0x580
// List the entries of a directory matching a wild-card name into the caller's table (continuing from an index).
void _sceMcFatGetDir(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00519850
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x600);
    sd(s6, sp, 0x5C0);
    sd(s7, sp, 0x5D0);
    s6 = a0;
    sd(s1, sp, 0x570);
    s7 = a2;
    sd(s0, sp, 0x560);
    s1 = t0;
    sd(ra, sp, 0x5F0);
    s0 = a1;
    sd(fp, sp, 0x5E0);
    sd(s5, sp, 0x5B0);
    sd(s4, sp, 0x5A0);
    sd(s3, sp, 0x590);
    sd(s2, sp, 0x580);
    sw(a3, sp, 0x544);
    sw(t1, sp, 0x548);
    link(ctx, 0x519894u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x54C);
    call(ctx, gen::fn__sceMcCoreGetConnection_0051c0c0);
    v1 = 2200;
    if (v0 != 0) {
        // 0x005198b0
        charge(ctx, 7);
        v0 = 0x980000;
        mult(v1, s6, v1);
        v0 = addiu(v0, -18552);  // &0x97B788
        v0 = addu(v0, v1);
        lw(a0, v0, 2188);
        a1 = s0;
        if (a0 != 0) {
            // 0x005198cc
            charge(ctx, 5);
            a0 = s6;
            a2 = sp;
            jal(ctx, 0x5198D0u, gen::fn__make_path_00515218);
            a0 = sp;
            if (v0 != 0) {
                // 0x005198e0
                charge(ctx, 6);
                v0 = 0x7C0000;
                s2 = addiu(v0, -6648);  // &0x7BE608
                a1 = s2;
                jal(ctx, 0x5198E8u, gen::fn_strcmp_00524128);
                s0 = addiu(sp, 0x80);
                if (v0 == 0) {
                    goto L_005198f8;
                }
                // 0x00519904
                charge(ctx, 19);
                a1 = sp;
                a0 = s0;
                jal(ctx, 0x519908u, gen::fn_strcpy_00524270);
                a0 = s0;
                a1 = 47;
                jal(ctx, 0x519914u, gen::fn_strrchr_005249e8);
                v1 = addiu(sp, 0x100);
                a0 = s0;
                sw(v1, sp, 0x550);
                link(ctx, 0x519928u);  // $ra first: the delay slot below depends on it
                sb(zero, v0, 0);
                call(ctx, gen::fn_strlen_00524388);
                v0 = addiu(v0, 1);
                lw(a0, sp, 0x550);
                a1 = addu(s0, v0);
                jal(ctx, 0x519938u, gen::fn_strcpy_00524270);
                a0 = s0;
                jal(ctx, 0x519940u, gen::fn_strlen_00524388);
                a1 = s0;
                if (v0 != 0) {
                    // 0x0051996c
                    charge(ctx, 5);
                    a0 = s6;
                    a2 = addiu(sp, 0x340);
                    a3 = 0;
                    t0 = 0;
                    s0 = 0;
                } else {
                    // 0x00519950
                    charge(ctx, 7);
                    a1 = s2;
                    a0 = s6;
                    a2 = addiu(sp, 0x340);
                    a3 = 0;
                    t0 = 0;
                    s0 = 1;
                }
                // 0x00519980
                charge(ctx, 7);
                jal(ctx, 0x519980u, gen::fn__SearchFile_00516ec0);
                v1 = lui(0x8101);
                a0 = v0;
                v1 = v1 | 0x11;
                sw(v0, sp, 0x540);
                if (a0 == v1) {
                    // 0x0051999c
                    charge(ctx, 4);
                    lhu(v0, sp, 0x340);
                    v0 = v0 & 0x20;
                    a1 = addiu(sp, 0x140);
                    if (v0 != 0) {
                        // 0x005199b8
                        charge(ctx, 8);
                        lw(a2, sp, 0x350);
                        sw(a1, sp, 0x554);
                        a0 = s6;
                        a3 = 0;
                        jal(ctx, 0x5199C4u, gen::fn__GetEntryByPos_00515b18);
                        v1 = v0;
                        sw(v0, sp, 0x540);
                        if (v1 == 0) {
                            // 0x005199d8
                            charge(ctx, 4);
                            lhu(v0, sp, 0x140);
                            v0 = v0 & 0x8000;
                            s3 = addiu(sp, 0x180);
                            if (v0 != 0) {
                                // 0x005199e8
                                charge(ctx, 6);
                                a2 = 0x7C0000;
                                a0 = s3;
                                a1 = addiu(a2, -6672);  // &0x7BE5F0
                                jal(ctx, 0x5199F0u, gen::fn_strcmp_00524128);
                                lw(a2, sp, 0x350);
                                if (v0 != 0) {
                                    goto L_00519cf8;
                                }
                                // 0x00519a00
                                charge(ctx, 7);
                                a0 = s6;
                                lw(a1, sp, 0x554);
                                a3 = 1;
                                jal(ctx, 0x519A08u, gen::fn__GetEntryByPos_00515b18);
                                v1 = v0;
                                sw(v0, sp, 0x540);
                                if (v1 != 0) {
                                    goto L_00519a1c;
                                }
                                // 0x00519a40
                                charge(ctx, 4);
                                lhu(v0, sp, 0x140);
                                v0 = v0 & 0x8000;
                                a3 = 0x7C0000;
                                if (v0 == 0) {
                                    goto L_00519cf8;
                                }
                                // 0x00519a50
                                charge(ctx, 5);
                                a0 = s3;
                                a1 = addiu(a3, -6664);
                                jal(ctx, 0x519A54u, gen::fn_strcmp_00524128);
                                lw(v1, sp, 0x344);
                                if (v0 != 0) {
                                    goto L_00519cf8;
                                }
                                // 0x00519a64
                                charge(ctx, 3);
                                v0 = slti(v1, 2);
                                if (v0 != 0) {
                                    goto L_00519cf8;
                                }
                                // 0x00519a70
                                charge(ctx, 3);
                                v0 = slt(s7, v1);
                                fp = 0;
                                if (v0 != 0) {
                                    // 0x00519a90
                                    charge(ctx, 2);
                                    lw(s4, sp, 0x350);
                                    if (s0 != 0) {
                                        // 0x00519a98
                                        charge(ctx, 3);
                                        v0 = addiu(v1, -2);
                                        sw(v0, sp, 0x344);
                                        if (v0 != 0) {
                                            // 0x00519ab8
                                            charge(ctx, 9);
                                            a1 = s4;
                                            a0 = s6;
                                            a2 = addiu(sp, 0x540);
                                            jal(ctx, 0x519AC0u, gen::fn__sceMcFatGetNextClustSelf_00515778);
                                            v1 = lui(0x8101);
                                            lw(a0, sp, 0x540);
                                            v1 = v1 | 0x59;
                                            s4 = v0;
                                            if (a0 == v1) {
                                                goto L_00519cf8;
                                            }
                                            // 0x00519adc
                                            charge(ctx, 2);
                                            lw(v0, sp, 0x344);
                                            if (a0 != 0) {
                                                goto L_00519ae4;
                                            }
                                        L_00519d24:
                                            charge(ctx, 2);
                                            cc = v0 != 0;  // the condition, before the delay slot changes it
                                            v0 = 0x980000;
                                            if (cc) {
                                                backedge(ctx);
                                                // 0x00519af8
                                                charge(ctx, 8);
                                                a0 = s6;
                                                s0 = addiu(v0, -14144);
                                                a2 = s4;
                                                a1 = s0;
                                                a3 = 1;
                                                jal(ctx, 0x519B08u, gen::fn__sceMcpReadUserClust_0051a9e0);
                                                s2 = s0;
                                                if (v0 == 0) {
                                                    backedge(ctx);
                                                    goto L_00519aec;
                                                }
                                                // 0x00519b18
                                                charge(ctx, 2);
                                                s5 = 0;
                                                s0 = addiu(s0, 512);
                                                for (;;) {
                                                    // 0x00519b20
                                                    charge(ctx, 4);
                                                    lw(a0, sp, 0x554);
                                                    v0 = s2 & 0x7;
                                                    v1 = s2;
                                                    if (v0 == 0) {
                                                        // 0x00519b90
                                                        charge(ctx, 1);
                                                        v0 = s0;
                                                        for (;;) {
                                                            // 0x00519b94
                                                            charge(ctx, 13);
                                                            ld(t1, v1, 0);
                                                            ld(a1, v1, 8);
                                                            ld(a2, v1, 16);
                                                            ld(a3, v1, 24);
                                                            sd(t1, a0, 0);
                                                            sd(a1, a0, 8);
                                                            sd(a2, a0, 16);
                                                            sd(a3, a0, 24);
                                                            v1 = addiu(v1, 32);
                                                            a0 = addiu(a0, 32);
                                                            if (v1 == v0) {
                                                                break;
                                                            }
                                                            backedge(ctx);
                                                        }
                                                        // 0x00519bc8
                                                        charge(ctx, 1);
                                                        lhu(v1, sp, 0x140);
                                                    } else {
                                                        // 0x00519b30
                                                        charge(ctx, 1);
                                                        v0 = s0;
                                                        for (;;) {
                                                            // 0x00519b34
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
                                                        // 0x00519b88
                                                        charge(ctx, 2);
                                                        lhu(v1, sp, 0x140);
                                                    }
                                                    // 0x00519bcc
                                                    charge(ctx, 3);
                                                    v0 = v1 & 0x8000;
                                                    sb(zero, sp, 0x19F);
                                                    if (v0 != 0) {
                                                        // 0x00519bd8
                                                        charge(ctx, 3);
                                                        v0 = v1 & 0x2000;
                                                        cc = v0 != 0;  // the condition, before the delay slot changes it
                                                        lw(v0, sp, 0x344);
                                                        if (!cc) {
                                                            // 0x00519be4
                                                            charge(ctx, 6);
                                                            lw(a1, sp, 0x550);
                                                            a0 = addiu(sp, 0x180);
                                                            jal(ctx, 0x519BE8u, gen::fn_isWildFit_00514f30);
                                                            v1 = 1;
                                                            if (v0 != v1) {
                                                                lw(v0, sp, 0x344);
                                                                goto L_00519ca8;
                                                            }
                                                            // 0x00519bfc
                                                            charge(ctx, 2);
                                                            if (s7 != 0) {
                                                                s7 = addiu(s7, -1);
                                                                goto L_00519ca4;
                                                            }
                                                            // 0x00519c04
                                                            charge(ctx, 2);
                                                            lw(t0, sp, 0x544);
                                                            if (s1 != 0) {
                                                                // 0x00519c0c
                                                                charge(ctx, 2);
                                                                lw(v1, sp, 0x144);
                                                                if (i64(t0) > 0) {
                                                                    // 0x00519c14
                                                                    charge(ctx, 20);
                                                                    a0 = addiu(s1, 24);
                                                                    lhu(v0, sp, 0x140);
                                                                    a1 = s3;
                                                                    ldl(t1, sp, 0x14F);
                                                                    ldr(t1, sp, 0x148);
                                                                    sdl(t1, s1, 7);
                                                                    sdr(t1, s1, 0);
                                                                    ldl(t1, sp, 0x15F);
                                                                    ldr(t1, sp, 0x158);
                                                                    sdl(t1, s1, 15);
                                                                    sdr(t1, s1, 8);
                                                                    sw(v1, s1, 16);
                                                                    link(ctx, 0x519C44u);  // $ra first: the delay slot below depends on it
                                                                    sh(v0, s1, 20);
                                                                    call(ctx, gen::fn_strcpy_00524270);
                                                                    t1 = 0x7C0000;
                                                                    a0 = s3;
                                                                    a1 = addiu(t1, -6672);  // &0x7BE5F0
                                                                    jal(ctx, 0x519C54u, gen::fn_strcmp_00524128);
                                                                    cc = v0 != 0;  // the condition, before the delay slot changes it
                                                                    v0 = 0x7C0000;
                                                                    if (!cc) {
                                                                        // 0x00519c64
                                                                        charge(ctx, 3);
                                                                        lhu(v0, sp, 0x340);
                                                                        sh(v0, s1, 20);
                                                                        v0 = 0x7C0000;
                                                                    }
                                                                    // 0x00519c70
                                                                    charge(ctx, 4);
                                                                    a0 = s3;
                                                                    a1 = addiu(v0, -6664);
                                                                    s1 = addiu(s1, 56);
                                                                    jal(ctx, 0x519C78u, gen::fn_strcmp_00524128);
                                                                }
                                                            }
                                                            // 0x00519c80
                                                            charge(ctx, 3);
                                                            lw(v1, sp, 0x544);
                                                            fp = addiu(fp, 0x1);
                                                            if (i64(v1) <= 0) {
                                                                goto L_00519ca4;
                                                            }
                                                            // 0x00519c8c
                                                            charge(ctx, 3);
                                                            v0 = slt(fp, v1);
                                                            cc = v0 != 0;  // the condition, before the delay slot changes it
                                                            lw(v0, sp, 0x344);
                                                            if (cc) {
                                                                goto L_00519ca8;
                                                            }
                                                            goto L_00519c98_52;
                                                        }
                                                    L_00519ca8:
                                                        charge(ctx, 3);
                                                        v0 = addiu(v0, -1);
                                                        sw(v0, sp, 0x344);
                                                        if (v0 == 0) {
                                                            goto L_00519d04;
                                                        }
                                                        // 0x00519cb4
                                                        charge(ctx, 5);
                                                        s5 = addiu(s5, 1);
                                                        s0 = addiu(s0, 512);
                                                        v0 = slti(s5, 2);
                                                        s2 = addiu(s2, 512);
                                                        if (v0 != 0) {
                                                            backedge(ctx);
                                                            continue;
                                                        }
                                                        break;
                                                    }
                                                L_00519ca4:
                                                    charge(ctx, 1);
                                                    lw(v0, sp, 0x344);
                                                    goto L_00519ca8;
                                                }
                                            L_00519cc8:
                                                charge(ctx, 4);
                                                lw(a2, sp, 0x54C);
                                                v0 = 1;
                                                a1 = s4;
                                                if (a2 == v0) {
                                                    goto L_00519d2c;
                                                }
                                                // 0x00519cd8
                                                charge(ctx, 8);
                                                a0 = s6;
                                                a2 = addiu(sp, 0x540);
                                                jal(ctx, 0x519CDCu, gen::fn__sceMcFatGetNextClustSelf_00515778);
                                                v1 = lui(0x8101);
                                                lw(a0, sp, 0x540);
                                                v1 = v1 | 0x59;
                                                s4 = v0;
                                                if (a0 == v1) {
                                                    goto L_00519cf8;
                                                }
                                                // 0x00519d10
                                                charge(ctx, 2);
                                                lw(t0, sp, 0x54C);
                                                if (a0 != 0) {
                                                    backedge(ctx);
                                                L_00519ae4:
                                                    charge(ctx, 2);
                                                    v0 = a0;
                                                } else {
                                                    // 0x00519d18
                                                    charge(ctx, 2);
                                                    lw(t1, sp, 0x548);
                                                    if (t0 == 0) {
                                                        goto L_00519d20;
                                                    }
                                                L_00519d30:
                                                    charge(ctx, 2);
                                                    if (t1 != 0) {
                                                        sw(fp, t1, 0);
                                                    }
                                                L_00519d38:
                                                    charge(ctx, 1);
                                                    v0 = 0;
                                                }
                                                // 0x00519d3c (the shared epilogue, written out on this path)
                                                charge(ctx, 12);
                                                ld(ra, sp, 0x5F0);
                                                ld(fp, sp, 0x5E0);
                                                ld(s7, sp, 0x5D0);
                                                ld(s6, sp, 0x5C0);
                                                ld(s5, sp, 0x5B0);
                                                ld(s4, sp, 0x5A0);
                                                ld(s3, sp, 0x590);
                                                ld(s2, sp, 0x580);
                                                ld(s1, sp, 0x570);
                                                ld(s0, sp, 0x560);
                                                sp = addiu(sp, 0x600);
                                                return;
                                            }
                                        L_00519d2c:
                                            charge(ctx, 1);
                                            lw(t1, sp, 0x548);
                                            goto L_00519d30;
                                        }
                                        // 0x00519aa4
                                        charge(ctx, 3);
                                        lw(t1, sp, 0x548);
                                        if (t1 != 0) {
                                            sw(zero, t1, 0);
                                            goto L_00519d38;
                                        }
                                        // 0x00519ab0
                                        charge(ctx, 2);
                                        v0 = 0;
                                        // 0x00519d3c (the shared epilogue, written out on this path)
                                        charge(ctx, 12);
                                        ld(ra, sp, 0x5F0);
                                        ld(fp, sp, 0x5E0);
                                        ld(s7, sp, 0x5D0);
                                        ld(s6, sp, 0x5C0);
                                        ld(s5, sp, 0x5B0);
                                        ld(s4, sp, 0x5A0);
                                        ld(s3, sp, 0x590);
                                        ld(s2, sp, 0x580);
                                        ld(s1, sp, 0x570);
                                        ld(s0, sp, 0x560);
                                        sp = addiu(sp, 0x600);
                                        return;
                                    }
                                L_00519d20:
                                    charge(ctx, 1);
                                    lw(v0, sp, 0x344);
                                    goto L_00519d24;
                                }
                                // 0x00519a7c
                                charge(ctx, 3);
                                lw(t0, sp, 0x548);
                                if (t0 != 0) {
                                    sw(zero, t0, 0);
                                    goto L_00519d38;
                                }
                                // 0x00519a88
                                charge(ctx, 2);
                                v0 = 0;
                                // 0x00519d3c (the shared epilogue, written out on this path)
                                charge(ctx, 12);
                                ld(ra, sp, 0x5F0);
                                ld(fp, sp, 0x5E0);
                                ld(s7, sp, 0x5D0);
                                ld(s6, sp, 0x5C0);
                                ld(s5, sp, 0x5B0);
                                ld(s4, sp, 0x5A0);
                                ld(s3, sp, 0x590);
                                ld(s2, sp, 0x580);
                                ld(s1, sp, 0x570);
                                ld(s0, sp, 0x560);
                                sp = addiu(sp, 0x600);
                                return;
                            }
                        L_00519cf8:
                            charge(ctx, 3);
                            v0 = lui(0x8101);
                            v0 = v0 | 0x9002;
                            // 0x00519d3c (the shared epilogue, written out on this path)
                            charge(ctx, 12);
                            ld(ra, sp, 0x5F0);
                            ld(fp, sp, 0x5E0);
                            ld(s7, sp, 0x5D0);
                            ld(s6, sp, 0x5C0);
                            ld(s5, sp, 0x5B0);
                            ld(s4, sp, 0x5A0);
                            ld(s3, sp, 0x590);
                            ld(s2, sp, 0x580);
                            ld(s1, sp, 0x570);
                            ld(s0, sp, 0x560);
                            sp = addiu(sp, 0x600);
                            return;
                        }
                    L_00519a1c:
                        charge(ctx, 4);
                        v0 = lui(0x8101);
                        v0 = v0 | 0x2;
                        if (v1 != v0) {
                            lw(v0, sp, 0x540);
                        } else {
                            // 0x00519a2c
                            charge(ctx, 5);
                            v0 = lui(0x8101);
                            v0 = v0 | 0x9002;
                            sw(v0, sp, 0x540);
                            lw(v0, sp, 0x540);
                        }
                    } else {
                        // 0x005199ac
                        charge(ctx, 3);
                        v0 = lui(0x8101);
                        v0 = v0 | 0x14;
                    }
                }
                // 0x00519d3c (the shared epilogue, written out on this path)
                charge(ctx, 12);
                ld(ra, sp, 0x5F0);
                ld(fp, sp, 0x5E0);
                ld(s7, sp, 0x5D0);
                ld(s6, sp, 0x5C0);
                ld(s5, sp, 0x5B0);
                ld(s4, sp, 0x5A0);
                ld(s3, sp, 0x590);
                ld(s2, sp, 0x580);
                ld(s1, sp, 0x570);
                ld(s0, sp, 0x560);
                sp = addiu(sp, 0x600);
                return;
            }
        L_005198f8:
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x16;
            // 0x00519d3c (the shared epilogue, written out on this path)
            charge(ctx, 12);
            ld(ra, sp, 0x5F0);
            ld(fp, sp, 0x5E0);
            ld(s7, sp, 0x5D0);
            ld(s6, sp, 0x5C0);
            ld(s5, sp, 0x5B0);
            ld(s4, sp, 0x5A0);
            ld(s3, sp, 0x590);
            ld(s2, sp, 0x580);
            ld(s1, sp, 0x570);
            ld(s0, sp, 0x560);
            sp = addiu(sp, 0x600);
            return;
        }
    L_00519aec:
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x6F;
    } else {
        // 0x005198a4
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x13;
    }
    // 0x00519d3c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x5F0);
    ld(fp, sp, 0x5E0);
    ld(s7, sp, 0x5D0);
    ld(s6, sp, 0x5C0);
    ld(s5, sp, 0x5B0);
    ld(s4, sp, 0x5A0);
    ld(s3, sp, 0x590);
    ld(s2, sp, 0x580);
    ld(s1, sp, 0x570);
    ld(s0, sp, 0x560);
    sp = addiu(sp, 0x600);
    return;
L_00519c98_52:
    charge(ctx, 3);
    a1 = 1;
    sw(a1, sp, 0x54C);
    goto L_00519cc8;
L_00519d04:
    charge(ctx, 3);
    a3 = 1;
    sw(a3, sp, 0x54C);
    backedge(ctx);
    goto L_00519cc8;
}

// 0x00519D70 _sceMcFatSetAttr -- 392 bytes; frame 0x2E0: s1 sp+0x2B0, s2 sp+0x2C0, s0 sp+0x2A0, ra sp+0x2D0
// Set a file's attributes / times from a record.
void _sceMcFatSetAttr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00519d70
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2E0);
    sd(s1, sp, 0x2B0);
    s1 = a0;
    sd(s2, sp, 0x2C0);
    sd(s0, sp, 0x2A0);
    s2 = a2 & 0xFFFF;
    sd(ra, sp, 0x2D0);
    s0 = a1;
    jal(ctx, 0x519D8Cu, gen::fn__ConfInsert_00516b48);
    ld(ra, sp, 0x2D0);
    if (v0 == 0) {
        // 0x00519d9c
        charge(ctx, 6);
        a1 = s0;
        a0 = s1;
        a2 = sp;
        jal(ctx, 0x519DA4u, gen::fn__CheckFileDescript_00516be8);
        ld(ra, sp, 0x2D0);
        if (v0 == 0) {
            // 0x00519db4
            charge(ctx, 11);
            s0 = addiu(sp, 0x80);
            a0 = s1;
            a1 = sp;
            a2 = s0;
            a3 = addiu(sp, 0x290);
            t0 = addiu(sp, 0x294);
            jal(ctx, 0x519DC8u, gen::fn__SearchFile_00516ec0);
            v1 = lui(0x8101);
            v1 = v1 | 0x11;
            ld(ra, sp, 0x2D0);
            if (v0 == v1) {
                // 0x00519de0
                charge(ctx, 4);
                lhu(v1, sp, 0x80);
                v0 = v1 & 0x20;
                if (v0 != 0) {
                    v0 = v1 & 0xE7F0;
                    // 0x00519dfc
                    charge(ctx, 51);
                    a0 = s1;
                    v1 = s2 & 0x180F;
                    a1 = addiu(sp, 0x280);
                    v0 = v0 | v1;
                    link(ctx, 0x519E0Cu);  // $ra first: the delay slot below depends on it
                    sh(v0, sp, 0x80);
                    call(ctx, gen::fn__sceMcCoreReadClock_0051b5f0);
                    lbu(a0, sp, 0x287);
                    v1 = 10;
                    lbu(a3, sp, 0x282);
                    a1 = s0;
                    lbu(a2, sp, 0x281);
                    v0 = srl(a0, 4);
                    lbu(t7, sp, 0x286);
                    t3 = srl(a3, 4);
                    lbu(t6, sp, 0x285);
                    t0 = srl(a2, 4);
                    lbu(t4, sp, 0x283);
                    t5 = srl(t7, 4);
                    t1 = srl(t6, 4);
                    mult(v0, v0, v1);
                    t2 = srl(t4, 4);
                    mult(t0, t0, v1);
                    mult(t3, t3, v1);
                    a0 = a0 & 0xF;
                    mult(t5, t5, v1);
                    a3 = a3 & 0xF;
                    mult1(t1, t1, v1);
                    a2 = a2 & 0xF;
                    mult1(t2, t2, v1);
                    v0 = addu(v0, a0);
                    t3 = addu(t3, a3);
                    t0 = addu(t0, a2);
                    t7 = t7 & 0xF;
                    t6 = t6 & 0xF;
                    t4 = t4 & 0xF;
                    t5 = addu(t5, t7);
                    t1 = addu(t1, t6);
                    t2 = addu(t2, t4);
                    v0 = addiu(v0, 2000);
                    lw(a2, sp, 0x290);
                    lw(a3, sp, 0x294);
                    a0 = s1;
                    sh(v0, sp, 0x9E);
                    sb(t5, sp, 0x9D);
                    sb(t1, sp, 0x9C);
                    sb(t2, sp, 0x9B);
                    sb(t3, sp, 0x9A);
                    link(ctx, 0x519EB8u);  // $ra first: the delay slot below depends on it
                    sb(t0, sp, 0x99);
                    call(ctx, gen::fn__SetEntryByPos_00517310);
                    ld(ra, sp, 0x2D0);
                    if (v0 == 0) {
                        // 0x00519ec8
                        charge(ctx, 7);
                        a0 = s1;
                        jal(ctx, 0x519EC8u, gen::fn__sceMcpFlushCache_0051a498);
                        v1 = lui(0x8101);
                        v1 = v1 | 0x6F;
                        if (v0 != 0) v1 = 0;
                        v0 = v1;
                        ld(ra, sp, 0x2D0);
                    }
                } else {
                    // 0x00519df0
                    charge(ctx, 3);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x14;
                }
            }
        }
    }
    // 0x00519ee4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s2, sp, 0x2C0);
    ld(s1, sp, 0x2B0);
    ld(s0, sp, 0x2A0);
    sp = addiu(sp, 0x2E0);
}

// 0x00519EF8 _sceMcFatRename -- 380 bytes; frame 0x380: s4 sp+0x350, s1 sp+0x320, s0 sp+0x310, ra sp+0x370, s5 sp+0x360, s3 sp+0x340, s2 sp+0x330
// Rename an entry within its directory.
void _sceMcFatRename(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00519ef8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x380);
    sd(s4, sp, 0x350);
    s4 = a0;
    sd(s1, sp, 0x320);
    sd(s0, sp, 0x310);
    s1 = a2;
    s0 = a1;
    sd(ra, sp, 0x370);
    sd(s5, sp, 0x360);
    sd(s3, sp, 0x340);
    link(ctx, 0x519F20u);  // $ra first: the delay slot below depends on it
    sd(s2, sp, 0x330);
    call(ctx, gen::fn__ConfInsert_00516b48);
    ld(ra, sp, 0x370);
    if (v0 == 0) {
        // 0x00519f30
        charge(ctx, 7);
        s5 = addiu(sp, 0x200);
        a1 = s0;
        a0 = s4;
        a2 = s5;
        jal(ctx, 0x519F3Cu, gen::fn__CheckFileDescript_00516be8);
        ld(ra, sp, 0x370);
        if (v0 == 0) {
            // 0x00519f4c
            charge(ctx, 5);
            a0 = s1;
            a1 = 47;
            jal(ctx, 0x519F50u, gen::fn_strchr_00523f98);
            s0 = addiu(sp, 0x280);
            if (v0 == 0) {
                // 0x00519f60
                charge(ctx, 13);
                a1 = s5;
                a0 = s0;
                jal(ctx, 0x519F64u, gen::fn_strcpy_00524270);
                a0 = s0;
                a1 = 47;
                jal(ctx, 0x519F70u, gen::fn_strrchr_005249e8);
                a0 = addiu(v0, 1);
                a1 = s1;
                jal(ctx, 0x519F7Cu, gen::fn_strcpy_00524270);
                a0 = s1;
                jal(ctx, 0x519F84u, gen::fn_isCorrFname_00514e20);
                if (v0 == 0) {
                    goto L_00519f94;
                }
                // 0x00519fa0
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x519FA0u, gen::fn_isCorrNameSize_00514db0);
                s2 = addiu(sp, 0x300);
                if (v0 == 0) {
                    // 0x00519fb0
                    charge(ctx, 3);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x5B;
                    goto L_0051a050;
                }
                // 0x00519fbc
                charge(ctx, 11);
                s3 = addiu(sp, 0x304);
                a1 = s0;
                a0 = s4;
                a2 = sp;
                a3 = s2;
                t0 = s3;
                jal(ctx, 0x519FD0u, gen::fn__SearchFile_00516ec0);
                v1 = lui(0x8101);
                v1 = v1 | 0x2;
                ld(ra, sp, 0x370);
                if (v0 == v1) {
                    // 0x00519fe8
                    charge(ctx, 10);
                    a1 = s5;
                    a3 = s2;
                    t0 = s3;
                    a0 = s4;
                    a2 = sp;
                    jal(ctx, 0x519FF8u, gen::fn__SearchFile_00516ec0);
                    v1 = lui(0x8101);
                    v1 = v1 | 0x11;
                    ld(ra, sp, 0x370);
                    if (v0 == v1) {
                        // 0x0051a010
                        charge(ctx, 10);
                        a1 = s1;
                        a0 = addiu(sp, 0x40);
                        jal(ctx, 0x51A014u, gen::fn_strcpy_00524270);
                        lw(a2, sp, 0x300);
                        a0 = s4;
                        lw(a3, sp, 0x304);
                        a1 = sp;
                        jal(ctx, 0x51A028u, gen::fn__SetEntryByPos_00517310);
                        ld(ra, sp, 0x370);
                        if (v0 == 0) {
                            // 0x0051a038
                            charge(ctx, 6);
                            a0 = s4;
                            jal(ctx, 0x51A038u, gen::fn__sceMcpFlushCache_0051a498);
                            v1 = lui(0x8101);
                            v1 = v1 | 0x6F;
                            if (v0 != 0) v1 = 0;
                            v0 = v1;
                        L_0051a050:
                            charge(ctx, 1);
                            ld(ra, sp, 0x370);
                        }
                    }
                }
                // 0x0051a054 (the shared epilogue, written out on this path)
                charge(ctx, 8);
                ld(s5, sp, 0x360);
                ld(s4, sp, 0x350);
                ld(s3, sp, 0x340);
                ld(s2, sp, 0x330);
                ld(s1, sp, 0x320);
                ld(s0, sp, 0x310);
                sp = addiu(sp, 0x380);
                return;
            }
        L_00519f94:
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x16;
            goto L_0051a050;
        }
    }
    // 0x0051a054 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s5, sp, 0x360);
    ld(s4, sp, 0x350);
    ld(s3, sp, 0x340);
    ld(s2, sp, 0x330);
    ld(s1, sp, 0x320);
    ld(s0, sp, 0x310);
    sp = addiu(sp, 0x380);
}

// 0x0051A078 _sceMcFatGetEntSpace -- 196 bytes; frame 0x2D0: s1 sp+0x2A0, s2 sp+0x2B0, ra sp+0x2C0, s0 sp+0x290
// The free entries of a directory.
void _sceMcFatGetEntSpace(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051a078
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2D0);
    sd(s1, sp, 0x2A0);
    sd(s2, sp, 0x2B0);
    s1 = a0;
    sd(ra, sp, 0x2C0);
    s2 = a1;
    link(ctx, 0x51A090u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x290);
    call(ctx, gen::fn__ConfInsert_00516b48);
    v1 = v0;
    sw(v0, sp, 0x280);
    if (v1 == 0) {
        // 0x0051a0a4
        charge(ctx, 8);
        s0 = addiu(sp, 0x200);
        a1 = s2;
        a0 = s1;
        a2 = s0;
        jal(ctx, 0x51A0B0u, gen::fn__CheckFileDescript_00516be8);
        v1 = v0;
        sw(v0, sp, 0x280);
        if (v1 == 0) {
            // 0x0051a0c4
            charge(ctx, 11);
            a1 = s0;
            a0 = s1;
            a2 = sp;
            a3 = 0;
            t0 = 0;
            jal(ctx, 0x51A0D4u, gen::fn__SearchFile_00516ec0);
            v1 = lui(0x8101);
            a0 = v0;
            v1 = v1 | 0x11;
            sw(v0, sp, 0x280);
            if (a0 == v1) {
                // 0x0051a0f0
                charge(ctx, 4);
                lhu(v0, sp, 0x0);
                v0 = v0 & 0x20;
                lw(a1, sp, 0x10);
                if (v0 != 0) {
                    // 0x0051a10c
                    charge(ctx, 6);
                    a0 = s1;
                    lw(a2, sp, 0x4);
                    a3 = addiu(sp, 0x280);
                    jal(ctx, 0x51A114u, gen::fn__GetFreeEntrySize_005174b8);
                    lw(v1, sp, 0x280);
                    if (v1 != 0) v0 = v1;
                } else {
                    // 0x0051a100
                    charge(ctx, 3);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x14;
                }
            }
        }
    }
    // 0x0051a124 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x2C0);
    ld(s2, sp, 0x2B0);
    ld(s1, sp, 0x2A0);
    ld(s0, sp, 0x290);
    sp = addiu(sp, 0x2D0);
}

}  // namespace p3fes::game
