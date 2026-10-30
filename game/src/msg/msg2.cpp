// BMD message manager, second slice (game/include/p3fes/game/msg2.h). Phase 5: these replace the
// recompiled bodies of the functions listed under "msg2" in game/replaced.txt; the recompiled bodies
// stay in the program under the __recomp symbols and tests/game/test_msg2.cpp proves both agree.
//
// The guest::enter/charge/backedge lines are the virtual-time model of the recompiled bodies
// (ADR-0013; block costs from the `ctx.cycles += N` lines of recomp/generated/fn_0032_0039edd0_003ac6e0.cpp).
// Loops whose test block comes first ("goto test" in the recompiled body) charge the test block,
// then take the back-edge check before every further iteration.
//
// Registers: still-recompiled callees get exactly the argument registers the original set (set_reg);
// every other register is left as the caller had it, as the original's pass-through does. A void
// function whose body used $v0 as scratch (or whose callee left a value there) leaves the same $v0
// (noted per function; the shims do it).
//
// Faithfulness audit (2026-10-21, tools/ours/audit): all 68 functions here are now p3fes_handgen's register-faithful
// bodies (the hand versions differed from the original: frame/spills 39, scratch GPRs 21, faults only 5, $v0 2, logic
// 1); what this header says above about how the bodies were written describes the earlier hand versions.
//
// Readability pass (read_text, 2026-10-21): the 68 generated bodies keep every statement, charge, check point and call
// of p3fes_handgen's output in the same order on every path; on top of it they name what they touch (text_view.h:
// `lb(v0, s0, mes_handle::kText + text_rec::kBusy)`, `la(v0, kItfMesSlotCurrentHandle)` for a lui/addiu pair,
// `k_assert(a0, a1, pc, kItfMesManagerFile, line)` for the four-statement K_Assert call), say what each block does,
// and replace the generator's gotos by if / else where every path keeps its statements. Each function's comment gives
// its role. The slot accessors all start with the same lookup: v1 = 52 * slot (((slot * 3) * 4 + slot) * 4), the
// handle = *(kItfMesSlotCurrentHandle + v1), K_Assert(handle) -- `jr $ra` in retail, so a null handle is used anyway.
#include "p3fes/game/msg2.h"

#include "p3fes/ee/core.h"
#include "p3fes/ee/hilo.h"
#include "p3fes/game/bmd_msg.h"
#include "p3fes/game/guest.h"
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/text_view.h"

// Callees of the register-faithful bodies (p3fes_handgen), through their recomp_gen entry points.
namespace p3fes::recomp_gen {
void fn_itfMesMngCheckBmdMagic_003a5090(p3fes::EEContext&);
void fn_itfMesMngResetSelection_003a3b00(p3fes::EEContext&);
void fn_itfMesMngTextOffsetNodes_003a6310(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line): `jr $ra` in this build
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sub_3B0170_003b0170(p3fes::EEContext&);  // frFont.c: releases a text node list
void fn_frFontSetTagSlot_003b2a10(p3fes::EEContext&);  // frFont.c: kFrMessageArgTable[a0] = a1
void fn_frFontLineResetAlpha_003b0c70(p3fes::EEContext&);  // frFont.c: node+64 = 1, alpha 255 down the list
void fn_sub_3B4A90_003b4a90(p3fes::EEContext&);  // frFont.c: n shaded colours from a factor table
void fn_sub_3A6CA0_003a6ca0(p3fes::EEContext&);  // itfMesManager.c: panel sub-record reset
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace tview;  // text_view.h: la / k_assert / hi / lo and the record offsets

// --- per-slot handle accessors ---------------------------------------------------------------------

// 0x003A2580 itfMesMngGetBusy -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// itfMesMngGetBusy(slot): the busy byte (s8, handle +52 = text_rec::kBusy) of the slot's handle; scrCommand_MSG
// polls it. K_Assert line 701. Blocks: entry 14; assert 5; load + epilogue 6.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngGetBusy(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::lb, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a2580
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v0 = sll(a0, 1);
    v0 = addu(v0, a0);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    v1 = sll(v0, 2);
    la(v0, kItfMesSlotCurrentHandle);
    v0 = addu(v0, v1);
    lw(s0, v0, 0);
    if (s0 == 0) {
        // 0x003a25b8: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A25C4u, kItfMesManagerFile, 701);
    }
    // 0x003a25cc: v0 = handle->busy; epilogue
    charge(ctx, 6);
    lb(v0, s0, mes_handle::kText + text_rec::kBusy);  // v0 = handle->busy (sign-extended)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003A25F0 itfMesMngSetBusy -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// itfMesMngSetBusy(slot, value): handle->busy (handle +52) = value (low byte). K_Assert line 728. Blocks: entry 16;
// assert 5; store + epilogue 7. Leaves $v0 alone.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngSetBusy(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sb, hg::sd,
          hg::sll, hg::sq;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a25f0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;  // value
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    a0 = sll(v1, 2);
    la(v1, kItfMesSlotCurrentHandle);
    v1 = addu(v1, a0);
    lw(s1, v1, 0);
    if (s1 == 0) {
        // 0x003a2630: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A263Cu, kItfMesManagerFile, 728);
    }
    // 0x003a2644: handle->busy = value; epilogue
    charge(ctx, 7);
    sb(s0, s1, mes_handle::kText + text_rec::kBusy);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003A2750 itfMesMngGetSelectWord84 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// itfMesMngGetSelectWord84(slot): the s16 at handle +84 (select_rec::kWord84). K_Assert line 1060. Blocks: entry 14;
// assert 5; load 6.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngGetSelectWord84(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lh, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a2750
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v0 = sll(a0, 1);
    v0 = addu(v0, a0);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    v1 = sll(v0, 2);
    la(v0, kItfMesSlotCurrentHandle);
    v0 = addu(v0, v1);
    lw(s0, v0, 0);
    if (s0 == 0) {
        // 0x003a2788: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A2794u, kItfMesManagerFile, 1060);
    }
    // 0x003a279c: v0 = handle->select.word84; epilogue
    charge(ctx, 6);
    lh(v0, s0, mes_handle::kSelect + select_rec::kWord84);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003A27C0 itfMesMngSetSelectWord84 -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// itfMesMngSetSelectWord84(slot, value): handle +84 = value (low half). K_Assert line 1082. Blocks: entry 16;
// assert 5; store 7.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngSetSelectWord84(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sh,
          hg::sll, hg::sq;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a27c0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;  // value
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    a0 = sll(v1, 2);
    la(v1, kItfMesSlotCurrentHandle);
    v1 = addu(v1, a0);
    lw(s1, v1, 0);
    if (s1 == 0) {
        // 0x003a2800: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A280Cu, kItfMesManagerFile, 1082);
    }
    // 0x003a2814: handle->select.word84 = value; epilogue
    charge(ctx, 7);
    sh(s0, s1, mes_handle::kSelect + select_rec::kWord84);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003A2830 itfMesMngGetSelection -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// itfMesMngGetSelection(slot): the chosen option (s16 cursor, handle +86) of a selection message. K_Assert line
// 1107. Blocks: entry 14; assert 5; load 6.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngGetSelection(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lh, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a2830
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v0 = sll(a0, 1);
    v0 = addu(v0, a0);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    v1 = sll(v0, 2);
    la(v0, kItfMesSlotCurrentHandle);
    v0 = addu(v0, v1);
    lw(s0, v0, 0);
    if (s0 == 0) {
        // 0x003a2868: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A2874u, kItfMesManagerFile, 1107);
    }
    // 0x003a287c: v0 = handle->select.cursor; epilogue
    charge(ctx, 6);
    lh(v0, s0, mes_handle::kSelect + select_rec::kCursor);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003A3F20 itfMesMngGetSelection2 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// itfMesMngGetSelection2(slot): the same body as itfMesMngGetSelection (a second copy in the binary) with K_Assert
// line 2729. Blocks: entry 14; assert 5; load 6.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngGetSelection2(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lh, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a3f20
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v0 = sll(a0, 1);
    v0 = addu(v0, a0);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    v1 = sll(v0, 2);
    la(v0, kItfMesSlotCurrentHandle);
    v0 = addu(v0, v1);
    lw(s0, v0, 0);
    if (s0 == 0) {
        // 0x003a3f58: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A3F64u, kItfMesManagerFile, 2729);
    }
    // 0x003a3f6c: v0 = handle->select.cursor; epilogue
    charge(ctx, 6);
    lh(v0, s0, mes_handle::kSelect + select_rec::kCursor);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003A3DA0 itfMesMngGetState -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// itfMesMngGetState(slot): the handle's state word (+0). K_Assert line 2644. Blocks: entry 14; assert 5; load 6.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngGetState(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sll,
          hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a3da0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v0 = sll(a0, 1);
    v0 = addu(v0, a0);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    v1 = sll(v0, 2);
    la(v0, kItfMesSlotCurrentHandle);
    v0 = addu(v0, v1);
    lw(s0, v0, 0);
    if (s0 == 0) {
        // 0x003a3dd8: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A3DE4u, kItfMesManagerFile, 2644);
    }
    // 0x003a3dec: v0 = handle->state; epilogue
    charge(ctx, 6);
    lw(v0, s0, mes_handle::kState);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003A3E10 itfMesMngSetStateFlags -- 128 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// itfMesMngSetStateFlags(slot, flags): handle->state |= flags & 0xFFFF0000 (only the caller's half of the word).
// K_Assert line 2689. Blocks: entry 16; assert 5; read-modify-write 11.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngSetStateFlags(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lui, hg::lw, hg::sd,
          hg::sll, hg::sq, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a3e10
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;  // flags
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    a0 = sll(v1, 2);
    la(v1, kItfMesSlotCurrentHandle);
    v1 = addu(v1, a0);
    lw(s1, v1, 0);
    if (s1 == 0) {
        // 0x003a3e50: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A3E5Cu, kItfMesManagerFile, 2689);
    }
    // 0x003a3e64: handle->state |= flags & 0xFFFF0000; epilogue
    charge(ctx, 11);
    v1 = lui(0xFFFF);  // mes_handle::kStateFlagsMask
    a0 = s0 & v1;
    lw(v1, s1, mes_handle::kState);
    v1 = v1 | a0;
    sw(v1, s1, mes_handle::kState);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003A3E90 itfMesMngClearStateFlags -- 132 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// itfMesMngClearStateFlags(slot, flags): handle->state &= ~(flags & 0xFFFF0000). K_Assert line 2710. Blocks: entry
// 16; assert 5; read-modify-write 12.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngClearStateFlags(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lui, hg::lw, hg::nor,
          hg::sd, hg::sll, hg::sq, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a3e90
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;  // flags
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    a0 = sll(v1, 2);
    la(v1, kItfMesSlotCurrentHandle);
    v1 = addu(v1, a0);
    lw(s0, v1, 0);
    if (s0 == 0) {
        // 0x003a3ed0: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A3EDCu, kItfMesManagerFile, 2710);
    }
    // 0x003a3ee4: handle->state &= ~(flags & 0xFFFF0000); epilogue
    charge(ctx, 12);
    v1 = lui(0xFFFF);  // mes_handle::kStateFlagsMask
    v1 = s1 & v1;
    a0 = nor(v1, 0);  // ~(flags & mask)
    lw(v1, s0, mes_handle::kState);
    v1 = v1 & a0;
    sw(v1, s0, mes_handle::kState);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003A3BA0 itfMesMngSetChoiceMask -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// itfMesMngSetChoiceMask(slot, mask): handle +80 = mask (bit i set = option i disabled). K_Assert line 2390.
// Blocks: entry 16; assert 5; store 7.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngSetChoiceMask(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sll,
          hg::sq, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a3ba0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;  // mask
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    a0 = sll(v1, 2);
    la(v1, kItfMesSlotCurrentHandle);
    v1 = addu(v1, a0);
    lw(s1, v1, 0);
    if (s1 == 0) {
        // 0x003a3be0: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A3BECu, kItfMesManagerFile, 2390);
    }
    // 0x003a3bf4: handle->select.choice_mask = mask; epilogue
    charge(ctx, 7);
    sw(s0, s1, mes_handle::kSelect + select_rec::kChoiceMask);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003A3C10 itfMesMngSetSelection -- 200 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// itfMesMngSetSelection(slot, option): maps `option` to its index among the enabled options and makes it the
// cursor: walks bits 0..option of the choice mask (at least bit 0: the bound is the caller's whole 64-bit $a1)
// counting the clear (enabled) ones; when bit `option` itself is set (disabled) the result is 0, else count - 1;
// stored to the cursor (+86) and its copy (+88). K_Assert line 2411. Blocks: entry 16; assert 5; loop setup 4; per
// bit: test 3 (+1 when clear), counter test 3, step 4 + back-edge check; result: last bit set 3 / clear 1; stores 8.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngSetSelection(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sh, hg::sll, hg::slt, hg::sq, hg::srl;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a3c10
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;  // option (the whole 64-bit register is the loop bound)
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    a0 = sll(v1, 2);
    la(v1, kItfMesSlotCurrentHandle);
    v1 = addu(v1, a0);
    lw(s1, v1, 0);
    if (s1 == 0) {
        // 0x003a3c50: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A3C5Cu, kItfMesManagerFile, 2411);
    }
    // 0x003a3c64: a0 = &handle->select; a1 = enabled count; a3 = the mask, shifted per bit; a2 = bit i
    charge(ctx, 4);
    a0 = addiu(s1, mes_handle::kSelect);
    a1 = 0;
    lw(a3, s1, mes_handle::kSelect + select_rec::kChoiceMask);
    a2 = 0;
    for (;;) {
        // 0x003a3c74: bit i of the mask clear (option enabled) -> ++count
        charge(ctx, 3);
        v1 = a3 & 0x1;
        if (v1 == 0) {
            // 0x003a3c80
            charge(ctx, 1);
            a1 = addiu(a1, 1);
        }
        // 0x003a3c84: stop after bit `option`
        charge(ctx, 3);
        at = slt(a2, s0);
        if (at == 0) {
            break;
        }
        // 0x003a3c90: next bit
        charge(ctx, 4);
        a2 = addiu(a2, 1);
        a3 = srl(a3, 1);
        backedge(ctx);
    }
    // 0x003a3ca0: v1 still holds the last bit tested (bit `option`)
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x003a3cb4: enabled: its index among the enabled options
        charge(ctx, 1);
        v1 = addiu(a1, -1);
    } else {
        // 0x003a3ca8: disabled: index 0
        charge(ctx, 3);
        v1 = 0;
    }
    // 0x003a3cb8: select.cursor = select.cursor2 = index; epilogue
    charge(ctx, 8);
    sh(v1, a0, select_rec::kCursor);
    sh(v1, a0, select_rec::kCursor2);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003A3CE0 itfMesMngSetTextPosition -- 184 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// itfMesMngSetTextPosition(slot, x, y): moves the text sub-record to (x, y): when either delta is non-zero, offsets
