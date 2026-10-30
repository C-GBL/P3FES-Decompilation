// The battle code, seventh pass (slice battle7, group cutin; docs/ANALYSIS/21_battle.md): the cut-in and special
// effect packets (the handle in gBtl +3360) and the action-end boss hook. Siblings of the functions the six replay
// routes reach in 0x290000-0x2FFFFF (a first-call probe found 19 of the 371 still-recompiled functions of the band
// reached; the AI rows only run for enemies without an AI script). The bodies are p3fes_handgen's (frame, spills, $ra
// links, every register, cycle charges, check points); this file names their offsets (battle3.h b3::, battle4.h b4::,
// battle5.h b5::, battle7.h b7::) and gives each its role -- proposed names in brackets (ADR-0009), symbols in code
// are functions.json's. Still-recompiled callees are reached through their gen:: entry points.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/battle7.h"

namespace p3fes::recomp_gen {
void fn_kwlnTaskGetState_00195290(p3fes::EEContext&);
void fn_sub_18B360_0018b360(p3fes::EEContext&);
void fn_sub_18B380_0018b380(p3fes::EEContext&);
void fn_sub_18B5F0_0018b5f0(p3fes::EEContext&);
void fn_sub_18B620_0018b620(p3fes::EEContext&);
void fn_sub_18EFB0_0018efb0(p3fes::EEContext&);
void fn_sub_18F060_0018f060(p3fes::EEContext&);
void fn_sub_18F080_0018f080(p3fes::EEContext&);
void fn_sub_18F0A0_0018f0a0(p3fes::EEContext&);
void fn_sub_18F0B0_0018f0b0(p3fes::EEContext&);
void fn_sub_18F0C0_0018f0c0(p3fes::EEContext&);
void fn_sub_18F0E0_0018f0e0(p3fes::EEContext&);
void fn_sub_27EC10_0027ec10(p3fes::EEContext&);
void fn_sub_2E3D50_002e3d50(p3fes::EEContext&);
void fn_sub_2E3DB0_002e3db0(p3fes::EEContext&);
void fn_sub_2E3DE0_002e3de0(p3fes::EEContext&);
void fn_sub_2E3E60_002e3e60(p3fes::EEContext&);
void fn_sub_2E3F20_002e3f20(p3fes::EEContext&);
void fn_sub_2E3F70_002e3f70(p3fes::EEContext&);
void fn_sub_2E3FB0_002e3fb0(p3fes::EEContext&);
void fn_sub_2E3FE0_002e3fe0(p3fes::EEContext&);
void fn_sub_2E4040_002e4040(p3fes::EEContext&);
void fn_sub_2E40D0_002e40d0(p3fes::EEContext&);
void fn_sub_2E4120_002e4120(p3fes::EEContext&);
void fn_sub_2E41D0_002e41d0(p3fes::EEContext&);
void fn_sub_2E4310_002e4310(p3fes::EEContext&);
void fn_sub_2E43A0_002e43a0(p3fes::EEContext&);
void fn_sub_2FD4A0_002fd4a0(p3fes::EEContext&);
void fn_sub_2FD500_002fd500(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b3;  // the record offsets and $gp slots of battle3.h
using namespace b4;  // battle4.h's additions
using namespace b5;  // battle5.h's additions
using namespace b7;  // this slice's additions (battle7.h)

// 0x002E3D50 sub_2E3D50 -- 92 bytes; frame 0x20: ra sp+0x0
// Cut-in packet start: plays the cut-in sub_18B620 under the battle task (gBtl +3352) and keeps its handle in gBtl
// +3360.
// Arguments: none.
void sub_2E3D50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e3d50
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    lw(v1, gp, -18676);  // gBtlSkillTbl+0x4
    lw(a1, a0, 4);
    v0 = sll(a1, 1);
    v0 = addu(v0, a1);
    v0 = sll(v0, 1);
    v1 = addu(v0, v1);
    lhu(v0, v1, -1630);
    sw(v0, sp, 0x18);
    lhu(v0, v1, -1628);
    sw(v0, sp, 0x1C);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl4::kTask);
    a2 = addiu(sp, 0x18);
    jal(ctx, 0x2E3D8Cu, gen::fn_sub_18B620_0018b620);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    sw(v0, v1, gbtl5::kCutIn);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002E3DB0 sub_2E3DB0 -- 48 bytes; frame 0x10: ra sp+0x0
// Cut-in packet update: done when sub_18B360 reports the cut-in finished (1).
// Arguments: none.
void sub_2E3DB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e3db0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl5::kCutIn);
    jal(ctx, 0x2E3DC0u, gen::fn_sub_18B360_0018b360);
    v0 = v0 ^ 0x1;
    v0 = sltiu(v0, 1);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E3DE0 sub_2E3DE0 -- 120 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlCutInPktCreate] Creates the cut-in packet (kind 3081, 8 data bytes; callbacks sub_2E3D50 / sub_2E3DB0; flags
// 0x11 cleared).
// Arguments: a0 u16, a1 u16 the cut-in arguments.
void sub_2E3DE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e3de0
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 3081;
    a1 = 8;
    jal(ctx, 0x2E3E00u, gen::fn_sub_27EC10_0027ec10);  // create a packet (kind $a0, $a1 data bytes)
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xEE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, 15696);  // &sub_2E3D50
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x2E0000;
    v1 = addiu(v1, 15792);  // &sub_2E3DB0
    sw(v1, v0, pkt::kUpdate);
    lw(a0, v0, pkt::kData);
    v1 = s1 & 0xFFFF;
    sw(v1, a0, 0);
    v1 = s0 & 0xFFFF;
    sw(v1, a0, 4);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002E3E60 sub_2E3E60 -- 184 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Cut-in close packet update: the first call starts the close (sub_18B380); then waits until the cut-in task is in
