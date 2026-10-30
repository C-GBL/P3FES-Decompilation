// Phase 5 slice field7, part 2 (field7_epl.h): the field's EPL player tasks of k_epl.c, 0x1A8DB0-0x1A9760. Started
// from p3fes_handgen's bodies (register for register, block for block as the recompiled ones; game/include/p3fes/game/
// hg_cpu.h) and made readable on top: a role comment per function, named work offsets, structured control flow
// (host flags where two blocks shared a tail), block roles. Every path keeps the original's statements, charges and
// check points in order; tests/game/test_field7_epl.cpp pairs them.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/field7_epl.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_CacheFindFile_001021c0(p3fes::EEContext&);
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1A8DB0_001a8db0(p3fes::EEContext&);
void fn_sub_1A8FE0_001a8fe0(p3fes::EEContext&);
void fn_sub_1A9080_001a9080(p3fes::EEContext&);
void fn_sub_1A9330_001a9330(p3fes::EEContext&);
void fn_sub_1A9470_001a9470(p3fes::EEContext&);
void fn_sub_1A9690_001a9690(p3fes::EEContext&);
void fn_sub_1A96C0_001a96c0(p3fes::EEContext&);
void fn_sub_1A9760_001a9760(p3fes::EEContext&);
void fn_sub_34FCD0_0034fcd0(p3fes::EEContext&);
void fn_sub_34FCF0_0034fcf0(p3fes::EEContext&);
void fn_sub_34FD30_0034fd30(p3fes::EEContext&);
void fn_sub_34FD70_0034fd70(p3fes::EEContext&);
void fn_sub_34FE80_0034fe80(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace f7::epl;

// 0x001A8DB0 sub_1A8DB0 -- 552 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A8DB0(task) [K_FldEpl_UpdateTask]: the "epl(kosaka)" update (the header has the states). Playing (state 2):
// the main node is stepped (sub_34FD30) and drawn on its layer (sub_34FD70) while its counter is below the frame
// count, then switched off; each child likewise, destroyed (sub_34FCF0) and uncounted at its end. Returns 0, or -1
// at state 3 (the kernel then destroys the task).
void sub_1A8DB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a8db0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s2, a0, kTaskWork);  // s2 = the work
    lw(v1, s2, kState);
    v0 = 3;
    if (v1 == v0) {
        // 0x001a8fa8: state 3 -- finished
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x001a8ddc
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x001a8e8c: state 2 -- playing
            charge(ctx, 3);
            lw(v1, s2, kMainOn);
            bool all_done = false;  // main node off and no child left (the original's branch to 0x1a8ea4)
            if (v1 == 0) {
                // 0x001a8e98
                charge(ctx, 3);
                lw(v0, s2, kLiveChildren);
                all_done = v0 == 0;
            }
            if (all_done) {
                // 0x001a8ea4: back to idle
                charge(ctx, 4);
                v0 = 1;
                sw(v0, s2, kState);
            } else {
                // 0x001a8eb4
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x001a8ec0: the main node
                    charge(ctx, 5);
                    lw(v1, s2, kMainFrame);
                    lw(v0, s2, kFrames);
                    at = sltu(v1, v0);
                    if (at == 0) {
                        // 0x001a8f04: its time is up
                        charge(ctx, 1);
                        sw(zero, s2, kMainOn);
                    } else {
                        // 0x001a8ed4: step, draw on its layer, count the frame
                        charge(ctx, 12);
                        lw(a0, s2, kMainNode);
                        jal(ctx, 0x1A8ED8u, gen::fn_sub_34FD30_0034fd30);
                        lw(a0, s2, kMainNode);
                        lhu(a1, s2, kMainLayer);
                        jal(ctx, 0x1A8EE8u, gen::fn_sub_34FD70_0034fd70);
                        lw(v0, s2, kMainFrame);
                        v0 = addiu(v0, 1);
                        sw(v0, s2, kMainFrame);
                    }
                }
                // 0x001a8f08: the eight child slots
                charge(ctx, 3);
                s3 = 0;  // s3 = slot
                for (;;) {
                    // 0x001a8f94
                    charge(ctx, 3);
                    v0 = slti(s3, kMaxChildren);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001a8f14
                    charge(ctx, 6);
                    v0 = sll(s3, 2);
                    v0 = addu(s2, v0);
                    s1 = addiu(v0, kChildNodes);  // s1 = &child node
                    lw(a0, v0, kChildNodes);
                    if (a0 != 0) {
                        // 0x001a8f2c
                        charge(ctx, 6);
                        s0 = addiu(v0, kChildFrames);  // s0 = &child counter
                        lw(v1, v0, kChildFrames);
                        lw(v0, s2, kFrames);
                        at = sltu(v1, v0);
                        if (at == 0) {
                            // 0x001a8f78: its time is up -- destroy it
                            charge(ctx, 6);
                            jal(ctx, 0x1A8F78u, gen::fn_sub_34FCF0_0034fcf0);
                            sw(zero, s1, 0);
                            lw(v0, s2, kLiveChildren);
                            v0 = addiu(v0, -1);
                            sw(v0, s2, kLiveChildren);
                        } else {
                            // 0x001a8f44: step, draw on its layer, count the frame
                            charge(ctx, 13);
                            jal(ctx, 0x1A8F44u, gen::fn_sub_34FD30_0034fd30);
                            v0 = sll(s3, 1);
                            v0 = addu(s2, v0);
                            lw(a0, s1, 0);
                            lhu(a1, v0, kChildLayers);
                            jal(ctx, 0x1A8F5Cu, gen::fn_sub_34FD70_0034fd70);
                            lw(v0, s0, 0);
                            v0 = addiu(v0, 1);
                            sw(v0, s0, 0);
                        }
                    }
                    // 0x001a8f90
                    charge(ctx, 1);
                    s3 = addiu(s3, 1);
                }
                // 0x001a8fa0
                charge(ctx, 2);
            }
        } else {
            // 0x001a8de8
            charge(ctx, 3);
            v0 = 1;
            if (v1 != v0) {
                // 0x001a8df4
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x001a8e04: state 0 -- the file
                    charge(ctx, 3);
                    lw(v0, s2, kCached);
                    bool made = false;  // the node was made: next state (the original's shared block 0x1a8e78)
                    if (v0 != 0) {
                        // 0x001a8e58: from the H_Cdvd cache by name
                        charge(ctx, 8);
                        a0 = addiu(s2, kPath);
                        a1 = addiu(sp, 0x5C);
                        jal(ctx, 0x1A8E60u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
                        a0 = v0;
                        jal(ctx, 0x1A8E6Cu, gen::fn_sub_34FCD0_0034fcd0);
                        sw(v0, s2, kMainNode);
                        made = true;
                    } else {
                        // 0x001a8e10: wait for the request
                        charge(ctx, 5);
                        lw(a0, s2, kRequest);
                        jal(ctx, 0x1A8E14u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                        if (v0 != 0) {
                            // 0x001a8e24
                            charge(ctx, 3);
                            lw(v0, s2, kRequest);
                            if (v0 != 0) {
                                // 0x001a8e30: the node from the loaded data (+272), then drop the request
                                charge(ctx, 10);
                                lw(a0, v0, 272);
                                jal(ctx, 0x1A8E34u, gen::fn_sub_34FCD0_0034fcd0);
                                sw(v0, s2, kMainNode);
                                lw(a0, s2, kRequest);
                                jal(ctx, 0x1A8E44u, gen::fn_H_Cdvd_Destroy_00100ec0);
                                sw(zero, s2, kRequest);
                            }
                            made = true;
                        }
                    }
                    if (made) {
                        // 0x001a8e78: state 1
                        charge(ctx, 5);
                        lw(v0, s2, kState);
                        v0 = addiu(v0, 1);
                        sw(v0, s2, kState);
                    }
                } else {
                    // 0x001a8dfc: any other state
                    charge(ctx, 2);
                }
            }
        }
        // 0x001a8fb4
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x001a8fb8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001A8FE0 sub_1A8FE0 -- 152 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A8FE0(task) [K_FldEpl_DestroyTask]: destroys every live child node and the main node (sub_34FCF0), then frees
// the work through the RW free slot (0x96017C). The request (+4) is not destroyed here.
void sub_1A8FE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a8fe0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(s0, a0, kTaskWork);
    s1 = 0;
    for (;;) {
        // 0x001a9028
        charge(ctx, 3);
        v0 = slti(s1, kMaxChildren);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001a9008
        charge(ctx, 5);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        lw(a0, v0, kChildNodes);
        if (a0 != 0) {
            // 0x001a901c
            charge(ctx, 2);
            jal(ctx, 0x1A901Cu, gen::fn_sub_34FCF0_0034fcf0);
        }
        // 0x001a9024
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x001a9034
    charge(ctx, 3);
    lw(a0, s0, kMainNode);
    if (a0 != 0) {
        // 0x001a9040
        charge(ctx, 2);
        jal(ctx, 0x1A9040u, gen::fn_sub_34FCF0_0034fcf0);
    }
    // 0x001a9048: free the work (tail of the frame)
    charge(ctx, 12);
    lw(a0, s2, kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C: the RW free slot
    jalr(ctx, 0x1A9054u, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001A9080 sub_1A9080 -- 252 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A9080(parent, path, frames, cached) [K_FldEpl_CreateTask]: allocates the 180-byte work (RW calloc slot
// 0x960184), creates "epl(kosaka)" under `parent` at priority 20 (kwlnTaskCreate; update sub_1A8DB0, destroy
// sub_1A8FE0); with `cached` non-zero stores it (+4) and sets the cache flag, else requests the file (H_Cdvd_Request,
// not an archive); stores the frame count and copies the path. Returns the task, or 0 when the allocation failed.
// The work is not checked after kwlnTaskCreate (as in retail).
void sub_1A9080(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a9080
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;  // parent
    s2 = a1;  // path
    s1 = a2;  // frames
    s0 = a3;  // cached
    a0 = 1;
    a1 = kWorkSize;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184: the RW calloc slot
    jalr(ctx, 0x1A90C0u, v0.u());
    s4 = v0;  // s4 = the work
    if (s4 != 0) {
        // 0x001a90e0
        charge(ctx, 14);
        a0 = s3;
        a1 = 0x680000;
        a1 = addiu(a1, -29560);  // "epl(kosaka)"
        a2 = 20;
        a3 = 0x1B0000;
        a3 = addiu(a3, -29264);  // &sub_1A8DB0
        t0 = 0x1B0000;
        t0 = addiu(t0, -28704);  // &sub_1A8FE0
        t1 = s4;
        jal(ctx, 0x1A9104u, gen::fn_kwlnTaskCreate_00194b20);
        s3 = v0;  // s3 = the task
        if (s0 != 0) {
            // 0x001a9134: from the cache
            charge(ctx, 3);
            sw(s0, s4, kRequest);
            v0 = 1;
            sw(v0, s4, kCached);
        } else {
            // 0x001a9118: request the file
            charge(ctx, 7);
            a0 = s2;
            a1 = 0;
            jal(ctx, 0x1A9120u, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s4, kRequest);
        }
        // 0x001a9140
        charge(ctx, 6);
        sw(s1, s4, kFrames);
        a0 = addiu(s4, kPath);
        a1 = s2;
        jal(ctx, 0x1A914Cu, gen::fn_strcpy_00524270);
        v0 = s3;
    } else {
        // 0x001a90d4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a9158 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001A9330 sub_1A9330 -- 92 bytes; frame 0x10: ra sp+0x0
// sub_1A9330(task, slot, matrix) [K_FldEpl_SetMatrix]: places a node from an RwMatrix (sub_34FE80): the main node
// for a negative slot (no NULL check), else child `slot` when it is live (no bound check). Called by the field event
// task (K_FldEvent_UpdateFldEventTask).
void sub_1A9330(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a9330
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, kTaskWork);
    if (i64(a1) < 0) {
        // 0x001a936c: the main node
        charge(ctx, 4);
        lw(a0, a0, kMainNode);
        a1 = a2;
        jal(ctx, 0x1A9374u, gen::fn_sub_34FE80_0034fe80);
    } else {
        // 0x001a9344: child `slot`
        charge(ctx, 5);
        v1 = sll(a1, 2);
        v1 = addu(v1, a0);
        lw(a0, v1, kChildNodes);
        if (a0 != 0) {
            // 0x001a9358
            charge(ctx, 5);
            a1 = a2;
            jal(ctx, 0x1A935Cu, gen::fn_sub_34FE80_0034fe80);
        }
    }
    // 0x001a937c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A9470 sub_1A9470 -- 144 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A9470(task) [K_FldEpl_Stop]: for a non-NULL task, destroys and clears every live child, zeroes the live count
// and, when there is a main node, switches it off (state 2 then falls back to idle). Callers: the dungeon floor
// change (sub_1BFCC0), sub_1C5900, the field event task.
void sub_1A9470(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a9470
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (a0 != 0) {
        // 0x001a948c
        charge(ctx, 4);
        lw(s1, a0, kTaskWork);  // s1 = the work
        s2 = 0;                 // s2 = slot
        for (;;) {
            // 0x001a94c4
            charge(ctx, 3);
            v1 = slti(s2, kMaxChildren);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001a949c
            charge(ctx, 6);
            v1 = sll(s2, 2);
            v1 = addu(s1, v1);
            s0 = addiu(v1, kChildNodes);
            lw(a0, v1, kChildNodes);
            if (a0 != 0) {
                // 0x001a94b4
                charge(ctx, 3);
                jal(ctx, 0x1A94B4u, gen::fn_sub_34FCF0_0034fcf0);
                sw(zero, s0, 0);
            }
            // 0x001a94c0
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
        // 0x001a94d0
        charge(ctx, 4);
        sw(zero, s1, kLiveChildren);
        lw(v1, s1, kMainNode);
        if (v1 != 0) {
            // 0x001a94e0
            charge(ctx, 1);
            sw(zero, s1, kMainOn);
        }
    }
    // 0x001a94e4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001A9690 sub_1A9690 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1A9690(task) [K_FldEpl_DestroyDelayTask]: frees the "epl delay(kosaka)" work (RW free slot 0x96017C).
void sub_1A9690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a9690
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C: the RW free slot
    jalr(ctx, 0x1A96A4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A96C0 sub_1A96C0 -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A96C0(parent) [K_FldEpl_CreateDelayTask]: allocates the 208-byte work and creates "epl delay(kosaka)" at
// priority 10 (kwlnTaskCreateWithAutoPriority; update sub_1A9500, destroy sub_1A9690), with +4 = 20. Returns the
// task, or 0 when the allocation failed.
void sub_1A96C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a96c0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;  // parent
    a0 = 1;
    a1 = kDelayWorkSize;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184: the RW calloc slot
    jalr(ctx, 0x1A96E8u, v0.u());
    s0 = v0;  // s0 = the work
    if (s0 != 0) {
        // 0x001a9708
        charge(ctx, 13);
        a0 = s1;
        a1 = 10;
        a2 = 0x680000;
        a2 = addiu(a2, -29536);  // "epl delay(kosaka)"
        a3 = 0x1B0000;
        a3 = addiu(a3, -27392);  // &sub_1A9500
        t0 = 0x1B0000;
        t0 = addiu(t0, -26992);  // &sub_1A9690
        t1 = s0;
        jal(ctx, 0x1A972Cu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        v1 = 20;
        sw(v1, s0, kDelayWait);
    } else {
        // 0x001a96fc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a973c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001A9760 sub_1A9760 -- 228 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1A9760(task, id, pos, a3, a4) [K_FldEpl_QueueDelayed]: for a non-NULL "epl delay" task, appends a request at
// slot count (+12): id, the vec3 at `pos`, a3, a4, and counts it. A full queue (8) asserts (k_epl.c 608; K_Assert
// returns in retail) and the store runs past the arrays. Callers: the Y map code (sub_424B60, sub_456670 ...).
void sub_1A9760(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001a9760
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a1;  // id
    s3 = a2;  // pos
    s2 = a3;
    s1 = t0;
    if (a0 != 0) {
        // 0x001a9794
        charge(ctx, 5);
        lw(s0, a0, kTaskWork);  // s0 = the work
        lw(v1, s0, kDelayCount);
        v1 = slti(v1, 8);
        if (v1 == 0) {
            // 0x001a97a8: the queue is full
            charge(ctx, 4);
            a0 = addiu(gp, -27360);  // "k_epl.c"
            a1 = 608;
            jal(ctx, 0x1A97B0u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x001a97b8: the four fields of slot `count`, then count++
        charge(ctx, 26);
        lw(v1, s0, kDelayCount);
        v1 = sll(v1, 2);
        v1 = addu(v1, s0);
        sw(s4, v1, kDelayId);
        lw(a0, s0, kDelayCount);
        v1 = sll(a0, 1);
        v1 = addu(v1, a0);
        v1 = sll(v1, 2);
        v1 = addu(v1, s0);
        lwc1(f2, s3, 0);
        lwc1(f1, s3, 4);
        lwc1(f0, s3, 8);
        swc1(f2, v1, kDelayPos + 0);
        swc1(f1, v1, kDelayPos + 4);
        swc1(f0, v1, kDelayPos + 8);
        lw(v1, s0, kDelayCount);
        v1 = sll(v1, 2);
        v1 = addu(v1, s0);
        sw(s2, v1, kDelayArg3);
        lw(v1, s0, kDelayCount);
        v1 = sll(v1, 2);
        v1 = addu(v1, s0);
        sw(s1, v1, kDelayArg4);
        lw(v1, s0, kDelayCount);
        v1 = addiu(v1, 1);
        sw(v1, s0, kDelayCount);
    }
    // 0x001a9820 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

}  // namespace p3fes::game