// every node of the laid-out text (itfMesMngTextOffsetNodes(nodes, dx, dy)) and stores x / y at handle +36 / +40.
// K_Assert line 2512. Blocks: entry 19; assert 5; deltas 7; dy test 2 (only when dx == 0); move 5; return 8.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngSetTextPosition(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sll,
          hg::sq, hg::subu, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a3ce0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;  // x
    s0 = a2;  // y
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    a0 = sll(v1, 2);
    la(v1, kItfMesSlotCurrentHandle);
    v1 = addu(v1, a0);
    lw(s3, v1, 0);
    if (s3 == 0) {
        // 0x003a3d2c: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A3D38u, kItfMesManagerFile, 2512);
    }
    // 0x003a3d40: s2 = &handle->text; a1 = dx, a2 = dy
    charge(ctx, 7);
    s2 = addiu(s3, mes_handle::kText);
    lw(v1, s3, mes_handle::kText + text_rec::kX);
    a1 = subu(s1, v1);
    lw(v1, s3, mes_handle::kText + text_rec::kY);
    a2 = subu(s0, v1);
    bool moved = true;  // dx != 0, or dy != 0
    if (a1 == 0) {
        // 0x003a3d5c: dx == 0: test dy
        charge(ctx, 2);
        moved = a2 != 0;
    }
    if (moved) {
        // 0x003a3d64: offset the nodes, store the new position
        charge(ctx, 5);
        lw(a0, s2, text_rec::kNodes);
        jal(ctx, 0x3A3D68u, gen::fn_itfMesMngTextOffsetNodes_003a6310);
        sw(s1, s2, text_rec::kX);
        sw(s0, s2, text_rec::kY);
    }
    // 0x003a3d78: epilogue
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003A3F90 itfMesMngGetMessageArg -- 120 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// itfMesMngGetMessageArg(slot, i): word i of the handle's 32-word argument table (+212; no bounds check). K_Assert
// line 2778. Blocks: entry 16; assert 5; load 9.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngGetMessageArg(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sll,
          hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a3f90
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;  // i
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v0 = sll(a0, 1);
    v0 = addu(v0, a0);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    v1 = sll(v0, 2);
    la(v0, kItfMesSlotCurrentHandle);
    v0 = addu(v0, v1);
    lw(s1, v0, 0);
    if (s1 == 0) {
        // 0x003a3fd0: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A3FDCu, kItfMesManagerFile, 2778);
    }
    // 0x003a3fe4: v0 = handle->args[i]; epilogue
    charge(ctx, 9);
    v0 = sll(s0, 2);
    v0 = addu(v0, s1);
    lw(v0, v0, mes_handle::kArgs);  // handle->args[i]
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003A5120 itfMesMngGetMessageType -- 124 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// itfMesMngGetMessageType(slot, i): the type word (0 dialogue, 1 selection) of entry i of the BMD the slot's
// handle is bound to: *(bmd + 0x20 + 8 * i). K_Assert line 3888. Blocks: entry 16; assert 5; load 10.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngGetMessageType(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sll,
          hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a5120
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;  // i
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v0 = sll(a0, 1);
    v0 = addu(v0, a0);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    v1 = sll(v0, 2);
    la(v0, kItfMesSlotCurrentHandle);
    v0 = addu(v0, v1);
    lw(s1, v0, 0);
    if (s1 == 0) {
        // 0x003a5160: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A516Cu, kItfMesManagerFile, 3888);
    }
    // 0x003a5174: v0 = bmd->entries[i].type; epilogue
    charge(ctx, 10);
    lw(v1, s1, mes_handle::kBmd);
    v0 = sll(s0, 3);  // 8 * i (bmd_img::kEntrySize)
    v0 = addu(v0, v1);
    lw(v0, v0, bmd_img::kEntries + bmd_img::kEntryType);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003A51A0 itfMesMngGetMessageCount -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// itfMesMngGetMessageCount(slot): the message count of the BMD the slot's handle is bound to. K_Assert line 3911.
// Blocks: entry 14; assert 5; loads 7.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngGetMessageCount(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sll,
          hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a51a0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v0 = sll(a0, 1);
    v0 = addu(v0, a0);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    v1 = sll(v0, 2);
    la(v0, kItfMesSlotCurrentHandle);
    v0 = addu(v0, v1);
    lw(s0, v0, 0);
    if (s0 == 0) {
        // 0x003a51d8: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A51E4u, kItfMesManagerFile, 3911);
    }
    // 0x003a51ec: v0 = handle->bmd->message_count; epilogue
    charge(ctx, 7);
    lw(v0, s0, mes_handle::kBmd);
    lw(v0, v0, bmd_img::kMessageCount);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003A6A80 itfMesMngSetWindowOffset -- 128 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// itfMesMngSetWindowOffset(slot, a, b): handle +480 = a, +482 = b (s16 each). K_Assert line 5152. Blocks: entry 18;
// assert 5; stores 9.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngSetWindowOffset(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sh,
          hg::sll, hg::sq;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a6a80
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;  // a
    s0 = a2;  // b
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    a0 = sll(v1, 2);
    la(v1, kItfMesSlotCurrentHandle);
    v1 = addu(v1, a0);
    lw(s2, v1, 0);
    if (s2 == 0) {
        // 0x003a6ac8: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A6AD4u, kItfMesManagerFile, 5152);
    }
    // 0x003a6adc: the two offsets; epilogue
    charge(ctx, 9);
    sh(s1, s2, mes_handle::kWindowOffsetA);
    sh(s0, s2, mes_handle::kWindowOffsetB);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003A3AB0 itfMesMngResetSelectionBySlot -- 68 bytes; frame 0x10: ra sp+0x0
// itfMesMngResetSelectionBySlot(slot): itfMesMngResetSelection on the slot's handle (no assert here; the callee
// asserts). One block of 17 around the call: $v0 holds the slot word's address (the lookup's scratch) when
// itfMesMngResetSelection starts; only its sub_3B0170 call can change it.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngResetSelectionBySlot(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a3ab0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    // the slot's handle: *(kItfMesSlotCurrentHandle + 52 * slot) (13 * slot, then << 2)
    v0 = sll(a0, 1);
    v0 = addu(v0, a0);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    v1 = sll(v0, 2);
    la(v0, kItfMesSlotCurrentHandle);
    v0 = addu(v0, v1);
    lw(a0, v0, 0);  // a0 = the handle
    jal(ctx, 0x3A3ADCu, gen::fn_itfMesMngResetSelection_003a3b00);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003A3B00 itfMesMngResetSelection -- 152 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// itfMesMngResetSelection(handle): releases the selection's text node (+76, through the still-recompiled
// sub_3B0170) and clears the selection sub-record: word84 = 0, option count = 0, cursor = -1, choice mask = 0;
// then state &= ~0x38 and state &= ~0x40000. K_Assert line 2354 on a null handle. Blocks: entry 7; assert 5; node
// test 4; release 3; clear 19.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngResetSelection(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lui, hg::lw, hg::sd, hg::sh,
          hg::si, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a3b00
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;  // handle
    if (s0 == 0) {
        // 0x003a3b1c: K_Assert(handle != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A3B28u, kItfMesManagerFile, 2354);
    }
    // 0x003a3b30: s1 = &handle->select
    charge(ctx, 4);
    s1 = addiu(s0, mes_handle::kSelect);
    lw(a0, s0, mes_handle::kSelect + select_rec::kNode);
    if (a0 != 0) {
        // 0x003a3b40: release the options' text node
        charge(ctx, 3);
        jal(ctx, 0x3A3B40u, gen::fn_sub_3B0170_003b0170);
        sw(zero, s1, select_rec::kNode);
    }
    // 0x003a3b4c: clear the selection sub-record and the selection state bits; epilogue
    charge(ctx, 19);
    sh(zero, s1, select_rec::kWord84);
    sh(zero, s1, select_rec::kOptionCount);
    v1 = si(select_rec::kNone);
    sh(v1, s1, select_rec::kCursor);
    sw(zero, s1, select_rec::kChoiceMask);
    lw(a0, s0, mes_handle::kState);
    v1 = si(~0x38);  // ~mes_handle::kStateSelectBits
    a0 = a0 & v1;
    sw(a0, s0, mes_handle::kState);
    v1 = lui(0xFFFB);
    v1 = v1 | 0xFFFF;  // ~mes_handle::kStateBit18
    v1 = a0 & v1;
    sw(v1, s0, mes_handle::kState);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003A2C90 itfMesMngSwitchCurrentHandle -- 236 bytes; frame 0x230: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// itfMesMngSwitchCurrentHandle(slot_va, i): makes entry i (0..3, K_Assert line 1625 otherwise) of the slot its
// current handle. Returns 0 when the entry is empty. Otherwise, when a handle was current, its 488 bytes are first
// copied to a buffer in this function's 560-byte frame (at +64), and afterwards the new handle takes the old state
// word and the old 44-byte panel sub-record (+168) from that copy; slot +12 and +16 both get the new handle.
// Returns the entry's address (slot + 20 + 8 * i). Blocks: entry 10; range test 3 (i >= 0); assert 5; entry test
// 5; empty 3; current test 3; save copy 5; switch 8; restore 9; result 1; epilogue 7. The frame stays on the guest
// stack (dead stack the gates compare).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngSwitchCurrentHandle(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::slti, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    constexpr s32 kSaved = 0x40;  // the copy of the old handle in this frame
    // 0x003a2c90
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x230);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;  // slot
    s1 = a1;  // i
    s0 = 0;   // saved: an old handle was copied
    bool in_range = false;
    if (i64(s1) >= 0) {
        // 0x003a2cb8: i < 4
        charge(ctx, 3);
        v0 = slti(s1, mes_slot::kEntryCount);
        in_range = v0 != 0;
    }
    if (!in_range) {
        // 0x003a2cc4: K_Assert(0 <= i < 4)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A2CD0u, kItfMesManagerFile, 1625);
    }
    // 0x003a2cd8: v0 = slot->entries[i].handle
    charge(ctx, 5);
    s1 = sll(s1, 3);  // 8 * i
    v0 = addu(s1, s2);
    lw(v0, v0, mes_slot::kEntries);
    if (v0 != 0) {
        // 0x003a2cf8: a1 = the current handle
        charge(ctx, 3);
        lw(a1, s2, mes_slot::kHandle);
        if (a1 != 0) {
            // 0x003a2d04: memcpy(frame + 0x40, current, 488)
            charge(ctx, 5);
            a0 = addiu(sp, kSaved);
            a2 = mes_handle::kSize;
            jal(ctx, 0x3A2D0Cu, gen::fn_memcpy_00521250);
            s0 = 1;
        }
        // 0x003a2d18: slot->handle = slot->handle_mirror = entries[i].handle; s1 = &entries[i]
        charge(ctx, 8);
        v1 = addu(s2, s1);
        s1 = addiu(v1, mes_slot::kEntries);
        lw(v0, v1, mes_slot::kEntries);
        sw(v0, s2, mes_slot::kHandle);
        lw(v0, v1, mes_slot::kEntries);
        sw(v0, s2, mes_slot::kHandleMirror);
        if (s0 != 0) {
            // 0x003a2d38: the new handle takes the old state and memcpy(new + 168, saved + 168, 44)
            charge(ctx, 9);
            lw(v1, sp, kSaved + mes_handle::kState);
            lw(v0, s2, mes_slot::kHandle);
            sw(v1, v0, mes_handle::kState);
            lw(v0, s2, mes_slot::kHandle);
            a0 = addiu(v0, mes_handle::kPanel);
            a1 = addiu(sp, kSaved + mes_handle::kPanel);
            a2 = mes_handle::kPanelSize;
            jal(ctx, 0x3A2D54u, gen::fn_memcpy_00521250);
        }
        // 0x003a2d5c: return &entries[i]
        charge(ctx, 1);
        v0 = s1;
    } else {
        // 0x003a2cec: an empty entry: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003a2d60: epilogue
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x230);
}

