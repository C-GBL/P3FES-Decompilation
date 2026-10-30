// Slice fcl, part 3 of 3 (game/include/p3fes/game/fcl.h): fclCombineEffect.c (0x417160-0x41BE44), the persona
// fusion cut-in. fusion's root update sub_3D3D20 creates it (fclCmbEff_CreateCmbEffCalcTasks: "fclCmbEffCalc" and its
// four draw tasks plus a psModel task) and queues scripts (sub_417330); the calc task loads the resources and runs a
// script per request through a command runner: 28-byte commands keyed by frame start "active" nodes whose handlers
// (table 0x6B30A0, 29 entries) run each frame until they return 1 (fcl.h, "fusion cut-in").
//
// "fcl" = the facility layer (fclMisc.c, fclCombine*.c, fclShop*.c, fclBankManager.c, fclDrawSprite.c): the Velvet
// Room, the shops and the shared facility services, entered from the field (the sequence table's facility steps and
// field events) and from the battle result / panel for the persona-status screen; its tasks are created by those
// sequences, not by the battle layer.
//
// The bodies are p3fes_handgen's (hg_cpu.h), statement for statement as the recompiled body; this pass adds roles
// (names in [brackets] are proposals, ADR-0009) and named offsets (fcl.h).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/fcl.h"

