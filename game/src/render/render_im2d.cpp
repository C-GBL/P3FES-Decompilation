// RenderWare's Im2D submission path (render_im2d.h has the data flow; docs/ANALYSIS/22_rendering.md
// sections 6 and 8.1).
//
// Cycle model (ADR-0013): every guest::charge below is one `ctx.cycles += N` block of the recompiled body
// in recomp/generated (fn_0048_*); guest::backedge sits where that body has its back-edge check point --
// including the two forward-looking ones the compiler's layout produces (the "program resident" retry of
// open2DVU1Pkt and the jump back into the zero-count test of the builders).
//
// Registers: the kernel saves the whole register file in guest memory when a check point preempts the
// thread (render_im2d.h, Frame), so these functions are register-faithful: at every check point, at every
// call and at the return each register holds what the original holds there, including the scratch registers
// of its loops, and the prologues write the original spills. The data flow is written once (build_packets:
// packets, batches, RwIm2DVertex copies); what differs between the ten builder bodies -- which register the
// compiler gave each value -- is data (`Alloc`, one per builder) plus two small per-builder functions for the
// batch header and the per-primitive copy, whose final register values are listed from the instructions.
// tests/game/test_render_im2d.cpp compares the register file at every check point and the dead stack.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 12 of the 18 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: faults only 12); each keeps the notes of its
// earlier hand version above it. The others are the hand-written versions this header describes.
#include "p3fes/game/render_im2d.h"

#include "p3fes/ee/hilo.h"
#include <cstring>
#include "p3fes/game/hg_cpu.h"

// Callees of the register-faithful bodies (p3fes_handgen), through their recomp_gen entry points.
namespace p3fes::recomp_gen {
void fn_closeAndDispatchVU1Packet_004ec4c0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::recomp_gen {
void fn__rwDMAOpenVIFPkt_004d59d0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace im2d;
namespace core = ee::core;

namespace {

u64 sx(u32 v) { return core::sext32(v); }

// Register writes: lo() is a 64-bit result (bits 64..127 unchanged), q() a 128-bit one (LQ, PCPYLD).
struct Regs {
    EEContext& c;
    u64 get(unsigned r) const { return core::gpr64(c, r); }
    void lo(unsigned r, u64 v) { core::set_gpr64(c, r, v); }
    void q(unsigned r, const u128& v) { core::set_gpr128(c, r, v); }
    void q(unsigned r, u64 lo_, u64 hi_) { core::set_gpr128(c, r, make_q(lo_, hi_)); }
};

u32 vertex_at(u32 verts, u32 index) { return verts + (index << 6); }

}  // namespace

// ======================================================================================================
// [closeAndDispatchVU1Packet] 0x4EC4C0
void closeAndDispatchVU1Packet(EEContext& ctx) {
    guest::enter(ctx, 18);
    const u32 p = guest::load<u32>(ctx, kSprWritePtr);
    const u128 cnt_a = load_q(ctx, kTplCnt1A);
    store_q(ctx, p + 0, cnt_a);
    const u128 flush = make_q(0x11000000u, 0);
    store_q(ctx, p + 16, flush);
    const u128 cnt_b = load_q(ctx, kTplCnt1B);
    store_q(ctx, p + 32, cnt_b);
    const u128 tail = load_q(ctx, kTplFlush);
    store_q(ctx, p + 48, tail);
    guest::store<u32>(ctx, kSprWritePtr, p + 64);
    Regs r{ctx};
    r.q(GPR_V1, sx(p + 64), tail.u64[1]);
    r.lo(GPR_A2, sx(p));
    r.q(GPR_A1, cnt_a);
    r.q(GPR_A0, cnt_b);
    r.q(GPR_A3, flush);
}

// ======================================================================================================
// [open2DVU1Pkt] 0x4EC100
u32 open2DVU1Pkt(EEContext& ctx, u32 batch_qw, u32 prim_qw, u32 prim_count, u32 gs_prim, u64 program) {
    guest::enter(ctx, 15);
    Frame frame(ctx, 48, {{GPR_RA, 32, false}, {GPR_S1, 16, true}, {GPR_S0, 0, true}});
    Regs r{ctx};
    r.lo(GPR_S1, r.get(GPR_A3));
    r.lo(GPR_S0, r.get(GPR_T0));
    // Quadwords to reserve (MULT and MULT1: both HI/LO pairs keep the products).
    ee::mult(ctx, ee::kPipe0, batch_qw, (prim_count + 15u) >> 4);
    const u32 head = static_cast<u32>(ee::mflo(ctx)) + 22u;
    ee::mult1(ctx, prim_qw, prim_count);
    u32 qwc = head + static_cast<u32>(ee::mflo1(ctx));
    const u32 resident = guest::load<u32>(ctx, kResidentProgram);
    r.lo(GPR_V0, sx(resident));
    r.lo(GPR_V1, sx(head));
    r.lo(GPR_A1, sx(qwc));
    if (sx(resident) == program) {  // no `call` tag needed
        guest::charge(ctx, 2);
        qwc -= 1;
        r.lo(GPR_A1, sx(qwc));
        guest::backedge(ctx);
    }
    guest::charge(ctx, 43);
    r.lo(GPR_A0, 0);
    frame.link(0x4EC13Cu);
    recomp_gen::fn__rwDMAOpenVIFPkt_004d59d0(ctx);  // _rwDMAOpenVIFPkt(0, qwc): DMAC registers, stays recompiled

    // The packet head at the (possibly moved) scratchpad write pointer.
    const u32 p = guest::load<u32>(ctx, kSprWritePtr);
    const u128 cnt_first = load_q(ctx, kTplCnt1A);
    store_q(ctx, p + 0, cnt_first);
    const u128 stcycl_flush = make_q(0x01000404u, 0x11000000u);  // STCYCL 4,4 ; FLUSH
    store_q(ctx, p + 16, stcycl_flush);
    const u128 unpack3 = load_q(ctx, kTplUnpack3);
    store_q(ctx, p + 32, unpack3);
    const u128 unpack3_data = load_q(ctx, kTplUnpack3Data);
    store_q(ctx, p + 48, unpack3_data);
    // GS PRIM = (render flags | gs_prim) & 0x7FF into bits 15..25 of the GIF tag's second word.
    const u64 flags = guest::load<u64>(ctx, kRenderFlags);
    const u32 tag_word = guest::load<u32>(ctx, kTplGifTag + 4);
    const u32 prim = (static_cast<u32>(flags) | gs_prim) & 0x7FFu;
    guest::store<u32>(ctx, kSprWritePtr, p + 64);
    guest::store<u32>(ctx, kTplGifTag + 4, (tag_word & 0xFC007FFFu) | (prim << 15));
    store_q(ctx, p + 64, load_q(ctx, kTplGifTag));
    const bool tme = (guest::load<u64>(ctx, kRenderFlags) & 0x10u) != 0;
    guest::charge(ctx, tme ? 7 : 6);
    store_q(ctx, p + 80, load_q(ctx, tme ? kTplHeadTex : kTplHeadNoTex));
    guest::store<u32>(ctx, kSprWritePtr, p + 96);
    guest::charge(ctx, 13);
    const u128 cnt_second = load_q(ctx, kTplCnt1A);
    store_q(ctx, p + 96, cnt_second);
    const u128 base_offset = load_q(ctx, kTplBaseOffset);
    store_q(ctx, p + 112, base_offset);
    guest::store<u32>(ctx, kSprWritePtr, p + 128);
    const bool call = sx(guest::load<u32>(ctx, kResidentProgram)) != program;
    if (call) {  // DMA `call` of the program image (the VIF uploads it with its MPG codes), now resident
        guest::charge(ctx, 12);
        store_q(ctx, p + 128, make_q((static_cast<u64>(static_cast<u32>(program)) << 32) | 0x50000000u, 0));
        guest::store<u32>(ctx, kResidentProgram, static_cast<u32>(program));
        guest::store<u32>(ctx, kSprWritePtr, p + 144);
    }
    guest::charge(ctx, 2);
    guest::charge(ctx, 5);

    // The registers as the original leaves them (bits 64..127 from the last LQ into each register).
    r.q(GPR_V0, 1, call ? 0 : base_offset.u64[1]);
    r.q(GPR_V1, call ? static_cast<u64>(static_cast<u32>(program)) << 32 : sx(p + 96), cnt_second.u64[1]);
    r.q(GPR_A0, sx(p + 128), unpack3.u64[1]);
    r.lo(GPR_A1, call ? 0 : gs_prim);
    r.lo(GPR_A2, 0xFFFFFFFFFC007FFFull);
    r.lo(GPR_A3, kTplGifTag + 4);
    r.q(GPR_T0, sx(p + 64), cnt_first.u64[1]);
    r.lo(GPR_T1, sx(p));
    r.q(GPR_T2, stcycl_flush);
    return 1;
}

// ======================================================================================================
// [addCopyVU1Line] 0x4EC8A0 / [addCopyVU1Triangle] 0x4ECAC0: one primitive in one batch. The vertices sit in
// s1, s0 (line) / s3, s2, s1 (triangle), the count (1, or 0 for a zero packet limit) in s2 / s0.
// 0x004EC8A0 addCopyVU1Line -- 436 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void addCopyVU1Line(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::call, hg::charge, hg::dsll32, hg::enter, hg::jalr, hg::ld, hg::link,
          hg::lq, hg::lui, hg::lw, hg::pcpyld, hg::sd, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ec8a0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = a0;
    sd(ra, sp, 0x30);
    t1 = a1;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = 1;
    sq(s0, sp, 0x0);
    s1 = a2;
    lw(v0, gp, -16872);  // 0x7CEB08
    s0 = a3;
    if (v0 == 0) {
        // 0x004ec8d0
        charge(ctx, 1);
        s2 = v0;
    }
    // 0x004ec8d4
    charge(ctx, 10);
    lw(t0, v1, 4);
    a0 = 3;
    lw(v0, v1, 0);
    a1 = 8;
    a2 = s2;
    a3 = 1;
    jalr(ctx, 0x4EC8E8u, v0.u());
    if (v0 == 0) s2 = 0;
    if (s2 != 0) {
        // 0x004ec904
        charge(ctx, 78);
        a0 = 0x1000000;
        v1 = 0x4000000;
        a1 = a0 | 0x404;  // &0x1000404
        lw(a3, gp, -17148);  // 0x7CE9F4
        a0 = v1 | 0x1;
        a1 = dsll32(a1, 0);
        v1 = 0x10000000;
        a0 = a0 | a1;
        v1 = v1 | 0xA;
        pcpyld(t0, a0, v1);
        a0 = 0x7C080000;
        v1 = lui(0xC000);
        a0 = a0 | 0x8000;
        v1 = v1 | 0xC000;
        a2 = dsll32(a0, 0);
        a1 = dsll32(v1, 0);
        a0 = 0x20000000;
        sq(t0, a3, 0);
        a0 = a0 | a1;
        v1 = 0x960000;
        pcpyld(a0, zero, a0);
        pcpyld(a0, a2, a0);
        sq(a0, a3, 16);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 32);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s1, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s1, 16);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s1, 32);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s1, 48);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s0, 16);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s0, 32);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a1, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a1, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a0, s0, 48);
        sq(a0, a1, 16);
        lq(v1, v1, 22752);  // 0x9658E0
        sq(v1, a1, 32);
        lw(v1, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v1, 32);
        link(ctx, 0x4ECA2Cu);  // $ra first: the delay slot below depends on it
        sw(v1, gp, -17148);  // 0x7CE9F4
        call(ctx, gen::fn_closeAndDispatchVU1Packet_004ec4c0);
        backedge(ctx);
    }
    // 0x004ec8fc
    charge(ctx, 2);
    ld(ra, sp, 0x30);
    // 0x004eca40
    charge(ctx, 5);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void addCopyVU1Line(EEContext& ctx, u32 desc, u64 open_arg, u32 va, u32 vb) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(desc)));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(open_arg));
    ee::core::set_gpr64(ctx, GPR_A2, ee::core::sext32(static_cast<u32>(va)));
    ee::core::set_gpr64(ctx, GPR_A3, ee::core::sext32(static_cast<u32>(vb)));
    addCopyVU1Line(ctx);
}

