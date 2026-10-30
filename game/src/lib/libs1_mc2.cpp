// libmc2's cluster cache, socket helpers and blocking API (0x5130E8-0x51C330): the per-port write-cluster cache
// (libs1::mc2::kClustCache: a run of up to 16 consecutive clusters of one erase block), the superblock page reads /
// writes, the bad-block checks, the core layer's small socket helpers, and the blocking sceMc2* calls (the async request
// followed by sceMc2Sync2, both still recompiled: they wait on kernel semaphores).
//
// Every body is p3fes_handgen's (register for register and block for block as the recompiled body: frame, spills,
// $ra links, cycle charges, check points); the readability pass (scratch spec.py, checked by check.py) adds the
// role comments and the named offsets of game/include/p3fes/game/libs1_mc2.h, each equal to the literal it replaces.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs1_mc2.h"

namespace p3fes::recomp_gen {
void fn__sceMcCoreAuthentication_0051b3b0(p3fes::EEContext&);
void fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8(p3fes::EEContext&);
void fn__sceMcCoreChangeSocketTypeMc2Dbc_0051c330(p3fes::EEContext&);
void fn__sceMcCoreCheckNewCard_0051b1b0(p3fes::EEContext&);
void fn__sceMcCoreCheckSocket_0051c250(p3fes::EEContext&);
void fn__sceMcCoreCreateSocket_0051c130(p3fes::EEContext&);
void fn__sceMcCoreDeleteSocket_0051c280(p3fes::EEContext&);
void fn__sceMcCoreGetCardSpec_0051afd8(p3fes::EEContext&);
void fn__sceMcCoreReadPage2_0051b708(p3fes::EEContext&);
void fn__sceMcCoreReadPageFast_0051bd10(p3fes::EEContext&);
void fn__sceMcCoreReadPage_0051b8d0(p3fes::EEContext&);
void fn__sceMcCoreSetCardSpec_0051af98(p3fes::EEContext&);
void fn__sceMcCoreSetWriteBackHole_0051af70(p3fes::EEContext&);
void fn__sceMcCoreWritePageFast_0051bf40(p3fes::EEContext&);
void fn__sceMcCoreWritePage_0051b8f0(p3fes::EEContext&);
void fn__sceMcFatInit2_00515400(p3fes::EEContext&);
void fn__sceMcpAuthentication_0051a1c0(p3fes::EEContext&);
void fn__sceMcpCheckNewCard_0051a1a0(p3fes::EEContext&);
void fn__sceMcpFlushCache_0051a498(p3fes::EEContext&);
void fn__sceMcpGetCardSpec_0051a180(p3fes::EEContext&);
void fn__sceMcpInit_0051a140(p3fes::EEContext&);
void fn__sceMcpIsSpeckOutBlock_0051ab08(p3fes::EEContext&);
void fn__sceMcpIsSpeckOutClust_0051ab50(p3fes::EEContext&);
void fn__sceMcpMakeSpecoutBlock_0051ab98(p3fes::EEContext&);
void fn__sceMcpReadClust_0051a418(p3fes::EEContext&);
void fn__sceMcpReadSysInfo_0051a1e0(p3fes::EEContext&);
void fn__sceMcpReadUserClustFast_0051aa00(p3fes::EEContext&);
void fn__sceMcpReadUserClustOnCache_0051a8a0(p3fes::EEContext&);
void fn__sceMcpReadUserClust_0051a9e0(p3fes::EEContext&);
void fn__sceMcpWriteClust_0051a458(p3fes::EEContext&);
void fn__sceMcpWriteSysInfo_0051a2f8(p3fes::EEContext&);
void fn__sceMcpWriteUserClustFast_0051aa48(p3fes::EEContext&);
void fn__sceMcpWriteUserClustOnCache_0051a508(p3fes::EEContext&);
void fn__sceMcpWriteUserClust_0051aa90(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sceMc2ChdirAsync_005141f0(p3fes::EEContext&);
void fn_sceMc2Chdir_00514c10(p3fes::EEContext&);
void fn_sceMc2ChmodAsync_005142f0(p3fes::EEContext&);
void fn_sceMc2Chmod_00514c90(p3fes::EEContext&);
void fn_sceMc2CreateFileAsync_00513de8(p3fes::EEContext&);
void fn_sceMc2CreateFile_00514b10(p3fes::EEContext&);
void fn_sceMc2DeleteAsync_00513ee0(p3fes::EEContext&);
void fn_sceMc2DeleteSocket_005133f8(p3fes::EEContext&);
void fn_sceMc2Delete_00514b50(p3fes::EEContext&);
void fn_sceMc2FormatAsync_00513598(p3fes::EEContext&);
void fn_sceMc2Format_00514990(p3fes::EEContext&);
void fn_sceMc2GetDirAsync_00513fc8(p3fes::EEContext&);
void fn_sceMc2GetDir_00514c50(p3fes::EEContext&);
void fn_sceMc2GetEntSpaceAsync_00514510(p3fes::EEContext&);
void fn_sceMc2GetEntSpace_00514d10(p3fes::EEContext&);
void fn_sceMc2GetInfoAsync_005136f8(p3fes::EEContext&);
void fn_sceMc2GetInfo_00514950(p3fes::EEContext&);
void fn_sceMc2MkdirAsync_005140f8(p3fes::EEContext&);
void fn_sceMc2Mkdir_00514bd0(p3fes::EEContext&);
void fn_sceMc2ReadFastFileAsync_00513a88(p3fes::EEContext&);
void fn_sceMc2ReadFastFile_00514a90(p3fes::EEContext&);
void fn_sceMc2ReadFileAsync_00513968(p3fes::EEContext&);
void fn_sceMc2ReadFile_00514a10(p3fes::EEContext&);
void fn_sceMc2RenameAsync_005143f0(p3fes::EEContext&);
void fn_sceMc2Rename_00514b90(p3fes::EEContext&);
void fn_sceMc2SearchFileAsync_005137b8(p3fes::EEContext&);
void fn_sceMc2SearchFile_00514cd0(p3fes::EEContext&);
void fn_sceMc2Sync2_00514858(p3fes::EEContext&);
void fn_sceMc2Sync_00514928(p3fes::EEContext&);
void fn_sceMc2UnformatAsync_00513648(p3fes::EEContext&);
void fn_sceMc2Unformat_005149d0(p3fes::EEContext&);
void fn_sceMc2WriteFastFileAsync_00513ba8(p3fes::EEContext&);
void fn_sceMc2WriteFastFile_00514ad0(p3fes::EEContext&);
void fn_sceMc2WriteFileAsync_00513cc8(p3fes::EEContext&);
void fn_sceMc2WriteFile_00514a50(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x005133F8 sceMc2DeleteSocket -- 124 bytes; frame 0x10: ra sp+0x0
// Close a card socket (refused while a request runs).
void sceMc2DeleteSocket(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005133f8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x513400u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
    a0 = v0;
    if (i64(a0) >= 0) {
        v0 = 0x780000;
        // 0x00513420
        charge(ctx, 3);
        lw(v1, v0, 10200);
        if (v1 != 0) {
            v0 = 0x970000;
            // 0x00513438
            charge(ctx, 3);
            lw(v1, v0, -3772);
            if (v1 == 0) {
                // 0x00513450
                charge(ctx, 6);
                jal(ctx, 0x513450u, gen::fn__sceMcCoreDeleteSocket_0051c280);
                v1 = lui(0x8101);
                v1 = v1 | 0x8002;
                if (v0 != 0) v1 = 0;
                v0 = v1;
            } else {
                // 0x00513444
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x10;
            }
        } else {
            // 0x0051342c
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8001;
        }
    } else {
        // 0x00513414
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8002;
    }
    // 0x00513468 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00514928 sceMc2Sync -- 36 bytes; frame 0x10: ra sp+0x0
// Wait for the running request (sceMc2Sync2 mode 0).
void sceMc2Sync(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514928
    enter(ctx, 9);  // entry check point + this block's cycles
    a2 = a1;
    sp = addiu(sp, -0x10);
    a1 = a0;
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x514938u, gen::fn_sceMc2Sync2_00514858);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00514950 sceMc2GetInfo -- 60 bytes; frame 0x20: ra sp+0x10
// Blocking card information: the async request, then a wait for its result.
void sceMc2GetInfo(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514950
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    jal(ctx, 0x514958u, gen::fn_sceMc2GetInfoAsync_005136f8);
    v1 = v0;
    sw(v0, sp, 0x0);
    if (v1 == 0) {
        // 0x0051496c
        charge(ctx, 5);
        a0 = 0;
        a1 = 0;
        a2 = sp;
        jal(ctx, 0x514974u, gen::fn_sceMc2Sync2_00514858);
        lw(v0, sp, 0x0);
    }
    // 0x00514980 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00514990 sceMc2Format -- 60 bytes; frame 0x20: ra sp+0x10
// Blocking format.
void sceMc2Format(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514990
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    jal(ctx, 0x514998u, gen::fn_sceMc2FormatAsync_00513598);
    v1 = v0;
    sw(v0, sp, 0x0);
    if (v1 == 0) {
        // 0x005149ac
        charge(ctx, 5);
        a0 = 0;
        a1 = 0;
        a2 = sp;
        jal(ctx, 0x5149B4u, gen::fn_sceMc2Sync2_00514858);
        lw(v0, sp, 0x0);
    }
    // 0x005149c0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005149D0 sceMc2Unformat -- 60 bytes; frame 0x20: ra sp+0x10
// Blocking unformat.
void sceMc2Unformat(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005149d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    jal(ctx, 0x5149D8u, gen::fn_sceMc2UnformatAsync_00513648);
    v1 = v0;
    sw(v0, sp, 0x0);
    if (v1 == 0) {
        // 0x005149ec
        charge(ctx, 5);
        a0 = 0;
        a1 = 0;
        a2 = sp;
        jal(ctx, 0x5149F4u, gen::fn_sceMc2Sync2_00514858);
        lw(v0, sp, 0x0);
    }
    // 0x00514a00 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00514A10 sceMc2ReadFile -- 60 bytes; frame 0x20: ra sp+0x10
// Blocking file read.
void sceMc2ReadFile(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514a10
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    jal(ctx, 0x514A18u, gen::fn_sceMc2ReadFileAsync_00513968);
    v1 = v0;
    sw(v0, sp, 0x0);
    if (v1 == 0) {
        // 0x00514a2c
        charge(ctx, 5);
        a0 = 0;
        a1 = 0;
        a2 = sp;
        jal(ctx, 0x514A34u, gen::fn_sceMc2Sync2_00514858);
        lw(v0, sp, 0x0);
    }
    // 0x00514a40 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00514A50 sceMc2WriteFile -- 60 bytes; frame 0x20: ra sp+0x10
// Blocking file write.
void sceMc2WriteFile(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514a50
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    jal(ctx, 0x514A58u, gen::fn_sceMc2WriteFileAsync_00513cc8);
    v1 = v0;
    sw(v0, sp, 0x0);
    if (v1 == 0) {
        // 0x00514a6c
        charge(ctx, 5);
        a0 = 0;
        a1 = 0;
        a2 = sp;
        jal(ctx, 0x514A74u, gen::fn_sceMc2Sync2_00514858);
        lw(v0, sp, 0x0);
    }
    // 0x00514a80 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00514A90 sceMc2ReadFastFile -- 60 bytes; frame 0x20: ra sp+0x10
// Blocking fast file read.
void sceMc2ReadFastFile(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514a90
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    jal(ctx, 0x514A98u, gen::fn_sceMc2ReadFastFileAsync_00513a88);
    v1 = v0;
    sw(v0, sp, 0x0);
    if (v1 == 0) {
        // 0x00514aac
        charge(ctx, 5);
        a0 = 0;
        a1 = 0;
        a2 = sp;
        jal(ctx, 0x514AB4u, gen::fn_sceMc2Sync2_00514858);
        lw(v0, sp, 0x0);
    }
    // 0x00514ac0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00514AD0 sceMc2WriteFastFile -- 60 bytes; frame 0x20: ra sp+0x10
// Blocking fast file write.
void sceMc2WriteFastFile(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514ad0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    jal(ctx, 0x514AD8u, gen::fn_sceMc2WriteFastFileAsync_00513ba8);
    v1 = v0;
    sw(v0, sp, 0x0);
    if (v1 == 0) {
        // 0x00514aec
        charge(ctx, 5);
        a0 = 0;
        a1 = 0;
        a2 = sp;
        jal(ctx, 0x514AF4u, gen::fn_sceMc2Sync2_00514858);
        lw(v0, sp, 0x0);
    }
    // 0x00514b00 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00514B10 sceMc2CreateFile -- 60 bytes; frame 0x20: ra sp+0x10
// Blocking create.
void sceMc2CreateFile(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514b10
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    jal(ctx, 0x514B18u, gen::fn_sceMc2CreateFileAsync_00513de8);
    v1 = v0;
    sw(v0, sp, 0x0);
    if (v1 == 0) {
        // 0x00514b2c
        charge(ctx, 5);
        a0 = 0;
        a1 = 0;
        a2 = sp;
        jal(ctx, 0x514B34u, gen::fn_sceMc2Sync2_00514858);
        lw(v0, sp, 0x0);
    }
    // 0x00514b40 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00514B50 sceMc2Delete -- 60 bytes; frame 0x20: ra sp+0x10
// Blocking delete.
void sceMc2Delete(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514b50
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    jal(ctx, 0x514B58u, gen::fn_sceMc2DeleteAsync_00513ee0);
    v1 = v0;
    sw(v0, sp, 0x0);
    if (v1 == 0) {
        // 0x00514b6c
        charge(ctx, 5);
        a0 = 0;
        a1 = 0;
        a2 = sp;
        jal(ctx, 0x514B74u, gen::fn_sceMc2Sync2_00514858);
        lw(v0, sp, 0x0);
    }
    // 0x00514b80 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00514B90 sceMc2Rename -- 60 bytes; frame 0x20: ra sp+0x10
// Blocking rename.
void sceMc2Rename(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514b90
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    jal(ctx, 0x514B98u, gen::fn_sceMc2RenameAsync_005143f0);
    v1 = v0;
    sw(v0, sp, 0x0);
    if (v1 == 0) {
        // 0x00514bac
        charge(ctx, 5);
        a0 = 0;
        a1 = 0;
        a2 = sp;
        jal(ctx, 0x514BB4u, gen::fn_sceMc2Sync2_00514858);
        lw(v0, sp, 0x0);
    }
    // 0x00514bc0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00514BD0 sceMc2Mkdir -- 60 bytes; frame 0x20: ra sp+0x10
// Blocking make-directory.
void sceMc2Mkdir(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514bd0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    jal(ctx, 0x514BD8u, gen::fn_sceMc2MkdirAsync_005140f8);
    v1 = v0;
    sw(v0, sp, 0x0);
    if (v1 == 0) {
        // 0x00514bec
        charge(ctx, 5);
        a0 = 0;
        a1 = 0;
        a2 = sp;
        jal(ctx, 0x514BF4u, gen::fn_sceMc2Sync2_00514858);
        lw(v0, sp, 0x0);
    }
    // 0x00514c00 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00514C10 sceMc2Chdir -- 60 bytes; frame 0x20: ra sp+0x10
// Blocking change-directory.
void sceMc2Chdir(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514c10
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    jal(ctx, 0x514C18u, gen::fn_sceMc2ChdirAsync_005141f0);
    v1 = v0;
    sw(v0, sp, 0x0);
    if (v1 == 0) {
        // 0x00514c2c
        charge(ctx, 5);
        a0 = 0;
        a1 = 0;
        a2 = sp;
        jal(ctx, 0x514C34u, gen::fn_sceMc2Sync2_00514858);
        lw(v0, sp, 0x0);
    }
    // 0x00514c40 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00514C50 sceMc2GetDir -- 60 bytes; frame 0x20: ra sp+0x10
// Blocking directory listing.
void sceMc2GetDir(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514c50
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    jal(ctx, 0x514C58u, gen::fn_sceMc2GetDirAsync_00513fc8);
    v1 = v0;
    sw(v0, sp, 0x0);
    if (v1 == 0) {
        // 0x00514c6c
        charge(ctx, 5);
        a0 = 0;
        a1 = 0;
        a2 = sp;
        jal(ctx, 0x514C74u, gen::fn_sceMc2Sync2_00514858);
        lw(v0, sp, 0x0);
    }
    // 0x00514c80 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00514C90 sceMc2Chmod -- 60 bytes; frame 0x20: ra sp+0x10
// Blocking attribute change.
void sceMc2Chmod(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514c90
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    a2 = a2 & 0xFFFF;
    jal(ctx, 0x514C98u, gen::fn_sceMc2ChmodAsync_005142f0);
    v1 = v0;
    sw(v0, sp, 0x0);
    if (v1 == 0) {
        // 0x00514cac
        charge(ctx, 5);
        a0 = 0;
        a1 = 0;
        a2 = sp;
        jal(ctx, 0x514CB4u, gen::fn_sceMc2Sync2_00514858);
        lw(v0, sp, 0x0);
    }
    // 0x00514cc0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00514CD0 sceMc2SearchFile -- 60 bytes; frame 0x20: ra sp+0x10
// Blocking file look-up.
void sceMc2SearchFile(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514cd0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    jal(ctx, 0x514CD8u, gen::fn_sceMc2SearchFileAsync_005137b8);
    v1 = v0;
    sw(v0, sp, 0x0);
    if (v1 == 0) {
        // 0x00514cec
        charge(ctx, 5);
        a0 = 0;
        a1 = 0;
        a2 = sp;
        jal(ctx, 0x514CF4u, gen::fn_sceMc2Sync2_00514858);
        lw(v0, sp, 0x0);
    }
    // 0x00514d00 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00514D10 sceMc2GetEntSpace -- 60 bytes; frame 0x20: ra sp+0x10
// Blocking free-entry query.
void sceMc2GetEntSpace(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514d10
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    jal(ctx, 0x514D18u, gen::fn_sceMc2GetEntSpaceAsync_00514510);
    v1 = v0;
    sw(v0, sp, 0x0);
    if (v1 == 0) {
        // 0x00514d2c
        charge(ctx, 5);
        a0 = 0;
        a1 = 0;
        a2 = sp;
        jal(ctx, 0x514D34u, gen::fn_sceMc2Sync2_00514858);
        lw(v0, sp, 0x0);
    }
    // 0x00514d40 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0051A140 _sceMcpInit -- 60 bytes; leaf frame (no stack)
// Empty both ports' write-cluster caches (first cluster -1, count 0).
void _sceMcpInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0051a140
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x980000;
    v1 = 0x8020;
    a0 = addiu(v0, -13120);  // &0x97CCC0
    a1 = si(-1);
    v1 = addu(a0, v1);
    for (;;) {
        // 0x0051a158
        charge(ctx, 7);
        sw(a1, a0, 0);
        sw(zero, a0, 12);
        a0 = addiu(a0, 16400);
        v0 = slt(a0, v1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0051a174
    charge(ctx, 2);
    v0 = 1;
}

// 0x0051A180 _sceMcpGetCardSpec -- 28 bytes; frame 0x10: ra sp+0x0
// The card geometry from the core layer (_sceMcCoreGetCardSpec).
void _sceMcpGetCardSpec(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0051a180
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x51A188u, gen::fn__sceMcCoreGetCardSpec_0051afd8);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0051A1A0 _sceMcpCheckNewCard -- 28 bytes; frame 0x10: ra sp+0x0
// Whether the card was changed (_sceMcCoreCheckNewCard).
void _sceMcpCheckNewCard(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0051a1a0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x51A1A8u, gen::fn__sceMcCoreCheckNewCard_0051b1b0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0051A1C0 _sceMcpAuthentication -- 28 bytes; frame 0x10: ra sp+0x0
// Authenticate the card (_sceMcCoreAuthentication).
void _sceMcpAuthentication(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0051a1c0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x51A1C8u, gen::fn__sceMcCoreAuthentication_0051b3b0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0051A1E0 _sceMcpReadSysInfo -- 276 bytes; frame 0x30: s1 sp+0x10, s0 sp+0x0, ra sp+0x20
// Read page 0 (the superblock) into 0x984D00 and copy its first 388 bytes to the port's superblock copy.
void _sceMcpReadSysInfo(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051a1e0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x980000;
    sd(s1, sp, 0x10);
    a2 = 0;
    sd(s0, sp, 0x0);
    s1 = addiu(v0, 19712);  // &0x984D00
    s0 = a0;
    sd(ra, sp, 0x20);
    a1 = s1;
    a3 = 1;
    t0 = 0;
    jal(ctx, 0x51A208u, gen::fn__sceMcCoreReadPage2_0051b708);
    a0 = 388;
    if (v0 != 0) {
        // 0x0051a220
        charge(ctx, 9);
        v1 = 0x780000;
        mult(a0, s0, a0);
        v1 = addiu(v1, 10208);  // &0x7827E0
        a1 = s1;
        a0 = addu(a0, v1);
        v0 = a0 | a1;
        v0 = v0 & 0x7;
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = addiu(a1, 384);
        if (cc) {
            for (;;) {
                // 0x0051a2a0
                charge(ctx, 13);
                ld(v1, a1, 0);
                ld(a2, a1, 8);
                ld(a3, a1, 16);
                ld(t0, a1, 24);
                sd(v1, a0, 0);
                sd(a2, a0, 8);
                sd(a3, a0, 16);
                sd(t0, a0, 24);
                a1 = addiu(a1, 32);
                a0 = addiu(a0, 32);
                if (a1 == v0) {
                    break;
                }
                backedge(ctx);
            }
        } else {
            for (;;) {
                // 0x0051a244
                charge(ctx, 21);
                ldl(v1, a1, 7);
                ldr(v1, a1, 0);
                ldl(a2, a1, 15);
                ldr(a2, a1, 8);
                ldl(a3, a1, 23);
                ldr(a3, a1, 16);
                ldl(t0, a1, 31);
                ldr(t0, a1, 24);
                sdl(v1, a0, 7);
                sdr(v1, a0, 0);
                sdl(a2, a0, 15);
                sdr(a2, a0, 8);
                sdl(a3, a0, 23);
                sdr(a3, a0, 16);
                sdl(t0, a0, 31);
                sdr(t0, a0, 24);
                a1 = addiu(a1, 32);
                a0 = addiu(a0, 32);
                if (a1 == v0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0051a298
            charge(ctx, 2);
        }
        // 0x0051a2d4
        charge(ctx, 3);
        lw(v0, a1, 0);
        sw(v0, a0, 0);
        v0 = 1;
    } else {
        // 0x0051a218
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0051a2e0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0051A2F8 _sceMcpWriteSysInfo -- 284 bytes; frame 0x40: s2 sp+0x20, s1 sp+0x10, s0 sp+0x0, ra sp+0x30
// Write the port's superblock copy to page 0 (padded with 0xFF).
void _sceMcpWriteSysInfo(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051a2f8
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a1 = 255;
    sd(s2, sp, 0x20);
    a2 = 2048;
    sd(s1, sp, 0x10);
    s2 = 0x980000;
    sd(s0, sp, 0x0);
    s1 = a0;
    s0 = addiu(s2, 19712);  // &0x984D00
    sd(ra, sp, 0x30);
    a0 = s0;
    jal(ctx, 0x51A320u, gen::fn_memset_00521408);
    a0 = 388;
    v1 = 0x780000;
    mult(a0, s1, a0);
    v1 = addiu(v1, 10208);  // &0x7827E0
    v1 = addu(a0, v1);
    v0 = v1 | s0;
    v0 = v0 & 0x7;
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = addiu(v1, 384);
    if (cc) {
        for (;;) {
            // 0x0051a3a8
            charge(ctx, 13);
            ld(t0, v1, 0);
            ld(t1, v1, 8);
            ld(t2, v1, 16);
            ld(a0, v1, 24);
            sd(t0, s0, 0);
            sd(t1, s0, 8);
            sd(t2, s0, 16);
            sd(a0, s0, 24);
            v1 = addiu(v1, 32);
            s0 = addiu(s0, 32);
            if (v1 == v0) {
                break;
            }
            backedge(ctx);
        }
    } else {
        for (;;) {
            // 0x0051a34c
            charge(ctx, 21);
            ldl(a0, v1, 7);
            ldr(a0, v1, 0);
            ldl(a1, v1, 15);
            ldr(a1, v1, 8);
            ldl(a2, v1, 23);
            ldr(a2, v1, 16);
            ldl(a3, v1, 31);
            ldr(a3, v1, 24);
            sdl(a0, s0, 7);
            sdr(a0, s0, 0);
            sdl(a1, s0, 15);
            sdr(a1, s0, 8);
            sdl(a2, s0, 23);
            sdr(a2, s0, 16);
            sdl(a3, s0, 31);
            sdr(a3, s0, 24);
            v1 = addiu(v1, 32);
            s0 = addiu(s0, 32);
            if (v1 == v0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0051a3a0
        charge(ctx, 2);
    }
    // 0x0051a3dc
    charge(ctx, 14);
    lw(t0, v1, 0);
    a0 = s1;
    a1 = addiu(s2, 19712);
    sw(t0, s0, 0);
    a2 = 0;
    a3 = 1;
    jal(ctx, 0x51A3F0u, gen::fn__sceMcCoreWritePage_0051b8f0);
    ld(ra, sp, 0x30);
    v0 = sltu(0, v0);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0051A418 _sceMcpReadClust -- 64 bytes; frame 0x10: ra sp+0x0
// Read N card clusters (clusters x pages per cluster) through _sceMcCoreReadPage.
void _sceMcpReadClust(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051a418
    enter(ctx, 16);  // entry check point + this block's cycles
    v1 = 388;
    sp = addiu(sp, -0x10);
    mult(v1, a0, v1);
    v0 = 0x780000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 10208);  // &0x7827E0
    v1 = addu(v1, v0);
    lhu(t0, v1, 42);
    mult(zero, t0, a3);
    mflo(a3);
    mult(zero, a2, t0);
    mflo(a2);
    jal(ctx, 0x51A444u, gen::fn__sceMcCoreReadPage_0051b8d0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0051A458 _sceMcpWriteClust -- 64 bytes; frame 0x10: ra sp+0x0
// Write N card clusters through _sceMcCoreWritePage.
void _sceMcpWriteClust(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051a458
    enter(ctx, 16);  // entry check point + this block's cycles
    v1 = 388;
    sp = addiu(sp, -0x10);
    mult(v1, a0, v1);
    v0 = 0x780000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 10208);  // &0x7827E0
    v1 = addu(v1, v0);
    lhu(t0, v1, 42);
    mult(zero, t0, a3);
    mflo(a3);
    mult(zero, a2, t0);
    mflo(a2);
    jal(ctx, 0x51A484u, gen::fn__sceMcCoreWritePage_0051b8f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0051A498 _sceMcpFlushCache -- 112 bytes; frame 0x40: s2 sp+0x20, s1 sp+0x10, ra sp+0x30, s0 sp+0x0
// Write the cached run of user clusters back and empty the cache.
void _sceMcpFlushCache(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051a498
    enter(ctx, 14);  // entry check point + this block's cycles
    v0 = 16400;
    sp = addiu(sp, -0x40);
    mult(a3, a0, v0);
    v1 = 0x980000;
    sd(s2, sp, 0x20);
    v1 = addiu(v1, -13120);  // &0x97CCC0
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x30);
    s2 = si(-1);
    sd(s0, sp, 0x0);
    s1 = addu(a3, v1);
    lw(a2, s1, 0);
    v0 = 1;
    if (a2 != s2) {
        // 0x0051a4d0
        charge(ctx, 8);
        s0 = addiu(v1, 12);
        a1 = addiu(v1, 16);
        s0 = addu(a3, s0);
        a1 = addu(a3, a1);
        link(ctx, 0x51A4E0u);  // $ra first: the delay slot below depends on it
        lw(a3, s0, 0);
        call(ctx, gen::fn__sceMcpWriteClust_0051a458);
        sw(s2, s1, 0);
        sw(zero, s0, 0);
    }
    // 0x0051a4f0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0051A508 _sceMcpWriteUserClustOnCache -- 916 bytes; frame 0x60: s3 sp+0x30, s4 sp+0x40, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0, ra sp+0x50
// Queue one user cluster in the write cache: starts a run, appends a consecutive cluster of the same erase block (up
// to 16), or flushes and starts over.
void _sceMcpWriteUserClustOnCache(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051a508
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v1 = 388;
    sd(s3, sp, 0x30);
    v0 = 16400;
    s3 = a0;
    sd(s4, sp, 0x40);
    mult(v1, s3, v1);
    a0 = 0x780000;
    sd(s2, sp, 0x20);
    a0 = addiu(a0, 10208);  // &0x7827E0
    sd(s1, sp, 0x10);
    mult(t0, s3, v0);
    sd(s0, sp, 0x0);
    s1 = a1;
    sd(ra, sp, 0x50);
    v1 = addu(v1, a0);
    s4 = 0x980000;
    a3 = si(-1);
    lw(a1, v1, 52);
    t1 = addiu(s4, -13120);  // &0x97CCC0
    lhu(a0, v1, 42);
    t2 = addu(t0, t1);
    s0 = addu(a2, a1);
    lhu(v0, v1, 44);
    mult(a0, s0, a0);
    if (v0 == 0) {
        brk(ctx, 0x51A570u, 0x7u);
    }
    // 0x0051a574
    charge(ctx, 5);
    lw(v1, t2, 0);
    div(a0, v0);
    mflo(s2);
    if (v1 != a3) {
        v1 = addiu(t1, 4);
        // 0x0051a668
        charge(ctx, 5);
        a1 = addu(t0, v1);
        lw(v0, a1, 0);
        v0 = addiu(v0, 1);
        v1 = addiu(t1, 12);
        if (s0 == v0) {
            // 0x0051a67c
            charge(ctx, 5);
            a0 = addu(t0, v1);
            lw(v0, a0, 0);
            v0 = slti(v0, 16);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addu(t1, t0);
            if (cc) {
                goto L_0051a770;
            }
            // 0x0051a690
            charge(ctx, 3);
            lw(v1, v0, 8);
            v0 = addiu(t1, 16);
            if (v1 != s2) {
                goto L_0051a770;
            }
            // 0x0051a69c
            charge(ctx, 9);
            sw(s0, a1, 0);
            lw(v1, a0, 0);
            v1 = sll(v1, 10);
            v1 = addu(t0, v1);
            v0 = addu(v1, v0);
            a0 = s1 | v0;
            a0 = a0 & 0x7;
            a2 = s1;
            if (a0 == 0) {
                // 0x0051a720
                charge(ctx, 1);
                a0 = addiu(s1, 1024);
                for (;;) {
                    // 0x0051a724
                    charge(ctx, 13);
                    ld(a3, a2, 0);
                    ld(t0, a2, 8);
                    ld(t1, a2, 16);
                    ld(v1, a2, 24);
                    sd(a3, v0, 0);
                    sd(t0, v0, 8);
                    sd(t1, v0, 16);
                    sd(v1, v0, 24);
                    a2 = addiu(a2, 32);
                    v0 = addiu(v0, 32);
                    if (a2 == a0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0051a758
                charge(ctx, 1);
                a1 = 16400;
            } else {
                // 0x0051a6c0
                charge(ctx, 1);
                a0 = addiu(s1, 1024);
                for (;;) {
                    // 0x0051a6c4
                    charge(ctx, 21);
                    ldl(t0, a2, 7);
                    ldr(t0, a2, 0);
                    ldl(t1, a2, 15);
                    ldr(t1, a2, 8);
                    ldl(v1, a2, 23);
                    ldr(v1, a2, 16);
                    ldl(a1, a2, 31);
                    ldr(a1, a2, 24);
                    sdl(t0, v0, 7);
                    sdr(t0, v0, 0);
                    sdl(t1, v0, 15);
                    sdr(t1, v0, 8);
                    sdl(v1, v0, 23);
                    sdr(v1, v0, 16);
                    sdl(a1, v0, 31);
                    sdr(a1, v0, 24);
                    a2 = addiu(a2, 32);
                    v0 = addiu(v0, 32);
                    if (a2 == a0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0051a718
                charge(ctx, 2);
                a1 = 16400;
            }
            // 0x0051a75c
            charge(ctx, 5);
            a0 = addiu(s4, -13120);
            mult(a1, s3, a1);
            a0 = addiu(a0, 12);
            v0 = 1;
            // 0x0051a86c (the shared epilogue, written out on this path)
            charge(ctx, 12);
            a1 = addu(a1, a0);
            lw(v1, a1, 0);
            v1 = addiu(v1, 1);
            sw(v1, a1, 0);
            ld(ra, sp, 0x50);
            ld(s4, sp, 0x40);
            ld(s3, sp, 0x30);
            ld(s2, sp, 0x20);
            ld(s1, sp, 0x10);
            ld(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_0051a770:
        charge(ctx, 20);
        a0 = s3;
        jal(ctx, 0x51A770u, gen::fn__sceMcpFlushCache_0051a498);
        v1 = 16400;
        a0 = addiu(s4, -13120);
        mult(v1, s3, v1);
        t0 = v0;
        a2 = addiu(a0, 16);
        a3 = s1;
        v0 = addu(v1, a0);
        a1 = addu(a0, v1);
        sw(s0, v0, 0);
        a2 = addu(v1, a2);
        v0 = a1;
        sw(s0, a1, 4);
        sw(s2, v0, 8);
        a0 = v0;
        v0 = a3 | a2;
        v0 = v0 & 0x7;
        sw(zero, a0, 12);
        if (v0 == 0) {
            // 0x0051a820
            charge(ctx, 1);
            v0 = addiu(a3, 1024);
            for (;;) {
                // 0x0051a824
                charge(ctx, 13);
                ld(a0, a3, 0);
                ld(a1, a3, 8);
                ld(t1, a3, 16);
                ld(v1, a3, 24);
                sd(a0, a2, 0);
                sd(a1, a2, 8);
                sd(t1, a2, 16);
                sd(v1, a2, 24);
                a3 = addiu(a3, 32);
                a2 = addiu(a2, 32);
                if (a3 == v0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0051a858
            charge(ctx, 1);
            a1 = 16400;
        } else {
            // 0x0051a7c0
            charge(ctx, 1);
            v0 = addiu(a3, 1024);
            for (;;) {
                // 0x0051a7c4
                charge(ctx, 21);
                ldl(a0, a3, 7);
                ldr(a0, a3, 0);
                ldl(a1, a3, 15);
                ldr(a1, a3, 8);
                ldl(t1, a3, 23);
                ldr(t1, a3, 16);
                ldl(v1, a3, 31);
                ldr(v1, a3, 24);
                sdl(a0, a2, 7);
                sdr(a0, a2, 0);
                sdl(a1, a2, 15);
                sdr(a1, a2, 8);
                sdl(t1, a2, 23);
                sdr(t1, a2, 16);
                sdl(v1, a2, 31);
                sdr(v1, a2, 24);
                a3 = addiu(a3, 32);
                a2 = addiu(a2, 32);
                if (a3 == v0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0051a818
            charge(ctx, 2);
            a1 = 16400;
        }
        // 0x0051a85c
        charge(ctx, 4);
        a0 = addiu(s4, -13120);
        mult(a1, s3, a1);
        a0 = addiu(a0, 12);
        v0 = t0;
    } else {
        // 0x0051a588
        charge(ctx, 12);
        v0 = addiu(t1, 16);
        v1 = addu(t1, t0);
        sw(s0, t2, 0);
        a2 = addu(t0, v0);
        sw(s0, v1, 4);
        v0 = v1;
        sw(s2, v0, 8);
        v0 = s1 | a2;
        sw(zero, v1, 12);
        v0 = v0 & 0x7;
        v1 = s1;
        if (v0 == 0) {
            // 0x0051a618
            charge(ctx, 1);
            v0 = addiu(s1, 1024);
            for (;;) {
                // 0x0051a61c
                charge(ctx, 13);
                ld(t1, v1, 0);
                ld(a0, v1, 8);
                ld(a1, v1, 16);
                ld(a3, v1, 24);
                sd(t1, a2, 0);
                sd(a0, a2, 8);
                sd(a1, a2, 16);
                sd(a3, a2, 24);
                v1 = addiu(v1, 32);
                a2 = addiu(a2, 32);
                if (v1 == v0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0051a650
            charge(ctx, 1);
            a1 = 16400;
        } else {
            // 0x0051a5b8
            charge(ctx, 1);
            v0 = addiu(s1, 1024);
            for (;;) {
                // 0x0051a5bc
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
            // 0x0051a610
            charge(ctx, 2);
            a1 = 16400;
        }
        // 0x0051a654
        charge(ctx, 5);
        a0 = addiu(s4, -13120);
        mult(a1, s3, a1);
        a0 = addiu(a0, 12);
        v0 = 1;
    }
    // 0x0051a86c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    a1 = addu(a1, a0);
    lw(v1, a1, 0);
    v1 = addiu(v1, 1);
    sw(v1, a1, 0);
    ld(ra, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0051A8A0 _sceMcpReadUserClustOnCache -- 320 bytes; frame 0x10: ra sp+0x0
// Read one user cluster (allocation offset added): from the write cache when it holds it, else from the card.
void _sceMcpReadUserClustOnCache(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051a8a0
    enter(ctx, 20);  // entry check point + this block's cycles
    a3 = a0;
    v0 = 16400;
    a0 = 388;
    mult(t0, a3, v0);
    mult(a0, a3, a0);
    sp = addiu(sp, -0x10);
    v1 = 0x780000;
    sd(ra, sp, 0x0);
    v0 = 0x980000;
    v1 = addiu(v1, 10208);  // &0x7827E0
    t1 = addiu(v0, -13120);  // &0x97CCC0
    t2 = a1;
    a0 = addu(a0, v1);
    v0 = addu(t0, t1);
    lw(a1, a0, 52);
    lw(a0, v0, 0);
    a2 = addu(a2, a1);
    v0 = slt(a2, a0);
    if (v0 != 0) {
        a0 = a3;
    } else {
        // 0x0051a8f0
        charge(ctx, 6);
        v1 = addu(t1, t0);
        lw(v0, v1, 12);
        v0 = addu(a0, v0);
        v0 = slt(a2, v0);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = subu(a2, a0);
        if (cc) {
            // 0x0051a9c4
            charge(ctx, 1);
            a0 = a3;
            goto L_0051a9c8;
        }
        // 0x0051a908
        charge(ctx, 9);
        a1 = t2;
        v0 = sll(v0, 10);
        a0 = addiu(t1, 16);
        v0 = addu(t0, v0);
        v0 = addu(v0, a0);
        v1 = v0 | a1;
        v1 = v1 & 0x7;
        cc = v1 == 0;  // the condition, before the delay slot changes it
        v1 = addiu(v0, 1024);
        if (cc) {
            for (;;) {
                // 0x0051a988
                charge(ctx, 13);
                ld(a0, v0, 0);
                ld(a2, v0, 8);
                ld(a3, v0, 16);
                ld(t0, v0, 24);
                sd(a0, a1, 0);
                sd(a2, a1, 8);
                sd(a3, a1, 16);
                sd(t0, a1, 24);
                v0 = addiu(v0, 32);
                a1 = addiu(a1, 32);
                if (v0 == v1) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0051a9bc
            charge(ctx, 2);
            v0 = 1;
        } else {
            for (;;) {
                // 0x0051a92c
                charge(ctx, 21);
                ldl(a0, v0, 7);
                ldr(a0, v0, 0);
                ldl(a2, v0, 15);
                ldr(a2, v0, 8);
                ldl(a3, v0, 23);
                ldr(a3, v0, 16);
                ldl(t0, v0, 31);
                ldr(t0, v0, 24);
                sdl(a0, a1, 7);
                sdr(a0, a1, 0);
                sdl(a2, a1, 15);
                sdr(a2, a1, 8);
                sdl(a3, a1, 23);
                sdr(a3, a1, 16);
                sdl(t0, a1, 31);
                sdr(t0, a1, 24);
                v0 = addiu(v0, 32);
                a1 = addiu(a1, 32);
                if (v0 == v1) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0051a980
            charge(ctx, 2);
            v0 = 1;
        }
        // 0x0051a9d4 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_0051a9c8:
    charge(ctx, 3);
    a1 = t2;
    a3 = 1;
    jal(ctx, 0x51A9CCu, gen::fn__sceMcpReadClust_0051a418);
    // 0x0051a9d4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0051A9E0 _sceMcpReadUserClust -- 28 bytes; frame 0x10: ra sp+0x0
// Read one user cluster (through the write cache).
void _sceMcpReadUserClust(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0051a9e0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x51A9E8u, gen::fn__sceMcpReadUserClustOnCache_0051a8a0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0051AA00 _sceMcpReadUserClustFast -- 72 bytes; frame 0x10: ra sp+0x0
// Read user clusters straight from the card (_sceMcCoreReadPageFast).
void _sceMcpReadUserClustFast(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051aa00
    enter(ctx, 18);  // entry check point + this block's cycles
    v1 = 388;
    sp = addiu(sp, -0x10);
    mult(v1, a0, v1);
    v0 = 0x780000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 10208);  // &0x7827E0
    v1 = addu(v1, v0);
    lw(t0, v1, 52);
    lhu(v0, v1, 42);
    a2 = addu(a2, t0);
    mult(zero, a2, v0);
    mflo(a2);
    mult(zero, v0, a3);
    mflo(a3);
    jal(ctx, 0x51AA34u, gen::fn__sceMcCoreReadPageFast_0051bd10);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0051AA48 _sceMcpWriteUserClustFast -- 72 bytes; frame 0x10: ra sp+0x0
// Write user clusters straight to the card (_sceMcCoreWritePageFast).
void _sceMcpWriteUserClustFast(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051aa48
    enter(ctx, 18);  // entry check point + this block's cycles
    v1 = 388;
    sp = addiu(sp, -0x10);
    mult(v1, a0, v1);
    v0 = 0x780000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 10208);  // &0x7827E0
    v1 = addu(v1, v0);
    lw(t0, v1, 52);
    lhu(v0, v1, 42);
    a2 = addu(a2, t0);
    mult(zero, a2, v0);
    mflo(a2);
    mult(zero, v0, a3);
    mflo(a3);
    jal(ctx, 0x51AA7Cu, gen::fn__sceMcCoreWritePageFast_0051bf40);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0051AA90 _sceMcpWriteUserClust -- 120 bytes; frame 0x50: s3 sp+0x30, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0, ra sp+0x40
// Write N consecutive user clusters through the write cache; 0 on the first failure.
void _sceMcpWriteUserClust(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051aa90
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    s3 = a0;
    sd(s1, sp, 0x10);
    s2 = a1;
    sd(s0, sp, 0x0);
    s1 = a2;
    s0 = a3;
    sd(ra, sp, 0x40);
    if (i64(s0) > 0) {
        // 0x0051aabc
        charge(ctx, 1);
        for (;;) {
            // 0x0051aac0
            charge(ctx, 6);
            a0 = s3;
            a1 = s2;
            a2 = s1;
            jal(ctx, 0x51AAC8u, gen::fn__sceMcpWriteUserClustOnCache_0051a508);
            s0 = addiu(s0, -1);
            if (v0 == 0) {
                goto L_0051aad8_3;
            }
            // 0x0051aae0
            charge(ctx, 2);
            s1 = addiu(s1, 1);
            if (i64(s0) <= 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0051aae8
    charge(ctx, 1);
    v0 = 1;
    // 0x0051aaec (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_0051aad8_3:
    charge(ctx, 2);
    v0 = 0;
    // 0x0051aaec (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0051AB08 _sceMcpIsSpeckOutBlock -- 72 bytes; leaf frame (no stack)
// Whether a block is in the superblock's bad-block list (32 entries).
void _sceMcpIsSpeckOutBlock(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0051ab08
    enter(ctx, 8);  // entry check point + this block's cycles
    v1 = 388;
    v0 = 0x780000;
    mult(a0, a0, v1);
    v0 = addiu(v0, 10208);  // &0x7827E0
    v1 = 0;
    a0 = addu(a0, v0);
    a0 = addiu(a0, 208);
    for (;;) {
        // 0x0051ab28
        charge(ctx, 3);
        lw(v0, a0, 0);
        v1 = addiu(v1, 1);
        if (v0 == a1) {
            goto L_0051ab34_2;
        }
        // 0x0051ab3c
        charge(ctx, 3);
        v0 = slti(v1, 32);
        a0 = addiu(a0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0051ab48
    charge(ctx, 2);
    v0 = 0;
    return;
L_0051ab34_2:
    charge(ctx, 2);
    v0 = 1;
}

// 0x0051AB50 _sceMcpIsSpeckOutClust -- 72 bytes; frame 0x10: ra sp+0x0
// Whether a cluster lies in a bad block.
void _sceMcpIsSpeckOutClust(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051ab50
    enter(ctx, 12);  // entry check point + this block's cycles
    v1 = 388;
    sp = addiu(sp, -0x10);
    mult(v1, a0, v1);
    v0 = 0x780000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 10208);  // &0x7827E0
    v1 = addu(v1, v0);
    lhu(a2, v1, 42);
    lhu(v0, v1, 44);
    mult(a1, a1, a2);
    if (v0 == 0) {
        brk(ctx, 0x51AB7Cu, 0x7u);
    }
    // 0x0051ab80
    charge(ctx, 6);
    div(a1, v0);
    mflo(a1);
    jal(ctx, 0x51AB84u, gen::fn__sceMcpIsSpeckOutBlock_0051ab08);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0051AB98 _sceMcpMakeSpecoutBlock -- 372 bytes; frame 0xC0: fp sp+0xA0, s7 sp+0x90, s6 sp+0x80, s5 sp+0x70, s4 sp+0x60, s2 sp+0x40, ra sp+0xB0, s3 sp+0x50, s1 sp+0x30, s0 sp+0x20
// Build the bad-block list for a format: reads the first pages of every block and lists (up to 16) blocks whose data
// is not all 0xFF.
void _sceMcpMakeSpecoutBlock(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051ab98
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    v1 = 0x980000;
    sd(fp, sp, 0xA0);
    sd(s7, sp, 0x90);
    fp = 0;
    sd(s6, sp, 0x80);
    sd(s5, sp, 0x70);
    s6 = addiu(v1, 19712);  // &0x984D00
    sd(s4, sp, 0x60);
    s5 = a2;
    sd(s2, sp, 0x40);
    s4 = a1;
    sd(ra, sp, 0xB0);
    s2 = 1;
    sd(s3, sp, 0x50);
    sd(s1, sp, 0x30);
    sd(s0, sp, 0x20);
    lw(v0, s4, 4);
    lw(a1, s4, 8);
    if (v0 == 0) {
        brk(ctx, 0x51ABE8u, 0x7u);
    }
    // 0x0051abec
    charge(ctx, 5);
    div(a1, v0);
    mflo(s7);
    v0 = slt(s2, s7);
    sw(a0, sp, 0x0);
    if (v0 != 0) {
        // 0x0051ac00
        charge(ctx, 4);
        s3 = lui(0xFFFF);
        t1 = 2048;
        s3 = s3 | 0xFFFF;
        v0 = slti(fp, 16);
        for (;;) {
            // 0x0051ac10
            charge(ctx, 2);
            a1 = s6;
            if (v0 != 0) {
                // 0x0051ac18
                charge(ctx, 6);
                lw(v0, s4, 0);
                lw(a2, s4, 4);
                t0 = 0;
                divu(t1, v0);
                if (v0 == 0) {
                    brk(ctx, 0x51AC2Cu, 0x7u);
                }
                // 0x0051ac30
                charge(ctx, 15);
                lw(a0, sp, 0x0);
                s1 = 0;
                sq(t1, sp, 0x10);
                mflo(v1);
                mult(zero, s2, a2);
                s0 = v1;
                mflo(a2);
                a3 = s0;
                jal(ctx, 0x51AC4Cu, gen::fn__sceMcCoreReadPage2_0051b708);
                lw(a2, s4, 0);
                a1 = 0;
                mult(v0, a2, s0);
                v0 = srl(v0, 2);
                lq(t1, sp, 0x10);
                if (v0 == 0) {
                    // 0x0051acb0
                    charge(ctx, 1);
                    a0 = addiu(s2, 1);
                } else {
                    // 0x0051ac6c
                    charge(ctx, 3);
                    lw(v0, s6, 0);
                    a0 = addiu(s2, 1);
                    if (v0 == s3) {
                        // 0x0051ac80
                        charge(ctx, 1);
                        mult(v0, a2, s0);
                        for (;;) {
                            // 0x0051ac84
                            charge(ctx, 5);
                            a1 = addiu(a1, 1);
                            v0 = srl(v0, 2);
                            v0 = sltu(a1, v0);
                            cc = v0 == 0;  // the condition, before the delay slot changes it
                            v0 = sll(a1, 2);
                            if (cc) {
                                break;
                            }
                            // 0x0051ac98
                            charge(ctx, 4);
                            v0 = addu(v0, s6);
                            lw(v1, v0, 0);
                            mult(v0, a2, s0);
                            if (v1 != s3) {
                                goto L_0051aca8_11;
                            }
                            backedge(ctx);
                        }
                    } else {
                        // 0x0051ac78
                        charge(ctx, 2);
                        s1 = 1;
                    }
                }
            L_0051acb4:
                charge(ctx, 2);
                if (i64(s1) <= 0) {
                    s2 = a0;
                } else {
                    // 0x0051acbc
                    charge(ctx, 4);
                    sw(s2, s5, 0);
                    fp = addiu(fp, 0x1);
                    s5 = addiu(s5, 4);
                    s2 = a0;
                }
                // 0x0051accc
                charge(ctx, 3);
                v0 = slt(s2, s7);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = slti(fp, 16);
                if (cc) {
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x0051acd8 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    v0 = 1;
    ld(ra, sp, 0xB0);
    ld(fp, sp, 0xA0);
    ld(s7, sp, 0x90);
    ld(s6, sp, 0x80);
    ld(s5, sp, 0x70);
    ld(s4, sp, 0x60);
    ld(s3, sp, 0x50);
    ld(s2, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0xC0);
    return;
L_0051aca8_11:
    charge(ctx, 2);
    s1 = 1;
    goto L_0051acb4;
}

// 0x0051AF70 _sceMcCoreSetWriteBackHole -- 40 bytes; leaf frame (no stack)
// Set a socket's write-back blocks (the backup blocks of the superblock).
void _sceMcCoreSetWriteBackHole(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0051af70
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = 36;
    v1 = 0x980000;
    mult(a0, a0, v0);
    v1 = addiu(v1, 21768);  // &0x985508
    v0 = 1;
    a3 = addu(v1, a0);
    v1 = a3;
    sw(a1, a3, 28);
    sw(a2, v1, 32);
}

// 0x0051AF98 _sceMcCoreSetCardSpec -- 60 bytes; leaf frame (no stack)
// Copy a 16-byte card geometry record into the socket's entry (+8).
void _sceMcCoreSetCardSpec(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0051af98
    enter(ctx, 15);  // entry check point + this block's cycles
    v0 = 36;
    v1 = 0x980000;
    mult(a0, a0, v0);
    v1 = addiu(v1, 21768);  // &0x985508
    a0 = addu(a0, v1);
    ldl(v1, a1, 7);
    ldr(v1, a1, 0);
    ldl(a2, a1, 15);
    ldr(a2, a1, 8);
    sdl(v1, a0, 15);
    sdr(v1, a0, 8);
    sdl(a2, a0, 23);
    sdr(a2, a0, 16);
    v0 = 1;
}

// 0x0051B8D0 _sceMcCoreReadPage -- 28 bytes; leaf frame (no stack)
// Read pages with the socket's ECC setting (_sceMcCoreReadPage2).
void _sceMcCoreReadPage(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, t0{ctx, 8};
    // 0x0051b8d0
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = 36;
    v0 = 0x980000;
    mult(v1, a0, v1);
    v0 = addiu(v0, 21768);  // &0x985508
    v0 = addu(v0, v1);
    lw(t0, v0, 20);
    gen::fn__sceMcCoreReadPage2_0051b708(ctx);  // tail call
}

// 0x0051C250 _sceMcCoreCheckSocket -- 48 bytes; leaf frame (no stack)
// 1 for a socket number below 2 whose entry is in use.
void _sceMcCoreCheckSocket(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0051c250
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = sltiu(a0, 2);
    v1 = 36;
    if (v0 == 0) {
        // 0x0051c25c
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x0051c264
    charge(ctx, 7);
    v0 = 0x980000;
    mult(v1, a0, v1);
    v0 = addiu(v0, 21768);  // &0x985508
    v1 = addu(v1, v0);
    lw(v0, v1, 0);
    v0 = sltu(0, v0);
}

// 0x0051C2E8 _sceMcCoreChangeSocketTypeDbc2Mc -- 68 bytes; leaf frame (no stack)
// The libmc2 socket (0 / 1) that holds a DBC socket id; -1 when none does.
void _sceMcCoreChangeSocketTypeDbc2Mc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0051c2e8
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x980000;
    v1 = 0;
    a1 = addiu(v0, 21768);  // &0x985508
    for (;;) {
        // 0x0051c2f8
        charge(ctx, 3);
        lw(v0, a1, 0);
        if (v0 == 0) {
            v1 = addiu(v1, 1);
        } else {
            // 0x0051c304
            charge(ctx, 3);
            lw(v0, a1, 4);
            if (v0 == a0) {
                goto L_0051c310_3;
            }
            v1 = addiu(v1, 1);
            goto L_0051c318;
        }
    L_0051c318:
        charge(ctx, 3);
        v0 = slti(v1, 2);
        a1 = addiu(a1, 36);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0051c324
    charge(ctx, 2);
    v0 = si(-1);
    return;
L_0051c310_3:
    charge(ctx, 2);
    v0 = v1;
}

// 0x0051C330 _sceMcCoreChangeSocketTypeMc2Dbc -- 48 bytes; leaf frame (no stack)
// The DBC socket id of a libmc2 socket; -1 when unused.
void _sceMcCoreChangeSocketTypeMc2Dbc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051c330
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 36;
    v1 = 0x980000;
    mult(a0, a0, v0);
    a1 = addiu(v1, 21768);  // &0x985508
    v0 = addu(a0, a1);
    lw(v1, v0, 0);
    cc = v1 != 0;  // the condition, before the delay slot changes it
    v1 = addu(a1, a0);
    if (cc) {
        // 0x0051c358
        charge(ctx, 2);
        lw(v0, v1, 4);
        return;
    }
    // 0x0051c350
    charge(ctx, 2);
    v0 = si(-1);
}

}  // namespace p3fes::game