namespace p3fes::recomp_gen {
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_fclCmbEff_CreateCmbEffCalcTasks_00417160(p3fes::EEContext&);
void fn_fclCmbEff_UpdateCmbEffDraw2DLowTask_004175e0(p3fes::EEContext&);
void fn_fclCmbEff_UpdateCmbEffDrawSPTask_00417630(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskGetWorkData_00195540(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_nmListAppendNew_003c4910(p3fes::EEContext&);
void fn_nmListFindByKey_003c4b50(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_20D650_0020d650(p3fes::EEContext&);
void fn_sub_3182D0_003182d0(p3fes::EEContext&);
void fn_sub_3C44D0_003c44d0(p3fes::EEContext&);
void fn_sub_3C45F0_003c45f0(p3fes::EEContext&);
void fn_sub_3C49E0_003c49e0(p3fes::EEContext&);
void fn_sub_3C4A90_003c4a90(p3fes::EEContext&);
void fn_sub_3CDA60_003cda60(p3fes::EEContext&);
void fn_sub_3CDF40_003cdf40(p3fes::EEContext&);
void fn_sub_3CE060_003ce060(p3fes::EEContext&);
void fn_sub_3CE180_003ce180(p3fes::EEContext&);
void fn_sub_417330_00417330(p3fes::EEContext&);
void fn_sub_417380_00417380(p3fes::EEContext&);
void fn_sub_4173E0_004173e0(p3fes::EEContext&);
void fn_sub_417680_00417680(p3fes::EEContext&);
void fn_sub_4176F0_004176f0(p3fes::EEContext&);
void fn_sub_4177E0_004177e0(p3fes::EEContext&);
void fn_sub_418030_00418030(p3fes::EEContext&);
void fn_sub_4180A0_004180a0(p3fes::EEContext&);
void fn_sub_4180E0_004180e0(p3fes::EEContext&);
void fn_sub_418130_00418130(p3fes::EEContext&);
void fn_sub_418340_00418340(p3fes::EEContext&);
void fn_sub_419B00_00419b00(p3fes::EEContext&);
void fn_sub_419B20_00419b20(p3fes::EEContext&);
void fn_sub_419B40_00419b40(p3fes::EEContext&);
void fn_sub_419C10_00419c10(p3fes::EEContext&);
void fn_sub_41A2C0_0041a2c0(p3fes::EEContext&);
void fn_sub_41A900_0041a900(p3fes::EEContext&);
void fn_sub_41ADD0_0041add0(p3fes::EEContext&);
void fn_sub_41B530_0041b530(p3fes::EEContext&);
void fn_sub_41B550_0041b550(p3fes::EEContext&);
void fn_sub_41B5C0_0041b5c0(p3fes::EEContext&);
void fn_sub_41BA60_0041ba60(p3fes::EEContext&);
void fn_sub_41BAF0_0041baf0(p3fes::EEContext&);
void fn_sub_41BC90_0041bc90(p3fes::EEContext&);
void fn_sub_41BF80_0041bf80(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);
void fn_sub_4C6C60_004c6c60(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace fcl;  // the named record offsets (fcl.h)

// 0x00417160 fclCmbEff_CreateCmbEffCalcTasks -- 456 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCmbEff_CreateCmbEffCalcTasks] ($a0 24-byte cut-in parameters) The fusion cut-in: RwMalloc(96) (K_Assert
// fclCombineEffect.c:533), zeroed; +28 = the parameters, +60 = a command runner (sub_418030), +56 = the main camera's
// frame (sub_198590 -> +4), +64 = an empty request list; creates "fclCmbEffCalc" (priority 10, update
// fclCmbEff_UpdateCmbEffCalcTask, destroy sub_417680, work = this) and under it "fclCmbEffDraw" (6310),
// "fclCmbEffDraw3D" (2109), "fclCmbEffDraw2DLow" (4207), "fclCmbEffDrawSP" (5242) into +8..+20, a psModel task into
// +24 (sub_3CDA60); sets flag 2 (loading). Returns the calc task. Caller: fusion's root update sub_3D3D20.
void fclCmbEff_CreateCmbEffCalcTasks(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00417160
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 96;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x417184u, v0.u());
    s0 = v0;
    if (s0 == 0) {
        // 0x00417198: out of memory: K_Assert (continues)
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, 10960);  // "fclCombineEffect.c"
        a1 = 533;
        jal(ctx, 0x4171A4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x004171ac: the work, the runner, the tasks
    charge(ctx, 95);
    a0 = s0;
    a1 = 0;
    a2 = 96;
    jal(ctx, 0x4171B8u, gen::fn_memset_00521408);
    a0 = addiu(s0, kCeParams);
    a1 = s1;
    a2 = 24;
    jal(ctx, 0x4171CCu, gen::fn_memcpy_00521250);
    jal(ctx, 0x4171D4u, gen::fn_sub_418030_00418030);
    sw(v0, s0, kCeRunner);
    jal(ctx, 0x4171E0u, gen::fn_sub_198590_00198590);
    lw(v0, v0, 4);
    sw(v0, s0, kCeCamera);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x417200u, gen::fn_sub_3C44D0_003c44d0);
    sw(v0, s0, kCeRequests);
    a0 = 0;
    a1 = 0x6B0000;
    a1 = addiu(a1, 10984);  // "fclCmbEffCalc"
    a2 = 10;
    a3 = 0x410000;
    a3 = addiu(a3, 29712);  // &fclCmbEff_UpdateCmbEffCalcTask
    t0 = 0x410000;
    t0 = addiu(t0, 30336);  // &sub_417680
    t1 = s0;
    jal(ctx, 0x417230u, gen::fn_kwlnTaskCreate_00194b20);
    s1 = v0;
    a0 = s1;
    a1 = 0x6B0000;
    a1 = addiu(a1, 11000);  // "fclCmbEffDraw"
    a2 = 6310;
    a3 = 0x410000;
    a3 = addiu(a3, 30016);  // &fclCmbEff_UpdateCmbEffDrawTask
    t0 = 0;
    t1 = s0;
    jal(ctx, 0x41725Cu, gen::fn_kwlnTaskCreate_00194b20);
    sw(v0, s0, kCeDrawTask);
    a0 = s1;
    a1 = 0x6B0000;
    a1 = addiu(a1, 11024);  // "fclCmbEffDraw3D"
    a2 = 2109;
    a3 = 0x410000;
    a3 = addiu(a3, 30096);  // &fclCmbEff_UpdateCmbEffDraw3DTask
    t0 = 0;
    t1 = s0;
    jal(ctx, 0x417288u, gen::fn_kwlnTaskCreate_00194b20);
    sw(v0, s0, kCeDraw3DTask);
    a0 = s1;
    a1 = 0x6B0000;
    a1 = addiu(a1, 11040);  // "fclCmbEffDraw2DLow"
    a2 = 4207;
    a3 = 0x410000;
    a3 = addiu(a3, 30176);  // &fclCmbEff_UpdateCmbEffDraw2DLowTask
    t0 = 0;
    t1 = s0;
    jal(ctx, 0x4172B4u, gen::fn_kwlnTaskCreate_00194b20);
    sw(v0, s0, kCeDraw2DTask);
    a0 = s1;
    a1 = 0x6B0000;
    a1 = addiu(a1, 11072);  // "fclCmbEffDrawSP"
    a2 = 5242;
    a3 = 0x410000;
    a3 = addiu(a3, 30256);  // &fclCmbEff_UpdateCmbEffDrawSPTask
    t0 = 0;
    t1 = s0;
    jal(ctx, 0x4172E0u, gen::fn_kwlnTaskCreate_00194b20);
    sw(v0, s0, kCeDrawSPTask);
    a0 = s1;
    a1 = 0;
    jal(ctx, 0x4172F4u, gen::fn_sub_3CDA60_003cda60);
    sw(v0, s0, kCePsModel);
    lw(v0, s0, kCeFlags);
    v0 = v0 | 0x2;
    sw(v0, s0, kCeFlags);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00417330 sub_417330 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCmbEffRequest] ($a0 calc task, $a1 script id) Appends a 4-byte request {id} to the cut-in's request list (+64).
// Returns 1. Caller: sub_3D3D20.
void sub_417330(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00417330
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x417340u, gen::fn_kwlnTaskGetWorkData_00195540);
    lw(a0, v0, kCeRequests);
    lhu(v0, a0, kNmObjCount);
    a1 = addiu(v0, 1);
    a2 = 4;
    jal(ctx, 0x417358u, gen::fn_nmListAppendNew_003c4910);
    lw(v0, v0, kNmNodePayload);
    sw(s0, v0, 0);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00417380 sub_417380 -- 96 bytes; frame 0x10: ra sp+0x0
// [fclCmbEffBusy] 1 while the cut-in is loading (flag 2), finishing (flag 4) or has queued requests (sub_41B530), else
// 0.
void sub_417380(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00417380
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x417388u, gen::fn_kwlnTaskGetWorkData_00195540);
    a0 = v0;
    lw(v1, v0, kCeFlags);
    v0 = v1 & 0x4;
    if (v0 == 0) {
        // 0x004173a4
        charge(ctx, 3);
        v0 = v1 & 0x2;
        if (v0 != 0) {
            goto L_004173c0;
        }
        // 0x004173b0
        charge(ctx, 4);
        jal(ctx, 0x4173B0u, gen::fn_sub_41B530_0041b530);
        if (v0 != 0) {
            goto L_004173c0;
        }
        // 0x004173cc
        charge(ctx, 1);
        v0 = 0;
        // 0x004173d0 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_004173c0:
    charge(ctx, 3);
    v0 = 1;
    // 0x004173d0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004173E0 sub_4173E0 -- 36 bytes; frame 0x10: ra sp+0x0
// [fclCmbEffGetPsModel] The cut-in's psModel task (+24).
void sub_4173E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004173e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x4173E8u, gen::fn_kwlnTaskGetWorkData_00195540);
    lw(v0, v0, kCePsModel);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004175E0 fclCmbEff_UpdateCmbEffDraw2DLowTask -- 76 bytes; frame 0x10: ra sp+0x0
// [fclCmbEff_UpdateCmbEffDraw2DLowTask] The "fclCmbEffDraw2DLow" task: when the cut-in is running (flag 1) draws its
// 2D resources (sub_41BA60). Returns 0.
void fclCmbEff_UpdateCmbEffDraw2DLowTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004175e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x4175E8u, gen::fn_kwlnTaskGetWorkData_00195540);
    a0 = v0;
    lw(v0, v0, kCeFlags);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x00417610
        charge(ctx, 3);
        jal(ctx, 0x417610u, gen::fn_sub_41BA60_0041ba60);
        v0 = 0;
    } else {
        // 0x00417604
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0041761c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00417630 fclCmbEff_UpdateCmbEffDrawSPTask -- 76 bytes; frame 0x10: ra sp+0x0
// [fclCmbEff_UpdateCmbEffDrawSPTask] The "fclCmbEffDrawSP" task: when running draws the special layer (sub_41BAF0).
// Returns 0.
void fclCmbEff_UpdateCmbEffDrawSPTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00417630
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x417638u, gen::fn_kwlnTaskGetWorkData_00195540);
    a0 = v0;
    lw(v0, v0, kCeFlags);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x00417660
        charge(ctx, 3);
        jal(ctx, 0x417660u, gen::fn_sub_41BAF0_0041baf0);
        v0 = 0;
    } else {
        // 0x00417654
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0041766c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00417680 sub_417680 -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCmbEffDestroy] Destroy callback of "fclCmbEffCalc": destroys the resource list object (+52 -> +20), the runner's
// two lists (sub_4180A0) and the request list (sub_3C45F0), then frees the work (RW slot 0x96017C).
void sub_417680(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00417680
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x41768Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    lw(v0, v0, kCeResources);
    if (v0 != 0) {
        // 0x004176a4
        charge(ctx, 3);
        lw(a0, v0, kCeResObj);
        jal(ctx, 0x4176A8u, gen::fn_sub_3C45F0_003c45f0);
    }
    // 0x004176b0
    charge(ctx, 16);
    lw(a0, s0, kCeRunner);
    jal(ctx, 0x4176B4u, gen::fn_sub_4180A0_004180a0);
    lw(a0, s0, kCeRequests);
    jal(ctx, 0x4176C0u, gen::fn_sub_3C45F0_003c45f0);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x4176D4u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004176F0 sub_4176F0 -- 236 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCmbEffAddResource] ($a0 work, $a1 s16 kind, $a2 file name or 0) Appends a resource node (payload 9 + strlen
// bytes, key = count + 1) to the resource list (+52 -> +20; K_Assert fclCombineEffect.c:717 when missing): payload +0
// = kind, +4 = the name copied to +8 (or 0). Returns the node.
void sub_4176F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004176f0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = 0;
    if (s1 != 0) {
        // 0x00417720
        charge(ctx, 4);
        a0 = s1;
        jal(ctx, 0x417724u, gen::fn_strlen_00524388);
        s0 = v0;
    }
    // 0x00417730
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x00417738
        charge(ctx, 3);
        lw(v0, s3, kCeResources);
        if (v0 == 0) {
            goto L_00417750;
        }
        // 0x00417744
        charge(ctx, 3);
        lw(v0, v0, kCeResObj);
        if (v0 == 0) {
            goto L_00417750;
        }
        goto L_00417764;
    }
L_00417750:
    charge(ctx, 5);
    a0 = 0x6B0000;
    a0 = addiu(a0, 10960);  // "fclCombineEffect.c"
    a1 = 717;
    jal(ctx, 0x41775Cu, gen::fn_sub_19D3F0_0019d3f0);
L_00417764:
    charge(ctx, 12);
    lw(v0, s3, kCeResources);
    lw(a0, v0, kCeResObj);
    lhu(v0, a0, kNmObjCount);
    a1 = addiu(v0, 1);
    a2 = addiu(s0, 9);
    jal(ctx, 0x417778u, gen::fn_nmListAppendNew_003c4910);
    s3 = v0;
    lw(v0, v0, kNmNodePayload);
    sh(s2, v0, 0);
    if (s0 == 0) {
        // 0x004177b4
        charge(ctx, 1);
        sw(zero, v0, 4);
    } else {
        // 0x00417794
        charge(ctx, 8);
        a0 = addiu(v0, 8);
        sw(a0, v0, 4);
        a2 = s0 & 0xFFFF;
        a1 = s1;
        jal(ctx, 0x4177A4u, gen::fn_memcpy_00521250);
    }
    // 0x004177b8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s3;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004177E0 sub_4177E0 -- 216 bytes; frame 0xB0: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCmbEffLoadResources] Builds the resource list of the cut-in: a 28-byte-payload list object (payload +0 = 0, +20
// = the object) into +52, the 16 {kind, file} entries of table 0x6B2CF0 (sub_4176F0), and a kind-64 command list on
// the runner (sub_4180E0). Returns 0. Caller: the calc update.
void sub_4177E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004177e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a2 = 0x6B0000;
    a2 = addiu(a2, 11504);  // &0x6B2CF0
    a1 = addiu(sp, 0x30);
    a0 = 16;
    for (;;) {
        // 0x00417804
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00417828
    charge(ctx, 13);
    a0 = 28;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x417838u, gen::fn_sub_3C44D0_003c44d0);
    lw(v1, v0, kNmObjPayload);
    sw(zero, v1, 0);
    sw(v0, v1, kCeResObj);
    sw(v1, s0, kCeResources);
    s1 = 0;
    for (;;) {
        // 0x00417880
        charge(ctx, 3);
        v0 = sltiu(s1, 16);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0041785c
        charge(ctx, 9);
        v0 = sll(s1, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 48);
        a0 = s0;
        lh(a1, v0, 0);
        lw(a2, v0, 4);
        jal(ctx, 0x417874u, gen::fn_sub_4176F0_004176f0);
        s1 = addiu(s1, 1);
    }
    // 0x0041788c
    charge(ctx, 11);
    lw(a0, s0, kCeRunner);
    a1 = 64;
    jal(ctx, 0x417894u, gen::fn_sub_4180E0_004180e0);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x00418030 sub_418030 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCmbEffRunnerCreate] The command runner: a 20-byte-payload list object (resource on-insert sub_418130, on-remove
// sub_418230; payload +0 = the object) plus a second, empty list object at payload +4. Returns the payload.
void sub_418030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00418030
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 20;
    a1 = 0x420000;
    a1 = addiu(a1, -32464);  // &sub_418130
    a2 = 0x420000;
    a2 = addiu(a2, -32208);  // &sub_418230
    a3 = 0;
    jal(ctx, 0x418054u, gen::fn_sub_3C44D0_003c44d0);
    lw(s0, v0, kNmObjPayload);
    sw(v0, s0, kRunResList);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x418074u, gen::fn_sub_3C44D0_003c44d0);
    sw(v0, s0, kRunActive);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004180A0 sub_4180A0 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCmbEffRunnerDestroy] Destroys the runner's two list objects (+0, +4) with sub_3C45F0.