// 0x004ECAC0 addCopyVU1Triangle -- 544 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void addCopyVU1Triangle(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::call, hg::charge, hg::dsll32, hg::enter, hg::jalr, hg::ld, hg::link,
          hg::lq, hg::lui, hg::lw, hg::pcpyld, hg::sd, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ecac0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v1 = a0;
    sd(ra, sp, 0x40);
    t1 = a1;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    s2 = a3;
    sq(s0, sp, 0x0);
    s1 = t0;
    lw(v0, gp, -16868);  // 0x7CEB0C
    s0 = 1;
    if (v0 == 0) {
        // 0x004ecaf8
        charge(ctx, 1);
        s0 = v0;
    }
    // 0x004ecafc
    charge(ctx, 10);
    lw(t0, v1, 8);
    a0 = 3;
    lw(v0, v1, 0);
    a1 = 12;
    a2 = s0;
    a3 = 5;
    jalr(ctx, 0x4ECB10u, v0.u());
    if (v0 == 0) s0 = 0;
    if (s0 != 0) {
        // 0x004ecb2c
        charge(ctx, 102);
        a0 = 0x1000000;
        v1 = 0x4000000;
        a1 = a0 | 0x404;  // &0x1000404
        lw(a3, gp, -17148);  // 0x7CE9F4
        a0 = v1 | 0x1;
        a1 = dsll32(a1, 0);
        v1 = 0x10000000;
        a0 = a0 | a1;
        v1 = v1 | 0xE;
        pcpyld(t0, a0, v1);
        a0 = 0x7C0C0000;
        v1 = lui(0xC000);
        a0 = a0 | 0x8000;
        v1 = v1 | 0xC000;
        a2 = dsll32(a0, 0);
        a1 = dsll32(v1, 0);
        a0 = 0x20000000;
        sq(t0, a3, 0);
        a0 = a0 | a1;
        v1 = 0x960000;
        pcpyld(a0, zero, a0);
        pcpyld(a0, a2, a0);
        sq(a0, a3, 16);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 32);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s3, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s3, 16);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s3, 32);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s3, 48);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s2, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s2, 16);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s2, 32);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s2, 48);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s1, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s1, 16);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a0, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a1, s1, 32);
        lw(a0, gp, -17148);  // 0x7CE9F4
        sq(a1, a0, 0);
        lw(a1, gp, -17148);  // 0x7CE9F4
        a0 = addiu(a1, 16);
        sw(a0, gp, -17148);  // 0x7CE9F4
        lq(a0, s1, 48);
        sq(a0, a1, 16);
        lq(v1, v1, 22752);  // 0x9658E0
        sq(v1, a1, 32);
        lw(v1, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v1, 32);
        link(ctx, 0x4ECCB4u);  // $ra first: the delay slot below depends on it
        sw(v1, gp, -17148);  // 0x7CE9F4
        call(ctx, gen::fn_closeAndDispatchVU1Packet_004ec4c0);
        backedge(ctx);
    }
    // 0x004ecb24
    charge(ctx, 2);
    ld(ra, sp, 0x40);
    // 0x004eccc8
    charge(ctx, 6);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void addCopyVU1Triangle(EEContext& ctx, u32 desc, u64 open_arg, u32 va, u32 vb, u32 vc) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(desc)));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(open_arg));
    ee::core::set_gpr64(ctx, GPR_A2, ee::core::sext32(static_cast<u32>(va)));
    ee::core::set_gpr64(ctx, GPR_A3, ee::core::sext32(static_cast<u32>(vb)));
    ee::core::set_gpr64(ctx, GPR_T0, ee::core::sext32(static_cast<u32>(vc)));
    addCopyVU1Triangle(ctx);
}

// ======================================================================================================
// The prim-array builders (prim table 0x77F1B0). Each prologue copies its arguments into s-registers
// (descriptor, open_arg, array pointer) and computes the primitive count; the walk advances the pointer.