// state 2 and sub_18B5F0 reports 30 frames, and clears gBtl +3360.
// Arguments: a0 the packet data {u16 frames}.
void sub_2E3E60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e3e60
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lh(v0, a0, 0);
    if (v0 == 0) {
        // 0x002e3e7c
        charge(ctx, 6);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(a0, v0, gbtl5::kCutIn);
        jal(ctx, 0x2E3E84u, gen::fn_sub_18B380_0018b380);
        goto L_002e3ef4;
    }
    // 0x002e3e94
    charge(ctx, 7);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl5::kCutIn);
    jal(ctx, 0x2E3E9Cu, gen::fn_kwlnTaskGetState_00195290);
    v1 = 2;
    if (v0 != v1) {
        // 0x002e3eb0
        charge(ctx, 3);
        v1 = 1;
        if (v0 != v1) {
            // 0x002e3ebc
            charge(ctx, 2);
        }
        goto L_002e3ef4;
    }
    // 0x002e3ec4
    charge(ctx, 7);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl5::kCutIn);
    jal(ctx, 0x2E3ECCu, gen::fn_sub_18B5F0_0018b5f0);
    v0 = slti(v0, 30);
    if (v0 != 0) {
    L_002e3ef4:
        charge(ctx, 4);
        lh(v0, s0, 0);
        v0 = addiu(v0, 1);
        sh(v0, s0, 0);
        v0 = 0;
    } else {
        // 0x002e3ee0
        charge(ctx, 5);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        sw(zero, v0, gbtl5::kCutIn);
        v0 = 1;
    }
    // 0x002e3f04 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002E3F20 sub_2E3F20 -- 72 bytes; frame 0x10: ra sp+0x0
// [btlCutInClosePktCreate] Creates the cut-in close packet (kind 3082; update sub_2E3E60).
// Arguments: none.
void sub_2E3F20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e3f20
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 3082;
    a1 = 2;
    jal(ctx, 0x2E3F30u, gen::fn_sub_27EC10_0027ec10);  // create a packet (kind $a0, $a1 data bytes)
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xEE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, 15968);  // &sub_2E3E60
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sh(zero, v1, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E3F70 sub_2E3F70 -- 52 bytes; frame 0x10: ra sp+0x0
// Special effect packet start: sub_18EFB0 under the battle task for the id at data +0; handle in gBtl +3360.
// Arguments: a0 the packet data {u16 id}.
void sub_2E3F70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e3f70
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lhu(a1, a0, 0);
    lw(a0, v0, gbtl4::kTask);
    jal(ctx, 0x2E3F84u, gen::fn_sub_18EFB0_0018efb0);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    sw(v0, v1, gbtl5::kCutIn);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E3FB0 sub_2E3FB0 -- 48 bytes; frame 0x10: ra sp+0x0
// Special effect packet update: done when sub_18F060 reports 1.
// Arguments: none.
void sub_2E3FB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e3fb0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl5::kCutIn);
    jal(ctx, 0x2E3FC0u, gen::fn_sub_18F060_0018f060);
    v0 = v0 ^ 0x1;
    v0 = sltiu(v0, 1);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E3FE0 sub_2E3FE0 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlSpecialFxPktCreate] Creates the special effect packet (kind 3083; callbacks sub_2E3F70 / sub_2E3FB0) for the id