void sub_4180A0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004180a0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, kRunResList);
    jal(ctx, 0x4180B4u, gen::fn_sub_3C45F0_003c45f0);
    lw(a0, s0, kRunActive);
    jal(ctx, 0x4180C0u, gen::fn_sub_3C45F0_003c45f0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004180E0 sub_4180E0 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCmbEffRunnerAdd] Appends a 12-byte node with key $a1 to the runner's resource list (+0); payload +2 = $a1.
// Returns the payload.
void sub_4180E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004180e0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    a1 = dsll32(s0, 16);
    a1 = dsra32(a1, 16);
    lw(a0, a0, kRunResList);
    a2 = 12;
    jal(ctx, 0x418100u, gen::fn_nmListAppendNew_003c4910);
    lw(v0, v0, kNmNodePayload);
    sh(s0, v0, 2);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00418130 sub_418130 -- 248 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCmbEffResourceOnInsert] On-insert of the runner's resource list: by the node key's low byte allocates the
// resource's buffer into payload +8 (4 -> 32 bytes, 5 -> 10,032, 6 -> 4,008; RW slot 0x960178, zeroed). Returns 0.
void sub_418130(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00418130
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, kNmNodePayload);
    lbu(v1, a1, 0);
    v0 = 6;
    if (v1 == v0) {
        // 0x004181e0
        charge(ctx, 12);
        a0 = 4008;
        a1 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178
        jalr(ctx, 0x4181F0u, v0.u());
        sw(v0, s0, kResBuffer);
        a0 = v0;
        a1 = 0;
        a2 = 4008;
        jal(ctx, 0x418208u, gen::fn_memset_00521408);
    } else {
        // 0x00418150
        charge(ctx, 3);
        v0 = 5;
        if (v1 == v0) {
            // 0x004181a8
            charge(ctx, 14);
            a0 = 10032;
            a1 = 0x40000;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178
            jalr(ctx, 0x4181B8u, v0.u());
            sw(v0, s0, kResBuffer);
            a0 = v0;
            a1 = 0;
            a2 = 10032;
            jal(ctx, 0x4181D0u, gen::fn_memset_00521408);
        } else {
            // 0x0041815c
            charge(ctx, 3);
            v0 = 4;
            if (v1 == v0) {
                // 0x00418170
                charge(ctx, 14);
                a0 = 32;
                a1 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 376);  // 0x960178
                jalr(ctx, 0x418180u, v0.u());
                sw(v0, s0, kResBuffer);
                a0 = v0;
                a1 = 0;
                a2 = 32;
                jal(ctx, 0x418198u, gen::fn_memset_00521408);
            } else {
                // 0x00418168
                charge(ctx, 2);
            }
        }
    }
    // 0x00418210 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00418340 sub_418340 -- 68 bytes; leaf frame (no stack)