// 0x003A3010 itfMesMngGetBmdMessageCount -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// itfMesMngGetBmdMessageCount(bmd): K_Assert(itfMesMngCheckBmdMagic(bmd) == 1) (line 1788), then the header's
// message count. Blocks: entry 9; assert 5; load 6. itfMesMngCheckBmdMagic is the hand-written function of
// bmd_msg.cpp, reached through its entry point as the recompiled body reaches it.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngGetBmdMessageCount(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a3010
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;  // bmd
    jal(ctx, 0x3A3020u, gen::fn_itfMesMngCheckBmdMagic_003a5090);
    v1 = 1;
    if (v0 != v1) {
        // 0x003a3034: K_Assert("MSG0" / "MSG1")
        charge(ctx, 5);
        k_assert(a0, a1, 0x3A3040u, kItfMesManagerFile, 1788);
    }
    // 0x003a3048: v0 = bmd->message_count; epilogue
    charge(ctx, 6);
    lw(v0, s0, bmd_img::kMessageCount);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// --- message records and handle sub-records ----------------------------------------------------------

// 0x003A5940 itfMesMngGetDialogueLine -- 56 bytes; leaf frame (no stack)
// itfMesMngGetDialogueLine(record, i): the text of line i of a dialogue record (s16 count at +24, pointers from
// +28); 0 when i is out of range. Blocks: entry 3; range test 3 (i >= 0); out of range 3 / line 3; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void itfMesMngGetDialogueLine(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::charge, hg::enter, hg::i64, hg::lh, hg::lw, hg::sll, hg::slt;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003a5940: v0 = record->line_count
    enter(ctx, 3);  // entry check point + this block's cycles
    lh(v0, a0, dialogue_rec::kLineCount);
    bool in_range = false;  // 0 <= i < count
    if (i64(a1) >= 0) {
        // 0x003a594c: i < count
        charge(ctx, 3);
        v0 = slt(a1, v0);
        in_range = v0 != 0;
    }
    if (in_range) {
        // 0x003a5964: v0 = record->lines[i]
        charge(ctx, 3);
        v0 = sll(a1, 2);
        v0 = addu(v0, a0);
        lw(v0, v0, dialogue_rec::kLines);
    } else {
        // 0x003a5958: out of range: 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003a5970: return
    charge(ctx, 2);
}

// 0x003A6030 itfMesMngGetSpeakerName -- 44 bytes; leaf frame (no stack)
// itfMesMngGetSpeakerName(handle): the speaker name of the handle: the speaker table of the bound BMD (the
// BmdSpeakerBlock right after the message entries, bmd + 0x20 + 8 * message_count) at the u16 speaker index
// (handle +32). No range check. One block of 11.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfMesMngGetSpeakerName(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::enter, hg::lhu, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003a6030
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(v1, a0, mes_handle::kBmd);
    lw(v0, v1, bmd_img::kMessageCount);
    v0 = sll(v0, 3);    // 8 * message_count: a1 + 0x20 = the speaker block
    a1 = addu(v0, v1);
    lhu(v0, a0, mes_handle::kSpeaker + speaker_rec::kIndex);
    v1 = sll(v0, 2);
    lw(v0, a1, bmd_img::kEntries + bmd_img::kSpeakerTable);  // the speaker name table
    v0 = addu(v0, v1);
    lw(v0, v0, 0);      // table[index]
}

// 0x003A6100 itfMesMngCountClearBits -- 52 bytes; leaf frame (no stack)
// itfMesMngCountClearBits(n, mask): the number of clear bits among the low `n` bits of `mask` (the enabled
// options of a choice mask). Blocks: entry 3; test 2 (first); body 3 (+1 when clear) + step 2; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void itfMesMngCountClearBits(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::srl;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003a6100
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;  // count
    for (;;) {
        // 0x003a6124: while (n > 0)
        charge(ctx, 2);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
        // 0x003a610c: bit 0 of the mask clear -> ++count
        charge(ctx, 3);
        v1 = a1 & 0x1;
        if (v1 == 0) {
            // 0x003a6118
            charge(ctx, 1);
            v0 = addiu(v0, 1);
        }
        // 0x003a611c: --n; mask >>= 1
        charge(ctx, 2);
        a0 = addiu(a0, -1);
        a1 = srl(a1, 1);
    }
    // 0x003a612c: return count
    charge(ctx, 2);
}

// 0x003A5FD0 itfMesMngPushMessageArgs -- 96 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// itfMesMngPushMessageArgs(table): hands the 32 words at `table` (a handle's argument table) to the font: word i
// through frFontSetTagSlot(i, word) (frFont.c: kFrMessageArgTable[i] = word). Leaves table + 124 in $v0. Blocks:
// entry 8; test 3 (first); body 7; epilogue 6.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngPushMessageArgs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a5fd0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;  // table
    s0 = 0;   // i
    for (;;) {
        // 0x003a600c: for (i = 0; i < 32; ++i)
        charge(ctx, 3);
        v1 = slti(s0, mes_handle::kArgCount);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a5ff0: frFontSetTagSlot(i, table[i])
        charge(ctx, 7);
        v0 = sll(s0, 2);
        v0 = addu(s1, v0);
        a0 = s0;
        lw(a1, v0, 0);
        jal(ctx, 0x3A6000u, gen::fn_frFontSetTagSlot_003b2a10);
        s0 = addiu(s0, 1);
    }
    // 0x003a6018: epilogue
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003A6900 itfMesMngInitSpeakerRecord -- 44 bytes; leaf frame (no stack)
// itfMesMngInitSpeakerRecord(rec, defaults): with `defaults`, x = 656 and y = 2632; always name node = 0 and
// speaker index = 0xFFFF (none). Blocks: entry 2; defaults 4; clear 5.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfMesMngInitSpeakerRecord(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::sh, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003a6900
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a1 != 0) {
        // 0x003a6908: the default position
        charge(ctx, 4);
        v1 = speaker_rec::kDefaultX;
        sw(v1, a0, speaker_rec::kX);
        v1 = speaker_rec::kDefaultY;
        sw(v1, a0, speaker_rec::kY);
    }
    // 0x003a6918: no name node, no speaker
    charge(ctx, 5);
    sw(zero, a0, speaker_rec::kNameNode);
    v1 = speaker_rec::kNoSpeaker;
    sh(v1, a0, speaker_rec::kIndex);
}

// 0x003A6930 itfMesMngInitTextRecord -- 80 bytes; leaf frame (no stack)
// itfMesMngInitTextRecord(rec, defaults): with `defaults`, x = 864 and y = 2840; then clears the record (record,
// nodes, busy, tag flags, the line words, style, colour set, mode) and sets the alpha (+21) to 255. Blocks: entry
// 2; defaults 4; clear 14.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfMesMngInitTextRecord(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::sb, hg::sh, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003a6930
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a1 != 0) {
        // 0x003a6938: the default position
        charge(ctx, 4);
        v1 = text_rec::kDefaultX;
        sw(v1, a0, text_rec::kX);
        v1 = text_rec::kDefaultY;
        sw(v1, a0, text_rec::kY);
    }
    // 0x003a6948: clear the rest; alpha = 255
    charge(ctx, 14);
    sw(zero, a0, text_rec::kRecord);
    sw(zero, a0, text_rec::kNodes);
    sb(zero, a0, text_rec::kBusy);
    sb(zero, a0, text_rec::kTagFlags);
    sh(zero, a0, text_rec::kLastLine);
    sh(zero, a0, text_rec::kLine);
    sh(zero, a0, text_rec::kWord26);
    sb(zero, a0, text_rec::kStyle);
    sb(zero, a0, text_rec::kColourSet);
    sb(zero, a0, text_rec::kMode);
    v1 = text_rec::kOpaque;
    sb(v1, a0, text_rec::kAlpha);
}

// 0x003A6980 itfMesMngInitSelectRecord -- 68 bytes; leaf frame (no stack)
// itfMesMngInitSelectRecord(rec): x = 3824, y = 3904, everything else cleared, cursor and its copy = -1 (none).
// One block of 17.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfMesMngInitSelectRecord(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sh, hg::si, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003a6980
    enter(ctx, 17);  // entry check point + this block's cycles
    v1 = select_rec::kDefaultX;
    sw(v1, a0, select_rec::kX);
    v1 = select_rec::kDefaultY;
    sw(v1, a0, select_rec::kY);
    sw(zero, a0, select_rec::kNode);
    sw(zero, a0, select_rec::kChoiceMask);
    sh(zero, a0, select_rec::kWord84);
    v1 = si(select_rec::kNone);
    sh(v1, a0, select_rec::kCursor);
    sh(v1, a0, select_rec::kCursor2);
    sh(zero, a0, select_rec::kOptionCount);
    sw(zero, a0, select_rec::kWord28);
    sw(zero, a0, select_rec::kWord32);
    sh(zero, a0, select_rec::kHalf36);
    sh(zero, a0, select_rec::kHalf38);
}

// 0x003A69D0 itfMesMngInitPanelRecord -- 52 bytes; frame 0x10: ra sp+0x0
// itfMesMngInitPanelRecord(rec): three null panel pointers, then the still-recompiled sub_3A6CA0(rec, 0, 0) ($a0
// stays rec) resets the rest. One block of 13 around the call.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngInitPanelRecord(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd, hg::sw;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a69d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    sw(zero, a0, 0);  // the three itfPnl pointers
    sw(zero, a0, 4);
    sw(zero, a0, 8);
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x3A69ECu, gen::fn_sub_3A6CA0_003a6ca0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003A6A10 itfMesMngClearMessageArgs -- 48 bytes; leaf frame (no stack)
// itfMesMngClearMessageArgs(table): zeroes the 32 words of a handle's argument table. Blocks: entry 3; test 3
// (first); body 4; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfMesMngClearMessageArgs(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::sll, hg::slti, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003a6a10
    enter(ctx, 3);  // entry check point + this block's cycles
    a1 = 0;
    for (;;) {
        // 0x003a6a2c: for (i = 0; i < 32; ++i)
        charge(ctx, 3);
        v1 = slti(a1, mes_handle::kArgCount);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a6a1c: table[i] = 0
        charge(ctx, 4);
        v1 = sll(a1, 2);
        v1 = addu(a0, v1);
        sw(zero, v1, 0);
        a1 = addiu(a1, 1);
    }
    // 0x003a6a38: return
    charge(ctx, 2);
}

// 0x003A6A40 itfMesMngInitWindowRecord -- 52 bytes; leaf frame (no stack)
// itfMesMngInitWindowRecord(rec, keep): the byte at +0 cleared unless `keep`; +2..+11 cleared, the window offsets
// +12 = 568 and +14 = 395 (s16; itfMesMngSetWindowOffset writes them later). Blocks: entry 2; clear byte 1; the rest 10.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfMesMngInitWindowRecord(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::sb, hg::sh, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003a6a40
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a1 == 0) {
        // 0x003a6a48: not kept: clear the byte at +0
        charge(ctx, 1);
        sb(zero, a0, window_rec::kByte0);
    }
    // 0x003a6a4c: the rest
    charge(ctx, 10);
    sh(zero, a0, window_rec::kHalf2);
    sh(zero, a0, window_rec::kHalf4);
    sh(zero, a0, window_rec::kHalf6);
    sw(zero, a0, window_rec::kWord8);
    v1 = window_rec::kDefaultOffsetA;
    sh(v1, a0, window_rec::kOffsetA);
    v1 = window_rec::kDefaultOffsetB;
    sh(v1, a0, window_rec::kOffsetB);
}