// a0.
// Arguments: a0 s16 the id.
void sub_2E3FE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e3fe0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 3083;
    a1 = 2;
    jal(ctx, 0x2E3FF8u, gen::fn_sub_27EC10_0027ec10);  // create a packet (kind $a0, $a1 data bytes)
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xEE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, 16240);  // &sub_2E3F70
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x2E0000;
    v1 = addiu(v1, 16304);  // &sub_2E3FB0
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sh(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002E4040 sub_2E4040 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Special effect hold packet update: the first call starts the hold (sub_18F080); then done once sub_18F0C0 says so;
// counts the frames at data +0.
// Arguments: a0 the packet data {u16 frames, u32 started}.
void sub_2E4040(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e4040
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, 4);
    if (v0 == 0) {
        // 0x002e405c
        charge(ctx, 8);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(a0, v0, gbtl5::kCutIn);
        jal(ctx, 0x2E4064u, gen::fn_sub_18F080_0018f080);
        v0 = 1;
        sw(v0, s0, 4);
        goto L_002e40a0;
    }
    // 0x002e407c
    charge(ctx, 6);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl5::kCutIn);
    jal(ctx, 0x2E4084u, gen::fn_sub_18F0C0_0018f0c0);
    if (v0 == 0) {
    L_002e40a0:
        charge(ctx, 4);
        lh(v0, s0, 0);
        v0 = addiu(v0, 1);
        sh(v0, s0, 0);
        v0 = 0;
    } else {
        // 0x002e4094
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002e40b0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002E40D0 sub_2E40D0 -- 76 bytes; frame 0x10: ra sp+0x0
// Creates the hold packet of sub_2E4040 (kind 3084).
// Arguments: none.
void sub_2E40D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e40d0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 3084;
    a1 = 8;
    jal(ctx, 0x2E40E0u, gen::fn_sub_27EC10_0027ec10);  // create a packet (kind $a0, $a1 data bytes)
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xEE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, 16448);  // &sub_2E4040
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sw(zero, v1, 4);
    sh(zero, v1, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E4120 sub_2E4120 -- 168 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Special effect end packet update: the first call ends the effect (sub_18F0E0) and reads its length (sub_18F0B0)
// into the frame counter; done when the counter reaches sub_18F0A0; clears gBtl +3360.
// Arguments: a0 the packet data {s16 frames, u32 started}.
void sub_2E4120(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e4120
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, 4);
    if (v0 == 0) {
        // 0x002e413c
        charge(ctx, 13);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(a0, v0, gbtl5::kCutIn);
        jal(ctx, 0x2E4144u, gen::fn_sub_18F0E0_0018f0e0);
        v0 = 1;
        sw(v0, s0, 4);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(a0, v0, gbtl5::kCutIn);
        jal(ctx, 0x2E415Cu, gen::fn_sub_18F0B0_0018f0b0);
        sh(v0, s0, 0);
        goto L_002e41a4;
    }
    // 0x002e4170
    charge(ctx, 8);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl5::kCutIn);
    jal(ctx, 0x2E4178u, gen::fn_sub_18F0A0_0018f0a0);
    lh(v1, s0, 0);
    at = slt(v1, v0);
    if (at != 0) {
    L_002e41a4:
        charge(ctx, 4);
        lh(v0, s0, 0);
        v0 = addiu(v0, 1);
        sh(v0, s0, 0);
        v0 = 0;
    } else {
        // 0x002e4190
        charge(ctx, 5);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        sw(zero, v0, gbtl5::kCutIn);
        v0 = 1;
    }
    // 0x002e41b4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002E41D0 sub_2E41D0 -- 76 bytes; frame 0x10: ra sp+0x0
// Creates the end packet of sub_2E4120 (kind 3085).
// Arguments: none.
void sub_2E41D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e41d0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 3085;
    a1 = 8;
    jal(ctx, 0x2E41E0u, gen::fn_sub_27EC10_0027ec10);  // create a packet (kind $a0, $a1 data bytes)
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xEE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, 16672);  // &sub_2E4120
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sw(zero, v1, 4);
    sh(zero, v1, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E4310 sub_2E4310 -- 32 bytes; frame 0x10: ra sp+0x0
// Boss event wait: sub_2FD4A0 (whether the boss event task has ended).
// Arguments: none.
void sub_2E4310(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x002e4310
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x2E4318u, gen::fn_sub_2FD4A0_002fd4a0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E43A0 sub_2E43A0 -- 140 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlBossActEndHook] Action-end boss hook: unless a boss event runs (sub_2FD500), calls the pending hook gBtl +2828
// with its argument (+2832) and clears the hook words once it returns 0; then, when nothing is pending, the boss
// event wait (sub_2FD4A0). Returns nonzero while something is pending.
// Arguments: none.
void sub_2E43A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e43a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    // a boss event still running: wait
    jal(ctx, 0x2E43B0u, gen::fn_sub_2FD500_002fd500);
    if (v0 == 0) {
        // 0x002e43c0
        charge(ctx, 4);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v1, gbtl7::kBossActEndHook);
        if (v0 != 0) {
            // 0x002e43d0
            charge(ctx, 6);
            lw(a0, v1, gbtl4::kBossActEndArg);
            jalr(ctx, 0x2E43D4u, v0.u());
            s0 = v0;
            if (s0 == 0) {
                // 0x002e43e8
                charge(ctx, 6);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                sw(zero, v0, gbtl4::kBossActEndFn);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                sw(zero, v0, gbtl7::kBossActEndHook);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                sw(zero, v0, gbtl4::kBossActEndArg);
            }
        }
    }
    // 0x002e4400
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x002e4408
        charge(ctx, 3);
        // nothing pending: the boss event wait
        jal(ctx, 0x2E4408u, gen::fn_sub_2FD4A0_002fd4a0);
        s0 = v0;
    }
    // 0x002e4414 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