// [fclCmbEffCmdFlags] Command handler: resource u16 flags |= command +12, then &= ~command +16. Returns 1 (done).
void sub_418340(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00418340
    enter(ctx, 17);  // entry check point + this block's cycles
    lw(a2, a1, kActResource);
    lw(a1, a1, kActCommand);
    lh(v1, a1, kCmdArg12);
    lh(v0, a2, 0);
    a0 = v0 | v1;
    sh(a0, a2, 0);
    lw(v0, a1, kCmdArg16);
    v0 = nor(v0, 0);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v0 = v0 & v1;
    sh(v0, a2, 0);
    v0 = 1;
}

// 0x00419B00 sub_419B00 -- 28 bytes; leaf frame (no stack)
// [fclCmbEffCmdRestart] Command handler: runner flags |= 2 (restart the command list). Returns 1.
void sub_419B00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00419b00
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v1, a0, kCeRunner);
    lw(v0, v1, kRunFlags);
    v0 = v0 | 0x2;
    sw(v0, v1, kRunFlags);
    v0 = 1;
}

// 0x00419B20 sub_419B20 -- 28 bytes; leaf frame (no stack)
// [fclCmbEffCmdEnd] Command handler: runner flags |= 1 (end of script). Returns 1.
void sub_419B20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00419b20
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v1, a0, kCeRunner);
    lw(v0, v1, kRunFlags);
    v0 = v0 | 0x1;
    sw(v0, v1, kRunFlags);
    v0 = 1;
}

// 0x00419B40 sub_419B40 -- 60 bytes; leaf frame (no stack)
// [fclCmbEffCmdEndWhenIdle] Command handler: when at most one command is active (runner active list count < 2) sets
// runner flag 1 and returns 1; else 0 (wait).
void sub_419B40(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00419b40
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, a0, kCeRunner);
    lw(v0, v1, kRunActive);
    lhu(v0, v0, kNmObjCount);
    at = sltiu(v0, 2);
    if (at == 0) {
        // 0x00419b70
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00419b58
        charge(ctx, 6);
        lw(v0, v1, kRunFlags);
        v0 = v0 | 0x1;
        sw(v0, v1, kRunFlags);
        v0 = 1;
    }
    // 0x00419b74 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00419C10 sub_419C10 -- 784 bytes; frame 0x30: ra sp+0x0