// 0x003A6C10 itfMesMngFormatNumber -- 144 bytes; frame 0x30
// itfMesMngFormatNumber(n, out): writes the decimal digits of n (at most 10, most significant first) as two-byte
// glyph codes ((d + 16) << 8) + 0x8080 at out, then a 0 halfword; returns the address of that terminator. The
// digits come from repeated div by 10, least significant first, into a 48-byte leaf frame (dead stack); a
// non-positive quotient stops the loop. Blocks: entry 3; digit 10 (two divs), more-digits test 3 + back-edge;
// reverse setup 3; reverse test 2 (first) + back-edge, store 10; terminator 5.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngFormatNumber(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::div, hg::enter, hg::i64, hg::lw, hg::mfhi,
          hg::mflo, hg::sh, hg::sll, hg::slti, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29};
    // 0x003a6c10
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a3 = 0;   // digit count
    a2 = 10;
    for (;;) {
        // 0x003a6c1c: digits[count++] = n % 10; n /= 10
        charge(ctx, 10);
        div(a0, a2);
        mfhi(v1);
        v0 = sll(a3, 2);
        v0 = addu(v0, sp);
        sw(v1, v0, 0);
        div(a0, a2);
        mflo(a0);
        a3 = addiu(a3, 1);
        if (i64(a0) > 0) {
            // 0x003a6c44: n > 0: another digit while count < 10
            charge(ctx, 3);
            v0 = slti(a3, 10);
            if (v0 != 0) {
                backedge(ctx);
                continue;
            }
        }
        break;
    }
    // 0x003a6c50: from the last digit down
    charge(ctx, 3);
    v1 = addiu(a3, -1);
    for (;;) {
        // 0x003a6c84: while (i >= 0)
        charge(ctx, 2);
        if (i64(v1) < 0) {
            break;
        }
        backedge(ctx);
        // 0x003a6c5c: *out++ = ((digits[i--] + 16) << 8) + 0x8080
        charge(ctx, 10);
        v0 = sll(v1, 2);
        v0 = addu(v0, sp);
        lw(v0, v0, 0);
        v0 = addiu(v0, 16);
        v0 = sll(v0, 8);
        v0 = addiu(v0, 32767);  // + 0x8080 in two steps (0x7FFF + 0x81)
        v0 = addiu(v0, 129);
        sh(v0, a1, 0);
        v1 = addiu(v1, -1);
        a1 = addiu(a1, 2);
    }
    // 0x003a6c8c: the terminator; return its address
    charge(ctx, 5);
    sh(zero, a1, 0);
    v0 = a1;
    sp = addiu(sp, 0x30);
}

// --- text line-node lists ----------------------------------------------------------------------------

// 0x003A6280 itfMesMngTextGetLastNode -- 48 bytes; leaf frame (no stack)
// itfMesMngTextGetLastNode(node): the last node of a text line-node list (following +36). Blocks: entry 2;
// load/test 6 (first); step 1 after the back-edge check; return 3.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void itfMesMngTextGetLastNode(EEContext& ctx) {
    using hg::Gpr, hg::backedge, hg::charge, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x003a6280
    enter(ctx, 2);  // entry check point + this block's cycles
    for (;;) {
        // 0x003a628c: while (node->next)
        charge(ctx, 6);
        lw(v0, a0, line_node::kNext);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a6288: node = node->next
        charge(ctx, 1);
        a0 = v0;
    }
    // 0x003a62a4: return node
    charge(ctx, 3);
    v0 = a0;
}

// 0x003A62B0 itfMesMngTextCopyNodeStyle -- 48 bytes; leaf frame (no stack)
// itfMesMngTextCopyNodeStyle(node, text): copies a laid-out node's look into the text sub-record (sub_3A5980
// calls it after the layout): text.alpha = node.alpha >> 1; text.style / colour set / mode = the style glyph's
// (node +32) style / colour set / mode. One block of 12; `lbu; sra 1` of a byte is a plain >> 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfMesMngTextCopyNodeStyle(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lbu, hg::lw, hg::sb, hg::sra;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x003a62b0
    enter(ctx, 12);  // entry check point + this block's cycles
    lw(a2, a0, line_node::kStyleGlyph);
    lbu(v1, a0, line_node::kAlpha);
    v1 = sra(v1, 1);
    sb(v1, a1, text_rec::kAlpha);
    lbu(v1, a2, glyph_node::kStyle);
    sb(v1, a1, text_rec::kStyle);
    lbu(v1, a2, glyph_node::kColourSet);
    sb(v1, a1, text_rec::kColourSet);
    lbu(v1, a2, glyph_node::kMode);
    sb(v1, a1, text_rec::kMode);
}

// 0x003A62E0 itfMesMngTextGetLineIndex -- 40 bytes; leaf frame (no stack)
// itfMesMngTextGetLineIndex(node, first): the 1-based line of `node` in the page that starts at `first`:
// ((node.y - first.y) >> 3) / first.line_step + 1 (EE div: HI/LO as the original). One block of 10.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfMesMngTextGetLineIndex(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::div, hg::enter, hg::lh, hg::lw, hg::mflo, hg::sra, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003a62e0
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(v1, a1, line_node::kY);
    lw(v0, a0, line_node::kY);
    v0 = subu(v1, v0);
    v1 = sra(v0, 3);
    lh(v0, a1, line_node::kLineStep);
    div(v1, v0);
    mflo(v0);
    v0 = addiu(v0, 1);
}

// 0x003A6310 itfMesMngTextOffsetNodes -- 52 bytes; leaf frame (no stack)
// itfMesMngTextOffsetNodes(node, dx, dy): every node of the list moves by (dx, dy). Blocks: entry 2; test 2
// (first); body 7; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfMesMngTextOffsetNodes(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x003a6310
    enter(ctx, 2);  // entry check point + this block's cycles
    for (;;) {
        // 0x003a6334: while (node)
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a6318: node->x += dx; node->y += dy; node = node->next
        charge(ctx, 7);
        lw(v1, a0, line_node::kX);
        v1 = addu(v1, a1);
        sw(v1, a0, line_node::kX);
        lw(v1, a0, line_node::kY);
        v1 = addu(v1, a2);
        sw(v1, a0, line_node::kY);
        lw(a0, a0, line_node::kNext);
    }
    // 0x003a633c: return
    charge(ctx, 2);
}

// 0x003A6350 itfMesMngTextSetNodesWord20 -- 44 bytes; leaf frame (no stack)
// itfMesMngTextSetNodesWord20(node, value): every node's +20 word = value (sub_3A5980 passes the handle's +12
// word). Blocks: entry 2; test 5 (first); body 2; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfMesMngTextSetNodesWord20(EEContext& ctx) {
    using hg::Gpr, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x003a6350
    enter(ctx, 2);  // entry check point + this block's cycles
    for (;;) {
        // 0x003a6360: while (node)
        charge(ctx, 5);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a6358: node->word20 = value; node = node->next
        charge(ctx, 2);
        sw(a1, a0, line_node::kWord20);
        lw(a0, a0, line_node::kNext);
    }
    // 0x003a6374: return
    charge(ctx, 2);
}