// 0x004ECD40 addCopyVU1PrimLineList -- 652 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void addCopyVU1PrimLineList(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::daddiu, hg::dsll32, hg::dsra32, hg::dsrl32, hg::enter,
          hg::jal, hg::jalr, hg::ld, hg::lq, hg::lui, hg::lw, hg::pcpyld, hg::sd, hg::sll, hg::sltiu, hg::sltu,
          hg::sq, hg::srl, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ecd40
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v1 = lui(0xC000);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a1;
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    a0 = v1 | 0xC000;
    sq(s1, sp, 0x10);
    v1 = 0x20000000;
    a0 = dsll32(a0, 0);
    sq(s0, sp, 0x0);
    v1 = v1 | a0;
    s3 = a2;
    s2 = srl(a3, 1);
    pcpyld(s0, zero, v1);
    v1 = sltu(0, s2);
    for (;;) {
        // 0x004ecd8c
        charge(ctx, 3);
        v1 = v1 ^ 0x1;
        s1 = s2;
        if (v1 == 0) {
            // 0x004ecd98
            charge(ctx, 4);
            lw(v0, gp, -16872);  // 0x7CEB08
            at = sltu(v0, s2);
            if (at != 0) {
                // 0x004ecda8
                charge(ctx, 2);
                s1 = v0;
            }
            // 0x004ecdb0
            charge(ctx, 10);
            lw(t0, s4, 4);
            lw(v0, s4, 0);
            a0 = 3;
            a1 = 8;
            a2 = s1;
            a3 = 1;
            t1 = s5;
            jalr(ctx, 0x4ECDC8u, v0.u());
            if (v0 == 0) {
                goto L_004ecfa0;
            }
            goto L_004ecdd8;
        }
    L_004ecfa0:
        charge(ctx, 2);
        s1 = 0;
        backedge(ctx);
    L_004ecdd8:
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        // 0x004ecde0
        charge(ctx, 4);
        v1 = 0x960000;
        lq(t0, v1, 22752);  // 0x9658E0
        s2 = subu(s2, s1);
        if (s1 != 0) {
            // 0x004ecdf0
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x004ecdf8
                charge(ctx, 10);
                v1 = 0x1000000;
                a2 = 16;
                a0 = v1 | 0x404;  // &0x1000404
                t1 = 0x960000;
                a1 = dsll32(a0, 0);
                v1 = 0x4000000;
                a1 = v1 | a1;
                a0 = 0x10000000;
                v1 = 0x7C000000;
                v1 = v1 | 0x8000;
                for (;;) {
                    // 0x004ece20
                    charge(ctx, 3);
                    at = sltiu(s1, 17);
                    a3 = s1;
                    if (at == 0) {
                        // 0x004ece2c
                        charge(ctx, 1);
                        a3 = a2;
                    }
                    // 0x004ece30
                    charge(ctx, 25);
                    t2 = sll(a3, 3);
                    t3 = dsll32(a3, 0);
                    t2 = dsll32(t2, 0);
                    t3 = dsrl32(t3, 0);
                    t2 = dsrl32(t2, 0);
                    t5 = t3 | a1;
                    t2 = daddiu(t2, 2);
                    t3 = t2 | a0;
                    lw(t4, gp, -17148);  // 0x7CE9F4
                    t2 = sll(a3, 19);
                    s1 = subu(s1, a3);
                    t2 = dsll32(t2, 0);
                    t2 = dsrl32(t2, 0);
                    t2 = t2 | v1;
                    pcpyld(t5, t5, t3);
                    t2 = dsll32(t2, 0);
                    sq(t5, t4, 0);
                    pcpyld(t2, t2, s0);
                    sq(t2, t4, 16);
                    t3 = a3;
                    lw(t2, gp, -17148);  // 0x7CE9F4
                    a3 = addiu(a3, -1);
                    t2 = addiu(t2, 32);
                    sw(t2, gp, -17148);  // 0x7CE9F4
                    if (t3 != 0) {
                        // 0x004ece94
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004ece98
                            charge(ctx, 53);
                            lq(t4, s3, 0);
                            t2 = dsll32(t2, 0);
                            t3 = a3;
                            t2 = dsra32(t2, 0);
                            a3 = addiu(a3, -1);
                            sq(t4, t2, 0);
                            lw(t2, gp, -17148);  // 0x7CE9F4
                            t2 = addiu(t2, 16);
                            sw(t2, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 16);
                            lw(t2, gp, -17148);  // 0x7CE9F4
                            sq(t4, t2, 0);
                            lw(t2, gp, -17148);  // 0x7CE9F4
                            t2 = addiu(t2, 16);
                            sw(t2, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 32);
                            lw(t2, gp, -17148);  // 0x7CE9F4
                            sq(t4, t2, 0);
                            lw(t2, gp, -17148);  // 0x7CE9F4
                            t2 = addiu(t2, 16);
                            sw(t2, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 48);
                            lw(t2, gp, -17148);  // 0x7CE9F4
                            sq(t4, t2, 0);
                            lw(t2, gp, -17148);  // 0x7CE9F4
                            t2 = addiu(t2, 16);
                            sw(t2, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 64);
                            lw(t2, gp, -17148);  // 0x7CE9F4
                            sq(t4, t2, 0);
                            lw(t2, gp, -17148);  // 0x7CE9F4
                            t2 = addiu(t2, 16);
                            sw(t2, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 80);
                            lw(t2, gp, -17148);  // 0x7CE9F4
                            sq(t4, t2, 0);
                            lw(t2, gp, -17148);  // 0x7CE9F4
                            t2 = addiu(t2, 16);
                            sw(t2, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 96);
                            lw(t2, gp, -17148);  // 0x7CE9F4
                            sq(t4, t2, 0);
                            lw(t2, gp, -17148);  // 0x7CE9F4
                            t2 = addiu(t2, 16);
                            sw(t2, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 112);
                            lw(t2, gp, -17148);  // 0x7CE9F4
                            s3 = addiu(s3, 128);
                            sq(t4, t2, 0);
                            lw(t2, gp, -17148);  // 0x7CE9F4
                            t2 = addiu(t2, 16);
                            sw(t2, gp, -17148);  // 0x7CE9F4
                            if (t3 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004ecf6c
                        charge(ctx, 1);
                    }
                    // 0x004ecf70
                    charge(ctx, 8);
                    a3 = dsll32(t2, 0);
                    a3 = dsra32(a3, 0);
                    sq(t0, a3, 0);
                    lw(a3, gp, -17148);  // 0x7CE9F4
                    lq(t0, t1, 22608);
                    t2 = addiu(a3, 16);
                    sw(t2, gp, -17148);  // 0x7CE9F4
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x004ecf90
        charge(ctx, 4);
        jal(ctx, 0x4ECF90u, gen::fn_closeAndDispatchVU1Packet_004ec4c0);
        v1 = sltu(0, s2);
        backedge(ctx);
    }
    // 0x004ecfa8
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x004ECFD0 addCopyVU1PrimPolyLine -- 652 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void addCopyVU1PrimPolyLine(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::daddiu, hg::dsll32, hg::dsra32, hg::dsrl32, hg::enter,
          hg::jal, hg::jalr, hg::ld, hg::lq, hg::lui, hg::lw, hg::pcpyld, hg::sd, hg::sll, hg::sltiu, hg::sltu,
          hg::sq, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ecfd0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v1 = lui(0xC000);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a1;
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    a0 = v1 | 0xC000;
    sq(s1, sp, 0x10);
    v1 = 0x20000000;
    a0 = dsll32(a0, 0);
    sq(s0, sp, 0x0);
    v1 = v1 | a0;
    s3 = a2;
    s2 = addiu(a3, -1);
    pcpyld(s0, zero, v1);
    v1 = sltu(0, s2);
    for (;;) {
        // 0x004ed01c
        charge(ctx, 3);
        v1 = v1 ^ 0x1;
        s1 = s2;
        if (v1 == 0) {
            // 0x004ed028
            charge(ctx, 4);
            lw(v0, gp, -16872);  // 0x7CEB08
            at = sltu(v0, s2);
            if (at != 0) {
                // 0x004ed038
                charge(ctx, 2);
                s1 = v0;
            }
            // 0x004ed040
            charge(ctx, 10);
            lw(t0, s4, 4);
            lw(v0, s4, 0);
            a0 = 3;
            a1 = 8;
            a2 = s1;
            a3 = 1;
            t1 = s5;
            jalr(ctx, 0x4ED058u, v0.u());
            if (v0 == 0) {
                goto L_004ed230;
            }
            goto L_004ed068;
        }
    L_004ed230:
        charge(ctx, 2);
        s1 = 0;
        backedge(ctx);
    L_004ed068:
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        // 0x004ed070
        charge(ctx, 4);
        v1 = 0x960000;
        lq(t1, v1, 22752);  // 0x9658E0
        s2 = subu(s2, s1);
        if (s1 != 0) {
            // 0x004ed080
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x004ed088
                charge(ctx, 10);
                v1 = 0x1000000;
                a3 = 16;
                a0 = v1 | 0x404;  // &0x1000404
                a1 = 0x10000000;
                v1 = 0x4000000;
                a0 = dsll32(a0, 0);
                a2 = v1 | a0;
                t2 = 0x960000;
                v1 = 0x7C000000;
                a0 = v1 | 0x8000;
                for (;;) {
                    // 0x004ed0b0
                    charge(ctx, 3);
                    at = sltiu(s1, 17);
                    t0 = s1;
                    if (at == 0) {
                        // 0x004ed0bc
                        charge(ctx, 1);
                        t0 = a3;
                    }
                    // 0x004ed0c0
                    charge(ctx, 25);
                    v1 = sll(t0, 3);
                    t3 = dsll32(t0, 0);
                    v1 = dsll32(v1, 0);
                    t3 = dsrl32(t3, 0);
                    v1 = dsrl32(v1, 0);
                    t5 = t3 | a2;
                    v1 = daddiu(v1, 2);
                    t3 = v1 | a1;
                    lw(t4, gp, -17148);  // 0x7CE9F4
                    pcpyld(t5, t5, t3);
                    v1 = sll(t0, 19);
                    s1 = subu(s1, t0);
                    t3 = dsll32(v1, 0);
                    t3 = dsrl32(t3, 0);
                    v1 = t0;
                    t3 = t3 | a0;
                    t0 = addiu(t0, -1);
                    t3 = dsll32(t3, 0);
                    sq(t5, t4, 0);
                    pcpyld(t3, t3, s0);
                    sq(t3, t4, 16);
                    lw(t3, gp, -17148);  // 0x7CE9F4
                    t3 = addiu(t3, 32);
                    sw(t3, gp, -17148);  // 0x7CE9F4
                    if (v1 != 0) {
                        // 0x004ed124
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004ed128
                            charge(ctx, 54);
                            lq(t5, s3, 0);
                            t3 = dsll32(t3, 0);
                            t4 = t0;
                            t3 = dsra32(t3, 0);
                            v1 = addiu(s3, 64);
                            t0 = addiu(t0, -1);
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s3, 16);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s3, 32);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s3, 48);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s3, 64);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s3, 80);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s3, 96);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s3, 112);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            s3 = v1;
                            sq(t5, t3, 0);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(v1, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            if (t4 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                    // 0x004ed200
                    charge(ctx, 8);
                    v1 = dsll32(t3, 0);
                    v1 = dsra32(v1, 0);
                    sq(t1, v1, 0);
                    lw(v1, gp, -17148);  // 0x7CE9F4
                    lq(t1, t2, 22608);
                    t3 = addiu(v1, 16);
                    sw(t3, gp, -17148);  // 0x7CE9F4
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x004ed220
        charge(ctx, 4);
        jal(ctx, 0x4ED220u, gen::fn_closeAndDispatchVU1Packet_004ec4c0);
        v1 = sltu(0, s2);
        backedge(ctx);
    }
    // 0x004ed238
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x004ED260 addCopyVU1PrimTriList -- 784 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void addCopyVU1PrimTriList(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::daddiu, hg::dsll32, hg::dsra32, hg::dsrl32,
          hg::enter, hg::jal, hg::jalr, hg::ld, hg::lq, hg::lui, hg::lw, hg::mfhi, hg::multu, hg::pcpyld, hg::sd,
          hg::sll, hg::sltiu, hg::sltu, hg::sq, hg::srl, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ed260
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v1 = lui(0xAAAA);
    sd(ra, sp, 0x60);
    v1 = v1 | 0xAAAB;
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a1;
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    multu(zero, v1, a3);
    mfhi(a1);
    v1 = lui(0xC000);
    a0 = v1 | 0xC000;
    v1 = 0x20000000;
    a0 = dsll32(a0, 0);
    v1 = v1 | a0;
    s2 = srl(a1, 1);
    pcpyld(s0, zero, v1);
    v1 = sltu(0, s2);
    for (;;) {
        // 0x004ed2bc
        charge(ctx, 3);
        v1 = v1 ^ 0x1;
        s1 = s2;
        if (v1 == 0) {
            // 0x004ed2c8
            charge(ctx, 4);
            lw(v0, gp, -16868);  // 0x7CEB0C
            at = sltu(v0, s2);
            if (at != 0) {
                // 0x004ed2d8
                charge(ctx, 2);
                s1 = v0;
            }
            // 0x004ed2e0
            charge(ctx, 10);
            lw(t0, s4, 8);
            lw(v0, s4, 0);
            a0 = 3;
            a1 = 12;
            a2 = s1;
            a3 = 5;
            t1 = s5;
            jalr(ctx, 0x4ED2F8u, v0.u());
            if (v0 == 0) {
                goto L_004ed538;
            }
            goto L_004ed308;
        }
    L_004ed538:
        charge(ctx, 2);
        s1 = 0;
        backedge(ctx);
    L_004ed308:
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        // 0x004ed310
        charge(ctx, 4);
        v1 = 0x960000;
        lq(t1, v1, 22752);  // 0x9658E0
        s2 = subu(s2, s1);
        if (s1 != 0) {
            // 0x004ed320
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x004ed328
                charge(ctx, 10);
                v1 = 0x1000000;
                a3 = 16;
                a0 = v1 | 0x404;  // &0x1000404
                t2 = 0x960000;
                a1 = dsll32(a0, 0);
                v1 = 0x4000000;
                a2 = v1 | a1;
                a0 = 0x10000000;
                v1 = 0x7C000000;
                v1 = v1 | 0x8000;
                for (;;) {
                    // 0x004ed350
                    charge(ctx, 3);
                    at = sltiu(s1, 17);
                    t0 = s1;
                    if (at == 0) {
                        // 0x004ed35c
                        charge(ctx, 1);
                        t0 = a3;
                    }
                    // 0x004ed360
                    charge(ctx, 27);
                    t3 = sll(t0, 1);
                    t3 = addu(t3, t0);
                    a1 = dsll32(t0, 0);
                    t4 = sll(t3, 2);
                    a1 = dsrl32(a1, 0);
                    t4 = dsll32(t4, 0);
                    t3 = sll(t3, 18);
                    t4 = dsrl32(t4, 0);
                    t3 = dsll32(t3, 0);
                    t4 = daddiu(t4, 2);
                    t3 = dsrl32(t3, 0);
                    a1 = a1 | a2;
                    t4 = t4 | a0;
                    pcpyld(t5, a1, t4);
                    lw(a1, gp, -17148);  // 0x7CE9F4
                    t3 = t3 | v1;
                    t3 = dsll32(t3, 0);
                    s1 = subu(s1, t0);
                    pcpyld(t4, t3, s0);
                    t3 = t0;
                    t0 = addiu(t0, -1);
                    sq(t5, a1, 0);
                    sq(t4, a1, 16);
                    lw(a1, gp, -17148);  // 0x7CE9F4
                    a1 = addiu(a1, 32);
                    sw(a1, gp, -17148);  // 0x7CE9F4
                    if (t3 != 0) {
                        // 0x004ed3cc
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004ed3d0
                            charge(ctx, 77);
                            lq(t4, s3, 0);
                            a1 = dsll32(a1, 0);
                            t3 = t0;
                            a1 = dsra32(a1, 0);
                            t0 = addiu(t0, -1);
                            sq(t4, a1, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            a1 = addiu(a1, 16);
                            sw(a1, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 16);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            sq(t4, a1, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            a1 = addiu(a1, 16);
                            sw(a1, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 32);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            sq(t4, a1, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            a1 = addiu(a1, 16);
                            sw(a1, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 48);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            sq(t4, a1, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            a1 = addiu(a1, 16);
                            sw(a1, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 64);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            sq(t4, a1, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            a1 = addiu(a1, 16);
                            sw(a1, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 80);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            sq(t4, a1, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            a1 = addiu(a1, 16);
                            sw(a1, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 96);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            sq(t4, a1, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            a1 = addiu(a1, 16);
                            sw(a1, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 112);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            sq(t4, a1, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            a1 = addiu(a1, 16);
                            sw(a1, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 128);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            sq(t4, a1, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            a1 = addiu(a1, 16);
                            sw(a1, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 144);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            sq(t4, a1, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            a1 = addiu(a1, 16);
                            sw(a1, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 160);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            sq(t4, a1, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            a1 = addiu(a1, 16);
                            sw(a1, gp, -17148);  // 0x7CE9F4
                            lq(t4, s3, 176);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            s3 = addiu(s3, 192);
                            sq(t4, a1, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            a1 = addiu(a1, 16);
                            sw(a1, gp, -17148);  // 0x7CE9F4
                            if (t3 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004ed504
                        charge(ctx, 1);
                    }
                    // 0x004ed508
                    charge(ctx, 8);
                    a1 = dsll32(a1, 0);
                    a1 = dsra32(a1, 0);
                    sq(t1, a1, 0);
                    lw(a1, gp, -17148);  // 0x7CE9F4
                    lq(t1, t2, 22608);
                    a1 = addiu(a1, 16);
                    sw(a1, gp, -17148);  // 0x7CE9F4
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x004ed528
        charge(ctx, 4);
        jal(ctx, 0x4ED528u, gen::fn_closeAndDispatchVU1Packet_004ec4c0);
        v1 = sltu(0, s2);
        backedge(ctx);
    }
    // 0x004ed540
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x004ED570 addCopyVU1PrimTriStrip -- 800 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void addCopyVU1PrimTriStrip(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::daddiu, hg::dsll32, hg::dsra32, hg::dsrl32,
          hg::enter, hg::jal, hg::jalr, hg::ld, hg::lq, hg::lui, hg::lw, hg::pcpyld, hg::sd, hg::sll, hg::sltiu,
          hg::sltu, hg::sq, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ed570
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    at = sltiu(a3, 3);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a1;
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a2;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (at != 0) {
        // 0x004ed5b0
        charge(ctx, 1);
        s3 = 0;
    } else {
        // 0x004ed5a8
        charge(ctx, 2);
        s3 = addiu(a3, -2);
    }
    // 0x004ed5b4
    charge(ctx, 8);
    v1 = lui(0xC000);
    s2 = 1;
    a0 = v1 | 0xC000;
    v1 = 0x20000000;
    a0 = dsll32(a0, 0);
    v1 = v1 | a0;
    pcpyld(s0, zero, v1);
    v1 = sltu(0, s3);
    for (;;) {
        // 0x004ed5d4
        charge(ctx, 3);
        v1 = v1 ^ 0x1;
        s1 = s3;
        if (v1 == 0) {
            // 0x004ed5e0
            charge(ctx, 4);
            lw(v0, gp, -16868);  // 0x7CEB0C
            at = sltu(v0, s3);
            if (at != 0) {
                // 0x004ed5f0
                charge(ctx, 2);
                s1 = v0;
            }
            // 0x004ed5f8
            charge(ctx, 10);
            lw(t0, s5, 8);
            lw(v0, s5, 0);
            a0 = 3;
            a1 = 12;
            a2 = s1;
            a3 = 5;
            t1 = s6;
            jalr(ctx, 0x4ED610u, v0.u());
            if (v0 == 0) {
                goto L_004ed860;
            }
            goto L_004ed620;
        }
    L_004ed860:
        charge(ctx, 2);
        s1 = 0;
        backedge(ctx);
    L_004ed620:
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        // 0x004ed628
        charge(ctx, 4);
        v1 = 0x960000;
        lq(t2, v1, 22752);  // 0x9658E0
        s3 = subu(s3, s1);
        if (s1 != 0) {
            // 0x004ed638
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x004ed640
                charge(ctx, 10);
                v1 = 0x1000000;
                t0 = 16;
                a0 = v1 | 0x404;  // &0x1000404
                a2 = 0x10000000;
                v1 = 0x4000000;
                a0 = dsll32(a0, 0);
                a3 = v1 | a0;
                t3 = 0x960000;
                v1 = 0x7C000000;
                a1 = v1 | 0x8000;
                for (;;) {
                    // 0x004ed668
                    charge(ctx, 3);
                    at = sltiu(s1, 17);
                    t1 = s1;
                    if (at == 0) {
                        // 0x004ed674
                        charge(ctx, 1);
                        t1 = t0;
                    }
                    // 0x004ed678
                    charge(ctx, 27);
                    a0 = sll(t1, 1);
                    a0 = addu(a0, t1);
                    v1 = dsll32(t1, 0);
                    t4 = sll(a0, 2);
                    v1 = dsrl32(v1, 0);
                    t4 = dsll32(t4, 0);
                    a0 = sll(a0, 18);
                    t4 = dsrl32(t4, 0);
                    a0 = dsll32(a0, 0);
                    t4 = daddiu(t4, 2);
                    a0 = dsrl32(a0, 0);
                    v1 = v1 | a3;
                    t4 = t4 | a2;
                    pcpyld(t5, v1, t4);
                    lw(t4, gp, -17148);  // 0x7CE9F4
                    a0 = a0 | a1;
                    a0 = dsll32(a0, 0);
                    s1 = subu(s1, t1);
                    v1 = t1;
                    pcpyld(a0, a0, s0);
                    t1 = addiu(t1, -1);
                    sq(t5, t4, 0);
                    sq(a0, t4, 16);
                    lw(a0, gp, -17148);  // 0x7CE9F4
                    t4 = addiu(a0, 32);
                    sw(t4, gp, -17148);  // 0x7CE9F4
                    if (v1 != 0) {
                        // 0x004ed6e4
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004ed6e8
                            charge(ctx, 82);
                            lq(t6, s4, 0);
                            v1 = sll(s2, 6);
                            t4 = dsll32(t4, 0);
                            t4 = dsra32(t4, 0);
                            t5 = t1;
                            a0 = addu(s4, v1);
                            s2 = s2 ^ 0x3;
                            v1 = sll(s2, 6);
                            t1 = addiu(t1, -1);
                            v1 = addu(s4, v1);
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t6, s4, 16);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t6, s4, 32);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t6, s4, 48);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            s4 = addiu(s4, 64);
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t6, a0, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t6, a0, 16);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t6, a0, 32);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t4, a0, 48);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t4, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(a0, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t4, v1, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t4, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(a0, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t4, v1, 16);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t4, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(a0, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t4, v1, 32);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t4, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(a0, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(a0, v1, 48);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            sq(a0, v1, 0);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(v1, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            if (t5 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                    // 0x004ed830
                    charge(ctx, 8);
                    v1 = dsll32(t4, 0);
                    v1 = dsra32(v1, 0);
                    sq(t2, v1, 0);
                    lw(v1, gp, -17148);  // 0x7CE9F4
                    lq(t2, t3, 22608);
                    t4 = addiu(v1, 16);
                    sw(t4, gp, -17148);  // 0x7CE9F4
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x004ed850
        charge(ctx, 4);
        jal(ctx, 0x4ED850u, gen::fn_closeAndDispatchVU1Packet_004ec4c0);
        v1 = sltu(0, s3);
        backedge(ctx);
    }
    // 0x004ed868
    charge(ctx, 10);
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

// 0x004ED890 addCopyVU1PrimTriFan -- 784 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void addCopyVU1PrimTriFan(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::daddiu, hg::dsll32, hg::dsra32, hg::dsrl32,
          hg::enter, hg::jal, hg::jalr, hg::ld, hg::lq, hg::lui, hg::lw, hg::pcpyld, hg::sd, hg::sll, hg::sltiu,
          hg::sltu, hg::sq, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ed890
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    at = sltiu(a3, 3);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a1;
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a2;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (at != 0) {
        // 0x004ed8d0
        charge(ctx, 1);
        s3 = 0;
    } else {
        // 0x004ed8c8
        charge(ctx, 2);
        s3 = addiu(a3, -2);
    }
    // 0x004ed8d4
    charge(ctx, 8);
    v1 = lui(0xC000);
    s1 = s4;
    a0 = v1 | 0xC000;
    v1 = 0x20000000;
    a0 = dsll32(a0, 0);
    v1 = v1 | a0;
    pcpyld(s0, zero, v1);
    v1 = sltu(0, s3);
    for (;;) {
        // 0x004ed8f4
        charge(ctx, 3);
        v1 = v1 ^ 0x1;
        s2 = s3;
        if (v1 == 0) {
            // 0x004ed900
            charge(ctx, 4);
            lw(v0, gp, -16868);  // 0x7CEB0C
            at = sltu(v0, s3);
            if (at != 0) {
                // 0x004ed910
                charge(ctx, 2);
                s2 = v0;
            }
            // 0x004ed918
            charge(ctx, 10);
            lw(t0, s5, 8);
            lw(v0, s5, 0);
            a0 = 3;
            a1 = 12;
            a2 = s2;
            a3 = 5;
            t1 = s6;
            jalr(ctx, 0x4ED930u, v0.u());
            if (v0 == 0) {
                goto L_004edb70;
            }
            goto L_004ed940;
        }
    L_004edb70:
        charge(ctx, 2);
        s2 = 0;
        backedge(ctx);
    L_004ed940:
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        // 0x004ed948
        charge(ctx, 4);
        v1 = 0x960000;
        lq(t1, v1, 22752);  // 0x9658E0
        s3 = subu(s3, s2);
        if (s2 != 0) {
            // 0x004ed958
            charge(ctx, 2);
            if (s2 != 0) {
                // 0x004ed960
                charge(ctx, 10);
                v1 = 0x1000000;
                a3 = 16;
                a0 = v1 | 0x404;  // &0x1000404
                a1 = 0x10000000;
                v1 = 0x4000000;
                a0 = dsll32(a0, 0);
                a2 = v1 | a0;
                t2 = 0x960000;
                v1 = 0x7C000000;
                a0 = v1 | 0x8000;
                for (;;) {
                    // 0x004ed988
                    charge(ctx, 3);
                    at = sltiu(s2, 17);
                    t0 = s2;
                    if (at == 0) {
                        // 0x004ed994
                        charge(ctx, 1);
                        t0 = a3;
                    }
                    // 0x004ed998
                    charge(ctx, 27);
                    t3 = sll(t0, 1);
                    t3 = addu(t3, t0);
                    v1 = dsll32(t0, 0);
                    t4 = sll(t3, 2);
                    v1 = dsrl32(v1, 0);
                    t4 = dsll32(t4, 0);
                    t3 = sll(t3, 18);
                    t4 = dsrl32(t4, 0);
                    t3 = dsll32(t3, 0);
                    t4 = daddiu(t4, 2);
                    t3 = dsrl32(t3, 0);
                    v1 = v1 | a2;
                    t4 = t4 | a1;
                    pcpyld(t5, v1, t4);
                    lw(t4, gp, -17148);  // 0x7CE9F4
                    t3 = t3 | a0;
                    t3 = dsll32(t3, 0);
                    s2 = subu(s2, t0);
                    v1 = t0;
                    pcpyld(t3, t3, s0);
                    t0 = addiu(t0, -1);
                    sq(t5, t4, 0);
                    sq(t3, t4, 16);
                    lw(t3, gp, -17148);  // 0x7CE9F4
                    t3 = addiu(t3, 32);
                    sw(t3, gp, -17148);  // 0x7CE9F4
                    if (v1 != 0) {
                        // 0x004eda04
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004eda08
                            charge(ctx, 78);
                            lq(t5, s1, 0);
                            t3 = dsll32(t3, 0);
                            t4 = t0;
                            t3 = dsra32(t3, 0);
                            v1 = addiu(s4, 64);
                            t0 = addiu(t0, -1);
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s1, 16);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s1, 32);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s1, 48);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s4, 64);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s4, 80);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s4, 96);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s4, 112);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s4, 128);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s4, 144);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s4, 160);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            sq(t5, t3, 0);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(t3, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            lq(t5, s4, 176);
                            lw(t3, gp, -17148);  // 0x7CE9F4
                            s4 = v1;
                            sq(t5, t3, 0);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            t3 = addiu(v1, 16);
                            sw(t3, gp, -17148);  // 0x7CE9F4
                            if (t4 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                    // 0x004edb40
                    charge(ctx, 8);
                    v1 = dsll32(t3, 0);
                    v1 = dsra32(v1, 0);
                    sq(t1, v1, 0);
                    lw(v1, gp, -17148);  // 0x7CE9F4
                    lq(t1, t2, 22608);
                    t3 = addiu(v1, 16);
                    sw(t3, gp, -17148);  // 0x7CE9F4
                    if (s2 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x004edb60
        charge(ctx, 4);
        jal(ctx, 0x4EDB60u, gen::fn_closeAndDispatchVU1Packet_004ec4c0);
        v1 = sltu(0, s3);
        backedge(ctx);
    }
    // 0x004edb78
    charge(ctx, 10);
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

// ======================================================================================================
// The indexed builders (prim table 0x77F1D0): u16 indices (pointer in s3), vertex = verts (s4) + 64 * index.

// 0x004EDC20 addCopyVU1IndPrimLineList -- 688 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void addCopyVU1IndPrimLineList(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::daddiu, hg::dsll32, hg::dsra32, hg::dsrl32,
          hg::enter, hg::jal, hg::jalr, hg::ld, hg::lhu, hg::lq, hg::lui, hg::lw, hg::pcpyld, hg::sd, hg::sll,
          hg::sltiu, hg::sltu, hg::sq, hg::srl, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004edc20
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v1 = 0x20000000;
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a1;
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    a0 = lui(0xC000);
    sq(s2, sp, 0x20);
    a0 = a0 | 0xC000;
    sq(s1, sp, 0x10);
    a0 = dsll32(a0, 0);
    sq(s0, sp, 0x0);
    v1 = v1 | a0;
    s4 = a2;
    s3 = a3;
    s2 = srl(t0, 1);
    pcpyld(s0, zero, v1);
    v1 = sltu(0, s2);
    for (;;) {
        // 0x004edc74
        charge(ctx, 3);
        v1 = v1 ^ 0x1;
        s1 = s2;
        if (v1 == 0) {
            // 0x004edc80
            charge(ctx, 4);
            lw(v0, gp, -16872);  // 0x7CEB08
            at = sltu(v0, s2);
            if (at != 0) {
                // 0x004edc90
                charge(ctx, 2);
                s1 = v0;
            }
            // 0x004edc98
            charge(ctx, 10);
            lw(t0, s5, 4);
            lw(v0, s5, 0);
            a0 = 3;
            a1 = 8;
            a2 = s1;
            a3 = 1;
            t1 = s6;
            jalr(ctx, 0x4EDCB0u, v0.u());
            if (v0 == 0) {
                goto L_004edea0;
            }
            goto L_004edcc0;
        }
    L_004edea0:
        charge(ctx, 2);
        s1 = 0;
        backedge(ctx);
    L_004edcc0:
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        // 0x004edcc8
        charge(ctx, 4);
        v1 = 0x960000;
        lq(t2, v1, 22752);  // 0x9658E0
        s2 = subu(s2, s1);
        if (s1 != 0) {
            // 0x004edcd8
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x004edce0
                charge(ctx, 10);
                v1 = 0x1000000;
                t0 = 16;
                a0 = v1 | 0x404;  // &0x1000404
                a2 = 0x10000000;
                v1 = 0x4000000;
                a0 = dsll32(a0, 0);
                a3 = v1 | a0;
                t3 = 0x960000;
                v1 = 0x7C000000;
                a1 = v1 | 0x8000;
                for (;;) {
                    // 0x004edd08
                    charge(ctx, 3);
                    at = sltiu(s1, 17);
                    t1 = s1;
                    if (at == 0) {
                        // 0x004edd14
                        charge(ctx, 1);
                        t1 = t0;
                    }
                    // 0x004edd18
                    charge(ctx, 25);
                    v1 = sll(t1, 3);
                    a0 = dsll32(t1, 0);
                    v1 = dsll32(v1, 0);
                    a0 = dsrl32(a0, 0);
                    v1 = dsrl32(v1, 0);
                    t5 = a0 | a3;
                    v1 = daddiu(v1, 2);
                    a0 = v1 | a2;
                    lw(t4, gp, -17148);  // 0x7CE9F4
                    pcpyld(t5, t5, a0);
                    v1 = sll(t1, 19);
                    s1 = subu(s1, t1);
                    a0 = dsll32(v1, 0);
                    a0 = dsrl32(a0, 0);
                    v1 = t1;
                    a0 = a0 | a1;
                    t1 = addiu(t1, -1);
                    a0 = dsll32(a0, 0);
                    sq(t5, t4, 0);
                    pcpyld(a0, a0, s0);
                    sq(a0, t4, 16);
                    lw(a0, gp, -17148);  // 0x7CE9F4
                    t4 = addiu(a0, 32);
                    sw(t4, gp, -17148);  // 0x7CE9F4
                    if (v1 != 0) {
                        // 0x004edd7c
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004edd80
                            charge(ctx, 59);
                            lhu(a0, s3, 0);
                            lhu(v1, s3, 2);
                            t4 = dsll32(t4, 0);
                            t5 = t1;
                            t4 = dsra32(t4, 0);
                            t1 = addiu(t1, -1);
                            a0 = sll(a0, 6);
                            a0 = addu(s4, a0);
                            v1 = sll(v1, 6);
                            lq(t6, a0, 0);
                            v1 = addu(s4, v1);
                            s3 = addiu(s3, 4);
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t6, a0, 16);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t6, a0, 32);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t4, a0, 48);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t4, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(a0, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t4, v1, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t4, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(a0, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t4, v1, 16);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t4, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(a0, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t4, v1, 32);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t4, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(a0, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(a0, v1, 48);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            sq(a0, v1, 0);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(v1, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            if (t5 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004ede6c
                        charge(ctx, 1);
                    }
                    // 0x004ede70
                    charge(ctx, 8);
                    v1 = dsll32(t4, 0);
                    v1 = dsra32(v1, 0);
                    sq(t2, v1, 0);
                    lw(v1, gp, -17148);  // 0x7CE9F4
                    lq(t2, t3, 22608);
                    t4 = addiu(v1, 16);
                    sw(t4, gp, -17148);  // 0x7CE9F4
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x004ede90
        charge(ctx, 4);
        jal(ctx, 0x4EDE90u, gen::fn_closeAndDispatchVU1Packet_004ec4c0);
        v1 = sltu(0, s2);
        backedge(ctx);
    }
    // 0x004edea8
    charge(ctx, 10);
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

// 0x004EDED0 addCopyVU1IndPrimPolyLine -- 688 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void addCopyVU1IndPrimPolyLine(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::daddiu, hg::dsll32, hg::dsra32, hg::dsrl32,
          hg::enter, hg::jal, hg::jalr, hg::ld, hg::lhu, hg::lq, hg::lui, hg::lw, hg::pcpyld, hg::sd, hg::sll,
          hg::sltiu, hg::sltu, hg::sq, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004eded0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v1 = 0x20000000;
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a1;
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    a0 = lui(0xC000);
    sq(s2, sp, 0x20);
    a0 = a0 | 0xC000;
    sq(s1, sp, 0x10);
    a0 = dsll32(a0, 0);
    sq(s0, sp, 0x0);
    v1 = v1 | a0;
    s4 = a2;
    s3 = a3;
    s2 = addiu(t0, -1);
    pcpyld(s0, zero, v1);
    v1 = sltu(0, s2);
    for (;;) {
        // 0x004edf24
        charge(ctx, 3);
        v1 = v1 ^ 0x1;
        s1 = s2;
        if (v1 == 0) {
            // 0x004edf30
            charge(ctx, 4);
            lw(v0, gp, -16872);  // 0x7CEB08
            at = sltu(v0, s2);
            if (at != 0) {
                // 0x004edf40
                charge(ctx, 2);
                s1 = v0;
            }
            // 0x004edf48
            charge(ctx, 10);
            lw(t0, s5, 4);
            lw(v0, s5, 0);
            a0 = 3;
            a1 = 8;
            a2 = s1;
            a3 = 1;
            t1 = s6;
            jalr(ctx, 0x4EDF60u, v0.u());
            if (v0 == 0) {
                goto L_004ee150;
            }
            goto L_004edf70;
        }
    L_004ee150:
        charge(ctx, 2);
        s1 = 0;
        backedge(ctx);
    L_004edf70:
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        // 0x004edf78
        charge(ctx, 4);
        v1 = 0x960000;
        lq(t2, v1, 22752);  // 0x9658E0
        s2 = subu(s2, s1);
        if (s1 != 0) {
            // 0x004edf88
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x004edf90
                charge(ctx, 10);
                v1 = 0x1000000;
                t0 = 16;
                a0 = v1 | 0x404;  // &0x1000404
                a2 = 0x10000000;
                v1 = 0x4000000;
                a0 = dsll32(a0, 0);
                a3 = v1 | a0;
                t3 = 0x960000;
                v1 = 0x7C000000;
                a1 = v1 | 0x8000;
                for (;;) {
                    // 0x004edfb8
                    charge(ctx, 3);
                    at = sltiu(s1, 17);
                    t1 = s1;
                    if (at == 0) {
                        // 0x004edfc4
                        charge(ctx, 1);
                        t1 = t0;
                    }
                    // 0x004edfc8
                    charge(ctx, 25);
                    v1 = sll(t1, 3);
                    a0 = dsll32(t1, 0);
                    v1 = dsll32(v1, 0);
                    a0 = dsrl32(a0, 0);
                    v1 = dsrl32(v1, 0);
                    t5 = a0 | a3;
                    v1 = daddiu(v1, 2);
                    a0 = v1 | a2;
                    lw(t4, gp, -17148);  // 0x7CE9F4
                    pcpyld(t5, t5, a0);
                    v1 = sll(t1, 19);
                    s1 = subu(s1, t1);
                    a0 = dsll32(v1, 0);
                    a0 = dsrl32(a0, 0);
                    v1 = t1;
                    a0 = a0 | a1;
                    t1 = addiu(t1, -1);
                    a0 = dsll32(a0, 0);
                    sq(t5, t4, 0);
                    pcpyld(a0, a0, s0);
                    sq(a0, t4, 16);
                    lw(a0, gp, -17148);  // 0x7CE9F4
                    t4 = addiu(a0, 32);
                    sw(t4, gp, -17148);  // 0x7CE9F4
                    if (v1 != 0) {
                        // 0x004ee02c
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004ee030
                            charge(ctx, 59);
                            lhu(a0, s3, 0);
                            lhu(v1, s3, 2);
                            t4 = dsll32(t4, 0);
                            t5 = t1;
                            t4 = dsra32(t4, 0);
                            t1 = addiu(t1, -1);
                            a0 = sll(a0, 6);
                            a0 = addu(s4, a0);
                            v1 = sll(v1, 6);
                            lq(t6, a0, 0);
                            v1 = addu(s4, v1);
                            s3 = addiu(s3, 2);
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t6, a0, 16);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t6, a0, 32);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t4, a0, 48);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t4, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(a0, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t4, v1, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t4, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(a0, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t4, v1, 16);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t4, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(a0, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t4, v1, 32);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t4, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(a0, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(a0, v1, 48);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            sq(a0, v1, 0);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(v1, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            if (t5 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004ee11c
                        charge(ctx, 1);
                    }
                    // 0x004ee120
                    charge(ctx, 8);
                    v1 = dsll32(t4, 0);
                    v1 = dsra32(v1, 0);
                    sq(t2, v1, 0);
                    lw(v1, gp, -17148);  // 0x7CE9F4
                    lq(t2, t3, 22608);
                    t4 = addiu(v1, 16);
                    sw(t4, gp, -17148);  // 0x7CE9F4
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x004ee140
        charge(ctx, 4);
        jal(ctx, 0x4EE140u, gen::fn_closeAndDispatchVU1Packet_004ec4c0);
        v1 = sltu(0, s2);
        backedge(ctx);
    }
    // 0x004ee158
    charge(ctx, 10);
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

// 0x004EE180 addCopyVU1IndPrimTriList -- 816 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void addCopyVU1IndPrimTriList(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::daddiu, hg::dsll32, hg::dsra32, hg::dsrl32,
          hg::enter, hg::jal, hg::jalr, hg::ld, hg::lhu, hg::lq, hg::lui, hg::lw, hg::mfhi, hg::multu, hg::pcpyld,
          hg::sd, hg::sll, hg::sltiu, hg::sltu, hg::sq, hg::srl, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ee180
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v1 = lui(0xAAAA);
    sd(ra, sp, 0x70);
    v1 = v1 | 0xAAAB;
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a1;
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a2;
    sq(s2, sp, 0x20);
    s3 = a3;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    multu(zero, v1, t0);
    mfhi(a1);
    v1 = lui(0xC000);
    a0 = v1 | 0xC000;
    v1 = 0x20000000;
    a0 = dsll32(a0, 0);
    v1 = v1 | a0;
    s2 = srl(a1, 1);
    pcpyld(s0, zero, v1);
    v1 = sltu(0, s2);
    for (;;) {
        // 0x004ee1e4
        charge(ctx, 3);
        v1 = v1 ^ 0x1;
        s1 = s2;
        if (v1 == 0) {
            // 0x004ee1f0
            charge(ctx, 4);
            lw(v0, gp, -16868);  // 0x7CEB0C
            at = sltu(v0, s2);
            if (at != 0) {
                // 0x004ee200
                charge(ctx, 2);
                s1 = v0;
            }
            // 0x004ee208
            charge(ctx, 10);
            lw(t0, s5, 8);
            lw(v0, s5, 0);
            a0 = 3;
            a1 = 12;
            a2 = s1;
            a3 = 5;
            t1 = s6;
            jalr(ctx, 0x4EE220u, v0.u());
            if (v0 == 0) {
                goto L_004ee480;
            }
            goto L_004ee230;
        }
    L_004ee480:
        charge(ctx, 2);
        s1 = 0;
        backedge(ctx);
    L_004ee230:
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        // 0x004ee238
        charge(ctx, 4);
        v1 = 0x960000;
        lq(t3, v1, 22752);  // 0x9658E0
        s2 = subu(s2, s1);
        if (s1 != 0) {
            // 0x004ee248
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x004ee250
                charge(ctx, 10);
                v1 = 0x1000000;
                t1 = 16;
                a0 = v1 | 0x404;  // &0x1000404
                a3 = 0x10000000;
                v1 = 0x4000000;
                a0 = dsll32(a0, 0);
                t0 = v1 | a0;
                t4 = 0x960000;
                v1 = 0x7C000000;
                a2 = v1 | 0x8000;
                for (;;) {
                    // 0x004ee278
                    charge(ctx, 3);
                    at = sltiu(s1, 17);
                    t2 = s1;
                    if (at == 0) {
                        // 0x004ee284
                        charge(ctx, 1);
                        t2 = t1;
                    }
                    // 0x004ee288
                    charge(ctx, 27);
                    a0 = sll(t2, 1);
                    a0 = addu(a0, t2);
                    v1 = dsll32(t2, 0);
                    a1 = sll(a0, 2);
                    v1 = dsrl32(v1, 0);
                    a1 = dsll32(a1, 0);
                    a0 = sll(a0, 18);
                    a1 = dsrl32(a1, 0);
                    a0 = dsll32(a0, 0);
                    a1 = daddiu(a1, 2);
                    a0 = dsrl32(a0, 0);
                    v1 = v1 | t0;
                    a1 = a1 | a3;
                    pcpyld(t5, v1, a1);
                    lw(a1, gp, -17148);  // 0x7CE9F4
                    a0 = a0 | a2;
                    a0 = dsll32(a0, 0);
                    s1 = subu(s1, t2);
                    v1 = t2;
                    pcpyld(a0, a0, s0);
                    t2 = addiu(t2, -1);
                    sq(t5, a1, 0);
                    sq(a0, a1, 16);
                    lw(a0, gp, -17148);  // 0x7CE9F4
                    t5 = addiu(a0, 32);
                    sw(t5, gp, -17148);  // 0x7CE9F4
                    if (v1 != 0) {
                        // 0x004ee2f4
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004ee2f8
                            charge(ctx, 86);
                            lhu(a1, s3, 0);
                            lhu(a0, s3, 2);
                            t5 = dsll32(t5, 0);
                            lhu(v1, s3, 4);
                            t6 = t2;
                            t5 = dsra32(t5, 0);
                            t2 = addiu(t2, -1);
                            a1 = sll(a1, 6);
                            a1 = addu(s4, a1);
                            a0 = sll(a0, 6);
                            lq(t7, a1, 0);
                            v1 = sll(v1, 6);
                            a0 = addu(s4, a0);
                            v1 = addu(s4, v1);
                            s3 = addiu(s3, 6);
                            sq(t7, t5, 0);
                            lw(t5, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(t5, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(t7, a1, 16);
                            lw(t5, gp, -17148);  // 0x7CE9F4
                            sq(t7, t5, 0);
                            lw(t5, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(t5, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(t7, a1, 32);
                            lw(t5, gp, -17148);  // 0x7CE9F4
                            sq(t7, t5, 0);
                            lw(t5, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(t5, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(t5, a1, 48);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            sq(t5, a1, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(a1, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(t5, a0, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            sq(t5, a1, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(a1, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(t5, a0, 16);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            sq(t5, a1, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(a1, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(t5, a0, 32);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            sq(t5, a1, 0);
                            lw(a1, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(a1, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(a1, a0, 48);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(a1, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(a0, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(a1, v1, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(a1, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(a0, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(a1, v1, 16);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(a1, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(a0, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(a1, v1, 32);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(a1, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(a0, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(a0, v1, 48);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            sq(a0, v1, 0);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(v1, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            if (t6 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                    // 0x004ee450
                    charge(ctx, 8);
                    v1 = dsll32(t5, 0);
                    v1 = dsra32(v1, 0);
                    sq(t3, v1, 0);
                    lw(v1, gp, -17148);  // 0x7CE9F4
                    lq(t3, t4, 22608);
                    t5 = addiu(v1, 16);
                    sw(t5, gp, -17148);  // 0x7CE9F4
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x004ee470
        charge(ctx, 4);
        jal(ctx, 0x4EE470u, gen::fn_closeAndDispatchVU1Packet_004ec4c0);
        v1 = sltu(0, s2);
        backedge(ctx);
    }
    // 0x004ee488
    charge(ctx, 10);
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

// 0x004EE4B0 addCopyVU1IndPrimTriStrip -- 864 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void addCopyVU1IndPrimTriStrip(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::daddiu, hg::dsll32, hg::dsra32, hg::dsrl32,
          hg::enter, hg::jal, hg::jalr, hg::ld, hg::lhu, hg::lq, hg::lui, hg::lw, hg::pcpyld, hg::sd, hg::sll,
          hg::sltiu, hg::sltu, hg::sq, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ee4b0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    at = sltiu(t0, 3);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    s7 = a1;
    sq(s5, sp, 0x50);
    s6 = a0;
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a2;
    sq(s2, sp, 0x20);
    s3 = a3;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (at != 0) {
        // 0x004ee4f8
        charge(ctx, 1);
        s5 = 0;
    } else {
        // 0x004ee4f0
        charge(ctx, 2);
        s5 = addiu(t0, -2);
    }
    // 0x004ee4fc
    charge(ctx, 8);
    v1 = lui(0xC000);
    s2 = 1;
    a0 = v1 | 0xC000;
    v1 = 0x20000000;
    a0 = dsll32(a0, 0);
    v1 = v1 | a0;
    pcpyld(s0, zero, v1);
    v1 = sltu(0, s5);
    for (;;) {
        // 0x004ee51c
        charge(ctx, 3);
        v1 = v1 ^ 0x1;
        s1 = s5;
        if (v1 == 0) {
            // 0x004ee528
            charge(ctx, 4);
            lw(v0, gp, -16868);  // 0x7CEB0C
            at = sltu(v0, s5);
            if (at != 0) {
                // 0x004ee538
                charge(ctx, 2);
                s1 = v0;
            }
            // 0x004ee540
            charge(ctx, 10);
            lw(t0, s6, 8);
            lw(v0, s6, 0);
            a0 = 3;
            a1 = 12;
            a2 = s1;
            a3 = 5;
            t1 = s7;
            jalr(ctx, 0x4EE558u, v0.u());
            if (v0 == 0) {
                goto L_004ee7d0;
            }
            goto L_004ee568;
        }
    L_004ee7d0:
        charge(ctx, 2);
        s1 = 0;
        backedge(ctx);
    L_004ee568:
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        // 0x004ee570
        charge(ctx, 4);
        v1 = 0x960000;
        lq(t2, v1, 22752);  // 0x9658E0
        s5 = subu(s5, s1);
        if (s1 != 0) {
            // 0x004ee580
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x004ee588
                charge(ctx, 10);
                v1 = 0x1000000;
                t0 = 16;
                a0 = v1 | 0x404;  // &0x1000404
                a2 = 0x10000000;
                v1 = 0x4000000;
                a0 = dsll32(a0, 0);
                a3 = v1 | a0;
                t3 = 0x960000;
                v1 = 0x7C000000;
                a1 = v1 | 0x8000;
                for (;;) {
                    // 0x004ee5b0
                    charge(ctx, 3);
                    at = sltiu(s1, 17);
                    t1 = s1;
                    if (at == 0) {
                        // 0x004ee5bc
                        charge(ctx, 1);
                        t1 = t0;
                    }
                    // 0x004ee5c0
                    charge(ctx, 27);
                    a0 = sll(t1, 1);
                    a0 = addu(a0, t1);
                    v1 = dsll32(t1, 0);
                    t4 = sll(a0, 2);
                    v1 = dsrl32(v1, 0);
                    t4 = dsll32(t4, 0);
                    a0 = sll(a0, 18);
                    t4 = dsrl32(t4, 0);
                    a0 = dsll32(a0, 0);
                    t4 = daddiu(t4, 2);
                    a0 = dsrl32(a0, 0);
                    v1 = v1 | a3;
                    t4 = t4 | a2;
                    pcpyld(t5, v1, t4);
                    lw(t4, gp, -17148);  // 0x7CE9F4
                    a0 = a0 | a1;
                    a0 = dsll32(a0, 0);
                    s1 = subu(s1, t1);
                    v1 = t1;
                    pcpyld(a0, a0, s0);
                    t1 = addiu(t1, -1);
                    sq(t5, t4, 0);
                    sq(a0, t4, 16);
                    lw(a0, gp, -17148);  // 0x7CE9F4
                    t5 = addiu(a0, 32);
                    sw(t5, gp, -17148);  // 0x7CE9F4
                    if (v1 != 0) {
                        // 0x004ee62c
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004ee630
                            charge(ctx, 91);
                            v1 = sll(s2, 1);
                            s2 = s2 ^ 0x3;
                            lhu(a0, s3, 0);
                            t4 = sll(s2, 1);
                            v1 = addu(s3, v1);
                            t6 = addu(s3, t4);
                            lhu(v1, v1, 0);
                            lhu(t7, t6, 0);
                            t5 = dsll32(t5, 0);
                            t4 = t1;
                            t5 = dsra32(t5, 0);
                            t1 = addiu(t1, -1);
                            a0 = sll(a0, 6);
                            s3 = addiu(s3, 2);
                            a0 = addu(s4, a0);
                            v1 = sll(v1, 6);
                            lq(t6, a0, 0);
                            t7 = sll(t7, 6);
                            v1 = addu(s4, v1);
                            t7 = addu(s4, t7);
                            sq(t6, t5, 0);
                            lw(t5, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(t5, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(t6, a0, 16);
                            lw(t5, gp, -17148);  // 0x7CE9F4
                            sq(t6, t5, 0);
                            lw(t5, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(t5, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(t6, a0, 32);
                            lw(t5, gp, -17148);  // 0x7CE9F4
                            sq(t6, t5, 0);
                            lw(t5, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(t5, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(t5, a0, 48);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t5, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(a0, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(t5, v1, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t5, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(a0, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(t5, v1, 16);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t5, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(a0, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(t5, v1, 32);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t5, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(a0, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(a0, v1, 48);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            sq(a0, v1, 0);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(v1, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(a0, t7, 0);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            sq(a0, v1, 0);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(v1, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(a0, t7, 16);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            sq(a0, v1, 0);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(v1, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(a0, t7, 32);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            sq(a0, v1, 0);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(v1, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            lq(a0, t7, 48);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            sq(a0, v1, 0);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            t5 = addiu(v1, 16);
                            sw(t5, gp, -17148);  // 0x7CE9F4
                            if (t4 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004ee79c
                        charge(ctx, 1);
                    }
                    // 0x004ee7a0
                    charge(ctx, 8);
                    v1 = dsll32(t5, 0);
                    v1 = dsra32(v1, 0);
                    sq(t2, v1, 0);
                    lw(v1, gp, -17148);  // 0x7CE9F4
                    lq(t2, t3, 22608);
                    t5 = addiu(v1, 16);
                    sw(t5, gp, -17148);  // 0x7CE9F4
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x004ee7c0
        charge(ctx, 4);
        jal(ctx, 0x4EE7C0u, gen::fn_closeAndDispatchVU1Packet_004ec4c0);
        v1 = sltu(0, s5);
        backedge(ctx);
    }
    // 0x004ee7d8
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x004EE810 addCopyVU1IndPrimTriFan -- 828 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void addCopyVU1IndPrimTriFan(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::daddiu, hg::dsll32, hg::dsra32, hg::dsrl32,
          hg::enter, hg::jal, hg::jalr, hg::ld, hg::lhu, hg::lq, hg::lui, hg::lw, hg::pcpyld, hg::sd, hg::sll,
          hg::sltiu, hg::sltu, hg::sq, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ee810
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    at = sltiu(t0, 3);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    s7 = a1;
    sq(s5, sp, 0x50);
    s6 = a0;
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a2;
    sq(s2, sp, 0x20);
    s3 = a3;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (at != 0) {
        // 0x004ee858
        charge(ctx, 1);
        s5 = 0;
    } else {
        // 0x004ee850
        charge(ctx, 2);
        s5 = addiu(t0, -2);
    }
    // 0x004ee85c
    charge(ctx, 10);
    lhu(a1, s3, 0);
    v1 = lui(0xC000);
    a0 = v1 | 0xC000;
    v1 = 0x20000000;
    a0 = dsll32(a0, 0);
    v1 = v1 | a0;
    pcpyld(s0, zero, v1);
    v1 = sll(a1, 6);
    s1 = addu(s4, v1);
    v1 = sltu(0, s5);
    for (;;) {
        // 0x004ee884
        charge(ctx, 3);
        v1 = v1 ^ 0x1;
        s2 = s5;
        if (v1 == 0) {
            // 0x004ee890
            charge(ctx, 4);
            lw(v0, gp, -16868);  // 0x7CEB0C
            at = sltu(v0, s5);
            if (at != 0) {
                // 0x004ee8a0
                charge(ctx, 2);
                s2 = v0;
            }
            // 0x004ee8a8
            charge(ctx, 10);
            lw(t0, s6, 8);
            lw(v0, s6, 0);
            a0 = 3;
            a1 = 12;
            a2 = s2;
            a3 = 5;
            t1 = s7;
            jalr(ctx, 0x4EE8C0u, v0.u());
            if (v0 == 0) {
                goto L_004eeb18;
            }
            goto L_004ee8d0;
        }
    L_004eeb18:
        charge(ctx, 2);
        s2 = 0;
        backedge(ctx);
    L_004ee8d0:
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        // 0x004ee8d8
        charge(ctx, 4);
        v1 = 0x960000;
        lq(t2, v1, 22752);  // 0x9658E0
        s5 = subu(s5, s2);
        if (s2 != 0) {
            // 0x004ee8e8
            charge(ctx, 2);
            if (s2 != 0) {
                // 0x004ee8f0
                charge(ctx, 10);
                v1 = 0x1000000;
                t0 = 16;
                a0 = v1 | 0x404;  // &0x1000404
                a2 = 0x10000000;
                v1 = 0x4000000;
                a0 = dsll32(a0, 0);
                a3 = v1 | a0;
                t3 = 0x960000;
                v1 = 0x7C000000;
                a1 = v1 | 0x8000;
                for (;;) {
                    // 0x004ee918
                    charge(ctx, 3);
                    at = sltiu(s2, 17);
                    t1 = s2;
                    if (at == 0) {
                        // 0x004ee924
                        charge(ctx, 1);
                        t1 = t0;
                    }
                    // 0x004ee928
                    charge(ctx, 27);
                    a0 = sll(t1, 1);
                    a0 = addu(a0, t1);
                    v1 = dsll32(t1, 0);
                    t4 = sll(a0, 2);
                    v1 = dsrl32(v1, 0);
                    t4 = dsll32(t4, 0);
                    a0 = sll(a0, 18);
                    t4 = dsrl32(t4, 0);
                    a0 = dsll32(a0, 0);
                    t4 = daddiu(t4, 2);
                    a0 = dsrl32(a0, 0);
                    v1 = v1 | a3;
                    t4 = t4 | a2;
                    pcpyld(t5, v1, t4);
                    lw(t4, gp, -17148);  // 0x7CE9F4
                    a0 = a0 | a1;
                    a0 = dsll32(a0, 0);
                    s2 = subu(s2, t1);
                    v1 = t1;
                    pcpyld(a0, a0, s0);
                    t1 = addiu(t1, -1);
                    sq(t5, t4, 0);
                    sq(a0, t4, 16);
                    lw(a0, gp, -17148);  // 0x7CE9F4
                    t4 = addiu(a0, 32);
                    sw(t4, gp, -17148);  // 0x7CE9F4
                    if (v1 != 0) {
                        // 0x004ee994
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004ee998
                            charge(ctx, 83);
                            v1 = dsll32(t4, 0);
                            lhu(a0, s3, 2);
                            t5 = t1;
                            lhu(t6, s3, 4);
                            v1 = dsra32(v1, 0);
                            lq(t4, s1, 0);
                            t1 = addiu(t1, -1);
                            a0 = sll(a0, 6);
                            t6 = sll(t6, 6);
                            a0 = addu(s4, a0);
                            sq(t4, v1, 0);
                            s3 = addiu(s3, 2);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            v1 = addu(s4, t6);
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t6, s1, 16);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t6, s1, 32);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t6, s1, 48);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t6, a0, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t6, a0, 16);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t6, a0, 32);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            sq(t6, t4, 0);
                            lw(t4, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(t4, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t4, a0, 48);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t4, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(a0, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t4, v1, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t4, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(a0, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t4, v1, 16);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t4, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(a0, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(t4, v1, 32);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            sq(t4, a0, 0);
                            lw(a0, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(a0, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            lq(a0, v1, 48);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            sq(a0, v1, 0);
                            lw(v1, gp, -17148);  // 0x7CE9F4
                            t4 = addiu(v1, 16);
                            sw(t4, gp, -17148);  // 0x7CE9F4
                            if (t5 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004eeae4
                        charge(ctx, 1);
                    }
                    // 0x004eeae8
                    charge(ctx, 8);
                    v1 = dsll32(t4, 0);
                    v1 = dsra32(v1, 0);
                    sq(t2, v1, 0);
                    lw(v1, gp, -17148);  // 0x7CE9F4
                    lq(t2, t3, 22608);
                    t4 = addiu(v1, 16);
                    sw(t4, gp, -17148);  // 0x7CE9F4
                    if (s2 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x004eeb08
        charge(ctx, 4);
        jal(ctx, 0x4EEB08u, gen::fn_closeAndDispatchVU1Packet_004ec4c0);
        v1 = sltu(0, s5);
        backedge(ctx);
    }
    // 0x004eeb20
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// ======================================================================================================
// The device entry points.

u32 SkyIm2DRenderLine(EEContext& ctx, u32 verts, u32 num_verts, u32 i0, u32 i1) {  // [SkyIm2DRenderLine]
    (void)num_verts;
    guest::enter(ctx, 6);
    Frame frame(ctx, 16, {{GPR_RA, 0, false}});
    Regs r{ctx};
    const bool fog = fog_selected(ctx);
    guest::charge(ctx, fog ? 3 : 2);
    const u32 desc = fog ? kDescriptorFog : kDescriptorNoFog;
    guest::charge(ctx, 11);
    r.lo(GPR_V1, sx(i0 << 6));
    r.lo(GPR_V0, sx(i1 << 6));
    r.lo(GPR_A2, sx(vertex_at(verts, i0)));
    r.lo(GPR_A3, sx(vertex_at(verts, i1)));
    r.lo(GPR_A0, desc);
    r.lo(GPR_A1, 0);
    frame.link(0x4ECAA0u);
    addCopyVU1Line(ctx, desc, 0, vertex_at(verts, i0), vertex_at(verts, i1));
    guest::ret32(ctx, 1);
    return 1;
}

u32 SkyIm2DRenderTriangle(EEContext& ctx, u32 verts, u32 num_verts, u32 i0, u32 i1, u32 i2) {  // [SkyIm2DRenderTriangle]
    (void)num_verts;
    guest::enter(ctx, 6);
    Frame frame(ctx, 16, {{GPR_RA, 0, false}});
    Regs r{ctx};
    const bool fog = fog_selected(ctx);
    guest::charge(ctx, fog ? 3 : 2);
    const u32 desc = fog ? kDescriptorFog : kDescriptorNoFog;
    guest::charge(ctx, 13);
    r.lo(GPR_T1, desc);
    r.lo(GPR_V0, sx(i2 << 6));
    r.lo(GPR_V1, sx(i0 << 6));
    r.lo(GPR_A3, sx(vertex_at(verts, i1)));
    r.lo(GPR_A2, sx(vertex_at(verts, i0)));
    r.lo(GPR_A1, 0);
    r.lo(GPR_T0, sx(vertex_at(verts, i2)));
    r.lo(GPR_A0, desc);
    frame.link(0x4ECD28u);
    addCopyVU1Triangle(ctx, desc, 0, vertex_at(verts, i0), vertex_at(verts, i1), vertex_at(verts, i2));
    guest::ret32(ctx, 1);
    return 1;
}

namespace {
// SkyIm2DRender(Indexed)Primitive: prim 1..5 -> table[prim](descriptor, 0, verts, $a3, $t0) by jalr. The
// early returns leave $v1 = prim and $at = (prim < 6) as the original does (the callers set the delay-slot
// copy each variant makes before this).
u32 render_prim(EEContext& ctx, u64 prim, u64 verts, u32 table, u32 table_cycles, u32 call_pc) {
    Frame frame(ctx, 16, {{GPR_RA, 0, false}});
    Regs r{ctx};
    r.lo(GPR_V1, prim);
    if (static_cast<s64>(prim) <= 0) {
        guest::charge(ctx, 4);
        guest::ret32(ctx, 1);
        return 1;
    }
    guest::charge(ctx, 3);
    r.lo(GPR_AT, prim < 6 ? 1 : 0);
    if (prim >= 6) {
        guest::charge(ctx, 4);
        guest::ret32(ctx, 1);
        return 1;
    }
    guest::charge(ctx, 4);
    const bool fog = fog_selected(ctx);
    guest::charge(ctx, fog ? 3 : 2);
    guest::charge(ctx, table_cycles);
    const u32 slot = static_cast<u32>(prim) << 2;
    const u32 builder = guest::load<u32>(ctx, table + slot);
    r.lo(GPR_V1, sx(slot));
    r.lo(GPR_V0, sx(builder));
    r.lo(GPR_A0, fog ? kDescriptorFog : kDescriptorNoFog);
    r.lo(GPR_A1, 0);
    r.lo(GPR_A2, verts);
    frame.link(call_pc);
    rt::lookup_func(builder)(ctx);
    guest::charge(ctx, 4);
    guest::ret32(ctx, 1);
    return 1;
}
}  // namespace

u32 SkyIm2DRenderPrimitive(EEContext& ctx, u64 prim, u64 verts, u64 num_verts) {  // [SkyIm2DRenderPrimitive]
    guest::enter(ctx, 5);
    core::set_gpr64(ctx, GPR_A3, num_verts);  // delay slot (every path): builder argument 4
    return render_prim(ctx, prim, verts, kPrimTable, 8, 0x4EDBFCu);
}

u32 SkyIm2DRenderIndexedPrimitive(EEContext& ctx, u64 prim, u64 verts, u64 num_verts) {  // [SkyIm2DRenderIndexedPrimitive]
    (void)num_verts;
    guest::enter(ctx, 5);
    core::set_gpr64(ctx, GPR_A2, verts);  // delay slot (every path): builder argument 3; $a3 / $t0 pass through
    return render_prim(ctx, prim, verts, kIndexedPrimTable, 7, 0x4EEBA8u);
}

}  // namespace p3fes::game

// ======================================================================================================
// The recompiled program's entry points (generated signature; arguments from $a0..$a3, $t0).
namespace p3fes::recomp_gen {

using p3fes::EEContext;
namespace guest = p3fes::game::guest;
namespace core = p3fes::ee::core;

void fn_closeAndDispatchVU1Packet_004ec4c0(EEContext& ctx) { p3fes::game::closeAndDispatchVU1Packet(ctx); }
void fn_open2DVU1Pkt_004ec100(EEContext& ctx) {
    p3fes::game::open2DVU1Pkt(ctx, guest::arg32(ctx, 0), guest::arg32(ctx, 1), guest::arg32(ctx, 2), guest::arg32(ctx, 3),
                            core::gpr64(ctx, GPR_T0));
}

#define P3FES_IM2D_PRIM_SHIM(name, addr)                                                                      \
    void fn_##name##_##addr(EEContext& ctx) {                                                                 \
        p3fes::game::name(ctx, guest::arg32(ctx, 0), core::gpr64(ctx, GPR_A1), guest::arg32(ctx, 2),          \
                          core::gpr64(ctx, GPR_A3));                                                          \
    }
#undef P3FES_IM2D_PRIM_SHIM

#define P3FES_IM2D_INDEXED_SHIM(name, addr)                                                                   \
    void fn_##name##_##addr(EEContext& ctx) {                                                                 \
        p3fes::game::name(ctx, guest::arg32(ctx, 0), core::gpr64(ctx, GPR_A1), guest::arg32(ctx, 2),          \
                          guest::arg32(ctx, 3), core::gpr64(ctx, GPR_T0));                                    \
    }
#undef P3FES_IM2D_INDEXED_SHIM

void fn_SkyIm2DRenderLine_004eca60(EEContext& ctx) {
    p3fes::game::SkyIm2DRenderLine(ctx, guest::arg32(ctx, 0), guest::arg32(ctx, 1), guest::arg32(ctx, 2), guest::arg32(ctx, 3));
}
void fn_SkyIm2DRenderTriangle_004ecce0(EEContext& ctx) {
    p3fes::game::SkyIm2DRenderTriangle(ctx, guest::arg32(ctx, 0), guest::arg32(ctx, 1), guest::arg32(ctx, 2), guest::arg32(ctx, 3),
                            core::gpr32(ctx, GPR_T0));
}
void fn_SkyIm2DRenderPrimitive_004edba0(EEContext& ctx) {
    p3fes::game::SkyIm2DRenderPrimitive(ctx, core::gpr64(ctx, GPR_A0), core::gpr64(ctx, GPR_A1), core::gpr64(ctx, GPR_A2));
}
void fn_SkyIm2DRenderIndexedPrimitive_004eeb50(EEContext& ctx) {
    p3fes::game::SkyIm2DRenderIndexedPrimitive(ctx, core::gpr64(ctx, GPR_A0), core::gpr64(ctx, GPR_A1), core::gpr64(ctx, GPR_A2));
}

}  // namespace p3fes::recomp_gen