// [fclCmbEffCmdPsColour] Command handler for opcode 64 / sub-op 3: converts the command's RGBA word (+12) to floats
// and, by +16 (0 colour, 1 colour A, 2 colour B), fades the psModel (+24) to it over +20 frames (sub_3CDF40 /
// sub_3CE060 / sub_3CE180). Returns 1.
void sub_419C10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00419c10
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x0);
    lw(t0, a1, kActCommand);
    lw(a3, t0, kCmdArg12);
    lw(a2, t0, kCmdArg20);
    lw(v0, t0, kCmdArg16);
    v1 = srl(a3, 24);
    v1 = v1 & 0xFF;
    if (i64(v1) < 0) {
        // 0x00419c4c
        charge(ctx, 7);
        a1 = srl(v1, 1);
        v1 = v1 & 0x1;
        a1 = a1 | v1;
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00419c38
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00419c68
    charge(ctx, 5);
    swc1(f0, sp, 0x10);
    v1 = srl(a3, 16);
    v1 = v1 & 0xFF;
    if (i64(v1) < 0) {
        // 0x00419c90
        charge(ctx, 7);
        a1 = srl(v1, 1);
        v1 = v1 & 0x1;
        a1 = a1 | v1;
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00419c7c
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00419cac
    charge(ctx, 5);
    swc1(f0, sp, 0x14);
    v1 = srl(a3, 8);
    v1 = v1 & 0xFF;
    if (i64(v1) < 0) {
        // 0x00419cd4
        charge(ctx, 7);
        a1 = srl(v1, 1);
        v1 = v1 & 0x1;
        a1 = a1 | v1;
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00419cc0
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00419cf0
    charge(ctx, 4);
    swc1(f0, sp, 0x18);
    v1 = a3 & 0xFF;
    if (i64(v1) < 0) {
        // 0x00419d14
        charge(ctx, 7);
        a1 = srl(v1, 1);
        v1 = v1 & 0x1;
        a1 = a1 | v1;
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00419d00
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00419d30
    charge(ctx, 5);
    swc1(f0, sp, 0x1C);
    lb(a1, t0, kCmdOp);
    v1 = 64;
    if (a1 == v1) {
        // 0x00419d4c
        charge(ctx, 4);
        lb(a1, t0, kCmdSubOp);
        v1 = 3;
        if (a1 == v1) {
            // 0x00419d64
            charge(ctx, 3);
            v1 = 2;
            if (v0 == v1) {
                // 0x00419efc
                charge(ctx, 4);
                lw(a0, a0, kCePsModel);
                a1 = addiu(sp, 0x10);
                jal(ctx, 0x419F04u, gen::fn_sub_3CE180_003ce180);
            } else {
                // 0x00419d70
                charge(ctx, 3);
                v1 = 1;
                if (v0 == v1) {
                    // 0x00419ee4
                    charge(ctx, 6);
                    lw(a0, a0, kCePsModel);
                    a1 = addiu(sp, 0x10);
                    jal(ctx, 0x419EECu, gen::fn_sub_3CE060_003ce060);
                } else {
                    // 0x00419d7c
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x00419d8c
                        charge(ctx, 7);
                        lwc1(f1, sp, 0x10);
                        v0 = 0x4F000000;
                        mtc1(v0, f0);
                        c_le_s(f0, f1);
                        if (cond(ctx)) {
                            // 0x00419dc0
                            charge(ctx, 6);
                            sub_s(f0, f1, f0);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            v0 = lui(0x8000);
                            v1 = v1 | v0;
                            v1 = v1 & 0xFF;
                        } else {
                            // 0x00419da8
                            charge(ctx, 6);
                            cvt_w_s(f0, f1);
                            mfc1(v1, f0);
                            v1 = v1 & 0xFF;
                        }
                        // 0x00419dd8
                        charge(ctx, 8);
                        sb(v1, sp, 0x2C);
                        lwc1(f1, sp, 0x14);
                        v0 = 0x4F000000;
                        mtc1(v0, f0);
                        c_le_s(f0, f1);
                        if (cond(ctx)) {
                            // 0x00419e10
                            charge(ctx, 6);
                            sub_s(f0, f1, f0);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            v0 = lui(0x8000);
                            v1 = v1 | v0;
                            v1 = v1 & 0xFF;
                        } else {
                            // 0x00419df8
                            charge(ctx, 6);
                            cvt_w_s(f0, f1);
                            mfc1(v1, f0);
                            v1 = v1 & 0xFF;
                        }
                        // 0x00419e28
                        charge(ctx, 8);
                        sb(v1, sp, 0x2D);
                        lwc1(f1, sp, 0x18);
                        v0 = 0x4F000000;
                        mtc1(v0, f0);
                        c_le_s(f0, f1);
                        if (cond(ctx)) {
                            // 0x00419e60
                            charge(ctx, 6);
                            sub_s(f0, f1, f0);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            v0 = lui(0x8000);
                            v1 = v1 | v0;
                            v1 = v1 & 0xFF;
                        } else {
                            // 0x00419e48
                            charge(ctx, 6);
                            cvt_w_s(f0, f1);
                            mfc1(v1, f0);
                            v1 = v1 & 0xFF;
                        }
                        // 0x00419e78
                        charge(ctx, 8);
                        sb(v1, sp, 0x2E);
                        lwc1(f1, sp, 0x1C);
                        v0 = 0x4F000000;
                        mtc1(v0, f0);
                        c_le_s(f0, f1);
                        if (cond(ctx)) {
                            // 0x00419eb0
                            charge(ctx, 6);
                            sub_s(f0, f1, f0);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            v0 = lui(0x8000);
                            v1 = v1 | v0;
                            v1 = v1 & 0xFF;
                        } else {
                            // 0x00419e98
                            charge(ctx, 6);
                            cvt_w_s(f0, f1);
                            mfc1(v1, f0);
                            v1 = v1 & 0xFF;
                        }
                        // 0x00419ec8
                        charge(ctx, 7);
                        sb(v1, sp, 0x2F);
                        lw(a0, a0, kCePsModel);
                        a1 = addiu(sp, 0x2C);
                        jal(ctx, 0x419ED4u, gen::fn_sub_3CDF40_003cdf40);
                    } else {
                        // 0x00419d84
                        charge(ctx, 2);
                    }
                }
            }
        } else {
            // 0x00419d5c
            charge(ctx, 2);
        }
    } else {
        // 0x00419d44
        charge(ctx, 2);
    }
    // 0x00419f0c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0041A2C0 sub_41A2C0 -- 76 bytes; frame 0x10: ra sp+0x0
// [fclCmbEffCmdAnim] Command handler: sub_3182D0(resource +8 (the model), 0, s16 work +32, command +16 low / high
// halves) -- starts a model animation. Returns 1.
void sub_41A2C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0041a2c0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a0;
    lw(v0, a1, kActCommand);
    lw(v0, v0, kCmdArg16);
    lw(v1, a1, kActResource);
    a3 = v0 & 0xFFFF;
    v0 = sra(v0, 16);
    t0 = v0 & 0xFFFF;
    lw(a0, v1, kResBuffer);
    a1 = 0;
    lh(a2, a2, 32);
    jal(ctx, 0x41A2F0u, gen::fn_sub_3182D0_003182d0);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0041A900 sub_41A900 -- 704 bytes; frame 0x120: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [fclCmbEffCmdRing] Command handler: places the resource's objects (+8: count +4, objects +8..) on a ring: radius
// from table 0x6B2FD0 by count, swinging with sin over 5 frames (0x7CAF38 / 0x7CAEEC), rotated by the matrix of
// 0x7CDA68 (sub_4C31B0, sub_4C6C60) and offset by 0x6B3008; sets each object's position (sub_20D650). Returns 1 after
// 5 frames (+12 counter), else 0.
void sub_41A900(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x0041a900
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s3 = a1;
    lw(v0, a1, kActResource);
    lw(s0, v0, kResBuffer);
    a2 = 0x6B0000;
    a2 = addiu(a2, 12240);  // &0x6B2FD0
    a1 = addiu(sp, 0xC0);
    a0 = 5;
    for (;;) {
        // 0x0041a944
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0041a968
    charge(ctx, 16);
    v0 = 0x6B0000;
    ld(v1, v0, 12280);  // 0x6B2FF8
    v0 = 0x6B0000;
    lwc1(f0, v0, 12288);  // 0x6B3000
    sd(v1, sp, 0x110);
    swc1(f0, sp, 0x118);
    v0 = 0x6B0000;
    ld(v1, v0, 12296);  // 0x6B3008
    v0 = 0x6B0000;
    lwc1(f0, v0, 12304);  // 0x6B3010
    sd(v1, sp, 0x100);
    swc1(f0, sp, 0x108);
    a1 = 0x6B0000;
    a1 = addiu(a1, 12320);  // &0x6B3020
    a0 = addiu(sp, 0x60);
    v1 = 5;
    for (;;) {
        // 0x0041a9a8
        charge(ctx, 7);
        lw(v0, a1, 0);
        a1 = addiu(a1, 4);
        v1 = addiu(v1, -1);
        sw(v0, a0, 0);
        a0 = addiu(a0, 4);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0041a9c4
    charge(ctx, 33);
    lwc1(f0, s3, kActTimer);
    cvt_s_w(f0, f0);
    v0 = 0x40A00000;
    mtc1(v0, f2);
    sub_s(f1, f2, f0);
    lwc1(f0, gp, -32184);  // 0x7CAF38
    mul_s(f0, f0, f1);
    div_s(f1, f0, f2);
    lwc1(f0, gp, -32260);  // 0x7CAEEC
    add_s(f12, f0, f1);
    jal(ctx, 0x41A9F4u, gen::fn_sinf_0052e878);
    v0 = 0x3F800000;
    mtc1(v0, f1);
    add_s(f1, f1, f0);
    lw(v0, s0, 4);
    v0 = sll(v0, 2);
    v0 = addu(v0, sp);
    lwc1(f0, v0, 88);
    mul_s(f1, f0, f1);
    v0 = 0x40000000;
    mtc1(v0, f0);
    div_s(f23, f1, f0);
    s1 = 0;
    neg_s(f22, f23);
    lwc1(f21, sp, 0x104);
    lwc1(f20, sp, 0x108);
    for (;;) {
        // 0x0041ab4c
        charge(ctx, 4);
        lw(v0, s0, 4);
        v0 = slt(s1, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0041aa48
        charge(ctx, 65);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        lw(v0, v0, 8);
        lw(s2, v0, 8);
        lw(v0, s0, 4);
        v0 = sll(v0, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 192);
        mtc1(s1, f0);
        cvt_s_w(f3, f0);
        lwc1(f2, v0, -12);
        lwc1(f1, v0, -16);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f12, f3, f2);
        jal(ctx, 0x41AA8Cu, gen::fn_cosf_0052e6d8);
        mul_s(f0, f23, f0);
        swc1(f0, sp, 0xF0);
        lw(v0, s0, 4);
        v0 = sll(v0, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 192);
        mtc1(s1, f0);
        cvt_s_w(f3, f0);
        lwc1(f2, v0, -12);
        lwc1(f1, v0, -16);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f12, f3, f2);
        jal(ctx, 0x41AAD0u, gen::fn_sinf_0052e878);
        mul_s(f0, f22, f0);
        swc1(f0, sp, 0xF4);
        sw(zero, sp, 0xF8);
        a0 = addiu(sp, 0x80);
        a1 = addiu(sp, 0x110);
        lwc1(f12, gp, -21128);  // 0x7CDA68
        a2 = 0;
        jal(ctx, 0x41AAF4u, gen::fn_sub_4C31B0_004c31b0);
        a0 = addiu(sp, 0xF0);
        a1 = a0;
        a2 = addiu(sp, 0x80);
        jal(ctx, 0x41AB08u, gen::fn_sub_4C6C60_004c6c60);
        lwc1(f1, sp, 0xF0);
        lwc1(f0, sp, 0x100);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF0);
        lwc1(f0, sp, 0xF4);
        add_s(f0, f0, f21);
        swc1(f0, sp, 0xF4);
        lwc1(f0, sp, 0xF8);
        add_s(f0, f0, f20);
        swc1(f0, sp, 0xF8);
        a0 = s2;
        a1 = addiu(sp, 0xF0);
        jal(ctx, 0x41AB40u, gen::fn_sub_20D650_0020d650);
        s1 = addiu(s1, 1);
    }
    // 0x0041ab5c
    charge(ctx, 12);
    lw(v0, s3, kActTimer);
    v0 = addiu(v0, 1);
    sw(v0, s3, kActTimer);
    lwc1(f0, s3, kActTimer);
    cvt_s_w(f1, f0);
    v0 = 0x40A00000;
    mtc1(v0, f0);
    c_le_s(f1, f0);
    v0 = 1;
    if (cond(ctx)) {
        // 0x0041ab8c
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0041ab90 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x120);
}

// 0x0041ADD0 sub_41ADD0 -- 80 bytes; leaf frame (no stack)
// [fclCmbEffCmdHide] Command handler: clears bit 0 of the u16 flags of every object of the resource (+8). Returns 1.
void sub_41ADD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0041add0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a1, kActResource);
    lw(a1, v0, kResBuffer);
    a2 = 0;
    v1 = si(-2);
    for (;;) {
        // 0x0041ae04
        charge(ctx, 4);
        lw(v0, a1, kActResource);
        v0 = slt(a2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0041ade8
        charge(ctx, 7);
        v0 = sll(a2, 2);
        v0 = addu(a1, v0);
        lw(a0, v0, 8);
        lh(v0, a0, 0);
        v0 = v0 & v1;
        sh(v0, a0, 0);
        a2 = addiu(a2, 1);
    }
    // 0x0041ae14
    charge(ctx, 3);
    v0 = 1;
}

// 0x0041B530 sub_41B530 -- 20 bytes; leaf frame (no stack)
// [fclCmbEffHasRequest] 1 when the request list (+64) has a node, else 0.
void sub_41B530(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0041b530
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, kCeRequests);
    lw(v0, v0, kNmObjHead);
    v0 = sltu(0, v0);
}

// 0x0041B550 sub_41B550 -- 104 bytes; frame 0x10: ra sp+0x0
// [fclCmbEffStartRequest] Takes the first request: +68 = the script entry 0x6B2AA0 + 8 * id, runner frame +8 = 0,
// runner flag 1 cleared, and removes the request node (sub_3C49E0).
void sub_41B550(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0041b550
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, kCeRequests);
    lw(a2, v0, kNmObjHead);
    lw(v0, a2, kNmNodePayload);
    lw(v0, v0, 0);
    v1 = sll(v0, 3);
    v0 = 0x6B0000;
    v0 = addiu(v0, 10912);  // &0x6B2AA0
    v0 = addu(v0, v1);
    sw(v0, a0, kCeScript);
    lw(v0, a0, kCeRunner);
    sw(zero, v0, kRunFrame);
    lw(a1, a0, kCeRunner);
    lw(v1, a1, kRunFlags);
    v0 = si(-2);
    v0 = v1 & v0;
    sw(v0, a1, kRunFlags);
    lw(a0, a0, kCeRequests);
    a1 = addiu(a0, kNmObjList);
    jal(ctx, 0x41B5A0u, gen::fn_sub_3C49E0_003c49e0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0041B5C0 sub_41B5C0 -- 588 bytes; frame 0x100: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCmbEffRunScript] One frame of the command runner ($a1 the script {commands, count}, 28-byte commands {frame, s8
// op / u8 key, sub, s16 handler}): every command whose frame equals the runner frame (+8) starts -- it finds its
// resource by key (nmListFindByKey; op >= 64 keys by the unsigned byte) and appends an active node {command copy at
// +112, resource, handler = table 0x6B30A0 [command +6]}, counting +12; then, walking the active list from its cursor
// (+12), every active node's handler runs (jalr with the work and the node payload; K_Assert fclCombineEffect.c:2099
// when null) and finished ones are removed (sub_3C49E0), a restart (flag 2) clears the whole active list. Frame +1
// (clamped to 0x1FFFFFFF). Returns 1 and clears +68 when the end flag (1) is set, else 0.
void sub_41B5C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0041b5c0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    lw(s1, a0, kCeRunner);
    lw(s3, a1, kScriptCommands);
    s2 = 0;
    for (;;) {
        // 0x0041b6e0
        charge(ctx, 4);
        lw(v0, s4, kScriptCount);
        v0 = slt(s2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0041b600: a command of this frame?
        charge(ctx, 4);
        lw(v1, s3, kCmdFrame);
        lw(v0, s1, kRunFrame);
        if (v1 == v0) {
            // 0x0041b610: the handler table 0x6B30A0 to the stack
            charge(ctx, 4);
            a1 = 0x6B0000;
            a1 = addiu(a1, 12448);  // &0x6B30A0
            a0 = addiu(sp, 0x80);
            v1 = 29;
            for (;;) {
                // 0x0041b620
                charge(ctx, 7);
                lw(v0, a1, 0);
                a1 = addiu(a1, 4);
                v1 = addiu(v1, -1);
                sw(v0, a0, 0);
                a0 = addiu(a0, 4);
                if (i64(v1) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0041b63c: its resource key (op >= 64: the unsigned byte)
            charge(ctx, 5);
            lh(a1, s3, kCmdOp);
            lb(v1, s3, kCmdOp);
            v0 = slti(v1, 64);
            if (v0 == 0) {
                // 0x0041b650
                charge(ctx, 3);
                v0 = v1 & 0xFF;
                a1 = dsll32(v0, 16);
                a1 = dsra32(a1, 16);
            }
            // 0x0041b65c
            charge(ctx, 8);
            lw(a0, s1, kRunResList);
            a2 = dsll32(a1, 16);
            a2 = dsra32(a2, 16);
            a1 = addiu(a0, 4);
            jal(ctx, 0x41B66Cu, gen::fn_nmListFindByKey_003c4b50);
            if (v0 != 0) {
                // 0x0041b67c: start it: an active node
                charge(ctx, 20);
                lw(s6, v0, kNmNodePayload);
                lw(a0, s1, kRunActive);
                lhu(v0, a0, kNmObjCount);
                a1 = addiu(v0, 1);
                a2 = 140;
                jal(ctx, 0x41B690u, gen::fn_nmListAppendNew_003c4910);
                lw(s0, v0, kNmNodePayload);
                a0 = addiu(s0, kActCommandCopy);
                sw(a0, s0, kActCommand);
                a1 = s3;
                a2 = 28;
                jal(ctx, 0x41B6ACu, gen::fn_memcpy_00521250);
                sw(s6, s0, kActResource);
                lh(v0, s3, kCmdHandler);
                v0 = sll(v0, 2);
                v0 = addu(v0, sp);
                lw(v0, v0, 128);
                sw(v0, s0, kActHandler);
            }
            // 0x0041b6cc: count it
            charge(ctx, 3);
            lw(v0, s1, kRunStarted);
            v0 = addiu(v0, 1);
            sw(v0, s1, kRunStarted);
        }
        // 0x0041b6d8
        charge(ctx, 2);
        s3 = addiu(s3, 28);
        s2 = addiu(s2, 1);
    }
    // 0x0041b6f0: run the active commands (from the list cursor)
    charge(ctx, 4);
    lw(s3, s1, kRunActive);
    lw(s2, s3, kNmObjCursor);
    for (;;) {
        // 0x0041b790
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0041b700
        charge(ctx, 6);
        lw(s4, s2, kNmNodePayload);
        s0 = s2;
        lw(s2, s2, kNmNodeNext);
        lw(v0, s4, kActHandler);
        if (v0 == 0) {
            // 0x0041b718: no handler: K_Assert (continues)
            charge(ctx, 5);
            a0 = 0x6B0000;
            a0 = addiu(a0, 10960);  // "fclCombineEffect.c"
            a1 = 2099;
            jal(ctx, 0x41B724u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x0041b72c: the handler (jalr)
        charge(ctx, 7);
        a0 = s5;
        a1 = s4;
        lw(v0, s4, kActHandler);
        jalr(ctx, 0x41B738u, v0.u());
        if (v0 == 0) {
            continue;
        }
        // 0x0041b748: finished: restart requested?
        charge(ctx, 4);
        lw(v1, s1, kRunFlags);
        v0 = v1 & 0x2;
        if (v0 != 0) {
            goto L_0041b758_16;
        }
        // 0x0041b77c: remove the finished command
        charge(ctx, 5);
        a0 = s3;
        a1 = addiu(s3, kNmObjList);
        a2 = s0;
        jal(ctx, 0x41B788u, gen::fn_sub_3C49E0_003c49e0);
    }
L_0041b798:
    charge(ctx, 8);
    lw(v0, s1, kRunFrame);
    a0 = addiu(v0, 1);
    sw(a0, s1, kRunFrame);
    v0 = 0x1FFF0000;
    v1 = v0 | 0xFFFF;
    v0 = slt(a0, v1);
    if (v0 == 0) {
        // 0x0041b7b8
        charge(ctx, 1);
        sw(v1, s1, kRunFrame);
    }
    // 0x0041b7bc: end of script?
    charge(ctx, 4);
    lw(v0, s1, kRunFlags);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0041b7dc
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0041b7cc: ended: clear the script
        charge(ctx, 4);
        sw(zero, s5, kCeScript);
        v0 = 1;
    }
    // 0x0041b7e0 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x100);
    return;
L_0041b758_16:
    charge(ctx, 9);
    v0 = si(-3);
    v0 = v1 & v0;
    sw(v0, s1, kRunFlags);
    a0 = s3;
    a1 = addiu(s3, kNmObjList);
    jal(ctx, 0x41B76Cu, gen::fn_sub_3C4A90_003c4a90);
    goto L_0041b798;
}

// 0x0041BA60 sub_41BA60 -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCmbEffDraw2D] Draws the visible 2D resources: walking the runner's resource list from its cursor (+12), every
// node whose u16 flags have 8 and 1 and kind byte (+2) 2 gets sub_41BF80 on its buffer (+8). Returns 0.
void sub_41BA60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0041ba60
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, kCeRunner);
    lw(v0, v0, kRunResList);
    lw(s0, v0, kNmObjCursor);
    for (;;) {
        // 0x0041bac8
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0041ba80
        charge(ctx, 5);
        lw(a0, s0, kNmNodePayload);
        lh(v1, a0, 0);
        v0 = v1 & 0x8;
        if (v0 != 0) {
            // 0x0041ba94
            charge(ctx, 3);
            v0 = v1 & 0x1;
            if (v0 != 0) {
                // 0x0041baa0
                charge(ctx, 4);
                lb(v1, a0, kResKind);
                v0 = 2;
                if (v1 == v0) {
                    // 0x0041bab8
                    charge(ctx, 3);
                    lw(a0, a0, kResBuffer);
                    jal(ctx, 0x41BABCu, gen::fn_sub_41BF80_0041bf80);
                } else {
                    // 0x0041bab0
                    charge(ctx, 2);
                }
            }
        }
        // 0x0041bac4
        charge(ctx, 1);
        lw(s0, s0, kNmNodeNext);
    }
    // 0x0041bad0
    charge(ctx, 6);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0041BC90 sub_41BC90 -- 436 bytes; frame 0x90: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCmbEffVertexBuffer] ($a0 positions (12 bytes each), $a1 uv pairs, $a2 RGBA words, $a3 count, $t0 texture;
// K_Assert fclCombineEffect.c:2279 on bad input) RwMalloc(20 + 36 n), zeroed: +12 texture, +8 count, +4 the 36-byte
// vertices {xyz, rgba bytes +12, u +28, v +32}, +16 = sub_4C38C0(). Returns the block.
void sub_41BC90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0041bc90
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    s6 = a2;
    s3 = a3;
    s2 = t0;
    if (s5 != 0) {
        // 0x0041bcd0
        charge(ctx, 2);
        if (i64(s3) <= 0) {
            goto L_0041bce0;
        }
        // 0x0041bcd8
        charge(ctx, 2);
        if (s2 == 0) {
            goto L_0041bce0;
        }
        goto L_0041bcf4;
    }
L_0041bce0:
    charge(ctx, 5);
    a0 = 0x6B0000;
    a0 = addiu(a0, 10960);  // "fclCombineEffect.c"
    a1 = 2279;
    jal(ctx, 0x41BCECu, gen::fn_sub_19D3F0_0019d3f0);
L_0041bcf4:
    charge(ctx, 23);
    v0 = sll(s3, 3);
    v0 = addu(v0, s3);
    v0 = sll(v0, 2);
    s0 = addiu(v0, 20);
    a0 = s0;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x41BD14u, v0.u());
    s1 = v0;
    a0 = s1;
    a1 = 0;
    a2 = s0;
    jal(ctx, 0x41BD2Cu, gen::fn_memset_00521408);
    sw(s2, s1, 12);
    sw(s3, s1, 8);
    v0 = addiu(s1, 20);
    sw(v0, s1, 4);
    v0 = 0;
    for (;;) {
        // 0x0041bdfc
        charge(ctx, 3);
        v1 = slt(v0, s3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0041bd50
        charge(ctx, 43);
        v1 = sll(v0, 1);
        v1 = addu(v1, v0);
        v1 = sll(v1, 2);
        v1 = addu(s5, v1);
        lwc1(f0, v1, 0);
        swc1(f0, sp, 0x80);
        lwc1(f0, v1, 4);
        swc1(f0, sp, 0x84);
        lwc1(f0, v1, 8);
        swc1(f0, sp, 0x88);
        a0 = sll(v0, 3);
        v1 = addu(a0, v0);
        a1 = sll(v1, 2);
        lw(v1, s1, 4);
        v1 = addu(v1, a1);
        lwc1(f2, sp, 0x80);
        lwc1(f1, sp, 0x84);
        lwc1(f0, sp, 0x88);
        swc1(f2, v1, 0);
        swc1(f1, v1, 4);
        swc1(f0, v1, 8);
        a0 = addu(s4, a0);
        lwc1(f0, a0, 0);
        lw(v1, s1, 4);
        v1 = addu(v1, a1);
        swc1(f0, v1, 28);
        lwc1(f0, a0, 4);
        lw(v1, s1, 4);
        v1 = addu(v1, a1);
        swc1(f0, v1, 32);
        lw(v1, s1, 4);
        a1 = addu(v1, a1);
        v1 = sll(v0, 2);
        a0 = addu(s6, v1);
        lbu(v1, a0, 0);
        sb(v1, a1, 12);
        lbu(v1, a0, 1);
        sb(v1, a1, 13);
        lbu(v1, a0, 2);
        sb(v1, a1, 14);
        lbu(v1, a0, 3);
        sb(v1, a1, 15);
        v0 = addiu(v0, 1);
    }
    // 0x0041be08
    charge(ctx, 15);
    jal(ctx, 0x41BE08u, gen::fn_sub_4C38C0_004c38c0);
    sw(v0, s1, 16);
    v0 = s1;
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

}  // namespace p3fes::game