// 0x003A6380 itfMesMngTextSetLineAlpha -- 144 bytes; leaf frame (no stack)
// itfMesMngTextSetLineAlpha(node, first, last, alpha): walks the list past (last - first - 1) line changes (a
// node with a new y starts a line; running off the list returns), then sets the colour-set byte (+20) of every
// glyph of the nodes of the line it reached to `alpha`. The recompiled block graph: entry 5; T1 (2) lines left
// > 0 -> (check) B; B (5) same y -> (check) A, else C; A (3) next node, null -> return; C (2) --left, y =
// node.y -> T1; D (1); E (3) glyph = node.glyphs; T2 (5) glyph -> (check) F; F (2) set, next glyph; G (3) next
// node, null -> return; H (3) same y -> (check) E; R (2) return.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: logic (memory, saved registers)).
void itfMesMngTextSetLineAlpha(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::lw, hg::sb, hg::subu;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x003a6380: a1 = lines left to skip (last - first - 1), a2 = the current line's y
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = subu(a2, a1);
    a1 = addiu(v1, -1);
    lw(a2, a0, line_node::kY);
    bool reached = false;  // the line was reached (else the list ran out)
    for (;;) {
        // 0x003a63bc (T1): no line left to skip -> set the glyphs
        charge(ctx, 2);
        if (i64(a1) <= 0) {
            reached = true;
            break;
        }
        backedge(ctx);
        bool new_line = false;
        for (;;) {
            // 0x003a63a0 (B): the node still on the current line?
            charge(ctx, 5);
            lw(v1, a0, line_node::kY);
            if (a2 != v1) {
                new_line = true;
                break;
            }
            backedge(ctx);
            // 0x003a6394 (A): node = node->next; the list ran out -> return
            charge(ctx, 3);
            lw(a0, a0, line_node::kNext);
            if (a0 == 0) {
                break;
            }
        }
        if (!new_line) {
            break;
        }
        // 0x003a63b4 (C): a new line: --left, y = its y
        charge(ctx, 2);
        a1 = addiu(a1, -1);
        a2 = v1;
    }
    if (reached) {
        // 0x003a63c4 (D): a1 = alpha
        charge(ctx, 1);
        a1 = a3 & 0xFF;
        for (;;) {
            // 0x003a63c8 (E): v1 = node->glyphs
            charge(ctx, 3);
            lw(v1, a0, line_node::kGlyphs);
            for (;;) {
                // 0x003a63dc (T2): while (glyph)
                charge(ctx, 5);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003a63d4 (F): glyph->colour_set = alpha; glyph = glyph->next
                charge(ctx, 2);
                sb(a1, v1, glyph_node::kColourSet);
                lw(v1, v1, glyph_node::kNext);
            }
            // 0x003a63f0 (G): node = node->next
            charge(ctx, 3);
            lw(a0, a0, line_node::kNext);
            if (a0 != 0) {
                // 0x003a63fc (H): still on the line -> its glyphs too
                charge(ctx, 3);
                lw(v1, a0, line_node::kY);
                if (a2 == v1) {
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x003a6408 (R): return
    charge(ctx, 2);
}

// 0x003A6410 itfMesMngTextSetGlyphColour -- 72 bytes; leaf frame (no stack)
// itfMesMngTextSetGlyphColour(node, value): every glyph of every node of the list: rgba = (rgba & ~0xFF) |
// value. Blocks: entry 3; node test 2 (first); glyph setup 3; glyph test 2 (first); glyph body 5; next node 1;
// return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfMesMngTextSetGlyphColour(EEContext& ctx) {
    using hg::Gpr, hg::backedge, hg::charge, hg::enter, hg::lw, hg::si, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x003a6410
    enter(ctx, 3);  // entry check point + this block's cycles
    a2 = si(-256);  // ~0xFF
    for (;;) {
        // 0x003a6448: while (node)
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a641c: glyph = node->glyphs
        charge(ctx, 3);
        lw(a3, a0, line_node::kGlyphs);
        for (;;) {
            // 0x003a643c: while (glyph)
            charge(ctx, 2);
            if (a3 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003a6428: glyph->rgba = (glyph->rgba & ~0xFF) | value; glyph = glyph->next
            charge(ctx, 5);
            lw(v1, a3, glyph_node::kRgba);
            v1 = v1 & a2;
            v1 = v1 | a1;
            sw(v1, a3, glyph_node::kRgba);
            lw(a3, a3, glyph_node::kNext);
        }
        // 0x003a6444: node = node->next
        charge(ctx, 1);
        lw(a0, a0, line_node::kNext);
    }
    // 0x003a6450: return
    charge(ctx, 2);
}

// 0x003A6460 itfMesMngTextGetMaxLineWidth -- 88 bytes; leaf frame (no stack)
// itfMesMngTextGetMaxLineWidth(node): the largest sum of the glyph counts (+12) of the nodes of one line (a run
// of nodes with the same y), x16. Blocks: entry 3; outer test 2 (first); line setup 2; sum 5; same-line test 3
// (+ check); max test 3 (+1 on a new maximum); result 3.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfMesMngTextGetMaxLineWidth(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sll, hg::slt;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x003a6460
    enter(ctx, 3);  // entry check point + this block's cycles
    a2 = 0;  // the widest line so far
    for (;;) {
        // 0x003a64a4: while (node)
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a646c: a new line: v1 = its y, a1 = its sum
        charge(ctx, 2);
        lw(v1, a0, line_node::kY);
        a1 = 0;
        for (;;) {
            // 0x003a6474: sum += node->glyph_count; node = node->next
            charge(ctx, 5);
            lw(v0, a0, line_node::kGlyphCount);
            a1 = addu(a1, v0);
            lw(a0, a0, line_node::kNext);
            if (a0 != 0) {
                // 0x003a6488: the next node on the same line?
                charge(ctx, 3);
                lw(v0, a0, line_node::kY);
                if (v1 == v0) {
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
        // 0x003a6494: a new maximum?
        charge(ctx, 3);
        at = slt(a2, a1);
        if (at != 0) {
            // 0x003a64a0
            charge(ctx, 1);
            a2 = a1;
        }
    }
    // 0x003a64ac: return max << 4
    charge(ctx, 3);
    v0 = sll(a2, 4);
}

// 0x003A64C0 itfMesMngTextResetNodes -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// itfMesMngTextResetNodes(node): frFontLineResetAlpha on every node of the list whose first glyph has mode 0
// (+22: not fading). Blocks: entry 6; test 2 (first); glyph test 4; reset call 3; next 1; epilogue 5.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfMesMngTextResetNodes(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sq;
    Gpr v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a64c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;  // node
    for (;;) {
        // 0x003a64f8: while (node)
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a64d8: node->glyphs->mode == 0?
        charge(ctx, 4);
        lw(v1, s0, line_node::kGlyphs);
        lbu(v1, v1, glyph_node::kMode);
        if (v1 == 0) {
            // 0x003a64e8: frFontLineResetAlpha(node)
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x3A64ECu, gen::fn_frFontLineResetAlpha_003b0c70);
        }
        // 0x003a64f4: node = node->next
        charge(ctx, 1);
        lw(s0, s0, line_node::kNext);
    }
    // 0x003a6500: epilogue
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// --- itfPnl per-type vertex tables -------------------------------------------------------------------

// 0x003A96F0 itfPnlSetVertexType0 -- 136 bytes; frame 0x10
// itfPnlSetVertexType0(buf, x0, y0, x1, y1): four columns {x0, x0 + 512, x1 - 512, x1} (the middle two meet at
// the centre when the panel is narrower than 1024), one {x, y0, x, y1} edge each, 16 bytes apart from buf. The
// columns sit in a 16-byte leaf frame (dead stack). Blocks: entry 10; narrow 5; setup 3; test 3 (first); body 10;
// return 3.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfPnlSetVertexType0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sll, hg::slt, hg::slti,
          hg::sra, hg::subu, hg::sw;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29};
    constexpr s32 kCols = 0x0;  // s32[4] in the frame
    // 0x003a96f0: the columns {x0, x0 + 512, x1 - 512, x1}
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sw(a1, sp, kCols + 0x0);
    t1 = addiu(a1, pnl_buf::kCorner);
    sw(t1, sp, kCols + 0x4);
    v1 = addiu(a3, -pnl_buf::kCorner);
    sw(v1, sp, kCols + 0x8);
    sw(a3, sp, kCols + 0xC);
    at = slt(v1, t1);
    if (at != 0) {
        // 0x003a9718: narrower than two corners: both middle columns at the centre
        charge(ctx, 5);
        v1 = subu(a3, a1);
        v1 = sra(v1, 1);
        v1 = addu(a1, v1);
        sw(v1, sp, kCols + 0x4);
        sw(v1, sp, kCols + 0x8);
    }
    // 0x003a972c
    charge(ctx, 3);
    a1 = 0;  // column c
    for (;;) {
        // 0x003a9760: for (c = 0; c < 4; ++c)
        charge(ctx, 3);
        v1 = slti(a1, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a9738: *buf++ = {col[c], y0, col[c], y1}
        charge(ctx, 10);
        v1 = sll(a1, 2);
        v1 = addu(v1, sp);
        v1 = addiu(v1, kCols);
        lw(v1, v1, 0);
        sw(v1, a0, 0);
        sw(a2, a0, 4);
        sw(v1, a0, 8);
        sw(t0, a0, 12);
        a0 = addiu(a0, pnl_buf::kQuadEdgeSize);
        a1 = addiu(a1, 1);
    }
    // 0x003a976c: return
    charge(ctx, 3);
    sp = addiu(sp, 0x10);
}

// 0x003A9780 itfPnlSetVertexType1 -- 420 bytes; frame 0x20
// itfPnlSetVertexType1(buf, x0, y0, x1, y1): a 4 x 4 grid {x0 - 256, x0 + 512, x1 - 512, x1 + 256} x {y0 - 128,
// y0 + 128, y1 - 128, y1 + 128}, then the top band: 3 rows at y0 + {0, 8, 48} (kItfPnlVertexStepTable) and the
// bottom band: 3 rows at y1 - {0, 8, 48}, each over {x0 - 256, x0 + 1024, x1 - 1024, x1 + 256}; 40 vertices of 8
// bytes. The rows and columns sit in a 32-byte leaf frame (dead stack). Blocks: entry 20; the grid (row setup 6,
// vertex 7); band setup 14; top band (row setup 7); setup 6; bottom band (row setup 7); return 3.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfPnlSetVertexType1(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sll, hg::slti, hg::subu,
          hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29};
    constexpr s32 kRows = 0x0;   // s32[4] in the frame: the y of each row
    constexpr s32 kCols = 0x10;  // s32[4] in the frame: the x of each column
    // 0x003a9780: the 4 x 4 grid: columns {x0 - 256, x0 + 512, x1 - 512, x1 + 256}, rows {y0 - 128, y0 + 128, y1 - 128, y1 + 128}
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = addiu(a1, -pnl_buf::kOuterX);
    sw(v1, sp, kCols + 0x0);
    v1 = addiu(a1, pnl_buf::kCorner);
    sw(v1, sp, kCols + 0x4);
    v1 = addiu(a3, -pnl_buf::kCorner);
    sw(v1, sp, kCols + 0x8);
    v1 = addiu(a3, pnl_buf::kOuterX);
    sw(v1, sp, kCols + 0xC);
    v1 = addiu(a2, -pnl_buf::kOuterY);
    sw(v1, sp, kRows + 0x0);
    v1 = addiu(a2, pnl_buf::kOuterY);
    sw(v1, sp, kRows + 0x4);
    v1 = addiu(t0, -pnl_buf::kOuterY);
    sw(v1, sp, kRows + 0x8);
    v1 = addiu(t0, pnl_buf::kOuterY);
    sw(v1, sp, kRows + 0xC);
    t3 = 0;  // row r
    for (;;) {
        // 0x003a9814: for (r = 0; r < 4; ++r)
        charge(ctx, 3);
        v1 = slti(t3, pnl_buf::kGridSize);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a97d0: t1 = rows[r]
        charge(ctx, 6);
        t2 = 0;  // column c
        v1 = sll(t3, 2);
        v1 = addu(v1, sp);
        lw(t1, v1, kRows);
        for (;;) {
            // 0x003a9804: for (c = 0; c < 4; ++c)
            charge(ctx, 3);
            v1 = slti(t2, pnl_buf::kGridSize);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003a97e8: *buf++ = {cols[c], rows[r]}
            charge(ctx, 7);
            v1 = sll(t2, 2);
            v1 = addu(v1, sp);
            lw(v1, v1, kCols);
            sw(v1, a0, 0);
            sw(t1, a0, 4);
            a0 = addiu(a0, pnl_buf::kVertexSize);
            t2 = addiu(t2, 1);
        }
        // 0x003a9810
        charge(ctx, 1);
        t3 = addiu(t3, 1);
    }
    // 0x003a9820: the band columns {x0 - 256, x0 + 1024, x1 - 1024, x1 + 256}; a3 = the row steps {0, 8, 48}
    charge(ctx, 14);
    v1 = addiu(a1, -pnl_buf::kOuterX);
    sw(v1, sp, kCols + 0x0);
    v1 = addiu(a1, pnl_buf::kBandX);
    sw(v1, sp, kCols + 0x4);
    v1 = addiu(a3, -pnl_buf::kBandX);
    sw(v1, sp, kCols + 0x8);
    v1 = addiu(a3, pnl_buf::kOuterX);
    sw(v1, sp, kCols + 0xC);
    sw(a2, sp, kRows + 0x0);
    t2 = 0;  // band row r
    la(a3, kItfPnlVertexStepTable);
    for (;;) {
        // 0x003a98a0: for (r = 0; r < 3; ++r)
        charge(ctx, 3);
        v1 = slti(t2, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a9858: a1 = y0 + steps[r]
        charge(ctx, 7);
        t1 = 0;  // column c
        v1 = sll(t2, 2);
        v1 = addu(a3, v1);
        lw(v1, v1, 0);
        a1 = addu(a2, v1);
        for (;;) {
            // 0x003a9890: for (c = 0; c < 4; ++c)
            charge(ctx, 3);
            v1 = slti(t1, pnl_buf::kGridSize);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003a9874: *buf++ = {cols[c], y0 + steps[r]}
            charge(ctx, 7);
            v1 = sll(t1, 2);
            v1 = addu(v1, sp);
            lw(v1, v1, kCols);
            sw(v1, a0, 0);
            sw(a1, a0, 4);
            a0 = addiu(a0, pnl_buf::kVertexSize);
            t1 = addiu(t1, 1);
        }
        // 0x003a989c
        charge(ctx, 1);
        t2 = addiu(t2, 1);
    }
    // 0x003a98ac: the bottom band; a2 = the row steps
    charge(ctx, 6);
    sw(t0, sp, kRows + 0x0);
    t1 = 0;  // band row r
    la(a2, kItfPnlVertexStepTable);
    for (;;) {
        // 0x003a990c: for (r = 0; r < 3; ++r)
        charge(ctx, 3);
        v1 = slti(t1, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a98c4: a1 = y1 - steps[r]
        charge(ctx, 7);
        a3 = 0;  // column c
        v1 = sll(t1, 2);
        v1 = addu(a2, v1);
        lw(v1, v1, 0);
        a1 = subu(t0, v1);
        for (;;) {
            // 0x003a98fc: for (c = 0; c < 4; ++c)
            charge(ctx, 3);
            v1 = slti(a3, pnl_buf::kGridSize);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003a98e0: *buf++ = {cols[c], y1 - steps[r]}
            charge(ctx, 7);
            v1 = sll(a3, 2);
            v1 = addu(v1, sp);
            lw(v1, v1, kCols);
            sw(v1, a0, 0);
            sw(a1, a0, 4);
            a0 = addiu(a0, pnl_buf::kVertexSize);
            a3 = addiu(a3, 1);
        }
        // 0x003a9908
        charge(ctx, 1);
        t1 = addiu(t1, 1);
    }
    // 0x003a9918: return
    charge(ctx, 3);
    sp = addiu(sp, 0x20);
}

// 0x003A9930 itfPnlSetVertexType2 -- 388 bytes; frame 0x20
// itfPnlSetVertexType2(buf, x0, y0, x1, y1): the same 4 x 4 grid as type 1, then 2 band rows at y0 + {0, 8} and 2
// at y1 - {0, 8} over {x0 - 256, x0 + 1024, x1 - 1024, x1 + 256}; 32 vertices. Blocks: entry 20; the grid (row
// setup 6); setup 12; top band (row setup 5); setup 4; bottom band (row setup 5); return 3.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfPnlSetVertexType2(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sll, hg::slti, hg::subu,
          hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29};
    constexpr s32 kRows = 0x0;   // s32[4] in the frame: the y of each row
    constexpr s32 kCols = 0x10;  // s32[4] in the frame: the x of each column
    // 0x003a9930: the 4 x 4 grid: columns {x0 - 256, x0 + 512, x1 - 512, x1 + 256}, rows {y0 - 128, y0 + 128, y1 - 128, y1 + 128}
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = addiu(a1, -pnl_buf::kOuterX);
    sw(v1, sp, kCols + 0x0);
    v1 = addiu(a1, pnl_buf::kCorner);
    sw(v1, sp, kCols + 0x4);
    v1 = addiu(a3, -pnl_buf::kCorner);
    sw(v1, sp, kCols + 0x8);
    v1 = addiu(a3, pnl_buf::kOuterX);
    sw(v1, sp, kCols + 0xC);
    v1 = addiu(a2, -pnl_buf::kOuterY);
    sw(v1, sp, kRows + 0x0);
    v1 = addiu(a2, pnl_buf::kOuterY);
    sw(v1, sp, kRows + 0x4);
    v1 = addiu(t0, -pnl_buf::kOuterY);
    sw(v1, sp, kRows + 0x8);
    v1 = addiu(t0, pnl_buf::kOuterY);
    sw(v1, sp, kRows + 0xC);
    t3 = 0;  // row r
    for (;;) {
        // 0x003a99c4: for (r = 0; r < 4; ++r)
        charge(ctx, 3);
        v1 = slti(t3, pnl_buf::kGridSize);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a9980: t1 = rows[r]
        charge(ctx, 6);
        t2 = 0;  // column c
        v1 = sll(t3, 2);
        v1 = addu(v1, sp);
        lw(t1, v1, kRows);
        for (;;) {
            // 0x003a99b4: for (c = 0; c < 4; ++c)
            charge(ctx, 3);
            v1 = slti(t2, pnl_buf::kGridSize);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003a9998: *buf++ = {cols[c], rows[r]}
            charge(ctx, 7);
            v1 = sll(t2, 2);
            v1 = addu(v1, sp);
            lw(v1, v1, kCols);
            sw(v1, a0, 0);
            sw(t1, a0, 4);
            a0 = addiu(a0, pnl_buf::kVertexSize);
            t2 = addiu(t2, 1);
        }
        // 0x003a99c0
        charge(ctx, 1);
        t3 = addiu(t3, 1);
    }
    // 0x003a99d0: the band columns {x0 - 256, x0 + 1024, x1 - 1024, x1 + 256}
    charge(ctx, 12);
    v1 = addiu(a1, -pnl_buf::kOuterX);
    sw(v1, sp, kCols + 0x0);
    v1 = addiu(a1, pnl_buf::kBandX);
    sw(v1, sp, kCols + 0x4);
    v1 = addiu(a3, -pnl_buf::kBandX);
    sw(v1, sp, kCols + 0x8);
    v1 = addiu(a3, pnl_buf::kOuterX);
    sw(v1, sp, kCols + 0xC);
    sw(a2, sp, kRows + 0x0);
    t1 = 0;  // band row r
    for (;;) {
        // 0x003a9a40: for (r = 0; r < 2; ++r)
        charge(ctx, 3);
        v1 = slti(t1, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a9a00: a1 = y0 + 8 * r
        charge(ctx, 5);
        a3 = 0;  // column c
        v1 = sll(t1, 3);
        a1 = addu(a2, v1);
        for (;;) {
            // 0x003a9a30: for (c = 0; c < 4; ++c)
            charge(ctx, 3);
            v1 = slti(a3, pnl_buf::kGridSize);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003a9a14: *buf++ = {cols[c], y0 + 8 * r}
            charge(ctx, 7);
            v1 = sll(a3, 2);
            v1 = addu(v1, sp);
            lw(v1, v1, kCols);
            sw(v1, a0, 0);
            sw(a1, a0, 4);
            a0 = addiu(a0, pnl_buf::kVertexSize);
            a3 = addiu(a3, 1);
        }
        // 0x003a9a3c
        charge(ctx, 1);
        t1 = addiu(t1, 1);
    }
    // 0x003a9a4c: the bottom band
    charge(ctx, 4);
    sw(t0, sp, kRows + 0x0);
    a3 = 0;  // band row r
    for (;;) {
        // 0x003a9a9c: for (r = 0; r < 2; ++r)
        charge(ctx, 3);
        v1 = slti(a3, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a9a5c: a1 = y1 - 8 * r
        charge(ctx, 5);
        a2 = 0;  // column c
        v1 = sll(a3, 3);
        a1 = subu(t0, v1);
        for (;;) {
            // 0x003a9a8c: for (c = 0; c < 4; ++c)
            charge(ctx, 3);
            v1 = slti(a2, pnl_buf::kGridSize);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003a9a70: *buf++ = {cols[c], y1 - 8 * r}
            charge(ctx, 7);
            v1 = sll(a2, 2);
            v1 = addu(v1, sp);
            lw(v1, v1, kCols);
            sw(v1, a0, 0);
            sw(a1, a0, 4);
            a0 = addiu(a0, pnl_buf::kVertexSize);
            a2 = addiu(a2, 1);
        }
        // 0x003a9a98
        charge(ctx, 1);
        a3 = addiu(a3, 1);
    }
    // 0x003a9aa8: return
    charge(ctx, 3);
    sp = addiu(sp, 0x20);
}

// 0x003A9AC0 itfPnlSetVertexType3 -- 40 bytes; leaf frame (no stack)
// itfPnlSetVertexType3(buf, x0, y0, x1, y1) (types 3 and 4): the rectangle's corners {x0, y0}, {x1, y0}, {x1,
// y1}, {x0, y1}. One block of 10.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void itfPnlSetVertexType3(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x003a9ac0
    enter(ctx, 10);  // entry check point + this block's cycles
    sw(a1, a0, 0);   // {x0, y0}
    sw(a2, a0, 4);
    sw(a3, a0, 8);   // {x1, y0}
    sw(a2, a0, 12);
    sw(a3, a0, 16);  // {x1, y1}
    sw(t0, a0, 20);
    sw(a1, a0, 24);  // {x0, y1}
    sw(t0, a0, 28);
}

// 0x003A9AF0 itfPnlSetVertexType5 -- 132 bytes; frame 0x20
// itfPnlSetVertexType5(buf, x0, y0, x1, y1): 2 rows {y0, y1} x 3 columns {x0, x1 - 1440, x1}: 6 vertices. The
// rows and columns sit in a 32-byte leaf frame (dead stack). Blocks: entry 10; 2 rows (setup 6) of 3 columns
// (test 3, vertex 7, step 1); return 3.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfPnlSetVertexType5(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sll, hg::slti, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29};
    constexpr s32 kRows = 0x8;   // s32[2] in the frame: {y0, y1}
    constexpr s32 kCols = 0x10;  // s32[3] in the frame: {x0, x1 - 1440, x1}
    // 0x003a9af0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sw(a1, sp, kCols + 0x0);
    v1 = addiu(a3, -pnl_buf::kType5Notch);
    sw(v1, sp, kCols + 0x4);
    sw(a3, sp, kCols + 0x8);
    sw(a2, sp, kRows + 0x0);
    sw(t0, sp, kRows + 0x4);
    a3 = 0;  // row r
    for (;;) {
        // 0x003a9b5c: for (r = 0; r < 2; ++r)
        charge(ctx, 3);
        v1 = slti(a3, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a9b18: a1 = rows[r]
        charge(ctx, 6);
        a2 = 0;  // column c
        v1 = sll(a3, 2);
        v1 = addu(v1, sp);
        lw(a1, v1, kRows);
        for (;;) {
            // 0x003a9b4c: for (c = 0; c < 3; ++c)
            charge(ctx, 3);
            v1 = slti(a2, 3);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003a9b30: *buf++ = {cols[c], rows[r]}
            charge(ctx, 7);
            v1 = sll(a2, 2);
            v1 = addu(v1, sp);
            lw(v1, v1, kCols);
            sw(v1, a0, 0);
            sw(a1, a0, 4);
            a0 = addiu(a0, pnl_buf::kVertexSize);
            a2 = addiu(a2, 1);
        }
        // 0x003a9b58
        charge(ctx, 1);
        a3 = addiu(a3, 1);
    }
    // 0x003a9b68: return
    charge(ctx, 3);
    sp = addiu(sp, 0x20);
}

// 0x003A9B80 itfPnlSetVertexType8 -- 124 bytes; frame 0x10
// itfPnlSetVertexType8(buf, x0, y0, x1, y1): fixed columns {416, 1152, 7024, 7760}, one {x, y0 + 352, x, y1 -
// 320} edge each, written from buf + 4. The x arguments are unused. Blocks: entry 15; test 3 (first); body 10;
// return 3.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfPnlSetVertexType8(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sll, hg::slti, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29};
    constexpr s32 kCols = 0x0;  // s32[4] in the frame
    // 0x003a9b80: a3 = buf + 4; the columns; a1 = top, a0 = bottom
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = addiu(a0, pnl_buf::kType8Vertices);
    v1 = pnl_buf::kType8Columns[0];
    sw(v1, sp, kCols + 0x0);
    v1 = pnl_buf::kType8Columns[1];
    sw(v1, sp, kCols + 0x4);
    v1 = pnl_buf::kType8Columns[2];
    sw(v1, sp, kCols + 0x8);
    v1 = pnl_buf::kType8Columns[3];
    sw(v1, sp, kCols + 0xC);
    a1 = addiu(a2, pnl_buf::kType8Top);
    a0 = addiu(t0, -pnl_buf::kType8Bottom);
    a2 = 0;  // column c
    for (;;) {
        // 0x003a9be4: for (c = 0; c < 4; ++c)
        charge(ctx, 3);
        v1 = slti(a2, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a9bbc: *buf++ = {cols[c], top, cols[c], bottom}
        charge(ctx, 10);
        v1 = sll(a2, 2);
        v1 = addu(v1, sp);
        v1 = addiu(v1, kCols);
        lw(v1, v1, 0);
        sw(v1, a3, 0);
        sw(a1, a3, 4);
        sw(v1, a3, 8);
        sw(a0, a3, 12);
        a3 = addiu(a3, pnl_buf::kQuadEdgeSize);
        a2 = addiu(a2, 1);
    }
    // 0x003a9bf0: return
    charge(ctx, 3);
    sp = addiu(sp, 0x10);
}

// --- itfPnl per-type colour tables -------------------------------------------------------------------

// 0x003A9C00 itfPnlSetColorType0 -- 40 bytes; leaf frame (no stack)
// itfPnlSetColorType0(buf, r, g, b, a): the colour block after the 4 edges: {r, g, b, 0}, {r, g, b, a} at buf
// +64. One block of 10.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void itfPnlSetColorType0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x003a9c00
    enter(ctx, 10);  // entry check point + this block's cycles
    sw(a1, a0, pnl_buf::kType0Colour + 0);  // {r, g, b, 0}
    sw(a2, a0, pnl_buf::kType0Colour + 4);
    sw(a3, a0, pnl_buf::kType0Colour + 8);
    sw(zero, a0, pnl_buf::kType0Colour + 12);
    sw(a1, a0, pnl_buf::kType0Colour + 16);  // {r, g, b, a}
    sw(a2, a0, pnl_buf::kType0Colour + 20);
    sw(a3, a0, pnl_buf::kType0Colour + 24);
    sw(t0, a0, pnl_buf::kType0Colour + 28);
}

// 0x003A9C30 itfPnlSetColorType1 -- 88 bytes; frame 0x10: ra sp+0x0
// itfPnlSetColorType1(buf, r, g, b, a): {r, g, b, 1}, {r, g, b, a} at buf +320 (after the 40 vertices), then
// the 6 shaded colours of the factor table 0x6A1E00 at +352 (the still-recompiled sub_3B4A90(buf + 352, r, g, b,
// a, table, 6)). Leaves 1 in $v0. One block of 22 around the call.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfPnlSetColorType1(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a9c30
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = addiu(a0, pnl_buf::kType1Colour);
    sw(a1, a0, pnl_buf::kType1Colour + 0);  // {r, g, b, 1}
    sw(a2, a0, pnl_buf::kType1Colour + 4);
    sw(a3, a0, pnl_buf::kType1Colour + 8);
    v0 = 1;
    sw(v0, a0, pnl_buf::kType1Colour + 12);
    sw(a1, a0, pnl_buf::kType1Colour + 16);  // {r, g, b, a}
    sw(a2, a0, pnl_buf::kType1Colour + 20);
    sw(a3, a0, pnl_buf::kType1Colour + 24);
    sw(t0, a0, pnl_buf::kType1Colour + 28);
    a0 = addiu(v1, pnl_buf::kShadesAfter);
    la(t1, pnl_buf::kType1Shades);
    t2 = 6;
    jal(ctx, 0x3A9C70u, gen::fn_sub_3B4A90_003b4a90);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003A9C90 itfPnlSetColorType2 -- 88 bytes; frame 0x10: ra sp+0x0
// itfPnlSetColorType2(buf, r, g, b, a): {r, g, b, 1}, {r, g, b, a} at buf +256 (after the 32 vertices), then the
// 4 shaded colours of the factor table 0x6A1E60 at +288 (sub_3B4A90(buf + 288, r, g, b, a, table, 4)). Leaves 1
// in $v0. One block of 22 around the call.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfPnlSetColorType2(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a9c90
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = addiu(a0, pnl_buf::kType2Colour);
    sw(a1, a0, pnl_buf::kType2Colour + 0);  // {r, g, b, 1}
    sw(a2, a0, pnl_buf::kType2Colour + 4);
    sw(a3, a0, pnl_buf::kType2Colour + 8);
    v0 = 1;
    sw(v0, a0, pnl_buf::kType2Colour + 12);
    sw(a1, a0, pnl_buf::kType2Colour + 16);  // {r, g, b, a}
    sw(a2, a0, pnl_buf::kType2Colour + 20);
    sw(a3, a0, pnl_buf::kType2Colour + 24);
    sw(t0, a0, pnl_buf::kType2Colour + 28);
    a0 = addiu(v1, pnl_buf::kShadesAfter);
    la(t1, pnl_buf::kType2Shades);
    t2 = 4;
    jal(ctx, 0x3A9CD0u, gen::fn_sub_3B4A90_003b4a90);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003A9CF0 itfPnlSetColorType3 -- 152 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// itfPnlSetColorType3(buf, r, g, b, a): {r, g, b, a} at buf +32 (after the 4 corners); one shaded colour of
// 0x6A1EA0 at +48 (sub_3B4A90(buf + 48, r, g, b, a, table, 1)) and two of 0x6A1EB0 at alpha 128 at +64
// (sub_3B4A90(buf + 64, r, g, b, 128, table, 2)). One block of 38 around the two calls.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfPnlSetColorType3(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sq, hg::sw;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a9cf0
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a1;  // r
    s2 = a2;  // g
    s1 = a3;  // b
    s0 = addiu(a0, pnl_buf::kType3Colour);
    sw(s3, a0, pnl_buf::kType3Colour + 0);  // {r, g, b, a}
    sw(s2, a0, pnl_buf::kType3Colour + 4);
    sw(s1, a0, pnl_buf::kType3Colour + 8);
    sw(t0, a0, pnl_buf::kType3Colour + 12);
    a0 = addiu(s0, 16);  // one shaded colour at +48
    la(t1, pnl_buf::kType3ShadeA);
    t2 = 1;
    jal(ctx, 0x3A9D38u, gen::fn_sub_3B4A90_003b4a90);
    a0 = addiu(s0, 32);  // two shaded colours at +64, alpha 128
    a1 = s3;
    a2 = s2;
    a3 = s1;
    t0 = pnl_buf::kType3ShadeAlpha;
    la(t1, pnl_buf::kType3ShadeB);
    t2 = 2;
    jal(ctx, 0x3A9D60u, gen::fn_sub_3B4A90_003b4a90);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003A9D90 itfPnlSetColorType4 -- 24 bytes; leaf frame (no stack)
// itfPnlSetColorType4(buf, r, g, b, a): {r, g, b, a} at buf +32 (after the 4 corners). One block of 6.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void itfPnlSetColorType4(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x003a9d90
    enter(ctx, 6);  // entry check point + this block's cycles
    sw(a1, a0, pnl_buf::kType4Colour + 0);
    sw(a2, a0, pnl_buf::kType4Colour + 4);
    sw(a3, a0, pnl_buf::kType4Colour + 8);
    sw(t0, a0, pnl_buf::kType4Colour + 12);
}

// 0x003A9DB0 itfPnlSetColorType5 -- 40 bytes; leaf frame (no stack)
// itfPnlSetColorType5(buf, r, g, b, a): {r, g, b, 0}, {r, g, b, a} at buf +48 (after the 6 vertices). One block
// of 10.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void itfPnlSetColorType5(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x003a9db0
    enter(ctx, 10);  // entry check point + this block's cycles
    sw(a1, a0, pnl_buf::kType5Colour + 0);  // {r, g, b, 0}
    sw(a2, a0, pnl_buf::kType5Colour + 4);
    sw(a3, a0, pnl_buf::kType5Colour + 8);
    sw(zero, a0, pnl_buf::kType5Colour + 12);
    sw(a1, a0, pnl_buf::kType5Colour + 16);  // {r, g, b, a}
    sw(a2, a0, pnl_buf::kType5Colour + 20);
    sw(a3, a0, pnl_buf::kType5Colour + 24);
    sw(t0, a0, pnl_buf::kType5Colour + 28);
}

