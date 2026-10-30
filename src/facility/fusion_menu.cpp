// The Velvet Room fusion, second batch (slice fusion; fusion.h documents the data): the fclCombine root and its three
// tasks, the root sequence's menu steps, the skill inheritance sub_3D74F0, the list-menu builders and the panels of
// fclCombineList.c. The bodies are p3fes_handgen's (game/include/p3fes/game/hg_cpu.h): register for register and block
// for block as the recompiled bodies -- frame, spills, $ra links, cycle charges and check points -- with each
// function's role, the record offsets and the branch meanings named on top (docs/PHASE5_AGENT_BRIEF.md "Using
// p3fes_handgen"). The heap (RwMalloc / RwFree through 0x960178 / 0x96017C, sub_3C44D0), printf and the H_Cdvd requests
// they reach are paired on the test stand-ins (tests/game/stand_ins.h).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/fusion_menu.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_fclCombine_CreateCombineTasks_003d0310(p3fes::EEContext&);
void fn_fclCombine_UpdateCombineDraw2Task_003d0470(p3fes::EEContext&);
void fn_fclCombine_UpdateCombineDrawTask_003d0400(p3fes::EEContext&);
void fn_fclCombine_UpdateCombineTask_003d03c0(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_nmCmdListAddRow_003c5a40(p3fes::EEContext&);
void fn_nmCmdListSetDrawFunc_003c5e20(p3fes::EEContext&);
void fn_nmCmdListSetPosition_003c6d40(p3fes::EEContext&);
void fn_nmCmdListSetRowDrawFunc_003c5ee0(p3fes::EEContext&);
void fn_nmCmdListSetRowRemoveFunc_003c5f40(p3fes::EEContext&);
void fn_nmCmdListSetUpdateFunc_003c5e80(p3fes::EEContext&);
void fn_nmListAppendNew_003c4910(p3fes::EEContext&);
void fn_nmListFindByWord4_003c4bf0(p3fes::EEContext&);
void fn_nmNodePayloadArea40_003c5480(p3fes::EEContext&);
void fn_nmObjPayloadWord12_003c5460(p3fes::EEContext&);
void fn_nmSequenceAddStep_003c5240(p3fes::EEContext&);
void fn_nmSequenceCreate_003c5180(p3fes::EEContext&);
void fn_nmSequenceDestroy_003c5220(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sub_1052B0_001052b0(p3fes::EEContext&);
void fn_sub_175410_00175410(p3fes::EEContext&);
void fn_sub_176840_00176840(p3fes::EEContext&);
void fn_sub_176990_00176990(p3fes::EEContext&);
void fn_sub_176A30_00176a30(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_3C44D0_003c44d0(p3fes::EEContext&);
void fn_sub_3C45F0_003c45f0(p3fes::EEContext&);
void fn_sub_3C49E0_003c49e0(p3fes::EEContext&);
void fn_sub_3C5470_003c5470(p3fes::EEContext&);
void fn_sub_3C5490_003c5490(p3fes::EEContext&);
void fn_sub_3C58F0_003c58f0(p3fes::EEContext&);
void fn_sub_3C6EE0_003c6ee0(p3fes::EEContext&);
void fn_sub_3C77A0_003c77a0(p3fes::EEContext&);
void fn_sub_3C9B00_003c9b00(p3fes::EEContext&);
void fn_sub_3C9CD0_003c9cd0(p3fes::EEContext&);
void fn_sub_3C9D00_003c9d00(p3fes::EEContext&);
void fn_sub_3C9E00_003c9e00(p3fes::EEContext&);
void fn_sub_3C9E70_003c9e70(p3fes::EEContext&);
void fn_sub_3D02E0_003d02e0(p3fes::EEContext&);
void fn_sub_3D02F0_003d02f0(p3fes::EEContext&);
void fn_sub_3D04B0_003d04b0(p3fes::EEContext&);
void fn_sub_3D04D0_003d04d0(p3fes::EEContext&);
void fn_sub_3D0560_003d0560(p3fes::EEContext&);
void fn_sub_3D0600_003d0600(p3fes::EEContext&);
void fn_sub_3D0610_003d0610(p3fes::EEContext&);
void fn_sub_3D06D0_003d06d0(p3fes::EEContext&);
void fn_sub_3D21D0_003d21d0(p3fes::EEContext&);
void fn_sub_3D2D80_003d2d80(p3fes::EEContext&);
void fn_sub_3D2F00_003d2f00(p3fes::EEContext&);
void fn_sub_3D3B00_003d3b00(p3fes::EEContext&);
void fn_sub_3D3CD0_003d3cd0(p3fes::EEContext&);
void fn_sub_3D4C80_003d4c80(p3fes::EEContext&);
void fn_sub_3D4CD0_003d4cd0(p3fes::EEContext&);
void fn_sub_3D4F30_003d4f30(p3fes::EEContext&);
void fn_sub_3D4F90_003d4f90(p3fes::EEContext&);
void fn_sub_3D53E0_003d53e0(p3fes::EEContext&);
void fn_sub_3D5420_003d5420(p3fes::EEContext&);
void fn_sub_3D54A0_003d54a0(p3fes::EEContext&);
void fn_sub_3D5730_003d5730(p3fes::EEContext&);
void fn_sub_3D5CD0_003d5cd0(p3fes::EEContext&);
void fn_sub_3D6910_003d6910(p3fes::EEContext&);
void fn_sub_3D74F0_003d74f0(p3fes::EEContext&);
void fn_sub_3D8260_003d8260(p3fes::EEContext&);
void fn_sub_3D8830_003d8830(p3fes::EEContext&);
void fn_sub_3D8850_003d8850(p3fes::EEContext&);
void fn_sub_3D9CC0_003d9cc0(p3fes::EEContext&);
void fn_sub_3D9EA0_003d9ea0(p3fes::EEContext&);
void fn_sub_3DA0C0_003da0c0(p3fes::EEContext&);
void fn_sub_3DB580_003db580(p3fes::EEContext&);
void fn_sub_3DD800_003dd800(p3fes::EEContext&);
void fn_sub_3DD9E0_003dd9e0(p3fes::EEContext&);
void fn_sub_3DDA80_003dda80(p3fes::EEContext&);
void fn_sub_3DDB00_003ddb00(p3fes::EEContext&);
void fn_sub_3DE160_003de160(p3fes::EEContext&);
void fn_sub_3DE290_003de290(p3fes::EEContext&);
void fn_sub_3DEDA0_003deda0(p3fes::EEContext&);
void fn_sub_3DFAC0_003dfac0(p3fes::EEContext&);
void fn_sub_3DFAE0_003dfae0(p3fes::EEContext&);
void fn_sub_3DFEB0_003dfeb0(p3fes::EEContext&);
void fn_sub_3DFF00_003dff00(p3fes::EEContext&);
void fn_sub_3E0680_003e0680(p3fes::EEContext&);
void fn_sub_401420_00401420(p3fes::EEContext&);
void fn_sub_4014E0_004014e0(p3fes::EEContext&);
void fn_sub_40C6F0_0040c6f0(p3fes::EEContext&);
void fn_sub_40C9A0_0040c9a0(p3fes::EEContext&);
void fn_sub_40CAD0_0040cad0(p3fes::EEContext&);
void fn_sub_40E360_0040e360(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x003D02F0 sub_3D02F0 -- 32 bytes; frame 0x10: ra sp+0x0
// [fclCombineStart]: a tail wrapper of fclCombine_CreateCombineTasks in its own 16-byte frame (the facility
// entry point the bank manager calls).
void sub_3D02F0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x003d02f0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3D02F8u, gen::fn_fclCombine_CreateCombineTasks_003d0310);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003D0310 fclCombine_CreateCombineTasks -- 168 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// creates the fclCombine root (sub_3D04D0) and the three Velvet Room tasks: "fclCombine"
// (priority 10, update fclCombine_UpdateCombineTask; the task is kept at root payload +204), "fclCombineDraw" (6326) and
// "fclCombineDraw2" (4207) as its children (kwlnTaskCreate(parent, name, priority, update, 0, 0)).
void fclCombine_CreateCombineTasks(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d0310
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3D031Cu, gen::fn_sub_3D04D0_003d04d0);
    s0 = v0;
    a0 = 0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 17328);  // "fclCombine"
    a2 = 10;
    a3 = 0x3D0000;
    a3 = addiu(a3, 960);  // &fclCombine_UpdateCombineTask
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x3D0348u, gen::fn_kwlnTaskCreate_00194b20);
    sw(v0, s0, 204);
    a0 = v0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 17344);  // "fclCombineDraw"
    a2 = 6326;
    a3 = 0x3D0000;
    a3 = addiu(a3, 1024);  // &fclCombine_UpdateCombineDrawTask
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x3D0374u, gen::fn_kwlnTaskCreate_00194b20);
    a0 = v0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 17360);  // "fclCombineDraw2"
    a2 = 4207;
    a3 = 0x3D0000;
    a3 = addiu(a3, 1136);  // &fclCombine_UpdateCombineDraw2Task
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x3D039Cu, gen::fn_kwlnTaskCreate_00194b20);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003D03C0 fclCombine_UpdateCombineTask -- 56 bytes; frame 0x10: ra sp+0x0
// the "fclCombine" update: runs the root sequence (sub_3D0610); -1 (end the task) when it
// finished, else 0.
void fclCombine_UpdateCombineTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d03c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3D03C8u, gen::fn_sub_3D0610_003d0610);
    if (v0 == 0) {
        // 0x003d03e4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003d03d8
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x003d03e8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003D0400 fclCombine_UpdateCombineDrawTask -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// the "fclCombineDraw" update: the root payload (nmObjPayloadWord12(root)) gets flag bit 1
// while the sequence steps draw (sub_3D21D0 = nmSequenceCallAll36) and the payload's element list (+212) runs the element
// drawer sub_3D1DF0 (sub_3E0680); returns 0.
void fclCombine_UpdateCombineDrawTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d0400
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, -18028);  // 0x7CE684: the fclCombine root (sequence object)
    jal(ctx, 0x3D0410u, gen::fn_nmObjPayloadWord12_003c5460);
    s0 = v0;
    jal(ctx, 0x3D041Cu, gen::fn_sub_3D21D0_003d21d0);
    lw(v0, s0, 0);
    v0 = v0 | 0x2;
    sw(v0, s0, 0);
    lw(a0, s0, 212);
    a1 = 0x3D0000;
    a1 = addiu(a1, 7664);  // &sub_3D1DF0
    a2 = 0;
    jal(ctx, 0x3D0440u, gen::fn_sub_3E0680_003e0680);
    lw(v1, s0, 0);
    v0 = si(-3);
    v0 = v1 & v0;
    sw(v0, s0, 0);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003D0470 fclCombine_UpdateCombineDraw2Task -- 64 bytes; frame 0x10: ra sp+0x0
