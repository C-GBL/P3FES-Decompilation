// BMD message manager helpers and the manager slot list (game/include/p3fes/game/bmd_msg.h). Phase 5:
// these replace the recompiled bodies of the eight functions listed under "BMD message manager" in
// game/replaced.txt; the recompiled bodies stay in the program under the __recomp symbols and
// tests/game/test_bmd_msg.cpp proves both agree on synthetic and real BMD images and on randomised
// slot lists.
//
// The guest::enter/charge/backedge lines are the virtual-time model of the recompiled bodies
// (ADR-0013; block costs from the `ctx.cycles += N` lines of recomp/generated/
// fn_0032_0039edd0_003ac6e0.cpp and fn_0033_003ac6f0_003b64c0.cpp). They keep every run
// byte-identical to the fully recompiled program and go away with Phase 6.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): all 8 functions here are now p3fes_handgen's register-faithful
// bodies (the hand versions differed from the original: scratch GPRs 4, frame/spills 2, faults only 1, callee frames
// 1). Each keeps the notes of its earlier hand version above it; what this header says about how the bodies were
// written describes those earlier versions.
#include "p3fes/game/bmd_msg.h"

#include "p3fes/game/guest.h"
#include "p3fes/game/script_vm.h"
#include "p3fes/game/hg_cpu.h"

// Callees of the register-faithful bodies (p3fes_handgen), through their recomp_gen entry points.
namespace p3fes::recomp_gen {
void fn_ApplyRelocTable_0035ac90(p3fes::EEContext&);
void fn_itfMesMngGetSpeakerBlock_003a5100(p3fes::EEContext&);
void fn_itfMesMngRelocateBmdOnce_003a5030(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line): a two-instruction stub in this build
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

// 0x003A5090 itfMesMngCheckBmdMagic -- 76 bytes; leaf frame (no stack)
// 0x3A5090. Blocks: entry 6 (the "MSG0" compare); "MSG1" compare 4; neither 1; the join 2; result
// 1 -> 3, result 0 -> 1; return 2.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void itfMesMngCheckBmdMagic(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003a5090
    enter(ctx, 6);  // entry check point + this block's cycles
    a1 = 1;
    lw(v1, a0, 8);
    v0 = 0x30470000;
    v0 = v0 | 0x534D;
    if (v1 != v0) {
        // 0x003a50a8
        charge(ctx, 4);
        v0 = 0x31470000;
        v0 = v0 | 0x534D;
        if (v1 != v0) {
            // 0x003a50b8
            charge(ctx, 1);
            a1 = 0;
        }
    }
    // 0x003a50bc
    charge(ctx, 2);
    if (a1 == 0) {
        // 0x003a50d0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003a50c4
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x003a50d4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003A50E0 itfMesMngGetMessageEntry -- 24 bytes; leaf frame (no stack)
// 0x3A50E0: one block of 6. `sll v0, a1, 3; addu; addiu 32`: 32-bit wrap-around, no bounds check.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void itfMesMngGetMessageEntry(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003a50e0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, a0, 4);
    v0 = sll(a1, 3);
    v0 = addu(v0, v1);
    v0 = addiu(v0, 32);
}

// 0x003A5100 itfMesMngGetSpeakerBlock -- 24 bytes; leaf frame (no stack)
// 0x3A5100: one block of 6.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void itfMesMngGetSpeakerBlock(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x003a5100
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, 24);
    v0 = sll(v0, 3);
    v0 = addu(v0, a0);
    v0 = addiu(v0, 32);
}

// 0x003A5030 itfMesMngRelocateBmdOnce -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x3A5030. Blocks: entry 7 (prologue + flag test); the relocation call 9; epilogue 5.
// ApplyRelocTable is the hand-written function of script_vm.cpp (its own entry check point and
// cycles), exactly what the recompiled body reaches through fn_ApplyRelocTable_0035ac90.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void itfMesMngRelocateBmdOnce(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lw, hg::sb,
          hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a5030
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lbu(v1, a0, 28);
    if (v1 == 0) {
        // 0x003a504c
        charge(ctx, 9);
        a0 = addiu(s0, 32);
        lw(v0, s0, 16);
        a2 = addu(s0, v0);
        lw(a3, s0, 20);
        a1 = a0;
        jal(ctx, 0x3A5060u, gen::fn_ApplyRelocTable_0035ac90);
        v1 = 1;
        sb(v1, s0, 28);
    }
    // 0x003a5070 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003A42C0 itfMesMngBindBmd -- 160 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x3A42C0. Blocks: entry 9 (prologue + null test); the assert call 5; bind + the two calls + the