// 0x003A9DE0 itfPnlSetColorType8 -- 52 bytes; leaf frame (no stack)
// itfPnlSetColorType8(buf, ...): the fixed colour {115, 135, 255, 0} twice at buf +68 (after the 4 edges written
// from buf + 4); the colour arguments are ignored. Its scratch registers are $a1 / $a2 / $v1 (135, 115, 255). One
// block of 13.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfPnlSetColorType8(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x003a9de0
    enter(ctx, 13);  // entry check point + this block's cycles
    a2 = pnl_buf::kType8R;
    sw(a2, a0, pnl_buf::kType8Colour + 0);
    a1 = pnl_buf::kType8G;
    sw(a1, a0, pnl_buf::kType8Colour + 4);
    v1 = pnl_buf::kType8B;
    sw(v1, a0, pnl_buf::kType8Colour + 8);
    sw(zero, a0, pnl_buf::kType8Colour + 12);
    sw(a2, a0, pnl_buf::kType8Colour + 16);
    sw(a1, a0, pnl_buf::kType8Colour + 20);
    sw(v1, a0, pnl_buf::kType8Colour + 24);
    sw(zero, a0, pnl_buf::kType8Colour + 28);
}

// --- itfPnl phase callbacks --------------------------------------------------------------------------

// 0x003A9140 itfPnlAnimClear10 -- 48 bytes; frame 0x10: ra sp+0x0
// itfPnlAnimClear10(panel): memset(panel->work, 0, 16) -- the animation record closed and zeroed; returns 0 (panel type 10;
// itfPnlRegist2 installs it). One block of 12 around the call.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfPnlAnimClear10(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a9140
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, pnl::kWork);
    a1 = 0;
    a2 = 16;  // the pnl_anim record
    jal(ctx, 0x3A9154u, gen::fn_memset_00521408);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003A92A0 itfPnlAnimClear11 -- 48 bytes; frame 0x10: ra sp+0x0