// the "fclCombineDraw2" update: the element drawer sub_3D1DF0 over the root payload's element
// list (+212) only; returns 0.
void fclCombine_UpdateCombineDraw2Task(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d0470
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, -18028);  // 0x7CE684: the fclCombine root (sequence object)
    jal(ctx, 0x3D047Cu, gen::fn_nmObjPayloadWord12_003c5460);
    lw(a0, v0, 212);
    a1 = 0x3D0000;
    a1 = addiu(a1, 7664);  // &sub_3D1DF0
    a2 = 0;
    jal(ctx, 0x3D0494u, gen::fn_sub_3E0680_003e0680);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003D04B0 sub_3D04B0 -- 32 bytes; frame 0x10: ra sp+0x0
// [fclCombineIsActive2]: a tail wrapper of sub_3D0600 (root != 0).
void sub_3D04B0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x003d04b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3D04B8u, gen::fn_sub_3D0600_003d0600);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003D04D0 sub_3D04D0 -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCombineCreateRoot]: when gp - 18028 is empty, creates the root sequence (nmSequenceCreate(sub_3D2200,
// 224): the sequence function sub_3D2200 drives the menu steps, 224 payload bytes), sets payload +8 = 1, gives the
// payload an element list (+212, sub_3DFEB0) and builds the stock list at payload +44 from the hero's personas
// (sub_3D5CD0); returns the payload, or 0 when a root already exists.
void sub_3D04D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d04d0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -18028);  // 0x7CE684: the fclCombine root (sequence object)
    if (v0 == 0) {
        // 0x003d04f4
        charge(ctx, 20);
        a0 = 0x3D0000;
        a0 = addiu(a0, 8704);  // &sub_3D2200
        a1 = 224;
        jal(ctx, 0x3D0500u, gen::fn_nmSequenceCreate_003c5180);
        sw(v0, gp, -18028);  // 0x7CE684: the fclCombine root (sequence object)
        a0 = v0;
        jal(ctx, 0x3D0510u, gen::fn_nmObjPayloadWord12_003c5460);
        s0 = v0;
        v1 = 1;
        sw(v1, v0, 8);
        a0 = s0;
        jal(ctx, 0x3D0528u, gen::fn_sub_3DFEB0_003dfeb0);
        sw(v0, s0, 212);
        a0 = addiu(s0, 44);
        jal(ctx, 0x3D0538u, gen::fn_sub_3D5CD0_003d5cd0);
        v0 = s0;
    } else {
        // 0x003d04e8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003d0544 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003D0560 sub_3D0560 -- 156 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCombineDestroyRoot]: with a root: the facility text / message cleanup (sub_40E360, sub_3C77A0), the
// file requests of the payload released (H_Cdvd_Destroy: +188 when set -- then cleared --, else +196 and +216), the
// element list (+212, sub_3DFF00) and the sequence itself (nmSequenceDestroy); the root word is cleared either way.
void sub_3D0560(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d0560
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, -18028);  // 0x7CE684: the fclCombine root (sequence object)
    if (a0 != 0) {
        // 0x003d0578
        charge(ctx, 10);
        jal(ctx, 0x3D0578u, gen::fn_nmObjPayloadWord12_003c5460);
        s0 = v0;
        jal(ctx, 0x3D0584u, gen::fn_sub_40E360_0040e360);
        jal(ctx, 0x3D058Cu, gen::fn_sub_3C77A0_003c77a0);
        lw(a0, s0, 188);
        if (a0 == 0) {
            // 0x003d05b4
            charge(ctx, 6);
            lw(a0, s0, 196);
            jal(ctx, 0x3D05B8u, gen::fn_H_Cdvd_Destroy_00100ec0);
            lw(a0, s0, 216);
            jal(ctx, 0x3D05C4u, gen::fn_H_Cdvd_Destroy_00100ec0);
        } else {
            // 0x003d05a0
            charge(ctx, 5);
            jal(ctx, 0x3D05A0u, gen::fn_H_Cdvd_Destroy_00100ec0);
            sw(zero, s0, 188);
        }
        // 0x003d05cc
        charge(ctx, 6);
        lw(a0, s0, 212);
        jal(ctx, 0x3D05D0u, gen::fn_sub_3DFF00_003dff00);
        lw(a0, gp, -18028);  // 0x7CE684: the fclCombine root (sequence object)
        jal(ctx, 0x3D05DCu, gen::fn_nmSequenceDestroy_003c5220);
    }
    // 0x003d05e4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    sw(zero, gp, -18028);  // 0x7CE684: the fclCombine root (sequence object)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003D0610 sub_3D0610 -- 184 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCombineUpdateRoot]: one frame of the root sequence (sub_3C5490 = nmSequenceUpdate); when it ended,
// the cleanup of sub_3D0560 and the root word cleared, returns 1; else 0.
void sub_3D0610(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d0610
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, -18028);  // 0x7CE684: the fclCombine root (sequence object)
    jal(ctx, 0x3D0620u, gen::fn_sub_3C5490_003c5490);
    if (v0 == 0) {
        // 0x003d06b0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003d0630
        charge(ctx, 11);
        lw(a0, gp, -18028);  // 0x7CE684: the fclCombine root (sequence object)
        jal(ctx, 0x3D0634u, gen::fn_nmObjPayloadWord12_003c5460);
        s0 = v0;
        jal(ctx, 0x3D0640u, gen::fn_sub_40E360_0040e360);
        jal(ctx, 0x3D0648u, gen::fn_sub_3C77A0_003c77a0);
        lw(a0, s0, 188);
        if (a0 == 0) {
            // 0x003d0670
            charge(ctx, 6);
            lw(a0, s0, 196);
            jal(ctx, 0x3D0674u, gen::fn_H_Cdvd_Destroy_00100ec0);
            lw(a0, s0, 216);
            jal(ctx, 0x3D0680u, gen::fn_H_Cdvd_Destroy_00100ec0);
        } else {
            // 0x003d065c
            charge(ctx, 5);
            jal(ctx, 0x3D065Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
            sw(zero, s0, 188);
        }
        // 0x003d0688
        charge(ctx, 10);
        lw(a0, s0, 212);
        jal(ctx, 0x3D068Cu, gen::fn_sub_3DFF00_003dff00);
        lw(a0, gp, -18028);  // 0x7CE684: the fclCombine root (sequence object)
        jal(ctx, 0x3D0698u, gen::fn_nmSequenceDestroy_003c5220);
        sw(zero, gp, -18028);  // 0x7CE684: the fclCombine root (sequence object)
        v0 = 1;
    }
    // 0x003d06b4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003D2F00 sub_3D2F00 -- 264 bytes; frame 0x70: ra sp+0x0
// [fclCombineRootListStart]: the debug trace (printf "[%s:%d]" with "fclCombine.c" 1163, printf
// "fclCombineRootListStart\n", the log formatter sub_1052B0), then adds step 1 of the 36-byte descriptor 0x6A46E0 (copied
// twice through the frame) to the root sequence (nmSequenceAddStep(root, 1, desc, 0, 0)) and returns that step's payload
// area (nmNodePayloadArea40).
void sub_3D2F00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003d2f00
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x0);
    v1 = addiu(sp, 0x40);
    v0 = 36;
    if (v1 != 0) {
        for (;;) {
            // 0x003d2f18
            charge(ctx, 7);
            sb(zero, v1, 0);
            v1 = addiu(v1, 1);
            v0 = addiu(v0, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x003d2f34
    charge(ctx, 4);
    a1 = 0x6A0000;
    a1 = addiu(a1, 18144);  // &0x6A46E0
    a0 = addiu(sp, 0x10);
    v1 = 2;
    for (;;) {
        // 0x003d2f44
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003d2f60
    charge(ctx, 5);
    lwc1(f0, a1, 0);
    swc1(f0, a0, 0);
    a1 = addiu(sp, 0x10);
    a0 = addiu(sp, 0x40);
    v1 = 2;
    for (;;) {
        // 0x003d2f74
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003d2f90
    charge(ctx, 30);
    lwc1(f0, a1, 0);
    swc1(f0, a0, 0);
    a0 = addiu(gp, -21912);  // "[%s:%d]"
    a1 = 0x6A0000;
    a1 = addiu(a1, 17992);  // "fclCombine.c"
    a2 = 1163;
    jal(ctx, 0x3D2FA8u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 18192);  // "fclCombineRootListStart\n"
    jal(ctx, 0x3D2FB8u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 18192);  // "fclCombineRootListStart\n"
    jal(ctx, 0x3D2FC8u, gen::fn_sub_1052B0_001052b0);
    lw(a0, gp, -18028);  // 0x7CE684: the fclCombine root (sequence object)
    a1 = 1;
    a2 = addiu(sp, 0x40);
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x3D2FE4u, gen::fn_nmSequenceAddStep_003c5240);
    a0 = v0;
    jal(ctx, 0x3D2FF0u, gen::fn_nmNodePayloadArea40_003c5480);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003D4CD0 sub_3D4CD0 -- 272 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCombineSnapshotSelection]: $a0 the root payload, $a1 a 24-byte record. Clears the record; +0 bit 0 =
// payload flag bit 1, +4 = payload +8 (u16), +6 = the list menu's (+924) u16 +34, then +8.. the persona ids of the list's
// selected personas (K_Assert 2102 for an empty slot; the null read continues as in retail).
void sub_3D4CD0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d4cd0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    if (s2 == 0) {
        // 0x003d4cf8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 17992);  // "fclCombine.c"
        a1 = 2095;
        jal(ctx, 0x3D4D04u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003d4d0c
    charge(ctx, 9);
    a0 = s2;
    a1 = 0;
    a2 = 24;
    jal(ctx, 0x3D4D18u, gen::fn_memset_00521408);
    lw(v1, s3, 0);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x003d4d30
        charge(ctx, 3);
        lw(v1, s2, 0);
        v1 = v1 | 0x1;
        sw(v1, s2, 0);
    }
    // 0x003d4d3c
    charge(ctx, 8);
    lw(v1, s3, 8);
    sh(v1, s2, 4);
    lw(v1, s3, 924);
    lhu(v1, v1, 34);
    sh(v1, s2, 6);
    s1 = 0;
    for (;;) {
        // 0x003d4dac
        charge(ctx, 5);
        lw(a0, s3, 924);
        lw(v1, a0, 12);
        v1 = slt(s1, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003d4d5c
        charge(ctx, 6);
        s0 = sll(s1, 2);
        lw(v1, a0, 24);
        v1 = addu(v1, s0);
        lw(v1, v1, 0);
        if (v1 == 0) {
            // 0x003d4d74
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 17992);  // "fclCombine.c"
            a1 = 2102;
            jal(ctx, 0x3D4D80u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x003d4d88
        charge(ctx, 9);
        lw(v1, s3, 924);
        lw(v1, v1, 24);
        v1 = addu(v1, s0);
        lw(v1, v1, 0);
        lhu(a0, v1, 2);
        v1 = sll(s1, 1);
        v1 = addu(s2, v1);
        sh(a0, v1, 8);
        s1 = addiu(s1, 1);
    }
    // 0x003d4dc0
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003D74F0 sub_3D74F0 -- 1344 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCombineInheritSkills]: $a0 the fused persona, $a1 the ingredient personas, $a2 their count. Collects
// into a fresh nm list (sub_3C44D0) every ingredient skill the result does not have (sub_176990) and whose inheritance
// weight is non-zero: weight = 10 * w / d, w = the s16 at 0x6A48F0 + 2 * (19 * table[result].byte10 + element) (the
// skill's element from SKILL.TBL section 0, -1 -> 18), d = the per-skill divisor byte of the scenario table
// (0x6A4BA0 / 0x6A4E10, sub_17D800); the number of skills to pass on comes from the 9-step table 0x6A48D0 (skill count ->
// slots) capped by the free slots (8 - sub_176A30); then that many weighted draws (RpRandom) over a RwMalloc'd weight
// array add the picked skills (sub_176840) and remove them from the list; the array and the list are freed.
// K_Assert 934 / 903 / 994 on bad input continue.
void sub_3D74F0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x003d74f0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s6 = a1;
    s7 = a2;
    if (s4 != 0) {
        // 0x003d7530
        charge(ctx, 2);
        if (s6 == 0) {
            goto L_003d7540;
        }
        // 0x003d7538
        charge(ctx, 2);
        if (i64(s7) <= 0) {
            goto L_003d7540;
        }
        goto L_003d7554;
    }
L_003d7540:
    charge(ctx, 5);
    a0 = 0x6A0000;
    a0 = addiu(a0, 24432);  // "fclCombineMisc.c"
    a1 = 934;
    jal(ctx, 0x3D754Cu, gen::fn_sub_19D3F0_0019d3f0);
L_003d7554:
    charge(ctx, 11);
    s2 = 0;
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x3D7568u, gen::fn_sub_3C44D0_003c44d0);
    s1 = v0;
    s3 = 0;
    for (;;) {
        // 0x003d7708
        charge(ctx, 3);
        v0 = slt(s3, s7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003d7580
        charge(ctx, 6);
        s5 = 0;
        v0 = sll(s3, 2);
        v0 = addu(s6, v0);
        sq(v0, sp, 0xA0);
        for (;;) {
            // 0x003d76f8
            charge(ctx, 3);
            v0 = slti(s5, 8);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003d7598
            charge(ctx, 7);
            v1 = sll(s5, 1);
            lq(v0, sp, 0xA0);
            lw(v0, v0, 0);
            v0 = addu(v0, v1);
            lhu(s0, v0, 12);
            if (s0 != 0) {
                // 0x003d75b4
                charge(ctx, 8);
                s2 = addiu(s2, 1);
                a0 = s4;
                a1 = s0;
                jal(ctx, 0x3D75C0u, gen::fn_sub_176990_00176990);
                v1 = si(-1);
                if (v0 == v1) {
                    // 0x003d75d4
                    charge(ctx, 7);
                    a0 = s1;
                    a1 = addiu(s1, 4);
                    a2 = s0;
                    jal(ctx, 0x3D75E0u, gen::fn_nmListFindByWord4_003c4bf0);
                    if (v0 == 0) {
                        // 0x003d75f0
                        charge(ctx, 2);
                        if (s4 == 0) {
                            // 0x003d75f8
                            charge(ctx, 5);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, 24432);  // "fclCombineMisc.c"
                            a1 = 903;
                            jal(ctx, 0x3D7604u, gen::fn_sub_19D3F0_0019d3f0);
                        }
                        // 0x003d760c
                        charge(ctx, 7);
                        v1 = sll(s0, 1);
                        lw(v0, gp, -18684);  // gBtlSkillElementTbl
                        v0 = addu(v0, v1);
                        lb(v0, v0, 0);
                        v1 = si(-1);
                        if (v0 == v1) {
                            // 0x003d7628
                            charge(ctx, 1);
                            v0 = 18;
                        }
                        // 0x003d762c
                        charge(ctx, 22);
                        lhu(a0, s4, 2);
                        v1 = sll(a0, 3);
                        v1 = subu(v1, a0);
                        a0 = sll(v1, 1);
                        lw(v1, gp, -18640);  // 0x7CE420: the persona table
                        v1 = addu(v1, a0);
                        lhu(a0, v1, 10);
                        v1 = sll(a0, 3);
                        v1 = addu(v1, a0);
                        v1 = sll(v1, 1);
                        v1 = addu(v1, a0);
                        a0 = sll(v1, 1);
                        v1 = 0x6A0000;
                        v1 = addiu(v1, 18672);  // &0x6A48F0
                        v1 = addu(v1, a0);
                        v0 = sll(v0, 1);
                        v0 = addu(v0, v1);
                        lh(fp, v0, 0);
                        jal(ctx, 0x3D7674u, gen::fn_sub_17D800_0017d800);
                        if (v0 == 0) {
                            // 0x003d769c
                            charge(ctx, 4);
                            v0 = 0x6A0000;
                            v0 = addiu(v0, 19360);  // &0x6A4BA0
                            v0 = addu(v0, s0);
                            lb(v1, v0, 0);
                        } else {
                            // 0x003d7684
                            charge(ctx, 6);
                            v0 = 0x6A0000;
                            v0 = addiu(v0, 19984);  // &0x6A4E10
                            v0 = addu(v0, s0);
                            lb(v1, v0, 0);
                        }
                        // 0x003d76ac
                        charge(ctx, 2);
                        if (v1 != 0) {
                            // 0x003d76c0
                            charge(ctx, 5);
                            v0 = sll(fp, 2);
                            v0 = addu(v0, fp);
                            v0 = sll(v0, 1);
                            div(v0, v1);
                            mflo(v0);
                        } else {
                            // 0x003d76b4
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x003d76d4
                        charge(ctx, 2);
                        if (v0 != 0) {
                            // 0x003d76dc
                            charge(ctx, 6);
                            a0 = s1;
                            a1 = 0;
                            a2 = 0;
                            jal(ctx, 0x3D76E8u, gen::fn_nmListAppendNew_003c4910);
                            sw(s0, v0, 4);
                        }
                    }
                }
            }
            // 0x003d76f4
            charge(ctx, 1);
            s5 = addiu(s5, 1);
        }
        // 0x003d7704
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x003d7714
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x003d771c
        charge(ctx, 3);
        lhu(v0, s1, 16);
        if (v0 == 0) {
            goto L_003d7728;
        }
        // 0x003d773c
        charge(ctx, 5);
        a1 = 8;
        v1 = 0x6A0000;
        v1 = addiu(v1, 18640);  // &0x6A48D0
        for (;;) {
            // 0x003d7784
            charge(ctx, 2);
            if (i64(a1) < 0) {
                break;
            }
            backedge(ctx);
            // 0x003d7750
            charge(ctx, 6);
            a0 = sll(a1, 1);
            v0 = addu(v1, a0);
            lb(v0, v0, 0);
            at = slt(s2, v0);
            if (at == 0) {
                goto L_003d7768_30;
            }
            // 0x003d7780
            charge(ctx, 1);
            a1 = addiu(a1, -1);
        }
        // 0x003d778c
        charge(ctx, 1);
        s0 = 0;
    L_003d7790:
        charge(ctx, 7);
        a0 = s4;
        jal(ctx, 0x3D7794u, gen::fn_sub_176A30_00176a30);
        v1 = 8;
        v0 = subu(v1, v0);
        if (v0 != 0) {
            // 0x003d77c0
            charge(ctx, 3);
            at = slt(v0, s0);
            if (at != 0) {
                // 0x003d77cc
                charge(ctx, 1);
                s0 = v0;
            }
            // 0x003d77d0
            charge(ctx, 9);
            a0 = sll(s2, 2);
            a1 = 0x40000;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178
            jalr(ctx, 0x3D77E0u, v0.u());
            s7 = v0;
            for (;;) {
            L_003d79d4:
                charge(ctx, 2);
                if (s0 != 0) {
                    backedge(ctx);
                    // 0x003d77f4
                    charge(ctx, 5);
                    s3 = 0;
                    s6 = 0;
                    lw(s2, s1, 4);
                    if (s2 != 0) {
                        // 0x003d7808
                        charge(ctx, 2);
                        for (;;) {
                            // 0x003d7934
                            charge(ctx, 2);
                            if (s2 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x003d7810
                            charge(ctx, 3);
                            lhu(s5, s2, 4);
                            if (s4 == 0) {
                                // 0x003d781c
                                charge(ctx, 5);
                                a0 = 0x6A0000;
                                a0 = addiu(a0, 24432);  // "fclCombineMisc.c"
                                a1 = 903;
                                jal(ctx, 0x3D7828u, gen::fn_sub_19D3F0_0019d3f0);
                            }
                            // 0x003d7830
                            charge(ctx, 8);
                            s5 = s5 & 0xFFFF;
                            v1 = sll(s5, 1);
                            lw(v0, gp, -18684);  // gBtlSkillElementTbl
                            v0 = addu(v0, v1);
                            lb(v0, v0, 0);
                            v1 = si(-1);
                            if (v0 == v1) {
                                // 0x003d7850
                                charge(ctx, 1);
                                v0 = 18;
                            }
                            // 0x003d7854
                            charge(ctx, 22);
                            lhu(a0, s4, 2);
                            v1 = sll(a0, 3);
                            v1 = subu(v1, a0);
                            a0 = sll(v1, 1);
                            lw(v1, gp, -18640);  // 0x7CE420: the persona table
                            v1 = addu(v1, a0);
                            lhu(a0, v1, 10);
                            v1 = sll(a0, 3);
                            v1 = addu(v1, a0);
                            v1 = sll(v1, 1);
                            v1 = addu(v1, a0);
                            a0 = sll(v1, 1);
                            v1 = 0x6A0000;
                            v1 = addiu(v1, 18672);  // &0x6A48F0
                            v1 = addu(v1, a0);
                            v0 = sll(v0, 1);
                            v0 = addu(v0, v1);
                            lh(fp, v0, 0);
                            jal(ctx, 0x3D789Cu, gen::fn_sub_17D800_0017d800);
                            if (v0 == 0) {
                                // 0x003d78c4
                                charge(ctx, 4);
                                v0 = 0x6A0000;
                                v0 = addiu(v0, 19360);  // &0x6A4BA0
                                v0 = addu(v0, s5);
                                lb(v1, v0, 0);
                            } else {
                                // 0x003d78ac
                                charge(ctx, 6);
                                v0 = 0x6A0000;
                                v0 = addiu(v0, 19984);  // &0x6A4E10
                                v0 = addu(v0, s5);
                                lb(v1, v0, 0);
                            }
                            // 0x003d78d4
                            charge(ctx, 2);
                            if (v1 != 0) {
                                // 0x003d78e8
                                charge(ctx, 5);
                                v0 = sll(fp, 2);
                                v0 = addu(v0, fp);
                                v0 = sll(v0, 1);
                                div(v0, v1);
                                mflo(v1);
                            } else {
                                // 0x003d78dc
                                charge(ctx, 3);
                                v1 = 0;
                            }
                            // 0x003d78fc
                            charge(ctx, 5);
                            v0 = sll(s3, 2);
                            s5 = addu(s7, v0);
                            sw(v1, s5, 0);
                            if (v1 == 0) {
                                // 0x003d7910
                                charge(ctx, 5);
                                a0 = 0x6A0000;
                                a0 = addiu(a0, 24432);  // "fclCombineMisc.c"
                                a1 = 994;
                                jal(ctx, 0x3D791Cu, gen::fn_sub_19D3F0_0019d3f0);
                            }
                            // 0x003d7924
                            charge(ctx, 4);
                            lw(v0, s5, 0);
                            s6 = addu(s6, v0);
                            s3 = addiu(s3, 1);
                            lw(s2, s2, 16);
                        }
                        // 0x003d793c
                        charge(ctx, 15);
                        s5 = 0;
                        s3 = 0;
                        jal(ctx, 0x3D7944u, gen::fn_sub_488F30_00488f30);
                        v1 = 0xFFFF;
                        divu(v0, v1);
                        mfhi(v0);
                        mult(v0, s6, v0);
                        divu(v0, v1);
                        mflo(v1);
                        lw(s2, s1, 4);
                        for (;;) {
                            // 0x003d79cc
                            charge(ctx, 2);
                            if (s2 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x003d7978
                            charge(ctx, 8);
                            v0 = sll(s5, 2);
                            v0 = addu(s7, v0);
                            lw(v0, v0, 0);
                            s3 = addu(s3, v0);
                            lhu(a1, s2, 4);
                            at = slt(v1, s3);
                            if (at != 0) {
                                goto L_003d7998_57;
                            }
                            // 0x003d79c4
                            charge(ctx, 2);
                            s5 = addiu(s5, 1);
                            lw(s2, s2, 16);
                        }
                        continue;
                    }
                }
                break;
            }
            // 0x003d79dc
            charge(ctx, 8);
            a0 = s1;
            jal(ctx, 0x3D79E0u, gen::fn_sub_3C45F0_003c45f0);
            a0 = s7;
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x3D79F4u, v0.u());
        } else {
            // 0x003d77ac
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x3D77B0u, gen::fn_sub_3C45F0_003c45f0);
        }
        // 0x003d79fc (the shared epilogue, written out on this path)
        charge(ctx, 13);
        ld(ra, sp, 0x90);
        lq(fp, sp, 0x80);
        lq(s7, sp, 0x70);
        lq(s6, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0xB0);
        return;
    }
L_003d7728:
    charge(ctx, 5);
    a0 = s1;
    jal(ctx, 0x3D772Cu, gen::fn_sub_3C45F0_003c45f0);
    // 0x003d79fc (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
    return;
L_003d7768_30:
    charge(ctx, 6);
    v0 = 0x6A0000;
    v0 = addiu(v0, 18641);  // &0x6A48D1
    v0 = addu(v0, a0);
    lb(s0, v0, 0);
    goto L_003d7790;
L_003d7998_57:
    charge(ctx, 11);
    a0 = s4;
    jal(ctx, 0x3D799Cu, gen::fn_sub_176840_00176840);
    s0 = addiu(s0, -1);
    a0 = s1;
    a1 = addiu(s1, 4);
    a2 = s2;
    jal(ctx, 0x3D79B4u, gen::fn_sub_3C49E0_003c49e0);
    goto L_003d79d4;
}

// 0x003DEDA0 sub_3DEDA0 -- 224 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclElemDrawAll]: $a0 an element holder. With an owner state (sub_3DFAC0), draws (sub_3DFAE0) the elements
// from the first node up to the state's current node (+4), then from the list's last node back to it, then the current
// one last (so it is on top).
void sub_3DEDA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003deda0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 != 0) {
        // 0x003dedc4
        charge(ctx, 6);
        lw(s2, s0, 4);
        jal(ctx, 0x3DEDC8u, gen::fn_sub_3DFAC0_003dfac0);
        s1 = v0;
        if (s1 != 0) {
            // 0x003deddc
            charge(ctx, 3);
            lw(s3, s2, 4);
            for (;;) {
                // 0x003dee08
                charge(ctx, 2);
                if (s3 != 0) {
                    backedge(ctx);
                    // 0x003dede8
                    charge(ctx, 3);
                    lw(v1, s1, 4);
                    if (s3 != v1) {
                        // 0x003dedf4
                        charge(ctx, 5);
                        lw(a1, s3, 20);
                        a0 = s0;
                        jal(ctx, 0x3DEDFCu, gen::fn_sub_3DFAE0_003dfae0);
                        lw(s3, s3, 16);
                        continue;
                    }
                }
                break;
            }
            // 0x003dee10
            charge(ctx, 3);
            lw(s2, s2, 8);
            for (;;) {
                // 0x003dee3c
                charge(ctx, 2);
                if (s2 != 0) {
                    backedge(ctx);
                    // 0x003dee1c
                    charge(ctx, 3);
                    lw(v1, s1, 4);
                    if (s2 != v1) {
                        // 0x003dee28
                        charge(ctx, 5);
                        lw(a1, s2, 20);
                        a0 = s0;
                        jal(ctx, 0x3DEE30u, gen::fn_sub_3DFAE0_003dfae0);
                        lw(s2, s2, 12);
                        continue;
                    }
                }
                break;
            }
            // 0x003dee44
            charge(ctx, 3);
            lw(v1, s1, 4);
            if (v1 != 0) {
                // 0x003dee50
                charge(ctx, 4);
                lw(a1, v1, 20);
                a0 = s0;
                jal(ctx, 0x3DEE58u, gen::fn_sub_3DFAE0_003dfae0);
            }
        }
    }
    // 0x003dee60 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003D9CC0 sub_3D9CC0 -- 468 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCombineListBuildRows]: $a0 a list menu (fusion.h). One row per stock entry (+284; 12 entries): a
// persona gets a row (nmCmdListAddRow keyed by the row count + 1) whose record holds the persona (+8) and, for the
// normal-fusion list (+4 == 0), its partner mask (sub_3D8260); an empty slot below the hero's slot count gets an empty
// row; every row gets an element list (+96, sub_3DFEB0). Then the window callbacks (update sub_3DB5E0, draw
// sub_3DC210, row draw sub_3DD800, row remove sub_3D9C90), position (0, 0), open (sub_3C6EE0); list +8 = 3.
void sub_3D9CC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d9cc0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = addiu(s5, 284);
    lw(s3, a0, 20);
    s0 = 0;
    for (;;) {
        // 0x003d9de4
        charge(ctx, 3);
        v0 = slti(s0, 12);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003d9cfc
        charge(ctx, 8);
        v0 = sll(s0, 1);
        v0 = addu(v0, s0);
        v0 = sll(v0, 2);
        s6 = addu(s4, v0);
        s2 = 0;
        lw(v0, s6, 4);
        if (v0 != 0) {
            // 0x003d9d1c
            charge(ctx, 3);
            lhu(v0, v0, 2);
            if (v0 == 0) {
                goto L_003d9d80;
            }
            // 0x003d9d28
            charge(ctx, 13);
            lhu(v0, s3, 16);
            a1 = addiu(v0, 1);
            a0 = s3;
            a2 = 140;
            a3 = 0;
            jal(ctx, 0x3D9D3Cu, gen::fn_nmCmdListAddRow_003c5a40);
            s2 = v0;
            lw(v0, v0, 20);
            lw(s1, v0, 28);
            lw(v0, s5, 4);
            if (v0 == 0) {
                // 0x003d9d5c
                charge(ctx, 5);
                a0 = s4;
                a1 = s0;
                jal(ctx, 0x3D9D64u, gen::fn_sub_3D8260_003d8260);
                sw(v0, s1, 4);
            }
            // 0x003d9d70
            charge(ctx, 4);
            lw(v0, s6, 4);
            sw(v0, s1, 8);
            goto L_003d9dc8;
        }
    L_003d9d80:
        charge(ctx, 6);
        jal(ctx, 0x3D9D80u, gen::fn_sub_175410_00175410);
        v0 = v0 & 0xFFFF;
        at = slt(s0, v0);
        if (at != 0) {
            // 0x003d9d98
            charge(ctx, 12);
            lhu(v0, s3, 16);
            a1 = addiu(v0, 1);
            a0 = s3;
            a2 = 140;
            a3 = 0;
            jal(ctx, 0x3D9DACu, gen::fn_nmCmdListAddRow_003c5a40);
            s2 = v0;
            lw(v0, v0, 20);
            lw(s1, v0, 28);
            sw(zero, s1, 4);
            sw(zero, s1, 8);
        }
    L_003d9dc8:
        charge(ctx, 2);
        if (s2 != 0) {
            // 0x003d9dd0
            charge(ctx, 4);
            a0 = s5;
            jal(ctx, 0x3D9DD4u, gen::fn_sub_3DFEB0_003dfeb0);
            sw(v0, s1, 96);
        }
        // 0x003d9de0
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x003d9df0
    charge(ctx, 41);
    a0 = s3;
    a1 = 0x3E0000;
    a1 = addiu(a1, -18976);  // &sub_3DB5E0
    jal(ctx, 0x3D9DFCu, gen::fn_nmCmdListSetUpdateFunc_003c5e80);
    a0 = s3;
    a1 = 0x3E0000;
    a1 = addiu(a1, -15856);  // &sub_3DC210
    jal(ctx, 0x3D9E10u, gen::fn_nmCmdListSetDrawFunc_003c5e20);
    a0 = s3;
    a1 = 0x3E0000;
    a1 = addiu(a1, -10240);  // &sub_3DD800
    jal(ctx, 0x3D9E24u, gen::fn_nmCmdListSetRowDrawFunc_003c5ee0);
    a0 = s3;
    a1 = 0x3E0000;
    a1 = addiu(a1, -25456);  // &sub_3D9C90
    jal(ctx, 0x3D9E38u, gen::fn_nmCmdListSetRowRemoveFunc_003c5f40);
    a0 = s3;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x3D9E4Cu, gen::fn_nmCmdListSetPosition_003c6d40);
    a0 = s3;
    jal(ctx, 0x3D9E58u, gen::fn_sub_3C6EE0_003c6ee0);
    v1 = 3;
    sh(v1, s5, 8);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x003D9EA0 sub_3D9EA0 -- 540 bytes; frame 0xD0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCombineListBuildRecipes]: $a0 a list menu. One row per special recipe of the list's category (+4;
// sub_3D8830, the index runs to the count inclusive -- the last one is empty) that sub_3D5730 matches against the stock:
// the row record keeps the 40-byte match (+100), and when the match is incomplete (flag bit 0) a preview fusion of the
// matched personas (sub_3D6910 into +16; +8 points at it); every row gets an element list (+96). Then the window
// callbacks (update sub_3DB5E0, draw sub_3DEB80, row draw sub_3DEC00, row remove sub_3D9C90), position, open; +8 = 3.
void sub_3D9EA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d9ea0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s6 = addiu(s5, 284);
    lw(s4, a0, 20);
    lw(s2, a0, 4);
    v1 = 0;
    for (;;) {
        // 0x003d9ee4
        charge(ctx, 6);
        v0 = slti(v1, 12);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003d9ee0
        charge(ctx, 1);
        v1 = addiu(v1, 1);
    }
    // 0x003d9efc
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x003da000
        charge(ctx, 6);
        a0 = s2;
        jal(ctx, 0x3DA004u, gen::fn_sub_3D8830_003d8830);
        at = slt(v0, s1);
        if (at != 0) {
            break;
        }
        backedge(ctx);
        // 0x003d9f08
        charge(ctx, 8);
        a0 = addiu(sp, 0x80);
        a1 = s2;
        a2 = s1;
        a3 = s6;
        jal(ctx, 0x3D9F18u, gen::fn_sub_3D5730_003d5730);
        if (v0 != 0) {
            // 0x003d9f28
            charge(ctx, 20);
            lhu(v0, s4, 16);
            a1 = addiu(v0, 1);
            a0 = s4;
            a2 = 140;
            a3 = 0;
            jal(ctx, 0x3D9F3Cu, gen::fn_nmCmdListAddRow_003c5a40);
            lw(v0, v0, 20);
            lw(s0, v0, 28);
            sw(zero, s0, 4);
            a0 = addiu(s0, 100);
            a1 = addiu(sp, 0x80);
            a2 = 40;
            jal(ctx, 0x3D9F5Cu, gen::fn_memcpy_00521250);
            s3 = 0;
            lw(v0, sp, 0x80);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x003d9f78
                charge(ctx, 8);
                a0 = addiu(sp, 0xB0);
                a1 = 0;
                a2 = 4;
                jal(ctx, 0x3D9F84u, gen::fn_memset_00521408);
                a0 = 0;
                for (;;) {
                    // 0x003d9fc4
                    charge(ctx, 3);
                    v0 = slti(a0, 8);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003d9f98
                    charge(ctx, 6);
                    v0 = sll(a0, 2);
                    v0 = addu(v0, sp);
                    v0 = addiu(v0, 128);
                    lw(v1, v0, 8);
                    if (v1 != 0) {
                        // 0x003d9fb0
                        charge(ctx, 4);
                        v0 = sll(s3, 2);
                        v0 = addu(v0, sp);
                        sw(v1, v0, 176);
                        s3 = addiu(s3, 1);
                    }
                    // 0x003d9fc0
                    charge(ctx, 1);
                    a0 = addiu(a0, 1);
                }
                // 0x003d9fd0
                charge(ctx, 7);
                a0 = addiu(s0, 16);
                a1 = s2;
                a2 = addiu(sp, 0xB0);
                jal(ctx, 0x3D9FDCu, gen::fn_sub_3D6910_003d6910);
                v0 = addiu(s0, 16);
                sw(v0, s0, 8);
            }
            // 0x003d9fec
            charge(ctx, 4);
            a0 = s5;
            jal(ctx, 0x3D9FF0u, gen::fn_sub_3DFEB0_003dfeb0);
            sw(v0, s0, 96);
        }
        // 0x003d9ffc
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x003da018
    charge(ctx, 41);
    a0 = s4;
    a1 = 0x3E0000;
    a1 = addiu(a1, -18976);  // &sub_3DB5E0
    jal(ctx, 0x3DA024u, gen::fn_nmCmdListSetUpdateFunc_003c5e80);
    a0 = s4;
    a1 = 0x3E0000;
    a1 = addiu(a1, -5248);  // &sub_3DEB80
    jal(ctx, 0x3DA038u, gen::fn_nmCmdListSetDrawFunc_003c5e20);
    a0 = s4;
    a1 = 0x3E0000;
    a1 = addiu(a1, -5120);  // &sub_3DEC00
    jal(ctx, 0x3DA04Cu, gen::fn_nmCmdListSetRowDrawFunc_003c5ee0);
    a0 = s4;
    a1 = 0x3E0000;
    a1 = addiu(a1, -25456);  // &sub_3D9C90
    jal(ctx, 0x3DA060u, gen::fn_nmCmdListSetRowRemoveFunc_003c5f40);
    a0 = s4;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x3DA074u, gen::fn_nmCmdListSetPosition_003c6d40);
    a0 = s4;
    jal(ctx, 0x3DA080u, gen::fn_sub_3C6EE0_003c6ee0);
    v1 = 3;
    sh(v1, s5, 8);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x003DA0C0 sub_3DA0C0 -- 468 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCombineListCreate]: $a0 a stock list, $a1 the kind (0 normal: 2 slots, 1 triangle: 3 slots; others
// K_Assert 952). Creates the command window (sub_3C58F0(0, 432 + 4 * slots, 12, 24)) whose user area (+36 -> +68) is the
// list menu: +20 the window, +4 kind, +12 slots, +0 flags, +24 the selected array (list + 432), +284 a copy of the stock,
// +428 an element list; builds the rows (sub_3D9CC0), starts the nine panel animations (sub_3D8850 kinds 11, 0, 1, 4,
// 5, 12, 15, 22, 13) and the menu text (sub_3D06D0(root payload, 5, 0)); returns the list menu.
void sub_3DA0C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003da0c0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    v0 = 1;
    if (s1 == v0) {
        // 0x003da108
        charge(ctx, 3);
        s0 = 3;
    } else {
        // 0x003da0ec
        charge(ctx, 2);
        if (s1 == 0) {
            // 0x003da0fc
            charge(ctx, 3);
            s0 = 2;
        } else {
            // 0x003da0f4
            charge(ctx, 2);
            // 0x003da114
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 24608);  // "fclCombineList.c"
            a1 = 952;
            jal(ctx, 0x3DA120u, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    // 0x003da128
    charge(ctx, 91);
    v0 = sll(s0, 2);
    a1 = addiu(v0, 432);
    a0 = 0;
    a2 = 12;
    a3 = 24;
    jal(ctx, 0x3DA13Cu, gen::fn_sub_3C58F0_003c58f0);
    lw(v1, v0, 36);
    lw(s3, v1, 68);
    sw(v0, s3, 20);
    sw(s1, s3, 4);
    sw(s0, s3, 12);
    sw(zero, s3, 0);
    v0 = addiu(s3, 432);
    sw(v0, s3, 24);
    a0 = addiu(s3, 284);
    a1 = s2;
    a2 = 144;
    jal(ctx, 0x3DA170u, gen::fn_memcpy_00521250);
    a0 = s3;
    jal(ctx, 0x3DA17Cu, gen::fn_sub_3DFEB0_003dfeb0);
    sw(v0, s3, 428);
    a0 = s3;
    jal(ctx, 0x3DA18Cu, gen::fn_sub_3D9CC0_003d9cc0);
    a0 = s3;
    a1 = 11;
    a2 = 0;
    jal(ctx, 0x3DA1A0u, gen::fn_sub_3D8850_003d8850);
    a0 = s3;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x3DA1B4u, gen::fn_sub_3D8850_003d8850);
    a0 = s3;
    a1 = 1;
    a2 = 0;
    jal(ctx, 0x3DA1C8u, gen::fn_sub_3D8850_003d8850);
    a0 = s3;
    a1 = 4;
    a2 = 0;
    jal(ctx, 0x3DA1DCu, gen::fn_sub_3D8850_003d8850);
    a0 = s3;
    a1 = 5;
    a2 = 0;
    jal(ctx, 0x3DA1F0u, gen::fn_sub_3D8850_003d8850);
    a0 = s3;
    a1 = 12;
    a2 = 0;
    jal(ctx, 0x3DA204u, gen::fn_sub_3D8850_003d8850);
    a0 = s3;
    a1 = 15;
    a2 = 0;
    jal(ctx, 0x3DA218u, gen::fn_sub_3D8850_003d8850);
    a0 = s3;
    a1 = 22;
    a2 = 0;
    jal(ctx, 0x3DA22Cu, gen::fn_sub_3D8850_003d8850);
    a0 = s3;
    a1 = 13;
    a2 = 0;
    jal(ctx, 0x3DA240u, gen::fn_sub_3D8850_003d8850);
    jal(ctx, 0x3DA248u, gen::fn_sub_3D02E0_003d02e0);
    a0 = v0;
    jal(ctx, 0x3DA254u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = v0;
    a1 = 5;
    a2 = 0;
    jal(ctx, 0x3DA268u, gen::fn_sub_3D06D0_003d06d0);
    v0 = s3;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003DE290 sub_3DE290 -- 476 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCombineRecipeListCreate]: $a0 a stock list, $a1 the category. The special-fusion variant of
// sub_3DA0C0 for categories 2..4 (slots 4 / 5 / 6 by a 3-case switch; others K_Assert 2406 and keep the caller's
// $s0): the rows from the recipes (sub_3D9EA0), the panel animations 11, 7, 8, 9, 10, 12, 15, 22, ...; returns the list
// menu.
void sub_3DE290(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003de290
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    v1 = 4;
    if (s1 == v1) {
        // 0x003de2f4
        charge(ctx, 3);
        s0 = 6;
    } else {
        // 0x003de2bc
        charge(ctx, 3);
        v0 = 3;
        if (s1 == v0) {
            // 0x003de2e8
            charge(ctx, 3);
            s0 = 5;
        } else {
            // 0x003de2c8
            charge(ctx, 3);
            v0 = 2;
            if (s1 == v0) {
                // 0x003de2dc
                charge(ctx, 3);
                s0 = v1;
            } else {
                // 0x003de2d4
                charge(ctx, 2);
                // 0x003de300
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 24608);  // "fclCombineList.c"
                a1 = 2406;
                jal(ctx, 0x3DE30Cu, gen::fn_sub_19D3F0_0019d3f0);
            }
        }
    }
    // 0x003de314
    charge(ctx, 86);
    v0 = sll(s0, 2);
    a1 = addiu(v0, 432);
    a0 = 0;
    a2 = 12;
    a3 = 24;
    jal(ctx, 0x3DE328u, gen::fn_sub_3C58F0_003c58f0);
    lw(v1, v0, 36);
    lw(s3, v1, 68);
    sw(v0, s3, 20);
    sw(s1, s3, 4);
    sw(s0, s3, 12);
    sw(zero, s3, 0);
    v0 = addiu(s3, 432);
    sw(v0, s3, 24);
    a0 = addiu(s3, 284);
    a1 = s2;
    a2 = 144;
    jal(ctx, 0x3DE35Cu, gen::fn_memcpy_00521250);
    a0 = s3;
    jal(ctx, 0x3DE368u, gen::fn_sub_3DFEB0_003dfeb0);
    sw(v0, s3, 428);
    a0 = s3;
    jal(ctx, 0x3DE378u, gen::fn_sub_3D9EA0_003d9ea0);
    a0 = s3;
    a1 = 11;
    a2 = 0;
    jal(ctx, 0x3DE38Cu, gen::fn_sub_3D8850_003d8850);
    a0 = s3;
    a1 = 7;
    a2 = 0;
    jal(ctx, 0x3DE3A0u, gen::fn_sub_3D8850_003d8850);
    a0 = s3;
    a1 = 8;
    a2 = 0;
    jal(ctx, 0x3DE3B4u, gen::fn_sub_3D8850_003d8850);
    a0 = s3;
    a1 = 9;
    a2 = 0;
    jal(ctx, 0x3DE3C8u, gen::fn_sub_3D8850_003d8850);
    a0 = s3;
    a1 = 10;
    a2 = 0;
    jal(ctx, 0x3DE3DCu, gen::fn_sub_3D8850_003d8850);
    a0 = s3;
    a1 = 12;
    a2 = 0;
    jal(ctx, 0x3DE3F0u, gen::fn_sub_3D8850_003d8850);
    a0 = s3;
    a1 = 15;
    a2 = 0;
    jal(ctx, 0x3DE404u, gen::fn_sub_3D8850_003d8850);
    a0 = s3;
    a1 = 22;
    a2 = 0;
    jal(ctx, 0x3DE418u, gen::fn_sub_3D8850_003d8850);
    jal(ctx, 0x3DE420u, gen::fn_sub_3D02E0_003d02e0);
    a0 = v0;
    jal(ctx, 0x3DE42Cu, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = v0;
    a1 = 6;
    a2 = 0;
    jal(ctx, 0x3DE440u, gen::fn_sub_3D06D0_003d06d0);
    v0 = s3;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003DD800 sub_3DD800 -- 480 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCombineListDrawRow]: the row-draw callback ($a0 x, $a1 y, $a2 colour, $a3 the window, $t0 the row):
// fills a 28-byte frame record {x, y, colour, flags (bit 0: the cursor row), the owner list, the row record, the window,
// the row} and runs the row drawer sub_3DD260 over the row record's elements (+96, sub_3E0680).
void sub_3DD800(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x003dd800
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s6 = a0;
    s7 = a1;
    fp = a2;
    s5 = a3;
    s4 = t0;
    a0 = addiu(sp, 0xA0);
    a1 = 0;
    a2 = 28;
    jal(ctx, 0x3DD84Cu, gen::fn_memset_00521408);
    lw(v0, s5, 36);
    lw(s1, v0, 68);
    lw(v0, s4, 20);
    lw(s0, v0, 28);
    lw(s3, s0, 8);
    lw(v0, s5, 12);
    if (s4 == v0) {
        // 0x003dd874
        charge(ctx, 3);
        lh(v0, sp, 0xAA);
        v0 = v0 | 0x1;
        sh(v0, sp, 0xAA);
    }
    // 0x003dd880
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x003dd888
        charge(ctx, 4);
        lw(v0, s1, 0);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x003dd898
            charge(ctx, 3);
            lhu(v0, s0, 18);
            if (v0 == 0) {
                goto L_003dd96c;
            }
            goto L_003dd8a4;
        }
    L_003dd8a4:
        charge(ctx, 2);
        if (s1 == 0) {
            // 0x003dd8ac
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 24608);  // "fclCombineList.c"
            a1 = 1080;
            jal(ctx, 0x3DD8B8u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x003dd8c0
        charge(ctx, 2);
        if (s3 != 0) {
            // 0x003dd8d4
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x003dd950
                charge(ctx, 4);
                lw(v0, s1, 16);
                v0 = slt(s2, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003dd8e0
                charge(ctx, 2);
                if (s1 == 0) {
                    // 0x003dd8e8
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 24608);  // "fclCombineList.c"
                    a1 = 1041;
                    jal(ctx, 0x3DD8F4u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x003dd8fc
                charge(ctx, 4);
                lw(v0, s1, 12);
                at = slt(s2, v0);
                if (at != 0) {
                    // 0x003dd918
                    charge(ctx, 6);
                    lw(v1, s1, 24);
                    v0 = sll(s2, 2);
                    v0 = addu(v1, v0);
                    lw(v0, v0, 0);
                    if (v0 == 0) {
                        // 0x003dd938
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x003dd930
                        charge(ctx, 2);
                    }
                } else {
                    // 0x003dd90c
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x003dd93c
                charge(ctx, 2);
                if (v0 == s3) {
                    goto L_003dd944_18;
                }
                // 0x003dd94c
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x003dd960
            charge(ctx, 1);
            s3 = 0;
        } else {
            // 0x003dd8c8
            charge(ctx, 3);
            s3 = 0;
        }
    L_003dd964:
        charge(ctx, 2);
        if (s3 != 0) {
            goto L_003dd96c;
        }
        goto L_003dd978;
    }
L_003dd96c:
    charge(ctx, 3);
    lh(v0, sp, 0xAA);
    v0 = v0 | 0x2;
    sh(v0, sp, 0xAA);
L_003dd978:
    charge(ctx, 26);
    sw(s6, sp, 0xA0);
    sw(s7, sp, 0xA4);
    sh(fp, sp, 0xA8);
    sw(s1, sp, 0xAC);
    sw(s0, sp, 0xB0);
    sw(s5, sp, 0xB4);
    sw(s4, sp, 0xB8);
    lw(a0, s0, 96);
    a1 = 0x3E0000;
    a1 = addiu(a1, -11680);  // &sub_3DD260
    a2 = addiu(sp, 0xA0);
    jal(ctx, 0x3DD9A4u, gen::fn_sub_3E0680_003e0680);
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
    return;
L_003dd944_18:
    charge(ctx, 2);
    goto L_003dd964;
}

// 0x003DD9E0 sub_3DD9E0 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCombineStatusOpen]: $a0 the list menu: flag bit 5, then the status panel (+112): sub_3C9D00(4) and (8),
// sub_3C9E00(0), colour -1 (sub_3C9CD0), and the cursor row's persona shown (sub_3C9B00(panel, persona, 0)).
void sub_3DD9E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003dd9e0
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, 20);
    lw(v0, v0, 12);
    lw(v0, v0, 20);
    lw(s1, v0, 28);
    lw(v0, a0, 0);
    v0 = v0 | 0x20;
    sw(v0, a0, 0);
    lw(a0, a0, 112);
    a1 = 4;
    jal(ctx, 0x3DDA18u, gen::fn_sub_3C9D00_003c9d00);
    lw(a0, s0, 112);
    a1 = 8;
    jal(ctx, 0x3DDA28u, gen::fn_sub_3C9D00_003c9d00);
    lw(a0, s0, 112);
    a1 = 0;
    jal(ctx, 0x3DDA38u, gen::fn_sub_3C9E00_003c9e00);
    lw(a0, s0, 112);
    a1 = si(-1);
    jal(ctx, 0x3DDA48u, gen::fn_sub_3C9CD0_003c9cd0);
    lw(a0, s0, 112);
    lw(a1, s1, 8);
    a2 = 0;
    jal(ctx, 0x3DDA5Cu, gen::fn_sub_3C9B00_003c9b00);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003DDA80 sub_3DDA80 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCombineStatusInput]: $a0 the list menu: when the pad words gPadFlags 0x7E094E / 0x7E0958 hold button 0x20 (the
// cancel key), clears flag bit 5, sub_3C9D00(panel, 16) and returns 1; else 0.
void sub_3DDA80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003dda80
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    v0 = 0x7E0000;
    lhu(v0, v0, 2382);  // gPadFlags (0x7E094E)
    v0 = v0 & 0x20;     // the cancel button
    bool cancel = v0 != 0;
    if (!cancel) {
        // 0x003ddaa4: the other pad word
        charge(ctx, 5);
        v0 = 0x7E0000;
        lhu(v0, v0, 2392);  // 0x7E0958
        v0 = v0 & 0x20;
        cancel = v0 != 0;
    }
    if (cancel) {
        // 0x003ddab8: close the status panel
        charge(ctx, 9);
        s0 = 1;
        lw(v1, a0, 0);
        v0 = si(-33);
        v0 = v1 & v0;       // flags &= ~0x20 (the panel shown)
        sw(v0, a0, 0);
        lw(a0, a0, 112);    // the status panel
        a1 = 16;
        jal(ctx, 0x3DDAD4u, gen::fn_sub_3C9D00_003c9d00);
    }
    // 0x003ddadc (the shared epilogue)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003DDB00 sub_3DDB00 -- 136 bytes; frame 0x20: ra sp+0x0
// [fclCombineStatusDraw]: $a0 the list menu: with flag bit 5, shows the cursor row's persona in the status
// panel (sub_3C9B00); returns 0. (Opens with the inlined clear of an unused 8-byte frame buffer.)
void sub_3DDB00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ddb00
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    v1 = addiu(sp, 0x18);
    v0 = 8;
    if (v1 != 0) {
        for (;;) {
            // 0x003ddb18
            charge(ctx, 7);
            sb(zero, v1, 0);
            v1 = addiu(v1, 1);
            v0 = addiu(v0, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x003ddb34
    charge(ctx, 4);
    lw(v0, a0, 0);
    v0 = v0 & 0x20;
    if (v0 != 0) {
        // 0x003ddb50
        charge(ctx, 10);
        lw(v0, a0, 20);
        lw(v0, v0, 12);
        lw(v0, v0, 20);
        lw(v0, v0, 28);
        lw(a0, a0, 112);
        lw(a1, v0, 8);
        a2 = 0;
        jal(ctx, 0x3DDB6Cu, gen::fn_sub_3C9B00_003c9b00);
        v0 = 0;
    } else {
        // 0x003ddb44
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ddb78 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003DE160 sub_3DE160 -- 304 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclCombinePersonaPanelDraw]: $a0 the persona panel record (list menu + 116): with flag bit 0, the panel
// (+160) shows either the fusion result (index +12 == +20: the result persona at +108, its flags at +24) or the
// selected persona +16[index]; colour 0x20202020 | 0xFF for a special or registered result (flag bits 1 / 3), else -1.
void sub_3DE160(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003de160
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 160);
    v1 = addiu(sp, 0x58);
    v0 = 8;
    if (v1 != 0) {
        for (;;) {
            // 0x003de18c
            charge(ctx, 7);
            sb(zero, v1, 0);
            v1 = addiu(v1, 1);
            v0 = addiu(v0, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x003de1a8
    charge(ctx, 4);
    lw(v0, a0, 0);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x003de1c4
        charge(ctx, 4);
        lw(a1, a0, 12);
        lw(v0, a0, 20);
        if (a1 != v0) {
            // 0x003de1e8
            charge(ctx, 6);
            v1 = sll(a1, 2);
            lw(v0, a0, 16);
            v0 = addu(v0, v1);
            lw(s3, v0, 0);
            s2 = 0;
            s1 = 0;
        } else {
            // 0x003de1d4
            charge(ctx, 5);
            s3 = addiu(a0, 108);
            s2 = addiu(a0, 24);
            lw(s1, a0, 24);
        }
        // 0x003de200
        charge(ctx, 13);
        a1 = dsll32(a1, 24);
        a1 = dsra32(a1, 24);
        a0 = s0;
        jal(ctx, 0x3DE20Cu, gen::fn_sub_3C9E70_003c9e70);
        a0 = s0;
        a1 = s3;
        a2 = s2;
        jal(ctx, 0x3DE220u, gen::fn_sub_3C9B00_003c9b00);
        v0 = s1 & 0x2;
        if (v0 == 0) {
            // 0x003de234
            charge(ctx, 3);
            v0 = s1 & 0x8;
            if (v0 != 0) {
                goto L_003de240;
            }
            // 0x003de25c
            charge(ctx, 4);
            a0 = s0;
            a1 = si(-1);
            jal(ctx, 0x3DE264u, gen::fn_sub_3C9CD0_003c9cd0);
            goto L_003de26c;
        }
    L_003de240:
        charge(ctx, 7);
        a0 = s0;
        v0 = 0x20200000;
        a1 = v0 | 0x20FF;
        jal(ctx, 0x3DE24Cu, gen::fn_sub_3C9CD0_003c9cd0);
    L_003de26c:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003de1b8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003de270 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003D2D80 sub_3D2D80 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCombineStepRootList]: a step callback: the node payload +8 = the root list step (sub_3D2F00).
void sub_3D2D80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d2d80
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3D2D90u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = s0;
    jal(ctx, 0x3D2D9Cu, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    jal(ctx, 0x3D2DA8u, gen::fn_sub_3D2F00_003d2f00);
    sw(v0, s0, 8);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003D3B00 sub_3D3B00 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCombineStepDrawElems]: a step callback: draws the payload's elements (+16, sub_3DEDA0) and runs the
// element animator sub_3D38B0 over +20 with the owner state (sub_3DFAC0).
void sub_3D3B00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d3b00
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3D3B10u, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    lw(a0, v0, 16);
    jal(ctx, 0x3D3B20u, gen::fn_sub_3DEDA0_003deda0);
    lw(a0, s0, 16);
    jal(ctx, 0x3D3B2Cu, gen::fn_sub_3DFAC0_003dfac0);
    lw(a0, s0, 20);
    a1 = 0x3D0000;
    a1 = addiu(a1, 14512);  // &sub_3D38B0
    a2 = v0;
    jal(ctx, 0x3D3B44u, gen::fn_sub_3E0680_003e0680);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003D3CD0 sub_3D3CD0 -- 72 bytes; frame 0x10: ra sp+0x0
// [fclCombineStepMenuText]: a step callback: the menu text of the root payload (sub_3D06D0(payload, 0, 1)).
void sub_3D3CD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d3cd0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3D3CDCu, gen::fn_sub_3C5470_003c5470);
    lw(a0, gp, -18028);  // 0x7CE684: the fclCombine root (sequence object)
    jal(ctx, 0x3D3CE8u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = v0;
    a1 = 0;
    a2 = 1;
    jal(ctx, 0x3D3CFCu, gen::fn_sub_3D06D0_003d06d0);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003D4C80 sub_3D4C80 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCombineStepListDraw]: a step callback: draws the payload's list menu (+924, sub_3DB580).
void sub_3D4C80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d4c80
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3D4C90u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = s0;
    jal(ctx, 0x3D4C9Cu, gen::fn_sub_3C5470_003c5470);
    lw(a0, v0, 924);
    jal(ctx, 0x3D4CA8u, gen::fn_sub_3DB580_003db580);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003D53E0 sub_3D53E0 -- 52 bytes; frame 0x10: ra sp+0x0
// [fclCombineStepBgFree]: a step callback: releases the payload's background object (+8, sub_40CAD0).
void sub_3D53E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d53e0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3D53ECu, gen::fn_sub_3C5470_003c5470);
    lw(a0, v0, 8);
    jal(ctx, 0x3D53F8u, gen::fn_sub_40CAD0_0040cad0);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003D5420 sub_3D5420 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCombineBgStart]: when the root payload has a background step (+36), starts its background (+8) with
// the descriptor 0x6B1FA0 (sub_401420); returns 0.
void sub_3D5420(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d5420
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    lw(a0, gp, -18028);  // 0x7CE684: the fclCombine root (sequence object)
    jal(ctx, 0x3D5434u, gen::fn_nmObjPayloadWord12_003c5460);
    if (v0 != 0) {
        // 0x003d5444
        charge(ctx, 1);
        lw(s0, v0, 36);
    }
    // 0x003d5448
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x003d545c
        charge(ctx, 9);
        a0 = s0;
        jal(ctx, 0x3D5460u, gen::fn_sub_3C5470_003c5470);
        lw(a0, v0, 8);
        a1 = 0x6B0000;
        a1 = addiu(a1, 8096);  // &0x6B1FA0
        jal(ctx, 0x3D5474u, gen::fn_sub_401420_00401420);
        v0 = 0;
    } else {
        // 0x003d5450
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003d5480 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003D54A0 sub_3D54A0 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCombineBgDone]: the background step's state (sub_4014E0 != 0), 1 when there is no such step.
void sub_3D54A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d54a0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    lw(a0, gp, -18028);  // 0x7CE684: the fclCombine root (sequence object)
    jal(ctx, 0x3D54B4u, gen::fn_nmObjPayloadWord12_003c5460);
    if (v0 != 0) {
        // 0x003d54c4
        charge(ctx, 1);
        lw(s0, v0, 36);
    }
    // 0x003d54c8
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x003d54dc
        charge(ctx, 7);
        a0 = s0;
        jal(ctx, 0x3D54E0u, gen::fn_sub_3C5470_003c5470);
        lw(a0, v0, 8);
        jal(ctx, 0x3D54ECu, gen::fn_sub_4014E0_004014e0);
        v0 = sltu(0, v0);
    } else {
        // 0x003d54d0
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x003d54f8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003D4F30 sub_3D4F30 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclCombineStepBgCreate]: a step callback: the payload +8 = a new background object (sub_40C6F0(0)), +4 = 1.
void sub_3D4F30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d4f30
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3D4F40u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = s0;
    jal(ctx, 0x3D4F4Cu, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    a0 = 0;
    jal(ctx, 0x3D4F5Cu, gen::fn_sub_40C6F0_0040c6f0);
    sw(v0, s0, 8);
    v0 = 1;
    sw(v0, s0, 4);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003D4F90 sub_3D4F90 -- 84 bytes; frame 0x10: ra sp+0x0
// [fclCombineStepBgEnd]: a step callback: ends the background (+8, sub_40C9A0) and redraws the menu text
// (sub_3D06D0(root payload, 0, 1)).
void sub_3D4F90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003d4f90
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3D4F9Cu, gen::fn_sub_3C5470_003c5470);
    lw(a0, v0, 8);
    jal(ctx, 0x3D4FA8u, gen::fn_sub_40C9A0_0040c9a0);
    lw(a0, gp, -18028);  // 0x7CE684: the fclCombine root (sequence object)
    jal(ctx, 0x3D4FB4u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = v0;
    a1 = 0;
    a2 = 1;
    jal(ctx, 0x3D4FC8u, gen::fn_sub_3D06D0_003d06d0);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