// magic test 13; "MSG1" 3 / other 1; store + epilogue 9. A null handle is asserted
// (K_Assert("itfMesManager.c", 3085)) and then used anyway, as the original does.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void itfMesMngBindBmd(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a42c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s2 = a1;
    if (s0 == 0) {
        // 0x003a42e4
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 6768);  // "itfMesManager.c"
        a1 = 3085;
        jal(ctx, 0x3A42F0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003a42f8
    charge(ctx, 13);
    lw(s1, s0, 4);
    sw(s2, s0, 4);
    a0 = s2;
    jal(ctx, 0x3A4304u, gen::fn_itfMesMngRelocateBmdOnce_003a5030);
    a0 = s2;
    jal(ctx, 0x3A4310u, gen::fn_itfMesMngGetSpeakerBlock_003a5100);
    lw(a0, s2, 8);
    v1 = 0x31470000;
    v1 = v1 | 0x534D;
    if (a0 != v1) {
        // 0x003a4338
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003a432c
        charge(ctx, 3);
        lw(v0, v0, 8);
    }
    // 0x003a433c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    sw(v0, s0, 8);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B4920 sub_3B4920 -- 116 bytes; leaf frame (no stack)
// 0x3B4920. Blocks: entry 3; the slot body 15 (runs first, then again while the remaining count
// is >= 2, with a back-edge check before each repeat); the last slot and the list header 11.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_3B4920(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::slti, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x003b4920
    enter(ctx, 3);  // entry check point + this block's cycles
    t3 = 0;
    t1 = 0;
    t2 = a1;
    for (;;) {
        // 0x003b492c
        charge(ctx, 15);
        sw(t1, t2, 0);
        t0 = addu(t2, a3);
        sw(t0, t2, 4);
        v1 = dsll32(t3, 24);
        v1 = dsra32(v1, 24);
        sw(v1, t2, 8);
        t1 = t2;
        t2 = t0;
        a2 = addiu(a2, -1);
        v1 = addiu(t3, 1);
        t3 = dsll32(v1, 24);
        t3 = dsra32(t3, 24);
        at = slti(a2, 2);
        if (at != 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003b4968
    charge(ctx, 11);
    sw(t1, t0, 0);
    sw(zero, t0, 4);
    v1 = dsll32(t3, 24);
    v1 = dsra32(v1, 24);
    sw(v1, t0, 8);
    sw(zero, a0, 0);
    sw(zero, a0, 4);
    sw(a1, a0, 8);
    sw(t0, a0, 12);
}

// 0x003B49A0 sub_3B49A0 -- 116 bytes; leaf frame (no stack)
// 0x3B49A0. Blocks: entry 3; empty free list 3 (+2 return); pop 4; append behind the tail 6 /
// first in use 2; the new tail 4; next free slot 3 / none 1; free head 1; return 2. The loads
// and stores keep the original order (the tail is re-read after the first store), so a slot that
// aliases the list header behaves as before.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_3B49A0(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003b49a0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 8);
    if (v0 != 0) {
        // 0x003b49b8
        charge(ctx, 4);
        lw(a1, v0, 4);
        lw(v1, a0, 0);
        if (v1 == 0) {
            // 0x003b49e0
            charge(ctx, 2);
            sw(zero, v0, 0);
            sw(v0, a0, 0);
        } else {
            // 0x003b49c8
            charge(ctx, 6);
            lw(v1, a0, 4);
            sw(v1, v0, 0);
            lw(v1, a0, 4);
            sw(v0, v1, 4);
        }
        // 0x003b49e8
        charge(ctx, 4);
        sw(zero, v0, 4);
        sw(v0, a0, 4);
        if (a1 == 0) {
            // 0x003b4a04
            charge(ctx, 1);
            sw(zero, a0, 12);
        } else {
            // 0x003b49f8
            charge(ctx, 3);
            sw(zero, a1, 0);
        }
        // 0x003b4a08
        charge(ctx, 1);
        sw(a1, a0, 8);
    } else {
        // 0x003b49ac
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b4a0c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003B4A20 sub_3B4A20 -- 108 bytes; leaf frame (no stack)
// 0x3B4A20. Blocks: entry 4; predecessor 3 / none 1; the join 2; successor 3 / none 1; append to
// the free list 5; a free tail exists 1; free tail + head test 4; empty free list 1; return 2.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_3B4A20(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x003b4a20
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(a2, a0, 0);
    lw(v1, a0, 4);
    if (a2 == 0) {
        // 0x003b4a3c
        charge(ctx, 1);
        sw(v1, a1, 0);
    } else {
        // 0x003b4a30
        charge(ctx, 3);
        sw(v1, a2, 4);
    }
    // 0x003b4a40
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x003b4a54
        charge(ctx, 1);
        sw(a2, a1, 4);
    } else {
        // 0x003b4a48
        charge(ctx, 3);
        sw(a2, v1, 0);
    }
    // 0x003b4a58
    charge(ctx, 5);
    sw(zero, a0, 4);
    lw(v1, a1, 12);
    sw(v1, a0, 0);
    if (v1 != 0) {
        // 0x003b4a6c
        charge(ctx, 1);
        sw(a0, v1, 4);
    }
    // 0x003b4a70
    charge(ctx, 4);
    sw(a0, a1, 12);
    lw(v1, a1, 8);
    if (v1 == 0) {
        // 0x003b4a80
        charge(ctx, 1);
        sw(a0, a1, 8);
    }
    // 0x003b4a84 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (signatures from recomp/generated/functions.h) ---------