// itfPnlAnimClear11(panel): memset(panel->work, 0, 16) -- the animation record closed and zeroed; returns 0 (panel type 11;
// itfPnlRegist2 installs it). One block of 12 around the call.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfPnlAnimClear11(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a92a0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, pnl::kWork);
    a1 = 0;
    a2 = 16;  // the pnl_anim record
    jal(ctx, 0x3A92B4u, gen::fn_memset_00521408);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003A94E0 itfPnlAnimClear13 -- 48 bytes; frame 0x10: ra sp+0x0
// itfPnlAnimClear13(panel): memset(panel->work, 0, 16) -- the animation record closed and zeroed; returns 0 (panel type 13;
// itfPnlRegist2 installs it). One block of 12 around the call.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfPnlAnimClear13(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a94e0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, pnl::kWork);
    a1 = 0;
    a2 = 16;  // the pnl_anim record
    jal(ctx, 0x3A94F4u, gen::fn_memset_00521408);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003A9170 itfPnlAnimOpenType10 -- 180 bytes; leaf frame (no stack)
// itfPnlAnimOpenType10(panel): one opening frame of panel type 10 (6 frames): phase = opening; ++frame; scale =
// 100 - 100 * frame / 6; alpha = 255 * frame / 6 from frame 2 (0 before). On frame 6 the panel is open (phase 2,
// frame 0, scale 0, alpha 255) and it returns 1, else 0. Blocks: entry 21; alpha (frame >= 2) 7 / 0 (frame < 2)
// 1; done test 4; done 9 / running 1; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfPnlAnimOpenType10(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::div, hg::enter, hg::lw, hg::mflo, hg::sll, hg::slti,
          hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003a9170
    enter(ctx, 21);  // entry check point + this block's cycles
    lw(a1, a0, pnl::kWork);  // a1 = the animation record
    v0 = pnl_anim::kOpening;
    sw(v0, a1, pnl_anim::kPhase);
    lw(v0, a1, pnl_anim::kFrame);
    v1 = addiu(v0, 1);
    sw(v1, a1, pnl_anim::kFrame);
    // scale = 100 - 100 * frame / 6 (100 * frame as ((frame * 5) * 5) * 4)
    v0 = sll(v1, 2);
    v1 = addu(v0, v1);
    v0 = sll(v1, 2);
    v0 = addu(v1, v0);
    v0 = sll(v0, 2);
    a0 = 6;
    div(v0, a0);
    mflo(v1);
    v0 = pnl_anim::kFullScale;
    v0 = subu(v0, v1);
    sw(v0, a1, pnl_anim::kScale);
    lw(v1, a1, pnl_anim::kFrame);
    at = slti(v1, 2);
    if (at != 0) {
        // 0x003a91e0: frame < 2: alpha 0
        charge(ctx, 1);
        sw(zero, a1, pnl_anim::kAlpha);
    } else {
        // 0x003a91c4: alpha = 255 * frame / 6
        charge(ctx, 7);
        v0 = sll(v1, 8);
        v0 = subu(v0, v1);
        div(v0, a0);
        mflo(v0);
        sw(v0, a1, pnl_anim::kAlpha);
    }
    // 0x003a91e4: done after 6 frames?
    charge(ctx, 4);
    lw(v0, a1, pnl_anim::kFrame);
    v0 = slti(v0, 6);
    if (v0 != 0) {
        // 0x003a9218: still opening: return 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003a91f4: open: phase 2, frame 0, scale 0, alpha 255; return 1
        charge(ctx, 9);
        v0 = pnl_anim::kOpen;
        sw(v0, a1, pnl_anim::kPhase);
        sw(zero, a1, pnl_anim::kFrame);
        sw(zero, a1, pnl_anim::kScale);
        v0 = pnl_anim::kOpaque;
        sw(v0, a1, pnl_anim::kAlpha);
        v0 = 1;
    }
    // 0x003a921c: return
    charge(ctx, 2);
}

// 0x003A9230 itfPnlAnimCloseFade10 -- 108 bytes; leaf frame (no stack)
// itfPnlAnimCloseFade10(panel): one closing frame of a 10-frame fade-out: phase = closing; ++frame; alpha = 255
// - 255 * frame / 10. After the last frame the record is cleared (phase closed, frame 0, alpha 0) and it returns
// 1, else 0. Blocks: entry 18; done 6 / running 1; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfPnlAnimCloseFade10(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::div, hg::enter, hg::lw, hg::mflo, hg::sll, hg::slti, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003a9230
    enter(ctx, 18);  // entry check point + this block's cycles
    lw(a0, a0, pnl::kWork);  // a0 = the animation record
    v0 = pnl_anim::kClosing;
    sw(v0, a0, pnl_anim::kPhase);
    lw(v0, a0, pnl_anim::kFrame);
    v1 = addiu(v0, 1);
    sw(v1, a0, pnl_anim::kFrame);
    // alpha = 255 - 255 * frame / 10 (255 * frame as (frame << 8) - frame)
    v0 = sll(v1, 8);
    v1 = subu(v0, v1);
    v0 = 10;
    div(v1, v0);
    mflo(v1);
    v0 = pnl_anim::kOpaque;
    v0 = subu(v0, v1);
    sw(v0, a0, pnl_anim::kAlpha);
    lw(v0, a0, pnl_anim::kFrame);
    v0 = slti(v0, 10);
    if (v0 != 0) {
        // 0x003a9290: still closing: return 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003a9278: closed: clear the record; return 1
        charge(ctx, 6);
        sw(zero, a0, pnl_anim::kPhase);
        sw(zero, a0, pnl_anim::kFrame);
        sw(zero, a0, pnl_anim::kAlpha);
        v0 = 1;
    }
    // 0x003a9294: return
    charge(ctx, 2);
}

// 0x003A9580 itfPnlAnimCloseFade13 -- 108 bytes; leaf frame (no stack)
// itfPnlAnimCloseFade13(panel) (panel type 13; the same body as itfPnlAnimCloseFade10): one closing frame of a 10-frame fade-out: phase = closing; ++frame; alpha = 255
// - 255 * frame / 10. After the last frame the record is cleared (phase closed, frame 0, alpha 0) and it returns
// 1, else 0. Blocks: entry 18; done 6 / running 1; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfPnlAnimCloseFade13(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::div, hg::enter, hg::lw, hg::mflo, hg::sll, hg::slti, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003a9580
    enter(ctx, 18);  // entry check point + this block's cycles
    lw(a0, a0, pnl::kWork);  // a0 = the animation record
    v0 = pnl_anim::kClosing;
    sw(v0, a0, pnl_anim::kPhase);
    lw(v0, a0, pnl_anim::kFrame);
    v1 = addiu(v0, 1);
    sw(v1, a0, pnl_anim::kFrame);
    // alpha = 255 - 255 * frame / 10 (255 * frame as (frame << 8) - frame)
    v0 = sll(v1, 8);
    v1 = subu(v0, v1);
    v0 = 10;
    div(v1, v0);
    mflo(v1);
    v0 = pnl_anim::kOpaque;
    v0 = subu(v0, v1);
    sw(v0, a0, pnl_anim::kAlpha);
    lw(v0, a0, pnl_anim::kFrame);
    v0 = slti(v0, 10);
    if (v0 != 0) {
        // 0x003a95e0: still closing: return 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003a95c8: closed: clear the record; return 1
        charge(ctx, 6);
        sw(zero, a0, pnl_anim::kPhase);
        sw(zero, a0, pnl_anim::kFrame);
        sw(zero, a0, pnl_anim::kAlpha);
        v0 = 1;
    }
    // 0x003a95e4: return
    charge(ctx, 2);
}

// 0x003A9470 itfPnlAnimCloseFade5 -- 108 bytes; leaf frame (no stack)
// itfPnlAnimCloseFade5(panel): one closing frame of a 5-frame fade-out: phase = closing; ++frame; alpha = 255
// - 255 * frame / 5. After the last frame the record is cleared (phase closed, frame 0, alpha 0) and it returns
// 1, else 0. Blocks: entry 18; done 6 / running 1; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfPnlAnimCloseFade5(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::div, hg::enter, hg::lw, hg::mflo, hg::sll, hg::slti, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003a9470
    enter(ctx, 18);  // entry check point + this block's cycles
    lw(a0, a0, pnl::kWork);  // a0 = the animation record
    v0 = pnl_anim::kClosing;
    sw(v0, a0, pnl_anim::kPhase);
    lw(v0, a0, pnl_anim::kFrame);
    v1 = addiu(v0, 1);
    sw(v1, a0, pnl_anim::kFrame);
    // alpha = 255 - 255 * frame / 5 (255 * frame as (frame << 8) - frame)
    v0 = sll(v1, 8);
    v1 = subu(v0, v1);
    v0 = 5;
    div(v1, v0);
    mflo(v1);
    v0 = pnl_anim::kOpaque;
    v0 = subu(v0, v1);
    sw(v0, a0, pnl_anim::kAlpha);
    lw(v0, a0, pnl_anim::kFrame);
    v0 = slti(v0, 5);
    if (v0 != 0) {
        // 0x003a94d0: still closing: return 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003a94b8: closed: clear the record; return 1
        charge(ctx, 6);
        sw(zero, a0, pnl_anim::kPhase);
        sw(zero, a0, pnl_anim::kFrame);
        sw(zero, a0, pnl_anim::kAlpha);
        v0 = 1;
    }
    // 0x003a94d4: return
    charge(ctx, 2);
}

// 0x003A9400 itfPnlAnimOpenFade15 -- 104 bytes; leaf frame (no stack)
// itfPnlAnimOpenFade15(panel): one opening frame of a 15-frame fade-in: phase = opening; ++frame; alpha = 255
// * frame / 15. After the last frame the panel is open (phase 2, frame 0, alpha 255) and it returns 1 (the $v0
// of the phase store, left as it is), else 0. Blocks: entry 16; done 7 / running 1; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfPnlAnimOpenFade15(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::div, hg::enter, hg::lw, hg::mflo, hg::sll, hg::slti, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003a9400
    enter(ctx, 16);  // entry check point + this block's cycles
    lw(a1, a0, pnl::kWork);  // a1 = the animation record
    v0 = pnl_anim::kOpening;
    sw(v0, a1, pnl_anim::kPhase);
    lw(v1, a1, pnl_anim::kFrame);
    a0 = addiu(v1, 1);
    sw(a0, a1, pnl_anim::kFrame);
    // alpha = 255 * frame / 15
    v1 = sll(a0, 8);
    a0 = subu(v1, a0);
    v1 = 15;
    div(a0, v1);
    mflo(v1);
    sw(v1, a1, pnl_anim::kAlpha);
    lw(v1, a1, pnl_anim::kFrame);
    v1 = slti(v1, 15);
    if (v1 != 0) {
        // 0x003a945c: still opening: return 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003a9440: open: phase 2, frame 0, alpha 255 ($v0 stays 1)
        charge(ctx, 7);
        v1 = pnl_anim::kOpen;
        sw(v1, a1, pnl_anim::kPhase);
        sw(zero, a1, pnl_anim::kFrame);
        v1 = pnl_anim::kOpaque;
        sw(v1, a1, pnl_anim::kAlpha);
    }
    // 0x003a9460: return
    charge(ctx, 2);
}

// 0x003A9510 itfPnlAnimOpenFade6 -- 104 bytes; leaf frame (no stack)
// itfPnlAnimOpenFade6(panel): one opening frame of a 6-frame fade-in: phase = opening; ++frame; alpha = 255
// * frame / 6. After the last frame the panel is open (phase 2, frame 0, alpha 255) and it returns 1 (the $v0
// of the phase store, left as it is), else 0. Blocks: entry 16; done 7 / running 1; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfPnlAnimOpenFade6(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::div, hg::enter, hg::lw, hg::mflo, hg::sll, hg::slti, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003a9510
    enter(ctx, 16);  // entry check point + this block's cycles
    lw(a1, a0, pnl::kWork);  // a1 = the animation record
    v0 = pnl_anim::kOpening;
    sw(v0, a1, pnl_anim::kPhase);
    lw(v1, a1, pnl_anim::kFrame);
    a0 = addiu(v1, 1);
    sw(a0, a1, pnl_anim::kFrame);
    // alpha = 255 * frame / 6
    v1 = sll(a0, 8);
    a0 = subu(v1, a0);
    v1 = 6;
    div(a0, v1);
    mflo(v1);
    sw(v1, a1, pnl_anim::kAlpha);
    lw(v1, a1, pnl_anim::kFrame);
    v1 = slti(v1, 6);
    if (v1 != 0) {
        // 0x003a956c: still opening: return 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003a9550: open: phase 2, frame 0, alpha 255 ($v0 stays 1)
        charge(ctx, 7);
        v1 = pnl_anim::kOpen;
        sw(v1, a1, pnl_anim::kPhase);
        sw(zero, a1, pnl_anim::kFrame);
        v1 = pnl_anim::kOpaque;
        sw(v1, a1, pnl_anim::kAlpha);
    }
    // 0x003a9570: return
    charge(ctx, 2);
}

// 0x003A92D0 itfPnlAnimOpenType11 -- 204 bytes; leaf frame (no stack)
// itfPnlAnimOpenType11(panel): one opening frame of panel type 11 (10 frames): phase = opening; ++frame; for
// frame < 4: scale = 100 - 100 * frame / 4 (the compiled /4 rounds toward zero: +3 when 100 * frame is
// negative) and alpha = 255 * frame / 10; from frame 4: scale 0, alpha 255. On frame 10 the panel is open (phase
// 2, frame 0, scale 0, alpha 255) and it returns 1, else 0. Blocks: entry 9; frame < 4: 9 (+2 when negative),
// then 12; frame >= 4: 3; done test 4; done 9 / running 1; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfPnlAnimOpenType11(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::div, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::lw,
          hg::mflo, hg::sll, hg::slti, hg::sra, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003a92d0
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(a0, a0, pnl::kWork);  // a0 = the animation record
    v0 = pnl_anim::kOpening;
    sw(v0, a0, pnl_anim::kPhase);
    lw(v0, a0, pnl_anim::kFrame);
    v1 = addiu(v0, 1);
    sw(v1, a0, pnl_anim::kFrame);
    at = slti(v1, 4);
    if (at == 0) {
        // 0x003a9350: frame >= 4: scale 0, alpha 255
        charge(ctx, 3);
        sw(zero, a0, pnl_anim::kScale);
        v0 = pnl_anim::kOpaque;
        sw(v0, a0, pnl_anim::kAlpha);
    } else {
        // 0x003a92f4: v1 = 100 * frame / 4 (100 * frame as ((frame * 5) * 5) * 4, then >> 2)
        charge(ctx, 9);
        v0 = sll(v1, 2);
        v1 = addu(v0, v1);
        v0 = sll(v1, 2);
        v1 = addu(v1, v0);
        v0 = sll(v1, 2);
        v1 = dsll32(v1, 2);
        v1 = dsra32(v1, 2);
        if (i64(v0) < 0) {
            // 0x003a9318: negative: round toward zero
            charge(ctx, 2);
            v0 = addiu(v0, 3);
            v1 = sra(v0, 2);
        }
        // 0x003a9320: scale = 100 - that; alpha = 255 * frame / 10
        charge(ctx, 12);
        v0 = pnl_anim::kFullScale;
        v0 = subu(v0, v1);
        sw(v0, a0, pnl_anim::kScale);
        lw(v1, a0, pnl_anim::kFrame);
        v0 = sll(v1, 8);
        v1 = subu(v0, v1);
        v0 = 10;
        div(v1, v0);
        mflo(v0);
        sw(v0, a0, pnl_anim::kAlpha);
    }
    // 0x003a935c: done after 10 frames?
    charge(ctx, 4);
    lw(v0, a0, pnl_anim::kFrame);
    v0 = slti(v0, 10);
    if (v0 != 0) {
        // 0x003a9390: still opening: return 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003a936c: open: phase 2, frame 0, scale 0, alpha 255; return 1
        charge(ctx, 9);
        v0 = pnl_anim::kOpen;
        sw(v0, a0, pnl_anim::kPhase);
        sw(zero, a0, pnl_anim::kFrame);
        sw(zero, a0, pnl_anim::kScale);
        v0 = pnl_anim::kOpaque;
        sw(v0, a0, pnl_anim::kAlpha);
        v0 = 1;
    }
    // 0x003a9394: return
    charge(ctx, 2);
}

// 0x003A93A0 itfPnlAnimCloseType11 -- 88 bytes; leaf frame (no stack)
// itfPnlAnimCloseType11(panel): the one closing frame of panel type 11: phase = closing; ++frame; alpha = 255 *
// (1 - frame); once frame > 0 (always, from a closed record) the record is cleared and the done path leaves $v0
// = 1 from the subtraction; returns 0 otherwise. Blocks: entry 14; done 5 / running 1; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void itfPnlAnimCloseType11(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::i64, hg::lw, hg::sll, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003a93a0
    enter(ctx, 14);  // entry check point + this block's cycles
    lw(a1, a0, pnl::kWork);  // a1 = the animation record
    v0 = pnl_anim::kClosing;
    sw(v0, a1, pnl_anim::kPhase);
    lw(v0, a1, pnl_anim::kFrame);
    v1 = addiu(v0, 1);
    sw(v1, a1, pnl_anim::kFrame);
    v0 = 1;
    a0 = subu(v0, v1);
    v1 = sll(a0, 8);
    v1 = subu(v1, a0);
    sw(v1, a1, pnl_anim::kAlpha);  // 255 * (1 - frame)
    lw(v1, a1, pnl_anim::kFrame);
    if (i64(v1) <= 0) {
        // 0x003a93ec: frame <= 0: return 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003a93d8: closed: clear the record ($v0 stays 1)
        charge(ctx, 5);
        sw(zero, a1, pnl_anim::kPhase);
        sw(zero, a1, pnl_anim::kFrame);
        sw(zero, a1, pnl_anim::kAlpha);
    }
    // 0x003a93f0: return
    charge(ctx, 2);
}

// 0x003A95F0 itfPnlRunPhase0 -- 56 bytes; frame 0x10: ra sp+0x0
// itfPnlRunPhase0(panel): calls the panel's phase-0 callback (+64; the callback gets the caller's $a0..$t3
// unchanged, the panel in $a0) and returns its $v0; 1 when the slot is null. Blocks: entry 5; callback 4 /
// none 1; epilogue 4.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfPnlRunPhase0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jalr, hg::ld, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a95f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, pnl::kPhase0);
    if (v0 == 0) {
        // 0x003a9614: no callback: return 1
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x003a9604: return callback(panel)
        charge(ctx, 4);
        jalr(ctx, 0x3A9604u, v0.u());
    }
    // 0x003a9618: epilogue
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003A9630 itfPnlRunPhase1 -- 56 bytes; frame 0x10: ra sp+0x0
// itfPnlRunPhase1(panel): calls the panel's phase-1 callback (+68; the callback gets the caller's $a0..$t3
// unchanged, the panel in $a0) and returns its $v0; 1 when the slot is null. Blocks: entry 5; callback 4 /
// none 1; epilogue 4.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfPnlRunPhase1(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jalr, hg::ld, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a9630
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, pnl::kPhase1);
    if (v0 == 0) {
        // 0x003a9654: no callback: return 1
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x003a9644: return callback(panel)
        charge(ctx, 4);
        jalr(ctx, 0x3A9644u, v0.u());
    }
    // 0x003a9658: epilogue
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003A9670 itfPnlRunPhase2 -- 56 bytes; frame 0x10: ra sp+0x0
// itfPnlRunPhase2(panel): calls the panel's phase-2 callback (+72; the callback gets the caller's $a0..$t3
// unchanged, the panel in $a0) and returns its $v0; 1 when the slot is null. Blocks: entry 5; callback 4 /
// none 1; epilogue 4.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfPnlRunPhase2(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jalr, hg::ld, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a9670
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, pnl::kPhase2);
    if (v0 == 0) {
        // 0x003a9694: no callback: return 1
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x003a9684: return callback(panel)
        charge(ctx, 4);
        jalr(ctx, 0x3A9684u, v0.u());
    }
    // 0x003a9698: epilogue
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003A96B0 itfPnlRunPhase3 -- 56 bytes; frame 0x10: ra sp+0x0
// itfPnlRunPhase3(panel): calls the panel's phase-3 callback (+76; the callback gets the caller's $a0..$t3
// unchanged, the panel in $a0) and returns its $v0; 1 when the slot is null. Blocks: entry 5; callback 4 /
// none 1; epilogue 4.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void itfPnlRunPhase3(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jalr, hg::ld, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a96b0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, pnl::kPhase3);
    if (v0 == 0) {
        // 0x003a96d4: no callback: return 1
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x003a96c4: return callback(panel)
        charge(ctx, 4);
        jalr(ctx, 0x3A96C4u, v0.u());
    }
    // 0x003a96d8: epilogue
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (signatures from recomp/generated/functions.h) ---------
namespace p3fes::recomp_gen {

using p3fes::EEContext;
namespace g = p3fes::game;
namespace gg = p3fes::game::guest;

// Returning functions: $v0 = the result (sign-extended as the original's load left it).

// Void functions that leave $v0 alone (or whose callee sets it): no write here.

// Void, (buf, a1, a2, a3, t0): the fifth argument is $t0 (EE ABI: eight argument registers).
#define P3FES_MSG2_PANEL_SHIM(name, addr)                                                                    \
    void fn_##name##_##addr(EEContext& c) {                                                                   \
        g::name(c, gg::arg32(c, 0), gg::arg32(c, 1), gg::arg32(c, 2), gg::arg32(c, 3), ee::core::gpr32(c, 8)); \
    }
#define P3FES_MSG2_PANEL_SHIM_S(name, addr)                                                                   \
    void fn_##name##_##addr(EEContext& c) {                                                                   \
        g::name(c, gg::arg32(c, 0), gg::args32(c, 1), gg::args32(c, 2), gg::args32(c, 3),                     \
                static_cast<s32>(ee::core::gpr32(c, 8)));                                                     \
    }
#undef P3FES_MSG2_PANEL_SHIM
#undef P3FES_MSG2_PANEL_SHIM_S

// itfMesMngPushMessageArgs leaves table + 124 in $v0 (its last element address; frFontSetTagSlot does not write $v0).

}  // namespace p3fes::recomp_gen
